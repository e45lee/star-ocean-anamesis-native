# soa_compat: what our code needs to build for Windows (port/PLAN.md 5b, W); compat/win32/. On Linux
# an empty INTERFACE target. On Windows (MinGW-w64): compat/win32/posix_compat.h force-included into
# every source of a target that links it (the POSIX spellings MinGW lacks), its functions, Winsock
# (ws2_32), and binary stdio (MinGW's binmode.o: fopen "r" / open() read bytes, as on Linux; our code
# never asks for text mode). Linked by the server's and the runtime's targets.
if(WIN32)
  add_library(soa_compat STATIC ${CMAKE_CURRENT_LIST_DIR}/../compat/win32/posix_compat.cpp)
  set(_soa_compat_h ${CMAKE_CURRENT_LIST_DIR}/../compat/win32/posix_compat.h)
  cmake_path(NORMAL_PATH _soa_compat_h)
  target_compile_options(soa_compat PUBLIC "SHELL:-include ${_soa_compat_h}")
  # <windows.h> without min/max macros and the rarely used APIs; 64-bit off_t (fseeko / ftello).
  target_compile_definitions(soa_compat PUBLIC NOMINMAX WIN32_LEAN_AND_MEAN _FILE_OFFSET_BITS=64)
  find_file(SOA_MINGW_BINMODE binmode.o PATHS ${CMAKE_FIND_ROOT_PATH} PATH_SUFFIXES lib REQUIRED NO_CMAKE_FIND_ROOT_PATH)
  target_link_libraries(soa_compat PUBLIC ${SOA_MINGW_BINMODE} ws2_32)
else()
  add_library(soa_compat INTERFACE)
endif()
