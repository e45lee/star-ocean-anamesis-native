// port/decomp/dynamics/ide_templates.c: Ghidra decompiles for the dynamics subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-08 14:46 UTC: tools/decomp.sh '--into' 'dynamics/ide_templates' 'Aska::IDE_\w+<' 'Aska::IDE\w+<\(Aska' 'Aska::IDESpacePartitionBVH::\w+<'

// ==== Aska::IDEPrimitiveOBB<(Aska::_EnumIDESpacePartitionType)0>::~IDEPrimitiveOBB()
// vaddr 0x20e7af0 | ghidra 0x21e7af0 | size 20 | symbol _ZN4Aska15IDEPrimitiveOBBILNS_26_EnumIDESpacePartitionTypeE0EED2Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska15IDEPrimitiveOBBILNS_26_EnumIDESpacePartitionTypeE0EED2Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska15IDEPrimitiveOBBILNS_26_EnumIDESpacePartitionTypeE0EEE_02cbeab8 +
                   0x10);
  return;
}

// ==== Aska::IDEPrimitiveOBB<(Aska::_EnumIDESpacePartitionType)0>::~IDEPrimitiveOBB()
// vaddr 0x20e7b04 | ghidra 0x21e7b04 | size 4 | symbol _ZN4Aska15IDEPrimitiveOBBILNS_26_EnumIDESpacePartitionTypeE0EED0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska15IDEPrimitiveOBBILNS_26_EnumIDESpacePartitionTypeE0EED0Ev(void)

{
  (*(code *)PTR__ZdlPv_02ca4758)();
  return;
}

// ==== Aska::IDEPrimitiveOBB<(Aska::_EnumIDESpacePartitionType)0>::Update()
// vaddr 0x20e7b08 | ghidra 0x21e7b08 | size 1216 | symbol _ZN4Aska15IDEPrimitiveOBBILNS_26_EnumIDESpacePartitionTypeE0EE6UpdateEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska15IDEPrimitiveOBBILNS_26_EnumIDESpacePartitionTypeE0EE6UpdateEv(long param_1)

{
  long *plVar1;
  ulong uVar2;
  undefined8 *puVar3;
  undefined8 uVar4;
  long *plVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  undefined8 uVar14;
  undefined8 uVar15;
  undefined8 uVar16;
  float fVar17;
  undefined8 uStack_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined8 uStack_98;
  undefined8 uStack_90;
  undefined8 uStack_88;
  undefined8 uStack_80;
  undefined8 uStack_78;
  
  if (*(long *)(param_1 + 0x120) != 0) {
    plVar1 = *(long **)(param_1 + 0x120);
    *(undefined8 *)(param_1 + 0x88) = *(undefined8 *)(param_1 + 0xd8);
    *(undefined8 *)(param_1 + 0x80) = *(undefined8 *)(param_1 + 0xd0);
    *(undefined8 *)(param_1 + 0x98) = *(undefined8 *)(param_1 + 0xe8);
    *(undefined8 *)(param_1 + 0x90) = *(undefined8 *)(param_1 + 0xe0);
    *(undefined8 *)(param_1 + 0xa0) = *(undefined8 *)(param_1 + 0xf0);
    *(undefined4 *)(param_1 + 0xa8) = *(undefined4 *)(param_1 + 0xf8);
    *(undefined4 *)(param_1 + 0xac) = 0;
    *(undefined4 *)(param_1 + 0xb0) = *(undefined4 *)(param_1 + 0x100);
    *(undefined4 *)(param_1 + 0xb4) = *(undefined4 *)(param_1 + 0x104);
    *(undefined4 *)(param_1 + 0xb8) = *(undefined4 *)(param_1 + 0x108);
    *(undefined4 *)(param_1 + 0xbc) = 0;
    *(undefined4 *)(param_1 + 0xc0) = *(undefined4 *)(param_1 + 0x110);
    *(undefined4 *)(param_1 + 0xc4) = *(undefined4 *)(param_1 + 0x114);
    *(undefined4 *)(param_1 + 200) = *(undefined4 *)(param_1 + 0x118);
    *(undefined4 *)(param_1 + 0xcc) = 0;
    if ((*(byte *)(plVar1 + 0x25) & 1) != 0) {
      (**(code **)(*plVar1 + 0xa8))();
      plVar1 = *(long **)(param_1 + 0x120);
    }
    uVar2 = Aska::IAnimatable::IsThisIt(unsigned short) const(plVar1,0xf117);
    if ((uVar2 & 1) == 0) {
      uVar4 = (**(code **)(**(long **)(param_1 + 0x120) + 0x98))();
      Aska::Vector::ApplyMatrix(Aska::Matrix const*)(param_1 + 0x80,uVar4);
      Aska::Vector::ApplyMatrixNoTransport(Aska::Matrix const*)(param_1 + 0xa0,uVar4);
      Aska::Vector::ApplyMatrixNoTransport(Aska::Matrix const*)(param_1 + 0xb0,uVar4);
      Aska::Vector::ApplyMatrixNoTransport(Aska::Matrix const*)(param_1 + 0xc0,uVar4);
      fVar8 = *(float *)(param_1 + 0xa0) * *(float *)(param_1 + 0xa0) +
              *(float *)(param_1 + 0xa4) * *(float *)(param_1 + 0xa4) +
              *(float *)(param_1 + 0xa8) * *(float *)(param_1 + 0xa8);
      fVar17 = SQRT(fVar8);
      if (NAN(fVar17)) {
        fVar17 = (float)sqrtf(fVar8);
      }
      fVar8 = 1.0 / fVar17;
      *(float *)(param_1 + 0x90) = fVar17 * *(float *)(param_1 + 0x90);
      *(float *)(param_1 + 0xa0) = fVar8 * *(float *)(param_1 + 0xa0);
      *(float *)(param_1 + 0xa4) = fVar8 * *(float *)(param_1 + 0xa4);
      *(float *)(param_1 + 0xa8) = fVar8 * *(float *)(param_1 + 0xa8);
      fVar8 = *(float *)(param_1 + 0xb0) * *(float *)(param_1 + 0xb0) +
              *(float *)(param_1 + 0xb4) * *(float *)(param_1 + 0xb4) +
              *(float *)(param_1 + 0xb8) * *(float *)(param_1 + 0xb8);
      fVar17 = SQRT(fVar8);
      if (NAN(fVar17)) {
        fVar17 = (float)sqrtf(fVar8);
      }
      fVar8 = 1.0 / fVar17;
      *(float *)(param_1 + 0x94) = fVar17 * *(float *)(param_1 + 0x94);
      *(float *)(param_1 + 0xb0) = fVar8 * *(float *)(param_1 + 0xb0);
      *(float *)(param_1 + 0xb4) = fVar8 * *(float *)(param_1 + 0xb4);
      *(float *)(param_1 + 0xb8) = fVar8 * *(float *)(param_1 + 0xb8);
      fVar8 = *(float *)(param_1 + 0xc0) * *(float *)(param_1 + 0xc0) +
              *(float *)(param_1 + 0xc4) * *(float *)(param_1 + 0xc4) +
              *(float *)(param_1 + 200) * *(float *)(param_1 + 200);
      fVar17 = SQRT(fVar8);
      if (NAN(fVar17)) {
        fVar17 = (float)sqrtf(fVar8);
      }
      fVar8 = *(float *)(param_1 + 0x98);
    }
    else {
      plVar5 = *(long **)(param_1 + 0x120);
      plVar1 = plVar5;
      if ((long *)plVar5[0x82] != (long *)0x0) {
        plVar1 = (long *)plVar5[0x82];
      }
      if ((long *)plVar5[0x81] != (long *)0x0) {
        plVar1 = (long *)plVar5[0x81];
      }
      if ((*(byte *)(plVar1 + 0x25) & 1) != 0) {
        (**(code **)(*plVar1 + 0xa8))(plVar1);
      }
      puVar3 = (undefined8 *)(**(code **)(*plVar1 + 0x98))(plVar1);
      uStack_a8 = puVar3[1];
      uStack_b0 = *puVar3;
      uVar14 = puVar3[3];
      uVar4 = puVar3[2];
      fVar10 = (float)((ulong)uStack_b0 >> 0x20);
      fVar8 = (float)uStack_b0;
      fVar11 = (float)uStack_a8;
      uVar16 = puVar3[5];
      uVar15 = puVar3[4];
      uStack_78 = puVar3[7];
      uStack_80 = puVar3[6];
      fVar17 = SQRT(fVar8 * fVar8 + fVar10 * fVar10 + fVar11 * fVar11);
      uStack_a0 = uVar4;
      uStack_98 = uVar14;
      uStack_90 = uVar15;
      uStack_88 = uVar16;
      if (NAN(fVar17)) {
        fVar17 = (float)sqrtf();
      }
      fVar13 = (float)((ulong)uVar4 >> 0x20);
      fVar12 = (float)uVar4;
      fVar7 = SQRT(fVar12 * fVar12 + fVar13 * fVar13 + (float)uVar14 * (float)uVar14);
      if (NAN(fVar7)) {
        fVar7 = (float)sqrtf();
      }
      fVar6 = (float)((ulong)uVar15 >> 0x20);
      fVar9 = (float)uVar15 * (float)uVar15 + fVar6 * fVar6 + (float)uVar16 * (float)uVar16;
      fVar6 = SQRT(fVar9);
      fVar17 = 1.0 / fVar17;
      fVar7 = 1.0 / fVar7;
      if (NAN(fVar6)) {
        fVar6 = (float)sqrtf(fVar9);
      }
      fVar6 = 1.0 / fVar6;
      uStack_b0 = CONCAT44(fVar17 * fVar10,fVar17 * fVar8);
      uStack_98 = CONCAT44(uStack_98._4_4_,fVar7 * (float)uStack_98);
      uStack_a8 = CONCAT44(uStack_a8._4_4_,fVar17 * fVar11);
      uStack_a0 = CONCAT44(fVar7 * fVar13,fVar7 * fVar12);
      uStack_90 = CONCAT44(fVar6 * uStack_90._4_4_,fVar6 * (float)uStack_90);
      uStack_88 = CONCAT44(uStack_88._4_4_,fVar6 * (float)uStack_88);
      Aska::Vector::ApplyMatrix(Aska::Matrix const*)(param_1 + 0x80,&uStack_b0);
      Aska::Vector::ApplyMatrixNoTransport(Aska::Matrix const*)(param_1 + 0xa0,&uStack_b0);
      Aska::Vector::ApplyMatrixNoTransport(Aska::Matrix const*)(param_1 + 0xb0,&uStack_b0);
      Aska::Vector::ApplyMatrixNoTransport(Aska::Matrix const*)(param_1 + 0xc0,&uStack_b0);
      fVar8 = *(float *)(param_1 + 0xa0) * *(float *)(param_1 + 0xa0) +
              *(float *)(param_1 + 0xa4) * *(float *)(param_1 + 0xa4) +
              *(float *)(param_1 + 0xa8) * *(float *)(param_1 + 0xa8);
      fVar17 = SQRT(fVar8);
      if (NAN(fVar17)) {
        fVar17 = (float)sqrtf(fVar8);
      }
      fVar8 = 1.0 / fVar17;
      *(float *)(param_1 + 0x90) = fVar17 * *(float *)(param_1 + 0x90);
      *(float *)(param_1 + 0xa0) = fVar8 * *(float *)(param_1 + 0xa0);
      *(float *)(param_1 + 0xa4) = fVar8 * *(float *)(param_1 + 0xa4);
      *(float *)(param_1 + 0xa8) = fVar8 * *(float *)(param_1 + 0xa8);
      fVar8 = *(float *)(param_1 + 0xb0) * *(float *)(param_1 + 0xb0) +
              *(float *)(param_1 + 0xb4) * *(float *)(param_1 + 0xb4) +
              *(float *)(param_1 + 0xb8) * *(float *)(param_1 + 0xb8);
      fVar17 = SQRT(fVar8);
      if (NAN(fVar17)) {
        fVar17 = (float)sqrtf(fVar8);
      }
      fVar8 = 1.0 / fVar17;
      *(float *)(param_1 + 0x94) = fVar17 * *(float *)(param_1 + 0x94);
      *(float *)(param_1 + 0xb0) = fVar8 * *(float *)(param_1 + 0xb0);
      *(float *)(param_1 + 0xb4) = fVar8 * *(float *)(param_1 + 0xb4);
      *(float *)(param_1 + 0xb8) = fVar8 * *(float *)(param_1 + 0xb8);
      fVar8 = *(float *)(param_1 + 0xc0) * *(float *)(param_1 + 0xc0) +
              *(float *)(param_1 + 0xc4) * *(float *)(param_1 + 0xc4) +
              *(float *)(param_1 + 200) * *(float *)(param_1 + 200);
      fVar17 = SQRT(fVar8);
      if (NAN(fVar17)) {
        fVar17 = (float)sqrtf(fVar8);
      }
      fVar8 = *(float *)(param_1 + 0x98);
    }
    fVar10 = 1.0 / fVar17;
    *(float *)(param_1 + 0x98) = fVar17 * fVar8;
    *(undefined4 *)(param_1 + 0xac) = 0;
    *(undefined4 *)(param_1 + 0xbc) = 0;
    *(float *)(param_1 + 0xc0) = fVar10 * *(float *)(param_1 + 0xc0);
    *(float *)(param_1 + 0xc4) = fVar10 * *(float *)(param_1 + 0xc4);
    *(float *)(param_1 + 200) = fVar10 * *(float *)(param_1 + 200);
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  return;
}

// ==== Aska::IDEPrimitiveOBB<(Aska::_EnumIDESpacePartitionType)0>::Intersect(Aska::Ray*, unsigned short)
// vaddr 0x20e7fc8 | ghidra 0x21e7fc8 | size 8 | symbol _ZN4Aska15IDEPrimitiveOBBILNS_26_EnumIDESpacePartitionTypeE0EE9IntersectEPNS_3RayEt | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska15IDEPrimitiveOBBILNS_26_EnumIDESpacePartitionTypeE0EE9IntersectEPNS_3RayEt
               (long param_1)

{
  (*(code *)PTR__ZN4Aska9Collision9IntersectEPKNS_3BoxEPKNS_3RayE_02ca7338)(param_1 + 0x80);
  return;
}

// ==== Aska::IDEPrimitiveOBB<(Aska::_EnumIDESpacePartitionType)0>::Intersect(Aska::Segment*, unsigned short)
// vaddr 0x20e7fd0 | ghidra 0x21e7fd0 | size 8 | symbol _ZN4Aska15IDEPrimitiveOBBILNS_26_EnumIDESpacePartitionTypeE0EE9IntersectEPNS_7SegmentEt | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska15IDEPrimitiveOBBILNS_26_EnumIDESpacePartitionTypeE0EE9IntersectEPNS_7SegmentEt
               (long param_1)

{
  (*(code *)PTR__ZN4Aska9Collision9IntersectEPKNS_3BoxEPKNS_7SegmentE_02c9f470)(param_1 + 0x80);
  return;
}

// ==== Aska::IDEPrimitiveOBB<(Aska::_EnumIDESpacePartitionType)0>::FindIntersectNearestPoint(Aska::Vector*, Aska::Ray*, unsigned short)
// vaddr 0x20e7fd8 | ghidra 0x21e7fd8 | size 116 | symbol _ZN4Aska15IDEPrimitiveOBBILNS_26_EnumIDESpacePartitionTypeE0EE25FindIntersectNearestPointEPNS_6VectorEPNS_3RayEt | lib libSOA-3.7.0.so | 2026-10-08
bool _ZN4Aska15IDEPrimitiveOBBILNS_26_EnumIDESpacePartitionTypeE0EE25FindIntersectNearestPointEPNS_6VectorEPNS_3RayEt
               (long param_1,undefined4 *param_2,undefined8 param_3)

{
  int iVar1;
  undefined4 *puStack_40;
  undefined1 *puStack_38;
  undefined4 auStack_30 [4];
  undefined1 auStack_20 [16];
  
  puStack_40 = auStack_30;
  puStack_38 = auStack_20;
  iVar1 = Aska::Collision::FindIntersectPoint(Aska::Box const*, Aska::Ray const*, Aska::Vector**)(param_1 + 0x80,param_3,&puStack_40);
  if (0 < iVar1) {
    *param_2 = *puStack_40;
    param_2[1] = puStack_40[1];
    param_2[2] = puStack_40[2];
    param_2[3] = puStack_40[3];
  }
  return 0 < iVar1;
}

// ==== Aska::IDEPrimitiveOBB<(Aska::_EnumIDESpacePartitionType)0>::FindIntersectNearestPoint(Aska::Vector*, Aska::Segment*, unsigned short)
// vaddr 0x20e804c | ghidra 0x21e804c | size 116 | symbol _ZN4Aska15IDEPrimitiveOBBILNS_26_EnumIDESpacePartitionTypeE0EE25FindIntersectNearestPointEPNS_6VectorEPNS_7SegmentEt | lib libSOA-3.7.0.so | 2026-10-08
bool _ZN4Aska15IDEPrimitiveOBBILNS_26_EnumIDESpacePartitionTypeE0EE25FindIntersectNearestPointEPNS_6VectorEPNS_7SegmentEt
               (long param_1,undefined4 *param_2,undefined8 param_3)

{
  int iVar1;
  undefined4 *puStack_40;
  undefined1 *puStack_38;
  undefined4 auStack_30 [4];
  undefined1 auStack_20 [16];
  
  puStack_40 = auStack_30;
  puStack_38 = auStack_20;
  iVar1 = Aska::Collision::FindIntersectPoint(Aska::Box const*, Aska::Segment const*, Aska::Vector**)(param_1 + 0x80,param_3,&puStack_40);
  if (0 < iVar1) {
    *param_2 = *puStack_40;
    param_2[1] = puStack_40[1];
    param_2[2] = puStack_40[2];
    param_2[3] = puStack_40[3];
  }
  return 0 < iVar1;
}

// ==== Aska::IDEPrimitiveOBB<(Aska::_EnumIDESpacePartitionType)0>::FindIntersectNearestObject(Aska::IDE_ResultOfNearestObject*, Aska::Ray*, unsigned short)
// vaddr 0x20e80c0 | ghidra 0x21e80c0 | size 136 | symbol _ZN4Aska15IDEPrimitiveOBBILNS_26_EnumIDESpacePartitionTypeE0EE26FindIntersectNearestObjectEPNS_25IDE_ResultOfNearestObjectEPNS_3RayEt | lib libSOA-3.7.0.so | 2026-10-08
bool _ZN4Aska15IDEPrimitiveOBBILNS_26_EnumIDESpacePartitionTypeE0EE26FindIntersectNearestObjectEPNS_25IDE_ResultOfNearestObjectEPNS_3RayEt
               (long param_1,undefined4 *param_2,undefined8 param_3)

{
  int iVar1;
  undefined4 *puStack_50;
  undefined1 *puStack_48;
  undefined4 auStack_40 [4];
  undefined1 auStack_30 [16];
  
  puStack_50 = auStack_40;
  puStack_48 = auStack_30;
  iVar1 = Aska::Collision::FindIntersectPoint(Aska::Box const*, Aska::Ray const*, Aska::Vector**)(param_1 + 0x80,param_3,&puStack_50);
  if (0 < iVar1) {
    *(undefined8 *)(param_2 + 4) = *(undefined8 *)(param_1 + 0x18);
    *param_2 = *puStack_50;
    param_2[1] = puStack_50[1];
    param_2[2] = puStack_50[2];
    param_2[3] = puStack_50[3];
  }
  return 0 < iVar1;
}

// ==== Aska::IDEPrimitiveOBB<(Aska::_EnumIDESpacePartitionType)0>::FindIntersectNearestObject(Aska::IDE_ResultOfNearestObject*, Aska::Segment*, unsigned short)
// vaddr 0x20e8148 | ghidra 0x21e8148 | size 136 | symbol _ZN4Aska15IDEPrimitiveOBBILNS_26_EnumIDESpacePartitionTypeE0EE26FindIntersectNearestObjectEPNS_25IDE_ResultOfNearestObjectEPNS_7SegmentEt | lib libSOA-3.7.0.so | 2026-10-08
bool _ZN4Aska15IDEPrimitiveOBBILNS_26_EnumIDESpacePartitionTypeE0EE26FindIntersectNearestObjectEPNS_25IDE_ResultOfNearestObjectEPNS_7SegmentEt
               (long param_1,undefined4 *param_2,undefined8 param_3)

{
  int iVar1;
  undefined4 *puStack_50;
  undefined1 *puStack_48;
  undefined4 auStack_40 [4];
  undefined1 auStack_30 [16];
  
  puStack_50 = auStack_40;
  puStack_48 = auStack_30;
  iVar1 = Aska::Collision::FindIntersectPoint(Aska::Box const*, Aska::Segment const*, Aska::Vector**)(param_1 + 0x80,param_3,&puStack_50);
  if (0 < iVar1) {
    *(undefined8 *)(param_2 + 4) = *(undefined8 *)(param_1 + 0x18);
    *param_2 = *puStack_50;
    param_2[1] = puStack_50[1];
    param_2[2] = puStack_50[2];
    param_2[3] = puStack_50[3];
  }
  return 0 < iVar1;
}

// ==== Aska::IDEPrimitiveOBB<(Aska::_EnumIDESpacePartitionType)0>::FindIntersectObjects(Aska::INotify*, Aska::Vector const*, unsigned short)
// vaddr 0x20e81d0 | ghidra 0x21e81d0 | size 72 | symbol _ZN4Aska15IDEPrimitiveOBBILNS_26_EnumIDESpacePartitionTypeE0EE20FindIntersectObjectsEPNS_7INotifyEPKNS_6VectorEt | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska15IDEPrimitiveOBBILNS_26_EnumIDESpacePartitionTypeE0EE20FindIntersectObjectsEPNS_7INotifyEPKNS_6VectorEt
               (long param_1,undefined8 *param_2,undefined8 param_3)

{
  ulong uVar1;
  
  uVar1 = Aska::Collision::Intersect(Aska::Box const*, Aska::Vector const*)(param_1 + 0x80,param_3);
  if ((uVar1 & 1) != 0) {
                    /* WARNING: Could not recover jumptable at 0x021e8208. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)*param_2)(param_2,param_1);
    return;
  }
  return;
}

// ==== Aska::IDEPrimitiveOBB<(Aska::_EnumIDESpacePartitionType)0>::FindIntersectObjects(Aska::INotify*, Aska::Box const*, unsigned short)
// vaddr 0x20e8218 | ghidra 0x21e8218 | size 72 | symbol _ZN4Aska15IDEPrimitiveOBBILNS_26_EnumIDESpacePartitionTypeE0EE20FindIntersectObjectsEPNS_7INotifyEPKNS_3BoxEt | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska15IDEPrimitiveOBBILNS_26_EnumIDESpacePartitionTypeE0EE20FindIntersectObjectsEPNS_7INotifyEPKNS_3BoxEt
               (long param_1,undefined8 *param_2,undefined8 param_3)

{
  ulong uVar1;
  
  uVar1 = Aska::Collision::Intersect(Aska::Box const*, Aska::Box const*)(param_1 + 0x80,param_3);
  if ((uVar1 & 1) != 0) {
                    /* WARNING: Could not recover jumptable at 0x021e8250. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)*param_2)(param_2,param_1);
    return;
  }
  return;
}

// ==== Aska::IDEPrimitiveAABB<(Aska::_EnumIDESpacePartitionType)0>* Aska::IDESpacePartition::Alloc<Aska::IDEPrimitiveAABB<(Aska::_EnumIDESpacePartitionType)0>, Aska::AABB_MinMax>(Aska::AABB_MinMax*)
// vaddr 0x23462e0 | ghidra 0x24462e0 | size 360 | symbol _ZN4Aska17IDESpacePartition5AllocINS_16IDEPrimitiveAABBILNS_26_EnumIDESpacePartitionTypeE0EEENS_11AABB_MinMaxEEEPT_PT0_ | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska17IDESpacePartition5AllocINS_16IDEPrimitiveAABBILNS_26_EnumIDESpacePartitionTypeE0EEENS_11AABB_MinMaxEEEPT_PT0_
               (long param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  undefined *puVar2;
  long *plVar3;
  
  if (*(long *)(param_1 + 8) == 0) {
    plVar3 = (long *)operator new(unsigned long, unsigned long, bool)(0xa0,0x10,1);
    if (plVar3 != (long *)0x0) {
      *(undefined2 *)((long)plVar3 + 0x21) = 1;
      plVar3[2] = 0;
      plVar3[3] = (long)plVar3;
      *(undefined1 *)((long)plVar3 + 0x23) = 1;
      *(undefined1 *)(plVar3 + 0xf) = 0;
      plVar3[0xd] = 0;
      plVar3[0xe] = 0;
      plVar3[0xc] = 0;
      *(undefined1 *)((long)plVar3 + 0x79) = 1;
      plVar3[6] = 0;
      *(undefined4 *)(plVar3 + 7) = 0;
      plVar3[8] = 0;
      *(undefined4 *)(plVar3 + 9) = 0;
      *(undefined1 *)(plVar3 + 4) = 1;
      *(undefined4 *)(plVar3 + 10) = 0xbf800000;
      *plVar3 = (long)(
                      PTR__ZTVN4Aska16IDEPrimitiveAABBILNS_26_EnumIDESpacePartitionTypeE0EEE_02cb7d98
                      + 0x10);
      plVar3[1] = 0;
      *(undefined4 *)(plVar3 + 0x10) = *param_2;
      *(undefined4 *)((long)plVar3 + 0x84) = param_2[1];
      *(undefined4 *)(plVar3 + 0x11) = param_2[2];
      *(undefined4 *)((long)plVar3 + 0x8c) = param_2[3];
      *(undefined4 *)(plVar3 + 0x12) = param_2[4];
      *(undefined4 *)((long)plVar3 + 0x94) = param_2[5];
      *(undefined4 *)(plVar3 + 0x13) = param_2[6];
      uVar1 = param_2[7];
      *(undefined1 *)((long)plVar3 + 0x21) = 1;
      *(undefined4 *)((long)plVar3 + 0x9c) = uVar1;
    }
  }
  else {
    plVar3 = (long *)Aska::MemoryManager::AlignedMalloc(unsigned long, long)(*(long *)(param_1 + 8),0xa0,0x10);
    if (plVar3 != (long *)0x0) {
      plVar3[2] = 0;
      plVar3[3] = (long)plVar3;
      *(undefined1 *)(plVar3 + 0xf) = 0;
      plVar3[0xd] = 0;
      plVar3[0xe] = 0;
      plVar3[0xc] = 0;
      plVar3[6] = 0;
      *(undefined4 *)(plVar3 + 7) = 0;
      plVar3[8] = 0;
      *(undefined4 *)(plVar3 + 9) = 0;
      *(undefined4 *)(plVar3 + 10) = 0xbf800000;
      puVar2 = PTR__ZTVN4Aska16IDEPrimitiveAABBILNS_26_EnumIDESpacePartitionTypeE0EEE_02cb7d98;
      *(undefined2 *)((long)plVar3 + 0x21) = 1;
      *(undefined1 *)((long)plVar3 + 0x23) = 1;
      *(undefined1 *)((long)plVar3 + 0x79) = 1;
      *(undefined1 *)(plVar3 + 4) = 1;
      *plVar3 = (long)(puVar2 + 0x10);
      plVar3[1] = 0;
      *(undefined4 *)(plVar3 + 0x10) = *param_2;
      *(undefined4 *)((long)plVar3 + 0x84) = param_2[1];
      *(undefined4 *)(plVar3 + 0x11) = param_2[2];
      *(undefined4 *)((long)plVar3 + 0x8c) = param_2[3];
      *(undefined4 *)(plVar3 + 0x12) = param_2[4];
      *(undefined4 *)((long)plVar3 + 0x94) = param_2[5];
      *(undefined4 *)(plVar3 + 0x13) = param_2[6];
      uVar1 = param_2[7];
      *(undefined1 *)((long)plVar3 + 0x21) = 1;
      *(undefined4 *)((long)plVar3 + 0x9c) = uVar1;
    }
  }
  return;
}

// ==== Aska::IDEPrimitiveSphere<(Aska::_EnumIDESpacePartitionType)0>* Aska::IDESpacePartition::Alloc<Aska::IDEPrimitiveSphere<(Aska::_EnumIDESpacePartitionType)0>, Aska::Vector>(Aska::Vector*)
// vaddr 0x23464c4 | ghidra 0x24464c4 | size 304 | symbol _ZN4Aska17IDESpacePartition5AllocINS_18IDEPrimitiveSphereILNS_26_EnumIDESpacePartitionTypeE0EEENS_6VectorEEEPT_PT0_ | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska17IDESpacePartition5AllocINS_18IDEPrimitiveSphereILNS_26_EnumIDESpacePartitionTypeE0EEENS_6VectorEEEPT_PT0_
               (long param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  undefined *puVar2;
  long *plVar3;
  
  if (*(long *)(param_1 + 8) == 0) {
    plVar3 = (long *)operator new(unsigned long, unsigned long, bool)(0x90,0x10,1);
    if (plVar3 != (long *)0x0) {
      *(undefined4 *)(plVar3 + 10) = 0xbf800000;
      *(undefined2 *)((long)plVar3 + 0x21) = 1;
      plVar3[2] = 0;
      plVar3[3] = (long)plVar3;
      *(undefined1 *)((long)plVar3 + 0x23) = 1;
      *(undefined1 *)(plVar3 + 0xf) = 0;
      plVar3[0xd] = 0;
      plVar3[0xe] = 0;
      plVar3[0xc] = 0;
      *(undefined1 *)((long)plVar3 + 0x79) = 1;
      plVar3[6] = 0;
      *(undefined4 *)(plVar3 + 7) = 0;
      plVar3[8] = 0;
      *(undefined4 *)(plVar3 + 9) = 0;
      *(undefined1 *)(plVar3 + 4) = 2;
      *plVar3 = (long)(
                      PTR__ZTVN4Aska18IDEPrimitiveSphereILNS_26_EnumIDESpacePartitionTypeE0EEE_02cc0c88
                      + 0x10);
      plVar3[1] = 0;
      *(undefined4 *)(plVar3 + 0x10) = *param_2;
      *(undefined4 *)((long)plVar3 + 0x84) = param_2[1];
      *(undefined4 *)(plVar3 + 0x11) = param_2[2];
      uVar1 = param_2[3];
      *(undefined1 *)((long)plVar3 + 0x21) = 1;
      *(undefined4 *)((long)plVar3 + 0x8c) = uVar1;
    }
  }
  else {
    plVar3 = (long *)Aska::MemoryManager::AlignedMalloc(unsigned long, long)(*(long *)(param_1 + 8),0x90,0x10);
    if (plVar3 != (long *)0x0) {
      *(undefined4 *)(plVar3 + 10) = 0xbf800000;
      plVar3[2] = 0;
      plVar3[3] = (long)plVar3;
      *(undefined1 *)(plVar3 + 0xf) = 0;
      plVar3[0xd] = 0;
      plVar3[0xe] = 0;
      plVar3[0xc] = 0;
      plVar3[6] = 0;
      *(undefined4 *)(plVar3 + 7) = 0;
      plVar3[8] = 0;
      *(undefined4 *)(plVar3 + 9) = 0;
      *(undefined1 *)(plVar3 + 4) = 2;
      puVar2 = PTR__ZTVN4Aska18IDEPrimitiveSphereILNS_26_EnumIDESpacePartitionTypeE0EEE_02cc0c88;
      *(undefined2 *)((long)plVar3 + 0x21) = 1;
      *(undefined1 *)((long)plVar3 + 0x23) = 1;
      *(undefined1 *)((long)plVar3 + 0x79) = 1;
      *plVar3 = (long)(puVar2 + 0x10);
      plVar3[1] = 0;
      *(undefined4 *)(plVar3 + 0x10) = *param_2;
      *(undefined4 *)((long)plVar3 + 0x84) = param_2[1];
      *(undefined4 *)(plVar3 + 0x11) = param_2[2];
      uVar1 = param_2[3];
      *(undefined1 *)((long)plVar3 + 0x21) = 1;
      *(undefined4 *)((long)plVar3 + 0x8c) = uVar1;
    }
  }
  return;
}

// ==== Aska::IDEPrimitiveHeightObject<(Aska::_EnumIDESpacePartitionType)0>* Aska::IDESpacePartition::Alloc<Aska::IDEPrimitiveHeightObject<(Aska::_EnumIDESpacePartitionType)0>, Aska::HeightObject>(Aska::HeightObject*)
// vaddr 0x2346694 | ghidra 0x2446694 | size 292 | symbol _ZN4Aska17IDESpacePartition5AllocINS_24IDEPrimitiveHeightObjectILNS_26_EnumIDESpacePartitionTypeE0EEENS_12HeightObjectEEEPT_PT0_ | lib libSOA-3.7.0.so | 2026-10-08
long * _ZN4Aska17IDESpacePartition5AllocINS_24IDEPrimitiveHeightObjectILNS_26_EnumIDESpacePartitionTypeE0EEENS_12HeightObjectEEEPT_PT0_
                 (long param_1,long *param_2)

{
  byte bVar1;
  long *plVar2;
  ulong uVar3;
  undefined *puVar4;
  
  if (*(long *)(param_1 + 8) == 0) {
    plVar2 = (long *)operator new(unsigned long, unsigned long, bool)(0xb0,0x10,1);
    if (plVar2 == (long *)0x0) {
      return (long *)0x0;
    }
    *(undefined2 *)((long)plVar2 + 0x21) = 0x101;
    *(undefined4 *)(plVar2 + 10) = 0xbf800000;
    plVar2[2] = 0;
    plVar2[3] = (long)plVar2;
    *(undefined1 *)((long)plVar2 + 0x23) = 1;
    *(undefined1 *)(plVar2 + 0xf) = 0;
    plVar2[0xd] = 0;
    plVar2[0xe] = 0;
    plVar2[0xc] = 0;
    *(undefined1 *)((long)plVar2 + 0x79) = 1;
    plVar2[6] = 0;
    *(undefined4 *)(plVar2 + 7) = 0;
    plVar2[8] = 0;
    *(undefined4 *)(plVar2 + 9) = 0;
    *(undefined1 *)(plVar2 + 4) = 3;
    puVar4 = PTR__ZTVN4Aska24IDEPrimitiveHeightObjectILNS_26_EnumIDESpacePartitionTypeE0EEE_02cb9228
    ;
  }
  else {
    plVar2 = (long *)Aska::MemoryManager::AlignedMalloc(unsigned long, long)(*(long *)(param_1 + 8),0xb0,0x10);
    if (plVar2 == (long *)0x0) {
      return (long *)0x0;
    }
    *(undefined2 *)((long)plVar2 + 0x21) = 0x101;
    *(undefined4 *)(plVar2 + 10) = 0xbf800000;
    plVar2[2] = 0;
    plVar2[3] = (long)plVar2;
    *(undefined1 *)(plVar2 + 0xf) = 0;
    plVar2[0xd] = 0;
    plVar2[0xe] = 0;
    plVar2[0xc] = 0;
    plVar2[6] = 0;
    *(undefined4 *)(plVar2 + 7) = 0;
    plVar2[8] = 0;
    *(undefined4 *)(plVar2 + 9) = 0;
    *(undefined1 *)(plVar2 + 4) = 3;
    puVar4 = PTR__ZTVN4Aska24IDEPrimitiveHeightObjectILNS_26_EnumIDESpacePartitionTypeE0EEE_02cb9228
    ;
    *(undefined1 *)((long)plVar2 + 0x23) = 1;
    *(undefined1 *)((long)plVar2 + 0x79) = 1;
  }
  *plVar2 = (long)(puVar4 + 0x10);
  plVar2[1] = 0;
  plVar2[0x10] = (long)param_2;
  uVar3 = (**(code **)(*param_2 + 0x1a0))(param_2);
  bVar1 = 0x80;
  if ((uVar3 & 1) == 0) {
    bVar1 = 0;
  }
  *(byte *)((long)plVar2 + 0x23) = *(byte *)((long)plVar2 + 0x23) | bVar1;
  *(undefined1 *)((long)plVar2 + 0x21) = 1;
  return plVar2;
}

// ==== Aska::IDEPrimitiveCollisionHandler<(Aska::_EnumIDESpacePartitionType)0>* Aska::IDESpacePartition::Alloc<Aska::IDEPrimitiveCollisionHandler<(Aska::_EnumIDESpacePartitionType)0>, Aska::CollisionHandler>(Aska::CollisionHandler*)
// vaddr 0x23467f4 | ghidra 0x24467f4 | size 144 | symbol _ZN4Aska17IDESpacePartition5AllocINS_28IDEPrimitiveCollisionHandlerILNS_26_EnumIDESpacePartitionTypeE0EEENS_16CollisionHandlerEEEPT_PT0_ | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska17IDESpacePartition5AllocINS_28IDEPrimitiveCollisionHandlerILNS_26_EnumIDESpacePartitionTypeE0EEENS_16CollisionHandlerEEEPT_PT0_
               (long param_1,long param_2)

{
  undefined *puVar1;
  long *plVar2;
  
  if (*(long *)(param_1 + 8) == 0) {
    plVar2 = (long *)operator new(unsigned long, unsigned long, bool)(0xb0,0x10,1);
  }
  else {
    plVar2 = (long *)Aska::MemoryManager::AlignedMalloc(unsigned long, long)(*(long *)(param_1 + 8),0xb0,0x10);
  }
  if (plVar2 != (long *)0x0) {
    plVar2[2] = 0;
    plVar2[3] = (long)plVar2;
    plVar2[0xd] = 0;
    plVar2[0xe] = 0;
    plVar2[0xc] = 0;
    plVar2[6] = 0;
    *(undefined4 *)(plVar2 + 7) = 0;
    plVar2[8] = 0;
    *(undefined4 *)(plVar2 + 9) = 0;
    plVar2[0x10] = param_2;
    *(undefined2 *)(plVar2 + 0xf) = 0x100;
    *(undefined4 *)(plVar2 + 10) = 0xbf800000;
    puVar1 = 
    PTR__ZTVN4Aska28IDEPrimitiveCollisionHandlerILNS_26_EnumIDESpacePartitionTypeE0EEE_02cc2ef8;
    *(undefined4 *)(plVar2 + 4) = 0x1010104;
    *plVar2 = (long)(puVar1 + 0x10);
    plVar2[1] = 0;
    plVar2[0x14] = 0;
  }
  return;
}

// ==== void Aska::IDESpacePartitionBVH::CollisionDetectionForArray<Aska::IDE_CollisionDetectionParam<(Aska::_Enum_IDECollisionDetectionInputType)2, (Aska::_Enum_IDECollisionDetectionOutputType)3>, false>(Aska::IDE_CollisionDetectionParam<(Aska::_Enum_IDECollisionDetectionInputType)2, (Aska::_Enum_IDECollisionDetectionOutputType)3>*, Aska::IDEPrimitiveBase*)
// vaddr 0x2347610 | ghidra 0x2447610 | size 1128 | symbol _ZN4Aska20IDESpacePartitionBVH26CollisionDetectionForArrayINS_27IDE_CollisionDetectionParamILNS_36_Enum_IDECollisionDetectionInputTypeE2ELNS_37_Enum_IDECollisionDetectionOutputTypeE3EEELb0EEEvPT_PNS_16IDEPrimitiveBaseE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska20IDESpacePartitionBVH26CollisionDetectionForArrayINS_27IDE_CollisionDetectionParamILNS_36_Enum_IDECollisionDetectionInputTypeE2ELNS_37_Enum_IDECollisionDetectionOutputTypeE3EEELb0EEEvPT_PNS_16IDEPrimitiveBaseE
               (long param_1,long param_2)

{
  undefined4 uVar1;
  uint uVar2;
  undefined8 *puVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined1 auVar6 [16];
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  bool bVar11;
  ulong uVar12;
  uint uVar13;
  long lVar14;
  long lVar15;
  uint *puVar16;
  undefined8 *puVar17;
  long lVar18;
  uint *puVar19;
  undefined8 *puVar20;
  long lVar21;
  long lVar22;
  uint uVar23;
  ulong uVar24;
  ulong uVar25;
  ulong uVar26;
  ulong uVar27;
  undefined4 *puVar28;
  undefined4 *puVar29;
  undefined8 uVar30;
  uint uVar31;
  uint uVar32;
  uint uVar33;
  uint uVar34;
  byte bVar35;
  byte bVar36;
  byte bVar37;
  byte bVar38;
  byte bVar39;
  byte bVar40;
  byte bVar41;
  byte bVar42;
  byte bVar43;
  byte bVar44;
  byte bVar45;
  byte bVar46;
  int iVar47;
  int iVar49;
  int iVar50;
  undefined1 auVar48 [16];
  int iVar51;
  long alStack_9d8 [59];
  uint auStack_800 [4];
  undefined8 auStack_7f0 [2];
  uint auStack_7e0 [2];
  undefined8 auStack_7d8 [239];
  
  uVar13 = *(uint *)(param_1 + 0x20);
  uVar23 = uVar13 + 0x1f;
  uVar2 = uVar23 >> 5;
  if (uVar2 == 0) {
    uVar24 = 0;
  }
  else {
    uVar24 = (ulong)uVar2;
    if (uVar23 < 0x80) {
      lVar15 = 0;
    }
    else {
      uVar23 = uVar23 >> 5 & 3;
      lVar15 = uVar24 - uVar23;
      if (lVar15 != 0) {
        uVar31 = uVar13 + (int)_UNK_029e3690;
        uVar32 = uVar13 + (int)((ulong)_UNK_029e3690 >> 0x20);
        uVar33 = uVar13 + (int)_UNK_029e3698;
        uVar34 = uVar13 + (int)((ulong)_UNK_029e3698 >> 0x20);
        puVar16 = auStack_7e0;
        lVar18 = lVar15;
        do {
          auVar48._8_4_ = 1;
          auVar48._0_8_ = 0x100000001;
          auVar48._12_4_ = 1;
          auVar6._4_4_ = uVar32;
          auVar6._0_4_ = uVar31;
          auVar6._8_4_ = uVar33;
          auVar6._12_4_ = uVar34;
          auVar48 = NEON_ushl(auVar48,auVar6,4);
          iVar7 = -(uint)(0x1f < uVar31);
          bVar35 = (byte)((uint)iVar7 >> 8);
          bVar36 = (byte)((uint)iVar7 >> 0x10);
          bVar37 = (byte)((uint)iVar7 >> 0x18);
          iVar8 = -(uint)(0x1f < uVar32);
          bVar38 = (byte)((uint)iVar8 >> 8);
          bVar39 = (byte)((uint)iVar8 >> 0x10);
          bVar40 = (byte)((uint)iVar8 >> 0x18);
          iVar9 = -(uint)(0x1f < uVar33);
          bVar41 = (byte)((uint)iVar9 >> 8);
          bVar42 = (byte)((uint)iVar9 >> 0x10);
          bVar43 = (byte)((uint)iVar9 >> 0x18);
          iVar10 = -(uint)(0x1f < uVar34);
          bVar44 = (byte)((uint)iVar10 >> 8);
          bVar45 = (byte)((uint)iVar10 >> 0x10);
          bVar46 = (byte)((uint)iVar10 >> 0x18);
          iVar47 = auVar48._0_4_ + -1;
          iVar49 = auVar48._4_4_ + -1;
          iVar50 = auVar48._8_4_ + -1;
          iVar51 = auVar48._12_4_ + -1;
          lVar18 = lVar18 + -4;
          *(ulong *)(puVar16 + 2) =
               CONCAT17(bVar46 | (byte)((uint)iVar51 >> 0x18) & ~bVar46,
                        CONCAT16(bVar45 | (byte)((uint)iVar51 >> 0x10) & ~bVar45,
                                 CONCAT15(bVar44 | (byte)((uint)iVar51 >> 8) & ~bVar44,
                                          CONCAT14((byte)iVar10 | (byte)iVar51 & ~(byte)iVar10,
                                                   CONCAT13(bVar43 | (byte)((uint)iVar50 >> 0x18) &
                                                                     ~bVar43,
                                                            CONCAT12(bVar42 | (byte)((uint)iVar50 >>
                                                                                    0x10) & ~bVar42,
                                                                     CONCAT11(bVar41 | (byte)((uint)
                                                  iVar50 >> 8) & ~bVar41,
                                                  (byte)iVar9 | (byte)iVar50 & ~(byte)iVar9)))))));
          *(ulong *)puVar16 =
               CONCAT17(bVar40 | (byte)((uint)iVar49 >> 0x18) & ~bVar40,
                        CONCAT16(bVar39 | (byte)((uint)iVar49 >> 0x10) & ~bVar39,
                                 CONCAT15(bVar38 | (byte)((uint)iVar49 >> 8) & ~bVar38,
                                          CONCAT14((byte)iVar8 | (byte)iVar49 & ~(byte)iVar8,
                                                   CONCAT13(bVar37 | (byte)((uint)iVar47 >> 0x18) &
                                                                     ~bVar37,
                                                            CONCAT12(bVar36 | (byte)((uint)iVar47 >>
                                                                                    0x10) & ~bVar36,
                                                                     CONCAT11(bVar35 | (byte)((uint)
                                                  iVar47 >> 8) & ~bVar35,
                                                  (byte)iVar7 | (byte)iVar47 & ~(byte)iVar7)))))));
          uVar31 = uVar31 - 0x80;
          uVar32 = uVar32 - 0x80;
          uVar33 = uVar33 - 0x80;
          uVar34 = uVar34 - 0x80;
          puVar16 = puVar16 + 4;
        } while (lVar18 != 0);
        uVar13 = uVar13 + (int)lVar15 * -0x20;
        if (uVar23 == 0) goto code_r0x024476f8;
      }
    }
    lVar18 = uVar24 - lVar15;
    puVar16 = auStack_7e0 + lVar15;
    do {
      uVar23 = (1 << (ulong)(uVar13 & 0x1f)) - 1;
      if (0x1f < uVar13) {
        uVar23 = 0xffffffff;
      }
      lVar18 = lVar18 + -1;
      *puVar16 = uVar23;
      uVar13 = uVar13 - 0x20;
      puVar16 = puVar16 + 1;
    } while (lVar18 != 0);
  }
code_r0x024476f8:
  lVar15 = 0;
  uVar26 = uVar24 & 0xfffffff8;
code_r0x02447730:
  do {
    lVar18 = (long)(int)lVar15;
    if (*(char *)(param_2 + 0x78) == '\0') {
      lVar14 = 0;
    }
    else {
      lVar14 = *(long *)(param_2 + 0x70);
    }
    alStack_9d8[lVar18 + 3] = lVar14;
    if ((((*(float *)(param_2 + 0x30) <= *(float *)(param_1 + 8)) &&
         (*(float *)(param_2 + 0x38) <= *(float *)(param_1 + 0x10))) &&
        (*(float *)(param_1 + 4) <= *(float *)(param_2 + 0x40))) &&
       ((*(float *)(param_1 + 0xc) <= *(float *)(param_2 + 0x48) && (uVar2 != 0)))) {
      bVar11 = false;
      uVar23 = *(uint *)(param_1 + 0x20);
      uVar27 = 0;
      puVar28 = (undefined4 *)(*(long *)(param_1 + 0x18) + 8);
      do {
        puVar16 = auStack_7e0 + lVar18 * 8 + uVar27;
        uVar13 = *puVar16;
        if (uVar13 != 0) {
          uVar31 = uVar23;
          if (0x1f < uVar23) {
            uVar31 = 0x20;
          }
          if (uVar31 != 0) {
            uVar25 = 0;
            puVar29 = puVar28;
            do {
              uVar32 = 1 << (ulong)((uint)uVar25 & 0x1f);
              if ((uVar32 & uVar13) != 0) {
                uVar1 = *puVar29;
                *(undefined8 *)(param_1 + 0x30) = *(undefined8 *)(puVar29 + -2);
                *(undefined4 *)(param_1 + 0x38) = uVar1;
                *(undefined4 *)(param_1 + 0x3c) = 0x3f800000;
                uVar12 = Aska::Collision::Intersect(Aska::AABB_MinMax const*, Aska::Ray const*)(param_2 + 0x30,param_1 + 0x30);
                if ((uVar12 & 1) == 0) {
                  uVar13 = *puVar16 & (uVar32 ^ 0xffffffff);
                }
                else {
                  bVar11 = true;
                  uVar13 = *puVar16 | uVar32;
                }
                *puVar16 = uVar13;
              }
              uVar25 = uVar25 + 1;
              puVar29 = puVar29 + 4;
            } while (uVar25 < uVar31);
          }
        }
        uVar27 = uVar27 + 1;
        uVar23 = uVar23 - 0x20;
        puVar28 = puVar28 + 0x80;
      } while (uVar27 != uVar24);
      if (bVar11) {
        if ((*(char *)(param_2 + 0x79) != '\0') &&
           (uVar27 = bool Aska::IDE_CollisionDetectionParam<(Aska::_Enum_IDECollisionDetectionInputType)2, (Aska::_Enum_IDECollisionDetectionOutputType)3>::CheckCollisionDetection<false>(unsigned int*, unsigned int, Aska::IDEPrimitiveBase*)(param_1,auStack_7e0 + lVar18 * 8,uVar2,param_2),
           (uVar27 & 1) != 0)) {
          return;
        }
        if (((int)lVar15 < 0x3b) && (lVar14 != 0)) {
          alStack_9d8[lVar18 + 3] = *(long *)(lVar14 + 0x68);
          lVar15 = lVar18 + 1;
          uVar27 = 0;
          param_2 = lVar14;
          if ((7 < uVar24) && (uVar26 != 0)) {
            if ((auStack_7e0 + lVar15 * 8 < auStack_7e0 + uVar24 + lVar18 * 8) &&
               (auStack_7e0 + lVar18 * 8 < auStack_7e0 + uVar24 + lVar15 * 8)) {
              uVar27 = 0;
            }
            else {
              puVar17 = auStack_7d8 + lVar18 * 4 + 1;
              puVar20 = auStack_7d8 + lVar15 * 4 + 1;
              uVar27 = uVar26;
              do {
                puVar3 = puVar17 + -1;
                uVar30 = puVar17[-2];
                uVar5 = puVar17[1];
                uVar4 = *puVar17;
                puVar17 = puVar17 + 4;
                uVar27 = uVar27 - 8;
                puVar20[-1] = *puVar3;
                puVar20[-2] = uVar30;
                puVar20[1] = uVar5;
                *puVar20 = uVar4;
                puVar20 = puVar20 + 4;
              } while (uVar27 != 0);
              uVar27 = uVar26;
              if (uVar24 == uVar26) goto code_r0x02447730;
            }
          }
          lVar14 = uVar24 - uVar27;
          puVar16 = auStack_7e0 + lVar18 * 8 + uVar27;
          puVar19 = auStack_7e0 + lVar15 * 8 + uVar27;
          do {
            lVar14 = lVar14 + -1;
            *puVar19 = *puVar16;
            puVar16 = puVar16 + 1;
            puVar19 = puVar19 + 1;
          } while (lVar14 != 0);
          goto code_r0x02447730;
        }
      }
    }
    puVar17 = auStack_7f0 + lVar18 * 4;
    lVar22 = 0;
    lVar14 = lVar18;
    do {
      lVar15 = lVar14;
      lVar21 = lVar22;
      puVar20 = puVar17;
      lVar14 = lVar15 + -1;
      if (lVar15 < 1) {
        return;
      }
      lVar22 = lVar21 + -0x20;
      puVar17 = puVar20 + -4;
    } while ((0x3b < lVar15) || (param_2 = alStack_9d8[lVar15 + 2], param_2 == 0));
    alStack_9d8[lVar15 + 2] = *(long *)(param_2 + 0x68);
  } while (uVar2 == 0);
  lVar22 = (long)(int)lVar15;
  uVar27 = 0;
  if ((7 < uVar24) && (uVar26 != 0)) {
    if ((auStack_7e0 + lVar22 * 8 < auStack_7e0 + uVar24 + lVar14 * 8) &&
       (auStack_7e0 + lVar14 * 8 <
        (uint *)((long)auStack_7e0 + ((lVar15 << 0x20) >> 0x1b) + uVar24 * 4))) {
      uVar27 = 0;
    }
    else {
      puVar17 = auStack_7d8 + lVar22 * 4 + 1;
      uVar27 = uVar26;
      do {
        puVar3 = puVar20 + -1;
        uVar30 = puVar20[-2];
        uVar5 = puVar20[1];
        uVar4 = *puVar20;
        puVar20 = puVar20 + 4;
        uVar27 = uVar27 - 8;
        puVar17[-1] = *puVar3;
        puVar17[-2] = uVar30;
        puVar17[1] = uVar5;
        *puVar17 = uVar4;
        puVar17 = puVar17 + 4;
      } while (uVar27 != 0);
      uVar27 = uVar26;
      if (uVar24 == uVar26) goto code_r0x02447730;
    }
  }
  lVar14 = uVar24 - uVar27;
  puVar16 = auStack_7e0 + uVar27 + lVar22 * 8;
  puVar19 = (uint *)((long)auStack_800 + lVar21 + (uVar27 + lVar18 * 8) * 4);
  do {
    lVar14 = lVar14 + -1;
    *puVar16 = *puVar19;
    puVar16 = puVar16 + 1;
    puVar19 = puVar19 + 1;
  } while (lVar14 != 0);
  goto code_r0x02447730;
}

// ==== Aska::IDEPrimitiveAABB<(Aska::_EnumIDESpacePartitionType)0>::~IDEPrimitiveAABB()
// vaddr 0x2349ae0 | ghidra 0x2449ae0 | size 20 | symbol _ZN4Aska16IDEPrimitiveAABBILNS_26_EnumIDESpacePartitionTypeE0EED2Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska16IDEPrimitiveAABBILNS_26_EnumIDESpacePartitionTypeE0EED2Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska16IDEPrimitiveAABBILNS_26_EnumIDESpacePartitionTypeE0EEE_02cb7d98
                   + 0x10);
  return;
}

// ==== Aska::IDEPrimitiveAABB<(Aska::_EnumIDESpacePartitionType)0>::~IDEPrimitiveAABB()
// vaddr 0x2349af4 | ghidra 0x2449af4 | size 4 | symbol _ZN4Aska16IDEPrimitiveAABBILNS_26_EnumIDESpacePartitionTypeE0EED0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska16IDEPrimitiveAABBILNS_26_EnumIDESpacePartitionTypeE0EED0Ev(void)

{
  (*(code *)PTR__ZdlPv_02ca4758)();
  return;
}

// ==== Aska::IDEPrimitiveAABB<(Aska::_EnumIDESpacePartitionType)0>::Intersect(Aska::Ray*, unsigned short)
// vaddr 0x2349af8 | ghidra 0x2449af8 | size 8 | symbol _ZN4Aska16IDEPrimitiveAABBILNS_26_EnumIDESpacePartitionTypeE0EE9IntersectEPNS_3RayEt | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska16IDEPrimitiveAABBILNS_26_EnumIDESpacePartitionTypeE0EE9IntersectEPNS_3RayEt
               (long param_1)

{
  (*(code *)PTR__ZN4Aska9Collision9IntersectEPKNS_11AABB_MinMaxEPKNS_3RayE_02caa008)(param_1 + 0x80)
  ;
  return;
}

// ==== Aska::IDEPrimitiveAABB<(Aska::_EnumIDESpacePartitionType)0>::Intersect(Aska::Segment*, unsigned short)
// vaddr 0x2349b00 | ghidra 0x2449b00 | size 8 | symbol _ZN4Aska16IDEPrimitiveAABBILNS_26_EnumIDESpacePartitionTypeE0EE9IntersectEPNS_7SegmentEt | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska16IDEPrimitiveAABBILNS_26_EnumIDESpacePartitionTypeE0EE9IntersectEPNS_7SegmentEt
               (long param_1)

{
  (*(code *)PTR__ZN4Aska9Collision9IntersectEPKNS_11AABB_MinMaxEPKNS_7SegmentE_02c99db0)
            (param_1 + 0x80);
  return;
}

// ==== Aska::IDEPrimitiveAABB<(Aska::_EnumIDESpacePartitionType)0>::FindIntersectNearestPoint(Aska::Vector*, Aska::Ray*, unsigned short)
// vaddr 0x2349b08 | ghidra 0x2449b08 | size 116 | symbol _ZN4Aska16IDEPrimitiveAABBILNS_26_EnumIDESpacePartitionTypeE0EE25FindIntersectNearestPointEPNS_6VectorEPNS_3RayEt | lib libSOA-3.7.0.so | 2026-10-08
bool _ZN4Aska16IDEPrimitiveAABBILNS_26_EnumIDESpacePartitionTypeE0EE25FindIntersectNearestPointEPNS_6VectorEPNS_3RayEt
               (long param_1,undefined4 *param_2,undefined8 param_3)

{
  int iVar1;
  undefined4 *puStack_40;
  undefined1 *puStack_38;
  undefined4 auStack_30 [4];
  undefined1 auStack_20 [16];
  
  puStack_40 = auStack_30;
  puStack_38 = auStack_20;
  iVar1 = Aska::Collision::FindIntersectPoint(Aska::AABB_MinMax const*, Aska::Ray const*, Aska::Vector**)(param_1 + 0x80,param_3,&puStack_40);
  if (0 < iVar1) {
    *param_2 = *puStack_40;
    param_2[1] = puStack_40[1];
    param_2[2] = puStack_40[2];
    param_2[3] = puStack_40[3];
  }
  return 0 < iVar1;
}

// ==== Aska::IDEPrimitiveAABB<(Aska::_EnumIDESpacePartitionType)0>::FindIntersectNearestPoint(Aska::Vector*, Aska::Segment*, unsigned short)
// vaddr 0x2349b7c | ghidra 0x2449b7c | size 116 | symbol _ZN4Aska16IDEPrimitiveAABBILNS_26_EnumIDESpacePartitionTypeE0EE25FindIntersectNearestPointEPNS_6VectorEPNS_7SegmentEt | lib libSOA-3.7.0.so | 2026-10-08
bool _ZN4Aska16IDEPrimitiveAABBILNS_26_EnumIDESpacePartitionTypeE0EE25FindIntersectNearestPointEPNS_6VectorEPNS_7SegmentEt
               (long param_1,undefined4 *param_2,undefined8 param_3)

{
  int iVar1;
  undefined4 *puStack_40;
  undefined1 *puStack_38;
  undefined4 auStack_30 [4];
  undefined1 auStack_20 [16];
  
  puStack_40 = auStack_30;
  puStack_38 = auStack_20;
  iVar1 = Aska::Collision::FindIntersectPoint(Aska::AABB_MinMax const*, Aska::Segment const*, Aska::Vector**)(param_1 + 0x80,param_3,&puStack_40);
  if (0 < iVar1) {
    *param_2 = *puStack_40;
    param_2[1] = puStack_40[1];
    param_2[2] = puStack_40[2];
    param_2[3] = puStack_40[3];
  }
  return 0 < iVar1;
}

// ==== Aska::IDEPrimitiveAABB<(Aska::_EnumIDESpacePartitionType)0>::FindIntersectNearestObject(Aska::IDE_ResultOfNearestObject*, Aska::Ray*, unsigned short)
// vaddr 0x2349bf0 | ghidra 0x2449bf0 | size 136 | symbol _ZN4Aska16IDEPrimitiveAABBILNS_26_EnumIDESpacePartitionTypeE0EE26FindIntersectNearestObjectEPNS_25IDE_ResultOfNearestObjectEPNS_3RayEt | lib libSOA-3.7.0.so | 2026-10-08
bool _ZN4Aska16IDEPrimitiveAABBILNS_26_EnumIDESpacePartitionTypeE0EE26FindIntersectNearestObjectEPNS_25IDE_ResultOfNearestObjectEPNS_3RayEt
               (long param_1,undefined4 *param_2,undefined8 param_3)

{
  int iVar1;
  undefined4 *puStack_50;
  undefined1 *puStack_48;
  undefined4 auStack_40 [4];
  undefined1 auStack_30 [16];
  
  puStack_50 = auStack_40;
  puStack_48 = auStack_30;
  iVar1 = Aska::Collision::FindIntersectPoint(Aska::AABB_MinMax const*, Aska::Ray const*, Aska::Vector**)(param_1 + 0x80,param_3,&puStack_50);
  if (0 < iVar1) {
    *(undefined8 *)(param_2 + 4) = *(undefined8 *)(param_1 + 0x18);
    *param_2 = *puStack_50;
    param_2[1] = puStack_50[1];
    param_2[2] = puStack_50[2];
    param_2[3] = puStack_50[3];
  }
  return 0 < iVar1;
}

// ==== Aska::IDEPrimitiveAABB<(Aska::_EnumIDESpacePartitionType)0>::FindIntersectNearestObject(Aska::IDE_ResultOfNearestObject*, Aska::Segment*, unsigned short)
// vaddr 0x2349c78 | ghidra 0x2449c78 | size 136 | symbol _ZN4Aska16IDEPrimitiveAABBILNS_26_EnumIDESpacePartitionTypeE0EE26FindIntersectNearestObjectEPNS_25IDE_ResultOfNearestObjectEPNS_7SegmentEt | lib libSOA-3.7.0.so | 2026-10-08
bool _ZN4Aska16IDEPrimitiveAABBILNS_26_EnumIDESpacePartitionTypeE0EE26FindIntersectNearestObjectEPNS_25IDE_ResultOfNearestObjectEPNS_7SegmentEt
               (long param_1,undefined4 *param_2,undefined8 param_3)

{
  int iVar1;
  undefined4 *puStack_50;
  undefined1 *puStack_48;
  undefined4 auStack_40 [4];
  undefined1 auStack_30 [16];
  
  puStack_50 = auStack_40;
  puStack_48 = auStack_30;
  iVar1 = Aska::Collision::FindIntersectPoint(Aska::AABB_MinMax const*, Aska::Segment const*, Aska::Vector**)(param_1 + 0x80,param_3,&puStack_50);
  if (0 < iVar1) {
    *(undefined8 *)(param_2 + 4) = *(undefined8 *)(param_1 + 0x18);
    *param_2 = *puStack_50;
    param_2[1] = puStack_50[1];
    param_2[2] = puStack_50[2];
    param_2[3] = puStack_50[3];
  }
  return 0 < iVar1;
}

// ==== Aska::IDEPrimitiveAABB<(Aska::_EnumIDESpacePartitionType)0>::FindIntersectObjects(Aska::INotify*, Aska::Vector const*, unsigned short)
// vaddr 0x2349d00 | ghidra 0x2449d00 | size 96 | symbol _ZN4Aska16IDEPrimitiveAABBILNS_26_EnumIDESpacePartitionTypeE0EE20FindIntersectObjectsEPNS_7INotifyEPKNS_6VectorEt | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska16IDEPrimitiveAABBILNS_26_EnumIDESpacePartitionTypeE0EE20FindIntersectObjectsEPNS_7INotifyEPKNS_6VectorEt
               (long param_1,undefined8 *param_2,undefined8 param_3)

{
  ulong uVar1;
  undefined4 uStack_80;
  undefined8 uStack_7c;
  undefined8 uStack_74;
  undefined8 uStack_6c;
  undefined8 uStack_64;
  
  uVar1 = Aska::Collision::Intersect(Aska::AABB_MinMax const*, Aska::Vector const*)((undefined8 *)(param_1 + 0x80),param_3);
  if ((uVar1 & 1) != 0) {
    uStack_80 = 1;
    uStack_64 = *(undefined8 *)(param_1 + 0x98);
    uStack_6c = *(undefined8 *)(param_1 + 0x90);
    uStack_74 = *(undefined8 *)(param_1 + 0x88);
    uStack_7c = *(undefined8 *)(param_1 + 0x80);
    (**(code **)*param_2)(param_2,&uStack_80);
  }
  return;
}

// ==== Aska::IDEPrimitiveSphere<(Aska::_EnumIDESpacePartitionType)0>::~IDEPrimitiveSphere()
// vaddr 0x2349d60 | ghidra 0x2449d60 | size 20 | symbol _ZN4Aska18IDEPrimitiveSphereILNS_26_EnumIDESpacePartitionTypeE0EED2Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska18IDEPrimitiveSphereILNS_26_EnumIDESpacePartitionTypeE0EED2Ev(long *param_1)

{
  *param_1 = (long)(
                   PTR__ZTVN4Aska18IDEPrimitiveSphereILNS_26_EnumIDESpacePartitionTypeE0EEE_02cc0c88
                   + 0x10);
  return;
}

// ==== Aska::IDEPrimitiveSphere<(Aska::_EnumIDESpacePartitionType)0>::~IDEPrimitiveSphere()
// vaddr 0x2349d74 | ghidra 0x2449d74 | size 4 | symbol _ZN4Aska18IDEPrimitiveSphereILNS_26_EnumIDESpacePartitionTypeE0EED0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska18IDEPrimitiveSphereILNS_26_EnumIDESpacePartitionTypeE0EED0Ev(void)

{
  (*(code *)PTR__ZdlPv_02ca4758)();
  return;
}

// ==== Aska::IDEPrimitiveSphere<(Aska::_EnumIDESpacePartitionType)0>::Intersect(Aska::Ray*, unsigned short)
// vaddr 0x2349d78 | ghidra 0x2449d78 | size 8 | symbol _ZN4Aska18IDEPrimitiveSphereILNS_26_EnumIDESpacePartitionTypeE0EE9IntersectEPNS_3RayEt | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska18IDEPrimitiveSphereILNS_26_EnumIDESpacePartitionTypeE0EE9IntersectEPNS_3RayEt
               (long param_1)

{
  (*(code *)PTR__ZN4Aska9Collision9IntersectEPKNS_6VectorEPKNS_3RayE_02ca18d8)(param_1 + 0x80);
  return;
}

// ==== Aska::IDEPrimitiveSphere<(Aska::_EnumIDESpacePartitionType)0>::Intersect(Aska::Segment*, unsigned short)
// vaddr 0x2349d80 | ghidra 0x2449d80 | size 12 | symbol _ZN4Aska18IDEPrimitiveSphereILNS_26_EnumIDESpacePartitionTypeE0EE9IntersectEPNS_7SegmentEt | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska18IDEPrimitiveSphereILNS_26_EnumIDESpacePartitionTypeE0EE9IntersectEPNS_7SegmentEt
               (long param_1)

{
  (*(code *)PTR__ZN4Aska9Collision9IntersectEPKNS_6VectorEPKNS_7SegmentEf_02c90498)
            (0,param_1 + 0x80);
  return;
}

// ==== Aska::IDEPrimitiveSphere<(Aska::_EnumIDESpacePartitionType)0>::FindIntersectNearestPoint(Aska::Vector*, Aska::Ray*, unsigned short)
// vaddr 0x2349d8c | ghidra 0x2449d8c | size 116 | symbol _ZN4Aska18IDEPrimitiveSphereILNS_26_EnumIDESpacePartitionTypeE0EE25FindIntersectNearestPointEPNS_6VectorEPNS_3RayEt | lib libSOA-3.7.0.so | 2026-10-08
bool _ZN4Aska18IDEPrimitiveSphereILNS_26_EnumIDESpacePartitionTypeE0EE25FindIntersectNearestPointEPNS_6VectorEPNS_3RayEt
               (long param_1,undefined4 *param_2,undefined8 param_3)

{
  int iVar1;
  undefined4 *puStack_40;
  undefined1 *puStack_38;
  undefined4 auStack_30 [4];
  undefined1 auStack_20 [16];
  
  puStack_40 = auStack_30;
  puStack_38 = auStack_20;
  iVar1 = Aska::Collision::FindIntersectPoint(Aska::Vector const*, Aska::Ray const*, Aska::Vector**)(param_1 + 0x80,param_3,&puStack_40);
  if (0 < iVar1) {
    *param_2 = *puStack_40;
    param_2[1] = puStack_40[1];
    param_2[2] = puStack_40[2];
    param_2[3] = puStack_40[3];
  }
  return 0 < iVar1;
}

// ==== Aska::IDEPrimitiveSphere<(Aska::_EnumIDESpacePartitionType)0>::FindIntersectNearestPoint(Aska::Vector*, Aska::Segment*, unsigned short)
// vaddr 0x2349e00 | ghidra 0x2449e00 | size 116 | symbol _ZN4Aska18IDEPrimitiveSphereILNS_26_EnumIDESpacePartitionTypeE0EE25FindIntersectNearestPointEPNS_6VectorEPNS_7SegmentEt | lib libSOA-3.7.0.so | 2026-10-08
bool _ZN4Aska18IDEPrimitiveSphereILNS_26_EnumIDESpacePartitionTypeE0EE25FindIntersectNearestPointEPNS_6VectorEPNS_7SegmentEt
               (long param_1,undefined4 *param_2,undefined8 param_3)

{
  int iVar1;
  undefined4 *puStack_40;
  undefined1 *puStack_38;
  undefined4 auStack_30 [4];
  undefined1 auStack_20 [16];
  
  puStack_40 = auStack_30;
  puStack_38 = auStack_20;
  iVar1 = Aska::Collision::FindIntersectPoint(Aska::Vector const*, Aska::Segment const*, Aska::Vector**)(param_1 + 0x80,param_3,&puStack_40);
  if (0 < iVar1) {
    *param_2 = *puStack_40;
    param_2[1] = puStack_40[1];
    param_2[2] = puStack_40[2];
    param_2[3] = puStack_40[3];
  }
  return 0 < iVar1;
}

// ==== Aska::IDEPrimitiveSphere<(Aska::_EnumIDESpacePartitionType)0>::FindIntersectNearestObject(Aska::IDE_ResultOfNearestObject*, Aska::Ray*, unsigned short)
// vaddr 0x2349e74 | ghidra 0x2449e74 | size 136 | symbol _ZN4Aska18IDEPrimitiveSphereILNS_26_EnumIDESpacePartitionTypeE0EE26FindIntersectNearestObjectEPNS_25IDE_ResultOfNearestObjectEPNS_3RayEt | lib libSOA-3.7.0.so | 2026-10-08
bool _ZN4Aska18IDEPrimitiveSphereILNS_26_EnumIDESpacePartitionTypeE0EE26FindIntersectNearestObjectEPNS_25IDE_ResultOfNearestObjectEPNS_3RayEt
               (long param_1,undefined4 *param_2,undefined8 param_3)

{
  int iVar1;
  undefined4 *puStack_50;
  undefined1 *puStack_48;
  undefined4 auStack_40 [4];
  undefined1 auStack_30 [16];
  
  puStack_50 = auStack_40;
  puStack_48 = auStack_30;
  iVar1 = Aska::Collision::FindIntersectPoint(Aska::Vector const*, Aska::Ray const*, Aska::Vector**)(param_1 + 0x80,param_3,&puStack_50);
  if (0 < iVar1) {
    *(undefined8 *)(param_2 + 4) = *(undefined8 *)(param_1 + 0x18);
    *param_2 = *puStack_50;
    param_2[1] = puStack_50[1];
    param_2[2] = puStack_50[2];
    param_2[3] = puStack_50[3];
  }
  return 0 < iVar1;
}

// ==== Aska::IDEPrimitiveSphere<(Aska::_EnumIDESpacePartitionType)0>::FindIntersectNearestObject(Aska::IDE_ResultOfNearestObject*, Aska::Segment*, unsigned short)
// vaddr 0x2349efc | ghidra 0x2449efc | size 136 | symbol _ZN4Aska18IDEPrimitiveSphereILNS_26_EnumIDESpacePartitionTypeE0EE26FindIntersectNearestObjectEPNS_25IDE_ResultOfNearestObjectEPNS_7SegmentEt | lib libSOA-3.7.0.so | 2026-10-08
bool _ZN4Aska18IDEPrimitiveSphereILNS_26_EnumIDESpacePartitionTypeE0EE26FindIntersectNearestObjectEPNS_25IDE_ResultOfNearestObjectEPNS_7SegmentEt
               (long param_1,undefined4 *param_2,undefined8 param_3)

{
  int iVar1;
  undefined4 *puStack_50;
  undefined1 *puStack_48;
  undefined4 auStack_40 [4];
  undefined1 auStack_30 [16];
  
  puStack_50 = auStack_40;
  puStack_48 = auStack_30;
  iVar1 = Aska::Collision::FindIntersectPoint(Aska::Vector const*, Aska::Segment const*, Aska::Vector**)(param_1 + 0x80,param_3,&puStack_50);
  if (0 < iVar1) {
    *(undefined8 *)(param_2 + 4) = *(undefined8 *)(param_1 + 0x18);
    *param_2 = *puStack_50;
    param_2[1] = puStack_50[1];
    param_2[2] = puStack_50[2];
    param_2[3] = puStack_50[3];
  }
  return 0 < iVar1;
}

// ==== Aska::IDEPrimitiveSphere<(Aska::_EnumIDESpacePartitionType)0>::FindIntersectObjects(Aska::INotify*, Aska::Vector const*, unsigned short)
// vaddr 0x2349f84 | ghidra 0x2449f84 | size 88 | symbol _ZN4Aska18IDEPrimitiveSphereILNS_26_EnumIDESpacePartitionTypeE0EE20FindIntersectObjectsEPNS_7INotifyEPKNS_6VectorEt | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska18IDEPrimitiveSphereILNS_26_EnumIDESpacePartitionTypeE0EE20FindIntersectObjectsEPNS_7INotifyEPKNS_6VectorEt
               (long param_1,undefined8 *param_2,undefined8 param_3)

{
  ulong uVar1;
  undefined4 uStack_80;
  undefined8 uStack_7c;
  undefined8 uStack_74;
  
  uVar1 = Aska::Collision::Intersect(Aska::Vector const*, Aska::Vector const*)((undefined8 *)(param_1 + 0x80),param_3);
  if ((uVar1 & 1) != 0) {
    uStack_80 = 2;
    uStack_74 = *(undefined8 *)(param_1 + 0x88);
    uStack_7c = *(undefined8 *)(param_1 + 0x80);
    (**(code **)*param_2)(param_2,&uStack_80);
  }
  return;
}

// ==== Aska::IDEPrimitiveHeightObject<(Aska::_EnumIDESpacePartitionType)0>::~IDEPrimitiveHeightObject()
// vaddr 0x2349fdc | ghidra 0x2449fdc | size 4 | symbol _ZN4Aska24IDEPrimitiveHeightObjectILNS_26_EnumIDESpacePartitionTypeE0EED0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska24IDEPrimitiveHeightObjectILNS_26_EnumIDESpacePartitionTypeE0EED0Ev(void)

{
  (*(code *)PTR__ZdlPv_02ca4758)();
  return;
}

// ==== Aska::IDEPrimitiveHeightObject<(Aska::_EnumIDESpacePartitionType)0>::CheckToDispatch(Aska::Ray*, unsigned short)
// vaddr 0x2349fe0 | ghidra 0x2449fe0 | size 24 | symbol _ZN4Aska24IDEPrimitiveHeightObjectILNS_26_EnumIDESpacePartitionTypeE0EE15CheckToDispatchEPNS_3RayEt | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska24IDEPrimitiveHeightObjectILNS_26_EnumIDESpacePartitionTypeE0EE15CheckToDispatchEPNS_3RayEt
          (long param_1,undefined8 param_2,short param_3)

{
  undefined8 uVar1;
  
  if (param_3 != 0) {
    uVar1 = (*(code *)PTR__ZN4Aska9Collision9IntersectEPKNS_4AABBEPKNS_3RayE_02cb1850)
                      (param_1 + 0x90);
    return uVar1;
  }
  return 0;
}

// ==== Aska::IDEPrimitiveHeightObject<(Aska::_EnumIDESpacePartitionType)0>::CheckToDispatch(Aska::Segment*, unsigned short)
// vaddr 0x2349ff8 | ghidra 0x2449ff8 | size 24 | symbol _ZN4Aska24IDEPrimitiveHeightObjectILNS_26_EnumIDESpacePartitionTypeE0EE15CheckToDispatchEPNS_7SegmentEt | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska24IDEPrimitiveHeightObjectILNS_26_EnumIDESpacePartitionTypeE0EE15CheckToDispatchEPNS_7SegmentEt
          (long param_1,undefined8 param_2,short param_3)

{
  undefined8 uVar1;
  
  if (param_3 != 0) {
    uVar1 = (*(code *)PTR__ZN4Aska9Collision9IntersectEPKNS_4AABBEPKNS_7SegmentE_02c947e0)
                      (param_1 + 0x90);
    return uVar1;
  }
  return 0;
}

// ==== Aska::IDEPrimitiveHeightObject<(Aska::_EnumIDESpacePartitionType)0>::CheckToDispatch(Aska::Box const*, unsigned short)
// vaddr 0x234a010 | ghidra 0x244a010 | size 12 | symbol _ZN4Aska24IDEPrimitiveHeightObjectILNS_26_EnumIDESpacePartitionTypeE0EE15CheckToDispatchEPKNS_3BoxEt | lib libSOA-3.7.0.so | 2026-10-08
bool _ZN4Aska24IDEPrimitiveHeightObjectILNS_26_EnumIDESpacePartitionTypeE0EE15CheckToDispatchEPKNS_3BoxEt
               (undefined8 param_1,undefined8 param_2,short param_3)

{
  return param_3 != 0;
}

// ==== Aska::IDEPrimitiveHeightObject<(Aska::_EnumIDESpacePartitionType)0>::Update()
// vaddr 0x234a01c | ghidra 0x244a01c | size 136 | symbol _ZN4Aska24IDEPrimitiveHeightObjectILNS_26_EnumIDESpacePartitionTypeE0EE6UpdateEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska24IDEPrimitiveHeightObjectILNS_26_EnumIDESpacePartitionTypeE0EE6UpdateEv(long param_1)

{
  undefined4 uVar1;
  long lVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  
  Aska::HeightObject::UpdateMinMax()(*(undefined8 *)(param_1 + 0x80));
  lVar2 = *(long *)(param_1 + 0x80);
  fVar3 = *(float *)(lVar2 + 0x1c0);
  fVar4 = *(float *)(lVar2 + 0x1d0);
  fVar5 = *(float *)(lVar2 + 0x1c4);
  fVar6 = *(float *)(lVar2 + 0x1d4);
  fVar7 = *(float *)(lVar2 + 0x1c8);
  fVar8 = *(float *)(lVar2 + 0x1d8);
  uVar1 = *(undefined4 *)(lVar2 + 0x1dc);
  *(undefined4 *)(param_1 + 0x9c) = 0x3f800000;
  *(float *)(param_1 + 0x90) = (fVar3 + fVar4) * 0.5;
  *(float *)(param_1 + 0x94) = (fVar5 + fVar6) * 0.5;
  *(float *)(param_1 + 0x98) = (fVar7 + fVar8) * 0.5;
  *(float *)(param_1 + 0xa0) = (fVar4 - fVar3) * 0.5;
  *(float *)(param_1 + 0xa4) = (fVar6 - fVar5) * 0.5;
  *(float *)(param_1 + 0xa8) = (fVar8 - fVar7) * 0.5;
  *(undefined4 *)(param_1 + 0xac) = uVar1;
  return;
}

// ==== Aska::IDEPrimitiveHeightObject<(Aska::_EnumIDESpacePartitionType)0>::Intersect(Aska::Ray*, unsigned short)
// vaddr 0x234a0a4 | ghidra 0x244a0a4 | size 52 | symbol _ZN4Aska24IDEPrimitiveHeightObjectILNS_26_EnumIDESpacePartitionTypeE0EE9IntersectEPNS_3RayEt | lib libSOA-3.7.0.so | 2026-10-08
uint _ZN4Aska24IDEPrimitiveHeightObjectILNS_26_EnumIDESpacePartitionTypeE0EE9IntersectEPNS_3RayEt
               (long param_1)

{
  uint uVar1;
  
  uVar1 = (**(code **)(**(long **)(param_1 + 0x80) + 0x168))();
  return uVar1 & 1;
}

// ==== Aska::IDEPrimitiveHeightObject<(Aska::_EnumIDESpacePartitionType)0>::Intersect(Aska::Segment*, unsigned short)
// vaddr 0x234a0d8 | ghidra 0x244a0d8 | size 52 | symbol _ZN4Aska24IDEPrimitiveHeightObjectILNS_26_EnumIDESpacePartitionTypeE0EE9IntersectEPNS_7SegmentEt | lib libSOA-3.7.0.so | 2026-10-08
uint _ZN4Aska24IDEPrimitiveHeightObjectILNS_26_EnumIDESpacePartitionTypeE0EE9IntersectEPNS_7SegmentEt
               (long param_1)

{
  uint uVar1;
  
  uVar1 = (**(code **)(**(long **)(param_1 + 0x80) + 0x170))();
  return uVar1 & 1;
}

// ==== Aska::IDEPrimitiveHeightObject<(Aska::_EnumIDESpacePartitionType)0>::FindIntersectNearestPoint(Aska::Vector*, Aska::Ray*, unsigned short)
// vaddr 0x234a10c | ghidra 0x244a10c | size 40 | symbol _ZN4Aska24IDEPrimitiveHeightObjectILNS_26_EnumIDESpacePartitionTypeE0EE25FindIntersectNearestPointEPNS_6VectorEPNS_3RayEt | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska24IDEPrimitiveHeightObjectILNS_26_EnumIDESpacePartitionTypeE0EE25FindIntersectNearestPointEPNS_6VectorEPNS_3RayEt
               (long param_1,undefined8 param_2,undefined8 param_3,undefined4 param_4)

{
                    /* WARNING: Could not recover jumptable at 0x0244a130. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(**(long **)(param_1 + 0x80) + 0x168))
            (*(long **)(param_1 + 0x80),param_3,param_4,param_2,0,0);
  return;
}

// ==== Aska::IDEPrimitiveHeightObject<(Aska::_EnumIDESpacePartitionType)0>::FindIntersectNearestPoint(Aska::Vector*, Aska::Segment*, unsigned short)
// vaddr 0x234a134 | ghidra 0x244a134 | size 40 | symbol _ZN4Aska24IDEPrimitiveHeightObjectILNS_26_EnumIDESpacePartitionTypeE0EE25FindIntersectNearestPointEPNS_6VectorEPNS_7SegmentEt | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska24IDEPrimitiveHeightObjectILNS_26_EnumIDESpacePartitionTypeE0EE25FindIntersectNearestPointEPNS_6VectorEPNS_7SegmentEt
               (long param_1,undefined8 param_2,undefined8 param_3,undefined4 param_4)

{
                    /* WARNING: Could not recover jumptable at 0x0244a158. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(**(long **)(param_1 + 0x80) + 0x170))
            (*(long **)(param_1 + 0x80),param_3,param_4,param_2,0,0);
  return;
}

// ==== Aska::IDEPrimitiveHeightObject<(Aska::_EnumIDESpacePartitionType)0>::FindIntersectNearestObject(Aska::IDE_ResultOfNearestObject*, Aska::Ray*, unsigned short)
// vaddr 0x234a15c | ghidra 0x244a15c | size 88 | symbol _ZN4Aska24IDEPrimitiveHeightObjectILNS_26_EnumIDESpacePartitionTypeE0EE26FindIntersectNearestObjectEPNS_25IDE_ResultOfNearestObjectEPNS_3RayEt | lib libSOA-3.7.0.so | 2026-10-08
bool _ZN4Aska24IDEPrimitiveHeightObjectILNS_26_EnumIDESpacePartitionTypeE0EE26FindIntersectNearestObjectEPNS_25IDE_ResultOfNearestObjectEPNS_3RayEt
               (long param_1,long param_2,undefined8 param_3,undefined4 param_4)

{
  bool bVar1;
  ulong uVar2;
  
  uVar2 = (**(code **)(**(long **)(param_1 + 0x80) + 0x168))
                    (*(long **)(param_1 + 0x80),param_3,param_4,param_2,param_2 + 0x30,
                     param_2 + 0x38);
  bVar1 = (uVar2 & 1) != 0;
  if (bVar1) {
    *(undefined8 *)(param_2 + 0x10) = *(undefined8 *)(param_1 + 0x18);
  }
  return bVar1;
}

// ==== Aska::IDEPrimitiveHeightObject<(Aska::_EnumIDESpacePartitionType)0>::FindIntersectNearestObject(Aska::IDE_ResultOfNearestObject*, Aska::Segment*, unsigned short)
// vaddr 0x234a1b4 | ghidra 0x244a1b4 | size 88 | symbol _ZN4Aska24IDEPrimitiveHeightObjectILNS_26_EnumIDESpacePartitionTypeE0EE26FindIntersectNearestObjectEPNS_25IDE_ResultOfNearestObjectEPNS_7SegmentEt | lib libSOA-3.7.0.so | 2026-10-08
bool _ZN4Aska24IDEPrimitiveHeightObjectILNS_26_EnumIDESpacePartitionTypeE0EE26FindIntersectNearestObjectEPNS_25IDE_ResultOfNearestObjectEPNS_7SegmentEt
               (long param_1,long param_2,undefined8 param_3,undefined4 param_4)

{
  bool bVar1;
  ulong uVar2;
  
  uVar2 = (**(code **)(**(long **)(param_1 + 0x80) + 0x170))
                    (*(long **)(param_1 + 0x80),param_3,param_4,param_2,param_2 + 0x30,
                     param_2 + 0x38);
  bVar1 = (uVar2 & 1) != 0;
  if (bVar1) {
    *(undefined8 *)(param_2 + 0x10) = *(undefined8 *)(param_1 + 0x18);
  }
  return bVar1;
}

// ==== Aska::IDEPrimitiveHeightObject<(Aska::_EnumIDESpacePartitionType)0>::FindIntersectObjects(Aska::INotify*, Aska::Vector const*, unsigned short)
// vaddr 0x234a20c | ghidra 0x244a20c | size 16 | symbol _ZN4Aska24IDEPrimitiveHeightObjectILNS_26_EnumIDESpacePartitionTypeE0EE20FindIntersectObjectsEPNS_7INotifyEPKNS_6VectorEt | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska24IDEPrimitiveHeightObjectILNS_26_EnumIDESpacePartitionTypeE0EE20FindIntersectObjectsEPNS_7INotifyEPKNS_6VectorEt
               (long param_1)

{
                    /* WARNING: Could not recover jumptable at 0x0244a218. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(**(long **)(param_1 + 0x80) + 400))();
  return;
}

// ==== Aska::IDEPrimitiveHeightObject<(Aska::_EnumIDESpacePartitionType)0>::CheckToDispatch(Aska::Vector*, unsigned short)
// vaddr 0x234a21c | ghidra 0x244a21c | size 24 | symbol _ZN4Aska24IDEPrimitiveHeightObjectILNS_26_EnumIDESpacePartitionTypeE0EE15CheckToDispatchEPNS_6VectorEt | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska24IDEPrimitiveHeightObjectILNS_26_EnumIDESpacePartitionTypeE0EE15CheckToDispatchEPNS_6VectorEt
          (long param_1,undefined8 param_2,short param_3)

{
  undefined8 uVar1;
  
  if (param_3 != 0) {
    uVar1 = (*(code *)PTR__ZN4Aska9Collision9IntersectEPKNS_4AABBEPKNS_6VectorE_02ca5270)
                      (param_1 + 0x90);
    return uVar1;
  }
  return 0;
}

// ==== Aska::IDEPrimitiveCollisionHandler<(Aska::_EnumIDESpacePartitionType)0>::~IDEPrimitiveCollisionHandler()
// vaddr 0x234a234 | ghidra 0x244a234 | size 4 | symbol _ZN4Aska28IDEPrimitiveCollisionHandlerILNS_26_EnumIDESpacePartitionTypeE0EED0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska28IDEPrimitiveCollisionHandlerILNS_26_EnumIDESpacePartitionTypeE0EED0Ev(void)

{
  (*(code *)PTR__ZdlPv_02ca4758)();
  return;
}

// ==== Aska::IDEPrimitiveCollisionHandler<(Aska::_EnumIDESpacePartitionType)0>::CheckToDispatch(Aska::Ray*, unsigned short)
// vaddr 0x234a238 | ghidra 0x244a238 | size 24 | symbol _ZN4Aska28IDEPrimitiveCollisionHandlerILNS_26_EnumIDESpacePartitionTypeE0EE15CheckToDispatchEPNS_3RayEt | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska28IDEPrimitiveCollisionHandlerILNS_26_EnumIDESpacePartitionTypeE0EE15CheckToDispatchEPNS_3RayEt
          (long param_1,undefined8 param_2,short param_3)

{
  undefined8 uVar1;
  
  if (param_3 != 0) {
    uVar1 = (*(code *)PTR__ZN4Aska9Collision9IntersectEPKNS_6VectorEPKNS_3RayE_02ca18d8)
                      (param_1 + 0x90);
    return uVar1;
  }
  return 0;
}

// ==== Aska::IDEPrimitiveCollisionHandler<(Aska::_EnumIDESpacePartitionType)0>::CheckToDispatch(Aska::Segment*, unsigned short)
// vaddr 0x234a250 | ghidra 0x244a250 | size 24 | symbol _ZN4Aska28IDEPrimitiveCollisionHandlerILNS_26_EnumIDESpacePartitionTypeE0EE15CheckToDispatchEPNS_7SegmentEt | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska28IDEPrimitiveCollisionHandlerILNS_26_EnumIDESpacePartitionTypeE0EE15CheckToDispatchEPNS_7SegmentEt
          (long param_1,undefined8 param_2,short param_3)

{
  undefined8 uVar1;
  
  if (param_3 != 0) {
    uVar1 = (*(code *)PTR__ZN4Aska9Collision9IntersectEPKNS_6VectorEPKNS_7SegmentE_02c96be8)
                      (param_1 + 0x90);
    return uVar1;
  }
  return 0;
}

// ==== Aska::IDEPrimitiveCollisionHandler<(Aska::_EnumIDESpacePartitionType)0>::CheckToDispatch(Aska::Box const*, unsigned short)
// vaddr 0x234a268 | ghidra 0x244a268 | size 12 | symbol _ZN4Aska28IDEPrimitiveCollisionHandlerILNS_26_EnumIDESpacePartitionTypeE0EE15CheckToDispatchEPKNS_3BoxEt | lib libSOA-3.7.0.so | 2026-10-08
bool _ZN4Aska28IDEPrimitiveCollisionHandlerILNS_26_EnumIDESpacePartitionTypeE0EE15CheckToDispatchEPKNS_3BoxEt
               (undefined8 param_1,undefined8 param_2,short param_3)

{
  return param_3 != 0;
}

// ==== Aska::IDEPrimitiveCollisionHandler<(Aska::_EnumIDESpacePartitionType)0>::Update()
// vaddr 0x234a274 | ghidra 0x244a274 | size 164 | symbol _ZN4Aska28IDEPrimitiveCollisionHandlerILNS_26_EnumIDESpacePartitionTypeE0EE6UpdateEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska28IDEPrimitiveCollisionHandlerILNS_26_EnumIDESpacePartitionTypeE0EE6UpdateEv
               (long param_1)

{
  undefined4 uVar1;
  long lVar2;
  undefined4 *puVar3;
  
  Aska::CollisionHandler::MakeMatrix()(*(undefined8 *)(param_1 + 0x80));
  lVar2 = *(long *)(param_1 + 0x80);
  if (*(char *)(lVar2 + 0x55) != '\0') {
    if ((*(short *)(*(long *)(lVar2 + 0x10) + 2) == 0) ||
       (puVar3 = *(undefined4 **)(lVar2 + 0x18), puVar3 == (undefined4 *)0x0)) {
      if (*(short *)(*(long *)(lVar2 + 0x10) + 4) == 0) {
        return;
      }
      puVar3 = *(undefined4 **)(lVar2 + 0x20);
    }
    if (puVar3 != (undefined4 *)0x0) {
      if (*(char *)(puVar3 + 0xc) == '\0') {
        lVar2 = Aska::CollisionHandler::GetObjectLinkedWithBranch(Aska::AcfSphereTreeBranch*) const(lVar2,puVar3);
      }
      else {
        lVar2 = Aska::CollisionHandler::GetObjectLinkedWithLeaf(Aska::AcfSphereTreeLeaf*) const(lVar2,puVar3);
      }
      *(undefined4 *)(param_1 + 0x90) = *puVar3;
      *(undefined4 *)(param_1 + 0x94) = puVar3[1];
      *(undefined4 *)(param_1 + 0x98) = puVar3[2];
      uVar1 = puVar3[3];
      *(undefined4 *)(param_1 + 0x9c) = 0x3f800000;
      Aska::Vector::ApplyMatrix(Aska::Matrix const*)((undefined4 *)(param_1 + 0x90),lVar2 + 0x10);
      *(undefined4 *)(param_1 + 0x9c) = uVar1;
    }
  }
  return;
}

// ==== Aska::IDEPrimitiveCollisionHandler<(Aska::_EnumIDESpacePartitionType)0>::Intersect(Aska::Ray*, unsigned short)
// vaddr 0x234a318 | ghidra 0x244a318 | size 20 | symbol _ZN4Aska28IDEPrimitiveCollisionHandlerILNS_26_EnumIDESpacePartitionTypeE0EE9IntersectEPNS_3RayEt | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska28IDEPrimitiveCollisionHandlerILNS_26_EnumIDESpacePartitionTypeE0EE9IntersectEPNS_3RayEt
               (long param_1,undefined8 param_2,undefined4 param_3)

{
  (*(code *)PTR__ZN4Aska9Collision9IntersectEPKNS_16CollisionHandlerEtPKNS_3RayE_02c90a08)
            (*(undefined8 *)(param_1 + 0x80),param_3,param_2);
  return;
}

// ==== Aska::IDEPrimitiveCollisionHandler<(Aska::_EnumIDESpacePartitionType)0>::Intersect(Aska::Segment*, unsigned short)
// vaddr 0x234a32c | ghidra 0x244a32c | size 24 | symbol _ZN4Aska28IDEPrimitiveCollisionHandlerILNS_26_EnumIDESpacePartitionTypeE0EE9IntersectEPNS_7SegmentEt | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska28IDEPrimitiveCollisionHandlerILNS_26_EnumIDESpacePartitionTypeE0EE9IntersectEPNS_7SegmentEt
               (long param_1,undefined8 param_2,undefined4 param_3)

{
  (*(code *)PTR__ZN4Aska9Collision9IntersectEPKNS_16CollisionHandlerEtPKNS_7SegmentEf_02c9a410)
            (0,*(undefined8 *)(param_1 + 0x80),param_3,param_2);
  return;
}

// ==== Aska::IDEPrimitiveCollisionHandler<(Aska::_EnumIDESpacePartitionType)0>::FindIntersectNearestPoint(Aska::Vector*, Aska::Ray*, unsigned short)
// vaddr 0x234a344 | ghidra 0x244a344 | size 68 | symbol _ZN4Aska28IDEPrimitiveCollisionHandlerILNS_26_EnumIDESpacePartitionTypeE0EE25FindIntersectNearestPointEPNS_6VectorEPNS_3RayEt | lib libSOA-3.7.0.so | 2026-10-08
bool _ZN4Aska28IDEPrimitiveCollisionHandlerILNS_26_EnumIDESpacePartitionTypeE0EE25FindIntersectNearestPointEPNS_6VectorEPNS_3RayEt
               (long param_1,undefined8 *param_2,undefined8 param_3,undefined4 param_4)

{
  bool bVar1;
  ulong uVar2;
  undefined1 auStack_60 [48];
  undefined8 uStack_30;
  undefined8 uStack_28;
  
  uVar2 = Aska::Collision::FindIntersectNearestObject(Aska::CollisionHandler const*, unsigned short, Aska::Ray const*, Aska::CollisionIntersectInfoOne*)(*(undefined8 *)(param_1 + 0x80),param_4,param_3,auStack_60);
  bVar1 = (uVar2 & 1) != 0;
  if (bVar1) {
    param_2[1] = uStack_28;
    *param_2 = uStack_30;
  }
  return bVar1;
}

// ==== Aska::IDEPrimitiveCollisionHandler<(Aska::_EnumIDESpacePartitionType)0>::FindIntersectNearestPoint(Aska::Vector*, Aska::Segment*, unsigned short)
// vaddr 0x234a388 | ghidra 0x244a388 | size 68 | symbol _ZN4Aska28IDEPrimitiveCollisionHandlerILNS_26_EnumIDESpacePartitionTypeE0EE25FindIntersectNearestPointEPNS_6VectorEPNS_7SegmentEt | lib libSOA-3.7.0.so | 2026-10-08
bool _ZN4Aska28IDEPrimitiveCollisionHandlerILNS_26_EnumIDESpacePartitionTypeE0EE25FindIntersectNearestPointEPNS_6VectorEPNS_7SegmentEt
               (long param_1,undefined8 *param_2,undefined8 param_3,undefined4 param_4)

{
  bool bVar1;
  ulong uVar2;
  undefined1 auStack_60 [48];
  undefined8 uStack_30;
  undefined8 uStack_28;
  
  uVar2 = Aska::Collision::FindIntersectNearestObject(Aska::CollisionHandler const*, unsigned short, Aska::Segment const*, Aska::CollisionIntersectInfoOne*)(*(undefined8 *)(param_1 + 0x80),param_4,param_3,auStack_60);
  bVar1 = (uVar2 & 1) != 0;
  if (bVar1) {
    param_2[1] = uStack_28;
    *param_2 = uStack_30;
  }
  return bVar1;
}

// ==== Aska::IDEPrimitiveCollisionHandler<(Aska::_EnumIDESpacePartitionType)0>::FindIntersectNearestObject(Aska::IDE_ResultOfNearestObject*, Aska::Ray*, unsigned short)
// vaddr 0x234a3cc | ghidra 0x244a3cc | size 80 | symbol _ZN4Aska28IDEPrimitiveCollisionHandlerILNS_26_EnumIDESpacePartitionTypeE0EE26FindIntersectNearestObjectEPNS_25IDE_ResultOfNearestObjectEPNS_3RayEt | lib libSOA-3.7.0.so | 2026-10-08
bool _ZN4Aska28IDEPrimitiveCollisionHandlerILNS_26_EnumIDESpacePartitionTypeE0EE26FindIntersectNearestObjectEPNS_25IDE_ResultOfNearestObjectEPNS_3RayEt
               (long param_1,undefined8 *param_2,undefined8 param_3,undefined4 param_4)

{
  bool bVar1;
  ulong uVar2;
  
  uVar2 = Aska::Collision::FindIntersectNearestObject(Aska::CollisionHandler const*, unsigned short, Aska::Ray const*, Aska::CollisionIntersectInfoOne*)(*(undefined8 *)(param_1 + 0x80),param_4,param_3,param_2 + 6);
  bVar1 = (uVar2 & 1) != 0;
  if (bVar1) {
    param_2[2] = *(undefined8 *)(param_1 + 0x18);
    param_2[1] = param_2[0xd];
    *param_2 = param_2[0xc];
  }
  return bVar1;
}

// ==== Aska::IDEPrimitiveCollisionHandler<(Aska::_EnumIDESpacePartitionType)0>::FindIntersectNearestObject(Aska::IDE_ResultOfNearestObject*, Aska::Segment*, unsigned short)
// vaddr 0x234a41c | ghidra 0x244a41c | size 80 | symbol _ZN4Aska28IDEPrimitiveCollisionHandlerILNS_26_EnumIDESpacePartitionTypeE0EE26FindIntersectNearestObjectEPNS_25IDE_ResultOfNearestObjectEPNS_7SegmentEt | lib libSOA-3.7.0.so | 2026-10-08
bool _ZN4Aska28IDEPrimitiveCollisionHandlerILNS_26_EnumIDESpacePartitionTypeE0EE26FindIntersectNearestObjectEPNS_25IDE_ResultOfNearestObjectEPNS_7SegmentEt
               (long param_1,undefined8 *param_2,undefined8 param_3,undefined4 param_4)

{
  bool bVar1;
  ulong uVar2;
  
  uVar2 = Aska::Collision::FindIntersectNearestObject(Aska::CollisionHandler const*, unsigned short, Aska::Segment const*, Aska::CollisionIntersectInfoOne*)(*(undefined8 *)(param_1 + 0x80),param_4,param_3,param_2 + 6);
  bVar1 = (uVar2 & 1) != 0;
  if (bVar1) {
    param_2[2] = *(undefined8 *)(param_1 + 0x18);
    param_2[1] = param_2[0xd];
    *param_2 = param_2[0xc];
  }
  return bVar1;
}

// ==== Aska::IDEPrimitiveCollisionHandler<(Aska::_EnumIDESpacePartitionType)0>::CheckToDispatch(Aska::Vector*, unsigned short)
// vaddr 0x234a46c | ghidra 0x244a46c | size 24 | symbol _ZN4Aska28IDEPrimitiveCollisionHandlerILNS_26_EnumIDESpacePartitionTypeE0EE15CheckToDispatchEPNS_6VectorEt | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska28IDEPrimitiveCollisionHandlerILNS_26_EnumIDESpacePartitionTypeE0EE15CheckToDispatchEPNS_6VectorEt
          (long param_1,undefined8 param_2,short param_3)

{
  undefined8 uVar1;
  
  if (param_3 != 0) {
    uVar1 = (*(code *)PTR__ZN4Aska9Collision9IntersectEPKNS_6VectorES3__02cb50b0)(param_1 + 0x90);
    return uVar1;
  }
  return 0;
}

// ==== void Aska::IDESpacePartitionBVH::CollisionDetection<Aska::IDE_CollisionDetectionParam<(Aska::_Enum_IDECollisionDetectionInputType)0, (Aska::_Enum_IDECollisionDetectionOutputType)0>, true>(Aska::IDE_CollisionDetectionParam<(Aska::_Enum_IDECollisionDetectionInputType)0, (Aska::_Enum_IDECollisionDetectionOutputType)0>*, Aska::IDEPrimitiveBase*)
// vaddr 0x234a484 | ghidra 0x244a484 | size 320 | symbol _ZN4Aska20IDESpacePartitionBVH18CollisionDetectionINS_27IDE_CollisionDetectionParamILNS_36_Enum_IDECollisionDetectionInputTypeE0ELNS_37_Enum_IDECollisionDetectionOutputTypeE0EEELb1EEEvPT_PNS_16IDEPrimitiveBaseE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska20IDESpacePartitionBVH18CollisionDetectionINS_27IDE_CollisionDetectionParamILNS_36_Enum_IDECollisionDetectionInputTypeE0ELNS_37_Enum_IDECollisionDetectionOutputTypeE0EEELb1EEEvPT_PNS_16IDEPrimitiveBaseE
               (undefined2 *param_1,long param_2)

{
  int *piVar1;
  char cVar2;
  bool bVar3;
  ulong uVar4;
  int iVar5;
  long lVar6;
  long lVar7;
  long *plVar8;
  long lVar9;
  long alStack_418 [61];
  long alStack_230 [60];
  
  iVar5 = 0;
  piVar1 = (int *)(param_1 + 0x18);
  alStack_230[0] = param_2;
  do {
    while( true ) {
      plVar8 = (long *)alStack_230[iVar5];
      lVar9 = (long)iVar5;
      if ((char)plVar8[0xf] == '\0') {
        lVar6 = 0;
      }
      else {
        lVar6 = plVar8[0xe];
      }
      alStack_418[lVar9 + 1] = lVar6;
      uVar4 = Aska::Collision::Intersect(Aska::AABB_MinMax const*, Aska::Ray const*)(plVar8 + 6,param_1 + 8);
      if ((uVar4 & 1) != 0) break;
code_r0x0244a56c:
      iVar5 = iVar5 + 1;
      do {
        lVar6 = lVar9;
        if (lVar6 < 1) {
          return;
        }
        iVar5 = iVar5 + -1;
        lVar9 = lVar6 + -1;
      } while ((0x3b < lVar6) || (lVar7 = alStack_418[lVar6], lVar7 == 0));
      lVar9 = *(long *)(lVar7 + 0x68);
      alStack_230[iVar5] = lVar7;
      alStack_418[lVar6] = lVar9;
    }
    if (*(char *)((long)plVar8 + 0x79) != '\0') {
      DataMemoryBarrier(2,3);
      if (*piVar1 != 0) {
        return;
      }
      if (*(char *)((long)plVar8 + 0x22) == '\0') {
        uVar4 = (**(code **)(*plVar8 + 0x38))(plVar8,param_1 + 8,*param_1);
        if ((uVar4 & 1) != 0) {
          do {
            cVar2 = '\x01';
            bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
            if (bVar3) {
              *piVar1 = 1;
              cVar2 = ExclusiveMonitorsStatus();
            }
          } while (cVar2 != '\0');
          return;
        }
      }
      else {
        Aska::IDE_CollisionDetectionParam<(Aska::_Enum_IDECollisionDetectionInputType)0, (Aska::_Enum_IDECollisionDetectionOutputType)0>::Dispatch(Aska::IDEPrimitiveBase*)(param_1,plVar8);
      }
    }
    if ((0x3a < iVar5) || (lVar6 = alStack_418[lVar9 + 1], lVar6 == 0)) goto code_r0x0244a56c;
    alStack_418[lVar9 + 1] = *(long *)(lVar6 + 0x68);
    iVar5 = iVar5 + 1;
    alStack_230[iVar5] = lVar6;
  } while( true );
}

// ==== void Aska::IDESpacePartitionBVH::CollisionDetection<Aska::IDE_CollisionDetectionParam<(Aska::_Enum_IDECollisionDetectionInputType)1, (Aska::_Enum_IDECollisionDetectionOutputType)0>, true>(Aska::IDE_CollisionDetectionParam<(Aska::_Enum_IDECollisionDetectionInputType)1, (Aska::_Enum_IDECollisionDetectionOutputType)0>*, Aska::IDEPrimitiveBase*)
// vaddr 0x234a5c4 | ghidra 0x244a5c4 | size 320 | symbol _ZN4Aska20IDESpacePartitionBVH18CollisionDetectionINS_27IDE_CollisionDetectionParamILNS_36_Enum_IDECollisionDetectionInputTypeE1ELNS_37_Enum_IDECollisionDetectionOutputTypeE0EEELb1EEEvPT_PNS_16IDEPrimitiveBaseE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska20IDESpacePartitionBVH18CollisionDetectionINS_27IDE_CollisionDetectionParamILNS_36_Enum_IDECollisionDetectionInputTypeE1ELNS_37_Enum_IDECollisionDetectionOutputTypeE0EEELb1EEEvPT_PNS_16IDEPrimitiveBaseE
               (undefined2 *param_1,long param_2)

{
  int *piVar1;
  char cVar2;
  bool bVar3;
  ulong uVar4;
  int iVar5;
  long lVar6;
  long lVar7;
  long *plVar8;
  long lVar9;
  long alStack_418 [61];
  long alStack_230 [60];
  
  iVar5 = 0;
  piVar1 = (int *)(param_1 + 0x18);
  alStack_230[0] = param_2;
  do {
    while( true ) {
      plVar8 = (long *)alStack_230[iVar5];
      lVar9 = (long)iVar5;
      if ((char)plVar8[0xf] == '\0') {
        lVar6 = 0;
      }
      else {
        lVar6 = plVar8[0xe];
      }
      alStack_418[lVar9 + 1] = lVar6;
      uVar4 = Aska::Collision::Intersect(Aska::AABB_MinMax const*, Aska::Segment const*)(plVar8 + 6,param_1 + 8);
      if ((uVar4 & 1) != 0) break;
code_r0x0244a6ac:
      iVar5 = iVar5 + 1;
      do {
        lVar6 = lVar9;
        if (lVar6 < 1) {
          return;
        }
        iVar5 = iVar5 + -1;
        lVar9 = lVar6 + -1;
      } while ((0x3b < lVar6) || (lVar7 = alStack_418[lVar6], lVar7 == 0));
      lVar9 = *(long *)(lVar7 + 0x68);
      alStack_230[iVar5] = lVar7;
      alStack_418[lVar6] = lVar9;
    }
    if (*(char *)((long)plVar8 + 0x79) != '\0') {
      DataMemoryBarrier(2,3);
      if (*piVar1 != 0) {
        return;
      }
      if (*(char *)((long)plVar8 + 0x22) == '\0') {
        uVar4 = (**(code **)(*plVar8 + 0x40))(plVar8,param_1 + 8,*param_1);
        if ((uVar4 & 1) != 0) {
          do {
            cVar2 = '\x01';
            bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
            if (bVar3) {
              *piVar1 = 1;
              cVar2 = ExclusiveMonitorsStatus();
            }
          } while (cVar2 != '\0');
          return;
        }
      }
      else {
        Aska::IDE_CollisionDetectionParam<(Aska::_Enum_IDECollisionDetectionInputType)1, (Aska::_Enum_IDECollisionDetectionOutputType)0>::Dispatch(Aska::IDEPrimitiveBase*)(param_1,plVar8);
      }
    }
    if ((0x3a < iVar5) || (lVar6 = alStack_418[lVar9 + 1], lVar6 == 0)) goto code_r0x0244a6ac;
    alStack_418[lVar9 + 1] = *(long *)(lVar6 + 0x68);
    iVar5 = iVar5 + 1;
    alStack_230[iVar5] = lVar6;
  } while( true );
}

// ==== void Aska::IDESpacePartitionBVH::CollisionDetection<Aska::IDE_CollisionDetectionParam<(Aska::_Enum_IDECollisionDetectionInputType)0, (Aska::_Enum_IDECollisionDetectionOutputType)1>, true>(Aska::IDE_CollisionDetectionParam<(Aska::_Enum_IDECollisionDetectionInputType)0, (Aska::_Enum_IDECollisionDetectionOutputType)1>*, Aska::IDEPrimitiveBase*)
// vaddr 0x234a704 | ghidra 0x244a704 | size 396 | symbol _ZN4Aska20IDESpacePartitionBVH18CollisionDetectionINS_27IDE_CollisionDetectionParamILNS_36_Enum_IDECollisionDetectionInputTypeE0ELNS_37_Enum_IDECollisionDetectionOutputTypeE1EEELb1EEEvPT_PNS_16IDEPrimitiveBaseE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska20IDESpacePartitionBVH18CollisionDetectionINS_27IDE_CollisionDetectionParamILNS_36_Enum_IDECollisionDetectionInputTypeE0ELNS_37_Enum_IDECollisionDetectionOutputTypeE1EEELb1EEEvPT_PNS_16IDEPrimitiveBaseE
               (undefined2 *param_1,long param_2)

{
  int *piVar1;
  char cVar2;
  bool bVar3;
  ulong uVar4;
  int iVar5;
  long *plVar6;
  long lVar7;
  long lVar8;
  long lVar9;
  long alStack_438 [61];
  long alStack_250 [60];
  undefined4 uStack_70;
  undefined4 uStack_6c;
  undefined4 uStack_68;
  float fStack_64;
  
  iVar5 = 0;
  piVar1 = (int *)(param_1 + 0x24);
  alStack_250[0] = param_2;
  do {
    while( true ) {
      plVar6 = (long *)alStack_250[iVar5];
      lVar7 = (long)iVar5;
      if ((char)plVar6[0xf] == '\0') {
        lVar8 = 0;
      }
      else {
        lVar8 = plVar6[0xe];
      }
      alStack_438[lVar7 + 1] = lVar8;
      uVar4 = Aska::Collision::Intersect(Aska::AABB_MinMax const*, Aska::Ray const*)(plVar6 + 6,param_1 + 8);
      if ((uVar4 & 1) != 0) break;
code_r0x0244a844:
      iVar5 = iVar5 + 1;
      do {
        lVar8 = lVar7;
        if (lVar8 < 1) {
          return;
        }
        iVar5 = iVar5 + -1;
        lVar7 = lVar8 + -1;
      } while ((0x3b < lVar8) || (lVar9 = alStack_438[lVar8], lVar9 == 0));
      lVar7 = *(long *)(lVar9 + 0x68);
      alStack_250[iVar5] = lVar9;
      alStack_438[lVar8] = lVar7;
    }
    if (*(char *)((long)plVar6 + 0x79) == '\0') {
code_r0x0244a7c8:
      if (iVar5 < 0x3b) goto code_r0x0244a7d0;
      goto code_r0x0244a844;
    }
    if (*(char *)((long)plVar6 + 0x22) == '\0') {
      uVar4 = (**(code **)(*plVar6 + 0x48))(plVar6,&uStack_70,param_1 + 8,*param_1);
      if ((uVar4 & 1) == 0) goto code_r0x0244a7c8;
      do {
        while (*piVar1 != 0) {
          ClearExclusiveLocal();
        }
        cVar2 = '\x01';
        bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
        if (bVar3) {
          *piVar1 = 1;
          cVar2 = ExclusiveMonitorsStatus();
        }
      } while (cVar2 != '\0');
      if (fStack_64 < *(float *)(param_1 + 0x1e)) {
        *(undefined4 *)(param_1 + 0x18) = uStack_70;
        *(undefined4 *)(param_1 + 0x1a) = uStack_6c;
        *(float *)(param_1 + 0x1e) = fStack_64;
        *(undefined1 *)(param_1 + 0x20) = 1;
        *(undefined4 *)(param_1 + 0x1c) = uStack_68;
      }
      do {
        cVar2 = '\x01';
        bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
        if (bVar3) {
          *piVar1 = 0;
          cVar2 = ExclusiveMonitorsStatus();
        }
      } while (cVar2 != '\0');
      lVar8 = alStack_438[lVar7 + 1];
    }
    else {
      Aska::IDE_CollisionDetectionParam<(Aska::_Enum_IDECollisionDetectionInputType)0, (Aska::_Enum_IDECollisionDetectionOutputType)1>::Dispatch(Aska::IDEPrimitiveBase*)(param_1,plVar6);
    }
    if (0x3a < iVar5) goto code_r0x0244a844;
code_r0x0244a7d0:
    if (lVar8 == 0) goto code_r0x0244a844;
    alStack_438[lVar7 + 1] = *(long *)(lVar8 + 0x68);
    iVar5 = iVar5 + 1;
    alStack_250[iVar5] = lVar8;
  } while( true );
}

// ==== void Aska::IDESpacePartitionBVH::CollisionDetection<Aska::IDE_CollisionDetectionParam<(Aska::_Enum_IDECollisionDetectionInputType)1, (Aska::_Enum_IDECollisionDetectionOutputType)1>, true>(Aska::IDE_CollisionDetectionParam<(Aska::_Enum_IDECollisionDetectionInputType)1, (Aska::_Enum_IDECollisionDetectionOutputType)1>*, Aska::IDEPrimitiveBase*)
// vaddr 0x234a890 | ghidra 0x244a890 | size 396 | symbol _ZN4Aska20IDESpacePartitionBVH18CollisionDetectionINS_27IDE_CollisionDetectionParamILNS_36_Enum_IDECollisionDetectionInputTypeE1ELNS_37_Enum_IDECollisionDetectionOutputTypeE1EEELb1EEEvPT_PNS_16IDEPrimitiveBaseE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska20IDESpacePartitionBVH18CollisionDetectionINS_27IDE_CollisionDetectionParamILNS_36_Enum_IDECollisionDetectionInputTypeE1ELNS_37_Enum_IDECollisionDetectionOutputTypeE1EEELb1EEEvPT_PNS_16IDEPrimitiveBaseE
               (undefined2 *param_1,long param_2)

{
  int *piVar1;
  char cVar2;
  bool bVar3;
  ulong uVar4;
  int iVar5;
  long *plVar6;
  long lVar7;
  long lVar8;
  long lVar9;
  long alStack_438 [61];
  long alStack_250 [60];
  undefined4 uStack_70;
  undefined4 uStack_6c;
  undefined4 uStack_68;
  float fStack_64;
  
  iVar5 = 0;
  piVar1 = (int *)(param_1 + 0x24);
  alStack_250[0] = param_2;
  do {
    while( true ) {
      plVar6 = (long *)alStack_250[iVar5];
      lVar7 = (long)iVar5;
      if ((char)plVar6[0xf] == '\0') {
        lVar8 = 0;
      }
      else {
        lVar8 = plVar6[0xe];
      }
      alStack_438[lVar7 + 1] = lVar8;
      uVar4 = Aska::Collision::Intersect(Aska::AABB_MinMax const*, Aska::Segment const*)(plVar6 + 6,param_1 + 8);
      if ((uVar4 & 1) != 0) break;
code_r0x0244a9d0:
      iVar5 = iVar5 + 1;
      do {
        lVar8 = lVar7;
        if (lVar8 < 1) {
          return;
        }
        iVar5 = iVar5 + -1;
        lVar7 = lVar8 + -1;
      } while ((0x3b < lVar8) || (lVar9 = alStack_438[lVar8], lVar9 == 0));
      lVar7 = *(long *)(lVar9 + 0x68);
      alStack_250[iVar5] = lVar9;
      alStack_438[lVar8] = lVar7;
    }
    if (*(char *)((long)plVar6 + 0x79) == '\0') {
code_r0x0244a954:
      if (iVar5 < 0x3b) goto code_r0x0244a95c;
      goto code_r0x0244a9d0;
    }
    if (*(char *)((long)plVar6 + 0x22) == '\0') {
      uVar4 = (**(code **)(*plVar6 + 0x50))(plVar6,&uStack_70,param_1 + 8,*param_1);
      if ((uVar4 & 1) == 0) goto code_r0x0244a954;
      do {
        while (*piVar1 != 0) {
          ClearExclusiveLocal();
        }
        cVar2 = '\x01';
        bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
        if (bVar3) {
          *piVar1 = 1;
          cVar2 = ExclusiveMonitorsStatus();
        }
      } while (cVar2 != '\0');
      if (fStack_64 < *(float *)(param_1 + 0x1e)) {
        *(undefined4 *)(param_1 + 0x18) = uStack_70;
        *(undefined4 *)(param_1 + 0x1a) = uStack_6c;
        *(float *)(param_1 + 0x1e) = fStack_64;
        *(undefined1 *)(param_1 + 0x20) = 1;
        *(undefined4 *)(param_1 + 0x1c) = uStack_68;
      }
      do {
        cVar2 = '\x01';
        bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
        if (bVar3) {
          *piVar1 = 0;
          cVar2 = ExclusiveMonitorsStatus();
        }
      } while (cVar2 != '\0');
      lVar8 = alStack_438[lVar7 + 1];
    }
    else {
      Aska::IDE_CollisionDetectionParam<(Aska::_Enum_IDECollisionDetectionInputType)1, (Aska::_Enum_IDECollisionDetectionOutputType)1>::Dispatch(Aska::IDEPrimitiveBase*)(param_1,plVar6);
    }
    if (0x3a < iVar5) goto code_r0x0244a9d0;
code_r0x0244a95c:
    if (lVar8 == 0) goto code_r0x0244a9d0;
    alStack_438[lVar7 + 1] = *(long *)(lVar8 + 0x68);
    iVar5 = iVar5 + 1;
    alStack_250[iVar5] = lVar8;
  } while( true );
}

// ==== void Aska::IDESpacePartitionBVH::CollisionDetection<Aska::IDE_CollisionDetectionParam<(Aska::_Enum_IDECollisionDetectionInputType)0, (Aska::_Enum_IDECollisionDetectionOutputType)2>, true>(Aska::IDE_CollisionDetectionParam<(Aska::_Enum_IDECollisionDetectionInputType)0, (Aska::_Enum_IDECollisionDetectionOutputType)2>*, Aska::IDEPrimitiveBase*)
// vaddr 0x234aa1c | ghidra 0x244aa1c | size 428 | symbol _ZN4Aska20IDESpacePartitionBVH18CollisionDetectionINS_27IDE_CollisionDetectionParamILNS_36_Enum_IDECollisionDetectionInputTypeE0ELNS_37_Enum_IDECollisionDetectionOutputTypeE2EEELb1EEEvPT_PNS_16IDEPrimitiveBaseE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska20IDESpacePartitionBVH18CollisionDetectionINS_27IDE_CollisionDetectionParamILNS_36_Enum_IDECollisionDetectionInputTypeE0ELNS_37_Enum_IDECollisionDetectionOutputTypeE2EEELb1EEEvPT_PNS_16IDEPrimitiveBaseE
               (undefined2 *param_1,long param_2)

{
  int *piVar1;
  char cVar2;
  bool bVar3;
  ulong uVar4;
  int iVar5;
  long *plVar6;
  long lVar7;
  long lVar8;
  long lVar9;
  long alStack_4a8 [61];
  long alStack_2c0 [60];
  undefined8 uStack_e0;
  undefined4 uStack_d8;
  float fStack_d4;
  undefined8 uStack_d0;
  undefined8 uStack_c8;
  undefined8 uStack_c0;
  undefined8 uStack_b8;
  undefined8 uStack_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined8 uStack_98;
  undefined8 uStack_90;
  undefined8 uStack_88;
  undefined8 uStack_80;
  undefined8 uStack_78;
  undefined8 uStack_70;
  undefined8 uStack_68;
  
  iVar5 = 0;
  piVar1 = (int *)(param_1 + 0x5a);
  alStack_2c0[0] = param_2;
  do {
    while( true ) {
      plVar6 = (long *)alStack_2c0[iVar5];
      lVar7 = (long)iVar5;
      if ((char)plVar6[0xf] == '\0') {
        lVar8 = 0;
      }
      else {
        lVar8 = plVar6[0xe];
      }
      alStack_4a8[lVar7 + 1] = lVar8;
      uVar4 = Aska::Collision::Intersect(Aska::AABB_MinMax const*, Aska::Ray const*)(plVar6 + 6,param_1 + 8);
      if ((uVar4 & 1) != 0) break;
code_r0x0244ab7c:
      iVar5 = iVar5 + 1;
      do {
        lVar8 = lVar7;
        if (lVar8 < 1) {
          return;
        }
        iVar5 = iVar5 + -1;
        lVar7 = lVar8 + -1;
      } while ((0x3b < lVar8) || (lVar9 = alStack_4a8[lVar8], lVar9 == 0));
      lVar7 = *(long *)(lVar9 + 0x68);
      alStack_2c0[iVar5] = lVar9;
      alStack_4a8[lVar8] = lVar7;
    }
    if (*(char *)((long)plVar6 + 0x79) == '\0') {
code_r0x0244aae0:
      if (iVar5 < 0x3b) goto code_r0x0244aae8;
      goto code_r0x0244ab7c;
    }
    if (*(char *)((long)plVar6 + 0x22) == '\0') {
      uVar4 = (**(code **)(*plVar6 + 0x58))(plVar6,&uStack_e0,param_1 + 8,*param_1);
      if ((uVar4 & 1) == 0) goto code_r0x0244aae0;
      do {
        while (*piVar1 != 0) {
          ClearExclusiveLocal();
        }
        cVar2 = '\x01';
        bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
        if (bVar3) {
          *piVar1 = 1;
          cVar2 = ExclusiveMonitorsStatus();
        }
      } while (cVar2 != '\0');
      if (fStack_d4 < *(float *)(param_1 + 0x1e)) {
        *(ulong *)(param_1 + 0x1c) = CONCAT44(fStack_d4,uStack_d8);
        *(undefined8 *)(param_1 + 0x18) = uStack_e0;
        *(undefined8 *)(param_1 + 0x24) = uStack_c8;
        *(undefined8 *)(param_1 + 0x20) = uStack_d0;
        *(undefined8 *)(param_1 + 0x2c) = uStack_b8;
        *(undefined8 *)(param_1 + 0x28) = uStack_c0;
        *(undefined8 *)(param_1 + 0x34) = uStack_a8;
        *(undefined8 *)(param_1 + 0x30) = uStack_b0;
        *(undefined8 *)(param_1 + 0x3c) = uStack_98;
        *(undefined8 *)(param_1 + 0x38) = uStack_a0;
        *(undefined8 *)(param_1 + 0x44) = uStack_88;
        *(undefined8 *)(param_1 + 0x40) = uStack_90;
        *(undefined8 *)(param_1 + 0x4c) = uStack_78;
        *(undefined8 *)(param_1 + 0x48) = uStack_80;
        *(undefined8 *)(param_1 + 0x54) = uStack_68;
        *(undefined8 *)(param_1 + 0x50) = uStack_70;
      }
      do {
        cVar2 = '\x01';
        bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
        if (bVar3) {
          *piVar1 = 0;
          cVar2 = ExclusiveMonitorsStatus();
        }
      } while (cVar2 != '\0');
      lVar8 = alStack_4a8[lVar7 + 1];
    }
    else {
      Aska::IDE_CollisionDetectionParam<(Aska::_Enum_IDECollisionDetectionInputType)0, (Aska::_Enum_IDECollisionDetectionOutputType)2>::Dispatch(Aska::IDEPrimitiveBase*)(param_1,plVar6);
    }
    if (0x3a < iVar5) goto code_r0x0244ab7c;
code_r0x0244aae8:
    if (lVar8 == 0) goto code_r0x0244ab7c;
    alStack_4a8[lVar7 + 1] = *(long *)(lVar8 + 0x68);
    iVar5 = iVar5 + 1;
    alStack_2c0[iVar5] = lVar8;
  } while( true );
}

// ==== void Aska::IDESpacePartitionBVH::CollisionDetection<Aska::IDE_CollisionDetectionParam<(Aska::_Enum_IDECollisionDetectionInputType)1, (Aska::_Enum_IDECollisionDetectionOutputType)2>, true>(Aska::IDE_CollisionDetectionParam<(Aska::_Enum_IDECollisionDetectionInputType)1, (Aska::_Enum_IDECollisionDetectionOutputType)2>*, Aska::IDEPrimitiveBase*)
// vaddr 0x234abc8 | ghidra 0x244abc8 | size 428 | symbol _ZN4Aska20IDESpacePartitionBVH18CollisionDetectionINS_27IDE_CollisionDetectionParamILNS_36_Enum_IDECollisionDetectionInputTypeE1ELNS_37_Enum_IDECollisionDetectionOutputTypeE2EEELb1EEEvPT_PNS_16IDEPrimitiveBaseE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska20IDESpacePartitionBVH18CollisionDetectionINS_27IDE_CollisionDetectionParamILNS_36_Enum_IDECollisionDetectionInputTypeE1ELNS_37_Enum_IDECollisionDetectionOutputTypeE2EEELb1EEEvPT_PNS_16IDEPrimitiveBaseE
               (undefined2 *param_1,long param_2)

{
  int *piVar1;
  char cVar2;
  bool bVar3;
  ulong uVar4;
  int iVar5;
  long *plVar6;
  long lVar7;
  long lVar8;
  long lVar9;
  long alStack_4a8 [61];
  long alStack_2c0 [60];
  undefined8 uStack_e0;
  undefined4 uStack_d8;
  float fStack_d4;
  undefined8 uStack_d0;
  undefined8 uStack_c8;
  undefined8 uStack_c0;
  undefined8 uStack_b8;
  undefined8 uStack_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined8 uStack_98;
  undefined8 uStack_90;
  undefined8 uStack_88;
  undefined8 uStack_80;
  undefined8 uStack_78;
  undefined8 uStack_70;
  undefined8 uStack_68;
  
  iVar5 = 0;
  piVar1 = (int *)(param_1 + 0x5a);
  alStack_2c0[0] = param_2;
  do {
    while( true ) {
      plVar6 = (long *)alStack_2c0[iVar5];
      lVar7 = (long)iVar5;
      if ((char)plVar6[0xf] == '\0') {
        lVar8 = 0;
      }
      else {
        lVar8 = plVar6[0xe];
      }
      alStack_4a8[lVar7 + 1] = lVar8;
      uVar4 = Aska::Collision::Intersect(Aska::AABB_MinMax const*, Aska::Segment const*)(plVar6 + 6,param_1 + 8);
      if ((uVar4 & 1) != 0) break;
code_r0x0244ad28:
      iVar5 = iVar5 + 1;
      do {
        lVar8 = lVar7;
        if (lVar8 < 1) {
          return;
        }
        iVar5 = iVar5 + -1;
        lVar7 = lVar8 + -1;
      } while ((0x3b < lVar8) || (lVar9 = alStack_4a8[lVar8], lVar9 == 0));
      lVar7 = *(long *)(lVar9 + 0x68);
      alStack_2c0[iVar5] = lVar9;
      alStack_4a8[lVar8] = lVar7;
    }
    if (*(char *)((long)plVar6 + 0x79) == '\0') {
code_r0x0244ac8c:
      if (iVar5 < 0x3b) goto code_r0x0244ac94;
      goto code_r0x0244ad28;
    }
    if (*(char *)((long)plVar6 + 0x22) == '\0') {
      uVar4 = (**(code **)(*plVar6 + 0x60))(plVar6,&uStack_e0,param_1 + 8,*param_1);
      if ((uVar4 & 1) == 0) goto code_r0x0244ac8c;
      do {
        while (*piVar1 != 0) {
          ClearExclusiveLocal();
        }
        cVar2 = '\x01';
        bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
        if (bVar3) {
          *piVar1 = 1;
          cVar2 = ExclusiveMonitorsStatus();
        }
      } while (cVar2 != '\0');
      if (fStack_d4 < *(float *)(param_1 + 0x1e)) {
        *(ulong *)(param_1 + 0x1c) = CONCAT44(fStack_d4,uStack_d8);
        *(undefined8 *)(param_1 + 0x18) = uStack_e0;
        *(undefined8 *)(param_1 + 0x24) = uStack_c8;
        *(undefined8 *)(param_1 + 0x20) = uStack_d0;
        *(undefined8 *)(param_1 + 0x2c) = uStack_b8;
        *(undefined8 *)(param_1 + 0x28) = uStack_c0;
        *(undefined8 *)(param_1 + 0x34) = uStack_a8;
        *(undefined8 *)(param_1 + 0x30) = uStack_b0;
        *(undefined8 *)(param_1 + 0x3c) = uStack_98;
        *(undefined8 *)(param_1 + 0x38) = uStack_a0;
        *(undefined8 *)(param_1 + 0x44) = uStack_88;
        *(undefined8 *)(param_1 + 0x40) = uStack_90;
        *(undefined8 *)(param_1 + 0x4c) = uStack_78;
        *(undefined8 *)(param_1 + 0x48) = uStack_80;
        *(undefined8 *)(param_1 + 0x54) = uStack_68;
        *(undefined8 *)(param_1 + 0x50) = uStack_70;
      }
      do {
        cVar2 = '\x01';
        bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
        if (bVar3) {
          *piVar1 = 0;
          cVar2 = ExclusiveMonitorsStatus();
        }
      } while (cVar2 != '\0');
      lVar8 = alStack_4a8[lVar7 + 1];
    }
    else {
      Aska::IDE_CollisionDetectionParam<(Aska::_Enum_IDECollisionDetectionInputType)1, (Aska::_Enum_IDECollisionDetectionOutputType)2>::Dispatch(Aska::IDEPrimitiveBase*)(param_1,plVar6);
    }
    if (0x3a < iVar5) goto code_r0x0244ad28;
code_r0x0244ac94:
    if (lVar8 == 0) goto code_r0x0244ad28;
    alStack_4a8[lVar7 + 1] = *(long *)(lVar8 + 0x68);
    iVar5 = iVar5 + 1;
    alStack_2c0[iVar5] = lVar8;
  } while( true );
}

// ==== bool Aska::IDE_CollisionDetectionParam<(Aska::_Enum_IDECollisionDetectionInputType)2, (Aska::_Enum_IDECollisionDetectionOutputType)3>::CheckCollisionDetection<false>(unsigned int*, unsigned int, Aska::IDEPrimitiveBase*)
// vaddr 0x234ad74 | ghidra 0x244ad74 | size 416 | symbol _ZN4Aska27IDE_CollisionDetectionParamILNS_36_Enum_IDECollisionDetectionInputTypeE2ELNS_37_Enum_IDECollisionDetectionOutputTypeE3EE23CheckCollisionDetectionILb0EEEbPjjPNS_16IDEPrimitiveBaseE | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska27IDE_CollisionDetectionParamILNS_36_Enum_IDECollisionDetectionInputTypeE2ELNS_37_Enum_IDECollisionDetectionOutputTypeE3EE23CheckCollisionDetectionILb0EEEbPjjPNS_16IDEPrimitiveBaseE
          (undefined2 *param_1,long param_2,uint param_3,long *param_4)

{
  undefined8 *puVar1;
  int *piVar2;
  float *pfVar3;
  uint uVar4;
  undefined4 uVar5;
  char cVar6;
  bool bVar7;
  ulong uVar8;
  uint uVar9;
  long lVar10;
  ulong uVar11;
  ulong uVar12;
  ulong uVar13;
  int iStack_80;
  uint uStack_7c;
  undefined1 auStack_70 [4];
  float fStack_6c;
  
  if (param_3 != 0) {
    iStack_80 = 0;
    lVar10 = *(long *)(param_1 + 0xc);
    uVar11 = 0;
    piVar2 = (int *)(param_1 + 0x30);
    uStack_7c = *(uint *)(param_1 + 0x10);
    do {
      uVar9 = *(uint *)(param_2 + uVar11 * 4);
      if (uVar9 != 0) {
        uVar4 = uStack_7c;
        if (0x1f < uStack_7c) {
          uVar4 = 0x20;
        }
        if (uVar4 != 0) {
          uVar13 = 0;
          while( true ) {
            if ((uVar9 & 1 << (ulong)((uint)uVar13 & 0x1f)) != 0) {
              uVar12 = (ulong)((uint)uVar13 + iStack_80);
              puVar1 = (undefined8 *)(lVar10 + uVar12 * 0x10);
              uVar5 = *(undefined4 *)(puVar1 + 1);
              *(undefined8 *)(param_1 + 0x18) = *puVar1;
              *(undefined4 *)(param_1 + 0x1c) = uVar5;
              *(undefined4 *)(param_1 + 0x1e) = 0x3f800000;
              uVar8 = (**(code **)(*param_4 + 0x10))(param_4,param_1 + 0x18,*param_1);
              if (((uVar8 & 1) != 0) &&
                 (uVar8 = (**(code **)(*param_4 + 0x48))(param_4,auStack_70,param_1 + 0x18,*param_1)
                 , (uVar8 & 1) != 0)) {
                do {
                  while (*piVar2 != 0) {
                    ClearExclusiveLocal();
                  }
                  cVar6 = '\x01';
                  bVar7 = (bool)ExclusiveMonitorPass(piVar2,0x10);
                  if (bVar7) {
                    *piVar2 = 1;
                    cVar6 = ExclusiveMonitorsStatus();
                  }
                } while (cVar6 != '\0');
                pfVar3 = (float *)(*(long *)(param_1 + 0x28) + uVar12 * 8);
                if (*pfVar3 < fStack_6c) {
                  *pfVar3 = fStack_6c;
                  *(undefined1 *)(*(long *)(param_1 + 0x28) + uVar12 * 8 + 4) = 0;
                }
                do {
                  cVar6 = '\x01';
                  bVar7 = (bool)ExclusiveMonitorPass(piVar2,0x10);
                  if (bVar7) {
                    *piVar2 = 0;
                    cVar6 = ExclusiveMonitorsStatus();
                  }
                } while (cVar6 != '\0');
              }
            }
            uVar13 = uVar13 + 1;
            if (uVar4 <= uVar13) break;
            uVar9 = *(uint *)(param_2 + uVar11 * 4);
          }
        }
      }
      uVar11 = uVar11 + 1;
      iStack_80 = iStack_80 + 0x20;
      uStack_7c = uStack_7c - 0x20;
    } while (uVar11 != param_3);
  }
  return 0;
}

// ==== void Aska::IDESpacePartitionBVH::CollisionDetectionForArray<Aska::IDE_CollisionDetectionParam<(Aska::_Enum_IDECollisionDetectionInputType)3, (Aska::_Enum_IDECollisionDetectionOutputType)4>, false>(Aska::IDE_CollisionDetectionParam<(Aska::_Enum_IDECollisionDetectionInputType)3, (Aska::_Enum_IDECollisionDetectionOutputType)4>*, Aska::IDEPrimitiveBase*)
// vaddr 0x234af14 | ghidra 0x244af14 | size 1060 | symbol _ZN4Aska20IDESpacePartitionBVH26CollisionDetectionForArrayINS_27IDE_CollisionDetectionParamILNS_36_Enum_IDECollisionDetectionInputTypeE3ELNS_37_Enum_IDECollisionDetectionOutputTypeE4EEELb0EEEvPT_PNS_16IDEPrimitiveBaseE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska20IDESpacePartitionBVH26CollisionDetectionForArrayINS_27IDE_CollisionDetectionParamILNS_36_Enum_IDECollisionDetectionInputTypeE3ELNS_37_Enum_IDECollisionDetectionOutputTypeE4EEELb0EEEvPT_PNS_16IDEPrimitiveBaseE
               (long param_1,long param_2)

{
  uint uVar1;
  undefined8 *puVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined1 auVar5 [16];
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  bool bVar10;
  ulong uVar11;
  uint uVar12;
  long lVar13;
  long lVar14;
  ulong uVar15;
  uint *puVar16;
  undefined8 *puVar17;
  long lVar18;
  uint *puVar19;
  undefined8 *puVar20;
  long lVar21;
  ulong uVar22;
  ulong uVar23;
  long lVar24;
  ulong uVar25;
  uint uVar26;
  undefined8 uVar27;
  uint uVar28;
  uint uVar29;
  uint uVar30;
  uint uVar31;
  byte bVar32;
  byte bVar33;
  byte bVar34;
  byte bVar35;
  byte bVar36;
  byte bVar37;
  byte bVar38;
  byte bVar39;
  byte bVar40;
  byte bVar41;
  byte bVar42;
  byte bVar43;
  int iVar44;
  int iVar46;
  int iVar47;
  undefined1 auVar45 [16];
  int iVar48;
  long alStack_9c0 [56];
  uint auStack_800 [4];
  undefined8 auStack_7f0 [2];
  uint auStack_7e0 [2];
  undefined8 auStack_7d8 [239];
  
  uVar12 = *(uint *)(param_1 + 0x10);
  uVar26 = uVar12 + 0x1f;
  uVar1 = uVar26 >> 5;
  if (uVar1 == 0) {
    uVar23 = 0;
  }
  else {
    uVar23 = (ulong)uVar1;
    if (uVar26 < 0x80) {
      lVar14 = 0;
    }
    else {
      uVar26 = uVar26 >> 5 & 3;
      lVar14 = uVar23 - uVar26;
      if (lVar14 != 0) {
        uVar28 = uVar12 + (int)_UNK_029e3690;
        uVar29 = uVar12 + (int)((ulong)_UNK_029e3690 >> 0x20);
        uVar30 = uVar12 + (int)_UNK_029e3698;
        uVar31 = uVar12 + (int)((ulong)_UNK_029e3698 >> 0x20);
        puVar16 = auStack_7e0;
        lVar18 = lVar14;
        do {
          auVar45._8_4_ = 1;
          auVar45._0_8_ = 0x100000001;
          auVar45._12_4_ = 1;
          auVar5._4_4_ = uVar29;
          auVar5._0_4_ = uVar28;
          auVar5._8_4_ = uVar30;
          auVar5._12_4_ = uVar31;
          auVar45 = NEON_ushl(auVar45,auVar5,4);
          iVar6 = -(uint)(0x1f < uVar28);
          bVar32 = (byte)((uint)iVar6 >> 8);
          bVar33 = (byte)((uint)iVar6 >> 0x10);
          bVar34 = (byte)((uint)iVar6 >> 0x18);
          iVar7 = -(uint)(0x1f < uVar29);
          bVar35 = (byte)((uint)iVar7 >> 8);
          bVar36 = (byte)((uint)iVar7 >> 0x10);
          bVar37 = (byte)((uint)iVar7 >> 0x18);
          iVar8 = -(uint)(0x1f < uVar30);
          bVar38 = (byte)((uint)iVar8 >> 8);
          bVar39 = (byte)((uint)iVar8 >> 0x10);
          bVar40 = (byte)((uint)iVar8 >> 0x18);
          iVar9 = -(uint)(0x1f < uVar31);
          bVar41 = (byte)((uint)iVar9 >> 8);
          bVar42 = (byte)((uint)iVar9 >> 0x10);
          bVar43 = (byte)((uint)iVar9 >> 0x18);
          iVar44 = auVar45._0_4_ + -1;
          iVar46 = auVar45._4_4_ + -1;
          iVar47 = auVar45._8_4_ + -1;
          iVar48 = auVar45._12_4_ + -1;
          lVar18 = lVar18 + -4;
          *(ulong *)(puVar16 + 2) =
               CONCAT17(bVar43 | (byte)((uint)iVar48 >> 0x18) & ~bVar43,
                        CONCAT16(bVar42 | (byte)((uint)iVar48 >> 0x10) & ~bVar42,
                                 CONCAT15(bVar41 | (byte)((uint)iVar48 >> 8) & ~bVar41,
                                          CONCAT14((byte)iVar9 | (byte)iVar48 & ~(byte)iVar9,
                                                   CONCAT13(bVar40 | (byte)((uint)iVar47 >> 0x18) &
                                                                     ~bVar40,
                                                            CONCAT12(bVar39 | (byte)((uint)iVar47 >>
                                                                                    0x10) & ~bVar39,
                                                                     CONCAT11(bVar38 | (byte)((uint)
                                                  iVar47 >> 8) & ~bVar38,
                                                  (byte)iVar8 | (byte)iVar47 & ~(byte)iVar8)))))));
          *(ulong *)puVar16 =
               CONCAT17(bVar37 | (byte)((uint)iVar46 >> 0x18) & ~bVar37,
                        CONCAT16(bVar36 | (byte)((uint)iVar46 >> 0x10) & ~bVar36,
                                 CONCAT15(bVar35 | (byte)((uint)iVar46 >> 8) & ~bVar35,
                                          CONCAT14((byte)iVar7 | (byte)iVar46 & ~(byte)iVar7,
                                                   CONCAT13(bVar34 | (byte)((uint)iVar44 >> 0x18) &
                                                                     ~bVar34,
                                                            CONCAT12(bVar33 | (byte)((uint)iVar44 >>
                                                                                    0x10) & ~bVar33,
                                                                     CONCAT11(bVar32 | (byte)((uint)
                                                  iVar44 >> 8) & ~bVar32,
                                                  (byte)iVar6 | (byte)iVar44 & ~(byte)iVar6)))))));
          uVar28 = uVar28 - 0x80;
          uVar29 = uVar29 - 0x80;
          uVar30 = uVar30 - 0x80;
          uVar31 = uVar31 - 0x80;
          puVar16 = puVar16 + 4;
        } while (lVar18 != 0);
        uVar12 = uVar12 + (int)lVar14 * -0x20;
        if (uVar26 == 0) goto code_r0x0244aff8;
      }
    }
    lVar18 = uVar23 - lVar14;
    puVar16 = auStack_7e0 + lVar14;
    do {
      uVar26 = (1 << (ulong)(uVar12 & 0x1f)) - 1;
      if (0x1f < uVar12) {
        uVar26 = 0xffffffff;
      }
      lVar18 = lVar18 + -1;
      *puVar16 = uVar26;
      uVar12 = uVar12 - 0x20;
      puVar16 = puVar16 + 1;
    } while (lVar18 != 0);
  }
code_r0x0244aff8:
  uVar15 = uVar23 & 0xfffffff8;
  lVar14 = 0;
code_r0x0244b040:
  do {
    lVar18 = (long)(int)lVar14;
    if (*(char *)(param_2 + 0x78) == '\0') {
      lVar13 = 0;
      alStack_9c0[lVar18] = 0;
    }
    else {
      lVar13 = *(long *)(param_2 + 0x70);
      alStack_9c0[lVar18] = lVar13;
    }
    if (uVar1 != 0) {
      lVar21 = 0;
      uVar22 = 0;
      bVar10 = false;
      uVar26 = *(uint *)(param_1 + 0x10);
      do {
        puVar16 = auStack_7e0 + lVar18 * 8 + uVar22;
        uVar12 = *puVar16;
        if (uVar12 != 0) {
          uVar28 = uVar26;
          if (0x1f < uVar26) {
            uVar28 = 0x20;
          }
          if (uVar28 != 0) {
            uVar25 = 0;
            lVar24 = lVar21;
            do {
              uVar29 = 1 << (ulong)((uint)uVar25 & 0x1f);
              if ((uVar29 & uVar12) != 0) {
                uVar11 = Aska::Collision::Intersect(Aska::AABB_MinMax const*, Aska::Ray const*)(param_2 + 0x30,*(long *)(param_1 + 8) + lVar24);
                if ((uVar11 & 1) == 0) {
                  uVar12 = *puVar16 & (uVar29 ^ 0xffffffff);
                }
                else {
                  bVar10 = true;
                  uVar12 = *puVar16 | uVar29;
                }
                *puVar16 = uVar12;
              }
              uVar25 = uVar25 + 1;
              lVar24 = lVar24 + 0x20;
            } while (uVar25 < uVar28);
          }
        }
        uVar22 = uVar22 + 1;
        uVar26 = uVar26 - 0x20;
        lVar21 = lVar21 + 0x400;
      } while (uVar22 != uVar23);
      if (bVar10) {
        if ((*(char *)(param_2 + 0x79) != '\0') &&
           (uVar22 = bool Aska::IDE_CollisionDetectionParam<(Aska::_Enum_IDECollisionDetectionInputType)3, (Aska::_Enum_IDECollisionDetectionOutputType)4>::CheckCollisionDetection<false>(unsigned int*, unsigned int, Aska::IDEPrimitiveBase*)(param_1,auStack_7e0 + lVar18 * 8,uVar1), (uVar22 & 1) != 0)) {
          return;
        }
        if (((int)lVar14 < 0x3b) && (lVar13 != 0)) {
          alStack_9c0[lVar18] = *(long *)(lVar13 + 0x68);
          lVar14 = lVar18 + 1;
          uVar22 = 0;
          param_2 = lVar13;
          if ((7 < uVar23) && (uVar15 != 0)) {
            if ((auStack_7e0 + lVar14 * 8 < auStack_7e0 + uVar23 + lVar18 * 8) &&
               (auStack_7e0 + lVar18 * 8 < auStack_7e0 + uVar23 + lVar14 * 8)) {
              uVar22 = 0;
            }
            else {
              puVar17 = auStack_7d8 + lVar18 * 4 + 1;
              puVar20 = auStack_7d8 + lVar14 * 4 + 1;
              uVar22 = uVar15;
              do {
                puVar2 = puVar17 + -1;
                uVar27 = puVar17[-2];
                uVar4 = puVar17[1];
                uVar3 = *puVar17;
                puVar17 = puVar17 + 4;
                uVar22 = uVar22 - 8;
                puVar20[-1] = *puVar2;
                puVar20[-2] = uVar27;
                puVar20[1] = uVar4;
                *puVar20 = uVar3;
                puVar20 = puVar20 + 4;
              } while (uVar22 != 0);
              uVar22 = uVar15;
              if (uVar23 == uVar15) goto code_r0x0244b040;
            }
          }
          lVar13 = uVar23 - uVar22;
          puVar16 = auStack_7e0 + lVar18 * 8 + uVar22;
          puVar19 = auStack_7e0 + lVar14 * 8 + uVar22;
          do {
            lVar13 = lVar13 + -1;
            *puVar19 = *puVar16;
            puVar16 = puVar16 + 1;
            puVar19 = puVar19 + 1;
          } while (lVar13 != 0);
          goto code_r0x0244b040;
        }
      }
    }
    puVar17 = auStack_7f0 + lVar18 * 4;
    lVar21 = 0;
    lVar13 = lVar18;
    do {
      lVar14 = lVar13;
      lVar24 = lVar21;
      puVar20 = puVar17;
      lVar13 = lVar14 + -1;
      if (lVar14 < 1) {
        return;
      }
      lVar21 = lVar24 + -0x20;
      puVar17 = puVar20 + -4;
    } while ((0x3b < lVar14) || (param_2 = alStack_9c0[lVar13], param_2 == 0));
    alStack_9c0[lVar13] = *(long *)(param_2 + 0x68);
  } while (uVar1 == 0);
  lVar21 = (long)(int)lVar14;
  uVar22 = 0;
  if ((7 < uVar23) && (uVar15 != 0)) {
    if ((auStack_7e0 + lVar21 * 8 < auStack_7e0 + uVar23 + lVar13 * 8) &&
       (auStack_7e0 + lVar13 * 8 <
        (uint *)((long)auStack_7e0 + ((lVar14 << 0x20) >> 0x1b) + uVar23 * 4))) {
      uVar22 = 0;
    }
    else {
      puVar17 = auStack_7d8 + lVar21 * 4 + 1;
      uVar22 = uVar15;
      do {
        puVar2 = puVar20 + -1;
        uVar27 = puVar20[-2];
        uVar4 = puVar20[1];
        uVar3 = *puVar20;
        puVar20 = puVar20 + 4;
        uVar22 = uVar22 - 8;
        puVar17[-1] = *puVar2;
        puVar17[-2] = uVar27;
        puVar17[1] = uVar4;
        *puVar17 = uVar3;
        puVar17 = puVar17 + 4;
      } while (uVar22 != 0);
      uVar22 = uVar15;
      if (uVar23 == uVar15) goto code_r0x0244b040;
    }
  }
  lVar13 = uVar23 - uVar22;
  puVar16 = auStack_7e0 + uVar22 + lVar21 * 8;
  puVar19 = (uint *)((long)auStack_800 + lVar24 + (uVar22 + lVar18 * 8) * 4);
  do {
    lVar13 = lVar13 + -1;
    *puVar16 = *puVar19;
    puVar16 = puVar16 + 1;
    puVar19 = puVar19 + 1;
  } while (lVar13 != 0);
  goto code_r0x0244b040;
}

// ==== bool Aska::IDE_CollisionDetectionParam<(Aska::_Enum_IDECollisionDetectionInputType)3, (Aska::_Enum_IDECollisionDetectionOutputType)4>::CheckCollisionDetection<false>(unsigned int*, unsigned int, Aska::IDEPrimitiveBase*)
// vaddr 0x234b338 | ghidra 0x244b338 | size 436 | symbol _ZN4Aska27IDE_CollisionDetectionParamILNS_36_Enum_IDECollisionDetectionInputTypeE3ELNS_37_Enum_IDECollisionDetectionOutputTypeE4EE23CheckCollisionDetectionILb0EEEbPjjPNS_16IDEPrimitiveBaseE | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska27IDE_CollisionDetectionParamILNS_36_Enum_IDECollisionDetectionInputTypeE3ELNS_37_Enum_IDECollisionDetectionOutputTypeE4EE23CheckCollisionDetectionILb0EEEbPjjPNS_16IDEPrimitiveBaseE
          (undefined2 *param_1,long param_2,uint param_3,long *param_4)

{
  int *piVar1;
  long lVar2;
  undefined8 *puVar3;
  uint uVar4;
  char cVar5;
  bool bVar6;
  ulong uVar7;
  uint uVar8;
  long lVar9;
  ulong uVar10;
  ulong uVar11;
  ulong uVar12;
  int iStack_f0;
  uint uStack_ec;
  undefined8 uStack_e0;
  undefined4 uStack_d8;
  float fStack_d4;
  undefined8 uStack_d0;
  undefined8 uStack_c8;
  undefined8 uStack_c0;
  undefined8 uStack_b8;
  undefined8 uStack_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined8 uStack_98;
  undefined8 uStack_90;
  undefined8 uStack_88;
  undefined8 uStack_80;
  undefined8 uStack_78;
  undefined8 uStack_70;
  undefined8 uStack_68;
  
  if (param_3 != 0) {
    iStack_f0 = 0;
    lVar9 = *(long *)(param_1 + 4);
    uVar10 = 0;
    piVar1 = (int *)(param_1 + 0x14);
    uStack_ec = *(uint *)(param_1 + 8);
    do {
      uVar8 = *(uint *)(param_2 + uVar10 * 4);
      if (uVar8 != 0) {
        uVar4 = uStack_ec;
        if (0x1f < uStack_ec) {
          uVar4 = 0x20;
        }
        if (uVar4 != 0) {
          uVar12 = 0;
          while( true ) {
            if ((uVar8 & 1 << (ulong)((uint)uVar12 & 0x1f)) != 0) {
              uVar11 = (ulong)((uint)uVar12 + iStack_f0);
              lVar2 = lVar9 + uVar11 * 0x20;
              uVar7 = (**(code **)(*param_4 + 0x10))(param_4,lVar2,*param_1);
              if (((uVar7 & 1) != 0) &&
                 (uVar7 = (**(code **)(*param_4 + 0x58))(param_4,&uStack_e0,lVar2,*param_1),
                 (uVar7 & 1) != 0)) {
                do {
                  while (*piVar1 != 0) {
                    ClearExclusiveLocal();
                  }
                  cVar5 = '\x01';
                  bVar6 = (bool)ExclusiveMonitorPass(piVar1,0x10);
                  if (bVar6) {
                    *piVar1 = 1;
                    cVar5 = ExclusiveMonitorsStatus();
                  }
                } while (cVar5 != '\0');
                puVar3 = (undefined8 *)(*(long *)(param_1 + 0xc) + uVar11 * 0x80);
                if (fStack_d4 < *(float *)((long)puVar3 + 0xc)) {
                  puVar3[1] = CONCAT44(fStack_d4,uStack_d8);
                  *puVar3 = uStack_e0;
                  puVar3[3] = uStack_c8;
                  puVar3[2] = uStack_d0;
                  puVar3[5] = uStack_b8;
                  puVar3[4] = uStack_c0;
                  puVar3[7] = uStack_a8;
                  puVar3[6] = uStack_b0;
                  puVar3[9] = uStack_98;
                  puVar3[8] = uStack_a0;
                  puVar3[0xb] = uStack_88;
                  puVar3[10] = uStack_90;
                  puVar3[0xd] = uStack_78;
                  puVar3[0xc] = uStack_80;
                  puVar3[0xf] = uStack_68;
                  puVar3[0xe] = uStack_70;
                }
                do {
                  cVar5 = '\x01';
                  bVar6 = (bool)ExclusiveMonitorPass(piVar1,0x10);
                  if (bVar6) {
                    *piVar1 = 0;
                    cVar5 = ExclusiveMonitorsStatus();
                  }
                } while (cVar5 != '\0');
              }
            }
            uVar12 = uVar12 + 1;
            if (uVar4 <= uVar12) break;
            uVar8 = *(uint *)(param_2 + uVar10 * 4);
          }
        }
      }
      uVar10 = uVar10 + 1;
      iStack_f0 = iStack_f0 + 0x20;
      uStack_ec = uStack_ec - 0x20;
    } while (uVar10 != param_3);
  }
  return 0;
}

// ==== void Aska::IDESpacePartitionBVH::CollisionDetectionForArray<Aska::IDE_CollisionDetectionParam<(Aska::_Enum_IDECollisionDetectionInputType)4, (Aska::_Enum_IDECollisionDetectionOutputType)4>, false>(Aska::IDE_CollisionDetectionParam<(Aska::_Enum_IDECollisionDetectionInputType)4, (Aska::_Enum_IDECollisionDetectionOutputType)4>*, Aska::IDEPrimitiveBase*)
// vaddr 0x234b4ec | ghidra 0x244b4ec | size 1060 | symbol _ZN4Aska20IDESpacePartitionBVH26CollisionDetectionForArrayINS_27IDE_CollisionDetectionParamILNS_36_Enum_IDECollisionDetectionInputTypeE4ELNS_37_Enum_IDECollisionDetectionOutputTypeE4EEELb0EEEvPT_PNS_16IDEPrimitiveBaseE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska20IDESpacePartitionBVH26CollisionDetectionForArrayINS_27IDE_CollisionDetectionParamILNS_36_Enum_IDECollisionDetectionInputTypeE4ELNS_37_Enum_IDECollisionDetectionOutputTypeE4EEELb0EEEvPT_PNS_16IDEPrimitiveBaseE
               (long param_1,long param_2)

{
  uint uVar1;
  undefined8 *puVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined1 auVar5 [16];
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  bool bVar10;
  ulong uVar11;
  uint uVar12;
  long lVar13;
  long lVar14;
  ulong uVar15;
  uint *puVar16;
  undefined8 *puVar17;
  long lVar18;
  uint *puVar19;
  undefined8 *puVar20;
  long lVar21;
  ulong uVar22;
  ulong uVar23;
  long lVar24;
  ulong uVar25;
  uint uVar26;
  undefined8 uVar27;
  uint uVar28;
  uint uVar29;
  uint uVar30;
  uint uVar31;
  byte bVar32;
  byte bVar33;
  byte bVar34;
  byte bVar35;
  byte bVar36;
  byte bVar37;
  byte bVar38;
  byte bVar39;
  byte bVar40;
  byte bVar41;
  byte bVar42;
  byte bVar43;
  int iVar44;
  int iVar46;
  int iVar47;
  undefined1 auVar45 [16];
  int iVar48;
  long alStack_9c0 [56];
  uint auStack_800 [4];
  undefined8 auStack_7f0 [2];
  uint auStack_7e0 [2];
  undefined8 auStack_7d8 [239];
  
  uVar12 = *(uint *)(param_1 + 0x10);
  uVar26 = uVar12 + 0x1f;
  uVar1 = uVar26 >> 5;
  if (uVar1 == 0) {
    uVar23 = 0;
  }
  else {
    uVar23 = (ulong)uVar1;
    if (uVar26 < 0x80) {
      lVar14 = 0;
    }
    else {
      uVar26 = uVar26 >> 5 & 3;
      lVar14 = uVar23 - uVar26;
      if (lVar14 != 0) {
        uVar28 = uVar12 + (int)_UNK_029e3690;
        uVar29 = uVar12 + (int)((ulong)_UNK_029e3690 >> 0x20);
        uVar30 = uVar12 + (int)_UNK_029e3698;
        uVar31 = uVar12 + (int)((ulong)_UNK_029e3698 >> 0x20);
        puVar16 = auStack_7e0;
        lVar18 = lVar14;
        do {
          auVar45._8_4_ = 1;
          auVar45._0_8_ = 0x100000001;
          auVar45._12_4_ = 1;
          auVar5._4_4_ = uVar29;
          auVar5._0_4_ = uVar28;
          auVar5._8_4_ = uVar30;
          auVar5._12_4_ = uVar31;
          auVar45 = NEON_ushl(auVar45,auVar5,4);
          iVar6 = -(uint)(0x1f < uVar28);
          bVar32 = (byte)((uint)iVar6 >> 8);
          bVar33 = (byte)((uint)iVar6 >> 0x10);
          bVar34 = (byte)((uint)iVar6 >> 0x18);
          iVar7 = -(uint)(0x1f < uVar29);
          bVar35 = (byte)((uint)iVar7 >> 8);
          bVar36 = (byte)((uint)iVar7 >> 0x10);
          bVar37 = (byte)((uint)iVar7 >> 0x18);
          iVar8 = -(uint)(0x1f < uVar30);
          bVar38 = (byte)((uint)iVar8 >> 8);
          bVar39 = (byte)((uint)iVar8 >> 0x10);
          bVar40 = (byte)((uint)iVar8 >> 0x18);
          iVar9 = -(uint)(0x1f < uVar31);
          bVar41 = (byte)((uint)iVar9 >> 8);
          bVar42 = (byte)((uint)iVar9 >> 0x10);
          bVar43 = (byte)((uint)iVar9 >> 0x18);
          iVar44 = auVar45._0_4_ + -1;
          iVar46 = auVar45._4_4_ + -1;
          iVar47 = auVar45._8_4_ + -1;
          iVar48 = auVar45._12_4_ + -1;
          lVar18 = lVar18 + -4;
          *(ulong *)(puVar16 + 2) =
               CONCAT17(bVar43 | (byte)((uint)iVar48 >> 0x18) & ~bVar43,
                        CONCAT16(bVar42 | (byte)((uint)iVar48 >> 0x10) & ~bVar42,
                                 CONCAT15(bVar41 | (byte)((uint)iVar48 >> 8) & ~bVar41,
                                          CONCAT14((byte)iVar9 | (byte)iVar48 & ~(byte)iVar9,
                                                   CONCAT13(bVar40 | (byte)((uint)iVar47 >> 0x18) &
                                                                     ~bVar40,
                                                            CONCAT12(bVar39 | (byte)((uint)iVar47 >>
                                                                                    0x10) & ~bVar39,
                                                                     CONCAT11(bVar38 | (byte)((uint)
                                                  iVar47 >> 8) & ~bVar38,
                                                  (byte)iVar8 | (byte)iVar47 & ~(byte)iVar8)))))));
          *(ulong *)puVar16 =
               CONCAT17(bVar37 | (byte)((uint)iVar46 >> 0x18) & ~bVar37,
                        CONCAT16(bVar36 | (byte)((uint)iVar46 >> 0x10) & ~bVar36,
                                 CONCAT15(bVar35 | (byte)((uint)iVar46 >> 8) & ~bVar35,
                                          CONCAT14((byte)iVar7 | (byte)iVar46 & ~(byte)iVar7,
                                                   CONCAT13(bVar34 | (byte)((uint)iVar44 >> 0x18) &
                                                                     ~bVar34,
                                                            CONCAT12(bVar33 | (byte)((uint)iVar44 >>
                                                                                    0x10) & ~bVar33,
                                                                     CONCAT11(bVar32 | (byte)((uint)
                                                  iVar44 >> 8) & ~bVar32,
                                                  (byte)iVar6 | (byte)iVar44 & ~(byte)iVar6)))))));
          uVar28 = uVar28 - 0x80;
          uVar29 = uVar29 - 0x80;
          uVar30 = uVar30 - 0x80;
          uVar31 = uVar31 - 0x80;
          puVar16 = puVar16 + 4;
        } while (lVar18 != 0);
        uVar12 = uVar12 + (int)lVar14 * -0x20;
        if (uVar26 == 0) goto code_r0x0244b5d0;
      }
    }
    lVar18 = uVar23 - lVar14;
    puVar16 = auStack_7e0 + lVar14;
    do {
      uVar26 = (1 << (ulong)(uVar12 & 0x1f)) - 1;
      if (0x1f < uVar12) {
        uVar26 = 0xffffffff;
      }
      lVar18 = lVar18 + -1;
      *puVar16 = uVar26;
      uVar12 = uVar12 - 0x20;
      puVar16 = puVar16 + 1;
    } while (lVar18 != 0);
  }
code_r0x0244b5d0:
  uVar15 = uVar23 & 0xfffffff8;
  lVar14 = 0;
code_r0x0244b618:
  do {
    lVar18 = (long)(int)lVar14;
    if (*(char *)(param_2 + 0x78) == '\0') {
      lVar13 = 0;
      alStack_9c0[lVar18] = 0;
    }
    else {
      lVar13 = *(long *)(param_2 + 0x70);
      alStack_9c0[lVar18] = lVar13;
    }
    if (uVar1 != 0) {
      lVar21 = 0;
      uVar22 = 0;
      bVar10 = false;
      uVar26 = *(uint *)(param_1 + 0x10);
      do {
        puVar16 = auStack_7e0 + lVar18 * 8 + uVar22;
        uVar12 = *puVar16;
        if (uVar12 != 0) {
          uVar28 = uVar26;
          if (0x1f < uVar26) {
            uVar28 = 0x20;
          }
          if (uVar28 != 0) {
            uVar25 = 0;
            lVar24 = lVar21;
            do {
              uVar29 = 1 << (ulong)((uint)uVar25 & 0x1f);
              if ((uVar29 & uVar12) != 0) {
                uVar11 = Aska::Collision::Intersect(Aska::AABB_MinMax const*, Aska::Segment const*)(param_2 + 0x30,*(long *)(param_1 + 8) + lVar24);
                if ((uVar11 & 1) == 0) {
                  uVar12 = *puVar16 & (uVar29 ^ 0xffffffff);
                }
                else {
                  bVar10 = true;
                  uVar12 = *puVar16 | uVar29;
                }
                *puVar16 = uVar12;
              }
              uVar25 = uVar25 + 1;
              lVar24 = lVar24 + 0x20;
            } while (uVar25 < uVar28);
          }
        }
        uVar22 = uVar22 + 1;
        uVar26 = uVar26 - 0x20;
        lVar21 = lVar21 + 0x400;
      } while (uVar22 != uVar23);
      if (bVar10) {
        if ((*(char *)(param_2 + 0x79) != '\0') &&
           (uVar22 = bool Aska::IDE_CollisionDetectionParam<(Aska::_Enum_IDECollisionDetectionInputType)4, (Aska::_Enum_IDECollisionDetectionOutputType)4>::CheckCollisionDetection<false>(unsigned int*, unsigned int, Aska::IDEPrimitiveBase*)(param_1,auStack_7e0 + lVar18 * 8,uVar1), (uVar22 & 1) != 0)) {
          return;
        }
        if (((int)lVar14 < 0x3b) && (lVar13 != 0)) {
          alStack_9c0[lVar18] = *(long *)(lVar13 + 0x68);
          lVar14 = lVar18 + 1;
          uVar22 = 0;
          param_2 = lVar13;
          if ((7 < uVar23) && (uVar15 != 0)) {
            if ((auStack_7e0 + lVar14 * 8 < auStack_7e0 + uVar23 + lVar18 * 8) &&
               (auStack_7e0 + lVar18 * 8 < auStack_7e0 + uVar23 + lVar14 * 8)) {
              uVar22 = 0;
            }
            else {
              puVar17 = auStack_7d8 + lVar18 * 4 + 1;
              puVar20 = auStack_7d8 + lVar14 * 4 + 1;
              uVar22 = uVar15;
              do {
                puVar2 = puVar17 + -1;
                uVar27 = puVar17[-2];
                uVar4 = puVar17[1];
                uVar3 = *puVar17;
                puVar17 = puVar17 + 4;
                uVar22 = uVar22 - 8;
                puVar20[-1] = *puVar2;
                puVar20[-2] = uVar27;
                puVar20[1] = uVar4;
                *puVar20 = uVar3;
                puVar20 = puVar20 + 4;
              } while (uVar22 != 0);
              uVar22 = uVar15;
              if (uVar23 == uVar15) goto code_r0x0244b618;
            }
          }
          lVar13 = uVar23 - uVar22;
          puVar16 = auStack_7e0 + lVar18 * 8 + uVar22;
          puVar19 = auStack_7e0 + lVar14 * 8 + uVar22;
          do {
            lVar13 = lVar13 + -1;
            *puVar19 = *puVar16;
            puVar16 = puVar16 + 1;
            puVar19 = puVar19 + 1;
          } while (lVar13 != 0);
          goto code_r0x0244b618;
        }
      }
    }
    puVar17 = auStack_7f0 + lVar18 * 4;
    lVar21 = 0;
    lVar13 = lVar18;
    do {
      lVar14 = lVar13;
      lVar24 = lVar21;
      puVar20 = puVar17;
      lVar13 = lVar14 + -1;
      if (lVar14 < 1) {
        return;
      }
      lVar21 = lVar24 + -0x20;
      puVar17 = puVar20 + -4;
    } while ((0x3b < lVar14) || (param_2 = alStack_9c0[lVar13], param_2 == 0));
    alStack_9c0[lVar13] = *(long *)(param_2 + 0x68);
  } while (uVar1 == 0);
  lVar21 = (long)(int)lVar14;
  uVar22 = 0;
  if ((7 < uVar23) && (uVar15 != 0)) {
    if ((auStack_7e0 + lVar21 * 8 < auStack_7e0 + uVar23 + lVar13 * 8) &&
       (auStack_7e0 + lVar13 * 8 <
        (uint *)((long)auStack_7e0 + ((lVar14 << 0x20) >> 0x1b) + uVar23 * 4))) {
      uVar22 = 0;
    }
    else {
      puVar17 = auStack_7d8 + lVar21 * 4 + 1;
      uVar22 = uVar15;
      do {
        puVar2 = puVar20 + -1;
        uVar27 = puVar20[-2];
        uVar4 = puVar20[1];
        uVar3 = *puVar20;
        puVar20 = puVar20 + 4;
        uVar22 = uVar22 - 8;
        puVar17[-1] = *puVar2;
        puVar17[-2] = uVar27;
        puVar17[1] = uVar4;
        *puVar17 = uVar3;
        puVar17 = puVar17 + 4;
      } while (uVar22 != 0);
      uVar22 = uVar15;
      if (uVar23 == uVar15) goto code_r0x0244b618;
    }
  }
  lVar13 = uVar23 - uVar22;
  puVar16 = auStack_7e0 + uVar22 + lVar21 * 8;
  puVar19 = (uint *)((long)auStack_800 + lVar24 + (uVar22 + lVar18 * 8) * 4);
  do {
    lVar13 = lVar13 + -1;
    *puVar16 = *puVar19;
    puVar16 = puVar16 + 1;
    puVar19 = puVar19 + 1;
  } while (lVar13 != 0);
  goto code_r0x0244b618;
}

// ==== bool Aska::IDE_CollisionDetectionParam<(Aska::_Enum_IDECollisionDetectionInputType)4, (Aska::_Enum_IDECollisionDetectionOutputType)4>::CheckCollisionDetection<false>(unsigned int*, unsigned int, Aska::IDEPrimitiveBase*)
// vaddr 0x234b910 | ghidra 0x244b910 | size 436 | symbol _ZN4Aska27IDE_CollisionDetectionParamILNS_36_Enum_IDECollisionDetectionInputTypeE4ELNS_37_Enum_IDECollisionDetectionOutputTypeE4EE23CheckCollisionDetectionILb0EEEbPjjPNS_16IDEPrimitiveBaseE | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska27IDE_CollisionDetectionParamILNS_36_Enum_IDECollisionDetectionInputTypeE4ELNS_37_Enum_IDECollisionDetectionOutputTypeE4EE23CheckCollisionDetectionILb0EEEbPjjPNS_16IDEPrimitiveBaseE
          (undefined2 *param_1,long param_2,uint param_3,long *param_4)

{
  int *piVar1;
  long lVar2;
  undefined8 *puVar3;
  uint uVar4;
  char cVar5;
  bool bVar6;
  ulong uVar7;
  uint uVar8;
  long lVar9;
  ulong uVar10;
  ulong uVar11;
  ulong uVar12;
  int iStack_f0;
  uint uStack_ec;
  undefined8 uStack_e0;
  undefined4 uStack_d8;
  float fStack_d4;
  undefined8 uStack_d0;
  undefined8 uStack_c8;
  undefined8 uStack_c0;
  undefined8 uStack_b8;
  undefined8 uStack_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined8 uStack_98;
  undefined8 uStack_90;
  undefined8 uStack_88;
  undefined8 uStack_80;
  undefined8 uStack_78;
  undefined8 uStack_70;
  undefined8 uStack_68;
  
  if (param_3 != 0) {
    iStack_f0 = 0;
    lVar9 = *(long *)(param_1 + 4);
    uVar10 = 0;
    piVar1 = (int *)(param_1 + 0x14);
    uStack_ec = *(uint *)(param_1 + 8);
    do {
      uVar8 = *(uint *)(param_2 + uVar10 * 4);
      if (uVar8 != 0) {
        uVar4 = uStack_ec;
        if (0x1f < uStack_ec) {
          uVar4 = 0x20;
        }
        if (uVar4 != 0) {
          uVar12 = 0;
          while( true ) {
            if ((uVar8 & 1 << (ulong)((uint)uVar12 & 0x1f)) != 0) {
              uVar11 = (ulong)((uint)uVar12 + iStack_f0);
              lVar2 = lVar9 + uVar11 * 0x20;
              uVar7 = (**(code **)(*param_4 + 0x18))(param_4,lVar2,*param_1);
              if (((uVar7 & 1) != 0) &&
                 (uVar7 = (**(code **)(*param_4 + 0x60))(param_4,&uStack_e0,lVar2,*param_1),
                 (uVar7 & 1) != 0)) {
                do {
                  while (*piVar1 != 0) {
                    ClearExclusiveLocal();
                  }
                  cVar5 = '\x01';
                  bVar6 = (bool)ExclusiveMonitorPass(piVar1,0x10);
                  if (bVar6) {
                    *piVar1 = 1;
                    cVar5 = ExclusiveMonitorsStatus();
                  }
                } while (cVar5 != '\0');
                puVar3 = (undefined8 *)(*(long *)(param_1 + 0xc) + uVar11 * 0x80);
                if (fStack_d4 < *(float *)((long)puVar3 + 0xc)) {
                  puVar3[1] = CONCAT44(fStack_d4,uStack_d8);
                  *puVar3 = uStack_e0;
                  puVar3[3] = uStack_c8;
                  puVar3[2] = uStack_d0;
                  puVar3[5] = uStack_b8;
                  puVar3[4] = uStack_c0;
                  puVar3[7] = uStack_a8;
                  puVar3[6] = uStack_b0;
                  puVar3[9] = uStack_98;
                  puVar3[8] = uStack_a0;
                  puVar3[0xb] = uStack_88;
                  puVar3[10] = uStack_90;
                  puVar3[0xd] = uStack_78;
                  puVar3[0xc] = uStack_80;
                  puVar3[0xf] = uStack_68;
                  puVar3[0xe] = uStack_70;
                }
                do {
                  cVar5 = '\x01';
                  bVar6 = (bool)ExclusiveMonitorPass(piVar1,0x10);
                  if (bVar6) {
                    *piVar1 = 0;
                    cVar5 = ExclusiveMonitorsStatus();
                  }
                } while (cVar5 != '\0');
              }
            }
            uVar12 = uVar12 + 1;
            if (uVar4 <= uVar12) break;
            uVar8 = *(uint *)(param_2 + uVar10 * 4);
          }
        }
      }
      uVar10 = uVar10 + 1;
      iStack_f0 = iStack_f0 + 0x20;
      uStack_ec = uStack_ec - 0x20;
    } while (uVar10 != param_3);
  }
  return 0;
}

// ==== Aska::IDEPrimitive<(Aska::_EnumIDESpacePartitionType)0, (Aska::_EnumIDEPrimitiveType)0>::~IDEPrimitive()
// vaddr 0x234bac4 | ghidra 0x244bac4 | size 4 | symbol _ZN4Aska12IDEPrimitiveILNS_26_EnumIDESpacePartitionTypeE0ELNS_21_EnumIDEPrimitiveTypeE0EED0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12IDEPrimitiveILNS_26_EnumIDESpacePartitionTypeE0ELNS_21_EnumIDEPrimitiveTypeE0EED0Ev
               (void)

{
  (*(code *)PTR__ZdlPv_02ca4758)();
  return;
}

// ==== void Aska::IDESpacePartitionBVH::CollisionDetection<Aska::IDE_CollisionDetectionParam<(Aska::_Enum_IDECollisionDetectionInputType)5, (Aska::_Enum_IDECollisionDetectionOutputType)5>, true>(Aska::IDE_CollisionDetectionParam<(Aska::_Enum_IDECollisionDetectionInputType)5, (Aska::_Enum_IDECollisionDetectionOutputType)5>*, Aska::IDEPrimitiveBase*)
// vaddr 0x234bac8 | ghidra 0x244bac8 | size 288 | symbol _ZN4Aska20IDESpacePartitionBVH18CollisionDetectionINS_27IDE_CollisionDetectionParamILNS_36_Enum_IDECollisionDetectionInputTypeE5ELNS_37_Enum_IDECollisionDetectionOutputTypeE5EEELb1EEEvPT_PNS_16IDEPrimitiveBaseE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska20IDESpacePartitionBVH18CollisionDetectionINS_27IDE_CollisionDetectionParamILNS_36_Enum_IDECollisionDetectionInputTypeE5ELNS_37_Enum_IDECollisionDetectionOutputTypeE5EEELb1EEEvPT_PNS_16IDEPrimitiveBaseE
               (undefined2 *param_1,long param_2)

{
  int iVar1;
  long *plVar2;
  long lVar3;
  long lVar4;
  long lVar5;
  float fVar6;
  long alStack_418 [61];
  long alStack_230 [60];
  
  iVar1 = 0;
  alStack_230[0] = param_2;
  do {
    while( true ) {
      plVar2 = (long *)alStack_230[iVar1];
      lVar3 = (long)iVar1;
      if ((char)plVar2[0xf] == '\0') {
        lVar4 = 0;
      }
      else {
        lVar4 = plVar2[0xe];
      }
      alStack_418[lVar3 + 1] = lVar4;
      fVar6 = (float)Aska::AABB_MinMax::CalcDistance(Aska::Vector const*) const(plVar2 + 6,param_1 + 8);
      if (fVar6 <= *(float *)(param_1 + 0xe)) break;
code_r0x0244bba0:
      iVar1 = iVar1 + 1;
      do {
        lVar4 = lVar3;
        if (lVar4 < 1) {
          return;
        }
        iVar1 = iVar1 + -1;
        lVar3 = lVar4 + -1;
      } while ((0x3b < lVar4) || (lVar5 = alStack_418[lVar4], lVar5 == 0));
      lVar3 = *(long *)(lVar5 + 0x68);
      alStack_230[iVar1] = lVar5;
      alStack_418[lVar4] = lVar3;
    }
    if (*(char *)((long)plVar2 + 0x79) != '\0') {
      if (*(char *)((long)plVar2 + 0x22) == '\0') {
        (**(code **)(*plVar2 + 0x68))(plVar2,*(undefined8 *)(param_1 + 0x34),param_1 + 8,*param_1);
      }
      else {
        Aska::IDE_CollisionDetectionParam<(Aska::_Enum_IDECollisionDetectionInputType)5, (Aska::_Enum_IDECollisionDetectionOutputType)5>::Dispatch(Aska::IDEPrimitiveBase*)(param_1,plVar2);
      }
    }
    if ((0x3a < iVar1) || (lVar4 == 0)) goto code_r0x0244bba0;
    alStack_418[lVar3 + 1] = *(long *)(lVar4 + 0x68);
    iVar1 = iVar1 + 1;
    alStack_230[iVar1] = lVar4;
  } while( true );
}

// ==== Aska::IDE_CollisionDetectionParam<(Aska::_Enum_IDECollisionDetectionInputType)0, (Aska::_Enum_IDECollisionDetectionOutputType)0>::Dispatch(Aska::IDEPrimitiveBase*)
// vaddr 0x25a28e0 | ghidra 0x26a28e0 | size 196 | symbol _ZN4Aska27IDE_CollisionDetectionParamILNS_36_Enum_IDECollisionDetectionInputTypeE0ELNS_37_Enum_IDECollisionDetectionOutputTypeE0EE8DispatchEPNS_16IDEPrimitiveBaseE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska27IDE_CollisionDetectionParamILNS_36_Enum_IDECollisionDetectionInputTypeE0ELNS_37_Enum_IDECollisionDetectionOutputTypeE0EE8DispatchEPNS_16IDEPrimitiveBaseE
               (undefined2 *param_1,long *param_2)

{
  int *piVar1;
  char cVar2;
  bool bVar3;
  ulong uVar4;
  undefined8 uVar5;
  
  uVar4 = (**(code **)(*param_2 + 0x10))(param_2,param_1 + 8,*param_1);
  if ((uVar4 & 1) != 0) {
    piVar1 = (int *)(param_1 + 0x1a);
    uVar5 = *(undefined8 *)PTR__ZN4Aska6Global20m_pMessageDispatcherE_02cb77c8;
    do {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar3) {
        *piVar1 = *piVar1 + 1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    uVar4 = Aska::SimpleMessageDispatcher::PostSyncMessageSingle(unsigned short, int*, Aska::INotify*, void*, void*, unsigned int*, signed char)(uVar5,0,piVar1,
                            &
                            PTR__ZTVN4Aska28IDE_NotifyCollisionDetectionILNS_36_Enum_IDECollisionDetectionInputTypeE0ELNS_37_Enum_IDECollisionDetectionOutputTypeE0EEE_16__02ceaee0
                            ,param_2,param_1,0,1);
    while ((uVar4 & 1) == 0) {
      Aska::Thread::Sleep(unsigned int)(1);
      uVar4 = Aska::SimpleMessageDispatcher::PostSyncMessageSingle(unsigned short, int*, Aska::INotify*, void*, void*, unsigned int*, signed char)(uVar5,0,piVar1,
                              &
                              PTR__ZTVN4Aska28IDE_NotifyCollisionDetectionILNS_36_Enum_IDECollisionDetectionInputTypeE0ELNS_37_Enum_IDECollisionDetectionOutputTypeE0EEE_16__02ceaee0
                              ,param_2,param_1,0,1);
    }
  }
  return;
}

// ==== Aska::IDE_CollisionDetectionParam<(Aska::_Enum_IDECollisionDetectionInputType)1, (Aska::_Enum_IDECollisionDetectionOutputType)0>::Dispatch(Aska::IDEPrimitiveBase*)
// vaddr 0x25a29a4 | ghidra 0x26a29a4 | size 196 | symbol _ZN4Aska27IDE_CollisionDetectionParamILNS_36_Enum_IDECollisionDetectionInputTypeE1ELNS_37_Enum_IDECollisionDetectionOutputTypeE0EE8DispatchEPNS_16IDEPrimitiveBaseE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska27IDE_CollisionDetectionParamILNS_36_Enum_IDECollisionDetectionInputTypeE1ELNS_37_Enum_IDECollisionDetectionOutputTypeE0EE8DispatchEPNS_16IDEPrimitiveBaseE
               (undefined2 *param_1,long *param_2)

{
  int *piVar1;
  char cVar2;
  bool bVar3;
  ulong uVar4;
  undefined8 uVar5;
  
  uVar4 = (**(code **)(*param_2 + 0x18))(param_2,param_1 + 8,*param_1);
  if ((uVar4 & 1) != 0) {
    piVar1 = (int *)(param_1 + 0x1a);
    uVar5 = *(undefined8 *)PTR__ZN4Aska6Global20m_pMessageDispatcherE_02cb77c8;
    do {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar3) {
        *piVar1 = *piVar1 + 1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    uVar4 = Aska::SimpleMessageDispatcher::PostSyncMessageSingle(unsigned short, int*, Aska::INotify*, void*, void*, unsigned int*, signed char)(uVar5,0,piVar1,
                            &
                            PTR__ZTVN4Aska28IDE_NotifyCollisionDetectionILNS_36_Enum_IDECollisionDetectionInputTypeE1ELNS_37_Enum_IDECollisionDetectionOutputTypeE0EEE_16__02ceaee8
                            ,param_2,param_1,0,1);
    while ((uVar4 & 1) == 0) {
      Aska::Thread::Sleep(unsigned int)(1);
      uVar4 = Aska::SimpleMessageDispatcher::PostSyncMessageSingle(unsigned short, int*, Aska::INotify*, void*, void*, unsigned int*, signed char)(uVar5,0,piVar1,
                              &
                              PTR__ZTVN4Aska28IDE_NotifyCollisionDetectionILNS_36_Enum_IDECollisionDetectionInputTypeE1ELNS_37_Enum_IDECollisionDetectionOutputTypeE0EEE_16__02ceaee8
                              ,param_2,param_1,0,1);
    }
  }
  return;
}

// ==== Aska::IDE_CollisionDetectionParam<(Aska::_Enum_IDECollisionDetectionInputType)0, (Aska::_Enum_IDECollisionDetectionOutputType)1>::Dispatch(Aska::IDEPrimitiveBase*)
// vaddr 0x25a2a68 | ghidra 0x26a2a68 | size 196 | symbol _ZN4Aska27IDE_CollisionDetectionParamILNS_36_Enum_IDECollisionDetectionInputTypeE0ELNS_37_Enum_IDECollisionDetectionOutputTypeE1EE8DispatchEPNS_16IDEPrimitiveBaseE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska27IDE_CollisionDetectionParamILNS_36_Enum_IDECollisionDetectionInputTypeE0ELNS_37_Enum_IDECollisionDetectionOutputTypeE1EE8DispatchEPNS_16IDEPrimitiveBaseE
               (undefined2 *param_1,long *param_2)

{
  int *piVar1;
  char cVar2;
  bool bVar3;
  ulong uVar4;
  undefined8 uVar5;
  
  uVar4 = (**(code **)(*param_2 + 0x10))(param_2,param_1 + 8,*param_1);
  if ((uVar4 & 1) != 0) {
    piVar1 = (int *)(param_1 + 0x22);
    uVar5 = *(undefined8 *)PTR__ZN4Aska6Global20m_pMessageDispatcherE_02cb77c8;
    do {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar3) {
        *piVar1 = *piVar1 + 1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    uVar4 = Aska::SimpleMessageDispatcher::PostSyncMessageSingle(unsigned short, int*, Aska::INotify*, void*, void*, unsigned int*, signed char)(uVar5,0,piVar1,
                            &
                            PTR__ZTVN4Aska28IDE_NotifyCollisionDetectionILNS_36_Enum_IDECollisionDetectionInputTypeE0ELNS_37_Enum_IDECollisionDetectionOutputTypeE1EEE_16__02ceaef0
                            ,param_2,param_1,0,1);
    while ((uVar4 & 1) == 0) {
      Aska::Thread::Sleep(unsigned int)(1);
      uVar4 = Aska::SimpleMessageDispatcher::PostSyncMessageSingle(unsigned short, int*, Aska::INotify*, void*, void*, unsigned int*, signed char)(uVar5,0,piVar1,
                              &
                              PTR__ZTVN4Aska28IDE_NotifyCollisionDetectionILNS_36_Enum_IDECollisionDetectionInputTypeE0ELNS_37_Enum_IDECollisionDetectionOutputTypeE1EEE_16__02ceaef0
                              ,param_2,param_1,0,1);
    }
  }
  return;
}

// ==== Aska::IDE_CollisionDetectionParam<(Aska::_Enum_IDECollisionDetectionInputType)1, (Aska::_Enum_IDECollisionDetectionOutputType)1>::Dispatch(Aska::IDEPrimitiveBase*)
// vaddr 0x25a2b2c | ghidra 0x26a2b2c | size 196 | symbol _ZN4Aska27IDE_CollisionDetectionParamILNS_36_Enum_IDECollisionDetectionInputTypeE1ELNS_37_Enum_IDECollisionDetectionOutputTypeE1EE8DispatchEPNS_16IDEPrimitiveBaseE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska27IDE_CollisionDetectionParamILNS_36_Enum_IDECollisionDetectionInputTypeE1ELNS_37_Enum_IDECollisionDetectionOutputTypeE1EE8DispatchEPNS_16IDEPrimitiveBaseE
               (undefined2 *param_1,long *param_2)

{
  int *piVar1;
  char cVar2;
  bool bVar3;
  ulong uVar4;
  undefined8 uVar5;
  
  uVar4 = (**(code **)(*param_2 + 0x18))(param_2,param_1 + 8,*param_1);
  if ((uVar4 & 1) != 0) {
    piVar1 = (int *)(param_1 + 0x22);
    uVar5 = *(undefined8 *)PTR__ZN4Aska6Global20m_pMessageDispatcherE_02cb77c8;
    do {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar3) {
        *piVar1 = *piVar1 + 1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    uVar4 = Aska::SimpleMessageDispatcher::PostSyncMessageSingle(unsigned short, int*, Aska::INotify*, void*, void*, unsigned int*, signed char)(uVar5,0,piVar1,
                            &
                            PTR__ZTVN4Aska28IDE_NotifyCollisionDetectionILNS_36_Enum_IDECollisionDetectionInputTypeE1ELNS_37_Enum_IDECollisionDetectionOutputTypeE1EEE_16__02ceaef8
                            ,param_2,param_1,0,1);
    while ((uVar4 & 1) == 0) {
      Aska::Thread::Sleep(unsigned int)(1);
      uVar4 = Aska::SimpleMessageDispatcher::PostSyncMessageSingle(unsigned short, int*, Aska::INotify*, void*, void*, unsigned int*, signed char)(uVar5,0,piVar1,
                              &
                              PTR__ZTVN4Aska28IDE_NotifyCollisionDetectionILNS_36_Enum_IDECollisionDetectionInputTypeE1ELNS_37_Enum_IDECollisionDetectionOutputTypeE1EEE_16__02ceaef8
                              ,param_2,param_1,0,1);
    }
  }
  return;
}

// ==== Aska::IDE_CollisionDetectionParam<(Aska::_Enum_IDECollisionDetectionInputType)0, (Aska::_Enum_IDECollisionDetectionOutputType)2>::Dispatch(Aska::IDEPrimitiveBase*)
// vaddr 0x25a2bf0 | ghidra 0x26a2bf0 | size 196 | symbol _ZN4Aska27IDE_CollisionDetectionParamILNS_36_Enum_IDECollisionDetectionInputTypeE0ELNS_37_Enum_IDECollisionDetectionOutputTypeE2EE8DispatchEPNS_16IDEPrimitiveBaseE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska27IDE_CollisionDetectionParamILNS_36_Enum_IDECollisionDetectionInputTypeE0ELNS_37_Enum_IDECollisionDetectionOutputTypeE2EE8DispatchEPNS_16IDEPrimitiveBaseE
               (undefined2 *param_1,long *param_2)

{
  int *piVar1;
  char cVar2;
  bool bVar3;
  ulong uVar4;
  undefined8 uVar5;
  
  uVar4 = (**(code **)(*param_2 + 0x10))(param_2,param_1 + 8,*param_1);
  if ((uVar4 & 1) != 0) {
    piVar1 = (int *)(param_1 + 0x58);
    uVar5 = *(undefined8 *)PTR__ZN4Aska6Global20m_pMessageDispatcherE_02cb77c8;
    do {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar3) {
        *piVar1 = *piVar1 + 1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    uVar4 = Aska::SimpleMessageDispatcher::PostSyncMessageSingle(unsigned short, int*, Aska::INotify*, void*, void*, unsigned int*, signed char)(uVar5,0,piVar1,
                            &
                            PTR__ZTVN4Aska28IDE_NotifyCollisionDetectionILNS_36_Enum_IDECollisionDetectionInputTypeE0ELNS_37_Enum_IDECollisionDetectionOutputTypeE2EEE_16__02ceaf00
                            ,param_2,param_1,0,1);
    while ((uVar4 & 1) == 0) {
      Aska::Thread::Sleep(unsigned int)(1);
      uVar4 = Aska::SimpleMessageDispatcher::PostSyncMessageSingle(unsigned short, int*, Aska::INotify*, void*, void*, unsigned int*, signed char)(uVar5,0,piVar1,
                              &
                              PTR__ZTVN4Aska28IDE_NotifyCollisionDetectionILNS_36_Enum_IDECollisionDetectionInputTypeE0ELNS_37_Enum_IDECollisionDetectionOutputTypeE2EEE_16__02ceaf00
                              ,param_2,param_1,0,1);
    }
  }
  return;
}

// ==== Aska::IDE_CollisionDetectionParam<(Aska::_Enum_IDECollisionDetectionInputType)1, (Aska::_Enum_IDECollisionDetectionOutputType)2>::Dispatch(Aska::IDEPrimitiveBase*)
// vaddr 0x25a2cb4 | ghidra 0x26a2cb4 | size 196 | symbol _ZN4Aska27IDE_CollisionDetectionParamILNS_36_Enum_IDECollisionDetectionInputTypeE1ELNS_37_Enum_IDECollisionDetectionOutputTypeE2EE8DispatchEPNS_16IDEPrimitiveBaseE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska27IDE_CollisionDetectionParamILNS_36_Enum_IDECollisionDetectionInputTypeE1ELNS_37_Enum_IDECollisionDetectionOutputTypeE2EE8DispatchEPNS_16IDEPrimitiveBaseE
               (undefined2 *param_1,long *param_2)

{
  int *piVar1;
  char cVar2;
  bool bVar3;
  ulong uVar4;
  undefined8 uVar5;
  
  uVar4 = (**(code **)(*param_2 + 0x18))(param_2,param_1 + 8,*param_1);
  if ((uVar4 & 1) != 0) {
    piVar1 = (int *)(param_1 + 0x58);
    uVar5 = *(undefined8 *)PTR__ZN4Aska6Global20m_pMessageDispatcherE_02cb77c8;
    do {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar3) {
        *piVar1 = *piVar1 + 1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    uVar4 = Aska::SimpleMessageDispatcher::PostSyncMessageSingle(unsigned short, int*, Aska::INotify*, void*, void*, unsigned int*, signed char)(uVar5,0,piVar1,
                            &
                            PTR__ZTVN4Aska28IDE_NotifyCollisionDetectionILNS_36_Enum_IDECollisionDetectionInputTypeE1ELNS_37_Enum_IDECollisionDetectionOutputTypeE2EEE_16__02ceaf08
                            ,param_2,param_1,0,1);
    while ((uVar4 & 1) == 0) {
      Aska::Thread::Sleep(unsigned int)(1);
      uVar4 = Aska::SimpleMessageDispatcher::PostSyncMessageSingle(unsigned short, int*, Aska::INotify*, void*, void*, unsigned int*, signed char)(uVar5,0,piVar1,
                              &
                              PTR__ZTVN4Aska28IDE_NotifyCollisionDetectionILNS_36_Enum_IDECollisionDetectionInputTypeE1ELNS_37_Enum_IDECollisionDetectionOutputTypeE2EEE_16__02ceaf08
                              ,param_2,param_1,0,1);
    }
  }
  return;
}

// ==== Aska::IDE_CollisionDetectionParam<(Aska::_Enum_IDECollisionDetectionInputType)2, (Aska::_Enum_IDECollisionDetectionOutputType)3>::Dispatch(Aska::IDEPrimitiveBase*, unsigned int)
// vaddr 0x25a2d78 | ghidra 0x26a2d78 | size 260 | symbol _ZN4Aska27IDE_CollisionDetectionParamILNS_36_Enum_IDECollisionDetectionInputTypeE2ELNS_37_Enum_IDECollisionDetectionOutputTypeE3EE8DispatchEPNS_16IDEPrimitiveBaseEj | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska27IDE_CollisionDetectionParamILNS_36_Enum_IDECollisionDetectionInputTypeE2ELNS_37_Enum_IDECollisionDetectionOutputTypeE3EE8DispatchEPNS_16IDEPrimitiveBaseEj
               (undefined2 *param_1,long *param_2,ulong param_3)

{
  undefined8 *puVar1;
  int *piVar2;
  undefined4 uVar3;
  char cVar4;
  bool bVar5;
  ulong uVar6;
  undefined8 uVar7;
  
  puVar1 = (undefined8 *)(*(long *)(param_1 + 0xc) + (param_3 & 0xffffffff) * 0x10);
  uVar3 = *(undefined4 *)(puVar1 + 1);
  *(undefined8 *)(param_1 + 0x18) = *puVar1;
  *(undefined4 *)(param_1 + 0x1c) = uVar3;
  *(undefined4 *)(param_1 + 0x1e) = 0x3f800000;
  uVar6 = (**(code **)(*param_2 + 0x10))(param_2,param_1 + 0x18,*param_1);
  if ((uVar6 & 1) != 0) {
    piVar2 = (int *)(param_1 + 0x2e);
    uVar7 = *(undefined8 *)PTR__ZN4Aska6Global20m_pMessageDispatcherE_02cb77c8;
    do {
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
      if (bVar5) {
        *piVar2 = *piVar2 + 1;
        cVar4 = ExclusiveMonitorsStatus();
      }
    } while (cVar4 != '\0');
    uVar6 = Aska::SimpleMessageDispatcher::PostSyncMessageSingle(unsigned short, int*, Aska::INotify*, void*, void*, unsigned long, unsigned long, unsigned int*, signed char)(uVar7,0,piVar2,
                            &
                            PTR__ZTVN4Aska28IDE_NotifyCollisionDetectionILNS_36_Enum_IDECollisionDetectionInputTypeE2ELNS_37_Enum_IDECollisionDetectionOutputTypeE3EEE_16__02ceaf10
                            ,param_2,param_1,puVar1,0,0,1);
    while ((uVar6 & 1) == 0) {
      Aska::Thread::Sleep(unsigned int)(1);
      uVar6 = Aska::SimpleMessageDispatcher::PostSyncMessageSingle(unsigned short, int*, Aska::INotify*, void*, void*, unsigned long, unsigned long, unsigned int*, signed char)(uVar7,0,piVar2,
                              &
                              PTR__ZTVN4Aska28IDE_NotifyCollisionDetectionILNS_36_Enum_IDECollisionDetectionInputTypeE2ELNS_37_Enum_IDECollisionDetectionOutputTypeE3EEE_16__02ceaf10
                              ,param_2,param_1,puVar1,0,0,1);
    }
  }
  return;
}

// ==== Aska::IDE_CollisionDetectionParam<(Aska::_Enum_IDECollisionDetectionInputType)3, (Aska::_Enum_IDECollisionDetectionOutputType)4>::Dispatch(Aska::IDEPrimitiveBase*, unsigned int)
// vaddr 0x25a2e7c | ghidra 0x26a2e7c | size 248 | symbol _ZN4Aska27IDE_CollisionDetectionParamILNS_36_Enum_IDECollisionDetectionInputTypeE3ELNS_37_Enum_IDECollisionDetectionOutputTypeE4EE8DispatchEPNS_16IDEPrimitiveBaseEj | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska27IDE_CollisionDetectionParamILNS_36_Enum_IDECollisionDetectionInputTypeE3ELNS_37_Enum_IDECollisionDetectionOutputTypeE4EE8DispatchEPNS_16IDEPrimitiveBaseEj
               (undefined2 *param_1,long *param_2,ulong param_3)

{
  int *piVar1;
  long lVar2;
  char cVar3;
  bool bVar4;
  ulong uVar5;
  undefined8 uVar6;
  
  lVar2 = *(long *)(param_1 + 4) + (param_3 & 0xffffffff) * 0x20;
  uVar5 = (**(code **)(*param_2 + 0x10))(param_2,lVar2,*param_1);
  if ((uVar5 & 1) != 0) {
    piVar1 = (int *)(param_1 + 0x12);
    uVar6 = *(undefined8 *)PTR__ZN4Aska6Global20m_pMessageDispatcherE_02cb77c8;
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + 1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
    uVar5 = Aska::SimpleMessageDispatcher::PostSyncMessageSingle(unsigned short, int*, Aska::INotify*, void*, void*, unsigned long, unsigned long, unsigned int*, signed char)(uVar6,0,piVar1,
                            &
                            PTR__ZTVN4Aska28IDE_NotifyCollisionDetectionILNS_36_Enum_IDECollisionDetectionInputTypeE3ELNS_37_Enum_IDECollisionDetectionOutputTypeE4EEE_16__02ceaf18
                            ,param_2,param_1,lVar2,0,0,1);
    while ((uVar5 & 1) == 0) {
      Aska::Thread::Sleep(unsigned int)(1);
      uVar5 = Aska::SimpleMessageDispatcher::PostSyncMessageSingle(unsigned short, int*, Aska::INotify*, void*, void*, unsigned long, unsigned long, unsigned int*, signed char)(uVar6,0,piVar1,
                              &
                              PTR__ZTVN4Aska28IDE_NotifyCollisionDetectionILNS_36_Enum_IDECollisionDetectionInputTypeE3ELNS_37_Enum_IDECollisionDetectionOutputTypeE4EEE_16__02ceaf18
                              ,param_2,param_1,lVar2,0,0,1);
    }
  }
  return;
}

// ==== Aska::IDE_CollisionDetectionParam<(Aska::_Enum_IDECollisionDetectionInputType)4, (Aska::_Enum_IDECollisionDetectionOutputType)4>::Dispatch(Aska::IDEPrimitiveBase*, unsigned int)
// vaddr 0x25a2f74 | ghidra 0x26a2f74 | size 248 | symbol _ZN4Aska27IDE_CollisionDetectionParamILNS_36_Enum_IDECollisionDetectionInputTypeE4ELNS_37_Enum_IDECollisionDetectionOutputTypeE4EE8DispatchEPNS_16IDEPrimitiveBaseEj | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska27IDE_CollisionDetectionParamILNS_36_Enum_IDECollisionDetectionInputTypeE4ELNS_37_Enum_IDECollisionDetectionOutputTypeE4EE8DispatchEPNS_16IDEPrimitiveBaseEj
               (undefined2 *param_1,long *param_2,ulong param_3)

{
  int *piVar1;
  long lVar2;
  char cVar3;
  bool bVar4;
  ulong uVar5;
  undefined8 uVar6;
  
  lVar2 = *(long *)(param_1 + 4) + (param_3 & 0xffffffff) * 0x20;
  uVar5 = (**(code **)(*param_2 + 0x18))(param_2,lVar2,*param_1);
  if ((uVar5 & 1) != 0) {
    piVar1 = (int *)(param_1 + 0x12);
    uVar6 = *(undefined8 *)PTR__ZN4Aska6Global20m_pMessageDispatcherE_02cb77c8;
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + 1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
    uVar5 = Aska::SimpleMessageDispatcher::PostSyncMessageSingle(unsigned short, int*, Aska::INotify*, void*, void*, unsigned long, unsigned long, unsigned int*, signed char)(uVar6,0,piVar1,
                            &
                            PTR__ZTVN4Aska28IDE_NotifyCollisionDetectionILNS_36_Enum_IDECollisionDetectionInputTypeE4ELNS_37_Enum_IDECollisionDetectionOutputTypeE4EEE_16__02ceaf20
                            ,param_2,param_1,lVar2,0,0,1);
    while ((uVar5 & 1) == 0) {
      Aska::Thread::Sleep(unsigned int)(1);
      uVar5 = Aska::SimpleMessageDispatcher::PostSyncMessageSingle(unsigned short, int*, Aska::INotify*, void*, void*, unsigned long, unsigned long, unsigned int*, signed char)(uVar6,0,piVar1,
                              &
                              PTR__ZTVN4Aska28IDE_NotifyCollisionDetectionILNS_36_Enum_IDECollisionDetectionInputTypeE4ELNS_37_Enum_IDECollisionDetectionOutputTypeE4EEE_16__02ceaf20
                              ,param_2,param_1,lVar2,0,0,1);
    }
  }
  return;
}

// ==== Aska::IDE_CollisionDetectionParam<(Aska::_Enum_IDECollisionDetectionInputType)5, (Aska::_Enum_IDECollisionDetectionOutputType)5>::Dispatch(Aska::IDEPrimitiveBase*)
// vaddr 0x25a306c | ghidra 0x26a306c | size 196 | symbol _ZN4Aska27IDE_CollisionDetectionParamILNS_36_Enum_IDECollisionDetectionInputTypeE5ELNS_37_Enum_IDECollisionDetectionOutputTypeE5EE8DispatchEPNS_16IDEPrimitiveBaseE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska27IDE_CollisionDetectionParamILNS_36_Enum_IDECollisionDetectionInputTypeE5ELNS_37_Enum_IDECollisionDetectionOutputTypeE5EE8DispatchEPNS_16IDEPrimitiveBaseE
               (undefined2 *param_1,long *param_2)

{
  int *piVar1;
  char cVar2;
  bool bVar3;
  ulong uVar4;
  undefined8 uVar5;
  
  uVar4 = (**(code **)(*param_2 + 0x20))(param_2,param_1 + 8,*param_1);
  if ((uVar4 & 1) != 0) {
    piVar1 = (int *)(param_1 + 0x14);
    uVar5 = *(undefined8 *)PTR__ZN4Aska6Global20m_pMessageDispatcherE_02cb77c8;
    do {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar3) {
        *piVar1 = *piVar1 + 1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    uVar4 = Aska::SimpleMessageDispatcher::PostSyncMessageSingle(unsigned short, int*, Aska::INotify*, void*, void*, unsigned int*, signed char)(uVar5,0,piVar1,
                            &
                            PTR__ZTVN4Aska28IDE_NotifyCollisionDetectionILNS_36_Enum_IDECollisionDetectionInputTypeE5ELNS_37_Enum_IDECollisionDetectionOutputTypeE5EEE_16__02ceaf28
                            ,param_2,param_1,0,1);
    while ((uVar4 & 1) == 0) {
      Aska::Thread::Sleep(unsigned int)(1);
      uVar4 = Aska::SimpleMessageDispatcher::PostSyncMessageSingle(unsigned short, int*, Aska::INotify*, void*, void*, unsigned int*, signed char)(uVar5,0,piVar1,
                              &
                              PTR__ZTVN4Aska28IDE_NotifyCollisionDetectionILNS_36_Enum_IDECollisionDetectionInputTypeE5ELNS_37_Enum_IDECollisionDetectionOutputTypeE5EEE_16__02ceaf28
                              ,param_2,param_1,0,1);
    }
  }
  return;
}

// ==== Aska::IDE_NotifyCollisionDetection<(Aska::_Enum_IDECollisionDetectionInputType)0, (Aska::_Enum_IDECollisionDetectionOutputType)0>::Handler(unsigned long)
// vaddr 0x25a32a0 | ghidra 0x26a32a0 | size 60 | symbol _ZN4Aska28IDE_NotifyCollisionDetectionILNS_36_Enum_IDECollisionDetectionInputTypeE0ELNS_37_Enum_IDECollisionDetectionOutputTypeE0EE7HandlerEm | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska28IDE_NotifyCollisionDetectionILNS_36_Enum_IDECollisionDetectionInputTypeE0ELNS_37_Enum_IDECollisionDetectionOutputTypeE0EE7HandlerEm
               (undefined8 param_1,long param_2)

{
  undefined2 *puVar1;
  char cVar2;
  bool bVar3;
  ulong uVar4;
  
  puVar1 = *(undefined2 **)(param_2 + 0x38);
  uVar4 = (**(code **)(**(long **)(param_2 + 0x30) + 0x38))
                    (*(long **)(param_2 + 0x30),puVar1 + 8,*puVar1);
  if ((uVar4 & 1) != 0) {
    do {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(puVar1 + 0x18,0x10);
      if (bVar3) {
        *(undefined4 *)(puVar1 + 0x18) = 1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
  }
  return;
}

// ==== Aska::IDE_NotifyCollisionDetection<(Aska::_Enum_IDECollisionDetectionInputType)0, (Aska::_Enum_IDECollisionDetectionOutputType)0>::~IDE_NotifyCollisionDetection()
// vaddr 0x25a32dc | ghidra 0x26a32dc | size 4 | symbol _ZN4Aska28IDE_NotifyCollisionDetectionILNS_36_Enum_IDECollisionDetectionInputTypeE0ELNS_37_Enum_IDECollisionDetectionOutputTypeE0EED0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska28IDE_NotifyCollisionDetectionILNS_36_Enum_IDECollisionDetectionInputTypeE0ELNS_37_Enum_IDECollisionDetectionOutputTypeE0EED0Ev
               (void)

{
  (*(code *)PTR__ZdlPv_02ca4758)();
  return;
}

// ==== Aska::IDE_NotifyCollisionDetection<(Aska::_Enum_IDECollisionDetectionInputType)1, (Aska::_Enum_IDECollisionDetectionOutputType)0>::Handler(unsigned long)
// vaddr 0x25a32e0 | ghidra 0x26a32e0 | size 60 | symbol _ZN4Aska28IDE_NotifyCollisionDetectionILNS_36_Enum_IDECollisionDetectionInputTypeE1ELNS_37_Enum_IDECollisionDetectionOutputTypeE0EE7HandlerEm | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska28IDE_NotifyCollisionDetectionILNS_36_Enum_IDECollisionDetectionInputTypeE1ELNS_37_Enum_IDECollisionDetectionOutputTypeE0EE7HandlerEm
               (undefined8 param_1,long param_2)

{
  undefined2 *puVar1;
  char cVar2;
  bool bVar3;
  ulong uVar4;
  
  puVar1 = *(undefined2 **)(param_2 + 0x38);
  uVar4 = (**(code **)(**(long **)(param_2 + 0x30) + 0x40))
                    (*(long **)(param_2 + 0x30),puVar1 + 8,*puVar1);
  if ((uVar4 & 1) != 0) {
    do {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(puVar1 + 0x18,0x10);
      if (bVar3) {
        *(undefined4 *)(puVar1 + 0x18) = 1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
  }
  return;
}

// ==== Aska::IDE_NotifyCollisionDetection<(Aska::_Enum_IDECollisionDetectionInputType)1, (Aska::_Enum_IDECollisionDetectionOutputType)0>::~IDE_NotifyCollisionDetection()
// vaddr 0x25a331c | ghidra 0x26a331c | size 4 | symbol _ZN4Aska28IDE_NotifyCollisionDetectionILNS_36_Enum_IDECollisionDetectionInputTypeE1ELNS_37_Enum_IDECollisionDetectionOutputTypeE0EED0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska28IDE_NotifyCollisionDetectionILNS_36_Enum_IDECollisionDetectionInputTypeE1ELNS_37_Enum_IDECollisionDetectionOutputTypeE0EED0Ev
               (void)

{
  (*(code *)PTR__ZdlPv_02ca4758)();
  return;
}

// ==== Aska::IDE_NotifyCollisionDetection<(Aska::_Enum_IDECollisionDetectionInputType)0, (Aska::_Enum_IDECollisionDetectionOutputType)1>::Handler(unsigned long)
// vaddr 0x25a3320 | ghidra 0x26a3320 | size 148 | symbol _ZN4Aska28IDE_NotifyCollisionDetectionILNS_36_Enum_IDECollisionDetectionInputTypeE0ELNS_37_Enum_IDECollisionDetectionOutputTypeE1EE7HandlerEm | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska28IDE_NotifyCollisionDetectionILNS_36_Enum_IDECollisionDetectionInputTypeE0ELNS_37_Enum_IDECollisionDetectionOutputTypeE1EE7HandlerEm
               (undefined8 param_1,long param_2)

{
  int *piVar1;
  undefined2 *puVar2;
  char cVar3;
  bool bVar4;
  ulong uVar5;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  float fStack_14;
  
  puVar2 = *(undefined2 **)(param_2 + 0x38);
  uVar5 = (**(code **)(**(long **)(param_2 + 0x30) + 0x48))
                    (*(long **)(param_2 + 0x30),&uStack_20,puVar2 + 8,*puVar2);
  if ((uVar5 & 1) != 0) {
    piVar1 = (int *)(puVar2 + 0x24);
    do {
      while (*piVar1 != 0) {
        ClearExclusiveLocal();
      }
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = 1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
    if (fStack_14 < *(float *)(puVar2 + 0x1e)) {
      *(undefined4 *)(puVar2 + 0x18) = uStack_20;
      *(undefined4 *)(puVar2 + 0x1a) = uStack_1c;
      *(float *)(puVar2 + 0x1e) = fStack_14;
      *(undefined1 *)(puVar2 + 0x20) = 1;
      *(undefined4 *)(puVar2 + 0x1c) = uStack_18;
    }
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = 0;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
  }
  return;
}

// ==== Aska::IDE_NotifyCollisionDetection<(Aska::_Enum_IDECollisionDetectionInputType)0, (Aska::_Enum_IDECollisionDetectionOutputType)1>::~IDE_NotifyCollisionDetection()
// vaddr 0x25a33b4 | ghidra 0x26a33b4 | size 4 | symbol _ZN4Aska28IDE_NotifyCollisionDetectionILNS_36_Enum_IDECollisionDetectionInputTypeE0ELNS_37_Enum_IDECollisionDetectionOutputTypeE1EED0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska28IDE_NotifyCollisionDetectionILNS_36_Enum_IDECollisionDetectionInputTypeE0ELNS_37_Enum_IDECollisionDetectionOutputTypeE1EED0Ev
               (void)

{
  (*(code *)PTR__ZdlPv_02ca4758)();
  return;
}

// ==== Aska::IDE_NotifyCollisionDetection<(Aska::_Enum_IDECollisionDetectionInputType)1, (Aska::_Enum_IDECollisionDetectionOutputType)1>::Handler(unsigned long)
// vaddr 0x25a33b8 | ghidra 0x26a33b8 | size 148 | symbol _ZN4Aska28IDE_NotifyCollisionDetectionILNS_36_Enum_IDECollisionDetectionInputTypeE1ELNS_37_Enum_IDECollisionDetectionOutputTypeE1EE7HandlerEm | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska28IDE_NotifyCollisionDetectionILNS_36_Enum_IDECollisionDetectionInputTypeE1ELNS_37_Enum_IDECollisionDetectionOutputTypeE1EE7HandlerEm
               (undefined8 param_1,long param_2)

{
  int *piVar1;
  undefined2 *puVar2;
  char cVar3;
  bool bVar4;
  ulong uVar5;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  float fStack_14;
  
  puVar2 = *(undefined2 **)(param_2 + 0x38);
  uVar5 = (**(code **)(**(long **)(param_2 + 0x30) + 0x50))
                    (*(long **)(param_2 + 0x30),&uStack_20,puVar2 + 8,*puVar2);
  if ((uVar5 & 1) != 0) {
    piVar1 = (int *)(puVar2 + 0x24);
    do {
      while (*piVar1 != 0) {
        ClearExclusiveLocal();
      }
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = 1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
    if (fStack_14 < *(float *)(puVar2 + 0x1e)) {
      *(undefined4 *)(puVar2 + 0x18) = uStack_20;
      *(undefined4 *)(puVar2 + 0x1a) = uStack_1c;
      *(float *)(puVar2 + 0x1e) = fStack_14;
      *(undefined1 *)(puVar2 + 0x20) = 1;
      *(undefined4 *)(puVar2 + 0x1c) = uStack_18;
    }
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = 0;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
  }
  return;
}

// ==== Aska::IDE_NotifyCollisionDetection<(Aska::_Enum_IDECollisionDetectionInputType)1, (Aska::_Enum_IDECollisionDetectionOutputType)1>::~IDE_NotifyCollisionDetection()
// vaddr 0x25a344c | ghidra 0x26a344c | size 4 | symbol _ZN4Aska28IDE_NotifyCollisionDetectionILNS_36_Enum_IDECollisionDetectionInputTypeE1ELNS_37_Enum_IDECollisionDetectionOutputTypeE1EED0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska28IDE_NotifyCollisionDetectionILNS_36_Enum_IDECollisionDetectionInputTypeE1ELNS_37_Enum_IDECollisionDetectionOutputTypeE1EED0Ev
               (void)

{
  (*(code *)PTR__ZdlPv_02ca4758)();
  return;
}

// ==== Aska::IDE_NotifyCollisionDetection<(Aska::_Enum_IDECollisionDetectionInputType)0, (Aska::_Enum_IDECollisionDetectionOutputType)2>::Handler(unsigned long)
// vaddr 0x25a3450 | ghidra 0x26a3450 | size 176 | symbol _ZN4Aska28IDE_NotifyCollisionDetectionILNS_36_Enum_IDECollisionDetectionInputTypeE0ELNS_37_Enum_IDECollisionDetectionOutputTypeE2EE7HandlerEm | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska28IDE_NotifyCollisionDetectionILNS_36_Enum_IDECollisionDetectionInputTypeE0ELNS_37_Enum_IDECollisionDetectionOutputTypeE2EE7HandlerEm
               (undefined8 param_1,long param_2)

{
  int *piVar1;
  undefined2 *puVar2;
  char cVar3;
  bool bVar4;
  ulong uVar5;
  undefined8 uStack_90;
  undefined4 uStack_88;
  float fStack_84;
  undefined8 uStack_80;
  undefined8 uStack_78;
  undefined8 uStack_70;
  undefined8 uStack_68;
  undefined8 uStack_60;
  undefined8 uStack_58;
  undefined8 uStack_50;
  undefined8 uStack_48;
  undefined8 uStack_40;
  undefined8 uStack_38;
  undefined8 uStack_30;
  undefined8 uStack_28;
  undefined8 uStack_20;
  undefined8 uStack_18;
  
  puVar2 = *(undefined2 **)(param_2 + 0x38);
  uVar5 = (**(code **)(**(long **)(param_2 + 0x30) + 0x58))
                    (*(long **)(param_2 + 0x30),&uStack_90,puVar2 + 8,*puVar2);
  if ((uVar5 & 1) != 0) {
    piVar1 = (int *)(puVar2 + 0x5a);
    do {
      while (*piVar1 != 0) {
        ClearExclusiveLocal();
      }
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = 1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
    if (fStack_84 < *(float *)(puVar2 + 0x1e)) {
      *(ulong *)(puVar2 + 0x1c) = CONCAT44(fStack_84,uStack_88);
      *(undefined8 *)(puVar2 + 0x18) = uStack_90;
      *(undefined8 *)(puVar2 + 0x24) = uStack_78;
      *(undefined8 *)(puVar2 + 0x20) = uStack_80;
      *(undefined8 *)(puVar2 + 0x2c) = uStack_68;
      *(undefined8 *)(puVar2 + 0x28) = uStack_70;
      *(undefined8 *)(puVar2 + 0x34) = uStack_58;
      *(undefined8 *)(puVar2 + 0x30) = uStack_60;
      *(undefined8 *)(puVar2 + 0x3c) = uStack_48;
      *(undefined8 *)(puVar2 + 0x38) = uStack_50;
      *(undefined8 *)(puVar2 + 0x44) = uStack_38;
      *(undefined8 *)(puVar2 + 0x40) = uStack_40;
      *(undefined8 *)(puVar2 + 0x4c) = uStack_28;
      *(undefined8 *)(puVar2 + 0x48) = uStack_30;
      *(undefined8 *)(puVar2 + 0x54) = uStack_18;
      *(undefined8 *)(puVar2 + 0x50) = uStack_20;
    }
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = 0;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
  }
  return;
}

// ==== Aska::IDE_NotifyCollisionDetection<(Aska::_Enum_IDECollisionDetectionInputType)0, (Aska::_Enum_IDECollisionDetectionOutputType)2>::~IDE_NotifyCollisionDetection()
// vaddr 0x25a3500 | ghidra 0x26a3500 | size 4 | symbol _ZN4Aska28IDE_NotifyCollisionDetectionILNS_36_Enum_IDECollisionDetectionInputTypeE0ELNS_37_Enum_IDECollisionDetectionOutputTypeE2EED0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska28IDE_NotifyCollisionDetectionILNS_36_Enum_IDECollisionDetectionInputTypeE0ELNS_37_Enum_IDECollisionDetectionOutputTypeE2EED0Ev
               (void)

{
  (*(code *)PTR__ZdlPv_02ca4758)();
  return;
}

// ==== Aska::IDE_NotifyCollisionDetection<(Aska::_Enum_IDECollisionDetectionInputType)1, (Aska::_Enum_IDECollisionDetectionOutputType)2>::Handler(unsigned long)
// vaddr 0x25a3504 | ghidra 0x26a3504 | size 176 | symbol _ZN4Aska28IDE_NotifyCollisionDetectionILNS_36_Enum_IDECollisionDetectionInputTypeE1ELNS_37_Enum_IDECollisionDetectionOutputTypeE2EE7HandlerEm | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska28IDE_NotifyCollisionDetectionILNS_36_Enum_IDECollisionDetectionInputTypeE1ELNS_37_Enum_IDECollisionDetectionOutputTypeE2EE7HandlerEm
               (undefined8 param_1,long param_2)

{
  int *piVar1;
  undefined2 *puVar2;
  char cVar3;
  bool bVar4;
  ulong uVar5;
  undefined8 uStack_90;
  undefined4 uStack_88;
  float fStack_84;
  undefined8 uStack_80;
  undefined8 uStack_78;
  undefined8 uStack_70;
  undefined8 uStack_68;
  undefined8 uStack_60;
  undefined8 uStack_58;
  undefined8 uStack_50;
  undefined8 uStack_48;
  undefined8 uStack_40;
  undefined8 uStack_38;
  undefined8 uStack_30;
  undefined8 uStack_28;
  undefined8 uStack_20;
  undefined8 uStack_18;
  
  puVar2 = *(undefined2 **)(param_2 + 0x38);
  uVar5 = (**(code **)(**(long **)(param_2 + 0x30) + 0x60))
                    (*(long **)(param_2 + 0x30),&uStack_90,puVar2 + 8,*puVar2);
  if ((uVar5 & 1) != 0) {
    piVar1 = (int *)(puVar2 + 0x5a);
    do {
      while (*piVar1 != 0) {
        ClearExclusiveLocal();
      }
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = 1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
    if (fStack_84 < *(float *)(puVar2 + 0x1e)) {
      *(ulong *)(puVar2 + 0x1c) = CONCAT44(fStack_84,uStack_88);
      *(undefined8 *)(puVar2 + 0x18) = uStack_90;
      *(undefined8 *)(puVar2 + 0x24) = uStack_78;
      *(undefined8 *)(puVar2 + 0x20) = uStack_80;
      *(undefined8 *)(puVar2 + 0x2c) = uStack_68;
      *(undefined8 *)(puVar2 + 0x28) = uStack_70;
      *(undefined8 *)(puVar2 + 0x34) = uStack_58;
      *(undefined8 *)(puVar2 + 0x30) = uStack_60;
      *(undefined8 *)(puVar2 + 0x3c) = uStack_48;
      *(undefined8 *)(puVar2 + 0x38) = uStack_50;
      *(undefined8 *)(puVar2 + 0x44) = uStack_38;
      *(undefined8 *)(puVar2 + 0x40) = uStack_40;
      *(undefined8 *)(puVar2 + 0x4c) = uStack_28;
      *(undefined8 *)(puVar2 + 0x48) = uStack_30;
      *(undefined8 *)(puVar2 + 0x54) = uStack_18;
      *(undefined8 *)(puVar2 + 0x50) = uStack_20;
    }
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = 0;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
  }
  return;
}

// ==== Aska::IDE_NotifyCollisionDetection<(Aska::_Enum_IDECollisionDetectionInputType)1, (Aska::_Enum_IDECollisionDetectionOutputType)2>::~IDE_NotifyCollisionDetection()
// vaddr 0x25a35b4 | ghidra 0x26a35b4 | size 4 | symbol _ZN4Aska28IDE_NotifyCollisionDetectionILNS_36_Enum_IDECollisionDetectionInputTypeE1ELNS_37_Enum_IDECollisionDetectionOutputTypeE2EED0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska28IDE_NotifyCollisionDetectionILNS_36_Enum_IDECollisionDetectionInputTypeE1ELNS_37_Enum_IDECollisionDetectionOutputTypeE2EED0Ev
               (void)

{
  (*(code *)PTR__ZdlPv_02ca4758)();
  return;
}

// ==== Aska::IDE_NotifyCollisionDetection<(Aska::_Enum_IDECollisionDetectionInputType)2, (Aska::_Enum_IDECollisionDetectionOutputType)3>::Handler(unsigned long)
// vaddr 0x25a35b8 | ghidra 0x26a35b8 | size 284 | symbol _ZN4Aska28IDE_NotifyCollisionDetectionILNS_36_Enum_IDECollisionDetectionInputTypeE2ELNS_37_Enum_IDECollisionDetectionOutputTypeE3EE7HandlerEm | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska28IDE_NotifyCollisionDetectionILNS_36_Enum_IDECollisionDetectionInputTypeE2ELNS_37_Enum_IDECollisionDetectionOutputTypeE3EE7HandlerEm
               (undefined8 param_1,long param_2)

{
  float *pfVar1;
  int *piVar2;
  long *plVar3;
  undefined2 *puVar4;
  char cVar5;
  bool bVar6;
  undefined8 uVar7;
  undefined *puVar8;
  int iVar9;
  ulong uVar10;
  undefined8 *puVar11;
  long lVar12;
  undefined8 uStack_60;
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined8 uStack_50;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined1 auStack_40 [4];
  float fStack_3c;
  
  plVar3 = *(long **)(param_2 + 0x30);
  puVar4 = *(undefined2 **)(param_2 + 0x38);
  puVar11 = *(undefined8 **)(param_2 + 0x40);
  lVar12 = *(long *)(puVar4 + 0xc);
  if (((*
        PTR__ZGVZN4Aska28IDE_NotifyCollisionDetectionILNS_36_Enum_IDECollisionDetectionInputTypeE2ELNS_37_Enum_IDECollisionDetectionOutputTypeE3EE7HandlerEmE3dir_02cb6dc0
       & 1) == 0) &&
     (iVar9 = __cxa_guard_acquire(
                             PTR__ZGVZN4Aska28IDE_NotifyCollisionDetectionILNS_36_Enum_IDECollisionDetectionInputTypeE2ELNS_37_Enum_IDECollisionDetectionOutputTypeE3EE7HandlerEmE3dir_02cb6dc0
                             ),
     puVar8 = 
     PTR__ZZN4Aska28IDE_NotifyCollisionDetectionILNS_36_Enum_IDECollisionDetectionInputTypeE2ELNS_37_Enum_IDECollisionDetectionOutputTypeE3EE7HandlerEmE3dir_02cbfce8
     , uVar7 = _UNK_029cc820, iVar9 != 0)) {
    *(undefined8 *)
     (
     PTR__ZZN4Aska28IDE_NotifyCollisionDetectionILNS_36_Enum_IDECollisionDetectionInputTypeE2ELNS_37_Enum_IDECollisionDetectionOutputTypeE3EE7HandlerEmE3dir_02cbfce8
     + 8) = _UNK_029cc828;
    *(undefined8 *)puVar8 = uVar7;
    __cxa_guard_release(
                   PTR__ZGVZN4Aska28IDE_NotifyCollisionDetectionILNS_36_Enum_IDECollisionDetectionInputTypeE2ELNS_37_Enum_IDECollisionDetectionOutputTypeE3EE7HandlerEmE3dir_02cb6dc0
                   );
  }
  uStack_60 = *puVar11;
  uStack_58 = *(undefined4 *)(puVar11 + 1);
  uStack_54 = 0x3f800000;
  uStack_50 = *(undefined8 *)
               PTR__ZZN4Aska28IDE_NotifyCollisionDetectionILNS_36_Enum_IDECollisionDetectionInputTypeE2ELNS_37_Enum_IDECollisionDetectionOutputTypeE3EE7HandlerEmE3dir_02cbfce8
  ;
  uStack_48 = *(undefined4 *)
               (
               PTR__ZZN4Aska28IDE_NotifyCollisionDetectionILNS_36_Enum_IDECollisionDetectionInputTypeE2ELNS_37_Enum_IDECollisionDetectionOutputTypeE3EE7HandlerEmE3dir_02cbfce8
               + 8);
  uStack_44 = 0x3f800000;
  uVar10 = (**(code **)(*plVar3 + 0x48))(plVar3,auStack_40,&uStack_60,*puVar4);
  if ((uVar10 & 1) != 0) {
    piVar2 = (int *)(puVar4 + 0x30);
    do {
      while (*piVar2 != 0) {
        ClearExclusiveLocal();
      }
      cVar5 = '\x01';
      bVar6 = (bool)ExclusiveMonitorPass(piVar2,0x10);
      if (bVar6) {
        *piVar2 = 1;
        cVar5 = ExclusiveMonitorsStatus();
      }
    } while (cVar5 != '\0');
    pfVar1 = (float *)(*(long *)(puVar4 + 0x28) +
                      ((ulong)((long)puVar11 - lVar12) >> 4 & 0xffffffff) * 8);
    if (*pfVar1 < fStack_3c) {
      *pfVar1 = fStack_3c;
      *(undefined1 *)
       (*(long *)(puVar4 + 0x28) + ((ulong)((long)puVar11 - lVar12) >> 4 & 0xffffffff) * 8 + 4) = 0;
    }
    do {
      cVar5 = '\x01';
      bVar6 = (bool)ExclusiveMonitorPass(piVar2,0x10);
      if (bVar6) {
        *piVar2 = 0;
        cVar5 = ExclusiveMonitorsStatus();
      }
    } while (cVar5 != '\0');
  }
  return;
}

// ==== Aska::IDE_NotifyCollisionDetection<(Aska::_Enum_IDECollisionDetectionInputType)2, (Aska::_Enum_IDECollisionDetectionOutputType)3>::~IDE_NotifyCollisionDetection()
// vaddr 0x25a36d4 | ghidra 0x26a36d4 | size 4 | symbol _ZN4Aska28IDE_NotifyCollisionDetectionILNS_36_Enum_IDECollisionDetectionInputTypeE2ELNS_37_Enum_IDECollisionDetectionOutputTypeE3EED0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska28IDE_NotifyCollisionDetectionILNS_36_Enum_IDECollisionDetectionInputTypeE2ELNS_37_Enum_IDECollisionDetectionOutputTypeE3EED0Ev
               (void)

{
  (*(code *)PTR__ZdlPv_02ca4758)();
  return;
}

// ==== Aska::IDE_NotifyCollisionDetection<(Aska::_Enum_IDECollisionDetectionInputType)3, (Aska::_Enum_IDECollisionDetectionOutputType)4>::Handler(unsigned long)
// vaddr 0x25a36d8 | ghidra 0x26a36d8 | size 208 | symbol _ZN4Aska28IDE_NotifyCollisionDetectionILNS_36_Enum_IDECollisionDetectionInputTypeE3ELNS_37_Enum_IDECollisionDetectionOutputTypeE4EE7HandlerEm | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska28IDE_NotifyCollisionDetectionILNS_36_Enum_IDECollisionDetectionInputTypeE3ELNS_37_Enum_IDECollisionDetectionOutputTypeE4EE7HandlerEm
               (undefined8 param_1,long param_2)

{
  int *piVar1;
  undefined8 *puVar2;
  undefined2 *puVar3;
  char cVar4;
  bool bVar5;
  ulong uVar6;
  long lVar7;
  long lVar8;
  undefined8 uStack_a0;
  undefined4 uStack_98;
  float fStack_94;
  undefined8 uStack_90;
  undefined8 uStack_88;
  undefined8 uStack_80;
  undefined8 uStack_78;
  undefined8 uStack_70;
  undefined8 uStack_68;
  undefined8 uStack_60;
  undefined8 uStack_58;
  undefined8 uStack_50;
  undefined8 uStack_48;
  undefined8 uStack_40;
  undefined8 uStack_38;
  undefined8 uStack_30;
  undefined8 uStack_28;
  
  puVar3 = *(undefined2 **)(param_2 + 0x38);
  lVar7 = *(long *)(param_2 + 0x40);
  lVar8 = *(long *)(puVar3 + 4);
  uVar6 = (**(code **)(**(long **)(param_2 + 0x30) + 0x58))
                    (*(long **)(param_2 + 0x30),&uStack_a0,lVar7,*puVar3);
  if ((uVar6 & 1) != 0) {
    piVar1 = (int *)(puVar3 + 0x14);
    do {
      while (*piVar1 != 0) {
        ClearExclusiveLocal();
      }
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar5) {
        *piVar1 = 1;
        cVar4 = ExclusiveMonitorsStatus();
      }
    } while (cVar4 != '\0');
    puVar2 = (undefined8 *)
             (*(long *)(puVar3 + 0xc) + ((ulong)(lVar7 - lVar8) >> 5 & 0xffffffff) * 0x80);
    if (fStack_94 < *(float *)((long)puVar2 + 0xc)) {
      puVar2[1] = CONCAT44(fStack_94,uStack_98);
      *puVar2 = uStack_a0;
      puVar2[3] = uStack_88;
      puVar2[2] = uStack_90;
      puVar2[5] = uStack_78;
      puVar2[4] = uStack_80;
      puVar2[7] = uStack_68;
      puVar2[6] = uStack_70;
      puVar2[9] = uStack_58;
      puVar2[8] = uStack_60;
      puVar2[0xb] = uStack_48;
      puVar2[10] = uStack_50;
      puVar2[0xd] = uStack_38;
      puVar2[0xc] = uStack_40;
      puVar2[0xf] = uStack_28;
      puVar2[0xe] = uStack_30;
    }
    do {
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar5) {
        *piVar1 = 0;
        cVar4 = ExclusiveMonitorsStatus();
      }
    } while (cVar4 != '\0');
  }
  return;
}

// ==== Aska::IDE_NotifyCollisionDetection<(Aska::_Enum_IDECollisionDetectionInputType)3, (Aska::_Enum_IDECollisionDetectionOutputType)4>::~IDE_NotifyCollisionDetection()
// vaddr 0x25a37a8 | ghidra 0x26a37a8 | size 4 | symbol _ZN4Aska28IDE_NotifyCollisionDetectionILNS_36_Enum_IDECollisionDetectionInputTypeE3ELNS_37_Enum_IDECollisionDetectionOutputTypeE4EED0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska28IDE_NotifyCollisionDetectionILNS_36_Enum_IDECollisionDetectionInputTypeE3ELNS_37_Enum_IDECollisionDetectionOutputTypeE4EED0Ev
               (void)

{
  (*(code *)PTR__ZdlPv_02ca4758)();
  return;
}

// ==== Aska::IDE_NotifyCollisionDetection<(Aska::_Enum_IDECollisionDetectionInputType)4, (Aska::_Enum_IDECollisionDetectionOutputType)4>::Handler(unsigned long)
// vaddr 0x25a37ac | ghidra 0x26a37ac | size 208 | symbol _ZN4Aska28IDE_NotifyCollisionDetectionILNS_36_Enum_IDECollisionDetectionInputTypeE4ELNS_37_Enum_IDECollisionDetectionOutputTypeE4EE7HandlerEm | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska28IDE_NotifyCollisionDetectionILNS_36_Enum_IDECollisionDetectionInputTypeE4ELNS_37_Enum_IDECollisionDetectionOutputTypeE4EE7HandlerEm
               (undefined8 param_1,long param_2)

{
  int *piVar1;
  undefined8 *puVar2;
  undefined2 *puVar3;
  char cVar4;
  bool bVar5;
  ulong uVar6;
  long lVar7;
  long lVar8;
  undefined8 uStack_a0;
  undefined4 uStack_98;
  float fStack_94;
  undefined8 uStack_90;
  undefined8 uStack_88;
  undefined8 uStack_80;
  undefined8 uStack_78;
  undefined8 uStack_70;
  undefined8 uStack_68;
  undefined8 uStack_60;
  undefined8 uStack_58;
  undefined8 uStack_50;
  undefined8 uStack_48;
  undefined8 uStack_40;
  undefined8 uStack_38;
  undefined8 uStack_30;
  undefined8 uStack_28;
  
  puVar3 = *(undefined2 **)(param_2 + 0x38);
  lVar7 = *(long *)(param_2 + 0x40);
  lVar8 = *(long *)(puVar3 + 4);
  uVar6 = (**(code **)(**(long **)(param_2 + 0x30) + 0x60))
                    (*(long **)(param_2 + 0x30),&uStack_a0,lVar7,*puVar3);
  if ((uVar6 & 1) != 0) {
    piVar1 = (int *)(puVar3 + 0x14);
    do {
      while (*piVar1 != 0) {
        ClearExclusiveLocal();
      }
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar5) {
        *piVar1 = 1;
        cVar4 = ExclusiveMonitorsStatus();
      }
    } while (cVar4 != '\0');
    puVar2 = (undefined8 *)
             (*(long *)(puVar3 + 0xc) + ((ulong)(lVar7 - lVar8) >> 5 & 0xffffffff) * 0x80);
    if (fStack_94 < *(float *)((long)puVar2 + 0xc)) {
      puVar2[1] = CONCAT44(fStack_94,uStack_98);
      *puVar2 = uStack_a0;
      puVar2[3] = uStack_88;
      puVar2[2] = uStack_90;
      puVar2[5] = uStack_78;
      puVar2[4] = uStack_80;
      puVar2[7] = uStack_68;
      puVar2[6] = uStack_70;
      puVar2[9] = uStack_58;
      puVar2[8] = uStack_60;
      puVar2[0xb] = uStack_48;
      puVar2[10] = uStack_50;
      puVar2[0xd] = uStack_38;
      puVar2[0xc] = uStack_40;
      puVar2[0xf] = uStack_28;
      puVar2[0xe] = uStack_30;
    }
    do {
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar5) {
        *piVar1 = 0;
        cVar4 = ExclusiveMonitorsStatus();
      }
    } while (cVar4 != '\0');
  }
  return;
}

// ==== Aska::IDE_NotifyCollisionDetection<(Aska::_Enum_IDECollisionDetectionInputType)4, (Aska::_Enum_IDECollisionDetectionOutputType)4>::~IDE_NotifyCollisionDetection()
// vaddr 0x25a387c | ghidra 0x26a387c | size 4 | symbol _ZN4Aska28IDE_NotifyCollisionDetectionILNS_36_Enum_IDECollisionDetectionInputTypeE4ELNS_37_Enum_IDECollisionDetectionOutputTypeE4EED0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska28IDE_NotifyCollisionDetectionILNS_36_Enum_IDECollisionDetectionInputTypeE4ELNS_37_Enum_IDECollisionDetectionOutputTypeE4EED0Ev
               (void)

{
  (*(code *)PTR__ZdlPv_02ca4758)();
  return;
}

// ==== Aska::IDE_NotifyCollisionDetection<(Aska::_Enum_IDECollisionDetectionInputType)5, (Aska::_Enum_IDECollisionDetectionOutputType)5>::Handler(unsigned long)
// vaddr 0x25a3880 | ghidra 0x26a3880 | size 28 | symbol _ZN4Aska28IDE_NotifyCollisionDetectionILNS_36_Enum_IDECollisionDetectionInputTypeE5ELNS_37_Enum_IDECollisionDetectionOutputTypeE5EE7HandlerEm | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska28IDE_NotifyCollisionDetectionILNS_36_Enum_IDECollisionDetectionInputTypeE5ELNS_37_Enum_IDECollisionDetectionOutputTypeE5EE7HandlerEm
               (undefined8 param_1,long param_2)

{
  undefined2 *puVar1;
  
  puVar1 = *(undefined2 **)(param_2 + 0x38);
                    /* WARNING: Could not recover jumptable at 0x026a3898. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(**(long **)(param_2 + 0x30) + 0x68))
            (*(long **)(param_2 + 0x30),*(undefined8 *)(puVar1 + 0x34),puVar1 + 8,*puVar1);
  return;
}

// ==== Aska::IDE_NotifyCollisionDetection<(Aska::_Enum_IDECollisionDetectionInputType)5, (Aska::_Enum_IDECollisionDetectionOutputType)5>::~IDE_NotifyCollisionDetection()
// vaddr 0x25a389c | ghidra 0x26a389c | size 4 | symbol _ZN4Aska28IDE_NotifyCollisionDetectionILNS_36_Enum_IDECollisionDetectionInputTypeE5ELNS_37_Enum_IDECollisionDetectionOutputTypeE5EED0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska28IDE_NotifyCollisionDetectionILNS_36_Enum_IDECollisionDetectionInputTypeE5ELNS_37_Enum_IDECollisionDetectionOutputTypeE5EED0Ev
               (void)

{
  (*(code *)PTR__ZdlPv_02ca4758)();
  return;
}


// FAILED to create function at 029c8120 typeinfo name for Aska::IDEPrimitiveOBB<(Aska::_EnumIDESpacePartitionType)0>
// FAILED to create function at 029c8160 typeinfo name for Aska::IDEPrimitive<(Aska::_EnumIDESpacePartitionType)0, (Aska::_EnumIDEPrimitiveType)5>
// FAILED to create function at 029e3760 typeinfo name for Aska::IDEPrimitiveAABB<(Aska::_EnumIDESpacePartitionType)0>
// FAILED to create function at 029e37a0 typeinfo name for Aska::IDEPrimitive<(Aska::_EnumIDESpacePartitionType)0, (Aska::_EnumIDEPrimitiveType)1>
// FAILED to create function at 029e3800 typeinfo name for Aska::IDEPrimitiveSphere<(Aska::_EnumIDESpacePartitionType)0>
// FAILED to create function at 029e3850 typeinfo name for Aska::IDEPrimitive<(Aska::_EnumIDESpacePartitionType)0, (Aska::_EnumIDEPrimitiveType)2>
// FAILED to create function at 029e38b0 typeinfo name for Aska::IDEPrimitiveHeightObject<(Aska::_EnumIDESpacePartitionType)0>
// FAILED to create function at 029e3900 typeinfo name for Aska::IDEPrimitive<(Aska::_EnumIDESpacePartitionType)0, (Aska::_EnumIDEPrimitiveType)3>
// FAILED to create function at 029e3960 typeinfo name for Aska::IDEPrimitiveCollisionHandler<(Aska::_EnumIDESpacePartitionType)0>
// FAILED to create function at 029e39b0 typeinfo name for Aska::IDEPrimitive<(Aska::_EnumIDESpacePartitionType)0, (Aska::_EnumIDEPrimitiveType)4>
// FAILED to create function at 029e3a10 typeinfo name for Aska::IDEPrimitive<(Aska::_EnumIDESpacePartitionType)0, (Aska::_EnumIDEPrimitiveType)0>
// FAILED to create function at 02a315c0 typeinfo name for Aska::IDE_NotifyCollisionDetection<(Aska::_Enum_IDECollisionDetectionInputType)0, (Aska::_Enum_IDECollisionDetectionOutputType)0>
// FAILED to create function at 02a31650 typeinfo name for Aska::IDE_NotifyCollisionDetection<(Aska::_Enum_IDECollisionDetectionInputType)1, (Aska::_Enum_IDECollisionDetectionOutputType)0>
// FAILED to create function at 02a316e0 typeinfo name for Aska::IDE_NotifyCollisionDetection<(Aska::_Enum_IDECollisionDetectionInputType)0, (Aska::_Enum_IDECollisionDetectionOutputType)1>
// FAILED to create function at 02a31770 typeinfo name for Aska::IDE_NotifyCollisionDetection<(Aska::_Enum_IDECollisionDetectionInputType)1, (Aska::_Enum_IDECollisionDetectionOutputType)1>
// FAILED to create function at 02a31800 typeinfo name for Aska::IDE_NotifyCollisionDetection<(Aska::_Enum_IDECollisionDetectionInputType)0, (Aska::_Enum_IDECollisionDetectionOutputType)2>
// FAILED to create function at 02a31890 typeinfo name for Aska::IDE_NotifyCollisionDetection<(Aska::_Enum_IDECollisionDetectionInputType)1, (Aska::_Enum_IDECollisionDetectionOutputType)2>
// FAILED to create function at 02a31920 typeinfo name for Aska::IDE_NotifyCollisionDetection<(Aska::_Enum_IDECollisionDetectionInputType)2, (Aska::_Enum_IDECollisionDetectionOutputType)3>
// FAILED to create function at 02a319b0 typeinfo name for Aska::IDE_NotifyCollisionDetection<(Aska::_Enum_IDECollisionDetectionInputType)3, (Aska::_Enum_IDECollisionDetectionOutputType)4>
// FAILED to create function at 02a31a40 typeinfo name for Aska::IDE_NotifyCollisionDetection<(Aska::_Enum_IDECollisionDetectionInputType)4, (Aska::_Enum_IDECollisionDetectionOutputType)4>
// FAILED to create function at 02a31ad0 typeinfo name for Aska::IDE_NotifyCollisionDetection<(Aska::_Enum_IDECollisionDetectionInputType)5, (Aska::_Enum_IDECollisionDetectionOutputType)5>
// FAILED to create function at 02c4a9f0 Aska::IDEPrimitiveOBB<(Aska::_EnumIDESpacePartitionType)0>::vtable
// FAILED to create function at 02c4aa80 Aska::IDEPrimitive<(Aska::_EnumIDESpacePartitionType)0,(Aska::_EnumIDEPrimitiveType)5>::typeinfo
// FAILED to create function at 02c4aaa0 Aska::IDEPrimitiveOBB<(Aska::_EnumIDESpacePartitionType)0>::typeinfo
// FAILED to create function at 02c63878 Aska::IDEPrimitiveAABB<(Aska::_EnumIDESpacePartitionType)0>::vtable
// FAILED to create function at 02c63900 Aska::IDEPrimitive<(Aska::_EnumIDESpacePartitionType)0,(Aska::_EnumIDEPrimitiveType)1>::typeinfo
// FAILED to create function at 02c63920 Aska::IDEPrimitiveAABB<(Aska::_EnumIDESpacePartitionType)0>::typeinfo
// FAILED to create function at 02c63938 Aska::IDEPrimitiveSphere<(Aska::_EnumIDESpacePartitionType)0>::vtable
// FAILED to create function at 02c639c0 Aska::IDEPrimitive<(Aska::_EnumIDESpacePartitionType)0,(Aska::_EnumIDEPrimitiveType)2>::typeinfo
// FAILED to create function at 02c639e0 Aska::IDEPrimitiveSphere<(Aska::_EnumIDESpacePartitionType)0>::typeinfo
// FAILED to create function at 02c639f8 Aska::IDEPrimitiveHeightObject<(Aska::_EnumIDESpacePartitionType)0>::vtable
// FAILED to create function at 02c63a90 Aska::IDEPrimitive<(Aska::_EnumIDESpacePartitionType)0,(Aska::_EnumIDEPrimitiveType)3>::typeinfo
// FAILED to create function at 02c63ab0 Aska::IDEPrimitiveHeightObject<(Aska::_EnumIDESpacePartitionType)0>::typeinfo
// FAILED to create function at 02c63ac8 Aska::IDEPrimitiveCollisionHandler<(Aska::_EnumIDESpacePartitionType)0>::vtable
// FAILED to create function at 02c63b60 Aska::IDEPrimitive<(Aska::_EnumIDESpacePartitionType)0,(Aska::_EnumIDEPrimitiveType)4>::typeinfo
// FAILED to create function at 02c63b80 Aska::IDEPrimitiveCollisionHandler<(Aska::_EnumIDESpacePartitionType)0>::typeinfo
// FAILED to create function at 02c63b98 Aska::IDEPrimitive<(Aska::_EnumIDESpacePartitionType)0,(Aska::_EnumIDEPrimitiveType)0>::vtable
// FAILED to create function at 02c63c20 Aska::IDEPrimitive<(Aska::_EnumIDESpacePartitionType)0,(Aska::_EnumIDEPrimitiveType)0>::typeinfo
// FAILED to create function at 02c86678 Aska::IDE_NotifyCollisionDetection<(Aska::_Enum_IDECollisionDetectionInputType)0,(Aska::_Enum_IDECollisionDetectionOutputType)0>::vtable
// FAILED to create function at 02c86688 Aska::IDE_NotifyCollisionDetection<(Aska::_Enum_IDECollisionDetectionInputType)0,(Aska::_Enum_IDECollisionDetectionOutputType)0>[16]::vtable
// FAILED to create function at 02c866a0 Aska::IDE_NotifyCollisionDetection<(Aska::_Enum_IDECollisionDetectionInputType)1,(Aska::_Enum_IDECollisionDetectionOutputType)0>::vtable
// FAILED to create function at 02c866b0 Aska::IDE_NotifyCollisionDetection<(Aska::_Enum_IDECollisionDetectionInputType)1,(Aska::_Enum_IDECollisionDetectionOutputType)0>[16]::vtable
// FAILED to create function at 02c866c8 Aska::IDE_NotifyCollisionDetection<(Aska::_Enum_IDECollisionDetectionInputType)0,(Aska::_Enum_IDECollisionDetectionOutputType)1>::vtable
// FAILED to create function at 02c866d8 Aska::IDE_NotifyCollisionDetection<(Aska::_Enum_IDECollisionDetectionInputType)0,(Aska::_Enum_IDECollisionDetectionOutputType)1>[16]::vtable
// FAILED to create function at 02c866f0 Aska::IDE_NotifyCollisionDetection<(Aska::_Enum_IDECollisionDetectionInputType)1,(Aska::_Enum_IDECollisionDetectionOutputType)1>::vtable
// FAILED to create function at 02c86700 Aska::IDE_NotifyCollisionDetection<(Aska::_Enum_IDECollisionDetectionInputType)1,(Aska::_Enum_IDECollisionDetectionOutputType)1>[16]::vtable
// FAILED to create function at 02c86718 Aska::IDE_NotifyCollisionDetection<(Aska::_Enum_IDECollisionDetectionInputType)0,(Aska::_Enum_IDECollisionDetectionOutputType)2>::vtable
// FAILED to create function at 02c86728 Aska::IDE_NotifyCollisionDetection<(Aska::_Enum_IDECollisionDetectionInputType)0,(Aska::_Enum_IDECollisionDetectionOutputType)2>[16]::vtable
// FAILED to create function at 02c86740 Aska::IDE_NotifyCollisionDetection<(Aska::_Enum_IDECollisionDetectionInputType)1,(Aska::_Enum_IDECollisionDetectionOutputType)2>::vtable
// FAILED to create function at 02c86750 Aska::IDE_NotifyCollisionDetection<(Aska::_Enum_IDECollisionDetectionInputType)1,(Aska::_Enum_IDECollisionDetectionOutputType)2>[16]::vtable
// FAILED to create function at 02c86768 Aska::IDE_NotifyCollisionDetection<(Aska::_Enum_IDECollisionDetectionInputType)2,(Aska::_Enum_IDECollisionDetectionOutputType)3>::vtable
// FAILED to create function at 02c86778 Aska::IDE_NotifyCollisionDetection<(Aska::_Enum_IDECollisionDetectionInputType)2,(Aska::_Enum_IDECollisionDetectionOutputType)3>[16]::vtable
// FAILED to create function at 02c86790 Aska::IDE_NotifyCollisionDetection<(Aska::_Enum_IDECollisionDetectionInputType)3,(Aska::_Enum_IDECollisionDetectionOutputType)4>::vtable
// FAILED to create function at 02c867a0 Aska::IDE_NotifyCollisionDetection<(Aska::_Enum_IDECollisionDetectionInputType)3,(Aska::_Enum_IDECollisionDetectionOutputType)4>[16]::vtable
// FAILED to create function at 02c867b8 Aska::IDE_NotifyCollisionDetection<(Aska::_Enum_IDECollisionDetectionInputType)4,(Aska::_Enum_IDECollisionDetectionOutputType)4>::vtable
// FAILED to create function at 02c867c8 Aska::IDE_NotifyCollisionDetection<(Aska::_Enum_IDECollisionDetectionInputType)4,(Aska::_Enum_IDECollisionDetectionOutputType)4>[16]::vtable
// FAILED to create function at 02c867e0 Aska::IDE_NotifyCollisionDetection<(Aska::_Enum_IDECollisionDetectionInputType)5,(Aska::_Enum_IDECollisionDetectionOutputType)5>::vtable
// FAILED to create function at 02c867f0 Aska::IDE_NotifyCollisionDetection<(Aska::_Enum_IDECollisionDetectionInputType)5,(Aska::_Enum_IDECollisionDetectionOutputType)5>[16]::vtable
// FAILED to create function at 02c86850 Aska::IDE_NotifyCollisionDetection<(Aska::_Enum_IDECollisionDetectionInputType)0,(Aska::_Enum_IDECollisionDetectionOutputType)0>::typeinfo
// FAILED to create function at 02c86870 Aska::IDE_NotifyCollisionDetection<(Aska::_Enum_IDECollisionDetectionInputType)1,(Aska::_Enum_IDECollisionDetectionOutputType)0>::typeinfo
// FAILED to create function at 02c86890 Aska::IDE_NotifyCollisionDetection<(Aska::_Enum_IDECollisionDetectionInputType)0,(Aska::_Enum_IDECollisionDetectionOutputType)1>::typeinfo
// FAILED to create function at 02c868b0 Aska::IDE_NotifyCollisionDetection<(Aska::_Enum_IDECollisionDetectionInputType)1,(Aska::_Enum_IDECollisionDetectionOutputType)1>::typeinfo
// FAILED to create function at 02c868d0 Aska::IDE_NotifyCollisionDetection<(Aska::_Enum_IDECollisionDetectionInputType)0,(Aska::_Enum_IDECollisionDetectionOutputType)2>::typeinfo
// FAILED to create function at 02c868f0 Aska::IDE_NotifyCollisionDetection<(Aska::_Enum_IDECollisionDetectionInputType)1,(Aska::_Enum_IDECollisionDetectionOutputType)2>::typeinfo
// FAILED to create function at 02c86910 Aska::IDE_NotifyCollisionDetection<(Aska::_Enum_IDECollisionDetectionInputType)2,(Aska::_Enum_IDECollisionDetectionOutputType)3>::typeinfo
// FAILED to create function at 02c86930 Aska::IDE_NotifyCollisionDetection<(Aska::_Enum_IDECollisionDetectionInputType)3,(Aska::_Enum_IDECollisionDetectionOutputType)4>::typeinfo
// FAILED to create function at 02c86950 Aska::IDE_NotifyCollisionDetection<(Aska::_Enum_IDECollisionDetectionInputType)4,(Aska::_Enum_IDECollisionDetectionOutputType)4>::typeinfo
// FAILED to create function at 02c86970 Aska::IDE_NotifyCollisionDetection<(Aska::_Enum_IDECollisionDetectionInputType)5,(Aska::_Enum_IDECollisionDetectionOutputType)5>::typeinfo
// FAILED to create function at 02e7ee10 Aska::IDE_NotifyCollisionDetection<(Aska::_Enum_IDECollisionDetectionInputType)2,(Aska::_Enum_IDECollisionDetectionOutputType)3>::Handler(unsigned_long)::dir
// FAILED to create function at 02e7ee20 Aska::IDE_NotifyCollisionDetection<(Aska::_Enum_IDECollisionDetectionInputType)2,(Aska::_Enum_IDECollisionDetectionOutputType)3>::Handler(unsigned_long)::dir
