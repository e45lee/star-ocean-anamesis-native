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

#include "core/log.h"

namespace soa {

static std::vector<NativeFunction>& registry() {
    static std::vector<NativeFunction> r;
    return r;
}

bool register_native_function(const NativeFunction& f) {
    registry().push_back(f);
    return true;
}

void list_native_functions(FILE* out) {
    for (auto& f : registry()) fprintf(out, "%s\t%s%s\n", f.symbol, f.note ? f.note : "", f.enabled ? " [conditional]" : "");
}

// Size of the function at addr from the symbol table (the largest symbol there), or 0.
static u64 function_size(const LoadedLib& lib, u64 addr) {
    auto it = std::lower_bound(lib.sorted_syms.begin(), lib.sorted_syms.end(), addr, [](const LoadedLib::Sym& s, u64 a) { return s.addr < a; });
    u64 size = 0;
    for (; it != lib.sorted_syms.end() && it->addr == addr; ++it) size = std::max(size, it->size);
    return size;
}

const char* native_set_name(NativeSet s) { return s == NativeSet::Route ? "route" : "none"; }

bool parse_native_set(const std::string& s, NativeSet& out) {
    if (s == "route" || s == "all") out = NativeSet::Route;
    else if (s == "none") out = NativeSet::None;
    else return false;
    return true;
}

static bool in_set(const NativeFunction& f, NativeSet set, bool with_route) {
    if (set == NativeSet::None) return false;
    bool route = f.group && strcmp(f.group, kGroupRoute) == 0;
    return with_route || !route;
}

void install_native_functions(LoadedLib& lib, NativeSet set, bool with_route) {
    int n = 0;
    std::set<u64> done;
    std::map<u64, u64> trampolines;
    std::set<u64> targets;  // every address that gets a replacement
    for (auto& f : registry()) {
        if (!in_set(f, set, with_route)) continue;
        if (f.enabled && !f.enabled()) continue;
        if (u64 a = f.symbol[0] == '@' ? lib.base + strtoull(f.symbol + 1, nullptr, 0) : lib.sym(f.symbol)) targets.insert(a);
    }
    for (auto& f : registry()) {
        if (!in_set(f, set, with_route)) continue;
        if (f.enabled && !f.enabled()) continue;
        // "@0x..." names a library-relative address (for functions without exported symbols).
        u64 addr = f.symbol[0] == '@' ? lib.base + strtoull(f.symbol + 1, nullptr, 0) : lib.sym(f.symbol);
        if (addr && !done.insert(addr).second) {  // aliases (e.g. C1/C2 constructors)
            if (f.original && trampolines.count(addr)) *f.original = trampolines[addr];
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
        hook_guest_function(addr, f.symbol, f.fn);
        n++;
    }
    LOGI("native", "%d guest functions replaced by native code (--natives %s%s)", n, native_set_name(set),
         with_route ? "" : ", without the FakeApiCaller route");
}

}  // namespace soa
