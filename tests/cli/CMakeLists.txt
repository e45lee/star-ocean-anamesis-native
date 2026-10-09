# soa_cli_tests (build/tests/cli/soa_cli_tests; T0 `cli`): the five programs' command lines on CLI11
# against the hand-written parsers they replaced (legacy.cpp), every option (cli_tests.cpp). It
# compiles the programs' cli.cpp files themselves: they depend only on CLI11 and the config types'
# headers.
add_executable(soa_cli_tests ${CMAKE_CURRENT_SOURCE_DIR}/cli_tests.cpp ${CMAKE_CURRENT_SOURCE_DIR}/legacy.cpp
               ${SOA_REPO_DIR}/port/src/core/cli.cpp ${SOA_REPO_DIR}/server/app/cli.cpp ${SOA_REPO_DIR}/emulator/src/cli.cpp
               ${SOA_REPO_DIR}/emulator-viewer/src/cli.cpp ${SOA_REPO_DIR}/webview/tools/cli.cpp)
# (port/src: its core/ is soa's; runtime/include for soaruntime/app/host.h and soaruntime/app/cli.h)
target_include_directories(soa_cli_tests PRIVATE ${SOA_REPO_DIR} ${SOA_REPO_DIR}/port/src ${SOA_REPO_DIR}/runtime/include
                           ${SOA_REPO_DIR}/platform370/include ${SOA_REPO_DIR}/server/include)
target_link_libraries(soa_cli_tests PRIVATE soa_warnings)
target_link_libraries(soa_cli_tests PRIVATE soa_env soa_compat)
