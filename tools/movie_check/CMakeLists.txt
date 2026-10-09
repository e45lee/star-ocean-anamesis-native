# movie_check: decodes a movie with the movie player's decoder (runtime/src/frontend/movie_decoder.cpp,
# compiled in here with the runtime's flags, soa_guest_code: the tool needs no JIT runtime) and writes its pictures / sound for
# tools/movie_compare.py, the proof that the player decodes as the ffmpeg program did. Added by the
# repository's CMakeLists.txt when the runtime is built (build/tools/movie_check/movie_check).
add_executable(movie_check movie_check.cpp ${CMAKE_SOURCE_DIR}/runtime/src/frontend/movie_decoder.cpp)
target_include_directories(movie_check PRIVATE ${CMAKE_SOURCE_DIR}/runtime/include)
target_link_libraries(movie_check PRIVATE soa_guest_code)
target_link_libraries(movie_check PRIVATE soa_zip soa_gamefiles soa::ffmpeg soa_compat)
