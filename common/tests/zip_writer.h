#pragma once
// Test helper (soa_zip_tests, soa_gamefiles_tests): writes small synthetic ZIP archives (no ZIP64)
// for the readers' tests to read back.
#include <zlib.h>

#include <cstdint>
#include <string>
#include <vector>

namespace soa::ziptest {

using Bytes = std::vector<uint8_t>;
inline void put16(Bytes& b, uint32_t v) { b.push_back(v & 0xff), b.push_back((v >> 8) & 0xff); }
inline void put32(Bytes& b, uint32_t v) { put16(b, v & 0xffff), put16(b, v >> 16); }
inline void put64(Bytes& b, uint64_t v) { put32(b, (uint32_t)v), put32(b, (uint32_t)(v >> 32)); }
inline void append(Bytes& b, const void* p, size_t n) { b.insert(b.end(), (const uint8_t*)p, (const uint8_t*)p + n); }
inline void append(Bytes& b, const std::string& s) { append(b, s.data(), s.size()); }

inline Bytes deflate_raw(const Bytes& in) {
    z_stream zs{};
    deflateInit2(&zs, 9, Z_DEFLATED, -MAX_WBITS, 8, Z_DEFAULT_STRATEGY);
    Bytes out(deflateBound(&zs, in.size()) + 16);
    zs.next_in = (Bytef*)in.data();
    zs.avail_in = (uInt)in.size();
    zs.next_out = out.data();
    zs.avail_out = (uInt)out.size();
    deflate(&zs, Z_FINISH);
    out.resize(zs.total_out);
    deflateEnd(&zs);
    return out;
}

struct Member {
    std::string name;
    Bytes data;
    bool deflate = false;
};
// A plain zip (no ZIP64) of the members, in order.
inline Bytes make_zip(const std::vector<Member>& ms) {
    Bytes z, cd;
    for (auto& m : ms) {
        Bytes body = m.deflate ? deflate_raw(m.data) : m.data;
        uint32_t crc = (uint32_t)crc32(0, m.data.data(), (uInt)m.data.size());
        uint32_t at = (uint32_t)z.size();
        put32(z, 0x04034b50), put16(z, 20), put16(z, 0), put16(z, m.deflate ? 8 : 0), put16(z, 0), put16(z, 0);
        put32(z, crc), put32(z, (uint32_t)body.size()), put32(z, (uint32_t)m.data.size());
        put16(z, (uint32_t)m.name.size()), put16(z, 4);
        append(z, m.name);
        put16(z, 0xcafe), put16(z, 0);  // an (empty) extra field: the data starts after it
        append(z, body.data(), body.size());
        put32(cd, 0x02014b50), put16(cd, 20), put16(cd, 20), put16(cd, 0), put16(cd, m.deflate ? 8 : 0), put16(cd, 0), put16(cd, 0);
        put32(cd, crc), put32(cd, (uint32_t)body.size()), put32(cd, (uint32_t)m.data.size());
        put16(cd, (uint32_t)m.name.size()), put16(cd, 0), put16(cd, 0), put16(cd, 0), put16(cd, 0), put32(cd, 0), put32(cd, at);
        append(cd, m.name);
    }
    uint32_t cd_off = (uint32_t)z.size();
    append(z, cd.data(), cd.size());
    put32(z, 0x06054b50), put16(z, 0), put16(z, 0), put16(z, (uint32_t)ms.size()), put16(z, (uint32_t)ms.size());
    put32(z, (uint32_t)cd.size()), put32(z, cd_off), put16(z, 0);
    return z;
}

}  // namespace soa::ziptest
