# port/src/native/lib_jpeg/subsystem.cmake: build settings of the `lib_jpeg` subsystem only. port/CMakeLists.txt
# includes every port/src/native/*/subsystem.cmake (sorted) after defining the soa target, so a
# subsystem never edits the shared CMakeLists.txt.
# Sources need no listing: port/CMakeLists.txt globs src/**/*.cpp and links them in basename order
# (static-initializer order, D8); name this subsystem's files lib_jpeg_*.cpp so they sort together.
# The host library is linked by port/CMakeLists.txt (cmake/deps.cmake finds or builds it).
