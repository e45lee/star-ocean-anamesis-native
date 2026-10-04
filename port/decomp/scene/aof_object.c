// port/decomp/scene/aof_object.c: Ghidra decompiles for the scene subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-04 06:29 UTC: tools/decomp.sh '--into' 'scene/aof_object' 'Aska::AofObject::'

// ==== Aska::AofObject::AofObject()
// vaddr 0x1e704d8 | ghidra 0x1f704d8 | size 516 | symbol _ZN4Aska9AofObjectC2Ev | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska9AofObjectC2Ev(long *param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  undefined1 auVar3 [16];
  
  Aska::RenderableObject::RenderableObject()();
  puVar1 = PTR__ZTVN4Aska9AofObjectE_02cbc918 + 0x10;
  *(undefined1 *)((long)param_1 + 0x37e) = 0;
  *(undefined2 *)((long)param_1 + 0x382) = 0;
  *(undefined1 *)((long)param_1 + 0x385) = 0;
  *param_1 = (long)puVar1;
  *(undefined1 *)((long)param_1 + 0x387) = 0;
  *(undefined1 *)(param_1 + 0x71) = 0;
  *(undefined2 *)(param_1 + 0x72) = 0;
  param_1[0x78] = 0;
  param_1[0x7b] = 0;
  *(short *)((long)param_1 + 0x37c) =
       (short)(((ulong)*(uint6 *)(param_1 + 0x6f) & 0xfe0000ce2220) >> 0x20);
  param_1[0x75] = 0;
  *(uint *)(param_1 + 0x6f) = (uint)((ulong)*(uint6 *)(param_1 + 0x6f) & 0xfe0000ce2220) | 0xc0;
  puVar2 = PTR__ZTVN4Aska11LinkElementE_02cc16d0;
  auVar3 = NEON_fmov(0x3f800000,4);
  *(undefined1 *)((long)param_1 + 0x386) = 0xff;
  param_1[0x74] = 0;
  param_1[0x73] = 0;
  param_1[0xa5] = auVar3._8_8_;
  param_1[0xa4] = auVar3._0_8_;
  param_1[0xa9] = auVar3._8_8_;
  param_1[0xa8] = auVar3._0_8_;
  puVar1 = PTR__ZTVN4Aska22TextureModifierManagerE_02cbe0b0;
  auVar3 = _UNK_02962690;
  param_1[0x83] = (long)(puVar2 + 0x10);
  param_1[0x82] = (long)(puVar1 + 0x10);
  param_1[0x84] = (long)(param_1 + 0x83);
  param_1[0x85] = (long)(param_1 + 0x83);
  *(undefined4 *)(param_1 + 0x76) = 0;
  *(undefined4 *)(param_1 + 0x86) = 0;
  param_1[0x8b] = 0;
  *(undefined4 *)(param_1 + 0x8c) = 4;
  param_1[0x8d] = 0;
  param_1[0xa7] = 0;
  param_1[0xa6] = 0;
  param_1[0xca] = 0;
  param_1[0xab] = 0;
  param_1[0xaa] = 0;
  *(undefined4 *)(param_1 + 0xcb) = 2;
  param_1[0xcc] = 0;
  *(undefined2 *)((long)param_1 + 0x69b) = 0;
  param_1[0x4c] = -1;
  *(uint *)(param_1 + 0x33) = *(uint *)(param_1 + 0x33) | 0x10;
  *(uint *)(param_1 + 0x36) = *(uint *)(param_1 + 0x36) | 0x10;
  param_1[0x9f] = (long)param_1;
  param_1[0xa0] = (long)param_1;
  param_1[0x7a] = 0;
  param_1[0x79] = 0;
  param_1[0xd0] = 0;
  param_1[0xcf] = 0;
  *(undefined4 *)(param_1 + 0xc6) = 0x42c80000;
  param_1[0xc5] = auVar3._8_8_;
  param_1[0xc4] = auVar3._0_8_;
  *(undefined8 *)((long)param_1 + 0x634) = 0x3f00000042c80000;
  *(undefined8 *)((long)param_1 + 0x63c) = 0x42c800003dcccccd;
  param_1[0x8a] = 0;
  param_1[0x89] = 0;
  param_1[0x88] = 0;
  param_1[0x87] = 0;
  memset(param_1 + 0xb4,0,0x80);
  *(undefined1 *)((long)param_1 + 0x38c) = 3;
  *(undefined1 *)((long)param_1 + 0x38a) = 3;
  *(undefined4 *)((long)param_1 + 0x3bc) = 0;
  param_1[0x6e] = 0;
  *(undefined1 *)((long)param_1 + 0x38b) = 0;
  *(undefined1 *)((long)param_1 + 0x38d) = 0;
  *(undefined1 *)((long)param_1 + 0x381) = 0xff;
  *(undefined2 *)((long)param_1 + 0x38e) = 0;
  *(undefined1 *)((long)param_1 + 900) = 0;
  *(undefined1 *)((long)param_1 + 0x389) = 1;
  *(undefined2 *)((long)param_1 + 0x37f) = 0xffff;
  *(undefined4 *)((long)param_1 + 0x3b4) = 0;
  *(undefined4 *)(param_1 + 0x77) = 0;
  *(undefined1 *)(param_1 + 0xd3) = 1;
  param_1[0xd2] = 0;
  param_1[0xd4] = 0;
  *(undefined1 *)((long)param_1 + 0x699) = 2;
  *(undefined1 *)((long)param_1 + 0x69a) = 0;
  *(uint *)(param_1 + 0x6f) = *(uint *)(param_1 + 0x6f) & 0xff71dddf;
  *(undefined4 *)(param_1 + 0x9e) = 0x3f800000;
  return;
}

// ==== Aska::AofObject::GetClassID(int) const
// vaddr 0x1e77b74 | ghidra 0x1f77b74 | size 68 | symbol _ZNK4Aska9AofObject10GetClassIDEi | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska9AofObject10GetClassIDEi(undefined8 param_1,uint param_2)

{
  undefined8 uVar1;
  undefined8 uVar2;
  
  if (param_2 < 3) {
    return *(undefined8 *)(&UNK_02962d70 + (long)(int)param_2 * 8);
  }
  uVar2 = 0xf000f001;
  if (param_2 != 4) {
    uVar2 = 0xf000;
  }
  uVar1 = 0xf000f001f002;
  if (param_2 != 3) {
    uVar1 = uVar2;
  }
  return uVar1;
}

// ==== Aska::AofObject::CheckSleepAvailability()
// vaddr 0x1e77bc0 | ghidra 0x1f77bc0 | size 48 | symbol _ZN4Aska9AofObject22CheckSleepAvailabilityEv | lib libSOA-3.7.0.so | 2026-10-04
bool _ZN4Aska9AofObject22CheckSleepAvailabilityEv(long param_1)

{
  ulong uVar1;
  
  uVar1 = Aska::RenderableObject::CheckSleepAvailability()();
  if ((uVar1 & 1) != 0) {
    return *(int *)(param_1 + 0x430) < 1;
  }
  return false;
}

// ==== Aska::AofObject::GetBoundingBox(bool)
// vaddr 0x1e77bf0 | ghidra 0x1f77bf0 | size 52 | symbol _ZN4Aska9AofObject14GetBoundingBoxEb | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZN4Aska9AofObject14GetBoundingBoxEb(long param_1,uint param_2)

{
  if ((*(byte *)(param_1 + 0x128) >> 4 & 1) == 0) {
    Aska::AofObject::CalcBoundingExtent(bool)(param_1,param_2 & 1);
  }
  return param_1 + 800U & (long)((ulong)*(uint *)(param_1 + 0x378) << 0x38) >> 0x3f;
}

// ==== Aska::AofObject::EnableCastShadow(bool)
// vaddr 0x1e77c24 | ghidra 0x1f77c24 | size 24 | symbol _ZN4Aska9AofObject16EnableCastShadowEb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska9AofObject16EnableCastShadowEb(long param_1,ushort param_2)

{
  ushort uVar1;
  
  uVar1 = *(ushort *)(param_1 + 0x1b5);
  *(ushort *)(param_1 + 0x1b5) = uVar1 & 0xffe0 | uVar1 & 0xf | (param_2 & 1) << 4;
  return;
}

// ==== Aska::AofObject::SetSystemColorRate(Aska::Vector const*)
// vaddr 0x1e77c3c | ghidra 0x1f77c3c | size 92 | symbol _ZN4Aska9AofObject18SetSystemColorRateEPKNS_6VectorE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska9AofObject18SetSystemColorRateEPKNS_6VectorE(long param_1,float *param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  
  *(float *)(param_1 + 0x540) = *param_2;
  *(float *)(param_1 + 0x544) = param_2[1];
  *(float *)(param_1 + 0x548) = param_2[2];
  *(float *)(param_1 + 0x54c) = param_2[3];
  fVar1 = param_2[1];
  fVar2 = param_2[2];
  fVar3 = param_2[3];
  *(float *)(param_1 + 0x270) = *param_2 * *(float *)(param_1 + 0x520);
  *(float *)(param_1 + 0x274) = fVar1 * *(float *)(param_1 + 0x524);
  *(float *)(param_1 + 0x278) = fVar2 * *(float *)(param_1 + 0x528);
  *(float *)(param_1 + 0x27c) = fVar3 * *(float *)(param_1 + 0x52c);
  return;
}

// ==== Aska::AofObject::SystemColorRate() const
// vaddr 0x1e77c98 | ghidra 0x1f77c98 | size 8 | symbol _ZNK4Aska9AofObject15SystemColorRateEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK4Aska9AofObject15SystemColorRateEv(long param_1)

{
  return param_1 + 0x540;
}

// ==== Aska::AofObject::SetColorRate(Aska::Vector const*)
// vaddr 0x1e77ca0 | ghidra 0x1f77ca0 | size 92 | symbol _ZN4Aska9AofObject12SetColorRateEPKNS_6VectorE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska9AofObject12SetColorRateEPKNS_6VectorE(long param_1,float *param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  
  *(float *)(param_1 + 0x520) = *param_2;
  *(float *)(param_1 + 0x524) = param_2[1];
  *(float *)(param_1 + 0x528) = param_2[2];
  *(float *)(param_1 + 0x52c) = param_2[3];
  fVar1 = param_2[1];
  fVar2 = param_2[2];
  fVar3 = param_2[3];
  *(float *)(param_1 + 0x270) = *param_2 * *(float *)(param_1 + 0x540);
  *(float *)(param_1 + 0x274) = fVar1 * *(float *)(param_1 + 0x544);
  *(float *)(param_1 + 0x278) = fVar2 * *(float *)(param_1 + 0x548);
  *(float *)(param_1 + 0x27c) = fVar3 * *(float *)(param_1 + 0x54c);
  return;
}

// ==== Aska::AofObject::ColorRate() const
// vaddr 0x1e77cfc | ghidra 0x1f77cfc | size 8 | symbol _ZNK4Aska9AofObject9ColorRateEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK4Aska9AofObject9ColorRateEv(long param_1)

{
  return param_1 + 0x520;
}

// ==== Aska::AofObject::SetSystemColorOffset(Aska::Vector const*)
// vaddr 0x1e77d04 | ghidra 0x1f77d04 | size 92 | symbol _ZN4Aska9AofObject20SetSystemColorOffsetEPKNS_6VectorE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska9AofObject20SetSystemColorOffsetEPKNS_6VectorE(long param_1,float *param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  
  *(float *)(param_1 + 0x550) = *param_2;
  *(float *)(param_1 + 0x554) = param_2[1];
  *(float *)(param_1 + 0x558) = param_2[2];
  *(float *)(param_1 + 0x55c) = param_2[3];
  fVar1 = param_2[1];
  fVar2 = param_2[2];
  fVar3 = param_2[3];
  *(float *)(param_1 + 0x280) = *param_2 + *(float *)(param_1 + 0x530);
  *(float *)(param_1 + 0x284) = fVar1 + *(float *)(param_1 + 0x534);
  *(float *)(param_1 + 0x288) = fVar2 + *(float *)(param_1 + 0x538);
  *(float *)(param_1 + 0x28c) = fVar3 + *(float *)(param_1 + 0x53c);
  return;
}

// ==== Aska::AofObject::SystemColorOffset() const
// vaddr 0x1e77d60 | ghidra 0x1f77d60 | size 8 | symbol _ZNK4Aska9AofObject17SystemColorOffsetEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK4Aska9AofObject17SystemColorOffsetEv(long param_1)

{
  return param_1 + 0x550;
}

// ==== Aska::AofObject::SetColorOffset(Aska::Vector const*)
// vaddr 0x1e77d68 | ghidra 0x1f77d68 | size 92 | symbol _ZN4Aska9AofObject14SetColorOffsetEPKNS_6VectorE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska9AofObject14SetColorOffsetEPKNS_6VectorE(long param_1,float *param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  
  *(float *)(param_1 + 0x530) = *param_2;
  *(float *)(param_1 + 0x534) = param_2[1];
  *(float *)(param_1 + 0x538) = param_2[2];
  *(float *)(param_1 + 0x53c) = param_2[3];
  fVar1 = param_2[1];
  fVar2 = param_2[2];
  fVar3 = param_2[3];
  *(float *)(param_1 + 0x280) = *param_2 + *(float *)(param_1 + 0x550);
  *(float *)(param_1 + 0x284) = fVar1 + *(float *)(param_1 + 0x554);
  *(float *)(param_1 + 0x288) = fVar2 + *(float *)(param_1 + 0x558);
  *(float *)(param_1 + 0x28c) = fVar3 + *(float *)(param_1 + 0x55c);
  return;
}

// ==== Aska::AofObject::ColorOffset() const
// vaddr 0x1e77dc4 | ghidra 0x1f77dc4 | size 8 | symbol _ZNK4Aska9AofObject11ColorOffsetEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK4Aska9AofObject11ColorOffsetEv(long param_1)

{
  return param_1 + 0x530;
}

// ==== Aska::AofObject::SetIBLAcceptanceNumber(unsigned int)
// vaddr 0x1e77dcc | ghidra 0x1f77dcc | size 12 | symbol _ZN4Aska9AofObject22SetIBLAcceptanceNumberEj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska9AofObject22SetIBLAcceptanceNumberEj(long param_1,undefined1 param_2)

{
  *(undefined1 *)(param_1 + 0x248) = param_2;
  *(undefined1 *)(param_1 + 0x69a) = param_2;
  return;
}

// ==== Aska::AofObject::ComputeBoundingSphere(bool)
// vaddr 0x1e77dd8 | ghidra 0x1f77dd8 | size 8 | symbol _ZN4Aska9AofObject21ComputeBoundingSphereEb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska9AofObject21ComputeBoundingSphereEb(undefined8 param_1,uint param_2)

{
  (*(code *)PTR__ZN4Aska9AofObject18CalcBoundingExtentEb_02ca2058)(param_1,param_2 & 1);
  return;
}

// ==== Aska::AofObject::GetBoundingBoxDirect(Aska::OrientedBoundingBox*)
// vaddr 0x1e77de0 | ghidra 0x1f77de0 | size 104 | symbol _ZN4Aska9AofObject20GetBoundingBoxDirectEPNS_19OrientedBoundingBoxE | lib libSOA-3.7.0.so | 2026-10-04
bool _ZN4Aska9AofObject20GetBoundingBoxDirectEPNS_19OrientedBoundingBoxE(long param_1,long param_2)

{
  bool bVar1;
  
  bVar1 = (*(uint *)(param_1 + 0x378) >> 7 & 1) != 0;
  if (bVar1) {
    memcpy(param_2,param_1 + 800,0x50);
    *(undefined4 *)(param_2 + 0x10) = *(undefined4 *)(param_1 + 0x510);
    *(undefined4 *)(param_2 + 0x14) = *(undefined4 *)(param_1 + 0x514);
    *(undefined4 *)(param_2 + 0x18) = *(undefined4 *)(param_1 + 0x518);
    *(undefined4 *)(param_2 + 0x1c) = *(undefined4 *)(param_1 + 0x51c);
  }
  return bVar1;
}

// ==== Aska::AofObject::HasBoundingBox() const
// vaddr 0x1e77e48 | ghidra 0x1f77e48 | size 12 | symbol _ZNK4Aska9AofObject14HasBoundingBoxEv | lib libSOA-3.7.0.so | 2026-10-04
uint _ZNK4Aska9AofObject14HasBoundingBoxEv(long param_1)

{
  return *(uint *)(param_1 + 0x378) >> 7 & 1;
}

// ==== Aska::AofObject::IsIntersectable()
// vaddr 0x1e77e54 | ghidra 0x1f77e54 | size 8 | symbol _ZN4Aska9AofObject15IsIntersectableEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska9AofObject15IsIntersectableEv(void)

{
  return 1;
}

// ==== Aska::AofObject::~AofObject()
// vaddr 0x20c2060 | ghidra 0x21c2060 | size 244 | symbol _ZN4Aska9AofObjectD1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska9AofObjectD2Ev(long *param_1)

{
  undefined8 *puVar1;
  long lVar2;
  undefined *puVar3;
  ulong uVar4;
  long lVar5;
  
  uVar4 = (ulong)*(ushort *)((long)param_1 + 0x65a);
  puVar3 = PTR__ZTVN4Aska9AofObjectE_02cbc918 + 0x10;
  *param_1 = (long)puVar3;
  if (uVar4 != 0) {
    lVar5 = uVar4 + 1;
    lVar2 = uVar4 * 8;
    do {
      puVar1 = (undefined8 *)((long)param_1 + lVar2 + 0x660);
      if (param_1[0xca] != 0) {
        puVar1 = (undefined8 *)(param_1[0xca] + lVar2 + -8);
      }
      Aska::AofObject::RemoveStandingShaderAdapter(Aska::BaseShaderAdapter*)(param_1,*puVar1);
      lVar5 = lVar5 + -1;
      lVar2 = lVar2 + -8;
    } while (1 < lVar5);
    puVar3 = (undefined *)*param_1;
  }
  (**(code **)(puVar3 + 0x2d0))(param_1,0,0);
  if ((long *)param_1[0x74] != (long *)0x0) {
    (**(code **)(*(long *)param_1[0x74] + 8))();
    param_1[0x74] = 0;
  }
  if (param_1[0xca] != 0) {
    if (param_1[0xcc] == 0) {
      operator delete[](void*)(param_1[0xca]);
      lVar5 = param_1[0x8b];
      goto joined_r0x021c210c;
    }
    Aska::MemoryManager::LocalFree(void*)();
  }
  lVar5 = param_1[0x8b];
joined_r0x021c210c:
  if (lVar5 != 0) {
    if (param_1[0x8d] == 0) {
      operator delete[](void*)(lVar5);
    }
    else {
      Aska::MemoryManager::LocalFree(void*)();
    }
  }
  Aska::TextureModifierManager::~TextureModifierManager()(param_1 + 0x82);
  (*(code *)PTR__ZN4Aska16RenderableObjectD2Ev_02cad338)(param_1);
  return;
}

// ==== Aska::AofObject::RemoveStandingShaderAdapter(Aska::BaseShaderAdapter*)
// vaddr 0x20c2154 | ghidra 0x21c2154 | size 508 | symbol _ZN4Aska9AofObject27RemoveStandingShaderAdapterEPNS_17BaseShaderAdapterE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska9AofObject27RemoveStandingShaderAdapterEPNS_17BaseShaderAdapterE
               (long param_1,long *param_2)

{
  short sVar1;
  ulong uVar2;
  uint uVar3;
  long lVar4;
  ulong uVar5;
  long lVar6;
  long lVar7;
  undefined8 *puVar8;
  long lVar9;
  ulong uVar10;
  undefined8 uVar11;
  undefined8 uVar12;
  
  uVar2 = (ulong)*(ushort *)(param_1 + 0x65a);
  if (uVar2 != 0) {
    if (*(long *)(param_1 + 0x650) == 0) {
      lVar4 = 0;
      do {
        if (*(long **)(param_1 + 0x668 + lVar4 * 8) == param_2) goto code_r0x021c21c0;
        lVar4 = lVar4 + 1;
      } while (lVar4 < (long)uVar2);
    }
    else {
      lVar4 = 0;
      do {
        if (*(long **)(*(long *)(param_1 + 0x650) + lVar4 * 8) == param_2) goto code_r0x021c21c0;
        lVar4 = lVar4 + 1;
      } while (lVar4 < (long)uVar2);
    }
  }
  goto code_r0x021c2304;
code_r0x021c21c0:
  uVar3 = (uint)lVar4;
  if (*(ushort *)(param_1 + 0x65a) <= uVar3) goto code_r0x021c2304;
  lVar6 = uVar2 - 1;
  lVar4 = param_1 + 0x668;
  if (*(long *)(param_1 + 0x650) != 0) {
    lVar4 = *(long *)(param_1 + 0x650);
  }
  if ((int)uVar3 < (int)lVar6) {
    lVar7 = (long)(int)uVar3;
    uVar2 = lVar6 - lVar7;
    lVar9 = lVar7;
    if ((uVar2 < 4) || (uVar5 = uVar2 & 0xfffffffffffffffc, uVar5 == 0)) {
code_r0x021c2230:
      lVar6 = lVar6 - lVar9;
      puVar8 = (undefined8 *)(lVar4 + lVar9 * 8);
      do {
        lVar6 = lVar6 + -1;
        *puVar8 = puVar8[1];
        puVar8 = puVar8 + 1;
      } while (lVar6 != 0);
    }
    else {
      lVar9 = lVar7 + uVar5;
      puVar8 = (undefined8 *)(lVar4 + lVar7 * 8 + 0x10);
      uVar10 = uVar5;
      do {
        uVar11 = puVar8[-1];
        uVar12 = puVar8[1];
        uVar10 = uVar10 - 4;
        puVar8[-1] = *puVar8;
        puVar8[-2] = uVar11;
        puVar8[1] = puVar8[2];
        *puVar8 = uVar12;
        puVar8 = puVar8 + 4;
      } while (uVar10 != 0);
      if (uVar2 != uVar5) goto code_r0x021c2230;
    }
    uVar2 = (ulong)*(ushort *)(param_1 + 0x65a);
  }
  uVar3 = (int)uVar2 - 1;
  if ((int)(uint)*(ushort *)(param_1 + 0x658) < (int)uVar3) {
    lVar6 = *(long *)(param_1 + 0x650);
    lVar4 = *(long *)(param_1 + 0x660);
    uVar2 = -(ulong)((uVar3 & 0x7fffffff) >> 0x1e) & 0xfffffff800000000 | (ulong)(uVar3 * 2) << 3;
    if (lVar6 == 0) {
      if (lVar4 == 0) {
        lVar4 = operator new[](unsigned long, std::nothrow_t const&)(uVar2,PTR__ZSt7nothrow_02cb9a80);
      }
      else {
        lVar4 = Aska::MemoryManager::Malloc(unsigned long)();
      }
      if (lVar4 != 0) {
        memcpy(lVar4,param_1 + 0x668,(ulong)*(ushort *)(param_1 + 0x65a) << 3);
      }
    }
    else if (lVar4 == 0) {
      lVar4 = operator new[](unsigned long, void*, unsigned long)(uVar2,lVar6,4);
    }
    else {
      lVar4 = Aska::MemoryManager::Realloc(unsigned long, void*, long)(lVar4,uVar2,lVar6,4);
    }
    if (lVar4 == 0) goto code_r0x021c2304;
    *(long *)(param_1 + 0x650) = lVar4;
    *(short *)(param_1 + 0x658) = (short)(uVar3 * 2);
  }
  *(short *)(param_1 + 0x65a) = (short)uVar3;
code_r0x021c2304:
  sVar1 = *(short *)((long)param_2 + 10) + -1;
  *(short *)((long)param_2 + 10) = sVar1;
  if ((param_2 != (long *)0x0) && (sVar1 == 0)) {
                    /* WARNING: Could not recover jumptable at 0x021c2338. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(*param_2 + 0x48))(param_2);
    return;
  }
  return;
}

// ==== Aska::AofObject::~AofObject()
// vaddr 0x20c2350 | ghidra 0x21c2350 | size 24 | symbol _ZN4Aska9AofObjectD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska9AofObjectD0Ev(undefined8 param_1)

{
  Aska::AofObject::~AofObject()();
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::AofObject::DeleteThis(Aska::DeleteManager*)
// vaddr 0x20c2368 | ghidra 0x21c2368 | size 4 | symbol _ZN4Aska9AofObject10DeleteThisEPNS_13DeleteManagerE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska9AofObject10DeleteThisEPNS_13DeleteManagerE(void)

{
  (*(code *)PTR__ZN4Aska16RenderableObject10DeleteThisEPNS_13DeleteManagerE_02c8e668)();
  return;
}

// ==== Aska::AofObject::Run(int)
// vaddr 0x20c236c | ghidra 0x21c236c | size 88 | symbol _ZN4Aska9AofObject3RunEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska9AofObject3RunEi(long param_1,undefined4 param_2)

{
  if (0 < *(int *)(param_1 + 0x430)) {
    (**(code **)**(undefined8 **)PTR__ZN4Aska6Global8m_pVSyncE_02cbd460)
              (*(undefined8 **)PTR__ZN4Aska6Global8m_pVSyncE_02cbd460,0);
    Aska::TextureModifierManager::Tick(float)(param_1 + 0x410);
  }
  (*(code *)PTR__ZN4Aska16RenderableObject3RunEi_02c98478)(param_1,param_2);
  return;
}

// ==== Aska::AofObject::ReleaseShaderCache()
// vaddr 0x20c23c4 | ghidra 0x21c23c4 | size 180 | symbol _ZN4Aska9AofObject18ReleaseShaderCacheEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska9AofObject18ReleaseShaderCacheEv(long param_1)

{
  long *plVar1;
  undefined8 uVar2;
  long lVar3;
  long lVar4;
  int *piVar5;
  
  lVar3 = *(long *)(param_1 + 0x3d8);
  if (lVar3 == 0) {
    return 0;
  }
  lVar4 = *(long *)(param_1 + 0x398);
  if (lVar4 == 0) {
    for (lVar4 = *(long *)(lVar3 + 0x138); lVar3 + 0x128 != lVar4; lVar4 = *(long *)(lVar4 + 0x10))
    {
      if ((*(short *)(lVar4 + 0x7a) == 0) && (piVar5 = (int *)(lVar4 + 0x90), *piVar5 == 0)) {
        Aska::RenderPassManager::InvalidateAll()(lVar4);
        goto code_r0x021c245c;
      }
    }
    plVar1 = (long *)(lVar3 + 0x120);
    lVar4 = Aska::RenderPassManagerList::CreateCopy()(plVar1);
    if (lVar4 != 0) {
      (**(code **)(*plVar1 + 0x10))(plVar1,lVar4);
      piVar5 = (int *)(lVar4 + 0x90);
code_r0x021c245c:
      *piVar5 = 0x1000000;
    }
    *(long *)(param_1 + 0x398) = lVar4;
  }
  uVar2 = (*(code *)PTR__ZN4Aska17RenderPassManager22InvalidateShaderCachesEv_02c9bf18)(lVar4);
  return uVar2;
}

// ==== Aska::AofObject::InitializeConditions()
// vaddr 0x20c2478 | ghidra 0x21c2478 | size 520 | symbol _ZN4Aska9AofObject20InitializeConditionsEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska9AofObject20InitializeConditionsEv(long param_1)

{
  long *plVar1;
  byte bVar2;
  long lVar3;
  long lVar4;
  ulong uVar5;
  long lVar6;
  char *pcVar7;
  float *pfVar8;
  int *piVar9;
  float fVar10;
  float fVar11;
  
  Aska::RenderableObject::InitializeConditions()();
  lVar3 = *(long *)(param_1 + 0x3d8);
  if (lVar3 == 0) {
    return;
  }
  if (*(int *)(param_1 + 0x430) != 0) {
    *(uint *)(param_1 + 0x378) = *(uint *)(param_1 + 0x378) & 0xffffffbf;
  }
  lVar4 = *(long *)(lVar3 + 0xd0);
  if (lVar4 == 0) {
code_r0x021c251c:
    pfVar8 = (float *)0x0;
  }
  else {
    uVar5 = (ulong)*(ushort *)(*(long *)(lVar3 + 0xb0) + 0x70);
    if (uVar5 != 0) {
      if (*(long *)(lVar3 + 0x100) == 0) {
        if (cRam0000000000000230 == -1) goto code_r0x021c2510;
code_r0x021c24fc:
        *(uint *)(param_1 + 0x378) = *(uint *)(param_1 + 0x378) & 0xffffffbf;
        lVar4 = *(long *)(lVar3 + 0xd0);
      }
      else {
        lVar6 = 0;
        pcVar7 = (char *)(*(long *)(lVar3 + 0x100) + 0x240);
        do {
          if (*pcVar7 != -1) goto code_r0x021c24fc;
          lVar6 = lVar6 + 1;
          pcVar7 = pcVar7 + 0x2a0;
        } while (lVar6 < (long)uVar5);
      }
      if (lVar4 == 0) goto code_r0x021c251c;
    }
code_r0x021c2510:
    pfVar8 = (float *)(*(long *)(lVar3 + 0xb0) + 0x10);
  }
  if (((*(uint *)(param_1 + 0x1b0) & 7) == 0) &&
     (((*(uint *)(param_1 + 0x1b0) & 0x600) == 0 || ((*(byte *)(param_1 + 400) & 0x1c) == 0)))) {
    bVar2 = *(byte *)(lVar3 + 0xa8);
    *(undefined2 *)(param_1 + 0x37c) = *(undefined2 *)(param_1 + 0x37c);
    *(uint *)(param_1 + 0x378) =
         *(uint *)(param_1 + 0x378) & 0xffffff00 |
         *(uint *)(param_1 + 0x378) & 0x7f | (bVar2 >> 3 & 1) << 7;
    *(float *)(param_1 + 0x310) = *pfVar8;
    *(float *)(param_1 + 0x314) = pfVar8[1];
    *(float *)(param_1 + 0x318) = pfVar8[2];
    *(float *)(param_1 + 0x31c) = pfVar8[3];
    lVar3 = *(long *)(param_1 + 0x398);
  }
  else {
    *(uint *)(param_1 + 0x378) = *(uint *)(param_1 + 0x378) & 0xffffff7f;
    fVar11 = *pfVar8 * *pfVar8 + pfVar8[1] * pfVar8[1] + pfVar8[2] * pfVar8[2];
    fVar10 = SQRT(fVar11);
    if (NAN(fVar10)) {
      fVar10 = (float)sqrtf(fVar11);
    }
    fVar11 = pfVar8[3];
    *(undefined4 *)(param_1 + 0x310) = 0;
    *(undefined8 *)(param_1 + 0x314) = 0;
    *(float *)(param_1 + 0x31c) = fVar10 + fVar11;
    lVar3 = *(long *)(param_1 + 0x398);
  }
  if (lVar3 == 0) {
    lVar4 = *(long *)(param_1 + 0x3d8);
    if (lVar4 != 0) {
      for (lVar3 = *(long *)(lVar4 + 0x138); lVar4 + 0x128 != lVar3; lVar3 = *(long *)(lVar3 + 0x10)
          ) {
        if ((*(short *)(lVar3 + 0x7a) == 0) && (piVar9 = (int *)(lVar3 + 0x90), *piVar9 == 0)) {
          Aska::RenderPassManager::InvalidateAll()(lVar3);
          goto code_r0x021c2664;
        }
      }
      plVar1 = (long *)(lVar4 + 0x120);
      lVar3 = Aska::RenderPassManagerList::CreateCopy()(plVar1);
      if (lVar3 != 0) {
        (**(code **)(*plVar1 + 0x10))(plVar1,lVar3);
        piVar9 = (int *)(lVar3 + 0x90);
code_r0x021c2664:
        *piVar9 = 0x1000000;
        *(long *)(param_1 + 0x398) = lVar3;
        goto code_r0x011d4170;
      }
      *(undefined8 *)(param_1 + 0x398) = 0;
    }
    return;
  }
code_r0x011d4170:
  (*(code *)PTR__ZN4Aska17RenderPassManager18InvalidateMaterialEv_02ca20a8)(lVar3);
  return;
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

// ==== Aska::AofObject::InvalidateObjectRenderState()
// vaddr 0x20c27a8 | ghidra 0x21c27a8 | size 56 | symbol _ZN4Aska9AofObject27InvalidateObjectRenderStateEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska9AofObject27InvalidateObjectRenderStateEv(long param_1)

{
  long lVar1;
  ulong uVar2;
  long lVar3;
  
  uVar2 = (ulong)*(ushort *)(param_1 + 0x462);
  if (uVar2 != 0) {
    lVar3 = 0;
    do {
      uVar2 = uVar2 - 1;
      lVar1 = param_1 + 0x470;
      if (*(long *)(param_1 + 0x458) != 0) {
        lVar1 = *(long *)(param_1 + 0x458);
      }
      lVar1 = lVar1 + lVar3;
      lVar3 = lVar3 + 0x20;
      *(undefined1 *)(lVar1 + 0x1a) = 0;
    } while (uVar2 != 0);
  }
  return;
}

// ==== Aska::AofObject::SetProgrammableForceOpaque(bool)
// vaddr 0x20c27e0 | ghidra 0x21c27e0 | size 392 | symbol _ZN4Aska9AofObject26SetProgrammableForceOpaqueEb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska9AofObject26SetProgrammableForceOpaqueEb(long *param_1,ushort param_2)

{
  uint *puVar1;
  undefined1 uVar2;
  uint uVar3;
  long *plVar4;
  ulong uVar5;
  long lVar6;
  
  if (((*(ushort *)((long)param_1 + 0x37a) ^ param_2) & 1) != 0) {
    puVar1 = (uint *)(param_1 + 0x6f);
    if ((param_2 & 1) == 0) {
      uVar5 = (ulong)*(ushort *)((long)param_1 + 0x462);
      if (uVar5 != 0) {
        lVar6 = 0;
        do {
          uVar5 = uVar5 - 1;
          plVar4 = param_1 + 0x8e;
          if ((long *)param_1[0x8b] != (long *)0x0) {
            plVar4 = (long *)param_1[0x8b];
          }
          *(undefined1 *)((long)plVar4 + lVar6 + 0x1a) = 0;
          lVar6 = lVar6 + 0x20;
        } while (uVar5 != 0);
      }
      if (*(char *)((long)param_1 + 0x386) != -1) {
        *(uint *)(param_1 + 0x33) = *(uint *)(param_1 + 0x33) & 0xffffffef;
        *(uint *)(param_1 + 0x36) = *(uint *)(param_1 + 0x36) & 0xffffffef;
        (**(code **)(*param_1 + 0x160))(param_1);
        *(undefined1 *)((long)param_1 + 0x386) = 0xff;
      }
      uVar2 = *(undefined1 *)((long)param_1 + 0x1b4);
      *(undefined1 *)((long)param_1 + 0x1b4) = 0;
      *puVar1 = *puVar1 & 0xfffeffff;
                    /* WARNING: Could not recover jumptable at 0x021c2964. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (**(code **)(*param_1 + 0x248))(param_1,uVar2);
      return;
    }
    uVar2 = *(undefined1 *)((long)param_1 + 0x1b4);
    (**(code **)(*param_1 + 0x248))(param_1,0);
    uVar5 = (ulong)*(ushort *)((long)param_1 + 0x462);
    *(undefined1 *)((long)param_1 + 0x1b4) = uVar2;
    if (uVar5 != 0) {
      lVar6 = 0;
      do {
        uVar5 = uVar5 - 1;
        plVar4 = param_1 + 0x8e;
        if ((long *)param_1[0x8b] != (long *)0x0) {
          plVar4 = (long *)param_1[0x8b];
        }
        *(undefined1 *)((long)plVar4 + lVar6 + 0x1a) = 0;
        lVar6 = lVar6 + 0x20;
      } while (uVar5 != 0);
    }
    uVar3 = *(byte *)((long)param_1 + 0x1b7) - 5;
    if (uVar3 < 3) {
      *(byte *)((long)param_1 + 0x386) = *(byte *)((long)param_1 + 0x1b7);
      (**(code **)(*param_1 + 0x160))(param_1,0x30304 >> (ulong)((uVar3 & 3) << 3));
      *(uint *)(param_1 + 0x33) = *(uint *)(param_1 + 0x33) | 0x10;
      if ((param_1[0x7b] == 0) || (uVar5 = Aska::MaterialList::IsPunchthrough()(param_1[0x7b] + 0xe8), (uVar5 & 1) == 0))
      {
        *(uint *)(param_1 + 0x36) = *(uint *)(param_1 + 0x36) | 0x10;
      }
    }
    *puVar1 = *puVar1 | 0x10000;
  }
  return;
}

// ==== Aska::AofObject::SetRenderLayerID(unsigned char)
// vaddr 0x20c2968 | ghidra 0x21c2968 | size 120 | symbol _ZN4Aska9AofObject16SetRenderLayerIDEh | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska9AofObject16SetRenderLayerIDEh(long param_1,uint param_2)

{
  ulong uVar1;
  undefined8 uVar2;
  
  if ((*(byte *)(param_1 + 0x2f0) & 1) != 0) {
    uVar2 = *(undefined8 *)PTR__ZN4Aska6Global16m_pObjectManagerE_02cc4688;
    uVar1 = Aska::ObjectManager::IsReducedBufferLayer(int)(uVar2,param_2 & 0xff);
    if (((uVar1 & 1) == 0) && (uVar1 = Aska::ObjectManager::IsNeedZLayer(int)(uVar2,param_2 & 0xff), (uVar1 & 1) == 0)) {
      param_2 = 8;
    }
    *(uint *)(param_1 + 0x378) = *(uint *)(param_1 + 0x378) & 0xffffffbf;
  }
  (*(code *)PTR__ZN4Aska16RenderableObject16SetRenderLayerIDEh_02ca2050)(param_1,param_2);
  return;
}

// ==== Aska::AofObject::SetAofHandler(Aska::AofHandler*, bool)
// vaddr 0x20c29e0 | ghidra 0x21c29e0 | size 2560 | symbol _ZN4Aska9AofObject13SetAofHandlerEPNS_10AofHandlerEb | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8
_ZN4Aska9AofObject13SetAofHandlerEPNS_10AofHandlerEb(long *param_1,long *param_2,ulong param_3)

{
  uint6 *puVar1;
  byte bVar2;
  short sVar3;
  ushort uVar4;
  undefined2 uVar5;
  char cVar6;
  bool bVar7;
  uint uVar8;
  uint6 uVar9;
  undefined *puVar10;
  ulong uVar11;
  long *plVar12;
  long lVar13;
  long *plVar14;
  long lVar15;
  long lVar16;
  ulong uVar17;
  uint uVar18;
  int iVar19;
  int *piVar20;
  long *plVar21;
  long lVar22;
  ulong uVar23;
  long lVar24;
  long lVar25;
  long lStack_88;
  long lStack_80;
  undefined8 uStack_78;
  undefined8 uStack_70;
  undefined8 uStack_68;
  
  sVar3 = *(short *)((long)param_1 + 0x462);
  if (param_1[0x73] == 0) {
    plVar14 = (long *)0x0;
  }
  else {
    plVar14 = &lStack_80;
    uStack_78 = 0;
    lStack_80 = 0;
    uStack_68 = 0;
    uStack_70 = 0;
  }
  *(undefined1 *)(param_1 + 0x71) = 0;
  *(undefined1 *)((long)param_1 + 0x386) = 0xff;
  *(undefined2 *)(param_1 + 0x72) = 0x210;
  if ((param_2 != (long *)0x0) &&
     (uVar11 = (**(code **)(*param_2 + 0x30))(param_2), (uVar11 & 1) != 0)) {
    bVar2 = *(byte *)(param_2 + 0x6a);
    if ((bVar2 >> 3 & 1) != 0) {
      *(undefined1 *)(param_1 + 0xd3) = 0;
      *(ushort *)(param_1 + 0x72) = *(ushort *)(param_1 + 0x72) | 8;
      bVar2 = *(byte *)(param_2 + 0x6a);
    }
    *(uint *)(param_1 + 0x6f) =
         *(uint *)(param_1 + 0x6f) & 0x80000000 |
         *(uint *)(param_1 + 0x6f) & 0x3fffffff | (bVar2 >> 4 & 1) << 0x1e;
  }
  *(ushort *)((long)param_1 + 0x37c) = *(ushort *)((long)param_1 + 0x37c) & 0xff7f;
  if (param_1[0x73] != 0) {
    plVar14[2] = param_1[0x73];
    param_1[0x73] = 0;
  }
  puVar10 = PTR__ZN4Aska6Global21m_systemDeleteManagerE_02cb77c0;
  if (sVar3 != 0) {
    uVar4 = *(ushort *)((long)param_1 + 0x462);
    uVar11 = (ulong)uVar4;
    if ((param_3 & 1) == 0) {
      if (uVar4 != 0) {
        uVar23 = 0;
        do {
          plVar21 = param_1 + uVar23 * 4 + 0x8e;
          if (param_1[0x8b] != 0) {
            plVar21 = (long *)(param_1[0x8b] + uVar23 * 0x20);
          }
          if (*plVar21 != 0) {
            Aska::RenderState::Release()();
          }
          if (plVar21[1] != 0) {
            Aska::RenderState::Release()();
          }
          plVar21 = (long *)plVar21[2];
          if (plVar21 != (long *)0x0) {
            plVar12 = (long *)*plVar21;
            if (plVar12 != (long *)0x0) {
              uVar17 = (ulong)*(ushort *)(plVar21 + 1);
              if (*(ushort *)(plVar21 + 1) != 0) {
                lVar24 = 0;
                do {
                  if (plVar12[lVar24] != 0) {
                    Aska::RenderState::Release()(plVar12[lVar24]);
                    *(undefined8 *)(*plVar21 + lVar24 * 8) = 0;
                    uVar17 = (ulong)*(ushort *)(plVar21 + 1);
                    plVar12 = (long *)*plVar21;
                  }
                  lVar24 = lVar24 + 1;
                } while (lVar24 < (long)uVar17);
              }
              if ((plVar12 != plVar21 + 2) && (plVar12 != (long *)0x0)) {
                operator delete[](void*)();
              }
            }
            operator delete(void*)(plVar21);
          }
          uVar23 = uVar23 + 1;
        } while (uVar23 != uVar11);
      }
    }
    else if (uVar4 != 0) {
      lVar24 = 0;
      do {
        plVar21 = param_1 + 0x8e;
        if ((long *)param_1[0x8b] != (long *)0x0) {
          plVar21 = (long *)param_1[0x8b];
        }
        plVar21 = (long *)((long)plVar21 + lVar24);
        if (*plVar21 != 0) {
          Aska::DeleteManager::AddMain(void*, unsigned char, unsigned char, Aska::IDeleteHandler*)(puVar10,*plVar21,0,0,
                          &PTR__ZTV23AofObjectReleaseHandlerIN4Aska11RenderStateEE_16__02cc7ae8);
        }
        if (plVar21[1] != 0) {
          Aska::DeleteManager::AddMain(void*, unsigned char, unsigned char, Aska::IDeleteHandler*)(puVar10,plVar21[1],0,0,
                          &PTR__ZTV23AofObjectReleaseHandlerIN4Aska11RenderStateEE_16__02cc7ae8);
        }
        if (plVar21[2] != 0) {
          Aska::DeleteManager::AddMain(void*, unsigned char, unsigned char, Aska::IDeleteHandler*)(puVar10,plVar21[2],0,0,
                          &PTR__ZTV22AofObjectDeleteHandlerIN4Aska16RenderStateArrayEE_16__02cc7ae0)
          ;
        }
        uVar11 = uVar11 - 1;
        lVar24 = lVar24 + 0x20;
      } while (uVar11 != 0);
    }
    *(undefined2 *)((long)param_1 + 0x462) = 0;
  }
  if (param_1[0x78] != 0) {
    plVar14[3] = param_1[0x78];
    param_1[0x78] = 0;
  }
  lVar24 = param_1[0x7b];
  if (lVar24 != 0) {
    *plVar14 = lVar24;
    *(char *)(lVar24 + 0xa9) = *(char *)(lVar24 + 0xa9) + -1;
    *(long *)(param_1[0x9f] + 0x500) = param_1[0xa0];
    *(long *)(param_1[0xa0] + 0x4f8) = param_1[0x9f];
    if (*(char *)(param_1[0x7b] + 0xa9) == '\0') {
      lVar24 = 0;
    }
    else {
      lVar24 = param_1[0x9f];
    }
    *(long *)(param_1[0x7b] + 800) = lVar24;
    param_1[0x9f] = (long)param_1;
    param_1[0xa0] = (long)param_1;
  }
  if (param_1[0x74] != 0) {
    plVar14[1] = param_1[0x74];
    param_1[0x74] = 0;
  }
  plVar21 = param_2;
  if ((param_2 != (long *)0x0) && (plVar21 = (long *)0x0, (*(byte *)(param_2 + 0x15) & 1) != 0)) {
    plVar21 = param_2;
  }
  param_1[0x7b] = (long)plVar21;
  if (plVar14 != (long *)0x0) {
    lVar24 = plVar14[2];
    if ((param_3 & 1) == 0) {
      if (lVar24 != 0) {
        (**(code **)(*(long *)*plVar14 + 0x58))((long *)*plVar14,0);
      }
      plVar12 = (long *)*plVar14;
      if (plVar12 != (long *)0x0) {
        iVar19 = (int)plVar12[1] + -1;
        *(int *)(plVar12 + 1) = iVar19;
        if (iVar19 == 0) {
          (**(code **)(*plVar12 + 8))();
        }
        *plVar14 = 0;
      }
      if ((long *)plVar14[1] != (long *)0x0) {
        (**(code **)(*(long *)plVar14[1] + 8))();
        plVar14[1] = 0;
      }
      if (plVar14[3] != 0) {
        operator delete[](void*)();
        plVar14[3] = 0;
      }
    }
    else {
      if (lVar24 != 0) {
        lVar13 = 0;
        if (*plVar14 != 0) {
          lVar13 = *plVar14 + 0xa0;
        }
        Aska::DeleteManager::AddMain(void*, unsigned char, unsigned char, Aska::IDeleteHandler*)(PTR__ZN4Aska6Global21m_systemDeleteManagerE_02cb77c0,lVar24,0,0,lVar13);
      }
      if (*plVar14 != 0) {
        Aska::DeleteManager::AddMain(void*, unsigned char, unsigned char, Aska::IDeleteHandler*)(PTR__ZN4Aska6Global21m_systemDeleteManagerE_02cb77c0,*plVar14,0,0,
                        &PTR__ZTV23AofObjectReleaseHandlerIN4Aska10AofHandlerEE_16__02cc7af0);
      }
      if (plVar14[1] != 0) {
        Aska::DeleteManager::AddMain(void*, unsigned char, unsigned char, Aska::IDeleteHandler*)(PTR__ZN4Aska6Global21m_systemDeleteManagerE_02cb77c0,plVar14[1],0,0,
                        &PTR__ZTV22AofObjectDeleteHandlerIN4Aska16SkinMatricesBaseEE_16__02cc7af8);
      }
      if (plVar14[3] != 0) {
        Aska::DeleteManager::AddMain(void*, unsigned char, unsigned char, Aska::IDeleteHandler*)(PTR__ZN4Aska6Global21m_systemDeleteManagerE_02cb77c0,plVar14[3],0,0,
                        &
                        PTR__ZTV27AofObjectDeleteArrayHandlerIN4Aska12LightManager12LightContextEE_16__02cc7b00
                       );
      }
    }
  }
  if (plVar21 == (long *)0x0) {
    return 1;
  }
  puVar1 = (uint6 *)(param_1 + 0x6f);
  Aska::AofHandler::SetShaderContextFlag()(param_1[0x7b]);
  lVar24 = param_1[0x7b];
  piVar20 = (int *)(lVar24 + 0x18);
  do {
    if (*piVar20 != 0) {
      ClearExclusiveLocal();
      uVar18 = 0;
      do {
        uVar18 = uVar18 + 1;
        if ((uVar18 & 0x1ff) == 0) {
          Aska::Thread::SleepU(unsigned int)(0);
        }
        while (*piVar20 == 0) {
          cVar6 = '\x01';
          bVar7 = (bool)ExclusiveMonitorPass(piVar20,0x10);
          if (bVar7) {
            *piVar20 = 1;
            cVar6 = ExclusiveMonitorsStatus();
          }
          if (cVar6 == '\0') goto code_r0x021c2e10;
        }
        ClearExclusiveLocal();
      } while( true );
    }
    cVar6 = '\x01';
    bVar7 = (bool)ExclusiveMonitorPass(piVar20,0x10);
    if (bVar7) {
      *piVar20 = 1;
      cVar6 = ExclusiveMonitorsStatus();
    }
  } while (cVar6 != '\0');
code_r0x021c2e10:
  *(int *)(lVar24 + 0x88) = *(int *)(lVar24 + 0x88) + 1;
  *(undefined4 *)(lVar24 + 0x18) = 0;
  Aska::Event::Wait(unsigned int) const(lVar24 + 0x20,0);
  do {
    if (*piVar20 != 0) {
      ClearExclusiveLocal();
      uVar18 = 0;
      do {
        uVar18 = uVar18 + 1;
        if ((uVar18 & 0x1ff) == 0) {
          Aska::Thread::SleepU(unsigned int)(0);
        }
        while (*piVar20 == 0) {
          cVar6 = '\x01';
          bVar7 = (bool)ExclusiveMonitorPass(piVar20,0x10);
          if (bVar7) {
            *piVar20 = 1;
            cVar6 = ExclusiveMonitorsStatus();
          }
          if (cVar6 == '\0') goto code_r0x021c2e8c;
        }
        ClearExclusiveLocal();
      } while( true );
    }
    cVar6 = '\x01';
    bVar7 = (bool)ExclusiveMonitorPass(piVar20,0x10);
    if (bVar7) {
      *piVar20 = 1;
      cVar6 = ExclusiveMonitorsStatus();
    }
  } while (cVar6 != '\0');
code_r0x021c2e8c:
  iVar19 = *(int *)(lVar24 + 0x88) + -1;
  *(int *)(lVar24 + 0x88) = iVar19;
  if ((iVar19 == 0) && (*(int *)(lVar24 + 0x1c) < 1)) {
    Aska::Event::Exit()(lVar24 + 0x20);
  }
  *piVar20 = 0;
  lVar24 = param_1[0x7b];
  uVar5 = *(undefined2 *)((long)param_1 + 0x37c);
  uVar18 = (uint)*puVar1;
  uVar4 = *(ushort *)(lVar24 + 0x108);
  *(undefined2 *)((long)param_1 + 0x37c) = uVar5;
  uVar8 = uVar18 & 0xf | (uVar4 >> 4 & 1) << 4;
  *(uint *)puVar1 = uVar18 & 0xffffffe0 | uVar8;
  uVar4 = *(ushort *)(lVar24 + 0x108);
  *(undefined2 *)((long)param_1 + 0x37c) = uVar5;
  *(uint *)puVar1 = uVar18 & 0xfffff800 | uVar18 & 0x3e0 | uVar8 | (uVar4 >> 5 & 1) << 10;
  if ((*(byte *)(lVar24 + 0x108) >> 6 & 1) == 0) {
code_r0x021c2f18:
    lVar13 = lVar24 + 0xe8;
    uVar11 = Aska::MaterialList::IsPunchthrough()(lVar13);
    if ((uVar11 & 1) != 0) {
      *(uint *)(param_1 + 0x36) = *(uint *)(param_1 + 0x36) & 0xffffffef;
    }
    lVar15 = param_1[0x7b];
    if (*(long *)(lVar15 + 0xd0) == 0) {
      uVar11 = 0;
    }
    else {
      uVar11 = (ulong)*(ushort *)(*(long *)(lVar15 + 0xb0) + 0x70);
    }
    bVar2 = *(byte *)(lVar15 + 0xa8);
    *(undefined2 *)((long)param_1 + 0x37c) = *(undefined2 *)((long)param_1 + 0x37c);
    *(uint *)puVar1 = (uint)*puVar1 & 0xffffff00 | (uint)*puVar1 & 0x7f | (bVar2 >> 3 & 1) << 7;
    *(byte *)(param_1 + 0x25) = *(byte *)(param_1 + 0x25) & 0xef;
    Aska::AofObject::UpdateBoundingVolumes(Aska::AofHandler*)(param_1);
    plVar14 = (long *)param_1[0x7b];
    if ((plVar14[0x1a] == 0) || (*(short *)(plVar14[0x16] + 0x76) == 0)) {
      *(uint *)(param_1 + 0x33) = *(uint *)(param_1 + 0x33) & 0xfffffdff;
      lVar15 = param_1[0x30];
joined_r0x021c2ffc:
      if (lVar15 != 0) {
        *(uint *)(param_1 + 0x33) = *(uint *)(param_1 + 0x33) | 0x200;
      }
      Aska::TextureModifierManager::DeleteAll()(param_1 + 0x82);
      puVar10 = PTR__ZSt7nothrow_02cb9a80;
      if ((int)uVar11 != 0) {
        lVar15 = 0;
        do {
          lVar25 = *(long *)(*(long *)(lVar24 + 0x100) + lVar15 * 0x2a0);
          if (*(char *)(lVar25 + 0x1a) != '\0') {
            iVar19 = 0;
            lVar22 = *(int *)(lVar25 + 0x34) + lVar25;
            do {
              plVar14 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x68,puVar10);
              if (plVar14 == (long *)0x0) goto code_r0x021c3280;
              Aska::TextureReplaceAnimModifier::TextureReplaceAnimModifier(void*)(plVar14,lVar22);
              if ((char)plVar14[3] == '\0') {
                lVar24 = *plVar14;
                goto code_r0x021c3278;
              }
              lVar16 = param_1[0x84];
              iVar19 = iVar19 + 1;
              lVar22 = lVar22 + 0x10;
              plVar14[1] = lVar16;
              plVar14[2] = (long)(param_1 + 0x83);
              param_1[0x84] = (long)plVar14;
              *(long **)(lVar16 + 0x10) = plVar14;
              *(int *)(param_1 + 0x86) = (int)param_1[0x86] + 1;
            } while (iVar19 < (int)(uint)*(byte *)(lVar25 + 0x1a));
          }
          lVar15 = lVar15 + 1;
        } while (lVar15 < (long)uVar11);
      }
      uVar11 = Aska::FrameTextureModifier::CheckFrameTexture(Aska::MaterialList*, Aska::FrameTextureModifier**)(lVar13,&lStack_88);
      if ((uVar11 & 1) != 0) {
        if (lStack_88 == 0) goto code_r0x021c3280;
        lVar15 = param_1[0x84];
        *(long *)(lStack_88 + 8) = lVar15;
        *(long **)(lStack_88 + 0x10) = param_1 + 0x83;
        param_1[0x84] = lStack_88;
        *(long *)(lVar15 + 0x10) = lStack_88;
        *(int *)(param_1 + 0x86) = (int)param_1[0x86] + 1;
      }
      uVar11 = Aska::TextureShaderAdapter::CheckGlobalTexture(Aska::MaterialList*)(lVar13);
      if ((uVar11 & 1) == 0) {
code_r0x021c3190:
        *(undefined2 *)((long)param_1 + 0x38e) = 0;
        uVar11 = ((ulong)*(ushort *)((long)param_1 + 0x37c) & 0xfffffffe) << 0x20;
        uVar23 = (ulong)CONCAT24(*(ushort *)(lVar24 + 0x108) >> 0xc,(uint)*puVar1);
        uVar17 = uVar11 | uVar23 & 0x1ffffffff;
        *(uint *)puVar1 = (uint)*puVar1;
        uVar5 = (undefined2)(uVar17 >> 0x20);
        *(undefined2 *)((long)param_1 + 0x37c) = uVar5;
        if (param_1[0x74] != 0) {
          uVar23 = uVar23 & 0x1ffffffbf;
          uVar17 = uVar11 | uVar23;
          *(undefined2 *)((long)param_1 + 0x37c) = uVar5;
          *(uint *)puVar1 = (uint)uVar23;
        }
        if ((int)param_1[0x86] != 0) {
          *(short *)((long)param_1 + 0x37c) = (short)(uVar17 >> 0x20);
          *(uint *)puVar1 = (uint)uVar17 & 0xffffffbf;
        }
        uVar11 = (**(code **)(*(long *)param_1[0x7b] + 0x30))();
        if ((uVar11 & 1) != 0) {
          if ((*(byte *)(param_1[0x7b] + 0x350) & 1) != 0) {
            *(uint *)puVar1 = (uint)*puVar1 & 0xffffffbf;
          }
          if ((*(byte *)(*(long *)(param_1[0x7b] + 0xb0) + 0x7c) & 0xc0) == 0x80) {
            *(uint *)(param_1 + 0x33) = *(uint *)(param_1 + 0x33) | 0x400000;
          }
        }
        (**(code **)(*param_1 + 0xb0))(param_1);
        lVar24 = *(long *)(param_1[0x7b] + 800);
        if (lVar24 == 0) {
          *(long **)(param_1[0x7b] + 800) = param_1;
          lVar24 = param_1[0x73];
        }
        else {
          lVar13 = *(long *)(lVar24 + 0x4f8);
          *(long **)(lVar24 + 0x4f8) = param_1;
          param_1[0xa0] = lVar24;
          param_1[0x9f] = lVar13;
          *(long **)(lVar13 + 0x500) = param_1;
          lVar24 = param_1[0x73];
        }
        if ((lVar24 == 0) && (lVar24 = param_1[0x7b], lVar24 != 0)) {
          for (lVar13 = *(long *)(lVar24 + 0x138); lVar24 + 0x128 != lVar13;
              lVar13 = *(long *)(lVar13 + 0x10)) {
            if ((*(short *)(lVar13 + 0x7a) == 0) &&
               (piVar20 = (int *)(lVar13 + 0x90), *piVar20 == 0)) {
              Aska::RenderPassManager::InvalidateAll()(lVar13);
              goto code_r0x021c3344;
            }
          }
          plVar14 = (long *)(lVar24 + 0x120);
          lVar13 = Aska::RenderPassManagerList::CreateCopy()(plVar14);
          if (lVar13 != 0) {
            (**(code **)(*plVar14 + 0x10))(plVar14,lVar13);
            piVar20 = (int *)(lVar13 + 0x90);
code_r0x021c3344:
            *piVar20 = 0x1000000;
          }
          param_1[0x73] = lVar13;
        }
        lVar13 = _UNK_029c6988;
        lVar24 = _UNK_029c6980;
        *(int *)(param_1[0x7b] + 8) = *(int *)(param_1[0x7b] + 8) + 1;
        *(char *)(param_1[0x7b] + 0xa9) = *(char *)(param_1[0x7b] + 0xa9) + '\x01';
        param_1[0x7f] = lVar13;
        param_1[0x7e] = lVar24;
        param_1[0x8a] = 0;
        param_1[0x89] = 0;
        param_1[0x88] = 0;
        param_1[0x87] = 0;
        uVar9 = *puVar1;
        *(uint *)puVar1 = (uint)((ulong)uVar9 & 0xfff9c7ffffff);
        *(short *)((long)param_1 + 0x37c) = (short)(((ulong)uVar9 & 0xfff9c7ffffff) >> 0x20);
        param_1[0x6e] = 0;
        return 1;
      }
      plVar14 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x150,PTR__ZSt7nothrow_02cb9a80);
      if (plVar14 != (long *)0x0) {
        *(undefined2 *)((long)plVar14 + 0x14) = 0;
        *(undefined4 *)(plVar14 + 2) = 0;
        puVar10 = PTR__ZTVN4Aska20TextureShaderAdapterE_02cbedb0;
        *(undefined2 *)(plVar14 + 4) = 2;
        *(undefined2 *)(plVar14 + 0xd) = 0x10;
        *(undefined2 *)(plVar14 + 0x18) = 8;
        plVar14[3] = 0;
        *(undefined2 *)((long)plVar14 + 0x22) = 0;
        plVar14[5] = 0;
        plVar14[0xc] = 0;
        *(undefined2 *)((long)plVar14 + 0x6a) = 0;
        plVar14[0xe] = 0;
        plVar14[0x17] = 0;
        *(undefined2 *)((long)plVar14 + 0xc2) = 0;
        plVar14[1] = (long)(puVar10 + 0x78);
        *plVar14 = (long)(puVar10 + 0x10);
        plVar14[0x19] = 0;
        uVar11 = Aska::TextureShaderAdapter::Init(Aska::MaterialList*)(plVar14,lVar13);
        if ((uVar11 & 1) != 0) {
          Aska::AofObject::AddStandingShaderAdapter(Aska::BaseShaderAdapter*)(param_1,plVar14 + 1);
          goto code_r0x021c3190;
        }
        lVar24 = *plVar14;
code_r0x021c3278:
        (**(code **)(lVar24 + 8))(plVar14);
      }
    }
    else {
      lVar15 = (**(code **)(*plVar14 + 0x68))();
      param_1[0x74] = lVar15;
      if (lVar15 != 0) {
        *(uint *)(param_1 + 0x33) = *(uint *)(param_1 + 0x33) | 0x200;
        *(uint *)puVar1 = (uint)*puVar1 & 0xfffffeff;
        (**(code **)(*(long *)param_1[0x7b] + 0x48))((long *)param_1[0x7b],param_1);
        lVar15 = param_1[0x30];
        goto joined_r0x021c2ffc;
      }
    }
code_r0x021c3280:
    if (param_1[0x78] == 0) goto code_r0x021c3290;
    operator delete[](void*)();
  }
  else {
    lVar13 = operator new[](unsigned long, unsigned long, bool)(0x3520,0x10,1);
    if (lVar13 != 0) {
      param_1[0x78] = lVar13;
      *(uint *)puVar1 = (uint)*puVar1 & 0xffffffbf;
      goto code_r0x021c2f18;
    }
  }
  param_1[0x78] = 0;
code_r0x021c3290:
  if ((long *)param_1[0x74] != (long *)0x0) {
    (**(code **)(*(long *)param_1[0x74] + 8))();
    param_1[0x74] = 0;
  }
  Aska::TextureModifierManager::DeleteAll()(param_1 + 0x82);
  param_1[0x7b] = 0;
  return 0;
}

// ==== Aska::AofObject::UpdateBoundingVolumes(Aska::AofHandler*)
// vaddr 0x20c33e0 | ghidra 0x21c33e0 | size 240 | symbol _ZN4Aska9AofObject21UpdateBoundingVolumesEPNS_10AofHandlerE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska9AofObject21UpdateBoundingVolumesEPNS_10AofHandlerE(long param_1,long param_2)

{
  undefined4 uVar1;
  long lVar2;
  
  if ((*(uint *)(param_1 + 0x378) >> 7 & 1) != 0) {
    lVar2 = *(long *)(param_2 + 0xb0);
    *(undefined4 *)(param_1 + 800) = *(undefined4 *)(lVar2 + 0x20);
    *(undefined4 *)(param_1 + 0x324) = *(undefined4 *)(lVar2 + 0x24);
    *(undefined4 *)(param_1 + 0x328) = *(undefined4 *)(lVar2 + 0x28);
    *(undefined4 *)(param_1 + 0x32c) = *(undefined4 *)(lVar2 + 0x2c);
    *(undefined4 *)(param_1 + 0x340) = *(undefined4 *)(lVar2 + 0x30);
    *(undefined4 *)(param_1 + 0x344) = *(undefined4 *)(lVar2 + 0x34);
    uVar1 = *(undefined4 *)(lVar2 + 0x38);
    *(undefined4 *)(param_1 + 0x34c) = 0;
    *(undefined4 *)(param_1 + 0x348) = uVar1;
    *(undefined4 *)(param_1 + 0x350) = *(undefined4 *)(lVar2 + 0x40);
    *(undefined4 *)(param_1 + 0x354) = *(undefined4 *)(lVar2 + 0x44);
    uVar1 = *(undefined4 *)(lVar2 + 0x48);
    *(undefined4 *)(param_1 + 0x35c) = 0;
    *(undefined4 *)(param_1 + 0x358) = uVar1;
    *(undefined4 *)(param_1 + 0x360) = *(undefined4 *)(lVar2 + 0x50);
    *(undefined4 *)(param_1 + 0x364) = *(undefined4 *)(lVar2 + 0x54);
    uVar1 = *(undefined4 *)(lVar2 + 0x58);
    *(undefined4 *)(param_1 + 0x36c) = 0;
    *(undefined4 *)(param_1 + 0x368) = uVar1;
    *(undefined4 *)(param_1 + 0x330) = *(undefined4 *)(lVar2 + 0x60);
    *(undefined4 *)(param_1 + 0x334) = *(undefined4 *)(lVar2 + 100);
    *(undefined4 *)(param_1 + 0x338) = *(undefined4 *)(lVar2 + 0x68);
    *(undefined4 *)(param_1 + 0x33c) = *(undefined4 *)(lVar2 + 0x6c);
    *(undefined4 *)(param_1 + 0x510) = *(undefined4 *)(lVar2 + 0x60);
    *(undefined4 *)(param_1 + 0x514) = *(undefined4 *)(lVar2 + 100);
    *(undefined4 *)(param_1 + 0x518) = *(undefined4 *)(lVar2 + 0x68);
    *(undefined4 *)(param_1 + 0x51c) = *(undefined4 *)(lVar2 + 0x6c);
  }
  lVar2 = *(long *)(param_2 + 0xb0);
  *(undefined4 *)(param_1 + 0x310) = *(undefined4 *)(lVar2 + 0x10);
  *(undefined4 *)(param_1 + 0x314) = *(undefined4 *)(lVar2 + 0x14);
  *(undefined4 *)(param_1 + 0x318) = *(undefined4 *)(lVar2 + 0x18);
  *(undefined4 *)(param_1 + 0x31c) = *(undefined4 *)(lVar2 + 0x1c);
  return;
}

// ==== Aska::AofObject::AddStandingShaderAdapter(Aska::BaseShaderAdapter*)
// vaddr 0x20c34d0 | ghidra 0x21c34d0 | size 264 | symbol _ZN4Aska9AofObject24AddStandingShaderAdapterEPNS_17BaseShaderAdapterE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska9AofObject24AddStandingShaderAdapterEPNS_17BaseShaderAdapterE
               (long param_1,long param_2)

{
  long lVar1;
  long *plVar2;
  ushort uVar3;
  long lVar4;
  long lVar5;
  long lVar6;
  
  uVar3 = *(ushort *)(param_1 + 0x65a);
  lVar1 = (ulong)uVar3 + 1;
  if (uVar3 < *(ushort *)(param_1 + 0x658)) {
    lVar6 = *(long *)(param_1 + 0x650);
  }
  else {
    lVar4 = *(long *)(param_1 + 0x650);
    lVar6 = *(long *)(param_1 + 0x660);
    lVar5 = lVar1 * 0x10;
    if (lVar4 == 0) {
      if (lVar6 == 0) {
        lVar6 = operator new[](unsigned long, std::nothrow_t const&)(lVar5,PTR__ZSt7nothrow_02cb9a80);
      }
      else {
        lVar6 = Aska::MemoryManager::Malloc(unsigned long)();
      }
      if (lVar6 != 0) {
        memcpy(lVar6,param_1 + 0x668,(ulong)*(ushort *)(param_1 + 0x65a) << 3);
      }
    }
    else if (lVar6 == 0) {
      lVar6 = operator new[](unsigned long, void*, unsigned long)(lVar5,lVar4,4);
    }
    else {
      lVar6 = Aska::MemoryManager::Realloc(unsigned long, void*, long)(lVar6,lVar5,lVar4,4);
    }
    if (lVar6 == 0) goto code_r0x021c35bc;
    *(long *)(param_1 + 0x650) = lVar6;
    *(short *)(param_1 + 0x658) = (short)((int)lVar1 << 1);
  }
  lVar5 = (ulong)uVar3 * 8;
  plVar2 = (long *)(param_1 + lVar5 + 0x668);
  if (lVar6 != 0) {
    plVar2 = (long *)(lVar6 + lVar5);
  }
  *(short *)(param_1 + 0x65a) = (short)lVar1;
  *plVar2 = param_2;
code_r0x021c35bc:
  *(short *)(param_2 + 10) = *(short *)(param_2 + 10) + 1;
  return;
}

// ==== Aska::AofObject::CheckRenderContexts()
// vaddr 0x20c35d8 | ghidra 0x21c35d8 | size 428 | symbol _ZN4Aska9AofObject19CheckRenderContextsEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska9AofObject19CheckRenderContextsEv(long param_1)

{
  ushort uVar1;
  uint uVar2;
  undefined *puVar3;
  undefined *puVar4;
  long lVar5;
  long *plVar6;
  long lVar7;
  ulong uVar8;
  int *piVar9;
  
  uVar1 = *(ushort *)(param_1 + 0x1b5);
  if ((uVar1 >> 2 & 1) != 0) {
    return;
  }
  *(ushort *)(param_1 + 0x1b5) = uVar1 | 4;
  puVar4 = PTR__ZN4Aska6Global18m_pRenderStatePoolE_02cbf5f0;
  *(int *)(param_1 + 0x3b0) = *(int *)(param_1 + 0x3b0) + 1;
  puVar3 = PTR__ZN4Aska9AofObject21m_ucDiscardResourceThE_02cb8538;
  lVar5 = *(long *)puVar4;
  *(int *)(lVar5 + 0x50) = *(int *)(lVar5 + 0x44) * 9;
  uVar2 = 0;
  if (*(uint *)(lVar5 + 0x54) != 0) {
    uVar2 = (uint)(*(int *)(lVar5 + 0x44) * 900) / *(uint *)(lVar5 + 0x54);
  }
  if (uVar2 <= (byte)*puVar3) {
    return;
  }
  if (*(uint *)(param_1 + 0x3b0) < *(uint *)PTR__ZN4Aska9AofObject21m_uiDiscardCountLimitE_02cbf3e0)
  {
    return;
  }
  plVar6 = *(long **)(param_1 + 0x398);
  if (plVar6 != (long *)0x0) {
    lVar5 = *(long *)(param_1 + 0x3d8);
    if (lVar5 == 0) goto code_r0x021c3714;
    (**(code **)(*(long *)(lVar5 + 0x120) + 0x28))(lVar5 + 0x120,plVar6);
    (**(code **)(*plVar6 + 8))(plVar6);
    *(undefined8 *)(param_1 + 0x398) = 0;
  }
  lVar5 = *(long *)(param_1 + 0x3d8);
  if (lVar5 != 0) {
    for (lVar7 = *(long *)(lVar5 + 0x138); lVar5 + 0x128 != lVar7; lVar7 = *(long *)(lVar7 + 0x10))
    {
      if ((*(short *)(lVar7 + 0x7a) == 0) && (piVar9 = (int *)(lVar7 + 0x90), *piVar9 == 0)) {
        Aska::RenderPassManager::InvalidateAll()(lVar7);
        goto code_r0x021c3708;
      }
    }
    plVar6 = (long *)(lVar5 + 0x120);
    lVar7 = Aska::RenderPassManagerList::CreateCopy()(plVar6);
    if (lVar7 != 0) {
      (**(code **)(*plVar6 + 0x10))(plVar6,lVar7);
      piVar9 = (int *)(lVar7 + 0x90);
code_r0x021c3708:
      *piVar9 = 0x1000000;
    }
    *(long *)(param_1 + 0x398) = lVar7;
  }
code_r0x021c3714:
  uVar8 = (ulong)*(ushort *)(param_1 + 0x462);
  if (uVar8 != 0) {
    lVar5 = 0;
    do {
      lVar7 = param_1 + 0x470;
      if (*(long *)(param_1 + 0x458) != 0) {
        lVar7 = *(long *)(param_1 + 0x458);
      }
      plVar6 = (long *)(lVar7 + lVar5);
      if (*plVar6 != 0) {
        Aska::RenderState::Release()();
        *plVar6 = 0;
      }
      if (plVar6[1] != 0) {
        Aska::RenderState::Release()();
        plVar6[1] = 0;
      }
      uVar8 = uVar8 - 1;
      lVar5 = lVar5 + 0x20;
      *(undefined1 *)((long)plVar6 + 0x1a) = 0;
    } while (uVar8 != 0);
  }
  *(uint *)(param_1 + 0x198) = *(uint *)(param_1 + 0x198) & 0xfdffffff;
  return;
}

// ==== Aska::AofObject::FlushRenderPassManager_unsafe()
// vaddr 0x20c3784 | ghidra 0x21c3784 | size 208 | symbol _ZN4Aska9AofObject29FlushRenderPassManager_unsafeEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska9AofObject29FlushRenderPassManager_unsafeEv(long param_1)

{
  long lVar1;
  long *plVar2;
  long lVar3;
  int *piVar4;
  
  plVar2 = *(long **)(param_1 + 0x398);
  if (plVar2 != (long *)0x0) {
    lVar1 = *(long *)(param_1 + 0x3d8);
    if (lVar1 == 0) {
      return;
    }
    (**(code **)(*(long *)(lVar1 + 0x120) + 0x28))(lVar1 + 0x120,plVar2);
    (**(code **)(*plVar2 + 8))(plVar2);
    *(undefined8 *)(param_1 + 0x398) = 0;
  }
  lVar1 = *(long *)(param_1 + 0x3d8);
  if (lVar1 != 0) {
    for (lVar3 = *(long *)(lVar1 + 0x138); lVar1 + 0x128 != lVar3; lVar3 = *(long *)(lVar3 + 0x10))
    {
      if ((*(short *)(lVar3 + 0x7a) == 0) && (piVar4 = (int *)(lVar3 + 0x90), *piVar4 == 0)) {
        Aska::RenderPassManager::InvalidateAll()(lVar3);
        goto code_r0x021c383c;
      }
    }
    plVar2 = (long *)(lVar1 + 0x120);
    lVar3 = Aska::RenderPassManagerList::CreateCopy()(plVar2);
    if (lVar3 != 0) {
      (**(code **)(*plVar2 + 0x10))(plVar2,lVar3);
      piVar4 = (int *)(lVar3 + 0x90);
code_r0x021c383c:
      *piVar4 = 0x1000000;
    }
    *(long *)(param_1 + 0x398) = lVar3;
  }
  return;
}

// ==== Aska::AofObject::FlushRenderPassManager()
// vaddr 0x20c3854 | ghidra 0x21c3854 | size 224 | symbol _ZN4Aska9AofObject22FlushRenderPassManagerEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska9AofObject22FlushRenderPassManagerEv(long param_1)

{
  long *plVar1;
  long lVar2;
  long lVar3;
  int *piVar4;
  
  lVar3 = *(long *)(param_1 + 0x398);
  if (lVar3 != 0) {
    lVar2 = *(long *)(param_1 + 0x3d8);
    if (lVar2 == 0) {
      return;
    }
    (**(code **)(*(long *)(lVar2 + 0x120) + 0x28))(lVar2 + 0x120,lVar3);
    Aska::DeleteManager::AddMain(void*, unsigned char, unsigned char, Aska::IDeleteHandler*)(PTR__ZN4Aska6Global21m_systemDeleteManagerE_02cb77c0,lVar3,0,0,
                    PTR__ZN4Aska21RenderPassManagerList15m_deleteHandlerE_02cc49e8);
    *(undefined8 *)(param_1 + 0x398) = 0;
  }
  lVar3 = *(long *)(param_1 + 0x3d8);
  if (lVar3 != 0) {
    for (lVar2 = *(long *)(lVar3 + 0x138); lVar3 + 0x128 != lVar2; lVar2 = *(long *)(lVar2 + 0x10))
    {
      if ((*(short *)(lVar2 + 0x7a) == 0) && (piVar4 = (int *)(lVar2 + 0x90), *piVar4 == 0)) {
        Aska::RenderPassManager::InvalidateAll()(lVar2);
        goto code_r0x021c391c;
      }
    }
    plVar1 = (long *)(lVar3 + 0x120);
    lVar2 = Aska::RenderPassManagerList::CreateCopy()(plVar1);
    if (lVar2 != 0) {
      (**(code **)(*plVar1 + 0x10))(plVar1,lVar2);
      piVar4 = (int *)(lVar2 + 0x90);
code_r0x021c391c:
      *piVar4 = 0x1000000;
    }
    *(long *)(param_1 + 0x398) = lVar2;
  }
  return;
}

// ==== Aska::AofObject::Clone(Aska::IAnimatable const*)
// vaddr 0x20c3934 | ghidra 0x21c3934 | size 72 | symbol _ZN4Aska9AofObject5CloneEPKNS_11IAnimatableE | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska9AofObject5CloneEPKNS_11IAnimatableE(long *param_1,undefined8 param_2)

{
  ulong uVar1;
  undefined8 uVar2;
  
  uVar1 = Aska::RenderableObject::Clone(Aska::IAnimatable const*)();
  if ((uVar1 & 1) != 0) {
                    /* WARNING: Could not recover jumptable at 0x021c3968. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar2 = (**(code **)(*param_1 + 0x2d8))(param_1,param_2,0);
    return uVar2;
  }
  return 0;
}

// ==== Aska::AofObject::CreateClone(Aska::IAnimatable const*)
// vaddr 0x20c397c | ghidra 0x21c397c | size 104 | symbol _ZN4Aska9AofObject11CreateCloneEPKNS_11IAnimatableE | lib libSOA-3.7.0.so | 2026-10-04
long * _ZN4Aska9AofObject11CreateCloneEPKNS_11IAnimatableE(undefined8 param_1,undefined8 param_2)

{
  long *plVar1;
  ulong uVar2;
  
  plVar1 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x6b0,PTR__ZSt7nothrow_02cb9a80);
  if (plVar1 != (long *)0x0) {
    Aska::AofObject::AofObject()(plVar1);
    uVar2 = (**(code **)(*plVar1 + 0x18))(plVar1,param_2);
    if ((uVar2 & 1) == 0) {
      (**(code **)(*plVar1 + 8))(plVar1);
      plVar1 = (long *)0x0;
    }
  }
  return plVar1;
}

// ==== Aska::AofObject::Clone(Aska::AofObject const*, int)
// vaddr 0x20c39e4 | ghidra 0x21c39e4 | size 1064 | symbol _ZN4Aska9AofObject5CloneEPKS0_i | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska9AofObject5CloneEPKS0_i(long *param_1,long *param_2,int param_3)

{
  uint *puVar1;
  uint6 *puVar2;
  char cVar3;
  char cVar4;
  char cVar5;
  char cVar6;
  char cVar7;
  uint uVar8;
  uint6 uVar9;
  long *plVar10;
  undefined4 *puVar11;
  undefined8 uVar12;
  long lVar13;
  uint uVar14;
  ulong uVar15;
  ulong uVar16;
  code *pcVar17;
  
  if (param_3 - 1U < 2) {
    plVar10 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x330,PTR__ZSt7nothrow_02cb9a80);
    if (plVar10 == (long *)0x0) {
      return 0;
    }
    Aska::AofHandler::AofHandler()(plVar10);
    if (param_3 == 2) {
      (**(code **)(*plVar10 + 0x18))(plVar10,*(undefined8 *)(param_2[0x7b] + 0xb0),0,0,0);
    }
    else {
      (**(code **)(*plVar10 + 0x28))(plVar10,param_2[0x7b],1);
    }
    lVar13 = *param_1;
  }
  else {
    if (param_3 != 0) {
      return 0;
    }
    lVar13 = *param_1;
    plVar10 = (long *)param_2[0x7b];
  }
  (**(code **)(lVar13 + 0x2d0))(param_1,plVar10,1);
  uVar9 = *(uint6 *)(param_1 + 0x6f);
  puVar1 = (uint *)(param_2 + 0x6f);
  uVar16 = (ulong)uVar9;
  puVar2 = (uint6 *)(param_1 + 0x6f);
  if ((*(uint *)(param_2 + 0x6f) >> 1 & 1) != ((uint)(uVar9 >> 1) & 1)) {
    uVar16 = (ulong)(uint)*(uint6 *)(param_1 + 0x6f) & 0xfffffffffffffffd |
             (ulong)*(ushort *)((long)param_1 + 0x37c) << 0x20 |
             (ulong)*(uint *)(param_2 + 0x6f) & 2;
    *(uint *)puVar2 = (uint)uVar16;
    *(short *)((long)param_1 + 0x37c) = (short)(uVar9 >> 0x20);
    uVar15 = (ulong)*(ushort *)((long)param_1 + 0x462);
    if (uVar15 != 0) {
      lVar13 = 0;
      do {
        uVar15 = uVar15 - 1;
        plVar10 = param_1 + 0x8e;
        if ((long *)param_1[0x8b] != (long *)0x0) {
          plVar10 = (long *)param_1[0x8b];
        }
        *(undefined1 *)((long)plVar10 + lVar13 + 0x1a) = 0;
        lVar13 = lVar13 + 0x20;
      } while (uVar15 != 0);
      uVar16 = (ulong)*puVar2;
    }
  }
  uVar14 = *puVar1;
  *(short *)((long)param_1 + 0x37c) = (short)(uVar16 >> 0x20);
  uVar14 = (uint)(uVar16 & 0xfffffffffffffff0) | (uint)uVar16 & 7 | (uVar14 >> 3 & 1) << 3;
  *(uint *)puVar2 = uVar14;
  if ((*puVar1 >> 0xb & 1) != 0) {
    cVar3 = *(char *)((long)param_2 + 0x389);
    cVar4 = *(char *)((long)param_2 + 0x38a);
    cVar5 = *(char *)((long)param_2 + 0x38b);
    cVar6 = *(char *)((long)param_2 + 0x38c);
    cVar7 = *(char *)((long)param_2 + 0x38d);
    if (((((((uint)uVar16 >> 0xb & 1) == 0) || (*(char *)((long)param_1 + 0x389) != cVar3)) ||
         (*(char *)((long)param_1 + 0x38a) != cVar4)) ||
        ((*(char *)((long)param_1 + 0x38b) != cVar5 || (*(char *)((long)param_1 + 0x38c) != cVar6)))
        ) || (*(char *)((long)param_1 + 0x38d) != cVar7)) {
      *(short *)((long)param_1 + 0x37c) = (short)((uVar16 & 0xfffffffffffffff0) >> 0x20);
      *(uint *)puVar2 = uVar14 | 0x800;
      uVar16 = (ulong)*(ushort *)((long)param_1 + 0x462);
      *(char *)((long)param_1 + 0x389) = cVar3;
      *(char *)((long)param_1 + 0x38a) = cVar4;
      *(char *)((long)param_1 + 0x38b) = cVar5;
      *(char *)((long)param_1 + 0x38c) = cVar6;
      *(char *)((long)param_1 + 0x38d) = cVar7;
      if (uVar16 != 0) {
        lVar13 = 0;
        do {
          uVar16 = uVar16 - 1;
          plVar10 = param_1 + 0x8e;
          if ((long *)param_1[0x8b] != (long *)0x0) {
            plVar10 = (long *)param_1[0x8b];
          }
          *(undefined1 *)((long)plVar10 + lVar13 + 0x1a) = 0;
          lVar13 = lVar13 + 0x20;
        } while (uVar16 != 0);
      }
    }
  }
  if ((*puVar1 >> 0xc & 1) != 0) {
    cVar3 = *(char *)((long)param_2 + 0x382);
    cVar4 = *(char *)((long)param_2 + 899);
    if (((((uint)*puVar2 >> 0xc & 1) == 0) || (*(char *)((long)param_1 + 0x382) != cVar3)) ||
       (*(char *)((long)param_1 + 899) != cVar4)) {
      *(undefined2 *)((long)param_1 + 0x37c) = *(undefined2 *)((long)param_1 + 0x37c);
      *(uint *)puVar2 = (uint)*puVar2 | 0x1000;
      uVar16 = (ulong)*(ushort *)((long)param_1 + 0x462);
      *(char *)((long)param_1 + 0x382) = cVar3;
      *(char *)((long)param_1 + 899) = cVar4;
      if (uVar16 != 0) {
        lVar13 = 0;
        do {
          uVar16 = uVar16 - 1;
          plVar10 = param_1 + 0x8e;
          if ((long *)param_1[0x8b] != (long *)0x0) {
            plVar10 = (long *)param_1[0x8b];
          }
          *(undefined1 *)((long)plVar10 + lVar13 + 0x1a) = 0;
          lVar13 = lVar13 + 0x20;
        } while (uVar16 != 0);
      }
    }
  }
  if ((*puVar1 >> 0xd & 1) != 0) {
    uVar14 = (uint)*puVar2;
    uVar8 = uVar14 >> 0xd & 1;
    if (((uVar14 >> 0xd & 1) == 0) || (uVar8 != *(byte *)((long)param_1 + 900))) {
      *(undefined2 *)((long)param_1 + 0x37c) = *(undefined2 *)((long)param_1 + 0x37c);
      *(uint *)puVar2 = uVar14 | 0x2000;
      uVar16 = (ulong)*(ushort *)((long)param_1 + 0x462);
      *(char *)((long)param_1 + 900) = (char)uVar8;
      if (uVar16 != 0) {
        lVar13 = 0;
        do {
          uVar16 = uVar16 - 1;
          plVar10 = param_1 + 0x8e;
          if ((long *)param_1[0x8b] != (long *)0x0) {
            plVar10 = (long *)param_1[0x8b];
          }
          *(undefined1 *)((long)plVar10 + lVar13 + 0x1a) = 0;
          lVar13 = lVar13 + 0x20;
        } while (uVar16 != 0);
      }
    }
  }
  if (*(char *)((long)param_2 + 0x1b4) != *(char *)((long)param_1 + 0x1b4)) {
    (**(code **)(*param_1 + 0x248))(param_1);
  }
  Aska::AofObject::SetProgrammableForceOpaque(bool)(param_1,*puVar1 >> 0x10 & 1);
  puVar11 = (undefined4 *)(**(code **)(*param_2 + 0x218))(param_2);
  *(undefined4 *)(param_1 + 0xa4) = *puVar11;
  *(undefined4 *)((long)param_1 + 0x524) = puVar11[1];
  *(undefined4 *)(param_1 + 0xa5) = puVar11[2];
  *(undefined4 *)((long)param_1 + 0x52c) = puVar11[3];
  puVar11 = (undefined4 *)(**(code **)(*param_2 + 0x238))(param_2);
  *(undefined4 *)(param_1 + 0xa6) = *puVar11;
  *(undefined4 *)((long)param_1 + 0x534) = puVar11[1];
  *(undefined4 *)(param_1 + 0xa7) = puVar11[2];
  *(undefined4 *)((long)param_1 + 0x53c) = puVar11[3];
  pcVar17 = *(code **)(*param_1 + 0x200);
  uVar12 = (**(code **)(*param_2 + 0x208))(param_2);
  (*pcVar17)(param_1,uVar12);
  pcVar17 = *(code **)(*param_1 + 0x220);
  uVar12 = (**(code **)(*param_2 + 0x228))(param_2);
  (*pcVar17)(param_1,uVar12);
  lVar13 = param_2[200];
  param_1[0xc9] = param_2[0xc9];
  param_1[200] = lVar13;
  lVar13 = param_2[0xc6];
  param_1[199] = param_2[199];
  param_1[0xc6] = lVar13;
  lVar13 = param_2[0xc4];
  param_1[0xc5] = param_2[0xc5];
  param_1[0xc4] = lVar13;
  return 1;
}

// ==== Aska::AofObject::MakeObjectRenderStateShadow(Aska::AofObjectRenderState*, Aska::RenderPass*, bool)
// vaddr 0x20c3e0c | ghidra 0x21c3e0c | size 12 | symbol _ZN4Aska9AofObject27MakeObjectRenderStateShadowEPNS_20AofObjectRenderStateEPNS_10RenderPassEb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska9AofObject27MakeObjectRenderStateShadowEPNS_20AofObjectRenderStateEPNS_10RenderPassEb
               (void)

{
  uint in_w3;
  
  if ((in_w3 & 1) != 0) {
    (*(code *)
      PTR__ZN4Aska9AofObject21MakeObjectRenderStateILj1010EEEbPNS_20AofObjectRenderStateEPNS_10RenderPassE_02c96888
    )();
    return;
  }
  (*(code *)
    PTR__ZN4Aska9AofObject21MakeObjectRenderStateILj496EEEbPNS_20AofObjectRenderStateEPNS_10RenderPassE_02cb2198
  )();
  return;
}

// ==== bool Aska::AofObject::MakeObjectRenderState<1010u>(Aska::AofObjectRenderState*, Aska::RenderPass*)
// vaddr 0x20c3e18 | ghidra 0x21c3e18 | size 1176 | symbol _ZN4Aska9AofObject21MakeObjectRenderStateILj1010EEEbPNS_20AofObjectRenderStateEPNS_10RenderPassE | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska9AofObject21MakeObjectRenderStateILj1010EEEbPNS_20AofObjectRenderStateEPNS_10RenderPassE
          (long param_1,long *param_2,long param_3)

{
  uint *puVar1;
  uint uVar2;
  uint uVar3;
  long lVar4;
  undefined1 *puVar5;
  byte *pbVar6;
  uint uVar7;
  char cVar8;
  long lVar9;
  long lVar10;
  undefined8 *puVar11;
  undefined8 *puVar12;
  uint uVar13;
  long lVar14;
  uint uVar15;
  long lVar16;
  char cVar17;
  undefined8 uVar18;
  long lVar19;
  long *plVar20;
  ulong uVar21;
  long lVar22;
  
  lVar9 = *param_2;
  lVar10 = param_2[1];
  lVar22 = param_2[2];
  uVar18 = *(undefined8 *)PTR__ZN4Aska6Global21m_pRenderStateManagerE_02cc0c10;
  if (lVar9 == 0) {
code_r0x021c3e6c:
    lVar9 = Aska::RenderStateManager::Get(int)(uVar18,6);
    *param_2 = lVar9;
    if (lVar9 == 0) {
      return 0;
    }
  }
  else if (*(int *)(lVar9 + 0x10) < 6) {
    Aska::RenderState::Release()(lVar9);
    goto code_r0x021c3e6c;
  }
  Aska::RenderState::Reset()(lVar9);
  if (lVar10 == 0) {
code_r0x021c3ea4:
    lVar10 = Aska::RenderStateManager::Get(int)(uVar18,3);
    param_2[1] = lVar10;
    if (lVar10 == 0) {
      return 0;
    }
  }
  else if (*(int *)(lVar10 + 0x10) < 3) {
    Aska::RenderState::Release()(lVar10);
    goto code_r0x021c3ea4;
  }
  Aska::RenderState::Reset()(lVar10);
  Aska::RenderState::SetDepthBias(float, float)(0,0,lVar9);
  Aska::RenderState::EnableZTest(bool)(lVar9,1);
  Aska::RenderState::SetZTestFunction(int)(lVar9,3);
  Aska::RenderState::EnableZWrite(bool)(lVar9,1);
  puVar1 = (uint *)(param_1 + 0x378);
  uVar13 = (uint)*(undefined6 *)(param_1 + 0x378);
  if ((uVar13 >> 1 & 1) == 0) {
    if ((uVar13 >> 1 & 1) == 0) goto code_r0x021c3f14;
code_r0x021c3f44:
    Aska::RenderState::SetFillMode(int)(lVar10,2);
    uVar13 = (uint)*(undefined6 *)puVar1;
    if ((uVar13 >> 0xb & 1) == 0) goto code_r0x021c3f64;
code_r0x021c3f18:
    if ((uVar13 >> 0xc & 1) == 0) goto code_r0x021c3f1c;
code_r0x021c3f84:
    cVar17 = *(char *)(param_1 + 0x382);
    if (cVar17 == '\x01') {
      Aska::RenderState::EnableAlphaTest(bool)(lVar9,0);
      cVar17 = '\x02';
    }
    else {
      Aska::RenderState::SetAlphaTestFunction(int, int)(lVar9,cVar17,*(undefined1 *)(param_1 + 899));
    }
  }
  else {
    Aska::RenderState::SetFillMode(int)(lVar9,1);
    uVar13 = (uint)*(undefined6 *)puVar1;
    if ((uVar13 >> 1 & 1) != 0) goto code_r0x021c3f44;
code_r0x021c3f14:
    if ((uVar13 >> 0xb & 1) != 0) goto code_r0x021c3f18;
code_r0x021c3f64:
    Aska::RenderState::EnableStencil(Aska::StencilMode::Mode)(lVar9,0);
    if (((uint)*(undefined6 *)puVar1 >> 0xc & 1) != 0) goto code_r0x021c3f84;
code_r0x021c3f1c:
    cVar17 = '\x02';
  }
  if ((*puVar1 >> 0xc & 1) != 0) {
    Aska::RenderState::EnableAlphaTest(bool)(lVar10,1);
  }
  Aska::RenderState::SetAlphaTestFunction(int, int)(lVar10,2,0);
  if (*(long *)(*(long *)(param_1 + 0x3d8) + 0xd0) == 0) {
    uVar21 = 0;
  }
  else {
    uVar21 = (ulong)*(ushort *)(*(long *)(*(long *)(param_1 + 0x3d8) + 0xb0) + 0x70);
  }
  cVar8 = *(char *)(param_3 + 0x2b);
  uVar13 = (uint)uVar21;
  if (lVar22 == 0) {
    puVar11 = (undefined8 *)operator new(unsigned long, std::nothrow_t const&)(0x20,PTR__ZSt7nothrow_02cb9a80);
    if (puVar11 == (undefined8 *)0x0) {
code_r0x021c4058:
      param_2[2] = 0;
      return 0;
    }
    *puVar11 = 0;
    *(undefined2 *)(puVar11 + 1) = 0;
    if (uVar13 < 3) {
      puVar12 = puVar11 + 2;
      *puVar11 = puVar12;
    }
    else {
      puVar12 = (undefined8 *)operator new[](unsigned long, std::nothrow_t const&)(uVar13 << 3,PTR__ZSt7nothrow_02cb9a80);
      *puVar11 = puVar12;
      if (puVar12 == (undefined8 *)0x0) {
        operator delete(void*)(puVar11);
        goto code_r0x021c4058;
      }
    }
    *(short *)(puVar11 + 1) = (short)uVar21;
    memset(puVar12,0,uVar13 << 3);
    param_2[2] = (long)puVar11;
  }
  if (uVar13 != 0) {
    lVar22 = 0;
    lVar9 = 0;
    lVar10 = 0x58;
    plVar20 = (long *)param_2[2];
    do {
      if ((*(byte *)(*(long *)(param_3 + 8) + lVar10) >> 2 & 1) == 0) {
        lVar14 = *(long *)(*(long *)(param_1 + 0x3d8) + 0x100);
        if (lVar14 == 0) {
          lVar16 = 0;
        }
        else {
          lVar16 = *(long *)(lVar14 + lVar22);
        }
        lVar19 = *(long *)(*plVar20 + lVar9 * 8);
        lVar4 = 0;
        if (lVar14 != 0) {
          lVar4 = lVar14 + lVar22 + 0x10;
        }
        if (lVar19 == 0) {
          uVar18 = Aska::RenderStateManager::Get(int)(*(undefined8 *)
                                    PTR__ZN4Aska6Global21m_pRenderStateManagerE_02cc0c10,9);
          *(undefined8 *)(*plVar20 + lVar9 * 8) = uVar18;
          lVar19 = *(long *)(*plVar20 + lVar9 * 8);
          if (lVar19 == 0) {
            return 0;
          }
        }
        Aska::RenderState::Reset()(lVar19);
        uVar7 = *puVar1;
        uVar13 = (uint)*(undefined6 *)puVar1;
        puVar5 = (undefined1 *)(lVar4 + 0x231);
        if ((uVar7 & 0x1000) != 0) {
          puVar5 = (undefined1 *)(param_1 + 899);
        }
        pbVar6 = (byte *)(lVar4 + 0x232);
        if ((uVar7 & 0x2000) != 0) {
          pbVar6 = (byte *)(param_1 + 900);
        }
        uVar3 = (uint)CONCAT11(*puVar5,*(char *)(lVar16 + 0x14));
        uVar2 = (*pbVar6 & 3) << 0x11;
        uVar15 = uVar3 | uVar2;
        if ((*(char *)(lVar16 + 0x14) == '\0') && (*(byte *)(param_1 + 0x1b4) != 0)) {
          uVar15 = uVar3 & 0xfffeff00 | uVar2 | (uint)*(byte *)(param_1 + 0x1b4);
        }
        if (((uVar13 >> 0xd & 1) != 0) && (*(byte *)(param_1 + 900) != 0)) {
          uVar15 = uVar15 & 0xffffff00;
        }
        uVar2 = uVar15 & 0xffffff00 | 0x10;
        if ((uVar15 & 0xff) != 0 || cVar8 != '\x01') {
          uVar2 = uVar15;
        }
        if ((uVar7 & 0x10000) != 0) {
          uVar2 = uVar15 & 0xffffff00;
        }
        if ((uVar2 != 0xffffffff) && ((uVar2 >> 8 & 0x1ff) != 0x1ff)) {
          Aska::RenderState::SetAlphaTestFunction(int, int)(lVar19,cVar17);
          uVar13 = (uint)*(undefined6 *)puVar1;
        }
        if ((uVar13 >> 0xb & 1) != 0) {
          Aska::RenderState::EnableStencil(Aska::StencilMode::Mode)(lVar19,1);
          Aska::RenderState::SetStencilOp(int, int, int, int, int, short)(lVar19,*(undefined1 *)(param_1 + 0x389),*(undefined1 *)(param_1 + 0x38a),
                          *(undefined1 *)(param_1 + 0x38b),*(undefined1 *)(param_1 + 0x38c),
                          *(undefined1 *)(param_1 + 0x38d),*(undefined2 *)(param_1 + 0x6a8));
        }
        lVar14 = *(long *)(*plVar20 + lVar9 * 8);
        if ((lVar14 != 0) && (*(int *)(lVar14 + 0x14) == 0)) {
          Aska::RenderState::Release()();
          *(undefined8 *)(*plVar20 + lVar9 * 8) = 0;
        }
      }
      lVar9 = lVar9 + 1;
      lVar10 = lVar10 + 0x1b8;
      lVar22 = lVar22 + 0x2a0;
    } while (lVar9 < (long)uVar21);
  }
  Aska::RenderPassManager::InvalidateObjectRenderState()(*(undefined8 *)(param_1 + 0x398));
  *(undefined1 *)((long)param_2 + 0x1a) = 1;
  return 1;
}

// ==== bool Aska::AofObject::MakeObjectRenderState<496u>(Aska::AofObjectRenderState*, Aska::RenderPass*)
// vaddr 0x20c42b0 | ghidra 0x21c42b0 | size 368 | symbol _ZN4Aska9AofObject21MakeObjectRenderStateILj496EEEbPNS_20AofObjectRenderStateEPNS_10RenderPassE | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska9AofObject21MakeObjectRenderStateILj496EEEbPNS_20AofObjectRenderStateEPNS_10RenderPassE
          (long param_1,long *param_2)

{
  long lVar1;
  long lVar2;
  uint uVar3;
  undefined8 uVar4;
  
  lVar1 = *param_2;
  lVar2 = param_2[1];
  uVar4 = *(undefined8 *)PTR__ZN4Aska6Global21m_pRenderStateManagerE_02cc0c10;
  if (lVar1 == 0) {
code_r0x021c42ec:
    lVar1 = Aska::RenderStateManager::Get(int)(uVar4,6);
    *param_2 = lVar1;
    if (lVar1 == 0) {
      return 0;
    }
  }
  else if (*(int *)(lVar1 + 0x10) < 6) {
    Aska::RenderState::Release()(lVar1);
    goto code_r0x021c42ec;
  }
  Aska::RenderState::Reset()(lVar1);
  if (lVar2 != 0) {
    if (1 < *(int *)(lVar2 + 0x10)) goto code_r0x021c433c;
    Aska::RenderState::Release()(lVar2);
  }
  lVar2 = Aska::RenderStateManager::Get(int)(uVar4,2);
  param_2[1] = lVar2;
  if (lVar2 == 0) {
    return 0;
  }
code_r0x021c433c:
  Aska::RenderState::Reset()(lVar2);
  Aska::RenderState::SetDepthBias(float, float)(0,0,lVar1);
  Aska::RenderState::EnableZTest(bool)(lVar1,1);
  Aska::RenderState::SetZTestFunction(int)(lVar1,3);
  Aska::RenderState::EnableZWrite(bool)(lVar1,1);
  uVar3 = (uint)*(undefined6 *)(param_1 + 0x378);
  if ((uVar3 >> 1 & 1) != 0) {
    Aska::RenderState::SetFillMode(int)(lVar1,1);
    uVar3 = (uint)*(undefined6 *)(param_1 + 0x378);
  }
  if ((uVar3 >> 1 & 1) != 0) {
    Aska::RenderState::SetFillMode(int)(lVar2,2);
    uVar3 = (uint)*(undefined6 *)(param_1 + 0x378);
  }
  if ((uVar3 >> 0xb & 1) == 0) {
    Aska::RenderState::EnableStencil(Aska::StencilMode::Mode)(lVar1,0);
  }
  Aska::RenderState::EnableAlphaTest(bool)(lVar1,0);
  Aska::RenderState::EnableAlphaTest(bool)(lVar2,1);
  Aska::RenderPassManager::InvalidateObjectRenderState()(*(undefined8 *)(param_1 + 0x398));
  *(undefined1 *)((long)param_2 + 0x1a) = 1;
  return 1;
}

// ==== Aska::AofObject::MakeObjectRenderStateOMB(Aska::AofObjectRenderState*, Aska::RenderPass*, bool)
// vaddr 0x20c4420 | ghidra 0x21c4420 | size 12 | symbol _ZN4Aska9AofObject24MakeObjectRenderStateOMBEPNS_20AofObjectRenderStateEPNS_10RenderPassEb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska9AofObject24MakeObjectRenderStateOMBEPNS_20AofObjectRenderStateEPNS_10RenderPassEb
               (void)

{
  uint in_w3;
  
  if ((in_w3 & 1) != 0) {
    (*(code *)
      PTR__ZN4Aska9AofObject21MakeObjectRenderStateILj2027EEEbPNS_20AofObjectRenderStateEPNS_10RenderPassE_02c99300
    )();
    return;
  }
  (*(code *)
    PTR__ZN4Aska9AofObject21MakeObjectRenderStateILj1514EEEbPNS_20AofObjectRenderStateEPNS_10RenderPassE_02cb20a8
  )();
  return;
}

// ==== bool Aska::AofObject::MakeObjectRenderState<2027u>(Aska::AofObjectRenderState*, Aska::RenderPass*)
// vaddr 0x20c442c | ghidra 0x21c442c | size 1344 | symbol _ZN4Aska9AofObject21MakeObjectRenderStateILj2027EEEbPNS_20AofObjectRenderStateEPNS_10RenderPassE | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska9AofObject21MakeObjectRenderStateILj2027EEEbPNS_20AofObjectRenderStateEPNS_10RenderPassE
          (long param_1,long *param_2,long param_3)

{
  uint *puVar1;
  uint uVar2;
  uint uVar3;
  long lVar4;
  undefined1 *puVar5;
  byte *pbVar6;
  byte bVar7;
  char cVar8;
  long lVar9;
  long lVar10;
  undefined8 *puVar11;
  undefined8 *puVar12;
  byte bVar13;
  uint uVar14;
  long lVar15;
  uint uVar16;
  char cVar17;
  undefined8 uVar18;
  long lVar19;
  long lVar20;
  long lVar21;
  long *plVar22;
  ulong uVar23;
  
  lVar9 = *param_2;
  lVar10 = param_2[1];
  lVar20 = param_2[2];
  uVar18 = *(undefined8 *)PTR__ZN4Aska6Global21m_pRenderStateManagerE_02cc0c10;
  if (lVar9 == 0) {
code_r0x021c4480:
    lVar9 = Aska::RenderStateManager::Get(int)(uVar18,7);
    *param_2 = lVar9;
    if (lVar9 == 0) {
      return 0;
    }
  }
  else if (*(int *)(lVar9 + 0x10) < 7) {
    Aska::RenderState::Release()(lVar9);
    goto code_r0x021c4480;
  }
  Aska::RenderState::Reset()(lVar9);
  if (lVar10 == 0) {
code_r0x021c44b8:
    lVar10 = Aska::RenderStateManager::Get(int)(uVar18,3);
    param_2[1] = lVar10;
    if (lVar10 == 0) {
      return 0;
    }
  }
  else if (*(int *)(lVar10 + 0x10) < 3) {
    Aska::RenderState::Release()(lVar10);
    goto code_r0x021c44b8;
  }
  Aska::RenderState::Reset()(lVar10);
  Aska::RenderState::SetDepthBias(float, float)(0,0,lVar9);
  bVar7 = *(byte *)(*(long *)(*(long *)(param_1 + 0x3d8) + 0xb0) + 0x7c);
  if ((*(byte *)(param_1 + 0x385) & 0x80) != 0) {
    bVar7 = *(byte *)(param_1 + 0x385);
  }
  if ((char)bVar7 < '\0') {
    if ((bVar7 & 0x60) != 0x40) {
      Aska::RenderState::EnableZTest(bool)(lVar9,bVar7 >> 5 & 1);
      bVar13 = bVar7 >> 6 & 1;
      goto code_r0x021c4554;
    }
    Aska::RenderState::EnableZTest(bool)(lVar9,1);
    Aska::RenderState::EnableZWrite(bool)(lVar9,1);
    bVar13 = 1;
  }
  else {
    Aska::RenderState::EnableZTest(bool)(lVar9,1);
    bVar13 = 1;
code_r0x021c4554:
    Aska::RenderState::EnableZWrite(bool)(lVar9,bVar13);
    bVar13 = bVar7 & 0xf;
  }
  Aska::RenderState::SetZTestFunction(int)(lVar9,bVar13);
  puVar1 = (uint *)(param_1 + 0x378);
  uVar14 = (uint)*(undefined6 *)(param_1 + 0x378);
  if ((uVar14 >> 1 & 1) == 0) {
    if ((uVar14 >> 1 & 1) != 0) goto code_r0x021c45ac;
code_r0x021c4580:
    if ((uVar14 >> 0xb & 1) == 0) goto code_r0x021c45c8;
code_r0x021c4584:
    if ((uVar14 >> 0xc & 1) != 0) goto code_r0x021c45e4;
code_r0x021c4588:
    cVar17 = '\x02';
  }
  else {
    Aska::RenderState::SetFillMode(int)(lVar9,1);
    uVar14 = (uint)*(undefined6 *)puVar1;
    if ((uVar14 >> 1 & 1) == 0) goto code_r0x021c4580;
code_r0x021c45ac:
    Aska::RenderState::SetFillMode(int)(lVar10,2);
    uVar14 = (uint)*(undefined6 *)puVar1;
    if ((uVar14 >> 0xb & 1) != 0) goto code_r0x021c4584;
code_r0x021c45c8:
    Aska::RenderState::EnableStencil(Aska::StencilMode::Mode)(lVar9,0);
    if (((uint)*(undefined6 *)puVar1 >> 0xc & 1) == 0) goto code_r0x021c4588;
code_r0x021c45e4:
    cVar17 = *(char *)(param_1 + 0x382);
    if (cVar17 == '\x01') {
      Aska::RenderState::EnableAlphaTest(bool)(lVar9,0);
      cVar17 = '\x02';
    }
    else {
      Aska::RenderState::SetAlphaTestFunction(int, int)(lVar9,cVar17,*(undefined1 *)(param_1 + 899));
    }
  }
  if ((*puVar1 >> 0xc & 1) != 0) {
    Aska::RenderState::EnableAlphaTest(bool)(lVar10,1);
  }
  Aska::RenderState::SetAlphaTestFunction(int, int)(lVar10,2,0);
  if (*(long *)(*(long *)(param_1 + 0x3d8) + 0xd0) == 0) {
    uVar23 = 0;
  }
  else {
    uVar23 = (ulong)*(ushort *)(*(long *)(*(long *)(param_1 + 0x3d8) + 0xb0) + 0x70);
  }
  cVar8 = *(char *)(param_3 + 0x2b);
  uVar14 = (uint)uVar23;
  if (lVar20 == 0) {
    puVar11 = (undefined8 *)operator new(unsigned long, std::nothrow_t const&)(0x20,PTR__ZSt7nothrow_02cb9a80);
    if (puVar11 == (undefined8 *)0x0) {
code_r0x021c46b8:
      param_2[2] = 0;
      return 0;
    }
    *puVar11 = 0;
    *(undefined2 *)(puVar11 + 1) = 0;
    if (uVar14 < 3) {
      puVar12 = puVar11 + 2;
      *puVar11 = puVar12;
    }
    else {
      puVar12 = (undefined8 *)operator new[](unsigned long, std::nothrow_t const&)(uVar14 << 3,PTR__ZSt7nothrow_02cb9a80);
      *puVar11 = puVar12;
      if (puVar12 == (undefined8 *)0x0) {
        operator delete(void*)(puVar11);
        goto code_r0x021c46b8;
      }
    }
    *(short *)(puVar11 + 1) = (short)uVar23;
    memset(puVar12,0,uVar14 << 3);
    param_2[2] = (long)puVar11;
  }
  if (uVar14 != 0) {
    lVar20 = 0;
    lVar9 = 0;
    lVar10 = 0x58;
    plVar22 = (long *)param_2[2];
    do {
      if ((*(byte *)(*(long *)(param_3 + 8) + lVar10) >> 2 & 1) == 0) {
        lVar15 = *(long *)(*(long *)(param_1 + 0x3d8) + 0x100);
        if (lVar15 == 0) {
          lVar21 = 0;
        }
        else {
          lVar21 = *(long *)(lVar15 + lVar20);
        }
        lVar19 = *(long *)(*plVar22 + lVar9 * 8);
        lVar4 = 0;
        if (lVar15 != 0) {
          lVar4 = lVar15 + lVar20 + 0x10;
        }
        if (lVar19 == 0) {
          uVar18 = Aska::RenderStateManager::Get(int)(*(undefined8 *)
                                    PTR__ZN4Aska6Global21m_pRenderStateManagerE_02cc0c10,9);
          *(undefined8 *)(*plVar22 + lVar9 * 8) = uVar18;
          lVar19 = *(long *)(*plVar22 + lVar9 * 8);
          if (lVar19 == 0) {
            return 0;
          }
        }
        Aska::RenderState::Reset()(lVar19);
        uVar14 = *puVar1;
        puVar5 = (undefined1 *)(lVar4 + 0x231);
        if ((uVar14 & 0x1000) != 0) {
          puVar5 = (undefined1 *)(param_1 + 899);
        }
        pbVar6 = (byte *)(lVar4 + 0x232);
        if ((uVar14 & 0x2000) != 0) {
          pbVar6 = (byte *)(param_1 + 900);
        }
        uVar3 = (uint)CONCAT11(*puVar5,*(char *)(lVar21 + 0x14));
        uVar2 = (*pbVar6 & 3) << 0x11;
        uVar16 = uVar3 | uVar2;
        if ((*(char *)(lVar21 + 0x14) == '\0') && (*(byte *)(param_1 + 0x1b4) != 0)) {
          uVar16 = uVar3 & 0xfffeff00 | uVar2 | (uint)*(byte *)(param_1 + 0x1b4);
        }
        if ((((uint)*(undefined6 *)puVar1 >> 0xd & 1) != 0) && (*(byte *)(param_1 + 900) != 0)) {
          uVar16 = uVar16 & 0xffffff00;
        }
        uVar2 = uVar16 & 0xffffff00 | 0x10;
        if ((uVar16 & 0xff) != 0 || cVar8 != '\x01') {
          uVar2 = uVar16;
        }
        if ((uVar14 & 0x10000) != 0) {
          uVar2 = uVar16 & 0xffffff00;
        }
        if (uVar2 != 0xffffffff) {
          uVar14 = uVar2 & 0xff;
          if (uVar14 != 0xff) {
            if (uVar14 == 0) {
              Aska::RenderState::EnableAlphaBlend(bool)(lVar19,0);
              if (-1 < (char)bVar7) {
                Aska::RenderState::EnableZWrite(bool)(lVar19,1);
              }
            }
            else {
              if (-1 < (char)bVar7) {
                Aska::RenderState::EnableZWrite(bool)(lVar19,uVar14 == 0x10);
              }
              Aska::RenderState::EnableAlphaBlend(bool)(lVar19,1);
              Aska::RenderState::SetAlphaBlendFunction(Aska::AlphaBlend::Operation, Aska::SeparateAlphaBlendMode::E)(lVar19,uVar14,cVar8);
            }
          }
          if ((uVar2 >> 8 & 0x1ff) != 0x1ff) {
            Aska::RenderState::SetAlphaTestFunction(int, int)(lVar19,cVar17);
          }
        }
        if ((*puVar1 >> 0xb & 1) != 0) {
          Aska::RenderState::EnableStencil(Aska::StencilMode::Mode)(lVar19,1);
          Aska::RenderState::SetStencilOp(int, int, int, int, int, short)(lVar19,*(undefined1 *)(param_1 + 0x389),*(undefined1 *)(param_1 + 0x38a),
                          *(undefined1 *)(param_1 + 0x38b),*(undefined1 *)(param_1 + 0x38c),
                          *(undefined1 *)(param_1 + 0x38d),*(undefined2 *)(param_1 + 0x6a8));
        }
        lVar15 = *(long *)(*plVar22 + lVar9 * 8);
        if ((lVar15 != 0) && (*(int *)(lVar15 + 0x14) == 0)) {
          Aska::RenderState::Release()();
          *(undefined8 *)(*plVar22 + lVar9 * 8) = 0;
        }
      }
      lVar9 = lVar9 + 1;
      lVar10 = lVar10 + 0x1b8;
      lVar20 = lVar20 + 0x2a0;
    } while (lVar9 < (long)uVar23);
  }
  Aska::RenderPassManager::InvalidateObjectRenderState()(*(undefined8 *)(param_1 + 0x398));
  *(undefined1 *)((long)param_2 + 0x1a) = 1;
  return 1;
}

// ==== bool Aska::AofObject::MakeObjectRenderState<1514u>(Aska::AofObjectRenderState*, Aska::RenderPass*)
// vaddr 0x20c496c | ghidra 0x21c496c | size 528 | symbol _ZN4Aska9AofObject21MakeObjectRenderStateILj1514EEEbPNS_20AofObjectRenderStateEPNS_10RenderPassE | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Type propagation algorithm not settling */

void _ZN4Aska9AofObject21MakeObjectRenderStateILj1514EEEbPNS_20AofObjectRenderStateEPNS_10RenderPassE
               (long param_1,long *param_2)

{
  uint *puVar1;
  long lVar2;
  long lVar3;
  byte bVar4;
  byte bVar5;
  uint uVar6;
  undefined8 uVar7;
  
  lVar2 = *param_2;
  lVar3 = param_2[1];
  uVar7 = *(undefined8 *)PTR__ZN4Aska6Global21m_pRenderStateManagerE_02cc0c10;
  if (lVar2 == 0) {
code_r0x021c49a8:
    lVar2 = Aska::RenderStateManager::Get(int)(uVar7,7);
    *param_2 = lVar2;
    if (lVar2 == 0) {
      return;
    }
  }
  else if (*(int *)(lVar2 + 0x10) < 7) {
    Aska::RenderState::Release()(lVar2);
    goto code_r0x021c49a8;
  }
  Aska::RenderState::Reset()(lVar2);
  if (lVar3 == 0) {
code_r0x021c49e0:
    lVar3 = Aska::RenderStateManager::Get(int)(uVar7,3);
    param_2[1] = lVar3;
    if (lVar3 == 0) {
      return;
    }
  }
  else if (*(int *)(lVar3 + 0x10) < 3) {
    Aska::RenderState::Release()(lVar3);
    goto code_r0x021c49e0;
  }
  Aska::RenderState::Reset()(lVar3);
  Aska::RenderState::SetDepthBias(float, float)(0,0,lVar2);
  bVar5 = *(byte *)(*(long *)(*(long *)(param_1 + 0x3d8) + 0xb0) + 0x7c);
  if ((*(byte *)(param_1 + 0x385) & 0x80) != 0) {
    bVar5 = *(byte *)(param_1 + 0x385);
  }
  if ((char)bVar5 < '\0') {
    if ((bVar5 & 0x60) == 0x40) {
      Aska::RenderState::EnableZTest(bool)(lVar2,1);
      Aska::RenderState::EnableZWrite(bool)(lVar2,1);
      bVar5 = 1;
      goto code_r0x021c4a88;
    }
    Aska::RenderState::EnableZTest(bool)(lVar2,bVar5 >> 5 & 1);
    bVar4 = bVar5 >> 6 & 1;
  }
  else {
    Aska::RenderState::EnableZTest(bool)(lVar2,1);
    bVar4 = 1;
  }
  Aska::RenderState::EnableZWrite(bool)(lVar2,bVar4);
  bVar5 = bVar5 & 0xf;
code_r0x021c4a88:
  Aska::RenderState::SetZTestFunction(int)(lVar2,bVar5);
  puVar1 = (uint *)(param_1 + 0x378);
  uVar6 = (uint)*(undefined6 *)(param_1 + 0x378);
  if ((uVar6 >> 1 & 1) != 0) {
    Aska::RenderState::SetFillMode(int)(lVar2,1);
    uVar6 = (uint)*(undefined6 *)puVar1;
  }
  if ((uVar6 >> 1 & 1) != 0) {
    Aska::RenderState::SetFillMode(int)(lVar3,2);
    uVar6 = (uint)*(undefined6 *)puVar1;
  }
  if ((uVar6 >> 0xb & 1) == 0) {
    Aska::RenderState::EnableStencil(Aska::StencilMode::Mode)(lVar2,0);
    uVar6 = (uint)*(undefined6 *)puVar1;
  }
  if ((uVar6 >> 0xc & 1) != 0) {
    if (*(char *)(param_1 + 0x382) == '\x01') {
      Aska::RenderState::EnableAlphaTest(bool)(lVar2,0);
    }
    else {
      Aska::RenderState::SetAlphaTestFunction(int, int)(lVar2,*(char *)(param_1 + 0x382),*(undefined1 *)(param_1 + 899));
    }
  }
  if ((*puVar1 >> 0xc & 1) != 0) {
    Aska::RenderState::EnableAlphaTest(bool)(lVar3,1);
  }
  Aska::RenderState::SetAlphaTestFunction(int, int)(lVar3,2,0);
  Aska::RenderPassManager::InvalidateObjectRenderState()(*(undefined8 *)(param_1 + 0x398));
  *(undefined1 *)((long)param_2 + 0x1a) = 1;
  return;
}

// ==== Aska::AofObject::MakeObjectRenderStateMultiDraw(Aska::AofObjectRenderState*, Aska::RenderPass*)
// vaddr 0x20c4b7c | ghidra 0x21c4b7c | size 4 | symbol _ZN4Aska9AofObject30MakeObjectRenderStateMultiDrawEPNS_20AofObjectRenderStateEPNS_10RenderPassE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska9AofObject30MakeObjectRenderStateMultiDrawEPNS_20AofObjectRenderStateEPNS_10RenderPassE
               (void)

{
  (*(code *)
    PTR__ZN4Aska9AofObject21MakeObjectRenderStateILj2543EEEbPNS_20AofObjectRenderStateEPNS_10RenderPassE_02c98bb0
  )();
  return;
}

// ==== bool Aska::AofObject::MakeObjectRenderState<2543u>(Aska::AofObjectRenderState*, Aska::RenderPass*)
// vaddr 0x20c4b80 | ghidra 0x21c4b80 | size 540 | symbol _ZN4Aska9AofObject21MakeObjectRenderStateILj2543EEEbPNS_20AofObjectRenderStateEPNS_10RenderPassE | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Type propagation algorithm not settling */

void _ZN4Aska9AofObject21MakeObjectRenderStateILj2543EEEbPNS_20AofObjectRenderStateEPNS_10RenderPassE
               (long param_1,long *param_2)

{
  uint *puVar1;
  long lVar2;
  long lVar3;
  byte bVar4;
  byte bVar5;
  uint uVar6;
  undefined8 uVar7;
  
  lVar2 = *param_2;
  lVar3 = param_2[1];
  uVar7 = *(undefined8 *)PTR__ZN4Aska6Global21m_pRenderStateManagerE_02cc0c10;
  if (lVar2 == 0) {
code_r0x021c4bbc:
    lVar2 = Aska::RenderStateManager::Get(int)(uVar7,7);
    *param_2 = lVar2;
    if (lVar2 == 0) {
      return;
    }
  }
  else if (*(int *)(lVar2 + 0x10) < 7) {
    Aska::RenderState::Release()(lVar2);
    goto code_r0x021c4bbc;
  }
  Aska::RenderState::Reset()(lVar2);
  if (lVar3 == 0) {
code_r0x021c4bf4:
    lVar3 = Aska::RenderStateManager::Get(int)(uVar7,3);
    param_2[1] = lVar3;
    if (lVar3 == 0) {
      return;
    }
  }
  else if (*(int *)(lVar3 + 0x10) < 3) {
    Aska::RenderState::Release()(lVar3);
    goto code_r0x021c4bf4;
  }
  Aska::RenderState::Reset()(lVar3);
  Aska::RenderState::EnableAlphaBlend(bool)(lVar2,0);
  Aska::RenderState::SetDepthBias(float, float)(0,0,lVar2);
  bVar5 = *(byte *)(*(long *)(*(long *)(param_1 + 0x3d8) + 0xb0) + 0x7c);
  if ((*(byte *)(param_1 + 0x385) & 0x80) != 0) {
    bVar5 = *(byte *)(param_1 + 0x385);
  }
  if ((char)bVar5 < '\0') {
    if ((bVar5 & 0x60) == 0x40) {
      Aska::RenderState::EnableZTest(bool)(lVar2,1);
      Aska::RenderState::EnableZWrite(bool)(lVar2,1);
      bVar5 = 1;
      goto code_r0x021c4ca8;
    }
    Aska::RenderState::EnableZTest(bool)(lVar2,bVar5 >> 5 & 1);
    bVar4 = bVar5 >> 6 & 1;
  }
  else {
    Aska::RenderState::EnableZTest(bool)(lVar2,1);
    bVar4 = 1;
  }
  Aska::RenderState::EnableZWrite(bool)(lVar2,bVar4);
  bVar5 = bVar5 & 0xf;
code_r0x021c4ca8:
  Aska::RenderState::SetZTestFunction(int)(lVar2,bVar5);
  puVar1 = (uint *)(param_1 + 0x378);
  uVar6 = (uint)*(undefined6 *)(param_1 + 0x378);
  if ((uVar6 >> 1 & 1) != 0) {
    Aska::RenderState::SetFillMode(int)(lVar2,1);
    uVar6 = (uint)*(undefined6 *)puVar1;
  }
  if ((uVar6 >> 1 & 1) != 0) {
    Aska::RenderState::SetFillMode(int)(lVar3,2);
    uVar6 = (uint)*(undefined6 *)puVar1;
  }
  if ((uVar6 >> 0xb & 1) == 0) {
    Aska::RenderState::EnableStencil(Aska::StencilMode::Mode)(lVar2,0);
    uVar6 = (uint)*(undefined6 *)puVar1;
  }
  if ((uVar6 >> 0xc & 1) != 0) {
    if (*(char *)(param_1 + 0x382) == '\x01') {
      Aska::RenderState::EnableAlphaTest(bool)(lVar2,0);
    }
    else {
      Aska::RenderState::SetAlphaTestFunction(int, int)(lVar2,*(char *)(param_1 + 0x382),*(undefined1 *)(param_1 + 899));
    }
  }
  if ((*puVar1 >> 0xc & 1) != 0) {
    Aska::RenderState::EnableAlphaTest(bool)(lVar3,1);
  }
  Aska::RenderState::SetAlphaTestFunction(int, int)(lVar3,2,0);
  Aska::RenderPassManager::InvalidateObjectRenderState()(*(undefined8 *)(param_1 + 0x398));
  *(undefined1 *)((long)param_2 + 0x1a) = 1;
  return;
}

// ==== Aska::AofObject::MakePassRenderStateMultiDraw(unsigned int, Aska::RenderPass*)
// vaddr 0x20c4d9c | ghidra 0x21c4d9c | size 252 | symbol _ZN4Aska9AofObject28MakePassRenderStateMultiDrawEjPNS_10RenderPassE | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska9AofObject28MakePassRenderStateMultiDrawEjPNS_10RenderPassE
          (long param_1,undefined4 param_2,long param_3)

{
  long lVar1;
  int iVar2;
  byte bVar3;
  int iVar4;
  long lVar5;
  undefined8 uVar6;
  long lVar7;
  long lVar8;
  
  bVar3 = *(byte *)(param_3 + 0x26);
  if ((ulong)bVar3 != 0) {
    lVar7 = 0;
    lVar8 = 0;
    uVar6 = *(undefined8 *)PTR__ZN4Aska6Global21m_pRenderStateManagerE_02cc0c10;
    do {
      lVar1 = *(long *)(param_3 + 8) + lVar7;
      if ((*(byte *)(lVar1 + 0x58) >> 2 & 1) == 0) {
        iVar4 = (**(code **)(**(long **)(param_1 + 0x690) + 0x10))
                          (*(long **)(param_1 + 0x690),param_2);
        lVar5 = *(long *)(lVar1 + 0x48);
        iVar2 = iVar4;
        if (iVar4 == 0) {
          iVar2 = 1;
        }
        if (lVar5 == 0) {
code_r0x021c4e28:
          lVar5 = Aska::RenderStateManager::Get(int)(uVar6,iVar2);
          *(long *)(lVar1 + 0x48) = lVar5;
          if (lVar5 == 0) {
            return 0;
          }
        }
        else if (*(int *)(lVar5 + 0x10) != iVar2) {
          Aska::RenderState::Release()(lVar5);
          goto code_r0x021c4e28;
        }
        if (iVar4 == 0) {
          Aska::RenderState::Reset()(lVar5);
        }
        else {
          (**(code **)(**(long **)(param_1 + 0x690) + 0x18))
                    (*(long **)(param_1 + 0x690),param_2,lVar5);
        }
      }
      lVar8 = lVar8 + 1;
      lVar7 = lVar7 + 0x1b8;
    } while (lVar8 < (long)(ulong)bVar3);
  }
  return 1;
}

// ==== Aska::AofObject::MakeObjectRenderState(Aska::AofObjectRenderState*, Aska::RenderPass*, bool)
// vaddr 0x20c4e98 | ghidra 0x21c4e98 | size 12 | symbol _ZN4Aska9AofObject21MakeObjectRenderStateEPNS_20AofObjectRenderStateEPNS_10RenderPassEb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska9AofObject21MakeObjectRenderStateEPNS_20AofObjectRenderStateEPNS_10RenderPassEb(void)

{
  uint in_w3;
  
  if ((in_w3 & 1) != 0) {
    (*(code *)
      PTR__ZN4Aska9AofObject21MakeObjectRenderStateILj7151EEEbPNS_20AofObjectRenderStateEPNS_10RenderPassE_02c92348
    )();
    return;
  }
  (*(code *)
    PTR__ZN4Aska9AofObject21MakeObjectRenderStateILj3055EEEbPNS_20AofObjectRenderStateEPNS_10RenderPassE_02c91f90
  )();
  return;
}

// ==== bool Aska::AofObject::MakeObjectRenderState<7151u>(Aska::AofObjectRenderState*, Aska::RenderPass*)
// vaddr 0x20c4ea4 | ghidra 0x21c4ea4 | size 1500 | symbol _ZN4Aska9AofObject21MakeObjectRenderStateILj7151EEEbPNS_20AofObjectRenderStateEPNS_10RenderPassE | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska9AofObject21MakeObjectRenderStateILj7151EEEbPNS_20AofObjectRenderStateEPNS_10RenderPassE
          (long param_1,long *param_2,long param_3)

{
  uint *puVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  long lVar5;
  undefined1 *puVar6;
  byte *pbVar7;
  uint uVar8;
  byte bVar9;
  char cVar10;
  bool bVar11;
  long lVar12;
  long lVar13;
  undefined8 *puVar14;
  undefined8 *puVar15;
  byte bVar16;
  uint uVar17;
  long lVar18;
  uint uVar19;
  ulong uVar20;
  long lVar21;
  long *plVar22;
  undefined8 uVar23;
  long lVar24;
  long lVar25;
  char cVar26;
  long *plVar27;
  int iStack_98;
  
  lVar12 = *param_2;
  lVar13 = param_2[1];
  lVar21 = param_2[2];
  uVar23 = *(undefined8 *)PTR__ZN4Aska6Global21m_pRenderStateManagerE_02cc0c10;
  if (lVar12 == 0) {
code_r0x021c4ef8:
    lVar12 = Aska::RenderStateManager::Get(int)(uVar23,6);
    *param_2 = lVar12;
    if (lVar12 == 0) {
      return 0;
    }
  }
  else if (*(int *)(lVar12 + 0x10) < 6) {
    Aska::RenderState::Release()(lVar12);
    goto code_r0x021c4ef8;
  }
  Aska::RenderState::Reset()(lVar12);
  if (lVar13 == 0) {
code_r0x021c4f30:
    lVar13 = Aska::RenderStateManager::Get(int)(uVar23,3);
    param_2[1] = lVar13;
    if (lVar13 == 0) {
      return 0;
    }
  }
  else if (*(int *)(lVar13 + 0x10) < 3) {
    Aska::RenderState::Release()(lVar13);
    goto code_r0x021c4f30;
  }
  Aska::RenderState::Reset()(lVar13);
  Aska::RenderState::SetDepthBias(float, float)(0,0,lVar12);
  bVar9 = *(byte *)(*(long *)(*(long *)(param_1 + 0x3d8) + 0xb0) + 0x7c);
  if ((*(byte *)(param_1 + 0x385) & 0x80) != 0) {
    bVar9 = *(byte *)(param_1 + 0x385);
  }
  if ((char)bVar9 < '\0') {
    if ((bVar9 & 0x60) == 0x40) {
      Aska::RenderState::EnableZTest(bool)(lVar12,1);
      Aska::RenderState::EnableZWrite(bool)(lVar12,1);
      bVar16 = 1;
    }
    else {
      Aska::RenderState::EnableZTest(bool)(lVar12,bVar9 >> 5 & 1);
      Aska::RenderState::EnableZWrite(bool)(lVar12,bVar9 >> 6 & 1);
      bVar16 = bVar9 & 0xf;
    }
  }
  else {
    Aska::RenderState::EnableZTest(bool)(lVar12,1);
    Aska::RenderState::EnableZWrite(bool)(lVar12,1);
    bVar16 = bVar9 & 0xf;
    if (bVar16 == 3) {
      bVar16 = 4;
    }
  }
  Aska::RenderState::SetZTestFunction(int)(lVar12,bVar16);
  puVar1 = (uint *)(param_1 + 0x378);
  uVar17 = (uint)*(undefined6 *)(param_1 + 0x378);
  if ((uVar17 >> 1 & 1) == 0) {
    if ((uVar17 >> 1 & 1) != 0) goto code_r0x021c503c;
code_r0x021c5010:
    if ((uVar17 >> 0xb & 1) == 0) goto code_r0x021c5058;
code_r0x021c5014:
    if ((uVar17 >> 0xc & 1) != 0) goto code_r0x021c5074;
code_r0x021c5018:
    cVar26 = '\x02';
  }
  else {
    Aska::RenderState::SetFillMode(int)(lVar12,1);
    uVar17 = (uint)*(undefined6 *)puVar1;
    if ((uVar17 >> 1 & 1) == 0) goto code_r0x021c5010;
code_r0x021c503c:
    Aska::RenderState::SetFillMode(int)(lVar13,2);
    uVar17 = (uint)*(undefined6 *)puVar1;
    if ((uVar17 >> 0xb & 1) != 0) goto code_r0x021c5014;
code_r0x021c5058:
    Aska::RenderState::EnableStencil(Aska::StencilMode::Mode)(lVar12,0);
    if (((uint)*(undefined6 *)puVar1 >> 0xc & 1) == 0) goto code_r0x021c5018;
code_r0x021c5074:
    cVar26 = *(char *)(param_1 + 0x382);
    if (cVar26 == '\x01') {
      Aska::RenderState::EnableAlphaTest(bool)(lVar12,0);
      cVar26 = '\x02';
    }
    else {
      Aska::RenderState::SetAlphaTestFunction(int, int)(lVar12,cVar26,*(undefined1 *)(param_1 + 899));
    }
  }
  if ((*puVar1 >> 0xc & 1) != 0) {
    Aska::RenderState::EnableAlphaTest(bool)(lVar13,1);
  }
  Aska::RenderState::SetAlphaTestFunction(int, int)(lVar13,2,0);
  uVar20 = 0;
  if (*(long *)(*(long *)(param_1 + 0x3d8) + 0xd0) != 0) {
    uVar20 = (ulong)*(ushort *)(*(long *)(*(long *)(param_1 + 0x3d8) + 0xb0) + 0x70);
  }
  cVar10 = *(char *)(param_3 + 0x2b);
  uVar17 = (uint)uVar20;
  if (lVar21 == 0) {
    puVar14 = (undefined8 *)operator new(unsigned long, std::nothrow_t const&)(0x20,PTR__ZSt7nothrow_02cb9a80);
    if (puVar14 == (undefined8 *)0x0) {
code_r0x021c5414:
      param_2[2] = 0;
      return 0;
    }
    *puVar14 = 0;
    *(undefined2 *)(puVar14 + 1) = 0;
    if (uVar17 < 3) {
      puVar15 = puVar14 + 2;
      *puVar14 = puVar15;
    }
    else {
      puVar15 = (undefined8 *)operator new[](unsigned long, std::nothrow_t const&)(uVar17 << 3,PTR__ZSt7nothrow_02cb9a80);
      *puVar14 = puVar15;
      if (puVar15 == (undefined8 *)0x0) {
        operator delete(void*)(puVar14);
        goto code_r0x021c5414;
      }
    }
    *(short *)(puVar14 + 1) = (short)uVar20;
    memset(puVar15,0,uVar17 << 3);
    param_2[2] = (long)puVar14;
  }
  if (uVar17 != 0) {
    iStack_98 = 0;
    bVar11 = false;
    plVar27 = (long *)param_2[2];
    lVar21 = 0;
    lVar12 = 0;
    uVar17 = 0xffffffff;
    lVar13 = 0x58;
    plVar22 = param_2;
    do {
      if ((*(byte *)(*(long *)(param_3 + 8) + lVar13) >> 2 & 1) == 0) {
        lVar18 = *(long *)(*(long *)(param_1 + 0x3d8) + 0x100);
        if (lVar18 == 0) {
          lVar25 = 0;
        }
        else {
          lVar25 = *(long *)(lVar18 + lVar21);
        }
        lVar24 = *(long *)(*plVar27 + lVar12 * 8);
        lVar5 = 0;
        if (lVar18 != 0) {
          lVar5 = lVar18 + lVar21 + 0x10;
        }
        if (lVar24 == 0) {
          uVar23 = Aska::RenderStateManager::Get(int)(*(undefined8 *)
                                    PTR__ZN4Aska6Global21m_pRenderStateManagerE_02cc0c10,9);
          *(undefined8 *)(*plVar27 + lVar12 * 8) = uVar23;
          lVar24 = *(long *)(*plVar27 + lVar12 * 8);
          if (lVar24 == 0) {
            return 0;
          }
        }
        Aska::RenderState::Reset()(lVar24);
        uVar8 = *puVar1;
        puVar6 = (undefined1 *)(lVar5 + 0x231);
        if ((uVar8 & 0x1000) != 0) {
          puVar6 = (undefined1 *)(param_1 + 899);
        }
        pbVar7 = (byte *)(lVar5 + 0x232);
        if ((uVar8 & 0x2000) != 0) {
          pbVar7 = (byte *)(param_1 + 900);
        }
        uVar2 = (uint)plVar22 & 0xfff80000;
        uVar4 = (uint)CONCAT11(*puVar6,*(char *)(lVar25 + 0x14));
        uVar3 = (*pbVar7 & 3) << 0x11;
        uVar19 = uVar2 | uVar4 | uVar3;
        if ((*(char *)(lVar25 + 0x14) == '\0') && (*(byte *)(param_1 + 0x1b4) != 0)) {
          uVar19 = uVar2 | uVar4 & 0xfffeff00 | uVar3 | (uint)*(byte *)(param_1 + 0x1b4);
        }
        if ((((uint)*(undefined6 *)puVar1 >> 0xd & 1) != 0) && (*(byte *)(param_1 + 900) != 0)) {
          uVar19 = uVar19 & 0xffffff00;
        }
        uVar2 = uVar19 & 0xffffff00 | 0x10;
        if ((uVar19 & 0xff) != 0 || cVar10 != '\x01') {
          uVar2 = uVar19;
        }
        if ((uVar8 & 0x10000) != 0) {
          uVar2 = uVar19 & 0xffffff00;
        }
        plVar22 = (long *)(ulong)uVar2;
        if (uVar17 != uVar2) {
          uVar8 = uVar2 & 0xff;
          if (uVar8 != (uVar17 & 0xff)) {
            if (uVar8 == 0) {
              Aska::RenderState::EnableAlphaBlend(bool)(lVar24,0);
              if ((char)bVar9 < '\0') {
                bVar11 = true;
              }
              else {
                bVar11 = true;
                Aska::RenderState::EnableZWrite(bool)(lVar24,1);
              }
            }
            else {
              if (-1 < (char)bVar9) {
                Aska::RenderState::EnableZWrite(bool)(lVar24,uVar8 == 0x10);
              }
              bVar11 = true;
              Aska::RenderState::EnableAlphaBlend(bool)(lVar24,1);
              Aska::RenderState::SetAlphaBlendFunction(Aska::AlphaBlend::Operation, Aska::SeparateAlphaBlendMode::E)(lVar24,uVar8,cVar10);
              iStack_98 = 1;
            }
          }
          if ((uVar2 >> 8 & 0x1ff) != (uVar17 >> 8 & 0x1ff)) {
            Aska::RenderState::SetAlphaTestFunction(int, int)(lVar24,cVar26);
          }
          uVar8 = uVar17 >> 0x11;
          uVar17 = uVar2;
          if ((uVar2 >> 0x11 & 3) != (uVar8 & 3)) {
            Aska::RenderState::SetAlphaToCoverage(int)(lVar24);
          }
        }
        if ((*puVar1 >> 0xb & 1) != 0) {
          Aska::RenderState::EnableStencil(Aska::StencilMode::Mode)(lVar24,1);
          Aska::RenderState::SetStencilOp(int, int, int, int, int, short)(lVar24,*(undefined1 *)(param_1 + 0x389),*(undefined1 *)(param_1 + 0x38a),
                          *(undefined1 *)(param_1 + 0x38b),*(undefined1 *)(param_1 + 0x38c),
                          *(undefined1 *)(param_1 + 0x38d),*(undefined2 *)(param_1 + 0x6a8));
        }
        lVar18 = *(long *)(*plVar27 + lVar12 * 8);
        if ((lVar18 != 0) && (*(int *)(lVar18 + 0x14) == 0)) {
          Aska::RenderState::Release()();
          *(undefined8 *)(*plVar27 + lVar12 * 8) = 0;
        }
      }
      lVar12 = lVar12 + 1;
      lVar13 = lVar13 + 0x1b8;
      lVar21 = lVar21 + 0x2a0;
    } while (lVar12 < (long)uVar20);
    if (bVar11) {
      *puVar1 = *puVar1 & 0xfffffff8 | *puVar1 & 3 | iStack_98 << 2;
    }
  }
  Aska::RenderPassManager::InvalidateObjectRenderState()(*(undefined8 *)(param_1 + 0x398));
  *(undefined1 *)((long)param_2 + 0x1a) = 1;
  return 1;
}

// ==== bool Aska::AofObject::MakeObjectRenderState<3055u>(Aska::AofObjectRenderState*, Aska::RenderPass*)
// vaddr 0x20c5480 | ghidra 0x21c5480 | size 1476 | symbol _ZN4Aska9AofObject21MakeObjectRenderStateILj3055EEEbPNS_20AofObjectRenderStateEPNS_10RenderPassE | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska9AofObject21MakeObjectRenderStateILj3055EEEbPNS_20AofObjectRenderStateEPNS_10RenderPassE
          (long param_1,long *param_2,long param_3)

{
  uint *puVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  long lVar5;
  undefined1 *puVar6;
  byte *pbVar7;
  uint uVar8;
  byte bVar9;
  char cVar10;
  bool bVar11;
  long lVar12;
  long lVar13;
  undefined8 *puVar14;
  undefined8 *puVar15;
  byte bVar16;
  uint uVar17;
  long lVar18;
  uint uVar19;
  ulong uVar20;
  long lVar21;
  long *plVar22;
  undefined8 uVar23;
  long lVar24;
  long lVar25;
  char cVar26;
  long *plVar27;
  int iStack_98;
  
  lVar12 = *param_2;
  lVar13 = param_2[1];
  lVar21 = param_2[2];
  uVar23 = *(undefined8 *)PTR__ZN4Aska6Global21m_pRenderStateManagerE_02cc0c10;
  if (lVar12 == 0) {
code_r0x021c54d4:
    lVar12 = Aska::RenderStateManager::Get(int)(uVar23,6);
    *param_2 = lVar12;
    if (lVar12 == 0) {
      return 0;
    }
  }
  else if (*(int *)(lVar12 + 0x10) < 6) {
    Aska::RenderState::Release()(lVar12);
    goto code_r0x021c54d4;
  }
  Aska::RenderState::Reset()(lVar12);
  if (lVar13 == 0) {
code_r0x021c550c:
    lVar13 = Aska::RenderStateManager::Get(int)(uVar23,3);
    param_2[1] = lVar13;
    if (lVar13 == 0) {
      return 0;
    }
  }
  else if (*(int *)(lVar13 + 0x10) < 3) {
    Aska::RenderState::Release()(lVar13);
    goto code_r0x021c550c;
  }
  Aska::RenderState::Reset()(lVar13);
  Aska::RenderState::SetDepthBias(float, float)(0,0,lVar12);
  bVar9 = *(byte *)(*(long *)(*(long *)(param_1 + 0x3d8) + 0xb0) + 0x7c);
  if ((*(byte *)(param_1 + 0x385) & 0x80) != 0) {
    bVar9 = *(byte *)(param_1 + 0x385);
  }
  if ((char)bVar9 < '\0') {
    if ((bVar9 & 0x60) != 0x40) {
      Aska::RenderState::EnableZTest(bool)(lVar12,bVar9 >> 5 & 1);
      bVar16 = bVar9 >> 6 & 1;
      goto code_r0x021c55a8;
    }
    Aska::RenderState::EnableZTest(bool)(lVar12,1);
    Aska::RenderState::EnableZWrite(bool)(lVar12,1);
    bVar16 = 1;
  }
  else {
    Aska::RenderState::EnableZTest(bool)(lVar12,1);
    bVar16 = 1;
code_r0x021c55a8:
    Aska::RenderState::EnableZWrite(bool)(lVar12,bVar16);
    bVar16 = bVar9 & 0xf;
  }
  Aska::RenderState::SetZTestFunction(int)(lVar12,bVar16);
  puVar1 = (uint *)(param_1 + 0x378);
  uVar17 = (uint)*(undefined6 *)(param_1 + 0x378);
  if ((uVar17 >> 1 & 1) == 0) {
    if ((uVar17 >> 1 & 1) != 0) goto code_r0x021c5600;
code_r0x021c55d4:
    if ((uVar17 >> 0xb & 1) == 0) goto code_r0x021c561c;
code_r0x021c55d8:
    if ((uVar17 >> 0xc & 1) != 0) goto code_r0x021c5638;
code_r0x021c55dc:
    cVar26 = '\x02';
  }
  else {
    Aska::RenderState::SetFillMode(int)(lVar12,1);
    uVar17 = (uint)*(undefined6 *)puVar1;
    if ((uVar17 >> 1 & 1) == 0) goto code_r0x021c55d4;
code_r0x021c5600:
    Aska::RenderState::SetFillMode(int)(lVar13,2);
    uVar17 = (uint)*(undefined6 *)puVar1;
    if ((uVar17 >> 0xb & 1) != 0) goto code_r0x021c55d8;
code_r0x021c561c:
    Aska::RenderState::EnableStencil(Aska::StencilMode::Mode)(lVar12,0);
    if (((uint)*(undefined6 *)puVar1 >> 0xc & 1) == 0) goto code_r0x021c55dc;
code_r0x021c5638:
    cVar26 = *(char *)(param_1 + 0x382);
    if (cVar26 == '\x01') {
      Aska::RenderState::EnableAlphaTest(bool)(lVar12,0);
      cVar26 = '\x02';
    }
    else {
      Aska::RenderState::SetAlphaTestFunction(int, int)(lVar12,cVar26,*(undefined1 *)(param_1 + 899));
    }
  }
  if ((*puVar1 >> 0xc & 1) != 0) {
    Aska::RenderState::EnableAlphaTest(bool)(lVar13,1);
  }
  Aska::RenderState::SetAlphaTestFunction(int, int)(lVar13,2,0);
  uVar20 = 0;
  if (*(long *)(*(long *)(param_1 + 0x3d8) + 0xd0) != 0) {
    uVar20 = (ulong)*(ushort *)(*(long *)(*(long *)(param_1 + 0x3d8) + 0xb0) + 0x70);
  }
  cVar10 = *(char *)(param_3 + 0x2b);
  uVar17 = (uint)uVar20;
  if (lVar21 == 0) {
    puVar14 = (undefined8 *)operator new(unsigned long, std::nothrow_t const&)(0x20,PTR__ZSt7nothrow_02cb9a80);
    if (puVar14 == (undefined8 *)0x0) {
code_r0x021c59d8:
      param_2[2] = 0;
      return 0;
    }
    *puVar14 = 0;
    *(undefined2 *)(puVar14 + 1) = 0;
    if (uVar17 < 3) {
      puVar15 = puVar14 + 2;
      *puVar14 = puVar15;
    }
    else {
      puVar15 = (undefined8 *)operator new[](unsigned long, std::nothrow_t const&)(uVar17 << 3,PTR__ZSt7nothrow_02cb9a80);
      *puVar14 = puVar15;
      if (puVar15 == (undefined8 *)0x0) {
        operator delete(void*)(puVar14);
        goto code_r0x021c59d8;
      }
    }
    *(short *)(puVar14 + 1) = (short)uVar20;
    memset(puVar15,0,uVar17 << 3);
    param_2[2] = (long)puVar14;
  }
  if (uVar17 != 0) {
    iStack_98 = 0;
    bVar11 = false;
    plVar27 = (long *)param_2[2];
    lVar21 = 0;
    lVar12 = 0;
    uVar17 = 0xffffffff;
    lVar13 = 0x58;
    plVar22 = param_2;
    do {
      if ((*(byte *)(*(long *)(param_3 + 8) + lVar13) >> 2 & 1) == 0) {
        lVar18 = *(long *)(*(long *)(param_1 + 0x3d8) + 0x100);
        if (lVar18 == 0) {
          lVar25 = 0;
        }
        else {
          lVar25 = *(long *)(lVar18 + lVar21);
        }
        lVar24 = *(long *)(*plVar27 + lVar12 * 8);
        lVar5 = 0;
        if (lVar18 != 0) {
          lVar5 = lVar18 + lVar21 + 0x10;
        }
        if (lVar24 == 0) {
          uVar23 = Aska::RenderStateManager::Get(int)(*(undefined8 *)
                                    PTR__ZN4Aska6Global21m_pRenderStateManagerE_02cc0c10,9);
          *(undefined8 *)(*plVar27 + lVar12 * 8) = uVar23;
          lVar24 = *(long *)(*plVar27 + lVar12 * 8);
          if (lVar24 == 0) {
            return 0;
          }
        }
        Aska::RenderState::Reset()(lVar24);
        uVar8 = *puVar1;
        puVar6 = (undefined1 *)(lVar5 + 0x231);
        if ((uVar8 & 0x1000) != 0) {
          puVar6 = (undefined1 *)(param_1 + 899);
        }
        pbVar7 = (byte *)(lVar5 + 0x232);
        if ((uVar8 & 0x2000) != 0) {
          pbVar7 = (byte *)(param_1 + 900);
        }
        uVar2 = (uint)plVar22 & 0xfff80000;
        uVar4 = (uint)CONCAT11(*puVar6,*(char *)(lVar25 + 0x14));
        uVar3 = (*pbVar7 & 3) << 0x11;
        uVar19 = uVar2 | uVar4 | uVar3;
        if ((*(char *)(lVar25 + 0x14) == '\0') && (*(byte *)(param_1 + 0x1b4) != 0)) {
          uVar19 = uVar2 | uVar4 & 0xfffeff00 | uVar3 | (uint)*(byte *)(param_1 + 0x1b4);
        }
        if ((((uint)*(undefined6 *)puVar1 >> 0xd & 1) != 0) && (*(byte *)(param_1 + 900) != 0)) {
          uVar19 = uVar19 & 0xffffff00;
        }
        uVar2 = uVar19 & 0xffffff00 | 0x10;
        if ((uVar19 & 0xff) != 0 || cVar10 != '\x01') {
          uVar2 = uVar19;
        }
        if ((uVar8 & 0x10000) != 0) {
          uVar2 = uVar19 & 0xffffff00;
        }
        plVar22 = (long *)(ulong)uVar2;
        if (uVar17 != uVar2) {
          uVar8 = uVar2 & 0xff;
          if (uVar8 != (uVar17 & 0xff)) {
            if (uVar8 == 0) {
              Aska::RenderState::EnableAlphaBlend(bool)(lVar24,0);
              if ((char)bVar9 < '\0') {
                bVar11 = true;
              }
              else {
                bVar11 = true;
                Aska::RenderState::EnableZWrite(bool)(lVar24,1);
              }
            }
            else {
              if (-1 < (char)bVar9) {
                Aska::RenderState::EnableZWrite(bool)(lVar24,uVar8 == 0x10);
              }
              bVar11 = true;
              Aska::RenderState::EnableAlphaBlend(bool)(lVar24,1);
              Aska::RenderState::SetAlphaBlendFunction(Aska::AlphaBlend::Operation, Aska::SeparateAlphaBlendMode::E)(lVar24,uVar8,cVar10);
              iStack_98 = 1;
            }
          }
          if ((uVar2 >> 8 & 0x1ff) != (uVar17 >> 8 & 0x1ff)) {
            Aska::RenderState::SetAlphaTestFunction(int, int)(lVar24,cVar26);
          }
          uVar8 = uVar17 >> 0x11;
          uVar17 = uVar2;
          if ((uVar2 >> 0x11 & 3) != (uVar8 & 3)) {
            Aska::RenderState::SetAlphaToCoverage(int)(lVar24);
          }
        }
        if ((*puVar1 >> 0xb & 1) != 0) {
          Aska::RenderState::EnableStencil(Aska::StencilMode::Mode)(lVar24,1);
          Aska::RenderState::SetStencilOp(int, int, int, int, int, short)(lVar24,*(undefined1 *)(param_1 + 0x389),*(undefined1 *)(param_1 + 0x38a),
                          *(undefined1 *)(param_1 + 0x38b),*(undefined1 *)(param_1 + 0x38c),
                          *(undefined1 *)(param_1 + 0x38d),*(undefined2 *)(param_1 + 0x6a8));
        }
        lVar18 = *(long *)(*plVar27 + lVar12 * 8);
        if ((lVar18 != 0) && (*(int *)(lVar18 + 0x14) == 0)) {
          Aska::RenderState::Release()();
          *(undefined8 *)(*plVar27 + lVar12 * 8) = 0;
        }
      }
      lVar12 = lVar12 + 1;
      lVar13 = lVar13 + 0x1b8;
      lVar21 = lVar21 + 0x2a0;
    } while (lVar12 < (long)uVar20);
    if (bVar11) {
      *puVar1 = *puVar1 & 0xfffffff8 | *puVar1 & 3 | iStack_98 << 2;
    }
  }
  Aska::RenderPassManager::InvalidateObjectRenderState()(*(undefined8 *)(param_1 + 0x398));
  *(undefined1 *)((long)param_2 + 0x1a) = 1;
  return 1;
}

// ==== Aska::AofObject::InitializeRendering()
// vaddr 0x20c5a44 | ghidra 0x21c5a44 | size 8 | symbol _ZN4Aska9AofObject19InitializeRenderingEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska9AofObject19InitializeRenderingEv(void)

{
  return 1;
}

// ==== Aska::AofObject::CalcBoundingExtent(bool)
// vaddr 0x20c5a4c | ghidra 0x21c5a4c | size 684 | symbol _ZN4Aska9AofObject18CalcBoundingExtentEb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska9AofObject18CalcBoundingExtentEb(long *param_1,ulong param_2)

{
  undefined8 uVar1;
  float *pfVar2;
  long lVar3;
  long lVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  undefined4 uStack_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  float fStack_54;
  
  if (param_1[0x7b] == 0) {
    lVar4 = *(long *)(PTR__ZN4Aska16RenderableObject16m_vDefaultSphereE_02cbd4d0 + 8);
    lVar3 = *(long *)PTR__ZN4Aska16RenderableObject16m_vDefaultSphereE_02cbd4d0;
    *(byte *)(param_1 + 0x25) = *(byte *)(param_1 + 0x25) | 0x10;
    param_1[0x5b] = lVar4;
    param_1[0x5a] = lVar3;
  }
  else {
    if (((param_2 & 1) != 0) && ((*(byte *)(param_1 + 0x25) & 1) != 0)) {
      (**(code **)(*param_1 + 0xa8))(param_1);
    }
    uStack_60 = (undefined4)param_1[0x62];
    uStack_5c = *(undefined4 *)((long)param_1 + 0x314);
    uStack_58 = (undefined4)param_1[99];
    fStack_54 = 1.0;
    uVar1 = (**(code **)(*param_1 + 0x98))(param_1);
    Aska::Vector::ApplyMatrix(Aska::Matrix const*)(&uStack_60,uVar1);
    pfVar2 = (float *)(**(code **)(*param_1 + 0x98))(param_1);
    fVar10 = SQRT(*pfVar2 * *pfVar2 + pfVar2[4] * pfVar2[4] + pfVar2[8] * pfVar2[8]);
    if (NAN(fVar10)) {
      fVar10 = (float)sqrtf();
    }
    lVar3 = (**(code **)(*param_1 + 0x98))(param_1);
    fVar11 = SQRT(*(float *)(lVar3 + 4) * *(float *)(lVar3 + 4) +
                  *(float *)(lVar3 + 0x14) * *(float *)(lVar3 + 0x14) +
                  *(float *)(lVar3 + 0x24) * *(float *)(lVar3 + 0x24));
    if (NAN(fVar11)) {
      fVar11 = (float)sqrtf();
    }
    lVar3 = (**(code **)(*param_1 + 0x98))(param_1);
    fVar12 = SQRT(*(float *)(lVar3 + 8) * *(float *)(lVar3 + 8) +
                  *(float *)(lVar3 + 0x18) * *(float *)(lVar3 + 0x18) +
                  *(float *)(lVar3 + 0x28) * *(float *)(lVar3 + 0x28));
    if (NAN(fVar12)) {
      fVar12 = (float)sqrtf();
    }
    fStack_54 = fVar10;
    if (fVar10 <= fVar11) {
      fStack_54 = fVar11;
    }
    if (fStack_54 <= fVar12) {
      fStack_54 = fVar12;
    }
    fStack_54 = *(float *)((long)param_1 + 0x31c) * fStack_54;
    fVar6 = *(float *)(param_1 + 0x6a);
    fVar5 = fVar11 * *(float *)((long)param_1 + 0x344);
    fVar7 = *(float *)(param_1 + 0x6b);
    fVar14 = *(float *)(param_1 + 0x6c);
    fVar9 = *(float *)((long)param_1 + 0x364);
    fVar8 = *(float *)(param_1 + 0x6d);
    fVar5 = SQRT(fVar10 * *(float *)(param_1 + 0x68) * fVar10 * *(float *)(param_1 + 0x68) +
                 fVar5 * fVar5 +
                 fVar12 * *(float *)(param_1 + 0x69) * fVar12 * *(float *)(param_1 + 0x69));
    fVar13 = fVar11 * *(float *)((long)param_1 + 0x354);
    if (NAN(fVar5)) {
      fVar5 = (float)sqrtf();
    }
    fVar6 = SQRT(fVar10 * fVar6 * fVar10 * fVar6 + fVar13 * fVar13 + fVar12 * fVar7 * fVar12 * fVar7
                );
    fVar11 = fVar11 * fVar9;
    if (NAN(fVar6)) {
      fVar6 = (float)sqrtf();
    }
    fVar11 = fVar10 * fVar14 * fVar10 * fVar14 + fVar11 * fVar11 + fVar12 * fVar8 * fVar12 * fVar8;
    fVar10 = SQRT(fVar11);
    if (NAN(fVar10)) {
      fVar10 = (float)sqrtf(fVar11);
    }
    *(byte *)(param_1 + 0x25) = *(byte *)(param_1 + 0x25) | 0x10;
    param_1[0x5b] = CONCAT44(fStack_54,uStack_58);
    param_1[0x5a] = CONCAT44(uStack_5c,uStack_60);
    *(float *)(param_1 + 0x66) = fVar5 * *(float *)(param_1 + 0xa2);
    *(float *)((long)param_1 + 0x334) = fVar6 * *(float *)((long)param_1 + 0x514);
    *(float *)(param_1 + 0x67) = fVar10 * *(float *)(param_1 + 0xa3);
    *(undefined4 *)((long)param_1 + 0x33c) = 0x3f800000;
  }
  return;
}

// ==== Aska::AofObject::RenderingDecided()
// vaddr 0x20c5cf8 | ghidra 0x21c5cf8 | size 220 | symbol _ZN4Aska9AofObject16RenderingDecidedEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska9AofObject16RenderingDecidedEv(long param_1)

{
  ulong uVar1;
  long *plVar2;
  
  if (*(long *)(param_1 + 0x180) != 0) {
    Aska::HierarchicalObject::UpdateSimpleDynamics(Aska::AFF::SimpleDynamicsParameters const*)(param_1,param_1 + 0x620);
  }
  plVar2 = *(long **)(param_1 + 0x3a0);
  if (plVar2 != (long *)0x0) {
    if ((*(byte *)((long)plVar2 + 10) >> 1 & 1) != 0) {
      Aska::AofHandler::InitializeSkinPaletteConstant(Aska::SkinMatricesBase*)(*(undefined8 *)(param_1 + 0x3d8),plVar2);
      plVar2 = *(long **)(param_1 + 0x3a0);
    }
    uVar1 = (**(code **)(*plVar2 + 0x10))(plVar2);
    if ((uVar1 & 1) == 0) {
      *(undefined2 *)(param_1 + 0x37c) = *(undefined2 *)(param_1 + 0x37c);
      *(uint *)(param_1 + 0x378) = *(uint *)(param_1 + 0x378) & 0xfffffeff;
    }
    else {
      *(undefined2 *)(param_1 + 0x37c) = *(undefined2 *)(param_1 + 0x37c);
      *(uint *)(param_1 + 0x378) = *(uint *)(param_1 + 0x378) | 0x100;
      if (*(long *)(param_1 + 0x180) != 0) {
        (**(code **)(**(long **)(param_1 + 0x3a0) + 0x18))
                  (*(long **)(param_1 + 0x3a0),param_1 + 0x620);
      }
    }
  }
  if (((*(uint *)(param_1 + 0x1b0) & 7) != 0) ||
     (((*(uint *)(param_1 + 0x1b0) & 0x600) != 0 && ((*(byte *)(param_1 + 400) & 0x1c) != 0)))) {
    *(undefined8 *)(param_1 + 0x188) = 0;
  }
  return;
}

// ==== Aska::AofObject::ResetDynamicShaderModifier()
// vaddr 0x20c5dd4 | ghidra 0x21c5dd4 | size 16 | symbol _ZN4Aska9AofObject26ResetDynamicShaderModifierEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska9AofObject26ResetDynamicShaderModifierEv(long param_1)

{
  if (*(long *)(param_1 + 0x398) != 0) {
    (*(code *)PTR__ZN4Aska17RenderPassManager31InvalidateDynamicShaderModifierEv_02ca06e8)();
    return;
  }
  return;
}

// ==== Aska::AofObject::ResetDynamicShaderModifierCache()
// vaddr 0x20c5de4 | ghidra 0x21c5de4 | size 16 | symbol _ZN4Aska9AofObject31ResetDynamicShaderModifierCacheEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska9AofObject31ResetDynamicShaderModifierCacheEv(long param_1)

{
  if (*(long *)(param_1 + 0x398) != 0) {
    (*(code *)PTR__ZN4Aska17RenderPassManager36InvalidateDynamicShaderModifierCacheEv_02cb0d78)();
    return;
  }
  return;
}

// ==== Aska::AofObject::SetShadowManagerIndex(int, unsigned long)
// vaddr 0x20c5df4 | ghidra 0x21c5df4 | size 224 | symbol _ZN4Aska9AofObject21SetShadowManagerIndexEim | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska9AofObject21SetShadowManagerIndexEim
               (long param_1,undefined4 param_2,undefined8 param_3)

{
  long *plVar1;
  long lVar2;
  long lVar3;
  int *piVar4;
  
  lVar3 = *(long *)(param_1 + 0x398);
  if (lVar3 == 0) {
    lVar2 = *(long *)(param_1 + 0x3d8);
    if (lVar2 == 0) {
      return;
    }
    for (lVar3 = *(long *)(lVar2 + 0x138); lVar2 + 0x128 != lVar3; lVar3 = *(long *)(lVar3 + 0x10))
    {
      if ((*(short *)(lVar3 + 0x7a) == 0) && (piVar4 = (int *)(lVar3 + 0x90), *piVar4 == 0)) {
        Aska::RenderPassManager::InvalidateAll()(lVar3);
        goto code_r0x021c5e88;
      }
    }
    plVar1 = (long *)(lVar2 + 0x120);
    lVar3 = Aska::RenderPassManagerList::CreateCopy()(plVar1);
    if (lVar3 == 0) {
      *(undefined8 *)(param_1 + 0x398) = 0;
      return;
    }
    (**(code **)(*plVar1 + 0x10))(plVar1,lVar3);
    piVar4 = (int *)(lVar3 + 0x90);
code_r0x021c5e88:
    *piVar4 = 0x1000000;
    *(long *)(param_1 + 0x398) = lVar3;
  }
  lVar2 = Aska::RenderPassManager::GetPass(int, int)(lVar3,1,param_2);
  if ((lVar2 != 0) || (lVar2 = Aska::RenderPassManager::CreateShaderNodeSystemModifiers(int)(lVar3,param_2), lVar2 != 0)) {
    *(undefined8 *)(lVar2 + 0x50) = param_3;
  }
  return;
}

// ==== Aska::AofObject::GetShadowManagerIndex(int)
// vaddr 0x20c5ed4 | ghidra 0x21c5ed4 | size 44 | symbol _ZN4Aska9AofObject21GetShadowManagerIndexEi | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska9AofObject21GetShadowManagerIndexEi(long param_1,undefined4 param_2)

{
  long lVar1;
  undefined8 uVar2;
  
  uVar2 = 0;
  if (*(long *)(param_1 + 0x398) != 0) {
    lVar1 = Aska::RenderPassManager::GetPass(int, int)(*(long *)(param_1 + 0x398),1,param_2);
    uVar2 = 0;
    if (lVar1 != 0) {
      uVar2 = *(undefined8 *)(lVar1 + 0x50);
    }
  }
  return uVar2;
}

// ==== Aska::AofObject::GetShaderAdapterCache(int)
// vaddr 0x20c5f00 | ghidra 0x21c5f00 | size 212 | symbol _ZN4Aska9AofObject21GetShaderAdapterCacheEi | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska9AofObject21GetShaderAdapterCacheEi(long param_1,undefined4 param_2)

{
  long *plVar1;
  long lVar2;
  long lVar3;
  int *piVar4;
  
  lVar3 = *(long *)(param_1 + 0x398);
  if (lVar3 == 0) {
    lVar2 = *(long *)(param_1 + 0x3d8);
    if (lVar2 != 0) {
      for (lVar3 = *(long *)(lVar2 + 0x138); lVar2 + 0x128 != lVar3; lVar3 = *(long *)(lVar3 + 0x10)
          ) {
        if ((*(short *)(lVar3 + 0x7a) == 0) && (piVar4 = (int *)(lVar3 + 0x90), *piVar4 == 0)) {
          Aska::RenderPassManager::InvalidateAll()(lVar3);
          goto code_r0x021c5f90;
        }
      }
      plVar1 = (long *)(lVar2 + 0x120);
      lVar3 = Aska::RenderPassManagerList::CreateCopy()(plVar1);
      if (lVar3 != 0) {
        (**(code **)(*plVar1 + 0x10))(plVar1,lVar3);
        piVar4 = (int *)(lVar3 + 0x90);
code_r0x021c5f90:
        *piVar4 = 0x1000000;
        *(long *)(param_1 + 0x398) = lVar3;
        goto code_r0x021c5f9c;
      }
      *(undefined8 *)(param_1 + 0x398) = 0;
    }
    lVar3 = 0;
  }
  else {
code_r0x021c5f9c:
    lVar2 = Aska::RenderPassManager::GetPass(int, int)(lVar3,1,param_2);
    lVar3 = 0;
    if (lVar2 != 0) {
      lVar3 = lVar2 + 0x1a0;
    }
  }
  return lVar3;
}

// ==== Aska::AofObject::GetShaderAdapterCacheSize() const
// vaddr 0x20c5fd4 | ghidra 0x21c5fd4 | size 8 | symbol _ZNK4Aska9AofObject25GetShaderAdapterCacheSizeEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska9AofObject25GetShaderAdapterCacheSizeEv(void)

{
  return 4;
}

// ==== Aska::AofObject::SetShaderAdapterCacheCount(int, int)
// vaddr 0x20c5fdc | ghidra 0x21c5fdc | size 208 | symbol _ZN4Aska9AofObject26SetShaderAdapterCacheCountEii | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska9AofObject26SetShaderAdapterCacheCountEii
               (long param_1,undefined4 param_2,undefined1 param_3)

{
  long *plVar1;
  long lVar2;
  long lVar3;
  int *piVar4;
  
  lVar3 = *(long *)(param_1 + 0x398);
  if (lVar3 == 0) {
    lVar2 = *(long *)(param_1 + 0x3d8);
    if (lVar2 == 0) {
      return;
    }
    for (lVar3 = *(long *)(lVar2 + 0x138); lVar2 + 0x128 != lVar3; lVar3 = *(long *)(lVar3 + 0x10))
    {
      if ((*(short *)(lVar3 + 0x7a) == 0) && (piVar4 = (int *)(lVar3 + 0x90), *piVar4 == 0)) {
        Aska::RenderPassManager::InvalidateAll()(lVar3);
        goto code_r0x021c6070;
      }
    }
    plVar1 = (long *)(lVar2 + 0x120);
    lVar3 = Aska::RenderPassManagerList::CreateCopy()(plVar1);
    if (lVar3 == 0) {
      *(undefined8 *)(param_1 + 0x398) = 0;
      return;
    }
    (**(code **)(*plVar1 + 0x10))(plVar1,lVar3);
    piVar4 = (int *)(lVar3 + 0x90);
code_r0x021c6070:
    *piVar4 = 0x1000000;
    *(long *)(param_1 + 0x398) = lVar3;
  }
  lVar3 = Aska::RenderPassManager::GetPass(int, int)(lVar3,1,param_2);
  if (lVar3 != 0) {
    *(undefined1 *)(lVar3 + 0x2a) = param_3;
  }
  return;
}

// ==== Aska::AofObject::IsAffectingLight(Aska::Light*)
// vaddr 0x20c60ac | ghidra 0x21c60ac | size 112 | symbol _ZN4Aska9AofObject16IsAffectingLightEPNS_5LightE | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZN4Aska9AofObject16IsAffectingLightEPNS_5LightE(long param_1,long param_2)

{
  long lVar1;
  long lVar2;
  ulong uVar3;
  
  uVar3 = (ulong)(*(byte *)(param_1 + 0x387) ^ 1);
  if (*(long *)(param_1 + 0x3c0) == 0) {
    lVar2 = *(long *)(param_1 + uVar3 * 8 + 0x3c8);
  }
  else {
    lVar2 = *(long *)(param_1 + 0x3c0) + uVar3 * 0x1a90;
  }
  uVar3 = 0;
  do {
    if (3 < (long)uVar3) {
      if (*(long *)(lVar2 + 0x500) != param_2) {
        return (ulong)(*(long *)(lVar2 + 0x508) == param_2);
      }
      return 1;
    }
    lVar1 = uVar3 * 8;
    uVar3 = uVar3 + 1;
  } while (*(long *)(lVar2 + 0x4e0 + lVar1) != param_2);
  return uVar3;
}

// ==== Aska::AofObject::PrepareLightContext(Aska::LightManager*)
// vaddr 0x20c611c | ghidra 0x21c611c | size 180 | symbol _ZN4Aska9AofObject19PrepareLightContextEPNS_12LightManagerE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska9AofObject19PrepareLightContextEPNS_12LightManagerE(long param_1,undefined8 param_2)

{
  byte bVar1;
  long lVar2;
  long lVar3;
  
  lVar3 = *(long *)(param_1 + 0x3d8);
  if ((lVar3 != 0) && ((*(byte *)(lVar3 + 0xa8) & 1) != 0)) {
    if (*(long *)(param_1 + 0x3c0) == 0) {
      lVar2 = Aska::RenderContextServer::GetLightContext(int)(*(undefined8 *)
                               (*(long *)PTR__ZN4Aska6Global16m_pObjectManagerE_02cc4688 + 0x1000),1
                             );
      *(long *)(param_1 + (ulong)*(byte *)(param_1 + 0x387) * 8 + 0x3c8) = lVar2;
      if (lVar2 == 0) {
        return;
      }
      lVar3 = 0;
    }
    else {
      lVar3 = lVar3 + 0x10e;
      lVar2 = *(long *)(param_1 + 0x3c0) + (ulong)*(byte *)(param_1 + 0x387) * 0x1a90;
    }
    Aska::LightManager::MakeLightContext(Aska::AofObject*, Aska::LightManager::LightContext*, unsigned char*)(param_2,param_1,lVar2,lVar3);
    *(ushort *)(param_1 + 0x1b5) = *(ushort *)(param_1 + 0x1b5) | 2;
    bVar1 = *(byte *)(param_1 + 0x387) ^ 1;
    *(byte *)(param_1 + 0x387) = bVar1;
    *(undefined8 *)(param_1 + (ulong)bVar1 * 8 + 0x3c8) = 0;
  }
  return;
}

// ==== Aska::AofObject::PrepareLightContextPost(Aska::LightManager*)
// vaddr 0x20c61d0 | ghidra 0x21c61d0 | size 92 | symbol _ZN4Aska9AofObject23PrepareLightContextPostEPNS_12LightManagerE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska9AofObject23PrepareLightContextPostEPNS_12LightManagerE
               (long param_1,undefined8 param_2)

{
  long lVar1;
  long lVar2;
  ulong uVar3;
  
  lVar2 = *(long *)(param_1 + 0x3d8);
  if ((lVar2 != 0) && ((*(byte *)(lVar2 + 0xa8) & 1) != 0)) {
    uVar3 = (ulong)(*(byte *)(param_1 + 0x387) ^ 1);
    if (*(long *)(param_1 + 0x3c0) == 0) {
      lVar1 = *(long *)(param_1 + uVar3 * 8 + 0x3c8);
      lVar2 = 0;
    }
    else {
      lVar1 = *(long *)(param_1 + 0x3c0) + uVar3 * 0x1a90;
      lVar2 = lVar2 + 0x10e;
    }
    (*(code *)
      PTR__ZN4Aska12LightManager20MakeLightContextPostEPNS_9AofObjectEPNS0_12LightContextEPh_02cb3350
    )(param_2,param_1,lVar1,lVar2);
    return;
  }
  return;
}

// ==== Aska::AofObject::PrepareIBLContext(Aska::LightManager*, Aska::Light**)
// vaddr 0x20c622c | ghidra 0x21c622c | size 244 | symbol _ZN4Aska9AofObject17PrepareIBLContextEPNS_12LightManagerEPPNS_5LightE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska9AofObject17PrepareIBLContextEPNS_12LightManagerEPPNS_5LightE
               (long param_1,undefined8 param_2,undefined8 param_3)

{
  undefined *puVar1;
  int iVar2;
  long lVar3;
  long lVar4;
  ulong uVar5;
  
  puVar1 = PTR__ZN4Aska12g_pRenderDevE_02cbb1a0;
  if ((*(long *)(param_1 + 0x3d8) == 0) || ((*(byte *)(*(long *)(param_1 + 0x3d8) + 0xa8) & 1) == 0)
     ) {
    return;
  }
  iVar2 = Aska::RenderDeviceGL::GetGLVersion() const(*(undefined8 *)PTR__ZN4Aska12g_pRenderDevE_02cbb1a0);
  if (iVar2 == 0) {
    if (((bRam0000000002dcdd40 & 1) == 0) && (iVar2 = __cxa_guard_acquire(0x2dcdd40), iVar2 != 0)) {
      bRam0000000002dcdd38 = Aska::RenderDeviceGL::IsSupported(Aska::GLExtension::E) const(*(undefined8 *)puVar1,0x14);
      bRam0000000002dcdd38 = bRam0000000002dcdd38 & 1;
      __cxa_guard_release(0x2dcdd40);
    }
    if (bRam0000000002dcdd38 == 0) {
      return;
    }
  }
  uVar5 = (ulong)(*(byte *)(param_1 + 0x387) ^ 1);
  if (*(long *)(param_1 + 0x3c0) == 0) {
    lVar3 = *(long *)(param_1 + uVar5 * 8 + 0x3c8);
    lVar4 = 0;
  }
  else {
    lVar3 = *(long *)(param_1 + 0x3c0) + uVar5 * 0x1a90;
    lVar4 = *(long *)(param_1 + 0x3d8) + 0x10e;
  }
  (*(code *)PTR__ZN4Aska12LightManager14MakeIBLContextEPPNS_5LightEPfPNS0_12LightContextEPh_02ca1b00
  )(param_2,param_3,param_1 + 0x240,lVar3,lVar4);
  return;
}

// ==== Aska::AofObject::EnableObjectMotionBlur(bool)
// vaddr 0x20c6320 | ghidra 0x21c6320 | size 236 | symbol _ZN4Aska9AofObject22EnableObjectMotionBlurEb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska9AofObject22EnableObjectMotionBlurEb(long *param_1,uint param_2)

{
  uint uVar1;
  long *plVar2;
  uint uVar3;
  long lVar4;
  long lVar5;
  
  uVar3 = *(uint *)(param_1 + 0x33);
  uVar1 = uVar3;
  if ((param_2 & 1) != 0) {
    if ((uVar3 >> 0x1a & 1) == 0) {
      plVar2 = (long *)(**(code **)(*param_1 + 0x98))(param_1);
      lVar5 = *plVar2;
      param_1[0xad] = plVar2[1];
      param_1[0xac] = lVar5;
      lVar5 = plVar2[2];
      param_1[0xaf] = plVar2[3];
      param_1[0xae] = lVar5;
      lVar5 = plVar2[4];
      param_1[0xb1] = plVar2[5];
      param_1[0xb0] = lVar5;
      lVar5 = plVar2[6];
      param_1[0xb3] = plVar2[7];
      param_1[0xb2] = lVar5;
      if ((param_1[0x74] != 0) && ((*(byte *)(param_1[0x74] + 10) >> 1 & 1) != 0)) {
        Aska::SkinMatricesBase::Init3rdTexturePalette()();
      }
    }
    uVar3 = *(uint *)(param_1 + 0x33);
    uVar1 = uVar3 & 0x4000000;
  }
  if (((((param_2 ^ uVar1 >> 0x1a) & 1) != 0) && (param_1[0x74] != 0)) &&
     ((*(byte *)(param_1[0x74] + 10) >> 1 & 1) != 0)) {
    lVar4 = *(long *)(param_1[0x7b] + 0x138);
    lVar5 = param_1[0x7b] + 0x128;
    if (lVar5 != lVar4) {
      do {
        Aska::RenderPass::InvalidateShaders()(*(undefined8 *)(lVar4 + 0x18));
        Aska::RenderPassManager::InvalidateShaders(bool)(lVar4,0);
        lVar4 = *(long *)(lVar4 + 0x10);
      } while (lVar5 != lVar4);
      uVar3 = *(uint *)(param_1 + 0x33);
    }
  }
  uVar1 = uVar3 | 0x4000000;
  if ((param_2 & 1) == 0) {
    uVar1 = uVar3 & 0xfbffffff;
  }
  *(uint *)(param_1 + 0x33) = uVar1;
  return;
}

// ==== Aska::AofObject::PreliminarilyPrepare(Aska::LightManager*)
// vaddr 0x20c640c | ghidra 0x21c640c | size 776 | symbol _ZN4Aska9AofObject20PreliminarilyPrepareEPNS_12LightManagerE | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska9AofObject20PreliminarilyPrepareEPNS_12LightManagerE(long param_1,undefined8 param_2)

{
  long *plVar1;
  ushort uVar2;
  uint uVar3;
  uint uVar4;
  ushort uVar5;
  ulong uVar6;
  long lVar7;
  ulong uVar8;
  ushort uVar9;
  long lVar10;
  int *piVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  
  DataMemoryBarrier(2,3);
  if (((*(int *)(param_1 + 0x1ac) != 0) && (lVar7 = *(long *)(param_1 + 0x3d8), lVar7 != 0)) &&
     ((*(byte *)(lVar7 + 0xa8) & 1) != 0)) {
    uVar3 = *(uint *)(param_1 + 0x378);
    if ((*(long *)(param_1 + 0x3a0) == 0) || ((uVar3 >> 8 & 1) != 0)) {
      uVar6 = (ulong)uVar3 | ((ulong)*(ushort *)(param_1 + 0x37c) & 0xfe9f) << 0x20;
      *(undefined1 *)(param_1 + 0x38f) = 0;
      *(undefined8 *)(param_1 + 0x3a8) = param_2;
      *(uint *)(param_1 + 0x378) = uVar3;
      uVar8 = uVar6 | 0x2000000000;
      *(short *)(param_1 + 0x37c) = (short)(uVar8 >> 0x20);
      uVar4 = *(uint *)(param_1 + 0x198);
      *(undefined8 *)(param_1 + 1000) = 0;
      *(undefined8 *)(param_1 + 0x3e0) = 0;
      *(uint *)(param_1 + 0x198) = uVar4 | 0x2000000;
      *(undefined4 *)(param_1 + 0x3b0) = 0;
      if (*(char *)(param_1 + 0x1b7) == '\x11') {
        uVar8 = uVar6 | 0x6000000000;
        *(uint *)(param_1 + 0x378) = uVar3;
        *(short *)(param_1 + 0x37c) = (short)(uVar8 >> 0x20);
      }
      uVar5 = *(ushort *)(param_1 + 0x390);
      fVar12 = (float)*(undefined8 *)(param_1 + 0x270);
      if (((((float)((ulong)*(undefined8 *)(param_1 + 0x3f0) >> 0x20) ==
             (float)((ulong)*(undefined8 *)(param_1 + 0x270) >> 0x20) &&
            (float)*(undefined8 *)(param_1 + 0x3f0) == fVar12) &&
           (float)*(undefined8 *)(param_1 + 0x3f8) == (float)*(undefined8 *)(param_1 + 0x278)) &&
           (float)((ulong)*(undefined8 *)(param_1 + 0x3f8) >> 0x20) ==
           (float)((ulong)*(undefined8 *)(param_1 + 0x278) >> 0x20)) &&
         (fVar13 = (float)*(undefined8 *)(param_1 + 0x280),
         (float)((ulong)*(undefined8 *)(param_1 + 0x408) >> 0x20) ==
         (float)((ulong)*(undefined8 *)(param_1 + 0x288) >> 0x20) &&
         ((float)*(undefined8 *)(param_1 + 0x408) == (float)*(undefined8 *)(param_1 + 0x288) &&
         ((float)*(undefined8 *)(param_1 + 0x400) == fVar13 &&
         (float)((ulong)*(undefined8 *)(param_1 + 0x400) >> 0x20) ==
         (float)((ulong)*(undefined8 *)(param_1 + 0x280) >> 0x20))))) {
        fVar14 = *(float *)(param_1 + 0x274);
        fVar15 = *(float *)(param_1 + 0x278);
        fVar16 = *(float *)(param_1 + 0x27c);
        uVar9 = uVar5;
      }
      else {
        fVar14 = *(float *)(param_1 + 0x274);
        fVar15 = *(float *)(param_1 + 0x278);
        fVar16 = *(float *)(param_1 + 0x27c);
        if (0.0001 < ABS(fVar16 + -1.0) ||
            (0.0001 < ABS(fVar15 + -1.0) ||
            (0.0001 < ABS(fVar12 + -1.0) || 0.0001 < ABS(fVar14 + -1.0)))) {
          fVar13 = *(float *)(param_1 + 0x280);
        }
        else {
          fVar13 = (float)*(undefined8 *)(param_1 + 0x280);
          if (ABS((float)((ulong)*(undefined8 *)(param_1 + 0x288) >> 0x20)) <= 0.0001 &&
              (ABS((float)*(undefined8 *)(param_1 + 0x288)) <= 0.0001 &&
              (ABS(fVar13) <= 0.0001 &&
              ABS((float)((ulong)*(undefined8 *)(param_1 + 0x280) >> 0x20)) <= 0.0001))) {
            uVar9 = uVar5 & 0xefff;
            goto code_r0x021c65dc;
          }
        }
        uVar9 = uVar5 | 0x1000;
      }
code_r0x021c65dc:
      *(float *)(param_1 + 0x3f0) = fVar12;
      *(float *)(param_1 + 0x3f4) = fVar14;
      *(float *)(param_1 + 0x3f8) = fVar15;
      *(float *)(param_1 + 0x3fc) = fVar16;
      *(float *)(param_1 + 0x400) = fVar13;
      *(undefined4 *)(param_1 + 0x404) = *(undefined4 *)(param_1 + 0x284);
      *(undefined4 *)(param_1 + 0x408) = *(undefined4 *)(param_1 + 0x288);
      *(undefined4 *)(param_1 + 0x40c) = *(undefined4 *)(param_1 + 0x28c);
      if ((((uint)uVar8 >> 10 & 1) != 0) || (*(char *)(param_1 + 0x699) == '\x01')) {
        uVar9 = uVar9 | 0x1000;
      }
      if (((uVar4 >> 0x16 & 1) == 0) && ((*(byte *)(param_1 + 0x1b0) >> 4 & 1) != 0)) {
        uVar9 = uVar9 & 0xbfff;
      }
      else {
        uVar9 = uVar9 | 0x4000;
      }
      uVar2 = uVar9 | 0x80;
      if ((uVar8 & 0x40000000) != 0) {
        uVar2 = uVar9 & 0xff7f;
      }
      uVar9 = uVar2 | 4;
      if (*(char *)(*(long *)(lVar7 + 0xb0) + 0x97) == '\0') {
        uVar9 = uVar2 & 0xfffb;
      }
      if (uVar9 != uVar5) {
        lVar10 = *(long *)(param_1 + 0x398);
        *(ushort *)(param_1 + 0x390) = uVar9;
        if (lVar10 == 0) {
          for (lVar10 = *(long *)(lVar7 + 0x138); lVar7 + 0x128 != lVar10;
              lVar10 = *(long *)(lVar10 + 0x10)) {
            if ((*(short *)(lVar10 + 0x7a) == 0) &&
               (piVar11 = (int *)(lVar10 + 0x90), *piVar11 == 0)) {
              Aska::RenderPassManager::InvalidateAll()(lVar10);
              goto code_r0x021c66ec;
            }
          }
          plVar1 = (long *)(lVar7 + 0x120);
          lVar10 = Aska::RenderPassManagerList::CreateCopy()(plVar1);
          if (lVar10 == 0) {
            *(undefined8 *)(param_1 + 0x398) = 0;
            return 0;
          }
          (**(code **)(*plVar1 + 0x10))(plVar1,lVar10);
          piVar11 = (int *)(lVar10 + 0x90);
code_r0x021c66ec:
          *piVar11 = 0x1000000;
          *(long *)(param_1 + 0x398) = lVar10;
        }
        *(undefined1 *)(lVar10 + 0x7d) = 1;
      }
      DataMemoryBarrier(2,3);
      *(undefined4 *)(param_1 + 0x1c0) = *(undefined4 *)(param_1 + 0x1ac);
      return 1;
    }
  }
  return 0;
}

// ==== Aska::AofObject::IsPBAmbientBRDFEnabled() const
// vaddr 0x20c6714 | ghidra 0x21c6714 | size 16 | symbol _ZNK4Aska9AofObject22IsPBAmbientBRDFEnabledEv | lib libSOA-3.7.0.so | 2026-10-04
undefined1 _ZNK4Aska9AofObject22IsPBAmbientBRDFEnabledEv(long param_1)

{
  return *(undefined1 *)(*(long *)(*(long *)(param_1 + 0x3d8) + 0xb0) + 0x97);
}

// ==== Aska::AofObject::GetColorPass(Aska::RENDERINFO const*)
// vaddr 0x20c6724 | ghidra 0x21c6724 | size 2028 | symbol _ZN4Aska9AofObject12GetColorPassEPKNS_10RENDERINFOE | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Possible PIC construction at 0x021c6d98: Changing call to branch */
/* WARNING: Possible PIC construction at 0x021c6f00: Changing call to branch */
/* WARNING: Removing unreachable block (ram,0x021c6d9c) */
/* WARNING: Removing unreachable block (ram,0x021c6e00) */
/* WARNING: Removing unreachable block (ram,0x021c6da4) */
/* WARNING: Removing unreachable block (ram,0x021c6e14) */
/* WARNING: Removing unreachable block (ram,0x021c6db0) */
/* WARNING: Removing unreachable block (ram,0x021c6db8) */
/* WARNING: Removing unreachable block (ram,0x021c6dc4) */
/* WARNING: Removing unreachable block (ram,0x021c6ddc) */
/* WARNING: Removing unreachable block (ram,0x021c6f04) */
/* WARNING: Removing unreachable block (ram,0x021c6e18) */
/* WARNING: Removing unreachable block (ram,0x021c6e48) */
/* WARNING: Removing unreachable block (ram,0x021c6e78) */
/* WARNING: Removing unreachable block (ram,0x021c6ea0) */
/* WARNING: Removing unreachable block (ram,0x021c6ea4) */
/* WARNING: Removing unreachable block (ram,0x021c6e88) */
/* WARNING: Removing unreachable block (ram,0x021c6ea8) */
/* WARNING: Removing unreachable block (ram,0x021c6e9c) */
/* WARNING: Removing unreachable block (ram,0x021c6eb8) */

undefined8 _ZN4Aska9AofObject12GetColorPassEPKNS_10RENDERINFOE(long *param_1,short *param_2)

{
  char cVar1;
  undefined4 uVar2;
  byte bVar3;
  ushort uVar4;
  short sVar5;
  bool bVar6;
  int iVar7;
  int iVar8;
  undefined8 uVar9;
  int iVar10;
  ulong uVar11;
  ulong uVar12;
  byte *pbVar13;
  long lVar14;
  long lVar15;
  long lVar16;
  uint uVar17;
  uint uVar18;
  ulong uVar19;
  ulong uVar20;
  long lVar21;
  long lVar22;
  long *plVar23;
  byte *pbVar24;
  long lVar25;
  undefined8 uStack_e8;
  undefined4 uStack_e0;
  undefined1 uStack_dc;
  long alStack_d8 [5];
  undefined1 auStack_b0 [80];
  
  sVar5 = *param_2;
  uVar19 = (ulong)sVar5;
  lVar25 = param_1[0x73];
  uVar20 = 1L << (uVar19 & 0x3f);
  if ((uVar20 & param_1[((long)uVar19 >> 6) + 0x7c]) == 0) {
    if (sVar5 != 0) {
      *(ushort *)((long)param_1 + 0x37c) = *(ushort *)((long)param_1 + 0x37c) | 0x100;
    }
    uVar4 = *(ushort *)((long)param_1 + 0x65a);
    uVar17 = (uint)uVar4;
    if (uVar17 == 0) {
      lVar21 = 0;
    }
    else {
      uVar18 = (uint)uVar4;
      if (param_1[0xca] == 0) {
        iVar10 = -5;
        if (0xfffffffa < -uVar17 && uVar17 != 5) {
          iVar10 = -uVar18;
        }
        memcpy(alStack_d8,param_1 + 0xcd,(iVar10 << 3 ^ 0xfffffff8U) + 8);
        lVar14 = 0;
        do {
          lVar21 = lVar14 + 1;
          if ((long)(ulong)uVar4 <= lVar21) break;
          bVar6 = lVar14 != 4;
          lVar14 = lVar21;
        } while (bVar6);
      }
      else {
        iVar10 = -5;
        if (0xfffffffa < -uVar18 && uVar18 != 5) {
          iVar10 = -uVar18;
        }
        memcpy(alStack_d8,param_1[0xca],(iVar10 << 3 ^ 0xfffffff8U) + 8);
        lVar14 = 0;
        do {
          lVar21 = lVar14 + 1;
          if ((long)(ulong)uVar4 <= lVar21) break;
          bVar6 = lVar14 != 4;
          lVar14 = lVar21;
        } while (bVar6);
      }
    }
    bVar6 = false;
    cVar1 = *PTR__ZN4Aska9AofObject28m_nSpecialShadowAdapterLimitE_02cbb5f0;
    if ((char)param_1[0x70] != -1) {
      cVar1 = (char)param_1[0x70];
    }
    if ((sVar5 == 0) && (param_1[0x78] == 0)) {
      bVar6 = (*(ushort *)((long)param_1 + 0x37c) & 0x100) == 0;
    }
    uStack_dc = 0;
    uStack_e0 = 0;
    lVar14 = *(long *)PTR__ZN4Aska6Global16m_pObjectManagerE_02cc4688;
    uStack_e8 = (**(code **)(*param_1 + 0x178))(param_1,uVar19 & 0xffffffff);
    if ((int)lVar21 != 5) {
      lVar22 = 0;
      iVar10 = 1;
      uVar12 = (long)(int)lVar21;
      while( true ) {
        bVar3 = *(byte *)((long)&uStack_e8 + lVar22);
        if (((bVar3 & 0x1f) == 0) || ((int)cVar1 <= (int)lVar22)) break;
        lVar21 = *(long *)(*(long *)(lVar14 + 0x104f0) + (ulong)((bVar3 & 0x1f) - 1) * 8 + 0x10f8);
        iVar7 = (**(code **)(*param_1 + 0x1c0))(param_1,*(undefined8 *)(lVar21 + 0xb8));
        if ((bool)(bVar6 & iVar10 < iVar7)) {
          uVar11 = (ulong)(*(byte *)((long)param_1 + 0x387) ^ 1);
          if (param_1[0x78] == 0) {
            pbVar24 = (byte *)param_1[uVar11 + 0x79];
          }
          else {
            pbVar24 = (byte *)(param_1[0x78] + uVar11 * 0x1a90);
          }
          lVar16 = (long)iVar7 + -1;
          lVar15 = (long)iVar10 + -1;
          memcpy(auStack_b0,pbVar24 + lVar16 * 0x50 + 0x110,0x50);
          memcpy(pbVar24 + lVar16 * 0x50 + 0x110,pbVar24 + lVar15 * 0x50 + 0x110,0x50);
          memcpy(pbVar24 + lVar15 * 0x50 + 0x110,auStack_b0,0x50);
          uVar2 = *(undefined4 *)(pbVar24 + lVar16 * 4 + 0xa0);
          *(undefined4 *)(pbVar24 + lVar16 * 4 + 0xa0) =
               *(undefined4 *)(pbVar24 + lVar15 * 4 + 0xa0);
          *(undefined4 *)(pbVar24 + lVar15 * 4 + 0xa0) = uVar2;
          uVar9 = *(undefined8 *)(pbVar24 + lVar16 * 8 + 0x4e0);
          *(undefined8 *)(pbVar24 + lVar16 * 8 + 0x4e0) =
               *(undefined8 *)(pbVar24 + lVar15 * 8 + 0x4e0);
          *(undefined8 *)(pbVar24 + lVar15 * 8 + 0x4e0) = uVar9;
          uVar11 = (ulong)*pbVar24;
          iVar7 = iVar10;
          if (uVar11 != 0) {
            pbVar13 = pbVar24 + lVar15 * 4 + 0x510;
            pbVar24 = pbVar24 + lVar16 * 4 + 0x510;
            do {
              uVar2 = *(undefined4 *)pbVar24;
              uVar11 = uVar11 - 1;
              *(undefined4 *)pbVar24 = *(undefined4 *)pbVar13;
              *(undefined4 *)pbVar13 = uVar2;
              pbVar13 = pbVar13 + 0x10;
              pbVar24 = pbVar24 + 0x10;
            } while (uVar11 != 0);
          }
        }
        *(char *)((long)&uStack_e0 + uVar12) = (char)iVar7;
        if (iVar10 <= iVar7 + 1) {
          iVar10 = iVar7 + 1;
        }
        if (((*(byte *)(lVar21 + 0x1c5) & 1) != 0) ||
           ((*PTR__ZN4Aska13ShadowManager16m_bEnableCascadeE_02cba2e0 != '\0' &&
            (*(char *)(lVar21 + 0x1c7) != '\0')))) {
          *(ushort *)((long)param_1 + 0x37c) = *(ushort *)((long)param_1 + 0x37c) | 0x40;
        }
        lVar15 = *(long *)(lVar21 + 0x118);
        if (lVar15 == 0) {
          lVar15 = *(long *)(lVar21 + (ulong)(bVar3 >> 5) * 8 + 0x1d0);
        }
        uVar11 = uVar12 + 1;
        lVar21 = 0;
        if (lVar15 != 0) {
          lVar21 = lVar15 + 0x1f8;
        }
        alStack_d8[uVar12] = lVar21;
        if ((3 < lVar22) || (lVar22 = lVar22 + 1, uVar12 = uVar11, (int)uVar11 == 5))
        goto code_r0x021c6af4;
      }
      uVar11 = uVar12 & 0xffffffff;
code_r0x021c6af4:
      uVar17 = (uint)uVar11;
      if ((int)uVar17 < 5) {
        lVar21 = Aska::RenderPassManager::GetPass(int, int)(lVar25,1,(long)*param_2);
        if (lVar21 == 0) {
          return 0;
        }
        bVar3 = *(byte *)(lVar21 + 0x2a);
        if (bVar3 != 0) {
          plVar23 = (long *)(lVar21 + 0x1a0);
          if (bVar6) {
            iVar7 = 0;
            do {
              uVar17 = (uint)uVar11;
              if ((long *)*plVar23 == (long *)0x0) break;
              lVar21 = (**(code **)(*(long *)*plVar23 + 0x1a8))();
              if ((lVar21 == 0) || ((*(uint *)(param_1 + 0x6f) >> 4 & 1) == 0)) {
code_r0x021c6c94:
                lVar21 = 0;
                if (*plVar23 != 0) {
                  lVar21 = *plVar23 + 0x1f8;
                }
                alStack_d8[(int)uVar17] = lVar21;
                uVar18 = uVar17 + 1;
                uVar11 = (ulong)uVar18;
                bVar6 = 3 < (int)uVar17;
                plVar23 = plVar23 + 1;
                uVar17 = uVar18;
                if (bVar6) break;
              }
              else {
                iVar8 = (**(code **)(*param_1 + 0x1c0))(param_1,lVar21);
                if (iVar8 != 0) {
                  if (iVar10 < iVar8) {
                    uVar12 = (ulong)(*(byte *)((long)param_1 + 0x387) ^ 1);
                    if (param_1[0x78] == 0) {
                      pbVar24 = (byte *)param_1[uVar12 + 0x79];
                    }
                    else {
                      pbVar24 = (byte *)(param_1[0x78] + uVar12 * 0x1a90);
                    }
                    lVar14 = (long)iVar8 + -1;
                    lVar21 = (long)iVar10 + -1;
                    memcpy(auStack_b0,pbVar24 + lVar14 * 0x50 + 0x110,0x50);
                    memcpy(pbVar24 + lVar14 * 0x50 + 0x110,pbVar24 + lVar21 * 0x50 + 0x110,
                                    0x50);
                    memcpy(pbVar24 + lVar21 * 0x50 + 0x110,auStack_b0,0x50);
                    uVar2 = *(undefined4 *)(pbVar24 + lVar14 * 4 + 0xa0);
                    *(undefined4 *)(pbVar24 + lVar14 * 4 + 0xa0) =
                         *(undefined4 *)(pbVar24 + lVar21 * 4 + 0xa0);
                    *(undefined4 *)(pbVar24 + lVar21 * 4 + 0xa0) = uVar2;
                    uVar9 = *(undefined8 *)(pbVar24 + lVar14 * 8 + 0x4e0);
                    *(undefined8 *)(pbVar24 + lVar14 * 8 + 0x4e0) =
                         *(undefined8 *)(pbVar24 + lVar21 * 8 + 0x4e0);
                    *(undefined8 *)(pbVar24 + lVar21 * 8 + 0x4e0) = uVar9;
                    uVar12 = (ulong)*pbVar24;
                    iVar8 = iVar10;
                    if (uVar12 != 0) {
                      pbVar13 = pbVar24 + lVar21 * 4 + 0x510;
                      pbVar24 = pbVar24 + lVar14 * 4 + 0x510;
                      do {
                        uVar2 = *(undefined4 *)pbVar24;
                        uVar12 = uVar12 - 1;
                        *(undefined4 *)pbVar24 = *(undefined4 *)pbVar13;
                        *(undefined4 *)pbVar13 = uVar2;
                        pbVar13 = pbVar13 + 0x10;
                        pbVar24 = pbVar24 + 0x10;
                      } while (uVar12 != 0);
                    }
                  }
                  if (iVar10 <= iVar8 + 1) {
                    iVar10 = iVar8 + 1;
                  }
                  *(char *)((long)&uStack_e0 + (long)(int)uVar17) = (char)iVar8;
                  goto code_r0x021c6c94;
                }
              }
              iVar7 = iVar7 + 1;
            } while (iVar7 < (int)(uint)bVar3);
          }
          else {
            iVar10 = 0;
            do {
              uVar17 = (uint)uVar11;
              if ((long *)*plVar23 == (long *)0x0) break;
              lVar21 = (**(code **)(*(long *)*plVar23 + 0x1a8))();
              if ((lVar21 == 0) || ((*(uint *)(param_1 + 0x6f) >> 4 & 1) == 0)) {
code_r0x021c6d30:
                lVar21 = 0;
                if (*plVar23 != 0) {
                  lVar21 = *plVar23 + 0x1f8;
                }
                alStack_d8[(int)uVar17] = lVar21;
                uVar18 = uVar17 + 1;
                uVar11 = (ulong)uVar18;
                bVar6 = 3 < (int)uVar17;
                plVar23 = plVar23 + 1;
                uVar17 = uVar18;
                if (bVar6) break;
              }
              else {
                iVar7 = (**(code **)(*param_1 + 0x1c0))(param_1,lVar21);
                if (iVar7 != 0) {
                  *(char *)((long)&uStack_e0 + (long)(int)uVar17) = (char)iVar7;
                  goto code_r0x021c6d30;
                }
              }
              iVar10 = iVar10 + 1;
            } while (iVar10 < (int)(uint)bVar3);
          }
        }
        if (uVar17 == 0) {
          lVar21 = lVar25 + ((long)uVar19 >> 6) * 8;
          *(ulong *)(lVar21 + 0x80) = *(ulong *)(lVar21 + 0x80) & (uVar20 ^ 0xffffffffffffffff);
          goto code_r0x011fc6c0;
        }
      }
    }
    uVar19 = (ulong)*param_2;
  }
  else {
    uVar19 = uVar19 & 0xffffffff;
  }
code_r0x011fc6c0:
  uVar9 = (*(code *)PTR__ZN4Aska17RenderPassManager31CreateShaderNodeSystemModifiersEi_02cb6350)
                    (lVar25,uVar19);
  return uVar9;
}

// ==== Aska::AofObject::QueryPrebuiltVariation() const
// vaddr 0x20c6f10 | ghidra 0x21c6f10 | size 52 | symbol _ZNK4Aska9AofObject22QueryPrebuiltVariationEv | lib libSOA-3.7.0.so | 2026-10-04
int _ZNK4Aska9AofObject22QueryPrebuiltVariationEv(long param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = 1;
  if (*(char *)(param_1 + 0x698) == '\x02') {
    iVar2 = 2;
  }
  iVar3 = 1;
  iVar1 = iVar3;
  if (*(char *)(param_1 + 0x699) == '\x02') {
    iVar1 = 2;
  }
  if (*(char *)(param_1 + 0x69a) == '\x02') {
    iVar3 = 2;
  }
  return iVar1 * iVar2 * iVar3;
}

// ==== Aska::AofObject::GetCurrentPrebuiltVariation() const
// vaddr 0x20c6f44 | ghidra 0x21c6f44 | size 84 | symbol _ZNK4Aska9AofObject27GetCurrentPrebuiltVariationEv | lib libSOA-3.7.0.so | 2026-10-04
uint _ZNK4Aska9AofObject27GetCurrentPrebuiltVariationEv(long param_1)

{
  uint uVar1;
  
  if (*(char *)(param_1 + 0x698) == '\x02') {
    uVar1 = *(uint *)(param_1 + 0x198) >> 0x17 & 2;
  }
  else {
    uVar1 = 0;
  }
  uVar1 = uVar1 << (*(char *)(param_1 + 0x699) == '\x02');
  if (*(char *)(param_1 + 0x69a) != '\0') {
    uVar1 = (uVar1 | *(char *)(param_1 + 0x248) == '\x02') << 1;
  }
  return uVar1;
}

// ==== Aska::AofObject::SetPrebuiltVariation(int)
// vaddr 0x20c6f98 | ghidra 0x21c6f98 | size 132 | symbol _ZN4Aska9AofObject20SetPrebuiltVariationEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska9AofObject20SetPrebuiltVariationEi(long *param_1,uint param_2)

{
  uint uVar1;
  char cVar2;
  uint uVar3;
  undefined8 uVar4;
  
  if ((char)param_1[0xd3] == '\x02') {
    uVar3 = param_2 & 1;
    param_2 = (int)param_2 >> 1;
    uVar1 = *(uint *)(param_1 + 0x33) & 0xfeffffff;
    if (uVar3 != 0) {
      uVar1 = *(uint *)(param_1 + 0x33) | 0x1000000;
    }
    *(uint *)(param_1 + 0x33) = uVar1;
  }
  cVar2 = *(char *)((long)param_1 + 0x69a);
  if (cVar2 != '\0') {
    if ((1 << (*(char *)((long)param_1 + 0x699) == '\x02') & param_2) == 0) {
      uVar4 = 1;
    }
    else {
      uVar4 = 2;
    }
    (**(code **)(*param_1 + 0x250))(param_1,uVar4);
    *(char *)((long)param_1 + 0x69a) = cVar2;
  }
  return;
}

// ==== Aska::AofObject::GetMultiDrawPass(unsigned int, Aska::RENDERINFO const*)
// vaddr 0x20c701c | ghidra 0x21c701c | size 372 | symbol _ZN4Aska9AofObject16GetMultiDrawPassEjPKNS_10RENDERINFOE | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska9AofObject16GetMultiDrawPassEjPKNS_10RENDERINFOE
               (long param_1,undefined4 param_2,long param_3)

{
  uint3 uVar1;
  long lVar2;
  undefined8 uVar3;
  ulong uVar4;
  uint uVar5;
  uint uVar6;
  uint3 *puVar7;
  long lVar8;
  long lVar9;
  
  lVar8 = *(long *)(param_1 + 0x398);
  lVar9 = *(long *)(param_1 + 0x3d8);
  lVar2 = Aska::RenderPassManager::GetMultiDrawPass(Aska::RenderPass*, int)(lVar8,*(undefined8 *)(lVar8 + 0x18),param_2);
  if (lVar2 != 0) {
    uVar3 = (**(code **)(**(long **)(param_1 + 0x690) + 8))(*(long **)(param_1 + 0x690),param_2);
    lVar8 = Aska::RenderPassManager::CreateShaderNodeMultiDrawModifiers(int)(lVar8,param_2);
    if (lVar8 == 0) {
      lVar2 = 0;
    }
    else {
      uVar4 = Aska::RenderPass::BeginModifyingShader()(lVar8);
      if ((uVar4 & 1) != 0) {
        uVar4 = Aska::RenderPass::AddShaderAdapter(Aska::BaseShaderAdapter*, int)(lVar8,uVar3,0);
        Aska::RenderPass::EndModifyingShader(Aska::MaterialList*)(lVar8,*(long *)(param_1 + 0x3d8) + 0xe8);
        lVar2 = lVar8;
        if ((uVar4 & 1) != 0) {
          *(ushort *)(lVar8 + 0x2f) = *(ushort *)(lVar8 + 0x2f) & 0xffbf;
        }
      }
      Aska::RenderPass::UpdateTexture(Aska::MaterialList*, Aska::TextureModifierManager*, Aska::RENDERINFO const*, int, bool)(lVar2,lVar9 + 0xe8,param_1 + 0x410,param_3,(long)*(char *)(param_3 + 5),1);
      uVar5 = (uint)*(uint3 *)(lVar2 + 0x2f);
      if ((*(byte *)(lVar2 + 0x31) & 1) == 0) {
        Aska::RenderPass::UpdateMaterial(Aska::MaterialList*)(lVar2,*(long *)(param_1 + 0x3d8) + 0xe8);
        puVar7 = (uint3 *)(lVar2 + 0x2f);
        uVar1 = *puVar7;
        *(undefined2 *)puVar7 = *(undefined2 *)puVar7;
        uVar5 = uVar1 | 0x10000;
        *(char *)(lVar2 + 0x31) = (char)(uVar5 >> 0x10);
      }
      if (*(char *)(*(long *)(param_3 + 0x10) + 0xeb2) == '\0') {
        if ((uVar5 >> 10 & 1) == 0) {
          return lVar2;
        }
        uVar6 = 0;
      }
      else {
        uVar6 = *(byte *)(param_1 + 0x19b) & 1;
        if (uVar6 == (uVar5 & 0x400) >> 10) {
          return lVar2;
        }
      }
      *(char *)(lVar2 + 0x31) = (char)(uVar5 >> 0x10);
      *(ushort *)(lVar2 + 0x2f) =
           (ushort)uVar5 & 0xf800 | (ushort)uVar5 & 0x3ff | (ushort)(uVar6 << 10);
    }
  }
  return lVar2;
}

// ==== Aska::AofObject::PrepareForRendering_Preliminary()
// vaddr 0x20c7190 | ghidra 0x21c7190 | size 1276 | symbol _ZN4Aska9AofObject31PrepareForRendering_PreliminaryEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska9AofObject31PrepareForRendering_PreliminaryEv(long *param_1)

{
  uint *puVar1;
  uint uVar2;
  byte bVar3;
  ushort uVar4;
  char cVar5;
  bool bVar6;
  int iVar7;
  long lVar8;
  long lVar9;
  long lVar10;
  long *plVar11;
  ulong uVar12;
  long lVar13;
  long lVar14;
  uint uVar15;
  long lVar16;
  long lStack_60;
  long lStack_58;
  
  lVar16 = param_1[0x7b];
  lVar14 = param_1[0x73];
  lVar10 = lVar16 + 0xe8;
  puVar1 = (uint *)(param_1 + 0x6f);
  if ((*(uint *)(param_1 + 0x6f) >> 4 & 1) == 0) goto code_r0x021c7528;
  lVar9 = lVar16;
  if ((*(byte *)((long)param_1 + 0x1b5) >> 1 & 1) == 0) {
    (**(code **)(*param_1 + 0x1b8))(param_1,param_1[0x75]);
    if ((*(byte *)((long)param_1 + 0x1b5) >> 1 & 1) == 0) {
      return 0;
    }
    lVar9 = param_1[0x7b];
  }
  if ((lVar9 != 0) && ((*(byte *)(lVar9 + 0xa8) & 1) != 0)) {
    uVar12 = (ulong)(*(byte *)((long)param_1 + 0x387) ^ 1);
    if (param_1[0x78] == 0) {
      lVar8 = param_1[uVar12 + 0x79];
      lVar9 = 0;
    }
    else {
      lVar8 = param_1[0x78] + uVar12 * 0x1a90;
      lVar9 = lVar9 + 0x10e;
    }
    Aska::LightManager::MakeLightContextPost(Aska::AofObject*, Aska::LightManager::LightContext*, unsigned char*)(param_1[0x75],param_1,lVar8,lVar9);
  }
  bVar3 = *(byte *)(param_1 + 0x71);
  cVar5 = *(char *)(lVar16 + 0x114);
  if ((int)cVar5 != (uint)bVar3) {
    Aska::MaterialList::SetShaderLod(int)(lVar10,(uint)bVar3);
    *(undefined1 *)(lVar14 + 0x7d) = 1;
  }
  uVar15 = (uint)bVar3;
  if ((*(byte *)(lVar16 + 0x109) >> 1 & 1) == 0) {
code_r0x021c72e4:
    lVar9 = param_1[0x46];
    if (lVar9 != 0) goto code_r0x021c72ec;
code_r0x021c7394:
    iVar7 = 0;
    uVar12 = 0;
  }
  else {
    uVar12 = (ulong)(*(byte *)((long)param_1 + 0x387) ^ 1);
    if (param_1[0x78] == 0) {
      lVar9 = param_1[uVar12 + 0x79];
    }
    else {
      lVar9 = param_1[0x78] + uVar12 * 0x1a90;
    }
    uVar2 = 0;
    if (*(char *)(lVar9 + 0x90) != '\0') {
      uVar2 = (*(ushort *)(param_1 + 0x72) >> 2 & 1) + 1;
    }
    if (((int)cVar5 == uVar15) && (uVar2 == (*puVar1 >> 0x1c & 3))) goto code_r0x021c72e4;
    if (((*puVar1 & 0x30000000) != 0) && (*(char *)(lVar9 + 0x90) != '\0')) {
      Aska::MaterialList::EnableAmbientBRDF(Aska::MaterialList::AmbientBRDFType)(lVar10,0);
    }
    Aska::MaterialList::EnableAmbientBRDF(Aska::MaterialList::AmbientBRDFType)(lVar10,uVar2);
    *puVar1 = *puVar1 & 0xcfffffff | uVar2 << 0x1c;
    *(undefined1 *)(lVar14 + 0x7d) = 1;
    Aska::RenderPassManager::InvalidateRenderState()(lVar14);
    lVar9 = param_1[0x46];
    if (lVar9 == 0) goto code_r0x021c7394;
code_r0x021c72ec:
    if ((*(ushort *)(lVar9 + 0x2a5) >> 3 & 1) == 0) {
      iVar7 = Aska::Light::GetIBLTextureUniqueID()(lVar9);
      lVar9 = param_1[0x46];
      if (lVar9 == 0) {
        uVar12 = 0;
        goto code_r0x021c73a4;
      }
    }
    else {
      iVar7 = 0;
    }
    if ((*(ushort *)(lVar9 + 0x2a5) >> 0xe & 1) == 0) {
      uVar12 = (ulong)(0.0 < *(float *)(lVar9 + 0x2c4));
    }
    else {
      uVar12 = 2;
    }
  }
code_r0x021c73a4:
  if (((((int)param_1[0x6e] != iVar7) ||
       (uVar4 = *(ushort *)((long)param_1 + 0x37c), ((uVar4 >> 1 ^ uVar4 >> 2) & 1) != 0)) ||
      ((int)cVar5 != uVar15)) || ((uVar4 >> 3 & 3) != (uint)uVar12)) {
    if ((int)param_1[0x6e] != 0) {
      Aska::MaterialList::EnableIBL(Aska::Light*, bool, Aska::MaterialList::IBLOffsetType)(lVar10,0,0,0);
      *(undefined4 *)(param_1 + 0x6e) = 0;
    }
    uVar4 = *(ushort *)((long)param_1 + 0x37c);
    *(ushort *)((long)param_1 + 0x37c) =
         uVar4 & 0xffe5 | (ushort)((uVar12 << 0x23) >> 0x20) |
         (ushort)((((ulong)uVar4 & 4) << 0x1f) >> 0x20);
    if (iVar7 != 0) {
      uVar12 = Aska::MaterialList::EnableIBL(Aska::Light*, bool, Aska::MaterialList::IBLOffsetType)(lVar10,param_1[0x46],uVar4 >> 2 & 1,uVar12);
      if ((uVar12 & 1) == 0) {
        *puVar1 = *puVar1;
        *(ushort *)((long)param_1 + 0x37c) = *(ushort *)((long)param_1 + 0x37c) & 0xffe5;
      }
      else {
        *(int *)(param_1 + 0x6e) = iVar7;
      }
    }
    *(undefined1 *)(lVar14 + 0x7d) = 1;
    Aska::RenderPassManager::InvalidateRenderState()(lVar14);
  }
  lVar9 = param_1[0x47];
  if ((lVar9 == 0) || ((*(uint3 *)(lVar9 + 0x2a5) & 8) != 0)) {
    iVar7 = 0;
  }
  else {
    iVar7 = Aska::Light::GetIBLTextureUniqueID()(lVar9);
  }
  if (((int)cVar5 != uVar15) || (*(int *)((long)param_1 + 0x374) != iVar7)) {
    if (*(int *)((long)param_1 + 0x374) != 0) {
      Aska::MaterialList::EnableSecondaryIBL(Aska::Light*)(lVar10,0);
      *(undefined4 *)((long)param_1 + 0x374) = 0;
    }
    if ((iVar7 != 0) && (uVar12 = Aska::MaterialList::EnableSecondaryIBL(Aska::Light*)(lVar10,lVar9), (uVar12 & 1) != 0)) {
      *(int *)((long)param_1 + 0x374) = iVar7;
    }
    *(undefined1 *)(lVar14 + 0x7d) = 1;
    Aska::RenderPassManager::InvalidateRenderState()(lVar14);
  }
  if ((int)param_1[0x6e] != 0) {
    lStack_60 = param_1[0x46];
    if (iVar7 == 0) {
      lVar9 = 0;
    }
    lStack_58 = lVar9;
    Aska::AofObject::PrepareIBLContext(Aska::LightManager*, Aska::Light**)(param_1,param_1[0x75],&lStack_60);
  }
code_r0x021c7528:
  if (*(char *)(lVar14 + 0x7d) != '\0') {
    lVar9 = *(long *)(lVar14 + 0x18);
    *(ushort *)(lVar9 + 0x2f) = *(ushort *)(lVar9 + 0x2f) | 1;
    *(undefined1 *)(lVar9 + 0x31) = *(undefined1 *)(lVar9 + 0x31);
    if (*(long *)(lVar9 + 0x40) != 0) {
      bVar6 = false;
      lVar8 = *(long *)(lVar9 + 0x40);
code_r0x021c7558:
      do {
        do {
          lVar13 = lVar8;
          if (!bVar6) {
            bVar6 = false;
            *(ushort *)(lVar13 + 0x2f) = *(ushort *)(lVar13 + 0x2f) | 1;
            lVar8 = *(long *)(lVar13 + 0x40);
            if (*(long *)(lVar13 + 0x40) != 0) goto code_r0x021c7558;
          }
          bVar6 = false;
          lVar8 = *(long *)(lVar13 + 0x48);
        } while (*(long *)(lVar13 + 0x48) != 0);
        bVar6 = true;
        lVar8 = *(long *)(lVar13 + 0x38);
      } while (*(long *)(lVar13 + 0x38) != lVar9);
    }
    Aska::RenderPassManager::InvalidateShaders(bool)(lVar14,1);
    Aska::RenderPassManager::InvalidateCommandBufferManager()(lVar14);
    *(undefined1 *)(lVar14 + 0x7d) = 0;
  }
  uVar4 = *(ushort *)(lVar16 + 0x108);
  if ((uVar4 >> 3 & 1) != 0) {
    Aska::MaterialList::ServeShaderConstantBody()(lVar10);
    uVar4 = *(ushort *)(lVar16 + 0x108);
  }
  if ((uVar4 >> 2 & 1) != 0) {
    Aska::MaterialList::UpdateMaterialContext()(lVar10);
  }
  if ((((*puVar1 >> 0x12 & 1) != 0) &&
      (uVar12 = Aska::Event::IsSignal() const(*(long *)PTR__ZN4Aska6Global18m_pModifierManagerE_02cbb990 + 0x58),
      (uVar12 & 1) != 0)) && ((int)param_1[0x77] != *(int *)((long)param_1 + 0x3b4))) {
    lVar10 = *(long *)(param_1[0x7b] + 0xd0);
    if ((lVar10 != 0) &&
       (uVar12 = (ulong)*(ushort *)(*(long *)(param_1[0x7b] + 0xb0) + 0x70), uVar12 != 0)) {
      lVar14 = 0;
      while( true ) {
        plVar11 = *(long **)(lVar10 + lVar14 * 8);
        if (*(short *)(*plVar11 + 0x1c) == 0) {
          Aska::RenderablePrimitive::FlipKick()(plVar11 + 8);
        }
        if (uVar12 - 1 == lVar14) break;
        lVar14 = lVar14 + 1;
        lVar10 = *(long *)(param_1[0x7b] + 0xd0);
      }
    }
    *(undefined4 *)(param_1 + 0x77) = *(undefined4 *)((long)param_1 + 0x3b4);
  }
  return 1;
}

// ==== Aska::AofObject::PrepareForRendering(Aska::RENDERINFO const*)
// vaddr 0x20c768c | ghidra 0x21c768c | size 2224 | symbol _ZN4Aska9AofObject19PrepareForRenderingEPKNS_10RENDERINFOE | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska9AofObject19PrepareForRenderingEPKNS_10RENDERINFOE(long param_1,short *param_2)

{
  uint6 *puVar1;
  uint uVar2;
  uint uVar3;
  char cVar4;
  byte bVar5;
  byte bVar6;
  ushort uVar7;
  short sVar8;
  uint6 uVar9;
  uint3 uVar10;
  bool bVar11;
  undefined1 uVar12;
  ulong uVar13;
  long lVar14;
  uint uVar15;
  long lVar16;
  long lVar17;
  long lVar18;
  int iVar19;
  
  lVar16 = *(long *)(param_1 + 0x398);
  puVar1 = (uint6 *)(param_1 + 0x378);
  *(short *)(param_1 + 0x6a8) = *param_2;
  if ((*(ushort *)(param_1 + 0x37c) & 0x20) == 0) {
    if (((*(uint *)(param_1 + 0x378) >> 4 & 1) != 0) && ((*(byte *)(param_1 + 0x1b5) >> 1 & 1) == 0)
       ) {
      return 0;
    }
  }
  else {
    *(uint *)puVar1 = *(uint *)(param_1 + 0x378);
    *(ushort *)(param_1 + 0x37c) = *(ushort *)(param_1 + 0x37c) & 0xffdf;
    uVar13 = Aska::AofObject::PrepareForRendering_Preliminary()(param_1);
    if ((uVar13 & 1) == 0) {
      return 0;
    }
  }
  lVar14 = Aska::AofObject::GetObjectRenderState(unsigned int)(param_1,*(byte *)((long)param_2 + 3) & 7);
  bVar6 = *(byte *)((long)param_2 + 3) & 7;
  if (5 < bVar6) {
    return 0;
  }
  lVar17 = *(long *)(lVar16 + 0x18);
  switch(*(byte *)((long)param_2 + 3) & 7) {
  case 0:
    lVar16 = Aska::AofObject::GetColorPass(Aska::RENDERINFO const*)(param_1,param_2);
    if (lVar16 == 0) {
      return 0;
    }
    lVar17 = *(long *)(param_1 + 0x3d8);
    if ((*(byte *)(lVar17 + 0x109) >> 2 & 1) != 0) {
      Aska::AofObject::PrepareObjectScreenUVMatrix(Aska::Camera*, Aska::RenderPass*)(param_1,*(undefined8 *)(param_2 + 8),lVar16);
    }
    if ((*(ushort *)(lVar16 + 0x2f) >> 0xe & 1) != 0) {
      Aska::RenderPass::UpdateFrameTexturePointers(Aska::MaterialList*, Aska::RENDERINFO const*, int)(lVar16,lVar17 + 0xe8,param_2,*(undefined1 *)(param_1 + 0x1b7));
    }
    uVar15 = (uint)*(char *)(param_1 + 0x37f);
    if (*(char *)(param_1 + 0x37f) == -1) {
      uVar15 = *(byte *)((long)param_2 + 3) >> 3 & 3;
    }
    bVar5 = *(byte *)(lVar16 + 0x2b);
    *(char *)(lVar16 + 0x2b) = (char)uVar15;
    if (uVar15 != bVar5) {
      *(undefined1 *)(lVar14 + 0x1a) = 0;
    }
    uVar15 = *(uint *)puVar1;
    cVar4 = *(char *)(param_1 + 900);
    if (((*(uint3 *)(lVar16 + 0x2f) >> 0x13 & 1) != (uVar15 >> 0xd & 1)) ||
       (*(char *)(lVar16 + 0x1c0) != cVar4)) {
      uVar2 = *(uint3 *)(lVar16 + 0x2f) & 0xf7ffff;
      *(short *)(lVar16 + 0x2f) = (short)uVar2;
      *(byte *)(lVar16 + 0x31) = (byte)(uVar2 >> 0x10) | (byte)(((uVar15 & 0x2000) << 6) >> 0x10);
      *(char *)(lVar16 + 0x1c0) = cVar4;
      Aska::RenderPass::InvalidateShaders()(lVar16);
    }
    if ((*(char *)(lVar14 + 0x1a) == '\0') &&
       (uVar13 = bool Aska::AofObject::MakeObjectRenderState<3055u>(Aska::AofObjectRenderState*, Aska::RenderPass*)(param_1,lVar14,lVar16), (uVar13 & 1) == 0)) {
      return 0;
    }
    if ((*(ushort *)(lVar16 + 0x2f) >> 6 & 1) == 0) {
      uVar13 = Aska::RenderPass::PrepareRenderState(Aska::MaterialList*, bool)(lVar16,*(long *)(param_1 + 0x3d8) + 0xe8,
                               (*(ushort *)(*(long *)(param_2 + 8) + 0xeb3) & 0x600) == 0x200);
joined_r0x021c7aec:
      if ((uVar13 & 1) == 0) {
        return 0;
      }
    }
    goto code_r0x021c7af0;
  case 1:
    lVar18 = *(long *)(param_1 + 0x3d8);
    uVar7 = *(ushort *)(lVar18 + 0x108);
    if (((uVar7 >> 8 & 1) == 0) && ((char)param_2[2] == '\0')) {
      bVar11 = false;
    }
    else if ((*(ushort *)(lVar17 + 0x2f) >> 5 & 1) == 0) {
      *(uint *)(lVar17 + 0x20) = *(ushort *)(param_1 + 0x390) & 0x4001;
      bVar11 = true;
      uVar13 = Aska::AofHandler::InitializeShader(Aska::RenderPass*, int, bool, bool)(*(undefined8 *)(param_1 + 0x3d8),lVar17,0xffffffff,0,1);
      if ((uVar13 & 1) == 0) {
        return 0;
      }
    }
    else {
      bVar11 = true;
    }
    lVar18 = lVar18 + 0xe8;
    lVar16 = Aska::RenderPassManager::GetZprePass(Aska::RenderPass*, Aska::MaterialList*, int, Aska::RENDERINFO::Zprepass)(lVar16,lVar17,lVar18,(long)*param_2,(char)param_2[2]);
    if (lVar16 == 0) {
      return 0;
    }
    if (*(char *)(lVar14 + 0x1a) == '\0') {
      if ((uVar7 >> 8 & 1) == 0) {
        uVar13 = bool Aska::AofObject::MakeObjectRenderState<497u>(Aska::AofObjectRenderState*, Aska::RenderPass*)(param_1,lVar14,lVar16);
      }
      else {
        uVar13 = bool Aska::AofObject::MakeObjectRenderState<1015u>(Aska::AofObjectRenderState*, Aska::RenderPass*)(param_1,lVar14,lVar16);
      }
      if ((uVar13 & 1) == 0) {
        return 0;
      }
    }
    if (bVar11) {
code_r0x021c7be8:
      Aska::RenderPass::UpdateTextureShadowPass(Aska::MaterialList*, Aska::TextureModifierManager*, Aska::RENDERINFO const*, int)(lVar16,lVar18,param_1 + 0x410,param_2,*(undefined1 *)(param_1 + 0x1b7));
    }
    else {
      bVar5 = *(byte *)(lVar16 + 0x31);
      *(undefined2 *)(lVar16 + 0x2f) = *(undefined2 *)(lVar16 + 0x2f);
      *(byte *)(lVar16 + 0x31) = bVar5 & 0xfb;
      if ((bVar5 >> 2 & 1) != 0) goto code_r0x021c7be8;
    }
    if ((*(ushort *)(lVar17 + 0x2f) >> 6 & 1) == 0) {
      uVar7 = *(ushort *)(*(long *)(param_2 + 8) + 0xeb3);
      lVar18 = *(long *)(param_1 + 0x3d8) + 0xe8;
code_r0x021c7ca0:
      uVar13 = Aska::RenderPass::PrepareRenderState(Aska::MaterialList*, bool)(lVar17,lVar18,(uVar7 & 0x600) == 0x200);
joined_r0x021c7b68:
      if ((uVar13 & 1) == 0) {
        return 0;
      }
    }
    break;
  case 2:
    lVar18 = *(long *)(param_1 + 0x3d8);
    uVar7 = *(ushort *)(lVar18 + 0x108);
    if (((uVar7 >> 7 & 1) != 0) && ((*(ushort *)(lVar17 + 0x2f) >> 5 & 1) == 0)) {
      *(uint *)(lVar17 + 0x20) = *(ushort *)(param_1 + 0x390) & 0x4001;
      uVar13 = Aska::AofHandler::InitializeShader(Aska::RenderPass*, int, bool, bool)(*(undefined8 *)(param_1 + 0x3d8),lVar17,0xffffffff,0,1);
      if ((uVar13 & 1) == 0) {
        return 0;
      }
    }
    lVar18 = lVar18 + 0xe8;
    lVar16 = Aska::RenderPassManager::GetShadowCastPass(Aska::RenderPass*, Aska::MaterialList*, unsigned char, int)(lVar16,lVar17,lVar18,(char)param_2[2],(long)*param_2);
    if (lVar16 == 0) {
      return 0;
    }
    if ((uVar7 >> 7 & 1) == 0) {
      bVar5 = *(byte *)(lVar16 + 0x31);
      *(undefined2 *)(lVar16 + 0x2f) = *(undefined2 *)(lVar16 + 0x2f);
      *(byte *)(lVar16 + 0x31) = bVar5 & 0xfb;
      if ((bVar5 >> 2 & 1) != 0) {
        Aska::RenderPass::ClearTexture()(lVar16);
      }
      cVar4 = *(char *)(lVar14 + 0x1a);
    }
    else {
      Aska::RenderPass::UpdateTextureShadowPass(Aska::MaterialList*, Aska::TextureModifierManager*, Aska::RENDERINFO const*, int)(lVar16,lVar18,param_1 + 0x410,param_2,*(undefined1 *)(param_1 + 0x1b7));
      cVar4 = *(char *)(lVar14 + 0x1a);
    }
    if (cVar4 == '\0') {
      if ((uVar7 >> 7 & 1) == 0) {
        uVar13 = bool Aska::AofObject::MakeObjectRenderState<496u>(Aska::AofObjectRenderState*, Aska::RenderPass*)(param_1,lVar14,lVar16);
      }
      else {
        uVar13 = bool Aska::AofObject::MakeObjectRenderState<1010u>(Aska::AofObjectRenderState*, Aska::RenderPass*)(param_1,lVar14,lVar16);
      }
      if ((uVar13 & 1) == 0) {
        return 0;
      }
    }
    if ((*(ushort *)(lVar16 + 0x2f) >> 6 & 1) == 0) {
      uVar13 = Aska::RenderPass::PrepareShadowCastState(Aska::AofHandler*, unsigned char)(lVar16,*(undefined8 *)(param_1 + 0x3d8),(char)param_2[2]);
      goto joined_r0x021c7b68;
    }
    break;
  case 3:
    lVar16 = Aska::RenderPassManager::GetVertexPass(Aska::RenderPass*)(lVar16,lVar17);
    if (lVar16 == 0) {
      return 0;
    }
    if ((*(ushort *)(lVar16 + 0x2f) >> 5 & 1) != 0) {
      uVar12 = Aska::RenderPass::GetVertexPassNum() const(lVar16);
      *(undefined1 *)(param_1 + 0x38f) = uVar12;
    }
    break;
  case 4:
    if ((*(ushort *)(lVar17 + 0x2f) >> 5 & 1) == 0) {
      *(uint *)(lVar17 + 0x20) = *(ushort *)(param_1 + 0x390) & 0x4001;
      uVar13 = Aska::AofHandler::InitializeShader(Aska::RenderPass*, int, bool, bool)(*(undefined8 *)(param_1 + 0x3d8),lVar17,0xffffffff,0,1);
      if ((uVar13 & 1) == 0) {
        return 0;
      }
    }
    uVar9 = *puVar1;
    lVar18 = *(long *)(param_1 + 0x3d8) + 0xe8;
    lVar16 = Aska::RenderPassManager::GetObjectMotionBlurPass(Aska::RenderPass*, Aska::MaterialList*, bool)(lVar16,lVar17,lVar18,(ulong)(uVar9 >> 0x13) & 1);
    if (lVar16 == 0) {
      return 0;
    }
    uVar15 = (uint)uVar9;
    if (*(char *)(lVar14 + 0x1a) == '\0') {
      if ((uVar15 >> 0x13 & 1) != 0) {
        uVar13 = bool Aska::AofObject::MakeObjectRenderState<2027u>(Aska::AofObjectRenderState*, Aska::RenderPass*)(param_1,lVar14,lVar16);
        if ((uVar13 & 1) == 0) {
          return 0;
        }
        goto code_r0x021c7c60;
      }
      uVar13 = bool Aska::AofObject::MakeObjectRenderState<1514u>(Aska::AofObjectRenderState*, Aska::RenderPass*)(param_1,lVar14,lVar16);
      if ((uVar13 & 1) == 0) {
        return 0;
      }
    }
    else if ((uVar15 >> 0x13 & 1) != 0) {
code_r0x021c7c60:
      Aska::RenderPass::UpdateTexture(Aska::MaterialList*, Aska::TextureModifierManager*, Aska::RENDERINFO const*, int, bool)(lVar16,lVar18,param_1 + 0x410,param_2,*(undefined1 *)(param_1 + 0x1b7),1);
    }
    if ((*(ushort *)(lVar17 + 0x2f) >> 6 & 1) == 0) {
      uVar7 = *(ushort *)(*(long *)(param_2 + 8) + 0xeb3);
      goto code_r0x021c7ca0;
    }
    break;
  case 5:
    uVar2 = *(uint *)(param_1 + 0x228);
    uVar3 = *(uint *)(*(long *)PTR__ZN4Aska6Global16m_pObjectManagerE_02cc4688 + 0x45d0);
    *(uint *)(param_1 + 0x228) = uVar2 + 1;
    uVar15 = *(uint *)(param_1 + 0x22c);
    if (uVar3 <= *(uint *)(param_1 + 0x22c)) {
      uVar15 = uVar3;
    }
    if (*(long *)(param_1 + 0x690) == 0) {
      return 0;
    }
    uVar3 = 0;
    if (uVar15 != 0) {
      uVar3 = uVar2 / uVar15;
    }
    iVar19 = uVar2 - uVar3 * uVar15;
    lVar16 = Aska::AofObject::GetMultiDrawPass(unsigned int, Aska::RENDERINFO const*)(param_1,iVar19,param_2);
    if (lVar16 == 0) {
      return 0;
    }
    if ((*(ushort *)(lVar16 + 0x2f) >> 0xe & 1) != 0) {
      Aska::RenderPass::UpdateFrameTexturePointers(Aska::MaterialList*, Aska::RENDERINFO const*, int)(lVar16,*(long *)(param_1 + 0x3d8) + 0xe8,param_2,
                      (long)*(char *)((long)param_2 + 5));
    }
    if ((*(char *)(lVar14 + 0x1a) == '\0') &&
       (uVar13 = bool Aska::AofObject::MakeObjectRenderState<2543u>(Aska::AofObjectRenderState*, Aska::RenderPass*)(param_1,lVar14,lVar16), (uVar13 & 1) == 0)) {
      return 0;
    }
    if ((*(ushort *)(lVar16 + 0x2f) >> 6 & 1) == 0) {
      uVar13 = Aska::AofObject::MakePassRenderStateMultiDraw(unsigned int, Aska::RenderPass*)(param_1,iVar19,lVar16);
      if ((uVar13 & 1) == 0) {
        return 0;
      }
      uVar13 = Aska::RenderPass::PrepareMultiDrawState(Aska::AofHandler*)(lVar16,*(undefined8 *)(param_1 + 0x3d8));
      goto joined_r0x021c7aec;
    }
code_r0x021c7af0:
    uVar13 = Aska::AofObject::PrepareColorShader(Aska::RenderPass*, Aska::RENDERINFO const*)(param_1,lVar16,param_2);
    if ((uVar13 & 1) == 0) {
      return 0;
    }
    goto code_r0x021c7cf8;
  }
  if ((*(ushort *)(lVar16 + 0x2f) >> 5 & 1) == 0) {
    *(uint *)(lVar16 + 0x20) = *(ushort *)(param_1 + 0x390) & 0x4001;
    uVar13 = Aska::AofHandler::InitializeShader(Aska::RenderPass*, int, bool, bool)(*(undefined8 *)(param_1 + 0x3d8),lVar16,0xffffffff,0,0);
    if ((uVar13 & 1) == 0) {
      return 0;
    }
  }
code_r0x021c7cf8:
  uVar10 = *(uint3 *)(lVar16 + 0x2f);
  if ((uVar10 & 0x80) == 0) {
    Aska::RenderPass::SetObjectState(Aska::AofObjectRenderState*)(lVar16,lVar14);
    uVar10 = *(uint3 *)(lVar16 + 0x2f);
  }
  if ((uVar10 & 3) != 0) {
    *(ushort *)(lVar16 + 0x2f) = (ushort)uVar10 & 0xdfff;
    *(char *)(lVar16 + 0x31) = (char)(uVar10 >> 0x10);
    Aska::RenderPass::UpdatePacket()(lVar16);
    if ((*(ushort *)(lVar16 + 0x2f) >> 0xd & 1) != 0) {
      return 0;
    }
  }
  sVar8 = param_2[3];
  if (0 < sVar8) {
    lVar14 = *(long *)(param_2 + 4);
    uVar15 = *(uint *)(param_1 + 0x1b0);
    bVar5 = (bVar6 == 1) << 3;
    if (bVar6 == 3) {
      iVar19 = 0;
      do {
        uVar13 = (**(code **)(**(long **)(param_1 + 0x3d8) + 0x38))
                           (*(long **)(param_1 + 0x3d8),lVar14,param_1,param_2,lVar16,0);
        if ((uVar13 & 1) == 0) {
          return 0;
        }
        bVar6 = *(byte *)(lVar14 + 10);
        iVar19 = iVar19 + 1;
        *(byte *)(lVar14 + 10) = bVar6 & 0xf7;
        uVar2 = *(uint *)(lVar14 + 0x58) | 4;
        if ((uVar15 & 0x100) == 0) {
          uVar2 = *(uint *)(lVar14 + 0x58) & 0xfffffffb;
        }
        *(byte *)(lVar14 + 10) =
             bVar6 & 0xe0 |
             bVar6 & 7 | (*(char *)(param_1 + 0x38f) == *(char *)(param_1 + 0x38e)) << 4;
        *(uint *)(lVar14 + 0x58) = uVar2;
        lVar14 = lVar14 + 0x230;
      } while (iVar19 < sVar8);
    }
    else if ((uVar15 >> 8 & 1) == 0) {
      iVar19 = 0;
      do {
        uVar13 = (**(code **)(**(long **)(param_1 + 0x3d8) + 0x38))
                           (*(long **)(param_1 + 0x3d8),lVar14,param_1,param_2,lVar16,0);
        if ((uVar13 & 1) == 0) {
          return 0;
        }
        iVar19 = iVar19 + 1;
        *(uint *)(lVar14 + 0x58) = *(uint *)(lVar14 + 0x58) & 0xfffffffb;
        *(byte *)(lVar14 + 10) = *(byte *)(lVar14 + 10) & 0xe7 | bVar5;
        lVar14 = lVar14 + 0x230;
      } while (iVar19 < sVar8);
    }
    else {
      iVar19 = 0;
      do {
        uVar13 = (**(code **)(**(long **)(param_1 + 0x3d8) + 0x38))
                           (*(long **)(param_1 + 0x3d8),lVar14,param_1,param_2,lVar16,0);
        if ((uVar13 & 1) == 0) {
          return 0;
        }
        iVar19 = iVar19 + 1;
        *(uint *)(lVar14 + 0x58) = *(uint *)(lVar14 + 0x58) | 4;
        *(byte *)(lVar14 + 10) = *(byte *)(lVar14 + 10) & 0xe7 | bVar5;
        lVar14 = lVar14 + 0x230;
      } while (iVar19 < sVar8);
    }
  }
  return 1;
}

// ==== Aska::AofObject::GetObjectRenderState(unsigned int)
// vaddr 0x20c7f3c | ghidra 0x21c7f3c | size 356 | symbol _ZN4Aska9AofObject20GetObjectRenderStateEj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska9AofObject20GetObjectRenderStateEj(long param_1,uint param_2)

{
  undefined8 *puVar1;
  ushort uVar2;
  long lVar3;
  long lVar4;
  long lVar5;
  long lVar6;
  ulong uVar7;
  
  uVar2 = *(ushort *)(param_1 + 0x462);
  uVar7 = (ulong)uVar2;
  if (uVar2 != 0) {
    lVar3 = *(long *)(param_1 + 0x458);
    if (lVar3 == 0) {
      lVar5 = 0;
      lVar3 = param_1 + 0x470;
      do {
        if (*(ushort *)(lVar3 + 0x18) == param_2) {
          return;
        }
        lVar5 = lVar5 + 1;
        lVar3 = lVar3 + 0x20;
      } while (lVar5 < (long)uVar7);
    }
    else {
      lVar5 = 0;
      do {
        if (*(ushort *)(lVar3 + 0x18) == param_2) {
          return;
        }
        lVar5 = lVar5 + 1;
        lVar3 = lVar3 + 0x20;
      } while (lVar5 < (long)uVar7);
    }
  }
  lVar3 = uVar7 + 1;
  if (uVar2 < *(ushort *)(param_1 + 0x460)) {
    lVar5 = *(long *)(param_1 + 0x458);
  }
  else {
    lVar6 = *(long *)(param_1 + 0x458);
    lVar5 = *(long *)(param_1 + 0x468);
    lVar4 = lVar3 * 0x40;
    if (lVar6 == 0) {
      if (lVar5 == 0) {
        lVar5 = operator new[](unsigned long, std::nothrow_t const&)(lVar4,PTR__ZSt7nothrow_02cb9a80);
      }
      else {
        lVar5 = Aska::MemoryManager::Malloc(unsigned long)();
      }
      if (lVar5 != 0) {
        memcpy(lVar5,param_1 + 0x470,(ulong)*(ushort *)(param_1 + 0x462) << 5);
      }
    }
    else if (lVar5 == 0) {
      lVar5 = operator new[](unsigned long, void*, unsigned long)(lVar4,lVar6,4);
    }
    else {
      lVar5 = Aska::MemoryManager::Realloc(unsigned long, void*, long)(lVar5,lVar4,lVar6,4);
    }
    if (lVar5 == 0) {
      lVar5 = *(long *)(param_1 + 0x458);
      uVar7 = (ulong)*(ushort *)(param_1 + 0x462) - 1;
      goto code_r0x021c8060;
    }
    *(long *)(param_1 + 0x458) = lVar5;
    *(short *)(param_1 + 0x460) = (short)((int)lVar3 << 1);
  }
  *(short *)(param_1 + 0x462) = (short)lVar3;
code_r0x021c8060:
  puVar1 = (undefined8 *)(param_1 + uVar7 * 0x20 + 0x470);
  if (lVar5 != 0) {
    puVar1 = (undefined8 *)(lVar5 + uVar7 * 0x20);
  }
  puVar1[1] = 0;
  *puVar1 = 0;
  puVar1[3] = 0;
  puVar1[2] = 0;
  *(short *)(puVar1 + 3) = (short)param_2;
  return;
}

// ==== Aska::AofObject::PrepareObjectScreenUVMatrix(Aska::Camera*, Aska::RenderPass*)
// vaddr 0x20c80a0 | ghidra 0x21c80a0 | size 856 | symbol _ZN4Aska9AofObject27PrepareObjectScreenUVMatrixEPNS_6CameraEPNS_10RenderPassE | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska9AofObject27PrepareObjectScreenUVMatrixEPNS_6CameraEPNS_10RenderPassE
               (long *param_1,long param_2,long param_3)

{
  bool bVar1;
  ulong uVar2;
  ulong uVar3;
  long lVar4;
  uint uVar5;
  long lVar6;
  ulong uVar7;
  long lVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  float fStack_90;
  float fStack_8c;
  float fStack_88;
  float fStack_80;
  float fStack_7c;
  float fStack_78;
  float fStack_70;
  float fStack_6c;
  float fStack_68;
  float fStack_60;
  float fStack_5c;
  float fStack_58;
  float fStack_54;
  
  if ((*(byte *)(param_1 + 0x25) >> 4 & 1) == 0) {
    (**(code **)(*param_1 + 600))(param_1,1);
  }
  fStack_60 = *(float *)(param_1 + 0x5a);
  fStack_5c = *(float *)((long)param_1 + 0x2d4);
  fStack_58 = *(float *)(param_1 + 0x5b);
  fVar13 = *(float *)((long)param_1 + 0x2dc);
  fStack_54 = 1.0;
  Aska::Vector::ApplyMatrix(Aska::Matrix const*)(&fStack_60,param_2 + 0xa20);
  uVar5 = (uint)(*(float *)(param_2 + 0x1f0) * _UNK_027ebdf4);
  fVar9 = (1.0 / fStack_54) * 0.5;
  fVar11 = *(float *)(param_2 + 0x1f0) + (float)(int)uVar5 * _UNK_027edb30;
  bVar1 = (uVar5 & 1) != 0;
  fVar14 = fVar11;
  if (bVar1) {
    fVar14 = -fVar11;
  }
  fVar11 = fVar11 * fVar11;
  fVar12 = fVar11 * (fVar11 * (fVar11 * (fVar11 * (fVar11 * (fVar11 * (fVar11 * _UNK_02964910 +
                                                                      _UNK_02964914) + _UNK_02964918
                                                            ) + _UNK_0296491c) + _UNK_02964920) +
                              _UNK_02964924) + -0.5);
  fVar15 = -0.5 - fVar9 * fStack_60;
  fVar10 = fVar9 * fStack_5c + -0.5;
  fStack_6c = 1.0 / *(float *)(param_2 + 0xdf0);
  fStack_90 = 1.0 / ((*(float *)(param_2 + 0xdfc) /
                     (*(float *)(param_2 + 0x98c) /
                     (fStack_58 / fStack_54 - *(float *)(param_2 + 0x988)))) * fVar13);
  fVar9 = fVar11 * (fVar11 * (fVar11 * (fVar11 * (fVar11 * (fVar11 * (fVar11 * _UNK_02964928 +
                                                                     _UNK_0296492c) + _UNK_02964930)
                                                 + _UNK_02964934) + _UNK_02964938) + _UNK_0296493c)
                   + _UNK_02964940) + 1.0;
  fStack_8c = fStack_90 / *(float *)(param_2 + 0xdf0);
  fStack_80 = -1.0 - fVar12;
  if (!bVar1) {
    fStack_80 = fVar12 + 1.0;
  }
  fStack_70 = fVar14 * fVar9;
  fStack_7c = -(fVar14 * fVar9);
  fStack_a0 = fStack_90 * fStack_80;
  fStack_9c = fStack_8c * fStack_7c;
  fStack_90 = fStack_90 * fStack_70;
  fStack_8c = fStack_8c * fStack_80;
  fStack_7c = fStack_6c * fStack_7c;
  fStack_6c = fStack_6c * fStack_80;
  fStack_98 = fVar15 * fStack_a0 + fVar10 * fStack_9c + 0.5;
  fStack_88 = fVar15 * fStack_90 + fVar10 * fStack_8c + 0.5;
  fStack_78 = fVar15 * fStack_80 + fVar10 * fStack_7c + 0.5;
  fStack_68 = fVar15 * fStack_70 + fVar10 * fStack_6c + 0.5;
  if ((*(long *)(param_1[0x7b] + 0xd0) != 0) &&
     (uVar7 = (ulong)*(ushort *)(*(long *)(param_1[0x7b] + 0xb0) + 0x70), uVar7 != 0)) {
    lVar8 = 0;
    do {
      lVar6 = *(long *)(param_3 + 8) + lVar8 * 0x1b8;
      uVar2 = Aska::ShaderConstantManager::SetShaderConstantFUC(int, int, Aska::Vector const*, int)(lVar6,0x55,0,&fStack_a0,2);
      uVar3 = Aska::ShaderConstantManager::SetShaderConstantFUC(int, int, Aska::Vector const*, int)(lVar6,0x56,0,&fStack_80,2);
      if (((uVar2 & 1) != 0) || ((uVar3 & 1) != 0)) {
        *(ushort *)(param_3 + 0x2f) = *(ushort *)(param_3 + 0x2f) | 1;
        if (*(long *)(param_3 + 0x40) != 0) {
          bVar1 = false;
          lVar6 = *(long *)(param_3 + 0x40);
code_r0x021c8390:
          do {
            do {
              lVar4 = lVar6;
              if (!bVar1) {
                bVar1 = false;
                *(ushort *)(lVar4 + 0x2f) = *(ushort *)(lVar4 + 0x2f) | 1;
                lVar6 = *(long *)(lVar4 + 0x40);
                if (*(long *)(lVar4 + 0x40) != 0) goto code_r0x021c8390;
              }
              bVar1 = false;
              lVar6 = *(long *)(lVar4 + 0x48);
            } while (*(long *)(lVar4 + 0x48) != 0);
            bVar1 = true;
            lVar6 = *(long *)(lVar4 + 0x38);
          } while (*(long *)(lVar4 + 0x38) != param_3);
        }
      }
      lVar8 = lVar8 + 1;
    } while (lVar8 < (long)uVar7);
  }
  return;
}

// ==== Aska::AofObject::PrepareColorShader(Aska::RenderPass*, Aska::RENDERINFO const*)
// vaddr 0x20c83f8 | ghidra 0x21c83f8 | size 268 | symbol _ZN4Aska9AofObject18PrepareColorShaderEPNS_10RenderPassEPKNS_10RENDERINFOE | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska9AofObject18PrepareColorShaderEPNS_10RenderPassEPKNS_10RENDERINFOE
          (long param_1,long param_2,long param_3)

{
  uint uVar1;
  ushort uVar2;
  uint uVar3;
  ulong uVar4;
  long lVar5;
  uint uVar6;
  
  uVar1 = (uint)(byte)*PTR__ZN4Aska13ObjectManager20m_LightConfigurationE_02cbf638;
  if ((int)*(char *)(param_1 + 0x381) != 0xffffffff) {
    uVar1 = (int)*(char *)(param_1 + 0x381);
  }
  if (uVar1 == 0) {
    uVar2 = *(ushort *)(param_2 + 0x2f);
    uVar3 = *(ushort *)(param_1 + 0x390) & 0xf7ff;
    lVar5 = *(long *)(param_3 + 0x10);
  }
  else {
    uVar2 = *(ushort *)(param_2 + 0x2f);
    uVar3 = (uVar2 & 0x400) >> 7 ^ 0x808 | (uint)*(ushort *)(param_1 + 0x390);
    lVar5 = *(long *)(param_3 + 0x10);
  }
  uVar6 = uVar3;
  if (((uVar2 >> 10 & 1) != 0) && (uVar6 = uVar3 | 0x100, *(char *)(lVar5 + 0xeb2) != '\x02')) {
    uVar6 = uVar3;
  }
  uVar6 = uVar6 | (*(ushort *)(lVar5 + 0xeb3) & 1) << 0x10;
  if ((uVar6 != *(uint *)(param_2 + 0x20)) || (uVar1 != *(byte *)(param_2 + 0x2d))) {
    *(char *)(param_2 + 0x2d) = (char)uVar1;
    Aska::RenderPass::InvalidateShaders()(param_2);
  }
  if ((*(ushort *)(param_2 + 0x2f) >> 5 & 1) == 0) {
    *(uint *)(param_2 + 0x20) = uVar6;
    uVar4 = Aska::AofHandler::InitializeShader(Aska::RenderPass*, int, bool, bool)(*(undefined8 *)(param_1 + 0x3d8),param_2,0xffffffff,1,0);
    if ((uVar4 & 1) == 0) {
      return 0;
    }
  }
  return 1;
}

// ==== Aska::AofObject::PrepareShader(Aska::RenderPass*, Aska::RENDERINFO const*, bool)
// vaddr 0x20c8504 | ghidra 0x21c8504 | size 84 | symbol _ZN4Aska9AofObject13PrepareShaderEPNS_10RenderPassEPKNS_10RENDERINFOEb | lib libSOA-3.7.0.so | 2026-10-04
uint _ZN4Aska9AofObject13PrepareShaderEPNS_10RenderPassEPKNS_10RENDERINFOEb
               (long param_1,long param_2,undefined8 param_3,uint param_4)

{
  uint uVar1;
  
  if ((*(ushort *)(param_2 + 0x2f) >> 5 & 1) == 0) {
    *(uint *)(param_2 + 0x20) = *(ushort *)(param_1 + 0x390) & 0x4001;
    uVar1 = Aska::AofHandler::InitializeShader(Aska::RenderPass*, int, bool, bool)(*(undefined8 *)(param_1 + 0x3d8),param_2,0xffffffff,0,param_4 & 1);
    if (((uVar1 & 1) == 0) || ((param_4 & 1) != 0)) goto code_r0x021c854c;
  }
  uVar1 = 1;
code_r0x021c854c:
  return uVar1 & 1;
}

// ==== Aska::AofObject::GetActualLightConfiguration() const
// vaddr 0x20c8558 | ghidra 0x21c8558 | size 28 | symbol _ZNK4Aska9AofObject27GetActualLightConfigurationEv | lib libSOA-3.7.0.so | 2026-10-04
uint _ZNK4Aska9AofObject27GetActualLightConfigurationEv(long param_1)

{
  uint uVar1;
  
  uVar1 = (uint)(byte)*PTR__ZN4Aska13ObjectManager20m_LightConfigurationE_02cbf638;
  if ((int)*(char *)(param_1 + 0x381) != 0xffffffff) {
    uVar1 = (int)*(char *)(param_1 + 0x381);
  }
  return uVar1;
}

// ==== Aska::AofObject::Render(Aska::RenderContext*, int)
// vaddr 0x20c8574 | ghidra 0x21c8574 | size 56 | symbol _ZN4Aska9AofObject6RenderEPNS_13RenderContextEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska9AofObject6RenderEPNS_13RenderContextEi(undefined8 param_1,long param_2,int param_3)

{
  if (0 < param_3) {
    do {
      Aska::RenderContext::OnPaint()(param_2);
      param_3 = param_3 + -1;
      param_2 = param_2 + 0x230;
    } while (param_3 != 0);
  }
  return;
}

// ==== Aska::AofObject::RenderProfileBegin(Aska::RenderContext*)
// vaddr 0x20c85ac | ghidra 0x21c85ac | size 4 | symbol _ZN4Aska9AofObject18RenderProfileBeginEPNS_13RenderContextE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska9AofObject18RenderProfileBeginEPNS_13RenderContextE(void)

{
  return;
}

// ==== Aska::AofObject::RenderContextValidation(Aska::RenderContext*)
// vaddr 0x20c85b0 | ghidra 0x21c85b0 | size 4 | symbol _ZN4Aska9AofObject23RenderContextValidationEPNS_13RenderContextE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska9AofObject23RenderContextValidationEPNS_13RenderContextE(void)

{
  return;
}

// ==== Aska::AofObject::RenderProfileEnd()
// vaddr 0x20c85b4 | ghidra 0x21c85b4 | size 4 | symbol _ZN4Aska9AofObject16RenderProfileEndEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska9AofObject16RenderProfileEndEv(void)

{
  return;
}

// ==== Aska::AofObject::SetPerPixelLightCount(int)
// vaddr 0x20c85b8 | ghidra 0x21c85b8 | size 40 | symbol _ZN4Aska9AofObject21SetPerPixelLightCountEi | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska9AofObject21SetPerPixelLightCountEi(long param_1)

{
  if (*(long *)(param_1 + 0x3d8) != 0) {
    Aska::MaterialList::SetPerPixelLightCount(int)(*(long *)(param_1 + 0x3d8) + 0xe8);
    return 1;
  }
  return 0;
}

// ==== Aska::AofObject::EnableBoundingObjectDebug(bool)
// vaddr 0x20c85e0 | ghidra 0x21c85e0 | size 4 | symbol _ZN4Aska9AofObject25EnableBoundingObjectDebugEb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska9AofObject25EnableBoundingObjectDebugEb(void)

{
  return;
}

// ==== Aska::AofObject::SetNormalDebug(int)
// vaddr 0x20c85e4 | ghidra 0x21c85e4 | size 4 | symbol _ZN4Aska9AofObject14SetNormalDebugEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska9AofObject14SetNormalDebugEi(void)

{
  return;
}

// ==== Aska::AofObject::SetBinormalDebug(int)
// vaddr 0x20c85e8 | ghidra 0x21c85e8 | size 4 | symbol _ZN4Aska9AofObject16SetBinormalDebugEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska9AofObject16SetBinormalDebugEi(void)

{
  return;
}

// ==== Aska::AofObject::GetPackedIndexByAttrType(char const*, char const*) const
// vaddr 0x20c85ec | ghidra 0x21c85ec | size 368 | symbol _ZNK4Aska9AofObject24GetPackedIndexByAttrTypeEPKcS2_ | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZNK4Aska9AofObject24GetPackedIndexByAttrTypeEPKcS2_
                (long param_1,byte *param_2,undefined8 param_3)

{
  long lVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  ulong uVar6;
  long lVar7;
  byte *pbVar8;
  long lVar10;
  uint uVar11;
  uint uVar12;
  long lVar13;
  ulong uVar14;
  byte *pbVar9;
  
  uVar12 = 0x811c9dc5;
  if (param_2 != (byte *)0x0) {
    uVar6 = strlen(param_2);
    if (0x1f < uVar6) {
      return 0;
    }
    pbVar9 = param_2;
    if (uVar6 != 0) goto code_r0x021c864c;
  }
  uVar6 = strlen(param_2);
  pbVar8 = param_2;
  for (; pbVar9 = pbVar8, uVar6 != 0; uVar6 = uVar6 - 1) {
code_r0x021c864c:
    pbVar8 = pbVar9 + 1;
    uVar12 = uVar12 * 0x1000193 ^ (uint)*pbVar9;
  }
  lVar13 = *(long *)(*(long *)(param_1 + 0x3d8) + 0xb0);
  iVar3 = *(int *)(lVar13 + 0xa0);
  if (iVar3 != 0) {
    lVar10 = lVar13 + iVar3;
    uVar2 = *(uint *)(lVar10 + 0xa0);
    uVar4 = Aska::AskaRenderNodeLabel::FindAttrTypeIndex(char const*)(param_3);
    if (uVar2 != 0) {
      uVar11 = 0;
      uVar6 = 0;
      do {
        lVar7 = lVar10 + uVar6 * 4;
        uVar14 = (ulong)*(uint *)(lVar7 + 0xb0);
        uVar6 = uVar6 + 1;
        lVar1 = lVar10 + 0x90 + uVar14;
        if (uVar6 < uVar2) {
          lVar7 = lVar10 + 0x90 + (ulong)*(uint *)(lVar7 + 0xb4);
        }
        else {
          lVar7 = 0;
        }
        Hint_Prefetch(lVar7,0,2,0);
        if ((*(uint *)(lVar1 + 0x10) == uVar12) &&
           (iVar5 = strcmp(param_2,lVar1 + 0x14), iVar5 == 0)) {
          if (*(byte *)(lVar1 + 0x35) == 0) {
            return 0;
          }
          lVar10 = 0;
          do {
            if (*(byte *)(lVar13 + iVar3 + uVar14 + 200 + lVar10 * 4) == uVar4) {
              return (ulong)(uVar11 | uVar4 & 0xffff) | 0x100000000;
            }
            lVar10 = lVar10 + 1;
          } while ((uint)lVar10 < (uint)*(byte *)(lVar1 + 0x35));
          return 0;
        }
        uVar11 = uVar11 + 0x10000;
      } while (uVar6 < uVar2);
    }
  }
  return 0;
}

// ==== Aska::AofObject::GetPackedIndexByTextureType(char const*, Aska::AofObject::TextureType) const
// vaddr 0x20c875c | ghidra 0x21c875c | size 472 | symbol _ZNK4Aska9AofObject27GetPackedIndexByTextureTypeEPKcNS0_11TextureTypeE | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZNK4Aska9AofObject27GetPackedIndexByTextureTypeEPKcNS0_11TextureTypeE
                (long param_1,byte *param_2,uint param_3)

{
  long lVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  ulong uVar6;
  long lVar7;
  long lVar8;
  byte *pbVar9;
  long lVar11;
  uint uVar12;
  uint uVar13;
  undefined8 uVar14;
  ulong uVar15;
  byte abStack_80 [31];
  undefined1 uStack_61;
  byte *pbVar10;
  
  if (param_2 == (byte *)0x0) {
    uVar6 = 0;
  }
  else {
    uVar6 = strlen(param_2);
  }
  if (param_3 != 0) {
    uVar14 = *(undefined8 *)(&UNK_02c48da8 + (ulong)param_3 * 8);
    lVar7 = strlen(uVar14);
    uVar6 = lVar7 + uVar6;
    __aska_snprintf_s(char*, unsigned long, unsigned long, char const*, ...)(abStack_80,0x20,0xffffffffffffffff,&UNK_029dc524/*"%s%s"*/,param_2,uVar14);
    param_2 = abStack_80;
    uStack_61 = 0;
  }
  if (uVar6 < 0x20) {
    uVar13 = 0x811c9dc5;
    pbVar10 = param_2;
    if (uVar6 != 0) goto code_r0x021c8808;
    uVar6 = strlen(param_2);
    pbVar9 = param_2;
    uVar4 = uRam0000000002dcdd18;
    for (; pbVar10 = pbVar9, uRam0000000002dcdd18 = uVar4, uVar6 != 0; uVar6 = uVar6 - 1) {
code_r0x021c8808:
      pbVar9 = pbVar10 + 1;
      uVar13 = uVar13 * 0x1000193 ^ (uint)*pbVar10;
      uVar4 = uRam0000000002dcdd18;
    }
    lVar7 = *(long *)(*(long *)(param_1 + 0x3d8) + 0xb0);
    iVar3 = *(int *)(lVar7 + 0xa0);
    if (iVar3 != 0) {
      lVar11 = lVar7 + iVar3;
      uVar2 = *(uint *)(lVar11 + 0xa0);
      if (uVar2 != 0) {
        uVar12 = 0;
        uVar6 = 0;
        do {
          lVar8 = lVar11 + uVar6 * 4;
          uVar15 = (ulong)*(uint *)(lVar8 + 0xb0);
          uVar6 = uVar6 + 1;
          lVar1 = lVar11 + 0x90 + uVar15;
          if (uVar6 < uVar2) {
            lVar8 = lVar11 + 0x90 + (ulong)*(uint *)(lVar8 + 0xb4);
          }
          else {
            lVar8 = 0;
          }
          Hint_Prefetch(lVar8,0,2,0);
          if ((*(uint *)(lVar1 + 0x10) == uVar13) &&
             (iVar5 = strcmp(param_2,lVar1 + 0x14), iVar5 == 0)) {
            if (*(byte *)(lVar1 + 0x35) == 0) {
              return 0;
            }
            lVar11 = 0;
            while ((uVar13 = *(uint *)(lVar7 + iVar3 + uVar15 + 200 + lVar11 * 4),
                   (uVar13 & 0xf0000000) != 0x20000000 || ((uVar13 & 0xff) != uVar4))) {
              lVar11 = lVar11 + 1;
              if ((uint)*(byte *)(lVar1 + 0x35) <= (uint)lVar11) {
                return 0;
              }
            }
            return (ulong)(uVar12 | uVar4 & 0xffff) | 0x100000000;
          }
          uVar12 = uVar12 + 0x10000;
        } while (uVar6 < uVar2);
      }
    }
  }
  return 0;
}

// ==== Aska::AofObject::SearchTextureID(char const*, Aska::AofObject::TextureType) const
// vaddr 0x20c8934 | ghidra 0x21c8934 | size 68 | symbol _ZNK4Aska9AofObject15SearchTextureIDEPKcNS0_11TextureTypeE | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska9AofObject15SearchTextureIDEPKcNS0_11TextureTypeE(long *param_1)

{
  long lVar1;
  undefined8 uStack_18;
  
  lVar1 = Aska::AofObject::GetPackedIndexByTextureType(char const*, Aska::AofObject::TextureType) const();
  uStack_18 = 0;
  if (lVar1 != 0) {
    uStack_18 = 0;
    (**(code **)(*param_1 + 0x28))(param_1,lVar1,&uStack_18);
  }
  return uStack_18;
}

// ==== Aska::AofObject::ChangeTextureID(unsigned long, char const*, Aska::AofObject::TextureType)
// vaddr 0x20c8978 | ghidra 0x21c8978 | size 108 | symbol _ZN4Aska9AofObject15ChangeTextureIDEmPKcNS0_11TextureTypeE | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska9AofObject15ChangeTextureIDEmPKcNS0_11TextureTypeE
          (long *param_1,undefined8 param_2,undefined8 param_3,undefined4 param_4)

{
  long lVar1;
  undefined8 uStack_28;
  undefined8 uStack_18;
  
  uStack_18 = param_2;
  lVar1 = Aska::AofObject::GetPackedIndexByTextureType(char const*, Aska::AofObject::TextureType) const(param_1,param_3,param_4);
  uStack_28 = 0;
  if (lVar1 != 0) {
    uStack_28 = 0;
    (**(code **)(*param_1 + 0x28))(param_1,lVar1,&uStack_28);
    (**(code **)(*param_1 + 0x30))(param_1,lVar1,&uStack_18);
  }
  return uStack_28;
}

// ==== Aska::AofObject::Get(unsigned long, void*) const
// vaddr 0x20c89e4 | ghidra 0x21c89e4 | size 3900 | symbol _ZNK4Aska9AofObject3GetEmPv | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 _ZNK4Aska9AofObject3GetEmPv(long param_1,ulong param_2,float *param_3)

{
  uint uVar1;
  byte bVar2;
  ushort uVar3;
  uint uVar4;
  char cVar5;
  code *pcVar6;
  int iVar7;
  undefined8 uVar8;
  long *plVar9;
  float fVar10;
  uint uVar11;
  ulong uVar12;
  long lVar13;
  long *plVar14;
  float *pfVar15;
  ushort *puVar16;
  byte *pbVar17;
  long lVar18;
  long lVar19;
  long lVar20;
  uint uVar21;
  uint uVar22;
  ulong uVar23;
  float fVar24;
  float *pfStack_38;
  
  uVar12 = param_2 >> 0x20 & 0xffff;
  if (4 < (uint)uVar12) {
code_r0x011cff50:
    uVar8 = (*(code *)PTR__ZNK4Aska16RenderableObject3GetEmPv_02c9ff98)(param_1,param_2,param_3);
    return uVar8;
  }
  uVar23 = param_2 >> 0x10 & 0xffff;
  uVar21 = (uint)param_2;
  uVar11 = uVar21 & 0xffff;
  uVar22 = (uint)uVar23;
  switch(uVar12) {
  case 1:
    lVar13 = *(long *)(param_1 + 0x3d8);
    lVar18 = *(long *)(lVar13 + 0xb0);
    lVar20 = (long)*(int *)(lVar18 + 0xa0);
    if (*(int *)(lVar18 + 0xa0) != 0) {
      uVar1 = *(uint *)(lVar18 + lVar20 + 0xa0);
      lVar19 = lVar18 + lVar20 + 0x90;
      uVar4 = 0;
      if (uVar1 != 0) {
        uVar4 = uVar22 / uVar1;
      }
      uVar12 = (ulong)*(uint *)(lVar19 + (ulong)(uVar22 - uVar4 * uVar1) * 4 + 0x20);
      uVar3 = *(ushort *)(lVar19 + uVar12 + 0x36);
      if (uVar3 != 0) {
        uVar22 = uVar21 & 0xffff;
        if (uVar22 == 0xb) {
          lVar19 = 0;
          do {
            uVar22 = *(uint *)(lVar18 + lVar20 + uVar12 + 200 + lVar19 * 4);
            if (uVar22 >> 0x1c == 0) {
              if ((uVar22 & 0xff) == uVar11) goto code_r0x021c8d88;
            }
            else if (uVar22 >> 0x1c == 2) {
              lVar18 = 0;
              if (*(long *)(lVar13 + 0x100) != 0) {
                lVar18 = *(long *)(lVar13 + 0x100) + (ulong)(uVar22 >> 8 & 0x7f) * 0x2a0 + 0x10;
              }
              *(undefined8 *)param_3 =
                   *(undefined8 *)(lVar18 + (ulong)(uVar22 >> 0x15 & 0x7f) * 0x20 + 0x20);
              goto code_r0x021c9178;
            }
            lVar19 = lVar19 + 1;
            if ((int)(uint)uVar3 <= (int)lVar19) {
              return 1;
            }
          } while( true );
        }
        if (uVar22 == 0xc) {
          lVar19 = 0;
          do {
            uVar22 = *(uint *)(lVar18 + lVar20 + uVar12 + 200 + lVar19 * 4);
            if (uVar22 >> 0x1c == 0) {
              if ((uVar22 & 0xff) == uVar11) goto code_r0x021c8d88;
            }
            else if (uVar22 >> 0x1c == 2) {
              lVar18 = 0;
              if (*(long *)(lVar13 + 0x100) != 0) {
                lVar18 = *(long *)(lVar13 + 0x100) + (ulong)(uVar22 >> 8 & 0x7f) * 0x2a0 + 0x10;
              }
              *(byte *)param_3 =
                   *(byte *)(lVar18 + (ulong)(uVar22 >> 0x15 & 0x7f) * 0x20 + 0x2e) & 7;
              goto code_r0x021c9178;
            }
            lVar19 = lVar19 + 1;
            if ((int)(uint)uVar3 <= (int)lVar19) {
              return 1;
            }
          } while( true );
        }
        if (uVar22 != 0xd) {
          lVar19 = 0;
          do {
            uVar22 = *(uint *)(lVar18 + lVar20 + uVar12 + 200 + lVar19 * 4);
            uVar1 = uVar22 >> 0x1c;
            if (uVar1 == 2) {
              switch(uVar21 & 0xffff) {
              case 0xe:
                lVar18 = 0;
                if (*(long *)(lVar13 + 0x100) != 0) {
                  lVar18 = *(long *)(lVar13 + 0x100) + (ulong)(uVar22 >> 8 & 0x7f) * 0x2a0 + 0x10;
                }
                *(byte *)param_3 = *(byte *)(lVar18 + (ulong)(uVar22 >> 0x15 & 0x7f) * 0x20 + 0x28);
                goto code_r0x021c9178;
              case 0xf:
                lVar18 = 0;
                if (*(long *)(lVar13 + 0x100) != 0) {
                  lVar18 = *(long *)(lVar13 + 0x100) + (ulong)(uVar22 >> 8 & 0x7f) * 0x2a0 + 0x10;
                }
                *param_3 = (float)((int)*(short *)(lVar18 + (ulong)(uVar22 >> 0x15 & 0x7f) * 0x20 +
                                                  0x2c) >> 6) * _UNK_02808338;
                goto code_r0x021c9178;
              case 0x10:
                lVar18 = 0;
                if (*(long *)(lVar13 + 0x100) != 0) {
                  lVar18 = *(long *)(lVar13 + 0x100) + (ulong)(uVar22 >> 8 & 0x7f) * 0x2a0 + 0x10;
                }
                *(byte *)param_3 =
                     *(byte *)(lVar18 + (ulong)(uVar22 >> 0x15 & 0x7f) * 0x20 + 0x2e) >> 7;
                goto code_r0x021c9178;
              case 0x11:
                lVar18 = 0;
                if (*(long *)(lVar13 + 0x100) != 0) {
                  lVar18 = *(long *)(lVar13 + 0x100) + (ulong)(uVar22 >> 8 & 0x7f) * 0x2a0 + 0x10;
                }
                *(byte *)param_3 =
                     *(byte *)(lVar18 + (ulong)(uVar22 >> 0x15 & 0x7f) * 0x20 + 0x2c) & 0x3f;
                goto code_r0x021c9178;
              case 0x14:
                lVar18 = *(long *)(param_1 + 0x6a0);
                if (((lVar18 == 0) || (*(long *)(lVar18 + 0x50) == 0)) ||
                   (*(long *)(*(long *)(lVar18 + 0x50) + 8) == 0)) goto code_r0x021c9730;
                lVar13 = *(long *)(*(long *)(lVar13 + 0x100) + (ulong)(uVar22 >> 8 & 0x7f) * 0x2a0);
                iVar7 = *(int *)(lVar13 + 0x38);
                if (iVar7 != 0) {
                  lVar13 = iVar7 + lVar13;
                  uVar12 = (ulong)*(ushort *)(lVar13 + (ulong)(uVar22 >> 0x15 & 0x7f) * 2);
                  if (uVar12 == 0) {
                    return 1;
                  }
                  if (lVar13 + uVar12 == 0) {
                    return 1;
                  }
                  lVar13 = (**(code **)(**(long **)(lVar18 + 0x2b0) + 0x58))();
                  if (lVar13 == 0) {
                    *param_3 = 0.0;
                  }
                  else {
                    *param_3 = *(float *)(lVar13 + 0x150);
                  }
                }
                goto code_r0x021c9178;
              case 0x15:
                lVar18 = 0;
                if (*(long *)(lVar13 + 0x100) != 0) {
                  lVar18 = *(long *)(lVar13 + 0x100) + (ulong)(uVar22 >> 8 & 0x7f) * 0x2a0 + 0x10;
                }
                lVar13 = *(long *)(lVar18 + (ulong)(uVar22 >> 0x15 & 0x7f) * 0x20 + 0x30);
                if (lVar13 != 0) {
                  *param_3 = (float)(uint)*(byte *)(lVar13 + 0x15);
                }
                goto code_r0x021c9178;
              case 0x16:
                lVar18 = 0;
                if (*(long *)(lVar13 + 0x100) != 0) {
                  lVar18 = *(long *)(lVar13 + 0x100) + (ulong)(uVar22 >> 8 & 0x7f) * 0x2a0 + 0x10;
                }
                lVar13 = *(long *)(lVar18 + (ulong)(uVar22 >> 0x15 & 0x7f) * 0x20 + 0x30);
                if (lVar13 != 0) {
                  *param_3 = (float)(uint)*(byte *)(lVar13 + 0x16);
                }
                goto code_r0x021c9178;
              case 0x17:
                lVar18 = 0;
                if (*(long *)(lVar13 + 0x100) != 0) {
                  lVar18 = *(long *)(lVar13 + 0x100) + (ulong)(uVar22 >> 8 & 0x7f) * 0x2a0 + 0x10;
                }
                lVar13 = *(long *)(lVar18 + (ulong)(uVar22 >> 0x15 & 0x7f) * 0x20 + 0x30);
                if (lVar13 != 0) {
                  *param_3 = *(float *)(lVar13 + 0x80);
                }
                goto code_r0x021c9178;
              case 0x18:
                lVar18 = 0;
                if (*(long *)(lVar13 + 0x100) != 0) {
                  lVar18 = *(long *)(lVar13 + 0x100) + (ulong)(uVar22 >> 8 & 0x7f) * 0x2a0 + 0x10;
                }
                lVar13 = *(long *)(lVar18 + (ulong)(uVar22 >> 0x15 & 0x7f) * 0x20 + 0x30);
                if (lVar13 != 0) {
                  *param_3 = (float)(uint)*(ushort *)(lVar13 + 0x18);
                }
                goto code_r0x021c9178;
              case 0x19:
                lVar18 = 0;
                if (*(long *)(lVar13 + 0x100) != 0) {
                  lVar18 = *(long *)(lVar13 + 0x100) + (ulong)(uVar22 >> 8 & 0x7f) * 0x2a0 + 0x10;
                }
                lVar13 = *(long *)(lVar18 + (ulong)(uVar22 >> 0x15 & 0x7f) * 0x20 + 0x30);
                if (lVar13 != 0) {
                  *param_3 = (float)(uint)*(ushort *)(lVar13 + 0x1a);
                }
                goto code_r0x021c9178;
              case 0x1a:
                lVar18 = 0;
                if (*(long *)(lVar13 + 0x100) != 0) {
                  lVar18 = *(long *)(lVar13 + 0x100) + (ulong)(uVar22 >> 8 & 0x7f) * 0x2a0 + 0x10;
                }
                lVar13 = *(long *)(lVar18 + (ulong)(uVar22 >> 0x15 & 0x7f) * 0x20 + 0x30);
                if (lVar13 != 0) {
                  *param_3 = (float)(uint)*(byte *)(lVar13 + 0x98);
                }
                goto code_r0x021c9178;
              case 0x1b:
                return 1;
              }
            }
            else if (uVar1 == 1) {
              switch(uVar21 & 0xffff) {
              case 1:
                lVar18 = 0;
                if (*(long *)(lVar13 + 0x100) != 0) {
                  lVar18 = *(long *)(lVar13 + 0x100) + (ulong)(uVar22 >> 8 & 0x7f) * 0x2a0 + 0x10;
                }
                fVar24 = (float)NEON_ucvtf((uint)*(byte *)(lVar18 + 0x231));
                *param_3 = fVar24 / _UNK_028014f8;
                goto code_r0x021c9178;
              case 2:
                lVar18 = 0;
                if (*(long *)(lVar13 + 0x100) != 0) {
                  lVar18 = *(long *)(lVar13 + 0x100) + (ulong)(uVar22 >> 8 & 0x7f) * 0x2a0 + 0x10;
                }
                *param_3 = (float)(uint)*(byte *)(lVar18 + 0x232);
                lVar18 = *(long *)(lVar13 + 0x138);
                if (lVar13 + 0x128 != lVar18) {
                  do {
                    Aska::RenderPass::InvalidateShaders()(*(undefined8 *)(lVar18 + 0x18));
                    Aska::RenderPassManager::InvalidateShaders(bool)(lVar18,0);
                    lVar18 = *(long *)(lVar18 + 0x10);
                  } while (lVar13 + 0x128 != lVar18);
                  return 1;
                }
                goto code_r0x021c9178;
              case 3:
                lVar18 = 0;
                if (*(long *)(lVar13 + 0x100) != 0) {
                  lVar18 = *(long *)(lVar13 + 0x100) + (ulong)(uVar22 >> 8 & 0x7f) * 0x2a0 + 0x10;
                }
                *(byte *)param_3 = (byte)(*(ushort *)(lVar18 + 0x245) >> 3) & 1;
                goto code_r0x021c9178;
              case 4:
                lVar18 = 0;
                if (*(long *)(lVar13 + 0x100) != 0) {
                  lVar18 = *(long *)(lVar13 + 0x100) + (ulong)(uVar22 >> 8 & 0x7f) * 0x2a0 + 0x10;
                }
                *(byte *)param_3 = (byte)(*(ushort *)(lVar18 + 0x245) >> 2) & 1;
                goto code_r0x021c9178;
              case 5:
                lVar18 = 0;
                if (*(long *)(lVar13 + 0x100) != 0) {
                  lVar18 = *(long *)(lVar13 + 0x100) + (ulong)(uVar22 >> 8 & 0x7f) * 0x2a0 + 0x10;
                }
                *param_3 = (float)(uint)*(byte *)(lVar18 + 0x233);
                goto code_r0x021c9178;
              case 6:
                lVar18 = 0;
                if (*(long *)(lVar13 + 0x100) != 0) {
                  lVar18 = *(long *)(lVar13 + 0x100) + (ulong)(uVar22 >> 8 & 0x7f) * 0x2a0 + 0x10;
                }
                uVar11 = (uint)*(ushort *)(lVar18 + 0x245);
                goto code_r0x021c9340;
              case 7:
                lVar18 = 0;
                if (*(long *)(lVar13 + 0x100) != 0) {
                  lVar18 = *(long *)(lVar13 + 0x100) + (ulong)(uVar22 >> 8 & 0x7f) * 0x2a0 + 0x10;
                }
                puVar16 = (ushort *)(lVar18 + 0x245);
                goto code_r0x021c93f4;
              case 8:
                lVar18 = 0;
                if (*(long *)(lVar13 + 0x100) != 0) {
                  lVar18 = *(long *)(lVar13 + 0x100) + (ulong)(uVar22 >> 8 & 0x7f) * 0x2a0 + 0x10;
                }
                puVar16 = (ushort *)(lVar18 + 0x245);
                goto code_r0x021c9408;
              case 10:
                lVar18 = 0;
                if (*(long *)(lVar13 + 0x100) != 0) {
                  lVar18 = *(long *)(lVar13 + 0x100) + (ulong)(uVar22 >> 8 & 0x7f) * 0x2a0 + 0x10;
                }
                *(byte *)param_3 = (byte)((ushort)*(undefined2 *)(lVar18 + 0x245) >> 0xd) & 1;
                goto code_r0x021c9178;
              case 0x1c:
                Aska::RenderPassManager::CreateShaderNodeSystemModifiers(int)(*(undefined8 *)(param_1 + 0x398),0);
                goto code_r0x021c9730;
              }
            }
            else if ((uVar1 == 0) && ((uVar22 & 0xff) == uVar11)) goto code_r0x021c8d88;
            lVar19 = lVar19 + 1;
            if ((int)(uint)uVar3 <= (int)lVar19) {
              return 1;
            }
          } while( true );
        }
        lVar19 = 0;
        do {
          uVar22 = *(uint *)(lVar18 + lVar20 + uVar12 + 200 + lVar19 * 4);
          if (uVar22 >> 0x1c == 0) {
            if ((uVar22 & 0xff) == uVar11) goto code_r0x021c8d88;
          }
          else if (uVar22 >> 0x1c == 2) {
            lVar18 = 0;
            if (*(long *)(lVar13 + 0x100) != 0) {
              lVar18 = *(long *)(lVar13 + 0x100) + (ulong)(uVar22 >> 8 & 0x7f) * 0x2a0 + 0x10;
            }
            *(byte *)param_3 = *(byte *)(lVar18 + (ulong)(uVar22 >> 0x15 & 0x7f) * 0x20 + 0x29);
            break;
          }
          lVar19 = lVar19 + 1;
          if ((int)(uint)uVar3 <= (int)lVar19) {
            return 1;
          }
        } while( true );
      }
    }
    goto code_r0x021c9178;
  case 2:
    plVar9 = (long *)Aska::ModifierManager::FindModifier(Aska::AofObject const*, int)(*(undefined8 *)
                                      PTR__ZN4Aska6Global18m_pModifierManagerE_02cbb990,param_1,
                                     uVar23);
    if (plVar9 == (long *)0x0) {
      return 0;
    }
    goto code_r0x021c8b34;
  case 3:
    goto code_r0x011cff50;
  case 4:
    plVar9 = (long *)Aska::MeshGeneratorManager::FindMeshGenerator(Aska::AofObject const*)(*(undefined8 *)
                                      PTR__ZN4Aska6Global23m_pMeshGeneratorManagerE_02cc2bc0,param_1
                                    );
    if (plVar9 == (long *)0x0) {
      return 0;
    }
code_r0x021c8b34:
                    /* WARNING: Could not recover jumptable at 0x021c8b54. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar8 = (**(code **)(*plVar9 + 0x28))(plVar9,param_2,param_3);
    return uVar8;
  }
  if ((uVar11 != 0xff00) && (0x47 < uVar11 - 0x3b)) goto code_r0x011cff50;
  lVar13 = *(long *)(param_1 + 0x3d8);
  bVar2 = *(byte *)(lVar13 + 0x10a);
  if (6 < uVar11 - 0x3b) {
    uVar1 = uVar21 & 0xffff;
    if (uVar1 == 0x81) {
      for (plVar9 = *(long **)(param_1 + 0x428); (long *)(param_1 + 0x418) != plVar9;
          plVar9 = (long *)plVar9[2]) {
        iVar7 = (**(code **)(*plVar9 + 0x10))(plVar9);
        if ((iVar7 == 1) && (uVar22 == *(byte *)((long)plVar9 + 0x61))) {
          *param_3 = *(float *)((long)plVar9 + 100);
          goto code_r0x021c9178;
        }
      }
      goto code_r0x011cff50;
    }
    if (uVar1 == 0x43) {
      for (plVar9 = *(long **)(param_1 + 0x428); (long *)(param_1 + 0x418) != plVar9;
          plVar9 = (long *)plVar9[2]) {
        iVar7 = (**(code **)(*plVar9 + 0x10))(plVar9);
        if ((iVar7 == 1) && (uVar22 == *(byte *)((long)plVar9 + 0x61))) {
          *param_3 = *(float *)(plVar9 + 9);
          goto code_r0x021c9178;
        }
      }
      goto code_r0x011cff50;
    }
    if (uVar1 == 0x42) {
      if ((bVar2 != 0) && (*(long *)(lVar13 + 0x100) != 0)) {
        lVar18 = 0;
        pbVar17 = (byte *)(*(long *)(lVar13 + 0x100) + 0x240);
        do {
          if (uVar22 == *pbVar17) {
            *param_3 = *(float *)(pbVar17 + -0x10);
            param_3[1] = *(float *)(pbVar17 + -0xc);
            param_3[2] = *(float *)(pbVar17 + -8);
            param_3[3] = *(float *)(pbVar17 + -4);
            goto code_r0x021c9178;
          }
          lVar18 = lVar18 + 1;
          pbVar17 = pbVar17 + 0x2a0;
        } while (lVar18 < (long)(ulong)bVar2);
      }
      goto code_r0x011cff50;
    }
    if (6 < uVar11 - 0x4f) {
      switch(uVar21 & 0xffff) {
      case 0x44:
        goto code_r0x021c8fe0;
      case 0x45:
        goto code_r0x021c93d4;
      case 0x46:
        goto code_r0x021c93e4;
      case 0x47:
        goto code_r0x021c93f0;
      case 0x48:
        goto code_r0x021c9404;
      case 0x49:
        goto code_r0x021c9418;
      case 0x4a:
        goto code_r0x021c9424;
      case 0x4b:
        goto code_r0x021c9430;
      case 0x4c:
        goto code_r0x021c943c;
      case 0x4d:
        goto code_r0x021c9448;
      case 0x4e:
        goto code_r0x021c9450;
      default:
        goto code_r0x011cff50;
      case 0x56:
        goto code_r0x021c945c;
      case 0x57:
        goto code_r0x021c9468;
      case 0x58:
        goto code_r0x021c9474;
      case 0x59:
        goto code_r0x021c9480;
      case 0x5a:
        goto code_r0x021c948c;
      case 0x5b:
        goto code_r0x021c9498;
      case 0x5c:
        goto code_r0x021c94a4;
      case 0x5d:
        goto code_r0x021c94b0;
      case 0x5e:
        goto code_r0x021c94bc;
      case 0x5f:
        goto code_r0x021c94c8;
      case 0x60:
        goto code_r0x021c94dc;
      case 0x61:
      case 0x71:
      case 0x78:
        goto code_r0x021c917c;
      case 0x62:
        goto code_r0x021c94ec;
      case 100:
        goto code_r0x021c9508;
      case 0x65:
        goto code_r0x021c951c;
      case 0x66:
        goto code_r0x021c9528;
      case 0x67:
        goto code_r0x021c9534;
      case 0x68:
        goto code_r0x021c9544;
      case 0x69:
        goto code_r0x021c9730;
      case 0x6f:
        goto code_r0x021c955c;
      case 0x72:
        goto code_r0x021c9568;
      case 0x73:
        goto code_r0x021c9578;
      case 0x74:
        goto code_r0x021c9584;
      case 0x75:
        goto code_r0x021c9590;
      case 0x76:
        goto code_r0x021c959c;
      case 0x77:
        goto code_r0x021c95a8;
      case 0x79:
        goto code_r0x021c95b4;
      case 0x7c:
        goto code_r0x021c95c4;
      case 0x82:
        goto code_r0x021c95d0;
      }
    }
    lVar18 = 0;
    if (*(long *)(lVar13 + 0x100) != 0) {
      lVar18 = *(long *)(lVar13 + 0x100) + uVar23 * 0x2a0 + 0x10;
    }
    switch(uVar21 & 0xffff) {
    case 0x44:
      goto code_r0x021c8fe0;
    case 0x45:
code_r0x021c93d4:
      *(byte *)param_3 = (byte)(*(uint *)(param_1 + 0x378) >> 0x14) & 1;
      break;
    case 0x46:
code_r0x021c93e4:
      *param_3 = (float)(uint)*(byte *)(param_1 + 0x69b);
      break;
    case 0x47:
code_r0x021c93f0:
      puVar16 = (ushort *)(param_1 + 0x1b5);
code_r0x021c93f4:
      *(byte *)param_3 = (byte)(*puVar16 >> 4) & 1;
      break;
    case 0x48:
code_r0x021c9404:
      puVar16 = (ushort *)(param_1 + 0x1b5);
code_r0x021c9408:
      *(byte *)param_3 = (byte)(*puVar16 >> 5) & 1;
      break;
    case 0x49:
code_r0x021c9418:
      *param_3 = (float)(uint)*(byte *)(lVar13 + 0xb8);
      break;
    case 0x4a:
code_r0x021c9424:
      *param_3 = *(float *)(lVar13 + 0xbc);
      break;
    case 0x4b:
code_r0x021c9430:
      *param_3 = *(float *)(lVar13 + 0xc0);
      break;
    case 0x4c:
code_r0x021c943c:
      *param_3 = (float)(int)*(char *)(lVar13 + 0x10c);
      break;
    case 0x4d:
code_r0x021c9448:
      *(byte *)param_3 = 0;
      break;
    case 0x4e:
code_r0x021c9450:
      *param_3 = (float)(uint)*(byte *)(param_1 + 0x69c);
      break;
    case 0x4f:
      *param_3 = *(float *)(*(long *)(lVar18 + 0x288) + 0x30);
      break;
    case 0x50:
      *param_3 = *(float *)(*(long *)(lVar18 + 0x288) + 4);
      break;
    case 0x51:
      *param_3 = *(float *)(*(long *)(lVar18 + 0x288) + 0x34);
      break;
    case 0x52:
      *param_3 = *(float *)(*(long *)(lVar18 + 0x288) + 8);
      break;
    case 0x53:
      *param_3 = *(float *)(*(long *)(lVar18 + 0x288) + 0xc);
      break;
    case 0x54:
      *param_3 = *(float *)(*(long *)(lVar18 + 0x288) + 0x38);
      break;
    case 0x55:
      lVar13 = *(long *)(lVar18 + 0x288);
      *param_3 = *(float *)(lVar13 + 0x20);
      param_3[1] = *(float *)(lVar13 + 0x24);
      param_3[2] = *(float *)(lVar13 + 0x28);
      param_3[3] = *(float *)(lVar13 + 0x2c);
      break;
    case 0x56:
code_r0x021c945c:
      *param_3 = *(float *)(param_1 + 0x628);
      break;
    case 0x57:
code_r0x021c9468:
      *param_3 = *(float *)(param_1 + 0x630);
      break;
    case 0x58:
code_r0x021c9474:
      *param_3 = *(float *)(param_1 + 0x62c);
      break;
    case 0x59:
code_r0x021c9480:
      *param_3 = *(float *)(param_1 + 0x634);
      break;
    case 0x5a:
code_r0x021c948c:
      *param_3 = *(float *)(param_1 + 0x638);
      break;
    case 0x5b:
code_r0x021c9498:
      *param_3 = *(float *)(param_1 + 0x640);
      break;
    case 0x5c:
code_r0x021c94a4:
      *param_3 = *(float *)(param_1 + 0x63c);
      break;
    case 0x5d:
code_r0x021c94b0:
      *param_3 = *(float *)(param_1 + 0x620);
      break;
    case 0x5e:
code_r0x021c94bc:
      *param_3 = *(float *)(param_1 + 0x624);
      break;
    case 0x5f:
code_r0x021c94c8:
      fVar24 = 0.0;
      if (*(long *)(lVar13 + 0xd0) == 0) goto code_r0x021c9554;
      *param_3 = *(float *)(lVar13 + 200);
      break;
    case 0x60:
code_r0x021c94dc:
      fVar24 = 0.0;
      if (*(long *)(lVar13 + 0xd0) != 0) {
        fVar24 = *(float *)(lVar13 + 0xc4);
      }
      goto code_r0x021c9554;
    case 0x61:
    case 0x71:
    case 0x78:
      goto code_r0x021c917c;
    case 0x62:
code_r0x021c94ec:
      if ((*(uint *)(param_1 + 0x378) >> 0xd & 1) == 0) {
        *param_3 = 0.0;
      }
      else {
        *param_3 = (float)(*(byte *)(param_1 + 900) + 1);
      }
      break;
    default:
      goto code_r0x011cff50;
    case 100:
code_r0x021c9508:
      *param_3 = (float)(int)(char)*PTR__ZN4Aska9AofObject28m_nSpecialShadowAdapterLimitE_02cbb5f0;
      break;
    case 0x65:
code_r0x021c951c:
      *param_3 = (float)(int)*(char *)(param_1 + 0x380);
      break;
    case 0x66:
code_r0x021c9528:
      *param_3 = *(float *)(param_1 + 0x4f0);
      break;
    case 0x67:
code_r0x021c9534:
      *(byte *)param_3 = (byte)(*(uint *)(param_1 + 0x378) >> 0x13) & 1;
      break;
    case 0x68:
code_r0x021c9544:
      fVar24 = 0.0;
      if (*(long *)(lVar13 + 0xd0) != 0) {
        fVar24 = (float)(uint)*(ushort *)(*(long *)(lVar13 + 0xb0) + 0x70);
      }
code_r0x021c9554:
      *param_3 = fVar24;
      break;
    case 0x69:
code_r0x021c9730:
      *param_3 = 0.0;
      break;
    case 0x6f:
code_r0x021c955c:
      *param_3 = (float)(uint)*(byte *)(param_1 + 0x388);
      break;
    case 0x72:
code_r0x021c9568:
      *(byte *)param_3 = (byte)(*(uint *)(param_1 + 0x378) >> 0xb) & 1;
      break;
    case 0x73:
code_r0x021c9578:
      *param_3 = (float)(uint)*(byte *)(param_1 + 0x389);
      break;
    case 0x74:
code_r0x021c9584:
      *param_3 = (float)(uint)*(byte *)(param_1 + 0x38a);
      break;
    case 0x75:
code_r0x021c9590:
      *param_3 = (float)(uint)*(byte *)(param_1 + 0x38b);
      break;
    case 0x76:
code_r0x021c959c:
      *param_3 = (float)(uint)*(byte *)(param_1 + 0x38c);
      break;
    case 0x77:
code_r0x021c95a8:
      *param_3 = (float)(uint)*(byte *)(param_1 + 0x38d);
      break;
    case 0x79:
code_r0x021c95b4:
      *(byte *)param_3 = (byte)(*(ushort *)(param_1 + 0x37c) >> 2) & 1;
      break;
    case 0x7c:
code_r0x021c95c4:
      *param_3 = (float)(int)*(char *)(param_1 + 0x381);
      break;
    case 0x82:
code_r0x021c95d0:
      *(byte *)param_3 = (byte)(*(ushort *)(param_1 + 0x1b5) >> 6) & 1;
    }
    goto code_r0x021c9178;
  }
  if (bVar2 == 0) goto code_r0x011cff50;
  if (*(long *)(lVar13 + 0x100) != 0) {
    lVar18 = 0;
    plVar9 = (long *)(*(long *)(lVar13 + 0x100) + 0x290);
    lVar13 = 1;
    do {
      if ((*(char *)((long)plVar9 + -0x3d) != -1) && (uVar22 == *(byte *)((long)plVar9 + -0x3e))) {
        plVar14 = plVar9 + -0x50;
        cVar5 = *(char *)((long)plVar9 + -0x3d);
        goto code_r0x021c8eec;
      }
      if (uVar22 == *(byte *)((long)plVar9 + -0x46)) {
        lVar13 = 0;
code_r0x021c90e4:
        switch(uVar21 & 0xffff) {
        case 0x3b:
          pfVar15 = (float *)(*plVar9 + lVar13 * 0x2c);
          goto code_r0x021c9114;
        case 0x3c:
          lVar13 = *plVar9 + lVar13 * 0x2c;
          goto code_r0x021c9128;
        case 0x3d:
          lVar13 = *plVar9 + lVar13 * 0x2c;
          goto code_r0x021c913c;
        case 0x3e:
          lVar13 = *plVar9 + lVar13 * 0x2c;
          goto code_r0x021c9154;
        case 0x3f:
          lVar13 = *plVar9 + lVar13 * 0x2c;
          goto code_r0x021c9168;
        case 0x40:
          lVar13 = *plVar9 + lVar13 * 0x2c;
          break;
        default:
          goto code_r0x021c9178;
        }
        goto code_r0x021c919c;
      }
      if (uVar22 == *(byte *)((long)plVar9 + -0x45)) goto code_r0x021c90e4;
      if (uVar22 == *(byte *)((long)plVar9 + -0x44)) {
        lVar13 = 2;
        goto code_r0x021c90e4;
      }
      if (uVar22 == *(byte *)((long)plVar9 + -0x43)) {
        lVar13 = 3;
        goto code_r0x021c90e4;
      }
      if (uVar22 == *(byte *)((long)plVar9 + -0x42)) {
        lVar13 = 4;
        goto code_r0x021c90e4;
      }
      if (uVar22 == *(byte *)((long)plVar9 + -0x41)) {
        lVar13 = 5;
        goto code_r0x021c90e4;
      }
      if (uVar22 == *(byte *)(plVar9 + -8)) {
        lVar13 = 6;
        goto code_r0x021c90e4;
      }
      if (uVar22 == *(byte *)((long)plVar9 + -0x3f)) {
        lVar13 = 7;
        goto code_r0x021c90e4;
      }
      lVar18 = lVar18 + 1;
      plVar9 = plVar9 + 0x54;
    } while (lVar18 < (long)(ulong)bVar2);
    goto code_r0x011cff50;
  }
  if ((cRam0000000000000243 == -1) || (uVar22 != (int)cRam0000000000000242)) {
                    /* WARNING: Does not return */
    pcVar6 = (code *)SoftwareBreakpoint(1,0x21c9920);
    (*pcVar6)();
  }
  plVar14 = (long *)0x0;
  cVar5 = cRam0000000000000243;
code_r0x021c8eec:
  switch(uVar21 & 0xffff) {
  case 0x3b:
    pfVar15 = (float *)(plVar14[0x50] + (long)cVar5 * 0x2c);
code_r0x021c9114:
    fVar24 = *pfVar15;
    fVar10 = pfVar15[1];
    break;
  case 0x3c:
    lVar13 = plVar14[0x50] + (long)cVar5 * 0x2c;
code_r0x021c9128:
    fVar24 = *(float *)(lVar13 + 8);
    fVar10 = *(float *)(lVar13 + 0xc);
    break;
  case 0x3d:
    lVar13 = plVar14[0x50] + (long)cVar5 * 0x2c;
code_r0x021c913c:
    *param_3 = *(float *)(lVar13 + 0x10);
    goto code_r0x021c9178;
  case 0x3e:
    lVar13 = plVar14[0x50] + (long)cVar5 * 0x2c;
code_r0x021c9154:
    fVar24 = *(float *)(lVar13 + 0x14);
    fVar10 = *(float *)(lVar13 + 0x18);
    break;
  case 0x3f:
    lVar13 = plVar14[0x50] + (long)cVar5 * 0x2c;
code_r0x021c9168:
    fVar24 = *(float *)(lVar13 + 0x1c);
    fVar10 = *(float *)(lVar13 + 0x20);
    break;
  case 0x40:
    lVar13 = plVar14[0x50] + (long)cVar5 * 0x2c;
code_r0x021c919c:
    *param_3 = *(float *)(lVar13 + 0x24);
  default:
    goto code_r0x021c9178;
  }
  param_3[2] = 0.0;
  param_3[3] = 1.0;
  *param_3 = fVar24;
  param_3[1] = fVar10;
code_r0x021c9178:
code_r0x021c917c:
  return 1;
code_r0x021c8d88:
  uVar11 = uVar22 >> 0x15 & 0x7f;
  iVar7 = Aska::ShaderConstantManager::GetShaderConstantF(int, int, Aska::Vector**) const(*(long *)(lVar13 + 0x150) + (ulong)(uVar22 >> 8 & 0x7f) * 0x1b8,uVar11,
                          uVar22 >> 0xf & 0x3f,&pfStack_38);
  if (iVar7 == 0) {
    uVar11 = 0xffffffff;
  }
  switch(uVar11) {
  case 7:
  case 0x12:
    *param_3 = *pfStack_38;
    break;
  case 8:
  case 0xb:
    Aska::AhslConst::AofRecoverFromNativeConstant(int, Aska::Vector const*, Aska::Vector*)(uVar11,pfStack_38,param_3);
    break;
  default:
    *param_3 = *pfStack_38;
    param_3[1] = pfStack_38[1];
    param_3[2] = pfStack_38[2];
    param_3[3] = pfStack_38[3];
    break;
  case 0xc:
  case 0xe:
    uVar8 = *(undefined8 *)(pfStack_38 + 4);
    *(undefined8 *)(param_3 + 6) = *(undefined8 *)(pfStack_38 + 6);
    *(undefined8 *)(param_3 + 4) = uVar8;
    uVar8 = *(undefined8 *)pfStack_38;
    *(undefined8 *)(param_3 + 2) = *(undefined8 *)(pfStack_38 + 2);
    *(undefined8 *)param_3 = uVar8;
    break;
  case 0x1f:
    uVar8 = *(undefined8 *)pfStack_38;
    *(undefined8 *)(param_3 + 2) = *(undefined8 *)(pfStack_38 + 2);
    *(undefined8 *)param_3 = uVar8;
    uVar8 = *(undefined8 *)(pfStack_38 + 4);
    *(undefined8 *)(param_3 + 6) = *(undefined8 *)(pfStack_38 + 6);
    *(undefined8 *)(param_3 + 4) = uVar8;
    uVar8 = *(undefined8 *)(pfStack_38 + 8);
    *(undefined8 *)(param_3 + 10) = *(undefined8 *)(pfStack_38 + 10);
    *(undefined8 *)(param_3 + 8) = uVar8;
    uVar8 = *(undefined8 *)(pfStack_38 + 0xc);
    *(undefined8 *)(param_3 + 0xe) = *(undefined8 *)(pfStack_38 + 0xe);
    *(undefined8 *)(param_3 + 0xc) = uVar8;
  }
  goto code_r0x021c9178;
code_r0x021c8fe0:
  uVar11 = *(uint *)(param_1 + 0x378);
code_r0x021c9340:
  *(byte *)param_3 = (byte)(uVar11 >> 1) & 1;
  goto code_r0x021c9178;
}

// ==== Aska::AofObject::Set(unsigned long, void const*)
// vaddr 0x20c9920 | ghidra 0x21c9920 | size 6472 | symbol _ZN4Aska9AofObject3SetEmPKv | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 _ZN4Aska9AofObject3SetEmPKv(long *param_1,ulong param_2,float *param_3)

{
  ushort *puVar1;
  ushort *puVar2;
  float fVar3;
  float fVar4;
  uint uVar5;
  undefined6 uVar6;
  bool bVar7;
  bool bVar8;
  int iVar9;
  int iVar10;
  undefined4 uVar11;
  int iVar12;
  undefined8 uVar13;
  long *plVar14;
  float *pfVar15;
  uint uVar16;
  ulong uVar17;
  ulong uVar18;
  long lVar19;
  long lVar20;
  code *pcVar21;
  byte bVar22;
  ushort uVar23;
  ushort uVar24;
  long lVar25;
  uint uVar26;
  long lVar27;
  uint uVar28;
  ulong uVar29;
  uint *puVar30;
  long lVar31;
  long lVar32;
  float fVar33;
  float fVar34;
  float fVar35;
  float afStack_90 [12];
  
  uVar17 = param_2 >> 0x20 & 0xffff;
  if (4 < (uint)uVar17) {
code_r0x011c80f0:
    uVar13 = (*(code *)PTR__ZN4Aska16RenderableObject3SetEmPKv_02c9c068)(param_1,param_2,param_3);
    return uVar13;
  }
  uVar29 = param_2 >> 0x10 & 0xffff;
  uVar26 = (uint)param_2;
  uVar16 = uVar26 & 0xffff;
  uVar28 = (uint)uVar29;
  switch(uVar17) {
  case 0:
    if ((uVar16 != 0xff00) && (0x47 < uVar16 - 0x3b)) goto code_r0x011c80f0;
    lVar31 = param_1[0x7b];
    bVar22 = *(byte *)(lVar31 + 0x10a);
    if (uVar16 - 0x3b < 7) {
      if (bVar22 == 0) {
        return 1;
      }
      uVar17 = 0;
      puVar2 = (ushort *)(lVar31 + 0x177);
      do {
        lVar27 = 0;
        if (*(long *)(lVar31 + 0x100) != 0) {
          lVar27 = *(long *)(lVar31 + 0x100) + uVar17 * 0x2a0 + 0x10;
        }
        if ((*(char *)(lVar27 + 0x243) == -1) || (uVar28 != (int)*(char *)(lVar27 + 0x242))) {
          uVar29 = 0;
          iVar12 = 0;
          uVar18 = 0;
          do {
            if (uVar28 == *(byte *)(lVar27 + uVar29 + 0x23a)) {
              SetUVShiftParam(int, int, Aska::MaterialContext*, void const*)(uVar16,uVar29 & 0xffffffff,lVar27,param_3);
              puVar1 = (ushort *)(*(long *)(lVar31 + 0x100) + uVar17 * 0x2a0 + 0x255);
              *puVar1 = *puVar1 | 1;
              uVar23 = *(ushort *)(lVar31 + 0x108);
              if ((uVar23 >> 2 & 1) == 0) {
                *puVar2 = *puVar2 | 1;
                if (*(long *)(lVar31 + 0x188) != 0) {
                  bVar8 = false;
                  lVar25 = *(long *)(lVar31 + 0x188);
code_r0x021c9bec:
                  do {
                    do {
                      lVar19 = lVar25;
                      if (!bVar8) {
                        bVar8 = false;
                        *(ushort *)(lVar19 + 0x2f) = *(ushort *)(lVar19 + 0x2f) | 1;
                        lVar25 = *(long *)(lVar19 + 0x40);
                        if (*(long *)(lVar19 + 0x40) != 0) goto code_r0x021c9bec;
                      }
                      bVar8 = false;
                      lVar25 = *(long *)(lVar19 + 0x48);
                    } while (*(long *)(lVar19 + 0x48) != 0);
                    bVar8 = true;
                    lVar25 = *(long *)(lVar19 + 0x38);
                  } while (*(long *)(lVar19 + 0x38) != lVar31 + 0x148);
                  uVar23 = *(ushort *)(lVar31 + 0x108);
                }
                *(ushort *)(lVar31 + 0x108) = uVar23 | 4;
              }
              iVar12 = iVar12 + 1;
              uVar18 = uVar29 & 0xffffffff;
            }
            uVar29 = uVar29 + 1;
          } while (uVar29 != 8);
          if (iVar12 == 1) {
            *(char *)(lVar27 + 0x243) = (char)uVar18;
            *(char *)(lVar27 + 0x242) = (char)(param_2 >> 0x10);
          }
          else if (1 < iVar12) {
            *(undefined1 *)(lVar27 + 0x243) = 0xff;
          }
        }
        else {
          SetUVShiftParam(int, int, Aska::MaterialContext*, void const*)(uVar16,(long)*(char *)(lVar27 + 0x243),lVar27,param_3);
          puVar1 = (ushort *)(*(long *)(lVar31 + 0x100) + uVar17 * 0x2a0 + 0x255);
          *puVar1 = *puVar1 | 1;
          uVar23 = *(ushort *)(lVar31 + 0x108);
          if ((uVar23 >> 2 & 1) == 0) {
            *puVar2 = *puVar2 | 1;
            if (*(long *)(lVar31 + 0x188) != 0) {
              bVar8 = false;
              lVar27 = *(long *)(lVar31 + 0x188);
code_r0x021c9b30:
              do {
                do {
                  lVar25 = lVar27;
                  if (!bVar8) {
                    bVar8 = false;
                    *(ushort *)(lVar25 + 0x2f) = *(ushort *)(lVar25 + 0x2f) | 1;
                    lVar27 = *(long *)(lVar25 + 0x40);
                    if (*(long *)(lVar25 + 0x40) != 0) goto code_r0x021c9b30;
                  }
                  bVar8 = false;
                  lVar27 = *(long *)(lVar25 + 0x48);
                } while (*(long *)(lVar25 + 0x48) != 0);
                bVar8 = true;
                lVar27 = *(long *)(lVar25 + 0x38);
              } while (*(long *)(lVar25 + 0x38) != lVar31 + 0x148);
              uVar23 = *(ushort *)(lVar31 + 0x108);
            }
            *(ushort *)(lVar31 + 0x108) = uVar23 | 4;
          }
        }
        uVar17 = uVar17 + 1;
        if (uVar17 == bVar22) {
          return 1;
        }
      } while( true );
    }
    uVar5 = uVar26 & 0xffff;
    if (uVar5 == 0x81) {
      plVar14 = (long *)param_1[0x85];
      if (param_1 + 0x83 != plVar14) {
        do {
          iVar12 = (**(code **)(*plVar14 + 0x10))(plVar14);
          if ((iVar12 == 1) && (uVar28 == *(byte *)((long)plVar14 + 0x61))) {
            *(float *)((long)plVar14 + 100) = *param_3;
          }
          plVar14 = (long *)plVar14[2];
        } while (param_1 + 0x83 != plVar14);
        return 1;
      }
      return 1;
    }
    if (uVar5 == 0x43) {
      plVar14 = (long *)param_1[0x85];
      if (param_1 + 0x83 != plVar14) {
        do {
          iVar12 = (**(code **)(*plVar14 + 0x10))(plVar14);
          if ((iVar12 == 1) && (uVar28 == *(byte *)((long)plVar14 + 0x61))) {
            Aska::TextureReplaceAnimModifier::SetFrame(float)(*param_3,plVar14);
          }
          plVar14 = (long *)plVar14[2];
        } while (param_1 + 0x83 != plVar14);
        return 1;
      }
      return 1;
    }
    if (uVar5 == 0x42) {
      if (bVar22 == 0) {
        return 1;
      }
      uVar17 = 0;
      do {
        lVar27 = 0;
        if (*(long *)(lVar31 + 0x100) != 0) {
          lVar27 = *(long *)(lVar31 + 0x100) + uVar17 * 0x2a0 + 0x10;
        }
        if (uVar28 == *(byte *)(lVar27 + 0x230)) {
          *(float *)(lVar27 + 0x220) = *param_3;
          *(float *)(lVar27 + 0x224) = param_3[1];
          *(float *)(lVar27 + 0x228) = param_3[2];
          *(float *)(lVar27 + 0x22c) = param_3[3];
          puVar2 = (ushort *)(*(long *)(lVar31 + 0x100) + uVar17 * 0x2a0 + 0x255);
          *puVar2 = *puVar2 | 1;
          uVar23 = *(ushort *)(lVar31 + 0x108);
          if ((uVar23 >> 2 & 1) == 0) {
            *(ushort *)(lVar31 + 0x177) = *(ushort *)(lVar31 + 0x177) | 1;
            if (*(long *)(lVar31 + 0x188) != 0) {
              bVar8 = false;
              lVar27 = *(long *)(lVar31 + 0x188);
code_r0x021c9d44:
              do {
                do {
                  lVar25 = lVar27;
                  if (!bVar8) {
                    bVar8 = false;
                    *(ushort *)(lVar25 + 0x2f) = *(ushort *)(lVar25 + 0x2f) | 1;
                    lVar27 = *(long *)(lVar25 + 0x40);
                    if (*(long *)(lVar25 + 0x40) != 0) goto code_r0x021c9d44;
                  }
                  bVar8 = false;
                  lVar27 = *(long *)(lVar25 + 0x48);
                } while (*(long *)(lVar25 + 0x48) != 0);
                bVar8 = true;
                lVar27 = *(long *)(lVar25 + 0x38);
              } while (*(long *)(lVar25 + 0x38) != lVar31 + 0x148);
              uVar23 = *(ushort *)(lVar31 + 0x108);
            }
            *(ushort *)(lVar31 + 0x108) = uVar23 | 4;
          }
        }
        uVar17 = uVar17 + 1;
        if (uVar17 == bVar22) {
          return 1;
        }
      } while( true );
    }
    if (uVar16 - 0x4f < 7) {
      lVar25 = *(long *)(lVar31 + 0x100) + uVar29 * 0x2a0;
      puVar2 = (ushort *)(lVar25 + 0x255);
      lVar27 = 0;
      if (*(long *)(lVar31 + 0x100) != 0) {
        lVar27 = lVar25 + 0x10;
      }
      *puVar2 = *puVar2 | 1;
      uVar23 = *(ushort *)(lVar31 + 0x108);
      if ((uVar23 >> 2 & 1) == 0) {
        *(ushort *)(lVar31 + 0x177) = *(ushort *)(lVar31 + 0x177) | 1;
        if (*(long *)(lVar31 + 0x188) != 0) {
          bVar8 = false;
          lVar25 = *(long *)(lVar31 + 0x188);
code_r0x021ca34c:
          do {
            do {
              lVar19 = lVar25;
              if (!bVar8) {
                bVar8 = false;
                *(ushort *)(lVar19 + 0x2f) = *(ushort *)(lVar19 + 0x2f) | 1;
                lVar25 = *(long *)(lVar19 + 0x40);
                if (*(long *)(lVar19 + 0x40) != 0) goto code_r0x021ca34c;
              }
              bVar8 = false;
              lVar25 = *(long *)(lVar19 + 0x48);
            } while (*(long *)(lVar19 + 0x48) != 0);
            bVar8 = true;
            lVar25 = *(long *)(lVar19 + 0x38);
          } while (*(long *)(lVar19 + 0x38) != lVar31 + 0x148);
          uVar23 = *(ushort *)(lVar31 + 0x108);
        }
        *(ushort *)(lVar31 + 0x108) = uVar23 | 4;
      }
      switch(uVar26 & 0xffff) {
      case 0x44:
code_r0x021ca438:
        bVar22 = *(byte *)param_3;
        if ((uint)(bVar22 != 0) == ((uint)(*(uint6 *)(param_1 + 0x6f) >> 1) & 1)) {
          return 1;
        }
        *(undefined2 *)((long)param_1 + 0x37c) = *(undefined2 *)((long)param_1 + 0x37c);
        *(uint *)(param_1 + 0x6f) =
             (uint)*(uint6 *)(param_1 + 0x6f) & 0xfffffffd | (bVar22 & 0x7f) << 1;
        uVar17 = (ulong)*(ushort *)((long)param_1 + 0x462);
        if (uVar17 != 0) {
          lVar31 = 0;
          do {
            uVar17 = uVar17 - 1;
            plVar14 = param_1 + 0x8e;
            if ((long *)param_1[0x8b] != (long *)0x0) {
              plVar14 = (long *)param_1[0x8b];
            }
            *(undefined1 *)((long)plVar14 + lVar31 + 0x1a) = 0;
            lVar31 = lVar31 + 0x20;
          } while (uVar17 != 0);
          return 1;
        }
        return 1;
      case 0x45:
      case 0x46:
      case 0x4d:
      case 0x4e:
      case 0x61:
      case 0x6e:
      case 0x71:
      case 0x78:
      case 0x7b:
        return 1;
      case 0x47:
code_r0x021caa40:
        pcVar21 = *(code **)(*param_1 + 0x1a0);
        break;
      case 0x48:
code_r0x021caa4c:
        pcVar21 = *(code **)(*param_1 + 0x1a8);
        break;
      case 0x49:
code_r0x021caa64:
        *(char *)(param_1[0x7b] + 0xb8) = SUB41(*param_3,0);
        for (lVar27 = *(long *)(lVar31 + 0x138); lVar31 + 0x128 != lVar27;
            lVar27 = *(long *)(lVar27 + 0x10)) {
          lVar25 = Aska::RenderPassManager::GetPass(int, int)(lVar27,2,0);
          if (lVar25 != 0) {
            *(ushort *)(lVar25 + 0x2f) = *(ushort *)(lVar25 + 0x2f) & 0xffbf;
          }
        }
        uVar17 = (ulong)*(ushort *)((long)param_1 + 0x462);
        if (uVar17 == 0) {
          return 1;
        }
        lVar31 = 0;
        do {
          uVar17 = uVar17 - 1;
          plVar14 = param_1 + 0x8e;
          if ((long *)param_1[0x8b] != (long *)0x0) {
            plVar14 = (long *)param_1[0x8b];
          }
          *(undefined1 *)((long)plVar14 + lVar31 + 0x1a) = 0;
          lVar31 = lVar31 + 0x20;
        } while (uVar17 != 0);
        return 1;
      case 0x4a:
code_r0x021caaec:
        *(float *)(param_1[0x7b] + 0xbc) = *param_3;
        for (lVar27 = *(long *)(lVar31 + 0x138); lVar31 + 0x128 != lVar27;
            lVar27 = *(long *)(lVar27 + 0x10)) {
          lVar25 = Aska::RenderPassManager::GetPass(int, int)(lVar27,2,0);
          if (lVar25 != 0) {
            *(ushort *)(lVar25 + 0x2f) = *(ushort *)(lVar25 + 0x2f) & 0xffbf;
          }
        }
        uVar17 = (ulong)*(ushort *)((long)param_1 + 0x462);
        if (uVar17 == 0) {
          return 1;
        }
        lVar31 = 0;
        do {
          uVar17 = uVar17 - 1;
          plVar14 = param_1 + 0x8e;
          if ((long *)param_1[0x8b] != (long *)0x0) {
            plVar14 = (long *)param_1[0x8b];
          }
          *(undefined1 *)((long)plVar14 + lVar31 + 0x1a) = 0;
          lVar31 = lVar31 + 0x20;
        } while (uVar17 != 0);
        return 1;
      case 0x4b:
code_r0x021cab74:
        *(float *)(param_1[0x7b] + 0xc0) = *param_3;
        for (lVar27 = *(long *)(lVar31 + 0x138); lVar31 + 0x128 != lVar27;
            lVar27 = *(long *)(lVar27 + 0x10)) {
          lVar25 = Aska::RenderPassManager::GetPass(int, int)(lVar27,2,0);
          if (lVar25 != 0) {
            *(ushort *)(lVar25 + 0x2f) = *(ushort *)(lVar25 + 0x2f) & 0xffbf;
          }
        }
        uVar17 = (ulong)*(ushort *)((long)param_1 + 0x462);
        if (uVar17 == 0) {
          return 1;
        }
        lVar31 = 0;
        do {
          uVar17 = uVar17 - 1;
          plVar14 = param_1 + 0x8e;
          if ((long *)param_1[0x8b] != (long *)0x0) {
            plVar14 = (long *)param_1[0x8b];
          }
          *(undefined1 *)((long)plVar14 + lVar31 + 0x1a) = 0;
          lVar31 = lVar31 + 0x20;
        } while (uVar17 != 0);
        return 1;
      case 0x4c:
code_r0x021cabfc:
        Aska::MaterialList::SetPerPixelLightCount(int)(lVar31 + 0xe8,*param_3);
        return 1;
      case 0x4f:
        fVar33 = *param_3;
        *(float *)(*(long *)(lVar27 + 0x288) + 0x30) = fVar33;
        fVar33 = 1.0 / (float)(uint)fVar33;
        **(float **)(lVar27 + 0x288) = fVar33 * (*(float **)(lVar27 + 0x288))[0xd];
        lVar31 = *(long *)(lVar27 + 0x288);
        *(float *)(lVar31 + 0x10) = fVar33 * *(float *)(lVar31 + 0x20);
        *(float *)(lVar31 + 0x14) = fVar33 * *(float *)(lVar31 + 0x24);
        *(float *)(lVar31 + 0x18) = fVar33 * *(float *)(lVar31 + 0x28);
        *(float *)(lVar31 + 0x1c) = fVar33 * *(float *)(lVar31 + 0x2c);
        return 1;
      case 0x50:
        *(float *)(*(long *)(lVar27 + 0x288) + 4) = *param_3;
        return 1;
      case 0x51:
        fVar33 = *param_3;
        *(float *)(*(long *)(lVar27 + 0x288) + 0x34) = fVar33;
        fVar35 = (float)NEON_ucvtf((*(float **)(lVar27 + 0x288))[0xc]);
        **(float **)(lVar27 + 0x288) = fVar33 / fVar35;
        return 1;
      case 0x52:
        *(float *)(*(long *)(lVar27 + 0x288) + 8) = *param_3;
        return 1;
      case 0x53:
        *(float *)(*(long *)(lVar27 + 0x288) + 0xc) = *param_3;
        return 1;
      case 0x54:
        *(float *)(*(long *)(lVar27 + 0x288) + 0x38) = *param_3;
        return 1;
      case 0x55:
        lVar31 = *(long *)(lVar27 + 0x288);
        fVar33 = *param_3;
        fVar3 = param_3[1];
        fVar35 = param_3[2];
        fVar4 = param_3[3];
        *(float *)(lVar31 + 0x20) = fVar33;
        *(float *)(lVar31 + 0x24) = fVar3;
        *(float *)(lVar31 + 0x28) = fVar35;
        *(float *)(lVar31 + 0x2c) = fVar4;
        lVar31 = *(long *)(lVar27 + 0x288);
        fVar34 = (float)NEON_ucvtf(*(undefined4 *)(lVar31 + 0x30));
        fVar34 = 1.0 / fVar34;
        *(float *)(lVar31 + 0x10) = fVar34 * fVar33;
        *(float *)(lVar31 + 0x14) = fVar34 * fVar3;
        *(float *)(lVar31 + 0x18) = fVar34 * fVar35;
        *(float *)(lVar31 + 0x1c) = fVar34 * fVar4;
        return 1;
      case 0x56:
code_r0x021cac0c:
        *(float *)(param_1 + 0xc5) = *param_3;
        return 1;
      case 0x57:
code_r0x021cac18:
        *(float *)(param_1 + 0xc6) = *param_3;
        return 1;
      case 0x58:
code_r0x021cac24:
        *(float *)((long)param_1 + 0x62c) = *param_3;
        return 1;
      case 0x59:
code_r0x021cac30:
        *(float *)((long)param_1 + 0x634) = *param_3;
        return 1;
      case 0x5a:
code_r0x021cac3c:
        *(float *)(param_1 + 199) = *param_3;
        return 1;
      case 0x5b:
code_r0x021cac48:
        *(float *)(param_1 + 200) = *param_3;
        return 1;
      case 0x5c:
code_r0x021cac54:
        *(float *)((long)param_1 + 0x63c) = *param_3;
        return 1;
      case 0x5d:
code_r0x021cac60:
        *(float *)(param_1 + 0xc4) = *param_3;
        return 1;
      case 0x5e:
code_r0x021cac6c:
        *(float *)((long)param_1 + 0x624) = *param_3;
        return 1;
      default:
        goto code_r0x011c80f0;
      case 0x62:
code_r0x021cac78:
        if (*param_3 == 0.0) {
          uVar6 = (undefined6)param_1[0x6f];
          if (((uint)uVar6 >> 0xd & 1) == 0) {
            return 1;
          }
          uVar17 = (ulong)*(ushort *)((long)param_1 + 0x462);
          if (uVar17 != 0) {
            lVar31 = 0;
            do {
              uVar17 = uVar17 - 1;
              plVar14 = param_1 + 0x8e;
              if ((long *)param_1[0x8b] != (long *)0x0) {
                plVar14 = (long *)param_1[0x8b];
              }
              *(undefined1 *)((long)plVar14 + lVar31 + 0x1a) = 0;
              lVar31 = lVar31 + 0x20;
            } while (uVar17 != 0);
            uVar6 = *(undefined6 *)(param_1 + 0x6f);
          }
          *(short *)((long)param_1 + 0x37c) = (short)((uint6)uVar6 >> 0x20);
          *(uint *)(param_1 + 0x6f) = (uint)uVar6 & 0xffffdfff;
          return 1;
        }
        uVar16 = (int)*param_3 - 1;
        if (((*(uint *)(param_1 + 0x6f) >> 0xd & 1) != 0) &&
           (uVar16 == *(byte *)((long)param_1 + 900))) {
          return 1;
        }
        *(undefined2 *)((long)param_1 + 0x37c) = *(undefined2 *)((long)param_1 + 0x37c);
        *(uint *)(param_1 + 0x6f) = *(uint *)(param_1 + 0x6f) | 0x2000;
        uVar17 = (ulong)*(ushort *)((long)param_1 + 0x462);
        *(char *)((long)param_1 + 900) = (char)uVar16;
        if (uVar17 == 0) {
          return 1;
        }
        lVar31 = 0;
        do {
          uVar17 = uVar17 - 1;
          plVar14 = param_1 + 0x8e;
          if ((long *)param_1[0x8b] != (long *)0x0) {
            plVar14 = (long *)param_1[0x8b];
          }
          *(undefined1 *)((long)plVar14 + lVar31 + 0x1a) = 0;
          lVar31 = lVar31 + 0x20;
        } while (uVar17 != 0);
        return 1;
      case 100:
code_r0x021cacf4:
        *PTR__ZN4Aska9AofObject28m_nSpecialShadowAdapterLimitE_02cbb5f0 = SUB41(*param_3,0);
        return 1;
      case 0x65:
code_r0x021cad08:
        *(char *)(param_1 + 0x70) = SUB41(*param_3,0);
        return 1;
      case 0x66:
code_r0x021cad14:
        *(float *)(param_1 + 0x9e) = *param_3;
        return 1;
      case 0x67:
code_r0x021cad20:
        bVar22 = *(byte *)param_3;
        if ((uint)(bVar22 != 0) == ((uint)((uint6)(int6)param_1[0x6f] >> 0x13) & 1)) {
          return 1;
        }
        *(undefined2 *)((long)param_1 + 0x37c) = *(undefined2 *)((long)param_1 + 0x37c);
        *(uint *)(param_1 + 0x6f) = (uint)(int6)param_1[0x6f] & 0xfff7ffff | (uint)bVar22 << 0x13;
        lVar31 = param_1[0x7b];
        if (lVar31 == 0) {
          return 1;
        }
        lVar27 = *(long *)(lVar31 + 0x138);
        if (lVar31 + 0x128 == lVar27) {
          return 1;
        }
        do {
          Aska::RenderPass::InvalidateShaders()(*(undefined8 *)(lVar27 + 0x18));
          Aska::RenderPassManager::InvalidateShaders(bool)(lVar27,0);
          lVar27 = *(long *)(lVar27 + 0x10);
        } while (lVar31 + 0x128 != lVar27);
        return 1;
      case 0x6a:
code_r0x021cad9c:
        *(uint *)(param_1 + 0x6f) = *(uint *)(param_1 + 0x6f) | 0x800000;
        return 1;
      case 0x6f:
code_r0x021cadac:
        *(char *)(param_1 + 0x71) = SUB41(*param_3,0);
        return 1;
      case 0x72:
code_r0x021cadb8:
        uVar16 = *(uint *)(param_1 + 0x6f);
        if ((uVar16 >> 0xb & 1) == (uint)*(byte *)param_3) {
          return 1;
        }
        puVar30 = (uint *)(param_1 + 0x6f);
        uVar6 = CONCAT24(*(undefined2 *)((long)param_1 + 0x37c),uVar16);
        if (*(byte *)param_3 == 0) {
          if ((uVar16 >> 0xb & 1) == 0) {
            return 1;
          }
          uVar17 = (ulong)*(ushort *)((long)param_1 + 0x462);
          if (uVar17 != 0) {
            lVar31 = 0;
            do {
              uVar17 = uVar17 - 1;
              plVar14 = param_1 + 0x8e;
              if ((long *)param_1[0x8b] != (long *)0x0) {
                plVar14 = (long *)param_1[0x8b];
              }
              *(undefined1 *)((long)plVar14 + lVar31 + 0x1a) = 0;
              lVar31 = lVar31 + 0x20;
            } while (uVar17 != 0);
            uVar6 = *(undefined6 *)puVar30;
          }
          *(short *)((long)param_1 + 0x37c) = (short)((uint6)uVar6 >> 0x20);
          *puVar30 = (uint)uVar6 & 0xfffff7ff;
          return 1;
        }
        if ((uVar16 >> 0xb & 1) != 0) {
          return 1;
        }
        *(undefined2 *)((long)param_1 + 0x37c) = *(undefined2 *)((long)param_1 + 0x37c);
        *puVar30 = uVar16 | 0x800;
        uVar17 = (ulong)*(ushort *)((long)param_1 + 0x462);
        if (uVar17 == 0) {
          return 1;
        }
        lVar31 = 0;
        do {
          uVar17 = uVar17 - 1;
          plVar14 = param_1 + 0x8e;
          if ((long *)param_1[0x8b] != (long *)0x0) {
            plVar14 = (long *)param_1[0x8b];
          }
          *(undefined1 *)((long)plVar14 + lVar31 + 0x1a) = 0;
          lVar31 = lVar31 + 0x20;
        } while (uVar17 != 0);
        return 1;
      case 0x73:
code_r0x021cae34:
        fVar33 = *param_3;
        if (((*(uint *)(param_1 + 0x6f) >> 0xb & 1) != 0) &&
           (fVar33 == (float)(uint)*(byte *)((long)param_1 + 0x389))) {
          return 1;
        }
        *(undefined2 *)((long)param_1 + 0x37c) = *(undefined2 *)((long)param_1 + 0x37c);
        *(uint *)(param_1 + 0x6f) = *(uint *)(param_1 + 0x6f) | 0x800;
        uVar17 = (ulong)*(ushort *)((long)param_1 + 0x462);
        *(char *)((long)param_1 + 0x389) = SUB41(fVar33,0);
        if (uVar17 == 0) {
          return 1;
        }
        lVar31 = 0;
        do {
          uVar17 = uVar17 - 1;
          plVar14 = param_1 + 0x8e;
          if ((long *)param_1[0x8b] != (long *)0x0) {
            plVar14 = (long *)param_1[0x8b];
          }
          *(undefined1 *)((long)plVar14 + lVar31 + 0x1a) = 0;
          lVar31 = lVar31 + 0x20;
        } while (uVar17 != 0);
        return 1;
      case 0x74:
code_r0x021caea8:
        fVar33 = *param_3;
        if (((*(uint *)(param_1 + 0x6f) >> 0xb & 1) != 0) &&
           (fVar33 == (float)(uint)*(byte *)((long)param_1 + 0x38a))) {
          return 1;
        }
        *(undefined2 *)((long)param_1 + 0x37c) = *(undefined2 *)((long)param_1 + 0x37c);
        *(uint *)(param_1 + 0x6f) = *(uint *)(param_1 + 0x6f) | 0x800;
        uVar17 = (ulong)*(ushort *)((long)param_1 + 0x462);
        *(char *)((long)param_1 + 0x38a) = SUB41(fVar33,0);
        if (uVar17 == 0) {
          return 1;
        }
        lVar31 = 0;
        do {
          uVar17 = uVar17 - 1;
          plVar14 = param_1 + 0x8e;
          if ((long *)param_1[0x8b] != (long *)0x0) {
            plVar14 = (long *)param_1[0x8b];
          }
          *(undefined1 *)((long)plVar14 + lVar31 + 0x1a) = 0;
          lVar31 = lVar31 + 0x20;
        } while (uVar17 != 0);
        return 1;
      case 0x75:
code_r0x021caf1c:
        fVar33 = *param_3;
        if (((*(uint *)(param_1 + 0x6f) >> 0xb & 1) != 0) &&
           (fVar33 == (float)(uint)*(byte *)((long)param_1 + 0x38b))) {
          return 1;
        }
        *(undefined2 *)((long)param_1 + 0x37c) = *(undefined2 *)((long)param_1 + 0x37c);
        *(uint *)(param_1 + 0x6f) = *(uint *)(param_1 + 0x6f) | 0x800;
        uVar17 = (ulong)*(ushort *)((long)param_1 + 0x462);
        *(char *)((long)param_1 + 0x38b) = SUB41(fVar33,0);
        if (uVar17 == 0) {
          return 1;
        }
        lVar31 = 0;
        do {
          uVar17 = uVar17 - 1;
          plVar14 = param_1 + 0x8e;
          if ((long *)param_1[0x8b] != (long *)0x0) {
            plVar14 = (long *)param_1[0x8b];
          }
          *(undefined1 *)((long)plVar14 + lVar31 + 0x1a) = 0;
          lVar31 = lVar31 + 0x20;
        } while (uVar17 != 0);
        return 1;
      case 0x76:
code_r0x021caf90:
        fVar33 = *param_3;
        if (((*(uint *)(param_1 + 0x6f) >> 0xb & 1) != 0) &&
           (fVar33 == (float)(uint)*(byte *)((long)param_1 + 0x38c))) {
          return 1;
        }
        *(undefined2 *)((long)param_1 + 0x37c) = *(undefined2 *)((long)param_1 + 0x37c);
        *(uint *)(param_1 + 0x6f) = *(uint *)(param_1 + 0x6f) | 0x800;
        uVar17 = (ulong)*(ushort *)((long)param_1 + 0x462);
        *(char *)((long)param_1 + 0x38c) = SUB41(fVar33,0);
        if (uVar17 == 0) {
          return 1;
        }
        lVar31 = 0;
        do {
          uVar17 = uVar17 - 1;
          plVar14 = param_1 + 0x8e;
          if ((long *)param_1[0x8b] != (long *)0x0) {
            plVar14 = (long *)param_1[0x8b];
          }
          *(undefined1 *)((long)plVar14 + lVar31 + 0x1a) = 0;
          lVar31 = lVar31 + 0x20;
        } while (uVar17 != 0);
        return 1;
      case 0x77:
code_r0x021cb004:
        fVar33 = *param_3;
        if (((*(uint *)(param_1 + 0x6f) >> 0xb & 1) != 0) &&
           (fVar33 == (float)(uint)*(byte *)((long)param_1 + 0x38d))) {
          return 1;
        }
        *(undefined2 *)((long)param_1 + 0x37c) = *(undefined2 *)((long)param_1 + 0x37c);
        *(uint *)(param_1 + 0x6f) = *(uint *)(param_1 + 0x6f) | 0x800;
        uVar17 = (ulong)*(ushort *)((long)param_1 + 0x462);
        *(char *)((long)param_1 + 0x38d) = SUB41(fVar33,0);
        if (uVar17 == 0) {
          return 1;
        }
        lVar31 = 0;
        do {
          uVar17 = uVar17 - 1;
          plVar14 = param_1 + 0x8e;
          if ((long *)param_1[0x8b] != (long *)0x0) {
            plVar14 = (long *)param_1[0x8b];
          }
          *(undefined1 *)((long)plVar14 + lVar31 + 0x1a) = 0;
          lVar31 = lVar31 + 0x20;
        } while (uVar17 != 0);
        return 1;
      case 0x79:
code_r0x021cb078:
        bVar22 = *(byte *)param_3;
        *(int *)(param_1 + 0x6f) = (int)param_1[0x6f];
        *(ushort *)((long)param_1 + 0x37c) =
             *(ushort *)((long)param_1 + 0x37c) & 0xfffb | (ushort)(((ulong)bVar22 << 0x22) >> 0x20)
        ;
        return 1;
      case 0x7c:
code_r0x021cb0a0:
        *(char *)((long)param_1 + 0x381) = SUB41(*param_3,0);
        return 1;
      case 0x82:
code_r0x021cb0ac:
        *(ushort *)((long)param_1 + 0x1b5) =
             *(ushort *)((long)param_1 + 0x1b5) & 0xffbf | (*(byte *)param_3 & 3) << 6;
        return 1;
      }
      (*pcVar21)(param_1,*(undefined1 *)param_3);
      return 1;
    }
    switch(uVar26 & 0xffff) {
    case 0x44:
      goto code_r0x021ca438;
    case 0x45:
    case 0x46:
    case 0x4d:
    case 0x4e:
    case 0x61:
    case 0x6e:
    case 0x71:
    case 0x78:
    case 0x7b:
      return 1;
    case 0x47:
      goto code_r0x021caa40;
    case 0x48:
      goto code_r0x021caa4c;
    case 0x49:
      goto code_r0x021caa64;
    case 0x4a:
      goto code_r0x021caaec;
    case 0x4b:
      goto code_r0x021cab74;
    case 0x4c:
      goto code_r0x021cabfc;
    default:
      goto code_r0x011c80f0;
    case 0x56:
      goto code_r0x021cac0c;
    case 0x57:
      goto code_r0x021cac18;
    case 0x58:
      goto code_r0x021cac24;
    case 0x59:
      goto code_r0x021cac30;
    case 0x5a:
      goto code_r0x021cac3c;
    case 0x5b:
      goto code_r0x021cac48;
    case 0x5c:
      goto code_r0x021cac54;
    case 0x5d:
      goto code_r0x021cac60;
    case 0x5e:
      goto code_r0x021cac6c;
    case 0x62:
      goto code_r0x021cac78;
    case 100:
      goto code_r0x021cacf4;
    case 0x65:
      goto code_r0x021cad08;
    case 0x66:
      goto code_r0x021cad14;
    case 0x67:
      goto code_r0x021cad20;
    case 0x6a:
      goto code_r0x021cad9c;
    case 0x6f:
      goto code_r0x021cadac;
    case 0x72:
      goto code_r0x021cadb8;
    case 0x73:
      goto code_r0x021cae34;
    case 0x74:
      goto code_r0x021caea8;
    case 0x75:
      goto code_r0x021caf1c;
    case 0x76:
      goto code_r0x021caf90;
    case 0x77:
      goto code_r0x021cb004;
    case 0x79:
      goto code_r0x021cb078;
    case 0x7c:
      goto code_r0x021cb0a0;
    case 0x82:
      goto code_r0x021cb0ac;
    }
  case 1:
    lVar31 = param_1[0x7b];
    iVar12 = *(int *)(*(long *)(lVar31 + 0xb0) + 0xa0);
    if (iVar12 == 0) {
      return 1;
    }
    lVar27 = *(long *)(lVar31 + 0xb0) + (long)iVar12;
    uVar26 = *(uint *)(lVar27 + 0xa0);
    lVar27 = lVar27 + 0x90;
    uVar5 = 0;
    if (uVar26 != 0) {
      uVar5 = uVar28 / uVar26;
    }
    lVar27 = lVar27 + (ulong)*(uint *)(lVar27 + (ulong)(uVar28 - uVar5 * uVar26) * 4 + 0x20);
    uVar23 = *(ushort *)(lVar27 + 0x36);
    if (uVar23 == 0) {
      return 1;
    }
    lVar25 = lVar31 + 0xe8;
    iVar12 = 0;
    puVar30 = (uint *)(lVar27 + 0x38);
    lVar19 = lVar31 + 0x128;
    do {
      uVar26 = *puVar30;
      if ((uVar26 & 0xff) != uVar16) goto code_r0x021ca218;
      uVar28 = uVar26 >> 0x1c;
      uVar29 = (ulong)(uVar26 >> 8 & 0x7f);
      uVar5 = uVar26 >> 0x15 & 0x7f;
      uVar17 = (ulong)uVar5;
      if (uVar28 != 2) {
        if (uVar28 == 1) {
          switch(uVar26 & 0xff) {
          case 1:
            lVar27 = 0;
            if (*(long *)(lVar31 + 0x100) != 0) {
              lVar27 = *(long *)(lVar31 + 0x100) + uVar29 * 0x2a0 + 0x10;
            }
            *(char *)(lVar27 + 0x231) = (char)(int)(*param_3 * _UNK_028014f8);
            uVar17 = (ulong)*(ushort *)((long)param_1 + 0x462);
            if (uVar17 != 0) {
              lVar27 = 0;
              do {
                uVar17 = uVar17 - 1;
                plVar14 = param_1 + 0x8e;
                if ((long *)param_1[0x8b] != (long *)0x0) {
                  plVar14 = (long *)param_1[0x8b];
                }
                *(undefined1 *)((long)plVar14 + lVar27 + 0x1a) = 0;
                lVar27 = lVar27 + 0x20;
              } while (uVar17 != 0);
            }
            lVar31 = *(long *)(lVar31 + 0x138);
            if (lVar19 != lVar31) {
              do {
                lVar27 = Aska::RenderPassManager::GetPass(int, int)(lVar31,2,0);
                if (lVar27 != 0) {
                  *(ushort *)(lVar27 + 0x2f) = *(ushort *)(lVar27 + 0x2f) & 0xffbf;
                }
                lVar31 = *(long *)(lVar31 + 0x10);
              } while (lVar19 != lVar31);
              return 1;
            }
            return 1;
          case 2:
            lVar27 = 0;
            if (*(long *)(lVar31 + 0x100) != 0) {
              lVar27 = *(long *)(lVar31 + 0x100) + uVar29 * 0x2a0 + 0x10;
            }
            *(char *)(lVar27 + 0x232) = SUB41(*param_3,0);
            uVar17 = (ulong)*(ushort *)((long)param_1 + 0x462);
            if (uVar17 != 0) {
              lVar31 = 0;
              do {
                uVar17 = uVar17 - 1;
                plVar14 = param_1 + 0x8e;
                if ((long *)param_1[0x8b] != (long *)0x0) {
                  plVar14 = (long *)param_1[0x8b];
                }
                *(undefined1 *)((long)plVar14 + lVar31 + 0x1a) = 0;
                lVar31 = lVar31 + 0x20;
              } while (uVar17 != 0);
              return 1;
            }
            return 1;
          case 3:
            lVar27 = 0;
            if (*(long *)(lVar31 + 0x100) != 0) {
              lVar27 = *(long *)(lVar31 + 0x100) + uVar29 * 0x2a0 + 0x10;
            }
            *(ushort *)(lVar27 + 0x245) =
                 *(ushort *)(lVar27 + 0x245) & 0xfff7 | (*(byte *)param_3 & 0x1f) << 3;
            if ((*(uint *)(param_1 + 0x33) & 0x400010) == 0x10) {
              if ((*(char *)param_3 == '\0') &&
                 (uVar17 = Aska::MaterialList::IsPunchthrough()(lVar25), (uVar17 & 1) == 0)) {
                uVar16 = *(uint *)(param_1 + 0x36) | 0x10;
              }
              else {
                uVar16 = *(uint *)(param_1 + 0x36) & 0xffffffef;
              }
              *(uint *)(param_1 + 0x36) = uVar16;
            }
            lVar31 = *(long *)(lVar31 + 0x138);
            if (lVar19 != lVar31) {
              do {
                Aska::RenderPass::InvalidateShaders()(*(undefined8 *)(lVar31 + 0x18));
                Aska::RenderPassManager::InvalidateShaders(bool)(lVar31,0);
                lVar31 = *(long *)(lVar31 + 0x10);
              } while (lVar19 != lVar31);
              return 1;
            }
            return 1;
          case 4:
            lVar27 = 0;
            if (*(long *)(lVar31 + 0x100) != 0) {
              lVar27 = *(long *)(lVar31 + 0x100) + uVar29 * 0x2a0 + 0x10;
            }
            *(ushort *)(lVar27 + 0x245) =
                 *(ushort *)(lVar27 + 0x245) & 0xfffb | (*(byte *)param_3 & 0x3f) << 2;
            Aska::MaterialList::UpdatePunchthroughZprepass()(lVar25);
            if (*(char *)param_3 != '\0') {
              for (lVar27 = *(long *)(lVar31 + 0x138); lVar19 != lVar27;
                  lVar27 = *(long *)(lVar27 + 0x10)) {
                Aska::RenderPassManager::InvalidateRenderState()(lVar27);
                Aska::RenderPassManager::InvalidateCommandBufferManager()(lVar27);
              }
              uVar17 = (ulong)*(ushort *)((long)param_1 + 0x462);
              if (uVar17 != 0) {
                lVar27 = 0;
                do {
                  uVar17 = uVar17 - 1;
                  plVar14 = param_1 + 0x8e;
                  if ((long *)param_1[0x8b] != (long *)0x0) {
                    plVar14 = (long *)param_1[0x8b];
                  }
                  *(undefined1 *)((long)plVar14 + lVar27 + 0x1a) = 0;
                  lVar27 = lVar27 + 0x20;
                } while (uVar17 != 0);
              }
            }
            if ((*(uint *)(param_1 + 0x33) & 0x400010) == 0x10) {
              if ((*(char *)param_3 == '\0') &&
                 (uVar17 = Aska::MaterialList::IsPunchthrough()(lVar25), (uVar17 & 1) == 0)) {
                uVar16 = *(uint *)(param_1 + 0x36) | 0x10;
              }
              else {
                uVar16 = *(uint *)(param_1 + 0x36) & 0xffffffef;
              }
              *(uint *)(param_1 + 0x36) = uVar16;
            }
            lVar31 = *(long *)(lVar31 + 0x138);
            if (lVar19 != lVar31) {
              do {
                Aska::RenderPass::InvalidateShaders()(*(undefined8 *)(lVar31 + 0x18));
                Aska::RenderPassManager::InvalidateShaders(bool)(lVar31,0);
                lVar31 = *(long *)(lVar31 + 0x10);
              } while (lVar19 != lVar31);
              return 1;
            }
            return 1;
          case 5:
            lVar27 = 0;
            if (*(long *)(lVar31 + 0x100) != 0) {
              lVar27 = *(long *)(lVar31 + 0x100) + uVar29 * 0x2a0 + 0x10;
            }
            *(char *)(lVar27 + 0x233) = SUB41(*param_3,0);
            lVar31 = *(long *)(lVar31 + 0x138);
            if (lVar19 != lVar31) {
              do {
                lVar27 = Aska::RenderPassManager::GetPass(int, int)(lVar31,2,0);
                if (lVar27 != 0) {
                  *(ushort *)(lVar27 + 0x2f) = *(ushort *)(lVar27 + 0x2f) & 0xffbf;
                }
                lVar31 = *(long *)(lVar31 + 0x10);
              } while (lVar19 != lVar31);
              return 1;
            }
            return 1;
          case 6:
            lVar27 = 0;
            if (*(long *)(lVar31 + 0x100) != 0) {
              lVar27 = *(long *)(lVar31 + 0x100) + uVar29 * 0x2a0 + 0x10;
            }
            *(ushort *)(lVar27 + 0x245) =
                 *(ushort *)(lVar27 + 0x245) & 0xfffd | (*(byte *)param_3 & 0x7f) << 1;
            if (*(char *)param_3 != '\0') {
              *(ushort *)(lVar31 + 0x108) = *(ushort *)(lVar31 + 0x108) | 0x80;
            }
            lVar25 = *(long *)(lVar31 + 0x138);
            lVar27 = lVar19;
            if (lVar19 != lVar25) {
              do {
                lVar27 = Aska::RenderPassManager::GetPass(int, int)(lVar25,2,0);
                if (lVar27 != 0) {
                  *(ushort *)(lVar27 + 0x2f) = *(ushort *)(lVar27 + 0x2f) & 0xffbf;
                }
                lVar25 = *(long *)(lVar25 + 0x10);
              } while (lVar19 != lVar25);
              lVar27 = *(long *)(lVar31 + 0x138);
            }
            if (lVar19 != lVar27) {
              do {
                Aska::RenderPass::InvalidateShaders()(*(undefined8 *)(lVar27 + 0x18));
                Aska::RenderPassManager::InvalidateShaders(bool)(lVar27,0);
                lVar27 = *(long *)(lVar27 + 0x10);
              } while (lVar19 != lVar27);
              return 1;
            }
            return 1;
          case 7:
            lVar27 = 0;
            if (*(long *)(lVar31 + 0x100) != 0) {
              lVar27 = *(long *)(lVar31 + 0x100) + uVar29 * 0x2a0 + 0x10;
            }
            *(ushort *)(lVar27 + 0x245) =
                 *(ushort *)(lVar27 + 0x245) & 0xffef | (*(byte *)param_3 & 0xf) << 4;
            if (param_1[0x73] != 0) {
              Aska::RenderPassManager::InvalidateDynamicShaderModifierCache()();
              return 1;
            }
            return 1;
          case 8:
            lVar27 = 0;
            if (*(long *)(lVar31 + 0x100) != 0) {
              lVar27 = *(long *)(lVar31 + 0x100) + uVar29 * 0x2a0 + 0x10;
            }
            *(ushort *)(lVar27 + 0x245) =
                 *(ushort *)(lVar27 + 0x245) & 0xffdf | (*(byte *)param_3 & 7) << 5;
            lVar31 = *(long *)(lVar31 + 0x138);
            if (lVar19 != lVar31) {
              do {
                Aska::RenderPass::InvalidateShaders()(*(undefined8 *)(lVar31 + 0x18));
                Aska::RenderPassManager::InvalidateShaders(bool)(lVar31,0);
                lVar31 = *(long *)(lVar31 + 0x10);
              } while (lVar19 != lVar31);
              return 1;
            }
            return 1;
          case 10:
            lVar27 = 0;
            if (*(long *)(lVar31 + 0x100) != 0) {
              lVar27 = *(long *)(lVar31 + 0x100) + uVar29 * 0x2a0 + 0x10;
            }
            *(ushort *)(lVar27 + 0x245) =
                 *(ushort *)(lVar27 + 0x245) & 0xdfff | (ushort)*(byte *)param_3 << 0xd;
            (**(code **)(*param_1 + 0xb0))(param_1);
            uVar17 = (ulong)*(ushort *)((long)param_1 + 0x462);
            if (uVar17 != 0) {
              lVar27 = 0;
              do {
                uVar17 = uVar17 - 1;
                plVar14 = param_1 + 0x8e;
                if ((long *)param_1[0x8b] != (long *)0x0) {
                  plVar14 = (long *)param_1[0x8b];
                }
                *(undefined1 *)((long)plVar14 + lVar27 + 0x1a) = 0;
                lVar27 = lVar27 + 0x20;
              } while (uVar17 != 0);
            }
            lVar25 = *(long *)(lVar31 + 0x138);
            lVar27 = lVar19;
            if (lVar19 != lVar25) {
              do {
                Aska::RenderPassManager::InvalidateRenderState()(lVar25);
                Aska::RenderPassManager::InvalidateCommandBufferManager()(lVar25);
                lVar25 = *(long *)(lVar25 + 0x10);
              } while (lVar19 != lVar25);
              lVar27 = *(long *)(lVar31 + 0x138);
            }
            if (lVar19 != lVar27) {
              do {
                Aska::RenderPass::InvalidateShaders()(*(undefined8 *)(lVar27 + 0x18));
                Aska::RenderPassManager::InvalidateShaders(bool)(lVar27,0);
                lVar27 = *(long *)(lVar27 + 0x10);
              } while (lVar19 != lVar27);
              return 1;
            }
            return 1;
          }
          goto code_r0x021ca218;
        }
        if (uVar28 != 0) goto code_r0x021ca218;
        uVar26 = uVar26 >> 0xf & 0x3f;
        lVar32 = *(long *)(lVar31 + 0x150) + uVar29 * 0x1b8;
        pfVar15 = param_3;
        switch(uVar5) {
        case 2:
          bVar22 = 1;
          uVar17 = Aska::ShaderConstantManager::SetShaderConstantFUC(int, int, Aska::Vector const*, int)(lVar32,uVar5,uVar26,param_3,1);
          if ((uVar17 & 1) == 0) goto code_r0x021ca218;
          bVar8 = false;
          goto code_r0x021ca150;
        default:
          uVar11 = 1;
          break;
        case 5:
        case 6:
        case 0x14:
        case 0x1d:
        case 0x1e:
          iVar9 = Aska::ShaderConstantManager::GetConstImmState(int, int) const(lVar32,uVar5,uVar26);
          uVar17 = Aska::ShaderConstantManager::SetShaderConstantFUC(int, int, Aska::Vector const*, int)(lVar32,uVar5,uVar26,param_3,1);
          iVar10 = Aska::ShaderConstantManager::GetConstImmState(int, int) const(lVar32,uVar5,uVar26);
          if ((uVar17 & 1) == 0) goto code_r0x021ca218;
          bVar8 = iVar9 != iVar10;
          Aska::AofHandler::UpdateForProceduralTexture()(param_1[0x7b]);
          goto code_r0x021ca14c;
        case 8:
        case 0xb:
          uVar11 = Aska::AhslConst::AofConvertToNativeConstant(int, Aska::Vector const*, Aska::Vector*)(uVar5,param_3,afStack_90);
          pfVar15 = afStack_90;
          break;
        case 0xc:
        case 0xe:
          Aska::AhslConst::AofConvertToNativeConstant(int, Aska::Vector const*, Aska::Vector*)(uVar5,param_3,afStack_90);
          uVar17 = Aska::ShaderConstantManager::SetShaderConstantFUC(int, int, Aska::Vector const*, int)(lVar32,uVar5,uVar26,param_3,2);
          uVar11 = 2;
          goto code_r0x021ca0fc;
        case 0x15:
          uVar11 = Aska::AhslConst::AofConvertToNativeConstant(int, Aska::Vector const*, Aska::Vector*)(uVar5,param_3,afStack_90);
          uVar17 = Aska::ShaderConstantManager::SetShaderConstantFUC(int, int, Aska::Vector const*, int)(lVar32,uVar5,uVar26,param_3,1);
code_r0x021ca0fc:
          uVar18 = Aska::ShaderConstantManager::SetShaderConstantFUC(int, int, Aska::Vector const*, int)(lVar32,uVar5 + 1,uVar26,afStack_90,uVar11);
          bVar8 = false;
          if ((uVar17 & 1) != 0) {
            bVar22 = 0;
            goto code_r0x021ca150;
          }
          bVar22 = 0;
          if ((uVar18 & 1) != 0) goto code_r0x021ca150;
          goto code_r0x021ca218;
        case 0x1f:
          uVar11 = 4;
        }
        uVar17 = Aska::ShaderConstantManager::SetShaderConstantFUC(int, int, Aska::Vector const*, int)(lVar32,uVar5,uVar26,pfVar15,uVar11);
        if ((uVar17 & 1) != 0) {
          bVar8 = false;
code_r0x021ca14c:
          bVar22 = 0;
code_r0x021ca150:
          puVar2 = (ushort *)(*(long *)(lVar31 + 0x100) + uVar29 * 0x2a0 + 0x255);
          *puVar2 = *puVar2 | 1;
          uVar24 = *(ushort *)(lVar31 + 0x108);
          if ((uVar24 >> 2 & 1) == 0) {
            *(ushort *)(lVar31 + 0x177) = *(ushort *)(lVar31 + 0x177) | 1;
            if (*(long *)(lVar31 + 0x188) != 0) {
              bVar7 = false;
              lVar32 = *(long *)(lVar31 + 0x188);
code_r0x021ca194:
              do {
                do {
                  lVar20 = lVar32;
                  if (!bVar7) {
                    bVar7 = false;
                    *(ushort *)(lVar20 + 0x2f) = *(ushort *)(lVar20 + 0x2f) | 1;
                    lVar32 = *(long *)(lVar20 + 0x40);
                    if (*(long *)(lVar20 + 0x40) != 0) goto code_r0x021ca194;
                  }
                  bVar7 = false;
                  lVar32 = *(long *)(lVar20 + 0x48);
                } while (*(long *)(lVar20 + 0x48) != 0);
                bVar7 = true;
                lVar32 = *(long *)(lVar20 + 0x38);
              } while (*(long *)(lVar20 + 0x38) != lVar31 + 0x148);
              uVar24 = *(ushort *)(lVar31 + 0x108);
            }
            *(ushort *)(lVar31 + 0x108) = uVar24 | 4;
          }
          if ((bool)(bVar8 | bVar22)) {
            for (lVar32 = *(long *)(lVar31 + 0x138); lVar19 != lVar32;
                lVar32 = *(long *)(lVar32 + 0x10)) {
              Aska::RenderPass::InvalidateShaders()(*(undefined8 *)(lVar32 + 0x18));
              Aska::RenderPassManager::InvalidateShaders(bool)(lVar32,0);
            }
          }
        }
        goto code_r0x021ca218;
      }
      lVar20 = *(long *)(lVar31 + 0x100);
      lVar32 = 0;
      if (lVar20 != 0) {
        lVar32 = lVar20 + uVar29 * 0x2a0 + 0x10;
      }
      switch(uVar26 & 0xff) {
      case 0xb:
        lVar32 = lVar32 + uVar17 * 0x20;
        plVar14 = (long *)(lVar32 + 0x20);
        if (*plVar14 != *(long *)param_3) {
          *plVar14 = *(long *)param_3;
          *(undefined8 *)(lVar32 + 0x30) = 0;
        }
        break;
      case 0xc:
        lVar32 = lVar32 + uVar17 * 0x20;
        bVar22 = *(byte *)(lVar32 + 0x2e) & 0x80;
        *(byte *)(lVar32 + 0x2e) = bVar22;
        bVar22 = *(byte *)param_3 | bVar22;
        goto code_r0x021c9fe4;
      case 0xd:
        *(undefined1 *)(lVar32 + uVar17 * 0x20 + 0x29) = *(undefined1 *)param_3;
        break;
      case 0xe:
        *(undefined1 *)(lVar32 + uVar17 * 0x20 + 0x28) = *(undefined1 *)param_3;
        break;
      case 0xf:
        lVar32 = lVar32 + uVar17 * 0x20;
        *(ushort *)(lVar32 + 0x2c) =
             *(ushort *)(lVar32 + 0x2c) & 0x3f | (ushort)((int)(*param_3 * 32.0) << 6);
        break;
      case 0x10:
        lVar32 = lVar32 + uVar17 * 0x20;
        bVar22 = *(byte *)(lVar32 + 0x2e);
        *(byte *)(lVar32 + 0x2e) = bVar22 & 0x7f;
        bVar22 = bVar22 & 0x7f | *(char *)param_3 << 7;
code_r0x021c9fe4:
        *(byte *)(lVar32 + 0x2e) = bVar22;
        break;
      case 0x11:
        lVar32 = lVar32 + uVar17 * 0x20;
        *(ushort *)(lVar32 + 0x2c) = *(ushort *)(lVar32 + 0x2c) & 0xffc0 | *(byte *)param_3 & 0x3f;
        break;
      case 0x14:
        lVar32 = param_1[0xd4];
        if (((lVar32 != 0) && (*(long *)(lVar32 + 0x50) != 0)) &&
           (*(long *)(*(long *)(lVar32 + 0x50) + 8) != 0)) {
          lVar20 = *(long *)(lVar20 + uVar29 * 0x2a0);
          iVar9 = *(int *)(lVar20 + 0x38);
          if (iVar9 != 0) {
            lVar20 = iVar9 + lVar20;
            uVar17 = (ulong)*(ushort *)(lVar20 + uVar17 * 2);
            if ((uVar17 != 0) && (lVar20 = lVar20 + uVar17, lVar20 != 0)) {
              Aska::AarTextureUpdater::UpdateTime(Aska::AUID const*, Aska::AofObject*, char const*, float)(*param_3,lVar32,lVar20,param_1,lVar27 + 0x14);
            }
          }
        }
      }
      for (lVar32 = *(long *)(lVar31 + 0x138); lVar19 != lVar32; lVar32 = *(long *)(lVar32 + 0x10))
      {
        Aska::RenderPassManager::InvalidateRenderState()(lVar32);
        Aska::RenderPassManager::InvalidateCommandBufferManager()(lVar32);
      }
code_r0x021ca218:
      iVar12 = iVar12 + 1;
      puVar30 = puVar30 + 1;
      if ((int)(uint)uVar23 <= iVar12) {
        return 1;
      }
    } while( true );
  case 2:
    plVar14 = (long *)Aska::ModifierManager::FindModifier(Aska::AofObject const*, int)(*(undefined8 *)
                                       PTR__ZN4Aska6Global18m_pModifierManagerE_02cbb990,param_1,
                                      uVar29);
    if (plVar14 == (long *)0x0) {
      return 0;
    }
    break;
  case 3:
    goto code_r0x011c80f0;
  case 4:
    plVar14 = (long *)Aska::MeshGeneratorManager::FindMeshGenerator(Aska::AofObject const*)(*(undefined8 *)
                                       PTR__ZN4Aska6Global23m_pMeshGeneratorManagerE_02cc2bc0,
                                      param_1);
    if (plVar14 == (long *)0x0) {
      return 0;
    }
  }
                    /* WARNING: Could not recover jumptable at 0x021c9a84. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  uVar13 = (**(code **)(*plVar14 + 0x30))(plVar14,param_2,param_3);
  return uVar13;
}

// ==== Aska::AofObject::GetRandomVertexPosAndNormal(Aska::Vector*, Aska::Vector*) const
// vaddr 0x20cb418 | ghidra 0x21cb418 | size 200 | symbol _ZNK4Aska9AofObject27GetRandomVertexPosAndNormalEPNS_6VectorES2_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK4Aska9AofObject27GetRandomVertexPosAndNormalEPNS_6VectorES2_
               (long param_1,undefined8 param_2,undefined8 param_3)

{
  undefined2 uVar1;
  undefined4 uVar2;
  long lVar4;
  ulong uVar3;
  
  lVar4 = *(long *)(param_1 + 0x3d8);
  if (lVar4 == 0) {
    return;
  }
  if (*(long *)(lVar4 + 0xd0) == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = *(undefined2 *)(*(long *)(lVar4 + 0xb0) + 0x70);
  }
  uVar3 = Aska::Random(unsigned int)(uVar1);
  uVar3 = -(uVar3 >> 0x1f & 1) & 0xfffffff800000000 | (uVar3 & 0xffffffff) << 3;
  uVar2 = Aska::Random(unsigned int)(*(undefined4 *)
                           (*(long *)(*(long *)(*(long *)(*(long *)(param_1 + 0x3d8) + 0xd0) + uVar3
                                               ) + 8) + 0x10));
  lVar4 = *(long *)(*(long *)(*(long *)(param_1 + 0x3d8) + 0xd0) + uVar3) + 0x40;
  uVar3 = Aska::PrimitiveBuffer::GetVertexAsmBit() const(lVar4);
  if ((uVar3 & 0xf0) != 0) {
    (*(code *)PTR__ZNK4Aska15PrimitiveBuffer21GetVertexPosAndNormalEjPNS_6VectorES2__02cb56e0)
              (lVar4,uVar2,param_2,param_3);
    return;
  }
  (*(code *)PTR__ZNK4Aska15PrimitiveBuffer17GetVertexPositionEjPNS_6VectorE_02cad008)
            (lVar4,uVar2,param_2);
  return;
}

// ==== Aska::AofObject::GetVertexPosition(int, Aska::Vector*) const
// vaddr 0x20cb4e0 | ghidra 0x21cb4e0 | size 140 | symbol _ZNK4Aska9AofObject17GetVertexPositionEiPNS_6VectorE | lib libSOA-3.7.0.so | 2026-10-04
uint _ZNK4Aska9AofObject17GetVertexPositionEiPNS_6VectorE(long param_1,ulong param_2)

{
  long lVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  ulong uVar6;
  
  uVar6 = param_2 >> 0x10 & 0xffff;
  uVar5 = (uint)uVar6;
  uVar4 = (uint)param_2 & 0xffff;
  lVar1 = *(long *)(*(long *)(*(long *)(param_1 + 0x3d8) + 0xd0) + uVar6 * 8) + 0x40;
  Aska::PrimitiveBuffer::GetVertexPosition(unsigned int, Aska::Vector*) const(lVar1,uVar4);
  uVar4 = uVar4 + 1;
  iVar2 = Aska::PrimitiveBuffer::GetVertexBufLength() const(lVar1);
  if (iVar2 <= (int)uVar4) {
    uVar5 = uVar5 + 1;
    if (*(long *)(*(long *)(param_1 + 0x3d8) + 0xd0) == 0) {
      uVar3 = 0;
    }
    else {
      uVar3 = (uint)*(ushort *)(*(long *)(*(long *)(param_1 + 0x3d8) + 0xb0) + 0x70);
    }
    uVar4 = 0;
    if (uVar3 <= uVar5) {
      uVar5 = 0;
    }
  }
  return uVar4 & 0xffff | uVar5 << 0x10;
}

// ==== Aska::AofObject::GetVertexPosAndNormal(int, Aska::Vector*, Aska::Vector*) const
// vaddr 0x20cb56c | ghidra 0x21cb56c | size 140 | symbol _ZNK4Aska9AofObject21GetVertexPosAndNormalEiPNS_6VectorES2_ | lib libSOA-3.7.0.so | 2026-10-04
uint _ZNK4Aska9AofObject21GetVertexPosAndNormalEiPNS_6VectorES2_(long param_1,ulong param_2)

{
  long lVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  ulong uVar6;
  
  uVar6 = param_2 >> 0x10 & 0xffff;
  uVar5 = (uint)uVar6;
  uVar4 = (uint)param_2 & 0xffff;
  lVar1 = *(long *)(*(long *)(*(long *)(param_1 + 0x3d8) + 0xd0) + uVar6 * 8) + 0x40;
  Aska::PrimitiveBuffer::GetVertexPosAndNormal(unsigned int, Aska::Vector*, Aska::Vector*) const(lVar1,uVar4);
  uVar4 = uVar4 + 1;
  iVar2 = Aska::PrimitiveBuffer::GetVertexBufLength() const(lVar1);
  if (iVar2 <= (int)uVar4) {
    uVar5 = uVar5 + 1;
    if (*(long *)(*(long *)(param_1 + 0x3d8) + 0xd0) == 0) {
      uVar3 = 0;
    }
    else {
      uVar3 = (uint)*(ushort *)(*(long *)(*(long *)(param_1 + 0x3d8) + 0xb0) + 0x70);
    }
    uVar4 = 0;
    if (uVar3 <= uVar5) {
      uVar5 = 0;
    }
  }
  return uVar4 & 0xffff | uVar5 << 0x10;
}

// ==== Aska::AofObject::StopModifiers()
// vaddr 0x20cb5f8 | ghidra 0x21cb5f8 | size 32 | symbol _ZN4Aska9AofObject13StopModifiersEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska9AofObject13StopModifiersEv(long param_1)

{
  if (*(long *)(param_1 + 0x678) != 0) {
    (*(code *)PTR__ZN4Aska10AsfHandler13StopModifiersEPNS_9AofObjectE_02ca76d8)
              (*(undefined8 *)(*(long *)(param_1 + 0x3d8) + 0x318),param_1);
    return;
  }
  return;
}

// ==== Aska::AofObject::StartModifiers()
// vaddr 0x20cb618 | ghidra 0x21cb618 | size 32 | symbol _ZN4Aska9AofObject14StartModifiersEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska9AofObject14StartModifiersEv(long param_1)

{
  if (*(long *)(param_1 + 0x678) != 0) {
    (*(code *)PTR__ZN4Aska10AsfHandler14StartModifiersEPNS_9AofObjectE_02c952c0)
              (*(undefined8 *)(*(long *)(param_1 + 0x3d8) + 0x318),param_1);
    return;
  }
  return;
}

// ==== Aska::AofObject::GetRenderNodeIndex(char const*)
// vaddr 0x20cb638 | ghidra 0x21cb638 | size 120 | symbol _ZN4Aska9AofObject18GetRenderNodeIndexEPKc | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZN4Aska9AofObject18GetRenderNodeIndexEPKc(long param_1,undefined8 param_2)

{
  int iVar1;
  int iVar2;
  long lVar3;
  ulong uVar4;
  
  lVar3 = *(long *)(*(long *)(param_1 + 0x3d8) + 0xb0);
  iVar1 = *(int *)(lVar3 + 0xa0);
  if (iVar1 != 0) {
    lVar3 = lVar3 + iVar1;
    iVar1 = *(int *)(lVar3 + 0xa0);
    if (0 < iVar1) {
      uVar4 = 0;
      do {
        iVar2 = strcmp(param_2,lVar3 + (ulong)*(uint *)(lVar3 + 0xb0 + uVar4 * 4) + 0xa4);
        if (iVar2 == 0) goto code_r0x021cb69c;
        uVar4 = uVar4 + 1;
      } while ((long)uVar4 < (long)iVar1);
    }
  }
  uVar4 = 0xffffffff;
code_r0x021cb69c:
  return uVar4 & 0xffffffff;
}

// ==== Aska::AofObject::GetRenderNode(int)
// vaddr 0x20cb6b0 | ghidra 0x21cb6b0 | size 68 | symbol _ZN4Aska9AofObject13GetRenderNodeEi | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska9AofObject13GetRenderNodeEi(long param_1,int param_2)

{
  int iVar1;
  long lVar2;
  
  lVar2 = *(long *)(*(long *)(param_1 + 0x3d8) + 0xb0);
  iVar1 = *(int *)(lVar2 + 0xa0);
  if (iVar1 == 0) {
    return 0;
  }
  lVar2 = lVar2 + iVar1;
  if (param_2 < *(int *)(lVar2 + 0xa0)) {
    lVar2 = lVar2 + 0x90;
    return lVar2 + (ulong)*(uint *)(lVar2 + (long)param_2 * 4 + 0x20);
  }
  return 0;
}

// ==== Aska::AofObject::AllocateMeshArray(unsigned int)
// vaddr 0x20cb6f4 | ghidra 0x21cb6f4 | size 156 | symbol _ZN4Aska9AofObject17AllocateMeshArrayEj | lib libSOA-3.7.0.so | 2026-10-04
undefined8 * _ZN4Aska9AofObject17AllocateMeshArrayEj(undefined8 param_1,uint param_2)

{
  undefined1 auVar1 [16];
  undefined8 *puVar2;
  undefined8 *puVar3;
  ulong uVar4;
  
  puVar2 = (undefined8 *)operator new(unsigned long, std::nothrow_t const&)(0x20,PTR__ZSt7nothrow_02cb9a80);
  if (puVar2 != (undefined8 *)0x0) {
    *puVar2 = 0;
    *(undefined2 *)(puVar2 + 1) = 0;
    if ((int)param_2 < 3) {
      puVar3 = puVar2 + 2;
      *puVar2 = puVar3;
    }
    else {
      auVar1._8_8_ = 0;
      auVar1._0_8_ = (long)(int)param_2;
      uVar4 = -(ulong)(param_2 >> 0x1f) & 0xfffffff800000000 | (ulong)param_2 << 3;
      if (SUB168(auVar1 * ZEXT816(8),8) != 0) {
        uVar4 = 0xffffffffffffffff;
      }
      puVar3 = (undefined8 *)operator new[](unsigned long, std::nothrow_t const&)(uVar4,PTR__ZSt7nothrow_02cb9a80);
      *puVar2 = puVar3;
      if (puVar3 == (undefined8 *)0x0) {
        operator delete(void*)(puVar2);
        return (undefined8 *)0x0;
      }
    }
    *(short *)(puVar2 + 1) = (short)param_2;
    memset(puVar3,0,(long)(int)param_2 << 3);
  }
  return puVar2;
}

// ==== Aska::AofObject::SetStateDirtyToAllObjects()
// vaddr 0x20cb790 | ghidra 0x21cb790 | size 492 | symbol _ZN4Aska9AofObject25SetStateDirtyToAllObjectsEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska9AofObject25SetStateDirtyToAllObjectsEv(void)

{
  int *piVar1;
  int *piVar2;
  char cVar3;
  bool bVar4;
  ulong uVar5;
  int iVar6;
  long lVar7;
  long lVar8;
  long lVar9;
  long lVar10;
  
  lVar10 = *(long *)PTR__ZN4Aska6Global16m_pObjectManagerE_02cc4688;
  piVar1 = (int *)(lVar10 + 0xf98);
  iVar6 = 0;
code_r0x021cb7b0:
  do {
    if (*piVar1 != -1) {
      ClearExclusiveLocal();
      bVar4 = iVar6 < 0x1ff;
      iVar6 = iVar6 + 1;
      if (bVar4) goto code_r0x021cb7b0;
      piVar2 = (int *)(lVar10 + 0xf9c);
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
        if (bVar4) {
          *piVar2 = *piVar2 + 1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      do {
        if (*piVar1 != -1) {
          ClearExclusiveLocal();
          do {
            uVar5 = Aska::Semaphore::IsReady() const(lVar10 + 0xfd8);
            if ((uVar5 & 1) == 0) {
              do {
                cVar3 = '\x01';
                bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
                if (bVar4) {
                  *piVar2 = *piVar2 + -1;
                  cVar3 = ExclusiveMonitorsStatus();
                }
              } while (cVar3 != '\0');
              Aska::Thread::Sleep(unsigned int)(1);
            }
            else {
              Aska::Semaphore::Wait() const(lVar10 + 0xfd8);
            }
            do {
              cVar3 = '\x01';
              bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
              if (bVar4) {
                *piVar2 = *piVar2 + 1;
                cVar3 = ExclusiveMonitorsStatus();
              }
            } while (cVar3 != '\0');
            while (*piVar1 == -1) {
              cVar3 = '\x01';
              bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
              if (bVar4) {
                *piVar1 = 0;
                cVar3 = ExclusiveMonitorsStatus();
              }
              if (cVar3 == '\0') goto code_r0x021cb868;
            }
            ClearExclusiveLocal();
          } while( true );
        }
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
        if (bVar4) {
          *piVar1 = 0;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
code_r0x021cb868:
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
        if (bVar4) {
          *piVar2 = *piVar2 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
code_r0x021cb878:
      DataMemoryBarrier(2,3);
      for (lVar8 = *(long *)(lVar10 + 0x18); lVar10 + 8 != lVar8; lVar8 = *(long *)(lVar8 + 0x10)) {
        uVar5 = Aska::IAnimatable::IsThisIt(unsigned short) const(lVar8,0xf113);
        if (((uVar5 & 1) != 0) && (lVar7 = *(long *)(lVar8 + 0x3d8), lVar7 != 0)) {
          for (lVar9 = *(long *)(lVar7 + 0x138); lVar7 + 0x128 != lVar9;
              lVar9 = *(long *)(lVar9 + 0x10)) {
            Aska::RenderPassManager::InvalidateRenderState()(lVar9);
            Aska::RenderPassManager::InvalidateCommandBufferManager()(lVar9);
          }
          uVar5 = (ulong)*(ushort *)(lVar8 + 0x462);
          if (uVar5 != 0) {
            lVar7 = 0;
            do {
              uVar5 = uVar5 - 1;
              lVar9 = lVar8 + 0x470;
              if (*(long *)(lVar8 + 0x458) != 0) {
                lVar9 = *(long *)(lVar8 + 0x458);
              }
              lVar9 = lVar9 + lVar7;
              lVar7 = lVar7 + 0x20;
              *(undefined1 *)(lVar9 + 0x1a) = 0;
            } while (uVar5 != 0);
          }
        }
      }
      DataMemoryBarrier(2,3);
      *(undefined4 *)(lVar10 + 0xf98) = 0xffffffff;
      DataMemoryBarrier(2,3);
      if (0x14 < *(int *)(lVar10 + 0xf9c)) {
        piVar1 = (int *)(lVar10 + 0xf9c);
        do {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar4) {
            *piVar1 = *piVar1 + -1;
            cVar3 = ExclusiveMonitorsStatus();
          }
        } while (cVar3 != '\0');
        uVar5 = Aska::Semaphore::IsReady() const(lVar10 + 0xfd8);
        if ((uVar5 & 1) != 0) {
          (*(code *)PTR__ZNK4Aska9Semaphore6SignalEv_02c96cd0)(lVar10 + 0xfd8);
          return;
        }
      }
      return;
    }
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar4) {
      *piVar1 = 0;
      cVar3 = ExclusiveMonitorsStatus();
    }
    if (cVar3 == '\0') goto code_r0x021cb878;
  } while( true );
}

// ==== Aska::AofObject::UpdateMultiDrawVars()
// vaddr 0x20cb97c | ghidra 0x21cb97c | size 44 | symbol _ZN4Aska9AofObject19UpdateMultiDrawVarsEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska9AofObject19UpdateMultiDrawVarsEv(long param_1)

{
  undefined4 uVar1;
  
  *(undefined4 *)(param_1 + 0x228) = 0;
  uVar1 = 0;
  if (*(undefined8 **)(param_1 + 0x690) != (undefined8 *)0x0) {
    uVar1 = (**(code **)**(undefined8 **)(param_1 + 0x690))();
  }
  *(undefined4 *)(param_1 + 0x22c) = uVar1;
  return;
}

// ==== bool Aska::AofObject::MakeObjectRenderState<1015u>(Aska::AofObjectRenderState*, Aska::RenderPass*)
// vaddr 0x20cbaa8 | ghidra 0x21cbaa8 | size 1252 | symbol _ZN4Aska9AofObject21MakeObjectRenderStateILj1015EEEbPNS_20AofObjectRenderStateEPNS_10RenderPassE | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska9AofObject21MakeObjectRenderStateILj1015EEEbPNS_20AofObjectRenderStateEPNS_10RenderPassE
          (long param_1,long *param_2,long param_3)

{
  uint *puVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  long lVar5;
  undefined1 *puVar6;
  byte *pbVar7;
  uint uVar8;
  char cVar9;
  long lVar10;
  long lVar11;
  undefined8 *puVar12;
  undefined8 *puVar13;
  uint uVar14;
  long lVar15;
  uint uVar16;
  ulong uVar17;
  long lVar18;
  long *plVar19;
  char cVar20;
  undefined8 uVar21;
  long *plVar22;
  long lVar23;
  long lVar24;
  
  lVar10 = *param_2;
  lVar11 = param_2[1];
  lVar18 = param_2[2];
  uVar21 = *(undefined8 *)PTR__ZN4Aska6Global21m_pRenderStateManagerE_02cc0c10;
  if (lVar10 == 0) {
code_r0x021cbafc:
    lVar10 = Aska::RenderStateManager::Get(int)(uVar21,6);
    *param_2 = lVar10;
    if (lVar10 == 0) {
      return 0;
    }
  }
  else if (*(int *)(lVar10 + 0x10) < 6) {
    Aska::RenderState::Release()(lVar10);
    goto code_r0x021cbafc;
  }
  Aska::RenderState::Reset()(lVar10);
  if (lVar11 == 0) {
code_r0x021cbb34:
    lVar11 = Aska::RenderStateManager::Get(int)(uVar21,3);
    param_2[1] = lVar11;
    if (lVar11 == 0) {
      return 0;
    }
  }
  else if (*(int *)(lVar11 + 0x10) < 3) {
    Aska::RenderState::Release()(lVar11);
    goto code_r0x021cbb34;
  }
  Aska::RenderState::Reset()(lVar11);
  Aska::RenderState::SetDepthBias(float, float)(0,0,lVar10);
  Aska::RenderState::EnableZTest(bool)(lVar10,1);
  Aska::RenderState::SetZTestFunction(int)(lVar10,3);
  Aska::RenderState::EnableZWrite(bool)(lVar10,1);
  puVar1 = (uint *)(param_1 + 0x378);
  uVar14 = (uint)*(undefined6 *)(param_1 + 0x378);
  if ((uVar14 >> 1 & 1) == 0) {
    if ((uVar14 >> 1 & 1) == 0) goto code_r0x021cbba0;
code_r0x021cbbcc:
    Aska::RenderState::SetFillMode(int)(lVar11,2);
    uVar14 = (uint)*(undefined6 *)puVar1;
    if ((uVar14 >> 0xb & 1) == 0) goto code_r0x021cbbe8;
code_r0x021cbba4:
    if ((uVar14 >> 0xc & 1) == 0) goto code_r0x021cbba8;
code_r0x021cbc04:
    cVar20 = *(char *)(param_1 + 0x382);
    if (cVar20 == '\x01') {
      Aska::RenderState::EnableAlphaTest(bool)(lVar10,0);
      cVar20 = '\x02';
    }
    else {
      Aska::RenderState::SetAlphaTestFunction(int, int)(lVar10,cVar20,*(undefined1 *)(param_1 + 899));
    }
  }
  else {
    Aska::RenderState::SetFillMode(int)(lVar10,1);
    uVar14 = (uint)*(undefined6 *)puVar1;
    if ((uVar14 >> 1 & 1) != 0) goto code_r0x021cbbcc;
code_r0x021cbba0:
    if ((uVar14 >> 0xb & 1) != 0) goto code_r0x021cbba4;
code_r0x021cbbe8:
    Aska::RenderState::EnableStencil(Aska::StencilMode::Mode)(lVar10,0);
    if (((uint)*(undefined6 *)puVar1 >> 0xc & 1) != 0) goto code_r0x021cbc04;
code_r0x021cbba8:
    cVar20 = '\x02';
  }
  if ((*puVar1 >> 0xc & 1) != 0) {
    Aska::RenderState::EnableAlphaTest(bool)(lVar11,1);
  }
  Aska::RenderState::SetAlphaTestFunction(int, int)(lVar11,2,0);
  uVar17 = 0;
  if (*(long *)(*(long *)(param_1 + 0x3d8) + 0xd0) != 0) {
    uVar17 = (ulong)*(ushort *)(*(long *)(*(long *)(param_1 + 0x3d8) + 0xb0) + 0x70);
  }
  cVar9 = *(char *)(param_3 + 0x2b);
  uVar14 = (uint)uVar17;
  if (lVar18 == 0) {
    puVar12 = (undefined8 *)operator new(unsigned long, std::nothrow_t const&)(0x20,PTR__ZSt7nothrow_02cb9a80);
    if (puVar12 == (undefined8 *)0x0) {
code_r0x021cbcd8:
      param_2[2] = 0;
      return 0;
    }
    *puVar12 = 0;
    *(undefined2 *)(puVar12 + 1) = 0;
    if (uVar14 < 3) {
      puVar13 = puVar12 + 2;
      *puVar12 = puVar13;
    }
    else {
      puVar13 = (undefined8 *)operator new[](unsigned long, std::nothrow_t const&)(uVar14 << 3,PTR__ZSt7nothrow_02cb9a80);
      *puVar12 = puVar13;
      if (puVar13 == (undefined8 *)0x0) {
        operator delete(void*)(puVar12);
        goto code_r0x021cbcd8;
      }
    }
    *(short *)(puVar12 + 1) = (short)uVar17;
    memset(puVar13,0,uVar14 << 3);
    param_2[2] = (long)puVar12;
  }
  if (uVar14 != 0) {
    lVar18 = 0;
    lVar10 = 0;
    uVar14 = 0xffffffff;
    plVar22 = (long *)param_2[2];
    lVar11 = 0x58;
    plVar19 = param_2;
    do {
      if ((*(byte *)(*(long *)(param_3 + 8) + lVar11) >> 2 & 1) == 0) {
        lVar15 = *(long *)(*(long *)(param_1 + 0x3d8) + 0x100);
        if (lVar15 == 0) {
          lVar24 = 0;
        }
        else {
          lVar24 = *(long *)(lVar15 + lVar18);
        }
        lVar23 = *(long *)(*plVar22 + lVar10 * 8);
        lVar5 = 0;
        if (lVar15 != 0) {
          lVar5 = lVar15 + lVar18 + 0x10;
        }
        if (lVar23 == 0) {
          uVar21 = Aska::RenderStateManager::Get(int)(*(undefined8 *)
                                    PTR__ZN4Aska6Global21m_pRenderStateManagerE_02cc0c10,9);
          *(undefined8 *)(*plVar22 + lVar10 * 8) = uVar21;
          lVar23 = *(long *)(*plVar22 + lVar10 * 8);
          if (lVar23 == 0) {
            return 0;
          }
        }
        Aska::RenderState::Reset()(lVar23);
        uVar8 = *puVar1;
        puVar6 = (undefined1 *)(lVar5 + 0x231);
        if ((uVar8 & 0x1000) != 0) {
          puVar6 = (undefined1 *)(param_1 + 899);
        }
        pbVar7 = (byte *)(lVar5 + 0x232);
        if ((uVar8 & 0x2000) != 0) {
          pbVar7 = (byte *)(param_1 + 900);
        }
        uVar2 = (uint)plVar19 & 0xfff80000;
        uVar4 = (uint)CONCAT11(*puVar6,*(char *)(lVar24 + 0x14));
        uVar3 = (*pbVar7 & 3) << 0x11;
        uVar16 = uVar2 | uVar4 | uVar3;
        if ((*(char *)(lVar24 + 0x14) == '\0') && (*(byte *)(param_1 + 0x1b4) != 0)) {
          uVar16 = uVar2 | uVar4 & 0xfffeff00 | uVar3 | (uint)*(byte *)(param_1 + 0x1b4);
        }
        if ((((uint)*(undefined6 *)puVar1 >> 0xd & 1) != 0) && (*(byte *)(param_1 + 900) != 0)) {
          uVar16 = uVar16 & 0xffffff00;
        }
        uVar2 = uVar16 & 0xffffff00 | 0x10;
        if ((uVar16 & 0xff) != 0 || cVar9 != '\x01') {
          uVar2 = uVar16;
        }
        if ((uVar8 & 0x10000) != 0) {
          uVar2 = uVar16 & 0xffffff00;
        }
        plVar19 = (long *)(ulong)uVar2;
        if (uVar14 != uVar2) {
          uVar8 = uVar2 & 0xff;
          if (uVar8 != (uVar14 & 0xff)) {
            if (uVar8 == 0) {
              Aska::RenderState::EnableAlphaBlend(bool)(lVar23,0);
            }
            else {
              Aska::RenderState::EnableAlphaBlend(bool)(lVar23,1);
              Aska::RenderState::SetAlphaBlendFunction(Aska::AlphaBlend::Operation, Aska::SeparateAlphaBlendMode::E)(lVar23,uVar8,cVar9);
            }
          }
          if ((uVar2 >> 8 & 0x1ff) != (uVar14 >> 8 & 0x1ff)) {
            Aska::RenderState::SetAlphaTestFunction(int, int)(lVar23,cVar20);
          }
          uVar8 = uVar14 >> 0x11;
          uVar14 = uVar2;
          if ((uVar2 >> 0x11 & 3) != (uVar8 & 3)) {
            Aska::RenderState::SetAlphaToCoverage(int)(lVar23);
          }
        }
        if ((*puVar1 >> 0xb & 1) != 0) {
          Aska::RenderState::EnableStencil(Aska::StencilMode::Mode)(lVar23,1);
          Aska::RenderState::SetStencilOp(int, int, int, int, int, short)(lVar23,*(undefined1 *)(param_1 + 0x389),*(undefined1 *)(param_1 + 0x38a),
                          *(undefined1 *)(param_1 + 0x38b),*(undefined1 *)(param_1 + 0x38c),
                          *(undefined1 *)(param_1 + 0x38d),*(undefined2 *)(param_1 + 0x6a8));
        }
        lVar15 = *(long *)(*plVar22 + lVar10 * 8);
        if ((lVar15 != 0) && (*(int *)(lVar15 + 0x14) == 0)) {
          Aska::RenderState::Release()();
          *(undefined8 *)(*plVar22 + lVar10 * 8) = 0;
        }
      }
      lVar10 = lVar10 + 1;
      lVar11 = lVar11 + 0x1b8;
      lVar18 = lVar18 + 0x2a0;
    } while (lVar10 < (long)uVar17);
  }
  Aska::RenderPassManager::InvalidateObjectRenderState()(*(undefined8 *)(param_1 + 0x398));
  *(undefined1 *)((long)param_2 + 0x1a) = 1;
  return 1;
}

// ==== bool Aska::AofObject::MakeObjectRenderState<497u>(Aska::AofObjectRenderState*, Aska::RenderPass*)
// vaddr 0x20cbf8c | ghidra 0x21cbf8c | size 380 | symbol _ZN4Aska9AofObject21MakeObjectRenderStateILj497EEEbPNS_20AofObjectRenderStateEPNS_10RenderPassE | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska9AofObject21MakeObjectRenderStateILj497EEEbPNS_20AofObjectRenderStateEPNS_10RenderPassE
          (long param_1,long *param_2)

{
  long lVar1;
  long lVar2;
  uint uVar3;
  undefined8 uVar4;
  
  lVar1 = *param_2;
  lVar2 = param_2[1];
  uVar4 = *(undefined8 *)PTR__ZN4Aska6Global21m_pRenderStateManagerE_02cc0c10;
  if (lVar1 == 0) {
code_r0x021cbfc8:
    lVar1 = Aska::RenderStateManager::Get(int)(uVar4,7);
    *param_2 = lVar1;
    if (lVar1 == 0) {
      return 0;
    }
  }
  else if (*(int *)(lVar1 + 0x10) < 7) {
    Aska::RenderState::Release()(lVar1);
    goto code_r0x021cbfc8;
  }
  Aska::RenderState::Reset()(lVar1);
  if (lVar2 != 0) {
    if (1 < *(int *)(lVar2 + 0x10)) goto code_r0x021cc018;
    Aska::RenderState::Release()(lVar2);
  }
  lVar2 = Aska::RenderStateManager::Get(int)(uVar4,2);
  param_2[1] = lVar2;
  if (lVar2 == 0) {
    return 0;
  }
code_r0x021cc018:
  Aska::RenderState::Reset()(lVar2);
  Aska::RenderState::EnableAlphaBlend(bool)(lVar1,0);
  Aska::RenderState::SetDepthBias(float, float)(0,0,lVar1);
  Aska::RenderState::EnableZTest(bool)(lVar1,1);
  Aska::RenderState::SetZTestFunction(int)(lVar1,3);
  Aska::RenderState::EnableZWrite(bool)(lVar1,1);
  uVar3 = (uint)*(undefined6 *)(param_1 + 0x378);
  if ((uVar3 >> 1 & 1) != 0) {
    Aska::RenderState::SetFillMode(int)(lVar1,1);
    uVar3 = (uint)*(undefined6 *)(param_1 + 0x378);
  }
  if ((uVar3 >> 1 & 1) != 0) {
    Aska::RenderState::SetFillMode(int)(lVar2,2);
    uVar3 = (uint)*(undefined6 *)(param_1 + 0x378);
  }
  if ((uVar3 >> 0xb & 1) == 0) {
    Aska::RenderState::EnableStencil(Aska::StencilMode::Mode)(lVar1,0);
  }
  Aska::RenderState::EnableAlphaTest(bool)(lVar1,0);
  Aska::RenderState::EnableAlphaTest(bool)(lVar2,1);
  Aska::RenderPassManager::InvalidateObjectRenderState()(*(undefined8 *)(param_1 + 0x398));
  *(undefined1 *)((long)param_2 + 0x1a) = 1;
  return 1;
}

// ==== Aska::AsfHandler::SearchTextureIDByName(char const*, char const*, Aska::AofObject::TextureType) const
// vaddr 0x20d44fc | ghidra 0x21d44fc | size 176 | symbol _ZNK4Aska10AsfHandler21SearchTextureIDByNameEPKcS2_NS_9AofObject11TextureTypeE | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZNK4Aska10AsfHandler21SearchTextureIDByNameEPKcS2_NS_9AofObject11TextureTypeE
          (long param_1,byte *param_2,long param_3,undefined4 param_4)

{
  uint uVar1;
  byte *pbVar2;
  undefined8 uVar3;
  long *plVar4;
  long lVar5;
  ulong uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  
  if (0 < *(int *)(param_1 + 0xb0)) {
    plVar4 = *(long **)(param_1 + 0xb8);
    uVar8 = (uint)*param_2;
    uVar7 = 0x811c9dc5;
    uVar1 = *(uint *)(plVar4 + 0xb);
    pbVar2 = param_2;
    if (*param_2 != 0) {
      do {
        uVar9 = (uint)pbVar2[1];
        uVar7 = uVar7 * 0x1000193 ^ uVar8;
        uVar8 = uVar9;
        pbVar2 = pbVar2 + 1;
      } while (uVar9 != 0);
    }
    uVar8 = 0;
    if (uVar1 != 0) {
      uVar8 = uVar7 / uVar1;
    }
    lVar5 = (**(code **)(*plVar4 + 0x80))(plVar4,param_2,uVar7 - uVar8 * uVar1);
    if ((((lVar5 != 0) && (lVar5 = *(long *)(lVar5 + 0x38), lVar5 != 0)) &&
        (uVar6 = Aska::IAnimatable::IsThisIt(unsigned short) const(lVar5,0xf113), param_3 != 0)) && ((uVar6 & 1) != 0)) {
      uVar3 = (*(code *)PTR__ZNK4Aska9AofObject15SearchTextureIDEPKcNS0_11TextureTypeE_02c8e200)
                        (lVar5,param_3,param_4);
      return uVar3;
    }
  }
  return 0;
}

// ==== Aska::AofObject::CheckLightMaskMixerLight(Aska::Light*) const
// vaddr 0x2140eec | ghidra 0x2240eec | size 324 | symbol _ZNK4Aska9AofObject24CheckLightMaskMixerLightEPNS_5LightE | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska9AofObject24CheckLightMaskMixerLightEPNS_5LightE(long param_1,long param_2)

{
  long lVar1;
  int iVar2;
  undefined8 uVar3;
  
  lVar1 = param_2 + 0x340;
  if (*(char *)(param_1 + 0x3bc) == '\0') {
    if (*(long *)(param_1 + 0x438) == param_2) {
      return 0;
    }
  }
  else if (*(char *)(param_1 + 0x3bc) == '\x01') {
    uVar3 = strcmp((ulong *)(param_1 + 0x5a0),lVar1);
    if ((int)uVar3 == 0) {
      return uVar3;
    }
  }
  else if ((*(ulong *)(param_2 + 0x2a8) & *(ulong *)(param_1 + 0x5a0)) != 0) {
    return 0;
  }
  if (*(char *)(param_1 + 0x3bd) == '\0') {
    if (*(long *)(param_1 + 0x440) == param_2) {
      return 1;
    }
  }
  else if (*(char *)(param_1 + 0x3bd) == '\x01') {
    iVar2 = strcmp((ulong *)(param_1 + 0x5c0),lVar1);
    if (iVar2 == 0) {
      return 1;
    }
  }
  else if ((*(ulong *)(param_2 + 0x2a8) & *(ulong *)(param_1 + 0x5c0)) != 0) {
    return 1;
  }
  if (*(char *)(param_1 + 0x3be) == '\0') {
    if (*(long *)(param_1 + 0x448) == param_2) {
      return 2;
    }
  }
  else if (*(char *)(param_1 + 0x3be) == '\x01') {
    iVar2 = strcmp((ulong *)(param_1 + 0x5e0),lVar1);
    if (iVar2 == 0) {
      return 2;
    }
  }
  else if ((*(ulong *)(param_2 + 0x2a8) & *(ulong *)(param_1 + 0x5e0)) != 0) {
    return 2;
  }
  if (*(char *)(param_1 + 0x3bf) == '\0') {
    if (*(long *)(param_1 + 0x450) != param_2) {
      return 0xffffffff;
    }
  }
  else if (*(char *)(param_1 + 0x3bf) == '\x01') {
    iVar2 = strcmp((ulong *)(param_1 + 0x600),lVar1);
    if (iVar2 != 0) {
      return 0xffffffff;
    }
  }
  else if ((*(ulong *)(param_2 + 0x2a8) & *(ulong *)(param_1 + 0x600)) == 0) {
    return 0xffffffff;
  }
  return 3;
}


// FAILED to create function at 02c48ab8 Aska::AofObject::vtable
// FAILED to create function at 02c48dd0 Aska::AofObject::typeinfo
// FAILED to create function at 02cc7ad8 Aska::AofObject::m_uiDiscardCountLimit
// FAILED to create function at 02cc7adc Aska::AofObject::m_ucDiscardResourceTh
// FAILED to create function at 02cc7add Aska::AofObject::m_nSpecialShadowAdapterLimit
// FAILED to create function at 02dcdd1c Aska::AofObject::m_bIBLOptimizeHackGlobal
// FAILED to create function at 02dcdd1d Aska::AofObject::m_bAlphaObjectDebug
// FAILED to create function at 02dcdd1e Aska::AofObject::m_bOpaqueObjectInTransparentDebug
// FAILED to create function at 02dcdd1f Aska::AofObject::m_bDoubleSideObjectDebug
// FAILED to create function at 02dcdd20 Aska::AofObject::m_bLightCountDebug
// FAILED to create function at 02dcdd21 Aska::AofObject::m_bIBLBlendDebug
// FAILED to create function at 02dcdd22 Aska::AofObject::m_bZprepassDebug
// FAILED to create function at 02dcdd23 Aska::AofObject::m_bPolyZSort
// FAILED to create function at 02dcdd24 Aska::AofObject::m_bShadowAdapterDebug
// FAILED to create function at 02dcdd25 Aska::AofObject::m_bShaderAdapterDebug
// FAILED to create function at 02dcdd26 Aska::AofObject::m_bHighPrecisionNormalDebug
// FAILED to create function at 02dcdd27 Aska::AofObject::m_ucLightIDDebug
// FAILED to create function at 02dcdd28 Aska::AofObject::m_bPolygonDensityDebug
// FAILED to create function at 02dcdd29 Aska::AofObject::m_bMasterShadowNoise
// FAILED to create function at 02dcdd30 Aska::AofObject::m_ulShadowNoiseTextureID
