// Differential tests of lib_crypto: AES key schedules and CBC through the guest's OpenSSL 1.0 (t.call
// on the original code) and the natives (the host's libcrypto): results, output bytes and updated IVs,
// for every length (partial final blocks too), both directions; and the game's own use, an AES ADLD
// file (the master DB) decrypted by Encrypt::CEncryptAES128::Decrypt and by the natives.
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

#include "native/common/test.h"
#include "native/common/test_assets.h"
#include "native/lib_crypto/lib_crypto_api.h"
#include "soaserver/adld.h"

namespace soa::native::lib_crypto {
namespace {

template <typename T>
u64 A(T* p) { return (u64)(uintptr_t)p; }

NATIVE_TEST("lib_crypto/aes") {
    auto* gk = (AesKey*)calloc(1, sizeof(AesKey) + 16);
    auto* hk = (AesKey*)calloc(1, sizeof(AesKey) + 16);
    u8* user = (u8*)calloc(1, 64);
    for (int bits : {128, 192, 256, 64, 0, 129}) {
        for (int i = 0; i < 32; i++) user[i] = (u8)t.rand_int(0, 255);
        for (int dec : {0, 1}) {
            s32 g = (s32)(u32)t.call(dec ? "private_AES_set_decrypt_key" : "private_AES_set_encrypt_key", {A(user), (u64)(u32)bits, A(gk)});
            s32 h = dec ? set_decrypt_key(user, bits, hk) : set_encrypt_key(user, bits, hk);
            if (g != h) t.fail("AES_set_%s_key(%d bits): guest %d, native %d", dec ? "decrypt" : "encrypt", bits, g, h);
            if (g || (bits != 128 && bits != 256 && bits != 192)) continue;
            for (size_t len : {(size_t)16, (size_t)32, (size_t)1, (size_t)15, (size_t)17, (size_t)47, (size_t)4096, (size_t)4100, (size_t)0}) {
                std::vector<u8> src = t.rand_bytes(len + 16);
                u8 *gi = (u8*)malloc(len + 32), *hi = (u8*)malloc(len + 32), *go = (u8*)calloc(1, len + 32), *ho = (u8*)calloc(1, len + 32);
                memcpy(gi, src.data(), len + 16), memcpy(hi, src.data(), len + 16);
                u8 *giv = (u8*)malloc(16), *hiv = (u8*)malloc(16);
                for (int i = 0; i < 16; i++) giv[i] = hiv[i] = (u8)t.rand_int(0, 255);
                t.call("AES_cbc_encrypt", {A(gi), A(go), len, A(gk), A(giv), (u64)(dec ? 0 : 1)});
                cbc_encrypt(hi, ho, len, hk, hiv, dec ? 0 : 1);
                if (memcmp(go, ho, len + 32) || memcmp(giv, hiv, 16))
                    t.fail("AES_cbc_encrypt(%zu bytes, %d bits, %s): the %s differ", len, bits, dec ? "decrypt" : "encrypt", memcmp(go, ho, len + 32) ? "outputs" : "IVs");
                // in place
                memcpy(gi, src.data(), len + 16), memcpy(hi, src.data(), len + 16);
                t.call("AES_cbc_encrypt", {A(gi), A(gi), len, A(gk), A(giv), (u64)(dec ? 0 : 1)});
                cbc_encrypt(hi, hi, len, hk, hiv, dec ? 0 : 1);
                if (memcmp(gi, hi, len + 16) || memcmp(giv, hiv, 16)) t.fail("AES_cbc_encrypt in place (%zu bytes, %d bits, %s) differs", len, bits, dec ? "decrypt" : "encrypt");
                free(gi), free(hi), free(go), free(ho), free(giv), free(hiv);
            }
        }
    }
    free(gk), free(hk), free(user);
}

NATIVE_TEST("lib_crypto/master-db") {
    // the game's use: CEncryptAES128 (the ADLD AES layer) over the 3.7.0 download's master DB
    const char* name = "sqlite/basmaster.sqlite3";
    std::vector<u8> f = test_assets::read_file(test_assets::download_dir().empty() ? "" : test_assets::download_dir() + "/" + name);
    if (f.size() < 16 + 65536) return (void)fprintf(stderr, "    (no download: skipped)\n");
    std::string key = server::adld::aes_key(name);
    auto* obj = (CEncryptAES128*)calloc(1, sizeof(CEncryptAES128) + 16);
    char* ks = strdup(key.c_str());
    t.expect_eq((s32)(u32)t.call("_ZN7Encrypt14CEncryptAES12810InitializeEPKhS2_", {A(obj), A(ks), 0}), 0, "CEncryptAES128::Initialize");
    for (u32 len : {65536u, 4096u + 5u, 16u}) {
        u8* src = (u8*)malloc(len + 16);
        memcpy(src, f.data() + 16, len + 16);
        u8 *g = (u8*)calloc(1, len + 16), *h = (u8*)calloc(1, len + 16);
        t.call("_ZN7Encrypt14CEncryptAES1287DecryptEPKvjPvj", {A(obj), A(src), len, A(g), len});
        // the same steps natively: AES_set_decrypt_key(key, 128), CBC from a copy of the IV
        auto* k = (AesKey*)calloc(1, sizeof(AesKey));
        u8* iv = (u8*)malloc(16);
        memcpy(iv, obj->iv, 16);
        set_decrypt_key(obj->key, 128, k);
        cbc_encrypt(src, h, len, k, iv, 0);
        if (memcmp(g, h, len)) t.fail("%s: %u bytes decrypted differently", name, len);
        if (len == 65536 && memcmp(g, "DCNE", 4)) t.fail("%s: no DCNE header after decrypting", name);
        free(src), free(g), free(h), free(k), free(iv);
    }
    free(obj), free(ks);
}

TestContext* g_t = nullptr;
u64 guest_sym(const char* s) { return g_t->sym(s); }

NATIVE_TEST("lib_crypto/live-check") {
    g_t = &t;
    use_originals(guest_sym);
    live::Lockstep& ck = lockstep();
    u64 c0 = ck.checks(), b0 = ck.mismatches();
    ck.on = true;
    auto* k = (AesKey*)calloc(1, sizeof(AesKey));
    u8* user = (u8*)calloc(1, 32);
    for (int i = 0; i < 16; i++) user[i] = (u8)(i * 37);
    for (int dec : {0, 1}) {
        if (dec) set_decrypt_key(user, 128, k);
        else set_encrypt_key(user, 128, k);
        for (size_t len : {(size_t)16, (size_t)100, (size_t)4096}) {
            std::vector<u8> src = t.rand_bytes(len + 16);
            u8* in = (u8*)malloc(len + 16);
            u8* out = (u8*)calloc(1, len + 32);
            u8* iv = (u8*)calloc(1, 16);
            memcpy(in, src.data(), len + 16);
            cbc_encrypt(in, out, len, k, iv, dec ? 0 : 1);
            free(in), free(out), free(iv);
        }
    }
    ck.on = false;
    use_originals(nullptr);
    free(k), free(user);
    u64 n = ck.checks() - c0, bad = ck.mismatches() - b0;
    fprintf(stderr, "    %llu checks, %llu mismatches\n", (unsigned long long)n, (unsigned long long)bad);
    if (n < 8) t.fail("only %llu checks", (unsigned long long)n);
    if (bad) t.fail("%llu mismatches", (unsigned long long)bad);
}

}  // namespace
}  // namespace soa::native::lib_crypto
