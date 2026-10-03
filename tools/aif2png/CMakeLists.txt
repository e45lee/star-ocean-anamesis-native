# aif2png: the AIF (zstd-compressed JPEG + alpha) -> PNG converter. Added by the repository's
# CMakeLists.txt (build/tools/aif2png/aif2png); IJG libjpeg 9 (soa::jpeg9, cmake/deps.cmake), zstd
# and zlib from vcpkg.
add_executable(aif2png aif2png.cpp)
target_compile_options(aif2png PRIVATE -Wall)
target_link_libraries(aif2png PRIVATE soa::jpeg9 zstd::libzstd ZLIB::ZLIB)
