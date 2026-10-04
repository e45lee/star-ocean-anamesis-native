#pragma once
// A small MessagePack value tree for the local server's responses (port code, not guest
// behaviour), encoded and decoded with msgpack-cxx (core/msgpack.cpp). Maps keep insertion order;
// the game's ASON reader doesn't care about order.
#include <cstddef>
#include <cstdint>
#include <string>
#include <utility>
#include <vector>

namespace soa::server {

struct Value {
    enum Type { Nil, Bool, Int, UInt, Float, Str, Arr, Map } type = Nil;
    bool b = false;
    int64_t i = 0;
    uint64_t u = 0;
    double f = 0;
    std::string s;
    std::vector<Value> arr;
    std::vector<std::pair<std::string, Value>> map;

    Value() = default;
    Value(bool v) : type(Bool), b(v) {}
    Value(int v) : type(v < 0 ? Int : UInt), i(v), u(v < 0 ? 0 : (uint64_t)v) {}
    // One constructor per integer type, not per <cstdint> alias: int64_t is long on Linux but
    // long long on Windows (LLP64), so an int64_t overload would duplicate one of these there.
    Value(long long v) : type(v < 0 ? Int : UInt), i(v), u(v < 0 ? 0 : (uint64_t)v) {}
    Value(long v) : Value((long long)v) {}
    Value(unsigned v) : type(UInt), u(v) {}
    Value(unsigned long v) : type(UInt), u(v) {}
    Value(unsigned long long v) : type(UInt), u(v) {}
    Value(double v) : type(Float), f(v) {}
    Value(const char* v) : type(Str), s(v) {}
    Value(std::string v) : type(Str), s(std::move(v)) {}

    // An empty array and an empty map.
    static Value array() {
        Value v;
        v.type = Arr;
        return v;
    }
    static Value object() {
        Value v;
        v.type = Map;
        return v;
    }

    // Map: set (replacing an existing key) and return the stored value.
    Value& operator[](const std::string& k) {
        if (type != Map) {
            type = Map;
        }
        for (auto& e : map)
            if (e.first == k) return e.second;
        map.emplace_back(k, Value());
        return map.back().second;
    }
    Value& push(Value v) {
        type = Arr;
        arr.push_back(std::move(v));
        return arr.back();
    }
    const Value* find(const std::string& k) const {
        for (auto& e : map)
            if (e.first == k) return &e.second;
        return nullptr;
    }
    // Map: the value of `k` to change in place; nullptr when absent (never adds the key).
    Value* find_mut(const std::string& k) {
        for (auto& e : map)
            if (e.first == k) return &e.second;
        return nullptr;
    }
    // Map: the unsigned value of `k` (its `u`), `dflt` when the key is absent.
    uint64_t get_u(const std::string& k, uint64_t dflt = 0) const {
        const Value* v = find(k);
        return v ? v->u : dflt;
    }
};

// Appends `v`'s MessagePack encoding to `o` (msgpack-cxx's packer, core/msgpack.cpp): the smallest
// form of each value, as the server always wrote it: positive ints (`UInt`) as fixint / uint8..64,
// negative ones (`Int`) as negative fixint / int8..64, floats as float64, strings as fixstr / str8 /
// str16 / str32, arrays and maps as fix / 16 / 32. The replay corpora pin the bytes.
void mp_encode(const Value& v, std::vector<uint8_t>& o);

// `v`'s MessagePack encoding.
std::vector<uint8_t> mp_encode(const Value& v);

// Decodes one MessagePack value at `p` (advanced past it) with msgpack-cxx; Nil (and `p` left
// alone) on malformed or truncated input. Map keys become strings (an integer key its decimal
// spelling); bin / ext values, which the server never writes, decode as Nil. Used by server modules
// that re-read a core response (e.g. api/sphere211/sphere211.cpp wraps the core MissionStart).
Value mp_decode(const uint8_t*& p, const uint8_t* e);

// The one MessagePack value in `b` (Nil when malformed).
Value mp_decode(const std::vector<uint8_t>& b);

}  // namespace soa::server
