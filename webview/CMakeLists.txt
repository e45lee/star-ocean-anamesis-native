# libsoawebview: the web view's page renderer (docs/webview.md; include/soawebview/page.h), and its
# offline tool and tests. Added by the repository's CMakeLists.txt when SOA_BUILD_WEBVIEW is on.
# It depends on nothing of the repository (no runtime, JNI or GL): the runtime's overlay, the
# server and tools can link it alike.
#
# Targets:
#   soawebview          STATIC. Public include dir webview/include (#include "soawebview/page.h");
#                       links litehtml (+ gumbo; vcpkg, our overlay port cmake/vcpkg-ports/litehtml)
#                       and the stb headers privately.
#   soa-webview-render  renders a local HTML page to a PNG (tools/render.cpp; docs/webview.md).
#   soawebview_tests    the library's tests (tests/webview_tests.cpp): `build/webview/soawebview_tests`.

set(SOA_WEBVIEW_DIR ${CMAKE_CURRENT_LIST_DIR})
file(GLOB SOA_WEBVIEW_SOURCES CONFIGURE_DEPENDS ${SOA_WEBVIEW_DIR}/src/*.cpp)
list(SORT SOA_WEBVIEW_SOURCES)
add_library(soawebview STATIC ${SOA_WEBVIEW_SOURCES})
target_include_directories(soawebview PUBLIC ${SOA_WEBVIEW_DIR}/include PRIVATE ${SOA_WEBVIEW_DIR}/src)
target_link_libraries(soawebview PUBLIC soa_env soa_compat litehtml PRIVATE soa::stb)
target_compile_options(soawebview PRIVATE -Wall -Wno-unused-parameter -Wno-unused-function)

add_executable(soa-webview-render ${SOA_WEBVIEW_DIR}/tools/render.cpp)
target_link_libraries(soa-webview-render PRIVATE soawebview soa::stb)
target_compile_options(soa-webview-render PRIVATE -Wall)

add_executable(soawebview_tests ${SOA_WEBVIEW_DIR}/tests/webview_tests.cpp)
target_link_libraries(soawebview_tests PRIVATE soawebview)
target_compile_options(soawebview_tests PRIVATE -Wall)
