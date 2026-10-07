# `lib_zlib`: zlib 1.2.5: the host library at the inflate / deflate API

A subsystem of the native rebuild (port/PLAN.md task 6). The workflow (decompile, types, natives,
tests, Ghidra types): port/src/native/README.md "Per-subsystem workflow".

- Scope: the demangled-name patterns in [`port/decomp/lib_zlib/scope.txt`](../../../decomp/lib_zlib/scope.txt).
- Decompiles and the function list: [`port/decomp/lib_zlib/`](../../../decomp/lib_zlib/) (`symbols.tsv`; `tools/decomp.sh --into lib_zlib/<topic>`).
- Types: [`lib_zlib_layout.h`](lib_zlib_layout.h); for Ghidra, `tools/subsystem.py export-types lib_zlib` -> `port/decomp/lib_zlib/types.json`.
- Build settings of its own (a host library, a definition): none; a `subsystem.cmake` here would hold them (port/CMakeLists.txt includes it).

## Types (classes with their methods attached)

| Struct | Guest size | Found from | Status |
|---|---|---|---|
| `ZStream` (`z_stream`) | 0x70 | zlib.h (LP64); `AskaUncompress*` pass `sizeof` 0x70 to `inflateInit2_` | typed; crosses through a host twin |

## Natives

3 functions: `inflateInit2_`, `inflate`, `inflateEnd`, the whole API the game calls (from the
`AskaUncompress*` wrappers; `AskaUncompressGzip` for SLZ codec-5 chunks, `AskaUncompressGzipStrict` from
`BridgeNotify::OnReceive`).

| Guest symbol | File | Differential tests | Live check |
|---|---|---|---|
| `inflateInit2_`, `inflate`, `inflateEnd` | `lib_zlib_api.cpp` | `lib_zlib/download-chunks`, `lib_zlib/synthetic`, `lib_zlib/live-check` | 0 mismatches (login 19+, battle 985+, gacha 784+, story 1,366+ checks) |

**Not bound:** the compressors (`deflate*`, `AskaCompress*`): nothing in the game calls them (no BL, no
address taken), so they stay guest code. That settles the version question: decompression is identical
across zlib versions (the tests compare every byte, the results, positions, totals, checksums and error
messages with vcpkg's 1.3.2), while compression bytes would differ between 1.2.5 and 1.3.2 but are never
produced.

**The twin:** the game's `z_stream` lives on the wrappers' stacks with the guest's layout, which on Windows
differs from the host's (`uLong` is 32-bit there). So `inflateInit2_` makes a host `z_stream` per stream
and keeps it in the guest's `state` field (the library's private pointer, never read by the game); each
call copies the public fields across (in: next_in / avail_in / next_out / avail_out / totals / adler; out:
the same plus msg and data_type). A `state` that isn't the stream's own twin (an uninitialized stack slot,
a stream ended) is `Z_STREAM_ERROR`, as zlib's own check. One code path on every host.

**1.2.5's API, kept:** `inflateInit2_` checks the version's first digit and the guest's `sizeof(z_stream)`
(0x70), and sets `adler` to 1 for every stream (1.2.9+ leave it alone for raw deflate).

**Differential tests:** SLZ codec-5 (raw deflate) chunks of downloaded `UI/etc2` scenes, inflated as
`AskaUncompressGzip` does (one `Z_FINISH` call, the output size as the input size; the stored size;
1000-byte steps); synthetic raw / zlib / gzip / auto-detected streams of levels 0-9, 0 to 64 KB, whole, in
steps, short output, damaged, cut, wrong window bits; the version and size checks.

**Live check:** `--live-check lib_zlib`: a shadow guest `z_stream` per stream in the guest's zlib 1.2.5,
the same input, its output into a copy of the buffer; results, positions, totals, adler, messages and
bytes compared.

**Guest time:** 214 samples (0.1%) before, 0 after.

## Dependencies

None (a leaf).
