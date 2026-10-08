// Aska::AudioSignalNotify: the voice lists of the signal path (port/decomp/audio/mixer.c; the layout in
// audio_layout.h). The sound manager thread adds a streaming SLVoice to one of AudioSignal's two notifies
// when it starts (AudioSignal::AddSignalVoiceList picks the emptier one) and removes it when it stops;
// each frame AudioSignal::Run posts the non-empty notifies to the message dispatcher, whose worker runs
// Handler: every voice in the list gets AudioSignal(slot) under the notify's lock (SLVoice refills its
// OpenSL buffer queue there). AudioSafetySignalThread calls Handler directly when the task stalls.
//
// The four methods enter the notify's FastCriticalSection (inlined in the guest: sync's Enter / Leave,
// the same algorithm on the same words, so guest code and these natives exclude each other) and scan
// the 20 slots in order.
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

// What a checked call saw under the lock (live check only; null otherwise).
struct SignalObs {
    SLVoice* pre[AudioSignalNotify::kSlots];
    SLVoice* post[AudioSignalNotify::kSlots];
    std::vector<std::pair<u64, u64>> calls;  // Handler: (voice, slot) in order
    u64 vtables[AudioSignalNotify::kSlots];  // Handler: each voice's vtable as the native saw it
};
thread_local SignalObs* t_obs = nullptr;

// The guest's Aska::SLVoice::AudioSignal(unsigned long): what slot 10 of an SLVoice's vtable holds.
u64 slvoice_audio_signal() {
    static const u64 fn = guest::sym("_ZN4Aska7SLVoice11AudioSignalEm");
    return fn;
}

// slot 10 of the voice's vtable (still guest code: a guest call).
u64 voice_slot_audio_signal(const SLVoice* voice) {
    const u64* vt = *reinterpret_cast<const u64* const*>(voice);
    return vt[AudioSignalNotify::kSlotVoiceAudioSignal];
}

}  // namespace

void AudioSignalNotify::Handler(u64 /*arg*/) {
    m_cs.Enter();
    if (t_obs) std::memcpy(t_obs->pre, m_voices, sizeof m_voices);
    for (int i = 0; i < kSlots; i++) {
        SLVoice* voice = m_voices[i];
        if (!voice) continue;
        if (t_obs) {
            t_obs->calls.emplace_back((u64)voice, (u64)i);
            t_obs->vtables[i] = *reinterpret_cast<const u64*>(voice);
        }
        guest_call(voice_slot_audio_signal(voice), {(u64)voice, (u64)i});
    }
    if (t_obs) std::memcpy(t_obs->post, m_voices, sizeof m_voices);
    m_cs.Leave();
}

bool AudioSignalNotify::AddSignalVoiceList(SLVoice* voice) {
    m_cs.Enter();
    if (t_obs) std::memcpy(t_obs->pre, m_voices, sizeof m_voices);
    bool added = false;
    for (SLVoice*& slot : m_voices)
        if (!slot) {
            slot = voice;
            added = true;
            break;
        }
    if (t_obs) std::memcpy(t_obs->post, m_voices, sizeof m_voices);
    m_cs.Leave();
    return added;
}

bool AudioSignalNotify::DeleteSignalVoiceList(SLVoice* voice) {
    m_cs.Enter();
    if (t_obs) std::memcpy(t_obs->pre, m_voices, sizeof m_voices);
    bool removed = false;
    for (SLVoice*& slot : m_voices)
        if (slot == voice) {
            slot = nullptr;
            removed = true;
            break;
        }
    if (t_obs) std::memcpy(t_obs->post, m_voices, sizeof m_voices);
    m_cs.Leave();
    return removed;
}

u32 AudioSignalNotify::GetSignalCount() const {
    auto& cs = const_cast<FastCriticalSection&>(m_cs);
    cs.Enter();
    u32 n = 0;
    for (const SLVoice* slot : m_voices) n += slot != nullptr;
    cs.Leave();
    return n;
}

// ---- The live check (audio_check.h) ----

namespace {

CheckedFn g_handler("_ZN4Aska17AudioSignalNotify7HandlerEm"), g_add("_ZN4Aska17AudioSignalNotify18AddSignalVoiceListEPNS_7SLVoiceE"),
    g_delete("_ZN4Aska17AudioSignalNotify21DeleteSignalVoiceListEPNS_7SLVoiceE"), g_count("_ZNK4Aska17AudioSignalNotify14GetSignalCountEv");

std::string slots_diff(SLVoice* const* native, SLVoice* const* guest) {
    for (int i = 0; i < AudioSignalNotify::kSlots; i++)
        if (native[i] != guest[i]) return "slot " + std::to_string(i) + " differs";
    return {};
}

// A private notify for the guest original: the slots the native saw, its lock free (a copy of the real
// lock's bytes, word -1 and no waiters: the guest's enter succeeds at once and its leave posts nothing).
struct ShadowNotify {
    alignas(16) AudioSignalNotify n;
    ShadowNotify(const AudioSignalNotify& real, SLVoice* const* slots) {
        std::memcpy(&n, &real, sizeof n);
        std::memcpy(n.m_voices, slots, sizeof n.m_voices);
        n.m_cs.m_lock = FastCriticalSection::kFree;
        n.m_cs.m_waiters = FastCriticalSection::kWaiterBias;
    }
};

// Add / Delete: the native for real, then the guest original on a shadow of the slots the native saw.
template <bool (AudioSignalNotify::*M)(SLVoice*)>
void list_checked(Cpu& c, CheckedFn& f) {
    if (!live::check_due(f)) return wrap_method<M>()(c);
    live::CheckScope scope;
    auto* self = reinterpret_cast<AudioSignalNotify*>(c.x(0));
    u64 voice = c.x(1);
    SignalObs obs;
    t_obs = &obs;
    bool native = (self->*M)(reinterpret_cast<SLVoice*>(voice));
    t_obs = nullptr;
    ShadowNotify sh(*self, obs.pre);
    bool guest = (guest_call(f.orig, {(u64)&sh.n, voice}) & 0xff) != 0;
    std::string why = native != guest ? "result: native " + std::to_string(native) + " guest " + std::to_string(guest) : slots_diff(obs.post, sh.n.m_voices);
    live::check_result(f, why.empty() ? live::Outcome::Ok : live::Outcome::Mismatch, why);
    c.set_x(0, native);
}
void add_checked(Cpu& c) { list_checked<&AudioSignalNotify::AddSignalVoiceList>(c, g_add); }
void delete_checked(Cpu& c) { list_checked<&AudioSignalNotify::DeleteSignalVoiceList>(c, g_delete); }

void count_checked(Cpu& c) {
    if (!live::check_due(g_count)) return wrap_method<&AudioSignalNotify::GetSignalCount>()(c);
    live::check_getter(c, g_count, wrap_method<&AudioSignalNotify::GetSignalCount>(), 0xffffffffu);
}

// Handler: the native for real (its voice calls logged, each voice's vtable as it was), then the guest
// original on a shadow notify whose slots hold proxies of those voices (just their vtables: a voice
// deleted right after the native's run doesn't matter), with SLVoice::AudioSignal answered by the
// check's stub: the calls, in order, must match. Skipped when a voice's slot 10 isn't
// SLVoice::AudioSignal (a class the stub doesn't cover).
void handler_checked(Cpu& c) {
    if (!live::check_due(g_handler)) return wrap_method<&AudioSignalNotify::Handler>()(c);
    auto* self = reinterpret_cast<AudioSignalNotify*>(c.x(0));
    const u64 target = slvoice_audio_signal();
    const char* stub = live::ensure_stub(target);
    if (!stub) {
        wrap_method<&AudioSignalNotify::Handler>()(c);
        return live::check_result(g_handler, live::Outcome::Skipped, "SLVoice::AudioSignal can't be stubbed");
    }
    live::CheckScope scope;
    SignalObs obs;
    t_obs = &obs;
    self->Handler(c.x(1));
    t_obs = nullptr;
    alignas(16) u64 proxies[AudioSignalNotify::kSlots][2] = {};
    SLVoice* slots[AudioSignalNotify::kSlots] = {};
    for (auto& [voice, slot] : obs.calls) {
        if (reinterpret_cast<const u64*>(obs.vtables[slot])[AudioSignalNotify::kSlotVoiceAudioSignal] != target)
            return live::check_result(g_handler, live::Outcome::Skipped, "a voice of another class");
        proxies[slot][0] = obs.vtables[slot];
        slots[slot] = reinterpret_cast<SLVoice*>(proxies[slot]);
    }
    auto real_of = [&](u64 p) -> u64 {
        for (int i = 0; i < AudioSignalNotify::kSlots; i++)
            if (p == (u64)proxies[i]) return (u64)obs.pre[i];
        return p;
    };
    ShadowNotify sh(*self, slots);
    std::vector<std::pair<u64, u64>> guest_calls;
    {
        live::ReplaySession s;
        s.answer(stub, [&](Cpu& cc) {
            guest_calls.emplace_back(real_of(cc.x(0)), cc.x(1));
            cc.set_x(0, 0);
        });
        live::drop_stale_code(target);
        guest_call(g_handler.orig, {(u64)&sh.n, c.x(1)});
    }
    std::string why;
    if (guest_calls != obs.calls)
        why = "voice calls: native " + std::to_string(obs.calls.size()) + " guest " + std::to_string(guest_calls.size());
    if (why.empty()) why = slots_diff(slots, sh.n.m_voices);
    live::check_result(g_handler, why.empty() ? live::Outcome::Ok : live::Outcome::Mismatch, why);
}

}  // namespace

NATIVE_FUNCTION_ORIG("_ZN4Aska17AudioSignalNotify7HandlerEm", handler_checked, "audio: Aska::AudioSignalNotify::Handler", &g_handler.orig);
NATIVE_FUNCTION_ORIG("_ZN4Aska17AudioSignalNotify18AddSignalVoiceListEPNS_7SLVoiceE", add_checked, "audio: Aska::AudioSignalNotify::AddSignalVoiceList",
                     &g_add.orig);
NATIVE_FUNCTION_ORIG("_ZN4Aska17AudioSignalNotify21DeleteSignalVoiceListEPNS_7SLVoiceE", delete_checked,
                     "audio: Aska::AudioSignalNotify::DeleteSignalVoiceList", &g_delete.orig);
NATIVE_FUNCTION_ORIG("_ZNK4Aska17AudioSignalNotify14GetSignalCountEv", count_checked, "audio: Aska::AudioSignalNotify::GetSignalCount", &g_count.orig);

}  // namespace soa::native::audio
