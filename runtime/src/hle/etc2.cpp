// ETC2 / EAC decoding (OpenGL ES 3.0.6 spec, section C.1.3 "ETC2 compressed textures"): see etc2.h.
#include "hle/etc2.h"

#include <cstring>

namespace soa::etc2 {
namespace {

inline int clamp255(int v) { return v < 0 ? 0 : v > 255 ? 255 : v; }
inline int ext4(int v) { return (v << 4) | v; }
inline int ext5(int v) { return (v << 3) | (v >> 2); }
inline int ext6(int v) { return (v << 2) | (v >> 4); }
inline int ext7(int v) { return (v << 1) | (v >> 6); }
inline unsigned bits(std::uint64_t w, int hi, int lo) { return (unsigned)(w >> lo) & ((1u << (hi - lo + 1)) - 1); }
inline std::uint64_t load_be64(const std::uint8_t* p) {
    std::uint64_t v;
    std::memcpy(&v, p, 8);
    return __builtin_bswap64(v);
}

// Table C.10 (intensity modifiers; columns for pixel index values 0..3 = {a, b, -a, -b}).
constexpr int kModifier[8][2] = {{2, 8}, {5, 17}, {9, 29}, {13, 42}, {18, 60}, {24, 80}, {33, 106}, {47, 183}};
// Table C.14 (T and H mode distances).
constexpr int kDistance[8] = {3, 6, 11, 16, 23, 32, 41, 64};
// Table C.16 (EAC alpha modifiers).
constexpr int kAlpha[16][8] = {
    {-3, -6, -9, -15, 2, 5, 8, 14}, {-3, -7, -10, -13, 2, 6, 9, 12}, {-2, -5, -8, -13, 1, 4, 7, 12},
    {-2, -4, -6, -13, 1, 3, 5, 12}, {-3, -6, -8, -12, 2, 5, 7, 11}, {-3, -7, -9, -11, 2, 6, 8, 10},
    {-4, -7, -8, -11, 3, 6, 7, 10}, {-3, -5, -8, -11, 2, 4, 7, 10}, {-2, -6, -8, -10, 1, 5, 7, 9},
    {-2, -5, -8, -10, 1, 4, 7, 9},  {-2, -4, -8, -10, 1, 3, 7, 9},  {-2, -5, -7, -10, 1, 4, 6, 9},
    {-3, -4, -7, -10, 2, 3, 6, 9},  {-1, -2, -3, -10, 0, 1, 2, 9},  {-4, -6, -8, -9, 3, 5, 7, 8},
    {-3, -5, -7, -9, 2, 4, 6, 8}};

// One 4x4 block's colour part to out[y][x] (RGBA; alpha 255 or 0 for punchthrough transparency).
void decode_color(std::uint64_t w, bool punchthrough, std::uint8_t out[4][4][4]) {
    const bool diff_or_opaque = bits(w, 33, 33);
    const bool flip = bits(w, 32, 32);
    const bool diff = punchthrough || diff_or_opaque;   // punchthrough has no individual mode
    const bool opaque = !punchthrough || diff_or_opaque;
    const unsigned lsbs = bits(w, 15, 0), msbs = bits(w, 31, 16);
    auto index = [&](int x, int y) { const int i = x * 4 + y; return (int)(((msbs >> i) & 1) << 1 | ((lsbs >> i) & 1)); };
    auto put = [&](int x, int y, int r, int g, int b, int a) {
        out[y][x][0] = (std::uint8_t)r, out[y][x][1] = (std::uint8_t)g, out[y][x][2] = (std::uint8_t)b, out[y][x][3] = (std::uint8_t)a;
    };
    int base[2][3];
    if (!diff) {
        for (int c = 0; c < 3; c++) {
            base[0][c] = ext4(bits(w, 63 - 8 * c, 60 - 8 * c));
            base[1][c] = ext4(bits(w, 59 - 8 * c, 56 - 8 * c));
        }
    } else {
        int b5[3], d3[3];
        for (int c = 0; c < 3; c++) {
            b5[c] = (int)bits(w, 63 - 8 * c, 59 - 8 * c);
            d3[c] = (int)bits(w, 58 - 8 * c, 56 - 8 * c);
            if (d3[c] >= 4) d3[c] -= 8;
        }
        const int r2 = b5[0] + d3[0], g2 = b5[1] + d3[1], b2 = b5[2] + d3[2];
        if (r2 < 0 || r2 > 31) {
            // T mode
            int c1[3] = {ext4((int)(bits(w, 60, 59) << 2 | bits(w, 57, 56))), ext4((int)bits(w, 55, 52)), ext4((int)bits(w, 51, 48))};
            int c2[3] = {ext4((int)bits(w, 47, 44)), ext4((int)bits(w, 43, 40)), ext4((int)bits(w, 39, 36))};
            const int d = kDistance[bits(w, 35, 34) << 1 | bits(w, 32, 32)];
            int paint[4][3];
            for (int c = 0; c < 3; c++) {
                paint[0][c] = c1[c];
                paint[1][c] = clamp255(c2[c] + d);
                paint[2][c] = c2[c];
                paint[3][c] = clamp255(c2[c] - d);
            }
            for (int y = 0; y < 4; y++)
                for (int x = 0; x < 4; x++) {
                    const int k = index(x, y);
                    if (!opaque && k == 2) put(x, y, 0, 0, 0, 0);
                    else put(x, y, paint[k][0], paint[k][1], paint[k][2], 255);
                }
            return;
        }
        if (g2 < 0 || g2 > 31) {
            // H mode
            int c1[3] = {ext4((int)bits(w, 62, 59)), ext4((int)(bits(w, 58, 56) << 1 | bits(w, 52, 52))),
                         ext4((int)(bits(w, 51, 51) << 3 | bits(w, 49, 47)))};
            int c2[3] = {ext4((int)bits(w, 46, 43)), ext4((int)bits(w, 42, 39)), ext4((int)bits(w, 38, 35))};
            const int v1 = c1[0] << 16 | c1[1] << 8 | c1[2], v2 = c2[0] << 16 | c2[1] << 8 | c2[2];
            const int d = kDistance[bits(w, 34, 34) << 2 | bits(w, 32, 32) << 1 | (v1 >= v2 ? 1 : 0)];
            int paint[4][3];
            for (int c = 0; c < 3; c++) {
                paint[0][c] = clamp255(c1[c] + d);
                paint[1][c] = clamp255(c1[c] - d);
                paint[2][c] = clamp255(c2[c] + d);
                paint[3][c] = clamp255(c2[c] - d);
            }
            for (int y = 0; y < 4; y++)
                for (int x = 0; x < 4; x++) {
                    const int k = index(x, y);
                    if (!opaque && k == 2) put(x, y, 0, 0, 0, 0);
                    else put(x, y, paint[k][0], paint[k][1], paint[k][2], 255);
                }
            return;
        }
        if (b2 < 0 || b2 > 31) {
            // Planar mode (always opaque)
            const int ro = ext6((int)bits(w, 62, 57));
            const int go = ext7((int)(bits(w, 56, 56) << 6 | bits(w, 54, 49)));
            const int bo = ext6((int)(bits(w, 48, 48) << 5 | bits(w, 44, 43) << 3 | bits(w, 41, 39)));
            const int rh = ext6((int)(bits(w, 38, 34) << 1 | bits(w, 32, 32)));
            const int gh = ext7((int)bits(w, 31, 25));
            const int bh = ext6((int)bits(w, 24, 19));
            const int rv = ext6((int)bits(w, 18, 13));
            const int gv = ext7((int)bits(w, 12, 6));
            const int bv = ext6((int)bits(w, 5, 0));
            for (int y = 0; y < 4; y++)
                for (int x = 0; x < 4; x++)
                    put(x, y, clamp255((x * (rh - ro) + y * (rv - ro) + 4 * ro + 2) >> 2),
                        clamp255((x * (gh - go) + y * (gv - go) + 4 * go + 2) >> 2),
                        clamp255((x * (bh - bo) + y * (bv - bo) + 4 * bo + 2) >> 2), 255);
            return;
        }
        for (int c = 0; c < 3; c++) {
            base[0][c] = ext5(b5[c]);
            base[1][c] = ext5(b5[c] + d3[c]);
        }
    }
    const int table[2] = {(int)bits(w, 39, 37), (int)bits(w, 36, 34)};
    for (int y = 0; y < 4; y++)
        for (int x = 0; x < 4; x++) {
            const int s = flip ? (y >= 2) : (x >= 2);
            const int k = index(x, y);
            if (!opaque && k == 2) {
                put(x, y, 0, 0, 0, 0);
                continue;
            }
            // Non-opaque punchthrough blocks use modifier 0 for index 0 (table C.13).
            const int a = (!opaque && k == 0) ? 0 : kModifier[table[s]][0], b = kModifier[table[s]][1];
            const int m = k == 0 ? a : k == 1 ? b : k == 2 ? -a : -b;
            put(x, y, clamp255(base[s][0] + m), clamp255(base[s][1] + m), clamp255(base[s][2] + m), 255);
        }
}

void decode_alpha(std::uint64_t w, std::uint8_t out[4][4][4]) {
    const int base = (int)bits(w, 63, 56), mult = (int)bits(w, 55, 52);
    const int* t = kAlpha[bits(w, 51, 48)];
    for (int x = 0; x < 4; x++)
        for (int y = 0; y < 4; y++) {
            const int i = x * 4 + y;
            out[y][x][3] = (std::uint8_t)clamp255(base + t[bits(w, 47 - 3 * i, 45 - 3 * i)] * mult);
        }
}

}  // namespace

void decode(Format f, const std::uint8_t* src, int w, int h, std::uint8_t* rgba) {
    const int bw = (w + 3) / 4, bh = (h + 3) / 4, bb = block_bytes(f);
    std::uint8_t blk[4][4][4];
    for (int by = 0; by < bh; by++)
        for (int bx = 0; bx < bw; bx++) {
            const std::uint8_t* p = src + (std::size_t)(by * bw + bx) * bb;
            if (f == Format::RGBA8) {
                decode_color(load_be64(p + 8), false, blk);
                decode_alpha(load_be64(p), blk);
            } else {
                decode_color(load_be64(p), f == Format::RGB8A1, blk);
            }
            const int nx = w - bx * 4 < 4 ? w - bx * 4 : 4, ny = h - by * 4 < 4 ? h - by * 4 : 4;
            for (int y = 0; y < ny; y++)
                std::memcpy(rgba + ((std::size_t)(by * 4 + y) * w + bx * 4) * 4, blk[y][0], (std::size_t)nx * 4);
        }
}

}  // namespace soa::etc2
