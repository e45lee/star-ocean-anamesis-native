// Aska::AskaOGG's packet decoding (port/decomp/audio/codec.c; the layout in audio_layout.h): DecodePackets
// (the packets of the pages fed so far, up to the frame target) and Decode_Pcmout (the synthesized
// float samples converted to interleaved s16 in the current out buffer, which grows by 64 KiB steps).
// DecodeBody (guest) calls DecodePackets for each page; Decode_LoopStart (guest) calls Decode_Pcmout
// after a loop jump. The rest of the decoder (Decode, DecodeHeader, DecodeBody, Decode_LoopStart) stays
// guest code: it runs once per page / header / loop, these once per packet and sample.
//
// The library is called through its guest symbols (guest_call): with lib_vorbis native that is the host
// function directly (on the host structs in place); with `--natives-skip lib_vorbis` it is the guest
// library on its own state, which a direct host call would misread.
//
// The conversion is the guest's: fmul by 32767.0f, fadd 0.5f (two roundings: no fused multiply-add),
// FCVTMS (toward -inf, saturating, NaN -> 0), clamped to [-0x8000, 0x7fff].
//
// The live check (`--live-check audio`): the native for real, every library and sound-memory call it
// makes logged with its results (vorbis_synthesis_pcmout's float rows copied); then the guest original
// on a shadow decoder (the object as the native found it, its current out buffer a copy) with those
// calls stubbed and answered from the log (DecodePackets' Decode_Pcmout calls run the guest's too). The calls, the result, the decoder's own fields (+0x3b0 on;
// the library's structs are only passed on) and the out buffer's bytes must match.
#include <algorithm>
#include <cmath>
#include <cstring>
#include <memory>
#include <string>
#include <vector>

#include "soaruntime/core/cpu.h"
#include "soaruntime/core/loader.h"
#include "native/audio/audio_check.h"
#include "native/audio/audio_layout.h"
#include "native/common/arm_float.h"
#include "native/common/guest_std.h"
#include "native/common/live_check.h"
#include "native/common/native_method.h"

namespace soa::native::audio {

namespace {

struct OggFns {
    u64 packetout = guest::sym("ogg_stream_packetout");
    u64 synthesis = guest::sym("vorbis_synthesis");
    u64 blockin = guest::sym("vorbis_synthesis_blockin");
    u64 pcmout = guest::sym("vorbis_synthesis_pcmout");
    u64 read = guest::sym("vorbis_synthesis_read");
    u64 alloc = guest::sym("_ZN4Aska11SoundMemory13ResourceAllocEmm");
    u64 free = guest::sym("_ZN4Aska11SoundMemory12ResourceFreeEPv");
    u64 pool_size = guest::sym("_ZN4Aska7AskaOGG18m_uiDecodePoolSizeE");
};
const OggFns& fns() {
    static const OggFns f;
    return f;
}

// What a checked call did (live check only; null otherwise).
struct OggObs {
    struct Call {
        const char* what;
        u64 a = 0, b = 0;  // the arguments that identify it (decoder pointers as offsets into it)
        u64 result = 0;
        std::vector<u8> bytes;           // packetout: the packet written
        std::vector<std::vector<float>> rows;  // pcmout: the channels' samples
        std::vector<u64> table;          // ... and the float** the replay hands out
        bool same(const Call& o) const { return !strcmp(what, o.what) && a == o.a && b == o.b; }
    };
    const AskaOGG* self = nullptr;
    std::vector<Call> calls;
    u64 written_end = 0;  // the out buffer's bytes written: [0, written_end) (a grown block holds garbage past it)
    Call& log(const char* what, u64 a, u64 b, u64 result) {
        calls.push_back({what, a, b, result});
        return calls.back();
    }
    u64 rel(const void* p) const {  // a pointer into the decoder as its offset (+ a tag), else as is
        u64 v = (u64)p;
        return v >= (u64)self && v < (u64)self + sizeof(AskaOGG) ? 0xa5a0000000000000ull + (v - (u64)self) : v;
    }
};
thread_local OggObs* t_oobs = nullptr;

s32 packetout(AskaOGG* o) {
    s32 r = (s32)guest_call(fns().packetout, {(u64)&o->m_stream, (u64)&o->m_packet});
    if (t_oobs) {
        auto& k = t_oobs->log("packetout", t_oobs->rel(&o->m_stream), t_oobs->rel(&o->m_packet), (u32)r);
        k.bytes.assign((const u8*)&o->m_packet, (const u8*)&o->m_packet + sizeof o->m_packet);
    }
    return r;
}
s32 synthesis(AskaOGG* o) {
    s32 r = (s32)guest_call(fns().synthesis, {(u64)&o->m_block, (u64)&o->m_packet});
    if (t_oobs) t_oobs->log("synthesis", t_oobs->rel(&o->m_block), t_oobs->rel(&o->m_packet), (u32)r);
    return r;
}
s32 blockin(AskaOGG* o) {
    s32 r = (s32)guest_call(fns().blockin, {(u64)&o->m_dsp, (u64)&o->m_block});
    if (t_oobs) t_oobs->log("blockin", t_oobs->rel(&o->m_dsp), t_oobs->rel(&o->m_block), (u32)r);
    return r;
}
s32 pcmout(AskaOGG* o, float*** pcm) {
    s32 r = (s32)guest_call(fns().pcmout, {(u64)&o->m_dsp, (u64)pcm});
    if (t_oobs) {
        auto& k = t_oobs->log("pcmout", t_oobs->rel(&o->m_dsp), pcm != nullptr, (u32)r);
        if (r > 0 && pcm)
            for (s32 c = 0; c < o->m_info.channels; c++) k.rows.emplace_back((*pcm)[c], (*pcm)[c] + r);
    }
    return r;
}
s32 read(AskaOGG* o, s32 n) {
    s32 r = (s32)guest_call(fns().read, {(u64)&o->m_dsp, (u64)(u32)n});
    if (t_oobs) t_oobs->log("read", t_oobs->rel(&o->m_dsp), (u32)n, (u32)r);
    return r;
}
s8* resource_alloc(u64 size, u64 align) {
    auto* p = reinterpret_cast<s8*>(guest_call(fns().alloc, {size, align}));
    if (t_oobs) t_oobs->log("ResourceAlloc", size, align, (u64)p);
    return p;
}
void resource_free(void* p) {
    guest_call(fns().free, {(u64)p});
    if (t_oobs) t_oobs->log("ResourceFree", (u64)p, 0, 0);
}

// FCVTMS (float -> int32, toward -inf): saturating, NaN -> 0.
s32 cvtms(float f) {
    if (std::isnan(f)) return 0;
    float r = std::floor(f);
    if (r >= 2147483648.0f) return INT32_MAX;
    if (r < -2147483648.0f) return INT32_MIN;
    return (s32)r;
}

}  // namespace

s64 AskaOGG::Decode_Pcmout(u32 offset) {
    const float scale = *reinterpret_cast<const float*>(main_lib()->base + kOggPcmScale);
    const s32 frameBytes = m_info.channels * 2;
    s64 frames = 0;
    for (;;) {
        float** pcm = nullptr;
        s32 n = pcmout(this, &pcm);
        if (n == 0) return frames;
        if (n < 0) return -1;
        u32 at = offset + (u32)(s32)frames * (u32)frameBytes;  // (32-bit, as the guest's mul)
        u32 size = m_bufferSizes[m_bufferIndex];
        while (size < at + (u32)n * (u32)frameBytes) {  // grow by 64 KiB (the pool size follows)
            s8* old = m_buffers[m_bufferIndex];
            s8* grown = resource_alloc((u64)size + 0x10000, 0x200);
            if (!grown) return kErrNoMemory;
            std::memcpy(grown, old, m_bufferSizes[m_bufferIndex]);
            resource_free(old);
            m_buffers[m_bufferIndex] = grown;
            m_bufferSizes[m_bufferIndex] = (size + 0x101ff) & ~0x1ffu;
            *reinterpret_cast<u32*>(fns().pool_size) = size + 0x10000;
            size = m_bufferSizes[m_bufferIndex];
        }
        s8* dst = m_buffers[m_bufferIndex] + at;
        if (t_oobs) t_oobs->written_end = std::max<u64>(t_oobs->written_end, (u64)at + (u64)n * (u64)frameBytes);
        if (!dst) return kErrNoMemory;
        const s32 channels = m_info.channels;
        for (s32 c = 0; c < channels; c++) {
            auto* out = reinterpret_cast<s16*>(dst) + c;
            const float* in = pcm[c];
            for (s32 i = 0; i < n; i++) {
                s32 v = cvtms(in[i] * scale + 0.5f);
                if (v > 0x7fff) v = 0x7fff;
                if (v <= -0x8000) v = -0x8000;
                *out = (s16)v;
                out += channels;
            }
        }
        s32 r = read(this, n);
        frames += n;
        if (r != 0) return kErrStream;
    }
}

s64 AskaOGG::DecodePackets(u32 offset, u32 maxFrames) {
    // The frame target: the short one when the caller's budget fits it, none without a rate.
    u32 limit = 0xffffffffu;
    if (m_framesLong != 0) limit = (maxFrames <= m_framesShort && m_framesShort != 0 ? m_framesShort : m_framesLong) - 1;
    u64 bytes = 0;
    u32 frames = 0;
    m_hasPending = 0;
    for (;;) {
        s32 r;
        do {
            r = packetout(this);
            if (r == 0) return (s64)bytes;
        } while (r < 0);  // (a hole in the stream: the next packet)
        if (synthesis(this) == 0 && blockin(this) != 0) return kErrStream;
        s64 n = Decode_Pcmout((u32)bytes + offset);
        if (n < 0) return n;
        frames += (u32)n;
        bytes += (u64)(u32)n * 2 * (u64)(s64)m_info.channels;
        if (m_loopEnd == 0 && frames > limit && !m_pageEos) break;
    }
    m_hasPending = 1;
    return (s64)bytes;
}

// ---- The live check (audio_check.h) ----

namespace {

CheckedFn g_packets("_ZN4Aska7AskaOGG13DecodePacketsEjj"), g_pcmout("_ZN4Aska7AskaOGG13Decode_PcmoutEj");

struct Shadow {
    alignas(16) AskaOGG o;
    const AskaOGG* real;
    std::vector<std::unique_ptr<u8[]>> scratch;
    std::vector<std::pair<u64, u64>> map;  // (scratch, real) block starts
    std::vector<u32> sizes;

    Shadow(const AskaOGG* r, const AskaOGG& pre, const std::vector<u8>& pre_buffer) : real(r) {
        std::memcpy((void*)&o, &pre, sizeof o);
        if (pre.m_buffers[pre.m_bufferIndex]) o.m_buffers[o.m_bufferIndex] = (s8*)block((u64)pre.m_buffers[pre.m_bufferIndex], pre_buffer.data(), (u32)pre_buffer.size());
    }
    u8* block(u64 real_ptr, const u8* init, u32 n) {
        scratch.emplace_back(new u8[n ? n : 1]);
        if (init) std::memcpy(scratch.back().get(), init, n);
        map.emplace_back((u64)scratch.back().get(), real_ptr);
        sizes.push_back(n);
        return scratch.back().get();
    }
    u64 to_real(u64 p) const {
        for (auto& [s, r] : map)
            if (p == s) return r;
        if (p >= (u64)&o && p < (u64)&o + sizeof o) return (u64)real + (p - (u64)&o);
        return p;
    }
    u64 rel(u64 p) const {  // as OggObs::rel
        return p >= (u64)&o && p < (u64)&o + sizeof o ? 0xa5a0000000000000ull + (p - (u64)&o) : to_real(p);
    }
};

// Runs `native` for real, then the guest original on the shadow (x1, x2 its arguments).
void ogg_check(CheckedFn& f, AskaOGG* self, s64 (*native)(AskaOGG*, u64, u64), u64 x1, u64 x2, s64* result) {
    const OggFns& g = fns();
    // (the last: Decode_Pcmout, DecodePackets' callee, answered by its guest original on the shadow)
    const u64 targets[] = {g.packetout, g.synthesis, g.blockin, g.pcmout, g.read, g.alloc, g.free, guest::sym("_ZN4Aska7AskaOGG13Decode_PcmoutEj")};
    const char* stubs[8];
    for (int i = 0; i < 8; i++)
        if (!(stubs[i] = live::ensure_stub(targets[i]))) {
            *result = native(self, x1, x2);
            return live::check_result(f, live::Outcome::Skipped, "callees can't be stubbed");
        }
    live::CheckScope scope;
    auto pre = std::make_unique<AskaOGG>();
    std::memcpy((void*)pre.get(), self, sizeof *pre);
    std::vector<u8> pre_buffer;
    if (const s8* b = self->m_buffers[self->m_bufferIndex]) pre_buffer.assign((const u8*)b, (const u8*)b + self->m_bufferSizes[self->m_bufferIndex]);
    OggObs obs;
    obs.self = self;
    t_oobs = &obs;
    *result = native(self, x1, x2);
    t_oobs = nullptr;
    auto sh = std::make_unique<Shadow>(self, *pre, pre_buffer);
    std::vector<OggObs::Call> calls;
    size_t next = 0;
    auto take = [&](const char* what, u64 a, u64 b) -> OggObs::Call* {
        calls.push_back({what, a, b});
        if (next < obs.calls.size() && !strcmp(obs.calls[next].what, what)) return &obs.calls[next++];
        next = obs.calls.size();  // out of step: answer nothing more
        return nullptr;
    };
    s64 guest_result;
    {
        live::ReplaySession s;
        s.answer(stubs[0], [&](Cpu& c) {
            OggObs::Call* k = take("packetout", sh->rel(c.x(0)), sh->rel(c.x(1)));
            if (k && c.x(1)) std::memcpy((void*)c.x(1), k->bytes.data(), k->bytes.size());
            c.set_x(0, k ? k->result : 0);
        });
        s.answer(stubs[1], [&](Cpu& c) {
            OggObs::Call* k = take("synthesis", sh->rel(c.x(0)), sh->rel(c.x(1)));
            c.set_x(0, k ? k->result : (u64)-1);
        });
        s.answer(stubs[2], [&](Cpu& c) {
            OggObs::Call* k = take("blockin", sh->rel(c.x(0)), sh->rel(c.x(1)));
            c.set_x(0, k ? k->result : (u64)-1);
        });
        s.answer(stubs[3], [&](Cpu& c) {
            OggObs::Call* k = take("pcmout", sh->rel(c.x(0)), c.x(1) != 0);
            if (k && c.x(1) && !k->rows.empty()) {
                k->table.clear();
                for (auto& row : k->rows) k->table.push_back((u64)row.data());
                *reinterpret_cast<u64*>(c.x(1)) = (u64)k->table.data();
            }
            c.set_x(0, k ? k->result : 0);
        });
        s.answer(stubs[4], [&](Cpu& c) {
            OggObs::Call* k = take("read", sh->rel(c.x(0)), c.x(1) & 0xffffffff);
            c.set_x(0, k ? k->result : (u64)-1);
        });
        s.answer(stubs[5], [&](Cpu& c) {
            OggObs::Call* k = take("ResourceAlloc", c.x(0), c.x(1));
            c.set_x(0, k && k->result ? (u64)sh->block(k->result, nullptr, (u32)c.x(0)) : 0);
        });
        s.answer(stubs[6], [&](Cpu& c) {
            take("ResourceFree", sh->to_real(c.x(0)), 0);
            c.set_x(0, 0);
        });
        if (&f == &g_packets)
            s.answer(stubs[7], [&](Cpu& c) { c.set_x(0, guest_call(g_pcmout.orig, {c.x(0), c.x(1) & 0xffffffff})); });
        for (u64 t : targets) live::drop_stale_code(t);
        guest_result = (s64)guest_call(f.orig, {(u64)&sh->o, x1, x2});
    }
    std::string why;
    if (calls.size() != obs.calls.size()) why = "calls: native " + std::to_string(obs.calls.size()) + " guest " + std::to_string(calls.size());
    for (size_t i = 0; why.empty() && i < calls.size(); i++)
        if (!calls[i].same(obs.calls[i])) why = "call " + std::to_string(i) + ": native " + obs.calls[i].what + " guest " + calls[i].what;
    if (why.empty() && guest_result != *result) why = "result: native " + std::to_string(*result) + " guest " + std::to_string(guest_result);
    if (why.empty()) {
        AskaOGG gs;
        std::memcpy((void*)&gs, &sh->o, sizeof gs);
        for (s8*& b : gs.m_buffers) b = reinterpret_cast<s8*>(sh->to_real((u64)b));
        why = live::diff_bytes(reinterpret_cast<const u8*>(self), reinterpret_cast<const u8*>(&gs), offsetof(AskaOGG, m_pendingData), sizeof(AskaOGG));
    }
    if (why.empty()) {
        // The current out buffer (the shadow's: the copy, or the block a growth answered).
        u32 idx = self->m_bufferIndex;
        u64 n = std::min<u64>(self->m_bufferSizes[idx], std::max<u64>(obs.written_end, pre_buffer.size()));
        bool grew = false;
        for (const OggObs::Call& k : obs.calls) grew |= !strcmp(k.what, "ResourceAlloc");
        if (grew) n = std::min<u64>(n, obs.written_end);  // (past it: the new blocks' leftovers)
        const u8* real_buf = (const u8*)self->m_buffers[idx];
        const u8* sh_buf = (const u8*)sh->o.m_buffers[idx];
        size_t have = 0;
        for (size_t i = 0; i < sh->map.size(); i++)
            if (sh->map[i].first == (u64)sh_buf) have = sh->sizes[i];
        if (real_buf && sh_buf && have >= n) {
            why = live::diff_bytes(real_buf, sh_buf, 0, n);
            if (!why.empty()) why = "out buffer " + why;
        } else if (real_buf || sh_buf) {
            why = "out buffer: native " + std::to_string((u64)real_buf != 0) + " guest " + std::to_string((u64)sh_buf != 0) + " (" + std::to_string(have) + " bytes)";
        }
    }
    live::check_result(f, why.empty() ? live::Outcome::Ok : live::Outcome::Mismatch, why);
}

s64 run_packets(AskaOGG* o, u64 a, u64 b) { return o->DecodePackets((u32)a, (u32)b); }
s64 run_pcmout(AskaOGG* o, u64 a, u64) { return o->Decode_Pcmout((u32)a); }

void packets_checked(Cpu& c) {
    auto* self = reinterpret_cast<AskaOGG*>(c.x(0));
    if (!live::check_due(g_packets)) return c.set_x(0, (u64)self->DecodePackets((u32)c.x(1), (u32)c.x(2)));
    s64 r = 0;
    ogg_check(g_packets, self, run_packets, c.x(1) & 0xffffffff, c.x(2) & 0xffffffff, &r);
    c.set_x(0, (u64)r);
}
void pcmout_checked(Cpu& c) {
    auto* self = reinterpret_cast<AskaOGG*>(c.x(0));
    if (!live::check_due(g_pcmout)) return c.set_x(0, (u64)self->Decode_Pcmout((u32)c.x(1)));
    s64 r = 0;
    ogg_check(g_pcmout, self, run_pcmout, c.x(1) & 0xffffffff, 0, &r);
    c.set_x(0, (u64)r);
}

}  // namespace

NATIVE_FUNCTION_ORIG("_ZN4Aska7AskaOGG13DecodePacketsEjj", packets_checked, "audio: Aska::AskaOGG::DecodePackets", &g_packets.orig);
NATIVE_FUNCTION_ORIG("_ZN4Aska7AskaOGG13Decode_PcmoutEj", pcmout_checked, "audio: Aska::AskaOGG::Decode_Pcmout", &g_pcmout.orig);

}  // namespace soa::native::audio
