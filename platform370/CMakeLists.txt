# libsoaplatform370: the 3.7.0 platform layer (platform370/README.md): the 3.7.0-only Java
# answers, the fmod import, the device clock, the service_stop_day native patch, and the network
# glue (host/port redirect, the AskaActivity HTTP client). soa-emu links it; soa will (P1,
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
file(GLOB_RECURSE _p370_check CONFIGURE_DEPENDS ${SOA_PLATFORM370_DIR}/src/* ${SOA_PLATFORM370_DIR}/include/*)
foreach(_f ${_p370_check})
  get_filename_component(_dir ${_f} DIRECTORY)
  file(STRINGS ${_f} _incs REGEX "^[ \t]*#[ \t]*include[ \t]*\"")
  foreach(_l ${_incs})
    string(REGEX REPLACE "^[ \t]*#[ \t]*include[ \t]*\"([^\"]*)\".*$" "\\1" _inc "${_l}")
    if(_inc MATCHES "\\.\\." OR NOT (EXISTS ${SOA_PLATFORM370_DIR}/src/${_inc} OR EXISTS ${SOA_PLATFORM370_DIR}/include/${_inc}
                                     OR EXISTS ${SOA_REPO_DIR}/runtime/src/${_inc} OR EXISTS ${SOA_REPO_DIR}/common/include/${_inc}
                                     OR EXISTS ${_dir}/${_inc}))
      message(FATAL_ERROR "platform370/ must not include \"${_inc}\" (${_f}): it includes only platform370/, runtime/src and common/include")
    endif()
  endforeach()
endforeach()

file(GLOB SOA_PLATFORM370_SOURCES CONFIGURE_DEPENDS ${SOA_PLATFORM370_DIR}/src/*.cpp)
list(SORT SOA_PLATFORM370_SOURCES)
add_library(soaplatform370 STATIC ${SOA_PLATFORM370_SOURCES})
target_include_directories(soaplatform370 PUBLIC ${SOA_PLATFORM370_DIR}/include PRIVATE ${SOA_PLATFORM370_DIR}/src)
target_link_libraries(soaplatform370 PUBLIC soaruntime_iface)
target_compile_options(soaplatform370 PRIVATE -Wall -Wno-unused-parameter -fno-strict-aliasing -mcx16)
