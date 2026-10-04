// Aska::Utf8: UTF-8 to UCS-4 / UCS-2 (hash_layout.h; port/decomp/hash/utf8.c). The guest's quirks
// are kept: an invalid lead byte (a continuation byte, 0xf8-0xff) is copied as one code unit; a
// 4-byte sequence reads its continuation bytes unchecked (even past a NUL) and, in UCS-2, stores
// the lead byte itself.
#include "native/hash/hash_family.h"
#include "native/hash/hash_layout.h"

namespace soa::native::hash {

u64 Utf8::GetByteSizeAt_(u8 c) {
    if (!(c & 0x80)) return 1;
    if ((c & 0xe0) == 0xc0) return 2;
    if ((c & 0xf0) == 0xe0) return 3;
    return (c & 0xf8) == 0xf0 ? 4 : 0;
}

u64 Utf8::ToUcs4(char32_t* dst, const char* src, u64 n) {
    if (!dst || !src || !n) return 0;
    const u8* p = reinterpret_cast<const u8*>(src);
    u64 k = 0;
    for (u32 c = *p; k < n && c != 0; c = *p) {
        if ((c & 0xe0) == 0xc0) {
            dst[k] = (c & 0x1f) << 6 | (p[1] & 0x3f);
            p += 2;
        } else if ((c & 0xf0) == 0xe0) {
            dst[k] = (c & 0x0f) << 12 | (p[1] & 0x3f) << 6 | (p[2] & 0x3f);
            p += 3;
        } else if ((c & 0xf8) == 0xf0) {
            dst[k] = (c & 0x07) << 18 | (p[1] & 0x3f) << 12 | (p[2] & 0x3f) << 6 | (p[3] & 0x3f);
            p += 4;
        } else {  // ASCII, or an invalid lead byte
            dst[k] = c;
            p += 1;
        }
        k++;
    }
    return k;
}

u64 Utf8::ToUcs2(char16_t* dst, const char* src, u64 n) {
    if (!dst || !src || !n) return 0;
    const u8* p = reinterpret_cast<const u8*>(src);
    u64 k = 0;
    for (u32 c = *p; k < n && c != 0; c = *p) {
        if ((c & 0xe0) == 0xc0) {
            dst[k] = (char16_t)((c & 0x1f) << 6 | (p[1] & 0x3f));
            p += 2;
        } else if ((c & 0xf0) == 0xe0) {
            dst[k] = (char16_t)(c << 12 | (p[1] & 0x3f) << 6 | (p[2] & 0x3f));
            p += 3;
        } else if ((c & 0xf8) == 0xf0) {
            dst[k] = (char16_t)c;  // (outside the BMP: the lead byte)
            p += 4;
        } else {
            dst[k] = (char16_t)c;
            p += 1;
        }
        k++;
    }
    return k;
}

using live::kInt;
using live::out_len;

LEAF_FUNCTION(family(), "_ZN4Aska4Utf814GetByteSizeAt_Eh", &Utf8::GetByteSizeAt_, kInt, "Aska::Utf8::GetByteSizeAt_", {});
LEAF_FUNCTION(family(), "_ZN4Aska4Utf86ToUcs4EPDiPKcm", &Utf8::ToUcs4, kInt, "Aska::Utf8::ToUcs4", {out_len(0, 2, 4, 0, 0x1000)});
LEAF_FUNCTION(family(), "_ZN4Aska4Utf86ToUcs2EPDsPKcm", &Utf8::ToUcs2, kInt, "Aska::Utf8::ToUcs2", {out_len(0, 2, 2, 0, 0x1000)});

}  // namespace soa::native::hash
