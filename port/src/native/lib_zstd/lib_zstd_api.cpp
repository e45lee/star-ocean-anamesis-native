// zstd on the host library, at the decompression API the game calls (lib_zstd_api.h, README.md).
//
// The decompression streams are host objects (opaque to the game); the buffers are plain structs.
// --live-check lib_zstd runs the guest library beside it (native/common/lockstep.h): every host
// stream has a guest one, every call runs on both (the guest's into scratch copies of the output),
// and results, consumed / produced positions and the decoded bytes are compared.
#include "native/lib_zstd/lib_zstd_api.h"

#include <zstd.h>

#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

#include "soaruntime/core/cpu.h"
#include "native/common/native.h"

namespace soa::native::lib_zstd {

static_assert(sizeof(ZSTD_inBuffer) == sizeof(ZSTDInBuffer) && offsetof(ZSTD_inBuffer, pos) == offsetof(ZSTDInBuffer, pos));
static_assert(sizeof(ZSTD_outBuffer) == sizeof(ZSTDOutBuffer) && offsetof(ZSTD_outBuffer, pos) == offsetof(ZSTDOutBuffer, pos));

namespace {

struct Originals {
    u64 create, free_, init, stream, decompress, is_error, in_size, out_size;
} orig;

live::Lockstep g_check("lib_zstd");

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
// Guest-visible scratch (host malloc is the guest's malloc).
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
thread_local Scratch t_out, t_bufs;

}  // namespace

void* create_dstream() {
    if (forwarding()) return (void*)(uintptr_t)guest_call(orig.create, {});
    ZSTD_DStream* r = ZSTD_createDStream();
    if (checking() && r) {
        u64 g = live::shadow_call(orig.create, {});
        verdict("ZSTD_createDStream", g != 0, "the guest's is null");
        if (g) g_check.adopt(a(r), g);
    }
    return r;
}
u64 free_dstream(void* zds) {
    if (forwarding()) return guest_call(orig.free_, {a(zds)});
    u64 r = ZSTD_freeDStream((ZSTD_DStream*)zds);
    if (checking())
        if (u64 g = g_check.release(a(zds))) {
            u64 gr = live::shadow_call(orig.free_, {g});
            verdict("ZSTD_freeDStream", gr == r, "result %#llx, guest %#llx", (unsigned long long)r, (unsigned long long)gr);
        }
    return r;
}
u64 init_dstream(void* zds) {
    if (forwarding()) return guest_call(orig.init, {a(zds)});
    u64 r = ZSTD_initDStream((ZSTD_DStream*)zds);
    if (checking())
        if (u64 g = g_check.find(a(zds))) {
            u64 gr = live::shadow_call(orig.init, {g});
            verdict("ZSTD_initDStream", gr == r, "result %#llx, guest %#llx", (unsigned long long)r, (unsigned long long)gr);
        }
    return r;
}
u64 decompress_stream(void* zds, ZSTDOutBuffer* out, ZSTDInBuffer* in) {
    if (forwarding()) return guest_call(orig.stream, {a(zds), a(out), a(in)});
    u64 g = checking() ? g_check.find(a(zds)) : 0;
    ZSTDOutBuffer gout{};
    ZSTDInBuffer gin{};
    u8 *gdst = nullptr, *before = nullptr;
    if (g) {
        // the guest's run: the same input, the output into a copy of the buffer as it is now
        gout = *out, gin = *in;
        gdst = t_out.get(out->size + 1);
        if (out->size) memcpy(gdst, out->dst, out->size);
        gout.dst = gdst;
        before = gdst;
    }
    u64 r = ZSTD_decompressStream((ZSTD_DStream*)zds, (ZSTD_outBuffer*)out, (ZSTD_inBuffer*)in);
    if (g) {
        u8* io = t_bufs.get(2 * sizeof(ZSTDOutBuffer));
        auto* po = (ZSTDOutBuffer*)io;
        auto* pi = (ZSTDInBuffer*)(io + sizeof(ZSTDOutBuffer));
        *po = gout, *pi = gin;
        u64 gr = live::shadow_call(orig.stream, {g, a(po), a(pi)});
        bool same = gr == r && po->pos == out->pos && pi->pos == in->pos && (!out->size || !memcmp(before, out->dst, out->size));
        verdict("ZSTD_decompressStream", same, "result %#llx/%#llx out.pos %llu/%llu in.pos %llu/%llu%s", (unsigned long long)r,
                (unsigned long long)gr, (unsigned long long)out->pos, (unsigned long long)po->pos, (unsigned long long)in->pos,
                (unsigned long long)pi->pos, out->size && memcmp(before, out->dst, out->size) ? ", the bytes differ" : "");
    }
    return r;
}
u64 decompress(void* dst, u64 capacity, const void* src, u64 size) {
    if (forwarding()) return guest_call(orig.decompress, {a(dst), capacity, a(src), size});
    u8* gdst = nullptr;
    if (checking() && capacity < (1u << 26)) {
        gdst = t_out.get(capacity + 1);
        if (capacity) memcpy(gdst, dst, capacity);
    }
    u64 r = ZSTD_decompress(dst, capacity, src, size);
    if (gdst) {
        u64 gr = live::shadow_call(orig.decompress, {a(gdst), capacity, a(src), size});
        bool bytes = !capacity || !memcmp(gdst, dst, capacity);
        verdict("ZSTD_decompress", gr == r && bytes, "result %#llx, guest %#llx%s", (unsigned long long)r, (unsigned long long)gr,
                bytes ? "" : ", the bytes differ");
    }
    return r;
}
u32 is_error(u64 code) { return ZSTD_isError(code); }
u64 dstream_in_size() { return ZSTD_DStreamInSize(); }
u64 dstream_out_size() { return ZSTD_DStreamOutSize(); }

namespace {
struct Bound {
    const char* sym;
    HostFn fn;
    u64* orig;
};
const Bound kBound[] = {
    {"ZSTD_createDStream", wrap<&create_dstream>(), &orig.create},
    {"ZSTD_freeDStream", wrap<&free_dstream>(), &orig.free_},
    {"ZSTD_initDStream", wrap<&init_dstream>(), &orig.init},
    {"ZSTD_decompressStream", wrap<&decompress_stream>(), &orig.stream},
    {"ZSTD_decompress", wrap<&decompress>(), &orig.decompress},
    {"ZSTD_isError", wrap<&is_error>(), &orig.is_error},
    {"ZSTD_DStreamInSize", wrap<&dstream_in_size>(), &orig.in_size},
    {"ZSTD_DStreamOutSize", wrap<&dstream_out_size>(), &orig.out_size},
};
bool register_all() {
    for (const Bound& b : kBound) register_native_function({b.sym, b.fn, "lib_zstd: host zstd", nullptr, b.orig});
    return true;
}
const bool g_registered = register_all();
}  // namespace

live::Lockstep& lockstep() { return g_check; }
void use_originals(u64 (*sym)(const char*)) {
    for (const Bound& b : kBound) *b.orig = sym ? sym(b.sym) : 0;
}

}  // namespace soa::native::lib_zstd
