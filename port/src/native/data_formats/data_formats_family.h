#pragma once
// The `data_formats` subsystem's live-check family (--live-check data_formats): every native of the
// subsystem is registered through it, so a normal run can compare each one with the guest original.
// Besides live_leaf.h's argument regions, a native can name a function that adds the memory it
// writes (an ASON's work block, a MessagePackContext, an output buffer) from its arguments
// (DF_HOSTFN). A function-local static: the natives in every data_formats_*.cpp share it whatever
// the static-initialization order.
#include <vector>

#include "native/common/live_leaf.h"

namespace soa::native::data_formats {

class DataFormatsFamily : public live::LeafFamily {
public:
    // Adds the regions a call with these argument registers touches (before the call).
    using RegionFn = void (*)(const u64 x[9], live::Regions& r);
    DataFormatsFamily() : LeafFamily("data_formats", 8) {}
    int add_with(const char* sym, HostFn fn, u32 obj_bytes, live::RetKind ret, const char* label, RegionFn f);
    void add_regions(const live::Entry& e, const u64 x[9], bool has_obj, live::Regions& r) override;

private:
    std::vector<RegionFn> fns_;  // by entry index
};

DataFormatsFamily& family();

// A region [p, p + n) (n capped at `cap`), unless p is null or already covered.
void add_region(live::Regions& r, u64 p, u64 n, u64 cap = 0x40000);

}  // namespace soa::native::data_formats

// A hand-written HostFn with a region function (DataFormatsFamily::RegionFn, or nullptr).
#define DF_HOSTFN(sym, hostfn, obj_bytes, ret, note, regions) \
    static int NATIVE_CONCAT(df_reg_, __LINE__) = ::soa::native::data_formats::family().add_with(sym, hostfn, obj_bytes, ret, note, regions)
