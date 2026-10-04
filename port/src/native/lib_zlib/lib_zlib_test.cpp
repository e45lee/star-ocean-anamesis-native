// Differential tests of lib_zlib: the same streams inflated by the guest's zlib 1.2.5 (t.call on the
// original code) and by the natives (lib_zlib_api.h), called the way AskaUncompress* calls them (one
// inflate with Z_FINISH, the output size as the input size) and in small steps; results, positions,
// totals, checksums, messages and every output byte compared.
#include <zlib.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

#include "native/common/test.h"
#include "native/common/test_assets.h"
#include "native/lib_zlib/lib_zlib_api.h"

namespace soa::native::lib_zlib {
namespace {

template <typename T>
u64 A(T* p) { return (u64)(uintptr_t)p; }

struct Run {
    std::vector<long long> r;  // results, positions, totals, checksums of every call
    std::vector<u8> out;
    std::string msgs;
};

// Inflates `src` (n bytes readable) into `out_size` bytes with window bits `wb`, `step` bytes of
// output per inflate call (0: one call with Z_FINISH, as the game does).
template <typename Init, typename Inf, typename End>
Run run(Init init, Inf inf, End end, const std::vector<u8>& src, size_t n, size_t out_size, int wb, size_t step) {
    Run R;
    auto* s = (ZStream*)calloc(1, sizeof(ZStream) + 16);
    u8* in = (u8*)calloc(1, (n > src.size() ? n : src.size()) + 16);
    memcpy(in, src.data(), src.size());
    u8* out = (u8*)malloc(out_size + 1);
    memset(out, 0x5a, out_size + 1);
    s->next_in = in, s->avail_in = (u32)n, s->next_out = out, s->avail_out = (u32)(step ? (step < out_size ? step : out_size) : out_size);
    R.r.push_back(init(s, wb));
    if (R.r.back() == Z_OK) {
        for (int k = 0; k < 100000; k++) {
            s32 e = inf(s, step ? Z_NO_FLUSH : Z_FINISH);
            R.r.push_back(e), R.r.push_back(s->avail_in), R.r.push_back(s->avail_out), R.r.push_back((long long)s->total_in),
                R.r.push_back((long long)s->total_out), R.r.push_back((long long)s->adler);
            if (s->msg) R.msgs += std::string(s->msg) + ";";
            if (!step || e != Z_OK) break;
            size_t done = (size_t)(s->next_out - out);
            if (done >= out_size) break;
            if (!s->avail_out) s->avail_out = (u32)(out_size - done < step ? out_size - done : step);
        }
        R.r.push_back(end(s));
    }
    R.out.assign(out, out + out_size + 1);
    free(s), free(in), free(out);
    return R;
}

void compare(TestContext& t, const std::vector<u8>& src, size_t n, size_t out, int wb, size_t step, const std::string& what) {
    static const char kVersion[] = "1.2.5";  // the game's
    auto gi = [&](ZStream* s, int w) { return (s32)(u32)t.call("inflateInit2_", {A(s), (u64)(u32)w, A(kVersion), sizeof(ZStream)}); };
    auto gf = [&](ZStream* s, int f) { return (s32)(u32)t.call("inflate", {A(s), (u64)(u32)f}); };
    auto ge = [&](ZStream* s) { return (s32)(u32)t.call("inflateEnd", {A(s)}); };
    auto hi = [&](ZStream* s, int w) { return inflate_init2(s, w, kVersion, sizeof(ZStream)); };
    auto hf = [&](ZStream* s, int f) { return inflate_(s, f); };
    auto he = [&](ZStream* s) { return inflate_end(s); };
    Run g = run(gi, gf, ge, src, n, out, wb, step), h = run(hi, hf, he, src, n, out, wb, step);
    if (g.r != h.r) {
        size_t i = 0;
        while (i < g.r.size() && i < h.r.size() && g.r[i] == h.r[i]) i++;
        t.fail("%s: value %zu: guest %lld, native %lld (%zu / %zu values)", what.c_str(), i, i < g.r.size() ? g.r[i] : -999, i < h.r.size() ? h.r[i] : -999,
               g.r.size(), h.r.size());
    }
    if (g.out != h.out) t.fail("%s: the output differs", what.c_str());
    if (g.msgs != h.msgs) t.fail("%s: messages: guest \"%s\", native \"%s\"", what.c_str(), g.msgs.c_str(), h.msgs.c_str());
}

NATIVE_TEST("lib_zlib/download-chunks") {
    // the game's own streams: SLZ codec-5 (raw deflate) chunks, inflated as AskaUncompressGzip does
    size_t chunks = 0;
    for (const char* dir : {"Image/etc2", "UI/etc2", "Character", "BG"}) {
        size_t files = 0;
        for (auto& rel : test_assets::download_files(dir, "", 400)) {
            auto cs = test_assets::slz_chunks(test_assets::download_payload(rel), 5, 3);
            if (cs.empty()) continue;
            for (auto& c : cs) {
                compare(t, c.data, c.out, c.out, -15, 0, rel);
                compare(t, c.data, c.stored, c.out, -15, 0, rel + " (stored size)");
                compare(t, c.data, c.stored, c.out, -15, 1000, rel + " (1000-byte steps)");
                chunks++;
            }
            if (++files == 5) break;
        }
    }
    if (!chunks) fprintf(stderr, "    (no download: skipped)\n");
    else fprintf(stderr, "    %zu chunks\n", chunks);
}

NATIVE_TEST("lib_zlib/synthetic") {
    // raw / zlib / gzip / auto-detected streams of every level, whole and in steps; damaged and cut
    std::vector<u8> text;
    while (text.size() < 200000) {
        char line[80];
        int n = snprintf(line, sizeof line, "BridgeNotify %d gzip %08x %s\n", t.rand_int(0, 99999), (unsigned)t.rand_u64(), t.rand_int(0, 1) ? "ok" : "ng");
        text.insert(text.end(), line, line + n);
    }
    std::vector<u8> noise = t.rand_bytes(50000);
    int streams = 0;
    for (auto* src : {&text, &noise})
        for (size_t size : {(size_t)0, (size_t)10, (size_t)5000, (size_t)65536, (size_t)50000})
            for (int level : {0, 1, 6, 9})
                for (int wb : {-15, 15, 31}) {
                    if (size > src->size()) continue;
                    z_stream z{};
                    deflateInit2(&z, level, Z_DEFLATED, wb, 8, Z_DEFAULT_STRATEGY);
                    std::vector<u8> f(deflateBound(&z, size) + 64);
                    z.next_in = src->data(), z.avail_in = (uInt)size, z.next_out = f.data(), z.avail_out = (uInt)f.size();
                    deflate(&z, Z_FINISH);
                    f.resize(z.total_out);
                    deflateEnd(&z);
                    std::string what = std::to_string(size) + " level " + std::to_string(level) + " wb " + std::to_string(wb);
                    compare(t, f, f.size(), size, wb, 0, what);
                    compare(t, f, size > f.size() ? size : f.size(), size, wb, 0, what + " (output size as input)");
                    compare(t, f, f.size(), size, wb == 31 ? 47 : wb, 777, what + " (steps)");
                    compare(t, f, f.size(), size ? size - 1 : 0, wb, 0, what + " (short output)");
                    std::vector<u8> bad = f;
                    for (size_t i = 3; i < bad.size(); i += 1 + bad.size() / 5) bad[i] ^= 0x24;
                    compare(t, bad, bad.size(), size, wb, 0, what + " damaged");
                    compare(t, f, f.size() / 2, size, wb, 0, what + " cut");
                    compare(t, f, f.size(), size, wb == -15 ? 15 : -15, 0, what + " (wrong window bits)");
                    streams++;
                }
    // what the game passes: version "1.2.5", 0x70
    for (const char* v : {"1.2.5", "2.0", ""}) {
        auto* s = (ZStream*)calloc(1, sizeof(ZStream));
        s32 g = (s32)(u32)t.call("inflateInit2_", {A(s), (u64)(u32)-15, A(v), sizeof(ZStream)});
        if (g == Z_OK) t.call("inflateEnd", {A(s)});
        memset(s, 0, sizeof(ZStream));
        s32 h = inflate_init2(s, -15, v, sizeof(ZStream));
        if (h == Z_OK) inflate_end(s);
        t.expect_eq(g, h, "inflateInit2_ version check");
        g = (s32)(u32)t.call("inflateInit2_", {A(s), (u64)(u32)-15, A("1.2.5"), 88});
        t.expect_eq(g, inflate_init2(s, -15, "1.2.5", 88), "inflateInit2_ size check");
        t.expect_eq((s32)(u32)t.call("inflate", {0, 0}), inflate_(nullptr, 0), "inflate(NULL)");
        free(s);
    }
    fprintf(stderr, "    %d streams\n", streams);
}

TestContext* g_t = nullptr;
u64 guest_sym(const char* s) { return g_t->sym(s); }

NATIVE_TEST("lib_zlib/live-check") {
    std::vector<u8> text(100000);
    for (size_t i = 0; i < text.size(); i++) text[i] = (u8)("AskaUncompressGzip"[i % 18] ^ (i >> 12));
    uLongf n = compressBound(text.size());
    std::vector<u8> f(n);
    compress2(f.data(), &n, text.data(), text.size(), 6);
    f.resize(n);
    g_t = &t;
    use_originals(guest_sym);
    live::Lockstep& ck = lockstep();
    u64 c0 = ck.checks(), b0 = ck.mismatches();
    ck.on = true;
    auto hi = [&](ZStream* s, int w) { return inflate_init2(s, w, "1.2.5", sizeof(ZStream)); };
    auto hf = [&](ZStream* s, int fl) { return inflate_(s, fl); };
    auto he = [&](ZStream* s) { return inflate_end(s); };
    Run a = run(hi, hf, he, f, f.size(), text.size(), 15, 0);
    Run b = run(hi, hf, he, f, f.size(), text.size(), 15, 3000);
    ck.on = false;
    use_originals(nullptr);
    t.expect_eq(std::vector<u8>(a.out.begin(), a.out.end() - 1) == text, true, "decoded");
    u64 c = ck.checks() - c0, bad = ck.mismatches() - b0;
    fprintf(stderr, "    %llu checks, %llu mismatches\n", (unsigned long long)c, (unsigned long long)bad);
    if (c < 10) t.fail("only %llu checks", (unsigned long long)c);
    if (bad) t.fail("%llu mismatches", (unsigned long long)bad);
    (void)b;
}

}  // namespace
}  // namespace soa::native::lib_zlib
