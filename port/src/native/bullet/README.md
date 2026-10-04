# `bullet`: Bullet Physics 2.7x and Aska's rigid-body wrapper

A subsystem of the native rebuild (port/PLAN.md task 6). The workflow (decompile, types, natives,
tests, Ghidra types): port/src/native/README.md "Per-subsystem workflow".

- Scope: the demangled-name patterns in [`port/decomp/bullet/scope.txt`](../../../decomp/bullet/scope.txt).
- Decompiles and the function list: [`port/decomp/bullet/`](../../../decomp/bullet/) (`symbols.tsv`; `tools/decomp.sh --into bullet/<topic>`).
- Types: [`bullet_layout.h`](bullet_layout.h); for Ghidra, `tools/subsystem.py export-types bullet` -> `port/decomp/bullet/types.json`.
- Build settings of its own (a host library, a definition): [`subsystem.cmake`](subsystem.cmake).

**Decision (task 6, "Bullet version pin"): leave Bullet on the guest.** No natives, no host library,
no boundary. The game's Bullet is a *locally modified* Bullet **2.75** (not 2.76–2.79, and not any
upstream release), so neither vcpkg's `bullet3` nor a `FetchContent` of an upstream tag can be
bit-exact; and in the shipped 3.7.0 content it never simulates anything (no asset carries a
rigid body), so it costs 27 samples of 359,202 (0.0%) in the profiled flows: the world's
construction at boot. Rewriting or hosting it buys nothing. The reasoning and the evidence follow.

## Summary

| Question | Answer |
|---|---|
| Version | Bullet **2.75** (2009-09), modified: the constraints (README "The pin") |
| Compiler / flags | NDK **r11c**'s clang 3.8.243773, `-O3 -fno-exceptions -fstack-protector -fPIC -DNDEBUG` (RTTI on, `BT_NO_PROFILE` off: `CProfileManager` is in), single precision |
| Match | of the 822 Bullet functions in the game's block (0x261c51c–0x265a9a4, 245 KB), 810 exist in the 2.75 build, **710 have the same size** (171 KB, 70% of the bytes), and **697** of those are **byte-identical** once relocated fields (branch targets, ADRP pages, `:lo12:` offsets) are masked; 13 differ |
| What uses it | `Aska::RigidBodyManager` (an `Aska::Task`, created by `Aska::Global::InitAll`) and `Aska::RigidBodyPrimitive*` / `RigidBodyConstraint*`, built from an `.asf` scene's `DyPr` chunk |
| Content using it | **none**: 0 of the 13,904 `.asf` / `.acf` / `.aaf` / `.apk` / `.csf` / `.fpk` / `.tpk` / `.bin` files of the 3.7.0 download + the APK's `builtin_data` carry a `DyPr` chunk (or a `RIGIDBODY*` name) |
| Executed in the four profiled flows | 21 of 801 functions: the static `btTypedConstraint` fixed body (static init, 0.3 s), `InitBullet`'s world (1.5 s), `RigidBodyManager::Run` every frame (returns at once: no primitives), the `.asf` loader's empty `Setup/Clear/RemoveRigidBodyPrimitive`. `stepSimulation` never runs. |
| Guest time | 27 samples (0.0%) self and inclusive (port/REBUILD-QUEUE.md row 34) |

## What the game uses Bullet for

`Aska::Global::InitAll` -> `Global::InstantiateRigidBodyManager` allocates the `RigidBodyManager`
(0xa8 bytes, `bullet_layout.h`), whose `InitBullet` builds a standard world (sizes from its
`operator new` calls, matching 2.75's on arm64): `btDefaultCollisionConfiguration` (0xb0),
`btCollisionDispatcher` (0x2988), `btDbvtBroadphase` (0xe0), `btSequentialImpulseConstraintSolver`
(0xf0), `btDiscreteDynamicsWorld` (0x178), gravity set; then the manager is added to the system
`TaskManager`. Its `Run(int)` calls `Simulate` only while its primitive list is non-empty;
`Simulate` steps the world (vtable +0x40: `stepSimulation(dt, fixed step, 0x7fffffff)`, the dt from
`Aska::DynamicsCommon::m_pIVSync`, only when above a minimum) and copies each body's transform to the Aska object it drives (`btDefaultMotionState`).

Bodies come only from scene files: `AsfHandler::CreateTree` records a top-level chunk `DyPr`
(`0x44795072`, stored `rPyD`) at `AsfHandler+0x500`; `CreateRigidBodyPrimitiveList` builds six
arrays of 0x48-byte `RigidBodyPrimitive{Sphere,Cube,Capsule,Cylinder,Cone,Plane}` (a `Soft` kind
exists but its `CreateBullet` is a stub: no soft bodies are linked), `SetupRigidBodyPrimitive`
binds each to its node and `RigidBodyManager::Add`s it, and the chunks
`RIGIDBODYCONSTRAINT{NAIL,HINGE,SIXDOF,SLIDER,CONE}` become `btPoint2PointConstraint` /
`btHingeConstraint` / `btGeneric6DofConstraint` / `btSliderConstraint` / `btConeTwistConstraint`
(`RigidBodyConstraint*::CreateBullet`). It's the Aska engine's generic "rigid bodies in a scene" feature. Nothing else calls Bullet: no
game-side (`C*`) code, no battle code (`CBulletObject` / `IsHitBullet` are projectiles, unrelated).

**No shipped asset has a `DyPr` chunk** (`port/decomp/bullet/pin/scan_rb.py`: ADLD -> SLZ codecs
0/5/7 -> AFF; every `.asf`/`.acf`/`.aaf` decodes to an AFF header, 0 errors). So in 3.7.0 the
world is built, ticked as an empty task, and destroyed; the profiled flows' 21 functions are all
of it. A later download could in principle ship a scene with rigid bodies; the port would then
run them on the guest, as now.

## The pin

Upstream sources: the Google Code archive (`bullet-2.72` … `bullet-2.80-rev2531`, the 2.75 release
candidates rc3/rc6/rc7); history in github.com/bulletphysics/bullet3 (no tags before 2.82).

- **The release, from the symbols (compiler-independent):** the game has
  `btPolyhedralConvexAabbCachingShape` (new in 2.75) and none of 2.76's virtuals
  (`btTypedConstraint::setParam/getParam`, `calculateSerializeBufferSize`/`serialize` on shapes,
  objects, constraints: overrides can't be dead-stripped, they'd be in the vtables);
  `calcPenDepth` still takes a `btStackAlloc*`; `btTypedConstraint`'s fixed body is 2.75's
  file-scope `static btRigidBody s_fixed` (its constructor runs from a static initializer at 0.3 s,
  before the manager exists; 2.77+ made it a function-local static, and no such guard variable
  exists). Object sizes on arm64 (`pin/sizes.cpp.in`): `btCollisionDispatcher` 10632 and
  `btSequentialImpulseConstraintSolver` 240 match 2.75 only (2.74: 9512 / 208; 2.76–2.79:
  10624 / 208); `btHingeConstraint` 792, `btGeneric6DofConstraint` 1272, `btConeTwistConstraint` 640
  match 2.75.
- **The builds** (`pin/build.sh`: every `.cpp` of LinearMath, BulletCollision, BulletDynamics,
  compiled alone; `pin/score.py`: same-size functions and vtables against the game's;
  `pin/bytes.py`: byte compare of the same-size ones with relocated fields masked):

  | Build | Same size (of the common functions) |
  |---|---|
  | 2.75, r11c clang 3.8, `-O3 -fstack-protector` | **793/912** |
  | 2.75, r11c clang 3.8, `-O3` | 791/912 |
  | 2.75, r11c clang 3.8, `-O2` / `-Os` | 763 / 630 |
  | 2.75, r11c clang 3.8, `-O3 -fstack-protector-strong` / `-fexceptions` / `-ffast-math` | 662 / 633 / 631 |
  | 2.75, r16b clang 5.0, `-O2` / `-O3` / `-Os` | 579 / 579 / 500 |
  | 2.75, GCC 4.9, `-O2` / `-Os` | 248 / 261 |
  | 2.75-rc7 / rc6 / rc3, best flags | 768 / 742 / 728 |
  | 2.74 / 2.76, best flags | 679 / 708 (and 2.76's vtables: 50/88) |

  (counts include C1/C2 aliases; per unique function: 710 of 810. `bytes.py --strict`, without the
  `:lo12:` masking, gives the same 697.) The lib's `.comment` lists
  GCC 4.9, clang 5.0.300080 (r16b: the game's own code) and clang 3.8.243773 (r11c): Bullet is the
  part built with r11c, presumably a prebuilt static library of the Aska engine.
- **The modifications** (what no build reproduces; all in the constraint solver and BVH code):
  - `btTypedConstraint` has no `solveConstraintObsolete` virtual (the game's vtables are one slot
    shorter: 8 vs 9 entries) and every constraint's `buildJacobian` is an empty 4-byte function
    (2.75 has the obsolete-solver path there: 632–2840 bytes); the `getInfo1` / `getInfo1NonVirtual`
    functions are shorter (12 vs 24 bytes: no `m_useSolveConstraintObsolete` test);
  - `btPoint2PointConstraint` is 392 bytes (2.75: 400) and `btSliderConstraint` 1104 (2.75: 1152):
    the slider's size equals 2.74's (1104), so it may be an older slider kept rather than a local edit;
    its constructors, `initParams`, `calculateTransforms` (1196 vs 1900 bytes),
    `getInfo2NonVirtual`, `testAngLimits` / `testLinLimits` differ;
  - `btSequentialImpulseConstraintSolver::solveGroup` / `solveGroupCacheFriendlySetup` /
    `solveGroupCacheFriendlyIterations` / `convertContact` (the obsolete path's callers);
  - `btQuantizedBvh::serialize` / `deSerializeInPlace` / `mergeInternalNodeAabb`,
    `btOptimizedBvh::updateBvhNodes`, `btHashedOverlappingPairCache::growTables`, `btUnionFind::reset`;
  - about 40 functions 4–24 bytes off that use `btAlignedObjectArray` (`remove`,
    `findLinearSearch`: e.g. `btRigidBody::addConstraintRef`, the dispatcher's / world's
    add / remove), i.e. a changed `btAlignedObjectArray.h` too;
  - same size but different code: `btManifoldResult::addContactPoint`, `cullPoints2`,
    `btHingeConstraint::setMotorTarget` (register allocation / scheduling: a changed inline or
    expression, not flags: the other 700 functions are identical under the same flags).
  The nearest upstream revisions don't explain them: from 2.75 to 2.76 every svn revision of
  `btTypedConstraint.h` keeps `solveConstraintObsolete`, and the 2.76-era revisions add
  `setParam` / serialization, which the game lacks.

## Recommendation

1. **Leave it on the guest** (the subsystem stays `track` in port/REBUILD-QUEUE.md). It's cold
   (0.0%), never simulates in 3.7.0 content, and a native copy would have to be verified on
   simulations the game never runs.
2. **Not a `FetchContent` host build:** no upstream version is bit-exact (the modified constraints
   and containers above), and a host Bullet would also need the guest's object layouts
   (`btRigidBody` is constructed in Aska's allocation, the world's objects live in guest memory and
   are reached through their guest vtables by guest code), so the boundary would be the whole
   `Aska::RigidBody*` wrapper plus every Bullet type it touches, for zero measured gain.
   vcpkg's `bullet3` 3.25 is further still (eight years of API and layout changes after 2.75).
3. **Not a rewrite:** 245 KB of numeric code, 801 functions, for a feature no asset uses.
4. **If a later content update ships `DyPr` chunks:** re-run `pin/scan_rb.py` on the new download and
   profile a scene with them. Should it then be hot, the cheapest exact route is a patched 2.75
   (upstream 2.75 + the modifications listed, recovered from the decompile function by function,
   checked with `pin/bytes.py` until every function compares equal) built with these flags; the
   hot path would be `btDiscreteDynamicsWorld::stepSimulation` and below, called from a native
   `RigidBodyManager::Simulate`.

## Reproducing

```sh
S=$TMP/bullet-src; B=$TMP/bullet-build   # never under work/ (read-only)
curl -LO https://storage.googleapis.com/google-code-archive-downloads/v2/code.google.com/bullet/bullet-2.75.tgz
tar xzf bullet-2.75.tgz -C $S
port/decomp/bullet/pin/build.sh $S/bullet-2.75 r11c clang $B/b275 -O3 -fno-exceptions -fstack-protector
python3 port/decomp/bullet/pin/score.py -v $B/b275       # sizes + vtables vs work/libSOA-3.7.0.so
.venv/bin/python port/decomp/bullet/pin/bytes.py -v $B/b275   # byte compare of the same-size ones
.venv/bin/python port/decomp/bullet/pin/vtab.py _ZTV17btHingeConstraint   # a game vtable's slots
.venv/bin/python port/decomp/bullet/pin/scan_rb.py        # DyPr chunks in the asset set (expect 0)
```

(`build.sh` uses `work/toolchains/android-ndk-{r11c,r16b}` with `LD_LIBRARY_PATH=work/toolchains/compat-lib`;
`sizes.cpp.in` prints class sizes as compile errors: `clang++ ... -x c++ -I$S/bullet-2.75/src -fsyntax-only sizes.cpp.in`.)

## Types (classes with their methods attached)

| Class | Guest size | Found from (ctor, decompile) | Status |
|---|---|---|---|
| `Aska::RigidBodyManager` | 0xa8 | `Global::InstantiateRigidBodyManager`, its ctor / dtor, `InitBullet`, `Run`, `Simulate` | typed (no natives) |
| `Aska::RigidBodyPrimitiveBase` | 0x48 | `AsfHandler::SetupRigidBodyPrimitive` (array stride), `RigidBodyPrimitiveSphere::CreateBullet`, `LocalCreateBullet` | typed (no natives) |
| `BtTransform`, `BtCollisionObjectHead` | 0x40, - | Bullet 2.75 headers; `Simulate`'s reads | typed |

## Natives

None (the decision above). No live-check family is registered.

| Class::Method (guest symbol) | File | Differential tests | Live check |
|---|---|---|---|

## Dependencies

None measured (port/REBUILD-QUEUE.md: no edges over 50 samples). From the decompiles: the wrapper
uses `Aska::Task` / `TaskManager` (kernel), `Aska::TList`, `Aska::AsfHandler` (scene) and
`Aska::DynamicsCommon::m_pIVSync` (the frame time); Bullet itself allocates through
`btAlignedAllocInternal` (its own default: `malloc`).

## RE notes

- Decompiles: [`port/decomp/bullet/aska_rigidbody.c`](../../../decomp/bullet/aska_rigidbody.c) (the
  manager, the `.asf` hooks, the hinge's `CreateBullet`). Bullet's own functions need no decompile:
  the 2.75 sources are the reference, plus the modifications above.
- Scope: `bullet` claims the four `Aska::AsfHandler::*RigidBody*` loader functions only because nothing
  else is scaffolded; a future `scene` subsystem claiming `Aska::AsfHandler::` may take them, `bullet`
  keeps `Aska::RigidBody*` and Bullet itself.
- The game's Bullet block is contiguous (0x261c51c–0x265a9a4); a few inline instantiations
  (`btMatrix3x3::getRotation`, `btDefaultMotionState`) live in the Aska wrapper's object at
  0x234e0e0–0x2350228, compiled with the game's own flags (r16b).
- No `btAssert` strings: built with `NDEBUG`. `btTransform::getIdentity` / `btMatrix3x3::getIdentity`
  have guard variables (thread-safe statics).
- `RigidBodyManager`'s destructor calls `CProfileNode::CleanupMemory` on `CProfileManager::Root`
  (Bullet's built-in profiler is compiled in).
