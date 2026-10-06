#pragma once
// The CDN's file and hashing helpers (server/src/cdn/README.md): what bundle.cpp, served_master.cpp
// and tree.cpp share. Internal to the CDN code; the public API is soaserver/cdn.h. Port code, not
// guest behaviour.
#include <openssl/evp.h>

#include <cstdint>
#include <string>
#include <vector>

#include "soaserver/msgpack.h"

namespace soa::server::cdn::files {

constexpr const char* kMasterName = "sqlite/basmaster.sqlite3";  // (b) the master's name in version.bin and the manifests
// (b) the English master's name: CGameResourceManager::FileExistLanguage tries "<name>-en.<ext>"
// first when CLanguage::Current is 1 (docs/english.md 6.3)
constexpr const char* kEnglishMasterName = "sqlite/basmaster-en.sqlite3";

// The whole file (false when it can't be read).
bool read_file(const std::string& path, std::vector<uint8_t>& out);
// Writes through "<path>.tmp" and a rename, so a reader never sees half a file.
bool write_file(const std::string& path, const uint8_t* data, size_t n);
bool copy_file(const std::string& from, const std::string& to);
// A regular file's size (and modification time in ns); false when it isn't one.
bool stat_file(const std::string& path, uint64_t* size, int64_t* mtime_ns = nullptr);
bool is_dir(const std::string& path);
void mkdirs(const std::string& path);
// Every regular file under `root` (relative paths, sorted), appended to `out`.
void walk(const std::string& root, const std::string& rel, std::vector<std::string>& out);
inline uint64_t align(uint64_t v, uint64_t a) { return (v + a - 1) / a * a; }

// A streamed SHA-1 (OpenSSL EVP); hex() finishes it, lowercase.
struct Sha1 {
    EVP_MD_CTX* c = EVP_MD_CTX_new();
    Sha1() { EVP_DigestInit_ex(c, EVP_sha1(), nullptr); }
    ~Sha1() { EVP_MD_CTX_free(c); }
    Sha1(const Sha1&) = delete;
    Sha1& operator=(const Sha1&) = delete;
    void add(const void* data, size_t n) {
        if (n) EVP_DigestUpdate(c, data, n);
    }
    std::string hex();
};

// The server clock of the CDN's dates (--clock aware): version.bin's times, the overrides.
int64_t server_time();
// The entry `key` of a msgpack map, nullptr when absent (the first, as the files hold one).
Value* map_find(Value& map, const std::string& key);

}  // namespace soa::server::cdn::files
