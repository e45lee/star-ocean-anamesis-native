// soa/aska_image.h (part of soa_codec_tests): SLZ round trips, the ISF payload sum, and ETC2 /
// EAC block encoding (decode(encode(x)) close to x; the same input gives the same bytes).
#include <cstdint>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <string>

#include <soa/aska_image.h>

#include "codec_check.h"

namespace {

uint32_t g_seed = 12345;
uint32_t rnd() { return g_seed = g_seed * 1103515245u + 12345u, g_seed >> 8; }

// The mean squared error per channel of decode(encode(px)).
double block_mse(int fmt, const uint8_t px[16][4], uint8_t* enc) {
    soa::aska::encode_block(fmt, px, enc);
    uint8_t back[16][4];
    soa::aska::decode_block(fmt, enc, back);
    double e = 0;
    int ch = fmt == soa::aska::kEtc2Rgba8 ? 4 : 3;
    for (int i = 0; i < 16; i++)
        for (int c = 0; c < ch; c++) e += (double)(back[i][c] - px[i][c]) * (back[i][c] - px[i][c]);
    return e / (16.0 * ch);
}

}  // namespace

void aska_image_tests() {
    using namespace soa::aska;
    // SLZ: round trips of empty, small, compressible and random data over the 64 KiB chunking
    for (size_t n : {0u, 1u, 100u, 65536u, 65537u, 200000u}) {
        Bytes plain(n);
        for (size_t i = 0; i < n; i++) plain[i] = (uint8_t)(n > 100000 ? rnd() : i / 7);
        Bytes enc = slz_encode(plain), back;
        std::string err;
        codec_check(is_slz(enc) && enc[3] == 5 && enc.size() % 4 == 0, "slz_encode header (n=" + std::to_string(n) + ")");
        codec_check(slz_decode(enc, back, &err) && back == plain, "slz round trip (n=" + std::to_string(n) + ") " + err);
        codec_check(slz_encode(plain) == enc, "slz_encode is deterministic (n=" + std::to_string(n) + ")");
    }
    Bytes notslz = {1, 2, 3}, out;
    codec_check(slz_decode(notslz, out) && out == notslz, "slz_decode passes a non-SLZ file through");

    // ISF: entries and the payload sum (byte sum, padded to 32 with 0xee)
    Bytes isf(0x80, 0);
    memcpy(isf.data(), "\0ISF", 4);
    isf[4] = 4, isf[5] = 3, isf[6] = 0x13, isf[7] = 0x20, isf[8] = 1;
    isf[0x10] = 0x20;                    // name at 0x20
    isf[0x14] = 0x40;                    // payload at 0x40
    isf[0x18] = 5;                       // 5 bytes
    memcpy(&isf[0x20], "a.csv", 6);
    for (int i = 0; i < 5; i++) isf[0x40 + i] = (uint8_t)(i + 1);
    auto entries = isf_entries(isf);
    codec_check(entries.size() == 1 && entries[0].name == "a.csv" && entries[0].offset == 0x40 && entries[0].size == 5, "isf_entries");
    if (entries.size() == 1) {
        isf_update_sum(isf, entries[0]);
        uint32_t want = 15 + 27 * 0xee;
        codec_check(isf_payload_sum(isf, entries[0]) == want && isf[0x1c] == (want & 0xff) && isf[0x1d] == (want >> 8), "isf sum");
    }
    codec_check(isf_entries(Bytes{1, 2, 3}).empty(), "isf_entries of a non-ISF");

    // ETC2 RGBA8 / RGB8 blocks: constant blocks exactly (alpha) or nearly (colour); gradients and
    // noise within bounds; edges of white text on a dark ground
    uint8_t px[16][4], enc[16], enc2[16];
    for (int fmt : {kEtc2Rgba8, kEtc2Rgb8}) {
        std::string f = fmt == kEtc2Rgba8 ? "rgba8" : "rgb8";
        for (int k = 0; k < 16; k++) px[k][0] = 30, px[k][1] = 60, px[k][2] = 120, px[k][3] = 255;
        { double m = block_mse(fmt, px, enc); codec_check(m < 4, f + ": a constant block" + " (mse " + std::to_string((int)m) + ")"); }
        for (int k = 0; k < 16; k++) px[k][0] = px[k][1] = px[k][2] = (uint8_t)(k * 16), px[k][3] = (uint8_t)(255 - k * 10);
        { double m = block_mse(fmt, px, enc); codec_check(m < 150, f + ": a steep gradient" + " (mse " + std::to_string((int)m) + ")"); }
        for (int k = 0; k < 16; k++) {
            bool on = (k % 4) >= 2;
            px[k][0] = on ? 250 : 20, px[k][1] = on ? 250 : 40, px[k][2] = on ? 255 : 90, px[k][3] = on ? 255 : 128;
        }
        { double m = block_mse(fmt, px, enc); codec_check(m < 300, f + ": a sharp edge" + " (mse " + std::to_string((int)m) + ")"); }
        double worst = 0;
        for (int n = 0; n < 200; n++) {
            uint8_t b[3] = {(uint8_t)rnd(), (uint8_t)rnd(), (uint8_t)rnd()};
            for (int k = 0; k < 16; k++)
                for (int c = 0; c < 4; c++) px[k][c] = (uint8_t)std::min(255, std::max(0, b[c % 3] + (int)(rnd() % 41) - 20));
            worst = std::max(worst, block_mse(fmt, px, enc));
            encode_block(fmt, px, enc2);
            if (memcmp(enc, enc2, block_bytes(fmt))) codec_check(false, f + ": encode_block is deterministic");
        }
        codec_check(worst < 200, f + ": noisy blocks (worst mse " + std::to_string((int)worst) + ")");
    }
    for (int k = 0; k < 16; k++) px[k][0] = px[k][1] = px[k][2] = 0, px[k][3] = 77;
    encode_block(kEtc2Rgba8, px, enc);
    uint8_t back[16][4];
    decode_block(kEtc2Rgba8, enc, back);
    bool exact = true;
    for (int k = 0; k < 16; k++) exact &= back[k][3] == 77;
    codec_check(exact, "rgba8: a constant alpha is exact");
    codec_check(!encode_block(kEtc2Rgb8A1, px, enc) && !encode_block(kJpeg, px, enc), "encode_block refuses formats it doesn't write");
}
