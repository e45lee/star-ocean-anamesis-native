// The shared live differential check (live_check.h): switches, the stub registry, and the
// record / replay check of the A64 families.
//
// Record / replay, the rules (collected from the family copies this replaces: arena_rt.cpp,
// objbase_rt.cpp, battle_charobj_check.cpp, battle_core_check.cpp):
//   - A call's target is where it lands: PLT entries resolved, lone-B functions (4-byte tail
//     branches, too small to stub) followed (PLT -> B -> PLT). A lone RET isn't recorded.
//   - Stubs are process-wide (ensure_stub) and each thread's JIT levels drop the unpatched code
//     once (drop_stale_code), at the callee and where the call went in (the PLT entry, lone B or
//     vtable entry); a stub another stubber renamed is re-applied. A callee that can't be stubbed
//     (an unrelocatable prologue, a family's test-hooked function) is stubbed at the PLT entry
//     the call went through.
//   - Arguments (x0-x8) pointing into the caller's frame (at or above the entry SP) are snapshot
//     regions of kBuf bytes: e.g. GetSceneObjectSphereList's TArray, which a callee
//     (ForceRealloc) filled in the native run; the replay started from the filled array, skipped
//     the call, and ran into unrecorded calls.
//   - The original runs at the native run's entry SP, with the kFrameSnap bytes below it as the
//     native run found them: stack arguments are in place, and slots neither run writes hold the
//     same leftovers (dead registers passed to callees compare equal).
//   - The replay's stub session never has an empty `only` (ReplaySession).
//   - A check's callees run unchecked (t_busy, every family): a transcribed callee then runs
//     directly instead of through a JIT level of its own.
//   - The replay starts from the memory the native run saw: the undo log of the transcribed
//     body's own stores (a callee's later write to one comes back as a patch at its call), the
//     blocks the native run freed (operator delete / delete[], the STL allocator's Free, deleting
//     destructors: the vtable the caller dispatched through), the
//     objects callees returned (pObjectRoot), the elements of stack vectors a callee filled, and
//     the snapshot regions. Only the bytes the replays changed are written back afterwards.
//   - Stack buffers passed to a callee (x0-x8 within the frame): the bytes the callee changed are
//     replayed (whole changed 8-byte words). An sret buffer: marked by the generator (gcall_sret)
//     it is pattern-filled before the call, so written bytes are seen even where they equal what
//     the frame held; unmarked (families without marks) an 8-aligned stack x8 counts as one and
//     its first 16 bytes are always replayed. Out-parameters written whole (FindIntersectObject's
//     info) are always replayed.
//   - Blocks a callee allocates (operator new / new[]: the requested size, up to
//     kMaxFresh) are snapshotted after every later call and written back at the replay's same
//     call: later callees initialise them (a constructor, AsfHandler::CreateTree) and the body
//     reads them, so the replay must not see the native run's final bytes (CThingObject::
//     ProgressInitialize_Asf read the finished tree's node count, took the DeleteTreeEx branch
//     for real and left the handler without a tree: the SOA_OBJBASE_ALL home crash). Their
//     bytes after the replay must match the native run's.
//   - memset / memcpy / memmove of a transcribed body are recorded as calls and done again on the
//     replay.
//   - A check records at most kMaxRecord bytes of snapshots (else skipped), and a replay that runs
//     past its record is stopped after kRunaway extra calls.
//   - A replay rewinds memory other threads can see (the snapshot regions, freed blocks) until
//     the check puts the native run's state back: a mismatch whose native run overlapped another
//     thread's replay counts as a race, not a mismatch.
//   - A stack-vector guess (a callee-filled {begin, end, cap} in a stack buffer) needs aligned,
//     mapped pointers (a buffer of floats can look like one), and so does a freed block's copy.
//   - A mismatch of a hand-written function that made no calls is rerun (the native again, its
//     calls answered from the record, then the original): if it doesn't reproduce, another thread
//     wrote its inputs in between and it counts as a race.
#include "native/common/live_check.h"

#ifndef _WIN32
#include <sys/mman.h>
#endif
#include <unistd.h>

#include <algorithm>
#include <chrono>
#include <condition_variable>
#include <cstdlib>
#include <ctime>
#include <set>
#include <thread>

#include "core/host_mem.h"
#include "core/loader.h"
#include "core/log.h"
#include "native/common/guest_std.h"
#include "native/common/native.h"
#include "native/common/test.h"

namespace soa::live {
using native::StubSession;
using native::stub_at;

// ---- switches ----

namespace {
std::mutex g_check_m;
std::map<std::string, CheckOptions>& check_table() {  // --live-check, by family tag
    static std::map<std::string, CheckOptions> t;
    return t;
}
std::vector<Family*>& families() {  // every constructed family
    static std::vector<Family*> v;
    return v;
}
std::vector<std::string> split(const std::string& s, char sep) {
    std::vector<std::string> out;
    for (size_t p = 0; p <= s.size();) {
        size_t q = s.find(sep, p);
        if (q == std::string::npos) q = s.size();
        if (q > p) out.push_back(s.substr(p, q - p));
        p = q + 1;
    }
    return out;
}
bool whole(const std::string& v, int lo, int* out) {
    char* end = nullptr;
    long n = strtol(v.c_str(), &end, 10);
    if (v.empty() || *end || n < lo || n > 1000000000) return false;
    *out = (int)n;
    return true;
}
}  // namespace

bool parse_live_check(const std::string& spec, std::string* err) {
    auto parts = split(spec, ':');
    if (spec.empty() || spec[0] == ':' || parts.empty()) return *err = "expected FAMILY[,FAMILY..][:KEY[=VALUE]..]", false;
    CheckOptions o;
    for (size_t k = 1; k < parts.size(); k++) {
        const std::string& kv = parts[k];
        size_t eq = kv.find('=');
        std::string key = kv.substr(0, eq), val = eq == std::string::npos ? "" : kv.substr(eq + 1);
        bool has = eq != std::string::npos;
        if (key == "every" && has && whole(val, 1, &o.every)) continue;
        if (key == "budget" && has && whole(val, 1, &o.budget)) continue;
        if (key == "out" && has && !val.empty()) {
            o.out = val;
            continue;
        }
        if (key == "only" && has && !(o.only = split(val, '|')).empty()) continue;
        if (key == "trace" && !has) {
            o.trace = true;
            continue;
        }
        if (key == "dump" && !has) {
            o.dump = true;
            continue;
        }
        return *err = "\"" + kv + "\": expected every=N, budget=N, out=FILE, only=SUB[|SUB..], trace or dump", false;
    }
    std::lock_guard lk(g_check_m);
    for (auto& fam : split(parts[0], ',')) check_table()[fam] = o;
    return true;
}

bool apply_live_check(std::string* err) {
    std::lock_guard lk(g_check_m);
    for (auto& [name, o] : check_table()) {
        Family* f = nullptr;
        for (Family* g : families())
            if (name == g->tag) f = g;
        if (!f) {
            std::string have;
            for (Family* g : families()) have += (have.empty() ? "" : ", ") + std::string(g->tag);
            *err = "no family \"" + name + "\" (registered: " + (have.empty() ? "none" : have) + ")";
            return false;
        }
        if (o.every) f->every = o.every;
        f->budget = o.budget;
        f->out_path = o.out;
        f->only.subs = o.only;
        f->trace = o.trace, f->dump = o.dump;
        f->on = true;
    }
    return true;
}
bool Only::match(const char* sym) const {
    if (subs.empty()) return true;
    for (auto& s : subs)
        if (strstr(sym, s.c_str())) return true;
    return false;
}

// ---- callees ----

namespace {
template <typename T>
T ld(u64 a) {
    T v;
    std::memcpy(&v, (const void*)a, sizeof(T));
    return v;
}
}  // namespace

u64 resolve_plt(u64 a) {
    const u32* p = (const u32*)a;
    if ((p[0] & 0x9f00001f) != 0x90000010 || (p[1] & 0xffc003ff) != 0xf9400211 || p[3] != 0xd61f0220) return a;
    u64 immlo = (p[0] >> 29) & 3, immhi = (p[0] >> 5) & 0x7ffff;
    s64 off = (s64)(((immhi << 2) | immlo) << 43) >> 31;  // sign-extended imm21 << 12
    u64 page = (a & ~0xfffull) + off;
    u64 slot = page + (((p[1] >> 10) & 0xfff) << 3);
    return ld<u64>(slot);
}
u64 follow_b(u64 a) {
    u32 i = ld<u32>(a);
    if ((i & 0xfc000000u) != 0x14000000u) return a;
    return a + (u64)(s64)((s32)(i << 6) >> 4);
}
u64 callee(u64 target) {
    u64 a = resolve_plt(target);
    for (int hop = 0; hop < 4; hop++) {
        u64 b = follow_b(a);
        if (b == a) break;
        a = resolve_plt(b);
    }
    return a;
}
bool is_ret_only(u64 a) { return ld<u32>(a) == 0xd65f03c0u; }

// ---- stubs ----

namespace {
std::mutex g_stub_mu;
std::map<u64, std::string>& stub_names() {  // stubbed address -> stub name ("" = can't)
    static std::map<u64, std::string> m;
    return m;
}
}  // namespace

const char* ensure_stub(u64 target) {
    std::lock_guard lk(g_stub_mu);
    auto& names = stub_names();
    auto it = names.find(target);
    if (it != names.end()) {
        if (it->second.empty()) return nullptr;
        // (another stubber, e.g. a test, may have renamed it: stub it under ours again)
        if (native::stub_name(target) != it->second) stub_at(target, it->second.c_str(), 0, 0);
        return it->second.c_str();
    }
    char b[48];
    u64 base = main_lib()->base;
    if (target >= base && target < base + 0x4000000) snprintf(b, sizeof b, "live:%llx", (unsigned long long)(target - base));
    else snprintf(b, sizeof b, "live:@%llx", (unsigned long long)target);
    std::string name = b;
    if (!stub_at(target, strdup(name.c_str()), 0, 0)) name.clear();
    auto& slot = names[target];
    slot = name;
    return slot.empty() ? nullptr : slot.c_str();
}

void drop_stale_code(u64 target) {
    thread_local std::unordered_map<u64, size_t> t_dropped;  // target -> lowest level dropped
    size_t d = guest_depth_this_thread();
    auto [it, fresh] = t_dropped.try_emplace(target, d);
    if (fresh || d < it->second) {
        invalidate_guest_code_this_thread(target, 8);
        it->second = d;
    }
}

void stop_runaway(Cpu& c) { c.set_x(30, host_return_addr()); }

GuestResult guest_call_at_sp(u64 fn, const u64* x, const void* v, u64 x8, u64 sp) {
    Cpu* c = current_cpu();
    u64 saved = c->sp();
    c->set_sp((sp & ~15ull) + 512);
    V128 vecs[8];
    std::memcpy(vecs, v, sizeof vecs);
    GuestResult g = guest_call_raw(fn, x, 8, vecs, 8, x8);
    c->set_sp(saved);
    return g;
}

// ---- memory ----

std::vector<u8> Regions::capture() const {
    std::vector<u8> b;
    size_t n = 0;
    for (auto& p : r) n += p.second;
    b.reserve(n);
    for (auto& [a, n1] : r) b.insert(b.end(), (const u8*)a, (const u8*)a + n1);
    return b;
}
void Regions::restore(const std::vector<u8>& b) const {
    size_t o = 0;
    for (auto& [a, n] : r) memcpy((void*)a, b.data() + o, n), o += n;
}
void Regions::restore_diff(const std::vector<u8>& now, const std::vector<u8>& want) const {
    size_t o = 0;
    for (auto& [a, n] : r) {
        for (u32 j = 0; j < n; j++)
            if (now[o + j] != want[o + j]) ((u8*)a)[j] = want[o + j];
        o += n;
    }
}
std::string Regions::where(size_t k) const {
    char b[64];
    for (size_t i = 0; i < r.size(); i++) {
        if (k < r[i].second) {
            snprintf(b, sizeof b, "%s +0x%zx", i == 0 ? "object" : "global", k);
            return b;
        }
        k -= r[i].second;
    }
    return "?";
}

void Journal::write(u64 a, const std::vector<u8>& v) {
    w.push_back({a, std::vector<u8>((u8*)a, (u8*)a + v.size())});
    memcpy((void*)a, v.data(), v.size());
}
void Journal::undo() {
    for (size_t q = w.size(); q-- > 0;) memcpy((void*)w[q].first, w[q].second.data(), w[q].second.size());
    w.clear();
}

// ---- the record / replay (A64) families ----

namespace {

constexpr int kMax = 768;
Entry g_entries[kMax];
int g_n = 0;

void check(Cpu& c, int i);
template <int I>
void hook(Cpu& c) {
    Entry& e = g_entries[I];
    if (!e.fam->on.load(std::memory_order_relaxed)) return e.run_unchecked(c);
    check(c, I);
}
template <int... I>
constexpr HostFn hook_at(int i, std::integer_sequence<int, I...>) {
    constexpr HostFn t[] = {hook<I>...};
    return t[i];
}

// A deleting destructor (D0: the object's own delete). The caller read the object's vtable to
// call it (a virtual delete, e.g. CArena::Progress_Release's loop over its objects), so the
// replay reads it again after the native run freed (and maybe reused) the block.
bool is_deleting_dtor(u64 target) {
    thread_local std::unordered_map<u64, bool> cache;
    auto it = cache.find(target);
    if (it != cache.end()) return it->second;
    const LoadedLib& lib = *main_lib();
    auto s = std::lower_bound(lib.sorted_syms.begin(), lib.sorted_syms.end(), target, [](const LoadedLib::Sym& y, u64 a) { return y.addr < a; });
    bool d0 = false;
    for (; s != lib.sorted_syms.end() && s->addr == target; ++s) {
        size_t n = strlen(s->name);
        d0 |= n > 4 && !strcmp(s->name + n - 4, "D0Ev");
    }
    return cache[target] = d0;
}

// Callees that free a block: operator delete / delete[] (the Aska memory manager's blocks), the
// STL allocator's static Free (fixed-length pool blocks) and deleting destructors (as much as
// operator delete: the caller may have read more than the vtable, e.g. PlayAnimation compares
// AafBlendManager's count at +0x28 before deleting it, and the native run's new manager reuses
// the block): the bytes kept from the block's start (0 = not one).
u32 freed_bytes(u64 target) {
    static const u64 dl = guest::sym("_ZdlPv"), da = guest::sym("_ZdaPv"), fr = guest::sym("_ZN9Framework37CAssignedMemoryManagerForSTLAllocator4FreeEPv");
    if (target == dl || target == da) return 0x100;
    if (target == fr) return 0x80;
    if (is_deleting_dtor(target)) return 0x100;
    return 0;
}

// Allocating callees (operator new / new[]; guest malloc is an HLE import): the requested size (x0 at the call) is the block the result points to.
bool is_alloc(u64 target) {
    static const std::vector<u64> t = [] {
        std::vector<u64> r;
        for (const char* sym : {"_Znwm", "_Znam", "_ZnwmRKSt9nothrow_t", "_ZnamRKSt9nothrow_t"})
            if (u64 a = main_lib()->sym(sym)) r.push_back(callee(a));
        return r;
    }();
    return std::find(t.begin(), t.end(), target) != t.end();
}
constexpr u64 kMaxFresh = 0x10000;  // (larger blocks aren't tracked)

// Callees whose result is an object the caller then reads: (symbol, bytes).
u32 ret_object_bytes(u64 target) {
    static const std::vector<std::pair<u64, u32>> t = [] {
        std::vector<std::pair<u64, u32>> r;
        for (auto [sym, n] : std::initializer_list<std::pair<const char*, u32>>{{"_ZN9Framework15CAnimationModel11pObjectRootEv", 0x130}})
            if (u64 a = guest::sym(sym)) r.push_back({a, n});
        return r;
    }();
    for (auto& [a, n] : t)
        if (a == target) return n;
    return 0;
}

// Out-parameters written whole, whatever the frame held before: (callee, argument register,
// bytes). A word the callee stores unchanged from what the recording frame held (e.g. the same
// object pointer a previous call left there) otherwise looks untouched and isn't replayed.
u32 out_param_bytes(u64 target, int reg) {
    // (Aska::Collision::FindIntersectObject(handler, u16, shape, CollisionIntersectInfoOne*): the
    // info, whose +0x18 is the object hit)
    static const std::vector<u64> fio = [] {
        std::vector<u64> r;
        for (const char* sym : {"_ZN4Aska9Collision19FindIntersectObjectEPKNS_16CollisionHandlerEtPKNS_3BoxEPNS_25CollisionIntersectInfoOneE",
                                "_ZN4Aska9Collision19FindIntersectObjectEPKNS_16CollisionHandlerEtPKNS_3RayEPNS_25CollisionIntersectInfoOneE",
                                "_ZN4Aska9Collision19FindIntersectObjectEPKNS_16CollisionHandlerEtPKNS_4LineEPNS_25CollisionIntersectInfoOneE",
                                "_ZN4Aska9Collision19FindIntersectObjectEPKNS_16CollisionHandlerEtPKNS_6VectorEPNS_25CollisionIntersectInfoOneE",
                                "_ZN4Aska9Collision19FindIntersectObjectEPKNS_16CollisionHandlerEtPKNS_7SegmentEfPNS_25CollisionIntersectInfoOneE"})
            if (u64 a = guest::sym(sym)) r.push_back(a);
        return r;
    }();
    if (reg == 3)
        for (u64 a : fio)
            if (a == target) return 0x20;
    return 0;
}

struct Call {
    u64 target = 0;  // where the replay stub sits (callee())
    u64 via = 0;     // the address called (a PLT entry, a lone-B function, a vtable's entry)
    u64 lands = 0;   // where it landed (callee(); `target` may become `via` when that can't be stubbed)
    u64 sp = 0;
    u64 x[9] = {};
    u64 vlo[4] = {};
    int ni = 8, nf = 4;  // argument registers that compare
    int memop = 0;       // memop's kind (1 memset, 2 memcpy, 3 memmove), else 0
    u64 rx0 = 0, rx1 = 0;
    V4 rv[4] = {};
    std::vector<u8> obj_after;  // the regions after the call
    // the blocks callees allocated so far in this check (Recorder::fresh), after the call
    std::vector<u8> fresh_after;
    size_t nfresh = 0;
    // stack buffers (in the caller's frame) the callee changed: (argument register, bytes before,
    // bytes after); the replay writes back only the bytes that changed
    struct Buf {
        int reg;
        std::vector<u8> before, after;
        u32 always = 0;      // leading bytes replayed even if unchanged (out_param_bytes)
        bool x8_head = false;  // an unmarked sret guess: the first 16 bytes (at an aligned x8) always
    };
    std::vector<Buf> bufs;
    // memory the checked body stored to (undo log) that the callee then changed, or the elements
    // of a stack vector it filled: (address, bytes after, size), written again by the replay
    struct Patch {
        u64 a, v;
        u32 n;
    };
    std::vector<Patch> patches;
    // the object the callee returned (x0), as the caller saw it right after the call, for the
    // callees of ret_object_bytes(): a later callee may change it before the replay reads it
    std::vector<u8> ret_obj;
    // a block the callee frees (freed_bytes()): its bytes before the call; the native run may
    // reuse the memory before the replay reads the block
    u64 freed_at = 0;
    std::vector<u8> freed;
};

struct Recorder {
    Family* fam = nullptr;
    const Regions* regions = nullptr;
    std::vector<Call> calls;
    u64 sp0 = 0;  // the checked call's SP
    std::vector<std::pair<u64, u32>> stored;  // the addresses the body stored to (undo log), once each
    std::unordered_map<u64, size_t> stored_at;
    size_t bytes = 0;  // snapshot bytes so far; past kMaxRecord the call isn't replayed (skipped)
    bool overflow = false;
    // Blocks allocated by callees (operator new / new[], their requested size): the
    // callees after it initialise them (a constructor, AsfHandler::CreateTree) and the body reads
    // them, so the replay gets their bytes back at each call as the native run left them.
    Regions fresh;
    void keep(Call& k) {
        bytes += k.obj_after.size() + k.fresh_after.size();
        for (auto& b : k.bufs) bytes += 2 * b.after.size();
        if (bytes > kMaxRecord) overflow = true;
        if (!overflow) calls.push_back(std::move(k));
    }
};
// Arity of the call ACall is making (hand-written code passes only its arguments; the rest of
// the registers are don't-care): -1 = a transcribed body's call (all registers compare).
thread_local int t_ni = -1, t_nf = -1;
thread_local Recorder* t_rec = nullptr;
thread_local bool t_sret = false;  // the call being made has an sret buffer at x8 (marked)
thread_local StoreLog* t_undo = nullptr;
constexpr size_t kMaxUndo = 1 << 16;
// The confirm rerun of a mismatch (check()): the native code runs again with every outgoing call
// answered from the first run's record instead of executing (no side effects twice).
struct Player {
    Recorder* rec = nullptr;
    Journal* journal = nullptr;
    size_t next = 0;
    bool bad = false;  // a call that doesn't match the record (target or arguments)
};
thread_local Player* t_play = nullptr;
struct PlayDiverged {};

// Guest call through the JIT (never a direct host call: the replay stubs need the guest PC).
void gcall_jit(A64& r, u64 target) {
    GuestResult g = a2c_guest_call(target, r.x, r.v, r.x[31]);
    r.x[0] = g.x0;
    r.x[1] = g.x1;
    r.v[0] = to_v4(g.v0);
    r.v[1] = to_v4(g.v1);
    r.v[2] = to_v4(g.v2);
    r.v[3] = to_v4(g.v3);
}

// Write back the bytes of a recorded stack buffer that the callee changed (whole 8-byte words
// that changed: a pointer the callee stored may share its high bytes with what the recording
// frame held before, but not with this one).
void write_back(const Call::Buf& bf, u64 dst) {
    for (size_t j = 0; j < bf.after.size(); j++) {
        size_t w = ((dst + j) & ~7ull) - dst;
        bool changed = (bf.x8_head && !(dst & 7) && j < 16) || j < bf.always;
        for (size_t q = w; q < w + 8; q++)
            if (q < bf.after.size() && bf.after[q] != bf.before[q]) changed = true;
        if (changed) ((u8*)dst)[j] = bf.after[j];
    }
}

void do_memop(int kind, u64 d, u64 src_or_val, u64 n) {
    if (kind == 1) memset((void*)d, (int)(u32)src_or_val, n);
    else if (kind == 2) memcpy((void*)d, (const void*)src_or_val, n);
    else memmove((void*)d, (const void*)src_or_val, n);
}

void play_call(A64& r, u64 target, int memop) {
    Player* p = t_play;
    u64 at = callee(target);
    t_ni = t_nf = -1;
    t_sret = false;
    if (!memop && is_ret_only(at)) return;
    // (a call off the record: the native code took another path, so its inputs changed; its
    // results can't be made up, so the rerun stops here)
    if (p->next >= p->rec->calls.size()) throw PlayDiverged{};
    Call& k = p->rec->calls[p->next++];
    if (k.target != at || k.memop != memop) throw PlayDiverged{};
    for (int a = 0; a < k.ni; a++)
        if (r.x[a] != k.x[a]) p->bad = true;  // (same frames as the recording run)
    for (int a = 0; a < k.nf; a++) {
        u64 lo;
        memcpy(&lo, &r.v[a], 8);
        if (k.ni < 8 ? (u32)lo != (u32)k.vlo[a] : lo != k.vlo[a]) p->bad = true;
    }
    if (memop) {
        u64 d = r.x[0];
        if (d >= r.x[31] && in_stack(d, r.x[31])) {
            if (memop == 1) memset((void*)d, (int)(u32)r.x[1], r.x[2]);
            else memmove((void*)d, (const void*)r.x[1], r.x[2]);
        }
        p->rec->regions->restore(k.obj_after);
        return;  // (x0 stays the destination)
    }
    for (auto& bf : k.bufs)
        if (r.x[bf.reg] >= r.x[31] && in_stack(r.x[bf.reg], r.x[31])) write_back(bf, r.x[bf.reg]);
    for (auto& pt : k.patches) memcpy((void*)pt.a, &pt.v, pt.n);
    if (!k.ret_obj.empty()) p->journal->write(k.rx0, k.ret_obj);
    p->rec->regions->restore(k.obj_after);
    r.x[0] = k.rx0, r.x[1] = k.rx1;
    for (int a = 0; a < 4; a++) r.v[a] = k.rv[a];
}

// [a, a + n) is mapped memory (the stack-vector guess below also matches buffers of floats: e.g. a
// CVector (0.707, 0) reads as the "pointer" 0x3f34fe8a).
bool mapped(u64 a, u64 n) { return hostmem::mapped((const void*)a, n); }

// Where a call through a PLT entry that has been stubbed itself (check(): the callee couldn't be)
// lands: callee() no longer recognises the patched entry.
std::mutex g_plt_mu;
std::unordered_map<u64, u64> g_plt_lands;
u64 lands_of(u64 target, u64 resolved) {
    if (resolved != target) return resolved;
    std::lock_guard lk(g_plt_mu);
    auto it = g_plt_lands.find(target);
    return it != g_plt_lands.end() ? it->second : resolved;
}

void record_call(A64& r, u64 target) {
    Recorder* rec = t_rec;
    Call k;
    k.target = callee(target);
    k.lands = lands_of(target, k.target);
    k.via = target;
    if (t_ni >= 0) k.ni = t_ni, k.nf = t_nf;
    t_ni = t_nf = -1;
    bool marked = t_sret;
    t_sret = false;
    if (is_ret_only(k.target)) return;  // a lone RET (e.g. CCharacterObject::pCharacterObject): nothing to replay
    k.sp = r.x[31];
    for (int i = 0; i < 9; i++) k.x[i] = r.x[i];
    for (int i = 0; i < 4; i++) memcpy(&k.vlo[i], &r.v[i], 8);
    std::vector<std::pair<int, std::vector<u8>>> before;
    for (int i = 0; i < 9; i++)
        if (r.x[i] >= r.x[31] && in_stack(r.x[i], r.x[31])) before.push_back({i, std::vector<u8>((u8*)r.x[i], (u8*)r.x[i] + kBuf)});
    if (u32 fb = freed_bytes(k.target); fb && r.x[0] >= 0x100000 && !in_stack(r.x[0], r.x[31]) && mapped(r.x[0], fb)) {
        k.freed_at = r.x[0];
        k.freed.assign((u8*)k.freed_at, (u8*)k.freed_at + fb);
    }
    // A marked sret buffer (x8) is output only: fill it with a pattern so bytes the callee writes
    // are seen even where they equal what the native frame held (a position that didn't change
    // since this frame's previous use would otherwise not be replayed into the guest frame, which
    // holds other bytes). Only up to the next argument pointing into the window (the callee reads
    // that one; an sret slot is a fresh temporary, so no argument aliases its start).
    constexpr u8 kPat = 0xa5;
    std::vector<u8> sret_orig;
    bool sret = marked && r.x[8] >= r.x[31] && in_stack(r.x[8], r.x[31]);
    u64 fill = kBuf;
    for (int i = 0; i < 8 && sret; i++)
        if (r.x[i] > r.x[8] && r.x[i] < r.x[8] + fill) fill = r.x[i] - r.x[8];
    if (rec->fam->trace && sret) LOGI(rec->fam->log_tag.c_str(), "sret call %llx fill %llu", (unsigned long long)(target - main_lib()->base), (unsigned long long)fill);
    if (sret && fill) {
        sret_orig.assign((u8*)r.x[8], (u8*)r.x[8] + kBuf);
        memset((void*)r.x[8], kPat, fill);
    }
    t_rec = nullptr;  // the callee's own calls (and stores) aren't part of this record
    bool undo_on = t_undo_on;
    t_undo_on = false;
    std::vector<u64> stored_before(rec->stored.size());
    for (size_t q = 0; q < rec->stored.size(); q++) memcpy(&stored_before[q], (const void*)rec->stored[q].first, rec->stored[q].second);
    gcall_jit(r, target);
    for (size_t q = 0; q < rec->stored.size(); q++)
        if (memcmp(&stored_before[q], (const void*)rec->stored[q].first, rec->stored[q].second)) {
            Call::Patch pt{rec->stored[q].first, 0, rec->stored[q].second};
            memcpy(&pt.v, (const void*)pt.a, pt.n);
            k.patches.push_back(pt);
        }
    t_undo_on = undo_on;
    t_rec = rec;
    k.rx0 = r.x[0], k.rx1 = r.x[1];
    for (int i = 0; i < 4; i++) k.rv[i] = r.v[i];
    if (u32 n = ret_object_bytes(k.target); n && k.rx0 >= 0x100000) k.ret_obj.assign((u8*)k.rx0, (u8*)k.rx0 + n);
    k.obj_after = rec->regions->capture();
    if (is_alloc(k.target) && k.rx0 >= 0x100000 && k.x[0] && k.x[0] <= kMaxFresh) rec->fresh.add(k.rx0, (u32)k.x[0]);
    k.nfresh = rec->fresh.r.size();
    if (k.nfresh) k.fresh_after = rec->fresh.capture();
    if (!sret_orig.empty()) {
        u8* p = (u8*)k.x[8];
        std::vector<u8> mark(kBuf);  // as "before": differs from "after" exactly where written
        for (u64 j = 0; j < kBuf; j++) {
            bool written = j < fill ? p[j] != kPat : p[j] != sret_orig[j];
            if (!written) p[j] = sret_orig[j];
            mark[j] = written ? (u8)~p[j] : p[j];
        }
        for (auto& [reg, b] : before)
            if (reg == 8) b = mark;
    }
    bool guess_x8 = !rec->fam->sret_marked;
    for (auto& [reg, b] : before) {
        u32 always = out_param_bytes(k.target, reg);
        bool x8_head = guess_x8 && reg == 8 && !(k.x[8] & 7);
        if (x8_head || always || memcmp(b.data(), (void*)k.x[reg], kBuf))
            k.bufs.push_back({reg, b, std::vector<u8>((u8*)k.x[reg], (u8*)k.x[reg] + kBuf), always, x8_head});
    }
    // A stack vector the callee filled (e.g. DetectCollidablesByShapeFilter's result): its
    // elements too, as the callee left them (the native run may free and reuse the buffer before
    // the replay reads it).
    for (auto& bf : k.bufs) {
        u64 b, e, cap;
        memcpy(&b, bf.after.data(), 8), memcpy(&e, bf.after.data() + 8, 8), memcpy(&cap, bf.after.data() + 16, 8);
        if (b < 0x100000 || ((b | e | cap) & 3) || b > e || e > cap || e - b > 0x10000 || in_stack(b, k.sp) || !mapped(b, e - b)) continue;
        for (u64 o = 0; o < e - b; o += 8) {
            Call::Patch pt{b + o, 0, (u32)std::min<u64>(8, e - b - o)};
            memcpy(&pt.v, (const void*)pt.a, pt.n);
            k.patches.push_back(pt);
        }
    }
    rec->keep(k);
}

}  // namespace

thread_local bool t_undo_on = false;
thread_local bool t_busy = false;

// ---- the Aska random state pin (live_check.h) ----
std::atomic<int> g_rand_pin{0};
namespace {
std::atomic<u64> g_rand_violations{0};
std::mutex g_pin_m;
std::condition_variable g_pin_cv;
thread_local int t_pin_depth = 0;
int my_tid() {
    static thread_local const int tid = (int)gettid();
    return tid;
}
}  // namespace
std::atomic<int> g_rand_inflight{0};
std::atomic<bool> g_rand_tracking{false};
void rand_tracking_on() { g_rand_tracking.store(true); }
bool RandDraw::rand_gate_pinned_by_me() { return g_rand_pin.load(std::memory_order_acquire) == my_tid(); }
bool RandDraw::rand_gate_wait() {
    std::unique_lock lk(g_pin_m);
    if (g_pin_cv.wait_for(lk, std::chrono::milliseconds(kPinWaitMs), [] { return g_rand_pin.load(std::memory_order_acquire) == 0; })) return true;
    g_rand_violations.fetch_add(1);
    return false;
}
u64 rand_violations() { return g_rand_violations.load(); }
RandPin::RandPin() {
    if (t_pin_depth++) return;
    const int me = my_tid();
    // (one pinning thread at a time: a second one waits like any other draw would, then pins)
    for (;;) {
        int z = 0;
        if (g_rand_pin.compare_exchange_strong(z, me, std::memory_order_acq_rel)) break;
        std::unique_lock lk(g_pin_m);
        g_pin_cv.wait_for(lk, std::chrono::milliseconds(kPinWaitMs), [] { return g_rand_pin.load(std::memory_order_acquire) == 0; });
    }
    // Draws that passed the gate before the pin finish first (for at most kPinWaitMs: a draw still
    // running then is a violation the check sees).
    const auto t0 = std::chrono::steady_clock::now();
    while (g_rand_inflight.load(std::memory_order_acquire) != 0) {
        if (std::chrono::steady_clock::now() - t0 > std::chrono::milliseconds(kPinWaitMs)) {
            g_rand_violations.fetch_add(1);
            break;
        }
        std::this_thread::yield();
    }
}
RandPin::~RandPin() {
    if (--t_pin_depth) return;
    {
        std::lock_guard lk(g_pin_m);
        g_rand_pin.store(0, std::memory_order_release);
    }
    g_pin_cv.notify_all();
}

void undo_note(u64 a, u32 n) {
    StoreLog* u = t_undo;
    if (!u) return;
    if (u->v.size() >= kMaxUndo) {
        u->v.push_back({0, 0, 0});  // (overflow marker: the check is skipped)
        t_undo_on = false;
        return;
    }
    StoreLog::E k{a, 0, n};
    memcpy(&k.old, (const void*)a, n);
    u->v.push_back(k);
    // (not the body's own stack frame: the replay's frames overlap it; stack out-parameters go
    // through Call::bufs)
    if (Recorder* rec = t_rec; rec && !in_stack(a, rec->sp0)) {
        auto [it, fresh] = rec->stored_at.try_emplace(a, rec->stored.size());
        if (fresh) rec->stored.push_back({a, n});
        else if (rec->stored[it->second].second < n) rec->stored[it->second].second = n;
    }
}

Family::Family(const char* tag_, int every_, bool sret_marked_)
    : tag(tag_), log_tag(std::string(tag_) + "_check"), every(every_), sret_marked(sret_marked_) {
    std::lock_guard lk(g_check_m);
    families().push_back(this);  // (static families: --live-check switches them on, apply_live_check)
}

int Family::add(const char* sym, HostFn run, Body body, u32 obj_bytes, RetKind ret, bool (*enabled)(), const char* label) {
    if (g_n >= kMax) {
        LOGE("live_check", "%s: too many functions (kMax %d); %s left to the guest", tag, kMax, sym);
        return -1;
    }
    int n = g_n++;
    Entry& e = g_entries[n];
    e.fam = this, e.sym = sym, e.run = run, e.body = body, e.obj_bytes = obj_bytes, e.ret = ret;
    register_native_function({sym, hook_at(n, std::make_integer_sequence<int, kMax>{}), label, enabled, &e.orig});
    entries.push_back(n);
    return n;
}
int Family::add_test(const char* sym, Body body, u32 obj_bytes, RetKind ret, int user) {
    if (g_n >= kMax) {
        LOGE("live_check", "%s: too many functions (kMax %d); %s not checked", tag, kMax, sym);
        return -1;
    }
    int n = g_n++;
    Entry& e = g_entries[n];
    e.fam = this, e.sym = sym, e.body = body, e.obj_bytes = obj_bytes, e.ret = ret, e.test = true, e.user = user;
    register_test_hook({sym, hook_at(n, std::make_integer_sequence<int, kMax>{}), &e.orig, true});
    entries.push_back(n);
    return n;
}

Entry& entry(int n) { return g_entries[n]; }

void Entry::run_original(Cpu& c) const {
    GuestArgs a;
    for (int k = 0; k < 8; k++) a.i(c.x(k));
    for (int k = 0; k < 8; k++) a.vecs.push_back(c.v(k));
    a.x8 = c.x(8);
    GuestResult g = guest_call(orig, a);
    c.set_x(0, g.x0);
    c.set_x(1, g.x1);
    c.set_v(0, g.v0);
    c.set_v(1, g.v1);
    c.set_v(2, g.v2);
    c.set_v(3, g.v3);
}

const std::unordered_map<u64, Body>& Family::own_bodies() {
    // (only installed ones: in --selftest nothing is, and the guest callees must run)
    std::call_once(own_once_, [this] {
        own_ = new std::unordered_map<u64, Body>;
        for (int k : entries)
            if (g_entries[k].body && g_entries[k].orig && !g_entries[k].test) (*own_)[guest::sym(g_entries[k].sym)] = g_entries[k].body;
    });
    return *own_;
}

void Family::gcall(A64& r, u64 target) {
    if (t_play) return play_call(r, target, 0);
    if (t_rec) return record_call(r, target);
    t_sret = false;
    // (Inside a check on this thread no call can be checked, so a transcribed callee runs
    // directly, as without the check, instead of through a JIT level of its own.)
    if (!on.load(std::memory_order_relaxed) || t_busy) {
        auto& m = own_bodies();
        auto it = m.find(target);
        if (it != m.end()) return it->second(r);
    }
    a2c_gcall(r, target);
}
void Family::icall(A64& r, u64 target) {
    if (t_play || t_rec) return gcall(r, target);
    t_sret = false;
    if (!on.load(std::memory_order_relaxed) || t_busy) {
        auto& m = own_bodies();
        auto it = m.find(target);
        if (it != m.end()) return it->second(r);
    }
    a2c_gcall(r, target);
}
void Family::gcall_sret(A64& r, u64 target) {
    if (!t_rec) return gcall(r, target);  // (the flag is for record_call only)
    t_sret = true;
    gcall(r, target);
    t_sret = false;
}

// Recorded as a call (the replay performs it again: the undo log reverted the native run's copy;
// later callees' writes over it come back with their patches).
void Family::memop(A64& r, u64 target, int kind) {
    if (t_play) return play_call(r, target, kind);
    Recorder* rec = t_rec;
    if (!rec) {
        do_memop(kind, r.x[0], r.x[1], r.x[2]);
        return;
    }
    Call k;
    k.target = callee(target);
    k.via = target;
    k.sp = r.x[31];
    k.memop = kind;
    k.ni = 3, k.nf = 0;
    for (int i = 0; i < 9; i++) k.x[i] = r.x[i];
    if (t_undo_on)
        for (u64 o = 0; o < r.x[2]; o += 8) undo_note(r.x[0] + o, (u32)std::min<u64>(8, r.x[2] - o));
    do_memop(kind, r.x[0], r.x[1], r.x[2]);
    k.rx0 = r.x[0], k.rx1 = r.x[1];  // (memset / memcpy return the destination; x1 is left as it was)
    for (int i = 0; i < 4; i++) k.rv[i] = r.v[i];
    k.obj_after = rec->regions->capture();
    k.nfresh = rec->fresh.r.size();
    if (k.nfresh) k.fresh_after = rec->fresh.capture();
    rec->keep(k);
}

ACall::ACall(Family& f) : fam(&f) {
    memset(&r, 0, sizeof r);
    Cpu* c = current_cpu();
    r.x[31] = c ? c->sp() : 0;
}
void ACall::tail(Cpu& c, u64 target) {
    call(target);
    c.set_x(0, r.x[0]);
    c.set_x(1, r.x[1]);
    for (int k = 0; k < 4; k++) c.set_v(k, to_v128(r.v[k]));
}
void Family::gcall_n(A64& r, u64 target, int ni, int nf, bool sret) {
    t_ni = ni, t_nf = nf;
    if (sret) gcall_sret(r, target);
    else gcall(r, target);
    t_ni = t_nf = -1;
}
u64 ACall::call(u64 target) {
    t_ni = ni, t_nf = nf;
    fam->gcall(r, target);
    t_ni = t_nf = -1;
    return r.x[0];
}
u64 ACall::call_sret(u64 target) {
    t_ni = ni, t_nf = nf;
    fam->gcall_sret(r, target);
    t_ni = t_nf = -1;
    return r.x[0];
}

void Family::summary(FILE* f) {
    for (int i : entries) {
        Entry& p = g_entries[i];
        if (!p.checks) continue;
        fprintf(f, "%-60.60s checks %6llu ok %6llu bad %llu skipped %llu races %llu\n", p.sym, (unsigned long long)p.checks.load(), (unsigned long long)p.ok.load(),
                (unsigned long long)p.bad.load(), (unsigned long long)p.skipped.load(), (unsigned long long)p.races.load());
    }
}
void Family::summary_file() {
    if (out_path.empty()) return;
    if (FILE* f = fopen(out_path.c_str(), "w")) {
        fprintf(f, "%llu checks: %llu ok, %llu mismatches, %llu skipped, %llu races\n", (unsigned long long)stats.checks.load(), (unsigned long long)stats.ok.load(),
                (unsigned long long)stats.bad.load(), (unsigned long long)stats.skipped.load(), (unsigned long long)stats.races.load());
        summary(f);
        fclose(f);
    }
}

namespace {

// ---- the check ----

GuestArgs entry_args(const u64 x[9], const V128 v[8]) {
    GuestArgs a;
    for (int i = 0; i < 8; i++) a.i(x[i]);
    for (int i = 0; i < 8; i++) a.vecs.push_back(v[i]);
    a.x8 = x[8];
    return a;
}

void totals(Family& f) {
    u64 n = f.stats.checks;
    if (n % 1000) {
        // (the counts file also every 10 s: a session ends with a kill, and rarely called
        // functions would otherwise be missing from it)
        static std::atomic<s64> last{0};
        static std::mutex m;
        s64 now = (s64)time(nullptr), l = last.load(std::memory_order_relaxed);
        if (f.out_path.empty() || now - l < 10 || !last.compare_exchange_strong(l, now)) return;
        std::lock_guard lk(m);
        f.summary_file();
        return;
    }
    f.summary_file();
    LOGI(f.log_tag.c_str(), "%llu checks: %llu ok, %llu mismatches, %llu skipped, %llu races", (unsigned long long)n, (unsigned long long)f.stats.ok.load(),
         (unsigned long long)f.stats.bad.load(), (unsigned long long)f.stats.skipped.load(), (unsigned long long)f.stats.races.load());
}

// Replays in progress on any thread (and how many started so far): a replay puts the snapshot
// regions and other memory back to their state before its native run while it runs, so a native
// run on another thread at the same time may read that rewound memory (e.g. an object's position
// that a fiber thread's check of the same model rewinds). A mismatch whose native run overlapped
// another thread's replay is counted as a race.
std::atomic<int> g_rewinding{0};
std::atomic<u64> g_rewind_epoch{0};

void check(Cpu& c, int i) {
    Entry& e = g_entries[i];
    Family& fam = *e.fam;
    if (t_busy || !e.orig || !fam.only.match(e.sym) || (fam.budget && e.checks >= (u64)fam.budget) || e.calls++ % fam.every) return e.run_unchecked(c);
    t_busy = true;
    if (fam.trace) LOGI(fam.log_tag.c_str(), "check %s x0=%llx (thread %ld)", e.sym, (unsigned long long)c.x(0), (long)gettid());
    u64 x[9];
    V128 v[8];
    for (int k = 0; k < 9; k++) x[k] = c.x(k);
    for (int k = 0; k < 8; k++) v[k] = c.v(k);
    u64 sp0 = c.sp();
    Regions regions;
    if (e.obj_bytes && x[0] >= 0x100000) regions.r.push_back({x[0], e.obj_bytes});
    bool has_obj = !regions.r.empty();
    fam.add_regions(e, x, has_obj, regions);
    // Arguments pointing into the caller's frame (at or above the entry SP: a TArray, an out
    // CVector, an sret buffer): the replay must start from their bytes as the native run found
    // them (callees the native run made, e.g. TArray::ForceRealloc, changed them), and they are
    // outputs to compare. (Below the entry SP is the body's own frame: stack0.)
    for (int k = 0; k < 9; k++)
        if (x[k] >= sp0 && in_stack(x[k], sp0)) {
            bool dup = false;
            for (auto& [a, n] : regions.r) dup |= a == x[k];
            if (!dup) regions.add(x[k], (u32)kBuf);
        }
    std::vector<u8> pre = regions.capture();
    // The stack below the entry SP as the native run found it: the replay runs at the same SP
    // (stack arguments in place, stack-address arguments at the same offsets) and gets these bytes
    // back, so a slot neither run wrote holds the same leftovers in both (e.g. a matrix's unused
    // lanes loaded into a register that is then passed along, dead, to a callee).
    std::vector<u8> stack0((const u8*)(sp0 - kFrameSnap), (const u8*)sp0);
    Recorder rec;
    rec.fam = &fam;
    rec.regions = &regions;
    rec.sp0 = sp0;
    t_rec = &rec;
    StoreLog undo;
    t_undo = &undo;
    t_undo_on = e.body != nullptr;
    int rw0 = g_rewinding.load();
    u64 ep0 = g_rewind_epoch.load();
    e.invoke(c);
    bool overlapped = rw0 > 0 || g_rewinding.load() > 0 || g_rewind_epoch.load() != ep0;
    t_undo_on = false;
    t_undo = nullptr;
    t_rec = nullptr;
    bool undo_overflow = !undo.v.empty() && undo.v.back().n == 0;
    // the final bytes of everything the body stored (callees' later writes included)
    std::vector<u64> redo(undo.v.size());
    for (size_t q = 0; q < undo.v.size(); q++) memcpy(&redo[q], (const void*)undo.v[q].a, undo.v[q].n);
    auto to_pre = [&] {
        undo.undo();
        regions.restore(pre);
    };
    // A replay's starting memory: the blocks the native run freed as they were (journaled), then
    // the body's stores undone and the regions as before.
    auto prep = [&](Journal& j) {
        for (size_t q = rec.calls.size(); q-- > 0;) {
            Call& k = rec.calls[q];
            if (k.freed_at) j.write(k.freed_at, k.freed);
        }
        to_pre();
    };
    u64 res_x0 = c.x(0), res_x1 = c.x(1);
    V128 res_v0 = c.v(0), res_v1 = c.v(1), res_v2 = c.v(2), res_v3 = c.v(3);
    std::vector<u8> after = regions.capture();
    // (the blocks callees allocated, as the native run left them: compared with the replay's)
    std::vector<u8> fresh_final = rec.fresh.capture();
    auto restore_fresh = [&](Journal& j, const Call& k) {
        size_t o = 0;
        for (size_t q = 0; q < k.nfresh; q++) {
            auto [a, n] = rec.fresh.r[q];
            j.write(a, std::vector<u8>(k.fresh_after.begin() + o, k.fresh_after.begin() + o + n));
            o += n;
        }
    };
    std::vector<const char*> names;
    std::string why = rec.overflow ? "more than kMaxRecord bytes of snapshots" : undo_overflow ? "undo log full" : fam.unreplayable(e.sym) ? "unreplayable" : "";
    for (auto& k : rec.calls) {
        if (!why.empty()) break;
        const char* n = fam.stubbable(k.target) ? ensure_stub(k.target) : nullptr;
        // (a callee that can't be stubbed itself, e.g. a test-hooked function of the family, or
        // an unrelocatable prologue: the PLT entry the call went through, where the guest's call
        // goes too)
        if (!n && k.via != k.target && !k.memop && fam.stubbable(k.via) && (n = ensure_stub(k.via))) {
            k.target = k.via;
            std::lock_guard lk(g_plt_mu);
            g_plt_lands.try_emplace(k.via, k.lands);
        }
        if (!n) {
            char b[80];
            snprintf(b, sizeof b, "can't stub callee %llx", (unsigned long long)(k.target - main_lib()->base));
            why = b;
            break;
        }
        names.push_back(n);
    }
    bool replayable = why.empty();
    fam.stats.checks++;
    e.checks++;
    if (!replayable) {
        fam.stats.skipped++;
        e.skipped++;
        fam.on_skip(e, why);
        t_busy = false;
        totals(fam);
        return;  // the native run stands
    }
    // The original against the replay stubs (no side effects outside the snapshot regions but
    // what the native run wrote as well), from the state in `pre`.
    struct Run {
        std::vector<std::string> errs;  // the call sequence
        u64 x0 = 0;
        V128 v0{};
        std::vector<u8> after;
        std::vector<u8> fresh;  // the callee-allocated blocks after the replay
    };
    bool rewound = false;
    auto rewind = [&] {
        if (rewound) return;
        rewound = true;
        g_rewinding++;
        g_rewind_epoch++;
    };
    // (alt: another image's counterparts of the recorded callees, where a replay's calls may land
    // instead, and their stubs' names; unused since the 3.7.0 oracle was removed)
    struct Alt {
        std::vector<u64> at;
        std::vector<const char*> names;
    };
    auto guest_run = [&](u64 fn, const Alt* alt) {
        Run run;
        Journal journal;
        rewind();
        prep(journal);
        auto& errs = run.errs;
        size_t next = 0, extra = 0;
        {
            ReplaySession ss;
            if (fam.dump)
                for (size_t q = 0; q < rec.calls.size(); q++) {
                    Call& k = rec.calls[q];
                    LOGI(fam.log_tag.c_str(), "  rec %zu %llx x0 %llx x1 %llx x2 %llx x8 %llx sp %llx -> %llx bufs %zu", q, (unsigned long long)(k.target - main_lib()->base),
                         (unsigned long long)k.x[0], (unsigned long long)k.x[1], (unsigned long long)k.x[2], (unsigned long long)k.x[8], (unsigned long long)k.sp,
                         (unsigned long long)k.rx0, k.bufs.size());
                    for (auto& bf : k.bufs) {
                        std::string h;
                        char hb[4];
                        for (size_t j = 0; j < 24 && j < bf.after.size(); j++) snprintf(hb, sizeof hb, "%02x", bf.after[j]), h += hb;
                        h += " (was ";
                        for (size_t j = 0; j < 24 && j < bf.before.size(); j++) snprintf(hb, sizeof hb, "%02x", bf.before[j]), h += hb;
                        LOGI(fam.log_tag.c_str(), "    buf x%d at %llx: %s)", bf.reg, (unsigned long long)k.x[bf.reg], h.c_str());
                    }
                }
            // `stub_at`: the address of the stub that answered (each stub name is answered with its
            // own). Not the CPU's pc - 4: that is the stub only for a call through the JIT (its
            // SVC); a direct native->native call (a2c_gcall / guest_call's hooked-function path,
            // e.g. a native the original reaches calling a recorded callee) leaves pc at its caller.
            auto replay = [&](Cpu& cc, u64 stub_at) {
                u64 at = stub_at;
                char b[256];
                if (fam.dump)
                    LOGI(fam.log_tag.c_str(), "  hit %zu %llx x0 %llx x1 %llx x2 %llx x8 %llx sp %llx", next, (unsigned long long)(at - main_lib()->base), (unsigned long long)cc.x(0),
                         (unsigned long long)cc.x(1), (unsigned long long)cc.x(2), (unsigned long long)cc.x(8), (unsigned long long)cc.sp());
                if (fam.dump)
                    for (int a : {0, 1, 8})
                        if (cc.x(a) >= cc.sp() && in_stack(cc.x(a), cc.sp())) {
                            std::string h;
                            char hb[4];
                            for (int j = 0; j < 24; j++) snprintf(hb, sizeof hb, "%02x", ((const u8*)cc.x(a))[j]), h += hb;
                            LOGI(fam.log_tag.c_str(), "    at x%d: %s", a, h.c_str());
                        }
                if (next >= rec.calls.size()) {
                    snprintf(b, sizeof b, "extra call to %llx", (unsigned long long)(at - main_lib()->base));
                    if (errs.size() < 4) errs.push_back(b);
                    if (++extra > (size_t)kRunaway) {
                        if (extra == (size_t)kRunaway + 1) errs.push_back("runaway replay stopped");
                        stop_runaway(cc);
                    }
                    return;
                }
                Call& k = rec.calls[next++];
                if (k.target != at && !(alt && alt->at[next - 1] && alt->at[next - 1] == at)) {
                    snprintf(b, sizeof b, "call %zu: target %llx, recorded %llx", next - 1, (unsigned long long)(at - main_lib()->base),
                             (unsigned long long)(k.target - main_lib()->base));
                    if (errs.size() < 4) errs.push_back(b);
                    return;
                }
                for (int a = 0; a < k.ni; a++) {
                    u64 gv = cc.x(a), tv = k.x[a];
                    bool gs = in_stack(gv, cc.sp()), ts = in_stack(tv, k.sp);
                    if (!(gv == tv || (gs && ts && gv - cc.sp() == tv - k.sp))) {
                        snprintf(b, sizeof b, "call %zu (%llx): x%d %llx, recorded %llx", next - 1, (unsigned long long)(at - main_lib()->base), a,
                                 (unsigned long long)gv, (unsigned long long)tv);
                        if (errs.size() < 4) errs.push_back(b);
                    }
                }
                for (int a = 0; a < k.nf; a++)
                    if ((k.ni < 8 ? (u32)cc.v(a).lo != (u32)k.vlo[a] : cc.v(a).lo != k.vlo[a])) {
                        snprintf(b, sizeof b, "call %zu (%llx): v%d %llx, recorded %llx", next - 1, (unsigned long long)(at - main_lib()->base), a,
                                 (unsigned long long)cc.v(a).lo, (unsigned long long)k.vlo[a]);
                        if (errs.size() < 4) errs.push_back(b);
                    }
                if (k.memop) {
                    // done again: on the guest's own frame, and elsewhere too (the undo log
                    // reverted the native run's copy; later callees' writes over it come back
                    // with their patches)
                    u64 d = cc.x(0);
                    do_memop(k.memop, d, cc.x(1), cc.x(2));
                    regions.restore(k.obj_after);
                    restore_fresh(journal, k);
                    cc.set_x(0, d);
                    return;
                }
                for (auto& bf : k.bufs) {
                    u64 dst = cc.x(bf.reg);
                    if (dst >= cc.sp() && in_stack(dst, cc.sp())) write_back(bf, dst);
                }
                for (auto& pt : k.patches) memcpy((void*)pt.a, &pt.v, pt.n);
                if (!k.ret_obj.empty()) journal.write(k.rx0, k.ret_obj);
                regions.restore(k.obj_after);
                restore_fresh(journal, k);
                cc.set_x(0, k.rx0);
                cc.set_x(1, k.rx1);
                for (int a = 0; a < 4; a++) cc.set_v(a, to_v128(k.rv[a]));
            };
            for (size_t q = 0; q < names.size(); q++) {
                u64 tgt = rec.calls[q].target;
                ss.answer(names[q], [&replay, tgt](Cpu& cc) { replay(cc, tgt); });
            }
            if (alt)
                for (size_t q = 0; q < alt->names.size(); q++) {
                    u64 tgt = alt->at[q];
                    ss.answer(alt->names[q], [&replay, tgt](Cpu& cc) { replay(cc, tgt); });
                }
            // (also where the call went in: the JIT may have compiled a lone B together with its
            // target's first instructions, as one block keyed by the B)
            for (auto& k : rec.calls) drop_stale_code(k.target), drop_stale_code(k.via);
            if (alt)
                for (u64 a : alt->at)
                    if (a) drop_stale_code(a);
            memcpy((void*)(sp0 - kFrameSnap), stack0.data(), kFrameSnap);
            GuestResult g = guest_call_at_sp(fn, x, v, x[8], sp0);
            run.x0 = g.x0;
            run.v0 = g.v0;
        }
        if (next != rec.calls.size() && errs.empty())
            errs.push_back("original made " + std::to_string(next) + " of " + std::to_string(rec.calls.size()) + " calls");
        run.after = regions.capture();
        run.fresh = rec.fresh.capture();
        journal.undo();
        // (the native run's state again: see check()'s end; until then this counts as rewinding)
        return run;
    };
    // results (a stack address compares by its offset from the entry SP; the replay's frames
    // sit elsewhere)
    auto compare = [&](const Run& g, u64 nx0, V128 nv0, const std::vector<u8>& nafter, std::vector<std::string>& errs) {
        bool x0_same = g.x0 == nx0 || (in_stack(g.x0, sp0) && in_stack(nx0, sp0));
        if (e.ret == kInt) x0_same = x0_same || (u32)g.x0 == (u32)nx0;  // (bool / int: only w0 is defined)
        if ((e.ret & kInt) && !x0_same) {
            char b[96];
            snprintf(b, sizeof b, "x0 %llx, native %llx", (unsigned long long)g.x0, (unsigned long long)nx0);
            errs.push_back(b);
        }
        if ((e.ret & kFloat) && g.v0.lo != nv0.lo) {
            char b[96];
            snprintf(b, sizeof b, "v0 %llx, native %llx", (unsigned long long)g.v0.lo, (unsigned long long)nv0.lo);
            errs.push_back(b);
        }
        if (g.after != nafter) {
            size_t k = 0;
            while (g.after[k] == nafter[k]) k++;
            char b[128];
            snprintf(b, sizeof b, "%s differs (guest %02x, native %02x)", regions.where(k).c_str(), g.after[k], nafter[k]);
            errs.push_back(b);
        }
    };
    Run g = guest_run(e.orig, nullptr);
    std::vector<std::string> errs = g.errs;
    compare(g, res_x0, res_v0, after, errs);
    if (g.fresh != fresh_final) {
        size_t k = 0;
        while (g.fresh[k] == fresh_final[k]) k++;
        size_t blk = 0, off = k;
        while (off >= rec.fresh.r[blk].second) off -= rec.fresh.r[blk++].second;
        char b[128];
        snprintf(b, sizeof b, "allocated block %zu +0x%zx differs (guest %02x, native %02x)", blk, off, g.fresh[k], fresh_final[k]);
        errs.push_back(b);
    }
    // A mismatch of a pure search counts only if it reproduces: other threads write some of this
    // state at any time (e.g. an effect piece's models becoming ready on the loader thread between
    // the native run and the replay). So the native code runs once more from the same snapshot,
    // its outgoing calls answered from the record (Player: nothing executes twice). If it now
    // agrees with the original, or doesn't repeat its own first run (its inputs changed under
    // it), or the original doesn't repeat its first replay, the call is counted as a race instead.
    // (Only for hand-written functions that made no calls: their only writes are to the snapshot
    // regions, so a rerun starts from exactly the state the first run saw, less other threads'
    // writes. A function with calls, or a transcribed one, may have changed memory outside the
    // regions that its own rerun, and the replay, then see: no evidence of a race.)
    const char* race = nullptr;
    if (!errs.empty() && !e.body && rec.calls.empty()) {
        for (int k = 0; k < 9; k++) c.set_x(k, x[k]);
        for (int k = 0; k < 8; k++) c.set_v(k, v[k]);
        Player pl;
        Journal pj;
        pl.rec = &rec;
        pl.journal = &pj;
        rewind();
        prep(pj);
        t_play = &pl;
        try {
            e.invoke(c);
        } catch (const PlayDiverged&) {
            pl.bad = true;
        }
        t_play = nullptr;
        pj.undo();
        bool nbad = pl.bad || pl.next != rec.calls.size();
        u64 nx0 = c.x(0);
        V128 nv0 = c.v(0);
        std::vector<u8> nafter = regions.capture();
        std::vector<std::string> e2;
        compare(g, nx0, nv0, nafter, e2);
        bool same_x0 = !(e.ret & kInt) || (e.ret == kInt ? (u32)nx0 == (u32)res_x0 : nx0 == res_x0);
        bool same_v0 = !(e.ret & kFloat) || nv0.lo == res_v0.lo;
        if (!nbad && g.errs.empty() && e2.empty()) race = "native rerun agrees";
        else if (nbad || !same_x0 || !same_v0 || nafter != after) race = "native rerun differs from its first run";
        else {
            Run g2 = guest_run(e.orig, nullptr);
            if (g2.errs != g.errs || g2.x0 != g.x0 || g2.v0.lo != g.v0.lo || g2.after != g.after) race = "original's rerun differs from its first";
        }
    }
    // (back to the native run's state: only what the replays changed, so memory the native run
    // freed, e.g. a removed node, isn't written again when the replay left it alone)
    for (size_t q = 0; q < undo.v.size(); q++) memcpy((void*)undo.v[q].a, &redo[q], undo.v[q].n);
    regions.restore_diff(regions.capture(), after);
    if (rewound) g_rewinding--;
    if (!errs.empty() && !race && overlapped) race = "another thread's replay was rewinding memory during the native run";
    c.set_x(0, res_x0);
    c.set_x(1, res_x1);
    c.set_v(0, res_v0);
    c.set_v(1, res_v1);
    c.set_v(2, res_v2);
    c.set_v(3, res_v3);
    if (errs.empty()) {
        fam.stats.ok++;
        e.ok++;
    } else {
        std::string s;
        for (auto& m : errs) s += m + "; ";
        s += "(" + std::to_string(rec.calls.size()) + " calls)";
        if (race) {
            u64 n = ++fam.stats.races;
            e.races++;
            if (n <= 60) LOGI(fam.log_tag.c_str(), "race %s (thread %ld): %s; %s", e.sym, (long)gettid(), s.c_str(), race);
        } else {
            e.bad++;
            fam.on_mismatch(e, s);
            u64 n = ++fam.stats.bad;
            if (n <= 60) LOGI(fam.log_tag.c_str(), "MISMATCH %s (thread %ld): %s", e.sym, (long)gettid(), s.c_str());
        }
    }
    t_busy = false;
    totals(fam);
}

}  // namespace
}  // namespace soa::live
