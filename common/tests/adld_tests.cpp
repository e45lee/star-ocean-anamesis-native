// soa/chash32.h and soa/adld.h (part of soa_codec_tests): CHash32 against the bit-by-bit
// definition and known values, the keys, and ADLD round trips (XOR and AES with its DCNE header).
// The 3.7.0 files themselves are checked by soa-server's cdn/adld-roundtrip.
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

#include <soa/adld.h>
#include <soa/chash32.h>

#include "codec_check.h"

namespace {

// Framework::CHash32 as the guest computes it: reflected CRC-32 (0xEDB88320), bit by bit, the
// register seeded with the length, no final xor.
uint32_t chash32_reference(const std::string& s) {
    uint32_t c = (uint32_t)s.size();
    for (unsigned char b : s) {
        c ^= b;
        for (int k = 0; k < 8; k++) c = (c >> 1) ^ ((c & 1) ? 0xEDB88320u : 0);
    }
    return c;
}

}  // namespace

void adld_tests() {
    using soa::chash32;
    namespace adld = soa::adld;
    // CHash32 (soa_save.adld.chash32 has the same known value: tests/test_adld.py)
    codec_check(chash32("role_cc0050_b01a_6073") == 7715287u, "chash32 known value");
    codec_check(chash32("") == 0 && chash32((const char*)nullptr) == 0, "chash32 of empty / null");
    uint32_t seed = 7;
    bool same = true;
    for (int i = 0; i < 500; i++) {
        std::string s;
        for (int n = (int)((seed = seed * 1103515245u + 12345u) >> 26); n > 0; n--) s += (char)((seed = seed * 1103515245u + 12345u) >> 24);
        same &= chash32(s.data(), s.size()) == chash32_reference(s);
    }
    codec_check(same, "chash32 matches the bitwise definition");

    // the keys
    const std::string name = "Script/1000_010.msgp";
    char hex[16], dec[40];
    snprintf(hex, sizeof hex, "%x", chash32_reference(name));
    snprintf(dec, sizeof dec, "%032u", chash32_reference(name));
    codec_check(adld::xor_key(name.c_str()) == hex && adld::aes_key(name.c_str()) == dec, "xor_key / aes_key");

    // round trips, and the header / passthrough rules
    std::vector<uint8_t> plain(1000);
    for (size_t i = 0; i < plain.size(); i++) plain[i] = (uint8_t)(i * 31 + 7);
    for (uint32_t flags : {adld::kXor, adld::kAes}) {
        auto enc = adld::encrypt(name, plain, flags);
        std::string what = flags == adld::kXor ? " (XOR)" : " (AES)";
        codec_check(adld::is_adld(enc.data(), enc.size()) && adld::flags_of(enc.data(), enc.size()) == flags, "encrypt header" + what);
        codec_check(adld::decrypt(name, enc) == plain, "decrypt(encrypt(x)) == x" + what);
    }
    auto x = adld::encrypt(name, plain, adld::kXor);
    bool xor_ok = x.size() == plain.size() + 16;
    for (size_t i = 0; xor_ok && i < plain.size(); i++) xor_ok = x[16 + i] == (uint8_t)(plain[i] ^ hex[i % strlen(hex)]);
    codec_check(xor_ok, "XOR payload is the plain text XOR the repeating hex key");
    std::vector<uint8_t> raw = {1, 2, 3, 4};
    codec_check(adld::decrypt("x", raw) == raw && !adld::is_adld(raw.data(), raw.size()), "non-ADLD passthrough");
}
