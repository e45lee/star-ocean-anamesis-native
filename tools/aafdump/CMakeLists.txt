# aafdump: the game's animations in text, their values, and the proof that soa_models evaluates them
# as the game does (tools/aafdump/aafdump.cpp). Added by the repository's CMakeLists.txt
# (build/tools/aafdump/aafdump); soa_models (common/: soa/aaf.h), soa_gamefiles (the download read in place).
add_executable(aafdump aafdump.cpp)
target_compile_options(aafdump PRIVATE -ffp-contract=off)
target_link_libraries(aafdump PRIVATE soa_warnings)
target_link_libraries(aafdump PRIVATE soa_models soa_codec soa_gamefiles soa_zip soa_compat)
