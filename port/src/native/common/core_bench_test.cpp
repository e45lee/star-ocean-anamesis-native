// Costs of crossing between native and guest code (core runtime), plus correctness checks of
// the guest_call fast paths. The guest code used here is hand-assembled into host buffers
// (guest memory is identity-mapped), so the tests don't depend on game functions.
#include <chrono>
#include <cstring>
#include <atomic>
#include <thread>
#include <vector>

#include "native/common/test.h"

namespace soa {
namespace {

using Clock = std::chrono::steady_clock;

// add x0, x0, #1; ret
alignas(16) u32 g_inc[] = {0x91000400, 0xd65f03c0};
// A function that gets hooked (hook_guest_function) by the benchmark: its body is overwritten.
alignas(16) u32 g_hooked_fn[] = {0x91000400, 0xd65f03c0, 0xd503201f, 0xd503201f};
// Calls x2(x0, x1) x3 times.
alignas(16) const u32 g_loop[] = {
    0xa9bf7bfd, 0xa9bf53f3, 0xa9bf5bf5,              // stp x29,x30 / x19,x20 / x21,x22, [sp,#-16]!
    0xaa0303f3, 0xaa0003f4, 0xaa0103f5, 0xaa0203f6,  // x19=count x20=a0 x21=a1 x22=fn
    0xaa1403e0, 0xaa1503e1, 0xd63f02c0,              // L: x0=x20 x1=x21 blr x22
    0xf1000673, 0x54ffff61,                          // subs x19,x19,#1; b.ne L
    0xa8c15bf5, 0xa8c153f3, 0xa8c17bfd, 0xd65f03c0,
};

void h_empty(Cpu&) {}
// Typical transcribed-hook marshalling: read the argument registers, write the result.
void h_marshal(Cpu& c) {
    u64 s = 0;
    for (int i = 0; i < 8; i++) s += c.x(i);
    for (int i = 0; i < 8; i++) s += c.v(i).lo;
    c.set_x(0, s);
}

double per_call(Clock::time_point t0, u64 n) { return std::chrono::duration<double, std::nano>(Clock::now() - t0).count() / (double)n; }

// Nested native->guest calls: run from inside a thunk (so guest_call nests on a JIT level).
u64 g_nested_n = 0;
double g_nested_ns[4];
u64 g_nested_target = 0;
void h_bench_nested(Cpu&) {
    u64 n = g_nested_n;
    auto t0 = Clock::now();
    for (int rep = 0; rep < 2; rep++) {  // the first round also warms up this JIT level
        t0 = Clock::now();
        for (u64 i = 0; i < n; i++) guest_call((u64)g_inc, {i});
        g_nested_ns[0] = per_call(t0, n);
    }
    GuestArgs a;
    a.i(1);
    t0 = Clock::now();
    for (u64 i = 0; i < n; i++) guest_call((u64)g_inc, a);
    g_nested_ns[1] = per_call(t0, n);
    t0 = Clock::now();
    for (u64 i = 0; i < n; i++) guest_call((u64)g_inc, GuestArgs().i(i).i(2).f(1.0f));
    g_nested_ns[2] = per_call(t0, n);
    t0 = Clock::now();
    for (u64 i = 0; i < n; i++) guest_call(g_nested_target, {i, 2});
    g_nested_ns[3] = per_call(t0, n);
}

}  // namespace

NATIVE_TEST("core/zz-bench-transitions") {
    static u64 hooked = 0;
    if (!hooked) {
        hook_guest_function((u64)g_hooked_fn, "bench-hooked", h_marshal);
        hooked = (u64)g_hooked_fn;
    }
    const u64 empty = make_thunk("bench-empty", h_empty), marshal = make_thunk("bench-marshal", h_marshal);
    const u64 nested = make_thunk("bench-nested", h_bench_nested);
    constexpr u64 N = 2000000;

    // guest -> guest / guest -> native (SVC trap), measured from a guest loop.
    struct {
        const char* name;
        u64 fn;
    } loops[] = {{"guest->guest (JIT BLR to add;ret)", (u64)g_inc},
                 {"guest->native, empty thunk", empty},
                 {"guest->native, 8x+8v marshalling", marshal},
                 {"guest->hooked guest fn (marshal)", hooked}};
    for (auto& l : loops) {
        guest_call((u64)g_loop, {1, 2, l.fn, 1000});
        auto t0 = Clock::now();
        guest_call((u64)g_loop, {1, 2, l.fn, N});
        fprintf(stderr, "    bench: %-40s %7.1f ns/call\n", l.name, per_call(t0, N));
    }

    // native -> guest from the top level (depth 0).
    constexpr u64 M = 500000;
    auto t0 = Clock::now();
    for (u64 i = 0; i < M; i++) guest_call((u64)g_inc, {i});
    fprintf(stderr, "    bench: %-40s %7.1f ns/call\n", "native->guest top, init-list", per_call(t0, M));
    GuestArgs a;
    a.i(1);
    t0 = Clock::now();
    for (u64 i = 0; i < M; i++) guest_call((u64)g_inc, a);
    fprintf(stderr, "    bench: %-40s %7.1f ns/call\n", "native->guest top, reused GuestArgs", per_call(t0, M));
    t0 = Clock::now();
    for (u64 i = 0; i < M; i++) guest_call((u64)g_inc, GuestArgs().i(i).i(2).f(1.0f));
    fprintf(stderr, "    bench: %-40s %7.1f ns/call\n", "native->guest top, fresh GuestArgs", per_call(t0, M));

    // native -> guest nested inside a thunk (the common case: a native replacement calling out).
    g_nested_n = M;
    g_nested_target = hooked;
    guest_call(nested, {});
    fprintf(stderr, "    bench: %-40s %7.1f ns/call\n", "native->guest nested, init-list", g_nested_ns[0]);
    fprintf(stderr, "    bench: %-40s %7.1f ns/call\n", "native->guest nested, reused GuestArgs", g_nested_ns[1]);
    fprintf(stderr, "    bench: %-40s %7.1f ns/call\n", "native->guest nested, fresh GuestArgs", g_nested_ns[2]);
    fprintf(stderr, "    bench: %-40s %7.1f ns/call\n", "native->hooked fn nested (guest_call)", g_nested_ns[3]);

    // native -> native through the hook registry.
    t0 = Clock::now();
    u64 found = 0;
    for (u64 i = 0; i < M; i++) found += hooked_host_fn(hooked + ((i & 1) ? 0 : 4)) != nullptr;
    fprintf(stderr, "    bench: %-40s %7.1f ns/call\n", "hooked_host_fn lookup (hit/miss)", per_call(t0, M));
    if (found != M / 2) t.fail("hooked_host_fn found %llu of %llu", (unsigned long long)found, (unsigned long long)M / 2);
}


// ---- guest_call fast paths: direct calls to hooked functions / thunks must behave like the JIT ----
namespace {
alignas(16) u32 g_rec_fn[] = {0xd503201f, 0xd503201f, 0xd65f03c0, 0xd503201f};
alignas(16) u32 g_recurse_fn[] = {0xd503201f, 0xd503201f, 0xd65f03c0, 0xd503201f};
struct Seen {
    u64 x[9];
    V128 v[8];
    u64 stack[6];
    u64 pc, lr, sp_align;
    bool cur;
};
Seen g_seen;
void h_record(Cpu& c) {
    for (int i = 0; i < 9; i++) g_seen.x[i] = c.x(i);
    for (int i = 0; i < 8; i++) g_seen.v[i] = c.v(i);
    for (int i = 0; i < 6; i++) g_seen.stack[i] = ((const u64*)c.sp())[i];
    g_seen.pc = c.pc();
    g_seen.lr = c.lr();
    g_seen.sp_align = c.sp() & 15;
    g_seen.cur = current_cpu() == &c;
    c.set_x(0, c.x(0) * 3 + 1);
    c.set_x(1, 77);
    for (int i = 0; i < 4; i++) c.set_v(i, {100 + (u64)i, 5});
}
// f(n) = n == 0 ? 0 : f(n - 1) + inc(n) + g(n) where g alternates guest loop / direct.
void h_recurse(Cpu& c) {
    u64 n = c.x(0);
    if (n == 0) {
        c.set_x(0, 0);
        return;
    }
    u64 r = guest_call((u64)g_recurse_fn, {n - 1});
    r += guest_call((u64)g_inc, {n});  // n + 1
    if (n & 1) guest_call((u64)g_loop, {n, 0, (u64)g_inc, 1});  // guest -> guest, discarded
    c.set_x(0, r);
}
// Registers the call doesn't pass keep stale values from earlier calls, which differ between
// the two paths: compare only what the arguments define.
bool same(const Seen& a, const Seen& b, const GuestArgs& g) {
    size_t ni = g.ints.size(), nv = g.vecs.size();
    for (size_t i = 0; i < 8 && i < ni; i++)
        if (a.x[i] != b.x[i]) return false;
    for (size_t i = 0; i < 8 && i < nv; i++)
        if (std::memcmp(&a.v[i], &b.v[i], 16)) return false;
    size_t ns = (ni > 8 ? ni - 8 : 0) + (nv > 8 ? nv - 8 : 0);
    for (size_t i = 0; i < ns && i < 6; i++)
        if (a.stack[i] != b.stack[i]) return false;
    return a.x[8] == b.x[8] && a.pc == b.pc && a.lr == b.lr && a.sp_align == b.sp_align && a.cur == b.cur;
}
bool same(const GuestResult& a, const GuestResult& b) {
    return a.x0 == b.x0 && a.x1 == b.x1 && std::memcmp(&a.v0, &b.v0, 16) == 0 && std::memcmp(&a.v1, &b.v1, 16) == 0 &&
           std::memcmp(&a.v2, &b.v2, 16) == 0 && std::memcmp(&a.v3, &b.v3, 16) == 0;
}
}  // namespace

NATIVE_TEST("core/guest-call-direct") {
    static bool hooked = false;
    if (!hooked) {
        hook_guest_function((u64)g_rec_fn, "test-record", h_record);
        hook_guest_function((u64)g_recurse_fn, "test-recurse", h_recurse);
        hooked = true;
    }
    const u64 stub = make_thunk("test-record-stub", h_record);
    const bool was = direct_host_calls();
    std::vector<GuestArgs> cases;
    cases.push_back(GuestArgs().i(1).i(2).i(3));
    {
        GuestArgs a;
        for (int i = 0; i < 12; i++) a.i(0x1000 + i);  // 4 on the stack
        a.f(1.5f).d(2.25);
        cases.push_back(a);
    }
    {
        GuestArgs a;
        a.i(9);
        for (int i = 0; i < 11; i++) a.f(0.5f * i);  // 3 on the stack
        cases.push_back(a);
    }
    {
        alignas(16) static u8 buf[64];
        cases.push_back(GuestArgs().sret(buf).p(buf).i(~0ull));
    }
    {
        GuestArgs a;  // spills the inline storage
        for (int i = 0; i < 20; i++) a.i(i);
        GuestArgs b = a;
        cases.push_back(b);
    }
    int n = 0;
    for (u64 target : {(u64)g_rec_fn, stub}) {
        for (auto& a : cases) {
            set_direct_host_calls(false);
            std::memset(&g_seen, 0, sizeof g_seen);
            GuestResult rj = guest_call(target, a);
            Seen sj = g_seen;
            set_direct_host_calls(true);
            std::memset(&g_seen, 0, sizeof g_seen);
            GuestResult rd = guest_call(target, a);
            Seen sd = g_seen;
            if (!same(sj, sd, a)) t.fail("case %d: the host function saw different state (direct vs JIT)", n);
            if (!same(rj, rd)) t.fail("case %d: different results (direct vs JIT)", n);
            if (!sd.cur || sd.pc != target + 4 || sd.lr != host_return_addr() || sd.sp_align) t.fail("case %d: cpu/pc/lr/sp", n);
            n++;
        }
    }
    // Nested: native -> (direct) native -> guest -> ... 12 levels deep, both modes.
    for (bool direct : {false, true}) {
        set_direct_host_calls(direct);
        u64 r = guest_call((u64)g_recurse_fn, {12});
        if (r != 12 * 13 / 2 + 12) t.fail("recursion (%s): %llu", direct ? "direct" : "JIT", (unsigned long long)r);
        // From inside a guest frame too.
        r = guest_call((u64)g_loop, {12, 0, (u64)g_recurse_fn, 3});
        if (r != 12 * 13 / 2 + 12) t.fail("recursion from guest (%s): %llu", direct ? "direct" : "JIT", (unsigned long long)r);
    }
    set_direct_host_calls(was);

    // guest_invoke: typed arguments and results.
    // fadd s0, s0, s1; ret  /  fmov d0, x0; scvtf d0, x0... keep it simple: integer and float paths.
    alignas(16) static const u32 fadd[] = {0x1e212800, 0xd65f03c0};  // fadd s0, s0, s1
    alignas(16) static const u32 cmp[] = {0xeb01001f, 0x1a9f07e0, 0xd65f03c0};  // cmp x0,x1; cset w0, ne
    if (guest_invoke<float>((u64)fadd, 1.25f, 2.5f) != 3.75f) t.fail("guest_invoke<float>");
    if (guest_invoke<bool>((u64)cmp, 3, 3) || !guest_invoke<bool>((u64)cmp, 3, (void*)4)) t.fail("guest_invoke<bool>");
    if (guest_invoke<u64>((u64)g_inc, (s32)-1) != 0) t.fail("guest_invoke<u64>(s32 -1) sign extension");
    if (guest_invoke<int>((u64)g_inc, 41) != 42) t.fail("guest_invoke<int>");
}

// Many host threads crossing at once: every thread has its own JIT levels and state.
NATIVE_TEST("core/guest-call-threads") {
    guest_call((u64)g_recurse_fn, {1});  // hooks installed by core/guest-call-direct
    if (!hooked_host_fn((u64)g_recurse_fn)) {
        hook_guest_function((u64)g_rec_fn, "test-record", h_record);
        hook_guest_function((u64)g_recurse_fn, "test-recurse", h_recurse);
    }
    std::atomic<int> bad{0};
    std::vector<std::thread> th;
    for (int k = 0; k < 8; k++) {
        th.emplace_back([&, k] {
            for (int i = 0; i < 20000; i++) {
                u64 n = (u64)((i + k) % 10);
                if (guest_call((u64)g_recurse_fn, {n}) != n * (n + 1) / 2 + n) bad++;
                if (guest_invoke<u64>((u64)g_inc, (u64)i) != (u64)i + 1) bad++;
                if (guest_call((u64)g_loop, {n, 0, (u64)g_recurse_fn, 2}) != n * (n + 1) / 2 + n) bad++;
            }
            guest_thread_release();
        });
    }
    for (auto& x : th) x.join();
    if (bad) t.fail("%d wrong results", bad.load());
}
}  // namespace soa
