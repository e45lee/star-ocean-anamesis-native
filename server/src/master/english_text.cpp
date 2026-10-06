// The English text table of --english (english_text.h; docs/server-rules.md#english). Port code,
// not guest behaviour.
#include "master/english_text.h"

#include <sys/stat.h>

#include <fstream>
#include <mutex>

#include "core/log.h"
#include "soaserver/cdn.h"
#include "soaserver/config.h"

namespace soa::server::english {

namespace {
constexpr const char* kTableRel = "data/english/master-en.tsv";
constexpr const char* kHeader = "message_id\tja_sha1\ten\tsource";

std::string sha1_of(const std::string& s) { return cdn::sha1_hex((const uint8_t*)s.data(), s.size()); }

// The printf conversions of `s` (as tools/english_mt.py's SPEC_STRICT: flags, width, precision,
// length, conversion), "%%" skipped.
std::string specifiers(const std::string& s) {
    std::string out;
    for (size_t i = 0; i < s.size(); i++) {
        if (s[i] != '%') continue;
        if (i + 1 < s.size() && s[i + 1] == '%') {
            i++;
            continue;
        }
        size_t j = i + 1;
        while (j < s.size() && std::string("-+#0").find(s[j]) != std::string::npos) j++;
        while (j < s.size() && isdigit((unsigned char)s[j])) j++;
        if (j < s.size() && s[j] == '.') {
            j++;
            while (j < s.size() && isdigit((unsigned char)s[j])) j++;
        }
        while (j < s.size() && (s[j] == 'l' || s[j] == 'h')) j++;
        if (j < s.size() && std::string("dusfxXc").find(s[j]) != std::string::npos) {
            out += s.substr(i, j + 1 - i) + "|";
            i = j;
        }
    }
    return out;
}
}  // namespace

bool load(const std::string& path, Table& out, std::string* err) {
    out.clear();
    std::ifstream in(path, std::ios::binary);
    if (!in) {
        if (err) *err = "cannot read " + path;
        return false;
    }
    std::string line;
    if (!std::getline(in, line) || line != kHeader) {
        if (err) *err = path + ": the first line is not \"" + std::string(kHeader) + "\"";
        return false;
    }
    size_t n = 1;
    while (std::getline(in, line)) {
        n++;
        if (line.empty()) continue;
        size_t a = line.find('\t'), b = a == std::string::npos ? a : line.find('\t', a + 1), c = b == std::string::npos ? b : line.find('\t', b + 1);
        if (c == std::string::npos || line.find('\t', c + 1) != std::string::npos || a == 0) {
            if (err) *err = path + ":" + std::to_string(n) + ": not four tab-separated fields";
            out.clear();
            return false;
        }
        out[line.substr(0, a)] = Entry{line.substr(a + 1, b - a - 1), line.substr(b + 1, c - b - 1), line.substr(c + 1)};
    }
    return true;
}

std::string table_path() {
    const ServerConfig& c = config();
    if (!c.english_text.empty()) return c.english_text;
    return find_repo_file(kTableRel);
}

std::string story_dir() {
    const ServerConfig& c = config();
    if (!c.english_text.empty()) {
        size_t slash = c.english_text.find_last_of("/\\");
        std::string dir = (slash == std::string::npos ? std::string(".") : c.english_text.substr(0, slash)) + "/story-en";
        struct stat s;
        return stat(dir.c_str(), &s) == 0 && S_ISDIR(s.st_mode) ? dir : "";
    }
    return find_repo_file("data/english/story-en");
}

std::shared_ptr<const Table> table() {
    if (!config().english) return nullptr;
    static std::mutex mu;
    static std::string loaded_path;
    static bool attempted = false;
    static std::shared_ptr<const Table> loaded;
    std::string path = table_path();
    std::lock_guard<std::mutex> lock(mu);
    if (attempted && path == loaded_path) return loaded;  // loaded, or warned once
    attempted = true;
    loaded.reset();
    loaded_path = path;
    if (path.empty()) {
        LOGW("english", "--english: no English text table (%s, --english-text): the server's texts stay Japanese", kTableRel);
        return nullptr;
    }
    auto t = std::make_shared<Table>();
    std::string err;
    if (!load(path, *t, &err)) {
        LOGW("english", "--english: %s: the server's texts stay Japanese", err.c_str());
        return nullptr;
    }
    LOGI("english", "English text table %s: %zu rows", path.c_str(), t->size());
    loaded = t;
    return loaded;
}

Match match(const Table& t, const std::string& message_id, const std::string& ja, const Entry** entry) {
    auto it = t.find(message_id);
    if (entry) *entry = it == t.end() ? nullptr : &it->second;
    if (it == t.end()) return Match::kNone;
    if (it->second.ja_sha1.empty()) return Match::kNewId;
    // (d) the English translates one Japanese text: a changed Japanese row keeps its Japanese
    return it->second.ja_sha1 == sha1_of(ja) ? Match::kReplace : Match::kStale;
}

std::string display(const std::string& message_id, const std::string& ja) {
    auto t = table();
    if (!t) return ja;
    const Entry* e = nullptr;
    Match m = match(*t, message_id, ja, &e);
    if (m == Match::kReplace || (m == Match::kNewId && ja.empty())) return e->en;
    return ja;
}

bool same_specifiers(const std::string& a, const std::string& b) { return specifiers(a) == specifiers(b); }

}  // namespace soa::server::english
