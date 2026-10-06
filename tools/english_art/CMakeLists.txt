# english-art: builds the English UI art (soaserver/english_art.h) without a server, with preview
# PNGs (build/tools/english_art/english-art). Added by the repository's CMakeLists.txt when the server
# library is built.
add_executable(english-art english_art.cpp)
target_compile_options(english-art PRIVATE -Wall)
target_link_libraries(english-art PRIVATE soaserver soa_env soa_compat)
