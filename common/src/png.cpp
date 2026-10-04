// soa/png.h: stb_image_write's PNG writer, private to this file (STB_IMAGE_WRITE_STATIC: the web
// view's render tool has its own copy).
#include <soa/png.h>

#include <zlib.h>

#include <cstdio>
#include <cstdlib>

namespace {
// stb's deflater, replaced with zlib's (STBIW_ZLIB_COMPRESS): level 6 as before, and smaller files
// than stb's own. stb frees the result with STBIW_FREE (free).
unsigned char* zlib_compress(unsigned char* data, int len, int* out_len, int /*quality*/) {
    uLongf n = compressBound((uLong)len);
    auto* out = (unsigned char*)malloc(n);
    if (!out || compress2(out, &n, data, (uLong)len, 6) != Z_OK) {
        free(out);
        return nullptr;
    }
    *out_len = (int)n;
    return out;
}
}  // namespace

#define STBIW_ZLIB_COMPRESS zlib_compress
#define STB_IMAGE_WRITE_STATIC
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

namespace soa {

std::string png_encode(int width, int height, int channels, const std::uint8_t* pixels, int stride) {
    stbi_write_force_png_filter = 0;  // filter type 0 (None) on every row, as the old writer
    std::string out;
    auto append = [](void* ctx, void* data, int size) { ((std::string*)ctx)->append((const char*)data, (size_t)size); };
    if (!stbi_write_png_to_func(append, &out, width, height, channels, pixels, stride)) return {};
    return out;
}

bool png_write(const std::string& path, int width, int height, int channels, const std::uint8_t* pixels, int stride) {
    std::string png = png_encode(width, height, channels, pixels, stride);
    if (png.empty()) return false;
    FILE* f = fopen(path.c_str(), "wb");
    if (!f) return false;
    bool ok = fwrite(png.data(), 1, png.size(), f) == png.size();
    return fclose(f) == 0 && ok;
}

}  // namespace soa
