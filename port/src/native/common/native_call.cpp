// Natives calling natives as C++ (native_call.h).
#include "native/common/native_call.h"

#include <cstring>
#include <map>

#include "soaruntime/core/log.h"
#include "native/common/guest_std.h"
#include "native/common/live_check.h"
#include "native/common/native.h"
#include "native/common/test.h"

namespace soa::native {

namespace {
std::vector<NativeCallee*>& registry() {
    static std::vector<NativeCallee*> v;
    return v;
}
}  // namespace

NativeCallee::NativeCallee(const char* subsystem, const char* sym, HostFn expect) : subsystem_(subsystem), sym_(sym), expect_(expect) {
    registry().push_back(this);
}

const std::vector<NativeCallee*>& NativeCallee::all() { return registry(); }

u64 NativeCallee::resolve() const {
    u64 a = guest::sym(sym_);
    addr_.store(a, std::memory_order_relaxed);
    return a;
}

void NativeCallee::resolve_all(const std::set<std::string>& installed, bool allowed) {
    int on = 0;
    for (NativeCallee* c : registry()) {
        c->direct_ = allowed && installed.count(c->sym_) != 0;
        on += c->direct_;
    }
    LOGI("native", "natives calling natives: %d of %zu callees as C++%s", on, registry().size(),
         allowed ? "" : " (off: --live-check, --gdb or SOA_DIRECT_CALLS=0)");
}

}  // namespace soa::native

// Every callee is a registered native of the subsystem it names (a typo or a removed native would
// silently keep the guest path), its HostFn the one the site mirrors when `expect` is given, and in
// --selftest (nothing installed) every site takes the guest path.
NATIVE_TEST("native/direct-callees") {
    using namespace soa;
    using namespace soa::native;
    std::map<std::string, const NativeFunction*> by_sym;
    for (auto& f : registered_natives()) by_sym.emplace(f.symbol, &f);
    t.expect_eq(NativeCallee::all().empty(), false, "callees declared");
    for (NativeCallee* c : NativeCallee::all()) {
        auto it = by_sym.find(c->sym());
        if (it == by_sym.end()) {
            t.fail("%s: not a registered native", c->sym());
            continue;
        }
        const NativeFunction& f = *it->second;
        if (native_subsystem(f) != c->subsystem()) t.fail("%s: registered by %s, declared %s", c->sym(), native_subsystem(f).c_str(), c->subsystem());
        if (f.group) t.fail("%s: a %s hook, not a subsystem's native", c->sym(), f.group);
        if (c->expect()) {
            const live::Entry* e = live::entry_for(c->sym());
            HostFn native = e ? e->run : f.fn;
            if (native != c->expect()) t.fail("%s: registered with another HostFn than the one its call sites mirror", c->sym());
        }
        if (c->direct()) t.fail("%s: direct in --selftest (no native is installed)", c->sym());
        if (!t.sym(c->sym()) || c->addr() != t.sym(c->sym())) t.fail("%s: address", c->sym());
    }
}
