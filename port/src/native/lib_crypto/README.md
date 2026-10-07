# `lib_crypto`: the bundled OpenSSL pieces: the host libcrypto at the AES_* API

A subsystem of the native rebuild (port/PLAN.md task 6). The workflow (decompile, types, natives,
tests, Ghidra types): port/src/native/README.md "Per-subsystem workflow".

- Scope: the demangled-name patterns in [`port/decomp/lib_crypto/scope.txt`](../../../decomp/lib_crypto/scope.txt).
- Decompiles and the function list: [`port/decomp/lib_crypto/`](../../../decomp/lib_crypto/) (`symbols.tsv`; `tools/decomp.sh --into lib_crypto/<topic>`).
- Types: [`lib_crypto_layout.h`](lib_crypto_layout.h); for Ghidra, `tools/subsystem.py export-types lib_crypto` -> `port/decomp/lib_crypto/types.json`.
- Build settings of its own (a host library, a definition): none; a `subsystem.cmake` here would hold them (port/CMakeLists.txt includes it).

## Types (classes with their methods attached)

| Struct | Guest size | Found from | Status |
|---|---|---|---|
| `AesKey` (`AES_KEY`) | 0xf4 | OpenSSL 1.0's aes.h (no AES_LONG); `CEncryptAES128::Encrypt` / `Decrypt` keep one on the stack | typed; the host's in place |
| `CEncryptAES128` (`Encrypt::CEncryptAES128`) | 0x20 | `Initialize` (port/decomp/lib_crypto/encrypt_aes.c) | typed (the caller; not native) |

## Natives

3 functions, the AES API the game calls (only `Encrypt::CEncryptAES128::Encrypt` / `Decrypt`: the ADLD
AES layer, e.g. the master DB):

| Guest symbol | File | Differential tests | Live check |
|---|---|---|---|
| `private_AES_set_encrypt_key`, `private_AES_set_decrypt_key`, `AES_cbc_encrypt` | `lib_crypto_api.cpp` | `lib_crypto/aes`, `lib_crypto/master-db`, `lib_crypto/live-check` | 0 mismatches (3+ checks per flow: the master DB's decryption at login) |

`AES_set_encrypt_key` / `AES_set_decrypt_key` themselves are 4-byte branches through the PLT to
`private_AES_set_*_key` (too short to hook): those are the natives. `AES_encrypt` / `AES_decrypt` /
`CRYPTO_cbc128_*` have no caller outside the library.

**Host library:** vcpkg's OpenSSL 3 libcrypto, its low-level AES API (deprecated, still there). Its round
keys may be laid out differently (an assembler key schedule), which only the host functions see: the
game never reads the `AES_KEY` between the calls.

**Differential tests:** key schedules of 128 / 192 / 256 bits and invalid sizes (the results); CBC both
ways for every length class (whole blocks, partial final blocks, which both read whole, 0), separate and in
place (outputs and the updated IVs); the 3.7.0 master DB decrypted by `CEncryptAES128::Decrypt` and by the
natives (it starts with the `DCNE` header).

**Live check:** `--live-check lib_crypto`: each key the game sets gets a shadow made by the guest's own key
schedule; each `AES_cbc_encrypt` runs on it too, into copies; output bytes and IVs compared.

**Guest time:** 1,700 samples (0.6%) before, 0 after.

## Dependencies

None (a leaf).
