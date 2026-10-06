# The build dependencies (README.md, "Setup"), included once by the root CMakeLists.txt.
#
# From vcpkg (vcpkg.json, manifest mode: configured through the vcpkg toolchain, which the root
# CMakeLists.txt picks up from $VCPKG_ROOT or .vcpkg/): imported targets
#   ZLIB::ZLIB  MINIZIP::minizip-ng  unofficial::sqlite3::sqlite3  zstd::libzstd  Ogg::ogg  Vorbis::vorbis
#   OpenSSL::Crypto  pugixml::pugixml  msgpack-cxx  httplib::httplib  nlohmann_json::nlohmann_json  soa::SDL2  Boost::boost (dynarmic)  Freetype::Freetype (the runtime's text box,
#   runtime/src/app/text_overlay.cpp)  soa::ffmpeg (FFmpeg's libraries: the movie player)  litehtml  soa::stb (headers; soa_codec's PNG writer, the web view)  and the
#   EGL/GLES/KHR headers.
# From the system (README.md, "Setup": what vcpkg can't replace on Linux), only when the runtime is
# built (SOA_NEED_RUNTIME, like soa::SDL2 and dynarmic):
#   soa::EGL, soa::GLESv2  Mesa's libEGL / libGLESv2 (the libraries only; headers from vcpkg)
# From CMake FetchContent, pinned by URL + SHA256 (not in vcpkg), into build/_deps:
#   dynarmic               the ARM64 -> x86-64 JIT (runtime/)
#   soa::jpeg9             IJG libjpeg 9b (the game's), static (cmake/libjpeg9/); soa (lib_jpeg), tools/aif2png
#   soa::zstd134           zstd 1.3.4, the game's version, static (cmake/zstd134/); soa's lib_zstd natives
include(FetchContent)

# ---- vcpkg packages
find_package(ZLIB REQUIRED)
find_package(unofficial-sqlite3 CONFIG REQUIRED)
find_package(zstd CONFIG REQUIRED)
find_package(Ogg CONFIG REQUIRED)
find_package(Vorbis CONFIG REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(minizip-ng CONFIG REQUIRED)  # MINIZIP::minizip-ng (zlib only): common/ soa_zip
find_package(pugixml CONFIG REQUIRED)  # pugixml::pugixml: SharedPreferences XML (soa_codec, common/src/prefs_xml.cpp)
# stb (headers): stb_image_write writes every PNG (soa_codec, common/src/png.cpp: screenshots,
# tools/aif2png; the web view's render tool), stb_truetype / stb_image the web view's text and images.
find_path(SOA_STB_INCLUDE_DIR stb_image_write.h REQUIRED)
add_library(soa::stb INTERFACE IMPORTED)
target_include_directories(soa::stb INTERFACE ${SOA_STB_INCLUDE_DIR})
find_package(msgpack-cxx CONFIG REQUIRED)  # target msgpack-cxx (headers; the server's MessagePack codec)
find_package(httplib CONFIG REQUIRED)  # target httplib::httplib (headers; soa-server's HTTP server and client)
find_package(nlohmann_json CONFIG REQUIRED)  # target nlohmann_json::nlohmann_json (headers; the server's English art recipes, server/src/english_art)
find_package(CLI11 CONFIG REQUIRED)  # target CLI11::CLI11 (vcpkg builds it precompiled): the programs' command lines (soa_env, common/include/soa/cli.h)
# The web view's page renderer (webview/, docs/webview.md): litehtml lays out HTML/CSS (gumbo
# parses it; the overlay port cmake/vcpkg-ports/litehtml).
if(SOA_BUILD_WEBVIEW)
  find_package(litehtml CONFIG REQUIRED)     # target litehtml (+ unofficial::gumbo::gumbo)
endif()
if(SOA_NEED_RUNTIME)  # the JIT host runtime and what links it (not for a server-only build)
  find_package(SDL2 CONFIG REQUIRED)
  find_package(Freetype REQUIRED)  # vcpkg's freetype (zlib only): soaruntime_app's text box
  # FFmpeg's libraries (vcpkg's ffmpeg: avcodec, avformat, swresample; LGPL): the movie player
  # (runtime/src/frontend/movie_decoder.cpp). The port's FindFFMPEG gives the static libraries in
  # link order plus their system libraries (Linux: m, atomic, pthread; MinGW: bcrypt and the like).
  find_package(FFMPEG REQUIRED)
  add_library(soa::ffmpeg INTERFACE IMPORTED)
  target_include_directories(soa::ffmpeg INTERFACE ${FFMPEG_INCLUDE_DIRS})
  target_link_directories(soa::ffmpeg INTERFACE ${FFMPEG_LIBRARY_DIRS})
  target_link_libraries(soa::ffmpeg INTERFACE ${FFMPEG_LIBRARIES})
  add_library(soa::SDL2 INTERFACE IMPORTED)
  target_link_libraries(soa::SDL2 INTERFACE $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>)
  # egl-registry / opengl-registry: headers only (EGL/, KHR/, GLES2/, GLES3/).
  find_path(SOA_EGL_INCLUDE_DIR EGL/egl.h REQUIRED)
  find_path(SOA_GLES_INCLUDE_DIR GLES2/gl2.h REQUIRED)

  if(WIN32)
    # ---- Windows: ANGLE from vcpkg (vcpkg.json feature "angle"; scripts/build.sh --windows)
    find_package(unofficial-angle CONFIG REQUIRED)
    set(SOA_EGL_LIBRARY unofficial::angle::libEGL)
    set(SOA_GLESV2_LIBRARY unofficial::angle::libGLESv2)
  else()
    # ---- system libraries: libEGL / libGLESv2 (Mesa), by soname too, so the -dev packages aren't needed
    find_library(SOA_EGL_LIBRARY NAMES EGL libEGL.so.1 REQUIRED)
    find_library(SOA_GLESV2_LIBRARY NAMES GLESv2 libGLESv2.so.2 REQUIRED)
  endif()
  add_library(soa::EGL INTERFACE IMPORTED)
  target_include_directories(soa::EGL INTERFACE ${SOA_EGL_INCLUDE_DIR})
  target_link_libraries(soa::EGL INTERFACE ${SOA_EGL_LIBRARY})
  add_library(soa::GLESv2 INTERFACE IMPORTED)
  target_include_directories(soa::GLESv2 INTERFACE ${SOA_GLES_INCLUDE_DIR})
  target_link_libraries(soa::GLESv2 INTERFACE ${SOA_GLESV2_LIBRARY})

  # ---- dynarmic, at the commit the port has always used (lioncash/dynarmic; the externals are in-tree)
  find_package(Boost CONFIG REQUIRED)  # vcpkg's boost-headers / boost-icl / boost-variant
  FetchContent_Declare(dynarmic
    URL https://github.com/lioncash/dynarmic/archive/a41c380246d3d9f9874f0f792d234dc0cc17c180.tar.gz
    URL_HASH SHA256=cc0dfec19b7cfb80a649bd994bd0569c0482de1f49448773d2899f30b6a180c3
    EXCLUDE_FROM_ALL)
  set(DYNARMIC_USE_BUNDLED_EXTERNALS ON CACHE BOOL "" FORCE)
  set(DYNARMIC_TESTS OFF CACHE BOOL "" FORCE)
  set(DYNARMIC_WARNINGS_AS_ERRORS OFF CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(dynarmic)
  if(WIN32 AND TARGET fmt)
    # dynarmic's bundled fmt 10.1 and llvm-mingw's clang (23): its compile-time format-string
    # checks are rejected ("call to consteval function ... is not a constant expression"); run
    # them at run time instead.
    target_compile_definitions(fmt PUBLIC FMT_CONSTEVAL=)
    # its <fmt/ostream.h> wants libc++'s internal <__std_stream> on Windows: cmake/dynarmic-win
    target_include_directories(fmt BEFORE PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/dynarmic-win>)
    # dynarmic's ir_emitter.h uses std::vector without <vector> (libstdc++ includes it on the way);
    # mcl's lift_sequence for this clang (cmake/dynarmic-win/mcl_lift_sequence.h)
    target_compile_options(dynarmic PRIVATE -include vector "SHELL:-include ${CMAKE_CURRENT_LIST_DIR}/dynarmic-win/mcl_lift_sequence.h")
  endif()
endif()

# ---- IJG libjpeg 9b, the game's version ("9b 17-Jan-2016"): port/src/native/lib_jpeg decodes
# bit-exactly with it (9e, used before, is what Ubuntu's libjpeg9 package ships)
FetchContent_Declare(jpeg9
  URL https://www.ijg.org/files/jpegsrc.v9b.tar.gz
  URL_HASH SHA256=566241ad815df935390b341a5d3d15a73a4000e5aab40c58505324c2855cbbb8
  SOURCE_SUBDIR no-cmake)  # the tarball has no CMakeLists.txt: only unpack it; cmake/libjpeg9/ builds it
FetchContent_MakeAvailable(jpeg9)
set(JPEG9_SOURCE_DIR ${jpeg9_SOURCE_DIR})
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/libjpeg9 ${jpeg9_BINARY_DIR} EXCLUDE_FROM_ALL)

# ---- zstd 1.3.4, the game's (port/src/native/lib_zstd: byte-exact with the guest, errors included)
FetchContent_Declare(zstd134
  URL https://github.com/facebook/zstd/archive/refs/tags/v1.3.4.tar.gz
  URL_HASH SHA256=92e41b6e8dd26bbd46248e8aa1d86f1551bc221a796277ae9362954f26d605a9
  SOURCE_SUBDIR no-cmake)  # only unpack it; cmake/zstd134/ builds the library
FetchContent_MakeAvailable(zstd134)
set(ZSTD134_SOURCE_DIR ${zstd134_SOURCE_DIR})
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/zstd134 ${zstd134_BINARY_DIR} EXCLUDE_FROM_ALL)
