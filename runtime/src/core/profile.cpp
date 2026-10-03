#include <cxxabi.h>
// Guest profiler: function table, one-shot coverage traps and a stack-sampling profiler.
//
// Function table. libSOA.so has no .symtab; .dynsym only names the ~25k exported functions,
// and more than half of .text is local functions. Local function entries are recovered from:
//   - BL targets found by a linear scan of .text (the compiler only emits BL for calls),
//   - R_AARCH64_RELATIVE relocations whose target is in .text (vtables, function-pointer tables),
//   - .eh_frame_hdr FDE start addresses,
//   - adjacent "ADRP xN / ADD xN, xN, #lo12" pairs that materialize a .text address (C callbacks).
// Locals are named FUN_<ghidra address> (Ghidra address = ELF vaddr + 0x100000, usable with
// tools/decomp_at.sh). A wrong "entry" (e.g. a label inside a function) is harmless: see below.
//
// Coverage. Every function entry gets its first instruction replaced by "SVC #<coverage>".
// The first time a JIT reaches it, the trap records the function, writes the original
// instruction back, invalidates that JIT's translation of the address and resumes at the entry,
// so the function runs unmodified. Other threads' JITs may still hold a translation with the
// trap; they take the same path (already recorded -> invalidate -> resume). Because only one
// instruction is replaced and the original is re-executed in place, nothing is relocated: short
// functions, PC-relative prologues and mid-function branch targets are all fine.
//
// Sampling. A timer thread wakes SOA_PROFILE_HZ times a second and looks at every guest thread:
//   - running JIT code: it halts that JIT (HaltExecution with a profiler reason); the guest
//     thread's run loop (guest_call) records its own stack and resumes;
//   - inside host code (an HLE import or a native replacement, published by CallSVC): the timer
//     thread records the stack itself from the registers saved at the SVC; the leaf frame is
//     "[hle]<import>" or "[native]<symbol>", so host time is attributed separately.
// Stacks come from the leaf PC, LR (for leaf functions) and the frame-pointer chain, and continue
// across nested guest_call levels (host code calling back into the guest).
#include "core/profile.h"

#include <dlfcn.h>
#include <elf.h>
#include <pthread.h>
#include <ucontext.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

#include <algorithm>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

#include "core/log.h"
#include "dynarmic/interface/A64/a64.h"

namespace soa {
namespace {

using Clock = std::chrono::steady_clock;

enum Source : u8 { kSrcExport = 1, kSrcBl = 2, kSrcReloc = 4, kSrcEh = 8, kSrcAdrp = 16 };

struct Func {
    u64 addr;          // guest address
    u64 size;          // symbol size (exports) or distance to the next entry
    const char* name;  // mangled export name, or nullptr for a local function
    u8 sources = 0;
};

LoadedLib* g_lib = nullptr;
const u32* g_code = nullptr;  // pristine .text from the file (guest .text has hooks patched in)
u64 g_text_lo = 0, g_text_hi = 0;  // guest addresses
u64 g_plt_lo = 0, g_plt_hi = 0;
std::vector<Func> g_funcs;           // sorted by addr
std::string g_dir;
bool g_coverage = false, g_sampling = false;
int g_hz = 1000;
Clock::time_point g_t0;

// Coverage state, indexed like g_funcs.
std::unique_ptr<u32[]> g_orig;                 // original first instruction
std::unique_ptr<std::atomic<u8>[]> g_state;    // 0 = not patched, 1 = trap armed, 2 = executed
std::unique_ptr<float[]> g_first_hit;          // seconds since start
std::atomic<int> g_cov_hits{0};
int g_cov_patched = 0;

// Sampled stacks: frame codes, leaf first.
u32 g_wait_thunk = 0;  // pseudo-import "native_wait": a native replacement blocked in a host wait
constexpr u64 kHle = 1ull << 40, kNative = 2ull << 40, kUnknown = 3ull << 40, kThread = 4ull << 40, kKindMask = 0xffull << 40;
struct VecHash {
    size_t operator()(const std::vector<u64>& v) const {
        u64 h = 1469598103934665603ull;
        for (u64 x : v) h = (h ^ x) * 1099511628211ull;
        return h;
    }
};
std::mutex g_stacks_mutex;
std::unordered_map<std::vector<u64>, u64, VecHash> g_stacks;
std::atomic<u64> g_samples{0}, g_samples_guest{0}, g_samples_host{0};

std::atomic<u64> g_sampler_cpu_ns{0};
std::mutex g_dump_mutex;
std::atomic<bool> g_dump_requested{false};

// ---- function table -------------------------------------------------------

int func_index(u64 addr) {  // function containing addr, or -1
    if (addr < g_text_lo || addr >= g_text_hi) return -1;
    auto it = std::upper_bound(g_funcs.begin(), g_funcs.end(), addr, [](u64 a, const Func& f) { return a < f.addr; });
    if (it == g_funcs.begin()) return -1;
    return (int)(it - g_funcs.begin()) - 1;
}

int func_index_exact(u64 addr) {
    auto it = std::lower_bound(g_funcs.begin(), g_funcs.end(), addr, [](const Func& f, u64 a) { return f.addr < a; });
    return it != g_funcs.end() && it->addr == addr ? (int)(it - g_funcs.begin()) : -1;
}

std::string func_name(size_t i) {
    const Func& f = g_funcs[i];
    if (f.name) return f.name;
    char b[32];
    snprintf(b, sizeof b, "FUN_%08lx", f.addr - g_lib->base + 0x100000);
    return b;
}

s64 sext(u64 v, int bits) { return (s64)(v << (64 - bits)) >> (64 - bits); }

bool build_function_table(LoadedLib& lib) {
    int fd = open(lib.path.c_str(), O_RDONLY);
    if (fd < 0) return false;
    struct stat st;
    fstat(fd, &st);
    auto* file = (const u8*)mmap(nullptr, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    close(fd);
    if (file == MAP_FAILED) return false;
    auto* eh = (const Elf64_Ehdr*)file;
    auto* sh = (const Elf64_Shdr*)(file + eh->e_shoff);
    const char* shstr = (const char*)file + sh[eh->e_shstrndx].sh_offset;
    auto find = [&](const char* n) -> const Elf64_Shdr* {
        for (int i = 0; i < eh->e_shnum; i++)
            if (!strcmp(shstr + sh[i].sh_name, n)) return &sh[i];
        return nullptr;
    };
    const Elf64_Shdr* text = find(".text");
    if (!text) return false;
    if (find(".symtab")) LOGI("profile", "note: .symtab present but not used");
    g_text_lo = lib.base + text->sh_addr;
    g_text_hi = g_text_lo + text->sh_size;
    if (const Elf64_Shdr* plt = find(".plt")) g_plt_lo = lib.base + plt->sh_addr, g_plt_hi = g_plt_lo + plt->sh_size;

    std::map<u64, Func> m;  // addr -> func
    auto add = [&](u64 vaddr, u8 src, const char* name = nullptr, u64 size = 0) {
        u64 a = lib.base + vaddr;
        if (a < g_text_lo || a >= g_text_hi || (a & 3)) return;
        Func& f = m[a];
        f.addr = a;
        f.sources |= src;
        if (name && (!f.name || strlen(name) < strlen(f.name))) f.name = name, f.size = size;  // prefer the shortest alias
    };

    // Exports
    const Elf64_Shdr* dynsym = find(".dynsym");
    const Elf64_Shdr* dynstr = find(".dynstr");
    if (dynsym && dynstr) {
        auto* syms = (const Elf64_Sym*)(file + dynsym->sh_offset);
        size_t n = dynsym->sh_size / sizeof(Elf64_Sym);
        const char* strs = (const char*)file + dynstr->sh_offset;
        for (size_t i = 0; i < n; i++)
            if (ELF64_ST_TYPE(syms[i].st_info) == STT_FUNC && syms[i].st_shndx != SHN_UNDEF)
                add(syms[i].st_value, kSrcExport, strdup(strs + syms[i].st_name), syms[i].st_size);
    }
    // BL targets and ADRP+ADD pairs
    auto* code = (const u32*)(file + text->sh_offset);
    g_code = code;
    size_t nw = text->sh_size / 4;
    for (size_t i = 0; i < nw; i++) {
        u32 w = code[i];
        u64 pc = text->sh_addr + i * 4;
        if ((w & 0xfc000000) == 0x94000000) {
            add(pc + sext(w & 0x3ffffff, 26) * 4, kSrcBl);
        } else if ((w & 0x9f000000) == 0x90000000 && i + 1 < nw) {
            u32 w2 = code[i + 1];
            u32 rd = w & 31;
            if ((w2 & 0xffc00000) == 0x91000000 && ((w2 >> 5) & 31) == rd && (w2 & 31) == rd) {
                u64 imm = ((w >> 29) & 3) | (((w >> 5) & 0x7ffff) << 2);
                u64 page = (pc & ~0xfffull) + (sext(imm, 21) << 12);
                add(page + ((w2 >> 10) & 0xfff), kSrcAdrp);
            }
        }
    }
    // RELATIVE relocations into .text
    if (const Elf64_Shdr* rela = find(".rela.dyn")) {
        auto* r = (const Elf64_Rela*)(file + rela->sh_offset);
        size_t n = rela->sh_size / sizeof(Elf64_Rela);
        for (size_t i = 0; i < n; i++)
            if (ELF64_R_TYPE(r[i].r_info) == R_AARCH64_RELATIVE) add(r[i].r_addend, kSrcReloc);
    }
    // .eh_frame_hdr binary search table
    if (const Elf64_Shdr* ehh = find(".eh_frame_hdr")) {
        const u8* p = file + ehh->sh_offset;
        if (p[0] == 1 && p[1] == 0x1b && p[2] == 0x03 && p[3] == 0x3b) {
            u32 count;
            memcpy(&count, p + 8, 4);
            const s32* t = (const s32*)(p + 12);
            for (u32 i = 0; i < count && 12 + (i + 1) * 8 <= ehh->sh_size; i++) add(ehh->sh_addr + (s64)t[i * 2], kSrcEh);
        } else {
            LOGW("profile", ".eh_frame_hdr encoding %02x/%02x/%02x not handled", p[1], p[2], p[3]);
        }
    }
    // (the file mapping stays: g_code points into it)

    g_funcs.reserve(m.size());
    for (auto& [a, f] : m) g_funcs.push_back(f);
    for (size_t i = 0; i < g_funcs.size(); i++) {
        u64 gap = (i + 1 < g_funcs.size() ? g_funcs[i + 1].addr : g_text_hi) - g_funcs[i].addr;
        if (!g_funcs[i].size || g_funcs[i].size > gap) g_funcs[i].size = gap;
    }
    return true;
}

// ---- coverage ------------------------------------------------------------

void coverage_trap(Cpu& c) {
    u64 addr = c.pc() - 4;
    int i = func_index_exact(addr);
    if (i < 0 || g_state[i].load() == 0) fatal("coverage: unexpected trap at %s", describe_guest_addr(addr).c_str());
    u8 expected = 1;
    if (g_state[i].compare_exchange_strong(expected, 2)) {
        g_first_hit[i] = std::chrono::duration<float>(Clock::now() - g_t0).count();
        __atomic_store_n((u32*)addr, g_orig[i], __ATOMIC_SEQ_CST);
        g_cov_hits.fetch_add(1, std::memory_order_relaxed);
    }
    // Another thread may have won the race and not restored the word yet: we just come back here.
    c.jit()->InvalidateCacheRange(addr, 4);
    c.jit()->SetPC(addr);
}

void install_coverage() {
    size_t n = g_funcs.size();
    g_orig.reset(new u32[n]);
    g_state.reset(new std::atomic<u8>[n]);
    g_first_hit.reset(new float[n]);
    u32 trap = thunk_trap_insn(make_thunk("<coverage>", coverage_trap));
    int skipped = 0;
    for (size_t i = 0; i < n; i++) {
        g_state[i].store(0);
        g_first_hit[i] = -1;
        u64 a = g_funcs[i].addr;
        u32 w = *(u32*)a;
        g_orig[i] = w;
        // Already hooked (native replacement, trace) or already a trap: leave alone.
        if (thunk_name_at(a) || (w & 0xffe0001f) == 0xd4000001) {
            skipped++;
            continue;
        }
        *(u32*)a = trap;
        g_state[i].store(1);
        g_cov_patched++;
    }
    LOGI("profile", "coverage: %d function entries armed (%d skipped: hooked)", g_cov_patched, skipped);
}

// ---- sampling --------------------------------------------------------------

u64 frame_code(u64 addr) {
    int i = func_index(addr);
    return i >= 0 ? (u64)i : kUnknown;
}

// ---- unwinding --------------------------------------------------------------
//
// libSOA.so is built without frame pointers (x29 is an ordinary callee-saved register), so
// stacks are unwound from the functions' prologues instead: the prologue tells how far SP moves
// and where x30 (and x29) are saved. Each step is validated (the return address must follow a
// BL/BLR); if it fails, the stack is scanned for a return address whose BL targets the current
// function. Unwinding stops at the first frame that can't be recovered ("[truncated]").

u32 insn(u64 a) { return g_code[(a - g_text_lo) / 4]; }

struct Frame {  // state of a function's prologue, relative to the CFA (SP at entry)
    u32 alloc = 0;           // bytes SP has moved down
    s32 lr_off = 1, fp_off = 1;  // where x30 / x29 were stored (CFA-relative, <=0), 1 = not stored
    s32 fp_set = 1;          // x29 = CFA + fp_set once "mov/add x29, sp" ran (<=0), 1 = not set
    bool dynamic = false;    // SP also moves by a register amount (alloca, stack probes)
};
struct FrameInfo {
    std::atomic<u8> ready{0};
    u16 p0 = 0, pend = 0;  // prologue [p0, pend) in instructions from the entry; p0 == 0xffff: frameless
    Frame full;
};
std::unique_ptr<FrameInfo[]> g_frames;
constexpr u16 kNoFrame = 0xffff;

bool is_sp_dec(u32 w) {
    if ((w & 0xff8003ff) == 0xd10003ff) return true;                                            // sub sp, sp, #imm
    if (((w & 0xffc00000) == 0xa9800000 || (w & 0xffc00000) == 0x6d800000 || (w & 0xffc00000) == 0xad800000) && ((w >> 5) & 31) == 31)
        return (w >> 21) & 1;                                                                        // stp ..., [sp, #-n]! (negative imm7)
    if (((w & 0xffe00c00) == 0xf8000c00 || (w & 0xffe00c00) == 0xfc000c00) && ((w >> 5) & 31) == 31) return (w >> 20) & 1;  // str ..., [sp, #-n]!
    return false;
}
bool is_branch(u32 w) {
    return (w & 0x7c000000) == 0x14000000 || (w & 0xff000010) == 0x54000000 || (w & 0x7e000000) == 0x34000000 ||
           (w & 0x7e000000) == 0x36000000 || (w & 0xfe1f0000) == 0xd61f0000;  // B/BL, B.cond, CBZ/CBNZ, TBZ/TBNZ, BR/BLR/RET
}

// Applies one instruction to the prologue state; returns true if it was a prologue instruction.
bool apply(u32 w, Frame& f) {
    auto store = [&](int rt, s32 at) {
        if (rt == 30) f.lr_off = at;
        if (rt == 29) f.fp_off = at;
    };
    u32 rn = (w >> 5) & 31, rt = w & 31, rt2 = (w >> 10) & 31;
    s32 sp_rel = -(s32)f.alloc;  // CFA-relative address of the current SP
    if ((w & 0xff8003ff) == 0xd10003ff) {  // sub sp, sp, #imm{, lsl 12}
        f.alloc += ((w >> 10) & 0xfff) << (((w >> 22) & 1) ? 12 : 0);
        return true;
    }
    if ((w & 0xffe0ffff) == 0xcb2063ff) {  // sub sp, sp, xN
        f.dynamic = true;
        return true;
    }
    if ((w & 0xff8003e0) == 0x910003e0 && rt == 29) {  // add x29, sp, #imm / mov x29, sp
        f.fp_set = sp_rel + (s32)(((w >> 10) & 0xfff) << (((w >> 22) & 1) ? 12 : 0));
        return true;
    }
    if (rn != 31) return false;
    u32 top = w & 0xffc00000;
    if (top == 0xa9800000 || top == 0xa9000000 || top == 0x6d800000 || top == 0x6d000000 || top == 0xad800000 || top == 0xad000000) {  // stp
        int scale = top >= 0xad000000 ? 16 : 8;
        s32 imm = (s32)sext((w >> 15) & 0x7f, 7) * scale;
        bool pre = top == 0xa9800000 || top == 0x6d800000 || top == 0xad800000;
        if (pre) f.alloc += (u32)-imm, sp_rel -= -imm;
        s32 at = pre ? sp_rel : sp_rel + imm;
        if (top == 0xa9800000 || top == 0xa9000000) store(rt, at), store(rt2, at + 8);
        return true;
    }
    if ((w & 0xffe00c00) == 0xf8000c00 || (w & 0xffe00c00) == 0xfc000c00) {  // str x/d, [sp, #imm]!
        s32 imm = (s32)sext((w >> 12) & 0x1ff, 9);
        f.alloc += (u32)-imm;
        if ((w & 0xffe00c00) == 0xf8000c00) store(rt, sp_rel + imm);
        return true;
    }
    if (top == 0xf9000000 || top == 0xfd000000) {  // str x/d, [sp, #imm]
        if (top == 0xf9000000) store(rt, sp_rel + (s32)(((w >> 10) & 0xfff) * 8));
        return true;
    }
    return false;
}

// Runs the prologue from p0 up to (not including) instruction index `upto`.
Frame run_prologue(u64 entry, u16 p0, u16 upto) {
    Frame f;
    for (u16 i = p0; i < upto; i++) apply(insn(entry + i * 4ull), f);
    return f;
}

FrameInfo& frame_info(int fi) {
    FrameInfo& info = g_frames[fi];
    if (info.ready.load(std::memory_order_acquire)) return info;
    const Func& fn = g_funcs[fi];
    u32 n = (u32)std::min<u64>(fn.size / 4, 1024);
    u16 p0 = kNoFrame, pend = 0;
    for (u32 i = 0; i < n; i++) {
        u32 w = insn(fn.addr + i * 4ull);
        if (is_sp_dec(w)) {
            p0 = (u16)i;
            break;
        }
        if (w == 0xd65f03c0 && i + 1 >= n) break;
    }
    Frame f;
    if (p0 != kNoFrame) {
        u32 other = 0;
        pend = p0;
        for (u32 i = p0; i < n && i < p0 + 48u; i++) {
            u32 w = insn(fn.addr + i * 4ull);
            if (is_branch(w)) break;
            if (apply(w, f)) {
                pend = (u16)(i + 1);
                other = 0;
            } else if (++other > 8) {
                break;
            }
        }
        f = run_prologue(fn.addr, p0, pend);
    }
    info.p0 = p0;
    info.pend = pend;
    info.full = f;
    info.ready.store(1, std::memory_order_release);
    return info;
}

bool is_return_site(u64 ret) {
    if (ret < g_text_lo + 4 || ret >= g_text_hi || (ret & 3)) return false;
    u32 w = insn(ret - 4);
    return (w & 0xfc000000) == 0x94000000 || (w & 0xfffffc1f) == 0xd63f0000;  // BL / BLR
}
u64 bl_target(u64 ret) {
    u32 w = insn(ret - 4);
    return (w & 0xfc000000) == 0x94000000 ? ret - 4 + sext(w & 0x3ffffff, 26) * 4 : 0;
}

// True if SP has already been restored at pc (between "add sp"/"ldp ..., [sp], #n" and ret).
bool in_epilogue_tail(u64 entry, u64 pc) {
    for (int k = 0; k < 6; k++) {
        u64 a = pc + k * 4ull;
        if (a >= g_text_hi) return false;
        u32 w = insn(a);
        if (w == 0xd65f03c0 || (w & 0xfc000000) == 0x14000000) {  // ret / tail call
            for (int j = 1; j <= 4 && pc - j * 4ull >= entry; j++) {
                u32 p = insn(pc - j * 4ull);
                if ((p & 0xff8003ff) == 0x910003ff || (((p & 0xffc00000) == 0xa8c00000 || (p & 0xffc00000) == 0x6cc00000) && ((p >> 5) & 31) == 31) ||
                    ((p & 0xffe00c00) == 0xf8400400 && ((p >> 5) & 31) == 31))
                    return true;
            }
            return false;
        }
        if (is_branch(w) || (w & 0xff8003ff) == 0x910003ff || (w & 0xffc00000) == 0xa8c00000 || (w & 0xffe00c00) == 0xf8400400) return false;
    }
    return false;
}

struct UnwindState {
    u64 pc, sp, fp, lr;
    bool lr_live;  // lr holds this frame's return address if it hasn't been saved
    bool is_ret;   // pc is a return address (the function is the one containing pc - 4)
};
enum Step { kStepOk, kStepEnd, kStepFail };

// One step: from the function containing st.pc to its caller.
Step unwind_step(UnwindState& st, const ProfThread& t) {
    int fi = func_index(st.is_ret ? st.pc - 4 : st.pc);
    if (fi < 0) return kStepFail;
    const Func& fn = g_funcs[fi];
    FrameInfo& info = frame_info(fi);
    u16 idx = (u16)std::min<u64>((st.pc - fn.addr) / 4, 0xfffe);
    Frame f;
    bool framed = info.p0 != kNoFrame && idx > info.p0 && !in_epilogue_tail(fn.addr, st.pc);
    if (framed) f = idx < info.pend ? run_prologue(fn.addr, info.p0, idx) : info.full;
    u64 ret = 0, cfa = st.sp;
    bool ok = false;
    if (framed) {
        if (f.dynamic && idx >= info.pend) {
            if (f.fp_set > 0) return kStepFail;
            cfa = st.fp - (s64)f.fp_set;
        } else {
            cfa = st.sp + f.alloc;
        }
        if (f.lr_off <= 0) {
            u64 slot = cfa + (s64)f.lr_off;
            if (slot >= t.stack_lo && slot + 8 <= t.stack_hi) ret = *(const u64*)slot;
        } else if (st.lr_live) {
            ret = st.lr;
        }
        ok = is_return_site(ret);
    } else if (st.lr_live) {
        ret = st.lr;
        ok = is_return_site(ret);
    }
    if (!ok && ret && ret == host_return_addr()) return kStepEnd;  // outermost guest function
    u64 new_fp = st.fp;
    if (ok && framed && f.fp_off <= 0) {
        u64 slot = cfa + (s64)f.fp_off;
        if (slot >= t.stack_lo && slot + 8 <= t.stack_hi) new_fp = *(const u64*)slot;
    }
    if (!ok) {
        // Fallback: look for a saved return address whose BL calls this function, then use this
        // function's full frame layout to find the caller's SP.
        const Frame& ff = info.full;
        if (info.p0 == kNoFrame || ff.lr_off > 0 || ff.dynamic) return kStepFail;
        for (u64 a = st.sp; a + 8 <= t.stack_hi && a < st.sp + 8192; a += 8) {
            u64 v = *(const u64*)a;
            if (is_return_site(v) && bl_target(v) == fn.addr) {
                ret = v;
                cfa = a - (s64)ff.lr_off;
                ok = true;
                break;
            }
        }
        if (!ok) return kStepFail;
    }
    if (cfa < st.sp) return kStepFail;  // the stack only grows towards the caller
    st = {ret, cfa, new_fp, 0, false, true};
    return kStepOk;
}

constexpr u64 kTruncated = kUnknown | 1;

// Appends the frames of one JIT level, leaf first. have_leaf: pc is inside the leaf function
// (a halted JIT); otherwise pc is an SVC site and the level starts with its caller (in LR).
void walk_level(u64 pc, u64 lr, u64 fp, u64 sp, const ProfThread& t, bool have_leaf, std::vector<u64>& out) {
    UnwindState st{pc, sp, fp, lr, true, false};
    if (have_leaf && (pc & 0xfff) && ((*(const u32*)(pc - 4)) & 0xffe0001f) == 0xd4000001) {
        // Stopped right after an SVC (the JIT checks for halts there): host code has just
        // returned and the next instruction is the RET of a thunk stub or hooked entry. Count
        // it as the caller's time, not as the hooked function's.
        have_leaf = false;
    }
    if (have_leaf && pc >= g_plt_lo && pc < g_plt_hi) have_leaf = false;  // in a PLT stub, on the way to an import
    if (have_leaf) {
        out.push_back(frame_code(pc));
        if (func_index(pc) < 0) {  // not in libSOA.so .text (a trampoline or thunk stub)
            if (!is_return_site(lr)) return;
            st = {lr, sp, fp, 0, false, true};
            out.push_back(frame_code(lr - 4));
        }
    } else {
        // Entered host code through a PLT/stub or a hooked entry: nothing was pushed yet.
        if (lr == host_return_addr()) return;
        if (!is_return_site(lr)) {
            out.push_back(kTruncated);
            return;
        }
        st = {lr, sp, fp, 0, false, true};
        out.push_back(frame_code(lr - 4));
    }
    for (int k = 0; k < 256; k++) {
        Step r = unwind_step(st, t);
        if (r == kStepEnd) return;
        if (r == kStepFail) {
            out.push_back(kTruncated);
            return;
        }
        out.push_back(frame_code(st.pc - 4));
    }
}

// A level that is inside host code: "[hle]name" / "[native]sym", then its guest caller chain.
void walk_host_level(const ProfThread& t, int level, std::vector<u64>& out) {
    const ProfLevel& l = t.lv[level];
    u32 svc = l.svc.load(std::memory_order_acquire);
    u64 site = l.pc - 4;
    bool native = site >= g_text_lo && site < g_text_hi;
    if (svc && l.wait.load(std::memory_order_acquire) && g_wait_thunk) out.push_back(kHle | g_wait_thunk);
    if (svc) out.push_back((native ? kNative : kHle) | svc);  // 0: the level is just returning
    walk_level(l.pc, l.lr, l.fp, l.sp, t, false, out);
}

void finish_stack(const ProfThread& t, int d, std::vector<u64>& out) {
    for (int level = d - 1; level >= 0; level--) walk_host_level(t, level, out);
    int e = func_index(t.entry.load(std::memory_order_relaxed));
    out.push_back(kThread | (e >= 0 ? (u64)e : 0xffffffffull));
}

// Counts one sample of a stack; returns its counter (element references stay valid).
u64* record(std::vector<u64>&& st, bool guest) {
    g_samples.fetch_add(1, std::memory_order_relaxed);
    (guest ? g_samples_guest : g_samples_host).fetch_add(1, std::memory_order_relaxed);
    std::lock_guard lk(g_stacks_mutex);
    u64& n = g_stacks[std::move(st)];
    n++;
    return &n;
}

// Guest thread, halted by the sampler.
void on_sample(Cpu& c, ProfThread& t) {
    int d = t.depth.load(std::memory_order_relaxed);
    if (d <= 0 || d > kProfLevels) return;
    std::vector<u64> st;
    st.reserve(32);
    walk_level(c.pc(), c.x(30), c.x(29), c.sp(), t, true, st);
    finish_stack(t, d - 1, st);
    record(std::move(st), true);
}

// Last host-code stack seen per thread (sampler thread only): a thread blocked in the same
// call (same depth and SVC sequence number) is counted again without unwinding.
struct LastHost {
    int depth = 0;
    u32 seq = 0;
    u64* counter = nullptr;
};
std::unordered_map<int, LastHost> g_last_host;

// SOA_PROFILE_HOST=1 (with SOA_PROFILE): host-code samples inside native replacements. When the
// sampler finds a thread in a native replacement (not in a marked wait), it sends it SIGPROF; the
// handler records the host PC. profile_dump() writes host.tsv (PC offsets in the soa executable
// and counts); port/scripts/host_profile.py symbolizes it (self time per C++ function, e.g. per
// transcribed body or readable rewrite, which the guest-level stacks can't see inside a native).
bool g_host_sampling = false;
constexpr size_t kHostPcs = 1 << 23;
u64* g_host_pcs = nullptr;
std::atomic<size_t> g_host_npcs{0};
u64 g_exe_base = 0;
void on_sigprof(int, siginfo_t*, void* uc) {
    size_t i = g_host_npcs.fetch_add(1, std::memory_order_relaxed);
    if (i < kHostPcs) g_host_pcs[i] = (u64)((ucontext_t*)uc)->uc_mcontext.gregs[REG_RIP];
}
void host_sample(ProfThread& t, int d) {
    if (!g_host_sampling || !t.host_thread) return;
    const ProfLevel& l = t.lv[d - 1];
    u64 site = l.pc - 4;
    if (site < g_text_lo || site >= g_text_hi || l.wait.load(std::memory_order_acquire)) return;  // HLE import / wait
    pthread_kill((pthread_t)t.host_thread, SIGPROF);
}
void init_host_sampling() {
    const char* e = getenv("SOA_PROFILE_HOST");
    if (!e || !*e || !strcmp(e, "0")) return;
    Dl_info di;
    if (!dladdr((void*)&profile_init, &di)) return;
    g_exe_base = (u64)di.dli_fbase;
    g_host_pcs = new u64[kHostPcs];
    struct sigaction sa = {};
    sa.sa_sigaction = on_sigprof;
    sa.sa_flags = SA_SIGINFO | SA_RESTART;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGPROF, &sa, nullptr);
    g_host_sampling = true;
}
void write_host_samples(FILE* f) {
    size_t n = std::min(g_host_npcs.load(std::memory_order_relaxed), kHostPcs);
    std::unordered_map<u64, u64> hist;
    for (size_t i = 0; i < n; i++) hist[g_host_pcs[i] - g_exe_base]++;
    std::vector<std::pair<u64, u64>> v(hist.begin(), hist.end());
    std::sort(v.begin(), v.end());
    fprintf(f, "# offset\tsamples   (host PCs in native replacements, relative to the soa executable; %zu samples)\n", n);
    for (auto& [pc, c] : v) fprintf(f, "%lx\t%lu\n", pc, c);
}

void sample_thread(ProfThread& t, void*) {
    int d = t.depth.load(std::memory_order_acquire);
    if (d <= 0 || d > kProfLevels) return;
    if (t.lv[d - 1].svc.load(std::memory_order_acquire)) {
        host_sample(t, d);
        u32 seq = t.lv[d - 1].seq.load(std::memory_order_relaxed);
        LastHost& last = g_last_host[t.id];
        if (last.depth == d && last.seq == seq && last.counter) {
            g_samples.fetch_add(1, std::memory_order_relaxed);
            g_samples_host.fetch_add(1, std::memory_order_relaxed);
            std::lock_guard lk(g_stacks_mutex);
            ++*last.counter;
            return;
        }
        std::vector<u64> st;
        st.reserve(32);
        finish_stack(t, d, st);
        last = {d, seq, record(std::move(st), false)};
    } else if (Cpu* c = t.cpu[d - 1].load(std::memory_order_acquire)) {
        prof_request_sample(c);
    }
}

void sampler_main() {
    auto period = std::chrono::nanoseconds(1000000000 / g_hz);
    auto next = Clock::now(), last_dump = next;
    for (;;) {
        next += period;
        std::this_thread::sleep_until(next);
        auto now = Clock::now();
        if (now - next > period * 10) next = now;  // fell behind (suspended); don't burst
        if (g_sampling) prof_for_each_thread(sample_thread, nullptr);
        timespec ts;
        clock_gettime(CLOCK_THREAD_CPUTIME_ID, &ts);
        g_sampler_cpu_ns = (u64)ts.tv_sec * 1000000000ull + ts.tv_nsec;
        if (g_dump_requested.exchange(false) || now - last_dump > std::chrono::seconds(10)) {
            profile_dump();
            last_dump = now;
        }
    }
}

void on_sigusr1(int) { g_dump_requested = true; }

// ---- output ------------------------------------------------------------------

std::string frame_name(u64 code) {
    u64 kind = code & kKindMask, v = code & ~kKindMask;
    if (kind == 0) return func_name(v);
    if (kind == kHle || kind == kNative) {
        const char* n = thunk_name((u32)v);
        return std::string(kind == kHle ? "[hle]" : "[native]") + (n ? n : "?");
    }
    if (kind == kThread) return v == 0xffffffffull ? "thread:?" : "thread:" + func_name(v);
    return code == kTruncated ? "[truncated]" : "[unknown]";
}

FILE* open_tmp(const std::string& name, std::string& tmp) {
    tmp = g_dir + "/." + name + ".tmp";
    return fopen(tmp.c_str(), "w");
}
void commit(FILE* f, const std::string& tmp, const std::string& name) {
    fclose(f);
    rename(tmp.c_str(), (g_dir + "/" + name).c_str());
}

bool g_funcs_written = false;

}  // namespace

bool profile_active() { return g_coverage || g_sampling; }

void profile_print_thread_stacks(FILE* out) {
    if (!g_sampling) {
        fprintf(out, "  (guest thread stacks need SOA_PROFILE)\n");
        return;
    }
    prof_for_each_thread(
        [](ProfThread& t, void* ctx) {
            FILE* out = (FILE*)ctx;
            int d = t.depth.load(std::memory_order_acquire);
            if (d <= 0 || d > kProfLevels) return;
            std::vector<u64> st;
            bool in_host = t.lv[d - 1].svc.load(std::memory_order_acquire) != 0;
            if (in_host) finish_stack(t, d, st);
            else finish_stack(t, d - 1, st);  // running guest code: only the levels below are known
            fprintf(out, "  guest thread %d%s:\n", t.id, in_host ? "" : " (running guest code; innermost level not shown)");
            for (u64 code : st) {
                std::string name = frame_name(code);
                size_t at = name.find("_Z");  // after a "[native]" / "thread:" prefix
                int status = 1;
                char* dm = at == std::string::npos ? nullptr : abi::__cxa_demangle(name.c_str() + at, nullptr, nullptr, &status);
                if (dm && status == 0) name = name.substr(0, at) + dm;
                free(dm);
                fprintf(out, "    %s\n", name.c_str());
            }
        },
        out);
    fflush(out);
}

void profile_dump() {
    if (!profile_active()) return;
    std::lock_guard lk(g_dump_mutex);
    std::string tmp;
    double secs = std::chrono::duration<double>(Clock::now() - g_t0).count();
    if (!g_funcs_written) {
        if (FILE* f = open_tmp("functions.tsv", tmp)) {
            fprintf(f, "# offset\tsize\tsources\tname   (sources: E=export B=BL target R=reloc H=eh_frame A=adrp+add)\n");
            for (size_t i = 0; i < g_funcs.size(); i++) {
                const Func& fn = g_funcs[i];
                char src[8], *p = src;
                if (fn.sources & kSrcExport) *p++ = 'E';
                if (fn.sources & kSrcBl) *p++ = 'B';
                if (fn.sources & kSrcReloc) *p++ = 'R';
                if (fn.sources & kSrcEh) *p++ = 'H';
                if (fn.sources & kSrcAdrp) *p++ = 'A';
                *p = 0;
                fprintf(f, "%lx\t%lu\t%s\t%s\n", fn.addr - g_lib->base, fn.size, src, func_name(i).c_str());
            }
            commit(f, tmp, "functions.tsv");
            g_funcs_written = true;
        }
    }
    if (g_coverage) {
        if (FILE* f = open_tmp("coverage.tsv", tmp)) {
            fprintf(f, "# offset\tfirst_hit_s\tname   (%d of %d armed entries executed, %.1f s)\n", g_cov_hits.load(), g_cov_patched, secs);
            for (size_t i = 0; i < g_funcs.size(); i++)
                if (g_state[i].load(std::memory_order_relaxed) == 2) fprintf(f, "%lx\t%.2f\t%s\n", g_funcs[i].addr - g_lib->base, g_first_hit[i], func_name(i).c_str());
            commit(f, tmp, "coverage.tsv");
        }
    }
    if (g_host_sampling)
        if (FILE* f = open_tmp("host.tsv", tmp)) {
            write_host_samples(f);
            commit(f, tmp, "host.tsv");
        }
    if (FILE* f = open_tmp("calls.tsv", tmp)) {
        fprintf(f, "# kind\tcalls\toffset\tname   (host functions called from guest code)\n");
        for (u32 i = 1; i < thunk_count(); i++) {
            u64 n = g_thunk_calls[i].load(std::memory_order_relaxed);
            if (!n) continue;
            u64 a = thunk_hook_addr(i);
            bool native = a >= g_text_lo && a < g_text_hi;
            fprintf(f, "%s\t%lu\t%lx\t%s\n", native ? "native" : "hle", n, native ? a - g_lib->base : 0, thunk_name(i) ? thunk_name(i) : "?");
        }
        commit(f, tmp, "calls.tsv");
    }
    if (g_sampling) {
        std::vector<std::pair<std::vector<u64>, u64>> snap;
        {
            std::lock_guard sl(g_stacks_mutex);
            snap.assign(g_stacks.begin(), g_stacks.end());
        }
        if (FILE* f = open_tmp("stacks.folded", tmp)) {
            std::unordered_map<u64, std::string> names;
            for (auto& [st, n] : snap) {
                std::string line;
                for (auto it = st.rbegin(); it != st.rend(); ++it) {
                    auto nit = names.find(*it);
                    if (nit == names.end()) nit = names.emplace(*it, frame_name(*it)).first;
                    if (!line.empty()) line += ';';
                    line += nit->second;
                }
                fprintf(f, "%s %lu\n", line.c_str(), n);
            }
            commit(f, tmp, "stacks.folded");
        }
    }
    if (FILE* f = open_tmp("meta.txt", tmp)) {
        fprintf(f, "seconds %.1f\ncoverage %d\nsampling %d\nhz %d\nfunctions %zu\narmed %d\nexecuted %d\nsamples %lu\nsamples_guest %lu\nsamples_host %lu\nsampler_cpu_s %.2f\n",
                secs, g_coverage, g_sampling, g_hz, g_funcs.size(), g_cov_patched, g_cov_hits.load(), g_samples.load(), g_samples_guest.load(),
                g_samples_host.load(), g_sampler_cpu_ns.load() / 1e9);
        commit(f, tmp, "meta.txt");
    }
}

void profile_init(LoadedLib& lib) {
    const char* cov = getenv("SOA_COVERAGE");
    const char* prof = getenv("SOA_PROFILE");
    if ((!cov || !*cov) && (!prof || !*prof)) return;
    if (cov && *cov && prof && *prof && strcmp(cov, prof) != 0) LOGW("profile", "SOA_COVERAGE and SOA_PROFILE differ; writing everything to %s", prof);
    g_dir = prof && *prof ? prof : cov;
    mkdir(g_dir.c_str(), 0755);
    g_lib = &lib;
    g_t0 = Clock::now();
    if (const char* hz = getenv("SOA_PROFILE_HZ")) g_hz = std::clamp(atoi(hz), 10, 10000);
    if (!build_function_table(lib)) {
        LOGE("profile", "couldn't read %s; profiling disabled", lib.path.c_str());
        return;
    }
    size_t exports = 0;
    for (auto& f : g_funcs) exports += f.name != nullptr;
    LOGI("profile", "function table: %zu entries (%zu exported, %zu local)", g_funcs.size(), exports, g_funcs.size() - exports);

    g_thunk_calls = new std::atomic<u64>[0x10000]();  // kMaxThunks
    g_prof_sample = on_sample;
    g_frames.reset(new FrameInfo[g_funcs.size()]);
    g_wait_thunk = (u32)(thunk_trap_insn(make_thunk("native_wait", [](Cpu&) {})) >> 5 & 0xffff);
    g_prof_enabled = true;
    g_coverage = cov && *cov;
    g_sampling = prof && *prof;
    if (g_coverage) install_coverage();
    if (g_sampling) init_host_sampling();
    signal(SIGUSR1, on_sigusr1);
    std::thread(sampler_main).detach();
    LOGI("profile", "writing to %s (coverage %s, sampling %s at %d Hz)", g_dir.c_str(), g_coverage ? "on" : "off", g_sampling ? "on" : "off", g_hz);
}

}  // namespace soa
