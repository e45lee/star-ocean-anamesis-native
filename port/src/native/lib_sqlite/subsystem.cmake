# port/src/native/lib_sqlite/subsystem.cmake: build settings of the `lib_sqlite` subsystem only. port/CMakeLists.txt
# includes every port/src/native/*/subsystem.cmake (sorted) after defining the soa target, so a
# subsystem never edits the shared CMakeLists.txt.
# Sources need no listing: port/CMakeLists.txt globs src/**/*.cpp and links them in basename order
# (static-initializer order, D8); name this subsystem's files lib_sqlite_*.cpp so they sort together.
# Add here what is this subsystem's own, e.g. a host library at a clean boundary:
#   target_link_libraries(soa PRIVATE ZLIB::ZLIB)
# The host SQLite (vcpkg's sqlite3, pinned to 3.45.1 in vcpkg.json; the server links it too). port/CMakeLists.txt
# links it already; named here as the subsystem's own dependency.
target_link_libraries(soa PRIVATE unofficial::sqlite3::sqlite3)
