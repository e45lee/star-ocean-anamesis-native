// libogg + libVorbis on the host libraries, at the API the game calls (lib_vorbis_api.h, README.md).
//
// The host structs live in place, inside the guest's blocks (Aska::AskaOGG's decode context): the
// host's are never larger (static_asserts below), and of their fields the game reads only those whose
// offsets agree on every host (lib_vorbis_layout.h). ogg_packet is the exception (its granulepos
// moves on Windows, where `long` is 32-bit): it crosses as OggPacket, converted both ways.
//
// --live-check lib_vorbis runs the guest library beside it, in lockstep (native/common/lockstep.h):
// every guest struct gets a shadow in the guest library's layout, every call runs on both, and the
// results, packets, stream parameters and decoded samples (bit for bit) are compared.
#include "native/lib_vorbis/lib_vorbis_api.h"

#include <ogg/ogg.h>
#include <vorbis/codec.h>

#include <cstring>
#include <mutex>
#include <unordered_map>

#include "core/cpu.h"
#include "native/common/lockstep.h"
#include "native/common/native.h"

namespace soa::native::lib_vorbis {

static_assert(sizeof(ogg_sync_state) <= sizeof(OggSyncState));
static_assert(sizeof(ogg_stream_state) <= sizeof(OggStreamState));
static_assert(sizeof(ogg_page) <= sizeof(OggPage));
static_assert(offsetof(ogg_page, header) == offsetof(OggPage, header) && offsetof(ogg_page, body) == offsetof(OggPage, body));
static_assert(sizeof(vorbis_info) <= sizeof(VorbisInfo));
static_assert(offsetof(vorbis_info, channels) == offsetof(VorbisInfo, channels) && offsetof(vorbis_info, rate) == offsetof(VorbisInfo, rate));
static_assert(sizeof(vorbis_comment) <= sizeof(VorbisComment));
static_assert(sizeof(vorbis_dsp_state) <= sizeof(VorbisDspState));
static_assert(sizeof(vorbis_block) <= sizeof(VorbisBlock));

namespace {

// The guest originals (hook trampolines; 0 in --selftest, where nothing is installed).
struct Originals {
    u64 memory_hook, sync_init, sync_clear, sync_reset, sync_buffer, sync_wrote, sync_pageout, page_eos, page_serialno, stream_init, stream_clear,
        stream_reset, stream_pagein, stream_packetout, stream_packetpeek, info_init, info_clear, info_blocksize, comment_init, comment_clear,
        headerin, synthesis_init, dsp_clear, block_init, block_clear, synthesis, trackonly, blockin, pcmout, read, restart, packet_blocksize;
} orig;

live::Lockstep g_check("lib_vorbis");

template <typename T>
u64 a(T* p) { return (u64)(uintptr_t)p; }
ogg_sync_state* H(OggSyncState* p) { return reinterpret_cast<ogg_sync_state*>(p); }
ogg_stream_state* H(OggStreamState* p) { return reinterpret_cast<ogg_stream_state*>(p); }
ogg_page* H(OggPage* p) { return reinterpret_cast<ogg_page*>(p); }
vorbis_info* H(VorbisInfo* p) { return reinterpret_cast<vorbis_info*>(p); }
vorbis_comment* H(VorbisComment* p) { return reinterpret_cast<vorbis_comment*>(p); }
vorbis_dsp_state* H(VorbisDspState* p) { return reinterpret_cast<vorbis_dsp_state*>(p); }
vorbis_block* H(VorbisBlock* p) { return reinterpret_cast<vorbis_block*>(p); }

ogg_packet to_host(const OggPacket& g) {
    ogg_packet h{};
    h.packet = g.packet;
    h.bytes = (long)g.bytes;
    h.b_o_s = (long)g.b_o_s;
    h.e_o_s = (long)g.e_o_s;
    h.granulepos = g.granulepos;
    h.packetno = g.packetno;
    return h;
}
void to_guest(const ogg_packet& h, OggPacket* g) {
    g->packet = h.packet;
    g->bytes = h.bytes;
    g->b_o_s = h.b_o_s;
    g->e_o_s = h.e_o_s;
    g->granulepos = h.granulepos;
    g->packetno = h.packetno;
}

// ---- the lockstep check ----

bool checking() { return g_check.active(); }
// A call the guest library makes on its own state during a shadow run: forwarded to the original.
bool forwarding() { return live::in_shadow_run(); }
u64 sh(const void* p, size_t n) { return g_check.shadow(a(p), n); }
u64 fresh(const void* p, size_t n) {
    g_check.drop(a(p));
    return g_check.shadow(a(p), n);
}
void verdict(const char* fn, bool good, const char* what) {
    if (!g_check.chosen(fn)) return;
    if (good) g_check.ok(fn);
    else g_check.bad(fn, "%s", what);
}
void verdict_ret(const char* fn, s64 host, s64 guest) {
    if (host == guest) return verdict(fn, true, "");
    char b[96];
    snprintf(b, sizeof b, "result %lld, guest %lld", (long long)host, (long long)guest);
    verdict(fn, false, b);
}
s32 gi(u64 r) { return (s32)(u32)r; }

// ogg_sync_buffer's two buffers (host, shadow) until ogg_sync_wrote: the game fills the host's, the
// bytes are copied to the shadow's.
std::mutex g_buf_m;
std::unordered_map<u64, std::pair<char*, u64>> g_bufs;

// Guest-visible scratch for the shadow's float** (vorbis_synthesis_pcmout).
thread_local u64* t_pcm_slot = nullptr;

bool same_packet(const OggPacket& h, const OggPacket& g, char* why, size_t n) {
    if (h.bytes != g.bytes || h.b_o_s != g.b_o_s || h.e_o_s != g.e_o_s || h.granulepos != g.granulepos || h.packetno != g.packetno) {
        snprintf(why, n, "packet: bytes %lld/%lld bos %lld/%lld eos %lld/%lld granule %lld/%lld no %lld/%lld", (long long)h.bytes, (long long)g.bytes,
                 (long long)h.b_o_s, (long long)g.b_o_s, (long long)h.e_o_s, (long long)g.e_o_s, (long long)h.granulepos, (long long)g.granulepos,
                 (long long)h.packetno, (long long)g.packetno);
        return false;
    }
    if (h.bytes > 0 && memcmp(h.packet, g.packet, (size_t)h.bytes) != 0) {
        snprintf(why, n, "packet data differ (%lld bytes)", (long long)h.bytes);
        return false;
    }
    return true;
}

}  // namespace

// ---- libogg ----

void ogg_memory_hook_(u64 malloc_fn, u64 calloc_fn, u64 realloc_fn, u64 free_fn) {
    // Aska::AskaOGG::InitializeMemory hands the game's sound-memory allocators to the guest libogg.
    // The host libraries allocate with the host's malloc (the guest's own malloc too); the game never
    // frees what the library allocated, so nothing else has to know. Not forwarded: the guest library
    // runs only as a live check's shadow, which needn't take the game's sound memory.
    (void)malloc_fn, (void)calloc_fn, (void)realloc_fn, (void)free_fn;
}

s32 sync_init(OggSyncState* oy) {
    if (forwarding()) return gi(guest_call(orig.sync_init, {a(oy)}));
    s32 r = ogg_sync_init(H(oy));
    if (checking()) verdict_ret("ogg_sync_init", r, gi(live::shadow_call(orig.sync_init, {fresh(oy, sizeof(OggSyncState))})));
    return r;
}
s32 sync_clear(OggSyncState* oy) {
    if (forwarding()) return gi(guest_call(orig.sync_clear, {a(oy)}));
    s32 r = ogg_sync_clear(H(oy));
    if (checking()) {
        if (u64 s = g_check.find(a(oy))) verdict_ret("ogg_sync_clear", r, gi(live::shadow_call(orig.sync_clear, {s})));
        g_check.drop(a(oy));
        std::lock_guard lk(g_buf_m);
        g_bufs.erase(a(oy));
    }
    return r;
}
s32 sync_reset(OggSyncState* oy) {
    if (forwarding()) return gi(guest_call(orig.sync_reset, {a(oy)}));
    s32 r = ogg_sync_reset(H(oy));
    if (checking()) verdict_ret("ogg_sync_reset", r, gi(live::shadow_call(orig.sync_reset, {sh(oy, sizeof(OggSyncState))})));
    return r;
}
char* sync_buffer(OggSyncState* oy, s64 size) {
    if (forwarding()) return (char*)(uintptr_t)guest_call(orig.sync_buffer, {a(oy), (u64)size});
    char* r = ogg_sync_buffer(H(oy), (long)size);
    if (checking()) {
        u64 s = live::shadow_call(orig.sync_buffer, {sh(oy, sizeof(OggSyncState)), (u64)size});
        verdict("ogg_sync_buffer", (r != nullptr) == (s != 0), "one buffer is null");
        std::lock_guard lk(g_buf_m);
        g_bufs[a(oy)] = {r, s};
    }
    return r;
}
s32 sync_wrote(OggSyncState* oy, s64 bytes) {
    if (forwarding()) return gi(guest_call(orig.sync_wrote, {a(oy), (u64)bytes}));
    if (checking()) {
        // the bytes the game put in the host's buffer, into the shadow's (before the host's wrote)
        std::lock_guard lk(g_buf_m);
        auto it = g_bufs.find(a(oy));
        if (it != g_bufs.end() && it->second.first && it->second.second && bytes > 0)
            memcpy((void*)(uintptr_t)it->second.second, it->second.first, (size_t)bytes);
        if (it != g_bufs.end()) g_bufs.erase(it);
    }
    s32 r = ogg_sync_wrote(H(oy), (long)bytes);
    if (checking()) verdict_ret("ogg_sync_wrote", r, gi(live::shadow_call(orig.sync_wrote, {sh(oy, sizeof(OggSyncState)), (u64)bytes})));
    return r;
}
s32 sync_pageout(OggSyncState* oy, OggPage* og) {
    if (forwarding()) return gi(guest_call(orig.sync_pageout, {a(oy), a(og)}));
    s32 r = ogg_sync_pageout(H(oy), H(og));
    if (checking()) {
        u64 sog = og ? sh(og, sizeof(OggPage)) : 0;
        s32 g = gi(live::shadow_call(orig.sync_pageout, {sh(oy, sizeof(OggSyncState)), sog}));
        if (r != g || r != 1 || !og) verdict_ret("ogg_sync_pageout", r, g);
        else {
            ogg_page* hp = H(og);
            const OggPage* gp = (const OggPage*)(uintptr_t)sog;
            bool same = hp->header_len == gp->header_len && hp->body_len == gp->body_len && !memcmp(hp->header, gp->header, (size_t)hp->header_len) &&
                        !memcmp(hp->body, gp->body, (size_t)hp->body_len);
            verdict("ogg_sync_pageout", same, "the pages differ");
        }
    }
    return r;
}
s32 page_eos(const OggPage* og) {
    if (forwarding()) return gi(guest_call(orig.page_eos, {a(og)}));
    s32 r = ogg_page_eos(H(const_cast<OggPage*>(og)));
    if (checking())
        if (u64 s = g_check.find(a(og)); s && ((const OggPage*)(uintptr_t)s)->header) verdict_ret("ogg_page_eos", r, gi(live::shadow_call(orig.page_eos, {s})));
    return r;
}
s32 page_serialno(const OggPage* og) {
    if (forwarding()) return gi(guest_call(orig.page_serialno, {a(og)}));
    s32 r = ogg_page_serialno(H(const_cast<OggPage*>(og)));
    if (checking())
        if (u64 s = g_check.find(a(og)); s && ((const OggPage*)(uintptr_t)s)->header)
            verdict_ret("ogg_page_serialno", r, gi(live::shadow_call(orig.page_serialno, {s})));
    return r;
}
s32 stream_init(OggStreamState* os, s32 serialno) {
    if (forwarding()) return gi(guest_call(orig.stream_init, {a(os), (u64)(u32)serialno}));
    s32 r = ogg_stream_init(H(os), serialno);
    if (checking()) verdict_ret("ogg_stream_init", r, gi(live::shadow_call(orig.stream_init, {fresh(os, sizeof(OggStreamState)), (u64)(u32)serialno})));
    return r;
}
s32 stream_clear(OggStreamState* os) {
    if (forwarding()) return gi(guest_call(orig.stream_clear, {a(os)}));
    s32 r = ogg_stream_clear(H(os));
    if (checking()) {
        if (u64 s = g_check.find(a(os))) verdict_ret("ogg_stream_clear", r, gi(live::shadow_call(orig.stream_clear, {s})));
        g_check.drop(a(os));
    }
    return r;
}
s32 stream_reset(OggStreamState* os) {
    if (forwarding()) return gi(guest_call(orig.stream_reset, {a(os)}));
    s32 r = ogg_stream_reset(H(os));
    if (checking()) verdict_ret("ogg_stream_reset", r, gi(live::shadow_call(orig.stream_reset, {sh(os, sizeof(OggStreamState))})));
    return r;
}
s32 stream_pagein(OggStreamState* os, OggPage* og) {
    if (forwarding()) return gi(guest_call(orig.stream_pagein, {a(os), a(og)}));
    s32 r = ogg_stream_pagein(H(os), H(og));
    if (checking())
        if (u64 s = g_check.find(a(og)); s && ((const OggPage*)(uintptr_t)s)->header)
            verdict_ret("ogg_stream_pagein", r, gi(live::shadow_call(orig.stream_pagein, {sh(os, sizeof(OggStreamState)), s})));
    return r;
}
static s32 packet_step(const char* fn, u64 o, int (*host)(ogg_stream_state*, ogg_packet*), OggStreamState* os, OggPacket* op) {
    if (forwarding()) return gi(guest_call(o, {a(os), a(op)}));
    ogg_packet hp{};
    s32 r = host(H(os), op ? &hp : nullptr);
    if (op && r == 1) to_guest(hp, op);
    if (checking()) {
        u64 sop = op ? sh(op, sizeof(OggPacket)) : 0;
        s32 g = gi(live::shadow_call(o, {sh(os, sizeof(OggStreamState)), sop}));
        char why[256];
        if (r != g || r != 1 || !op) verdict_ret(fn, r, g);
        else verdict(fn, same_packet(*op, *(const OggPacket*)(uintptr_t)sop, why, sizeof why), why);
    }
    return r;
}
s32 stream_packetout(OggStreamState* os, OggPacket* op) { return packet_step("ogg_stream_packetout", orig.stream_packetout, ogg_stream_packetout, os, op); }
s32 stream_packetpeek(OggStreamState* os, OggPacket* op) { return packet_step("ogg_stream_packetpeek", orig.stream_packetpeek, ogg_stream_packetpeek, os, op); }

// ---- libVorbis ----

void info_init(VorbisInfo* vi) {
    if (forwarding()) return (void)guest_call(orig.info_init, {a(vi)});
    vorbis_info_init(H(vi));
    if (checking()) live::shadow_call(orig.info_init, {fresh(vi, sizeof(VorbisInfo))});
}
void info_clear(VorbisInfo* vi) {
    if (forwarding()) return (void)guest_call(orig.info_clear, {a(vi)});
    vorbis_info_clear(H(vi));
    if (checking()) {
        if (u64 s = g_check.find(a(vi))) live::shadow_call(orig.info_clear, {s});
        g_check.drop(a(vi));
    }
}
s32 info_blocksize(VorbisInfo* vi, s32 zo) {
    if (forwarding()) return gi(guest_call(orig.info_blocksize, {a(vi), (u64)(u32)zo}));
    s32 r = vorbis_info_blocksize(H(vi), zo);
    if (checking()) verdict_ret("vorbis_info_blocksize", r, gi(live::shadow_call(orig.info_blocksize, {sh(vi, sizeof(VorbisInfo)), (u64)(u32)zo})));
    return r;
}
void comment_init(VorbisComment* vc) {
    if (forwarding()) return (void)guest_call(orig.comment_init, {a(vc)});
    vorbis_comment_init(H(vc));
    if (checking()) live::shadow_call(orig.comment_init, {fresh(vc, sizeof(VorbisComment))});
}
void comment_clear(VorbisComment* vc) {
    if (forwarding()) return (void)guest_call(orig.comment_clear, {a(vc)});
    vorbis_comment_clear(H(vc));
    if (checking()) {
        if (u64 s = g_check.find(a(vc))) live::shadow_call(orig.comment_clear, {s});
        g_check.drop(a(vc));
    }
}
s32 synthesis_headerin(VorbisInfo* vi, VorbisComment* vc, OggPacket* op) {
    if (forwarding()) return gi(guest_call(orig.headerin, {a(vi), a(vc), a(op)}));
    ogg_packet hp = to_host(*op);
    s32 r = vorbis_synthesis_headerin(H(vi), H(vc), &hp);
    if (checking())
        if (u64 sop = g_check.find(a(op))) {
            u64 svi = sh(vi, sizeof(VorbisInfo));
            s32 g = gi(live::shadow_call(orig.headerin, {svi, sh(vc, sizeof(VorbisComment)), sop}));
            const vorbis_info* h = H(vi);
            const VorbisInfo* s = (const VorbisInfo*)(uintptr_t)svi;
            if (r != g) verdict_ret("vorbis_synthesis_headerin", r, g);
            else {
                char why[160];
                snprintf(why, sizeof why, "info: version %d/%d channels %d/%d rate %ld/%lld", h->version, s->version, h->channels, s->channels, h->rate,
                         (long long)s->rate);
                verdict("vorbis_synthesis_headerin",
                        h->version == s->version && h->channels == s->channels && h->rate == s->rate && h->bitrate_upper == s->bitrate_upper &&
                            h->bitrate_nominal == s->bitrate_nominal && h->bitrate_lower == s->bitrate_lower && h->bitrate_window == s->bitrate_window,
                        why);
            }
        }
    return r;
}
s32 synthesis_init(VorbisDspState* vd, VorbisInfo* vi) {
    if (forwarding()) return gi(guest_call(orig.synthesis_init, {a(vd), a(vi)}));
    s32 r = vorbis_synthesis_init(H(vd), H(vi));
    if (checking())
        verdict_ret("vorbis_synthesis_init", r, gi(live::shadow_call(orig.synthesis_init, {fresh(vd, sizeof(VorbisDspState)), sh(vi, sizeof(VorbisInfo))})));
    return r;
}
void dsp_clear(VorbisDspState* vd) {
    if (forwarding()) return (void)guest_call(orig.dsp_clear, {a(vd)});
    vorbis_dsp_clear(H(vd));
    if (checking()) {
        if (u64 s = g_check.find(a(vd))) live::shadow_call(orig.dsp_clear, {s});
        g_check.drop(a(vd));
    }
}
s32 block_init(VorbisDspState* vd, VorbisBlock* vb) {
    if (forwarding()) return gi(guest_call(orig.block_init, {a(vd), a(vb)}));
    s32 r = vorbis_block_init(H(vd), H(vb));
    if (checking())
        verdict_ret("vorbis_block_init", r, gi(live::shadow_call(orig.block_init, {sh(vd, sizeof(VorbisDspState)), fresh(vb, sizeof(VorbisBlock))})));
    return r;
}
s32 block_clear(VorbisBlock* vb) {
    if (forwarding()) return gi(guest_call(orig.block_clear, {a(vb)}));
    s32 r = vorbis_block_clear(H(vb));
    if (checking()) {
        if (u64 s = g_check.find(a(vb))) verdict_ret("vorbis_block_clear", r, gi(live::shadow_call(orig.block_clear, {s})));
        g_check.drop(a(vb));
    }
    return r;
}
static s32 block_step(const char* fn, u64 o, int (*host)(vorbis_block*, ogg_packet*), VorbisBlock* vb, OggPacket* op) {
    if (forwarding()) return gi(guest_call(o, {a(vb), a(op)}));
    ogg_packet hp = to_host(*op);
    s32 r = host(H(vb), &hp);
    if (checking())
        if (u64 sop = g_check.find(a(op))) verdict_ret(fn, r, gi(live::shadow_call(o, {sh(vb, sizeof(VorbisBlock)), sop})));
    return r;
}
s32 synthesis(VorbisBlock* vb, OggPacket* op) { return block_step("vorbis_synthesis", orig.synthesis, vorbis_synthesis, vb, op); }
s32 synthesis_trackonly(VorbisBlock* vb, OggPacket* op) {
    return block_step("vorbis_synthesis_trackonly", orig.trackonly, vorbis_synthesis_trackonly, vb, op);
}
s32 synthesis_blockin(VorbisDspState* vd, VorbisBlock* vb) {
    if (forwarding()) return gi(guest_call(orig.blockin, {a(vd), a(vb)}));
    s32 r = vorbis_synthesis_blockin(H(vd), H(vb));
    if (checking())
        verdict_ret("vorbis_synthesis_blockin", r, gi(live::shadow_call(orig.blockin, {sh(vd, sizeof(VorbisDspState)), sh(vb, sizeof(VorbisBlock))})));
    return r;
}
s32 synthesis_pcmout(VorbisDspState* vd, float*** pcm) {
    if (forwarding()) return gi(guest_call(orig.pcmout, {a(vd), a(pcm)}));
    s32 r = vorbis_synthesis_pcmout(H(vd), pcm);
    if (checking()) {
        if (!t_pcm_slot) t_pcm_slot = (u64*)calloc(1, 16);
        *t_pcm_slot = 0;
        s32 g = gi(live::shadow_call(orig.pcmout, {sh(vd, sizeof(VorbisDspState)), pcm ? a(t_pcm_slot) : 0}));
        if (r != g || r <= 0 || !pcm) verdict_ret("vorbis_synthesis_pcmout", r, g);
        else {
            // the decoded samples, bit for bit
            int ch = H(vd)->vi->channels;
            float** gp = (float**)(uintptr_t)*t_pcm_slot;
            int bad_ch = -1;
            for (int i = 0; i < ch && bad_ch < 0; i++)
                if (memcmp((*pcm)[i], gp[i], sizeof(float) * (size_t)r)) bad_ch = i;
            char why[96];
            snprintf(why, sizeof why, "%d samples differ in channel %d", r, bad_ch);
            verdict("vorbis_synthesis_pcmout", bad_ch < 0, why);
        }
    }
    return r;
}
s32 synthesis_read(VorbisDspState* vd, s32 samples) {
    if (forwarding()) return gi(guest_call(orig.read, {a(vd), (u64)(u32)samples}));
    s32 r = vorbis_synthesis_read(H(vd), samples);
    if (checking()) verdict_ret("vorbis_synthesis_read", r, gi(live::shadow_call(orig.read, {sh(vd, sizeof(VorbisDspState)), (u64)(u32)samples})));
    return r;
}
s32 synthesis_restart(VorbisDspState* vd) {
    if (forwarding()) return gi(guest_call(orig.restart, {a(vd)}));
    s32 r = vorbis_synthesis_restart(H(vd));
    if (checking()) verdict_ret("vorbis_synthesis_restart", r, gi(live::shadow_call(orig.restart, {sh(vd, sizeof(VorbisDspState))})));
    return r;
}
s64 packet_blocksize(VorbisInfo* vi, OggPacket* op) {
    if (forwarding()) return (s64)guest_call(orig.packet_blocksize, {a(vi), a(op)});
    ogg_packet hp = to_host(*op);
    s64 r = vorbis_packet_blocksize(H(vi), &hp);
    if (checking())
        if (u64 sop = g_check.find(a(op)))
            verdict_ret("vorbis_packet_blocksize", r, (s64)live::shadow_call(orig.packet_blocksize, {sh(vi, sizeof(VorbisInfo)), sop}));
    return r;
}

// ---- the natives ----

namespace {
const BoundNative kBound[] = {
    {"ogg_memory_hook", wrap<&ogg_memory_hook_>(), &orig.memory_hook},
    {"ogg_sync_init", wrap<&sync_init>(), &orig.sync_init},
    {"ogg_sync_clear", wrap<&sync_clear>(), &orig.sync_clear},
    {"ogg_sync_reset", wrap<&sync_reset>(), &orig.sync_reset},
    {"ogg_sync_buffer", wrap<&sync_buffer>(), &orig.sync_buffer},
    {"ogg_sync_wrote", wrap<&sync_wrote>(), &orig.sync_wrote},
    {"ogg_sync_pageout", wrap<&sync_pageout>(), &orig.sync_pageout},
    {"ogg_page_eos", wrap<&page_eos>(), &orig.page_eos},
    {"ogg_page_serialno", wrap<&page_serialno>(), &orig.page_serialno},
    {"ogg_stream_init", wrap<&stream_init>(), &orig.stream_init},
    {"ogg_stream_clear", wrap<&stream_clear>(), &orig.stream_clear},
    {"ogg_stream_reset", wrap<&stream_reset>(), &orig.stream_reset},
    {"ogg_stream_pagein", wrap<&stream_pagein>(), &orig.stream_pagein},
    {"ogg_stream_packetout", wrap<&stream_packetout>(), &orig.stream_packetout},
    {"ogg_stream_packetpeek", wrap<&stream_packetpeek>(), &orig.stream_packetpeek},
    {"vorbis_info_init", wrap<&info_init>(), &orig.info_init},
    {"vorbis_info_clear", wrap<&info_clear>(), &orig.info_clear},
    {"vorbis_info_blocksize", wrap<&info_blocksize>(), &orig.info_blocksize},
    {"vorbis_comment_init", wrap<&comment_init>(), &orig.comment_init},
    {"vorbis_comment_clear", wrap<&comment_clear>(), &orig.comment_clear},
    {"vorbis_synthesis_headerin", wrap<&synthesis_headerin>(), &orig.headerin},
    {"vorbis_synthesis_init", wrap<&synthesis_init>(), &orig.synthesis_init},
    {"vorbis_dsp_clear", wrap<&dsp_clear>(), &orig.dsp_clear},
    {"vorbis_block_init", wrap<&block_init>(), &orig.block_init},
    {"vorbis_block_clear", wrap<&block_clear>(), &orig.block_clear},
    {"vorbis_synthesis", wrap<&synthesis>(), &orig.synthesis},
    {"vorbis_synthesis_trackonly", wrap<&synthesis_trackonly>(), &orig.trackonly},
    {"vorbis_synthesis_blockin", wrap<&synthesis_blockin>(), &orig.blockin},
    {"vorbis_synthesis_pcmout", wrap<&synthesis_pcmout>(), &orig.pcmout},
    {"vorbis_synthesis_read", wrap<&synthesis_read>(), &orig.read},
    {"vorbis_synthesis_restart", wrap<&synthesis_restart>(), &orig.restart},
    {"vorbis_packet_blocksize", wrap<&packet_blocksize>(), &orig.packet_blocksize},
};
const bool g_registered = register_bound(kBound, "lib_vorbis: host libogg / libVorbis");
}  // namespace

live::Lockstep& lockstep() { return g_check; }
void use_originals(u64 (*sym)(const char*)) {
    bind_originals(kBound, sym);
}

}  // namespace soa::native::lib_vorbis
