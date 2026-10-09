#pragma once
// AFF: the container of the game's 3D files (.asf scenes, .aaf animations, .acf collision; part of
// soa_models). docs/notes.md "Models and animation" and "Meshes (ASF)" describe the layout; this
// header reads what is common to them:
//   - the chunk walk: every chunk is {u32 tag, u32 size, u32, u32 offset of the next chunk};
//   - the AMF chunk (' FMA') that ends a file whose bulk data (vertex, index and pixel blocks) is
//     kept apart from the chunk tree: 'buff' entries (one per data buffer, stored back to back at
//     the end of the file) and 'addr' entries (a block of a buffer, named by a 16-byte AUID);
//   - the block codecs the game's Aska::MappedMemoryManager::TranslateMappedBufferEx applies when a
//     buffer's type is a compressed one: TriListComp::DecompressTriangleList (types 7..12) and
//     IdxBufComp::DecompressIndexBuffer (13..18).
// The files on disk are ADLD-wrapped and mostly SLZ-compressed: soa/adld.h and soa/aska_image.h
// (slz_decode) undo those first.
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <map>
#include <string>
#include <vector>

namespace soa::aff {

using Bytes = std::vector<uint8_t>;

inline uint32_t rd32(const uint8_t* p) { uint32_t v; memcpy(&v, p, 4); return v; }
inline uint16_t rd16(const uint8_t* p) { uint16_t v; memcpy(&v, p, 2); return v; }
inline uint64_t rd64(const uint8_t* p) { uint64_t v; memcpy(&v, p, 8); return v; }
inline float rdf(const uint8_t* p) { float v; memcpy(&v, p, 4); return v; }

// A chunk tag as stored (the bytes of a little-endian multi-character constant: 'AMF ' reads " FMA").
inline bool tag_is(const uint8_t* p, const char (&t)[5]) { return memcmp(p, t, 4) == 0; }

struct Auid {
    uint8_t b[16] = {};
    bool zero() const { for (uint8_t x : b) if (x) return false; return true; }
    bool operator<(const Auid& o) const { return memcmp(b, o.b, 16) < 0; }
    std::string hex() const;
};
inline Auid auid_at(const uint8_t* p) { Auid a; memcpy(a.b, p, 16); return a; }

// One 'buff' entry of the AMF chunk: +0x10 u64 stored size, +0x18 u64 offset (in the authoring
// tool's layout; not used to find the bytes), +0x20 u32 alignment, +0x2c s16 type
// (Aska::MappedTarget: 0 raw; |type| 7..12 triangle lists, 13..18 bit-packed index lists),
// +0x30 u64 size after decompression.
struct Buffer {
    uint64_t size = 0, offset = 0, decoded_size = 0;
    int16_t type = 0;
    size_t start = 0;  // where its bytes are in the file
};
// One 'addr' entry: +0x10 AUID, +0x20 u64 stored size, +0x28 u64 offset in its buffer, +0x30 u32
// alignment, +0x3c u16 buffer type (the 'buff' it is in), +0x3e u8 kind, +0x3f u8 flags,
// +0x48 u64 size after decompression.
struct Block {
    uint64_t size = 0, offset = 0, decoded_size = 0;
    uint32_t align = 0;
    int16_t buffer_type = 0;
    uint8_t kind = 0, flags = 0;
};

class Amf {
public:
    // Reads the AMF chunk of a whole decoded file (`d` must outlive this). False when there is no
    // AMF chunk (then every block lookup fails) or its entries run past the end.
    bool parse(const Bytes& d, std::string* err = nullptr);
    bool present() const { return amf_ != SIZE_MAX; }
    const std::vector<Buffer>& buffers() const { return buffers_; }
    const std::map<Auid, Block>& blocks() const { return blocks_; }
    const Block* find(const Auid& a) const;
    // A block's bytes as the game maps them: raw blocks copied, compressed ones decompressed to
    // their decoded size. False when the AUID is unknown or the data doesn't decode.
    bool block(const Auid& a, Bytes& out, std::string* err = nullptr) const;
    // Where a raw block's bytes are in the file (0, nullptr for a compressed or unknown block).
    const uint8_t* raw_block(const Auid& a, size_t* n = nullptr) const;

private:
    const Bytes* d_ = nullptr;
    size_t amf_ = SIZE_MAX;
    std::vector<Buffer> buffers_;
    std::map<Auid, Block> blocks_;
    const Buffer* buffer_of(const Block& b) const;
};

// Aska::TriListComp::DecompressTriangleList(src, dst, src_size, dst_size): u16 words; the first is
// the "high watermark" constant K (0xffff: the indices are stored as they are). Each later word w
// decodes to hw - w (16 bits), and hw = max(hw, index + K) (hw starts at K - 1). Groups of three
// indices a, b, c are one triangle; when a < b a fourth index d follows and the group is the two
// triangles (a, b, c), (a, d, b). Writes at most dst_size bytes of u16 indices. False when the
// output would overflow.
bool decompress_triangle_list(const uint8_t* src, size_t src_size, uint8_t* dst, size_t dst_size);
// Aska::IdxBufComp::DecompressIndexBuffer(src, dst, src_size, dst_size): a bit stream (LSB first):
// u32 count, u16 first index, then runs: a u16 run length n and n signed deltas of `bits` bits
// (bits starts at 3), each added to the previous index; when bits > 4 and more indices are due an
// absolute u16 index follows and bits restarts at 3, else bits grows by one; stops at bits 32 or
// `count` indices.
bool decompress_index_buffer(const uint8_t* src, size_t src_size, uint8_t* dst, size_t dst_size);

// A game file as the game reads it: ADLD undone (the key is CHash32 of `name`, the path relative to
// the download's root, e.g. "Character/etc2/hi/cp0303_b04a.asf") and SLZ decompressed. `source`
// is the file's bytes (from the 3.7.0 download, the APK's assetpack, or a file already decoded:
// then returned as it is).
bool decode_game_file(const std::string& name, const Bytes& source, Bytes& out, std::string* err = nullptr);
// The game path of a local file: the part of `path` from its first component that is one of the
// download's top-level folders (Character/, Motion/, Weapon/, BG/, ...), or "" when none is.
std::string game_name_of(const std::string& path);

// Walk the chunks from `pos` (each chunk's +0xc is the offset to the next; 0 ends the walk).
template <class F>
void walk_chunks(const Bytes& d, size_t pos, size_t end, F&& f) {
    while (pos + 16 <= end && pos + 16 <= d.size()) {
        uint32_t next = rd32(&d[pos + 0xc]);
        if (!f(pos)) return;
        if (next == 0) return;
        pos += next;
    }
}

}  // namespace soa::aff
