// Differential tests of libcxx_shared_count.cpp against the 3.7.0 guest (--selftest libcxx/): the same
// random sequences of count operations on two control blocks, one through the guest's out-of-line
// members, one through the natives; the counts, results and the virtual callbacks (slots 2 and 4,
// counting guest functions) must agree after every step.
#include <cstring>

#include "soaruntime/core/cpu.h"
#include "native/common/test.h"
#include "native/libcxx/libcxx_layout.h"

namespace soa::native::libcxx {
namespace {

// A control block with two counters the fake vtable's slots bump: +0x18 for __on_zero_shared,
// +0x20 for __on_zero_shared_weak.
struct Block {
    shared_weak_count c;
    u64 zero_shared;       // 0x18
    u64 zero_shared_weak;  // 0x20
};
static_assert(offsetof(Block, zero_shared) == 0x18 && offsetof(Block, zero_shared_weak) == 0x20);

// The fake vtable: slots 0-1 and 3 are never called (a lone RET), slot 2 bumps +0x18, slot 4 +0x20.
// Mapped once for the process (map_guest_code: a page that is never unmapped).
const u64* fake_vtable() {
    static const u64* vt = [] {
        auto* code = (u32*)map_guest_code(4096);
        const u32 prog[] = {
            0xD65F03C0,                                      // 0: ret
            0xF9400C01, 0x91000421, 0xF9000C01, 0xD65F03C0,  // 1: ldr x1,[x0,#0x18]; add x1,x1,#1; str x1,[x0,#0x18]; ret
            0xF9401001, 0x91000421, 0xF9001001, 0xD65F03C0,  // 5: the same at +0x20
        };
        std::memcpy(code, prog, sizeof prog);
        auto* table = (u64*)(code + 64);
        table[0] = table[1] = table[3] = (u64)&code[0];
        table[2] = (u64)&code[1];
        table[4] = (u64)&code[5];
        return (const u64*)table;
    }();
    return vt;
}

constexpr const char* kSwAdd = "_ZNSt6__ndk119__shared_weak_count12__add_sharedEv";
constexpr const char* kSwAddWeak = "_ZNSt6__ndk119__shared_weak_count10__add_weakEv";
constexpr const char* kSwRelease = "_ZNSt6__ndk119__shared_weak_count16__release_sharedEv";
constexpr const char* kSwReleaseWeak = "_ZNSt6__ndk119__shared_weak_count14__release_weakEv";
constexpr const char* kSwLock = "_ZNSt6__ndk119__shared_weak_count4lockEv";
constexpr const char* kScAdd = "_ZNSt6__ndk114__shared_count12__add_sharedEv";
constexpr const char* kScRelease = "_ZNSt6__ndk114__shared_count16__release_sharedEv";

NATIVE_TEST("libcxx/shared-weak-count") {
    for (int round = 0; round < 200; round++) {
        Block g{}, n{};
        s64 owners = t.rand_int(-1, 3), weak = t.rand_int(-1, 3);
        g.c = {fake_vtable(), owners, weak};
        n.c = {fake_vtable(), owners, weak};
        for (int step = 0; step < 12; step++) {
            int op = t.rand_int(0, 4);
            u64 rg = 0, rn = 0;
            switch (op) {
                case 0: t.call(kSwAdd, {(u64)&g}), n.c.__add_shared(); break;
                case 1: t.call(kSwAddWeak, {(u64)&g}), n.c.__add_weak(); break;
                case 2: t.call(kSwRelease, {(u64)&g}), n.c.__release_shared(); break;
                case 3: t.call(kSwReleaseWeak, {(u64)&g}), n.c.__release_weak(); break;
                case 4:
                    rg = t.call(kSwLock, {(u64)&g});  // this or null
                    rg = rg == (u64)&g.c ? 1 : rg ? 2 : 0;
                    rn = n.c.lock() == &n.c ? 1 : 0;
                    break;
            }
            if (g.c.shared_owners != n.c.shared_owners || g.c.shared_weak_owners != n.c.shared_weak_owners || g.zero_shared != n.zero_shared ||
                g.zero_shared_weak != n.zero_shared_weak || rg != rn) {
                t.fail("round %d step %d op %d: guest {%lld, %lld, zs %llu, zsw %llu, r %llu} native {%lld, %lld, zs %llu, zsw %llu, r %llu}", round, step, op,
                       (long long)g.c.shared_owners, (long long)g.c.shared_weak_owners, (unsigned long long)g.zero_shared, (unsigned long long)g.zero_shared_weak,
                       (unsigned long long)rg, (long long)n.c.shared_owners, (long long)n.c.shared_weak_owners, (unsigned long long)n.zero_shared,
                       (unsigned long long)n.zero_shared_weak, (unsigned long long)rn);
                break;
            }
        }
    }
}

NATIVE_TEST("libcxx/shared-count") {
    for (int round = 0; round < 100; round++) {
        Block g{}, n{};
        s64 owners = t.rand_int(-1, 3);
        g.c = {fake_vtable(), owners, 0};
        n.c = {fake_vtable(), owners, 0};
        auto* gc = reinterpret_cast<shared_count*>(&g.c);
        auto* nc = reinterpret_cast<shared_count*>(&n.c);
        for (int step = 0; step < 10; step++) {
            u64 rg = 0, rn = 0;
            if (t.rand_int(0, 1)) {
                t.call(kScAdd, {(u64)gc});
                nc->__add_shared();
            } else {
                rg = t.call(kScRelease, {(u64)gc}) & 0xff;
                rn = nc->__release_shared();
            }
            if (gc->shared_owners != nc->shared_owners || g.zero_shared != n.zero_shared || g.zero_shared_weak != n.zero_shared_weak || rg != rn) {
                t.fail("round %d step %d: guest {%lld, zs %llu, r %llu} native {%lld, zs %llu, r %llu}", round, step, (long long)gc->shared_owners,
                       (unsigned long long)g.zero_shared, (unsigned long long)rg, (long long)nc->shared_owners, (unsigned long long)n.zero_shared, (unsigned long long)rn);
                break;
            }
        }
    }
}

}  // namespace
}  // namespace soa::native::libcxx
