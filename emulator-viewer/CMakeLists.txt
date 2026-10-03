# soa-viewer: the offline 3.8.0 client (the XAPK's libSOA.so + its APKs), unmodified, under the JIT
# host runtime (../runtime). No natives, no restore code, no server: it never links port/src.
# emulator-viewer/README.md. Added by the repository's CMakeLists.txt after ../runtime
# (cmake -S . -B build: build/emulator-viewer/soa-viewer).

# The viewer's extensions register themselves (hle_add_registrar) from static initializers, so
# the runtime archive is linked whole.
file(GLOB SOA_VIEWER_SOURCES CONFIGURE_DEPENDS src/*.cpp)
add_executable(soa-viewer ${SOA_VIEWER_SOURCES})
target_include_directories(soa-viewer PRIVATE src)
target_compile_options(soa-viewer PRIVATE -Wall -Wno-unused-parameter -fno-strict-aliasing -mcx16)
target_link_libraries(soa-viewer PRIVATE soaruntime_app $<LINK_LIBRARY:WHOLE_ARCHIVE,soaruntime>)
