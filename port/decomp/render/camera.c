// port/decomp/render/camera.c: Ghidra decompiles for the render subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-04 07:01 UTC: tools/decomp.sh '--into' 'render/camera' 'Aska::AimingObject::' 'Aska::Camera::' 'Aska::CameraManager::'

// ==== Aska::Camera::GetClassID(int) const
// vaddr 0x1e68b84 | ghidra 0x1f68b84 | size 68 | symbol _ZNK4Aska6Camera10GetClassIDEi | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska6Camera10GetClassIDEi(undefined8 param_1,uint param_2)

{
  undefined8 uVar1;
  undefined8 uVar2;
  
  if (param_2 < 4) {
    return *(undefined8 *)(&UNK_02961d00 + (long)(int)param_2 * 8);
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

// ==== Aska::Camera::CheckSleepAvailability()
// vaddr 0x1e68bd8 | ghidra 0x1f68bd8 | size 8 | symbol _ZN4Aska6Camera22CheckSleepAvailabilityEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska6Camera22CheckSleepAvailabilityEv(void)

{
  return 0;
}

// ==== Aska::AimingObject::TargetObject() const
// vaddr 0x1e68f7c | ghidra 0x1f68f7c | size 8 | symbol _ZNK4Aska12AimingObject12TargetObjectEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska12AimingObject12TargetObjectEv(long param_1)

{
  return *(undefined8 *)(param_1 + 0x1b0);
}

// ==== Aska::AimingObject::UpTargetObject() const
// vaddr 0x1e68f84 | ghidra 0x1f68f84 | size 8 | symbol _ZNK4Aska12AimingObject14UpTargetObjectEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska12AimingObject14UpTargetObjectEv(long param_1)

{
  return *(undefined8 *)(param_1 + 0x1b8);
}

// ==== Aska::AimingObject::Clone(Aska::IAnimatable const*)
// vaddr 0x20e56ac | ghidra 0x21e56ac | size 332 | symbol _ZN4Aska12AimingObject5CloneEPKNS_11IAnimatableE | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska12AimingObject5CloneEPKNS_11IAnimatableE(long *param_1,long *param_2)

{
  long *plVar1;
  ulong uVar2;
  undefined8 uVar3;
  long lVar4;
  code *pcVar5;
  
  uVar2 = Aska::HierarchicalObject::Clone(Aska::IAnimatable const*)();
  if ((uVar2 & 1) == 0) {
    uVar3 = 0;
  }
  else {
    pcVar5 = *(code **)(*param_1 + 0xa0);
    uVar3 = (**(code **)(*param_2 + 0x98))(param_2);
    (*pcVar5)(param_1,uVar3);
    *(int *)(param_1 + 0x34) = (int)param_2[0x34];
    *(undefined4 *)((long)param_1 + 0x1a4) = *(undefined4 *)((long)param_2 + 0x1a4);
    *(int *)(param_1 + 0x35) = (int)param_2[0x35];
    *(undefined4 *)((long)param_1 + 0x1ac) = *(undefined4 *)((long)param_2 + 0x1ac);
    param_1[0x36] = param_2[0x36];
    param_1[0x37] = param_2[0x37];
    *(int *)(param_1 + 0x3e) = (int)param_2[0x3e];
    if (param_1[0x39] != 0) {
      *(long *)(param_1[0x39] + 0x10) = param_1[0x3a];
    }
    if ((long *)param_1[0x3a] != (long *)0x0) {
      *(long *)param_1[0x3a] = param_1[0x39];
      param_1[0x3a] = 0;
    }
    lVar4 = param_1[0x36];
    param_1[0x39] = 0;
    if (lVar4 != 0) {
      param_1[0x39] = 0;
      plVar1 = (long *)(lVar4 + 0x110);
      if (*(long *)(lVar4 + 0x110) == 0) {
        lVar4 = 0;
      }
      else {
        *(long **)(*(long *)(lVar4 + 0x110) + 0x10) = param_1 + 0x39;
        lVar4 = *plVar1;
      }
      param_1[0x39] = lVar4;
      param_1[0x3a] = (long)plVar1;
      *plVar1 = (long)(param_1 + 0x38);
    }
    if (param_1[0x3c] != 0) {
      *(long *)(param_1[0x3c] + 0x10) = param_1[0x3d];
    }
    if ((long *)param_1[0x3d] != (long *)0x0) {
      *(long *)param_1[0x3d] = param_1[0x3c];
      param_1[0x3d] = 0;
    }
    lVar4 = param_1[0x37];
    param_1[0x3c] = 0;
    if (lVar4 != 0) {
      param_1[0x3c] = 0;
      plVar1 = (long *)(lVar4 + 0x110);
      if (*(long *)(lVar4 + 0x110) == 0) {
        lVar4 = 0;
      }
      else {
        *(long **)(*(long *)(lVar4 + 0x110) + 0x10) = param_1 + 0x3c;
        lVar4 = *plVar1;
      }
      param_1[0x3c] = lVar4;
      param_1[0x3d] = (long)plVar1;
      *plVar1 = (long)(param_1 + 0x3b);
    }
    uVar3 = 1;
  }
  return uVar3;
}

// ==== Aska::AimingObject::CreateClone(Aska::IAnimatable const*)
// vaddr 0x20e57f8 | ghidra 0x21e57f8 | size 104 | symbol _ZN4Aska12AimingObject11CreateCloneEPKNS_11IAnimatableE | lib libSOA-3.7.0.so | 2026-10-04
long * _ZN4Aska12AimingObject11CreateCloneEPKNS_11IAnimatableE
                 (undefined8 param_1,undefined8 param_2)

{
  long *plVar1;
  ulong uVar2;
  
  plVar1 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x200,PTR__ZSt7nothrow_02cb9a80);
  if (plVar1 != (long *)0x0) {
    Aska::AimingObject::AimingObject()(plVar1);
    uVar2 = (**(code **)(*plVar1 + 0x18))(plVar1,param_2);
    if ((uVar2 & 1) == 0) {
      (**(code **)(*plVar1 + 8))(plVar1);
      plVar1 = (long *)0x0;
    }
  }
  return plVar1;
}

// ==== Aska::AimingObject::AimingObject()
// vaddr 0x20e5934 | ghidra 0x21e5934 | size 352 | symbol _ZN4Aska12AimingObjectC2Ev | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska12AimingObjectC2Ev(long *param_1)

{
  byte bVar1;
  byte bVar2;
  long lVar3;
  long lVar4;
  undefined *puVar5;
  undefined4 uVar6;
  code *pcVar7;
  long *plVar8;
  long *plVar9;
  long *plVar10;
  
  pcVar7 = *(code **)(PTR__ZTVN4Aska4TaskE_02cbe020 + 0x68);
  *param_1 = (long)(PTR__ZTVN4Aska4TaskE_02cbe020 + 0x10);
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  *(undefined2 *)((long)param_1 + 0x24) = 0;
  *(undefined1 *)((long)param_1 + 0x26) = 0;
  uVar6 = (*pcVar7)();
  *(undefined4 *)(param_1 + 4) = uVar6;
  puVar5 = PTR__ZTVN4Aska27HierarchicalObjectContainerE_02cb81a8;
  *param_1 = (long)(PTR__ZTVN4Aska18HierarchicalObjectE_02cb6bb0 + 0x10);
  plVar10 = param_1 + 6;
  *plVar10 = (long)(puVar5 + 0x10);
  *(undefined4 *)(param_1 + 0x14) = 0x3f800000;
  *(undefined4 *)((long)param_1 + 0xac) = 0x3f800000;
  lVar4 = _UNK_027dbb38;
  lVar3 = _UNK_027dbb30;
  bVar1 = *(byte *)(param_1 + 0x25);
  bVar2 = *(byte *)((long)param_1 + 0x129);
  *(byte *)((long)param_1 + 0x129) = bVar2 & 0xfc;
  *(undefined8 *)((long)param_1 + 0xa4) = 0x3f8000003f800000;
  param_1[0x11] = lVar4;
  param_1[0x10] = lVar3;
  param_1[0x13] = lVar4;
  param_1[0x12] = lVar3;
  *(byte *)(param_1 + 0x25) = bVar1 & 0xde | 1;
  plVar8 = param_1 + 0x18;
  do {
    plVar9 = (long *)((long)plVar8 + 0x7fU & 0xffffffffffffff81);
    Hint_Prefetch(plVar8,0,2,0);
    plVar8 = plVar9;
  } while (plVar9 < param_1 + 0x1a);
  param_1[0x1b] = lVar4;
  param_1[0x1a] = lVar3;
  param_1[0x1d] = lVar4;
  param_1[0x1c] = lVar3;
  param_1[0x17] = lVar4;
  param_1[0x16] = lVar3;
  *(undefined4 *)(param_1 + 0x18) = 0;
  *(undefined8 *)((long)param_1 + 0xc4) = 0;
  param_1[0x1e] = 0;
  param_1[0x1f] = 0;
  param_1[0x22] = 0;
  param_1[0x23] = 0;
  param_1[0x20] = (long)plVar10;
  param_1[0x21] = (long)plVar10;
  param_1[5] = 0;
  *(byte *)((long)param_1 + 0x129) = bVar2 & 0xf8;
  param_1[0x23] = (long)param_1;
  param_1[0x24] = (long)(param_1 + 8);
  param_1[0x30] = 0;
  param_1[0x31] = 0;
  *(undefined4 *)(param_1 + 0x32) = 0;
  puVar5 = PTR__ZTVN4Aska12AimingObjectE_02cc4418;
  *(byte *)(param_1 + 0x25) = bVar1 & 200 | 1;
  *(undefined4 *)(param_1 + 0x34) = 0;
  *(undefined4 *)((long)param_1 + 0xcc) = 0x3f800000;
  *(undefined2 *)((long)param_1 + 0x194) = 1;
  *param_1 = (long)(puVar5 + 0x10);
  memset(param_1 + 0x36,0,0x44);
  *(undefined8 *)((long)param_1 + 0x1a4) = 0x3f800000;
  *(undefined4 *)((long)param_1 + 0x1ac) = 0x3f800000;
  param_1[0x38] = (long)plVar10;
  param_1[0x3b] = (long)plVar10;
  *(undefined1 *)((long)param_1 + 500) = 0;
  *(undefined1 *)((long)param_1 + 0x197) = 1;
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

// ==== Aska::Camera::SetNumberOfAFPoints(long)
// vaddr 0x20e968c | ghidra 0x21e968c | size 84 | symbol _ZN4Aska6Camera19SetNumberOfAFPointsEl | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6Camera19SetNumberOfAFPointsEl(long param_1,long param_2)

{
  long lVar1;
  
  lVar1 = *(long *)(param_1 + 0xe88);
  Aska::TArray<Aska::Camera::AFPoint, true>::Resize(long, bool)(param_1 + 0xe70,param_2,0);
  if (lVar1 < param_2) {
    (*(code *)PTR_memset_02c9b870)(*(long *)(param_1 + 0xe78) + lVar1 * 8,0,(param_2 - lVar1) * 8);
    return;
  }
  return;
}

// ==== Aska::Camera::SetAFPoint(long, float, float)
// vaddr 0x20e96e0 | ghidra 0x21e96e0 | size 44 | symbol _ZN4Aska6Camera10SetAFPointElff | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska6Camera10SetAFPointElff(undefined4 param_1,undefined4 param_2,long param_3,long param_4)

{
  undefined4 *puVar1;
  undefined8 uVar2;
  
  uVar2 = 0;
  if ((-1 < param_4) && (param_4 < *(long *)(param_3 + 0xe88))) {
    uVar2 = 1;
    puVar1 = (undefined4 *)(*(long *)(param_3 + 0xe78) + param_4 * 8);
    *puVar1 = param_1;
    puVar1[1] = param_2;
  }
  return uVar2;
}

// ==== Aska::Camera::GetFogConst()
// vaddr 0x20e970c | ghidra 0x21e970c | size 388 | symbol _ZN4Aska6Camera11GetFogConstEv | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

long _ZN4Aska6Camera11GetFogConstEv(long param_1)

{
  ushort *puVar1;
  ushort uVar2;
  undefined *puVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  undefined8 uVar8;
  
  puVar3 = PTR__ZN4Aska6Camera19m_avDisableFogConstE_02cb91a8;
  fVar4 = _UNK_029c8d10;
  puVar1 = (ushort *)(param_1 + 0xeb3);
  uVar2 = *puVar1;
  if ((uVar2 >> 2 & 1) == 0) goto code_r0x021e987c;
  if (*(char *)(param_1 + 0xeb2) == '\x02') {
    fVar7 = *(float *)(param_1 + 0xeec);
    *(undefined4 *)(param_1 + 0xf2c) = 0xc0000000;
    *(float *)(param_1 + 0xf20) = fVar4 / (fVar7 / *(float *)(param_1 + 0xf10));
    *(float *)(param_1 + 0xf24) = fVar4 / (fVar7 / *(float *)(param_1 + 0xf14));
    *(float *)(param_1 + 0xf28) = fVar4 / (fVar7 / *(float *)(param_1 + 0xf18));
    *(undefined8 *)(param_1 + 0xf40) = 0x3e6365df3f5c4823;
code_r0x021e9834:
    *(float *)(param_1 + 0xf48) = fVar7;
    *(undefined8 *)(param_1 + 0xf38) = *(undefined8 *)(param_1 + 0xf08);
    *(undefined8 *)(param_1 + 0xf30) = *(undefined8 *)(param_1 + 0xf00);
    fVar4 = _UNK_02964e6c;
    if (fVar7 < *(float *)(param_1 + 0xee8)) {
      fVar4 = 1.0 / (*(float *)(param_1 + 0xee8) - *(float *)(param_1 + 0xeec));
    }
    *(float *)(param_1 + 0xf4c) = fVar4;
    uVar2 = *puVar1;
  }
  else {
    if (*(char *)(param_1 + 0xeb2) != '\0') {
      fVar4 = (float)expf(*(float *)(param_1 + 0xeec) *
                                     (_UNK_029c8d14 / *(float *)(param_1 + 0xee8)));
      fVar5 = (float)logf(_UNK_029c8d18 / (1.0 / fVar4));
      fVar5 = fVar5 / -*(float *)(param_1 + 0xee8);
      fVar6 = (float)expf(-(*(float *)(param_1 + 0xeec) * fVar5));
      fVar4 = _UNK_02807c00;
      fVar7 = *(float *)(param_1 + 0xeec);
      *(float *)(param_1 + 0xf20) = 1.0 / fVar6;
      *(undefined4 *)(param_1 + 0xf28) = *(undefined4 *)(param_1 + 0xef0);
      *(float *)(param_1 + 0xf24) = fVar5 * fVar4;
      *(undefined4 *)(param_1 + 0xf2c) = 0;
      goto code_r0x021e9834;
    }
    uVar8 = *(undefined8 *)(PTR__ZN4Aska6Camera19m_avDisableFogConstE_02cb91a8 + 0x20);
    *(undefined8 *)(param_1 + 0xf48) =
         *(undefined8 *)(PTR__ZN4Aska6Camera19m_avDisableFogConstE_02cb91a8 + 0x28);
    *(undefined8 *)(param_1 + 0xf40) = uVar8;
    uVar8 = *(undefined8 *)(puVar3 + 0x10);
    *(undefined8 *)(param_1 + 0xf38) = *(undefined8 *)(puVar3 + 0x18);
    *(undefined8 *)(param_1 + 0xf30) = uVar8;
    uVar8 = *(undefined8 *)puVar3;
    *(undefined8 *)(param_1 + 0xf28) = *(undefined8 *)(puVar3 + 8);
    *(undefined8 *)(param_1 + 0xf20) = uVar8;
  }
  *puVar1 = uVar2 & 0xfffb;
code_r0x021e987c:
  return param_1 + 0xf20;
}

// ==== Aska::Camera::SetRawScatteringFogConst(float, float, float, Aska::Vector*)
// vaddr 0x20e9890 | ghidra 0x21e9890 | size 108 | symbol _ZN4Aska6Camera24SetRawScatteringFogConstEfffPNS_6VectorE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6Camera24SetRawScatteringFogConstEfffPNS_6VectorE
               (undefined4 param_1,undefined4 param_2,undefined4 param_3,long param_4,
               undefined4 *param_5)

{
  if (*(char *)(param_4 + 0xeb2) == '\x02') {
    *(undefined4 *)(param_4 + 0xf2c) = 0xc0000000;
    *(undefined4 *)(param_4 + 0xf20) = param_1;
    *(undefined4 *)(param_4 + 0xf24) = param_2;
    *(undefined4 *)(param_4 + 0xf28) = param_3;
    *(undefined8 *)(param_4 + 0xf40) = 0x3e6365df3f5c4823;
    *(undefined4 *)(param_4 + 0xf30) = *param_5;
    *(undefined4 *)(param_4 + 0xf34) = param_5[1];
    *(undefined4 *)(param_4 + 0xf38) = param_5[2];
    *(undefined4 *)(param_4 + 0xf3c) = param_5[3];
    *(ushort *)(param_4 + 0xeb3) = *(ushort *)(param_4 + 0xeb3) & 0xfffb;
  }
  return;
}

// ==== Aska::Camera::ConvertFromOLS()
// vaddr 0x20e98fc | ghidra 0x21e98fc | size 944 | symbol _ZN4Aska6Camera14ConvertFromOLSEv | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska6Camera14ConvertFromOLSEv(long param_1)

{
  undefined8 uVar1;
  long lVar2;
  long lVar3;
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
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  float fVar19;
  float fVar20;
  float fVar21;
  float fVar22;
  float fVar23;
  float fVar24;
  
  lVar3 = *(long *)(param_1 + 0xe18);
  fVar20 = *(float *)(lVar3 + 0x2d0) * _UNK_029c8d1c;
  fVar18 = *(float *)(lVar3 + 0x2d4) * _UNK_029c8d1c;
  fVar17 = *(float *)(lVar3 + 0x2d8) * _UNK_029c8d1c;
  fVar5 = (*(float *)(lVar3 + 0x328) * _UNK_029c8d20 + _UNK_029c8d24) * _UNK_027fac84 *
          _UNK_029c8d28;
  fVar8 = *(float *)(lVar3 + 0x2e0) * fVar5;
  fVar21 = *(float *)(lVar3 + 0x2e4) * fVar5;
  fVar12 = *(float *)(lVar3 + 800) * _UNK_027f5450;
  fVar15 = fVar20 + fVar8;
  fVar22 = fVar18 + fVar21;
  fVar5 = *(float *)(lVar3 + 0x2e8) * fVar5;
  fVar4 = fVar12 * fVar15;
  fVar6 = fVar12 * fVar22;
  fVar16 = fVar17 + fVar5;
  fVar12 = fVar12 * fVar16;
  fVar9 = fVar4;
  if (fVar6 <= fVar4) {
    fVar9 = fVar6;
  }
  if (fVar12 <= fVar9) {
    fVar9 = fVar12;
  }
  fVar9 = _UNK_029c8d10 / fVar9;
  fVar4 = -(fVar4 * fVar9) / _UNK_029c744c;
  fVar6 = -(fVar6 * fVar9) / _UNK_029c744c;
  fVar12 = -(fVar12 * fVar9) / _UNK_029c744c;
  *(float *)(param_1 + 0xee8) = fVar9;
  *(float *)(param_1 + 0xeec) = fVar9;
  *(float *)(param_1 + 0xf10) = fVar4;
  *(float *)(param_1 + 0xf14) = fVar6;
  *(float *)(param_1 + 0xf18) = fVar12;
  lVar2 = Aska::LightManager::GetActualSunLight() const(*(undefined8 *)PTR__ZN4Aska6Global15m_pLightManagerE_02cc1770);
  uVar1 = _UNK_027dbb30;
  if (lVar2 == 0) {
    *(undefined8 *)(param_1 + 0xf08) = _UNK_027dbb38;
    *(undefined8 *)(param_1 + 0xf00) = uVar1;
  }
  else {
    Aska::Camera::MakeCameraMatrix()(param_1);
    fVar9 = *(float *)(lVar2 + 0x290);
    fVar4 = *(float *)(lVar2 + 0x294);
    fVar6 = *(float *)(lVar2 + 0x298);
    fVar7 = fVar9 * fVar9 + fVar4 * fVar4 + fVar6 * fVar6;
    fVar12 = SQRT(fVar7);
    if (NAN(fVar12)) {
      fVar12 = (float)sqrtf(fVar7);
    }
    if (_UNK_027e519c <= fVar12) {
      fVar12 = 1.0 / fVar12;
      fVar9 = fVar12 * fVar9;
      fVar4 = fVar12 * fVar4;
      fVar6 = fVar12 * fVar6;
    }
    fVar24 = *(float *)(lVar3 + 0x2fc);
    fVar7 = *(float *)(lVar3 + 0x2f0) * fVar24;
    fVar14 = *(float *)(lVar3 + 0x2f4) * fVar24;
    fVar24 = *(float *)(lVar3 + 0x2f8) * fVar24;
    fVar12 = fVar7 * fVar7;
    fVar11 = fVar14 * fVar14;
    fVar13 = fVar24 * fVar24;
    fVar6 = (-(*(float *)(param_1 + 0x154) * fVar4) - *(float *)(param_1 + 0x150) * fVar9) -
            *(float *)(param_1 + 0x158) * fVar6;
    fVar23 = fVar6 * fVar6 + 1.0;
    fVar19 = fVar23 * _UNK_029c8d2c;
    fVar9 = (float)powf(fVar12 + 1.0 + fVar6 * fVar7 * -2.0,0x40200000);
    fVar4 = (float)powf(fVar11 + 1.0 + fVar6 * fVar14 * -2.0,0x40200000);
    fVar6 = (float)powf(fVar13 + 1.0 + fVar6 * fVar24 * -2.0,0x40200000);
    fVar7 = *(float *)(lVar2 + 0x23c) * *(float *)(lVar3 + 0x324);
    fVar14 = (float)*(undefined8 *)(lVar2 + 0x230) * fVar7;
    fVar24 = (float)((ulong)*(undefined8 *)(lVar2 + 0x230) >> 0x20) * fVar7;
    fVar10 = (float)*(undefined8 *)(lVar2 + 0x238) * fVar7;
    *(ulong *)(param_1 + 0xf08) =
         CONCAT44((float)((ulong)*(undefined8 *)(lVar2 + 0x238) >> 0x20) * fVar7,fVar10);
    *(ulong *)(param_1 + 0xf00) = CONCAT44(fVar24,fVar14);
    *(float *)(param_1 + 0xf00) =
         (1.0 / fVar15) *
         (fVar20 * fVar19 + fVar8 * ((fVar23 * (((1.0 - fVar12) * 1.5) / (fVar12 + 2.0))) / fVar9))
         * fVar14;
    *(float *)(param_1 + 0xf04) =
         (1.0 / fVar22) *
         (fVar18 * fVar19 + fVar21 * ((fVar23 * (((1.0 - fVar11) * 1.5) / (fVar11 + 2.0))) / fVar4))
         * fVar24;
    *(float *)(param_1 + 0xf08) =
         (1.0 / fVar16) *
         (fVar17 * fVar19 + fVar5 * ((fVar23 * (((1.0 - fVar13) * 1.5) / (fVar13 + 2.0))) / fVar6))
         * fVar10;
  }
  *(ushort *)(param_1 + 0xeb3) = *(ushort *)(param_1 + 0xeb3) | 4;
  return;
}

// ==== Aska::Camera::MakeCameraMatrix()
// vaddr 0x20e9cac | ghidra 0x21e9cac | size 2580 | symbol _ZN4Aska6Camera16MakeCameraMatrixEv | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska6Camera16MakeCameraMatrixEv(long *param_1)

{
  long *plVar1;
  int iVar2;
  ushort uVar3;
  ushort uVar4;
  ushort uVar5;
  bool bVar6;
  long lVar7;
  long lVar8;
  long lVar9;
  long lVar10;
  long lVar11;
  undefined8 uVar12;
  undefined8 *puVar13;
  ushort uVar14;
  uint uVar15;
  ushort *puVar16;
  byte bVar17;
  long *plVar18;
  float *pfVar19;
  ushort *puVar20;
  ulong uVar21;
  float fVar22;
  long lVar23;
  long lVar24;
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
  long alStack_d0 [8];
  
  lVar11 = (**(code **)(*param_1 + 0x160))();
  if ((lVar11 == 0) && ((*(byte *)(param_1 + 0x25) & 1) == 0)) {
    bVar6 = false;
  }
  else {
    (**(code **)(*param_1 + 0xa8))(param_1);
    bVar6 = true;
  }
  puVar16 = (ushort *)((long)param_1 + 0xeb3);
  uVar4 = *puVar16 >> 5 & 1;
  uVar14 = *puVar16 & 0xffdf;
  *puVar16 = uVar14;
  lVar23 = _UNK_027dbb38;
  lVar11 = _UNK_027dbb30;
  if (bVar6 || uVar4 != 0) {
    bVar17 = *(byte *)(param_1 + 0x25);
    if ((bVar17 >> 2 & 1) == 0) {
      if ((*(byte *)((long)param_1 + 0x129) & 3) == 0) {
        fVar22 = *(float *)((long)param_1 + 0x4c);
        fVar25 = *(float *)((long)param_1 + 0x5c);
        fVar27 = *(float *)((long)param_1 + 0x6c);
        param_1[0x27] = CONCAT44((int)param_1[0xe],*(float *)(param_1 + 0xc));
        param_1[0x26] = CONCAT44(*(float *)(param_1 + 10),*(float *)(param_1 + 8));
        param_1[0x29] =
             CONCAT44(*(undefined4 *)((long)param_1 + 0x74),*(float *)((long)param_1 + 100));
        param_1[0x28] = CONCAT44(*(float *)((long)param_1 + 0x54),*(float *)((long)param_1 + 0x44));
        *(float *)((long)param_1 + 0x13c) =
             -(*(float *)(param_1 + 8) * fVar22 + *(float *)(param_1 + 10) * fVar25 +
              *(float *)(param_1 + 0xc) * fVar27);
        *(float *)((long)param_1 + 0x14c) =
             -(fVar22 * *(float *)((long)param_1 + 0x44) + fVar25 * *(float *)((long)param_1 + 0x54)
              + fVar27 * *(float *)((long)param_1 + 100));
        param_1[0x2b] = CONCAT44((int)param_1[0xf],*(float *)(param_1 + 0xd));
        param_1[0x2a] = CONCAT44(*(float *)(param_1 + 0xb),*(float *)(param_1 + 9));
        param_1[0x2d] = lVar23;
        param_1[0x2c] = lVar11;
        *(float *)((long)param_1 + 0x15c) =
             -(fVar22 * *(float *)(param_1 + 9) + fVar25 * *(float *)(param_1 + 0xb) +
              fVar27 * *(float *)(param_1 + 0xd));
      }
      else {
        Aska::Matrix::InvertLowError(Aska::Matrix*) const(param_1 + 8,param_1 + 0x26);
        bVar17 = *(byte *)(param_1 + 0x25);
        uVar14 = *puVar16;
      }
      *(byte *)(param_1 + 0x25) = bVar17 | 4;
    }
    *(undefined4 *)((long)param_1 + 0xc6c) = 0x3f800000;
    *(undefined4 *)(param_1 + 0x18c) = *(undefined4 *)((long)param_1 + 0x4c);
    *(undefined4 *)((long)param_1 + 0xc64) = *(undefined4 *)((long)param_1 + 0x5c);
    *(undefined4 *)(param_1 + 0x18d) = *(undefined4 *)((long)param_1 + 0x6c);
    *puVar16 = uVar14 & 0xffef;
    uVar12 = (**(code **)(*param_1 + 0x98))(param_1);
    Aska::Matrix::CalcEuler(Aska::Vector*, EnumRotateType) const(uVar12,param_1 + 0x12a,4);
  }
  lVar11 = param_1[0x1c2];
  if ((*(byte *)(lVar11 + 0x68) >> 5 & 1) != 0) {
    Aska::Lens::CalcExposureControl()();
    lVar11 = param_1[0x1c2];
  }
  uVar15 = (uint)*puVar16;
  iVar2 = *(int *)(lVar11 + 0x6c);
  if (((*puVar16 >> 1 & 1) == 0) && (iVar2 == *(int *)((long)param_1 + 0xe2c))) {
    if (!bVar6 && uVar4 == 0) {
      return;
    }
  }
  else {
    fVar27 = *(float *)(param_1 + 0x1da);
    fVar30 = *(float *)(lVar11 + 0x40);
    fVar29 = *(float *)(lVar11 + 0x20);
    fVar28 = *(float *)(lVar11 + 0x28);
    fVar31 = *(float *)(lVar11 + 0x2c);
    fVar22 = fVar30 / *(float *)((long)param_1 + 0xed4);
    fVar25 = fVar30 / (*(float *)(param_1 + 0x1db) * fVar27);
    fVar25 = fVar22 * fVar22 + fVar25 * fVar25;
    fVar22 = SQRT(fVar25);
    if (NAN(fVar22)) {
      fVar22 = (float)sqrtf(fVar25);
    }
    fVar22 = fVar22 * 0.5;
    fVar27 = (1.0 / (fVar27 * fVar27) + 1.0) * fVar30 * fVar30 + fVar29 * fVar29;
    fVar25 = SQRT(fVar27);
    *(float *)((long)param_1 + 0xc74) = fVar29;
    *(float *)(param_1 + 0x18e) = (fVar29 * 0.5) / fVar31;
    *(float *)(param_1 + 399) = fVar22;
    if (NAN(fVar25)) {
      fVar25 = (float)sqrtf(fVar27);
    }
    fVar29 = fVar29 / fVar25;
    fVar27 = 1.0 - fVar29 * fVar29;
    fVar25 = SQRT(fVar27);
    if (NAN(fVar25)) {
      fVar25 = (float)sqrtf(fVar27);
    }
    fVar27 = *(float *)((long)param_1 + 0xc74) / fVar29;
    fVar30 = (fVar22 * fVar29) / (fVar27 - fVar22 * fVar25);
    fVar22 = (fVar29 * *(float *)(param_1 + 0x18e)) /
             ((fVar28 * 10.0 - fVar27) - fVar25 * *(float *)(param_1 + 0x18e));
    lVar11 = param_1[0x1c2];
    *(float *)((long)param_1 + 0xc7c) = fVar30 * fVar30 * _UNK_029c8d30 + fVar22 * fVar22 * 0.5;
    fVar25 = *(float *)((long)param_1 + 0xed4);
    fVar22 = (*(float *)(lVar11 + 0x14) * *(float *)(lVar11 + 0x24)) /
             (*(float *)(lVar11 + 0x40) * 0.5);
    fVar27 = *(float *)((long)param_1 + 0xde4) * *(float *)(param_1 + 0x1da);
    fVar28 = fVar22 * fVar25 * 0.5;
    *(float *)((long)param_1 + 0xdfc) = fVar22;
    *(float *)((long)param_1 + 0xdf4) = fVar28;
    *(float *)(param_1 + 0x1bf) = fVar22 * *(float *)(param_1 + 0x1dc) * 0.5;
    *(float *)(param_1 + 0x1bd) = fVar27;
    lVar8 = _UNK_027dbb28;
    lVar7 = _UNK_027dbb20;
    lVar24 = _UNK_027dbb18;
    lVar23 = _UNK_027dbb10;
    lVar11 = _UNK_027dbb00;
    uVar14 = *puVar16;
    if ((uVar14 & 1) == 0) {
      fVar32 = *(float *)(param_1 + 0x1aa);
      fVar29 = *(float *)(param_1 + 0x1d9);
      fVar30 = *(float *)((long)param_1 + 0xecc);
      fVar31 = *(float *)(param_1 + 0x1c0);
      fVar26 = *(float *)((long)param_1 + 0xe04);
      fVar33 = *(float *)((long)param_1 + 0xd54);
      fVar34 = *(float *)(param_1 + 0x1db);
      param_1[0x131] = 0;
      param_1[0x130] = 0;
      param_1[0x133] = 0;
      param_1[0x132] = 0;
      param_1[0x12d] = 0;
      param_1[300] = 0;
      param_1[0x12f] = 0;
      param_1[0x12e] = 0;
      *(float *)((long)param_1 + 0x974) = fVar27 * fVar22;
      fVar36 = (fVar30 * fVar26 - fVar29 * fVar31) / (fVar26 - fVar31);
      fVar35 = ((fVar29 - fVar30) * fVar31 * fVar26) / (fVar26 - fVar31);
      *(float *)(param_1 + 300) = fVar22;
      *(float *)(param_1 + 0x12d) = (fVar32 / fVar25) * -2.0 + 0.0;
      *(float *)(param_1 + 0x12f) = 0.0 - (fVar33 / fVar34 + fVar33 / fVar34);
      *(float *)(param_1 + 0x131) = fVar36;
      *(undefined4 *)(param_1 + 0x133) = 0x3f800000;
    }
    else {
      fVar32 = *(float *)(param_1 + 0x1aa);
      fVar33 = *(float *)((long)param_1 + 0xd54);
      fVar34 = *(float *)(param_1 + 0x1db);
      param_1[0x12d] = _UNK_027dbb08;
      param_1[300] = lVar11;
      lVar9 = _UNK_027dbb38;
      lVar11 = _UNK_027dbb30;
      fVar29 = *(float *)(param_1 + 0x1d9);
      fVar30 = *(float *)((long)param_1 + 0xecc);
      fVar31 = *(float *)(param_1 + 0x1c0);
      fVar26 = *(float *)((long)param_1 + 0xe04);
      param_1[0x131] = lVar8;
      param_1[0x130] = lVar7;
      param_1[0x133] = lVar9;
      param_1[0x132] = lVar11;
      param_1[0x12f] = lVar24;
      param_1[0x12e] = lVar23;
      *(float *)(param_1 + 300) = 2.0 / *(float *)(param_1 + 0x1c1);
      *(float *)((long)param_1 + 0x974) = fVar27 * (2.0 / *(float *)(param_1 + 0x1c1));
      fVar35 = 1.0 - fVar31 / fVar26;
      fVar36 = ((fVar29 - fVar30) * (-1.0 / fVar26)) / fVar35;
      *(float *)((long)param_1 + 0x96c) = 0.0 - (fVar32 / fVar25 + fVar32 / fVar25);
      *(float *)((long)param_1 + 0x97c) = 0.0 - (fVar33 / fVar34 + fVar33 / fVar34);
      *(float *)(param_1 + 0x131) = fVar36;
      fVar35 = fVar29 + ((fVar29 - fVar30) * (fVar31 / fVar26)) / fVar35;
    }
    *(float *)(param_1 + 0x191) = fVar36;
    fVar28 = (fVar25 * 0.5 + fVar25 * 0.5) / fVar28;
    *(float *)((long)param_1 + 0x98c) = fVar35;
    *(float *)(param_1 + 400) = fVar28;
    *(float *)((long)param_1 + 0xc84) = -fVar28 / fVar27;
    *(float *)((long)param_1 + 0xc8c) = fVar35;
    if (*(char *)((long)param_1 + 0xeae) == '\0') {
      fVar27 = *(float *)((long)param_1 + 0xde4) * *(float *)((long)param_1 + 0xedc);
      *(float *)((long)param_1 + 0xdec) = fVar27;
      lVar10 = _UNK_027dbb38;
      lVar9 = _UNK_027dbb30;
      lVar8 = _UNK_027dbb28;
      lVar7 = _UNK_027dbb20;
      lVar24 = _UNK_027dbb18;
      lVar23 = _UNK_027dbb10;
      lVar11 = _UNK_027dbb00;
      if ((uVar14 & 1) == 0) {
        param_1[0x19f] = 0;
        param_1[0x19e] = 0;
        param_1[0x1a1] = 0;
        param_1[0x1a0] = 0;
        param_1[0x19b] = 0;
        param_1[0x19a] = 0;
        param_1[0x19d] = 0;
        param_1[0x19c] = 0;
        *(float *)(param_1 + 0x19a) = fVar22;
        *(float *)((long)param_1 + 0xce4) = fVar27 * fVar22;
        *(float *)(param_1 + 0x19b) = (fVar32 / fVar25) * -2.0 + 0.0;
        *(float *)(param_1 + 0x19d) = 0.0 - (fVar33 / fVar34 + fVar33 / fVar34);
        *(float *)(param_1 + 0x19f) = (fVar30 * fVar26 - fVar29 * fVar31) / (fVar26 - fVar31);
        *(float *)((long)param_1 + 0xcfc) =
             ((fVar29 - fVar30) * fVar31 * fVar26) / (fVar26 - fVar31);
        *(undefined4 *)(param_1 + 0x1a1) = 0x3f800000;
      }
      else {
        fVar22 = 1.0 - fVar31 / fVar26;
        param_1[0x19b] = _UNK_027dbb08;
        param_1[0x19a] = lVar11;
        *(float *)(param_1 + 0x19a) = 2.0 / *(float *)(param_1 + 0x1c1);
        param_1[0x19d] = lVar24;
        param_1[0x19c] = lVar23;
        param_1[0x19f] = lVar8;
        param_1[0x19e] = lVar7;
        param_1[0x1a1] = lVar10;
        param_1[0x1a0] = lVar9;
        *(float *)((long)param_1 + 0xcdc) = 0.0 - (fVar32 / fVar25 + fVar32 / fVar25);
        *(float *)((long)param_1 + 0xcec) = 0.0 - (fVar33 / fVar34 + fVar33 / fVar34);
        *(float *)(param_1 + 0x19f) = ((fVar29 - fVar30) * (-1.0 / fVar26)) / fVar22;
        *(float *)((long)param_1 + 0xce4) = fVar27 * (2.0 / *(float *)(param_1 + 0x1c1));
        *(float *)((long)param_1 + 0xcfc) =
             fVar29 + ((fVar29 - fVar30) * (fVar31 / fVar26)) / fVar22;
      }
    }
    else {
      param_1[0x19b] = param_1[0x12d];
      param_1[0x19a] = param_1[300];
      param_1[0x19d] = param_1[0x12f];
      param_1[0x19c] = param_1[0x12e];
      param_1[0x19f] = param_1[0x131];
      param_1[0x19e] = param_1[0x130];
      param_1[0x1a1] = param_1[0x133];
      param_1[0x1a0] = param_1[0x132];
    }
    uVar15 = uVar14 & 0xfffd;
    *puVar16 = (ushort)uVar15;
    *(int *)((long)param_1 + 0xe2c) = iVar2;
  }
  plVar1 = param_1 + 0x26;
  plVar18 = plVar1;
  if ((uVar15 >> 6 & 1) != 0) {
    Aska::Matrix::Mul(Aska::Matrix const*, Aska::Matrix const*)(alStack_d0,param_1 + 0x1ea,plVar1);
    plVar18 = alStack_d0;
  }
  puVar13 = (undefined8 *)
            Aska::RenderTargetManagerGL::GetRenderTarget(unsigned int)(*(undefined8 *)PTR__ZN4Aska6Global22m_pRenderTargetManagerE_02cbfa00,
                            *(undefined1 *)((long)param_1 + 0xeae));
  if ((puVar13 != (undefined8 *)0x0) && (puVar20 = (ushort *)puVar13[1], puVar20 != (ushort *)0x0))
  {
    if (*(char *)((long)param_1 + 0xeb1) != '\x01') {
      uVar14 = puVar20[5];
      uVar21 = (ulong)uVar14;
      uVar4 = *puVar20 >> 1;
      uVar5 = puVar20[1] >> 1;
      if ((*(byte *)puVar16 & 1) == 0) {
        if (uVar14 != 0) {
          pfVar19 = (float *)(param_1 + 0x14c);
          do {
            puVar16 = (ushort *)*puVar13;
            lVar11 = param_1[300];
            uVar14 = *puVar16;
            uVar3 = puVar16[1];
            *(long *)(pfVar19 + 2) = param_1[0x12d];
            *(long *)pfVar19 = lVar11;
            lVar23 = param_1[0x12e];
            fVar25 = (float)(uVar3 >> 1);
            *(long *)(pfVar19 + 6) = param_1[0x12f];
            *(long *)(pfVar19 + 4) = lVar23;
            lVar23 = param_1[0x130];
            fVar22 = (float)(uVar14 >> 1);
            fVar27 = (float)uVar4 / fVar22;
            *(long *)(pfVar19 + 10) = param_1[0x131];
            *(long *)(pfVar19 + 8) = lVar23;
            lVar24 = param_1[0x133];
            lVar23 = param_1[0x132];
            *pfVar19 = fVar27 * (float)lVar11;
            fVar28 = (float)uVar5 / fVar25;
            *(long *)(pfVar19 + 0xe) = lVar24;
            *(long *)(pfVar19 + 0xc) = lVar23;
            pfVar19[5] = fVar28 * pfVar19[5];
            pfVar19[2] = fVar27 * pfVar19[2] +
                         (float)(int)((((uint)uVar4 - (uint)(uVar14 >> 1)) + (uint)puVar16[4]) -
                                     (uint)puVar16[6]) / fVar22;
            pfVar19[6] = fVar28 * pfVar19[6] -
                         (float)(int)((((uint)uVar5 - (uint)(uVar3 >> 1)) + (uint)puVar16[5]) -
                                     (uint)puVar16[7]) / fVar25;
            Aska::Matrix::Mul(Aska::Matrix const*)(pfVar19,plVar18);
            uVar21 = uVar21 - 1;
            pfVar19 = pfVar19 + 0x10;
            puVar13 = puVar13 + 0x10;
          } while (uVar21 != 0);
        }
      }
      else if (uVar14 != 0) {
        pfVar19 = (float *)(param_1 + 0x14c);
        do {
          puVar16 = (ushort *)*puVar13;
          lVar11 = param_1[300];
          uVar14 = *puVar16;
          uVar3 = puVar16[1];
          *(long *)(pfVar19 + 2) = param_1[0x12d];
          *(long *)pfVar19 = lVar11;
          lVar23 = param_1[0x12e];
          fVar27 = (float)(uVar3 >> 1);
          *(long *)(pfVar19 + 6) = param_1[0x12f];
          *(long *)(pfVar19 + 4) = lVar23;
          lVar23 = param_1[0x130];
          fVar25 = (float)(uVar14 >> 1);
          fVar28 = (float)uVar4 / fVar25;
          *(long *)(pfVar19 + 10) = param_1[0x131];
          *(long *)(pfVar19 + 8) = lVar23;
          lVar24 = param_1[0x133];
          lVar23 = param_1[0x132];
          *pfVar19 = fVar28 * (float)lVar11;
          fVar22 = (float)uVar5 / fVar27;
          pfVar19[5] = fVar22 * pfVar19[5];
          *(long *)(pfVar19 + 0xe) = lVar24;
          *(long *)(pfVar19 + 0xc) = lVar23;
          pfVar19[3] = fVar28 * pfVar19[3] +
                       (float)(int)((((uint)uVar4 - (uint)(uVar14 >> 1)) + (uint)puVar16[4]) -
                                   (uint)puVar16[6]) / fVar25;
          pfVar19[7] = fVar22 * pfVar19[7] -
                       (float)(int)((((uint)uVar5 - (uint)(uVar3 >> 1)) + (uint)puVar16[5]) -
                                   (uint)puVar16[7]) / fVar27;
          Aska::Matrix::Mul(Aska::Matrix const*)(pfVar19,plVar18);
          uVar21 = uVar21 - 1;
          pfVar19 = pfVar19 + 0x10;
          puVar13 = puVar13 + 0x10;
        } while (uVar21 != 0);
      }
    }
    if (*(char *)((long)param_1 + 0xeae) == '\0') {
      fVar22 = (float)(uint)(*puVar20 >> 1) / (float)((uint)puVar20[2] + (uint)(*puVar20 >> 1));
      fVar25 = (float)(puVar20[1] >> 1) / (float)((uint)puVar20[3] + (uint)(puVar20[1] >> 1));
      param_1[0x145] = param_1[0x12d];
      param_1[0x144] = param_1[300];
      param_1[0x147] = param_1[0x12f];
      param_1[0x146] = param_1[0x12e];
      *(float *)(param_1 + 0x144) = fVar22 * (float)param_1[300];
      *(float *)((long)param_1 + 0xa34) = fVar25 * (float)((ulong)param_1[0x12e] >> 0x20);
      *(float *)(param_1 + 0x145) = fVar22 * (float)param_1[0x12d];
      *(float *)(param_1 + 0x147) = fVar25 * (float)param_1[0x12f];
      param_1[0x149] = param_1[0x131];
      param_1[0x148] = param_1[0x130];
      param_1[0x14b] = param_1[0x133];
      param_1[0x14a] = param_1[0x132];
      param_1[0x139] = param_1[0x131];
      param_1[0x138] = param_1[0x130];
      param_1[0x135] = param_1[0x145];
      param_1[0x134] = param_1[0x144];
      param_1[0x137] = param_1[0x147];
      param_1[0x136] = param_1[0x146];
      param_1[0x13b] = param_1[0x133];
      param_1[0x13a] = param_1[0x132];
      Aska::Matrix::Mul(Aska::Matrix const*)(param_1 + 0x144,plVar18);
      *(float *)(param_1 + 0x1be) = (fVar25 / fVar22) * *(float *)(param_1 + 0x1bd);
      goto code_r0x021ea534;
    }
  }
  param_1[0x145] = param_1[0x12d];
  param_1[0x144] = param_1[300];
  param_1[0x147] = param_1[0x12f];
  param_1[0x146] = param_1[0x12e];
  param_1[0x149] = param_1[0x131];
  param_1[0x148] = param_1[0x130];
  param_1[0x14b] = param_1[0x133];
  param_1[0x14a] = param_1[0x132];
  param_1[0x135] = param_1[0x12d];
  param_1[0x134] = param_1[300];
  param_1[0x137] = param_1[0x12f];
  param_1[0x136] = param_1[0x12e];
  param_1[0x139] = param_1[0x131];
  param_1[0x138] = param_1[0x130];
  param_1[0x13b] = param_1[0x133];
  param_1[0x13a] = param_1[0x132];
  Aska::Matrix::Mul(Aska::Matrix const*)(param_1 + 0x144,plVar18);
  *(int *)(param_1 + 0x1be) = (int)param_1[0x1bd];
code_r0x021ea534:
  param_1[0x13d] = param_1[0x19b];
  param_1[0x13c] = param_1[0x19a];
  param_1[0x13f] = param_1[0x19d];
  param_1[0x13e] = param_1[0x19c];
  param_1[0x141] = param_1[0x19f];
  param_1[0x140] = param_1[0x19e];
  param_1[0x143] = param_1[0x1a1];
  param_1[0x142] = param_1[0x1a0];
  Aska::Matrix::Mul(Aska::Matrix const*)(param_1 + 0x13c,plVar18);
  *(undefined2 *)(param_1 + 0x129) = 0;
  param_1[0x128] = 0;
  if ((*(byte *)((long)param_1 + 0xeb4) >> 4 & 1) != 0) {
    fVar22 = (float)(**(code **)**(undefined8 **)PTR__ZN4Aska6Global8m_pVSyncE_02cbd460)
                              (*(undefined8 **)PTR__ZN4Aska6Global8m_pVSyncE_02cbd460,0);
    if (fVar22 <= _UNK_027e519c) {
      fVar22 = *(float *)(param_1 + 0x1bc);
    }
    else {
      fVar22 = *(float *)(param_1[0x1c2] + 0x30) / fVar22;
      *(float *)(param_1 + 0x1bc) = fVar22;
    }
    Aska::Matrix::Lerp(Aska::Matrix const*, Aska::Matrix const*, float)(fVar22 * *(float *)PTR__ZN4Aska6Camera23m_fMasterMotionBlurRateE_02cb81b8,
                    param_1 + 0x1b4,plVar1,param_1 + 0x1ac);
    Aska::Matrix::MulFromLeft(Aska::Matrix const*)(param_1 + 0x1b4,param_1 + 0x134);
  }
  return;
}

// ==== Aska::Camera::Default()
// vaddr 0x20ea6c0 | ghidra 0x21ea6c0 | size 392 | symbol _ZN4Aska6Camera7DefaultEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6Camera7DefaultEv(long param_1)

{
  ushort *puVar1;
  undefined4 uVar2;
  ushort uVar3;
  int iVar4;
  float fVar5;
  float fVar6;
  undefined *puVar7;
  long lVar8;
  long *plVar9;
  long lVar10;
  ushort *puVar11;
  
  lVar8 = Aska::RenderTargetManagerGL::GetRenderTarget(unsigned int)(*(undefined8 *)PTR__ZN4Aska6Global22m_pRenderTargetManagerE_02cbfa00,0);
  lVar10 = *(long *)(lVar8 + 0x10);
  *(undefined2 *)(param_1 + 0xeae) = 0;
  puVar1 = (ushort *)(param_1 + 0xeb3);
  uVar2 = *(undefined4 *)(lVar10 + 0x54);
  *(undefined4 *)(param_1 + 0xe08) = 0x43fa0000;
  *(char *)(param_1 + 0xeb0) = (char)uVar2;
  *puVar1 = *puVar1 | 2;
  lVar10 = operator new(unsigned long, std::nothrow_t const&)(0x70,PTR__ZSt7nothrow_02cb9a80);
  if (lVar10 != 0) {
    Aska::Lens::Lens()(lVar10);
  }
  plVar9 = *(long **)(param_1 + 0xe10);
  if (plVar9 != (long *)0x0) {
    iVar4 = (int)plVar9[1] + -1;
    *(int *)(plVar9 + 1) = iVar4;
    if (iVar4 == 0) {
      (**(code **)(*plVar9 + 8))();
    }
    *(undefined8 *)(param_1 + 0xe10) = 0;
  }
  *(long *)(param_1 + 0xe10) = lVar10;
  if (lVar10 != 0) {
    *(int *)(lVar10 + 8) = *(int *)(lVar10 + 8) + 1;
  }
  *puVar1 = *puVar1 | 2;
  lVar10 = *(long *)PTR__ZN4Aska6Global20m_pOpticalPhenomenonE_02cc1ac0;
  if (lVar10 != 0) {
    if (*(long *)(param_1 + 0xe18) != 0) {
      Aska::DeleteManager::AddMain(void*, unsigned char, unsigned char, Aska::IDeleteHandler*)(PTR__ZN4Aska6Global21m_systemDeleteManagerE_02cb77c0,
                      *(long *)(param_1 + 0xe18),7,0,0);
    }
    *(long *)(param_1 + 0xe18) = lVar10;
    *(int *)(lVar10 + 8) = *(int *)(lVar10 + 8) + 1;
  }
  uVar2 = Aska::RenderTarget::GetAspectRatio() const(lVar8);
  *(undefined4 *)(param_1 + 0xed0) = uVar2;
  uVar3 = *puVar1 | 2;
  *puVar1 = uVar3;
  puVar11 = *(ushort **)(lVar8 + 8);
  uVar2 = NEON_ucvtf((uint)*puVar11);
  *(undefined4 *)(param_1 + 0xed4) = uVar2;
  *puVar1 = uVar3;
  puVar7 = PTR__ZN4Aska6Global14m_pFrameBufferE_02cb8198;
  uVar2 = NEON_ucvtf((uint)puVar11[1]);
  *(undefined4 *)(param_1 + 0xed8) = uVar2;
  *puVar1 = uVar3;
  lVar8 = *(long *)puVar7;
  uVar2 = NEON_ucvtf((uint)*(ushort *)(lVar8 + 0x18));
  *(undefined4 *)(param_1 + 0xee0) = uVar2;
  uVar2 = NEON_ucvtf((uint)*(ushort *)(lVar8 + 0x1a));
  *(undefined4 *)(param_1 + 0xee4) = uVar2;
  fVar5 = (float)NEON_ucvtf((uint)*(ushort *)(lVar8 + 0x18));
  fVar6 = (float)NEON_ucvtf((uint)*(ushort *)(lVar8 + 0x1a));
  *(float *)(param_1 + 0xedc) = fVar5 / fVar6;
  (*(code *)PTR__ZN4Aska6Camera13DefaultCommonEv_02c9d740)(param_1);
  return;
}

// ==== Aska::Camera::DefaultCommon()
// vaddr 0x20ea978 | ghidra 0x21ea978 | size 592 | symbol _ZN4Aska6Camera13DefaultCommonEv | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

bool _ZN4Aska6Camera13DefaultCommonEv(long param_1)

{
  ushort *puVar1;
  byte bVar2;
  ushort uVar3;
  float fVar4;
  undefined8 uVar5;
  long lVar6;
  float fVar7;
  float fVar8;
  undefined1 auVar9 [16];
  
  if (*(long *)(param_1 + 0xe10) != 0) {
    Aska::Lens::SetBaseView(float)();
    Aska::Lens::SetZoom(float)(*(undefined8 *)(param_1 + 0xe10));
    lVar6 = *(long *)(param_1 + 0xe10);
    *(undefined4 *)(lVar6 + 0x14) = 0x3f800000;
    *(int *)(lVar6 + 0x6c) = *(int *)(lVar6 + 0x6c) + 1;
  }
  uVar5 = _UNK_029c8d00;
  puVar1 = (ushort *)(param_1 + 0xeb3);
  uVar3 = *puVar1;
  *(undefined8 *)(param_1 + 0xec0) = _UNK_029c8d08;
  *(undefined8 *)(param_1 + 0xeb8) = uVar5;
  auVar9 = NEON_fmov(0x3f800000,4);
  *(undefined8 *)(param_1 + 0xe00) = 0x474350004121999a;
  *(undefined4 *)(param_1 + 0xec8) = 0x3f800000;
  *(undefined4 *)(param_1 + 0xecc) = 0;
  *(undefined4 *)(param_1 + 0xde4) = 0x3f800000;
  *(undefined1 *)(param_1 + 0xeb2) = 0;
  *(undefined8 *)(param_1 + 0xee8) = 0x461c4000469c4000;
  *(undefined4 *)(param_1 + 0xef0) = 0;
  *(long *)(param_1 + 0xf08) = auVar9._8_8_;
  *(long *)(param_1 + 0xf00) = auVar9._0_8_;
  *(undefined4 *)(param_1 + 0xf10) = 0x3f800000;
  *(undefined8 *)(param_1 + 0xf14) = 0x3f8000003f800000;
  *(undefined4 *)(param_1 + 0xf1c) = 0x3f800000;
  *puVar1 = uVar3 | 6;
  if ((uVar3 >> 0xc & 1) != 0) {
    *puVar1 = uVar3 & 0xefff | 6;
    *(undefined4 *)(param_1 + 0xde0) = 0;
    *(long *)(param_1 + 0xd68) = SUB168(*(undefined1 (*) [16])(param_1 + 0x130),8);
    *(long *)(param_1 + 0xd60) = SUB168(*(undefined1 (*) [16])(param_1 + 0x130),0);
    *(undefined8 *)(param_1 + 0xd78) = *(undefined8 *)(param_1 + 0x148);
    *(undefined8 *)(param_1 + 0xd70) = *(undefined8 *)(param_1 + 0x140);
    *(undefined8 *)(param_1 + 0xd88) = *(undefined8 *)(param_1 + 0x158);
    *(undefined8 *)(param_1 + 0xd80) = *(undefined8 *)(param_1 + 0x150);
    *(undefined8 *)(param_1 + 0xd98) = *(undefined8 *)(param_1 + 0x168);
    *(undefined8 *)(param_1 + 0xd90) = *(undefined8 *)(param_1 + 0x160);
  }
  lVar6 = *(long *)(param_1 + 0xe10);
  if (lVar6 != 0) {
    fVar7 = (float)Aska::LensStructure::GetMaxFStop() const(lVar6 + 0x18);
    fVar8 = (float)Aska::LensStructure::GetMinFStop() const(lVar6 + 0x18);
    fVar4 = _UNK_029c8d38;
    if (_UNK_029c8d38 - fVar8 < 0.0) {
      fVar4 = fVar8;
    }
    if (fVar4 - fVar7 < 0.0) {
      fVar7 = fVar4;
    }
    bVar2 = *(byte *)(lVar6 + 0x68) | 2;
    if (fVar7 == _UNK_029c8d38) {
      bVar2 = *(byte *)(lVar6 + 0x68) & 0xfd;
    }
    *(byte *)(lVar6 + 0x68) = bVar2;
    if (*(float *)(lVar6 + 0x2c) != fVar7) {
      *(byte *)(lVar6 + 0x68) = bVar2 | 0x20;
      *(float *)(lVar6 + 0x2c) = fVar7;
      *(int *)(lVar6 + 0x6c) = *(int *)(lVar6 + 0x6c) + 1;
    }
    lVar6 = *(long *)(param_1 + 0xe10);
    if (*(float *)(lVar6 + 0x34) != 0.0) {
      *(undefined8 *)(lVar6 + 0x34) = 0;
      *(byte *)(lVar6 + 0x68) = *(byte *)(lVar6 + 0x68) | 0x20;
      lVar6 = *(long *)(param_1 + 0xe10);
    }
    Aska::Lens::SetFocusDepth(float)(lVar6);
    *(byte *)(*(long *)(param_1 + 0xe10) + 0x68) =
         *(byte *)(*(long *)(param_1 + 0xe10) + 0x68) & 0xf7;
    *(undefined1 *)(*(long *)(param_1 + 0xe10) + 0x67) = 3;
    lVar6 = *(long *)(param_1 + 0xe10);
    if (*(float *)(lVar6 + 0x40) != _UNK_0296bcf8) {
      *(int *)(lVar6 + 0x6c) = *(int *)(lVar6 + 0x6c) + 1;
      tanf(*(float *)(lVar6 + 0xc) * 0.5,0x3f000000);
      *(undefined4 *)(lVar6 + 0x40) = 0x42100000;
      atanf();
      Aska::Lens::SetBaseView(float)(lVar6);
      lVar6 = *(long *)(param_1 + 0xe10);
    }
    Aska::Lens::CalcExposureControl()(lVar6);
  }
  *(long *)(param_1 + 0xe30) = *(long *)PTR__ZN4Aska6Global16m_pCameraManagerE_02cb7d08 + 0x1000;
  Aska::Camera::AdjustCameraEV()(param_1);
  return *(long *)(param_1 + 0xe10) != 0;
}

// ==== Aska::Camera::SetZBufferRange(double, double)
// vaddr 0x20eabc8 | ghidra 0x21eabc8 | size 44 | symbol _ZN4Aska6Camera15SetZBufferRangeEdd | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6Camera15SetZBufferRangeEdd(double param_1,double param_2,long param_3)

{
  *(ushort *)(param_3 + 0xeb3) = *(ushort *)(param_3 + 0xeb3) | 2;
  *(double *)(param_3 + 0xeb8) = param_1;
  *(double *)(param_3 + 0xec0) = param_2;
  *(float *)(param_3 + 0xec8) = (float)param_2;
  *(float *)(param_3 + 0xecc) = (float)param_1;
  return;
}

// ==== Aska::Camera::AdjustCameraEV()
// vaddr 0x20eb0f0 | ghidra 0x21eb0f0 | size 348 | symbol _ZN4Aska6Camera14AdjustCameraEVEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6Camera14AdjustCameraEVEv(long param_1)

{
  long lVar1;
  long lVar2;
  ulong uVar3;
  long lVar4;
  float fVar5;
  float fVar6;
  
  uVar3 = (ulong)*(byte *)(param_1 + 0xeae);
  lVar2 = *(long *)PTR__ZN4Aska6Global16m_pObjectManagerE_02cc4688;
  if (uVar3 == 0) {
    lVar1 = *(long *)(lVar2 + 0xb418);
  }
  else {
    if ((*(byte *)(lVar2 + (uVar3 - 1) * 0x48 + 0x4632) >> 5 & 1) == 0) {
      return;
    }
    lVar1 = *(long *)(lVar2 + (uVar3 - 1) * 0x48 + 0x4618);
  }
  if (lVar1 == 0) {
    return;
  }
  lVar1 = *(long *)(param_1 + 0xe10);
  if (*(char *)(param_1 + 0xead) == '\0') {
    fVar5 = *(float *)(param_1 + 0xe20) + *(float *)(lVar1 + 0x58);
  }
  else {
    if (*(byte *)(param_1 + 0xeae) == 0) {
      lVar4 = 0xb418;
    }
    else {
      fVar5 = 0.0;
      if ((*(byte *)(lVar2 + (uVar3 - 1) * 0x48 + 0x4632) >> 5 & 1) == 0) goto code_r0x021eb1e0;
      lVar2 = lVar2 + (uVar3 - 1) * 0x48;
      lVar4 = 0x4618;
    }
    if (*(long *)(lVar2 + lVar4) == 0) {
      fVar5 = 0.0;
    }
    else {
      fVar5 = *(float *)(*(long *)(*(long *)(lVar2 + lVar4) + 0x470) + 0x344);
      fVar6 = *(float *)(param_1 + 0xe24);
      if (0.0 <= fVar6 + 6.0) {
        fVar6 = -6.0;
      }
      if (fVar5 - fVar6 < 0.0) {
        fVar5 = fVar6;
      }
    }
  }
code_r0x021eb1e0:
  if (fVar5 - *(float *)(param_1 + 0xe24) < 0.0) {
    fVar5 = *(float *)(param_1 + 0xe24);
  }
  fVar6 = *(float *)(param_1 + 0xe28);
  if (fVar5 - *(float *)(param_1 + 0xe28) < 0.0) {
    fVar6 = fVar5;
  }
  if (*(float *)(lVar1 + 0x48) != fVar6) {
    *(float *)(lVar1 + 0x48) = fVar6;
    *(byte *)(lVar1 + 0x68) = *(byte *)(lVar1 + 0x68) | 0x20;
  }
  fVar5 = (float)Aska::CameraFilterManager::GetIsoExposureOffset()(*(undefined8 *)(param_1 + 0xe30));
  lVar2 = *(long *)(param_1 + 0xe10);
  if (*(float *)(lVar2 + 0x4c) != fVar5) {
    *(float *)(lVar2 + 0x4c) = fVar5;
    *(byte *)(lVar2 + 0x68) = *(byte *)(lVar2 + 0x68) | 0x20;
  }
  return;
}

// ==== Aska::Camera::DefaultForMultipassRendering(unsigned int, int, int, int, int)
// vaddr 0x20eb24c | ghidra 0x21eb24c | size 360 | symbol _ZN4Aska6Camera28DefaultForMultipassRenderingEjiiii | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6Camera28DefaultForMultipassRenderingEjiiii
               (long param_1,undefined1 param_2,int param_3,int param_4,undefined1 param_5,
               int param_6)

{
  ushort *puVar1;
  int iVar2;
  ulong uVar3;
  long lVar4;
  long *plVar5;
  ushort uVar6;
  float fVar7;
  float fVar8;
  
  *(undefined1 *)(param_1 + 0xeae) = param_2;
  *(undefined1 *)(param_1 + 0xeaf) = param_2;
  *(char *)(param_1 + 0xeb0) = (char)param_6;
  if ((param_6 == 0x991ca1) &&
     (uVar3 = Aska::RenderDeviceGL::IsSupported(Aska::GLExtension::E) const(*(undefined8 *)PTR__ZN4Aska12g_pRenderDevE_02cbb1a0,0xd),
     (uVar3 & 1) == 0)) {
    *(undefined1 *)(param_1 + 0xeb0) = 0x87;
  }
  *(undefined4 *)(param_1 + 0xe08) = 0x43fa0000;
  puVar1 = (ushort *)(param_1 + 0xeb3);
  *puVar1 = *puVar1 | 2;
  lVar4 = operator new(unsigned long, std::nothrow_t const&)(0x70,PTR__ZSt7nothrow_02cb9a80);
  if (lVar4 != 0) {
    Aska::Lens::Lens()(lVar4);
  }
  plVar5 = *(long **)(param_1 + 0xe10);
  if (plVar5 != (long *)0x0) {
    iVar2 = (int)plVar5[1] + -1;
    *(int *)(plVar5 + 1) = iVar2;
    if (iVar2 == 0) {
      (**(code **)(*plVar5 + 8))();
    }
    *(undefined8 *)(param_1 + 0xe10) = 0;
  }
  *(long *)(param_1 + 0xe10) = lVar4;
  if (lVar4 != 0) {
    *(int *)(lVar4 + 8) = *(int *)(lVar4 + 8) + 1;
  }
  uVar6 = *puVar1 | 2;
  *puVar1 = uVar6;
  lVar4 = *(long *)PTR__ZN4Aska6Global20m_pOpticalPhenomenonE_02cc1ac0;
  if (lVar4 != 0) {
    if (*(long *)(param_1 + 0xe18) != 0) {
      Aska::DeleteManager::AddMain(void*, unsigned char, unsigned char, Aska::IDeleteHandler*)(PTR__ZN4Aska6Global21m_systemDeleteManagerE_02cb77c0,
                      *(long *)(param_1 + 0xe18),7,0,0);
    }
    *(long *)(param_1 + 0xe18) = lVar4;
    *(int *)(lVar4 + 8) = *(int *)(lVar4 + 8) + 1;
    uVar6 = *puVar1;
  }
  fVar7 = (float)param_3;
  fVar8 = (float)param_4;
  *(undefined1 *)(param_1 + 0xeb1) = param_5;
  *(float *)(param_1 + 0xed4) = fVar7;
  *(float *)(param_1 + 0xed8) = fVar8;
  *(float *)(param_1 + 0xed0) = fVar7 / fVar8;
  *puVar1 = uVar6 | 2;
  *(float *)(param_1 + 0xedc) = fVar7 / fVar8;
  *(float *)(param_1 + 0xee0) = fVar7;
  *(float *)(param_1 + 0xee4) = fVar8;
  (*(code *)PTR__ZN4Aska6Camera13DefaultCommonEv_02c9d740)(param_1);
  return;
}

// ==== Aska::Camera::CalcReprojectionMatrix(float, Aska::Matrix*) const
// vaddr 0x20eb3b4 | ghidra 0x21eb3b4 | size 524 | symbol _ZNK4Aska6Camera22CalcReprojectionMatrixEfPNS_6MatrixE | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK4Aska6Camera22CalcReprojectionMatrixEfPNS_6MatrixE
               (float param_1,long *param_2,long *param_3)

{
  undefined8 uVar1;
  long lVar2;
  float fStack_60;
  float fStack_5c;
  float fStack_58;
  float fStack_54;
  float fStack_50;
  float fStack_4c;
  float fStack_48;
  float fStack_44;
  float fStack_40;
  float fStack_3c;
  float fStack_38;
  float fStack_34;
  float fStack_30;
  float fStack_2c;
  float fStack_28;
  float fStack_24;
  
  fStack_60 = *(float *)(param_2 + 0x26) +
              (*(float *)(param_2 + 0x1ac) - *(float *)(param_2 + 0x26)) * param_1;
  fStack_5c = *(float *)((long)param_2 + 0x134) +
              (*(float *)((long)param_2 + 0xd64) - *(float *)((long)param_2 + 0x134)) * param_1;
  fStack_58 = *(float *)(param_2 + 0x27) +
              (*(float *)(param_2 + 0x1ad) - *(float *)(param_2 + 0x27)) * param_1;
  fStack_54 = *(float *)((long)param_2 + 0x13c) +
              (*(float *)((long)param_2 + 0xd6c) - *(float *)((long)param_2 + 0x13c)) * param_1;
  fStack_50 = *(float *)(param_2 + 0x28) +
              (*(float *)(param_2 + 0x1ae) - *(float *)(param_2 + 0x28)) * param_1;
  fStack_4c = *(float *)((long)param_2 + 0x144) +
              (*(float *)((long)param_2 + 0xd74) - *(float *)((long)param_2 + 0x144)) * param_1;
  fStack_48 = *(float *)(param_2 + 0x29) +
              (*(float *)(param_2 + 0x1af) - *(float *)(param_2 + 0x29)) * param_1;
  fStack_44 = *(float *)((long)param_2 + 0x14c) +
              (*(float *)((long)param_2 + 0xd7c) - *(float *)((long)param_2 + 0x14c)) * param_1;
  fStack_40 = *(float *)(param_2 + 0x2a) +
              (*(float *)(param_2 + 0x1b0) - *(float *)(param_2 + 0x2a)) * param_1;
  fStack_3c = *(float *)((long)param_2 + 0x154) +
              (*(float *)((long)param_2 + 0xd84) - *(float *)((long)param_2 + 0x154)) * param_1;
  fStack_38 = *(float *)(param_2 + 0x2b) +
              (*(float *)(param_2 + 0x1b1) - *(float *)(param_2 + 0x2b)) * param_1;
  fStack_34 = *(float *)((long)param_2 + 0x15c) +
              (*(float *)((long)param_2 + 0xd8c) - *(float *)((long)param_2 + 0x15c)) * param_1;
  fStack_30 = *(float *)(param_2 + 0x2c) +
              (*(float *)(param_2 + 0x1b2) - *(float *)(param_2 + 0x2c)) * param_1;
  fStack_2c = *(float *)((long)param_2 + 0x164) +
              (*(float *)((long)param_2 + 0xd94) - *(float *)((long)param_2 + 0x164)) * param_1;
  fStack_28 = *(float *)(param_2 + 0x2d) +
              (*(float *)(param_2 + 0x1b3) - *(float *)(param_2 + 0x2d)) * param_1;
  fStack_24 = *(float *)((long)param_2 + 0x16c) +
              (*(float *)((long)param_2 + 0xd9c) - *(float *)((long)param_2 + 0x16c)) * param_1;
  lVar2 = param_2[300];
  param_3[1] = param_2[0x12d];
  *param_3 = lVar2;
  lVar2 = param_2[0x12e];
  param_3[3] = param_2[0x12f];
  param_3[2] = lVar2;
  lVar2 = param_2[0x130];
  param_3[5] = param_2[0x131];
  param_3[4] = lVar2;
  lVar2 = param_2[0x132];
  param_3[7] = param_2[0x133];
  param_3[6] = lVar2;
  lVar2 = (ulong)(*(ushort *)((long)param_2 + 0xeb3) & 1 | 2) * 4;
  *(undefined4 *)((long)param_3 + lVar2) = 0;
  *(undefined4 *)((long)param_3 + lVar2 + 0x10) = 0;
  Aska::Matrix::Mul(Aska::Matrix const*)(param_3,&fStack_60);
  uVar1 = (**(code **)(*param_2 + 0x98))(param_2);
  Aska::Matrix::Mul(Aska::Matrix const*)(param_3,uVar1);
  return;
}

// ==== Aska::TArray<Aska::Camera::AFPoint, true>::Resize(long, bool)
// vaddr 0x20eb744 | ghidra 0x21eb744 | size 252 | symbol _ZN4Aska6TArrayINS_6Camera7AFPointELb1EE6ResizeElb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6TArrayINS_6Camera7AFPointELb1EE6ResizeElb(long param_1,long param_2)

{
  long lVar1;
  ushort uVar2;
  long lVar3;
  
  if (param_2 == 0) {
    if ((*(byte *)(param_1 + 0x32) & 1) != 0) {
      if (*(long *)(param_1 + 8) != 0) {
        operator delete[](void*)();
        *(undefined8 *)(param_1 + 8) = 0;
      }
      *(undefined8 *)(param_1 + 0x10) = 0;
    }
    *(undefined8 *)(param_1 + 0x18) = 0;
    *(undefined8 *)(param_1 + 0x20) = 0;
    return;
  }
  lVar3 = *(long *)(param_1 + 0x10);
  if (lVar3 < param_2) {
    lVar3 = param_2 << 1;
  }
  else {
    lVar1 = lVar3 + 3;
    if (-1 < lVar3) {
      lVar1 = lVar3;
    }
    if (((lVar1 >> 2 < param_2) || ((*(ushort *)(param_1 + 0x32) & 1) == 0)) ||
       (lVar3 = param_2 * 2,
       lVar3 - *(long *)(param_1 + 0x28) == 0 || lVar3 < *(long *)(param_1 + 0x28)))
    goto code_r0x021eb824;
  }
  if (*(long *)(param_1 + 8) == 0) {
    lVar3 = *(long *)(param_1 + 0x28);
    if (*(long *)(param_1 + 0x28) <= param_2) {
      lVar3 = param_2;
    }
    lVar1 = operator new[](unsigned long, std::nothrow_t const&)(lVar3 << 3,PTR__ZSt7nothrow_02cb9a80);
    *(long *)(param_1 + 8) = lVar1;
    if (lVar1 == 0) {
      *(ushort *)(param_1 + 0x30) = *(ushort *)(param_1 + 0x30) | 1;
      return;
    }
    uVar2 = *(ushort *)(param_1 + 0x30) & 0xfffe;
code_r0x021eb81c:
    *(ushort *)(param_1 + 0x30) = uVar2;
  }
  else {
    lVar1 = operator new[](unsigned long, void*, unsigned long)(param_2 << 4,*(long *)(param_1 + 8),4);
    if (lVar1 == 0) {
      uVar2 = *(ushort *)(param_1 + 0x30) | 1;
      goto code_r0x021eb81c;
    }
    *(long *)(param_1 + 8) = lVar1;
    *(long *)(param_1 + 0x10) = lVar3;
    *(long *)(param_1 + 0x18) = param_2;
  }
  *(long *)(param_1 + 0x10) = lVar3;
code_r0x021eb824:
  *(long *)(param_1 + 0x18) = param_2;
  return;
}

// ==== Aska::Camera::GetAFPoint(long, float*, float*)
// vaddr 0x20eb840 | ghidra 0x21eb840 | size 68 | symbol _ZN4Aska6Camera10GetAFPointElPfS1_ | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska6Camera10GetAFPointElPfS1_
          (long param_1,long param_2,undefined4 *param_3,undefined4 *param_4)

{
  undefined8 uVar1;
  long lVar2;
  
  uVar1 = 0;
  if ((-1 < param_2) && (param_2 < *(long *)(param_1 + 0xe88))) {
    lVar2 = *(long *)(param_1 + 0xe78);
    if (param_3 != (undefined4 *)0x0) {
      *param_3 = *(undefined4 *)(lVar2 + param_2 * 8);
    }
    if (param_4 != (undefined4 *)0x0) {
      *param_4 = *(undefined4 *)(lVar2 + param_2 * 8 + 4);
    }
    uVar1 = 1;
  }
  return uVar1;
}

// ==== Aska::Camera::GetExposureMeterValue() const
// vaddr 0x20eb884 | ghidra 0x21eb884 | size 196 | symbol _ZNK4Aska6Camera21GetExposureMeterValueEv | lib libSOA-3.7.0.so | 2026-10-04
float _ZNK4Aska6Camera21GetExposureMeterValueEv(long param_1)

{
  long lVar1;
  long lVar2;
  float fVar3;
  float fVar4;
  
  if (*(char *)(param_1 + 0xead) == '\0') {
    fVar3 = *(float *)(param_1 + 0xe20) + *(float *)(*(long *)(param_1 + 0xe10) + 0x58);
  }
  else {
    lVar1 = *(long *)PTR__ZN4Aska6Global16m_pObjectManagerE_02cc4688;
    if ((ulong)*(byte *)(param_1 + 0xeae) == 0) {
      lVar2 = 0xb418;
    }
    else {
      lVar2 = (ulong)*(byte *)(param_1 + 0xeae) - 1;
      fVar3 = 0.0;
      if ((*(byte *)(lVar1 + lVar2 * 0x48 + 0x4632) >> 5 & 1) == 0) goto code_r0x021eb924;
      lVar1 = lVar1 + lVar2 * 0x48;
      lVar2 = 0x4618;
    }
    if (*(long *)(lVar1 + lVar2) == 0) {
      fVar3 = 0.0;
    }
    else {
      fVar3 = *(float *)(*(long *)(*(long *)(lVar1 + lVar2) + 0x470) + 0x344);
      fVar4 = *(float *)(param_1 + 0xe24);
      if (0.0 <= fVar4 + 6.0) {
        fVar4 = -6.0;
      }
      if (fVar3 - fVar4 < 0.0) {
        fVar3 = fVar4;
      }
    }
  }
code_r0x021eb924:
  if (fVar3 - *(float *)(param_1 + 0xe24) < 0.0) {
    fVar3 = *(float *)(param_1 + 0xe24);
  }
  fVar4 = *(float *)(param_1 + 0xe28);
  if (fVar3 - *(float *)(param_1 + 0xe28) < 0.0) {
    fVar4 = fVar3;
  }
  return fVar4;
}

// ==== Aska::Camera::SetMeteringMode(int)
// vaddr 0x20eb948 | ghidra 0x21eb948 | size 4 | symbol _ZN4Aska6Camera15SetMeteringModeEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6Camera15SetMeteringModeEi(void)

{
  return;
}

// ==== Aska::Camera::GetMeteringMode(int*) const
// vaddr 0x20eb94c | ghidra 0x21eb94c | size 16 | symbol _ZNK4Aska6Camera15GetMeteringModeEPi | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska6Camera15GetMeteringModeEPi(long param_1,uint *param_2)

{
  *param_2 = (uint)*(byte *)(param_1 + 0xead);
  return 1;
}

// ==== Aska::Camera::SetAutoExposureSensitivity(float, float, float)
// vaddr 0x20eb95c | ghidra 0x21eb95c | size 16 | symbol _ZN4Aska6Camera26SetAutoExposureSensitivityEfff | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6Camera26SetAutoExposureSensitivityEfff
               (undefined4 param_1,undefined4 param_2,undefined4 param_3,long param_4)

{
  *(undefined4 *)(param_4 + 0xe50) = param_1;
  *(undefined4 *)(param_4 + 0xe58) = param_2;
  *(undefined4 *)(param_4 + 0xe5c) = param_3;
  return;
}

// ==== Aska::Camera::SetCenterweightedMetringGaussCoef(float)
// vaddr 0x20eb96c | ghidra 0x21eb96c | size 8 | symbol _ZN4Aska6Camera33SetCenterweightedMetringGaussCoefEf | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6Camera33SetCenterweightedMetringGaussCoefEf(undefined4 param_1,long param_2)

{
  *(undefined4 *)(param_2 + 0xe68) = param_1;
  return;
}

// ==== Aska::Camera::CalcMotionBlurMatrix(float, Aska::Matrix*, Aska::Matrix const*) const
// vaddr 0x20eb974 | ghidra 0x21eb974 | size 556 | symbol _ZNK4Aska6Camera20CalcMotionBlurMatrixEfPNS_6MatrixEPKS1_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK4Aska6Camera20CalcMotionBlurMatrixEfPNS_6MatrixEPKS1_
               (float param_1,long *param_2,long *param_3,float *param_4)

{
  undefined8 uVar1;
  long lVar2;
  float fStack_60;
  float fStack_5c;
  float fStack_58;
  float fStack_54;
  float fStack_50;
  float fStack_4c;
  float fStack_48;
  float fStack_44;
  float fStack_40;
  float fStack_3c;
  float fStack_38;
  float fStack_34;
  float fStack_30;
  float fStack_2c;
  float fStack_28;
  float fStack_24;
  
  if (param_4 == (float *)0x0) {
    param_4 = (float *)(param_2 + 0x1ac);
    param_1 = *(float *)(param_2 + 0x1bc) *
              *(float *)PTR__ZN4Aska6Camera23m_fMasterMotionBlurRateE_02cb81b8 * param_1;
  }
  fStack_60 = *(float *)(param_2 + 0x26) + param_1 * (*param_4 - *(float *)(param_2 + 0x26));
  fStack_5c = *(float *)((long)param_2 + 0x134) +
              param_1 * (param_4[1] - *(float *)((long)param_2 + 0x134));
  fStack_58 = *(float *)(param_2 + 0x27) + param_1 * (param_4[2] - *(float *)(param_2 + 0x27));
  fStack_54 = *(float *)((long)param_2 + 0x13c) +
              param_1 * (param_4[3] - *(float *)((long)param_2 + 0x13c));
  fStack_50 = *(float *)(param_2 + 0x28) + param_1 * (param_4[4] - *(float *)(param_2 + 0x28));
  fStack_4c = *(float *)((long)param_2 + 0x144) +
              param_1 * (param_4[5] - *(float *)((long)param_2 + 0x144));
  fStack_48 = *(float *)(param_2 + 0x29) + param_1 * (param_4[6] - *(float *)(param_2 + 0x29));
  fStack_44 = *(float *)((long)param_2 + 0x14c) +
              param_1 * (param_4[7] - *(float *)((long)param_2 + 0x14c));
  fStack_40 = *(float *)(param_2 + 0x2a) + param_1 * (param_4[8] - *(float *)(param_2 + 0x2a));
  fStack_3c = *(float *)((long)param_2 + 0x154) +
              param_1 * (param_4[9] - *(float *)((long)param_2 + 0x154));
  fStack_38 = *(float *)(param_2 + 0x2b) + param_1 * (param_4[10] - *(float *)(param_2 + 0x2b));
  fStack_34 = *(float *)((long)param_2 + 0x15c) +
              param_1 * (param_4[0xb] - *(float *)((long)param_2 + 0x15c));
  fStack_30 = *(float *)(param_2 + 0x2c) + param_1 * (param_4[0xc] - *(float *)(param_2 + 0x2c));
  fStack_2c = *(float *)((long)param_2 + 0x164) +
              param_1 * (param_4[0xd] - *(float *)((long)param_2 + 0x164));
  fStack_28 = *(float *)(param_2 + 0x2d) + param_1 * (param_4[0xe] - *(float *)(param_2 + 0x2d));
  fStack_24 = *(float *)((long)param_2 + 0x16c) +
              param_1 * (param_4[0xf] - *(float *)((long)param_2 + 0x16c));
  lVar2 = param_2[300];
  param_3[1] = param_2[0x12d];
  *param_3 = lVar2;
  lVar2 = param_2[0x12e];
  param_3[3] = param_2[0x12f];
  param_3[2] = lVar2;
  lVar2 = param_2[0x130];
  param_3[5] = param_2[0x131];
  param_3[4] = lVar2;
  lVar2 = param_2[0x132];
  param_3[7] = param_2[0x133];
  param_3[6] = lVar2;
  lVar2 = (ulong)(*(ushort *)((long)param_2 + 0xeb3) & 1 | 2) * 4;
  *(undefined4 *)((long)param_3 + lVar2) = 0;
  *(undefined4 *)((long)param_3 + lVar2 + 0x10) = 0;
  Aska::Matrix::Mul(Aska::Matrix const*)(param_3,&fStack_60);
  uVar1 = (**(code **)(*param_2 + 0x98))(param_2);
  Aska::Matrix::Mul(Aska::Matrix const*)(param_3,uVar1);
  return;
}

// ==== Aska::Camera::CloneForMultipass(Aska::Camera const*)
// vaddr 0x20ebba0 | ghidra 0x21ebba0 | size 528 | symbol _ZN4Aska6Camera17CloneForMultipassEPKS0_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6Camera17CloneForMultipassEPKS0_(long param_1,long param_2)

{
  ushort *puVar1;
  int iVar2;
  long *plVar3;
  long lVar4;
  undefined8 uVar5;
  
  plVar3 = *(long **)(param_1 + 0xe10);
  lVar4 = *(long *)(param_2 + 0xe10);
  if (plVar3 != (long *)0x0) {
    iVar2 = (int)plVar3[1] + -1;
    *(int *)(plVar3 + 1) = iVar2;
    if (iVar2 == 0) {
      (**(code **)(*plVar3 + 8))();
    }
    *(undefined8 *)(param_1 + 0xe10) = 0;
  }
  *(long *)(param_1 + 0xe10) = lVar4;
  if (lVar4 != 0) {
    *(int *)(lVar4 + 8) = *(int *)(lVar4 + 8) + 1;
  }
  puVar1 = (ushort *)(param_1 + 0xeb3);
  *puVar1 = *puVar1 | 2;
  lVar4 = *(long *)(param_2 + 0xe18);
  if (lVar4 != 0) {
    if (*(long *)(param_1 + 0xe18) != 0) {
      Aska::DeleteManager::AddMain(void*, unsigned char, unsigned char, Aska::IDeleteHandler*)(PTR__ZN4Aska6Global21m_systemDeleteManagerE_02cb77c0,
                      *(long *)(param_1 + 0xe18),7,0,0);
    }
    *(long *)(param_1 + 0xe18) = lVar4;
    *(int *)(lVar4 + 8) = *(int *)(lVar4 + 8) + 1;
  }
  lVar4 = operator new(unsigned long, std::nothrow_t const&)(0x70,PTR__ZSt7nothrow_02cb9a80);
  if (lVar4 != 0) {
    Aska::Lens::Lens()(lVar4);
    Aska::Lens::Clone(Aska::Lens*)(lVar4,*(undefined8 *)(param_1 + 0xe10));
    plVar3 = *(long **)(param_1 + 0xe10);
    if (plVar3 != (long *)0x0) {
      iVar2 = (int)plVar3[1] + -1;
      *(int *)(plVar3 + 1) = iVar2;
      if (iVar2 == 0) {
        (**(code **)(*plVar3 + 8))();
      }
      *(undefined8 *)(param_1 + 0xe10) = 0;
    }
    *(long *)(param_1 + 0xe10) = lVar4;
    *(int *)(lVar4 + 8) = *(int *)(lVar4 + 8) + 1;
    *puVar1 = *puVar1 | 2;
  }
  lVar4 = operator new(unsigned long, std::nothrow_t const&)(0x430,PTR__ZSt7nothrow_02cb9a80);
  if (lVar4 != 0) {
    Aska::OpticalPhenomenon::OpticalPhenomenon()(lVar4);
    Aska::OpticalPhenomenon::Clone(Aska::OpticalPhenomenon*)(lVar4,*(undefined8 *)(param_1 + 0xe18));
    if (*(long *)(param_1 + 0xe18) != 0) {
      Aska::DeleteManager::AddMain(void*, unsigned char, unsigned char, Aska::IDeleteHandler*)(PTR__ZN4Aska6Global21m_systemDeleteManagerE_02cb77c0,
                      *(long *)(param_1 + 0xe18),7,0,0);
    }
    *(long *)(param_1 + 0xe18) = lVar4;
    *(int *)(lVar4 + 8) = *(int *)(lVar4 + 8) + 1;
  }
  *(undefined4 *)(param_1 + 0xde4) = *(undefined4 *)(param_2 + 0xde4);
  *(undefined4 *)(param_1 + 0xee8) = *(undefined4 *)(param_2 + 0xee8);
  *(undefined4 *)(param_1 + 0xeec) = *(undefined4 *)(param_2 + 0xeec);
  *(undefined4 *)(param_1 + 0xef0) = *(undefined4 *)(param_2 + 0xef0);
  *(undefined4 *)(param_1 + 0xf00) = *(undefined4 *)(param_2 + 0xf00);
  *(undefined4 *)(param_1 + 0xf04) = *(undefined4 *)(param_2 + 0xf04);
  *(undefined4 *)(param_1 + 0xf08) = *(undefined4 *)(param_2 + 0xf08);
  *(undefined4 *)(param_1 + 0xf0c) = *(undefined4 *)(param_2 + 0xf0c);
  *(undefined4 *)(param_1 + 0xf10) = *(undefined4 *)(param_2 + 0xf10);
  *(undefined4 *)(param_1 + 0xf14) = *(undefined4 *)(param_2 + 0xf14);
  *(undefined4 *)(param_1 + 0xf18) = *(undefined4 *)(param_2 + 0xf18);
  *(undefined4 *)(param_1 + 0xf1c) = *(undefined4 *)(param_2 + 0xf1c);
  *(undefined1 *)(param_1 + 0xeb2) = *(undefined1 *)(param_2 + 0xeb2);
  *(undefined4 *)(param_1 + 0xe20) = *(undefined4 *)(param_2 + 0xe20);
  *(undefined4 *)(param_1 + 0xe24) = *(undefined4 *)(param_2 + 0xe24);
  *(undefined4 *)(param_1 + 0xe28) = *(undefined4 *)(param_2 + 0xe28);
  uVar5 = *(undefined8 *)(param_2 + 0xf40);
  *(undefined8 *)(param_1 + 0xf48) = *(undefined8 *)(param_2 + 0xf48);
  *(undefined8 *)(param_1 + 0xf40) = uVar5;
  uVar5 = *(undefined8 *)(param_2 + 0xf30);
  *(undefined8 *)(param_1 + 0xf38) = *(undefined8 *)(param_2 + 0xf38);
  *(undefined8 *)(param_1 + 0xf30) = uVar5;
  uVar5 = *(undefined8 *)(param_2 + 0xf20);
  *(undefined8 *)(param_1 + 0xf28) = *(undefined8 *)(param_2 + 0xf28);
  *(undefined8 *)(param_1 + 0xf20) = uVar5;
  return;
}

// ==== Aska::Camera::CloneLens()
// vaddr 0x20ebdb0 | ghidra 0x21ebdb0 | size 144 | symbol _ZN4Aska6Camera9CloneLensEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska6Camera9CloneLensEv(long param_1)

{
  int iVar1;
  long lVar2;
  long *plVar3;
  undefined8 uVar4;
  
  lVar2 = operator new(unsigned long, std::nothrow_t const&)(0x70,PTR__ZSt7nothrow_02cb9a80);
  uVar4 = 0;
  if (lVar2 != 0) {
    Aska::Lens::Lens()(lVar2);
    Aska::Lens::Clone(Aska::Lens*)(lVar2,*(undefined8 *)(param_1 + 0xe10));
    plVar3 = *(long **)(param_1 + 0xe10);
    if (plVar3 != (long *)0x0) {
      iVar1 = (int)plVar3[1] + -1;
      *(int *)(plVar3 + 1) = iVar1;
      if (iVar1 == 0) {
        (**(code **)(*plVar3 + 8))();
      }
      *(undefined8 *)(param_1 + 0xe10) = 0;
    }
    *(long *)(param_1 + 0xe10) = lVar2;
    uVar4 = 1;
    *(int *)(lVar2 + 8) = *(int *)(lVar2 + 8) + 1;
    *(ushort *)(param_1 + 0xeb3) = *(ushort *)(param_1 + 0xeb3) | 2;
  }
  return uVar4;
}

// ==== Aska::Camera::CloneOpticalPhenomenon()
// vaddr 0x20ebe40 | ghidra 0x21ebe40 | size 120 | symbol _ZN4Aska6Camera22CloneOpticalPhenomenonEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska6Camera22CloneOpticalPhenomenonEv(long param_1)

{
  long lVar1;
  undefined8 uVar2;
  
  lVar1 = operator new(unsigned long, std::nothrow_t const&)(0x430,PTR__ZSt7nothrow_02cb9a80);
  uVar2 = 0;
  if (lVar1 != 0) {
    Aska::OpticalPhenomenon::OpticalPhenomenon()(lVar1);
    Aska::OpticalPhenomenon::Clone(Aska::OpticalPhenomenon*)(lVar1,*(undefined8 *)(param_1 + 0xe18));
    if (*(long *)(param_1 + 0xe18) != 0) {
      Aska::DeleteManager::AddMain(void*, unsigned char, unsigned char, Aska::IDeleteHandler*)(PTR__ZN4Aska6Global21m_systemDeleteManagerE_02cb77c0,
                      *(long *)(param_1 + 0xe18),7,0,0);
    }
    *(long *)(param_1 + 0xe18) = lVar1;
    uVar2 = 1;
    *(int *)(lVar1 + 8) = *(int *)(lVar1 + 8) + 1;
  }
  return uVar2;
}

// ==== Aska::Camera::CloneCommon(Aska::Camera const*)
// vaddr 0x20ebeb8 | ghidra 0x21ebeb8 | size 156 | symbol _ZN4Aska6Camera11CloneCommonEPKS0_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6Camera11CloneCommonEPKS0_(long param_1,long param_2)

{
  undefined8 uVar1;
  
  *(undefined4 *)(param_1 + 0xde4) = *(undefined4 *)(param_2 + 0xde4);
  *(undefined4 *)(param_1 + 0xee8) = *(undefined4 *)(param_2 + 0xee8);
  *(undefined4 *)(param_1 + 0xeec) = *(undefined4 *)(param_2 + 0xeec);
  *(undefined4 *)(param_1 + 0xef0) = *(undefined4 *)(param_2 + 0xef0);
  *(undefined4 *)(param_1 + 0xf00) = *(undefined4 *)(param_2 + 0xf00);
  *(undefined4 *)(param_1 + 0xf04) = *(undefined4 *)(param_2 + 0xf04);
  *(undefined4 *)(param_1 + 0xf08) = *(undefined4 *)(param_2 + 0xf08);
  *(undefined4 *)(param_1 + 0xf0c) = *(undefined4 *)(param_2 + 0xf0c);
  *(undefined4 *)(param_1 + 0xf10) = *(undefined4 *)(param_2 + 0xf10);
  *(undefined4 *)(param_1 + 0xf14) = *(undefined4 *)(param_2 + 0xf14);
  *(undefined4 *)(param_1 + 0xf18) = *(undefined4 *)(param_2 + 0xf18);
  *(undefined4 *)(param_1 + 0xf1c) = *(undefined4 *)(param_2 + 0xf1c);
  *(undefined1 *)(param_1 + 0xeb2) = *(undefined1 *)(param_2 + 0xeb2);
  *(undefined4 *)(param_1 + 0xe20) = *(undefined4 *)(param_2 + 0xe20);
  *(undefined4 *)(param_1 + 0xe24) = *(undefined4 *)(param_2 + 0xe24);
  *(undefined4 *)(param_1 + 0xe28) = *(undefined4 *)(param_2 + 0xe28);
  uVar1 = *(undefined8 *)(param_2 + 0xf40);
  *(undefined8 *)(param_1 + 0xf48) = *(undefined8 *)(param_2 + 0xf48);
  *(undefined8 *)(param_1 + 0xf40) = uVar1;
  uVar1 = *(undefined8 *)(param_2 + 0xf30);
  *(undefined8 *)(param_1 + 0xf38) = *(undefined8 *)(param_2 + 0xf38);
  *(undefined8 *)(param_1 + 0xf30) = uVar1;
  uVar1 = *(undefined8 *)(param_2 + 0xf20);
  *(undefined8 *)(param_1 + 0xf28) = *(undefined8 *)(param_2 + 0xf28);
  *(undefined8 *)(param_1 + 0xf20) = uVar1;
  return;
}

// ==== Aska::Camera::Clone(Aska::IAnimatable const*)
// vaddr 0x20ebf54 | ghidra 0x21ebf54 | size 1384 | symbol _ZN4Aska6Camera5CloneEPKNS_11IAnimatableE | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska6Camera5CloneEPKNS_11IAnimatableE(long param_1,long param_2)

{
  ushort *puVar1;
  ushort *puVar2;
  ushort uVar3;
  ushort uVar4;
  ushort uVar5;
  char cVar6;
  ushort uVar7;
  ushort uVar8;
  int iVar9;
  ushort uVar10;
  ulong uVar11;
  long *plVar12;
  undefined8 uVar13;
  long lVar14;
  undefined8 uVar15;
  
  uVar11 = Aska::AimingObject::Clone(Aska::IAnimatable const*)();
  if ((uVar11 & 1) == 0) {
    uVar13 = 0;
  }
  else {
    *(undefined4 *)(param_1 + 0xde4) = *(undefined4 *)(param_2 + 0xde4);
    *(undefined4 *)(param_1 + 0xee8) = *(undefined4 *)(param_2 + 0xee8);
    *(undefined4 *)(param_1 + 0xeec) = *(undefined4 *)(param_2 + 0xeec);
    *(undefined4 *)(param_1 + 0xef0) = *(undefined4 *)(param_2 + 0xef0);
    *(undefined4 *)(param_1 + 0xf00) = *(undefined4 *)(param_2 + 0xf00);
    *(undefined4 *)(param_1 + 0xf04) = *(undefined4 *)(param_2 + 0xf04);
    *(undefined4 *)(param_1 + 0xf08) = *(undefined4 *)(param_2 + 0xf08);
    *(undefined4 *)(param_1 + 0xf0c) = *(undefined4 *)(param_2 + 0xf0c);
    *(undefined4 *)(param_1 + 0xf10) = *(undefined4 *)(param_2 + 0xf10);
    *(undefined4 *)(param_1 + 0xf14) = *(undefined4 *)(param_2 + 0xf14);
    *(undefined4 *)(param_1 + 0xf18) = *(undefined4 *)(param_2 + 0xf18);
    *(undefined4 *)(param_1 + 0xf1c) = *(undefined4 *)(param_2 + 0xf1c);
    *(undefined1 *)(param_1 + 0xeb2) = *(undefined1 *)(param_2 + 0xeb2);
    *(undefined4 *)(param_1 + 0xe20) = *(undefined4 *)(param_2 + 0xe20);
    *(undefined4 *)(param_1 + 0xe24) = *(undefined4 *)(param_2 + 0xe24);
    *(undefined4 *)(param_1 + 0xe28) = *(undefined4 *)(param_2 + 0xe28);
    uVar13 = *(undefined8 *)(param_2 + 0xf40);
    *(undefined8 *)(param_1 + 0xf48) = *(undefined8 *)(param_2 + 0xf48);
    *(undefined8 *)(param_1 + 0xf40) = uVar13;
    uVar13 = *(undefined8 *)(param_2 + 0xf30);
    *(undefined8 *)(param_1 + 0xf38) = *(undefined8 *)(param_2 + 0xf38);
    *(undefined8 *)(param_1 + 0xf30) = uVar13;
    uVar13 = *(undefined8 *)(param_2 + 0xf20);
    *(undefined8 *)(param_1 + 0xf28) = *(undefined8 *)(param_2 + 0xf28);
    *(undefined8 *)(param_1 + 0xf20) = uVar13;
    uVar13 = *(undefined8 *)(param_2 + 0x130);
    *(undefined8 *)(param_1 + 0x138) = *(undefined8 *)(param_2 + 0x138);
    *(undefined8 *)(param_1 + 0x130) = uVar13;
    uVar13 = *(undefined8 *)(param_2 + 0x140);
    *(undefined8 *)(param_1 + 0x148) = *(undefined8 *)(param_2 + 0x148);
    *(undefined8 *)(param_1 + 0x140) = uVar13;
    uVar13 = *(undefined8 *)(param_2 + 0x150);
    *(undefined8 *)(param_1 + 0x158) = *(undefined8 *)(param_2 + 0x158);
    *(undefined8 *)(param_1 + 0x150) = uVar13;
    uVar13 = *(undefined8 *)(param_2 + 0x160);
    *(undefined8 *)(param_1 + 0x168) = *(undefined8 *)(param_2 + 0x168);
    *(undefined8 *)(param_1 + 0x160) = uVar13;
    memcpy(param_1 + 0x200,param_2 + 0x200,0x360);
    memcpy(param_1 + 0x560,param_2 + 0x560,0x360);
    *(undefined1 *)(param_1 + 0x948) = *(undefined1 *)(param_2 + 0x948);
    *(undefined8 *)(param_1 + 0x940) = *(undefined8 *)(param_2 + 0x940);
    cVar6 = *(char *)(param_2 + 0x949);
    *(char *)(param_1 + 0x949) = cVar6;
    if (cVar6 != '\0') {
      memcpy(param_1 + 0x8c0,param_2 + 0x8c0,0x80);
    }
    *(undefined4 *)(param_1 + 0x950) = *(undefined4 *)(param_2 + 0x950);
    *(undefined4 *)(param_1 + 0x954) = *(undefined4 *)(param_2 + 0x954);
    *(undefined4 *)(param_1 + 0x958) = *(undefined4 *)(param_2 + 0x958);
    *(undefined4 *)(param_1 + 0x95c) = *(undefined4 *)(param_2 + 0x95c);
    uVar13 = *(undefined8 *)(param_2 + 0x960);
    *(undefined8 *)(param_1 + 0x968) = *(undefined8 *)(param_2 + 0x968);
    *(undefined8 *)(param_1 + 0x960) = uVar13;
    uVar13 = *(undefined8 *)(param_2 + 0x970);
    *(undefined8 *)(param_1 + 0x978) = *(undefined8 *)(param_2 + 0x978);
    *(undefined8 *)(param_1 + 0x970) = uVar13;
    uVar13 = *(undefined8 *)(param_2 + 0x980);
    *(undefined8 *)(param_1 + 0x988) = *(undefined8 *)(param_2 + 0x988);
    *(undefined8 *)(param_1 + 0x980) = uVar13;
    uVar13 = *(undefined8 *)(param_2 + 0x990);
    *(undefined8 *)(param_1 + 0x998) = *(undefined8 *)(param_2 + 0x998);
    *(undefined8 *)(param_1 + 0x990) = uVar13;
    uVar13 = *(undefined8 *)(param_2 + 0x9a0);
    *(undefined8 *)(param_1 + 0x9a8) = *(undefined8 *)(param_2 + 0x9a8);
    *(undefined8 *)(param_1 + 0x9a0) = uVar13;
    uVar13 = *(undefined8 *)(param_2 + 0x9b0);
    *(undefined8 *)(param_1 + 0x9b8) = *(undefined8 *)(param_2 + 0x9b8);
    *(undefined8 *)(param_1 + 0x9b0) = uVar13;
    uVar13 = *(undefined8 *)(param_2 + 0x9c0);
    *(undefined8 *)(param_1 + 0x9c8) = *(undefined8 *)(param_2 + 0x9c8);
    *(undefined8 *)(param_1 + 0x9c0) = uVar13;
    uVar13 = *(undefined8 *)(param_2 + 0x9d0);
    *(undefined8 *)(param_1 + 0x9d8) = *(undefined8 *)(param_2 + 0x9d8);
    *(undefined8 *)(param_1 + 0x9d0) = uVar13;
    memcpy(param_1 + 0x9e0,param_2 + 0x9e0,0x280);
    plVar12 = *(long **)(param_1 + 0xe10);
    *(undefined4 *)(param_1 + 0xc60) = *(undefined4 *)(param_2 + 0xc60);
    *(undefined4 *)(param_1 + 0xc64) = *(undefined4 *)(param_2 + 0xc64);
    *(undefined4 *)(param_1 + 0xc68) = *(undefined4 *)(param_2 + 0xc68);
    *(undefined4 *)(param_1 + 0xc6c) = *(undefined4 *)(param_2 + 0xc6c);
    uVar13 = *(undefined8 *)(param_2 + 0xc90);
    *(undefined8 *)(param_1 + 0xc98) = *(undefined8 *)(param_2 + 0xc98);
    *(undefined8 *)(param_1 + 0xc90) = uVar13;
    uVar13 = *(undefined8 *)(param_2 + 0xca0);
    *(undefined8 *)(param_1 + 0xca8) = *(undefined8 *)(param_2 + 0xca8);
    *(undefined8 *)(param_1 + 0xca0) = uVar13;
    uVar13 = *(undefined8 *)(param_2 + 0xcb0);
    *(undefined8 *)(param_1 + 0xcb8) = *(undefined8 *)(param_2 + 0xcb8);
    *(undefined8 *)(param_1 + 0xcb0) = uVar13;
    uVar13 = *(undefined8 *)(param_2 + 0xcc0);
    *(undefined8 *)(param_1 + 0xcc8) = *(undefined8 *)(param_2 + 0xcc8);
    *(undefined8 *)(param_1 + 0xcc0) = uVar13;
    uVar13 = *(undefined8 *)(param_2 + 0xf50);
    *(undefined8 *)(param_1 + 0xf58) = *(undefined8 *)(param_2 + 0xf58);
    *(undefined8 *)(param_1 + 0xf50) = uVar13;
    uVar13 = *(undefined8 *)(param_2 + 0xf60);
    *(undefined8 *)(param_1 + 0xf68) = *(undefined8 *)(param_2 + 0xf68);
    *(undefined8 *)(param_1 + 0xf60) = uVar13;
    uVar13 = *(undefined8 *)(param_2 + 0xf70);
    *(undefined8 *)(param_1 + 0xf78) = *(undefined8 *)(param_2 + 0xf78);
    *(undefined8 *)(param_1 + 0xf70) = uVar13;
    uVar13 = *(undefined8 *)(param_2 + 0xf80);
    *(undefined8 *)(param_1 + 0xf88) = *(undefined8 *)(param_2 + 0xf88);
    *(undefined8 *)(param_1 + 0xf80) = uVar13;
    *(undefined4 *)(param_1 + 0xed0) = *(undefined4 *)(param_2 + 0xed0);
    *(undefined4 *)(param_1 + 0xde8) = *(undefined4 *)(param_2 + 0xde8);
    *(undefined4 *)(param_1 + 0xdf4) = *(undefined4 *)(param_2 + 0xdf4);
    *(undefined4 *)(param_1 + 0xdfc) = *(undefined4 *)(param_2 + 0xdfc);
    *(undefined4 *)(param_1 + 0xe08) = *(undefined4 *)(param_2 + 0xe08);
    *(undefined4 *)(param_1 + 0xd50) = *(undefined4 *)(param_2 + 0xd50);
    *(undefined4 *)(param_1 + 0xd54) = *(undefined4 *)(param_2 + 0xd54);
    *(undefined4 *)(param_1 + 0xd58) = *(undefined4 *)(param_2 + 0xd58);
    *(undefined4 *)(param_1 + 0xd5c) = *(undefined4 *)(param_2 + 0xd5c);
    *(undefined4 *)(param_1 + 0xed4) = *(undefined4 *)(param_2 + 0xed4);
    *(undefined4 *)(param_1 + 0xed8) = *(undefined4 *)(param_2 + 0xed8);
    *(undefined4 *)(param_1 + 0xe00) = *(undefined4 *)(param_2 + 0xe00);
    *(undefined4 *)(param_1 + 0xe04) = *(undefined4 *)(param_2 + 0xe04);
    *(undefined4 *)(param_1 + 0xdec) = *(undefined4 *)(param_2 + 0xdec);
    *(undefined4 *)(param_1 + 0xdf8) = *(undefined4 *)(param_2 + 0xdf8);
    *(undefined4 *)(param_1 + 0xedc) = *(undefined4 *)(param_2 + 0xedc);
    *(undefined4 *)(param_1 + 0xee0) = *(undefined4 *)(param_2 + 0xee0);
    *(undefined4 *)(param_1 + 0xee4) = *(undefined4 *)(param_2 + 0xee4);
    uVar13 = *(undefined8 *)(param_2 + 0xcd0);
    *(undefined8 *)(param_1 + 0xcd8) = *(undefined8 *)(param_2 + 0xcd8);
    *(undefined8 *)(param_1 + 0xcd0) = uVar13;
    uVar13 = *(undefined8 *)(param_2 + 0xce0);
    *(undefined8 *)(param_1 + 0xce8) = *(undefined8 *)(param_2 + 0xce8);
    *(undefined8 *)(param_1 + 0xce0) = uVar13;
    uVar13 = *(undefined8 *)(param_2 + 0xcf0);
    *(undefined8 *)(param_1 + 0xcf8) = *(undefined8 *)(param_2 + 0xcf8);
    *(undefined8 *)(param_1 + 0xcf0) = uVar13;
    uVar13 = *(undefined8 *)(param_2 + 0xd00);
    *(undefined8 *)(param_1 + 0xd08) = *(undefined8 *)(param_2 + 0xd08);
    *(undefined8 *)(param_1 + 0xd00) = uVar13;
    uVar13 = *(undefined8 *)(param_2 + 0xd10);
    *(undefined8 *)(param_1 + 0xd18) = *(undefined8 *)(param_2 + 0xd18);
    *(undefined8 *)(param_1 + 0xd10) = uVar13;
    uVar13 = *(undefined8 *)(param_2 + 0xd20);
    *(undefined8 *)(param_1 + 0xd28) = *(undefined8 *)(param_2 + 0xd28);
    *(undefined8 *)(param_1 + 0xd20) = uVar13;
    uVar13 = *(undefined8 *)(param_2 + 0xd30);
    *(undefined8 *)(param_1 + 0xd38) = *(undefined8 *)(param_2 + 0xd38);
    *(undefined8 *)(param_1 + 0xd30) = uVar13;
    uVar13 = *(undefined8 *)(param_2 + 0xd40);
    *(undefined8 *)(param_1 + 0xd48) = *(undefined8 *)(param_2 + 0xd48);
    *(undefined8 *)(param_1 + 0xd40) = uVar13;
    lVar14 = *(long *)(param_2 + 0xe10);
    if (plVar12 != (long *)0x0) {
      iVar9 = (int)plVar12[1] + -1;
      *(int *)(plVar12 + 1) = iVar9;
      if (iVar9 == 0) {
        (**(code **)(*plVar12 + 8))();
      }
      *(undefined8 *)(param_1 + 0xe10) = 0;
    }
    *(long *)(param_1 + 0xe10) = lVar14;
    if (lVar14 != 0) {
      *(int *)(lVar14 + 8) = *(int *)(lVar14 + 8) + 1;
    }
    puVar1 = (ushort *)(param_1 + 0xeb3);
    *puVar1 = *puVar1 | 2;
    lVar14 = *(long *)(param_2 + 0xe18);
    if (lVar14 != 0) {
      if (*(long *)(param_1 + 0xe18) != 0) {
        Aska::DeleteManager::AddMain(void*, unsigned char, unsigned char, Aska::IDeleteHandler*)(PTR__ZN4Aska6Global21m_systemDeleteManagerE_02cb77c0,
                        *(long *)(param_1 + 0xe18),7,0,0);
      }
      *(long *)(param_1 + 0xe18) = lVar14;
      *(int *)(lVar14 + 8) = *(int *)(lVar14 + 8) + 1;
    }
    uVar15 = *(undefined8 *)(param_2 + 0xd60);
    puVar2 = (ushort *)(param_2 + 0xeb3);
    uVar13 = 1;
    *(undefined8 *)(param_1 + 0xd68) = *(undefined8 *)(param_2 + 0xd68);
    *(undefined8 *)(param_1 + 0xd60) = uVar15;
    uVar15 = *(undefined8 *)(param_2 + 0xd70);
    *(undefined8 *)(param_1 + 0xd78) = *(undefined8 *)(param_2 + 0xd78);
    *(undefined8 *)(param_1 + 0xd70) = uVar15;
    uVar15 = *(undefined8 *)(param_2 + 0xd80);
    *(undefined8 *)(param_1 + 0xd88) = *(undefined8 *)(param_2 + 0xd88);
    *(undefined8 *)(param_1 + 0xd80) = uVar15;
    uVar15 = *(undefined8 *)(param_2 + 0xd90);
    *(undefined8 *)(param_1 + 0xd98) = *(undefined8 *)(param_2 + 0xd98);
    *(undefined8 *)(param_1 + 0xd90) = uVar15;
    uVar15 = *(undefined8 *)(param_2 + 0xda0);
    *(undefined8 *)(param_1 + 0xda8) = *(undefined8 *)(param_2 + 0xda8);
    *(undefined8 *)(param_1 + 0xda0) = uVar15;
    uVar15 = *(undefined8 *)(param_2 + 0xdb0);
    *(undefined8 *)(param_1 + 0xdb8) = *(undefined8 *)(param_2 + 0xdb8);
    *(undefined8 *)(param_1 + 0xdb0) = uVar15;
    uVar15 = *(undefined8 *)(param_2 + 0xdc0);
    *(undefined8 *)(param_1 + 0xdc8) = *(undefined8 *)(param_2 + 0xdc8);
    *(undefined8 *)(param_1 + 0xdc0) = uVar15;
    uVar15 = *(undefined8 *)(param_2 + 0xdd0);
    *(undefined8 *)(param_1 + 0xdd8) = *(undefined8 *)(param_2 + 0xdd8);
    *(undefined8 *)(param_1 + 0xdd0) = uVar15;
    *(undefined4 *)(param_1 + 0xde0) = *(undefined4 *)(param_2 + 0xde0);
    *(undefined8 *)(param_1 + 0xe30) = *(undefined8 *)(param_2 + 0xe30);
    *(undefined4 *)(param_1 + 0xe50) = *(undefined4 *)(param_2 + 0xe50);
    *(undefined4 *)(param_1 + 0xe54) = *(undefined4 *)(param_2 + 0xe54);
    *(undefined4 *)(param_1 + 0xe58) = *(undefined4 *)(param_2 + 0xe58);
    *(undefined4 *)(param_1 + 0xe5c) = *(undefined4 *)(param_2 + 0xe5c);
    *(undefined4 *)(param_1 + 0xe60) = *(undefined4 *)(param_2 + 0xe60);
    *(undefined4 *)(param_1 + 0xe64) = *(undefined4 *)(param_2 + 0xe64);
    *(undefined4 *)(param_1 + 0xe68) = *(undefined4 *)(param_2 + 0xe68);
    *(undefined1 *)(param_1 + 0xeac) = *(undefined1 *)(param_2 + 0xeac);
    *(undefined4 *)(param_1 + 0xe38) = *(undefined4 *)(param_2 + 0xe38);
    *(undefined4 *)(param_1 + 0xe3c) = *(undefined4 *)(param_2 + 0xe3c);
    *(undefined4 *)(param_1 + 0xe40) = *(undefined4 *)(param_2 + 0xe40);
    *(undefined1 *)(param_1 + 0xea8) = *(undefined1 *)(param_2 + 0xea8);
    *(undefined1 *)(param_1 + 0xea9) = *(undefined1 *)(param_2 + 0xea9);
    *(undefined1 *)(param_1 + 0xeaa) = *(undefined1 *)(param_2 + 0xeaa);
    *(undefined1 *)(param_1 + 0xeab) = *(undefined1 *)(param_2 + 0xeab);
    *(undefined4 *)(param_1 + 0xe44) = *(undefined4 *)(param_2 + 0xe44);
    *(undefined4 *)(param_1 + 0xe48) = *(undefined4 *)(param_2 + 0xe48);
    *(undefined4 *)(param_1 + 0xe4c) = *(undefined4 *)(param_2 + 0xe4c);
    *(undefined1 *)(param_1 + 0xead) = *(undefined1 *)(param_2 + 0xead);
    uVar7 = *puVar1;
    uVar3 = (*puVar2 >> 0xb & 1) << 0xb;
    uVar8 = uVar7 & 0x7ff | uVar3;
    *puVar1 = uVar7 & 0xf000 | uVar8;
    uVar4 = (*puVar2 >> 0xc & 1) << 0xc;
    uVar8 = uVar8 | uVar4;
    *puVar1 = uVar7 & 0xe000 | uVar8;
    uVar5 = (*puVar2 >> 0xd & 1) << 0xd;
    uVar10 = uVar7 & 0xc000;
    *puVar1 = uVar10 | uVar8 | uVar5;
    *(undefined1 *)(param_1 + 0xeae) = *(undefined1 *)(param_2 + 0xeae);
    *(undefined1 *)(param_1 + 0xeaf) = *(undefined1 *)(param_2 + 0xeaf);
    *(undefined1 *)(param_1 + 0xeb0) = *(undefined1 *)(param_2 + 0xeb0);
    *(undefined1 *)(param_1 + 0xeb1) = *(undefined1 *)(param_2 + 0xeb1);
    uVar8 = *puVar2;
    *puVar1 = uVar10 | uVar7 & 0x7fe | uVar3 | uVar4 | uVar5 | uVar8 & 1;
    uVar8 = uVar8 & 1 | (*puVar2 >> 1 & 1) << 1;
    *puVar1 = uVar10 | uVar7 & 0x7fc | uVar3 | uVar4 | uVar5 | uVar8;
    uVar8 = uVar8 | (*puVar2 >> 2 & 1) << 2;
    *puVar1 = uVar10 | uVar7 & 0x7f8 | uVar3 | uVar4 | uVar5 | uVar8;
    uVar8 = uVar7 & 8 | uVar8 | (*puVar2 >> 4 & 1) << 4;
    *puVar1 = uVar10 | uVar7 & 0x7e0 | uVar3 | uVar4 | uVar5 | uVar8;
    uVar8 = uVar8 | (*puVar2 >> 5 & 1) << 5;
    *puVar1 = uVar10 | uVar7 & 0x7c0 | uVar3 | uVar4 | uVar5 | uVar8;
    uVar8 = uVar8 | (*puVar2 >> 6 & 1) << 6;
    *puVar1 = uVar10 | uVar7 & 0x780 | uVar3 | uVar4 | uVar5 | uVar8;
    uVar8 = uVar8 | (*puVar2 >> 7 & 1) << 7;
    *puVar1 = uVar10 | uVar7 & 0x700 | uVar3 | uVar4 | uVar5 | uVar8;
    uVar8 = uVar8 | (*puVar2 >> 8 & 1) << 8;
    *puVar1 = uVar10 | uVar7 & 0x600 | uVar3 | uVar4 | uVar5 | uVar8;
    uVar8 = uVar8 | (*puVar2 >> 9 & 1) << 9;
    *puVar1 = uVar10 | uVar7 & 0x400 | uVar3 | uVar4 | uVar5 | uVar8;
    *puVar1 = uVar10 | uVar3 | uVar4 | uVar5 | uVar8 | *puVar2 & 0x400;
    *(undefined8 *)(param_1 + 0xeb8) = *(undefined8 *)(param_2 + 0xeb8);
    *(undefined8 *)(param_1 + 0xec0) = *(undefined8 *)(param_2 + 0xec0);
    *(undefined4 *)(param_1 + 0xec8) = *(undefined4 *)(param_2 + 0xec8);
    *(undefined4 *)(param_1 + 0xecc) = *(undefined4 *)(param_2 + 0xecc);
  }
  return uVar13;
}

// ==== Aska::Camera::CreateClone(Aska::IAnimatable const*)
// vaddr 0x20ec4bc | ghidra 0x21ec4bc | size 104 | symbol _ZN4Aska6Camera11CreateCloneEPKNS_11IAnimatableE | lib libSOA-3.7.0.so | 2026-10-04
long * _ZN4Aska6Camera11CreateCloneEPKNS_11IAnimatableE(undefined8 param_1,undefined8 param_2)

{
  long *plVar1;
  ulong uVar2;
  
  plVar1 = (long *)operator new(unsigned long, std::nothrow_t const&)(0xf90,PTR__ZSt7nothrow_02cb9a80);
  if (plVar1 != (long *)0x0) {
    Aska::Camera::Camera()(plVar1);
    uVar2 = (**(code **)(*plVar1 + 0x18))(plVar1,param_2);
    if ((uVar2 & 1) == 0) {
      (**(code **)(*plVar1 + 8))(plVar1);
      plVar1 = (long *)0x0;
    }
  }
  return plVar1;
}

// ==== Aska::Camera::ResetViewFrustum()
// vaddr 0x20ec524 | ghidra 0x21ec524 | size 12 | symbol _ZN4Aska6Camera16ResetViewFrustumEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6Camera16ResetViewFrustumEv(long param_1)

{
  *(undefined2 *)(param_1 + 0x948) = 0;
  *(undefined8 *)(param_1 + 0x940) = 0;
  return;
}

// ==== Aska::Camera::SetWorldMatrix(Aska::Matrix const*)
// vaddr 0x20ec530 | ghidra 0x21ec530 | size 92 | symbol _ZN4Aska6Camera14SetWorldMatrixEPKNS_6MatrixE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6Camera14SetWorldMatrixEPKNS_6MatrixE(long param_1,undefined8 *param_2)

{
  byte bVar1;
  undefined8 uVar2;
  
  *(ushort *)(param_1 + 0xeb3) = *(ushort *)(param_1 + 0xeb3) | 0x20;
  uVar2 = *param_2;
  bVar1 = *(byte *)(param_1 + 0x128);
  *(undefined8 *)(param_1 + 0x48) = param_2[1];
  *(undefined8 *)(param_1 + 0x40) = uVar2;
  uVar2 = param_2[2];
  *(undefined8 *)(param_1 + 0x58) = param_2[3];
  *(undefined8 *)(param_1 + 0x50) = uVar2;
  uVar2 = param_2[4];
  *(undefined8 *)(param_1 + 0x68) = param_2[5];
  *(undefined8 *)(param_1 + 0x60) = uVar2;
  uVar2 = param_2[6];
  *(undefined8 *)(param_1 + 0x78) = param_2[7];
  *(undefined8 *)(param_1 + 0x70) = uVar2;
  if ((bVar1 & 1) == 0) {
    Aska::HierarchicalObjectContainer::UpdateHierarchically()(param_1 + 0x30);
    bVar1 = *(byte *)(param_1 + 0x128);
  }
  *(byte *)(param_1 + 0x128) = bVar1 & 0xfe;
  return;
}

// ==== Aska::Camera::MakeMatrix()
// vaddr 0x20ec58c | ghidra 0x21ec58c | size 36 | symbol _ZN4Aska6Camera10MakeMatrixEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6Camera10MakeMatrixEv(long param_1)

{
  Aska::AimingObject::MakeMatrix()();
  *(ushort *)(param_1 + 0xeb3) = *(ushort *)(param_1 + 0xeb3) | 0x20;
  return;
}

// ==== Aska::Camera::PrepareScreenProjection()
// vaddr 0x20ec5b0 | ghidra 0x21ec5b0 | size 276 | symbol _ZN4Aska6Camera23PrepareScreenProjectionEv | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska6Camera23PrepareScreenProjectionEv(long param_1)

{
  undefined8 uVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  float fVar5;
  
  uVar4 = _UNK_027dbb38;
  uVar3 = _UNK_027dbb30;
  uVar2 = _UNK_027dbb28;
  uVar1 = _UNK_027dbb20;
  fVar5 = *(float *)(param_1 + 0xed4) * 0.5;
  *(undefined8 *)(param_1 + 0xcb8) = _UNK_027dbb28;
  *(undefined8 *)(param_1 + 0xcb0) = uVar1;
  *(undefined8 *)(param_1 + 0xcc8) = uVar4;
  *(undefined8 *)(param_1 + 0xcc0) = uVar3;
  *(ulong *)(param_1 + 0xc98) = (ulong)(uint)fVar5 << 0x20;
  *(ulong *)(param_1 + 0xc90) = (ulong)(uint)fVar5;
  *(ulong *)(param_1 + 0xca8) = (ulong)(uint)(*(float *)(param_1 + 0xed8) * 0.5) << 0x20;
  *(ulong *)(param_1 + 0xca0) = (ulong)(uint)(*(float *)(param_1 + 0xed8) * -0.5) << 0x20;
  Aska::Matrix::Mul(Aska::Matrix const*)(param_1 + 0xc90,param_1 + 0x960);
  Aska::Matrix::Mul(Aska::Matrix const*)(param_1 + 0xc90,param_1 + 0x130);
  *(undefined8 *)(param_1 + 0xd38) = uVar2;
  *(undefined8 *)(param_1 + 0xd30) = uVar1;
  fVar5 = *(float *)(param_1 + 0xee0) * 0.5;
  *(undefined8 *)(param_1 + 0xd48) = uVar4;
  *(undefined8 *)(param_1 + 0xd40) = uVar3;
  *(ulong *)(param_1 + 0xd18) = (ulong)(uint)fVar5 << 0x20;
  *(ulong *)(param_1 + 0xd10) = (ulong)(uint)fVar5;
  *(ulong *)(param_1 + 0xd28) = (ulong)(uint)(*(float *)(param_1 + 0xee4) * 0.5) << 0x20;
  *(ulong *)(param_1 + 0xd20) = (ulong)(uint)(*(float *)(param_1 + 0xee4) * -0.5) << 0x20;
  Aska::Matrix::Mul(Aska::Matrix const*)(param_1 + 0xd10,param_1 + 0xcd0);
  Aska::Matrix::Mul(Aska::Matrix const*)(param_1 + 0xd10,param_1 + 0x130);
  *(ushort *)(param_1 + 0xeb3) = *(ushort *)(param_1 + 0xeb3) | 0x10;
  return;
}

// ==== Aska::Camera::ProjectScreen(Aska::Vector*)
// vaddr 0x20ec6c4 | ghidra 0x21ec6c4 | size 56 | symbol _ZN4Aska6Camera13ProjectScreenEPNS_6VectorE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6Camera13ProjectScreenEPNS_6VectorE(long param_1,float *param_2)

{
  Aska::Vector::ApplyMatrix(Aska::Matrix const*)(param_2,param_1 + 0xc90);
  *param_2 = *param_2 * (1.0 / param_2[3]);
  param_2[1] = (1.0 / param_2[3]) * param_2[1];
  return;
}

// ==== Aska::Camera::ProjectFrontScreen(Aska::Vector*)
// vaddr 0x20ec6fc | ghidra 0x21ec6fc | size 56 | symbol _ZN4Aska6Camera18ProjectFrontScreenEPNS_6VectorE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6Camera18ProjectFrontScreenEPNS_6VectorE(long param_1,float *param_2)

{
  Aska::Vector::ApplyMatrix(Aska::Matrix const*)(param_2,param_1 + 0xd10);
  *param_2 = *param_2 * (1.0 / param_2[3]);
  param_2[1] = (1.0 / param_2[3]) * param_2[1];
  return;
}

// ==== Aska::Camera::SetViewMatrix(Aska::Matrix const*)
// vaddr 0x20ec734 | ghidra 0x21ec734 | size 316 | symbol _ZN4Aska6Camera13SetViewMatrixEPKNS_6MatrixE | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska6Camera13SetViewMatrixEPKNS_6MatrixE(long *param_1,undefined1 (*param_2) [12])

{
  long lVar1;
  long lVar2;
  long lVar3;
  long lVar4;
  undefined1 auVar5 [12];
  undefined1 auVar6 [12];
  byte bVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  long lVar12;
  float fVar13;
  long lVar14;
  float fVar15;
  long lVar16;
  undefined8 uStack_50;
  float fStack_48;
  float fStack_44;
  undefined8 uStack_40;
  float fStack_38;
  float fStack_34;
  undefined8 uStack_30;
  float fStack_28;
  float fStack_24;
  undefined8 uStack_20;
  undefined8 uStack_18;
  
  lVar2 = *(long *)(*param_2 + 8);
  fVar9 = (float)((ulong)lVar2 >> 0x20);
  lVar1 = *(long *)*param_2;
  auVar5 = *param_2;
  fVar8 = (float)((ulong)lVar1 >> 0x20);
  param_1[0x27] = lVar2;
  param_1[0x26] = lVar1;
  lVar4 = *(long *)param_2[2];
  fVar11 = (float)((ulong)lVar4 >> 0x20);
  lVar3 = *(long *)*(undefined1 (*) [12])(param_2[1] + 4);
  auVar6 = *(undefined1 (*) [12])(param_2[1] + 4);
  fVar10 = (float)((ulong)lVar3 >> 0x20);
  param_1[0x29] = lVar4;
  param_1[0x28] = lVar3;
  lVar14 = *(long *)(param_2[3] + 4);
  lVar12 = *(long *)(param_2[2] + 8);
  fVar15 = (float)((ulong)lVar14 >> 0x20);
  param_1[0x2b] = lVar14;
  param_1[0x2a] = lVar12;
  uStack_18 = _UNK_027dbb38;
  uStack_20 = _UNK_027dbb30;
  lVar16 = *(long *)param_2[4];
  fVar13 = (float)((ulong)lVar12 >> 0x20);
  param_1[0x2d] = *(long *)(param_2[4] + 8);
  param_1[0x2c] = lVar16;
  uStack_50 = CONCAT44((float)lVar3,(float)lVar1);
  uStack_40 = CONCAT44(fVar10,fVar8);
  uStack_30 = CONCAT44(auVar6._8_4_,auVar5._8_4_);
  _fStack_48 = CONCAT44(-(fVar9 * (float)lVar1 + fVar11 * (float)lVar3 + fVar15 * (float)lVar12),
                        (float)lVar12);
  _fStack_38 = CONCAT44(-(fVar9 * fVar8 + fVar11 * fVar10 + fVar15 * fVar13),fVar13);
  _fStack_28 = CONCAT44(-(fVar9 * (float)lVar2 + fVar11 * (float)lVar4 + fVar15 * (float)lVar14),
                        (float)lVar14);
  (**(code **)(*param_1 + 0xa0))(param_1,&uStack_50);
  if (param_1[0x36] == 0) {
    bVar7 = *(byte *)(param_1 + 0x25);
  }
  else {
    if (param_1[0x39] != 0) {
      *(long *)(param_1[0x39] + 0x10) = param_1[0x3a];
    }
    if ((long *)param_1[0x3a] != (long *)0x0) {
      *(long *)param_1[0x3a] = param_1[0x39];
      param_1[0x3a] = 0;
    }
    param_1[0x39] = 0;
    param_1[0x36] = 0;
    bVar7 = *(byte *)(param_1 + 0x25) & 0xe0 | 1;
    *(byte *)(param_1 + 0x25) = bVar7;
  }
  *(byte *)(param_1 + 0x25) = bVar7 & 0xfb;
  return;
}

// ==== Aska::Camera::SetViewObjectMatrix(Aska::Matrix const*)
// vaddr 0x20ec870 | ghidra 0x21ec870 | size 96 | symbol _ZN4Aska6Camera19SetViewObjectMatrixEPKNS_6MatrixE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6Camera19SetViewObjectMatrixEPKNS_6MatrixE(long *param_1)

{
  (**(code **)(*param_1 + 0xa0))();
  if (param_1[0x36] != 0) {
    if (param_1[0x39] != 0) {
      *(long *)(param_1[0x39] + 0x10) = param_1[0x3a];
    }
    if ((long *)param_1[0x3a] != (long *)0x0) {
      *(long *)param_1[0x3a] = param_1[0x39];
      param_1[0x3a] = 0;
    }
    param_1[0x39] = 0;
    param_1[0x36] = 0;
    *(byte *)(param_1 + 0x25) = *(byte *)(param_1 + 0x25) & 0xe0 | 1;
  }
  return;
}

// ==== Aska::Camera::GetFrameBufferDepth(float, float)
// vaddr 0x20ec8d0 | ghidra 0x21ec8d0 | size 440 | symbol _ZN4Aska6Camera19GetFrameBufferDepthEff | lib libSOA-3.7.0.so | 2026-10-04
undefined1  [16] _ZN4Aska6Camera19GetFrameBufferDepthEff(float param_1,float param_2,long param_3)

{
  float fVar1;
  float fVar2;
  float fVar3;
  undefined4 uVar4;
  ulong uVar5;
  long lVar6;
  undefined8 *puVar7;
  long lVar8;
  long lVar9;
  undefined8 uVar10;
  float fVar11;
  undefined1 auVar12 [16];
  undefined8 uVar13;
  undefined8 uVar14;
  
  uVar13 = 0xbf800000;
  uVar14 = 0;
  if (*(char *)(param_3 + 0xeae) == '\0') {
    uVar5 = Aska::RenderDeviceGL::IsSupported(Aska::GLExtension::E) const(*(undefined8 *)PTR__ZN4Aska12g_pRenderDevE_02cbb1a0,0xd);
    puVar7 = *(undefined8 **)
              (*(long *)(*(long *)PTR__ZN4Aska6Global16m_pObjectManagerE_02cc4688 + 0xb420) + 0x380)
    ;
    if ((uVar5 & 1) == 0) {
      if (puVar7 != (undefined8 *)0x0) {
        uVar10 = *puVar7;
        lVar9 = *(long *)PTR__ZN4Aska6Global17m_pTextureManagerE_02cc19f0;
        lVar6 = lVar9 + 0xb0;
        Aska::CriticalSection::Enter() const(lVar6);
        lVar9 = Aska::TextureManager::QueryTextureEx(unsigned long, bool)(lVar9,uVar10,1);
        Aska::CriticalSection::Leave() const(lVar6);
        if ((lVar9 != 0) && (*(int *)(lVar9 + 0x80) == 0xb12087)) {
          Aska::Texture::GetBody() const(lVar9);
          uVar4 = 0;
          goto code_r0x011edac0;
        }
        goto code_r0x021ec8f4;
      }
    }
    else if (puVar7 != (undefined8 *)0x0) {
      uVar10 = *puVar7;
      lVar9 = *(long *)PTR__ZN4Aska6Global17m_pTextureManagerE_02cc19f0;
      lVar6 = lVar9 + 0xb0;
      Aska::CriticalSection::Enter() const(lVar6);
      lVar9 = Aska::TextureManager::QueryTextureEx(unsigned long, bool)(lVar9,uVar10,1);
      Aska::CriticalSection::Leave() const(lVar6);
      if ((lVar9 != 0) && (*(int *)(lVar9 + 0x80) == 0x991ca1)) {
        lVar6 = Aska::Texture::GetBody() const(lVar9);
        lVar8 = *(long *)PTR__ZN4Aska6Global14m_pFrameBufferE_02cb8198;
        fVar11 = (float)NEON_ucvtf((uint)*(ushort *)(lVar8 + 0x18));
        fVar1 = (float)NEON_ucvtf((uint)*(ushort *)(lVar8 + 0x1a));
        fVar2 = (float)NEON_ucvtf((uint)*(ushort *)(lVar8 + 0x28));
        fVar3 = (float)NEON_ucvtf((uint)*(ushort *)(lVar8 + 0x2a));
        uVar4 = *(undefined4 *)
                 (lVar6 + (ulong)(*(int *)(lVar9 + 0x28) *
                                  (int)((param_2 / fVar1) * fVar3 + 0.0 + 0.5) & 0xfffffffc) +
                 (long)(int)((param_1 / fVar11) * fVar2 + 0.0 + 0.5) * 4);
code_r0x011edac0:
        auVar12 = (*(code *)PTR__ZN4Aska11PixelFormat10UnpackD24FEj_02caed50)(uVar4);
        return auVar12;
      }
      goto code_r0x021ec8f4;
    }
    uVar13 = 0;
    uVar14 = 0;
  }
code_r0x021ec8f4:
  auVar12._8_8_ = uVar14;
  auVar12._0_8_ = uVar13;
  return auVar12;
}

// ==== Aska::Camera::MeasureExposure(float*) const
// vaddr 0x20eca88 | ghidra 0x21eca88 | size 232 | symbol _ZNK4Aska6Camera15MeasureExposureEPf | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float _ZNK4Aska6Camera15MeasureExposureEPf(long param_1,float *param_2)

{
  int iVar1;
  long lVar2;
  long lVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  
  lVar2 = *(long *)PTR__ZN4Aska6Global16m_pObjectManagerE_02cc4688;
  if ((ulong)*(byte *)(param_1 + 0xeae) == 0) {
    lVar3 = 0xb418;
  }
  else {
    lVar3 = (ulong)*(byte *)(param_1 + 0xeae) - 1;
    if ((*(byte *)(lVar2 + lVar3 * 0x48 + 0x4632) >> 5 & 1) == 0) {
      return 0.0;
    }
    lVar2 = lVar2 + lVar3 * 0x48;
    lVar3 = 0x4618;
  }
  if (*(long *)(lVar2 + lVar3) == 0) {
    fVar4 = 0.0;
  }
  else {
    fVar4 = *(float *)(*(long *)(*(long *)(lVar2 + lVar3) + 0x470) + 0x344);
    fVar6 = *(float *)(param_1 + 0xe24);
    if (0.0 <= fVar6 + 6.0) {
      fVar6 = -6.0;
    }
    if (fVar4 - fVar6 < 0.0) {
      fVar4 = fVar6;
    }
    if (param_2 != (float *)0x0) {
      fVar6 = *(float *)(*(long *)(param_1 + 0xe10) + 0x44);
      fVar7 = *(float *)(*(long *)(param_1 + 0xe10) + 0x58);
      iVar1 = Aska::CameraFilterManager::GetISO()(*(undefined8 *)(param_1 + 0xe30));
      fVar5 = (float)logf((float)iVar1 / _UNK_027e5198);
      *param_2 = fVar4 - ((fVar6 - fVar7) + fVar5 * _UNK_029c8d40);
    }
  }
  return fVar4;
}

// ==== Aska::Camera::Run(int)
// vaddr 0x20ecb70 | ghidra 0x21ecb70 | size 1576 | symbol _ZN4Aska6Camera3RunEi | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska6Camera3RunEi(long param_1)

{
  uint uVar1;
  ushort uVar2;
  int iVar3;
  bool bVar4;
  undefined *puVar5;
  uint uVar6;
  ulong uVar7;
  long lVar8;
  long lVar9;
  long lVar10;
  long *plVar11;
  float fVar12;
  undefined8 uVar13;
  float fVar14;
  float fVar15;
  undefined4 uVar16;
  float fVar17;
  
  puVar5 = PTR__ZN4Aska6Global16m_pObjectManagerE_02cc4688;
  uVar7 = (ulong)*(byte *)(param_1 + 0xeae);
  lVar8 = *(long *)PTR__ZN4Aska6Global16m_pObjectManagerE_02cc4688;
  if (uVar7 == 0) {
    lVar10 = *(long *)(lVar8 + 0xb418);
joined_r0x021ecc14:
    if (lVar10 != 0) {
      if (*(byte *)(param_1 + 0xeae) == 0) {
        if (*(long *)(*(long *)PTR__ZN4Aska6Global16m_pCameraManagerE_02cb7d08 + 0xff0) == param_1)
        goto code_r0x021ecc34;
      }
      else {
        lVar8 = lVar8 + uVar7 * 0x48;
        lVar9 = lVar8 + 0x45a8;
        if ((*(byte *)(lVar8 + 0x45ea) & 4) == 0) {
          lVar9 = 0;
        }
        if ((*(long *)(lVar9 + 0x20) == param_1) && ((*(byte *)(lVar9 + 0x42) >> 2 & 1) != 0)) {
code_r0x021ecc34:
          if (*(float *)(lVar10 + 0x498) != *(float *)(param_1 + 0xe68)) {
            *(float *)(lVar10 + 0x498) = *(float *)(param_1 + 0xe68);
            Aska::PostProcessCombinerTBR::SetMeteringMode(int)(lVar10,*(undefined1 *)(lVar10 + 0x1ed4));
          }
          if (*(char *)(lVar10 + 0x1ed4) != *(char *)(param_1 + 0xead)) {
            Aska::PostProcessCombinerTBR::SetMeteringMode(int)(lVar10);
          }
        }
      }
      if (*(char *)(param_1 + 0xead) == '\0') {
        fVar12 = *(float *)(param_1 + 0xe20) + *(float *)(*(long *)(param_1 + 0xe10) + 0x58);
      }
      else {
        lVar8 = *(long *)puVar5;
        if ((ulong)*(byte *)(param_1 + 0xeae) == 0) {
          lVar10 = 0xb418;
        }
        else {
          lVar10 = (ulong)*(byte *)(param_1 + 0xeae) - 1;
          fVar12 = 0.0;
          if ((*(byte *)(lVar8 + lVar10 * 0x48 + 0x4632) >> 5 & 1) == 0) goto code_r0x021ecd18;
          lVar8 = lVar8 + lVar10 * 0x48;
          lVar10 = 0x4618;
        }
        if (*(long *)(lVar8 + lVar10) == 0) {
          fVar12 = 0.0;
        }
        else {
          fVar12 = *(float *)(*(long *)(*(long *)(lVar8 + lVar10) + 0x470) + 0x344);
          fVar15 = *(float *)(param_1 + 0xe24);
          if (0.0 <= fVar15 + 6.0) {
            fVar15 = -6.0;
          }
          if (fVar12 - fVar15 < 0.0) {
            fVar12 = fVar15;
          }
        }
      }
code_r0x021ecd18:
      if (fVar12 - *(float *)(param_1 + 0xe24) < 0.0) {
        fVar12 = *(float *)(param_1 + 0xe24);
      }
      if (*(char *)(param_1 + 0xeaa) == '\0') {
        fVar15 = *(float *)(param_1 + 0xe28);
        if (fVar12 - *(float *)(param_1 + 0xe28) < 0.0) {
          fVar15 = fVar12;
        }
        *(float *)(param_1 + 0xe48) = fVar15;
      }
      else {
        fVar15 = *(float *)(param_1 + 0xe48);
      }
      fVar12 = *(float *)(*(long *)(param_1 + 0xe10) + 0x48);
      if ((*(float *)(param_1 + 0xe50) < fVar12 - fVar15) ||
         (fVar12 - fVar15 < -*(float *)(param_1 + 0xe50))) {
        *(float *)(param_1 + 0xe60) = fVar15;
        if (fVar12 <= fVar15) {
          fVar15 = *(float *)(param_1 + 0xe5c);
        }
        else {
          fVar15 = -*(float *)(param_1 + 0xe58);
        }
        *(float *)(param_1 + 0xe54) = fVar15;
      }
      else {
        fVar15 = *(float *)(param_1 + 0xe54);
      }
      if (fVar15 != 0.0) {
        fVar17 = (float)(**(code **)**(undefined8 **)PTR__ZN4Aska6Global8m_pVSyncE_02cbd460)
                                  (*(undefined8 **)PTR__ZN4Aska6Global8m_pVSyncE_02cbd460,0);
        fVar14 = *(float *)(param_1 + 0xe60);
        fVar12 = fVar12 + fVar15 * fVar17;
        bVar4 = fVar14 < fVar12;
        if (*(float *)(param_1 + 0xe54) <= 0.0) {
          bVar4 = fVar14 != fVar12 && fVar14 >= fVar12;
        }
        fVar15 = fVar14;
        if (!bVar4) {
          fVar15 = fVar12;
        }
        if (fVar15 == fVar14) {
          *(undefined4 *)(param_1 + 0xe54) = 0;
        }
        lVar8 = *(long *)(param_1 + 0xe10);
        if (*(float *)(lVar8 + 0x48) != fVar15) {
          *(float *)(lVar8 + 0x48) = fVar15;
          *(byte *)(lVar8 + 0x68) = *(byte *)(lVar8 + 0x68) | 0x20;
        }
      }
      fVar12 = (float)Aska::CameraFilterManager::GetIsoExposureOffset()(*(undefined8 *)(param_1 + 0xe30));
      lVar8 = *(long *)(param_1 + 0xe10);
      if (*(float *)(lVar8 + 0x4c) != fVar12) {
        *(float *)(lVar8 + 0x4c) = fVar12;
        *(byte *)(lVar8 + 0x68) = *(byte *)(lVar8 + 0x68) | 0x20;
      }
    }
  }
  else if ((*(byte *)(lVar8 + (uVar7 - 1) * 0x48 + 0x4632) >> 5 & 1) != 0) {
    lVar10 = *(long *)(lVar8 + (uVar7 - 1) * 0x48 + 0x4618);
    goto joined_r0x021ecc14;
  }
  if ((*(long *)(param_1 + 0xe10) != 0) && (*(char *)(param_1 + 0xeac) != '\0')) {
    iVar3 = *(int *)(param_1 + 0xe40);
    lVar8 = *(long *)(param_1 + 0xe88);
    if (iVar3 < 0) {
      lVar10 = 0;
      lVar9 = lVar8;
    }
    else {
      lVar10 = (long)iVar3;
      if (lVar8 <= iVar3) {
        lVar10 = lVar8 + -1;
      }
      lVar9 = lVar10 + 1;
    }
    if (((*(char *)(param_1 + 0xea9) != '\0') && (*(char *)(param_1 + 0xeab) != '\0')) ||
       (*(char *)(param_1 + 0xeac) == '\x01')) {
      fVar12 = _UNK_027fa924;
      if (lVar10 < lVar9) {
        uVar13 = NEON_ucvtf((ulong)CONCAT24(*(undefined2 *)
                                             (*(long *)PTR__ZN4Aska6Global14m_pFrameBufferE_02cb8198
                                             + 0x1a),(uint)*(ushort *)
                                                            (*(long *)
                                                  PTR__ZN4Aska6Global14m_pFrameBufferE_02cb8198 +
                                                  0x18)),4);
        fVar15 = (float)uVar13 * 0.5;
        fVar17 = (float)((ulong)uVar13 >> 0x20) * 0.5;
        while( true ) {
          if ((-1 < lVar10) && (lVar10 < lVar8)) {
            uVar13 = *(undefined8 *)(*(long *)(param_1 + 0xe78) + lVar10 * 8);
          }
          fVar14 = fVar17 + fVar17 * (float)((ulong)uVar13 >> 0x20);
          uVar13 = CONCAT44(fVar14,fVar15 + fVar15 * (float)uVar13);
          fVar14 = (float)Aska::Camera::GetFrameBufferDepth(float, float)(uVar13,fVar14,param_1);
          fVar14 = *(float *)(param_1 + 0x98c) / (fVar14 - *(float *)(param_1 + 0x988));
          if (fVar14 < 0.0) {
            fVar14 = *(float *)(param_1 + 0xe04);
          }
          if (fVar14 - fVar12 < 0.0) {
            fVar12 = fVar14;
          }
          if (lVar9 + -1 == lVar10) break;
          lVar8 = *(long *)(param_1 + 0xe88);
          lVar10 = lVar10 + 1;
        }
      }
      *(float *)(param_1 + 0xe4c) = fVar12;
      *(undefined1 *)(param_1 + 0xeab) = 0;
    }
    lVar8 = *(long *)(param_1 + 0xe10);
    if (*(char *)(param_1 + 0xea8) == '\0') {
      fVar15 = *(float *)(lVar8 + 0x28);
      fVar12 = (*(float *)(param_1 + 0xe3c) * fVar15 * fVar15 * _UNK_0296bcf4) /
               *(float *)(lVar8 + 0x20);
      if (fVar12 + _UNK_02804664 < 0.0) {
        fVar12 = _UNK_027e6a14;
      }
      if (ABS(*(float *)(param_1 + 0xe4c) - fVar15) < fVar12) goto code_r0x021ed10c;
      *(undefined1 *)(param_1 + 0xea8) = 1;
      *(undefined4 *)(param_1 + 0xe44) = 0;
    }
    puVar5 = PTR__ZN4Aska6Global8m_pVSyncE_02cbd460;
    fVar12 = *(float *)(lVar8 + 0x28);
    fVar15 = (float)(**(code **)**(undefined8 **)PTR__ZN4Aska6Global8m_pVSyncE_02cbd460)
                              (*(undefined8 **)PTR__ZN4Aska6Global8m_pVSyncE_02cbd460,0);
    fVar15 = fVar15 * _UNK_027ebde0;
    if (*(float *)(param_1 + 0xe4c) <= fVar12) {
      if (fVar12 <= *(float *)(param_1 + 0xe4c)) {
        *(undefined1 *)(param_1 + 0xea8) = 0;
        *(undefined4 *)(param_1 + 0xe44) = 0;
      }
      else {
        fVar17 = *(float *)(param_1 + 0xe44);
        if (0.0 <= *(float *)(param_1 + 0xe44) + _UNK_027e6ae4) {
          fVar17 = _UNK_027f5450;
        }
        *(float *)(param_1 + 0xe44) = fVar17;
        uVar16 = NEON_ucvtf((uint)*(ushort *)(*(long *)puVar5 + 0xf0));
        fVar14 = (float)powf(_UNK_029c8d44,uVar16);
        fVar14 = fVar14 * *(float *)(param_1 + 0xe44);
        fVar17 = -*(float *)(param_1 + 0xe38);
        if (0.0 <= fVar14 + *(float *)(param_1 + 0xe38)) {
          fVar17 = fVar14;
        }
        *(float *)(param_1 + 0xe44) = fVar17;
        fVar15 = fVar12 + fVar15 * fVar17;
        fVar12 = *(float *)(param_1 + 0xe4c);
        if (0.0 <= fVar15 - *(float *)(param_1 + 0xe4c)) {
          fVar12 = fVar15;
        }
      }
    }
    else {
      fVar17 = _UNK_027e6ae4;
      if (0.0 <= *(float *)(param_1 + 0xe44) + _UNK_027f5450) {
        fVar17 = *(float *)(param_1 + 0xe44);
      }
      *(float *)(param_1 + 0xe44) = fVar17;
      uVar16 = NEON_ucvtf((uint)*(ushort *)(*(long *)puVar5 + 0xf0));
      fVar17 = (float)powf(_UNK_029c8d44,uVar16);
      fVar17 = fVar17 * *(float *)(param_1 + 0xe44);
      if (0.0 <= fVar17 - *(float *)(param_1 + 0xe38)) {
        fVar17 = *(float *)(param_1 + 0xe38);
      }
      *(float *)(param_1 + 0xe44) = fVar17;
      fVar12 = fVar12 + fVar15 * fVar17;
      if (0.0 <= fVar12 - *(float *)(param_1 + 0xe4c)) {
        fVar12 = *(float *)(param_1 + 0xe4c);
      }
    }
    Aska::Lens::SetFocusDepth(float)(fVar12,*(undefined8 *)(param_1 + 0xe10));
  }
code_r0x021ed10c:
  uVar2 = *(ushort *)(param_1 + 0xeb3);
  uVar6 = (uint)uVar2;
  if ((uVar2 >> 8 & 1) != 0) {
    uVar1 = *(uint *)(*(long *)(param_1 + 0xe18) + 0x420);
    uVar7 = (ulong)uVar1;
    if (0 < (int)uVar1) {
      plVar11 = (long *)(*(long *)(param_1 + 0xe18) + 0x340);
      do {
        if ((*(byte *)((long *)*plVar11 + 0x25) & 1) != 0) {
          (**(code **)(*(long *)*plVar11 + 0xa8))();
        }
        uVar7 = uVar7 - 1;
        plVar11 = plVar11 + 7;
      } while (uVar7 != 0);
      uVar6 = (uint)*(ushort *)(param_1 + 0xeb3);
    }
  }
  if (((uVar6 >> 3 & 1) != 0) && (*(char *)(param_1 + 0xeb2) == '\x02')) {
    (*(code *)PTR__ZN4Aska6Camera14ConvertFromOLSEv_02ca16f8)(param_1);
    return;
  }
  return;
}

// ==== Aska::Camera::Get(unsigned long, void*) const
// vaddr 0x20ed198 | ghidra 0x21ed198 | size 1776 | symbol _ZNK4Aska6Camera3GetEmPv | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 _ZNK4Aska6Camera3GetEmPv(long param_1,ulong param_2,float *param_3)

{
  byte bVar1;
  ulong uVar2;
  undefined8 uVar3;
  bool bVar4;
  float fVar5;
  uint uVar6;
  long lVar7;
  long lVar8;
  long *plVar9;
  float fVar10;
  double dVar11;
  float fVar12;
  
  uVar2 = Aska::AimingObject::Get(unsigned long, void*) const();
  if ((uVar2 & 1) != 0) goto code_r0x021ed1b8;
  bVar1 = *(byte *)(param_1 + 0xeae);
  uVar2 = (ulong)bVar1;
  lVar7 = *(long *)PTR__ZN4Aska6Global16m_pObjectManagerE_02cc4688;
  if (uVar2 == 0) {
    plVar9 = (long *)(lVar7 + 0xb418);
code_r0x021ed218:
    lVar8 = *plVar9;
  }
  else {
    if ((*(byte *)(lVar7 + (uVar2 - 1) * 0x48 + 0x4632) >> 5 & 1) != 0) {
      plVar9 = (long *)(lVar7 + (uVar2 - 1) * 0x48 + 0x4618);
      goto code_r0x021ed218;
    }
    lVar8 = 0;
  }
  if ((param_2 & 0xffff00000000) != 0) {
    return 0;
  }
  uVar3 = 0;
  switch((uint)param_2 & 0xffff) {
  case 0x10:
    fVar5 = *(float *)(param_1 + 0xde4);
    break;
  case 0x11:
    fVar5 = *(float *)(param_1 + 0xe04);
    break;
  case 0x12:
    fVar5 = *(float *)(param_1 + 0xe00);
    break;
  case 0x13:
    fVar5 = *(float *)(*(long *)(param_1 + 0xe10) + 0xc);
    break;
  case 0x14:
    fVar5 = *(float *)(*(long *)(param_1 + 0xe10) + 0x10);
    break;
  case 0x15:
    fVar5 = *(float *)(*(long *)(param_1 + 0xe10) + 0x14);
    break;
  case 0x16:
    dVar11 = *(double *)(param_1 + 0xec0);
    goto code_r0x021ed2a8;
  case 0x17:
    dVar11 = *(double *)(param_1 + 0xeb8);
code_r0x021ed2a8:
    *param_3 = (float)dVar11;
    goto code_r0x021ed1b8;
  case 0x18:
    fVar5 = *(float *)(param_1 + 0xee8);
    break;
  case 0x19:
    fVar5 = *(float *)(param_1 + 0xeec);
    break;
  case 0x1a:
    fVar5 = *(float *)(param_1 + 0xef0);
    break;
  case 0x1b:
    *param_3 = *(float *)(param_1 + 0xf00);
    param_3[1] = *(float *)(param_1 + 0xf04);
    param_3[2] = *(float *)(param_1 + 0xf08);
    param_3[3] = *(float *)(param_1 + 0xf0c);
    goto code_r0x021ed1b8;
  case 0x1c:
    fVar5 = (float)(uint)*(byte *)(param_1 + 0xeb2);
    break;
  case 0x1d:
    bVar4 = false;
    if (*(long *)PTR__ZN4Aska6Camera13m_pCrossFaderE_02cb7638 != 0) {
      bVar4 = 0.0 < *(float *)(*(long *)PTR__ZN4Aska6Camera13m_pCrossFaderE_02cb7638 + 0x760);
    }
    *(bool *)param_3 = bVar4;
    goto code_r0x021ed1b8;
  case 0x1e:
    fVar5 = *(float *)PTR__ZN4Aska6Camera15m_fCrossFadeSecE_02cb93a0;
    break;
  case 0x1f:
    fVar5 = *(float *)(*(long *)(param_1 + 0xe10) + 0x34);
    break;
  case 0x20:
    *param_3 = *(float *)(param_1 + 0xd50);
    param_3[1] = *(float *)(param_1 + 0xd54);
    param_3[2] = *(float *)(param_1 + 0xd58);
    param_3[3] = *(float *)(param_1 + 0xd5c);
    goto code_r0x021ed1b8;
  default:
    goto code_r0x021ed228;
  case 0x22:
    *(byte *)param_3 = (byte)((ushort)*(undefined2 *)(lVar7 + 0xb432) >> 9) & 1;
    goto code_r0x021ed1b8;
  case 0x23:
    bVar1 = (byte)((ushort)*(undefined2 *)(lVar7 + 0xb432) >> 8);
    goto code_r0x021ed5cc;
  case 0x24:
    *(byte *)param_3 = (byte)((ushort)*(undefined2 *)(param_1 + 0xeb3) >> 0xb) & 1;
    goto code_r0x021ed1b8;
  case 0x25:
    lVar7 = Aska::ObjectManager::GetPostProcessBloom()(lVar7);
    *param_3 = *(float *)(lVar7 + 0x340);
    goto code_r0x021ed1b8;
  case 0x2b:
    fVar5 = *(float *)(*(long *)(param_1 + 0xe30) + 0x5c);
    break;
  case 0x2c:
    fVar5 = *(float *)(*(long *)(param_1 + 0xe10) + 0x28);
    break;
  case 0x2d:
    uVar6 = (uint)*(byte *)(*(long *)(param_1 + 0xe10) + 0x68);
    goto code_r0x021ed728;
  case 0x2e:
    fVar5 = *(float *)(*(long *)(param_1 + 0xe10) + 0x2c);
    break;
  case 0x2f:
    lVar7 = *(long *)(param_1 + 0xe10);
    fVar5 = *(float *)(lVar7 + 0x40);
    fVar12 = *(float *)(lVar7 + 0x10);
    fVar10 = (float)tanf(*(float *)(lVar7 + 0xc) * 0.5);
    *param_3 = (fVar5 * 0.5 * fVar12) / fVar10;
    goto code_r0x021ed1b8;
  case 0x30:
    fVar5 = *(float *)(*(long *)(param_1 + 0xe10) + 0x40);
    break;
  case 0x31:
    fVar5 = *(float *)(*(long *)(param_1 + 0xe10) + 0x5c);
    break;
  case 0x32:
    fVar5 = *(float *)(*(long *)(param_1 + 0xe10) + 0x30);
    break;
  case 0x33:
    fVar5 = *(float *)(*(long *)(param_1 + 0xe10) + 0x44);
    break;
  case 0x34:
    if (*(char *)(param_1 + 0xead) == '\0') {
      fVar5 = *(float *)(param_1 + 0xe20) + *(float *)(*(long *)(param_1 + 0xe10) + 0x58);
    }
    else {
      if (bVar1 == 0) {
        lVar8 = 0xb418;
      }
      else {
        fVar5 = 0.0;
        if ((*(byte *)(lVar7 + (uVar2 - 1) * 0x48 + 0x4632) >> 5 & 1) == 0) goto code_r0x021ed860;
        lVar7 = lVar7 + (uVar2 - 1) * 0x48;
        lVar8 = 0x4618;
      }
      if (*(long *)(lVar7 + lVar8) == 0) {
        fVar5 = 0.0;
      }
      else {
        fVar5 = *(float *)(*(long *)(*(long *)(lVar7 + lVar8) + 0x470) + 0x344);
        fVar10 = *(float *)(param_1 + 0xe24);
        if (0.0 <= fVar10 + 6.0) {
          fVar10 = -6.0;
        }
        if (fVar5 - fVar10 < 0.0) {
          fVar5 = fVar10;
        }
      }
    }
code_r0x021ed860:
    if (fVar5 - *(float *)(param_1 + 0xe24) < 0.0) {
      fVar5 = *(float *)(param_1 + 0xe24);
    }
    fVar10 = *(float *)(param_1 + 0xe28);
    if (fVar5 - *(float *)(param_1 + 0xe28) < 0.0) {
      fVar10 = fVar5;
    }
    *param_3 = fVar10;
    goto code_r0x021ed1b8;
  case 0x36:
    fVar5 = (float)Aska::ObjectManager::GetPostProcessDitherRate() const(lVar7);
    *param_3 = fVar5;
    goto code_r0x021ed1b8;
  case 0x37:
    fVar5 = *(float *)(*(long *)(param_1 + 0xe10) + 0x3c);
    break;
  case 0x38:
    fVar5 = (float)(uint)*(byte *)(*(long *)(param_1 + 0xe10) + 0x66);
    break;
  case 0x39:
    fVar5 = *(float *)(*(long *)(param_1 + 0xe10) + 0x18);
    break;
  case 0x3a:
    if (lVar8 == 0) {
      fVar5 = 0.0;
    }
    else {
      fVar5 = (float)(uint)*(byte *)(lVar8 + 0x1ed4);
    }
    break;
  case 0x3c:
    fVar5 = *(float *)(param_1 + 0xe50);
    break;
  case 0x3d:
    fVar5 = *(float *)(param_1 + 0xe58);
    break;
  case 0x3e:
    fVar5 = *(float *)(param_1 + 0xe5c);
    break;
  case 0x3f:
    if (lVar8 == 0) {
code_r0x021ed7b4:
      *param_3 = 0.0;
    }
    else {
      *param_3 = *(float *)(lVar8 + 0x498);
    }
    goto code_r0x021ed1b8;
  case 0x41:
    if (lVar8 == 0) goto code_r0x021ed7b4;
    fVar5 = (float)((uint)(param_2 >> 0x10) & 0xffff);
    fVar5 = (fVar5 + fVar5) / _UNK_0293ed6c + -1.0;
    fVar12 = -1.625 / (*(float *)(lVar8 + 0x498) * *(float *)(lVar8 + 0x498));
    fVar5 = (float)expf(fVar5 * fVar5 * fVar12,0);
    fVar12 = fVar12 / _UNK_027edb30;
    fVar10 = SQRT(fVar12);
    if (NAN(fVar10)) {
      fVar10 = (float)sqrtf(fVar12);
    }
    *param_3 = fVar5 * fVar10;
    goto code_r0x021ed1b8;
  case 0x42:
    fVar12 = -1.625 / (*(float *)(lVar8 + 0x498) * *(float *)(lVar8 + 0x498));
    fVar10 = (float)expf(fVar12 * 0.0,0);
    fVar12 = fVar12 / _UNK_027edb30;
    fVar5 = SQRT(fVar12);
    if (NAN(fVar5)) {
      fVar5 = (float)sqrtf(fVar12);
    }
    fVar10 = fVar10 * fVar5;
    if (fVar10 + -1.0 < 0.0) {
      fVar10 = 1.0;
    }
    param_3[1] = 0.0;
    *param_3 = fVar10;
    goto code_r0x021ed1b8;
  case 0x43:
    *(byte *)param_3 = *(byte *)(*(long *)(param_1 + 0xe10) + 0x68) >> 6 & 1;
    goto code_r0x021ed1b8;
  case 0x44:
    bVar1 = (byte)((ushort)*(undefined2 *)(param_1 + 0xeb3) >> 8);
code_r0x021ed5cc:
    *(byte *)param_3 = bVar1 >> 4 & 1;
    goto code_r0x021ed1b8;
  case 0x45:
    *(byte *)param_3 = (byte)((ushort)*(undefined2 *)(param_1 + 0xeb3) >> 0xd) & 1;
    goto code_r0x021ed1b8;
  case 0x46:
    fVar5 = *(float *)(param_1 + 0xe64);
    break;
  case 0x47:
    fVar5 = (float)Aska::CameraFilterManager::GetISO()(*(undefined8 *)(param_1 + 0xe30));
    *param_3 = fVar5;
    goto code_r0x021ed1b8;
  case 0x48:
    fVar5 = (float)(uint)*(byte *)(param_1 + 0xeac);
    break;
  case 0x49:
    fVar5 = *(float *)(param_1 + 0xe38);
    break;
  case 0x4a:
    fVar5 = *(float *)(param_1 + 0xe3c);
    break;
  case 0x4b:
    fVar5 = *(float *)(param_1 + 0xe40);
    break;
  case 0x4d:
    *(byte *)param_3 = *(byte *)(*(long *)(param_1 + 0xe10) + 0x68) >> 4 & 1;
    goto code_r0x021ed1b8;
  case 0x4e:
    fVar5 = *(float *)(*(long *)(param_1 + 0xe10) + 0x50);
    break;
  case 0x4f:
    fVar5 = *(float *)(*(long *)(param_1 + 0xe10) + 0x24);
    break;
  case 0x50:
    fVar5 = (float)(uint)(byte)PTR__ZN4Aska13LensStructure11m_parameterE_02cbc6a0
                               [(long)*(int *)(*(long *)(param_1 + 0xe10) + 0x18) * 0x118 + 0x40];
    break;
  case 0x51:
    fVar5 = *(float *)(*(long *)(param_1 + 0xe10) + 0x20);
    break;
  case 0x52:
    fVar5 = *(float *)(*(long *)(param_1 + 0xe10) + 0x54);
    break;
  case 0x53:
    fVar5 = (float)(uint)*(ushort *)(*(long *)(param_1 + 0xe10) + 100);
    break;
  case 0x55:
    *(byte *)param_3 = (byte)(*(ushort *)(param_1 + 0xeb3) >> 7) & 1;
    goto code_r0x021ed1b8;
  case 0x56:
    *(byte *)param_3 = *(byte *)(param_1 + 0xeb4) & 1;
    goto code_r0x021ed1b8;
  case 0x58:
    if (((*(byte *)(param_1 + 0xeb4) >> 4 & 1) == 0) ||
       ((*(byte *)(*(long *)(param_1 + 0xe18) + 0x2c0) >> 2 & 1) == 0)) {
      *(byte *)param_3 = 0;
    }
    else {
      *(byte *)param_3 = 1;
    }
    goto code_r0x021ed1b8;
  case 0x5a:
    fVar5 = *(float *)(*(long *)(param_1 + 0xe10) + 0x60);
    break;
  case 0x5b:
    *(byte *)param_3 = *(byte *)(*(long *)(param_1 + 0xe10) + 0x68) >> 2 & 1;
    goto code_r0x021ed1b8;
  case 0x5c:
    *param_3 = *(float *)(param_1 + 0xf10);
    param_3[1] = *(float *)(param_1 + 0xf14);
    param_3[2] = *(float *)(param_1 + 0xf18);
    param_3[3] = *(float *)(param_1 + 0xf1c);
    goto code_r0x021ed1b8;
  case 0x5e:
    uVar6 = (uint)*(ushort *)(param_1 + 0xeb3);
code_r0x021ed728:
    *(byte *)param_3 = (byte)(uVar6 >> 3) & 1;
    goto code_r0x021ed1b8;
  case 0x5f:
    fVar5 = *(float *)(param_1 + 0xe20);
    break;
  case 0x60:
    if (bVar1 == 0) {
      lVar8 = 0xb418;
    }
    else {
      if ((*(byte *)(lVar7 + (uVar2 - 1) * 0x48 + 0x4632) >> 5 & 1) == 0) {
        return 0;
      }
      lVar7 = lVar7 + (uVar2 - 1) * 0x48;
      lVar8 = 0x4618;
    }
    if (*(long *)(lVar7 + lVar8) == 0) {
      return 0;
    }
    fVar5 = *(float *)(*(long *)(lVar7 + lVar8) + 0x330);
    break;
  case 0x61:
    if (bVar1 == 0) {
      lVar8 = 0xb418;
    }
    else {
      if ((*(byte *)(lVar7 + (uVar2 - 1) * 0x48 + 0x4632) >> 5 & 1) == 0) {
        return 0;
      }
      lVar7 = lVar7 + (uVar2 - 1) * 0x48;
      lVar8 = 0x4618;
    }
    if (*(long *)(lVar7 + lVar8) == 0) {
      return 0;
    }
    fVar5 = *(float *)(*(long *)(lVar7 + lVar8) + 0x334);
    break;
  case 0x62:
    fVar5 = *(float *)(param_1 + 0xe24);
    break;
  case 99:
    fVar5 = *(float *)(param_1 + 0xe28);
    break;
  case 100:
    *(byte *)param_3 = 0;
    goto code_r0x021ed1b8;
  case 0x69:
    *param_3 = 0.0;
    goto code_r0x021ed1b8;
  }
  *param_3 = fVar5;
code_r0x021ed1b8:
  uVar3 = 1;
code_r0x021ed228:
  return uVar3;
}

// ==== Aska::Camera::Set(unsigned long, void const*)
// vaddr 0x20ed888 | ghidra 0x21ed888 | size 2668 | symbol _ZN4Aska6Camera3SetEmPKv | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 _ZN4Aska6Camera3SetEmPKv(long param_1,ulong param_2,float *param_3)

{
  ushort uVar1;
  undefined *puVar2;
  bool bVar3;
  uint uVar4;
  ulong uVar5;
  undefined8 uVar6;
  long *plVar7;
  byte bVar8;
  long lVar9;
  byte bVar10;
  long lVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  
  uVar5 = Aska::AimingObject::Set(unsigned long, void const*)();
  puVar2 = PTR__ZN4Aska6Camera13m_pCrossFaderE_02cb7638;
  if ((uVar5 & 1) != 0) goto code_r0x021ed8ac;
  bVar10 = *(byte *)(param_1 + 0xeae);
  uVar5 = (ulong)bVar10;
  lVar9 = *(long *)PTR__ZN4Aska6Global16m_pObjectManagerE_02cc4688;
  if (uVar5 == 0) {
    plVar7 = (long *)(lVar9 + 0xb418);
code_r0x021ed90c:
    lVar11 = *plVar7;
  }
  else {
    if ((*(byte *)(lVar9 + (uVar5 - 1) * 0x48 + 0x4632) >> 5 & 1) != 0) {
      plVar7 = (long *)(lVar9 + (uVar5 - 1) * 0x48 + 0x4618);
      goto code_r0x021ed90c;
    }
    lVar11 = 0;
  }
  if ((param_2 & 0xffff00000000) != 0) {
    return 0;
  }
  uVar6 = 0;
  switch((uint)param_2 & 0xffff) {
  case 0x10:
    fVar12 = *param_3;
    *(ushort *)(param_1 + 0xeb3) = *(ushort *)(param_1 + 0xeb3) | 2;
    *(float *)(param_1 + 0xde4) = fVar12;
    break;
  case 0x11:
    fVar12 = *param_3;
    *(ushort *)(param_1 + 0xeb3) = *(ushort *)(param_1 + 0xeb3) | 2;
    *(float *)(param_1 + 0xe04) = fVar12;
    break;
  case 0x12:
    fVar12 = *param_3;
    *(ushort *)(param_1 + 0xeb3) = *(ushort *)(param_1 + 0xeb3) | 2;
    *(float *)(param_1 + 0xe00) = fVar12;
    break;
  case 0x13:
    if (*(long *)(param_1 + 0xe10) != 0) {
      Aska::Lens::SetBaseView(float)(*param_3);
    }
    break;
  case 0x14:
    if (*(long *)(param_1 + 0xe10) != 0) {
      Aska::Lens::SetZoom(float)(*param_3);
    }
    break;
  case 0x15:
    lVar9 = *(long *)(param_1 + 0xe10);
    if (lVar9 != 0) {
      *(float *)(lVar9 + 0x14) = *param_3;
      *(int *)(lVar9 + 0x6c) = *(int *)(lVar9 + 0x6c) + 1;
    }
    break;
  case 0x16:
    fVar15 = *param_3;
    fVar12 = (float)*(double *)(param_1 + 0xeb8);
    *(ushort *)(param_1 + 0xeb3) = *(ushort *)(param_1 + 0xeb3) | 2;
    *(double *)(param_1 + 0xec0) = (double)fVar15;
    goto code_r0x021eda40;
  case 0x17:
    fVar12 = *param_3;
    fVar15 = (float)*(double *)(param_1 + 0xec0);
    *(ushort *)(param_1 + 0xeb3) = *(ushort *)(param_1 + 0xeb3) | 2;
    *(double *)(param_1 + 0xeb8) = (double)fVar12;
code_r0x021eda40:
    *(float *)(param_1 + 0xec8) = fVar15;
    *(float *)(param_1 + 0xecc) = fVar12;
    break;
  case 0x18:
    *(float *)(param_1 + 0xee8) = *param_3;
    goto code_r0x021ee124;
  case 0x19:
    *(float *)(param_1 + 0xeec) = *param_3;
    goto code_r0x021ee124;
  case 0x1a:
    *(float *)(param_1 + 0xef0) = *param_3;
    goto code_r0x021ee124;
  case 0x1b:
    *(float *)(param_1 + 0xf00) = *param_3;
    *(float *)(param_1 + 0xf04) = param_3[1];
    *(float *)(param_1 + 0xf08) = param_3[2];
    *(float *)(param_1 + 0xf0c) = param_3[3];
    goto code_r0x021ee124;
  case 0x1c:
    *(char *)(param_1 + 0xeb2) = SUB41(*param_3,0);
    goto code_r0x021ee124;
  case 0x1d:
    if (*(byte *)param_3 == 0) {
      if (*(long *)PTR__ZN4Aska6Camera13m_pCrossFaderE_02cb7638 != 0) {
        Aska::Task::Remove()();
        plVar7 = *(long **)puVar2;
        (**(code **)(*plVar7 + 0x38))(plVar7,0);
        *(undefined8 *)puVar2 = 0;
      }
    }
    else {
      Aska::Camera::CrossFade()();
    }
    break;
  case 0x1e:
    *(float *)PTR__ZN4Aska6Camera15m_fCrossFadeSecE_02cb93a0 = *param_3;
    break;
  case 0x1f:
    lVar9 = *(long *)(param_1 + 0xe10);
    fVar12 = *param_3;
    if (*(float *)(lVar9 + 0x34) != fVar12) {
      *(float *)(lVar9 + 0x34) = fVar12;
      *(float *)(lVar9 + 0x38) = fVar12;
      *(byte *)(lVar9 + 0x68) = *(byte *)(lVar9 + 0x68) | 0x20;
      goto code_r0x021eddcc;
    }
    goto code_r0x021eddd0;
  case 0x20:
    if ((*(float *)(param_1 + 0xd50) != *param_3) || (*(float *)(param_1 + 0xd54) != param_3[1])) {
      *(ushort *)(param_1 + 0xeb3) = *(ushort *)(param_1 + 0xeb3) | 2;
      *(float *)(param_1 + 0xd50) = *param_3;
      *(float *)(param_1 + 0xd54) = param_3[1];
      *(float *)(param_1 + 0xd58) = param_3[2];
      *(float *)(param_1 + 0xd5c) = param_3[3];
    }
    break;
  default:
    goto code_r0x021ed91c;
  case 0x22:
    *(ushort *)(lVar9 + 0xb432) =
         *(ushort *)(lVar9 + 0xb432) & 0xfdff | (ushort)*(byte *)param_3 << 9;
    break;
  case 0x23:
    *(ushort *)(lVar9 + 0xb432) =
         *(ushort *)(lVar9 + 0xb432) & 0xefff | (ushort)*(byte *)param_3 << 0xc;
    break;
  case 0x24:
    uVar1 = *(ushort *)(param_1 + 0xeb3);
    if ((uVar1 >> 0xb & 1) != (ushort)*(byte *)param_3) {
      *(ushort *)(param_1 + 0xeb3) = uVar1 & 0xf7ff | (ushort)*(byte *)param_3 << 0xb;
    }
    break;
  case 0x2b:
    lVar9 = *(long *)(param_1 + 0xe30);
    if (*(float *)(lVar9 + 0x5c) != *param_3) {
      *(float *)(lVar9 + 0x5c) = *param_3;
      *(int *)(lVar9 + 0x58) = *(int *)(lVar9 + 0x58) + 1;
    }
    break;
  case 0x2c:
    Aska::Lens::SetFocusDepth(float)(*param_3,*(undefined8 *)(param_1 + 0xe10));
    break;
  case 0x2d:
    *(byte *)(*(long *)(param_1 + 0xe10) + 0x68) =
         *(byte *)(*(long *)(param_1 + 0xe10) + 0x68) & 0xf7 | *(byte *)param_3 << 3;
    break;
  case 0x2e:
    lVar9 = *(long *)(param_1 + 0xe10);
    fVar14 = *param_3;
    fVar15 = (float)Aska::LensStructure::GetMaxFStop() const(lVar9 + 0x18);
    fVar13 = (float)Aska::LensStructure::GetMinFStop() const(lVar9 + 0x18);
    fVar12 = fVar14;
    if (fVar14 - fVar13 < 0.0) {
      fVar12 = fVar13;
    }
    if (fVar12 - fVar15 < 0.0) {
      fVar15 = fVar12;
    }
    bVar10 = *(byte *)(lVar9 + 0x68) | 2;
    if (fVar15 == fVar14) {
      bVar10 = *(byte *)(lVar9 + 0x68) & 0xfd;
    }
    *(byte *)(lVar9 + 0x68) = bVar10;
    if (*(float *)(lVar9 + 0x2c) != fVar15) {
      *(byte *)(lVar9 + 0x68) = bVar10 | 0x20;
      *(float *)(lVar9 + 0x2c) = fVar15;
      *(int *)(lVar9 + 0x6c) = *(int *)(lVar9 + 0x6c) + 1;
    }
    goto code_r0x021eddcc;
  case 0x2f:
    lVar9 = *(long *)(param_1 + 0xe10);
    fVar13 = (*(float *)(lVar9 + 0x40) * 0.5 * *(float *)(lVar9 + 0x10)) / *param_3;
code_r0x021edcb4:
    fVar12 = (float)atanf(fVar13);
    Aska::Lens::SetBaseView(float)(fVar12 + fVar12,lVar9);
    break;
  case 0x30:
    lVar9 = *(long *)(param_1 + 0xe10);
    fVar15 = *param_3;
    fVar12 = *(float *)(lVar9 + 0x40);
    if (fVar12 != fVar15) {
      *(int *)(lVar9 + 0x6c) = *(int *)(lVar9 + 0x6c) + 1;
      fVar13 = (float)tanf(*(float *)(lVar9 + 0xc) * 0.5);
      fVar13 = (fVar15 / fVar12) * fVar13;
      *(float *)(lVar9 + 0x40) = fVar15;
      goto code_r0x021edcb4;
    }
    break;
  case 0x31:
    *(float *)(*(long *)(param_1 + 0xe10) + 0x5c) = *param_3;
    break;
  case 0x32:
    lVar9 = *(long *)(param_1 + 0xe10);
    fVar15 = *param_3;
    uVar4 = (**(code **)(**(long **)PTR__ZN4Aska6Global8m_pVSyncE_02cbd460 + 0x10))();
    fVar12 = 1.0 / (float)uVar4;
    if (fVar15 - 1.0 / (float)uVar4 < 0.0) {
      fVar12 = fVar15;
    }
    if (fVar12 + _UNK_027ed8d4 < 0.0) {
      fVar12 = _UNK_027ed8d8;
    }
    fVar13 = *(float *)(lVar9 + 0x30);
    bVar10 = *(byte *)(lVar9 + 0x68) & 0xfe;
    bVar8 = *(byte *)(lVar9 + 0x68) | 1;
    bVar3 = fVar12 == fVar15;
    goto code_r0x021eddb0;
  case 0x35:
    lVar9 = *(long *)(param_1 + 0xe10);
    fVar15 = 1.0 / *param_3;
    uVar4 = (**(code **)(**(long **)PTR__ZN4Aska6Global8m_pVSyncE_02cbd460 + 0x10))();
    fVar12 = 1.0 / (float)uVar4;
    if (fVar15 - 1.0 / (float)uVar4 < 0.0) {
      fVar12 = fVar15;
    }
    fVar13 = *(float *)(lVar9 + 0x30);
    if (fVar12 + _UNK_027ed8d4 < 0.0) {
      fVar12 = _UNK_027ed8d8;
    }
    bVar10 = *(byte *)(lVar9 + 0x68) & 0xfe;
    bVar8 = *(byte *)(lVar9 + 0x68) | 1;
    bVar3 = false;
    if (!NAN(fVar12) && !NAN(fVar15)) {
      bVar3 = fVar12 == fVar15;
    }
code_r0x021eddb0:
    if (bVar3) {
      bVar8 = bVar10;
    }
    *(byte *)(lVar9 + 0x68) = bVar8;
    if (fVar13 != fVar12) {
      *(float *)(lVar9 + 0x30) = fVar12;
      *(byte *)(lVar9 + 0x68) = bVar8 | 0x20;
    }
code_r0x021eddcc:
    lVar9 = *(long *)(param_1 + 0xe10);
code_r0x021eddd0:
    Aska::Lens::CalcExposureControl()(lVar9);
    break;
  case 0x36:
    Aska::ObjectManager::SetPostProcessDitherRate(float)(*param_3,lVar9);
    break;
  case 0x37:
    lVar9 = *(long *)(param_1 + 0xe10);
    fVar13 = *(float *)(lVar9 + 0x40);
    fVar14 = *(float *)(lVar9 + 0x10);
    fVar15 = *(float *)(lVar9 + 0x2c);
    fVar16 = *(float *)(lVar9 + 0x24);
    *(float *)(lVar9 + 0x3c) = *param_3;
    fVar12 = (float)tanf(*(float *)(lVar9 + 0xc) * 0.5);
    fVar15 = fVar15 * (fVar16 / ((fVar13 * 0.5 * fVar14) / fVar12));
    fVar12 = (float)logf(fVar15 * fVar15);
    fVar15 = (float)logf(*(undefined4 *)(lVar9 + 0x30));
    *(float *)(lVar9 + 0x44) =
         ((fVar12 - fVar15) * _UNK_02807c00 - *(float *)(lVar9 + 0x3c)) - *(float *)(lVar9 + 0x58);
    break;
  case 0x38:
    lVar9 = *(long *)(param_1 + 0xe10);
    if (*param_3 != (float)(uint)*(byte *)(lVar9 + 0x66)) {
      *(char *)(lVar9 + 0x66) = SUB41(*param_3,0);
      *(byte *)(lVar9 + 0x68) = *(byte *)(lVar9 + 0x68) | 0x20;
    }
    break;
  case 0x39:
    Aska::Lens::SetLensStructureID(int)(*(undefined8 *)(param_1 + 0xe10),*param_3);
    break;
  case 0x3a:
  case 100:
  case 0x69:
    break;
  case 0x3c:
    *(float *)(param_1 + 0xe50) = *param_3;
    break;
  case 0x3d:
    *(float *)(param_1 + 0xe58) = *param_3;
    break;
  case 0x3e:
    *(float *)(param_1 + 0xe5c) = *param_3;
    break;
  case 0x3f:
    if ((lVar11 != 0) && (*(float *)(lVar11 + 0x498) != *param_3)) {
      *(float *)(lVar11 + 0x498) = *param_3;
      Aska::PostProcessCombinerTBR::SetMeteringMode(int)(lVar11,*(undefined1 *)(lVar11 + 0x1ed4));
    }
    break;
  case 0x43:
    *(byte *)(*(long *)(param_1 + 0xe10) + 0x68) =
         *(byte *)(*(long *)(param_1 + 0xe10) + 0x68) & 0xbf | *(byte *)param_3 << 6;
    break;
  case 0x44:
    uVar1 = *(ushort *)(param_1 + 0xeb3);
    if ((uVar1 >> 0xc & 1) != (ushort)*(byte *)param_3) {
      *(ushort *)(param_1 + 0xeb3) = uVar1 & 0xefff | (ushort)*(byte *)param_3 << 0xc;
      *(undefined4 *)(param_1 + 0xde0) = 0;
code_r0x021ee0b4:
      *(undefined8 *)(param_1 + 0xd68) = *(undefined8 *)(param_1 + 0x138);
      *(undefined8 *)(param_1 + 0xd60) = *(undefined8 *)(param_1 + 0x130);
      *(undefined8 *)(param_1 + 0xd78) = *(undefined8 *)(param_1 + 0x148);
      *(undefined8 *)(param_1 + 0xd70) = *(undefined8 *)(param_1 + 0x140);
      *(undefined8 *)(param_1 + 0xd88) = *(undefined8 *)(param_1 + 0x158);
      *(undefined8 *)(param_1 + 0xd80) = *(undefined8 *)(param_1 + 0x150);
      *(undefined8 *)(param_1 + 0xd98) = *(undefined8 *)(param_1 + 0x168);
      *(undefined8 *)(param_1 + 0xd90) = *(undefined8 *)(param_1 + 0x160);
    }
    break;
  case 0x45:
    *(ushort *)(param_1 + 0xeb3) =
         *(ushort *)(param_1 + 0xeb3) & 0xdfff | (ushort)*(byte *)param_3 << 0xd;
    break;
  case 0x46:
    *(float *)(param_1 + 0xe64) = *param_3;
    break;
  case 0x47:
    Aska::CameraFilterManager::SetISO(int)(*(undefined8 *)(param_1 + 0xe30),*param_3);
    break;
  case 0x48:
    *(char *)(param_1 + 0xeac) = SUB41(*param_3,0);
    break;
  case 0x49:
    *(float *)(param_1 + 0xe38) = *param_3;
    break;
  case 0x4a:
    *(float *)(param_1 + 0xe3c) = *param_3;
    break;
  case 0x4b:
    *(float *)(param_1 + 0xe40) = *param_3;
    break;
  case 0x4d:
    *(byte *)(*(long *)(param_1 + 0xe10) + 0x68) =
         *(byte *)(*(long *)(param_1 + 0xe10) + 0x68) & 0xef | *(byte *)param_3 << 4;
    break;
  case 0x4e:
    *(float *)(*(long *)(param_1 + 0xe10) + 0x50) = *param_3;
    break;
  case 0x52:
    *(float *)(*(long *)(param_1 + 0xe10) + 0x54) = *param_3;
    break;
  case 0x53:
    lVar9 = *(long *)(param_1 + 0xe10);
    fVar12 = *param_3;
    if (fVar12 != (float)(uint)*(ushort *)(lVar9 + 100)) {
      *(short *)(lVar9 + 100) = SUB42(fVar12,0);
      fVar12 = (float)logf(1.0 / (float)(int)fVar12,0);
      fVar12 = fVar12 / _UNK_029c744c;
      *(byte *)(lVar9 + 0x68) = *(byte *)(lVar9 + 0x68) | 0x20;
      *(float *)(lVar9 + 0x58) = fVar12;
    }
    break;
  case 0x55:
    uVar1 = *(ushort *)(param_1 + 0xeb3);
    *(ushort *)(param_1 + 0xeb3) = uVar1 & 0xff00 | uVar1 & 0x7f | (*(byte *)param_3 & 1) << 7;
    break;
  case 0x56:
    *(ushort *)(param_1 + 0xeb3) =
         *(ushort *)(param_1 + 0xeb3) & 0xfeff | (ushort)*(byte *)param_3 << 8;
    break;
  case 0x58:
    *(byte *)(*(long *)(param_1 + 0xe18) + 0x2c0) =
         *(byte *)(*(long *)(param_1 + 0xe18) + 0x2c0) & 0xfb | *(byte *)param_3 << 2;
    break;
  case 0x59:
    if (*(long *)(*(long *)PTR__ZN4Aska6Global16m_pCameraManagerE_02cb7d08 + 0xff0) != param_1) {
      *(long *)(*(long *)PTR__ZN4Aska6Global16m_pCameraManagerE_02cb7d08 + 0xff0) = param_1;
      if ((*(byte *)(param_1 + 0xeb4) >> 4 & 1) != 0) {
        Aska::Camera::MakeCameraMatrix()(param_1);
      }
      goto code_r0x021ee0b4;
    }
    break;
  case 0x5a:
    *(float *)(*(long *)(param_1 + 0xe10) + 0x60) = *param_3;
    break;
  case 0x5b:
    *(byte *)(*(long *)(param_1 + 0xe10) + 0x68) =
         *(byte *)(*(long *)(param_1 + 0xe10) + 0x68) & 0xfb | *(byte *)param_3 << 2;
    break;
  case 0x5c:
    *(float *)(param_1 + 0xf10) = *param_3;
    *(float *)(param_1 + 0xf14) = param_3[1];
    *(float *)(param_1 + 0xf18) = param_3[2];
    *(float *)(param_1 + 0xf1c) = param_3[3];
code_r0x021ee124:
    *(ushort *)(param_1 + 0xeb3) = *(ushort *)(param_1 + 0xeb3) | 4;
    break;
  case 0x5d:
    Aska::Camera::ConvertFromOLS()(param_1);
    return 0;
  case 0x5e:
    *(ushort *)(param_1 + 0xeb3) =
         *(ushort *)(param_1 + 0xeb3) & 0xfff7 | (*(byte *)param_3 & 0x1f) << 3;
    break;
  case 0x5f:
    *(float *)(param_1 + 0xe20) = *param_3;
    break;
  case 0x60:
    if (bVar10 == 0) {
      lVar11 = 0xb418;
    }
    else {
      if ((*(byte *)(lVar9 + (uVar5 - 1) * 0x48 + 0x4632) >> 5 & 1) == 0) {
        return 0;
      }
      lVar9 = lVar9 + (uVar5 - 1) * 0x48;
      lVar11 = 0x4618;
    }
    lVar9 = *(long *)(lVar9 + lVar11);
    if (lVar9 == 0) {
      return 0;
    }
    if ((NAN(*(float *)(lVar9 + 0x334))) || (*(float *)(lVar9 + 0x330) != *param_3)) {
      *(float *)(lVar9 + 0x330) = *param_3;
      *(byte *)(lVar9 + 0x345) = *(byte *)(lVar9 + 0x345) & 0xfd;
      Aska::ToneMapTable::CalcLogEncodeCoef()(lVar9 + 0x310);
    }
    break;
  case 0x61:
    if (bVar10 == 0) {
      lVar11 = 0xb418;
    }
    else {
      if ((*(byte *)(lVar9 + (uVar5 - 1) * 0x48 + 0x4632) >> 5 & 1) == 0) {
        return 0;
      }
      lVar9 = lVar9 + (uVar5 - 1) * 0x48;
      lVar11 = 0x4618;
    }
    lVar9 = *(long *)(lVar9 + lVar11);
    if ((lVar9 != 0) &&
       ((NAN(*(float *)(lVar9 + 0x330)) || (*(float *)(lVar9 + 0x334) != *param_3)))) {
      *(float *)(lVar9 + 0x334) = *param_3;
      *(byte *)(lVar9 + 0x345) = *(byte *)(lVar9 + 0x345) & 0xfd;
      Aska::ToneMapTable::CalcLogEncodeCoef()(lVar9 + 0x310);
    }
    return 0;
  case 0x62:
    *(float *)(param_1 + 0xe24) = *param_3;
    break;
  case 99:
    *(float *)(param_1 + 0xe28) = *param_3;
  }
code_r0x021ed8ac:
  uVar6 = 1;
code_r0x021ed91c:
  return uVar6;
}

// ==== Aska::Camera::EnableViewFrustumObjectDebug(bool)
// vaddr 0x20ee2f4 | ghidra 0x21ee2f4 | size 4 | symbol _ZN4Aska6Camera28EnableViewFrustumObjectDebugEb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6Camera28EnableViewFrustumObjectDebugEb(void)

{
  return;
}

// ==== Aska::Camera::CrossFade()
// vaddr 0x20ee2f8 | ghidra 0x21ee2f8 | size 204 | symbol _ZN4Aska6Camera9CrossFadeEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6Camera9CrossFadeEv(void)

{
  undefined *puVar1;
  undefined *puVar2;
  undefined *puVar3;
  long *plVar4;
  ulong uVar5;
  undefined4 uVar6;
  
  puVar1 = PTR__ZN4Aska6Camera13m_pCrossFaderE_02cb7638;
  if (*(long *)PTR__ZN4Aska6Camera13m_pCrossFaderE_02cb7638 != 0) {
    (*(code *)PTR__ZN4Aska10CrossFader6ReinitEf_02c9b0c0)
              (*(undefined4 *)PTR__ZN4Aska6Camera15m_fCrossFadeSecE_02cb93a0);
    return;
  }
  plVar4 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x780,PTR__ZSt7nothrow_02cb9a80);
  if (plVar4 != (long *)0x0) {
    Aska::BackBufferEffect::BackBufferEffect()(plVar4);
    puVar3 = PTR__ZTVN4Aska10CrossFaderE_02cc0b30;
    puVar2 = PTR__ZN4Aska6Camera15m_fCrossFadeSecE_02cb93a0;
    *(long **)puVar1 = plVar4;
    uVar6 = *(undefined4 *)puVar2;
    *plVar4 = (long)(puVar3 + 0x10);
    uVar5 = Aska::CrossFader::Init(float)(uVar6,plVar4);
    plVar4 = *(long **)puVar1;
    if ((uVar5 & 1) != 0) {
      *(byte *)(plVar4 + 0xea) = *(byte *)(plVar4 + 0xea) & 0xfb;
      (*(code *)PTR__ZN4Aska11TaskManager3AddEPNS_4TaskE_02c95ab0)
                (*(undefined8 *)PTR__ZN4Aska6Global16m_pObjectManagerE_02cc4688,plVar4);
      return;
    }
    (**(code **)(*plVar4 + 0x50))(plVar4);
  }
  *(undefined8 *)puVar1 = 0;
  return;
}

// ==== Aska::Camera::~Camera()
// vaddr 0x20ee3c4 | ghidra 0x21ee3c4 | size 268 | symbol _ZN4Aska6CameraD1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6CameraD2Ev(long *param_1)

{
  int iVar1;
  long *plVar2;
  
  plVar2 = (long *)param_1[0x1c2];
  *param_1 = (long)(PTR__ZTVN4Aska6CameraE_02cc27a8 + 0x10);
  if (plVar2 != (long *)0x0) {
    iVar1 = (int)plVar2[1] + -1;
    *(int *)(plVar2 + 1) = iVar1;
    if (iVar1 == 0) {
      (**(code **)(*plVar2 + 8))();
    }
    param_1[0x1c2] = 0;
  }
  plVar2 = (long *)param_1[0x1c3];
  if (plVar2 != (long *)0x0) {
    iVar1 = (int)plVar2[1] + -1;
    *(int *)(plVar2 + 1) = iVar1;
    if (iVar1 == 0) {
      (**(code **)(*plVar2 + 8))();
    }
    param_1[0x1c3] = 0;
  }
  param_1[0x1ce] = (long)(PTR__ZTVN4Aska6TArrayINS_6Camera7AFPointELb1EEE_02cba8f0 + 0x10);
  *(ushort *)((long)param_1 + 0xea2) = *(ushort *)((long)param_1 + 0xea2) | 1;
  if (param_1[0x1cf] != 0) {
    operator delete[](void*)();
    param_1[0x1cf] = 0;
  }
  param_1[0x1d2] = 0;
  param_1[0x1d1] = 0;
  param_1[0x1d0] = 0;
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

// ==== Aska::TArray<Aska::Camera::AFPoint, true>::~TArray()
// vaddr 0x20ee4d0 | ghidra 0x21ee4d0 | size 68 | symbol _ZN4Aska6TArrayINS_6Camera7AFPointELb1EED2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6TArrayINS_6Camera7AFPointELb1EED2Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska6TArrayINS_6Camera7AFPointELb1EEE_02cba8f0 + 0x10);
  *(ushort *)((long)param_1 + 0x32) = *(ushort *)((long)param_1 + 0x32) | 1;
  if (param_1[1] != 0) {
    operator delete[](void*)();
    param_1[1] = 0;
  }
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[2] = 0;
  return;
}

// ==== Aska::Camera::~Camera()
// vaddr 0x20ee514 | ghidra 0x21ee514 | size 24 | symbol _ZN4Aska6CameraD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6CameraD0Ev(undefined8 param_1)

{
  Aska::Camera::~Camera()();
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::Camera::MakeViewFrustumPlane(int)
// vaddr 0x20ee52c | ghidra 0x21ee52c | size 2736 | symbol _ZN4Aska6Camera20MakeViewFrustumPlaneEi | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska6Camera20MakeViewFrustumPlaneEi(long *param_1,int param_2)

{
  long lVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  ushort uVar7;
  long *plVar8;
  float *pfVar9;
  long lVar10;
  ushort *puVar11;
  long lVar12;
  long lVar13;
  long lVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  float fVar19;
  float fVar20;
  float fVar21;
  float fVar22;
  float fVar23;
  undefined1 uVar24;
  undefined1 uVar25;
  undefined2 uVar26;
  float fVar27;
  undefined1 uVar28;
  undefined1 uVar29;
  undefined2 uVar30;
  float fVar31;
  float fVar32;
  float fVar33;
  float fVar34;
  undefined1 auVar35 [16];
  float fVar36;
  undefined1 auVar37 [16];
  undefined1 auVar38 [16];
  float fVar39;
  float fVar40;
  undefined1 auVar41 [16];
  undefined1 auVar42 [16];
  undefined1 auVar43 [16];
  undefined1 auVar44 [16];
  undefined1 auVar45 [16];
  undefined1 auVar46 [16];
  undefined1 auVar47 [16];
  undefined1 auVar48 [16];
  undefined1 auVar49 [16];
  undefined1 auVar50 [16];
  float fVar51;
  float fVar52;
  float fVar57;
  float fVar59;
  undefined1 auVar53 [16];
  undefined1 auVar54 [16];
  float fVar58;
  float fVar60;
  undefined1 auVar55 [16];
  undefined1 auVar56 [16];
  float fVar61;
  float fVar66;
  float fVar67;
  undefined1 auVar62 [16];
  undefined1 auVar63 [16];
  undefined1 auVar64 [16];
  undefined1 auVar65 [16];
  undefined1 auVar68 [16];
  undefined1 auVar69 [16];
  undefined1 auVar70 [16];
  undefined1 auVar71 [16];
  undefined1 auVar72 [16];
  undefined1 auVar73 [16];
  undefined1 auVar74 [16];
  undefined1 auVar75 [16];
  undefined1 auVar76 [16];
  undefined1 auVar77 [16];
  undefined1 auVar78 [16];
  undefined1 auVar79 [16];
  undefined1 auVar80 [16];
  undefined1 auVar81 [16];
  undefined1 auVar82 [16];
  undefined1 auVar83 [16];
  undefined1 auVar84 [16];
  undefined1 auVar85 [16];
  undefined1 auVar86 [16];
  undefined1 auVar87 [16];
  undefined1 auVar88 [16];
  undefined1 auVar89 [16];
  undefined1 auVar90 [16];
  float fVar97;
  undefined1 auVar91 [16];
  undefined1 auVar92 [16];
  undefined1 auVar93 [16];
  undefined1 auVar94 [16];
  undefined1 auVar95 [16];
  undefined1 auVar96 [16];
  undefined1 auVar98 [16];
  undefined1 auVar99 [16];
  undefined1 auVar100 [16];
  undefined1 auVar101 [16];
  undefined1 auVar102 [16];
  undefined1 auVar103 [16];
  undefined1 auVar104 [16];
  undefined1 auVar105 [16];
  undefined1 auVar106 [16];
  undefined1 auVar107 [16];
  undefined1 auVar108 [16];
  undefined1 auVar109 [16];
  undefined1 auVar110 [16];
  undefined1 auVar111 [16];
  undefined1 auVar112 [16];
  undefined1 auVar113 [16];
  undefined1 auVar114 [16];
  undefined1 auVar115 [16];
  undefined1 auVar116 [16];
  undefined1 auVar117 [16];
  undefined1 auVar118 [16];
  undefined1 auVar119 [16];
  float afStack_c0 [19];
  float fStack_74;
  undefined8 uStack_70;
  float fStack_68;
  float fStack_64;
  
  fVar40 = *(float *)((long)param_1 + 0xde4);
  fVar34 = *(float *)((long)param_1 + 0xed4);
  fVar36 = *(float *)(param_1 + 0x1db);
  fVar39 = *(float *)(param_1 + 0x1da);
  fVar22 = *(float *)((long)param_1 + 0x4c);
  fVar18 = *(float *)((long)param_1 + 0x6c);
  fVar23 = *(float *)((long)param_1 + 0x5c);
  lVar14 = *(long *)PTR__ZN4Aska6Global22m_pRenderTargetManagerE_02cbfa00;
  if (param_2 < 0) {
    lVar10 = 0;
    plVar8 = (long *)0x0;
    param_2 = -1;
  }
  else {
    plVar8 = (long *)Aska::RenderTargetManagerGL::GetRenderTarget(unsigned int)(lVar14,(uint)*(byte *)((long)param_1 + 0xeae) | param_2 << 0x10
                                    );
    if (plVar8 == (long *)0x0) {
      return;
    }
    lVar10 = plVar8[1];
    if (lVar10 == 0) {
      return;
    }
  }
  fVar34 = fVar34 * 0.5;
  fVar36 = fVar36 * 0.5;
  fVar39 = (1.0 / fVar40) * ((fVar34 / fVar36) / fVar39);
  if ((*(byte *)((long)param_1 + 0xeb3) & 1) == 0) {
    if (param_2 == -1) {
      fVar40 = (float)NEON_ucvtf((uint)*(byte *)(lVar14 + 0xb1));
      afStack_c0[4] = (float)NEON_ucvtf((uint)*(byte *)(lVar14 + 0xb0));
      fVar36 = fVar36 + fVar40;
      afStack_c0[4] = fVar34 + afStack_c0[4];
      fVar34 = -afStack_c0[4];
      uVar24 = SUB41(fVar34,0);
      uVar25 = (undefined1)((uint)fVar34 >> 8);
      uVar26 = (undefined2)((uint)fVar34 >> 0x10);
      fVar34 = -fVar36;
      uVar28 = SUB41(fVar34,0);
      uVar29 = (undefined1)((uint)fVar34 >> 8);
      uVar30 = (undefined2)((uint)fVar34 >> 0x10);
    }
    else {
      puVar11 = (ushort *)*plVar8;
      fVar33 = (float)NEON_ucvtf((uint)puVar11[7]);
      fVar40 = (float)NEON_ucvtf((uint)puVar11[6]);
      fVar32 = (float)NEON_ucvtf((uint)puVar11[4]);
      fVar32 = (fVar40 - fVar34) - fVar32;
      uVar24 = SUB41(fVar32,0);
      uVar25 = (undefined1)((uint)fVar32 >> 8);
      uVar26 = (undefined2)((uint)fVar32 >> 0x10);
      fVar40 = (float)NEON_ucvtf((uint)puVar11[5]);
      fVar40 = (fVar33 - fVar36) - fVar40;
      afStack_c0[4] = (float)NEON_ucvtf((uint)*puVar11);
      fVar34 = (float)NEON_ucvtf((uint)puVar11[1]);
      fVar36 = -fVar40;
      afStack_c0[4] = fVar32 + afStack_c0[4];
      fVar34 = fVar36 - fVar34;
      uVar28 = SUB41(fVar34,0);
      uVar29 = (undefined1)((uint)fVar34 >> 8);
      uVar30 = (undefined2)((uint)fVar34 >> 0x10);
      if ((*(ushort *)(lVar10 + 6) != 0 || *(ushort *)(lVar10 + 4) != 0) ||
          *(ushort *)(lVar10 + 8) != 0) {
        uVar7 = puVar11[8];
        iVar4 = (uint)*(ushort *)(lVar10 + 4) - (uint)*(byte *)(lVar14 + 0xb0);
        iVar5 = (uint)*(ushort *)(lVar10 + 8) - (uint)*(byte *)(lVar14 + 0xb2);
        iVar3 = iVar5;
        if ((uVar7 & 1) == 0) {
          iVar3 = iVar4;
        }
        iVar6 = (uint)*(ushort *)(lVar10 + 6) - (uint)*(byte *)(lVar14 + 0xb1);
        iVar2 = iVar5;
        if ((uVar7 & 2) == 0) {
          iVar2 = iVar4;
        }
        fVar32 = fVar32 + (float)iVar3;
        uVar24 = SUB41(fVar32,0);
        uVar25 = (undefined1)((uint)fVar32 >> 8);
        uVar26 = (undefined2)((uint)fVar32 >> 0x10);
        iVar3 = iVar5;
        if ((uVar7 & 4) == 0) {
          iVar3 = iVar6;
        }
        afStack_c0[4] = afStack_c0[4] - (float)iVar2;
        if ((uVar7 & 8) == 0) {
          iVar5 = iVar6;
        }
        fVar36 = (float)iVar3 - fVar40;
        fVar34 = fVar34 - (float)iVar5;
        uVar28 = SUB41(fVar34,0);
        uVar29 = (undefined1)((uint)fVar34 >> 8);
        uVar30 = (undefined2)((uint)fVar34 >> 0x10);
      }
    }
    afStack_c0[0] = (float)CONCAT22(uVar26,CONCAT11(uVar25,uVar24)) + *(float *)(param_1 + 0x1aa);
    afStack_c0[9] = fVar39 * (fVar36 + *(float *)((long)param_1 + 0xd54));
    afStack_c0[2] = *(float *)((long)param_1 + 0xdf4);
    afStack_c0[4] = afStack_c0[4] + *(float *)(param_1 + 0x1aa);
    afStack_c0[1] =
         fVar39 * ((float)CONCAT22(uVar30,CONCAT11(uVar29,uVar28)) +
                  *(float *)((long)param_1 + 0xd54));
    afStack_c0[0xf] = 1.0;
    afStack_c0[0xb] = 1.0;
    afStack_c0[3] = 1.0;
    afStack_c0[7] = 1.0;
    afStack_c0[0x12] = *(float *)(param_1 + 0x1c0);
    uStack_70 = 0;
    fStack_74 = 1.0;
    fStack_68 = *(float *)((long)param_1 + 0xe04);
    fStack_64 = 1.0;
    afStack_c0[5] = afStack_c0[1];
    afStack_c0[6] = afStack_c0[2];
    afStack_c0[8] = afStack_c0[4];
    afStack_c0[10] = afStack_c0[2];
    afStack_c0[0xc] = afStack_c0[0];
    afStack_c0[0xd] = afStack_c0[9];
    afStack_c0[0xe] = afStack_c0[2];
    afStack_c0[0x10] = afStack_c0[0];
    afStack_c0[0x11] = afStack_c0[1];
    if ((*(byte *)(param_1 + 0x25) & 1) != 0) {
      (**(code **)(*param_1 + 0xa8))(param_1);
    }
    pfVar9 = (float *)(**(code **)(*param_1 + 0x98))(param_1);
    fVar39 = *pfVar9;
    fVar40 = pfVar9[1];
    fVar32 = pfVar9[2];
    fVar33 = pfVar9[3];
    fVar20 = (float)*(undefined8 *)(pfVar9 + 6);
    fVar21 = (float)((ulong)*(undefined8 *)(pfVar9 + 6) >> 0x20);
    fVar27 = (float)((ulong)*(undefined8 *)(pfVar9 + 4) >> 0x20);
    fVar19 = pfVar9[8];
    fVar17 = pfVar9[9];
    fVar16 = pfVar9[10];
    fVar15 = pfVar9[0xb];
    auVar119._0_4_ = fVar39 * afStack_c0[0];
    auVar119._4_4_ = fVar40 * afStack_c0[1];
    auVar119._8_4_ = fVar32 * afStack_c0[2];
    auVar119._12_4_ = fVar33 * afStack_c0[3];
    fVar36 = (float)*(undefined8 *)(pfVar9 + 4);
    auVar48._0_4_ = afStack_c0[0] * fVar36;
    auVar48._4_4_ = afStack_c0[1] * fVar27;
    auVar48._8_4_ = afStack_c0[2] * fVar20;
    auVar48._12_4_ = afStack_c0[3] * fVar21;
    fVar34 = afStack_c0[0] * fVar19;
    fVar31 = afStack_c0[1] * fVar17;
    auVar53._0_4_ = fVar39 * afStack_c0[4];
    auVar53._4_4_ = fVar40 * afStack_c0[5];
    auVar53._8_4_ = fVar32 * afStack_c0[6];
    auVar53._12_4_ = fVar33 * afStack_c0[7];
    auVar62._0_4_ = fVar36 * afStack_c0[4];
    auVar62._4_4_ = fVar27 * afStack_c0[5];
    auVar62._8_4_ = fVar20 * afStack_c0[6];
    auVar62._12_4_ = fVar21 * afStack_c0[7];
    auVar86._0_4_ = fVar19 * afStack_c0[4];
    auVar86._4_4_ = fVar17 * afStack_c0[5];
    auVar86._8_4_ = fVar16 * afStack_c0[6];
    auVar86._12_4_ = fVar15 * afStack_c0[7];
    auVar68._0_4_ = fVar39 * afStack_c0[8];
    auVar68._4_4_ = fVar40 * afStack_c0[9];
    auVar68._8_4_ = fVar32 * afStack_c0[10];
    auVar68._12_4_ = fVar33 * afStack_c0[0xb];
    auVar72._0_4_ = fVar36 * afStack_c0[8];
    auVar72._4_4_ = fVar27 * afStack_c0[9];
    auVar72._8_4_ = fVar20 * afStack_c0[10];
    auVar72._12_4_ = fVar21 * afStack_c0[0xb];
    auVar89._0_4_ = fVar19 * afStack_c0[8];
    auVar89._4_4_ = fVar17 * afStack_c0[9];
    auVar89._8_4_ = fVar16 * afStack_c0[10];
    auVar89._12_4_ = fVar15 * afStack_c0[0xb];
    auVar76._0_4_ = fVar39 * afStack_c0[0xc];
    auVar76._4_4_ = fVar40 * afStack_c0[0xd];
    auVar76._8_4_ = fVar32 * afStack_c0[0xe];
    auVar76._12_4_ = fVar33 * afStack_c0[0xf];
    auVar79._0_4_ = fVar36 * afStack_c0[0xc];
    auVar79._4_4_ = fVar27 * afStack_c0[0xd];
    auVar79._8_4_ = fVar20 * afStack_c0[0xe];
    auVar79._12_4_ = fVar21 * afStack_c0[0xf];
    auVar96._0_4_ = fVar19 * afStack_c0[0xc];
    auVar96._4_4_ = fVar17 * afStack_c0[0xd];
    auVar96._8_4_ = fVar16 * afStack_c0[0xe];
    auVar96._12_4_ = fVar15 * afStack_c0[0xf];
    auVar84._0_4_ = fVar39 * afStack_c0[0x10];
    auVar84._4_4_ = fVar40 * afStack_c0[0x11];
    auVar84._8_4_ = fVar32 * afStack_c0[0x12];
    auVar84._12_4_ = fVar33 * fStack_74;
    auVar87._0_4_ = fVar36 * afStack_c0[0x10];
    auVar87._4_4_ = fVar27 * afStack_c0[0x11];
    auVar87._8_4_ = fVar20 * afStack_c0[0x12];
    auVar87._12_4_ = fVar21 * fStack_74;
    auVar109._0_4_ = fVar19 * afStack_c0[0x10];
    auVar109._4_4_ = fVar17 * afStack_c0[0x11];
    auVar109._8_4_ = fVar16 * afStack_c0[0x12];
    auVar109._12_4_ = fVar15 * fStack_74;
    auVar82._0_4_ = fVar39 * (float)uStack_70;
    auVar82._4_4_ = fVar40 * uStack_70._4_4_;
    auVar82._8_4_ = fVar32 * fStack_68;
    auVar82._12_4_ = fVar33 * fStack_64;
    fVar36 = fVar36 * (float)uStack_70;
    fVar27 = fVar27 * uStack_70._4_4_;
    auVar83._0_4_ = fVar19 * (float)uStack_70;
    auVar83._4_4_ = fVar17 * uStack_70._4_4_;
    auVar83._8_4_ = fVar16 * fStack_68;
    auVar83._12_4_ = fVar15 * fStack_64;
    auVar42 = NEON_ext(auVar119,auVar119,8,1);
    auVar91 = NEON_ext(auVar48,auVar48,8,1);
    auVar75._4_4_ = fVar31;
    auVar75._0_4_ = fVar34;
    auVar75._8_4_ = afStack_c0[2] * fVar16;
    auVar75._12_4_ = afStack_c0[3] * fVar15;
    auVar78._4_4_ = fVar31;
    auVar78._0_4_ = fVar34;
    auVar78._8_4_ = afStack_c0[2] * fVar16;
    auVar78._12_4_ = afStack_c0[3] * fVar15;
    auVar98 = NEON_ext(auVar75,auVar78,8,1);
    auVar114 = NEON_ext(auVar62,auVar62,8,1);
    auVar44 = NEON_ext(auVar86,auVar86,8,1);
    auVar92 = NEON_ext(auVar68,auVar68,8,1);
    auVar99 = NEON_ext(auVar72,auVar72,8,1);
    auVar110 = NEON_ext(auVar53,auVar53,8,1);
    auVar115 = NEON_ext(auVar76,auVar76,8,1);
    auVar45 = NEON_ext(auVar79,auVar79,8,1);
    auVar93 = NEON_ext(auVar96,auVar96,8,1);
    auVar100 = NEON_ext(auVar84,auVar84,8,1);
    auVar111 = NEON_ext(auVar89,auVar89,8,1);
    auVar116 = NEON_ext(auVar109,auVar109,8,1);
    auVar80 = NEON_ext(auVar82,auVar82,8,1);
    auVar65._4_4_ = fVar27;
    auVar65._0_4_ = fVar36;
    auVar65._8_4_ = fVar20 * fStack_68;
    auVar65._12_4_ = fVar21 * fStack_64;
    auVar71._4_4_ = fVar27;
    auVar71._0_4_ = fVar36;
    auVar71._8_4_ = fVar20 * fStack_68;
    auVar71._12_4_ = fVar21 * fStack_64;
    auVar94 = NEON_ext(auVar65,auVar71,8,1);
    auVar101 = NEON_ext(auVar83,auVar83,8,1);
    fVar40 = auVar42._0_4_ + auVar119._0_4_ + auVar42._4_4_ + auVar119._4_4_;
    fVar19 = auVar91._0_4_ + auVar48._0_4_ + auVar91._4_4_ + auVar48._4_4_;
    lVar14 = CONCAT44(fVar19,fVar40);
    fVar15 = auVar98._0_4_ + fVar34 + auVar98._4_4_ + fVar31;
    fVar32 = auVar110._0_4_ + auVar53._0_4_ + auVar110._4_4_ + auVar53._4_4_;
    fVar20 = auVar114._0_4_ + auVar62._0_4_ + auVar114._4_4_ + auVar62._4_4_;
    uVar24 = SUB41(fVar32,0);
    uVar25 = (undefined1)((uint)fVar32 >> 8);
    uVar26 = (undefined2)((uint)fVar32 >> 0x10);
    fVar34 = auVar44._0_4_ + auVar86._0_4_ + auVar44._4_4_ + auVar86._4_4_;
    fVar39 = auVar111._0_4_ + auVar89._0_4_ + auVar111._4_4_ + auVar89._4_4_;
    fVar16 = auVar93._0_4_ + auVar96._0_4_ + auVar93._4_4_ + auVar96._4_4_;
    fVar17 = auVar116._0_4_ + auVar109._0_4_ + auVar116._4_4_ + auVar109._4_4_;
    lVar10 = CONCAT44(auVar94._0_4_ + fVar36 + auVar94._4_4_ + fVar27,
                      auVar80._0_4_ + auVar82._0_4_ + auVar80._4_4_ + auVar82._4_4_);
    fVar27 = auVar101._0_4_ + auVar83._0_4_ + auVar101._4_4_ + auVar83._4_4_;
    auVar42 = NEON_ext(auVar87,auVar87,8,1);
    fVar36 = auVar92._0_4_ + auVar68._0_4_ + auVar92._4_4_ + auVar68._4_4_;
    fVar21 = auVar99._0_4_ + auVar72._0_4_ + auVar99._4_4_ + auVar72._4_4_;
    uVar28 = SUB41(fVar36,0);
    uVar29 = (undefined1)((uint)fVar36 >> 8);
    uVar30 = (undefined2)((uint)fVar36 >> 0x10);
    fVar33 = auVar115._0_4_ + auVar76._0_4_ + auVar115._4_4_ + auVar76._4_4_;
    fVar31 = auVar45._0_4_ + auVar79._0_4_ + auVar45._4_4_ + auVar79._4_4_;
    lVar12 = CONCAT44(fVar31,fVar33);
    lVar13 = CONCAT44(auVar42._0_4_ + auVar87._0_4_ + auVar42._4_4_ + auVar87._4_4_,
                      auVar100._0_4_ + auVar84._0_4_ + auVar100._4_4_ + auVar84._4_4_);
    fVar51 = fVar32 - fVar40;
    fVar57 = fVar20 - fVar19;
    fVar59 = fVar34 - fVar15;
    auVar90._0_4_ = ((fVar19 - fVar23) * fVar59 - (fVar15 - fVar18) * fVar57) * _UNK_029c49f0;
    auVar90._4_4_ = ((fVar40 - fVar22) * fVar59 - (fVar15 - fVar18) * fVar51) * _UNK_029c49f4;
    auVar90._8_4_ = ((fVar40 - fVar22) * fVar57 - (fVar19 - fVar23) * fVar51) * _UNK_029c49f8;
    auVar108._0_4_ =
         ((fVar20 - fVar23) * (fVar39 - fVar34) - (fVar34 - fVar18) * (fVar21 - fVar20)) *
         _UNK_029c49f0;
    auVar108._4_4_ =
         ((fVar32 - fVar22) * (fVar39 - fVar34) - (fVar34 - fVar18) * (fVar36 - fVar32)) *
         _UNK_029c49f4;
    auVar108._8_4_ =
         ((fVar32 - fVar22) * (fVar21 - fVar20) - (fVar20 - fVar23) * (fVar36 - fVar32)) *
         _UNK_029c49f8;
    auVar113._0_4_ =
         ((fVar21 - fVar23) * (fVar16 - fVar39) - (fVar39 - fVar18) * (fVar31 - fVar21)) *
         _UNK_029c49f0;
    auVar113._4_4_ =
         ((fVar36 - fVar22) * (fVar16 - fVar39) - (fVar39 - fVar18) * (fVar33 - fVar36)) *
         _UNK_029c49f4;
    auVar113._8_4_ =
         ((fVar36 - fVar22) * (fVar31 - fVar21) - (fVar21 - fVar23) * (fVar33 - fVar36)) *
         _UNK_029c49f8;
    auVar118._0_4_ =
         ((fVar31 - fVar23) * (fVar15 - fVar16) - (fVar16 - fVar18) * (fVar19 - fVar31)) *
         _UNK_029c49f0;
    auVar118._4_4_ =
         ((fVar33 - fVar22) * (fVar15 - fVar16) - (fVar16 - fVar18) * (fVar40 - fVar33)) *
         _UNK_029c49f4;
    auVar118._8_4_ =
         ((fVar33 - fVar22) * (fVar19 - fVar31) - (fVar31 - fVar23) * (fVar40 - fVar33)) *
         _UNK_029c49f8;
    auVar46._0_4_ = (fVar57 * (fVar39 - fVar15) - fVar59 * (fVar21 - fVar19)) * _UNK_029c49f0;
    auVar46._4_4_ = (fVar51 * (fVar39 - fVar15) - fVar59 * (fVar36 - fVar40)) * _UNK_029c49f4;
    auVar46._8_4_ = (fVar51 * (fVar21 - fVar19) - fVar57 * (fVar36 - fVar40)) * _UNK_029c49f8;
    auVar90._12_4_ = 0x3f800000;
    auVar108._12_4_ = 0x3f800000;
    auVar113._12_4_ = 0x3f800000;
    auVar118._12_4_ = 0x3f800000;
    auVar46._12_4_ = 0x3f800000;
    auVar42 = NEON_ext(auVar90,auVar90,8,1);
    auVar44 = NEON_ext(auVar108,auVar108,8,1);
    auVar45 = NEON_ext(auVar113,auVar113,8,1);
    auVar80 = NEON_ext(auVar118,auVar118,8,1);
    auVar91 = NEON_ext(auVar46,auVar46,8,1);
    fVar18 = auVar90._0_4_ * auVar90._0_4_ + auVar42._0_4_ * auVar42._0_4_ +
             auVar90._4_4_ * auVar90._4_4_ + 0.0;
    fVar36 = auVar108._0_4_ * auVar108._0_4_ + auVar44._0_4_ * auVar44._0_4_ +
             auVar108._4_4_ * auVar108._4_4_ + 0.0;
    auVar49._4_4_ = fVar18;
    auVar49._0_4_ = fVar18;
    auVar49._8_4_ = fVar18;
    auVar49._12_4_ = fVar18;
    fVar18 = auVar113._0_4_ * auVar113._0_4_ + auVar45._0_4_ * auVar45._0_4_ +
             auVar113._4_4_ * auVar113._4_4_ + 0.0;
    auVar54._4_4_ = fVar36;
    auVar54._0_4_ = fVar36;
    auVar54._8_4_ = fVar36;
    auVar54._12_4_ = fVar36;
    auVar42 = NEON_frsqrte(auVar49,4);
    fVar36 = auVar118._0_4_ * auVar118._0_4_ + auVar80._0_4_ * auVar80._0_4_ +
             auVar118._4_4_ * auVar118._4_4_ + 0.0;
    auVar63._4_4_ = fVar18;
    auVar63._0_4_ = fVar18;
    auVar63._8_4_ = fVar18;
    auVar63._12_4_ = fVar18;
    auVar44 = NEON_frsqrte(auVar54,4);
    fVar22 = auVar42._0_4_;
    auVar102._0_4_ = fVar22 * fVar22;
    fVar23 = auVar42._4_4_;
    auVar102._4_4_ = fVar23 * fVar23;
    fVar32 = auVar42._8_4_;
    auVar102._8_4_ = fVar32 * fVar32;
    auVar102._12_4_ = auVar42._12_4_ * auVar42._12_4_;
    fVar18 = auVar46._0_4_ * auVar46._0_4_ + auVar91._0_4_ * auVar91._0_4_ +
             auVar46._4_4_ * auVar46._4_4_ + 0.0;
    auVar69._4_4_ = fVar36;
    auVar69._0_4_ = fVar36;
    auVar69._8_4_ = fVar36;
    auVar69._12_4_ = fVar36;
    auVar45 = NEON_frsqrte(auVar63,4);
    auVar42 = NEON_frsqrts(auVar102,auVar49,4);
    fVar36 = auVar44._0_4_;
    auVar103._0_4_ = fVar36 * fVar36;
    fVar40 = auVar44._4_4_;
    auVar103._4_4_ = fVar40 * fVar40;
    fVar33 = auVar44._8_4_;
    auVar103._8_4_ = fVar33 * fVar33;
    auVar103._12_4_ = auVar44._12_4_ * auVar44._12_4_;
    auVar73._4_4_ = fVar18;
    auVar73._0_4_ = fVar18;
    auVar73._8_4_ = fVar18;
    auVar73._12_4_ = fVar18;
    auVar80 = NEON_frsqrte(auVar69,4);
    auVar44 = NEON_frsqrts(auVar103,auVar54,4);
    fVar19 = auVar45._0_4_;
    auVar104._0_4_ = fVar19 * fVar19;
    fVar31 = auVar45._4_4_;
    auVar104._4_4_ = fVar31 * fVar31;
    fVar59 = auVar45._8_4_;
    auVar104._8_4_ = fVar59 * fVar59;
    auVar104._12_4_ = auVar45._12_4_ * auVar45._12_4_;
    auVar91 = NEON_frsqrte(auVar73,4);
    auVar45 = NEON_frsqrts(auVar104,auVar63,4);
    fVar61 = auVar80._0_4_;
    auVar105._0_4_ = fVar61 * fVar61;
    fVar66 = auVar80._4_4_;
    auVar105._4_4_ = fVar66 * fVar66;
    fVar67 = auVar80._8_4_;
    auVar105._8_4_ = fVar67 * fVar67;
    auVar105._12_4_ = auVar80._12_4_ * auVar80._12_4_;
    auVar80 = NEON_frsqrts(auVar105,auVar69,4);
    fVar18 = auVar91._0_4_;
    auVar106._0_4_ = fVar18 * fVar18;
    fVar51 = auVar91._4_4_;
    auVar106._4_4_ = fVar51 * fVar51;
    fVar97 = auVar91._8_4_;
    auVar106._8_4_ = fVar97 * fVar97;
    auVar106._12_4_ = auVar91._12_4_ * auVar91._12_4_;
    auVar91 = NEON_frsqrts(auVar106,auVar73,4);
    fVar52 = auVar108._0_4_ * fVar36 * auVar44._0_4_;
    fVar58 = auVar108._4_4_ * fVar40 * auVar44._4_4_;
    fVar60 = auVar108._8_4_ * fVar33 * auVar44._8_4_;
    fVar33 = auVar46._0_4_ * fVar18 * auVar91._0_4_;
    fVar57 = auVar46._4_4_ * fVar51 * auVar91._4_4_;
    fVar18 = auVar46._8_4_ * fVar97 * auVar91._8_4_;
    fVar40 = auVar90._0_4_ * fVar22 * auVar42._0_4_;
    fVar51 = auVar90._4_4_ * fVar23 * auVar42._4_4_;
    fVar32 = auVar90._8_4_ * fVar32 * auVar42._8_4_;
    fVar36 = auVar113._0_4_ * fVar19 * auVar45._0_4_;
    fVar19 = auVar113._4_4_ * fVar31 * auVar45._4_4_;
    fVar59 = auVar113._8_4_ * fVar59 * auVar45._8_4_;
    fVar22 = auVar118._0_4_ * fVar61 * auVar80._0_4_;
    fVar31 = auVar118._4_4_ * fVar66 * auVar80._4_4_;
    fVar23 = auVar118._8_4_ * fVar67 * auVar80._8_4_;
  }
  else {
    fVar18 = *(float *)(param_1 + 0x1c1) * 0.5;
    fVar22 = (fVar36 / fVar34) * fVar18;
    if (param_2 == -1) {
      lVar12 = 0;
      lVar10 = 3;
      fVar36 = (float)NEON_ucvtf((uint)*(byte *)(lVar14 + 0xb1));
      fVar23 = (float)NEON_ucvtf((uint)*(byte *)(lVar14 + 0xb0));
      fVar22 = fVar22 + fVar36;
      fVar23 = fVar18 + fVar23;
      uVar28 = SUB41(fVar23,0);
      uVar29 = (undefined1)((uint)fVar23 >> 8);
      uVar30 = (undefined2)((uint)fVar23 >> 0x10);
      lVar14 = 2;
      fVar18 = fVar39 * fVar22;
      uVar24 = SUB41(fVar18,0);
      uVar25 = (undefined1)((uint)fVar18 >> 8);
      uVar26 = (undefined2)((uint)fVar18 >> 0x10);
      fVar18 = -fVar23;
      fVar36 = -(fVar39 * fVar22);
      lVar13 = 1;
      afStack_c0[0] = fVar18;
    }
    else {
      puVar11 = (ushort *)*plVar8;
      fVar39 = fVar39 * (fVar22 / fVar36);
      fVar23 = (float)NEON_ucvtf((uint)puVar11[6]);
      fVar33 = (float)NEON_ucvtf((uint)puVar11[7]);
      fVar22 = (float)NEON_ucvtf((uint)puVar11[4]);
      fVar22 = (fVar23 - fVar34) - fVar22;
      fVar40 = (float)NEON_ucvtf((uint)puVar11[5]);
      fVar32 = (float)NEON_ucvtf((uint)puVar11[1]);
      fVar40 = (fVar33 - fVar36) - fVar40;
      fVar36 = (float)NEON_ucvtf((uint)*puVar11);
      fVar23 = fVar22 + *(float *)(param_1 + 0x1aa);
      fVar22 = fVar22 + fVar36 + *(float *)(param_1 + 0x1aa);
      uVar24 = SUB41(fVar22,0);
      uVar25 = (undefined1)((uint)fVar22 >> 8);
      uVar26 = (undefined2)((uint)fVar22 >> 0x10);
      fVar36 = *(float *)((long)param_1 + 0xd54) - fVar40;
      fVar40 = (-fVar40 - fVar32) + *(float *)((long)param_1 + 0xd54);
      if ((*(ushort *)(lVar10 + 6) != 0 || *(ushort *)(lVar10 + 4) != 0) ||
          *(ushort *)(lVar10 + 8) != 0) {
        uVar7 = puVar11[8];
        iVar4 = (uint)*(ushort *)(lVar10 + 4) - (uint)*(byte *)(lVar14 + 0xb0);
        iVar5 = (uint)*(ushort *)(lVar10 + 8) - (uint)*(byte *)(lVar14 + 0xb2);
        iVar3 = iVar5;
        if ((uVar7 & 1) == 0) {
          iVar3 = iVar4;
        }
        iVar6 = (uint)*(ushort *)(lVar10 + 6) - (uint)*(byte *)(lVar14 + 0xb1);
        iVar2 = iVar5;
        if ((uVar7 & 2) == 0) {
          iVar2 = iVar4;
        }
        fVar23 = fVar23 + (float)iVar3;
        iVar3 = iVar5;
        if ((uVar7 & 4) == 0) {
          iVar3 = iVar6;
        }
        fVar22 = fVar22 - (float)iVar2;
        uVar24 = SUB41(fVar22,0);
        uVar25 = (undefined1)((uint)fVar22 >> 8);
        uVar26 = (undefined2)((uint)fVar22 >> 0x10);
        if ((uVar7 & 8) == 0) {
          iVar5 = iVar6;
        }
        fVar36 = fVar36 + (float)iVar3;
        fVar40 = fVar40 - (float)iVar5;
      }
      fVar23 = (fVar18 / fVar34) * fVar23;
      fVar18 = (fVar18 / fVar34) * (float)CONCAT22(uVar26,CONCAT11(uVar25,uVar24));
      uVar28 = SUB41(fVar18,0);
      uVar29 = (undefined1)((uint)fVar18 >> 8);
      uVar30 = (undefined2)((uint)fVar18 >> 0x10);
      lVar14 = 0;
      fVar36 = fVar39 * fVar36;
      fVar39 = fVar39 * fVar40;
      uVar24 = SUB41(fVar39,0);
      uVar25 = (undefined1)((uint)fVar39 >> 8);
      uVar26 = (undefined2)((uint)fVar39 >> 0x10);
      lVar10 = 1;
      lVar13 = 2;
      lVar12 = 3;
      afStack_c0[0xc] = fVar23;
    }
    afStack_c0[lVar12 * 4 + 1] = fVar36;
    fVar22 = *(float *)((long)param_1 + 0xdf4);
    afStack_c0[lVar12 * 4 + 2] = fVar22;
    afStack_c0[lVar12 * 4 + 3] = 1.0;
    afStack_c0[lVar13 * 4] = (float)CONCAT22(uVar30,CONCAT11(uVar29,uVar28));
    afStack_c0[lVar13 * 4 + 1] = fVar36;
    afStack_c0[lVar13 * 4 + 2] = fVar22;
    afStack_c0[lVar13 * 4 + 3] = 1.0;
    afStack_c0[lVar14 * 4] = fVar23;
    afStack_c0[lVar14 * 4 + 1] = (float)CONCAT22(uVar26,CONCAT11(uVar25,uVar24));
    afStack_c0[lVar14 * 4 + 2] = fVar22;
    afStack_c0[lVar14 * 4 + 3] = 1.0;
    afStack_c0[lVar10 * 4] = fVar18;
    afStack_c0[lVar10 * 4 + 1] = (float)CONCAT22(uVar26,CONCAT11(uVar25,uVar24));
    afStack_c0[lVar10 * 4 + 2] = fVar22;
    afStack_c0[lVar10 * 4 + 3] = 1.0;
    afStack_c0[0x10] = afStack_c0[0];
    afStack_c0[0x11] = afStack_c0[1];
    fStack_74 = afStack_c0[3];
    afStack_c0[0x12] = *(float *)(param_1 + 0x1c0);
    uStack_70 = 0;
    fStack_68 = *(float *)((long)param_1 + 0xe04);
    fStack_64 = 1.0;
    if ((*(byte *)(param_1 + 0x25) & 1) != 0) {
      (**(code **)(*param_1 + 0xa8))(param_1);
    }
    pfVar9 = (float *)(**(code **)(*param_1 + 0x98))(param_1);
    fVar22 = *pfVar9;
    fVar23 = pfVar9[1];
    fVar34 = pfVar9[2];
    fVar39 = pfVar9[3];
    fVar40 = (float)*(undefined8 *)(pfVar9 + 6);
    fVar32 = (float)((ulong)*(undefined8 *)(pfVar9 + 6) >> 0x20);
    fVar19 = (float)((ulong)*(undefined8 *)(pfVar9 + 4) >> 0x20);
    fVar33 = (float)*(undefined8 *)(pfVar9 + 10);
    fVar17 = (float)((ulong)*(undefined8 *)(pfVar9 + 10) >> 0x20);
    fVar59 = (float)((ulong)*(undefined8 *)(pfVar9 + 8) >> 0x20);
    auVar55._0_4_ = fVar22 * afStack_c0[0];
    auVar55._4_4_ = fVar23 * afStack_c0[1];
    auVar55._8_4_ = fVar34 * afStack_c0[2];
    auVar55._12_4_ = fVar39 * afStack_c0[3];
    fVar18 = (float)*(undefined8 *)(pfVar9 + 4);
    auVar64._0_4_ = fVar18 * afStack_c0[0];
    auVar64._4_4_ = fVar19 * afStack_c0[1];
    auVar64._8_4_ = fVar40 * afStack_c0[2];
    auVar64._12_4_ = fVar32 * afStack_c0[3];
    fVar36 = (float)*(undefined8 *)(pfVar9 + 8);
    auVar100._0_4_ = fVar36 * afStack_c0[0];
    auVar100._4_4_ = fVar59 * afStack_c0[1];
    auVar100._8_4_ = fVar33 * afStack_c0[2];
    auVar100._12_4_ = fVar17 * afStack_c0[3];
    auVar70._0_4_ = fVar22 * afStack_c0[4];
    auVar70._4_4_ = fVar23 * afStack_c0[5];
    auVar70._8_4_ = fVar34 * afStack_c0[6];
    auVar70._12_4_ = fVar39 * afStack_c0[7];
    auVar74._0_4_ = fVar18 * afStack_c0[4];
    auVar74._4_4_ = fVar19 * afStack_c0[5];
    auVar74._8_4_ = fVar40 * afStack_c0[6];
    auVar74._12_4_ = fVar32 * afStack_c0[7];
    auVar110._0_4_ = fVar36 * afStack_c0[4];
    auVar110._4_4_ = fVar59 * afStack_c0[5];
    auVar110._8_4_ = fVar33 * afStack_c0[6];
    auVar110._12_4_ = fVar17 * afStack_c0[7];
    auVar77._0_4_ = fVar22 * afStack_c0[8];
    auVar77._4_4_ = fVar23 * afStack_c0[9];
    auVar77._8_4_ = fVar34 * afStack_c0[10];
    auVar77._12_4_ = fVar39 * afStack_c0[0xb];
    auVar81._0_4_ = fVar18 * afStack_c0[8];
    auVar81._4_4_ = fVar19 * afStack_c0[9];
    auVar81._8_4_ = fVar40 * afStack_c0[10];
    auVar81._12_4_ = fVar32 * afStack_c0[0xb];
    auVar114._0_4_ = fVar36 * afStack_c0[8];
    auVar114._4_4_ = fVar59 * afStack_c0[9];
    auVar114._8_4_ = fVar33 * afStack_c0[10];
    auVar114._12_4_ = fVar17 * afStack_c0[0xb];
    auVar85._0_4_ = fVar22 * afStack_c0[0xc];
    auVar85._4_4_ = fVar23 * afStack_c0[0xd];
    auVar85._8_4_ = fVar34 * afStack_c0[0xe];
    auVar85._12_4_ = fVar39 * afStack_c0[0xf];
    auVar88._0_4_ = fVar18 * afStack_c0[0xc];
    auVar88._4_4_ = fVar19 * afStack_c0[0xd];
    auVar88._8_4_ = fVar40 * afStack_c0[0xe];
    auVar88._12_4_ = fVar32 * afStack_c0[0xf];
    auVar115._0_4_ = fVar36 * afStack_c0[0xc];
    auVar115._4_4_ = fVar59 * afStack_c0[0xd];
    auVar115._8_4_ = fVar33 * afStack_c0[0xe];
    auVar115._12_4_ = fVar17 * afStack_c0[0xf];
    auVar95._0_4_ = fVar22 * afStack_c0[0x10];
    auVar95._4_4_ = fVar23 * afStack_c0[0x11];
    auVar95._8_4_ = fVar34 * afStack_c0[0x12];
    auVar95._12_4_ = fVar39 * fStack_74;
    auVar107._0_4_ = fVar18 * afStack_c0[0x10];
    auVar107._4_4_ = fVar19 * afStack_c0[0x11];
    auVar107._8_4_ = fVar40 * afStack_c0[0x12];
    auVar107._12_4_ = fVar32 * fStack_74;
    auVar41._0_4_ = fVar36 * afStack_c0[0x10];
    auVar41._4_4_ = fVar59 * afStack_c0[0x11];
    auVar41._8_4_ = fVar33 * afStack_c0[0x12];
    auVar41._12_4_ = fVar17 * fStack_74;
    auVar112._0_4_ = fVar22 * (float)uStack_70;
    auVar112._4_4_ = fVar23 * uStack_70._4_4_;
    auVar112._8_4_ = fVar34 * fStack_68;
    auVar112._12_4_ = fVar39 * fStack_64;
    auVar117._0_4_ = fVar18 * (float)uStack_70;
    auVar117._4_4_ = fVar19 * uStack_70._4_4_;
    auVar117._8_4_ = fVar40 * fStack_68;
    auVar117._12_4_ = fVar32 * fStack_64;
    auVar43._0_4_ = fVar36 * (float)uStack_70;
    auVar43._4_4_ = fVar59 * uStack_70._4_4_;
    auVar43._8_4_ = fVar33 * fStack_68;
    auVar43._12_4_ = fVar17 * fStack_64;
    auVar116._0_4_ = fVar22 * _UNK_027dbb00;
    auVar116._4_4_ = fVar23 * _UNK_027dbb04;
    auVar116._8_4_ = fVar34 * _UNK_027dbb08;
    auVar116._12_4_ = fVar39 * _UNK_027dbb0c;
    auVar37._0_4_ = fVar18 * _UNK_027dbb00;
    auVar37._4_4_ = fVar19 * _UNK_027dbb04;
    auVar37._8_4_ = fVar40 * _UNK_027dbb08;
    auVar37._12_4_ = fVar32 * _UNK_027dbb0c;
    auVar99._0_4_ = fVar36 * _UNK_027dbb00;
    auVar99._4_4_ = fVar59 * _UNK_027dbb04;
    auVar99._8_4_ = fVar33 * _UNK_027dbb08;
    auVar99._12_4_ = fVar17 * _UNK_027dbb0c;
    fVar16 = fVar22 * _UNK_027dbb10;
    fVar20 = fVar23 * _UNK_027dbb14;
    fVar51 = fVar18 * _UNK_027dbb10;
    fVar57 = fVar19 * _UNK_027dbb14;
    auVar47._0_4_ = fVar36 * _UNK_027dbb10;
    auVar47._4_4_ = fVar59 * _UNK_027dbb14;
    auVar47._8_4_ = fVar33 * _UNK_027dbb18;
    auVar47._12_4_ = fVar17 * _UNK_027dbb1c;
    auVar98._0_4_ = fVar22 * _UNK_027dbb20;
    auVar98._4_4_ = fVar23 * _UNK_027dbb24;
    auVar98._8_4_ = fVar34 * _UNK_027dbb28;
    auVar98._12_4_ = fVar39 * _UNK_027dbb2c;
    fVar18 = fVar18 * _UNK_027dbb20;
    fVar19 = fVar19 * _UNK_027dbb24;
    fVar36 = fVar36 * _UNK_027dbb20;
    fVar59 = fVar59 * _UNK_027dbb24;
    auVar50 = NEON_ext(auVar55,auVar55,8,1);
    auVar56 = NEON_ext(auVar64,auVar64,8,1);
    auVar65 = NEON_ext(auVar100,auVar100,8,1);
    auVar101 = NEON_ext(auVar70,auVar70,8,1);
    auVar71 = NEON_ext(auVar74,auVar74,8,1);
    auVar75 = NEON_ext(auVar110,auVar110,8,1);
    auVar111 = NEON_ext(auVar77,auVar77,8,1);
    auVar78 = NEON_ext(auVar81,auVar81,8,1);
    auVar82 = NEON_ext(auVar114,auVar114,8,1);
    auVar83 = NEON_ext(auVar85,auVar85,8,1);
    auVar86 = NEON_ext(auVar88,auVar88,8,1);
    auVar89 = NEON_ext(auVar115,auVar115,8,1);
    auVar90 = NEON_ext(auVar95,auVar95,8,1);
    auVar96 = NEON_ext(auVar107,auVar107,8,1);
    auVar108 = NEON_ext(auVar41,auVar41,8,1);
    auVar109 = NEON_ext(auVar112,auVar112,8,1);
    auVar113 = NEON_ext(auVar117,auVar117,8,1);
    auVar118 = NEON_ext(auVar43,auVar43,8,1);
    auVar119 = NEON_ext(auVar116,auVar116,8,1);
    auVar35 = NEON_ext(auVar37,auVar37,8,1);
    auVar38 = NEON_ext(auVar99,auVar99,8,1);
    auVar91._4_4_ = fVar20;
    auVar91._0_4_ = fVar16;
    auVar91._8_4_ = fVar34 * _UNK_027dbb18;
    auVar91._12_4_ = fVar39 * _UNK_027dbb1c;
    auVar92._4_4_ = fVar20;
    auVar92._0_4_ = fVar16;
    auVar92._8_4_ = fVar34 * _UNK_027dbb18;
    auVar92._12_4_ = fVar39 * _UNK_027dbb1c;
    auVar91 = NEON_ext(auVar91,auVar92,8,1);
    auVar93._4_4_ = fVar57;
    auVar93._0_4_ = fVar51;
    auVar93._8_4_ = fVar40 * _UNK_027dbb18;
    auVar93._12_4_ = fVar32 * _UNK_027dbb1c;
    auVar94._4_4_ = fVar57;
    auVar94._0_4_ = fVar51;
    auVar94._8_4_ = fVar40 * _UNK_027dbb18;
    auVar94._12_4_ = fVar32 * _UNK_027dbb1c;
    auVar92 = NEON_ext(auVar93,auVar94,8,1);
    auVar93 = NEON_ext(auVar47,auVar47,8,1);
    auVar94 = NEON_ext(auVar98,auVar98,8,1);
    auVar42._4_4_ = fVar19;
    auVar42._0_4_ = fVar18;
    auVar42._8_4_ = fVar40 * _UNK_027dbb28;
    auVar42._12_4_ = fVar32 * _UNK_027dbb2c;
    auVar44._4_4_ = fVar19;
    auVar44._0_4_ = fVar18;
    auVar44._8_4_ = fVar40 * _UNK_027dbb28;
    auVar44._12_4_ = fVar32 * _UNK_027dbb2c;
    auVar42 = NEON_ext(auVar42,auVar44,8,1);
    auVar45._4_4_ = fVar59;
    auVar45._0_4_ = fVar36;
    auVar45._8_4_ = fVar33 * _UNK_027dbb28;
    auVar45._12_4_ = fVar17 * _UNK_027dbb2c;
    auVar80._4_4_ = fVar59;
    auVar80._0_4_ = fVar36;
    auVar80._8_4_ = fVar33 * _UNK_027dbb28;
    auVar80._12_4_ = fVar17 * _UNK_027dbb2c;
    auVar44 = NEON_ext(auVar45,auVar80,8,1);
    fVar22 = auVar111._0_4_ + auVar77._0_4_ + auVar111._4_4_ + auVar77._4_4_;
    fVar21 = auVar78._0_4_ + auVar81._0_4_ + auVar78._4_4_ + auVar81._4_4_;
    uVar28 = SUB41(fVar22,0);
    uVar29 = (undefined1)((uint)fVar22 >> 8);
    uVar30 = (undefined2)((uint)fVar22 >> 0x10);
    lVar14 = CONCAT44(auVar56._0_4_ + auVar64._0_4_ + auVar56._4_4_ + auVar64._4_4_,
                      auVar50._0_4_ + auVar55._0_4_ + auVar50._4_4_ + auVar55._4_4_);
    fVar15 = auVar65._0_4_ + auVar100._0_4_ + auVar65._4_4_ + auVar100._4_4_;
    lVar12 = CONCAT44(auVar86._0_4_ + auVar88._0_4_ + auVar86._4_4_ + auVar88._4_4_,
                      auVar83._0_4_ + auVar85._0_4_ + auVar83._4_4_ + auVar85._4_4_);
    fVar22 = auVar119._0_4_ + auVar116._0_4_ + auVar119._4_4_ + auVar116._4_4_;
    fVar31 = auVar35._0_4_ + auVar37._0_4_ + auVar35._4_4_ + auVar37._4_4_;
    fVar27 = auVar118._0_4_ + auVar43._0_4_ + auVar118._4_4_ + auVar43._4_4_;
    fVar23 = auVar38._0_4_ + auVar99._0_4_ + auVar38._4_4_ + auVar99._4_4_;
    fVar40 = auVar91._0_4_ + fVar16 + auVar91._4_4_ + fVar20;
    fVar51 = auVar92._0_4_ + fVar51 + auVar92._4_4_ + fVar57;
    fVar39 = auVar82._0_4_ + auVar114._0_4_ + auVar82._4_4_ + auVar114._4_4_;
    fVar16 = auVar89._0_4_ + auVar115._0_4_ + auVar89._4_4_ + auVar115._4_4_;
    fVar32 = auVar93._0_4_ + auVar47._0_4_ + auVar93._4_4_ + auVar47._4_4_;
    fVar34 = auVar101._0_4_ + auVar70._0_4_ + auVar101._4_4_ + auVar70._4_4_;
    fVar20 = auVar71._0_4_ + auVar74._0_4_ + auVar71._4_4_ + auVar74._4_4_;
    uVar24 = SUB41(fVar34,0);
    uVar25 = (undefined1)((uint)fVar34 >> 8);
    uVar26 = (undefined2)((uint)fVar34 >> 0x10);
    lVar13 = CONCAT44(auVar96._0_4_ + auVar107._0_4_ + auVar96._4_4_ + auVar107._4_4_,
                      auVar90._0_4_ + auVar95._0_4_ + auVar90._4_4_ + auVar95._4_4_);
    fVar33 = auVar94._0_4_ + auVar98._0_4_ + auVar94._4_4_ + auVar98._4_4_;
    fVar57 = auVar42._0_4_ + fVar18 + auVar42._4_4_ + fVar19;
    fVar34 = auVar75._0_4_ + auVar110._0_4_ + auVar75._4_4_ + auVar110._4_4_;
    fVar17 = auVar108._0_4_ + auVar41._0_4_ + auVar108._4_4_ + auVar41._4_4_;
    fVar18 = auVar44._0_4_ + fVar36 + auVar44._4_4_ + fVar59;
    fVar36 = fVar23 * fVar23 + fVar22 * fVar22 + fVar31 * fVar31 + 0.0;
    fVar19 = fVar32 * fVar32 + fVar40 * fVar40 + fVar51 * fVar51 + 0.0;
    auVar101._4_4_ = fVar36;
    auVar101._0_4_ = fVar36;
    auVar101._8_4_ = fVar36;
    auVar101._12_4_ = fVar36;
    fVar36 = fVar18 * fVar18 + fVar33 * fVar33 + fVar57 * fVar57 + 0.0;
    auVar111._4_4_ = fVar19;
    auVar111._0_4_ = fVar19;
    auVar111._8_4_ = fVar19;
    auVar111._12_4_ = fVar19;
    auVar42 = NEON_frsqrte(auVar101,4);
    auVar35._4_4_ = fVar36;
    auVar35._0_4_ = fVar36;
    auVar35._8_4_ = fVar36;
    auVar35._12_4_ = fVar36;
    auVar44 = NEON_frsqrte(auVar111,4);
    fVar36 = auVar42._0_4_;
    auVar38._0_4_ = fVar36 * fVar36;
    fVar19 = auVar42._4_4_;
    auVar38._4_4_ = fVar19 * fVar19;
    fVar59 = auVar42._8_4_;
    auVar38._8_4_ = fVar59 * fVar59;
    auVar38._12_4_ = auVar42._12_4_ * auVar42._12_4_;
    auVar45 = NEON_frsqrte(auVar35,4);
    auVar42 = NEON_frsqrts(auVar38,auVar101,4);
    fVar52 = auVar44._0_4_;
    auVar50._0_4_ = fVar52 * fVar52;
    fVar58 = auVar44._4_4_;
    auVar50._4_4_ = fVar58 * fVar58;
    fVar60 = auVar44._8_4_;
    auVar50._8_4_ = fVar60 * fVar60;
    auVar50._12_4_ = auVar44._12_4_ * auVar44._12_4_;
    auVar44 = NEON_frsqrts(auVar50,auVar111,4);
    fVar61 = auVar45._0_4_;
    auVar56._0_4_ = fVar61 * fVar61;
    fVar66 = auVar45._4_4_;
    auVar56._4_4_ = fVar66 * fVar66;
    fVar67 = auVar45._8_4_;
    auVar56._8_4_ = fVar67 * fVar67;
    auVar56._12_4_ = auVar45._12_4_ * auVar45._12_4_;
    auVar45 = NEON_frsqrts(auVar56,auVar35,4);
    fVar22 = fVar22 * fVar36 * auVar42._0_4_;
    fVar31 = fVar31 * fVar19 * auVar42._4_4_;
    fVar23 = fVar23 * fVar59 * auVar42._8_4_;
    fVar40 = fVar40 * fVar52 * auVar44._0_4_;
    fVar51 = fVar51 * fVar58 * auVar44._4_4_;
    fVar32 = fVar32 * fVar60 * auVar44._8_4_;
    fVar33 = fVar33 * fVar61 * auVar45._0_4_;
    fVar57 = fVar57 * fVar66 * auVar45._4_4_;
    fVar18 = fVar18 * fVar67 * auVar45._8_4_;
    lVar10 = CONCAT44(auVar113._0_4_ + auVar117._0_4_ + auVar113._4_4_ + auVar117._4_4_,
                      auVar109._0_4_ + auVar112._0_4_ + auVar109._4_4_ + auVar112._4_4_);
    fVar52 = -fVar22;
    fVar58 = -fVar31;
    fVar60 = -fVar23;
    fVar36 = -fVar40;
    fVar19 = -fVar51;
    fVar59 = -fVar32;
  }
  lVar1 = (long)param_2 + 1;
  param_1[lVar1 * 0xc + 0x41] = CONCAT44(0x3f800000,fVar15);
  param_1[lVar1 * 0xc + 0x40] = lVar14;
  param_1[lVar1 * 0xc + 0x43] = CONCAT44(0x3f800000,fVar34);
  param_1[lVar1 * 0xc + 0x42] = CONCAT44(fVar20,CONCAT22(uVar26,CONCAT11(uVar25,uVar24)));
  param_1[lVar1 * 0xc + 0x45] = CONCAT44(0x3f800000,fVar39);
  param_1[lVar1 * 0xc + 0x44] = CONCAT44(fVar21,CONCAT22(uVar30,CONCAT11(uVar29,uVar28)));
  param_1[lVar1 * 0xc + 0x47] = CONCAT44(0x3f800000,fVar16);
  param_1[lVar1 * 0xc + 0x46] = lVar12;
  param_1[lVar1 * 0xc + 0x49] = CONCAT44(0x3f800000,fVar17);
  param_1[lVar1 * 0xc + 0x48] = lVar13;
  param_1[lVar1 * 0xc + 0x4b] = CONCAT44(0x3f800000,fVar27);
  param_1[lVar1 * 0xc + 0x4a] = lVar10;
  *(float *)(param_1 + lVar1 * 0xc + 0xad) = fVar32;
  *(undefined4 *)((long)param_1 + lVar1 * 0x60 + 0x56c) = 0x3f800000;
  *(float *)(param_1 + lVar1 * 0xc + 0xac) = fVar40;
  *(float *)((long)param_1 + lVar1 * 0x60 + 0x564) = fVar51;
  *(float *)(param_1 + lVar1 * 0xc + 0xaf) = fVar60;
  *(undefined4 *)((long)param_1 + lVar1 * 0x60 + 0x57c) = 0x3f800000;
  *(float *)(param_1 + lVar1 * 0xc + 0xae) = fVar52;
  *(float *)((long)param_1 + lVar1 * 0x60 + 0x574) = fVar58;
  *(float *)(param_1 + lVar1 * 0xc + 0xb1) = fVar59;
  *(undefined4 *)((long)param_1 + lVar1 * 0x60 + 0x58c) = 0x3f800000;
  *(float *)(param_1 + lVar1 * 0xc + 0xb0) = fVar36;
  *(float *)((long)param_1 + lVar1 * 0x60 + 0x584) = fVar19;
  *(float *)(param_1 + lVar1 * 0xc + 0xb3) = fVar23;
  *(undefined4 *)((long)param_1 + lVar1 * 0x60 + 0x59c) = 0x3f800000;
  *(float *)(param_1 + lVar1 * 0xc + 0xb2) = fVar22;
  *(float *)((long)param_1 + lVar1 * 0x60 + 0x594) = fVar31;
  *(float *)(param_1 + lVar1 * 0xc + 0xb5) = fVar18;
  *(undefined4 *)((long)param_1 + lVar1 * 0x60 + 0x5ac) = 0x3f800000;
  *(float *)(param_1 + lVar1 * 0xc + 0xb4) = fVar33;
  *(float *)((long)param_1 + lVar1 * 0x60 + 0x5a4) = fVar57;
  *(float *)(param_1 + lVar1 * 0xc + 0xb7) = -fVar18;
  *(undefined4 *)((long)param_1 + lVar1 * 0x60 + 0x5bc) = 0x3f800000;
  *(float *)(param_1 + lVar1 * 0xc + 0xb6) = -fVar33;
  *(float *)((long)param_1 + lVar1 * 0x60 + 0x5b4) = -fVar57;
  *(undefined1 *)((long)param_1 + (long)param_2 + 0x941) = 1;
  return;
}

// ==== Aska::Camera::MakeLocalViewFrustumVertices(Aska::Vector*, int)
// vaddr 0x20eefdc | ghidra 0x21eefdc | size 1044 | symbol _ZN4Aska6Camera28MakeLocalViewFrustumVerticesEPNS_6VectorEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6Camera28MakeLocalViewFrustumVerticesEPNS_6VectorEi
               (long param_1,float *param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  float fVar6;
  float fVar7;
  ushort uVar8;
  long *plVar9;
  long lVar10;
  ushort *puVar11;
  long lVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  undefined1 uVar16;
  undefined1 uVar17;
  undefined2 uVar18;
  float fVar19;
  undefined1 uVar20;
  undefined1 uVar21;
  undefined2 uVar22;
  undefined1 uVar23;
  undefined1 uVar24;
  undefined2 uVar25;
  float fVar26;
  float fVar27;
  float fVar28;
  float fVar29;
  
  fVar26 = *(float *)(param_1 + 0xde4);
  fVar27 = *(float *)(param_1 + 0xed4);
  fVar28 = *(float *)(param_1 + 0xed8);
  fVar29 = *(float *)(param_1 + 0xed0);
  lVar12 = *(long *)PTR__ZN4Aska6Global22m_pRenderTargetManagerE_02cbfa00;
  if (param_3 == -1) {
    lVar10 = 0;
    plVar9 = (long *)0x0;
  }
  else {
    plVar9 = (long *)Aska::RenderTargetManagerGL::GetRenderTarget(unsigned int)(lVar12,(uint)*(byte *)(param_1 + 0xeae) | param_3 << 0x10);
    if (plVar9 == (long *)0x0) {
      return;
    }
    lVar10 = plVar9[1];
    if (lVar10 == 0) {
      return;
    }
  }
  fVar27 = fVar27 * 0.5;
  fVar28 = fVar28 * 0.5;
  fVar26 = (1.0 / fVar26) * ((fVar27 / fVar28) / fVar29);
  if ((*(byte *)(param_1 + 0xeb3) & 1) == 0) {
    fVar29 = 1.0 / *(float *)(param_1 + 0xdf4);
    fVar19 = *(float *)(param_1 + 0xe04) * fVar29;
    fVar29 = fVar29 * *(float *)(param_1 + 0xe00);
    if (param_3 == -1) {
      if (*(char *)(param_1 + 0xeae) == '\0') {
        fVar15 = (float)NEON_ucvtf((uint)*(byte *)(lVar12 + 0xb1));
        fVar13 = (float)NEON_ucvtf((uint)*(byte *)(lVar12 + 0xb0));
        fVar28 = fVar28 + fVar15;
        fVar27 = fVar27 + fVar13;
      }
      fVar15 = -fVar27;
      uVar16 = SUB41(fVar15,0);
      uVar17 = (undefined1)((uint)fVar15 >> 8);
      uVar18 = (undefined2)((uint)fVar15 >> 0x10);
      fVar15 = -fVar28;
      uVar20 = SUB41(fVar15,0);
      uVar21 = (undefined1)((uint)fVar15 >> 8);
      uVar22 = (undefined2)((uint)fVar15 >> 0x10);
    }
    else {
      puVar11 = (ushort *)*plVar9;
      fVar15 = (float)NEON_ucvtf((uint)puVar11[6]);
      fVar13 = (float)NEON_ucvtf((uint)puVar11[7]);
      fVar6 = (float)NEON_ucvtf((uint)puVar11[4]);
      fVar6 = (fVar15 - fVar27) - fVar6;
      uVar16 = SUB41(fVar6,0);
      uVar17 = (undefined1)((uint)fVar6 >> 8);
      uVar18 = (undefined2)((uint)fVar6 >> 0x10);
      fVar7 = (float)NEON_ucvtf((uint)puVar11[5]);
      fVar7 = (fVar13 - fVar28) - fVar7;
      fVar27 = (float)NEON_ucvtf((uint)*puVar11);
      fVar15 = (float)NEON_ucvtf((uint)puVar11[1]);
      fVar28 = -fVar7;
      fVar27 = fVar6 + fVar27;
      fVar15 = fVar28 - fVar15;
      uVar20 = SUB41(fVar15,0);
      uVar21 = (undefined1)((uint)fVar15 >> 8);
      uVar22 = (undefined2)((uint)fVar15 >> 0x10);
      if ((*(ushort *)(lVar10 + 6) != 0 || *(ushort *)(lVar10 + 4) != 0) ||
          *(ushort *)(lVar10 + 8) != 0) {
        uVar8 = puVar11[8];
        iVar3 = (uint)*(ushort *)(lVar10 + 4) - (uint)*(byte *)(lVar12 + 0xb0);
        iVar4 = (uint)*(ushort *)(lVar10 + 8) - (uint)*(byte *)(lVar12 + 0xb2);
        iVar2 = iVar4;
        if ((uVar8 & 1) == 0) {
          iVar2 = iVar3;
        }
        iVar5 = (uint)*(ushort *)(lVar10 + 6) - (uint)*(byte *)(lVar12 + 0xb1);
        iVar1 = iVar4;
        if ((uVar8 & 2) == 0) {
          iVar1 = iVar3;
        }
        fVar6 = fVar6 + (float)iVar2;
        uVar16 = SUB41(fVar6,0);
        uVar17 = (undefined1)((uint)fVar6 >> 8);
        uVar18 = (undefined2)((uint)fVar6 >> 0x10);
        iVar2 = iVar4;
        if ((uVar8 & 4) == 0) {
          iVar2 = iVar5;
        }
        fVar27 = fVar27 - (float)iVar1;
        if ((uVar8 & 8) == 0) {
          iVar4 = iVar5;
        }
        fVar28 = (float)iVar2 - fVar7;
        fVar15 = fVar15 - (float)iVar4;
        uVar20 = SUB41(fVar15,0);
        uVar21 = (undefined1)((uint)fVar15 >> 8);
        uVar22 = (undefined2)((uint)fVar15 >> 0x10);
      }
    }
    fVar7 = *(float *)(param_1 + 0xd50);
    fVar13 = *(float *)(param_1 + 0xd54);
    param_2[2] = *(float *)(param_1 + 0xe04);
    fVar15 = (float)CONCAT22(uVar18,CONCAT11(uVar17,uVar16)) + fVar7;
    fVar14 = fVar26 * (fVar28 + fVar13);
    fVar26 = fVar26 * ((float)CONCAT22(uVar22,CONCAT11(uVar21,uVar20)) + fVar13);
    fVar13 = fVar19 * fVar15;
    fVar6 = fVar19 * fVar26;
    param_2[3] = 1.0;
    *param_2 = fVar13;
    param_2[1] = fVar6;
    fVar28 = *(float *)(param_1 + 0xe04);
    fVar27 = fVar27 + fVar7;
    fVar7 = fVar19 * fVar27;
    param_2[4] = fVar7;
    param_2[5] = fVar6;
    param_2[6] = fVar28;
    param_2[7] = 1.0;
    fVar28 = *(float *)(param_1 + 0xe04);
    fVar19 = fVar19 * fVar14;
    param_2[8] = fVar7;
    param_2[9] = fVar19;
    fVar15 = fVar29 * fVar15;
    param_2[10] = fVar28;
    param_2[0xb] = 1.0;
    fVar28 = *(float *)(param_1 + 0xe04);
    param_2[0xc] = fVar13;
    param_2[0xd] = fVar19;
    fVar26 = fVar29 * fVar26;
    fVar27 = fVar29 * fVar27;
    param_2[0xe] = fVar28;
    param_2[0xf] = 1.0;
    fVar28 = *(float *)(param_1 + 0xe00);
    param_2[0x10] = fVar15;
    param_2[0x11] = fVar26;
    fVar29 = fVar29 * fVar14;
    param_2[0x12] = fVar28;
    param_2[0x13] = 1.0;
    fVar28 = *(float *)(param_1 + 0xe00);
    param_2[0x14] = fVar27;
    param_2[0x15] = fVar26;
    param_2[0x16] = fVar28;
    param_2[0x17] = 1.0;
    fVar28 = *(float *)(param_1 + 0xe00);
    param_2[0x18] = fVar27;
    param_2[0x19] = fVar29;
    param_2[0x1a] = fVar28;
    param_2[0x1b] = 1.0;
    fVar27 = *(float *)(param_1 + 0xe00);
    param_2[0x1c] = fVar15;
    param_2[0x1d] = fVar29;
    param_2[0x1e] = fVar27;
    param_2[0x1f] = 1.0;
  }
  else {
    fVar19 = *(float *)(param_1 + 0xe08) * 0.5;
    fVar29 = fVar19 / fVar27;
    fVar26 = fVar26 * (((fVar28 / fVar27) * fVar19) / fVar28);
    if (param_3 == -1) {
      if (*(char *)(param_1 + 0xeae) == '\0') {
        fVar19 = (float)NEON_ucvtf((uint)*(byte *)(lVar12 + 0xb1));
        fVar15 = (float)NEON_ucvtf((uint)*(byte *)(lVar12 + 0xb0));
        fVar28 = fVar28 + fVar19;
        fVar27 = fVar27 + fVar15;
      }
      fVar19 = *(float *)(param_1 + 0xd50) - fVar27;
      uVar20 = SUB41(fVar19,0);
      uVar21 = (undefined1)((uint)fVar19 >> 8);
      uVar22 = (undefined2)((uint)fVar19 >> 0x10);
      fVar27 = fVar27 + *(float *)(param_1 + 0xd50);
      uVar16 = SUB41(fVar27,0);
      uVar17 = (undefined1)((uint)fVar27 >> 8);
      uVar18 = (undefined2)((uint)fVar27 >> 0x10);
      fVar27 = fVar28 + *(float *)(param_1 + 0xd54);
      uVar23 = SUB41(fVar27,0);
      uVar24 = (undefined1)((uint)fVar27 >> 8);
      uVar25 = (undefined2)((uint)fVar27 >> 0x10);
      fVar28 = *(float *)(param_1 + 0xd54) - fVar28;
    }
    else {
      puVar11 = (ushort *)*plVar9;
      fVar15 = (float)NEON_ucvtf((uint)puVar11[6]);
      fVar6 = (float)NEON_ucvtf((uint)puVar11[7]);
      fVar13 = (float)NEON_ucvtf((uint)puVar11[5]);
      fVar19 = (float)NEON_ucvtf((uint)puVar11[4]);
      fVar13 = (fVar6 - fVar28) - fVar13;
      fVar19 = (fVar15 - fVar27) - fVar19;
      fVar28 = (float)NEON_ucvtf((uint)puVar11[1]);
      fVar15 = fVar19 + *(float *)(param_1 + 0xd50);
      uVar20 = SUB41(fVar15,0);
      uVar21 = (undefined1)((uint)fVar15 >> 8);
      uVar22 = (undefined2)((uint)fVar15 >> 0x10);
      fVar27 = (float)NEON_ucvtf((uint)*puVar11);
      fVar27 = fVar19 + fVar27 + *(float *)(param_1 + 0xd50);
      uVar16 = SUB41(fVar27,0);
      uVar17 = (undefined1)((uint)fVar27 >> 8);
      uVar18 = (undefined2)((uint)fVar27 >> 0x10);
      fVar19 = *(float *)(param_1 + 0xd54) - fVar13;
      uVar23 = SUB41(fVar19,0);
      uVar24 = (undefined1)((uint)fVar19 >> 8);
      uVar25 = (undefined2)((uint)fVar19 >> 0x10);
      fVar28 = (-fVar13 - fVar28) + *(float *)(param_1 + 0xd54);
      if ((*(ushort *)(lVar10 + 6) != 0 || *(ushort *)(lVar10 + 4) != 0) ||
          *(ushort *)(lVar10 + 8) != 0) {
        uVar8 = puVar11[8];
        iVar3 = (uint)*(ushort *)(lVar10 + 4) - (uint)*(byte *)(lVar12 + 0xb0);
        iVar4 = (uint)*(ushort *)(lVar10 + 8) - (uint)*(byte *)(lVar12 + 0xb2);
        iVar2 = iVar4;
        if ((uVar8 & 1) == 0) {
          iVar2 = iVar3;
        }
        iVar5 = (uint)*(ushort *)(lVar10 + 6) - (uint)*(byte *)(lVar12 + 0xb1);
        iVar1 = iVar4;
        if ((uVar8 & 2) == 0) {
          iVar1 = iVar3;
        }
        fVar15 = fVar15 + (float)iVar2;
        uVar20 = SUB41(fVar15,0);
        uVar21 = (undefined1)((uint)fVar15 >> 8);
        uVar22 = (undefined2)((uint)fVar15 >> 0x10);
        iVar2 = iVar4;
        if ((uVar8 & 4) == 0) {
          iVar2 = iVar5;
        }
        fVar27 = fVar27 - (float)iVar1;
        uVar16 = SUB41(fVar27,0);
        uVar17 = (undefined1)((uint)fVar27 >> 8);
        uVar18 = (undefined2)((uint)fVar27 >> 0x10);
        if ((uVar8 & 8) == 0) {
          iVar4 = iVar5;
        }
        fVar19 = fVar19 + (float)iVar2;
        uVar23 = SUB41(fVar19,0);
        uVar24 = (undefined1)((uint)fVar19 >> 8);
        uVar25 = (undefined2)((uint)fVar19 >> 0x10);
        fVar28 = fVar28 - (float)iVar4;
      }
    }
    fVar27 = *(float *)(param_1 + 0xe04);
    fVar15 = fVar29 * (float)CONCAT22(uVar22,CONCAT11(uVar21,uVar20));
    fVar19 = fVar26 * (float)CONCAT22(uVar25,CONCAT11(uVar24,uVar23));
    *param_2 = fVar15;
    param_2[1] = fVar19;
    param_2[2] = fVar27;
    param_2[3] = 1.0;
    fVar27 = *(float *)(param_1 + 0xe04);
    fVar29 = fVar29 * (float)CONCAT22(uVar18,CONCAT11(uVar17,uVar16));
    param_2[4] = fVar29;
    param_2[5] = fVar19;
    fVar26 = fVar26 * fVar28;
    param_2[6] = fVar27;
    param_2[7] = 1.0;
    fVar27 = *(float *)(param_1 + 0xe04);
    param_2[8] = fVar15;
    param_2[9] = fVar26;
    param_2[10] = fVar27;
    param_2[0xb] = 1.0;
    fVar27 = *(float *)(param_1 + 0xe04);
    param_2[0xc] = fVar29;
    param_2[0xd] = fVar26;
    param_2[0xe] = fVar27;
    param_2[0xf] = 1.0;
    fVar27 = *(float *)(param_1 + 0xe00);
    param_2[0x10] = fVar15;
    param_2[0x11] = fVar19;
    param_2[0x12] = fVar27;
    param_2[0x13] = 1.0;
    fVar27 = *(float *)(param_1 + 0xe00);
    param_2[0x14] = fVar29;
    param_2[0x15] = fVar19;
    param_2[0x16] = fVar27;
    param_2[0x17] = 1.0;
    fVar27 = *(float *)(param_1 + 0xe00);
    param_2[0x18] = fVar15;
    param_2[0x19] = fVar26;
    param_2[0x1a] = fVar27;
    param_2[0x1b] = 1.0;
    fVar27 = *(float *)(param_1 + 0xe00);
    param_2[0x1c] = fVar29;
    param_2[0x1d] = fVar26;
    param_2[0x1e] = fVar27;
    param_2[0x1f] = 1.0;
  }
  return;
}

// ==== Aska::TArray<Aska::Camera::AFPoint, true>::~TArray()
// vaddr 0x20ef458 | ghidra 0x21ef458 | size 60 | symbol _ZN4Aska6TArrayINS_6Camera7AFPointELb1EED0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6TArrayINS_6Camera7AFPointELb1EED0Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska6TArrayINS_6Camera7AFPointELb1EEE_02cba8f0 + 0x10);
  *(ushort *)((long)param_1 + 0x32) = *(ushort *)((long)param_1 + 0x32) | 1;
  if (param_1[1] != 0) {
    operator delete[](void*)();
  }
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::CameraManager::CreateCamera(Aska::CameraManager::CameraType::desc, float)
// vaddr 0x20f065c | ghidra 0x21f065c | size 516 | symbol _ZN4Aska13CameraManager12CreateCameraENS0_10CameraType4descEf | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8
_ZN4Aska13CameraManager12CreateCameraENS0_10CameraType4descEf(undefined8 param_1,undefined4 param_2)

{
  undefined8 uVar1;
  undefined8 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined1 auStack_18 [8];
  
  Aska::CameraFactory::CameraFactory()(auStack_18);
  uVar3 = _UNK_027dab9c;
  uVar4 = _UNK_02951638;
  switch(param_2) {
  case 0:
    uVar3 = 0x40000000;
    uVar4 = uVar3;
    break;
  case 1:
    uVar3 = 0x40000000;
    uVar4 = uVar3;
    goto code_r0x021f0838;
  case 2:
    uVar3 = 0x3f800000;
    uVar4 = uVar3;
    break;
  case 3:
    uVar3 = 0x3f800000;
    uVar4 = uVar3;
    goto code_r0x021f0838;
  case 4:
    uVar3 = 0x3f800000;
    uVar2 = 1;
    uVar4 = 0x3f800000;
    uVar1 = 0;
    goto code_r0x021f083c;
  case 5:
    uVar3 = 0x3f800000;
    uVar2 = 1;
    uVar1 = 1;
    uVar4 = 0x3f800000;
    goto code_r0x021f083c;
  case 6:
    uVar3 = _UNK_029c9a48;
    uVar4 = 0x3f800000;
    break;
  case 7:
    uVar3 = _UNK_029c9a48;
    uVar4 = 0x3f800000;
    goto code_r0x021f0838;
  case 8:
    uVar4 = 0x3f800000;
    uVar3 = _UNK_029c9a48;
    goto code_r0x021f07f0;
  case 9:
    uVar4 = 0x3f800000;
    uVar3 = _UNK_029c9a48;
    goto code_r0x021f0810;
  case 10:
    uVar3 = 0x3f800000;
    uVar4 = 0x3f100000;
    break;
  case 0xb:
    uVar3 = 0x3f800000;
    uVar4 = 0x3f100000;
    goto code_r0x021f0838;
  case 0xc:
    uVar3 = 0x3f800000;
    uVar4 = 0x3f100000;
    goto code_r0x021f07f0;
  case 0xd:
    uVar3 = 0x3f800000;
    uVar4 = 0x3f100000;
    goto code_r0x021f0810;
  case 0xe:
    uVar4 = _UNK_02951638;
    break;
  case 0xf:
    uVar4 = _UNK_02951638;
    goto code_r0x021f0838;
  case 0x10:
    goto code_r0x021f07f0;
  case 0x11:
    goto code_r0x021f0810;
  case 0x12:
    uVar3 = _UNK_029c9a40;
    uVar4 = _UNK_029c9a44;
    break;
  case 0x13:
    uVar3 = _UNK_029c9a40;
    uVar4 = _UNK_029c9a44;
code_r0x021f0838:
    uVar1 = 1;
    uVar2 = 0;
    goto code_r0x021f083c;
  case 0x14:
    uVar3 = _UNK_029c9a40;
    uVar4 = _UNK_029c9a44;
code_r0x021f07f0:
    uVar2 = 1;
    uVar1 = 0;
    goto code_r0x021f083c;
  case 0x15:
    uVar3 = _UNK_029c9a40;
    uVar4 = _UNK_029c9a44;
code_r0x021f0810:
    uVar2 = 1;
    uVar1 = 1;
    goto code_r0x021f083c;
  default:
    uVar2 = 0;
    goto code_r0x021f0848;
  }
  uVar2 = 0;
  uVar1 = 0;
code_r0x021f083c:
  uVar2 = Aska::CameraFactory::CreateCamera(float, float, Aska::CameraFactory::OriginType::desc, Aska::CameraFactory::ProjectionType::desc, float) const(uVar3,uVar4,param_1,auStack_18,uVar2,uVar1);
code_r0x021f0848:
  Aska::CameraFactory::~CameraFactory()(auStack_18);
  return uVar2;
}

// ==== Aska::CameraManager::~CameraManager()
// vaddr 0x20f09f4 | ghidra 0x21f09f4 | size 80 | symbol _ZN4Aska13CameraManagerD1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13CameraManagerD2Ev(long *param_1)

{
  undefined *puVar1;
  long *plVar2;
  
  plVar2 = (long *)param_1[0x1ff];
  puVar1 = PTR__ZTVN4Aska13CameraManagerE_02cbb9d0 + 0xb8;
  *param_1 = (long)(PTR__ZTVN4Aska13CameraManagerE_02cbb9d0 + 0x10);
  param_1[5] = (long)puVar1;
  if (plVar2 != (long *)0x0) {
    (**(code **)(*plVar2 + 0x38))(plVar2,0);
    param_1[0x1ff] = 0;
  }
  Aska::CameraFilterManager::~CameraFilterManager()(param_1 + 0x200);
  (*(code *)PTR__ZN4Aska11TaskManagerD2Ev_02ca45c0)(param_1);
  return;
}

// ==== non-virtual thunk to Aska::CameraManager::~CameraManager()
// vaddr 0x20f0a44 | ghidra 0x21f0a44 | size 92 | symbol _ZThn40_N4Aska13CameraManagerD1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZThn40_N4Aska13CameraManagerD1Ev(long *param_1)

{
  undefined *puVar1;
  long *plVar2;
  
  puVar1 = PTR__ZTVN4Aska13CameraManagerE_02cbb9d0;
  param_1[-5] = (long)(PTR__ZTVN4Aska13CameraManagerE_02cbb9d0 + 0x10);
  plVar2 = (long *)param_1[0x1fa];
  *param_1 = (long)(puVar1 + 0xb8);
  if (plVar2 != (long *)0x0) {
    (**(code **)(*plVar2 + 0x38))(plVar2,0);
    param_1[0x1fa] = 0;
  }
  Aska::CameraFilterManager::~CameraFilterManager()(param_1 + 0x1fb);
  (*(code *)PTR__ZN4Aska11TaskManagerD2Ev_02ca45c0)(param_1 + -5);
  return;
}

// ==== Aska::CameraManager::~CameraManager()
// vaddr 0x20f0aa0 | ghidra 0x21f0aa0 | size 88 | symbol _ZN4Aska13CameraManagerD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13CameraManagerD0Ev(long *param_1)

{
  undefined *puVar1;
  long *plVar2;
  
  plVar2 = (long *)param_1[0x1ff];
  puVar1 = PTR__ZTVN4Aska13CameraManagerE_02cbb9d0 + 0xb8;
  *param_1 = (long)(PTR__ZTVN4Aska13CameraManagerE_02cbb9d0 + 0x10);
  param_1[5] = (long)puVar1;
  if (plVar2 != (long *)0x0) {
    (**(code **)(*plVar2 + 0x38))(plVar2,0);
    param_1[0x1ff] = 0;
  }
  Aska::CameraFilterManager::~CameraFilterManager()(param_1 + 0x200);
  Aska::TaskManager::~TaskManager()(param_1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== non-virtual thunk to Aska::CameraManager::~CameraManager()
// vaddr 0x20f0af8 | ghidra 0x21f0af8 | size 100 | symbol _ZThn40_N4Aska13CameraManagerD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZThn40_N4Aska13CameraManagerD0Ev(long *param_1)

{
  undefined *puVar1;
  long *plVar2;
  long *plVar3;
  
  puVar1 = PTR__ZTVN4Aska13CameraManagerE_02cbb9d0;
  plVar3 = param_1 + -5;
  *plVar3 = (long)(PTR__ZTVN4Aska13CameraManagerE_02cbb9d0 + 0x10);
  plVar2 = (long *)param_1[0x1fa];
  *param_1 = (long)(puVar1 + 0xb8);
  if (plVar2 != (long *)0x0) {
    (**(code **)(*plVar2 + 0x38))(plVar2,0);
    param_1[0x1fa] = 0;
  }
  Aska::CameraFilterManager::~CameraFilterManager()(param_1 + 0x1fb);
  Aska::TaskManager::~TaskManager()(plVar3);
  (*(code *)PTR__ZdlPv_02ca4758)(plVar3);
  return;
}

// ==== Aska::CameraManager::Run(int)
// vaddr 0x20f0b5c | ghidra 0x21f0b5c | size 124 | symbol _ZN4Aska13CameraManager3RunEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13CameraManager3RunEi(long param_1)

{
  long *plVar1;
  long lVar2;
  long *plVar3;
  
  lVar2 = *(long *)(param_1 + 0xff8);
  if (lVar2 != 0) {
    plVar3 = (long *)0x0;
    if (*(long *)(lVar2 + 0xf0) != 0) {
      plVar3 = *(long **)(*(long *)(lVar2 + 0xf0) + 0xe8);
    }
    plVar1 = *(long **)(param_1 + 0xff0);
    if (plVar3 == plVar1) goto code_r0x021f0bb0;
    plVar3 = (long *)0x0;
    if (plVar1 != (long *)0x0) {
      plVar3 = plVar1 + 6;
    }
    Aska::HierarchicalObjectContainer::SwapParent(Aska::HierarchicalObjectContainer*)(lVar2 + 0x30,plVar3);
  }
  plVar1 = *(long **)(param_1 + 0xff0);
code_r0x021f0bb0:
  if (plVar1 != (long *)0x0) {
    (**(code **)(*plVar1 + 0xa8))();
  }
                    /* WARNING: Could not recover jumptable at 0x021f0bd4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(**(long **)(param_1 + 0x108) + 0x70))();
  return;
}

// ==== non-virtual thunk to Aska::CameraManager::Run(int)
// vaddr 0x20f0bd8 | ghidra 0x21f0bd8 | size 124 | symbol _ZThn40_N4Aska13CameraManager3RunEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZThn40_N4Aska13CameraManager3RunEi(long param_1)

{
  long *plVar1;
  long lVar2;
  long *plVar3;
  
  lVar2 = *(long *)(param_1 + 0xfd0);
  if (lVar2 != 0) {
    plVar3 = (long *)0x0;
    if (*(long *)(lVar2 + 0xf0) != 0) {
      plVar3 = *(long **)(*(long *)(lVar2 + 0xf0) + 0xe8);
    }
    plVar1 = *(long **)(param_1 + 0xfc8);
    if (plVar3 == plVar1) goto code_r0x021f0c2c;
    plVar3 = (long *)0x0;
    if (plVar1 != (long *)0x0) {
      plVar3 = plVar1 + 6;
    }
    Aska::HierarchicalObjectContainer::SwapParent(Aska::HierarchicalObjectContainer*)(lVar2 + 0x30,plVar3);
  }
  plVar1 = *(long **)(param_1 + 0xfc8);
code_r0x021f0c2c:
  if (plVar1 != (long *)0x0) {
    (**(code **)(*plVar1 + 0xa8))();
  }
                    /* WARNING: Could not recover jumptable at 0x021f0c50. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(**(long **)(param_1 + 0xe0) + 0x70))();
  return;
}

// ==== Aska::CameraManager::InitScreenEffectCamera()
// vaddr 0x20f0c54 | ghidra 0x21f0c54 | size 120 | symbol _ZN4Aska13CameraManager22InitScreenEffectCameraEv | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska13CameraManager22InitScreenEffectCameraEv(long param_1)

{
  long lVar1;
  
  if (*(long *)(param_1 + 0xff8) != 0) {
    return;
  }
  lVar1 = operator new(unsigned long, std::nothrow_t const&)(0xf90,PTR__ZSt7nothrow_02cb9a80);
  if (lVar1 != 0) {
    Aska::Camera::Camera()(lVar1);
  }
  *(long *)(param_1 + 0xff8) = lVar1;
  Aska::Camera::Default()(lVar1);
  lVar1 = *(long *)(param_1 + 0xff8);
  if (*(long *)(lVar1 + 0xe10) != 0) {
    Aska::Lens::SetBaseView(float)(_UNK_027f7284);
    lVar1 = *(long *)(param_1 + 0xff8);
  }
  (*(code *)PTR__ZN4Aska11TaskManager3AddEPNS_4TaskE_02c95ab0)(param_1,lVar1);
  return;
}

// ==== Aska::CameraManager::UpdateAllCameras()
// vaddr 0x20f0ccc | ghidra 0x21f0ccc | size 64 | symbol _ZN4Aska13CameraManager16UpdateAllCamerasEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13CameraManager16UpdateAllCamerasEv(long param_1)

{
  long lVar1;
  
  for (lVar1 = *(long *)(param_1 + 0x18); param_1 + 8 != lVar1; lVar1 = *(long *)(lVar1 + 0x10)) {
    *(ushort *)(lVar1 + 0xeb3) = *(ushort *)(lVar1 + 0xeb3) | 2;
    *(byte *)(lVar1 + 0x128) = *(byte *)(lVar1 + 0x128) & 0xe0 | 1;
  }
  return;
}

// ==== Aska::CameraManager::AdjustAllCameraEV(int)
// vaddr 0x20f0d0c | ghidra 0x21f0d0c | size 72 | symbol _ZN4Aska13CameraManager17AdjustAllCameraEVEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13CameraManager17AdjustAllCameraEVEi(long param_1,uint param_2)

{
  long lVar1;
  
  for (lVar1 = *(long *)(param_1 + 0x18); param_1 + 8 != lVar1; lVar1 = *(long *)(lVar1 + 0x10)) {
    if (*(byte *)(lVar1 + 0xeae) == param_2) {
      Aska::Camera::AdjustCameraEV()(lVar1);
    }
  }
  return;
}

// ==== Aska::CameraManager::UpdatePrevView()
// vaddr 0x20f0d54 | ghidra 0x21f0d54 | size 56 | symbol _ZN4Aska13CameraManager14UpdatePrevViewEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13CameraManager14UpdatePrevViewEv(long param_1)

{
  long lVar1;
  
  for (lVar1 = *(long *)(param_1 + 0x18); param_1 + 8 != lVar1; lVar1 = *(long *)(lVar1 + 0x10)) {
    *(undefined8 *)(lVar1 + 0xd68) = *(undefined8 *)(lVar1 + 0x138);
    *(undefined8 *)(lVar1 + 0xd60) = *(undefined8 *)(lVar1 + 0x130);
    *(undefined8 *)(lVar1 + 0xd78) = *(undefined8 *)(lVar1 + 0x148);
    *(undefined8 *)(lVar1 + 0xd70) = *(undefined8 *)(lVar1 + 0x140);
    *(undefined8 *)(lVar1 + 0xd88) = *(undefined8 *)(lVar1 + 0x158);
    *(undefined8 *)(lVar1 + 0xd80) = *(undefined8 *)(lVar1 + 0x150);
    *(undefined8 *)(lVar1 + 0xd98) = *(undefined8 *)(lVar1 + 0x168);
    *(undefined8 *)(lVar1 + 0xd90) = *(undefined8 *)(lVar1 + 0x160);
  }
  return;
}

// ==== Aska::CameraManager::UpdateProjectorRects(int)
// vaddr 0x20f0d8c | ghidra 0x21f0d8c | size 188 | symbol _ZN4Aska13CameraManager20UpdateProjectorRectsEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13CameraManager20UpdateProjectorRectsEi(long param_1,uint param_2)

{
  float fVar1;
  uint uVar2;
  long lVar3;
  ushort *puVar4;
  float fVar5;
  
  lVar3 = Aska::RenderTargetManagerGL::GetRenderTarget(unsigned int)(*(undefined8 *)PTR__ZN4Aska6Global22m_pRenderTargetManagerE_02cbfa00);
  if (lVar3 != 0) {
    puVar4 = *(ushort **)(lVar3 + 8);
    if (puVar4 == (ushort *)0x0) {
      uVar2 = Aska::RenderTarget::GetWidth() const(lVar3);
      fVar5 = (float)uVar2;
      uVar2 = Aska::RenderTarget::GetHeight() const(lVar3);
      fVar1 = (float)uVar2;
    }
    else {
      fVar5 = (float)NEON_ucvtf((uint)*puVar4);
      fVar1 = (float)NEON_ucvtf((uint)puVar4[1]);
    }
    for (lVar3 = *(long *)(param_1 + 0x18); param_1 + 8 != lVar3; lVar3 = *(long *)(lVar3 + 0x10)) {
      if (*(byte *)(lVar3 + 0xeae) == param_2) {
        *(float *)(lVar3 + 0xed4) = fVar5;
        *(float *)(lVar3 + 0xed8) = fVar1;
        *(ushort *)(lVar3 + 0xeb3) = *(ushort *)(lVar3 + 0xeb3) | 2;
      }
    }
  }
  return;
}

// ==== Aska::CameraManager::Get(unsigned long, void*) const
// vaddr 0x20f0e48 | ghidra 0x21f0e48 | size 8 | symbol _ZNK4Aska13CameraManager3GetEmPv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska13CameraManager3GetEmPv(void)

{
  return 0;
}

// ==== non-virtual thunk to Aska::CameraManager::Get(unsigned long, void*) const
// vaddr 0x20f0e50 | ghidra 0x21f0e50 | size 8 | symbol _ZThn40_NK4Aska13CameraManager3GetEmPv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZThn40_NK4Aska13CameraManager3GetEmPv(void)

{
  return 0;
}

// ==== Aska::CameraManager::GetClassID(int) const
// vaddr 0x20f0e58 | ghidra 0x21f0e58 | size 88 | symbol _ZNK4Aska13CameraManager10GetClassIDEi | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska13CameraManager10GetClassIDEi(undefined8 param_1,int param_2)

{
  undefined8 uVar1;
  undefined8 uVar2;
  
  if (param_2 == 0) {
    return 0xf002f003f008;
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

// ==== Aska::CameraManager::GetDefaultLevel() const
// vaddr 0x20f0eb0 | ghidra 0x21f0eb0 | size 8 | symbol _ZNK4Aska13CameraManager15GetDefaultLevelEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska13CameraManager15GetDefaultLevelEv(void)

{
  return 0x1000;
}

// ==== non-virtual thunk to Aska::CameraManager::GetClassID(int) const
// vaddr 0x20f0eb8 | ghidra 0x21f0eb8 | size 88 | symbol _ZThn40_NK4Aska13CameraManager10GetClassIDEi | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZThn40_NK4Aska13CameraManager10GetClassIDEi(undefined8 param_1,int param_2)

{
  undefined8 uVar1;
  undefined8 uVar2;
  
  if (param_2 == 0) {
    return 0xf002f003f008;
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

// ==== non-virtual thunk to Aska::CameraManager::GetDefaultLevel() const
// vaddr 0x20f0f10 | ghidra 0x21f0f10 | size 8 | symbol _ZThn40_NK4Aska13CameraManager15GetDefaultLevelEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZThn40_NK4Aska13CameraManager15GetDefaultLevelEv(void)

{
  return 0x1000;
}

// ==== Aska::AimingObject::MakeMatrixMain()
// vaddr 0x23577c8 | ghidra 0x24577c8 | size 448 | symbol _ZN4Aska12AimingObject14MakeMatrixMainEv | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska12AimingObject14MakeMatrixMainEv(long *param_1)

{
  long lVar1;
  long *plVar2;
  undefined4 uVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  undefined8 uStack_b0;
  undefined8 uStack_a8;
  undefined1 auStack_a0 [64];
  float fStack_60;
  float fStack_5c;
  float fStack_58;
  undefined4 uStack_54;
  float fStack_50;
  float fStack_4c;
  float fStack_48;
  undefined4 uStack_44;
  
  plVar2 = &uStack_b0;
  lVar1 = (**(code **)(*(long *)param_1[0x36] + 0x98))();
  fVar5 = *(float *)(lVar1 + 0xc);
  fVar7 = *(float *)(lVar1 + 0x1c);
  fVar9 = *(float *)(lVar1 + 0x2c);
  uStack_44 = 0x3f800000;
  lVar1 = (**(code **)(*param_1 + 0x98))(param_1);
  fVar8 = *(float *)(lVar1 + 0xc);
  fVar6 = *(float *)(lVar1 + 0x1c);
  fVar4 = *(float *)(lVar1 + 0x2c);
  uStack_44 = 0x3f800000;
  fStack_50 = fVar5 - fVar8;
  fStack_4c = fVar7 - fVar6;
  fStack_48 = fVar9 - fVar4;
  uStack_54 = 0x3f800000;
  fStack_60 = fVar8;
  fStack_5c = fVar6;
  fStack_58 = fVar4;
  if ((long *)param_1[0x37] == (long *)0x0) {
    if ((fStack_50 != 0.0) || (fStack_48 != 0.0)) {
      uVar3 = (undefined4)param_1[0x3e];
      plVar2 = param_1 + 0x34;
      goto code_r0x024578f0;
    }
    uStack_a8 = _UNK_027f7c08;
    uStack_b0 = _UNK_027f7c00;
    if (0.0 < fStack_4c) {
      uStack_a8._4_4_ = (undefined4)((ulong)_UNK_027f7c08 >> 0x20);
      uStack_a8 = CONCAT44(uStack_a8._4_4_,0xbf800000);
    }
  }
  else {
    lVar1 = (**(code **)(*(long *)param_1[0x37] + 0x98))();
    fVar8 = *(float *)(lVar1 + 0xc) - fVar8;
    fVar6 = *(float *)(lVar1 + 0x1c) - fVar6;
    fVar4 = *(float *)(lVar1 + 0x2c) - fVar4;
    fVar7 = fVar8 * fVar8 + fVar6 * fVar6 + fVar4 * fVar4;
    fVar5 = SQRT(fVar7);
    uStack_b0 = CONCAT44(fVar6,fVar8);
    uStack_a8 = CONCAT44(0x3f800000,fVar4);
    if (NAN(fVar5)) {
      fVar5 = (float)sqrtf(fVar7);
    }
    if (_UNK_027e519c <= fVar5) {
      fVar5 = 1.0 / fVar5;
      uStack_b0 = CONCAT44(fVar5 * fVar6,fVar5 * fVar8);
      uStack_a8 = CONCAT44(uStack_a8._4_4_,fVar5 * fVar4);
    }
  }
  uVar3 = (undefined4)param_1[0x3e];
code_r0x024578f0:
  Aska::Matrix::SetLookAtMatrixZPUp(Aska::Vector const*, Aska::Vector const*, Aska::Vector const*, float)(uVar3,auStack_a0,&fStack_60,&fStack_50,plVar2);
  Aska::Matrix::SetTranslate(Aska::Vector const*)(auStack_a0,&fStack_60);
  (**(code **)(*param_1 + 0xa0))(param_1,auStack_a0);
  if (*(char *)((long)param_1 + 500) != '\0') {
    Aska::HierarchicalObjectContainer::MakeTransformParam()(param_1 + 6);
  }
  return;
}

// ==== Aska::AimingObject::MakeMatrix()
// vaddr 0x2357988 | ghidra 0x2457988 | size 92 | symbol _ZN4Aska12AimingObject10MakeMatrixEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska12AimingObject10MakeMatrixEv(long param_1)

{
  long *plVar1;
  
  Aska::HierarchicalObjectContainer::MakeMatrix()(param_1 + 0x30);
  plVar1 = *(long **)(param_1 + 0x1b0);
  if (plVar1 != (long *)0x0) {
    if ((*(byte *)(plVar1 + 0x25) & 1) != 0) {
      (**(code **)(*plVar1 + 0xa8))();
    }
    plVar1 = *(long **)(param_1 + 0x1b8);
    if ((plVar1 != (long *)0x0) && ((*(byte *)(plVar1 + 0x25) & 1) != 0)) {
      (**(code **)(*plVar1 + 0xa8))();
    }
    (*(code *)PTR__ZN4Aska12AimingObject14MakeMatrixMainEv_02ca8d98)(param_1);
    return;
  }
  return;
}

// ==== Aska::AimingObject::Get(unsigned long, void*) const
// vaddr 0x23579e4 | ghidra 0x24579e4 | size 72 | symbol _ZNK4Aska12AimingObject3GetEmPv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska12AimingObject3GetEmPv(long param_1,ulong param_2,undefined4 *param_3)

{
  ulong uVar1;
  
  uVar1 = Aska::HierarchicalObject::Get(unsigned long, void*) const();
  if ((uVar1 & 1) == 0) {
    if ((param_2 & 0xffff0000ffff) != 0xf) {
      return 0;
    }
    *param_3 = *(undefined4 *)(param_1 + 0x1f0);
  }
  return 1;
}

// ==== Aska::AimingObject::Set(unsigned long, void const*)
// vaddr 0x2357a2c | ghidra 0x2457a2c | size 72 | symbol _ZN4Aska12AimingObject3SetEmPKv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska12AimingObject3SetEmPKv(long param_1,ulong param_2,undefined4 *param_3)

{
  ulong uVar1;
  
  uVar1 = Aska::HierarchicalObject::Set(unsigned long, void const*)();
  if ((uVar1 & 1) == 0) {
    if ((param_2 & 0xffff0000ffff) != 0xf) {
      return 0;
    }
    *(undefined4 *)(param_1 + 0x1f0) = *param_3;
  }
  return 1;
}

// ==== Aska::AimingObject::~AimingObject()
// vaddr 0x2357a74 | ghidra 0x2457a74 | size 100 | symbol _ZN4Aska12AimingObjectD2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska12AimingObjectD2Ev(long *param_1)

{
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
  (*(code *)PTR__ZN4Aska18HierarchicalObjectD2Ev_02ca75e8)();
  return;
}

// ==== Aska::AimingObject::~AimingObject()
// vaddr 0x2357ad8 | ghidra 0x2457ad8 | size 124 | symbol _ZN4Aska12AimingObjectD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska12AimingObjectD0Ev(long *param_1)

{
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
  Aska::HierarchicalObject::~HierarchicalObject()(param_1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::AimingObject::GetClassID(int) const
// vaddr 0x2357b54 | ghidra 0x2457b54 | size 92 | symbol _ZNK4Aska12AimingObject10GetClassIDEi | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska12AimingObject10GetClassIDEi(undefined8 param_1,int param_2)

{
  undefined8 uVar1;
  undefined8 uVar2;
  
  if (param_2 == 0) {
    return 0xf002f111f115;
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


// FAILED to create function at 029c9080 typeinfo name for Aska::TArray<Aska::Camera::AFPoint, true>
// FAILED to create function at 02c4b478 Aska::Camera::vtable
// FAILED to create function at 02c4b620 Aska::Camera::typeinfo
// FAILED to create function at 02c4b988 Aska::TArray<Aska::Camera::AFPoint,true>::vtable
// FAILED to create function at 02c4b9a8 Aska::TArray<Aska::Camera::AFPoint,true>::typeinfo
// FAILED to create function at 02c4bab8 Aska::CameraManager::vtable
// FAILED to create function at 02c4bc10 Aska::CameraManager::typeinfo
// FAILED to create function at 02c64f98 Aska::AimingObject::vtable
// FAILED to create function at 02c65120 Aska::AimingObject::typeinfo
// FAILED to create function at 02cc7b0c Aska::Camera::m_fCrossFadeSec
// FAILED to create function at 02cc7b10 Aska::Camera::m_fMasterMotionBlurRate
// FAILED to create function at 02cc7b20 Aska::Camera::m_avDisableFogConst
// FAILED to create function at 02dcddf8 Aska::Camera::m_cActiveTileNo
// FAILED to create function at 02dcde00 Aska::Camera::m_pCrossFader
