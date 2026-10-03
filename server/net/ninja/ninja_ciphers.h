// Internal to ninja_ref.cpp: the ten block ciphers of the sqex library, each with the exact
// CBC loop of its client class (the classes differ in block/word byte order and in what the
// chaining state holds; see the notes on each implementation).
#pragma once
#include <cstddef>
#include <cstdint>
#include <memory>

namespace ninja::detail {

struct Cipher {
    size_t block = 16;  // bytes
    virtual ~Cipher() = default;
    // `iv`: the block/4 IV words as the class draws them from its generator, in order.
    // `data`, `n`: the padded plaintext (after the 4-byte length word), n a multiple of block.
    virtual void encrypt_cbc(const uint32_t* iv, uint8_t* data, size_t n) const = 0;
    virtual void decrypt_cbc(const uint32_t* iv, uint8_t* data, size_t n) const = 0;
};

// `key`: the 32-byte session key (Blowfish uses all of it, the others the first 16 bytes).
std::unique_ptr<Cipher> make_aes128(const uint8_t* key);
std::unique_ptr<Cipher> make_camellia128(const uint8_t* key);
std::unique_ptr<Cipher> make_blowfish(const uint8_t* key);
std::unique_ptr<Cipher> make_cast128(const uint8_t* key);
std::unique_ptr<Cipher> make_seed(const uint8_t* key);
std::unique_ptr<Cipher> make_idea(const uint8_t* key);
std::unique_ptr<Cipher> make_mars(const uint8_t* key);
std::unique_ptr<Cipher> make_misty1(const uint8_t* key);
std::unique_ptr<Cipher> make_serpent(const uint8_t* key);
std::unique_ptr<Cipher> make_twofish(const uint8_t* key);

inline uint32_t load_be32(const uint8_t* p) {
    return (uint32_t)p[0] << 24 | (uint32_t)p[1] << 16 | (uint32_t)p[2] << 8 | p[3];
}
inline void store_be32(uint8_t* p, uint32_t v) {
    p[0] = (uint8_t)(v >> 24), p[1] = (uint8_t)(v >> 16), p[2] = (uint8_t)(v >> 8), p[3] = (uint8_t)v;
}
inline uint32_t load_le32(const uint8_t* p) {
    return (uint32_t)p[3] << 24 | (uint32_t)p[2] << 16 | (uint32_t)p[1] << 8 | p[0];
}
inline void store_le32(uint8_t* p, uint32_t v) {
    p[0] = (uint8_t)v, p[1] = (uint8_t)(v >> 8), p[2] = (uint8_t)(v >> 16), p[3] = (uint8_t)(v >> 24);
}
inline uint32_t rotl32(uint32_t v, unsigned n) { n &= 31; return n ? v << n | v >> (32 - n) : v; }
inline uint32_t rotr32(uint32_t v, unsigned n) { n &= 31; return n ? v >> n | v << (32 - n) : v; }

}  // namespace ninja::detail
