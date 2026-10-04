#pragma once
// zstd: the game's copy (1.3.4) replaced by the host's at the decompression API the game calls (only
// Aska::_DecodeMain<*, 7>::Decode does, through the Aska::*ZSTD* wrappers: 4-byte tail calls, so
// the ZSTD_* functions themselves are the natives). These functions, with the guest's signatures, are
// the natives; the differential tests call them directly. README.md has the list and the rules.
#include "native/common/lockstep.h"
#include "native/lib_zstd/lib_zstd_layout.h"

namespace soa::native::lib_zstd {

void* create_dstream();
u64 free_dstream(void* zds);
u64 init_dstream(void* zds);
u64 decompress_stream(void* zds, ZSTDOutBuffer* out, ZSTDInBuffer* in);
u64 decompress(void* dst, u64 capacity, const void* src, u64 size);
u32 is_error(u64 code);
u64 dstream_in_size();
u64 dstream_out_size();

// The live check (--live-check lib_zstd) and, for its test, its originals (as lib_vorbis_api.h).
live::Lockstep& lockstep();
void use_originals(u64 (*sym)(const char*));

}  // namespace soa::native::lib_zstd
