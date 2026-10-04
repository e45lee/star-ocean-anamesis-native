# IJG libjpeg 9 (the library only), static, from the source tarball FetchContent unpacks
# (cmake/deps.cmake: JPEG9_SOURCE_DIR): 9b, the version the game bundles (port/src/native/lib_jpeg);
# vcpkg has only libjpeg-turbo, whose output isn't bit-exact with IJG's. The sources are
# makefile.ansi's LIBSOURCES with the jmemnobs memory manager, as the tarball's ./configure builds
# libjpeg.so.9. jconfig.h is ours (next to this file).
#
# Target: soa::jpeg9 (STATIC). Its include dirs come first for every consumer, ahead of any system
# jpeglib.h (libjpeg-turbo's).
set(_jpeg9_sources
  jaricom.c jcapimin.c jcapistd.c jcarith.c jccoefct.c jccolor.c
  jcdctmgr.c jchuff.c jcinit.c jcmainct.c jcmarker.c jcmaster.c
  jcomapi.c jcparam.c jcprepct.c jcsample.c jctrans.c jdapimin.c
  jdapistd.c jdarith.c jdatadst.c jdatasrc.c jdcoefct.c jdcolor.c
  jddctmgr.c jdhuff.c jdinput.c jdmainct.c jdmarker.c jdmaster.c
  jdmerge.c jdpostct.c jdsample.c jdtrans.c jerror.c jfdctflt.c
  jfdctfst.c jfdctint.c jidctflt.c jidctfst.c jidctint.c jquant1.c
  jquant2.c jutils.c jmemmgr.c
  jmemnobs.c)
list(TRANSFORM _jpeg9_sources PREPEND ${JPEG9_SOURCE_DIR}/)
add_library(jpeg9 STATIC ${_jpeg9_sources})
add_library(soa::jpeg9 ALIAS jpeg9)
# jconfig.h (ours) and the public headers (jpeglib.h, jmorecfg.h, jerror.h) from the tarball.
target_include_directories(jpeg9 BEFORE PUBLIC ${CMAKE_CURRENT_LIST_DIR} ${JPEG9_SOURCE_DIR})
set_target_properties(jpeg9 PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_compile_options(jpeg9 PRIVATE $<$<C_COMPILER_ID:GNU,Clang>:-w>)
