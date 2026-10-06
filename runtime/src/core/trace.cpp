// Function tracing for reverse engineering: SOA_TRACE="sym[:dump,...];sym2..." logs a guest
// function's arguments and result on every call, then runs the original code.
//   dump = <offset>=<f|i|x|s>, read from the *first argument* (this) after the call (s: the C string
//   there, e.g. the path CLanguage::PostfixLanguageCodeFilepath(TStaticString<256>&, ...) wrote:
//   SOA_TRACE="_ZN9CLanguage27PostfixLanguageCodeFilepathERN9Framework13TStaticStringILm256EEENS_9tLanguageEb:0=s"), e.g.
//   SOA_TRACE="_ZN21CHomeModelViewManager12SetCameraPosEPNS_13HomeCharacterEb:0x3270=f,0x3274=f"
//   A symbol can also be "0x<ELF vaddr>" (functions without a symbol, e.g. lambdas).
#include <soa/env.h>
#include <cinttypes>
#include <cstdlib>
#include <cstring>
#include <mutex>
#include <sstream>
#include <unordered_map>
#include <vector>

#include "core/abi.h"
#include "core/loader.h"
#include "core/log.h"

namespace soa {
namespace {

struct Dump {
    u64 off;
    char kind;
};
struct Traced {
    std::string name;
    u64 original;
    std::vector<Dump> dumps;
    bool has_ret_override = false;
    float ret_override = 0;  // "sym=value": replace a float result (for experiments)
};
std::unordered_map<u64, Traced> g_traced;  // hooked address -> info

void trace_thunk(Cpu& c) {
    auto it = g_traced.find(c.pc() - 4);
    if (it == g_traced.end()) fatal("trace: unknown hook at %#" PRIx64, c.pc() - 4);
    const Traced& t = it->second;
    GuestArgs a;
    for (int i = 0; i < 8; i++) a.i(c.x(i));
    for (int i = 0; i < 8; i++) a.vecs.push_back(c.v(i));
    char buf[512];
    snprintf(buf, sizeof buf, "x0=%#" PRIx64 " x1=%#" PRIx64 " x2=%#" PRIx64 " x3=%#" PRIx64 " s0=%g s1=%g s2=%g", c.x(0), c.x(1), c.x(2), c.x(3), c.s(0), c.s(1), c.s(2));
    u64 self = c.x(0), lr = c.x(30);
    GuestResult r = guest_call(t.original, a);
    float rf;
    u32 rb = (u32)r.v0.lo;
    memcpy(&rf, &rb, 4);
    std::string dumps;
    for (auto& d : t.dumps) {
        char b[64];
        u64 p = self + d.off;
        if (d.kind == 'f') snprintf(b, sizeof b, " [+%#" PRIx64 "]=%g", d.off, *(float*)p);
        else if (d.kind == 'i') snprintf(b, sizeof b, " [+%#" PRIx64 "]=%d", d.off, *(s32*)p);
        else if (d.kind == 's') snprintf(b, sizeof b, " [+%#" PRIx64 "]=\"%.48s\"", d.off, (const char*)p);
        else snprintf(b, sizeof b, " [+%#" PRIx64 "]=%#" PRIx64, d.off, *(u64*)p);
        dumps += b;
    }
    LOGI("trace", "%s(%s) from %s -> x0=%#" PRIx64 " s0=%g%s", t.name.c_str(), buf, describe_guest_addr(lr).c_str(), r.x0, rf, dumps.c_str());
    c.set_x(0, r.x0);
    c.set_v(0, r.v0);
    if (t.has_ret_override) {
        c.set_s(0, t.ret_override);
        LOGI("trace", "%s: result overridden with %g", t.name.c_str(), t.ret_override);
    }
}

}  // namespace

void install_traces(LoadedLib& lib) {
    const char* spec = env::env_str("SOA_TRACE");
    if (!spec) return;
    std::stringstream ss(spec);
    std::string item;
    while (std::getline(ss, item, ';')) {
        if (item.empty()) continue;
        std::string sym = item.substr(0, item.find(':'));
        Traced t{sym, 0, {}};
        if (sym.find('=') != std::string::npos) {
            t.has_ret_override = true;
            t.ret_override = strtof(sym.c_str() + sym.find('=') + 1, nullptr);
            sym = t.name = sym.substr(0, sym.find('='));
        }
        if (item.find(':') != std::string::npos) {
            std::stringstream ds(item.substr(item.find(':') + 1));
            std::string d;
            while (std::getline(ds, d, ',')) t.dumps.push_back({strtoull(d.c_str(), nullptr, 0), d.back()});
        }
        // "0x<vaddr>": an unnamed function (e.g. a lambda's operator()) by its ELF address
        u64 addr = sym.rfind("0x", 0) == 0 ? lib.base + strtoull(sym.c_str(), nullptr, 16) : lib.sym(sym);
        if (!addr) {
            LOGW("trace", "symbol %s not found", sym.c_str());
            continue;
        }
        t.original = make_original_trampoline(addr);
        if (!t.original) {
            LOGW("trace", "%s: prologue is PC-relative; can't trace", sym.c_str());
            continue;
        }
        g_traced[addr] = t;
        hook_guest_function(addr, strdup(sym.c_str()), trace_thunk);
        LOGI("trace", "tracing %s", sym.c_str());
    }
}

}  // namespace soa
