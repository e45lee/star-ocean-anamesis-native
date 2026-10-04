// Differential tests of libcxx_string.cpp against the 3.7.0 guest (--selftest libcxx/string-): the same
// random operations on two strings built alike (the guest's own insert), one through the guest's
// members, one through the natives; contents, size, short / long form and capacity must agree.
#include <cstring>
#include <string>

#include "native/common/test.h"
#include "native/libcxx/libcxx_layout.h"

namespace soa::native::libcxx {
namespace {

#define STR_SYM(m) "_ZNSt6__ndk112basic_stringIcNS_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS3_22CSTLStringAllocatorInfEEEE" m
constexpr const char* kInsert = STR_SYM("6insertEmPKc");
constexpr const char* kDtor = STR_SYM("D2Ev");

using Str = basic_string<char>;

std::string view(const Str& s) { return std::string(s.data(), s.size()); }

std::string rand_text(TestContext& t, int maxlen) {
    std::string s((size_t)t.rand_int(0, maxlen), ' ');
    for (auto& c : s) c = (char)t.rand_int('a', 'z');
    return s;
}

struct Pair {
    TestContext& t;
    alignas(8) Str g{}, n{};
    Pair(TestContext& tc, const std::string& init) : t(tc) {
        std::memset(&g, 0, sizeof g);
        std::memset(&n, 0, sizeof n);
        if (!init.empty()) {
            t.call(kInsert, {(u64)&g, 0, (u64)init.c_str()});
            t.call(kInsert, {(u64)&n, 0, (u64)init.c_str()});
        }
    }
    ~Pair() {
        t.call(kDtor, {(u64)&g});
        t.call(kDtor, {(u64)&n});
    }
    std::string diff() const {
        if (view(g) != view(n)) return "contents \"" + view(g) + "\" vs \"" + view(n) + "\"";
        if (g.is_long() != n.is_long() || g.capacity() != n.capacity()) return "form / capacity";
        if (g.data()[g.size()] != 0 || n.data()[n.size()] != 0) return "terminator";
        return "";
    }
};

NATIVE_TEST("libcxx/string-replace-reserve") {
    for (int k = 0; k < 600; k++) {
        Pair p(t, rand_text(t, k % 3 ? 20 : 120));
        for (int step = 0; step < 6; step++) {
            u64 sz = p.g.size();
            int op = t.rand_int(0, 2);
            if (op == 0) {
                u64 res = (u64)t.rand_int(0, 200);
                t.call(STR_SYM("7reserveEm"), {(u64)&p.g, res});
                p.n.reserve(res);
            } else {
                u64 pos = (u64)t.rand_int(0, (int)sz), n1 = (u64)t.rand_int(0, 30);
                std::string ext = rand_text(t, op == 1 ? 10 : 90);
                bool inside = t.rand_int(0, 3) == 0 && sz > 0;
                u64 from = inside ? (u64)t.rand_int(0, (int)sz - 1) : 0;
                u64 n2 = inside ? (u64)t.rand_int(0, (int)(sz - from)) : ext.size();
                const char* sg = inside ? p.g.data() + from : ext.c_str();
                const char* sn = inside ? p.n.data() + from : ext.c_str();
                u64 rg = t.call(STR_SYM("7replaceEmmPKcm"), {(u64)&p.g, pos, n1, (u64)sg, n2});
                u64 rn = (u64)p.n.replace(pos, n1, sn, n2);
                if (rg != (u64)&p.g || rn != (u64)&p.n) t.fail("replace's result");
            }
            std::string d = p.diff();
            if (!d.empty()) {
                t.fail("case %d step %d op %d: %s", k, step, op, d.c_str());
                return;
            }
        }
    }
}

NATIVE_TEST("libcxx/string-grow-by") {
    for (int k = 0; k < 300; k++) {
        Pair p(t, rand_text(t, k % 2 ? 20 : 100));
        u64 sz = p.g.size(), cap = p.g.capacity();
        u64 n_copy = (u64)t.rand_int(0, (int)sz), n_del = (u64)t.rand_int(0, (int)(sz - n_copy)), n_add = (u64)t.rand_int(0, 40);
        u64 delta = (u64)t.rand_int(1, 200);
        if (k % 2) {
            std::string add = rand_text(t, (int)n_add);
            n_add = add.size();
            t.call(STR_SYM("21__grow_by_and_replaceEmmmmmmPKc"), {(u64)&p.g, cap, delta, sz, n_copy, n_del, n_add, (u64)add.c_str()});
            p.n.__grow_by_and_replace(cap, delta, sz, n_copy, n_del, n_add, add.c_str());
            std::string d = p.diff();
            if (!d.empty()) {
                t.fail("grow_by_and_replace case %d: %s", k, d.c_str());
                return;
            }
        } else {
            t.call(STR_SYM("9__grow_byEmmmmmm"), {(u64)&p.g, cap, delta, sz, n_copy, n_del, n_add});
            p.n.__grow_by(cap, delta, sz, n_copy, n_del, n_add);
            // (the caller fills the gap and sets the size: compare the copied parts and the capacity)
            u64 rest = sz - n_del - n_copy;
            bool same = p.g.r.l.cap == p.n.r.l.cap && std::memcmp(p.g.r.l.data, p.n.r.l.data, n_copy) == 0 &&
                        std::memcmp(p.g.r.l.data + n_copy + n_add, p.n.r.l.data + n_copy + n_add, rest) == 0;
            // make both valid strings again for the destructor
            for (Str* s : {&p.g, &p.n}) {
                std::memset(s->r.l.data + n_copy, 'g', n_add);
                s->r.l.size = n_copy + n_add + rest;
                s->r.l.data[s->r.l.size] = 0;
            }
            if (!same) {
                t.fail("grow_by case %d (cap %llu delta %llu size %llu copy %llu del %llu add %llu)", k, (unsigned long long)cap, (unsigned long long)delta,
                       (unsigned long long)sz, (unsigned long long)n_copy, (unsigned long long)n_del, (unsigned long long)n_add);
                return;
            }
        }
    }
}
#undef STR_SYM

}  // namespace
}  // namespace soa::native::libcxx
