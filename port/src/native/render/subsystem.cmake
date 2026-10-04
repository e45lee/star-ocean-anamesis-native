# port/src/native/render/subsystem.cmake: build settings of the `render` subsystem only. port/CMakeLists.txt
# includes every port/src/native/*/subsystem.cmake (sorted) after defining the soa target, so a
# subsystem never edits the shared CMakeLists.txt.
# Sources need no listing: port/CMakeLists.txt globs src/**/*.cpp and links them in basename order
# (static-initializer order, D8); name this subsystem's files render_*.cpp so they sort together.
# Add here what is this subsystem's own, e.g. a host library at a clean boundary:
#   target_link_libraries(soa PRIVATE ZLIB::ZLIB)
