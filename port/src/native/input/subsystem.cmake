# port/src/native/input/subsystem.cmake: build settings of the `input` subsystem only. port/CMakeLists.txt
# includes every port/src/native/*/subsystem.cmake (sorted) after defining the soa target, so a
# subsystem never edits the shared CMakeLists.txt.
# Sources need no listing: port/CMakeLists.txt globs src/**/*.cpp and links them in basename order
# (static-initializer order, D8); name this subsystem's files input_*.cpp so they sort together.
# Add here what is this subsystem's own, e.g. a host library at a clean boundary:
#   target_link_libraries(soa PRIVATE ZLIB::ZLIB)
#
# No contraction of a * b + c into a fused multiply-add (the guest lib has none; math/subsystem.cmake).
file(GLOB _soa_input_sources CONFIGURE_DEPENDS ${CMAKE_CURRENT_LIST_DIR}/input_*.cpp)
set_source_files_properties(${_soa_input_sources} PROPERTIES COMPILE_OPTIONS "-ffp-contract=off")
