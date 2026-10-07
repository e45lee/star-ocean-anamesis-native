# The one build of the repository: the JIT host runtime (runtime/), the 3.7.0 platform layer
# (platform370/), the local game server (server/), the desktop port (port/), the 3.7.0 emulator
# (emulator/), the 3.8.0 viewer (emulator-viewer/) and the host tools (tools/aif2png, tools/movie_check).
#
#   scripts/build.sh                    # bootstraps vcpkg (.vcpkg/) if needed, configures, builds
#   cmake --build build -j8             # afterwards, a build dir build.sh configured (no reconfigure)
# Configure only through scripts/build.sh (it sets SOA_BUILD_SH, checked below; its header says why).
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
#   build/tools/movie_check/movie_check  the movie player's decoder on one movie (tools/movie_compare.py)
#   build/webview/soa-webview-render  renders an HTML page to a PNG with the web view's renderer (docs/webview.md)
#
# One part: `cmake --build build --target soa` (or soa-server, soa-emu, soa-viewer,
# soaruntime_tests, aif2png), or turn parts off at configure time with the options below.
#
# The subdirectories' CMakeLists.txt are not roots: they use the settings defined here.
cmake_minimum_required(VERSION 3.28)  # FetchContent_Declare(... EXCLUDE_FROM_ALL)

# Configured only by scripts/build.sh, also when a bare `cmake --build` reconfigures: the first
# configure installs the vcpkg ports, and build.sh's environment makes their binary-cache keys
# (scripts/build.sh header: the Windows build's fixed PATH, its posix-thread MinGW compilers first).
# Another environment rebuilds every port (about an hour for Windows) or, for Windows, builds them
# with the distribution's default win32-thread compilers.
if(NOT DEFINED ENV{SOA_BUILD_SH})
  message(FATAL_ERROR "configure this build through scripts/build.sh (scripts/build.sh [--windows] "
                      "[--release] [cmake --build options...]; README.md \"Building\"), not cmake directly: "
                      "it sets the environment the vcpkg ports' binary-cache keys depend on.")
endif()

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
# Our overlay ports (cmake/vcpkg-ports/): litehtml, patched (the web view, webview/).
list(APPEND VCPKG_OVERLAY_PORTS "${CMAKE_CURRENT_SOURCE_DIR}/cmake/vcpkg-ports")

project(soa CXX C)

option(SOA_BUILD_PORT "build port/ (soa); needs the server library and platform370" ON)
option(SOA_BUILD_SERVER "build server/ (libsoaserver, soa-server)" ON)
option(SOA_BUILD_EMULATOR "build emulator/ (soa-emu); needs platform370" ON)
option(SOA_BUILD_VIEWER "build emulator-viewer/ (soa-viewer)" ON)
option(SOA_BUILD_TOOLS "build the host tools (tools/aif2png, tools/english_art, tools/movie_check)" ON)
option(SOA_BUILD_WEBVIEW "build webview/ (libsoawebview, soa-webview-render: the HTML page renderer, docs/webview.md)" ON)
if(SOA_BUILD_PORT AND NOT SOA_BUILD_SERVER)
  message(FATAL_ERROR "SOA_BUILD_PORT needs SOA_BUILD_SERVER: soa links libsoaserver")
endif()
if(SOA_BUILD_PORT AND NOT SOA_BUILD_WEBVIEW)
  message(FATAL_ERROR "SOA_BUILD_PORT needs SOA_BUILD_WEBVIEW: soa links libsoawebview (the web view prototype)")
endif()
# platform370/ (libsoaplatform370, the 3.7.0 platform layer): built when soa or soa-emu is, which link it
if(SOA_BUILD_PORT OR SOA_BUILD_EMULATOR)
  set(SOA_BUILD_PLATFORM370 ON)
else()
  set(SOA_BUILD_PLATFORM370 OFF)
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
if(SOA_BUILD_PORT OR SOA_BUILD_EMULATOR OR SOA_BUILD_VIEWER)
  set(SOA_NEED_RUNTIME ON)
else()
  set(SOA_NEED_RUNTIME OFF)
endif()
include(cmake/deps.cmake)
include(cmake/flags.cmake)  # soa_warnings, soa_guest_code: our compile flags; soa_check_includes: the layering checks
include(cmake/init_order.cmake)  # soa_link_in_init_order: static-initializer order on MinGW
if(SOA_NEED_RUNTIME OR SOA_BUILD_WEBVIEW)
  include(cmake/fonts.cmake)  # soa_fonts: Noto Sans JP built into the programs (soa/fonts.h)
endif()

# A release build (scripts/build.sh --release, the only Release configure; the packages are made
# from it): SOA_RELEASE_PACKAGE, so the programs never look for a source checkout around them,
# only --repo DIR and the install dirs (common/include/soa/install.h, "the repo roots"). Not NDEBUG.
if(CMAKE_BUILD_TYPE STREQUAL "Release")
  add_compile_definitions(SOA_RELEASE_PACKAGE=1)
endif()

add_subdirectory(common)    # soa_env (header-only: the environment rule, soa/env.h), soa_env_tests, soa_compat (sockets; the Windows shims), soa_zip (the ZIP reader), soa_zip_tests, soa_codec (PNG, Base64, SharedPreferences XML), soa_codec_tests

# ---- the parts, in dependency order
if(SOA_NEED_RUNTIME)
  add_subdirectory(runtime)   # libsoaruntime, soaruntime_app, soaruntime_tests
endif()
if(SOA_BUILD_PLATFORM370)
  add_subdirectory(platform370)  # libsoaplatform370: runtime extensions for the 3.7.0 client
endif()
if(SOA_BUILD_SERVER)
  add_subdirectory(server)    # libsoaserver, soanet, soa-server
endif()
if(SOA_BUILD_WEBVIEW)
  add_subdirectory(webview)   # libsoawebview + soa-webview-render (litehtml; no runtime dependency)
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
if(SOA_BUILD_PORT AND SOA_BUILD_EMULATOR AND SOA_BUILD_VIEWER)
  add_subdirectory(tests/cli)  # soa_cli_tests: the five programs' command lines vs the parsers they replaced
endif()
if(SOA_BUILD_TOOLS)
  add_subdirectory(tools/aif2png)  # aif2png: links soa::jpeg9
  if(SOA_BUILD_SERVER)
    add_subdirectory(tools/english_art)  # english-art: the English UI art without a server (links libsoaserver)
  endif()
  if(SOA_NEED_RUNTIME)
    add_subdirectory(tools/movie_check)  # movie_check: the movie player's decoder (soa::ffmpeg)
  endif()
endif()
