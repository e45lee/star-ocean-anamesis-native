// Differential tests of the AskaADPCM natives (audio_adpcm.cpp) against the guest's: random streams
// (random headers: predictors and steps over the whole s16 range, negative steps included; random
// nibbles) through the four Decode_* and Decode, for every valid block size and the degenerate ones
// (shorter than the header: the skip path), with input sizes that end mid-block and mid-header; the
// outputs (with a guard area after them), the byte counts and the object compared. Init over valid and
// invalid arguments (the object after it compared), GetSamplesPerBlock over channel counts.
#include <cstring>
#include <vector>

#include "soaruntime/core/cpu.h"
#include "native/audio/audio_layout.h"
#include "native/common/test.h"

using namespace soa;
using namespace soa::native::audio;

namespace {

struct Decoder {
    const char* sym;
    u32 (AskaADPCM::*fn)(const u8*, u32, u8*);
    s32 channels, bits;
};
const Decoder kDecoders[] = {
    {"_ZN4Aska9AskaADPCM10Decode_M08EPKhjPh", &AskaADPCM::Decode_M08, 1, 8},
    {"_ZN4Aska9AskaADPCM10Decode_M16EPKhjPh", &AskaADPCM::Decode_M16, 1, 16},
    {"_ZN4Aska9AskaADPCM10Decode_S08EPKhjPh", &AskaADPCM::Decode_S08, 2, 8},
    {"_ZN4Aska9AskaADPCM10Decode_S16EPKhjPh", &AskaADPCM::Decode_S16, 2, 16},
    // Decode dispatches by the object's channels / bits (and 0 for other channel counts)
    {"_ZN4Aska9AskaADPCM6DecodeEPKhjPh", &AskaADPCM::Decode, 1, 16},
    {"_ZN4Aska9AskaADPCM6DecodeEPKhjPh", &AskaADPCM::Decode, 2, 8},
    {"_ZN4Aska9AskaADPCM6DecodeEPKhjPh", &AskaADPCM::Decode, 1, 8},
    {"_ZN4Aska9AskaADPCM6DecodeEPKhjPh", &AskaADPCM::Decode, 2, 16},
    {"_ZN4Aska9AskaADPCM6DecodeEPKhjPh", &AskaADPCM::Decode, 3, 16},
};

}  // namespace

NATIVE_TEST("audio/adpcm-decode") {
    const s32 blockSizes[] = {32, 64, 128, 256, 36, 100, 9, 8, 5, 4, 1};
    constexpr u32 kGuard = 64;
    for (const Decoder& d : kDecoders)
        for (s32 bs : blockSizes)
            for (int round = 0; round < 6 && !t.failures(); round++) {
                u32 size = round == 0 ? 0 : (u32)t.rand_int(1, 3 * 256 + 17);
                if (round == 1) size = (u32)bs * (u32)t.rand_int(1, 4);  // whole blocks
                std::vector<u8> in = t.rand_bytes(size + 16);
                std::vector<u8> out_g(4 * size + kGuard, 0xa5), out_n(4 * size + kGuard, 0xa5);
                alignas(16) AskaADPCM obj_g{}, obj_n{};
                obj_g.m_channels = obj_n.m_channels = d.channels;
                obj_g.m_bits = obj_n.m_bits = d.bits;
                obj_g.m_blockSize = obj_n.m_blockSize = bs;
                obj_g.m_encPredictor[0] = obj_n.m_encPredictor[0] = 0x1234;
                u32 g = (u32)t.call(d.sym, {(u64)&obj_g, (u64)in.data(), (u64)size, (u64)out_g.data()});
                u32 n = (obj_n.*d.fn)(in.data(), size, out_n.data());
                if (g != n) t.fail("%s ch %d bits %d block %d size %u: guest %u bytes native %u", d.sym, d.channels, d.bits, bs, size, g, n);
                if (out_g != out_n) {
                    size_t k = 0;
                    while (k < out_g.size() && out_g[k] == out_n[k]) k++;
                    t.fail("%s ch %d bits %d block %d size %u: output differs at byte %zu (guest %02x native %02x)", d.sym, d.channels, d.bits,
                           bs, size, k, out_g[k], out_n[k]);
                }
                if (std::memcmp(&obj_g, &obj_n, sizeof obj_g) != 0) t.fail("%s: the object differs", d.sym);
            }
}

NATIVE_TEST("audio/adpcm-init") {
    const s32 values[] = {-1, 0, 1, 2, 3, 4, 7, 8, 9, 16, 24, 31, 32, 33, 48, 64, 96, 127, 128, 160, 192, 224, 255, 256, 257, 288, 512, 0x40000020};
    for (int i = 0; i < 2000 && !t.failures(); i++) {
        s32 ch = values[t.rand_int(0, 7)], bits = values[t.rand_int(4, 11)], bs = values[t.rand_int(0, 27)];
        if (i % 3 == 0) ch = t.rand_int(1, 2), bits = t.rand_int(0, 1) ? 8 : 16;
        alignas(16) AskaADPCM obj_g, obj_n;
        for (u32 k = 0; k < sizeof obj_g; k++) reinterpret_cast<u8*>(&obj_g)[k] = (u8)t.rand_int(0, 255);
        std::memcpy(&obj_n, &obj_g, sizeof obj_g);
        u64 g = t.call("_ZN4Aska9AskaADPCM4InitEiii", {(u64)&obj_g, (u64)(u32)ch, (u64)(u32)bits, (u64)(u32)bs}) & 0xffffffffu;
        u64 n = obj_n.Init(ch, bits, bs);
        if (g != n) t.fail("Init(%d, %d, %d): guest %llu native %llu", ch, bits, bs, (unsigned long long)g, (unsigned long long)n);
        if (std::memcmp(&obj_g, &obj_n, sizeof obj_g) != 0) t.fail("Init(%d, %d, %d): the object differs", ch, bits, bs);
    }
    for (s32 ch = -1; ch <= 3; ch++)
        for (s32 bs : {0, 8, 32, 33, 256, -5})
            t.expect_eq((s32)t.call("_ZN4Aska9AskaADPCM18GetSamplesPerBlockEii", {(u64)(u32)bs, (u64)(u32)ch}), AskaADPCM::GetSamplesPerBlock(bs, ch),
                        "GetSamplesPerBlock");
}
