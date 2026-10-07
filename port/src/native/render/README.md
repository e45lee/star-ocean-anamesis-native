# `render`: the GL renderer, shaders, materials, post-processing, cameras

A subsystem of the native rebuild (port/PLAN.md task 6). The workflow (decompile, types, natives,
tests, Ghidra types): port/src/native/README.md "Per-subsystem workflow".

- Scope: the demangled-name patterns in [`port/decomp/render/scope.txt`](../../../decomp/render/scope.txt).
- Decompiles and the function list: [`port/decomp/render/`](../../../decomp/render/) (`symbols.tsv`; `tools/decomp.sh --into render/<topic>`).
- Types: [`render_layout.h`](render_layout.h); for Ghidra, `tools/subsystem.py export-types render` -> `port/decomp/render/types.json`.
- Build settings of its own (a host library, a definition): [`subsystem.cmake`](subsystem.cmake).

## Types (classes with their methods attached)

Type recovery a wave ahead of the code (port/REBUILD-QUEUE.md: render is wave 5, co-developed with
scene). Every class is in [`render_layout.h`](render_layout.h) (namespace `soa::native::render`); a guest
base class is the first member `base` (composition: the classes stay standard-layout), the guest's
virtuals are members listed in vtable order. Layouts are proven by the `render/layout-*` selftests in
[`render_layout_test.cpp`](render_layout_test.cpp): private objects built by the guest's constructors
and driven by its methods, or the running game's objects read at a frame boundary
([`render_test_util.h`](render_test_util.h) `on_frame`: the body runs on the game thread inside
`Aska::ObjectManager::OnPrePaint`). `soa --selftest render/` runs them at the title;
`port/scripts/selftest_live.sh SOA OUT TMP render/ [--at home|battle]` runs them at home or in a battle
(soa --selftest on the wire against soa-server; control/soadrive/sessions/selftest_live.py).

| Class (guest) | Guest size | Found from | Proven by (render/layout-...) | Status |
|---|---|---|---|---|
| `IAnimatable` (Aska) | 0x08 | IsThisIt, Clone, GetClassID | `-renderable-object` (vtable, IsThisIt) | typed |
| `AnimatableLinkElement` (Aska) | 0x18 | | | kernel's / containers' (`containers::LinkElement`: vtable, m_prev, m_next); aliased here |
| `Task`, `TaskManager` (Aska) | 0x28, 0xff0 | | `-renderable-object` (the Task base: m_owner, m_level = Task::GetDefaultLevel()) | kernel's (kernel_layout.h); aliased here |
| `HierarchicalObjectContainer` (Aska) | 0x100 (CreateClone) | CopyParameter, Clone, AttachChild, DetachFromParent, ChildObject | `-renderable-object` (owner, world pointer, the child ring through AttachChild / DetachFromParent / GetChildObjectCount / ChildObject, the setters) | typed; 0x08, 0x90 unknown |
| `HierarchicalObject` (Aska) | 0x1a0 allocated, 0x198 data (CreateClone) | the inlined constructor, setters, Get / Set, ~HierarchicalObject, EnableSimpleDynamics | `-renderable-object` (WorldMatrix, SetPosition / SetPosture / SetScale, Get(5, 8, 13), Set(10, 11)) | typed; 0x170..0x17f, 0x188..0x190 partly |
| `RenderableObject` (Aska) | 0x310 (CreateClone) | RenderableObject(), Clone, the accessors | `-renderable-object` (color rate / offset, shadow flag bits, OnActive, motion blur, transparency, IBL, multipass ids, multi-draw, bounding sphere) | typed; about half of 0x198..0x310 named |
| `ShaderComprssionTree` (Aska, sic) | 0x50058 (CompressLZwordDic: operator new) | ctor, InsertNode, DeleteNode | `-shader-compression` (private tree: every InsertNode's m_matchLen = the brute-force longest match, parent / child / root links; the dictionary codec's round trip) | typed |
| `ShaderCompression` (Aska) | statics | the six codecs | `-shader-compression` | typed |
| `RenderContextServer` (Aska) | 0x58 (ObjectManager(): operator new) | ctor, Realloc*, ResetServer, Get* | `-render-context-server` (live, on GetRenderBatch: vtable, the new[] cookies = the counts, the light buffers) | typed |
| `RenderThread` (+ `RENDER_REQUEST`, `RenderRequestQueue` = TQueue<RENDER_REQUEST, 8192>) | 0x50298 (ObjectManager(): operator new) | ctor, dtor, GetStatus, DeviceReset, AddRenderQueue, AddBeginRender | `-render-thread` (live, two AddRenderQueue calls: the first call's entry holds its arguments, m_write advanced; the helper threads' vtables) | typed; sync members opaque |
| `RenderState` | 0x18 | ctor, Alloc, Reset, Release, setters, Apply | `-render-state` (private: the guest setters' command bytes) and `-render-context` (live states: every opcode is Apply's) | typed |
| `RenderContextBatch` | 0x130 (ReallocBatch) | ctor, ApplyState, ApplyTextures, OnPaint | `-render-context` (private ctor; live batches' states) | partial |
| `RenderContext` | 0x230 (ReallocRenderContext) | ctor, dtor, GetBatchArray, OnPaint, SetShaderConstant_* | `-render-context` (private: identities, GetBatchArray; live: GetBatchArray of each batch) | partial; register names (d) |
| `RenderDeviceGL` | 0xec0c8 (InstantiateVideoManager) | ctor, RenderManagerBase(), BindTexture, SetTexture, BindVertexFormat | `-render-device` (g_pRenderDev on the game thread: base vtable, m_data, stage count, GetGLVersion, vertex formats) | partial: base = GpuResource pool (8000 x 0x78) |
| `RenderDeviceData` (+ `TextureStateCache`, `OglStateSet0`, `StateCacheThreadSafe`, `DeviceTextureSlot`, `VertexFormatGL`) | 0xc6b0 | ctor, GetTextureStateCaches, GetBoundTextureID, BindTexture | `-render-device` (the containers by vtable; on the render thread every map bucket = GetTextureStateCaches(name), a pool slot) | partial: most of 0x8448..0xc6b0 padding |
| `MaterialContext`, `MaterialEntry` | 0x290 / 0x2a0 | ctor, Reset, MaterialList::Alloc / Connect | `-material-context` (private), `-material-list` (live) | partial |
| `ShaderConstantManager`, `RenderPassBatch` | 0x20 (start) / 0x1b8 | RenderPass::Init / Create / ~RenderPass, SetShaderConstantF_lockable | `-render-pass` | partial |
| `RenderPass` | 0x1c8 (RenderPassManager::GetPass) | ctor, Init, Create, dtor | `-render-pass` (private: Init(3), Create(0), dtor) | partial |
| `RenderPassManagerList`, `MaterialList` | 0x28 / 0x228 (data; embedded in AofHandler at +0xe8) | MaterialList(), Alloc, Connect, IsPunchthrough, Activate | `-material-list` (live at home, on RenderPass::UpdateTexture: entries' vtables, the pass's batch count, IsPunchthrough / GetActualPerPixelLightCount from the fields; not required at the title) | partial |
| `AimingObject` | 0x200 (data 0x1f5) | ctor, TargetObject, UpTargetObject, Get / Set | `-camera`, `-light` | typed |
| `Camera` | 0xf90 (CameraFactory) | ctor, Get, GetFogConst, MakeCameraMatrix, SetZBufferRange | `-camera` (live, MakeViewFrustumPlane: view (base 0x130) x world = I, Get(0x10..0x1c) = fields) | partial |
| `Light`, `LightContext` | 0x430 (AsfHandler::CreateInstanceOfObject) / 0x550 | ctor, SetLightType, Get, GetIlluminance | `-light` (private: Get = fields, SetLightType) | partial; LightContext opaque |

## Natives

Bound: `soa --list-native | grep render:`. Live check: `soa --live-check render[:every=N][:budget=N][:only=..][:out=FILE]`
(default every=1; [`render_check.h`](render_check.h): a run-both family, the guest original on private memory).

| Class::Method (guest symbol) | File | Differential tests | Live check |
|---|---|---|---|
| `ShaderComprssionTree` ctor / `InsertNode` / `DeleteNode` | `render_shader_compression.cpp` | `render/shader-compression-tree` (guest vs native tree, every word, after each of 18,000 calls) | inside CompressLZwordDic's |
| `ShaderCompression::CompressLZwordDic` | `render_shader_compression.cpp` | `render/shader-compression-edge` (sizes 0..0x40, odd, negative, long matches, none), `render/shader-compression-cache` (all 1,523 entries of the shipped cache, byte for byte) | the original into a scratch buffer: size and bytes |
| `RenderContextServer::GetRenderBatch` / `GetRenderBatchLite` / `GetLightContext` | `render_context_server.cpp` | `render/context-server-alloc` | the original on a copy taken before the native (race: the counter moved by more than n) |
| `RenderThread::AddRenderQueue` and the other `Add*` (`ChangeRenderTarget`, `ReloadZCull`, `EnableGnmOcclusionQuery`, `ExposureScale`, `EnableFastZ`, `FinishRenderTarget`, `TemporaryResolve`, `BeginRender`, `EndRender`, `CallBack`, `DataTransfer`, `OcclusionQueryBegin` / `End`), `ExecutePendingTileRegionOperationByAddress`, `ReqSwap` / `ReqDeviceInit` / `ReqDeviceReset` / `ReqExit` / `ReqGpuWait` | `render_thread.cpp` (bound in `render_thread_check.cpp`) | `render/thread-requests` (20,000 random requests, a full ring, the consumer simulated) | shadow replay: the original on a private RenderThread loaded with the state the native saw under m_queueLock; the ring slot (the guest-defined bytes), indices, status, flags, events |
| `RenderThread::GetStatus` (+ the wait for a request) | `render_thread.cpp` | `render/thread-requests` | getter (the original on the real object; race on a rerun) |
| `RenderThread::ReqCustomCommandBlock` / `ReqDownloadResourceBlock` | `render_thread.cpp` | `render/thread-block-call` (a host thread serving the call) | - (a replay would run the call twice) |
| `RenderDeviceGL::BindVertexFormat(int, int, void*)` | `render_device.cpp` | `render/device-bind-vertex-format` (300 of the render thread's calls: the guest's and the native's GL calls recorded, the state set compared) | `gl_run_both` (both runs recorded on a saved state set) |
| `RenderState::Apply`; `RenderDeviceGL::EnableAlphaBlend` / `EnableZTest` / `EnableZWrite` / `EnableStencil` / `SetZTestFunction` / `SetCullMode` / `SetDepthBias` / `SetAlphaBlendFunction` / `SetStencilOp` / `SetStencilOpCCW` / `SetTextureSampling{Filter, MipmapFilter, WrapMode, MaxAnisotropic}`; `RenderDeviceData::SetCullMode` / `SetAlphaBlendFunction` | `render_state.cpp` | `render/state-apply` (1,000 Apply calls: the guest's setter chain against the natives') | `gl_run_both` |
| `RenderDeviceData::DrawIndexedPrimitive` / `UpdateRenderState` / `UpdateVertexAttribute` / `LastMinuteDrawCommands_Blending` / `LastMinuteDrawCommands_Depth` | `render_draw.cpp` | `render/device-draw` (the guest's chain against the natives' on the render thread's draws) | `gl_run_both`, the two guest callees recorded as markers (`t_mark_callees`), the program established for real first (`establish_program`); a draw with an upload pending: skipped |
| `RenderDeviceGL::BindTexture` / `ActiveTexture` / `SetTexture` / `RemoveTexture` | `render_texture.cpp` | `render/device-textures` (1,000 SetTexture with the binds under it, 200 RemoveTexture) | `gl_run_both`; SetTexture with an upload pending: skipped |
| `RenderDeviceData::UpdateShaderProgram` (finding a linked program; creating / linking one: the guest original) | `render_program.cpp` | `render/device-shader-program` | `gl_run_both` over state set 1 and the program fields, SetShaderProgramUniform a marker |
| (hooks) `RenderDeviceData::LastMinuteDrawCommands_Textures` / `SetShaderProgramUniform` | `render_draw.cpp` | - | forward to the guest (the markers of the composite checks) |

`symbols.tsv` status `tested`: live-checked at 0 mismatches over the boot -> battle -> gacha session (19.7M
checks; and 10.9M on llvmpipe). Still `native` (differential tests only): what natives call as C++ members, so
no live call reaches its hook (UpdateVertexAttribute and the blending / depth commands under UpdateRenderState,
the tree under CompressLZwordDic: `render/device-draw` and `render/shader-compression-tree` compare them with
the guest's chain, at the title and in selftest-live at home and in a battle), and requests the flows never
made (the stencil setters, the occlusion queries, AddReloadZCull, AddDataTransfer, AddCallBack, ReqExit,
ReqGpuWait, ReqDeviceInit, the block calls, GetRenderBatchLite, SetTextureSamplingMaxAnisotropic).

Not bound (the next wave): the texture state of a draw (`LastMinuteDrawCommands_Textures`, `UpdateTextureFilters`,
`GetTextureStateCaches`, `GetBoundTextureID`), the program's creation and uniforms (`CompileShaderProgram`,
`SetShaderProgramUniform`, `GetThreadOglState1`'s creation), `BindFrameBuffer`, `ResolveDepth`, the shader constants (`SetVertexShaderConstant` / `SetPixelShaderConstant`), the instanced draw paths (the natives
run the guest originals when a draw has instance data), `LIBLManager::CopyTexture` (resource's; render's types).

## Measurements

The login and battle flows (REBUILD-QUEUE.md's scripts, `SOA_PROFILE` at 1000 Hz), main's binary (before,
5c10fda) and this branch's run side by side on the same machine load, 2026-10-04, twice (the machine was
shared with other agents' runs: the absolute counts move, the shares hold):

| Run | Busy samples | render guest self | RenderThread | RenderDeviceData | RenderDeviceGL | ShaderComprssionTree + ShaderCompression | RenderContextServer | RenderState |
|---|---|---|---|---|---|---|---|---|
| 1 before | 97,424 | 16,720 (17.2%) | 2,662 | 2,189 | 2,019 | 2,008 | 746 | 367 |
| 1 after (all but UpdateShaderProgram) | 91,981 (-5.6%) | 10,140 (11.0%) | 812 | 1,248 | 885 | 0 | 0 | 81 |
| 2 before | 123,856 | 22,031 (17.8%) | 3,203 | 3,031 | 2,864 | 2,485 | 1,048 | 544 |
| 2 after (every native above) | 117,861 (-4.8%) | 13,256 (11.2%) | 1,074 | 1,370 | 1,252 | 0 | 0 | 106 |

What is left: RenderThread's Render and Handler (the frame itself: guest); the device's shader constants
(SetVertexShaderConstant / SetPixelShaderConstant, ~520), the texture state caches and filters
(GetTextureStateCaches, LastMinuteDrawCommands_Textures, UpdateTextureFilters, GetBoundTextureID, ~570),
BindFrameBuffer, ResolveDepth, SetShaderProgramUniform, SetScissorRect / EnableScissorTest, BindVertexBuffer.
Frame rate: the battle runs at the 60 fps cap before and after (`I/perf`); a software-GL (llvmpipe) run under
load passes the boot -> battle -> gacha session with the live checks on (0 mismatches).

## Dependencies

Subsystems whose types or functions this one uses (port/REBUILD-QUEUE.md has the measured call edges):
- `memory`: `memory::DeleteManager` (Task::DeleteThis*).
- `math`: Aska::Vector / Quaternion / Matrix are math_layout.h's (`MathVector` / `MathQuaternion` /
  `MathMatrix` are aliases of `math::Vector` etc.; render, scene and anim use the aliases).
- `kernel`: `Aska::Task`, `TaskManager` and AnimatableLinkElement (containers' LinkElement) are kernel's
  (kernel_layout.h, containers_layout.h); render_layout.h includes them and aliases the names.
- **Scope moves (re-ranks the queue):** the hierarchy's bases (`IAnimatable`, `AnimatableLinkElement`,
  `HierarchicalObject`, `HierarchicalObjectContainer`, `AimingObject`) are render's (scope.txt), not
  scene's / anim's as port/scripts/rebuild_queue.py's table proposed: RenderableObject and Camera
  (render) derive from them, and render is a level below scene. scene and anim include render_layout.h.
- Upwards: the render thread and the object manager call the objects' virtuals (RenderableObject
  slots 79-84: PreliminarilyPrepare, PrepareForRendering, Render, FinishRendering): callbacks.

## RE notes

- **The object hierarchy.** IAnimatable -> AnimatableLinkElement -> Task -> HierarchicalObject (+ its
  second base HierarchicalObjectContainer at +0x30, with its own vptr) -> RenderableObject -> the
  drawables (scene's AofObject, the post-process objects, ...); AimingObject -> Camera. Each class's
  GetClassID(depth) returns its id chain (u16 ids packed in a u64, 0xf000 = IAnimatable ends it):
  `IAnimatable::IsThisIt(id)` walks it, which is how the engine tests an object's class at run time.
- **Tail padding.** HierarchicalObject is allocated as 0x1a0 bytes but its data ends at 0x198, and
  RenderableObject's first field is at 0x198 (the Itanium ABI lays a derived class's members into a
  non-POD base's tail padding). So `sizeof(HierarchicalObject)` is 0x198 here (and in types.json /
  Ghidra), and a standalone HierarchicalObject still needs 0x1a0 bytes.
- **Construction.** The Task part of every constructor stores `Task::GetDefaultLevel()` (0x40) in
  m_level, called through Task's own vtable before the derived vptr is set; the derived class's
  GetDefaultLevel (RenderableObject: 0x4000) is what TaskManager::Add uses later, most likely.
- **The scene graph.** A node's children are a ring through m_prevSibling / m_nextSibling with the
  parent's m_firstChild pointing into it; DetachFromParent hands a node's children to its parent;
  m_hoc.m_flags bit 0 ("matrix fixed") turns off the hierarchical update the setters trigger
  (Function_UpdateHierarchicallyByUsingStack<256, false>).

- **The boot-time shader-cache recompression (n-types-rdev).** `ShaderComprssionTree::InsertNode` (3,125
  self samples: 1.1% of all busy samples, about 770 in every flow) runs on the AHSL cache thread at
  boot: AHSLCacheManagerV2::Handler -> ProcDiskCacheEntry -> RebuildL2Database -> BuildLinkedDiskCacheL2
  -> AHSLBase::CreateCompressedShaderCache -> ShaderCompression::CompressLZwordDic. For each cache entry
  stored compressed (flags & 3), BuildLinkedDiskCacheL2 decompresses it into a stack buffer, creates
  the GL shader, then **compresses the entry again** in place (CreateCompressedShaderCache: memcpy of
  the header, CompressLZwordDic of the rest, the entry's flags = 3). So, unlike what
  docs/render/hair-shader.md's "no shader is generated at runtime" suggests, the client does
  shader-cache work at run time: no GLSL is generated, but every compressed entry is recompressed
  (an O(n * tree depth) LZSS encoder over 16-bit words, 0x50058-byte tree per call; each call first
  inserts the 4,079 dictionary positions). Measured with the live check: about 1,540 calls in a
  boot -> battle -> gacha session (one per compressed entry, 1,523 in the shipped cache). Now native (bit-exact: `render/shader-compression-*`,
  the live check), as a port and not a skip: the recompressed entries are stored back.
- **Atomic bump allocators.** RenderContextServer::GetRenderBatch / GetRenderBatchLite / GetLightContext
  are LDXR/STXR adds on a shared counter (1,376 / 494 self samples: contention among the
  ObjectManager worker threads); the pools are reset per frame by ResetServer.
- **The render queue.** RenderThread::AddRenderQueue writes a 0x28-byte RENDER_REQUEST without a lock
  (and bumps RenderableObject::m_renderQueued atomically); the other Add* take m_queueLock, a
  FastCriticalSection that spins 0x1ff times before the semaphore. GetStatus (831 self) is the render
  thread polling m_status under that lock: Handler loops `while (GetStatus() == 2) Render(...)`, and
  Render returns at once when the ring is empty (m_read + 1 == m_write), so between two requests of a
  frame the thread spun. The native GetStatus returns the same status but, when it is 2 and there is
  nothing to do (the ring empty, no block call), first waits for the next request: every producer is a
  native that bumps a sequence number and wakes it (a host condition variable), with a 2 ms timeout as
  the safety net. The ring stays the only state; the wait never changes what Handler sees.
- **Request entries carry stack garbage.** Add* build the entry in a stack temporary and copy all 0x28
  bytes: the bytes a request type doesn't define (BeginRender's arguments, EndRender's second and third,
  the floats' upper halves of ExposureScale) are whatever the stack held. The natives write zeros there;
  Render reads only the defined ones (render_thread_check.cpp's mask table).
- **AddRenderQueue's recheck.** After writing the entry it advances m_write only if m_read != m_write
  still, and returns 1 either way (the reader stops one short of m_write, so it can't fail).
- **RenderState is a command list**, replayed by Apply (769 self) through RenderDeviceGL setters that
  check the calling thread's OglStateSet0 (a pthread key per thread) before calling GL.
- **GetTextureStateCaches** (479 self) looks a GL texture name up in an Aska::THashMap with 64-bit
  modulo probing, twice per call (count, then find).
- **The draw path's state caches.** Every RenderDeviceGL / RenderDeviceData method looks up the calling
  thread's ASKA_OGL_STATESET0 (0x3e0 bytes: textures per unit, the active unit, the array / element buffer
  bindings, sampler records per unit, the cap bits wanted (0-6) and set in GL (7-12), color mask, front /
  cull face, blend, viewport, depth function, polygon offset, the vertex arrays wanted and enabled) through a
  pthread key (inlined get-or-create: the key with an LL/SC flag, the set allocated by
  AllocateAndStoreStateSet0 and filled by SetDefaults from the GL state); a second set (0x10 bytes,
  GetThreadOglState1) holds the program in use. The setters only record what they want there; the draw
  (UpdateRenderState and the LastMinuteDrawCommands_*) compares and calls GL. The natives use the guest's
  sets in place (`guest_getspecific`) and leave their creation to the guest originals.
- **Ghidra misreads the draw path.** "Possible PIC construction" in UpdateRenderState, DrawIndexedPrimitive,
  the LastMinuteDrawCommands, BindTexture / ActiveTexture and UpdateShaderProgram: the C drops the
  arguments of glFrontFace / glCullFace / glBlendFunc / glDepthFunc / glPolygonOffset and the cache stores
  after the GL calls, and returns early where the code goes on (UpdateShaderProgram's uniforms). The natives
  follow the disassembly (`aarch64-linux-gnu-objdump`); the differential tests compare the GL call lists.
- **Composite checks and guest callees with lasting effects.** A recorded run (glh::Recorder) doesn't execute
  GL, so a callee that uploads and then marks something clean (a buffer's handler Update, UpdateShaderProgram's
  uniforms, the texture commands) would leave the game believing GL has state it never got. The draw checks
  therefore record those callees as markers instead of running them (`t_mark_callees`, hooks that forward to
  the guest otherwise) and skip draws / SetTexture calls with an upload pending. UpdateShaderProgram, the first
  step of a draw and of UpdateRenderState, runs for real before such a check (`establish_program`): as a marker
  it would leave the device's `m_program` as it was, which CompileShaderProgramCache sets to null after
  compiling the pending programs (a battle's loading), and UpdateVertexAttribute (guest and native alike)
  reads the program unchecked. The real run afterwards finds it current (no GL call). Until 2026-10-06 the
  checks lacked this and `--live-check render` crashed in a battle whenever the first draw after the compile
  was checked (`render/device-draw` now starts every 4th draw from a null program).
- **GpuResource::m_handle** (+0x48) is a buffer's GL name but a texture's slot in the device's 0x400 texture
  slots (SetTexture: `slot > 0x3ff` returns).
- **Unknowns.** RENDERINFO's +0x02, +0x04, +0x18 (the struct: render_layout.h, recovered by n-scene from
  OnPostPaint and the object-manager worker's copy), LightManager, ShadowManager, PostProcessCombinerTBR, RenderTarget / RenderTargetManagerGL,
  RenderPassManager (0x3c0), UniformValueBuffer2, AhslConst, CameraManager (a TaskManager + Task;
  0xff0 the current camera, 0x1000 a CameraFilterManager: size not recovered); most of RenderDeviceGL's
  GpuResource (0x78) and the large paddings in Camera / Light / RenderDeviceData.
