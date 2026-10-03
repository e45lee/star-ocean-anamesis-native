// Test helper: stubbing guest callees for differential tests (see guest_stub.h).
#include "native/common/guest_stub.h"

#include <sys/mman.h>

#include <algorithm>
#include <array>
#include <cinttypes>
#include <cstring>
#include <utility>
#include <mutex>
#include <unordered_map>

#include "core/loader.h"
#include "core/log.h"
#include "native/common/guest_std.h"

namespace soa::native {
namespace {

struct Stub {
    std::string name;
    u64 original = 0;  // trampoline to the original code (0 for fake functions)
    int ni = 4, nf = 0;
    bool passthrough = false;  // sessions without a behaviour for it run the original
    bool isolated = false;     // only sessions whose `only` names it answer it (stub_isolated)
};
std::mutex g_mutex;
std::unordered_map<u64, Stub> g_stubs;  // hooked address / fake-function address -> stub
thread_local StubSession* t_session = nullptr;

Stub lookup(u64 addr) {
    std::lock_guard lk(g_mutex);
    auto it = g_stubs.find(addr);
    if (it == g_stubs.end()) fatal("guest_stub: unknown stub at %#" PRIx64, addr);
    return it->second;
}

void run_session(StubSession* s, const Stub& st, Cpu& c) {
    s->record(st.name.c_str(), c);
    auto b = s->behave.find(st.name);
    if (b != s->behave.end()) {
        b->second(c);
    } else {
        c.set_x(0, 0);
        c.set_s(0, 0);
    }
}

void stub_dispatch(u64 addr, Cpu& c) {
    const Stub st = lookup(addr);
    if (StubSession* s = t_session; s && (s->only.empty() ? !st.isolated : s->only.count(st.name) != 0)) {
        if (!st.passthrough || s->behave.count(st.name)) {
            run_session(s, st, c);
            return;
        }
    }
    if (!st.original) {  // fake function outside a session
        c.set_x(0, 0);
        return;
    }
    // Guest code called it (through the hook's SVC: the CPU is at the entry's second instruction):
    // continue in the original on this JIT level, as if it weren't hooked. (A nested guest call per
    // unanswered call made a recursive stubbed function, e.g. CCocosNode::SearchByName once a live
    // check had stubbed it, take a JIT level, and its code cache, per recursion: the processor
    // slots ran out.) Native code calling it directly (models_gcall) gets the nested call below.
    if (c.pc() == addr + 4) {
        c.xregs()[32] = st.original;  // (the PC: the SVC's block ends by dispatching on it)
        return;
    }
    GuestArgs a;
    for (int i = 0; i < 8; i++) a.i(c.x(i));
    // The caller's stack arguments, for a stub declared with more than 8 integer arguments
    // (n_int; e.g. PostMessage's priority): at its SP, passed on as the call's own stack
    // arguments (guest_call runs the original below that SP). Not read otherwise: the SP can be
    // at the very top of a stack mapping.
    for (int i = 8; i < st.ni && i < 16; i++) a.i(*(const u64*)(c.sp() + 8 * (i - 8)));
    for (int i = 0; i < 8; i++) a.vecs.push_back(c.v(i));
    a.x8 = c.x(8);
    GuestResult r = guest_call(st.original, a);
    // every result register (x0:x1 pairs, HFA results in v0-v3), as the unstubbed function
    c.set_x(0, r.x0);
    c.set_x(1, r.x1);
    c.set_v(0, r.v0);
    c.set_v(1, r.v1);
    c.set_v(2, r.v2);
    c.set_v(3, r.v3);
}

// The host function behind each stub. Native code may call a hooked guest function's host
// function directly (guest_call's direct path sets the PC, but models_gcall and the containers'
// direct calls don't), so the stubbed address can't be recovered from c.pc() there: that was the
// "guest_stub: unknown stub" crash of later tests once an earlier one had stubbed a function
// natively called code uses (the allocator, gDoAssert). Each stub gets its own entry function,
// which knows its address; c.pc() is only the fallback once the slots run out.
constexpr size_t kSlots = 4096;
u64 g_slot_addr[kSlots];
size_t g_slots_used = 0;  // under g_mutex
void stub_entry(Cpu& c) { stub_dispatch(c.pc() - 4, c); }
template <size_t I>
void stub_entry_slot(Cpu& c) {
    stub_dispatch(g_slot_addr[I], c);
}
template <size_t... I>
constexpr std::array<HostFn, sizeof...(I)> slot_fns(std::index_sequence<I...>) {
    return {&stub_entry_slot<I>...};
}
const std::array<HostFn, kSlots> kSlotFns = slot_fns(std::make_index_sequence<kSlots>());
HostFn entry_for(u64 addr) {
    std::lock_guard lk(g_mutex);
    if (g_slots_used == kSlots) return stub_entry;
    g_slot_addr[g_slots_used] = addr;
    return kSlotFns[g_slots_used++];
}

// A trampoline running the first two instructions of addr (relocated, including PC-relative
// branches, CBZ/CBNZ/TBZ/TBNZ, B.cond and ADRP) and then jumping to addr + 8.
u64 make_trampoline(u64 addr) {
    auto* t = (u32*)map_guest_code(4096);
    size_t k = 0;
    auto jump_abs = [&](u64 target) {  // LDR X16, #8; BR X16; .quad target
        t[k++] = 0x58000050;
        t[k++] = 0xd61f0200;
        memcpy(&t[k], &target, 8);
        k += 2;
    };
    auto sext = [](u64 v, int bits) { return (s64)(v << (64 - bits)) >> (64 - bits); };
    for (int i = 0; i < 2; i++) {
        u64 pc = addr + 4 * i;
        u32 w = ((const u32*)addr)[i];
        if ((w & 0x7c000000) == 0x14000000) {  // B / BL
            u64 target = pc + (sext(w & 0x3ffffff, 26) << 2);
            if (w & 0x80000000) {  // BL: LDR X16, #12; BLR X16; B #12; .quad (the literal is 3 words on)
                t[k++] = 0x58000070;
                t[k++] = 0xd63f0200;
                t[k++] = 0x14000003;
                memcpy(&t[k], &target, 8);
                k += 2;
            } else {
                jump_abs(target);
            }
        } else if ((w & 0x7e000000) == 0x34000000 || (w & 0xff000010) == 0x54000000 || (w & 0x7e000000) == 0x36000000) {
            // CBZ/CBNZ/B.cond (imm19 at bit 5) or TBZ/TBNZ (imm14 at bit 5): branch to +8 (the
            // absolute jump), else skip it.
            u64 target;
            u32 nw;
            if ((w & 0x7e000000) == 0x36000000) {
                target = pc + (sext((w >> 5) & 0x3fff, 14) << 2);
                nw = (w & ~(0x3fffu << 5)) | (2u << 5);
            } else {
                target = pc + (sext((w >> 5) & 0x7ffff, 19) << 2);
                nw = (w & ~(0x7ffffu << 5)) | (2u << 5);
            }
            t[k++] = nw;          // cond -> +8
            t[k++] = 0x14000005;  // B over the 4-word jump
            jump_abs(target);
        } else if ((w & 0x9f000000) == 0x90000000) {  // ADRP
            u64 imm = ((w >> 29) & 3) | (((w >> 5) & 0x7ffff) << 2);
            u64 value = (pc & ~0xfffull) + (sext(imm, 21) << 12);
            u32 rd = w & 31;
            t[k++] = 0x58000040 | rd;  // LDR Xd, #8
            t[k++] = 0x14000003;       // B #12
            memcpy(&t[k], &value, 8);
            k += 2;
        } else if ((w & 0x9f000000) == 0x10000000 || (w & 0x3b000000) == 0x18000000) {
            return 0;  // ADR / LDR literal: not needed so far
        } else {
            t[k++] = w;
        }
    }
    jump_abs(addr + 8);
    return (u64)t;
}

}  // namespace

StubSession::StubSession() {
    if (t_session) fatal("guest_stub: nested StubSession");
    t_session = this;
}
StubSession::~StubSession() { t_session = nullptr; }
StubSession* StubSession::current() { return t_session; }

void StubSession::record(const char* name, Cpu& c) {
    int ni = 4, nf = 0;
    {
        std::lock_guard lk(g_mutex);
        auto it = g_stubs.find(c.pc() - 4);
        if (it != g_stubs.end()) ni = it->second.ni, nf = it->second.nf;
    }
    auto ar = arity.find(name);
    if (ar != arity.end()) ni = ar->second.first, nf = ar->second.second;
    std::string e = std::string(name) + "(";
    for (int i = 0; i < ni; i++) {
        if (i) e += ",";
        e += fmt_ptr ? fmt_ptr(c.x(i)) : std::to_string(c.x(i));
    }
    for (int i = 0; i < nf; i++) {
        char b[32];
        u32 bits = (u32)c.v(i).lo;
        snprintf(b, sizeof b, ";%g/%08x", c.s(i), bits);
        e += b;
    }
    e += ")";
    static bool trace = getenv("SOA_STUB_TRACE") != nullptr;
    if (trace) fprintf(stderr, "stub: %s\n", e.c_str());
    log.push_back(e);
}

bool stub(const char* mangled, const char* name, int n_int, int n_float) { return stub_at(guest::sym(mangled), name, n_int, n_float); }

bool stub_at(u64 addr, const char* name, int n_int, int n_float) {
    // The patch is 8 bytes: a 4-byte function (a lone RET or tail branch) would take the next
    // function's first instruction with it.
    {
        const LoadedLib& lib = *main_lib();
        auto it = std::lower_bound(lib.sorted_syms.begin(), lib.sorted_syms.end(), addr, [](const LoadedLib::Sym& s, u64 a) { return s.addr < a; });
        u64 size = 0;
        for (; it != lib.sorted_syms.end() && it->addr == addr; ++it) size = std::max(size, it->size);
        if (size && size < 8) {
            LOGI("stub", "%s is only %" PRIu64 " bytes; not stubbed", name, size);
            return false;
        }
    }
    bool already = false;
    {
        std::lock_guard lk(g_mutex);
        auto it = g_stubs.find(addr);
        if (it != g_stubs.end()) {
            // Stubbed again (by another test): the latest caller names it, since sessions key their
            // behaviours and `only` sets by name, and it may rely on sessions without `only`.
            it->second.name = name;
            it->second.ni = n_int, it->second.nf = n_float;
            if (it->second.isolated) {  // an ordinary stub() now: behave as if it came first
                it->second.isolated = false;
                it->second.name = name;
            }
            already = true;
        }
    }
    if (already) {
        // Stubbed earlier, maybe from another thread: this thread's JIT may still hold the
        // unpatched code (e.g. the main thread, for an in-frame test stubbing it second).
        invalidate_guest_code_this_thread(addr, 8);
        return true;
    }
    u64 orig = make_trampoline(addr);
    if (!orig) {
        LOGW("stub", "%s: prologue is PC-relative; can't stub", name);
        return false;
    }
    {
        std::lock_guard lk(g_mutex);
        g_stubs[addr] = Stub{name, orig, n_int, n_float};
    }
    hook_guest_function(addr, strdup(name), entry_for(addr));
    invalidate_guest_code_this_thread(addr, 8);
    return true;
}

void stub_set_exclusive(u64 addr, bool on) {  // (battle-calc's name for an isolated stub)
    std::lock_guard lk(g_mutex);
    auto it = g_stubs.find(addr);
    if (it != g_stubs.end()) it->second.isolated = on;
}

std::string stub_name(u64 addr) {
    std::lock_guard lk(g_mutex);
    auto it = g_stubs.find(addr);
    return it == g_stubs.end() ? std::string() : it->second.name;
}

u64 stub_original(u64 addr) {
    std::lock_guard lk(g_mutex);
    auto it = g_stubs.find(addr);
    return it == g_stubs.end() ? 0 : it->second.original;
}

bool stub_passthrough(const char* mangled, const char* name, int n_int) {
    if (!stub(mangled, name, n_int)) return false;
    std::lock_guard lk(g_mutex);
    g_stubs[guest::sym(mangled)].passthrough = true;
    return true;
}

bool stub_isolated_at(u64 addr, const char* name, int n_int, int n_float) {
    {
        // Already hooked by another test: take it over under our name and arity (sessions key
        // `only` and behaviours by name, so keeping the other test's name would leave this
        // test's session answering nothing and the real callee running), isolated.
        std::lock_guard lk(g_mutex);
        auto it = g_stubs.find(addr);
        if (it != g_stubs.end()) {
            it->second.name = name;
            it->second.ni = n_int, it->second.nf = n_float;
            it->second.isolated = true;
            return true;
        }
    }
    if (!stub_at(addr, name, n_int, n_float)) return false;
    std::lock_guard lk(g_mutex);
    g_stubs[addr].isolated = true;
    return true;
}
bool stub_isolated(const char* mangled, const char* name, int n_int, int n_float) {
    return stub_isolated_at(guest::sym(mangled), name, n_int, n_float);
}

u64 fake_function(const char* name, int n_int, int n_float) {
    u64 a = make_thunk(strdup(name), stub_entry);
    std::lock_guard lk(g_mutex);
    g_stubs[a] = Stub{name, 0, n_int, n_float};
    return a;
}

}  // namespace soa::native
