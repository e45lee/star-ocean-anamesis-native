// The `data_formats` live-check family (data_formats_family.h).
#include "native/data_formats/data_formats_family.h"

namespace soa::native::data_formats {

int DataFormatsFamily::add_with(const char* sym, HostFn fn, u32 obj_bytes, live::RetKind ret, const char* label, RegionFn f) {
    int n = add_leaf(sym, fn, obj_bytes, ret, label, {});
    if (n >= 0) {
        if ((size_t)n >= fns_.size()) fns_.resize(n + 1);
        fns_[n] = f;
    }
    return n;
}

void DataFormatsFamily::add_regions(const live::Entry& e, const u64 x[9], bool has_obj, live::Regions& r) {
    LeafFamily::add_regions(e, x, has_obj, r);
    int n = (int)(&e - &live::entry(0));
    if (n >= 0 && (size_t)n < fns_.size() && fns_[n]) fns_[n](x, r);
}

DataFormatsFamily& family() {
    static DataFormatsFamily f;
    return f;
}

void add_region(live::Regions& r, u64 p, u64 n, u64 cap) {
    if (!p || !n) return;
    if (n > cap) n = cap;
    for (auto& [q, m] : r.r)
        if (q <= p && p + n <= q + m) return;
    r.add(p, (u32)n);
}

}  // namespace soa::native::data_formats
