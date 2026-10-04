#pragma once
// Native C++ reimplementations of guest (libSOA.so) functions.
//
// Each entry replaces one guest function, looked up by its mangled symbol: the guest
// function's entry is patched to trap into the host implementation. This is how the port
// moves from "ARM64 code under a JIT" towards native code, one verified function at a time.
#include <cstdio>
#include <string>

#include "core/abi.h"
#include "core/loader.h"

namespace soa {

struct NativeFunction {
    const char* symbol;  // mangled name in libSOA.so, or "@0x..." for a library-relative address
    HostFn fn;
    const char* note;
    // Optional feature switch: the replacement is only installed when this returns true
    // (used for replacements that change behaviour, like enhancements).
    bool (*enabled)() = nullptr;
    // Optional: receives the address of a trampoline that runs the original guest code
    // (make_original_trampoline), for replacements that defer some cases to it. Left 0 when
    // the replacement isn't installed (e.g. in --selftest, where the guest symbol itself is
    // still the original code).
    u64* original = nullptr;
    // Optional group: nullptr = an ordinary native; kGroupRoute = the in-process server route's own
    // hooks (the FakeApiCaller replacements, native/api/fakeapi.cpp), left out with --server HOST.
    const char* group = nullptr;
    // Optional: the C++ that replaces it, as written at the registration (the NATIVE_* macros fill
    // it: the member of NATIVE_METHOD, the function of NATIVE_FUNCTION); shown by the GDB stub's
    // `monitor natives` (runtime/README.md "Debugging the guest with gdb"). nullptr: the note.
    const char* host = nullptr;
};

constexpr const char* kGroupRoute = "route";

// Which registered natives install_native_functions installs (soa --natives):
//   Route: every registered native: the in-process route's hooks plus the port's own (the
//          CPhase::Progress wrapper of the control commands, the tower, the local web pages).
//          Since the rebase's revision 2 (docs/history/PLAN-rebase-370.md) there are no other natives;
//          "all" is accepted as a synonym.
//   None:  nothing (--no-native).
enum class NativeSet { Route, None };
const char* native_set_name(NativeSet s);
// "route" (or "all") / "none" (false for anything else).
bool parse_native_set(const std::string& s, NativeSet& out);

// Registers a replacement (call from a static initializer via NATIVE_FUNCTION).
bool register_native_function(const NativeFunction& f);
// `route` false leaves out the kGroupRoute hooks whatever the set (soa --server HOST: the
// client's own NetworkApiCaller, no FakeApiCaller route).
void install_native_functions(LoadedLib& lib, NativeSet set = NativeSet::Route, bool route = true);
// Prints "symbol<TAB>note" for every registered replacement (soa --list-native).
void list_native_functions(FILE* out);

}  // namespace soa

#define NATIVE_CONCAT2(a, b) a##b
#define NATIVE_CONCAT(a, b) NATIVE_CONCAT2(a, b)
#define NATIVE_REGISTER(sym, fn, note, cond, orig, group, host) \
    static bool NATIVE_CONCAT(native_reg_, __LINE__) = ::soa::register_native_function({sym, fn, note, cond, orig, group, host})
#define NATIVE_FUNCTION(sym, fn, note) NATIVE_REGISTER(sym, fn, note, nullptr, nullptr, nullptr, #fn)
#define NATIVE_FUNCTION_ORIG(sym, fn, note, orig) NATIVE_REGISTER(sym, fn, note, nullptr, orig, nullptr, #fn)
#define NATIVE_FUNCTION_IF(sym, fn, note, cond) NATIVE_REGISTER(sym, fn, note, cond, nullptr, nullptr, #fn)
// The in-process server route's own hooks (group kGroupRoute; not installed with --server HOST).
#define NATIVE_ROUTE_FUNCTION(sym, fn, note) NATIVE_REGISTER(sym, fn, note, nullptr, nullptr, ::soa::kGroupRoute, #fn)
#define NATIVE_ROUTE_FUNCTION_ORIG_IF(sym, fn, note, cond, orig) NATIVE_REGISTER(sym, fn, note, cond, orig, ::soa::kGroupRoute, #fn)
// Like NATIVE_FUNCTION_IF, and stores a trampoline to the original guest code in *orig (u64).
#define NATIVE_FUNCTION_ORIG_IF(sym, fn, note, cond, orig) NATIVE_REGISTER(sym, fn, note, cond, orig, nullptr, #fn)
