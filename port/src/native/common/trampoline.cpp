#include "native/common/trampoline.h"

#include <cstring>
#include <vector>

namespace soa {
namespace {

s64 sext(u64 v, int bits) { return (s64)(v << (64 - bits)) >> (64 - bits); }

constexpr u32 kLdrLit = 0x58000000;  // LDR Xt, literal (imm19 << 5 | Rt)
constexpr u32 kBrX16 = 0xd61f0200, kBlrX16 = 0xd63f0200;
constexpr u32 kX16 = 16;

struct Code {
    std::vector<u32> w;
    std::vector<u64> lits;
    struct Fix {
        size_t at;
        int target;  // a literal (kind 0) or a stub (kind 19 / 14: the immediate's width)
        int kind;
    };
    std::vector<Fix> fixes;
    std::vector<u64> stub_targets;

    void ldr_lit(u32 rt, u64 value) {
        fixes.push_back({w.size(), (int)lits.size(), 0});
        lits.push_back(value);
        w.push_back(kLdrLit | rt);
    }
    void cond(u32 insn, int imm_bits, u64 target) {
        fixes.push_back({w.size(), (int)stub_targets.size(), imm_bits});
        stub_targets.push_back(target);
        w.push_back(insn);
    }
    // One instruction, as it executes at `pc`; false: can't be relocated.
    bool relocate(u32 i, u64 pc) {
        if ((i & 0x9f000000) == 0x90000000 || (i & 0x9f000000) == 0x10000000) {  // ADRP / ADR
            s64 imm = sext(((u64)((i >> 5) & 0x7ffff) << 2) | ((i >> 29) & 3), 21);
            bool page = i & 0x80000000;
            ldr_lit(i & 31, page ? (pc & ~0xfffull) + (u64)(imm << 12) : pc + (u64)imm);
        } else if ((i & 0x7c000000) == 0x14000000) {  // B / BL
            ldr_lit(kX16, pc + (u64)(sext(i & 0x3ffffff, 26) * 4));
            w.push_back(i & 0x80000000 ? kBlrX16 : kBrX16);
        } else if ((i & 0xff000010) == 0x54000000 || (i & 0x7e000000) == 0x34000000) {  // B.cond / CBZ / CBNZ
            cond(i & ~(0x7ffffu << 5), 19, pc + (u64)(sext((i >> 5) & 0x7ffff, 19) * 4));
        } else if ((i & 0x7e000000) == 0x36000000) {  // TBZ / TBNZ
            cond(i & ~(0x3fffu << 5), 14, pc + (u64)(sext((i >> 5) & 0x3fff, 14) * 4));
        } else if ((i & 0x3b000000) == 0x18000000) {  // LDR (literal)
            return false;
        } else {
            w.push_back(i);
        }
        return true;
    }
};

}  // namespace

u64 make_relocated_trampoline(u64 addr) {
    if (u64 t = make_original_trampoline(addr)) return t;
    const u32* p = (const u32*)addr;
    Code c;
    if (!c.relocate(p[0], addr) || !c.relocate(p[1], addr + 4)) return 0;
    c.ldr_lit(kX16, addr + 8);
    c.w.push_back(kBrX16);
    std::vector<size_t> stubs;
    for (u64 tgt : c.stub_targets) {
        stubs.push_back(c.w.size());
        c.ldr_lit(kX16, tgt);
        c.w.push_back(kBrX16);
    }
    if (c.w.size() & 1) c.w.push_back(0xd503201f);  // NOP: the literals 8-aligned
    size_t lit0 = c.w.size();
    for (u64 v : c.lits) {
        c.w.push_back((u32)v);
        c.w.push_back((u32)(v >> 32));
    }
    for (auto& f : c.fixes) {
        size_t to = f.kind == 0 ? lit0 + 2 * f.target : stubs[f.target];
        u32 off = (u32)(to - f.at);
        u32 mask = f.kind == 14 ? 0x3fff : 0x7ffff;
        c.w[f.at] |= (off & mask) << 5;
    }
    auto* t = (u32*)map_guest_code(4096);
    memcpy(t, c.w.data(), c.w.size() * 4);
    return (u64)t;
}

}  // namespace soa
