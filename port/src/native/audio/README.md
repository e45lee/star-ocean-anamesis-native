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
| `SoundObject` (Aska) | 0x1f8 | SoundManager's object-list sentinel (+0xc08, next field +0xe00); CElement::PostProgress, Add/FlushDeletingSoundObject | partial: links, m_player (+0x128), m_type (+0x1e8), m_flags1f2 |
| `SoundManager` (Aska) | >= 0x1238 | the constructor, Initialize, SoundProcessSync, the list methods, the SLVoice functions | partial: m_audioSignal (+0x40), m_soundServer (+0xe8), the handle / command / deleting lists and their locks (+0x2c8 / +0x2f8, +0xa18 / +0xe08, +0xc00 / +0xfb8), the dummy buffer (+0x1228), m_flags1234; proven by `audio/sound-manager-lists` |
| `TList<T>` (Aska) | 0x10 + sizeof(T) | the SoundManager / Sequencer2 constructors (a T as the sentinel, then the count), the inlined Add / Delete | proven by the list tests |
| `SoundHandle`, `SoundCommand` (Aska) | 0x20, 0xa8 | the list sentinels' extents; AddSoundHandle / QuerySoundHandle; ProcessCommandList, ArrangeCommand | partial (links, the object; the command's type) |
| `AudioPlayer`, `WaveVoiceBase`, `WaveBuffer`, `WaveStreamView` | - | the chain FlushDeletingSoundObject reads (player +0x118 -> voice +0x30 -> buffer +8 -> stream +0x3fc / +0x728); AudioPlayer::m_state (+0x18) | partial views (the stream is resource's MultiMediaStream family) |
| `Sequencer2`, `AudioMessageNote`, `WaitingNoteNotify` (Aska) | 0x110, 0x40, 0x18 | the Sequencer2 constructor, AddMessageNote, Arrange / ProcessMessageNote | proven by `audio/sequencer` |
| `Audio3DObject`, `AudioListener` (Aska) | 0xf0, 0x120 | the AudioListener / AudioEmitter constructors, UpdateMatrix, Compute, Audio3DEngine's members | proven by `audio/3d-listener` |
| `CElement` (Framework::CSound) | 0x70 | the constructor, Initialize, Activate, PostProgress, TObjectContainer<CElement>'s 0x70 stride | proven by `audio/framework-progress`, `audio/element-post-progress` |
| `CSoundManager` (Framework) | >= 0x84 | the constructor, Initialize, Pre/PostProgress, the accessors | proven by `audio/framework-progress` |

Other subsystems' classes: sync's `FastCriticalSection` (embedded; its Enter / Leave are the guest's inlined
lock code) and `CMutex` (CSoundManager's, through a pointer), kernel's `Task` (AudioSignal's base) and
`CTimeElement` (CSoundManager's base), memory's `TObjectContainer<T>` (the element array).

## Natives

35 bound (`soa --list-native`: the 28 `audio:` ones and the seven `Aska::AskaADPCM::*`). Live checks:
`soa --live-check audio[:every=N][:out=FILE]` (shadow checks; default every=16) and
`--live-check audio_leaf[:every=N][:out=FILE]` (record / replay; `audio_check.h`).
Result (2026-10-08, `port/scripts/restore_session.sh`, the battle-gacha flow, audio every=2, audio_leaf every=1): PASS;
audio 20,128 checks, 0 mismatches, 0 races (Handler 6,561, AddSignalVoiceList 196, DeleteSignalVoiceList 298,
GetSignalCount 13,073); audio_leaf 943 checks, 0 mismatches (Decode 567, Init 376). With the Framework's
Pre/PostProgress (same flow, after merging main): audio 46,001 checks, 0 mismatches, 0 races (PreProgress
12,803, PostProgress 12,798, the notify's 20,400); audio_leaf 886, 0 mismatches. With the sequencer, the 3D
objects and the SoundManager lists (battle-gacha, every=2): audio 117,000 checks, 0 mismatches, 0 skipped,
0 races (UpdateMatrix 10,591, AudioListener::Compute 2,368, Pre/PostProgress 25,809, Sequencer2 29,796,
the notify 20,584, ArrangeCommandList / ProcessCommandList 7,207 each, AddSoundCommand 192,
UpdateAllSoundStatus 6,456, QuerySoundHandle 20, AddSoundHandle 157, AddDeletingSoundObject 157,
FlushDeletingSoundObject 6,456); audio_leaf 798, 0 mismatches.

| Class::Method (guest symbol) | File | Differential tests | Live check |
|---|---|---|---|
| `Aska::AudioSignalNotify::Handler` (slot 0: every voice's `AudioSignal(slot)`, vtable slot 10, under the lock) | `audio_signal.cpp` | `audio/signal-notify`, `audio/signal-notify-full` (fake voices: a fake slot 10 logged by a stub session) | the guest on a shadow notify with the slots the native saw, `SLVoice::AudioSignal` answered by the check's stub: the calls compared |
| `AudioSignalNotify::AddSignalVoiceList` / `DeleteSignalVoiceList` | `audio_signal.cpp` | same | the guest on a shadow notify built from the slots the native saw under the lock: result and slots compared |
| `AudioSignalNotify::GetSignalCount` | `audio_signal.cpp` | same | getter |
| `Framework::CSoundManager::PreProgress` / `PostProgress` (the element array read directly when it is the Framework's TObjectContainer<CElement>, else through its vtable) | `audio_framework.cpp` | `audio/framework-progress` (random element / sound-object states, with and without the mutex; StopSound, DeleteThis, FunctorAllPlayingElements stubbed and logged) | the guest on a shadow manager (no mutex), a shadow element array and shadow copies of the sound objects; the three callees stubbed; calls, elements and m_numPlaying compared; a sound object the sound thread changed meanwhile = a race |
| `Framework::CSound::CElement::PostProgress` (the watchdog stop, the release of a finished sound object) | `audio_framework.cpp` | `audio/element-post-progress` | inside PostProgress's check (its only caller) |
| `Aska::Sequencer2::AddMessageNote` / `DeleteMessageNote` / `DeleteAllMessageNote` / `ArrangeMessageNote` / `ProcessMessageNote` / `AudioRun` / `IsWaitingNote`, `Sequencer2::WaitingNoteNotify::Handler` | `audio_sequencer.cpp` | `audio/sequencer` (random notes of every type incl. NaN times, the player's states, the pool and SendMessage stubbed) | the guest on a shadow sequencer (its notes copied, the notify moved to the shadow's), Acquire / ReleaseMessageNote and SendMessage stubbed; calls, list, notes, count, clock, notify compared; AudioRun's two passes are checked as Arrange / Process |
| `Aska::Audio3DObject::UpdateMatrix`, `Aska::AudioListener::Compute` | `audio_3d.cpp` | `audio/3d-listener` (a fake node's random world matrix, or none) | the guest and the native again on two shadows of the object: equal bytes |
| `Aska::SoundManager::ArrangeCommandList` / `ProcessCommandList` / `AddSoundCommand` / `InsertSoundCommand` / `RemoveSoundCommand` / `UpdateAllSoundStatus` / `QuerySoundHandle` / `AddSoundHandle` / `RemoveSoundHandle` / `AddDeletingSoundObject` / `FlushDeletingSoundObject` | `audio_sound_manager.cpp` | `audio/sound-manager-lists` (private pools of commands, handles, objects; ArrangeCommand / ProcessCommand stubbed with per-command results and follow-up commands; the releases and UpdateSoundStatus logged) | the guest on a shadow manager whose lists are copies taken before the native ran, the guest callees answered with the native run's results; calls, lists and counts compared; a node from another thread = a race; QuerySoundHandle a getter |
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
- **The SoundManager's lists.** The command list (TList<SoundCommand> at +0xa18 under the FastCriticalSection
  at +0xe08), the handle list (+0x2c8 under +0x2f8) and the deleting list (TList<SoundObject> at +0xc00 under
  +0xfb8). The walkers take the lock only to read a node's next pointer; the commands run unlocked, and a
  command ProcessCommand hands back is inserted after it and runs next. ProcessCommandList ends each step
  with an empty lock / unlock pair (kept). FlushDeletingSoundObject runs only when m_flags1234 has both bits
  0x06; a streaming object (m_type bit 3) waits while its stream has a read in flight (+0x3fc), and an
  object without a handle leaves the list without being released (the guest's order).
- **The sequencer.** Each SoundObject's Sequencer2 holds timed messages for its AudioPlayer. ArrangeMessageNote
  (under the lock throughout): of the type-1 and type-4 notes only the earliest of each type stays; of the due
  notes only the latest of each type; then the due notes run through the player's state machine as they would
  change it (0 play from state 1; 1 stop from 2-4; 2 pause from 2 / 4; 3 resume from 3; 4 from 2 / 3; 5-9 from
  2 / 3) and the ones that make no sense are dropped. A type-3 note in another state is dropped and still moves
  the local state to 2 (a game quirk, kept; the state is a local, nothing is written back). ProcessMessageNote
  sends the due notes that aren't waiting (a type-0 note's WaitingNoteNotify holds the notes 1-9 added
  after it until it is sent). Times compare as the guest's fcmp + b.lt: a NaN time is never due.
- **The Framework layer.** Framework::CSoundManager's PreProgress / PostProgress run on two CManageFiber
  fibers each frame (game thread): PreProgress clears every active element's `m_watched` (CElement::
  PreProgress, inlined), PostProgress counts the active elements into m_numPlaying and runs CElement::
  PostProgress: an element whose owner asked for the watchdog (`m_keepPlayByWatchdog`, from tArguments) and
  didn't call Watchdog() this frame has its sound stopped (Aska::SoundManager::StopSound(o, 10)), and a
  finished sound object (+0x1f2 bit 0) is returned (its DeleteThis, slot 7) and the element freed. An
  element whose sound object is neither SE nor BGM asserts "Illegal sound type" and isn't stopped (the
  shipped gDoAssert returns; a branch after it skips StopSound, which Ghidra's decompile shows as else).
  The guest calls NumElements / rElement through the vtable twice per element; the dt (the manager's
  CTimeElement, or the Framework's when it has no parent) is computed and unused.
- **Not audio's:** Aska::WaveModifier / WaveModifierCPUGL / WaveDistortionFilter are the GL screen
  distortion (render's), whatever their name.
