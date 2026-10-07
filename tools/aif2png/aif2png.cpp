// aif2png: convert the game's Aska image containers (Image/etc2/*.aif, ADLD-wrapped,
// optionally SLZ-compressed) to PNG.  Standalone host tool; see docs/notes.md
// "Image assets and gacha banners" for the formats.
//
// Usage:
//   aif2png <in.aif> <asset-name> <out.png>      one file (<in.aif> may be FILE@OFFSET+SIZE: a byte
//                                                range of FILE, e.g. a stored zip entry in place)
//   aif2png -                                    batch: stdin lines "in<TAB>asset-name<TAB>out.png"
// <asset-name> is the path used for the ADLD key, e.g. "Image/etc2/banner_sale_001.aif".
// For each input one tab-separated line is printed: "ok <in> <out>:<w>x<h>:<kind>..." (one field
// per image) or "err <in> <reason>".  A file holding more than one image writes <out>,
// <out-stem>_1.png, ...  Also accepts Cocos scenes (UI/etc2/*.csf) and writes their atlas.
//
// Build: tools/aif2png/build.sh, or the repository build's `aif2png` target (soa_codec: ADLD,
// soa/adld.h; SLZ / AIF / ETC2, soa/aska_image.h; IJG libjpeg 9 by FetchContent: cmake/deps.cmake).
#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <csetjmp>
#include <string>
#include <vector>
#include <iostream>
#include <soa/adld.h>
#include <soa/aska_image.h>
#include <soa/png.h>
extern "C" {
#include <jpeglib.h>
}

using u8 = uint8_t;
using Bytes = std::vector<u8>;

// ---------------------------------------------------------------- SLZ
static bool slz(Bytes& d, std::string& err) {
    if (!soa::aska::is_slz(d)) return true;
    Bytes out;
    if (!soa::aska::slz_decode(d, out, &err)) return false;
    d.swap(out);
    return true;
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
// RGB (colour type 2) or RGBA (6) from the decoded RGBA pixels: soa/png.h (stb_image_write).
static bool write_png(const std::string& path, int w, int h, const Bytes& rgba, bool alpha) {
    if (alpha) return soa::png_write(path, w, h, 4, rgba.data());
    Bytes rgb((size_t)w * h * 3);
    for (size_t i = 0; i < (size_t)w * h; i++) memcpy(&rgb[i * 3], &rgba[i * 4], 3);
    return soa::png_write(path, w, h, 3, rgb.data());
}

// ---------------------------------------------------------------- AIF images
// The containers, image headers and ETC2 pixels: soa/aska_image.h (docs/notes.md "Image assets and
// gacha banners"). Formats seen: 39 JPEG (decoded here), 47 ETC2 RGB8, 48 ETC2 RGB8 punch-through
// A1, 49 ETC2 RGBA8.
struct Img {
    int w = 0, h = 0, fmt = 0;
    bool alpha = false;
    Bytes rgba;
    const char* kind = "";
};

static bool decode_image(const Bytes& d, const soa::aska::ImageRef& r, Img& img, std::string& err) {
    img.fmt = r.fmt;
    img.w = r.w;
    img.h = r.h;
    if (img.fmt == soa::aska::kJpeg) {
        if (r.data_size < 3 || d[r.data] != 0xff || d[r.data + 1] != 0xd8) { err = "JPEG SOI not at data offset"; return false; }
        int jw, jh;
        if (!decode_jpeg(&d[r.data], r.data_size, jw, jh, img.rgba, err)) return false;
        img.w = jw; img.h = jh;
        img.alpha = false;
        img.kind = "jpeg";
        return true;
    }
    if (!soa::aska::block_bytes(img.fmt)) { err = "unknown format " + std::to_string(img.fmt); return false; }
    if (!soa::aska::decode_image(d, r, img.rgba, &err)) return false;
    bool rgba8 = img.fmt == soa::aska::kEtc2Rgba8, punch = img.fmt == soa::aska::kEtc2Rgb8A1;
    img.alpha = rgba8 || punch;
    img.kind = rgba8 ? "etc2-rgba8" : punch ? "etc2-rgb8a1" : "etc2-rgb8";
    return true;
}

// `in` is a file, or "FILE@OFFSET+SIZE": SIZE bytes at OFFSET of FILE (a stored entry of a zip such
// as the 3.7.0 download's SOA-3.7.0-canonical-data.zip, read in place: soa_save/download_tree.py
// DownloadTree.locate). A path that exists as given is always a file.
static bool read_input(const std::string& in, Bytes& d) {
    std::string path = in;
    long long off = 0, size = -1;
    size_t at = in.rfind('@'), plus = in.rfind('+');
    FILE* f = fopen(in.c_str(), "rb");
    if (!f && at != std::string::npos && plus != std::string::npos && plus > at + 1 && plus + 1 < in.size() &&
        in.find_first_not_of("0123456789", at + 1) == plus && in.find_first_not_of("0123456789", plus + 1) == std::string::npos) {
        path = in.substr(0, at);
        off = std::stoll(in.substr(at + 1, plus - at - 1));
        size = std::stoll(in.substr(plus + 1));
        f = fopen(path.c_str(), "rb");
#ifdef _WIN32
        if (f && _fseeki64(f, off, SEEK_SET) != 0) {
#else
        if (f && fseeko(f, (off_t)off, SEEK_SET) != 0) {
#endif
            fclose(f);
            return false;
        }
    }
    if (!f) return false;
    u8 buf[65536];
    size_t n;
    while ((size < 0 || (long long)d.size() < size) &&
           (n = fread(buf, 1, size < 0 ? sizeof buf : (size_t)std::min<long long>((long long)sizeof buf, size - (long long)d.size()), f)) > 0)
        d.insert(d.end(), buf, buf + n);
    fclose(f);
    return size < 0 || (long long)d.size() == size;
}

static std::string convert(const std::string& in, const std::string& name, const std::string& out) {
    Bytes d;
    if (!read_input(in, d)) return "err\t" + in + "\tcannot open";
    std::string err;
    // ADLD (soa/adld.h): XOR (flags & 1, what Image/ assets use: version.bin encType 1) or AES
    if (soa::adld::is_adld(d.data(), d.size())) d = soa::adld::decrypt(name, d);
    if (!slz(d, err)) return "err\t" + in + "\t" + err;
    // An .aif is one ' FIA' container; a Cocos scene (.csf, tag "\0ISF") embeds its texture
    // atlas as a ' FIA' container.
    std::vector<soa::aska::ImageRef> imgs = soa::aska::find_images(d);
    if (imgs.empty()) return "err\t" + in + "\tno image in file";
    std::string res = "ok\t" + in;
    for (size_t k = 0; k < imgs.size(); k++) {
        Img img;
        if (!decode_image(d, imgs[k], img, err)) return "err\t" + in + "\t" + err;
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
