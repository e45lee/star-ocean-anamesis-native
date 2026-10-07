// soa/chash32.h: Framework::CHash32 (moved here from soa-server's core/support.cpp).
#include "soa/chash32.h"

#include <cstring>

namespace soa {

namespace {
const uint32_t* crc_table() {
    static uint32_t t[256];
    static bool init = [] {
        for (uint32_t i = 0; i < 256; i++) {
            uint32_t c = i;
            for (int k = 0; k < 8; k++) c = (c & 1) ? (c >> 1) ^ 0xEDB88320u : c >> 1;
            t[i] = c;
        }
        return true;
    }();
    (void)init;
    return t;
}
}  // namespace

uint32_t chash32(const void* data, size_t len) {
    const uint32_t* t = crc_table();
    const auto* p = (const unsigned char*)data;
    uint32_t c = (uint32_t)len;
    if (len == 0) return 0;
    for (size_t i = 0; i < len; i++) c = t[(c ^ p[i]) & 0xff] ^ (c >> 8);
    return c;
}
uint32_t chash32(const char* s) { return s ? chash32(s, strlen(s)) : 0; }

}  // namespace soa
