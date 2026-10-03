# libsoaserver: the local game server (server/README.md), and soa-server, its standalone binary.
# Added by the repository's CMakeLists.txt (cmake -S . -B build: build/server/soa-server); it needs
# only SQLite and OpenSSL's libcrypto (and zlib for soanet), from vcpkg (cmake/deps.cmake).

# The library must stand alone: no includes from the port or the runtime (checked at configure time).
# The library's own folders (src/core/, src/api/, ... included as "core/...") share names with the
# port's (core/), so a match is an error only when no such file exists under server/src.
file(GLOB_RECURSE _soaserver_all CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
     ${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h ${CMAKE_CURRENT_SOURCE_DIR}/app/*.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/net/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/net/*.h ${CMAKE_CURRENT_SOURCE_DIR}/net/*.inc)
foreach(_f ${_soaserver_all})
  file(STRINGS ${_f} _bad REGEX "^[ \t]*#[ \t]*include[ \t]*[\"<](core|hle|jni|android|frontend|native|restore|runtime|port|src)/")
  foreach(_line ${_bad})
    string(REGEX REPLACE "^[^\"<]*[\"<]([^\">]*)[\">].*$" "\\1" _inc "${_line}")
    if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/src/${_inc})
      message(FATAL_ERROR "server/ must not include port or runtime code: ${_f}: ${_line}")
    endif()
  endforeach()
endforeach()

# The library: every source under src/ (recursive) and the cross-cutting tests of tests/ (not
# tests/net or tests/ninja: those are soa-server's). The modules register in src/core/modules.cpp's
# explicit order; only the tests register from static initializers, so the source order is the
# tests' run order and nothing else (their seeds come from their names).
file(GLOB_RECURSE SOASERVER_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB _soaserver_tests CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp)
list(APPEND SOASERVER_SOURCES ${_soaserver_tests})

add_library(soaserver STATIC ${SOASERVER_SOURCES})
target_include_directories(soaserver PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_compile_options(soaserver PRIVATE -Wall -Wno-unused-parameter -Wno-unused-function -fno-strict-aliasing)
target_link_libraries(soaserver PUBLIC unofficial::sqlite3::sqlite3 OpenSSL::Crypto pthread)

# soanet: soa-server's wire layer (net/: packets, the Ninja cipher, the request decoder, the game
# session and bridge, the HTTP server, the poll loop). Not part of libsoaserver: soa never needs it.
file(GLOB_RECURSE _soanet_src CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/net/*.cpp)
add_library(soanet STATIC ${_soanet_src})
# (soaserver's headers only: the executable links the library whole, after soanet)
target_include_directories(soanet PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} $<TARGET_PROPERTY:soaserver,INTERFACE_INCLUDE_DIRECTORIES>)
target_compile_options(soanet PRIVATE -Wall -Wno-unused-parameter -fno-strict-aliasing)
target_link_libraries(soanet PUBLIC ZLIB::ZLIB OpenSSL::Crypto)

# soa-server: the standalone server. app/ is the command line; tests/net and tests/ninja are the
# wire layer's selftests (tests/ninja/ninja_check.cpp is a separate command-line tool, not built here).
file(GLOB _soaserver_app CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/app/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/tests/net/*.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/tests/ninja/*_test.cpp)
add_executable(soa-server ${_soaserver_app})
target_compile_options(soa-server PRIVATE -Wall -Wno-unused-parameter)
# Every object of the library (the tests register from static initializers).
target_link_libraries(soa-server PRIVATE soanet "$<LINK_LIBRARY:WHOLE_ARCHIVE,soaserver>")
