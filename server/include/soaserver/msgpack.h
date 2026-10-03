#pragma once
// A small MessagePack value tree and encoder for the local server's responses (port code, not
// guest behaviour). Maps keep insertion order; the game's ASON reader doesn't care about order.
#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <memory>
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
    Value(int64_t v) : type(v < 0 ? Int : UInt), i(v), u(v < 0 ? 0 : (uint64_t)v) {}
    Value(unsigned v) : type(UInt), u(v) {}
    Value(unsigned long v) : type(UInt), u(v) {}
    Value(unsigned long long v) : type(UInt), u(v) {}
    Value(long long v) : Value((int64_t)v) {}
    Value(double v) : type(Float), f(v) {}
    Value(const char* v) : type(Str), s(v) {}
    Value(std::string v) : type(Str), s(std::move(v)) {}

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

inline void mp_put_be(std::vector<uint8_t>& o, uint64_t v, int n) {
    for (int k = n - 1; k >= 0; k--) o.push_back((uint8_t)(v >> (8 * k)));
}

inline void mp_encode(const Value& v, std::vector<uint8_t>& o) {
    switch (v.type) {
        case Value::Nil:
            o.push_back(0xc0);
            break;
        case Value::Bool:
            o.push_back(v.b ? 0xc3 : 0xc2);
            break;
        case Value::UInt:
            if (v.u < 0x80) o.push_back((uint8_t)v.u);
            else if (v.u <= 0xff) {
                o.push_back(0xcc);
                mp_put_be(o, v.u, 1);
            } else if (v.u <= 0xffff) {
                o.push_back(0xcd);
                mp_put_be(o, v.u, 2);
            } else if (v.u <= 0xffffffffull) {
                o.push_back(0xce);
                mp_put_be(o, v.u, 4);
            } else {
                o.push_back(0xcf);
                mp_put_be(o, v.u, 8);
            }
            break;
        case Value::Int:
            if (v.i >= -32) o.push_back((uint8_t)(int8_t)v.i);
            else if (v.i >= -128) {
                o.push_back(0xd0);
                mp_put_be(o, (uint64_t)v.i, 1);
            } else if (v.i >= -32768) {
                o.push_back(0xd1);
                mp_put_be(o, (uint64_t)v.i, 2);
            } else if (v.i >= -2147483648ll) {
                o.push_back(0xd2);
                mp_put_be(o, (uint64_t)v.i, 4);
            } else {
                o.push_back(0xd3);
                mp_put_be(o, (uint64_t)v.i, 8);
            }
            break;
        case Value::Float: {
        // float64 (as python msgpack writes the generator's floats)
            o.push_back(0xcb);
            uint64_t bits;
            static_assert(sizeof(double) == 8);
            __builtin_memcpy(&bits, &v.f, 8);
            mp_put_be(o, bits, 8);
            break;
        }
        case Value::Str: {
            size_t n = v.s.size();
            if (n < 32) o.push_back((uint8_t)(0xa0 | n));
            else if (n <= 0xff) {
                o.push_back(0xd9);
                mp_put_be(o, n, 1);
            } else if (n <= 0xffff) {
                o.push_back(0xda);
                mp_put_be(o, n, 2);
            } else {
                o.push_back(0xdb);
                mp_put_be(o, n, 4);
            }
            o.insert(o.end(), v.s.begin(), v.s.end());
            break;
        }
        case Value::Arr: {
            size_t n = v.arr.size();
            if (n < 16) o.push_back((uint8_t)(0x90 | n));
            else if (n <= 0xffff) {
                o.push_back(0xdc);
                mp_put_be(o, n, 2);
            } else {
                o.push_back(0xdd);
                mp_put_be(o, n, 4);
            }
            for (auto& e : v.arr) mp_encode(e, o);
            break;
        }
        case Value::Map: {
            size_t n = v.map.size();
            if (n < 16) o.push_back((uint8_t)(0x80 | n));
            else if (n <= 0xffff) {
                o.push_back(0xde);
                mp_put_be(o, n, 2);
            } else {
                o.push_back(0xdf);
                mp_put_be(o, n, 4);
            }
            for (auto& e : v.map) {
                mp_encode(Value(e.first), o);
                mp_encode(e.second, o);
            }
            break;
        }
    }
}

inline std::vector<uint8_t> mp_encode(const Value& v) {
    std::vector<uint8_t> o;
    mp_encode(v, o);
    return o;
}

// Decodes one MessagePack value at `p` (advanced past it); Nil on malformed input. Used by server
// modules that re-read a core response (e.g. api/sphere211/sphere211.cpp wraps the core MissionStart).
inline uint64_t mp_get_be(const uint8_t*& p, const uint8_t* e, int n) {
    uint64_t v = 0;
    for (int k = 0; k < n && p < e; k++) v = (v << 8) | *p++;
    return v;
}
inline Value mp_decode(const uint8_t*& p, const uint8_t* e) {
    if (p >= e) return Value();
    uint8_t t = *p++;
    auto str = [&](size_t n) {
        Value v(std::string((const char*)p, (size_t)std::min<ptrdiff_t>(n, e - p)));
        p += std::min<ptrdiff_t>(n, e - p);
        return v;
    };
    auto arr = [&](size_t n) {
        Value v = Value::array();
        for (size_t k = 0; k < n && p < e; k++) v.push(mp_decode(p, e));
        return v;
    };
    auto map = [&](size_t n) {
        Value v = Value::object();
        for (size_t k = 0; k < n && p < e; k++) {
            Value key = mp_decode(p, e);
            std::string ks = key.type == Value::Str ? key.s : std::to_string(key.type == Value::Int ? key.i : (int64_t)key.u);
            v.map.emplace_back(ks, mp_decode(p, e));
        }
        return v;
    };
    if (t < 0x80) return Value((unsigned)t);
    if (t >= 0xe0) return Value((int)(int8_t)t);
    if ((t & 0xe0) == 0xa0) return str(t & 0x1f);
    if ((t & 0xf0) == 0x90) return arr(t & 0x0f);
    if ((t & 0xf0) == 0x80) return map(t & 0x0f);
    switch (t) {
        case 0xc0:
            return Value();
        case 0xc2:
            return Value(false);
        case 0xc3:
            return Value(true);
        case 0xcc:
            return Value((unsigned long long)mp_get_be(p, e, 1));
        case 0xcd:
            return Value((unsigned long long)mp_get_be(p, e, 2));
        case 0xce:
            return Value((unsigned long long)mp_get_be(p, e, 4));
        case 0xcf:
            return Value((unsigned long long)mp_get_be(p, e, 8));
        case 0xd0:
            return Value((int64_t)(int8_t)mp_get_be(p, e, 1));
        case 0xd1:
            return Value((int64_t)(int16_t)mp_get_be(p, e, 2));
        case 0xd2:
            return Value((int64_t)(int32_t)mp_get_be(p, e, 4));
        case 0xd3:
            return Value((int64_t)mp_get_be(p, e, 8));
        case 0xca: {
            uint32_t b = (uint32_t)mp_get_be(p, e, 4);
            float f;
            __builtin_memcpy(&f, &b, 4);
            return Value((double)f);
        }
        case 0xcb: {
            uint64_t b = mp_get_be(p, e, 8);
            double d;
            __builtin_memcpy(&d, &b, 8);
            return Value(d);
        }
        case 0xd9:
            return str(mp_get_be(p, e, 1));
        case 0xda:
            return str(mp_get_be(p, e, 2));
        case 0xdb:
            return str(mp_get_be(p, e, 4));
        case 0xdc:
            return arr(mp_get_be(p, e, 2));
        case 0xdd:
            return arr(mp_get_be(p, e, 4));
        case 0xde:
            return map(mp_get_be(p, e, 2));
        case 0xdf:
            return map(mp_get_be(p, e, 4));
        default:
            return Value();
    }
}
inline Value mp_decode(const std::vector<uint8_t>& b) {
    const uint8_t* p = b.data();
    return mp_decode(p, b.data() + b.size());
}

}  // namespace soa::server
