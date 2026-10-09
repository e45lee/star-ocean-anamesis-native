// Differential tests of the SLVoice submit path and WaveBuffer's lock / unlock (audio_voice.cpp): two
// private voices (ADPCM, OGG or PCM; random queue states, pending counts, failed / armed flags), each with
// its own wave buffer over a fake stream (a fake vtable: IsEnd / Lock / Unlock), a fake buffer-queue
// interface (Enqueue) and private decode buffers; AskaOGG::Decode, VBRBuffer::LockBufferEx and
// SoundServer::AcquireAskaAdpcmDecodeBuffer stubbed. The fakes and stubs answer from one scripted sequence
// per round (the n-th call of a kind gets the n-th answer on both sides). One voice runs the guest's
// AudioSignal / ProcAudioBuffer / LockAndSubmit* / SubmitDummyData*, the other the natives; the call logs
// (objects by name), the voices' and the buffers' bytes (pointers by name) must match.
#include <cstring>
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

// The scripted answers, by kind and call index (the same for both sides).
struct Script {
    std::vector<u64> is_end, lock, unlock, enqueue, decode, lock_ex, acquire;
};

struct Side {
    alignas(16) SLVoice v;
    alignas(16) WaveBuffer buffer;
    std::unique_ptr<WaveStreamView> stream{new WaveStreamView()};
    alignas(16) AaoWAVE format;
    alignas(16) u64 itf_table[4] = {};
    u64 itf = 0;
    alignas(16) u8 data[0x8000];                       // what Lock / LockBufferEx hand out
    alignas(16) u8 decode[3][SLVoice::kDecodeBufferSize];
    alignas(16) u8 pool_buffer[SLVoice::kDecodeBufferSize];
    alignas(16) u8 ogg_out[0x100];
    std::vector<std::string> log;
    size_t n_is_end = 0, n_lock = 0, n_unlock = 0, n_enqueue = 0, n_decode = 0, n_lock_ex = 0, n_acquire = 0;

    std::string name(u64 p) const {
        auto in = [&](const void* base, size_t n) { return p >= (u64)base && p < (u64)base + n; };
        if (!p) return "null";
        if (in(data, sizeof data)) return "data+" + std::to_string(p - (u64)data);
        for (int i = 0; i < 3; i++)
            if (in(decode[i], sizeof decode[i])) return "decode" + std::to_string(i) + "+" + std::to_string(p - (u64)decode[i]);
        if (in(pool_buffer, sizeof pool_buffer)) return "pool+" + std::to_string(p - (u64)pool_buffer);
        if (in(ogg_out, sizeof ogg_out)) return "oggout+" + std::to_string(p - (u64)ogg_out);
        if (p == (u64)&buffer) return "buffer";
        if (p == (u64)stream.get()) return "stream";
        if (p == (u64)&itf) return "itf";
        if (in(&v, sizeof v)) return "voice+" + std::to_string(p - (u64)&v);
        return "ext";  // (the sound manager's dummy buffer)
    }
};

struct Rig {
    TestContext& t;
    Script sc;
    Side g, n;

    Rig(TestContext& tc, u32 codec) : t(tc) {
        static const u64 fIsEnd = fake_function("audio.t.is-end", 3), fLock = fake_function("audio.t.lock", 4),
                         fUnlock = fake_function("audio.t.unlock", 2), fEnqueue = fake_function("audio.t.enqueue", 3);
        stub("_ZN4Aska7AskaOGG6DecodeEPKajPPajjj", "audio.t.ogg-decode", 7);
        stub("_ZN4Aska9VBRBuffer12LockBufferExEPPvmPmS3_mb", "audio.t.lock-ex", 7);
        stub("_ZN4Aska11SoundServer28AcquireAskaAdpcmDecodeBufferEv", "audio.t.acquire", 1);
        auto pick = [&](std::vector<u64>& out, int count, auto gen) {
            for (int i = 0; i < count; i++) out.push_back(gen());
        };
        pick(sc.is_end, 200, [&] { return (u64)(t.rand_int(0, 9) == 0); });
        pick(sc.lock, 200, [&] {
            int k = t.rand_int(0, 9);
            return k == 0 ? (u64)-5 : k <= 2 ? 0 : (u64)(t.rand_int(1, 0x40) * 0x40);
        });
        pick(sc.unlock, 200, [&] { return (u64)t.rand_int(0, 1); });
        pick(sc.enqueue, 200, [&] { return (u64)(t.rand_int(0, 15) == 0 ? 3 : 0); });
        pick(sc.decode, 200, [&] {
            int k = t.rand_int(0, 9);
            return k == 0 ? (u64)-7 : k <= 2 ? 0 : (u64)t.rand_int(1, 0x2000);
        });
        pick(sc.lock_ex, 200, [&] {
            int k = t.rand_int(0, 9);
            return k == 0 ? (u64)-6 : k <= 2 ? 0 : (u64)t.rand_int(1, 0x2000);
        });
        pick(sc.acquire, 50, [&] { return (u64)(t.rand_int(0, 6) != 0); });
        // the voice's random state (the same for both sides)
        alignas(16) SLVoice tmpl;
        for (u32 k = 0; k < sizeof tmpl; k++) reinterpret_cast<u8*>(&tmpl)[k] = (u8)t.rand_int(0, 255);
        tmpl.vtable = (const void*)(t.sym("_ZTVN4Aska7SLVoiceE") + 0x10);
        tmpl.m_codec = codec;
        tmpl.m_failed = (u8)(t.rand_int(0, 7) == 0);
        tmpl.m_countdownArmed = (u8)t.rand_int(0, 1);
        tmpl.m_pendingBuffers = t.rand_int(-1, 5);
        tmpl.m_queuedBytes = t.rand_int(0, 0x20000);
        tmpl.m_adpcmWrite = (u32)t.rand_int(0, 3);
        tmpl.m_adpcmRead = (u32)t.rand_int(0, 3);
        tmpl.m_oggWrite = (u32)t.rand_int(0, 8);
        tmpl.m_oggRead = (u32)t.rand_int(0, 8);
        for (auto& b : tmpl.m_adpcmLocked) b = (u8)t.rand_int(0, 1);
        for (auto& s : tmpl.m_oggSubmits) s = (u64)t.rand_int(0, 0x2000) | (u64)t.rand_int(0, 1) << 32;
        tmpl.m_lockSize = 0x800;
        tmpl.m_queueDepth = (u32)t.rand_int(0, 4);
        tmpl.m_submitCount = (u32)t.rand_int(0, 3);
        tmpl.m_decodeIndex = (u32)t.rand_int(0, 2);
        tmpl.m_ogg.m_hasPending = (u8)(t.rand_int(0, 3) == 0);
        tmpl.m_ogg.m_pendingSize = (u32)t.rand_int(1, 0x400);
        alignas(16) WaveBuffer btmpl;
        for (u32 k = 0; k < sizeof btmpl; k++) reinterpret_cast<u8*>(&btmpl)[k] = (u8)t.rand_int(0, 255);
        btmpl.m_write = (u32)t.rand_int(0, 16);
        btmpl.m_read = (u32)t.rand_int(0, 16);
        alignas(16) AaoWAVE ftmpl;
        std::memset((void*)&ftmpl, 0, sizeof ftmpl);
        ftmpl.m_channels = (u8)t.rand_int(1, 2);
        ftmpl.m_bits = t.rand_int(0, 1) ? 16 : 8;
        ftmpl.m_loopHeadFrames = (u32)t.rand_int(0, 8);
        ftmpl.m_loopTailFrames = (u32)t.rand_int(0, 8);
        u8 loop_tail = (u8)t.rand_int(0, 1);
        int null_buffers = t.rand_int(0, 7);
        std::vector<u8> in = t.rand_bytes(sizeof g.data);
        for (Side* s : {&g, &n}) {
            std::memcpy((void*)&s->v, &tmpl, sizeof tmpl);
            std::memcpy((void*)&s->buffer, &btmpl, sizeof btmpl);
            std::memcpy((void*)&s->format, &ftmpl, sizeof ftmpl);
            std::memcpy(s->data, in.data(), sizeof s->data);
            std::memset(s->decode, 0, sizeof s->decode);
            std::memset(s->pool_buffer, 0, sizeof s->pool_buffer);
            std::memset(s->ogg_out, 0, sizeof s->ogg_out);
            t.call("_ZN4Aska19FastCriticalSectionC1Ev", {(u64)&s->v.m_cs});
            s->v.m_adpcm = {};
            s->v.m_adpcm.m_channels = ftmpl.m_channels;
            s->v.m_adpcm.m_bits = 16;
            s->v.m_adpcm.m_blockSize = 0x40;
            s->v.m_format = &s->format;
            s->v.m_buffer = &s->buffer;
            s->buffer.m_stream = s->stream.get();
            s->buffer.m_format = &s->format;
            static u64 stream_vtable[32];
            stream_vtable[WaveStreamView::kSlotIsEnd] = fIsEnd;
            stream_vtable[WaveStreamView::kSlotLock] = fLock;
            stream_vtable[WaveStreamView::kSlotUnlock] = fUnlock;
            s->stream->vtable = stream_vtable;
            s->stream->m_loopTail = loop_tail;
            s->itf_table[0] = fEnqueue;
            s->itf = (u64)s->itf_table;
            s->v.m_bufferQueue = reinterpret_cast<SLItf>(&s->itf);
            for (int i = 0; i < 3; i++) s->v.m_decodeBuffers[i] = (null_buffers >> i) & 1 ? nullptr : s->decode[i];
            s->v.m_ogg.m_pendingData = reinterpret_cast<const s8*>(s->data + 0x100);
        }
    }
    ~Rig() {
        for (Side* s : {&g, &n}) t.call("_ZN4Aska19FastCriticalSectionD1Ev", {(u64)&s->v.m_cs});
    }

    struct Session {
        StubSession ss;
        Session(Rig& r, Side& s) {
            ss.only = {"audio.t.is-end", "audio.t.lock", "audio.t.unlock", "audio.t.enqueue", "audio.t.ogg-decode", "audio.t.lock-ex", "audio.t.acquire"};
            auto at = [](const std::vector<u64>& v, size_t& i, u64 dflt) { return i < v.size() ? v[i++] : dflt; };
            Script& sc = r.sc;
            ss.behave["audio.t.is-end"] = [&, at](Cpu& c) {
                u64 res = at(sc.is_end, s.n_is_end, 1);
                s.log.push_back("IsEnd " + s.name(c.x(0)) + " " + std::to_string(c.x(1) & 0xff) + " " + std::to_string(c.x(2) & 0xffffffff) + " -> " + std::to_string(res));
                c.set_x(0, res | 0x100);
            };
            ss.behave["audio.t.lock"] = [&, at](Cpu& c) {
                u64 res = at(sc.lock, s.n_lock, (u64)-1);
                // (as MultiMediaStream::Lock: nothing written when nothing is locked)
                if ((s64)res > 0) *reinterpret_cast<u64*>(c.x(1)) = (u64)(s.data + (s.n_lock * 0x40) % 0x4000);
                s.log.push_back("Lock " + s.name(c.x(0)) + " " + std::to_string(c.x(2)) + " " + std::to_string(c.x(3) & 0xff) + " -> " + std::to_string((s64)res));
                c.set_x(0, res);
            };
            ss.behave["audio.t.unlock"] = [&, at](Cpu& c) {
                u64 res = at(sc.unlock, s.n_unlock, 0);
                s.log.push_back("Unlock " + s.name(c.x(0)) + " " + std::to_string(c.x(1) & 0xffffffff));
                c.set_x(0, res);
            };
            ss.behave["audio.t.enqueue"] = [&, at](Cpu& c) {
                u64 res = at(sc.enqueue, s.n_enqueue, 0);
                // (a 0-byte Enqueue: the guest passes an uninitialized pointer, the native null: not compared)
                u32 size = (u32)c.x(2);
                s.log.push_back("Enqueue " + s.name(c.x(0)) + " " + (size ? s.name(c.x(1)) : std::string("-")) + " " + std::to_string(size));
                c.set_x(0, res);
            };
            ss.behave["audio.t.ogg-decode"] = [&, at](Cpu& c) {
                u64 res = at(sc.decode, s.n_decode, (u64)-1);
                *reinterpret_cast<u64*>(c.x(3)) = (u64)s.ogg_out;
                s.v.m_ogg.m_hasPending = (u8)(s.n_decode % 3 == 1);  // (the decoder's state after the call)
                s.log.push_back("Decode " + s.name(c.x(0)) + " " + s.name(c.x(1)) + " " + std::to_string(c.x(2) & 0xffffffff) + " " +
                                std::to_string(c.x(4) & 0xffffffff) + " " + std::to_string(c.x(5) & 0xffffffff) + " " + std::to_string(c.x(6) & 0xffffffff));
                c.set_x(0, res);
            };
            ss.behave["audio.t.lock-ex"] = [&, at](Cpu& c) {
                u64 res = at(sc.lock_ex, s.n_lock_ex, (u64)-1);
                *reinterpret_cast<u64*>(c.x(1)) = (u64)(s.data + (s.n_lock_ex * 0x80) % 0x4000);
                *reinterpret_cast<u64*>(c.x(3)) = s.n_lock_ex * 3;
                *reinterpret_cast<u64*>(c.x(4)) = s.n_lock_ex * 5;
                s.buffer.m_write = (u32)(s.n_lock_ex % 17);  // (the buffer's state after the call)
                s.log.push_back("LockBufferEx " + s.name(c.x(0)) + " " + std::to_string(c.x(2)) + " " + std::to_string(c.x(5)) + " " + std::to_string(c.x(6) & 0xff));
                c.set_x(0, res);
            };
            ss.behave["audio.t.acquire"] = [&, at](Cpu& c) {
                u64 res = at(sc.acquire, s.n_acquire, 0);
                s.log.push_back("Acquire");
                c.set_x(0, res ? (u64)s.pool_buffer : 0);
            };
        }
    };

    void compare(const std::string& what) {
        if (g.log != n.log) {
            t.fail("%s: logs differ (guest %zu, native %zu)", what.c_str(), g.log.size(), n.log.size());
            for (size_t i = 0; i < g.log.size() || i < n.log.size(); i++)
                t.fail("  %s | %s", i < g.log.size() ? g.log[i].c_str() : "-", i < n.log.size() ? n.log[i].c_str() : "-");
        }
        // the voices' bytes, the pointers by name, the lock region skipped (its semaphore pointer differs)
        auto norm = [](const Side& s) {
            SLVoice v = s.v;
            for (u8*& b : v.m_decodeBuffers) b = nullptr;  // (compared by name below)
            v.m_buffer = nullptr;
            v.m_format = nullptr;
            v.m_bufferQueue = nullptr;
            v.m_ogg.m_pendingData = nullptr;
            std::memset((void*)&v.m_cs, 0, sizeof v.m_cs);
            return v;
        };
        SLVoice a = norm(g), b = norm(n);
        if (std::memcmp(&a, &b, sizeof a) != 0) {
            size_t k = 0;
            while (reinterpret_cast<u8*>(&a)[k] == reinterpret_cast<u8*>(&b)[k]) k++;
            t.fail("%s: the voices differ at +0x%zx", what.c_str(), k);
        }
        for (int i = 0; i < 3; i++)
            if (g.name((u64)g.v.m_decodeBuffers[i]) != n.name((u64)n.v.m_decodeBuffers[i])) t.fail("%s: decode buffer %d differs", what.c_str(), i);
        WaveBuffer ba = g.buffer, bb = n.buffer;
        ba.m_stream = bb.m_stream = nullptr;
        ba.m_format = bb.m_format = nullptr;
        if (std::memcmp(&ba, &bb, sizeof ba) != 0) t.fail("%s: the wave buffers differ", what.c_str());
        if (std::memcmp(g.decode, n.decode, sizeof g.decode) != 0 || std::memcmp(g.pool_buffer, n.pool_buffer, sizeof g.pool_buffer) != 0)
            t.fail("%s: the decoded data differs", what.c_str());
        if (n.v.m_cs.m_lock != FastCriticalSection::kFree) t.fail("%s: lock left held", what.c_str());
    }
};

struct Op {
    const char* name;
    const char* sym;
    bool x8;
};
const Op kOps[] = {
    {"AudioSignal", "_ZN4Aska7SLVoice11AudioSignalEm", false},
    {"ProcAudioBuffer", "_ZN4Aska7SLVoice15ProcAudioBufferEv", false},
    {"LockAndSubmitADPCM", "_ZN4Aska7SLVoice18LockAndSubmitADPCMEv", true},
    {"LockAndSubmitOGG", "_ZN4Aska7SLVoice16LockAndSubmitOGGEv", true},
    {"LockAndSubmitData", "_ZN4Aska7SLVoice17LockAndSubmitDataEv", true},
    {"SubmitDummyDataAdpcm", "_ZN4Aska7SLVoice20SubmitDummyDataAdpcmEv", false},
    {"SubmitDummyDataOgg", "_ZN4Aska7SLVoice18SubmitDummyDataOggEv", false},
};

s64 run_native(Side& s, int op) {
    switch (op) {
    case 0: s.v.AudioSignal(3); return 0;
    case 1: s.v.ProcAudioBuffer(); return 0;
    case 2: return s.v.LockAndSubmitADPCM();
    case 3: return s.v.LockAndSubmitOGG();
    case 4: return s.v.LockAndSubmitData();
    case 5: return s.v.SubmitDummyDataAdpcm();
    default: return s.v.SubmitDummyDataOgg();
    }
}

}  // namespace

NATIVE_TEST("audio/voice-submit") {
    if (!*reinterpret_cast<const u64*>(t.sym("_ZN4Aska6Global15m_pSoundManagerE"))) {
        t.fail("Global::m_pSoundManager is null (the sound manager isn't up)");
        return;
    }
    const u32 codecs[] = {SLVoice::kCodecADPCM, SLVoice::kCodecOGG, SLVoice::kCodecPCM};
    int enqueues = 0;
    for (int round = 0; round < 90 && !t.failures(); round++) {
        u32 codec = codecs[round % 3];
        auto rig = std::make_unique<Rig>(t, codec);
        Rig& r = *rig;
        for (int step = 0; step < 6 && !t.failures(); step++) {
            int op = round % 3 == 2 ? (step % 2 ? 1 : 4) : t.rand_int(0, 6);
            std::string what = "round " + std::to_string(round) + " step " + std::to_string(step) + " " + kOps[op].name;
            s64 gr = 0, nr;
            {
                Rig::Session s(r, r.g);
                alignas(16) s64 res = 0;
                GuestArgs a;
                a.p(&r.g.v).i(3);
                if (kOps[op].x8) a.sret(&res);
                GuestResult x = t.call(kOps[op].sym, a);
                gr = kOps[op].x8 ? res : (op >= 5 ? (s64)x.x0 : 0);
            }
            {
                Rig::Session s(r, r.n);
                nr = run_native(r.n, op);
            }
            if (gr != nr) t.fail("%s: result guest %lld native %lld", what.c_str(), (long long)gr, (long long)nr);
            r.compare(what);
            for (auto& l : r.g.log) enqueues += l.rfind("Enqueue", 0) == 0;
            r.g.log.clear();
            r.n.log.clear();
        }
    }
    if (enqueues < 50) t.fail("too few enqueues reached (%d)", enqueues);
}
