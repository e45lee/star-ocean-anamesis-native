#pragma once
// The containers of the server's reply types (api/gen/reply_types.h, server/src/api/gen/README.md): port
// code, not guest behaviour. An IInfoBaseMap<K, T> the client reads (its keys the decimal text of a K) is
// an InfoMap<K, T>: the pairs in insertion order, a key set twice keeping its first place, as the
// Value maps the handlers built before did (msgpack.h: maps keep insertion order); its encoding is
// those maps' byte for byte.
#include <string>
#include <utility>
#include <vector>

#include "soaserver/msgpack.h"
#include "soaserver/server.h"  // u8 ... u64

namespace soa::server::infos {

template <class K, class T>
struct InfoMap {
    std::vector<std::pair<K, T>> pairs;

    // The value of `k`, added (default) at the end when absent.
    T& operator[](K k) {
        for (auto& p : pairs)
            if (p.first == k) return p.second;
        pairs.emplace_back(k, T{});
        return pairs.back().second;
    }
    bool empty() const { return pairs.empty(); }
    size_t size() const { return pairs.size(); }
    auto begin() const { return pairs.begin(); }
    auto end() const { return pairs.end(); }
};

// A scalar as the Value the handlers sent (u8 as unsigned: the same encoding).
inline Value to_value(bool v) { return Value(v); }
inline Value to_value(u8 v) { return Value((unsigned)v); }
inline Value to_value(u32 v) { return Value(v); }
inline Value to_value(u64 v) { return Value(v); }
inline Value to_value(s32 v) { return Value(v); }
inline Value to_value(double v) { return Value(v); }
inline Value to_value(const std::string& v) { return Value(v); }

template <class T>
Value to_value(const std::vector<T>& v);
template <class K, class T>
Value to_value(const InfoMap<K, T>& m);

// A list (InfoBaseArray<T>, InfoBaseValueArray<T>): an array of its elements' values.
template <class T>
Value to_array(const std::vector<T>& v) {
    Value a = Value::array();
    for (const T& e : v) a.push(to_value(e));
    return a;
}
// A map container sent as an array (the client's map reader gets an array: today's replies).
template <class K, class T>
Value to_array(const InfoMap<K, T>& m) {
    Value a = Value::array();
    for (const auto& [k, e] : m) a.push(to_value(e));
    return a;
}
// An IInfoBaseMap<K, T>: a map from the keys' decimal text to the elements' values.
template <class K, class T>
Value to_map(const InfoMap<K, T>& m) {
    Value o = Value::object();
    for (const auto& [k, e] : m) o[std::to_string(k)] = to_value(e);
    return o;
}

// to_value of a container: a list's array, a map's map (a container of containers nests them).
template <class T>
Value to_value(const std::vector<T>& v) {
    return to_array(v);
}
template <class K, class T>
Value to_value(const InfoMap<K, T>& m) {
    return to_map(m);
}

}  // namespace soa::server::infos
