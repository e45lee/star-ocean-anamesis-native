// Reference implementation of the game RPC's per-message encryption ("Ninja": the sqex
// encryption library inside libSOA.so, class Aska::Cryption::Ninja). Pure C++ + OpenSSL
// (libcrypto: SHA-256 and the AES, Camellia, Blowfish, CAST5 and SEED block functions, in
// ninja_ciphers_ossl.cpp); the ciphers OpenSSL 3 lacks (IDEA, MARS, MISTY1, Serpent, Twofish)
// are ninja_<name>.cpp. No guest dependencies. Build: all of server/net/ninja/ninja_*.cpp, -lcrypto.
//
// Verified byte-for-byte against the client's own ARM64 code (server/tests/ninja/tools/ninja_client.py
// runs it under unicorn; vectors in server/tests/ninja/ninja_vectors.txt, checked by
// server/tests/ninja/ninja_check.cpp; run in soa-server --selftest "net/ninja"). Format: docs/online-server.md §3 "Encryption (Ninja)".
//
// For the server:
//   - key = the first 32 bytes of the bridge's `sharedSecurityKey` JSON string (the client's
//     KeyStore copies exactly 32 bytes; issue a string of >= 32 printable characters, since a
//     key whose first byte is 0 counts as "no key" and every encrypted call then fails -0x3b3).
//   - Client requests: the body after the 24-byte packet header is one envelope; decrypt() it.
//     The client picks the algorithm at random per message (all ten occur), so decrypt() must
//     (and does) handle every one.
//   - Replies: encrypt() the body (u32 length + ASON blob) with any algorithm; kAES128 is the
//     simplest. r2 and salt are free (the client reads them from the envelope); vary them per
//     message if you like.
//   - The packet header flags byte of an encrypted reply MUST carry 0x80: Deserialize only
//     reserves room for the plaintext when it is set (without it Get<Api>Res fails -0x3eb).
//     The SHA-1 trailer covers the packet as sent (header + envelope).
//   - Replies to encrypted requests must be encrypted: the Get<Api>Res helpers decrypt any
//     non-empty body and don't look at the flag.
#pragma once
#include <cstddef>
#include <cstdint>
#include <vector>

namespace ninja {

// Algorithm ids as they appear in the envelope (sqex::SqexEncryptionCreator).
enum Alg : uint32_t {
    kSEED = 0x01e6ac1b,
    kAES128 = 0x021d4314,
    kBlowfish = 0x03478caf,
    kCAST128 = 0x048a4dfe,
    kCamellia128 = 0x052e3a67,
    kSerpent = 0x07fedca9,
    kTwofish = 0x08a723ab,
    kIDEA = 0x0951fad3,
    kMARS = 0x0a325482,
    kMISTY1 = 0x0b46b571,
};
extern const uint32_t kAllAlgs[10];
const char* alg_name(uint32_t alg);  // nullptr for an unknown id

constexpr size_t kKeySize = 32;      // sharedSecurityKey
constexpr size_t kHeaderSize = 24;   // envelope header
constexpr size_t kTrailerSize = 32;  // keyed SHA-256 (obfuscated)

// Decrypt results. On the client every rejected envelope (bad signature, version or trailer,
// i.e. any modified byte) makes Get<Api>Res fail with status -0x3b8; an algorithm id outside
// Alg makes the client dereference a null algorithm object, so never send one.
enum Error : int {
    kOk = 0,
    kErrBadEnvelope = 1,  // too short, bad signature or version, unknown algorithm
    kErrMac = 3,          // trailer mismatch (the client's error 3 -> -0x3b8)
    kErrLength = 5,       // ciphertext not a whole number of blocks, or length word too large
};

// Encrypts `n` (> 0) bytes into an envelope: header(24) | BE32(n ^ m) | CBC(pad(plain)) | trailer(32).
//   alg   one of Alg.
//   r2    the per-message parameter (seeds the IV generator; the client draws it at random).
//   salt  header mask (the client uses low32(output buffer address) + r2).
std::vector<uint8_t> encrypt(const uint8_t key[kKeySize], uint32_t alg, uint32_t r2, uint32_t salt,
                             const uint8_t* plain, size_t n);

// Decrypts an envelope. Returns kOk and the plaintext, or an Error. `alg_out` (optional)
// receives the algorithm id read from the header.
int decrypt(const uint8_t key[kKeySize], const uint8_t* env, size_t n, std::vector<uint8_t>* plain,
            uint32_t* alg_out = nullptr);

// Header fields (for logging / tests).
struct Header {
    uint32_t salt, signature, version, alg, r2, mt;
};
bool parse_header(const uint8_t* env, size_t n, Header* h);

}  // namespace ninja
