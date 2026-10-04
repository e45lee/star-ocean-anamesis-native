// Differential tests of lib_zstd: the same frames decompressed by the guest's zstd 1.3.4 (t.call on
// the original code) and by the natives (lib_zstd_api.h), called the way Aska::_DecodeMain<*, 7>
// calls them: one-shot with the output size as the input size, and streamed (above 64 KiB) with
// in.size = out.size; results, positions and every output byte compared.
#define ZSTD_STATIC_LINKING_ONLY  // ZSTD_compress_advanced (1.3.4)
#include <zstd.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

#include "native/common/test.h"
#include "native/common/test_assets.h"
#include "native/lib_zstd/lib_zstd_api.h"

namespace soa::native::lib_zstd {
namespace {

template <typename T>
u64 A(T* p) { return (u64)(uintptr_t)p; }

// Guest-visible copies (malloc) of the input, padded to at least `min` bytes.
struct Buf {
    u8* p;
    size_t n;
    Buf(const u8* d, size_t len, size_t min) : n(len > min ? len : min) {
        p = (u8*)calloc(1, n + 16);
        memcpy(p, d, len);
    }
    ~Buf() { free(p); }
};

// One-shot: ZSTD_decompress(dst, out, src, n) on both; the outputs prefilled alike.
bool one_shot(TestContext& t, const u8* src, size_t n, size_t out, const std::string& what) {
    Buf in(src, n, out);
    std::vector<u8> fill(out + 1, 0xa5);
    u8* g = (u8*)malloc(out + 1);
    u8* h = (u8*)malloc(out + 1);
    memcpy(g, fill.data(), out + 1), memcpy(h, fill.data(), out + 1);
    u64 gr = t.call("ZSTD_decompress", {A(g), out, A(in.p), n});
    u64 hr = decompress(h, out, in.p, n);
    bool ok = gr == hr && !memcmp(g, h, out + 1);
    if (!ok) t.fail("%s: ZSTD_decompress(%zu, %zu): guest %#llx, native %#llx%s", what.c_str(), out, n, (unsigned long long)gr, (unsigned long long)hr,
                    memcmp(g, h, out + 1) ? ", the bytes differ" : "");
    free(g), free(h);
    return ok;
}

// Streamed like _DecodeMain: create, init, decompressStream with in.size = out.size until 0 or an error.
bool streamed(TestContext& t, const u8* src, size_t n, size_t out, const std::string& what) {
    Buf in(src, n, out);
    u8* g = (u8*)calloc(1, out + 1);
    u8* h = (u8*)calloc(1, out + 1);
    u64 gs = t.call("ZSTD_createDStream", {});
    void* hs = create_dstream();
    bool ok = true;
    u64 gi = t.call("ZSTD_initDStream", {gs}), hi = init_dstream(hs);
    if (gi != hi) ok = false, t.fail("%s: ZSTD_initDStream: guest %#llx, native %#llx", what.c_str(), (unsigned long long)gi, (unsigned long long)hi);
    auto* bufs = (u8*)calloc(1, 4 * sizeof(ZSTDOutBuffer));
    auto* go = (ZSTDOutBuffer*)bufs;
    auto* gin = (ZSTDInBuffer*)(bufs + 0x18);
    auto* ho = (ZSTDOutBuffer*)(bufs + 0x30);
    auto* hin = (ZSTDInBuffer*)(bufs + 0x48);
    *go = {g, out, 0}, *ho = {h, out, 0};
    *gin = {in.p, out, 0}, *hin = {in.p, out, 0};
    for (int step = 0; ok && step < 64; step++) {
        u64 gr = t.call("ZSTD_decompressStream", {gs, A(go), A(gin)});
        u64 hr = decompress_stream(hs, ho, hin);
        if (gr != hr || go->pos != ho->pos || gin->pos != hin->pos) {
            t.fail("%s: step %d: ZSTD_decompressStream: guest %#llx (out %llu, in %llu), native %#llx (out %llu, in %llu)", what.c_str(), step,
                   (unsigned long long)gr, (unsigned long long)go->pos, (unsigned long long)gin->pos, (unsigned long long)hr, (unsigned long long)ho->pos,
                   (unsigned long long)hin->pos);
            ok = false;
        }
        if (gr == 0 || (s64)gr < 0 || (go->pos == out && gin->pos == gin->size)) break;
        if (gin->pos == gin->size && go->pos < out) break;  // (_DecodeMain would spin: no more input)
    }
    if (ok && memcmp(g, h, out + 1)) ok = false, t.fail("%s: streamed: the bytes differ", what.c_str());
    u64 gf = t.call("ZSTD_freeDStream", {gs}), hf = free_dstream(hs);
    if (gf != hf) ok = false, t.fail("%s: ZSTD_freeDStream: guest %#llx, native %#llx", what.c_str(), (unsigned long long)gf, (unsigned long long)hf);
    free(bufs), free(g), free(h);
    return ok;
}

NATIVE_TEST("lib_zstd/download-chunks") {
    // the game's own frames: SLZ codec-7 chunks of downloaded assets (each stored size counts one pad
    // byte after its frame; the game hands over the output size as the input size)
    size_t chunks = 0;
    for (const char* dir : {"Image/etc2", "Motion", "Effect", "UI/etc2"}) {
        size_t files = 0;
        for (auto& rel : test_assets::download_files(dir, "", 200)) {
            auto cs = test_assets::slz_chunks(test_assets::download_payload(rel), 7, 3);
            if (cs.empty()) continue;
            for (auto& c : cs) {
                one_shot(t, c.data.data(), c.data.size(), c.out, rel);
                one_shot(t, c.data.data(), c.stored, c.out, rel + " (stored size)");
                streamed(t, c.data.data(), c.data.size(), c.out, rel);
                chunks++;
            }
            if (++files == 6) break;
        }
    }
    if (!chunks) fprintf(stderr, "    (no download: skipped)\n");
    else fprintf(stderr, "    %zu chunks\n", chunks);
}

NATIVE_TEST("lib_zstd/synthetic") {
    // frames of every level and size class (incl. > 64 KiB: the streamed path), with and without a
    // checksum / content size; then damaged and cut ones (the error codes must agree too)
    std::vector<u8> text;
    while (text.size() < 300000) {
        char line[96];
        int n = snprintf(line, sizeof line, "role_cp%04d_b%02da_%d %s\n", t.rand_int(0, 9999), t.rand_int(0, 99), t.rand_int(0, 1 << 20),
                         t.rand_int(0, 3) ? "AskaOGG" : "SLVoice");
        text.insert(text.end(), line, line + n);
    }
    std::vector<u8> noise = t.rand_bytes(150000);
    int frames = 0;
    for (auto* src : {&text, &noise})
        for (size_t size : {(size_t)1, (size_t)100, (size_t)4096, (size_t)65536, (size_t)70000, (size_t)150000})
            for (int level : {1, 3, 9, 19}) {
                if (size > src->size()) continue;
                ZSTD_CCtx* cc = ZSTD_createCCtx();
                ZSTD_parameters par = ZSTD_getParams(level, size, 0);
                par.fParams.checksumFlag = level & 1;
                par.fParams.contentSizeFlag = level != 9;
                std::vector<u8> f(ZSTD_compressBound(size));
                size_t n = ZSTD_compress_advanced(cc, f.data(), f.size(), src->data(), size, nullptr, 0, par);
                ZSTD_freeCCtx(cc);
                if (ZSTD_isError(n)) continue;
                f.resize(n);
                std::string what = (src == &text ? "text " : "noise ") + std::to_string(size) + " level " + std::to_string(level);
                one_shot(t, f.data(), n, size, what);
                one_shot(t, f.data(), n + 1, size, what + " +1 byte");
                one_shot(t, f.data(), n, size - 1 ? size - 1 : 1, what + " short output");
                streamed(t, f.data(), n, size, what);
                std::vector<u8> bad = f;
                for (size_t i = 6; i < bad.size(); i += 1 + bad.size() / 7) bad[i] ^= 0x5a;
                one_shot(t, bad.data(), n, size, what + " damaged");
                streamed(t, bad.data(), n, size, what + " damaged");
                one_shot(t, f.data(), n / 2, size, what + " cut");
                frames++;
            }
    fprintf(stderr, "    %d frames\n", frames);
}

NATIVE_TEST("lib_zstd/constants") {
    t.expect_eq(t.call("ZSTD_DStreamInSize", {}), dstream_in_size(), "ZSTD_DStreamInSize");
    t.expect_eq(t.call("ZSTD_DStreamOutSize", {}), dstream_out_size(), "ZSTD_DStreamOutSize");
    for (u64 code = 0; code < 200; code++)
        for (u64 v : {code, (u64)0 - code}) t.expect_eq((u32)t.call("ZSTD_isError", {v}), is_error(v), "ZSTD_isError");
}

TestContext* g_t = nullptr;
u64 guest_sym(const char* s) { return g_t->sym(s); }

NATIVE_TEST("lib_zstd/live-check") {
    // --live-check lib_zstd on the natives: no mismatch
    std::vector<u8> text(200000);
    for (size_t i = 0; i < text.size(); i++) text[i] = (u8)("SLZ chunk " [i % 10] + (i / 4096));
    std::vector<u8> f(ZSTD_compressBound(text.size()));
    f.resize(ZSTD_compress(f.data(), f.size(), text.data(), text.size(), 3));
    g_t = &t;
    use_originals(guest_sym);
    live::Lockstep& ck = lockstep();
    u64 c0 = ck.checks(), b0 = ck.mismatches();
    ck.on = true;
    Buf in(f.data(), f.size(), text.size());
    std::vector<u8> out(text.size());
    decompress(out.data(), out.size(), in.p, text.size());
    void* s = create_dstream();
    init_dstream(s);
    ZSTDOutBuffer o{out.data(), out.size(), 0};
    ZSTDInBuffer i{in.p, text.size(), 0};
    for (int k = 0; k < 16 && decompress_stream(s, &o, &i) != 0; k++) {
    }
    free_dstream(s);
    ck.on = false;
    use_originals(nullptr);
    t.expect_eq(out == text, true, "decoded");
    u64 n = ck.checks() - c0, bad = ck.mismatches() - b0;
    fprintf(stderr, "    %llu checks, %llu mismatches\n", (unsigned long long)n, (unsigned long long)bad);
    if (n < 4) t.fail("only %llu checks", (unsigned long long)n);
    if (bad) t.fail("%llu mismatches", (unsigned long long)bad);
}

}  // namespace
}  // namespace soa::native::lib_zstd
