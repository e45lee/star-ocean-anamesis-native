# `scene`: the object manager, AOF models, skinning, the framework's models

A subsystem of the native rebuild (port/PLAN.md task 6). The workflow (decompile, types, natives,
tests, Ghidra types): port/src/native/README.md "Per-subsystem workflow".

- Scope: the demangled-name patterns in [`port/decomp/scene/scope.txt`](../../../decomp/scene/scope.txt).
- Decompiles and the function list: [`port/decomp/scene/`](../../../decomp/scene/) (`symbols.tsv`; `tools/decomp.sh --into scene/<topic>`).
- Types: [`scene_layout.h`](scene_layout.h); for Ghidra, `tools/subsystem.py export-types scene` -> `port/decomp/scene/types.json`.
- Build settings of its own (a host library, a definition): [`subsystem.cmake`](subsystem.cmake).

## Types (classes with their methods attached)

Type recovery a wave ahead of the code (port/REBUILD-QUEUE.md: scene is wave 6, the hottest subsystem).
Every class is in [`scene_layout.h`](scene_layout.h) (namespace `soa::native::scene`; the hierarchy's bases
come from render_layout.h). Layouts are proven by the `scene/layout-*` selftests in
[`scene_layout_test.cpp`](scene_layout_test.cpp), all on the running game's objects at a frame boundary
(`render::testutil::on_frame`: the body runs on the game thread inside `ObjectManager::OnPrePaint`,
before the frame's jobs are dispatched), compared with the guest's own getters and the decompiles'
invariants. `soa --selftest scene/` runs them at the title (5/5: 9 painting candidates, 6 AofObjects,
the Cocos UI's 5 primitive and 1 text renderers; no bones); `port/scripts/selftest_live.sh SOA OUT TMP
scene/ --at home` on the home screen (5/5: 27 candidates, 23
AofObjects, 30 render states, 19 skinned AofObjects, 157 bones of which 93 JointObjects).

| Class (guest) | Guest size | Found from | Proven by (scene/layout-...) | Status |
|---|---|---|---|---|
| `TaskManagerBase` (= kernel::TaskManager, aliased) | 0xff0 data | TaskManager::TaskManager, Add | `-object-manager` (the Task base's vptr at 0x28) | parked here, opaque-ish (32 Events, CriticalSection, FastCriticalSection by extent) |
| `ObjectManagerWorkerThread` (Aska) | 0x210 (the dispatcher's new[]) | ctor, Handler, Handler_*, ChangeMode, the dispatcher's Dispatch_* / Set*Parameter | `-job-dispatcher` (vtable, back pointers, mode / job / lock word, result bits, batch pointers into m_candidates) | typed; 0x120, 0x1d4..0x1ff (RenderingDecided's) partly |
| `ObjectManagerJobDispatcher` (Aska) | 0xc8 (Global::Instantiate...: new(200)) | ctor, dtors, WaitIdle, ChangeMode, Dispatch_*, Sleep | `-job-dispatcher` (1 worker, new[] count, except index) | typed |
| `ObjectManager` (Aska) | 0x10700 (Global::InstantiateObjectManager) | ctor, OnPrePaint, TraversePaintingList, MakePaintingList, GetSceneEV, GetNoTexture | `-object-manager` (11 owned objects by vtable, the system objects, GetSceneEV(0..) through the combiners, GetNoTexture through m_renderThread, every candidate IsThisIt RenderableObject) | typed where the hot paths read; large fixed arrays partly padding (0x10a0, 0x1e88..0x3ef0, 0x69f0..0xb418, 0xb428..0x104f0) |
| `PaintingPassList`, `MultipassEnvironment` | 0x10, 0x48 | MakePaintingList, OnPrePaint, GetSceneEV | `-object-manager` (the env's combiner) | typed partly |
| `AofObject` (Aska) | 0x6b0 (CreateClone) | ctor, PrepareForRendering, GetObjectRenderState, the color / variation / light getters, SetAofHandler | `-aof-object` (4 color vectors, HasBoundingBox, QueryPrebuiltVariation, GetActualLightConfiguration, the render-state array through GetObjectRenderState) | typed; ~40% named |
| `AofObjectRenderState` (Aska) | 0x20 | GetObjectRenderState, PrepareForRendering | `-aof-object` | typed: 0x00..0x17 unknown |
| `AofHandler` (Aska) | 0x330 (AofObject::Clone) | ctor, SetShaderContextFlag, SkinMatricesBase::Init | `-aof-object` (the 3 vptrs, IsDirectAof), `-skinning` (m_bindPose) | typed; MaterialList opaque (render's) |
| `SkinMatricesBase` / `SkinMatrices` / `SkinMatricesSimple` (Aska) | 0x78 / 0x98 (CreateSkinMatrices) / 0x90 | ctors, Init, GetBoneObject, MakeSkinMatrices | `-skinning` (m_object, initialized flag, bind pose, GetBoneObject(i) = m_bones[i] for every bone) | typed; Simple's fields unnamed |
| `JointObject` (Aska) | 0x1a0 (data 0x199; no allocation found) | MakeMatrix, Get / Set | `-skinning` (Get(15) = the joint orientation at m_hoc 0x90) | typed |
| `DirectAofHandler` (Aska) | 0x380 (CCocosScene::AddSceneRenderer) | ctor, Create | `-direct-aof` (IsDirectAof only: the handlers seen were subclasses) | typed partly |
| `CDirectAofPrimitiveRenderer` (Framework) | 0x7b0 | ctor, Reset, Reserve, PutCounter, Type, IsInitialized | `-direct-aof` (IsInitialized, PutCounter, Type) | typed partly |
| `CDirectAofTextRenderer` + `DirectAofTextPutPool` (Framework) | 0x830, 0x20 | ctor, Reset, PutCounter | `-direct-aof` (PutCounter over the double-buffered pools, the compositor's vtable) | typed partly |

Not recovered (smaller, later): `Aska::ModifierManager` (347 self samples), `Aska::AsfHandler` (232; its
CreateTree is a load path), `Aska::DPGHandler`, `Aska::HeightObject*`, `Framework::CCharacterModel` /
`CEffectModel` / `CEffectManager`, `CAnimationModelObject`, `CHomeModelViewManager`, `CArenaEffectModel`
(each under 0.05%); `DirectAofPrimitive` / `DirectAofPrimitiveBase`.

## Natives

16 bound (`soa --list-native | grep scene:`). Live check: `soa --live-check scene[:every=N][:out=FILE]`
(default every=16; [`scene_check.h`](scene_check.h)).

| Class::Method (guest symbol) | File | Differential tests | Live check |
|---|---|---|---|
| `ObjectManagerJobDispatcher::Dispatch_MakePaintingList` / `_PreliminarilyPrepare` / `_PrepareForRendering` / `_ViewFrustumCulling` / `_DetectLIBL` / `_ResetSystemFlags` (the job inline: `ObjectManagerWorkerThread::Run*`) | [`scene_dispatch.cpp`](scene_dispatch.cpp) | `scene/dispatch-make-painting-list`, `-preliminarily-prepare`, `-prepare-for-rendering`, `-view-frustum-culling`, `-detect-libl`, `-reset-system-flags` | shadow replay: the guest's Dispatch_X + the worker's Handler_X on a shadow worker, the job's callees replayed from the native's record |
| `ObjectManagerJobDispatcher::ChangeMode` / `RetryChangeMode` / `RetryChangeModeExceptRenderThread` / `WaitIdle` / `WaitAllIssued` / `Sleep` | `scene_dispatch.cpp` | `scene/dispatch-modes-and-parameters` | shadow replay (the dispatcher's bytes) |
| `ObjectManagerJobDispatcher::Set{PreliminarilyPrepare,PrepareForRendering,ViewFrustumCulling,DetectLIBL}BasicParameter` | `scene_dispatch.cpp` | `scene/dispatch-modes-and-parameters` | shadow replay (the workers' parameters) |

Not bound: `Dispatch_RenderingDecided` (no caller in 3.7.0), the worker's `Handler` / `Handler_*` / `ChangeMode`
(no longer reached: the worker stays parked, below), the constructors and destructors (once per process).

### The job dispatcher (scene_dispatch.cpp)

The guest's dispatcher hands each job to its single worker thread and the caller polls (RE notes,
"Busy-waits"). The natives keep the guest's job structures — the dispatcher's Set*BasicParameter and
Dispatch_X store every parameter in the worker as the guest does, and the job's body reads them from
there (`ObjectManagerWorkerThread::Run*`, one iteration of the worker's Handler_X loop: the same
RENDERINFO copy at the worker's +0x170 passed to PrepareForRendering, the same atomic ORs into the result
words) — but run the body at once on the posting thread and return true. That is one of the guest's
own schedules (a worker that finishes before the poster looks again):
- the callers scan the result words in index order (TraversePaintingList's AddRenderQueue /
  AddTemporaryResolve, OnPrePaint's context hand-out, the culling's output list), so what they produce
  doesn't depend on when the worker finished;
- jobs 4 to 6 (culling, LIBL detection, the system-flag reset) are already run on the posting thread by
  the guest itself whenever its worker is busy (MultithreadViewFrustumCulling, Prerender's
  LIBLManager::Intersect, PrepareMatrices' inline reset);
- the work OnPrePaint does after posting the last MakePaintingList (ResetServer, GetRenderContext for
  the context objects, the multi-draw counters) doesn't meet the job: MakePaintingList's only shared
  writes are atomic increments of the objects' m_contextDivisor, which commute with OnPrePaint's;
- no job takes a lock its poster holds and none reads thread-local state (pthread_getspecific is the
  render device's, on the render thread).
ChangeMode / Sleep / WaitIdle keep only the dispatcher's bookkeeping (m_workerCountSeen, m_exceptMode),
so the worker thread, created in mode 7, stays in its Event wait for the life of the process (the
guest destructor still stops it). Per-frame draw lists traced at the title (SOA_TRACE on OnPostPaint /
AddRenderQueue / AddTemporaryResolve, objects and contexts renamed by first appearance): the 13
distinct draw lists of ~3,800 frames are the same with and without the natives; at home after login
(rebase_inproc_session) the 56 distinct lists of ~5,980 frames are the same, every frame of either run
covered by the other; in mf01_001's battle (time-dependent effects) the natives' run shares 125 lists
covering 69% / 71% of the frames with the baseline, exactly what two baseline runs share (127, 69% / 72%).

### Measurements

The four flows (port/REBUILD-QUEUE.md's scripts, `SOA_PROFILE` at 1000 Hz), the baseline (main at
c52def9) and this family's binary run side by side on the same machine load, 2026-10-04:

| | baseline | natives |
|---|---|---|
| busy samples (login / battle / gacha / story) | 280,166 (40,358 / 79,836 / 60,277 / 99,695) | 229,412 (30,160 / 70,496 / 55,862 / 72,894): -18.1% |
| scene guest self | 57,963 (20.7%) | 16,609 (7.2%) |
| ObjectManagerJobDispatcher + ObjectManagerWorkerThread self | 25,480 | 5 |
| ObjectManager self (TraversePaintingList*, OnPrePaint, MultithreadViewFrustumCulling, ...) | 22,252 | 7,236 |
| game thread (AskaMainThread) busy, battle flow | 39,494 of 168,350 (23.5%) | 33,228 of 172,749 (19.2%) |

Frame rate: both at the 60 fps cap in the battle's steady state (the 10-second `I/perf` samples), so
the gain is headroom: the game thread's busy time per frame is down by about a sixth in battle and
by a quarter at login / in the story flow. Live checks (every call, `--live-check scene:every=1`): login
135,000, battle 235,000, gacha 258,000, story 351,000 checks, 0 mismatches; the same four flows on
llvmpipe (`SOA_SLOT_SOFTWARE_GL=1`, a slower render thread: other timings) 728,000 checks, 0
mismatches; Windows (soa.exe, the battle-gacha session) 220,000 checks, 0 mismatches. Again after merging
main with render's natives (bbedbbb): the four flows 1,028,000 checks, Windows 217,000, 0 mismatches.

## Dependencies

Subsystems whose types or functions this one uses (port/REBUILD-QUEUE.md has the measured call edges):
- `render`: the bases (RenderableObject, HierarchicalObject(Container), Task) from render_layout.h; pointers
  to RenderContext (0x230 bytes each), RENDERINFO, RenderPass / RenderPassManager, RenderThread,
  RenderContextServer, RenderLayer, MaterialList (embedded in AofHandler at 0xe8, 0x230 bytes, opaque here).
- `kernel`: `Aska::TaskManager` (ObjectManager's base) is kernel's (kernel_layout.h); `TaskManagerBase` aliases it.
- `sync`: Thread / Event / FastCriticalSection are opaque byte arrays of their sizes (0x18 / 0x68 / 0x90).
- `math`: render's MathVector / MathMatrix (aliases of math::Vector / Matrix since 19a4682).
- `anim`: the models' animation (AafHandler, CAnimationBlendContainer, CAnimationModel) are anim_layout.h's.
For render (fields of its RenderableObject that scene's code reads, not yet named there): 0x1ac s32
(context divisor / multi-draw count), 0x1c0 s32 (contexts wanted), 0x1cc s32 (contexts used), 0x1d0
RenderContext* (the object's contexts), 0x1a0 (a Camera*), 0x1e8..0x200, 0x230 / 0x238 (zeroed per frame),
0x22c u32 (multi-draw limit), 0x1b5 bit 0 (prepared this frame), m_renderFlags bit 9 (skinned), 21, 25;
HierarchicalObject 0x130 is the cached inverse world matrix (MakeSkinMatrices; valid when m_hoc.m_flags
bit 2) and m_hoc 0x90 a JointObject's joint orientation (property 15).

## RE notes

- **The frame (one game-thread task, ObjectManager's, run by TaskManager::OwnersKickTask):** Prerender
  (culling: m_candidates), OnPrePaint (system objects appended; MakePaintingList jobs per shadow layer,
  multipass layer and pass; PreliminarilyPrepare (slot 79) over the candidates in batches of 64),
  OnPaint / OnPostPaint (TraversePaintingList(NoResolve): PrepareForRendering (slot 80) in batches of 8,
  then RenderThread::AddRenderQueue(object, object->contexts + used * 0x230, n) per prepared object).
  Each batch goes to the job dispatcher, which has ONE worker thread in 3.7.0
  (Global::InstantiateObjectManagerJobDispatcher passes 1).
- **Busy-waits (where most of scene's self time went; native since n-scene: "The job dispatcher").** The game thread never sleeps while a job is
  out: `TraversePaintingList` (5497 self samples) and `OnPrePaint` (4073) loop on
  `Dispatch_PrepareForRendering` (6753) / `Dispatch_PreliminarilyPrepare` (1296) /
  `Dispatch_MakePaintingList` (2412): each call scans the worker for "idle in mode X" (5 flags behind
  DMB barriers) and returns false when it is busy; the caller then scans the 2-bit result words for
  finished objects and calls again: no yield, no wait (Dispatch_MakePaintingList's own retry loop calls
  Thread::Switch). `ObjectManagerJobDispatcher::ChangeMode` (315 self, 6008 inclusive) spins with
  Thread::Switch until every worker's m_job is 0, and `ObjectManagerWorkerThread::ChangeMode` (2475) /
  `Handler` (3738) spin on the worker's FastCriticalSection (LDAXR/STXR 0x1ff times, then its
  semaphore / Thread::Sleep(1)) — the same lock the game thread takes for every mode change. The jobs
  themselves (the objects' PreliminarilyPrepare / PrepareForRendering) are only the inclusive part. On a
  host with one worker this pipeline does nothing in parallel that the game thread couldn't do itself:
  a native OnPrePaint / TraversePaintingList that runs the batches inline (or a dispatcher with host
  condition variables) removes about 25,000 of scene's 48,600 self samples (8.5% of all busy samples).
- **The result words:** 2 bits per object in m_resultBits (0 pending, 1 skipped: 0x1b5 bit 0 clear, 2 done,
  3 failed), set by the worker with atomic ORs; for 3 the game thread calls the object's slot 83
  (RoutineProcedure) when m_renderFlags & 0x200008 == 0x200000.
- **AofObject's draw prep** (PrepareForRendering, 7661 inclusive): per RENDERINFO pass kind (byte 3 & 7:
  0 color, 1 z-prepass, 2 shadow cast, 3 vertex, 4 object motion blur, 5 multi-draw) a RenderPass from the
  RenderPassManager at 0x398, MakeObjectRenderState<flags> into the cached AofObjectRenderState of that
  kind, RenderPass::PrepareRenderState with m_handler's MaterialList, PrepareColorShader, then
  m_handler's slot 7 (MakeRenderContext; DirectAofHandler's: 561 self) per RenderContext (0x230 each).
- **Skinning** (SkinMatrices::MakeSkinMatrices): palette[i] = inverse(object world) * bone[i]'s world *
  bind[i] as 3x4 matrices (plain NEON mul+add, no FMA in the decompile: check the disassembly before a
  bit-exact native), then SkinMatricesBase::KickPalette.

## Hot methods (the code agents' first targets)

From the task-5 profile (login + battle + gacha + story, 293,654 busy samples;
`port/scripts/hot_methods.py scene ...`; self samples, callers):

| Method | Self | Inclusive | Called from |
|---|---|---|---|
| ObjectManagerJobDispatcher::Dispatch_PrepareForRendering | 6753 | 9045 | TraversePaintingList (7524), ...NoResolve (1521) — polling |
| ObjectManager::TraversePaintingList | 5497 | 13970 | OnPostPaint — polling the result words |
| ObjectManager::OnPrePaint | 4073 | 12645 | TaskManager::OwnersKickTask — polling |
| ObjectManagerWorkerThread::Handler | 3738 | 21626 | Thread::Main — the worker's lock spin |
| ObjectManagerWorkerThread::ChangeMode | 2475 | 8213 | the dispatcher's ChangeMode (5693), Sleep (2516) — lock spin |
| ObjectManagerJobDispatcher::Dispatch_MakePaintingList | 2412 | 2412 | OnPrePaint |
| ObjectManagerWorkerThread::Handler_PrepareForRendering | 2278 | 11613 | Handler (the job loop) |
| ObjectManager::ViewFrustumCulling | 2091 | 2269 | the worker (1513), MultithreadViewFrustumCulling (756) |
| ObjectManager::MultithreadViewFrustumCulling | 1983 | 3180 | Prerender |
| ObjectManager::TraversePaintingListNoResolve | 1851 | 3516 | OnPostPaint |
| ObjectManagerJobDispatcher::Dispatch_PreliminarilyPrepare | 1296 | 1767 | OnPrePaint |
| ObjectManager::MakePaintingList | 810 | 1138 | the worker (job 1) |
| ObjectManager::MultithreadOcclusionCulling | 673 | 1398 | Prerender |
| ObjectManager::Prerender | 650 | 13087 | OwnersKickTask |
| ObjectManager::AddPaintingListCandidates | 586 | 586 | PostProcessCombinerTBR (301), Prerender (285) |
| DirectAofHandler::MakeRenderContext | 561 | 604 | AofObject::PrepareForRendering |
| AofObject::PrepareForRendering | 442 | 7661 | Handler_PrepareForRendering |
| HierarchicalObjectContainer::MakeMatrix (render's) | 456 | 575 | MakeSkinMatrices, particles, AimingObject |
| CDirectAofTextRenderer::PreliminarilyPrepare | 357 | 515 | the worker |
| AofObject::PreliminarilyPrepare | 343 | 343 | the worker |
| CDirectAofTextRenderer::Reset | 333 | 333 | CCocosScene::Progress |
| SkinMatrices::MakeSkinMatrices | (SkinMatrices 326) | | |

(This table is the task-5 profile, before the dispatcher's natives; ObjectManager's residue after them,
side by side over the four flows: ViewFrustumCulling 1,710, MultithreadOcclusionCulling 809,
MakePaintingList 741, OnPrePaint 727, Prerender 726, AddPaintingListCandidates 636, OnPostPaint 594,
PrepareMatrices 309, TraversePaintingList 224.)

Recommended order: (1, done: "The job dispatcher") the dispatch / polling layer as one family (OnPrePaint's and
TraversePaintingList's batch loops, the Dispatch_* and both ChangeModes, the worker's Handler: they share
the worker's state, port them together; about 25k samples, pure control flow over the types here; the
objects' virtuals stay guest calls); (2) the culling (ViewFrustumCulling + the Multithread* wrappers,
4.7k; math-heavy: needs math's types and FMA care); (3) MakePaintingList / AddPaintingListCandidates
(1.4k); (4) the leaves of the draw prep (DirectAofHandler::MakeRenderContext, AofObject's
PrepareForRendering chain, MakeSkinMatrices: they need render's RenderContext / RenderPass / MaterialList).

