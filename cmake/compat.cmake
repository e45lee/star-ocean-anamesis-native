# soa_compat (compat/): what more than one part needs to build for both Linux and Windows
# (port/PLAN.md 5b, W). Linked by the server's and the runtime's targets.
#   compat/include/soa_compat/sock.h  host TCP sockets (BSD / Winsock): soa-server's wire layer,
#                                     platform370's HTTP client
# On Windows (MinGW-w64) also: compat/win32/posix_compat.h force-included into every source of a
# target that links it (the POSIX spellings MinGW lacks) and its functions, Winsock (ws2_32), and
# binary stdio (MinGW's binmode.o: fopen "r" / open() read bytes, as on Linux; our code never asks
# for text mode).
set(_soa_compat_dir ${CMAKE_CURRENT_LIST_DIR}/../compat)
cmake_path(NORMAL_PATH _soa_compat_dir)
add_library(soa_compat STATIC ${_soa_compat_dir}/src/sock.cpp $<$<PLATFORM_ID:Windows>:${_soa_compat_dir}/src/posix_compat_win32.cpp>)
target_include_directories(soa_compat PUBLIC ${_soa_compat_dir}/include)
target_compile_options(soa_compat PRIVATE -Wall -Wno-unused-parameter)
if(WIN32)
  target_compile_options(soa_compat PUBLIC "SHELL:-include ${_soa_compat_dir}/win32/posix_compat.h")
  # <windows.h> without min/max macros and the rarely used APIs; 64-bit off_t (fseeko / ftello);
  # MinGW's localtime_r / gmtime_r.
  target_compile_definitions(soa_compat PUBLIC NOMINMAX WIN32_LEAN_AND_MEAN _FILE_OFFSET_BITS=64 _POSIX_THREAD_SAFE_FUNCTIONS)
  find_file(SOA_MINGW_BINMODE binmode.o PATHS ${SOA_MINGW_SYSROOT}/lib REQUIRED NO_DEFAULT_PATH)
  target_link_libraries(soa_compat PUBLIC ${SOA_MINGW_BINMODE} ws2_32)
endif()
