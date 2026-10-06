# Static-initializer order across translation units (port/PLAN.md 5b, "Gaps fixed"). The natives,
# the selftests and the test hooks register from static initializers, so their order is the link
# order of the objects: the order the source lists are sorted in (port/CMakeLists.txt, D8). On ELF
# (.init_array) the initializers run in link order; on MinGW they are .ctors entries, which
# libgcc's / mingw-w64's __do_global_ctors runs from the LAST to the first (within one object the
# order is the same on both). A Windows build left in link order therefore registered every family
# in reverse: --list-native in another order, the zz_* tests first, aliased natives resolved to the
# other registration, and two test hooks on one symbol chained the other way round (the selftest
# render/device-shader-program reached the draw tests' marking hook instead of the guest).
#
# soa_link_in_init_order(VAR): reverses the source list VAR on MinGW, so that the objects (and an
# archive's members, which a whole-archive link takes in archive order) initialize in the list's
# order there too. Lists whose order doesn't matter needn't call it.
function(soa_link_in_init_order var)
  if(MINGW)
    set(_l ${${var}})
    list(REVERSE _l)
    set(${var} ${_l} PARENT_SCOPE)
  endif()
endfunction()
