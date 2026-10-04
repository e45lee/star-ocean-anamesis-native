#pragma once
// libogg + libVorbis: the game's copies (libogg 1.3.x, libVorbis 1.3.5) replaced by the host's at the
// ogg_* / vorbis_* API the game calls (only Aska::AskaOGG does: port/decomp/lib_vorbis/aska_ogg.c).
// The natives are these functions, with the guest's (LP64) signatures; the differential tests call
// them directly. README.md has the list and the rules.
#include "native/common/lockstep.h"
#include "native/lib_vorbis/lib_vorbis_layout.h"

namespace soa::native::lib_vorbis {

// libogg
void ogg_memory_hook_(u64 malloc_fn, u64 calloc_fn, u64 realloc_fn, u64 free_fn);
s32 sync_init(OggSyncState* oy);
s32 sync_clear(OggSyncState* oy);
s32 sync_reset(OggSyncState* oy);
char* sync_buffer(OggSyncState* oy, s64 size);
s32 sync_wrote(OggSyncState* oy, s64 bytes);
s32 sync_pageout(OggSyncState* oy, OggPage* og);
s32 page_eos(const OggPage* og);
s32 page_serialno(const OggPage* og);
s32 stream_init(OggStreamState* os, s32 serialno);
s32 stream_clear(OggStreamState* os);
s32 stream_reset(OggStreamState* os);
s32 stream_pagein(OggStreamState* os, OggPage* og);
s32 stream_packetout(OggStreamState* os, OggPacket* op);
s32 stream_packetpeek(OggStreamState* os, OggPacket* op);
// libVorbis (the decoder side)
void info_init(VorbisInfo* vi);
void info_clear(VorbisInfo* vi);
s32 info_blocksize(VorbisInfo* vi, s32 zo);
void comment_init(VorbisComment* vc);
void comment_clear(VorbisComment* vc);
s32 synthesis_headerin(VorbisInfo* vi, VorbisComment* vc, OggPacket* op);
s32 synthesis_init(VorbisDspState* vd, VorbisInfo* vi);
void dsp_clear(VorbisDspState* vd);
s32 block_init(VorbisDspState* vd, VorbisBlock* vb);
s32 block_clear(VorbisBlock* vb);
s32 synthesis(VorbisBlock* vb, OggPacket* op);
s32 synthesis_trackonly(VorbisBlock* vb, OggPacket* op);
s32 synthesis_blockin(VorbisDspState* vd, VorbisBlock* vb);
s32 synthesis_pcmout(VorbisDspState* vd, float*** pcm);
s32 synthesis_read(VorbisDspState* vd, s32 samples);
s32 synthesis_restart(VorbisDspState* vd);
s64 packet_blocksize(VorbisInfo* vi, OggPacket* op);

// The live check (--live-check lib_vorbis) and, for its test, the originals it runs: by default the
// hooks' trampolines; use_originals(sym) sets them to sym(symbol) (in --selftest the guest symbols
// themselves, nothing being installed), nullptr back to none.
live::Lockstep& lockstep();
void use_originals(u64 (*sym)(const char*));

}  // namespace soa::native::lib_vorbis
