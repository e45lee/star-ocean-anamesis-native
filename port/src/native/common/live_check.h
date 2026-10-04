#pragma once
// The shared live differential check ("live check") of native families: one harness for every
// family that checks its natives against the guest originals in a normal run.
//
// Two kinds of check use it:
//
// 1. Record / replay (A64 families: arena, objbase; their transcribed bodies and hand-written
//    functions call out through Family::gcall / icall / memop / ACall). A checked call runs the
//    native first, for real, with every outgoing call recorded (target, argument registers,
//    results, the snapshot regions after it, stack buffers the callee wrote). Then the regions
//    are put back and the guest original (the hook's trampoline) runs with every recorded callee
//    replaced by a replay stub (guest_stub.h) that checks target and arguments and plays back the
//    recorded effects. Call sequence, region bytes and x0 / v0 must match; side effects happen
//    once (in the native run). See check_a64() in live_check.cpp for every rule the replay uses.
//    The families with their own recorders (charobj, battle core: calls from hand-written C++
//    through GuestArgs) replay through the same stub registry and ReplaySession.
//
// 2. Run both (particles, dynamics): the family runs the original and the native from the same
//    state and compares; they share the switches, the chosen-set filter and the Budget counters.
//
// Switched on per family from the command line (soa --live-check, parse_live_check below):
//   --live-check FAMILY[,FAMILY..][:KEY[=VALUE]..]   (repeatable; FAMILY = the family's tag)
// keys: every=N (every n-th call per function; default the family's), budget=N (checks per
// function at most), out=FILE (per-function counts, record / replay families), only=SUB[|SUB..]
// (check only functions whose symbol contains one of these: the others run natively without a
// check, so the chosen ones are checked also where they are nested callees of other natives),
// trace, dump (debugging). E.g. --live-check arena:every=4:only=Alloc|Free. Registered: lib_sqlite
// (its own shadow run: native/lib_sqlite/lib_sqlite_api.cpp; it uses the switch and out=).
#include <atomic>
#include <cstdio>
#include <cstring>
#include <functional>
#include <map>
#include <mutex>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "core/cpu.h"
#include "native/common/a2c_regs.h"
#include "native/common/guest_stub.h"

namespace soa::live {

using a2c::A64;
using a2c::Body;
using a2c::V4;
using a2c::a2c_gcall;

// ---- switches (soa --live-check) ----

// One family's --live-check options.
struct CheckOptions {
    int every = 0;   // 0: the family's default
    int budget = 0;  // 0: no limit
    std::string out;
    std::vector<std::string> only;
    bool trace = false, dump = false;
};
// Parses one --live-check value (main.cpp) into the process-wide table; false (and *err) when it
// is malformed. Families are checked against the registered ones by apply_live_check.
bool parse_live_check(const std::string& spec, std::string* err);
// After the natives are registered (before they are installed): false (and *err, naming the
// registered families) when --live-check named a family that doesn't exist; else every family
// named takes its options and is switched on.
bool apply_live_check(std::string* err);
// The chosen set (only=): substrings of symbols. Empty = every function.
struct Only {
    std::vector<std::string> subs;
    bool any() const { return !subs.empty(); }
    bool match(const char* sym) const;
};

// ---- callees ----

// A PLT entry (ADRP x16; LDR x17, [x16, #off]; ADD; BR x17) -> the address in its GOT slot.
u64 resolve_plt(u64 a);
// A function that is a lone B (a 4-byte tail branch, too small to stub) -> where it branches.
u64 follow_b(u64 a);
// Where a call to `target` really lands: PLT entries and lone-B hops followed (PLT -> B -> PLT, up
// to 4 hops).
u64 callee(u64 target);
bool is_ret_only(u64 a);  // a lone RET: nothing to replay

// ---- stubs (process-wide, shared by every family) ----

// The replay stub name at `target` ("live:<off>"), stubbing it once; nullptr if it can't be
// stubbed. A name another stubber took over is re-applied.
const char* ensure_stub(u64 target);
// The replay's JIT level may hold a callee's code from before its stub (stubbing drops only the
// idle levels of the thread it runs on, at that time): dropped once per thread and level. (Not on
// every check: dynarmic keeps invalidated code in its cache until the cache is full, so a level
// recompiling its callees at every check grows towards its 256 MB cache, times every level of
// every thread.)
void drop_stale_code(u64 target);
// The replay's stub session: never answers a stub it wasn't given (its `only` is never empty: a
// session without one answers every other stub with 0).
struct ReplaySession : native::StubSession {
    ReplaySession() { only.insert("live:(none)"); }
    void answer(const std::string& name, Behaviour b) {
        behave[name] = std::move(b);
        only.insert(name);
    }
};
// A replay that ran past its record may loop for ever (e.g. over a list whose links the stubs
// don't maintain): past kRunaway extra calls, stop_runaway() makes the stub return to the host.
constexpr int kRunaway = 16;
void stop_runaway(Cpu& c);

// Runs guest function `fn` with its stack pointer exactly at `sp` (a hook's entry SP: stack
// arguments above it are in place). guest_call runs a nested call 512 bytes below the current
// CPU's SP, so that is moved for the call.
GuestResult guest_call_at_sp(u64 fn, const u64* x, const void* v /* 8 x 16 bytes */, u64 x8, u64 sp);

// ---- memory ----

constexpr u64 kStackBelow = 0x20000, kStackAbove = 0x10000, kBuf = 0x40;
inline bool in_stack(u64 v, u64 sp) { return v >= sp - kStackBelow && v < sp + kStackAbove; }
constexpr size_t kMaxRecord = 64 << 20;  // a check's snapshots, at most (then it is skipped)
constexpr u64 kFrameSnap = 0x1000;       // stack bytes below the entry SP the replay gets back (the body's frame)

// The memory a check snapshots: (address, bytes). The first is "object", the rest "global".
struct Regions {
    std::vector<std::pair<u64, u32>> r;
    void add(u64 a, u32 n) { r.push_back({a, n}); }
    std::vector<u8> capture() const;
    void restore(const std::vector<u8>& b) const;
    // Only the bytes where `now` (a capture) differs from `want`.
    void restore_diff(const std::vector<u8>& now, const std::vector<u8>& want) const;
    std::string where(size_t k) const;  // "<region> +off" of byte k of a capture
};

// Writes undone later (newest first).
struct Journal {
    std::vector<std::pair<u64, std::vector<u8>>> w;
    void write(u64 a, const std::vector<u8>& v);
    void undo();
};

// Store log: (address, the bytes overwritten, size). The record / replay check's undo log of a
// transcribed body's own stores, and the particles check's store log.
struct StoreLog {
    struct E {
        u64 a;
        u64 old;
        u32 n;
    };
    std::vector<E> v;
    void undo() const {
        for (size_t k = v.size(); k-- > 0;) std::memcpy((void*)v[k].a, &v[k].old, v[k].n);
    }
};

// ---- the Aska random state pin ----
// The Aska random-number generators (Aska::Random / RandomShort / RandomFloat / ... and MT::Rand,
// which HighPrecisionRandom tail-calls; and g_uiLowPrecisionRandomSeed) keep their state in one guest .bss block that every
// thread draws from. A run-both check that puts that state back and compares it pins it for the
// check's window (RandPin): another thread's draw (RandDraw) waits until the pin is released, for
// at most kPinWaitMs; then it draws anyway and counts as a pin violation (so a check never
// deadlocks on a thread it waits for), which the check sees in rand_violations() and treats as a
// proven race. The pin also waits for draws already past the gate. (The low-precision seed's
// inline draws in guest code and in the transcriptions can't be gated.)
constexpr int kPinWaitMs = 200;
extern std::atomic<int> g_rand_pin;       // the pinning thread's tid (0: none)
extern std::atomic<int> g_rand_inflight;   // draws in progress (a pin waits for them to end)
extern std::atomic<bool> g_rand_tracking;  // a family with a pinning check is on (else draws skip all this)
void rand_tracking_on();
// One draw (scope): waits for a pin another thread holds, and counts as in progress, so a pin
// taken meanwhile waits for it to end (a draw that passed the gate can't overlap the pinned window).
struct RandDraw {
    bool on = false;
    RandDraw() {
        if (__builtin_expect(!g_rand_tracking.load(std::memory_order_relaxed), 1)) return;
        on = true;
        for (;;) {
            g_rand_inflight.fetch_add(1, std::memory_order_acq_rel);
            if (__builtin_expect(g_rand_pin.load(std::memory_order_acquire) == 0, 1)) return;
            g_rand_inflight.fetch_sub(1, std::memory_order_acq_rel);
            if (rand_gate_pinned_by_me()) {
                g_rand_inflight.fetch_add(1, std::memory_order_acq_rel);
                return;
            }
            if (!rand_gate_wait()) {  // (a violation: draws anyway)
                g_rand_inflight.fetch_add(1, std::memory_order_acq_rel);
                return;
            }
        }
    }
    ~RandDraw() {
        if (on) g_rand_inflight.fetch_sub(1, std::memory_order_acq_rel);
    }
    RandDraw(const RandDraw&) = delete;
    RandDraw& operator=(const RandDraw&) = delete;
    static bool rand_gate_pinned_by_me();
    static bool rand_gate_wait();  // false: timed out (counted as a violation)
};
u64 rand_violations();
struct RandPin {  // pins for the calling thread (nests)
    RandPin();
    ~RandPin();
    RandPin(const RandPin&) = delete;
    RandPin& operator=(const RandPin&) = delete;
};

// Per-function counters of a budgeted run-both check (particles, dynamics). races: a difference
// every attempt showed while another thread provably touched the shared state (not a mismatch).
struct Budget {
    std::atomic<int> budget{0}, done{0}, bad{0}, unstable{0}, races{0};
    std::mutex m;
    std::vector<std::string> errs;
    // One check off the budget (false: none left).
    bool take() { return budget.load(std::memory_order_relaxed) > 0 && budget.fetch_sub(1) > 0; }
    void fail(const std::string& e, size_t keep = 3) {
        std::lock_guard lk(m);
        if (errs.size() < keep) errs.push_back(e);
    }
    void reset(int n) {
        budget = n;
        done = 0, bad = 0, unstable = 0, races = 0;
        std::lock_guard lk(m);
        errs.clear();
    }
};

// ---- the record / replay (A64) families ----

enum RetKind : u8 { kVoid = 0, kInt = 1, kFloat = 2, kAll = 3 };

struct Entry;

// A family: its switches and the rules only it knows. The rules about callees (blocks they free,
// objects they return, out-parameters they write whole) are shared (live_check.cpp).
class Family {
public:
    // tag: log tag (I/<tag>_check), registration label and --live-check name ("arena");
    // every: the default of --live-check's every=; sret_marked: the generator marks x8 = sret calls
    // (gcall_sret); otherwise any 8-aligned stack x8 is treated as one (its first 16 bytes are
    // always replayed).
    Family(const char* tag, int every, bool sret_marked);
    virtual ~Family() = default;

    const char* tag;
    std::string log_tag;  // "<tag>_check"
    std::atomic<bool> on{false};  // --live-check <tag> (a test may switch it at run time)
    int every;
    int budget = 0;  // checks per function at most (0: no limit)
    bool sret_marked;
    Only only;
    std::string out_path;  // --live-check <tag>:out=FILE
    bool trace = false, dump = false;

    // Regions to snapshot besides the object at x0 (obj_bytes): globals, out-parameters, the
    // nodes of structures the call links or unlinks. `has_obj`: x0's object is regions.r[0].
    virtual void add_regions(const Entry&, const u64 x[9], bool has_obj, Regions&) {}
    // Functions whose calls can't be replayed (counted as skipped).
    virtual bool unreplayable(const char*) { return false; }
    // Callees that mustn't be stubbed (e.g. the family's own test-hooked functions): a call to
    // one makes the check unreplayable.
    virtual bool stubbable(u64) { return true; }
    // Results, for families that collect them (a test): a mismatch (its messages) or a skip
    // (why). The log gets the first mismatches either way.
    virtual void on_mismatch(const Entry&, const std::string&) {}
    virtual void on_skip(const Entry&, const std::string&) {}

    // Registers a native at `sym` (hooked through the check when the family is on): a
    // hand-written host function (run) or a transcribed body (body). `enabled`: the family's
    // on switch; `label`: the registry's description.
    int add(const char* sym, HostFn run, Body body, u32 obj_bytes, RetKind ret, bool (*enabled)(), const char* label);
    // A transcribed body checked through a test hook (--selftest, where natives aren't installed):
    // calls that aren't checked run the guest original. `user`: the family's own index.
    int add_test(const char* sym, Body body, u32 obj_bytes, RetKind ret, int user);

    // Outgoing calls of the family's natives (transcribed bodies and ACall).
    void gcall(A64& r, u64 target);
    void icall(A64& r, u64 target);  // (a virtual call; a guest call when not recorded)
    void gcall_sret(A64& r, u64 target);  // x8 is an sret buffer in the caller's frame
    // A call from readable code with its real arity: only x0..x(ni-1) and v0..v(nf-1) (and x8 when
    // `sret`) are arguments; the replay compares only those (like ACall, on a register file of the
    // caller's).
    void gcall_n(A64& r, u64 target, int ni, int nf, bool sret = false);
    void memop(A64& r, u64 target, int kind);  // memset (1) / memcpy (2) / memmove (3), on the host

    // Installed transcribed bodies by guest address (direct calls between them skip the hook).
    const std::unordered_map<u64, Body>& own_bodies();

    void summary(FILE* f);  // per-function counts
    void summary_file();    // to out_path

    struct Stats {
        std::atomic<u64> checks{0}, ok{0}, bad{0}, skipped{0}, races{0};
    } stats;
    int first = -1, count = 0;  // (entries [first, first + count) are this family's, when contiguous)
    std::vector<int> entries;

private:
    std::unordered_map<u64, Body>* own_ = nullptr;
    std::once_flag own_once_;
};

struct Entry {
    Family* fam = nullptr;
    const char* sym = nullptr;
    HostFn run = nullptr;          // a hand-written native
    Body body = nullptr;   // a transcribed one
    u32 obj_bytes = 0;
    RetKind ret = kAll;
    bool test = false;  // a test hook: an unchecked call runs the original
    int user = -1;      // the family's own index
    u64 orig = 0;  // trampoline to the guest original (set when installed)
    std::atomic<u64> calls{0}, checks{0}, ok{0}, bad{0}, skipped{0}, races{0};
    void invoke(Cpu& c) const {
        if (body) a2c::a2c_run_hook(c, body);
        else run(c);
    }
    void run_original(Cpu& c) const;
    void run_unchecked(Cpu& c) const {
        if (test) run_original(c);
        else invoke(c);
    }
};

Entry& entry(int n);  // (an index Family::add / add_test returned)

// Undo log of the checked transcribed body's own stores (the a2c store macros note each one
// while t_undo_on is set): the replay starts from the memory the native run saw.
extern thread_local bool t_undo_on;
void undo_note(u64 a, u32 n);
// Inside a check on this thread (no other call can be checked; every family).
extern thread_local bool t_busy;

// Outgoing call from hand-written code, through the family's path (so the check sees it).
// Integers go to x0.., floats to v0..; x0 / s0 come back.
struct ACall {
    A64 r;
    int ni = 0, nf = 0;
    Family* fam;
    explicit ACall(Family& f);
    ACall& i(u64 v) {
        r.x[ni++] = v;
        return *this;
    }
    ACall& f(float v) {
        r.v[nf++].f[0] = v;
        return *this;
    }
    u64 call(u64 target);
    // A call whose x8 (set by the caller in r.x[8]) is an sret buffer in the caller's frame.
    u64 call_sret(u64 target);
    float fcall(u64 target) {
        call(target);
        return r.v[0].f[0];
    }
    // A tail call: the callee's result registers (x0, x1, v0-v3) become the caller's.
    void tail(Cpu& c, u64 target);
};

inline V4 to_v4(V128 q) {
    V4 v;
    std::memcpy(&v.f[0], &q.lo, 8);
    std::memcpy(&v.f[2], &q.hi, 8);
    return v;
}
inline V128 to_v128(const V4& v) {
    V128 q;
    std::memcpy(&q.lo, &v.f[0], 8);
    std::memcpy(&q.hi, &v.f[2], 8);
    return q;
}

}  // namespace soa::live
