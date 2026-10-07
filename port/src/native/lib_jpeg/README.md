# `lib_jpeg`: IJG libjpeg 9b: the host library at Aska::JpegUtil

A subsystem of the native rebuild (port/PLAN.md task 6). The workflow (decompile, types, natives,
tests, Ghidra types): port/src/native/README.md "Per-subsystem workflow".

- Scope: the demangled-name patterns in [`port/decomp/lib_jpeg/scope.txt`](../../../decomp/lib_jpeg/scope.txt).
- Decompiles and the function list: [`port/decomp/lib_jpeg/`](../../../decomp/lib_jpeg/) (`symbols.tsv`; `tools/decomp.sh --into lib_jpeg/<topic>`).
- Types: [`lib_jpeg_layout.h`](lib_jpeg_layout.h); for Ghidra, `tools/subsystem.py export-types lib_jpeg` -> `port/decomp/lib_jpeg/types.json`.
- Build settings of its own (a host library, a definition): none; a `subsystem.cmake` here would hold them (port/CMakeLists.txt includes it).

## Types (classes with their methods attached)

| Class | Guest size | Found from | Status |
|---|---|---|---|
| `JpegUtil` (`Aska::JpegUtil`) | - (static functions) | the decompile (port/decomp/lib_jpeg/jpeg_util.c) | native |
| `ILineScanner` (`Aska::JpegUtil::ILineScanner`) | 8 (vtable) | `GetInfo + 0x78` calls slot 0 | typed; guest objects, called through the vtable |
| `IAllocator` (`Aska::JpegUtil::IAllocator`) | 8 (vtable) | slots 0 (Malloc) and 1 (Free) | typed; same |

libjpeg's own structs never leave these functions (each has its `jpeg_decompress_struct` on its stack):
the boundary is `Aska::JpegUtil`, not the `jpeg_*` API. (The guest's libjpeg was built with `boolean` =
`unsigned char`: `jpeg_CreateDecompress(.., 90, 0x278)`; the host's layout is its own business.)

## Natives

6 functions:

| Guest symbol | File | Differential tests | Live check |
|---|---|---|---|
| `JpegUtil::GetInfo`, `JpegUtil::GetPlaneInfo`, `JpegUtil::DecodeQuantCoef` | `lib_jpeg_util.cpp` (+ the check, `lib_jpeg_api.cpp`) | `lib_jpeg/download`, `lib_jpeg/synthetic`, `lib_jpeg/live-check` | 0 mismatches (battle 1+, story 16+ checks: the GPU-decoded JPEG backgrounds) |
| `JpegUtil::Decode`, `JpegUtil::DecodeYuv` | same | same | in its test (the flows don't reach them) |
| `glj_ilog` | `lib_jpeg_util.cpp` | `lib_jpeg/ilog-and-tables` | - (pure) |

The game's own `FnGrayscaleLineReader` / `FnRGBXLineReader` / `FnCMYKLineReader` / `FnASKAEngineAllocator`
stay guest code (called through their vtables with `guest_call`).

**The host library is IJG libjpeg 9b, the game's version** (`cmake/libjpeg9/`, now pinned to 9b instead of
9e; `soa::jpeg9`, also used by tools/aif2png).

**Differential tests:** the download's JPEG textures (all 431 are baseline, SOF0) and host-encoded ones
(grayscale, YCbCr 4:4:4 / 4:2:2 / 4:2:0, CMYK, arithmetic coding, restart markers): every function, with
outputs left out, `Decode` through the game's scanners and allocator (whole and clipped); damaged inputs
(`GetInfo`'s checks); `glj_ilog` over 0..70000 and every bit length; the IDCT scale table.

**Progressive JPEGs are not compared:** under the JIT the guest's libjpeg ends with zero coefficients for
them (all of `DecodeQuantCoef`, `DecodeYuv`, `Decode`), while the host's decodes them; the game has none,
so only their headers are compared (a lead for a JIT check, not a game behaviour).

**Live check:** `--live-check lib_jpeg`: the functions are stateless, so the guest original runs on the same
input into scratch copies of every output (rows, planes, coefficients, tables, header values) and they are
compared.

**Guest time:** 73 samples (0.0%) before, 0 after.

## Dependencies

None (a leaf). Callers: `Aska::TextureUtil::CreateTextureFromJpeg` / `CreateCubeTextureFromJpeg` (GetInfo,
Decode) and `Aska::DecodeJpegObject::DecodeCpu*` (GetInfo, GetPlaneInfo, DecodeQuantCoef, DecodeYuv).

## RE notes

- **`GetInfo + 0x78`** (a local function; `GetInfo` and `Decode` are its wrappers): needs `FF D8` (else
  -1020); an error manager whose `error_exit` stores `msg_code` in `*client_data` and returns (no longjmp),
  checked after each call; outputs the size, `out_color_space - 1` (or -1), `progressive_mode`, `arith_code`;
  with a destination: the scanner by output color space (CMYK, RGB, grayscale; others: nothing), a
  scanline buffer of `output_components * output_width` from the allocator, rows clipped to
  min(width, image_width) x min(height, image_height). **Guest leak:** for an output color space without a
  scanner, or a failed Malloc, it returns 0 without `jpeg_destroy_decompress`; the native frees it
  (unobservable).
- **`GetPlaneInfo`, `DecodeQuantCoef`, `DecodeYuv`** use the default error manager (an error exits, as in
  the guest). Per component: plane width `ceil(W / (max_h * 8)) * 8 * h`, height `v * ceil(H / (max_v * 8)) * 8`,
  shifts `ilog(max) - ilog(f)`; the third output divides the vertical block rows by the *horizontal* shift
  (kept). `DecodeQuantCoef`: tables x `GLJ_REAL_IDCT8X8_SCALES` (float), coefficients block row band by band
  via `access_virt_barray`, components at the guest's padded offsets. `DecodeYuv`: raw data out, no fancy
  upsampling, `JDCT_ISLOW`, 16 rows per call per component (>> its vertical shift).
