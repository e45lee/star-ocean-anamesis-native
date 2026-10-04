# soa, the desktop port (port/README.md). Added by the repository's CMakeLists.txt, which defines the
# shared settings (the C++ standard) and the dependencies' targets (cmake/deps.cmake: vcpkg, the
# system, FetchContent), adds dynarmic and adds ../runtime (libsoaruntime), ../platform370
# (libsoaplatform370) and ../server (libsoaserver) before this directory.

file(GLOB_RECURSE SOA_SOURCES CONFIGURE_DEPENDS src/*.cpp)
# Link order = static-initializer order = the order natives and selftests register in, and some
# selftests depend on it (the zz_*_test.cpp files must register last). src/native/ is split into
# subsystem folders (src/native/README.md); sort its files by basename as if the folder were flat,
# so the order doesn't depend on the folder layout.
set(_soa_keyed "")
foreach(_f ${SOA_SOURCES})
  string(REGEX REPLACE "/src/native/.*/([^/]+)$" "/src/native/\\1" _key "${_f}")
  list(APPEND _soa_keyed "${_key}|${_f}")
endforeach()
list(SORT _soa_keyed)
set(SOA_SOURCES "")
foreach(_e ${_soa_keyed})
  string(REGEX REPLACE "^[^|]*\\|" "" _f "${_e}")
  list(APPEND SOA_SOURCES "${_f}")
endforeach()
# The JIT host runtime, libsoaruntime (../runtime: core, hle, jni, android, frontend;
# runtime/README.md). Its objects are linked FIRST, as when they were part of src/: link order is
# static-initializer order. CMake puts $<TARGET_OBJECTS> after a target's own objects, so they go
# in through the link options, which come before the objects on the link line, and LINK_DEPENDS
# relinks soa when they change.
add_executable(soa ${SOA_SOURCES})
add_dependencies(soa soaruntime_objs)
target_link_options(soa PRIVATE $<TARGET_OBJECTS:soaruntime_objs>)
set_property(TARGET soa APPEND PROPERTY LINK_DEPENDS $<TARGET_OBJECTS:soaruntime_objs>)
target_include_directories(soa PRIVATE src)
target_compile_definitions(soa PRIVATE _GNU_SOURCE GL_GLEXT_PROTOTYPES EGL_EGLEXT_PROTOTYPES)
target_compile_options(soa PRIVATE -Wall -Wno-unused-parameter -Wno-unused-function -fno-strict-aliasing -mcx16)
# The 3.7.0 platform layer (../platform370: the Java answers, fmod, the device clock, the
# service_stop_day patch, the network glue); main.cpp calls platform370::install /
# install_patches. A plain library: nothing in it self-registers.
target_link_libraries(soa PRIVATE
  soaplatform370
  soaruntime_app
  soaruntime_iface
  dynarmic
  soa::SDL2
  soa::EGL
  soa::GLESv2
  ZLIB::ZLIB
  unofficial::sqlite3::sqlite3
  OpenSSL::Crypto
  # Static, for the host-library natives (the game's zlib, libjpeg 9b, SQLite, libVorbis + libogg,
  # zstd: port/PLAN.md, N); nothing uses them yet, so nothing of them is linked in.
  Vorbis::vorbis
  Ogg::ogg
  soa::jpeg9
  soa::zstd134  # the game's zstd version (cmake/deps.cmake), not vcpkg's
  pthread $<$<NOT:$<PLATFORM_ID:Windows>>:dl>)
# The server library, whole (its tests register from static initializers; its modules register in
# server/src/core/modules.cpp's order), after the port's own objects: the same test order as when it was
# port/src/server.
target_link_libraries(soa PRIVATE "$<LINK_LIBRARY:WHOLE_ARCHIVE,soaserver>")
# soa-server's HTTP router and poll loop (../server/net): --server inproc serves the library's CDN
# in-process (src/native/api/server_cdn.cpp).
target_link_libraries(soa PRIVATE soanet)
# The web view's page renderer (../webview: litehtml; on by default, docs/webview.md).
target_link_libraries(soa PRIVATE soawebview)

# Per-subsystem build settings of the native rebuild (port/src/native/<s>/subsystem.cmake, made by
# tools/subsystem.py new): a subsystem's own libraries / definitions live in its folder, so parallel
# branches adding subsystems never edit this file. Its sources come from the glob above (basename
# order, D8). Included sorted, after the target exists.
file(GLOB _soa_subsystem_cmake CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/native/*/subsystem.cmake)
list(SORT _soa_subsystem_cmake)
foreach(_f ${_soa_subsystem_cmake})
  include(${_f})
endforeach()
