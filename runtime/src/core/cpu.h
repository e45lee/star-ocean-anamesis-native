#pragma once
// Guest CPU: dynarmic A64 JIT instances, one (or more, when nested) per host thread.
//
// Guest memory is identity-mapped: a guest virtual address is the host address,
// so HLE code can dereference guest pointers directly.
#include <array>
#include <atomic>
#include <cstdint>
#include <cstring>
#include <memory>
#include <string>
#include <type_traits>
#include <vector>

namespace Dynarmic::A64 { class Jit; }

namespace soa {

using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using s8 = std::int8_t;
using s16 = std::int16_t;
using s32 = std::int32_t;
using s64 = std::int64_t;

class Cpu;
using HostFn = void (*)(Cpu&);

// A 128-bit SIMD register value.
struct V128 { u64 lo, hi; };

struct GuestResult {
    u64 x0;
    V128 v0;
    u64 x1 = 0;             // second result register (16-byte integer returns)
    V128 v1{}, v2{}, v3{};  // rest of a homogeneous float aggregate result (e.g. a Vector)
};

class Cpu {
public:
    // Register access reads and writes the JIT's register file directly (inline; no call into
    // dynarmic). The guest registers are only in sync while the JIT is stopped or inside a
    // callback (SVC), which is when host code runs.
    u64 x(int i) const { return i == 31 ? 0 : st_[i]; }
    void set_x(int i, u64 v) { st_[i] = v; }
    V128 v(int i) const { return {vec_[2 * i], vec_[2 * i + 1]}; }
    void set_v(int i, V128 v) {
        vec_[2 * i] = v.lo;
        vec_[2 * i + 1] = v.hi;
    }
    u64 sp() const { return st_[31]; }
    void set_sp(u64 v) { st_[31] = v; }
    u64 pc() const { return st_[32]; }
    u64 lr() const { return x(30); }

    float s(int i) const { float f; u32 b = (u32)vec_[2 * i]; std::memcpy(&f, &b, 4); return f; }
    double d(int i) const { double f; u64 b = vec_[2 * i]; std::memcpy(&f, &b, 8); return f; }
    void set_s(int i, float f) { u32 b; std::memcpy(&b, &f, 4); set_v(i, {b, 0}); }
    void set_d(int i, double f) { u64 b; std::memcpy(&b, &f, 8); set_v(i, {b, 0}); }

    // Raw register file: x0..x30, sp, pc (33 words), and v0..v31 (two words each).
    u64* xregs() { return st_; }
    u64* vregs() { return vec_; }

    void halt();
    // Pending halt reasons (dynarmic HaltReason bits); a plain read of the JIT's word.
    u32 halt_reason() const { return *halt_; }
    void set_tpidr(u64 v);
    Dynarmic::A64::Jit* jit() { return jit_.get(); }

    ~Cpu();

private:
    friend struct CpuImpl;
    friend class ThreadState;
    friend struct CpuCallbacks;
    friend GuestResult guest_call_raw(u64, const u64*, size_t, const V128*, size_t, u64);
    Cpu();
    void locate_jit_state();
    void set_pc(u64 v) { st_[32] = v; }
    u64* st_ = nullptr;   // dynarmic's A64JitState::reg[31], sp, pc
    u64* vec_ = nullptr;  // dynarmic's A64JitState::vec[64]
    u32* nzcv_ = nullptr; // A64JitState::cpsr_nzcv
    volatile u32* halt_ = nullptr;  // A64JitState::halt_reason
    std::unique_ptr<Dynarmic::A64::Jit> jit_;
    std::unique_ptr<struct CpuCallbacks> cb_;
    size_t processor_id_ = 0;
};

// ---- Thunks: host functions reachable from guest code via "SVC #n; RET" stubs ----

// Registers a host function and returns the guest address of its stub.
u64 make_thunk(const char* name, HostFn fn);
// Name of the thunk at a guest address, or nullptr.
const char* thunk_name_at(u64 addr);
// Overwrites a guest function's entry with an SVC stub so calls go to `fn` instead.
void hook_guest_function(u64 guest_addr, const char* name, HostFn fn);
// Drops this host thread's JIT translations of a guest code range (after patching it at run time).
void invalidate_guest_code_this_thread(u64 addr, u64 size);
// This host thread's guest_call nesting depth (the first level invalidate_guest_code_this_thread
// reaches).
size_t guest_depth_this_thread();
// Guest CPU context bookkeeping (core/memstats.cpp, soa --memstats): live contexts (each one a
// dynarmic JIT with its own code cache), the highest processor id + 1 ever used, the limit, and
// per host thread that holds contexts: its tid, nesting levels allocated, and the guest function
// of its last outermost guest_call (the thread entry for guest threads).
struct CpuMemStats {
    struct Thread {
        int tid;
        size_t levels;
        u64 entry;
        bool operator<(const Thread& o) const { return tid < o.tid; }
    };
    size_t contexts = 0, peak_ids = 0, limit = 0;
    std::vector<Thread> threads;
};
CpuMemStats cpu_memstats();
// Drops every thread's JIT translations of [addr, addr + size) (thread-safe: each JIT drops them
// at its next Run() entry or halt; running ones halt and resume). JIT translations are keyed by
// address only, so code memory that is unmapped and mapped again must go through this, or a JIT
// that ran the old code there keeps running it.
void invalidate_guest_code(u64 addr, u64 size);
// Host-built guest code (trampolines, test snippets): an anonymous read/write mapping whose range
// was invalidated in every JIT (see invalidate_guest_code), and its release.
void* map_guest_code(size_t bytes);
void unmap_guest_code(void* p, size_t bytes);
// Host function that replaces the guest function at `guest_addr` (hook_guest_function), or
// nullptr. Lock-free: valid once the hooks are installed (they are, before guest code runs).
HostFn hooked_host_fn(u64 guest_addr);
// Per-thread interception of hooked guest functions (live checks that must not repeat a callee's
// side effects, e.g. particles_rt.cpp's render check): while set on a thread, a call to a hooked
// function (guest code through its SVC hook, or native code through models_gcall) first asks the
// filter, and when it returns true (it produced the result registers) the hook's host function is
// skipped. Off (nullptr) normally.
extern thread_local bool (*t_hook_filter)(Cpu& c, u64 hook_addr);
// Builds a trampoline that runs a function's original code (its first two instructions,
// relocated, then a jump back). Call it before hooking. Returns 0 if the prologue is
// PC-relative and can't be relocated.
u64 make_original_trampoline(u64 guest_addr);
// Address of the "return to host" stub used as LR for host->guest calls.
u64 host_return_addr();

// ---- Calling guest code from the host ----

// Small vector with inline storage (spills to the heap past N): GuestArgs builds its argument
// lists without allocating. Supports the std::vector operations callers use.
template <typename T, size_t N>
class ArgVec {
public:
    ArgVec() = default;
    ArgVec(const ArgVec& o) { assign(o.begin(), o.end()); }
    ArgVec& operator=(const ArgVec& o) {
        if (this != &o) assign(o.begin(), o.end());
        return *this;
    }
    ArgVec& operator=(std::initializer_list<T> l) {
        assign(l.begin(), l.end());
        return *this;
    }
    size_t size() const { return n_; }
    bool empty() const { return n_ == 0; }
    T* data() { return p_; }
    const T* data() const { return p_; }
    T* begin() { return p_; }
    T* end() { return p_ + n_; }
    const T* begin() const { return p_; }
    const T* end() const { return p_ + n_; }
    T& operator[](size_t i) { return p_[i]; }
    const T& operator[](size_t i) const { return p_[i]; }
    void clear() { n_ = 0; }
    void reserve(size_t c) {
        if (c > cap_) grow(c);
    }
    void push_back(const T& v) {
        if (n_ == cap_) grow(cap_ * 2);
        p_[n_++] = v;
    }
    template <typename It>
    void assign(It b, It e) {
        n_ = 0;
        insert(end(), b, e);
    }
    template <typename It>
    T* insert(T* pos, It b, It e) {  // only at end()
        (void)pos;
        size_t k = (size_t)(e - b);
        if (n_ + k > cap_) grow(n_ + k > cap_ * 2 ? n_ + k : cap_ * 2);
        for (size_t i = 0; i < k; i++) p_[n_ + i] = b[i];
        n_ += k;
        return p_ + n_;
    }

private:
    void grow(size_t c) {
        std::unique_ptr<T[]> h(new T[c]);
        for (size_t i = 0; i < n_; i++) h[i] = p_[i];
        heap_ = std::move(h);
        p_ = heap_.get();
        cap_ = c;
    }
    T buf_[N];
    T* p_ = buf_;
    size_t n_ = 0, cap_ = N;
    std::unique_ptr<T[]> heap_;
};

struct GuestArgs {
    ArgVec<u64, 16> ints;
    ArgVec<V128, 8> vecs;
    u64 x8 = 0;  // indirect result location (functions returning large/non-trivial structs)
    GuestArgs& sret(void* p) { x8 = (u64)(uintptr_t)p; return *this; }
    GuestArgs& i(u64 v) { ints.push_back(v); return *this; }
    GuestArgs& p(const void* v) { ints.push_back((u64)(uintptr_t)v); return *this; }
    GuestArgs& f(float v) { u32 b; std::memcpy(&b, &v, 4); vecs.push_back({b, 0}); return *this; }
    GuestArgs& d(double v) { u64 b; std::memcpy(&b, &v, 8); vecs.push_back({b, 0}); return *this; }
};

// Calls a guest function on the current host thread (nesting is allowed: calls made from
// inside a thunk run on a per-thread, per-depth JIT instance using the caller's stack below
// its SP). A target that is a native replacement (hook_guest_function) or a thunk stub
// (make_thunk) is called directly, without entering the JIT.
GuestResult guest_call(u64 fn, const GuestArgs& args);
// Core of every guest_call form: ints[0..7] -> x0..x7, vecs[0..7] -> v0..v7, the rest on the
// stack (integers first, then FP), x8 = indirect result pointer.
GuestResult guest_call_raw(u64 fn, const u64* ints, size_t nints, const V128* vecs, size_t nvecs, u64 x8);
// A guest call from transcribed ARM64 code (the *_a2c bodies): x[0..8] and v (v0..v7) are the body's
// argument registers, body_sp its SP. Moves the current CPU's SP below the body's frame for the
// call and passes the body's stack slots as the callee's stack arguments. (guest_call runs the
// callee 512 bytes below the current SP, so a callee with stack arguments -- more than 8 integer
// or 8 FP arguments, or large by-value structs -- would otherwise read unrelated stack words.)
// When the body runs on the current guest stack (body_sp below the CPU's SP) the slots passed are
// the first 16, bounded by the CPU's SP (the body's frame ends there); otherwise (a body on a host
// buffer) the first 8.
constexpr size_t kA2cStackSlots = 16;
GuestResult a2c_guest_call(u64 fn, const u64* x, const void* v /* 8 x 16 bytes */, u64 body_sp);
inline u64 guest_call(u64 fn, std::initializer_list<u64> ints) {
    return guest_call_raw(fn, ints.begin(), ints.size(), nullptr, 0, 0).x0;
}

// Typed variadic form: guest_invoke<R>(fn, args...) passes integer/pointer/enum arguments in
// x registers and float/double ones in v registers (AAPCS64 order), without allocating, and
// returns R from x0 (integers, pointers, bool) or v0 (float, double); R = void or GuestResult
// are allowed too.
namespace detail {
struct InvokeRegs {
    u64 x[16];
    V128 v[16];
    size_t nx = 0, nv = 0;
    template <typename T>
    void put(T a) {
        if constexpr (std::is_floating_point_v<T>) {
            V128 q{0, 0};
            std::memcpy(&q.lo, &a, sizeof(T));
            v[nv++] = q;
        } else if constexpr (std::is_pointer_v<T>) {
            x[nx++] = (u64)(uintptr_t)a;
        } else {
            static_assert(std::is_integral_v<T> || std::is_enum_v<T>, "guest_invoke: unsupported argument type");
            x[nx++] = (u64)a;
        }
    }
};
}  // namespace detail
template <typename R = u64, typename... A>
inline R guest_invoke(u64 fn, A... args) {
    static_assert(sizeof...(A) <= 16, "guest_invoke: too many arguments");
    detail::InvokeRegs r;
    (r.put(args), ...);
    GuestResult g = guest_call_raw(fn, r.x, r.nx, r.v, r.nv, 0);
    if constexpr (std::is_void_v<R>) {
        (void)g;
    } else if constexpr (std::is_same_v<R, GuestResult>) {
        return g;
    } else if constexpr (std::is_floating_point_v<R>) {
        R f;
        std::memcpy(&f, &g.v0.lo, sizeof(R));
        return f;
    } else if constexpr (std::is_same_v<R, bool>) {
        return (g.x0 & 0xff) != 0;
    } else if constexpr (std::is_pointer_v<R>) {
        return (R)(uintptr_t)g.x0;
    } else {
        return (R)g.x0;
    }
}

// Direct native->native calls (see guest_call) are on by default; SOA_DIRECT_CALLS=0 turns
// them off (every guest_call then enters the JIT). Tests toggle it to compare both paths.
void set_direct_host_calls(bool on);
bool direct_host_calls();

// The CPU currently executing on this thread (innermost), or nullptr.
Cpu* current_cpu();

// Per-thread guest environment (stack + TLS block).
struct GuestThreadInfo {
    u64 stack_lo = 0, stack_hi = 0;
    u64* tls = nullptr;           // TPIDR_EL0 value points here
    bool exiting = false;         // set by pthread_exit
    u64 exit_value = 0;
};
GuestThreadInfo& guest_thread();
// Allocates the guest stack for this host thread (otherwise a default one is created lazily).
void guest_thread_init(size_t stack_size);
void guest_thread_release();

void cpu_global_init();

// ---- Profiling support (used by core/profile.cpp; inert unless g_prof_enabled) ----

// Guest-side state of one host thread, readable from the profiler's sampling thread.
struct ProfLevel {
    std::atomic<u32> svc{0};      // thunk index while this JIT level is inside host code, else 0
    std::atomic<u32> seq{0};      // bumped on every SVC (lets the sampler reuse an unchanged stack)
    std::atomic<u8> wait{0};      // the native function running in this level is blocked (prof_native_wait)
    u64 pc = 0, lr = 0, fp = 0, sp = 0;  // guest registers at that SVC
};
constexpr int kProfLevels = 32;  // nesting levels tracked (deeper guest_call nesting is ignored)
struct ProfThread {
    int id = 0;
    std::atomic<int> depth{0};                  // number of active guest_call levels
    std::atomic<Cpu*> cpu[kProfLevels] = {};    // JIT running each level
    ProfLevel lv[kProfLevels];
    std::atomic<u64> entry{0};                  // function of the outermost guest_call
    u64 stack_lo = 0, stack_hi = 0;             // guest stack bounds
    u64 host_thread = 0;                        // pthread_t of the host thread (SOA_PROFILE_HOST)
};
extern bool g_prof_enabled;                // set once, before guest code runs
extern std::atomic<u64>* g_thunk_calls;    // per-thunk call counts (when g_prof_enabled)
// Called on the guest thread when its JIT was halted for a sample (see prof_request_sample).
extern void (*g_prof_sample)(Cpu& c, ProfThread& t);
// Native replacements call this around a blocking host wait (cond/sem wait, sleep) so the
// profiler counts that time as waiting, like the HLE'd waits, rather than native work.
void prof_native_wait(bool waiting);
struct ProfNativeWait {
    ProfNativeWait() { prof_native_wait(true); }
    ~ProfNativeWait() { prof_native_wait(false); }
};

// Runs fn on every thread that has executed guest code, holding the registry lock.
void prof_for_each_thread(void (*fn)(ProfThread& t, void* ctx), void* ctx);
// Asks a running JIT to stop at the next block boundary and call g_prof_sample.
void prof_request_sample(Cpu* c);
// "SVC #n" instruction that traps to the thunk whose stub make_thunk returned.
u32 thunk_trap_insn(u64 stub);
u32 thunk_count();
const char* thunk_name(u32 idx);
// Guest address a thunk index is hooked at (0 for plain HLE thunks).
u64 thunk_hook_addr(u32 idx);

// ---- Debugger support (core/gdbstub.cpp; inert unless g_gdb_enabled) ----

// A host thread that holds guest CPU contexts, as the GDB stub sees it: its kernel tid, the CPU of
// its innermost guest_call level in use (the one whose registers gdb shows; level 0's when the
// thread is in no guest_call), whether that level is running JIT code right now (false: parked,
// in a host function, or outside guest code), and its last outermost guest function.
struct GuestThreadView {
    int tid;
    Cpu* cpu;
    bool in_jit;
    u64 entry;
};
std::vector<GuestThreadView> guest_threads();
// HaltExecution(reason) on every live guest CPU (running ones stop at their next block boundary,
// idle ones as soon as they run).
void halt_all_guest_cpus(u32 reason);

// Symbolization for diagnostics.
std::string describe_guest_addr(u64 addr);
void dump_guest_state(Cpu& c);

}  // namespace soa
