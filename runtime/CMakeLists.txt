# libsoaruntime: the JIT host runtime (runtime/README.md): the ELF loader and the dynarmic CPU,
# the HLE of the Android imports, the C++ JVM, the NDK surface and the movie frontend.
#
# Added by the repository's CMakeLists.txt (cmake -S . -B build: build/runtime/), which defines what
# it uses (cmake/deps.cmake):
#   dynarmic          the `dynarmic` target (FetchContent)
#   soa::EGL, soa::GLESv2  Mesa's libEGL / libGLESv2 with the Khronos headers from vcpkg
#   ZLIB::ZLIB, soa::SDL2, Freetype::Freetype (vcpkg)
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
#                     box: FreeType, privately). Kept out of
#                     soaruntime because it links SDL2; a host program that uses it links it as a
#                     plain library.

set(SOA_RUNTIME_DIR ${CMAKE_CURRENT_LIST_DIR})

# Sources, sorted: link order = static-initializer order = RUNTIME_TEST order.
file(GLOB_RECURSE SOA_RUNTIME_SOURCES CONFIGURE_DEPENDS ${SOA_RUNTIME_DIR}/src/*.cpp)
list(FILTER SOA_RUNTIME_SOURCES EXCLUDE REGEX "/src/app/")  # soaruntime_app below
list(SORT SOA_RUNTIME_SOURCES)

# The runtime must not depend on its users: every quoted #include in runtime/ must name a file in
# runtime/src (or next to the including file), or dynarmic. Nothing from port/, server/ or
# emulator/. The one other include is the header-only soa_env (`#include <soa/env.h>`,
# common/include: the environment rule every program shares), a dependency like dynarmic, not a
# user of the runtime. (Also enforced by the include path, which is runtime/src only, and by
# soaruntime_tests, which links the whole archive without any port code.)
file(GLOB_RECURSE _rt_check CONFIGURE_DEPENDS ${SOA_RUNTIME_DIR}/src/* ${SOA_RUNTIME_DIR}/tests/*)
foreach(_f ${_rt_check})
  get_filename_component(_dir ${_f} DIRECTORY)
  file(STRINGS ${_f} _incs REGEX "^[ \t]*#[ \t]*include[ \t]*\"")
  foreach(_l ${_incs})
    string(REGEX REPLACE "^[ \t]*#[ \t]*include[ \t]*\"([^\"]*)\".*$" "\\1" _inc "${_l}")
    if(_inc MATCHES "^dynarmic/")
      continue()
    endif()
    if(_inc MATCHES "\\.\\." OR NOT (EXISTS ${SOA_RUNTIME_DIR}/src/${_inc} OR EXISTS ${_dir}/${_inc}))
      message(FATAL_ERROR "runtime/ must not include \"${_inc}\" (${_f}): the runtime includes only runtime/src")
    endif()
  endforeach()
endforeach()

add_library(soaruntime_iface INTERFACE)
target_include_directories(soaruntime_iface INTERFACE ${SOA_RUNTIME_DIR}/src)
target_compile_definitions(soaruntime_iface INTERFACE _GNU_SOURCE GL_GLEXT_PROTOTYPES EGL_EGLEXT_PROTOTYPES)
target_link_libraries(soaruntime_iface INTERFACE
  soa_env
  dynarmic
  soa::EGL
  soa::GLESv2
  ZLIB::ZLIB
  soa_compat
  pthread
  $<IF:$<PLATFORM_ID:Windows>,synchronization,dl>)  # Windows: WaitOnAddress (the guest's futex)

add_library(soaruntime_objs OBJECT ${SOA_RUNTIME_SOURCES})
target_link_libraries(soaruntime_objs PUBLIC soaruntime_iface)
target_compile_options(soaruntime_objs PRIVATE -Wall -Wno-unused-parameter -Wno-unused-function -fno-strict-aliasing -mcx16)

add_library(soaruntime STATIC $<TARGET_OBJECTS:soaruntime_objs>)
target_link_libraries(soaruntime PUBLIC soaruntime_iface)

file(GLOB SOA_RUNTIME_TEST_SOURCES CONFIGURE_DEPENDS ${SOA_RUNTIME_DIR}/tests/*.cpp)
add_executable(soaruntime_tests ${SOA_RUNTIME_TEST_SOURCES})
target_link_libraries(soaruntime_tests PRIVATE $<LINK_LIBRARY:WHOLE_ARCHIVE,soaruntime>)
target_compile_options(soaruntime_tests PRIVATE -Wall -Wno-unused-parameter -fno-strict-aliasing -mcx16)

# The desktop host loop (src/app/host.h), on SDL2 (X11 or Wayland: SDL picks).
file(GLOB SOA_RUNTIME_APP_SOURCES CONFIGURE_DEPENDS ${SOA_RUNTIME_DIR}/src/app/*.cpp)
add_library(soaruntime_app STATIC ${SOA_RUNTIME_APP_SOURCES})
target_link_libraries(soaruntime_app PUBLIC soaruntime_iface soa::SDL2 PRIVATE Freetype::Freetype)
# Windows: the program exports ANGLE's EGL entry points, so SDL loads EGL from it (src/app/sdl_gl.cpp)
target_link_options(soaruntime_app INTERFACE $<$<PLATFORM_ID:Windows>:${SOA_RUNTIME_DIR}/src/app/egl_exports_win32.def>)
target_compile_options(soaruntime_app PRIVATE -Wall -Wno-unused-parameter -Wno-unused-function -fno-strict-aliasing -mcx16)
