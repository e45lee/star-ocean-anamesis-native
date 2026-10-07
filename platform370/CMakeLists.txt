# libsoaplatform370: the 3.7.0 platform layer (platform370/README.md): the 3.7.0-only Java
# answers, the fmod import, the device clock, the service_stop_day native patch, and the network
# glue (host/port redirect, the AskaActivity HTTP client). soa-emu and soa link it (soa since P1,
# docs/history/PLAN-rebase-370.md).
#
# Added by the repository's CMakeLists.txt (scripts/build.sh: build/platform370/) after
# runtime/, when soa or soa-emu is built (both link it; the root CMakeLists.txt derives SOA_BUILD_PLATFORM370).
#
# Target:
#   soaplatform370  STATIC. Public include dir platform370/include (#include
#                   "platform370/platform370.h"); links soaruntime_iface. No self-registering
#                   objects: platform370::install() registers the pieces, so a plain static link
#                   is enough.

set(SOA_PLATFORM370_DIR ${CMAKE_CURRENT_LIST_DIR})

# platform370 may include the runtime, nothing else of the repository: every quoted #include in
# platform370/ must name a file in platform370/src, platform370/include or runtime/src (or next to
# the including file). Nothing from port/, server/, emulator/.
soa_check_includes(platform370/ DIRS ${SOA_PLATFORM370_DIR}/src ${SOA_PLATFORM370_DIR}/include
                   ALLOW ${SOA_PLATFORM370_DIR}/src ${SOA_PLATFORM370_DIR}/include ${SOA_REPO_DIR}/runtime/src
                         ${SOA_REPO_DIR}/common/include)

file(GLOB SOA_PLATFORM370_SOURCES CONFIGURE_DEPENDS ${SOA_PLATFORM370_DIR}/src/*.cpp)
list(SORT SOA_PLATFORM370_SOURCES)
add_library(soaplatform370 STATIC ${SOA_PLATFORM370_SOURCES})
target_include_directories(soaplatform370 PUBLIC ${SOA_PLATFORM370_DIR}/include PRIVATE ${SOA_PLATFORM370_DIR}/src)
target_link_libraries(soaplatform370 PUBLIC soaruntime_iface soa_text)
target_link_libraries(soaplatform370 PRIVATE soa_guest_code)
