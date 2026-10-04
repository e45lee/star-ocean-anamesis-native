#pragma once
// Framework::CHash32 (library code; the game's string hash): CRC-32 (reflected, poly 0xEDB88320)
// seeded with the input length, no final inversion; empty input hashes to 0. The server derives
// player ids and BGM hashes with it; the port's CHash32 natives (port/src/native/engine/
// asset_decrypt.*) use this implementation too.
#include <cstddef>
#include <cstdint>

namespace soa::server {

// The client's CHash32 of `len` bytes at `data`, and of a C string.
uint32_t chash32(const void* data, size_t len);
uint32_t chash32(const char* s);  // nullptr -> 0

}  // namespace soa::server
