# libsoaserver: the local game server (server/README.md), and soa-server, its standalone binary.
# Added by the repository's CMakeLists.txt (scripts/build.sh: build/server/soa-server); it needs
# only SQLite and OpenSSL's libcrypto (and zlib for soanet), from vcpkg (cmake/deps.cmake).

# The server stands alone: it includes only server/ and common/include, nothing of the port, the
# runtime, platform370 or the web view (checked at configure time: cmake/flags.cmake).
soa_check_includes(server/ DIRS ${CMAKE_CURRENT_SOURCE_DIR}/src ${CMAKE_CURRENT_SOURCE_DIR}/include
                   ${CMAKE_CURRENT_SOURCE_DIR}/tests ${CMAKE_CURRENT_SOURCE_DIR}/app ${CMAKE_CURRENT_SOURCE_DIR}/net
                   ALLOW ${CMAKE_CURRENT_SOURCE_DIR}/src ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}
                         ${SOA_REPO_DIR}/common/include)

# The library: every source under src/ (recursive) and the cross-cutting tests of tests/ (not
# tests/net or tests/ninja: those are soa-server's). The modules register in src/core/modules.cpp's
# explicit order; only the tests register from static initializers, so the source order is the
# tests' run order and nothing else (their seeds come from their names).
file(GLOB_RECURSE SOASERVER_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB _soaserver_tests CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp)
list(APPEND SOASERVER_SOURCES ${_soaserver_tests})
soa_link_in_init_order(SOASERVER_SOURCES)  # (MinGW: reversed, so the tests register in this order: cmake/init_order.cmake)

add_library(soaserver STATIC ${SOASERVER_SOURCES})
target_include_directories(soaserver PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
# -fno-strict-aliasing, as it always had; no -mcx16 (cmake/flags.cmake)
target_compile_options(soaserver PRIVATE -fno-strict-aliasing)
target_link_libraries(soaserver PRIVATE soa_warnings)
target_link_libraries(soaserver PUBLIC soa_env soa_gamefiles soa_codec unofficial::sqlite3::sqlite3 OpenSSL::Crypto pthread soa_compat)
# msgpack-cxx (headers): core/msgpack.cpp only; soaserver/msgpack.h stays free of it
target_link_libraries(soaserver PRIVATE msgpack-cxx)
# nlohmann-json (headers): the English art recipes (src/english_art/recipe.cpp) only
target_link_libraries(soaserver PRIVATE nlohmann_json::nlohmann_json)
# utf8proc: Unicode normalization and categories for the English derivation (src/master/english_derive.cpp)
target_link_libraries(soaserver PRIVATE utf8proc::utf8proc soa_text)

# soanet: soa-server's wire layer (net/: packets, the Ninja cipher, the request decoder, the game
# session and bridge, the HTTP router; the HTTP server and client on cpp-httplib, the poll loop). Not part of
# libsoaserver. soa links it too: the HTTP router for its in-process CDN and the packet log's formats (net/README.md).
file(GLOB_RECURSE _soanet_src CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/net/*.cpp)
add_library(soanet STATIC ${_soanet_src})
# (soaserver's headers only: the executable links the library whole, after soanet)
target_include_directories(soanet PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} $<TARGET_PROPERTY:soaserver,INTERFACE_INCLUDE_DIRECTORIES>)
target_compile_options(soanet PRIVATE -fno-strict-aliasing)
target_link_libraries(soanet PRIVATE soa_warnings)
target_link_libraries(soanet PUBLIC ZLIB::ZLIB OpenSSL::Crypto soa_compat PRIVATE httplib::httplib)
target_link_libraries(soanet PRIVATE soa_httplib_win)  # (cmake/flags.cmake)
# nlohmann-json (headers): the bridge's JSON (net/game.cpp parse_bridge_request, bridge_reply_json)
target_link_libraries(soanet PRIVATE nlohmann_json::nlohmann_json)

# soa-server: the standalone server. app/ is the command line; tests/net and tests/ninja are the
# wire layer's selftests (tests/ninja/ninja_check.cpp is a separate command-line tool, not built here).
file(GLOB _soaserver_app CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/app/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/tests/net/*.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/tests/ninja/*_test.cpp)
add_executable(soa-server ${_soaserver_app})
target_link_libraries(soa-server PRIVATE soa_warnings)
# Every object of the library (the tests register from static initializers).
target_link_libraries(soa-server PRIVATE soanet "$<LINK_LIBRARY:WHOLE_ARCHIVE,soaserver>" httplib::httplib)  # (httplib: tests/net's client)
target_link_libraries(soa-server PRIVATE soa_httplib_win)  # (cpp-httplib, as soanet)
