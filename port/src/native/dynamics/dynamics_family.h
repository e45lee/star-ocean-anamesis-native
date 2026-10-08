#pragma once
// The `dynamics` subsystem's live-check family (--live-check dynamics) and the float helpers its
// natives share. Every native is registered through the family (a live::LeafFamily: the object at
// x0 plus the regions each native names), so a normal run compares each with the guest original.
//
// Floating point: as math's (math_family.h): no fused multiply-add in the lib, so plain * and +
// in the guest's operand order (compiled with -ffp-contract=off), armf::F for AArch64's NaN rules,
// and branches on the guest's condition codes (an unordered FCMP takes lt, le, hi, pl, ne and
// skips gt, ge, mi, ls, eq). The guest's square roots are FSQRT with a call to libm's sqrtf when
// the result is a NaN: math::Sqrt (the host's sqrtf, which the HLE thunk calls).
//
// Outgoing calls: the guest functions the primitives call are pure computations over their
// arguments (Vector::ApplyMatrix, ApplyMatrixNoTransport, Matrix::InvertLowError, the node's
// WorldMatrix getter) or idempotent (the node's MakeMatrix), so the natives call them as plain
// guest calls, in the guest's order, and a live check's replay of the original runs them for real
// as well (no stubs: nothing to record); a callee that is a native itself (math's
// Segment::SquaredDistance) is called as its C++ member.
#include <initializer_list>
#include <vector>

#include "core/loader.h"
#include "core/cpu.h"
#include "native/common/live_leaf.h"
#include "native/dynamics/dynamics_layout.h"
#include "native/math/math_constants.h"
#include "native/math/math_family.h"

namespace soa::native::dynamics {

using F = armf::F;
using math::Sqrt;

// The family: a LeafFamily whose natives can also name memory reached through the object (e.g. a
// primitive's scene node: the flags and the inverse matrix Run updates) with extra(n, fn).
class DynamicsFamily : public live::LeafFamily {
public:
    using Extra = void (*)(const u64 x[9], live::Regions& r);
    DynamicsFamily() : LeafFamily("dynamics", 1) {}
    int extra(int n, Extra fn) {
        if (n >= 0) {
            if ((size_t)n >= extra_.size()) extra_.resize(n + 1);
            extra_[n] = fn;
        }
        return n;
    }
    void add_regions(const live::Entry& e, const u64 x[9], bool has_obj, live::Regions& r) override {
        LeafFamily::add_regions(e, x, has_obj, r);
        size_t n = (size_t)(&e - &live::entry(0));
        if (n < extra_.size() && extra_[n]) extra_[n](x, r);
    }

private:
    std::vector<Extra> extra_;  // by entry index
};

DynamicsFamily& family();

inline float f(F a) { return a.v; }

// A guest function's address (resolved once per call site: a function-local static).
inline u64 fn_addr(const char* sym) { return main_lib()->sym(sym); }

// A guest call (pointer / integer arguments).
inline u64 call(u64 fn, std::initializer_list<u64> args) { return guest_call(fn, args); }
// A native calling another native of this family: as a C++ call normally; with the family's live
// check on, through the guest entry (guest_call reaches the registered host function, i.e. the
// check), so a native only other natives call is still compared with its original
// (--live-check dynamics:only=...).
inline bool checking() { return family().on.load(std::memory_order_relaxed); }

// A virtual of the node: its vtable's slot.
inline u64 vcall(const HierarchicalObject* h, int slot) {
    u64 fn = static_cast<const u64*>(h->base.link.vtable)[slot];
    return guest_call(fn, {(u64)h});
}

}  // namespace soa::native::dynamics
