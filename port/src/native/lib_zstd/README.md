# `lib_zstd`: zstd: the host library at the ZSTD_* API

A subsystem of the native rebuild (port/PLAN.md task 6). The workflow (decompile, types, natives,
tests, Ghidra types): port/src/native/README.md "Per-subsystem workflow".

- Scope: the demangled-name patterns in [`port/decomp/lib_zstd/scope.txt`](../../../decomp/lib_zstd/scope.txt).
- Decompiles and the function list: [`port/decomp/lib_zstd/`](../../../decomp/lib_zstd/) (`symbols.tsv`; `tools/decomp.sh --into lib_zstd/<topic>`).
- Types: [`lib_zstd_layout.h`](lib_zstd_layout.h); for Ghidra, `tools/subsystem.py export-types lib_zstd` -> `port/decomp/lib_zstd/types.json`.
- Build settings of its own (a host library, a definition): none; a `subsystem.cmake` here would hold them (port/CMakeLists.txt includes it).

## Types (classes with their methods attached)

| Struct | Guest size | Found from | Status |
|---|---|---|---|
| `ZSTDInBuffer` (`Aska::ZSTDInBuffer`, zstd's `ZSTD_inBuffer`) | 0x18 | `Aska::DecompressStreamZSTD`; zstd.h | typed; the host's, same layout everywhere |
| `ZSTDOutBuffer` (`Aska::ZSTDOutBuffer`, `ZSTD_outBuffer`) | 0x18 | same | typed |

The decompression stream (`ZSTD_DStream*`) is opaque to the game: a host object.

## Natives

8 functions: the decompression API the game calls. `Aska::CreateZSTDStream`, `DecompressZSTD` and the
other `Aska::*ZSTD*` wrappers are 4-byte tail calls (too short to hook), so the `ZSTD_*` functions they
branch to are the natives; their only caller is `Aska::_DecodeMain<*, 7>::Decode` (SLZ codec 7,
port/decomp/lib_zstd/decode_main.c).

| Guest symbol | File | Differential tests | Live check |
|---|---|---|---|
| `ZSTD_decompress` | `lib_zstd_api.cpp` | `lib_zstd/download-chunks`, `lib_zstd/synthetic`, `lib_zstd/live-check` | 0 mismatches (login 805+, battle 3,000+, gacha 2,000+, story 5,000+ checks) |
| `ZSTD_createDStream`, `ZSTD_initDStream`, `ZSTD_decompressStream`, `ZSTD_freeDStream` | `lib_zstd_api.cpp` | same | in its test (the streamed path, chunks over 64 KiB, isn't reached by the flows: every asset has 64 KiB chunks) |
| `ZSTD_isError`, `ZSTD_DStreamInSize`, `ZSTD_DStreamOutSize` | `lib_zstd_api.cpp` | `lib_zstd/constants` | - (pure) |

**Not bound:** `ZSTD_compress` / `ZSTD_compressBound` (`Aska::CompressZSTD` / `CompressSizeZSTD`): nothing in
the game calls them; they stay guest code.

**The host library is zstd 1.3.4, the game's version** (`cmake/zstd134/`, `FetchContent` pinned by
SHA-256; `soa::zstd134`), not vcpkg's 1.5.7: the game hands `ZSTD_decompress` the output size as the
input size (each SLZ chunk's stored size also counts a pad byte), so every call ends past the frame with
an error the game ignores, and 1.5 reports another one (`srcSize_wrong`, -72, for 1.3.4's
`prefix_unknown`, -10); 1.5 also leaves other bytes behind in the output of failing frames. With 1.3.4
everything agrees: results, positions, every byte.

**Differential tests:** the SLZ codec-7 chunks of downloaded assets (`Image/etc2`, `Motion`, `Effect`,
`UI/etc2`; test data from `native/common/test_assets.h`) decompressed as `_DecodeMain` does (one-shot
with the output size as the input size, with the stored size, and streamed with in.size = out.size);
synthetic frames of levels 1-19, 1 byte to 150 KB (the streamed path), with and without checksums and
content sizes, one byte longer, a short output, damaged and cut.

**Live check:** `--live-check lib_zstd` (native/common/lockstep.h): every host stream has a guest one
(the guest's `ZSTD_createDStream`); each call runs on both, the guest's into a copy of the output buffer;
results, consumed / produced positions and the bytes compared.

**Guest time:** 1,066 samples (0.4%) before, 0 after.

## Dependencies

None (a leaf). Its caller, `Aska::_DecodeMain` (the SLZ decoder), belongs to a later subsystem.

## RE notes

- `_DecodeMain<*, 7>::Decode(src, dst, size)`: above 64 KiB it streams (`CreateZSTDStream`, `Initialize...`,
  `DecompressStreamZSTD` with in = out = size until it returns 0, `Thread::Switch` between calls, an
  error falls through), then (also below 64 KiB, and after a streaming error) `DecompressZSTD(dst, size,
  src, size)`, whose result is ignored.
- The game's zstd has no legacy (v0.x) decoders, no ZDICT / ZSTDMT; the pinned build likewise
  (`ZSTD_LEGACY_SUPPORT=0`, `XXH_NAMESPACE=ZSTD_` as in zstd's own Makefile).
