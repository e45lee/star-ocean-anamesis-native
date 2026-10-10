// The MessagePack codec of soaserver/msgpack.h over msgpack-cxx (vcpkg `msgpack`, header-only,
// without Boost). The encoder picks the same forms the server's own encoder did (the header says
// which); the replay corpora (server/tests/replay/) pin the bytes.
#include "soaserver/msgpack.h"

#include <msgpack.hpp>

namespace soa::server {

namespace {

// msgpack-cxx's packer writes to a stream with write(const char*, size_t).
struct VectorSink {
    std::vector<uint8_t>& out;
    void write(const char* p, size_t n) { out.insert(out.end(), (const uint8_t*)p, (const uint8_t*)p + n); }
};

void pack(msgpack::packer<VectorSink>& pk, const Value& v) {
    switch (v.type) {
        case Value::Nil:
            pk.pack_nil();
            break;
        case Value::Bool:
            v.b ? pk.pack_true() : pk.pack_false();
            break;
        case Value::UInt:
            pk.pack_uint64(v.u);  // fixint, 0xcc, 0xcd, 0xce, 0xcf: the smallest
            break;
        case Value::Int:
            pk.pack_int64(v.i);  // a negative value: fixint >= -32, 0xd0, 0xd1, 0xd2, 0xd3
            break;
        case Value::Float:
            pk.pack_double(v.f);  // always float64 (as python msgpack writes the generator's floats)
            break;
        case Value::Str:
            pk.pack_str((uint32_t)v.s.size());  // fixstr < 32, str8 (0xd9) < 256, str16, str32
            pk.pack_str_body(v.s.data(), (uint32_t)v.s.size());
            break;
        case Value::Arr:
            pk.pack_array((uint32_t)v.arr.size());
            for (const Value& e : v.arr) pack(pk, e);
            break;
        case Value::Map:
            pk.pack_map((uint32_t)v.map.size());
            for (const auto& [key, value] : v.map) {
                pk.pack_str((uint32_t)key.size());
                pk.pack_str_body(key.data(), (uint32_t)key.size());
                pack(pk, value);
            }
            break;
    }
}

Value from_object(const msgpack::object& o) {
    switch (o.type) {
        case msgpack::type::BOOLEAN:
            return Value(o.via.boolean);
        case msgpack::type::POSITIVE_INTEGER:
            return Value((unsigned long long)o.via.u64);
        case msgpack::type::NEGATIVE_INTEGER:
            return Value((long long)o.via.i64);
        case msgpack::type::FLOAT32:
        case msgpack::type::FLOAT64:
            return Value(o.via.f64);
        case msgpack::type::STR:
            return Value(std::string(o.via.str.ptr, o.via.str.size));
        case msgpack::type::ARRAY: {
            Value v = Value::array();
            v.arr.reserve(o.via.array.size);
            for (uint32_t k = 0; k < o.via.array.size; k++) v.arr.push_back(from_object(o.via.array.ptr[k]));
            return v;
        }
        case msgpack::type::MAP: {
            Value v = Value::object();
            v.map.reserve(o.via.map.size);
            for (uint32_t k = 0; k < o.via.map.size; k++) {
                const msgpack::object& key = o.via.map.ptr[k].key;
                // a string key as is, an integer key in decimal (any other key reads as "0")
                std::string ks = key.type == msgpack::type::STR                ? std::string(key.via.str.ptr, key.via.str.size)
                                 : key.type == msgpack::type::NEGATIVE_INTEGER ? std::to_string(key.via.i64)
                                 : key.type == msgpack::type::POSITIVE_INTEGER ? std::to_string((int64_t)key.via.u64)
                                                                               : std::string("0");
                v.map.emplace_back(std::move(ks), from_object(o.via.map.ptr[k].val));
            }
            return v;
        }
        default:  // nil; bin and ext have no Value
            return Value();
    }
}

}  // namespace

void mp_encode(const Value& v, std::vector<uint8_t>& o) {
    VectorSink sink{o};
    msgpack::packer<VectorSink> pk(sink);
    pack(pk, v);
}

std::vector<uint8_t> mp_encode(const Value& v) {
    std::vector<uint8_t> o;
    mp_encode(v, o);
    return o;
}

Value mp_decode(const uint8_t*& p, const uint8_t* e) {
    if (p >= e) return Value();
    size_t off = 0;
    try {
        // Nesting deeper than kMaxDepth throws (msgpack::depth_size_overflow): from_object, pack and
        // ~Value recurse once per level, so a peer's 0x91 0x91 ... would otherwise overflow the stack.
        // The game's documents nest a few levels.
        constexpr size_t kMaxDepth = 256;
        const msgpack::unpack_limit limit(0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, kMaxDepth);
        msgpack::object_handle h = msgpack::unpack((const char*)p, (size_t)(e - p), off, nullptr, nullptr, limit);
        Value v = from_object(h.get());
        p += off;
        return v;
    } catch (const std::exception&) {  // msgpack::unpack_error (malformed, truncated, too deep), std::bad_alloc
        return Value();
    }
}

Value mp_decode(const std::vector<uint8_t>& b) {
    const uint8_t* p = b.data();
    return mp_decode(p, b.data() + b.size());
}

}  // namespace soa::server
