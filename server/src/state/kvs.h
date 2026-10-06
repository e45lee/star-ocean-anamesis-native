#pragma once
// The Game.xml codec: the game's Aska::LocalKVS SharedPreferences files (port code, not guest
// behaviour; the format is the client's, soa_save/kvs.py documents it). The server reads the seed
// save with it (state/seed.cpp); the tests write one back. The file codec itself is soa_codec's
// (common/include/soa/kvs.h); these forward to it.
#include <map>
#include <string>
#include <utility>
#include <vector>

#include "soaserver/server.h"

namespace soa::server {

// The key / value pairs of the file at `path`, in file order (empty when it can't be read).
std::vector<std::pair<std::string, std::string>> read_kvs_ordered(const std::string& path);
std::map<std::string, std::string> read_kvs(const std::string& path);
// Writes the pairs as the game writes them (true when written).
bool write_kvs(const std::string& path, const std::vector<std::pair<std::string, std::string>>& kv);
// A value as the little-endian u32 the game stores (`dflt` when missing or empty).
u32 kv_u32(const std::map<std::string, std::string>& kv, const std::string& k, u32 dflt = 0);
// A value as a string, trailing NULs cut ("" when missing).
std::string kv_str(const std::map<std::string, std::string>& kv, const std::string& k);

}  // namespace soa::server
