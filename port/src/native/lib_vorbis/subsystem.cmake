# port/src/native/lib_vorbis/subsystem.cmake: build settings of the `lib_vorbis` subsystem only. port/CMakeLists.txt
# includes every port/src/native/*/subsystem.cmake (sorted) after defining the soa target, so a
# subsystem never edits the shared CMakeLists.txt.
# Sources need no listing: port/CMakeLists.txt globs src/**/*.cpp and links them in basename order
# (static-initializer order, D8); name this subsystem's files lib_vorbis_*.cpp so they sort together.
# The host libraries (vcpkg's libogg and libVorbis: Ogg::ogg, Vorbis::vorbis) are linked by
# port/CMakeLists.txt already (cmake/deps.cmake finds them).
