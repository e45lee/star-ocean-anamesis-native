// The live check of the params natives: the family and the string helpers (params_check.h).
#include "native/params/params_check.h"

#include <cstdio>

#include "native/params/params_guest.h"

namespace soa::native::params {

live::RunBothFamily& fam() {
    static live::RunBothFamily f("params", 8);
    return f;
}

thread_local std::vector<PropertyCall>* t_record = nullptr;
thread_local std::vector<PropertyCall>* t_trace = nullptr;

void copy_string(String& dst, const String& src) {
    std::memcpy(&dst, &src, sizeof(String));
    if (!src.is_long()) return;
    u64 alloc = src.r.l.cap & ~u64(1);
    char* p = (char*)g::StlAllocate(alloc, native::kStrStlStringH, 0x1c);
    std::memcpy(p, src.r.l.data, alloc);
    dst.r.l.data = p;
}

void free_copy(String& s) {
    if (s.is_long()) g::StlFree(s.r.l.data);
    std::memset(&s, 0, sizeof s);
}

std::string diff_strings(const String& n, const String& g) {
    char m[200];
    if (n.is_long() != g.is_long() || n.size() != g.size() || n.capacity() != g.capacity()) {
        snprintf(m, sizeof m, "native %s size %llu cap %llu, guest %s size %llu cap %llu", n.is_long() ? "long" : "short",
                 (unsigned long long)n.size(), (unsigned long long)n.capacity(), g.is_long() ? "long" : "short",
                 (unsigned long long)g.size(), (unsigned long long)g.capacity());
        return m;
    }
    // (a short string: all 24 bytes, also those past the NUL, which an earlier value left)
    if (!n.is_long()) return live::RunBothFamily::diff_bytes(&n, &g, sizeof(String));
    if (std::memcmp(n.data(), g.data(), n.size() + 1) != 0) return "bytes " + live::RunBothFamily::diff_bytes(n.data(), g.data(), n.size() + 1);
    return {};
}

}  // namespace soa::native::params
