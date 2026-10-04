// port/decomp/scene/skinning.c: Ghidra decompiles for the scene subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-04 06:32 UTC: tools/decomp.sh '--into' 'scene/skinning' 'Aska::JointObject::' 'Aska::SkinMatrices\w*::'

// ==== Aska::SkinMatrices::SkinMatrices()
// vaddr 0x21d531c | ghidra 0x22d531c | size 48 | symbol _ZN4Aska12SkinMatricesC1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska12SkinMatricesC2Ev(long *param_1)

{
  undefined *puVar1;
  
  Aska::SkinMatricesBase::SkinMatricesBase()();
  puVar1 = PTR__ZTVN4Aska12SkinMatricesE_02cb79f0;
  param_1[0x12] = 0;
  param_1[0x11] = 0;
  param_1[0x10] = 0;
  param_1[0xf] = 0;
  *param_1 = (long)(puVar1 + 0x10);
  return;
}

// ==== Aska::SkinMatrices::~SkinMatrices()
// vaddr 0x21d534c | ghidra 0x22d534c | size 24 | symbol _ZN4Aska12SkinMatricesD2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska12SkinMatricesD1Ev(long *param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZTVN4Aska12SkinMatricesE_02cb79f0;
  param_1[0xf] = 0;
  *param_1 = (long)(puVar1 + 0x10);
  (*(code *)PTR__ZN4Aska16SkinMatricesBaseD1Ev_02c9a4a8)();
  return;
}

// ==== Aska::SkinMatrices::~SkinMatrices()
// vaddr 0x21d5364 | ghidra 0x22d5364 | size 44 | symbol _ZN4Aska12SkinMatricesD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska12SkinMatricesD0Ev(long *param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZTVN4Aska12SkinMatricesE_02cb79f0;
  param_1[0xf] = 0;
  *param_1 = (long)(puVar1 + 0x10);
  Aska::SkinMatricesBase::~SkinMatricesBase()();
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::SkinMatrices::GetAllocSize(unsigned long, unsigned long, unsigned long) const
// vaddr 0x21d5390 | ghidra 0x22d5390 | size 80 | symbol _ZNK4Aska12SkinMatrices12GetAllocSizeEmmm | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK4Aska12SkinMatrices12GetAllocSizeEmmm(undefined8 param_1,long param_2)

{
  long lVar1;
  long lVar2;
  
  lVar1 = Aska::SkinMatricesBase::GetAllocSize(unsigned long, unsigned long, unsigned long) const();
  lVar2 = *(long *)PTR__ZN4Aska16SkinMatricesBase15s_sizeToAlignToE_02cc1398;
  return ((lVar2 + param_2 * 8) - 1U & -lVar2) + lVar1 +
         (lVar2 + param_2 * 0x30 + 0x7fffffffffffffffU & -lVar2) * 2;
}

// ==== Aska::SkinMatrices::Assign(unsigned long, unsigned long, unsigned long)
// vaddr 0x21d53e0 | ghidra 0x22d53e0 | size 104 | symbol _ZN4Aska12SkinMatrices6AssignEmmm | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska12SkinMatrices6AssignEmmm(long param_1)

{
  long lVar1;
  long lVar2;
  long lVar3;
  ulong uVar4;
  ulong uVar5;
  long lVar6;
  
  lVar2 = Aska::SkinMatricesBase::Assign(unsigned long, unsigned long, unsigned long)();
  lVar3 = 0;
  if (lVar2 != 0) {
    lVar6 = *(long *)PTR__ZN4Aska16SkinMatricesBase15s_sizeToAlignToE_02cc1398 + -1;
    uVar4 = -*(long *)PTR__ZN4Aska16SkinMatricesBase15s_sizeToAlignToE_02cc1398;
    uVar5 = lVar6 + (ulong)*(ushort *)(param_1 + 8) * 0x30 & uVar4;
    lVar3 = lVar2 + (lVar6 + (ulong)*(ushort *)(param_1 + 8) * 8 & uVar4);
    lVar1 = lVar3 + uVar5;
    *(long *)(param_1 + 0x80) = lVar2;
    *(ulong *)(param_1 + 0x88) = lVar6 + lVar3 & uVar4;
    lVar3 = lVar1 + uVar5;
    *(ulong *)(param_1 + 0x90) = lVar6 + lVar1 & uVar4;
  }
  return lVar3;
}

// ==== Aska::SkinMatrices::InitPalette_(Aska::AofObject*, Aska::AsfHandler*)
// vaddr 0x21d5448 | ghidra 0x22d5448 | size 324 | symbol _ZN4Aska12SkinMatrices12InitPalette_EPNS_9AofObjectEPNS_10AsfHandlerE | lib libSOA-3.7.0.so | 2026-10-04
undefined4
_ZN4Aska12SkinMatrices12InitPalette_EPNS_9AofObjectEPNS_10AsfHandlerE
          (long param_1,long *param_2,long param_3)

{
  bool bVar1;
  ulong uVar2;
  undefined8 uVar3;
  undefined8 *puVar4;
  long lVar5;
  long lVar6;
  long lVar7;
  undefined8 uStack_80;
  undefined8 uStack_78;
  undefined8 uStack_70;
  undefined8 uStack_68;
  undefined8 uStack_60;
  undefined8 uStack_58;
  undefined8 uStack_50;
  undefined8 uStack_48;
  
  if (param_3 != 0) {
    *(long *)(param_1 + 0x78) = param_3;
    uVar2 = Aska::SkinMatricesBase::Init(Aska::AofObject*)(param_1,param_2);
    if ((uVar2 & 1) != 0) {
      if ((*(byte *)(param_2 + 0x25) & 1) != 0) {
        (**(code **)(*param_2 + 0xa8))(param_2);
      }
      uVar3 = (**(code **)(*param_2 + 0x98))(param_2);
      if (*(short *)(param_1 + 8) == 0) {
        bVar1 = true;
      }
      else {
        lVar5 = 0;
        lVar6 = 0;
        lVar7 = 0;
        do {
          puVar4 = (undefined8 *)
                   Aska::AsfHandler::GetInverseBindPose(int, Aska::IAnimatable**) const(*(undefined8 *)(param_1 + 0x78),
                                   (long)*(short *)(*(long *)(param_1 + 0x48) + lVar7 * 2),
                                   *(long *)(param_1 + 0x80) + lVar6);
          uStack_78 = puVar4[1];
          uStack_80 = *puVar4;
          uStack_68 = puVar4[3];
          uStack_70 = puVar4[2];
          uStack_58 = puVar4[5];
          uStack_60 = puVar4[4];
          uStack_48 = puVar4[7];
          uStack_50 = puVar4[6];
          Aska::Matrix34::Mul(Aska::Matrix34 const*, Aska::Matrix34 const*)(*(long *)(param_1 + 0x88) + lVar5,&uStack_80,uVar3);
          lVar7 = lVar7 + 1;
          lVar6 = lVar6 + 8;
          lVar5 = lVar5 + 0x30;
        } while (lVar7 < (long)(ulong)*(ushort *)(param_1 + 8));
        bVar1 = *(ushort *)(param_1 + 8) == 0;
      }
      if (param_2[0x30] == 0) {
        return 1;
      }
      if (bVar1) {
        return 1;
      }
      lVar7 = 0;
      do {
        Aska::AsfHandler::EnableSimpleDynamics(int, bool)(*(undefined8 *)(param_1 + 0x78),
                        (long)*(short *)(*(long *)(param_1 + 0x48) + lVar7 * 2),1);
        lVar7 = lVar7 + 1;
      } while (lVar7 < (long)(ulong)*(ushort *)(param_1 + 8));
      return 1;
    }
  }
  return 0;
}

// ==== Aska::SkinMatrices::InitPaletteEx_(Aska::AofObject*, Aska::AsfHandler*)
// vaddr 0x21d558c | ghidra 0x22d558c | size 212 | symbol _ZN4Aska12SkinMatrices14InitPaletteEx_EPNS_9AofObjectEPNS_10AsfHandlerE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska12SkinMatrices14InitPaletteEx_EPNS_9AofObjectEPNS_10AsfHandlerE
               (long param_1,long *param_2)

{
  short sVar1;
  undefined8 uVar2;
  undefined8 *puVar3;
  ulong uVar4;
  long lVar5;
  long lVar6;
  long lVar7;
  undefined8 uStack_70;
  undefined8 uStack_68;
  undefined8 uStack_60;
  undefined8 uStack_58;
  undefined8 uStack_50;
  undefined8 uStack_48;
  undefined8 uStack_40;
  undefined8 uStack_38;
  
  if ((*(byte *)(param_2 + 0x25) & 1) != 0) {
    (**(code **)(*param_2 + 0xa8))(param_2);
  }
  uVar2 = (**(code **)(*param_2 + 0x98))(param_2);
  uVar4 = (ulong)*(ushort *)(param_1 + 8);
  if (*(ushort *)(param_1 + 8) != 0) {
    lVar5 = 0;
    lVar6 = 0;
    lVar7 = 0;
    do {
      sVar1 = *(short *)(*(long *)(param_1 + 0x48) + lVar7 * 2);
      if (sVar1 < 0) {
        puVar3 = (undefined8 *)
                 Aska::AsfHandler::GetInverseBindPose(int, Aska::IAnimatable**) const(*(undefined8 *)(param_1 + 0x78),(long)sVar1,
                                 *(long *)(param_1 + 0x80) + lVar6);
        uStack_68 = puVar3[1];
        uStack_70 = *puVar3;
        uStack_58 = puVar3[3];
        uStack_60 = puVar3[2];
        uStack_48 = puVar3[5];
        uStack_50 = puVar3[4];
        uStack_38 = puVar3[7];
        uStack_40 = puVar3[6];
        Aska::Matrix34::Mul(Aska::Matrix34 const*, Aska::Matrix34 const*)(*(long *)(param_1 + 0x88) + lVar5,&uStack_70,uVar2);
        uVar4 = (ulong)*(ushort *)(param_1 + 8);
      }
      lVar7 = lVar7 + 1;
      lVar6 = lVar6 + 8;
      lVar5 = lVar5 + 0x30;
    } while (lVar7 < (long)uVar4);
  }
  return;
}

// ==== Aska::SkinMatrices::GetTexturePaletteMatrices() const
// vaddr 0x21d5660 | ghidra 0x22d5660 | size 8 | symbol _ZNK4Aska12SkinMatrices25GetTexturePaletteMatricesEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska12SkinMatrices25GetTexturePaletteMatricesEv(long param_1)

{
  return *(undefined8 *)(param_1 + 0x90);
}

// ==== Aska::SkinMatrices::GetBoneObject(unsigned int) const
// vaddr 0x21d5668 | ghidra 0x22d5668 | size 32 | symbol _ZNK4Aska12SkinMatrices13GetBoneObjectEj | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska12SkinMatrices13GetBoneObjectEj(long param_1,uint param_2)

{
  if (*(ushort *)(param_1 + 8) < param_2) {
    return 0;
  }
  return *(undefined8 *)(*(long *)(param_1 + 0x80) + (ulong)param_2 * 8);
}

// ==== Aska::SkinMatrices::MakeSkinMatrices()
// vaddr 0x21d5688 | ghidra 0x22d5688 | size 892 | symbol _ZN4Aska12SkinMatrices16MakeSkinMatricesEv | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 _ZN4Aska12SkinMatrices16MakeSkinMatricesEv(long param_1)

{
  undefined4 *puVar1;
  uint uVar2;
  ushort uVar3;
  undefined8 uVar4;
  byte bVar5;
  undefined8 *puVar6;
  long lVar7;
  int iVar8;
  long *plVar9;
  long lVar10;
  ulong uVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  float fVar19;
  long lVar20;
  float fVar21;
  float fVar22;
  float fVar23;
  float fVar24;
  float fVar25;
  float fVar26;
  long lVar27;
  float fVar28;
  float fVar29;
  float fVar30;
  float fVar31;
  float fVar32;
  float fVar33;
  float fVar34;
  long lVar35;
  float fVar36;
  float fVar37;
  float fVar38;
  float fVar39;
  float fVar40;
  float fVar41;
  long lVar42;
  float fVar43;
  float fVar44;
  float fVar45;
  float fVar46;
  float fVar47;
  float fVar48;
  float fVar49;
  float fVar50;
  float fVar51;
  float fVar52;
  float fVar53;
  float fVar54;
  float fVar55;
  float fVar56;
  float fVar57;
  float fVar58;
  float fVar59;
  float fVar60;
  float fVar61;
  float fVar62;
  float fVar63;
  
  if ((*(long *)(param_1 + 0x78) == 0) || (*(int *)(*(long *)(param_1 + 0x78) + 0xb0) < 2)) {
    uVar4 = 0;
  }
  else {
    plVar9 = *(long **)(param_1 + 0x70);
    bVar5 = *(byte *)(plVar9 + 0x25);
    if ((bVar5 & 1) != 0) {
      (**(code **)(*plVar9 + 0xa8))(plVar9);
      plVar9 = *(long **)(param_1 + 0x70);
      bVar5 = *(byte *)(plVar9 + 0x25);
    }
    lVar7 = _UNK_027dbb38;
    lVar10 = _UNK_027dbb30;
    if ((bVar5 >> 2 & 1) == 0) {
      if ((*(byte *)((long)plVar9 + 0x129) & 3) == 0) {
        fVar31 = *(float *)((long)plVar9 + 0x4c);
        fVar54 = *(float *)((long)plVar9 + 0x5c);
        fVar59 = *(float *)((long)plVar9 + 0x6c);
        plVar9[0x27] = CONCAT44((int)plVar9[0xe],*(float *)(plVar9 + 0xc));
        plVar9[0x26] = CONCAT44(*(float *)(plVar9 + 10),*(float *)(plVar9 + 8));
        plVar9[0x29] = CONCAT44(*(undefined4 *)((long)plVar9 + 0x74),*(float *)((long)plVar9 + 100))
        ;
        plVar9[0x28] = CONCAT44(*(float *)((long)plVar9 + 0x54),*(float *)((long)plVar9 + 0x44));
        *(float *)((long)plVar9 + 0x13c) =
             -(*(float *)(plVar9 + 8) * fVar31 + *(float *)(plVar9 + 10) * fVar54 +
              *(float *)(plVar9 + 0xc) * fVar59);
        *(float *)((long)plVar9 + 0x14c) =
             -(fVar31 * *(float *)((long)plVar9 + 0x44) + fVar54 * *(float *)((long)plVar9 + 0x54) +
              fVar59 * *(float *)((long)plVar9 + 100));
        plVar9[0x2b] = CONCAT44((int)plVar9[0xf],*(float *)(plVar9 + 0xd));
        plVar9[0x2a] = CONCAT44(*(float *)(plVar9 + 0xb),*(float *)(plVar9 + 9));
        plVar9[0x2d] = lVar7;
        plVar9[0x2c] = lVar10;
        *(float *)((long)plVar9 + 0x15c) =
             -(fVar31 * *(float *)(plVar9 + 9) + fVar54 * *(float *)(plVar9 + 0xb) +
              fVar59 * *(float *)(plVar9 + 0xd));
      }
      else {
        Aska::Matrix::InvertLowError(Aska::Matrix*) const(plVar9 + 8,plVar9 + 0x26);
        bVar5 = *(byte *)(plVar9 + 0x25);
      }
      *(byte *)(plVar9 + 0x25) = bVar5 | 4;
      plVar9 = *(long **)(param_1 + 0x70);
    }
    uVar3 = *(ushort *)(param_1 + 8);
    lVar42 = plVar9[0x27];
    lVar35 = plVar9[0x26];
    lVar27 = plVar9[0x29];
    lVar20 = plVar9[0x28];
    lVar7 = plVar9[0x2b];
    lVar10 = plVar9[0x2a];
    puVar6 = (undefined8 *)(*(long *)(param_1 + 0x90) + 0x7fU & 0xffffffffffffff80);
    uVar2 = ((int)*(long *)(param_1 + 0x90) + (uint)uVar3 * 0x30) - (int)puVar6 & 0xffffff80;
    if (0 < (int)uVar2) {
      uVar2 = uVar2 >> 5;
      Hint_Prefetch(puVar6,2,2,0);
      if (uVar2 != 0) {
        iVar8 = -uVar2;
        do {
          Hint_Prefetch(puVar6 + 4,2,2,0);
          iVar8 = iVar8 + 1;
          puVar6[1] = 0;
          *puVar6 = 0;
          puVar6[3] = 0;
          puVar6[2] = 0;
          puVar6 = puVar6 + 4;
        } while (iVar8 != 0);
      }
    }
    if (uVar3 != 0) {
      fVar32 = (float)lVar35;
      fVar36 = (float)((ulong)lVar35 >> 0x20);
      fVar39 = (float)lVar42;
      fVar43 = (float)((ulong)lVar42 >> 0x20);
      fVar17 = (float)lVar20;
      fVar21 = (float)((ulong)lVar20 >> 0x20);
      fVar24 = (float)lVar27;
      fVar28 = (float)((ulong)lVar27 >> 0x20);
      fVar31 = (float)lVar10;
      fVar54 = (float)((ulong)lVar10 >> 0x20);
      fVar59 = (float)lVar7;
      fVar15 = (float)((ulong)lVar7 >> 0x20);
      lVar10 = 0;
      uVar11 = 0;
      fVar60 = (float)_UNK_027dbb30;
      fVar61 = (float)((ulong)_UNK_027dbb30 >> 0x20);
      fVar62 = (float)_UNK_027dbb38;
      fVar63 = (float)((ulong)_UNK_027dbb38 >> 0x20);
      do {
        lVar7 = *(long *)(param_1 + 0x88);
        Hint_Prefetch(lVar7 + lVar10 + 0x50,0,2,0);
        plVar9 = *(long **)(*(long *)(param_1 + 0x80) + uVar11 * 8);
        uVar11 = uVar11 + 1;
        if (plVar9 == (long *)0x0) {
          puVar1 = (undefined4 *)(*(long *)(param_1 + 0x90) + lVar10);
          *puVar1 = 0x3f800000;
          *(undefined8 *)(puVar1 + 3) = 0;
          *(undefined8 *)(puVar1 + 1) = 0;
          puVar1[5] = 0x3f800000;
          *(undefined8 *)(puVar1 + 6) = 0;
          *(undefined8 *)(puVar1 + 8) = 0;
          *(undefined8 *)(puVar1 + 10) = 0x3f800000;
        }
        else {
          if ((*(byte *)(plVar9 + 0x25) & 1) != 0) {
            (**(code **)(*plVar9 + 0xa8))(plVar9);
            lVar7 = *(long *)(param_1 + 0x88);
          }
          puVar6 = (undefined8 *)(lVar7 + lVar10);
          fVar12 = (float)plVar9[8];
          fVar13 = (float)((ulong)plVar9[8] >> 0x20);
          fVar14 = (float)plVar9[9];
          fVar16 = (float)((ulong)plVar9[9] >> 0x20);
          fVar18 = (float)plVar9[10];
          fVar22 = (float)((ulong)plVar9[10] >> 0x20);
          fVar25 = (float)plVar9[0xb];
          fVar29 = (float)((ulong)plVar9[0xb] >> 0x20);
          fVar33 = (float)plVar9[0xc];
          fVar37 = (float)((ulong)plVar9[0xc] >> 0x20);
          fVar40 = (float)plVar9[0xd];
          fVar44 = (float)((ulong)plVar9[0xd] >> 0x20);
          fVar34 = fVar43 * fVar60 + fVar32 * fVar12 + fVar36 * fVar18 + fVar39 * fVar33;
          fVar38 = fVar43 * fVar61 + fVar32 * fVar13 + fVar36 * fVar22 + fVar39 * fVar37;
          fVar41 = fVar43 * fVar62 + fVar32 * fVar14 + fVar36 * fVar25 + fVar39 * fVar40;
          fVar45 = fVar43 * fVar63 + fVar32 * fVar16 + fVar36 * fVar29 + fVar39 * fVar44;
          fVar19 = fVar28 * fVar60 + fVar17 * fVar12 + fVar21 * fVar18 + fVar24 * fVar33;
          fVar23 = fVar28 * fVar61 + fVar17 * fVar13 + fVar21 * fVar22 + fVar24 * fVar37;
          fVar26 = fVar28 * fVar62 + fVar17 * fVar14 + fVar21 * fVar25 + fVar24 * fVar40;
          fVar30 = fVar28 * fVar63 + fVar17 * fVar16 + fVar21 * fVar29 + fVar24 * fVar44;
          fVar46 = (float)*puVar6;
          fVar47 = (float)((ulong)*puVar6 >> 0x20);
          fVar48 = (float)puVar6[1];
          fVar49 = (float)((ulong)puVar6[1] >> 0x20);
          fVar50 = (float)puVar6[2];
          fVar51 = (float)((ulong)puVar6[2] >> 0x20);
          fVar52 = (float)puVar6[3];
          fVar53 = (float)((ulong)puVar6[3] >> 0x20);
          fVar55 = (float)puVar6[4];
          fVar56 = (float)((ulong)puVar6[4] >> 0x20);
          fVar57 = (float)puVar6[5];
          fVar58 = (float)((ulong)puVar6[5] >> 0x20);
          puVar6 = (undefined8 *)(*(long *)(param_1 + 0x90) + lVar10);
          puVar6[1] = CONCAT44(fVar63 * fVar45 + fVar58 * fVar41 + fVar49 * fVar34 + fVar53 * fVar38
                               ,fVar62 * fVar45 +
                                fVar57 * fVar41 + fVar48 * fVar34 + fVar52 * fVar38);
          *puVar6 = CONCAT44(fVar61 * fVar45 + fVar56 * fVar41 + fVar47 * fVar34 + fVar51 * fVar38,
                             fVar60 * fVar45 + fVar55 * fVar41 + fVar46 * fVar34 + fVar50 * fVar38);
          lVar7 = *(long *)(param_1 + 0x90) + lVar10;
          *(ulong *)(lVar7 + 0x18) =
               CONCAT44(fVar63 * fVar30 + fVar58 * fVar26 + fVar49 * fVar19 + fVar53 * fVar23,
                        fVar62 * fVar30 + fVar57 * fVar26 + fVar48 * fVar19 + fVar52 * fVar23);
          *(ulong *)(lVar7 + 0x10) =
               CONCAT44(fVar61 * fVar30 + fVar56 * fVar26 + fVar47 * fVar19 + fVar51 * fVar23,
                        fVar60 * fVar30 + fVar55 * fVar26 + fVar46 * fVar19 + fVar50 * fVar23);
          fVar12 = fVar15 * fVar60 + fVar31 * fVar12 + fVar54 * fVar18 + fVar59 * fVar33;
          fVar13 = fVar15 * fVar61 + fVar31 * fVar13 + fVar54 * fVar22 + fVar59 * fVar37;
          fVar14 = fVar15 * fVar62 + fVar31 * fVar14 + fVar54 * fVar25 + fVar59 * fVar40;
          fVar16 = fVar15 * fVar63 + fVar31 * fVar16 + fVar54 * fVar29 + fVar59 * fVar44;
          lVar7 = *(long *)(param_1 + 0x90) + lVar10;
          *(ulong *)(lVar7 + 0x28) =
               CONCAT44(fVar63 * fVar16 + fVar58 * fVar14 + fVar49 * fVar12 + fVar53 * fVar13,
                        fVar62 * fVar16 + fVar57 * fVar14 + fVar48 * fVar12 + fVar52 * fVar13);
          *(ulong *)(lVar7 + 0x20) =
               CONCAT44(fVar61 * fVar16 + fVar56 * fVar14 + fVar47 * fVar12 + fVar51 * fVar13,
                        fVar60 * fVar16 + fVar55 * fVar14 + fVar46 * fVar12 + fVar50 * fVar13);
        }
        lVar10 = lVar10 + 0x30;
      } while (uVar3 != uVar11);
    }
    Aska::SkinMatricesBase::KickPalette(Aska::Matrix34*)(param_1,*(undefined8 *)(param_1 + 0x90));
    uVar4 = 1;
  }
  return uVar4;
}

// ==== Aska::SkinMatrices::UpdateSimpleDynamics(Aska::AFF::SimpleDynamicsParameters const*)
// vaddr 0x21d5a04 | ghidra 0x22d5a04 | size 1012 | symbol _ZN4Aska12SkinMatrices20UpdateSimpleDynamicsEPKNS_3AFF24SimpleDynamicsParametersE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska12SkinMatrices20UpdateSimpleDynamicsEPKNS_3AFF24SimpleDynamicsParametersE
               (long param_1,undefined8 param_2)

{
  undefined4 *puVar1;
  undefined8 *puVar2;
  byte bVar3;
  ushort uVar4;
  short sVar5;
  int iVar6;
  undefined *puVar7;
  long lVar8;
  long lVar9;
  undefined8 uVar10;
  undefined4 *puVar11;
  ushort *puVar12;
  uint uVar13;
  ulong uVar14;
  long lVar15;
  long *plVar16;
  ulong uVar17;
  uint uVar18;
  long lVar19;
  undefined8 uStack_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined8 uStack_98;
  undefined1 auStack_90 [64];
  
  if (*(short *)(param_1 + 8) == 0) {
    bVar3 = *(byte *)(param_1 + 10);
  }
  else {
    lVar15 = 0;
    do {
      lVar8 = *(long *)(param_1 + 0x78);
      if (0 < *(int *)(lVar8 + 0xb0)) {
        sVar5 = *(short *)(*(long *)(param_1 + 0x48) + lVar15 * 2);
        if (sVar5 < 0) {
          if ((*(long *)(lVar8 + 0x78) == 0) || (*(long *)(lVar8 + 0x508) == 0))
          goto code_r0x022d5a98;
          lVar8 = Aska::AsfHandler::QuickSearchExternalLinkByName(char const*) const(lVar8,*(long *)(lVar8 + 0x78) +
                                        (long)(int)((int)sVar5 << 5 ^ 0xffffffe0) + 0x20);
        }
        else {
          lVar8 = *(long *)(*(long *)(*(long *)(lVar8 + 0xd8) + (long)(int)sVar5 * 8) + 0x38);
        }
        if (lVar8 != 0) {
          *(byte *)(lVar8 + 0x128) = *(byte *)(lVar8 + 0x128) & 0xfd;
        }
      }
code_r0x022d5a98:
      puVar7 = PTR__ZN4Aska6Vector10zeroVectorE_02cc0768;
      lVar15 = lVar15 + 1;
    } while (lVar15 < (long)(ulong)*(ushort *)(param_1 + 8));
    lVar15 = *(long *)(param_1 + 0x70);
    if (*(ushort *)(param_1 + 8) != 0) {
      lVar19 = 0;
      lVar8 = 0;
      do {
        lVar9 = *(long *)(param_1 + 0x78);
        if (0 < *(int *)(lVar9 + 0xb0)) {
          sVar5 = *(short *)(*(long *)(param_1 + 0x48) + lVar19);
          if (sVar5 < 0) {
            if ((*(long *)(lVar9 + 0x78) == 0) || (*(long *)(lVar9 + 0x508) == 0))
            goto code_r0x022d5bec;
            plVar16 = (long *)Aska::AsfHandler::QuickSearchExternalLinkByName(char const*) const(lVar9,*(long *)(lVar9 + 0x78) +
                                                    (long)(int)((int)sVar5 << 5 ^ 0xffffffe0) + 0x20
                                             );
          }
          else {
            plVar16 = *(long **)(*(long *)(*(long *)(lVar9 + 0xd8) + (long)(int)sVar5 * 8) + 0x38);
          }
          if ((plVar16 != (long *)0x0) && ((*(byte *)(plVar16 + 0x25) >> 1 & 1) == 0)) {
            Aska::HierarchicalObject::UpdateSimpleDynamics(Aska::AFF::SimpleDynamicsParameters const*)(plVar16,param_2);
            uVar10 = (**(code **)(*plVar16 + 0x98))(plVar16);
            Aska::Matrix::Mul(Aska::Matrix const*, Aska::Matrix const*)(auStack_90,lVar15 + 0x130,uVar10);
            lVar9 = plVar16[0x30];
            puVar2 = (undefined8 *)puVar7;
            if (lVar9 != 0) {
              puVar2 = (undefined8 *)(lVar9 + 0x70);
            }
            uStack_98 = puVar2[1];
            uStack_a0 = *puVar2;
            puVar2 = (undefined8 *)puVar7;
            if (lVar9 != 0) {
              puVar2 = (undefined8 *)(lVar9 + 0x80);
            }
            uStack_a8 = puVar2[1];
            uStack_b0 = *puVar2;
            Aska::Vector::ApplyMatrixNoTransport(Aska::Matrix const*)(&uStack_a0,auStack_90);
            Aska::Vector::ApplyMatrixNoTransport(Aska::Matrix const*)(&uStack_b0,auStack_90);
            puVar11 = (undefined4 *)(*(long *)(param_1 + 0x28) + (long)(int)lVar19 * 0x10);
            *puVar11 = (undefined4)uStack_a0;
            puVar11[1] = uStack_a0._4_4_;
            puVar11[2] = (undefined4)uStack_98;
            puVar11[3] = uStack_98._4_4_;
            puVar11 = (undefined4 *)(*(long *)(param_1 + 0x28) + (long)((int)lVar19 + 1) * 0x10);
            *puVar11 = (undefined4)uStack_b0;
            puVar11[1] = uStack_b0._4_4_;
            puVar11[2] = (undefined4)uStack_a8;
            puVar11[3] = uStack_a8._4_4_;
          }
        }
code_r0x022d5bec:
        lVar8 = lVar8 + 1;
        lVar19 = lVar19 + 2;
      } while (lVar8 < (long)(ulong)*(ushort *)(param_1 + 8));
    }
    bVar3 = *(byte *)(param_1 + 10);
  }
  if ((bVar3 >> 1 & 1) == 0) {
    lVar8 = *(long *)(*(long *)(param_1 + 0x70) + 0x3d8);
    lVar15 = *(long *)(lVar8 + 0xd0);
    if ((lVar15 != 0) && (uVar17 = (ulong)*(ushort *)(*(long *)(lVar8 + 0xb0) + 0x70), uVar17 != 0))
    {
      uVar14 = 0;
      while( true ) {
        plVar16 = *(long **)(lVar15 + uVar14 * 8);
        if ((*(char *)(*plVar16 + 0x1a) == -1) &&
           (uVar18 = (uint)*(byte *)(plVar16[1] + 0x19), *(byte *)(plVar16[1] + 0x19) != 0)) {
          lVar15 = plVar16[4];
          puVar11 = (undefined4 *)Aska::SkinMatricesBase::GetVelocityArrayBack(int) const(param_1,uVar14 & 0xffffffff);
          puVar12 = (ushort *)(lVar15 + 0x10);
          do {
            uVar4 = *puVar12;
            uVar18 = uVar18 - 1;
            puVar1 = (undefined4 *)(*(long *)(param_1 + 0x28) + (ulong)uVar4 * 0x20);
            *puVar11 = *puVar1;
            puVar11[1] = puVar1[1];
            puVar11[2] = puVar1[2];
            puVar11[3] = puVar1[3];
            puVar1 = (undefined4 *)
                     (*(long *)(param_1 + 0x28) + (ulong)((uint)uVar4 << 1 | 1) * 0x10);
            puVar11[4] = *puVar1;
            puVar11[5] = puVar1[1];
            puVar11[6] = puVar1[2];
            puVar11[7] = puVar1[3];
            puVar11 = puVar11 + 8;
            puVar12 = puVar12 + 1;
          } while (uVar18 != 0);
        }
        uVar14 = uVar14 + 1;
        if ((long)uVar17 <= (long)uVar14) break;
        lVar15 = *(long *)(lVar8 + 0xd0);
      }
    }
  }
  else {
    lVar15 = Aska::Texture::GetBody() const(*(undefined8 *)
                              (param_1 + (ulong)(*(byte *)(param_1 + 0xb) ^ 1) * 8 + 0x50));
    lVar8 = *(long *)(*(long *)(param_1 + 0x70) + 0x3d8);
    lVar19 = *(long *)(lVar8 + 0xd0);
    if ((lVar19 != 0) && (uVar17 = (ulong)*(ushort *)(*(long *)(lVar8 + 0xb0) + 0x70), uVar17 != 0))
    {
      lVar9 = 0;
      iVar6 = *(int *)(param_1 + 0x6c) * 0x10;
      while( true ) {
        plVar16 = *(long **)(lVar19 + lVar9 * 8);
        if ((*(char *)(*plVar16 + 0x1a) == -1) &&
           (uVar18 = (uint)*(byte *)(plVar16[1] + 0x19), *(byte *)(plVar16[1] + 0x19) != 0)) {
          uVar13 = iVar6 * (uint)*(ushort *)(*(long *)(param_1 + 0x40) + lVar9 * 2);
          puVar12 = (ushort *)(plVar16[4] + 0x10);
          do {
            uVar4 = *puVar12;
            puVar11 = (undefined4 *)(lVar15 + 0x30 + (ulong)uVar13);
            uVar18 = uVar18 - 1;
            uVar13 = uVar13 + iVar6;
            puVar1 = (undefined4 *)(*(long *)(param_1 + 0x28) + (ulong)uVar4 * 0x20);
            *puVar11 = *puVar1;
            puVar11[1] = puVar1[1];
            puVar11[2] = puVar1[2];
            puVar11[3] = puVar1[3];
            puVar1 = (undefined4 *)
                     (*(long *)(param_1 + 0x28) + (ulong)((uint)uVar4 << 1 | 1) * 0x10);
            puVar11[4] = *puVar1;
            puVar11[5] = puVar1[1];
            puVar11[6] = puVar1[2];
            puVar11[7] = puVar1[3];
            puVar12 = puVar12 + 1;
          } while (uVar18 != 0);
        }
        lVar9 = lVar9 + 1;
        if ((long)uVar17 <= lVar9) break;
        lVar19 = *(long *)(lVar8 + 0xd0);
      }
    }
  }
  return;
}

// ==== Aska::SkinMatricesBase::SkinMatricesBase()
// vaddr 0x21d5df8 | ghidra 0x22d5df8 | size 64 | symbol _ZN4Aska16SkinMatricesBaseC2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16SkinMatricesBaseC2Ev(long *param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZTVN4Aska16SkinMatricesBaseE_02cb7df0;
  *(undefined2 *)(param_1 + 1) = 0;
  *(undefined1 *)((long)param_1 + 0xb) = 0;
  *param_1 = (long)(puVar1 + 0x10);
  *(byte *)((long)param_1 + 10) = *(byte *)((long)param_1 + 10) & 0xf8;
  memset(param_1 + 2,0,0x68);
  return;
}

// ==== Aska::SkinMatricesBase::~SkinMatricesBase()
// vaddr 0x21d5e38 | ghidra 0x22d5e38 | size 236 | symbol _ZN4Aska16SkinMatricesBaseD2Ev | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Possible PIC construction at 0x022d5eac: Changing call to branch */
/* WARNING: Possible PIC construction at 0x022d5ed8: Changing call to branch */

void _ZN4Aska16SkinMatricesBaseD1Ev(long *param_1)

{
  long lVar1;
  undefined *puVar2;
  long lVar3;
  undefined8 uVar4;
  
  *param_1 = (long)(PTR__ZTVN4Aska16SkinMatricesBaseE_02cb7df0 + 0x10);
  if (param_1[2] != 0) {
    operator delete[](void*)();
    param_1[2] = 0;
  }
  puVar2 = PTR__ZN4Aska6Global17m_pTextureManagerE_02cc19f0;
  *(byte *)((long)param_1 + 10) = *(byte *)((long)param_1 + 10) & 0xfe;
  lVar3 = *(long *)puVar2;
  lVar1 = lVar3 + 0xb0;
  if ((undefined8 *)param_1[10] == (undefined8 *)0x0) {
    if ((undefined8 *)param_1[0xb] == (undefined8 *)0x0) {
      if ((undefined8 *)param_1[0xc] == (undefined8 *)0x0) {
        return;
      }
      uVar4 = *(undefined8 *)param_1[0xc];
      Aska::CriticalSection::Enter() const(lVar1);
      Aska::TextureManager::DeleteTextureEx(unsigned long, unsigned char)(lVar3,uVar4,0xff);
    }
    else {
      uVar4 = *(undefined8 *)param_1[0xb];
      Aska::CriticalSection::Enter() const(lVar1);
      Aska::TextureManager::DeleteTextureEx(unsigned long, unsigned char)(lVar3,uVar4,0xff);
    }
  }
  else {
    uVar4 = *(undefined8 *)param_1[10];
    Aska::CriticalSection::Enter() const(lVar1);
    Aska::TextureManager::DeleteTextureEx(unsigned long, unsigned char)(lVar3,uVar4,0xff);
  }
  (*(code *)PTR__ZNK4Aska15CriticalSection5LeaveEv_02ca8d00)(lVar1);
  return;
}

// ==== Aska::SkinMatricesBase::~SkinMatricesBase()
// vaddr 0x21d5f24 | ghidra 0x22d5f24 | size 4 | symbol _ZN4Aska16SkinMatricesBaseD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16SkinMatricesBaseD0Ev(void)

{
  code *pcVar1;
  
                    /* WARNING: Does not return */
  pcVar1 = (code *)SoftwareBreakpoint(1,0x22d5f28);
  (*pcVar1)();
}

// ==== Aska::SkinMatricesBase::InitPalette_(Aska::AofObject*, Aska::AsfHandler*)
// vaddr 0x21d5f28 | ghidra 0x22d5f28 | size 8 | symbol _ZN4Aska16SkinMatricesBase12InitPalette_EPNS_9AofObjectEPNS_10AsfHandlerE | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska16SkinMatricesBase12InitPalette_EPNS_9AofObjectEPNS_10AsfHandlerE(void)

{
  return 0;
}

// ==== Aska::SkinMatricesBase::InitPalette(Aska::AofObject*, Aska::AsfHandler*)
// vaddr 0x21d5f30 | ghidra 0x22d5f30 | size 24 | symbol _ZN4Aska16SkinMatricesBase11InitPaletteEPNS_9AofObjectEPNS_10AsfHandlerE | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska16SkinMatricesBase11InitPaletteEPNS_9AofObjectEPNS_10AsfHandlerE
          (long *param_1,undefined8 param_2,long param_3)

{
  undefined8 uVar1;
  
  if (param_3 != 0) {
                    /* WARNING: Could not recover jumptable at 0x022d5f3c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = (**(code **)(*param_1 + 0x30))();
    return uVar1;
  }
  return 0;
}

// ==== Aska::SkinMatricesBase::InitPalette_(Aska::AofObject*, Aska::DirectAofPrimitiveBase*)
// vaddr 0x21d5f48 | ghidra 0x22d5f48 | size 8 | symbol _ZN4Aska16SkinMatricesBase12InitPalette_EPNS_9AofObjectEPNS_22DirectAofPrimitiveBaseE | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska16SkinMatricesBase12InitPalette_EPNS_9AofObjectEPNS_22DirectAofPrimitiveBaseE(void)

{
  return 0;
}

// ==== Aska::SkinMatricesBase::InitPalette(Aska::AofObject*, Aska::DirectAofPrimitiveBase*)
// vaddr 0x21d5f50 | ghidra 0x22d5f50 | size 24 | symbol _ZN4Aska16SkinMatricesBase11InitPaletteEPNS_9AofObjectEPNS_22DirectAofPrimitiveBaseE | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska16SkinMatricesBase11InitPaletteEPNS_9AofObjectEPNS_22DirectAofPrimitiveBaseE
          (long *param_1,undefined8 param_2,long param_3)

{
  undefined8 uVar1;
  
  if (param_3 != 0) {
                    /* WARNING: Could not recover jumptable at 0x022d5f5c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = (**(code **)(*param_1 + 0x38))();
    return uVar1;
  }
  return 0;
}

// ==== Aska::SkinMatricesBase::InitPaletteEx_(Aska::AofObject*, Aska::AsfHandler*)
// vaddr 0x21d5f68 | ghidra 0x22d5f68 | size 4 | symbol _ZN4Aska16SkinMatricesBase14InitPaletteEx_EPNS_9AofObjectEPNS_10AsfHandlerE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16SkinMatricesBase14InitPaletteEx_EPNS_9AofObjectEPNS_10AsfHandlerE(void)

{
  return;
}

// ==== Aska::SkinMatricesBase::InitPaletteEx(Aska::AofObject*, Aska::AsfHandler*)
// vaddr 0x21d5f6c | ghidra 0x22d5f6c | size 12 | symbol _ZN4Aska16SkinMatricesBase13InitPaletteExEPNS_9AofObjectEPNS_10AsfHandlerE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16SkinMatricesBase13InitPaletteExEPNS_9AofObjectEPNS_10AsfHandlerE(long *param_1)

{
                    /* WARNING: Could not recover jumptable at 0x022d5f74. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*param_1 + 0x40))();
  return;
}

// ==== Aska::SkinMatricesBase::UpdateSimpleDynamics(Aska::AFF::SimpleDynamicsParameters const*)
// vaddr 0x21d5f78 | ghidra 0x22d5f78 | size 4 | symbol _ZN4Aska16SkinMatricesBase20UpdateSimpleDynamicsEPKNS_3AFF24SimpleDynamicsParametersE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16SkinMatricesBase20UpdateSimpleDynamicsEPKNS_3AFF24SimpleDynamicsParametersE(void)

{
  return;
}

// ==== Aska::SkinMatricesBase::GetAllocSize(unsigned long, unsigned long, unsigned long) const
// vaddr 0x21d5f7c | ghidra 0x22d5f7c | size 80 | symbol _ZNK4Aska16SkinMatricesBase12GetAllocSizeEmmm | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZNK4Aska16SkinMatricesBase12GetAllocSizeEmmm
                (long param_1,long param_2,long param_3,long param_4)

{
  byte bVar1;
  ulong uVar2;
  
  bVar1 = *(byte *)(param_1 + 10);
  uVar2 = param_3 * 2 + 0xfU & 0xfffffffffffffff0;
  if ((bVar1 >> 2 & 1) != 0) {
    uVar2 = uVar2 + ((param_2 << 5 | 0x10U) - 1 & 0xffffffffffffffe0);
  }
  if (((bVar1 >> 1 & 1) == 0) && (uVar2 = uVar2 + param_4 * 0x60, (bVar1 >> 2 & 1) != 0)) {
    uVar2 = uVar2 + ((param_4 << 6 | 0x20U) - 2 & 0xffffffffffffffc0);
  }
  return uVar2;
}

// ==== Aska::SkinMatricesBase::Assign(unsigned long, unsigned long, unsigned long)
// vaddr 0x21d5fcc | ghidra 0x22d5fcc | size 244 | symbol _ZN4Aska16SkinMatricesBase6AssignEmmm | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska16SkinMatricesBase6AssignEmmm(long *param_1,long param_2,long param_3,long param_4)

{
  long lVar1;
  byte bVar2;
  long lVar3;
  ulong uVar4;
  
  lVar3 = (**(code **)(*param_1 + 0x48))();
  lVar3 = operator new[](unsigned long, unsigned long, bool)(lVar3 + 3U & 0xfffffffffffffffc,0x10,1);
  param_1[2] = lVar3;
  if (lVar3 != 0) {
    bVar2 = *(byte *)((long)param_1 + 10);
    param_1[8] = lVar3;
    lVar3 = lVar3 + (param_3 * 2 + 0xfU & 0xfffffffffffffff0);
    if ((bVar2 >> 1 & 1) == 0) {
      lVar1 = lVar3 + param_4 * 0x30;
      param_1[4] = lVar1 + 0xfU & 0xfffffffffffffff0;
      param_1[3] = lVar3 + 0xfU & 0xfffffffffffffff0;
      lVar3 = lVar1 + param_4 * 0x30;
    }
    else {
      param_1[3] = 0;
      param_1[4] = 0;
    }
    if ((bVar2 >> 2 & 1) != 0) {
      param_1[5] = lVar3;
      lVar3 = lVar3 + ((param_2 << 5 | 0x10U) - 1 & 0xffffffffffffffe0);
      if ((bVar2 >> 1 & 1) == 0) {
        uVar4 = (param_4 << 5 | 0x10U) - 1 & 0xffffffffffffffe0;
        lVar1 = lVar3 + uVar4;
        param_1[6] = lVar3;
        param_1[7] = lVar1;
        lVar3 = lVar1 + uVar4;
      }
      else {
        param_1[6] = 0;
        param_1[7] = 0;
      }
    }
  }
  return lVar3;
}

// ==== Aska::SkinMatricesBase::Init(Aska::AofObject*)
// vaddr 0x21d60c0 | ghidra 0x22d60c0 | size 424 | symbol _ZN4Aska16SkinMatricesBase4InitEPNS_9AofObjectE | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska16SkinMatricesBase4InitEPNS_9AofObjectE(long *param_1,long param_2)

{
  byte bVar1;
  ushort uVar2;
  byte bVar3;
  undefined8 uVar4;
  undefined2 uVar5;
  short sVar6;
  long lVar7;
  long lVar8;
  long lVar9;
  ulong uVar10;
  
  uVar4 = 0;
  if ((param_2 != 0) && ((*(byte *)((long)param_1 + 10) & 1) == 0)) {
    lVar9 = *(long *)(param_2 + 0x3d8);
    if (lVar9 == 0) {
      uVar4 = 0;
    }
    else {
      bVar3 = Aska::AofHandler::UsesTexturePaletteBySkinning() const(lVar9);
      bVar1 = *(byte *)((long)param_1 + 10);
      bVar3 = bVar1 & 1 | (bVar3 & 1) << 1;
      *(byte *)((long)param_1 + 10) = bVar1 & 0xfc | bVar3;
      if (*(long *)(lVar9 + 0xd0) == 0) {
        uVar5 = 0;
      }
      else {
        uVar5 = *(undefined2 *)(*(long *)(lVar9 + 0xb0) + 0x76);
      }
      *(undefined2 *)(param_1 + 1) = uVar5;
      lVar7 = *(long *)(param_2 + 0x180);
      param_1[0xe] = param_2;
      *(byte *)((long)param_1 + 10) = bVar1 & 0xf8 | bVar3 | (lVar7 != 0) << 2;
      if (*(long *)(lVar9 + 0xd0) == 0) {
        uVar10 = 0;
      }
      else {
        uVar10 = (ulong)*(ushort *)(*(long *)(lVar9 + 0xb0) + 0x70);
      }
      uVar2 = *(ushort *)(*(long *)(lVar9 + 0xb0) + 0x78);
      lVar7 = (**(code **)(*param_1 + 0x50))(param_1,uVar5,uVar10,uVar2);
      uVar4 = 0;
      if (lVar7 != 0) {
        if ((int)uVar10 != 0) {
          lVar7 = 0;
          sVar6 = 0;
          do {
            lVar8 = (long)*(char *)(**(long **)(*(long *)(lVar9 + 0xd0) + lVar7 * 8) + 0x1a);
            if (lVar8 == -1) {
              *(short *)(param_1[8] + lVar7 * 2) = sVar6;
              sVar6 = sVar6 + (ushort)*(byte *)(*(long *)(*(long *)(*(long *)(lVar9 + 0xd0) +
                                                                   lVar7 * 8) + 8) + 0x19);
            }
            else {
              *(undefined2 *)(param_1[8] + lVar7 * 2) = *(undefined2 *)(param_1[8] + lVar8 * 2);
            }
            lVar7 = lVar7 + 1;
          } while (lVar7 < (long)uVar10);
        }
        param_1[9] = *(long *)(lVar9 + 0xe0);
        if ((*(byte *)((long)param_1 + 10) >> 1 & 1) != 0) {
          *(uint *)(param_1 + 0xd) = (uint)uVar2;
          *(undefined4 *)((long)param_1 + 0x6c) = 5;
          lVar9 = Aska::SkinMatricesBase::AllocPaletteTexture_(int)(param_1,(uint)uVar2 * 5);
          if (lVar9 != 0) {
            param_1[10] = lVar9;
            lVar9 = Aska::SkinMatricesBase::AllocPaletteTexture_(int)(param_1,(uint)uVar2 * 5);
            if (lVar9 != 0) {
              param_1[0xb] = lVar9;
            }
          }
          if (((((*(byte *)(param_2 + 0x19b) >> 2 & 1) != 0) &&
               ((*(byte *)((long)param_1 + 10) >> 1 & 1) != 0)) && (param_1[0xc] == 0)) &&
             (lVar9 = Aska::SkinMatricesBase::AllocPaletteTexture_(int)(param_1,*(int *)((long)param_1 + 0x6c) * (int)param_1[0xd]),
             lVar9 != 0)) {
            param_1[0xc] = lVar9;
          }
        }
        uVar4 = 1;
        *(byte *)((long)param_1 + 10) = *(byte *)((long)param_1 + 10) | 1;
      }
    }
  }
  return uVar4;
}

// ==== Aska::SkinMatricesBase::InitTexturePalette_()
// vaddr 0x21d6268 | ghidra 0x22d6268 | size 84 | symbol _ZN4Aska16SkinMatricesBase19InitTexturePalette_Ev | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska16SkinMatricesBase19InitTexturePalette_Ev(long param_1)

{
  int iVar1;
  long lVar2;
  
  if ((*(byte *)(param_1 + 10) >> 1 & 1) != 0) {
    iVar1 = *(int *)(param_1 + 0x6c) * *(int *)(param_1 + 0x68);
    lVar2 = Aska::SkinMatricesBase::AllocPaletteTexture_(int)(param_1,iVar1);
    if (lVar2 == 0) {
      return 0;
    }
    *(long *)(param_1 + 0x50) = lVar2;
    lVar2 = Aska::SkinMatricesBase::AllocPaletteTexture_(int)(param_1,iVar1);
    if (lVar2 == 0) {
      return 0;
    }
    *(long *)(param_1 + 0x58) = lVar2;
  }
  return 1;
}

// ==== Aska::SkinMatricesBase::Init3rdTexturePalette()
// vaddr 0x21d62bc | ghidra 0x22d62bc | size 60 | symbol _ZN4Aska16SkinMatricesBase21Init3rdTexturePaletteEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska16SkinMatricesBase21Init3rdTexturePaletteEv(long param_1)

{
  long lVar1;
  
  if (((*(byte *)(param_1 + 10) >> 1 & 1) != 0) && (*(long *)(param_1 + 0x60) == 0)) {
    lVar1 = Aska::SkinMatricesBase::AllocPaletteTexture_(int)(param_1,*(int *)(param_1 + 0x6c) * *(int *)(param_1 + 0x68));
    if (lVar1 == 0) {
      return 0;
    }
    *(long *)(param_1 + 0x60) = lVar1;
  }
  return 1;
}

// ==== Aska::SkinMatricesBase::AllocPaletteTexture_(int)
// vaddr 0x21d62f8 | ghidra 0x22d62f8 | size 256 | symbol _ZN4Aska16SkinMatricesBase20AllocPaletteTexture_Ei | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska16SkinMatricesBase20AllocPaletteTexture_Ei(long param_1,int param_2)

{
  long lVar1;
  undefined8 uVar2;
  long lVar3;
  ulong uVar4;
  long alStack_40 [2];
  
  if ((*(byte *)(param_1 + 10) >> 1 & 1) != 0) {
    lVar3 = *(long *)PTR__ZN4Aska6Global17m_pTextureManagerE_02cc19f0;
    lVar1 = lVar3 + 0xb0;
    uVar4 = (ulong)(uint)(iRam0000000002ce6eec << 7) | 0x7074407400000000;
    iRam0000000002ce6eec = iRam0000000002ce6eec + 1;
    Aska::CriticalSection::Enter() const(lVar1);
    Aska::TextureManager::AllocTextureEx(unsigned long, int, int, int, int, int, void*, int, Aska::AFF::AifImage const**, bool)(alStack_40,lVar3,uVar4,param_2,1,0xf88099,0x40000,1,0,1,0,1);
    Aska::CriticalSection::Leave() const(lVar1);
    if (alStack_40[0] != 0) {
      Aska::CriticalSection::Enter() const(lVar1);
      lVar3 = Aska::TextureManager::QueryTextureEx(unsigned long, bool)(lVar3,uVar4,1);
      Aska::CriticalSection::Leave() const(lVar1);
      if (lVar3 == 0) {
        return 0;
      }
      uVar2 = Aska::Texture::GetBody() const(lVar3);
      memset(uVar2,0,(long)(param_2 << 4));
      return lVar3;
    }
  }
  return 0;
}

// ==== Aska::SkinMatricesBase::AllocUnmanagedPaletteTexture()
// vaddr 0x21d63f8 | ghidra 0x22d63f8 | size 28 | symbol _ZN4Aska16SkinMatricesBase28AllocUnmanagedPaletteTextureEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska16SkinMatricesBase28AllocUnmanagedPaletteTextureEv(long param_1)

{
  undefined8 uVar1;
  
  if ((*(byte *)(param_1 + 10) >> 1 & 1) == 0) {
    return 0;
  }
  uVar1 = (*(code *)PTR__ZN4Aska16SkinMatricesBase20AllocPaletteTexture_Ei_02ca4108)
                    (param_1,*(int *)(param_1 + 0x6c) * *(int *)(param_1 + 0x68));
  return uVar1;
}

// ==== Aska::SkinMatricesBase::GetSkinMatrixCount(int) const
// vaddr 0x21d6414 | ghidra 0x22d6414 | size 28 | symbol _ZNK4Aska16SkinMatricesBase18GetSkinMatrixCountEi | lib libSOA-3.7.0.so | 2026-10-04
undefined1 _ZNK4Aska16SkinMatricesBase18GetSkinMatrixCountEi(long param_1,int param_2)

{
  return *(undefined1 *)
          (*(long *)(*(long *)(*(long *)(*(long *)(*(long *)(param_1 + 0x70) + 0x3d8) + 0xd0) +
                              (long)param_2 * 8) + 8) + 0x19);
}

// ==== Aska::SkinMatricesBase::GetVelocityArray(int) const
// vaddr 0x21d6430 | ghidra 0x22d6430 | size 40 | symbol _ZNK4Aska16SkinMatricesBase16GetVelocityArrayEi | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK4Aska16SkinMatricesBase16GetVelocityArrayEi(long param_1,int param_2)

{
  long lVar1;
  
  lVar1 = *(long *)(param_1 + (ulong)*(byte *)(param_1 + 0xb) * 8 + 0x30);
  if (lVar1 != 0) {
    return lVar1 + (ulong)*(ushort *)(*(long *)(param_1 + 0x40) + (long)param_2 * 2) * 0x20;
  }
  return 0;
}

// ==== Aska::SkinMatricesBase::GetVelocityArrayBack(int) const
// vaddr 0x21d6458 | ghidra 0x22d6458 | size 32 | symbol _ZNK4Aska16SkinMatricesBase20GetVelocityArrayBackEi | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK4Aska16SkinMatricesBase20GetVelocityArrayBackEi(long param_1,int param_2)

{
  return *(long *)(param_1 + (ulong)(*(byte *)(param_1 + 0xb) ^ 1) * 8 + 0x30) +
         (ulong)*(ushort *)(*(long *)(param_1 + 0x40) + (long)param_2 * 2) * 0x20;
}

// ==== Aska::SkinMatricesBase::KickPalette(Aska::Matrix34*)
// vaddr 0x21d6478 | ghidra 0x22d6478 | size 500 | symbol _ZN4Aska16SkinMatricesBase11KickPaletteEPNS_8Matrix34E | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska16SkinMatricesBase11KickPaletteEPNS_8Matrix34E(long param_1,long param_2)

{
  byte bVar1;
  int iVar2;
  long lVar3;
  uint uVar4;
  long lVar5;
  undefined8 uVar6;
  long *plVar7;
  undefined8 *puVar8;
  uint uVar9;
  ushort *puVar10;
  undefined8 *puVar11;
  long lVar12;
  ulong uVar13;
  float fVar14;
  undefined8 uVar15;
  
  lVar12 = *(long *)(*(long *)(param_1 + 0x70) + 0x3d8);
  lVar5 = *(long *)(lVar12 + 0xd0);
  if (lVar5 == 0) {
    uVar13 = 0;
    bVar1 = *(byte *)(param_1 + 10);
  }
  else {
    uVar13 = (ulong)*(ushort *)(*(long *)(lVar12 + 0xb0) + 0x70);
    bVar1 = *(byte *)(param_1 + 10);
  }
  if ((bVar1 >> 1 & 1) == 0) {
    if ((int)uVar13 != 0) {
      lVar3 = 0;
      while( true ) {
        plVar7 = *(long **)(lVar5 + lVar3 * 8);
        if ((*(char *)(*plVar7 + 0x1a) == -1) &&
           (uVar4 = (uint)*(byte *)(plVar7[1] + 0x19), *(byte *)(plVar7[1] + 0x19) != 0)) {
          puVar8 = (undefined8 *)
                   (*(long *)(param_1 + (ulong)(*(byte *)(param_1 + 0xb) ^ 1) * 8 + 0x18) +
                   (ulong)*(ushort *)(*(long *)(param_1 + 0x40) + lVar3 * 2) * 0x30);
          puVar10 = (ushort *)(plVar7[4] + 0x10);
          do {
            uVar4 = uVar4 - 1;
            puVar11 = (undefined8 *)(param_2 + (ulong)*puVar10 * 0x30);
            uVar6 = *puVar11;
            puVar8[1] = puVar11[1];
            *puVar8 = uVar6;
            uVar6 = puVar11[2];
            puVar8[3] = puVar11[3];
            puVar8[2] = uVar6;
            uVar6 = puVar11[4];
            puVar8[5] = puVar11[5];
            puVar8[4] = uVar6;
            puVar8 = puVar8 + 6;
            puVar10 = puVar10 + 1;
          } while (uVar4 != 0);
        }
        lVar3 = lVar3 + 1;
        if ((long)uVar13 <= lVar3) break;
        lVar5 = *(long *)(lVar12 + 0xd0);
      }
    }
  }
  else {
    uVar6 = *(undefined8 *)(param_1 + (ulong)(*(byte *)(param_1 + 0xb) ^ 1) * 8 + 0x50);
    lVar5 = Aska::Texture::GetBody() const(uVar6);
    if ((int)uVar13 != 0) {
      lVar3 = 0;
      iVar2 = *(int *)(param_1 + 0x6c) * 0x10;
      do {
        plVar7 = *(long **)(*(long *)(lVar12 + 0xd0) + lVar3 * 8);
        if ((*(char *)(*plVar7 + 0x1a) == -1) &&
           (uVar4 = (uint)*(byte *)(plVar7[1] + 0x19), *(byte *)(plVar7[1] + 0x19) != 0)) {
          uVar9 = iVar2 * (uint)*(ushort *)(*(long *)(param_1 + 0x40) + lVar3 * 2);
          puVar10 = (ushort *)(plVar7[4] + 0x10);
          do {
            puVar8 = (undefined8 *)(lVar5 + (ulong)uVar9);
            uVar4 = uVar4 - 1;
            uVar9 = uVar9 + iVar2;
            puVar11 = (undefined8 *)(param_2 + (ulong)*puVar10 * 0x30);
            uVar15 = *puVar11;
            puVar8[1] = puVar11[1];
            *puVar8 = uVar15;
            uVar15 = puVar11[2];
            puVar8[3] = puVar11[3];
            puVar8[2] = uVar15;
            uVar15 = puVar11[4];
            puVar8[5] = puVar11[5];
            puVar8[4] = uVar15;
            puVar10 = puVar10 + 1;
          } while (uVar4 != 0);
        }
        lVar3 = lVar3 + 1;
      } while (lVar3 < (long)uVar13);
    }
    Aska::TextureManager::MarkTextureForUpdate(Aska::Texture*)(*(undefined8 *)PTR__ZN4Aska6Global17m_pTextureManagerE_02cc19f0,uVar6);
  }
  if ((*(long *)(param_1 + 0x60) != 0) &&
     (fVar14 = (float)(**(code **)**(undefined8 **)PTR__ZN4Aska6Global8m_pVSyncE_02cbd460)
                                (*(undefined8 **)PTR__ZN4Aska6Global8m_pVSyncE_02cbd460,0),
     _UNK_027e519c < fVar14)) {
    lVar5 = param_1 + (ulong)*(byte *)(param_1 + 0xb) * 8;
    uVar6 = *(undefined8 *)(lVar5 + 0x50);
    *(undefined8 *)(lVar5 + 0x50) = *(undefined8 *)(param_1 + 0x60);
    *(undefined8 *)(param_1 + 0x60) = uVar6;
  }
  *(byte *)(param_1 + 0xb) = *(byte *)(param_1 + 0xb) ^ 1;
  return;
}

// ==== Aska::SkinMatricesBase::GetTexturePaletteMatrices() const
// vaddr 0x21d666c | ghidra 0x22d666c | size 8 | symbol _ZNK4Aska16SkinMatricesBase25GetTexturePaletteMatricesEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska16SkinMatricesBase25GetTexturePaletteMatricesEv(void)

{
  return 0;
}

// ==== Aska::SkinMatricesBase::GetBoneObject(unsigned int) const
// vaddr 0x21d6674 | ghidra 0x22d6674 | size 8 | symbol _ZNK4Aska16SkinMatricesBase13GetBoneObjectEj | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska16SkinMatricesBase13GetBoneObjectEj(void)

{
  return 0;
}

// ==== Aska::SkinMatricesSimple::SkinMatricesSimple()
// vaddr 0x21d667c | ghidra 0x22d667c | size 44 | symbol _ZN4Aska18SkinMatricesSimpleC1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18SkinMatricesSimpleC2Ev(long *param_1)

{
  undefined *puVar1;
  
  Aska::SkinMatricesBase::SkinMatricesBase()();
  puVar1 = PTR__ZTVN4Aska18SkinMatricesSimpleE_02cbe340;
  *(undefined4 *)(param_1 + 0x11) = 0;
  param_1[0xf] = 0;
  param_1[0x10] = 0;
  *param_1 = (long)(puVar1 + 0x10);
  return;
}

// ==== Aska::SkinMatricesSimple::~SkinMatricesSimple()
// vaddr 0x21d66a8 | ghidra 0x22d66a8 | size 24 | symbol _ZN4Aska18SkinMatricesSimpleD2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18SkinMatricesSimpleD1Ev(long *param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZTVN4Aska18SkinMatricesSimpleE_02cbe340;
  param_1[0xf] = 0;
  param_1[0x10] = 0;
  *param_1 = (long)(puVar1 + 0x10);
  (*(code *)PTR__ZN4Aska16SkinMatricesBaseD1Ev_02c9a4a8)();
  return;
}

// ==== Aska::SkinMatricesSimple::~SkinMatricesSimple()
// vaddr 0x21d66c0 | ghidra 0x22d66c0 | size 44 | symbol _ZN4Aska18SkinMatricesSimpleD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18SkinMatricesSimpleD0Ev(long *param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZTVN4Aska18SkinMatricesSimpleE_02cbe340;
  param_1[0xf] = 0;
  param_1[0x10] = 0;
  *param_1 = (long)(puVar1 + 0x10);
  Aska::SkinMatricesBase::~SkinMatricesBase()();
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::SkinMatricesSimple::GetAllocSize(unsigned long, unsigned long, unsigned long) const
// vaddr 0x21d66ec | ghidra 0x22d66ec | size 60 | symbol _ZNK4Aska18SkinMatricesSimple12GetAllocSizeEmmm | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK4Aska18SkinMatricesSimple12GetAllocSizeEmmm(undefined8 param_1,long param_2)

{
  long lVar1;
  
  lVar1 = Aska::SkinMatricesBase::GetAllocSize(unsigned long, unsigned long, unsigned long) const();
  return ((*(long *)PTR__ZN4Aska16SkinMatricesBase15s_sizeToAlignToE_02cc1398 + param_2 * 0x30) - 1U
         & -*(long *)PTR__ZN4Aska16SkinMatricesBase15s_sizeToAlignToE_02cc1398) + lVar1;
}

// ==== Aska::SkinMatricesSimple::Assign(unsigned long, unsigned long, unsigned long)
// vaddr 0x21d6728 | ghidra 0x22d6728 | size 80 | symbol _ZN4Aska18SkinMatricesSimple6AssignEmmm | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska18SkinMatricesSimple6AssignEmmm(long param_1)

{
  long lVar1;
  long lVar2;
  long lVar3;
  
  lVar2 = Aska::SkinMatricesBase::Assign(unsigned long, unsigned long, unsigned long)();
  if (lVar2 != 0) {
    lVar3 = *(long *)PTR__ZN4Aska16SkinMatricesBase15s_sizeToAlignToE_02cc1398;
    lVar1 = lVar2 + lVar3;
    lVar2 = lVar2 + ((lVar3 + (ulong)*(ushort *)(param_1 + 8) * 0x30) - 1 & -lVar3);
    *(ulong *)(param_1 + 0x80) = lVar1 - 1U & -lVar3;
  }
  return lVar2;
}

// ==== Aska::SkinMatricesSimple::InitPalette_(Aska::AofObject*, Aska::DirectAofPrimitiveBase*)
// vaddr 0x21d6778 | ghidra 0x22d6778 | size 32 | symbol _ZN4Aska18SkinMatricesSimple12InitPalette_EPNS_9AofObjectEPNS_22DirectAofPrimitiveBaseE | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska18SkinMatricesSimple12InitPalette_EPNS_9AofObjectEPNS_22DirectAofPrimitiveBaseE
          (long param_1,long param_2,long param_3)

{
  undefined8 uVar1;
  
  if ((param_3 != 0) && (param_3 == *(long *)(param_2 + 0x3d8))) {
    *(long *)(param_1 + 0x78) = param_3;
    uVar1 = (*(code *)PTR__ZN4Aska16SkinMatricesBase4InitEPNS_9AofObjectE_02ca5750)();
    return uVar1;
  }
  return 0;
}

// ==== Aska::SkinMatricesSimple::MakeSkinMatrices()
// vaddr 0x21d6798 | ghidra 0x22d6798 | size 268 | symbol _ZN4Aska18SkinMatricesSimple16MakeSkinMatricesEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska18SkinMatricesSimple16MakeSkinMatricesEv(long param_1)

{
  undefined8 *puVar1;
  undefined4 *puVar2;
  undefined8 *puVar3;
  undefined8 uVar4;
  long lVar5;
  long lVar6;
  long lVar7;
  ulong uVar8;
  
  lVar5 = *(long *)(param_1 + 0x78);
  if (((lVar5 == 0) || (lVar6 = *(long *)(param_1 + 0x48), lVar6 == 0)) ||
     (*(long *)(param_1 + 0x80) == 0)) {
    uVar4 = 0;
  }
  else {
    if (*(char *)(lVar5 + 0x3de) != '\0') {
      if (*(short *)(param_1 + 8) != 0) {
        lVar7 = 0;
        uVar8 = 0;
        while( true ) {
          puVar3 = (undefined8 *)Aska::detail::AnimationGroupContainer::GetBoneMatrix(int) const(lVar5 + 0x380,(long)*(short *)(lVar6 + uVar8 * 2));
          if (puVar3 == (undefined8 *)0x0) {
            puVar2 = (undefined4 *)(*(long *)(param_1 + 0x80) + lVar7);
            *puVar2 = 0x3f800000;
            *(undefined8 *)(puVar2 + 3) = 0;
            *(undefined8 *)(puVar2 + 1) = 0;
            puVar2[5] = 0x3f800000;
            *(undefined8 *)(puVar2 + 6) = 0;
            *(undefined8 *)(puVar2 + 8) = 0;
            *(undefined8 *)(puVar2 + 10) = 0x3f800000;
          }
          else {
            uVar4 = *puVar3;
            puVar1 = (undefined8 *)(*(long *)(param_1 + 0x80) + lVar7);
            puVar1[1] = puVar3[1];
            *puVar1 = uVar4;
            uVar4 = puVar3[2];
            puVar1[3] = puVar3[3];
            puVar1[2] = uVar4;
            uVar4 = puVar3[4];
            puVar1[5] = puVar3[5];
            puVar1[4] = uVar4;
          }
          lVar5 = *(long *)(param_1 + 0x78);
          uVar8 = uVar8 + 1;
          if (*(ushort *)(param_1 + 8) <= uVar8) break;
          lVar6 = *(long *)(param_1 + 0x48);
          lVar7 = lVar7 + 0x30;
        }
      }
      *(undefined4 *)(param_1 + 0x88) = 3;
      *(undefined1 *)(lVar5 + 0x3de) = 0;
    }
    if (0 < *(int *)(param_1 + 0x88)) {
      Aska::SkinMatricesBase::KickPalette(Aska::Matrix34*)(param_1,*(undefined8 *)(param_1 + 0x80));
      *(int *)(param_1 + 0x88) = *(int *)(param_1 + 0x88) + -1;
    }
    uVar4 = 1;
  }
  return uVar4;
}

// ==== Aska::JointObject::MakeMatrix()
// vaddr 0x234bbe8 | ghidra 0x244bbe8 | size 196 | symbol _ZN4Aska11JointObject10MakeMatrixEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11JointObject10MakeMatrixEv(long param_1)

{
  long lVar1;
  long lVar2;
  bool bVar3;
  bool bVar4;
  long *plVar5;
  long lVar6;
  
  lVar6 = *(long *)(param_1 + 0xf0);
  if (lVar6 == 0) {
code_r0x0244bc38:
    bVar3 = true;
  }
  else {
    plVar5 = *(long **)(lVar6 + 0xe8);
    if ((plVar5 != (long *)0x0) && ((*(byte *)(plVar5 + 0x25) & 1) != 0)) {
      (**(code **)(*plVar5 + 0xa8))();
      lVar6 = *(long *)(param_1 + 0xf0);
      if (lVar6 == 0) goto code_r0x0244bc38;
    }
    bVar3 = false;
    if (*(long *)(lVar6 + 0xe8) != 0) {
      if ((*(byte *)(*(long *)(lVar6 + 0xe8) + 0x195) & 1) == 0) {
        bVar3 = false;
        bVar4 = true;
      }
      else {
        bVar3 = false;
        bVar4 = *(char *)(param_1 + 0x198) == '\0';
      }
      goto code_r0x0244bc54;
    }
  }
  bVar4 = true;
code_r0x0244bc54:
  lVar1 = 0;
  if (!bVar3 && !bVar4) {
    lVar1 = lVar6 + 0x70;
  }
  lVar2 = 0;
  if (!bVar3) {
    lVar2 = lVar6 + 0x10;
  }
  Aska::MatrixCalcFunc(Aska::Matrix*, Aska::Vector const*, Aska::Quaternion const*, Aska::Quaternion const*, Aska::Vector const*, Aska::Vector const*, Aska::Matrix const*)(param_1 + 0x40,param_1 + 0x80,param_1 + 0x90,param_1 + 0xc0,param_1 + 0xa0,lVar1,
                  lVar2);
  *(byte *)(param_1 + 0x128) = *(byte *)(param_1 + 0x128) & 0xe2;
  *(byte *)(param_1 + 0x129) = *(byte *)(param_1 + 0x129) | 3;
  return;
}

// ==== Aska::JointObject::Get(unsigned long, void*) const
// vaddr 0x234bcac | ghidra 0x244bcac | size 96 | symbol _ZNK4Aska11JointObject3GetEmPv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska11JointObject3GetEmPv(long param_1,ulong param_2,undefined4 *param_3)

{
  ulong uVar1;
  
  uVar1 = Aska::HierarchicalObject::Get(unsigned long, void*) const();
  if ((uVar1 & 1) == 0) {
    if ((param_2 & 0xffff0000ffff) != 0xf) {
      return 0;
    }
    *param_3 = *(undefined4 *)(param_1 + 0xc0);
    param_3[1] = *(undefined4 *)(param_1 + 0xc4);
    param_3[2] = *(undefined4 *)(param_1 + 200);
    param_3[3] = *(undefined4 *)(param_1 + 0xcc);
  }
  return 1;
}

// ==== Aska::JointObject::Set(unsigned long, void const*)
// vaddr 0x234bd0c | ghidra 0x244bd0c | size 112 | symbol _ZN4Aska11JointObject3SetEmPKv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska11JointObject3SetEmPKv(long param_1,ulong param_2,undefined4 *param_3)

{
  ulong uVar1;
  
  uVar1 = Aska::HierarchicalObject::Set(unsigned long, void const*)();
  if ((uVar1 & 1) == 0) {
    if ((param_2 & 0xffff0000ffff) != 0xf) {
      return 0;
    }
    if ((*(byte *)(param_1 + 0x128) & 1) == 0) {
      Aska::HierarchicalObjectContainer::UpdateHierarchically()(param_1 + 0x30);
    }
    *(undefined4 *)(param_1 + 0xc0) = *param_3;
    *(undefined4 *)(param_1 + 0xc4) = param_3[1];
    *(undefined4 *)(param_1 + 200) = param_3[2];
    *(undefined4 *)(param_1 + 0xcc) = param_3[3];
  }
  return 1;
}

// ==== Aska::JointObject::~JointObject()
// vaddr 0x234bd7c | ghidra 0x244bd7c | size 24 | symbol _ZN4Aska11JointObjectD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11JointObjectD0Ev(undefined8 param_1)

{
  Aska::HierarchicalObject::~HierarchicalObject()();
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::JointObject::GetClassID(int) const
// vaddr 0x234bd94 | ghidra 0x244bd94 | size 92 | symbol _ZNK4Aska11JointObject10GetClassIDEi | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska11JointObject10GetClassIDEi(undefined8 param_1,int param_2)

{
  undefined8 uVar1;
  undefined8 uVar2;
  
  if (param_2 == 0) {
    return 0xf002f111f182;
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


// FAILED to create function at 029d2868 Aska::SkinMatricesBase::s_sizeToAlignTo
// FAILED to create function at 02c54bd8 Aska::SkinMatrices::vtable
// FAILED to create function at 02c54c40 Aska::SkinMatrices::typeinfo
// FAILED to create function at 02c54c58 Aska::SkinMatricesBase::vtable
// FAILED to create function at 02c54cc0 Aska::SkinMatricesBase::typeinfo
// FAILED to create function at 02c54cd0 Aska::SkinMatricesSimple::vtable
// FAILED to create function at 02c54d40 Aska::SkinMatricesSimple::typeinfo
// FAILED to create function at 02c63c38 Aska::JointObject::vtable
// FAILED to create function at 02c63db0 Aska::JointObject::typeinfo
