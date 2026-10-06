// soa/kvs.h (part of soa_codec_tests): the committed client save (data/saves/client/Game.xml) read,
// one known value checked, and written back byte for byte; a changed value survives a round trip.
#include <cstdio>
#include <cstring>
#include <filesystem>
#include <string>

#include <soa/kvs.h>

#include "codec_check.h"

namespace {
std::string bytes_of(const std::string& path) {
    std::string s;
    FILE* f = fopen(path.c_str(), "rb");
    if (!f) return s;
    char buf[65536];
    size_t k;
    while ((k = fread(buf, 1, sizeof buf, f)) > 0) s.append(buf, k);
    fclose(f);
    return s;
}
unsigned u32_of(const soa::kvs::Pairs& kv, const std::string& key, bool* found) {
    *found = false;
    for (auto& [k, v] : kv)
        if (k == key && v.size() == 4) {
            unsigned x;
            memcpy(&x, v.data(), 4);
            *found = true;
            return x;
        }
    return 0;
}
}  // namespace

void kvs_tests() {
    using namespace soa;
    codec_check(kvs::crypt(kvs::crypt("BAS:VoiceLanguage")) == "BAS:VoiceLanguage", "kvs: crypt is its own inverse");
    codec_check(kvs::decode(kvs::encode_name("BAS:VoiceLanguage")) == "BAS:VoiceLanguage", "kvs: a name round trip");
    codec_check(kvs::decode(kvs::encode_value(std::string("\0\1\0\0", 4))) == std::string("\0\1\0\0", 4), "kvs: a value round trip");

    std::string save = std::string(SOA_REPO_DIR) + "/data/saves/client/Game.xml";
    kvs::Pairs kv = kvs::read(save);
    codec_check(kv.size() > 100, "kvs: the committed client save has its entries");
    bool found = false;
    codec_check(u32_of(kv, "BAS:VoiceLanguage", &found) == 256 && found, "kvs: BAS:VoiceLanguage = 256 (u32) in the committed save");

    std::string tmp = (std::filesystem::temp_directory_path() / "soa_kvs_tests_Game.xml").string();
    codec_check(kvs::write(tmp, kv), "kvs: write");
    codec_check(bytes_of(tmp) == bytes_of(save), "kvs: the committed save written back byte for byte");
    for (auto& [k, v] : kv)
        if (k == "BAS:VoiceLanguage") v = std::string("\0\0\0\0", 4);
    codec_check(kvs::write(tmp, kv), "kvs: write a changed value");
    kvs::Pairs back = kvs::read(tmp);
    codec_check(back.size() == kv.size() && u32_of(back, "BAS:VoiceLanguage", &found) == 0 && found, "kvs: the changed value read back");
    remove(tmp.c_str());
}
