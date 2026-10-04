// port/decomp/render/renderable_object.c: Ghidra decompiles for the render subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-04 06:08 UTC: tools/decomp.sh '--into' 'render/renderable_object' 'Aska::RenderableObject::' 'Aska::Camera::Camera\(' 'Aska::Light::Light\(' 'Aska::AofObject::AofObject\(\)'

// ==== Aska::RenderableObject::VirtualBoundingSphere()
// vaddr 0x1e766c0 | ghidra 0x1f766c0 | size 48 | symbol _ZN4Aska16RenderableObject21VirtualBoundingSphereEv | lib libSOA-3.7.0.so | 2026-10-04
long * _ZN4Aska16RenderableObject21VirtualBoundingSphereEv(long *param_1)

{
  if ((*(byte *)(param_1 + 0x25) >> 4 & 1) == 0) {
    (**(code **)(*param_1 + 600))(param_1,1);
  }
  return param_1 + 0x5a;
}

// ==== Aska::RenderableObject::OnActive(bool)
// vaddr 0x1e766f0 | ghidra 0x1f766f0 | size 28 | symbol _ZN4Aska16RenderableObject8OnActiveEb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16RenderableObject8OnActiveEb(long param_1,uint param_2)

{
  uint uVar1;
  
  uVar1 = *(uint *)(param_1 + 0x198) & 0xffffdfff;
  if ((param_2 & 1) == 0) {
    uVar1 = *(uint *)(param_1 + 0x198) | 0x2000;
  }
  *(uint *)(param_1 + 0x198) = uVar1;
  return;
}

// ==== Aska::RenderableObject::UpdateMultiDrawVars()
// vaddr 0x1e7670c | ghidra 0x1f7670c | size 8 | symbol _ZN4Aska16RenderableObject19UpdateMultiDrawVarsEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16RenderableObject19UpdateMultiDrawVarsEv(long param_1)

{
  *(undefined4 *)(param_1 + 0x228) = 0;
  return;
}

// ==== Aska::RenderableObject::SetShadowManagerIndex(int, unsigned long)
// vaddr 0x1e76714 | ghidra 0x1f76714 | size 4 | symbol _ZN4Aska16RenderableObject21SetShadowManagerIndexEim | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16RenderableObject21SetShadowManagerIndexEim(void)

{
  return;
}

// ==== Aska::RenderableObject::GetShadowManagerIndex(int)
// vaddr 0x1e76718 | ghidra 0x1f76718 | size 8 | symbol _ZN4Aska16RenderableObject21GetShadowManagerIndexEi | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska16RenderableObject21GetShadowManagerIndexEi(void)

{
  return 0;
}

// ==== Aska::RenderableObject::GetShaderAdapterCache(int)
// vaddr 0x1e76720 | ghidra 0x1f76720 | size 8 | symbol _ZN4Aska16RenderableObject21GetShaderAdapterCacheEi | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska16RenderableObject21GetShaderAdapterCacheEi(void)

{
  return 0;
}

// ==== Aska::RenderableObject::GetShaderAdapterCacheSize() const
// vaddr 0x1e76728 | ghidra 0x1f76728 | size 8 | symbol _ZNK4Aska16RenderableObject25GetShaderAdapterCacheSizeEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska16RenderableObject25GetShaderAdapterCacheSizeEv(void)

{
  return 0;
}

// ==== Aska::RenderableObject::SetShaderAdapterCacheCount(int, int)
// vaddr 0x1e76730 | ghidra 0x1f76730 | size 4 | symbol _ZN4Aska16RenderableObject26SetShaderAdapterCacheCountEii | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16RenderableObject26SetShaderAdapterCacheCountEii(void)

{
  return;
}

// ==== Aska::RenderableObject::ResetDynamicShaderModifier()
// vaddr 0x1e76734 | ghidra 0x1f76734 | size 4 | symbol _ZN4Aska16RenderableObject26ResetDynamicShaderModifierEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16RenderableObject26ResetDynamicShaderModifierEv(void)

{
  return;
}

// ==== Aska::RenderableObject::EnableCastShadow(bool)
// vaddr 0x1e76738 | ghidra 0x1f76738 | size 24 | symbol _ZN4Aska16RenderableObject16EnableCastShadowEb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16RenderableObject16EnableCastShadowEb(long param_1,ushort param_2)

{
  ushort uVar1;
  
  uVar1 = *(ushort *)(param_1 + 0x1b5);
  *(ushort *)(param_1 + 0x1b5) = uVar1 & 0xffe0 | uVar1 & 0xf | (param_2 & 1) << 4;
  return;
}

// ==== Aska::RenderableObject::EnableReceiveShadow(bool)
// vaddr 0x1e76750 | ghidra 0x1f76750 | size 24 | symbol _ZN4Aska16RenderableObject19EnableReceiveShadowEb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16RenderableObject19EnableReceiveShadowEb(long param_1,ushort param_2)

{
  ushort uVar1;
  
  uVar1 = *(ushort *)(param_1 + 0x1b5);
  *(ushort *)(param_1 + 0x1b5) = uVar1 & 0xffc0 | uVar1 & 0x1f | (param_2 & 1) << 5;
  return;
}

// ==== Aska::RenderableObject::EnableReceiveProjector(bool)
// vaddr 0x1e76768 | ghidra 0x1f76768 | size 24 | symbol _ZN4Aska16RenderableObject22EnableReceiveProjectorEb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16RenderableObject22EnableReceiveProjectorEb(long param_1,ushort param_2)

{
  ushort uVar1;
  
  uVar1 = *(ushort *)(param_1 + 0x1b5);
  *(ushort *)(param_1 + 0x1b5) = uVar1 & 0xff00 | uVar1 & 0x7f | (param_2 & 1) << 7;
  return;
}

// ==== Aska::RenderableObject::PrepareLightContext(Aska::LightManager*)
// vaddr 0x1e76780 | ghidra 0x1f76780 | size 20 | symbol _ZN4Aska16RenderableObject19PrepareLightContextEPNS_12LightManagerE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16RenderableObject19PrepareLightContextEPNS_12LightManagerE(long param_1)

{
  *(ushort *)(param_1 + 0x1b5) = *(ushort *)(param_1 + 0x1b5) | 2;
  return;
}

// ==== Aska::RenderableObject::IsAffectingLight(Aska::Light*)
// vaddr 0x1e76794 | ghidra 0x1f76794 | size 8 | symbol _ZN4Aska16RenderableObject16IsAffectingLightEPNS_5LightE | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska16RenderableObject16IsAffectingLightEPNS_5LightE(void)

{
  return 0;
}

// ==== Aska::RenderableObject::QueryPrebuiltVariation() const
// vaddr 0x1e7679c | ghidra 0x1f7679c | size 8 | symbol _ZNK4Aska16RenderableObject22QueryPrebuiltVariationEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska16RenderableObject22QueryPrebuiltVariationEv(void)

{
  return 1;
}

// ==== Aska::RenderableObject::SetPrebuiltVariation(int)
// vaddr 0x1e767a4 | ghidra 0x1f767a4 | size 4 | symbol _ZN4Aska16RenderableObject20SetPrebuiltVariationEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16RenderableObject20SetPrebuiltVariationEi(void)

{
  return;
}

// ==== Aska::RenderableObject::GetCurrentPrebuiltVariation() const
// vaddr 0x1e767a8 | ghidra 0x1f767a8 | size 8 | symbol _ZNK4Aska16RenderableObject27GetCurrentPrebuiltVariationEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska16RenderableObject27GetCurrentPrebuiltVariationEv(void)

{
  return 0;
}

// ==== Aska::RenderableObject::CheckRenderContexts()
// vaddr 0x1e767b0 | ghidra 0x1f767b0 | size 4 | symbol _ZN4Aska16RenderableObject19CheckRenderContextsEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16RenderableObject19CheckRenderContextsEv(void)

{
  return;
}

// ==== Aska::RenderableObject::DoesInsertToPaintingList(Aska::RenderableObject::IPL*, int, int, int const*)
// vaddr 0x1e767b4 | ghidra 0x1f767b4 | size 8 | symbol _ZN4Aska16RenderableObject24DoesInsertToPaintingListEPNS0_3IPLEiiPKi | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska16RenderableObject24DoesInsertToPaintingListEPNS0_3IPLEiiPKi(void)

{
  return 0;
}

// ==== Aska::RenderableObject::SetSystemColorRate(Aska::Vector const*)
// vaddr 0x1e767bc | ghidra 0x1f767bc | size 36 | symbol _ZN4Aska16RenderableObject18SetSystemColorRateEPKNS_6VectorE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16RenderableObject18SetSystemColorRateEPKNS_6VectorE(long param_1,undefined4 *param_2)

{
  *(undefined4 *)(param_1 + 0x270) = *param_2;
  *(undefined4 *)(param_1 + 0x274) = param_2[1];
  *(undefined4 *)(param_1 + 0x278) = param_2[2];
  *(undefined4 *)(param_1 + 0x27c) = param_2[3];
  return;
}

// ==== Aska::RenderableObject::SystemColorRate() const
// vaddr 0x1e767e0 | ghidra 0x1f767e0 | size 8 | symbol _ZNK4Aska16RenderableObject15SystemColorRateEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK4Aska16RenderableObject15SystemColorRateEv(long param_1)

{
  return param_1 + 0x270;
}

// ==== Aska::RenderableObject::SetColorRate(Aska::Vector const*)
// vaddr 0x1e767e8 | ghidra 0x1f767e8 | size 36 | symbol _ZN4Aska16RenderableObject12SetColorRateEPKNS_6VectorE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16RenderableObject12SetColorRateEPKNS_6VectorE(long param_1,undefined4 *param_2)

{
  *(undefined4 *)(param_1 + 0x270) = *param_2;
  *(undefined4 *)(param_1 + 0x274) = param_2[1];
  *(undefined4 *)(param_1 + 0x278) = param_2[2];
  *(undefined4 *)(param_1 + 0x27c) = param_2[3];
  return;
}

// ==== Aska::RenderableObject::ColorRate() const
// vaddr 0x1e7680c | ghidra 0x1f7680c | size 8 | symbol _ZNK4Aska16RenderableObject9ColorRateEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK4Aska16RenderableObject9ColorRateEv(long param_1)

{
  return param_1 + 0x270;
}

// ==== Aska::RenderableObject::SetSystemColorOffset(Aska::Vector const*)
// vaddr 0x1e76814 | ghidra 0x1f76814 | size 36 | symbol _ZN4Aska16RenderableObject20SetSystemColorOffsetEPKNS_6VectorE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16RenderableObject20SetSystemColorOffsetEPKNS_6VectorE
               (long param_1,undefined4 *param_2)

{
  *(undefined4 *)(param_1 + 0x280) = *param_2;
  *(undefined4 *)(param_1 + 0x284) = param_2[1];
  *(undefined4 *)(param_1 + 0x288) = param_2[2];
  *(undefined4 *)(param_1 + 0x28c) = param_2[3];
  return;
}

// ==== Aska::RenderableObject::SystemColorOffset() const
// vaddr 0x1e76838 | ghidra 0x1f76838 | size 8 | symbol _ZNK4Aska16RenderableObject17SystemColorOffsetEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK4Aska16RenderableObject17SystemColorOffsetEv(long param_1)

{
  return param_1 + 0x280;
}

// ==== Aska::RenderableObject::SetColorOffset(Aska::Vector const*)
// vaddr 0x1e76840 | ghidra 0x1f76840 | size 36 | symbol _ZN4Aska16RenderableObject14SetColorOffsetEPKNS_6VectorE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16RenderableObject14SetColorOffsetEPKNS_6VectorE(long param_1,undefined4 *param_2)

{
  *(undefined4 *)(param_1 + 0x280) = *param_2;
  *(undefined4 *)(param_1 + 0x284) = param_2[1];
  *(undefined4 *)(param_1 + 0x288) = param_2[2];
  *(undefined4 *)(param_1 + 0x28c) = param_2[3];
  return;
}

// ==== Aska::RenderableObject::ColorOffset() const
// vaddr 0x1e76864 | ghidra 0x1f76864 | size 8 | symbol _ZNK4Aska16RenderableObject11ColorOffsetEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK4Aska16RenderableObject11ColorOffsetEv(long param_1)

{
  return param_1 + 0x280;
}

// ==== Aska::RenderableObject::SetProgrammableTransparency(Aska::RenderableObject::ProgTrans)
// vaddr 0x1e7686c | ghidra 0x1f7686c | size 8 | symbol _ZN4Aska16RenderableObject27SetProgrammableTransparencyENS0_9ProgTransE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16RenderableObject27SetProgrammableTransparencyENS0_9ProgTransE
               (long param_1,undefined1 param_2)

{
  *(undefined1 *)(param_1 + 0x1b4) = param_2;
  return;
}

// ==== Aska::RenderableObject::SetIBLAcceptanceNumber(unsigned int)
// vaddr 0x1e76874 | ghidra 0x1f76874 | size 8 | symbol _ZN4Aska16RenderableObject22SetIBLAcceptanceNumberEj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16RenderableObject22SetIBLAcceptanceNumberEj(long param_1,undefined1 param_2)

{
  *(undefined1 *)(param_1 + 0x248) = param_2;
  return;
}

// ==== Aska::RenderableObject::ComputeBoundingSphere(bool)
// vaddr 0x1e7687c | ghidra 0x1f7687c | size 32 | symbol _ZN4Aska16RenderableObject21ComputeBoundingSphereEb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16RenderableObject21ComputeBoundingSphereEb(long param_1)

{
  undefined8 uVar1;
  undefined8 uVar2;
  
  uVar2 = *(undefined8 *)(PTR__ZN4Aska16RenderableObject16m_vDefaultSphereE_02cbd4d0 + 8);
  uVar1 = *(undefined8 *)PTR__ZN4Aska16RenderableObject16m_vDefaultSphereE_02cbd4d0;
  *(byte *)(param_1 + 0x128) = *(byte *)(param_1 + 0x128) | 0x10;
  *(undefined8 *)(param_1 + 0x2d8) = uVar2;
  *(undefined8 *)(param_1 + 0x2d0) = uVar1;
  return;
}

// ==== Aska::RenderableObject::GetBoundingBoxDirect(Aska::OrientedBoundingBox*)
// vaddr 0x1e7689c | ghidra 0x1f7689c | size 8 | symbol _ZN4Aska16RenderableObject20GetBoundingBoxDirectEPNS_19OrientedBoundingBoxE | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska16RenderableObject20GetBoundingBoxDirectEPNS_19OrientedBoundingBoxE(void)

{
  return 0;
}

// ==== Aska::RenderableObject::HasBoundingBox() const
// vaddr 0x1e768a4 | ghidra 0x1f768a4 | size 8 | symbol _ZNK4Aska16RenderableObject14HasBoundingBoxEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska16RenderableObject14HasBoundingBoxEv(void)

{
  return 0;
}

// ==== Aska::RenderableObject::RenderingDecided()
// vaddr 0x1e768ac | ghidra 0x1f768ac | size 44 | symbol _ZN4Aska16RenderableObject16RenderingDecidedEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16RenderableObject16RenderingDecidedEv(long param_1)

{
  if (((*(uint *)(param_1 + 0x1b0) & 7) != 0) ||
     (((*(uint *)(param_1 + 0x1b0) & 0x600) != 0 && ((*(byte *)(param_1 + 400) & 0x1c) != 0)))) {
    *(undefined8 *)(param_1 + 0x188) = 0;
  }
  return;
}

// ==== Aska::RenderableObject::ResolveTargetGL(int, int)
// vaddr 0x1e768d8 | ghidra 0x1f768d8 | size 8 | symbol _ZN4Aska16RenderableObject15ResolveTargetGLEii | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska16RenderableObject15ResolveTargetGLEii(void)

{
  return 0;
}

// ==== Aska::RenderableObject::RoutineProcedure()
// vaddr 0x1e768e0 | ghidra 0x1f768e0 | size 4 | symbol _ZN4Aska16RenderableObject16RoutineProcedureEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16RenderableObject16RoutineProcedureEv(void)

{
  return;
}

// ==== Aska::RenderableObject::FinishRendering()
// vaddr 0x1e768e4 | ghidra 0x1f768e4 | size 4 | symbol _ZN4Aska16RenderableObject15FinishRenderingEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16RenderableObject15FinishRenderingEv(void)

{
  return;
}

// ==== Aska::RenderableObject::ReleaseShaderCache()
// vaddr 0x1e768e8 | ghidra 0x1f768e8 | size 8 | symbol _ZN4Aska16RenderableObject18ReleaseShaderCacheEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska16RenderableObject18ReleaseShaderCacheEv(void)

{
  return 0;
}

// ==== Aska::RenderableObject::EnableObjectMotionBlur(bool)
// vaddr 0x1e768f0 | ghidra 0x1f768f0 | size 28 | symbol _ZN4Aska16RenderableObject22EnableObjectMotionBlurEb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16RenderableObject22EnableObjectMotionBlurEb(long param_1,uint param_2)

{
  uint uVar1;
  
  uVar1 = *(uint *)(param_1 + 0x198) | 0x4000000;
  if ((param_2 & 1) == 0) {
    uVar1 = *(uint *)(param_1 + 0x198) & 0xfbffffff;
  }
  *(uint *)(param_1 + 0x198) = uVar1;
  return;
}

// ==== Aska::RenderableObject::ProcessTextureDiscard()
// vaddr 0x1e7690c | ghidra 0x1f7690c | size 4 | symbol _ZN4Aska16RenderableObject21ProcessTextureDiscardEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16RenderableObject21ProcessTextureDiscardEv(void)

{
  return;
}

// ==== Aska::RenderableObject::ProcessTextureAllocate()
// vaddr 0x1e76910 | ghidra 0x1f76910 | size 4 | symbol _ZN4Aska16RenderableObject22ProcessTextureAllocateEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16RenderableObject22ProcessTextureAllocateEv(void)

{
  return;
}

// ==== Aska::RenderableObject::GetDefaultLevel() const
// vaddr 0x1e77bb8 | ghidra 0x1f77bb8 | size 8 | symbol _ZNK4Aska16RenderableObject15GetDefaultLevelEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska16RenderableObject15GetDefaultLevelEv(void)

{
  return 0x4000;
}

// ==== Aska::AofObject::SetProgrammableTransparency(Aska::RenderableObject::ProgTrans)
// vaddr 0x20c2680 | ghidra 0x21c2680 | size 296 | symbol _ZN4Aska9AofObject27SetProgrammableTransparencyENS_16RenderableObject9ProgTransE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska9AofObject27SetProgrammableTransparencyENS_16RenderableObject9ProgTransE
               (long *param_1,uint param_2)

{
  byte bVar1;
  long *plVar2;
  undefined8 uVar3;
  ulong uVar4;
  long lVar5;
  
  if ((*(byte *)((long)param_1 + 0x1b4) != param_2) &&
     (*(char *)((long)param_1 + 0x1b4) = (char)param_2, (*(uint *)(param_1 + 0x6f) >> 0x10 & 1) == 0
     )) {
    uVar4 = (ulong)*(ushort *)((long)param_1 + 0x462);
    if (uVar4 != 0) {
      lVar5 = 0;
      do {
        uVar4 = uVar4 - 1;
        plVar2 = param_1 + 0x8e;
        if ((long *)param_1[0x8b] != (long *)0x0) {
          plVar2 = (long *)param_1[0x8b];
        }
        *(undefined1 *)((long)plVar2 + lVar5 + 0x1a) = 0;
        lVar5 = lVar5 + 0x20;
      } while (uVar4 != 0);
    }
    if ((int)param_2 < 1) {
      if (*(byte *)((long)param_1 + 0x386) != 0xff) {
        if (*(byte *)((long)param_1 + 0x386) < 5) {
          *(uint *)(param_1 + 0x33) = *(uint *)(param_1 + 0x33) | 0x10;
          if ((param_1[0x7b] == 0) ||
             (uVar4 = Aska::MaterialList::IsPunchthrough()(param_1[0x7b] + 0xe8), (uVar4 & 1) == 0)) {
            *(uint *)(param_1 + 0x36) = *(uint *)(param_1 + 0x36) | 0x10;
          }
        }
        (**(code **)(*param_1 + 0x160))(param_1,*(undefined1 *)((long)param_1 + 0x386));
        *(undefined1 *)((long)param_1 + 0x386) = 0xff;
      }
    }
    else {
      bVar1 = *(byte *)((long)param_1 + 0x1b7);
      if (bVar1 < 5) {
        *(byte *)((long)param_1 + 0x386) = bVar1;
        if (bVar1 != 2) {
          if (bVar1 == 4) {
            lVar5 = *param_1;
            uVar3 = 5;
          }
          else {
            lVar5 = *param_1;
            uVar3 = 6;
          }
          (**(code **)(lVar5 + 0x160))(param_1,uVar3);
        }
        *(uint *)(param_1 + 0x33) = *(uint *)(param_1 + 0x33) & 0xffffffef;
        *(uint *)(param_1 + 0x36) = *(uint *)(param_1 + 0x36) & 0xffffffef;
        return;
      }
    }
  }
  return;
}

// ==== Aska::Camera::Camera()
// vaddr 0x20e92bc | ghidra 0x21e92bc | size 976 | symbol _ZN4Aska6CameraC2Ev | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska6CameraC1Ev(long *param_1)

{
  long lVar1;
  undefined *puVar2;
  undefined *puVar3;
  long lVar4;
  
  Aska::AimingObject::AimingObject()();
  *(undefined1 *)((long)param_1 + 0x1f5) = 0;
  puVar3 = PTR__ZTVN4Aska6CameraE_02cc27a8;
  *(undefined1 *)((long)param_1 + 0x949) = 0;
  puVar2 = PTR__ZTVN4Aska6TArrayINS_6Camera7AFPointELb1EEE_02cba8f0;
  *(undefined1 *)((long)param_1 + 0xeb1) = 0xff;
  param_1[0x1d2] = 0;
  param_1[0x1d1] = 0;
  param_1[0x1d0] = 0;
  *(undefined4 *)(param_1 + 0x1d4) = 0;
  *(undefined2 *)((long)param_1 + 0xeae) = 0;
  param_1[0x1d3] = 8;
  param_1[0x1c3] = 0;
  param_1[0x1c2] = 0;
  lVar1 = _UNK_029c8ce8;
  lVar4 = _UNK_029c8ce0;
  *param_1 = (long)(puVar3 + 0x10);
  param_1[0x1ce] = (long)(puVar2 + 0x10);
  *(undefined4 *)(param_1 + 0x1aa) = 0;
  *(undefined8 *)((long)param_1 + 0xd54) = 0;
  *(undefined1 *)(param_1 + 0x129) = 0;
  param_1[0x128] = 0;
  *(undefined1 *)((long)param_1 + 0xeb2) = 0;
  *(undefined4 *)(param_1 + 0x12a) = 0;
  *(undefined8 *)((long)param_1 + 0x954) = 0;
  *(undefined4 *)(param_1 + 0x1c4) = 0x41700000;
  *(undefined4 *)((long)param_1 + 0xe24) = 0xc0c00000;
  *(undefined4 *)(param_1 + 0x1c5) = 0x41800000;
  *(undefined4 *)((long)param_1 + 0x95c) = 0x3f800000;
  param_1[0x1c6] = 0;
  *(undefined4 *)(param_1 + 0x1bc) = 0;
  param_1[0x1cb] = lVar1;
  param_1[0x1ca] = lVar4;
  *(ushort *)((long)param_1 + 0xeb3) = *(ushort *)((long)param_1 + 0xeb3) & 0xc010 | 0x26;
  *(undefined4 *)((long)param_1 + 0xe64) = 0x3f800000;
  lVar4 = operator new[](unsigned long, std::nothrow_t const&)(0x98,PTR__ZSt7nothrow_02cb9a80);
  param_1[0x1cf] = lVar4;
  if (lVar4 == 0) {
    lVar4 = param_1[0x1d1];
    *(undefined2 *)(param_1 + 0x1d4) = 1;
    memset(0,0,0x98);
    if (lVar4 < 1) goto code_r0x021e9654;
  }
  else {
    *(undefined2 *)(param_1 + 0x1d4) = 0;
    param_1[0x1d1] = 0x13;
    param_1[0x1d0] = 0x13;
    memset(lVar4,0,0x98);
  }
  *(undefined8 *)param_1[0x1cf] = 0;
  if (((((((1 < param_1[0x1d1]) &&
          (*(undefined8 *)(param_1[0x1cf] + 8) = 0xbe23d70a3de147ae, 2 < param_1[0x1d1])) &&
         (*(undefined8 *)(param_1[0x1cf] + 0x10) = 0x3e23d70a, 3 < param_1[0x1d1])) &&
        ((*(undefined8 *)(param_1[0x1cf] + 0x18) = 0x3e23d70a3de147ae, 4 < param_1[0x1d1] &&
         (*(undefined8 *)(param_1[0x1cf] + 0x20) = 0x3eae147b00000000, 5 < param_1[0x1d1])))) &&
       ((*(undefined8 *)(param_1[0x1cf] + 0x28) = 0x3e23d70abde147ae, 6 < param_1[0x1d1] &&
        ((*(undefined8 *)(param_1[0x1cf] + 0x30) = 0xbe23d70a, 7 < param_1[0x1d1] &&
         (*(undefined8 *)(param_1[0x1cf] + 0x38) = 0xbe23d70abde147ae, 8 < param_1[0x1d1])))))) &&
      (*(undefined8 *)(param_1[0x1cf] + 0x40) = 0xbeae147b00000000, 9 < param_1[0x1d1])) &&
     (((((*(undefined8 *)(param_1[0x1cf] + 0x48) = 0xbea8f5c33e6b851f, 10 < param_1[0x1d1] &&
         (*(undefined8 *)(param_1[0x1cf] + 0x50) = 0xbe23d70a3eb33333, 0xb < param_1[0x1d1])) &&
        (*(undefined8 *)(param_1[0x1cf] + 0x58) = 0x3ecccccd, 0xc < param_1[0x1d1])) &&
       (((*(undefined8 *)(param_1[0x1cf] + 0x60) = 0x3e23d70a3eb33333, 0xd < param_1[0x1d1] &&
         (*(undefined8 *)(param_1[0x1cf] + 0x68) = 0x3ea8f5c33e6b851f, 0xe < param_1[0x1d1])) &&
        ((*(undefined8 *)(param_1[0x1cf] + 0x70) = 0x3ea8f5c3be6b851f, 0xf < param_1[0x1d1] &&
         ((*(undefined8 *)(param_1[0x1cf] + 0x78) = 0x3e23d70abeb33333, 0x10 < param_1[0x1d1] &&
          (*(undefined8 *)(param_1[0x1cf] + 0x80) = 0xbecccccd, 0x11 < param_1[0x1d1])))))))) &&
      (*(undefined8 *)(param_1[0x1cf] + 0x88) = 0xbe23d70abeb33333, 0x12 < param_1[0x1d1])))) {
    *(undefined8 *)(param_1[0x1cf] + 0x90) = 0xbea8f5c3be6b851f;
  }
code_r0x021e9654:
  *(undefined2 *)((long)param_1 + 0xeac) = 0;
  param_1[0x1c9] = 0;
  *(undefined4 *)(param_1 + 0x1d5) = 0;
  param_1[0x1c7] = 0x3f800000447a0000;
  *(undefined4 *)(param_1 + 0x1c8) = 0xffffffff;
  *(undefined4 *)(param_1 + 0x1cd) = 0x3eb33333;
  return;
}

// ==== Aska::FilterTextureObject::DoesInsertToPaintingList(Aska::RenderableObject::IPL*, int, int, int const*)
// vaddr 0x212f0c4 | ghidra 0x222f0c4 | size 228 | symbol _ZN4Aska19FilterTextureObject24DoesInsertToPaintingListEPNS_16RenderableObject3IPLEiiPKi | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska19FilterTextureObject24DoesInsertToPaintingListEPNS_16RenderableObject3IPLEiiPKi
          (long param_1,undefined1 *param_2,undefined8 param_3,uint param_4,long param_5)

{
  byte bVar1;
  bool bVar2;
  ulong uVar3;
  ulong uVar4;
  long lVar5;
  
  lVar5 = *(long *)PTR__ZN4Aska6Global16m_pObjectManagerE_02cc4688;
  uVar3 = *(ulong *)(lVar5 + ((long)((ulong)param_4 << 0x20) >> 0x26) * 8 + 0x45a0);
  uVar4 = 1L << ((long)(int)param_4 & 0x3fU);
  bVar1 = *(byte *)(*(long *)(lVar5 + 0x4478) + (ulong)*(byte *)(param_1 + 0x1b7) + 0x10);
  bVar2 = (uVar3 & uVar4) != 0;
  if ((ulong)*(byte *)(param_1 + 0x1b7) == 0x11) {
    bVar2 = (uVar3 & uVar4) != 0 ||
            0 < *(int *)(param_5 + (ulong)*(byte *)(*(long *)(lVar5 + 0x4478) + 0x2b) * 4);
  }
  bVar2 = (bool)(bVar2 | 0 < *(int *)(param_5 + (ulong)bVar1 * 4));
  if (param_4 == 0) {
    if (bVar2) {
      void Aska::FrameTextureEntities::AddEntry<true>(int, int)(param_1 + 0x308,0);
      *param_2 = 1;
      param_2[1] = *(undefined1 *)(lVar5 + 0x3f1c);
      return 1;
    }
  }
  else if (bVar2) {
    void Aska::FrameTextureEntities::AddEntry<true>(int, int)(param_1 + 0x308,param_4);
    *param_2 = 1;
    param_2[1] = bVar1;
    return 1;
  }
  return 0;
}

// ==== Aska::Light::Light()
// vaddr 0x213a4ac | ghidra 0x223a4ac | size 556 | symbol _ZN4Aska5LightC2Ev | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska5LightC1Ev(long *param_1)

{
  uint3 *puVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  long lVar5;
  long lVar6;
  long lVar7;
  long lVar8;
  float fVar9;
  undefined *puVar10;
  
  Aska::AimingObject::AimingObject()();
  *(undefined1 *)((long)param_1 + 0x1f5) = 0;
  lVar6 = _UNK_027dbb28;
  lVar5 = _UNK_027dbb20;
  *param_1 = (long)(PTR__ZTVN4Aska5LightE_02cc3a30 + 0x10);
  *(undefined4 *)(param_1 + 0x46) = 0x3f800000;
  param_1[0x43] = lVar6;
  param_1[0x42] = lVar5;
  *(undefined8 *)((long)param_1 + 0x234) = 0x3f8000003f800000;
  lVar6 = _UNK_028c0b98;
  lVar5 = _UNK_028c0b90;
  puVar1 = (uint3 *)((long)param_1 + 0x2a5);
  *(undefined4 *)(param_1 + 0x54) = 0xff000000;
  param_1[0x51] = 0;
  param_1[0x50] = 0;
  lVar8 = _UNK_029cc0b8;
  lVar7 = _UNK_029cc0b0;
  param_1[0x56] = lVar6;
  param_1[0x55] = lVar5;
  lVar6 = _UNK_029cc0c8;
  lVar5 = _UNK_029cc0c0;
  param_1[0x57] = 0x44fa000044fa0000;
  *(undefined4 *)((long)param_1 + 0x23c) = 0x42c80000;
  param_1[0x59] = lVar8;
  param_1[0x58] = lVar7;
  *(undefined4 *)((long)param_1 + 0x30c) = 0;
  *(ushort *)puVar1 = *(ushort *)puVar1 & 0xffb0 | 1;
  param_1[0x5b] = lVar6;
  param_1[0x5a] = lVar5;
  *(undefined4 *)(param_1 + 0x5c) = 0x41a007ce;
  Aska::Light::CalcAttenuation()(param_1);
  lVar6 = _UNK_027dbb38;
  lVar5 = _UNK_027dbb30;
  *(int *)(param_1 + 0x49) = (int)param_1[0x47];
  *(int *)(param_1 + 0x48) = (int)param_1[0x46];
  *(undefined4 *)((long)param_1 + 0x244) = *(undefined4 *)((long)param_1 + 0x234);
  *(undefined4 *)((long)param_1 + 0x24c) = *(undefined4 *)((long)param_1 + 0x23c);
  param_1[0x4b] = lVar6;
  param_1[0x4a] = lVar5;
  param_1[0x4d] = lVar6;
  param_1[0x4c] = lVar5;
  param_1[0x4f] = lVar6;
  param_1[0x4e] = lVar5;
  *(undefined8 *)((long)param_1 + 0x304) = 0x3fb8aa3b40000000;
  lVar6 = _UNK_027dbb08;
  lVar5 = _UNK_027dbb00;
  *(undefined4 *)(param_1 + 0x72) = 0;
  *(undefined8 *)((long)param_1 + 0x394) = 0;
  param_1[0x6d] = 0;
  param_1[0x6c] = 0;
  param_1[0x6f] = 0;
  param_1[0x6e] = 0;
  param_1[0x69] = 0;
  param_1[0x68] = 0;
  param_1[0x6b] = 0;
  param_1[0x6a] = 0;
  *(undefined4 *)((long)param_1 + 0x39c) = 0x3f800000;
  *(undefined4 *)(param_1 + 0x76) = 0x3f800000;
  *(undefined8 *)((long)param_1 + 0x3bc) = 0;
  *(undefined8 *)((long)param_1 + 0x3b4) = 0;
  *(undefined4 *)((long)param_1 + 0x3c4) = 0x3f800000;
  param_1[0x7a] = 0;
  param_1[0x79] = 0;
  lVar8 = _UNK_027dbb18;
  lVar7 = _UNK_027dbb10;
  uVar2 = (undefined4)param_1[0x57];
  *(undefined4 *)(param_1 + 0x74) = uVar2;
  *(undefined4 *)((long)param_1 + 0x3a4) = uVar2;
  *(undefined4 *)(param_1 + 0x75) = uVar2;
  param_1[0x7c] = lVar6;
  param_1[0x7b] = lVar5;
  param_1[0x7e] = lVar8;
  param_1[0x7d] = lVar7;
  lVar6 = _UNK_029cc0d8;
  lVar5 = _UNK_029cc0d0;
  param_1[0x7f] = 0x3f80000000000000;
  puVar10 = PTR__ZN4Aska26g_uiLowPrecisionRandomSeedE_02cbb068;
  *(undefined4 *)((long)param_1 + 0x2e4) = 0x40168;
  param_1[0x70] = 0;
  param_1[0x82] = 0;
  param_1[0x81] = 0;
  param_1[0x80] = 0;
  *(char *)((long)param_1 + 0x2a7) = (char)((*puVar1 & 0xfe807f) >> 0x10);
  *(ushort *)puVar1 = (ushort)(*puVar1 & 0xfe807f) | 0x80;
  param_1[0x5f] = lVar6;
  param_1[0x5e] = lVar5;
  fVar9 = _UNK_028014f8;
  iVar3 = *(int *)puVar10 * 0x19660d + 0x3c6ef35f;
  uVar4 = iVar3 * 0x19660d + 0x3c6ef35f;
  *(byte *)(param_1 + 0x5d) = (byte)iVar3 & 3;
  *(uint *)puVar10 = uVar4;
  param_1[0x83] = 0;
  *(undefined4 *)(param_1 + 0x84) = 0;
  *(float *)((long)param_1 + 0x2ec) = ((float)(uVar4 & 0x7fffff | 0x3f800000) + -1.0) * fVar9;
  *(undefined1 *)((long)param_1 + 0x424) = 1;
  return;
}

// ==== Aska::RenderableObject::GetClassID(int) const
// vaddr 0x21696e4 | ghidra 0x22696e4 | size 92 | symbol _ZNK4Aska16RenderableObject10GetClassIDEi | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska16RenderableObject10GetClassIDEi(undefined8 param_1,int param_2)

{
  undefined8 uVar1;
  undefined8 uVar2;
  
  if (param_2 == 0) {
    return 0xf002f111f112;
  }
  if (param_2 == 1) {
    return 0xf000f002f111;
  }
  uVar2 = 0xf000f001;
  if (param_2 != 3) {
    uVar2 = 0xf000;
  }
  uVar1 = 0xf000f001f002;
  if (param_2 != 2) {
    uVar1 = uVar2;
  }
  return uVar1;
}

// ==== Aska::MSAAChangerObject::DoesInsertToPaintingList(Aska::RenderableObject::IPL*, int, int, int const*)
// vaddr 0x2169740 | ghidra 0x2269740 | size 52 | symbol _ZN4Aska17MSAAChangerObject24DoesInsertToPaintingListEPNS_16RenderableObject3IPLEiiPKi | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska17MSAAChangerObject24DoesInsertToPaintingListEPNS_16RenderableObject3IPLEiiPKi
          (long param_1,undefined1 *param_2)

{
  undefined1 uVar1;
  long lVar2;
  
  lVar2 = *(long *)PTR__ZN4Aska6Global16m_pObjectManagerE_02cc4688;
  uVar1 = 1;
  if (*(char *)(param_1 + 0x309) == '\0') {
    uVar1 = 2;
  }
  *param_2 = uVar1;
  param_2[1] = *(undefined1 *)(*(long *)(lVar2 + 0x4478) + 0x1e);
  return 1;
}

// ==== Aska::RenderableObject::Render(Aska::RenderContext*, int)
// vaddr 0x21a996c | ghidra 0x22a996c | size 4 | symbol _ZN4Aska16RenderableObject6RenderEPNS_13RenderContextEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16RenderableObject6RenderEPNS_13RenderContextEi(void)

{
  return;
}

// ==== Aska::PostProcessBufferManager::DoesInsertToPaintingList(Aska::RenderableObject::IPL*, int, int, int const*)
// vaddr 0x21aa828 | ghidra 0x22aa828 | size 100 | symbol _ZN4Aska24PostProcessBufferManager24DoesInsertToPaintingListEPNS_16RenderableObject3IPLEiiPKi | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska24PostProcessBufferManager24DoesInsertToPaintingListEPNS_16RenderableObject3IPLEiiPKi
          (long param_1,undefined1 *param_2,undefined8 param_3,uint param_4)

{
  undefined1 uVar1;
  
  if (*(byte *)(param_1 + 0x43c) != param_4) {
    return 0;
  }
  if ((0 < (int)param_4) &&
     (((*(ushort *)
         (*(long *)PTR__ZN4Aska6Global16m_pObjectManagerE_02cc4688 + (long)(int)param_4 * 0x48 +
         0x45ea) ^ 0xffff) & 0x84) != 0)) {
    return 0;
  }
  uVar1 = *(undefined1 *)
           (*(long *)(*(long *)PTR__ZN4Aska6Global16m_pObjectManagerE_02cc4688 + 0x4478) + 0x25);
  *param_2 = 1;
  param_2[1] = uVar1;
  return 1;
}

// ==== Aska::RenderableObject::GetDeepestZ(int) const
// vaddr 0x21b6a98 | ghidra 0x22b6a98 | size 36 | symbol _ZNK4Aska16RenderableObject11GetDeepestZEi | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK4Aska16RenderableObject11GetDeepestZEi(long param_1,int param_2)

{
  return *(undefined4 *)
          (*(long *)(*(long *)PTR__ZN4Aska6Global16m_pObjectManagerE_02cc4688 + (long)param_2 * 8 +
                    0x3f48) + (ulong)*(ushort *)(param_1 + 0x1b8) * 8);
}

// ==== Aska::RenderableObject::GetShallowestZ(int) const
// vaddr 0x21b6abc | ghidra 0x22b6abc | size 36 | symbol _ZNK4Aska16RenderableObject14GetShallowestZEi | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK4Aska16RenderableObject14GetShallowestZEi(long param_1,int param_2)

{
  return *(undefined4 *)
          (*(long *)(*(long *)PTR__ZN4Aska6Global16m_pObjectManagerE_02cc4688 + (long)param_2 * 8 +
                    0x3f48) + (ulong)*(ushort *)(param_1 + 0x1b8) * 8 + 4);
}

// ==== Aska::RenderableObject::RenderableObject()
// vaddr 0x21b6ae0 | ghidra 0x22b6ae0 | size 476 | symbol _ZN4Aska16RenderableObjectC2Ev | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska16RenderableObjectC1Ev(long *param_1)

{
  undefined *puVar1;
  byte bVar2;
  byte bVar3;
  long lVar4;
  long lVar5;
  undefined4 uVar6;
  code *pcVar7;
  long *plVar8;
  long *plVar9;
  long *plVar10;
  undefined1 auVar11 [16];
  
  pcVar7 = *(code **)(PTR__ZTVN4Aska4TaskE_02cbe020 + 0x68);
  *param_1 = (long)(PTR__ZTVN4Aska4TaskE_02cbe020 + 0x10);
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  *(undefined2 *)((long)param_1 + 0x24) = 0;
  *(undefined1 *)((long)param_1 + 0x26) = 0;
  uVar6 = (*pcVar7)();
  *(undefined4 *)(param_1 + 4) = uVar6;
  puVar1 = PTR__ZTVN4Aska27HierarchicalObjectContainerE_02cb81a8;
  *param_1 = (long)(PTR__ZTVN4Aska18HierarchicalObjectE_02cb6bb0 + 0x10);
  plVar8 = param_1 + 6;
  *plVar8 = (long)(puVar1 + 0x10);
  *(undefined4 *)(param_1 + 0x14) = 0x3f800000;
  *(undefined4 *)((long)param_1 + 0xac) = 0x3f800000;
  lVar5 = _UNK_027dbb38;
  lVar4 = _UNK_027dbb30;
  bVar2 = *(byte *)(param_1 + 0x25);
  bVar3 = *(byte *)((long)param_1 + 0x129);
  *(byte *)((long)param_1 + 0x129) = bVar3 & 0xfc;
  *(undefined8 *)((long)param_1 + 0xa4) = 0x3f8000003f800000;
  param_1[0x11] = lVar5;
  param_1[0x10] = lVar4;
  param_1[0x13] = lVar5;
  param_1[0x12] = lVar4;
  *(byte *)(param_1 + 0x25) = bVar2 & 0xde | 1;
  plVar9 = param_1 + 0x18;
  do {
    plVar10 = (long *)((long)plVar9 + 0x7fU & 0xffffffffffffff81);
    Hint_Prefetch(plVar9,0,2,0);
    plVar9 = plVar10;
  } while (plVar10 < param_1 + 0x1a);
  param_1[0x1b] = lVar5;
  param_1[0x1a] = lVar4;
  param_1[0x1d] = lVar5;
  param_1[0x1c] = lVar4;
  param_1[0x17] = lVar5;
  param_1[0x16] = lVar4;
  *(undefined4 *)(param_1 + 0x18) = 0;
  *(undefined8 *)((long)param_1 + 0xc4) = 0;
  param_1[0x20] = (long)plVar8;
  param_1[0x21] = (long)plVar8;
  param_1[5] = 0;
  *(byte *)((long)param_1 + 0x129) = bVar3 & 0xf8;
  param_1[0x30] = 0;
  *(undefined4 *)(param_1 + 0x32) = 0;
  *(undefined1 *)((long)param_1 + 0x197) = 0;
  *(undefined4 *)((long)param_1 + 0xcc) = 0x3f800000;
  puVar1 = PTR__ZTVN4Aska16RenderableObjectE_02cc01e8 + 0x10;
  param_1[0x24] = (long)(param_1 + 8);
  param_1[0x1f] = 0;
  param_1[0x1e] = 0;
  param_1[0x23] = 0;
  param_1[0x22] = 0;
  *(undefined2 *)((long)param_1 + 0x194) = 1;
  param_1[0x23] = (long)param_1;
  *param_1 = (long)puVar1;
  *(undefined1 *)(param_1 + 0x49) = 1;
  auVar11 = NEON_fmov(0x3f800000,4);
  *(byte *)(param_1 + 0x25) = bVar2 & 200 | 1;
  param_1[0x3c] = 0;
  param_1[0x4d] = 0;
  param_1[0x4f] = auVar11._8_8_;
  param_1[0x4e] = auVar11._0_8_;
  param_1[0x4c] = 0;
  *(undefined4 *)(param_1 + 0x33) = 0;
  *(undefined4 *)(param_1 + 0x36) = 0;
  *(undefined4 *)(param_1 + 0x38) = 0;
  param_1[0x34] = 0;
  *(undefined1 *)(param_1 + 0x5e) = 0;
  param_1[0x48] = 0;
  param_1[0x47] = 0;
  param_1[0x46] = 0;
  param_1[0x51] = 0;
  param_1[0x50] = 0;
  *(ushort *)((long)param_1 + 0x1b5) = *(ushort *)((long)param_1 + 0x1b5) & 0xff02 | 0x40;
  lVar5 = _UNK_029d1a78;
  lVar4 = _UNK_029d1a70;
  *(undefined1 *)((long)param_1 + 0x1b4) = 0;
  param_1[0x44] = 0;
  param_1[0x43] = 0;
  param_1[0x42] = 0;
  param_1[0x41] = 0;
  *(undefined1 *)((long)param_1 + 0x1b7) = 3;
  param_1[0x3b] = 0;
  param_1[0x5d] = lVar5;
  param_1[0x5c] = lVar4;
  param_1[0x31] = 0;
  param_1[0x45] = 0;
  *(undefined4 *)((long)param_1 + 0x2f4) = 0;
  *(undefined4 *)(param_1 + 0x5f) = 0x3f490fdb;
  *(undefined4 *)((long)param_1 + 0x2fc) = 0x3ec90fdb;
  param_1[0x60] = 0;
  *(undefined4 *)((long)param_1 + 0x1c4) = 0;
  *(undefined4 *)(param_1 + 0x39) = 0;
  return;
}

// ==== Aska::RenderableObject::~RenderableObject()
// vaddr 0x21b6cbc | ghidra 0x22b6cbc | size 4 | symbol _ZN4Aska16RenderableObjectD1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16RenderableObjectD2Ev(void)

{
  (*(code *)PTR__ZN4Aska18HierarchicalObjectD2Ev_02ca75e8)();
  return;
}

// ==== Aska::RenderableObject::~RenderableObject()
// vaddr 0x21b6cc0 | ghidra 0x22b6cc0 | size 24 | symbol _ZN4Aska16RenderableObjectD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16RenderableObjectD0Ev(undefined8 param_1)

{
  Aska::HierarchicalObject::~HierarchicalObject()();
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::RenderableObject::Clone(Aska::IAnimatable const*)
// vaddr 0x21b6cd8 | ghidra 0x22b6cd8 | size 336 | symbol _ZN4Aska16RenderableObject5CloneEPKNS_11IAnimatableE | lib libSOA-3.7.0.so | 2026-10-04
bool _ZN4Aska16RenderableObject5CloneEPKNS_11IAnimatableE(long param_1,long param_2)

{
  ushort *puVar1;
  ushort *puVar2;
  ushort uVar3;
  bool bVar4;
  ushort uVar5;
  ulong uVar6;
  
  uVar6 = Aska::HierarchicalObject::Clone(Aska::IAnimatable const*)();
  bVar4 = (uVar6 & 1) != 0;
  if (bVar4) {
    *(long *)(param_1 + 0x1d8) = param_2;
    puVar1 = (ushort *)(param_2 + 0x1b5);
    puVar2 = (ushort *)(param_1 + 0x1b5);
    *(undefined4 *)(param_1 + 0x198) = *(undefined4 *)(param_2 + 0x198);
    *(undefined4 *)(param_1 + 0x1b0) = *(undefined4 *)(param_2 + 0x1b0);
    uVar5 = *puVar2;
    uVar3 = uVar5 & 0xf | (*puVar1 >> 4 & 1) << 4;
    *puVar2 = uVar5 & 0xffe0 | uVar3;
    uVar3 = uVar3 | (*puVar1 >> 5 & 1) << 5;
    *puVar2 = uVar5 & 0xffc0 | uVar3;
    *puVar2 = uVar5 & 0xff40 | uVar3 | *puVar1 & 0x80;
    *(undefined8 *)(param_1 + 0x208) = *(undefined8 *)(param_2 + 0x208);
    *(undefined8 *)(param_1 + 0x210) = *(undefined8 *)(param_2 + 0x210);
    *(undefined8 *)(param_1 + 0x218) = *(undefined8 *)(param_2 + 0x218);
    *(undefined8 *)(param_1 + 0x220) = *(undefined8 *)(param_2 + 0x220);
    *(undefined8 *)(param_1 + 0x1f8) = *(undefined8 *)(param_2 + 0x1f8);
    *(undefined8 *)(param_1 + 0x200) = *(undefined8 *)(param_2 + 0x200);
    *(undefined1 *)(param_1 + 0x1b4) = *(undefined1 *)(param_2 + 0x1b4);
    *(undefined1 *)(param_1 + 0x1b7) = *(undefined1 *)(param_2 + 0x1b7);
    *(undefined8 *)(param_1 + 0x1a0) = *(undefined8 *)(param_2 + 0x1a0);
    *(undefined4 *)(param_1 + 0x270) = *(undefined4 *)(param_2 + 0x270);
    *(undefined4 *)(param_1 + 0x274) = *(undefined4 *)(param_2 + 0x274);
    *(undefined4 *)(param_1 + 0x278) = *(undefined4 *)(param_2 + 0x278);
    *(undefined4 *)(param_1 + 0x27c) = *(undefined4 *)(param_2 + 0x27c);
    *(undefined4 *)(param_1 + 0x280) = *(undefined4 *)(param_2 + 0x280);
    *(undefined4 *)(param_1 + 0x284) = *(undefined4 *)(param_2 + 0x284);
    *(undefined4 *)(param_1 + 0x288) = *(undefined4 *)(param_2 + 0x288);
    *(undefined4 *)(param_1 + 0x28c) = *(undefined4 *)(param_2 + 0x28c);
    *(undefined8 *)(param_1 + 0x260) = *(undefined8 *)(param_2 + 0x260);
    *(undefined8 *)(param_1 + 0x268) = *(undefined8 *)(param_2 + 0x268);
    *(undefined4 *)(param_1 + 0x2e0) = *(undefined4 *)(param_2 + 0x2e0);
    *(undefined4 *)(param_1 + 0x2e4) = *(undefined4 *)(param_2 + 0x2e4);
    *(undefined4 *)(param_1 + 0x2e8) = *(undefined4 *)(param_2 + 0x2e8);
    *(undefined4 *)(param_1 + 0x2ec) = *(undefined4 *)(param_2 + 0x2ec);
    *(undefined1 *)(param_1 + 0x248) = *(undefined1 *)(param_2 + 0x248);
    *(undefined1 *)(param_1 + 0x2f0) = *(undefined1 *)(param_2 + 0x2f0);
  }
  return bVar4;
}

// ==== Aska::RenderableObject::CreateClone(Aska::IAnimatable const*)
// vaddr 0x21b6e28 | ghidra 0x22b6e28 | size 104 | symbol _ZN4Aska16RenderableObject11CreateCloneEPKNS_11IAnimatableE | lib libSOA-3.7.0.so | 2026-10-04
long * _ZN4Aska16RenderableObject11CreateCloneEPKNS_11IAnimatableE
                 (undefined8 param_1,undefined8 param_2)

{
  long *plVar1;
  ulong uVar2;
  
  plVar1 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x310,PTR__ZSt7nothrow_02cb9a80);
  if (plVar1 != (long *)0x0) {
    Aska::RenderableObject::RenderableObject()(plVar1);
    uVar2 = (**(code **)(*plVar1 + 0x18))(plVar1,param_2);
    if ((uVar2 & 1) == 0) {
      (**(code **)(*plVar1 + 8))(plVar1);
      plVar1 = (long *)0x0;
    }
  }
  return plVar1;
}

// ==== Aska::RenderableObject::SetMultipassRenderingID(unsigned long const*, int)
// vaddr 0x21b6e90 | ghidra 0x22b6e90 | size 52 | symbol _ZN4Aska16RenderableObject23SetMultipassRenderingIDEPKmi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16RenderableObject23SetMultipassRenderingIDEPKmi(long param_1,long param_2,int param_3)

{
  long lVar1;
  long lVar2;
  long lVar3;
  
  if (0 < param_3) {
    lVar2 = 0;
    lVar1 = 1;
    if (param_3 != 1) {
      lVar1 = 2;
    }
    do {
      lVar3 = lVar2 * 8;
      lVar2 = lVar2 + 1;
      *(undefined8 *)(param_1 + 0x208 + lVar3) = *(undefined8 *)(param_2 + lVar3);
    } while (lVar2 < lVar1);
  }
  return;
}

// ==== Aska::RenderableObject::SetMultipassRequestRenderingID(unsigned long const*, int)
// vaddr 0x21b6ec4 | ghidra 0x22b6ec4 | size 52 | symbol _ZN4Aska16RenderableObject30SetMultipassRequestRenderingIDEPKmi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16RenderableObject30SetMultipassRequestRenderingIDEPKmi
               (long param_1,long param_2,int param_3)

{
  long lVar1;
  long lVar2;
  long lVar3;
  
  if (0 < param_3) {
    lVar2 = 0;
    lVar1 = 1;
    if (param_3 != 1) {
      lVar1 = 2;
    }
    do {
      lVar3 = lVar2 * 8;
      lVar2 = lVar2 + 1;
      *(undefined8 *)(param_1 + 0x218 + lVar3) = *(undefined8 *)(param_2 + lVar3);
    } while (lVar2 < lVar1);
  }
  return;
}

// ==== Aska::RenderableObject::PreliminarilyPrepare(Aska::LightManager*)
// vaddr 0x21b6ef8 | ghidra 0x22b6ef8 | size 8 | symbol _ZN4Aska16RenderableObject20PreliminarilyPrepareEPNS_12LightManagerE | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska16RenderableObject20PreliminarilyPrepareEPNS_12LightManagerE(void)

{
  return 0;
}

// ==== Aska::RenderableObject::PrepareForRendering(Aska::RENDERINFO const*)
// vaddr 0x21b6f00 | ghidra 0x22b6f00 | size 8 | symbol _ZN4Aska16RenderableObject19PrepareForRenderingEPKNS_10RENDERINFOE | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska16RenderableObject19PrepareForRenderingEPKNS_10RENDERINFOE(void)

{
  return 0;
}

// ==== Aska::RenderableObject::CheckSleepAvailability()
// vaddr 0x21b6f08 | ghidra 0x22b6f08 | size 20 | symbol _ZN4Aska16RenderableObject22CheckSleepAvailabilityEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska16RenderableObject22CheckSleepAvailabilityEv(long param_1)

{
  undefined8 uVar1;
  
  if ((*(byte *)(param_1 + 0x19a) >> 1 & 1) == 0) {
    uVar1 = (*(code *)PTR__ZN4Aska18HierarchicalObject22CheckSleepAvailabilityEv_02c948b0)();
    return uVar1;
  }
  return 0;
}

// ==== Aska::RenderableObject::SetAppropriateTaskLevel()
// vaddr 0x21b6f1c | ghidra 0x22b6f1c | size 20 | symbol _ZN4Aska16RenderableObject23SetAppropriateTaskLevelEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16RenderableObject23SetAppropriateTaskLevelEv(long param_1)

{
  if ((*(byte *)(param_1 + 0x19a) >> 1 & 1) == 0) {
    (*(code *)PTR__ZN4Aska18HierarchicalObject23SetAppropriateTaskLevelEv_02ca3368)();
    return;
  }
  (*(code *)PTR__ZN4Aska4Task11ChangeLevelEj_02cad070)(param_1,0x4000);
  return;
}

// ==== Aska::RenderableObject::InitializeConditions()
// vaddr 0x21b6f30 | ghidra 0x22b6f30 | size 164 | symbol _ZN4Aska16RenderableObject20InitializeConditionsEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16RenderableObject20InitializeConditionsEv(long *param_1)

{
  long *plVar1;
  
  Aska::HierarchicalObject::InitializeConditions()();
  if (((*(byte *)((long)param_1 + 0x19a) >> 1 & 1) != 0) &&
     ((plVar1 = (long *)param_1[0x34], plVar1 != (long *)0x0 ||
      (plVar1 = *(long **)(*(long *)PTR__ZN4Aska6Global16m_pCameraManagerE_02cb7d08 + 0xff0),
      plVar1 != (long *)0x0)))) {
    if ((*(byte *)(plVar1 + 0x25) & 1) != 0) {
      (**(code **)(*plVar1 + 0xa8))(plVar1);
    }
    (**(code **)(*param_1 + 200))
              (*(undefined4 *)((long)plVar1 + 0x4c),*(undefined4 *)((long)param_1 + 0x84),
               *(undefined4 *)((long)plVar1 + 0x6c),param_1);
  }
  if (((*(uint *)(param_1 + 0x36) & 7) != 0) ||
     (((*(uint *)(param_1 + 0x36) & 0x600) != 0 && ((*(byte *)(param_1 + 0x32) & 0x1c) != 0)))) {
    *(uint *)(param_1 + 0x33) = *(uint *)(param_1 + 0x33) | 0x200;
  }
  return;
}

// ==== Aska::RenderableObject::ProcFarObject()
// vaddr 0x21b6fd4 | ghidra 0x22b6fd4 | size 112 | symbol _ZN4Aska16RenderableObject13ProcFarObjectEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16RenderableObject13ProcFarObjectEv(long *param_1)

{
  long *plVar1;
  
  plVar1 = (long *)param_1[0x34];
  if ((plVar1 == (long *)0x0) &&
     (plVar1 = *(long **)(*(long *)PTR__ZN4Aska6Global16m_pCameraManagerE_02cb7d08 + 0xff0),
     plVar1 == (long *)0x0)) {
    return;
  }
  if ((*(byte *)(plVar1 + 0x25) & 1) != 0) {
    (**(code **)(*plVar1 + 0xa8))(plVar1);
  }
                    /* WARNING: Could not recover jumptable at 0x022b7034. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*param_1 + 200))
            (*(undefined4 *)((long)plVar1 + 0x4c),*(undefined4 *)((long)param_1 + 0x84),
             *(undefined4 *)((long)plVar1 + 0x6c),param_1);
  return;
}

// ==== Aska::RenderableObject::MakeBillboardMatrix(Aska::Camera*)
// vaddr 0x21b7044 | ghidra 0x22b7044 | size 1928 | symbol _ZN4Aska16RenderableObject19MakeBillboardMatrixEPNS_6CameraE | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

long * _ZN4Aska16RenderableObject19MakeBillboardMatrixEPNS_6CameraE(long *param_1,long *param_2)

{
  uint uVar1;
  bool bVar2;
  long lVar3;
  long *plVar4;
  float *pfVar5;
  float *pfVar6;
  undefined8 *puVar7;
  undefined8 uVar8;
  byte bVar9;
  float fVar10;
  long lVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  undefined8 uVar18;
  undefined8 uVar19;
  float fVar20;
  undefined8 uVar21;
  undefined8 uVar22;
  float fVar23;
  undefined8 uVar24;
  float fVar25;
  float fVar26;
  float fVar27;
  float fVar28;
  float fStack_140;
  float fStack_13c;
  float fStack_138;
  float fStack_134;
  float fStack_130;
  float fStack_12c;
  float fStack_128;
  undefined4 uStack_124;
  undefined8 uStack_120;
  long lStack_118;
  undefined8 uStack_110;
  long lStack_108;
  undefined8 uStack_100;
  float fStack_f8;
  float fStack_f4;
  undefined8 uStack_f0;
  undefined8 uStack_e8;
  undefined8 uStack_e0;
  undefined8 uStack_d8;
  undefined8 uStack_d0;
  undefined8 uStack_c8;
  undefined8 uStack_c0;
  undefined8 uStack_b8;
  undefined8 uStack_b0;
  undefined8 uStack_a8;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  float fStack_94;
  float fStack_90;
  float fStack_8c;
  float fStack_88;
  
  if ((long *)param_1[0x31] == param_2) goto code_r0x022b7784;
  uVar1 = *(uint *)(param_1 + 0x36);
  param_1[0x31] = (long)param_2;
  if ((*(byte *)((long)param_1 + 0x129) >> 2 & 1) == 0) {
    plVar4 = (long *)(**(code **)(*param_1 + 0x98))(param_1);
    lVar11 = *plVar4;
    param_1[0x53] = plVar4[1];
    param_1[0x52] = lVar11;
    lVar11 = plVar4[2];
    param_1[0x55] = plVar4[3];
    param_1[0x54] = lVar11;
    lVar11 = plVar4[4];
    param_1[0x57] = plVar4[5];
    param_1[0x56] = lVar11;
    lVar11 = plVar4[6];
    param_1[0x59] = plVar4[7];
    param_1[0x58] = lVar11;
    if ((~uVar1 & 7) == 0) {
      pfVar5 = (float *)Aska::HierarchicalObject::EstimateScaleStat()(param_1);
      pfVar6 = (float *)Aska::HierarchicalObject::EstimateScaleStat()(param_2);
      fVar25 = *pfVar5 / *pfVar6;
      fVar27 = pfVar5[1] / pfVar6[1];
      fVar28 = pfVar5[2] / pfVar6[2];
      pfVar5 = (float *)(**(code **)(*param_2 + 0x98))(param_2);
      *(float *)(param_1 + 0x52) = fVar25 * *pfVar5;
      *(float *)(param_1 + 0x54) = fVar25 * pfVar5[4];
      *(float *)(param_1 + 0x56) = fVar25 * pfVar5[8];
      *(float *)((long)param_1 + 0x294) = fVar27 * pfVar5[1];
      *(float *)((long)param_1 + 0x2a4) = fVar27 * pfVar5[5];
      *(float *)((long)param_1 + 0x2b4) = fVar27 * pfVar5[9];
      *(float *)(param_1 + 0x53) = fVar28 * pfVar5[2];
      *(float *)(param_1 + 0x55) = fVar28 * pfVar5[6];
      *(float *)(param_1 + 0x57) = fVar28 * pfVar5[10];
    }
    else {
      fVar25 = *(float *)(param_2 + 0x12a);
      fVar27 = *(float *)((long)param_2 + 0x954);
      fVar28 = *(float *)(param_2 + 299);
      puVar7 = (undefined8 *)(**(code **)(*param_1 + 0x98))(param_1);
      uVar18 = puVar7[1];
      uVar8 = *puVar7;
      uVar21 = puVar7[3];
      uVar19 = puVar7[2];
      uVar24 = puVar7[5];
      uVar22 = puVar7[4];
      fVar13 = (float)uVar8;
      fVar14 = (float)uVar19;
      uStack_a8 = puVar7[7];
      uStack_b0 = puVar7[6];
      fVar15 = (float)uVar22;
      fVar26 = SQRT(fVar13 * fVar13 + fVar14 * fVar14 + fVar15 * fVar15);
      uStack_e0 = uVar8;
      uStack_d8 = uVar18;
      uStack_d0 = uVar19;
      uStack_c8 = uVar21;
      uStack_c0 = uVar22;
      uStack_b8 = uVar24;
      if (NAN(fVar26)) {
        fVar26 = (float)sqrtf();
      }
      fVar17 = (float)((ulong)uVar8 >> 0x20);
      fVar20 = (float)((ulong)uVar19 >> 0x20);
      fVar23 = (float)((ulong)uVar22 >> 0x20);
      fVar12 = SQRT(fVar17 * fVar17 + fVar20 * fVar20 + fVar23 * fVar23);
      if (NAN(fVar12)) {
        fVar12 = (float)sqrtf();
      }
      fVar16 = (float)uVar18 * (float)uVar18 + (float)uVar21 * (float)uVar21 +
               (float)uVar24 * (float)uVar24;
      fVar10 = SQRT(fVar16);
      fVar26 = 1.0 / fVar26;
      fVar12 = 1.0 / fVar12;
      if (NAN(fVar10)) {
        fVar10 = (float)sqrtf(fVar16);
      }
      uStack_e0 = CONCAT44(fVar12 * fVar17,fVar26 * fVar13);
      fVar10 = 1.0 / fVar10;
      uStack_d8 = CONCAT44(uStack_d8._4_4_,fVar10 * (float)uStack_d8);
      uStack_c8 = CONCAT44(uStack_c8._4_4_,fVar10 * (float)uStack_c8);
      uStack_d0 = CONCAT44(fVar12 * fVar20,fVar26 * fVar14);
      uStack_c0 = CONCAT44(fVar12 * fVar23,fVar26 * fVar15);
      uStack_b8 = CONCAT44(uStack_b8._4_4_,fVar10 * (float)uStack_b8);
      Aska::Quaternion::Create(Aska::Matrix const*)(&fStack_a0,&uStack_e0);
      Aska::Quaternion::CalcEuler(Aska::Vector*, EnumRotateType) const(&fStack_a0,&fStack_90,4);
      if ((uVar1 & 1) == 0) {
        fVar25 = fStack_90;
      }
      fStack_90 = fVar25;
      if ((uVar1 >> 1 & 1) == 0) {
        fVar27 = fStack_8c;
      }
      fStack_8c = fVar27;
      if ((uVar1 >> 2 & 1) != 0) {
        fStack_88 = fVar28;
      }
      Aska::Matrix::SetRotation(Aska::Vector const*, EnumRotateType)(&uStack_120,&fStack_90,4);
      pfVar5 = (float *)Aska::HierarchicalObject::EstimateScaleStat()(param_1);
      *(float *)(param_1 + 0x52) = (float)uStack_120 * *pfVar5;
      *(float *)(param_1 + 0x54) = (float)uStack_110 * *pfVar5;
      *(float *)(param_1 + 0x56) = (float)uStack_100 * *pfVar5;
      *(float *)((long)param_1 + 0x294) = uStack_120._4_4_ * pfVar5[1];
      *(float *)((long)param_1 + 0x2a4) = uStack_110._4_4_ * pfVar5[1];
      *(float *)((long)param_1 + 0x2b4) = uStack_100._4_4_ * pfVar5[1];
      *(float *)(param_1 + 0x53) = (float)lStack_118 * pfVar5[2];
      *(float *)(param_1 + 0x55) = (float)lStack_108 * pfVar5[2];
      *(float *)(param_1 + 0x57) = fStack_f8 * pfVar5[2];
    }
    goto code_r0x022b7784;
  }
  if ((param_1[0x1e] == 0) || (plVar4 = *(long **)(param_1[0x1e] + 0xe8), plVar4 == (long *)0x0)) {
    plVar4 = (long *)0x0;
    bVar2 = false;
code_r0x022b7250:
    Aska::Quaternion::CalcEuler(Aska::Vector*, EnumRotateType) const(param_1 + 0x12,&fStack_90,4);
    if ((uVar1 & 1) != 0) {
      fStack_90 = *(float *)(param_2 + 0x12a);
    }
    if ((uVar1 >> 1 & 1) != 0) {
      fStack_8c = *(float *)((long)param_2 + 0x954);
    }
    if ((uVar1 >> 2 & 1) != 0) {
      fStack_88 = *(float *)(param_2 + 299);
    }
  }
  else {
    if ((*(byte *)(plVar4 + 0x25) & 1) != 0) {
      (**(code **)(*plVar4 + 0xa8))(plVar4);
    }
    puVar7 = (undefined8 *)(**(code **)(*plVar4 + 0x98))(plVar4);
    lVar3 = _UNK_027dbb38;
    lVar11 = _UNK_027dbb30;
    fVar25 = (float)*puVar7;
    fVar13 = (float)((ulong)puVar7[2] >> 0x20);
    fVar17 = (float)puVar7[5];
    fVar27 = (float)((ulong)*puVar7 >> 0x20);
    fVar28 = (float)puVar7[1];
    fVar26 = (float)puVar7[2];
    fVar14 = (float)puVar7[3];
    fVar15 = (float)puVar7[4];
    fVar12 = (float)((ulong)puVar7[4] >> 0x20);
    if (ABS((fVar25 - fVar13) + (fVar25 - fVar17) +
            fVar12 + fVar15 + fVar14 + fVar26 + fVar27 + fVar28) <= 1e-06 &&
        (ABS((fVar25 - fVar13) + (fVar25 - fVar17) +
             fVar12 + fVar15 + fVar14 + fVar26 + fVar27 + fVar28) <= 1e-06 &&
        (ABS((fVar25 - fVar13) + (fVar25 - fVar17) +
             fVar12 + fVar15 + fVar14 + fVar26 + fVar27 + fVar28) <= 1e-06 &&
        ABS((fVar25 - fVar13) + (fVar25 - fVar17) +
            fVar12 + fVar15 + fVar14 + fVar26 + fVar27 + fVar28) <= 1e-06))) {
      bVar2 = true;
      goto code_r0x022b7250;
    }
    bVar9 = *(byte *)(plVar4 + 0x25);
    if ((bVar9 >> 2 & 1) == 0) {
      if ((*(byte *)((long)plVar4 + 0x129) & 3) == 0) {
        fVar25 = *(float *)((long)plVar4 + 0x4c);
        fVar27 = *(float *)((long)plVar4 + 0x5c);
        fVar28 = *(float *)((long)plVar4 + 0x6c);
        plVar4[0x27] = CONCAT44((int)plVar4[0xe],*(float *)(plVar4 + 0xc));
        plVar4[0x26] = CONCAT44(*(float *)(plVar4 + 10),*(float *)(plVar4 + 8));
        plVar4[0x29] = CONCAT44(*(undefined4 *)((long)plVar4 + 0x74),*(float *)((long)plVar4 + 100))
        ;
        plVar4[0x28] = CONCAT44(*(float *)((long)plVar4 + 0x54),*(float *)((long)plVar4 + 0x44));
        *(float *)((long)plVar4 + 0x13c) =
             -(*(float *)(plVar4 + 8) * fVar25 + *(float *)(plVar4 + 10) * fVar27 +
              *(float *)(plVar4 + 0xc) * fVar28);
        *(float *)((long)plVar4 + 0x14c) =
             -(fVar25 * *(float *)((long)plVar4 + 0x44) + fVar27 * *(float *)((long)plVar4 + 0x54) +
              fVar28 * *(float *)((long)plVar4 + 100));
        plVar4[0x2b] = CONCAT44((int)plVar4[0xf],*(float *)(plVar4 + 0xd));
        plVar4[0x2a] = CONCAT44(*(float *)(plVar4 + 0xb),*(float *)(plVar4 + 9));
        plVar4[0x2d] = lVar3;
        plVar4[0x2c] = lVar11;
        *(float *)((long)plVar4 + 0x15c) =
             -(fVar25 * *(float *)(plVar4 + 9) + fVar27 * *(float *)(plVar4 + 0xb) +
              fVar28 * *(float *)(plVar4 + 0xd));
      }
      else {
        Aska::Matrix::InvertLowError(Aska::Matrix*) const(plVar4 + 8,plVar4 + 0x26);
        bVar9 = *(byte *)(plVar4 + 0x25);
      }
      *(byte *)(plVar4 + 0x25) = bVar9 | 4;
    }
    uVar8 = (**(code **)(*param_2 + 0x98))(param_2);
    Aska::Matrix::Mul(Aska::Matrix const*, Aska::Matrix const*)(&uStack_e0,plVar4 + 0x26,uVar8);
    Aska::Quaternion::Create(Aska::Matrix const*)(&uStack_120,&uStack_e0);
    Aska::Quaternion::CalcEuler(Aska::Vector*, EnumRotateType) const(&uStack_120,&fStack_a0,4);
    Aska::Quaternion::CalcEuler(Aska::Vector*, EnumRotateType) const(param_1 + 0x12,&fStack_90,4);
    fVar25 = fStack_a0;
    if ((uVar1 & 1) == 0) {
      fVar25 = fStack_90;
    }
    fStack_90 = fVar25;
    if ((uVar1 >> 1 & 1) != 0) {
      fStack_8c = fStack_9c;
    }
    if ((uVar1 >> 2 & 1) != 0) {
      fStack_88 = fStack_98;
    }
    bVar2 = true;
  }
  Aska::Quaternion::CreateFromEuler(float, float, float, EnumRotateType)(fStack_90,fStack_8c,fStack_88,&fStack_a0,4);
  fStack_130 = *(float *)(param_1 + 0x10) + *(float *)(param_1 + 0x16);
  fStack_12c = *(float *)((long)param_1 + 0x84) + *(float *)((long)param_1 + 0xb4);
  uStack_124 = 0x3f800000;
  fStack_128 = *(float *)(param_1 + 0x11) + *(float *)(param_1 + 0x17);
  fVar25 = *(float *)(param_1 + 0x19);
  fVar27 = *(float *)((long)param_1 + 0xcc);
  fVar28 = *(float *)(param_1 + 0x18);
  fVar26 = *(float *)((long)param_1 + 0xc4);
  fStack_140 = (fVar27 * fStack_a0 + fVar28 * fStack_94 + fVar26 * fStack_98) - fVar25 * fStack_9c;
  fStack_13c = fStack_a0 * fVar25 + fStack_94 * fVar26 + (fVar27 * fStack_9c - fVar28 * fStack_98);
  fStack_138 = fStack_94 * fVar25 + ((fVar27 * fStack_98 + fVar28 * fStack_9c) - fStack_a0 * fVar26)
  ;
  fStack_134 = ((fVar27 * fStack_94 - fStack_a0 * fVar28) - fVar26 * fStack_9c) - fStack_98 * fVar25
  ;
  Aska::Matrix::Create(Aska::Quaternion const*, Aska::Vector const*)(&uStack_e0,&fStack_140,&fStack_130);
  uStack_100 = 0;
  uStack_f0 = 0;
  uStack_120 = (ulong)(uint)*(float *)(param_1 + 0x14);
  uStack_110 = (ulong)(uint)*(float *)((long)param_1 + 0xa4) << 0x20;
  uStack_e8 = 0x3f80000000000000;
  lStack_118 = (ulong)(uint)(*(float *)(param_1 + 0x1a) -
                            *(float *)(param_1 + 0x1c) * *(float *)(param_1 + 0x14)) << 0x20;
  lStack_108 = (ulong)(uint)(*(float *)((long)param_1 + 0xd4) -
                            *(float *)((long)param_1 + 0xe4) * *(float *)((long)param_1 + 0xa4)) <<
               0x20;
  _fStack_f8 = CONCAT44(*(float *)(param_1 + 0x1b) -
                        *(float *)(param_1 + 0x1d) * *(float *)(param_1 + 0x15),
                        *(float *)(param_1 + 0x15));
  Aska::Matrix::Mul(Aska::Matrix const*, Aska::Matrix const*)(param_1 + 0x52,&uStack_e0,&uStack_120);
  if (bVar2) {
    uVar8 = (**(code **)(*plVar4 + 0x98))(plVar4);
    Aska::Matrix::MulFromLeft(Aska::Matrix const*)(param_1 + 0x52,uVar8);
  }
code_r0x022b7784:
  return param_1 + 0x52;
}

// ==== Aska::RenderableObject::MakeBillboardMatrixFromLocalAxis(Aska::Camera*)
// vaddr 0x21b77cc | ghidra 0x22b77cc | size 88 | symbol _ZN4Aska16RenderableObject32MakeBillboardMatrixFromLocalAxisEPNS_6CameraE | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska16RenderableObject32MakeBillboardMatrixFromLocalAxisEPNS_6CameraE
               (long param_1,long param_2)

{
  int iVar1;
  
  if (*(long *)(param_1 + 0x188) != param_2) {
    *(long *)(param_1 + 0x188) = param_2;
    if ((~*(uint *)(param_1 + 0x1b0) & 0x600) == 0) {
      iVar1 = 0;
    }
    else {
      iVar1 = 2 - (*(uint *)(param_1 + 0x1b0) >> 9 & 1);
    }
    Aska::HierarchicalObject::MakeBillboardMatrixFromLocalAxis(Aska::HierarchicalObject*, Aska::Matrix*, Aska::HierarchicalObject::TargetFace)(param_1,param_2,param_1 + 0x290,iVar1);
  }
  return param_1 + 0x290;
}

// ==== Aska::RenderableObject::Run(int)
// vaddr 0x21b7824 | ghidra 0x22b7824 | size 124 | symbol _ZN4Aska16RenderableObject3RunEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16RenderableObject3RunEi(long *param_1,undefined4 param_2)

{
  long *plVar1;
  
  if (((*(byte *)((long)param_1 + 0x19a) >> 1 & 1) != 0) &&
     ((plVar1 = (long *)param_1[0x34], plVar1 != (long *)0x0 ||
      (plVar1 = *(long **)(*(long *)PTR__ZN4Aska6Global16m_pCameraManagerE_02cb7d08 + 0xff0),
      plVar1 != (long *)0x0)))) {
    if ((*(byte *)(plVar1 + 0x25) & 1) != 0) {
      (**(code **)(*plVar1 + 0xa8))(plVar1);
    }
    (**(code **)(*param_1 + 200))
              (*(undefined4 *)((long)plVar1 + 0x4c),*(undefined4 *)((long)param_1 + 0x84),
               *(undefined4 *)((long)plVar1 + 0x6c),param_1);
  }
  (*(code *)PTR__ZN4Aska18HierarchicalObject3RunEi_02c94c60)(param_1,param_2);
  return;
}

// ==== Aska::RenderableObject::SetVisibility(float)
// vaddr 0x21b78a0 | ghidra 0x22b78a0 | size 328 | symbol _ZN4Aska16RenderableObject13SetVisibilityEf | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska16RenderableObject13SetVisibilityEf(float param_1,long *param_2)

{
  undefined4 *puVar1;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  float fStack_24;
  
  if (_UNK_029715ac <= param_1) {
    *(uint *)(param_2 + 0x33) = *(uint *)(param_2 + 0x33) & 0xffffff7f;
    (**(code **)(*param_2 + 0x248))(param_2,0);
    puVar1 = (undefined4 *)(**(code **)(*param_2 + 0x208))(param_2);
    uStack_30 = *puVar1;
    uStack_2c = puVar1[1];
    if (param_1 < _UNK_029d1a80) {
      param_1 = 1.0;
    }
    uStack_28 = puVar1[2];
    fStack_24 = param_1;
  }
  else if (param_1 <= 0.0) {
    *(uint *)(param_2 + 0x33) = *(uint *)(param_2 + 0x33) | 0x80;
    (**(code **)(*param_2 + 0x248))(param_2,0);
    puVar1 = (undefined4 *)(**(code **)(*param_2 + 0x208))(param_2);
    uStack_30 = *puVar1;
    uStack_2c = puVar1[1];
    uStack_28 = puVar1[2];
    fStack_24 = 0.0;
  }
  else {
    *(uint *)(param_2 + 0x33) = *(uint *)(param_2 + 0x33) & 0xffffff7f;
    (**(code **)(*param_2 + 0x248))(param_2,2);
    puVar1 = (undefined4 *)(**(code **)(*param_2 + 0x208))(param_2);
    uStack_30 = *puVar1;
    uStack_2c = puVar1[1];
    uStack_28 = puVar1[2];
    fStack_24 = param_1;
  }
  (**(code **)(*param_2 + 0x200))(param_2,&uStack_30);
  return;
}

// ==== Aska::RenderableObject::SetRenderLayerID(unsigned char)
// vaddr 0x21b79e8 | ghidra 0x22b79e8 | size 8 | symbol _ZN4Aska16RenderableObject16SetRenderLayerIDEh | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16RenderableObject16SetRenderLayerIDEh(long param_1,undefined1 param_2)

{
  *(undefined1 *)(param_1 + 0x1b7) = param_2;
  return;
}

// ==== Aska::RenderableObject::IsPostProcessObject() const
// vaddr 0x21b79f0 | ghidra 0x22b79f0 | size 52 | symbol _ZNK4Aska16RenderableObject19IsPostProcessObjectEv | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK4Aska16RenderableObject19IsPostProcessObjectEv(long param_1)

{
  return (byte)*PTR__ZN4Aska11RenderLayer20m_ucPostProcessIndexE_02cb6a88 <
         *(byte *)(*(long *)(*(long *)PTR__ZN4Aska6Global16m_pObjectManagerE_02cc4688 + 0x4478) +
                   (ulong)*(byte *)(param_1 + 0x1b7) + 0x10);
}

// ==== Aska::RenderableObject::Get(unsigned long, void*) const
// vaddr 0x21b7a24 | ghidra 0x22b7a24 | size 516 | symbol _ZNK4Aska16RenderableObject3GetEmPv | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 _ZNK4Aska16RenderableObject3GetEmPv(long *param_1,ulong param_2,float *param_3)

{
  ulong uVar1;
  undefined8 uVar2;
  float *pfVar3;
  long lVar4;
  code *pcVar5;
  float fVar6;
  
  uVar1 = Aska::HierarchicalObject::Get(unsigned long, void*) const();
  if ((uVar1 & 1) != 0) goto code_r0x022b7a40;
  if ((param_2 & 0xffff00000000) != 0) {
    return 0;
  }
  uVar2 = 0;
  switch((uint)param_2 & 0xffff) {
  case 0xf:
    pcVar5 = *(code **)(*param_1 + 0x218);
    goto code_r0x022b7b28;
  case 0x10:
    pcVar5 = *(code **)(*param_1 + 0x208);
    goto code_r0x022b7b28;
  case 0x11:
    pcVar5 = *(code **)(*param_1 + 0x238);
    goto code_r0x022b7b28;
  case 0x12:
    pcVar5 = *(code **)(*param_1 + 0x228);
code_r0x022b7b28:
    pfVar3 = (float *)(*pcVar5)(param_1);
    *param_3 = *pfVar3;
    param_3[1] = pfVar3[1];
    param_3[2] = pfVar3[2];
    param_3[3] = pfVar3[3];
    break;
  case 0x13:
    lVar4 = (**(code **)(*param_1 + 0x208))(param_1);
    *param_3 = *(float *)(lVar4 + 0xc);
    break;
  case 0x14:
    *(bool *)param_3 = (*(uint *)(param_1 + 0x33) & 0x20400000) == 0;
    break;
  default:
    goto code_r0x022b7a54;
  case 0x17:
    if ((*(byte *)((long)param_1 + 0x19b) >> 6 & 1) == 0) {
      if (*(byte *)(*(long *)PTR__ZN4Aska6Global16m_pObjectManagerE_02cc4688 + 0x3f09) - 3 < 2)
      break;
      pfVar3 = (float *)(*(long *)(*(long *)PTR__ZN4Aska6Global16m_pObjectManagerE_02cc4688 + 0x3f48
                                  ) + (ulong)*(ushort *)(param_1 + 0x37) * 8 + 4);
    }
    else {
      pfVar3 = (float *)((long)param_1 + 0x1bc);
    }
    *param_3 = *pfVar3;
    break;
  case 0x20:
    *(long *)param_3 = param_1[0x4c];
    break;
  case 0x24:
    *(long *)param_3 = param_1[0x4d];
    break;
  case 0x2d:
    *param_3 = *(float *)(param_1 + 0x5c);
    break;
  case 0x2e:
    *param_3 = *(float *)((long)param_1 + 0x2e4);
    break;
  case 0x30:
    *param_3 = (float)(uint)*(byte *)(param_1 + 0x49);
    break;
  case 0x31:
    *param_3 = (float)param_1[0x4c];
    break;
  case 0x32:
    *param_3 = *(float *)((long)param_1 + 0x1c4);
    break;
  case 0x33:
    *param_3 = *(float *)(param_1 + 0x39);
    break;
  case 0x34:
    *(byte *)param_3 = (byte)*(undefined4 *)((long)param_1 + 0x2f4) & 1;
    break;
  case 0x35:
    *(byte *)param_3 = (byte)(*(uint *)((long)param_1 + 0x2f4) >> 1) & 1;
    break;
  case 0x36:
    *(byte *)param_3 = (byte)(*(uint *)((long)param_1 + 0x2f4) >> 2) & 1;
    break;
  case 0x37:
    fVar6 = *(float *)(param_1 + 0x5f);
    goto code_r0x022b7b00;
  case 0x38:
    fVar6 = *(float *)((long)param_1 + 0x2fc);
code_r0x022b7b00:
    *param_3 = fVar6 * _UNK_029cf7ac;
    break;
  case 0x39:
    *param_3 = *(float *)(param_1 + 0x5d);
    break;
  case 0x3a:
    *param_3 = *(float *)((long)param_1 + 0x2ec);
  }
code_r0x022b7a40:
  uVar2 = 1;
code_r0x022b7a54:
  return uVar2;
}

// ==== Aska::RenderableObject::Set(unsigned long, void const*)
// vaddr 0x21b7c28 | ghidra 0x22b7c28 | size 512 | symbol _ZN4Aska16RenderableObject3SetEmPKv | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 _ZN4Aska16RenderableObject3SetEmPKv(long *param_1,ulong param_2,float *param_3)

{
  float fVar1;
  ulong uVar2;
  uint uVar3;
  code *pcVar4;
  
  uVar2 = Aska::HierarchicalObject::Set(unsigned long, void const*)();
  if ((uVar2 & 1) != 0) {
    return 1;
  }
  if ((param_2 & 0xffff00000000) != 0) {
code_r0x022b7c58:
    return 0;
  }
  switch((uint)param_2 & 0xffff) {
  case 0xf:
    pcVar4 = *(code **)(*param_1 + 0x210);
    goto code_r0x022b7cb8;
  case 0x10:
    pcVar4 = *(code **)(*param_1 + 0x200);
    goto code_r0x022b7cb8;
  case 0x11:
    pcVar4 = *(code **)(*param_1 + 0x230);
    goto code_r0x022b7cb8;
  case 0x12:
    pcVar4 = *(code **)(*param_1 + 0x220);
code_r0x022b7cb8:
    (*pcVar4)(param_1,param_3);
    break;
  case 0x13:
    (**(code **)(*param_1 + 0x240))(*param_3,param_1);
    break;
  case 0x14:
    if (*(byte *)param_3 == 0) {
      uVar3 = *(uint *)(param_1 + 0x33) | 0x400000;
    }
    else {
      uVar3 = *(uint *)(param_1 + 0x33) & 0xffbfffff;
    }
    *(uint *)(param_1 + 0x33) = uVar3;
    break;
  default:
    goto code_r0x022b7c58;
  case 0x17:
    if ((*(uint *)(param_1 + 0x33) >> 0x1e & 1) == 0) {
      return 1;
    }
    fVar1 = *param_3;
    *(uint *)(param_1 + 0x33) = *(uint *)(param_1 + 0x33) | 0x40000000;
    *(float *)((long)param_1 + 0x1bc) = fVar1;
    return 1;
  case 0x21:
  case 0x22:
  case 0x23:
  case 0x25:
  case 0x26:
    break;
  case 0x2d:
    *(float *)(param_1 + 0x5c) = *param_3;
    break;
  case 0x2e:
    *(float *)((long)param_1 + 0x2e4) = *param_3;
    break;
  case 0x30:
    (**(code **)(*param_1 + 0x250))(param_1,*param_3);
    break;
  case 0x31:
    *(float *)(param_1 + 0x4c) = *param_3;
    break;
  case 0x32:
    *(float *)((long)param_1 + 0x1c4) = *param_3;
    break;
  case 0x33:
    *(float *)(param_1 + 0x39) = *param_3;
    break;
  case 0x34:
    uVar3 = *(uint *)((long)param_1 + 0x2f4) | (uint)*(byte *)param_3;
    goto code_r0x022b7db4;
  case 0x35:
    uVar3 = *(uint *)((long)param_1 + 0x2f4) | (uint)*(byte *)param_3 << 1;
    goto code_r0x022b7db4;
  case 0x36:
    uVar3 = *(uint *)((long)param_1 + 0x2f4) | (uint)*(byte *)param_3 << 2;
code_r0x022b7db4:
    *(uint *)((long)param_1 + 0x2f4) = uVar3;
    break;
  case 0x37:
    *(float *)(param_1 + 0x5f) = *param_3 * _UNK_027fa920;
    break;
  case 0x38:
    *(float *)((long)param_1 + 0x2fc) = *param_3 * _UNK_027fa920;
    break;
  case 0x39:
    *(float *)(param_1 + 0x5d) = *param_3;
    break;
  case 0x3a:
    *(float *)((long)param_1 + 0x2ec) = *param_3;
  }
  return 1;
}

// ==== Aska::RenderableObject::DeleteThis(Aska::DeleteManager*)
// vaddr 0x21b7e28 | ghidra 0x22b7e28 | size 124 | symbol _ZN4Aska16RenderableObject10DeleteThisEPNS_13DeleteManagerE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16RenderableObject10DeleteThisEPNS_13DeleteManagerE(long param_1)

{
  char cVar1;
  undefined8 uVar2;
  
  if (*(long *)PTR__ZN4Aska6Global16m_pObjectManagerE_02cc4688 != 0) {
    cVar1 = *(char *)(*(long *)PTR__ZN4Aska6Global16m_pObjectManagerE_02cc4688 + 0x3f09);
    if (cVar1 == '\x01') {
      uVar2 = 0;
      goto code_r0x011ca1d0;
    }
    if (cVar1 == '\x02') goto code_r0x011e8200;
  }
  if ((*(byte *)(param_1 + 0x1b5) >> 3 & 1) == 0) {
code_r0x011e8200:
    (*(code *)PTR__ZN4Aska4Task10DeleteThisEPNS_13DeleteManagerE_02cac0f0)(param_1);
    return;
  }
  uVar2 = 1;
code_r0x011ca1d0:
  (*(code *)PTR__ZN4Aska13DeleteManager7AddMainEPvhhPNS_14IDeleteHandlerE_02c9d0d8)
            (PTR__ZN4Aska6Global21m_systemDeleteManagerE_02cb77c0,param_1,2,uVar2,0);
  return;
}


// FAILED to create function at 02c53ce8 Aska::RenderableObject::vtable
// FAILED to create function at 02c53fc0 Aska::RenderableObject::typeinfo
// FAILED to create function at 02ce6ea0 Aska::RenderableObject::m_vDefaultSphere
