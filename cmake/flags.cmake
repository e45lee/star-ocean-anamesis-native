# The compile flags and the layering checks of the repository's own targets, in one place (included
# once by the root CMakeLists.txt, after cmake/deps.cmake). Dependencies keep their own flags.
#
# INTERFACE targets a target links PRIVATE (they carry flags only, nothing to link; soa_httplib_win below):
#   soa_warnings    every target of ours: -Wall without the unused-parameter / unused-function
#                   warnings (guest-ABI callbacks keep unused parameters; header helpers go unused)
#   soa_guest_code  code that reads and writes guest memory (the runtime, platform370, the port, the
#                   emulator, the viewer, movie_check): -fno-strict-aliasing (guest structures are read
#                   through other types) and -mcx16 (16-byte compare-and-swap: the guest's 128-bit
#                   exclusive pairs); soa_warnings too
# Only the port adds -ffp-contract=off (port/CMakeLists.txt: the natives' float rounding), and the
# server library -fno-strict-aliasing without -mcx16 (server/CMakeLists.txt): it handles no guest
# memory, and soa links it, so its code stays as it was.
add_library(soa_warnings INTERFACE)
target_compile_options(soa_warnings INTERFACE -Wall -Wno-unused-parameter -Wno-unused-function)

add_library(soa_guest_code INTERFACE)
target_compile_options(soa_guest_code INTERFACE -fno-strict-aliasing -mcx16)
target_link_libraries(soa_guest_code INTERFACE soa_warnings)

# soa_httplib_win: what a target that includes cpp-httplib needs on Windows: the Windows 10 API
# (CreateFile2, GetAddrInfoEx; MinGW-w64's default _WIN32_WINNT is older). soanet and soa-server.
add_library(soa_httplib_win INTERFACE)
if(WIN32)
  target_compile_definitions(soa_httplib_win INTERFACE _WIN32_WINNT=0x0A00)
endif()

# soa_check_includes(NAME DIRS <dir>... ALLOW <dir>... [EXTRA <regex>])
# Every #include of the sources under DIRS (recursive) must name a file under one of the ALLOW
# include roots, or one relative to the including file inside DIRS / ALLOW: quoted includes always, angle
# includes when they name a file of the repository (under one of SOA_INCLUDE_ROOTS: a library's
# public headers or sources; else they are a dependency's or the system's). EXTRA: a regex of
# quoted includes that are a dependency's (e.g. "^dynarmic/"). A violation fails the configure
# (AGENTS.md "Layering"). The include path of each target is the backstop; this names the file.
set(SOA_INCLUDE_ROOTS
  ${SOA_REPO_DIR}/common/include ${SOA_REPO_DIR}/common/win32
  ${SOA_REPO_DIR}/runtime/include ${SOA_REPO_DIR}/runtime/src
  ${SOA_REPO_DIR}/platform370/include ${SOA_REPO_DIR}/platform370/src
  ${SOA_REPO_DIR}/server/include ${SOA_REPO_DIR}/server/src ${SOA_REPO_DIR}/server
  ${SOA_REPO_DIR}/webview/include ${SOA_REPO_DIR}/webview/src
  ${SOA_REPO_DIR}/port/src
  ${SOA_REPO_DIR}/emulator/src
  ${SOA_REPO_DIR}/emulator-viewer/src)
function(soa_check_includes name)
  cmake_parse_arguments(PARSE_ARGV 1 A "" "EXTRA" "DIRS;ALLOW")
  set(_files "")
  foreach(_d ${A_DIRS})
    file(GLOB_RECURSE _f CONFIGURE_DEPENDS ${_d}/*.h ${_d}/*.hpp ${_d}/*.cpp ${_d}/*.c ${_d}/*.inc)
    list(APPEND _files ${_f})
  endforeach()
  foreach(_f ${_files})
    get_filename_component(_dir ${_f} DIRECTORY)
    file(STRINGS ${_f} _incs REGEX "^[ \t]*#[ \t]*include[ \t]*[\"<]")
    foreach(_l ${_incs})
      string(REGEX REPLACE "^[ \t]*#[ \t]*include[ \t]*([\"<])([^\">]*)[\">].*$" "\\1\\2" _q "${_l}")
      string(SUBSTRING "${_q}" 0 1 _kind)
      string(SUBSTRING "${_q}" 1 -1 _inc)
      if(_kind STREQUAL "\"" AND EXISTS ${_dir}/${_inc})
        # next to the including file, or reached with "..": it must stay inside DIRS / ALLOW
        get_filename_component(_abs ${_dir}/${_inc} ABSOLUTE)
        set(_in OFF)
        foreach(_r ${A_DIRS} ${A_ALLOW})
          string(FIND "${_abs}" "${_r}/" _at)
          if(_at EQUAL 0)
            set(_in ON)
            break()
          endif()
        endforeach()
        if(NOT _in)
          message(FATAL_ERROR "${name} must not include \"${_inc}\" (${_f}): it leaves ${name} (it includes only ${A_ALLOW})")
        endif()
        continue()
      endif()
      if(_inc MATCHES "(^|/)\\.\\.(/|$)")
        message(FATAL_ERROR "${name} must not include \"${_inc}\" (${_f}): no \"..\" out of an include root")
      endif()
      set(_ok OFF)
      foreach(_r ${A_ALLOW})
        if(EXISTS ${_r}/${_inc})
          set(_ok ON)
          break()
        endif()
      endforeach()
      if(_ok)
        continue()
      endif()
      if(_kind STREQUAL "\"")
        if(A_EXTRA AND _inc MATCHES "${A_EXTRA}")
          continue()
        endif()
        message(FATAL_ERROR "${name} must not include \"${_inc}\" (${_f}): it includes only ${A_ALLOW}")
      endif()
      foreach(_r ${SOA_INCLUDE_ROOTS})
        if(EXISTS ${_r}/${_inc})
          message(FATAL_ERROR "${name} must not include <${_inc}> (${_f}, from ${_r}): it includes only ${A_ALLOW}")
        endif()
      endforeach()
    endforeach()
  endforeach()
endfunction()
