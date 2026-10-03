# The default Linux triplet (static libraries), release builds only: the dependencies are built once
# per binary-cache key, and a Debug build of the repository links the release libraries.
set(VCPKG_TARGET_ARCHITECTURE x64)
set(VCPKG_CRT_LINKAGE dynamic)
set(VCPKG_LIBRARY_LINKAGE static)
set(VCPKG_CMAKE_SYSTEM_NAME Linux)
set(VCPKG_BUILD_TYPE release)

# sqlite3 (pinned to 3.45.1 in vcpkg.json): the compile options of Ubuntu 24.04's libsqlite3 3.45.1,
# which the port and the server linked before vcpkg (`PRAGMA compile_options` of the system library
# minus vcpkg's own). SECURE_DELETE matters most: it zeroes freed space, so the server's VACUUMed
# served master (server/src/cdn.cpp make_served_master) is byte-identical to the one the system
# library wrote, and so are the CDN version ids derived from its SHA-1. The rest keeps SQL behaviour
# (LIKE on blobs, limits, URIs, the FTS / R-tree / math functions) as it was.
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
