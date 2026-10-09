#include "native/common/lib_check.h"

#include <openssl/evp.h>

#include <cstdio>
#include <filesystem>
#include <memory>
#include <vector>

#include "soaruntime/core/loader.h"
#include "native/common/gen/common_addresses.h"
#include "native/common/test.h"

namespace soa::native {

std::string file_sha256(const std::string& path) {
    FILE* f = fopen(path.c_str(), "rb");
    if (!f) return "";
    std::unique_ptr<EVP_MD_CTX, decltype(&EVP_MD_CTX_free)> ctx(EVP_MD_CTX_new(), EVP_MD_CTX_free);
    bool ok = ctx && EVP_DigestInit_ex(ctx.get(), EVP_sha256(), nullptr) == 1;
    std::vector<unsigned char> buf(1 << 20);
    for (size_t n; ok && (n = fread(buf.data(), 1, buf.size(), f)) > 0;) ok = EVP_DigestUpdate(ctx.get(), buf.data(), n) == 1;
    ok = ok && !ferror(f);
    fclose(f);
    unsigned char md[EVP_MAX_MD_SIZE];
    unsigned len = 0;
    if (!ok || EVP_DigestFinal_ex(ctx.get(), md, &len) != 1) return "";
    std::string hex;
    for (unsigned i = 0; i < len; i++) {
        char b[3];
        snprintf(b, sizeof b, "%02x", md[i]);
        hex += b;
    }
    return hex;
}

const char* expected_lib_sha256() { return kLibSha256; }

bool lib_matches(const std::string& path, std::string* got) {
    std::string h = file_sha256(path);
    if (got) *got = h;
    return h == kLibSha256;
}

}  // namespace soa::native

// The lib this selftest runs on is the one the tables were made from; another file isn't.
NATIVE_TEST("native/lib-check") {
    using namespace soa;
    std::string got;
    t.expect_eq(native::lib_matches(main_lib()->path, &got), true, "the loaded lib is the tables' build");
    t.expect_eq(got, std::string(native::expected_lib_sha256()), "its sha256");
    // (sha256 of the empty file, the standard test vector)
    std::string empty = (std::filesystem::temp_directory_path() / "soa-lib-check.empty").string();
    if (FILE* f = fopen(empty.c_str(), "wb")) fclose(f);
    t.expect_eq(native::file_sha256(empty), std::string("e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855"), "sha256 of an empty file");
    t.expect_eq(native::lib_matches(empty), false, "another file doesn't match");
    remove(empty.c_str());
    t.expect_eq(native::file_sha256("/nonexistent/soa-lib-check"), std::string(""), "unreadable: empty");
}
