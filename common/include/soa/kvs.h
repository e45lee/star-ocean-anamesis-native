#pragma once
// The game's Game.xml / Aska.xml: Aska::LocalKVS SharedPreferences files (soa_codec;
// common/src/kvs.cpp; the layout is the client's, soa_save/kvs.py documents it). Each entry is a
// <string> whose name is Aska's Base64 (base64::aska_name) of ChaCha20(key) and whose text is
// Android's Base64.DEFAULT of ChaCha20(value) plus four spaces, with one fixed key and nonce.
// Users: the server's seed save (server/src/state/kvs.h forwards here) and platform370's
// --voice-lang (BAS:VoiceLanguage written before the client starts).
#include <string>
#include <string_view>
#include <utility>
#include <vector>

namespace soa::kvs {

using Pairs = std::vector<std::pair<std::string, std::string>>;  // key, value (plain bytes)

// ChaCha20 with the game's key and nonce (its own inverse).
std::string crypt(std::string_view bytes);
// A key as the file's entry name / a value as the entry's text.
std::string encode_name(std::string_view key);
std::string encode_value(std::string_view value);
// The plain bytes of an entry's name / text (any Base64 spelling).
std::string decode(std::string_view text);

// The key / value pairs of the file at `path`, in file order (empty when it can't be read).
Pairs read(const std::string& path);
// Writes the pairs as the game writes them, through a temporary file and a rename (true when written).
bool write(const std::string& path, const Pairs& kv);

}  // namespace soa::kvs
