// The CDN's file and hashing helpers (cdn/files.h). Port code, not guest behaviour.
#include "cdn/files.h"

#include <dirent.h>
#include <sys/stat.h>

#include <algorithm>
#include <cstdio>
#include <ctime>

#include "soaserver/config.h"

namespace soa::server::cdn::files {

bool read_file(const std::string& path, std::vector<uint8_t>& out) {
    FILE* f = fopen(path.c_str(), "rb");
    if (!f) return false;
    out.clear();
    uint8_t buf[1 << 16];
    size_t n;
    while ((n = fread(buf, 1, sizeof buf, f)) > 0) out.insert(out.end(), buf, buf + n);
    bool ok = !ferror(f);
    fclose(f);
    return ok;
}
bool write_file(const std::string& path, const uint8_t* data, size_t n) {
    std::string tmp = path + ".tmp";
    FILE* f = fopen(tmp.c_str(), "wb");
    if (!f) return false;
    bool ok = fwrite(data, 1, n, f) == n;
    ok = (fclose(f) == 0) && ok;
    return ok && rename(tmp.c_str(), path.c_str()) == 0;
}
bool copy_file(const std::string& from, const std::string& to) {
    std::vector<uint8_t> data;
    return read_file(from, data) && write_file(to, data.data(), data.size());
}
bool stat_file(const std::string& path, uint64_t* size, int64_t* mtime_ns) {
    struct stat st;
    if (stat(path.c_str(), &st) != 0 || !S_ISREG(st.st_mode)) return false;
    if (size) *size = (uint64_t)st.st_size;
#ifdef _WIN32  // (whole seconds in the CRT's stat)
    if (mtime_ns) *mtime_ns = (int64_t)st.st_mtime * 1000000000;
#else
    if (mtime_ns) *mtime_ns = (int64_t)st.st_mtim.tv_sec * 1000000000 + st.st_mtim.tv_nsec;
#endif
    return true;
}
bool is_dir(const std::string& path) {
    struct stat st;
    return stat(path.c_str(), &st) == 0 && S_ISDIR(st.st_mode);
}
void mkdirs(const std::string& path) {
    for (size_t i = 1; i <= path.size(); i++)
        if (i == path.size() || path[i] == '/') mkdir(path.substr(0, i).c_str(), 0755);
}
void walk(const std::string& root, const std::string& rel, std::vector<std::string>& out) {
    DIR* dir = opendir((root + (rel.empty() ? "" : "/" + rel)).c_str());
    if (!dir) return;
    while (dirent* entry = readdir(dir)) {
        std::string name = entry->d_name;
        if (name == "." || name == "..") continue;
        std::string child = rel.empty() ? name : rel + "/" + name;
        std::string full = root + "/" + child;
        if (is_dir(full)) walk(root, child, out);
        else if (stat_file(full, nullptr)) out.push_back(child);
    }
    closedir(dir);
    std::sort(out.begin(), out.end());
}

std::string Sha1::hex() {
    unsigned char md[EVP_MAX_MD_SIZE];
    unsigned int n = 0;
    EVP_DigestFinal_ex(c, md, &n);
    static const char* digits = "0123456789abcdef";
    std::string s;
    for (unsigned i = 0; i < n; i++) s += digits[md[i] >> 4], s += digits[md[i] & 15];
    return s;
}

int64_t server_time() {
    const ServerConfig& c = config();
    return (int64_t)time(nullptr) + (c.has_clock ? c.clock_offset : 0);
}

Value* map_find(Value& map, const std::string& key) {
    for (auto& entry : map.map)
        if (entry.first == key) return &entry.second;
    return nullptr;
}

}  // namespace soa::server::cdn::files
