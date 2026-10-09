// zlib's inflate on the host library (lib_zlib_api.h, README.md).
//
// Every guest z_stream (ZStream, LP64) gets a host twin, a host z_stream, made by inflateInit2_ and
// kept in the guest's `state` field (the library's private pointer, which the game never reads);
// around each call the public fields are copied across. So the host's own layout (Windows: 32-bit
// uLong) never meets the guest's.
//
// --live-check lib_zlib runs the guest's zlib 1.2.5 beside it (native/common/lockstep.h): a shadow
// guest z_stream per stream gets the same input, its output goes to a copy of the output buffer, and
// results, positions, totals, checksums and the written bytes are compared.
#include "native/lib_zlib/lib_zlib_api.h"

#include <zlib.h>

#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <mutex>
#include <unordered_map>

#include "core/cpu.h"
#include "native/common/native.h"

namespace soa::native::lib_zlib {

namespace {

struct Originals {
    u64 init2, inflate, end;
} orig;

live::Lockstep g_check("lib_zlib");

template <typename T>
u64 a(T* p) { return (u64)(uintptr_t)p; }
bool checking() { return g_check.active(); }
// A call the guest library makes on its own state during a shadow run: forwarded to the original.
bool forwarding() { return live::in_shadow_run(); }
void verdict(const char* fn, bool good, const char* fmt, ...) __attribute__((format(printf, 3, 4)));
void verdict(const char* fn, bool good, const char* fmt, ...) {
    if (!g_check.chosen(fn)) return;
    if (good) return g_check.ok(fn);
    char b[256];
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(b, sizeof b, fmt, ap);
    va_end(ap);
    g_check.bad(fn, "%s", b);
}
s32 gi(u64 r) { return (s32)(u32)r; }

// The live twins and their guest streams (a `state` that isn't the stream's own twin: a stream
// never initialized, or ended; the game's z_streams live on its stack, `state` uninitialized).
std::mutex g_m;
std::unordered_map<z_stream*, const ZStream*> g_twins;
z_stream* twin(const ZStream* s) {
    if (!s) return nullptr;
    auto* z = (z_stream*)s->state;
    std::lock_guard lk(g_m);
    auto it = g_twins.find(z);
    return it != g_twins.end() && it->second == s ? z : nullptr;
}
void to_host(const ZStream* g, z_stream* h) {
    h->next_in = const_cast<Bytef*>(g->next_in);
    h->avail_in = g->avail_in;
    h->total_in = (uLong)g->total_in;
    h->next_out = g->next_out;
    h->avail_out = g->avail_out;
    h->total_out = (uLong)g->total_out;
    h->data_type = g->data_type;
    h->adler = (uLong)g->adler;
}
void to_guest(const z_stream* h, ZStream* g) {
    g->next_in = h->next_in;
    g->avail_in = h->avail_in;
    g->total_in = h->total_in;
    g->next_out = h->next_out;
    g->avail_out = h->avail_out;
    g->total_out = h->total_out;
    g->msg = h->msg;
    g->data_type = h->data_type;
    g->adler = h->adler;
}

struct Scratch {
    u8* p = nullptr;
    size_t n = 0;
    u8* get(size_t want) {
        if (want > n) {
            free(p);
            p = (u8*)malloc(want ? want : 1);
            n = want;
        }
        return p;
    }
};
thread_local Scratch t_out;

}  // namespace

s32 inflate_init2(ZStream* strm, s32 window_bits, const char* version, s32 stream_size) {
    if (forwarding()) return gi(guest_call(orig.init2, {a(strm), (u64)(u32)window_bits, a(version), (u64)(u32)stream_size}));
    s32 r;
    // zlib 1.2.5's checks, on the guest's sizes (the host's z_stream differs on Windows)
    if (!version || version[0] != ZLIB_VERSION[0] || stream_size != (s32)sizeof(ZStream)) r = Z_VERSION_ERROR;
    else if (!strm) r = Z_STREAM_ERROR;
    else {
        if (z_stream* old = twin(strm)) {  // initialized again without inflateEnd: the old twin goes
            inflateEnd(old);
            std::lock_guard lk(g_m);
            g_twins.erase(old);
            delete old;
        }
        auto* h = new z_stream{};
        to_host(strm, h);
        // (the game's zalloc / zfree, always 0, aren't bridged: the twin's memory is the host's)
        r = inflateInit2(h, window_bits);
        strm->msg = h->msg;
        if (r == Z_OK) {
            // zlib 1.2.5's inflateReset sets adler to 1 for every stream; since 1.2.9 only a zlib /
            // gzip one gets it (raw deflate keeps the caller's value)
            h->adler = 1;
            to_guest(h, strm);
            std::lock_guard lk(g_m);
            g_twins[h] = strm;
            strm->state = h;
        } else {
            delete h;
            strm->state = nullptr;
        }
    }
    if (checking() && strm) {
        u64 s = g_check.shadow(a(strm), sizeof(ZStream));
        memset((void*)(uintptr_t)s, 0, sizeof(ZStream));
        s32 g = gi(live::shadow_call(orig.init2, {s, (u64)(u32)window_bits, a(version), (u64)(u32)stream_size}));
        verdict("inflateInit2_", g == r, "result %d, guest %d", r, g);
    }
    return r;
}

s32 inflate_(ZStream* strm, s32 flush) {
    if (forwarding()) return gi(guest_call(orig.inflate, {a(strm), (u64)(u32)flush}));
    ZStream before{};
    u8* copy = nullptr;
    u64 sh = 0;
    if (checking() && strm && (sh = g_check.find(a(strm)))) {
        before = *strm;
        copy = t_out.get((size_t)strm->avail_out + 1);
        if (strm->avail_out && strm->next_out) memcpy(copy, strm->next_out, strm->avail_out);
    }
    z_stream* h = twin(strm);
    s32 r;
    if (!h) r = Z_STREAM_ERROR;
    else {
        to_host(strm, h);
        r = inflate(h, flush);
        to_guest(h, strm);
    }
    if (sh) {
        auto* s = (ZStream*)(uintptr_t)sh;
        s->next_in = before.next_in, s->avail_in = before.avail_in;
        s->next_out = before.next_out ? copy : nullptr, s->avail_out = before.avail_out;
        s32 g = gi(live::shadow_call(orig.inflate, {sh, (u64)(u32)flush}));
        u64 wrote = before.avail_out - strm->avail_out;
        bool same = g == r && s->avail_in == strm->avail_in && s->avail_out == strm->avail_out && s->total_in == strm->total_in &&
                    s->total_out == strm->total_out && s->adler == strm->adler && (!wrote || !memcmp(copy, before.next_out, wrote)) &&
                    (!s->msg == !strm->msg) && (!s->msg || !strcmp(s->msg, strm->msg));
        verdict("inflate", same, "result %d/%d avail_in %u/%u avail_out %u/%u total_out %llu/%llu adler %#llx/%#llx msg %s/%s", r, g, strm->avail_in,
                s->avail_in, strm->avail_out, s->avail_out, (unsigned long long)strm->total_out, (unsigned long long)s->total_out,
                (unsigned long long)strm->adler, (unsigned long long)s->adler, strm->msg ? strm->msg : "-", s->msg ? s->msg : "-");
    }
    return r;
}

s32 inflate_end(ZStream* strm) {
    if (forwarding()) return gi(guest_call(orig.end, {a(strm)}));
    z_stream* h = twin(strm);
    s32 r;
    if (!h) r = Z_STREAM_ERROR;
    else {
        r = inflateEnd(h);
        {
            std::lock_guard lk(g_m);
            g_twins.erase(h);
        }
        delete h;
        strm->state = nullptr;
    }
    if (checking() && strm)
        if (u64 s = g_check.find(a(strm))) {
            s32 g = gi(live::shadow_call(orig.end, {s}));
            verdict("inflateEnd", g == r, "result %d, guest %d", r, g);
            g_check.drop(a(strm));
        }
    return r;
}

namespace {
const BoundNative kBound[] = {
    {"inflateInit2_", wrap<&inflate_init2>(), &orig.init2},
    {"inflate", wrap<&inflate_>(), &orig.inflate},
    {"inflateEnd", wrap<&inflate_end>(), &orig.end},
};
const bool g_registered = register_bound(kBound, "lib_zlib: host zlib (inflate)");
}  // namespace

live::Lockstep& lockstep() { return g_check; }
void use_originals(u64 (*sym)(const char*)) {
    bind_originals(kBound, sym);
}

}  // namespace soa::native::lib_zlib
