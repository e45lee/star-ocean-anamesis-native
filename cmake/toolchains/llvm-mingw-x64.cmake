# Cross-compiling for Windows x64 with llvm-mingw (clang, libc++, MinGW-w64 UCRT): port/PLAN.md 5b.
# Used as vcpkg's chainloaded toolchain by scripts/build.sh --windows (build-win/). llvm-mingw's
# root: $SOA_LLVM_MINGW, else ~/tools/llvm-mingw (github.com/mstorsjo/llvm-mingw, the ucrt
# ubuntu-x86_64 release unpacked there).
set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_PROCESSOR x86_64)
if(DEFINED ENV{SOA_LLVM_MINGW})
  set(_soa_llvm_mingw "$ENV{SOA_LLVM_MINGW}")
else()
  set(_soa_llvm_mingw "$ENV{HOME}/tools/llvm-mingw")
endif()
if(NOT EXISTS "${_soa_llvm_mingw}/bin/x86_64-w64-mingw32-clang++")
  message(FATAL_ERROR "llvm-mingw not found at ${_soa_llvm_mingw}: set SOA_LLVM_MINGW (README.md, \"Windows\")")
endif()
set(CMAKE_C_COMPILER "${_soa_llvm_mingw}/bin/x86_64-w64-mingw32-clang")
set(CMAKE_CXX_COMPILER "${_soa_llvm_mingw}/bin/x86_64-w64-mingw32-clang++")
set(CMAKE_RC_COMPILER "${_soa_llvm_mingw}/bin/x86_64-w64-mingw32-windres")
set(CMAKE_AR "${_soa_llvm_mingw}/bin/llvm-ar" CACHE FILEPATH "")
set(CMAKE_RANLIB "${_soa_llvm_mingw}/bin/llvm-ranlib" CACHE FILEPATH "")
# One self-contained .exe: libc++, libunwind and winpthreads linked in (only Windows' own DLLs,
# UCRT included, stay dynamic), so it runs from anywhere, WSL interop included.
set(CMAKE_EXE_LINKER_FLAGS_INIT "-static")
# The target's own files (common/CMakeLists.txt finds MinGW's binmode.o there). Packages come from
# vcpkg's installed tree, which its toolchain adds to the search paths.
set(SOA_MINGW_SYSROOT "${_soa_llvm_mingw}/x86_64-w64-mingw32" CACHE PATH "")
