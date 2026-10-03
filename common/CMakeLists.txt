# Shared by the parts (none depends on another for these):
#
# soa_env: header-only (include/soa/env.h), the programs' environment rule and the table of the
# SOA_* variables that are flags now (docs/environment.md); include/soa/paths.h, the programs'
# default data dirs (Linux ~/.local/share/..., Windows %LOCALAPPDATA%\soa\...). Every library links it: the runtime,
# the server, the web view (none depends on another for it).
#   soa_env_tests  its unit tests (build/common/soa_env_tests); tests/env_removed.sh checks the
#                  programs' warnings.
add_library(soa_env INTERFACE)
target_include_directories(soa_env INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(soa_env_tests ${CMAKE_CURRENT_SOURCE_DIR}/tests/env_tests.cpp ${CMAKE_CURRENT_SOURCE_DIR}/tests/paths_tests.cpp)
target_link_libraries(soa_env_tests PRIVATE soa_env soa_compat)  # (soa_compat: setenv on Windows)

# soa_compat: what more than one part needs to build for both Linux and Windows (port/PLAN.md 5b,
# W); linked by the server's and the runtime's targets.
#   include/soa/sock.h  host TCP sockets (BSD / Winsock): soa-server's wire layer (server/net) and
#                       platform370's HTTP client
# On Windows (MinGW-w64) also: win32/posix_compat.h force-included into every source of a target
# that links it (the POSIX spellings MinGW lacks; src/posix_compat_win32.cpp), Winsock (ws2_32),
# and binary stdio (MinGW's binmode.o: fopen "r" / open() read bytes, as on Linux; our code never
# asks for text mode).
add_library(soa_compat STATIC ${CMAKE_CURRENT_SOURCE_DIR}/src/sock.cpp
            $<$<PLATFORM_ID:Windows>:${CMAKE_CURRENT_SOURCE_DIR}/src/posix_compat_win32.cpp>)
target_include_directories(soa_compat PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_options(soa_compat PRIVATE -Wall -Wno-unused-parameter)
if(WIN32)
  target_compile_options(soa_compat PUBLIC "SHELL:-include ${CMAKE_CURRENT_SOURCE_DIR}/win32/posix_compat.h")
  # <windows.h> without min/max macros and the rarely used APIs; 64-bit off_t (fseeko / ftello);
  # MinGW's localtime_r / gmtime_r.
  target_compile_definitions(soa_compat PUBLIC NOMINMAX WIN32_LEAN_AND_MEAN _FILE_OFFSET_BITS=64 _POSIX_THREAD_SAFE_FUNCTIONS)
  find_file(SOA_MINGW_BINMODE binmode.o PATHS ${SOA_MINGW_SYSROOT}/lib REQUIRED NO_DEFAULT_PATH)
  target_link_libraries(soa_compat PUBLIC ${SOA_MINGW_BINMODE} ws2_32)
endif()
