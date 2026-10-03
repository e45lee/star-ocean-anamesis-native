// The master DB the CDN serves (soaserver/cdn.h make_served_master): the decrypted 3.7.0 master
// with the server's client-master overrides, VACUUMed and ADLD-AES packed. Our code; labels as in
// docs/server-rules.md "soa-server: the CDN".
#include <sqlite3.h>

#include "cdn/files.h"
#include "core/log.h"
#include "soaserver/adld.h"
#include "soaserver/cdn.h"
#include "soaserver/config.h"
#include "soaserver/server.h"

namespace soa::server::cdn {

std::vector<uint8_t> make_served_master(const std::string& master, const std::string& plain_out, bool overrides, int64_t now, std::string* plain_sha1,
                                        uint64_t* plain_size) {
    if (!files::copy_file(master, plain_out)) {
        LOGE("cdn", "master: cannot copy %s to %s", master.c_str(), plain_out.c_str());
        return {};
    }
    sqlite3* db = nullptr;
    if (sqlite3_open_v2(plain_out.c_str(), &db, SQLITE_OPEN_READWRITE, nullptr) != SQLITE_OK) {
        LOGE("cdn", "master: cannot open %s: %s", plain_out.c_str(), db ? sqlite3_errmsg(db) : "?");
        sqlite3_close(db);
        return {};
    }
    if (overrides) {
        // (d) the overrides the in-process client master gets (apply_client_master), with the
        // clock of the server's start: the server clock, and the event calendar replayed on this
        // master (event_now: the clock itself under --clock).
        int64_t t = now ? now : files::server_time();
        int64_t ev = config().has_clock ? t : event_time(db, t);
        apply_client_master(db, t, ev, master);
    }
    char* err = nullptr;
    if (sqlite3_exec(db, "vacuum", nullptr, nullptr, &err) != SQLITE_OK) {
        LOGW("cdn", "master: vacuum: %s", err ? err : "?");
        sqlite3_free(err);
    }
    sqlite3_close(db);
    std::vector<uint8_t> plain;
    if (!files::read_file(plain_out, plain)) return {};
    if (plain_sha1) *plain_sha1 = sha1_hex(plain.data(), plain.size());
    if (plain_size) *plain_size = plain.size();
    return adld::encrypt(files::kMasterName, plain, adld::kAes);
}

}  // namespace soa::server::cdn
