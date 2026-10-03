#pragma once
// The GDB remote serial protocol's framing and encodings (core/gdbstub.cpp uses them; pure functions,
// tested by core/gdb_protocol_tests.cpp). Packets are "$<data>#<2 hex digit checksum>"; inside data,
// '$', '#', '}' and '*' are escaped as '}' followed by the byte XOR 0x20 (binary data, the X packet);
// replies may use run-length encoding ("*"), which we never send but decode.
#include <cstdint>
#include <optional>
#include <string>
#include <vector>

namespace soa::gdbrsp {

// "$data#cs" for a reply (data escaped).
std::string frame(const std::string& data);
// The checksum of data (sum of bytes mod 256).
uint8_t checksum(const std::string& data);

// Incremental packet reader over a byte stream.
struct Reader {
    std::string buf;
    // The next complete item: a packet's (unescaped) data, "\x03" for an interrupt byte; nullopt
    // when more bytes are needed. Acks ('+', '-') are skipped; *bad is set for a checksum mismatch
    // (the caller answers '-').
    std::optional<std::string> next(bool* bad = nullptr);
};

// Binary-data unescape ('}' x -> x ^ 0x20) and run-length expansion ("c*n": n - 29 more copies).
std::string unescape(const std::string& s);
std::string escape(const std::string& s);

std::string to_hex(const void* p, size_t n);
std::string to_hex(const std::string& s);
// Hex -> bytes; false on an odd length or a non-hex digit.
bool from_hex(const std::string& h, std::string& out);
// Little-endian value of `bytes` bytes as hex (register encodings).
std::string le_hex(uint64_t v, int bytes);
uint64_t le_from_hex(const std::string& h);
// Parses a hex number at s[i..] (advancing i); false when there is none.
bool parse_hex(const std::string& s, size_t& i, uint64_t& v);

// "vCont;s:1f;c" -> actions (an empty tid = the default for every thread not named).
struct VContAction {
    char op;      // 'c', 's', 't' (C / S are mapped to c / s; their signal is ignored)
    int tid;      // -1 = default
};
bool parse_vcont(const std::string& p, std::vector<VContAction>& out);

}  // namespace soa::gdbrsp
