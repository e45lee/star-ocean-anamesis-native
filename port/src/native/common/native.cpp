#include "native/common/native.h"
#include "native/common/trampoline.h"

#include <algorithm>
#include <cinttypes>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <set>
#include <vector>

#include "core/gdbstub.h"
#include "core/log.h"
#include "native/common/live_check.h"
#include "native/common/native_call.h"
#include "native/common/test.h"

namespace soa {

static std::vector<NativeFunction>& registry() {
    static std::vector<NativeFunction> r;
    return r;
}

bool register_native_function(const NativeFunction& f, const char* file) {
    registry().push_back(f);
    if (!registry().back().file) registry().back().file = file;
    return true;
}

std::string native_subsystem(const NativeFunction& f) {
    if (!f.file) return "";
    std::string p = f.file;
    std::replace(p.begin(), p.end(), '\\', '/');
    size_t at = p.rfind("/native/");
    if (at == std::string::npos) return "";
    at += 8;
    size_t end = p.find('/', at);
    return end == std::string::npos ? "" : p.substr(at, end - at);
}

bool check_native_subsystems(const std::vector<std::string>& names, std::string* err) {
    std::set<std::string> have;
    for (auto& f : registry()) have.insert(native_subsystem(f));
    have.erase("");
    for (auto& n : names) {
        if (have.count(n)) continue;
        std::string l;
        for (auto& h : have) l += (l.empty() ? "" : ", ") + h;
        *err = "no natives in a subsystem \"" + n + "\" (subsystems with natives: " + l + ")";
        return false;
    }
    return true;
}

const std::vector<NativeFunction>& registered_natives() { return registry(); }

bool register_bound(const BoundNative* table, size_t n, const char* note, const char* file) {
    for (size_t i = 0; i < n; i++) register_native_function({table[i].sym, table[i].fn, note, nullptr, table[i].orig}, file);
    return true;
}

void bind_originals(const BoundNative* table, size_t n, u64 (*sym)(const char*)) {
    for (size_t i = 0; i < n; i++) *table[i].orig = sym ? sym(table[i].sym) : 0;
}

void list_native_functions(FILE* out) {
    for (auto& f : registry()) fprintf(out, "%s\t%s%s\n", f.symbol, f.note ? f.note : "", f.enabled ? " [conditional]" : "");
}

// The C++ a registration names, as `monitor natives` shows it: "&C::M" / "::soa::f" -> "C::M" / "soa::f"
// (kept for the run: the hook keeps the pointer).
static const char* host_name(const char* written) {
    std::string s = written;
    while (!s.empty() && (s[0] == '&' || s[0] == ' ')) s.erase(0, 1);
    if (s.rfind("::", 0) == 0) s.erase(0, 2);
    return s == written ? written : strdup(s.c_str());
}

// Size of the function at addr from the symbol table (the largest symbol there), or 0.
static u64 function_size(const LoadedLib& lib, u64 addr) {
    auto it = std::lower_bound(lib.sorted_syms.begin(), lib.sorted_syms.end(), addr, [](const LoadedLib::Sym& s, u64 a) { return s.addr < a; });
    u64 size = 0;
    for (; it != lib.sorted_syms.end() && it->addr == addr; ++it) size = std::max(size, it->size);
    return size;
}

const char* native_set_name(NativeSet s) { return s == NativeSet::All ? "all" : s == NativeSet::Route ? "route" : "none"; }

bool parse_native_set(const std::string& s, NativeSet& out) {
    if (s == "all") out = NativeSet::All;
    else if (s == "route") out = NativeSet::Route;
    else if (s == "none") out = NativeSet::None;
    else return false;
    return true;
}

static bool in_group(const NativeFunction& f, const char* g) { return f.group && strcmp(f.group, g) == 0; }

static bool in_set(const NativeFunction& f, NativeSet set, bool with_route, const std::vector<std::string>& skip) {
    if (set == NativeSet::None) return false;
    if (!with_route && in_group(f, kGroupRoute)) return false;
    if (set == NativeSet::Route && !in_group(f, kGroupRoute) && !in_group(f, kGroupPort)) return false;
    if (!skip.empty() && std::find(skip.begin(), skip.end(), native_subsystem(f)) != skip.end()) return false;
    return true;
}

void install_native_functions(LoadedLib& lib, NativeSet set, bool with_route, const std::vector<std::string>& skip) {
    int n = 0, skipped = 0;
    std::set<u64> done;
    std::map<u64, u64> trampolines;
    std::set<u64> targets;  // every address that gets a replacement
    std::set<u64> installed_at;
    std::set<std::string> installed;  // the symbols installed (native_call.h)
    for (auto& f : registry()) {
        if (!in_set(f, set, with_route, skip)) continue;
        if (f.enabled && !f.enabled()) continue;
        if (u64 a = f.symbol[0] == '@' ? lib.base + strtoull(f.symbol + 1, nullptr, 0) : lib.sym(f.symbol)) targets.insert(a);
    }
    for (auto& f : registry()) {
        if (!in_set(f, set, with_route, skip)) {
            skipped += !skip.empty() && in_set(f, set, with_route, {});
            continue;
        }
        if (f.enabled && !f.enabled()) continue;
        // "@0x..." names a library-relative address (for functions without exported symbols).
        u64 addr = f.symbol[0] == '@' ? lib.base + strtoull(f.symbol + 1, nullptr, 0) : lib.sym(f.symbol);
        if (addr && !done.insert(addr).second) {  // aliases (e.g. C1/C2 constructors)
            if (f.original && trampolines.count(addr)) *f.original = trampolines[addr];
            if (installed_at.count(addr)) installed.insert(f.symbol);
            continue;
        }
        if (!addr) {
            LOGW("native", "symbol %s not found; replacement not installed", f.symbol);
            continue;
        }
        // The patch is two instructions (SVC; RET): on a 4-byte function it also overwrites the
        // next function's first instruction. When the short function is a lone RET, or a tail
        // branch to another replaced function, its guest code does the same job, so it's left
        // alone; otherwise it isn't replaced (warning).
        if (u64 size = function_size(lib, addr); size && size < 8) {
            u32 insn = *(const u32*)addr;
            bool is_ret = insn == 0xd65f03c0;
            bool to_replaced = false;
            if ((insn & 0xfc000000) == 0x14000000) {
                s64 off = (s64)((u64)(insn & 0x3ffffff) << 38) >> 36;  // imm26 * 4, sign-extended
                to_replaced = targets.count(addr + off) != 0;
            }
            if (is_ret || to_replaced) {
                LOGI("native", "%s is a %" PRIu64 "-byte %s; left as guest code", f.symbol, size, is_ret ? "RET" : "branch to a replaced function");
                continue;
            }
            // Anything else would overwrite the next function's entry: leave it to the guest.
            LOGW("native", "%s is only %" PRIu64 " bytes; replacement not installed", f.symbol, size);
            continue;
        }
        if (f.original) {
            *f.original = trampolines[addr] = make_relocated_trampoline(addr);  // (PC-relative prologues relocated: trampoline.h)
            if (!*f.original) {
                LOGW("native", "%s: prologue can't be relocated; replacement not installed", f.symbol);
                continue;
            }
        }
        hook_guest_function(addr, f.symbol, f.fn, f.host ? host_name(f.host) : f.note);
        installed_at.insert(addr);
        installed.insert(f.symbol);
        n++;
    }
    std::string skipped_note;
    for (auto& s : skip) skipped_note += (skipped_note.empty() ? ", --natives-skip " : ",") + s;
    if (!skip.empty()) skipped_note += " (" + std::to_string(skipped) + " left to the guest)";
    LOGI("native", "%d guest functions replaced by native code (--natives %s%s%s)", n, native_set_name(set),
         with_route ? "" : ", without the FakeApiCaller route", skipped_note.c_str());
    // Natives calling natives as C++ (native_call.h): only callees installed here, and none while a live
    // check (applied before this), the GDB stub (breakpoints on natives) or SOA_DIRECT_CALLS=0 needs every
    // call to go through the guest entry.
    native::NativeCallee::resolve_all(installed, direct_host_calls() && !g_gdb_enabled && !live::any_family_on());
}

}  // namespace soa

// --natives-skip and --natives route rely on these: every registration names its subsystem (the
// folder of the file that registered it), and native/common/ registers only the port's own hooks.
NATIVE_TEST("native/registry-groups") {
    using namespace soa;
    std::map<std::string, int> per;
    for (auto& f : registered_natives()) {
        std::string s = native_subsystem(f);
        per[s]++;
        if (s.empty()) t.fail("%s: registered from %s, outside port/src/native/<subsystem>/", f.symbol, f.file ? f.file : "?");
        bool own = f.group && (strcmp(f.group, kGroupRoute) == 0 || strcmp(f.group, kGroupPort) == 0);
        if (s == "common" && !own) t.fail("%s: a native in native/common/ that isn't one of the port's own hooks", f.symbol);
        // the sets: all = everything, route = the route's and the port's own, none = nothing; --server HOST
        // drops the route's; a skipped subsystem is out of every set
        bool route = f.group && strcmp(f.group, kGroupRoute) == 0;
        if (!in_set(f, NativeSet::All, true, {}) || in_set(f, NativeSet::None, true, {})) t.fail("%s: all / none", f.symbol);
        if (in_set(f, NativeSet::Route, true, {}) != own) t.fail("%s: route", f.symbol);
        if (in_set(f, NativeSet::All, false, {}) == route) t.fail("%s: --server HOST", f.symbol);
        if (!s.empty() && in_set(f, NativeSet::All, true, {s})) t.fail("%s: --natives-skip %s", f.symbol, s.c_str());
    }
    t.expect_eq(per.size() > 10, true, "natives in many subsystems");
    std::string err;
    t.expect_eq(check_native_subsystems({"render", "math"}, &err), true, "render, math have natives");
    t.expect_eq(check_native_subsystems({"no_such_subsystem"}, &err), false, "an unknown subsystem");
    NativeSet s;
    t.expect_eq(parse_native_set("all", s) && s == NativeSet::All, true, "all");
    t.expect_eq(parse_native_set("route", s) && s == NativeSet::Route, true, "route");
    t.expect_eq(parse_native_set("none", s) && s == NativeSet::None, true, "none");
    t.expect_eq(parse_native_set("everything", s), false, "a bad word");
}
