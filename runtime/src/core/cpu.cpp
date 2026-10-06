#include <soa/env.h>
#include "core/cpu.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <execinfo.h>
#include <signal.h>
#include <ucontext.h>
#endif
#include <malloc.h>
#include <pthread.h>
#include <unistd.h>

#include <algorithm>
#include <atomic>
#include <chrono>
#include <cinttypes>
#include <mutex>
#include <set>
#include <unordered_map>

#include "core/crash.h"
#include "core/gdbstub.h"
#include "core/host_mem.h"
#include "core/log.h"
#include "dynarmic/interface/A64/a64.h"
#include "dynarmic/interface/A64/config.h"
#include "dynarmic/interface/exclusive_monitor.h"

// For a host gdb attached to the process (control/gdbinit-soa: soa-native-break): the thunk table,
// kMaxThunks entries of {HostFn fn; const char* name; u64 hook; const char* host_name} (32 bytes),
// filled in order from entry 1 (0 is the return to the host; a later entry with fn 0 ends it). Set
// by cpu_global_init.
extern "C" {
void* soa_gdb_thunks = nullptr;
}

namespace soa {

namespace {

constexpr u32 kMaxThunks = 0x10000;
// Guest CPU contexts alive at once: one per host thread per guest<->host nesting depth (ThreadState
// pools keep a thread's deepest level until it exits). 256 ran out in the 3rd-4th battle of
// sphere211_session.sh (agent a5-sphere) when the guest saw all 32 host CPUs and started 62
// engine workers, each reaching 4-6 levels (PLAN-next D7). With --guest-cpus 8 (the default) the
// same run peaks at about 110; the limit stays at 1024 for --guest-cpus host on large machines
// (the monitor's per-processor state is a few bytes).
constexpr size_t kMaxProcessors = 1024;
constexpr u64 kCntFreq = 19200000;  // typical Android CNTFRQ
// Mapped memory above the guest stack's top: a read of the caller's frame at a top-level sp (a
// host function looking at "stack arguments" that weren't passed, core_bench_test's h_record)
// stays in the mapping. Linux's mmap usually had a neighbour there; Windows' 64 KiB-aligned
// VirtualAlloc regions don't.
constexpr size_t kStackHeadroom = 0x1000;

struct ThunkEntry {
    HostFn fn = nullptr;
    const char* name = nullptr;
    u64 hook = 0;                    // guest function entry patched to trap here (hook_guest_function), or 0
    const char* host_name = nullptr;  // hook_guest_function's host_name
};
// control/gdbinit-soa's soa-native-break reads this table from a host gdb (no debug info needed).
static_assert(sizeof(ThunkEntry) == 32 && offsetof(ThunkEntry, name) == 8 && offsetof(ThunkEntry, hook) == 16 &&
              offsetof(ThunkEntry, host_name) == 24);

ThunkEntry* g_thunks = nullptr;
u32* g_thunk_code = nullptr;  // 2 instructions per thunk
std::atomic<u32> g_thunk_count{1};  // index 0 = return-to-host
std::mutex g_thunk_mutex;
std::unordered_map<u64, u32> g_hooked;  // guest addr -> thunk index for hooks

Dynarmic::ExclusiveMonitor* g_monitor = nullptr;
std::mutex g_proc_mutex;
std::vector<bool> g_proc_used;
std::set<Cpu*> g_cpus;  // every live Cpu (invalidate_guest_code), under g_proc_mutex
size_t g_proc_peak = 0;  // highest processor id + 1 ever in use, under g_proc_mutex

size_t alloc_processor_id() {
    std::lock_guard lk(g_proc_mutex);
    for (size_t i = 0; i < g_proc_used.size(); i++) {
        if (!g_proc_used[i]) {
            g_proc_used[i] = true;
            if (i + 1 > g_proc_peak) {
                g_proc_peak = i + 1;
                if (g_proc_peak % 128 == 0) LOGI("cpu", "%zu guest CPU contexts in use (limit %zu)", g_proc_peak, kMaxProcessors);
            }
            return i;
        }
    }
    // Every host thread holds one context per guest_call nesting level it has reached, until it
    // exits. Running out means a thread nests without bound (e.g. a hook or stub that calls
    // guest code which calls the hook again) or thousands of live guest threads.
    fatal("out of guest CPU contexts (%zu in use, kMaxProcessors = %zu in core/cpu.cpp): each host thread holds one per "
          "guest_call nesting level it reached; run soa with --memstats to see which threads hold them (log "
          "I/memstats), and look for unbounded guest<->host recursion before raising the limit",
          g_cpus.size(), kMaxProcessors);
}

void free_processor_id(size_t id) {
    std::lock_guard lk(g_proc_mutex);
    g_proc_used[id] = false;
}

inline u32 enc_svc(u32 imm) { return 0xd4000001u | (imm << 5); }
constexpr u32 kRet = 0xd65f03c0u;

std::chrono::steady_clock::time_point g_start = std::chrono::steady_clock::now();

// Profiler thread registry (only populated when g_prof_enabled).
std::mutex g_prof_mutex;
std::set<ProfThread*> g_prof_threads;
int g_prof_next_id = 0;
constexpr auto kSampleHalt = Dynarmic::HaltReason::UserDefined2;

}  // namespace

bool g_prof_enabled = false;
std::atomic<u64>* g_thunk_calls = nullptr;
void (*g_prof_sample)(Cpu& c, ProfThread& t) = nullptr;

// ---------------------------------------------------------------------------

struct CpuCallbacks final : Dynarmic::A64::UserCallbacks {
    Cpu* cpu = nullptr;
    u64 tpidr_el0 = 0;
    u64 tpidrro_el0 = 0;

    // AArch64 Top Byte Ignore. Linux enables TBI0 for user space: bits 56-63 of a DATA address
    // are ignored (instruction fetches aren't affected). Guest memory is identity-mapped, so a
    // data access goes to the address with its top byte cleared. dynarmic's fastmem uses the
    // address as it is: a tagged one is non-canonical on x86-64 (#GP) or unmapped; its fault
    // handler (backend/exception_handler_posix.cpp, keyed on the faulting host RIP, not the
    // address) then calls these callbacks, and recompile_on_fastmem_failure keeps that
    // instruction on the callbacks. So the mask costs nothing on the fastmem path. 3.7.0
    // Aska::Yayoi::Socket::Poll reads [fdset + 0x1ffffffffffffff8] when another thread closed the
    // socket (fd = -1): fdset - 8 on a phone, a crash here before (emulator/README.md "Error
    // replies and the tagged-address crash"; test cpu/tbi-tagged-data-addresses).
    static constexpr u64 kTbiMask = 0x00ffffffffffffffull;
    static u64 tbi(u64 a) { return a & kTbiMask; }

    template <typename T>
    static T rd(u64 a) {
        T v;
        std::memcpy(&v, (const void*)tbi(a), sizeof(T));
        return v;
    }
    template <typename T>
    static void wr(u64 a, T v) {
        std::memcpy((void*)tbi(a), &v, sizeof(T));
    }
    template <typename T>
    static T fetch(u64 a) {  // instruction fetch: no TBI
        T v;
        std::memcpy(&v, (const void*)a, sizeof(T));
        return v;
    }

    std::optional<u32> MemoryReadCode(u64 a) override { return fetch<u32>(a); }
    u8 MemoryRead8(u64 a) override { return rd<u8>(a); }
    u16 MemoryRead16(u64 a) override { return rd<u16>(a); }
    u32 MemoryRead32(u64 a) override { return rd<u32>(a); }
    u64 MemoryRead64(u64 a) override { return rd<u64>(a); }
    Dynarmic::A64::Vector MemoryRead128(u64 a) override { return {rd<u64>(a), rd<u64>(a + 8)}; }
    void MemoryWrite8(u64 a, u8 v) override { wr(a, v); }
    void MemoryWrite16(u64 a, u16 v) override { wr(a, v); }
    void MemoryWrite32(u64 a, u32 v) override { wr(a, v); }
    void MemoryWrite64(u64 a, u64 v) override { wr(a, v); }
    void MemoryWrite128(u64 a, Dynarmic::A64::Vector v) override {
        wr(a, v[0]);
        wr(a + 8, v[1]);
    }

    template <typename T>
    static bool cas(u64 a, T v, T expected) {
        return __atomic_compare_exchange_n((T*)tbi(a), &expected, v, false, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST);
    }
    bool MemoryWriteExclusive8(u64 a, u8 v, u8 e) override { return cas(a, v, e); }
    bool MemoryWriteExclusive16(u64 a, u16 v, u16 e) override { return cas(a, v, e); }
    bool MemoryWriteExclusive32(u64 a, u32 v, u32 e) override { return cas(a, v, e); }
    bool MemoryWriteExclusive64(u64 a, u64 v, u64 e) override { return cas(a, v, e); }
    bool MemoryWriteExclusive128(u64 a, Dynarmic::A64::Vector v, Dynarmic::A64::Vector e) override {
        unsigned __int128 nv = ((unsigned __int128)v[1] << 64) | v[0];
        unsigned __int128 ev = ((unsigned __int128)e[1] << 64) | e[0];
        return __sync_bool_compare_and_swap((unsigned __int128*)tbi(a), ev, nv);
    }

    void InterpreterFallback(u64 pc, size_t n) override {
        LOGE("cpu", "unimplemented instruction %08x at %s", fetch<u32>(pc), describe_guest_addr(pc).c_str());
        dump_guest_state(*cpu);
        if (g_gdb_enabled) gdb_fault(cpu, kGdbSigIll);
        fatal("interpreter fallback");
    }

    void CallSVC(u32 swi) override;

    void ExceptionRaised(u64 pc, Dynarmic::A64::Exception e) override {
        using E = Dynarmic::A64::Exception;
        switch (e) {
        case E::Yield:
        case E::WaitForEvent:
        case E::SendEvent:
        case E::SendEventLocal:
        case E::WaitForInterrupt:
            cpu->set_pc(pc + 4);
            return;
        case E::Breakpoint:
            // A breakpoint the GDB stub inserted (--gdb): back to the BRK (the IR advanced the PC
            // past it), and the stub has halted this JIT, so it parks at the end of this block.
            if (g_gdb_enabled && gdb_breakpoint_hit(*cpu, pc)) {
                cpu->set_pc(pc);
                return;
            }
            LOGE("cpu", "guest BRK at %s", describe_guest_addr(pc).c_str());
            break;
        default:
            LOGE("cpu", "guest exception %d at %s (insn %08x)", (int)e, describe_guest_addr(pc).c_str(), fetch<u32>(pc));
            break;
        }
        dump_guest_state(*cpu);
        if (g_gdb_enabled) gdb_fault(cpu, e == E::Breakpoint ? kGdbSigTrap : kGdbSigIll);
        fatal("guest exception");
    }

    void DataCacheOperationRaised(Dynarmic::A64::DataCacheOperation op, u64 value) override {
        if (op == Dynarmic::A64::DataCacheOperation::ZeroByVA) std::memset((void*)(tbi(value) & ~63ull), 0, 64);
    }
    void InstructionCacheOperationRaised(Dynarmic::A64::InstructionCacheOperation, u64) override {}

    void AddTicks(u64) override {}
    u64 GetTicksRemaining() override { return ~0ull >> 1; }
    u64 GetCNTPCT() override {
        auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now() - g_start).count();
        return (u64)((unsigned __int128)ns * kCntFreq / 1000000000ull);
    }
};

// ---------------------------------------------------------------------------
// Per-thread state

class ThreadState;
static std::set<ThreadState*> g_thread_states;  // threads that hold guest CPU contexts, under g_proc_mutex

class ThreadState {
public:
    std::vector<std::unique_ptr<Cpu>> pool;
    // For cpu_memstats (read by other threads under g_proc_mutex): the host tid and pool.size().
    pid_t tid = 0;
    size_t levels = 0;
    u64 entry = 0;  // the guest function of the last outermost guest_call (thread entry for guest threads)
    size_t depth = 0;
    GuestThreadInfo info;
    std::vector<u64> tls_block;
    ProfThread prof;
    bool prof_registered = false;
    std::atomic<bool> in_jit{false};  // the innermost level is running JIT code (maintained only with g_gdb_enabled)

    ~ThreadState() { release(); }

    void prof_register() {
        std::lock_guard lk(g_prof_mutex);
        prof.id = g_prof_next_id++;
        prof.stack_lo = info.stack_lo;
        prof.stack_hi = info.stack_hi;
        prof.host_thread = (u64)pthread_self();
        g_prof_threads.insert(&prof);
        prof_registered = true;
    }

    void release() {
        if (prof_registered) {
            std::lock_guard lk(g_prof_mutex);
            g_prof_threads.erase(&prof);
            prof_registered = false;
        }
        if (!pool.empty()) {
            std::lock_guard lk(g_proc_mutex);
            g_thread_states.erase(this);
            levels = 0;
        }
        pool.clear();
        if (info.stack_lo) {
            hostmem::unmap((void*)(info.stack_lo - 0x1000), info.stack_hi - info.stack_lo + 0x1000 + kStackHeadroom);
            info.stack_lo = info.stack_hi = 0;
        }
    }

    Cpu& cpu_at(size_t d) {
        if (d < pool.size()) return *pool[d];
        while (pool.size() <= d) {
            auto c = std::unique_ptr<Cpu>(new Cpu());
            c->set_tpidr((u64)info.tls);
            pool.push_back(std::move(c));
        }
        std::lock_guard lk(g_proc_mutex);
        if (!tid) tid = gettid();
        g_thread_states.insert(this);
        levels = pool.size();
        return *pool[d];
    }
};

static thread_local ThreadState t_state;
static thread_local Cpu* t_current = nullptr;

GuestThreadInfo& guest_thread() { return t_state.info; }
Cpu* current_cpu() { return t_current; }

void guest_thread_init(size_t stack_size) {
    auto& ts = t_state;
    if (ts.info.stack_lo) return;
    // A thread nobody set up for crash reports (a library's thread calling into guest code).
    if (!crash_thread()) {
        char name[32];
        snprintf(name, sizeof name, "host-%d", (int)gettid());
        crash_thread_begin(name);
    }
    stack_size = (stack_size + 0xfff) & ~0xfffull;
    if (stack_size < 0x40000) stack_size = 0x40000;
    void* p = hostmem::map_rw(stack_size + 0x1000 + kStackHeadroom, true);
    if (!p) fatal("guest stack mapping failed");
    hostmem::protect_none(p, 0x1000);  // guard page
    ts.info.stack_lo = (u64)p + 0x1000;
    ts.info.stack_hi = ts.info.stack_lo + stack_size;
    // Bionic-style TLS: slot 5 (tp+0x28) is the stack guard. Keep some slots below tp too.
    ts.tls_block.assign(128, 0);
    ts.info.tls = ts.tls_block.data() + 16;
    ts.info.tls[0] = (u64)ts.info.tls;     // self
    ts.info.tls[1] = (u64)gettid();        // thread id
    ts.info.tls[5] = 0x5f3759df1badf00dull;  // stack guard
    for (auto& c : ts.pool) c->set_tpidr((u64)ts.info.tls);
}

void guest_thread_release() { t_state.release(); }

// ---------------------------------------------------------------------------

static void release_fast_dispatch_table(Dynarmic::A64::Jit& j);

Cpu::Cpu() : cb_(std::make_unique<CpuCallbacks>()) {
    cb_->cpu = this;
    processor_id_ = alloc_processor_id();
    Dynarmic::A64::UserConfig conf{};
    conf.callbacks = cb_.get();
    conf.processor_id = processor_id_;
    conf.global_monitor = g_monitor;
    conf.fastmem_pointer = 0;  // identity mapping
    conf.fastmem_address_space_bits = 64;
    conf.silently_mirror_fastmem = false;
    conf.recompile_on_fastmem_failure = true;
    conf.fastmem_exclusive_access = true;
    conf.recompile_on_exclusive_fastmem_failure = true;
    conf.page_table = nullptr;
    conf.tpidr_el0 = &cb_->tpidr_el0;
    conf.tpidrro_el0 = &cb_->tpidrro_el0;
    conf.cntfrq_el0 = kCntFreq;
    conf.dczid_el0 = 4;  // 64-byte DC ZVA
    conf.ctr_el0 = 0x8444c004;
    conf.hook_data_cache_operations = true;  // DC ZVA goes through DataCacheOperationRaised
    conf.enable_cycle_counting = false;
    conf.define_unpredictable_behaviour = true;
    conf.code_cache_size = 256 * 1024 * 1024;
    jit_ = std::make_unique<Dynarmic::A64::Jit>(conf);
    locate_jit_state();
    release_fast_dispatch_table(*jit_);
    std::lock_guard lk(g_proc_mutex);
    g_cpus.insert(this);
}

// dynarmic's A64EmitX64 (inside Jit::Impl) holds the fast-dispatch table: 0x100000 entries of
// {location descriptor, code pointer}, 16 MB, which its constructor fills with the empty entry
// {~0, nullptr}. So every JIT instance, i.e. every guest CPU context, costs 16 MB of resident
// memory before it runs anything, while a context uses a few hundred of the entries (PLAN-next
// D7: 16 of the ~22 MB per context; 230 contexts after four battles). This gives the table's
// pages back to the kernel; they come back zero-filled when touched. A zero entry {0, nullptr}
// only matches location descriptor 0 (guest PC 0 with FPCR 0), and a jump to guest address 0
// faults either way (on the table's null code pointer instead of reading the code at 0).
// The table is found as the one run of exactly 0x100000 empty entries in the Impl; anything
// else (a dynarmic change) leaves it alone.
static void release_fast_dispatch_table(Dynarmic::A64::Jit& j) {
    constexpr size_t kEntries = 0x100000;
    u64* impl;
    std::memcpy(&impl, (const void*)&j, sizeof impl);
    const size_t words = malloc_usable_size(impl) / 8;
    size_t run_at = 0, runs = 0, found = 0;
    for (size_t k = 0; k + 1 < words;) {
        if (impl[k] != ~0ull || impl[k + 1] != 0) {
            k++;
            continue;
        }
        size_t e = k;
        while (e + 1 < words && impl[e] == ~0ull && impl[e + 1] == 0) e += 2;
        if ((e - k) / 2 >= kEntries) {
            runs++;
            run_at = k;
            found = (e - k) / 2;
        }
        k = e;
    }
    static bool warned = false;
    if (runs != 1 || found != kEntries) {
        if (!warned) LOGW("cpu", "dynarmic's fast-dispatch table not found (%zu runs, %zu entries): each JIT keeps 16 MB resident", runs, found);
        warned = true;
        return;
    }
    const u64 lo = ((u64)(impl + run_at) + 0xfff) & ~0xfffull;
    const u64 hi = ((u64)(impl + run_at) + kEntries * 16) & ~0xfffull;
    if (hi > lo) hostmem::discard((void*)lo, hi - lo);
}

// Finds dynarmic's A64JitState inside the Jit's private Impl so the register accessors can be
// inline loads and stores (the Jit API goes through two out-of-line calls per register). The
// layout is A64JitState's: reg[31], sp, pc, cpsr_nzcv, ..., alignas(16) vec[64]. The Impl is
// found through Jit's only member (unique_ptr<Impl>) and searched for tagged register values;
// everything is then cross-checked against the API, so a dynarmic change fails loudly here.
void Cpu::locate_jit_state() {
    Dynarmic::A64::Jit& j = *jit_;
    static_assert(sizeof(Dynarmic::A64::Jit) == sizeof(void*), "Jit is expected to hold only its Impl pointer");
    u64* impl;
    std::memcpy(&impl, (const void*)&j, sizeof impl);
    size_t words = malloc_usable_size(impl) / 8;
    const u64 tag = 0x50a7c0de00000000ull;
    for (int i = 0; i < 31; i++) j.SetRegister(i, tag | (u64)i << 8 | 0x11);
    j.SetSP(tag | 0x1f11);
    j.SetPC(tag | 0x2011);
    for (int i = 0; i < 32; i++) j.SetVector(i, {tag | (u64)i << 8 | 0x22, tag | (u64)i << 8 | 0x33});
    auto match = [&](size_t k, size_t n, auto want) {
        if (k + n > words) return false;
        for (size_t i = 0; i < n; i++)
            if (impl[k + i] != want(i)) return false;
        return true;
    };
    for (size_t k = 0; k < words && !st_; k++)
        if (match(k, 33, [&](size_t i) { return tag | (u64)i << 8 | 0x11; })) st_ = impl + k;
    for (size_t k = 0; k < words && !vec_; k++)
        if (match(k, 64, [&](size_t i) { return tag | (u64)(i / 2) << 8 | (i & 1 ? 0x33 : 0x22); })) vec_ = impl + k;
    if (!st_ || !vec_) fatal("cpu: dynarmic's register file not found in Jit::Impl (dynarmic layout changed?)");
    nzcv_ = (u32*)(st_ + 33);
    halt_ = (volatile u32*)(vec_ + 64) + 2;  // after guest_MXCSR, asimd_MXCSR
    // Cross-check both directions and the flags word.
    bool ok = true;
    for (int i = 0; i < 31; i++) {
        st_[i] = 0x1234567800000000ull + i;
        ok &= j.GetRegister(i) == 0x1234567800000000ull + i;
    }
    st_[31] = 0xabc0;
    st_[32] = 0xdef0;
    ok &= j.GetSP() == 0xabc0 && j.GetPC() == 0xdef0;
    for (int i = 0; i < 32; i++) {
        vec_[2 * i] = 0x77 + i;
        vec_[2 * i + 1] = 0x99 + i;
        auto v = j.GetVector(i);
        ok &= v[0] == 0x77u + i && v[1] == 0x99u + i;
    }
    j.SetPstate(0xf0000000);
    ok &= *nzcv_ != 0;
    j.SetPstate(0);
    ok &= *nzcv_ == 0;
    ok &= *halt_ == 0;
    j.HaltExecution(Dynarmic::HaltReason::UserDefined3);
    ok &= *halt_ == (u32)Dynarmic::HaltReason::UserDefined3;
    j.ClearHalt(Dynarmic::HaltReason::UserDefined3);
    ok &= *halt_ == 0;
    if (!ok) fatal("cpu: direct register access disagrees with the dynarmic API");
    for (int i = 0; i < 33; i++) st_[i] = 0;
    for (int i = 0; i < 64; i++) vec_[i] = 0;
}

Cpu::~Cpu() {
    {
        std::lock_guard lk(g_proc_mutex);
        g_cpus.erase(this);
    }
    jit_.reset();
    free_processor_id(processor_id_);
}

void Cpu::halt() { jit_->HaltExecution(); }
void Cpu::set_tpidr(u64 v) { cb_->tpidr_el0 = v; }

void CpuCallbacks::CallSVC(u32 swi) {
    if (swi == 0) {  // return to host: same as cpu->halt(), without the two calls into dynarmic
        __atomic_fetch_or(cpu->halt_, (u32)Dynarmic::HaltReason::UserDefined1, __ATOMIC_SEQ_CST);
        return;
    }
    const ThunkEntry& t = g_thunks[swi];
    if (!t.fn) fatal("SVC #%u with no handler", swi);
    if (__builtin_expect(t_hook_filter != nullptr, 0) && t.hook && t_hook_filter(*cpu, t.hook)) return;
    if (__builtin_expect(g_gdb_enabled, 0)) {
        // For the GDB stub: this level is in host code (stopped from gdb's point of view) until the
        // handler returns to the JIT.
        bool was = t_state.in_jit.exchange(false, std::memory_order_acq_rel);
        if (g_prof_enabled) g_thunk_calls[swi].fetch_add(1, std::memory_order_relaxed);
        if (t.hook && gdb_native_breakpoints()) gdb_call_native(*cpu, t.hook, t.fn, true);  // (a breakpoint on a native)
        else t.fn(*cpu);
        t_state.in_jit.store(was, std::memory_order_release);
        if (t_state.info.exiting) cpu->halt();
        return;
    }
    if (g_prof_enabled) {
        // Count the call and publish "this thread is in host code" for the sampler.
        g_thunk_calls[swi].fetch_add(1, std::memory_order_relaxed);
        size_t d = t_state.depth;
        if (d > 0 && d <= (size_t)kProfLevels) {
            ProfLevel& l = t_state.prof.lv[d - 1];
            l.pc = cpu->pc();
            l.lr = cpu->x(30);
            l.fp = cpu->x(29);
            l.sp = cpu->sp();
            l.seq.store(l.seq.load(std::memory_order_relaxed) + 1, std::memory_order_relaxed);  // only this thread writes it
            l.svc.store(swi, std::memory_order_release);
            t.fn(*cpu);
            l.svc.store(0, std::memory_order_release);
        } else {
            t.fn(*cpu);
        }
    } else {
        t.fn(*cpu);
    }
    if (t_state.info.exiting) cpu->halt();
}

void prof_native_wait(bool waiting) {
    if (!g_prof_enabled) return;
    size_t d = t_state.depth;
    if (d == 0 || d > (size_t)kProfLevels) return;
    ProfLevel& l = t_state.prof.lv[d - 1];
    l.wait.store(waiting, std::memory_order_release);
    l.seq.store(l.seq.load(std::memory_order_relaxed) + 1, std::memory_order_release);
}

// ---------------------------------------------------------------------------

namespace {

bool g_direct_calls = [] {
    return env::env_bool("SOA_DIRECT_CALLS", true);
}();

// Thunk index when `fn` is the entry of a host function that can be called without the JIT: a
// thunk stub (make_thunk) or a hooked guest function (hook_guest_function). Other traps, e.g.
// coverage probes, don't qualify: their handlers redirect the guest PC.
inline u32 direct_thunk(u64 fn) {
    u32 w;
    std::memcpy(&w, (const void*)fn, 4);
    if ((w & 0xffe0001fu) != 0xd4000001u) return 0;
    u32 idx = (w >> 5) & 0xffff;
    if (idx == 0) return 0;
    const ThunkEntry& t = g_thunks[idx];
    if (!t.fn || (fn != (u64)&g_thunk_code[idx * 2] && fn != t.hook)) return 0;
    return idx;
}

// run_jit with the GDB stub on (--gdb; core/gdbstub.h): parks this thread while the debugger has
// the guest stopped (at entry, or when the JIT returns with kGdbHalt) and keeps ts.in_jit current.
void run_jit_debug(Cpu& c, ThreadState& ts) {
    using HR = Dynarmic::HaltReason;
    const bool was = ts.in_jit.load(std::memory_order_relaxed);
    if (gdb_stopped()) gdb_park(c);
    for (;;) {
        ts.in_jit.store(true, std::memory_order_release);
        HR hr = c.jit()->Run();
        ts.in_jit.store(false, std::memory_order_release);
        if (ts.info.exiting || Has(hr, HR::UserDefined1)) break;
        if (Has(hr, (HR)kGdbHalt)) {
            gdb_park(c);
            continue;
        }
        if (!Has(hr, HR::CacheInvalidation)) break;
    }
    ts.in_jit.store(was, std::memory_order_release);
}

// Runs the JIT at level d (1-based) until the guest function returns to host_return_addr.
void run_jit(Cpu& c, u64 fn, ThreadState& ts, int d) {
    // The JIT clears every halt reason when it returns, so these are normally no-ops; skip the
    // locked RMW then. (A halt requested while this level wasn't running, e.g. by a directly
    // called handler, is still pending.)
    if (c.halt_reason() & (u32)Dynarmic::HaltReason::UserDefined1) c.jit()->ClearHalt();
    if (!g_prof_enabled) {
        if (__builtin_expect(g_gdb_enabled, 0)) return run_jit_debug(c, ts);
        // A cache invalidation requested while this level runs (e.g. a test stubbing a guest
        // function from inside a hook) halts the JIT too: resume, like the profiling loop below.
        using HR = Dynarmic::HaltReason;
        for (;;) {
            HR hr = c.jit()->Run();
            if (ts.info.exiting || Has(hr, HR::UserDefined1) || !Has(hr, HR::CacheInvalidation)) break;
        }
        return;
    }
    // Profiling: the JIT also stops for samples (kSampleHalt) and after the coverage
    // hooks invalidate code (CacheInvalidation); both resume where they stopped.
    if (!ts.prof_registered) ts.prof_register();
    auto& pt = ts.prof;
    if (d == 1) pt.entry.store(fn, std::memory_order_relaxed);
    if (d <= kProfLevels) {
        pt.lv[d - 1].svc.store(0, std::memory_order_relaxed);
        pt.cpu[d - 1].store(&c, std::memory_order_release);
    }
    pt.depth.store(d, std::memory_order_release);
    if (c.halt_reason() & (u32)kSampleHalt) c.jit()->ClearHalt(kSampleHalt);
    using HR = Dynarmic::HaltReason;
    if (g_gdb_enabled && gdb_stopped()) gdb_park(c);
    for (;;) {
        if (g_gdb_enabled) ts.in_jit.store(true, std::memory_order_release);
        HR hr = c.jit()->Run();
        if (g_gdb_enabled) ts.in_jit.store(false, std::memory_order_release);
        if (ts.info.exiting || Has(hr, HR::UserDefined1)) break;
        if (Has(hr, (HR)kGdbHalt)) {
            gdb_park(c);
            continue;
        }
        if (!Has(hr, kSampleHalt) && !Has(hr, HR::CacheInvalidation)) break;
        if (Has(hr, kSampleHalt) && g_prof_sample) g_prof_sample(c, pt);
    }
    if (d <= kProfLevels) pt.cpu[d - 1].store(nullptr, std::memory_order_release);
    pt.depth.store(d - 1, std::memory_order_release);
}

// Calls thunk `idx` directly on level d's CPU, as the SVC at `fn` would (PC = fn + 4).
void run_direct(Cpu& c, u32 idx, u64 fn, ThreadState& ts, int d) {
    HostFn f = g_thunks[idx].fn;
    if (__builtin_expect(g_gdb_enabled, 0) && g_thunks[idx].hook && gdb_native_breakpoints()) {
        gdb_call_native(c, fn, f, false);  // (a breakpoint on a native: core/gdbstub.h)
        return;
    }
    if (!g_prof_enabled) {
        f(c);
        return;
    }
    // Same bookkeeping as run_jit + CallSVC: the level is "in host code" for the sampler.
    if (!ts.prof_registered) ts.prof_register();
    auto& pt = ts.prof;
    if (d == 1) pt.entry.store(fn, std::memory_order_relaxed);
    g_thunk_calls[idx].fetch_add(1, std::memory_order_relaxed);
    if (d > kProfLevels) {
        f(c);
        return;
    }
    ProfLevel& l = pt.lv[d - 1];
    l.pc = fn + 4;
    l.lr = c.x(30);
    l.fp = c.x(29);
    l.sp = c.sp();
    l.seq.store(l.seq.load(std::memory_order_relaxed) + 1, std::memory_order_relaxed);
    l.svc.store(idx, std::memory_order_release);
    pt.cpu[d - 1].store(nullptr, std::memory_order_release);  // nothing to halt at this level
    pt.depth.store(d, std::memory_order_release);
    f(c);
    l.svc.store(0, std::memory_order_release);
    pt.depth.store(d - 1, std::memory_order_release);
}

}  // namespace

void set_direct_host_calls(bool on) { g_direct_calls = on; }
bool direct_host_calls() { return g_direct_calls; }

GuestResult guest_call(u64 fn, const GuestArgs& args) {
    return guest_call_raw(fn, args.ints.data(), args.ints.size(), args.vecs.data(), args.vecs.size(), args.x8);
}

GuestResult guest_call_raw(u64 fn, const u64* ints, size_t ni, const V128* vecs, size_t nv, u64 x8) {
    auto& ts = t_state;
    if (!ts.info.stack_lo) guest_thread_init(1 << 20);
    const size_t depth = ts.depth;
    Cpu& c = ts.cpu_at(depth);
    u64 sp = depth > 0 ? ts.pool[depth - 1]->sp() - 512 : ts.info.stack_hi;
    size_t nstack_i = ni > 8 ? ni - 8 : 0;
    size_t nstack_v = nv > 8 ? nv - 8 : 0;
    sp -= (nstack_i + nstack_v) * 8;
    sp &= ~15ull;
    // Stack arguments: integer overflow args first then FP overflow args. Correct as long as a
    // call doesn't overflow both classes (we never do).
    u64* stk = (u64*)sp;
    for (size_t k = 0; k < nstack_i; k++) *stk++ = ints[8 + k];
    for (size_t k = 0; k < nstack_v; k++) *stk++ = vecs[8 + k].lo;

    u64* x = c.st_;
    for (size_t k = 0; k < 8 && k < ni; k++) x[k] = ints[k];
    for (size_t k = 0; k < 8 && k < nv; k++) c.set_v((int)k, vecs[k]);
    x[8] = x8;
    x[29] = 0;
    x[30] = host_return_addr();
    x[31] = sp;
    *c.nzcv_ = 0;  // SetPstate(0)

    if (depth == 0) ts.entry = fn;
    ts.depth = depth + 1;
    Cpu* saved = t_current;
    t_current = &c;
    const int d = (int)depth + 1;
    bool ran_jit = true;
    if (u32 idx = g_direct_calls ? direct_thunk(fn) : 0) {
        c.set_pc(fn + 4);
        run_direct(c, idx, fn, ts, d);
        // A handler that redirected the PC (none do today) continues in the JIT from there.
        ran_jit = !ts.info.exiting && c.pc() != fn + 4;
        if (ran_jit) run_jit(c, fn, ts, d);
    } else {
        // Enter through "BR x16" at host_return_addr() + 4: the SVC #0 that ended the previous
        // call on this level pushed that address on the JIT's return stack buffer, so Run()
        // finds its code there instead of looking the block up, and the BR goes through the
        // JIT's fast dispatch table. x16 (IP0) is scratch at a call boundary.
        x[16] = fn;
        c.set_pc(host_return_addr() + 4);
        run_jit(c, fn, ts, d);
    }
    t_current = saved;
    ts.depth = depth;

    if (ran_jit && !ts.info.exiting && c.pc() != host_return_addr() + 4 && c.pc() != host_return_addr()) {
        LOGW("cpu", "guest_call returned with unexpected pc %s", describe_guest_addr(c.pc()).c_str());
    }
    const u64* v = c.vec_;
    return {x[0], {v[0], v[1]}, x[1], {v[2], v[3]}, {v[4], v[5]}, {v[6], v[7]}};
}

GuestResult a2c_guest_call(u64 fn, const u64* x, const void* v, u64 body_sp) {
    u64 ints[8 + kA2cStackSlots];
    V128 vecs[8];
    std::memcpy(vecs, v, sizeof vecs);
    for (int k = 0; k < 8; k++) ints[k] = x[k];
    size_t slots = 8;
    Cpu* c = current_cpu();
    u64 saved = 0;
    bool moved = false;
    if (c) {
        saved = c->sp();
        // A body running on the guest stack: nested guest code stays below its frame.
        if (body_sp < saved && saved - body_sp < (8ull << 20)) {
            c->set_sp(body_sp & ~15ull);
            moved = true;
            slots = std::min<u64>(kA2cStackSlots, (saved - body_sp) / 8);
        }
    }
    for (size_t k = 0; k < slots; k++) std::memcpy(&ints[8 + k], (const void*)(body_sp + 8 * k), 8);
    GuestResult g = guest_call_raw(fn, ints, 8 + slots, vecs, 8, x[8]);
    if (moved) c->set_sp(saved);
    return g;
}

// ---------------------------------------------------------------------------
// Profiling support

void prof_for_each_thread(void (*fn)(ProfThread& t, void* ctx), void* ctx) {
    std::lock_guard lk(g_prof_mutex);
    for (ProfThread* t : g_prof_threads) fn(*t, ctx);
}

void prof_request_sample(Cpu* c) { c->jit()->HaltExecution(kSampleHalt); }

u32 thunk_trap_insn(u64 stub) { return enc_svc((u32)((stub - (u64)g_thunk_code) / 8)); }
u32 thunk_count() { return g_thunk_count.load(); }
const char* thunk_name(u32 idx) { return idx < kMaxThunks ? g_thunks[idx].name : nullptr; }
u64 thunk_hook_addr(u32 idx) {
    std::lock_guard lk(g_thunk_mutex);
    for (auto& [addr, i] : g_hooked)
        if (i == idx) return addr;
    return 0;
}

// ---------------------------------------------------------------------------

u64 host_return_addr() { return (u64)&g_thunk_code[0]; }

u64 make_thunk(const char* name, HostFn fn) {
    u32 idx = g_thunk_count.fetch_add(1);
    if (idx >= kMaxThunks) fatal("too many thunks");
    g_thunks[idx].fn = fn;
    g_thunks[idx].name = name;
    std::atomic_thread_fence(std::memory_order_release);  // entry before its code (direct_thunk)
    g_thunk_code[idx * 2] = enc_svc(idx);
    g_thunk_code[idx * 2 + 1] = kRet;
    return (u64)&g_thunk_code[idx * 2];
}

const char* thunk_name_at(u64 addr) {
    u64 base = (u64)g_thunk_code;
    if (addr >= base && addr < base + kMaxThunks * 8) return g_thunks[(addr - base) / 8].name;
    std::lock_guard lk(g_thunk_mutex);
    auto it = g_hooked.find(addr);
    if (it != g_hooked.end()) return g_thunks[it->second].name;
    return nullptr;
}

static bool pc_relative(u32 w) {
    return (w & 0x1f000000) == 0x10000000 ||  // ADR/ADRP
           (w & 0x7c000000) == 0x14000000 ||  // B/BL
           (w & 0xff000010) == 0x54000000 ||  // B.cond
           (w & 0x7e000000) == 0x34000000 ||  // CBZ/CBNZ
           (w & 0x7e000000) == 0x36000000 ||  // TBZ/TBNZ
           (w & 0x3b000000) == 0x18000000;    // LDR (literal)
}

static bool is_adrp(u32 w) { return (w & 0x9f000000) == 0x90000000; }

u64 make_original_trampoline(u64 addr) {
    const u32* p = (const u32*)addr;
    // ADRP is relocated (LDR Xd of the page it computes, from a literal); other PC-relative forms aren't.
    for (int i = 0; i < 2; i++)
        if (pc_relative(p[i]) && !is_adrp(p[i])) return 0;
    auto* t = (u32*)map_guest_code(4096);
    for (int i = 0; i < 2; i++) {
        t[i] = p[i];
        if (!is_adrp(p[i])) continue;
        const u32 w = p[i];
        const s64 imm = (s64)((u64)((((w >> 5) & 0x7ffff) << 2) | ((w >> 29) & 3)) << 43) >> 31;  // imm21 << 12, sign-extended
        const u64 page = ((addr + 4 * (u64)i) & ~u64{0xfff}) + (u64)imm;
        *(u64*)&t[6 + 2 * i] = page;                                            // the literal at byte 24 + 8 i
        t[i] = 0x58000000 | ((u32)((24 + 8 * i - 4 * i) / 4) << 5) | (w & 31);  // LDR Xd, literal
    }
    t[2] = 0x58000050;  // LDR X16, #8
    t[3] = 0xd61f0200;  // BR X16
    *(u64*)&t[4] = addr + 8;
    return (u64)t;
}

// Drops this thread's JIT translations of [addr, addr + size) (every idle nesting level), e.g.
// after patching guest code at run time (test stubs). Levels that are running (this is called
// from inside one of their callbacks) are left alone: invalidating a JIT that is stopped in a
// callback makes its Run() return early. They keep running the old code.
void invalidate_guest_code_this_thread(u64 addr, u64 size) {
    for (size_t i = t_state.depth; i < t_state.pool.size(); i++) t_state.pool[i]->jit()->InvalidateCacheRange(addr, size);
}

size_t guest_depth_this_thread() { return t_state.depth; }

std::vector<GuestThreadView> guest_threads() {
    std::vector<GuestThreadView> out;
    std::lock_guard lk(g_proc_mutex);
    for (ThreadState* t : g_thread_states) {
        if (t->pool.empty()) continue;
        size_t d = t->depth;
        Cpu* c = t->pool[d > 0 && d <= t->pool.size() ? d - 1 : 0].get();
        out.push_back({(int)t->tid, c, t->in_jit.load(std::memory_order_acquire), t->entry});
    }
    std::sort(out.begin(), out.end(), [](const GuestThreadView& a, const GuestThreadView& b) { return a.tid < b.tid; });
    return out;
}

void halt_all_guest_cpus(u32 reason) {
    std::lock_guard lk(g_proc_mutex);
    for (Cpu* c : g_cpus) c->jit()->HaltExecution((Dynarmic::HaltReason)reason);
}

CpuMemStats cpu_memstats() {
    CpuMemStats st;
    std::lock_guard lk(g_proc_mutex);
    st.contexts = g_cpus.size();
    st.peak_ids = g_proc_peak;
    st.limit = kMaxProcessors;
    for (ThreadState* t : g_thread_states) st.threads.push_back({(int)t->tid, t->levels, t->entry});
    std::sort(st.threads.begin(), st.threads.end());
    return st;
}

void invalidate_guest_code(u64 addr, u64 size) {
    std::lock_guard lk(g_proc_mutex);
    for (Cpu* c : g_cpus) c->jit()->InvalidateCacheRange(addr, size);
}

void* map_guest_code(size_t bytes) {
    void* p = hostmem::map_rw(bytes);
    if (!p) fatal("map_guest_code: mapping %zu bytes failed", bytes);
    invalidate_guest_code((u64)p, bytes);
    return p;
}

void unmap_guest_code(void* p, size_t bytes) {
    invalidate_guest_code((u64)p, bytes);
    hostmem::unmap(p, bytes);
}

thread_local bool (*t_hook_filter)(Cpu& c, u64 hook_addr) = nullptr;

HostFn hooked_host_fn(u64 addr) {
    // O(1) and lock-free: a hooked entry starts with "SVC #idx" and thunk idx records the hook.
    u32 w;
    std::memcpy(&w, (const void*)addr, 4);
    if ((w & 0xffe0001fu) != 0xd4000001u) return nullptr;
    const ThunkEntry& t = g_thunks[(w >> 5) & 0xffff];
    return t.hook == addr ? t.fn : nullptr;
}

void hook_guest_function(u64 addr, const char* name, HostFn fn, const char* host_name) {
    u64 stub = make_thunk(name, fn);
    u32 idx = (u32)((stub - (u64)g_thunk_code) / 8);
    g_thunks[idx].host_name = host_name;
    g_thunks[idx].hook = addr;
    std::atomic_thread_fence(std::memory_order_release);
    u32* p = (u32*)addr;
    p[0] = enc_svc(idx);
    p[1] = kRet;
    std::lock_guard lk(g_thunk_mutex);
    g_hooked[addr] = idx;
}

std::vector<HookedFunction> hooked_functions() {
    std::vector<HookedFunction> out;
    {
        std::lock_guard lk(g_thunk_mutex);
        for (auto& [addr, idx] : g_hooked) {
            const ThunkEntry& t = g_thunks[idx];
            if (hooked_host_fn(addr) == t.fn) out.push_back({addr, t.name, t.host_name, t.fn});
        }
    }
    std::sort(out.begin(), out.end(), [](const HookedFunction& a, const HookedFunction& b) { return a.guest_addr < b.guest_addr; });
    return out;
}

// ---------------------------------------------------------------------------

// The first lines of a fault's report when it is a stack overflow (core/crash.h): the host stack
// of a thread set up by crash_thread_begin, or the guest stack's guard page (guest_thread_init).
static void report_overflow(uintptr_t addr, uintptr_t sp) {
    if (const CrashThread* ct = crash_thread(); ct && crash_is_stack_overflow(*ct, addr, sp)) {
        crash_report_overflow(*ct, sp);
        return;
    }
    const auto& gi = t_state.info;
    if (gi.stack_lo && addr < gi.stack_lo && addr + 0x1000 >= gi.stack_lo) {
        const CrashThread* ct = crash_thread();
        fprintf(stderr, "\n*** guest stack overflow on thread %s (tid %d, guest stack %llu KiB) ***\n", ct && ct->name[0] ? ct->name : "?",
                (int)gettid(), (unsigned long long)((gi.stack_hi - gi.stack_lo) >> 10));
    }
}

#ifdef _WIN32
// The GDB protocol's signal for a Windows exception code.
static int gdb_signal_of(DWORD code) {
    switch (code) {
    case EXCEPTION_ILLEGAL_INSTRUCTION:
    case EXCEPTION_PRIV_INSTRUCTION: return kGdbSigIll;
    case EXCEPTION_BREAKPOINT:
    case EXCEPTION_SINGLE_STEP: return kGdbSigTrap;
    case EXCEPTION_INT_DIVIDE_BY_ZERO:
    case EXCEPTION_INT_OVERFLOW:
    case EXCEPTION_FLT_DIVIDE_BY_ZERO:
    case EXCEPTION_FLT_INVALID_OPERATION:
    case EXCEPTION_FLT_OVERFLOW:
    case EXCEPTION_FLT_UNDERFLOW:
    case EXCEPTION_FLT_INEXACT_RESULT:
    case EXCEPTION_FLT_DENORMAL_OPERAND:
    case EXCEPTION_FLT_STACK_CHECK: return kGdbSigFpe;
    case EXCEPTION_DATATYPE_MISALIGNMENT: return kGdbSigBus;
    default: return kGdbSigSegv;  // access violation, stack overflow, in-page error, ...
    }
}
// The last chance for an exception nothing handled (dynarmic's fastmem faults are handled before
// this, by its own handler): the guest state, then the default (the process ends).
static LONG WINAPI unhandled_exception(EXCEPTION_POINTERS* ep) {
    Cpu* c = t_current;
    const EXCEPTION_RECORD* r = ep->ExceptionRecord;
    const u64 exe = (u64)GetModuleHandleA(nullptr);
    report_overflow(r->NumberParameters >= 2 ? (uintptr_t)r->ExceptionInformation[1] : 0, (uintptr_t)ep->ContextRecord->Rsp);
    fprintf(stderr, "\n*** host exception %#lx at %p = exe+%#llx (fault addr %#llx, thread %d) ***\n", (unsigned long)r->ExceptionCode,
            r->ExceptionAddress, (unsigned long long)((u64)r->ExceptionAddress - exe),
            r->NumberParameters >= 2 ? (unsigned long long)r->ExceptionInformation[1] : 0ull, (int)gettid());
    // host backtrace as exe offsets (llvm-symbolizer --obj=<the .exe> --adjust-vma=0x140000000 <offset>)
    void* bt[48];
    USHORT n = CaptureStackBackTrace(0, 48, bt, nullptr);
    fprintf(stderr, "host backtrace (exe offsets):");
    for (USHORT i = 0; i < n; i++) fprintf(stderr, " %#llx", (unsigned long long)((u64)bt[i] - exe));
    fprintf(stderr, "\n");
    if (c) {
        fprintf(stderr, "guest pc (last sync) = %s\n", describe_guest_addr(c->pc()).c_str());
        dump_guest_state(*c);
    }
    fflush(stderr);  // (the CRT buffers a redirected stderr; the process ends right after)
    return EXCEPTION_CONTINUE_SEARCH;
}
// --gdb (core/gdbstub.h): an attached debugger sees a fatal fault in guest context first. A vectored
// handler, called last among them: the filter above isn't reached when the unwinder can't get
// through the JIT's frames (the process just ends). Vectored handlers run before dynarmic's own
// (SEH on its code, RtlAddFunctionTable), which takes the fastmem faults that are normal (tagged
// addresses, retried through the memory callbacks): those happen in JIT code, outside every
// module, and are left alone; a fault in the .exe or a DLL is reported.
static LONG WINAPI gdb_fault_handler(EXCEPTION_POINTERS* ep) {
    const EXCEPTION_RECORD* r = ep->ExceptionRecord;
    Cpu* c = t_current;
    if (!g_gdb_enabled || !c) return EXCEPTION_CONTINUE_SEARCH;
    switch (r->ExceptionCode) {
    case EXCEPTION_ACCESS_VIOLATION:
    case EXCEPTION_ILLEGAL_INSTRUCTION:
    case EXCEPTION_PRIV_INSTRUCTION:
    case EXCEPTION_INT_DIVIDE_BY_ZERO:
    case EXCEPTION_STACK_OVERFLOW:
    case EXCEPTION_IN_PAGE_ERROR:
    case EXCEPTION_DATATYPE_MISALIGNMENT: break;
    default: return EXCEPTION_CONTINUE_SEARCH;
    }
    HMODULE m = nullptr;
    if (!GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, (LPCSTR)r->ExceptionAddress, &m))
        return EXCEPTION_CONTINUE_SEARCH;  // JIT code: dynarmic's
    gdb_fault(c, gdb_signal_of(r->ExceptionCode));
    return EXCEPTION_CONTINUE_SEARCH;
}
// A host stack overflow (EXCEPTION_STACK_OVERFLOW): reported and ended here. The guard page is
// used up, so the thread runs on the stack SetThreadStackGuarantee kept (crash_thread_begin), and
// the unhandled-exception filter above isn't reliably reached. Registered after gdb_fault_handler,
// so an attached debugger sees it first.
static LONG WINAPI stack_overflow_handler(EXCEPTION_POINTERS* ep) {
    const EXCEPTION_RECORD* r = ep->ExceptionRecord;
    if (r->ExceptionCode != EXCEPTION_STACK_OVERFLOW) return EXCEPTION_CONTINUE_SEARCH;
    const uintptr_t sp = (uintptr_t)ep->ContextRecord->Rsp;
    if (const CrashThread* ct = crash_thread())
        crash_report_overflow(*ct, sp);
    else
        fprintf(stderr, "\n*** stack overflow on thread ? (tid %d, a thread the runtime didn't set up) ***\n", (int)gettid());
    const u64 exe = (u64)GetModuleHandleA(nullptr);
    fprintf(stderr, "host exception %#lx at %p = exe+%#llx\n", (unsigned long)r->ExceptionCode, r->ExceptionAddress,
            (unsigned long long)((u64)r->ExceptionAddress - exe));
    void* bt[48];
    USHORT n = CaptureStackBackTrace(0, 48, bt, nullptr);
    fprintf(stderr, "host backtrace (exe offsets):");
    for (USHORT i = 0; i < n; i++) fprintf(stderr, " %#llx", (unsigned long long)((u64)bt[i] - exe));
    fprintf(stderr, "\n");
    if (Cpu* c = t_current) {
        fprintf(stderr, "guest pc (last sync) = %s\n", describe_guest_addr(c->pc()).c_str());
        dump_guest_state(*c);
    }
    fflush(stderr);
    TerminateProcess(GetCurrentProcess(), (UINT)EXCEPTION_STACK_OVERFLOW);
    return EXCEPTION_CONTINUE_SEARCH;
}
static LONG WINAPI log_fault(EXCEPTION_POINTERS* ep) {
    static std::atomic<int> n{0};
    const EXCEPTION_RECORD* r = ep->ExceptionRecord;
    if (r->ExceptionCode < 0xc0000000u || n++ >= 20) return EXCEPTION_CONTINUE_SEARCH;
    fprintf(stderr, "fault: %#lx at %p, address %#llx, thread %d; host stack:", (unsigned long)r->ExceptionCode, r->ExceptionAddress,
            r->NumberParameters >= 2 ? (unsigned long long)r->ExceptionInformation[1] : 0ull, (int)gettid());
    void* bt[32];
    USHORT k = CaptureStackBackTrace(0, 32, bt, nullptr);
    for (USHORT i = 0; i < k; i++) {  // module+offset (llvm-symbolizer --obj=MODULE 0x140000000+offset for the .exe)
        HMODULE m = nullptr;
        char name[MAX_PATH] = "?";
        if (GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, (LPCSTR)bt[i], &m))
            GetModuleFileNameA(m, name, sizeof name);
        const char* base = strrchr(name, '\\') ? strrchr(name, '\\') + 1 : name;
        fprintf(stderr, " %s+%#llx", base, (unsigned long long)((u64)bt[i] - (u64)m));
    }
    fprintf(stderr, "\n");
    if (Cpu* c = t_current)
        fprintf(stderr, "fault: guest pc %s, x0=%#llx x1=%#llx x2=%#llx, lr %s\n", describe_guest_addr(c->pc()).c_str(), (unsigned long long)c->x(0),
                (unsigned long long)c->x(1), (unsigned long long)c->x(2), describe_guest_addr(c->x(30)).c_str());
    fflush(stderr);
    return EXCEPTION_CONTINUE_SEARCH;
}
#else
// Runs on the thread's alternate signal stack (crash_thread_begin; SA_ONSTACK), so it also
// reports a host stack overflow. For SIGSEGV dynarmic's handler runs first (its fastmem faults in
// JIT code) and calls this one for every other fault.
static void segv_handler(int sig, siginfo_t* si, void* uctx) {
    Cpu* c = t_current;
    report_overflow((uintptr_t)si->si_addr, (uintptr_t)((ucontext_t*)uctx)->uc_mcontext.gregs[REG_RSP]);
    fprintf(stderr, "\n*** host signal %d (fault addr %p, thread %ld) ***\n", sig, si->si_addr, (long)gettid());
    {
        // host backtrace (module(+offset): `addr2line -e soa -f -C <offset>` names the frames)
        void* bt[48];
        int n = backtrace(bt, 48);
        fprintf(stderr, "host backtrace:\n");
        backtrace_symbols_fd(bt, n, 2);
    }
    if (c) {
        fprintf(stderr, "guest pc (last sync) = %s\n", describe_guest_addr(c->pc()).c_str());
        dump_guest_state(*c);
        if (g_gdb_enabled)  // an attached debugger sees the fault first
            gdb_fault(c, sig == SIGILL ? kGdbSigIll : sig == SIGFPE ? kGdbSigFpe : sig == SIGBUS ? kGdbSigBus : kGdbSigSegv);
    }
    signal(sig, SIG_DFL);
    raise(sig);
}
#endif

void cpu_global_init() {
    crash_thread_begin("main");  // (the host program's main thread)
    g_thunks = new ThunkEntry[kMaxThunks];
    soa_gdb_thunks = g_thunks;
    void* p = hostmem::map_rw(kMaxThunks * 8);
    if (!p) fatal("thunk mapping failed");
    g_thunk_code = (u32*)p;
    g_thunk_code[0] = enc_svc(0);
    g_thunk_code[1] = 0xd61f0200;  // BR X16: guest_call's entry (see guest_call_raw)
    g_thunks[0].name = "<return-to-host>";
    g_proc_used.assign(kMaxProcessors, false);
    g_monitor = new Dynarmic::ExclusiveMonitor(kMaxProcessors);

#ifdef _WIN32
    SetUnhandledExceptionFilter(unhandled_exception);
    // SOA_FAULT_LOG (Windows): every first-chance fault, with module offsets and the guest's pc. A
    // crash in a system DLL called from a thunk (e.g. strstr(NULL) in ucrtbase) ended the process
    // without reaching the filter above.
    if (env::env_bool("SOA_FAULT_LOG", false)) AddVectoredExceptionHandler(1, log_fault);
    AddVectoredExceptionHandler(0, gdb_fault_handler);  // (nothing unless --gdb)
    AddVectoredExceptionHandler(0, stack_overflow_handler);
#else
    {
        void* bt[1];
        backtrace(bt, 1);  // the first call loads libgcc_s: not in the handler, on a small stack
    }
    struct sigaction sa {};
    sa.sa_sigaction = segv_handler;
    sa.sa_flags = SA_SIGINFO | SA_ONSTACK;
    sigaction(SIGSEGV, &sa, nullptr);
    sigaction(SIGBUS, &sa, nullptr);
    sigaction(SIGILL, &sa, nullptr);
    sigaction(SIGFPE, &sa, nullptr);
#endif
}

void dump_guest_state(Cpu& c) {
    fprintf(stderr, "  pc=%s  sp=%016" PRIx64 "  lr=%s\n", describe_guest_addr(c.pc()).c_str(), c.sp(), describe_guest_addr(c.x(30)).c_str());
    for (int i = 0; i < 31; i += 4) {
        fprintf(stderr, " ");
        for (int j = i; j < i + 4 && j < 31; j++) fprintf(stderr, " x%-2d=%016" PRIx64, j, c.x(j));
        fprintf(stderr, "\n");
    }
    // Frame-pointer walk
    u64 fp = c.x(29);
    const auto& ti = t_state.info;
    for (int i = 0; i < 32 && fp >= ti.stack_lo && fp + 16 <= ti.stack_hi && (fp & 7) == 0; i++) {
        u64 ret = ((u64*)fp)[1];
        fprintf(stderr, "  #%d %s\n", i, describe_guest_addr(ret).c_str());
        u64 next = ((u64*)fp)[0];
        if (next <= fp) break;
        fp = next;
    }
}

}  // namespace soa
