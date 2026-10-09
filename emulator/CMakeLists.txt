# soa-emu: the 3.7.0 online client (work/libSOA-3.7.0.so + the 3.7.0 APK), unmodified, under the
# JIT host runtime (../runtime) with the 3.7.0 platform layer (../platform370). No natives: it never
# links port/src/native. emulator/README.md.
# Added by the repository's CMakeLists.txt after ../runtime and ../platform370 (scripts/build.sh:
# build/emulator/soa-emu).

# src/ is main.cpp only: the command line -> platform370::Config, the data dir, the APK and library,
# the runtime bring-up. platform370 registers its pieces from platform370::install (no static
# initializers), so it links as a plain library; the runtime archive is linked whole (its
# self-registering objects).
file(GLOB SOA_EMU_SOURCES CONFIGURE_DEPENDS src/*.cpp)
add_executable(soa-emu ${SOA_EMU_SOURCES})
target_include_directories(soa-emu PRIVATE src)
target_link_libraries(soa-emu PRIVATE soa_guest_code)
# the emulator: the runtime, platform370 and common/include (cmake/flags.cmake); nobody else includes emulator/
soa_check_includes(emulator/ DIRS ${CMAKE_CURRENT_SOURCE_DIR}/src
                   ALLOW ${CMAKE_CURRENT_SOURCE_DIR}/src ${SOA_REPO_DIR}/runtime/include ${SOA_REPO_DIR}/platform370/include
                         ${SOA_REPO_DIR}/common/include)
target_link_libraries(soa-emu PRIVATE soaplatform370 soaruntime_app $<LINK_LIBRARY:WHOLE_ARCHIVE,soaruntime>)
