# The build dependencies (README.md, "Setup"), included once by the root CMakeLists.txt.
#
# From vcpkg (vcpkg.json, manifest mode: configured through the vcpkg toolchain, which the root
# CMakeLists.txt picks up from $VCPKG_ROOT or .vcpkg/): imported targets
#   ZLIB::ZLIB  unofficial::sqlite3::sqlite3  zstd::libzstd  Ogg::ogg  Vorbis::vorbis
#   OpenSSL::Crypto  soa::SDL2  Boost::boost (dynarmic)  litehtml  soa::stb (headers)  and the
#   EGL/GLES/KHR headers.
# From the system (README.md, "Setup": what vcpkg can't replace on Linux), only when the runtime is
# built (SOA_NEED_RUNTIME, like soa::SDL2 and dynarmic):
#   soa::EGL, soa::GLESv2  Mesa's libEGL / libGLESv2 (the libraries only; headers from vcpkg)
# From CMake FetchContent, pinned by URL + SHA256 (not in vcpkg), into build/_deps:
#   dynarmic               the ARM64 -> x86-64 JIT (runtime/)
#   soa::jpeg9             IJG libjpeg 9e, static (cmake/libjpeg9/); tools/aif2png
include(FetchContent)

# ---- vcpkg packages
find_package(ZLIB REQUIRED)
find_package(unofficial-sqlite3 CONFIG REQUIRED)
find_package(zstd CONFIG REQUIRED)
find_package(Ogg CONFIG REQUIRED)
find_package(Vorbis CONFIG REQUIRED)
find_package(OpenSSL REQUIRED)
# The web view's page renderer (webview/, docs/webview.md): litehtml lays out HTML/CSS (gumbo
# parses it; the overlay port cmake/vcpkg-ports/litehtml), stb_truetype draws the text, stb_image
# decodes the images, stb_image_write writes the render tool's PNGs.
if(SOA_BUILD_WEBVIEW)
  find_package(litehtml CONFIG REQUIRED)     # target litehtml (+ unofficial::gumbo::gumbo)
  find_path(SOA_STB_INCLUDE_DIR stb_truetype.h REQUIRED)
  add_library(soa::stb INTERFACE IMPORTED)
  target_include_directories(soa::stb INTERFACE ${SOA_STB_INCLUDE_DIR})
endif()
if(SOA_NEED_RUNTIME)  # the JIT host runtime and what links it (not for a server-only build)
  find_package(SDL2 CONFIG REQUIRED)
  add_library(soa::SDL2 INTERFACE IMPORTED)
  target_link_libraries(soa::SDL2 INTERFACE $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>)
  # egl-registry / opengl-registry: headers only (EGL/, KHR/, GLES2/, GLES3/).
  find_path(SOA_EGL_INCLUDE_DIR EGL/egl.h REQUIRED)
  find_path(SOA_GLES_INCLUDE_DIR GLES2/gl2.h REQUIRED)

  # ---- system libraries: libEGL / libGLESv2 (Mesa), by soname too, so the -dev packages aren't needed
  find_library(SOA_EGL_LIBRARY NAMES EGL libEGL.so.1 REQUIRED)
  find_library(SOA_GLESV2_LIBRARY NAMES GLESv2 libGLESv2.so.2 REQUIRED)
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
endif()

# ---- IJG libjpeg 9e (the game bundles 9b; 9e is what Ubuntu's libjpeg9 package, used before, ships)
FetchContent_Declare(jpeg9
  URL https://www.ijg.org/files/jpegsrc.v9e.tar.gz
  URL_HASH SHA256=4077d6a6a75aeb01884f708919d25934c93305e49f7e3f36db9129320e6f4f3d
  SOURCE_SUBDIR no-cmake)  # the tarball has no CMakeLists.txt: only unpack it; cmake/libjpeg9/ builds it
FetchContent_MakeAvailable(jpeg9)
set(JPEG9_SOURCE_DIR ${jpeg9_SOURCE_DIR})
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/libjpeg9 ${jpeg9_BINARY_DIR} EXCLUDE_FROM_ALL)
