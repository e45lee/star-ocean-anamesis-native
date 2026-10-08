# `dynamics`: Aska's own dynamics: cloth, joints, collision

A subsystem of the native rebuild (port/PLAN.md task 6). The workflow (decompile, types, natives,
tests, Ghidra types): port/src/native/README.md "Per-subsystem workflow".

- Scope: the demangled-name patterns in [`port/decomp/dynamics/scope.txt`](../../../decomp/dynamics/scope.txt).
- Decompiles and the function list: [`port/decomp/dynamics/`](../../../decomp/dynamics/) (`symbols.tsv`; `tools/decomp.sh --into dynamics/<topic>`).
- Types: [`dynamics_layout.h`](dynamics_layout.h); for Ghidra, `tools/subsystem.py export-types dynamics` -> `port/decomp/dynamics/types.json`.
- Build settings of its own (a host library, a definition): none; a `subsystem.cmake` here would hold them (port/CMakeLists.txt includes it).

## Types (classes with their methods attached)

| Class | Guest size | Found from (ctor, decompile) | Status |
|---|---|---|---|
| `Aska::DynamicsPrimitive` | 0x60 (base) | `DynamicsCube::CreateClone` (0x20 the node, 0x30 the local position, 0x50 = &the shape at 0x60) | typed |
| `Aska::DynamicsSphere` / `DynamicsCapsule` / `DynamicsCube` / `DynamicsPlane` | 0xc0 / 0xf0 / 0x170 / 0xc0 | `CreateClone`'s `operator new`, `Run`, `Update` (`primitives.c`) | typed, natives |
| `DYNAMICS_PRIMITIVE` (the shape's head) | 0x20 | `CollisionAndConstraint` (`m_data`: two response floats, the owner ADM at 0x10) | typed |
| `Aska::DYNAMICS_CAPSULE` / `DYNAMICS_CUBE` / `DYNAMICS_SPHERE` / plane | 0x90 / 0x110 / 0x60 / 0x60 | the thunks (`this + 0x60`), `Run`, `TestIntersection*`, `CollisionAndConstraint`'s stack capsule | typed, natives |

## Natives

All are registered through the live-check family `dynamics` (`dynamics_family.cpp`, a `live::LeafFamily`
that can also snapshot memory reached through the object: `Run`'s node flags and inverse matrix):
`soa --live-check dynamics`. Differential tests: `soa --selftest dynamics/` (random shapes, points and
nodes, a fifth of the cases with special floats: signed zeros, NaNs with payloads, infinities,
denormals), compared bit for bit.

| Class::Method (guest symbol) | File | Differential tests | Live check (battle-gacha) |
|---|---|---|---|
| `DynamicsSphere::Run()` | `dynamics_primitives.cpp` | `dynamics/run` | 67K checks, 0 mismatches |
| `DynamicsPlane::Run()` | `dynamics_primitives.cpp` | `dynamics/run` | 110K checks, 0 mismatches |
| `DynamicsCapsule::Run()` | `dynamics_primitives.cpp` | `dynamics/run` | 35K checks, 0 mismatches |
| `DynamicsCube::Run()` | `dynamics_primitives.cpp` | `dynamics/run` | 11K checks, 0 mismatches |
| `DynamicsSphere` / `DynamicsPlane` / `DynamicsCube` / `DynamicsCapsule` `::Update(float, bool)` | `dynamics_primitives.cpp` | `dynamics/update` | 88K / 149K / 16K / 54K checks, 0 mismatches (20 races) |
| `DYNAMICS_CAPSULE::TestIntersection(DYNAMICS_CAPSULE*, bool, Vector*, float*, float*)` | `dynamics_primitives.cpp` | `dynamics/capsule-capsule` | 760K checks, 0 mismatches (43 races) |
| `DYNAMICS_CAPSULE::TestIntersection(Vector const*, float, Vector*)` | `dynamics_primitives.cpp` | `dynamics/capsule-point` | 2.4K checks, 0 mismatches |
| `DYNAMICS_CUBE::TestIntersection(Vector const*, float, Vector*)` | `dynamics_primitives.cpp` | `dynamics/cube-point` | 36K checks, 0 mismatches |
| `DynamicsSphere::TestIntersection(DYNAMICS_CAPSULE*, bool, Vector*, float*, float*)` | `dynamics_primitives.cpp` | `dynamics/sphere-capsule` | 465K checks, 0 mismatches |
| `DynamicsSphere::TestIntersection(Vector const*, float, Vector*)` | `dynamics_primitives.cpp` | `dynamics/sphere-point` | 78K checks, 0 mismatches |
| `DynamicsPlane::TestIntersection(Vector const*, float, Vector*)` | `dynamics_primitives.cpp` | `dynamics/plane-point` | 367K checks, 0 mismatches |

Races: the primitives run on the dynamics worker threads ("Aska::DynamicsWorker") while other workers
move the same characters' shapes; a difference the check can attribute to another thread counts as a
race, not a mismatch (as math's). The first run: 2.24M checks, 0 mismatches, 82 races.

Not ported (executed, but 4 instructions each): the primitives' `Reset()` (velocity = (0, 0, 0, 1)); the
`DynamicsCapsule` / `DynamicsCube` `TestIntersection*` thunks (`this + 0x60`, a tail call).

## Dependencies

Subsystems whose types or functions this one uses (port/REBUILD-QUEUE.md has the measured call edges):

| Subsystem | What |
|---|---|
| `math` | `Vector`, `Matrix`, `Segment` (math_layout.h); `Segment::SquaredDistance` (both, native) called as members; `math::Sqrt`, `kEpsilon`; the guest's `Vector::ApplyMatrix`, `ApplyMatrixNoTransport`, `Matrix::InvertLowError` (guest code) through `guest_call` |
| `render` | `HierarchicalObject` (render_layout.h): the node a primitive follows; its vtable slots 19 `WorldMatrix`, 21 `MakeMatrix`; `m_hoc.m_flags` bits 0 / 2, `m_flags2`, `m_invWorld` |
| `kernel` | the dynamics worker threads (`SimpleMessageDispatcher`, "Aska::DynamicsWorker") run the jobs |
| `anim` | co-developed: the IK controllers run from the ADM's notify (not touched yet) |

## RE notes

- **Calls out:** the natives make the guest's calls in the guest's order (the node's virtuals, the
  guest math helpers) as plain `guest_call`s: they are pure or idempotent, so a live check's replay of
  the original simply runs them again (dynamics_family.h).
- **The shapes' layout:** a primitive's shape starts at +0x60 (`m_data` points there); the
  `DynamicsCapsule` / `DynamicsCube` `TestIntersection*` are thunks to `DYNAMICS_CAPSULE` /
  `DYNAMICS_CUBE` with `this + 0x60`, while `DynamicsSphere` / `DynamicsPlane` test on their own fields.
  A capsule tested as the `other` operand is read at +0x40 (segment) and +0x80 (radius): the joints'
  capsule `CollisionAndConstraint` builds on its stack has that form; as `this` it uses +0x20.
- **Run's inverse:** `DynamicsCapsule::Run` and `DynamicsCube::Run` make the node's `m_invWorld`
  current inline (the rigid inverse: transposed rotation, -R^T t, the last row (0, 0, 0, 1) from
  .rodata 0x26dbb30) unless property 8 is set (`Matrix::InvertLowError`); only the cube copies it.
  The capsule's axis goes through the world matrix with its columns scaled to unit length (no epsilon).
- **Condition codes:** `DYNAMICS_CUBE::TestIntersection`'s per-axis clamp branches `b.pl` / `b.le`: a NaN
  coordinate takes the upper test and is then inside (no clamp); the capsule / sphere / plane contact
  tests (`b.ls`, `b.ge`) miss on a NaN; the normalizations (`b.mi`) scale a NaN length.
- **Guest time** (SOA_PROFILE at 1000 Hz, battle flow, the default natives): the scope's guest self
  time was ~1,500 of 62,757 busy samples (2.4%), the ADM simulation the largest share
  (`CollisionAndConstraint` 164, `SimulateMain` 129, `ADMJoint::PrepareCalc` 116, `StandardIK<true>` 91,
  plus the local helpers after `Functor_ExternalForceEmitterCalculation`: FUN_02429d78 141,
  FUN_0242a08c 109, FUN_02429994 52, FUN_0242a9f4 34, FUN_0242ac84 31), then the primitives
  (`DYNAMICS_CAPSULE::TestIntersection` 93, the `Run`s 178, `DynamicsSphere::TestIntersection` 70, the
  `Update`s 38). Only the non-MP `ArticulatedDynamicsManager` instantiations run.
