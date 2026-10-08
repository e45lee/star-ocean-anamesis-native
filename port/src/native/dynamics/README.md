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
| `Aska::ADMJoint` | 0x1c0 | `InitCalcData`, `Init`, `DefaultParam`, `PrepareCalc`, `Flush`, `ExternalForce` (`adm.c`), the templates' stride | typed (partly), natives |
| `Aska::ADM_CALC_DATA` | 0xa0 | `ADMJoint + 0xb0`, the ADM's array at +0xa0; `MatrixCalcFunc`'s arguments | typed |
| `ADMLink` (a joint's links / contact pairs) | 0x50 | `ADMJoint::PrepareCalc` (+0x28 length, +0x48 the other joint), `CollisionAndConstraint` (flags +0x20, friction +0x2c, bounce +0x30) | typed (partly) |
| `Aska::ArticulatedDynamicsManagerBase` | (0x1c0 for `ArticulatedDynamicsManager`) | `PrepareCalc(float)`, `Flush`, `Simulate`, the templates | typed (to 0x110) |
| `ADMSolver` (the local helpers after `Functor_ExternalForceEmitterCalculation<ADM>`) | - | `adm_local.c` | natives (by address) |

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

| `ADMJoint::PrepareCalc()` | `dynamics_adm.cpp` | `dynamics/joint-prepare-flush` | 508K checks, 0 mismatches (run with `only=ADMJoint11PrepareCalc`: below) |
| `ADMJoint::Flush()` | `dynamics_adm.cpp` | `dynamics/joint-prepare-flush` | 36K checks, 0 mismatches |
| `ADMJoint::ExternalForce(float, float, float, Vector const*, ADM_CALC_DATA*, bool)` | `dynamics_adm.cpp` | `dynamics/joint-external-force` | 608K checks, 0 mismatches |
| `ArticulatedDynamicsManagerBase::PrepareCalc(float)` | `dynamics_adm.cpp` | `dynamics/adm-prepare-flush` | 34K checks, 0 mismatches |
| `ArticulatedDynamicsManagerBase::Flush()` | `dynamics_adm.cpp` | `dynamics/adm-prepare-flush` | 30K checks, 0 mismatches |
| FUN_02429994 `ADMSolver::SolveLink` (the link / distance constraint; NEON estimates) | `dynamics_adm_solver.cpp` | `dynamics/solve-link`, `dynamics/neon` | 434K checks, 0 mismatches |
| FUN_0242a9f4 `ADMSolver::ResolveContact` (the contact response) | `dynamics_adm_solver.cpp` | `dynamics/resolve-contact` | 36K checks, 0 mismatches |
| FUN_0242ac84 `ADMSolver::UpdateVelocity` | `dynamics_adm_solver.cpp` | `dynamics/update-velocity` | 608K checks, 0 mismatches |

| `CollisionAndConstraint<ADM>` (the links' capsules against the primitives, the joints against the constraints and the land; the NEON inverse) | `dynamics_adm_simulate.cpp` | `dynamics/collision-and-constraint` | 37K checks, 0 mismatches (12 races; `only=22CollisionAndConstraint`) |
| `StandardIK<ADM, true>` | `dynamics_adm_simulate.cpp` | `dynamics/standard-ik` | 38K checks, 0 mismatches (`only=10StandardIK`) |
| FUN_02429d78 `ADMSolver::BlendRotation` (aim, then slerps by the step-adjusted rates) | `dynamics_adm_solver.cpp` | `dynamics/blend-rotation` | 423K checks, 0 mismatches (`only=@0x2329d78`) |
| FUN_0242a08c `ADMSolver::AimRotation` (NEON: the 3x3 inverse, FRSQRTE / FRECPE, a vectorized acos and sin / cos) | `dynamics_adm_solver.cpp` | `dynamics/aim-rotation` | 360K checks, 0 mismatches (`only=@0x232a08c`) |
| `ArticulatedDynamicsManager::Simulate(float, unsigned, float)` | `dynamics_adm_simulate.cpp` | `dynamics/simulate` | 36K checks, 0 mismatches (91 races) |
| `SimulateMain<ADM>` | `dynamics_adm_simulate.cpp` | `dynamics/simulate` | 32K checks, 0 mismatches (83 races; `only=12SimulateMain`) |
| `PreprocessBeforeInternalForce<ADM>` | `dynamics_adm_simulate.cpp` | `dynamics/preprocess` | 37K checks, 0 mismatches (`only=PreprocessBeforeInternalForce`) |
| `InterpolateRoot<ADM>` | `dynamics_adm_simulate.cpp` | `dynamics/interpolate-root` | 38K checks, 0 mismatches |
| `CollisionSetting<ADM>` | `dynamics_adm_simulate.cpp` | `dynamics/collision-setting` | 38K checks, 0 mismatches |

Still guest code in the solver (called from the natives): `MatrixPreFixAndMotionBlend<true>`, the force-emitter functor,
`StandardIK<false>` / `Finalize` (not executed in the measured flows), `MatrixCalcFunc` (not dynamics').

**Live-check runs:** a native checked on every call runs its nested natives unchecked, so the solver
is verified level by level with `only=`: the full family (Simulate at the top), `only=12SimulateMain`,
`only=PreprocessBeforeInternalForce`, `only=InterpolateRoot|CollisionSetting|@0x2329994|ExternalForce|ADMJoint11PrepareCalc`,
and the primitives / contact / velocity helpers under the native solver
(`only=14DynamicsSphere|13DynamicsPlane|15DynamicsCapsule|12DynamicsCube|DYNAMICS|@0x232a|@0x232ac`:
3.0M checks, 76 races, and 2 differences of `DynamicsCapsule::Update`'s +0x80 the race rerun didn't
classify: several ADMs share a character's collision capsules, and their CollisionSetting passes call
`Update` on the same primitive from different dynamics workers, a race of the game's. The same run
with `--guest-cpus 1` (one dynamics worker): 2.98M checks, 0 mismatches, 0 races).

A native another native calls (ADMJoint::PrepareCalc from ArticulatedDynamicsManagerBase::PrepareCalc,
ADMJoint::Flush from Flush) is called as C++ normally, but through its guest entry while the family's
live check is on (`checking()`, dynamics_family.h), so a run with `only=` checks it on its own: the
full run checks the caller every call and its nested calls run unchecked. The local helpers have no
symbols: they are registered as `@0x...` from `addresses.txt` (`at ... ref` the caller that BLs to
them; `tools/gen_addresses.py` finds BL / B targets).

Races: the primitives run on the dynamics worker threads ("Aska::DynamicsWorker") while other workers
move the same characters' shapes; a difference the check can attribute to another thread counts as a
race, not a mismatch (as math's). The run with every native above: 4.12M checks, 0 mismatches, 48 races.

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

- **NEON estimates:** the ADM solver uses FRECPE / FRSQRTE with one Newton step (FRECPS / FRSQRTS).
  `dynamics_neon.cpp` is the ARM pseudocode (as dynarmic computes them under the JIT: the port's
  layering keeps dynarmic's own headers out of port/); test `dynamics/neon` runs the four
  instructions in a guest code page over every exponent and many fractions, NaNs, denormals, and
  step operands with products near 2 / 3 (exact zeros, ties), bit for bit. The fused steps are
  computed in double with a TwoSum remainder, so the single rounding is exact on any host libm.
- **HierarchicalObjectContainer::m_flags bit 0** is the stale-matrix mark: `UpdateHierarchically` sets
  it on the node's subtree (and returns at once when it is set already), `MakeMatrix` clears it (the
  primitives' `Run` calls `MakeMatrix` when set). render_layout.h's comment ("matrix fixed (no
  hierarchy update)") reads it the other way round.
- **Shared memory:** an ADM's `m_hitFlags` array is shared by the ADMs of a character, whose workers set
  it concurrently: the live checks don't snapshot it (rewinding it for a replay raced with the other
  workers: thousands of "races" and a few unclassified differences; with one worker: 0); the unit test
  compares it.
- **NaN branches:** an unordered FCMP takes `le` / `lt` / `pl` / `hi`: e.g. `ExternalForce` doesn't damp
  with a NaN mass, `ResolveContact`'s fast-contact test (`b.le`) isn't fast on a NaN velocity.

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
- **After** (the battle flow re-profiled with every native above, same machine, 2026-10-08): the
  scope's guest self time 2,045 -> 339 samples (3.3% -> 0.8% of the run's busy samples), the natives
  567 (1.4%): the scope's time 2,045 -> 906 samples. What stays guest code: the IDE collision
  handler / dispatch pair (59 + 61: a spinlock and the dispatcher's synchronous posts around the
  height objects' guest tests), `ADMHandler::Run` (24), `DynamicsCommandNotify::Handler` (20), the
  managers' `Run`s and the rest of the scope's 750 functions (mostly unexecuted: set-up, cloning,
  property Get / Set, the MP variants, rigid bodies).
