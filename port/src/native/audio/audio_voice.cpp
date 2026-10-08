// Aska::SLVoice's submit path and Aska::WaveBuffer's lock / unlock (port/decomp/audio/voice.c; the
// layouts in audio_layout.h): what keeps a streaming voice's OpenSL buffer queue fed. The runtime's
// OpenSL HLE is untouched: the voice still enqueues through the interface the HLE made (its function
// table's slot 0), and the HLE still calls the guest's SLPlayerCallback, which lands on ProcAudioBuffer.
//
// The decoders: AskaADPCM is native (audio_adpcm.cpp), AskaOGG::Decode and VBRBuffer::LockBufferEx,
// SoundServer's pool and the stream's virtual functions are guest calls.
#include <cstring>
#include <string>
#include <vector>

#include "core/cpu.h"
#include "core/loader.h"
#include "native/audio/audio_check.h"
#include "native/audio/audio_layout.h"
#include "native/audio/audio_voice_obs.h"
#include "native/common/arm_float.h"
#include "native/common/guest_std.h"
#include "native/common/native_method.h"

namespace soa::native::audio {

thread_local VoiceObs* t_vobs = nullptr;

namespace {

struct VoiceFns {
    u64 lock_buffer_ex = guest::sym("_ZN4Aska9VBRBuffer12LockBufferExEPPvmPmS3_mb");
    u64 ogg_decode = guest::sym("_ZN4Aska7AskaOGG6DecodeEPKajPPajjj");
    u64 acquire_adpcm_buffer = guest::sym("_ZN4Aska11SoundServer28AcquireAskaAdpcmDecodeBufferEv");
    u64 sound_manager = guest::sym("_ZN4Aska6Global15m_pSoundManagerE");
};
const VoiceFns& fns() {
    static const VoiceFns f;
    return f;
}

SoundManager* sound_manager() { return *reinterpret_cast<SoundManager* const*>(fns().sound_manager); }

const u64* vtable_of(const void* o) { return *reinterpret_cast<const u64* const*>(o); }

// The calls that leave the voice (logged in a check: what, the arguments, the results, the out-params).
bool stream_is_end(WaveStreamView* s, bool a, s32 b) {
    bool r = (guest_call(vtable_of(s)[WaveStreamView::kSlotIsEnd], {(u64)s, (u64)a, (u64)(u32)b}) & 1) != 0;
    if (t_vobs) t_vobs->log("IsEnd", (u64)s, a, (u64)(u32)b, r);
    return r;
}
s64 stream_lock(WaveStreamView* s, void** out, u64 size, bool append) {
    s64 r = (s64)guest_call(vtable_of(s)[WaveStreamView::kSlotLock], {(u64)s, (u64)out, size, (u64)append});
    if (t_vobs) t_vobs->log("Lock", (u64)s, size, append, (u64)r, (u64)*out);
    return r;
}
s64 stream_unlock(WaveStreamView* s, u64 size) {
    s64 r = (s64)guest_call(vtable_of(s)[WaveStreamView::kSlotUnlock], {(u64)s, size});
    if (t_vobs) t_vobs->log("Unlock", (u64)s, size, 0, (u64)r);
    return r;
}
s32 enqueue(SLItf itf, const void* data, u32 size) {
    s32 r = (s32)guest_call((*itf)[0], {(u64)itf, (u64)data, (u64)size});
    if (t_vobs) t_vobs->log("Enqueue", (u64)itf, (u64)data, size, (u64)(u32)r);
    return r;
}

// (x + 1) mod d, and x + 1 when d is 0 (the guest's udiv by 0 gives 0).
u32 inc_mod(u32 x, u32 d) { return d ? (x + 1) % d : x + 1; }

void atomic_add(s32& v, s32 d) { __atomic_fetch_add(&v, d, __ATOMIC_SEQ_CST); }
void atomic_store(s32& v, s32 x) { __atomic_store_n(&v, x, __ATOMIC_SEQ_CST); }
s32 atomic_load(const s32& v) { return __atomic_load_n(&v, __ATOMIC_SEQ_CST); }

}  // namespace

// ---- Aska::WaveBuffer ----

s64 WaveBuffer::LockBuffer(void** out, u64 size, bool append) {
    if (!out || !size) return -0x3bd;
    if (!m_stream) return -0x3bc;
    s64 r = stream_lock(m_stream, out, size, append);
    if (r < 0 || r == 0) return r;
    if (append) {
        // the bytes join the last locked slot
        s32 last = (s32)m_write - 1;
        if (last < 0) last = kSlots - 1;
        if ((u32)last != m_read) {
            m_sizes[last] += (u32)r;
            return r;
        }
    } else if (m_read != m_write) {
        m_sizes[m_write] = (u32)r;
        m_write = m_write + 1 < kSlots ? m_write + 1 : 0;
        return r;
    }
    return -1;
}

s64 WaveBuffer::UnlockBuffer() {
    if (!m_stream) return -0x3bc;
    u32 next = m_read + 1 < kSlots ? m_read + 1 : 0;
    if (next == m_write) return -1;
    m_read = next;
    return stream_unlock(m_stream, m_sizes[next]);
}

// ---- Aska::SLVoice ----

void SLVoice::SetDeleteCountdown() {
    SoundManager* sm = sound_manager();
    float base = sm->m_signalTime;
    __atomic_thread_fence(__ATOMIC_SEQ_CST);
    float extra = sm->m_signalExtra ? *reinterpret_cast<const float*>(main_lib()->base + kDeleteCountdownExtra) : 0.0f;
    atomic_store(m_deleteCountdown, armf::cvtzs(armf::add(base, extra)));
    m_countdownArmed = 1;
}

s64 SLVoice::SubmitBufferDataPCM(const void* data, u32 size) {
    if (enqueue(m_bufferQueue, data, size) != 0) return kFailed;
    m_submitCount = inc_mod(m_submitCount, m_queueDepth);
    return 0;
}

s64 SLVoice::LockAndSubmitData() {
    if (stream_is_end(m_buffer->m_stream, false, 0)) return kEnded;
    void* p = nullptr;
    s64 r = m_buffer->LockBuffer(&p, m_lockSize, false);
    if (r < 0) return r;
    if (enqueue(m_bufferQueue, p, (u32)r) != 0) return kFailed;
    m_submitCount = inc_mod(m_submitCount, m_queueDepth);
    return 0;
}

s64 SLVoice::SubmitDummyDataAdpcm() {
    SoundManager* sm = sound_manager();
    if (enqueue(m_bufferQueue, sm->m_dummyBuffer, sm->m_dummyBufferSize) == 0) {
        m_submitCount = inc_mod(m_submitCount, m_queueDepth);
        u32 w = m_adpcmWrite;
        if (m_adpcmRead != w) {
            m_adpcmLocked[w] = 1;
            m_adpcmWrite = w + 1 < kAdpcmQueue ? w + 1 : 0;
            atomic_add(m_pendingBuffers, -1);
            return 0;
        }
    }
    m_failed = 1;
    return kFailed;
}

s64 SLVoice::SubmitDummyDataOgg() {
    SoundManager* sm = sound_manager();
    if (enqueue(m_bufferQueue, sm->m_dummyBuffer, sm->m_dummyBufferSize) == 0) {
        m_submitCount = inc_mod(m_submitCount, m_queueDepth);
        atomic_add(m_pendingBuffers, -1);
        u32 w = m_oggWrite;
        if (m_oggRead != w) {
            m_oggSubmits[w] = 0x100000000ull;
            m_oggWrite = w + 1 < kOggQueue ? w + 1 : 0;
            return 0;
        }
    }
    m_failed = 1;
    return kFailed;
}

// Decodes one locked chunk into the current decode buffer (taken from the pool on first use), drops the
// loop's head / tail frames, enqueues it. Returns the bytes enqueued.
s64 SLVoice::SubmitBufferDataADPCM(const void* data, u32 size, bool loopHead) {
    u8* buf = m_decodeBuffers[m_decodeIndex];
    if (!buf) {
        buf = reinterpret_cast<u8*>(guest_call(fns().acquire_adpcm_buffer, {(u64)sound_manager()->m_soundServer}));
        if (t_vobs) t_vobs->log("AcquireAdpcmBuffer", 0, 0, 0, (u64)buf);
        m_decodeBuffers[m_decodeIndex] = buf;
        if (!m_decodeBuffers[m_decodeIndex]) {
            m_failed = 1;
            return kNoBuffer;
        }
        m_decodeBufferSizes[m_decodeIndex] = kDecodeBufferSize;
        buf = m_decodeBuffers[m_decodeIndex];
    }
    u32 n = m_adpcm.Decode(static_cast<const u8*>(data), size, buf);
    const u32 frameBytes = (u32)m_format->m_channels * (u32)(m_format->m_bits >> 3);
    if (loopHead) {
        u32 skip = m_format->m_loopHeadFrames * frameBytes;
        n -= skip;
        buf += skip;
    }
    if (m_buffer->m_stream->m_loopTail) n -= m_format->m_loopTailFrames * frameBytes;
    if (n == 0) return 0;
    if (enqueue(m_bufferQueue, buf, n) == 0) {
        m_submitCount = inc_mod(m_submitCount, m_queueDepth);
        atomic_add(m_pendingBuffers, -1);
        u32 w = m_adpcmWrite;
        if (m_adpcmRead != w) {
            m_adpcmLocked[w] = 1;
            m_adpcmWrite = w + 1 < kAdpcmQueue ? w + 1 : 0;
            m_decodeIndex = (m_decodeIndex + 1) % kDecodeBuffers;
            return n;
        }
    }
    m_failed = 1;
    return kFailed;
}

// Decodes (as many frames as the queue has room for) and enqueues the PCM AskaOGG hands back.
s64 SLVoice::SubmitBufferDataOGG(const void* data, u32 size, u32 a, u32 b) {
    s8* out = nullptr;
    u32 frameBytes = ((u32)m_format->m_bits * (u32)m_format->m_channels) >> 3;
    u32 maxFrames = frameBytes ? (u32)m_queuedBytes / frameBytes : 0;
    s64 r = (s64)guest_call(fns().ogg_decode, {(u64)&m_ogg, (u64)data, (u64)size, (u64)&out, (u64)maxFrames, (u64)a, (u64)b});
    if (t_vobs) t_vobs->log_ogg("Decode", (u64)data, size, maxFrames, (u64)r, (u64)out, m_ogg);
    if (r < 0) {
        m_failed = 1;
        return r;
    }
    if ((u32)r == 0) return 0;
    if (enqueue(m_bufferQueue, out, (u32)r) == 0) {
        m_submitCount = inc_mod(m_submitCount, m_queueDepth);
        atomic_add(m_pendingBuffers, -1);
        atomic_add(m_queuedBytes, (s32)r);
        u32 w = m_oggWrite;
        if (m_oggRead != w) {
            m_oggSubmits[w] = (u64)(u32)r | (u64)(m_ogg.m_hasPending ^ 1) << 32;
            m_oggWrite = w + 1 < kOggQueue ? w + 1 : 0;
            return (u32)r;
        }
    }
    m_failed = 1;
    return kFailed;
}

// Locks the stream's next chunk(s) and submits them until one buffer is enqueued (at most 63 tries); with
// nothing to read, a dummy buffer when something was locked, else "nothing yet".
s64 SLVoice::LockAndSubmitADPCM() {
    bool locked = false;
    for (int tries = -0x40; ++tries != 0;) {
        WaveStreamView* s = m_buffer->m_stream;
        if (stream_is_end(s, false, 0)) {
            atomic_add(m_pendingBuffers, -1);
            return kEnded;
        }
        bool loopTail = m_buffer->m_stream->m_loopTail != 0;
        void* p = nullptr;
        s64 r = m_buffer->LockBuffer(&p, m_lockSize, locked);
        if (r < 0) {
            m_failed = 1;
            return r;
        }
        if ((u32)r != 0) {
            s64 n = SubmitBufferDataADPCM(p, (u32)r, loopTail);
            if (n < 0) return n;
            locked = true;
            if (n != 0) return 0;
            continue;
        }
        if (!locked) {
            u32 w = m_adpcmWrite;
            if (m_adpcmRead == w) break;
            m_adpcmLocked[w] = 0;
            m_adpcmWrite = w + 1 < kAdpcmQueue ? w + 1 : 0;
            return kWouldBlock;
        }
        SoundManager* sm = sound_manager();
        if (enqueue(m_bufferQueue, sm->m_dummyBuffer, sm->m_dummyBufferSize) == 0) {
            m_submitCount = inc_mod(m_submitCount, m_queueDepth);
            u32 w = m_adpcmWrite;
            if (m_adpcmRead != w) {
                m_adpcmLocked[w] = 1;
                m_adpcmWrite = w + 1 < kAdpcmQueue ? w + 1 : 0;
                atomic_add(m_pendingBuffers, -1);
                return kWouldBlock;
            }
        }
        break;
    }
    m_failed = 1;
    return kFailed;
}

s64 SLVoice::LockAndSubmitOGG() {
    bool locked = false;
    for (;;) {
        const void* data;
        u32 size, a, b;
        if (!m_ogg.m_hasPending) {
            if (stream_is_end(m_buffer->m_stream, false, 0)) {
                atomic_add(m_pendingBuffers, -1);
                return kEnded;
            }
            void* p = nullptr;
            u64 oa = 0, ob = 0;
            s64 r = (s64)guest_call(fns().lock_buffer_ex, {(u64)m_buffer, (u64)&p, (u64)m_lockSize, (u64)&oa, (u64)&ob, 0, (u64)locked});
            if (t_vobs) t_vobs->log_lock_ex((u64)m_buffer, m_lockSize, locked, (u64)r, (u64)p, oa, ob, *m_buffer);
            if (r < 0) {
                m_failed = 1;
                return r;
            }
            if ((u32)r == 0) {
                u64 value;
                if (!locked) {
                    if (m_oggRead == m_oggWrite) break;
                    value = 0;
                } else {
                    SoundManager* sm = sound_manager();
                    if (enqueue(m_bufferQueue, sm->m_dummyBuffer, sm->m_dummyBufferSize) != 0) break;
                    m_submitCount = inc_mod(m_submitCount, m_queueDepth);
                    atomic_add(m_pendingBuffers, -1);
                    if (m_oggRead == m_oggWrite) break;
                    value = 0x100000000ull;
                }
                u32 w = m_oggWrite;
                m_oggSubmits[w] = value;
                m_oggWrite = w + 1 < kOggQueue ? w + 1 : 0;
                return kWouldBlock;
            }
            data = p;
            size = (u32)r;
            a = (u32)oa;
            b = (u32)ob;
        } else {
            data = m_ogg.m_pendingData;
            size = m_ogg.m_pendingSize;
            a = 0;
            b = 0;
        }
        s64 n = SubmitBufferDataOGG(data, size, a, b);
        if (n < 0) return n;
        locked = true;
        if (n != 0) return 0;
    }
    m_failed = 1;
    return kFailed;
}

// The refill: for each played buffer (m_pendingBuffers, read once), the next entry of the submit queue
// says whether that buffer came from the stream (then the stream is unlocked; a stream that has played
// out arms the delete countdown instead), and one more buffer is decoded and enqueued.
void SLVoice::AudioSignal(u64 /*slot*/) {
    m_cs.Enter();
    if (t_vobs) t_vobs->capture(this);
    if (!m_failed && m_buffer && !stream_is_end(m_buffer->m_stream, true, 0)) {
        __atomic_thread_fence(__ATOMIC_SEQ_CST);
        s32 n = atomic_load(m_pendingBuffers);
        if (t_vobs) {
            t_vobs->has_pending_read = true;
            t_vobs->pending_read = n;
        }
        s64 r = 0;
        for (s32 i = 0; i < n;) {
            if (m_codec == kCodecOGG) {
                u32 next = m_oggRead + 1 < kOggQueue ? m_oggRead + 1 : 0;
                if (next == m_oggWrite) {
                    m_failed = 1;
                    break;
                }
                u64 submit = m_oggSubmits[next];
                m_oggRead = next;
                if (submit & 0xff00000000ull) {
                    m_buffer->UnlockBuffer();
                    if (stream_is_end(m_buffer->m_stream, true, 0)) {
                        SetDeleteCountdown();
                        break;
                    }
                }
                atomic_add(m_queuedBytes, -(s32)(u32)submit);
                r = LockAndSubmitOGG();
            } else if (m_codec == kCodecADPCM) {
                u32 next = m_adpcmRead + 1 < kAdpcmQueue ? m_adpcmRead + 1 : 0;
                if (next == m_adpcmWrite) {
                    m_failed = 1;
                    break;
                }
                u8 lockedBuffer = m_adpcmLocked[next];
                m_adpcmRead = next;
                if (lockedBuffer) {
                    m_buffer->UnlockBuffer();
                    if (stream_is_end(m_buffer->m_stream, true, 0)) {
                        SetDeleteCountdown();
                        break;
                    }
                }
                r = LockAndSubmitADPCM();
            }
            if ((r != kEnded && r < 0) || ++i >= n) break;
        }
    }
    if (t_vobs) t_vobs->capture_post(this);
    m_cs.Leave();
}

// The OpenSL callback (the HLE's audio thread): a compressed voice only counts the played buffer (the
// signal refills it); a PCM voice unlocks it and enqueues the next chunk at once.
void SLVoice::ProcAudioBuffer() {
    if (m_codec != kCodecPCM) {
        atomic_add(m_pendingBuffers, 1);
        return;
    }
    m_cs.Enter();
    if (t_vobs) t_vobs->capture(this);
    if (m_buffer) {
        m_buffer->UnlockBuffer();
        if (!stream_is_end(m_buffer->m_stream, true, 0)) {
            if (!stream_is_end(m_buffer->m_stream, false, 0)) {
                void* p = nullptr;
                s64 r = m_buffer->LockBuffer(&p, m_lockSize, false);
                if (r >= 0 && enqueue(m_bufferQueue, p, (u32)r) == 0) m_submitCount = inc_mod(m_submitCount, m_queueDepth);
            }
        } else {
            SetDeleteCountdown();
        }
    }
    if (t_vobs) t_vobs->capture_post(this);
    m_cs.Leave();
}

}  // namespace soa::native::audio
