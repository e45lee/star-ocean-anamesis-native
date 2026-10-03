#pragma once
// ETC2 / EAC texture decoding on the CPU (OpenGL ES 3.0 spec, appendix C.1), for the sRGB ETC2
// uploads in gles.cpp: the host driver (Mesa d3d12) has no native ETC2 and decompresses the sRGB
// variants very slowly, so the port decodes them itself and uploads GL_SRGB8_ALPHA8. The decode
// is exact (ETC2 decoding is integer arithmetic fully specified by the standard); the selftest
// hle/etc2-vs-host compares it texel for texel with the host driver's own decode.
#include <cstddef>
#include <cstdint>

namespace soa::etc2 {

enum class Format {
    RGB8,           // GL_COMPRESSED_RGB8_ETC2 / GL_COMPRESSED_SRGB8_ETC2 (and ETC1): alpha 255
    RGB8A1,         // GL_COMPRESSED_(S)RGB8_PUNCHTHROUGH_ALPHA1_ETC2
    RGBA8,          // GL_COMPRESSED_RGBA8_ETC2_EAC / GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC
};

// Bytes per 4x4 block.
inline int block_bytes(Format f) { return f == Format::RGBA8 ? 16 : 8; }
// Size of a w x h image in blocks' bytes.
inline std::size_t image_bytes(Format f, int w, int h) { return (std::size_t)((w + 3) / 4) * ((h + 3) / 4) * block_bytes(f); }

// Decodes a w x h image to tightly packed RGBA8 (row stride w * 4). `src` holds image_bytes().
void decode(Format f, const std::uint8_t* src, int w, int h, std::uint8_t* rgba);

}  // namespace soa::etc2
