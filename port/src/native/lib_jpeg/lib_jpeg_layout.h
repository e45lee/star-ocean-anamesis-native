// lib_jpeg_layout.h: the guest data layouts of the `lib_jpeg` subsystem (IJG libjpeg 9b: the host library at Aska::JpegUtil).
//
// Types first (port/PLAN.md task 6): every guest class or struct this subsystem's natives touch is
// recovered here before the code that uses it, as a C++ class with the guest's layout byte for byte
// and the guest's methods attached as members (not a struct + free functions):
//   - fields at the guest's offsets, named after their use (m_hp); unknown bytes as named padding
//     (u8 unk_0c[4]), never offset arithmetic in the natives;
//   - a static_assert per known field offset and one for sizeof, so a wrong guess fails the build;
//   - a comment naming where the layout was read (constructor, decompile in port/decomp/lib_jpeg/).
// Natives are these members (this->m_hp), never *(T*)(p + off). Keep the classes standard-layout (no
// C++ virtual, no non-static members of reference type), so offsetof works. The guest is AArch64 LP64; the
// host (x86-64 / AArch64) has the same sizes and alignments for these plain types.
// `tools/subsystem.py export-types lib_jpeg` turns the structs into port/decomp/lib_jpeg/types.json for Ghidra.
#ifndef SOA_NATIVE_LIB_JPEG_LAYOUT_H
#define SOA_NATIVE_LIB_JPEG_LAYOUT_H

#include <cstddef>
#include <cstdint>

namespace soa::native::lib_jpeg {

using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using s8 = std::int8_t;
using s16 = std::int16_t;
using s32 = std::int32_t;
using s64 = std::int64_t;

// Aska::JpegUtil::ILineScanner: the game's line converters (FnGrayscaleLineReader, FnRGBXLineReader,
// FnCMYKLineReader) implement it: one decoded scanline (src, `width` pixels) into the destination row.
// Guest objects: vtable slot 0.
class ILineScanner {
public:
    void Scan(u8* dst, const u8* src, s32 width) const;  // operator()(u8*, const u8*, int) const
    const void* const* vtable;                           // 0x00
};
// Aska::JpegUtil::IAllocator: the scanline buffer's allocator (FnASKAEngineAllocator: the engine heap).
// Vtable slots 0, 1.
class IAllocator {
public:
    void* Malloc(u64 size) const;  // slot 0
    void Free(void* p) const;      // slot 1
    const void* const* vtable;     // 0x00
};
static_assert(sizeof(ILineScanner) == 8 && sizeof(IAllocator) == 8);

// Aska::JpegUtil: the game's JPEG decoding over IJG libjpeg 9b, static functions only (decompiles in
// port/decomp/lib_jpeg/jpeg_util.c). Its callers: Aska::TextureUtil::CreateTextureFromJpeg /
// CreateCubeTextureFromJpeg (GetInfo, Decode) and Aska::DecodeJpegObject::DecodeCpu* (GetInfo,
// GetPlaneInfo, DecodeQuantCoef, DecodeYuv). The libjpeg structs never leave these functions (they
// live on their stacks), so the boundary is here: the natives run the host's libjpeg 9b.
class JpegUtil {
public:
    // out_color_space - 1 (libjpeg's J_COLOR_SPACE: 0 grayscale, 1 RGB, 2 YCbCr, 3 CMYK, 4 YCCK, 5 BG_RGB,
    // 6 BG_YCC); -1 for the others.
    using ColorSpace = s32;

    using ILineScanner = lib_jpeg::ILineScanner;  // Aska::JpegUtil::ILineScanner
    using IAllocator = lib_jpeg::IAllocator;      // Aska::JpegUtil::IAllocator

    // JpegUtil::GetInfo(u32*, u32*, ColorSpace*, bool*, bool*, const void*, unsigned long): the header's
    // size, color space, progressive / arithmetic coding. 0, -1 (not decodable) or -1020 (no SOI).
    static s32 GetInfo(u32* width, u32* height, ColorSpace* cs, bool* progressive, bool* arith, const void* data, u64 size);
    // JpegUtil::Decode(void*, unsigned long, u32, u32, const void*, unsigned long, const ILineScanner& x3,
    // const IAllocator&): every scanline through the scanner of the output color space (gray, RGB,
    // CMYK), rows clipped to width x height, `pitch` bytes apart.
    static s32 Decode(u8* dst, u64 pitch, u32 width, u32 height, const void* data, u64 size, const ILineScanner* gray, const ILineScanner* rgb,
                      const ILineScanner* cmyk, const IAllocator* alloc);
    // JpegUtil::GetPlaneInfo(u32*, u32*, u32*, u32*, u32*, const void*, unsigned long): per component,
    // the plane's width and height in pixels (whole MCUs), its height >> the horizontal shift, and the
    // horizontal / vertical subsampling shifts. Any pointer may be null. 0 or -1.
    static s32 GetPlaneInfo(u32* widths, u32* heights, u32* shifted_rows, u32* shift_x, u32* shift_y, const void* data, u64 size);
    // JpegUtil::DecodeQuantCoef(float*, short*, const void*, unsigned long): the quantization tables
    // times the IDCT scales (64 floats per component; 1 or 3 components) and the raw DCT coefficients,
    // component after component. Either pointer may be null. 0 or -1.
    static s32 DecodeQuantCoef(float* quant, s16* coef, const void* data, u64 size);
    // JpegUtil::DecodeYuv(u32**, const void*, unsigned long): raw (not upsampled, not color converted)
    // component planes, 1 or 3 components. 0 or -1.
    static s32 DecodeYuv(u32** planes, const void* data, u64 size);

private:
    // The shared body of GetInfo and Decode (a local function at GetInfo + 0x78).
    static s32 DecodeImpl(u8* dst, u64 pitch, u32 width, u32 height, u32* out_width, u32* out_height, ColorSpace* cs, bool* progressive, bool* arith,
                          const u8* data, u64 size, const ILineScanner* gray, const ILineScanner* rgb, const ILineScanner* cmyk,
                          const IAllocator* alloc);
};

}  // namespace soa::native::lib_jpeg

#endif  // SOA_NATIVE_LIB_JPEG_LAYOUT_H
