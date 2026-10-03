# soa_env: header-only (include/soa/env.h), the programs' environment rule and the table of the
# SOA_* variables that are flags now (docs/environment.md). Every library links it: the runtime,
# the server, the web view (none depends on another for it).
#   soa_env_tests  its unit tests (build/common/soa_env_tests); tests/env_removed.sh checks the
#                  programs' warnings.
add_library(soa_env INTERFACE)
target_include_directories(soa_env INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(soa_env_tests ${CMAKE_CURRENT_SOURCE_DIR}/tests/env_tests.cpp)
target_link_libraries(soa_env_tests PRIVATE soa_env)
