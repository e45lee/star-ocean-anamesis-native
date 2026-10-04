// make_relocated_trampoline: small guest functions whose first two instructions are PC-relative,
// called through the original and through the trampoline, must return the same.
#include <cstring>
#include <vector>

#include "native/common/test.h"
#include "native/common/trampoline.h"

namespace soa {
namespace {

struct Snippet {
    const char* name;
    std::vector<u32> code;
    std::vector<u64> inputs;
};

NATIVE_TEST("native/relocated-trampoline") {
    const Snippet snippets[] = {
        {"adrp", {0xb0000000, 0x91004000, 0xd65f03c0}, {0}},  // adrp x0, +1 page; add x0, x0, #0x10; ret
        {"b", {0x14000002, 0xd28000e0, 0xd2800120, 0xd65f03c0}, {0}},  // b +8; mov x0, #7; mov x0, #9; ret
        {"cbz", {0xb4000080, 0x91000400, 0x91002800, 0xd65f03c0, 0xd2800c80, 0xd65f03c0}, {0, 5}},
        {"tbnz", {0x37100080, 0x91000400, 0x91002800, 0xd65f03c0, 0xd2800c80, 0xd65f03c0}, {4, 1, 0}},
        {"b.cond", {0xf1000c1f, 0x54000040, 0x91002800, 0xd65f03c0, 0xd2800c80, 0xd65f03c0}, {3, 4}},
        {"bl", {0xa9bf7bfd, 0x94000003, 0xa8c17bfd, 0xd65f03c0, 0xd503201f, 0x91001c00, 0xd65f03c0}, {1, 40}},
    };
    for (auto& s : snippets) {
        auto* page = (u32*)map_guest_code(4096);
        memcpy(page, s.code.data(), s.code.size() * 4);
        u64 fn = (u64)page, tr = make_relocated_trampoline(fn);
        if (!tr) {
            t.fail("%s: no trampoline", s.name);
            continue;
        }
        for (u64 in : s.inputs) {
            u64 want = guest_invoke<u64>(fn, in), got = guest_invoke<u64>(tr, in);
            if (want != got) t.fail("%s(%llu): original %#llx, trampoline %#llx", s.name, (unsigned long long)in, (unsigned long long)want, (unsigned long long)got);
        }
        // (the pages stay mapped: the JIT caches translations by address, port/src/native/README.md)
    }
    // An LDR (literal) in the first two instructions isn't relocated.
    auto* page = (u32*)map_guest_code(4096);
    page[0] = 0x58000040;  // ldr x0, #8
    page[1] = 0xd65f03c0;
    t.expect_eq(make_relocated_trampoline((u64)page), (u64)0, "LDR (literal) refused");
}

}  // namespace
}  // namespace soa
