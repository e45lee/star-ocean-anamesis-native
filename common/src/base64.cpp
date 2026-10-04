// soa/base64.h on OpenSSL's EVP_EncodeBlock / EVP_DecodeBlock.
#include <soa/base64.h>

#include <openssl/evp.h>

namespace soa::base64 {

std::string encode(std::string_view bytes) {
    std::string out(4 * ((bytes.size() + 2) / 3) + 1, '\0');  // + EVP_EncodeBlock's NUL
    int n = EVP_EncodeBlock((unsigned char*)out.data(), (const unsigned char*)bytes.data(), (int)bytes.size());
    out.resize((size_t)n);
    return out;
}

std::string android_default(std::string_view bytes) {
    std::string b = encode(bytes), out;
    for (size_t i = 0; i < b.size(); i += 76) out.append(b, i, 76) += '\n';
    return out;
}

std::string aska_name(std::string_view bytes) {
    std::string out = encode(bytes);
    if (bytes.size() % 3 == 0) out += "====";
    return out;
}

std::string decode(std::string_view text) {
    // EVP_DecodeBlock is strict (no inner whitespace, whole quads): give it the alphabet characters
    // only, completed to a quad with 'A' (zero bits), and keep the bytes those characters hold.
    std::string clean;
    clean.reserve(text.size());
    for (char c : text)
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '+' || c == '/') clean.push_back(c);
    size_t keep = clean.size() * 6 / 8;
    clean.resize((clean.size() + 3) / 4 * 4, 'A');
    std::string out(clean.size() / 4 * 3, '\0');
    if (!clean.empty() && EVP_DecodeBlock((unsigned char*)out.data(), (const unsigned char*)clean.data(), (int)clean.size()) < 0) return {};
    out.resize(keep);
    return out;
}

}  // namespace soa::base64
