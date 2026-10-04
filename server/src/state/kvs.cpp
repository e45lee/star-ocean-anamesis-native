// The Game.xml codec (Aska::LocalKVS SharedPreferences files; state/kvs.h). Port code, not guest
// behaviour: the layout is the client's (soa_save/kvs.py documents it).
#include "state/kvs.h"

#include <openssl/evp.h>
#include <soa/base64.h>
#include <soa/prefs_xml.h>

#include <cstdio>
#include <cstring>

namespace soa::server {

namespace {
std::string chacha(const std::string& in) {
    static const u8 key[] = "xp1666a2P7QGhOCRxCjG8aWj5PmxZOrY";
    static const u8 nonce[] = "g7TtZVIKyqc0";
    u8 iv[16] = {0};
    memcpy(iv + 4, nonce, 12);
    std::string out(in.size(), '\0');
    EVP_CIPHER_CTX* c = EVP_CIPHER_CTX_new();
    int n = 0;
    EVP_EncryptInit_ex(c, EVP_chacha20(), nullptr, key, iv);
    EVP_EncryptUpdate(c, (u8*)out.data(), &n, (const u8*)in.data(), (int)in.size());
    EVP_CIPHER_CTX_free(c);
    return out;
}

}  // namespace

std::vector<std::pair<std::string, std::string>> read_kvs_ordered(const std::string& path) {
    std::vector<std::pair<std::string, std::string>> kv;
    FILE* f = fopen(path.c_str(), "rb");
    if (!f) return kv;
    std::string s;
    char buf[65536];
    size_t k;
    while ((k = fread(buf, 1, sizeof buf, f)) > 0) s.append(buf, k);
    fclose(f);
    for (auto& [name, text] : prefs_xml::parse(s)) kv.emplace_back(chacha(base64::decode(name)), chacha(base64::decode(text)));
    return kv;
}
std::map<std::string, std::string> read_kvs(const std::string& path) {
    std::map<std::string, std::string> kv;
    for (auto& [k, v] : read_kvs_ordered(path)) kv[k] = v;
    return kv;
}

// Writes an Aska::LocalKVS SharedPreferences file (the layout soa_save/kvs.py documents): the
// name is Aska's Base64 of ChaCha20(key) ("====" appended when no padding is needed), the value
// Android's Base64.DEFAULT (76-column lines) of ChaCha20(value) plus four spaces.
bool write_kvs(const std::string& path, const std::vector<std::pair<std::string, std::string>>& kv) {
    prefs_xml::Entries e;
    for (auto& [k, v] : kv) e.emplace_back(base64::aska_name(chacha(k)), base64::android_default(chacha(v)) + "    ");
    std::string out = prefs_xml::serialize(e);
    std::string tmp = path + ".tmp";
    FILE* f = fopen(tmp.c_str(), "wb");
    if (!f) return false;
    fwrite(out.data(), 1, out.size(), f);
    fclose(f);
    return rename(tmp.c_str(), path.c_str()) == 0;
}
u32 kv_u32(const std::map<std::string, std::string>& kv, const std::string& k, u32 dflt) {
    auto it = kv.find(k);
    if (it == kv.end() || it->second.size() < 1) return dflt;
    u32 v = 0;
    memcpy(&v, it->second.data(), std::min<size_t>(4, it->second.size()));
    return v;
}
std::string kv_str(const std::map<std::string, std::string>& kv, const std::string& k) {
    auto it = kv.find(k);
    if (it == kv.end()) return "";
    std::string v = it->second;
    while (!v.empty() && v.back() == '\0') v.pop_back();
    return v;
}

}  // namespace soa::server
