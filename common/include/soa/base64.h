#pragma once
// Base64 (soa_codec; common/src/base64.cpp), on OpenSSL's EVP_EncodeBlock / EVP_DecodeBlock, with the
// two spellings the game's save files use:
//   android_default  android.util.Base64 with DEFAULT flags: 76-column lines, each ending in "\n"
//                    (the SharedPreferences values: the runtime's prefs, the server's Game.xml)
//   aska_name        Aska's key names in Game.xml (Aska::LocalKVS): padded Base64, plus "===="
//                    when no padding was needed (the byte count is a multiple of 3; also when empty)
#include <string>
#include <string_view>

namespace soa::base64 {

// Standard padded Base64, one line.
std::string encode(std::string_view bytes);
std::string android_default(std::string_view bytes);
std::string aska_name(std::string_view bytes);

// Lenient: every character outside A-Z a-z 0-9 + / is skipped (line breaks, the indentation,
// padding, the "====" quirk), and trailing bits short of a byte are dropped. Decodes all three.
std::string decode(std::string_view text);

}  // namespace soa::base64
