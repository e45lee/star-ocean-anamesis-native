# `audio`: sound and voice: the game's sound engine (Aska::Sound*, Audio*, SLVoice, AskaOGG / AskaADPCM, Sequencer2; Framework::CSound*; CSoundManager, the voice managers)

A subsystem of the native rebuild (port/PLAN.md task 6). The workflow (decompile, types, natives,
tests, Ghidra types): port/src/native/README.md "Per-subsystem workflow".

- Scope: the demangled-name patterns in [`port/decomp/audio/scope.txt`](../../../decomp/audio/scope.txt).
- Decompiles and the function list: [`port/decomp/audio/`](../../../decomp/audio/) (`symbols.tsv`; `tools/decomp.sh --into audio/<topic>`).
- Types: [`audio_layout.h`](audio_layout.h); for Ghidra, `tools/subsystem.py export-types audio` -> `port/decomp/audio/types.json`.
- Build settings of its own (a host library, a definition): none; a `subsystem.cmake` here would hold them (port/CMakeLists.txt includes it).

## Types (classes with their methods attached)

| Class (guest) | Guest size | Found from (ctor, decompile) | Status |
|---|---|---|---|
| `AudioSignalNotify` (Aska) | 0x138 | the construction SoundManager::Initialize inlines (vtable, FastCriticalSection at +0xa8, memset of the 20 slots); Handler / Add / Delete / GetSignalCount | proven by `audio/signal-notify*` (the guest's methods on private notifies) |
| `AudioSignal` (Aska) | 0x2a0 | SoundManager::Initialize (SoundMemory::Malloc(0x2a0), Task inlined, both notifies, +0x298 = 0); Run; AudioSafetySignalNotify::Handler | typed |
| `AskaADPCM` (Aska) | 0x1c | Init, Encode_* (the encoder state), Decode_* | proven by `audio/adpcm-*` |

Other subsystems' classes: sync's `FastCriticalSection` (embedded; its Enter / Leave are the guest's inlined
lock code), kernel's `Task` (AudioSignal's base).

## Natives

11 bound (`soa --list-native`: the four `audio:` ones and the seven `Aska::AskaADPCM::*`). Live checks:
`soa --live-check audio[:every=N][:out=FILE]` (shadow checks; default every=16) and
`--live-check audio_leaf[:every=N][:out=FILE]` (record / replay; `audio_check.h`).
Result (2026-10-08, `port/scripts/restore_session.sh`, the battle-gacha flow, audio every=2, audio_leaf every=1): PASS;
audio 20,128 checks, 0 mismatches, 0 races (Handler 6,561, AddSignalVoiceList 196, DeleteSignalVoiceList 298,
GetSignalCount 13,073); audio_leaf 943 checks, 0 mismatches (Decode 567, Init 376).

| Class::Method (guest symbol) | File | Differential tests | Live check |
|---|---|---|---|
| `Aska::AudioSignalNotify::Handler` (slot 0: every voice's `AudioSignal(slot)`, vtable slot 10, under the lock) | `audio_signal.cpp` | `audio/signal-notify`, `audio/signal-notify-full` (fake voices: a fake slot 10 logged by a stub session) | the guest on a shadow notify with the slots the native saw, `SLVoice::AudioSignal` answered by the check's stub: the calls compared |
| `AudioSignalNotify::AddSignalVoiceList` / `DeleteSignalVoiceList` | `audio_signal.cpp` | same | the guest on a shadow notify built from the slots the native saw under the lock: result and slots compared |
| `AudioSignalNotify::GetSignalCount` | `audio_signal.cpp` | same | getter |
| `Aska::AskaADPCM::Decode`, `Decode_M08` / `M16` / `S08` / `S16`, `Init`, `GetSamplesPerBlock` | `audio_adpcm.cpp` | `audio/adpcm-decode` (random streams, all block sizes incl. degenerate ones, cut streams), `audio/adpcm-init` | record / replay (the object, the input, the output); the Decode_* only through Decode (their only caller) |

## Dependencies

Subsystems whose types or functions this one uses (port/REBUILD-QUEUE.md has the measured call edges):
- `sync`: FastCriticalSection (AudioSignalNotify +0xa8, SLVoice +0x5a8, SoundManager +0xe08; the guest
  inlines its enter / leave everywhere in this subsystem), Semaphore, Thread::Sleep.
- `kernel`: Task (AudioSignal's base), INotify (AudioSignalNotify is one; the dispatcher's messages 0x467 /
  0x468), SimpleMessageDispatcher::PostMessage (AudioSignal::Run).
- `lib_vorbis` (AskaOGG), `resource` (MultiMediaStream / VBRBuffer behind the voices), `memory`
  (SoundMemory), `libcxx`, `params`.
- Upwards: `ui` (CUIVoiceManager / CMenuVoiceManager are called from the screens); `anim` and `master`
  co-developed (no shared type yet).

## RE notes

- **The signal path.** SoundManager::Initialize makes the AudioSignal task (SoundManager + 0x40) with two
  AudioSignalNotify lists of 20 voices each, the AudioSafetySignalThread (+0x58) and its notify (+0x48). A
  streaming SLVoice (OGG / ADPCM) is added to the emptier list on CreateVoice and removed on DeleteVoice.
  AudioSignal::Run (each frame on the system task manager) posts each non-empty notify to the dispatcher
  (messages 0x467 / 0x468); the worker's Handler calls `SLVoice::AudioSignal(slot)` for every voice, which
  refills the OpenSL buffer queue (LockAndSubmitOGG / ADPCM). The safety thread runs both Handlers itself
  when Run hasn't happened for more than 0x42 ms (AudioSafetySignalNotify::Handler vs m_lastRunTime).
- **ADPCM.** 4-bit, Yamaha-style steps (57 / 77 / 102 / 128 / 153 over 64, clamped to [0x7f, 0x6000]);
  blocks of 32 / 64 / 128 / 256 bytes, a header per channel (s16 predictor, s16 step). The predictor is
  never clamped (the sample is its low 16 bits): a game quirk reproduced. SLVoice decodes into
  SoundServer's 0x6000-byte buffers (AcquireAskaAdpcmDecodeBuffer).
- **The SoundManager's command list** (ProcessCommandList / ArrangeCommandList, the hottest functions of
  the subsystem): a TList<SoundCommand> at +0xa18 (sentinel +0xa20) under the FastCriticalSection at +0xe08;
  the lock is taken only to read a node's next pointer, the commands themselves run unlocked.
- **Not audio's:** Aska::WaveModifier / WaveModifierCPUGL / WaveDistortionFilter are the GL screen
  distortion (render's), whatever their name.
