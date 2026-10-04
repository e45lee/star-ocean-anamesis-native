// soa/base64.h (part of soa_codec_tests): the vectors of RFC 4648, the Game.xml spellings (names and
// values from port/server-data/test-seed.xml), the lenient decoder's skipping, and round trips.
#include <string>

#include <soa/base64.h>

#include "codec_check.h"

void base64_tests() {
    using namespace soa::base64;
    // RFC 4648 section 10
    const char* rfc[][2] = {{"", ""}, {"f", "Zg=="}, {"fo", "Zm8="}, {"foo", "Zm9v"}, {"foob", "Zm9vYg=="}, {"fooba", "Zm9vYmE="}, {"foobar", "Zm9vYmFy"}};
    for (auto& [plain, b64] : rfc) {
        codec_check(encode(plain) == b64, std::string("encode \"") + plain + "\"");
        codec_check(decode(b64) == plain, std::string("decode \"") + b64 + "\"");
    }
    codec_check(encode(std::string("\0\xff\xfe", 3)) == "AP/+", "encode binary (+ and /)");

    // Aska's names: "====" exactly when no padding was needed (test-seed.xml: 12, 11, 10 bytes)
    for (const char* name : {"Rka7znVJ5ahzkyQa====", "dGuJjUBX2793jAg=", "dGuJjUBX27RukQ=="}) {
        std::string raw = decode(name);
        codec_check(aska_name(raw) == name, std::string("aska_name round trip ") + name);
    }
    codec_check(decode("Rka7znVJ5ahzkyQa====").size() == 12, "the \"====\" quirk decodes as 12 bytes");
    codec_check(aska_name("") == "====", "aska_name of nothing: \"====\"");
    codec_check(aska_name("ab") == "YWI=" && aska_name("abc") == "YWJj====", "aska_name padding / quirk");

    // Android's DEFAULT: 76-column lines, each ending in "\n"; nothing for no bytes
    codec_check(android_default("") == "", "android_default of nothing: \"\"");
    codec_check(android_default("foob") == "Zm9vYg==\n", "android_default: one short line");
    std::string b57(57, 'x'), b58(58, 'x'), b200;
    for (int i = 0; i < 200; i++) b200.push_back((char)(i * 37));
    codec_check(android_default(b57) == encode(b57) + "\n", "57 bytes: exactly one 76-column line");
    std::string e58 = encode(b58);
    codec_check(android_default(b58) == e58.substr(0, 76) + "\n" + e58.substr(76) + "\n", "58 bytes: a second line");
    std::string a200 = android_default(b200), joined;
    bool cols = true;
    for (size_t p = 0; p < a200.size();) {
        size_t nl = a200.find('\n', p);
        if (nl == std::string::npos || (nl - p != 76 && a200.find('\n', nl + 1) != std::string::npos)) cols = false;
        if (nl == std::string::npos) break;
        joined += a200.substr(p, nl - p);
        p = nl + 1;
    }
    codec_check(cols && a200.back() == '\n' && joined == encode(b200), "200 bytes: 76-column lines, the last ending in \"\\n\"");

    // the lenient decoder: the stored text of a SharedPreferences value ("\n" + four spaces)
    codec_check(decode("SEirtWkVtOEm0G0=\n    ") == decode("SEirtWkVtOEm0G0="), "decode skips the line break and indentation");
    codec_check(decode(android_default(b200) + "    ") == b200, "decode(android_default) round trip, 200 bytes");
    codec_check(decode("Zm9v\nYmFy") == "foobar" && decode(" Z m 9 v ") == "foo", "decode skips inner whitespace");
    codec_check(decode("Zm9vY") == "foo", "a dangling 6 bits are dropped");
    codec_check(decode("Zm9vYm") == "foob" && decode("Zm9vYmE") == "fooba", "unpadded tails");
    codec_check(decode("=====") == "" && decode("") == "" && decode("&#;") == "", "nothing to decode");
    bool rt = true;
    for (size_t n = 0; n < 300; n++) {
        std::string s;
        for (size_t i = 0; i < n; i++) s.push_back((char)(i * 131 + n));
        if (decode(encode(s)) != s || decode(aska_name(s)) != s || decode(android_default(s)) != s) rt = false;
    }
    codec_check(rt, "round trips of 0..299 bytes, all three spellings");
}
