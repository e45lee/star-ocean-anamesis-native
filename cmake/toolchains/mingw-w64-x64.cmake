# Cross-compiling for Windows x64 with the distribution's MinGW-w64 GCC (Ubuntu / Debian:
# g++-mingw-w64-x86-64-posix; README.md "Windows"): port/PLAN.md 5b. Used as vcpkg's chainloaded
# toolchain by scripts/build.sh --windows (build-win/). The "-posix" compilers: GCC's posix thread
# model (winpthreads), which std::thread / std::mutex need; the distribution's default alternative is
# the win32 model.
set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_PROCESSOR x86_64)
set(_soa_mingw x86_64-w64-mingw32)
find_program(CMAKE_C_COMPILER ${_soa_mingw}-gcc-posix REQUIRED)
find_program(CMAKE_CXX_COMPILER ${_soa_mingw}-g++-posix REQUIRED)
find_program(CMAKE_RC_COMPILER ${_soa_mingw}-windres REQUIRED)
find_program(CMAKE_AR ${_soa_mingw}-gcc-ar-posix REQUIRED)
find_program(CMAKE_RANLIB ${_soa_mingw}-gcc-ranlib-posix REQUIRED)
# One self-contained .exe: libstdc++, libgcc and winpthreads linked in (only Windows' own DLLs, the
# C runtime msvcrt.dll included, stay dynamic), so it runs from anywhere, WSL interop included.
set(CMAKE_EXE_LINKER_FLAGS_INIT "-static")
# The target's own files (common/CMakeLists.txt finds MinGW's binmode.o there). Packages come from
# vcpkg's installed tree, which its toolchain adds to the search paths.
set(SOA_MINGW_SYSROOT "/usr/${_soa_mingw}" CACHE PATH "")
