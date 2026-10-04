#pragma once
// The live check of the resource natives (soa --live-check resource[:every=N][:budget=N][:only=..][:out=FILE]).
//
// A shadow check (native/common/shadow_check.h): the resource list is shared by the game thread (Run,
// Add, Remove), the loader threads and the downloader, all under CResourceManager::m_mutex. The
// read-only members (the searches, IsReady*, the counts) run the guest original on the real object
// right after the native (check_getter: a difference a rerun doesn't reproduce is a race). Run, the
// one mutator, is checked under the manager's own (recursive) lock against the guest original on a
// shadow manager (resource_manager.cpp).
#include "native/common/shadow_check.h"

namespace soa::native::resource {

live::ShadowFamily& family();
struct CheckedFn : live::ShadowFn {
    explicit CheckedFn(const char* s) : ShadowFn(family(), s) {}
};

}  // namespace soa::native::resource
