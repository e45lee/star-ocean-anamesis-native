# soa_cli_tests (build/tests/cli/soa_cli_tests; T0 `cli`): the four programs' command lines on CLI11
# against the hand-written parsers they replaced (legacy.cpp), every option (cli_tests.cpp). It
# compiles the programs' cli.cpp files themselves: they depend only on CLI11 and the config types'
# headers.
add_executable(soa_cli_tests ${CMAKE_CURRENT_SOURCE_DIR}/cli_tests.cpp ${CMAKE_CURRENT_SOURCE_DIR}/legacy.cpp
               ${SOA_REPO_DIR}/port/src/core/cli.cpp ${SOA_REPO_DIR}/server/app/cli.cpp ${SOA_REPO_DIR}/emulator/src/cli.cpp
               ${SOA_REPO_DIR}/emulator-viewer/src/cli.cpp)
# (port/src first: its core/ is soa's; runtime/src for app/host.h and app/cli.h)
target_include_directories(soa_cli_tests PRIVATE ${SOA_REPO_DIR} ${SOA_REPO_DIR}/port/src ${SOA_REPO_DIR}/runtime/src
                           ${SOA_REPO_DIR}/platform370/include ${SOA_REPO_DIR}/server/include)
target_compile_options(soa_cli_tests PRIVATE -Wall -Wno-unused-parameter)
target_link_libraries(soa_cli_tests PRIVATE soa_env soa_compat)
