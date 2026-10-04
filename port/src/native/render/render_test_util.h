// render_test_util.h: helpers for the layout tests of render, scene and anim (port/PLAN.md task 6, types
// first): guest addresses and vtables, virtual calls, and running a check on the game thread at a frame
// boundary, where the scene graph and the render objects are consistent.
//
// The live objects (the ObjectManager, its painting lists, the models, the render device) belong to the
// game's threads. A test that reads them runs its body through on_frame(): the body runs on the game
// thread at the start of Aska::ObjectManager::OnPrePaint (a NATIVE_TEST_HOOK, installed only in
// --selftest), before that frame's painting lists are built, while the test thread waits. The render
// thread may still be drawing the previous frame then: read what it doesn't write (pointers, vtables,
// counts, the objects' parameters), and compare with the guest's own getters called in the same body.
#ifndef SOA_NATIVE_RENDER_TEST_UTIL_H
#define SOA_NATIVE_RENDER_TEST_UTIL_H

#include <cstdint>
#include <functional>
#include <initializer_list>

#include "core/cpu.h"
#include "core/loader.h"
#include "native/common/test.h"

namespace soa::native::render::testutil {

// The guest object at ELF vaddr `vaddr` (a global).
template <typename T>
T* at_vaddr(u64 vaddr) {
    return reinterpret_cast<T*>(main_lib()->base + vaddr);
}
// The value of a pointer global at `vaddr` (e.g. kVaddrGlobalObjectManager).
template <typename T>
T* global_ptr(u64 vaddr) {
    return *reinterpret_cast<T**>(main_lib()->base + vaddr);
}
// The vtable pointer an object of the class with vtable symbol `ztv` (_ZTV...) holds.
inline const void* vtable_of(TestContext& t, const char* ztv) { return reinterpret_cast<const void*>(t.sym(ztv) + 0x10); }
// The address of vtable slot `slot` of `obj` (the function a virtual call reaches).
inline u64 vslot(const void* obj, int slot) { return (*reinterpret_cast<const u64* const*>(obj))[slot]; }
// Calls vtable slot `slot` of the guest object `obj` with integer arguments.
u64 vcall(const void* obj, int slot, std::initializer_list<u64> rest = {});
// A guest function without arguments (t.call(name, {}) would be ambiguous).
inline u64 call0(TestContext& t, const char* name) { return guest_call(t.sym(name), std::initializer_list<u64>{}); }
// The guest function's address for `obj`'s class: true when `obj`'s vtable is `ztv`'s.
inline bool has_vtable(TestContext& t, const void* obj, const char* ztv) {
    return obj && *reinterpret_cast<const void* const*>(obj) == vtable_of(t, ztv);
}

// Runs `body` on the game thread at the next Aska::ObjectManager::OnPrePaint and waits for it (at most
// `timeout_ms`). Returns false (and fails the test) when no frame came: the game isn't painting.
bool on_frame(TestContext& t, const std::function<void()>& body, int timeout_ms = 20000);

}  // namespace soa::native::render::testutil

#endif  // SOA_NATIVE_RENDER_TEST_UTIL_H
