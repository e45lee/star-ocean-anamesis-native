// Where the 3.7.0 master DB comes from: the startup rule and the derivation from the user's game
// files (soaserver/master_source.h). Port code, not guest behaviour: (c) the decryption is the
// client's own (soa/adld.h), the rule ours (docs/server-rules.md#core).
#include "soaserver/master_source.h"

#include <soa/file_tree.h>
#include <soa/game_files.h>
#include <soa/zip.h>
#include <soa/paths.h>

#include <cstring>
#include <mutex>

#include "cdn/files.h"
#include "core/log.h"
#include "soa/adld.h"
#include "soaserver/config.h"

namespace soa::server::master_source {
namespace {

// (b) The master's name, its ADLD key (CHash32 of it): the same for the download's copy and the
// APK's built-in one (builtin_data/ is the APK's asset root, not part of the name).
constexpr const char* kName = cdn::files::kMasterName;
constexpr const char* kApkEntry = "assets/builtin_data/sqlite/basmaster.sqlite3";
constexpr const char kSqliteMagic[16] = "SQLite format 3";  // + NUL: 16 bytes

std::mutex g_mu;
bool g_resolved = false;

}  // namespace

std::string cache_dir() {
    const ServerConfig& c = config();
    if (!c.data_root.empty()) return c.data_root + "/master";
    return soa::default_data_dir("soa-server-370", "server-370") + "/master";
}

std::string derive(const std::vector<uint8_t>& encrypted, const std::string& tag, const std::string& dir, std::string* err, bool* reused) {
    if (reused) *reused = false;
    if (!adld::is_adld(encrypted.data(), encrypted.size())) {
        if (err) *err = "not an ADLD file";
        return "";
    }
    cdn::files::Sha1 h;
    h.add(encrypted.data(), encrypted.size());
    std::string path = dir + "/basmaster-3.7.0-" + tag + "-" + h.hex().substr(0, 12) + ".sqlite3";
    uint64_t size = 0;
    if (cdn::files::stat_file(path, &size) && size > sizeof kSqliteMagic) {
        if (reused) *reused = true;
        return path;
    }
    std::vector<uint8_t> plain = adld::decrypt(kName, encrypted);
    if (plain.size() < sizeof kSqliteMagic || memcmp(plain.data(), kSqliteMagic, sizeof kSqliteMagic) != 0) {
        if (err) *err = "the decrypted file isn't a SQLite database";
        return "";
    }
    cdn::files::mkdirs(dir);
    if (!cdn::files::write_file(path, plain.data(), plain.size())) {
        if (err) *err = "can't write " + path;
        return "";
    }
    return path;
}

std::string derive_from_download(const std::string& download, const std::string& dir, std::string* err, bool* reused) {
    std::vector<uint8_t> enc;
    auto tree = FileTree::open(download, err);
    if (!tree) return "";
    if (!tree->read(kName, enc)) {
        if (err) *err = "can't read " + std::string(kName) + " in " + download;
        return "";
    }
    return derive(enc, "download", dir, err, reused);
}

std::string derive_from_apk(const std::string& apk, const std::string& dir, std::string* err, bool* reused) {
    ZipArchive z;
    std::vector<uint8_t> enc;
    const ZipArchive::Entry* e = z.open(apk) ? z.find(kApkEntry) : nullptr;
    if (!e || !z.extract(*e, enc)) {
        if (err) *err = apk + ": can't read " + kApkEntry;
        return "";
    }
    return derive(enc, "apk", dir, err, reused);
}

const std::string& resolve() {
    std::lock_guard<std::mutex> l(g_mu);
    ServerConfig& c = config();
    if (g_resolved) return c.master;
    g_resolved = true;
    if (!c.master.empty()) {  // --master: as given (a missing file is reported where it's opened)
        LOGI("server", "master DB %s (--master)", c.master.c_str());
        return c.master;
    }
    if (std::string p = find_repo_file("data/basmaster-3.7.0.sqlite3"); !p.empty()) {
        c.master = p;
        LOGI("server", "master DB %s", p.c_str());
        return c.master;
    }
    const std::vector<std::string> dirs = install::install_dirs();
    std::string download = !c.download_dir.empty() ? c.download_dir : find_repo_file(install::kRepoDownloadZip);
    if (download.empty() || !install::is_download(download)) {
        if (std::string d = install::find_download(dirs); !d.empty()) download = d;
    }
    std::string dir = cache_dir(), err;
    bool reused = false;
    if (!download.empty() && install::is_download(download)) {
        std::string p = derive_from_download(download, dir, &err, &reused);
        if (!p.empty()) {
            c.master = p;
            LOGI("server", "master DB %s (%s from %s/%s)", p.c_str(), reused ? "derived before" : "decrypted now", download.c_str(), kName);
            return c.master;
        }
        LOGW("server", "the download's master %s/%s: %s", download.c_str(), kName, err.c_str());
    }
    std::vector<std::string> apks;
    if (!c.apk.empty()) apks.push_back(c.apk);
    else if (std::string a = find_repo_file(std::string("apk/") + install::kApk370Name); !a.empty()) apks.push_back(a);
    else apks = install::apk_candidates(dirs);
    for (auto& apk : apks) {
        std::string p = derive_from_apk(apk, dir, &err, &reused);
        if (!p.empty()) {
            c.master = p;
            LOGW("server",
                 "master DB %s (%s from the APK's built-in master, %s): no 3.7.0 download was found, and the APK's master is "
                 "OLDER than the download's (content added later is missing; give --download-dir or --master)",
                 p.c_str(), reused ? "derived before" : "decrypted now", apk.c_str());
            return c.master;
        }
        LOGW("server", "the APK's master (%s): %s", apk.c_str(), err.c_str());
    }
    LOGE("server",
         "no 3.7.0 master DB: give --master FILE, or --download PATH (the 3.7.0 download, a folder or "
         "SOA-3.7.0-canonical-data.zip, whose sqlite/basmaster.sqlite3 is decrypted), or %s",
         install::missing_hint().c_str());
    return c.master;
}

void reset() {
    std::lock_guard<std::mutex> l(g_mu);
    g_resolved = false;
}

}  // namespace soa::server::master_source
