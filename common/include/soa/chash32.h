#pragma once
// Framework::CHash32 (part of soa_codec; the game's string hash): CRC-32 (reflected, poly
// 0xEDB88320) seeded with the input length, no final inversion; empty input hashes to 0. The ADLD
// keys (soa/adld.h) are made from it; the server derives player ids and BGM hashes with it; the
// port's debug commands and fake API use it. (The port's `hash` natives are the game's own code,
// separately: port/src/native/hash/.) Python: soa_save.adld.chash32.
#include <cstddef>
#include <cstdint>

namespace soa {

// The client's CHash32 of `len` bytes at `data`, and of a C string.
uint32_t chash32(const void* data, size_t len);
uint32_t chash32(const char* s);  // nullptr -> 0

}  // namespace soa
