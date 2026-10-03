// Image decoding for the page renderer: stb_image (PNG, JPEG, GIF's first frame, BMP). The
// Dragalia renderer also decoded WebP (libwebp); this game's pages have none, so it is left out.
#include <cstring>
#include <memory>
#include <string>

#include "internal.h"

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#define STBI_ONLY_JPEG
#define STBI_ONLY_GIF
#define STBI_ONLY_BMP
#define STB_IMAGE_STATIC
#include <stb_image.h>

namespace soa::webview {

std::shared_ptr<Image> decode_image(const std::string& data) {
    auto img = std::make_shared<Image>();
    const auto* p = (const uint8_t*)data.data();
    int w, h, n;
    if (uint8_t* px = stbi_load_from_memory(p, (int)data.size(), &w, &h, &n, 4)) {
        img->w = w, img->h = h;
        img->rgba.assign(px, px + (size_t)w * h * 4);
        stbi_image_free(px);
        return img;
    }
    return nullptr;
}

}  // namespace soa::webview
