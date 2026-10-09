# soa-viewer: the offline 3.8.0 client (the XAPK's libSOA.so + its APKs), unmodified, under the JIT
# host runtime (../runtime). No natives, no restore code, no server: it never links port/src.
# emulator-viewer/README.md. Added by the repository's CMakeLists.txt after ../runtime
# (scripts/build.sh: build/emulator-viewer/soa-viewer).

# The viewer's extensions register themselves (hle_add_registrar) from static initializers, so
# the runtime archive is linked whole.
file(GLOB SOA_VIEWER_SOURCES CONFIGURE_DEPENDS src/*.cpp)
add_executable(soa-viewer ${SOA_VIEWER_SOURCES})
target_include_directories(soa-viewer PRIVATE src)
target_link_libraries(soa-viewer PRIVATE soa_guest_code)
# the viewer: the runtime and common/include only (cmake/flags.cmake)
soa_check_includes(emulator-viewer/ DIRS ${CMAKE_CURRENT_SOURCE_DIR}/src
                   ALLOW ${CMAKE_CURRENT_SOURCE_DIR}/src ${SOA_REPO_DIR}/runtime/include ${SOA_REPO_DIR}/common/include)
target_link_libraries(soa-viewer PRIVATE soaruntime_app $<LINK_LIBRARY:WHOLE_ARCHIVE,soaruntime>)
