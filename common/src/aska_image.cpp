// soa/aska_image.h: SLZ, ISF, AIF and ETC2 (the decoder moved here from tools/aif2png).
#include <soa/aska_image.h>

#include <zlib.h>
#include <zstd.h>

#include <algorithm>
#include <climits>
#include <cstring>

namespace soa::aska {
namespace {

uint32_t rd32(const uint8_t* p) { return p[0] | p[1] << 8 | p[2] << 16 | (uint32_t)p[3] << 24; }
uint16_t rd16(const uint8_t* p) { return (uint16_t)(p[0] | p[1] << 8); }
void wr32(uint8_t* p, uint32_t v) {
    for (int i = 0; i < 4; i++) p[i] = (uint8_t)(v >> (8 * i));
}
void fail(std::string* err, const std::string& why) {
    if (err) *err = why;
}

}  // namespace

// ---------------------------------------------------------------- SLZ
bool is_slz(const Bytes& d) { return d.size() >= 0x20 && !memcmp(d.data(), "SLZ", 3); }

bool slz_chunks(const Bytes& d, std::vector<SlzChunk>& chunks, std::string* err) {
    chunks.clear();
    if (!is_slz(d)) return fail(err, "not SLZ"), false;
    int codec = d[3];
    int32_t dsz = (int32_t)rd32(&d[0xc]);
    uint32_t chunk = d[0x19] ? d[0x19] * 1024u : (uint32_t)dsz;
    if (rd32(&d[0x1c])) return fail(err, "chained SLZ not supported"), false;
    if (dsz < 0) return fail(err, "SLZ: bad size"), false;
    size_t p = rd32(&d[0x14]);
    for (uint32_t done = 0; done < (uint32_t)dsz;) {
        SlzChunk c;
        c.size = std::min<uint32_t>(chunk, (uint32_t)dsz - done);
        if (codec == 0) {  // stored: no size fields
            c.raw = true;
            c.stored = c.size;
        } else {
            if (p + 2 > d.size()) return fail(err, "SLZ truncated"), false;
            c.stored = rd16(&d[p]);
            p += 2;
            c.raw = c.stored == 0;  // a zero size means the chunk is stored raw
            if (c.raw) c.stored = c.size;
        }
        if (p + c.stored > d.size()) return fail(err, "SLZ truncated"), false;
        c.offset = p;
        chunks.push_back(c);
        p += c.stored;
        done += (uint32_t)c.size;
    }
    return true;
}

bool slz_decode(const Bytes& d, Bytes& out, std::string* err, size_t limit) {
    if (!is_slz(d)) {
        out = d;
        return true;
    }
    std::vector<SlzChunk> chunks;
    if (!slz_chunks(d, chunks, err)) return false;
    int codec = d[3];
    out.clear();
    out.reserve((size_t)rd32(&d[0xc]));
    for (const SlzChunk& c : chunks) {
        if (out.size() >= limit) break;
        const uint8_t* src = &d[c.offset];
        size_t base = out.size();
        out.resize(base + c.size);
        if (c.raw) {
            memcpy(&out[base], src, c.size);
        } else if (codec == 7) {
            // The stored size counts one pad byte after the zstd frame (the game passes the output
            // size as the input size, so zstd stops at the frame end): trim to the frame.
            size_t fs = ZSTD_findFrameCompressedSize(src, c.stored);
            size_t r = ZSTD_decompress(&out[base], c.size, src, ZSTD_isError(fs) ? c.stored : fs);
            if (ZSTD_isError(r)) return fail(err, std::string("zstd: ") + ZSTD_getErrorName(r)), false;
            out.resize(base + r);
        } else if (codec == 5) {
            z_stream zs{};
            inflateInit2(&zs, -15);
            zs.next_in = const_cast<uint8_t*>(src);
            zs.avail_in = (uInt)c.stored;
            zs.next_out = &out[base];
            zs.avail_out = (uInt)c.size;
            int r = inflate(&zs, Z_FINISH);
            inflateEnd(&zs);
            if (r != Z_STREAM_END && r != Z_OK) return fail(err, "inflate failed"), false;
            out.resize(base + zs.total_out);
        } else {
            return fail(err, "SLZ codec " + std::to_string(codec) + " not supported"), false;
        }
    }
    return true;
}

Bytes slz_encode(const Bytes& plain) {
    const size_t kChunk = 65536;
    Bytes payload;
    std::vector<uint8_t> z(compressBound(kChunk) + 64);
    for (size_t i = 0; i < plain.size(); i += kChunk) {
        size_t n = std::min(kChunk, plain.size() - i);
        z_stream zs{};
        deflateInit2(&zs, 9, Z_DEFLATED, -15, 8, Z_DEFAULT_STRATEGY);
        zs.next_in = const_cast<uint8_t*>(&plain[i]);
        zs.avail_in = (uInt)n;
        zs.next_out = z.data();
        zs.avail_out = (uInt)z.size();
        deflate(&zs, Z_FINISH);
        size_t zn = zs.total_out;
        deflateEnd(&zs);
        if (zn < n && zn < 65536) {
            payload.push_back((uint8_t)zn);
            payload.push_back((uint8_t)(zn >> 8));
            payload.insert(payload.end(), z.begin(), z.begin() + zn);
        } else {  // doesn't shrink: stored (size 0)
            payload.push_back(0);
            payload.push_back(0);
            payload.insert(payload.end(), plain.begin() + i, plain.begin() + i + n);
        }
    }
    Bytes out(0x20, 0);
    memcpy(out.data(), "SLZ", 3);
    out[3] = 5;
    out[5] = 1;
    out[6] = 0x25;
    wr32(&out[8], (uint32_t)payload.size());
    wr32(&out[0xc], (uint32_t)plain.size());
    wr32(&out[0x14], 0x20);
    out[0x18] = 1;
    out[0x19] = 64;
    out[0x1a] = 0x10;
    out.insert(out.end(), payload.begin(), payload.end());
    out.resize((out.size() + 3) / 4 * 4, 0);
    return out;
}

// ---------------------------------------------------------------- ISF
std::vector<IsfEntry> isf_entries(const Bytes& d) {
    std::vector<IsfEntry> out;
    if (d.size() < 16 || memcmp(d.data(), "\0ISF", 4)) return out;
    uint32_t count = rd32(&d[8]);
    if (count > 4096 || 16 + (size_t)count * 16 > d.size()) return out;
    for (uint32_t i = 0; i < count; i++) {
        const uint8_t* e = &d[16 + i * 16];
        IsfEntry entry;
        entry.index = i;
        uint32_t name = rd32(e);
        entry.offset = rd32(e + 4);
        entry.size = rd32(e + 8);
        if (name >= d.size() || (uint64_t)entry.offset + entry.size > d.size()) return {};
        const char* s = (const char*)&d[name];
        entry.name.assign(s, strnlen(s, d.size() - name));
        out.push_back(entry);
    }
    return out;
}

uint32_t isf_payload_sum(const Bytes& d, const IsfEntry& e) {
    uint32_t sum = 0;
    for (uint32_t i = 0; i < e.size; i++) sum += d[e.offset + i];
    uint32_t padded = (e.size + 31) / 32 * 32;
    sum += (padded - e.size) * 0xeeu;
    return sum;
}

void isf_update_sum(Bytes& d, const IsfEntry& e) { wr32(&d[16 + e.index * 16 + 12], isf_payload_sum(d, e)); }

bool isf_repack(const Bytes& d, const std::vector<const Bytes*>& payloads, Bytes& out, std::string* err) {
    auto entries = isf_entries(d);
    if (entries.empty()) return fail(err, "not an ISF image"), false;
    if (payloads.size() > entries.size()) return fail(err, "ISF repack: more payloads than entries"), false;
    // the layout this rebuilds: payloads in entry order, each at the next 32-byte boundary, after
    // the header and entry table (which the rebuilt file keeps and rewrites)
    if (entries[0].offset < 16 + entries.size() * 16) return fail(err, "ISF repack: a payload overlaps the entry table"), false;
    size_t at = entries[0].offset;
    for (auto& e : entries) {
        if (e.offset != at || e.offset % 32) return fail(err, "ISF repack: " + e.name + " isn't where the layout puts it"), false;
        at = (e.offset + (size_t)e.size + 31) / 32 * 32;
    }
    out.assign(d.begin(), d.begin() + entries[0].offset);
    for (auto& e : entries) {
        const Bytes* p = e.index < payloads.size() ? payloads[e.index] : nullptr;
        size_t off = out.size();
        if (p) out.insert(out.end(), p->begin(), p->end());
        else out.insert(out.end(), d.begin() + e.offset, d.begin() + e.offset + e.size);
        IsfEntry ne = e;
        ne.offset = (uint32_t)off;
        ne.size = (uint32_t)(out.size() - off);
        out.resize((out.size() + 31) / 32 * 32, 0xee);
        wr32(&out[16 + e.index * 16 + 4], ne.offset);
        wr32(&out[16 + e.index * 16 + 8], ne.size);
        isf_update_sum(out, ne);
    }
    return true;
}

// ---------------------------------------------------------------- ETC1 / ETC2 / EAC
namespace {

inline uint8_t clamp8(int v) { return (uint8_t)(v < 0 ? 0 : v > 255 ? 255 : v); }
inline int ext4(int v) { return v << 4 | v; }
inline int ext5(int v) { return v << 3 | v >> 2; }
inline int ext6(int v) { return v << 2 | v >> 4; }
inline int ext7(int v) { return v << 1 | v >> 6; }

const int kEtcMod[8][2] = {{2, 8}, {5, 17}, {9, 29}, {13, 42}, {18, 60}, {24, 80}, {33, 106}, {47, 183}};
const int kEtcDist[8] = {3, 6, 11, 16, 23, 32, 41, 64};
const int kEacMod[16][8] = {
    {-3, -6, -9, -15, 2, 5, 8, 14}, {-3, -7, -10, -13, 2, 6, 9, 12}, {-2, -5, -8, -13, 1, 4, 7, 12},
    {-2, -4, -6, -13, 1, 3, 5, 12}, {-3, -6, -8, -12, 2, 5, 7, 11}, {-3, -7, -9, -11, 2, 6, 8, 10},
    {-4, -7, -8, -11, 3, 6, 7, 10}, {-3, -5, -8, -11, 2, 4, 7, 10}, {-2, -6, -8, -10, 1, 5, 7, 9},
    {-2, -5, -8, -10, 1, 4, 7, 9},  {-2, -4, -8, -10, 1, 3, 7, 9},  {-2, -5, -7, -10, 1, 4, 6, 9},
    {-3, -4, -7, -10, 2, 3, 6, 9},  {-1, -2, -3, -10, 0, 1, 2, 9},  {-4, -6, -8, -9, 3, 5, 7, 8},
    {-3, -5, -7, -9, 2, 4, 6, 8}};

// Decodes one 8-byte ETC2 RGB block into out[16][4] (pixel (x,y) at y*4+x).
// punch: the RGB8_PUNCHTHROUGH_ALPHA1 variant (bit 33 is "opaque" instead of "diff").
void etc2_rgb_block(const uint8_t* b, uint8_t out[16][4], bool punch) {
    uint64_t v = 0;
    for (int i = 0; i < 8; i++) v = v << 8 | b[i];
    uint32_t idx = (uint32_t)v;
    bool diff = (v >> 33) & 1, flip = (v >> 32) & 1;
    bool opaque = punch ? diff : true;
    if (punch) diff = true;
    auto pix = [&](int x, int y) {
        int j = x * 4 + y;
        return (int)(((idx >> (j + 16)) & 1) << 1 | ((idx >> j) & 1));
    };
    auto paint4 = [&](int paint[4][3]) {
        for (int y = 0; y < 4; y++)
            for (int x = 0; x < 4; x++) {
                int i = pix(x, y);
                uint8_t* o = out[y * 4 + x];
                if (!opaque && i == 2) {
                    o[0] = o[1] = o[2] = o[3] = 0;
                    continue;
                }
                o[0] = (uint8_t)paint[i][0];
                o[1] = (uint8_t)paint[i][1];
                o[2] = (uint8_t)paint[i][2];
                o[3] = 255;
            }
    };
    int r1, g1, b1, r2, g2, b2;
    if (!diff) {
        r1 = ext4((int)(v >> 60) & 15);
        r2 = ext4((int)(v >> 56) & 15);
        g1 = ext4((int)(v >> 52) & 15);
        g2 = ext4((int)(v >> 48) & 15);
        b1 = ext4((int)(v >> 44) & 15);
        b2 = ext4((int)(v >> 40) & 15);
    } else {
        int R = (int)(v >> 59) & 31, dR = (int)(v >> 56) & 7;
        int G = (int)(v >> 51) & 31, dG = (int)(v >> 48) & 7;
        int B = (int)(v >> 43) & 31, dB = (int)(v >> 40) & 7;
        if (dR & 4) dR -= 8;
        if (dG & 4) dG -= 8;
        if (dB & 4) dB -= 8;
        if (R + dR < 0 || R + dR > 31) {  // T mode
            int c1[3] = {ext4((int)((v >> 59) & 3) << 2 | (int)((v >> 56) & 3)), ext4((int)(v >> 52) & 15), ext4((int)(v >> 48) & 15)};
            int c2[3] = {ext4((int)(v >> 44) & 15), ext4((int)(v >> 40) & 15), ext4((int)(v >> 36) & 15)};
            int d = kEtcDist[((v >> 34) & 3) << 1 | ((v >> 32) & 1)];
            int paint[4][3];
            for (int c = 0; c < 3; c++) {
                paint[0][c] = c1[c];
                paint[1][c] = clamp8(c2[c] + d);
                paint[2][c] = c2[c];
                paint[3][c] = clamp8(c2[c] - d);
            }
            paint4(paint);
            return;
        }
        if (G + dG < 0 || G + dG > 31) {  // H mode
            int R1 = (int)(v >> 59) & 15, G1 = (int)((v >> 56) & 7) << 1 | (int)((v >> 52) & 1);
            int B1 = (int)((v >> 51) & 1) << 3 | (int)((v >> 47) & 7);
            int R2 = (int)(v >> 43) & 15, G2 = (int)(v >> 39) & 15, B2 = (int)(v >> 35) & 15;
            int di = (int)((v >> 34) & 1) << 2 | (int)((v >> 32) & 1) << 1 | ((R1 << 8 | G1 << 4 | B1) >= (R2 << 8 | G2 << 4 | B2) ? 1 : 0);
            int d = kEtcDist[di];
            int c1[3] = {ext4(R1), ext4(G1), ext4(B1)}, c2[3] = {ext4(R2), ext4(G2), ext4(B2)};
            int paint[4][3];
            for (int c = 0; c < 3; c++) {
                paint[0][c] = clamp8(c1[c] + d);
                paint[1][c] = clamp8(c1[c] - d);
                paint[2][c] = clamp8(c2[c] + d);
                paint[3][c] = clamp8(c2[c] - d);
            }
            paint4(paint);
            return;
        }
        if (B + dB < 0 || B + dB > 31) {  // planar (always opaque)
            int RO = ext6((int)(v >> 57) & 63);
            int GO = ext7((int)((v >> 56) & 1) << 6 | (int)((v >> 49) & 63));
            int BO = ext6((int)((v >> 48) & 1) << 5 | (int)((v >> 43) & 3) << 3 | (int)((v >> 39) & 7));
            int RH = ext6((int)((v >> 34) & 31) << 1 | (int)((v >> 32) & 1));
            int GH = ext7((int)(v >> 25) & 127), BH = ext6((int)(v >> 19) & 63);
            int RV = ext6((int)(v >> 13) & 63), GV = ext7((int)(v >> 6) & 127), BV = ext6((int)v & 63);
            for (int y = 0; y < 4; y++)
                for (int x = 0; x < 4; x++) {
                    uint8_t* o = out[y * 4 + x];
                    o[0] = clamp8((x * (RH - RO) + y * (RV - RO) + 4 * RO + 2) >> 2);
                    o[1] = clamp8((x * (GH - GO) + y * (GV - GO) + 4 * GO + 2) >> 2);
                    o[2] = clamp8((x * (BH - BO) + y * (BV - BO) + 4 * BO + 2) >> 2);
                    o[3] = 255;
                }
            return;
        }
        r1 = ext5(R);
        r2 = ext5(R + dR);
        g1 = ext5(G);
        g2 = ext5(G + dG);
        b1 = ext5(B);
        b2 = ext5(B + dB);
    }
    int t1 = (int)(v >> 37) & 7, t2 = (int)(v >> 34) & 7;
    for (int y = 0; y < 4; y++)
        for (int x = 0; x < 4; x++) {
            bool second = flip ? y >= 2 : x >= 2;
            int t = second ? t2 : t1;
            int i = pix(x, y);
            uint8_t* o = out[y * 4 + x];
            if (!opaque && i == 2) {
                o[0] = o[1] = o[2] = o[3] = 0;
                continue;
            }
            int m = (!opaque && i == 0) ? 0 : (i & 1 ? kEtcMod[t][1] : kEtcMod[t][0]) * (i & 2 ? -1 : 1);
            o[0] = clamp8((second ? r2 : r1) + m);
            o[1] = clamp8((second ? g2 : g1) + m);
            o[2] = clamp8((second ? b2 : b1) + m);
            o[3] = 255;
        }
}

void eac_alpha_block(const uint8_t* b, uint8_t out[16][4]) {
    int base = b[0], mult = b[1] >> 4, tab = b[1] & 15;
    uint64_t bits = 0;
    for (int i = 2; i < 8; i++) bits = bits << 8 | b[i];
    for (int x = 0; x < 4; x++)
        for (int y = 0; y < 4; y++) {
            int i = x * 4 + y;
            int idx = (int)(bits >> (45 - 3 * i)) & 7;
            out[y * 4 + x][3] = clamp8(base + kEacMod[tab][idx] * mult);
        }
}

// EAC R11 (one channel of RG11: formats 50 unsigned, 51 signed), to 8 bits (the top 8 of the 11;
// signed values -1023..1023 mapped to 0..255) in channel `ch`. Khronos spec, "EAC R11": the base
// is base * 8 + 4 (signed: base * 8), each pixel adds modifier * multiplier * 8 (multiplier 0: the
// modifier alone), clamped to the 11-bit range.
void eac_r11_block(const uint8_t* b, uint8_t out[16][4], int ch, bool sign) {
    int base = sign ? (int)(int8_t)b[0] : b[0], mult = b[1] >> 4, tab = b[1] & 15;
    if (sign && base == -128) base = -127;
    uint64_t bits = 0;
    for (int i = 2; i < 8; i++) bits = bits << 8 | b[i];
    for (int x = 0; x < 4; x++)
        for (int y = 0; y < 4; y++) {
            int i = x * 4 + y;
            int idx = (int)(bits >> (45 - 3 * i)) & 7;
            int m = kEacMod[tab][idx];
            int v;
            if (sign) {
                v = base * 8 + (mult ? m * mult * 8 : m);
                v = v < -1023 ? -1023 : v > 1023 ? 1023 : v;
                out[y * 4 + x][ch] = (uint8_t)((v + 1023) * 255 / 2046);
            } else {
                v = base * 8 + 4 + (mult ? m * mult * 8 : m);
                v = v < 0 ? 0 : v > 2047 ? 2047 : v;
                out[y * 4 + x][ch] = (uint8_t)(v >> 3);
            }
        }
}

// ---- the encoders
// ETC1 (the ETC2 individual / differential modes). For each flip and mode, each sub-block's base
// colour is searched around its rounded average (each channel -1..+1 quantization steps) with every
// table and each pixel's best modifier; in differential mode the second base must stay within
// -4..+3 steps of the first. The least squared error wins (ties: the first tried).
struct SubFit {
    int64_t err = INT64_MAX;
    int q[3] = {0, 0, 0};  // the quantized base (4 or 5 bits)
    int table = 0;
    int idx[16] = {0};  // the modifier index of each of its pixels (y * 4 + x)
};

// The best base and table for the pixels with mask[y*4+x] set, the base quantized to `bits` (4
// or 5) and drawn from [lo[c], hi[c]].
// mode 1: the punch-through variant with transparent pixels (format 48, "opaque" bit clear): a pixel
// with alpha < 128 takes index 2 (transparent), the others index 0 (the base), 1 (+large) or 3 (-large).
SubFit fit_sub(const uint8_t px[16][4], const bool mask[16], int bits, const int lo[3], const int hi[3], int mode) {
    SubFit best;
    int maxq = (1 << bits) - 1;
    int q[3];
    for (q[0] = std::max(0, lo[0]); q[0] <= std::min(maxq, hi[0]); q[0]++)
        for (q[1] = std::max(0, lo[1]); q[1] <= std::min(maxq, hi[1]); q[1]++)
            for (q[2] = std::max(0, lo[2]); q[2] <= std::min(maxq, hi[2]); q[2]++) {
                int base[3];
                for (int c = 0; c < 3; c++) base[c] = bits == 5 ? ext5(q[c]) : ext4(q[c]);
                for (int t = 0; t < 8; t++) {
                    int64_t e = 0;
                    int idx[16] = {0};
                    for (int k = 0; k < 16 && e < best.err; k++) {
                        if (!mask[k]) continue;
                        if (mode == 1 && px[k][3] < 128) {
                            idx[k] = 2;
                            continue;
                        }
                        int be = INT32_MAX, bi = 0;
                        for (int i = 0; i < 4; i++) {
                            if (mode == 1 && i == 2) continue;
                            int m = mode == 1 ? (i == 0 ? 0 : kEtcMod[t][1] * (i & 2 ? -1 : 1)) : (i & 1 ? kEtcMod[t][1] : kEtcMod[t][0]) * (i & 2 ? -1 : 1);
                            int ee = 0;
                            for (int c = 0; c < 3; c++) {
                                int dd = clamp8(base[c] + m) - px[k][c];
                                ee += dd * dd;
                            }
                            if (ee < be) be = ee, bi = i;
                        }
                        e += be;
                        idx[k] = bi;
                    }
                    if (e < best.err) {
                        best.err = e;
                        memcpy(best.q, q, sizeof q);
                        best.table = t;
                        memcpy(best.idx, idx, sizeof idx);
                    }
                }
            }
    return best;
}

// punch: the RGB8 punch-through A1 variant (format 48): differential mode only, bit 33 is "opaque"
// (every alpha >= 128); a block with transparent pixels uses the reduced modifier set (fit_sub mode 1).
void etc1_encode(const uint8_t px[16][4], uint8_t out[8], bool punch) {
    uint64_t best = 0;
    int64_t best_err = INT64_MAX;
    bool opaque = true;
    if (punch)
        for (int k = 0; k < 16; k++) opaque &= px[k][3] >= 128;
    int mode = punch && !opaque ? 1 : 0;
    for (int flip = 0; flip < 2; flip++) {
        bool mask[2][16];
        int sum[2][3] = {{0, 0, 0}, {0, 0, 0}}, cnt[2] = {0, 0};
        for (int y = 0; y < 4; y++)
            for (int x = 0; x < 4; x++) {
                int s = flip ? y >= 2 : x >= 2;
                mask[s][y * 4 + x] = true;
                mask[!s][y * 4 + x] = false;
                if (mode == 1 && px[y * 4 + x][3] < 128) continue;
                cnt[s]++;
                for (int c = 0; c < 3; c++) sum[s][c] += px[y * 4 + x][c];
            }
        for (int diff = punch ? 1 : 0; diff < 2; diff++) {
            int bits = diff ? 5 : 4, n = diff ? 31 : 15;
            int avg_q[2][3], lo[3], hi[3];
            for (int s = 0; s < 2; s++)
                for (int c = 0; c < 3; c++)  // round(sum / cnt * n / 255)
                    avg_q[s][c] = cnt[s] ? std::min(n, (2 * sum[s][c] * n + cnt[s] * 255) / (2 * cnt[s] * 255)) : 0;
            SubFit f[2];
            for (int c = 0; c < 3; c++) lo[c] = avg_q[0][c] - 1, hi[c] = avg_q[0][c] + 1;
            f[0] = fit_sub(px, mask[0], bits, lo, hi, mode);
            for (int c = 0; c < 3; c++) {
                lo[c] = avg_q[1][c] - 1, hi[c] = avg_q[1][c] + 1;
                if (diff) lo[c] = std::max(lo[c], f[0].q[c] - 4), hi[c] = std::min(hi[c], f[0].q[c] + 3);
            }
            bool empty = false;
            for (int c = 0; c < 3; c++) empty |= lo[c] > hi[c] || hi[c] < 0 || lo[c] > n;
            if (empty) {  // the second average is too far from the first's base: the nearest allowed
                if (!diff) continue;
                for (int c = 0; c < 3; c++) {
                    int v = std::min(std::max(avg_q[1][c], f[0].q[c] - 4), f[0].q[c] + 3);
                    lo[c] = hi[c] = std::min(std::max(v, 0), n);
                }
            }
            f[1] = fit_sub(px, mask[1], bits, lo, hi, mode);
            if (f[0].err == INT64_MAX || f[1].err == INT64_MAX) continue;
            int64_t err_total = f[0].err + f[1].err;
            if (err_total >= best_err) continue;
            uint64_t v = 0;
            const int shifts[3] = {56, 48, 40};
            for (int c = 0; c < 3; c++) {
                int sh = shifts[c];
                if (diff)
                    v |= (uint64_t)f[0].q[c] << (sh + 3) | (uint64_t)((f[1].q[c] - f[0].q[c]) & 7) << sh;
                else
                    v |= (uint64_t)f[0].q[c] << (sh + 4) | (uint64_t)f[1].q[c] << sh;
            }
            v |= (uint64_t)f[0].table << 37 | (uint64_t)f[1].table << 34 | (uint64_t)(punch ? opaque : diff) << 33 | (uint64_t)flip << 32;
            for (int y = 0; y < 4; y++)
                for (int x = 0; x < 4; x++) {
                    int k = y * 4 + x, s = mask[1][k];
                    int j = x * 4 + y, i = f[s].idx[k];
                    v |= (uint64_t)((i >> 1) & 1) << (j + 16) | (uint64_t)(i & 1) << j;
                }
            best = v;
            best_err = err_total;
        }
    }
    for (int i = 0; i < 8; i++) out[i] = (uint8_t)(best >> (56 - 8 * i));
}

// EAC alpha: a constant block exactly (table 13 has a 0 modifier); otherwise a search over every
// multiplier and table, with the bases near the one that centres the table on the block's range.
void eac_encode(const uint8_t px[16][4], uint8_t out[8]) {
    int a[16];  // pixel i = x * 4 + y
    int lo = 255, hi = 0;
    for (int x = 0; x < 4; x++)
        for (int y = 0; y < 4; y++) {
            a[x * 4 + y] = px[y * 4 + x][3];
            lo = std::min(lo, a[x * 4 + y]);
            hi = std::max(hi, a[x * 4 + y]);
        }
    int base_b = lo, mult_b = 1, tab_b = 13;
    int idx_b[16];
    for (int& i : idx_b) i = 4;
    if (lo != hi) {
        int64_t best = INT64_MAX;
        // per table and multiplier, the bases that centre the table's span on [lo, hi], +-3
        for (int mult = 1; mult < 16; mult++)
            for (int t = 0; t < 16; t++) {
                int centre = (lo + hi) / 2 - (kEacMod[t][3] + kEacMod[t][7]) * mult / 2;
                for (int base = std::max(0, centre - 3); base <= std::min(255, centre + 3); base++) {
                    int64_t e = 0;
                    int idx[16];
                    for (int i = 0; i < 16 && e < best; i++) {
                        int be = INT32_MAX, bi = 0;
                        for (int k = 0; k < 8; k++) {
                            int d = clamp8(base + kEacMod[t][k] * mult) - a[i];
                            if (d * d < be) be = d * d, bi = k;
                        }
                        e += be;
                        idx[i] = bi;
                    }
                    if (e < best) {
                        best = e;
                        base_b = base, mult_b = mult, tab_b = t;
                        memcpy(idx_b, idx, sizeof idx);
                    }
                }
            }
    }
    uint64_t bits = 0;
    for (int i = 0; i < 16; i++) bits |= (uint64_t)idx_b[i] << (45 - 3 * i);
    out[0] = (uint8_t)base_b;
    out[1] = (uint8_t)(mult_b << 4 | tab_b);
    for (int i = 0; i < 6; i++) out[2 + i] = (uint8_t)(bits >> (40 - 8 * i));
}

}  // namespace

int block_bytes(int fmt) {
    return (fmt == kEtc2Rgba8 || fmt == kEacRg11 || fmt == kEacRg11Signed) ? 16 : (fmt == kEtc2Rgb8 || fmt == kEtc2Rgb8A1) ? 8 : 0;
}

void decode_block(int fmt, const uint8_t* b, uint8_t rgba[16][4]) {
    if (fmt == kEacRg11 || fmt == kEacRg11Signed) {
        eac_r11_block(b, rgba, 0, fmt == kEacRg11Signed);
        eac_r11_block(b + 8, rgba, 1, fmt == kEacRg11Signed);
        for (int i = 0; i < 16; i++) rgba[i][2] = 0, rgba[i][3] = 255;
        return;
    }
    bool rgba8 = fmt == kEtc2Rgba8;
    etc2_rgb_block(rgba8 ? b + 8 : b, rgba, fmt == kEtc2Rgb8A1);
    if (rgba8) eac_alpha_block(b, rgba);
}

bool encode_block(int fmt, const uint8_t rgba[16][4], uint8_t* out) {
    if (fmt == kEtc2Rgba8) {
        eac_encode(rgba, out);
        etc1_encode(rgba, out + 8, false);
        return true;
    }
    if (fmt == kEtc2Rgb8 || fmt == kEtc2Rgb8A1) {
        etc1_encode(rgba, out, fmt == kEtc2Rgb8A1);
        return true;
    }
    return false;
}

// ---------------------------------------------------------------- AIF
namespace {

// Where an image's pixel data lives. The ' FMA' (AMF) chunk ends with the data buffer ('buff'
// +0x10 = buffer size, so buffer = AMF start + AMF size - buffer size); each 'addr' chunk names a
// block of that buffer by GUID (+0x10), with size +0x20 and offset +0x28. The image header's GUID
// (+0x40) selects its block.
bool find_data(const Bytes& d, size_t base, size_t at, size_t& data, size_t& size) {
    auto find = [&](const char* tag, size_t from, size_t to) -> size_t {
        for (size_t i = from; i + 16 <= to; i += 16)
            if (!memcmp(&d[i], tag, 4)) return i;
        return std::string::npos;
    };
    size_t amf = find(" FMA", base, d.size());
    if (amf == std::string::npos) return false;
    size_t amf_end = amf + rd32(&d[amf + 4]);
    size_t buff = find("ffub", amf, std::min(amf_end, d.size()));
    if (buff == std::string::npos || amf_end > d.size() || buff + 0x14 > amf_end) return false;
    size_t bsz = rd32(&d[buff + 0x10]);
    if (bsz > amf_end - amf) return false;
    size_t start = amf_end - bsz;
    if (at + 0x50 > d.size()) return false;
    for (size_t a = amf; (a = find("rdda", a, std::min(start, amf_end))) != std::string::npos; a += 16) {
        if (a + 0x2c > d.size()) return false;
        if (memcmp(&d[a + 0x10], &d[at + 0x40], 16)) continue;
        size = rd32(&d[a + 0x20]);
        data = start + rd32(&d[a + 0x28]);
        return data + size <= d.size();
    }
    return false;
}

}  // namespace

std::vector<ImageRef> find_images(const Bytes& d) {
    // An .aif is one ' FIA' container; a Cocos scene embeds its texture atlas as a ' FIA' container.
    // Each container: images ('Xgmi' chunks) up to the end of its ' FMA' chunk (whose buffer may
    // itself start with a nested ' FIA' header: skipped).
    auto at16 = [&](size_t i, const char* t) { return i + 4 <= d.size() && !memcmp(&d[i], t, 4); };
    std::vector<ImageRef> out;
    for (size_t c = 0; c + 16 <= d.size(); c += 16) {
        if (!at16(c, " FIA")) continue;
        size_t amf = c, end = d.size();
        while (amf + 16 <= d.size() && !at16(amf, " FMA")) amf += 16;
        if (amf + 16 <= d.size()) end = std::min(d.size(), amf + rd32(&d[amf + 4]));
        for (size_t i = c; i + 16 <= end; i += 16) {  // chunks are 16-byte aligned
            if (!at16(i, "Xgmi") || i + 0x70 > d.size()) continue;
            ImageRef r;
            r.container = c;
            r.header = i;
            r.fmt = d[i + 0x20];
            r.w = rd16(&d[i + 0x28]);
            r.h = rd16(&d[i + 0x2a]);
            if (find_data(d, c, i, r.data, r.data_size)) out.push_back(r);
        }
        c = (end + 15) / 16 * 16 - 16;
    }
    return out;
}

bool decode_image(const Bytes& d, const ImageRef& img, Bytes& rgba, std::string* err) {
    int bpb = block_bytes(img.fmt);
    if (!bpb) return fail(err, "format " + std::to_string(img.fmt) + " is not ETC"), false;
    int bw = (img.w + 3) / 4, bh = (img.h + 3) / 4;
    if ((size_t)bw * bh * bpb > img.data_size) return fail(err, "pixel data truncated"), false;
    rgba.assign((size_t)img.w * img.h * 4, 0);
    uint8_t blk[16][4];
    for (int by = 0; by < bh; by++)
        for (int bx = 0; bx < bw; bx++) {
            decode_block(img.fmt, &d[img.data + ((size_t)by * bw + bx) * bpb], blk);
            for (int y = 0; y < 4; y++)
                for (int x = 0; x < 4; x++) {
                    int px = bx * 4 + x, py = by * 4 + y;
                    if (px < img.w && py < img.h) memcpy(&rgba[((size_t)py * img.w + px) * 4], blk[y * 4 + x], 4);
                }
        }
    return true;
}

}  // namespace soa::aska
