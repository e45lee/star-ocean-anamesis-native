#pragma once
// The shared live differential check ("live check") of native families: one harness for every
// family that checks its natives against the guest originals in a normal run.
//
// The kinds of check that use it:
//
// 1. Record / replay (Family::add; the leaf families of live_leaf.h: hash, math, containers, libcxx,
//    data_formats). A checked call runs the native first, for real, with every outgoing call recorded
//    (calls from readable natives go through live::ACall / live::out_call, live_call.h: target,
//    argument registers, results, the snapshot regions after it, stack buffers the callee wrote).
//    Then the regions are put back and the guest original (the hook's trampoline) runs with every
//    recorded callee replaced by a replay stub (guest_stub.h) that checks target and arguments and
//    plays back the recorded effects. Call sequence, region bytes and x0 / v0 must match; side effects
//    happen once (in the native run). The rules the replay follows are at the top of live_check.cpp.
// 2. The other kinds use the switches below (and some the stubs, ReplaySession, guest_call_at_sp):
//    shadow checks (shadow_check.h: sync, input, kernel, resource, scene, restore), lockstep shadow
//    runs (lockstep.h: lib_crypto, lib_jpeg, lib_vorbis, lib_zlib, lib_zstd), run-both checks
//    (live_run_both.h: render, params) and the families with checks of their own on a plain
//    live::Family (memory, lib_sqlite, yayoi_sqlite).
//
// Switched on per family from the command line (soa --live-check, parse_live_check below):
//   --live-check FAMILY[,FAMILY..][:KEY[=VALUE]..]   (repeatable; FAMILY = the family's tag)
// keys: every=N (every n-th call per function; default the family's), budget=N (checks per
// function at most), out=FILE (per-function counts), only=SUB[|SUB..] (check only functions whose
// symbol contains one of these: the others run natively without a check, so the chosen ones are
// checked also where they are nested callees of other natives), trace, dump (debugging). E.g.
// --live-check math:every=4:only=Matrix. An unknown family fails at start (apply_live_check).
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
#include "native/common/guest_stub.h"

namespace soa::live {

// The register file of an outgoing call from a native (ACall): the AAPCS64 argument and result
// registers and the caller's SP.
struct V4 {
    float f[4];
};
struct Regs {
    u64 x[9];  // x0-x7 the integer arguments, x8 the indirect-result pointer; x0 / x1 come back
    u64 sp;    // the caller's SP: stack arguments are above it
    V4 v[8];   // v0-v7 (the low 128 bits); v0-v3 come back
};

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

// ---- the record / replay families ----

enum RetKind : u8 { kVoid = 0, kInt = 1, kFloat = 2, kAll = 3 };

struct Entry;

// A family: its switches and the rules only it knows. The rules about callees (blocks they free,
// objects they return, out-parameters they write whole) are shared (live_check.cpp).
class Family {
public:
    // tag: log tag (I/<tag>_check), registration label and --live-check name ("math");
    // every: the default of --live-check's every=.
    Family(const char* tag, int every);
    virtual ~Family() = default;

    const char* tag;
    std::string log_tag;  // "<tag>_check"
    std::atomic<bool> on{false};  // --live-check <tag> (a test may switch it at run time)
    int every;
    int budget = 0;  // checks per function at most (0: no limit)
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

    // Registers the native `run` at `sym`, hooked through the check when the family is on.
    // obj_bytes: the object at x0 the check snapshots and compares (0: none); ret: the result
    // registers compared; `enabled`: its install switch (nullptr: always); `label`: the registry's
    // description; `file`: the registering source (its subsystem: --natives-skip; the caller's).
    int add(const char* sym, HostFn run, u32 obj_bytes, RetKind ret, bool (*enabled)(), const char* label,
            const char* file = __builtin_FILE());

    // An outgoing call of the family's natives (ACall::call): recorded inside a check, else a plain
    // guest call (a replaced callee's host function directly). Only x0..x(ni-1) and v0..v(nf-1) are
    // arguments; the replay compares only those.
    void gcall(Regs& r, u64 target, int ni, int nf);

    void summary(FILE* f);  // per-function counts
    void summary_file();    // to out_path

    struct Stats {
        std::atomic<u64> checks{0}, ok{0}, bad{0}, skipped{0}, races{0};
    } stats;
    std::vector<int> entries;
};

struct Entry {
    Family* fam = nullptr;
    const char* sym = nullptr;
    HostFn run = nullptr;  // the native
    u32 obj_bytes = 0;
    RetKind ret = kAll;
    u64 orig = 0;  // trampoline to the guest original (set when installed)
    std::atomic<u64> calls{0}, checks{0}, ok{0}, bad{0}, skipped{0}, races{0};
};

Entry& entry(int n);  // (an index Family::add returned)
// The entry registered at `sym` by Family::add (nullptr when none; test native/direct-callees).
const Entry* entry_for(const char* sym);
// True when --live-check switched any family on (install_native_functions: native_call.h's direct
// calls are off then).
bool any_family_on();

// Inside a check on this thread (no other call can be checked; every family).
extern thread_local bool t_busy;

// An outgoing call from a native, through the family's path (so the check sees it).
// Integers go to x0.., floats to v0..; x0 / s0 come back.
struct ACall {
    Regs r;
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
