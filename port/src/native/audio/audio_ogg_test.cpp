// Differential test of the AskaOGG natives (audio_ogg.cpp): real Ogg Vorbis streams of the 3.7.0 download
// (two BGMs, stereo; read in place, skipped when the download is absent) decoded twice through the guest's AskaOGG::Decode, the way SLVoice::LockAndSubmitOGG
// drives it (chunks of the stream, a frame budget, the pending source handed back while m_hasPending),
// over two decoders built by the guest's constructor and DecodeInit. On one side everything is the guest's
// (no natives in --selftest); on the other DecodePackets and Decode_Pcmout are stubbed by the native members
// (DecodeBody and Decode_LoopStart call them through their entries). Both use the guest library. Every
// Decode's result, the PCM bytes it hands out (bit for bit), the decoders' own fields and the pool size
// must agree. Budgets range from a few frames to more than a buffer holds, the frame targets stop decodes
// midway, small buffers (the pool size set low) grow, and with a loop end (Decode's last argument)
// Decode_LoopStart runs too.
#include <cstdio>
#include <cstring>
#include <memory>
#include <string>
#include <vector>

#include "core/cpu.h"
#include "native/audio/audio_layout.h"
#include "native/common/guest_stub.h"
#include "native/common/test.h"
#include "native/common/test_assets.h"

using namespace soa;
using namespace soa::native;
using namespace soa::native::audio;

namespace {

// The Ogg pages of a download file (from the first "OggS" on), its stored bytes or, for an ADLD one, its payload.
std::vector<u8> ogg_of(const std::string& rel, bool payload) {
    std::vector<u8> d = payload ? test_assets::download_payload(rel) : test_assets::download_file(rel);
    for (size_t i = 0; i + 4 <= d.size(); i++)
        if (!memcmp(d.data() + i, "OggS", 4)) return std::vector<u8>(d.begin() + (long)i, d.end());
    return {};
}

struct Step {
    u32 chunk, budget, loop_end;
};

struct Trace {
    std::vector<long long> results;
    std::vector<u8> pcm;
    int pendings = 0;
};

struct Decoder {
    std::unique_ptr<AskaOGG> o{new AskaOGG()};
    Decoder(TestContext& t, u32 total, u32 loop_start) {
        std::memset((void*)o.get(), 0, sizeof *o);
        t.call("_ZN4Aska7AskaOGGC1Ev", {(u64)o.get()});
        s64 r = -1;
        t.call("_ZN4Aska7AskaOGG10DecodeInitEjj", GuestArgs().p(o.get()).i(total).i(loop_start).sret(&r));
        if (r != 0) t.fail("DecodeInit: %lld", (long long)r);
    }
    void done(TestContext& t) { t.call("_ZN4Aska7AskaOGG13DecodeContextD1Ev", {(u64)o.get()}); }
};

// Feeds the stream as LockAndSubmitOGG does: a chunk, then the pending source again while the decoder has one.
Trace run(TestContext& t, Decoder& dec, const std::vector<u8>& d, const std::vector<Step>& steps) {
    Trace tr;
    size_t pos = 0;
    for (const Step& s : steps) {
        if (pos >= d.size()) break;
        AskaOGG& o = *dec.o;
        const s8* data;
        u32 size, loop_end;
        if (o.m_hasPending) {
            data = o.m_pendingData;
            size = o.m_pendingSize;
            loop_end = 0;
            tr.pendings++;
        } else {
            data = (const s8*)d.data() + pos;
            size = (u32)std::min<size_t>(s.chunk, d.size() - pos);
            loop_end = s.loop_end;
            pos += size;
        }
        s8* out = nullptr;
        s64 r = (s64)t.call("_ZN4Aska7AskaOGG6DecodeEPKajPPajjj", {(u64)&o, (u64)data, size, (u64)&out, s.budget, 0, loop_end});
        tr.results.push_back(r);
        if (r > 0 && out) tr.pcm.insert(tr.pcm.end(), (const u8*)out, (const u8*)out + r);
        if (r < 0 && r != AskaOGG::kErrStream) break;  // (-0x3b8: not enough data yet, e.g. after a loop jump: feed on)
    }
    return tr;
}

}  // namespace

NATIVE_TEST("audio/ogg-decode") {
    stub("_ZN4Aska7AskaOGG13DecodePacketsEjj", "audio.t.ogg-packets", 3);
    stub("_ZN4Aska7AskaOGG13Decode_PcmoutEj", "audio.t.ogg-pcmout", 2);
    u32* pool = reinterpret_cast<u32*>(t.sym("_ZN4Aska7AskaOGG18m_uiDecodePoolSizeE"));
    const u32 pool0 = *pool;
    struct Src {
        const char* rel;
        bool payload;
    };
    std::vector<Src> srcs = {{"Sound/BAS_SYSTEM_BGM_07.aac", false}, {"Sound/BAS_BATTLE_BGM_01.aac", false}};
    long long bytes = 0, pendings = 0, decodes = 0, loop_pcmouts = 0, grown = 0;
    int streams = 0;
    for (const Src& src : srcs) {
        std::vector<u8> d = ogg_of(src.rel, src.payload);
        if (d.empty()) {
            fprintf(stderr, "    (%s missing: skipped)\n", src.rel);
            continue;
        }
        streams++;
        for (int variant = 0; variant < 4 && !t.failures(); variant++) {
            // variant 0: the voice's usual budgets; 1: tiny budgets (many pending decodes); 2: huge ones
            // (the buffers grow); 3: loop ends now and then (Decode_LoopStart).
            std::vector<Step> steps;
            for (int i = 0; i < 400; i++) {
                Step s{(u32)t.rand_int(0x400, 0x2000), 0, 0};
                switch (variant) {
                case 0: s.budget = (u32)t.rand_int(0x400, 0x1000); break;
                case 1: s.budget = (u32)t.rand_int(1, 0x100); break;
                case 2: s.budget = (u32)t.rand_int(0x8000, 0x40000); break;
                default:
                    s.budget = (u32)t.rand_int(0x200, 0x2000);
                    if (i > 8 && t.rand_int(0, 15) == 0) s.loop_end = (u32)t.rand_int(0x7c0, 0x800);  // (DecodeBody takes (0x800 - it) frames off)
                    break;
                }
                steps.push_back(s);
            }
            u32 total = variant == 3 ? 0x800 : 0, loop_start = variant == 3 ? (u32)t.rand_int(0, 0x4000) : 0;
            const u32 pool_start = variant == 2 ? 0x1000 : pool0;  // variant 2: small buffers, which grow
            *pool = pool_start;
            Decoder g(t, total, loop_start);
            Trace tg = run(t, g, d, steps);
            u32 pool_g = *pool;
            *pool = pool_start;
            Decoder n(t, total, loop_start);
            Trace tn;
            {
                StubSession ss;
                ss.only = {"audio.t.ogg-packets", "audio.t.ogg-pcmout"};
                ss.behave["audio.t.ogg-packets"] = [](Cpu& c) {
                    c.set_x(0, (u64)reinterpret_cast<AskaOGG*>(c.x(0))->DecodePackets((u32)c.x(1), (u32)c.x(2)));
                };
                ss.behave["audio.t.ogg-pcmout"] = [](Cpu& c) { c.set_x(0, (u64)reinterpret_cast<AskaOGG*>(c.x(0))->Decode_Pcmout((u32)c.x(1))); };
                tn = run(t, n, d, steps);
                int from_loop = 0;
                for (const std::string& l : ss.log) from_loop += l.rfind("audio.t.ogg-pcmout", 0) == 0;
                if (ss.log.empty()) t.fail("%s variant %d: the natives never ran", src.rel, variant);
                if (variant == 3) loop_pcmouts += from_loop;
            }
            u32 pool_n = *pool;
            std::string what = std::string(src.rel) + " variant " + std::to_string(variant);
            if (tg.results != tn.results) {
                size_t i = 0;
                while (i < tg.results.size() && i < tn.results.size() && tg.results[i] == tn.results[i]) i++;
                t.fail("%s: Decode %zu: guest %lld native %lld (%zu / %zu calls)", what.c_str(), i, i < tg.results.size() ? tg.results[i] : -999,
                       i < tn.results.size() ? tn.results[i] : -999, tg.results.size(), tn.results.size());
            }
            if (tg.pcm != tn.pcm) {
                size_t i = 0;
                while (i < tg.pcm.size() && i < tn.pcm.size() && tg.pcm[i] == tn.pcm[i]) i++;
                t.fail("%s: PCM byte %zu of %zu / %zu differs", what.c_str(), i, tg.pcm.size(), tn.pcm.size());
            }
            AskaOGG a = *g.o, b = *n.o;
            for (AskaOGG* x : {&a, &b})
                for (s8*& p : x->m_buffers) p = p ? (s8*)1 : nullptr;
            if (memcmp((const u8*)&a + offsetof(AskaOGG, m_pendingData) + 8, (const u8*)&b + offsetof(AskaOGG, m_pendingData) + 8,
                       sizeof(AskaOGG) - offsetof(AskaOGG, m_pendingData) - 8) != 0 ||
                (a.m_pendingData != nullptr) != (b.m_pendingData != nullptr))
                t.fail("%s: the decoders' fields differ", what.c_str());
            if (pool_g != pool_n) t.fail("%s: pool size guest %u native %u", what.c_str(), pool_g, pool_n);
            for (u32 k = 0; k < AskaOGG::kBuffers; k++)
                if (g.o->m_bufferSizes[k] != n.o->m_bufferSizes[k]) t.fail("%s: buffer %u: guest %u native %u bytes", what.c_str(), k, g.o->m_bufferSizes[k], n.o->m_bufferSizes[k]);
            if (n.o->m_bufferSizes[0] > 0x1000 && variant == 2) grown++;
            bytes += (long long)tn.pcm.size();
            pendings += tn.pendings;
            decodes += (long long)tn.results.size();
            fprintf(stderr, "    %s: %zu decodes (last %lld), %d pending, %zu PCM bytes, buffer 0 %u bytes, loop state %u\n", what.c_str(), tn.results.size(),
                    tn.results.empty() ? 0 : tn.results.back(), tn.pendings, tn.pcm.size(), n.o->m_bufferSizes[0], n.o->m_loopState);
            g.done(t);
            n.done(t);
        }
    }
    *pool = pool0;
    if (streams && (bytes < 1000000 || pendings < 50 || loop_pcmouts == 0 || grown == 0))
        t.fail("too few paths reached: %lld PCM bytes, %lld pending decodes of %lld, %lld Decode_Pcmout from Decode_LoopStart, %lld grown", bytes, pendings,
               decodes, loop_pcmouts, grown);
}
