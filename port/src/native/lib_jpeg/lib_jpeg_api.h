#pragma once
// IJG libjpeg 9b: the game's copy replaced by the host's (cmake/libjpeg9, pinned to 9b) at
// Aska::JpegUtil (lib_jpeg_layout.h), whose functions are the natives (lib_jpeg_util.cpp). README.md
// has the rules.
#include "native/common/lockstep.h"
#include "native/lib_jpeg/lib_jpeg_layout.h"

namespace soa::native::lib_jpeg {

extern const double kIdctScales[64];
u32 glj_ilog(u32 x);  // glj_ilog(unsigned int)

// The bytes each output of JpegUtil writes for this JPEG (from its header; 0 when unreadable), for
// the live check's scratch copies and the tests.
struct OutputSizes {
    int components = 0;
    u64 coef_bytes = 0;       // DecodeQuantCoef's coefficients
    u64 plane_bytes[4] = {};  // DecodeYuv's planes
    u32 image_width = 0, image_height = 0;
};
OutputSizes output_sizes(const void* data, u64 size);

// The natives: JpegUtil's functions behind the live check (the tests call JpegUtil's directly).
s32 checked_get_info(u32* width, u32* height, JpegUtil::ColorSpace* cs, bool* progressive, bool* arith, const void* data, u64 size);
s32 checked_decode(u8* dst, u64 pitch, u32 width, u32 height, const void* data, u64 size, const JpegUtil::ILineScanner* gray,
                   const JpegUtil::ILineScanner* rgb, const JpegUtil::ILineScanner* cmyk, const JpegUtil::IAllocator* alloc);
s32 checked_plane_info(u32* widths, u32* heights, u32* shifted_rows, u32* shift_x, u32* shift_y, const void* data, u64 size);
s32 checked_quant_coef(float* quant, s16* coef, const void* data, u64 size);
s32 checked_yuv(u32** planes, const void* data, u64 size);

// The live check (--live-check lib_jpeg) and, for its test, its originals (as lib_vorbis_api.h).
live::Lockstep& lockstep();
void use_originals(u64 (*sym)(const char*));

}  // namespace soa::native::lib_jpeg
