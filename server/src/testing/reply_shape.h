#pragma once
// Test helper (port code): a reply's shape, to pin the key order and types a handler sends where the
// replay corpora have no case (api/gen/README.md "Converting a handler").
#include <string>
#include <vector>

#include "soaserver/msgpack.h"
#include "soaserver/server.h"

namespace soa::server {

// A reply value's shape: each map's keys in order with their values' shapes, an array's first
// element's, a scalar's kind (u: unsigned, i: negative, b: bool, f: float, s: string). Pins the key
// order and types the client gets (api/gen/reply_types.txt) where the replay corpora have no case.
inline std::string shape(const Value& v) {
    switch (v.type) {
        case Value::Map: {
            std::string s = "{";
            for (const auto& [k, e] : v.map) s += (s.size() > 1 ? " " : "") + k + ":" + shape(e);
            return s + "}";
        }
        case Value::Arr:
            return "[" + (v.arr.empty() ? std::string() : shape(v.arr[0])) + "]";
        case Value::UInt:
            return "u";
        case Value::Int:
            return "i";
        case Value::Bool:
            return "b";
        case Value::Float:
            return "f";
        case Value::Str:
            return "s";
        default:
            return "nil";
    }
}
// data.<key>'s shape in the reply `body`.
inline std::string data_shape(const std::vector<u8>& body, const char* key) {
    Value d = body.empty() ? Value() : mp_decode(body);
    const Value* data = d.find("data");
    const Value* v = data ? data->find(key) : nullptr;
    return v ? shape(*v) : "(none)";
}

}  // namespace soa::server
