# The one build of the repository: the JIT host runtime (runtime/), the 3.7.0 platform layer
# (platform370/), the local game server (server/), the desktop port (port/), the 3.7.0 emulator
# (emulator/), the 3.8.0 viewer (emulator-viewer/) and the host tools (tools/aif2png).
#
#   scripts/build.sh                    # bootstraps vcpkg (.vcpkg/) if needed, configures, builds
# or by hand, with vcpkg at $VCPKG_ROOT or .vcpkg/ (scripts/vcpkg-bootstrap.sh):
#   cmake -S . -B build                 # RelWithDebInfo unless -DCMAKE_BUILD_TYPE=...
#   cmake --build build -j8
#
# Dependencies (cmake/deps.cmake; README.md, "Setup"): vcpkg in manifest mode (vcpkg.json), the
# first configure builds them into build/vcpkg_installed/; dynarmic and IJG libjpeg 9 by CMake
# FetchContent (build/_deps/); Mesa's libEGL/libGLESv2 from the system.
#
# Outputs:
#   build/port/soa                  the port (port/README.md)
#   build/server/soa-server         the standalone local server (server/README.md)
#   build/emulator/soa-emu          the unmodified 3.7.0 client (emulator/README.md)
#   build/emulator-viewer/soa-viewer the unmodified offline 3.8.0 client (emulator-viewer/README.md)
#   build/runtime/soaruntime_tests  the runtime's extension-point tests (runtime/README.md)
#   build/platform370/libsoaplatform370.a  the 3.7.0 platform layer soa-emu and soa link (platform370/README.md)
#   build/tools/aif2png/aif2png     the AIF -> PNG converter (tools/aif2png)
#
# One part: `cmake --build build --target soa` (or soa-server, soa-emu, soa-viewer,
# soaruntime_tests, aif2png), or turn parts off at configure time with the options below.
#
# The subdirectories' CMakeLists.txt are not roots: they use the settings defined here.
cmake_minimum_required(VERSION 3.28)  # FetchContent_Declare(... EXCLUDE_FROM_ALL)

# vcpkg's toolchain (before project()): $VCPKG_ROOT, else the repository's .vcpkg/ (an untracked
# clone made by scripts/vcpkg-bootstrap.sh). An explicit -DCMAKE_TOOLCHAIN_FILE wins.
if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  if(DEFINED ENV{VCPKG_ROOT} AND EXISTS "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE FILEPATH "")
  elseif(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/.vcpkg/scripts/buildsystems/vcpkg.cmake")
    set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/.vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE FILEPATH "")
  else()
    message(FATAL_ERROR "vcpkg not found: run scripts/vcpkg-bootstrap.sh (clones it into .vcpkg/), "
                        "set VCPKG_ROOT, or pass -DCMAKE_TOOLCHAIN_FILE=<vcpkg>/scripts/buildsystems/vcpkg.cmake")
  endif()
endif()
# Our x64-linux triplet: vcpkg's (static libraries), release builds only.
# vcpkg builds its ports with VCPKG_MAX_CONCURRENCY jobs (default here 8, like `cmake --build -j8`).
if(NOT DEFINED ENV{VCPKG_MAX_CONCURRENCY})
  set(ENV{VCPKG_MAX_CONCURRENCY} 8)
endif()
set(VCPKG_OVERLAY_TRIPLETS "${CMAKE_CURRENT_SOURCE_DIR}/cmake/vcpkg-triplets" CACHE STRING "")

project(soa CXX C)

option(SOA_BUILD_PORT "build port/ (soa); needs the server library and platform370" ON)
option(SOA_BUILD_SERVER "build server/ (libsoaserver, soa-server)" ON)
option(SOA_BUILD_EMULATOR "build emulator/ (soa-emu); needs platform370" ON)
option(SOA_BUILD_PLATFORM370 "build platform370/ (libsoaplatform370, the 3.7.0 platform layer)" ON)
option(SOA_BUILD_VIEWER "build emulator-viewer/ (soa-viewer)" ON)
option(SOA_BUILD_TOOLS "build the host tools (tools/aif2png)" ON)
if(SOA_BUILD_PORT AND NOT SOA_BUILD_SERVER)
  message(FATAL_ERROR "SOA_BUILD_PORT needs SOA_BUILD_SERVER: soa links libsoaserver")
endif()
if(SOA_BUILD_PORT AND NOT SOA_BUILD_PLATFORM370)
  message(FATAL_ERROR "SOA_BUILD_PORT needs SOA_BUILD_PLATFORM370: soa links libsoaplatform370")
endif()
if(SOA_BUILD_EMULATOR AND NOT SOA_BUILD_PLATFORM370)
  message(FATAL_ERROR "SOA_BUILD_EMULATOR needs SOA_BUILD_PLATFORM370: soa-emu links libsoaplatform370")
endif()

# ---- shared settings (every part)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE RelWithDebInfo)
endif()

set(SOA_REPO_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# ---- the dependencies (vcpkg, the system, FetchContent; SDL2, EGL/GLES and dynarmic only when
# the runtime is built)
if(SOA_BUILD_PORT OR SOA_BUILD_EMULATOR OR SOA_BUILD_VIEWER OR SOA_BUILD_PLATFORM370)
  set(SOA_NEED_RUNTIME ON)
else()
  set(SOA_NEED_RUNTIME OFF)
endif()
include(cmake/deps.cmake)

# ---- the parts, in dependency order
if(SOA_BUILD_PORT OR SOA_BUILD_EMULATOR OR SOA_BUILD_VIEWER OR SOA_BUILD_PLATFORM370)
  add_subdirectory(runtime)   # libsoaruntime, soaruntime_app, soaruntime_tests
endif()
if(SOA_BUILD_PLATFORM370)
  add_subdirectory(platform370)  # libsoaplatform370: runtime extensions for the 3.7.0 client
endif()
if(SOA_BUILD_SERVER)
  add_subdirectory(server)    # libsoaserver, soanet, soa-server
endif()
if(SOA_BUILD_PORT)
  add_subdirectory(port)      # soa: runtime objects + port/src + libsoaserver
endif()
if(SOA_BUILD_EMULATOR)
  add_subdirectory(emulator)  # soa-emu: runtime + emulator/src
endif()
if(SOA_BUILD_VIEWER)
  add_subdirectory(emulator-viewer)  # soa-viewer: runtime + emulator-viewer/src
endif()
if(SOA_BUILD_TOOLS)
  add_subdirectory(tools/aif2png)  # aif2png: links soa::jpeg9
endif()
