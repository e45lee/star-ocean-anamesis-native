# aif2png: the AIF (zstd-compressed JPEG + alpha) -> PNG converter. Added by the repository's
# CMakeLists.txt (build/tools/aif2png/aif2png); IJG libjpeg 9 (soa::jpeg9, cmake/deps.cmake); ADLD
# (soa/adld.h), SLZ, AIF and ETC2 (soa/aska_image.h) and the PNG writer from soa_codec (common/).
add_executable(aif2png aif2png.cpp)
target_link_libraries(aif2png PRIVATE soa_warnings)
target_link_libraries(aif2png PRIVATE soa::jpeg9 soa_codec soa_compat)
