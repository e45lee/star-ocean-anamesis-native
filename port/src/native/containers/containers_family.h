#pragma once
// The `containers` subsystem's live-check family (--live-check containers): every native of the
// subsystem is registered through it (native/common/live_leaf.h), so a normal run can compare each one
// with the guest original. Besides live_leaf.h's argument regions, a native can name a function that
// adds the memory it writes from its arguments (CONTAINERS_HOSTFN: a pool's bit words). A
// function-local static: the natives in every containers_*.cpp share it whatever the
// static-initialization order.
#include <vector>

#include "native/common/live_leaf.h"

namespace soa::native::containers {

class ContainersFamily : public live::LeafFamily {
public:
    using RegionFn = void (*)(const u64 x[9], live::Regions& r);
    ContainersFamily() : LeafFamily("containers", 8) {}
    int add_with(const char* sym, HostFn fn, u32 obj_bytes, live::RetKind ret, const char* label, RegionFn f) {
        int n = add_leaf(sym, fn, obj_bytes, ret, label, {});
        if (n >= 0) {
            if ((size_t)n >= fns_.size()) fns_.resize(n + 1);
            fns_[n] = f;
        }
        return n;
    }
    void add_regions(const live::Entry& e, const u64 x[9], bool has_obj, live::Regions& r) override {
        LeafFamily::add_regions(e, x, has_obj, r);
        int n = (int)(&e - &live::entry(0));
        if (n >= 0 && (size_t)n < fns_.size() && fns_[n]) fns_[n](x, r);
    }

private:
    std::vector<RegionFn> fns_;  // by entry index
};

ContainersFamily& family();

}  // namespace soa::native::containers

#define CONTAINERS_HOSTFN(sym, hostfn, obj_bytes, ret, note, regions) \
    static int NATIVE_CONCAT(cont_reg_, __LINE__) = ::soa::native::containers::family().add_with(sym, hostfn, obj_bytes, ret, note, regions)
