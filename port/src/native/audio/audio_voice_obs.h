#pragma once
// What a checked SLVoice native did (the live check, audio_voice_check.cpp): the voice and its wave
// buffer as the native found them under the voice's lock and as it left them, and every call that left
// the voice, in order, with its results and out-parameters (the check's stubs replay them for the guest
// original on a shadow voice). Null outside a check.
#include <cstring>
#include <string>
#include <vector>

#include "native/audio/audio_layout.h"

namespace soa::native::audio {

struct VoiceObs {
    struct Call {
        std::string what;
        u64 a = 0, b = 0, c = 0;   // the arguments that identify the call
        u64 result = 0;
        u64 out = 0, out2 = 0, out3 = 0;  // out-parameters (Lock / LockBufferEx / Decode)
        std::vector<u8> after;     // Decode: the decoder's bytes after it; LockBufferEx: the buffer's
        bool same(const Call& o) const { return what == o.what && a == o.a && b == o.b && c == o.c; }
    };
    std::vector<Call> calls;
    bool captured = false, captured_post = false;
    SLVoice pre, post;
    WaveBuffer pre_buffer, post_buffer;
    u8 loop_tail = 0;  // the stream's m_loopTail at the capture
    bool has_pending_read = false;
    s32 pending_read = 0;  // AudioSignal: the m_pendingBuffers it read (the OpenSL thread may have added since the capture)

    void log(const char* what, u64 a, u64 b, u64 c, u64 result, u64 out = 0) { calls.push_back({what, a, b, c, result, out}); }
    void log_ogg(const char* what, u64 a, u64 b, u64 c, u64 result, u64 out, const AskaOGG& ogg) {
        Call k{what, a, b, c, result, out};
        k.after.assign(reinterpret_cast<const u8*>(&ogg), reinterpret_cast<const u8*>(&ogg) + sizeof ogg);
        calls.push_back(std::move(k));
    }
    void log_lock_ex(u64 buffer, u64 size, u64 append, u64 result, u64 out, u64 out2, u64 out3, const WaveBuffer& after) {
        Call k{"LockBufferEx", buffer, size, append, result, out, out2, out3};
        k.after.assign(reinterpret_cast<const u8*>(&after), reinterpret_cast<const u8*>(&after) + sizeof after);
        calls.push_back(std::move(k));
    }
    void capture(const SLVoice* v) {
        if (captured) return;
        captured = true;
        std::memcpy((void*)&pre, v, sizeof pre);
        if (v->m_buffer) {
            std::memcpy((void*)&pre_buffer, v->m_buffer, sizeof pre_buffer);
            if (v->m_buffer->m_stream) loop_tail = v->m_buffer->m_stream->m_loopTail;
        }
    }
    void capture_post(const SLVoice* v) {
        captured_post = true;
        std::memcpy((void*)&post, v, sizeof post);
        if (v->m_buffer) std::memcpy((void*)&post_buffer, v->m_buffer, sizeof post_buffer);
    }
};
extern thread_local VoiceObs* t_vobs;

}  // namespace soa::native::audio
