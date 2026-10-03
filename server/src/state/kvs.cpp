// The Game.xml codec (Aska::LocalKVS SharedPreferences files; state/kvs.h). Port code, not guest
// behaviour: the layout is the client's (soa_save/kvs.py documents it).
#include "state/kvs.h"

#include <openssl/evp.h>

#include <cstdio>
#include <cstring>

namespace soa::server {

namespace {
std::string b64decode(const std::string& in) {
    static int8_t T[256];
    static bool init = false;
    if (!init) {
        memset(T, -1, sizeof T);
        const char* a = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
        for (int i = 0; i < 64; i++) T[(u8)a[i]] = (int8_t)i;
        init = true;
    }
    std::string out;
    u32 acc = 0;
    int bits = 0;
    for (char c : in) {
        int8_t v = T[(u8)c];
        if (v < 0) continue;  // whitespace, '=', "&#10;" leftovers are skipped
        acc = (acc << 6) | (u32)v;
        bits += 6;
        if (bits >= 8) {
            bits -= 8;
            out.push_back((char)((acc >> bits) & 0xff));
        }
    }
    return out;
}

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
    size_t p = 0;
    const std::string open = "<string name=\"";
    while ((p = s.find(open, p)) != std::string::npos) {
        p += open.size();
        size_t q = s.find("\">", p);
        size_t e = s.find("</string>", q);
        if (q == std::string::npos || e == std::string::npos) break;
        std::string name = chacha(b64decode(s.substr(p, q - p)));
        std::string text = s.substr(q + 2, e - q - 2);
        size_t amp;
        while ((amp = text.find("&#10;")) != std::string::npos) text.replace(amp, 5, "\n");
        kv.emplace_back(name, chacha(b64decode(text)));
        p = e;
    }
    return kv;
}
std::map<std::string, std::string> read_kvs(const std::string& path) {
    std::map<std::string, std::string> kv;
    for (auto& [k, v] : read_kvs_ordered(path)) kv[k] = v;
    return kv;
}

namespace {
std::string b64encode(const std::string& in) {
    static const char* a = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    std::string out;
    size_t i = 0;
    for (; i + 2 < in.size(); i += 3) {
        u32 v = ((u8)in[i] << 16) | ((u8)in[i + 1] << 8) | (u8)in[i + 2];
        for (int k = 3; k >= 0; k--) out.push_back(a[(v >> (6 * k)) & 63]);
    }
    if (i + 1 == in.size()) {
        u32 v = (u8)in[i] << 16;
        out += {a[(v >> 18) & 63], a[(v >> 12) & 63], '=', '='};
    } else if (i + 2 == in.size()) {
        u32 v = ((u8)in[i] << 16) | ((u8)in[i + 1] << 8);
        out += {a[(v >> 18) & 63], a[(v >> 12) & 63], a[(v >> 6) & 63], '='};
    }
    return out;
}

}  // namespace

// Writes an Aska::LocalKVS SharedPreferences file (the layout soa_save/kvs.py documents): the
// name is Aska's Base64 of ChaCha20(key) ("====" appended when no padding is needed), the value
// Android's Base64.DEFAULT (76-column lines) of ChaCha20(value) plus four spaces.
bool write_kvs(const std::string& path, const std::vector<std::pair<std::string, std::string>>& kv) {
    std::string out = "<?xml version='1.0' encoding='utf-8' standalone='yes' ?>\n<map>\n";
    for (auto& [k, v] : kv) {
        std::string ek = chacha(k), n = b64encode(ek);
        if (ek.size() % 3 == 0) n += "====";
        std::string b = b64encode(chacha(v)), t;
        for (size_t i = 0; i < b.size(); i += 76) t += b.substr(i, 76) + "&#10;";
        t += "    ";
        out += "    <string name=\"" + n + "\">" + t + "</string>\n";
    }
    out += "</map>\n";
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
