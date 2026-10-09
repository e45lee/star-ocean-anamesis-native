// The lib_jpeg natives: Aska::JpegUtil's functions and glj_ilog, with the live check around them
// (lib_jpeg_api.h, README.md). The functions are stateless, so the check runs the guest original on
// the same input into scratch copies of the outputs and compares.
#include "native/lib_jpeg/lib_jpeg_api.h"

#include <cstddef>
#include <cstdio>
#include <cstring>
// clang-format off: jpeglib.h needs size_t and FILE first
#include <jpeglib.h>
// clang-format on

#include <cstdarg>
#include <cstdlib>

#include "soaruntime/core/cpu.h"
#include "native/common/native.h"

namespace soa::native::lib_jpeg {

namespace {

struct Originals {
    u64 get_info, decode, plane_info, quant_coef, yuv, ilog;
} orig;

live::Lockstep g_check("lib_jpeg");

template <typename T>
u64 a(T* p) { return (u64)(uintptr_t)p; }
bool checking() { return g_check.active(); }
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
void quiet_error(j_common_ptr cinfo) { *(int*)cinfo->client_data = 1; }

// A guest-visible copy of `n` bytes at p (or zeros when p is null), freed with free().
u8* copy_of(const void* p, u64 n) {
    u8* c = (u8*)malloc(n ? n : 1);
    if (p) memcpy(c, p, n);
    else memset(c, 0, n);
    return c;
}

}  // namespace

OutputSizes output_sizes(const void* data, u64 size) {
    OutputSizes o;
    int err = 0;
    jpeg_decompress_struct ci;
    jpeg_error_mgr jerr;
    ci.client_data = &err;
    ci.err = jpeg_std_error(&jerr);
    jerr.error_exit = quiet_error;
    jpeg_create_decompress(&ci);
    if (err) return o;
    jpeg_mem_src(&ci, (const unsigned char*)data, (unsigned long)size);
    if (!err && jpeg_read_header(&ci, TRUE) == JPEG_HEADER_OK && !err && ci.num_components > 0 && ci.num_components <= 4) {
        o.components = ci.num_components;
        o.image_width = ci.image_width, o.image_height = ci.image_height;
        s32 mh = 0, mv = 0;
        for (int i = 0; i < ci.num_components; i++) {
            if (ci.comp_info[i].h_samp_factor > mh) mh = ci.comp_info[i].h_samp_factor;
            if (ci.comp_info[i].v_samp_factor > mv) mv = ci.comp_info[i].v_samp_factor;
        }
        u32 lh = glj_ilog((u32)mh), lv = glj_ilog((u32)mv);
        u32 f = (u32)ci.max_h_samp_factor * 8, g = (u32)ci.max_v_samp_factor * 8;
        u32 cols8 = (f ? (ci.image_width + f - 1) / f : 0) * 8, rows = g ? (ci.image_height + g - 1) / g : 0;
        u64 at = 0, end = 0;
        for (int c = 0; c < ci.num_components; c++) {
            jpeg_component_info& comp = ci.comp_info[c];
            u32 h = (u32)comp.h_samp_factor, v = (u32)comp.v_samp_factor, sx = lh - glj_ilog(h);
            u64 bands = v ? (comp.height_in_blocks + v - 1) / v : 0;
            u64 written = at + bands * v * comp.width_in_blocks * sizeof(JBLOCK);
            if (written > end) end = written;
            u32 blocks_down = (u32)((s32)((1u << (sx & 31)) + v * rows - 1) >> (sx & 31));
            at += (u64)((s64)(s32)(blocks_down * ((cols8 * h) << ((sx + 3) & 31))) * 2);
            if (at > end) end = at;
            // DecodeYuv's plane: the rows the raw reads reach
            u32 sy = lv - glj_ilog(v), pitch = cols8 * h, step = (u32)ci.max_v_samp_factor * 8, last = 0;
            for (u32 s = 0; step && s < ci.image_height; s += step) last = (s >> (sy & 31)) + (16u >> (sy & 31));
            o.plane_bytes[c] = (u64)last * pitch;
        }
        o.coef_bytes = end;
    }
    jpeg_destroy_decompress(&ci);
    return o;
}

// ---- the natives, with the check ----

s32 checked_get_info(u32* width, u32* height, JpegUtil::ColorSpace* cs, bool* progressive, bool* arith, const void* data, u64 size) {
    s32 r = JpegUtil::GetInfo(width, height, cs, progressive, arith, data, size);
    if (checking()) {
        struct Out {
            u32 w, h;
            s32 cs;
            bool p, a;
        };
        auto* o = (Out*)copy_of(nullptr, sizeof(Out));
        s32 g = gi(live::shadow_call(orig.get_info, {a(&o->w), a(&o->h), a(&o->cs), a(&o->p), a(&o->a), a(data), size}));
        bool same = g == r && (r != 0 || ((!width || *width == o->w) && (!height || *height == o->h) && (!cs || *cs == o->cs) &&
                                          (!progressive || *progressive == o->p) && (!arith || *arith == o->a)));
        verdict("JpegUtil::GetInfo", same, "result %d, guest %d (or the header values differ)", r, g);
        free(o);
    }
    return r;
}

s32 checked_decode(u8* dst, u64 pitch, u32 width, u32 height, const void* data, u64 size, const JpegUtil::ILineScanner* gray,
                   const JpegUtil::ILineScanner* rgb, const JpegUtil::ILineScanner* cmyk, const JpegUtil::IAllocator* alloc) {
    u8* before = nullptr;
    u64 bytes = 0;
    if (checking() && dst) {
        OutputSizes s = output_sizes(data, size);
        u32 rows = height < s.image_height ? height : s.image_height;
        u64 last = (u64)width * 4 < pitch ? (u64)width * 4 : pitch;  // the last row: its pixels (at most 4 bytes each)
        bytes = rows ? pitch * (rows - 1) + last : 0;
        before = copy_of(dst, bytes);
    }
    s32 r = JpegUtil::Decode(dst, pitch, width, height, data, size, gray, rgb, cmyk, alloc);
    if (before) {
        // the guest's run into the copy of the destination as it was (the scanners only write rows)
        s32 g = gi(live::shadow_call(orig.decode, {a(before), pitch, width, height, a(data), size, a(gray), a(rgb), a(cmyk), a(alloc)}));
        bool same = g == r && !memcmp(before, dst, bytes);
        verdict("JpegUtil::Decode", same, "result %d, guest %d%s", r, g, memcmp(before, dst, bytes) ? ", the rows differ" : "");
        free(before);
    }
    return r;
}

s32 checked_plane_info(u32* widths, u32* heights, u32* shifted_rows, u32* shift_x, u32* shift_y, const void* data, u64 size) {
    s32 r = JpegUtil::GetPlaneInfo(widths, heights, shifted_rows, shift_x, shift_y, data, size);
    if (checking()) {
        int n = output_sizes(data, size).components;
        u32* o = (u32*)copy_of(nullptr, 5 * 4 * sizeof(u32));
        u32* outs[5] = {widths, heights, shifted_rows, shift_x, shift_y};
        u64 args[5];
        for (int k = 0; k < 5; k++) args[k] = outs[k] ? a(o + 4 * k) : 0;
        s32 g = gi(live::shadow_call(orig.plane_info, {args[0], args[1], args[2], args[3], args[4], a(data), size}));
        bool same = g == r;
        for (int k = 0; k < 5; k++)
            if (outs[k] && n) same = same && !memcmp(outs[k], o + 4 * k, (size_t)n * sizeof(u32));
        verdict("JpegUtil::GetPlaneInfo", same, "result %d, guest %d (or the plane values differ)", r, g);
        free(o);
    }
    return r;
}

s32 checked_quant_coef(float* quant, s16* coef, const void* data, u64 size) {
    OutputSizes s;
    float* gq = nullptr;
    u8* gc = nullptr;
    if (checking()) {
        s = output_sizes(data, size);
        if (quant) gq = (float*)copy_of(quant, 3 * 64 * sizeof(float));
        if (coef) gc = copy_of(coef, s.coef_bytes);
    }
    s32 r = JpegUtil::DecodeQuantCoef(quant, coef, data, size);
    if (checking()) {
        s32 g = gi(live::shadow_call(orig.quant_coef, {a(gq), a(gc), a(data), size}));
        bool q = !quant || !memcmp(gq, quant, (size_t)(s.components == 3 ? 3 : 1) * 64 * sizeof(float));
        bool c = !coef || !memcmp(gc, coef, s.coef_bytes);
        verdict("JpegUtil::DecodeQuantCoef", g == r && q && c, "result %d, guest %d%s%s", r, g, q ? "" : ", the tables differ", c ? "" : ", the coefficients differ");
        free(gq), free(gc);
    }
    return r;
}

s32 checked_yuv(u32** planes, const void* data, u64 size) {
    OutputSizes s;
    u8* copies[4] = {};
    u8** gp = nullptr;
    if (checking()) {
        s = output_sizes(data, size);
        if (planes) {
            gp = (u8**)copy_of(nullptr, 4 * sizeof(u8*));
            for (int i = 0; i < s.components && i < 3; i++) gp[i] = copies[i] = copy_of(planes[i], s.plane_bytes[i]);
        }
    }
    s32 r = JpegUtil::DecodeYuv(planes, data, size);
    if (checking()) {
        s32 g = gi(live::shadow_call(orig.yuv, {a(gp), a(data), size}));
        bool same = g == r;
        for (int i = 0; planes && i < s.components && i < 3; i++) same = same && !memcmp(copies[i], planes[i], s.plane_bytes[i]);
        verdict("JpegUtil::DecodeYuv", same, "result %d, guest %d (or the planes differ)", r, g);
        for (u8* c : copies) free(c);
        free(gp);
    }
    return r;
}

namespace {
struct Bound {
    const char* sym;
    HostFn fn;
    u64* orig;
};
const Bound kBound[] = {
    {"_ZN4Aska8JpegUtil7GetInfoEPjS1_PNS0_10ColorSpaceEPbS4_PKvm", wrap<&checked_get_info>(), &orig.get_info},
    {"_ZN4Aska8JpegUtil6DecodeEPvmjjPKvmRKNS0_12ILineScannerES6_S6_RKNS0_10IAllocatorE", wrap<&checked_decode>(), &orig.decode},
    {"_ZN4Aska8JpegUtil12GetPlaneInfoEPjS1_S1_S1_S1_PKvm", wrap<&checked_plane_info>(), &orig.plane_info},
    {"_ZN4Aska8JpegUtil15DecodeQuantCoefEPfPsPKvm", wrap<&checked_quant_coef>(), &orig.quant_coef},
    {"_ZN4Aska8JpegUtil9DecodeYuvEPPjPKvm", wrap<&checked_yuv>(), &orig.yuv},
    {"_Z8glj_ilogj", wrap<&glj_ilog>(), &orig.ilog},
};
bool register_all() {
    for (const Bound& b : kBound) register_native_function({b.sym, b.fn, "lib_jpeg: Aska::JpegUtil on host IJG libjpeg 9b", nullptr, b.orig});
    return true;
}
const bool g_registered = register_all();
}  // namespace

live::Lockstep& lockstep() { return g_check; }
void use_originals(u64 (*sym)(const char*)) {
    for (const Bound& b : kBound) *b.orig = sym ? sym(b.sym) : 0;
}

}  // namespace soa::native::lib_jpeg
