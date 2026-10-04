# port/src/native/yayoi/subsystem.cmake: build settings of the `yayoi` subsystem only. port/CMakeLists.txt
# includes every port/src/native/*/subsystem.cmake (sorted) after defining the soa target, so a
# subsystem never edits the shared CMakeLists.txt.
# Sources need no listing: port/CMakeLists.txt globs src/**/*.cpp and links them in basename order
# (static-initializer order, D8); name this subsystem's files yayoi_*.cpp so they sort together.
# Add here what is this subsystem's own, e.g. a host library at a clean boundary:
#   target_link_libraries(soa PRIVATE ZLIB::ZLIB)
# The SQLite driver's natives call the host SQLite directly (lib_sqlite's boundary: README.md "The SQLite
# driver").
target_link_libraries(soa PRIVATE unofficial::sqlite3::sqlite3)
