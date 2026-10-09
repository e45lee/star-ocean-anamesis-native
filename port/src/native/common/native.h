#pragma once
// Native C++ reimplementations of guest (libSOA.so) functions.
//
// Each entry replaces one guest function, looked up by its mangled symbol: the guest
// function's entry is patched to trap into the host implementation. This is how the port
// moves from "ARM64 code under a JIT" towards native code, one verified function at a time.
#include <cstdio>
#include <string>
#include <vector>

#include "soaruntime/core/abi.h"
#include "soaruntime/core/loader.h"

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
    // Optional group: nullptr = an ordinary native (a subsystem's bit-exact replacement);
    // kGroupRoute = the in-process server route's own hooks (the FakeApiCaller replacements,
    // native/api/fakeapi.cpp), left out with --server HOST; kGroupPort = the port's own hooks
    // (behaviour the port adds: the control commands, the tower opt-in, the resolution, the local
    // web pages), kept with --natives route.
    const char* group = nullptr;
    // Optional: the C++ that replaces it, as written at the registration (the NATIVE_* macros fill
    // it: the member of NATIVE_METHOD, the function of NATIVE_FUNCTION); shown by the GDB stub's
    // `monitor natives` (runtime/README.md "Debugging the guest with gdb"). nullptr: the note.
    const char* host = nullptr;
    // The source file that registered it (register_native_function fills it from its caller):
    // its folder under native/ is the native's subsystem (--natives-skip, native_subsystem).
    const char* file = nullptr;
};

constexpr const char* kGroupRoute = "route";
constexpr const char* kGroupPort = "port";

// Which registered natives install_native_functions installs (soa --natives):
//   All:   every registered native (the default): the subsystems' replacements of guest code, the
//          in-process route's hooks and the port's own.
//   Route: only the route's hooks (kGroupRoute) and the port's own (kGroupPort): the game's own code
//          all runs under the JIT, as in soa-emu, while the in-process server, the control commands
//          (port_debug: phase N) and the port's options still work. The A/B of a native regression:
//          a bug that goes away with `route` is in a subsystem's natives (--natives-skip narrows it).
//   None:  nothing (--no-native): pure JIT, no in-process route.
enum class NativeSet { All, Route, None };
const char* native_set_name(NativeSet s);
// "all" / "route" / "none" (false for anything else).
bool parse_native_set(const std::string& s, NativeSet& out);

// Registers a replacement (call from a static initializer via NATIVE_FUNCTION); `file` is the
// caller's source file unless f.file is set.
bool register_native_function(const NativeFunction& f, const char* file = __builtin_FILE());
// The subsystem a native belongs to: the folder under port/src/native/ of the file that registered
// it ("render", "math", ...; "" when unknown).
std::string native_subsystem(const NativeFunction& f);
// false (and *err, listing the subsystems that have natives) when a name isn't one of them.
bool check_native_subsystems(const std::vector<std::string>& names, std::string* err);
// `route` false leaves out the kGroupRoute hooks whatever the set (soa --server HOST: the
// client's own NetworkApiCaller, no FakeApiCaller route). `skip`: subsystems left out
// (soa --natives-skip), whatever their group.
void install_native_functions(LoadedLib& lib, NativeSet set = NativeSet::All, bool route = true,
                              const std::vector<std::string>& skip = {});
// Prints "symbol<TAB>note" for every registered replacement (soa --list-native).
void list_native_functions(FILE* out);
// Every registration, in registration order.
const std::vector<NativeFunction>& registered_natives();

// A host library's table of natives (lib_zlib, lib_zstd, lib_jpeg, lib_vorbis, lib_crypto): each entry
// replaces the guest's copy of a library function and keeps the trampoline to it in *orig (the lockstep
// check's guest run).
struct BoundNative {
    const char* sym;
    HostFn fn;
    u64* orig;
};
// Registers every entry, in table order, with the library's note (the file is the caller's: its folder
// is the natives' subsystem).
bool register_bound(const BoundNative* table, size_t n, const char* note, const char* file = __builtin_FILE());
template <size_t N>
bool register_bound(const BoundNative (&table)[N], const char* note, const char* file = __builtin_FILE()) {
    return register_bound(table, N, note, file);
}
// Points every entry's *orig at sym(its symbol), or 0 when sym is null (the selftests run the guest's
// copies through them: lib_*_api.h use_originals).
void bind_originals(const BoundNative* table, size_t n, u64 (*sym)(const char*));
template <size_t N>
void bind_originals(const BoundNative (&table)[N], u64 (*sym)(const char*)) {
    bind_originals(table, N, sym);
}

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
// The port's own hooks (group kGroupPort: kept with --natives route): behaviour the port adds, not
// a bit-exact replacement (docs/client-changes.md lists each).
#define NATIVE_PORT_FUNCTION_ORIG(sym, fn, note, orig) NATIVE_REGISTER(sym, fn, note, nullptr, orig, ::soa::kGroupPort, #fn)
#define NATIVE_PORT_FUNCTION_IF(sym, fn, note, cond) NATIVE_REGISTER(sym, fn, note, cond, nullptr, ::soa::kGroupPort, #fn)
#define NATIVE_PORT_FUNCTION_ORIG_IF(sym, fn, note, cond, orig) NATIVE_REGISTER(sym, fn, note, cond, orig, ::soa::kGroupPort, #fn)
// Like NATIVE_FUNCTION_IF, and stores a trampoline to the original guest code in *orig (u64).
#define NATIVE_FUNCTION_ORIG_IF(sym, fn, note, cond, orig) NATIVE_REGISTER(sym, fn, note, cond, orig, nullptr, #fn)
