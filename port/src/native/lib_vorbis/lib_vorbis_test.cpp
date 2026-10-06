// Differential tests of lib_vorbis: the same Ogg Vorbis streams decoded through the guest's libogg /
// libVorbis (t.call on the original code: --selftest installs no natives) and through the natives
// (lib_vorbis_api.h, called directly), the way Aska::AskaOGG drives them; every result, packet and
// stream parameter and every decoded sample (bit for bit) must agree.
#include <ogg/ogg.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

#include "native/common/test.h"
#include "native/common/test_assets.h"
#include "native/lib_vorbis/lib_vorbis_api.h"

namespace soa::native::lib_vorbis {
namespace {

// One decoder's structs, as in Aska::AskaOGG's decode context (calloc: guest-visible, like the game's).
struct Ctx {
    OggSyncState* oy;
    OggStreamState* os;
    OggPage* og;
    OggPacket* op;
    VorbisInfo* vi;
    VorbisComment* vc;
    VorbisDspState* vd;
    VorbisBlock* vb;
    float*** pcm;  // the out-parameter of vorbis_synthesis_pcmout
    u8* block;
    Ctx() {
        block = (u8*)calloc(1, 0x450);
        oy = (OggSyncState*)(block + 0x000);
        os = (OggStreamState*)(block + 0x020);
        og = (OggPage*)(block + 0x1b8);
        op = (OggPacket*)(block + 0x1d8);
        vi = (VorbisInfo*)(block + 0x208);
        vc = (VorbisComment*)(block + 0x240);
        vd = (VorbisDspState*)(block + 0x260);
        vb = (VorbisBlock*)(block + 0x2f0);
        pcm = (float***)(block + 0x3b0);
    }
    ~Ctx() { free(block); }
};

// What a decode produced: every call's result in order, and the decoded samples.
struct Trace {
    std::vector<long long> results;
    std::vector<float> samples;
    void r(long long v) { results.push_back(v); }
};

template <typename T>
u64 A(T* p) { return (u64)(uintptr_t)p; }

// The two implementations behind one interface.
struct Guest {
    TestContext& t;
    s64 c(const char* s, std::initializer_list<u64> a) { return (s64)t.call(s, a); }
    s32 ci(const char* s, std::initializer_list<u64> a) { return (s32)(u32)t.call(s, a); }
    s32 sync_init(Ctx& x) { return ci("ogg_sync_init", {A(x.oy)}); }
    char* sync_buffer(Ctx& x, s64 n) { return (char*)(uintptr_t)c("ogg_sync_buffer", {A(x.oy), (u64)n}); }
    s32 sync_wrote(Ctx& x, s64 n) { return ci("ogg_sync_wrote", {A(x.oy), (u64)n}); }
    s32 sync_pageout(Ctx& x) { return ci("ogg_sync_pageout", {A(x.oy), A(x.og)}); }
    s32 sync_reset(Ctx& x) { return ci("ogg_sync_reset", {A(x.oy)}); }
    s32 page_eos(Ctx& x) { return ci("ogg_page_eos", {A(x.og)}); }
    s32 page_serialno(Ctx& x) { return ci("ogg_page_serialno", {A(x.og)}); }
    s32 stream_init(Ctx& x, s32 s) { return ci("ogg_stream_init", {A(x.os), (u64)(u32)s}); }
    s32 stream_pagein(Ctx& x) { return ci("ogg_stream_pagein", {A(x.os), A(x.og)}); }
    s32 stream_packetout(Ctx& x, bool p = true) { return ci("ogg_stream_packetout", {A(x.os), p ? A(x.op) : 0}); }
    s32 stream_packetpeek(Ctx& x) { return ci("ogg_stream_packetpeek", {A(x.os), A(x.op)}); }
    s32 stream_reset(Ctx& x) { return ci("ogg_stream_reset", {A(x.os)}); }
    void info_init(Ctx& x) { c("vorbis_info_init", {A(x.vi)}); }
    void comment_init(Ctx& x) { c("vorbis_comment_init", {A(x.vc)}); }
    s32 headerin(Ctx& x) { return ci("vorbis_synthesis_headerin", {A(x.vi), A(x.vc), A(x.op)}); }
    s32 synthesis_init(Ctx& x) { return ci("vorbis_synthesis_init", {A(x.vd), A(x.vi)}); }
    s32 block_init(Ctx& x) { return ci("vorbis_block_init", {A(x.vd), A(x.vb)}); }
    s32 synthesis(Ctx& x) { return ci("vorbis_synthesis", {A(x.vb), A(x.op)}); }
    s32 trackonly(Ctx& x) { return ci("vorbis_synthesis_trackonly", {A(x.vb), A(x.op)}); }
    s32 blockin(Ctx& x) { return ci("vorbis_synthesis_blockin", {A(x.vd), A(x.vb)}); }
    s32 pcmout(Ctx& x, bool p = true) { return ci("vorbis_synthesis_pcmout", {A(x.vd), p ? A(x.pcm) : 0}); }
    s32 read(Ctx& x, s32 n) { return ci("vorbis_synthesis_read", {A(x.vd), (u64)(u32)n}); }
    s32 restart(Ctx& x) { return ci("vorbis_synthesis_restart", {A(x.vd)}); }
    s64 packet_blocksize(Ctx& x) { return c("vorbis_packet_blocksize", {A(x.vi), A(x.op)}); }
    s32 info_blocksize(Ctx& x, s32 zo) { return ci("vorbis_info_blocksize", {A(x.vi), (u64)(u32)zo}); }
    void clear(Ctx& x) {
        ci("vorbis_block_clear", {A(x.vb)});
        c("vorbis_dsp_clear", {A(x.vd)});
        c("vorbis_comment_clear", {A(x.vc)});
        c("vorbis_info_clear", {A(x.vi)});
        ci("ogg_stream_clear", {A(x.os)});
        ci("ogg_sync_clear", {A(x.oy)});
    }
};
struct Host {
    s32 sync_init(Ctx& x) { return lib_vorbis::sync_init(x.oy); }
    char* sync_buffer(Ctx& x, s64 n) { return lib_vorbis::sync_buffer(x.oy, n); }
    s32 sync_wrote(Ctx& x, s64 n) { return lib_vorbis::sync_wrote(x.oy, n); }
    s32 sync_pageout(Ctx& x) { return lib_vorbis::sync_pageout(x.oy, x.og); }
    s32 sync_reset(Ctx& x) { return lib_vorbis::sync_reset(x.oy); }
    s32 page_eos(Ctx& x) { return lib_vorbis::page_eos(x.og); }
    s32 page_serialno(Ctx& x) { return lib_vorbis::page_serialno(x.og); }
    s32 stream_init(Ctx& x, s32 s) { return lib_vorbis::stream_init(x.os, s); }
    s32 stream_pagein(Ctx& x) { return lib_vorbis::stream_pagein(x.os, x.og); }
    s32 stream_packetout(Ctx& x, bool p = true) { return lib_vorbis::stream_packetout(x.os, p ? x.op : nullptr); }
    s32 stream_packetpeek(Ctx& x) { return lib_vorbis::stream_packetpeek(x.os, x.op); }
    s32 stream_reset(Ctx& x) { return lib_vorbis::stream_reset(x.os); }
    void info_init(Ctx& x) { lib_vorbis::info_init(x.vi); }
    void comment_init(Ctx& x) { lib_vorbis::comment_init(x.vc); }
    s32 headerin(Ctx& x) { return synthesis_headerin(x.vi, x.vc, x.op); }
    s32 synthesis_init(Ctx& x) { return lib_vorbis::synthesis_init(x.vd, x.vi); }
    s32 block_init(Ctx& x) { return lib_vorbis::block_init(x.vd, x.vb); }
    s32 synthesis(Ctx& x) { return lib_vorbis::synthesis(x.vb, x.op); }
    s32 trackonly(Ctx& x) { return synthesis_trackonly(x.vb, x.op); }
    s32 blockin(Ctx& x) { return synthesis_blockin(x.vd, x.vb); }
    s32 pcmout(Ctx& x, bool p = true) { return synthesis_pcmout(x.vd, p ? x.pcm : nullptr); }
    s32 read(Ctx& x, s32 n) { return synthesis_read(x.vd, n); }
    s32 restart(Ctx& x) { return synthesis_restart(x.vd); }
    s64 packet_blocksize(Ctx& x) { return lib_vorbis::packet_blocksize(x.vi, x.op); }
    s32 info_blocksize(Ctx& x, s32 zo) { return lib_vorbis::info_blocksize(x.vi, zo); }
    void clear(Ctx& x) {
        block_clear(x.vb);
        dsp_clear(x.vd);
        comment_clear(x.vc);
        info_clear(x.vi);
        stream_clear(x.os);
        sync_clear(x.oy);
    }
};

// Feeds up to 0x2000 bytes at `pos` (as AskaOGG does); returns the bytes taken.
template <typename I>
size_t feed(I& api, Ctx& x, Trace& tr, const std::vector<u8>& d, size_t pos) {
    size_t n = d.size() - pos < 0x2000 ? d.size() - pos : 0x2000;
    if (!n) return 0;
    char* b = api.sync_buffer(x, 0x2000);
    tr.r(b != nullptr);
    if (!b) return 0;
    memcpy(b, d.data() + pos, n);
    tr.r(api.sync_wrote(x, (s64)n));
    return n;
}

void take_packet(Trace& tr, Ctx& x) {
    tr.r(x.op->bytes), tr.r(x.op->b_o_s), tr.r(x.op->e_o_s), tr.r(x.op->granulepos), tr.r(x.op->packetno);
    long long h = 0;
    for (s64 i = 0; i < x.op->bytes; i++) h = h * 131 + x.op->packet[i];
    tr.r(h);
}

// Decodes `d` the way Aska::AskaOGG does: the three headers, then page by page every packet (synthesis,
// blockin, pcmout, read). At `loop_at` pages it seeks back like Decode_LoopStart: stream / synthesis /
// sync reset, refeed from the start, skip packets with vorbis_packet_blocksize + trackonly up to a
// target sample, then decode on. `max_pages` bounds the run (guest decoding under the JIT is slow).
template <typename I>
Trace decode(I& api, const std::vector<u8>& d, int max_pages, int loop_at) {
    Trace tr;
    Ctx x;
    size_t pos = 0;
    tr.r(api.sync_init(x));
    int headers = 0;
    bool stream = false;
    for (int guard = 0; headers < 3 && guard < 4096; guard++) {
        s32 r = api.sync_pageout(x);
        tr.r(r);
        if (r == 0) {
            size_t n = feed(api, x, tr, d, pos);
            if (!n) break;
            pos += n;
            continue;
        }
        if (r < 0) continue;
        if (!stream) {
            s32 serial = api.page_serialno(x);
            tr.r(serial);
            tr.r(api.stream_init(x, serial));
            api.info_init(x);
            api.comment_init(x);
            stream = true;
        }
        tr.r(api.stream_pagein(x));
        for (;;) {
            s32 p = api.stream_packetout(x);
            tr.r(p);
            if (p != 1) break;
            take_packet(tr, x);
            tr.r(api.headerin(x));
            if (++headers == 3) break;
        }
    }
    if (headers < 3) return tr;
    int ch = x.vi->channels;
    // (the fields the game reads, which keep their offsets on every host: on Windows the host's
    // vorbis_info, in place, has its 32-bit longs elsewhere; the live check compares them all)
    tr.r(ch), tr.r((s32)x.vi->rate), tr.r(x.vi->version);
    tr.r(api.synthesis_init(x));
    tr.r(api.block_init(x));
    tr.r(api.info_blocksize(x, 0)), tr.r(api.info_blocksize(x, 1));
    auto out = [&]() {
        for (;;) {
            s32 n = api.pcmout(x);
            tr.r(n);
            if (n <= 0) break;
            for (int c = 0; c < ch; c++) tr.samples.insert(tr.samples.end(), (*x.pcm)[c], (*x.pcm)[c] + n);
            tr.r(api.read(x, n));
        }
    };
    int pages = 0;
    bool looped = false;
    for (int guard = 0; pages < max_pages && guard < 100000; guard++) {
        s32 r = api.sync_pageout(x);
        tr.r(r);
        if (r == 0) {
            size_t n = feed(api, x, tr, d, pos);
            if (!n) break;
            pos += n;
            continue;
        }
        if (r < 0) continue;
        pages++;
        tr.r(api.page_eos(x));
        tr.r(api.stream_pagein(x));
        for (;;) {
            s32 p = api.stream_packetout(x);
            tr.r(p);
            if (p == 0) break;
            if (p < 0) continue;
            take_packet(tr, x);
            s32 s = api.synthesis(x);
            tr.r(s);
            if (s == 0) tr.r(api.blockin(x));
            out();
        }
        if (pages == loop_at && !looped) {
            // Decode_LoopStart: back to the start, skip to a sample, decode on
            looped = true;
            s64 target = (s64)x.vi->rate / 4;
            tr.r(api.stream_reset(x));
            tr.r(api.restart(x));
            tr.r(api.sync_reset(x));
            pos = 0;
            s64 at = 0, prev = 0;
            bool done = false;
            for (int g2 = 0; !done && g2 < 4096;) {
                s32 r2 = api.sync_pageout(x);
                tr.r(r2);
                if (r2 == 0) {
                    size_t n = feed(api, x, tr, d, pos);
                    if (!n) break;
                    pos += n;
                    g2++;
                    continue;
                }
                if (r2 < 0) continue;
                tr.r(api.stream_pagein(x));
                for (;;) {
                    s32 p = api.stream_packetpeek(x);
                    tr.r(p);
                    if (p != 1) break;
                    if (x.op->packetno < 3) {  // the headers again
                        tr.r(api.stream_packetout(x, false));
                        continue;
                    }
                    s64 bs = api.packet_blocksize(x);
                    tr.r(bs);
                    if (bs < 0) {
                        tr.r(api.stream_packetout(x, false));
                        continue;
                    }
                    if (prev) at += (prev + bs) / 4;
                    if (at + (api.info_blocksize(x, 1) + bs) / 4 >= target) {
                        done = true;
                        break;
                    }
                    tr.r(api.stream_packetout(x, false));
                    take_packet(tr, x);
                    tr.r(api.trackonly(x));
                    tr.r(api.blockin(x));
                    if (x.op->granulepos != -1) at = x.op->granulepos;
                    prev = bs;
                    tr.r(api.pcmout(x, false));
                }
            }
            tr.r(at);
        }
    }
    api.clear(x);
    return tr;
}

// A BGM of the 3.7.0 download (`rel` relative to it, read in place: native/common/test_assets.h).
std::vector<u8> ogg_of(const std::string& rel) {
    std::vector<u8> d = test_assets::download_file(rel);
    // the BGM container (" CAA") holds plain Ogg pages: from the first one on
    for (size_t i = 0; i + 4 <= d.size(); i++)
        if (!memcmp(d.data() + i, "OggS", 4)) return std::vector<u8>(d.begin() + (long)i, d.end());
    return {};
}

void compare(TestContext& t, const Trace& g, const Trace& h, const char* what) {
    if (g.results.size() != h.results.size()) t.fail("%s: %zu calls on the guest, %zu native", what, g.results.size(), h.results.size());
    size_t n = g.results.size() < h.results.size() ? g.results.size() : h.results.size();
    for (size_t i = 0; i < n; i++)
        if (g.results[i] != h.results[i]) {
            t.fail("%s: step %zu: guest %lld, native %lld", what, i, g.results[i], h.results[i]);
            break;
        }
    if (g.samples.size() != h.samples.size()) t.fail("%s: %zu samples on the guest, %zu native", what, g.samples.size(), h.samples.size());
    else if (memcmp(g.samples.data(), h.samples.data(), g.samples.size() * sizeof(float))) {
        size_t i = 0;
        while (!memcmp(&g.samples[i], &h.samples[i], sizeof(float))) i++;
        t.fail("%s: sample %zu of %zu differs: guest %.9g, native %.9g", what, i, g.samples.size(), (double)g.samples[i], (double)h.samples[i]);
    }
    fprintf(stderr, "    %s: %zu calls, %zu samples\n", what, h.results.size(), h.samples.size());
}

// Rewrites each page's CRC after `mutate` changed its body (the host libogg's own checksum).
void fix_crcs(std::vector<u8>& d) {
    for (size_t i = 0; i + 27 <= d.size();) {
        if (memcmp(d.data() + i, "OggS", 4)) {
            i++;
            continue;
        }
        int segs = d[i + 26];
        if (i + 27 + (size_t)segs > d.size()) break;
        size_t body = 0;
        for (int s = 0; s < segs; s++) body += d[i + 27 + (size_t)s];
        size_t hl = 27 + (size_t)segs;
        if (i + hl + body > d.size()) break;
        ogg_page pg{d.data() + i, (long)hl, d.data() + i + hl, (long)body};
        ogg_page_checksum_set(&pg);
        i += hl + body;
    }
}

NATIVE_TEST("lib_vorbis/decode-bgm") {
    for (const char* f : {"Sound/BAS_SYSTEM_BGM_07.aac", "Sound/BAS_BATTLE_BGM_01.aac"}) {
        std::vector<u8> d = ogg_of(f);
        if (d.empty()) {
            fprintf(stderr, "    (%s missing: skipped)\n", f);
            continue;
        }
        Guest g{t};
        Host h;
        compare(t, decode(g, d, 60, 25), decode(h, d, 60, 25), f);
    }
}

NATIVE_TEST("lib_vorbis/decode-damaged") {
    // the decoder on damaged audio packets (valid pages: the CRCs rewritten), and on a cut stream
    std::vector<u8> d = ogg_of("Sound/BAS_SYSTEM_BGM_07.aac");
    if (d.empty()) return (void)fprintf(stderr, "    (BAS_SYSTEM_BGM_07.aac missing: skipped)\n");
    if (d.size() > 200000) d.resize(200000);
    std::vector<u8> bad = d;
    for (size_t i = 8000; i < bad.size(); i += 997) bad[i] ^= (u8)(1 + t.rand_int(0, 254));
    std::vector<u8> fixed = bad;
    fix_crcs(fixed);
    Guest g{t};
    Host h;
    compare(t, decode(g, bad, 40, 0), decode(h, bad, 40, 0), "flipped bytes (CRC errors)");
    compare(t, decode(g, fixed, 40, 0), decode(h, fixed, 40, 0), "flipped bytes (valid CRCs)");
    std::vector<u8> cut(d.begin(), d.begin() + 5000);
    compare(t, decode(g, cut, 40, 0), decode(h, cut, 40, 0), "cut after 5000 bytes");
}

TestContext* g_t = nullptr;
u64 guest_sym(const char* s) { return g_t->sym(s); }

NATIVE_TEST("lib_vorbis/live-check") {
    // --live-check lib_vorbis on the natives (the guest library in lockstep on shadows): no mismatch,
    // and the shadows' own calls reach the guest
    std::vector<u8> d = ogg_of("Sound/BAS_SYSTEM_BGM_07.aac");
    if (d.empty()) return (void)fprintf(stderr, "    (BAS_SYSTEM_BGM_07.aac missing: skipped)\n");
    g_t = &t;
    use_originals(guest_sym);
    live::Lockstep& ck = lockstep();
    u64 c0 = ck.checks(), b0 = ck.mismatches();
    ck.on = true;
    Host h;
    Trace a = decode(h, d, 30, 12);
    ck.on = false;
    use_originals(nullptr);
    Trace b = decode(h, d, 30, 12);
    compare(t, a, b, "checked vs unchecked");
    u64 n = ck.checks() - c0, bad = ck.mismatches() - b0;
    fprintf(stderr, "    %llu checks, %llu mismatches\n", (unsigned long long)n, (unsigned long long)bad);
    if (n < 1000) t.fail("only %llu checks", (unsigned long long)n);
    if (bad) t.fail("%llu mismatches", (unsigned long long)bad);
}

}  // namespace
}  // namespace soa::native::lib_vorbis
