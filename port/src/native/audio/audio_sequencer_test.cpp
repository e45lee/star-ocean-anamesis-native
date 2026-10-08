// Differential tests of the Sequencer2 natives (audio_sequencer.cpp): two private sequencers built by the
// guest's constructor over fake players, one driven through the guest functions (no natives in
// --selftest), the other through the native members, by the same random sequence of AddMessageNote
// (every message type and some unknown ones, times around the clock, NaN now and then), DeleteMessageNote
// (a listed note, or null), ArrangeMessageNote, ProcessMessageNote, AudioRun and player state changes.
// SoundServer::Acquire / ReleaseMessageNote are answered from a private pool per side and logged, and
// AudioPlayer::SendMessage is logged; after every step the logs (notes by pool index), the lists, the
// notes' bytes, the counts, the clocks and the waiting notifies must match.
#include <cmath>
#include <cstring>
#include <memory>
#include <string>
#include <vector>

#include "core/cpu.h"
#include "native/audio/audio_layout.h"
#include "native/common/guest_stub.h"
#include "native/common/test.h"

using namespace soa;
using namespace soa::native;
using namespace soa::native::audio;

namespace {

constexpr int kPool = 48;

struct Side {
    alignas(16) Sequencer2 seq;
    alignas(16) AudioPlayer player;
    alignas(16) AudioMessageNote pool[kPool];
    bool used[kPool] = {};
    std::vector<std::string> log;

    int index_of(u64 p) const {
        for (int i = 0; i < kPool; i++)
            if (p == (u64)&pool[i]) return i;
        if (p == (u64)&seq.m_sentinel) return -2;
        if (p == (u64)&seq.m_notify) return -3;
        return p ? -4 : -1;
    }
};

struct Rig {
    TestContext& t;
    Side g, n;

    explicit Rig(TestContext& tc) : t(tc) {
        stub("_ZN4Aska11SoundServer18AcquireMessageNoteEv", "audio.t.acquire", 1);
        stub("_ZN4Aska11SoundServer18ReleaseMessageNoteEPNS_16AudioMessageNoteE", "audio.t.release", 2);
        stub("_ZN4Aska11AudioPlayer11SendMessageEjPvS1_", "audio.t.send", 4);
        const u64 note_vtable = t.sym("_ZTVN4Aska16AudioMessageNoteE") + 0x10;
        for (Side* s : {&g, &n}) {
            std::memset((void*)&s->seq, 0, sizeof s->seq);
            t.call("_ZN4Aska10Sequencer2C1Ev", {(u64)&s->seq});
            std::memset((void*)&s->player, 0, sizeof s->player);
            s->seq.m_player = &s->player;
            for (auto& p : s->pool) {
                std::memset((void*)&p, 0, sizeof p);
                p.vtable = (const void*)note_vtable;
            }
        }
    }
    ~Rig() {
        for (Side* s : {&g, &n}) t.call("_ZN4Aska19FastCriticalSectionD1Ev", {(u64)&s->seq.m_cs});
    }

    // A stub session answering the pool and the player for one side.
    struct Session {
        StubSession ss;
        Session(Side& s) {
            ss.only = {"audio.t.acquire", "audio.t.release", "audio.t.send"};
            ss.behave["audio.t.acquire"] = [&s](Cpu& c) {
                int k = 0;
                while (k < kPool && s.used[k]) k++;
                s.log.push_back("acquire " + std::to_string(k < kPool ? k : -1));
                if (k < kPool) s.used[k] = true;
                c.set_x(0, k < kPool ? (u64)&s.pool[k] : 0);
            };
            ss.behave["audio.t.release"] = [&s](Cpu& c) {
                int k = s.index_of(c.x(1));
                s.log.push_back("release " + std::to_string(k));
                if (k >= 0) s.used[k] = false;
            };
            ss.behave["audio.t.send"] = [&s](Cpu& c) {
                s.log.push_back("send " + std::to_string((u32)c.x(1)) + " " + std::to_string(c.x(2)) + " " + std::to_string(c.x(3)));
            };
        }
    };

    void compare(const std::string& what) {
        if (g.log != n.log) {
            t.fail("%s: logs differ (guest %zu, native %zu)", what.c_str(), g.log.size(), n.log.size());
            for (size_t i = 0; i < g.log.size() || i < n.log.size(); i++)
                t.fail("  %s | %s", i < g.log.size() ? g.log[i].c_str() : "-", i < n.log.size() ? n.log[i].c_str() : "-");
        }
        std::vector<int> lg, ln;
        for (auto* p = g.seq.m_sentinel.m_next; p != &g.seq.m_sentinel && lg.size() < 100; p = p->m_next) lg.push_back(g.index_of((u64)p));
        for (auto* p = n.seq.m_sentinel.m_next; p != &n.seq.m_sentinel && ln.size() < 100; p = p->m_next) ln.push_back(n.index_of((u64)p));
        if (lg != ln) t.fail("%s: lists differ (guest %zu, native %zu notes)", what.c_str(), lg.size(), ln.size());
        for (int k = 0; k < kPool; k++) {
            const AudioMessageNote &a = g.pool[k], &b = n.pool[k];
            if (g.index_of((u64)a.m_prev) != n.index_of((u64)b.m_prev) || g.index_of((u64)a.m_next) != n.index_of((u64)b.m_next) ||
                g.index_of((u64)a.m_waitNotify) != n.index_of((u64)b.m_waitNotify) || a.m_message != b.m_message || a.m_arg0 != b.m_arg0 ||
                a.m_arg1 != b.m_arg1 || std::memcmp(&a.m_time, &b.m_time, 4) != 0)
                t.fail("%s: note %d differs", what.c_str(), k);
        }
        if (g.seq.m_count != n.seq.m_count) t.fail("%s: count guest %d native %d", what.c_str(), g.seq.m_count, n.seq.m_count);
        if (std::memcmp(&g.seq.m_time, &n.seq.m_time, 8) != 0) t.fail("%s: clock guest %g native %g", what.c_str(), g.seq.m_time, n.seq.m_time);
        if (g.seq.m_notify.m_waiting != n.seq.m_notify.m_waiting || g.index_of((u64)g.seq.m_notify.m_note) != n.index_of((u64)n.seq.m_notify.m_note))
            t.fail("%s: the waiting notify differs", what.c_str());
        for (Side* s : {&g, &n})
            if (s->seq.m_cs.m_lock != FastCriticalSection::kFree) t.fail("%s: lock left held", what.c_str());
    }
};

}  // namespace

NATIVE_TEST("audio/sequencer") {
    if (!*reinterpret_cast<const u64*>(t.sym("_ZN4Aska6Global15m_pSoundManagerE"))) {
        t.fail("Global::m_pSoundManager is null (the sound manager isn't up)");
        return;
    }
    int sends = 0, releases = 0;
    for (int round = 0; round < 12 && !t.failures(); round++) {
        auto rig = std::make_unique<Rig>(t);
        Rig& r = *rig;
        for (int step = 0; step < 250 && !t.failures(); step++) {
            int op = t.rand_int(0, 11);
            std::string what = "round " + std::to_string(round) + " step " + std::to_string(step);
            if (op <= 4) {
                u32 message = (u32)t.rand_int(0, 11);
                float base = r.g.seq.m_time;
                float time = t.rand_int(0, 30) == 0 ? NAN : base + (float)t.rand_int(-60, 120);
                u64 a0 = (u64)t.rand_int(0, 5), a1 = (u64)t.rand_int(0, 5);
                what += " Add " + std::to_string(message);
                u64 gr, nr;
                {
                    Rig::Session s(r.g);
                    gr = t.call("_ZN4Aska10Sequencer214AddMessageNoteEjfPKvS2_", GuestArgs().p(&r.g.seq).i(message).f(time).i(a0).i(a1)).x0 & 0xff;
                }
                {
                    Rig::Session s(r.n);
                    nr = r.n.seq.AddMessageNote(message, time, (const void*)a0, (const void*)a1);
                }
                if (gr != nr) t.fail("%s: result guest %llu native %llu", what.c_str(), (unsigned long long)gr, (unsigned long long)nr);
            } else if (op == 5) {
                // a listed note (by position) or null
                int pos = t.rand_int(-1, std::max(0, r.g.seq.m_count - 1));
                auto pick = [&](Side& s) -> AudioMessageNote* {
                    if (pos < 0) return nullptr;
                    AudioMessageNote* p = s.seq.m_sentinel.m_next;
                    for (int i = 0; i < pos && p != &s.seq.m_sentinel; i++) p = p->m_next;
                    return p == &s.seq.m_sentinel ? nullptr : p;
                };
                what += " Delete";
                {
                    Rig::Session s(r.g);
                    t.call("_ZN4Aska10Sequencer217DeleteMessageNoteEPNS_16AudioMessageNoteE", {(u64)&r.g.seq, (u64)pick(r.g)});
                }
                {
                    Rig::Session s(r.n);
                    r.n.seq.DeleteMessageNote(pick(r.n));
                }
            } else if (op == 6) {
                what += " Arrange";
                {
                    Rig::Session s(r.g);
                    t.call("_ZN4Aska10Sequencer218ArrangeMessageNoteEv", {(u64)&r.g.seq});
                }
                {
                    Rig::Session s(r.n);
                    r.n.seq.ArrangeMessageNote();
                }
            } else if (op == 7) {
                what += " Process";
                {
                    Rig::Session s(r.g);
                    t.call("_ZN4Aska10Sequencer218ProcessMessageNoteEv", {(u64)&r.g.seq});
                }
                {
                    Rig::Session s(r.n);
                    r.n.seq.ProcessMessageNote();
                }
            } else if (op <= 9) {
                what += " AudioRun";
                {
                    Rig::Session s(r.g);
                    t.call("_ZN4Aska10Sequencer28AudioRunEv", {(u64)&r.g.seq});
                }
                {
                    Rig::Session s(r.n);
                    r.n.seq.AudioRun();
                }
            } else if (op == 10) {
                u32 state = (u32)t.rand_int(0, 6);
                r.g.player.m_state = r.n.player.m_state = state;
                what += " state " + std::to_string(state);
            } else {
                // a type-0 note's notify cleared from outside (WaitingNoteNotify::Handler)
                t.call("_ZN4Aska10Sequencer217WaitingNoteNotify7HandlerEm", {(u64)&r.g.seq.m_notify, 0});
                r.n.seq.m_notify.Handler(0);
                what += " notify";
            }
            r.compare(what);
            // IsWaitingNote on every pool note
            for (int k = 0; k < kPool; k++)
                if ((t.call("_ZNK4Aska10Sequencer213IsWaitingNoteEPNS_16AudioMessageNoteE", {(u64)&r.g.seq, (u64)&r.g.pool[k]}) & 0xff) !=
                    (u64)r.n.seq.IsWaitingNote(&r.n.pool[k]))
                    t.fail("%s: IsWaitingNote(%d) differs", what.c_str(), k);
        }
        // DeleteAllMessageNote at the end
        {
            Rig::Session s(r.g);
            t.call("_ZN4Aska10Sequencer220DeleteAllMessageNoteEv", {(u64)&r.g.seq});
        }
        {
            Rig::Session s(r.n);
            r.n.seq.DeleteAllMessageNote();
        }
        r.compare("DeleteAll");
        for (auto& l : r.g.log) sends += l.rfind("send", 0) == 0, releases += l.rfind("release", 0) == 0;
    }
    if (sends < 50 || releases < 50) t.fail("too few paths reached: %d sends, %d releases", sends, releases);
}
