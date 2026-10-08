// Aska::SoundManager's lists (port/decomp/audio/sound_manager.c; the layouts in audio_layout.h): the
// command list (requests from the game threads, run by the sound thread), the handle list (one per live
// sound object) and the deleting list (objects waiting to go back to SoundServer's pool), each under a
// FastCriticalSection of its own (the guest inlines its enter / leave everywhere: sync's Enter / Leave
// on the same words, so the guest code still using these lists and the natives exclude each other).
//
// The walkers (ArrangeCommandList, ProcessCommandList, UpdateAllSoundStatus) hold the lock only to step
// to the next node, so commands added meanwhile by the game thread are run in the same pass; the
// commands, statuses and pool calls themselves are guest code (guest calls).
#include <algorithm>
#include <cstring>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "core/cpu.h"
#include "native/audio/audio_check.h"
#include "native/audio/audio_layout.h"
#include "native/common/guest_std.h"
#include "native/common/live_check.h"
#include "native/common/native_method.h"

namespace soa::native::audio {

namespace {

struct ManagerFns {
    u64 arrange_command = guest::sym("_ZN4Aska12SoundCommand14ArrangeCommandEPNS_5TListIS0_EE");
    u64 process_command = guest::sym("_ZN4Aska12SoundCommand14ProcessCommandEPPS0_");
    u64 release_command = guest::sym("_ZN4Aska11SoundServer19ReleaseSoundCommandEPNS_12SoundCommandE");
    u64 update_status = guest::sym("_ZN4Aska11SoundObject17UpdateSoundStatusEv");
    u64 release_handle = guest::sym("_ZN4Aska11SoundServer18ReleaseSoundHandleEPNS_11SoundHandleE");
    u64 release_object = guest::sym("_ZN4Aska11SoundServer18ReleaseSoundObjectEPNS_11SoundObjectE");
};
const ManagerFns& fns() {
    static const ManagerFns f;
    return f;
}

// What a checked run did (live check only; null otherwise): its outgoing calls with their results, and
// the nodes it stepped to.
struct ManagerObs {
    struct Call {
        std::string what;
        u64 a = 0, b = 0;     // the arguments (nodes, objects)
        u64 result = 0;       // ArrangeCommand / ProcessCommand's result
        u64 inserted = 0;     // ProcessCommand's follow-up command
        bool operator==(const Call& o) const { return what == o.what && a == o.a && b == o.b; }
    };
    std::vector<Call> calls;
    std::vector<u64> visited;
    // The one-node methods: the list as they left it, under its lock (another thread may change it
    // right after: the sound thread runs and removes the commands the game thread adds).
    bool has_post = false;
    std::vector<u64> post;
    s32 post_count = 0;
};
thread_local ManagerObs* t_mobs = nullptr;

template <typename T>
void capture_post(TList<T>& l) {
    if (!t_mobs) return;
    t_mobs->has_post = true;
    t_mobs->post.clear();
    for (T* n = l.begin(); n && n != l.end() && t_mobs->post.size() < 4096; n = n->m_next) t_mobs->post.push_back((u64)n);
    t_mobs->post_count = l.m_count;
}

void log_call(const char* what, u64 a, u64 b = 0, u64 result = 0, u64 inserted = 0) {
    if (t_mobs) t_mobs->calls.push_back({what, a, b, result, inserted});
}

}  // namespace

// ---- The command list ----

void SoundManager::AddSoundCommand(SoundCommand* c) {
    m_commandCs.Enter();
    m_commands.Add(c);
    capture_post(m_commands);
    m_commandCs.Leave();
}

void SoundManager::InsertSoundCommand(SoundCommand* after, SoundCommand* c) {
    m_commandCs.Enter();
    SoundCommand* next = after->m_next;
    c->m_prev = after;
    c->m_next = next;
    next->m_prev = c;
    after->m_next = c;
    m_commands.m_count++;
    capture_post(m_commands);
    m_commandCs.Leave();
}

void SoundManager::RemoveSoundCommand(SoundCommand* c) {
    m_commandCs.Enter();
    if (c != m_commands.end() && c) m_commands.Delete(c);
    capture_post(m_commands);
    m_commandCs.Leave();
}

// Drops the commands whose sound object is gone (SoundCommand::ArrangeCommand decides).
void SoundManager::ArrangeCommandList() {
    m_commandCs.Enter();
    SoundCommand* c = m_commands.begin();
    m_commandCs.Leave();
    while (c != m_commands.end()) {
        if (t_mobs) t_mobs->visited.push_back((u64)c);
        m_commandCs.Enter();
        SoundCommand* next = c->m_next;
        m_commandCs.Leave();
        bool drop = (guest_call(fns().arrange_command, {(u64)c, (u64)&m_commands}) & 1) != 0;
        log_call("ArrangeCommand", (u64)c, 0, drop);
        if (drop) {
            RemoveSoundCommand(c);
            log_call("ReleaseSoundCommand", (u64)c);
            guest_call(fns().release_command, {(u64)m_soundServer, (u64)c});
        }
        c = next;
    }
}

// Runs every command: a finished one leaves the list; a follow-up command it made goes after it and runs
// next.
void SoundManager::ProcessCommandList() {
    m_commandCs.Enter();
    SoundCommand* c = m_commands.begin();
    m_commandCs.Leave();
    while (c != m_commands.end()) {
        if (t_mobs) t_mobs->visited.push_back((u64)c);
        m_commandCs.Enter();
        SoundCommand* next = c->m_next;
        m_commandCs.Leave();
        SoundCommand* inserted = nullptr;
        bool done = (guest_call(fns().process_command, {(u64)c, (u64)&inserted}) & 1) != 0;
        log_call("ProcessCommand", (u64)c, 0, done, (u64)inserted);
        if (inserted) InsertSoundCommand(c, inserted);
        if (done) {
            RemoveSoundCommand(c);
            log_call("ReleaseSoundCommand", (u64)c);
            guest_call(fns().release_command, {(u64)m_soundServer, (u64)c});
        }
        c = inserted ? inserted : next;
        m_commandCs.Enter();  // (an empty lock pair in the guest)
        m_commandCs.Leave();
    }
}

// ---- The handle list ----

void SoundManager::UpdateAllSoundStatus() {
    m_handleCs.Enter();
    SoundHandle* h = m_handles.begin();
    m_handleCs.Leave();
    while (h != m_handles.end()) {
        if (t_mobs) t_mobs->visited.push_back((u64)h);
        m_handleCs.Enter();
        SoundHandle* next = h->m_next;
        m_handleCs.Leave();
        if (SoundObject* o = h->m_object) {
            log_call("UpdateSoundStatus", (u64)o);
            guest_call(fns().update_status, {(u64)o});
        }
        h = next;
    }
}

SoundHandle* SoundManager::QuerySoundHandle(SoundObject* o) const {
    auto* self = const_cast<SoundManager*>(this);
    self->m_handleCs.Enter();
    SoundHandle* found = nullptr;
    for (SoundHandle* h = self->m_handles.begin(); h != self->m_handles.end(); h = h->m_next)
        if (h->m_object == o) {
            found = h;
            break;
        }
    self->m_handleCs.Leave();
    return found;
}

void SoundManager::AddSoundHandle(SoundHandle* h) {
    m_handleCs.Enter();
    m_handles.Add(h);
    capture_post(m_handles);
    m_handleCs.Leave();
}

void SoundManager::RemoveSoundHandle(SoundHandle* h) {
    m_handleCs.Enter();
    if (h != m_handles.end() && h) m_handles.Delete(h);
    capture_post(m_handles);
    m_handleCs.Leave();
}

// ---- The deleting list ----

namespace {
// The stream behind a streaming object's voice, or null (the guest doesn't check the wave buffer).
WaveStreamView* stream_of(const SoundObject* o) {
    if (!(o->m_type & SoundObject::kTypeStreaming) || !o->m_player || !o->m_player->m_voice) return nullptr;
    return o->m_player->m_voice->m_buffer->m_stream;
}
}  // namespace

void SoundManager::AddDeletingSoundObject(SoundObject* o) {
    m_deletingCs.Enter();
    bool listed = false;
    for (SoundObject* p = m_deleting.begin(); p != m_deleting.end(); p = p->m_next)
        if (p == o) {
            listed = true;
            break;
        }
    if (!listed) {
        if (WaveStreamView* s = stream_of(o)) s->m_abort = 1;
        m_deleting.Add(o);
    }
    capture_post(m_deleting);
    m_deletingCs.Leave();
}

// Returns the deleting objects to the pool, except the streaming ones whose stream still has a read in
// flight. (An object without a handle stays out of the list but isn't released: the guest's order.)
void SoundManager::FlushDeletingSoundObject() {
    if ((~m_flags1234 & kFlushReady) != 0) return;
    m_deletingCs.Enter();
    for (SoundObject* o = m_deleting.begin(); o != m_deleting.end();) {
        SoundObject* next = o->m_next;
        if (t_mobs) t_mobs->visited.push_back((u64)o);
        WaveStreamView* s = stream_of(o);
        if (!s || s->m_pending == 0) {
            m_deleting.Delete(o);
            if (SoundHandle* h = QuerySoundHandle(o)) {
                RemoveSoundHandle(h);
                log_call("ReleaseSoundHandle", (u64)h);
                guest_call(fns().release_handle, {(u64)m_soundServer, (u64)h});
                log_call("ReleaseSoundObject", (u64)o);
                guest_call(fns().release_object, {(u64)m_soundServer, (u64)o});
            }
        }
        o = next;
    }
    m_deletingCs.Leave();
}

// ---- The live check (audio_check.h) ----
//
// The native for real (its guest calls and their results logged, the nodes it stepped to recorded),
// then the guest original on a shadow manager: the manager's bytes, its three lists rebuilt over copies
// of their nodes as they were before the native ran (taken under each list's lock), the locks free. The
// guest calls are answered by the check's stubs on this thread, replaying the native run's results
// (ArrangeCommand / ProcessCommand, whose follow-up commands become shadow copies too). The calls (shadow
// nodes mapped back), the lists left and the counts must match. A node the native stepped to or left
// in a list that wasn't there before came from another thread meanwhile: a race. QuerySoundHandle is a
// getter (check_getter).

namespace {

CheckedFn g_arrange("_ZN4Aska12SoundManager18ArrangeCommandListEv"), g_process("_ZN4Aska12SoundManager18ProcessCommandListEv"),
    g_add_cmd("_ZN4Aska12SoundManager15AddSoundCommandEPNS_12SoundCommandE"),
    g_insert_cmd("_ZN4Aska12SoundManager18InsertSoundCommandEPNS_12SoundCommandES2_"),
    g_remove_cmd("_ZN4Aska12SoundManager18RemoveSoundCommandEPNS_12SoundCommandE"), g_update("_ZN4Aska12SoundManager20UpdateAllSoundStatusEv"),
    g_query("_ZNK4Aska12SoundManager16QuerySoundHandleEPNS_11SoundObjectE"), g_add_handle("_ZN4Aska12SoundManager14AddSoundHandleEPNS_11SoundHandleE"),
    g_remove_handle("_ZN4Aska12SoundManager17RemoveSoundHandleEPNS_11SoundHandleE"),
    g_add_deleting("_ZN4Aska12SoundManager22AddDeletingSoundObjectEPNS_11SoundObjectE"),
    g_flush("_ZN4Aska12SoundManager24FlushDeletingSoundObjectEv");

constexpr size_t kMaxNodes = 2048;

// One list's snapshot and its shadow copies.
template <typename T>
struct ListShadow {
    std::vector<T*> real;      // the nodes before, in order
    std::vector<T> copies;     // their bytes before; then the shadow nodes
    std::map<u64, T*> extra;   // nodes the shadow run gets that weren't listed (keyed by the real pointer)
    std::vector<std::unique_ptr<T>> extra_store;
    bool too_long = false;

    void snapshot(TList<T>& l, FastCriticalSection& cs) {
        cs.Enter();
        for (T* n = l.begin(); n && n != l.end(); n = n->m_next) {
            if (real.size() >= kMaxNodes) {
                too_long = true;
                break;
            }
            real.push_back(n);
            copies.push_back(*n);
        }
        cs.Leave();
    }
    // Relinks the copies into the shadow list `l` (a byte copy of the real one).
    void relink(TList<T>& l) {
        T* prev = &l.m_sentinel;
        for (T& n : copies) {
            n.m_prev = prev;
            prev->m_next = &n;
            prev = &n;
        }
        prev->m_next = &l.m_sentinel;
        l.m_sentinel.m_prev = prev;
    }
    T* to_shadow(u64 p, const TList<T>& real_list, TList<T>& shadow_list) {
        for (size_t i = 0; i < real.size(); i++)
            if ((u64)real[i] == p) return &copies[i];
        if (p == (u64)&real_list.m_sentinel) return &shadow_list.m_sentinel;
        auto it = extra.find(p);
        return it != extra.end() ? it->second : reinterpret_cast<T*>(p);
    }
    u64 to_real(u64 p, const TList<T>& real_list, const TList<T>& shadow_list) const {
        for (size_t i = 0; i < copies.size(); i++)
            if ((u64)&copies[i] == p) return (u64)real[i];
        if (p == (u64)&shadow_list.m_sentinel) return (u64)&real_list.m_sentinel;
        for (auto& [r, s] : extra)
            if ((u64)s == p) return r;
        return p;
    }
    // A shadow node for a node that wasn't listed (a follow-up command): a copy of its bytes as given.
    T* add_extra(u64 real_ptr, const T& bytes) {
        extra_store.push_back(std::make_unique<T>(bytes));
        extra[real_ptr] = extra_store.back().get();
        return extra_store.back().get();
    }
    bool knows(u64 p) const { return std::find(real.begin(), real.end(), (T*)p) != real.end() || extra.count(p); }
};

// The lists a checked function works on (only those are snapshotted, under their own locks one at a
// time, and compared: a caller may hold another list's lock).
enum Lists : int { kCmds = 1, kHandles = 2, kDeleting = 4, kOneNode = 8 };  // kOneNode: compare the list the native left under its lock

struct ManagerShadow {
    std::unique_ptr<SoundManager> s{new SoundManager};
    SoundManager* real;
    int lists;
    ListShadow<SoundCommand> cmds;
    ListShadow<SoundHandle> handles;
    ListShadow<SoundObject> deleting;

    ManagerShadow(SoundManager* r, int which) : real(r), lists(which) {
        if (lists & kCmds) cmds.snapshot(r->m_commands, r->m_commandCs);
        if (lists & kHandles) handles.snapshot(r->m_handles, r->m_handleCs);
        if (lists & kDeleting) deleting.snapshot(r->m_deleting, r->m_deletingCs);
    }
    bool too_long() const { return cmds.too_long || handles.too_long || deleting.too_long; }
    // Builds the shadow manager (after the native ran: the real manager's other bytes as they are now).
    void build() {
        std::memcpy((void*)s.get(), real, sizeof(SoundManager));
        for (FastCriticalSection* cs : {&s->m_commandCs, &s->m_handleCs, &s->m_deletingCs}) {
            cs->m_lock = FastCriticalSection::kFree;
            cs->m_waiters = FastCriticalSection::kWaiterBias;
        }
        if (lists & kCmds) {
            s->m_commands.m_count = (s32)cmds.copies.size();
            cmds.relink(s->m_commands);
        }
        if (lists & kHandles) {
            s->m_handles.m_count = (s32)handles.copies.size();
            handles.relink(s->m_handles);
        }
        if (lists & kDeleting) {
            s->m_deleting.m_count = (s32)deleting.copies.size();
            deleting.relink(s->m_deleting);
        }
        // the shadow handles' and commands' objects: shadow deleting objects where listed
        for (SoundHandle& h : handles.copies) h.m_object = deleting.to_shadow((u64)h.m_object, real->m_deleting, s->m_deleting);
    }
    u64 to_real(u64 p) const {
        u64 r = cmds.to_real(p, real->m_commands, s->m_commands);
        if (r != p) return r;
        r = handles.to_real(p, real->m_handles, s->m_handles);
        if (r != p) return r;
        r = deleting.to_real(p, real->m_deleting, s->m_deleting);
        if (r != p) return r;
        if (p == (u64)&s->m_commands) return (u64)&real->m_commands;
        if (p == (u64)s.get()) return (u64)real;
        return p;
    }
};

// The list the native left (`post`: captured under the lock by a one-node method; else the live list,
// where a node the guest run kept and the live list lacks was removed by another thread: a race).
template <typename T>
std::string compare_list(ListShadow<T>& ls, TList<T>& real_list, TList<T>& shadow_list, const ManagerShadow& sh, const char* name,
                         bool* race, const ManagerObs* post) {
    std::vector<u64> left_real, left_sh;
    s32 real_count = real_list.m_count;
    if (post) {
        left_real = post->post;
        real_count = post->post_count;
    } else {
        for (T* n = real_list.begin(); n && n != real_list.end() && left_real.size() < kMaxNodes * 2; n = n->m_next) left_real.push_back((u64)n);
    }
    for (T* n = shadow_list.begin(); n && n != shadow_list.end() && left_sh.size() < kMaxNodes * 2; n = n->m_next)
        left_sh.push_back(sh.to_real((u64)n));
    for (u64 n : left_real)
        if (!ls.knows(n)) {
            *race = true;
            return std::string(name) + ": a node added by another thread";
        }
    if (!post)
        for (u64 n : left_sh)
            if (std::find(left_real.begin(), left_real.end(), n) == left_real.end()) {
                *race = true;
                return std::string(name) + ": a node removed by another thread";
            }
    if (left_real != left_sh)
        return std::string(name) + ": the list left differs (native " + std::to_string(left_real.size()) + ", guest " + std::to_string(left_sh.size()) + ")";
    if (real_count != shadow_list.m_count)
        return std::string(name) + ": count native " + std::to_string(real_count) + " guest " + std::to_string(shadow_list.m_count);
    return {};
}

// Runs the native for real and the guest original on the shadow, and compares.
template <typename Native, typename Guest>
void manager_check(CheckedFn& f, SoundManager* self, int lists, Native native, Guest guest_run) {
    const ManagerFns& g = fns();
    const u64 targets[] = {g.arrange_command, g.process_command, g.release_command, g.update_status, g.release_handle, g.release_object};
    const char* stubs[6];
    for (int i = 0; i < 6; i++)
        if (!(stubs[i] = live::ensure_stub(targets[i]))) {
            native();
            return live::check_result(f, live::Outcome::Skipped, "callees can't be stubbed");
        }
    live::CheckScope scope;
    ManagerShadow sh(self, lists);
    ManagerObs obs;
    t_mobs = &obs;
    native();
    t_mobs = nullptr;
    if (sh.too_long()) return live::check_result(f, live::Outcome::Skipped, "a list too long");
    for (u64 v : obs.visited)
        if (!sh.cmds.knows(v) && !sh.handles.knows(v) && !sh.deleting.knows(v)) {
            bool inserted = false;
            for (auto& c : obs.calls) inserted |= c.inserted == v;
            if (!inserted) return live::check_result(f, live::Outcome::Race, "a node added by another thread during the run");
        }
    // Follow-up commands: shadow copies of their bytes as the native's Insert found them (prev / next
    // are relinked by the shadow's Insert anyway).
    for (auto& c : obs.calls)
        if (c.inserted) sh.cmds.add_extra(c.inserted, *reinterpret_cast<const SoundCommand*>(c.inserted));
    sh.build();
    // The guest run's calls, answered from the native's log in order.
    std::vector<ManagerObs::Call> calls;
    size_t replay = 0;
    auto next_result = [&](const char* what, u64 a, u64* inserted) -> u64 {
        while (replay < obs.calls.size() && obs.calls[replay].what != what) replay++;
        if (replay >= obs.calls.size() || obs.calls[replay].a != a) return 0;
        if (inserted) *inserted = obs.calls[replay].inserted;
        return obs.calls[replay++].result;
    };
    {
        live::ReplaySession s;
        s.answer(stubs[0], [&](Cpu& cc) {
            u64 cmd = sh.to_real(cc.x(0));
            u64 r = next_result("ArrangeCommand", cmd, nullptr);
            calls.push_back({"ArrangeCommand", cmd, 0, r, 0});
            cc.set_x(0, r);
        });
        s.answer(stubs[1], [&](Cpu& cc) {
            u64 cmd = sh.to_real(cc.x(0)), ins = 0;
            u64 r = next_result("ProcessCommand", cmd, &ins);
            calls.push_back({"ProcessCommand", cmd, 0, r, ins});
            *reinterpret_cast<u64*>(cc.x(1)) = ins ? (u64)sh.cmds.to_shadow(ins, self->m_commands, sh.s->m_commands) : 0;
            cc.set_x(0, r);
        });
        s.answer(stubs[2], [&](Cpu& cc) { calls.push_back({"ReleaseSoundCommand", sh.to_real(cc.x(1))}); });
        s.answer(stubs[3], [&](Cpu& cc) { calls.push_back({"UpdateSoundStatus", sh.to_real(cc.x(0))}); });
        s.answer(stubs[4], [&](Cpu& cc) { calls.push_back({"ReleaseSoundHandle", sh.to_real(cc.x(1))}); });
        s.answer(stubs[5], [&](Cpu& cc) { calls.push_back({"ReleaseSoundObject", sh.to_real(cc.x(1))}); });
        for (u64 t : targets) live::drop_stale_code(t);
        guest_run(sh);
    }
    std::string why;
    if (!(calls == obs.calls)) {
        why = "calls: native " + std::to_string(obs.calls.size()) + " guest " + std::to_string(calls.size());
        for (size_t i = 0; i < calls.size() && i < obs.calls.size(); i++)
            if (!(calls[i] == obs.calls[i])) {
                why += " (first difference at " + std::to_string(i) + ": native " + obs.calls[i].what + " guest " + calls[i].what + ")";
                break;
            }
    }
    bool race = false;
    const ManagerObs* post = (lists & kOneNode) && obs.has_post ? &obs : nullptr;  // (a one-node method touches one list)
    if (why.empty() && (lists & kCmds)) why = compare_list(sh.cmds, self->m_commands, sh.s->m_commands, sh, "commands", &race, post);
    if (why.empty() && (lists & kHandles)) why = compare_list(sh.handles, self->m_handles, sh.s->m_handles, sh, "handles", &race, post);
    if (why.empty() && (lists & kDeleting)) why = compare_list(sh.deleting, self->m_deleting, sh.s->m_deleting, sh, "deleting", &race, post);
    if (race) return live::check_result(f, live::Outcome::Race, why);
    live::check_result(f, why.empty() ? live::Outcome::Ok : live::Outcome::Mismatch, why);
}

// The hooks. Each checked form: the native in a lambda, the guest original on the shadow.
template <void (SoundManager::*M)()>
void walker_checked(Cpu& c, CheckedFn& f, int lists) {
    if (!live::check_due(f)) return wrap_method<M>()(c);
    auto* self = reinterpret_cast<SoundManager*>(c.x(0));
    manager_check(f, self, lists, [&] { (self->*M)(); }, [&](ManagerShadow& sh) { guest_call(f.orig, {(u64)sh.s.get()}); });
}
void arrange_checked(Cpu& c) { walker_checked<&SoundManager::ArrangeCommandList>(c, g_arrange, kCmds); }
void process_checked(Cpu& c) { walker_checked<&SoundManager::ProcessCommandList>(c, g_process, kCmds); }
void update_checked(Cpu& c) { walker_checked<&SoundManager::UpdateAllSoundStatus>(c, g_update, kHandles); }
void flush_checked(Cpu& c) { walker_checked<&SoundManager::FlushDeletingSoundObject>(c, g_flush, kHandles | kDeleting); }

// The one-node forms: the node argument mapped to its shadow (a node not listed gets a shadow copy).
template <typename T, void (SoundManager::*M)(T*), ListShadow<T> ManagerShadow::*L, TList<T> SoundManager::*RL, int kLists>
void node_checked(Cpu& c, CheckedFn& f) {
    if (!live::check_due(f)) return wrap_method<M>()(c);
    auto* self = reinterpret_cast<SoundManager*>(c.x(0));
    u64 node = c.x(1);
    // a node that isn't in the list yet (Add) is copied before the native links it
    alignas(16) T before{};
    if (node) std::memcpy((void*)&before, (const void*)node, sizeof(T));
    manager_check(
        f, self, kLists | kOneNode, [&] { (self->*M)(reinterpret_cast<T*>(node)); },
        [&](ManagerShadow& sh) {
            ListShadow<T>& ls = sh.*L;
            u64 arg = node;
            if (node) {
                T* s = ls.to_shadow(node, self->*RL, sh.s.get()->*RL);
                if ((u64)s == node) s = ls.add_extra(node, before);
                arg = (u64)s;
            }
            guest_call(f.orig, {(u64)sh.s.get(), arg});
        });
}
void add_cmd_checked(Cpu& c) { node_checked<SoundCommand, &SoundManager::AddSoundCommand, &ManagerShadow::cmds, &SoundManager::m_commands, kCmds>(c, g_add_cmd); }
void remove_cmd_checked(Cpu& c) {
    node_checked<SoundCommand, &SoundManager::RemoveSoundCommand, &ManagerShadow::cmds, &SoundManager::m_commands, kCmds>(c, g_remove_cmd);
}
void add_handle_checked(Cpu& c) { node_checked<SoundHandle, &SoundManager::AddSoundHandle, &ManagerShadow::handles, &SoundManager::m_handles, kHandles>(c, g_add_handle); }
void remove_handle_checked(Cpu& c) {
    node_checked<SoundHandle, &SoundManager::RemoveSoundHandle, &ManagerShadow::handles, &SoundManager::m_handles, kHandles>(c, g_remove_handle);
}
void add_deleting_checked(Cpu& c) {
    node_checked<SoundObject, &SoundManager::AddDeletingSoundObject, &ManagerShadow::deleting, &SoundManager::m_deleting, kDeleting>(c, g_add_deleting);
}
void insert_cmd_checked(Cpu& c) {
    if (!live::check_due(g_insert_cmd)) return wrap_method<&SoundManager::InsertSoundCommand>()(c);
    auto* self = reinterpret_cast<SoundManager*>(c.x(0));
    u64 after = c.x(1), node = c.x(2);
    alignas(16) SoundCommand before{};
    std::memcpy((void*)&before, (const void*)node, sizeof before);
    manager_check(
        g_insert_cmd, self, kCmds | kOneNode, [&] { self->InsertSoundCommand(reinterpret_cast<SoundCommand*>(after), reinterpret_cast<SoundCommand*>(node)); },
        [&](ManagerShadow& sh) {
            SoundCommand* a = sh.cmds.to_shadow(after, self->m_commands, sh.s->m_commands);
            SoundCommand* n = sh.cmds.to_shadow(node, self->m_commands, sh.s->m_commands);
            if ((u64)n == node) n = sh.cmds.add_extra(node, before);
            guest_call(g_insert_cmd.orig, {(u64)sh.s.get(), (u64)a, (u64)n});
        });
}
void query_checked(Cpu& c) {
    if (!live::check_due(g_query)) return wrap_method<&SoundManager::QuerySoundHandle>()(c);
    live::check_getter(c, g_query, wrap_method<&SoundManager::QuerySoundHandle>(), ~0ull);
}

}  // namespace

NATIVE_FUNCTION_ORIG("_ZN4Aska12SoundManager18ArrangeCommandListEv", arrange_checked, "audio: Aska::SoundManager::ArrangeCommandList", &g_arrange.orig);
NATIVE_FUNCTION_ORIG("_ZN4Aska12SoundManager18ProcessCommandListEv", process_checked, "audio: Aska::SoundManager::ProcessCommandList", &g_process.orig);
NATIVE_FUNCTION_ORIG("_ZN4Aska12SoundManager15AddSoundCommandEPNS_12SoundCommandE", add_cmd_checked, "audio: Aska::SoundManager::AddSoundCommand",
                     &g_add_cmd.orig);
NATIVE_FUNCTION_ORIG("_ZN4Aska12SoundManager18InsertSoundCommandEPNS_12SoundCommandES2_", insert_cmd_checked,
                     "audio: Aska::SoundManager::InsertSoundCommand", &g_insert_cmd.orig);
NATIVE_FUNCTION_ORIG("_ZN4Aska12SoundManager18RemoveSoundCommandEPNS_12SoundCommandE", remove_cmd_checked,
                     "audio: Aska::SoundManager::RemoveSoundCommand", &g_remove_cmd.orig);
NATIVE_FUNCTION_ORIG("_ZN4Aska12SoundManager20UpdateAllSoundStatusEv", update_checked, "audio: Aska::SoundManager::UpdateAllSoundStatus", &g_update.orig);
NATIVE_FUNCTION_ORIG("_ZNK4Aska12SoundManager16QuerySoundHandleEPNS_11SoundObjectE", query_checked, "audio: Aska::SoundManager::QuerySoundHandle",
                     &g_query.orig);
NATIVE_FUNCTION_ORIG("_ZN4Aska12SoundManager14AddSoundHandleEPNS_11SoundHandleE", add_handle_checked, "audio: Aska::SoundManager::AddSoundHandle",
                     &g_add_handle.orig);
NATIVE_FUNCTION_ORIG("_ZN4Aska12SoundManager17RemoveSoundHandleEPNS_11SoundHandleE", remove_handle_checked,
                     "audio: Aska::SoundManager::RemoveSoundHandle", &g_remove_handle.orig);
NATIVE_FUNCTION_ORIG("_ZN4Aska12SoundManager22AddDeletingSoundObjectEPNS_11SoundObjectE", add_deleting_checked,
                     "audio: Aska::SoundManager::AddDeletingSoundObject", &g_add_deleting.orig);
NATIVE_FUNCTION_ORIG("_ZN4Aska12SoundManager24FlushDeletingSoundObjectEv", flush_checked, "audio: Aska::SoundManager::FlushDeletingSoundObject",
                     &g_flush.orig);

}  // namespace soa::native::audio
