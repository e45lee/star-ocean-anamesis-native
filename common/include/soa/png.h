#pragma once
// PNG encoding for the programs' screenshots and tools (soa_codec; common/src/png.cpp): stb_image_write
// (vcpkg `stb`), with zlib's compress2 at level 6 as its deflater and filter 0 on every row, so the
// files are the ones the hand-written writer this replaced produced, byte for byte.
#include <cstdint>
#include <string>

namespace soa {

// 8-bit RGB (channels 3) or RGBA (channels 4) rows, top row first, `stride` bytes apart (0: packed).
// Returns the PNG file bytes ("" on failure).
std::string png_encode(int width, int height, int channels, const std::uint8_t* pixels, int stride = 0);
// png_encode, written to `path` (true when written).
bool png_write(const std::string& path, int width, int height, int channels, const std::uint8_t* pixels, int stride = 0);

}  // namespace soa
