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
| `AnimatableLinkElement` (Aska) | 0x18 | the inlined constructors (links zeroed) | `-renderable-object` | typed; the links' users (TaskManager) not read |
| `Task` (Aska; kernel's) | 0x28 (Task::CreateClone) | ~Task, Remove, ChangeLevel, Clone, ForceDelete | `-renderable-object` (m_manager, m_level = Task::GetDefaultLevel()) | typed; m_flags24 / m_flags26 unknown |
| `HierarchicalObjectContainer` (Aska) | 0x100 (CreateClone) | CopyParameter, Clone, AttachChild, DetachFromParent, ChildObject | `-renderable-object` (owner, world pointer, the child ring through AttachChild / DetachFromParent / GetChildObjectCount / ChildObject, the setters) | typed; 0x08, 0x90 unknown |
| `HierarchicalObject` (Aska) | 0x1a0 allocated, 0x198 data (CreateClone) | the inlined constructor, setters, Get / Set, ~HierarchicalObject, EnableSimpleDynamics | `-renderable-object` (WorldMatrix, SetPosition / SetPosture / SetScale, Get(5, 8, 13), Set(10, 11)) | typed; 0x170..0x17f, 0x188..0x190 partly |
| `RenderableObject` (Aska) | 0x310 (CreateClone) | RenderableObject(), Clone, the accessors | `-renderable-object` (color rate / offset, shadow flag bits, OnActive, motion blur, transparency, IBL, multipass ids, multi-draw, bounding sphere) | typed; about half of 0x198..0x310 named |

## Natives

| Class::Method (guest symbol) | File | Differential tests | Live check |
|---|---|---|---|

## Dependencies

Subsystems whose types or functions this one uses (port/REBUILD-QUEUE.md has the measured call edges):
- `memory`: `memory::DeleteManager` (Task::DeleteThis*).
- `math` (n-hash-math; not on main yet): Aska::Vector / Quaternion / Matrix are opaque `MathVector` /
  `MathQuaternion` / `MathMatrix` of the guest's sizes here; swap them for `math::Vector` etc. once
  math_layout.h is merged (`using MathVector = math::Vector;`).
- `kernel`: **`Aska::Task` and `Aska::AnimatableLinkElement` are kernel's classes, parked here** as every
  scene object's base (Task's methods are in render's symbols.tsv with that note; render's scope.txt
  doesn't claim them). When kernel's layout header recovers them, it takes them over and
  render_layout.h includes it. `TaskManager` is opaque here.
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
