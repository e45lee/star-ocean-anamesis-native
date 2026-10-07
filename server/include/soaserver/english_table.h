#pragma once
// An English text table (docs/server-rules.md#english): message_id -> the English to serve, the
// SHA-1 of the Japanese it translates and its source. The tables' file form and rules are
// server/src/master/english_text.h's; this header only holds the type, for cdn.h.
#include <map>
#include <string>

namespace soa::server::english {

struct Entry {
    std::string ja_sha1;  // "" = a new id: inserted, never matched against a Japanese row
    std::string en;
    std::string source;
};
using Table = std::map<std::string, Entry>;  // by message_id

}  // namespace soa::server::english
