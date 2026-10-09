// Differential tests of the SoundManager list natives (audio_sound_manager.cpp): two private managers
// (the three lists' TList vtables and sentinels, their FastCriticalSections by the guest's constructor),
// one driven through the guest functions (no natives in --selftest), the other through the native
// members, by the same random sequence of AddSoundCommand / InsertSoundCommand / RemoveSoundCommand /
// ArrangeCommandList / ProcessCommandList / AddSoundHandle / RemoveSoundHandle / QuerySoundHandle /
// UpdateAllSoundStatus / AddDeletingSoundObject / FlushDeletingSoundObject over private pools of
// commands, handles and sound objects (some streaming, their stream's read in flight or not).
// SoundCommand::ArrangeCommand / ProcessCommand are stubbed with results that depend only on the command
// (ProcessCommand sometimes hands back a follow-up command from a spare pool), the pool releases and
// UpdateSoundStatus are logged. The logs (nodes by index), the lists, the counts and the streams' abort
// flags must match after every step.
#include <cstring>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "soaruntime/core/cpu.h"
#include "native/audio/audio_layout.h"
#include "native/common/guest_stub.h"
#include "native/common/test.h"

using namespace soa;
using namespace soa::native;
using namespace soa::native::audio;

namespace {

constexpr int kCmds = 40, kSpare = 24, kHandles = 24, kObjects = 24;

struct Side {
    std::unique_ptr<SoundManager> m{new SoundManager};
    SoundCommand cmds[kCmds + kSpare];
    SoundHandle handles[kHandles];
    SoundObject objs[kObjects];
    AudioPlayer players[kObjects];
    WaveVoiceBase voices[kObjects];
    WaveBuffer buffers[kObjects];
    std::unique_ptr<WaveStreamView[]> streams{new WaveStreamView[kObjects]};
    int next_spare = 0;
    std::vector<std::string> log;

    std::string name(u64 p) const {
        for (int i = 0; i < kCmds + kSpare; i++)
            if (p == (u64)&cmds[i]) return "cmd" + std::to_string(i);
        for (int i = 0; i < kHandles; i++)
            if (p == (u64)&handles[i]) return "handle" + std::to_string(i);
        for (int i = 0; i < kObjects; i++)
            if (p == (u64)&objs[i]) return "obj" + std::to_string(i);
        if (p == (u64)&m->m_commands.m_sentinel) return "cmd-sentinel";
        if (p == (u64)&m->m_handles.m_sentinel) return "handle-sentinel";
        if (p == (u64)&m->m_deleting.m_sentinel) return "obj-sentinel";
        return p ? "?" : "null";
    }
    int cmd_index(u64 p) const {
        for (int i = 0; i < kCmds + kSpare; i++)
            if (p == (u64)&cmds[i]) return i;
        return -1;
    }
    template <typename T>
    std::vector<std::string> list(TList<T>& l) const {
        std::vector<std::string> r;
        for (T* n = l.begin(); n != l.end() && r.size() < 200; n = n->m_next) r.push_back(name((u64)n));
        r.push_back("count " + std::to_string(l.m_count));
        return r;
    }
};

template <typename T>
void init_list(TList<T>& l, u64 vtable, u64 node_vtable) {
    l.vtable = (const void*)vtable;
    std::memset((void*)&l.m_sentinel, 0, sizeof l.m_sentinel);
    *reinterpret_cast<u64*>(&l.m_sentinel) = node_vtable;
    l.m_sentinel.m_prev = l.m_sentinel.m_next = &l.m_sentinel;
    l.m_count = 0;
}

struct Rig {
    TestContext& t;
    Side g, n;
    std::map<std::string, int> seen;  // the guest log's kinds, for the coverage check

    explicit Rig(TestContext& tc) : t(tc) {
        stub("_ZN4Aska12SoundCommand14ArrangeCommandEPNS_5TListIS0_EE", "audio.t.arrange-command", 2);
        stub("_ZN4Aska12SoundCommand14ProcessCommandEPPS0_", "audio.t.process-command", 2);
        stub("_ZN4Aska11SoundServer19ReleaseSoundCommandEPNS_12SoundCommandE", "audio.t.release-command", 2);
        stub("_ZN4Aska11SoundObject17UpdateSoundStatusEv", "audio.t.update-status", 1);
        stub("_ZN4Aska11SoundServer18ReleaseSoundHandleEPNS_11SoundHandleE", "audio.t.release-handle", 2);
        stub("_ZN4Aska11SoundServer18ReleaseSoundObjectEPNS_11SoundObjectE", "audio.t.release-object", 2);
        // the objects: random types, players with or without a voice and a stream
        std::vector<u32> types(kObjects);
        std::vector<int> chain(kObjects), pending(kObjects);
        for (int i = 0; i < kObjects; i++) {
            types[i] = (u32)t.rand_int(0, 15);
            chain[i] = t.rand_int(0, 4);  // 0: no player, 1: no voice, 2: no stream, 3-4: a stream
            pending[i] = t.rand_int(0, 2);
        }
        for (Side* s : {&g, &n}) {
            SoundManager& m = *s->m;
            std::memset((void*)&m, 0, sizeof m);
            for (FastCriticalSection* cs : {&m.m_commandCs, &m.m_handleCs, &m.m_deletingCs}) t.call("_ZN4Aska19FastCriticalSectionC1Ev", {(u64)cs});
            init_list(m.m_commands, t.sym("_ZTVN4Aska5TListINS_12SoundCommandEEE") + 0x10, t.sym("_ZTVN4Aska12SoundCommandE") + 0x10);
            init_list(m.m_handles, t.sym("_ZTVN4Aska5TListINS_11SoundHandleEEE") + 0x10, t.sym("_ZTVN4Aska11SoundHandleE") + 0x10);
            init_list(m.m_deleting, t.sym("_ZTVN4Aska5TListINS_11SoundObjectEEE") + 0x10, t.sym("_ZTVN4Aska11SoundObjectE") + 0x10);
            m.m_soundServer = reinterpret_cast<SoundServer*>(0x5e5e0000);
            std::memset((void*)s->cmds, 0, sizeof s->cmds);
            std::memset((void*)s->handles, 0, sizeof s->handles);
            std::memset((void*)s->objs, 0, sizeof s->objs);
            std::memset((void*)s->players, 0, sizeof s->players);
            std::memset((void*)s->voices, 0, sizeof s->voices);
            std::memset((void*)s->buffers, 0, sizeof s->buffers);
            std::memset((void*)s->streams.get(), 0, sizeof(WaveStreamView) * kObjects);
            for (int i = 0; i < kObjects; i++) {
                SoundObject& o = s->objs[i];
                o.m_type = types[i];
                if (chain[i] >= 1) o.m_player = &s->players[i];
                if (chain[i] >= 2) s->players[i].m_voice = &s->voices[i];
                if (chain[i] >= 2) s->voices[i].m_buffer = &s->buffers[i];
                if (chain[i] >= 3) s->buffers[i].m_stream = &s->streams[i];
                s->streams[i].m_pending = pending[i] == 2 ? 1 : 0;
            }
            for (int i = 0; i < kHandles; i++) s->handles[i].m_object = &s->objs[i % kObjects];
        }
    }
    ~Rig() {
        for (Side* s : {&g, &n})
            for (FastCriticalSection* cs : {&s->m->m_commandCs, &s->m->m_handleCs, &s->m->m_deletingCs})
                t.call("_ZN4Aska19FastCriticalSectionD1Ev", {(u64)cs});
    }

    struct Session {
        StubSession ss;
        explicit Session(Side& s) {
            ss.only = {"audio.t.arrange-command", "audio.t.process-command", "audio.t.release-command",
                       "audio.t.update-status",   "audio.t.release-handle",  "audio.t.release-object"};
            ss.behave["audio.t.arrange-command"] = [&s](Cpu& c) {
                int i = s.cmd_index(c.x(0));
                s.log.push_back("ArrangeCommand " + s.name(c.x(0)));
                c.set_x(0, (i * 7) % 5 == 0 ? 1 : 0x100);  // (only bit 0 counts)
            };
            ss.behave["audio.t.process-command"] = [&s](Cpu& c) {
                int i = s.cmd_index(c.x(0));
                u64 inserted = 0;
                if (i % 4 == 1 && s.next_spare < kSpare) inserted = (u64)&s.cmds[kCmds + s.next_spare++];
                *reinterpret_cast<u64*>(c.x(1)) = inserted;
                s.log.push_back("ProcessCommand " + s.name(c.x(0)) + " -> " + s.name(inserted));
                c.set_x(0, i % 3 == 0 ? 1 : 0);
            };
            ss.behave["audio.t.release-command"] = [&s](Cpu& c) { s.log.push_back("ReleaseSoundCommand " + s.name(c.x(1))); };
            ss.behave["audio.t.update-status"] = [&s](Cpu& c) { s.log.push_back("UpdateSoundStatus " + s.name(c.x(0))); };
            ss.behave["audio.t.release-handle"] = [&s](Cpu& c) { s.log.push_back("ReleaseSoundHandle " + s.name(c.x(1))); };
            ss.behave["audio.t.release-object"] = [&s](Cpu& c) { s.log.push_back("ReleaseSoundObject " + s.name(c.x(1))); };
        }
    };

    void compare(const std::string& what) {
        auto diff = [&](const std::vector<std::string>& a, const std::vector<std::string>& b, const char* which) {
            if (a == b) return;
            t.fail("%s: %s differ (guest %zu, native %zu)", what.c_str(), which, a.size(), b.size());
            for (size_t i = 0; i < a.size() || i < b.size(); i++)
                t.fail("  %s | %s", i < a.size() ? a[i].c_str() : "-", i < b.size() ? b[i].c_str() : "-");
        };
        diff(g.log, n.log, "logs");
        diff(g.list(g.m->m_commands), n.list(n.m->m_commands), "commands");
        diff(g.list(g.m->m_handles), n.list(n.m->m_handles), "handles");
        diff(g.list(g.m->m_deleting), n.list(n.m->m_deleting), "deleting objects");
        for (int i = 0; i < kObjects; i++)
            if (g.streams[i].m_abort != n.streams[i].m_abort) t.fail("%s: stream %d's abort flag differs", what.c_str(), i);
        for (Side* s : {&g, &n})
            for (FastCriticalSection* cs : {&s->m->m_commandCs, &s->m->m_handleCs, &s->m->m_deletingCs})
                if (cs->m_lock != FastCriticalSection::kFree) t.fail("%s: a lock left held", what.c_str());
        for (auto& l : g.log) seen[l.substr(0, l.find(' '))] += 1 + (l.find("-> cmd") != std::string::npos ? 1000 : 0);
        g.log.clear();
        n.log.clear();
    }
};

// A listed node by position (or the sentinel / null now and then), the same on both sides.
template <typename T>
T* pick(TList<T>& l, int pos) {
    if (pos == -1) return nullptr;
    if (pos == -2) return l.end();
    T* p = l.begin();
    for (int i = 0; i < pos && p != l.end(); i++) p = p->m_next;
    return p == l.end() ? nullptr : p;
}

}  // namespace

NATIVE_TEST("audio/sound-manager-lists") {
    std::map<std::string, int> seen;
    for (int round = 0; round < 10 && !t.failures(); round++) {
        auto rig = std::make_unique<Rig>(t);
        Rig& r = *rig;
        int next_cmd = 0, next_handle = 0;
        for (int step = 0; step < 200 && !t.failures(); step++) {
            int op = t.rand_int(0, 14);
            std::string what = "round " + std::to_string(round) + " step " + std::to_string(step);
            auto both = [&](auto guest, auto native) {
                {
                    Rig::Session s(r.g);
                    guest(r.g);
                }
                {
                    Rig::Session s(r.n);
                    native(r.n);
                }
            };
            if (op <= 2 && next_cmd < kCmds) {
                int i = next_cmd++;
                what += " AddSoundCommand";
                both([&](Side& s) { t.call("_ZN4Aska12SoundManager15AddSoundCommandEPNS_12SoundCommandE", {(u64)s.m.get(), (u64)&s.cmds[i]}); },
                     [&](Side& s) { s.m->AddSoundCommand(&s.cmds[i]); });
            } else if (op == 3 && next_cmd < kCmds && r.g.m->m_commands.m_count > 0) {
                int i = next_cmd++;
                int pos = t.rand_int(0, r.g.m->m_commands.m_count - 1);
                what += " InsertSoundCommand";
                both([&](Side& s) {
                         t.call("_ZN4Aska12SoundManager18InsertSoundCommandEPNS_12SoundCommandES2_",
                                {(u64)s.m.get(), (u64)pick(s.m->m_commands, pos), (u64)&s.cmds[i]});
                     },
                     [&](Side& s) { s.m->InsertSoundCommand(pick(s.m->m_commands, pos), &s.cmds[i]); });
            } else if (op == 4) {
                int pos = t.rand_int(-2, std::max(0, r.g.m->m_commands.m_count - 1));
                what += " RemoveSoundCommand";
                both([&](Side& s) { t.call("_ZN4Aska12SoundManager18RemoveSoundCommandEPNS_12SoundCommandE", {(u64)s.m.get(), (u64)pick(s.m->m_commands, pos)}); },
                     [&](Side& s) { s.m->RemoveSoundCommand(pick(s.m->m_commands, pos)); });
            } else if (op == 5) {
                what += " ArrangeCommandList";
                both([&](Side& s) { t.call("_ZN4Aska12SoundManager18ArrangeCommandListEv", {(u64)s.m.get()}); },
                     [&](Side& s) { s.m->ArrangeCommandList(); });
            } else if (op == 6) {
                what += " ProcessCommandList";
                both([&](Side& s) { t.call("_ZN4Aska12SoundManager18ProcessCommandListEv", {(u64)s.m.get()}); },
                     [&](Side& s) { s.m->ProcessCommandList(); });
            } else if (op == 7 && next_handle < kHandles) {
                int i = next_handle++;
                what += " AddSoundHandle";
                both([&](Side& s) { t.call("_ZN4Aska12SoundManager14AddSoundHandleEPNS_11SoundHandleE", {(u64)s.m.get(), (u64)&s.handles[i]}); },
                     [&](Side& s) { s.m->AddSoundHandle(&s.handles[i]); });
            } else if (op == 8) {
                int pos = t.rand_int(-2, std::max(0, r.g.m->m_handles.m_count - 1));
                what += " RemoveSoundHandle";
                both([&](Side& s) { t.call("_ZN4Aska12SoundManager17RemoveSoundHandleEPNS_11SoundHandleE", {(u64)s.m.get(), (u64)pick(s.m->m_handles, pos)}); },
                     [&](Side& s) { s.m->RemoveSoundHandle(pick(s.m->m_handles, pos)); });
            } else if (op == 9) {
                int i = t.rand_int(0, kObjects - 1);
                std::string gq = r.g.name(t.call("_ZNK4Aska12SoundManager16QuerySoundHandleEPNS_11SoundObjectE", {(u64)r.g.m.get(), (u64)&r.g.objs[i]}));
                std::string nq = r.n.name((u64)r.n.m->QuerySoundHandle(&r.n.objs[i]));
                if (gq != nq) t.fail("%s QuerySoundHandle(obj%d): guest %s native %s", what.c_str(), i, gq.c_str(), nq.c_str());
            } else if (op == 10) {
                what += " UpdateAllSoundStatus";
                both([&](Side& s) { t.call("_ZN4Aska12SoundManager20UpdateAllSoundStatusEv", {(u64)s.m.get()}); },
                     [&](Side& s) { s.m->UpdateAllSoundStatus(); });
            } else if (op <= 12) {
                int i = t.rand_int(0, kObjects - 1);
                what += " AddDeletingSoundObject";
                both([&](Side& s) { t.call("_ZN4Aska12SoundManager22AddDeletingSoundObjectEPNS_11SoundObjectE", {(u64)s.m.get(), (u64)&s.objs[i]}); },
                     [&](Side& s) { s.m->AddDeletingSoundObject(&s.objs[i]); });
            } else if (op == 13) {
                u8 flags = (u8)t.rand_int(0, 7);
                r.g.m->m_flags1234 = r.n.m->m_flags1234 = flags;
                what += " FlushDeletingSoundObject";
                both([&](Side& s) { t.call("_ZN4Aska12SoundManager24FlushDeletingSoundObjectEv", {(u64)s.m.get()}); },
                     [&](Side& s) { s.m->FlushDeletingSoundObject(); });
            } else {
                int i = t.rand_int(0, kObjects - 1);
                r.g.streams[i].m_pending = r.n.streams[i].m_pending = t.rand_int(0, 1);
            }
            r.compare(what);
        }
        for (auto& [k, v] : r.seen) seen[k] += v;
    }
    for (const char* k : {"ArrangeCommand", "ProcessCommand", "ReleaseSoundCommand", "UpdateSoundStatus", "ReleaseSoundHandle", "ReleaseSoundObject"})
        if (!seen[k]) t.fail("never reached: %s", k);
    if (seen["ProcessCommand"] < 1000) t.fail("no follow-up command was inserted");
}
