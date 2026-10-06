// The master DB the CDN serves (soaserver/cdn.h make_served_master): the decrypted 3.7.0 master
// with the server's client-master overrides, VACUUMed and ADLD-AES packed; and under --english its
// English copy (make_english_master). Our code; labels as in docs/server-rules.md#cdn and
// docs/server-rules.md#english.
#include <sqlite3.h>

#include "cdn/files.h"
#include "core/log.h"
#include "master/english_text.h"
#include "soaserver/adld.h"
#include "soaserver/cdn.h"
#include "soaserver/chash32.h"
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
        ServerTime t(now ? now : files::server_time());
        EventTime ev = config().has_clock ? clock_as_calendar(t) : event_time(db, t);
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

namespace {
// VACUUMs `path` and returns its bytes (with the SHA-1 and size), ADLD-AES packed under `name`.
std::vector<uint8_t> vacuum_and_pack(sqlite3* db, const std::string& path, const char* name, std::string* plain_sha1, uint64_t* plain_size) {
    char* err = nullptr;
    if (sqlite3_exec(db, "vacuum", nullptr, nullptr, &err) != SQLITE_OK) {
        LOGW("cdn", "%s: vacuum: %s", name, err ? err : "?");
        sqlite3_free(err);
    }
    sqlite3_close(db);
    std::vector<uint8_t> plain;
    if (!files::read_file(path, plain)) return {};
    if (plain_sha1) *plain_sha1 = sha1_hex(plain.data(), plain.size());
    if (plain_size) *plain_size = plain.size();
    return adld::encrypt(name, plain, adld::kAes);
}
}  // namespace

std::vector<uint8_t> make_english_master(const std::string& served_plain, const std::string& table, const std::string& plain_out,
                                         std::string* plain_sha1, uint64_t* plain_size, EnglishStats* stats) {
    english::Table t;
    std::string why;
    if (!english::load(table, t, &why)) {
        LOGW("cdn", "english master: %s", why.c_str());
        return {};
    }
    if (!files::copy_file(served_plain, plain_out)) {
        LOGE("cdn", "english master: cannot copy %s to %s", served_plain.c_str(), plain_out.c_str());
        return {};
    }
    sqlite3* db = nullptr;
    if (sqlite3_open_v2(plain_out.c_str(), &db, SQLITE_OPEN_READWRITE, nullptr) != SQLITE_OK) {
        LOGE("cdn", "english master: cannot open %s: %s", plain_out.c_str(), db ? sqlite3_errmsg(db) : "?");
        sqlite3_close(db);
        return {};
    }
    EnglishStats st;
    sqlite3_exec(db, "begin", nullptr, nullptr, nullptr);
    // (b) StringDB::GetNativeString / GetList look a row up by id = CHash32("ja_" + message_id)
    // (docs/english.md 6.2), so the English goes into the ja_ rows' text_value and a new id gets a
    // ja_ row of that id; (a) the other columns as the master's own rows: lang ja, data_type
    // package, category_id_label system, category_id = CHash32("system"), serial_number the next.
    sqlite3_stmt *get = nullptr, *upd = nullptr, *ins = nullptr;
    sqlite3_prepare_v2(db, "select text_value from master_text where id = ?", -1, &get, nullptr);
    sqlite3_prepare_v2(db, "update master_text set text_value = ? where id = ?", -1, &upd, nullptr);
    sqlite3_prepare_v2(db,
                       "insert into master_text (id, serial_number, lang, message_id, text_value, text_kana, data_type, category_id, "
                       "category_id_label) values (?, (select ifnull(max(serial_number), 0) + 1 from master_text), 'ja', ?, ?, null, "
                       "'package', ?, 'system')",
                       -1, &ins, nullptr);
    if (!get || !upd || !ins) {
        LOGE("cdn", "english master: %s: %s", plain_out.c_str(), sqlite3_errmsg(db));
        for (sqlite3_stmt* s : {get, upd, ins}) sqlite3_finalize(s);
        sqlite3_close(db);
        return {};
    }
    const int64_t category = chash32("system");
    for (auto& [mid, entry] : t) {
        const int64_t id = chash32(("ja_" + mid).c_str());
        sqlite3_reset(get);
        sqlite3_bind_int64(get, 1, id);
        bool exists = sqlite3_step(get) == SQLITE_ROW;
        std::string ja = exists && sqlite3_column_text(get, 0) ? (const char*)sqlite3_column_text(get, 0) : "";
        english::Match m = exists ? english::match(t, mid, ja, nullptr) : (entry.ja_sha1.empty() ? english::Match::kNewId : english::Match::kNone);
        if (exists && m == english::Match::kReplace) {
            sqlite3_reset(upd);
            sqlite3_bind_text(upd, 1, entry.en.data(), (int)entry.en.size(), SQLITE_TRANSIENT);
            sqlite3_bind_int64(upd, 2, id);
            if (sqlite3_step(upd) == SQLITE_DONE) st.replaced++;
            else st.skipped++;
        } else if (exists && m == english::Match::kStale) {
            st.stale++;  // (d) the English of an older Japanese text: the row keeps its Japanese
        } else if (!exists && m == english::Match::kNewId) {
            sqlite3_reset(ins);
            sqlite3_bind_int64(ins, 1, id);
            sqlite3_bind_text(ins, 2, mid.data(), (int)mid.size(), SQLITE_TRANSIENT);
            sqlite3_bind_text(ins, 3, entry.en.data(), (int)entry.en.size(), SQLITE_TRANSIENT);
            sqlite3_bind_int64(ins, 4, category);
            if (sqlite3_step(ins) == SQLITE_DONE) st.inserted++;
            else st.skipped++;
        } else {
            // (d) a new id whose ja_ id the master has (taken, or the table is wrong), or English for a
            // Japanese row the master lacks: nothing to apply
            st.skipped++;
        }
    }
    for (sqlite3_stmt* s : {get, upd, ins}) sqlite3_finalize(s);
    sqlite3_exec(db, "commit", nullptr, nullptr, nullptr);
    LOGI("cdn", "english master: %s: %zu rows English, %zu inserted, %zu stale (Japanese kept), %zu skipped", table.c_str(), st.replaced, st.inserted,
         st.stale, st.skipped);
    if (stats) *stats = st;
    return vacuum_and_pack(db, plain_out, files::kEnglishMasterName, plain_sha1, plain_size);
}

}  // namespace soa::server::cdn
