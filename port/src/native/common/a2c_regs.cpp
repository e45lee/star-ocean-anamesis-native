// The a2c register file's calls (a2c_regs.h).
#include "native/common/a2c_regs.h"

#include <cstring>

namespace soa::a2c {
namespace {

V4 to_v4(V128 q) {
    V4 v;
    std::memcpy(&v.f[0], &q.lo, 8);
    std::memcpy(&v.f[2], &q.hi, 8);
    return v;
}
V128 to_v128(const V4& v) {
    V128 q;
    std::memcpy(&q.lo, &v.f[0], 8);
    std::memcpy(&q.hi, &v.f[2], 8);
    return q;
}

}  // namespace

void a2c_gcall(A64& r, std::uint64_t target) {
    // A guest function that is itself replaced by native code: call the host function directly
    // on the current CPU (the JIT round trip costs more than most callees).
    if (Cpu* c = current_cpu()) {
        if (HostFn f = hooked_host_fn(target)) {
            u64 saved_sp = c->sp();
            for (int i = 0; i <= 8; i++) c->set_x(i, r.x[i]);
            for (int i = 0; i < 8; i++) c->set_v(i, to_v128(r.v[i]));
            c->set_sp(r.x[31]);  // stack arguments are at the body's SP
            if (!(__builtin_expect(t_hook_filter != nullptr, 0) && t_hook_filter(*c, target))) f(*c);
            c->set_sp(saved_sp);
            r.x[0] = c->x(0);
            r.x[1] = c->x(1);
            for (int i = 0; i < 4; i++) r.v[i] = to_v4(c->v(i));
            return;
        }
    }
    // The body's frame lives below the SP it was entered with: a2c_guest_call moves the CPU's SP
    // below it (so the nested guest call doesn't overwrite it) and passes the body's stack slots
    // as the callee's stack arguments.
    GuestResult g = a2c_guest_call(target, r.x, r.v, r.x[31]);
    r.x[0] = g.x0;
    r.x[1] = g.x1;
    r.v[0] = to_v4(g.v0);
    r.v[1] = to_v4(g.v1);
    r.v[2] = to_v4(g.v2);
    r.v[3] = to_v4(g.v3);
}

void a2c_run_hook(Cpu& c, Body body) {
    A64 r;
    for (int i = 0; i <= 8; i++) r.x[i] = c.x(i);
    for (int i = 0; i < 8; i++) r.v[i] = to_v4(c.v(i));
    r.x[31] = c.sp();
    body(r);
    c.set_x(0, r.x[0]);
    c.set_x(1, r.x[1]);
    for (int i = 0; i < 4; i++) c.set_v(i, to_v128(r.v[i]));
}

}  // namespace soa::a2c
