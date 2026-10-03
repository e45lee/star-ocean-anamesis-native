# server/net/ninja: the Ninja envelope and its ciphers

The Square Enix "Ninja" message envelope every encrypted request and reply of the 3.7.0 client is wrapped in, and the ten block ciphers it can use. Part of `libsoanet` (soa-server only). The format is described in `docs/online-server.md` §3 "Encryption (Ninja)".

| File | What |
|---|---|
| `ninja_ref.{h,cpp}` | the envelope: `ninja::decrypt` (all ten algorithms), `ninja::encrypt` (soa-server replies in AES-128) |
| `ninja_ciphers.h` | internal to `ninja_ref.cpp`: the ten block ciphers' interface |
| `ninja_ciphers_ossl.cpp` | AES, Camellia, Blowfish, CAST5 and SEED over OpenSSL 3's block functions (SEED's key schedule our own) |
| `ninja_idea.cpp`, `ninja_mars.cpp`, `ninja_misty1.cpp`, `ninja_serpent.cpp`, `ninja_twofish.cpp` | the ciphers OpenSSL 3 lacks, ported from the client with its quirks (e.g. MARS's original 1998 key schedule) |

This is data-like code: it is not reformatted (`server/.clang-format-ignore`), and its `@` constants are cipher tables, not client addresses (`tools/server_evidence.py` counts them apart). It is checked byte for byte against the client's own ARM64 code: `../../tests/ninja/` (700 envelopes the client made, `soa-server --selftest "net/ninja"`; `ninja_check.sh` builds a stand-alone checker; `tools/` regenerates the vectors under unicorn from `work/`'s lib).
