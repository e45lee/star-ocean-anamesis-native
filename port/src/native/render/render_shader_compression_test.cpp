// Differential tests of the shader-cache compressor natives (render_shader_compression.cpp) against the
// 3.7.0 guest: the tree members word for word, and CompressLZwordDic's output byte for byte on edge-case
// inputs and on every entry of the shipped shader cache (the inputs the boot-time recompression sees).
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <memory>
#include <string>
#include <vector>

#include "core/paths.h"
#include "native/common/test.h"
#include "native/common/test_assets.h"
#include "native/render/render_layout.h"

namespace soa::native::render {
namespace {

constexpr const char* kCtor = "_ZN4Aska20ShaderComprssionTreeC2Ev";
constexpr const char* kInsert = "_ZN4Aska20ShaderComprssionTree10InsertNodeEii";
constexpr const char* kDelete = "_ZN4Aska20ShaderComprssionTree10DeleteNodeEi";
constexpr const char* kCompress = "_ZN4Aska17ShaderCompression17CompressLZwordDicEPviS1_Ph";
constexpr const char* kDecompress = "_ZN4Aska17ShaderCompression19DecompressLZwordDicEPtS1_Ph";

// The first differing 32-bit word of two trees, or -1.
long tree_diff(const ShaderComprssionTree& a, const ShaderComprssionTree& b) {
    const u32* x = reinterpret_cast<const u32*>(&a);
    const u32* y = reinterpret_cast<const u32*>(&b);
    for (size_t i = 0; i < sizeof a / 4; i++)
        if (x[i] != y[i]) return (long)i * 4;
    return -1;
}

// One CompressLZwordDic input compared: the guest's and the native's size and bytes. `src` must have
// slack after `size` (both read up to two bytes past it).
bool compare_compress(TestContext& t, const u8* src, s32 size, const u8* dic, const char* what) {
    size_t cap = (size_t)std::max(size, 0) * 2 + 0x100;
    std::vector<u8> g(cap, 0xcd), n(cap, 0xcd);
    s32 gs = (s32)t.call(kCompress, {(u64)src, (u64)(u32)size, (u64)g.data(), (u64)dic});
    s32 ns = ShaderCompression::CompressLZwordDic(const_cast<u8*>(src), size, n.data(), const_cast<u8*>(dic));
    if (gs != ns) {
        t.fail("%s (size %d): compressed size native %d, guest %d", what, size, ns, gs);
        return false;
    }
    if (std::memcmp(g.data(), n.data(), cap) != 0) {  // also the bytes past the end: untouched in both
        size_t k = 0;
        while (g[k] == n[k]) k++;
        t.fail("%s (size %d): byte %zu of %d differs: native %02x guest %02x", what, size, k, gs, n[k], g[k]);
        return false;
    }
    return true;
}

}  // namespace

// The tree: two private trees, one driven by the guest's members and one by the natives, through the
// call sequence of a compression (every window position inserted, the oldest deleted before a new one
// goes in, both maxLen 0x11 and the maxLen < 2 path) over words with few distinct values (long matches,
// full-length replacements, deletions of nodes with two children); the trees compared word for word
// after every call.
NATIVE_TEST("render/shader-compression-tree") {
    auto gmem = std::make_unique<ShaderComprssionTree>();
    auto nmem = std::make_unique<ShaderComprssionTree>();
    ShaderComprssionTree& g = *gmem;
    ShaderComprssionTree& n = *nmem;
    std::memset(&g, 0x5a, sizeof g);
    std::memset(&n, 0x5a, sizeof n);
    t.call(kCtor, {(u64)&g});
    n.Ctor();
    t.expect_eq(tree_diff(g, n), -1L, "Ctor");
    for (int round = 0; round < 3; round++) {
        t.call(kCtor, {(u64)&g});
        n.Ctor();
        const int alphabet = round == 0 ? 2 : round == 1 ? 5 : 0x10000;
        for (int i = 0; i < 0x1011; i++) g.m_text[i] = n.m_text[i] = t.rand_int(0, alphabet - 1);
        int bad = 0;
        const int kOps = 6000;  // the window wraps: positions are deleted and reused
        for (int k = 0; k < kOps && bad < 3; k++) {
            const int r = k & 0xfff;
            const int maxLen = (k % 37 == 5) ? t.rand_int(0, 1) : ShaderComprssionTree::kMaxMatch;
            // the slot's previous position leaves the window, a new word goes in (as the compressor does)
            t.call(kDelete, {(u64)&g, (u64)r});
            n.DeleteNode(r);
            if (long d = tree_diff(g, n); d >= 0) t.fail("round %d op %d: DeleteNode(%d): word +0x%lx differs", round, k, r, d), bad++;
            if (k >= 0x1000 || k % 2 == 0) {
                int w = t.rand_int(0, alphabet - 1);
                g.m_text[r] = n.m_text[r] = w;
            }
            t.call(kInsert, {(u64)&g, (u64)r, (u64)maxLen});
            n.InsertNode(r, maxLen);
            if (long d = tree_diff(g, n); d >= 0) t.fail("round %d op %d: InsertNode(%d, %d): word +0x%lx differs", round, k, r, maxLen, d), bad++;
        }
        // delete every node (nodes with two children, the predecessor walk)
        for (int p = 0; p < 0x1000 && bad < 3; p += 7) {
            t.call(kDelete, {(u64)&g, (u64)p});
            n.DeleteNode(p);
            if (long d = tree_diff(g, n); d >= 0) t.fail("round %d: DeleteNode(%d) sweep: word +0x%lx differs", round, p, d), bad++;
        }
    }
}

// CompressLZwordDic on edge-case inputs: sizes 0..0x40 (each odd size, the short-lookahead paths), a
// window's worth and more, all-equal words (the longest matches), random words (no matches), a block
// repeated from the dictionary (matches reaching into it), and a negative size.
NATIVE_TEST("render/shader-compression-edge") {
    std::vector<u8> dic(0x2000);
    for (size_t i = 0; i < dic.size(); i++) dic[i] = (u8)(i % 5 == 0 ? t.rand_int(0, 255) : "vs_3_0 ps_3_0 2.0.6534.1 "[i % 25]);
    auto run = [&](const std::vector<u8>& data, s32 size, const char* what) {
        std::vector<u8> src(data);
        src.resize(std::max<size_t>(src.size(), (size_t)std::max(size, 0)) + 0x40, 0);
        compare_compress(t, src.data(), size, dic.data(), what);
    };
    for (s32 size = 0; size <= 0x40; size++) run(t.rand_bytes((size_t)size, 3), size, "short");
    run(std::vector<u8>(0x3000, 0x41), 0x3000, "all-equal");
    run(t.rand_bytes(0x2001), 0x2001, "random");
    run(t.rand_bytes(0x6000, 2), 0x6000, "two-symbol");
    std::vector<u8> fromdic(dic.begin() + 0x100, dic.begin() + 0x900);
    run(fromdic, (s32)fromdic.size(), "dictionary text");
    std::vector<u8> mixed;
    for (int i = 0; i < 0x80; i++) {
        auto chunk = t.rand_bytes((size_t)t.rand_int(1, 60), i % 2 ? 4 : 256);
        mixed.insert(mixed.end(), chunk.begin(), chunk.end());
        mixed.insert(mixed.end(), mixed.begin(), mixed.begin() + std::min<size_t>(mixed.size(), 37));
    }
    run(mixed, (s32)mixed.size(), "mixed");
    run({}, -5, "negative size");
}

// CompressLZwordDic on every shader entry of the shipped cache, as the boot-time recompression feeds it
// (AHSLBase::CreateCompressedShaderCache: the unpacked entry after its raw head of info offset + 48 bytes,
// the section's dictionary). The entries are unpacked with the guest's DecompressLZwordDic.
NATIVE_TEST("render/shader-compression-cache") {
    std::string path = find_repo_file("work/extracted/com.square_enix.android_googleplay.StarOceanj/assets/builtin_data/Shader/AHSLDiskCacheAdd");
    std::vector<u8> d = test_assets::read_file(path);
    if (d.size() < 0x4040) {
        fprintf(stderr, "    (no shader cache: skipped)\n");
        return;
    }
    auto u16_at = [&](size_t o) { return (u32)d[o] | (u32)d[o + 1] << 8; };
    auto u32_at = [&](size_t o) { return u16_at(o) | u16_at(o + 2) << 16; };
    t.expect_eq(u32_at(0), 0x5348504bu, "KPHS");
    const u32 sections = u16_at(12);
    size_t off = 0x2020;
    int entries = 0, bad = 0;
    for (u32 sec = 0; sec < sections && off + 8 + 0x2020 <= d.size(); sec++) {
        const u32 size = u32_at(off + 4);
        const size_t h = off + 8;
        const u32 count = u16_at(h + 12);
        if (std::memcmp(&d[h], "3AHA", 4) == 0) {
            const u8* dic = &d[h + 0x20];
            size_t e = h + 0x2020;
            for (u32 i = 0; i < count && e + 12 <= d.size(); i++) {
                const u32 stored = u16_at(e + 2), unpacked = u16_at(e + 4), info = u16_at(e + 6), flags = d[e + 10];
                const u32 raw = info + 48;
                if ((flags & 3) == 3 && raw < unpacked) {
                    std::vector<u8> u(unpacked + 0x100, 0);
                    std::memcpy(u.data(), &d[e], raw);
                    t.call(kDecompress, {(u64)&d[e + raw], (u64)(u.data() + raw), (u64)dic});
                    std::string what = "cache entry " + std::to_string(entries);
                    if (!compare_compress(t, u.data() + raw, (s32)(unpacked - raw), dic, what.c_str())) bad++;
                    entries++;
                }
                if (bad >= 3) break;
                e += stored;
            }
        }
        off += (size + 3) & ~3u;
    }
    fprintf(stderr, "    %d entries compared\n", entries);
    t.expect_eq(entries > 1000, true, "the cache's compressed entries found");
}

}  // namespace soa::native::render
