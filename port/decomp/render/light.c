// port/decomp/render/light.c: Ghidra decompiles for the render subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-04 07:14 UTC: tools/decomp.sh '--into' 'render/light' 'Aska::LightManager::' 'Aska::Light::'

// ==== AofObjectDeleteArrayHandler<Aska::LightManager::LightContext>::DeleteCallback(int, void*)
// vaddr 0x20cba90 | ghidra 0x21cba90 | size 16 | symbol _ZN27AofObjectDeleteArrayHandlerIN4Aska12LightManager12LightContextEE14DeleteCallbackEiPv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN27AofObjectDeleteArrayHandlerIN4Aska12LightManager12LightContextEE14DeleteCallbackEiPv
               (undefined8 param_1,undefined8 param_2,long param_3)

{
  if (param_3 != 0) {
    (*(code *)PTR__ZdaPv_02cb5db8)(param_3);
    return;
  }
  return;
}

// ==== AofObjectDeleteArrayHandler<Aska::LightManager::LightContext>::CancelCallback(int, void*)
// vaddr 0x20cbaa0 | ghidra 0x21cbaa0 | size 4 | symbol _ZN27AofObjectDeleteArrayHandlerIN4Aska12LightManager12LightContextEE14CancelCallbackEiPv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN27AofObjectDeleteArrayHandlerIN4Aska12LightManager12LightContextEE14CancelCallbackEiPv(void)

{
  return;
}

// ==== AofObjectDeleteArrayHandler<Aska::LightManager::LightContext>::~AofObjectDeleteArrayHandler()
// vaddr 0x20cbaa4 | ghidra 0x21cbaa4 | size 4 | symbol _ZN27AofObjectDeleteArrayHandlerIN4Aska12LightManager12LightContextEED0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN27AofObjectDeleteArrayHandlerIN4Aska12LightManager12LightContextEED0Ev(void)

{
  (*(code *)PTR__ZdlPv_02ca4758)();
  return;
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

// ==== Aska::Light::CalcSpotCoefficient()
// vaddr 0x213a6d8 | ghidra 0x223a6d8 | size 104 | symbol _ZN4Aska5Light19CalcSpotCoefficientEv | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska5Light19CalcSpotCoefficientEv(long param_1)

{
  float fVar1;
  
  fVar1 = *(float *)(param_1 + 0x2d8);
  if (*(float *)(param_1 + 0x2d8) <= _UNK_027e519c) {
    fVar1 = _UNK_027e519c;
  }
  fVar1 = (float)cosf((*(float *)(param_1 + 0x2d4) + fVar1) * 0.5);
  *(float *)(param_1 + 0x2dc) = fVar1 * fVar1;
  fVar1 = (float)cosf(*(float *)(param_1 + 0x2d4) * 0.5);
  *(float *)(param_1 + 0x2e0) = 1.0 / (fVar1 * fVar1 - *(float *)(param_1 + 0x2dc));
  return;
}

// ==== Aska::Light::CalcAttenuation()
// vaddr 0x213a740 | ghidra 0x223a740 | size 404 | symbol _ZN4Aska5Light15CalcAttenuationEv | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska5Light15CalcAttenuationEv(long param_1)

{
  uint3 uVar1;
  ulong uVar2;
  uint uVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  
  uVar3 = *(uint *)(param_1 + 0x30c);
  uVar2 = Aska::AffUtil::DoesAffectPlatformType(unsigned int)(uVar3 >> 0xc & 0xff);
  if (((uVar2 & 1) != 0) || (uVar2 = Aska::AffUtil::DoesAffectPlatformRange(unsigned int)(uVar3 >> 0x14 & 0xf), (uVar2 & 1) != 0)) {
    uVar1 = *(uint3 *)(param_1 + 0x2a5);
    uVar3 = (uint)uVar1;
    if (((uVar1 & 0x40) == 0) &&
       ((1.0 < *(float *)(param_1 + 0x210) + *(float *)(param_1 + 0x214) +
               *(float *)(param_1 + 0x218) && (*(float *)(param_1 + 0x21c) == 0.0)))) {
      uVar3 = uVar3 | 0x40;
      *(char *)(param_1 + 0x2a7) = (char)(uVar1 >> 0x10);
      *(short *)(param_1 + 0x2a5) = (short)uVar3;
    }
    if ((uVar3 >> 6 & 1) != 0) {
      *(float *)(param_1 + 0x2b8) =
           *(float *)PTR__ZN4Aska5Light22m_fRangeReductionRatioE_02cbda50 *
           *(float *)(param_1 + 700);
    }
  }
  fVar5 = *(float *)(param_1 + 0x214);
  fVar4 = *(float *)(param_1 + 0x218);
  fVar6 = *(float *)(param_1 + 0x210);
  *(float *)(param_1 + 0x220) = fVar6;
  *(float *)(param_1 + 0x224) = fVar5;
  *(float *)(param_1 + 0x22c) = *(float *)(param_1 + 0x21c);
  *(float *)(param_1 + 0x228) = fVar4;
  fVar8 = _UNK_027edb40;
  fVar7 = _UNK_027e6ae4;
  if (*(float *)(param_1 + 0x21c) == 0.0) {
    *(undefined4 *)(param_1 + 0x22c) = 0;
    fVar5 = fVar5 * fVar7;
    fVar4 = fVar4 * fVar8;
    *(float *)(param_1 + 0x224) = fVar5;
    *(float *)(param_1 + 0x228) = fVar4;
    if ((*(ushort *)(param_1 + 0x2a5) >> 6 & 1) == 0) {
      return;
    }
    fVar7 = *(float *)(param_1 + 0x2b8);
    fVar8 = 1.0 / (fVar7 * fVar5 + fVar6 + fVar7 * fVar7 * fVar4);
    if (fVar8 < 1.0) {
      fVar7 = -fVar8 / (fVar8 + -1.0);
      fVar8 = 1.0 / (fVar7 + 1.0);
      *(float *)(param_1 + 0x220) = fVar8 * fVar6;
      *(float *)(param_1 + 0x224) = fVar8 * fVar5;
      *(float *)(param_1 + 0x228) = fVar8 * fVar4;
      *(float *)(param_1 + 0x22c) = fVar7;
      return;
    }
    fVar5 = fVar5 / fVar7;
    fVar4 = fVar4 / (fVar7 * fVar7);
  }
  else {
    fVar6 = *(float *)(param_1 + 0x2b8);
    fVar5 = fVar5 / fVar6;
    fVar4 = fVar4 / (fVar6 * fVar6);
  }
  *(float *)(param_1 + 0x224) = fVar5;
  *(float *)(param_1 + 0x228) = fVar4;
  return;
}

// ==== Aska::Light::Clone(Aska::Light const*)
// vaddr 0x213a8d4 | ghidra 0x223a8d4 | size 948 | symbol _ZN4Aska5Light5CloneEPKS0_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Light5CloneEPKS0_(long param_1,long param_2)

{
  ushort *puVar1;
  ushort *puVar2;
  ushort uVar3;
  byte bVar4;
  byte bVar5;
  ushort uVar6;
  ushort uVar7;
  ushort uVar8;
  ushort uVar9;
  long lVar10;
  long lVar11;
  long lVar12;
  undefined8 uVar13;
  
  *(undefined4 *)(param_1 + 0x290) = *(undefined4 *)(param_2 + 0x290);
  *(undefined4 *)(param_1 + 0x294) = *(undefined4 *)(param_2 + 0x294);
  *(undefined4 *)(param_1 + 0x298) = *(undefined4 *)(param_2 + 0x298);
  *(undefined4 *)(param_1 + 0x29c) = *(undefined4 *)(param_2 + 0x29c);
  *(undefined4 *)(param_1 + 0x200) = *(undefined4 *)(param_2 + 0x200);
  *(undefined4 *)(param_1 + 0x204) = *(undefined4 *)(param_2 + 0x204);
  *(undefined4 *)(param_1 + 0x208) = *(undefined4 *)(param_2 + 0x208);
  *(undefined4 *)(param_1 + 0x20c) = *(undefined4 *)(param_2 + 0x20c);
  *(undefined4 *)(param_1 + 0x210) = *(undefined4 *)(param_2 + 0x210);
  *(undefined4 *)(param_1 + 0x214) = *(undefined4 *)(param_2 + 0x214);
  *(undefined4 *)(param_1 + 0x218) = *(undefined4 *)(param_2 + 0x218);
  *(undefined4 *)(param_1 + 0x21c) = *(undefined4 *)(param_2 + 0x21c);
  *(undefined4 *)(param_1 + 0x230) = *(undefined4 *)(param_2 + 0x230);
  *(undefined4 *)(param_1 + 0x234) = *(undefined4 *)(param_2 + 0x234);
  *(undefined4 *)(param_1 + 0x238) = *(undefined4 *)(param_2 + 0x238);
  *(undefined4 *)(param_1 + 0x23c) = *(undefined4 *)(param_2 + 0x23c);
  *(undefined4 *)(param_1 + 0x280) = *(undefined4 *)(param_2 + 0x280);
  *(undefined4 *)(param_1 + 0x284) = *(undefined4 *)(param_2 + 0x284);
  *(undefined4 *)(param_1 + 0x288) = *(undefined4 *)(param_2 + 0x288);
  *(undefined4 *)(param_1 + 0x28c) = *(undefined4 *)(param_2 + 0x28c);
  uVar13 = *(undefined8 *)(param_2 + 0x270);
  *(undefined8 *)(param_1 + 0x278) = *(undefined8 *)(param_2 + 0x278);
  *(undefined8 *)(param_1 + 0x270) = uVar13;
  uVar13 = *(undefined8 *)(param_2 + 0x260);
  *(undefined8 *)(param_1 + 0x268) = *(undefined8 *)(param_2 + 0x268);
  *(undefined8 *)(param_1 + 0x260) = uVar13;
  uVar13 = *(undefined8 *)(param_2 + 0x250);
  *(undefined8 *)(param_1 + 600) = *(undefined8 *)(param_2 + 600);
  *(undefined8 *)(param_1 + 0x250) = uVar13;
  uVar13 = *(undefined8 *)(param_2 + 0x240);
  *(undefined8 *)(param_1 + 0x248) = *(undefined8 *)(param_2 + 0x248);
  *(undefined8 *)(param_1 + 0x240) = uVar13;
  *(undefined4 *)(param_1 + 0x2d4) = *(undefined4 *)(param_2 + 0x2d4);
  *(undefined4 *)(param_1 + 0x2d8) = *(undefined4 *)(param_2 + 0x2d8);
  *(undefined4 *)(param_1 + 0x2dc) = *(undefined4 *)(param_2 + 0x2dc);
  *(undefined4 *)(param_1 + 0x2e0) = *(undefined4 *)(param_2 + 0x2e0);
  *(undefined4 *)(param_1 + 700) = *(undefined4 *)(param_2 + 700);
  *(undefined4 *)(param_1 + 0x2b8) = *(undefined4 *)(param_2 + 0x2b8);
  *(undefined8 *)(param_1 + 0x2a8) = *(undefined8 *)(param_2 + 0x2a8);
  *(undefined4 *)(param_1 + 0x2c4) = *(undefined4 *)(param_2 + 0x2c4);
  *(undefined4 *)(param_1 + 0x2cc) = *(undefined4 *)(param_2 + 0x2cc);
  if (*(byte *)(param_2 + 0x2a1) < 9) {
    *(byte *)(param_1 + 0x2a1) = *(byte *)(param_2 + 0x2a1);
  }
  puVar1 = (ushort *)(param_1 + 0x2a5);
  puVar2 = (ushort *)(param_2 + 0x2a5);
  bVar4 = *(byte *)(param_1 + 0x2a7);
  *(undefined1 *)(param_1 + 0x2a0) = *(undefined1 *)(param_2 + 0x2a0);
  *(undefined1 *)(param_1 + 0x2a2) = *(undefined1 *)(param_2 + 0x2a2);
  uVar6 = *puVar1;
  uVar7 = *puVar2;
  *puVar1 = uVar6 & 0xfffe | uVar7 & 1;
  uVar7 = uVar6 & 6 | uVar7 & 1 | (*puVar2 >> 3 & 1) << 3;
  *puVar1 = uVar6 & 0xfff0 | uVar7;
  *(byte *)(param_1 + 0x2a7) = bVar4;
  uVar8 = *puVar2;
  *(byte *)(param_1 + 0x2a7) = bVar4;
  uVar3 = uVar6 & 0x30 | uVar7 | (uVar8 >> 6 & 1) << 6;
  *puVar1 = uVar6 & 0xff80 | uVar3;
  uVar7 = *puVar2;
  *(byte *)(param_1 + 0x2a7) = bVar4;
  uVar3 = uVar3 | (uVar7 >> 7 & 1) << 7;
  *puVar1 = uVar6 & 0xff00 | uVar3;
  uVar7 = *puVar2;
  *(byte *)(param_1 + 0x2a7) = bVar4;
  uVar3 = uVar3 | (uVar7 >> 8 & 1) << 8;
  *puVar1 = uVar6 & 0xfe00 | uVar3;
  uVar7 = *puVar2;
  *(byte *)(param_1 + 0x2a7) = bVar4;
  uVar3 = uVar3 | (uVar7 >> 9 & 1) << 9;
  *puVar1 = uVar6 & 0xfc00 | uVar3;
  uVar7 = *puVar2;
  *(byte *)(param_1 + 0x2a7) = bVar4;
  uVar3 = uVar3 | (uVar7 >> 10 & 1) << 10;
  *puVar1 = uVar6 & 0xf800 | uVar3;
  *(undefined4 *)(param_1 + 0x304) = *(undefined4 *)(param_2 + 0x304);
  *(undefined4 *)(param_1 + 0x308) = *(undefined4 *)(param_2 + 0x308);
  *(undefined4 *)(param_1 + 0x30c) = *(undefined4 *)(param_2 + 0x30c);
  uVar13 = *(undefined8 *)(param_2 + 0x350);
  *(undefined8 *)(param_1 + 0x358) = *(undefined8 *)(param_2 + 0x358);
  *(undefined8 *)(param_1 + 0x350) = uVar13;
  uVar13 = *(undefined8 *)(param_2 + 0x340);
  *(undefined8 *)(param_1 + 0x348) = *(undefined8 *)(param_2 + 0x348);
  *(undefined8 *)(param_1 + 0x340) = uVar13;
  uVar13 = *(undefined8 *)(param_2 + 0x370);
  *(undefined8 *)(param_1 + 0x378) = *(undefined8 *)(param_2 + 0x378);
  *(undefined8 *)(param_1 + 0x370) = uVar13;
  uVar13 = *(undefined8 *)(param_2 + 0x360);
  *(undefined8 *)(param_1 + 0x368) = *(undefined8 *)(param_2 + 0x368);
  *(undefined8 *)(param_1 + 0x360) = uVar13;
  memcpy(param_1 + 0x390,param_2 + 0x390,0x50);
  uVar7 = *puVar2;
  *(byte *)(param_1 + 0x2a7) = bVar4;
  uVar7 = (uVar7 >> 0xc & 1) << 0xc;
  uVar9 = uVar6 & 0x800 | uVar3 | uVar7;
  *puVar1 = uVar6 & 0xe000 | uVar9;
  uVar8 = *puVar2;
  *(byte *)(param_1 + 0x2a7) = bVar4;
  uVar8 = (uVar8 >> 0xd & 1) << 0xd;
  uVar9 = uVar6 & 0xc000 | uVar9 | uVar8;
  *puVar1 = uVar9;
  bVar5 = *(byte *)(param_2 + 0x2a7);
  *puVar1 = uVar9;
  bVar4 = bVar4 & 0xfe | bVar5 & 1;
  *(byte *)(param_1 + 0x2a7) = bVar4;
  uVar9 = *puVar2;
  *(byte *)(param_1 + 0x2a7) = bVar4;
  *puVar1 = uVar6 & 0xc000 | uVar3 | uVar7 | uVar8 | uVar9 & 0x800;
  *(undefined2 *)(param_1 + 0x2e6) = *(undefined2 *)(param_2 + 0x2e6);
  *(undefined4 *)(param_1 + 0x2f0) = *(undefined4 *)(param_2 + 0x2f0);
  *(undefined4 *)(param_1 + 0x2f4) = *(undefined4 *)(param_2 + 0x2f4);
  *(undefined4 *)(param_1 + 0x2f8) = *(undefined4 *)(param_2 + 0x2f8);
  *(undefined1 *)(param_1 + 0x2e8) = *(undefined1 *)(param_2 + 0x2e8);
  *(undefined4 *)(param_1 + 0x2ec) = *(undefined4 *)(param_2 + 0x2ec);
  *(undefined4 *)(param_1 + 0x2fc) = *(undefined4 *)(param_2 + 0x2fc);
  *(undefined8 *)(param_1 + 0x380) = *(undefined8 *)(param_2 + 0x380);
  *(undefined1 *)(param_1 + 0x424) = *(undefined1 *)(param_2 + 0x424);
  lVar11 = *(long *)(param_2 + 0x418);
  if (lVar11 == 0) {
    lVar10 = *(long *)(param_1 + 0x418);
    if (lVar10 == 0) goto code_r0x011dfe60;
    if (*(long *)(lVar10 + 0x11d0) != 0) {
      *(undefined8 *)(lVar10 + 0x11d0) = 0;
      *(undefined8 *)(lVar10 + 0x11e0) = 0;
      lVar10 = *(long *)(param_1 + 0x418);
    }
    if (*(long *)(lVar10 + 0x11f0) == 0) goto code_r0x011dfe60;
    *(undefined8 *)(lVar10 + 0x11f0) = 0;
  }
  else {
    lVar12 = *(long *)(lVar11 + 0x11d0);
    lVar10 = *(long *)(param_1 + 0x418);
    lVar11 = *(long *)(lVar11 + 0x11f0);
    if (lVar10 == 0) {
      if (lVar12 == 0) goto code_r0x011dfe60;
      lVar10 = operator new(unsigned long, std::nothrow_t const&)(0x1218,PTR__ZSt7nothrow_02cb9a80);
      if (lVar10 == 0) {
        *(undefined8 *)(param_1 + 0x418) = 0;
        goto code_r0x011dfe60;
      }
      Aska::IBLMap::IBLMap()(lVar10);
      *(long *)(param_1 + 0x418) = lVar10;
      Aska::Light::SetIBLProfile(unsigned int)(param_1,*(undefined1 *)(param_1 + 0x424));
      *(long *)(*(long *)(param_1 + 0x418) + 0x40) = param_1 + 0x240;
      lVar10 = *(long *)(param_1 + 0x418);
    }
    if (*(long *)(lVar10 + 0x11d0) != lVar12) {
      *(long *)(lVar10 + 0x11d0) = lVar12;
      *(undefined8 *)(lVar10 + 0x11e0) = 0;
      lVar10 = *(long *)(param_1 + 0x418);
    }
    if (*(long *)(lVar10 + 0x11f0) == lVar11) goto code_r0x011dfe60;
    *(long *)(lVar10 + 0x11f0) = lVar11;
  }
  *(undefined8 *)(lVar10 + 0x1200) = 0;
code_r0x011dfe60:
  *(undefined8 *)(param_1 + 0x400) = *(undefined8 *)(param_2 + 0x400);
  *(undefined8 *)(param_1 + 0x408) = *(undefined8 *)(param_2 + 0x408);
  *(undefined8 *)(param_1 + 0x410) = *(undefined8 *)(param_2 + 0x410);
  (*(code *)PTR__ZN4Aska12AimingObject5CloneEPKNS_11IAnimatableE_02ca7f20)(param_1,param_2);
  return;
}

// ==== Aska::Light::SetLightType(int)
// vaddr 0x213ac88 | ghidra 0x223ac88 | size 16 | symbol _ZN4Aska5Light12SetLightTypeEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Light12SetLightTypeEi(long param_1,uint param_2)

{
  if (param_2 < 9) {
    *(char *)(param_1 + 0x2a1) = (char)param_2;
  }
  return;
}

// ==== Aska::Light::SetIBLTextureID(unsigned long, unsigned long)
// vaddr 0x213ac98 | ghidra 0x223ac98 | size 172 | symbol _ZN4Aska5Light15SetIBLTextureIDEmm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Light15SetIBLTextureIDEmm(long param_1,long param_2,long param_3)

{
  long lVar1;
  
  lVar1 = *(long *)(param_1 + 0x418);
  if (lVar1 == 0) {
    if (param_2 == 0) {
      return;
    }
    lVar1 = operator new(unsigned long, std::nothrow_t const&)(0x1218,PTR__ZSt7nothrow_02cb9a80);
    if (lVar1 == 0) {
      *(undefined8 *)(param_1 + 0x418) = 0;
      return;
    }
    Aska::IBLMap::IBLMap()(lVar1);
    *(long *)(param_1 + 0x418) = lVar1;
    Aska::Light::SetIBLProfile(unsigned int)(param_1,*(undefined1 *)(param_1 + 0x424));
    *(long *)(*(long *)(param_1 + 0x418) + 0x40) = param_1 + 0x240;
    lVar1 = *(long *)(param_1 + 0x418);
  }
  if (*(long *)(lVar1 + 0x11d0) != param_2) {
    *(long *)(lVar1 + 0x11d0) = param_2;
    *(undefined8 *)(lVar1 + 0x11e0) = 0;
    lVar1 = *(long *)(param_1 + 0x418);
  }
  if (*(long *)(lVar1 + 0x11f0) != param_3) {
    *(long *)(lVar1 + 0x11f0) = param_3;
    *(undefined8 *)(lVar1 + 0x1200) = 0;
  }
  return;
}

// ==== Aska::Light::InitNoiseBuf()
// vaddr 0x213ad44 | ghidra 0x223ad44 | size 544 | symbol _ZN4Aska5Light12InitNoiseBufEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Light12InitNoiseBufEv(void)

{
  undefined4 uVar1;
  undefined *puVar2;
  uint uVar3;
  long lVar4;
  undefined8 *puVar5;
  long lVar6;
  float fVar7;
  
  puVar2 = PTR_m_aafNoiseBuf_02cbc598;
  lVar6 = 0;
  do {
    fVar7 = (float)Aska::RandomFloat()();
    *(float *)(puVar2 + lVar6) = fVar7 + -0.5;
    lVar6 = lVar6 + 4;
  } while (lVar6 != 0x400);
  lVar6 = 0;
  do {
    uVar1 = *(undefined4 *)(puVar2 + lVar6);
    uVar3 = Aska::Random()();
    lVar4 = (ulong)(uVar3 & 0xff) * 4;
    *(undefined4 *)(puVar2 + lVar6) = *(undefined4 *)(puVar2 + lVar4);
    lVar6 = lVar6 + 4;
    *(undefined4 *)(puVar2 + lVar4) = uVar1;
  } while (lVar6 != 0x400);
  lVar6 = 0;
  do {
    puVar5 = (undefined8 *)(puVar2 + lVar6);
    lVar6 = lVar6 + 0x10;
    puVar5[0x81] = puVar5[1];
    puVar5[0x80] = *puVar5;
  } while (lVar6 != 0x400);
  *(undefined4 *)(puVar2 + 0x800) = *(undefined4 *)(puVar2 + 0x400);
  *(undefined4 *)(puVar2 + 0x804) = *(undefined4 *)(puVar2 + 0x404);
  lVar6 = 0;
  do {
    fVar7 = (float)Aska::RandomFloat()();
    lVar4 = lVar6 + 4;
    *(float *)(puVar2 + lVar6 + 0x808) = fVar7 + -0.5;
    lVar6 = lVar4;
  } while (lVar4 != 0x400);
  lVar6 = 0;
  do {
    uVar1 = *(undefined4 *)(puVar2 + lVar6 + 0x808);
    uVar3 = Aska::Random()();
    lVar4 = (ulong)(uVar3 & 0xff) * 4;
    *(undefined4 *)(puVar2 + lVar6 + 0x808) = *(undefined4 *)(puVar2 + lVar4 + 0x808);
    lVar6 = lVar6 + 4;
    *(undefined4 *)(puVar2 + lVar4 + 0x808) = uVar1;
  } while (lVar6 != 0x400);
  lVar6 = 0x808;
  do {
    puVar5 = (undefined8 *)(puVar2 + lVar6);
    lVar6 = lVar6 + 0x10;
    puVar5[0x81] = puVar5[1];
    puVar5[0x80] = *puVar5;
  } while (lVar6 != 0xc08);
  *(undefined4 *)(puVar2 + 0x1008) = *(undefined4 *)(puVar2 + 0xc08);
  *(undefined4 *)(puVar2 + 0x100c) = *(undefined4 *)(puVar2 + 0xc0c);
  lVar6 = 0;
  do {
    fVar7 = (float)Aska::RandomFloat()();
    lVar4 = lVar6 + 4;
    *(float *)(puVar2 + lVar6 + 0x1010) = fVar7 + -0.5;
    lVar6 = lVar4;
  } while (lVar4 != 0x400);
  lVar6 = 0;
  do {
    uVar1 = *(undefined4 *)(puVar2 + lVar6 + 0x1010);
    uVar3 = Aska::Random()();
    lVar4 = (ulong)(uVar3 & 0xff) * 4;
    *(undefined4 *)(puVar2 + lVar6 + 0x1010) = *(undefined4 *)(puVar2 + lVar4 + 0x1010);
    lVar6 = lVar6 + 4;
    *(undefined4 *)(puVar2 + lVar4 + 0x1010) = uVar1;
  } while (lVar6 != 0x400);
  lVar6 = -0x400;
  do {
    lVar4 = lVar6 + 0x10;
    *(undefined8 *)(puVar2 + lVar6 + 0x1818) = *(undefined8 *)(puVar2 + lVar6 + 0x1418);
    *(undefined8 *)(puVar2 + lVar6 + 0x1810) = *(undefined8 *)(puVar2 + lVar6 + 0x1410);
    lVar6 = lVar4;
  } while (lVar4 != 0);
  *(undefined4 *)(puVar2 + 0x1810) = *(undefined4 *)(puVar2 + 0x1410);
  *(undefined4 *)(puVar2 + 0x1814) = *(undefined4 *)(puVar2 + 0x1414);
  lVar6 = 0;
  do {
    fVar7 = (float)Aska::RandomFloat()();
    lVar4 = lVar6 + 4;
    *(float *)(puVar2 + lVar6 + 0x1818) = fVar7 + -0.5;
    lVar6 = lVar4;
  } while (lVar4 != 0x400);
  lVar6 = 0;
  do {
    uVar1 = *(undefined4 *)(puVar2 + lVar6 + 0x1818);
    uVar3 = Aska::Random()();
    lVar4 = (ulong)(uVar3 & 0xff) * 4;
    *(undefined4 *)(puVar2 + lVar6 + 0x1818) = *(undefined4 *)(puVar2 + lVar4 + 0x1818);
    lVar6 = lVar6 + 4;
    *(undefined4 *)(puVar2 + lVar4 + 0x1818) = uVar1;
  } while (lVar6 != 0x400);
  puVar5 = (undefined8 *)(puVar2 + 0x1818);
  lVar6 = 0x100;
  do {
    lVar6 = lVar6 + -4;
    puVar5[0x81] = puVar5[1];
    puVar5[0x80] = *puVar5;
    puVar5 = puVar5 + 2;
  } while (lVar6 != 0);
  *(undefined4 *)(puVar2 + 0x2018) = *(undefined4 *)(puVar2 + 0x1c18);
  *(undefined4 *)(puVar2 + 0x201c) = *(undefined4 *)(puVar2 + 0x1c1c);
  return;
}

// ==== Aska::Light::GetNoise(float)
// vaddr 0x213af64 | ghidra 0x223af64 | size 108 | symbol _ZN4Aska5Light8GetNoiseEf | lib libSOA-3.7.0.so | 2026-10-04
float _ZN4Aska5Light8GetNoiseEf(float param_1,long param_2)

{
  uint uVar1;
  
  uVar1 = (uint)param_1;
  param_1 = param_1 - (float)(int)uVar1;
  return param_1 * *(float *)(PTR_m_aafNoiseBuf_02cbc598 +
                             (ulong)(uVar1 & 0xff) * 4 + (ulong)*(byte *)(param_2 + 0x2e8) * 0x808)
         + param_1 * param_1 * (param_1 * -2.0 + 3.0) *
           ((param_1 + -1.0) *
            *(float *)(PTR_m_aafNoiseBuf_02cbc598 +
                      (ulong)(uVar1 + 1 & 0xff) * 4 + (ulong)*(byte *)(param_2 + 0x2e8) * 0x808) -
           param_1 * *(float *)(PTR_m_aafNoiseBuf_02cbc598 +
                               (ulong)(uVar1 & 0xff) * 4 + (ulong)*(byte *)(param_2 + 0x2e8) * 0x808
                               ));
}

// ==== Aska::Light::MakeNoiseIntension()
// vaddr 0x213afd0 | ghidra 0x223afd0 | size 304 | symbol _ZN4Aska5Light18MakeNoiseIntensionEv | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska5Light18MakeNoiseIntensionEv(long param_1)

{
  int iVar1;
  uint uVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  
  if (0 < *(short *)(param_1 + 0x2e6)) {
    iVar1 = 0;
    fVar3 = 0.0;
    fVar4 = *(float *)(param_1 + 0x2f4);
    fVar5 = (*(float *)PTR__ZN4Aska5Light12m_fNoiseTimeE_02cbc668 + *(float *)(param_1 + 0x2ec)) *
            *(float *)(param_1 + 0x2f8);
    fVar5 = fVar5 + (float)(int)(fVar5 * _UNK_029cc0e0) * _UNK_0286c760;
    fVar6 = 0.0;
    do {
      uVar2 = (uint)fVar5;
      fVar7 = fVar5 - (float)(int)uVar2;
      fVar3 = fVar4 + fVar3;
      fVar7 = fVar4 * (fVar7 * *(float *)(PTR_m_aafNoiseBuf_02cbc598 +
                                         (ulong)(uVar2 & 0xff) * 4 +
                                         (ulong)*(byte *)(param_1 + 0x2e8) * 0x808) +
                      fVar7 * fVar7 * (fVar7 * -2.0 + 3.0) *
                      ((fVar7 + -1.0) *
                       *(float *)(PTR_m_aafNoiseBuf_02cbc598 +
                                 (ulong)(uVar2 + 1 & 0xff) * 4 +
                                 (ulong)*(byte *)(param_1 + 0x2e8) * 0x808) -
                      fVar7 * *(float *)(PTR_m_aafNoiseBuf_02cbc598 +
                                        (ulong)(uVar2 & 0xff) * 4 +
                                        (ulong)*(byte *)(param_1 + 0x2e8) * 0x808)));
      fVar4 = fVar4 * *(float *)(param_1 + 0x2f0);
      fVar6 = fVar6 + fVar7;
      if (fVar4 < _UNK_027e519c) break;
      iVar1 = iVar1 + 1;
      fVar5 = fVar5 + fVar5;
    } while (iVar1 < *(short *)(param_1 + 0x2e6));
    if (fVar3 != 0.0) {
      fVar3 = fVar6 * (*(float *)(param_1 + 0x2f4) / fVar3) + 1.0;
      if (fVar3 <= 0.0) {
        fVar3 = 0.0;
      }
      *(float *)(param_1 + 0x2fc) = fVar3;
      return;
    }
  }
  *(undefined4 *)(param_1 + 0x2fc) = 0x3f800000;
  return;
}

// ==== Aska::Light::CalcIBLIntensity() const
// vaddr 0x213b100 | ghidra 0x223b100 | size 64 | symbol _ZNK4Aska5Light16CalcIBLIntensityEv | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float _ZNK4Aska5Light16CalcIBLIntensityEv(long param_1)

{
  float fVar1;
  float fVar2;
  
  fVar1 = 0.0;
  if (_UNK_027fac84 <= ABS(*(float *)(param_1 + 0x23c))) {
    fVar2 = *(float *)(param_1 + 0x234);
    if (*(float *)(param_1 + 0x234) <= *(float *)(param_1 + 0x230)) {
      fVar2 = *(float *)(param_1 + 0x230);
    }
    fVar1 = *(float *)(param_1 + 0x238);
    if (*(float *)(param_1 + 0x238) <= fVar2) {
      fVar1 = fVar2;
    }
    fVar1 = *(float *)(param_1 + 0x23c) * fVar1;
  }
  return fVar1;
}

// ==== Aska::Light::CalcIntensityTS(Aska::RenderableObject*, Aska::Light::CalcIntensityWork*, bool, bool, float*, float*, float*) const
// vaddr 0x213b140 | ghidra 0x223b140 | size 860 | symbol _ZNK4Aska5Light15CalcIntensityTSEPNS_16RenderableObjectEPNS0_17CalcIntensityWorkEbbPfS5_S5_ | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float _ZNK4Aska5Light15CalcIntensityTSEPNS_16RenderableObjectEPNS0_17CalcIntensityWorkEbbPfS5_S5_
                (long param_1,long *param_2,float *param_3,byte param_4,uint param_5,float *param_6,
                float *param_7,float *param_8)

{
  byte bVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  
  fVar5 = *(float *)(param_1 + 0x23c);
  *(undefined1 *)(param_3 + 6) = 0;
  if (*(byte *)(param_1 + 0x2a1) < 4) {
    if ((*(byte *)(param_2 + 0x25) >> 4 & 1) == 0) {
      (**(code **)(*param_2 + 600))(param_2,1);
    }
    fVar8 = *(float *)(param_2 + 0x5a) - *(float *)(param_1 + 0x200);
    fVar9 = *(float *)((long)param_2 + 0x2d4) - *(float *)(param_1 + 0x204);
    fVar7 = *(float *)(param_2 + 0x5b) - *(float *)(param_1 + 0x208);
    fVar3 = *(float *)((long)param_2 + 0x2dc);
    fVar4 = SQRT(fVar8 * fVar8 + fVar9 * fVar9 + fVar7 * fVar7);
    if (NAN(fVar4)) {
      fVar4 = (float)sqrtf();
      bVar1 = *(byte *)(param_2 + 0x25);
    }
    else {
      bVar1 = *(byte *)(param_2 + 0x25);
    }
    if ((bVar1 >> 4 & 1) == 0) {
      (**(code **)(*param_2 + 600))(param_2,1);
    }
    fVar2 = *(float *)((long)param_2 + 0x2dc);
    fVar6 = fVar4 - fVar2;
    if (*(float *)(param_1 + 0x2b8) < fVar6) {
      if (param_6 != (float *)0x0) {
        *param_6 = 0.0;
      }
      if (param_7 != (float *)0x0) {
        *param_7 = 0.0;
      }
      if (param_8 == (float *)0x0) {
        return 0.0;
      }
      *param_8 = 0.0;
      return 0.0;
    }
    if ((((param_4 & 1) != 0) && ((param_5 & 1) == 0)) && (*(char *)(param_1 + 0x2a1) == '\x01')) {
      if ((*(byte *)(param_2 + 0x25) >> 4 & 1) == 0) {
        (**(code **)(*param_2 + 600))(param_2,1);
        fVar2 = *(float *)((long)param_2 + 0x2dc);
      }
      param_4 = *(float *)(param_1 + 0x2c0) <= fVar4 / fVar2 & param_4;
    }
    if (((param_4 & 1) == 0) && ((param_5 & 1) == 0)) {
      if ((0.0 <= fVar6) && (*(byte *)(param_1 + 0x2a1) - 1 < 3)) {
        fVar3 = 1.0 / (*(float *)(param_1 + 0x220) + fVar6 * *(float *)(param_1 + 0x224) +
                      fVar6 * fVar6 * *(float *)(param_1 + 0x228)) - *(float *)(param_1 + 0x22c);
        if (fVar3 < 0.0) {
          fVar3 = 0.0;
        }
        fVar4 = 1.0;
        if (fVar3 + -1.0 < 0.0) {
          fVar4 = fVar3;
        }
        fVar5 = fVar5 * fVar4;
      }
    }
    else if (*(byte *)(param_1 + 0x2a1) - 1 < 2) {
      fVar4 = 1.0 / fVar4;
      *param_3 = fVar8 * fVar4;
      param_3[1] = fVar9 * fVar4;
      param_3[2] = fVar7 * fVar4;
      param_3[3] = fVar3;
      fVar3 = 1.0;
      if (*(char *)(param_1 + 0x2a1) == '\x02') {
        fVar3 = fVar8 * fVar4 * *(float *)(param_1 + 0x290) +
                fVar9 * fVar4 * *(float *)(param_1 + 0x294) +
                fVar7 * fVar4 * *(float *)(param_1 + 0x298);
        fVar4 = *(float *)(param_1 + 0x2e0) * (fVar3 * fVar3 - *(float *)(param_1 + 0x2dc));
        fVar7 = (float)NEON_fminnm(fVar4,0x3f800000);
        fVar3 = 0.0;
        if (0.0 <= fVar4) {
          fVar3 = fVar7;
        }
      }
      param_3[5] = fVar3;
      fVar4 = fVar5;
      if (0.0 <= fVar6) {
        fVar7 = 1.0 / (*(float *)(param_1 + 0x220) + fVar6 * *(float *)(param_1 + 0x224) +
                      fVar6 * fVar6 * *(float *)(param_1 + 0x228)) - *(float *)(param_1 + 0x22c);
        if (fVar7 < 0.0) {
          fVar7 = 0.0;
        }
        fVar4 = 1.0;
        if (fVar7 + -1.0 < 0.0) {
          fVar4 = fVar7;
        }
        fVar4 = fVar5 * fVar4;
        fVar5 = fVar3 * fVar4;
      }
      param_3[4] = fVar4;
      *(byte *)(param_3 + 6) = param_4 & 1;
    }
  }
  fVar3 = 0.0;
  if (_UNK_027fac84 <= ABS(fVar5)) {
    fVar9 = *(float *)(param_1 + 0x230);
    fVar8 = *(float *)(param_1 + 0x234);
    fVar7 = *(float *)(param_1 + 0x238);
    fVar4 = fVar8;
    if (fVar8 <= fVar9) {
      fVar4 = fVar9;
    }
    fVar3 = fVar7;
    if (fVar7 <= fVar4) {
      fVar3 = fVar4;
    }
    fVar4 = 1.0 / fVar3;
    if (param_6 != (float *)0x0) {
      *param_6 = fVar9 * fVar4;
    }
    if (param_7 != (float *)0x0) {
      *param_7 = fVar8 * fVar4;
    }
    if (param_8 != (float *)0x0) {
      *param_8 = fVar7 * fVar4;
    }
    fVar3 = fVar5 * fVar3;
  }
  return fVar3;
}

// ==== Aska::Light::CalcBounceIntensity(Aska::Light*, Aska::Vector*) const
// vaddr 0x213b49c | ghidra 0x223b49c | size 892 | symbol _ZNK4Aska5Light19CalcBounceIntensityEPS0_PNS_6VectorE | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float _ZNK4Aska5Light19CalcBounceIntensityEPS0_PNS_6VectorE
                (long param_1,long param_2,float *param_3)

{
  uint3 uVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  
  fVar5 = *(float *)(param_1 + 0x23c);
  if (3 < *(byte *)(param_1 + 0x2a1)) goto code_r0x0223b7a8;
  fVar8 = *(float *)(param_1 + 0x200) - *(float *)(param_2 + 0x200);
  fVar9 = *(float *)(param_1 + 0x204) - *(float *)(param_2 + 0x204);
  fVar6 = *(float *)(param_1 + 0x208) - *(float *)(param_2 + 0x208);
  fVar4 = SQRT(fVar8 * fVar8 + fVar9 * fVar9 + fVar6 * fVar6);
  if (NAN(fVar4)) {
    fVar4 = (float)sqrtf();
    if (*(char *)(param_1 + 0x2a1) == '\0') goto code_r0x0223b6b4;
code_r0x0223b51c:
    uVar1 = *(uint3 *)(param_2 + 0x2a5);
    fVar2 = 1.0 / fVar4;
    fVar8 = fVar8 * fVar2;
    fVar9 = fVar9 * fVar2;
    fVar6 = fVar6 * fVar2;
    if ((uVar1 & 0x200) == 0) {
      fVar2 = 0.0;
      if (((*(ushort *)(param_2 + 0x2a5) & 0x180) != 0x100) &&
         (fVar2 = fVar8 * *(float *)(param_2 + 0x290) + fVar9 * *(float *)(param_2 + 0x294) +
                  fVar6 * *(float *)(param_2 + 0x298), fVar2 <= 0.0)) {
        return 0.0;
      }
      if ((uVar1 & 0x100) != 0) {
        fVar7 = fVar8 + *param_3;
        fVar11 = fVar9 + param_3[1];
        fVar10 = fVar6 + param_3[2];
        fVar3 = fVar7 * fVar7 + fVar11 * fVar11 + fVar10 * fVar10;
        fVar2 = SQRT(fVar3);
        if (NAN(fVar2)) {
          fVar2 = (float)sqrtf(fVar3);
        }
        if (_UNK_027e519c <= fVar2) {
          fVar2 = 1.0 / fVar2;
          fVar7 = fVar7 * fVar2;
          fVar11 = fVar11 * fVar2;
          fVar10 = fVar10 * fVar2;
        }
        fVar2 = fVar7 * *param_3 + fVar11 * param_3[1] + fVar10 * param_3[2];
      }
      fVar5 = fVar5 * fVar2;
    }
    if (fVar4 < 0.0) goto code_r0x0223b7a8;
    fVar4 = 1.0 / (*(float *)(param_1 + 0x220) + fVar4 * *(float *)(param_1 + 0x224) +
                  fVar4 * fVar4 * *(float *)(param_1 + 0x228)) - *(float *)(param_1 + 0x22c);
    if (fVar4 < 0.0) {
      fVar4 = 0.0;
    }
    fVar2 = 1.0;
    if (fVar4 + -1.0 < 0.0) {
      fVar2 = fVar4;
    }
    fVar5 = fVar5 * fVar2;
    if (*(char *)(param_1 + 0x2a1) != '\x02') goto code_r0x0223b7a8;
    fVar4 = fVar8 * *(float *)(param_1 + 0x290) + fVar9 * *(float *)(param_1 + 0x294) +
            fVar6 * *(float *)(param_1 + 0x298);
    fVar4 = (float)NEON_fminnm(*(float *)(param_1 + 0x2e0) *
                               (fVar4 * fVar4 - *(float *)(param_1 + 0x2dc)),0x3f800000);
  }
  else {
    if (*(char *)(param_1 + 0x2a1) != '\0') goto code_r0x0223b51c;
code_r0x0223b6b4:
    uVar1 = *(uint3 *)(param_2 + 0x2a5);
    if ((uVar1 & 0x200) != 0) goto code_r0x0223b7a8;
    fVar4 = 0.0;
    if (((*(ushort *)(param_2 + 0x2a5) & 0x180) != 0x100) &&
       (fVar4 = *(float *)(param_2 + 0x290) * *(float *)(param_1 + 0x290) +
                (float)*(undefined8 *)(param_2 + 0x294) * (float)*(undefined8 *)(param_1 + 0x294) +
                (float)((ulong)*(undefined8 *)(param_2 + 0x294) >> 0x20) *
                (float)((ulong)*(undefined8 *)(param_1 + 0x294) >> 0x20), 0.0 <= fVar4)) {
      return 0.0;
    }
    if ((uVar1 & 0x100) == 0) {
      fVar5 = -(fVar5 * fVar4);
      goto code_r0x0223b7a8;
    }
    fVar2 = *param_3 - *(float *)(param_1 + 0x290);
    fVar9 = param_3[1] - *(float *)(param_1 + 0x294);
    fVar8 = param_3[2] - *(float *)(param_1 + 0x298);
    fVar6 = fVar2 * fVar2 + fVar9 * fVar9 + fVar8 * fVar8;
    fVar4 = SQRT(fVar6);
    if (NAN(fVar4)) {
      fVar4 = (float)sqrtf(fVar6);
    }
    if (_UNK_027e519c <= fVar4) {
      fVar4 = 1.0 / fVar4;
      fVar2 = fVar2 * fVar4;
      fVar9 = fVar9 * fVar4;
      fVar8 = fVar8 * fVar4;
    }
    fVar4 = fVar2 * *param_3 + fVar9 * param_3[1] + fVar8 * param_3[2];
  }
  fVar5 = fVar5 * fVar4;
code_r0x0223b7a8:
  fVar4 = 0.0;
  if ((_UNK_027fac84 <= ABS(fVar5)) && (fVar4 = fVar5, (*(uint3 *)(param_2 + 0x2a5) & 0x400) != 0))
  {
    fVar6 = (float)logf(ABS(fVar5) + 1.0);
    fVar4 = fVar6 * *(float *)(param_2 + 0x308);
    if (fVar5 <= 0.0) {
      fVar4 = -(fVar6 * *(float *)(param_2 + 0x308));
    }
  }
  return fVar4;
}

// ==== Aska::Light::GetIBLTextureID(int) const
// vaddr 0x213b818 | ghidra 0x223b818 | size 44 | symbol _ZNK4Aska5Light15GetIBLTextureIDEi | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska5Light15GetIBLTextureIDEi(long param_1,int param_2)

{
  undefined8 *puVar1;
  long lVar2;
  
  lVar2 = *(long *)(param_1 + 0x418);
  if (lVar2 != 0) {
    puVar1 = (undefined8 *)(lVar2 + 0x11d0);
    if (param_2 != 0) {
      puVar1 = (undefined8 *)(lVar2 + 0x10);
    }
    return *puVar1;
  }
  return 0;
}

// ==== Aska::Light::SetIBLProfile(unsigned int)
// vaddr 0x213b9b4 | ghidra 0x223b9b4 | size 648 | symbol _ZN4Aska5Light13SetIBLProfileEj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Light13SetIBLProfileEj(long param_1,undefined4 param_2)

{
  char cVar1;
  bool bVar2;
  undefined *puVar3;
  long lVar4;
  long lVar5;
  int iVar6;
  
  lVar4 = *(long *)(param_1 + 0x418);
  *(char *)(param_1 + 0x424) = (char)param_2;
  if (lVar4 != 0) {
    switch(param_2) {
    case 0:
      if (*(char *)(lVar4 + 0xf72) != '\0') {
        lVar5 = *(long *)(lVar4 + 0x28);
        *(undefined1 *)(lVar4 + 0xf72) = 0;
        puVar3 = PTR__ZN4Aska14TextureManager18m_iCurrentUniqueIDE_02cba9f0;
        if (lVar5 != 0) {
          do {
            iVar6 = *(int *)puVar3;
            cVar1 = '\x01';
            bVar2 = (bool)ExclusiveMonitorPass(puVar3,0x10);
            if (bVar2) {
              *(int *)puVar3 = iVar6 + 1;
              cVar1 = ExclusiveMonitorsStatus();
            }
          } while (cVar1 != '\0');
          *(int *)(lVar5 + 0x7c) = iVar6 + 1;
        }
      }
      if (*(char *)(lVar4 + 0xf82) == '\x10') {
        return;
      }
      lVar5 = *(long *)(lVar4 + 0x28);
      *(undefined1 *)(lVar4 + 0xf82) = 0x10;
      puVar3 = PTR__ZN4Aska14TextureManager18m_iCurrentUniqueIDE_02cba9f0;
      if (lVar5 == 0) {
        return;
      }
      do {
        iVar6 = *(int *)puVar3 + 1;
        cVar1 = '\x01';
        bVar2 = (bool)ExclusiveMonitorPass(puVar3,0x10);
        if (bVar2) {
          *(int *)puVar3 = iVar6;
          cVar1 = ExclusiveMonitorsStatus();
        }
      } while (cVar1 != '\0');
      break;
    case 1:
      if (*(char *)(lVar4 + 0xf72) != '\x01') {
        lVar5 = *(long *)(lVar4 + 0x28);
        *(undefined1 *)(lVar4 + 0xf72) = 1;
        puVar3 = PTR__ZN4Aska14TextureManager18m_iCurrentUniqueIDE_02cba9f0;
        if (lVar5 != 0) {
          do {
            iVar6 = *(int *)puVar3;
            cVar1 = '\x01';
            bVar2 = (bool)ExclusiveMonitorPass(puVar3,0x10);
            if (bVar2) {
              *(int *)puVar3 = iVar6 + 1;
              cVar1 = ExclusiveMonitorsStatus();
            }
          } while (cVar1 != '\0');
          *(int *)(lVar5 + 0x7c) = iVar6 + 1;
        }
      }
      if (*(char *)(lVar4 + 0xf71) != '\0') {
        lVar5 = *(long *)(lVar4 + 0x28);
        *(undefined1 *)(lVar4 + 0xf71) = 0;
        puVar3 = PTR__ZN4Aska14TextureManager18m_iCurrentUniqueIDE_02cba9f0;
        if (lVar5 != 0) {
          do {
            iVar6 = *(int *)puVar3;
            cVar1 = '\x01';
            bVar2 = (bool)ExclusiveMonitorPass(puVar3,0x10);
            if (bVar2) {
              *(int *)puVar3 = iVar6 + 1;
              cVar1 = ExclusiveMonitorsStatus();
            }
          } while (cVar1 != '\0');
          *(int *)(lVar5 + 0x7c) = iVar6 + 1;
        }
      }
      if (*(char *)(lVar4 + 0xf82) == ' ') {
        return;
      }
      lVar5 = *(long *)(lVar4 + 0x28);
      *(undefined1 *)(lVar4 + 0xf82) = 0x20;
      puVar3 = PTR__ZN4Aska14TextureManager18m_iCurrentUniqueIDE_02cba9f0;
      if (lVar5 == 0) {
        return;
      }
      do {
        iVar6 = *(int *)puVar3 + 1;
        cVar1 = '\x01';
        bVar2 = (bool)ExclusiveMonitorPass(puVar3,0x10);
        if (bVar2) {
          *(int *)puVar3 = iVar6;
          cVar1 = ExclusiveMonitorsStatus();
        }
      } while (cVar1 != '\0');
      break;
    case 2:
      if (*(char *)(lVar4 + 0xf72) != '\x01') {
        lVar5 = *(long *)(lVar4 + 0x28);
        *(undefined1 *)(lVar4 + 0xf72) = 1;
        puVar3 = PTR__ZN4Aska14TextureManager18m_iCurrentUniqueIDE_02cba9f0;
        if (lVar5 != 0) {
          do {
            iVar6 = *(int *)puVar3;
            cVar1 = '\x01';
            bVar2 = (bool)ExclusiveMonitorPass(puVar3,0x10);
            if (bVar2) {
              *(int *)puVar3 = iVar6 + 1;
              cVar1 = ExclusiveMonitorsStatus();
            }
          } while (cVar1 != '\0');
          *(int *)(lVar5 + 0x7c) = iVar6 + 1;
        }
      }
      if (*(char *)(lVar4 + 0xf71) != '\x01') {
        lVar5 = *(long *)(lVar4 + 0x28);
        *(undefined1 *)(lVar4 + 0xf71) = 1;
        puVar3 = PTR__ZN4Aska14TextureManager18m_iCurrentUniqueIDE_02cba9f0;
        if (lVar5 != 0) {
          do {
            iVar6 = *(int *)puVar3;
            cVar1 = '\x01';
            bVar2 = (bool)ExclusiveMonitorPass(puVar3,0x10);
            if (bVar2) {
              *(int *)puVar3 = iVar6 + 1;
              cVar1 = ExclusiveMonitorsStatus();
            }
          } while (cVar1 != '\0');
          *(int *)(lVar5 + 0x7c) = iVar6 + 1;
        }
      }
      if (*(char *)(lVar4 + 0xf82) == '\x10') {
        return;
      }
      lVar5 = *(long *)(lVar4 + 0x28);
      *(undefined1 *)(lVar4 + 0xf82) = 0x10;
      puVar3 = PTR__ZN4Aska14TextureManager18m_iCurrentUniqueIDE_02cba9f0;
      if (lVar5 == 0) {
        return;
      }
      do {
        iVar6 = *(int *)puVar3 + 1;
        cVar1 = '\x01';
        bVar2 = (bool)ExclusiveMonitorPass(puVar3,0x10);
        if (bVar2) {
          *(int *)puVar3 = iVar6;
          cVar1 = ExclusiveMonitorsStatus();
        }
      } while (cVar1 != '\0');
      break;
    case 3:
      if (*(char *)(lVar4 + 0xf72) != '\x01') {
        lVar5 = *(long *)(lVar4 + 0x28);
        *(undefined1 *)(lVar4 + 0xf72) = 1;
        puVar3 = PTR__ZN4Aska14TextureManager18m_iCurrentUniqueIDE_02cba9f0;
        if (lVar5 != 0) {
          do {
            iVar6 = *(int *)puVar3;
            cVar1 = '\x01';
            bVar2 = (bool)ExclusiveMonitorPass(puVar3,0x10);
            if (bVar2) {
              *(int *)puVar3 = iVar6 + 1;
              cVar1 = ExclusiveMonitorsStatus();
            }
          } while (cVar1 != '\0');
          *(int *)(lVar5 + 0x7c) = iVar6 + 1;
        }
      }
      if (*(char *)(lVar4 + 0xf71) != '\x01') {
        lVar5 = *(long *)(lVar4 + 0x28);
        *(undefined1 *)(lVar4 + 0xf71) = 1;
        puVar3 = PTR__ZN4Aska14TextureManager18m_iCurrentUniqueIDE_02cba9f0;
        if (lVar5 != 0) {
          do {
            iVar6 = *(int *)puVar3;
            cVar1 = '\x01';
            bVar2 = (bool)ExclusiveMonitorPass(puVar3,0x10);
            if (bVar2) {
              *(int *)puVar3 = iVar6 + 1;
              cVar1 = ExclusiveMonitorsStatus();
            }
          } while (cVar1 != '\0');
          *(int *)(lVar5 + 0x7c) = iVar6 + 1;
        }
      }
      if (*(char *)(lVar4 + 0xf82) == ' ') {
        return;
      }
      lVar5 = *(long *)(lVar4 + 0x28);
      *(undefined1 *)(lVar4 + 0xf82) = 0x20;
      puVar3 = PTR__ZN4Aska14TextureManager18m_iCurrentUniqueIDE_02cba9f0;
      if (lVar5 == 0) {
        return;
      }
      do {
        iVar6 = *(int *)puVar3 + 1;
        cVar1 = '\x01';
        bVar2 = (bool)ExclusiveMonitorPass(puVar3,0x10);
        if (bVar2) {
          *(int *)puVar3 = iVar6;
          cVar1 = ExclusiveMonitorsStatus();
        }
      } while (cVar1 != '\0');
      break;
    default:
      goto code_r0x0223bc38;
    }
    *(int *)(lVar5 + 0x7c) = iVar6;
  }
code_r0x0223bc38:
  return;
}

// ==== Aska::Light::GetIBLTexture()
// vaddr 0x213bc3c | ghidra 0x223bc3c | size 120 | symbol _ZN4Aska5Light13GetIBLTextureEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska5Light13GetIBLTextureEv(long param_1)

{
  long lVar1;
  long lVar2;
  long lVar3;
  long lVar4;
  
  lVar4 = *(long *)(param_1 + 0x418);
  if ((lVar4 == 0) || (lVar2 = *(long *)(lVar4 + 0x11d0), lVar2 == 0)) {
    lVar3 = 0;
  }
  else {
    lVar3 = *(long *)(lVar4 + 0x11e0);
    if (lVar3 == 0) {
      lVar3 = *(long *)PTR__ZN4Aska6Global17m_pTextureManagerE_02cc19f0;
      lVar1 = lVar3 + 0xb0;
      Aska::CriticalSection::Enter() const(lVar1);
      lVar3 = Aska::TextureManager::QueryTextureEx(unsigned long, bool)(lVar3,lVar2,1);
      Aska::CriticalSection::Leave() const(lVar1);
      *(long *)(lVar4 + 0x11e0) = lVar3;
    }
  }
  return lVar3;
}

// ==== Aska::Light::GetIBLTextureUniqueID()
// vaddr 0x213bcb4 | ghidra 0x223bcb4 | size 124 | symbol _ZN4Aska5Light21GetIBLTextureUniqueIDEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZN4Aska5Light21GetIBLTextureUniqueIDEv(long param_1)

{
  long lVar1;
  undefined4 uVar2;
  long lVar3;
  long lVar4;
  long lVar5;
  
  lVar5 = *(long *)(param_1 + 0x418);
  if ((lVar5 == 0) || (lVar3 = *(long *)(lVar5 + 0x11d0), lVar3 == 0)) {
code_r0x0223bd1c:
    uVar2 = 0;
  }
  else {
    lVar4 = *(long *)(lVar5 + 0x11e0);
    if (lVar4 == 0) {
      lVar4 = *(long *)PTR__ZN4Aska6Global17m_pTextureManagerE_02cc19f0;
      lVar1 = lVar4 + 0xb0;
      Aska::CriticalSection::Enter() const(lVar1);
      lVar4 = Aska::TextureManager::QueryTextureEx(unsigned long, bool)(lVar4,lVar3,1);
      Aska::CriticalSection::Leave() const(lVar1);
      *(long *)(lVar5 + 0x11e0) = lVar4;
      if (lVar4 == 0) goto code_r0x0223bd1c;
    }
    uVar2 = *(undefined4 *)(lVar4 + 0x7c);
  }
  return uVar2;
}

// ==== Aska::Light::GetIBLLodOffset() const
// vaddr 0x213bd30 | ghidra 0x223bd30 | size 24 | symbol _ZNK4Aska5Light15GetIBLLodOffsetEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK4Aska5Light15GetIBLLodOffsetEv(long param_1)

{
  if (*(long *)(param_1 + 0x418) != 0) {
    return *(undefined4 *)(*(long *)(param_1 + 0x418) + 0xf7c);
  }
  return 0;
}

// ==== Aska::Light::DownconvertIBL(int, bool)
// vaddr 0x213bd48 | ghidra 0x223bd48 | size 1056 | symbol _ZN4Aska5Light14DownconvertIBLEib | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 _ZN4Aska5Light14DownconvertIBLEib(long *param_1,uint param_2,uint param_3)

{
  long *plVar1;
  float fVar2;
  ulong uVar3;
  ulong uVar4;
  ulong uVar5;
  undefined8 uVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  undefined1 auStack_50 [16];
  
  if ((param_3 & 1) != 0) {
    return 0;
  }
  plVar1 = (long *)param_1[0x81];
  if (plVar1 == (long *)0x0) {
    fVar2 = ABS(*(float *)(param_1 + 0x72)) +
            *(float *)(param_1 + 0x74) * *(float *)(param_1 + 0x14);
    fVar7 = ABS((float)*(undefined8 *)((long)param_1 + 0x394)) +
            (float)*(undefined8 *)((long)param_1 + 0x3a4) *
            (float)*(undefined8 *)((long)param_1 + 0xa4);
    fVar8 = ABS((float)((ulong)*(undefined8 *)((long)param_1 + 0x394) >> 0x20)) +
            (float)((ulong)*(undefined8 *)((long)param_1 + 0x3a4) >> 0x20) *
            (float)((ulong)*(undefined8 *)((long)param_1 + 0xa4) >> 0x20);
    fVar7 = fVar2 * fVar2 + fVar7 * fVar7 + fVar8 * fVar8;
    fVar2 = SQRT(fVar7);
    if (NAN(fVar2)) {
      fVar2 = (float)sqrtf(fVar7);
    }
    if (*(float *)((long)param_1 + 700) == fVar2) goto code_r0x0223be44;
  }
  else {
    if ((*(byte *)(param_1 + 0x25) & 1) != 0) {
      (**(code **)(*param_1 + 0xa8))(param_1);
    }
    if ((*(byte *)(plVar1 + 0x25) & 1) != 0) {
      (**(code **)(*plVar1 + 0xa8))(plVar1);
    }
    fVar2 = *(float *)((long)param_1 + 0x4c) - *(float *)((long)plVar1 + 0x4c);
    fVar7 = *(float *)((long)param_1 + 0x5c) - *(float *)((long)plVar1 + 0x5c);
    fVar8 = *(float *)((long)param_1 + 0x6c) - *(float *)((long)plVar1 + 0x6c);
    fVar2 = SQRT(fVar2 * fVar2 + fVar7 * fVar7 + fVar8 * fVar8);
    if (NAN(fVar2)) {
      fVar2 = (float)sqrtf();
    }
    fVar8 = *(float *)(plVar1 + 0x14) * *(float *)(plVar1 + 0x14) +
            *(float *)((long)plVar1 + 0xa4) * *(float *)((long)plVar1 + 0xa4) +
            *(float *)(plVar1 + 0x15) * *(float *)(plVar1 + 0x15);
    fVar7 = SQRT(fVar8);
    if (NAN(fVar7)) {
      fVar7 = (float)sqrtf(fVar8);
    }
    fVar2 = fVar2 + fVar7;
    if (*(float *)((long)param_1 + 700) == fVar2) goto code_r0x0223be44;
  }
  *(float *)((long)param_1 + 700) = fVar2;
  *(float *)(param_1 + 0x57) = fVar2;
  Aska::Light::CalcAttenuation()(param_1);
code_r0x0223be44:
  if (param_2 == 4) {
    fVar2 = SQRT(*(float *)(param_1 + 0x4a) * *(float *)(param_1 + 0x4a) +
                 *(float *)((long)param_1 + 0x254) * *(float *)((long)param_1 + 0x254) +
                 *(float *)(param_1 + 0x4b) * *(float *)(param_1 + 0x4b));
    uVar3 = (ulong)(uint)fVar2;
    if (NAN(fVar2)) {
      uVar3 = sqrtf();
    }
    fVar7 = *(float *)(param_1 + 0x4c) * *(float *)(param_1 + 0x4c) +
            *(float *)((long)param_1 + 0x264) * *(float *)((long)param_1 + 0x264) +
            *(float *)(param_1 + 0x4d) * *(float *)(param_1 + 0x4d);
    fVar2 = SQRT(fVar7);
    if (NAN(fVar2)) {
      fVar2 = (float)sqrtf(fVar7);
    }
    fVar7 = *(float *)(param_1 + 0x4e) * *(float *)(param_1 + 0x4e) +
            *(float *)((long)param_1 + 0x274) * *(float *)((long)param_1 + 0x274) +
            *(float *)(param_1 + 0x4f) * *(float *)(param_1 + 0x4f);
    fVar8 = SQRT(fVar7);
    uVar4 = (ulong)(uint)fVar8;
    fVar2 = fVar2 + _UNK_027edb40;
    if (NAN(fVar8)) {
      uVar4 = sqrtf(fVar7);
    }
    fVar9 = (float)uVar3;
    fVar10 = (float)uVar4;
    fVar8 = fVar9 * fVar9 + fVar2 * fVar2 + fVar10 * fVar10;
    fVar7 = SQRT(fVar8);
    if (NAN(fVar7)) {
      fVar7 = (float)sqrtf(fVar8);
    }
    if (_UNK_027e519c <= fVar7) {
      fVar7 = 1.0 / fVar7;
      uVar3 = (ulong)(uint)(fVar9 * fVar7);
      fVar2 = fVar2 * fVar7;
      uVar4 = (ulong)(uint)(fVar10 * fVar7);
    }
    fVar12 = (float)uVar3;
    fVar13 = (float)uVar4;
    fVar7 = fVar12 * *(float *)(param_1 + 0x4a) + fVar2 * *(float *)(param_1 + 0x4c) +
            fVar13 * *(float *)(param_1 + 0x4e);
    fVar11 = *(float *)(param_1 + 0x46);
    fVar8 = fVar12 * *(float *)((long)param_1 + 0x254) + fVar2 * *(float *)((long)param_1 + 0x264) +
            fVar13 * *(float *)((long)param_1 + 0x274);
    fVar9 = fVar12 * *(float *)(param_1 + 0x4b) + fVar2 * *(float *)(param_1 + 0x4d) +
            fVar13 * *(float *)(param_1 + 0x4f);
    fVar10 = *(float *)(param_1 + 0x47);
    *(float *)((long)param_1 + 0x284) =
         (fVar8 + *(float *)((long)param_1 + 0x244)) * *(float *)((long)param_1 + 0x234);
    *(undefined4 *)((long)param_1 + 0x28c) = *(undefined4 *)((long)param_1 + 0x24c);
    *(float *)(param_1 + 0x46) = (*(float *)(param_1 + 0x48) - fVar7) * fVar11;
    *(float *)((long)param_1 + 0x234) =
         (*(float *)((long)param_1 + 0x244) - fVar8) * *(float *)((long)param_1 + 0x234);
    *(float *)(param_1 + 0x47) = (*(float *)(param_1 + 0x49) - fVar9) * fVar10;
    *(float *)(param_1 + 0x50) = (fVar7 + *(float *)(param_1 + 0x48)) * fVar11;
    *(float *)(param_1 + 0x51) = (fVar9 + *(float *)(param_1 + 0x49)) * fVar10;
    if ((fVar12 * fVar12 == 0.0) && (fVar13 * fVar13 == 0.0)) {
      if (0.0 <= fVar2) {
        uVar6 = 0;
        uVar5 = (ulong)_UNK_027f782c;
        if (fVar2 <= 0.0) {
          uVar5 = 0;
        }
      }
      else {
        uVar5 = (ulong)_UNK_027f7284;
        uVar6 = 0;
      }
    }
    else {
      fVar7 = SQRT(fVar12 * fVar12 + fVar13 * fVar13);
      uVar5 = (ulong)(uint)fVar7;
      if (NAN(fVar7)) {
        uVar5 = sqrtf();
      }
      uVar5 = atan2f(-fVar2,uVar5);
      uVar6 = atan2f(uVar3,uVar4);
    }
    Aska::Quaternion::CreateFromEuler(float, float, float, EnumRotateType)(uVar5,uVar6,0,auStack_50,0);
    (**(code **)(*param_1 + 0xe8))(param_1,auStack_50);
  }
  else {
    (**(code **)(*param_1 + 0xd8))(0,0,0,param_1);
    if (8 < param_2) {
      return 1;
    }
  }
  *(char *)((long)param_1 + 0x2a1) = (char)param_2;
  return 1;
}

// ==== Aska::Light::EnableDebugGuide(bool)
// vaddr 0x213c168 | ghidra 0x223c168 | size 4 | symbol _ZN4Aska5Light16EnableDebugGuideEb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Light16EnableDebugGuideEb(void)

{
  return;
}

// ==== Aska::Light::EnableTileDebug(bool)
// vaddr 0x213c16c | ghidra 0x223c16c | size 4 | symbol _ZN4Aska5Light15EnableTileDebugEb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Light15EnableTileDebugEb(void)

{
  return;
}

// ==== Aska::Light::~Light()
// vaddr 0x213c170 | ghidra 0x223c170 | size 236 | symbol _ZN4Aska5LightD2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5LightD1Ev(long *param_1)

{
  long lVar1;
  ulong uVar2;
  undefined8 uVar3;
  
  *param_1 = (long)(PTR__ZTVN4Aska5LightE_02cc3a30 + 0x10);
  if (param_1[0x83] != 0) {
    if (*(uint *)(param_1 + 0x84) != 0) {
      uVar2 = (ulong)*(uint *)(param_1 + 0x84) | 0x200000000000000;
      uVar3 = *(undefined8 *)(*(long *)PTR__ZN4Aska6Global16m_pObjectManagerE_02cc4688 + 0x45e0);
      lVar1 = Aska::ProceduralTextureManager::GetProcTexEnv(unsigned long)(uVar3,uVar2);
      if (lVar1 != 0) {
        Aska::ProceduralTextureManager::Unregister(unsigned long)(uVar3,uVar2);
        Aska::DiffuseCubeMap::DeleteTexture()(param_1[0x83]);
      }
    }
    if ((long *)param_1[0x83] != (long *)0x0) {
      (**(code **)(*(long *)param_1[0x83] + 0x28))();
    }
    param_1[0x83] = 0;
  }
  *param_1 = (long)(PTR__ZTVN4Aska12AimingObjectE_02cc4418 + 0x10);
  if (param_1[0x3c] != 0) {
    *(long *)(param_1[0x3c] + 0x10) = param_1[0x3d];
  }
  if ((long *)param_1[0x3d] != (long *)0x0) {
    *(long *)param_1[0x3d] = param_1[0x3c];
    param_1[0x3d] = 0;
  }
  param_1[0x3c] = 0;
  if (param_1[0x39] != 0) {
    *(long *)(param_1[0x39] + 0x10) = param_1[0x3a];
  }
  if ((long *)param_1[0x3a] != (long *)0x0) {
    *(long *)param_1[0x3a] = param_1[0x39];
    param_1[0x3a] = 0;
  }
  param_1[0x39] = 0;
  (*(code *)PTR__ZN4Aska18HierarchicalObjectD2Ev_02ca75e8)(param_1);
  return;
}

// ==== Aska::Light::UnregisterDiffuseCubeMap()
// vaddr 0x213c25c | ghidra 0x223c25c | size 104 | symbol _ZN4Aska5Light24UnregisterDiffuseCubeMapEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Light24UnregisterDiffuseCubeMapEv(long param_1)

{
  long lVar1;
  ulong uVar2;
  undefined8 uVar3;
  
  if ((*(long *)(param_1 + 0x418) != 0) && (*(uint *)(param_1 + 0x420) != 0)) {
    uVar2 = (ulong)*(uint *)(param_1 + 0x420) | 0x200000000000000;
    uVar3 = *(undefined8 *)(*(long *)PTR__ZN4Aska6Global16m_pObjectManagerE_02cc4688 + 0x45e0);
    lVar1 = Aska::ProceduralTextureManager::GetProcTexEnv(unsigned long)(uVar3,uVar2);
    if (lVar1 != 0) {
      Aska::ProceduralTextureManager::Unregister(unsigned long)(uVar3,uVar2);
      (*(code *)PTR__ZN4Aska14DiffuseCubeMap13DeleteTextureEv_02ca58e8)
                (*(undefined8 *)(param_1 + 0x418));
      return;
    }
  }
  return;
}

// ==== Aska::Light::~Light()
// vaddr 0x213c2c4 | ghidra 0x223c2c4 | size 24 | symbol _ZN4Aska5LightD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5LightD0Ev(undefined8 param_1)

{
  Aska::Light::~Light()();
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::Light::DeleteThis(Aska::DeleteManager*)
// vaddr 0x213c2dc | ghidra 0x223c2dc | size 108 | symbol _ZN4Aska5Light10DeleteThisEPNS_13DeleteManagerE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Light10DeleteThisEPNS_13DeleteManagerE(undefined8 param_1)

{
  char cVar1;
  undefined8 uVar2;
  
  if (*(long *)PTR__ZN4Aska6Global16m_pObjectManagerE_02cc4688 != 0) {
    cVar1 = *(char *)(*(long *)PTR__ZN4Aska6Global16m_pObjectManagerE_02cc4688 + 0x3f09);
    if (cVar1 == '\x01') {
      uVar2 = 0;
      goto code_r0x011ca1d0;
    }
    if (cVar1 == '\x02') {
      (*(code *)PTR__ZN4Aska4Task10DeleteThisEPNS_13DeleteManagerE_02cac0f0)(param_1);
      return;
    }
  }
  uVar2 = 1;
code_r0x011ca1d0:
  (*(code *)PTR__ZN4Aska13DeleteManager7AddMainEPvhhPNS_14IDeleteHandlerE_02c9d0d8)
            (PTR__ZN4Aska6Global21m_systemDeleteManagerE_02cb77c0,param_1,2,uVar2,0);
  return;
}

// ==== Aska::Light::Get(unsigned long, void*) const
// vaddr 0x213c348 | ghidra 0x223c348 | size 1276 | symbol _ZNK4Aska5Light3GetEmPv | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 _ZNK4Aska5Light3GetEmPv(long param_1,ulong param_2,float *param_3)

{
  byte bVar1;
  bool bVar2;
  ulong uVar3;
  float fVar4;
  undefined8 uVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  
  uVar3 = Aska::AimingObject::Get(unsigned long, void*) const();
  if ((uVar3 & 1) != 0) {
    return 1;
  }
  if ((param_2 & 0xffff00000000) != 0) {
code_r0x0223c378:
    return 0;
  }
  switch((uint)param_2 & 0xffff) {
  case 0x10:
    *param_3 = *(float *)(param_1 + 0x230);
    param_3[1] = *(float *)(param_1 + 0x234);
    param_3[2] = *(float *)(param_1 + 0x238);
    fVar4 = *(float *)(param_1 + 0x23c);
    goto code_r0x0223c720;
  case 0x11:
    fVar4 = *(float *)(param_1 + 0x23c);
    break;
  case 0x12:
    fVar4 = *(float *)(param_1 + 700);
    break;
  case 0x13:
    *param_3 = *(float *)(param_1 + 0x210);
    param_3[1] = *(float *)(param_1 + 0x214);
    param_3[2] = *(float *)(param_1 + 0x218);
    fVar4 = *(float *)(param_1 + 0x21c);
    goto code_r0x0223c720;
  case 0x14:
    fVar4 = *(float *)(param_1 + 0x2d4);
    break;
  case 0x15:
    fVar4 = *(float *)(param_1 + 0x2d8);
    break;
  case 0x16:
    *param_3 = *(float *)(param_1 + 0x280);
    param_3[1] = *(float *)(param_1 + 0x284);
    param_3[2] = *(float *)(param_1 + 0x288);
    fVar4 = *(float *)(param_1 + 0x28c);
    goto code_r0x0223c720;
  case 0x17:
    fVar4 = (float)(uint)*(byte *)(param_1 + 0x2a1);
    break;
  case 0x18:
    bVar2 = (bool)(*(byte *)(param_1 + 0x2a5) & 1);
    goto code_r0x0223c798;
  case 0x19:
  case 0x5e:
    *(byte *)param_3 = 0;
    return 1;
  case 0x1a:
    uVar5 = *(undefined8 *)(param_1 + 0x2a8);
    goto code_r0x0223c63c;
  case 0x1b:
    bVar2 = (bool)((byte)(*(ushort *)(param_1 + 0x2a5) >> 3) & 1);
    goto code_r0x0223c798;
  case 0x1c:
  case 0x4c:
    fVar4 = *(float *)(param_1 + 0x2c4);
    break;
  case 0x1d:
    fVar4 = (float)(uint)*(byte *)(param_1 + 0x2a0);
    break;
  default:
    goto code_r0x0223c378;
  case 0x1f:
  case 0x20:
  case 0x34:
  case 0x3f:
    goto code_r0x0223c378;
  case 0x21:
    bVar2 = (bool)((byte)(*(ushort *)(param_1 + 0x2a5) >> 6) & 1);
    goto code_r0x0223c798;
  case 0x27:
    bVar2 = *(char *)(param_1 + 0x2a2) != '\0';
    goto code_r0x0223c798;
  case 0x28:
    bVar2 = false;
    if (*(long *)(param_1 + 0x18) != 0) {
      bVar2 = *(long *)(*(long *)(param_1 + 0x18) + 0x2ff0) == param_1;
    }
    goto code_r0x0223c798;
  case 0x29:
    *param_3 = *(float *)(param_1 + 0x240);
    param_3[1] = *(float *)(param_1 + 0x244);
    param_3[2] = *(float *)(param_1 + 0x248);
    fVar4 = *(float *)(param_1 + 0x24c);
    goto code_r0x0223c720;
  case 0x2a:
    *param_3 = *(float *)(param_1 + 0x250);
    param_3[1] = *(float *)(param_1 + 0x254);
    param_3[2] = *(float *)(param_1 + 600);
    fVar4 = *(float *)(param_1 + 0x25c);
    goto code_r0x0223c720;
  case 0x2b:
    *param_3 = *(float *)(param_1 + 0x260);
    param_3[1] = *(float *)(param_1 + 0x264);
    param_3[2] = *(float *)(param_1 + 0x268);
    fVar4 = *(float *)(param_1 + 0x26c);
    goto code_r0x0223c720;
  case 0x2c:
    *param_3 = *(float *)(param_1 + 0x270);
    param_3[1] = *(float *)(param_1 + 0x274);
    param_3[2] = *(float *)(param_1 + 0x278);
    fVar4 = *(float *)(param_1 + 0x27c);
    goto code_r0x0223c720;
  case 0x2d:
    bVar2 = (bool)(*(byte *)(param_1 + 0x2a6) & 1);
    goto code_r0x0223c798;
  case 0x2e:
    bVar2 = (bool)((byte)(*(ushort *)(param_1 + 0x2a5) >> 7) & 1);
    goto code_r0x0223c798;
  case 0x2f:
    bVar2 = (bool)((byte)((ushort)*(undefined2 *)(param_1 + 0x2a5) >> 0xb) & 1);
    goto code_r0x0223c798;
  case 0x30:
    fVar4 = (float)(int)*(short *)(param_1 + 0x2e6);
    break;
  case 0x31:
    fVar4 = *(float *)(param_1 + 0x2f0);
    break;
  case 0x32:
    fVar4 = *(float *)(param_1 + 0x2f4);
    break;
  case 0x33:
    fVar4 = *(float *)(param_1 + 0x2f8);
    break;
  case 0x35:
    bVar2 = (bool)((byte)((ushort)*(undefined2 *)(param_1 + 0x2a5) >> 0xc) & 1);
    goto code_r0x0223c798;
  case 0x36:
    fVar4 = (float)Aska::Light::GetIlluminance() const(param_1);
    goto code_r0x0223c838;
  case 0x37:
    bVar1 = *(byte *)(param_1 + 0x2a1);
    if ((bVar1 & 0xfc) == 4) {
      if (bVar1 == 5) {
        fVar8 = *(float *)(param_1 + 0x240);
        fVar7 = *(float *)(param_1 + 0x244);
        fVar6 = *(float *)(param_1 + 0x248);
      }
      else {
        if (bVar1 != 4) goto code_r0x0223c7c4;
        fVar8 = (*(float *)(param_1 + 0x230) + *(float *)(param_1 + 0x280)) * 0.5;
        fVar7 = (*(float *)(param_1 + 0x234) + *(float *)(param_1 + 0x284)) * 0.5;
        fVar6 = (*(float *)(param_1 + 0x238) + *(float *)(param_1 + 0x288)) * 0.5;
      }
    }
    else {
code_r0x0223c7c4:
      fVar8 = *(float *)(param_1 + 0x230);
      fVar7 = *(float *)(param_1 + 0x234);
      fVar6 = *(float *)(param_1 + 0x238);
    }
    fVar4 = *(float *)(param_1 + 0x23c) * _UNK_029cc0f4;
    if (4 < bVar1 - 4) {
      fVar4 = *(float *)(param_1 + 0x23c);
    }
    fVar4 = fVar4 * (fVar6 * _UNK_029cc0ec + fVar7 * _UNK_029cc0e8 + fVar8 * _UNK_029cc0e4) *
                    _UNK_029cc0f0;
    goto code_r0x0223c838;
  case 0x38:
    fVar4 = (float)Aska::Light::GetColorTemperature() const(param_1);
    goto code_r0x0223c838;
  case 0x39:
    fVar4 = 1.0;
    break;
  case 0x3b:
    uVar5 = 0;
    if (*(long *)(param_1 + 0x418) != 0) {
      uVar5 = *(undefined8 *)(*(long *)(param_1 + 0x418) + 0x11d0);
    }
code_r0x0223c63c:
    *(undefined8 *)param_3 = uVar5;
    return 1;
  case 0x3c:
    *param_3 = *(float *)(param_1 + 0x390);
    param_3[1] = *(float *)(param_1 + 0x394);
    param_3[2] = *(float *)(param_1 + 0x398);
    fVar4 = *(float *)(param_1 + 0x39c);
    goto code_r0x0223c720;
  case 0x3d:
    *param_3 = *(float *)(param_1 + 0x3a0);
    param_3[1] = *(float *)(param_1 + 0x3a4);
    param_3[2] = *(float *)(param_1 + 0x3a8);
    fVar4 = *(float *)(param_1 + 0x3ac);
    goto code_r0x0223c720;
  case 0x3e:
    fVar4 = 0.0;
    if (*(long *)(param_1 + 0x418) != 0) {
      fVar4 = (float)(uint)*(byte *)(*(long *)(param_1 + 0x418) + 0xf72);
    }
    break;
  case 0x40:
    *param_3 = *(float *)(param_1 + 0x3e0);
    param_3[1] = *(float *)(param_1 + 0x3e4);
    param_3[2] = *(float *)(param_1 + 1000);
    fVar4 = *(float *)(param_1 + 0x3ec);
    goto code_r0x0223c720;
  case 0x41:
    *param_3 = *(float *)(param_1 + 0x3f0);
    param_3[1] = *(float *)(param_1 + 0x3f4);
    param_3[2] = *(float *)(param_1 + 0x3f8);
    fVar4 = *(float *)(param_1 + 0x3fc);
code_r0x0223c720:
    param_3[3] = fVar4;
    return 1;
  case 0x42:
    fVar4 = 0.0;
    if (*(long *)(param_1 + 0x418) != 0) {
      fVar4 = (float)(uint)*(byte *)(*(long *)(param_1 + 0x418) + 0xf73);
    }
    break;
  case 0x43:
    fVar4 = 0.0;
    if (*(long *)(param_1 + 0x418) != 0) {
      fVar4 = (float)(uint)*(byte *)(*(long *)(param_1 + 0x418) + 0xf71);
    }
    break;
  case 0x44:
    if (*(long *)(param_1 + 0x418) != 0) {
      fVar4 = *(float *)(*(long *)(param_1 + 0x418) + 0xf74);
      goto code_r0x0223c838;
    }
    goto code_r0x0223c7bc;
  case 0x45:
    if (*(long *)(param_1 + 0x418) != 0) {
      fVar4 = *(float *)(*(long *)(param_1 + 0x418) + 0xf78);
      goto code_r0x0223c838;
    }
code_r0x0223c7bc:
    fVar4 = 0.0;
code_r0x0223c838:
    *param_3 = fVar4;
    return 1;
  case 0x46:
    fVar4 = 0.0;
    if (*(long *)(param_1 + 0x418) != 0) {
      fVar4 = (float)(uint)(*(char *)(*(long *)(param_1 + 0x418) + 0xf82) != ' ');
    }
    break;
  case 0x47:
    fVar4 = (float)(uint)*(byte *)(param_1 + 0x424);
    break;
  case 0x48:
    *param_3 = (float)*(undefined8 *)(param_1 + 0x2a8);
    return 1;
  case 0x4a:
    bVar2 = (bool)((byte)((ushort)*(undefined2 *)(param_1 + 0x2a5) >> 0xd) & 1);
    goto code_r0x0223c798;
  case 0x4b:
    fVar4 = *(float *)(param_1 + 0x2cc);
    break;
  case 0x4d:
    fVar4 = (float)(uint)*(ushort *)(param_1 + 0x2e4);
    break;
  case 0x4e:
    fVar4 = *(float *)(param_1 + 0x2d0);
    break;
  case 0x4f:
    fVar4 = *(float *)(param_1 + 0x2c8);
    break;
  case 0x50:
    bVar2 = (bool)((byte)((ushort)*(undefined2 *)(param_1 + 0x2a5) >> 0xe) & 1);
    goto code_r0x0223c798;
  case 0x51:
    fVar4 = 2.8026e-45;
    if (*(char *)(param_1 + 0x2a1) != '\x04') {
      fVar4 = (float)(uint)(*(char *)(param_1 + 0x2a1) == '\x05');
    }
    break;
  case 0x52:
    bVar2 = (bool)((byte)((ushort)*(undefined2 *)(param_1 + 0x2a5) >> 9) & 1);
    goto code_r0x0223c798;
  case 0x53:
    bVar2 = (bool)((byte)((ushort)*(undefined2 *)(param_1 + 0x2a5) >> 10) & 1);
code_r0x0223c798:
    *(bool *)param_3 = bVar2;
    return 1;
  case 0x54:
    fVar4 = *(float *)(param_1 + 0x304);
    break;
  case 0x5d:
    fVar4 = *(float *)(param_1 + 0x2b8);
  }
  *param_3 = fVar4;
code_r0x0223c378:
  return 1;
}

// ==== Aska::Light::GetIlluminance() const
// vaddr 0x213c844 | ghidra 0x223c844 | size 604 | symbol _ZNK4Aska5Light14GetIlluminanceEv | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float _ZNK4Aska5Light14GetIlluminanceEv(long param_1)

{
  byte bVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  
  fVar2 = 1.0 / (*(float *)(param_1 + 0x220) + *(float *)(param_1 + 0x224) * _UNK_027e5198 +
                *(float *)(param_1 + 0x228) * _UNK_027e6ae0) - *(float *)(param_1 + 0x22c);
  if (fVar2 < 0.0) {
    fVar2 = 0.0;
  }
  fVar4 = 1.0;
  if (fVar2 + -1.0 < 0.0) {
    fVar4 = fVar2;
  }
  if (_UNK_027e519c <= fVar4) {
    bVar1 = *(byte *)(param_1 + 0x2a1);
    if ((bVar1 & 0xfc) == 4) {
      if (bVar1 == 5) {
        fVar2 = *(float *)(param_1 + 0x240);
        fVar5 = *(float *)(param_1 + 0x244);
        fVar6 = *(float *)(param_1 + 0x248);
        goto code_r0x0223ca40;
      }
      if (bVar1 == 4) {
        fVar2 = (*(float *)(param_1 + 0x230) + *(float *)(param_1 + 0x280)) * 0.5;
        fVar5 = (*(float *)(param_1 + 0x234) + *(float *)(param_1 + 0x284)) * 0.5;
        fVar6 = (*(float *)(param_1 + 0x238) + *(float *)(param_1 + 0x288)) * 0.5;
        goto code_r0x0223ca40;
      }
    }
    fVar2 = *(float *)(param_1 + 0x230);
    fVar5 = *(float *)(param_1 + 0x234);
    fVar6 = *(float *)(param_1 + 0x238);
code_r0x0223ca40:
    fVar3 = *(float *)(param_1 + 0x23c) * _UNK_029cc0f4;
    if (4 < bVar1 - 4) {
      fVar3 = *(float *)(param_1 + 0x23c);
    }
    return fVar4 * fVar3 * (fVar6 * _UNK_029cc0ec + fVar5 * _UNK_029cc0e8 + fVar2 * _UNK_029cc0e4) *
                           _UNK_029cc0f0;
  }
  bVar1 = *(byte *)(param_1 + 0x2a1);
  fVar2 = 1.0 / (*(float *)(param_1 + 0x220) + *(float *)(param_1 + 0x224) * _UNK_027ebdd8 +
                *(float *)(param_1 + 0x228) * _UNK_029cc0f8) - *(float *)(param_1 + 0x22c);
  if (fVar2 < 0.0) {
    fVar2 = 0.0;
  }
  fVar4 = 1.0;
  if (fVar2 + -1.0 < 0.0) {
    fVar4 = fVar2;
  }
  if ((bVar1 & 0xfc) == 4) {
    if (bVar1 == 5) {
      fVar6 = *(float *)(param_1 + 0x240);
      fVar5 = *(float *)(param_1 + 0x244);
      fVar2 = *(float *)(param_1 + 0x248);
      goto code_r0x0223c9c4;
    }
    if (bVar1 == 4) {
      fVar6 = (*(float *)(param_1 + 0x230) + *(float *)(param_1 + 0x280)) * 0.5;
      fVar5 = (*(float *)(param_1 + 0x234) + *(float *)(param_1 + 0x284)) * 0.5;
      fVar2 = (*(float *)(param_1 + 0x238) + *(float *)(param_1 + 0x288)) * 0.5;
      goto code_r0x0223c9c4;
    }
  }
  fVar6 = *(float *)(param_1 + 0x230);
  fVar5 = *(float *)(param_1 + 0x234);
  fVar2 = *(float *)(param_1 + 0x238);
code_r0x0223c9c4:
  fVar3 = *(float *)(param_1 + 0x23c) * _UNK_029cc0f4;
  if (4 < bVar1 - 4) {
    fVar3 = *(float *)(param_1 + 0x23c);
  }
  fVar3 = fVar3 * (fVar2 * _UNK_029cc0ec + fVar5 * _UNK_029cc0e8 + fVar6 * _UNK_029cc0e4) *
                  _UNK_029cc0f0;
  if (fVar4 < _UNK_027e519c) {
    return fVar3;
  }
  return fVar4 * fVar3 * 0.25;
}

// ==== Aska::Light::GetColorTemperature() const
// vaddr 0x213caa0 | ghidra 0x223caa0 | size 624 | symbol _ZNK4Aska5Light19GetColorTemperatureEv | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float _ZNK4Aska5Light19GetColorTemperatureEv(long param_1)

{
  byte bVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  undefined8 uVar9;
  undefined8 uVar10;
  long lVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  float fVar19;
  float fVar20;
  float fVar21;
  float fVar22;
  undefined8 uVar23;
  float fVar24;
  float fVar25;
  
  uVar10 = _UNK_029cc268;
  uVar9 = _UNK_029cc260;
  fVar8 = _UNK_029c9b90;
  fVar7 = _UNK_029c9b8c;
  fVar6 = _UNK_029c9b88;
  fVar5 = _UNK_029c9b7c;
  fVar4 = _UNK_029c9b70;
  fVar3 = _UNK_029c9b6c;
  fVar2 = _UNK_02961b98;
  bVar1 = *(byte *)(param_1 + 0x2a1);
  if ((bVar1 & 0xfc) == 4) {
    if (bVar1 == 5) {
      uVar23 = *(undefined8 *)(param_1 + 0x240);
      fVar16 = *(float *)(param_1 + 0x248);
      goto code_r0x0223cb00;
    }
    if (bVar1 == 4) {
      uVar23 = CONCAT44(((float)((ulong)*(undefined8 *)(param_1 + 0x230) >> 0x20) +
                        (float)((ulong)*(undefined8 *)(param_1 + 0x280) >> 0x20)) * 0.5,
                        ((float)*(undefined8 *)(param_1 + 0x230) +
                        (float)*(undefined8 *)(param_1 + 0x280)) * 0.5);
      fVar16 = (*(float *)(param_1 + 0x238) + *(float *)(param_1 + 0x288)) * 0.5;
      goto code_r0x0223cb00;
    }
  }
  uVar23 = *(undefined8 *)(param_1 + 0x230);
  fVar16 = *(float *)(param_1 + 0x238);
code_r0x0223cb00:
  fVar15 = (float)((ulong)uVar23 >> 0x20);
  fVar19 = 1.0 / ((float)uVar23 + fVar15 + fVar16);
  fVar20 = (float)uVar23 * fVar19;
  fVar16 = fVar16 * fVar19;
  fVar22 = _UNK_029cc0fc;
  if (_UNK_027e519c <= ABS(fVar20 - fVar16)) {
    uVar23 = NEON_fmov(0xbf800000,4);
    lVar11 = (ulong)(fVar16 < fVar20) * 4;
    fVar25 = *(float *)(&UNK_029cc250 + lVar11);
    fVar21 = *(float *)(&UNK_029cc258 + lVar11);
    fVar12 = _UNK_029cc100;
    fVar24 = _UNK_027e5198;
    fVar22 = fVar21;
    while( true ) {
      fVar13 = (float)expf(fVar4 / (fVar22 * fVar3));
      fVar14 = (float)expf(fVar4 / (fVar22 * fVar5));
      fVar17 = (float)uVar10 / ((fVar13 + (float)uVar23) * (float)uVar9);
      fVar18 = (float)((ulong)uVar10 >> 0x20) /
               ((fVar14 + (float)((ulong)uVar23 >> 0x20)) * (float)((ulong)uVar9 >> 0x20));
      fVar13 = (float)expf(fVar4 / (fVar22 * fVar6));
      fVar13 = fVar8 / ((fVar13 + -1.0) * fVar7);
      fVar14 = 1.0 / (fVar17 + fVar18 + fVar13);
      fVar17 = fVar20 - fVar17 * fVar14;
      fVar18 = fVar15 * fVar19 - fVar18 * fVar14;
      fVar13 = fVar16 - fVar13 * fVar14;
      fVar13 = fVar13 * fVar13 + fVar17 * fVar17 + fVar18 * fVar18;
      if (((fVar12 < fVar13) && (fVar24 = fVar24 * -0.5, ABS(fVar24) < 2.0)) ||
         (((fVar25 <= fVar22 + fVar24 || (fVar22 + fVar24 < fVar21)) &&
          (fVar24 = fVar24 * fVar2, ABS(fVar24) < 2.0)))) break;
      fVar22 = fVar22 + fVar24;
      fVar12 = fVar13;
    }
  }
  return fVar22;
}

// ==== Aska::Light::Set(unsigned long, void const*)
// vaddr 0x213cd10 | ghidra 0x223cd10 | size 2632 | symbol _ZN4Aska5Light3SetEmPKv | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 _ZN4Aska5Light3SetEmPKv(long param_1,ulong param_2,float *param_3)

{
  uint3 *puVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  byte bVar6;
  bool bVar7;
  undefined *puVar8;
  ulong uVar9;
  long lVar10;
  ushort uVar11;
  uint uVar12;
  long lVar13;
  char cVar14;
  int iVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  float fVar19;
  
  uVar9 = Aska::AimingObject::Set(unsigned long, void const*)();
  fVar16 = _UNK_027e519c;
  if ((uVar9 & 1) != 0) {
    return 1;
  }
  if ((param_2 & 0xffff00000000) != 0) {
code_r0x0223cd44:
    return 0;
  }
  switch((uint)param_2 & 0xffff) {
  case 0x10:
    *(float *)(param_1 + 0x230) = *param_3;
    *(float *)(param_1 + 0x234) = param_3[1];
    *(float *)(param_1 + 0x238) = param_3[2];
    break;
  case 0x11:
    *(float *)(param_1 + 0x23c) = *param_3;
    break;
  case 0x12:
    fVar16 = *param_3;
    if (*(float *)(param_1 + 700) != fVar16) {
      *(float *)(param_1 + 700) = fVar16;
      *(float *)(param_1 + 0x2b8) = fVar16;
code_r0x0223cf58:
      Aska::Light::CalcAttenuation()(param_1);
      return 1;
    }
    break;
  case 0x13:
    if (param_3[3] != 0.0) {
      *(float *)(param_1 + 0x210) = *param_3;
      *(float *)(param_1 + 0x214) = param_3[1];
      *(float *)(param_1 + 0x218) = param_3[2];
      *(float *)(param_1 + 0x21c) = param_3[3];
      goto code_r0x0223cf58;
    }
    break;
  case 0x14:
    fVar17 = *param_3;
    fVar16 = *(float *)(param_1 + 0x2d8);
    if (*(float *)(param_1 + 0x2d8) <= _UNK_027e519c) {
      fVar16 = _UNK_027e519c;
    }
    *(float *)(param_1 + 0x2d4) = fVar17;
    fVar17 = fVar17 + fVar16;
    goto code_r0x0223ce34;
  case 0x15:
    fVar17 = *param_3;
    *(float *)(param_1 + 0x2d8) = fVar17;
    if (fVar17 <= fVar16) {
      fVar17 = fVar16;
    }
    fVar17 = fVar17 + *(float *)(param_1 + 0x2d4);
code_r0x0223ce34:
    fVar16 = (float)cosf(fVar17 * 0.5);
    *(float *)(param_1 + 0x2dc) = fVar16 * fVar16;
    fVar16 = (float)cosf(*(float *)(param_1 + 0x2d4) * 0.5);
    *(float *)(param_1 + 0x2e0) = 1.0 / (fVar16 * fVar16 - *(float *)(param_1 + 0x2dc));
    break;
  case 0x16:
    *(float *)(param_1 + 0x280) = *param_3;
    *(float *)(param_1 + 0x284) = param_3[1];
    *(float *)(param_1 + 0x288) = param_3[2];
    break;
  case 0x17:
    if ((uint)*param_3 < 9) {
      *(char *)(param_1 + 0x2a1) = SUB41(*param_3,0);
      return 1;
    }
    break;
  case 0x18:
    bVar6 = *(byte *)param_3;
    *(undefined1 *)(param_1 + 0x2a7) = *(undefined1 *)(param_1 + 0x2a7);
    uVar11 = *(ushort *)(param_1 + 0x2a5) & 0xfffe | (ushort)bVar6;
    goto code_r0x0223d05c;
  case 0x19:
  case 0x1e:
  case 0x1f:
  case 0x20:
  case 0x39:
  case 0x3f:
  case 0x51:
  case 0x5e:
    break;
  default:
    goto code_r0x0223cd44;
  case 0x1b:
    bVar6 = *(byte *)param_3;
    *(undefined1 *)(param_1 + 0x2a7) = *(undefined1 *)(param_1 + 0x2a7);
    *(ushort *)(param_1 + 0x2a5) = *(ushort *)(param_1 + 0x2a5) & 0xfff7 | (bVar6 & 0x1f) << 3;
    break;
  case 0x1c:
    if (*(char *)(param_1 + 0x2a1) == '\b') {
      return 1;
    }
    goto code_r0x0223d520;
  case 0x1d:
    *(char *)(param_1 + 0x2a0) = SUB41(*param_3,0);
    break;
  case 0x21:
    puVar1 = (uint3 *)(param_1 + 0x2a5);
    bVar6 = *(byte *)param_3;
    if ((*puVar1 >> 6 & 1) != (uint)bVar6) {
      *(char *)(param_1 + 0x2a7) = (char)(*puVar1 >> 0x10);
      *(ushort *)puVar1 = *(ushort *)puVar1 & 0xffbf | (ushort)((bVar6 & 3) << 6);
      goto code_r0x0223cf58;
    }
    break;
  case 0x27:
    *(undefined1 *)(param_1 + 0x2a2) = *(undefined1 *)param_3;
    break;
  case 0x28:
    lVar10 = *(long *)(param_1 + 0x18);
    if (lVar10 != 0) {
      if (*(char *)param_3 == '\0') {
        if (*(long *)(lVar10 + 0x2ff0) == param_1) {
          *(undefined8 *)(lVar10 + 0x2ff0) = 0;
        }
      }
      else if (*(char *)(param_1 + 0x2a1) == '\0') {
        *(long *)(lVar10 + 0x2ff0) = param_1;
        return 1;
      }
    }
    break;
  case 0x29:
    *(float *)(param_1 + 0x240) = *param_3;
    *(float *)(param_1 + 0x244) = param_3[1];
    *(float *)(param_1 + 0x248) = param_3[2];
    *(float *)(param_1 + 0x24c) = param_3[3];
    break;
  case 0x2a:
    *(float *)(param_1 + 0x250) = *param_3;
    *(float *)(param_1 + 0x254) = param_3[1];
    *(float *)(param_1 + 600) = param_3[2];
    *(float *)(param_1 + 0x25c) = param_3[3];
    break;
  case 0x2b:
    *(float *)(param_1 + 0x260) = *param_3;
    *(float *)(param_1 + 0x264) = param_3[1];
    *(float *)(param_1 + 0x268) = param_3[2];
    *(float *)(param_1 + 0x26c) = param_3[3];
    break;
  case 0x2c:
    *(float *)(param_1 + 0x270) = *param_3;
    *(float *)(param_1 + 0x274) = param_3[1];
    *(float *)(param_1 + 0x278) = param_3[2];
    *(float *)(param_1 + 0x27c) = param_3[3];
    break;
  case 0x2d:
    bVar6 = *(byte *)param_3;
    *(undefined1 *)(param_1 + 0x2a7) = *(undefined1 *)(param_1 + 0x2a7);
    uVar11 = *(ushort *)(param_1 + 0x2a5) & 0xfeff | (ushort)bVar6 << 8;
code_r0x0223d05c:
    *(ushort *)(param_1 + 0x2a5) = uVar11;
    break;
  case 0x2e:
    bVar6 = *(byte *)param_3;
    uVar11 = *(ushort *)(param_1 + 0x2a5);
    *(undefined1 *)(param_1 + 0x2a7) = *(undefined1 *)(param_1 + 0x2a7);
    *(ushort *)(param_1 + 0x2a5) = uVar11 & 0xff00 | uVar11 & 0x7f | (bVar6 & 1) << 7;
    break;
  case 0x2f:
    bVar6 = *(byte *)param_3;
    uVar12 = *(uint3 *)(param_1 + 0x2a5) & 0xfff7ff | (uint)bVar6 << 0xb;
    *(short *)(param_1 + 0x2a5) = (short)uVar12;
    *(char *)(param_1 + 0x2a7) = (char)(uVar12 >> 0x10);
    if (bVar6 == 0) {
      *(undefined4 *)(param_1 + 0x2fc) = 0x3f800000;
      return 1;
    }
    break;
  case 0x30:
    *(short *)(param_1 + 0x2e6) = SUB42(*param_3,0);
    break;
  case 0x31:
    *(float *)(param_1 + 0x2f0) = *param_3;
    break;
  case 0x32:
    *(float *)(param_1 + 0x2f4) = *param_3;
    break;
  case 0x33:
    *(float *)(param_1 + 0x2f8) = *param_3;
    break;
  case 0x35:
    uVar12 = *(uint3 *)(param_1 + 0x2a5) & 0xffefff | (uint)*(byte *)param_3 << 0xc;
    goto code_r0x0223d5e0;
  case 0x36:
    Aska::Light::SetIlluminance(float)(*param_3,param_1);
    break;
  case 0x37:
    bVar6 = *(byte *)(param_1 + 0x2a1);
    if ((bVar6 & 0xfc) == 4) {
      if (bVar6 == 5) {
        fVar16 = *(float *)(param_1 + 0x240);
        fVar17 = *(float *)(param_1 + 0x244);
        fVar18 = *(float *)(param_1 + 0x248);
      }
      else {
        if (bVar6 != 4) goto code_r0x0223d614;
        fVar16 = (*(float *)(param_1 + 0x230) + *(float *)(param_1 + 0x280)) * 0.5;
        fVar17 = (*(float *)(param_1 + 0x234) + *(float *)(param_1 + 0x284)) * 0.5;
        fVar18 = (*(float *)(param_1 + 0x238) + *(float *)(param_1 + 0x288)) * 0.5;
      }
    }
    else {
code_r0x0223d614:
      fVar16 = *(float *)(param_1 + 0x230);
      fVar17 = *(float *)(param_1 + 0x234);
      fVar18 = *(float *)(param_1 + 0x238);
    }
    fVar19 = 1.0 / (fVar18 + fVar17 + fVar16);
    fVar17 = (*param_3 * fVar19) /
             ((fVar18 * fVar19 * _UNK_029cc0ec +
              fVar16 * fVar19 * _UNK_029cc0e4 + fVar17 * fVar19 * _UNK_029cc0e8) * _UNK_029cc0f0);
    fVar16 = fVar17 / _UNK_029cc0f4;
    if (4 < bVar6 - 4) {
      fVar16 = fVar17;
    }
    *(float *)(param_1 + 0x23c) = fVar16;
    break;
  case 0x38:
    Aska::Light::SetColorByTemperature(float)(*param_3,param_1);
    break;
  case 0x3b:
    lVar10 = *(long *)(param_1 + 0x418);
    lVar13 = *(long *)param_3;
    if (lVar10 == 0) {
      if (lVar13 == 0) {
        return 1;
      }
    }
    else if (lVar13 == *(long *)(lVar10 + 0x11d0)) {
      return 1;
    }
    if (lVar10 == 0) {
      if (lVar13 == 0) {
        return 1;
      }
      lVar10 = operator new(unsigned long, std::nothrow_t const&)(0x1218,PTR__ZSt7nothrow_02cb9a80);
      if (lVar10 == 0) {
        *(undefined8 *)(param_1 + 0x418) = 0;
        return 1;
      }
      Aska::IBLMap::IBLMap()(lVar10);
      *(long *)(param_1 + 0x418) = lVar10;
      Aska::Light::SetIBLProfile(unsigned int)(param_1,*(undefined1 *)(param_1 + 0x424));
      *(long *)(*(long *)(param_1 + 0x418) + 0x40) = param_1 + 0x240;
      lVar10 = *(long *)(param_1 + 0x418);
    }
    if (*(long *)(lVar10 + 0x11d0) != lVar13) {
      *(long *)(lVar10 + 0x11d0) = lVar13;
      *(undefined8 *)(lVar10 + 0x11e0) = 0;
      lVar10 = *(long *)(param_1 + 0x418);
    }
    if (*(long *)(lVar10 + 0x11f0) != 0) {
      *(undefined8 *)(lVar10 + 0x11f0) = 0;
      *(undefined8 *)(lVar10 + 0x1200) = 0;
      return 1;
    }
    break;
  case 0x3c:
    *(float *)(param_1 + 0x390) = *param_3;
    *(float *)(param_1 + 0x394) = param_3[1];
    *(float *)(param_1 + 0x398) = param_3[2];
    *(float *)(param_1 + 0x39c) = param_3[3];
    break;
  case 0x3d:
    *(float *)(param_1 + 0x3a0) = *param_3;
    *(float *)(param_1 + 0x3a4) = param_3[1];
    *(float *)(param_1 + 0x3a8) = param_3[2];
    *(float *)(param_1 + 0x3ac) = param_3[3];
    break;
  case 0x3e:
    lVar10 = *(long *)(param_1 + 0x418);
    if ((lVar10 != 0) && ((uint)*(byte *)(lVar10 + 0xf72) != ((uint)*param_3 & 0xff))) {
      lVar13 = *(long *)(lVar10 + 0x28);
      *(char *)(lVar10 + 0xf72) = SUB41(*param_3,0);
      puVar8 = PTR__ZN4Aska14TextureManager18m_iCurrentUniqueIDE_02cba9f0;
      if (lVar13 != 0) {
        do {
          iVar15 = *(int *)puVar8 + 1;
          cVar14 = '\x01';
          bVar7 = (bool)ExclusiveMonitorPass(puVar8,0x10);
          if (bVar7) {
            *(int *)puVar8 = iVar15;
            cVar14 = ExclusiveMonitorsStatus();
          }
        } while (cVar14 != '\0');
code_r0x0223d454:
        *(int *)(lVar13 + 0x7c) = iVar15;
        return 1;
      }
    }
    break;
  case 0x40:
    fVar16 = *param_3;
    puVar2 = (undefined4 *)(param_1 + 0x3e0);
    *(float *)(param_1 + 0x3e0) = fVar16;
    fVar17 = param_3[1];
    puVar3 = (undefined4 *)(param_1 + 0x3a0);
    *(float *)(param_1 + 0x3e4) = fVar17;
    fVar18 = param_3[2];
    puVar4 = puVar3;
    if (fVar16 < *(float *)(param_1 + 0x3a0)) {
      puVar4 = puVar2;
    }
    *(float *)(param_1 + 1000) = fVar18;
    *(float *)(param_1 + 0x3ec) = param_3[3];
    puVar5 = puVar3;
    if (fVar17 < *(float *)(param_1 + 0x3a4)) {
      puVar5 = puVar2;
    }
    if (fVar18 < *(float *)(param_1 + 0x3a8)) {
      puVar3 = puVar2;
    }
    *(undefined4 *)(param_1 + 0x3e0) = *puVar4;
    *(undefined4 *)(param_1 + 0x3e4) = puVar5[1];
    *(undefined4 *)(param_1 + 1000) = puVar3[2];
    break;
  case 0x41:
    fVar16 = *param_3;
    puVar2 = (undefined4 *)(param_1 + 0x3f0);
    *(float *)(param_1 + 0x3f0) = fVar16;
    fVar17 = param_3[1];
    puVar3 = (undefined4 *)(param_1 + 0x3a0);
    *(float *)(param_1 + 0x3f4) = fVar17;
    fVar18 = param_3[2];
    puVar4 = puVar3;
    if (fVar16 < *(float *)(param_1 + 0x3a0)) {
      puVar4 = puVar2;
    }
    *(float *)(param_1 + 0x3f8) = fVar18;
    *(float *)(param_1 + 0x3fc) = param_3[3];
    puVar5 = puVar3;
    if (fVar17 < *(float *)(param_1 + 0x3a4)) {
      puVar5 = puVar2;
    }
    if (fVar18 < *(float *)(param_1 + 0x3a8)) {
      puVar3 = puVar2;
    }
    *(undefined4 *)(param_1 + 0x3f0) = *puVar4;
    *(undefined4 *)(param_1 + 0x3f4) = puVar5[1];
    *(undefined4 *)(param_1 + 0x3f8) = puVar3[2];
    break;
  case 0x42:
    lVar10 = *(long *)(param_1 + 0x418);
    if ((lVar10 != 0) && ((uint)*(byte *)(lVar10 + 0xf73) != ((uint)*param_3 & 0xff))) {
      lVar13 = *(long *)(lVar10 + 0x28);
      *(char *)(lVar10 + 0xf73) = SUB41(*param_3,0);
      puVar8 = PTR__ZN4Aska14TextureManager18m_iCurrentUniqueIDE_02cba9f0;
      if (lVar13 != 0) {
        do {
          iVar15 = *(int *)puVar8 + 1;
          cVar14 = '\x01';
          bVar7 = (bool)ExclusiveMonitorPass(puVar8,0x10);
          if (bVar7) {
            *(int *)puVar8 = iVar15;
            cVar14 = ExclusiveMonitorsStatus();
          }
        } while (cVar14 != '\0');
        goto code_r0x0223d454;
      }
    }
    break;
  case 0x43:
    lVar10 = *(long *)(param_1 + 0x418);
    if ((lVar10 != 0) && ((uint)*(byte *)(lVar10 + 0xf71) != ((uint)*param_3 & 0xff))) {
      lVar13 = *(long *)(lVar10 + 0x28);
      *(char *)(lVar10 + 0xf71) = SUB41(*param_3,0);
      puVar8 = PTR__ZN4Aska14TextureManager18m_iCurrentUniqueIDE_02cba9f0;
      if (lVar13 != 0) {
        do {
          iVar15 = *(int *)puVar8 + 1;
          cVar14 = '\x01';
          bVar7 = (bool)ExclusiveMonitorPass(puVar8,0x10);
          if (bVar7) {
            *(int *)puVar8 = iVar15;
            cVar14 = ExclusiveMonitorsStatus();
          }
        } while (cVar14 != '\0');
        goto code_r0x0223d454;
      }
    }
    break;
  case 0x44:
    lVar10 = *(long *)(param_1 + 0x418);
    if ((lVar10 != 0) && (*(float *)(lVar10 + 0xf74) != *param_3)) {
      lVar13 = *(long *)(lVar10 + 0x28);
      *(float *)(lVar10 + 0xf74) = *param_3;
      puVar8 = PTR__ZN4Aska14TextureManager18m_iCurrentUniqueIDE_02cba9f0;
      if (lVar13 != 0) {
        do {
          iVar15 = *(int *)puVar8 + 1;
          cVar14 = '\x01';
          bVar7 = (bool)ExclusiveMonitorPass(puVar8,0x10);
          if (bVar7) {
            *(int *)puVar8 = iVar15;
            cVar14 = ExclusiveMonitorsStatus();
          }
        } while (cVar14 != '\0');
        goto code_r0x0223d454;
      }
    }
    break;
  case 0x45:
    lVar10 = *(long *)(param_1 + 0x418);
    if ((lVar10 != 0) && (*(float *)(lVar10 + 0xf78) != *param_3)) {
      lVar13 = *(long *)(lVar10 + 0x28);
      *(float *)(lVar10 + 0xf78) = *param_3;
      puVar8 = PTR__ZN4Aska14TextureManager18m_iCurrentUniqueIDE_02cba9f0;
      if (lVar13 != 0) {
        do {
          iVar15 = *(int *)puVar8 + 1;
          cVar14 = '\x01';
          bVar7 = (bool)ExclusiveMonitorPass(puVar8,0x10);
          if (bVar7) {
            *(int *)puVar8 = iVar15;
            cVar14 = ExclusiveMonitorsStatus();
          }
        } while (cVar14 != '\0');
        goto code_r0x0223d454;
      }
    }
    break;
  case 0x46:
    lVar10 = *(long *)(param_1 + 0x418);
    if (lVar10 != 0) {
      cVar14 = '\x10';
      if (*param_3 == 0.0) {
        cVar14 = ' ';
      }
      if (*(char *)(lVar10 + 0xf82) != cVar14) {
        lVar13 = *(long *)(lVar10 + 0x28);
        *(char *)(lVar10 + 0xf82) = cVar14;
        puVar8 = PTR__ZN4Aska14TextureManager18m_iCurrentUniqueIDE_02cba9f0;
        if (lVar13 != 0) {
          do {
            iVar15 = *(int *)puVar8;
            cVar14 = '\x01';
            bVar7 = (bool)ExclusiveMonitorPass(puVar8,0x10);
            if (bVar7) {
              *(int *)puVar8 = iVar15 + 1;
              cVar14 = ExclusiveMonitorsStatus();
            }
          } while (cVar14 != '\0');
          *(int *)(lVar13 + 0x7c) = iVar15 + 1;
          return 1;
        }
      }
    }
    break;
  case 0x47:
    Aska::Light::SetIBLProfile(unsigned int)(param_1,*param_3);
    break;
  case 0x48:
    *(float *)(param_1 + 0x2a8) = *param_3;
    break;
  case 0x4a:
    uVar12 = *(uint3 *)(param_1 + 0x2a5) & 0xffdfff | (uint)*(byte *)param_3 << 0xd;
    goto code_r0x0223d5e0;
  case 0x4b:
    *(float *)(param_1 + 0x2cc) = *param_3;
    break;
  case 0x4c:
    if (*(char *)(param_1 + 0x2a1) != '\b') {
      return 1;
    }
code_r0x0223d520:
    if (*(float *)(param_1 + 0x2c4) != *param_3) {
      *(float *)(param_1 + 0x2c4) = *param_3;
      return 1;
    }
    break;
  case 0x4d:
    *(short *)(param_1 + 0x2e4) = SUB42(*param_3,0);
    break;
  case 0x4e:
    *(float *)(param_1 + 0x2d0) = *param_3;
    break;
  case 0x4f:
    *(float *)(param_1 + 0x2c8) = *param_3;
    break;
  case 0x50:
    uVar12 = *(uint3 *)(param_1 + 0x2a5) & 0xffbfff | (uint)*(byte *)param_3 << 0xe;
    goto code_r0x0223d5e0;
  case 0x52:
    uVar12 = *(uint3 *)(param_1 + 0x2a5) & 0xfffdff | (uint)*(byte *)param_3 << 9;
    goto code_r0x0223d5e0;
  case 0x53:
    uVar12 = *(uint3 *)(param_1 + 0x2a5) & 0xfffbff | (uint)*(byte *)param_3 << 10;
code_r0x0223d5e0:
    *(short *)(param_1 + 0x2a5) = (short)uVar12;
    *(char *)(param_1 + 0x2a7) = (char)(uVar12 >> 0x10);
    break;
  case 0x54:
    *(float *)(param_1 + 0x304) = *param_3;
    fVar16 = (float)logf(1);
    *(float *)(param_1 + 0x308) = 1.0 / fVar16;
  }
  return 1;
}

// ==== Aska::Light::SetIlluminance(float)
// vaddr 0x213d758 | ghidra 0x223d758 | size 624 | symbol _ZN4Aska5Light14SetIlluminanceEf | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska5Light14SetIlluminanceEf(float param_1,long param_2)

{
  byte bVar1;
  uint uVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  
  fVar7 = 1.0 / (*(float *)(param_2 + 0x220) + *(float *)(param_2 + 0x224) * _UNK_027e5198 +
                *(float *)(param_2 + 0x228) * _UNK_027e6ae0) - *(float *)(param_2 + 0x22c);
  if (fVar7 < 0.0) {
    fVar7 = 0.0;
  }
  fVar6 = 1.0;
  if (fVar7 + -1.0 < 0.0) {
    fVar6 = fVar7;
  }
  if (_UNK_027e519c <= fVar6) {
    bVar1 = *(byte *)(param_2 + 0x2a1);
    fVar6 = param_1 / fVar6;
  }
  else {
    fVar7 = 1.0 / (*(float *)(param_2 + 0x220) + *(float *)(param_2 + 0x224) * _UNK_027ebdd8 +
                  *(float *)(param_2 + 0x228) * _UNK_029cc0f8) - *(float *)(param_2 + 0x22c);
    if (fVar7 < 0.0) {
      fVar7 = 0.0;
    }
    fVar6 = 1.0;
    if (fVar7 + -1.0 < 0.0) {
      fVar6 = fVar7;
    }
    if (fVar6 < _UNK_027e519c) {
      bVar1 = *(byte *)(param_2 + 0x2a1);
      uVar2 = (uint)bVar1;
      if ((bVar1 & 0xfc) == 4) {
        if (bVar1 == 5) {
          fVar7 = *(float *)(param_2 + 0x240);
          fVar3 = *(float *)(param_2 + 0x244);
          fVar4 = *(float *)(param_2 + 0x248);
        }
        else {
          if (bVar1 != 4) goto code_r0x0223d8dc;
          fVar7 = (*(float *)(param_2 + 0x230) + *(float *)(param_2 + 0x280)) * 0.5;
          fVar3 = (*(float *)(param_2 + 0x234) + *(float *)(param_2 + 0x284)) * 0.5;
          fVar4 = (*(float *)(param_2 + 0x238) + *(float *)(param_2 + 0x288)) * 0.5;
        }
      }
      else {
code_r0x0223d8dc:
        fVar7 = *(float *)(param_2 + 0x230);
        fVar3 = *(float *)(param_2 + 0x234);
        fVar4 = *(float *)(param_2 + 0x238);
      }
      fVar6 = 1.0 / (fVar4 + fVar3 + fVar7);
      fVar7 = fVar4 * fVar6 * _UNK_029cc0ec +
              fVar7 * fVar6 * _UNK_029cc0e4 + fVar3 * fVar6 * _UNK_029cc0e8;
      fVar6 = fVar6 * param_1;
      goto code_r0x0223d998;
    }
    bVar1 = *(byte *)(param_2 + 0x2a1);
    fVar6 = (param_1 * 4.0) / fVar6;
  }
  uVar2 = (uint)bVar1;
  if ((uVar2 & 0xfc) == 4) {
    if (uVar2 == 5) {
      fVar7 = *(float *)(param_2 + 0x240);
      fVar3 = *(float *)(param_2 + 0x244);
      fVar4 = *(float *)(param_2 + 0x248);
    }
    else {
      if (uVar2 != 4) goto code_r0x0223d8cc;
      fVar7 = (*(float *)(param_2 + 0x230) + *(float *)(param_2 + 0x280)) * 0.5;
      fVar3 = (*(float *)(param_2 + 0x234) + *(float *)(param_2 + 0x284)) * 0.5;
      fVar4 = (*(float *)(param_2 + 0x238) + *(float *)(param_2 + 0x288)) * 0.5;
    }
  }
  else {
code_r0x0223d8cc:
    fVar7 = *(float *)(param_2 + 0x230);
    fVar3 = *(float *)(param_2 + 0x234);
    fVar4 = *(float *)(param_2 + 0x238);
  }
  fVar5 = 1.0 / (fVar4 + fVar3 + fVar7);
  fVar7 = fVar4 * fVar5 * _UNK_029cc0ec +
          fVar7 * fVar5 * _UNK_029cc0e4 + fVar3 * fVar5 * _UNK_029cc0e8;
  fVar6 = fVar6 * fVar5;
code_r0x0223d998:
  fVar6 = fVar6 / (fVar7 * _UNK_029cc0f0);
  fVar7 = fVar6 / _UNK_029cc0f4;
  if (4 < uVar2 - 4) {
    fVar7 = fVar6;
  }
  *(float *)(param_2 + 0x23c) = fVar7;
  return;
}

// ==== Aska::Light::SetColorByTemperature(float)
// vaddr 0x213d9c8 | ghidra 0x223d9c8 | size 324 | symbol _ZN4Aska5Light21SetColorByTemperatureEf | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska5Light21SetColorByTemperatureEf(float param_1,long param_2)

{
  byte bVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  
  fVar5 = _UNK_029c9b70;
  fVar4 = (float)expf(_UNK_029c9b70 / (param_1 * _UNK_029c9b6c));
  fVar7 = _UNK_029c9b78 / ((fVar4 + -1.0) * _UNK_029c9b74);
  fVar4 = (float)expf(fVar5 / (param_1 * _UNK_029c9b7c));
  fVar4 = _UNK_029c9b84 / ((fVar4 + -1.0) * _UNK_029c9b80);
  fVar5 = (float)expf(fVar5 / (param_1 * _UNK_029c9b88));
  uVar3 = _UNK_027dbb38;
  uVar2 = _UNK_027dbb30;
  bVar1 = *(byte *)(param_2 + 0x2a1);
  fVar5 = _UNK_029c9b90 / ((fVar5 + -1.0) * _UNK_029c9b8c);
  fVar6 = 1.0 / (fVar7 + fVar4 + fVar5);
  fVar7 = fVar7 * fVar6;
  fVar4 = fVar4 * fVar6;
  fVar5 = fVar5 * fVar6;
  if ((bVar1 & 0xfc) == 4) {
    if (bVar1 == 5) {
      *(float *)(param_2 + 0x240) = fVar7;
      *(float *)(param_2 + 0x244) = fVar4;
      *(float *)(param_2 + 0x248) = fVar5;
      *(undefined8 *)(param_2 + 600) = uVar3;
      *(undefined8 *)(param_2 + 0x250) = uVar2;
      *(undefined8 *)(param_2 + 0x268) = uVar3;
      *(undefined8 *)(param_2 + 0x260) = uVar2;
      *(undefined8 *)(param_2 + 0x278) = uVar3;
      *(undefined8 *)(param_2 + 0x270) = uVar2;
      return;
    }
    if (bVar1 == 4) {
      *(float *)(param_2 + 0x230) = fVar7;
      *(float *)(param_2 + 0x234) = fVar4;
      *(float *)(param_2 + 0x238) = fVar5;
      *(float *)(param_2 + 0x280) = fVar7;
      *(float *)(param_2 + 0x284) = fVar4;
      *(float *)(param_2 + 0x288) = fVar5;
      return;
    }
  }
  *(float *)(param_2 + 0x230) = fVar7;
  *(float *)(param_2 + 0x234) = fVar4;
  *(float *)(param_2 + 0x238) = fVar5;
  return;
}

// ==== Aska::Light::CalcHemisphereIntensity(Aska::RenderableObject*)
// vaddr 0x213db0c | ghidra 0x223db0c | size 260 | symbol _ZN4Aska5Light23CalcHemisphereIntensityEPNS_16RenderableObjectE | lib libSOA-3.7.0.so | 2026-10-04
float _ZN4Aska5Light23CalcHemisphereIntensityEPNS_16RenderableObjectE(long param_1,long *param_2)

{
  byte bVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  
  fVar2 = *(float *)((long)param_2 + 0x4c) - *(float *)(param_1 + 0x200);
  fVar3 = *(float *)((long)param_2 + 0x5c) - *(float *)(param_1 + 0x204);
  fVar4 = *(float *)((long)param_2 + 0x6c) - *(float *)(param_1 + 0x208);
  fVar5 = *(float *)(param_1 + 0x23c);
  fVar2 = SQRT(fVar2 * fVar2 + fVar3 * fVar3 + fVar4 * fVar4);
  if (NAN(fVar2)) {
    fVar2 = (float)sqrtf();
    bVar1 = *(byte *)(param_2 + 0x25);
  }
  else {
    bVar1 = *(byte *)(param_2 + 0x25);
  }
  if ((bVar1 >> 4 & 1) == 0) {
    (**(code **)(*param_2 + 600))(param_2,0);
  }
  fVar3 = 0.0;
  if (fVar2 - *(float *)((long)param_2 + 0x2dc) <= *(float *)(param_1 + 0x2b8)) {
    fVar2 = 1.0 / (*(float *)(param_1 + 0x220) + fVar2 * *(float *)(param_1 + 0x224) +
                  fVar2 * fVar2 * *(float *)(param_1 + 0x228)) - *(float *)(param_1 + 0x22c);
    if (fVar2 < 0.0) {
      fVar2 = 0.0;
    }
    fVar3 = 1.0;
    if (fVar2 + -1.0 < 0.0) {
      fVar3 = fVar2;
    }
    fVar3 = fVar5 * fVar3;
  }
  return fVar3;
}

// ==== Aska::Light::RegisterDiffuseCubeMap()
// vaddr 0x213dc10 | ghidra 0x223dc10 | size 700 | symbol _ZN4Aska5Light22RegisterDiffuseCubeMapEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska5Light22RegisterDiffuseCubeMapEv(long param_1)

{
  long *plVar1;
  undefined *puVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  ulong uVar6;
  long lVar7;
  ulong uVar8;
  long lVar9;
  long lVar10;
  undefined8 uVar11;
  undefined8 uVar12;
  long lVar13;
  
  lVar13 = *(long *)(param_1 + 0x418);
  if (lVar13 == 0) {
    return 0;
  }
  lVar7 = *(long *)(lVar13 + 0x11d0);
  if (lVar7 == 0) {
code_r0x0223dc8c:
    iVar4 = 0;
  }
  else {
    lVar9 = *(long *)(lVar13 + 0x11e0);
    if (lVar9 == 0) {
      lVar9 = *(long *)PTR__ZN4Aska6Global17m_pTextureManagerE_02cc19f0;
      lVar10 = lVar9 + 0xb0;
      Aska::CriticalSection::Enter() const(lVar10);
      lVar9 = Aska::TextureManager::QueryTextureEx(unsigned long, bool)(lVar9,lVar7,1);
      Aska::CriticalSection::Leave() const(lVar10);
      *(long *)(lVar13 + 0x11e0) = lVar9;
      if (lVar9 == 0) goto code_r0x0223dc8c;
    }
    iVar4 = *(int *)(lVar9 + 0x7c);
  }
  if (iVar4 == *(int *)(lVar13 + 0x1210)) {
    return 1;
  }
  plVar1 = (long *)(param_1 + 0x418);
  *(int *)(lVar13 + 0x1210) = iVar4;
  lVar7 = *plVar1;
  lVar13 = *(long *)(lVar7 + 0x11d0);
  if (lVar13 == 0) {
code_r0x0223dd98:
    if (lVar7 == 0) {
      return 1;
    }
    if (*(uint *)(param_1 + 0x420) == 0) {
      return 1;
    }
    uVar8 = (ulong)*(uint *)(param_1 + 0x420) | 0x200000000000000;
    uVar11 = *(undefined8 *)(*(long *)PTR__ZN4Aska6Global16m_pObjectManagerE_02cc4688 + 0x45e0);
    lVar13 = Aska::ProceduralTextureManager::GetProcTexEnv(unsigned long)(uVar11,uVar8);
    if (lVar13 == 0) {
      return 1;
    }
    Aska::ProceduralTextureManager::Unregister(unsigned long)(uVar11,uVar8);
    Aska::DiffuseCubeMap::DeleteTexture()(*plVar1);
    return 1;
  }
  if (*(long *)(lVar7 + 0x11e0) == 0) {
    lVar10 = *(long *)PTR__ZN4Aska6Global17m_pTextureManagerE_02cc19f0;
    lVar9 = lVar10 + 0xb0;
    Aska::CriticalSection::Enter() const(lVar9);
    lVar13 = Aska::TextureManager::QueryTextureEx(unsigned long, bool)(lVar10,lVar13,1);
    Aska::CriticalSection::Leave() const(lVar9);
    *(long *)(lVar7 + 0x11e0) = lVar13;
    if (lVar13 == 0) {
      lVar7 = *plVar1;
      goto code_r0x0223dd98;
    }
  }
  uVar3 = uRam0000000002ccb34c;
  uVar5 = *(uint *)(param_1 + 0x420);
  if (*(uint *)(param_1 + 0x420) == 0) {
    uVar5 = uRam0000000002ccb34c + 1;
    *(uint *)(param_1 + 0x420) = uRam0000000002ccb34c;
    uRam0000000002ccb34c = uVar5;
    uVar5 = uVar3;
  }
  puVar2 = PTR__ZN4Aska6Global16m_pObjectManagerE_02cc4688;
  uVar8 = (ulong)uVar5 | 0x200000000000000;
  uVar11 = *(undefined8 *)(*(long *)PTR__ZN4Aska6Global16m_pObjectManagerE_02cc4688 + 0x45e0);
  lVar13 = Aska::ProceduralTextureManager::GetProcTexEnv(unsigned long)(uVar11,uVar8);
  if (lVar13 == 0) goto code_r0x0223de80;
  lVar13 = *plVar1;
  lVar7 = *(long *)(lVar13 + 0x11f0);
  if (lVar7 == 0) {
code_r0x0223dde4:
    if (*(long *)(lVar13 + 0x20) != 0) {
      Aska::DiffuseCubeMap::DiffuseSHCoef()(lVar13);
      lVar13 = *plVar1;
      lVar7 = *(long *)(lVar13 + 0x11d0);
      if (lVar7 == 0) {
        lVar9 = 0;
      }
      else {
        lVar9 = *(long *)(lVar13 + 0x11e0);
        if (lVar9 == 0) {
          lVar9 = *(long *)PTR__ZN4Aska6Global17m_pTextureManagerE_02cc19f0;
          lVar10 = lVar9 + 0xb0;
          Aska::CriticalSection::Enter() const(lVar10);
          lVar9 = Aska::TextureManager::QueryTextureEx(unsigned long, bool)(lVar9,lVar7,1);
          Aska::CriticalSection::Leave() const(lVar10);
          *(long *)(lVar13 + 0x11e0) = lVar9;
        }
      }
      Aska::DiffuseCubeMap::Init(Aska::Texture*)(lVar13,lVar9);
      Aska::ProceduralTextureManager::Update(unsigned long)(uVar11,uVar8);
      return 1;
    }
joined_r0x0223de44:
    if (lVar13 == 0) goto code_r0x0223de80;
  }
  else if (*(long *)(lVar13 + 0x1200) == 0) {
    lVar10 = *(long *)PTR__ZN4Aska6Global17m_pTextureManagerE_02cc19f0;
    lVar9 = lVar10 + 0xb0;
    Aska::CriticalSection::Enter() const(lVar9);
    lVar7 = Aska::TextureManager::QueryTextureEx(unsigned long, bool)(lVar10,lVar7,1);
    Aska::CriticalSection::Leave() const(lVar9);
    *(long *)(lVar13 + 0x1200) = lVar7;
    if (lVar7 == 0) {
      lVar13 = *plVar1;
      goto code_r0x0223dde4;
    }
    lVar13 = *plVar1;
    goto joined_r0x0223de44;
  }
  if (*(uint *)(param_1 + 0x420) != 0) {
    uVar6 = (ulong)*(uint *)(param_1 + 0x420) | 0x200000000000000;
    uVar12 = *(undefined8 *)(*(long *)puVar2 + 0x45e0);
    lVar13 = Aska::ProceduralTextureManager::GetProcTexEnv(unsigned long)(uVar12,uVar6);
    if (lVar13 != 0) {
      Aska::ProceduralTextureManager::Unregister(unsigned long)(uVar12,uVar6);
      Aska::DiffuseCubeMap::DeleteTexture()(*plVar1);
    }
  }
code_r0x0223de80:
  Aska::ProceduralTextureManager::Register(unsigned long, Aska::IProceduralTextureHandler*)(uVar11,uVar8,*plVar1);
  return 1;
}

// ==== Aska::Light::DoesAffectLightOFF(unsigned int)
// vaddr 0x213decc | ghidra 0x223decc | size 44 | symbol _ZN4Aska5Light18DoesAffectLightOFFEj | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska5Light18DoesAffectLightOFFEj(uint param_1)

{
  undefined8 uVar1;
  ulong uVar2;
  
  uVar2 = Aska::AffUtil::DoesAffectPlatformType(unsigned int)(param_1 & 0xff);
  if ((uVar2 & 1) != 0) {
    return 1;
  }
  uVar1 = (*(code *)PTR__ZN4Aska7AffUtil23DoesAffectPlatformRangeEj_02c8f788)(param_1 >> 8 & 0xf);
  return uVar1;
}

// ==== Aska::Light::DoesAffectRangeReduction(unsigned int)
// vaddr 0x213def8 | ghidra 0x223def8 | size 44 | symbol _ZN4Aska5Light24DoesAffectRangeReductionEj | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska5Light24DoesAffectRangeReductionEj(uint param_1)

{
  undefined8 uVar1;
  ulong uVar2;
  
  uVar2 = Aska::AffUtil::DoesAffectPlatformType(unsigned int)(param_1 >> 0xc & 0xff);
  if ((uVar2 & 1) != 0) {
    return 1;
  }
  uVar1 = (*(code *)PTR__ZN4Aska7AffUtil23DoesAffectPlatformRangeEj_02c8f788)(param_1 >> 0x14 & 0xf)
  ;
  return uVar1;
}

// ==== Aska::Light::GetClassID(int) const
// vaddr 0x213df24 | ghidra 0x223df24 | size 68 | symbol _ZNK4Aska5Light10GetClassIDEi | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska5Light10GetClassIDEi(undefined8 param_1,uint param_2)

{
  undefined8 uVar1;
  undefined8 uVar2;
  
  if (param_2 < 4) {
    return *(undefined8 *)(&UNK_029cc3d0 + (long)(int)param_2 * 8);
  }
  uVar2 = 0xf000f001;
  if (param_2 != 5) {
    uVar2 = 0xf000;
  }
  uVar1 = 0xf000f001f002;
  if (param_2 != 4) {
    uVar1 = uVar2;
  }
  return uVar1;
}

// ==== Aska::Light::GetDefaultLevel() const
// vaddr 0x213df68 | ghidra 0x223df68 | size 8 | symbol _ZNK4Aska5Light15GetDefaultLevelEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska5Light15GetDefaultLevelEv(void)

{
  return 0x1000;
}

// ==== Aska::Light::OnActive(bool)
// vaddr 0x213df70 | ghidra 0x223df70 | size 20 | symbol _ZN4Aska5Light8OnActiveEb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Light8OnActiveEb(long param_1,ushort param_2)

{
  *(ushort *)(param_1 + 0x2a5) = *(ushort *)(param_1 + 0x2a5) & 0xfffe | param_2 & 1;
  return;
}

// ==== Aska::LightManager::Run(int)
// vaddr 0x213e2c4 | ghidra 0x223e2c4 | size 96 | symbol _ZN4Aska12LightManager3RunEi | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska12LightManager3RunEi(long param_1)

{
  float fVar1;
  
  fVar1 = (float)(**(code **)**(undefined8 **)PTR__ZN4Aska6Global8m_pVSyncE_02cbd460)
                           (*(undefined8 **)PTR__ZN4Aska6Global8m_pVSyncE_02cbd460,0);
  if (_UNK_027e519c < fVar1) {
    *(float *)PTR__ZN4Aska5Light12m_fNoiseTimeE_02cbc668 =
         fVar1 + *(float *)PTR__ZN4Aska5Light12m_fNoiseTimeE_02cbc668;
  }
                    /* WARNING: Could not recover jumptable at 0x0223e320. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(**(long **)(param_1 + 0x108) + 0x70))();
  return;
}

// ==== non-virtual thunk to Aska::LightManager::Run(int)
// vaddr 0x213e324 | ghidra 0x223e324 | size 96 | symbol _ZThn40_N4Aska12LightManager3RunEi | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZThn40_N4Aska12LightManager3RunEi(long param_1)

{
  float fVar1;
  
  fVar1 = (float)(**(code **)**(undefined8 **)PTR__ZN4Aska6Global8m_pVSyncE_02cbd460)
                           (*(undefined8 **)PTR__ZN4Aska6Global8m_pVSyncE_02cbd460,0);
  if (_UNK_027e519c < fVar1) {
    *(float *)PTR__ZN4Aska5Light12m_fNoiseTimeE_02cbc668 =
         fVar1 + *(float *)PTR__ZN4Aska5Light12m_fNoiseTimeE_02cbc668;
  }
                    /* WARNING: Could not recover jumptable at 0x0223e380. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(**(long **)(param_1 + 0xe0) + 0x70))();
  return;
}

// ==== Aska::LightManager::GetActualSunLight() const
// vaddr 0x213e384 | ghidra 0x223e384 | size 64 | symbol _ZNK4Aska12LightManager17GetActualSunLightEv | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

long _ZNK4Aska12LightManager17GetActualSunLightEv(long param_1)

{
  long lVar1;
  
  lVar1 = *(long *)(param_1 + 0x2ff0);
  if ((lVar1 != 0) &&
     ((((*(ushort *)(lVar1 + 0x2a5) & 1) == 0 || (*(float *)(lVar1 + 0x2b8) < _UNK_027daba4)) ||
      (*(char *)(lVar1 + 0x2a1) != '\0')))) {
    lVar1 = 0;
  }
  return lVar1;
}

// ==== Aska::LightManager::MakeIBLContext(Aska::Light**, float*, Aska::LightManager::LightContext*, unsigned char*)
// vaddr 0x213e3c4 | ghidra 0x223e3c4 | size 676 | symbol _ZN4Aska12LightManager14MakeIBLContextEPPNS_5LightEPfPNS0_12LightContextEPh | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska12LightManager14MakeIBLContextEPPNS_5LightEPfPNS0_12LightContextEPh
               (undefined8 param_1,long *param_2,float *param_3,long param_4,long param_5)

{
  float fVar1;
  float fVar2;
  float fVar3;
  long lVar4;
  float *pfVar5;
  long lVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  float *pfStack_178;
  undefined8 uStack_160;
  undefined8 uStack_158;
  undefined8 uStack_150;
  undefined8 uStack_148;
  undefined8 uStack_140;
  undefined8 uStack_138;
  undefined8 uStack_120;
  undefined8 uStack_118;
  undefined8 uStack_110;
  undefined8 uStack_108;
  undefined8 uStack_100;
  undefined8 uStack_f8;
  float fStack_e0;
  float fStack_dc;
  float fStack_d8;
  float fStack_d4;
  float fStack_d0;
  float fStack_cc;
  float fStack_c8;
  float fStack_c4;
  undefined8 uStack_c0;
  undefined8 uStack_b8;
  float fStack_b0;
  float fStack_ac;
  float fStack_a8;
  float fStack_a4;
  
  lVar6 = *param_2;
  lVar4 = param_2[1];
  fStack_a4 = *(float *)(lVar6 + 0x23c);
  fVar13 = *(float *)(lVar6 + 0x2fc) * fStack_a4 * *param_3;
  fVar15 = fVar13 * *(float *)(lVar6 + 0x230);
  fVar16 = fVar13 * *(float *)(lVar6 + 0x234);
  fVar13 = fVar13 * *(float *)(lVar6 + 0x238);
  fVar1 = *(float *)(lVar6 + 0x200);
  fVar2 = *(float *)(lVar6 + 0x204);
  fVar3 = *(float *)(lVar6 + 0x208);
  fVar11 = 1.0 / *(float *)(lVar6 + 0x2c4);
  if (*(float *)(lVar6 + 0x2c4) <= 0.0) {
    fVar11 = 0.0;
  }
  fStack_e0 = fVar1;
  fStack_dc = fVar2;
  fStack_d8 = fVar3;
  fStack_d4 = fVar11;
  fStack_b0 = fVar15;
  fStack_ac = fVar16;
  fStack_a8 = fVar13;
  Aska::Light::CalcIBLLocalMatrix(Aska::Matrix*)(lVar6,&uStack_120);
  uStack_b8 = _UNK_027dbb38;
  uStack_c0 = _UNK_027dbb30;
  if (lVar4 == 0) {
    pfStack_178 = &fStack_b0;
    fVar14 = 0.0;
    fVar17 = 0.0;
    fVar18 = 0.0;
    fVar7 = fStack_d0;
    fVar8 = fStack_cc;
    fVar9 = fStack_c8;
    fVar12 = fStack_c4;
  }
  else {
    pfStack_178 = (float *)&uStack_c0;
    Aska::Light::CalcIBLLocalMatrix(Aska::Matrix*)(lVar4,&uStack_160);
    fVar14 = *(float *)(lVar4 + 0x2fc) * *(float *)(lVar4 + 0x23c) * param_3[1];
    fVar17 = fVar14 * *(float *)(lVar4 + 0x230);
    fVar18 = fVar14 * *(float *)(lVar4 + 0x234);
    fVar14 = fVar14 * *(float *)(lVar4 + 0x238);
    uStack_c0 = CONCAT44(fVar18,fVar17);
    uStack_b8 = CONCAT44(*(float *)(lVar4 + 0x23c),fVar14);
    fVar7 = *(float *)(lVar4 + 0x200);
    fVar8 = *(float *)(lVar4 + 0x204);
    fVar9 = *(float *)(lVar4 + 0x208);
    fVar12 = 1.0 / *(float *)(lVar4 + 0x2c4);
    if (*(float *)(lVar4 + 0x2c4) <= 0.0) {
      fVar12 = 0.0;
    }
    fStack_d0 = fVar7;
    fStack_cc = fVar8;
    fStack_c8 = fVar9;
    fStack_c4 = fVar12;
    fStack_a4 = (float)Aska::Light::GetIBLLodOffset() const(lVar6);
    fStack_a4 = fStack_a4 + _UNK_029cc3f0;
    lVar6 = lVar4;
  }
  fVar10 = (float)Aska::Light::GetIBLLodOffset() const(lVar6);
  pfStack_178[3] = fVar10 + _UNK_029cc3f0;
  lVar6 = 5;
  if (param_5 == 0) {
    lVar6 = 1;
  }
  if (lVar4 == 0) {
    pfVar5 = (float *)(param_4 + 0x250);
    lVar4 = 0;
    do {
      lVar4 = lVar4 + 1;
      *(undefined1 *)(pfVar5 + -0x93) = 1;
      *pfVar5 = fVar15;
      pfVar5[1] = fVar16;
      pfVar5[2] = fVar13;
      pfVar5[3] = fStack_a4;
      pfVar5[4] = fVar1;
      pfVar5[5] = fVar2;
      pfVar5[6] = fVar3;
      pfVar5[7] = fVar11;
      *(undefined8 *)(pfVar5 + 10) = uStack_118;
      *(undefined8 *)(pfVar5 + 8) = uStack_120;
      *(undefined8 *)(pfVar5 + 0xe) = uStack_108;
      *(undefined8 *)(pfVar5 + 0xc) = uStack_110;
      *(undefined8 *)(pfVar5 + 0x12) = uStack_f8;
      *(undefined8 *)(pfVar5 + 0x10) = uStack_100;
      pfVar5 = pfVar5 + 0x154;
    } while (lVar4 < lVar6);
  }
  else {
    lVar4 = 0;
    pfVar5 = (float *)(param_4 + 0x250);
    do {
      lVar4 = lVar4 + 1;
      *pfVar5 = fVar15;
      pfVar5[1] = fVar16;
      pfVar5[2] = fVar13;
      pfVar5[3] = fStack_a4;
      pfVar5[4] = fVar1;
      pfVar5[5] = fVar2;
      pfVar5[6] = fVar3;
      pfVar5[7] = fVar11;
      *(undefined8 *)(pfVar5 + 10) = uStack_118;
      *(undefined8 *)(pfVar5 + 8) = uStack_120;
      *(undefined8 *)(pfVar5 + 0xe) = uStack_108;
      *(undefined8 *)(pfVar5 + 0xc) = uStack_110;
      *(undefined8 *)(pfVar5 + 0x12) = uStack_f8;
      *(undefined8 *)(pfVar5 + 0x10) = uStack_100;
      *(undefined1 *)(pfVar5 + -0x93) = 2;
      pfVar5[0x14] = fVar17;
      pfVar5[0x15] = fVar18;
      pfVar5[0x16] = fVar14;
      pfVar5[0x17] = uStack_b8._4_4_;
      pfVar5[0x18] = fVar7;
      pfVar5[0x19] = fVar8;
      pfVar5[0x1a] = fVar9;
      pfVar5[0x1b] = fVar12;
      *(undefined8 *)(pfVar5 + 0x1e) = uStack_158;
      *(undefined8 *)(pfVar5 + 0x1c) = uStack_160;
      *(undefined8 *)(pfVar5 + 0x22) = uStack_148;
      *(undefined8 *)(pfVar5 + 0x20) = uStack_150;
      *(undefined8 *)(pfVar5 + 0x26) = uStack_138;
      *(undefined8 *)(pfVar5 + 0x24) = uStack_140;
      pfVar5 = pfVar5 + 0x154;
    } while (lVar4 < lVar6);
  }
  return;
}

// ==== Aska::Light::CalcIBLLocalMatrix(Aska::Matrix*)
// vaddr 0x213e668 | ghidra 0x223e668 | size 436 | symbol _ZN4Aska5Light18CalcIBLLocalMatrixEPNS_6MatrixE | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska5Light18CalcIBLLocalMatrixEPNS_6MatrixE(long param_1,float *param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  undefined8 uVar4;
  long lVar5;
  float fVar6;
  undefined8 uVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  
  uVar4 = _UNK_027dbb38;
  uVar7 = _UNK_027dbb30;
  lVar5 = *(long *)(param_1 + 0x400);
  if (lVar5 != 0) {
    uVar7 = *(undefined8 *)(lVar5 + 0x130);
    *(undefined8 *)(param_2 + 2) = *(undefined8 *)(lVar5 + 0x138);
    *(undefined8 *)param_2 = uVar7;
    uVar7 = *(undefined8 *)(lVar5 + 0x140);
    *(undefined8 *)(param_2 + 6) = *(undefined8 *)(lVar5 + 0x148);
    *(undefined8 *)(param_2 + 4) = uVar7;
    uVar7 = *(undefined8 *)(lVar5 + 0x150);
    *(undefined8 *)(param_2 + 10) = *(undefined8 *)(lVar5 + 0x158);
    *(undefined8 *)(param_2 + 8) = uVar7;
    uVar7 = *(undefined8 *)(lVar5 + 0x160);
    *(undefined8 *)(param_2 + 0xe) = *(undefined8 *)(lVar5 + 0x168);
    *(undefined8 *)(param_2 + 0xc) = uVar7;
    return;
  }
  fVar11 = *(float *)(param_1 + 0x3b0);
  *param_2 = fVar11;
  fVar12 = *(float *)(param_1 + 0x3b4);
  param_2[1] = fVar12;
  fVar13 = *(float *)(param_1 + 0x3b8);
  param_2[2] = fVar13;
  fVar1 = *(float *)(param_1 + 0x3bc);
  param_2[3] = fVar1;
  fVar15 = *(float *)(param_1 + 0x3c0);
  param_2[4] = fVar15;
  fVar16 = *(float *)(param_1 + 0x3c4);
  param_2[5] = fVar16;
  fVar17 = *(float *)(param_1 + 0x3c8);
  param_2[6] = fVar17;
  fVar2 = *(float *)(param_1 + 0x3cc);
  param_2[7] = fVar2;
  fVar18 = *(float *)(param_1 + 0x3d0);
  param_2[8] = fVar18;
  fVar10 = *(float *)(param_1 + 0x3d4);
  param_2[9] = fVar10;
  fVar14 = *(float *)(param_1 + 0x3d8);
  param_2[10] = fVar14;
  fVar3 = *(float *)(param_1 + 0x3dc);
  *(undefined8 *)(param_2 + 0xe) = uVar4;
  *(undefined8 *)(param_2 + 0xc) = uVar7;
  param_2[0xb] = fVar3;
  fVar6 = 1.0 / *(float *)(param_1 + 0x3a0);
  fVar8 = 1.0 / *(float *)(param_1 + 0x3a4);
  fVar9 = 1.0 / *(float *)(param_1 + 0x3a8);
  fVar11 = fVar6 * fVar11;
  fVar12 = fVar6 * fVar12;
  fVar13 = fVar6 * fVar13;
  fVar15 = fVar8 * fVar15;
  fVar16 = fVar8 * fVar16;
  fVar17 = fVar8 * fVar17;
  fVar18 = fVar9 * fVar18;
  fVar10 = fVar9 * fVar10;
  fVar14 = fVar9 * fVar14;
  *param_2 = fVar11;
  param_2[1] = fVar12;
  param_2[2] = fVar13;
  param_2[3] = fVar6 * fVar1;
  param_2[4] = fVar15;
  param_2[5] = fVar16;
  param_2[6] = fVar17;
  param_2[7] = fVar8 * fVar2;
  param_2[8] = fVar18;
  param_2[9] = fVar10;
  param_2[10] = fVar14;
  param_2[0xb] = fVar9 * fVar3;
  param_2[3] = -(fVar11 * *(float *)(param_1 + 0x390) + fVar12 * *(float *)(param_1 + 0x394) +
                fVar13 * *(float *)(param_1 + 0x398));
  param_2[7] = -(fVar15 * *(float *)(param_1 + 0x390) + fVar16 * *(float *)(param_1 + 0x394) +
                fVar17 * *(float *)(param_1 + 0x398));
  param_2[0xb] = -(fVar18 * *(float *)(param_1 + 0x390) + fVar10 * *(float *)(param_1 + 0x394) +
                  fVar14 * *(float *)(param_1 + 0x398));
  (*(code *)PTR__ZN4Aska6Matrix3MulEPKS0__02c93898)(param_2,param_1 + 0x130);
  return;
}

// ==== Aska::LightManager::MakeLightContext(Aska::AofObject*, Aska::LightManager::LightContext*, unsigned char*)
// vaddr 0x213e81c | ghidra 0x223e81c | size 7716 | symbol _ZN4Aska12LightManager16MakeLightContextEPNS_9AofObjectEPNS0_12LightContextEPh | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8
_ZN4Aska12LightManager16MakeLightContextEPNS_9AofObjectEPNS0_12LightContextEPh
          (long param_1,long param_2,long param_3,long param_4)

{
  undefined1 (*pauVar1) [16];
  uint3 *puVar2;
  ulong uVar3;
  long lVar4;
  char cVar5;
  uint3 uVar6;
  float fVar7;
  undefined8 uVar8;
  float fVar9;
  float fVar10;
  bool bVar11;
  bool bVar12;
  int iVar13;
  uint uVar14;
  int iVar15;
  int iVar16;
  int iVar17;
  undefined8 *puVar18;
  long lVar19;
  undefined1 *puVar20;
  long lVar21;
  float *pfVar22;
  uint uVar23;
  undefined4 uVar24;
  ulong uVar25;
  uint uVar26;
  long *plVar27;
  float *pfVar28;
  int iVar29;
  uint uVar30;
  ulong uVar31;
  long lVar32;
  int iVar33;
  ushort uVar34;
  ulong uVar35;
  int iVar36;
  ulong uVar37;
  long lVar38;
  long lVar39;
  ulong uVar40;
  uint uVar41;
  float fVar42;
  float fVar43;
  undefined8 uVar44;
  undefined1 auVar45 [16];
  undefined1 auVar46 [16];
  undefined8 uVar50;
  undefined1 auVar47 [16];
  undefined1 auVar48 [16];
  undefined1 auVar49 [16];
  float fVar51;
  undefined8 uVar52;
  undefined8 uVar53;
  undefined8 uVar54;
  float fVar55;
  float fVar56;
  float fVar57;
  uint uStack_be8;
  ulong uStack_bd8;
  long lStack_bb8;
  uint uStack_b60;
  float *pfStack_b40;
  ulong uStack_b38;
  undefined8 uStack_b30;
  undefined8 uStack_b28;
  float afStack_b20 [2];
  undefined8 uStack_b18;
  float afStack_b10 [2];
  char acStack_b08 [2024];
  long alStack_320 [32];
  long alStack_220 [2];
  byte abStack_20c [12];
  float afStack_200 [12];
  long alStack_1d0 [4];
  long lStack_1b0;
  long lStack_1a8;
  long lStack_1a0;
  long lStack_198;
  long lStack_190;
  long lStack_188;
  long lStack_180;
  long lStack_178;
  byte abStack_170 [16];
  float afStack_160 [16];
  long alStack_120 [4];
  long lStack_100;
  long lStack_f8;
  long lStack_f0;
  long lStack_e8;
  long lStack_e0;
  long lStack_d8;
  long lStack_d0;
  long lStack_c8;
  long lStack_c0;
  long lStack_b8;
  long lStack_b0;
  long lStack_a8;
  
  iVar13 = Aska::AofObject::GetActualLightConfiguration() const(param_2);
  if (iVar13 == 0) {
    uVar14 = 0;
    bVar11 = false;
    uVar34 = 1;
    uStack_be8 = (uint)*(ushort *)(param_1 + 0x300a);
  }
  else {
    uStack_be8 = *(uint *)(PTR__ZN4Aska13ObjectManager20m_LightConfigurationE_02cbf638 +
                          (long)iVar13 * 4 + 2);
    uVar34 = (ushort)((uStack_be8 & 0x7000) != 0);
    bVar11 = (uStack_be8 >> 0x10 & 7) != 0;
    uVar14 = uStack_be8 >> 0x10 & 7;
  }
  memset(alStack_120,0,0x80);
  pauVar1 = (undefined1 (*) [16])(param_3 + 0x10);
  afStack_160[0xe] = 0.0;
  afStack_160[0xf] = 0.0;
  afStack_160[0xc] = 0.0;
  afStack_160[0xd] = 0.0;
  afStack_160[10] = 0.0;
  afStack_160[0xb] = 0.0;
  afStack_160[8] = 0.0;
  afStack_160[9] = 0.0;
  afStack_160[6] = 0.0;
  afStack_160[7] = 0.0;
  afStack_160[4] = 0.0;
  afStack_160[5] = 0.0;
  afStack_160[2] = 0.0;
  afStack_160[3] = 0.0;
  afStack_160[0] = 0.0;
  afStack_160[1] = 0.0;
  memset(pauVar1,0,0x90);
  memset(alStack_1d0,0,0x60);
  fVar10 = _UNK_029cc100;
  fVar9 = _UNK_0296acf8;
  fVar7 = _UNK_027daba4;
  afStack_200[10] = 0.0;
  afStack_200[0xb] = 0.0;
  afStack_200[8] = 0.0;
  afStack_200[9] = 0.0;
  afStack_200[6] = 0.0;
  afStack_200[7] = 0.0;
  afStack_200[4] = 0.0;
  afStack_200[5] = 0.0;
  afStack_200[2] = 0.0;
  afStack_200[3] = 0.0;
  afStack_200[0] = 0.0;
  afStack_200[1] = 0.0;
  if (*(ushort *)(param_1 + 0x2ff8) == 0) {
    pfStack_b40 = (float *)0x0;
    uVar41 = 0;
    iVar36 = 0;
    uStack_b38 = 0;
  }
  else {
    uStack_b38 = 0;
    uVar31 = *(ulong *)(param_2 + 0x260);
    uVar41 = 0;
    iVar36 = 0;
    iVar17 = 0;
    uVar30 = 0;
    lVar39 = 0x1fe;
    do {
      pfStack_b40 = afStack_b20 + (long)(int)uVar30 * 8;
      if (0x3f < (int)uVar30) break;
      lVar19 = *(long *)(param_1 + lVar39 * 8);
      if ((*(ulong *)(lVar19 + 0x2a8) & uVar31) != 0) {
        puVar2 = (uint3 *)(lVar19 + 0x2a5);
        uVar6 = *puVar2;
        if ((*(byte *)(lVar19 + 0x2a7) & 1) == 0) {
          uVar23 = (uint)*(byte *)(lVar19 + 0x2a1);
          if ((uVar6 & 0x2000) == 0) {
            if ((uVar23 == 7) || (((uVar6 & 0x200) != 0 && (uVar23 - 4 < 3)))) {
              if (iVar17 < 0x20) {
                *(byte *)(lVar19 + 0x2a7) = *(byte *)(lVar19 + 0x2a7);
                *(ushort *)puVar2 = (ushort)uVar6 | 2;
                alStack_320[iVar17] = lVar19;
                iVar17 = iVar17 + 1;
              }
            }
            else if (uVar23 - 4 < 3) {
              fVar42 = (float)Aska::Light::CalcHemisphereIntensity(Aska::RenderableObject*)(lVar19,param_2);
              if ((fVar7 < fVar42) || (fVar42 < fVar9)) {
                auVar45._0_8_ = CONCAT44(fVar42,fVar42);
                auVar45._8_4_ = fVar42;
                auVar45._12_4_ = fVar42;
                *(ushort *)puVar2 = *(ushort *)puVar2 | 2;
                uStack_b28 = auVar45._8_8_;
                uStack_b30 = auVar45._0_8_;
                Aska::LightManager::CalcHemisphereLightCoeffs(Aska::LightManager::SHAmbConst*, Aska::Light const*, Aska::Vector*)(param_1,pauVar1,lVar19,&uStack_b30);
              }
            }
            else if ((uVar23 != 2) ||
                    ((1L << ((long)*(char *)(lVar19 + 0x2a3) & 0x3fU) &
                     *(ulong *)(param_2 + ((long)*(char *)(lVar19 + 0x2a3) >> 6) * 8 + 0x1e8)) != 0)
                    ) {
              uVar37 = *(ulong *)(lVar19 + 0x2b0);
              fVar42 = (float)Aska::Light::CalcIntensityTS(Aska::RenderableObject*, Aska::Light::CalcIntensityWork*, bool, bool, float*, float*, float*) const(lVar19,param_2,pfStack_b40,
                                              bVar11 | (uVar37 & uVar31) != 0,iVar13 != 0,0,0,0);
              if (fVar42 != 0.0) {
                fVar42 = ABS(fVar42);
                if (*(char *)(lVar19 + 0x2a2) != '\0') {
                  fVar42 = fVar10;
                }
                auVar46 = ZEXT416((uint)fVar42);
                if (((uVar37 & uVar31) == 0) && (acStack_b08[(long)(int)uVar30 * 0x20] != '\0')) {
                  acStack_b08[(long)(int)uVar30 * 0x20] = '\0';
                }
                if ((*(ushort *)puVar2 >> 3 & 1) == 0) {
                  uVar23 = uVar30;
                  if (fVar42 <= afStack_160[0]) {
                    bVar12 = false;
                    lVar32 = lVar19;
code_r0x0223eed0:
                    lVar19 = lVar32;
                    uVar37 = (ulong)(uint)afStack_160[1];
                    uVar53 = auVar46._8_8_;
                    if (auVar46._0_4_ <= afStack_160[1]) {
                      uVar37 = auVar46._0_8_;
                      lVar32 = lVar19;
                    }
                    else {
                      if (alStack_120[1] == 0) {
                        lVar32 = 1;
                        pfVar22 = (float *)((ulong)afStack_160 | 4);
                        plVar27 = alStack_120 + 1;
                        goto code_r0x0223f674;
                      }
                      uVar26 = (uint)abStack_170[1];
                      abStack_170[1] = (byte)uVar23;
                      bVar12 = true;
                      lVar32 = alStack_120[1];
                      uVar53 = 0;
                      uVar23 = uVar26;
                      alStack_120[1] = lVar19;
                      afStack_160[1] = auVar46._0_4_;
                    }
                    lVar19 = lVar32;
                    auVar46 = ZEXT416((uint)afStack_160[2]);
                    if ((float)uVar37 <= afStack_160[2]) {
                      auVar46._8_8_ = uVar53;
                      auVar46._0_8_ = uVar37;
                      lVar32 = lVar19;
                    }
                    else {
                      if (alStack_120[2] == 0) {
                        auVar46._8_8_ = uVar53;
                        auVar46._0_8_ = uVar37;
                        lVar32 = 2;
                        pfVar22 = afStack_160 + 2;
                        plVar27 = alStack_120 + 2;
                        goto code_r0x0223f674;
                      }
                      uVar26 = (uint)abStack_170[2];
                      abStack_170[2] = (byte)uVar23;
                      bVar12 = true;
                      lVar32 = alStack_120[2];
                      uVar23 = uVar26;
                      alStack_120[2] = lVar19;
                      afStack_160[2] = (float)uVar37;
                    }
                    lVar19 = lVar32;
                    uVar37 = (ulong)(uint)afStack_160[3];
                    uVar53 = auVar46._8_8_;
                    if (auVar46._0_4_ <= afStack_160[3]) {
                      uVar37 = auVar46._0_8_;
                      lVar32 = lVar19;
                    }
                    else {
                      if (alStack_120[3] == 0) {
                        lVar32 = 3;
                        pfVar22 = afStack_160 + 3;
                        plVar27 = alStack_120 + 3;
                        goto code_r0x0223f674;
                      }
                      uVar26 = (uint)abStack_170[3];
                      abStack_170[3] = (byte)uVar23;
                      bVar12 = true;
                      lVar32 = alStack_120[3];
                      uVar53 = 0;
                      uVar23 = uVar26;
                      alStack_120[3] = lVar19;
                      afStack_160[3] = auVar46._0_4_;
                    }
                    lVar19 = lVar32;
                    auVar46 = ZEXT416((uint)afStack_160[4]);
                    if ((float)uVar37 <= afStack_160[4]) {
                      auVar46._8_8_ = uVar53;
                      auVar46._0_8_ = uVar37;
                      lVar32 = lVar19;
                    }
                    else {
                      if (lStack_100 == 0) {
                        auVar46._8_8_ = uVar53;
                        auVar46._0_8_ = uVar37;
                        lVar32 = 4;
                        pfVar22 = afStack_160 + 4;
                        plVar27 = &lStack_100;
                        goto code_r0x0223f674;
                      }
                      uVar26 = (uint)abStack_170[4];
                      abStack_170[4] = (byte)uVar23;
                      bVar12 = true;
                      lVar32 = lStack_100;
                      uVar23 = uVar26;
                      lStack_100 = lVar19;
                      afStack_160[4] = (float)uVar37;
                    }
                    lVar19 = lVar32;
                    uVar37 = (ulong)(uint)afStack_160[5];
                    uVar53 = auVar46._8_8_;
                    if (auVar46._0_4_ <= afStack_160[5]) {
                      uVar37 = auVar46._0_8_;
                      lVar32 = lVar19;
                    }
                    else {
                      if (lStack_f8 == 0) {
                        lVar32 = 5;
                        pfVar22 = afStack_160 + 5;
                        plVar27 = &lStack_f8;
                        goto code_r0x0223f674;
                      }
                      uVar26 = (uint)abStack_170[5];
                      abStack_170[5] = (byte)uVar23;
                      bVar12 = true;
                      lVar32 = lStack_f8;
                      uVar53 = 0;
                      uVar23 = uVar26;
                      lStack_f8 = lVar19;
                      afStack_160[5] = auVar46._0_4_;
                    }
                    lVar19 = lVar32;
                    auVar46 = ZEXT416((uint)afStack_160[6]);
                    if ((float)uVar37 <= afStack_160[6]) {
                      auVar46._8_8_ = uVar53;
                      auVar46._0_8_ = uVar37;
                      lVar32 = lVar19;
                    }
                    else {
                      if (lStack_f0 == 0) {
                        auVar46._8_8_ = uVar53;
                        auVar46._0_8_ = uVar37;
                        lVar32 = 6;
                        pfVar22 = afStack_160 + 6;
                        plVar27 = &lStack_f0;
                        goto code_r0x0223f674;
                      }
                      uVar26 = (uint)abStack_170[6];
                      abStack_170[6] = (byte)uVar23;
                      bVar12 = true;
                      lVar32 = lStack_f0;
                      uVar23 = uVar26;
                      lStack_f0 = lVar19;
                      afStack_160[6] = (float)uVar37;
                    }
                    lVar19 = lVar32;
                    uVar37 = (ulong)(uint)afStack_160[7];
                    uVar53 = auVar46._8_8_;
                    if (auVar46._0_4_ <= afStack_160[7]) {
                      uVar37 = auVar46._0_8_;
                      lVar32 = lVar19;
                    }
                    else {
                      if (lStack_e8 == 0) {
                        lVar32 = 7;
                        pfVar22 = afStack_160 + 7;
                        plVar27 = &lStack_e8;
                        goto code_r0x0223f674;
                      }
                      uVar26 = (uint)abStack_170[7];
                      abStack_170[7] = (byte)uVar23;
                      bVar12 = true;
                      lVar32 = lStack_e8;
                      uVar53 = 0;
                      uVar23 = uVar26;
                      lStack_e8 = lVar19;
                      afStack_160[7] = auVar46._0_4_;
                    }
                    lVar19 = lVar32;
                    auVar46 = ZEXT416((uint)afStack_160[8]);
                    if ((float)uVar37 <= afStack_160[8]) {
                      auVar46._8_8_ = uVar53;
                      auVar46._0_8_ = uVar37;
                      lVar32 = lVar19;
                    }
                    else {
                      if (lStack_e0 == 0) {
                        auVar46._8_8_ = uVar53;
                        auVar46._0_8_ = uVar37;
                        lVar32 = 8;
                        pfVar22 = afStack_160 + 8;
                        plVar27 = &lStack_e0;
                        goto code_r0x0223f674;
                      }
                      uVar26 = (uint)abStack_170[8];
                      abStack_170[8] = (byte)uVar23;
                      bVar12 = true;
                      lVar32 = lStack_e0;
                      uVar23 = uVar26;
                      lStack_e0 = lVar19;
                      afStack_160[8] = (float)uVar37;
                    }
                    lVar19 = lVar32;
                    uVar37 = (ulong)(uint)afStack_160[9];
                    uVar53 = auVar46._8_8_;
                    if (auVar46._0_4_ <= afStack_160[9]) {
                      uVar37 = auVar46._0_8_;
                      lVar32 = lVar19;
                    }
                    else {
                      if (lStack_d8 == 0) {
                        lVar32 = 9;
                        pfVar22 = afStack_160 + 9;
                        plVar27 = &lStack_d8;
                        goto code_r0x0223f674;
                      }
                      uVar26 = (uint)abStack_170[9];
                      abStack_170[9] = (byte)uVar23;
                      bVar12 = true;
                      lVar32 = lStack_d8;
                      uVar53 = 0;
                      uVar23 = uVar26;
                      lStack_d8 = lVar19;
                      afStack_160[9] = auVar46._0_4_;
                    }
                    lVar19 = lVar32;
                    auVar46 = ZEXT416((uint)afStack_160[10]);
                    if ((float)uVar37 <= afStack_160[10]) {
                      auVar46._8_8_ = uVar53;
                      auVar46._0_8_ = uVar37;
                      lVar32 = lVar19;
                    }
                    else {
                      if (lStack_d0 == 0) {
                        auVar46._8_8_ = uVar53;
                        auVar46._0_8_ = uVar37;
                        lVar32 = 10;
                        pfVar22 = afStack_160 + 10;
                        plVar27 = &lStack_d0;
                        goto code_r0x0223f674;
                      }
                      uVar26 = (uint)abStack_170[10];
                      abStack_170[10] = (byte)uVar23;
                      bVar12 = true;
                      lVar32 = lStack_d0;
                      uVar23 = uVar26;
                      lStack_d0 = lVar19;
                      afStack_160[10] = (float)uVar37;
                    }
                    lVar19 = lVar32;
                    uVar37 = (ulong)(uint)afStack_160[0xb];
                    uVar53 = auVar46._8_8_;
                    if (auVar46._0_4_ <= afStack_160[0xb]) {
                      uVar37 = auVar46._0_8_;
                      lVar32 = lVar19;
                    }
                    else {
                      if (lStack_c8 == 0) {
                        lVar32 = 0xb;
                        pfVar22 = afStack_160 + 0xb;
                        plVar27 = &lStack_c8;
                        goto code_r0x0223f674;
                      }
                      uVar26 = (uint)abStack_170[0xb];
                      abStack_170[0xb] = (byte)uVar23;
                      bVar12 = true;
                      lVar32 = lStack_c8;
                      uVar53 = 0;
                      uVar23 = uVar26;
                      lStack_c8 = lVar19;
                      afStack_160[0xb] = auVar46._0_4_;
                    }
                    lVar19 = lVar32;
                    auVar46 = ZEXT416((uint)afStack_160[0xc]);
                    if ((float)uVar37 <= afStack_160[0xc]) {
                      auVar46._8_8_ = uVar53;
                      auVar46._0_8_ = uVar37;
                      lVar32 = lVar19;
                    }
                    else {
                      if (lStack_c0 == 0) {
                        auVar46._8_8_ = uVar53;
                        auVar46._0_8_ = uVar37;
                        lVar32 = 0xc;
                        pfVar22 = afStack_160 + 0xc;
                        plVar27 = &lStack_c0;
                        goto code_r0x0223f674;
                      }
                      uVar26 = (uint)abStack_170[0xc];
                      abStack_170[0xc] = (byte)uVar23;
                      bVar12 = true;
                      lVar32 = lStack_c0;
                      uVar23 = uVar26;
                      lStack_c0 = lVar19;
                      afStack_160[0xc] = (float)uVar37;
                    }
                    lVar19 = lVar32;
                    uVar37 = (ulong)(uint)afStack_160[0xd];
                    uVar53 = auVar46._8_8_;
                    if (auVar46._0_4_ <= afStack_160[0xd]) {
                      uVar37 = auVar46._0_8_;
                      lVar32 = lVar19;
                    }
                    else {
                      if (lStack_b8 == 0) {
                        lVar32 = 0xd;
                        pfVar22 = afStack_160 + 0xd;
                        plVar27 = &lStack_b8;
                        goto code_r0x0223f674;
                      }
                      uVar26 = (uint)abStack_170[0xd];
                      abStack_170[0xd] = (byte)uVar23;
                      bVar12 = true;
                      lVar32 = lStack_b8;
                      uVar53 = 0;
                      uVar23 = uVar26;
                      lStack_b8 = lVar19;
                      afStack_160[0xd] = auVar46._0_4_;
                    }
                    lVar19 = lVar32;
                    auVar46 = ZEXT416((uint)afStack_160[0xe]);
                    if ((float)uVar37 <= afStack_160[0xe]) {
                      auVar46._8_8_ = uVar53;
                      auVar46._0_8_ = uVar37;
                      lVar38 = lVar19;
                    }
                    else {
                      if (lStack_b0 == 0) {
                        auVar46._8_8_ = uVar53;
                        auVar46._0_8_ = uVar37;
                        lVar32 = 0xe;
                        pfVar22 = afStack_160 + 0xe;
                        plVar27 = &lStack_b0;
                        goto code_r0x0223f674;
                      }
                      uVar26 = (uint)abStack_170[0xe];
                      abStack_170[0xe] = (byte)uVar23;
                      bVar12 = true;
                      lVar38 = lStack_b0;
                      uVar23 = uVar26;
                      lStack_b0 = lVar19;
                      afStack_160[0xe] = (float)uVar37;
                    }
                    if (auVar46._0_4_ <= afStack_160[0xf]) {
joined_r0x0223f4cc:
                      if (!bVar12) goto code_r0x0223ebbc;
                      goto code_r0x0223f68c;
                    }
                    if (lStack_a8 != 0) {
                      abStack_170[0xf] = (byte)uVar23;
                      lStack_a8 = lVar38;
                      afStack_160[0xf] = auVar46._0_4_;
                      goto code_r0x0223f68c;
                    }
                    lVar32 = 0xf;
                    pfVar22 = afStack_160 + 0xf;
                    plVar27 = &lStack_a8;
                    lVar19 = lVar38;
                  }
                  else {
                    if (alStack_120[0] != 0) {
                      bVar12 = true;
                      auVar46 = ZEXT416((uint)afStack_160[0]);
                      lVar32 = alStack_120[0];
                      uVar23 = (uint)abStack_170[0];
                      abStack_170[0] = (byte)uVar30;
                      alStack_120[0] = lVar19;
                      afStack_160[0] = fVar42;
                      goto code_r0x0223eed0;
                    }
                    lVar32 = 0;
                    pfVar22 = afStack_160;
                    plVar27 = alStack_120;
                  }
code_r0x0223f674:
                  *plVar27 = lVar19;
                  *pfVar22 = auVar46._0_4_;
                  abStack_170[lVar32] = (byte)uVar23;
                  uVar41 = uVar41 + 1;
                }
                else {
                  uVar23 = uVar30;
                  if (fVar42 <= afStack_200[0]) {
                    bVar12 = false;
                    lVar32 = lVar19;
code_r0x0223ef0c:
                    lVar19 = lVar32;
                    uVar37 = (ulong)(uint)afStack_200[1];
                    uVar53 = auVar46._8_8_;
                    if (auVar46._0_4_ <= afStack_200[1]) {
                      uVar37 = auVar46._0_8_;
                      lVar32 = lVar19;
                    }
                    else {
                      if (alStack_1d0[1] == 0) {
                        lVar32 = 1;
                        pfVar22 = (float *)((ulong)afStack_200 | 4);
                        plVar27 = alStack_1d0 + 1;
                        goto code_r0x0223f624;
                      }
                      uVar26 = (uint)abStack_20c[1];
                      abStack_20c[1] = (byte)uVar23;
                      bVar12 = true;
                      lVar32 = alStack_1d0[1];
                      uVar53 = 0;
                      uVar23 = uVar26;
                      alStack_1d0[1] = lVar19;
                      afStack_200[1] = auVar46._0_4_;
                    }
                    lVar19 = lVar32;
                    auVar46 = ZEXT416((uint)afStack_200[2]);
                    if ((float)uVar37 <= afStack_200[2]) {
                      auVar46._8_8_ = uVar53;
                      auVar46._0_8_ = uVar37;
                      lVar32 = lVar19;
                    }
                    else {
                      if (alStack_1d0[2] == 0) {
                        auVar46._8_8_ = uVar53;
                        auVar46._0_8_ = uVar37;
                        lVar32 = 2;
                        pfVar22 = afStack_200 + 2;
                        plVar27 = alStack_1d0 + 2;
                        goto code_r0x0223f624;
                      }
                      uVar26 = (uint)abStack_20c[2];
                      abStack_20c[2] = (byte)uVar23;
                      bVar12 = true;
                      lVar32 = alStack_1d0[2];
                      uVar23 = uVar26;
                      alStack_1d0[2] = lVar19;
                      afStack_200[2] = (float)uVar37;
                    }
                    lVar19 = lVar32;
                    uVar37 = (ulong)(uint)afStack_200[3];
                    uVar53 = auVar46._8_8_;
                    if (auVar46._0_4_ <= afStack_200[3]) {
                      uVar37 = auVar46._0_8_;
                      lVar32 = lVar19;
                    }
                    else {
                      if (alStack_1d0[3] == 0) {
                        lVar32 = 3;
                        pfVar22 = afStack_200 + 3;
                        plVar27 = alStack_1d0 + 3;
                        goto code_r0x0223f624;
                      }
                      uVar26 = (uint)abStack_20c[3];
                      abStack_20c[3] = (byte)uVar23;
                      bVar12 = true;
                      lVar32 = alStack_1d0[3];
                      uVar53 = 0;
                      uVar23 = uVar26;
                      alStack_1d0[3] = lVar19;
                      afStack_200[3] = auVar46._0_4_;
                    }
                    lVar19 = lVar32;
                    auVar46 = ZEXT416((uint)afStack_200[4]);
                    if ((float)uVar37 <= afStack_200[4]) {
                      auVar46._8_8_ = uVar53;
                      auVar46._0_8_ = uVar37;
                      lVar32 = lVar19;
                    }
                    else {
                      if (lStack_1b0 == 0) {
                        auVar46._8_8_ = uVar53;
                        auVar46._0_8_ = uVar37;
                        lVar32 = 4;
                        pfVar22 = afStack_200 + 4;
                        plVar27 = &lStack_1b0;
                        goto code_r0x0223f624;
                      }
                      uVar26 = (uint)abStack_20c[4];
                      abStack_20c[4] = (byte)uVar23;
                      bVar12 = true;
                      lVar32 = lStack_1b0;
                      uVar23 = uVar26;
                      lStack_1b0 = lVar19;
                      afStack_200[4] = (float)uVar37;
                    }
                    lVar19 = lVar32;
                    uVar37 = (ulong)(uint)afStack_200[5];
                    uVar53 = auVar46._8_8_;
                    if (auVar46._0_4_ <= afStack_200[5]) {
                      uVar37 = auVar46._0_8_;
                      lVar32 = lVar19;
                    }
                    else {
                      if (lStack_1a8 == 0) {
                        lVar32 = 5;
                        pfVar22 = afStack_200 + 5;
                        plVar27 = &lStack_1a8;
                        goto code_r0x0223f624;
                      }
                      uVar26 = (uint)abStack_20c[5];
                      abStack_20c[5] = (byte)uVar23;
                      bVar12 = true;
                      lVar32 = lStack_1a8;
                      uVar53 = 0;
                      uVar23 = uVar26;
                      lStack_1a8 = lVar19;
                      afStack_200[5] = auVar46._0_4_;
                    }
                    lVar19 = lVar32;
                    auVar46 = ZEXT416((uint)afStack_200[6]);
                    if ((float)uVar37 <= afStack_200[6]) {
                      auVar46._8_8_ = uVar53;
                      auVar46._0_8_ = uVar37;
                      lVar32 = lVar19;
                    }
                    else {
                      if (lStack_1a0 == 0) {
                        auVar46._8_8_ = uVar53;
                        auVar46._0_8_ = uVar37;
                        lVar32 = 6;
                        pfVar22 = afStack_200 + 6;
                        plVar27 = &lStack_1a0;
                        goto code_r0x0223f624;
                      }
                      uVar26 = (uint)abStack_20c[6];
                      abStack_20c[6] = (byte)uVar23;
                      bVar12 = true;
                      lVar32 = lStack_1a0;
                      uVar23 = uVar26;
                      lStack_1a0 = lVar19;
                      afStack_200[6] = (float)uVar37;
                    }
                    lVar19 = lVar32;
                    uVar37 = (ulong)(uint)afStack_200[7];
                    uVar53 = auVar46._8_8_;
                    if (auVar46._0_4_ <= afStack_200[7]) {
                      uVar37 = auVar46._0_8_;
                      lVar32 = lVar19;
                    }
                    else {
                      if (lStack_198 == 0) {
                        lVar32 = 7;
                        pfVar22 = afStack_200 + 7;
                        plVar27 = &lStack_198;
                        goto code_r0x0223f624;
                      }
                      uVar26 = (uint)abStack_20c[7];
                      abStack_20c[7] = (byte)uVar23;
                      bVar12 = true;
                      lVar32 = lStack_198;
                      uVar53 = 0;
                      uVar23 = uVar26;
                      lStack_198 = lVar19;
                      afStack_200[7] = auVar46._0_4_;
                    }
                    lVar19 = lVar32;
                    auVar46 = ZEXT416((uint)afStack_200[8]);
                    if ((float)uVar37 <= afStack_200[8]) {
                      auVar46._8_8_ = uVar53;
                      auVar46._0_8_ = uVar37;
                      lVar32 = lVar19;
                    }
                    else {
                      if (lStack_190 == 0) {
                        auVar46._8_8_ = uVar53;
                        auVar46._0_8_ = uVar37;
                        lVar32 = 8;
                        pfVar22 = afStack_200 + 8;
                        plVar27 = &lStack_190;
                        goto code_r0x0223f624;
                      }
                      uVar26 = (uint)abStack_20c[8];
                      abStack_20c[8] = (byte)uVar23;
                      bVar12 = true;
                      lVar32 = lStack_190;
                      uVar23 = uVar26;
                      lStack_190 = lVar19;
                      afStack_200[8] = (float)uVar37;
                    }
                    lVar19 = lVar32;
                    uVar37 = (ulong)(uint)afStack_200[9];
                    uVar53 = auVar46._8_8_;
                    if (auVar46._0_4_ <= afStack_200[9]) {
                      uVar37 = auVar46._0_8_;
                      lVar32 = lVar19;
                    }
                    else {
                      if (lStack_188 == 0) {
                        lVar32 = 9;
                        pfVar22 = afStack_200 + 9;
                        plVar27 = &lStack_188;
                        goto code_r0x0223f624;
                      }
                      uVar26 = (uint)abStack_20c[9];
                      abStack_20c[9] = (byte)uVar23;
                      bVar12 = true;
                      lVar32 = lStack_188;
                      uVar53 = 0;
                      uVar23 = uVar26;
                      lStack_188 = lVar19;
                      afStack_200[9] = auVar46._0_4_;
                    }
                    lVar19 = lVar32;
                    auVar46 = ZEXT416((uint)afStack_200[10]);
                    if ((float)uVar37 <= afStack_200[10]) {
                      auVar46._8_8_ = uVar53;
                      auVar46._0_8_ = uVar37;
                      lVar38 = lVar19;
                    }
                    else {
                      if (lStack_180 == 0) {
                        auVar46._8_8_ = uVar53;
                        auVar46._0_8_ = uVar37;
                        lVar32 = 10;
                        pfVar22 = afStack_200 + 10;
                        plVar27 = &lStack_180;
                        goto code_r0x0223f624;
                      }
                      uVar26 = (uint)abStack_20c[10];
                      abStack_20c[10] = (byte)uVar23;
                      bVar12 = true;
                      lVar38 = lStack_180;
                      uVar23 = uVar26;
                      lStack_180 = lVar19;
                      afStack_200[10] = (float)uVar37;
                    }
                    if (auVar46._0_4_ <= afStack_200[0xb]) goto joined_r0x0223f4cc;
                    if (lStack_178 == 0) {
                      lVar32 = 0xb;
                      pfVar22 = afStack_200 + 0xb;
                      plVar27 = &lStack_178;
                      lVar19 = lVar38;
                      goto code_r0x0223f624;
                    }
                    abStack_20c[0xb] = (byte)uVar23;
                    lStack_178 = lVar38;
                    afStack_200[0xb] = auVar46._0_4_;
                  }
                  else {
                    if (alStack_1d0[0] != 0) {
                      bVar12 = true;
                      auVar46 = ZEXT416((uint)afStack_200[0]);
                      lVar32 = alStack_1d0[0];
                      uVar23 = (uint)abStack_20c[0];
                      abStack_20c[0] = (byte)uVar30;
                      alStack_1d0[0] = lVar19;
                      afStack_200[0] = fVar42;
                      goto code_r0x0223ef0c;
                    }
                    lVar32 = 0;
                    plVar27 = alStack_1d0;
                    pfVar22 = afStack_200;
code_r0x0223f624:
                    *pfVar22 = auVar46._0_4_;
                    iVar36 = iVar36 + 1;
                    *plVar27 = lVar19;
                    abStack_20c[lVar32] = (byte)uVar23;
                  }
                }
code_r0x0223f68c:
                uVar30 = uVar30 + 1;
              }
            }
          }
          else if ((uVar23 < 4) &&
                  ((uVar23 != 2 ||
                   ((1L << ((long)*(char *)(lVar19 + 0x2a3) & 0x3fU) &
                    *(ulong *)(param_2 + ((long)*(char *)(lVar19 + 0x2a3) >> 6) * 8 + 0x1e8)) != 0))
                  )) {
            fVar42 = (float)Aska::Light::CalcIntensityTS(Aska::RenderableObject*, Aska::Light::CalcIntensityWork*, bool, bool, float*, float*, float*) const(lVar19,param_2,pfStack_b40,0,0,0,0,0);
            iVar15 = (int)uStack_b38;
            if ((iVar15 < 2) && (fVar42 != 0.0)) {
              alStack_220[iVar15] = lVar19;
              *(ushort *)puVar2 = *(ushort *)puVar2 | 2;
              uStack_b38 = (ulong)(iVar15 + 1);
            }
          }
        }
      }
code_r0x0223ebbc:
      lVar19 = lVar39 + -0x1fd;
      lVar39 = lVar39 + 1;
    } while (lVar19 < (long)(ulong)*(ushort *)(param_1 + 0x2ff8));
    if (0 < iVar17) {
      Aska::LightManager::CalcBounceLightCoeffs(Aska::LightManager::SHAmbConst*, Aska::RenderableObject*, Aska::Light**, int, Aska::Light**, int)(param_1,pauVar1,param_2,alStack_320,iVar17,alStack_120,uVar41);
    }
  }
  *(undefined8 *)(param_3 + 0x88) = *(undefined8 *)(param_3 + 0x48);
  *(undefined8 *)(param_3 + 0x80) = *(undefined8 *)(param_3 + 0x40);
  *(undefined8 *)(param_3 + 0x78) = *(undefined8 *)(param_3 + 0x38);
  *(undefined8 *)(param_3 + 0x70) = *(undefined8 *)(param_3 + 0x30);
  *(undefined8 *)(param_3 + 0x68) = *(undefined8 *)(param_3 + 0x28);
  *(undefined8 *)(param_3 + 0x60) = *(undefined8 *)(param_3 + 0x20);
  *(long *)(param_3 + 0x58) = SUB168(*pauVar1,8);
  *(long *)(param_3 + 0x50) = SUB168(*pauVar1,0);
  if (param_4 == 0) {
    uVar31 = Aska::MaterialList::GetActualPerPixelLightCount() const(*(long *)(param_2 + 0x3d8) + 0xe8);
    uStack_bd8 = 0;
  }
  else if (*(char *)(param_4 + 4) == '\0') {
    if (*(char *)(param_4 + 3) == '\0') {
      if (*(char *)(param_4 + 2) == '\0') {
        uVar31 = (ulong)(*(char *)(param_4 + 1) != '\0');
        uStack_bd8 = uVar31;
      }
      else {
        uStack_bd8 = 2;
        uVar31 = 2;
      }
    }
    else {
      uStack_bd8 = 3;
      uVar31 = 3;
    }
  }
  else {
    uStack_bd8 = 4;
    uVar31 = 4;
  }
  if (iVar13 == 0) {
    uVar14 = (uint)uVar31;
  }
  if ((int)uVar41 <= (int)uVar14) {
    uVar14 = uVar41;
  }
  uVar31 = (ulong)uVar14;
  uVar37 = -(ulong)(uVar14 >> 0x1f) & 0xfffffff800000000 | uVar31 << 3;
  lVar39 = 0;
  if (uVar37 < 0x20) {
    lVar39 = 0x20 - uVar37;
  }
  memset(param_3 + 0x4e0 + uVar37,0,lVar39);
  memcpy(param_3 + 0x4e0,alStack_120,uVar37);
  uVar37 = -(uStack_b38 >> 0x1f) & 0xfffffff800000000 | uStack_b38 << 3;
  lVar39 = 0;
  if (uVar37 < 0x10) {
    lVar39 = 0x10 - uVar37;
  }
  memset(param_3 + 0x500 + uVar37,0,lVar39);
  memcpy(param_3 + 0x500,alStack_220,uVar37);
  fVar10 = _UNK_029cc3f4;
  fVar9 = _UNK_027ebdf4;
  fVar7 = _UNK_027e519c;
  uVar8 = _UNK_027dbb08;
  uVar53 = _UNK_027dbb00;
  bVar11 = true;
  if (*(char *)(param_2 + 0x3bc) == '\0') {
    if (((((*(long *)(param_2 + 0x438) == 0) && (*(char *)(param_2 + 0x3bd) == '\0')) &&
         (*(long *)(param_2 + 0x440) == 0)) &&
        ((*(char *)(param_2 + 0x3be) == '\0' && (*(long *)(param_2 + 0x448) == 0)))) &&
       (*(char *)(param_2 + 0x3bf) == '\0')) {
      bVar11 = *(long *)(param_2 + 0x450) != 0;
    }
    else {
      bVar11 = true;
    }
  }
  auVar46 = NEON_fmov(0x3f800000,4);
  uVar50 = auVar46._8_8_;
  uVar44 = auVar46._0_8_;
  uStack_b60 = uStack_be8 & 0xffff;
  uStack_be8 = uStack_be8 & 0x6000;
  uVar37 = 0;
  lStack_bb8 = 0;
  do {
    uVar35 = uVar31;
    if (param_4 == 0) {
      bVar12 = false;
      iVar17 = 4;
code_r0x0223f974:
      lVar39 = param_3 + uVar37 * 0x550;
      memset((undefined1 (*) [16])(lVar39 + 0x110),0,0x50);
      if (*(char *)(param_2 + 0x3bc) == '\0') {
        lVar19 = param_3 + uVar37 * 0x550;
        puVar18 = (undefined8 *)(lVar19 + 0x510);
        if (*(long *)(param_2 + 0x438) != 0) goto code_r0x0223f9c8;
        *(undefined8 *)(lVar19 + 0x518) = uVar50;
        *puVar18 = uVar44;
        if (*(char *)(param_2 + 0x3bd) != '\0') goto code_r0x0223f9d8;
code_r0x0223fa08:
        lVar19 = param_3 + uVar37 * 0x550;
        puVar18 = (undefined8 *)(lVar19 + 0x520);
        if (*(long *)(param_2 + 0x440) != 0) goto code_r0x0223fa1c;
        *(undefined8 *)(lVar19 + 0x528) = uVar50;
        *puVar18 = uVar44;
        if (*(char *)(param_2 + 0x3be) == '\0') goto code_r0x0223fa44;
code_r0x0223fa28:
        puVar18 = (undefined8 *)(param_3 + uVar37 * 0x550 + 0x530);
code_r0x0223fa58:
        *puVar18 = 0;
        puVar18[1] = 0;
        if (*(char *)(param_2 + 0x3bf) == '\0') goto code_r0x0223fa80;
code_r0x0223fa64:
        puVar18 = (undefined8 *)(param_3 + uVar37 * 0x550 + 0x540);
code_r0x0223fa94:
        *puVar18 = 0;
        puVar18[1] = 0;
      }
      else {
        puVar18 = (undefined8 *)(param_3 + uVar37 * 0x550 + 0x510);
code_r0x0223f9c8:
        *puVar18 = 0;
        puVar18[1] = 0;
        if (*(char *)(param_2 + 0x3bd) == '\0') goto code_r0x0223fa08;
code_r0x0223f9d8:
        puVar18 = (undefined8 *)(param_3 + uVar37 * 0x550 + 0x520);
code_r0x0223fa1c:
        *puVar18 = 0;
        puVar18[1] = 0;
        if (*(char *)(param_2 + 0x3be) != '\0') goto code_r0x0223fa28;
code_r0x0223fa44:
        lVar19 = param_3 + uVar37 * 0x550;
        puVar18 = (undefined8 *)(lVar19 + 0x530);
        if (*(long *)(param_2 + 0x448) != 0) goto code_r0x0223fa58;
        *(undefined8 *)(lVar19 + 0x538) = uVar50;
        *puVar18 = uVar44;
        if (*(char *)(param_2 + 0x3bf) != '\0') goto code_r0x0223fa64;
code_r0x0223fa80:
        lVar19 = param_3 + uVar37 * 0x550;
        puVar18 = (undefined8 *)(lVar19 + 0x540);
        if (*(long *)(param_2 + 0x450) != 0) goto code_r0x0223fa94;
        *(undefined8 *)(lVar19 + 0x548) = uVar50;
        *puVar18 = uVar44;
      }
      if (0x1000 < uStack_be8) {
        lVar19 = param_3 + uVar37 * 0x550;
        *(undefined8 *)(lVar19 + 0x308) = 0;
        *(undefined8 *)(lVar19 + 0x300) = 0;
        *(undefined8 *)(lVar19 + 0x318) = 0;
        *(undefined8 *)(lVar19 + 0x310) = 0;
      }
      puVar20 = (undefined1 *)(param_3 + uVar37 * 0x550);
      *puVar20 = (char)uVar35;
      *(undefined8 *)(puVar20 + 0xa0) = 0;
      *(undefined8 *)(puVar20 + 0xa8) = 0;
      if (0 < (int)uVar35) {
        uVar14 = 0;
        lVar19 = 0;
        lVar32 = param_3 + lStack_bb8;
        uVar25 = 0;
        do {
          *(undefined4 *)(lVar32 + uVar25 * 4 + 0xa0) = 0x3f800000;
          lVar38 = alStack_120[uVar25];
          uVar40 = (ulong)abStack_170[uVar25];
          pfStack_b40 = afStack_b20 + uVar40 * 8;
          *(undefined1 *)(lVar38 + 0x2a7) = *(undefined1 *)(lVar38 + 0x2a7);
          *(ushort *)(lVar38 + 0x2a5) = *(ushort *)(lVar38 + 0x2a5) | 2;
          if ((bVar11) && (iVar15 = Aska::AofObject::CheckLightMaskMixerLight(Aska::Light*) const(param_2,lVar38), -1 < iVar15)) {
            *(undefined4 *)(lVar32 + (long)iVar15 * 0x10 + uVar25 * 4 + 0x510) = 0x3f800000;
          }
          uVar3 = uVar25 + 1;
          uVar30 = uStack_b60 >> (ulong)(uVar14 & 0x1f) & 7;
          if (acStack_b08[uVar40 * 0x20] == '\0') {
            cVar5 = *(char *)(lVar38 + 0x2a1);
            if (uVar30 == 2) {
              if (cVar5 == '\0') goto code_r0x0223fc58;
              acStack_b08[uVar40 * 0x20] = '\x01';
              goto code_r0x0223fe28;
            }
            if (cVar5 == '\0') {
code_r0x0223fc58:
              lVar21 = lVar32 + lVar19;
              *(undefined4 *)(lVar21 + 0x120) = *(undefined4 *)(lVar38 + 0x290);
              *(undefined4 *)(lVar21 + 0x124) = *(undefined4 *)(lVar38 + 0x294);
              *(undefined4 *)(lVar21 + 0x128) = *(undefined4 *)(lVar38 + 0x298);
              *(undefined4 *)(lVar21 + 300) = *(undefined4 *)(lVar38 + 0x29c);
              pfVar22 = (float *)(lVar38 + 0x23c);
              goto code_r0x0223fe58;
            }
            if (cVar5 == '\x01') {
              lVar21 = lVar32 + lVar19;
              *(undefined4 *)(lVar21 + 0x110) = *(undefined4 *)(lVar38 + 0x200);
              *(undefined4 *)(lVar21 + 0x114) = *(undefined4 *)(lVar38 + 0x204);
              *(undefined4 *)(lVar21 + 0x118) = *(undefined4 *)(lVar38 + 0x208);
              *(undefined4 *)(lVar21 + 0x11c) = *(undefined4 *)(lVar38 + 0x20c);
              *(undefined4 *)(lVar21 + 0x140) = *(undefined4 *)(lVar38 + 0x220);
              *(undefined4 *)(lVar21 + 0x144) = *(undefined4 *)(lVar38 + 0x224);
              *(undefined4 *)(lVar21 + 0x148) = *(undefined4 *)(lVar38 + 0x228);
              *(undefined4 *)(lVar21 + 0x14c) = *(undefined4 *)(lVar38 + 0x22c);
              fVar42 = *(float *)(lVar38 + 0x23c) * *(float *)(lVar38 + 0x2fc);
              if (iVar13 != 2) {
                fVar42 = fVar42 * fVar9;
              }
              uVar52 = *(undefined8 *)(lVar38 + 0x230);
              *(float *)(lVar21 + 0x138) = (float)*(undefined8 *)(lVar38 + 0x238) * fVar42;
              *(undefined4 *)(lVar21 + 0x13c) = 0x3f800000;
              *(float *)(lVar21 + 0x130) = (float)uVar52 * fVar42;
              *(float *)(lVar21 + 0x134) = (float)((ulong)uVar52 >> 0x20) * fVar42;
              *(undefined8 *)(lVar21 + 0x124) = uVar8;
              *(undefined8 *)(lVar21 + 0x11c) = uVar53;
              *(undefined4 *)(lVar21 + 300) = 0xbf800000;
              uVar24 = 0x3f800000;
code_r0x0223fd20:
              lVar21 = lVar32 + lVar19;
              *(undefined4 *)(lVar21 + 0x13c) = uVar24;
              if ((*(float *)(lVar38 + 0x224) == 0.0) && (*(float *)(lVar38 + 0x228) == 0.0)) {
                *(undefined4 *)(lVar32 + lVar19 + 0x154) = 0x3f800000;
                *(undefined4 *)(lVar32 + lVar19 + 0x150) = 0;
              }
              else {
                fVar42 = *(float *)(lVar38 + 0x2cc) / *(float *)(lVar38 + 0x2c4);
                *(float *)(lVar21 + 0x150) = fVar42;
                *(float *)(lVar21 + 0x154) = fVar42;
                *(float *)(lVar21 + 0x158) = 1.0 / fVar42;
              }
              fVar42 = (float)tanf();
              *(float *)(lVar32 + lVar19 + 0x15c) = fVar42 * 0.5;
            }
            else if (cVar5 == '\x02') {
              lVar21 = lVar32 + lVar19;
              *(undefined4 *)(lVar21 + 0x110) = *(undefined4 *)(lVar38 + 0x200);
              *(undefined4 *)(lVar21 + 0x114) = *(undefined4 *)(lVar38 + 0x204);
              *(undefined4 *)(lVar21 + 0x118) = *(undefined4 *)(lVar38 + 0x208);
              *(undefined4 *)(lVar21 + 0x11c) = *(undefined4 *)(lVar38 + 0x20c);
              fVar42 = *(float *)(lVar38 + 0x290);
              *(float *)(lVar21 + 0x120) = fVar42;
              fVar43 = *(float *)(lVar38 + 0x294);
              *(float *)(lVar21 + 0x124) = fVar43;
              fVar51 = *(float *)(lVar38 + 0x298);
              *(float *)(lVar21 + 0x128) = fVar51;
              fVar43 = fVar42 * fVar42 + fVar43 * fVar43 + fVar51 * fVar51;
              fVar42 = SQRT(fVar43);
              *(undefined4 *)(lVar21 + 300) = *(undefined4 *)(lVar38 + 0x29c);
              if (NAN(fVar42)) {
                fVar42 = (float)sqrtf(fVar43);
              }
              if (fVar7 <= fVar42) {
                fVar42 = 1.0 / fVar42;
                *(float *)(lVar21 + 0x120) = fVar42 * *(float *)(lVar21 + 0x120);
                *(float *)(lVar21 + 0x124) = fVar42 * *(float *)(lVar21 + 0x124);
                *(float *)(lVar21 + 0x128) = fVar42 * *(float *)(lVar21 + 0x128);
              }
              fVar42 = *(float *)(lVar38 + 0x23c) * *(float *)(lVar38 + 0x2fc);
              if (iVar13 != 2) {
                fVar42 = fVar42 * fVar9;
              }
              if (uVar30 == 3) {
                fVar42 = fVar42 * afStack_b10[uVar40 * 8 + 1];
              }
              uVar52 = *(undefined8 *)(lVar38 + 0x230);
              lVar4 = lVar32 + lVar19;
              *(float *)(lVar4 + 0x138) = (float)*(undefined8 *)(lVar38 + 0x238) * fVar42;
              *(undefined4 *)(lVar4 + 0x13c) = 0x3f800000;
              *(float *)(lVar4 + 0x130) = (float)uVar52 * fVar42;
              *(float *)(lVar4 + 0x134) = (float)((ulong)uVar52 >> 0x20) * fVar42;
              *(undefined4 *)(lVar4 + 0x140) = *(undefined4 *)(lVar38 + 0x220);
              *(undefined4 *)(lVar4 + 0x144) = *(undefined4 *)(lVar38 + 0x224);
              *(undefined4 *)(lVar4 + 0x148) = *(undefined4 *)(lVar38 + 0x228);
              *(undefined4 *)(lVar4 + 0x14c) = *(undefined4 *)(lVar38 + 0x22c);
              *(undefined4 *)(lVar21 + 0x11c) = 0x3f800000;
              *(undefined4 *)(lVar21 + 300) = *(undefined4 *)(lVar38 + 0x2dc);
              uVar24 = *(undefined4 *)(lVar38 + 0x2e0);
              goto code_r0x0223fd20;
            }
          }
          else {
code_r0x0223fe28:
            uVar52 = *(undefined8 *)pfStack_b40;
            lVar21 = param_3 + uVar37 * 0x550 + uVar25 * 0x50;
            *(undefined8 *)(lVar32 + lVar19 + 0x128) = (&uStack_b18)[uVar40 * 4];
            *(undefined8 *)(lVar32 + lVar19 + 0x120) = uVar52;
            pfVar22 = afStack_b10 + uVar40 * 8;
code_r0x0223fe58:
            lVar4 = lVar32 + lVar19;
            fVar42 = *pfVar22 * *(float *)(lVar38 + 0x2fc);
            if (iVar13 != 2) {
              fVar42 = fVar42 * fVar9;
            }
            fVar51 = *(float *)(lVar4 + 0x120) * *(float *)(lVar4 + 0x120) +
                     *(float *)(lVar4 + 0x124) * *(float *)(lVar4 + 0x124) +
                     *(float *)(lVar4 + 0x128) * *(float *)(lVar4 + 0x128);
            fVar43 = SQRT(fVar51);
            if (NAN(fVar43)) {
              fVar43 = (float)sqrtf(fVar51);
            }
            if (fVar7 <= fVar43) {
              fVar43 = 1.0 / fVar43;
              *(float *)(lVar4 + 0x120) = fVar43 * *(float *)(lVar4 + 0x120);
              *(float *)(lVar4 + 0x124) = fVar43 * *(float *)(lVar4 + 0x124);
              *(float *)(lVar4 + 0x128) = fVar43 * *(float *)(lVar4 + 0x128);
            }
            uVar54 = *(undefined8 *)(lVar38 + 0x238);
            uVar52 = *(undefined8 *)(lVar38 + 0x230);
            lVar38 = lVar32 + lVar19;
            *(undefined4 *)(lVar38 + 0x11c) = 0;
            *(float *)(lVar38 + 0x138) = fVar42 * (float)uVar54;
            *(undefined4 *)(lVar38 + 0x13c) = 0x3f800000;
            *(float *)(lVar38 + 0x130) = fVar42 * (float)uVar52;
            *(float *)(lVar38 + 0x134) = fVar42 * (float)((ulong)uVar52 >> 0x20);
            fVar42 = (float)tanf();
            *(float *)(lVar38 + 0x15c) = fVar42 * 0.5 * fVar42 * 0.5;
            if (uVar30 - 3 < 2) {
              fVar42 = *(float *)(lVar21 + 0x120) * fVar10;
              fVar43 = *(float *)(lVar38 + 0x124) * fVar10;
              fVar51 = *(float *)(lVar38 + 0x128) * fVar10;
              *(float *)(lVar38 + 0x110) = *(float *)(lVar21 + 0x120);
              *(float *)(lVar38 + 0x114) = *(float *)(lVar38 + 0x124);
              *(float *)(lVar38 + 0x118) = *(float *)(lVar38 + 0x128);
              *(undefined4 *)(lVar38 + 0x11c) = *(undefined4 *)(lVar38 + 300);
              *(float *)(lVar38 + 0x110) = fVar42;
              *(float *)(lVar38 + 0x114) = fVar43;
              *(float *)(lVar38 + 0x118) = fVar51;
              fVar55 = *(float *)(param_2 + 0x4c);
              fVar56 = *(float *)(param_2 + 0x5c);
              fVar57 = *(float *)(param_2 + 0x6c);
              *(undefined8 *)(lVar38 + 0x148) = uVar8;
              *(undefined8 *)(lVar38 + 0x140) = uVar53;
              *(undefined4 *)(lVar38 + 0x11c) = 0x3f800000;
              *(undefined4 *)(lVar38 + 300) = 0xbf800000;
              *(undefined4 *)(lVar38 + 0x13c) = 0x3f800000;
              *(undefined4 *)(lVar38 + 0x150) = 0;
              *(float *)(lVar38 + 0x110) = fVar55 + fVar42;
              *(float *)(lVar38 + 0x114) = fVar56 + fVar43;
              *(float *)(lVar38 + 0x118) = fVar57 + fVar51;
              *(undefined4 *)(lVar38 + 0x154) = 0x3f800000;
            }
          }
          lVar19 = lVar19 + 0x50;
          uVar14 = uVar14 + 3;
          uVar25 = uVar3;
        } while (uVar35 != uVar3);
      }
      if ((ushort)(param_4 != 0 | uVar34 | *(ushort *)(param_2 + 0x37c) & 1) == 1) {
        iVar15 = 0;
        iVar33 = 0;
        uVar14 = 3;
        iVar29 = 0;
code_r0x02240090:
        do {
          do {
            iVar16 = (int)uVar35;
            if (iVar16 < (int)uVar41) {
              lVar19 = alStack_120[iVar16];
              pfStack_b40 = afStack_b20 + (ulong)abStack_170[iVar16] * 8;
              uVar35 = (ulong)(iVar16 + 1);
              if (iVar36 <= iVar15) goto code_r0x0224011c;
code_r0x022400bc:
              if (lVar19 == 0) {
code_r0x02240100:
                lVar19 = alStack_1d0[iVar15];
                pfStack_b40 = afStack_b20 + (ulong)abStack_20c[iVar15] * 8;
                iVar15 = iVar15 + 1;
                goto code_r0x0224011c;
              }
              uVar25 = (long)(int)uVar35 - 1;
              if (afStack_160[uVar25] < afStack_200[iVar15]) {
                uVar35 = uVar25 & 0xffffffff;
                goto code_r0x02240100;
              }
            }
            else {
              lVar19 = 0;
              if (iVar15 < iVar36) goto code_r0x022400bc;
code_r0x0224011c:
              if (lVar19 == 0) goto code_r0x02240568;
            }
            if (*(char *)(pfStack_b40 + 6) != '\0') {
              *(ushort *)(lVar19 + 0x2a5) = *(ushort *)(lVar19 + 0x2a5) | 4;
code_r0x02240138:
              if (iVar33 < 7) {
                lVar32 = (long)iVar33;
                pfVar22 = (float *)(param_3 + uVar37 * 0x550 + lVar32 * 0x20 + 0x300);
                if (*(char *)(pfStack_b40 + 6) == '\0') {
                  fVar51 = *(float *)(lVar19 + 0x290);
                  lVar38 = param_3 + uVar37 * 0x550 + lVar32 * 0x20;
                  *pfVar22 = fVar51;
                  fVar42 = *(float *)(lVar19 + 0x294);
                  *(float *)(lVar38 + 0x304) = fVar42;
                  fVar43 = *(float *)(lVar19 + 0x298);
                  *(float *)(lVar38 + 0x308) = fVar43;
                  *(undefined4 *)(lVar38 + 0x30c) = *(undefined4 *)(lVar19 + 0x29c);
                  pfVar28 = (float *)(lVar19 + 0x23c);
                }
                else {
                  fVar51 = *pfStack_b40;
                  lVar38 = param_3 + uVar37 * 0x550 + lVar32 * 0x20;
                  *pfVar22 = fVar51;
                  fVar42 = pfStack_b40[1];
                  *(float *)(lVar38 + 0x304) = fVar42;
                  fVar43 = pfStack_b40[2];
                  *(float *)(lVar38 + 0x308) = fVar43;
                  *(float *)(lVar38 + 0x30c) = pfStack_b40[3];
                  pfVar28 = pfStack_b40 + 4;
                }
                fVar55 = *pfVar28;
                fVar56 = *(float *)(lVar19 + 0x2fc);
                fVar43 = fVar51 * fVar51 + fVar42 * fVar42 + fVar43 * fVar43;
                fVar42 = SQRT(fVar43);
                if (NAN(fVar42)) {
                  fVar42 = (float)sqrtf(fVar43);
                }
                iVar33 = iVar33 + 1;
                fVar55 = fVar55 * fVar56;
                if (fVar7 <= fVar42) {
                  fVar42 = 1.0 / fVar42;
                  *pfVar22 = fVar42 * *pfVar22;
                  *(float *)(lVar38 + 0x304) = fVar42 * *(float *)(lVar38 + 0x304);
                  *(float *)(lVar38 + 0x308) = fVar42 * *(float *)(lVar38 + 0x308);
                }
                if (iVar13 != 2) {
                  fVar55 = fVar55 * fVar9;
                }
                auVar48._0_8_ =
                     CONCAT44(fVar55 * (float)((ulong)*(undefined8 *)(lVar19 + 0x230) >> 0x20),
                              fVar55 * (float)*(undefined8 *)(lVar19 + 0x230));
                auVar48._8_4_ = fVar55 * (float)*(undefined8 *)(lVar19 + 0x238);
                lVar32 = param_3 + uVar37 * 0x550 + lVar32 * 0x20;
                auVar48._12_4_ = 0x3f800000;
                *(long *)(lVar32 + 0x318) = auVar48._8_8_;
                *(undefined8 *)(lVar32 + 0x310) = auVar48._0_8_;
                *(undefined4 *)(lVar32 + 0x31c) = 0;
                if (bVar11) {
                  pfVar22 = (float *)(lVar32 + 0x31c);
code_r0x02240070:
                  iVar16 = Aska::AofObject::CheckLightMaskMixerLight(Aska::Light*) const(param_2,lVar19);
                  *pfVar22 = (float)iVar16 + 1.0;
                }
              }
              else {
                uVar14 = uVar14 & 0xfffffffe;
                if (uVar14 == 0) goto code_r0x02240568;
              }
              goto code_r0x02240090;
            }
            *(ushort *)(lVar19 + 0x2a5) = *(ushort *)(lVar19 + 0x2a5) | 4;
            cVar5 = *(char *)(lVar19 + 0x2a1);
            if (cVar5 == '\0') goto code_r0x02240138;
            if (cVar5 == '\x01') {
              if (iVar17 <= iVar29) goto joined_r0x02240564;
              lVar32 = param_3 + uVar37 * 0x550 + (long)iVar29 * 0x40;
              *(undefined4 *)(lVar32 + 0x3e0) = *(undefined4 *)(lVar19 + 0x200);
              iVar29 = iVar29 + 1;
              *(undefined4 *)(lVar32 + 0x3e4) = *(undefined4 *)(lVar19 + 0x204);
              *(undefined4 *)(lVar32 + 1000) = *(undefined4 *)(lVar19 + 0x208);
              *(undefined4 *)(lVar32 + 0x3ec) = *(undefined4 *)(lVar19 + 0x20c);
              *(undefined4 *)(lVar32 + 0x3f0) = *(undefined4 *)(lVar19 + 0x220);
              *(undefined4 *)(lVar32 + 0x3f4) = *(undefined4 *)(lVar19 + 0x224);
              *(undefined4 *)(lVar32 + 0x3f8) = *(undefined4 *)(lVar19 + 0x228);
              *(undefined4 *)(lVar32 + 0x3fc) = *(undefined4 *)(lVar19 + 0x22c);
              fVar42 = *(float *)(lVar19 + 0x23c) * *(float *)(lVar19 + 0x2fc);
              if (iVar13 != 2) {
                fVar42 = fVar42 * fVar9;
              }
              auVar49._0_8_ =
                   CONCAT44((float)((ulong)*(undefined8 *)(lVar19 + 0x230) >> 0x20) * fVar42,
                            (float)*(undefined8 *)(lVar19 + 0x230) * fVar42);
              auVar49._8_4_ = (float)*(undefined8 *)(lVar19 + 0x238) * fVar42;
              *(undefined4 *)(lVar32 + 0x41c) = 0xbf800000;
              auVar49._12_4_ = 0x3f800000;
              *(undefined4 *)(lVar32 + 0x3ec) = 0x3f800000;
              *(undefined4 *)(lVar32 + 0x418) = 0;
              *(undefined8 *)(lVar32 + 0x410) = 0;
              *(long *)(lVar32 + 0x408) = auVar49._8_8_;
              *(undefined8 *)(lVar32 + 0x400) = auVar49._0_8_;
              *(undefined4 *)(lVar32 + 0x40c) = 0;
              if (bVar11) {
                pfVar22 = (float *)(lVar32 + 0x40c);
                goto code_r0x02240070;
              }
              goto code_r0x02240090;
            }
          } while (cVar5 != '\x02');
          if (iVar29 < iVar17) {
            lVar38 = (long)iVar29;
            lVar32 = param_3 + uVar37 * 0x550 + lVar38 * 0x40;
            *(undefined4 *)(lVar32 + 0x3e0) = *(undefined4 *)(lVar19 + 0x200);
            *(undefined4 *)(lVar32 + 0x3e4) = *(undefined4 *)(lVar19 + 0x204);
            *(undefined4 *)(lVar32 + 1000) = *(undefined4 *)(lVar19 + 0x208);
            *(undefined4 *)(lVar32 + 0x3ec) = *(undefined4 *)(lVar19 + 0x20c);
            fVar42 = *(float *)(lVar19 + 0x290);
            *(float *)(lVar32 + 0x410) = fVar42;
            fVar43 = *(float *)(lVar19 + 0x294);
            *(float *)(lVar32 + 0x414) = fVar43;
            fVar51 = *(float *)(lVar19 + 0x298);
            *(float *)(lVar32 + 0x418) = fVar51;
            fVar43 = fVar42 * fVar42 + fVar43 * fVar43 + fVar51 * fVar51;
            fVar42 = SQRT(fVar43);
            *(undefined4 *)(lVar32 + 0x41c) = *(undefined4 *)(lVar19 + 0x29c);
            if (NAN(fVar42)) {
              fVar42 = (float)sqrtf(fVar43);
            }
            iVar29 = iVar29 + 1;
            if (fVar7 <= fVar42) {
              fVar42 = 1.0 / fVar42;
              *(float *)(lVar32 + 0x410) = fVar42 * *(float *)(lVar32 + 0x410);
              *(float *)(lVar32 + 0x414) = fVar42 * *(float *)(lVar32 + 0x414);
              *(float *)(lVar32 + 0x418) = fVar42 * *(float *)(lVar32 + 0x418);
            }
            fVar42 = *(float *)(lVar19 + 0x23c) * *(float *)(lVar19 + 0x2fc);
            if (iVar13 != 2) {
              fVar42 = fVar42 * fVar9;
            }
            lVar38 = param_3 + uVar37 * 0x550 + lVar38 * 0x40;
            auVar47._0_8_ =
                 CONCAT44((float)((ulong)*(undefined8 *)(lVar19 + 0x230) >> 0x20) * fVar42,
                          (float)*(undefined8 *)(lVar19 + 0x230) * fVar42);
            auVar47._8_4_ = (float)*(undefined8 *)(lVar19 + 0x238) * fVar42;
            auVar47._12_4_ = 0x3f800000;
            *(long *)(lVar38 + 0x408) = auVar47._8_8_;
            *(undefined8 *)(lVar38 + 0x400) = auVar47._0_8_;
            *(undefined4 *)(lVar38 + 0x3f0) = *(undefined4 *)(lVar19 + 0x220);
            *(undefined4 *)(lVar38 + 0x3f4) = *(undefined4 *)(lVar19 + 0x224);
            *(undefined4 *)(lVar38 + 0x3f8) = *(undefined4 *)(lVar19 + 0x228);
            *(undefined4 *)(lVar38 + 0x3fc) = *(undefined4 *)(lVar19 + 0x22c);
            *(undefined4 *)(lVar32 + 0x3ec) = *(undefined4 *)(lVar19 + 0x2dc);
            *(undefined4 *)(lVar32 + 0x41c) = *(undefined4 *)(lVar19 + 0x2e0);
            *(undefined4 *)(lVar38 + 0x40c) = 0;
            if (bVar11) {
              iVar16 = Aska::AofObject::CheckLightMaskMixerLight(Aska::Light*) const(param_2,lVar19);
              *(float *)(lVar38 + 0x40c) = (float)iVar16 + 1.0;
            }
            goto code_r0x02240090;
          }
joined_r0x02240564:
          uVar14 = uVar14 & 0xfffffffd;
        } while (uVar14 != 0);
code_r0x02240568:
        lVar19 = param_3 + uVar37 * 0x550;
        *(float *)(lVar19 + 0x2f0) = (float)iVar33;
        *(float *)(lVar19 + 0x2f4) = (float)iVar29;
        *(char *)(lVar19 + 1) = (char)iVar33;
      }
      else {
        iVar29 = 0;
        lVar19 = param_3 + uVar37 * 0x550;
        *(undefined8 *)(lVar19 + 0x2f0) = 0;
        *(undefined1 *)(lVar19 + 1) = 0;
      }
      *(char *)(param_3 + uVar37 * 0x550 + 2) = (char)iVar29;
      if (bVar12) {
        lVar19 = param_3 + uVar37 * 0x550;
        uVar52 = *(undefined8 *)(lVar39 + 0x140);
        *(undefined8 *)(lVar19 + 0x4d8) = *(undefined8 *)(lVar39 + 0x148);
        *(undefined8 *)(lVar19 + 0x4d0) = uVar52;
        uVar52 = *(undefined8 *)(lVar39 + 0x130);
        *(undefined8 *)(lVar19 + 0x4c8) = *(undefined8 *)(lVar39 + 0x138);
        *(undefined8 *)(lVar19 + 0x4c0) = uVar52;
        uVar52 = *(undefined8 *)(lVar39 + 0x120);
        *(undefined8 *)(lVar19 + 0x4b8) = *(undefined8 *)(lVar39 + 0x128);
        *(undefined8 *)(lVar19 + 0x4b0) = uVar52;
        auVar46 = *(undefined1 (*) [16])(lVar39 + 0x110);
        *(long *)(lVar19 + 0x4a8) = auVar46._8_8_;
        *(long *)(lVar19 + 0x4a0) = auVar46._0_8_;
      }
    }
    else {
      cVar5 = *(char *)(param_4 + uVar37);
      if (cVar5 != '\0') {
        if (cVar5 != '\x02') {
          iVar17 = 4;
        }
        else {
          iVar17 = 3;
        }
        bVar12 = cVar5 == '\x02';
        if (iVar13 == 0) {
          uVar14 = (uint)uVar37;
          if ((long)(int)uVar41 <= (long)uVar37) {
            uVar14 = uVar41;
          }
          uVar35 = (ulong)uVar14;
        }
        goto code_r0x0223f974;
      }
    }
    bVar12 = uVar37 == uStack_bd8;
    uVar37 = uVar37 + 1;
    lStack_bb8 = lStack_bb8 + 0x550;
    if (bVar12) {
      return 1;
    }
  } while( true );
}

// ==== Aska::LightManager::CalcHemisphereLightCoeffs(Aska::LightManager::SHAmbConst*, Aska::Light const*, Aska::Vector*)
// vaddr 0x2140640 | ghidra 0x2240640 | size 1136 | symbol _ZN4Aska12LightManager25CalcHemisphereLightCoeffsEPNS0_10SHAmbConstEPKNS_5LightEPNS_6VectorE | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska12LightManager25CalcHemisphereLightCoeffsEPNS0_10SHAmbConstEPKNS_5LightEPNS_6VectorE
               (undefined8 param_1,float *param_2,long *param_3,float *param_4)

{
  char cVar1;
  undefined8 *puVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar12;
  undefined8 uVar11;
  float fVar13;
  ulong uVar14;
  undefined8 uVar15;
  ulong uVar16;
  undefined8 uVar17;
  float fVar18;
  ulong uVar19;
  float fVar20;
  float fVar21;
  undefined8 uStack_e0;
  ulong uStack_d8;
  undefined8 uStack_d0;
  ulong uStack_c8;
  undefined8 uStack_c0;
  ulong uStack_b8;
  undefined8 uStack_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  long lStack_98;
  undefined8 uStack_90;
  long lStack_88;
  undefined8 uStack_80;
  long lStack_78;
  undefined8 uStack_70;
  undefined8 uStack_68;
  
  fVar3 = *(float *)((long)param_3 + 0x2fc);
  cVar1 = *(char *)((long)param_3 + 0x2a1);
  fVar21 = fVar3 * *param_4;
  fVar20 = fVar3 * param_4[1];
  fVar3 = fVar3 * param_4[2];
  *(byte *)(param_2 + 0x20) =
       (byte)((ushort)*(undefined2 *)((long)param_3 + 0x2a5) >> 0xc) & 1 | *(byte *)(param_2 + 0x20)
  ;
  if (cVar1 == '\x06') {
    fVar4 = *(float *)(param_3 + 0x52);
    fVar5 = *(float *)((long)param_3 + 0x294);
    fVar6 = *(float *)(param_3 + 0x53);
    fVar21 = fVar21 * 0.5 * *(float *)(param_3 + 0x46);
    fVar20 = fVar20 * 0.5 * *(float *)((long)param_3 + 0x234);
    fVar3 = fVar3 * 0.5 * *(float *)(param_3 + 0x47);
    param_2[0xc] = fVar21 + param_2[0xc];
    param_2[0xd] = fVar20 + param_2[0xd];
    param_2[0xe] = fVar3 + param_2[0xe];
    *param_2 = *param_2 - fVar21 * fVar4;
    param_2[1] = param_2[1] - fVar20 * fVar4;
    param_2[2] = param_2[2] - fVar3 * fVar4;
    param_2[4] = param_2[4] - fVar21 * fVar5;
    param_2[5] = param_2[5] - fVar20 * fVar5;
    param_2[6] = param_2[6] - fVar3 * fVar5;
    param_2[8] = param_2[8] - fVar21 * fVar6;
    param_2[9] = param_2[9] - fVar20 * fVar6;
    param_2[10] = param_2[10] - fVar3 * fVar6;
  }
  else if (cVar1 == '\x05') {
    lStack_98 = param_3[0x4b];
    uStack_a0 = param_3[0x4a];
    lStack_88 = param_3[0x4d];
    uStack_90 = param_3[0x4c];
    lStack_78 = param_3[0x4f];
    uStack_80 = param_3[0x4e];
    uStack_68 = _UNK_027dbb38;
    uStack_70 = _UNK_027dbb30;
    puVar2 = (undefined8 *)(**(code **)(*param_3 + 0x98))(param_3);
    uVar19 = puVar2[1];
    uVar17 = *puVar2;
    uVar16 = puVar2[3];
    uVar15 = puVar2[2];
    uVar14 = puVar2[5];
    uVar11 = puVar2[4];
    uStack_a8 = puVar2[7];
    uStack_b0 = puVar2[6];
    fVar7 = (float)uVar17;
    fVar6 = (float)uVar15;
    fVar5 = (float)uVar11;
    fVar4 = SQRT(fVar7 * fVar7 + fVar6 * fVar6 + fVar5 * fVar5);
    uStack_d8 = uVar19 & 0xffffffff;
    uStack_c8 = uVar16 & 0xffffffff;
    uStack_b8 = uVar14 & 0xffffffff;
    uStack_e0 = uVar17;
    uStack_d0 = uVar15;
    uStack_c0 = uVar11;
    if (NAN(fVar4)) {
      fVar4 = (float)sqrtf();
    }
    fVar10 = (float)uVar14;
    fVar12 = (float)uVar16;
    fVar18 = (float)uVar19;
    fVar13 = (float)((ulong)uVar17 >> 0x20);
    fVar8 = (float)((ulong)uVar15 >> 0x20);
    fVar9 = (float)((ulong)uVar11 >> 0x20);
    fVar8 = SQRT(fVar13 * fVar13 + fVar8 * fVar8 + fVar9 * fVar9);
    if (NAN(fVar8)) {
      fVar8 = (float)sqrtf();
    }
    fVar12 = fVar18 * fVar18 + fVar12 * fVar12 + fVar10 * fVar10;
    fVar10 = SQRT(fVar12);
    fVar4 = 1.0 / fVar4;
    fVar8 = 1.0 / fVar8;
    if (NAN(fVar10)) {
      fVar10 = (float)sqrtf(fVar12);
    }
    fVar10 = 1.0 / fVar10;
    uStack_e0 = CONCAT44(fVar8 * uStack_e0._4_4_,fVar4 * fVar7);
    uStack_d0 = CONCAT44(fVar8 * uStack_d0._4_4_,fVar4 * fVar6);
    uStack_c0 = CONCAT44(fVar8 * fVar9,fVar4 * fVar5);
    uStack_d8 = CONCAT44(uStack_d8._4_4_,fVar10 * (float)uStack_d8);
    uStack_c8 = CONCAT44(uStack_c8._4_4_,fVar10 * (float)uStack_c8);
    uStack_b8 = CONCAT44(uStack_b8._4_4_,fVar10 * (float)uStack_b8);
    Aska::Matrix::MulFromLeft(Aska::Matrix const*)(&uStack_a0,&uStack_e0);
    fVar4 = *(float *)(param_3 + 0x48);
    fVar5 = *(float *)((long)param_3 + 0x244);
    fVar6 = *(float *)(param_3 + 0x49);
    *param_2 = *param_2 + fVar21 * (float)uStack_a0;
    param_2[1] = param_2[1] + fVar20 * uStack_a0._4_4_;
    param_2[2] = param_2[2] + fVar3 * (float)lStack_98;
    param_2[4] = param_2[4] + fVar21 * (float)uStack_90;
    param_2[5] = param_2[5] + fVar20 * uStack_90._4_4_;
    param_2[6] = param_2[6] + fVar3 * (float)lStack_88;
    param_2[8] = param_2[8] + fVar21 * (float)uStack_80;
    param_2[9] = param_2[9] + fVar20 * uStack_80._4_4_;
    param_2[10] = param_2[10] + fVar3 * (float)lStack_78;
    param_2[0xc] = param_2[0xc] + fVar21 * fVar4;
    param_2[0xd] = param_2[0xd] + fVar20 * fVar5;
    param_2[0xe] = param_2[0xe] + fVar3 * fVar6;
  }
  else if (cVar1 == '\x04') {
    fVar8 = *(float *)(param_3 + 0x52);
    fVar4 = *(float *)((long)param_3 + 0x294);
    fVar9 = *(float *)(param_3 + 0x53);
    fVar5 = fVar21 * 0.5 * (float)param_3[0x46];
    fVar6 = fVar20 * 0.5 * (float)((ulong)param_3[0x46] >> 0x20);
    fVar7 = fVar3 * 0.5 * (float)param_3[0x47];
    fVar10 = fVar21 * 0.5 * (float)param_3[0x50];
    fVar12 = fVar20 * 0.5 * (float)((ulong)param_3[0x50] >> 0x20);
    fVar13 = fVar3 * 0.5 * (float)param_3[0x51];
    fVar3 = fVar5 - fVar10;
    fVar20 = fVar6 - fVar12;
    fVar21 = fVar7 - fVar13;
    param_2[0xc] = param_2[0xc] + fVar5 + fVar10;
    param_2[0xd] = param_2[0xd] + fVar6 + fVar12;
    param_2[0xe] = fVar7 + fVar13 + param_2[0xe];
    *param_2 = *param_2 - fVar8 * fVar3;
    param_2[1] = param_2[1] - fVar8 * fVar20;
    param_2[2] = param_2[2] - fVar8 * fVar21;
    param_2[8] = param_2[8] - fVar9 * fVar3;
    param_2[9] = param_2[9] - fVar9 * fVar20;
    param_2[10] = param_2[10] - fVar9 * fVar21;
    param_2[4] = param_2[4] - fVar4 * fVar3;
    param_2[5] = param_2[5] - fVar4 * fVar20;
    param_2[6] = param_2[6] - fVar4 * fVar21;
  }
  return;
}

// ==== Aska::LightManager::CalcBounceLightCoeffs(Aska::LightManager::SHAmbConst*, Aska::RenderableObject*, Aska::Light**, int, Aska::Light**, int)
// vaddr 0x2140ab0 | ghidra 0x2240ab0 | size 1084 | symbol _ZN4Aska12LightManager21CalcBounceLightCoeffsEPNS0_10SHAmbConstEPNS_16RenderableObjectEPPNS_5LightEiS7_i | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska12LightManager21CalcBounceLightCoeffsEPNS0_10SHAmbConstEPNS_16RenderableObjectEPPNS_5LightEiS7_i
               (undefined8 param_1,float *param_2,long *param_3,long param_4,uint param_5,
               long *param_6,uint param_7)

{
  undefined8 uVar1;
  undefined8 uVar2;
  ulong uVar3;
  long *plVar4;
  long lVar5;
  long lVar6;
  ushort uVar7;
  ulong uVar8;
  ulong uVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fStack_b0;
  float fStack_ac;
  float fStack_a8;
  undefined4 uStack_a4;
  undefined8 uStack_a0;
  undefined8 uStack_98;
  
  uVar2 = _UNK_027dbb38;
  uVar1 = _UNK_027dbb30;
  if ((int)param_5 < 1) {
    uVar7 = 0;
  }
  else {
    uVar8 = 0;
    uVar7 = 0;
    do {
      lVar5 = *(long *)(param_4 + uVar8 * 8);
      uStack_98 = uVar2;
      uStack_a0 = uVar1;
      uVar9 = *(ulong *)(lVar5 + 0x2a8);
      uVar7 = uVar7 | *(ushort *)(lVar5 + 0x2a5) >> 0xc & 1;
      if (*(char *)(lVar5 + 0x2a1) == '\a') {
        if ((*(byte *)(param_3 + 0x25) >> 4 & 1) == 0) {
          (**(code **)(*param_3 + 600))(param_3,1);
        }
        uStack_a4 = *(undefined4 *)((long)param_3 + 0x2dc);
        fStack_b0 = *(float *)(param_3 + 0x5a) - *(float *)(lVar5 + 0x200);
        fStack_ac = *(float *)((long)param_3 + 0x2d4) - *(float *)(lVar5 + 0x204);
        fStack_a8 = *(float *)(param_3 + 0x5b) - *(float *)(lVar5 + 0x208);
        fVar13 = SQRT(fStack_a8 * fStack_a8 + fStack_b0 * fStack_b0 + fStack_ac * fStack_ac);
        if (NAN(fVar13)) {
          fVar13 = (float)sqrtf();
        }
        fVar10 = 1.0 / fVar13;
        fStack_b0 = fStack_b0 * fVar10;
        fStack_ac = fVar10 * fStack_ac;
        fStack_a8 = fVar10 * fStack_a8;
        uVar3 = (ulong)param_7;
        plVar4 = param_6;
        if (0 < (int)param_7) {
          do {
            lVar6 = *plVar4;
            if ((*(ulong *)(lVar6 + 0x2a8) & uVar9) != 0) {
              fVar10 = (float)Aska::Light::CalcBounceIntensity(Aska::Light*, Aska::Vector*) const(lVar6,lVar5,&fStack_b0);
              fVar11 = *(float *)(lVar6 + 0x2fc);
              uStack_a0 = CONCAT44(fVar10 * *(float *)(lVar6 + 0x234) * fVar11 + uStack_a0._4_4_,
                                   fVar10 * *(float *)(lVar6 + 0x230) * fVar11 + (float)uStack_a0);
              uStack_98 = CONCAT44(uStack_98._4_4_,
                                   fVar10 * *(float *)(lVar6 + 0x238) * fVar11 + (float)uStack_98);
            }
            uVar3 = uVar3 - 1;
            plVar4 = plVar4 + 1;
          } while (uVar3 != 0);
        }
        fVar10 = *(float *)(lVar5 + 0x234);
        fVar11 = *(float *)(lVar5 + 0x238);
        fVar13 = 1.0 / (*(float *)(lVar5 + 0x220) + fVar13 * *(float *)(lVar5 + 0x224) +
                       fVar13 * fVar13 * *(float *)(lVar5 + 0x228)) - *(float *)(lVar5 + 0x22c);
        if (fVar13 < 0.0) {
          fVar13 = 0.0;
        }
        fVar14 = *(float *)(lVar5 + 0x23c) * *(float *)(lVar5 + 0x2fc);
        fVar12 = 1.0;
        if (fVar13 + -1.0 < 0.0) {
          fVar12 = fVar13;
        }
        fVar13 = (float)uStack_a0 * *(float *)(lVar5 + 0x230) * fVar14 * 0.5 * fVar12;
        param_2[0xc] = fVar13 + param_2[0xc];
        param_2[4] = param_2[4] - fVar13 * fStack_ac;
        *param_2 = *param_2 - fVar13 * fStack_b0;
        param_2[8] = param_2[8] - fVar13 * fStack_a8;
        fVar13 = (float)((ulong)uStack_a0 >> 0x20) * fVar14 * fVar10 * 0.5 * fVar12;
        param_2[0xd] = fVar13 + param_2[0xd];
        param_2[1] = param_2[1] - fVar13 * fStack_b0;
        param_2[5] = param_2[5] - fVar13 * fStack_ac;
        param_2[9] = param_2[9] - fVar13 * fStack_a8;
        uStack_98._0_4_ = fVar14 * fVar11 * 0.5 * fVar12 * (float)uStack_98;
        param_2[0xe] = (float)uStack_98 + param_2[0xe];
        param_2[2] = param_2[2] - (float)uStack_98 * fStack_b0;
        param_2[6] = param_2[6] - (float)uStack_98 * fStack_ac;
        param_2[10] = param_2[10] - (float)uStack_98 * fStack_a8;
      }
      else {
        plVar4 = param_6;
        uVar3 = (ulong)param_7;
        if (0 < (int)param_7) {
          do {
            lVar6 = *plVar4;
            if ((*(ulong *)(lVar6 + 0x2a8) & uVar9) != 0) {
              fVar13 = (float)Aska::Light::CalcBounceIntensity(Aska::Light*, Aska::Vector*) const(lVar6,lVar5,0);
              fVar10 = *(float *)(lVar6 + 0x2fc);
              uStack_a0 = CONCAT44(fVar13 * *(float *)(lVar6 + 0x234) * fVar10 + uStack_a0._4_4_,
                                   fVar13 * *(float *)(lVar6 + 0x230) * fVar10 + (float)uStack_a0);
              uStack_98 = CONCAT44(uStack_98._4_4_,
                                   fVar13 * *(float *)(lVar6 + 0x238) * fVar10 + (float)uStack_98);
            }
            uVar3 = uVar3 - 1;
            plVar4 = plVar4 + 1;
          } while (uVar3 != 0);
        }
        fVar13 = (float)Aska::Light::CalcHemisphereIntensity(Aska::RenderableObject*)(lVar5,param_3);
        uStack_a0 = CONCAT44(fVar13 * uStack_a0._4_4_,fVar13 * (float)uStack_a0);
        uStack_98 = CONCAT44(uStack_98._4_4_,fVar13 * (float)uStack_98);
        Aska::LightManager::CalcHemisphereLightCoeffs(Aska::LightManager::SHAmbConst*, Aska::Light const*, Aska::Vector*)(param_1,param_2,lVar5,&uStack_a0);
      }
      uVar8 = uVar8 + 1;
    } while (uVar8 != param_5);
  }
  *(bool *)(param_2 + 0x20) = uVar7 != 0 || *(char *)(param_2 + 0x20) != '\0';
  return;
}

// ==== Aska::LightManager::MakeLightContextPost(Aska::AofObject*, Aska::LightManager::LightContext*, unsigned char*)
// vaddr 0x2141030 | ghidra 0x2241030 | size 672 | symbol _ZN4Aska12LightManager20MakeLightContextPostEPNS_9AofObjectEPNS0_12LightContextEPh | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska12LightManager20MakeLightContextPostEPNS_9AofObjectEPNS0_12LightContextEPh
               (undefined8 param_1,long param_2,long param_3,long param_4)

{
  long lVar1;
  undefined1 *puVar2;
  float fVar3;
  float fVar4;
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
  
  *(undefined1 *)(param_3 + 4) = 0;
  ProcIBLforSHAmbi(Aska::RenderableObject*, Aska::LightManager::SHAmbConst*, bool)(param_2,param_3 + 0x10,*(ushort *)(param_2 + 0x37c) >> 2 & 1);
  if ('\x02' < (char)*PTR__ZN4Aska13ObjectManager19m_cShaderGradeLevelE_02cb9f98) {
    fVar4 = 1.0 / *(float *)(param_3 + 0x40);
    if (*(float *)(param_3 + 0x40) <= 0.0) {
      fVar4 = 0.0;
    }
    fVar5 = 1.0 / *(float *)(param_3 + 0x44);
    if (*(float *)(param_3 + 0x44) <= 0.0) {
      fVar5 = 0.0;
    }
    fVar6 = 1.0 / *(float *)(param_3 + 0x48);
    fVar12 = SQRT(*(float *)(param_3 + 0x10) * *(float *)(param_3 + 0x10) +
                  *(float *)(param_3 + 0x20) * *(float *)(param_3 + 0x20) +
                  *(float *)(param_3 + 0x30) * *(float *)(param_3 + 0x30));
    if (*(float *)(param_3 + 0x48) <= 0.0) {
      fVar6 = 0.0;
    }
    if (NAN(fVar12)) {
      fVar12 = (float)sqrtf();
    }
    fVar13 = SQRT(*(float *)(param_3 + 0x14) * *(float *)(param_3 + 0x14) +
                  *(float *)(param_3 + 0x24) * *(float *)(param_3 + 0x24) +
                  *(float *)(param_3 + 0x34) * *(float *)(param_3 + 0x34));
    if (NAN(fVar13)) {
      fVar13 = (float)sqrtf();
    }
    fVar7 = *(float *)(param_3 + 0x18) * *(float *)(param_3 + 0x18) +
            *(float *)(param_3 + 0x28) * *(float *)(param_3 + 0x28) +
            *(float *)(param_3 + 0x38) * *(float *)(param_3 + 0x38);
    fVar3 = SQRT(fVar7);
    if (NAN(fVar3)) {
      fVar3 = (float)sqrtf(fVar7);
    }
    fVar4 = fVar4 * fVar12;
    fVar5 = fVar5 * fVar13;
    fVar6 = fVar6 * fVar3;
    fVar10 = *(float *)(param_3 + 0x40);
    fVar11 = *(float *)(param_3 + 0x44);
    *(float *)(param_3 + 0x1c) = fVar4;
    fVar12 = 0.5 / fVar12;
    fVar13 = 0.5 / fVar13;
    fVar3 = 0.5 / fVar3;
    *(float *)(param_3 + 0x2c) = fVar5;
    fVar7 = (1.0 - fVar4) / (fVar4 + 1.0);
    *(float *)(param_3 + 0x3c) = fVar6;
    fVar8 = (1.0 - fVar5) / (fVar5 + 1.0);
    fVar9 = fVar4 + fVar4 + 1.0;
    fVar14 = fVar5 + fVar5 + 1.0;
    fVar5 = (1.0 - fVar6) / (fVar6 + 1.0);
    *(float *)(param_3 + 0x50) = fVar9;
    *(float *)(param_3 + 0x54) = fVar14;
    *(float *)(param_3 + 0x60) = fVar7 * fVar10;
    *(float *)(param_3 + 100) = fVar8 * fVar11;
    fVar4 = *(float *)(param_3 + 0x48);
    fVar6 = fVar6 + fVar6 + 1.0;
    if (fVar10 <= 0.0) {
      fVar12 = 0.0;
    }
    *(float *)(param_3 + 0x58) = fVar6;
    *(float *)(param_3 + 0x5c) = fVar12;
    if (fVar11 <= 0.0) {
      fVar13 = 0.0;
    }
    if (fVar4 <= 0.0) {
      fVar3 = 0.0;
    }
    *(float *)(param_3 + 0x68) = fVar5 * fVar4;
    *(float *)(param_3 + 0x6c) = fVar13;
    *(float *)(param_3 + 0x78) = (1.0 - fVar5) * (fVar6 + 1.0) * fVar4;
    *(float *)(param_3 + 0x7c) = fVar3;
    *(float *)(param_3 + 0x70) = (1.0 - fVar7) * (fVar9 + 1.0) * fVar10;
    *(float *)(param_3 + 0x74) = (1.0 - fVar8) * (fVar14 + 1.0) * fVar11;
  }
  if (param_4 != 0) {
    if (*(char *)(param_4 + 4) == '\0') {
      if (*(char *)(param_4 + 3) == '\0') {
        if (*(char *)(param_4 + 2) == '\0') {
          if (*(char *)(param_4 + 1) == '\0') {
            return;
          }
          lVar1 = 2;
        }
        else {
          lVar1 = 3;
        }
      }
      else {
        lVar1 = 4;
      }
    }
    else {
      lVar1 = 5;
    }
    puVar2 = (undefined1 *)(param_3 + 0x554);
    lVar1 = lVar1 + -1;
    do {
      memcpy(puVar2 + 0xc,param_3 + 0x10,0x90);
      *puVar2 = *(undefined1 *)(param_3 + 4);
      memcpy(puVar2 + 0x24c,param_3 + 0x250,(ulong)*(byte *)(param_3 + 4) * 0x50);
      lVar1 = lVar1 + -1;
      puVar2 = puVar2 + 0x550;
    } while (lVar1 != 0);
  }
  return;
}

// ==== ProcIBLforSHAmbi(Aska::RenderableObject*, Aska::LightManager::SHAmbConst*, bool)
// vaddr 0x21412d0 | ghidra 0x22412d0 | size 1172 | symbol _Z16ProcIBLforSHAmbiPN4Aska16RenderableObjectEPNS_12LightManager10SHAmbConstEb | lib libSOA-3.7.0.so | 2026-10-04
void _Z16ProcIBLforSHAmbiPN4Aska16RenderableObjectEPNS_12LightManager10SHAmbConstEb
               (long param_1,float *param_2,uint param_3)

{
  ushort *puVar1;
  ushort uVar2;
  float *pfVar3;
  long lVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  
  lVar4 = *(long *)(param_1 + 0x230);
  if (lVar4 != 0) {
    puVar1 = (ushort *)(lVar4 + 0x2a5);
    *(byte *)(param_2 + 0x20) = (byte)(*puVar1 >> 0xc) & 1 | *(byte *)(param_2 + 0x20);
    fVar5 = *(float *)(lVar4 + 0x23c) * *(float *)(lVar4 + 0x2fc) * *(float *)(param_1 + 0x240);
    fVar7 = *(float *)(lVar4 + 0x230) * fVar5;
    fVar6 = *(float *)(lVar4 + 0x234) * fVar5;
    fVar5 = *(float *)(lVar4 + 0x238) * fVar5;
    pfVar3 = (float *)Aska::DiffuseCubeMap::DiffuseSHCoef()(*(undefined8 *)(lVar4 + 0x418));
    if (((param_3 & 1) == 0) || (uVar2 = *puVar1, (uVar2 >> 3 & 1) != 0)) {
      *param_2 = *param_2 + fVar7 * pfVar3[4];
      param_2[1] = param_2[1] + fVar6 * pfVar3[5];
      param_2[2] = param_2[2] + fVar5 * pfVar3[6];
      param_2[4] = param_2[4] + fVar7 * pfVar3[8];
      param_2[5] = param_2[5] + fVar6 * pfVar3[9];
      param_2[6] = param_2[6] + fVar5 * pfVar3[10];
      param_2[8] = param_2[8] + fVar7 * pfVar3[0xc];
      param_2[9] = param_2[9] + fVar6 * pfVar3[0xd];
      param_2[10] = param_2[10] + fVar5 * pfVar3[0xe];
      param_2[0xc] = param_2[0xc] + fVar7 * *pfVar3;
      param_2[0xd] = param_2[0xd] + fVar6 * pfVar3[1];
      param_2[0xe] = param_2[0xe] + fVar5 * pfVar3[2];
      uVar2 = *puVar1;
    }
    if ((uVar2 >> 3 & 1) != 0) {
      param_2[0x10] = param_2[0x10] + fVar7 * pfVar3[4];
      param_2[0x11] = param_2[0x11] + fVar6 * pfVar3[5];
      param_2[0x12] = param_2[0x12] + fVar5 * pfVar3[6];
      param_2[0x14] = param_2[0x14] + fVar7 * pfVar3[8];
      param_2[0x15] = param_2[0x15] + fVar6 * pfVar3[9];
      param_2[0x16] = param_2[0x16] + fVar5 * pfVar3[10];
      param_2[0x18] = param_2[0x18] + fVar7 * pfVar3[0xc];
      param_2[0x19] = param_2[0x19] + fVar6 * pfVar3[0xd];
      param_2[0x1a] = param_2[0x1a] + fVar5 * pfVar3[0xe];
      param_2[0x1c] = param_2[0x1c] + fVar7 * *pfVar3;
      param_2[0x1d] = param_2[0x1d] + fVar6 * pfVar3[1];
      param_2[0x1e] = param_2[0x1e] + fVar5 * pfVar3[2];
    }
  }
  lVar4 = *(long *)(param_1 + 0x238);
  if (lVar4 != 0) {
    *(byte *)(param_2 + 0x20) =
         (byte)(*(ushort *)(lVar4 + 0x2a5) >> 0xc) & 1 | *(byte *)(param_2 + 0x20);
    fVar5 = *(float *)(lVar4 + 0x23c) * *(float *)(lVar4 + 0x2fc) * *(float *)(param_1 + 0x244);
    fVar7 = *(float *)(lVar4 + 0x230) * fVar5;
    fVar6 = *(float *)(lVar4 + 0x234) * fVar5;
    fVar5 = *(float *)(lVar4 + 0x238) * fVar5;
    pfVar3 = (float *)Aska::DiffuseCubeMap::DiffuseSHCoef()(*(undefined8 *)(lVar4 + 0x418));
    *param_2 = *param_2 + fVar7 * pfVar3[4];
    param_2[1] = param_2[1] + fVar6 * pfVar3[5];
    param_2[2] = param_2[2] + fVar5 * pfVar3[6];
    param_2[4] = param_2[4] + fVar7 * pfVar3[8];
    param_2[5] = param_2[5] + fVar6 * pfVar3[9];
    param_2[6] = param_2[6] + fVar5 * pfVar3[10];
    param_2[8] = param_2[8] + fVar7 * pfVar3[0xc];
    param_2[9] = param_2[9] + fVar6 * pfVar3[0xd];
    param_2[10] = param_2[10] + fVar5 * pfVar3[0xe];
    param_2[0xc] = param_2[0xc] + fVar7 * *pfVar3;
    param_2[0xd] = param_2[0xd] + fVar6 * pfVar3[1];
    param_2[0xe] = param_2[0xe] + fVar5 * pfVar3[2];
    if ((*(ushort *)(lVar4 + 0x2a5) >> 3 & 1) != 0) {
      param_2[0x10] = param_2[0x10] + fVar7 * pfVar3[4];
      param_2[0x11] = param_2[0x11] + fVar6 * pfVar3[5];
      param_2[0x12] = param_2[0x12] + fVar5 * pfVar3[6];
      param_2[0x14] = param_2[0x14] + fVar7 * pfVar3[8];
      param_2[0x15] = param_2[0x15] + fVar6 * pfVar3[9];
      param_2[0x16] = param_2[0x16] + fVar5 * pfVar3[10];
      param_2[0x18] = param_2[0x18] + fVar7 * pfVar3[0xc];
      param_2[0x19] = param_2[0x19] + fVar6 * pfVar3[0xd];
      param_2[0x1a] = param_2[0x1a] + fVar5 * pfVar3[0xe];
      param_2[0x1c] = param_2[0x1c] + fVar7 * *pfVar3;
      param_2[0x1d] = param_2[0x1d] + fVar6 * pfVar3[1];
      param_2[0x1e] = param_2[0x1e] + fVar5 * pfVar3[2];
    }
  }
  return;
}

// ==== Aska::LightManager::MakeLightContext(Aska::RenderableObject*, Aska::LightManager::LightContextSimple*)
// vaddr 0x2141764 | ghidra 0x2241764 | size 1968 | symbol _ZN4Aska12LightManager16MakeLightContextEPNS_16RenderableObjectEPNS0_18LightContextSimpleE | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Type propagation algorithm not settling */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska12LightManager16MakeLightContextEPNS_16RenderableObjectEPNS0_18LightContextSimpleE
               (long param_1,long *param_2,long param_3)

{
  bool bVar1;
  undefined4 uVar2;
  uint uVar3;
  double dVar4;
  long lVar5;
  long lVar6;
  long lVar7;
  long lVar8;
  long lVar9;
  long lVar10;
  float fVar11;
  int iVar12;
  long *plVar13;
  long lVar14;
  uint uVar15;
  int iVar16;
  long lVar17;
  long lVar18;
  ulong uVar19;
  long lVar20;
  float fVar21;
  float fVar22;
  float fVar23;
  float fVar24;
  float fVar25;
  float fVar26;
  float fVar27;
  float fVar28;
  float fVar29;
  float fVar30;
  float fVar31;
  float fVar32;
  float fVar33;
  float fVar34;
  float fVar35;
  float fVar36;
  float fVar37;
  undefined8 uStack_1f0;
  undefined8 uStack_1e8;
  long alStack_1e0 [32];
  long alStack_e0 [8];
  
  memset(param_3,0,0x310);
  dVar4 = _UNK_029cc408;
  fVar30 = _UNK_029cc100;
  alStack_e0[5] = 0;
  alStack_e0[4] = 0;
  alStack_e0[7] = 0;
  alStack_e0[6] = 0;
  alStack_e0[1] = 0;
  alStack_e0[0] = 0;
  alStack_e0[3] = 0;
  alStack_e0[2] = 0;
  if (*(ushort *)(param_1 + 0x2ff8) == 0) {
    uVar15 = 0;
  }
  else {
    uVar19 = param_2[0x4c];
    uVar15 = 0;
    iVar16 = 0;
    fVar37 = 0.0;
    lVar20 = 0x1fe;
    fVar28 = 0.0;
    fVar25 = 0.0;
    fVar34 = 0.0;
    fVar35 = 0.0;
    fVar36 = 0.0;
    fVar24 = 0.0;
    fVar27 = 0.0;
    do {
      lVar18 = *(long *)(param_1 + lVar20 * 8);
      fVar23 = fVar27;
      if (((*(ulong *)(lVar18 + 0x2a8) & uVar19) != 0) &&
         ((*(uint3 *)(lVar18 + 0x2a5) & 0x12000) == 0)) {
        if ((*(byte *)(lVar18 + 0x2a1) == 7) ||
           ((uVar3 = *(byte *)(lVar18 + 0x2a1) - 4, (*(uint3 *)(lVar18 + 0x2a5) & 0x200) != 0 &&
            (uVar3 < 3)))) {
          if (iVar16 < 0x20) {
            alStack_1e0[iVar16] = lVar18;
            iVar16 = iVar16 + 1;
          }
        }
        else if (uVar3 < 3) {
          fVar27 = (float)Aska::Light::CalcHemisphereIntensity(Aska::RenderableObject*)(lVar18,param_2);
          if (dVar4 < (double)fVar27) {
            uStack_1f0 = CONCAT44(fVar27,fVar27);
            uStack_1e8 = CONCAT44(fVar27,fVar27);
            Aska::LightManager::CalcHemisphereLightCoeffs(Aska::LightManager::SHAmbConst*, Aska::Light const*, Aska::Vector*)(param_1,param_3,lVar18,&uStack_1f0);
          }
        }
        else {
          fVar21 = (float)Aska::Light::CalcIntensityTS(Aska::RenderableObject*, Aska::Light::CalcIntensityWork*, bool, bool, float*, float*, float*) const(lVar18,param_2,lVar18 + 0x310,
                                          (*(ulong *)(lVar18 + 0x2b0) & uVar19) != 0,0,0,0,0);
          if (fVar21 != 0.0) {
            fVar23 = ABS(fVar21);
            if (*(char *)(lVar18 + 0x2a2) != '\0') {
              fVar23 = fVar30;
            }
            lVar14 = alStack_e0[3];
            lVar7 = alStack_e0[4];
            lVar8 = alStack_e0[5];
            lVar9 = alStack_e0[6];
            fVar21 = fVar28;
            fVar33 = fVar25;
            fVar32 = fVar34;
            fVar29 = fVar35;
            lVar10 = alStack_e0[1];
            fVar11 = fVar24;
            if (fVar23 <= fVar27) {
              lVar17 = lVar18;
              lVar5 = alStack_e0[0];
              fVar31 = fVar23;
              fVar22 = fVar27;
              fVar27 = fVar23;
              if (fVar23 <= fVar24) {
joined_r0x022419b8:
                fVar23 = fVar22;
                fVar24 = fVar11;
                alStack_e0[0] = lVar5;
                alStack_e0[1] = lVar10;
                lVar10 = alStack_e0[2];
                fVar11 = fVar36;
                lVar17 = alStack_e0[1];
                fVar31 = fVar24;
                if ((((((fVar27 <= fVar36) ||
                       (lVar6 = lVar18, fVar26 = fVar27, lVar10 = lVar18, fVar11 = fVar27,
                       lVar18 = alStack_e0[2], fVar27 = fVar36, alStack_e0[2] != 0)) &&
                      ((fVar36 = fVar11, alStack_e0[2] = lVar10, lVar6 = alStack_e0[2],
                       fVar26 = fVar36, fVar27 <= fVar35 ||
                       (lVar14 = lVar18, fVar29 = fVar27, lVar18 = alStack_e0[3], fVar27 = fVar35,
                       alStack_e0[3] != 0)))) &&
                     ((fVar35 = fVar29, alStack_e0[3] = lVar14, lVar10 = lVar18, fVar11 = fVar27,
                      lVar14 = alStack_e0[3], fVar29 = fVar35, fVar27 <= fVar34 ||
                      (bVar1 = alStack_e0[4] != 0, lVar7 = lVar18, fVar32 = fVar27,
                      lVar10 = alStack_e0[4], alStack_e0[4] = lVar18, fVar11 = fVar34,
                      fVar34 = fVar27, bVar1)))) &&
                    ((lVar18 = alStack_e0[5], fVar27 = fVar25, lVar7 = alStack_e0[4],
                     fVar32 = fVar34, fVar11 <= fVar25 ||
                     (lVar8 = lVar10, fVar33 = fVar11, lVar18 = lVar10, lVar10 = alStack_e0[5],
                     fVar27 = fVar11, fVar11 = fVar25, alStack_e0[5] != 0)))) &&
                   ((fVar21 = fVar11, fVar25 = fVar27, alStack_e0[5] = lVar18,
                    lVar18 = alStack_e0[6], fVar11 = fVar28, fVar27 = fVar21, fVar21 <= fVar28 ||
                    (lVar8 = alStack_e0[5], lVar9 = lVar10, fVar33 = fVar25, lVar18 = lVar10,
                    fVar11 = fVar21, lVar10 = alStack_e0[6], fVar27 = fVar28, alStack_e0[6] != 0))))
                {
                  fVar28 = fVar11;
                  alStack_e0[6] = lVar18;
                  if ((fVar27 <= fVar37) ||
                     (bVar1 = alStack_e0[7] != 0, lVar18 = alStack_e0[0], alStack_e0[7] = lVar10,
                     fVar37 = fVar27, bVar1)) goto code_r0x02241b30;
                  goto code_r0x02241a58;
                }
              }
              else {
code_r0x0224199c:
                alStack_e0[0] = lVar5;
                lVar6 = alStack_e0[2];
                fVar23 = fVar22;
                fVar26 = fVar36;
                lVar10 = lVar17;
                lVar5 = alStack_e0[0];
                lVar18 = alStack_e0[1];
                fVar11 = fVar31;
                fVar27 = fVar24;
                if (alStack_e0[1] != 0) goto joined_r0x022419b8;
              }
              alStack_e0[6] = lVar9;
              alStack_e0[5] = lVar8;
              alStack_e0[4] = lVar7;
              alStack_e0[3] = lVar14;
              alStack_e0[2] = lVar6;
              alStack_e0[1] = lVar17;
              uVar15 = uVar15 + 1;
              fVar28 = fVar21;
              fVar25 = fVar33;
              fVar34 = fVar32;
              fVar35 = fVar29;
              fVar36 = fVar26;
              fVar24 = fVar31;
            }
            else {
              if (alStack_e0[0] != 0) {
                lVar17 = alStack_e0[0];
                lVar5 = lVar18;
                fVar31 = fVar27;
                fVar22 = fVar23;
                lVar18 = alStack_e0[0];
                if (fVar24 < fVar27) goto code_r0x0224199c;
                goto joined_r0x022419b8;
              }
code_r0x02241a58:
              alStack_e0[0] = lVar18;
              uVar15 = uVar15 + 1;
            }
          }
        }
      }
code_r0x02241b30:
      lVar18 = lVar20 + -0x1fd;
      lVar20 = lVar20 + 1;
      fVar27 = fVar23;
    } while (lVar18 < (long)(ulong)*(ushort *)(param_1 + 0x2ff8));
    if (0 < iVar16) {
      Aska::LightManager::CalcBounceLightCoeffs(Aska::LightManager::SHAmbConst*, Aska::RenderableObject*, Aska::Light**, int, Aska::Light**, int)(param_1,param_3,param_2,alStack_1e0,iVar16,alStack_e0,uVar15);
    }
  }
  ProcIBLforSHAmbi(Aska::RenderableObject*, Aska::LightManager::SHAmbConst*, bool)(param_2,param_3,0);
  lVar20 = alStack_e0[0];
  fVar30 = _UNK_027ebdf4;
  if ((int)uVar15 < 1) {
    *(undefined2 *)(param_3 + 0x308) = 0;
    return;
  }
  iVar12 = 0;
  iVar16 = 0;
  uVar19 = (ulong)uVar15;
  if (*PTR__ZN4Aska13ObjectManager20m_LightConfigurationE_02cbf638 == '\x02') {
    plVar13 = alStack_e0;
    do {
      lVar18 = *plVar13;
      fVar30 = *(float *)(lVar18 + 0x23c);
      fVar27 = *(float *)(lVar18 + 0x230) * fVar30;
      fVar24 = *(float *)(lVar18 + 0x234) * fVar30;
      fVar30 = *(float *)(lVar18 + 0x238) * fVar30;
      if (*(byte *)(lVar18 + 0x2a1) - 1 < 2) {
        if (iVar16 < 4) {
          lVar14 = param_3 + (long)iVar16 * 0x50;
          *(float *)(lVar14 + 0x130) = fVar27;
          *(float *)(lVar14 + 0x134) = fVar24;
          *(float *)(lVar14 + 0x138) = fVar30;
          *(undefined4 *)(lVar14 + 0x13c) = 0x3f800000;
          iVar16 = iVar16 + 1;
          *(undefined4 *)(lVar14 + 0x110) = *(undefined4 *)(lVar18 + 0x200);
          *(undefined4 *)(lVar14 + 0x114) = *(undefined4 *)(lVar18 + 0x204);
          *(undefined4 *)(lVar14 + 0x118) = *(undefined4 *)(lVar18 + 0x208);
          uVar2 = *(undefined4 *)(lVar18 + 0x20c);
          *(undefined8 *)(lVar14 + 0x120) = 0;
          *(undefined8 *)(lVar14 + 0x128) = 0;
          *(undefined8 *)(lVar14 + 0x140) = 0;
          *(undefined8 *)(lVar14 + 0x148) = 0;
          *(undefined4 *)(lVar14 + 0x11c) = uVar2;
        }
      }
      else if ((*(byte *)(lVar18 + 0x2a1) == 0) && (iVar12 < 4)) {
        lVar14 = param_3 + (long)iVar12 * 0x20;
        *(float *)(lVar14 + 0xa0) = fVar27;
        *(float *)(lVar14 + 0xa4) = fVar24;
        *(float *)(lVar14 + 0xa8) = fVar30;
        *(undefined4 *)(lVar14 + 0xac) = 0x3f800000;
        iVar12 = iVar12 + 1;
        *(undefined4 *)(lVar14 + 0x90) = *(undefined4 *)(lVar18 + 0x290);
        *(undefined4 *)(lVar14 + 0x94) = *(undefined4 *)(lVar18 + 0x294);
        *(undefined4 *)(lVar14 + 0x98) = *(undefined4 *)(lVar18 + 0x298);
        *(undefined4 *)(lVar14 + 0x9c) = *(undefined4 *)(lVar18 + 0x29c);
      }
      uVar19 = uVar19 - 1;
      plVar13 = plVar13 + 1;
    } while (uVar19 != 0);
  }
  else {
    plVar13 = alStack_e0;
    do {
      lVar18 = *plVar13;
      fVar24 = *(float *)(lVar18 + 0x23c) * fVar30;
      fVar25 = *(float *)(lVar18 + 0x230) * fVar24;
      fVar27 = *(float *)(lVar18 + 0x234) * fVar24;
      fVar24 = *(float *)(lVar18 + 0x238) * fVar24;
      if (*(byte *)(lVar18 + 0x2a1) - 1 < 2) {
        if (iVar16 < 4) {
          lVar14 = param_3 + (long)iVar16 * 0x50;
          *(float *)(lVar14 + 0x130) = fVar25;
          *(float *)(lVar14 + 0x134) = fVar27;
          *(float *)(lVar14 + 0x138) = fVar24;
          *(undefined4 *)(lVar14 + 0x13c) = 0x3f800000;
          iVar16 = iVar16 + 1;
          *(undefined4 *)(lVar14 + 0x110) = *(undefined4 *)(lVar18 + 0x200);
          *(undefined4 *)(lVar14 + 0x114) = *(undefined4 *)(lVar18 + 0x204);
          *(undefined4 *)(lVar14 + 0x118) = *(undefined4 *)(lVar18 + 0x208);
          uVar2 = *(undefined4 *)(lVar18 + 0x20c);
          *(undefined8 *)(lVar14 + 0x120) = 0;
          *(undefined8 *)(lVar14 + 0x128) = 0;
          *(undefined8 *)(lVar14 + 0x140) = 0;
          *(undefined8 *)(lVar14 + 0x148) = 0;
          *(undefined4 *)(lVar14 + 0x11c) = uVar2;
        }
      }
      else if ((*(byte *)(lVar18 + 0x2a1) == 0) && (iVar12 < 4)) {
        lVar14 = param_3 + (long)iVar12 * 0x20;
        *(float *)(lVar14 + 0xa0) = fVar25;
        *(float *)(lVar14 + 0xa4) = fVar27;
        *(float *)(lVar14 + 0xa8) = fVar24;
        *(undefined4 *)(lVar14 + 0xac) = 0x3f800000;
        iVar12 = iVar12 + 1;
        *(undefined4 *)(lVar14 + 0x90) = *(undefined4 *)(lVar18 + 0x290);
        *(undefined4 *)(lVar14 + 0x94) = *(undefined4 *)(lVar18 + 0x294);
        *(undefined4 *)(lVar14 + 0x98) = *(undefined4 *)(lVar18 + 0x298);
        *(undefined4 *)(lVar14 + 0x9c) = *(undefined4 *)(lVar18 + 0x29c);
      }
      uVar19 = uVar19 - 1;
      plVar13 = plVar13 + 1;
    } while (uVar19 != 0);
  }
  *(char *)(param_3 + 0x308) = (char)iVar12;
  *(char *)(param_3 + 0x309) = (char)iVar16;
  if ((int)uVar15 < 1) {
    return;
  }
  if (*(long *)(param_3 + 0x300) == 0) {
    *(long *)(param_3 + 0x300) = alStack_e0[0];
    if (*(char *)(alStack_e0[0] + 0x2a1) != '\0') goto code_r0x02241d98;
code_r0x02241e68:
    *(float *)(param_3 + 0x250) = -*(float *)(alStack_e0[0] + 0x290);
    *(float *)(param_3 + 0x254) = -*(float *)(alStack_e0[0] + 0x294);
    fVar24 = *(float *)(alStack_e0[0] + 0x298);
    *(undefined4 *)(param_3 + 0x25c) = 0x3f800000;
    fVar24 = -fVar24;
  }
  else {
    if (*(char *)(alStack_e0[0] + 0x2a1) == '\0') goto code_r0x02241e68;
code_r0x02241d98:
    lVar18 = (**(code **)(*param_2 + 0x98))(param_2);
    fVar30 = *(float *)(lVar20 + 0x200);
    fVar27 = *(float *)(lVar18 + 0xc);
    fVar25 = *(float *)(lVar18 + 0x1c);
    fVar28 = *(float *)(lVar18 + 0x2c);
    *(float *)(param_3 + 0x250) = fVar30;
    fVar24 = *(float *)(lVar20 + 0x204);
    fVar30 = fVar30 - fVar27;
    *(float *)(param_3 + 0x254) = fVar24;
    fVar27 = *(float *)(lVar20 + 0x208);
    fVar24 = fVar24 - fVar25;
    *(float *)(param_3 + 600) = fVar27;
    fVar27 = fVar27 - fVar28;
    uVar2 = *(undefined4 *)(lVar20 + 0x20c);
    *(float *)(param_3 + 0x250) = fVar30;
    *(float *)(param_3 + 0x254) = fVar24;
    fVar24 = fVar27 * fVar27 + fVar24 * fVar24 + fVar30 * fVar30;
    fVar30 = SQRT(fVar24);
    *(undefined4 *)(param_3 + 0x25c) = uVar2;
    *(float *)(param_3 + 600) = fVar27;
    if (NAN(fVar30)) {
      fVar30 = (float)sqrtf(fVar24);
    }
    if (fVar30 < _UNK_027e519c) goto code_r0x02241e94;
    fVar30 = 1.0 / fVar30;
    fVar24 = fVar30 * *(float *)(param_3 + 600);
    *(float *)(param_3 + 0x250) = fVar30 * *(float *)(param_3 + 0x250);
    *(float *)(param_3 + 0x254) = fVar30 * *(float *)(param_3 + 0x254);
  }
  *(float *)(param_3 + 600) = fVar24;
code_r0x02241e94:
  fVar30 = *(float *)(lVar20 + 0x230);
  *(float *)(param_3 + 0x260) = fVar30;
  fVar24 = *(float *)(lVar20 + 0x234);
  *(float *)(param_3 + 0x264) = fVar24;
  fVar27 = *(float *)(lVar20 + 0x238);
  *(float *)(param_3 + 0x268) = fVar27;
  *(undefined4 *)(param_3 + 0x26c) = *(undefined4 *)(lVar20 + 0x23c);
  fVar25 = *(float *)(lVar20 + 0x23c) * *(float *)(lVar20 + 0x2fc);
  *(float *)(param_3 + 0x260) = fVar25 * fVar30;
  *(float *)(param_3 + 0x264) = fVar25 * fVar24;
  *(float *)(param_3 + 0x268) = fVar25 * fVar27;
  return;
}

// ==== Aska::LightManager::CalcSH(Aska::LightManager::LightContextSimple*, Aska::Matrix const*)
// vaddr 0x2141f14 | ghidra 0x2241f14 | size 532 | symbol _ZN4Aska12LightManager6CalcSHEPNS0_18LightContextSimpleEPKNS_6MatrixE | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska12LightManager6CalcSHEPNS0_18LightContextSimpleEPKNS_6MatrixE
               (undefined8 param_1,long param_2,long param_3)

{
  float *pfVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  long lVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  float fVar19;
  float fStack_60;
  float fStack_5c;
  float fStack_58;
  
  memset(param_2 + 0x270,0,0x90);
  fVar5 = _UNK_029cc400;
  fVar4 = _UNK_029cc3fc;
  fVar3 = _UNK_029cc3f8;
  fVar2 = _UNK_028cfc70;
  lVar6 = 0;
  fVar7 = 0.0;
  fVar8 = 0.0;
  fVar9 = 0.0;
  fVar10 = 0.0;
  fVar11 = 0.0;
  fVar12 = 0.0;
  fVar13 = 0.0;
  fVar14 = 0.0;
  fVar15 = 0.0;
  fVar16 = 0.0;
  fVar17 = 0.0;
  fVar18 = 0.0;
  do {
    pfVar1 = (float *)(param_2 + 0x90 + lVar6);
    fStack_60 = -*pfVar1;
    fStack_5c = -pfVar1[1];
    fStack_58 = -pfVar1[2];
    if (param_3 != 0) {
      Aska::Vector::ApplyMatrixNoTransport(Aska::Matrix const*)(&fStack_60,param_3);
      fVar18 = *(float *)(param_2 + 0x270);
      fVar17 = *(float *)(param_2 + 0x280);
      fVar16 = *(float *)(param_2 + 0x290);
      fVar15 = *(float *)(param_2 + 0x2a0);
      fVar14 = *(float *)(param_2 + 0x274);
      fVar13 = *(float *)(param_2 + 0x284);
      fVar12 = *(float *)(param_2 + 0x294);
      fVar11 = *(float *)(param_2 + 0x2a4);
      fVar10 = *(float *)(param_2 + 0x278);
      fVar9 = *(float *)(param_2 + 0x288);
      fVar8 = *(float *)(param_2 + 0x298);
      fVar7 = *(float *)(param_2 + 0x2a8);
    }
    lVar6 = lVar6 + 0x20;
    fVar19 = pfVar1[4] * fVar5;
    fVar18 = fVar18 + pfVar1[4] * fVar3 * fVar4;
    fVar17 = fVar17 + fStack_5c * fVar19 * fVar4 * fVar2;
    fVar16 = fStack_58 * fVar19 * fVar4 * fVar2 + fVar16;
    fVar15 = fStack_60 * fVar19 * fVar4 * fVar2 + fVar15;
    *(float *)(param_2 + 0x270) = fVar18;
    *(float *)(param_2 + 0x280) = fVar17;
    *(float *)(param_2 + 0x290) = fVar16;
    *(float *)(param_2 + 0x2a0) = fVar15;
    fVar19 = pfVar1[5] * fVar5;
    fVar14 = fVar14 + pfVar1[5] * fVar3 * fVar4;
    fVar13 = fVar13 + fStack_5c * fVar19 * fVar4 * fVar2;
    fVar12 = fStack_58 * fVar19 * fVar4 * fVar2 + fVar12;
    fVar11 = fStack_60 * fVar19 * fVar4 * fVar2 + fVar11;
    *(float *)(param_2 + 0x274) = fVar14;
    *(float *)(param_2 + 0x284) = fVar13;
    *(float *)(param_2 + 0x294) = fVar12;
    *(float *)(param_2 + 0x2a4) = fVar11;
    fVar19 = pfVar1[6] * fVar5;
    fVar10 = fVar10 + pfVar1[6] * fVar3 * fVar4;
    fVar9 = fVar9 + fStack_5c * fVar19 * fVar4 * fVar2;
    fVar8 = fStack_58 * fVar19 * fVar4 * fVar2 + fVar8;
    fVar7 = fStack_60 * fVar19 * fVar4 * fVar2 + fVar7;
    *(float *)(param_2 + 0x278) = fVar10;
    *(float *)(param_2 + 0x288) = fVar9;
    *(float *)(param_2 + 0x298) = fVar8;
    *(float *)(param_2 + 0x2a8) = fVar7;
  } while (lVar6 != 0x80);
  return;
}

// ==== Aska::LightManager::PickOutPrimaryLights(Aska::RenderableObject*, Aska::Light**, int)
// vaddr 0x2142128 | ghidra 0x2242128 | size 1348 | symbol _ZN4Aska12LightManager20PickOutPrimaryLightsEPNS_16RenderableObjectEPPNS_5LightEi | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska12LightManager20PickOutPrimaryLightsEPNS_16RenderableObjectEPPNS_5LightEi
               (long param_1,long param_2,undefined8 param_3,uint param_4)

{
  bool bVar1;
  uint uVar2;
  long lVar3;
  float fVar4;
  long lVar5;
  long lVar6;
  long lVar7;
  long lVar8;
  long lVar9;
  long lVar10;
  long lVar11;
  long lVar12;
  long lVar13;
  long lVar14;
  uint uVar15;
  long lVar16;
  ulong uVar17;
  long lVar18;
  float fVar19;
  float fVar20;
  float fVar21;
  float fVar22;
  float fVar23;
  float fVar24;
  float fVar25;
  float fVar26;
  float fVar27;
  float fVar28;
  float fVar29;
  float fVar30;
  float fVar31;
  float fVar32;
  float fVar33;
  float fVar34;
  long lStack_158;
  long lStack_150;
  long lStack_148;
  long lStack_140;
  long lStack_130;
  long lStack_128;
  long lStack_120;
  long lStack_118;
  long lStack_110;
  long lStack_108;
  long lStack_100;
  long lStack_f8;
  long lStack_f0;
  long lStack_e0;
  long lStack_d8;
  long lStack_d0;
  long lStack_c8;
  long lStack_c0;
  long lStack_b8;
  long lStack_b0;
  long lStack_a8;
  
  memset(param_3,0,-(ulong)(param_4 >> 0x1f) & 0xfffffff800000000 | (ulong)param_4 << 3);
  fVar4 = _UNK_029cc100;
  lStack_b0 = 0;
  lStack_a8 = 0;
  lStack_c0 = 0;
  lStack_b8 = 0;
  lStack_d0 = 0;
  lStack_c8 = 0;
  lStack_e0 = 0;
  lStack_d8 = 0;
  if (*(ushort *)(param_1 + 0x2ff8) == 0) {
    uVar15 = 0;
  }
  else {
    lStack_118 = 0;
    lStack_110 = 0;
    lStack_108 = 0;
    lStack_100 = 0;
    lStack_f8 = 0;
    uVar17 = *(ulong *)(param_2 + 0x260);
    lStack_120 = 0;
    lStack_128 = 0;
    lVar13 = 0;
    lVar16 = 0;
    uVar15 = 0;
    lStack_130 = 0;
    fVar27 = 0.0;
    lStack_140 = 0;
    lStack_148 = 0;
    lStack_150 = 0;
    fVar28 = 0.0;
    lStack_158 = 0;
    lStack_f0 = 0;
    lVar12 = 0;
    lVar18 = 0;
    fVar34 = 0.0;
    fVar32 = 0.0;
    fVar23 = 0.0;
    fVar31 = 0.0;
    fVar29 = 0.0;
    fVar30 = 0.0;
    do {
      lVar14 = *(long *)(param_1 + 0xff0 + lVar16 * 8);
      lVar7 = lVar12;
      lVar6 = lVar18;
      fVar20 = fVar34;
      fVar21 = fVar32;
      fVar22 = fVar23;
      fVar24 = fVar31;
      fVar25 = fVar29;
      fVar26 = fVar30;
      if (((((*(ulong *)(lVar14 + 0x2a8) & uVar17) != 0) &&
           ((*(uint3 *)(lVar14 + 0x2a5) & 0x12000) == 0)) && (*(byte *)(lVar14 + 0x2a1) < 4)) &&
         (fVar19 = (float)Aska::Light::CalcIntensityTS(Aska::RenderableObject*, Aska::Light::CalcIntensityWork*, bool, bool, float*, float*, float*) const(lVar14,param_2,lVar14 + 0x310,
                                          (*(ulong *)(lVar14 + 0x2b0) & uVar17) != 0,0,0,0,0),
         fVar19 != 0.0)) {
        fVar19 = ABS(fVar19);
        if (*(char *)(lVar14 + 0x2a2) != '\0') {
          fVar19 = fVar4;
        }
        lVar3 = lVar14;
        lVar5 = lVar13;
        fVar33 = fVar19;
        lVar8 = lStack_f8;
        lVar9 = lStack_110;
        lVar10 = lStack_100;
        lVar11 = lStack_108;
        if (((((((fVar28 < fVar19) &&
                (lStack_120 = lVar14, lVar3 = lVar13, lVar5 = lVar14, fVar33 = fVar28,
                fVar28 = fVar19, lVar13 == 0)) ||
               ((fVar19 = fVar28, lVar14 = lVar5, fVar34 < fVar33 &&
                (lVar6 = lVar3, lStack_128 = lVar3, fVar20 = fVar33, lVar3 = lVar18, fVar33 = fVar34
                , lVar18 == 0)))) ||
              ((lVar13 = lVar3, fVar32 < fVar33 &&
               (lVar7 = lVar3, lVar13 = lVar12, lStack_130 = lVar3, fVar21 = fVar33, fVar33 = fVar32
               , lVar12 == 0)))) ||
             ((lVar12 = lVar13, fVar34 = fVar33, fVar23 < fVar33 &&
              (lVar8 = lVar13, lVar12 = lStack_f8, lStack_140 = lVar13, fVar22 = fVar33,
              fVar34 = fVar23, fVar23 = fVar33, lStack_f8 == 0)))) ||
            ((((lVar18 = lVar12, fVar23 = fVar22, fVar31 < fVar34 &&
               (bVar1 = lStack_110 == 0, lVar9 = lVar12, lStack_148 = lVar12, fVar24 = fVar34,
               lVar18 = lStack_110, lStack_110 = lVar12, fVar34 = fVar31, bVar1)) ||
              ((lVar12 = lStack_100, lVar9 = lStack_110, fVar29 < fVar34 &&
               (lVar10 = lVar18, lStack_150 = lVar18, fVar25 = fVar34, lVar12 = lVar18,
               lVar18 = lStack_100, fVar34 = fVar29, lStack_100 == 0)))) ||
             ((lStack_100 = lVar12, lVar12 = lStack_108, lVar10 = lStack_100, fVar30 < fVar34 &&
              (lVar11 = lVar18, lStack_158 = lVar18, fVar26 = fVar34, lVar12 = lVar18,
              lVar18 = lStack_108, fVar34 = fVar30, lStack_108 == 0)))))) ||
           ((lStack_108 = lVar12, lVar13 = lVar14, lStack_f8 = lVar8, fVar28 = fVar19,
            fVar27 < fVar34 &&
            (bVar1 = lStack_118 == 0, lStack_f0 = lVar18, lVar11 = lStack_108, lStack_118 = lVar18,
            fVar27 = fVar34, bVar1)))) {
          uVar15 = uVar15 + 1;
          lVar13 = lVar14;
          lStack_110 = lVar9;
          lStack_108 = lVar11;
          lStack_100 = lVar10;
          lStack_f8 = lVar8;
          fVar22 = fVar23;
          fVar28 = fVar19;
        }
      }
      lVar16 = lVar16 + 1;
      lVar12 = lVar7;
      lVar18 = lVar6;
      fVar34 = fVar20;
      fVar32 = fVar21;
      fVar23 = fVar22;
      fVar31 = fVar24;
      fVar29 = fVar25;
      fVar30 = fVar26;
    } while (lVar16 < (long)(ulong)*(ushort *)(param_1 + 0x2ff8));
    lStack_e0 = lStack_120;
    lStack_d8 = lStack_128;
    lStack_d0 = lStack_130;
    lStack_c8 = lStack_140;
    lStack_c0 = lStack_148;
    lStack_b8 = lStack_150;
    lStack_b0 = lStack_158;
    lStack_a8 = lStack_f0;
  }
  uVar2 = uVar15;
  if ((int)param_4 <= (int)uVar15) {
    uVar2 = param_4;
  }
  if (0 < (int)uVar2) {
    if ((int)param_4 <= (int)uVar15) {
      uVar15 = param_4;
    }
    memcpy(param_3,&lStack_e0,(ulong)(uVar15 - 1) * 8 + 8);
  }
  return;
}

// ==== Aska::LightManager::PrepareLightsForRendering(Aska::RenderableObject**, int)
// vaddr 0x214266c | ghidra 0x224266c | size 2148 | symbol _ZN4Aska12LightManager25PrepareLightsForRenderingEPPNS_16RenderableObjectEi | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska12LightManager25PrepareLightsForRenderingEPPNS_16RenderableObjectEi
               (long param_1,long param_2,int param_3)

{
  uint3 *puVar1;
  ulong *puVar2;
  ushort *puVar3;
  char cVar4;
  ushort uVar5;
  uint3 uVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  float fVar19;
  float fVar20;
  bool bVar21;
  long lVar22;
  ulong uVar23;
  byte bVar24;
  ulong uVar25;
  int iVar26;
  ulong uVar27;
  float *pfVar28;
  long lVar29;
  long *plVar30;
  long lVar31;
  long lVar32;
  long *plVar33;
  uint uVar34;
  undefined8 *puVar35;
  float fVar36;
  float fVar37;
  float fVar38;
  float fVar39;
  float fVar40;
  float fVar41;
  float fVar42;
  char acStack_2d30 [128];
  undefined1 auStack_2cb0 [16];
  undefined8 auStack_2ca0 [510];
  float afStack_1cb0 [1536];
  long alStack_4b0 [128];
  ulong auStack_b0 [2];
  
  lVar32 = *(long *)(*(long *)PTR__ZN4Aska6Global16m_pCameraManagerE_02cb7d08 + 0xff0);
  if (*(char *)(lVar32 + 0x940) == '\0') {
    Aska::Camera::MakeViewFrustumPlane(int)(lVar32,0xffffffff);
  }
  lVar31 = *(long *)PTR__ZN4Aska6Global16m_pObjectManagerE_02cc4688;
  uVar27 = 0;
  uVar34 = 0;
  auStack_b0[1] = _UNK_0285f1f8;
  auStack_b0[0] = _UNK_0285f1f0;
  do {
    while (*(int *)(lVar31 + uVar27 * 4 + 0x1c08) != 0) {
      lVar29 = *(long *)(lVar31 + uVar27 * 0x48 + 0x4610);
      if (*(char *)(lVar29 + 0x940) == '\0') {
        Aska::Camera::MakeViewFrustumPlane(int)(lVar29,0xffffffff);
      }
      uVar27 = uVar27 + 1;
      uVar25 = auStack_b0[(long)uVar27 >> 6];
      alStack_4b0[(int)uVar34] = lVar29;
      uVar34 = uVar34 + 1;
      auStack_b0[(long)uVar27 >> 6] = uVar25 | 1L << (uVar27 & 0x3f);
      if (uVar27 == 0x80) goto code_r0x0224276c;
    }
    uVar27 = uVar27 + 1;
  } while (uVar27 != 0x80);
code_r0x0224276c:
  puVar3 = (ushort *)(param_1 + 0x2ff8);
  *puVar3 = 0;
  *(short *)(param_1 + 0x300e) = 0;
  fVar20 = _UNK_027f7cb4;
  fVar19 = _UNK_027f7cb0;
  fVar18 = _UNK_027f7cac;
  fVar17 = _UNK_027f7ca8;
  fVar16 = _UNK_027f7ca4;
  fVar15 = _UNK_027edb30;
  fVar14 = _UNK_027ebe0c;
  fVar13 = _UNK_027ebe08;
  fVar12 = _UNK_027ebe04;
  fVar11 = _UNK_027ebe00;
  fVar10 = _UNK_027ebdfc;
  fVar9 = _UNK_027ebdf8;
  fVar8 = _UNK_027ebdf4;
  fVar7 = _UNK_027e519c;
  lVar29 = _UNK_027dbb38;
  lVar31 = _UNK_027dbb30;
  fVar38 = _UNK_027daba4;
  plVar30 = *(long **)(param_1 + 0x18);
  if ((long *)(param_1 + 8) == plVar30) {
    bVar21 = false;
    uVar27 = 0;
  }
  else {
    uVar27 = 0;
    do {
      puVar1 = (uint3 *)((long)plVar30 + 0x2a5);
      if (((*(ushort *)puVar1 & 1) != 0) && (fVar38 <= *(float *)(plVar30 + 0x57))) {
        if (0x1ff < *puVar3) break;
        if ((plVar30[0x36] != 0) || ((*(byte *)(plVar30 + 0x25) & 1) != 0)) {
          (**(code **)(*plVar30 + 0xa8))(plVar30);
        }
        lVar22 = (**(code **)(*plVar30 + 0x98))(plVar30);
        fVar37 = *(float *)(lVar22 + 8);
        fVar40 = *(float *)(lVar22 + 0x18);
        fVar41 = *(float *)(lVar22 + 0x28);
        *(undefined4 *)((long)plVar30 + 0x29c) = 0x3f800000;
        fVar39 = fVar37 * fVar37 + fVar40 * fVar40 + fVar41 * fVar41;
        fVar36 = SQRT(fVar39);
        *(float *)(plVar30 + 0x52) = fVar37;
        *(float *)((long)plVar30 + 0x294) = fVar40;
        *(float *)(plVar30 + 0x53) = fVar41;
        if (NAN(fVar36)) {
          fVar36 = (float)sqrtf(fVar39);
        }
        if (fVar7 <= fVar36) {
          fVar36 = 1.0 / fVar36;
          *(float *)(plVar30 + 0x52) = fVar36 * *(float *)(plVar30 + 0x52);
          *(float *)((long)plVar30 + 0x294) = fVar36 * *(float *)((long)plVar30 + 0x294);
          *(float *)(plVar30 + 0x53) = fVar36 * *(float *)(plVar30 + 0x53);
        }
        *(undefined4 *)((long)plVar30 + 0x29c) = 0;
        *(undefined4 *)((long)plVar30 + 0x20c) = 0x3f800000;
        *(undefined4 *)(plVar30 + 0x40) = *(undefined4 *)((long)plVar30 + 0x4c);
        *(undefined4 *)((long)plVar30 + 0x204) = *(undefined4 *)((long)plVar30 + 0x5c);
        *(undefined4 *)(plVar30 + 0x41) = *(undefined4 *)((long)plVar30 + 0x6c);
        uVar6 = *puVar1;
        if ((uVar6 & 0x800) != 0) {
          Aska::Light::MakeNoiseIntension()(plVar30);
          uVar6 = *puVar1;
        }
        *(char *)((long)plVar30 + 0x2a7) = (char)(uVar6 >> 0x10);
        *(ushort *)puVar1 = (ushort)uVar6 & 0xfff9;
        cVar4 = *(char *)((long)plVar30 + 0x2a1);
        plVar30[0x67] = 0;
        plVar30[0x66] = 0;
        if (cVar4 != '\x03') {
          if (cVar4 == '\x02') {
            iVar26 = (int)uVar27;
            if (0x7f < iVar26) {
              return;
            }
            lVar22 = (long)iVar26;
            pfVar28 = afStack_1cb0 + lVar22 * 0xc;
            fVar37 = *(float *)((long)plVar30 + 0x2d4);
            fVar40 = *(float *)(plVar30 + 0x5b);
            fVar41 = *(float *)(plVar30 + 0x57);
            *pfVar28 = *(float *)(plVar30 + 0x40);
            fVar40 = (fVar37 + fVar40) * 0.5;
            afStack_1cb0[lVar22 * 0xc + 1] = *(float *)((long)plVar30 + 0x204);
            afStack_1cb0[lVar22 * 0xc + 2] = *(float *)(plVar30 + 0x41);
            afStack_1cb0[lVar22 * 0xc + 3] = *(float *)((long)plVar30 + 0x20c);
            fVar37 = fVar40 + (float)(int)(fVar40 * fVar8) * fVar15;
            fVar36 = fVar37 * fVar37;
            afStack_1cb0[lVar22 * 0xc + 4] = *(float *)(plVar30 + 0x52);
            bVar21 = ((int)(fVar40 * fVar8) & 1U) != 0;
            if (bVar21) {
              fVar37 = -fVar37;
            }
            afStack_1cb0[lVar22 * 0xc + 5] = *(float *)((long)plVar30 + 0x294);
            fVar42 = fVar36 * (fVar36 * (fVar36 * (fVar36 * fVar9 + fVar10) + fVar11) + fVar12);
            afStack_1cb0[lVar22 * 0xc + 6] = *(float *)(plVar30 + 0x53);
            fVar39 = *(float *)((long)plVar30 + 0x29c);
            fVar37 = fVar37 * (fVar36 * (fVar36 * (fVar36 * (fVar36 * fVar16 + fVar17) + fVar18) +
                                        fVar19) + fVar20);
            fVar36 = fVar13 - fVar42;
            if (!bVar21) {
              fVar36 = fVar42 + fVar14;
            }
            afStack_1cb0[lVar22 * 0xc + 8] = fVar36;
            afStack_1cb0[lVar22 * 0xc + 9] = fVar37;
            afStack_1cb0[lVar22 * 0xc + 7] = fVar39;
            afStack_1cb0[lVar22 * 0xc + 10] = fVar41;
            afStack_1cb0[lVar22 * 0xc + 0xb] = (fVar41 * fVar37) / fVar36;
            lVar22 = (long)iVar26;
            puVar2 = (ulong *)(plVar30 + 0x66);
            Aska::AABB::SetCone(Aska::Vector const*, Aska::Vector const*, float, float)(fVar40,(int)plVar30[0x57],auStack_2cb0 + lVar22 * 0x20,plVar30 + 0x40,
                            plVar30 + 0x52);
            acStack_2d30[lVar22] = '\0';
            *(char *)((long)plVar30 + 0x2a3) = (char)uVar27;
            *puVar2 = 0;
            plVar30[0x67] = 0;
            uVar27 = Aska::FrustumCulling(Aska::Vector const*, Aska::Vector const*, Aska::CullingCone const*)(lVar32 + 0x200,lVar32 + 0x560,pfVar28);
            if ((uVar27 & 1) == 0) {
              acStack_2d30[lVar22] = '\x01';
            }
            else {
              *puVar2 = *puVar2 | 1;
            }
            if (0 < (int)uVar34) {
              uVar27 = 0;
              do {
                while (uVar25 = Aska::FrustumCulling(Aska::Vector const*, Aska::Vector const*, Aska::CullingCone const*)(alStack_4b0[uVar27] + 0x200,
                                                alStack_4b0[uVar27] + 0x560,pfVar28),
                      (uVar25 & 1) == 0) {
                  acStack_2d30[lVar22] = '\x01';
                  uVar27 = uVar27 + 1;
                  if (uVar27 == uVar34) goto code_r0x02242c5c;
                }
                uVar27 = uVar27 + 1;
                puVar2[(long)uVar27 >> 6] = puVar2[(long)uVar27 >> 6] | 1L << (uVar27 & 0x3f);
              } while (uVar27 != uVar34);
            }
code_r0x02242c5c:
            cVar4 = *(char *)((long)plVar30 + 0x2a1);
            uVar27 = (ulong)(iVar26 + 1);
          }
          if (cVar4 == '\b') {
            lVar22 = Aska::Light::GetIBLTextureID(int) const(plVar30,0);
            if (((lVar22 != 0) && ((*(ushort *)puVar1 >> 0xd & 1) == 0)) &&
               (plVar33 = (long *)plVar30[0x80], plVar33 != (long *)0x0)) {
              bVar24 = *(byte *)(plVar33 + 0x25);
              if ((bVar24 & 1) != 0) {
                (**(code **)(*plVar33 + 0xa8))(plVar33);
                bVar24 = *(byte *)(plVar33 + 0x25);
              }
              if ((bVar24 >> 2 & 1) == 0) {
                if ((*(byte *)((long)plVar33 + 0x129) & 3) == 0) {
                  fVar37 = *(float *)((long)plVar33 + 0x4c);
                  fVar40 = *(float *)((long)plVar33 + 0x5c);
                  fVar41 = *(float *)((long)plVar33 + 0x6c);
                  plVar33[0x27] = CONCAT44((int)plVar33[0xe],*(float *)(plVar33 + 0xc));
                  plVar33[0x26] = CONCAT44(*(float *)(plVar33 + 10),*(float *)(plVar33 + 8));
                  plVar33[0x29] =
                       CONCAT44(*(undefined4 *)((long)plVar33 + 0x74),
                                *(float *)((long)plVar33 + 100));
                  plVar33[0x28] =
                       CONCAT44(*(float *)((long)plVar33 + 0x54),*(float *)((long)plVar33 + 0x44));
                  *(float *)((long)plVar33 + 0x13c) =
                       -(*(float *)(plVar33 + 8) * fVar37 + *(float *)(plVar33 + 10) * fVar40 +
                        *(float *)(plVar33 + 0xc) * fVar41);
                  *(float *)((long)plVar33 + 0x14c) =
                       -(fVar37 * *(float *)((long)plVar33 + 0x44) +
                         fVar40 * *(float *)((long)plVar33 + 0x54) +
                        fVar41 * *(float *)((long)plVar33 + 100));
                  plVar33[0x2b] = CONCAT44((int)plVar33[0xf],*(float *)(plVar33 + 0xd));
                  plVar33[0x2a] = CONCAT44(*(float *)(plVar33 + 0xb),*(float *)(plVar33 + 9));
                  plVar33[0x2d] = lVar29;
                  plVar33[0x2c] = lVar31;
                  *(float *)((long)plVar33 + 0x15c) =
                       -(fVar37 * *(float *)(plVar33 + 9) + fVar40 * *(float *)(plVar33 + 0xb) +
                        fVar41 * *(float *)(plVar33 + 0xd));
                }
                else {
                  Aska::Matrix::InvertLowError(Aska::Matrix*) const(plVar33 + 8,plVar33 + 0x26);
                  bVar24 = *(byte *)(plVar33 + 0x25);
                }
                *(byte *)(plVar33 + 0x25) = bVar24 | 4;
              }
            }
          }
          else {
            uVar5 = *puVar3;
            *puVar3 = uVar5 + 1;
            *(long **)(param_1 + (ulong)uVar5 * 8 + 0xff0) = plVar30;
          }
        }
      }
      plVar30 = (long *)plVar30[2];
    } while ((long *)(param_1 + 8) != plVar30);
    bVar21 = *(short *)(param_1 + 0x300e) != 0;
  }
  *(undefined1 *)(param_1 + 0x3009) = 0;
  iVar26 = (int)uVar27;
  if ((((iVar26 != 0) || (bVar21)) || (*(short *)(param_1 + 0x2ffa) != 0)) &&
     ((0 < param_3 && (iVar26 != 0)))) {
    lVar32 = 0;
    do {
      plVar30 = *(long **)(param_2 + lVar32 * 8);
      if ((*(byte *)(plVar30 + 0x25) >> 4 & 1) == 0) {
        (**(code **)(*plVar30 + 600))(plVar30,1);
      }
      if (0 < iVar26) {
        lVar29 = plVar30[0x5b];
        lVar31 = plVar30[0x5a];
        uVar25 = 0;
        fVar38 = (float)((ulong)lVar29 >> 0x20);
        pfVar28 = afStack_1cb0;
        puVar35 = auStack_2ca0;
        do {
          lVar22 = plVar30[0x34];
          cVar4 = acStack_2d30[uVar25];
          if (lVar22 == 0) {
            if (cVar4 != '\0') goto code_r0x02242df8;
          }
          else {
            if (*(char *)(lVar22 + 0x940) == '\0') {
              Aska::Camera::MakeViewFrustumPlane(int)(lVar22,0xffffffff);
            }
            uVar23 = Aska::FrustumCulling(Aska::Vector const*, Aska::Vector const*, Aska::CullingCone const*)(lVar22 + 0x200,lVar22 + 0x560,pfVar28);
            if ((cVar4 != '\0') || ((uVar23 & 1) == 0)) {
code_r0x02242df8:
              if ((ABS((float)((ulong)puVar35[-1] >> 0x20) - fVar38) <=
                   fVar38 + (float)((ulong)puVar35[1] >> 0x20) &&
                   (ABS((float)puVar35[-1] - (float)lVar29) <= fVar38 + (float)puVar35[1] &&
                   (ABS((float)puVar35[-2] - (float)lVar31) <= fVar38 + (float)*puVar35 &&
                   ABS((float)((ulong)puVar35[-2] >> 0x20) - (float)((ulong)lVar31 >> 0x20)) <=
                   fVar38 + (float)((ulong)*puVar35 >> 0x20)))) &&
                 (uVar23 = Aska::ConeCulling(Aska::CullingCone*, Aska::RenderableObject*)(pfVar28,plVar30), (uVar23 & 1) == 0)) {
                plVar30[((long)uVar25 >> 6) + 0x3d] =
                     plVar30[((long)uVar25 >> 6) + 0x3d] | 1L << (uVar25 & 0x3f);
              }
            }
          }
          uVar25 = uVar25 + 1;
          pfVar28 = pfVar28 + 0xc;
          puVar35 = puVar35 + 4;
        } while (uVar27 != uVar25);
      }
      lVar32 = lVar32 + 1;
    } while (lVar32 < param_3);
  }
  return;
}

// ==== Aska::LightManager::PrepareForTexture()
// vaddr 0x2142ed0 | ghidra 0x2242ed0 | size 56 | symbol _ZN4Aska12LightManager17PrepareForTextureEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska12LightManager17PrepareForTextureEv(long param_1)

{
  ulong uVar1;
  undefined8 *puVar2;
  
  uVar1 = (ulong)*(ushort *)(param_1 + 0x2ffa);
  if (uVar1 != 0) {
    puVar2 = (undefined8 *)(param_1 + 0x1ff0);
    do {
      Aska::Light::RegisterDiffuseCubeMap()(*puVar2);
      uVar1 = uVar1 - 1;
      puVar2 = puVar2 + 1;
    } while (uVar1 != 0);
  }
  return;
}

// ==== Aska::LightManager::~LightManager()
// vaddr 0x214300c | ghidra 0x224300c | size 24 | symbol _ZN4Aska12LightManagerD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska12LightManagerD0Ev(undefined8 param_1)

{
  Aska::TaskManager::~TaskManager()();
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::LightManager::GetClassID(int) const
// vaddr 0x2143024 | ghidra 0x2243024 | size 88 | symbol _ZNK4Aska12LightManager10GetClassIDEi | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska12LightManager10GetClassIDEi(undefined8 param_1,int param_2)

{
  undefined8 uVar1;
  undefined8 uVar2;
  
  if (param_2 == 0) {
    return 0xf002f003f009;
  }
  if (param_2 == 1) {
    return 0xf002f003;
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

// ==== Aska::LightManager::Delete(Aska::Task*)
// vaddr 0x214307c | ghidra 0x224307c | size 24 | symbol _ZN4Aska12LightManager6DeleteEPNS_4TaskE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska12LightManager6DeleteEPNS_4TaskE(long param_1,long param_2)

{
  if (*(long *)(param_1 + 0x2ff0) == param_2) {
    *(undefined8 *)(param_1 + 0x2ff0) = 0;
  }
  (*(code *)PTR__ZN4Aska11TaskManager6DeleteEPNS_4TaskE_02cb43e8)();
  return;
}

// ==== Aska::LightManager::GetDefaultLevel() const
// vaddr 0x2143094 | ghidra 0x2243094 | size 8 | symbol _ZNK4Aska12LightManager15GetDefaultLevelEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska12LightManager15GetDefaultLevelEv(void)

{
  return 0x1000;
}

// ==== non-virtual thunk to Aska::LightManager::~LightManager()
// vaddr 0x214309c | ghidra 0x224309c | size 8 | symbol _ZThn40_N4Aska12LightManagerD1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZThn40_N4Aska12LightManagerD1Ev(long param_1)

{
  (*(code *)PTR__ZN4Aska11TaskManagerD2Ev_02ca45c0)(param_1 + -0x28);
  return;
}

// ==== non-virtual thunk to Aska::LightManager::~LightManager()
// vaddr 0x21430a4 | ghidra 0x22430a4 | size 28 | symbol _ZThn40_N4Aska12LightManagerD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZThn40_N4Aska12LightManagerD0Ev(long param_1)

{
  Aska::TaskManager::~TaskManager()(param_1 + -0x28);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1 + -0x28);
  return;
}

// ==== non-virtual thunk to Aska::LightManager::GetClassID(int) const
// vaddr 0x21430c0 | ghidra 0x22430c0 | size 88 | symbol _ZThn40_NK4Aska12LightManager10GetClassIDEi | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZThn40_NK4Aska12LightManager10GetClassIDEi(undefined8 param_1,int param_2)

{
  undefined8 uVar1;
  undefined8 uVar2;
  
  if (param_2 == 0) {
    return 0xf002f003f009;
  }
  if (param_2 == 1) {
    return 0xf002f003;
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

// ==== non-virtual thunk to Aska::LightManager::GetDefaultLevel() const
// vaddr 0x2143118 | ghidra 0x2243118 | size 8 | symbol _ZThn40_NK4Aska12LightManager15GetDefaultLevelEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZThn40_NK4Aska12LightManager15GetDefaultLevelEv(void)

{
  return 0x1000;
}

// ==== Aska::RenderContext::Static::SetShaderConstantLightMaskGroup(Aska::RenderDeviceGL*, Aska::LightManager::LightContext*)
// vaddr 0x2174418 | ghidra 0x2274418 | size 224 | symbol _ZN4Aska13RenderContext6Static31SetShaderConstantLightMaskGroupEPNS_14RenderDeviceGLEPNS_12LightManager12LightContextE | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Possible PIC construction at 0x02274434: Changing call to branch */
/* WARNING: Possible PIC construction at 0x0227445c: Changing call to branch */
/* WARNING: Possible PIC construction at 0x022744a4: Changing call to branch */
/* WARNING: Possible PIC construction at 0x022744cc: Changing call to branch */
/* WARNING: Removing unreachable block (ram,0x02274438) */
/* WARNING: Removing unreachable block (ram,0x02274460) */
/* WARNING: Removing unreachable block (ram,0x022744ec) */
/* WARNING: Removing unreachable block (ram,0x02274480) */
/* WARNING: Removing unreachable block (ram,0x02274494) */
/* WARNING: Removing unreachable block (ram,0x022744a8) */
/* WARNING: Removing unreachable block (ram,0x022744bc) */
/* WARNING: Removing unreachable block (ram,0x022744d0) */
/* WARNING: Recovered jumptable eliminated as dead code */

void _ZN4Aska13RenderContext6Static31SetShaderConstantLightMaskGroupEPNS_14RenderDeviceGLEPNS_12LightManager12LightContextE
               (undefined8 param_1,long param_2)

{
  (*(code *)PTR__ZN4Aska14RenderDeviceGL22SetPixelShaderConstantEiPKvi_02c965b0)
            (param_1,0x16,param_2 + 0xa0,1);
  return;
}

// ==== Aska::LightManager::LightContextSimple::operator=(Aska::LightManager::LightContextSimple const&)
// vaddr 0x21a77b4 | ghidra 0x22a77b4 | size 1076 | symbol _ZN4Aska12LightManager18LightContextSimpleaSERKS1_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska12LightManager18LightContextSimpleaSERKS1_(undefined4 *param_1,undefined4 *param_2)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  long lVar3;
  
  *param_1 = *param_2;
  param_1[1] = param_2[1];
  param_1[2] = param_2[2];
  param_1[3] = param_2[3];
  param_1[4] = param_2[4];
  param_1[5] = param_2[5];
  param_1[6] = param_2[6];
  param_1[7] = param_2[7];
  param_1[8] = param_2[8];
  param_1[9] = param_2[9];
  param_1[10] = param_2[10];
  param_1[0xb] = param_2[0xb];
  param_1[0xc] = param_2[0xc];
  param_1[0xd] = param_2[0xd];
  param_1[0xe] = param_2[0xe];
  param_1[0xf] = param_2[0xf];
  param_1[0x10] = param_2[0x10];
  param_1[0x11] = param_2[0x11];
  param_1[0x12] = param_2[0x12];
  param_1[0x13] = param_2[0x13];
  param_1[0x14] = param_2[0x14];
  param_1[0x15] = param_2[0x15];
  param_1[0x16] = param_2[0x16];
  param_1[0x17] = param_2[0x17];
  param_1[0x18] = param_2[0x18];
  param_1[0x19] = param_2[0x19];
  param_1[0x1a] = param_2[0x1a];
  param_1[0x1b] = param_2[0x1b];
  param_1[0x1c] = param_2[0x1c];
  param_1[0x1d] = param_2[0x1d];
  param_1[0x1e] = param_2[0x1e];
  param_1[0x1f] = param_2[0x1f];
  *(undefined1 *)(param_1 + 0x20) = *(undefined1 *)(param_2 + 0x20);
  param_1[0x24] = param_2[0x24];
  param_1[0x25] = param_2[0x25];
  param_1[0x26] = param_2[0x26];
  param_1[0x27] = param_2[0x27];
  param_1[0x28] = param_2[0x28];
  param_1[0x29] = param_2[0x29];
  param_1[0x2a] = param_2[0x2a];
  param_1[0x2b] = param_2[0x2b];
  param_1[0x2c] = param_2[0x2c];
  param_1[0x2d] = param_2[0x2d];
  param_1[0x2e] = param_2[0x2e];
  param_1[0x2f] = param_2[0x2f];
  param_1[0x30] = param_2[0x30];
  param_1[0x31] = param_2[0x31];
  param_1[0x32] = param_2[0x32];
  param_1[0x33] = param_2[0x33];
  param_1[0x34] = param_2[0x34];
  param_1[0x35] = param_2[0x35];
  param_1[0x36] = param_2[0x36];
  param_1[0x37] = param_2[0x37];
  param_1[0x38] = param_2[0x38];
  param_1[0x39] = param_2[0x39];
  param_1[0x3a] = param_2[0x3a];
  param_1[0x3b] = param_2[0x3b];
  param_1[0x3c] = param_2[0x3c];
  param_1[0x3d] = param_2[0x3d];
  param_1[0x3e] = param_2[0x3e];
  param_1[0x3f] = param_2[0x3f];
  param_1[0x40] = param_2[0x40];
  param_1[0x41] = param_2[0x41];
  param_1[0x42] = param_2[0x42];
  param_1[0x43] = param_2[0x43];
  lVar3 = 0x15c;
  do {
    puVar1 = (undefined4 *)((long)param_2 + lVar3);
    puVar2 = (undefined4 *)((long)param_1 + lVar3);
    lVar3 = lVar3 + 0x50;
    puVar2[-0x13] = puVar1[-0x13];
    puVar2[-0x12] = puVar1[-0x12];
    puVar2[-0x11] = puVar1[-0x11];
    puVar2[-0x10] = puVar1[-0x10];
    puVar2[-0xf] = puVar1[-0xf];
    puVar2[-0xe] = puVar1[-0xe];
    puVar2[-0xd] = puVar1[-0xd];
    puVar2[-0xc] = puVar1[-0xc];
    puVar2[-0xb] = puVar1[-0xb];
    puVar2[-10] = puVar1[-10];
    puVar2[-9] = puVar1[-9];
    puVar2[-8] = puVar1[-8];
    puVar2[-7] = puVar1[-7];
    puVar2[-6] = puVar1[-6];
    puVar2[-5] = puVar1[-5];
    puVar2[-4] = puVar1[-4];
    puVar2[-3] = puVar1[-3];
    puVar2[-2] = puVar1[-2];
    puVar2[-1] = puVar1[-1];
    *puVar2 = *puVar1;
  } while (lVar3 != 0x29c);
  param_1[0x94] = param_2[0x94];
  param_1[0x95] = param_2[0x95];
  param_1[0x96] = param_2[0x96];
  param_1[0x97] = param_2[0x97];
  param_1[0x98] = param_2[0x98];
  param_1[0x99] = param_2[0x99];
  param_1[0x9a] = param_2[0x9a];
  param_1[0x9b] = param_2[0x9b];
  param_1[0x9c] = param_2[0x9c];
  param_1[0x9d] = param_2[0x9d];
  param_1[0x9e] = param_2[0x9e];
  param_1[0x9f] = param_2[0x9f];
  param_1[0xa0] = param_2[0xa0];
  param_1[0xa1] = param_2[0xa1];
  param_1[0xa2] = param_2[0xa2];
  param_1[0xa3] = param_2[0xa3];
  param_1[0xa4] = param_2[0xa4];
  param_1[0xa5] = param_2[0xa5];
  param_1[0xa6] = param_2[0xa6];
  param_1[0xa7] = param_2[0xa7];
  param_1[0xa8] = param_2[0xa8];
  param_1[0xa9] = param_2[0xa9];
  param_1[0xaa] = param_2[0xaa];
  param_1[0xab] = param_2[0xab];
  param_1[0xac] = param_2[0xac];
  param_1[0xad] = param_2[0xad];
  param_1[0xae] = param_2[0xae];
  param_1[0xaf] = param_2[0xaf];
  param_1[0xb0] = param_2[0xb0];
  param_1[0xb1] = param_2[0xb1];
  param_1[0xb2] = param_2[0xb2];
  param_1[0xb3] = param_2[0xb3];
  param_1[0xb4] = param_2[0xb4];
  param_1[0xb5] = param_2[0xb5];
  param_1[0xb6] = param_2[0xb6];
  param_1[0xb7] = param_2[0xb7];
  param_1[0xb8] = param_2[0xb8];
  param_1[0xb9] = param_2[0xb9];
  param_1[0xba] = param_2[0xba];
  param_1[0xbb] = param_2[0xbb];
  param_1[0xbc] = param_2[0xbc];
  param_1[0xbd] = param_2[0xbd];
  param_1[0xbe] = param_2[0xbe];
  param_1[0xbf] = param_2[0xbf];
  *(undefined2 *)(param_1 + 0xc2) = *(undefined2 *)(param_2 + 0xc2);
  *(undefined8 *)(param_1 + 0xc0) = *(undefined8 *)(param_2 + 0xc0);
  return;
}


// FAILED to create function at 029c7110 typeinfo name for AofObjectDeleteArrayHandler<Aska::LightManager::LightContext>
// FAILED to create function at 02c48a88 AofObjectDeleteArrayHandler<Aska::LightManager::LightContext>::vtable
// FAILED to create function at 02c48a98 AofObjectDeleteArrayHandler<Aska::LightManager::LightContext>[16]::vtable
// FAILED to create function at 02c48e70 AofObjectDeleteArrayHandler<Aska::LightManager::LightContext>::typeinfo
// FAILED to create function at 02c4e758 Aska::Light::vtable
// FAILED to create function at 02c4e8f0 Aska::Light::typeinfo
// FAILED to create function at 02c4e9a8 Aska::LightManager::vtable
// FAILED to create function at 02c4eaf0 Aska::LightManager::typeinfo
// FAILED to create function at 02ccb348 Aska::Light::m_fRangeReductionRatio
// FAILED to create function at 02dce494 Aska::Light::m_fNoiseTime
// FAILED to create function at 02dd04b8 Aska::LightManager::m_bMultipassDeferred
