# `math`: Math: vectors, matrices, quaternions, primitives, intersection

A subsystem of the native rebuild (port/PLAN.md task 6). The workflow (decompile, types, natives,
tests, Ghidra types): port/src/native/README.md "Per-subsystem workflow".

- Scope: the demangled-name patterns in [`port/decomp/math/scope.txt`](../../../decomp/math/scope.txt):
  the value classes `Aska::Vector`, `Matrix`, `Matrix34`, `Quaternion`, the primitives (`Segment`,
  `Line`, `Ray`, `Box`, `Sphere`, `Plane`, `AABB`, `AABB_MinMax`), `Framework::CVector` / `CMatrix` /
  `CQuaternion` and `Collision::Math`. The queue's proposal also took `Aska::Collision` (the ACF mesh
  intersection templates), `Aska::_HO_*` (height objects), `Collision::CCollision*` (the battle's
  collision field), `NormalVisitor` and `Aska::AffUtil` (the AFF file format): they need scene /
  dynamics / battle / data_formats types and are left to those subsystems.
- Decompiles and the function list: [`port/decomp/math/`](../../../decomp/math/) (`symbols.tsv`; `tools/decomp.sh --into math/<topic>`).
- Types: [`math_layout.h`](math_layout.h); for Ghidra, `tools/subsystem.py export-types math` -> `port/decomp/math/types.json`.
- Build settings: [`subsystem.cmake`](subsystem.cmake) compiles `math_*.cpp` with `-ffp-contract=off`.

## Types (classes with their methods attached)

| Class | Guest size | Found from (decompile) | Status |
|---|---|---|---|
| `Aska::Vector` | 0x10 | `Vector::ApplyMatrix` (`vector.c`): x, y, z, w | typed |
| `Aska::Quaternion` | 0x10 | `Quaternion::Create(Vector const*)` (`quaternion.c`): x, y, z, w (w scalar) | typed, 4 natives |
| `Aska::Matrix` | 0x40 | `Framework::CMatrix::Translate` (translation in column 3), `Vector::ApplyMatrix` (rows) | typed, 6 natives |
| `Aska::Matrix34` | 0x30 | `Matrix34::Mul` (`matrix34.c`) | typed |
| `Aska::Segment` | 0x20 | `Segment::SquaredDistance` (`primitives.c`): origin, direction | typed, 2 natives |
| `Aska::Sphere` | 0x10 | `AABB::SetSphere`: center, radius in w | typed |
| `Aska::Plane` | 0x20 | `Plane::ApplyMatrix`: point, unit normal | typed |
| `Aska::AABB` | 0x20 | `AABB::SetBox`, `SetSphere`: center, half extents | typed |
| `Aska::AABB_MinMax` | 0x20 | `AABB_MinMax::CalcDistance`: min, max | typed |
| `Aska::Box` | 0x50 | `AABB::SetBox`, `Box::ComputeVertices`: center, half extents, 3 axes | typed |
| `Framework::CVector` / `CQuaternion` / `CMatrix` | 0x10 / 0x10 / 0x40 | `CMatrix::PutPRS` (a tail call into `Aska::Matrix::PutPRS`), `CQuaternion::Matrix` | typed |

**What other subsystems can rely on:** `math_layout.h`'s value types (`#include "native/math/math_layout.h"`;
layout headers may include each other: `tools/subsystem.py` compiles them with `-I port/src`) with
the conventions at its top (Matrix row-major, translation in column 3, v' = M v; Quaternion w
last), and the natives below as members (`Quaternion::Slerp`, `Matrix::Mul`, ...), bit-exact with
the guest, callable from other natives directly. Not ported: `Line` and `Ray` (no hot user; their
layouts unconfirmed) and everything listed "guest code" in the header.

## Natives

All are registered through the live-check family `math` (`math_family.cpp`, `native/common/live_leaf.h`):
`soa --live-check math[:every=N]`. Differential tests: `soa --selftest math/` (tens of thousands of
random cases each: ordinary values, structured edge cases (parallel / degenerate segments, single-axis
and gimbal-lock rotations, near-zero pivots, aliasing out == in) and, for a fifth of the cases,
special floats (signed zeros, NaNs with payloads, infinities, denormals, huge and tiny values)),
compared bit for bit.

| Class::Method | File | Differential tests | Live check (login, battle, gacha, story) |
|---|---|---|---|
| `Segment::SquaredDistance(Vector const*, float*) const` | `math_segment.cpp` | `math/segment-point` | 1.4M checks, 0 mismatches (37 races) |
| `Segment::SquaredDistance(Segment const*, float*, float*) const` | `math_segment.cpp` | `math/segment-segment` | 2.4M checks, 0 mismatches (289 races, 1 unflagged race (below)) |
| `Quaternion::Create(Vector const*)` (axis-angle) | `math_quaternion.cpp` | `math/quaternion-create` | 25K checks, 0 mismatches |
| `Quaternion::Create(Matrix const*)` | `math_quaternion.cpp` | `math/quaternion-create` | 78K checks, 0 mismatches |
| `Quaternion::CreateFromEuler(float, float, float, EnumRotateType)` | `math_quaternion.cpp` | `math/quaternion-euler` | 353K checks, 0 mismatches |
| `Quaternion::Slerp(Quaternion const*, Quaternion const*, float)` | `math_quaternion.cpp` | `math/quaternion-slerp` | 2.4M checks, 0 mismatches |
| `Matrix::Mul(Matrix const*, Matrix const*)` | `math_matrix.cpp` | `math/matrix-mul` | 1.1M checks, 0 mismatches |
| `Matrix::Invert()` | `math_matrix.cpp` | `math/matrix-invert` | ~10K checks, 0 mismatches |
| `Matrix::ApplyVector(Vector*, Vector const*) const` | `math_matrix.cpp` | `math/matrix-applyvector` | ~43K checks, 0 mismatches |
| `Matrix::SetLookAtMatrixZPUp(Vector const*, Vector const*, Vector const*, float)` | `math_matrix.cpp` | `math/matrix-lookat` | 83K checks, 0 mismatches |
| `Matrix::PutPRS(Vector*, Quaternion*, Vector*) const` | `math_matrix.cpp` | `math/matrix-putprs` | 26K checks, 0 mismatches |
| `Matrix::CalcEuler(Vector*, EnumRotateType) const` | `math_matrix.cpp` | `math/matrix-euler` | 63K checks, 0 mismatches |

Races: the battle's and story's attack segments are updated by other threads while the game measures
them; the check counts a difference it can attribute to another thread as a race, not a mismatch. In
the first story run one more such call showed up as a mismatch: `Segment::SquaredDistance(Segment)`
whose `this` bytes (which it never writes) differed between the native run and the replay, i.e.
another thread's write. Since then the const members snapshot no `this` (restoring it for the replay
would rewind that thread's write). **The final run** (all 12 natives, with `hash`, every call checked):
login 634K checks, battle 2.8M (113 races), gacha 1.6M, story 2.4M (30 races): 0 mismatches.

12 natives; `math/constants` checks every `.rodata` constant they copy (`math_constants.h`) against
the lib. The rest of the scope's 189 functions stay guest code (`symbols.tsv` status `decompiled`).

## Dependencies

None (level 0). The natives call host libm (`asinf`, `acosf`, `cosf`, `atan2f`, `sqrtf`) where the guest
calls libm through the PLT: the HLE thunks call the same host functions, so the results match the
port's guest exactly (not necessarily a phone's bionic).

## RE notes

- **No fused multiply-add anywhere:** the 3.7.0 lib has 0 `fmadd` / `fmsub` / `fnmadd` / `fnmsub` /
  `fmla` / `fmls` instructions (110,503 `fmul`): it was built without contraction. Every product is
  rounded before the add, so the natives use plain `*` and `+` in the guest's order, and
  `subsystem.cmake` turns contraction off (`-ffp-contract=off`) for hosts that would fuse.
- **Operation order** follows the disassembly, not Ghidra's C: e.g. sums are `((a + b) + c) + d` or
  `d + ((a + b) + c)` per function (the NEON pairwise `faddp` / `ext` forms included), and products keep
  their operand order (it decides which NaN propagates).
- **NaNs:** the natives compute in `armf::F` (AArch64's default NaN and propagation order), and every
  branch follows the guest's condition code: an unordered `fcmp` takes `lt`, `le`, `hi`, `pl` and skips
  `gt`, `ge`, `mi`, `ls`. Ghidra's C reads them as ordered compares and is wrong for NaN inputs (e.g.
  `Segment::SquaredDistance`'s projection `b.ls`, `Slerp`'s `b.gt` / `b.mi` range check);
  `Segment::SquaredDistance(Segment)` also ends in an `fmax(d, 0)` (propagating a NaN) that Ghidra
  drops. `fcvtzs` saturates (`armf::cvtzs`).
- **The guest's own trigonometry:** `Quaternion::Create(Vector)`, `Slerp` and `SetLookAtMatrixZPUp`
  use inline polynomial sin / cos (range-reduced by multiples of pi, Horner coefficients at
  0x2864910..0x2864940) and `Slerp` an inline acos (0x287158c..); `Matrix::CalcEuler` calls libm except
  for its default order's rational asin (0x2870cd8..). `Quaternion::Create(Vector)` returns
  `(sin(a/2) axis, cos(a/2))` with the axis normalized only when its length is >= 1e-6.
- **Quirks kept:** `Matrix::Invert` is Gauss-Jordan without pivoting, a pivot within 1e-5 of zero is
  replaced by +-1e-5, and the compiler's unrolling negates `inv * a[i][k]` as `-0.0 - x` for some
  (i, k) and `-x` for others (a NaN's sign differs); `Matrix::ApplyVector` with out == v swaps the
  operand order of its products; `SetLookAtMatrixZPUp` builds the right axis from the unnormalized
  direction, returns the identity (without the translation) for a zero direction, and reads the
  eye position after the product; `Quaternion::Create(Matrix)` uses `sqrt(trace)` with m33 in the
  trace, and the identity when the selected diagonal's root is 0; `CreateFromEuler`'s order 0 (and
  any order outside 1-5) is qz * qy * qx.
- **Guest time** (SOA_PROFILE at 1000 Hz, guest self samples of this scope): task 5's four flows:
  2,657 of 359,202 busy samples (0.74%; the queue's 3,097 / 0.86% included the families left out
  above), 2,508 of them in the 12 functions ported. Before -> after, one pair per flow on the same
  machine and load: login 293 (0.58%) -> 8 guest + 68 native; battle 988 (1.00%) -> 71 guest + 235
  native (`Segment::SquaredDistance(Segment)` 74, `Slerp` 45, `Matrix::Mul` 40). Battle frame rate:
  52.4 -> 51.5 fps mean over the session's perf lines (noise: the run is paced by its taps and the
  host load).
