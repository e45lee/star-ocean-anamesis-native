// Tests of the master's derivation from the game files (soaserver/master_source.h) and of the gacha
// titles a packaged pools file takes from the master (master/gacha_pools.h name_from_master).
// Server code, no guest counterpart. They read the 3.7.0 download (work/download-3.7.0), the 3.7.0
// APK (apk/) and data/ from the repo; a missing input fails the test, like cdn/'s.
#include <sqlite3.h>
#include <unistd.h>

#include <cstdio>
#include <cstring>
#include <map>
#include <string>
#include <vector>

#include "cdn/files.h"
#include "master/gacha_pools.h"
#include "soaserver/config.h"
#include "soaserver/master_source.h"
#include "soaserver/native_test.h"

namespace soa::server {
namespace {

// (the SHA-1 of the decrypted 3.7.0 master, the committed data/basmaster-3.7.0.sqlite3;
// cdn/adld-reencrypt-3.7.0 checks the same file)
constexpr const char* kMasterSha1 = "ca6131f2984f8c14a75c715f92d36f9f66d1d8f1";

std::string sha1_of(const std::string& path) {
    std::vector<uint8_t> d;
    if (!cdn::files::read_file(path, d)) return "";
    cdn::files::Sha1 h;
    h.add(d.data(), d.size());
    return h.hex();
}

bool has_table(const std::string& db, const char* table) {
    sqlite3* h = nullptr;
    bool ok = false;
    if (sqlite3_open_v2(db.c_str(), &h, SQLITE_OPEN_READONLY, nullptr) == SQLITE_OK) {
        sqlite3_stmt* st = nullptr;
        if (sqlite3_prepare_v2(h, "select count(*) from sqlite_master where type = 'table' and name = ?", -1, &st, nullptr) == SQLITE_OK) {
            sqlite3_bind_text(st, 1, table, -1, SQLITE_STATIC);
            ok = sqlite3_step(st) == SQLITE_ROW && sqlite3_column_int(st, 0) == 1;
        }
        sqlite3_finalize(st);
    }
    sqlite3_close(h);
    return ok;
}

}  // namespace

// The download's master decrypts to the committed file, byte for byte; a second derivation reuses
// the cached file; the APK's built-in master decrypts to an (older) SQLite master.
NATIVE_TEST("cdn/master-source") {
    std::string download = find_repo_file("work/download-3.7.0");
    std::string apk = find_repo_file("apk/STAR+OCEAN+-anamnesis-_3.7.0_APKPure.apk");
    if (download.empty()) return t.fail("work/download-3.7.0 not found");
    std::string dir = "/tmp/soa-cdn-test-master-" + std::to_string(getpid());
    std::string err;
    bool reused = true;
    std::string p = master_source::derive_from_download(download, dir, &err, &reused);
    if (p.empty()) return t.fail("derive_from_download: %s", err.c_str());
    t.expect_eq(reused, false, "first derivation decrypts");
    t.expect_eq(sha1_of(p), std::string(kMasterSha1), "the derived master's SHA-1 (= data/basmaster-3.7.0.sqlite3)");
    if (std::string committed = find_repo_file("data/basmaster-3.7.0.sqlite3"); !committed.empty())
        t.expect_eq(sha1_of(committed), std::string(kMasterSha1), "the committed master's SHA-1");
    std::string again = master_source::derive_from_download(download, dir, &err, &reused);
    t.expect_eq(again, p, "same path");
    t.expect_eq(reused, true, "second derivation reuses the cache");
    // a changed source gets its own file (keyed by the source's SHA-1); a non-ADLD file is refused
    std::vector<uint8_t> junk(64, 7);
    if (!master_source::derive(junk, "download", dir, &err).empty()) t.fail("a non-ADLD file was accepted");
    if (!master_source::has_zip_reader()) {
        fprintf(stderr, "    no zip reader in this program (soa-server): the APK's master is checked by soa --selftest\n");
    } else if (apk.empty()) {
        t.fail("apk/STAR+OCEAN+-anamnesis-_3.7.0_APKPure.apk not found");
    } else {
        std::string a = master_source::derive_from_apk(apk, dir, &err, &reused);
        if (a.empty()) t.fail("derive_from_apk: %s", err.c_str());
        else {
            if (a == p) t.fail("the APK's master has the download's cache name");
            if (!has_table(a, "master_gacha")) t.fail("the APK's master has no master_gacha");
            master_source::derive_from_apk(apk, dir, &err, &reused);
            t.expect_eq(reused, true, "the APK's master is reused too");
            remove(a.c_str());
        }
    }
    remove(p.c_str());
    rmdir(dir.c_str());
}

// The resolution rule with only an install-style download: --master unset and no repo master ->
// derived into the data dir's master/ (config().data_root), then cached in config().master.
NATIVE_TEST("cdn/master-source-resolve") {
    std::string download = find_repo_file("work/download-3.7.0");
    if (download.empty()) return t.fail("work/download-3.7.0 not found");
    ServerConfig& c = config();
    ServerConfig saved = c;
    std::string root = "/tmp/soa-cdn-test-resolve-" + std::to_string(getpid());
    c.master.clear();
    c.repo_roots = {root + "/no-repo"};  // no data/basmaster-3.7.0.sqlite3 there
    c.data_root = root;
    c.download_dir = download;
    master_source::reset();
    std::string p = master_source::resolve();
    t.expect_eq(p,
                root + "/master/basmaster-3.7.0-download-" + std::string(sha1_of(download + "/sqlite/basmaster.sqlite3")).substr(0, 12) + ".sqlite3",
                "the derived master in DATA/master");
    t.expect_eq(c.master, p, "config().master set");
    t.expect_eq(sha1_of(p), std::string(kMasterSha1), "byte-identical to the committed master");
    remove(p.c_str());
    rmdir((root + "/master").c_str());
    rmdir(root.c_str());
    c = saved;
    master_source::reset();
}

// A pools file without titles (the packages') gives the same GetGachaRate titles: every gacha's
// gacha.name is the master's title through zen2han.
NATIVE_TEST("gacha/pools-name-from-master") {
    std::string pools = find_repo_file("data/gacha_pools.sqlite3");
    std::string master = master_source::resolve();
    if (pools.empty() || master.empty()) return t.fail("data/gacha_pools.sqlite3 or the 3.7.0 master not found");
    t.expect_eq(gacha_pools::zen2han("\xEF\xBC\xA1\xE3\x80\x80\xEF\xBC\x86\xEF\xBD\x9E\xEF\xBD\x9F"), std::string("A &~\xEF\xBD\x9F"),
                "zen2han: U+FF21, U+3000, U+FF06, U+FF5E; U+FF5F kept");
    sqlite3 *p = nullptr, *m = nullptr;
    sqlite3_open_v2(pools.c_str(), &p, SQLITE_OPEN_READONLY, nullptr);
    sqlite3_open_v2(master.c_str(), &m, SQLITE_OPEN_READONLY, nullptr);
    // Every title through zen2han from one read of the master's texts (master_text has no index on
    // message_id, so name_from_master scans it per call); name_from_master itself on every 40th.
    std::map<std::string, std::string> texts;  // message_id -> text (ja)
    sqlite3_stmt* st = nullptr;
    if (sqlite3_prepare_v2(m,
                           "select t.message_id, t.text_value from master_text t join master_gacha g on g.name_message_id = t.message_id "
                           "where t.lang = 'ja'",
                           -1, &st, nullptr) == SQLITE_OK)
        while (sqlite3_step(st) == SQLITE_ROW)
            texts[(const char*)sqlite3_column_text(st, 0)] = sqlite3_column_text(st, 1) ? (const char*)sqlite3_column_text(st, 1) : "";
    sqlite3_finalize(st);
    std::map<uint32_t, std::string> mids;  // gacha id -> name_message_id
    if (sqlite3_prepare_v2(m, "select id, ifnull(name_message_id, '') from master_gacha", -1, &st, nullptr) == SQLITE_OK)
        while (sqlite3_step(st) == SQLITE_ROW) mids[(uint32_t)sqlite3_column_int64(st, 0)] = (const char*)sqlite3_column_text(st, 1);
    sqlite3_finalize(st);
    int n = 0, bad = 0;
    if (sqlite3_prepare_v2(p, "select gacha_id, ifnull(name, '') from gacha", -1, &st, nullptr) == SQLITE_OK) {
        while (sqlite3_step(st) == SQLITE_ROW) {
            uint32_t id = (uint32_t)sqlite3_column_int64(st, 0);
            std::string name = (const char*)sqlite3_column_text(st, 1);
            auto mi = mids.find(id);
            auto ti = mi == mids.end() ? texts.end() : texts.find(mi->second);
            std::string want = ti == texts.end() ? "" : gacha_pools::zen2han(ti->second);
            if (want != name && bad++ < 5) t.fail("gacha %u: the master's title differs from \"%s\"", id, name.c_str());
            if (n++ % 40 == 0 && gacha_pools::name_from_master(m, id) != name && bad++ < 5) t.fail("gacha %u: name_from_master differs", id);
        }
    }
    sqlite3_finalize(st);
    sqlite3_close(p);
    sqlite3_close(m);
    if (n < 1000) t.fail("only %d gachas in the pools", n);
    if (bad) t.fail("%d of %d titles differ", bad, n);
}

}  // namespace soa::server
