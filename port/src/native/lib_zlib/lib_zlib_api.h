#pragma once
// zlib: the game's copy (1.2.5) replaced by the host's at the inflate API the game calls (only the
// AskaUncompress* wrappers do; port/decomp/lib_zlib/aska_compress.c). The compressors (deflate*,
// AskaCompress*) have no caller in the game and stay guest code. These functions, with the guest's
// signatures, are the natives; the differential tests call them directly. README.md has the rules.
#include "native/common/lockstep.h"
#include "native/lib_zlib/lib_zlib_layout.h"

namespace soa::native::lib_zlib {

s32 inflate_init2(ZStream* strm, s32 window_bits, const char* version, s32 stream_size);
s32 inflate_(ZStream* strm, s32 flush);
s32 inflate_end(ZStream* strm);

// The live check (--live-check lib_zlib) and, for its test, its originals (as lib_vorbis_api.h).
live::Lockstep& lockstep();
void use_originals(u64 (*sym)(const char*));

}  // namespace soa::native::lib_zlib
