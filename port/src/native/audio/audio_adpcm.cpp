// Aska::AskaADPCM: the voices' 4-bit ADPCM decoder (port/decomp/audio/codec.c; audio_layout.h has the
// format). SLVoice::SubmitBufferDataADPCM decodes each streamed chunk with Decode into a buffer it then
// enqueues to OpenSL. The four Decode_* differ only in the channel count and the PCM width, so they are
// one template here; the guest's quirks are kept: the predictor is never clamped (a sample is its low
// 16 bits, or bits 8-15 biased by 0x80 for 8-bit PCM), a block's header step is used unclamped for its
// first nibble, and a block shorter than its header (blockSize < 5 mono / 9 stereo) skips 4 / 8 bytes
// at a time and decodes nothing.
#include "native/audio/audio_check.h"
#include "native/audio/audio_layout.h"
#include "native/common/live_leaf.h"
#include "native/common/native_method.h"

namespace soa::native::audio {

namespace {

// One channel's decoder state: the predicted sample and the step.
struct AdpcmChannel {
    s32 predictor;
    s32 step;

    // Decodes one nibble: the predictor moves by +-(2 * magnitude + 1) * step / 8 (an arithmetic shift
    // of the 32-bit product), the step scales by 57 / 77 / 102 / 128 / 153 over 64 and is clamped to
    // [0x7f, 0x6000]. Returns the new predictor.
    s32 Decode(u32 nibble) {
        u32 magnitude = nibble & 7;
        s32 diff = (s32)((magnitude * 2 + 1) * (u32)step) >> 3;
        if (nibble & 8) diff = -diff;
        predictor = (s32)((u32)predictor + (u32)diff);
        s32 scale = magnitude < 4 ? 57 : magnitude == 4 ? 77 : magnitude == 5 ? 102 : magnitude == 6 ? 128 : 153;
        step = (step * scale) >> 6;
        if (step > 0x5fff) step = 0x6000;
        if (step < 0x80) step = 0x7f;
        return predictor;
    }
};

inline s16 read_s16(const u8* p) { return (s16)(u16)(p[0] | p[1] << 8); }

// Writes one sample: 16-bit PCM keeps the predictor's low 16 bits, 8-bit PCM bits 8-15 biased by 0x80.
template <bool kOut16>
inline u8* put_sample(u8* out, s32 predictor) {
    if constexpr (kOut16) {
        u16 v = (u16)predictor;
        out[0] = (u8)v;
        out[1] = (u8)(v >> 8);
        return out + 2;
    } else {
        *out = (u8)(((u32)predictor >> 8) - 0x80);
        return out + 1;
    }
}

// The four Decode_*: blocks of [header: per channel an s16 predictor and an s16 step][blockSize - header
// data bytes]; mono takes the low nibble first, stereo the low nibble for the left channel and the high
// one for the right. Returns the bytes written. A block cut short by `size` ends the stream after its
// last whole byte.
template <int kChannels, bool kOut16>
u32 decode_blocks(s32 blockSize, const u8* in, u32 size, u8* out) {
    constexpr u32 kHeader = 4 * kChannels;
    u32 written = 0;
    if (size == 0) return 0;
    u32 consumed = 0;
    do {
        // A block no longer than its header: skipped, header by header.
        while (blockSize < (s32)kHeader + 1) {
            in += kHeader;
            consumed += kHeader;
            if (size <= consumed) return written;
        }
        AdpcmChannel ch[2];
        for (int k = 0; k < kChannels; k++) ch[k] = {read_s16(in + 4 * k), read_s16(in + 4 * k + 2)};
        // blockSize - kHeader data bytes (the guest counts down from blockSize - kHeader + 1 while > 1).
        u32 i = 0;
        for (s32 left = blockSize - (s32)kHeader + 1;; i++) {
            u8 b = in[kHeader + i];
            if constexpr (kChannels == 1) {
                out = put_sample<kOut16>(out, ch[0].Decode(b & 0xf));
                out = put_sample<kOut16>(out, ch[0].Decode(b >> 4));
            } else {
                out = put_sample<kOut16>(out, ch[0].Decode(b & 0xf));
                out = put_sample<kOut16>(out, ch[1].Decode(b >> 4));
            }
            written += kOut16 ? 4 : 2;
            if (size <= consumed + kHeader + 1 + i) break;
            if (!(1 < --left)) break;
        }
        in += kHeader + 1 + i;
        consumed += kHeader + 1 + i;
    } while (consumed < size);
    return written;
}

}  // namespace

bool AskaADPCM::Init(s32 channels, s32 bits, s32 blockSize) {
    if ((u32)(channels - 1) > 1) return false;
    if (bits != 16 && bits != 8) return false;
    if (blockSize != 32 && blockSize != 64 && blockSize != 128 && blockSize != 256) return false;
    m_bits = bits;
    m_blockSize = blockSize;
    m_channels = channels;
    m_encStep[0] = m_encStep[1] = 0;
    m_encPredictor[0] = m_encPredictor[1] = 0;
    return true;
}

u32 AskaADPCM::Decode_M08(const u8* in, u32 size, u8* out) { return decode_blocks<1, false>(m_blockSize, in, size, out); }
u32 AskaADPCM::Decode_M16(const u8* in, u32 size, u8* out) { return decode_blocks<1, true>(m_blockSize, in, size, out); }
u32 AskaADPCM::Decode_S08(const u8* in, u32 size, u8* out) { return decode_blocks<2, false>(m_blockSize, in, size, out); }
u32 AskaADPCM::Decode_S16(const u8* in, u32 size, u8* out) { return decode_blocks<2, true>(m_blockSize, in, size, out); }

// By the channel count and the PCM width; other channel counts decode nothing (0). (A 64-bit result
// in the guest: 0 or the u32 the Decode_* return.)
u32 AskaADPCM::Decode(const u8* in, u32 size, u8* out) {
    if (m_channels == 2) return m_bits == 8 ? Decode_S08(in, size, out) : Decode_S16(in, size, out);
    if (m_channels == 1) return m_bits == 8 ? Decode_M08(in, size, out) : Decode_M16(in, size, out);
    return 0;
}

s32 AskaADPCM::GetSamplesPerBlock(s32 blockSize, s32 channels) {
    if (channels == 2) return blockSize - 8;
    if (channels == 1) return blockSize * 2 - 8;
    return 0;
}

namespace {
using live::kInt;
// The decoders read `size` bytes at x1 and write at most 4 bytes per input byte at x3 (16-bit PCM,
// two samples per byte).
#define AUDIO_ADPCM_DECODER(sym, method, label) \
    LEAF_METHOD(leaf_family(), sym, method, sizeof(AskaADPCM), kInt, label, {live::out_len(1, 2, 1, 0, 0x40000), live::out_len(3, 2, 4, 0, 0x40000)})
AUDIO_ADPCM_DECODER("_ZN4Aska9AskaADPCM6DecodeEPKhjPh", &AskaADPCM::Decode, "Aska::AskaADPCM::Decode");
AUDIO_ADPCM_DECODER("_ZN4Aska9AskaADPCM10Decode_M08EPKhjPh", &AskaADPCM::Decode_M08, "Aska::AskaADPCM::Decode_M08");
AUDIO_ADPCM_DECODER("_ZN4Aska9AskaADPCM10Decode_M16EPKhjPh", &AskaADPCM::Decode_M16, "Aska::AskaADPCM::Decode_M16");
AUDIO_ADPCM_DECODER("_ZN4Aska9AskaADPCM10Decode_S08EPKhjPh", &AskaADPCM::Decode_S08, "Aska::AskaADPCM::Decode_S08");
AUDIO_ADPCM_DECODER("_ZN4Aska9AskaADPCM10Decode_S16EPKhjPh", &AskaADPCM::Decode_S16, "Aska::AskaADPCM::Decode_S16");
#undef AUDIO_ADPCM_DECODER
LEAF_METHOD(leaf_family(), "_ZN4Aska9AskaADPCM4InitEiii", &AskaADPCM::Init, sizeof(AskaADPCM), kInt, "Aska::AskaADPCM::Init", {});
LEAF_FUNCTION(leaf_family(), "_ZN4Aska9AskaADPCM18GetSamplesPerBlockEii", &AskaADPCM::GetSamplesPerBlock, kInt, "Aska::AskaADPCM::GetSamplesPerBlock", {});
}  // namespace

}  // namespace soa::native::audio
