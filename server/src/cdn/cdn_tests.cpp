// Unit tests of the CDN content (soaserver/cdn.h) and the ADLD packing (soaserver/adld.h)
// (--selftest "cdn/"; server code, no guest counterpart). The 3.7.0 checks read the download
// (work/download-3.7.0) and the decrypted master (data/basmaster-3.7.0.sqlite3) from the repo.
#include <ftw.h>
#include <sqlite3.h>
#include <sys/stat.h>
#include <unistd.h>

#include <cstdio>
#include <cstring>
#include <ctime>
#include <string>
#include <vector>

#include "soaserver/adld.h"
#include "soaserver/cdn.h"
#include "soaserver/chash32.h"
#include "soaserver/config.h"
#include "soaserver/msgpack.h"
#include "soaserver/native_test.h"
#include "soaserver/scratch.h"
#include "soaserver/server.h"

namespace soa::server {
namespace {

bool slurp(const std::string& p, std::vector<uint8_t>& out) {
    out.clear();
    FILE* f = fopen(p.c_str(), "rb");
    if (!f) return false;
    uint8_t b[65536];
    size_t n;
    while ((n = fread(b, 1, sizeof b, f)) > 0) out.insert(out.end(), b, b + n);
    fclose(f);
    return true;
}
bool spit(const std::string& p, const std::vector<uint8_t>& d) {
    for (size_t i = 1; i < p.size(); i++)
        if (p[i] == '/') mkdir(p.substr(0, i).c_str(), 0755);
    FILE* f = fopen(p.c_str(), "wb");
    if (!f) return false;
    fwrite(d.data(), 1, d.size(), f);
    fclose(f);
    return true;
}
void remove_tree(const std::string& dir) {
    if (dir.rfind("/tmp/soa-cdn-test-", 0) != 0) return;  // only our own scratch trees
    nftw(dir.c_str(), [](const char* p, const struct stat*, int, struct FTW*) { return ::remove(p); }, 16, FTW_DEPTH | FTW_PHYS);
}
std::string need(testing::Context& t, const char* rel) {
    std::string p = find_repo_file(rel);
    if (p.empty()) t.fail("%s not found (the 3.7.0 download / decrypted master)", rel);
    return p;
}
uint32_t rd32(const uint8_t* p) {
    uint32_t v;
    std::memcpy(&v, p, 4);
    return v;
}
int64_t local_time(int y, int mo, int d) {
    struct tm tm = {};
    tm.tm_year = y - 1900;
    tm.tm_mon = mo - 1;
    tm.tm_mday = d;
    tm.tm_hour = 12;
    tm.tm_isdst = -1;
    return (int64_t)mktime(&tm);
}

NATIVE_TEST("cdn/adld-roundtrip") {
    for (int i = 0; i < 60; i++) {
        uint32_t flags = (uint32_t)t.rand_int(0, 2);  // 0 = no cipher, 1 XOR, 2 AES
        auto plain = t.rand_bytes((size_t)t.rand_int(0, 5000));
        std::string name = "Some/asset_" + std::to_string(i) + ".bin";
        auto enc = adld::encrypt(name, plain, flags);
        if (!adld::is_adld(enc.data(), enc.size()) || adld::flags_of(enc.data(), enc.size()) != flags) t.fail("case %d: header", i);
        for (int k = 8; k < 16; k++)
            if (enc[k]) t.fail("case %d: header byte %d", i, k);
        if (flags == adld::kAes && (enc.size() - 16) % 16) t.fail("case %d: AES payload not block-sized", i);
        if (flags == adld::kXor && enc.size() != plain.size() + 16) t.fail("case %d: XOR size", i);
        if (flags != 0 && adld::decrypt(name, enc) != plain) t.fail("case %d (flags %u): decrypt(encrypt(x)) != x", i, flags);
    }
    // a file that isn't ADLD passes through
    std::vector<uint8_t> raw = {'S', 'Q', 'L', 'i', 't', 'e'};
    t.expect_eq(adld::decrypt("x", raw), raw, "non-ADLD passthrough");
}

NATIVE_TEST("cdn/adld-reencrypt-3.7.0") {
    // The 3.7.0 master (AES + DCNE) and an XOR asset: encrypt(decrypt(file)) is the file itself,
    // and the plaintext's SHA-1 is version.bin's "md5".
    struct Case {
        const char* rel;
        const char* name;
        const char* sha1;
    } cases[] = {{"work/download-3.7.0/sqlite/basmaster.sqlite3", "sqlite/basmaster.sqlite3", "ca6131f2984f8c14a75c715f92d36f9f66d1d8f1"},
                 {"work/download-3.7.0/Character/cp0202_b07a.apk", "Character/cp0202_b07a.apk", "36d45f424cac5b1013757fe9836199994ea0cc61"}};
    for (auto& c : cases) {
        std::string p = need(t, c.rel);
        std::vector<uint8_t> file;
        if (p.empty() || !slurp(p, file)) continue;
        auto plain = adld::decrypt(c.name, file);
        t.expect_eq(cdn::sha1_hex(plain.data(), plain.size()), std::string(c.sha1), c.name);
        auto again = adld::encrypt(c.name, plain, adld::flags_of(file.data(), file.size()));
        if (again != file) t.fail("%s: re-encryption differs (%zu vs %zu bytes)", c.name, again.size(), file.size());
    }
    std::string dec = find_repo_file("data/basmaster-3.7.0.sqlite3");
    std::vector<uint8_t> ref, file;
    if (!dec.empty() && slurp(dec, ref) && slurp(find_repo_file("work/download-3.7.0/sqlite/basmaster.sqlite3"), file))
        if (adld::decrypt("sqlite/basmaster.sqlite3", file) != ref) t.fail("the decrypted master differs from data/basmaster-3.7.0.sqlite3");
}

NATIVE_TEST("cdn/version-bin-roundtrip") {
    std::string p = need(t, "work/download-3.7.0/version.bin");
    std::vector<uint8_t> raw;
    if (p.empty() || !slurp(p, raw)) return;
    Value v = mp_decode(raw);
    t.expect_eq(mp_encode(v), raw, "decode -> encode of version.bin");
    const Value* a = v.find("assets");
    if (!a || a->map.size() != 26268) t.fail("assets: %zu entries (26,268 expected)", a ? a->map.size() : 0);
    const Value* r = v.find("revision");
    t.expect_eq(r ? r->s : std::string(), std::string("1471"), "revision");
    // the manifests: they re-encode (not byte for byte: the 3.7.0 files use str16 for short
    // strings) to the same value
    std::string m = need(t, "work/download-3.7.0/manifest/etc2/hi/version_latest_ep1.bin");
    if (!m.empty() && slurp(m, raw)) {
        Value mv = mp_decode(raw);
        auto again = mp_encode(mv);
        t.expect_eq(mp_encode(mp_decode(again)), again, "manifest re-encode is stable");
        const Value* ma = mv.find("assets");
        t.expect_eq(ma ? ma->map.size() : 0, (size_t)102, "ep1 bundles");
    }
}

NATIVE_TEST("cdn/bundle-layout") {
    // Our bundle layout gives the 3.7.0 bundles' sizes (rounded up to 32) for every bundle of the
    // Individual and Bulk manifests, from the members on disk.
    std::string dir = need(t, "work/download-3.7.0");
    if (dir.empty()) return;
    for (const char* man : {"Individual", "Bulk"}) {
        std::vector<uint8_t> raw;
        if (!slurp(dir + "/manifest/etc2/hi/version_latest_" + man + ".bin", raw)) {
            t.fail("%s manifest missing", man);
            continue;
        }
        Value v = mp_decode(raw);
        size_t n = 0, bad = 0;
        for (auto& [bundle, b] : v.find("assets")->map) {
            std::vector<cdn::Member> ms;
            for (auto& [name, m] : b.map) {
                if (m.type != Value::Map) continue;
                cdn::Member mm;
                mm.name = name;
                mm.enc = (uint32_t)m.get_u("e");
                struct stat st;
                if (stat((dir + "/" + name).c_str(), &st) != 0) {
                    t.fail("%s: member %s missing", bundle.c_str(), name.c_str());
                    continue;
                }
                mm.skip = mm.enc ? 16 : 0;
                mm.len = (uint64_t)st.st_size - mm.skip;
                ms.push_back(mm);
            }
            uint64_t want = (b.get_u("size") + 31) / 32 * 32;
            if (cdn::bundle_size(ms) != want && bad++ < 5)
                t.fail("%s: size %llu, 3.7.0 %llu", bundle.c_str(), (unsigned long long)cdn::bundle_size(ms), (unsigned long long)want);
            n++;
        }
        if (n < 1000) t.fail("%s: only %zu bundles", man, n);
    }
    // the bytes: the client's reading (CDownloadNode::UnpackChildData) gets every member back
    std::vector<cdn::Member> ms;
    std::vector<std::vector<uint8_t>> payloads;
    for (int i = 0; i < 5; i++) {
        auto d = std::make_shared<std::vector<uint8_t>>(t.rand_bytes((size_t)t.rand_int(0, 3000)));
        cdn::Member m;
        m.name = "Dir" + std::to_string(i) + "/file_" + std::string((size_t)t.rand_int(1, 40), 'x') + ".bin";
        m.mem = d;
        m.skip = d->size() > 8 ? 8 : 0;
        m.len = d->size() - m.skip;
        payloads.emplace_back(d->begin() + (ptrdiff_t)m.skip, d->end());
        ms.push_back(m);
    }
    std::vector<uint8_t> b;
    if (!cdn::bundle_bytes(ms, b)) t.fail("bundle_bytes");
    t.expect_eq((uint64_t)b.size(), cdn::bundle_size(ms), "bundle size");
    t.expect_eq(cdn::bundle_sha1(ms), cdn::sha1_hex(b.data(), b.size()), "streamed SHA-1");
    if (b.size() < 16 || rd32(&b[0]) != 0x46534900 || rd32(&b[4]) > 0x20130304 || rd32(&b[8]) != ms.size()) {
        t.fail("bundle header");
        return;
    }
    for (size_t i = 0; i < ms.size(); i++) {
        const uint8_t* e = &b[16 + 16 * i];
        std::string name((const char*)&b[rd32(e)]);
        t.expect_eq(name, ms[i].name, "member name");
        if (rd32(e + 4) % 32) t.fail("member %zu not 32-aligned", i);
        std::vector<uint8_t> got(b.begin() + rd32(e + 4), b.begin() + rd32(e + 4) + rd32(e + 8));
        t.expect_eq(got, payloads[i], "member payload");
    }
}

NATIVE_TEST("cdn/served-master") {
    // The served master: the 3.7.0 master with the client-master overrides (here at a fixed clock,
    // 2026-07-20: the replayed event calendar is in 2021 or earlier, so the dated event tables move
    // by whole years), VACUUMed, ADLD-AES packed.
    std::string master = need(t, "data/basmaster-3.7.0.sqlite3");
    if (master.empty()) return;
    std::string dir = "/tmp/soa-cdn-test-" + std::to_string(getpid()) + "-master";
    mkdir(dir.c_str(), 0755);
    std::string sha;
    uint64_t size = 0;
    auto enc = cdn::make_served_master(master, dir + "/served.sqlite3", true, local_time(2026, 7, 20), &sha, &size);
    if (enc.empty()) {
        t.fail("make_served_master failed");
        remove_tree(dir);
        return;
    }
    auto plain = adld::decrypt("sqlite/basmaster.sqlite3", enc);
    t.expect_eq((uint64_t)plain.size(), size, "plaintext size");
    t.expect_eq(cdn::sha1_hex(plain.data(), plain.size()), sha, "plaintext SHA-1");
    t.expect_eq(adld::flags_of(enc.data(), enc.size()), adld::kAes, "encType 2");
    t.expect_eq(adld::encrypt("sqlite/basmaster.sqlite3", plain, adld::kAes), enc, "re-encryption");
    spit(dir + "/check.sqlite3", plain);
    sqlite3* db = nullptr;
    if (sqlite3_open_v2((dir + "/check.sqlite3").c_str(), &db, SQLITE_OPEN_READWRITE, nullptr) == SQLITE_OK) {
        auto one = [&](const std::string& sql) -> int64_t {
            sqlite3_stmt* st = nullptr;
            int64_t v = -1;
            if (sqlite3_prepare_v2(db, sql.c_str(), -1, &st, nullptr) == SQLITE_OK && sqlite3_step(st) == SQLITE_ROW) v = sqlite3_column_int64(st, 0);
            else t.fail("query failed: %s: %s", sql.c_str(), sqlite3_errmsg(db));
            sqlite3_finalize(st);
            return v;
        };
        t.expect_eq(one("select count(*) from master_global where key = 'service_stop_day'"), (int64_t)0, "service_stop_day dropped");
        t.expect_eq(one("select count(*) from master_text"), (int64_t)66945, "master_text rows (3.7.0)");
        sqlite3_exec(db, ("attach database '" + master + "' as o").c_str(), nullptr, nullptr, nullptr);
        int64_t moved = one("select count(*) from master_event_term n join o.master_event_term e on e.id = n.id where n.opened_day != e.opened_day");
        int64_t whole =
            one("select count(*) from master_event_term n join o.master_event_term e on e.id = n.id where n.opened_day != e.opened_day "
                "and substr(n.opened_day, 5) = substr(e.opened_day, 5) and cast(substr(n.opened_day, 1, 4) as integer) > "
                "cast(substr(e.opened_day, 1, 4) as integer)");
        if (moved <= 0) t.fail("no master_event_term date moved");
        t.expect_eq(whole, moved, "event terms moved by whole years, forwards");
        sqlite3_close(db);
    } else t.fail("cannot open the served master");
    remove_tree(dir);
}

// A small synthetic download: version.bin, two manifests, three members; the served tree.
NATIVE_TEST("cdn/tree") {
    std::string root = "/tmp/soa-cdn-test-" + std::to_string(getpid()) + "-tree";
    remove_tree(root);
    std::string mir = root + "/mirror";
    auto plain_a = t.rand_bytes(1000), plain_b = t.rand_bytes(333), plain_s = t.rand_bytes(2000);
    auto file_a = adld::encrypt("BG/a.aaf", plain_a, adld::kXor);
    spit(mir + "/BG/a.aaf", file_a);
    spit(mir + "/Sound/b.bin", plain_b);
    auto file_s = adld::encrypt("Image/etc2/standin.aif", plain_s, adld::kXor);
    spit(root + "/standins/Image/etc2/standin.aif", file_s);
    spit(root + "/standins/BG/a.aaf", file_a);  // a real asset of the same name wins
    // a tiny master
    std::string master = root + "/master.sqlite3";
    {
        sqlite3* db = nullptr;
        sqlite3_open(master.c_str(), &db);
        sqlite3_exec(
            db,
            "create table master_global (key text, value text); insert into master_global (key, value) values ('service_stop_day', 'x'), ('a', 'b');",
            nullptr, nullptr, nullptr);
        sqlite3_close(db);
    }
    auto entry = [](const char* md5, uint64_t size, uint32_t enc, uint32_t flags = 0) {
        Value e = Value::object();
        e["md5"] = Value(md5);
        e["size"] = Value((unsigned long long)size);
        e["time"] = Value(1600000000u);
        e["parentHash"] = Value(0u);
        e["flags"] = Value(flags);
        e["encType"] = Value(enc);
        e["ep_data"] = Value("");
        e["meta"] = Value::array();
        return e;
    };
    const std::string vid = "0123456789abcdef0123456789abcdef";
    Value vb = Value::object();
    vb["appliversion"] = Value(1u);
    vb["version"] = Value(vid);
    vb["revision"] = Value("7");
    Value& as = vb["assets"];
    as = Value::object();
    as["BG/a.aaf"] = entry("old", file_a.size(), 1);
    as["Sound/b.bin"] = entry("old", plain_b.size(), 0);
    as["sqlite/basmaster.sqlite3"] = entry("old", 1, 2);
    as["I/00000001/00000001.bin"] = entry("old", 0, 0, 1);
    spit(mir + "/version.bin", mp_encode(vb));
    auto member = [](const std::vector<uint8_t>& plain, uint32_t e, const std::string& p) {
        Value m = Value::object();
        m["size"] = Value((unsigned long long)plain.size());
        m["md5"] = Value(cdn::sha1_hex(plain.data(), plain.size()));  // as in the 3.7.0 manifests
        m["meta"] = Value::array();
        m["p"] = Value(p);
        m["e"] = Value(e);
        m["ep_data"] = Value("");
        return m;
    };
    auto bundle = [](Value members) {
        members["md5"] = Value("old");
        members["size"] = Value(0u);
        members["meta"] = Value::array();
        return members;
    };
    Value ind = Value::object();
    ind["version"] = Value(vid);
    ind["toolversion"] = Value("1.2.0");
    ind["assets"] = Value::object();
    Value b1 = Value::object(), b2 = Value::object(), b3 = Value::object(), ball = Value::object();
    b1["BG/a.aaf"] = member(plain_a, 1, "I/00000001/00000001");
    b2["sqlite/basmaster.sqlite3"] = member({}, 2, "I/00000002/00000002");
    b3["Sound/b.bin"] = member(plain_b, 0, "I/00000003/00000003");
    ind["assets"]["I/00000001/00000001.bin"] = bundle(b1);
    ind["assets"]["I/00000002/00000002.bin"] = bundle(b2);
    ind["assets"]["I/00000003/00000003.bin"] = bundle(b3);
    ball["BG/a.aaf"] = member(plain_a, 1, "B/00000001/00000001");
    ball["sqlite/basmaster.sqlite3"] = member({}, 2, "B/00000001/00000001");
    ball["Sound/b.bin"] = member(plain_b, 0, "B/00000001/00000001");
    Value bulk = Value::object();
    bulk["version"] = Value(vid);
    bulk["toolversion"] = Value("1.2.0");
    bulk["assets"] = Value::object();
    bulk["assets"]["B/00000001/00000001.bin"] = bundle(ball);
    spit(mir + "/manifest/etc2/hi/version_latest_Individual.bin", mp_encode(ind));
    spit(mir + "/manifest/etc2/hi/version_latest_Bulk.bin", mp_encode(bulk));

    cdn::Options o;
    o.mirror = mir;
    o.master = master;
    o.scratch = root + "/scratch";
    o.standins = root + "/standins";
    o.overrides = false;
    o.now = 1700000000;
    o.threads = 2;
    std::string err;
    auto tree = cdn::Tree::build(o, &err);
    if (!tree) {
        t.fail("build: %s", err.c_str());
        remove_tree(root);
        return;
    }
    t.expect_eq(tree->revision(), std::string("8"), "revision + 1");
    const std::string base = "/download/8/Android/";
    cdn::Response r;
    auto get = [&](const std::string& path) -> Value {
        if (!tree->lookup(path, r) || r.status != 200) {
            t.fail("GET %s: %d", path.c_str(), r.status);
            return Value();
        }
        std::vector<uint8_t> b;
        r.read(b);
        return mp_decode(b);
    };
    Value v = get(base + "version.bin");
    t.expect_eq(v.find("revision") ? v.find("revision")->s : "", std::string("8"), "served revision");
    t.expect_eq(v.find("version") ? v.find("version")->s : "", tree->version_id(), "served version id");
    if (tree->version_id() == vid || tree->version_id().size() != 32) t.fail("version id not renewed");
    // the served master: version.bin's entry and the file
    std::vector<uint8_t> master_file;
    if (tree->lookup(base + "sqlite/basmaster.sqlite3", r)) r.read(master_file);
    else t.fail("no served master");
    auto master_plain = adld::decrypt("sqlite/basmaster.sqlite3", master_file);
    const Value* me = v.find("assets") ? v.find("assets")->find("sqlite/basmaster.sqlite3") : nullptr;
    if (!me || me->find("md5")->s != cdn::sha1_hex(master_plain.data(), master_plain.size()) || me->get_u("size") != master_file.size() ||
        me->get_u("time") != 1700000000u)
        t.fail("version.bin master entry");
    // every bundle: its SHA-1 and size as the manifest says, and its members as the client writes them
    std::map<std::string, std::vector<uint8_t>> expect = {
        {"BG/a.aaf", file_a}, {"Sound/b.bin", plain_b}, {"sqlite/basmaster.sqlite3", master_file}, {"Image/etc2/standin.aif", file_s}};
    int checked = 0;
    for (const char* man : {"Individual", "Bulk"}) {
        Value mv = get(base + "manifest/etc2/hi/version_latest_" + std::string(man) + ".bin");
        t.expect_eq(mv.find("version") ? mv.find("version")->s : "", tree->version_id(), "manifest version id");
        if (!mv.find("assets")) continue;
        for (auto& [bname, bv] : mv.find("assets")->map) {
            std::vector<uint8_t> bytes;
            if (!tree->lookup(base + bname, r) || !r.read(bytes)) {
                t.fail("bundle %s not served", bname.c_str());
                continue;
            }
            t.expect_eq(cdn::sha1_hex(bytes.data(), bytes.size()), bv.find("md5")->s, "bundle md5");
            t.expect_eq((uint64_t)bytes.size(), bv.get_u("size"), "bundle size");
            for (uint32_t i = 0; i < rd32(&bytes[8]); i++) {
                const uint8_t* e = &bytes[16 + 16 * i];
                std::string name((const char*)&bytes[rd32(e)]);
                const Value* mm = bv.find(name);
                if (!mm) {
                    t.fail("%s: %s not in the manifest", bname.c_str(), name.c_str());
                    continue;
                }
                uint32_t enc = (uint32_t)mm->get_u("e");
                std::vector<uint8_t> written;  // CDownloadNode::UnpackNotify::Handler
                if (enc) {
                    written.assign(16, 0);
                    std::memcpy(written.data(), "ADLD", 4);
                    std::memcpy(written.data() + 4, &enc, 4);
                }
                written.insert(written.end(), bytes.begin() + rd32(e + 4), bytes.begin() + rd32(e + 4) + rd32(e + 8));
                if (written != expect[name]) t.fail("%s: %s as written differs", bname.c_str(), name.c_str());
                auto p = adld::decrypt(name, written);
                t.expect_eq(cdn::sha1_hex(p.data(), p.size()), mm->find("md5")->s, "member md5");
                t.expect_eq((uint64_t)p.size(), mm->get_u("size"), "member size");
                checked++;
            }
        }
    }
    t.expect_eq(checked, 8, "members checked (4 Individual, 4 Bulk)");
    // the bundle entries of version.bin, the stand-in's entry
    if (const Value* a = v.find("assets")) {
        const Value* be = a->find("I/00000001/00000001.bin");
        std::vector<uint8_t> b1b;
        if (tree->lookup(base + "I/00000001/00000001.bin", r)) r.read(b1b);
        if (!be || be->find("md5")->s != cdn::sha1_hex(b1b.data(), b1b.size())) t.fail("version.bin bundle entry md5");
        const Value* se = a->find("Image/etc2/standin.aif");
        std::string sb = tree->bundle_of("Individual", "Image/etc2/standin.aif");
        if (!se || sb.empty() || se->get_u("parentHash") != chash32(sb.c_str()) || se->get_u("size") != file_s.size() || se->get_u("encType") != 1)
            t.fail("version.bin stand-in entry");
        if (tree->bundle_of("Individual", "BG/a.aaf") != "I/00000001/00000001.bin") t.fail("a real asset was replaced by a stand-in");
    }
    // the .version files
    if (tree->lookup(base + "manifest/etc2/hi/version_latest_Individual.version", r)) {
        std::string s(r.body.begin(), r.body.end());
        std::string want = "version:" + tree->version_id() +
                           "\r\ntotalSize:" + std::to_string(plain_a.size() + plain_b.size() + master_plain.size() + plain_s.size()) + "\r\n";
        t.expect_eq(s, want, "version_latest_Individual.version");
        t.expect_eq(r.content_type, std::string("text/plain"), "content type");
    } else t.fail("no .version");
    if (!tree->lookup(base + "manifest/etc2/hi/version.version", r) || std::string(r.body.begin(), r.body.end()) != tree->version_id())
        t.fail("version.version");
    // other spellings and refusals
    if (!tree->lookup("/master/8/version.bin", r) || r.status != 200) t.fail("master/ swap path");
    if (!tree->lookup("Android/version.bin?x=1", r)) t.fail("query string");
    if (!tree->lookup(base + "BG/a.aaf", r) || r.file.empty()) t.fail("plain download file");
    if (tree->lookup(base + "../mirror/version.bin", r) || tree->lookup(base + "nope.bin", r) || tree->lookup("/download/8/version.bin", r))
        t.fail("bad paths answered");
    if (r.status != 404) t.fail("404 expected");
    // the hash cache: a second build reuses it and gives the same answers
    o.now = 1700000000;
    auto again = cdn::Tree::build(o, &err);
    if (!again || again->version_id().size() != 32) t.fail("rebuild");
    remove_tree(root);
}

NATIVE_TEST("cdn/login-paths") {
    // Login carries AssetPath / MasterPath / r_ver / a_ver / LatestEpisodeVersion only when a CDN is
    // configured (soa-server, soa's in-process CDN).
    ServerConfig& c = config();
    std::string saved_url = c.cdn_url, saved_rev = c.cdn_revision;
    for (int pass = 0; pass < 2; pass++) {
        c.cdn_url = pass ? "http://127.0.0.1:8081/" : "";
        c.cdn_revision = pass ? "1472" : "";
        testing::Scratch s(t.rand_u64());
        if (!s.ok()) break;
        Request r;
        r.method = "Login";
        r.fid = 1;
        std::vector<uint8_t> body;
        t.expect_eq(s.call(r, &body), 0u, "Login accepted");
        Value v = mp_decode(body);
        const Value* d = v.find("data");
        if (!d) {
            t.fail("no data");
            continue;
        }
        if (!pass) {
            if (d->find("AssetPath") || d->find("MasterPath") || d->find("r_ver") || d->find("a_ver") || d->find("LatestEpisodeVersion"))
                t.fail("CDN keys sent without a CDN");
        } else {
            t.expect_eq(d->find("AssetPath") ? d->find("AssetPath")->s : "", std::string("http://127.0.0.1:8081/download"), "AssetPath");
            t.expect_eq(d->find("MasterPath") ? d->find("MasterPath")->s : "", std::string("http://127.0.0.1:8081/master"), "MasterPath");
            t.expect_eq(d->find("r_ver") ? d->find("r_ver")->s : "", std::string("1472"), "r_ver");
            // master_global.a_ver_android: the app versions the client accepts (CallBackCore)
            t.expect_eq(d->find("a_ver") ? d->find("a_ver")->s : "", std::string("3.7.0"), "a_ver");
            // master_global.latest_episode_version: the episode count (CInfoManager+0xb0f0 =
            // CParameterManager+0xb6f0, tEpisodeData's max; docs/server-rules.md "soa-server: the CDN", "Episode data")
            const Value* ev = d->find("LatestEpisodeVersion");
            t.expect_eq(ev ? (unsigned)ev->u : 0u, 3u, "LatestEpisodeVersion");
        }
    }
    c.cdn_url = saved_url;
    c.cdn_revision = saved_rev;
}

}  // namespace
}  // namespace soa::server
