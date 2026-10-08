// The SLVoice natives' registrations and their live check (audio_check.h, family `audio`).
//
// SLVoice::AudioSignal and ProcAudioBuffer: the native for real (every call that leaves the voice logged
// with its results and out-parameters; the voice and its wave buffer captured under the voice's lock as
// the native found and left them), then the guest original on a shadow voice: the captured voice, its
// lock free, its wave buffer a copy whose stream is a proxy (a fake vtable: IsEnd / Lock / Unlock), its
// buffer queue a proxy interface (a fake Enqueue), its decode buffers scratch memory. The check's stubs
// answer the proxies, AskaOGG::Decode, VBRBuffer::LockBufferEx and SoundServer's decode-buffer pool from
// the native's log (Decode and LockBufferEx also put the decoder's / buffer's bytes after the call into
// the shadow). The calls (proxies and scratch mapped back), the voice and the buffer must match. The
// voice's other natives run inside (the guest original calls them through their hooks). A voice whose
// pending-buffer count the OpenSL thread changed meanwhile, or whose stream's loop flag moved, is a race.
#include <cstring>
#include <memory>
#include <string>
#include <vector>

#include "core/cpu.h"
#include "native/audio/audio_check.h"
#include "native/audio/audio_layout.h"
#include "native/audio/audio_voice_obs.h"
#include "native/common/guest_std.h"
#include "native/common/live_check.h"
#include "native/common/native_method.h"

namespace soa::native::audio {

namespace {

CheckedFn g_signal("_ZN4Aska7SLVoice11AudioSignalEm"), g_proc("_ZN4Aska7SLVoice15ProcAudioBufferEv");

// The fake functions the shadow's proxies call (made once; answered by the check's session).
struct Fakes {
    u64 is_end = native::fake_function("audio.live.stream-is-end", 3);
    u64 lock = native::fake_function("audio.live.stream-lock", 4);
    u64 unlock = native::fake_function("audio.live.stream-unlock", 2);
    u64 enqueue = native::fake_function("audio.live.enqueue", 3);
};
const Fakes& fakes() {
    static const Fakes f;
    return f;
}

struct Shadow {
    alignas(16) SLVoice voice;
    alignas(16) WaveBuffer buffer;
    std::unique_ptr<WaveStreamView> stream{new WaveStreamView()};
    alignas(16) u64 stream_vtable[32] = {};
    alignas(16) u64 itf_table[8] = {};
    u64 itf = 0;  // the SLAndroidSimpleBufferQueueItf: points at itf_table
    std::vector<std::unique_ptr<u8[]>> scratch;
    std::vector<std::pair<u64, u64>> scratch_map;  // (scratch, real)
    const SLVoice* real;

    Shadow(const SLVoice* r, const VoiceObs& o) : real(r) {
        std::memcpy((void*)&voice, &o.pre, sizeof voice);
        std::memcpy((void*)&buffer, &o.pre_buffer, sizeof buffer);
        voice.m_cs.m_lock = FastCriticalSection::kFree;
        voice.m_cs.m_waiters = FastCriticalSection::kWaiterBias;
        if (o.has_pending_read) voice.m_pendingBuffers = o.pending_read;
        stream_vtable[WaveStreamView::kSlotIsEnd] = fakes().is_end;
        stream_vtable[WaveStreamView::kSlotLock] = fakes().lock;
        stream_vtable[WaveStreamView::kSlotUnlock] = fakes().unlock;
        stream->vtable = stream_vtable;
        stream->m_loopTail = o.loop_tail;
        buffer.m_stream = stream.get();
        voice.m_buffer = o.pre.m_buffer ? &buffer : nullptr;
        itf_table[0] = fakes().enqueue;
        itf = (u64)itf_table;
        voice.m_bufferQueue = reinterpret_cast<SLItf>(&itf);
        for (u8*& b : voice.m_decodeBuffers)
            if (b) b = scratch_for((u64)b);
    }
    u8* scratch_for(u64 real_ptr) {
        for (auto& [s, r] : scratch_map)
            if (r == real_ptr) return (u8*)s;
        scratch.emplace_back(new u8[SLVoice::kDecodeBufferSize + 0x100]());
        scratch_map.emplace_back((u64)scratch.back().get(), real_ptr);
        return scratch.back().get();
    }
    // A shadow address as the real run's: scratch -> its real buffer, the proxies -> the real objects.
    u64 to_real(u64 p) const {
        for (auto& [s, r] : scratch_map)
            if (p >= s && p < s + SLVoice::kDecodeBufferSize + 0x100) return r + (p - s);
        if (p >= (u64)&voice && p < (u64)&voice + sizeof voice) return (u64)real + (p - (u64)&voice);
        if (p == (u64)&buffer) return (u64)real->m_buffer;
        if (p == (u64)stream.get()) return real->m_buffer ? (u64)real->m_buffer->m_stream : 0;
        if (p == (u64)&itf) return (u64)real->m_bufferQueue;
        return p;
    }
};

std::string compare_voice(const VoiceObs& o, const Shadow& sh, bool* race) {
    SLVoice g;
    std::memcpy((void*)&g, &sh.voice, sizeof g);
    g.m_buffer = reinterpret_cast<WaveBuffer*>(sh.to_real((u64)g.m_buffer));
    g.m_bufferQueue = reinterpret_cast<SLItf>(sh.to_real((u64)g.m_bufferQueue));
    for (u8*& b : g.m_decodeBuffers) b = reinterpret_cast<u8*>(sh.to_real((u64)b));
    const u8* n = reinterpret_cast<const u8*>(&o.post);
    const u8* s = reinterpret_cast<const u8*>(&g);
    // The fields other threads write without the voice's lock: the playback parameters (+0x18..0x30: the
    // sound thread's volume / pitch / pan and flags), m_kicks (AudioKick), m_pendingBuffers (ProcAudioBuffer,
    // the OpenSL thread) and m_deleteCountdown (AudioKick). Compared apart: a difference there only is a race.
    auto field = [](size_t off) { return std::pair<size_t, size_t>{off, off + 4}; };
    const std::pair<size_t, size_t> params{offsetof(SLVoice, unk_018), offsetof(SLVoice, m_buffer)};
    std::string why = live::diff_bytes(n, s, 0, offsetof(SLVoice, m_cs), {params, field(offsetof(SLVoice, m_kicks))});
    if (why.empty())
        why = live::diff_bytes(n, s, offsetof(SLVoice, m_cs) + sizeof(FastCriticalSection), sizeof(SLVoice),
                               {field(offsetof(SLVoice, m_pendingBuffers)), field(offsetof(SLVoice, m_deleteCountdown))});
    if (why.empty() && (o.post.m_kicks != g.m_kicks || o.post.m_pendingBuffers != g.m_pendingBuffers || o.post.m_deleteCountdown != g.m_deleteCountdown ||
                        std::memcmp(o.post.unk_018, g.unk_018, sizeof g.unk_018) != 0)) {
        *race = true;
        return "a field another thread writes without the lock (the parameters, m_kicks, m_pendingBuffers, m_deleteCountdown)";
    }
    if (why.empty() && o.pre.m_buffer) {
        WaveBuffer b = sh.buffer;
        b.m_stream = o.post_buffer.m_stream;
        why = live::diff_bytes(reinterpret_cast<const u8*>(&o.post_buffer), reinterpret_cast<const u8*>(&b), 0, sizeof b);
        if (!why.empty()) why = "the wave buffer " + why;
    }
    return why;
}

// The native for real, then the guest original on the shadow.
template <typename Native>
void voice_check(CheckedFn& f, SLVoice* self, Native native, u64 x1) {
    static const u64 ogg_decode = guest::sym("_ZN4Aska7AskaOGG6DecodeEPKajPPajjj");
    static const u64 lock_ex = guest::sym("_ZN4Aska9VBRBuffer12LockBufferExEPPvmPmS3_mb");
    static const u64 acquire = guest::sym("_ZN4Aska11SoundServer28AcquireAskaAdpcmDecodeBufferEv");
    const char* stub_decode = live::ensure_stub(ogg_decode);
    const char* stub_lock_ex = live::ensure_stub(lock_ex);
    const char* stub_acquire = live::ensure_stub(acquire);
    if (!stub_decode || !stub_lock_ex || !stub_acquire) {
        native();
        return live::check_result(f, live::Outcome::Skipped, "callees can't be stubbed");
    }
    (void)fakes();
    live::CheckScope scope;
    auto obs = std::make_unique<VoiceObs>();
    t_vobs = obs.get();
    native();
    t_vobs = nullptr;
    if (!obs->captured || !obs->captured_post) return live::check_result(f, live::Outcome::Skipped, "nothing under the lock");
    if (self->m_buffer && self->m_buffer->m_stream && self->m_buffer->m_stream->m_loopTail != obs->loop_tail)
        return live::check_result(f, live::Outcome::Race, "the stream's loop flag moved");
    auto sh = std::make_unique<Shadow>(self, *obs);
    std::vector<VoiceObs::Call> calls;
    size_t replay = 0;
    // The next logged call of this kind (the native's order); nullptr when the guest made one more.
    auto next = [&](const char* what) -> const VoiceObs::Call* {
        while (replay < obs->calls.size() && obs->calls[replay].what != what) replay++;
        return replay < obs->calls.size() ? &obs->calls[replay++] : nullptr;
    };
    u64 real_stream = self->m_buffer ? (u64)self->m_buffer->m_stream : 0;
    {
        live::ReplaySession s;
        s.answer("audio.live.stream-is-end", [&](Cpu& c) {
            calls.push_back({"IsEnd", real_stream, c.x(1) & 0xff, c.x(2) & 0xffffffff});
            const VoiceObs::Call* k = next("IsEnd");
            c.set_x(0, k ? k->result : 1);
        });
        s.answer("audio.live.stream-lock", [&](Cpu& c) {
            calls.push_back({"Lock", real_stream, c.x(2), c.x(3) & 0xff});
            const VoiceObs::Call* k = next("Lock");
            if (k && c.x(1)) *reinterpret_cast<u64*>(c.x(1)) = k->out;
            c.set_x(0, k ? k->result : (u64)-1);
        });
        s.answer("audio.live.stream-unlock", [&](Cpu& c) {
            calls.push_back({"Unlock", real_stream, c.x(1), 0});
            const VoiceObs::Call* k = next("Unlock");
            c.set_x(0, k ? k->result : 0);
        });
        s.answer("audio.live.enqueue", [&](Cpu& c) {
            // (a 0-byte Enqueue: the guest passes an uninitialized pointer, the native null: not compared)
            u64 size = c.x(2) & 0xffffffff;
            calls.push_back({"Enqueue", sh->to_real(c.x(0)), size ? sh->to_real(c.x(1)) : 0, size});
            const VoiceObs::Call* k = next("Enqueue");
            c.set_x(0, k ? k->result : 0);
        });
        s.answer(stub_decode, [&](Cpu& c) {
            calls.push_back({"Decode", c.x(1), c.x(2) & 0xffffffff, c.x(4) & 0xffffffff});
            const VoiceObs::Call* k = next("Decode");
            if (k) {
                if (c.x(3)) *reinterpret_cast<u64*>(c.x(3)) = k->out;
                std::memcpy((void*)&sh->voice.m_ogg, k->after.data(), sizeof(AskaOGG));
            }
            c.set_x(0, k ? k->result : (u64)-1);
        });
        s.answer(stub_lock_ex, [&](Cpu& c) {
            calls.push_back({"LockBufferEx", sh->to_real(c.x(0)), c.x(2), c.x(6) & 0xff});
            const VoiceObs::Call* k = next("LockBufferEx");
            if (k) {
                if (c.x(1)) *reinterpret_cast<u64*>(c.x(1)) = k->out;
                if (c.x(3)) *reinterpret_cast<u64*>(c.x(3)) = k->out2;
                if (c.x(4)) *reinterpret_cast<u64*>(c.x(4)) = k->out3;
                WaveStreamView* keep = sh->buffer.m_stream;
                std::memcpy((void*)&sh->buffer, k->after.data(), sizeof(WaveBuffer));
                sh->buffer.m_stream = keep;
            }
            c.set_x(0, k ? k->result : (u64)-1);
        });
        s.answer(stub_acquire, [&](Cpu& c) {
            calls.push_back({"AcquireAdpcmBuffer", 0, 0, 0});
            const VoiceObs::Call* k = next("AcquireAdpcmBuffer");
            c.set_x(0, k && k->result ? (u64)sh->scratch_for(k->result) : 0);
        });
        for (u64 t : {ogg_decode, lock_ex, acquire}) live::drop_stale_code(t);
        guest_call(f.orig, {(u64)&sh->voice, x1});
    }
    // The native's log, as the guest's entries are recorded (the arguments that identify a call).
    std::vector<VoiceObs::Call> native_calls;
    for (const VoiceObs::Call& k : obs->calls) {
        VoiceObs::Call n{k.what, k.a, k.b, k.c};
        if (k.what == "Decode") n = {k.what, k.a, k.b, k.c};
        else if (k.what == "IsEnd" || k.what == "Lock" || k.what == "Unlock") n.a = real_stream;
        else if (k.what == "AcquireAdpcmBuffer") n = {k.what, 0, 0, 0};
        else if (k.what == "Enqueue" && k.c == 0) n.b = 0;
        native_calls.push_back(n);
    }
    std::string why;
    bool race = false;
    if (calls.size() != native_calls.size()) why = "calls: native " + std::to_string(native_calls.size()) + " guest " + std::to_string(calls.size());
    for (size_t i = 0; why.empty() && i < calls.size(); i++)
        if (!calls[i].same(native_calls[i])) why = "call " + std::to_string(i) + ": native " + native_calls[i].what + " guest " + calls[i].what;
    if (why.empty()) why = compare_voice(*obs, *sh, &race);
    if (race) return live::check_result(f, live::Outcome::Race, why);
    live::check_result(f, why.empty() ? live::Outcome::Ok : live::Outcome::Mismatch, why);
}

void signal_checked(Cpu& c) {
    auto* self = reinterpret_cast<SLVoice*>(c.x(0));
    u64 slot = c.x(1);
    if (!live::check_due(g_signal)) return self->AudioSignal(slot);
    voice_check(g_signal, self, [&] { self->AudioSignal(slot); }, slot);
}
void proc_checked(Cpu& c) {
    auto* self = reinterpret_cast<SLVoice*>(c.x(0));
    if (self->m_codec != SLVoice::kCodecPCM || !live::check_due(g_proc)) return self->ProcAudioBuffer();
    voice_check(g_proc, self, [&] { self->ProcAudioBuffer(); }, 0);
}

// The members returning an Aska result through x8.
template <s64 (SLVoice::*M)()>
void x8_result(Cpu& c) {
    s64 r = (reinterpret_cast<SLVoice*>(c.x(0))->*M)();
    *reinterpret_cast<s64*>(c.x(8)) = r;
}
void submit_pcm_x8(Cpu& c) {
    s64 r = reinterpret_cast<SLVoice*>(c.x(0))->SubmitBufferDataPCM(reinterpret_cast<const void*>(c.x(1)), (u32)c.x(2));
    *reinterpret_cast<s64*>(c.x(8)) = r;
}

}  // namespace

NATIVE_FUNCTION_ORIG("_ZN4Aska7SLVoice11AudioSignalEm", signal_checked, "audio: Aska::SLVoice::AudioSignal", &g_signal.orig);
NATIVE_FUNCTION_ORIG("_ZN4Aska7SLVoice15ProcAudioBufferEv", proc_checked, "audio: Aska::SLVoice::ProcAudioBuffer", &g_proc.orig);
NATIVE_FUNCTION("_ZN4Aska7SLVoice17LockAndSubmitDataEv", x8_result<&SLVoice::LockAndSubmitData>, "audio: Aska::SLVoice::LockAndSubmitData");
NATIVE_FUNCTION("_ZN4Aska7SLVoice18LockAndSubmitADPCMEv", x8_result<&SLVoice::LockAndSubmitADPCM>, "audio: Aska::SLVoice::LockAndSubmitADPCM");
NATIVE_FUNCTION("_ZN4Aska7SLVoice16LockAndSubmitOGGEv", x8_result<&SLVoice::LockAndSubmitOGG>, "audio: Aska::SLVoice::LockAndSubmitOGG");
NATIVE_FUNCTION("_ZN4Aska7SLVoice19SubmitBufferDataPCMEPKvj", submit_pcm_x8, "audio: Aska::SLVoice::SubmitBufferDataPCM");
NATIVE_METHOD("_ZN4Aska7SLVoice21SubmitBufferDataADPCMEPKvjb", &SLVoice::SubmitBufferDataADPCM, "audio: Aska::SLVoice::SubmitBufferDataADPCM");
NATIVE_METHOD("_ZN4Aska7SLVoice19SubmitBufferDataOGGEPKvjjj", &SLVoice::SubmitBufferDataOGG, "audio: Aska::SLVoice::SubmitBufferDataOGG");
NATIVE_METHOD("_ZN4Aska7SLVoice20SubmitDummyDataAdpcmEv", &SLVoice::SubmitDummyDataAdpcm, "audio: Aska::SLVoice::SubmitDummyDataAdpcm");
NATIVE_METHOD("_ZN4Aska7SLVoice18SubmitDummyDataOggEv", &SLVoice::SubmitDummyDataOgg, "audio: Aska::SLVoice::SubmitDummyDataOgg");
NATIVE_METHOD("_ZN4Aska7SLVoice18SetDeleteCountdownEv", &SLVoice::SetDeleteCountdown, "audio: Aska::SLVoice::SetDeleteCountdown");
NATIVE_METHOD("_ZN4Aska10WaveBuffer10LockBufferEPPvmb", &WaveBuffer::LockBuffer, "audio: Aska::WaveBuffer::LockBuffer");
NATIVE_METHOD("_ZN4Aska10WaveBuffer12UnlockBufferEv", &WaveBuffer::UnlockBuffer, "audio: Aska::WaveBuffer::UnlockBuffer");

}  // namespace soa::native::audio
