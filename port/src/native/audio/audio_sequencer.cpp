// Aska::Sequencer2: a sound object's timed message list (port/decomp/audio/sound_manager.c; the layouts
// in audio_layout.h). The game side adds notes (AddMessageNote: a message for the AudioPlayer at a time
// on the sequencer's clock); each sound-thread pass (SoundObject::AudioRun -> Sequencer2::AudioRun)
// advances the clock by 1/60 s while the player plays, drops the notes made redundant
// (ArrangeMessageNote) and sends the ones that are due (ProcessMessageNote). The notes come from and go
// back to SoundServer's pool (Acquire / ReleaseMessageNote, guest code). Every method takes the
// sequencer's FastCriticalSection (inlined in the guest: sync's Enter / Leave on the same words);
// ProcessMessageNote holds it only to step through the list, so notes added meanwhile are seen.
//
// Comparisons of the times are the guest's: a note is due when the clock >= its time, ordered (a NaN is
// never due), as the guest's fcmp + b.lt does.
#include <algorithm>
#include <cstring>
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

struct SequencerFns {
    u64 acquire = guest::sym("_ZN4Aska11SoundServer18AcquireMessageNoteEv");
    u64 release = guest::sym("_ZN4Aska11SoundServer18ReleaseMessageNoteEPNS_16AudioMessageNoteE");
    u64 send = guest::sym("_ZN4Aska11AudioPlayer11SendMessageEjPvS1_");
    u64 notify_handler = guest::sym("_ZN4Aska10Sequencer217WaitingNoteNotify7HandlerEm");
    u64 sound_manager = guest::sym("_ZN4Aska6Global15m_pSoundManagerE");
};
const SequencerFns& fns() {
    static const SequencerFns f;
    return f;
}

SoundServer* sound_server() { return (*reinterpret_cast<SoundManager* const*>(fns().sound_manager))->m_soundServer; }

// The calls a checked run made (live check only; null otherwise).
struct SequencerObs {
    std::vector<std::string> calls;
    std::vector<AudioMessageNote*> visited;  // ProcessMessageNote: the notes it stepped to
    bool captured = false;
    Sequencer2 pre;                          // the sequencer under the lock, before any change
    std::vector<AudioMessageNote*> pre_list; // its notes, in order
    std::vector<AudioMessageNote> pre_notes; // their bytes
    AudioMessageNote* acquired = nullptr;    // AddMessageNote: the pool's note
    AudioMessageNote acquired_pre{};         // ... its bytes before the native wrote them
};
thread_local SequencerObs* t_sobs = nullptr;

std::string hex(u64 v) {
    char b[24];
    snprintf(b, sizeof b, "%llx", (unsigned long long)v);
    return b;
}

// Captures the sequencer and its notes (called under the lock, once per checked call).
void capture(Sequencer2* s) {
    if (!t_sobs || t_sobs->captured) return;
    t_sobs->captured = true;
    std::memcpy(&t_sobs->pre, s, sizeof *s);
    for (AudioMessageNote* n = s->m_sentinel.m_next; n && n != &s->m_sentinel; n = n->m_next) {
        t_sobs->pre_list.push_back(n);
        t_sobs->pre_notes.push_back(*n);
        if (t_sobs->pre_list.size() > 4096) break;
    }
}

void release_note(AudioMessageNote* note) {
    if (t_sobs) t_sobs->calls.push_back("Release " + hex((u64)note));
    guest_call(fns().release, {(u64)sound_server(), (u64)note});
}

}  // namespace

void Sequencer2::Unlink(AudioMessageNote* note) {
    AudioMessageNote* prev = note->m_prev;
    AudioMessageNote* next = note->m_next;
    if (prev) prev->m_next = next;
    if (next) next->m_prev = prev;
    if (m_count > 0) m_count--;
    note->m_prev = nullptr;
    note->m_next = nullptr;
}

bool Sequencer2::IsWaitingNote(const AudioMessageNote* note) const {
    const WaitingNoteNotify* w = note->m_waitNotify;
    return w && w->m_note != note && w->m_waiting;
}

void WaitingNoteNotify::Handler(u64 /*arg*/) { m_waiting = 0; }

bool Sequencer2::AddMessageNote(u32 message, float time, const void* a0, const void* a1) {
    m_cs.Enter();
    capture(this);
    auto* note = reinterpret_cast<AudioMessageNote*>(guest_call(fns().acquire, {(u64)sound_server()}));
    if (t_sobs) {
        t_sobs->calls.push_back("Acquire");
        t_sobs->acquired = note;
        if (note) t_sobs->acquired_pre = *note;
    }
    bool added = false;
    if (note) {
        WaitingNoteNotify* wait = nullptr;
        if (message - 1u < 9) {
            if (m_notify.m_waiting) wait = &m_notify;
        } else if (message == 0) {
            m_notify.m_waiting = 1;
            m_notify.m_note = note;
            wait = &m_notify;
        }
        note->m_waitNotify = wait;
        note->m_time = time;
        note->m_message = message;
        note->m_arg0 = a0;
        note->m_arg1 = a1;
        AudioMessageNote* last = m_sentinel.m_prev;
        note->m_prev = last;
        note->m_next = &m_sentinel;
        m_sentinel.m_prev = note;
        last->m_next = note;
        m_count++;
        added = true;
    }
    m_cs.Leave();
    return added;
}

void Sequencer2::DeleteMessageNote(AudioMessageNote* note) {
    m_cs.Enter();
    capture(this);
    if (note != &m_sentinel && note) Unlink(note);
    release_note(note);  // (also a null note or the sentinel, as the guest does)
    m_cs.Leave();
}

void Sequencer2::DeleteAllMessageNote() {
    m_cs.Enter();
    capture(this);
    for (AudioMessageNote* n = m_sentinel.m_next; n != &m_sentinel;) {
        AudioMessageNote* next = n->m_next;
        if (n) Unlink(n);
        release_note(n);
        n = next;
    }
    m_cs.Leave();
}

void Sequencer2::ArrangeMessageNote() {
    m_cs.Enter();
    capture(this);
    AudioMessageNote* const end = &m_sentinel;
    // 1. Of the notes of type 1 and 4, only the earliest of each type stays.
    for (AudioMessageNote* n = m_sentinel.m_next; n != end;) {
        AudioMessageNote* next = n->m_next;
        if (n->m_message == 4 || n->m_message == 1)
            for (AudioMessageNote* o = m_sentinel.m_next; o != end; o = o->m_next)
                if (n->m_message == o->m_message && n->m_time > o->m_time) {
                    Unlink(n);
                    release_note(n);
                    break;
                }
        n = next;
    }
    // 2. Of the notes already due, only the latest of each type stays.
    for (AudioMessageNote* n = m_sentinel.m_next; n != end;) {
        AudioMessageNote* next = n->m_next;
        if (m_time >= n->m_time)
            for (AudioMessageNote* o = m_sentinel.m_next; o != end; o = o->m_next)
                if (n != o && m_time >= o->m_time && o->m_message == n->m_message && o->m_time >= n->m_time) {
                    Unlink(n);
                    release_note(n);
                    break;
                }
        n = next;
    }
    // 3. The due notes, in order, against the player's state as they would change it: a note that
    //    makes no sense in that state is dropped. (The state is a local: nothing is written back; a
    //    type-3 note in another state than 3 is dropped and still moves it to 2, as in the guest.)
    if (m_sentinel.m_next != end) {
        u32 state = m_player->m_state;
        for (AudioMessageNote* n = m_sentinel.m_next; n != end;) {
            AudioMessageNote* next = n->m_next;
            if (!IsWaitingNote(n) && m_time >= n->m_time && n->m_message <= 9) {
                bool drop = false;
                switch (n->m_message) {
                case 0:  // play: only from state 1
                    if (state == 1) state = 2;
                    else drop = true;
                    break;
                case 1:  // stop: from 2, 3 or 4
                    if (state - 2 < 3) state = 5;
                    else drop = true;
                    break;
                case 2:  // pause: from 2 or 4
                    if (state == 2 || state == 4) state = 3;
                    else drop = true;
                    break;
                case 3: {  // resume: from 3
                    bool ok = state == 3;
                    state = 2;
                    drop = !ok;
                    break;
                }
                case 4:  // from 2 or 3
                    if ((state & ~1u) == 2) state = 4;
                    else drop = true;
                    break;
                default:  // 5-9: from 2 or 3
                    drop = (state & ~1u) != 2;
                    break;
                }
                if (drop) {
                    Unlink(n);
                    release_note(n);
                }
            }
            n = next;
        }
    }
    m_cs.Leave();
}

void Sequencer2::ProcessMessageNote() {
    m_cs.Enter();
    capture(this);
    AudioMessageNote* n = m_sentinel.m_next;
    m_cs.Leave();
    while (n != &m_sentinel) {
        if (t_sobs) t_sobs->visited.push_back(n);
        m_cs.Enter();
        AudioMessageNote* next = n->m_next;
        m_cs.Leave();
        if (!IsWaitingNote(n) && m_time >= n->m_time) {
            if (t_sobs) t_sobs->calls.push_back("Send " + std::to_string(n->m_message) + " " + hex((u64)n->m_arg0) + " " + hex((u64)n->m_arg1));
            guest_call(fns().send, {(u64)m_player, (u64)n->m_message, (u64)n->m_arg0, (u64)n->m_arg1});
            if (WaitingNoteNotify* w = n->m_waitNotify) {
                u64 handler = (*reinterpret_cast<const u64* const*>(w))[0];
                if (handler == fns().notify_handler) w->Handler(0);
                else guest_call(handler, {(u64)w, 0});
            }
            DeleteMessageNote(n);
        }
        n = next;
    }
}

// ---- The live check (audio_check.h) ----
//
// Each method: the native for real (its pool and player calls logged, the sequencer and its notes
// captured under the lock before any change), then the guest original on a shadow sequencer built from
// that capture (its notes copied and relinked, the notify pointers moved to the shadow's notify, the
// lock free), with SoundServer::Acquire / ReleaseMessageNote and AudioPlayer::SendMessage answered by
// the check's stubs on this thread. The calls (shadow notes mapped back), the list left (by note), the
// notes' bytes, the count, the clock and the notify must match. ProcessMessageNote drops the lock
// between notes: a note another thread added meanwhile makes it a race.

namespace {

CheckedFn g_add("_ZN4Aska10Sequencer214AddMessageNoteEjfPKvS2_"), g_delete("_ZN4Aska10Sequencer217DeleteMessageNoteEPNS_16AudioMessageNoteE"),
    g_delete_all("_ZN4Aska10Sequencer220DeleteAllMessageNoteEv"), g_arrange("_ZN4Aska10Sequencer218ArrangeMessageNoteEv"),
    g_process("_ZN4Aska10Sequencer218ProcessMessageNoteEv"), g_run("_ZN4Aska10Sequencer28AudioRunEv");

struct Shadow {
    alignas(16) Sequencer2 s;
    std::vector<AudioMessageNote> notes;  // shadow copies, in the captured order
    const std::vector<AudioMessageNote*>* real = nullptr;
    const Sequencer2* real_seq = nullptr;
    AudioMessageNote scratch{};           // AddMessageNote's acquired note (guest side)
    const AudioMessageNote* real_acquired = nullptr;

    Shadow(const Sequencer2* real_s, const SequencerObs& o) : real(&o.pre_list), real_seq(real_s) {
        std::memcpy(&s, &o.pre, sizeof s);
        s.m_cs.m_lock = FastCriticalSection::kFree;
        s.m_cs.m_waiters = FastCriticalSection::kWaiterBias;
        notes = o.pre_notes;
        AudioMessageNote* prev = &s.m_sentinel;
        for (AudioMessageNote& n : notes) {
            n.m_prev = prev;
            prev->m_next = &n;
            prev = &n;
        }
        prev->m_next = &s.m_sentinel;
        s.m_sentinel.m_prev = prev;
        for (AudioMessageNote& n : notes) n.m_waitNotify = map_notify(n.m_waitNotify);
        s.m_notify.m_note = to_shadow(s.m_notify.m_note);
        scratch = o.acquired_pre;
        real_acquired = o.acquired;
    }
    WaitingNoteNotify* map_notify(WaitingNoteNotify* w) {
        return w == &real_seq->m_notify ? &s.m_notify : w;
    }
    AudioMessageNote* to_shadow(AudioMessageNote* p) {
        for (size_t i = 0; i < real->size(); i++)
            if ((*real)[i] == p) return &notes[i];
        if (p == &real_seq->m_sentinel) return &s.m_sentinel;
        if (real_acquired && p == real_acquired) return &scratch;
        return p;
    }
    u64 to_real(u64 p) const {
        for (size_t i = 0; i < notes.size(); i++)
            if (p == (u64)&notes[i]) return (u64)(*real)[i];
        if (p == (u64)&s.m_sentinel) return (u64)&real_seq->m_sentinel;
        if (p == (u64)&s.m_notify) return (u64)&real_seq->m_notify;
        if (p == (u64)&scratch && real_acquired) return (u64)real_acquired;
        if (p == (u64)&s) return (u64)real_seq;
        return p;
    }
    // A note's bytes with its pointers as the real run's.
    AudioMessageNote normalized(const AudioMessageNote& n) const {
        AudioMessageNote r = n;
        r.m_prev = reinterpret_cast<AudioMessageNote*>(to_real((u64)n.m_prev));
        r.m_next = reinterpret_cast<AudioMessageNote*>(to_real((u64)n.m_next));
        r.m_waitNotify = reinterpret_cast<WaitingNoteNotify*>(to_real((u64)n.m_waitNotify));
        return r;
    }
};

// Runs `native` for real, then the guest original on the shadow, and compares.
template <typename Native, typename Guest>
void sequencer_check(CheckedFn& f, Sequencer2* self, Native native, Guest guest_run, std::string (*extra)(void*) = nullptr, void* extra_arg = nullptr) {
    const SequencerFns& g = fns();
    const char* stub_acquire = live::ensure_stub(g.acquire);
    const char* stub_release = live::ensure_stub(g.release);
    const char* stub_send = live::ensure_stub(g.send);
    if (!stub_acquire || !stub_release || !stub_send) {
        native();
        return live::check_result(f, live::Outcome::Skipped, "callees can't be stubbed");
    }
    live::CheckScope scope;
    SequencerObs obs;
    t_sobs = &obs;
    native();
    t_sobs = nullptr;
    if (!obs.captured) return live::check_result(f, live::Outcome::Skipped, "nothing captured");
    if (obs.pre_list.size() > 4096) return live::check_result(f, live::Outcome::Skipped, "list too long");
    for (AudioMessageNote* v : obs.visited)
        if (v != &self->m_sentinel && std::find(obs.pre_list.begin(), obs.pre_list.end(), v) == obs.pre_list.end())
            return live::check_result(f, live::Outcome::Race, "a note added during the run");
    Shadow sh(self, obs);
    std::vector<std::string> calls;
    {
        live::ReplaySession s;
        s.answer(stub_acquire, [&](Cpu& cc) {
            calls.push_back("Acquire");
            cc.set_x(0, obs.acquired ? (u64)&sh.scratch : 0);
        });
        s.answer(stub_release, [&](Cpu& cc) {
            calls.push_back("Release " + hex(sh.to_real(cc.x(1))));
            cc.set_x(0, 0);
        });
        s.answer(stub_send, [&](Cpu& cc) {
            calls.push_back("Send " + std::to_string((u32)cc.x(1)) + " " + hex(cc.x(2)) + " " + hex(cc.x(3)));
            cc.set_x(0, 0);
        });
        live::drop_stale_code(g.acquire);
        live::drop_stale_code(g.release);
        live::drop_stale_code(g.send);
        guest_run(&sh);
    }
    std::string why;
    if (calls != obs.calls) {
        why = "calls: native " + std::to_string(obs.calls.size()) + " guest " + std::to_string(calls.size());
        for (size_t i = 0; i < calls.size() && i < obs.calls.size(); i++)
            if (calls[i] != obs.calls[i]) {
                why += " (first difference: native " + obs.calls[i] + " guest " + calls[i] + ")";
                break;
            }
    }
    if (why.empty() && extra) why = extra(extra_arg);
    // The list left: the shadow's, mapped back, against the real one. A note in the real list that the
    // native neither found nor added came from another thread after the native's last lock: a race.
    std::vector<u64> left_sh, left_real;
    for (AudioMessageNote* n = sh.s.m_sentinel.m_next; n && n != &sh.s.m_sentinel && left_sh.size() < 5000; n = n->m_next) left_sh.push_back(sh.to_real((u64)n));
    for (AudioMessageNote* n = self->m_sentinel.m_next; n && n != &self->m_sentinel && left_real.size() < 5000; n = n->m_next) left_real.push_back((u64)n);
    for (u64 n : left_real)
        if (n != (u64)obs.acquired && std::find(obs.pre_list.begin(), obs.pre_list.end(), (AudioMessageNote*)n) == obs.pre_list.end())
            return live::check_result(f, live::Outcome::Race, "a note added by another thread");
    if (why.empty() && left_sh != left_real) why = "the list left: native " + std::to_string(left_real.size()) + " notes guest " + std::to_string(left_sh.size());
    // The bytes of the notes left (released ones go back to the pool, which may hand them out again).
    for (size_t i = 0; why.empty() && i < left_real.size(); i++) {
        const AudioMessageNote* real_note = reinterpret_cast<const AudioMessageNote*>(left_real[i]);
        const AudioMessageNote* shadow_note = nullptr;
        for (AudioMessageNote* n = sh.s.m_sentinel.m_next; n != &sh.s.m_sentinel; n = n->m_next)
            if (sh.to_real((u64)n) == left_real[i]) shadow_note = n;
        if (!shadow_note) continue;
        AudioMessageNote a = *real_note, b = sh.normalized(*shadow_note);
        if (std::memcmp(&a, &b, sizeof a) != 0) why = "note " + std::to_string(i) + ": " + live::diff_bytes((const u8*)&a, (const u8*)&b, 0, sizeof a);
    }
    if (why.empty() && sh.s.m_count != self->m_count) why = "count: native " + std::to_string(self->m_count) + " guest " + std::to_string(sh.s.m_count);
    if (why.empty() && std::memcmp(&sh.s.m_time, &self->m_time, 8) != 0) why = "the clock differs";
    if (why.empty() && (sh.s.m_notify.m_waiting != self->m_notify.m_waiting || sh.to_real((u64)sh.s.m_notify.m_note) != (u64)self->m_notify.m_note))
        why = "the waiting notify differs";
    live::check_result(f, why.empty() ? live::Outcome::Ok : live::Outcome::Mismatch, why);
}

// The checked entry points: the hooks (guest callers) and AudioRun's calls (a native caller).
void arrange(Sequencer2* s) {
    if (!live::check_due(g_arrange)) return s->ArrangeMessageNote();
    sequencer_check(g_arrange, s, [&] { s->ArrangeMessageNote(); }, [&](Shadow* sh) { guest_call(g_arrange.orig, {(u64)&sh->s}); });
}
void process(Sequencer2* s) {
    if (!live::check_due(g_process)) return s->ProcessMessageNote();
    sequencer_check(g_process, s, [&] { s->ProcessMessageNote(); }, [&](Shadow* sh) { guest_call(g_process.orig, {(u64)&sh->s}); });
}

void add_checked(Cpu& c) {
    if (!live::check_due(g_add)) return wrap_method<&Sequencer2::AddMessageNote>()(c);
    auto* s = reinterpret_cast<Sequencer2*>(c.x(0));
    u32 message = (u32)c.x(1);
    float time = c.s(0);
    u64 a0 = c.x(2), a1 = c.x(3);
    struct Results {
        bool native = false;
        int guest = -1;
    } r;
    sequencer_check(
        g_add, s, [&] { r.native = s->AddMessageNote(message, time, (const void*)a0, (const void*)a1); },
        [&](Shadow* sh) { r.guest = (int)(guest_call(g_add.orig, GuestArgs().p(&sh->s).i(message).f(time).i(a0).i(a1)).x0 & 0xff); },
        [](void* p) -> std::string {
            auto* q = static_cast<Results*>(p);
            return q->guest != (int)q->native ? "result: native " + std::to_string(q->native) + " guest " + std::to_string(q->guest) : std::string();
        },
        &r);
    c.set_x(0, r.native);
}
void delete_checked(Cpu& c) {
    if (!live::check_due(g_delete)) return wrap_method<&Sequencer2::DeleteMessageNote>()(c);
    auto* s = reinterpret_cast<Sequencer2*>(c.x(0));
    auto* note = reinterpret_cast<AudioMessageNote*>(c.x(1));
    sequencer_check(g_delete, s, [&] { s->DeleteMessageNote(note); }, [&](Shadow* sh) { guest_call(g_delete.orig, {(u64)&sh->s, (u64)sh->to_shadow(note)}); });
}
void delete_all_checked(Cpu& c) {
    if (!live::check_due(g_delete_all)) return wrap_method<&Sequencer2::DeleteAllMessageNote>()(c);
    auto* s = reinterpret_cast<Sequencer2*>(c.x(0));
    sequencer_check(g_delete_all, s, [&] { s->DeleteAllMessageNote(); }, [&](Shadow* sh) { guest_call(g_delete_all.orig, {(u64)&sh->s}); });
}
void arrange_checked(Cpu& c) { arrange(reinterpret_cast<Sequencer2*>(c.x(0))); }
void process_checked(Cpu& c) { process(reinterpret_cast<Sequencer2*>(c.x(0))); }

}  // namespace

// AudioRun: the clock moves while the player plays (state 2 or 4), then the two passes (checked ones).
void Sequencer2::AudioRun() {
    if (!m_player) return;
    if (m_player->m_state == 2 || m_player->m_state == 4) m_time = m_step + m_time;
    arrange(this);
    process(this);
}

NATIVE_FUNCTION_ORIG("_ZN4Aska10Sequencer214AddMessageNoteEjfPKvS2_", add_checked, "audio: Aska::Sequencer2::AddMessageNote", &g_add.orig);
NATIVE_FUNCTION_ORIG("_ZN4Aska10Sequencer217DeleteMessageNoteEPNS_16AudioMessageNoteE", delete_checked, "audio: Aska::Sequencer2::DeleteMessageNote",
                     &g_delete.orig);
NATIVE_FUNCTION_ORIG("_ZN4Aska10Sequencer220DeleteAllMessageNoteEv", delete_all_checked, "audio: Aska::Sequencer2::DeleteAllMessageNote",
                     &g_delete_all.orig);
NATIVE_FUNCTION_ORIG("_ZN4Aska10Sequencer218ArrangeMessageNoteEv", arrange_checked, "audio: Aska::Sequencer2::ArrangeMessageNote", &g_arrange.orig);
NATIVE_FUNCTION_ORIG("_ZN4Aska10Sequencer218ProcessMessageNoteEv", process_checked, "audio: Aska::Sequencer2::ProcessMessageNote", &g_process.orig);
NATIVE_METHOD("_ZN4Aska10Sequencer28AudioRunEv", &Sequencer2::AudioRun, "audio: Aska::Sequencer2::AudioRun");
NATIVE_METHOD("_ZNK4Aska10Sequencer213IsWaitingNoteEPNS_16AudioMessageNoteE", &Sequencer2::IsWaitingNote, "audio: Aska::Sequencer2::IsWaitingNote");
NATIVE_METHOD("_ZN4Aska10Sequencer217WaitingNoteNotify7HandlerEm", &WaitingNoteNotify::Handler, "audio: Aska::Sequencer2::WaitingNoteNotify::Handler");

}  // namespace soa::native::audio
