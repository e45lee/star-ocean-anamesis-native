// The shared live differential check (live_check.h): switches, the stub registry, and the
// record / replay check (Check, at the end).
//
// Record / replay, the rules:
//   - A call's target is where it lands: PLT entries resolved, lone-B functions (4-byte tail
//     branches, too small to stub) followed (PLT -> B -> PLT). A lone RET isn't recorded.
//   - Stubs are process-wide (ensure_stub) and each thread's JIT levels drop the unpatched code
//     once (drop_stale_code), at the callee and where the call went in (the PLT entry, lone B or
//     vtable entry); a stub another stubber renamed is re-applied. A callee that can't be stubbed
//     (an unrelocatable prologue, a family's test-hooked function) is stubbed at the PLT entry
//     the call went through.
//   - Arguments (x0-x8) pointing into the caller's frame (at or above the entry SP) are snapshot
//     regions of kBuf bytes: e.g. a TArray a callee (ForceRealloc) filled in the native run; a
//     replay that started from the filled array would skip the call and run into unrecorded calls.
//   - The original runs at the native run's entry SP, with the kFrameSnap bytes below it as the
//     native run found them: stack arguments are in place, and slots neither run writes hold the
//     same leftovers (dead registers passed to callees compare equal).
//   - The replay's stub session never has an empty `only` (ReplaySession).
//   - A check's callees run unchecked (t_busy, every family).
//   - The replay starts from the memory the native run saw: the blocks the native run freed
//     (operator delete / delete[], the STL allocator's Free, deleting destructors: the vtable the
//     caller dispatched through), the objects callees returned (ret_object_bytes), the elements of
//     stack vectors a callee filled, and the snapshot regions. Only the bytes the replays changed
//     are written back afterwards.
//   - Stack buffers passed to a callee (x0-x8 within the frame): the bytes the callee changed are
//     replayed (whole changed 8-byte words). An 8-aligned stack x8 may be an sret buffer: its first
//     16 bytes are always replayed. Out-parameters written whole (out_param_bytes) are always
//     replayed.
//   - Blocks a callee allocates (operator new / new[]: the requested size, up to kMaxFresh) are
//     snapshotted after every later call and written back at the replay's same call: later
//     callees initialise them (a constructor) and the native reads them, so the replay must not
//     see the native run's final bytes. Their bytes after the replay must match the native run's.
//   - A check records at most kMaxRecord bytes of snapshots (else skipped), and a replay that runs
//     past its record is stopped after kRunaway extra calls.
//   - A replay rewinds memory other threads can see (the snapshot regions, freed blocks) until
//     the check puts the native run's state back: a mismatch whose native run overlapped another
//     thread's replay counts as a race, not a mismatch.
//   - A stack-vector guess (a callee-filled {begin, end, cap} in a stack buffer) needs aligned,
//     mapped pointers (a buffer of floats can look like one), and so does a freed block's copy.
//   - A mismatch of a native that made no calls is rerun (the native again, then the original):
//     if it doesn't reproduce, another thread wrote its inputs in between and it counts as a race.
#include "native/common/live_check.h"

#ifndef _WIN32
#include <sys/mman.h>
#endif
#include <unistd.h>

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <set>

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
    struct DroppedTag;  // target -> lowest level dropped (this thread's)
    auto& t_dropped = thread_object<std::unordered_map<u64, size_t>, DroppedTag>();
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

// ---- the record / replay families ----

namespace {

constexpr int kMax = 768;
Entry g_entries[kMax];
int g_n = 0;

void check(Cpu& c, int i);
template <int I>
void hook(Cpu& c) {
    Entry& e = g_entries[I];
    if (!e.fam->on.load(std::memory_order_relaxed)) return e.run(c);
    check(c, I);
}
template <int... I>
constexpr HostFn hook_at(int i, std::integer_sequence<int, I...>) {
    constexpr HostFn t[] = {hook<I>...};
    return t[i];
}

// A deleting destructor (D0: the object's own delete). The caller read the object's vtable to
// call it (a virtual delete), so the replay reads it again after the native run freed (and maybe
// reused) the block.
bool is_deleting_dtor(u64 target) {
    struct CacheTag;
    auto& cache = thread_object<std::unordered_map<u64, bool>, CacheTag>();
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
        u32 always = 0;        // leading bytes replayed even if unchanged (out_param_bytes)
        bool x8_head = false;  // a stack x8 (an sret buffer, maybe): the first 16 bytes at an aligned x8 always
    };
    std::vector<Buf> bufs;
    // the elements of a stack vector the callee filled: (address, bytes after, size), written
    // again by the replay
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
    size_t bytes = 0;  // snapshot bytes so far; past kMaxRecord the call isn't replayed (skipped)
    bool overflow = false;
    // Blocks allocated by callees (operator new / new[], their requested size): the
    // callees after it initialise them (a constructor) and the native reads them, so the replay
    // gets their bytes back at each call as the native run left them.
    Regions fresh;
    void keep(Call& k) {
        bytes += k.obj_after.size() + k.fresh_after.size();
        for (auto& b : k.bufs) bytes += 2 * b.after.size();
        if (bytes > kMaxRecord) overflow = true;
        if (!overflow) calls.push_back(std::move(k));
    }
};
thread_local Recorder* t_rec = nullptr;
// The confirm rerun of a mismatch (Check::race_of): the native code runs again with every outgoing
// call answered from the first run's record instead of executing (no side effects twice).
struct Player {
    Recorder* rec = nullptr;
    Journal* journal = nullptr;
    size_t next = 0;
    bool bad = false;  // a call that doesn't match the record (target or arguments)
};
thread_local Player* t_play = nullptr;
struct PlayDiverged {};

// A call on the register file outside a check: a guest function that is itself replaced by native
// code is called directly on the current CPU (the JIT round trip costs more than most callees);
// otherwise a guest call with the caller's stack slots as the callee's stack arguments.
void regs_call(Regs& r, u64 target) {
    if (Cpu* c = current_cpu()) {
        if (HostFn f = hooked_host_fn(target)) {
            u64 saved_sp = c->sp();
            for (int i = 0; i <= 8; i++) c->set_x(i, r.x[i]);
            for (int i = 0; i < 8; i++) c->set_v(i, to_v128(r.v[i]));
            c->set_sp(r.sp);  // stack arguments are at the caller's SP
            if (!(__builtin_expect(t_hook_filter != nullptr, 0) && t_hook_filter(*c, target))) f(*c);
            c->set_sp(saved_sp);
            r.x[0] = c->x(0);
            r.x[1] = c->x(1);
            for (int i = 0; i < 4; i++) r.v[i] = to_v4(c->v(i));
            return;
        }
    }
    GuestResult g = a2c_guest_call(target, r.x, r.v, r.sp);
    r.x[0] = g.x0;
    r.x[1] = g.x1;
    r.v[0] = to_v4(g.v0);
    r.v[1] = to_v4(g.v1);
    r.v[2] = to_v4(g.v2);
    r.v[3] = to_v4(g.v3);
}

// Guest call through the JIT (never a direct host call: the replay stubs need the guest PC).
void gcall_jit(Regs& r, u64 target) {
    GuestResult g = a2c_guest_call(target, r.x, r.v, r.sp);
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

void play_call(Regs& r, u64 target) {
    Player* p = t_play;
    u64 at = callee(target);
    if (is_ret_only(at)) return;
    // (a call off the record: the native code took another path, so its inputs changed; its
    // results can't be made up, so the rerun stops here)
    if (p->next >= p->rec->calls.size()) throw PlayDiverged{};
    Call& k = p->rec->calls[p->next++];
    if (k.target != at) throw PlayDiverged{};
    for (int a = 0; a < k.ni; a++)
        if (r.x[a] != k.x[a]) p->bad = true;  // (same frames as the recording run)
    for (int a = 0; a < k.nf; a++) {
        u64 lo;
        memcpy(&lo, &r.v[a], 8);
        if (k.ni < 8 ? (u32)lo != (u32)k.vlo[a] : lo != k.vlo[a]) p->bad = true;
    }
    for (auto& bf : k.bufs)
        if (r.x[bf.reg] >= r.sp && in_stack(r.x[bf.reg], r.sp)) write_back(bf, r.x[bf.reg]);
    for (auto& pt : k.patches) memcpy((void*)pt.a, &pt.v, pt.n);
    if (!k.ret_obj.empty()) p->journal->write(k.rx0, k.ret_obj);
    p->rec->regions->restore(k.obj_after);
    r.x[0] = k.rx0, r.x[1] = k.rx1;
    for (int a = 0; a < 4; a++) r.v[a] = k.rv[a];
}

// [a, a + n) is mapped memory (the stack-vector guess below also matches buffers of floats: e.g. a
// CVector (0.707, 0) reads as the "pointer" 0x3f34fe8a).
bool mapped(u64 a, u64 n) { return hostmem::mapped((const void*)a, n); }

// Where a call through a PLT entry that has been stubbed itself (Check::stub_callees: the callee
// couldn't be) lands: callee() no longer recognises the patched entry.
std::mutex g_plt_mu;
std::unordered_map<u64, u64> g_plt_lands;
u64 lands_of(u64 target, u64 resolved) {
    if (resolved != target) return resolved;
    std::lock_guard lk(g_plt_mu);
    auto it = g_plt_lands.find(target);
    return it != g_plt_lands.end() ? it->second : resolved;
}

void record_call(Regs& r, u64 target, int ni, int nf) {
    Recorder* rec = t_rec;
    Call k;
    k.target = callee(target);
    k.lands = lands_of(target, k.target);
    k.via = target;
    k.ni = ni, k.nf = nf;
    if (is_ret_only(k.target)) return;  // a lone RET: nothing to replay
    k.sp = r.sp;
    for (int i = 0; i < 9; i++) k.x[i] = r.x[i];
    for (int i = 0; i < 4; i++) memcpy(&k.vlo[i], &r.v[i], 8);
    std::vector<std::pair<int, std::vector<u8>>> before;
    for (int i = 0; i < 9; i++)
        if (r.x[i] >= r.sp && in_stack(r.x[i], r.sp)) before.push_back({i, std::vector<u8>((u8*)r.x[i], (u8*)r.x[i] + kBuf)});
    if (u32 fb = freed_bytes(k.target); fb && r.x[0] >= 0x100000 && !in_stack(r.x[0], r.sp) && mapped(r.x[0], fb)) {
        k.freed_at = r.x[0];
        k.freed.assign((u8*)k.freed_at, (u8*)k.freed_at + fb);
    }
    t_rec = nullptr;  // the callee's own calls aren't part of this record
    gcall_jit(r, target);
    t_rec = rec;
    k.rx0 = r.x[0], k.rx1 = r.x[1];
    for (int i = 0; i < 4; i++) k.rv[i] = r.v[i];
    if (u32 n = ret_object_bytes(k.target); n && k.rx0 >= 0x100000) k.ret_obj.assign((u8*)k.rx0, (u8*)k.rx0 + n);
    k.obj_after = rec->regions->capture();
    if (is_alloc(k.target) && k.rx0 >= 0x100000 && k.x[0] && k.x[0] <= kMaxFresh) rec->fresh.add(k.rx0, (u32)k.x[0]);
    k.nfresh = rec->fresh.r.size();
    if (k.nfresh) k.fresh_after = rec->fresh.capture();
    for (auto& [reg, b] : before) {
        u32 always = out_param_bytes(k.target, reg);
        bool x8_head = reg == 8 && !(k.x[8] & 7);
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

thread_local bool t_busy = false;

Family::Family(const char* tag_, int every_) : tag(tag_), log_tag(std::string(tag_) + "_check"), every(every_) {
    std::lock_guard lk(g_check_m);
    families().push_back(this);  // (static families: --live-check switches them on, apply_live_check)
}

int Family::add(const char* sym, HostFn run, u32 obj_bytes, RetKind ret, bool (*enabled)(), const char* label, const char* file) {
    if (g_n >= kMax) {
        LOGE("live_check", "%s: too many functions (kMax %d); %s left to the guest", tag, kMax, sym);
        return -1;
    }
    int n = g_n++;
    Entry& e = g_entries[n];
    e.fam = this, e.sym = sym, e.run = run, e.obj_bytes = obj_bytes, e.ret = ret;
    NativeFunction f{sym, hook_at(n, std::make_integer_sequence<int, kMax>{}), label, enabled, &e.orig};
    f.file = file;
    register_native_function(f);
    entries.push_back(n);
    return n;
}

Entry& entry(int n) { return g_entries[n]; }

void Family::gcall(Regs& r, u64 target, int ni, int nf) {
    if (t_play) return play_call(r, target);
    if (t_rec) return record_call(r, target, ni, nf);
    regs_call(r, target);
}

ACall::ACall(Family& f) : fam(&f) {
    memset(&r, 0, sizeof r);
    Cpu* c = current_cpu();
    r.sp = c ? c->sp() : 0;
}
void ACall::tail(Cpu& c, u64 target) {
    call(target);
    c.set_x(0, r.x[0]);
    c.set_x(1, r.x[1]);
    for (int k = 0; k < 4; k++) c.set_v(k, to_v128(r.v[k]));
}
u64 ACall::call(u64 target) {
    fam->gcall(r, target, ni, nf);
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

// One checked call, in its steps: snapshot (the regions and the frame below the entry SP), record
// (the native run, its outgoing calls recorded), stub_callees (a replay stub per recorded callee),
// replay (the original against the stubs, from the snapshot), compare (results and memory), race_of
// (whether a mismatch reproduces), and back to the native run's state.
class Check {
public:
    Check(Cpu& c, Entry& e) : c_(c), e_(e), fam_(*e.fam) {}
    void run();

private:
    // One run of the original against the replay stubs.
    struct Run {
        std::vector<std::string> errs;  // the call sequence
        u64 x0 = 0;
        V128 v0{};
        std::vector<u8> after;
        std::vector<u8> fresh;  // the callee-allocated blocks after the replay
    };
    void snapshot();
    void record();
    bool stub_callees(std::string* why);
    Run replay();
    void answer(Run& run, Journal& journal, size_t& next, size_t& extra, Cpu& cc, u64 at);
    void dump_record() const;
    void compare(const Run& g, u64 nx0, V128 nv0, const std::vector<u8>& nafter, std::vector<std::string>& errs) const;
    void compare_fresh(const Run& g, std::vector<std::string>& errs) const;
    const char* race_of(const Run& g, const std::vector<std::string>& errs);
    void prep(Journal& j);
    void restore_fresh(Journal& j, const Call& k);
    void rewind();
    void count(const std::vector<std::string>& errs, const char* race);

    Cpu& c_;
    Entry& e_;
    Family& fam_;
    u64 x_[9] = {};
    V128 v_[8] = {};
    u64 sp0_ = 0;
    Regions regions_;
    std::vector<u8> pre_;     // the regions before the native run
    std::vector<u8> stack0_;  // the kFrameSnap bytes below the entry SP before it
    Recorder rec_;
    std::vector<u8> after_;        // the regions after the native run
    std::vector<u8> fresh_final_;  // the callee-allocated blocks after it
    u64 res_x0_ = 0, res_x1_ = 0;
    V128 res_v_[4] = {};
    std::vector<const char*> names_;  // the replay stubs, by recorded call
    bool overlapped_ = false;         // the native run overlapped another thread's replay
    bool rewound_ = false;            // this check counts in g_rewinding
};

void Check::snapshot() {
    for (int k = 0; k < 9; k++) x_[k] = c_.x(k);
    for (int k = 0; k < 8; k++) v_[k] = c_.v(k);
    sp0_ = c_.sp();
    if (e_.obj_bytes && x_[0] >= 0x100000) regions_.r.push_back({x_[0], e_.obj_bytes});
    bool has_obj = !regions_.r.empty();
    fam_.add_regions(e_, x_, has_obj, regions_);
    // Arguments pointing into the caller's frame (at or above the entry SP: a TArray, an out
    // CVector, an sret buffer): the replay must start from their bytes as the native run found
    // them (callees the native run made, e.g. TArray::ForceRealloc, changed them), and they are
    // outputs to compare. (Below the entry SP is the native's own frame: stack0_.)
    for (int k = 0; k < 9; k++)
        if (x_[k] >= sp0_ && in_stack(x_[k], sp0_)) {
            bool dup = false;
            for (auto& [a, n] : regions_.r) dup |= a == x_[k];
            if (!dup) regions_.add(x_[k], (u32)kBuf);
        }
    pre_ = regions_.capture();
    // The stack below the entry SP as the native run found it: the replay runs at the same SP
    // (stack arguments in place, stack-address arguments at the same offsets) and gets these bytes
    // back, so a slot neither run wrote holds the same leftovers in both (e.g. a matrix's unused
    // lanes loaded into a register that is then passed along, dead, to a callee).
    stack0_.assign((const u8*)(sp0_ - kFrameSnap), (const u8*)sp0_);
}

void Check::record() {
    rec_.fam = &fam_;
    rec_.regions = &regions_;
    t_rec = &rec_;
    int rw0 = g_rewinding.load();
    u64 ep0 = g_rewind_epoch.load();
    e_.run(c_);
    overlapped_ = rw0 > 0 || g_rewinding.load() > 0 || g_rewind_epoch.load() != ep0;
    t_rec = nullptr;
    res_x0_ = c_.x(0), res_x1_ = c_.x(1);
    for (int k = 0; k < 4; k++) res_v_[k] = c_.v(k);
    after_ = regions_.capture();
    fresh_final_ = rec_.fresh.capture();
}

bool Check::stub_callees(std::string* why) {
    for (auto& k : rec_.calls) {
        const char* n = fam_.stubbable(k.target) ? ensure_stub(k.target) : nullptr;
        // (a callee that can't be stubbed itself, e.g. a test-hooked function of the family, or
        // an unrelocatable prologue: the PLT entry the call went through, where the guest's call
        // goes too)
        if (!n && k.via != k.target && fam_.stubbable(k.via) && (n = ensure_stub(k.via))) {
            k.target = k.via;
            std::lock_guard lk(g_plt_mu);
            g_plt_lands.try_emplace(k.via, k.lands);
        }
        if (!n) {
            char b[80];
            snprintf(b, sizeof b, "can't stub callee %llx", (unsigned long long)(k.target - main_lib()->base));
            *why = b;
            return false;
        }
        names_.push_back(n);
    }
    return true;
}

// A replay's starting memory: the blocks the native run freed as they were (journaled), then
// the regions as before.
void Check::prep(Journal& j) {
    for (size_t q = rec_.calls.size(); q-- > 0;) {
        Call& k = rec_.calls[q];
        if (k.freed_at) j.write(k.freed_at, k.freed);
    }
    regions_.restore(pre_);
}

void Check::restore_fresh(Journal& j, const Call& k) {
    size_t o = 0;
    for (size_t q = 0; q < k.nfresh; q++) {
        auto [a, n] = rec_.fresh.r[q];
        j.write(a, std::vector<u8>(k.fresh_after.begin() + o, k.fresh_after.begin() + o + n));
        o += n;
    }
}

void Check::rewind() {
    if (rewound_) return;
    rewound_ = true;
    g_rewinding++;
    g_rewind_epoch++;
}

void Check::dump_record() const {
    for (size_t q = 0; q < rec_.calls.size(); q++) {
        const Call& k = rec_.calls[q];
        LOGI(fam_.log_tag.c_str(), "  rec %zu %llx x0 %llx x1 %llx x2 %llx x8 %llx sp %llx -> %llx bufs %zu", q, (unsigned long long)(k.target - main_lib()->base),
             (unsigned long long)k.x[0], (unsigned long long)k.x[1], (unsigned long long)k.x[2], (unsigned long long)k.x[8], (unsigned long long)k.sp,
             (unsigned long long)k.rx0, k.bufs.size());
        for (auto& bf : k.bufs) {
            std::string h;
            char hb[4];
            for (size_t j = 0; j < 24 && j < bf.after.size(); j++) snprintf(hb, sizeof hb, "%02x", bf.after[j]), h += hb;
            h += " (was ";
            for (size_t j = 0; j < 24 && j < bf.before.size(); j++) snprintf(hb, sizeof hb, "%02x", bf.before[j]), h += hb;
            LOGI(fam_.log_tag.c_str(), "    buf x%d at %llx: %s)", bf.reg, (unsigned long long)k.x[bf.reg], h.c_str());
        }
    }
}

// A replay stub's answer: the next recorded call, checked (target, arguments) and played back
// (stack buffers, patches, the returned object, the regions, the fresh blocks, the results).
// `at` is the address of the stub that answered (each stub name is answered with its own), not the
// CPU's pc - 4: that is the stub only for a call through the JIT (its SVC); a direct native->native
// call (guest_call's hooked-function path, e.g. a native the original reaches calling a recorded
// callee) leaves pc at its caller.
void Check::answer(Run& run, Journal& journal, size_t& next, size_t& extra, Cpu& cc, u64 at) {
    auto& errs = run.errs;
    char b[256];
    if (fam_.dump) {
        LOGI(fam_.log_tag.c_str(), "  hit %zu %llx x0 %llx x1 %llx x2 %llx x8 %llx sp %llx", next, (unsigned long long)(at - main_lib()->base), (unsigned long long)cc.x(0),
             (unsigned long long)cc.x(1), (unsigned long long)cc.x(2), (unsigned long long)cc.x(8), (unsigned long long)cc.sp());
        for (int a : {0, 1, 8})
            if (cc.x(a) >= cc.sp() && in_stack(cc.x(a), cc.sp())) {
                std::string h;
                char hb[4];
                for (int j = 0; j < 24; j++) snprintf(hb, sizeof hb, "%02x", ((const u8*)cc.x(a))[j]), h += hb;
                LOGI(fam_.log_tag.c_str(), "    at x%d: %s", a, h.c_str());
            }
    }
    if (next >= rec_.calls.size()) {
        snprintf(b, sizeof b, "extra call to %llx", (unsigned long long)(at - main_lib()->base));
        if (errs.size() < 4) errs.push_back(b);
        if (++extra > (size_t)kRunaway) {
            if (extra == (size_t)kRunaway + 1) errs.push_back("runaway replay stopped");
            stop_runaway(cc);
        }
        return;
    }
    Call& k = rec_.calls[next++];
    if (k.target != at) {
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
    for (auto& bf : k.bufs) {
        u64 dst = cc.x(bf.reg);
        if (dst >= cc.sp() && in_stack(dst, cc.sp())) write_back(bf, dst);
    }
    for (auto& pt : k.patches) memcpy((void*)pt.a, &pt.v, pt.n);
    if (!k.ret_obj.empty()) journal.write(k.rx0, k.ret_obj);
    regions_.restore(k.obj_after);
    restore_fresh(journal, k);
    cc.set_x(0, k.rx0);
    cc.set_x(1, k.rx1);
    for (int a = 0; a < 4; a++) cc.set_v(a, to_v128(k.rv[a]));
}

// The original against the replay stubs (no side effects outside the snapshot regions but what
// the native run wrote as well), from the state in pre_.
Check::Run Check::replay() {
    Run run;
    Journal journal;
    rewind();
    prep(journal);
    size_t next = 0, extra = 0;
    {
        ReplaySession ss;
        if (fam_.dump) dump_record();
        for (size_t q = 0; q < names_.size(); q++) {
            u64 tgt = rec_.calls[q].target;
            ss.answer(names_[q], [this, &run, &journal, &next, &extra, tgt](Cpu& cc) { answer(run, journal, next, extra, cc, tgt); });
        }
        // (also where the call went in: the JIT may have compiled a lone B together with its
        // target's first instructions, as one block keyed by the B)
        for (auto& k : rec_.calls) drop_stale_code(k.target), drop_stale_code(k.via);
        memcpy((void*)(sp0_ - kFrameSnap), stack0_.data(), kFrameSnap);
        GuestResult g = guest_call_at_sp(e_.orig, x_, v_, x_[8], sp0_);
        run.x0 = g.x0;
        run.v0 = g.v0;
    }
    if (next != rec_.calls.size() && run.errs.empty())
        run.errs.push_back("original made " + std::to_string(next) + " of " + std::to_string(rec_.calls.size()) + " calls");
    run.after = regions_.capture();
    run.fresh = rec_.fresh.capture();
    journal.undo();
    // (the native run's state again: see run()'s end; until then this counts as rewinding)
    return run;
}

// Results (a stack address compares by its offset from the entry SP; the replay's frames sit
// elsewhere) and the regions.
void Check::compare(const Run& g, u64 nx0, V128 nv0, const std::vector<u8>& nafter, std::vector<std::string>& errs) const {
    bool x0_same = g.x0 == nx0 || (in_stack(g.x0, sp0_) && in_stack(nx0, sp0_));
    if (e_.ret == kInt) x0_same = x0_same || (u32)g.x0 == (u32)nx0;  // (bool / int: only w0 is defined)
    if ((e_.ret & kInt) && !x0_same) {
        char b[96];
        snprintf(b, sizeof b, "x0 %llx, native %llx", (unsigned long long)g.x0, (unsigned long long)nx0);
        errs.push_back(b);
    }
    if ((e_.ret & kFloat) && g.v0.lo != nv0.lo) {
        char b[96];
        snprintf(b, sizeof b, "v0 %llx, native %llx", (unsigned long long)g.v0.lo, (unsigned long long)nv0.lo);
        errs.push_back(b);
    }
    if (g.after != nafter) {
        size_t k = 0;
        while (g.after[k] == nafter[k]) k++;
        char b[128];
        snprintf(b, sizeof b, "%s differs (guest %02x, native %02x)", regions_.where(k).c_str(), g.after[k], nafter[k]);
        errs.push_back(b);
    }
}

// The blocks callees allocated, as the replay left them, against the native run's.
void Check::compare_fresh(const Run& g, std::vector<std::string>& errs) const {
    if (g.fresh == fresh_final_) return;
    size_t k = 0;
    while (g.fresh[k] == fresh_final_[k]) k++;
    size_t blk = 0, off = k;
    while (off >= rec_.fresh.r[blk].second) off -= rec_.fresh.r[blk++].second;
    char b[128];
    snprintf(b, sizeof b, "allocated block %zu +0x%zx differs (guest %02x, native %02x)", blk, off, g.fresh[k], fresh_final_[k]);
    errs.push_back(b);
}

// A mismatch of a pure search counts only if it reproduces: other threads write some of this
// state at any time (e.g. an effect piece's models becoming ready on the loader thread between
// the native run and the replay). So the native code runs once more from the same snapshot,
// its outgoing calls answered from the record (Player: nothing executes twice). If it now
// agrees with the original, or doesn't repeat its own first run (its inputs changed under
// it), or the original doesn't repeat its first replay, the call is counted as a race (the
// reason); nullptr: a mismatch. (Only for natives that made no calls: their only writes are to the
// snapshot regions, so a rerun starts from exactly the state the first run saw, less other
// threads' writes. A native with calls may have changed memory outside the regions that its own
// rerun, and the replay, then see: no evidence of a race.)
const char* Check::race_of(const Run& g, const std::vector<std::string>& errs) {
    if (errs.empty() || !rec_.calls.empty()) return nullptr;
    for (int k = 0; k < 9; k++) c_.set_x(k, x_[k]);
    for (int k = 0; k < 8; k++) c_.set_v(k, v_[k]);
    Player pl;
    Journal pj;
    pl.rec = &rec_;
    pl.journal = &pj;
    rewind();
    prep(pj);
    t_play = &pl;
    try {
        e_.run(c_);
    } catch (const PlayDiverged&) {
        pl.bad = true;
    }
    t_play = nullptr;
    pj.undo();
    bool nbad = pl.bad || pl.next != rec_.calls.size();
    u64 nx0 = c_.x(0);
    V128 nv0 = c_.v(0);
    std::vector<u8> nafter = regions_.capture();
    std::vector<std::string> e2;
    compare(g, nx0, nv0, nafter, e2);
    bool same_x0 = !(e_.ret & kInt) || (e_.ret == kInt ? (u32)nx0 == (u32)res_x0_ : nx0 == res_x0_);
    bool same_v0 = !(e_.ret & kFloat) || nv0.lo == res_v_[0].lo;
    if (!nbad && g.errs.empty() && e2.empty()) return "native rerun agrees";
    if (nbad || !same_x0 || !same_v0 || nafter != after_) return "native rerun differs from its first run";
    Run g2 = replay();
    if (g2.errs != g.errs || g2.x0 != g.x0 || g2.v0.lo != g.v0.lo || g2.after != g.after) return "original's rerun differs from its first";
    return nullptr;
}

void Check::count(const std::vector<std::string>& errs, const char* race) {
    if (errs.empty()) {
        fam_.stats.ok++;
        e_.ok++;
        return;
    }
    std::string s;
    for (auto& m : errs) s += m + "; ";
    s += "(" + std::to_string(rec_.calls.size()) + " calls)";
    if (race) {
        u64 n = ++fam_.stats.races;
        e_.races++;
        if (n <= 60) LOGI(fam_.log_tag.c_str(), "race %s (thread %ld): %s; %s", e_.sym, (long)gettid(), s.c_str(), race);
    } else {
        e_.bad++;
        fam_.on_mismatch(e_, s);
        u64 n = ++fam_.stats.bad;
        if (n <= 60) LOGI(fam_.log_tag.c_str(), "MISMATCH %s (thread %ld): %s", e_.sym, (long)gettid(), s.c_str());
    }
}

void Check::run() {
    t_busy = true;
    if (fam_.trace) LOGI(fam_.log_tag.c_str(), "check %s x0=%llx (thread %ld)", e_.sym, (unsigned long long)c_.x(0), (long)gettid());
    snapshot();
    record();
    std::string why = rec_.overflow ? "more than kMaxRecord bytes of snapshots" : fam_.unreplayable(e_.sym) ? "unreplayable" : "";
    if (why.empty()) stub_callees(&why);
    fam_.stats.checks++;
    e_.checks++;
    if (!why.empty()) {
        fam_.stats.skipped++;
        e_.skipped++;
        fam_.on_skip(e_, why);
        t_busy = false;
        totals(fam_);
        return;  // the native run stands
    }
    Run g = replay();
    std::vector<std::string> errs = g.errs;
    compare(g, res_x0_, res_v_[0], after_, errs);
    compare_fresh(g, errs);
    const char* race = race_of(g, errs);
    // (back to the native run's state: only what the replays changed, so memory the native run
    // freed, e.g. a removed node, isn't written again when the replay left it alone)
    regions_.restore_diff(regions_.capture(), after_);
    if (rewound_) g_rewinding--;
    if (!errs.empty() && !race && overlapped_) race = "another thread's replay was rewinding memory during the native run";
    c_.set_x(0, res_x0_);
    c_.set_x(1, res_x1_);
    for (int k = 0; k < 4; k++) c_.set_v(k, res_v_[k]);
    count(errs, race);
    t_busy = false;
    totals(fam_);
}

void check(Cpu& c, int i) {
    Entry& e = g_entries[i];
    Family& fam = *e.fam;
    if (t_busy || !e.orig || !fam.only.match(e.sym) || (fam.budget && e.checks >= (u64)fam.budget) || e.calls++ % fam.every) return e.run(c);
    Check(c, e).run();
}

}  // namespace
}  // namespace soa::live
