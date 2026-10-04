// Differential tests of lib_jpeg: Aska::JpegUtil's functions on the same JPEGs through the guest (its
// libjpeg 9b; t.call on the original code) and natively (the host's libjpeg 9b): results, header
// values, decoded rows (through the game's own line scanners and allocator), planes, coefficients and
// tables, byte for byte. The JPEGs: the download's JPEG textures and host-encoded ones of every kind the
// decoder distinguishes (grayscale, YCbCr 4:4:4 / 4:2:2 / 4:2:0, CMYK, progressive, arithmetic, restarts).
#include <cstddef>
#include <cstdio>
#include <cstring>
// clang-format off: jpeglib.h needs size_t and FILE first
#include <jpeglib.h>
// clang-format on

#include <cstdlib>
#include <string>
#include <vector>

#include "native/common/test.h"
#include "native/common/test_assets.h"
#include "native/lib_jpeg/lib_jpeg_api.h"

namespace soa::native::lib_jpeg {
namespace {

template <typename T>
u64 A(T* p) { return (u64)(uintptr_t)p; }

struct Jpeg {
    std::string name;
    std::vector<u8> data;
    // Progressive JPEGs: under the JIT the guest's libjpeg ends with zero coefficients for them (the
    // host's decodes them); the game has none (all 431 JPEG textures of the 3.7.0 download are baseline,
    // SOF0), so only their headers are compared.
    bool headers_only = false;
};

// The download's JPEG textures (JPEG data inside AIF containers, stored uncompressed).
std::vector<Jpeg> download_jpegs(size_t n) {
    std::vector<Jpeg> out;
    for (auto& rel : test_assets::download_files("Image/etc2", ".aif", 3000)) {
        if (rel.find("bg") == std::string::npos && rel.find("_bm") == std::string::npos) continue;
        std::vector<u8> p = test_assets::download_payload(rel);
        for (size_t i = 0; i + 3 < p.size(); i++)
            if (p[i] == 0xff && p[i + 1] == 0xd8 && p[i + 2] == 0xff) {
                out.push_back({rel, std::vector<u8>(p.begin() + (long)i, p.end())});
                break;
            }
        if (out.size() >= n) break;
    }
    return out;
}

// A host-encoded JPEG (libjpeg 9b's compressor) of a w x h test image.
std::vector<u8> encode(TestContext& t, int w, int h, J_COLOR_SPACE in, int comps, int hs, int vs, bool progressive, bool arith, int restart) {
    jpeg_compress_struct c;
    jpeg_error_mgr e;
    c.err = jpeg_std_error(&e);
    jpeg_create_compress(&c);
    unsigned char* buf = nullptr;
    unsigned long len = 0;
    jpeg_mem_dest(&c, &buf, &len);
    c.image_width = (JDIMENSION)w, c.image_height = (JDIMENSION)h, c.input_components = comps, c.in_color_space = in;
    jpeg_set_defaults(&c);
    jpeg_set_quality(&c, 70 + t.rand_int(0, 25), TRUE);
    if (comps == 3) c.comp_info[0].h_samp_factor = hs, c.comp_info[0].v_samp_factor = vs;
    if (progressive) jpeg_simple_progression(&c);
    c.arith_code = arith ? TRUE : FALSE;
    c.restart_interval = (unsigned)restart;
    jpeg_start_compress(&c, TRUE);
    std::vector<u8> row((size_t)w * comps);
    while (c.next_scanline < c.image_height) {
        for (int x = 0; x < w * comps; x++) row[(size_t)x] = (u8)((x * 7 + (int)c.next_scanline * 3) ^ (x / 13) ^ t.rand_int(0, 15));
        JSAMPROW r = row.data();
        jpeg_write_scanlines(&c, &r, 1);
    }
    jpeg_finish_compress(&c);
    std::vector<u8> out(buf, buf + len);
    free(buf);
    jpeg_destroy_compress(&c);
    return out;
}

std::vector<Jpeg> synthetic(TestContext& t) {
    std::vector<Jpeg> v;
    v.push_back({"gray 37x29", encode(t, 37, 29, JCS_GRAYSCALE, 1, 1, 1, false, false, 0)});
    v.push_back({"rgb 4:4:4 64x48", encode(t, 64, 48, JCS_RGB, 3, 1, 1, false, false, 0)});
    v.push_back({"rgb 4:2:2 50x30", encode(t, 50, 30, JCS_RGB, 3, 2, 1, false, false, 0)});
    v.push_back({"rgb 4:2:0 129x67", encode(t, 129, 67, JCS_RGB, 3, 2, 2, false, false, 0)});
    v.push_back({"rgb 4:2:0 progressive 100x100", encode(t, 100, 100, JCS_RGB, 3, 2, 2, true, false, 0), true});
    v.push_back({"rgb 4:2:0 arithmetic 77x41", encode(t, 77, 41, JCS_RGB, 3, 2, 2, false, true, 0)});
    v.push_back({"rgb 4:2:0 restarts 90x70", encode(t, 90, 70, JCS_RGB, 3, 2, 2, false, false, 3)});
    v.push_back({"cmyk 33x21", encode(t, 33, 21, JCS_CMYK, 4, 1, 1, false, false, 0)});
    return v;
}

void check_one(TestContext& t, const Jpeg& j) {
    const char* nm = j.name.c_str();
    u8* d = (u8*)malloc(j.data.size() + 16);
    memcpy(d, j.data.data(), j.data.size());
    u64 n = j.data.size();
    OutputSizes s = output_sizes(d, n);
    // GetInfo
    struct Info {
        u32 w, h;
        s32 cs;
        bool p, a;
    };
    auto* gi = (Info*)calloc(1, sizeof(Info));
    auto* hi = (Info*)calloc(1, sizeof(Info));
    s32 g = (s32)(u32)t.call("_ZN4Aska8JpegUtil7GetInfoEPjS1_PNS0_10ColorSpaceEPbS4_PKvm", {A(&gi->w), A(&gi->h), A(&gi->cs), A(&gi->p), A(&gi->a), A(d), n});
    s32 h = JpegUtil::GetInfo(&hi->w, &hi->h, &hi->cs, &hi->p, &hi->a, d, n);
    if (g != h || memcmp(gi, hi, sizeof(Info))) t.fail("%s: GetInfo: guest %d (%u x %u cs %d), native %d (%u x %u cs %d)", nm, g, gi->w, gi->h, gi->cs, h, hi->w, hi->h, hi->cs);
    if (!s.components || j.headers_only) {
        if (j.headers_only) fprintf(stderr, "    (%s: the headers only)\n", nm);
        free(gi), free(hi), free(d);
        return;
    }
    // GetPlaneInfo: all outputs, then some left out
    for (int mask : {31, 30, 7, 24}) {
        u32* go = (u32*)calloc(20, sizeof(u32));
        u32* ho = (u32*)calloc(20, sizeof(u32));
        u64 ga[5], ha[5];
        for (int k = 0; k < 5; k++) ga[k] = mask >> k & 1 ? A(go + 4 * k) : 0, ha[k] = mask >> k & 1 ? A(ho + 4 * k) : 0;
        g = (s32)(u32)t.call("_ZN4Aska8JpegUtil12GetPlaneInfoEPjS1_S1_S1_S1_PKvm", {ga[0], ga[1], ga[2], ga[3], ga[4], A(d), n});
        h = JpegUtil::GetPlaneInfo((u32*)ha[0], (u32*)ha[1], (u32*)ha[2], (u32*)ha[3], (u32*)ha[4], d, n);
        if (g != h || memcmp(go, ho, 20 * sizeof(u32))) t.fail("%s: GetPlaneInfo (outputs %#x): guest %d, native %d, or the values differ", nm, mask, g, h);
        free(go), free(ho);
    }
    // DecodeQuantCoef: both, the tables only, the coefficients only
    for (int mask : {3, 1, 2}) {
        float *gq = (float*)calloc(192, 4), *hq = (float*)calloc(192, 4);
        u8 *gc = (u8*)calloc(1, s.coef_bytes + 64), *hc = (u8*)calloc(1, s.coef_bytes + 64);
        g = (s32)(u32)t.call("_ZN4Aska8JpegUtil15DecodeQuantCoefEPfPsPKvm", {mask & 1 ? A(gq) : 0, mask & 2 ? A(gc) : 0, A(d), n});
        h = JpegUtil::DecodeQuantCoef(mask & 1 ? hq : nullptr, mask & 2 ? (s16*)hc : nullptr, d, n);
        if (g != h) t.fail("%s: DecodeQuantCoef (%d): guest %d, native %d", nm, mask, g, h);
        if (memcmp(gq, hq, 192 * 4)) t.fail("%s: DecodeQuantCoef (%d): the tables differ", nm, mask);
        if (memcmp(gc, hc, s.coef_bytes + 64)) {
            size_t i = 0, bad = 0;
            while (gc[i] == hc[i]) i++;
            for (size_t k = 0; k < s.coef_bytes / 2; k++) bad += ((s16*)gc)[k] != ((s16*)hc)[k];
            t.fail("%s: DecodeQuantCoef (%d): the coefficients differ: first at coefficient %zu (block %zu, k %zu): guest %d, native %d; %zu of %llu differ", nm,
                   mask, i / 2, i / 128, i / 2 % 64, ((s16*)gc)[i / 2], ((s16*)hc)[i / 2], bad, (unsigned long long)s.coef_bytes / 2);
        }
        free(gq), free(hq), free(gc), free(hc);
    }
    // DecodeYuv
    {
        u8** gp = (u8**)calloc(4, sizeof(u8*));
        u8** hp = (u8**)calloc(4, sizeof(u8*));
        for (int i = 0; i < 4; i++) gp[i] = (u8*)calloc(1, s.plane_bytes[i] + 64), hp[i] = (u8*)calloc(1, s.plane_bytes[i] + 64);
        g = (s32)(u32)t.call("_ZN4Aska8JpegUtil9DecodeYuvEPPjPKvm", {A(gp), A(d), n});
        h = JpegUtil::DecodeYuv((u32**)hp, d, n);
        if (g != h) t.fail("%s: DecodeYuv: guest %d, native %d", nm, g, h);
        for (int i = 0; i < 4; i++)
            if (memcmp(gp[i], hp[i], s.plane_bytes[i] + 64)) t.fail("%s: DecodeYuv: plane %d differs", nm, i);
        for (int i = 0; i < 4; i++) free(gp[i]), free(hp[i]);
        free(gp), free(hp);
        g = (s32)(u32)t.call("_ZN4Aska8JpegUtil9DecodeYuvEPPjPKvm", {0, A(d), n});
        t.expect_eq(g, JpegUtil::DecodeYuv(nullptr, d, n), "DecodeYuv(null)");
    }
    // Decode, through the game's scanners and allocator (whole, and clipped)
    auto obj = [&](const char* vt) {
        u64* o = (u64*)calloc(1, 16);
        *o = t.sym(vt) + 0x10;
        return o;
    };
    u64* gray = obj("_ZTVN4Aska8JpegUtil21FnGrayscaleLineReaderE");
    u64* rgb = obj("_ZTVN4Aska8JpegUtil16FnRGBXLineReaderE");
    u64* cmyk = obj("_ZTVN4Aska8JpegUtil16FnCMYKLineReaderE");
    u64* alloc = obj("_ZTVN4Aska8JpegUtil21FnASKAEngineAllocatorE");
    for (int clip : {0, 1}) {
        u32 w = clip ? s.image_width / 2 + 1 : s.image_width + 3, hh = clip ? s.image_height / 2 + 1 : s.image_height + 2;
        u64 pitch = (u64)(s.image_width + 5) * 4;
        size_t bytes = pitch * (s.image_height + 3);
        u8 *gd = (u8*)malloc(bytes), *hd = (u8*)malloc(bytes);
        memset(gd, 0xcd, bytes), memset(hd, 0xcd, bytes);
        g = (s32)(u32)t.call("_ZN4Aska8JpegUtil6DecodeEPvmjjPKvmRKNS0_12ILineScannerES6_S6_RKNS0_10IAllocatorE",
                             GuestArgs().p(gd).i(pitch).i(w).i(hh).p(d).i(n).p(gray).p(rgb).i(A(cmyk)).i(A(alloc)))
                .x0;
        h = JpegUtil::Decode(hd, pitch, w, hh, d, n, (const JpegUtil::ILineScanner*)gray, (const JpegUtil::ILineScanner*)rgb,
                             (const JpegUtil::ILineScanner*)cmyk, (const JpegUtil::IAllocator*)alloc);
        if (g != h) t.fail("%s: Decode (clip %d): guest %d, native %d", nm, clip, g, h);
        if (memcmp(gd, hd, bytes)) t.fail("%s: Decode (clip %d): the rows differ", nm, clip);
        free(gd), free(hd);
    }
    free(gray), free(rgb), free(cmyk), free(alloc), free(gi), free(hi), free(d);
}

NATIVE_TEST("lib_jpeg/download") {
    auto js = download_jpegs(8);
    if (js.empty()) return (void)fprintf(stderr, "    (no download: skipped)\n");
    for (auto& j : js) check_one(t, j);
    fprintf(stderr, "    %zu JPEGs\n", js.size());
}

NATIVE_TEST("lib_jpeg/synthetic") {
    for (auto& j : synthetic(t)) check_one(t, j);
    // not JPEG / damaged headers: GetInfo and Decode's checks (the others exit on a bad header, as the guest's do)
    std::vector<Jpeg> bad = {{"empty", {}}, {"one byte", {0xff}}, {"no SOI", {0x00, 0xd8, 0xff, 0xe0}}, {"SOI only", {0xff, 0xd8}}};
    std::vector<u8> cut = synthetic(t)[3].data;
    cut.resize(cut.size() / 3);
    bad.push_back({"cut", cut});
    for (auto& j : bad) {
        u8* d = (u8*)calloc(1, j.data.size() + 16);
        if (!j.data.empty()) memcpy(d, j.data.data(), j.data.size());
        u32* o = (u32*)calloc(8, 4);
        s32 g = (s32)(u32)t.call("_ZN4Aska8JpegUtil7GetInfoEPjS1_PNS0_10ColorSpaceEPbS4_PKvm", {A(o), A(o + 1), A(o + 2), A(o + 3), A(o + 4), A(d), j.data.size()});
        u32* p = (u32*)calloc(8, 4);
        s32 h = JpegUtil::GetInfo(p, p + 1, (s32*)(p + 2), (bool*)(p + 3), (bool*)(p + 4), d, j.data.size());
        if (g != h || memcmp(o, p, 32)) t.fail("%s: GetInfo: guest %d, native %d, or the values differ", j.name.c_str(), g, h);
        free(o), free(p), free(d);
    }
}

NATIVE_TEST("lib_jpeg/ilog-and-tables") {
    for (u64 x = 0; x < 70000; x++) t.expect_eq((u32)t.call("_Z8glj_ilogj", {x}), glj_ilog((u32)x), "glj_ilog");
    for (int b = 16; b < 32; b++)
        for (u32 x : {1u << b, (1u << b) - 1, (1u << b) + 1, (3u << (b - 1))}) t.expect_eq((u32)t.call("_Z8glj_ilogj", {x}), glj_ilog(x), "glj_ilog");
    t.expect_eq(memcmp((const void*)(uintptr_t)t.sym("GLJ_REAL_IDCT8X8_SCALES"), kIdctScales, sizeof kIdctScales), 0, "GLJ_REAL_IDCT8X8_SCALES");
}

TestContext* g_t = nullptr;
u64 guest_sym(const char* s) { return g_t->sym(s); }

NATIVE_TEST("lib_jpeg/live-check") {
    g_t = &t;
    use_originals(guest_sym);
    live::Lockstep& ck = lockstep();
    u64 c0 = ck.checks(), b0 = ck.mismatches();
    ck.on = true;
    for (auto& j : synthetic(t)) {
        if (j.headers_only) continue;
        u8* d = (u8*)malloc(j.data.size());
        memcpy(d, j.data.data(), j.data.size());
        OutputSizes s = output_sizes(d, j.data.size());
        u32* o = (u32*)calloc(32, 4);
        checked_get_info(o, o + 1, (s32*)(o + 2), (bool*)(o + 3), (bool*)(o + 4), d, j.data.size());
        checked_plane_info(o, o + 4, o + 8, o + 12, o + 16, d, j.data.size());
        float* q = (float*)calloc(192, 4);
        u8* c = (u8*)calloc(1, s.coef_bytes + 16);
        checked_quant_coef(q, (s16*)c, d, j.data.size());
        u8* planes[4];
        for (int i = 0; i < 4; i++) planes[i] = (u8*)calloc(1, s.plane_bytes[i] + 16);
        checked_yuv((u32**)planes, d, j.data.size());
        u64* rgb = (u64*)calloc(1, 16);
        *rgb = t.sym("_ZTVN4Aska8JpegUtil16FnRGBXLineReaderE") + 0x10;
        u64* gray = (u64*)calloc(1, 16);
        *gray = t.sym("_ZTVN4Aska8JpegUtil21FnGrayscaleLineReaderE") + 0x10;
        u64* cmyk = (u64*)calloc(1, 16);
        *cmyk = t.sym("_ZTVN4Aska8JpegUtil16FnCMYKLineReaderE") + 0x10;
        u64* al = (u64*)calloc(1, 16);
        *al = t.sym("_ZTVN4Aska8JpegUtil21FnASKAEngineAllocatorE") + 0x10;
        u64 pitch = (u64)s.image_width * 4;
        u8* dst = (u8*)calloc(1, pitch * s.image_height + 16);
        checked_decode(dst, pitch, s.image_width, s.image_height, d, j.data.size(), (const JpegUtil::ILineScanner*)gray, (const JpegUtil::ILineScanner*)rgb,
                       (const JpegUtil::ILineScanner*)cmyk, (const JpegUtil::IAllocator*)al);
        for (u8* p : planes) free(p);
        free(q), free(c), free(o), free(d), free(dst), free(rgb), free(gray), free(cmyk), free(al);
    }
    ck.on = false;
    use_originals(nullptr);
    u64 n = ck.checks() - c0, bad = ck.mismatches() - b0;
    fprintf(stderr, "    %llu checks, %llu mismatches\n", (unsigned long long)n, (unsigned long long)bad);
    if (n < 30) t.fail("only %llu checks", (unsigned long long)n);
    if (bad) t.fail("%llu mismatches", (unsigned long long)bad);
}

}  // namespace
}  // namespace soa::native::lib_jpeg
