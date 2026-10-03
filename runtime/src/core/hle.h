#pragma once
// Registry of HLE symbols (imports of the guest library resolved to host thunks or data).
#include <functional>
#include <string>
#include <unordered_map>

#include "core/abi.h"

namespace soa {

class Hle {
public:
    static Hle& get();

    void fn(const char* name, HostFn f) {
        syms_[name] = make_thunk(name, f);
        fns_[name] = f;
    }
    void data(const char* name, void* p) {
        syms_[name] = (u64)(uintptr_t)p;
        fns_.erase(name);
    }
    // Extension point: binds the import `name` to `f` (replacing a built-in thunk or adding a new
    // one); returns the host function it replaces (nullptr when `name` was data, unknown, or a
    // missing() stub), so `f` can delegate to it. Imports are bound when a library is loaded, so
    // override before load_library(): from an hle_add_registrar() callback, or after hle_init().
    HostFn override_fn(const std::string& name, HostFn f);
    // The host function the import `name` is bound to (fn / override_fn); nullptr when none.
    HostFn host_fn(const std::string& name) const {
        auto it = fns_.find(name);
        return it == fns_.end() ? nullptr : it->second;
    }
    // Returns 0 if not found.
    u64 lookup(const std::string& name) const {
        auto it = syms_.find(name);
        return it == syms_.end() ? 0 : it->second;
    }
    // Resolves a name to a thunk that logs + aborts when called (for unimplemented imports).
    u64 missing(const std::string& name);

private:
    std::unordered_map<std::string, u64> syms_;
    std::unordered_map<std::string, HostFn> fns_;
};

// Each HLE module provides a registration function; all are called from hle_init().
void hle_init();
// Extension point: `fn` runs at the end of hle_init(), after the built-in modules below, in
// registration order; for a host program's own imports or replacements (Hle::fn, Hle::data,
// Hle::override_fn). Register before hle_init(), e.g. from a static initializer; returns true.
bool hle_add_registrar(std::function<void(Hle&)> fn);
void register_libc(Hle&);
void register_libc_stdio(Hle&);
void register_libc_thread(Hle&);
void register_libc_misc(Hle&);
void register_libm(Hle&);
void register_gles(Hle&);
void register_egl(Hle&);
void register_android(Hle&);
void register_opensles(Hle&);
#ifdef _WIN32
void register_libc_win32(Hle&);  // hle/libc_win32.cpp: what differs on a Windows host
#endif

// pthread_getspecific of a guest key on the calling thread (libc_thread.cpp), for native code.
u64 guest_getspecific(u32 key);

}  // namespace soa

#define HLE_WRAP(h, f) (h).fn(#f, ::soa::wrap<&::f>())
#define HLE_WRAP_T(h, name, type, f) (h).fn(name, ::soa::wrap<static_cast<type>(&f)>())
