// audio_layout.h: the guest data layouts of the `audio` subsystem (sound and voice: the game's sound engine (Aska::Sound*, Audio*, SLVoice, AskaOGG / AskaADPCM, Sequencer2; Framework::CSound*; CSoundManager, the voice managers)).
//
// Types first (port/PLAN.md task 6): every guest class or struct this subsystem's natives touch is
// recovered here before the code that uses it, as a C++ class with the guest's layout byte for byte
// and the guest's methods attached as members (not a struct + free functions):
//   - fields at the guest's offsets, named after their use (m_hp); unknown bytes as named padding
//     (u8 unk_0c[4]), never offset arithmetic in the natives;
//   - a static_assert per known field offset and one for sizeof, so a wrong guess fails the build;
//   - a comment naming where the layout was read (constructor, decompile in port/decomp/audio/).
// Natives are these members (this->m_hp), never *(T*)(p + off). Keep the classes standard-layout (no
// C++ virtual, no non-static members of reference type), so offsetof works. The guest is AArch64 LP64; the
// host (x86-64 / AArch64) has the same sizes and alignments for these plain types.
// `tools/subsystem.py export-types audio` turns the structs into port/decomp/audio/types.json for Ghidra.
#ifndef SOA_NATIVE_AUDIO_LAYOUT_H
#define SOA_NATIVE_AUDIO_LAYOUT_H

#include <cstddef>
#include <cstdint>

#include "../kernel/kernel_layout.h"  // Task, CTimeElement (kernel's classes)
#include "../lib_vorbis/lib_vorbis_layout.h"  // the libogg / libVorbis structs AskaOGG embeds
#include "../math/math_layout.h"      // Matrix, Vector, Quaternion (math's classes)
#include "../memory/memory_layout.h"  // TObjectContainer (memory's class)
#include "../sync/sync_layout.h"      // FastCriticalSection, CMutex (sync's classes)
#include "gen/audio_addresses.h"     // the guest addresses (tools/gen_addresses.py)

namespace soa::native::audio {

using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using s8 = std::int8_t;
using s16 = std::int16_t;
using s32 = std::int32_t;
using s64 = std::int64_t;

class SLVoice;
class SoundServer;  // Aska::SoundServer: the pools (opaque here: guest calls)

// The locks and the task base are the lower subsystems' classes: sync's FastCriticalSection (0x90,
// lock word +0x38, waiter count +0x3c, Semaphore +0x78) and kernel's Task (0x28).
using FastCriticalSection = sync::FastCriticalSection;
using Task = kernel::Task;
using CTimeElement = kernel::CTimeElement;
using CMutex = sync::CMutex;
using Matrix = math::Matrix;
using Vector = math::Vector;
using Quaternion = math::Quaternion;

// ---- The signal path (port/decomp/audio/mixer.c) ------------------------------------------------------
//
// Aska::AudioSignalNotify: an INotify holding the voices to signal, guest size 0x138. Layout from the
// construction SoundManager::Initialize inlines (vtable, FastCriticalSection at +0xa8, memset of the 20
// slots) and the four methods: each takes m_cs (the FastCriticalSection enter / leave inlined), then
// works on m_voices. Handler (slot 0; the dispatcher's message 0x467 / 0x468 from AudioSignal::Run, and
// AudioSafetySignalThread's direct call) calls each voice's AudioSignal(index) (SLVoice vtable slot 10)
// under the lock.
class AudioSignalNotify {
public:
    static constexpr int kSlots = 20;
    static constexpr int kSlotVoiceAudioSignal = 10;  // Aska::SLVoice::AudioSignal(unsigned long): vtable + 0x50

    // vtable slot 0 (INotify::Handler)
    void Handler(u64 arg);                    // _ZN4Aska17AudioSignalNotify7HandlerEm
    // vtable slots 1 / 2: the destructors (not bound: run once at shutdown)
    bool AddSignalVoiceList(SLVoice* voice);  // _ZN4Aska17AudioSignalNotify18AddSignalVoiceListEPNS_7SLVoiceE: the first free slot
    bool DeleteSignalVoiceList(SLVoice* voice);  // _ZN4Aska17AudioSignalNotify21DeleteSignalVoiceListEPNS_7SLVoiceE: the first slot holding it
    u32 GetSignalCount() const;               // _ZNK4Aska17AudioSignalNotify14GetSignalCountEv: the slots in use

    const void* vtable;           // 0x00: _ZTVN4Aska17AudioSignalNotifyE + 0x10
    SLVoice* m_voices[kSlots];    // 0x08: null = free
    FastCriticalSection m_cs;     // 0xa8: guards m_voices (its lock word at +0xe0, waiters +0xe4, semaphore +0x120)
};
static_assert(offsetof(AudioSignalNotify, m_voices) == 0x08);
static_assert(offsetof(AudioSignalNotify, m_cs) == 0xa8);
static_assert(sizeof(AudioSignalNotify) == 0x138);

// Aska::AudioSignal: the system task that posts the two notifies to the message dispatcher each frame;
// guest size 0x2a0 (SoundManager::Initialize: SoundMemory::Malloc(0x2a0), Task's construction inlined,
// both notifies, m_lastRunTime = 0); SoundManager + 0x40 holds it. AddSignalVoiceList picks the notify
// with fewer voices; AudioSafetySignalNotify::Handler compares m_lastRunTime with the CPU time.
class AudioSignal {
public:
    static constexpr u16 kMessageSignal0 = 0x467, kMessageSignal1 = 0x468;

    Task m_task;                    // 0x000: vtable _ZTVN4Aska11AudioSignalE + 0x10 (slot 13 Run)
    AudioSignalNotify m_notify[2];  // 0x028, 0x160
    u32 m_lastRunTime;              // 0x298: Global::GetCPUTime() at the last Run
    u8 unk_29c[4];                  // 0x29c: (allocation padding)
};
static_assert(offsetof(AudioSignal, m_notify) == 0x28);
static_assert(offsetof(AudioSignal, m_lastRunTime) == 0x298);
static_assert(sizeof(AudioSignal) == 0x2a0);

// ---- The codecs (port/decomp/audio/codec.c) -----------------------------------------------------------
//
// Aska::AskaADPCM: tri-Ace's 4-bit ADPCM (a Yamaha-style step table: the step scales by 57 / 77 / 102
// / 128 / 153 over 64 for the magnitudes 0-3 / 4 / 5 / 6 / 7, clamped to [127, 0x6000]); guest size
// 0x1c (SLVoice + 0x38). Layout from Init (channels, bits, block size checked; the encoder state zeroed),
// Encode_* (the state at +0x0c / +0x14 carried across calls) and Decode_* (each block's header: per
// channel an s16 predictor and an s16 step, then (block - 4 * channels) bytes of two nibbles; mono:
// low nibble first, stereo: low nibble left, high nibble right). The decoders keep no state.
class AskaADPCM {
public:
    bool Init(s32 channels, s32 bits, s32 blockSize);   // _ZN4Aska9AskaADPCM4InitEiii
    u32 Decode(const u8* in, u32 size, u8* out);        // _ZN4Aska9AskaADPCM6DecodeEPKhjPh: by channels / bits
    u32 Decode_M08(const u8* in, u32 size, u8* out);    // _ZN4Aska9AskaADPCM10Decode_M08EPKhjPh
    u32 Decode_M16(const u8* in, u32 size, u8* out);    // _ZN4Aska9AskaADPCM10Decode_M16EPKhjPh
    u32 Decode_S08(const u8* in, u32 size, u8* out);    // _ZN4Aska9AskaADPCM10Decode_S08EPKhjPh
    u32 Decode_S16(const u8* in, u32 size, u8* out);    // _ZN4Aska9AskaADPCM10Decode_S16EPKhjPh
    static s32 GetSamplesPerBlock(s32 blockSize, s32 channels);  // _ZN4Aska9AskaADPCM18GetSamplesPerBlockEii
    // Encode / Encode_{M,S}{08,16}: the encoder (no caller in 3.7.0's flows; not ported)

    s32 m_channels;   // 0x00: 1 or 2
    s32 m_bits;       // 0x04: 8 or 16 (the PCM side)
    s32 m_blockSize;  // 0x08: 32, 64, 128 or 256 bytes
    s32 m_encPredictor[2];  // 0x0c: the encoder's predictor per channel (Init zeroes them)
    s32 m_encStep[2];       // 0x14: the encoder's step per channel (Init zeroes them)
};
static_assert(offsetof(AskaADPCM, m_blockSize) == 0x08);
static_assert(offsetof(AskaADPCM, m_encPredictor) == 0x0c);
static_assert(offsetof(AskaADPCM, m_encStep) == 0x14);
static_assert(sizeof(AskaADPCM) == 0x1c);

// ---- 3D sound (port/decomp/audio/mixer.c) --------------------------------------------------------------
//
// Aska::Audio3DObject: the base of the listener and the emitters, guest size 0xf0 (the constructors
// AudioListener / AudioEmitter inline it: vtable, the list links, m_node = 0, the FastCriticalSection at
// +0x20). UpdateMatrix copies the node's world matrix (its vtable slot 19), or the identity without a
// node, under the lock; Compute reads that copy under the lock.
class Audio3DObject {
public:
    static constexpr int kSlotNodeWorldMatrix = 19;  // HierarchicalObject vtable + 0x98: the world matrix (const Matrix*)

    void UpdateMatrix();  // _ZN4Aska13Audio3DObject12UpdateMatrixEv

    const void* vtable;              // 0x00: _ZTVN4Aska13Audio3DObjectE + 0x10, or a derived class's
    Audio3DObject* m_prev;           // 0x08: Audio3DEngine's emitter list
    Audio3DObject* m_next;           // 0x10
    void* m_node;                    // 0x18: the Aska::HierarchicalObject it follows (opaque: its vtable)
    FastCriticalSection m_cs;        // 0x20: guards m_matrix (lock word +0x58, semaphore +0x98)
    Matrix m_matrix;                 // 0xb0
};
static_assert(offsetof(Audio3DObject, m_node) == 0x18);
static_assert(offsetof(Audio3DObject, m_cs) == 0x20);
static_assert(offsetof(Audio3DObject, m_matrix) == 0xb0);
static_assert(sizeof(Audio3DObject) == 0xf0);

// Aska::AudioListener: guest size 0x120 (Audio3DEngine + 0x10; the emitter list's TList at +0x130).
// Compute: the ear position = the matrix applied to (0, 0, m_offsetZ, 1); the orientation from the matrix.
class AudioListener {
public:
    void Compute();  // _ZN4Aska13AudioListener7ComputeEv

    Audio3DObject base;        // 0x000: vtable _ZTVN4Aska13AudioListenerE + 0x10
    float m_offsetZ;           // 0x0f0: SetAudioListener's offset (the ears in front of the node)
    u8 unk_0f4[0xc];           // 0x0f4
    Vector m_position;         // 0x100
    Quaternion m_orientation;  // 0x110
};
static_assert(offsetof(AudioListener, m_offsetZ) == 0xf0);
static_assert(offsetof(AudioListener, m_position) == 0x100);
static_assert(offsetof(AudioListener, m_orientation) == 0x110);
static_assert(sizeof(AudioListener) == 0x120);

// Aska::AudioEmitter: a 3D sound source (SEControlObject + 0x200), guest size 0x128 (the constructor: the
// base's fields, 10.0 / 800.0 at +0xf0 / +0xf4, the speaker gains from a table, 1.0 at +0x110, no curve).
// Compute (SoundProcessSync, per emitter with a node, after the listener's): the gains of the six speaker
// slots (index 3 unused: the speakers' layout leaves it out) from the source's place relative to the
// listener: a "far" share panned between the two speakers whose angles bracket the source's (around the
// listener's up axis), a "near" share spread over five by inverse distance, both scaled by the two
// attenuation curves and the master volume (port/decomp/audio/mixer.c; the order of operations from the
// disassembly, where Ghidra's decompile reorders products).
class AudioEmitter {
public:
    static constexpr int kSpeakers = 6;
    static constexpr int kSlotCurveValue = 15;  // the curves' vtable + 0x78: float GetValue(float) const

    void Compute();  // _ZN4Aska12AudioEmitter7ComputeEv

    Audio3DObject base;          // 0x000: vtable _ZTVN4Aska12AudioEmitterE + 0x10
    float m_unk0f0;              // 0x0f0: 10.0 at construction (not read by Compute)
    float m_distanceScale;       // 0x0f4: 800.0 at construction: the emitter's curve's distance unit
    float m_gains[kSpeakers];    // 0x0f8: Compute's output
    float m_rangeScale;          // 0x110: 1.0
    u8 unk_114[4];               // 0x114
    void* m_curve;               // 0x118: the emitter's attenuation curve (TFastQuadraticCurve<N>: vtable slot 15)
    u8 m_computed;               // 0x120: set by Compute
    u8 unk_121[7];               // 0x121
};
static_assert(offsetof(AudioEmitter, m_distanceScale) == 0xf4);
static_assert(offsetof(AudioEmitter, m_gains) == 0xf8);
static_assert(offsetof(AudioEmitter, m_rangeScale) == 0x110);
static_assert(offsetof(AudioEmitter, m_curve) == 0x118);
static_assert(offsetof(AudioEmitter, m_computed) == 0x120);
static_assert(sizeof(AudioEmitter) == 0x128);

// ---- The sound objects (port/decomp/audio/sound_manager.c) -------------------------------------------
//
// Aska::TList<T>: an intrusive list whose sentinel is a T (the T's m_prev / m_next at +0x08 / +0x10), then
// the count; layout from the SoundManager constructor (TList<SoundHandle>, <SoundCommand>, <SoundPass>,
// <AudioInterface>, <SoundObject>: the next member right after the count's 8-byte slot) and the inlined
// add / delete code (TList::Add appends, TList::Delete unlinks, counts down but not below 0, clears the
// links). (containers' TList<LinkElement> is the same template with a bare link as the sentinel.)
template <typename T>
class TList {
public:
    void Add(T* e) {  // append at the tail
        T* last = m_sentinel.m_prev;
        e->m_prev = last;
        e->m_next = &m_sentinel;
        m_sentinel.m_prev = e;
        last->m_next = e;
        m_count++;
    }
    void Delete(T* e) {
        T* prev = e->m_prev;
        T* next = e->m_next;
        if (prev) prev->m_next = next;
        if (next) next->m_prev = prev;
        if (m_count > 0) m_count--;
        e->m_prev = nullptr;
        e->m_next = nullptr;
    }
    T* begin() { return m_sentinel.m_next; }
    T* end() { return &m_sentinel; }

    const void* vtable;  // 0x00: _ZTVN4Aska5TListI...EE + 0x10
    T m_sentinel;        // 0x08: m_prev = the last element, m_next = the first
    s32 m_count;
    u8 unk_count[4];
};

class AudioPlayer;
class WaveVoiceBase;
class WaveBuffer;
class SoundObject;

// Aska::TSoundDynamicQueue<T>: a growable ring of T (the sound thread's mailboxes: AudioPlayer's messages,
// SoundObject's requests, EffectorRequest's), guest size 0x20. Layout from SEControlObject's constructor
// (vtable, m_write / m_read = 1 / 0 as one u64, then a 5-slot buffer from SoundMemory::Malloc) and AddEx
// (port/decomp/audio/sound_manager.c). m_read is the last slot read, m_write the next one written: empty
// when the slot after m_read is m_write, full when m_write == m_read. AddEx grows a full ring by one
// slot: a new buffer (SoundMemory::Malloc) with the ring unrolled from m_write (the oldest slot, the one
// last read, first), the old one returned with operator delete (the game's mix of allocators), m_read 0,
// the new slot at the end. Its owners take their FastCriticalSection around it (inlined in the guest).
template <typename T>
class TSoundDynamicQueue {
public:
    T* AddEx();           // the slot to fill, null when the buffer can't grow
    bool Get(T* out);     // the next unread slot copied out (the owners' inlined pop)

    const void* vtable;   // 0x00: _ZTVN4Aska18TSoundDynamicQueueI..EE + 0x10
    u32 m_write;          // 0x08: the next slot written
    u32 m_read;           // 0x0c: the last slot read
    u32 m_capacity;       // 0x10
    u8 unk_14[4];         // 0x14
    T* m_items;           // 0x18
};

// Aska::AudioMessage: a message for an AudioPlayer (Sequencer2's notes send them; AudioPlayer::GetMessage
// hands them to its AudioRun), guest size 0x18 (TSoundDynamicQueue<AudioMessage>::AddEx's stride).
class AudioMessage {
public:
    u32 m_message;        // 0x00: 0 play, 1 stop, 2 pause, 3 resume, 4.., 5-9 (Sequencer2's note types)
    u8 unk_04[4];         // 0x04: never written by SendMessage
    const void* m_arg0;   // 0x08
    const void* m_arg1;   // 0x10
};
static_assert(sizeof(AudioMessage) == 0x18);

// Aska::SoundObject::RequestContainer: a request for a sound object's AudioRun (SoundObject vtable slot 11
// handles it), guest size 0x10 (RequestSet's inlined AddEx stride).
class SoundRequest {
public:
    u32 m_type;           // 0x00
    u8 unk_04[4];         // 0x04: never written by RequestSet
    const void* m_data;   // 0x08
};
static_assert(sizeof(SoundRequest) == 0x10);

static_assert(offsetof(TSoundDynamicQueue<AudioMessage>, m_write) == 0x08);
static_assert(offsetof(TSoundDynamicQueue<AudioMessage>, m_capacity) == 0x10);
static_assert(offsetof(TSoundDynamicQueue<AudioMessage>, m_items) == 0x18);
static_assert(sizeof(TSoundDynamicQueue<AudioMessage>) == 0x20);

// The stream behind a voice's wave buffer: resource's Aska::MultiMediaStream (resource_layout.h types it
// to 0x90; the object is larger): the vtable slots and the fields the voices and the sound manager use.
class WaveStreamView {
public:
    static constexpr int kSlotLock = 19;     // s64 Lock(void** out, u64 size)
    static constexpr int kSlotUnlock = 20;   // s64 Unlock(u64 size)
    static constexpr int kSlotIsEnd = 23;    // bool (bool, int): the voices ask (1, 0) "played out?", (0, 0) "nothing left to read?"

    const void* vtable;  // 0x000
    u8 unk_008[0x84];    // 0x008
    u8 m_loopTail;       // 0x08c: (MultiMediaStream::unk_8c's low byte) the read reached the loop's end: the voices drop the tail frames
    u8 unk_08d[0x36f];   // 0x08d
    s32 m_pending;       // 0x3fc: nonzero while a read is in flight (FlushDeletingSoundObject waits for 0)
    u8 unk_400[0x328];   // 0x400
    u8 m_abort;          // 0x728: AddDeletingSoundObject sets it for a streaming object (m_type bit 3)
};
static_assert(offsetof(WaveStreamView, m_loopTail) == 0x8c);
static_assert(offsetof(WaveStreamView, m_pending) == 0x3fc);
static_assert(offsetof(WaveStreamView, m_abort) == 0x728);

// Aska::AFF::AaoWAVE: a wave's header in the sound data (opaque beyond what the voices read).
class AaoWAVE {
public:
    u8 unk_00[0x14];
    u8 m_codec;              // 0x14: 0x0c PCM, 0x0d ADPCM, 0x0e OGG (SLVoice::m_codec)
    u8 m_channels;           // 0x15
    u8 unk_16;               // 0x16
    u8 m_bits;               // 0x17
    u8 unk_18[0x40];         // 0x18: the rate (+0x18), ...
    u32 m_loopHeadFrames;    // 0x58: frames the voice drops after a loop start (SubmitBufferDataADPCM)
    u32 m_loopTailFrames;    // 0x5c: frames it drops before the stream's loop end
};
static_assert(offsetof(AaoWAVE, m_codec) == 0x14);
static_assert(offsetof(AaoWAVE, m_bits) == 0x17);
static_assert(offsetof(AaoWAVE, m_loopHeadFrames) == 0x58);

// Aska::WaveBuffer (CBRBuffer / VBRBuffer, guest size 0x78: SLVoice::CreateVoice's SoundMemory::Malloc(0x78)):
// the stream and a TQueue<unsigned int, 16> of the sizes locked and not yet unlocked. Layout from
// CreateVoice's construction, CreateBuffer, LockBuffer, UnlockBuffer.
class WaveBuffer {
public:
    static constexpr u32 kSlots = 17;  // TQueue<u32, 16>: 16 + 1

    s64 LockBuffer(void** out, u64 size, bool append);  // _ZN4Aska10WaveBuffer10LockBufferEPPvmb
    s64 UnlockBuffer();                                 // _ZN4Aska10WaveBuffer12UnlockBufferEv

    const void* vtable;           // 0x00: _ZTVN4Aska9CBRBufferE / _ZTVN4Aska9VBRBufferE + 0x10
    WaveStreamView* m_stream;     // 0x08
    const AaoWAVE* m_format;      // 0x10
    const void* m_queueVtable;    // 0x18: _ZTVN4Aska6TQueueIjLi16EEE + 0x10
    u32 m_write;                  // 0x20: the next slot written (1 at construction)
    u32 m_read;                   // 0x24: the last slot read
    u32 m_sizes[kSlots];          // 0x28
    u8 unk_6c[4];                 // 0x6c
    u32 m_isVBR;                  // 0x70: 1 for a VBRBuffer
    u16 unk_74;                   // 0x74
    u8 unk_76;                    // 0x76
    u8 unk_77;                    // 0x77
};
static_assert(offsetof(WaveBuffer, m_stream) == 0x08);
static_assert(offsetof(WaveBuffer, m_write) == 0x20);
static_assert(offsetof(WaveBuffer, m_sizes) == 0x28);
static_assert(offsetof(WaveBuffer, m_isVBR) == 0x70);
static_assert(sizeof(WaveBuffer) == 0x78);

// Aska::WaveVoiceBase: only its wave buffer (+0x30; SLVoice below has the whole layout).
class WaveVoiceBase {
public:
    u8 unk_00[0x30];
    WaveBuffer* m_buffer;      // 0x30
};
static_assert(offsetof(WaveVoiceBase, m_buffer) == 0x30);

// An OpenSL ES interface as the guest holds it (SLAndroidSimpleBufferQueueItf, SLPlayItf, SLVolumeItf, ...):
// a pointer to a table of functions; the HLE (runtime) makes them. Slot 0 of the buffer queue is Enqueue.
using SLItf = const u64* const*;
constexpr int kSLBufferQueueEnqueue = 0;  // SLAndroidSimpleBufferQueueItf: Enqueue(itf, buffer, size)

// Aska::AskaOGG: the voice's Ogg Vorbis decoder over lib_vorbis, guest size 0x450 (SLVoice + 0x58 .. 0x4a8).
// Layout from its constructor (DecodeContext's: memset of 0x3ca and 0x6e bytes), DecodeInit (the 8 decode
// buffers from SoundMemory::ResourceAlloc, m_uiDecodePoolSize bytes rounded up to 0x200), DecodeHeader (the
// frame targets from the rate), DecodeBody / DecodePackets / Decode_Pcmout / Decode_LoopStart
// (port/decomp/audio/codec.c). The library's structs are embedded (lib_vorbis_layout.h; the host's live in
// place when lib_vorbis is native). Decode hands back each call's PCM in the next of the 8 buffers (round
// robin), so the voice can keep a few enqueued.
class AskaOGG {
public:
    static constexpr u32 kBuffers = 8;
    static constexpr s64 kErrStream = -0x3b8;   // a corrupt packet / stream (vorbis_synthesis_blockin / read failed)
    static constexpr s64 kErrNoMemory = -0x3bf; // a decode buffer couldn't grow

    s64 Decode(const s8* data, u32 size, s8** out, u32 maxFrames, u32 a, u32 b);  // _ZN4Aska7AskaOGG6DecodeEPKajPPajjj (guest)
    s64 DecodePackets(u32 offset, u32 maxFrames);   // _ZN4Aska7AskaOGG13DecodePacketsEjj
    s64 Decode_Pcmout(u32 offset);                  // _ZN4Aska7AskaOGG13Decode_PcmoutEj

    lib_vorbis::OggSyncState m_sync;        // 0x000
    lib_vorbis::OggStreamState m_stream;    // 0x020
    lib_vorbis::OggPage m_page;             // 0x1b8
    lib_vorbis::OggPacket m_packet;         // 0x1d8
    lib_vorbis::VorbisInfo m_info;          // 0x208: channels +0x20c
    lib_vorbis::VorbisComment m_comment;    // 0x240
    lib_vorbis::VorbisDspState m_dsp;       // 0x260
    lib_vorbis::VorbisBlock m_block;        // 0x2f0
    const s8* m_pendingData;   // 0x3b0: the source DecodeBody stopped in (m_hasPending)
    u32 m_pendingSize;         // 0x3b8
    u32 m_framesLong;          // 0x3bc: frames per decode (DecodeHeader: from the rate; 0 = no limit)
    u32 m_framesShort;         // 0x3c0: ... when the caller's budget is at most this many
    u32 m_consumed;            // 0x3c4: source bytes of m_pendingData already fed to the sync layer
    u8 m_hasPending;           // 0x3c8: a decode stopped at its frame target: packets are left (LockAndSubmitOGG submits m_pendingData first)
    u8 m_pageEos;              // 0x3c9: the current page's header flag 4 (end of stream)
    u8 unk_3ca[6];             // 0x3ca
    s8* m_buffers[kBuffers];   // 0x3d0: the PCM out buffers (SoundMemory::ResourceAlloc)
    u32 m_bufferSizes[kBuffers];  // 0x410
    u32 m_bufferIndex;         // 0x430: the one being filled
    u32 m_loopEnd;             // 0x434: DecodeBody's last argument, taken per page (nonzero: a loop jump after this page)
    u32 m_totalFrames;         // 0x438: DecodeInit's first argument
    u8 m_headerStage;          // 0x43c: Decode parses headers while < 3
    u8 m_loopState;            // 0x43d: Decode_LoopStart's state (0 none, 1-4)
    u8 unk_43e[2];             // 0x43e
    u32 m_loopPos;             // 0x440
    u32 m_loopBlock;           // 0x444
    u32 m_loopStart;           // 0x448: DecodeInit's second argument
    u8 unk_44c[4];             // 0x44c
};
static_assert(offsetof(AskaOGG, m_packet) == 0x1d8);
static_assert(offsetof(AskaOGG, m_info) == 0x208);
static_assert(offsetof(AskaOGG, m_dsp) == 0x260);
static_assert(offsetof(AskaOGG, m_block) == 0x2f0);
static_assert(offsetof(AskaOGG, m_pendingData) == 0x3b0);
static_assert(offsetof(AskaOGG, m_framesLong) == 0x3bc);
static_assert(offsetof(AskaOGG, m_consumed) == 0x3c4);
static_assert(offsetof(AskaOGG, m_hasPending) == 0x3c8);
static_assert(offsetof(AskaOGG, m_buffers) == 0x3d0);
static_assert(offsetof(AskaOGG, m_bufferSizes) == 0x410);
static_assert(offsetof(AskaOGG, m_bufferIndex) == 0x430);
static_assert(offsetof(AskaOGG, m_headerStage) == 0x43c);
static_assert(offsetof(AskaOGG, m_loopPos) == 0x440);
static_assert(offsetof(AskaOGG, m_loopStart) == 0x448);
static_assert(sizeof(AskaOGG) == 0x450);

// Aska::SLVoice: one OpenSL ES player, guest size 0x648 (layout from the constructor, CreateVoice and the
// submit path). The voice keeps m_queueDepth buffers enqueued: each OpenSL callback (ProcAudioBuffer, on
// the HLE's audio thread) unlocks the played one and, for PCM, locks and enqueues the next at once; for
// ADPCM / OGG it only counts it (m_pendingBuffers), and AudioSignal (from AudioSignalNotify::Handler)
// refills that many under the voice's lock: decode, enqueue, remember what each enqueued buffer holds
// (m_adpcmQueue / m_oggQueue, read back when it has played). A dummy (silent) buffer keeps the queue
// going while the stream has nothing. Results are Aska's (negative errors: -0x3c1 "stream ended",
// -0x3eb "nothing yet", -0x3bf "no decode buffer").
class SLVoice {
public:
    static constexpr u32 kCodecPCM = 0x0c, kCodecADPCM = 0x0d, kCodecOGG = 0x0e;
    static constexpr s64 kEnded = -0x3c1, kWouldBlock = -0x3eb, kNoBuffer = -0x3bf, kFailed = -1;
    static constexpr u32 kDecodeBuffers = 3, kDecodeBufferSize = 0x6000;
    static constexpr u32 kAdpcmQueue = 4, kOggQueue = 9;  // TQueue<.., 3> / <.., 8>: N + 1 slots

    void AudioSignal(u64 slot);              // vtable slot 10  _ZN4Aska7SLVoice11AudioSignalEm
    void ProcAudioBuffer();                  // _ZN4Aska7SLVoice15ProcAudioBufferEv (the OpenSL callback)
    s64 LockAndSubmitData();                 // _ZN4Aska7SLVoice17LockAndSubmitDataEv (result through x8)
    s64 LockAndSubmitADPCM();                // _ZN4Aska7SLVoice18LockAndSubmitADPCMEv (x8)
    s64 LockAndSubmitOGG();                  // _ZN4Aska7SLVoice16LockAndSubmitOGGEv (x8)
    s64 SubmitBufferDataPCM(const void* data, u32 size);  // _ZN4Aska7SLVoice19SubmitBufferDataPCMEPKvj (x8)
    s64 SubmitBufferDataADPCM(const void* data, u32 size, bool loopHead);  // _ZN4Aska7SLVoice21SubmitBufferDataADPCMEPKvjb
    s64 SubmitBufferDataOGG(const void* data, u32 size, u32 a, u32 b);     // _ZN4Aska7SLVoice19SubmitBufferDataOGGEPKvjjj
    s64 SubmitDummyDataAdpcm();              // _ZN4Aska7SLVoice20SubmitDummyDataAdpcmEv
    s64 SubmitDummyDataOgg();                // _ZN4Aska7SLVoice18SubmitDummyDataOggEv
    void SetDeleteCountdown();               // _ZN4Aska7SLVoice18SetDeleteCountdownEv
    void AudioKick();                        // vtable slot  _ZN4Aska7SLVoice9AudioKickEv

    const void* vtable;           // 0x000: _ZTVN4Aska7SLVoiceE + 0x10
    u32 m_state;                  // 0x008: 1 playing (Play), 3 stopped (Stop)
    u8 unk_00c[4];                // 0x00c
    const AaoWAVE* m_format;      // 0x010
    u8 unk_018[0x18];             // 0x018: volume, pitch, pan (floats), the created flag (+0x2a)
    WaveBuffer* m_buffer;         // 0x030
    AskaADPCM m_adpcm;            // 0x038
    u8 unk_054[4];                // 0x054
    AskaOGG m_ogg;                // 0x058
    const void* m_adpcmQueueVtable;  // 0x4a8: TQueue<AdpcmSubmitContext, 3>
    u32 m_adpcmWrite;             // 0x4b0 (1 at construction)
    u32 m_adpcmRead;              // 0x4b4
    u8 m_adpcmLocked[kAdpcmQueue];   // 0x4b8: the enqueued buffer came from a LockBuffer (else the dummy)
    const void* m_oggQueueVtable; // 0x4c0: TQueue<OggSubmitContext, 8>
    u32 m_oggWrite;               // 0x4c8 (1 at construction)
    u32 m_oggRead;                // 0x4cc
    u64 m_oggSubmits[kOggQueue];  // 0x4d0: the bytes enqueued | (locked from the stream) << 32
    s32 m_queuedBytes;            // 0x518: decoded bytes enqueued and not played (atomic)
    u8 unk_51c[4];                // 0x51c
    void* m_bus;                  // 0x520: CreateVoice's IBus
    SLItf m_playerObject;         // 0x528
    SLItf m_play;                 // 0x530
    SLItf m_bufferQueue;          // 0x538: Enqueue (slot 0)
    SLItf m_volume;               // 0x540
    s16 m_maxVolumeLevel;         // 0x548
    u8 unk_54a[6];                // 0x54a
    SLItf m_playbackRate;         // 0x550
    s16 m_minRate;                // 0x558
    s16 m_maxRate;                // 0x55a
    u8 unk_55c[4];                // 0x55c
    u8* m_decodeBuffers[kDecodeBuffers];    // 0x560: SoundServer's ADPCM decode buffers, taken on first use
    u64 m_decodeBufferSizes[kDecodeBuffers];  // 0x578
    u32 m_decodeIndex;            // 0x590
    u32 m_lockSize;               // 0x594: the bytes LockBuffer asks for
    u32 m_queueDepth;             // 0x598: the buffers kept enqueued
    u32 m_submitCount;            // 0x59c: mod m_queueDepth
    u32 m_kicks;                  // 0x5a0: AudioKick while playing (GetElapsedTime)
    u32 m_codec;                  // 0x5a4: kCodec*
    FastCriticalSection m_cs;     // 0x5a8: lock word +0x5e0, semaphore +0x620
    s32 m_pendingBuffers;         // 0x638: played buffers to refill (atomic; ProcAudioBuffer adds)
    s32 m_deleteCountdown;        // 0x63c: (atomic)
    u8 m_countdownArmed;          // 0x640
    u8 m_failed;                  // 0x641
    u8 unk_642[6];                // 0x642
};
static_assert(offsetof(SLVoice, m_buffer) == 0x30);
static_assert(offsetof(SLVoice, m_adpcm) == 0x38);
static_assert(offsetof(SLVoice, m_ogg) == 0x58);
static_assert(offsetof(SLVoice, m_adpcmWrite) == 0x4b0);
static_assert(offsetof(SLVoice, m_adpcmLocked) == 0x4b8);
static_assert(offsetof(SLVoice, m_oggWrite) == 0x4c8);
static_assert(offsetof(SLVoice, m_oggSubmits) == 0x4d0);
static_assert(offsetof(SLVoice, m_queuedBytes) == 0x518);
static_assert(offsetof(SLVoice, m_bufferQueue) == 0x538);
static_assert(offsetof(SLVoice, m_volume) == 0x540);
static_assert(offsetof(SLVoice, m_decodeBuffers) == 0x560);
static_assert(offsetof(SLVoice, m_decodeBufferSizes) == 0x578);
static_assert(offsetof(SLVoice, m_decodeIndex) == 0x590);
static_assert(offsetof(SLVoice, m_codec) == 0x5a4);
static_assert(offsetof(SLVoice, m_cs) == 0x5a8);
static_assert(offsetof(SLVoice, m_pendingBuffers) == 0x638);
static_assert(offsetof(SLVoice, m_deleteCountdown) == 0x63c);
static_assert(offsetof(SLVoice, m_failed) == 0x641);
static_assert(sizeof(SLVoice) == 0x648);

// Aska::SoundObject: one playing (or loading) sound, guest size 0x1f8 (SoundManager embeds one as its
// object list's sentinel at +0xc08, the next field at +0xe00). Only the fields the natives read so far.
class SoundObject {
public:
    static constexpr int kSlotDeleteThis = 7;   // vtable + 0x38: Aska::SoundObject::DeleteThis()
    static constexpr u32 kTypeSE = 1, kTypeBGM = 2;  // m_type bits (CElement::PostProgress: one of them, or "Illegal sound type")
    static constexpr u32 kTypeStreaming = 8;    // m_type bit 3: its deletion waits for the stream
    static constexpr u8 kFlagFinished = 0x01;   // m_flags1f2 bit 0: done; its CElement releases it

    bool RequestGet(SoundRequest* out);                 // _ZN4Aska11SoundObject10RequestGetEPNS0_16RequestContainerE
    bool RequestSet(u32 type, const void* data);        // _ZN4Aska11SoundObject10RequestSetEjPKv

    const void* vtable;        // 0x000: _ZTVN4Aska11SoundObjectE + 0x10
    SoundObject* m_prev;       // 0x008: (a TList<SoundObject> link)
    SoundObject* m_next;       // 0x010
    u8 unk_018[0x110];         // 0x018
    AudioPlayer* m_player;     // 0x128
    TSoundDynamicQueue<SoundRequest> m_requests;  // 0x130: RequestSet / RequestGet, guarded by m_requestCs
    FastCriticalSection m_requestCs;              // 0x150: lock word +0x188, semaphore +0x1c8
    u8 unk_1e0[8];             // 0x1e0: the sound status (UpdateSoundStatus)
    u32 m_type;                // 0x1e8: kTypeSE / kTypeBGM / kTypeStreaming bits
    u8 unk_1ec[6];             // 0x1ec
    u8 m_flags1f2;             // 0x1f2: kFlagFinished
    u8 unk_1f3[5];             // 0x1f3
};
static_assert(offsetof(SoundObject, m_player) == 0x128);
static_assert(offsetof(SoundObject, m_requests) == 0x130);
static_assert(offsetof(SoundObject, m_requestCs.m_lock) == 0x188);
static_assert(offsetof(SoundObject, m_type) == 0x1e8);
static_assert(offsetof(SoundObject, m_flags1f2) == 0x1f2);
static_assert(sizeof(SoundObject) == 0x1f8);

// Aska::SoundHandle: a SoundObject's entry in the manager's handle list, guest size 0x20 (the list's
// sentinel at SoundManager + 0x2d0, the count at +0x2f0).
class SoundHandle {
public:
    const void* vtable;      // 0x00: _ZTVN4Aska11SoundHandleE + 0x10
    SoundHandle* m_prev;     // 0x08
    SoundHandle* m_next;     // 0x10
    SoundObject* m_object;   // 0x18
};
static_assert(sizeof(SoundHandle) == 0x20);

// Aska::SoundCommand: a request for the sound thread (play, stop, pause, the BGM stack, effects), guest
// size 0xa8 (the list's sentinel at SoundManager + 0xa20, the count at +0xac8). ProcessCommand runs it
// (and may create a follow-up command to insert after it); ArrangeCommand drops one whose object is gone.
class SoundCommand {
public:
    const void* vtable;      // 0x00: _ZTVN4Aska12SoundCommandE + 0x10
    SoundCommand* m_prev;    // 0x08
    SoundCommand* m_next;    // 0x10
    u32 m_type;              // 0x18
    u8 unk_1c[4];            // 0x1c
    SoundObject* m_object;   // 0x20
    u8 unk_28[0x80];         // 0x28
};
static_assert(offsetof(SoundCommand, m_type) == 0x18);
static_assert(offsetof(SoundCommand, m_object) == 0x20);
static_assert(sizeof(SoundCommand) == 0xa8);

// Aska::SoundManager (Global::m_pSoundManager): the sound thread's manager. The fields the natives use;
// the rest is named padding (layout from the constructor, Initialize, SoundProcessSync, the list methods).
class SoundManager {
public:
    void StopSound(SoundObject* o, u32 fadeFrames);   // _ZN4Aska12SoundManager9StopSoundEPNS_11SoundObjectEj (guest)
    void ArrangeCommandList();                         // _ZN4Aska12SoundManager18ArrangeCommandListEv
    void ProcessCommandList();                         // _ZN4Aska12SoundManager18ProcessCommandListEv
    void AddSoundCommand(SoundCommand* c);             // _ZN4Aska12SoundManager15AddSoundCommandEPNS_12SoundCommandE
    void InsertSoundCommand(SoundCommand* after, SoundCommand* c);  // _ZN4Aska12SoundManager18InsertSoundCommandEPNS_12SoundCommandES2_
    void RemoveSoundCommand(SoundCommand* c);          // _ZN4Aska12SoundManager18RemoveSoundCommandEPNS_12SoundCommandE
    void UpdateAllSoundStatus();                       // _ZN4Aska12SoundManager20UpdateAllSoundStatusEv
    SoundHandle* QuerySoundHandle(SoundObject* o) const;  // _ZNK4Aska12SoundManager16QuerySoundHandleEPNS_11SoundObjectE
    void AddSoundHandle(SoundHandle* h);               // _ZN4Aska12SoundManager14AddSoundHandleEPNS_11SoundHandleE
    void RemoveSoundHandle(SoundHandle* h);            // _ZN4Aska12SoundManager17RemoveSoundHandleEPNS_11SoundHandleE
    void AddDeletingSoundObject(SoundObject* o);       // _ZN4Aska12SoundManager22AddDeletingSoundObjectEPNS_11SoundObjectE
    void FlushDeletingSoundObject();                   // _ZN4Aska12SoundManager24FlushDeletingSoundObjectEv
    static constexpr u8 kFlushReady = 0x06;            // m_flags1234: both bits before FlushDeletingSoundObject runs

    Task m_task;                 // 0x000: vtable _ZTVN4Aska12SoundManagerE + 0x10
    u8 unk_028[0x10];            // 0x028
    float m_signalTime;          // 0x038: SLVoice::SetDeleteCountdown's base countdown
    s32 m_signalExtra;           // 0x03c: nonzero adds a constant to it
    AudioSignal* m_audioSignal;  // 0x040
    u8 unk_048[0xa0];            // 0x048: the safety signal (+0x48) and its thread (+0x58), the manager thread (+0xe0)
    SoundServer* m_soundServer;  // 0x0e8: the pools (message notes, commands, handles, decode buffers)
    u8 unk_0f0[0x1d8];           // 0x0f0: the control-object lists (+0xf0, +0x118), the 8 auxiliary slots
    TList<SoundHandle> m_handles;     // 0x2c8: guarded by m_handleCs
    FastCriticalSection m_handleCs;   // 0x2f8
    u8 unk_388[0x18];            // 0x388: the 3D engine (+0x390: its vtable, then the listener)
    AudioListener m_listener;    // 0x3a0: Audio3DEngine's (SoundProcessSync computes it when it has a node)
    u8 unk_4c0[0x150];           // 0x4c0: the emitter list (+0x4c0), ...
    float m_volumeDb;            // 0x610: the 3D sounds' master volume (dB: 10^(dB / 20) * 1.4 above -96)
    u8 unk_614[4];               // 0x614
    float m_listenerRange;       // 0x618: the listener's curve's distance unit
    float m_speakerAngles[AudioEmitter::kSpeakers];  // 0x61c: each speaker's angle (radians around the up axis; index 3 unused)
    u8 unk_634[0xc];             // 0x634
    Vector m_speakers[AudioEmitter::kSpeakers];      // 0x640: each speaker's place (index 3 unused)
    float m_innerRadius;         // 0x6a0: closer than this: all "near"
    float m_outerRadius;         // 0x6a4: farther: all "far"
    float m_distanceUnit;        // 0x6a8
    u8 unk_6ac[4];               // 0x6ac
    void* m_listenerCurve;       // 0x6b0: the listener's attenuation curve (vtable slot 15)
    u8 unk_6b8[0x360];           // 0x6b8: the mixer (+0x6c8), the devices and effectors
    TList<SoundCommand> m_commands;   // 0xa18: guarded by m_commandCs
    u8 unk_ad0[0x130];           // 0xad0: TList<SoundPass>, TList<AudioInterface>
    TList<SoundObject> m_deleting;    // 0xc00: the objects waiting to go back to the pool; guarded by m_deletingCs
    FastCriticalSection m_commandCs;  // 0xe08
    u8 unk_e98[0x120];           // 0xe98: two more locks
    FastCriticalSection m_deletingCs; // 0xfb8
    u8 unk_1048[0x1e0];          // 0x1048: one more lock, the hash maps
    u8* m_dummyBuffer;           // 0x1228: the silent buffer SubmitDummyData* enqueue
    u32 m_dummyBufferSize;       // 0x1230: 0x4000
    u8 m_flags1234;              // 0x1234: kFlushReady
    u8 unk_1235[3];              // 0x1235
};
static_assert(offsetof(SoundManager, m_signalTime) == 0x38);
static_assert(offsetof(SoundManager, m_audioSignal) == 0x40);
static_assert(offsetof(SoundManager, m_soundServer) == 0xe8);
static_assert(offsetof(SoundManager, m_listener) == 0x3a0);
static_assert(offsetof(SoundManager, m_listener.m_position) == 0x4a0);
static_assert(offsetof(SoundManager, m_volumeDb) == 0x610);
static_assert(offsetof(SoundManager, m_speakerAngles) == 0x61c);
static_assert(offsetof(SoundManager, m_speakers) == 0x640);
static_assert(offsetof(SoundManager, m_innerRadius) == 0x6a0);
static_assert(offsetof(SoundManager, m_listenerCurve) == 0x6b0);
static_assert(offsetof(SoundManager, m_commands) == 0xa18);
static_assert(offsetof(SoundManager, m_handles) == 0x2c8);
static_assert(offsetof(SoundManager, m_handles.m_sentinel) == 0x2d0);
static_assert(offsetof(SoundManager, m_handles.m_count) == 0x2f0);
static_assert(offsetof(SoundManager, m_handleCs) == 0x2f8);
static_assert(offsetof(SoundManager, m_commands.m_sentinel) == 0xa20);
static_assert(offsetof(SoundManager, m_commands.m_count) == 0xac8);
static_assert(offsetof(SoundManager, m_deleting.m_sentinel) == 0xc08);
static_assert(offsetof(SoundManager, m_deleting.m_count) == 0xe00);
static_assert(offsetof(SoundManager, m_commandCs) == 0xe08);
static_assert(offsetof(SoundManager, m_deletingCs) == 0xfb8);
static_assert(offsetof(SoundManager, m_dummyBuffer) == 0x1228);
static_assert(offsetof(SoundManager, m_dummyBufferSize) == 0x1230);
static_assert(offsetof(SoundManager, m_flags1234) == 0x1234);

// ---- The sequencer (port/decomp/audio/sound_manager.c) -------------------------------------------------
//
// Aska::AudioPlayer: what a SoundObject plays through: its state (Sequencer2's AudioRun advances time in
// states 2 and 4, ArrangeMessageNote starts its state machine from it) and its message queue (SendMessage
// from the sequencer, GetMessage from its own AudioRun; the queue under m_messageCs).
class AudioPlayer {
public:
    bool SendMessage(u32 message, const void* a0, const void* a1);  // _ZN4Aska11AudioPlayer11SendMessageEjPvS1_
    bool GetMessage(AudioMessage* out);                             // _ZN4Aska11AudioPlayer10GetMessageEPNS_12AudioMessageE

    const void* vtable;  // 0x00
    u8 unk_08[0x10];     // 0x08
    u32 m_state;         // 0x18: 5 = done (SoundProcessSync deletes the object)
    u8 unk_1c[0x34];     // 0x1c
    TSoundDynamicQueue<AudioMessage> m_messages;  // 0x50
    FastCriticalSection m_messageCs;              // 0x70: lock word +0xa8, semaphore +0xe8
    u8 unk_100[0x18];    // 0x100
    WaveVoiceBase* m_voice;  // 0x118
};
static_assert(offsetof(AudioPlayer, m_state) == 0x18);
static_assert(offsetof(AudioPlayer, m_messages) == 0x50);
static_assert(offsetof(AudioPlayer, m_messageCs.m_lock) == 0xa8);
static_assert(offsetof(AudioPlayer, m_messageCs.m_sem) == 0xe8);
static_assert(offsetof(AudioPlayer, m_voice) == 0x118);

class AudioMessageNote;

// Aska::Sequencer2::WaitingNoteNotify: the sequencer's "a note of type 0 is pending" marker, guest size
// 0x18 (Sequencer2's constructor: vtable, m_note = 0, m_waiting = 0). Handler (slot 0) clears m_waiting.
class WaitingNoteNotify {
public:
    void Handler(u64 arg);  // _ZN4Aska10Sequencer217WaitingNoteNotify7HandlerEm

    const void* vtable;        // 0x00: _ZTVN4Aska10Sequencer217WaitingNoteNotifyE + 0x10
    AudioMessageNote* m_note;  // 0x08: the type-0 note it waits for
    u8 m_waiting;              // 0x10
    u8 unk_11[7];              // 0x11
};
static_assert(offsetof(WaitingNoteNotify, m_note) == 0x08);
static_assert(offsetof(WaitingNoteNotify, m_waiting) == 0x10);
static_assert(sizeof(WaitingNoteNotify) == 0x18);

// Aska::AudioMessageNote: a timed message for the AudioPlayer, guest size 0x40 (Sequencer2's list sentinel
// at +0x18, its count at +0x58; SoundServer's TPoolLegacy<AudioMessageNote>). Fields from AddMessageNote.
class AudioMessageNote {
public:
    const void* vtable;               // 0x00: _ZTVN4Aska16AudioMessageNoteE + 0x10
    AudioMessageNote* m_prev;         // 0x08
    AudioMessageNote* m_next;         // 0x10
    WaitingNoteNotify* m_waitNotify;  // 0x18: the sequencer's notify (type 0, and types 1-9 while it waits), else null
    u32 m_message;                    // 0x20: the message type (0-9 the sequencer knows)
    u8 unk_24[4];                     // 0x24
    const void* m_arg0;               // 0x28
    const void* m_arg1;               // 0x30
    float m_time;                     // 0x38: when (the sequencer's clock)
    u8 unk_3c[4];                     // 0x3c
};
static_assert(offsetof(AudioMessageNote, m_waitNotify) == 0x18);
static_assert(offsetof(AudioMessageNote, m_message) == 0x20);
static_assert(offsetof(AudioMessageNote, m_arg0) == 0x28);
static_assert(offsetof(AudioMessageNote, m_time) == 0x38);
static_assert(sizeof(AudioMessageNote) == 0x40);

// Aska::Sequencer2: a SoundObject's message sequencer, guest size 0x110 (layout from the constructor:
// the TList<AudioMessageNote> at +0x10 with its sentinel at +0x18 and count at +0x58, the
// FastCriticalSection at +0x60, the clock 0 and its step 1/60 s in ms (16.6667) at +0xf0 / +0xf4, the
// WaitingNoteNotify at +0xf8). Every method takes m_cs; ProcessMessageNote only to step the list.
class Sequencer2 {
public:
    bool AddMessageNote(u32 message, float time, const void* a0, const void* a1);  // _ZN4Aska10Sequencer214AddMessageNoteEjfPKvS2_
    void DeleteMessageNote(AudioMessageNote* note);  // _ZN4Aska10Sequencer217DeleteMessageNoteEPNS_16AudioMessageNoteE
    void DeleteAllMessageNote();                     // _ZN4Aska10Sequencer220DeleteAllMessageNoteEv
    void ArrangeMessageNote();                       // _ZN4Aska10Sequencer218ArrangeMessageNoteEv
    void ProcessMessageNote();                       // _ZN4Aska10Sequencer218ProcessMessageNoteEv
    void AudioRun();                                 // _ZN4Aska10Sequencer28AudioRunEv
    bool IsWaitingNote(const AudioMessageNote* note) const;  // _ZNK4Aska10Sequencer213IsWaitingNoteEPNS_16AudioMessageNoteE

    // helpers (not guest symbols)
    AudioMessageNote* sentinel() { return &m_sentinel; }
    void Unlink(AudioMessageNote* note);  // TList::Delete inlined: unlink, count down (not below 0), clear the links

    const void* vtable;           // 0x000: _ZTVN4Aska10Sequencer2E + 0x10
    AudioPlayer* m_player;        // 0x008
    const void* m_listVtable;     // 0x010: _ZTVN4Aska5TListINS_16AudioMessageNoteEEE + 0x10
    AudioMessageNote m_sentinel;  // 0x018: m_prev = the last note, m_next = the first
    s32 m_count;                  // 0x058
    u8 unk_05c[4];                // 0x05c
    FastCriticalSection m_cs;     // 0x060: lock word +0x98, semaphore +0xd8
    float m_time;                 // 0x0f0: the clock (ms)
    float m_step;                 // 0x0f4: per AudioRun while playing (16.6667)
    WaitingNoteNotify m_notify;   // 0x0f8
};
static_assert(offsetof(Sequencer2, m_player) == 0x08);
static_assert(offsetof(Sequencer2, m_sentinel) == 0x18);
static_assert(offsetof(Sequencer2, m_count) == 0x58);
static_assert(offsetof(Sequencer2, m_cs) == 0x60);
static_assert(offsetof(Sequencer2, m_time) == 0xf0);
static_assert(offsetof(Sequencer2, m_step) == 0xf4);
static_assert(offsetof(Sequencer2, m_notify) == 0xf8);
static_assert(sizeof(Sequencer2) == 0x110);

// ---- The Framework's sound layer (port/decomp/audio/framework.c) ----------------------------------------
//
// Framework::CSound::CElement: one slot of Framework::CSoundManager's element array, guest size 0x70
// (TObjectContainer<CElement>::Initialize: new[](n * 0x70 + 8); the destructor's stride). Layout from the
// constructor, Initialize, Activate, PostProgress, Watchdog / IsKeepPlayByWatchdog.
class CElement {
public:
    static constexpr int kSlotRelease = 7;  // (the hierarchical object's slot 7 in the destructor)

    void PreProgress(float dt);    // _ZN9Framework6CSound8CElement11PreProgressEf (inlined in CSoundManager::PreProgress)
    void PostProgress(float dt);   // _ZN9Framework6CSound8CElement12PostProgressEf
    bool IsActive() const;         // m_handle != CSound::iInvalidHandle

    const void* vtable;            // 0x00: _ZTVN9Framework6CSound8CElementE + 0x10
    u64 m_handle;                  // 0x08: CSound::iInvalidHandle when free
    SoundObject* m_pAskaSoundObject;  // 0x10: set by Activate
    u8 m_keepPlayByWatchdog;       // 0x18: Activate (tArguments + 0x38); PostProgress stops the sound when no Watchdog() came
    u8 m_watched;                  // 0x19: Watchdog() sets it, PreProgress clears it
    u8 unk_1a[6];                  // 0x1a
    void* m_pHierarchicalObject;   // 0x20: the 3D position's node (Initialize: a 0x1a0-byte HierarchicalObject)
    u8 m_is3D;                     // 0x28: Activate (tArguments + 0x40)
    u8 unk_29[0x47];               // 0x29
};
static_assert(offsetof(CElement, m_handle) == 0x08);
static_assert(offsetof(CElement, m_pAskaSoundObject) == 0x10);
static_assert(offsetof(CElement, m_keepPlayByWatchdog) == 0x18);
static_assert(offsetof(CElement, m_watched) == 0x19);
static_assert(offsetof(CElement, m_pHierarchicalObject) == 0x20);
static_assert(offsetof(CElement, m_is3D) == 0x28);
static_assert(sizeof(CElement) == 0x70);

using CElementContainer = memory::TObjectContainer<CElement>;  // vtable _ZTVN9Framework16TObjectContainerINS_6CSound8CElementEEE

// Framework::CSoundManager: the game thread's sound layer over Aska's (a CTimeElement; its PreProgress /
// PostProgress run each frame on two CManageFiber fibers). Layout from the constructor, Initialize,
// Pre/PostProgress, NumPlaying, NewHandle, EnableIgnorePlayRequest, FunctorAllPlayingElements.
class CSoundManager {
public:
    static constexpr int kSlotNumElements = 4, kSlotElement = 5;  // m_pElements' vtable (+0x20 / +0x28)

    void PreProgress();    // _ZN9Framework13CSoundManager11PreProgressEv
    void PostProgress();   // _ZN9Framework13CSoundManager12PostProgressEv

    CTimeElement base;          // 0x00: vtable _ZTVN9Framework13CSoundManagerE + 0x10; m_parent (+0x08) picks DT()'s source
    u32 m_uniqueNumber;         // 0x48: gInstanceUniqueNumber at construction
    u8 unk_4c[4];               // 0x4c
    void* m_pFiberPreProgress;  // 0x50: CManageFiber (kind 0)
    void* m_pFiberPostProgress; // 0x58: CManageFiber (kind 1)
    CElementContainer* m_pElements;  // 0x60
    CMutex* m_pMutex;           // 0x68
    u32 m_numPlaying;           // 0x70: PostProgress counts the active elements
    u8 m_ignorePlayRequest;     // 0x74: EnableIgnorePlayRequest
    u8 unk_75[3];               // 0x75
    u32 m_nextHandle;           // 0x78: NewHandle
    u8 m_callPlayingElements;   // 0x7c: PostProgress then runs FunctorAllPlayingElements
    u8 unk_7d[3];               // 0x7d
    u32 unk_80;                 // 0x80: 0 after Initialize
};
static_assert(offsetof(CSoundManager, m_uniqueNumber) == 0x48);
static_assert(offsetof(CSoundManager, m_pElements) == 0x60);
static_assert(offsetof(CSoundManager, m_pMutex) == 0x68);
static_assert(offsetof(CSoundManager, m_numPlaying) == 0x70);
static_assert(offsetof(CSoundManager, m_nextHandle) == 0x78);
static_assert(offsetof(CSoundManager, m_callPlayingElements) == 0x7c);
static_assert(offsetof(CSoundManager, unk_80) == 0x80);

}  // namespace soa::native::audio

#endif  // SOA_NATIVE_AUDIO_LAYOUT_H
