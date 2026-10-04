#pragma once
// The parser's entry points for the other params natives (internal): the checked entries of the
// getters the property natives call, as the guest's property code calls them (so --live-check params
// also sees these nested calls), and the key-hash cache CParameterElementBase::Deserialize lends
// GetParserValue.
#include <vector>

#include "native/params/params_layout.h"

namespace soa::native::params {

// CParameterParser::GetValue<T>(map, unsigned) as the property instantiations call them (T = unsigned,
// int, float, bool, unsigned char, unsigned long).
template <typename T>
ParserResult<T> GetValueByHash(const AMap* map, u32 hash);
// GetValue<std::string>(map, unsigned) (x8 result).
void GetValueStdStringByHash(libcxx::pair<String, bool>* out, const AMap* map, u32 hash);

// The hashes of one map's keys, made once by CParameterElementBase::Deserialize for the walk it does
// and lent (through a thread-local) to the GetParserValue calls its properties make on the same map:
// the guest hashes every key again in every lookup (n^2 / 2 hashes per element). hash[i] is
// CHash32(key C string) for a string key (kind 5; 0 when its C string is null, as CHash32(nullptr)),
// 0 for any other kind; GetParserValue never matches hash 0, so the first i with hash[i] == h is the
// guest's answer. Valid while the map is unchanged: the element's Deserialize and its properties
// only read it (a const map).
class KeyHashes {
public:
    explicit KeyHashes(const AMap* map);
    ~KeyHashes();
    KeyHashes(const KeyHashes&) = delete;
    KeyHashes& operator=(const KeyHashes&) = delete;

    static const KeyHashes* current();  // the innermost one on this thread, or null
    bool covers(const AMap* map) const { return map == map_ && map->m_pairs == pairs_ && map->m_count == count_; }
    u32 hash(u32 i) const { return hash_[i]; }
    // kind 5 with a C string (CParameterElementBase::Deserialize's test for a key it looks up)
    bool named(u32 i) const { return named_[i]; }
    u32 count() const { return count_; }

private:
    static constexpr u32 kInline = 64;  // (most maps: no allocation)
    const AMap* map_;
    const ASON_Pair* pairs_;
    u32 count_;
    const KeyHashes* outer_;
    u32* hash_;
    u8* named_;
    std::vector<u32> heap_hash_;
    std::vector<u8> heap_named_;
    u32 inline_hash_[kInline];
    u8 inline_named_[kInline];
};

}  // namespace soa::native::params
