# movie_check: decodes a movie with the movie player's decoder (runtime/src/frontend/movie_decoder.cpp,
# compiled in here: the tool needs no JIT runtime) and writes its pictures / sound for
# tools/movie_compare.py, the proof that the player decodes as the ffmpeg program did. Added by the
# repository's CMakeLists.txt when the runtime is built (build/tools/movie_check/movie_check).
add_executable(movie_check movie_check.cpp ${CMAKE_SOURCE_DIR}/runtime/src/frontend/movie_decoder.cpp)
target_include_directories(movie_check PRIVATE ${CMAKE_SOURCE_DIR}/runtime/src)
target_compile_options(movie_check PRIVATE -Wall)
target_link_libraries(movie_check PRIVATE soa_zip soa_gamefiles soa::ffmpeg soa_compat)
