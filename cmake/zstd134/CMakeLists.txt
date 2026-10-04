# zstd 1.3.4 (the library: common, decompress, compress; no legacy formats, no multithreading),
# static, from the source tarball FetchContent unpacks (cmake/deps.cmake: ZSTD134_SOURCE_DIR). The
# game bundles 1.3.4 (ZSTD_versionNumber 10304), and the port's lib_zstd natives must agree with it
# byte for byte, error results and the output of failing frames included, which vcpkg's 1.5 doesn't
# (port/src/native/lib_zstd/README.md). As the guest's: no ZSTDv0x legacy decoders, no ZDICT / ZSTDMT.
#
# Target: soa::zstd134 (STATIC), zstd.h on its include path. Only soa links it; vcpkg's zstd stays for
# tools/aif2png.
set(_zstd134_sources
  common/entropy_common.c common/error_private.c common/fse_decompress.c common/pool.c
  common/threading.c common/xxhash.c common/zstd_common.c
  decompress/huf_decompress.c decompress/zstd_decompress.c
  compress/fse_compress.c compress/huf_compress.c compress/zstd_compress.c compress/zstd_double_fast.c
  compress/zstd_fast.c compress/zstd_lazy.c compress/zstd_ldm.c compress/zstd_opt.c)
list(TRANSFORM _zstd134_sources PREPEND ${ZSTD134_SOURCE_DIR}/lib/)
add_library(zstd134 STATIC ${_zstd134_sources})
add_library(soa::zstd134 ALIAS zstd134)
target_include_directories(zstd134 BEFORE PUBLIC ${ZSTD134_SOURCE_DIR}/lib)
target_include_directories(zstd134 PRIVATE ${ZSTD134_SOURCE_DIR}/lib/common)
target_compile_definitions(zstd134 PRIVATE ZSTD_LEGACY_SUPPORT=0 XXH_NAMESPACE=ZSTD_)
set_target_properties(zstd134 PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_compile_options(zstd134 PRIVATE $<$<C_COMPILER_ID:GNU,Clang>:-w>)
