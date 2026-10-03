// aif2png: convert the game's Aska image containers (Image/etc2/*.aif, ADLD-wrapped,
// optionally SLZ-compressed) to PNG.  Standalone host tool; see docs/notes.md
// "Image assets and gacha banners" for the formats.
//
// Usage:
//   aif2png <in.aif> <asset-name> <out.png>      one file
//   aif2png -                                    batch: stdin lines "in<TAB>asset-name<TAB>out.png"
// <asset-name> is the path used for the ADLD key, e.g. "Image/etc2/banner_sale_001.aif".
// For each input one tab-separated line is printed: "ok <in> <out>:<w>x<h>:<kind>..." (one field
// per image) or "err <in> <reason>".  A file holding more than one image writes <out>,
// <out-stem>_1.png, ...  Also accepts Cocos scenes (UI/etc2/*.csf) and writes their atlas.
//
// Build: tools/aif2png/build.sh, or the repository build's `aif2png` target (zstd and zlib from
// vcpkg, IJG libjpeg 9 by FetchContent: cmake/deps.cmake).
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <csetjmp>
#include <string>
#include <vector>
#include <iostream>
#include <zlib.h>
#include <zstd.h>
extern "C" {
#include <jpeglib.h>
}

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;
using Bytes = std::vector<u8>;

static u32 rd32(const u8* p) { return p[0] | p[1] << 8 | p[2] << 16 | (u32)p[3] << 24; }
static u16 rd16(const u8* p) { return (u16)(p[0] | p[1] << 8); }

// ---------------------------------------------------------------- ADLD / CHash32
static u32 chash32(const std::string& s) {
    static u32 T[256];
    static bool init = false;
    if (!init) {
        for (u32 i = 0; i < 256; i++) {
            u32 c = i;
            for (int k = 0; k < 8; k++) c = (c & 1) ? (c >> 1) ^ 0xEDB88320u : c >> 1;
            T[i] = c;
        }
        init = true;
    }
    u32 c = (u32)s.size();
    for (unsigned char b : s) c = T[(c ^ b) & 0xff] ^ (c >> 8);
    return c;
}

// Only the XOR variant (flags & 1) is used by Image/ assets (version.bin encType 1).
static bool adld(Bytes& d, const std::string& name, std::string& err) {
    if (d.size() < 16 || memcmp(d.data(), "ADLD", 4)) return true;  // not wrapped
    u32 flags = rd32(&d[4]);
    Bytes body(d.begin() + 16, d.end());
    if (flags & 2) { err = "ADLD AES variant not supported here (use soa_save/adld.py)"; return false; }
    if (flags & 1) {
        char key[16];
        int n = snprintf(key, sizeof key, "%x", chash32(name));
        for (size_t i = 0; i < body.size(); i++) body[i] ^= (u8)key[i % n];
    }
    d.swap(body);
    return true;
}

// ---------------------------------------------------------------- SLZ
static bool slz(Bytes& d, std::string& err) {
    if (d.size() < 0x20 || memcmp(d.data(), "SLZ", 3)) return true;
    int codec = d[3];
    int32_t dsz = (int32_t)rd32(&d[0xc]);
    u32 off = rd32(&d[0x14]);
    u32 chunk = d[0x19] ? d[0x19] * 1024u : (u32)dsz;
    if (rd32(&d[0x1c])) { err = "chained SLZ not supported"; return false; }
    Bytes out;
    out.reserve(dsz);
    size_t p = off;
    while ((int32_t)out.size() < dsz) {
        u32 want = std::min<u32>(chunk, dsz - (u32)out.size());
        if (codec == 0) {
            if (p + want > d.size()) { err = "SLZ truncated"; return false; }
            out.insert(out.end(), d.begin() + p, d.begin() + p + want);
            p += want;
            continue;
        }
        if (p + 2 > d.size()) { err = "SLZ truncated"; return false; }
        u32 n = rd16(&d[p]);
        p += 2;
        bool raw = n == 0;  // a zero size means the chunk is stored raw
        if (raw) n = want;
        if (p + n > d.size()) { err = "SLZ truncated"; return false; }
        size_t base = out.size();
        out.resize(base + want);
        if (raw) {
            memcpy(&out[base], &d[p], want);
        } else if (codec == 7) {
            // The stored size counts one pad byte after the zstd frame (the game passes the
            // output size as the input size, so zstd stops at the frame end); trim to the frame.
            size_t fs = ZSTD_findFrameCompressedSize(&d[p], n);
            size_t r = ZSTD_decompress(&out[base], want, &d[p], ZSTD_isError(fs) ? n : fs);
            if (ZSTD_isError(r)) { err = std::string("zstd: ") + ZSTD_getErrorName(r); return false; }
            out.resize(base + r);
        } else if (codec == 5) {
            z_stream zs{};
            inflateInit2(&zs, -15);
            zs.next_in = &d[p];
            zs.avail_in = n;
            zs.next_out = &out[base];
            zs.avail_out = want;
            int r = inflate(&zs, Z_FINISH);
            inflateEnd(&zs);
            if (r != Z_STREAM_END && r != Z_OK) { err = "inflate failed"; return false; }
            out.resize(base + zs.total_out);
        } else {
            err = "SLZ codec " + std::to_string(codec) + " not supported";
            return false;
        }
        p += n;
    }
    d.swap(out);
    return true;
}

// ---------------------------------------------------------------- ETC1 / ETC2 / EAC
static inline u8 clamp8(int v) { return (u8)(v < 0 ? 0 : v > 255 ? 255 : v); }
static inline int ext4(int v) { return v << 4 | v; }
static inline int ext5(int v) { return v << 3 | v >> 2; }
static inline int ext6(int v) { return v << 2 | v >> 4; }
static inline int ext7(int v) { return v << 1 | v >> 6; }

static const int kEtcMod[8][2] = {{2, 8}, {5, 17}, {9, 29}, {13, 42}, {18, 60}, {24, 80}, {33, 106}, {47, 183}};
static const int kEtcDist[8] = {3, 6, 11, 16, 23, 32, 41, 64};

// Decodes one 8-byte ETC2 RGB block into rgba[16][4] (pixel (x,y) at y*4+x).
// punch: the RGB8_PUNCHTHROUGH_ALPHA1 variant (bit 33 is "opaque" instead of "diff").
static void etc2_rgb_block(const u8* b, u8 out[16][4], bool punch) {
    u64 v = 0;
    for (int i = 0; i < 8; i++) v = v << 8 | b[i];
    u32 idx = (u32)v;
    bool diff = (v >> 33) & 1, flip = (v >> 32) & 1;
    bool opaque = punch ? diff : true;
    if (punch) diff = true;
    auto pix = [&](int x, int y) {
        int j = x * 4 + y;
        return (int)(((idx >> (j + 16)) & 1) << 1 | ((idx >> j) & 1));
    };
    int r1, g1, b1, r2, g2, b2;
    if (!diff) {
        r1 = ext4((int)(v >> 60) & 15); r2 = ext4((int)(v >> 56) & 15);
        g1 = ext4((int)(v >> 52) & 15); g2 = ext4((int)(v >> 48) & 15);
        b1 = ext4((int)(v >> 44) & 15); b2 = ext4((int)(v >> 40) & 15);
    } else {
        int R = (int)(v >> 59) & 31, dR = (int)(v >> 56) & 7;
        int G = (int)(v >> 51) & 31, dG = (int)(v >> 48) & 7;
        int B = (int)(v >> 43) & 31, dB = (int)(v >> 40) & 7;
        if (dR & 4) dR -= 8;
        if (dG & 4) dG -= 8;
        if (dB & 4) dB -= 8;
        if (R + dR < 0 || R + dR > 31) {  // T mode
            int c1[3] = {ext4((int)((v >> 59) & 3) << 2 | (int)((v >> 56) & 3)), ext4((int)(v >> 52) & 15), ext4((int)(v >> 48) & 15)};
            int c2[3] = {ext4((int)(v >> 44) & 15), ext4((int)(v >> 40) & 15), ext4((int)(v >> 36) & 15)};
            int d = kEtcDist[((v >> 34) & 3) << 1 | ((v >> 32) & 1)];
            int paint[4][3];
            for (int c = 0; c < 3; c++) {
                paint[0][c] = c1[c];
                paint[1][c] = clamp8(c2[c] + d);
                paint[2][c] = c2[c];
                paint[3][c] = clamp8(c2[c] - d);
            }
            for (int y = 0; y < 4; y++)
                for (int x = 0; x < 4; x++) {
                    int i = pix(x, y);
                    u8* o = out[y * 4 + x];
                    if (!opaque && i == 2) { o[0] = o[1] = o[2] = o[3] = 0; continue; }
                    o[0] = (u8)paint[i][0]; o[1] = (u8)paint[i][1]; o[2] = (u8)paint[i][2]; o[3] = 255;
                }
            return;
        }
        if (G + dG < 0 || G + dG > 31) {  // H mode
            int R1 = (int)(v >> 59) & 15, G1 = (int)((v >> 56) & 7) << 1 | (int)((v >> 52) & 1);
            int B1 = (int)((v >> 51) & 1) << 3 | (int)((v >> 47) & 7);
            int R2 = (int)(v >> 43) & 15, G2 = (int)(v >> 39) & 15, B2 = (int)(v >> 35) & 15;
            int di = (int)((v >> 34) & 1) << 2 | (int)((v >> 32) & 1) << 1 | ((R1 << 8 | G1 << 4 | B1) >= (R2 << 8 | G2 << 4 | B2) ? 1 : 0);
            int d = kEtcDist[di];
            int c1[3] = {ext4(R1), ext4(G1), ext4(B1)}, c2[3] = {ext4(R2), ext4(G2), ext4(B2)};
            int paint[4][3];
            for (int c = 0; c < 3; c++) {
                paint[0][c] = clamp8(c1[c] + d);
                paint[1][c] = clamp8(c1[c] - d);
                paint[2][c] = clamp8(c2[c] + d);
                paint[3][c] = clamp8(c2[c] - d);
            }
            for (int y = 0; y < 4; y++)
                for (int x = 0; x < 4; x++) {
                    int i = pix(x, y);
                    u8* o = out[y * 4 + x];
                    if (!opaque && i == 2) { o[0] = o[1] = o[2] = o[3] = 0; continue; }
                    o[0] = (u8)paint[i][0]; o[1] = (u8)paint[i][1]; o[2] = (u8)paint[i][2]; o[3] = 255;
                }
            return;
        }
        if (B + dB < 0 || B + dB > 31) {  // planar (always opaque)
            int RO = ext6((int)(v >> 57) & 63);
            int GO = ext7((int)((v >> 56) & 1) << 6 | (int)((v >> 49) & 63));
            int BO = ext6((int)((v >> 48) & 1) << 5 | (int)((v >> 43) & 3) << 3 | (int)((v >> 39) & 7));
            int RH = ext6((int)((v >> 34) & 31) << 1 | (int)((v >> 32) & 1));
            int GH = ext7((int)(v >> 25) & 127), BH = ext6((int)(v >> 19) & 63);
            int RV = ext6((int)(v >> 13) & 63), GV = ext7((int)(v >> 6) & 127), BV = ext6((int)v & 63);
            for (int y = 0; y < 4; y++)
                for (int x = 0; x < 4; x++) {
                    u8* o = out[y * 4 + x];
                    o[0] = clamp8((x * (RH - RO) + y * (RV - RO) + 4 * RO + 2) >> 2);
                    o[1] = clamp8((x * (GH - GO) + y * (GV - GO) + 4 * GO + 2) >> 2);
                    o[2] = clamp8((x * (BH - BO) + y * (BV - BO) + 4 * BO + 2) >> 2);
                    o[3] = 255;
                }
            return;
        }
        r1 = ext5(R); r2 = ext5(R + dR);
        g1 = ext5(G); g2 = ext5(G + dG);
        b1 = ext5(B); b2 = ext5(B + dB);
    }
    int t1 = (int)(v >> 37) & 7, t2 = (int)(v >> 34) & 7;
    for (int y = 0; y < 4; y++)
        for (int x = 0; x < 4; x++) {
            bool second = flip ? y >= 2 : x >= 2;
            int t = second ? t2 : t1;
            int i = pix(x, y);
            u8* o = out[y * 4 + x];
            if (!opaque && i == 2) { o[0] = o[1] = o[2] = o[3] = 0; continue; }
            int m = (!opaque && i == 0) ? 0 : (i & 1 ? kEtcMod[t][1] : kEtcMod[t][0]) * (i & 2 ? -1 : 1);
            o[0] = clamp8((second ? r2 : r1) + m);
            o[1] = clamp8((second ? g2 : g1) + m);
            o[2] = clamp8((second ? b2 : b1) + m);
            o[3] = 255;
        }
}

static const int kEacMod[16][8] = {
    {-3, -6, -9, -15, 2, 5, 8, 14}, {-3, -7, -10, -13, 2, 6, 9, 12}, {-2, -5, -8, -13, 1, 4, 7, 12},
    {-2, -4, -6, -13, 1, 3, 5, 12}, {-3, -6, -8, -12, 2, 5, 7, 11}, {-3, -7, -9, -11, 2, 6, 8, 10},
    {-4, -7, -8, -11, 3, 6, 7, 10}, {-3, -5, -8, -11, 2, 4, 7, 10}, {-2, -6, -8, -10, 1, 5, 7, 9},
    {-2, -5, -8, -10, 1, 4, 7, 9},  {-2, -4, -8, -10, 1, 3, 7, 9},  {-2, -5, -7, -10, 1, 4, 6, 9},
    {-3, -4, -7, -10, 2, 3, 6, 9},  {-1, -2, -3, -10, 0, 1, 2, 9},  {-4, -6, -8, -9, 3, 5, 7, 8},
    {-3, -5, -7, -9, 2, 4, 6, 8}};

static void eac_alpha_block(const u8* b, u8 out[16][4]) {
    int base = b[0], mult = b[1] >> 4, tab = b[1] & 15;
    u64 bits = 0;
    for (int i = 2; i < 8; i++) bits = bits << 8 | b[i];
    for (int x = 0; x < 4; x++)
        for (int y = 0; y < 4; y++) {
            int i = x * 4 + y;
            int idx = (int)(bits >> (45 - 3 * i)) & 7;
            out[y * 4 + x][3] = clamp8(base + kEacMod[tab][idx] * mult);
        }
}

// ---------------------------------------------------------------- JPEG (libjpeg 9)
struct JErr {
    jpeg_error_mgr mgr;
    jmp_buf jb;
    char msg[JMSG_LENGTH_MAX];
};
static void jerr_exit(j_common_ptr c) {
    JErr* e = (JErr*)c->err;
    c->err->format_message(c, e->msg);
    longjmp(e->jb, 1);
}
static bool decode_jpeg(const u8* p, size_t n, int& w, int& h, Bytes& rgba, std::string& err) {
    jpeg_decompress_struct ci;
    JErr je;
    ci.err = jpeg_std_error(&je.mgr);
    je.mgr.error_exit = jerr_exit;
    if (setjmp(je.jb)) {
        err = std::string("jpeg: ") + je.msg;
        jpeg_destroy_decompress(&ci);
        return false;
    }
    jpeg_create_decompress(&ci);
    jpeg_mem_src(&ci, (unsigned char*)p, (unsigned long)n);
    jpeg_read_header(&ci, TRUE);
    ci.out_color_space = JCS_RGB;
    jpeg_start_decompress(&ci);
    w = (int)ci.output_width;
    h = (int)ci.output_height;
    rgba.assign((size_t)w * h * 4, 255);
    std::vector<u8> row((size_t)w * 3);
    while (ci.output_scanline < ci.output_height) {
        u8* rp = row.data();
        int y = (int)ci.output_scanline;
        jpeg_read_scanlines(&ci, &rp, 1);
        for (int x = 0; x < w; x++) memcpy(&rgba[((size_t)y * w + x) * 4], &row[x * 3], 3);
    }
    jpeg_finish_decompress(&ci);
    jpeg_destroy_decompress(&ci);
    return true;
}

// ---------------------------------------------------------------- PNG writer
static void be32(Bytes& o, u32 v) {
    o.push_back(v >> 24); o.push_back(v >> 16); o.push_back(v >> 8); o.push_back(v);
}
static void chunk(Bytes& o, const char* type, const Bytes& data) {
    be32(o, (u32)data.size());
    size_t start = o.size();
    o.insert(o.end(), type, type + 4);
    o.insert(o.end(), data.begin(), data.end());
    be32(o, (u32)crc32(0, &o[start], (uInt)(o.size() - start)));
}
static bool write_png(const std::string& path, int w, int h, const Bytes& rgba, bool alpha) {
    int ch = alpha ? 4 : 3;
    Bytes raw;
    raw.reserve((size_t)(w * ch + 1) * h);
    for (int y = 0; y < h; y++) {
        raw.push_back(0);
        for (int x = 0; x < w; x++) {
            const u8* p = &rgba[((size_t)y * w + x) * 4];
            raw.insert(raw.end(), p, p + ch);
        }
    }
    uLongf zn = compressBound((uLong)raw.size());
    Bytes z(zn);
    compress2(z.data(), &zn, raw.data(), (uLong)raw.size(), 6);
    z.resize(zn);
    Bytes o = {0x89, 'P', 'N', 'G', '\r', '\n', 0x1a, '\n'};
    Bytes ihdr;
    be32(ihdr, (u32)w); be32(ihdr, (u32)h);
    ihdr.push_back(8); ihdr.push_back(alpha ? 6 : 2); ihdr.push_back(0); ihdr.push_back(0); ihdr.push_back(0);
    chunk(o, "IHDR", ihdr);
    chunk(o, "IDAT", z);
    chunk(o, "IEND", {});
    FILE* f = fopen(path.c_str(), "wb");
    if (!f) return false;
    bool ok = fwrite(o.data(), 1, o.size(), f) == o.size();
    return fclose(f) == 0 && ok;
}

// ---------------------------------------------------------------- AIF image chunk ('imgX')
// Image header chunk (tag bytes "Xgmi", 0x70 bytes, pixel data follows at +chunk size):
//   +0x04 u32 chunk size (0x70)    +0x20 u8 format            +0x22 u8 flags (3 on JPEG)
//   +0x28 u16 width, u16 height    +0x2c u16 mip levels       +0x2e u16 bits per pixel
//   +0x30 u16 bytes per block, u16 blocks across, u16 blocks down   +0x38 u32 row pitch
//   +0x40 GUID of the data block (see find_data)
// Formats seen: 39 JPEG, 47 ETC2 RGB8 (ETC1-compatible), 48 ETC2 RGB8 punch-through A1,
// 49 ETC2 RGBA8 (EAC alpha block + ETC2 colour block).
struct Img {
    int w = 0, h = 0, fmt = 0;
    bool alpha = false;
    Bytes rgba;
    const char* kind = "";
};

// Where an image's pixel data lives.  The ' FMA' (AMF) chunk ends with the data buffer
// ('buff' +0x10 = buffer size, so buffer = AMF start + AMF size - buffer size); each 'addr'
// chunk names a block of that buffer by GUID (+0x10), with size +0x20 and offset +0x28.
// The image header's GUID (+0x40) selects its block.
static bool find_data(const Bytes& d, size_t base, size_t at, size_t& data, size_t& size) {
    auto find = [&](const char* tag, size_t from, size_t to) -> size_t {
        for (size_t i = from; i + 16 <= to; i += 16)
            if (!memcmp(&d[i], tag, 4)) return i;
        return std::string::npos;
    };
    size_t amf = find(" FMA", base, d.size());
    if (amf == std::string::npos) return false;
    size_t amf_end = amf + rd32(&d[amf + 4]);
    size_t buff = find("ffub", amf, std::min(amf_end, d.size()));
    if (buff == std::string::npos || amf_end > d.size()) return false;
    size_t bsz = rd32(&d[buff + 0x10]);
    if (bsz > amf_end - amf) return false;
    size_t start = amf_end - bsz;
    for (size_t a = amf; (a = find("rdda", a, std::min(start, amf_end))) != std::string::npos; a += 16) {
        if (memcmp(&d[a + 0x10], &d[at + 0x40], 16)) continue;
        size = rd32(&d[a + 0x20]);
        data = start + rd32(&d[a + 0x28]);
        return data + size <= d.size();
    }
    return false;
}

static bool decode_image(const Bytes& d, size_t base, size_t at, Img& img, std::string& err) {
    if (at + 0x70 > d.size()) { err = "truncated image header"; return false; }
    const u8* h = &d[at];
    img.fmt = h[0x20];
    img.w = rd16(h + 0x28);
    img.h = rd16(h + 0x2a);
    size_t data = 0, dsz = 0;
    if (!find_data(d, base, at, data, dsz)) { err = "image data block not found"; return false; }
    if (img.fmt == 39) {
        if (dsz < 3 || d[data] != 0xff || d[data + 1] != 0xd8) { err = "JPEG SOI not at data offset"; return false; }
        size_t n = dsz;
        int jw, jh;
        if (!decode_jpeg(&d[data], n, jw, jh, img.rgba, err)) return false;
        img.w = jw; img.h = jh;
        img.alpha = false;
        img.kind = "jpeg";
        return true;
    }
    bool rgba8 = img.fmt == 49, punch = img.fmt == 48;
    if (img.fmt != 47 && img.fmt != 48 && img.fmt != 49) { err = "unknown format " + std::to_string(img.fmt); return false; }
    int bw = (img.w + 3) / 4, bh = (img.h + 3) / 4, bpb = rgba8 ? 16 : 8;
    if ((size_t)bw * bh * bpb > dsz) { err = "pixel data truncated"; return false; }
    img.rgba.assign((size_t)img.w * img.h * 4, 0);
    u8 blk[16][4];
    for (int by = 0; by < bh; by++)
        for (int bx = 0; bx < bw; bx++) {
            const u8* b = &d[data + ((size_t)by * bw + bx) * bpb];
            etc2_rgb_block(rgba8 ? b + 8 : b, blk, punch);
            if (rgba8) eac_alpha_block(b, blk);
            for (int y = 0; y < 4; y++)
                for (int x = 0; x < 4; x++) {
                    int px = bx * 4 + x, py = by * 4 + y;
                    if (px < img.w && py < img.h) memcpy(&img.rgba[((size_t)py * img.w + px) * 4], blk[y * 4 + x], 4);
                }
        }
    img.alpha = rgba8 || punch;
    img.kind = rgba8 ? "etc2-rgba8" : punch ? "etc2-rgb8a1" : "etc2-rgb8";
    return true;
}

static std::string convert(const std::string& in, const std::string& name, const std::string& out) {
    FILE* f = fopen(in.c_str(), "rb");
    if (!f) return "err\t" + in + "\tcannot open";
    Bytes d;
    u8 buf[65536];
    size_t n;
    while ((n = fread(buf, 1, sizeof buf, f)) > 0) d.insert(d.end(), buf, buf + n);
    fclose(f);
    std::string err;
    if (!adld(d, name, err) || !slz(d, err)) return "err\t" + in + "\t" + err;
    // An .aif is one ' FIA' container; a Cocos scene (.csf, tag "\0ISF") embeds its texture
    // atlas as a ' FIA' container.  Each container: images ('Xgmi' chunks) up to the end of its
    // ' FMA' chunk (whose buffer may itself start with a nested ' FIA' header: skipped).
    auto at16 = [&](size_t i, const char* t) { return i + 4 <= d.size() && !memcmp(&d[i], t, 4); };
    std::vector<std::pair<size_t, size_t>> imgs;  // (container start, image chunk)
    for (size_t c = 0; c + 16 <= d.size(); c += 16) {
        if (!at16(c, " FIA")) continue;
        size_t amf = c, end = d.size();
        while (amf + 16 <= d.size() && !at16(amf, " FMA")) amf += 16;
        if (amf + 16 <= d.size()) end = std::min(d.size(), amf + rd32(&d[amf + 4]));
        for (size_t i = c; i + 16 <= end; i += 16)  // chunks are 16-byte aligned
            if (at16(i, "Xgmi")) imgs.push_back({c, i});
        c = (end + 15) / 16 * 16 - 16;
    }
    if (imgs.empty()) return "err\t" + in + "\tno image in file";
    std::string res = "ok\t" + in;
    for (size_t k = 0; k < imgs.size(); k++) {
        Img img;
        if (!decode_image(d, imgs[k].first, imgs[k].second, img, err)) return "err\t" + in + "\t" + err;
        std::string o = out;
        if (k) o = out.substr(0, out.size() - 4) + "_" + std::to_string(k) + ".png";
        if (!write_png(o, img.w, img.h, img.rgba, img.alpha)) return "err\t" + in + "\tcannot write " + o;
        res += "\t" + o + ":" + std::to_string(img.w) + "x" + std::to_string(img.h) + ":" + img.kind;
    }
    return res;
}

int main(int argc, char** argv) {
    if (argc == 4) {
        std::string r = convert(argv[1], argv[2], argv[3]);
        puts(r.c_str());
        return r.rfind("ok", 0) == 0 ? 0 : 1;
    }
    if (argc == 2 && !strcmp(argv[1], "-")) {
        std::string line;
        while (std::getline(std::cin, line)) {
            size_t a = line.find('\t'), b = a == std::string::npos ? a : line.find('\t', a + 1);
            if (b == std::string::npos) { puts(("err\t" + line + "\tbad input line").c_str()); continue; }
            puts(convert(line.substr(0, a), line.substr(a + 1, b - a - 1), line.substr(b + 1)).c_str());
            fflush(stdout);
        }
        return 0;
    }
    fprintf(stderr, "usage: aif2png <in.aif> <asset-name> <out.png> | aif2png -\n");
    return 2;
}
