// Aska::JpegUtil on the host's IJG libjpeg 9b (lib_jpeg_layout.h, README.md): readable C++ from the
// Ghidra decompile (port/decomp/lib_jpeg/jpeg_util.c). The libjpeg structs are local to each function,
// so the guest never sees them; the game's line scanners and allocator (guest objects) are called
// through their vtables.
//
// --live-check lib_jpeg runs the guest original on the same input into scratch outputs and compares
// (results, header values, decoded rows / planes / coefficients / tables), for GetInfo, GetPlaneInfo,
// DecodeQuantCoef and DecodeYuv; Decode's scanners and allocator are guest code with effects, so it is
// checked through its output rows (a scanner run twice writes the same rows).
#include <cstddef>
#include <cstdio>
#include <cstring>
// clang-format off: jpeglib.h needs size_t and FILE first
#include <jpeglib.h>
// clang-format on

#include <cstdarg>
#include <cstdlib>
#include <vector>

#include "soaruntime/core/cpu.h"
#include "native/common/lockstep.h"
#include "native/common/native.h"
#include "native/lib_jpeg/lib_jpeg_api.h"

namespace soa::native::lib_jpeg {

// The IDCT scale factors (GLJ_REAL_IDCT8X8_SCALES, 64 doubles at 0x2beafa0 in the 3.7.0 lib; the test
// lib_jpeg/tables compares them with the guest's): DecodeQuantCoef's quantization tables are scaled by
// them for the game's GPU IDCT.
const double kIdctScales[64] = {
    0.125, 0.17337998066526844, 0.16332037060954707, 0.14698445030241983,
    0.125, 0.09821186979838777, 0.06764951251827463, 0.034487422410367875,
    0.17337998066526844, 0.24048494156391084, 0.22653186158822197, 0.20387328921222928,
    0.17337998066526844, 0.13622377669395466, 0.09383256937946631, 0.04783542904563622,
    0.16332037060954707, 0.22653186158822197, 0.21338834764831843, 0.19204443917785408,
    0.16332037060954707, 0.1283199917898342, 0.08838834764831845, 0.04505998887543424,
    0.14698445030241983, 0.20387328921222928, 0.19204443917785408, 0.17283542904563623,
    0.14698445030241983, 0.11548494156391084, 0.07954741128580212, 0.04055291860268222,
    0.125, 0.17337998066526844, 0.16332037060954707, 0.14698445030241983,
    0.125, 0.09821186979838777, 0.06764951251827463, 0.034487422410367875,
    0.09821186979838777, 0.13622377669395466, 0.1283199917898342, 0.11548494156391084,
    0.09821186979838777, 0.07716457095436378, 0.053151880922953525, 0.027096593915592403,
    0.06764951251827463, 0.09383256937946631, 0.08838834764831845, 0.07954741128580212,
    0.06764951251827463, 0.053151880922953525, 0.03661165235168156, 0.018664458512585653,
    0.034487422410367875, 0.04783542904563622, 0.04505998887543424, 0.04055291860268222,
    0.034487422410367875, 0.027096593915592403, 0.018664458512585653, 0.009515058436089156,
};

// glj_ilog(unsigned int): 0 for 0, else floor(log2(x)) + 1 rounded up at the half (the guest's bit
// trick, kept as is: the test lib_jpeg/ilog compares every bit length).
u32 glj_ilog(u32 x) {
    u32 r = x != 0;
    u32 b4 = (x >> 16) != 0;
    r |= b4 << 4;
    u32 y = x >> (b4 << 4);
    u32 b3 = (y & 0xff00) != 0;
    r |= b3 << 3;
    y >>= b3 << 3;
    u32 b2 = (y & 0xf0) != 0;
    r |= b2 << 2;
    y >>= b2 << 2;
    u32 b1 = (y & 0xc) != 0;
    r |= b1 << 1;
    if ((2u << (b1 << 1)) & y) r++;
    return r;
}

void ILineScanner::Scan(u8* dst, const u8* src, s32 width) const {
    guest_call((u64)(uintptr_t)vtable[0], {(u64)(uintptr_t)this, (u64)(uintptr_t)dst, (u64)(uintptr_t)src, (u64)(u32)width});
}
void* IAllocator::Malloc(u64 size) const {
    return (void*)(uintptr_t)guest_call((u64)(uintptr_t)vtable[0], {(u64)(uintptr_t)this, size});
}
void IAllocator::Free(void* p) const { guest_call((u64)(uintptr_t)vtable[1], {(u64)(uintptr_t)this, (u64)(uintptr_t)p}); }

namespace {

// The error manager of GetInfo / Decode: error_exit records the message code in the int that
// client_data points at and returns (no longjmp); the caller checks the code after each call.
void record_error(j_common_ptr cinfo) { *(int*)cinfo->client_data = cinfo->err->msg_code; }

// max over the components of h_samp_factor (h = true) or v_samp_factor
u32 max_samp(const jpeg_decompress_struct& ci, bool h) {
    s32 m = 0;
    for (int i = 0; i < ci.num_components; i++) {
        s32 f = h ? ci.comp_info[i].h_samp_factor : ci.comp_info[i].v_samp_factor;
        if (f > m) m = f;
    }
    return (u32)m;
}
// ceil(n / (f * 8)), 0 when f * 8 is 0
u32 mcus(u32 n, u32 f) { return f * 8 ? (n + f * 8 - 1) / (f * 8) : 0; }

}  // namespace

s32 JpegUtil::DecodeImpl(u8* dst, u64 pitch, u32 width, u32 height, u32* out_width, u32* out_height, ColorSpace* cs, bool* progressive, bool* arith,
                         const u8* data, u64 size, const ILineScanner* gray, const ILineScanner* rgb, const ILineScanner* cmyk, const IAllocator* alloc) {
    if (size < 2 || data[0] != 0xff || data[1] != 0xd8) return -1020;
    int err = 0;
    jpeg_decompress_struct ci;
    jpeg_error_mgr jerr;
    ci.client_data = &err;  // (kept by jpeg_create_decompress)
    ci.err = jpeg_std_error(&jerr);
    jerr.error_exit = record_error;
    jpeg_create_decompress(&ci);
    if (err) return -1;
    jpeg_mem_src(&ci, data, (unsigned long)size);
    if (!err) jpeg_read_header(&ci, TRUE);
    if (err) {
        jpeg_destroy_decompress(&ci);
        return -1;
    }
    if (out_width) *out_width = ci.image_width;
    if (out_height) *out_height = ci.image_height;
    if (cs) *cs = (u32)(ci.out_color_space - 1) <= 6 ? (s32)ci.out_color_space - 1 : -1;
    if (progressive) *progressive = ci.progressive_mode != 0;
    if (arith) *arith = ci.arith_code != 0;
    if (!dst) {
        jpeg_destroy_decompress(&ci);
        return err ? -1 : 0;
    }
    const ILineScanner* scan = ci.out_color_space == JCS_CMYK ? cmyk : ci.out_color_space == JCS_RGB ? rgb : ci.out_color_space == JCS_GRAYSCALE ? gray : nullptr;
    if (scan) {
        jpeg_start_decompress(&ci);
        if (!err) {
            JSAMPROW row = (JSAMPROW)alloc->Malloc((u64)(s64)(s32)(ci.output_components * (s32)ci.output_width));
            if (row) {
                if (ci.image_width <= width) width = ci.image_width;
                if (ci.image_height <= height) height = ci.image_height;
                while (ci.output_scanline < ci.output_height) {
                    u32 y = ci.output_scanline;
                    jpeg_read_scanlines(&ci, &row, 1);
                    if (y < height) scan->Scan(dst + (u64)y * pitch, row, (s32)width);
                }
                if (!err) {
                    alloc->Free(row);
                    jpeg_finish_decompress(&ci);
                    if (!err) {
                        jpeg_destroy_decompress(&ci);
                        return 0;
                    }
                    jpeg_destroy_decompress(&ci);
                    return -1;
                }
                alloc->Free(row);
            }
            jpeg_finish_decompress(&ci);
        }
    }
    // The guest returns 0 here without jpeg_destroy_decompress when no error was recorded (an output
    // color space it has no scanner for, or a failed Malloc): a leak of the decoder's memory, which
    // nothing observes; the native frees it.
    jpeg_destroy_decompress(&ci);
    return err ? -1 : 0;
}

s32 JpegUtil::GetInfo(u32* width, u32* height, ColorSpace* cs, bool* progressive, bool* arith, const void* data, u64 size) {
    return DecodeImpl(nullptr, 0, 0, 0, width, height, cs, progressive, arith, (const u8*)data, size, nullptr, nullptr, nullptr, nullptr);
}

s32 JpegUtil::Decode(u8* dst, u64 pitch, u32 width, u32 height, const void* data, u64 size, const ILineScanner* gray, const ILineScanner* rgb,
                     const ILineScanner* cmyk, const IAllocator* alloc) {
    return DecodeImpl(dst, pitch, width, height, nullptr, nullptr, nullptr, nullptr, nullptr, (const u8*)data, size, gray, rgb, cmyk, alloc);
}

s32 JpegUtil::GetPlaneInfo(u32* widths, u32* heights, u32* shifted_rows, u32* shift_x, u32* shift_y, const void* data, u64 size) {
    // (the library's default error manager: an error exits, as in the guest)
    jpeg_decompress_struct ci;
    jpeg_error_mgr jerr;
    ci.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&ci);
    jpeg_mem_src(&ci, (const unsigned char*)data, (unsigned long)size);
    if (jpeg_read_header(&ci, TRUE) != JPEG_HEADER_OK) {
        jpeg_destroy_decompress(&ci);
        return -1;
    }
    if (ci.num_components > 0) {
        u32 lh = glj_ilog(max_samp(ci, true)), lv = glj_ilog(max_samp(ci, false));
        u32 rows = mcus(ci.image_height, (u32)ci.max_v_samp_factor);
        u32 cols = widths ? mcus(ci.image_width, (u32)ci.max_h_samp_factor) : 0;
        for (int i = 0; i < ci.num_components; i++) {
            u32 h = (u32)ci.comp_info[i].h_samp_factor, v = (u32)ci.comp_info[i].v_samp_factor;
            u32 sx = lh - glj_ilog(h);
            if (widths) widths[i] = cols * 8 * h;
            if (heights) heights[i] = v * rows * 8;
            if (shift_x) shift_x[i] = sx;
            if (shift_y) shift_y[i] = lv - glj_ilog(v);
            // (the vertical block rows over the *horizontal* shift: the guest's)
            if (shifted_rows) shifted_rows[i] = (u32)((s32)(v * rows + (1u << (sx & 31)) - 1) >> (sx & 31));
        }
    }
    jpeg_destroy_decompress(&ci);
    return 0;
}

s32 JpegUtil::DecodeQuantCoef(float* quant, s16* coef, const void* data, u64 size) {
    jpeg_decompress_struct ci;
    jpeg_error_mgr jerr;
    ci.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&ci);
    jpeg_mem_src(&ci, (const unsigned char*)data, (unsigned long)size);
    if (jpeg_read_header(&ci, TRUE) != JPEG_HEADER_OK) {
        jpeg_destroy_decompress(&ci);
        return -1;
    }
    if (quant) {
        if (ci.num_components != 1 && ci.num_components != 3) {
            jpeg_destroy_decompress(&ci);
            return -1;
        }
        for (int c = 0; c < ci.num_components; c++) {
            const JQUANT_TBL* q = ci.quant_tbl_ptrs[ci.comp_info[c].quant_tbl_no];
            for (int k = 0; k < 64; k++) quant[c * 64 + k] = (float)kIdctScales[k] * (float)q->quantval[k];
        }
    }
    if (coef) {
        u32 lh = glj_ilog(max_samp(ci, true));
        jvirt_barray_ptr* arrays = jpeg_read_coefficients(&ci);
        if (ci.num_components > 0) {
            u32 cols8 = mcus(ci.image_width, (u32)ci.max_h_samp_factor) * 8;
            u32 rows = mcus(ci.image_height, (u32)ci.max_v_samp_factor);
            u8* at = (u8*)coef;
            for (int c = 0; c < ci.num_components; c++) {
                jpeg_component_info& comp = ci.comp_info[c];
                u8* base = at;
                // every block row band of v_samp_factor rows, block by block (128 bytes each)
                for (u32 row = 0; row < comp.height_in_blocks; row += (u32)comp.v_samp_factor) {
                    JBLOCKARRAY band = ci.mem->access_virt_barray((j_common_ptr)&ci, arrays[c], row, (JDIMENSION)comp.v_samp_factor, FALSE);
                    for (int r = 0; r < comp.v_samp_factor; r++)
                        for (JDIMENSION b = 0; b < comp.width_in_blocks; b++, at += sizeof(JBLOCK)) memcpy(at, band[r][b], sizeof(JBLOCK));
                }
                // the next component starts after this one's whole plane (MCU-padded, shifted as the guest computes it)
                u32 h = (u32)comp.h_samp_factor, sx = lh - glj_ilog(h);
                u32 blocks_down = (u32)((s32)((1u << (sx & 31)) + (u32)comp.v_samp_factor * rows - 1) >> (sx & 31));
                at = base + (s64)(s32)(blocks_down * ((cols8 * h) << ((sx + 3) & 31))) * 2;
            }
        }
    }
    jpeg_destroy_decompress(&ci);
    return 0;
}

s32 JpegUtil::DecodeYuv(u32** planes, const void* data, u64 size) {
    jpeg_decompress_struct ci;
    jpeg_error_mgr jerr;
    ci.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&ci);
    jpeg_mem_src(&ci, (const unsigned char*)data, (unsigned long)size);
    if (jpeg_read_header(&ci, TRUE) != JPEG_HEADER_OK || (ci.num_components != 1 && ci.num_components != 3)) {
        jpeg_destroy_decompress(&ci);
        return -1;
    }
    if (planes) {
        u32 lv = glj_ilog(max_samp(ci, false));
        u32 cols8 = mcus(ci.image_width, (u32)ci.max_h_samp_factor) * 8;
        u32 shift[3], pitch[3];
        for (int i = 0; i < ci.num_components; i++) {
            pitch[i] = cols8 * (u32)ci.comp_info[i].h_samp_factor;
            shift[i] = lv - glj_ilog((u32)ci.comp_info[i].v_samp_factor);
        }
        JSAMPROW rows[3][16];
        JSAMPARRAY image[3] = {rows[0], rows[1], rows[2]};
        ci.raw_data_out = TRUE;
        ci.do_fancy_upsampling = FALSE;
        ci.dct_method = JDCT_ISLOW;
        jpeg_start_decompress(&ci);
        while (ci.output_scanline < ci.output_height) {
            for (int i = 0; i < ci.num_components; i++) {
                s32 n = 16 >> (shift[i] & 31);
                s64 off = (s64)(s32)pitch[i] * (s64)(s32)(ci.output_scanline >> (shift[i] & 31));
                for (s32 k = 0; k < n; k++, off += (s32)pitch[i]) rows[i][k] = (JSAMPROW)((u8*)planes[i] + off);
            }
            jpeg_read_raw_data(&ci, image, 16);
        }
        jpeg_finish_decompress(&ci);
    }
    jpeg_destroy_decompress(&ci);
    return 0;
}

}  // namespace soa::native::lib_jpeg
