# libsoaruntime: the JIT host runtime (runtime/README.md): the ELF loader and the dynarmic CPU,
# the HLE of the Android imports, the C++ JVM, the NDK surface and the movie frontend.
#
# Added by the repository's CMakeLists.txt (scripts/build.sh: build/runtime/), which defines what
# it uses (cmake/deps.cmake):
#   dynarmic          the `dynarmic` target (FetchContent)
#   soa::EGL, soa::GLESv2  Mesa's libEGL / libGLESv2 with the Khronos headers from vcpkg
#   ZLIB::ZLIB, soa::SDL2, Freetype::Freetype (vcpkg); soa_zip (common/: the ZIP reader, on minizip-ng)
#   soa_codec         common/: Base64 (SharedPreferences values; OpenSSL), PNG (screenshots; stb)
#
# Targets:
#   soaruntime_iface  INTERFACE: include dir (runtime/src, so `#include "core/cpu.h"`), definitions
#                     and libraries every user of the runtime needs.
#   soaruntime_objs   OBJECT: the runtime's objects. Link them with $<TARGET_OBJECTS:soaruntime_objs>
#                     at the FRONT of the executable's sources: link order is static-initializer
#                     order (soa keeps the order it had before the runtime was a library).
#   soaruntime        STATIC archive of the same objects. The runtime has self-registering objects
#                     (RUNTIME_TEST), so link it with $<LINK_LIBRARY:WHOLE_ARCHIVE,soaruntime>.
#   soaruntime_tests  the runtime's extension-point tests (tests/), linked against soaruntime alone,
#                     which also proves the runtime links without any port code.
#   soaruntime_app    STATIC: the desktop host loop (src/app/: SDL2 window and GL contexts, input,
#                     audio device, control FIFO, activity bring-up, main loop, the text-entry
#                     box: FreeType, privately; screenshots: soa_codec's PNG writer). Kept out of
#                     soaruntime because it links SDL2; a host program that uses it links it as a
#                     plain library.

set(SOA_RUNTIME_DIR ${CMAKE_CURRENT_LIST_DIR})

# Sources, sorted: link order = static-initializer order = RUNTIME_TEST order.
file(GLOB_RECURSE SOA_RUNTIME_SOURCES CONFIGURE_DEPENDS ${SOA_RUNTIME_DIR}/src/*.cpp)
list(FILTER SOA_RUNTIME_SOURCES EXCLUDE REGEX "/src/app/")  # soaruntime_app below
list(SORT SOA_RUNTIME_SOURCES)
soa_link_in_init_order(SOA_RUNTIME_SOURCES)  # (MinGW: reversed, so they initialize in this order: cmake/init_order.cmake)

# The runtime must not depend on its users: every quoted #include in runtime/ must name a file in
# runtime/src (or next to the including file), or dynarmic. Nothing from port/, server/ or
# emulator/. The other includes are common/include's (`#include <soa/env.h>`, the environment rule
# every program shares; `<soa/zip.h>`, the ZIP reader soa_zip; `<soa/base64.h>`, `<soa/prefs_xml.h>`,
# `<soa/png.h>`, the formats of soa_codec; `<soa/sock.h>`, the host sockets of soa_compat; `<soa/fonts.h>`,
# the built-in fonts of soa_fonts), dependencies like dynarmic, not
# users of the runtime. (Also enforced by the include path, which is runtime/src only, and by
# soaruntime_tests, which links the whole archive without any port code.)
soa_check_includes(runtime/ DIRS ${SOA_RUNTIME_DIR}/src ${SOA_RUNTIME_DIR}/tests
                   ALLOW ${SOA_RUNTIME_DIR}/src ${SOA_REPO_DIR}/common/include EXTRA "^dynarmic/")

add_library(soaruntime_iface INTERFACE)
target_include_directories(soaruntime_iface INTERFACE ${SOA_RUNTIME_DIR}/src)
target_compile_definitions(soaruntime_iface INTERFACE _GNU_SOURCE GL_GLEXT_PROTOTYPES EGL_EGLEXT_PROTOTYPES)
target_link_libraries(soaruntime_iface INTERFACE
  soa_env
  soa_zip
  soa_gamefiles
  soa_codec
  soa::ffmpeg  # the movie player (src/frontend/movie_decoder.cpp)
  dynarmic
  soa::EGL
  soa::GLESv2
  ZLIB::ZLIB
  soa_compat
  pthread
  $<IF:$<PLATFORM_ID:Windows>,synchronization,dl>)  # Windows: WaitOnAddress (the guest's futex)

add_library(soaruntime_objs OBJECT ${SOA_RUNTIME_SOURCES})
target_link_libraries(soaruntime_objs PUBLIC soaruntime_iface)
target_link_libraries(soaruntime_objs PRIVATE soa_guest_code)

add_library(soaruntime STATIC $<TARGET_OBJECTS:soaruntime_objs>)
target_link_libraries(soaruntime PUBLIC soaruntime_iface)

file(GLOB SOA_RUNTIME_TEST_SOURCES CONFIGURE_DEPENDS ${SOA_RUNTIME_DIR}/tests/*.cpp)
add_executable(soaruntime_tests ${SOA_RUNTIME_TEST_SOURCES})
target_link_libraries(soaruntime_tests PRIVATE $<LINK_LIBRARY:WHOLE_ARCHIVE,soaruntime>)
target_link_libraries(soaruntime_tests PRIVATE soa_guest_code)

# The desktop host loop (src/app/host.h), on SDL2 (X11 or Wayland: SDL picks).
file(GLOB SOA_RUNTIME_APP_SOURCES CONFIGURE_DEPENDS ${SOA_RUNTIME_DIR}/src/app/*.cpp)
add_library(soaruntime_app STATIC ${SOA_RUNTIME_APP_SOURCES})
target_link_libraries(soaruntime_app PUBLIC soaruntime_iface soa::SDL2 PRIVATE Freetype::Freetype soa_codec soa_fonts)
# Windows: the program exports ANGLE's EGL entry points, so SDL loads EGL from it (src/app/sdl_gl.cpp)
target_link_options(soaruntime_app INTERFACE $<$<PLATFORM_ID:Windows>:${SOA_RUNTIME_DIR}/src/app/egl_exports_win32.def>)
target_link_libraries(soaruntime_app PRIVATE soa_guest_code)
