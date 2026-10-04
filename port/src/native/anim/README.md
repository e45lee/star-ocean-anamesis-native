# `anim`: animation controllers (TAaf*), blending, IK

A subsystem of the native rebuild (port/PLAN.md task 6). The workflow (decompile, types, natives,
tests, Ghidra types): port/src/native/README.md "Per-subsystem workflow".

- Scope: the demangled-name patterns in [`port/decomp/anim/scope.txt`](../../../decomp/anim/scope.txt).
- Decompiles and the function list: [`port/decomp/anim/`](../../../decomp/anim/) (`symbols.tsv`; `tools/decomp.sh --into anim/<topic>`).
- Types: [`anim_layout.h`](anim_layout.h); for Ghidra, `tools/subsystem.py export-types anim` -> `port/decomp/anim/types.json`.
- Build settings of its own (a host library, a definition): [`subsystem.cmake`](subsystem.cmake).

## Types (classes with their methods attached)

Type recovery a wave ahead of the code (port/REBUILD-QUEUE.md: anim is wave 5; scene embeds it through the
Framework models). All in [`anim_layout.h`](anim_layout.h) (namespace `soa::native::anim`; it includes
render_layout.h for the object hierarchy and containers_layout.h for `TArray`). Proven by the
`anim/layout-*` selftests in [`anim_layout_test.cpp`](anim_layout_test.cpp): private objects built and
driven by the guest's own code, and live ones taken in the game's own calls (`TEST_PROBE`,
render_test_util.h) at home, where the character animates:
`port/scripts/selftest_live.sh build/port/soa OUT TMP anim/ --at home` (6/6 at home, 2026-10-04; at the
title the four live tests note "not on this screen" and pass).

| Class (guest) | Guest size | Found from | Proven by (anim/layout-...) | Status |
|---|---|---|---|---|
| `AafHandler` (Aska) | 0x120 (Instantiate) | Instantiate, ~AafHandler, AttachAaf, Length, IsChunkReady, the complement getters, AafCalcCommonFunctor::CalcAndSetSubFunctor | `-live-aaf-handler` (home: the header-derived counts, the one-block layout of targets / infos / cache arrays, Length(), GetComplementBufferSize(), IsAttachedComplementBuffer(), the infos' key headers); `-live-blend-container` (every element's handler) | typed; 0x030, 0x058..0x067, 0x0d8, 0x0fb..0x117 unknown |
| `AafHeader` (Aska) | 0x30 read | AttachAaf, IsChunkReady, the functor | through `-live-aaf-handler` (version 0x2e, the counts) | typed (partly) |
| `AafTarget`, `AafControllerInfo` (Aska) | 0x10, 0x30 | AttachAaf, the functor | `-live-aaf-handler` | typed |
| `AafController` (Aska; TAafNormalController's fields) | 0x48 | TAafNormalController<...>::CalcValueSub, GetControllerSize (0x10 base) | not run (the decompile only) | typed from the decompile |
| `AafBlendManager` (+ `AafBlendInfo` = IAafBlendManager::_AafInfo, `AafBlendCalcNotify` = _CalcNotify) | 0x48 (PlayAnimation: new(0x48)); infos 0x30 | Initialize, Create, Open, Close, AddAaf, Get/Set*, NormalizeWeights, _CalcNotify::Handler | `-blend-manager` (private: Initialize .. Close, the getters, NormalizeWeights); `-live-blend-manager` (home, while motions blend) | typed |
| `Framework::CAnimationBlendContainer` (+ `BlendMotionData`) | 0xb0 (last field at 0xa8); motions 0x10 | the constructor, Initialize, PlayAnimation, rElement, PresentFrame, Flag | `-blend-container` (private: ctor, Initialize(3, 2), the elements 0x68 apart, the blend-rate player); `-live-blend-container` (home: PresentFrame() / Flag() = the present element's, the motions, the manager) | typed |
| `Framework::CAnimationElement` / `CAnimationTimeElement` | 0x68 / 0x28 | the constructor, CreateAafHandler, Reset, SetPresentFrame, SetMaxLoopCount | `-blend-container` (vtables, ids, SetPresentFrame, SetMaxLoopCount, Reset) | typed; 0x14 / 0x18 start / end frame (most likely) |
| `Framework::CBlendRatePlayer` (+ `BlendRatePiece` = CPiece) | 0x18; pieces 0x1c | the constructor, Initialize, NumPlayHandle | `-blend-container` (NumPlayHandle over the pieces) | typed; CPiece's curve unknown |
| `Framework::CAnimationModel` | 0x64 data (0x68 here) | the constructor, the forwarding getters | `-live-animation-model` (home: m_pBlend, rAnimationBlendContainer(), PresentFrame() forwarding) | typed (partly); derived models are scene's |
| `TAaf*Controller<...>` instantiations | per template | | | not recovered (their data is AafController's; each template's own fields after 0x48 are not) |

## Natives

| Class::Method (guest symbol) | File | Differential tests | Live check |
|---|---|---|---|

## Dependencies

Subsystems whose types or functions this one uses (port/REBUILD-QUEUE.md has the measured call edges):
- `render`: the object hierarchy (IAnimatable, HierarchicalObject: the controllers' targets), `Task`
  (AafAutoRunTask), the opaque math values.
- `containers`: `TArray<BlendMotionData>` (CAnimationBlendContainer::m_motions).
- `kernel`: the blend manager's _CalcNotify runs on Aska::SimpleMessageDispatcher's workers (a callback).
- **Scope:** `Aska::Sequencer2` (664 self samples in the queue's anim row) is the sound sequencer
  (`Aska::SoundObject::AudioRun` calls it): audio's; anim's scope.txt doesn't claim it, but
  port/scripts/rebuild_queue.py's proposed table still maps it here until audio claims it.
  `Aska::AimingObject` moved to render (Camera's base).

## RE notes

- **The per-frame path** (home and battle, measured 2026-10-03 over login / battle / gacha / story: 3,588
  guest self samples, 1.2%): `Framework::CAnimationModel::Progress` (from CAnimationModelObject::
  Progress_Main, CEffectModel::Progress) -> `CAnimationBlendContainer::ProgressBlend` / `ProgressFrame` /
  `PlayAnimation` -> `AafBlendManager` (Open, AddAaf per motion, SetPlayFrame, SetWeight,
  NormalizeWeights, vtable slot 2 SetValues) -> one `_CalcNotify` per motion on the message dispatcher's
  workers -> `AafHandler::SetValues` / `BlendValues` -> `AafCalcCommonFunctor::CalcAndSetSubFunctor<...>`
  (426 self, 3,227 inclusive: the functor that walks the controller infos) -> each controller's
  `CalcValueSub` (the TAafNormalController<AafType<ControlPoint...>> instantiations: Quaternion_Linear
  204, Vector 140, Normal 86, ...) and `SetValueToTarget` (TAafRotateQuaternionController 109+62,
  TAafTranslateXYZController 42).
- **For the code agent, biggest first:** the functor `CalcAndSetSubFunctor<..., kTYPE_AAFCALCCNTR 0>`
  (0x1f9c508, 426 self) with `CheckCache` (0x1f9c9b8, 46): pure walks over AafHandler / AafControllerInfo
  calling controller virtuals; then the hot `CalcValueSub` instantiations (Quaternion_Linear 0x1fcf4ac,
  Vector 0x1fc4d90, Normal 0x1fab770: key search + lerp / slerp, leaf math: bit-exact FMA care needed)
  and `SetValueToTarget` (0x1fdee48, 0x1fd97a8); `CAnimationBlendContainer::PlayAnimation` (58 self,
  1,834 inclusive), `ProgressBlend`, `ProgressFrame_Direct`. `FastIkEndEffector::InverseKinematics`
  (104, battle / story only) is IK, run from the dynamics notify. Each controller instantiation is its
  own function: port the executed ones (the hot list: port/scripts/hot_methods.py anim ...).
- **Controller dispatch:** AafController's virtuals (slot k at vptr + 8k) as the functor calls them:
  12 CalcValue (+0x60), 40 CalcValueComplement, 41 CalcValueConstant, 45 SetValueToTarget (+0x168),
  57 SwapControlPoint (+0x1c8), 59 IsIndependentController (+0x1d8). A native functor still calls guest
  controllers through these slots until the controllers move too (port whole families: the cache state
  in the controller objects, m_keySlot / m_keyTime / m_keyIndex, is shared).
- **Unknowns:** AafHandler 0x030, 0x058..0x067, 0x0d8, 0x0fb..0x117; AafHeader 0x14, 0x1c, 0x24; the
  TAaf templates' own fields after AafController's 0x48; CAnimationBlendContainer 0x40, 0x78..0x87, 0x88
  (NaN at construction); CAnimationModel 0x20..0x3b; CBlendRatePlayer::CPiece's curve.
