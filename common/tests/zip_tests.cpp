// Unit tests of soa/zip.h (build/common/soa_zip_tests): synthetic archives written here, then read
// back: stored and deflated entries, an archive nested in another (an app bundle's APK) read in place,
// byte ranges, CRC checks, ZIP64 offsets past 4 GiB (a sparse file), concurrent readers.
#include <soa/zip.h>
#include <zlib.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <thread>
#include <vector>
#include <sys/stat.h>
#include <unistd.h>

namespace {
int g_failures = 0;
void check(bool ok, const std::string& what) {
    fprintf(stderr, "%s  %s\n", ok ? "ok  " : "FAIL", what.c_str());
    if (!ok) g_failures++;
}

using Bytes = std::vector<uint8_t>;
void put16(Bytes& b, uint32_t v) { b.push_back(v & 0xff), b.push_back((v >> 8) & 0xff); }
void put32(Bytes& b, uint32_t v) { put16(b, v & 0xffff), put16(b, v >> 16); }
void put64(Bytes& b, uint64_t v) { put32(b, (uint32_t)v), put32(b, (uint32_t)(v >> 32)); }
void append(Bytes& b, const void* p, size_t n) { b.insert(b.end(), (const uint8_t*)p, (const uint8_t*)p + n); }
void append(Bytes& b, const std::string& s) { append(b, s.data(), s.size()); }

Bytes deflate_raw(const Bytes& in) {
    z_stream zs{};
    deflateInit2(&zs, 9, Z_DEFLATED, -MAX_WBITS, 8, Z_DEFAULT_STRATEGY);
    Bytes out(deflateBound(&zs, in.size()) + 16);
    zs.next_in = (Bytef*)in.data();
    zs.avail_in = (uInt)in.size();
    zs.next_out = out.data();
    zs.avail_out = (uInt)out.size();
    deflate(&zs, Z_FINISH);
    out.resize(zs.total_out);
    deflateEnd(&zs);
    return out;
}

struct Member {
    std::string name;
    Bytes data;
    bool deflate = false;
};
// A plain zip (no ZIP64) of the members, in order.
Bytes make_zip(const std::vector<Member>& ms) {
    Bytes z, cd;
    for (auto& m : ms) {
        Bytes body = m.deflate ? deflate_raw(m.data) : m.data;
        uint32_t crc = (uint32_t)crc32(0, m.data.data(), (uInt)m.data.size());
        uint32_t at = (uint32_t)z.size();
        put32(z, 0x04034b50), put16(z, 20), put16(z, 0), put16(z, m.deflate ? 8 : 0), put16(z, 0), put16(z, 0);
        put32(z, crc), put32(z, (uint32_t)body.size()), put32(z, (uint32_t)m.data.size());
        put16(z, (uint32_t)m.name.size()), put16(z, 4);
        append(z, m.name);
        put16(z, 0xcafe), put16(z, 0);  // an (empty) extra field: the data starts after it
        append(z, body.data(), body.size());
        put32(cd, 0x02014b50), put16(cd, 20), put16(cd, 20), put16(cd, 0), put16(cd, m.deflate ? 8 : 0), put16(cd, 0), put16(cd, 0);
        put32(cd, crc), put32(cd, (uint32_t)body.size()), put32(cd, (uint32_t)m.data.size());
        put16(cd, (uint32_t)m.name.size()), put16(cd, 0), put16(cd, 0), put16(cd, 0), put16(cd, 0), put32(cd, 0), put32(cd, at);
        append(cd, m.name);
    }
    uint32_t cd_off = (uint32_t)z.size();
    append(z, cd.data(), cd.size());
    put32(z, 0x06054b50), put16(z, 0), put16(z, 0), put16(z, (uint32_t)ms.size()), put16(z, (uint32_t)ms.size());
    put32(z, (uint32_t)cd.size()), put32(z, cd_off), put16(z, 0);
    return z;
}

std::string tmp_dir() {
    const char* t = getenv("TMPDIR");
    std::string d = std::string(t && *t ? t : "/tmp") + "/soa_zip_tests." + std::to_string(getpid());
    mkdir(d.c_str(), 0755);
    return d;
}
bool write_file(const std::string& path, const Bytes& b) {
    FILE* f = fopen(path.c_str(), "wb");
    if (!f) return false;
    bool ok = fwrite(b.data(), 1, b.size(), f) == b.size();
    return fclose(f) == 0 && ok;
}
Bytes pread_file(const std::string& path, uint64_t off, size_t n) {
    Bytes b(n);
    FILE* f = fopen(path.c_str(), "rb");
    if (!f) return {};
    bool ok = fseeko(f, (off_t)off, SEEK_SET) == 0 && fread(b.data(), 1, n, f) == n;
    fclose(f);
    return ok ? b : Bytes{};
}
Bytes pattern(size_t n, uint32_t seed) {
    Bytes b(n);
    for (size_t i = 0; i < n; i++) b[i] = (uint8_t)((seed * 2654435761u + i * 7 + (i >> 9)) & 0xff);
    return b;
}
Bytes text(const std::string& s) { return Bytes(s.begin(), s.end()); }

// ---- an app bundle: stored APKs (zips) and a deflated one, the APK's entries stored and deflated --------
void nested_tests(const std::string& dir) {
    Bytes a = text("hello from a stored asset");
    Bytes big = pattern(300000, 1);
    Bytes apk = make_zip({{"assets/a.txt", a}, {"assets/big.bin", big, true}, {"lib/arm64-v8a/libSOA.so", pattern(5000, 2), true}});
    Bytes apk2 = make_zip({{"assets/other.txt", text("second apk")}});
    std::string bundle = dir + "/bundle.zip";
    check(write_file(bundle, make_zip({{"manifest.json", text("{}"), true},
                                     {"base.apk", apk},
                                     {"split.apk", apk2},
                                     {"packed.apk", apk2, true}})),
          "write the synthetic bundle");

    soa::ZipArchive outer;
    check(outer.open(bundle), "open the bundle");
    check(outer.entries().size() == 4, "bundle: 4 entries");
    const auto* m = outer.find("manifest.json");
    check(m && m->method == 8 && !outer.stored_data(*m), "a deflated entry has no stored_data");
    std::vector<uint8_t> out;
    check(m && outer.extract(*m, out) && out == text("{}"), "extract a deflated entry");

    soa::ZipArchive inner;
    check(inner.open_member(outer, "base.apk"), "open_member: the stored base.apk, in place");
    check(inner.path() == bundle, "a nested archive's path() is the outer file");
    const auto* be = outer.find("base.apk");
    check(be && inner.base_offset() == outer.data_offset_of(*be) && inner.size() == apk.size(),
          "the nested archive spans the member's bytes in the outer file");
    const auto* ea = inner.find("assets/a.txt");
    check(ea && ea->method == 0 && ea->size == a.size() && ea->crc == (uint32_t)crc32(0, a.data(), (uInt)a.size()),
          "nested stored entry: method, size, CRC");
    check(ea && inner.stored_data(*ea) && memcmp(inner.stored_data(*ea), a.data(), a.size()) == 0, "nested stored_data in place");
    check(ea && pread_file(bundle, inner.data_offset_of(*ea), a.size()) == a,
          "data_offset_of is an offset in the outer file (pread / ffmpeg subfile)");
    const auto* eb = inner.find("assets/big.bin");
    check(eb && eb->method == 8 && inner.extract(*eb, out) && out == big, "nested deflated entry extracts");
    char buf[64];
    check(ea && inner.read(*ea, 6, buf, 4) == 4 && memcmp(buf, "from", 4) == 0, "read(): a range of a stored entry");
    check(eb && inner.read(*eb, 200000, buf, 64) == 64 && memcmp(buf, big.data() + 200000, 64) == 0,
          "read(): a range of a deflated entry");
    check(ea && inner.read(*ea, a.size() - 2, buf, 64) == 2, "read(): clipped at the end");
    check(ea && inner.read(*ea, a.size() + 5, buf, 4) == 0, "read(): past the end reads nothing");

    soa::ZipArchive second;
    check(second.open_member(outer, "split.apk") && second.find("assets/other.txt"), "a second nested APK");
    soa::ZipArchive packed;
    check(!packed.open_member(outer, "packed.apk"), "open_member refuses a deflated member (extract it instead)");
    check(!packed.open_member(outer, "missing.apk"), "open_member: no such member");

    // the same through open(path, offset, length)
    soa::ZipArchive ranged;
    check(be && ranged.open(bundle, outer.data_offset_of(*be), be->size) && ranged.find("assets/big.bin"),
          "open(path, offset, length)");
    check(!ranged.open(bundle, 1u << 30, 10), "open(): a range past the end fails");

    // a corrupted deflated entry: the CRC check catches it
    Bytes bad = apk;
    soa::ZipArchive tmp;
    std::string apk_path = dir + "/bad.apk";
    write_file(apk_path, apk);
    tmp.open(apk_path);
    uint64_t at = tmp.data_offset_of(*tmp.find("assets/big.bin"));
    tmp.open(dir + "/test.bundle");  // (unmaps bad.apk before it is rewritten)
    bad[at + 100] ^= 0x55;
    write_file(apk_path, bad);
    soa::ZipArchive corrupt;
    check(corrupt.open(apk_path), "open the corrupted APK");
    const auto* cb = corrupt.find("assets/big.bin");
    check(cb && !corrupt.extract(*cb, out), "extract fails on a corrupted deflated entry (inflate or CRC)");

    check(!soa::ZipArchive().open(dir + "/nonexistent.zip"), "open: a missing file fails");
    write_file(dir + "/notzip.bin", text("this is not a zip file at all, just some bytes"));
    check(!soa::ZipArchive().open(dir + "/notzip.bin"), "open: not a zip fails");
}

// ---- many threads read one fresh archive (data offsets resolve concurrently) --------------------
void concurrency_tests(const std::string& dir) {
    std::vector<Member> ms;
    std::vector<Bytes> want;
    for (int i = 0; i < 64; i++) {
        want.push_back(pattern(1000 + i * 997, (uint32_t)i));
        ms.push_back({"assets/f" + std::to_string(i), want.back(), (i % 2) == 1});
    }
    std::string path = dir + "/many.zip";
    write_file(path, make_zip(ms));
    for (int round = 0; round < 5; round++) {
        soa::ZipArchive z;
        if (!z.open(path)) {
            check(false, "open many.zip");
            return;
        }
        std::atomic<int> bad{0};
        std::vector<std::thread> ts;
        for (int t = 0; t < 8; t++) {
            ts.emplace_back([&, t] {
                std::vector<uint8_t> out;
                for (int k = 0; k < 64; k++) {
                    int i = (k * 7 + t * 13) % 64;
                    const auto* e = z.find("assets/f" + std::to_string(i));
                    if (!e || !z.extract(*e, out) || out != want[i]) bad++;
                    uint8_t b[16];
                    if (!e || z.read(*e, 500, b, 16) != 16 || memcmp(b, want[i].data() + 500, 16) != 0) bad++;
                }
            });
        }
        for (auto& th : ts) th.join();
        if (bad) {
            check(false, "concurrent reads: " + std::to_string(bad.load()) + " wrong");
            return;
        }
    }
    check(true, "8 threads x 5 fresh archives: every extract and range read right");
}

// ---- ZIP64: an entry whose local header is past 4 GiB (a sparse file; the hole reads as zeros) ----
void zip64_tests(const std::string& dir) {
#ifdef _WIN32
    // (NTFS files aren't sparse unless asked: the gap would be 4 GiB written to disk)
    fprintf(stderr, "skip  zip64: no sparse files here (run on Linux)\n");
    return;
#endif
    std::string path = dir + "/zip64.zip";
    const uint64_t far = (4ull << 30) + 12345;  // past 4 GiB
    Bytes a = text("near"), b = text("far away, past four gigabytes");
    FILE* f = fopen(path.c_str(), "wb");
    if (!f) {
        check(false, "zip64: create the file");
        return;
    }
    Bytes head;
    auto local = [](Bytes& z, const std::string& name, const Bytes& d) {
        put32(z, 0x04034b50), put16(z, 45), put16(z, 0), put16(z, 0), put16(z, 0), put16(z, 0);
        put32(z, (uint32_t)crc32(0, d.data(), (uInt)d.size())), put32(z, (uint32_t)d.size()), put32(z, (uint32_t)d.size());
        put16(z, (uint32_t)name.size()), put16(z, 0);
        append(z, name);
        append(z, d.data(), d.size());
    };
    local(head, "a.txt", a);
    Bytes tail;
    local(tail, "far/b.txt", b);
    uint64_t cd_off = far + tail.size();
    Bytes cd;
    auto central = [&](const std::string& name, const Bytes& d, uint64_t at) {
        bool z64 = at >= 0xffffffffull;
        put32(cd, 0x02014b50), put16(cd, 45), put16(cd, 45), put16(cd, 0), put16(cd, 0), put16(cd, 0), put16(cd, 0);
        put32(cd, (uint32_t)crc32(0, d.data(), (uInt)d.size())), put32(cd, (uint32_t)d.size()), put32(cd, (uint32_t)d.size());
        put16(cd, (uint32_t)name.size()), put16(cd, z64 ? 12 : 0), put16(cd, 0), put16(cd, 0), put16(cd, 0), put32(cd, 0);
        put32(cd, z64 ? 0xffffffffu : (uint32_t)at);
        append(cd, name);
        if (z64) put16(cd, 1), put16(cd, 8), put64(cd, at);  // the ZIP64 extra field: the offset
    };
    central("a.txt", a, 0);
    central("far/b.txt", b, far);
    uint64_t z64_eocd = cd_off + cd.size();
    Bytes end;
    put32(end, 0x06064b50), put64(end, 44), put16(end, 45), put16(end, 45), put32(end, 0), put32(end, 0);
    put64(end, 2), put64(end, 2), put64(end, cd.size()), put64(end, cd_off);
    put32(end, 0x07064b50), put32(end, 0), put64(end, z64_eocd), put32(end, 1);
    put32(end, 0x06054b50), put16(end, 0), put16(end, 0), put16(end, 0xffff), put16(end, 0xffff);
    put32(end, 0xffffffffu), put32(end, 0xffffffffu), put16(end, 0);
    bool ok = fwrite(head.data(), 1, head.size(), f) == head.size() && fseeko(f, (off_t)far, SEEK_SET) == 0 &&
              fwrite(tail.data(), 1, tail.size(), f) == tail.size() && fwrite(cd.data(), 1, cd.size(), f) == cd.size() &&
              fwrite(end.data(), 1, end.size(), f) == end.size();
    ok = fclose(f) == 0 && ok;
    bool sparse = false;
#ifndef _WIN32
    struct stat st;
    sparse = stat(path.c_str(), &st) == 0 && (uint64_t)st.st_blocks * 512 <= (64u << 20);
#endif
    if (!ok || !sparse) {
        fprintf(stderr, "skip  zip64: no sparse 4 GiB file here\n");
        unlink(path.c_str());
        return;
    }
    {
        soa::ZipArchive z;
        check(z.open(path), "zip64: open (ZIP64 end records)");
        const auto* e = z.find("far/b.txt");
        check(e && e->local_header == far, "zip64: a local header offset past 4 GiB");
        check(e && z.data_offset_of(*e) > (4ull << 30) && z.stored_data(*e) && memcmp(z.stored_data(*e), b.data(), b.size()) == 0,
              "zip64: the entry's bytes in place");
        std::vector<uint8_t> out;
        check(e && z.extract(*e, out) && out == b, "zip64: extract");
        const auto* n = z.find("a.txt");
        check(n && z.extract(*n, out) && out == a, "zip64: the near entry too");
    }
    unlink(path.c_str());
}

}  // namespace

int main() {
    std::string dir = tmp_dir();
    nested_tests(dir);
    concurrency_tests(dir);
    zip64_tests(dir);
    for (const char* f : {"test.bundle", "bad.apk", "many.zip", "notzip.bin"}) unlink((dir + "/" + f).c_str());
    rmdir(dir.c_str());
    fprintf(stderr, "%s (%d failure%s)\n", g_failures ? "FAIL" : "PASS", g_failures, g_failures == 1 ? "" : "s");
    return g_failures ? 1 : 0;
}
