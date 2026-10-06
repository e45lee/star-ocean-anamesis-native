// The Aska::LocalKVS file codec (soa/kvs.h). Port code, not guest behaviour: the layout is the
// client's (soa_save/kvs.py documents it). Moved from server/src/state/kvs.cpp so platform370 can
// write the client's settings too.
#include <soa/kvs.h>

#include <openssl/evp.h>
#include <soa/base64.h>
#include <soa/prefs_xml.h>

#include <cstdio>
#include <cstring>

namespace soa::kvs {

std::string crypt(std::string_view in) {
    static const unsigned char key[] = "xp1666a2P7QGhOCRxCjG8aWj5PmxZOrY";
    static const unsigned char nonce[] = "g7TtZVIKyqc0";
    unsigned char iv[16] = {0};
    memcpy(iv + 4, nonce, 12);
    std::string out(in.size(), '\0');
    if (in.empty()) return out;
    EVP_CIPHER_CTX* c = EVP_CIPHER_CTX_new();
    int n = 0;
    EVP_EncryptInit_ex(c, EVP_chacha20(), nullptr, key, iv);
    EVP_EncryptUpdate(c, (unsigned char*)out.data(), &n, (const unsigned char*)in.data(), (int)in.size());
    EVP_CIPHER_CTX_free(c);
    return out;
}

std::string encode_name(std::string_view key) { return base64::aska_name(crypt(key)); }
std::string encode_value(std::string_view value) { return base64::android_default(crypt(value)) + "    "; }
std::string decode(std::string_view text) { return crypt(base64::decode(text)); }

Pairs read(const std::string& path) {
    Pairs kv;
    FILE* f = fopen(path.c_str(), "rb");
    if (!f) return kv;
    std::string s;
    char buf[65536];
    size_t k;
    while ((k = fread(buf, 1, sizeof buf, f)) > 0) s.append(buf, k);
    fclose(f);
    for (auto& [name, text] : prefs_xml::parse(s)) kv.emplace_back(decode(name), decode(text));
    return kv;
}

bool write(const std::string& path, const Pairs& kv) {
    prefs_xml::Entries e;
    for (auto& [k, v] : kv) e.emplace_back(encode_name(k), encode_value(v));
    std::string out = prefs_xml::serialize(e);
    std::string tmp = path + ".tmp";
    FILE* f = fopen(tmp.c_str(), "wb");
    if (!f) return false;
    bool ok = fwrite(out.data(), 1, out.size(), f) == out.size();
    ok = fclose(f) == 0 && ok;
    if (!ok) {
        remove(tmp.c_str());
        return false;
    }
    return rename(tmp.c_str(), path.c_str()) == 0;
}

}  // namespace soa::kvs
