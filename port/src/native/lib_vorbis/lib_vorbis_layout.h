// lib_vorbis_layout.h: the guest data layouts of the `lib_vorbis` subsystem (libVorbis 1.3.5 + libogg: the host libraries at the ogg_* / vorbis_* API).
//
// Types first (port/PLAN.md task 6): every guest class or struct this subsystem's natives touch is
// recovered here before the code that uses it, as a C++ class with the guest's layout byte for byte
// and the guest's methods attached as members (not a struct + free functions):
//   - fields at the guest's offsets, named after their use (m_hp); unknown bytes as named padding
//     (u8 unk_0c[4]), never offset arithmetic in the natives;
//   - a static_assert per known field offset and one for sizeof, so a wrong guess fails the build;
//   - a comment naming where the layout was read (constructor, decompile in port/decomp/lib_vorbis/).
// Natives are these members (this->m_hp), never *(T*)(p + off). Keep the classes standard-layout (no
// C++ virtual, no non-static members of reference type), so offsetof works. The guest is AArch64 LP64; the
// host (x86-64 / AArch64) has the same sizes and alignments for these plain types.
// `tools/subsystem.py export-types lib_vorbis` turns the structs into port/decomp/lib_vorbis/types.json for Ghidra.
#ifndef SOA_NATIVE_LIB_VORBIS_LAYOUT_H
#define SOA_NATIVE_LIB_VORBIS_LAYOUT_H

#include <cstddef>
#include <cstdint>

namespace soa::native::lib_vorbis {

using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using s8 = std::int8_t;
using s16 = std::int16_t;
using s32 = std::int32_t;
using s64 = std::int64_t;

// The library structs as the guest (AArch64 LP64, libogg 1.3.x + libVorbis 1.3.5) lays them out.
// Aska::AskaOGG (the audio subsystem's class; port/decomp/lib_vorbis/aska_ogg.c) embeds one of each in
// its decode context: ogg_sync_state at +0x000, ogg_stream_state +0x020, ogg_page +0x1b8, ogg_packet
// +0x1d8, vorbis_info +0x208, vorbis_comment +0x240, vorbis_dsp_state +0x260, vorbis_block +0x2f0
// (its own fields from +0x3b0). The natives keep the host library's structs in place, inside those
// guest blocks (the host's are never larger: only `long` differs, 32-bit on Windows), so of these
// layouts only what the game reads must agree (the static_asserts in lib_vorbis_api.cpp):
//   ogg_page.header (+0x00; AskaOGG reads header[5], the page flags), vorbis_info.channels (+0x04) and
//   .rate (+0x08, read as a 32-bit int), and ogg_packet.granulepos (+0x20) -- which differs on
//   Windows, so every ogg_packet crosses as OggPacket below, converted.

// ogg_packet: a packet handed out by ogg_stream_packetout / packetpeek and into vorbis_synthesis*.
struct OggPacket {
    u8* packet;      // 0x00
    s64 bytes;       // 0x08
    s64 b_o_s;       // 0x10
    s64 e_o_s;       // 0x18
    s64 granulepos;  // 0x20: read by Aska::AskaOGG::Decode_LoopStart
    s64 packetno;    // 0x28
};
static_assert(offsetof(OggPacket, bytes) == 0x08);
static_assert(offsetof(OggPacket, granulepos) == 0x20);
static_assert(sizeof(OggPacket) == 0x30);

// ogg_page: header / body pointers into the sync buffer (ogg_sync_pageout).
struct OggPage {
    u8* header;      // 0x00: header[5] = the page's flags (bit 2: end of stream)
    s64 header_len;  // 0x08
    u8* body;        // 0x10
    s64 body_len;    // 0x18
};
static_assert(offsetof(OggPage, body) == 0x10);
static_assert(sizeof(OggPage) == 0x20);

// vorbis_info: the stream's parameters (vorbis_synthesis_headerin fills them).
struct VorbisInfo {
    s32 version;          // 0x00
    s32 channels;         // 0x04: read by AskaOGG (interleaving, byte counts)
    s64 rate;             // 0x08: read by AskaOGG as a 32-bit int (frame sample counts)
    s64 bitrate_upper;    // 0x10
    s64 bitrate_nominal;  // 0x18
    s64 bitrate_lower;    // 0x20
    s64 bitrate_window;   // 0x28
    void* codec_setup;    // 0x30: the library's private codec_setup_info
};
static_assert(offsetof(VorbisInfo, channels) == 0x04);
static_assert(offsetof(VorbisInfo, rate) == 0x08);
static_assert(sizeof(VorbisInfo) == 0x38);

// The opaque states: only their guest sizes matter (the host's live inside, and a live check's shadow
// of the guest library is this big).
struct OggSyncState {      // ogg_sync_state
    u8 opaque[0x20];
};
struct OggStreamState {    // ogg_stream_state
    u8 opaque[0x198];
};
struct VorbisComment {     // vorbis_comment
    u8 opaque[0x20];
};
struct VorbisDspState {    // vorbis_dsp_state
    u8 opaque[0x90];
};
struct VorbisBlock {       // vorbis_block
    u8 opaque[0xc0];
};
static_assert(sizeof(OggSyncState) == 0x20 && sizeof(OggStreamState) == 0x198 && sizeof(VorbisComment) == 0x20);
static_assert(sizeof(VorbisDspState) == 0x90 && sizeof(VorbisBlock) == 0xc0);

}  // namespace soa::native::lib_vorbis

#endif  // SOA_NATIVE_LIB_VORBIS_LAYOUT_H
