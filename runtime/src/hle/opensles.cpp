// OpenSL ES (Android flavour): engine, output mix, PCM buffer-queue audio players.
// Mixed on a host thread and fed to the frontend's audio device.
#include <soa/env.h>
#include <algorithm>
#include <atomic>
#include <chrono>
#include <cmath>
#include <condition_variable>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <mutex>
#include <thread>
#include <vector>

#include "core/hle.h"
#include "core/log.h"
#include "hle/audio.h"
#include "core/selftest.h"

namespace soa {
namespace {

// ---- constants from OpenSLES.h / OpenSLES_Android.h ----
constexpr u32 SL_RESULT_SUCCESS = 0, SL_RESULT_PARAMETER_INVALID = 2, SL_RESULT_FEATURE_UNSUPPORTED = 12, SL_RESULT_BUFFER_INSUFFICIENT = 7;
constexpr u32 SL_OBJECT_STATE_REALIZED = 2;
constexpr u32 SL_PLAYSTATE_STOPPED = 1, SL_PLAYSTATE_PAUSED = 2, SL_PLAYSTATE_PLAYING = 3;
constexpr u32 SL_DATALOCATOR_BUFFERQUEUE = 6, SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE = 0x800007BD;
constexpr u32 SL_DATAFORMAT_PCM = 2;
constexpr u32 SL_PLAYEVENT_HEADATEND = 1;

struct Guid {
    u8 b[16];
};
Guid g_iid_storage[8];
u64 g_iid_vars[8];  // SL_IID_* variables (pointers to the GUIDs)
enum Iid { IID_ENGINE, IID_PLAY, IID_BUFFERQUEUE, IID_ANDROIDSIMPLEBUFFERQUEUE, IID_VOLUME, IID_PLAYBACKRATE, IID_OBJECT, IID_COUNT };

int iid_index(u64 p) {
    for (int i = 0; i < IID_COUNT; i++)
        if (p == (u64)&g_iid_storage[i]) return i;
    return -1;
}

// ---- objects ----
struct SlObject;
struct Itf {
    u64 vtbl;  // the guest's XXXItf points here
    SlObject* owner;
};

enum class Kind { Engine, OutputMix, Player };

struct Buffer {
    const u8* data;
    u32 size;
};

struct SlObject {
    Kind kind;
    Itf obj_itf, engine_itf, play_itf, bq_itf, volume_itf, rate_itf;

    // Player state (guarded by g_mix_mutex)
    u32 channels = 2, sample_rate = 44100, bits = 16;
    u32 play_state = SL_PLAYSTATE_STOPPED;
    std::deque<Buffer> queue;
    u32 play_index = 0;
    double pos = 0;  // fractional frame position in the current buffer
    u64 bq_callback = 0, bq_context = 0, bq_itf_addr = 0;
    u64 play_callback = 0, play_context = 0;
    u32 play_event_mask = 0;
    s16 volume_mb = 0;
    bool muted = false;
    s16 rate_permille = 1000;
    u64 played_frames = 0;
    int pending_callbacks = 0;
    FILE* dump = nullptr;  // SOA_AUDIO_DUMP: every enqueued buffer, as a WAV file
    u32 dump_bytes = 0;
};

u64 g_vt_object[10], g_vt_engine[15], g_vt_play[12], g_vt_bq[4], g_vt_volume[9], g_vt_rate[6];

std::mutex g_mix_mutex;
std::vector<SlObject*> g_players;
std::thread g_mixer;
std::atomic<bool> g_mixer_run{false};

SlObject* owner(Cpu& c) { return ((Itf*)c.x(0))->owner; }

// SOA_AUDIO_DUMP=<dir>: writes the PCM each player enqueues to <dir>/player<N>.wav (N in
// creation order), before mixing and resampling, so decoded audio can be compared exactly.
void dump_open(SlObject* o) {
    static const char* dir = env::env_str("SOA_AUDIO_DUMP");
    static std::atomic<int> next{0};
    if (!dir) return;
    char path[512];
    snprintf(path, sizeof path, "%s/player%d.wav", dir, next++);
    o->dump = fopen(path, "wb");
    if (!o->dump) LOGW("sles", "SOA_AUDIO_DUMP: cannot create %s", path);
}
void dump_write(SlObject* o, const u8* data, u32 size) {
    if (!o->dump) return;
    auto le32 = [](u8* p, u32 v) { std::memcpy(p, &v, 4); };
    auto le16 = [](u8* p, u16 v) { std::memcpy(p, &v, 2); };
    o->dump_bytes += size;
    u8 h[44];
    std::memcpy(h, "RIFF\0\0\0\0WAVEfmt ", 16);
    le32(h + 4, 36 + o->dump_bytes);
    le32(h + 16, 16);
    le16(h + 20, 1);
    le16(h + 22, (u16)o->channels);
    le32(h + 24, o->sample_rate);
    le32(h + 28, o->sample_rate * o->channels * o->bits / 8);
    le16(h + 32, (u16)(o->channels * o->bits / 8));
    le16(h + 34, (u16)o->bits);
    std::memcpy(h + 36, "data", 4);
    le32(h + 40, o->dump_bytes);
    fseek(o->dump, 0, SEEK_SET);
    fwrite(h, 1, 44, o->dump);
    fseek(o->dump, 0, SEEK_END);
    fwrite(data, 1, size, o->dump);
    fflush(o->dump);
}

void init_obj(SlObject* o, Kind k) {
    o->kind = k;
    o->obj_itf = {(u64)g_vt_object, o};
    o->engine_itf = {(u64)g_vt_engine, o};
    o->play_itf = {(u64)g_vt_play, o};
    o->bq_itf = {(u64)g_vt_bq, o};
    o->volume_itf = {(u64)g_vt_volume, o};
    o->rate_itf = {(u64)g_vt_rate, o};
}

// ---- SLObjectItf ----
void o_Realize(Cpu& c) { ret(c, SL_RESULT_SUCCESS); }
void o_Resume(Cpu& c) { ret(c, SL_RESULT_SUCCESS); }
void o_GetState(Cpu& c) {
    *(u32*)c.x(1) = SL_OBJECT_STATE_REALIZED;
    ret(c, SL_RESULT_SUCCESS);
}
void o_GetInterface(Cpu& c) {
    SlObject* o = owner(c);
    int i = iid_index(c.x(1));
    Itf* itf = nullptr;
    switch (i) {
    case IID_ENGINE: itf = o->kind == Kind::Engine ? &o->engine_itf : nullptr; break;
    case IID_PLAY: itf = o->kind == Kind::Player ? &o->play_itf : nullptr; break;
    case IID_BUFFERQUEUE:
    case IID_ANDROIDSIMPLEBUFFERQUEUE: itf = o->kind == Kind::Player ? &o->bq_itf : nullptr; break;
    case IID_VOLUME: itf = o->kind == Kind::Player ? &o->volume_itf : nullptr; break;
    case IID_PLAYBACKRATE: itf = o->kind == Kind::Player ? &o->rate_itf : nullptr; break;
    }
    if (!itf) {
        LOGW("sles", "GetInterface: unsupported interface %d on object kind %d", i, (int)o->kind);
        ret(c, SL_RESULT_FEATURE_UNSUPPORTED);
        return;
    }
    *(u64*)c.x(2) = (u64)itf;
    ret(c, SL_RESULT_SUCCESS);
}
void o_RegisterCallback(Cpu& c) { ret(c, SL_RESULT_SUCCESS); }
void o_AbortAsyncOperation(Cpu& c) {}
void o_Destroy(Cpu& c) {
    SlObject* o = owner(c);
    if (o->kind == Kind::Player) {
        std::unique_lock lk(g_mix_mutex);
        std::erase(g_players, o);
    }
    // Keep the memory: a guest callback may still be in flight on the mixer thread.
    o->play_state = SL_PLAYSTATE_STOPPED;
    o->queue.clear();
}
void o_SetPriority(Cpu& c) { ret(c, SL_RESULT_SUCCESS); }
void o_GetPriority(Cpu& c) { ret(c, SL_RESULT_SUCCESS); }
void o_SetLossOfControlInterfaces(Cpu& c) { ret(c, SL_RESULT_SUCCESS); }

// ---- SLEngineItf ----
void e_unsupported(Cpu& c) {
    LOGW("sles", "unsupported engine function %s", thunk_name_at(c.pc() - 4));
    ret(c, SL_RESULT_FEATURE_UNSUPPORTED);
}
void e_CreateOutputMix(Cpu& c) {
    auto* o = new SlObject();
    init_obj(o, Kind::OutputMix);
    *(u64*)c.x(1) = (u64)&o->obj_itf;
    ret(c, SL_RESULT_SUCCESS);
}
void e_CreateAudioPlayer(Cpu& c) {
    const u64* src = (const u64*)c.x(2);  // SLDataSource {pLocator, pFormat}
    const u32* loc = (const u32*)src[0];
    const u32* fmt = (const u32*)src[1];
    if (loc[0] != SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE && loc[0] != SL_DATALOCATOR_BUFFERQUEUE) {
        LOGW("sles", "CreateAudioPlayer: unsupported locator %#x", loc[0]);
        ret(c, SL_RESULT_FEATURE_UNSUPPORTED);
        return;
    }
    if (fmt[0] != SL_DATAFORMAT_PCM) {
        LOGW("sles", "CreateAudioPlayer: unsupported format %u", fmt[0]);
        ret(c, SL_RESULT_FEATURE_UNSUPPORTED);
        return;
    }
    auto* o = new SlObject();
    init_obj(o, Kind::Player);
    o->channels = fmt[1];
    o->sample_rate = fmt[2] / 1000;
    o->bits = fmt[3];
    LOGD("sles", "CreateAudioPlayer: %u ch, %u Hz, %u bits, %u buffers", o->channels, o->sample_rate, o->bits, loc[1]);
    dump_open(o);
    {
        std::lock_guard lk(g_mix_mutex);
        g_players.push_back(o);
    }
    *(u64*)c.x(1) = (u64)&o->obj_itf;
    ret(c, SL_RESULT_SUCCESS);
}

// ---- SLPlayItf ----
void p_SetPlayState(Cpu& c) {
    SlObject* o = owner(c);
    std::lock_guard lk(g_mix_mutex);
    u32 st = (u32)c.x(1);
    if (st == SL_PLAYSTATE_STOPPED) {
        o->pos = 0;
        o->played_frames = 0;
    }
    o->play_state = st;
    ret(c, SL_RESULT_SUCCESS);
}
void p_GetPlayState(Cpu& c) {
    *(u32*)c.x(1) = owner(c)->play_state;
    ret(c, SL_RESULT_SUCCESS);
}
void p_GetDuration(Cpu& c) {
    *(u32*)c.x(1) = 0xFFFFFFFF;  // SL_TIME_UNKNOWN
    ret(c, SL_RESULT_SUCCESS);
}
void p_GetPosition(Cpu& c) {
    SlObject* o = owner(c);
    *(u32*)c.x(1) = (u32)(o->played_frames * 1000 / std::max<u32>(1, o->sample_rate));
    ret(c, SL_RESULT_SUCCESS);
}
void p_RegisterCallback(Cpu& c) {
    SlObject* o = owner(c);
    std::lock_guard lk(g_mix_mutex);
    o->play_callback = c.x(1);
    o->play_context = c.x(2);
    ret(c, SL_RESULT_SUCCESS);
}
void p_SetCallbackEventsMask(Cpu& c) {
    owner(c)->play_event_mask = (u32)c.x(1);
    ret(c, SL_RESULT_SUCCESS);
}
void p_GetCallbackEventsMask(Cpu& c) {
    *(u32*)c.x(1) = owner(c)->play_event_mask;
    ret(c, SL_RESULT_SUCCESS);
}
void p_ok(Cpu& c) { ret(c, SL_RESULT_SUCCESS); }

// ---- buffer queue ----
void bq_Enqueue(Cpu& c) {
    SlObject* o = owner(c);
    std::lock_guard lk(g_mix_mutex);
    if (o->queue.size() >= 64) {
        ret(c, SL_RESULT_BUFFER_INSUFFICIENT);
        return;
    }
    o->queue.push_back({(const u8*)c.x(1), (u32)c.x(2)});
    dump_write(o, (const u8*)c.x(1), (u32)c.x(2));
    ret(c, SL_RESULT_SUCCESS);
}
void bq_Clear(Cpu& c) {
    SlObject* o = owner(c);
    std::lock_guard lk(g_mix_mutex);
    o->queue.clear();
    o->pos = 0;
    ret(c, SL_RESULT_SUCCESS);
}
void bq_GetState(Cpu& c) {
    SlObject* o = owner(c);
    std::lock_guard lk(g_mix_mutex);
    ((u32*)c.x(1))[0] = (u32)o->queue.size();
    ((u32*)c.x(1))[1] = o->play_index;
    ret(c, SL_RESULT_SUCCESS);
}
void bq_RegisterCallback(Cpu& c) {
    SlObject* o = owner(c);
    std::lock_guard lk(g_mix_mutex);
    o->bq_callback = c.x(1);
    o->bq_context = c.x(2);
    o->bq_itf_addr = c.x(0);
    ret(c, SL_RESULT_SUCCESS);
}

// ---- volume ----
void v_SetVolumeLevel(Cpu& c) {
    owner(c)->volume_mb = (s16)c.x(1);
    ret(c, SL_RESULT_SUCCESS);
}
void v_GetVolumeLevel(Cpu& c) {
    *(s16*)c.x(1) = owner(c)->volume_mb;
    ret(c, SL_RESULT_SUCCESS);
}
void v_GetMaxVolumeLevel(Cpu& c) {
    *(s16*)c.x(1) = 0;
    ret(c, SL_RESULT_SUCCESS);
}
void v_SetMute(Cpu& c) {
    owner(c)->muted = c.x(1) & 1;
    ret(c, SL_RESULT_SUCCESS);
}
void v_GetMute(Cpu& c) {
    *(u32*)c.x(1) = owner(c)->muted;
    ret(c, SL_RESULT_SUCCESS);
}

// ---- playback rate ----
void r_SetRate(Cpu& c) {
    owner(c)->rate_permille = (s16)c.x(1);
    ret(c, SL_RESULT_SUCCESS);
}
void r_GetRate(Cpu& c) {
    *(s16*)c.x(1) = owner(c)->rate_permille;
    ret(c, SL_RESULT_SUCCESS);
}
void r_GetRateRange(Cpu& c) {
    // (self, index, *minRate, *maxRate, *stepSize, *capabilities)
    *(s16*)c.x(2) = 500;
    *(s16*)c.x(3) = 2000;
    *(s16*)c.x(4) = 1;
    *(u32*)c.x(5) = 0;
    ret(c, SL_RESULT_SUCCESS);
}

void th_slCreateEngine(Cpu& c) {
    auto* o = new SlObject();
    init_obj(o, Kind::Engine);
    *(u64*)c.x(0) = (u64)&o->obj_itf;
    audio_start_mixer();
    ret(c, SL_RESULT_SUCCESS);
}

// ---- mixer ----
inline float sample_at(const SlObject* o, const Buffer& b, u64 frame, u32 ch) {
    u32 fch = std::min(ch, o->channels - 1);
    if (o->bits == 16) return ((const s16*)b.data)[frame * o->channels + fch] * (1.0f / 32768.0f);
    if (o->bits == 8) return (((const u8*)b.data)[frame * o->channels + fch] - 128) * (1.0f / 128.0f);
    return 0;
}

struct Pending {
    u64 fn, itf, ctx;
};

// Mixes `frames` stereo float frames at `out_rate` into out (accumulating).
void mix(float* out, int frames, int out_rate, std::vector<Pending>& callbacks) {
    std::lock_guard lk(g_mix_mutex);
    for (SlObject* o : g_players) {
        if (o->play_state != SL_PLAYSTATE_PLAYING || o->queue.empty()) continue;
        float gain = o->muted ? 0.f : (o->volume_mb <= -9600 ? 0.f : std::pow(10.0f, o->volume_mb / 2000.0f));
        double step = (double)o->sample_rate * (o->rate_permille / 1000.0) / out_rate;
        u32 bpf = o->channels * (o->bits / 8);
        for (int i = 0; i < frames && !o->queue.empty(); i++) {
            const Buffer& b = o->queue.front();
            u64 nframes = b.size / bpf;
            u64 f0 = (u64)o->pos;
            if (f0 >= nframes) {
                // buffer finished
                o->queue.pop_front();
                o->play_index++;
                o->pos -= nframes;
                if (o->bq_callback) callbacks.push_back({o->bq_callback, o->bq_itf_addr, o->bq_context});
                i--;
                continue;
            }
            double frac = o->pos - f0;
            u64 f1 = f0 + 1 < nframes ? f0 + 1 : f0;
            for (u32 ch = 0; ch < 2; ch++) {
                float s = sample_at(o, b, f0, ch) * (1 - frac) + sample_at(o, b, f1, ch) * frac;
                out[i * 2 + ch] += s * gain;
            }
            o->pos += step;
            o->played_frames++;
        }
        // Report buffers that finished exactly at the chunk end too.
        while (!o->queue.empty() && (u64)o->pos >= o->queue.front().size / bpf) {
            o->pos -= o->queue.front().size / bpf;
            o->queue.pop_front();
            o->play_index++;
            if (o->bq_callback) callbacks.push_back({o->bq_callback, o->bq_itf_addr, o->bq_context});
        }
    }
}

}  // namespace

void audio_mix(float* out, int frames, int rate) {
    std::memset(out, 0, sizeof(float) * frames * 2);
    std::vector<Pending> cbs;
    mix(out, frames, rate, cbs);
    for (auto& p : cbs) guest_call(p.fn, {p.itf, p.ctx});
}

void register_opensles(Hle& h) {
    // Interface IDs (values are arbitrary; only identity matters).
    const char* names[] = {"SL_IID_ENGINE", "SL_IID_PLAY", "SL_IID_BUFFERQUEUE", "SL_IID_ANDROIDSIMPLEBUFFERQUEUE", "SL_IID_VOLUME", "SL_IID_PLAYBACKRATE", "SL_IID_OBJECT"};
    for (int i = 0; i < IID_COUNT; i++) {
        memset(&g_iid_storage[i], 0x40 + i, sizeof(Guid));
        g_iid_vars[i] = (u64)&g_iid_storage[i];
        h.data(names[i], &g_iid_vars[i]);
    }
    HostFn obj[] = {o_Realize, o_Resume, o_GetState, o_GetInterface, o_RegisterCallback, o_AbortAsyncOperation, o_Destroy, o_SetPriority, o_GetPriority, o_SetLossOfControlInterfaces};
    const char* obj_n[] = {"SLObject::Realize", "SLObject::Resume", "SLObject::GetState", "SLObject::GetInterface", "SLObject::RegisterCallback",
                           "SLObject::AbortAsyncOperation", "SLObject::Destroy", "SLObject::SetPriority", "SLObject::GetPriority", "SLObject::SetLossOfControlInterfaces"};
    for (int i = 0; i < 10; i++) g_vt_object[i] = make_thunk(obj_n[i], obj[i]);
    const char* eng_n[] = {"SLEngine::CreateLEDDevice", "SLEngine::CreateVibraDevice", "SLEngine::CreateAudioPlayer", "SLEngine::CreateAudioRecorder", "SLEngine::CreateMidiPlayer",
                           "SLEngine::CreateListener", "SLEngine::Create3DGroup", "SLEngine::CreateOutputMix", "SLEngine::CreateMetadataExtractor", "SLEngine::CreateExtensionObject",
                           "SLEngine::QueryNumSupportedInterfaces", "SLEngine::QuerySupportedInterfaces", "SLEngine::QueryNumSupportedExtensions", "SLEngine::QuerySupportedExtension",
                           "SLEngine::IsExtensionSupported"};
    for (int i = 0; i < 15; i++) g_vt_engine[i] = make_thunk(eng_n[i], i == 2 ? e_CreateAudioPlayer : i == 7 ? e_CreateOutputMix : e_unsupported);
    HostFn play[] = {p_SetPlayState, p_GetPlayState, p_GetDuration, p_GetPosition, p_RegisterCallback, p_SetCallbackEventsMask, p_GetCallbackEventsMask, p_ok, p_ok, p_ok, p_ok, p_ok};
    for (int i = 0; i < 12; i++) g_vt_play[i] = make_thunk("SLPlay", play[i]);
    HostFn bq[] = {bq_Enqueue, bq_Clear, bq_GetState, bq_RegisterCallback};
    for (int i = 0; i < 4; i++) g_vt_bq[i] = make_thunk("SLBufferQueue", bq[i]);
    HostFn vol[] = {v_SetVolumeLevel, v_GetVolumeLevel, v_GetMaxVolumeLevel, v_SetMute, v_GetMute, p_ok, p_ok, p_ok, p_ok};
    for (int i = 0; i < 9; i++) g_vt_volume[i] = make_thunk("SLVolume", vol[i]);
    HostFn rate[] = {r_SetRate, r_GetRate, p_ok, p_ok, p_ok, r_GetRateRange};
    for (int i = 0; i < 6; i++) g_vt_rate[i] = make_thunk("SLPlaybackRate", rate[i]);
    h.fn("slCreateEngine", th_slCreateEngine);
}

// ---- test ----------------------------------------------------------------------------------
// Not differential (host-side emulation of Android's OpenSL ES): a PLAYING player's queued buffer
// must get played in real time whether or not an audio device pulls (main.cpp's null sink takes
// over when none does). The game detects a sound's end only through its buffers being played;
// without an output pulling, every SE stayed playing and scenes waited forever for them to end.
namespace {
RUNTIME_TEST("audio/opensl-queue-drains") {
    static s16 pcm[4800];  // 100 ms of mono 48 kHz silence
    auto* o = new SlObject();  // leaked on purpose: the mixer thread may still hold it briefly
    init_obj(o, Kind::Player);
    o->channels = 1, o->sample_rate = 48000, o->bits = 16;
    {
        std::lock_guard lk(g_mix_mutex);
        o->queue.push_back({(const u8*)pcm, (u32)sizeof pcm});
        o->play_state = SL_PLAYSTATE_PLAYING;
        g_players.push_back(o);
    }
    bool drained = false;
    for (int i = 0; i < 300 && !drained; i++) {  // up to 3 s
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        std::lock_guard lk(g_mix_mutex);
        drained = o->queue.empty();
    }
    std::lock_guard lk(g_mix_mutex);
    std::erase(g_players, o);
    o->play_state = SL_PLAYSTATE_STOPPED;
    if (!drained) t.fail("a playing OpenSL buffer queue was not played within 3 s (played %llu frames)", (unsigned long long)o->played_frames);
    else t.expect_eq(o->play_index, 1u, "buffers played");
}
}  // namespace

}  // namespace soa
