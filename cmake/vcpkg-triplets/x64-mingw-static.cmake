# The Windows triplet (port/PLAN.md 5b, W): MinGW-w64, static libraries, release builds only, built by
# llvm-mingw's clang. vcpkg's own mingw toolchain (scripts/toolchains/mingw.cmake) finds the compilers
# as x86_64-w64-mingw32-gcc/g++ on PATH: scripts/build.sh --windows puts llvm-mingw's bin/ (whose
# x86_64-w64-mingw32-gcc/g++ are clang wrappers) first on PATH, hence the PATH passthrough.
# Overrides vcpkg's community triplet of the same name (which builds debug libraries too and lacks
# the sqlite3 options below).
set(VCPKG_TARGET_ARCHITECTURE x64)
set(VCPKG_CRT_LINKAGE dynamic)
set(VCPKG_LIBRARY_LINKAGE static)
set(VCPKG_CMAKE_SYSTEM_NAME MinGW)
set(VCPKG_BUILD_TYPE release)
set(VCPKG_ENV_PASSTHROUGH PATH)

# sqlite3: the same compile options as on Linux (x64-linux.cmake, which explains them): the served
# master's bytes, and so the CDN version ids, must not depend on the platform.
if(PORT STREQUAL "sqlite3")
  set(_soa_sqlite_defs
    SQLITE_SECURE_DELETE SQLITE_LIKE_DOESNT_MATCH_BLOBS SQLITE_USE_URI=1 SQLITE_SOUNDEX
    SQLITE_MAX_VARIABLE_NUMBER=250000 SQLITE_MAX_DEFAULT_PAGE_SIZE=32768 SQLITE_MAX_SCHEMA_RETRY=25
    SQLITE_ENABLE_DBSTAT_VTAB SQLITE_ENABLE_FTS3
    SQLITE_ENABLE_FTS3_PARENTHESIS SQLITE_ENABLE_FTS3_TOKENIZER SQLITE_ENABLE_FTS4 SQLITE_ENABLE_FTS5
    SQLITE_ENABLE_MATH_FUNCTIONS SQLITE_ENABLE_PREUPDATE_HOOK SQLITE_ENABLE_RTREE SQLITE_ENABLE_SESSION
    SQLITE_ENABLE_STMTVTAB SQLITE_ENABLE_UPDATE_DELETE_LIMIT
    SQLITE_ENABLE_LOAD_EXTENSION SQLITE_HAVE_ISNAN)
  list(TRANSFORM _soa_sqlite_defs PREPEND "-D")
  list(JOIN _soa_sqlite_defs " " _soa_sqlite_defs)
  set(VCPKG_C_FLAGS "${_soa_sqlite_defs}")
  set(VCPKG_CXX_FLAGS "${_soa_sqlite_defs}")
endif()

# litehtml 0.10 (our overlay port, cmake/vcpkg-ports/litehtml): el_font.cpp calls atoi without
# <cstdlib>, which glibc's libstdc++ includes transitively and llvm-mingw's libc++ doesn't. Kept
# here, not as a port patch, so the Linux build's port hash doesn't change.
if(PORT STREQUAL "litehtml")
  set(VCPKG_C_FLAGS "")  # (vcpkg_cmake_configure wants both or neither)
  set(VCPKG_CXX_FLAGS "-include cstdlib")
endif()
