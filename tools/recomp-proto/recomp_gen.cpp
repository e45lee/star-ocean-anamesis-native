// recomp_gen: the static-recompilation prototype's translator (docs/PLAN-recomp.md, "The prototype").
//
// Lifts guest functions of the 3.7.0 libSOA.so to C++ through dynarmic's own A64 frontend: each
// basic block is translated to dynarmic IR (A64::Translate, the decoder and semantics the JIT
// runs), cleaned up with dynarmic's IR passes, and printed as C++ over a register-file struct
// (`rc::St`, recomp_rt.h): one C++ function per guest function, one label per basic block,
// SSA values as locals, every IR opcode a call of an inline function `rc::<Opcode>` that
// recomp_rt.h defines (an opcode it doesn't define fails to compile: nothing is silently wrong).
//
// Usage (tools/recomp-proto/build.sh runs it):
//   recomp_gen stats LIB FUNCTIONS.tsv                 every function of the list: blocks, IR
//                                                      sizes, terminals, the opcode histogram
//   recomp_gen emit LIB FUNCS.txt OUT.cpp [--locals]   the listed functions as C++ (--locals: the
//                                                      registers in a local copy, written back at
//                                                      calls and returns)
// FUNCTIONS.tsv: the profiler's functions.tsv (offset, size, sources, name); FUNCS.txt: lines
// "0xVADDR SIZE NAME". Linux only (a throwaway prototype, not part of the build).
#include <algorithm>
#include <cinttypes>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include <elf.h>

#include "dynarmic/common/fp/fpcr.h"
#include "dynarmic/frontend/A64/a64_location_descriptor.h"
#include "dynarmic/frontend/A64/a64_types.h"
#include "dynarmic/frontend/A64/translate/a64_translate.h"
#include "dynarmic/interface/A64/config.h"
#include "dynarmic/ir/basic_block.h"
#include "dynarmic/ir/microinstruction.h"
#include "dynarmic/ir/opcodes.h"
#include "dynarmic/ir/opt/passes.h"
#include "dynarmic/ir/terminal.h"
#include "dynarmic/ir/value.h"

using namespace Dynarmic;
using u8 = std::uint8_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;

// Guest code is translated as if loaded here, so a PC-relative constant (ADRP / ADR / a literal
// load's address) comes out of the IR as an immediate in [kFakeBase, kFakeBase + size): the
// emitter prints those as LIB + offset (the real load address at run time).
static constexpr u64 kFakeBase = 0x7e0000000000ull;

static std::vector<u8> g_file;
struct Seg { u64 va, off, filesz; bool x; };
static std::vector<Seg> g_segs;
static u64 g_image_size = 0;
static std::map<u64, std::string> g_plt;  // PLT stub vaddr -> symbol (JUMP_SLOT)
static std::map<u64, std::string> g_dynsym;  // defined function vaddr -> symbol
static std::set<std::string> g_dynsym_by_name;
static std::map<std::string, u64> g_dynsym_addr;

// A call target: a PLT stub of a function the lib defines itself is resolved to that function
// (the loader binds the GOT to it: the call doesn't need the PLT); an import's stub stays.
static u64 resolve_call(u64 va, std::string* why) {
    auto p = g_plt.find(va);
    if (p == g_plt.end()) return va;
    auto d = g_dynsym_addr.find(p->second);
    if (d != g_dynsym_addr.end()) {
        if (why) *why = p->second;
        return d->second;
    }
    if (why) *why = p->second + " (import)";
    return va;
}

static bool load_elf(const char* path) {
    std::ifstream f(path, std::ios::binary);
    if (!f) return false;
    g_file.assign(std::istreambuf_iterator<char>(f), {});
    auto* eh = (const Elf64_Ehdr*)g_file.data();
    auto* ph = (const Elf64_Phdr*)(g_file.data() + eh->e_phoff);
    for (int i = 0; i < eh->e_phnum; i++)
        if (ph[i].p_type == PT_LOAD) {
            g_segs.push_back({ph[i].p_vaddr, ph[i].p_offset, ph[i].p_filesz, (ph[i].p_flags & PF_X) != 0});
            g_image_size = std::max<u64>(g_image_size, ph[i].p_vaddr + ph[i].p_memsz);
        }
    // Section headers: .dynsym, .dynstr, .rela.plt, .plt
    auto* sh = (const Elf64_Shdr*)(g_file.data() + eh->e_shoff);
    const char* shstr = (const char*)g_file.data() + sh[eh->e_shstrndx].sh_offset;
    const Elf64_Shdr *dynsym = nullptr, *relaplt = nullptr, *plt = nullptr;
    for (int i = 0; i < eh->e_shnum; i++) {
        const char* n = shstr + sh[i].sh_name;
        if (!strcmp(n, ".dynsym")) dynsym = &sh[i];
        if (!strcmp(n, ".rela.plt")) relaplt = &sh[i];
        if (!strcmp(n, ".plt")) plt = &sh[i];
    }
    if (dynsym) {
        const char* str = (const char*)g_file.data() + sh[dynsym->sh_link].sh_offset;
        auto* syms = (const Elf64_Sym*)(g_file.data() + dynsym->sh_offset);
        size_t n = dynsym->sh_size / sizeof(Elf64_Sym);
        for (size_t i = 0; i < n; i++)
            if (ELF64_ST_TYPE(syms[i].st_info) == STT_FUNC && syms[i].st_shndx != SHN_UNDEF) {
                g_dynsym[syms[i].st_value] = str + syms[i].st_name;
                g_dynsym_by_name.insert(str + syms[i].st_name);
                g_dynsym_addr[str + syms[i].st_name] = syms[i].st_value;
            }
        if (relaplt && plt) {
            auto* r = (const Elf64_Rela*)(g_file.data() + relaplt->sh_offset);
            size_t nr = relaplt->sh_size / sizeof(Elf64_Rela);
            // AArch64 PLT: a 32-byte header, then 16-byte stubs in .rela.plt order.
            for (size_t i = 0; i < nr; i++) g_plt[plt->sh_addr + 32 + 16 * i] = str + syms[ELF64_R_SYM(r[i].r_info)].st_name;
        }
    }
    return true;
}

static std::optional<u32> read_code_at(u64 va) {
    for (auto& s : g_segs)
        if (s.x && va >= s.va && va + 4 <= s.va + s.filesz) {
            u32 w;
            memcpy(&w, g_file.data() + s.off + (va - s.va), 4);
            return w;
        }
    return std::nullopt;
}

static A64::LocationDescriptor loc(u64 va) { return A64::LocationDescriptor(kFakeBase + va, FP::FPCR{0}); }
static u64 va_of(const IR::LocationDescriptor& l) { return A64::LocationDescriptor(l).PC() - kFakeBase; }

// One function: its blocks, translated with block starts as hard stops.
struct Fn {
    u64 start, size;
    std::string name;
    std::map<u64, IR::Block> blocks;
    std::set<u64> starts;
    bool indirect_jump = false;  // has a BR that isn't a call or a return
    std::string fail;
};

static IR::Block translate_block(u64 va, u64 fstart, u64 fend, const std::set<u64>& stops) {
    auto rd = [&](u64 pc) -> std::optional<u32> {
        u64 v = pc - kFakeBase;
        if (v < fstart || v >= fend) return std::nullopt;
        if (v != va && stops.count(v)) return std::nullopt;  // the next block starts here
        return read_code_at(v);
    };
    A64::TranslationOptions opt;
    opt.define_unpredictable_behaviour = true;  // as the runtime's JIT (core/cpu.cpp)
    opt.hook_hint_instructions = false;
    IR::Block b = A64::Translate(loc(va), rd, opt);
    Optimization::A64GetSetElimination(b);
    Optimization::ConstantPropagation(b);
    Optimization::DeadCodeElimination(b);
    Optimization::IdentityRemovalPass(b);
    return b;
}

// Successors inside the function, from a block's terminal (and a call's return address).
static void successors(const IR::Block& b, const IR::Terminal& t, std::vector<u64>& out) {
    using namespace IR::Term;
    if (auto* l = boost::get<LinkBlock>(&t)) out.push_back(va_of(l->next));
    else if (auto* l = boost::get<LinkBlockFast>(&t)) out.push_back(va_of(l->next));
    else if (auto* i = boost::get<If>(&t)) { successors(b, i->then_, out); successors(b, i->else_, out); }
    else if (auto* c = boost::get<CheckBit>(&t)) { successors(b, c->then_, out); successors(b, c->else_, out); }
    else if (auto* h = boost::get<CheckHalt>(&t)) successors(b, h->else_, out);
}

static bool has_op(const IR::Block& b, IR::Opcode op, u64* arg = nullptr) {
    for (auto& i : b)
        if (i.GetOpcode() == op) {
            if (arg && i.GetArg(0).IsImmediate()) *arg = i.GetArg(0).GetImmediateAsU64();
            return true;
        }
    return false;
}

static void discover(Fn& f) {
    u64 fend = f.start + f.size;
    std::vector<u64> work{f.start};
    f.starts.insert(f.start);
    // Pass 1: find every block start (iterate until no new start splits a block).
    for (int round = 0; round < 8; round++) {
        size_t before = f.starts.size();
        work.assign(f.starts.begin(), f.starts.end());
        std::set<u64> seen;
        while (!work.empty()) {
            u64 va = work.back();
            work.pop_back();
            if (!seen.insert(va).second) continue;
            IR::Block b = translate_block(va, f.start, fend, f.starts);
            std::vector<u64> succ;
            successors(b, b.GetTerminal(), succ);
            u64 ret;
            bool call = has_op(b, IR::Opcode::PushRSB, &ret);
            if (call) succ.push_back(va_of(IR::LocationDescriptor{ret}));
            for (u64 s : succ) {
                if (call && s != va_of(IR::LocationDescriptor{ret})) continue;  // the callee isn't ours
                if (s >= f.start && s < fend && f.starts.insert(s).second) work.push_back(s);
                else if (s >= f.start && s < fend) work.push_back(s);
            }
        }
        if (f.starts.size() == before) break;
    }
    for (u64 va : f.starts) f.blocks.emplace(va, translate_block(va, f.start, fend, f.starts));
}

// ---------------------------------------------------------------------------------- stats mode

static int stats(const char* fnlist) {
    std::ifstream in(fnlist);
    std::string line;
    std::map<std::string, u64> ophist;
    u64 nf = 0, nblocks = 0, ninsts = 0, nguest = 0, nindirect = 0, ninterp = 0, nfault = 0, ncalls = 0, nicalls = 0;
    u64 nret = 0, ntail = 0, nfall = 0;
    std::map<int, u64> exc_hist;
    u64 ncall_direct = 0, ncall_plt_internal = 0, ncall_plt_import = 0;
    std::set<std::string> imports_called;
    while (std::getline(in, line)) {
        if (line.empty() || line[0] == '#') continue;
        std::istringstream ls(line);
        std::string off, size, src, name;
        ls >> off >> size >> src >> name;
        Fn f{std::stoull(off, nullptr, 16), std::stoull(size), name};
        if (f.size < 4) continue;
        discover(f);
        nf++;
        nguest += f.size / 4;
        for (auto& [va, b] : f.blocks) {
            nblocks++;
            for (auto& i : b) {
                ninsts++;
                ophist[IR::GetNameOf(i.GetOpcode())]++;
            }
            const auto& t = b.GetTerminal();
            bool call = has_op(b, IR::Opcode::PushRSB);
            using namespace IR::Term;
            if (call) {
                if (boost::get<LinkBlock>(&t)) ncalls++;
                else nicalls++;
            } else if (boost::get<PopRSBHint>(&t)) nret++;
            else if (boost::get<FastDispatchHint>(&t) || boost::get<ReturnToDispatch>(&t)) nindirect++;
            for (auto& i : b)
                if (i.GetOpcode() == IR::Opcode::A64ExceptionRaised) {
                    nfault++;
                    exc_hist[(int)i.GetArg(1).GetU64()]++;
                }
            if (call) {
                if (auto* l = boost::get<LinkBlock>(&t)) {
                    u64 tgt = va_of(l->next);
                    auto p = g_plt.find(tgt);
                    if (p == g_plt.end()) ncall_direct++;
                    else if (g_dynsym_by_name.count(p->second)) ncall_plt_internal++;
                    else { ncall_plt_import++; imports_called.insert(p->second); }
                }
            }
            if (boost::get<Interpret>(&t)) ninterp++;
            if (auto* l = boost::get<LinkBlock>(&t); l && !call) {
                u64 s = va_of(l->next);
                if (s < f.start || s >= f.start + f.size) ntail++;
            }
            (void)nfall;
        }
        if (nf % 10000 == 0) fprintf(stderr, "  %" PRIu64 " functions\n", nf);
    }
    printf("functions\t%" PRIu64 "\nguest_instructions\t%" PRIu64 "\nblocks\t%" PRIu64 "\nir_instructions\t%" PRIu64 "\n", nf, nguest, nblocks, ninsts);
    printf("direct_calls\t%" PRIu64 "\nindirect_calls\t%" PRIu64 "\nreturns\t%" PRIu64 "\nindirect_jumps\t%" PRIu64 "\ndirect_jumps_out\t%" PRIu64 "\nblocks_with_exception\t%" PRIu64 "\ninterpret_terminals\t%" PRIu64 "\n",
           ncalls, nicalls, nret, nindirect, ntail, nfault, ninterp);
    printf("calls_direct_to_text\t%" PRIu64 "\ncalls_via_plt_to_lib_function\t%" PRIu64 "\ncalls_via_plt_to_import\t%" PRIu64 "\nimports_called\t%zu\n",
           ncall_direct, ncall_plt_internal, ncall_plt_import, imports_called.size());
    for (auto& [k, n] : exc_hist) printf("exception\t%d\t%" PRIu64 "\n", k, n);
    printf("distinct_opcodes\t%zu\n", ophist.size());
    std::vector<std::pair<u64, std::string>> v;
    for (auto& [k, n] : ophist) v.push_back({n, k});
    std::sort(v.rbegin(), v.rend());
    for (auto& [n, k] : v) printf("op\t%s\t%" PRIu64 "\n", k.c_str(), n);
    return 0;
}

// ----------------------------------------------------------------------------------- emit mode

struct Emitter {
    std::ostringstream o;
    std::set<u64> funcs;  // entries of the functions in this unit
    std::map<const IR::Inst*, int> names;
    std::set<const IR::Inst*> flagged;  // values with pseudo-op users: a struct, .v is the value
    std::set<std::string> used_ops;
    bool locals = false;
    std::string fail;

    std::string imm64(u64 v) {
        char b[64];
        if (v >= kFakeBase && v < kFakeBase + g_image_size) snprintf(b, sizeof b, "(LIB + 0x%" PRIx64 "ull)", v - kFakeBase);
        else snprintf(b, sizeof b, "0x%" PRIx64 "ull", v);
        return b;
    }
    std::string arg(const IR::Value& a) {
        char b[64];
        if (!a.IsImmediate()) {
            const IR::Inst* i = a.GetInst();
            snprintf(b, sizeof b, flagged.count(i) ? "t%d.v" : "t%d", names.at(i));
            return b;
        }
        switch (a.GetType()) {
        case IR::Type::U1: return a.GetU1() ? "true" : "false";
        case IR::Type::U8: snprintf(b, sizeof b, "(u8)0x%x", a.GetU8()); return b;
        case IR::Type::U16: snprintf(b, sizeof b, "(u16)0x%x", a.GetU16()); return b;
        case IR::Type::U32: snprintf(b, sizeof b, "0x%xu", a.GetU32()); return b;
        case IR::Type::U64: return imm64(a.GetU64());
        case IR::Type::A64Reg: snprintf(b, sizeof b, "%d", (int)a.GetA64RegRef()); return b;
        case IR::Type::A64Vec: snprintf(b, sizeof b, "%d", (int)a.GetA64VecRef()); return b;
        case IR::Type::Cond: snprintf(b, sizeof b, "%d", (int)a.GetCond()); return b;
        case IR::Type::AccType: snprintf(b, sizeof b, "%d", (int)a.GetAccType()); return b;
        default: fail = "immediate of type " + IR::GetNameOf(a.GetType()); return "0";
        }
    }

    // A jump to va from inside function f: a label of f, or a tail call.
    void jump(const Fn& f, u64 va, const char* ind) {
        if (f.starts.count(va)) o << ind << "goto L_" << std::hex << va << std::dec << ";\n";
        else {
            std::string why;
            u64 t = resolve_call(va, &why);
            o << ind << "{ RC_FLUSH; rc::call(s, LIB + 0x" << std::hex << t << std::dec << "); return; }  // tail " << why << "\n";
        }
    }
    void term(const Fn& f, const IR::Block& b, const IR::Terminal& t, const char* ind, bool call, u64 ret) {
        using namespace IR::Term;
        if (call) {  // BL / BLR: the callee, then the block at the return address
            if (auto* l = boost::get<LinkBlock>(&t)) {
                std::string why;
                u64 tgt = resolve_call(va_of(l->next), &why);
                o << ind << "RC_FLUSH; rc::call(s, " << imm64(kFakeBase + tgt) << "); RC_RELOAD;  // " << why << "\n";
            }
            else o << ind << "RC_FLUSH; rc::call(s, L.pc); RC_RELOAD;\n";
            jump(f, ret, ind);
            return;
        }
        if (auto* l = boost::get<LinkBlock>(&t)) jump(f, va_of(l->next), ind);
        else if (auto* l = boost::get<LinkBlockFast>(&t)) jump(f, va_of(l->next), ind);
        else if (boost::get<PopRSBHint>(&t)) o << ind << "RC_FLUSH; return;  // RET\n";
        else if (boost::get<FastDispatchHint>(&t) || boost::get<ReturnToDispatch>(&t)) {
            // BR: a jump table into this function or a tail call; or an exception's end.
            if (has_op(b, IR::Opcode::A64ExceptionRaised)) {
                o << ind << "RC_FLUSH; return;  // (after the exception)\n";
                return;
            }
            o << ind << "switch (L.pc - LIB) {\n";
            for (u64 st : f.starts) o << ind << "case 0x" << std::hex << st << std::dec << ": goto L_" << std::hex << st << std::dec << ";\n";
            o << ind << "default: RC_FLUSH; rc::call(s, L.pc); return;  // tail\n" << ind << "}\n";
        } else if (auto* i = boost::get<If>(&t)) {
            o << ind << "if (rc::cond(L, " << (int)i->if_ << ")) {\n";
            term(f, b, i->then_, (std::string(ind) + "  ").c_str(), false, 0);
            o << ind << "} else {\n";
            term(f, b, i->else_, (std::string(ind) + "  ").c_str(), false, 0);
            o << ind << "}\n";
        } else if (auto* c = boost::get<CheckBit>(&t)) {
            o << ind << "if (L.check_bit) {\n";
            term(f, b, c->then_, (std::string(ind) + "  ").c_str(), false, 0);
            o << ind << "} else {\n";
            term(f, b, c->else_, (std::string(ind) + "  ").c_str(), false, 0);
            o << ind << "}\n";
        } else if (auto* h = boost::get<CheckHalt>(&t)) term(f, b, h->else_, ind, false, 0);
        else fail = "terminal kind";
    }

    void function(const Fn& f) {
        names.clear();
        flagged.clear();
        o << "// " << f.name << " (0x" << std::hex << f.start << ", " << std::dec << f.size << " bytes)\n";
        o << "void f_" << std::hex << f.start << std::dec << "(rc::St& s) {\n";
        o << "  const u64 LIB = rc::lib_base;\n";
        if (!locals) {
            o << "  rc::St& L = s;\n#define RC_FLUSH\n#define RC_RELOAD\n";
        } else {
            // The registers the function reads and writes live in a local copy the compiler can
            // keep in host registers (guest stores can't alias it); it is written back before every
            // call and return and read again after a call.
            std::set<int> rx, wx, rv, wv;
            for (auto& [va, b] : f.blocks)
                for (auto& i : b) {
                    switch (i.GetOpcode()) {
                    case IR::Opcode::A64GetX: case IR::Opcode::A64GetW: rx.insert((int)i.GetArg(0).GetA64RegRef()); break;
                    case IR::Opcode::A64SetX: case IR::Opcode::A64SetW: wx.insert((int)i.GetArg(0).GetA64RegRef()); break;
                    case IR::Opcode::A64GetS: case IR::Opcode::A64GetD: case IR::Opcode::A64GetQ: rv.insert((int)i.GetArg(0).GetA64VecRef()); break;
                    case IR::Opcode::A64SetS: case IR::Opcode::A64SetD: case IR::Opcode::A64SetQ: wv.insert((int)i.GetArg(0).GetA64VecRef()); break;
                    default: break;
                    }
                }
            // (L keeps the flags, pc and tpidr; the registers are plain locals X<n>, V<n>, SP)
            o << "  rc::St L;\n  u64 SP;\n";
            {
                std::set<int> ax = rx, av = rv;
                ax.insert(wx.begin(), wx.end());
                av.insert(wv.begin(), wv.end());
                for (int r : ax) o << "  u64 X" << r << ";\n";
                for (int r : av) o << "  rc::U128 V" << r << ";\n";
            }
            std::string ld = "SP = s.sp; L.nzcv = s.nzcv; L.tpidr = s.tpidr;", st = "s.sp = SP; s.nzcv = L.nzcv;";
            // (a written register is read back too: after a call the callee's value is current)
            std::set<int> lx = rx, lv = rv;
            lx.insert(wx.begin(), wx.end());
            lv.insert(wv.begin(), wv.end());
            for (int r : lx) ld += " X" + std::to_string(r) + " = s.x[" + std::to_string(r) + "];";
            for (int r : lv) ld += " V" + std::to_string(r) + " = s.v[" + std::to_string(r) + "];";
            for (int r : wx) st += " s.x[" + std::to_string(r) + "] = X" + std::to_string(r) + ";";
            for (int r : wv) st += " s.v[" + std::to_string(r) + "] = V" + std::to_string(r) + ";";
            o << "#define RC_FLUSH do { " << st << " } while (0)\n#define RC_RELOAD do { " << ld << " } while (0)\n  RC_RELOAD;\n";
        }
        int n = 0;
        for (auto& [va, b] : f.blocks) {
            o << "L_" << std::hex << va << std::dec << ": {\n";
            u64 ret = 0;
            bool call = has_op(b, IR::Opcode::PushRSB, &ret);
            if (call) ret = va_of(IR::LocationDescriptor{ret});
            u64 fault_pc = 0;
            bool fault = false;
            for (auto& i : b) {
                const IR::Opcode op = i.GetOpcode();
                if (op == IR::Opcode::Void || op == IR::Opcode::PushRSB) continue;
                if (op == IR::Opcode::A64ExceptionRaised) {
                    // The block ran into the next block's start (or the function's end): fall through.
                    if (i.GetArg(1).GetU64() == (u64)A64::Exception::NoExecuteFault) {
                        fault = true;
                        fault_pc = i.GetArg(0).GetU64() - kFakeBase;
                        break;
                    }
                }
                int id = ++n;
                names[&i] = id;
                std::string nm = IR::GetNameOf(op);
                if (op == IR::Opcode::GetCarryFromOp || op == IR::Opcode::GetOverflowFromOp || op == IR::Opcode::GetNZCVFromOp ||
                    op == IR::Opcode::GetNZFromOp || op == IR::Opcode::GetUpperFromOp || op == IR::Opcode::GetLowerFromOp) {
                    static const std::map<IR::Opcode, const char*> field = {
                        {IR::Opcode::GetCarryFromOp, "c"}, {IR::Opcode::GetOverflowFromOp, "o"}, {IR::Opcode::GetNZCVFromOp, "nzcv"},
                        {IR::Opcode::GetNZFromOp, "nz"}, {IR::Opcode::GetUpperFromOp, "hi"}, {IR::Opcode::GetLowerFromOp, "lo"}};
                    o << "  auto t" << id << " = t" << names.at(i.GetArg(0).GetInst()) << "." << field.at(op) << ";\n";
                    continue;
                }
                bool fl = false;  // a flag-reading pseudo-op uses it: the op returns a struct
                for (IR::Opcode po : {IR::Opcode::GetCarryFromOp, IR::Opcode::GetOverflowFromOp, IR::Opcode::GetNZCVFromOp,
                                      IR::Opcode::GetNZFromOp, IR::Opcode::GetUpperFromOp, IR::Opcode::GetLowerFromOp})
                    if (i.HasAssociatedPseudoOperation() && const_cast<IR::Inst&>(i).GetAssociatedPseudoOperation(po)) fl = true;
                if (fl) {
                    flagged.insert(&i);
                    nm += "_f";
                }
                if (locals && !fl) {  // register accesses as the locals
                    std::string a0 = i.NumArgs() ? arg(i.GetArg(0)) : "", a1 = i.NumArgs() > 1 ? arg(i.GetArg(1)) : "";
                    std::string tn = "t" + std::to_string(id);
                    std::string line;
                    switch (op) {
                    case IR::Opcode::A64GetX: line = "auto " + tn + " = X" + a0 + ";"; break;
                    case IR::Opcode::A64GetW: line = "auto " + tn + " = (u32)X" + a0 + ";"; break;
                    case IR::Opcode::A64SetX: line = "X" + a0 + " = " + a1 + ";"; break;
                    case IR::Opcode::A64SetW: line = "X" + a0 + " = (u64)(u32)" + a1 + ";"; break;
                    case IR::Opcode::A64GetSP: line = "auto " + tn + " = SP;"; break;
                    case IR::Opcode::A64SetSP: line = "SP = " + a0 + ";"; break;
                    case IR::Opcode::A64GetS: line = "auto " + tn + " = rc::U128{V" + a0 + ".lo & 0xffffffffu, 0};"; break;
                    case IR::Opcode::A64GetD: line = "auto " + tn + " = rc::U128{V" + a0 + ".lo, 0};"; break;
                    case IR::Opcode::A64GetQ: line = "auto " + tn + " = V" + a0 + ";"; break;
                    case IR::Opcode::A64SetS: line = "V" + a0 + " = rc::U128{" + a1 + ".lo & 0xffffffffu, 0};"; break;
                    case IR::Opcode::A64SetD: line = "V" + a0 + " = rc::U128{" + a1 + ".lo, 0};"; break;
                    case IR::Opcode::A64SetQ: line = "V" + a0 + " = " + a1 + ";"; break;
                    default: break;
                    }
                    if (!line.empty()) {
                        o << "  " << line << "\n";
                        continue;
                    }
                }
                used_ops.insert(nm);
                std::string call_s = "rc::" + nm + "(L";
                for (size_t k = 0; k < i.NumArgs(); k++) call_s += ", " + arg(i.GetArg(k));
                call_s += ")";
                if (i.GetType() == IR::Type::Void) o << "  " << call_s << ";\n";
                else o << "  auto t" << id << " = " << call_s << ";\n";
            }
            if (fault) jump(f, fault_pc, "  ");
            else term(f, b, b.GetTerminal(), "  ", call, ret);
            o << "}\n";
        }
        o << "}\n#undef RC_FLUSH\n#undef RC_RELOAD\n\n";
    }
};

static int emit(const char* list, const char* out_path, bool locals) {
    std::ifstream in(list);
    std::string line;
    std::vector<Fn> fns;
    while (std::getline(in, line)) {
        if (line.empty() || line[0] == '#') continue;
        std::istringstream ls(line);
        std::string va, size, name;
        ls >> va >> size >> name;
        fns.push_back(Fn{std::stoull(va, nullptr, 16), std::stoull(size), name});
    }
    Emitter e;
    e.locals = locals;
    for (auto& f : fns) e.funcs.insert(f.start);
    e.o << "// Generated by tools/recomp-proto/recomp_gen.cpp from libSOA.so 3.7.0: do not edit.\n";
    e.o << "#include \"recomp_rt.h\"\nnamespace rc_gen {\nusing namespace rc::types;\n\n";
    // RECOMP_ONLY_OPS=FILE: leave out the functions that use an opcode the file doesn't list
    // (recomp_rt.h's; for size samples of code the prototype's run time doesn't cover yet)
    std::set<std::string> only;
    if (const char* p = getenv("RECOMP_ONLY_OPS")) {
        std::ifstream f(p);
        std::string op;
        while (f >> op) only.insert(op);
    }
    std::vector<Fn> kept;
    size_t skipped = 0;
    for (auto& f : fns) {
        discover(f);
        if (!only.empty()) {
            bool ok = true;
            for (auto& [va, b] : f.blocks)
                for (auto& i : b) {
                    std::string nm = IR::GetNameOf(i.GetOpcode());
                    if (i.GetOpcode() == IR::Opcode::Void || i.GetOpcode() == IR::Opcode::PushRSB || i.IsAPseudoOperation() && nm.find("FromOp") != std::string::npos) continue;
                    if (i.GetOpcode() == IR::Opcode::A64ExceptionRaised && i.GetArg(1).GetU64() == (u64)A64::Exception::NoExecuteFault) continue;
                    if (!only.count(nm)) ok = false;
                }
            if (!ok) {
                skipped++;
                continue;
            }
        }
        kept.push_back(std::move(f));
    }
    if (!only.empty()) fprintf(stderr, "kept %zu functions, left out %zu (opcodes not in RECOMP_ONLY_OPS)\n", kept.size(), skipped);
    fns = std::move(kept);
    for (auto& f : fns) {
        e.fail.clear();
        e.function(f);
        if (!e.fail.empty()) fprintf(stderr, "%s: %s\n", f.name.c_str(), e.fail.c_str());
    }
    e.o << "}  // namespace rc_gen\n\n";
    // The table: guest vaddr -> host function.
    e.o << "extern const rc::Entry rc_table[];\nextern const unsigned rc_table_size;\n";
    e.o << "const rc::Entry rc_table[] = {  // sorted by vaddr\n";
    std::sort(fns.begin(), fns.end(), [](const Fn& a, const Fn& b) { return a.start < b.start; });
    for (auto& f : fns) e.o << "  {0x" << std::hex << f.start << std::dec << ", rc_gen::f_" << std::hex << f.start << std::dec << ", \"" << f.name << "\"},\n";
    e.o << "};\nconst unsigned rc_table_size = " << fns.size() << ";\n";
    std::ofstream(out_path) << e.o.str();
    fprintf(stderr, "ops used:");
    for (auto& s : e.used_ops) fprintf(stderr, " %s", s.c_str());
    fprintf(stderr, "\n");
    return 0;
}

int main(int argc, char** argv) {
    if (argc < 4) {
        fprintf(stderr, "usage: recomp_gen stats LIB FUNCTIONS.tsv | emit LIB FUNCS.txt OUT.cpp\n");
        return 2;
    }
    if (!load_elf(argv[2])) {
        fprintf(stderr, "cannot read %s\n", argv[2]);
        return 1;
    }
    if (!strcmp(argv[1], "stats")) return stats(argv[3]);
    if (!strcmp(argv[1], "emit") && argc >= 5) return emit(argv[3], argv[4], argc >= 6 && !strcmp(argv[5], "--locals"));
    return 2;
}
