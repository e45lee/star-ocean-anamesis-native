// The Game.xml codec (Aska::LocalKVS SharedPreferences files; state/kvs.h): the file codec is
// soa_codec's (common/include/soa/kvs.h); the value readers are the server's. Port code, not guest
// behaviour: the layout is the client's (soa_save/kvs.py documents it).
#include "state/kvs.h"

#include <soa/kvs.h>

#include <algorithm>
#include <cstring>

namespace soa::server {

std::vector<std::pair<std::string, std::string>> read_kvs_ordered(const std::string& path) { return kvs::read(path); }
std::map<std::string, std::string> read_kvs(const std::string& path) {
    std::map<std::string, std::string> kv;
    for (auto& [k, v] : read_kvs_ordered(path)) kv[k] = v;
    return kv;
}
bool write_kvs(const std::string& path, const std::vector<std::pair<std::string, std::string>>& kv) { return kvs::write(path, kv); }
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
