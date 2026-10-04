// AES on the host's libcrypto, at the API the game calls (lib_crypto_api.h, README.md).
//
// --live-check lib_crypto runs the guest's OpenSSL beside it (native/common/lockstep.h): each key the
// game sets gets a shadow AES_KEY made by the guest's own key schedule, each AES_cbc_encrypt runs on
// it too (into a scratch copy of the output, with a copy of the IV), and the output bytes and the
// updated IV are compared. The guest's AES_set_decrypt_key calls its AES_set_encrypt_key on the
// shadow: forwarded to the original.
#include "native/lib_crypto/lib_crypto_api.h"

#define OPENSSL_SUPPRESS_DEPRECATED  // the low-level AES API (deprecated in OpenSSL 3, still there)
#include <openssl/aes.h>

#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "core/cpu.h"
#include "native/common/native.h"

namespace soa::native::lib_crypto {

static_assert(sizeof(AES_KEY) == sizeof(AesKey) && offsetof(AES_KEY, rounds) == offsetof(AesKey, rounds));

namespace {

struct Originals {
    u64 set_encrypt, set_decrypt, cbc;
} orig;

live::Lockstep g_check("lib_crypto");

template <typename T>
u64 a(T* p) { return (u64)(uintptr_t)p; }
bool checking() { return g_check.active(); }
// A call the guest library makes on its own state during a shadow run: forwarded to the original.
bool forwarding() { return live::in_shadow_run(); }
void verdict(const char* fn, bool good, const char* fmt, ...) __attribute__((format(printf, 3, 4)));
void verdict(const char* fn, bool good, const char* fmt, ...) {
    if (!g_check.chosen(fn)) return;
    if (good) return g_check.ok(fn);
    char b[256];
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(b, sizeof b, fmt, ap);
    va_end(ap);
    g_check.bad(fn, "%s", b);
}
s32 gi(u64 r) { return (s32)(u32)r; }

s32 set_key(const char* fn, u64 o, int (*host)(const unsigned char*, int, AES_KEY*), const u8* user_key, s32 bits, AesKey* key) {
    if (forwarding()) return gi(guest_call(o, {a(user_key), (u64)(u32)bits, a(key)}));
    s32 r = host(user_key, bits, (AES_KEY*)key);
    if (checking() && key) {
        // the guest's schedule into the key's shadow (a stack slot reused for every call: made afresh)
        g_check.drop(a(key));
        u64 s = g_check.shadow(a(key), sizeof(AesKey));
        s32 g = gi(live::shadow_call(o, {a(user_key), (u64)(u32)bits, s}));
        verdict(fn, g == r, "result %d, guest %d", r, g);
    }
    return r;
}

}  // namespace

s32 set_encrypt_key(const u8* user_key, s32 bits, AesKey* key) {
    return set_key("AES_set_encrypt_key", orig.set_encrypt, AES_set_encrypt_key, user_key, bits, key);
}
s32 set_decrypt_key(const u8* user_key, s32 bits, AesKey* key) {
    return set_key("AES_set_decrypt_key", orig.set_decrypt, AES_set_decrypt_key, user_key, bits, key);
}

void cbc_encrypt(const u8* in, u8* out, u64 length, const AesKey* key, u8* ivec, s32 enc) {
    if (forwarding()) return (void)guest_call(orig.cbc, {a(in), a(out), length, a(key), a(ivec), (u64)(u32)enc});
    u64 s = checking() ? g_check.find(a(key)) : 0;
    // the guest's run: copies of the input (in may be out), the output, the IV; a partial final block
    // is read whole (16 bytes) by both, and written whole when encrypting
    u64 span = (length + 15) & ~15ull;
    u8 *gin = nullptr, *gout = nullptr, *giv = nullptr;
    if (s) {
        gin = (u8*)malloc(span + 16), gout = (u8*)malloc(span + 16), giv = (u8*)malloc(16);
        memcpy(gin, in, span), memcpy(gout, out, span), memcpy(giv, ivec, 16);
    }
    AES_cbc_encrypt(in, out, (size_t)length, (const AES_KEY*)key, ivec, enc);
    if (s) {
        live::shadow_call(orig.cbc, {a(gin), a(gout), length, s, a(giv), (u64)(u32)enc});
        u64 wrote = enc ? span : length;
        bool same = !memcmp(gout, out, wrote) && !memcmp(giv, ivec, 16);
        verdict("AES_cbc_encrypt", same, "%s %llu bytes: %s differ", enc ? "encrypting" : "decrypting", (unsigned long long)length,
                memcmp(gout, out, wrote) ? "the output bytes" : "the IVs");
        free(gin), free(gout), free(giv);
    }
}

namespace {
struct Bound {
    const char* sym;
    HostFn fn;
    u64* orig;
};
const Bound kBound[] = {
    {"private_AES_set_encrypt_key", wrap<&set_encrypt_key>(), &orig.set_encrypt},
    {"private_AES_set_decrypt_key", wrap<&set_decrypt_key>(), &orig.set_decrypt},
    {"AES_cbc_encrypt", wrap<&cbc_encrypt>(), &orig.cbc},
};
bool register_all() {
    for (const Bound& b : kBound) register_native_function({b.sym, b.fn, "lib_crypto: host libcrypto (AES)", nullptr, b.orig});
    return true;
}
const bool g_registered = register_all();
}  // namespace

live::Lockstep& lockstep() { return g_check; }
void use_originals(u64 (*sym)(const char*)) {
    for (const Bound& b : kBound) *b.orig = sym ? sym(b.sym) : 0;
}

}  // namespace soa::native::lib_crypto
