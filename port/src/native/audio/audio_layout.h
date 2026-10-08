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

// The locks and the task base are the lower subsystems' classes: sync's FastCriticalSection (0x90,
// lock word +0x38, waiter count +0x3c, Semaphore +0x78) and kernel's Task (0x28).
using FastCriticalSection = sync::FastCriticalSection;
using Task = kernel::Task;
using CTimeElement = kernel::CTimeElement;
using CMutex = sync::CMutex;

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

// ---- The sound objects (port/decomp/audio/sound_manager.c) -------------------------------------------
//
// Aska::SoundObject: one playing (or loading) sound, guest size 0x1f8 (SoundManager embeds one as its
// object list's sentinel at +0xc08, the next field at +0xe00). Only the fields the natives read so far.
class SoundObject {
public:
    static constexpr int kSlotDeleteThis = 7;   // vtable + 0x38: Aska::SoundObject::DeleteThis()
    static constexpr u32 kTypeSE = 1, kTypeBGM = 2;  // m_type bits (CElement::PostProgress: one of them, or "Illegal sound type")
    static constexpr u8 kFlagFinished = 0x01;   // m_flags1f2 bit 0: done; its CElement releases it

    const void* vtable;        // 0x000: _ZTVN4Aska11SoundObjectE + 0x10 (a TList link: m_prev 0x08, m_next 0x10)
    u8 unk_008[0x1e0];         // 0x008
    u32 m_type;                // 0x1e8: kTypeSE / kTypeBGM bits (bit 3: FlushDeletingSoundObject's "wait for the stream")
    u8 unk_1ec[6];             // 0x1ec
    u8 m_flags1f2;             // 0x1f2: kFlagFinished
    u8 unk_1f3[5];             // 0x1f3
};
static_assert(offsetof(SoundObject, m_type) == 0x1e8);
static_assert(offsetof(SoundObject, m_flags1f2) == 0x1f2);
static_assert(sizeof(SoundObject) == 0x1f8);

// Aska::SoundManager (Global::m_pSoundManager): the sound thread's manager. Only the fields the natives
// use so far; the rest is named padding (layout from the constructor, Initialize, SoundProcessSync).
class SoundManager {
public:
    void StopSound(SoundObject* o, u32 fadeFrames);  // _ZN4Aska12SoundManager9StopSoundEPNS_11SoundObjectEj (guest)

    Task m_task;                 // 0x000: vtable _ZTVN4Aska12SoundManagerE + 0x10
    u8 unk_028[0x10];            // 0x028
    float m_signalTime;          // 0x038: SLVoice::SetDeleteCountdown's base countdown
    s32 m_signalExtra;           // 0x03c: nonzero adds a constant to it
    AudioSignal* m_audioSignal;  // 0x040
    u8 unk_048[0x11e0];          // 0x048: the safety signal, the threads, the lists and their locks, the effectors
    u8* m_dummyBuffer;           // 0x1228: the silent buffer SubmitDummyData* enqueue
    u32 m_dummyBufferSize;       // 0x1230: 0x4000
    u8 m_flags1234;              // 0x1234
    u8 unk_1235[3];              // 0x1235
};
static_assert(offsetof(SoundManager, m_signalTime) == 0x38);
static_assert(offsetof(SoundManager, m_audioSignal) == 0x40);
static_assert(offsetof(SoundManager, m_dummyBuffer) == 0x1228);
static_assert(offsetof(SoundManager, m_dummyBufferSize) == 0x1230);
static_assert(offsetof(SoundManager, m_flags1234) == 0x1234);

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
