// Differential tests of the `hash` natives against the 3.7.0 guest (--selftest hash/): the guest
// functions run as ARM64 code (natives aren't installed in --selftest), the natives on the same
// inputs; random inputs plus real ones (the 3.7.0 download's paths and file bytes).
#include <algorithm>
#include <cstddef>
#include <cstring>
#include <memory>
#include <string>
#include <vector>

#include <soa/file_tree.h>
#include <soa/install.h>

#include "core/loader.h"
#include "core/paths.h"
#include "native/common/test.h"
#include "native/common/test_assets.h"
#include "native/hash/hash_layout.h"

namespace soa::native::hash {

const u32* chash32_table();
const u16* crc16_table();
const u32* crc32_table();

namespace {

// Real inputs: relative paths of the 3.7.0 download (the names the game hashes are paths and ids
// like these), sorted, the first n; and the bytes of a few of its files. The download is the zip
// work/SOA-3.7.0-canonical-data.zip, read in place (native/common/test_assets.h).
std::vector<std::string> real_names(size_t n) {
    static const std::vector<std::string> all = [] {  // (a folder's files() walks the disk: once)
        const soa::FileTree* tree = soa::test_assets::download_tree();
        return tree ? tree->files() : std::vector<std::string>{};
    }();
    std::vector<std::string> out(all.begin(), all.begin() + (std::ptrdiff_t)std::min(n, all.size()));
    if (out.empty()) {
        if (auto* t = current_test_context())
            t->fail("no files in the 3.7.0 download (%s)", soa::install::kRepoDownloadZip);
    }
    return out;
}
std::vector<std::vector<u8>> real_files(size_t n, size_t max_bytes) {
    std::vector<std::vector<u8>> out;
    const soa::FileTree* tree = soa::test_assets::download_tree();
    for (auto& name : real_names(200)) {
        if (out.size() >= n) break;
        std::vector<u8> b;
        if (!tree->read(name, b)) continue;
        if (b.size() > max_bytes) b.resize(max_bytes);
        if (!b.empty()) out.push_back(std::move(b));
    }
    return out;
}

std::string rand_string(TestContext& t, size_t maxlen) {
    size_t n = (size_t)t.rand_int(0, (int)maxlen);
    std::string s(n, ' ');
    for (auto& c : s) c = (char)t.rand_int(1, 255);
    return s;
}

// A guest libc++ string (read-only use: short or long form over `s`).
GuestString guest_string(const std::string& s) {
    GuestString g{};
    if (s.size() < 23) {
        g.r.s.head.size = (u8)(s.size() << 1);
        std::memcpy(g.r.s.data, s.data(), s.size());
    } else {
        g.r.l.cap = (s.size() + 16) | 1;
        g.r.l.size = s.size();
        g.r.l.data = const_cast<char*>(s.data());
    }
    return g;
}

const u8* guest_at(u64 vaddr) { return (const u8*)(main_lib()->base + vaddr); }

}  // namespace

NATIVE_TEST("hash/tables") {
    // the CRC tables the natives compute are the guest's (and settle CRC-16's polynomial: 0x8408)
    t.expect_eq(std::memcmp(guest_at(0x2863e48), chash32_table(), 1024), 0, "CHash32 table");
    t.expect_eq(std::memcmp(guest_at(0x2872808), crc16_table(), 512), 0, "CRC-16 table");
    t.expect_eq(std::memcmp(guest_at(0x2872a08), crc32_table(), 1024), 0, "CRC-32 table");
}

NATIVE_TEST("hash/chash32") {
    std::vector<std::string> in = real_names(3000);
    in.insert(in.end(), {"", "a", "role_cp0303_b04a_6131", std::string(300, 'x')});
    for (int i = 0; i < 2000; i++) in.push_back(rand_string(t, i < 1900 ? 40 : 600));
    int bad = 0;
    for (auto& s : in) {
        alignas(16) CHash32 g{}, n{};
        std::memset(&g, 0xa5, sizeof g), std::memset(&n, 0xa5, sizeof n);
        t.call("_ZN9Framework7CHash32C2EPKc", {(u64)&g, (u64)s.c_str()});
        n.Ctor(s.c_str());
        bad += std::memcmp(&g, &n, sizeof g) != 0;
        // (char const*, n) with a length past an embedded NUL-free prefix
        u64 len = s.empty() ? 0 : (u64)t.rand_int(0, (int)s.size());
        t.call("_ZN9Framework7CHash32C1EPKcm", {(u64)&g, (u64)s.data(), len});
        n.Ctor(s.data(), len);
        bad += std::memcmp(&g, &n, sizeof g) != 0;
        GuestString gs = guest_string(s);
        t.call("_ZN9Framework7CHash32C1ERKNSt6__ndk112basic_stringIcNS1_11char_traitsIcEENS_13CSTLAllocatorIcNS_22CSTLStringAllocatorInfEEEEE", {(u64)&g, (u64)&gs});
        n.Ctor(gs);
        bad += std::memcmp(&g, &n, sizeof g) != 0;
        u64 r = t.call("_ZN9Framework7CHash32aSEPKc", {(u64)&g, (u64)s.c_str()});
        bad += r != (u64)&g;
        bad += n.Assign(s.c_str()) != &n;
        bad += std::memcmp(&g, &n, sizeof g) != 0;
        g.m_hash = n.m_hash = (u32)t.rand_u64();
        t.call("_ZN9Framework7CHash32aSERKNSt6__ndk112basic_stringIcNS1_11char_traitsIcEENS_13CSTLAllocatorIcNS_22CSTLStringAllocatorInfEEEEE", {(u64)&g, (u64)&gs});
        n.Assign(gs);
        bad += std::memcmp(&g, &n, sizeof g) != 0;
        // comparisons against the string and against a nearby value
        bad += (bool)(u8)t.call("_ZNK9Framework7CHash32ltEPKc", {(u64)&g, (u64)"abc"}) != n.Lt("abc");
        bad += (bool)(u8)t.call("_ZNK9Framework7CHash32gtEPKc", {(u64)&g, (u64)s.c_str()}) != n.Gt(s.c_str());
    }
    t.expect_eq(bad, 0, "CHash32 constructors / assignment");
    // null pointers: the constructors hash nothing
    alignas(16) CHash32 g{}, n{};
    t.call("_ZN9Framework7CHash32C2EPKc", {(u64)&g, 0});
    n.Ctor((const char*)nullptr);
    t.expect_eq(std::memcmp(&g, &n, sizeof g), 0, "CHash32(nullptr)");
    t.call("_ZN9Framework7CHash32C1EPKcm", {(u64)&g, 0, 5});
    n.Ctor((const char*)nullptr, 5);
    t.expect_eq(std::memcmp(&g, &n, sizeof g), 0, "CHash32(nullptr, 5)");
    t.call("_ZN9Framework7CHash32C2Ev", {(u64)&g});
    n.Ctor();
    t.expect_eq(std::memcmp(&g, &n, sizeof g), 0, "CHash32()");
}

NATIVE_TEST("hash/chash32-numbers") {
    int bad = 0;
    std::vector<u32> vals = {0, 1, 9, 10, 4294967295u, 2147483648u, 100001};
    for (int i = 0; i < 3000; i++) vals.push_back(i < 1000 ? (u32)i : (u32)t.rand_u64() >> t.rand_int(0, 31));
    for (u32 v : vals) {
        alignas(16) CHash32 g{}, n{};
        t.call("_ZN9Framework7CHash32C1Ej", {(u64)&g, v});
        n.Ctor(v);
        bad += std::memcmp(&g, &n, sizeof g) != 0;
        t.call("_ZN9Framework7CHash32C2Ei", {(u64)&g, (u64)(s64)(s32)v});
        n.Ctor((s32)v);
        bad += std::memcmp(&g, &n, sizeof g) != 0;
        // the accessors and comparisons
        CHash32 o = n;
        o.m_hash = t.rand_int(0, 3) ? (u32)t.rand_u64() : n.m_hash + (u32)t.rand_int(-1, 1);
        u32 w = o.m_hash;
        auto b = [&](const char* sym, u64 arg) { return (bool)(u8)t.call(sym, {(u64)&g, arg}); };
        bad += (u32)t.call("_ZNK9Framework7CHash323GetEv", {(u64)&g}) != n.Get();
        bad += (u32)t.call("_ZNK9Framework7CHash32cvjEv", {(u64)&g}) != n.ToU32();
        bad += b("_ZNK9Framework7CHash32eqERKS0_", (u64)&o) != n.Eq(o);
        bad += b("_ZNK9Framework7CHash32eqERKj", (u64)&w) != n.Eq(w);
        bad += b("_ZNK9Framework7CHash32neERKS0_", (u64)&o) != n.Ne(o);
        bad += b("_ZNK9Framework7CHash32neERKj", (u64)&w) != n.Ne(w);
        bad += b("_ZNK9Framework7CHash32ltERKS0_", (u64)&o) != n.Lt(o);
        bad += b("_ZNK9Framework7CHash32gtERKS0_", (u64)&o) != n.Gt(o);
        bad += b("_ZNK9Framework7CHash32ltERKj", (u64)&w) != n.Lt(w);
        bad += b("_ZNK9Framework7CHash32gtERKj", (u64)&w) != n.Gt(w);
    }
    t.expect_eq(bad, 0, "CHash32 numbers / comparisons");
}

NATIVE_TEST("hash/crc") {
    auto files = real_files(20, 1 << 16);
    std::vector<std::vector<u8>> in(files.begin(), files.end());
    for (int len : {0, 1, 2, 3, 7, 8, 255, 256, 4096}) in.push_back(t.rand_bytes((size_t)len));
    for (int i = 0; i < 300; i++) in.push_back(t.rand_bytes((size_t)t.rand_int(0, 2000)));
    int bad = 0;
    for (auto& b : in) {
        u16 g16 = 0x5a5a, n16 = 0xa5a5;
        u32 g32 = 0x5a5a5a5a, n32 = 0xa5a5a5a5;
        bad += t.call("_ZN4Aska4Hash3CRCEPKhmPt", {(u64)b.data(), b.size(), (u64)&g16}) != Hash::CRC(b.data(), b.size(), &n16);
        bad += g16 != n16;
        bad += t.call("_ZN4Aska4Hash3CRCEPKhmPj", {(u64)b.data(), b.size(), (u64)&g32}) != Hash::CRC(b.data(), b.size(), &n32);
        bad += g32 != n32;
    }
    u16 g16 = 1, n16 = 2;
    bad += t.call("_ZN4Aska4Hash3CRCEPKhmPt", {0, 5, (u64)&g16}) != Hash::CRC(nullptr, 5, &n16) || g16 != n16;
    t.expect_eq(bad, 0, "CRC-16 / CRC-32");
}

NATIVE_TEST("hash/sha1") {
    auto files = real_files(10, 1 << 14);
    std::vector<std::vector<u8>> in(files.begin(), files.end());
    for (int len = 0; len <= 200; len++) in.push_back(t.rand_bytes((size_t)len));
    for (int i = 0; i < 100; i++) in.push_back(t.rand_bytes((size_t)t.rand_int(0, 5000)));
    int bad = 0, k = 0;
    for (auto& b : in) {
        u64 total = (b.size() + 0x41) & ~(u64)0x3f;
        // the work buffer: big enough, exactly the minimum, one short; out: 20 bytes or 19
        u64 worklen = k % 7 == 3 ? total + 0x3f : k % 5 == 1 ? total + 0x40 : total + 0x100;
        u64 outlen = k % 31 == 7 ? 19 : 20;
        k++;
        std::vector<u8> gw(worklen + 64, 0xcc), nw(worklen + 64, 0xcc), go(32, 0xdd), no(32, 0xdd);
        u64 gr = t.call("_ZN4Aska4Hash4SHA1EPKcmPcmS3_m", {(u64)b.data(), b.size(), (u64)go.data(), outlen, (u64)gw.data(), worklen});
        u64 nr = Hash::SHA1((const char*)b.data(), b.size(), (char*)no.data(), outlen, (char*)nw.data(), worklen);
        bad += gr != nr || go != no || gw != nw;
    }
    t.expect_eq(bad, 0, "SHA1 (result, digest, work buffer)");
}

NATIVE_TEST("hash/spooky-short") {
    int bad = 0;
    for (int len = 0; len < 400; len++) {
        // (unaligned starts too: the guest reads unaligned)
        auto b = t.rand_bytes((size_t)len + 8);
        const u8* p = b.data() + (len % 8);
        u64 seeds[2] = {t.rand_u64(), len % 3 ? t.rand_u64() : 0};
        u64 g1 = seeds[0], g2 = seeds[1], n1 = seeds[0], n2 = seeds[1];
        if (len < 192) {
            t.call("_ZN4Aska6detail12SpookyHashV25ShortEPKvmPmS4_", {(u64)p, (u64)len, (u64)&g1, (u64)&g2});
            SpookyHashV2::Short(p, (u64)len, &n1, &n2);
            if ((g1 != n1 || g2 != n2) && !bad++) t.fail("Short len %d: guest %016llx %016llx native %016llx %016llx", len, (unsigned long long)g1, (unsigned long long)g2, (unsigned long long)n1, (unsigned long long)n2);
            g1 = n1 = seeds[0], g2 = n2 = seeds[1];
        }
        t.call("_ZN4Aska6detail12SpookyHashV27Hash128EPKvmPmS4_", {(u64)p, (u64)len, (u64)&g1, (u64)&g2});
        SpookyHashV2::Hash128(p, (u64)len, &n1, &n2);
        if ((g1 != n1 || g2 != n2) && !bad++) t.fail("Hash128 len %d: guest %016llx %016llx native %016llx %016llx", len, (unsigned long long)g1, (unsigned long long)g2, (unsigned long long)n1, (unsigned long long)n2);
    }
    for (auto& f : real_files(10, 1 << 15)) {
        u64 g1 = 0, g2 = 0, n1 = 0, n2 = 0;
        t.call("_ZN4Aska6detail12SpookyHashV27Hash128EPKvmPmS4_", {(u64)f.data(), f.size(), (u64)&g1, (u64)&g2});
        SpookyHashV2::Hash128(f.data(), f.size(), &n1, &n2);
        bad += g1 != n1 || g2 != n2;
    }
    t.expect_eq(bad, 0, "SpookyHashV2::Short / Hash128");
}

NATIVE_TEST("hash/spooky-stream") {
    // Init, Updates of sizes that straddle the 192-byte buffer and the 96-byte block, Final;
    // the whole object compared after each step
    int bad = 0;
    for (int round = 0; round < 300; round++) {
        alignas(16) SpookyHashV2 g, n;
        std::memset(&g, 0x33, sizeof g);
        std::memset(&n, 0x33, sizeof n);
        u64 s1 = t.rand_u64(), s2 = t.rand_u64();
        t.call("_ZN4Aska6detail12SpookyHashV24InitEmm", {(u64)&g, s1, s2});
        n.Init(s1, s2);
        bad += std::memcmp(&g, &n, sizeof g) != 0;
        int steps = t.rand_int(0, 8);
        for (int k = 0; k < steps; k++) {
            int kind = t.rand_int(0, 3);
            size_t len = kind == 0 ? (size_t)t.rand_int(0, 20) : kind == 1 ? (size_t)t.rand_int(80, 200) : kind == 2 ? (size_t)t.rand_int(180, 600) : (size_t)t.rand_int(0, 3000);
            auto b = t.rand_bytes(len + 8);
            const u8* p = b.data() + t.rand_int(0, 7);
            t.call("_ZN4Aska6detail12SpookyHashV26UpdateEPKvm", {(u64)&g, (u64)p, len});
            n.Update(p, len);
            bad += std::memcmp(&g, &n, sizeof g) != 0;
        }
        u64 g1 = 0, g2 = 0, n1 = 0, n2 = 0;
        t.call("_ZN4Aska6detail12SpookyHashV25FinalEPmS2_", {(u64)&g, (u64)&g1, (u64)&g2});
        n.Final(&n1, &n2);
        bad += g1 != n1 || g2 != n2 || std::memcmp(&g, &n, sizeof g) != 0;
    }
    t.expect_eq(bad, 0, "SpookyHashV2 Init / Update / Final");
}

NATIVE_TEST("hash/utf8") {
    std::vector<std::string> in = real_names(500);
    in.insert(in.end(), {"", "abc", "\xe3\x81\x82\xe3\x81\x84", "\xf0\x9f\x98\x80x", "\xc3\xa9t\xc3\xa9", "\x80\xbf\xff\xfe", "a\xe3\x81", "\xf0\x9f"});
    for (int i = 0; i < 1500; i++) {
        // random mixes of valid sequences, stray continuation bytes and truncations
        std::string s;
        int n = t.rand_int(0, 30);
        for (int k = 0; k < n; k++) {
            switch (t.rand_int(0, 5)) {
            case 0: s += (char)t.rand_int(1, 0x7f); break;
            case 1: s += (char)t.rand_int(0xc2, 0xdf), s += (char)t.rand_int(0x80, 0xbf); break;
            case 2: s += (char)t.rand_int(0xe0, 0xef), s += (char)t.rand_int(0x80, 0xbf), s += (char)t.rand_int(0x80, 0xbf); break;
            case 3: s += (char)t.rand_int(0xf0, 0xf4), s += (char)t.rand_int(0x80, 0xbf), s += (char)t.rand_int(0x80, 0xbf), s += (char)t.rand_int(0x80, 0xbf); break;
            default: s += (char)t.rand_int(0x80, 0xff); break;
            }
        }
        in.push_back(s);
    }
    int bad = 0;
    for (auto& s : in) {
        // (4 bytes of slack: a truncated 4-byte sequence reads past the NUL in both)
        std::string src = s + std::string(4, '\0');
        u64 n = (u64)t.rand_int(0, 40);
        std::vector<char32_t> g4(64, 0x77), n4(64, 0x77);
        std::vector<char16_t> g2(64, 0x77), n2(64, 0x77);
        bad += t.call("_ZN4Aska4Utf86ToUcs4EPDiPKcm", {(u64)g4.data(), (u64)src.data(), n}) != Utf8::ToUcs4(n4.data(), src.data(), n) || g4 != n4;
        bad += t.call("_ZN4Aska4Utf86ToUcs2EPDsPKcm", {(u64)g2.data(), (u64)src.data(), n}) != Utf8::ToUcs2(n2.data(), src.data(), n) || g2 != n2;
    }
    bad += t.call("_ZN4Aska4Utf86ToUcs4EPDiPKcm", {0, (u64)"a", 4}) != Utf8::ToUcs4(nullptr, "a", 4);
    for (int c = 0; c < 256; c++) bad += t.call("_ZN4Aska4Utf814GetByteSizeAt_Eh", {(u64)c}) != Utf8::GetByteSizeAt_((u8)c);
    t.expect_eq(bad, 0, "Utf8");
}

}  // namespace soa::native::hash
