#pragma once
// The game's packed image formats (part of soa_codec; docs/notes.md "SLZ compressed files" and
// "Image assets and gacha banners"): what tools/aif2png reads and the server's English art
// generator (soaserver/english_art.h) reads and writes.
//
//   SLZ   Aska's chunked compression: codec 5 (raw deflate) and 7 (zstd) read, 5 written
//         (64 KiB chunks, zlib level 9: the same input gives the same bytes);
//   ISF   Framework::FileStream images ("\0ISF"): the members of a Cocos scene (UI/etc2/*.csf:
//         <name>.msgp, <name>.aif, <name>.csv) and of the font (Font/etc2/font.fpk);
//   AIF   the texture container (' FIA' ... ' FMA'): the images ('Xgmi' headers) and where their
//         pixels are;
//   ETC2  the pixel formats 47 (RGB8), 48 (RGB8 punch-through A1), 49 (RGBA8: EAC alpha + ETC2
//         colour), decoded per 4x4 block; all three encoded per block (ETC1 individual /
//         differential modes, both flips, every table; 48 differential only, with its transparent
//         index; EAC alpha by search), integer arithmetic
//         only, so the bytes are the same on every platform.
// ADLD (the XOR / AES layer over these files) is soa/adld.h.
#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace soa::aska {

using Bytes = std::vector<uint8_t>;

// ---- SLZ ----------------------------------------------------------------------------------------
// Header (little-endian): "SLZ", u8 codec (0 stored, 5 raw deflate, 7 zstd), ..., i32 size at 0xc,
// u32 payload offset at 0x14, u8 chunk KiB at 0x19 (0: one chunk), u32 chain at 0x1c (0: none).
// Each chunk of a codec 5 / 7 file is a u16 size and that many bytes; size 0 means the chunk is
// stored raw. Python: soa_save.slz.
bool is_slz(const Bytes& d);
// One chunk of an SLZ file.
struct SlzChunk {
    size_t offset = 0;  // its bytes in the file (after its u16 size)
    size_t stored = 0;  // how many
    size_t size = 0;    // what it decompresses to
    bool raw = false;   // stored uncompressed (codec 0, or a size field of 0)
};
// The chunks of an SLZ file, in order, from its header and size fields. False (and *err) when it
// isn't SLZ, is chained, or runs past the end: `chunks` then holds those before the failure.
bool slz_chunks(const Bytes& d, std::vector<SlzChunk>& chunks, std::string* err = nullptr);
// The decompressed bytes of an SLZ file (single header, no chain); a file that isn't SLZ is copied.
// `limit`: stop after the chunk that reaches this many bytes (a prefix: e.g. a scene's first member
// without its atlas); the default decodes everything.
bool slz_decode(const Bytes& in, Bytes& out, std::string* err = nullptr, size_t limit = SIZE_MAX);
// SLZ codec 5 as the shipped files have it: header {"SLZ", 5, 0, 1, 0x25, compressed size,
// size, 0, payload at 0x20, flags 1, 64 KiB chunks, 0x10, no chain}, each chunk a u16 size + raw
// deflate (size 0: stored), the whole padded to 4.
Bytes slz_encode(const Bytes& plain);

// ---- ISF ----------------------------------------------------------------------------------------
struct IsfEntry {
    std::string name;
    size_t index = 0;     // its slot in the entry table
    uint32_t offset = 0;  // payload offset and length in the image
    uint32_t size = 0;
};
// The entries of a "\0ISF" image (empty when `d` isn't one).
std::vector<IsfEntry> isf_entries(const Bytes& d);
// The entry's fourth word as the game's files have it: the byte sum of its payload padded to 16
// bytes with 0xee (the padding the files carry). Recomputed after a payload is changed in place.
uint32_t isf_payload_sum(const Bytes& d, const IsfEntry& e);
void isf_update_sum(Bytes& d, const IsfEntry& e);
// The image laid out again with some payloads replaced: `payloads[i]` (by entry index; nullptr =
// the entry's own bytes). Everything before the first payload (header, entry table, names) is kept;
// the payloads follow in entry order, each at a 32-byte boundary after the previous one, the gaps
// and the end padded with 0xee, each entry's offset, size and sum rewritten. The layout of all 853
// 3.7.0 scenes (english.md 7.14), so payloads == all nullptr gives the input back byte for byte.
// False (and *err) when `d` isn't an ISF image laid out that way.
bool isf_repack(const Bytes& d, const std::vector<const Bytes*>& payloads, Bytes& out, std::string* err = nullptr);

// ---- ETC2 / EAC blocks ----------------------------------------------------------------------------
enum Format : int { kJpeg = 39, kEtc2Rgb8 = 47, kEtc2Rgb8A1 = 48, kEtc2Rgba8 = 49 };
// Bytes per 4x4 block (8 or 16), 0 for a format that isn't ETC.
int block_bytes(int fmt);
// One block into rgba[y * 4 + x][4].
void decode_block(int fmt, const uint8_t* block, uint8_t rgba[16][4]);
// One block from rgba[y * 4 + x][4]: 16 bytes for kEtc2Rgba8, 8 for kEtc2Rgb8 (alpha ignored) and
// kEtc2Rgb8A1 (alpha < 128: transparent).
// False for another format.
bool encode_block(int fmt, const uint8_t rgba[16][4], uint8_t* out);

// ---- AIF ------------------------------------------------------------------------------------------
struct ImageRef {
    size_t container = 0;  // the ' FIA' it belongs to
    size_t header = 0;     // its 'Xgmi' chunk
    size_t data = 0;       // its pixel bytes
    size_t data_size = 0;
    int fmt = 0, w = 0, h = 0;
};
// Every image of the AIF containers in `d` (an .aif, or an ISF image with an .aif member), in
// file order; an image whose pixels can't be located is left out.
std::vector<ImageRef> find_images(const Bytes& d);
// An ETC image's pixels as RGBA8 (w * h * 4, top-down, straight alpha). False (and *err) for JPEG
// or a short buffer.
bool decode_image(const Bytes& d, const ImageRef& img, Bytes& rgba, std::string* err = nullptr);

}  // namespace soa::aska
