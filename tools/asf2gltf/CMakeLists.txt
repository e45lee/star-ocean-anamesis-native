# asf2gltf: the game's models and animations as glTF 2.0 (tools/asf2gltf/asf2gltf.cpp). Added by the
# repository's CMakeLists.txt (build/tools/asf2gltf/asf2gltf); soa_models (common/: soa/asf.h,
# soa/aaf.h), soa_gamefiles (the download read in place), nlohmann-json (the glTF JSON).
add_executable(asf2gltf asf2gltf.cpp gltf_writer.cpp)
target_compile_options(asf2gltf PRIVATE -ffp-contract=off)
target_link_libraries(asf2gltf PRIVATE soa_warnings)
target_link_libraries(asf2gltf PRIVATE soa_models soa_codec soa_gamefiles soa_zip nlohmann_json::nlohmann_json soa_compat)
