# port/src/native/math/subsystem.cmake: build settings of the `math` subsystem only. port/CMakeLists.txt
# includes every port/src/native/*/subsystem.cmake (sorted) after defining the soa target, so a
# subsystem never edits the shared CMakeLists.txt.
# Sources need no listing: port/CMakeLists.txt globs src/**/*.cpp and links them in basename order
# (static-initializer order, D8); name this subsystem's files math_*.cpp so they sort together.
#
# No contraction of a * b + c into a fused multiply-add: the guest lib has none (math_family.h), and
# a host compiler targeting FMA (x86-64-v3, AArch64 hosts, clang's default -ffp-contract=on) would
# otherwise round differently.
file(GLOB _soa_math_sources CONFIGURE_DEPENDS ${CMAKE_CURRENT_LIST_DIR}/math_*.cpp)
set_source_files_properties(${_soa_math_sources} PROPERTIES COMPILE_OPTIONS "-ffp-contract=off")
