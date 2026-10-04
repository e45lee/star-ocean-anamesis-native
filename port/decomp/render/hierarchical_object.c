// port/decomp/render/hierarchical_object.c: Ghidra decompiles for the render subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-04 06:09 UTC: tools/decomp.sh '--into' 'render/hierarchical_object' 'Aska::Task::' 'Aska::HierarchicalObject::' 'Aska::HierarchicalObjectContainer::'
// run      2026-10-04 06:12 UTC: tools/decomp.sh '--into' 'render/hierarchical_object' 'Aska::IAnimatable::'

// ==== Aska::Task::GetClassID(int) const
// vaddr 0x120232c | ghidra 0x130232c | size 44 | symbol _ZNK4Aska4Task10GetClassIDEi | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska4Task10GetClassIDEi(undefined8 param_1,int param_2)

{
  undefined8 uVar1;
  undefined8 uVar2;
  
  uVar2 = 0xf000f001;
  if (param_2 != 1) {
    uVar2 = 0xf000;
  }
  uVar1 = 0xf000f001f002;
  if (param_2 != 0) {
    uVar1 = uVar2;
  }
  return uVar1;
}

// ==== Aska::Task::MessageHandler(unsigned int, int, void*, void*)
// vaddr 0x1202370 | ghidra 0x1302370 | size 8 | symbol _ZN4Aska4Task14MessageHandlerEjiPvS1_ | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska4Task14MessageHandlerEjiPvS1_(void)

{
  return 0;
}

// ==== Aska::Task::IsMulti() const
// vaddr 0x1202378 | ghidra 0x1302378 | size 8 | symbol _ZNK4Aska4Task7IsMultiEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska4Task7IsMultiEv(void)

{
  return 0;
}

// ==== Aska::Task::OnDeleteFromTaskManager()
// vaddr 0x1202380 | ghidra 0x1302380 | size 4 | symbol _ZN4Aska4Task23OnDeleteFromTaskManagerEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska4Task23OnDeleteFromTaskManagerEv(void)

{
  return;
}

// ==== Aska::Task::OnAddToTaskManager()
// vaddr 0x1202384 | ghidra 0x1302384 | size 4 | symbol _ZN4Aska4Task18OnAddToTaskManagerEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska4Task18OnAddToTaskManagerEv(void)

{
  return;
}

// ==== Aska::Task::OnAddTopToTaskManager()
// vaddr 0x1202388 | ghidra 0x1302388 | size 4 | symbol _ZN4Aska4Task21OnAddTopToTaskManagerEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska4Task21OnAddTopToTaskManagerEv(void)

{
  return;
}

// ==== Aska::Task::OnInsertToTaskManager()
// vaddr 0x120238c | ghidra 0x130238c | size 4 | symbol _ZN4Aska4Task21OnInsertToTaskManagerEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska4Task21OnInsertToTaskManagerEv(void)

{
  return;
}

// ==== Aska::Task::GetDefaultLevel() const
// vaddr 0x134e514 | ghidra 0x144e514 | size 8 | symbol _ZNK4Aska4Task15GetDefaultLevelEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska4Task15GetDefaultLevelEv(void)

{
  return 0x40;
}

// ==== Aska::HierarchicalObject::GetDefaultLevel() const
// vaddr 0x1e68bc8 | ghidra 0x1f68bc8 | size 8 | symbol _ZNK4Aska18HierarchicalObject15GetDefaultLevelEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska18HierarchicalObject15GetDefaultLevelEv(void)

{
  return 0x1000;
}

// ==== Aska::HierarchicalObject::WorldMatrix() const
// vaddr 0x1e68bd0 | ghidra 0x1f68bd0 | size 8 | symbol _ZNK4Aska18HierarchicalObject11WorldMatrixEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK4Aska18HierarchicalObject11WorldMatrixEv(long param_1)

{
  return param_1 + 0x40;
}

// ==== Aska::HierarchicalObject::SetPosition(float, float, float)
// vaddr 0x1e68be0 | ghidra 0x1f68be0 | size 76 | symbol _ZN4Aska18HierarchicalObject11SetPositionEfff | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18HierarchicalObject11SetPositionEfff
               (undefined4 param_1,undefined4 param_2,undefined4 param_3,long param_4)

{
  if ((*(byte *)(param_4 + 0x128) & 1) == 0) {
    Aska::HierarchicalObjectContainer::UpdateHierarchically()(param_4 + 0x30);
  }
  *(undefined4 *)(param_4 + 0x80) = param_1;
  *(undefined4 *)(param_4 + 0x84) = param_2;
  *(undefined4 *)(param_4 + 0x88) = param_3;
  *(undefined4 *)(param_4 + 0x8c) = 0x3f800000;
  return;
}

// ==== Aska::HierarchicalObject::SetPosition(Aska::Vector const*)
// vaddr 0x1e68c2c | ghidra 0x1f68c2c | size 76 | symbol _ZN4Aska18HierarchicalObject11SetPositionEPKNS_6VectorE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18HierarchicalObject11SetPositionEPKNS_6VectorE(long param_1,undefined4 *param_2)

{
  if ((*(byte *)(param_1 + 0x128) & 1) == 0) {
    Aska::HierarchicalObjectContainer::UpdateHierarchically()(param_1 + 0x30);
  }
  *(undefined4 *)(param_1 + 0x80) = *param_2;
  *(undefined4 *)(param_1 + 0x84) = param_2[1];
  *(undefined4 *)(param_1 + 0x88) = param_2[2];
  *(undefined4 *)(param_1 + 0x8c) = param_2[3];
  return;
}

// ==== Aska::HierarchicalObject::SetPosture(float, float, float)
// vaddr 0x1e68c78 | ghidra 0x1f68c78 | size 80 | symbol _ZN4Aska18HierarchicalObject10SetPostureEfff | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18HierarchicalObject10SetPostureEfff
               (undefined8 param_1,undefined8 param_2,undefined8 param_3,long param_4)

{
  if ((*(byte *)(param_4 + 0x128) & 1) == 0) {
    Aska::HierarchicalObjectContainer::UpdateHierarchically()(param_4 + 0x30);
  }
  (*(code *)PTR__ZN4Aska10Quaternion15CreateFromEulerEfff14EnumRotateType_02c9af00)
            (param_1,param_2,param_3,param_4 + 0x90,0);
  return;
}

// ==== Aska::HierarchicalObject::SetPosture(Aska::Vector const*)
// vaddr 0x1e68cc8 | ghidra 0x1f68cc8 | size 60 | symbol _ZN4Aska18HierarchicalObject10SetPostureEPKNS_6VectorE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18HierarchicalObject10SetPostureEPKNS_6VectorE(long param_1,undefined4 *param_2)

{
  if ((*(byte *)(param_1 + 0x128) & 1) == 0) {
    Aska::HierarchicalObjectContainer::UpdateHierarchically()(param_1 + 0x30);
  }
  (*(code *)PTR__ZN4Aska10Quaternion15CreateFromEulerEfff14EnumRotateType_02c9af00)
            (*param_2,param_2[1],param_2[2],param_1 + 0x90,0);
  return;
}

// ==== Aska::HierarchicalObject::SetPosture(Aska::Quaternion const*)
// vaddr 0x1e68d04 | ghidra 0x1f68d04 | size 76 | symbol _ZN4Aska18HierarchicalObject10SetPostureEPKNS_10QuaternionE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18HierarchicalObject10SetPostureEPKNS_10QuaternionE(long param_1,undefined4 *param_2)

{
  if ((*(byte *)(param_1 + 0x128) & 1) == 0) {
    Aska::HierarchicalObjectContainer::UpdateHierarchically()(param_1 + 0x30);
  }
  *(undefined4 *)(param_1 + 0x90) = *param_2;
  *(undefined4 *)(param_1 + 0x94) = param_2[1];
  *(undefined4 *)(param_1 + 0x98) = param_2[2];
  *(undefined4 *)(param_1 + 0x9c) = param_2[3];
  return;
}

// ==== Aska::HierarchicalObject::SetPosture(float, float, float, float)
// vaddr 0x1e68d50 | ghidra 0x1f68d50 | size 72 | symbol _ZN4Aska18HierarchicalObject10SetPostureEffff | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18HierarchicalObject10SetPostureEffff
               (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
               long param_5)

{
  if ((*(byte *)(param_5 + 0x128) & 1) == 0) {
    Aska::HierarchicalObjectContainer::UpdateHierarchically()(param_5 + 0x30);
  }
  *(undefined4 *)(param_5 + 0x90) = param_1;
  *(undefined4 *)(param_5 + 0x94) = param_2;
  *(undefined4 *)(param_5 + 0x98) = param_3;
  *(undefined4 *)(param_5 + 0x9c) = param_4;
  return;
}

// ==== Aska::HierarchicalObject::SetScale(float, float, float)
// vaddr 0x1e68d98 | ghidra 0x1f68d98 | size 68 | symbol _ZN4Aska18HierarchicalObject8SetScaleEfff | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18HierarchicalObject8SetScaleEfff
               (undefined4 param_1,undefined4 param_2,undefined4 param_3,long param_4)

{
  if ((*(byte *)(param_4 + 0x128) & 1) == 0) {
    Aska::HierarchicalObjectContainer::UpdateHierarchically()(param_4 + 0x30);
  }
  *(undefined4 *)(param_4 + 0xa0) = param_1;
  *(undefined4 *)(param_4 + 0xa4) = param_2;
  *(undefined4 *)(param_4 + 0xa8) = param_3;
  return;
}

// ==== Aska::HierarchicalObject::SetScale(Aska::Vector const*)
// vaddr 0x1e68ddc | ghidra 0x1f68ddc | size 76 | symbol _ZN4Aska18HierarchicalObject8SetScaleEPKNS_6VectorE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18HierarchicalObject8SetScaleEPKNS_6VectorE(long param_1,undefined4 *param_2)

{
  if ((*(byte *)(param_1 + 0x128) & 1) == 0) {
    Aska::HierarchicalObjectContainer::UpdateHierarchically()(param_1 + 0x30);
  }
  *(undefined4 *)(param_1 + 0xa0) = *param_2;
  *(undefined4 *)(param_1 + 0xa4) = param_2[1];
  *(undefined4 *)(param_1 + 0xa8) = param_2[2];
  *(undefined4 *)(param_1 + 0xac) = param_2[3];
  return;
}

// ==== Aska::HierarchicalObject::SetPositionPassive(float, float, float)
// vaddr 0x1e68e28 | ghidra 0x1f68e28 | size 36 | symbol _ZN4Aska18HierarchicalObject18SetPositionPassiveEfff | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18HierarchicalObject18SetPositionPassiveEfff
               (undefined4 param_1,undefined4 param_2,undefined4 param_3,long param_4)

{
  *(undefined4 *)(param_4 + 0x80) = param_1;
  *(undefined4 *)(param_4 + 0x84) = param_2;
  *(undefined4 *)(param_4 + 0x88) = param_3;
  *(byte *)(param_4 + 0x128) = *(byte *)(param_4 + 0x128) & 0xe0 | 1;
  *(undefined4 *)(param_4 + 0x8c) = 0x3f800000;
  return;
}

// ==== Aska::HierarchicalObject::SetPositionPassive(Aska::Vector const*)
// vaddr 0x1e68e4c | ghidra 0x1f68e4c | size 52 | symbol _ZN4Aska18HierarchicalObject18SetPositionPassiveEPKNS_6VectorE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18HierarchicalObject18SetPositionPassiveEPKNS_6VectorE
               (long param_1,undefined4 *param_2)

{
  *(byte *)(param_1 + 0x128) = *(byte *)(param_1 + 0x128) & 0xe0 | 1;
  *(undefined4 *)(param_1 + 0x80) = *param_2;
  *(undefined4 *)(param_1 + 0x84) = param_2[1];
  *(undefined4 *)(param_1 + 0x88) = param_2[2];
  *(undefined4 *)(param_1 + 0x8c) = param_2[3];
  return;
}

// ==== Aska::HierarchicalObject::SetPosturePassive(float, float, float)
// vaddr 0x1e68e80 | ghidra 0x1f68e80 | size 32 | symbol _ZN4Aska18HierarchicalObject17SetPosturePassiveEfff | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18HierarchicalObject17SetPosturePassiveEfff(long param_1)

{
  *(byte *)(param_1 + 0x128) = *(byte *)(param_1 + 0x128) & 0xe0 | 1;
  (*(code *)PTR__ZN4Aska10Quaternion15CreateFromEulerEfff14EnumRotateType_02c9af00)
            (param_1 + 0x90,0);
  return;
}

// ==== Aska::HierarchicalObject::SetPosturePassive(Aska::Vector const*)
// vaddr 0x1e68ea0 | ghidra 0x1f68ea0 | size 36 | symbol _ZN4Aska18HierarchicalObject17SetPosturePassiveEPKNS_6VectorE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18HierarchicalObject17SetPosturePassiveEPKNS_6VectorE(long param_1,undefined4 *param_2)

{
  *(byte *)(param_1 + 0x128) = *(byte *)(param_1 + 0x128) & 0xe0 | 1;
  (*(code *)PTR__ZN4Aska10Quaternion15CreateFromEulerEfff14EnumRotateType_02c9af00)
            (*param_2,param_2[1],param_2[2],param_1 + 0x90,0);
  return;
}

// ==== Aska::HierarchicalObject::SetPosturePassive(Aska::Quaternion const*)
// vaddr 0x1e68ec4 | ghidra 0x1f68ec4 | size 52 | symbol _ZN4Aska18HierarchicalObject17SetPosturePassiveEPKNS_10QuaternionE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18HierarchicalObject17SetPosturePassiveEPKNS_10QuaternionE
               (long param_1,undefined4 *param_2)

{
  *(byte *)(param_1 + 0x128) = *(byte *)(param_1 + 0x128) & 0xe0 | 1;
  *(undefined4 *)(param_1 + 0x90) = *param_2;
  *(undefined4 *)(param_1 + 0x94) = param_2[1];
  *(undefined4 *)(param_1 + 0x98) = param_2[2];
  *(undefined4 *)(param_1 + 0x9c) = param_2[3];
  return;
}

// ==== Aska::HierarchicalObject::SetPosturePassive(float, float, float, float)
// vaddr 0x1e68ef8 | ghidra 0x1f68ef8 | size 28 | symbol _ZN4Aska18HierarchicalObject17SetPosturePassiveEffff | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18HierarchicalObject17SetPosturePassiveEffff
               (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
               long param_5)

{
  *(undefined4 *)(param_5 + 0x90) = param_1;
  *(undefined4 *)(param_5 + 0x94) = param_2;
  *(undefined4 *)(param_5 + 0x98) = param_3;
  *(undefined4 *)(param_5 + 0x9c) = param_4;
  *(byte *)(param_5 + 0x128) = *(byte *)(param_5 + 0x128) & 0xe0 | 1;
  return;
}

// ==== Aska::HierarchicalObject::SetScalePassive(float, float, float)
// vaddr 0x1e68f14 | ghidra 0x1f68f14 | size 28 | symbol _ZN4Aska18HierarchicalObject15SetScalePassiveEfff | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18HierarchicalObject15SetScalePassiveEfff
               (undefined4 param_1,undefined4 param_2,undefined4 param_3,long param_4)

{
  *(undefined4 *)(param_4 + 0xa0) = param_1;
  *(undefined4 *)(param_4 + 0xa4) = param_2;
  *(undefined4 *)(param_4 + 0xa8) = param_3;
  *(byte *)(param_4 + 0x128) = *(byte *)(param_4 + 0x128) & 0xe0 | 1;
  return;
}

// ==== Aska::HierarchicalObject::SetScalePassive(Aska::Vector const*)
// vaddr 0x1e68f30 | ghidra 0x1f68f30 | size 52 | symbol _ZN4Aska18HierarchicalObject15SetScalePassiveEPKNS_6VectorE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18HierarchicalObject15SetScalePassiveEPKNS_6VectorE(long param_1,undefined4 *param_2)

{
  *(byte *)(param_1 + 0x128) = *(byte *)(param_1 + 0x128) & 0xe0 | 1;
  *(undefined4 *)(param_1 + 0xa0) = *param_2;
  *(undefined4 *)(param_1 + 0xa4) = param_2[1];
  *(undefined4 *)(param_1 + 0xa8) = param_2[2];
  *(undefined4 *)(param_1 + 0xac) = param_2[3];
  return;
}

// ==== Aska::HierarchicalObject::VirtualBoundingSphere()
// vaddr 0x1e68f64 | ghidra 0x1f68f64 | size 12 | symbol _ZN4Aska18HierarchicalObject21VirtualBoundingSphereEv | lib libSOA-3.7.0.so | 2026-10-04
undefined * _ZN4Aska18HierarchicalObject21VirtualBoundingSphereEv(void)

{
  return PTR__ZN4Aska18HierarchicalObject16m_vDefaultSphereE_02cb87c0;
}

// ==== Aska::HierarchicalObject::GetBoundingBox(bool)
// vaddr 0x1e68f70 | ghidra 0x1f68f70 | size 8 | symbol _ZN4Aska18HierarchicalObject14GetBoundingBoxEb | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska18HierarchicalObject14GetBoundingBoxEb(void)

{
  return 0;
}

// ==== Aska::HierarchicalObject::OnActive(bool)
// vaddr 0x1e68f78 | ghidra 0x1f68f78 | size 4 | symbol _ZN4Aska18HierarchicalObject8OnActiveEb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18HierarchicalObject8OnActiveEb(void)

{
  return;
}

// ==== Aska::HierarchicalObject::SetWorldMatrix(Aska::Matrix const*)
// vaddr 0x1e7666c | ghidra 0x1f7666c | size 76 | symbol _ZN4Aska18HierarchicalObject14SetWorldMatrixEPKNS_6MatrixE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18HierarchicalObject14SetWorldMatrixEPKNS_6MatrixE(long param_1,undefined8 *param_2)

{
  byte bVar1;
  undefined8 uVar2;
  
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

// ==== Aska::HierarchicalObject::MakeMatrix()
// vaddr 0x1e766b8 | ghidra 0x1f766b8 | size 8 | symbol _ZN4Aska18HierarchicalObject10MakeMatrixEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18HierarchicalObject10MakeMatrixEv(long param_1)

{
  (*(code *)PTR__ZN4Aska27HierarchicalObjectContainer10MakeMatrixEv_02c91fd8)(param_1 + 0x30);
  return;
}

// ==== Aska::IAnimatable::IsThisIt(unsigned short) const
// vaddr 0x1f22454 | ghidra 0x2022454 | size 116 | symbol _ZNK4Aska11IAnimatable8IsThisItEt | lib libSOA-3.7.0.so | 2026-10-04
byte _ZNK4Aska11IAnimatable8IsThisItEt(long *param_1,uint param_2)

{
  bool bVar1;
  long lVar2;
  byte unaff_w19;
  int iVar3;
  
  iVar3 = 0;
  do {
    lVar2 = (**(code **)(*param_1 + 0x10))(param_1,iVar3);
    if ((((uint)lVar2 & 0xffff) == (param_2 & 0xffff)) ||
       (((uint)((ulong)lVar2 >> 0x10) & 0xffff) == (param_2 & 0xffff))) {
      return 1;
    }
    bVar1 = lVar2 != 0xf000;
    if (bVar1) {
      iVar3 = iVar3 + 1;
    }
    unaff_w19 = unaff_w19 & bVar1;
  } while (bVar1);
  return unaff_w19;
}

// ==== Aska::IAnimatable::Clone(Aska::IAnimatable const*)
// vaddr 0x1f224c8 | ghidra 0x20224c8 | size 84 | symbol _ZN4Aska11IAnimatable5CloneEPKS0_ | lib libSOA-3.7.0.so | 2026-10-04
bool _ZN4Aska11IAnimatable5CloneEPKS0_(long *param_1,long *param_2)

{
  bool bVar1;
  long lVar2;
  long lVar3;
  
  if (param_2 == (long *)0x0) {
    bVar1 = false;
  }
  else {
    lVar2 = (**(code **)(*param_1 + 0x10))(param_1,0);
    lVar3 = (**(code **)(*param_2 + 0x10))(param_2,0);
    bVar1 = lVar2 == lVar3;
  }
  return bVar1;
}

// ==== Aska::IAnimatable::CreateClone(Aska::IAnimatable const*)
// vaddr 0x1f2251c | ghidra 0x202251c | size 8 | symbol _ZN4Aska11IAnimatable11CreateCloneEPKS0_ | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska11IAnimatable11CreateCloneEPKS0_(void)

{
  return 0;
}

// ==== Aska::IAnimatable::~IAnimatable()
// vaddr 0x1f22524 | ghidra 0x2022524 | size 4 | symbol _ZN4Aska11IAnimatableD1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11IAnimatableD2Ev(void)

{
  return;
}

// ==== Aska::IAnimatable::~IAnimatable()
// vaddr 0x1f22528 | ghidra 0x2022528 | size 4 | symbol _ZN4Aska11IAnimatableD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11IAnimatableD0Ev(void)

{
  code *pcVar1;
  
                    /* WARNING: Does not return */
  pcVar1 = (code *)SoftwareBreakpoint(1,0x202252c);
  (*pcVar1)();
}

// ==== Aska::IAnimatable::GetClassID(int) const
// vaddr 0x1f2252c | ghidra 0x202252c | size 8 | symbol _ZNK4Aska11IAnimatable10GetClassIDEi | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska11IAnimatable10GetClassIDEi(void)

{
  return 0xf000;
}


// FAILED to create function at 02bb0688 Aska::IAnimatable::vtable
// FAILED to create function at 02bb06d0 Aska::IAnimatable::typeinfo

// ==== Aska::Task::~Task()
// vaddr 0x1f7f564 | ghidra 0x207f564 | size 60 | symbol _ZN4Aska4TaskD2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska4TaskD1Ev(long *param_1)

{
  long *plVar1;
  
  plVar1 = (long *)param_1[3];
  *param_1 = (long)(PTR__ZTVN4Aska4TaskE_02cbe020 + 0x10);
  if (plVar1 != (long *)0x0) {
    (**(code **)(*plVar1 + 0x40))(plVar1,param_1);
  }
  (*(code *)PTR__ZN4Aska11IAnimatableD2Ev_02cb13b8)(param_1);
  return;
}

// ==== Aska::Task::~Task()
// vaddr 0x1f7f5a0 | ghidra 0x207f5a0 | size 68 | symbol _ZN4Aska4TaskD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska4TaskD0Ev(long *param_1)

{
  long *plVar1;
  
  plVar1 = (long *)param_1[3];
  *param_1 = (long)(PTR__ZTVN4Aska4TaskE_02cbe020 + 0x10);
  if (plVar1 != (long *)0x0) {
    (**(code **)(*plVar1 + 0x40))(plVar1,param_1);
  }
  Aska::IAnimatable::~IAnimatable()(param_1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::Task::Remove()
// vaddr 0x1f7f5e4 | ghidra 0x207f5e4 | size 32 | symbol _ZN4Aska4Task6RemoveEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska4Task6RemoveEv(long param_1)

{
  long *plVar1;
  
  plVar1 = *(long **)(param_1 + 0x18);
  if (plVar1 != (long *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x0207f5fc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(*plVar1 + 0x40))(plVar1,param_1);
    return;
  }
  return;
}

// ==== Aska::Task::DeleteThis(Aska::DeleteManager*)
// vaddr 0x1f7f604 | ghidra 0x207f604 | size 48 | symbol _ZN4Aska4Task10DeleteThisEPNS_13DeleteManagerE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska4Task10DeleteThisEPNS_13DeleteManagerE(undefined8 param_1,undefined *param_2)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZN4Aska6Global21m_systemDeleteManagerE_02cb77c0;
  if (param_2 != (undefined *)0x0) {
    puVar1 = param_2;
  }
  (*(code *)PTR__ZN4Aska13DeleteManager7AddMainEPvhhPNS_14IDeleteHandlerE_02c9d0d8)
            (puVar1,param_1,3,0,0);
  return;
}

// ==== Aska::Task::DeleteThisNextFrame(Aska::DeleteManager*)
// vaddr 0x1f7f634 | ghidra 0x207f634 | size 52 | symbol _ZN4Aska4Task19DeleteThisNextFrameEPNS_13DeleteManagerE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska4Task19DeleteThisNextFrameEPNS_13DeleteManagerE(undefined8 param_1,undefined *param_2)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZN4Aska6Global21m_systemDeleteManagerE_02cb77c0;
  if (param_2 != (undefined *)0x0) {
    puVar1 = param_2;
  }
  (*(code *)PTR__ZN4Aska13DeleteManager7AddMainEPvhhPNS_14IDeleteHandlerE_02c9d0d8)
            (puVar1,param_1,3,1,0);
  return;
}

// ==== Aska::Task::DeleteThisAfterTwoFrames(Aska::DeleteManager*)
// vaddr 0x1f7f668 | ghidra 0x207f668 | size 52 | symbol _ZN4Aska4Task24DeleteThisAfterTwoFramesEPNS_13DeleteManagerE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska4Task24DeleteThisAfterTwoFramesEPNS_13DeleteManagerE
               (undefined8 param_1,undefined *param_2)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZN4Aska6Global21m_systemDeleteManagerE_02cb77c0;
  if (param_2 != (undefined *)0x0) {
    puVar1 = param_2;
  }
  (*(code *)PTR__ZN4Aska13DeleteManager7AddMainEPvhhPNS_14IDeleteHandlerE_02c9d0d8)
            (puVar1,param_1,3,2,0);
  return;
}

// ==== Aska::Task::DeleteThisImmediately()
// vaddr 0x1f7f69c | ghidra 0x207f69c | size 20 | symbol _ZN4Aska4Task21DeleteThisImmediatelyEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska4Task21DeleteThisImmediatelyEv(long *param_1)

{
  if (param_1 != (long *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x0207f6a8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(*param_1 + 8))();
    return;
  }
  return;
}

// ==== Aska::Task::Clone(Aska::IAnimatable const*)
// vaddr 0x1f7f6b0 | ghidra 0x207f6b0 | size 76 | symbol _ZN4Aska4Task5CloneEPKNS_11IAnimatableE | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska4Task5CloneEPKNS_11IAnimatableE(long param_1,long param_2)

{
  ulong uVar1;
  undefined8 uVar2;
  
  uVar1 = Aska::IAnimatable::Clone(Aska::IAnimatable const*)();
  if (((uVar1 & 1) == 0) || (param_2 == 0)) {
    uVar2 = 0;
  }
  else {
    uVar2 = 1;
    *(undefined4 *)(param_1 + 0x20) = *(undefined4 *)(param_2 + 0x20);
    *(undefined1 *)(param_1 + 0x26) = *(undefined1 *)(param_2 + 0x26);
    *(undefined2 *)(param_1 + 0x24) = *(undefined2 *)(param_2 + 0x24);
  }
  return uVar2;
}

// ==== Aska::Task::CreateClone(Aska::IAnimatable const*)
// vaddr 0x1f7f6fc | ghidra 0x207f6fc | size 156 | symbol _ZN4Aska4Task11CreateCloneEPKNS_11IAnimatableE | lib libSOA-3.7.0.so | 2026-10-04
long * _ZN4Aska4Task11CreateCloneEPKNS_11IAnimatableE(undefined8 param_1,long param_2)

{
  undefined *puVar1;
  long *plVar2;
  ulong uVar3;
  
  plVar2 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x28,PTR__ZSt7nothrow_02cb9a80);
  if (plVar2 != (long *)0x0) {
    puVar1 = PTR__ZTVN4Aska4TaskE_02cbe020 + 0x10;
    plVar2[2] = 0;
    plVar2[3] = 0;
    *(undefined2 *)((long)plVar2 + 0x24) = 0;
    *(undefined1 *)((long)plVar2 + 0x26) = 0;
    *plVar2 = (long)puVar1;
    plVar2[1] = 0;
    *(undefined4 *)(plVar2 + 4) = 0x40;
    uVar3 = Aska::IAnimatable::Clone(Aska::IAnimatable const*)(plVar2,param_2);
    if (((uVar3 & 1) == 0) || (param_2 == 0)) {
      (**(code **)(*plVar2 + 8))(plVar2);
      plVar2 = (long *)0x0;
    }
    else {
      *(undefined4 *)(plVar2 + 4) = *(undefined4 *)(param_2 + 0x20);
      *(undefined1 *)((long)plVar2 + 0x26) = *(undefined1 *)(param_2 + 0x26);
      *(undefined2 *)((long)plVar2 + 0x24) = *(undefined2 *)(param_2 + 0x24);
    }
  }
  return plVar2;
}

// ==== Aska::Task::ChangeLevel(unsigned int)
// vaddr 0x1f7f798 | ghidra 0x207f798 | size 56 | symbol _ZN4Aska4Task11ChangeLevelEj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska4Task11ChangeLevelEj(long param_1,int param_2)

{
  if (param_2 != 0) {
    if (*(long *)(param_1 + 0x18) != 0) {
      Aska::TaskManager::ChangeLevel(Aska::Task*, unsigned int)(*(long *)(param_1 + 0x18),param_1,param_2);
    }
    *(int *)(param_1 + 0x20) = param_2;
  }
  return;
}

// ==== Aska::Task::ForceDelete()
// vaddr 0x1f7f7d0 | ghidra 0x207f7d0 | size 16 | symbol _ZN4Aska4Task11ForceDeleteEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska4Task11ForceDeleteEv(long *param_1)

{
  param_1[3] = 0;
                    /* WARNING: Could not recover jumptable at 0x0207f7dc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*param_1 + 0x50))();
  return;
}

// ==== Aska::Task::Run(int)
// vaddr 0x1f7f7e0 | ghidra 0x207f7e0 | size 4 | symbol _ZN4Aska4Task3RunEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska4Task3RunEi(void)

{
  return;
}

// ==== Aska::HierarchicalObject::~HierarchicalObject()
// vaddr 0x209f540 | ghidra 0x219f540 | size 152 | symbol _ZN4Aska18HierarchicalObjectD2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18HierarchicalObjectD2Ev(long *param_1)

{
  long *plVar1;
  long lVar2;
  long lVar3;
  
  plVar1 = param_1 + 6;
  *param_1 = (long)(PTR__ZTVN4Aska18HierarchicalObjectE_02cb6bb0 + 0x10);
  Aska::HierarchicalObjectContainer::DetachFromParent()(plVar1);
  if ((*(byte *)(param_1 + 0x25) & 1) == 0) {
    Aska::HierarchicalObjectContainer::UpdateHierarchically()(plVar1);
  }
  if ((code *)param_1[5] != (code *)0x0) {
    (*(code *)param_1[5])(param_1);
  }
  if (param_1[0x30] != 0) {
    operator delete(void*)();
    param_1[0x30] = 0;
  }
  param_1[6] = (long)(PTR__ZTVN4Aska27HierarchicalObjectContainerE_02cb81a8 + 0x10);
  lVar2 = param_1[0x22];
  while (lVar2 != 0) {
    lVar3 = *(long *)(lVar2 + 8);
    *(undefined8 *)(lVar2 + 8) = 0;
    *(undefined8 *)(lVar2 + 0x10) = 0;
    lVar2 = lVar3;
  }
  Aska::IAnimatable::~IAnimatable()(plVar1);
  (*(code *)PTR__ZN4Aska4TaskD1Ev_02c92d10)(param_1);
  return;
}

// ==== Aska::HierarchicalObject::EnableSimpleDynamics(bool)
// vaddr 0x20d48d4 | ghidra 0x21d48d4 | size 140 | symbol _ZN4Aska18HierarchicalObject20EnableSimpleDynamicsEb | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska18HierarchicalObject20EnableSimpleDynamicsEb(long param_1,ulong param_2)

{
  undefined8 uVar1;
  undefined8 uVar2;
  undefined8 *puVar3;
  
  uVar2 = _UNK_027dbb38;
  uVar1 = _UNK_027dbb30;
  puVar3 = *(undefined8 **)(param_1 + 0x180);
  if ((param_2 & 1) == 0) {
    if (puVar3 != (undefined8 *)0x0) {
      operator delete(void*)();
      *(undefined8 *)(param_1 + 0x180) = 0;
      return;
    }
  }
  else {
    if (puVar3 == (undefined8 *)0x0) {
      puVar3 = (undefined8 *)operator new(unsigned long, std::nothrow_t const&)(0x90,PTR__ZSt7nothrow_02cb9a80);
      uVar2 = _UNK_027dbb38;
      uVar1 = _UNK_027dbb30;
      if (puVar3 != (undefined8 *)0x0) {
        puVar3[1] = _UNK_027dbb38;
        *puVar3 = uVar1;
        puVar3[3] = uVar2;
        puVar3[2] = uVar1;
        puVar3[5] = uVar2;
        puVar3[4] = uVar1;
        puVar3[7] = uVar2;
        puVar3[6] = uVar1;
        puVar3[9] = uVar2;
        puVar3[8] = uVar1;
        puVar3[0xb] = uVar2;
        puVar3[10] = uVar1;
        puVar3[0xd] = uVar2;
        puVar3[0xc] = uVar1;
        puVar3[0xf] = uVar2;
        puVar3[0xe] = uVar1;
        puVar3[0x11] = uVar2;
        puVar3[0x10] = uVar1;
      }
      *(undefined8 **)(param_1 + 0x180) = puVar3;
      return;
    }
    puVar3[1] = _UNK_027dbb38;
    *puVar3 = uVar1;
    puVar3[3] = uVar2;
    puVar3[2] = uVar1;
    puVar3[5] = uVar2;
    puVar3[4] = uVar1;
    puVar3[7] = uVar2;
    puVar3[6] = uVar1;
    puVar3[9] = uVar2;
    puVar3[8] = uVar1;
    puVar3[0xb] = uVar2;
    puVar3[10] = uVar1;
    puVar3[0xd] = uVar2;
    puVar3[0xc] = uVar1;
    puVar3[0xf] = uVar2;
    puVar3[0xe] = uVar1;
    puVar3[0x11] = uVar2;
    puVar3[0x10] = uVar1;
  }
  return;
}

// ==== Aska::HierarchicalObject::Clone(Aska::IAnimatable const*)
// vaddr 0x21328fc | ghidra 0x22328fc | size 140 | symbol _ZN4Aska18HierarchicalObject5CloneEPKNS_11IAnimatableE | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska18HierarchicalObject5CloneEPKNS_11IAnimatableE(long param_1,long param_2)

{
  ulong uVar1;
  undefined8 uVar2;
  
  uVar1 = Aska::Task::Clone(Aska::IAnimatable const*)();
  if (((uVar1 & 1) == 0) ||
     (uVar1 = Aska::HierarchicalObjectContainer::Clone(Aska::IAnimatable const*)(param_1 + 0x30,param_2 + 0x30), (uVar1 & 1) == 0)) {
    uVar2 = 0;
  }
  else {
    if ((*(byte *)(param_1 + 0x128) >> 2 & 1) != 0) {
      uVar2 = *(undefined8 *)(param_2 + 0x130);
      *(undefined8 *)(param_1 + 0x138) = *(undefined8 *)(param_2 + 0x138);
      *(undefined8 *)(param_1 + 0x130) = uVar2;
      uVar2 = *(undefined8 *)(param_2 + 0x140);
      *(undefined8 *)(param_1 + 0x148) = *(undefined8 *)(param_2 + 0x148);
      *(undefined8 *)(param_1 + 0x140) = uVar2;
      uVar2 = *(undefined8 *)(param_2 + 0x150);
      *(undefined8 *)(param_1 + 0x158) = *(undefined8 *)(param_2 + 0x158);
      *(undefined8 *)(param_1 + 0x150) = uVar2;
      uVar2 = *(undefined8 *)(param_2 + 0x160);
      *(undefined8 *)(param_1 + 0x168) = *(undefined8 *)(param_2 + 0x168);
      *(undefined8 *)(param_1 + 0x160) = uVar2;
    }
    if ((*(byte *)(param_1 + 0x128) >> 3 & 1) != 0) {
      *(undefined4 *)(param_1 + 0x170) = *(undefined4 *)(param_2 + 0x170);
      *(undefined4 *)(param_1 + 0x174) = *(undefined4 *)(param_2 + 0x174);
      *(undefined4 *)(param_1 + 0x178) = *(undefined4 *)(param_2 + 0x178);
      *(undefined4 *)(param_1 + 0x17c) = *(undefined4 *)(param_2 + 0x17c);
    }
    uVar2 = 1;
  }
  return uVar2;
}

// ==== Aska::HierarchicalObject::CreateClone(Aska::IAnimatable const*)
// vaddr 0x2132988 | ghidra 0x2232988 | size 408 | symbol _ZN4Aska18HierarchicalObject11CreateCloneEPKNS_11IAnimatableE | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

long * _ZN4Aska18HierarchicalObject11CreateCloneEPKNS_11IAnimatableE
                 (undefined8 param_1,long param_2)

{
  undefined *puVar1;
  byte bVar2;
  byte bVar3;
  long lVar4;
  undefined4 uVar5;
  long *plVar6;
  ulong uVar7;
  code *pcVar8;
  long *plVar9;
  long *plVar10;
  long *plVar11;
  long lVar12;
  
  plVar6 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x1a0,PTR__ZSt7nothrow_02cb9a80);
  puVar1 = PTR__ZTVN4Aska4TaskE_02cbe020;
  if (plVar6 != (long *)0x0) {
    plVar6[2] = 0;
    plVar6[3] = 0;
    *(undefined2 *)((long)plVar6 + 0x24) = 0;
    pcVar8 = *(code **)(puVar1 + 0x68);
    *plVar6 = (long)(puVar1 + 0x10);
    plVar6[1] = 0;
    *(undefined1 *)((long)plVar6 + 0x26) = 0;
    uVar5 = (*pcVar8)(plVar6);
    *(undefined4 *)(plVar6 + 4) = uVar5;
    puVar1 = PTR__ZTVN4Aska27HierarchicalObjectContainerE_02cb81a8 + 0x10;
    *plVar6 = (long)(PTR__ZTVN4Aska18HierarchicalObjectE_02cb6bb0 + 0x10);
    plVar11 = plVar6 + 6;
    *plVar11 = (long)puVar1;
    plVar6[0x14] = 0x3f8000003f800000;
    plVar6[0x15] = 0x3f8000003f800000;
    lVar4 = _UNK_027dbb38;
    lVar12 = _UNK_027dbb30;
    bVar2 = *(byte *)(plVar6 + 0x25);
    bVar3 = *(byte *)((long)plVar6 + 0x129);
    *(byte *)((long)plVar6 + 0x129) = bVar3 & 0xfc;
    plVar6[0x11] = lVar4;
    plVar6[0x10] = lVar12;
    plVar6[0x13] = lVar4;
    plVar6[0x12] = lVar12;
    *(byte *)(plVar6 + 0x25) = bVar2 & 0xde | 1;
    plVar9 = plVar6 + 0x18;
    do {
      plVar10 = (long *)((long)plVar9 + 0x7fU & 0xffffffffffffff81);
      Hint_Prefetch(plVar9,0,2,0);
      plVar9 = plVar10;
    } while (plVar10 < plVar6 + 0x1a);
    *(byte *)((long)plVar6 + 0x129) = bVar3 & 0xf8;
    plVar6[0x18] = 0;
    plVar6[0x19] = 0x3f80000000000000;
    plVar6[0x22] = 0;
    plVar6[0x23] = 0;
    plVar6[0x23] = (long)plVar6;
    plVar6[0x24] = (long)(plVar6 + 8);
    plVar6[0x1b] = lVar4;
    plVar6[0x1a] = lVar12;
    plVar6[0x1d] = lVar4;
    plVar6[0x1c] = lVar12;
    plVar6[0x17] = lVar4;
    plVar6[0x16] = lVar12;
    plVar6[0x20] = (long)plVar11;
    plVar6[0x21] = (long)plVar11;
    plVar6[0x1e] = 0;
    plVar6[0x1f] = 0;
    plVar6[5] = 0;
    plVar6[0x30] = 0;
    plVar6[0x31] = 0;
    *(undefined4 *)(plVar6 + 0x32) = 0;
    *(undefined1 *)((long)plVar6 + 0x195) = 0;
    *(undefined1 *)((long)plVar6 + 0x194) = 1;
    *(byte *)(plVar6 + 0x25) = bVar2 & 200 | 1;
    *(undefined1 *)((long)plVar6 + 0x197) = 0;
    uVar7 = Aska::Task::Clone(Aska::IAnimatable const*)(plVar6,param_2);
    if (((uVar7 & 1) == 0) || (uVar7 = Aska::HierarchicalObjectContainer::Clone(Aska::IAnimatable const*)(plVar11,param_2 + 0x30), (uVar7 & 1) == 0)) {
      (**(code **)(*plVar6 + 8))(plVar6);
      plVar6 = (long *)0x0;
    }
    else {
      if ((*(byte *)(plVar6 + 0x25) >> 2 & 1) != 0) {
        lVar12 = *(long *)(param_2 + 0x130);
        plVar6[0x27] = *(long *)(param_2 + 0x138);
        plVar6[0x26] = lVar12;
        lVar12 = *(long *)(param_2 + 0x140);
        plVar6[0x29] = *(long *)(param_2 + 0x148);
        plVar6[0x28] = lVar12;
        lVar12 = *(long *)(param_2 + 0x150);
        plVar6[0x2b] = *(long *)(param_2 + 0x158);
        plVar6[0x2a] = lVar12;
        lVar12 = *(long *)(param_2 + 0x160);
        plVar6[0x2d] = *(long *)(param_2 + 0x168);
        plVar6[0x2c] = lVar12;
      }
      if ((*(byte *)(plVar6 + 0x25) >> 3 & 1) != 0) {
        lVar12 = *(long *)(param_2 + 0x170);
        plVar6[0x2f] = *(long *)(param_2 + 0x178);
        plVar6[0x2e] = lVar12;
      }
    }
  }
  return plVar6;
}

// ==== Aska::HierarchicalObject::InitializeConditions()
// vaddr 0x2132b20 | ghidra 0x2232b20 | size 68 | symbol _ZN4Aska18HierarchicalObject20InitializeConditionsEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18HierarchicalObject20InitializeConditionsEv(long *param_1)

{
  ushort uVar1;
  ulong uVar2;
  
  uVar2 = (**(code **)(*param_1 + 0xb8))();
  uVar1 = *(ushort *)((long)param_1 + 0x24) | 2;
  if ((uVar2 & 1) == 0) {
    uVar1 = *(ushort *)((long)param_1 + 0x24) & 0xfffd;
  }
  *(ushort *)((long)param_1 + 0x24) = uVar1;
                    /* WARNING: Could not recover jumptable at 0x02232b60. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*param_1 + 0xc0))(param_1);
  return;
}

// ==== Aska::HierarchicalObject::CheckSleepAvailability()
// vaddr 0x2132b64 | ghidra 0x2232b64 | size 16 | symbol _ZN4Aska18HierarchicalObject22CheckSleepAvailabilityEv | lib libSOA-3.7.0.so | 2026-10-04
bool _ZN4Aska18HierarchicalObject22CheckSleepAvailabilityEv(long param_1)

{
  return (*(byte *)(param_1 + 400) & 3) == 0;
}

// ==== Aska::HierarchicalObject::SetAppropriateTaskLevel()
// vaddr 0x2132b74 | ghidra 0x2232b74 | size 24 | symbol _ZN4Aska18HierarchicalObject23SetAppropriateTaskLevelEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18HierarchicalObject23SetAppropriateTaskLevelEv(long param_1)

{
  if ((*(byte *)(param_1 + 400) & 3) != 0) {
    (*(code *)PTR__ZN4Aska4Task11ChangeLevelEj_02cad070)(param_1,0x1000);
    return;
  }
  return;
}

// ==== Aska::HierarchicalObject::Run(int)
// vaddr 0x2132b8c | ghidra 0x2232b8c | size 264 | symbol _ZN4Aska18HierarchicalObject3RunEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18HierarchicalObject3RunEi(long *param_1)

{
  int iVar1;
  uint uVar2;
  undefined8 uVar3;
  long lVar4;
  long *plVar5;
  undefined1 auStack_70 [64];
  
  uVar2 = *(uint *)(param_1 + 0x32);
  if ((((uVar2 & 3) != 0) && ((uVar2 & 0x1c) != 0)) &&
     (lVar4 = *(long *)(*(long *)PTR__ZN4Aska6Global16m_pCameraManagerE_02cb7d08 + 0xff0),
     lVar4 != 0)) {
    iVar1 = 0;
    if ((uVar2 & 3) != 3) {
      iVar1 = 2 - (uVar2 & 1);
    }
    if ((*(byte *)(param_1 + 0x25) & 1) == 0) {
      Aska::HierarchicalObjectContainer::UpdateHierarchically()(param_1 + 6);
    }
    (**(code **)(*param_1 + 0xa8))(param_1);
    if ((*(byte *)((long)param_1 + 0x129) >> 2 & 1) == 0) {
      uVar3 = 0;
    }
    else {
      if ((param_1[0x1e] != 0) && (plVar5 = *(long **)(param_1[0x1e] + 0xe8), plVar5 != (long *)0x0)
         ) {
        if ((*(byte *)(plVar5 + 0x25) & 1) != 0) {
          (**(code **)(*plVar5 + 0xa8))(plVar5);
        }
        (**(code **)(*plVar5 + 0x98))(plVar5);
      }
      uVar3 = 1;
    }
    Aska::HierarchicalObject::MakeBillboardMatrixFromLocalAxisSub(Aska::HierarchicalObject*, Aska::Matrix&, bool, bool, Aska::HierarchicalObject::TargetFace)(param_1,lVar4,auStack_70,uVar3,0,iVar1);
    (**(code **)(*param_1 + 0xa0))(param_1,auStack_70);
  }
  return;
}

// ==== Aska::HierarchicalObject::MakeBillboardMatrixFromLocalAxis(Aska::HierarchicalObject*, Aska::Matrix*, Aska::HierarchicalObject::TargetFace)
// vaddr 0x2132c94 | ghidra 0x2232c94 | size 152 | symbol _ZN4Aska18HierarchicalObject32MakeBillboardMatrixFromLocalAxisEPS0_PNS_6MatrixENS0_10TargetFaceE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18HierarchicalObject32MakeBillboardMatrixFromLocalAxisEPS0_PNS_6MatrixENS0_10TargetFaceE
               (long param_1,undefined8 param_2,undefined8 param_3,undefined4 param_4)

{
  undefined8 uVar1;
  long *plVar2;
  
  if ((*(byte *)(param_1 + 0x129) >> 2 & 1) == 0) {
    uVar1 = 0;
  }
  else {
    if ((*(long *)(param_1 + 0xf0) != 0) &&
       (plVar2 = *(long **)(*(long *)(param_1 + 0xf0) + 0xe8), plVar2 != (long *)0x0)) {
      if ((*(byte *)(plVar2 + 0x25) & 1) != 0) {
        (**(code **)(*plVar2 + 0xa8))(plVar2);
      }
      (**(code **)(*plVar2 + 0x98))(plVar2);
    }
    uVar1 = 1;
  }
  (*(code *)
    PTR__ZN4Aska18HierarchicalObject35MakeBillboardMatrixFromLocalAxisSubEPS0_RNS_6MatrixEbbNS0_10TargetFaceE_02caa9b0
  )(param_1,param_2,param_3,uVar1,0,param_4);
  return;
}

// ==== Aska::HierarchicalObject::MakeBillboardMatrixFromLocalAxisSub(Aska::HierarchicalObject*, Aska::Matrix&, bool, bool, Aska::HierarchicalObject::TargetFace)
// vaddr 0x2132d2c | ghidra 0x2232d2c | size 1764 | symbol _ZN4Aska18HierarchicalObject35MakeBillboardMatrixFromLocalAxisSubEPS0_RNS_6MatrixEbbNS0_10TargetFaceE | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Type propagation algorithm not settling */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska18HierarchicalObject35MakeBillboardMatrixFromLocalAxisSubEPS0_RNS_6MatrixEbbNS0_10TargetFaceE
               (long *param_1,long *param_2,float *param_3,ulong param_4,undefined8 param_5,
               uint param_6)

{
  uint uVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  int iVar9;
  undefined8 *puVar10;
  float *pfVar11;
  float *pfVar12;
  undefined8 uVar13;
  undefined8 uVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  float fVar19;
  float fVar20;
  undefined8 uStack_2e0;
  undefined8 uStack_2d8;
  undefined8 uStack_2d0;
  undefined8 uStack_2c8;
  undefined8 uStack_2c0;
  undefined8 uStack_2b8;
  undefined8 uStack_2b0;
  undefined8 uStack_2a8;
  undefined1 auStack_2a0 [64];
  undefined8 uStack_260;
  undefined8 uStack_258;
  undefined8 uStack_250;
  undefined8 uStack_248;
  undefined8 uStack_240;
  undefined8 uStack_238;
  undefined8 uStack_230;
  undefined8 uStack_228;
  undefined1 auStack_220 [16];
  undefined1 auStack_210 [16];
  float fStack_200;
  float fStack_1fc;
  undefined8 uStack_1f8;
  undefined8 uStack_1c0;
  undefined8 uStack_1b8;
  undefined8 uStack_1b0;
  undefined8 uStack_1a8;
  undefined1 auStack_1a0 [64];
  undefined8 uStack_160;
  undefined8 uStack_158;
  undefined8 uStack_150;
  undefined8 uStack_148;
  undefined8 uStack_140;
  undefined8 uStack_138;
  undefined8 uStack_130;
  undefined8 uStack_128;
  undefined8 uStack_120;
  undefined8 uStack_118;
  undefined8 uStack_110;
  undefined8 uStack_108;
  undefined8 uStack_100;
  undefined8 uStack_f8;
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
  undefined8 uStack_a0;
  undefined8 uStack_98;
  undefined8 uStack_90;
  undefined8 uStack_88;
  undefined8 uStack_80;
  undefined8 uStack_78;
  undefined8 uStack_70;
  undefined8 uStack_68;
  undefined8 uStack_60;
  undefined8 uStack_58;
  
  puVar10 = (undefined8 *)(**(code **)(*param_2 + 0x98))(param_2);
  uStack_88 = puVar10[1];
  uStack_90 = *puVar10;
  uStack_78 = puVar10[3];
  uStack_80 = puVar10[2];
  uStack_68 = puVar10[5];
  uStack_70 = puVar10[4];
  uStack_58 = puVar10[7];
  uStack_60 = puVar10[6];
  if (((bRam0000000002dce470 & 1) == 0) && (iVar9 = __cxa_guard_acquire(0x2dce470), iVar9 != 0)) {
    uRam0000000002dce448 = _UNK_027f44a8;
    uRam0000000002dce440 = _UNK_027f44a0;
    uRam0000000002dce458 = _UNK_027ed898;
    uRam0000000002dce450 = _UNK_027ed890;
    uRam0000000002dce468 = _UNK_027e51b8;
    uRam0000000002dce460 = _UNK_027e51b0;
    __cxa_guard_release(0x2dce470);
  }
  uStack_98 = *(undefined8 *)((ulong)param_6 * 0x10 + 0x2dce448);
  uStack_a0 = *(undefined8 *)((ulong)param_6 * 0x10 + 0x2dce440);
  if (((param_4 & 1) == 0) && ((~*(uint *)(param_1 + 0x32) & 0x1c) == 0)) {
    uStack_a0 = CONCAT44(-(float)((ulong)uStack_a0 >> 0x20),-(float)uStack_a0);
    uStack_158 = _UNK_027e51b8;
    uStack_160 = _UNK_027e51b0;
    Aska::Quaternion::Create(Aska::Vector const*, Aska::Vector const*)(auStack_1a0,&uStack_160,&uStack_a0);
    Aska::Matrix::Create(Aska::Quaternion const*)(&uStack_e0,auStack_1a0);
    Aska::Matrix::Mul(Aska::Matrix const*, Aska::Matrix const*)(&uStack_120,&uStack_90,&uStack_e0);
    pfVar11 = (float *)Aska::HierarchicalObject::EstimateScaleStat()(param_1);
    pfVar12 = (float *)Aska::HierarchicalObject::EstimateScaleStat()(param_2);
    fVar17 = *pfVar11 / *pfVar12;
    fVar18 = pfVar11[1] / pfVar12[1];
    fVar19 = pfVar11[2] / pfVar12[2];
    puVar10 = (undefined8 *)(**(code **)(*param_1 + 0x98))(param_1);
    uVar14 = *puVar10;
    *(undefined8 *)(param_3 + 2) = puVar10[1];
    *(undefined8 *)param_3 = uVar14;
    uVar14 = puVar10[2];
    *(undefined8 *)(param_3 + 6) = puVar10[3];
    *(undefined8 *)(param_3 + 4) = uVar14;
    uVar14 = puVar10[4];
    *(undefined8 *)(param_3 + 10) = puVar10[5];
    *(undefined8 *)(param_3 + 8) = uVar14;
    uVar14 = puVar10[6];
    *(undefined8 *)(param_3 + 0xe) = puVar10[7];
    *(undefined8 *)(param_3 + 0xc) = uVar14;
    *param_3 = fVar17 * (float)uStack_120;
    param_3[4] = fVar17 * (float)uStack_110;
    param_3[8] = fVar17 * (float)uStack_100;
    param_3[1] = fVar18 * uStack_120._4_4_;
    param_3[5] = fVar18 * uStack_110._4_4_;
    param_3[9] = fVar18 * uStack_100._4_4_;
    param_3[2] = fVar19 * (float)uStack_118;
    param_3[6] = fVar19 * (float)uStack_108;
    param_3[10] = fVar19 * (float)uStack_f8;
    return;
  }
  uVar13 = Aska::HierarchicalObject::EstimateScaleStat()(param_1);
  uVar8 = _UNK_027dbb38;
  uVar7 = _UNK_027dbb30;
  uVar6 = _UNK_027dbb28;
  uVar5 = _UNK_027dbb20;
  uVar4 = _UNK_027dbb18;
  uVar3 = _UNK_027dbb10;
  uVar2 = _UNK_027dbb08;
  uVar14 = _UNK_027dbb00;
  uStack_158 = _UNK_027dbb08;
  uStack_160 = _UNK_027dbb00;
  uStack_148 = _UNK_027dbb18;
  uStack_150 = _UNK_027dbb10;
  uStack_138 = _UNK_027dbb28;
  uStack_140 = _UNK_027dbb20;
  uStack_128 = _UNK_027dbb38;
  uStack_130 = _UNK_027dbb30;
  Aska::Matrix::Scale(Aska::Vector const*)(&uStack_160,uVar13);
  puVar10 = (undefined8 *)(**(code **)(*param_1 + 0x98))(param_1);
  uStack_d8 = puVar10[1];
  uStack_e0 = *puVar10;
  uStack_c8 = puVar10[3];
  uStack_d0 = puVar10[2];
  uStack_b8 = puVar10[5];
  uStack_c0 = puVar10[4];
  uStack_a8 = puVar10[7];
  uStack_b0 = puVar10[6];
  Aska::Matrix::InvertLowError(Aska::Matrix*) const(&uStack_e0,auStack_1a0);
  uStack_118 = uVar2;
  uStack_120 = uVar14;
  uStack_108 = uVar4;
  uStack_110 = uVar3;
  uStack_f8 = uVar6;
  uStack_100 = uVar5;
  uStack_e8 = uVar8;
  uStack_f0 = uVar7;
  Aska::Matrix::Mul(Aska::Matrix const*, Aska::Matrix const*)(&uStack_120,auStack_1a0,&uStack_90);
  fVar17 = uStack_118._4_4_;
  fVar18 = uStack_108._4_4_;
  fVar19 = uStack_f8._4_4_;
  uStack_1b8 = uVar8;
  uStack_1c0 = uVar7;
  uVar1 = *(uint *)(param_1 + 0x32);
  if ((uVar1 >> 2 & 1) != 0) {
    fVar15 = uStack_108._4_4_ * uStack_108._4_4_ + 0.0 + uStack_f8._4_4_ * uStack_f8._4_4_;
    fVar16 = SQRT(fVar15);
    fStack_200 = 0.0;
    fStack_1fc = uStack_108._4_4_;
    uStack_1f8 = CONCAT44(0x3f800000,uStack_f8._4_4_);
    if (NAN(fVar16)) {
      fVar16 = (float)sqrtf(fVar15);
    }
    if (_UNK_027e519c <= fVar16) {
      fVar16 = 1.0 / fVar16;
      fStack_200 = fVar16 * 0.0;
      fStack_1fc = fVar16 * fVar18;
      uStack_1f8 = CONCAT44(uStack_1f8._4_4_,fVar16 * fVar19);
    }
    uStack_1a8 = uVar8;
    uStack_1b0 = uVar7;
    Aska::Quaternion::Create(Aska::Vector const*, Aska::Vector const*)(&uStack_1c0,&uStack_a0,&fStack_200);
    uVar1 = *(uint *)(param_1 + 0x32);
  }
  if ((uVar1 >> 3 & 1) != 0) {
    fVar15 = fVar17 * fVar17 + 0.0 + fVar19 * fVar19;
    fVar16 = SQRT(fVar15);
    fStack_200 = fVar17;
    fStack_1fc = 0.0;
    uStack_1f8 = CONCAT44(0x3f800000,fVar19);
    if (NAN(fVar16)) {
      fVar16 = (float)sqrtf(fVar15);
    }
    if (_UNK_027e519c <= fVar16) {
      fVar16 = 1.0 / fVar16;
      fStack_200 = fVar16 * fVar17;
      fStack_1fc = fVar16 * 0.0;
      uStack_1f8 = CONCAT44(uStack_1f8._4_4_,fVar16 * fVar19);
    }
    uStack_1a8 = uVar8;
    uStack_1b0 = uVar7;
    Aska::Quaternion::Create(Aska::Vector const*, Aska::Vector const*)(&uStack_1b0,&uStack_a0,&fStack_200);
    fVar20 = (float)uStack_1c0 * uStack_1b0._4_4_;
    fVar16 = (float)uStack_1b0 * (float)uStack_1c0;
    fVar19 = (float)uStack_1b0 * uStack_1c0._4_4_;
    fVar15 = uStack_1c0._4_4_ * uStack_1b0._4_4_;
    uStack_1c0 = CONCAT44((float)uStack_1b0 * (float)uStack_1b8 +
                          uStack_1a8._4_4_ * uStack_1c0._4_4_ +
                          (uStack_1b8._4_4_ * uStack_1b0._4_4_ -
                          (float)uStack_1c0 * (float)uStack_1a8),
                          (uStack_1b8._4_4_ * (float)uStack_1b0 +
                           (float)uStack_1c0 * uStack_1a8._4_4_ +
                          uStack_1c0._4_4_ * (float)uStack_1a8) -
                          (float)uStack_1b8 * uStack_1b0._4_4_);
    uStack_1b8 = CONCAT44(((uStack_1b8._4_4_ * uStack_1a8._4_4_ - fVar16) - fVar15) -
                          (float)uStack_1a8 * (float)uStack_1b8,
                          uStack_1a8._4_4_ * (float)uStack_1b8 +
                          ((uStack_1b8._4_4_ * (float)uStack_1a8 + fVar20) - fVar19));
    uVar1 = *(uint *)(param_1 + 0x32);
  }
  if ((uVar1 >> 4 & 1) == 0) {
    uStack_1c0._4_4_ = (float)((ulong)uStack_1c0 >> 0x20);
    uStack_1b8._4_4_ = (float)((ulong)uStack_1b8 >> 0x20);
    fVar17 = (float)uStack_1c0;
    fVar18 = uStack_1c0._4_4_;
    fVar19 = (float)uStack_1b8;
    fVar16 = uStack_1b8._4_4_;
  }
  else {
    fVar16 = fVar17 * fVar17 + fVar18 * fVar18 + 0.0;
    fVar19 = SQRT(fVar16);
    fStack_200 = fVar17;
    fStack_1fc = fVar18;
    uStack_1f8 = 0x3f80000000000000;
    if (NAN(fVar19)) {
      fVar19 = (float)sqrtf(fVar16);
    }
    if (_UNK_027e519c <= fVar19) {
      fVar19 = 1.0 / fVar19;
      fStack_200 = fVar19 * fVar17;
      fStack_1fc = fVar19 * fVar18;
      uStack_1f8 = CONCAT44(uStack_1f8._4_4_,fVar19 * 0.0);
    }
    uStack_1a8 = uVar8;
    uStack_1b0 = uVar7;
    Aska::Quaternion::Create(Aska::Vector const*, Aska::Vector const*)(&uStack_1b0,&uStack_a0,&fStack_200);
    fVar17 = (uStack_1b8._4_4_ * (float)uStack_1b0 + (float)uStack_1c0 * uStack_1a8._4_4_ +
             uStack_1c0._4_4_ * (float)uStack_1a8) - (float)uStack_1b8 * uStack_1b0._4_4_;
    fVar18 = (float)uStack_1b0 * (float)uStack_1b8 +
             uStack_1a8._4_4_ * uStack_1c0._4_4_ +
             (uStack_1b8._4_4_ * uStack_1b0._4_4_ - (float)uStack_1c0 * (float)uStack_1a8);
    fVar19 = uStack_1a8._4_4_ * (float)uStack_1b8 +
             ((uStack_1b8._4_4_ * (float)uStack_1a8 + (float)uStack_1c0 * uStack_1b0._4_4_) -
             (float)uStack_1b0 * uStack_1c0._4_4_);
    fVar16 = ((uStack_1b8._4_4_ * uStack_1a8._4_4_ - (float)uStack_1b0 * (float)uStack_1c0) -
             uStack_1c0._4_4_ * uStack_1b0._4_4_) - (float)uStack_1a8 * (float)uStack_1b8;
    uStack_1c0 = CONCAT44(fVar18,fVar17);
    uStack_1b8 = CONCAT44(fVar16,fVar19);
  }
  fVar18 = fVar17 * fVar17 + fVar18 * fVar18 + fVar19 * fVar19 + fVar16 * fVar16;
  fVar17 = SQRT(fVar18);
  if (NAN(fVar17)) {
    fVar17 = (float)sqrtf(fVar18);
  }
  fVar17 = 1.0 / fVar17;
  uStack_1c0 = CONCAT44((float)((ulong)uStack_1c0 >> 0x20) * fVar17,(float)uStack_1c0 * fVar17);
  uStack_1b8 = CONCAT44((float)((ulong)uStack_1b8 >> 0x20) * fVar17,(float)uStack_1b8 * fVar17);
  Aska::Matrix::Create(Aska::Quaternion const*)(&fStack_200,&uStack_1c0);
  Aska::Matrix::PutPRS(Aska::Vector*, Aska::Quaternion*, Aska::Vector*) const(&uStack_e0,auStack_210,auStack_220,0);
  uStack_258 = uVar2;
  uStack_260 = uVar14;
  uStack_248 = uVar4;
  uStack_250 = uVar3;
  uStack_238 = uVar6;
  uStack_240 = uVar5;
  uStack_228 = uVar8;
  uStack_230 = uVar7;
  Aska::Matrix::Translate(Aska::Vector const*)(&uStack_260,auStack_210);
  Aska::Matrix::Create(Aska::Quaternion const*)(auStack_2a0,auStack_220);
  Aska::Matrix::Mul(Aska::Matrix const*, Aska::Matrix const*)(&uStack_2e0,&uStack_260,auStack_2a0);
  Aska::Matrix::Mul(Aska::Matrix const*)(&uStack_2e0,&fStack_200);
  Aska::Matrix::Mul(Aska::Matrix const*)(&uStack_2e0,&uStack_160);
  *(undefined8 *)(param_3 + 2) = uStack_2d8;
  *(undefined8 *)param_3 = uStack_2e0;
  *(undefined8 *)(param_3 + 6) = uStack_2c8;
  *(undefined8 *)(param_3 + 4) = uStack_2d0;
  *(undefined8 *)(param_3 + 10) = uStack_2b8;
  *(undefined8 *)(param_3 + 8) = uStack_2c0;
  *(undefined8 *)(param_3 + 0xe) = uStack_2a8;
  *(undefined8 *)(param_3 + 0xc) = uStack_2b0;
  return;
}

// ==== Aska::HierarchicalObject::EstimateScaleStat()
// vaddr 0x2133410 | ghidra 0x2233410 | size 340 | symbol _ZN4Aska18HierarchicalObject17EstimateScaleStatEv | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

long * _ZN4Aska18HierarchicalObject17EstimateScaleStatEv(long *param_1)

{
  float *pfVar1;
  byte bVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  
  pfVar1 = (float *)(**(code **)(*param_1 + 0x98))();
  if ((*(byte *)(param_1 + 0x25) >> 3 & 1) == 0) {
    *(byte *)(param_1 + 0x25) = *(byte *)(param_1 + 0x25) | 8;
    fVar6 = SQRT(*pfVar1 * *pfVar1 + pfVar1[4] * pfVar1[4] + pfVar1[8] * pfVar1[8]);
    if (NAN(fVar6)) {
      fVar6 = (float)sqrtf();
    }
    *(float *)(param_1 + 0x2e) = fVar6;
    fVar4 = pfVar1[1] * pfVar1[1] + pfVar1[5] * pfVar1[5] + pfVar1[9] * pfVar1[9];
    fVar3 = SQRT(fVar4);
    if (NAN(fVar3)) {
      fVar3 = (float)sqrtf(fVar4);
    }
    *(float *)((long)param_1 + 0x174) = fVar3;
    fVar5 = pfVar1[2] * pfVar1[2] + pfVar1[6] * pfVar1[6] + pfVar1[10] * pfVar1[10];
    fVar4 = SQRT(fVar5);
    if (NAN(fVar4)) {
      fVar4 = (float)sqrtf(fVar5);
    }
    fVar5 = _UNK_027daba4;
    *(float *)(param_1 + 0x2f) = fVar4;
    if ((fVar5 <= ABS(fVar6 - fVar3)) || (fVar5 <= ABS(fVar6 - fVar4))) {
      bVar2 = *(byte *)((long)param_1 + 0x129) & 0xfc | 2;
    }
    else {
      bVar2 = *(byte *)((long)param_1 + 0x129) & 0xfc;
      if (fVar5 <= ABS(fVar6 + -1.0)) {
        bVar2 = bVar2 | 1;
      }
    }
    *(byte *)((long)param_1 + 0x129) = bVar2;
  }
  return param_1 + 0x2e;
}

// ==== Aska::HierarchicalObject::UpdateSimpleDynamics(Aska::AFF::SimpleDynamicsParameters const*)
// vaddr 0x2133564 | ghidra 0x2233564 | size 1340 | symbol _ZN4Aska18HierarchicalObject20UpdateSimpleDynamicsEPKNS_3AFF24SimpleDynamicsParametersE | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska18HierarchicalObject20UpdateSimpleDynamicsEPKNS_3AFF24SimpleDynamicsParametersE
               (long *param_1,float *param_2)

{
  long lVar1;
  long lVar2;
  byte bVar3;
  float *pfVar4;
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
  float fStack_80;
  float fStack_7c;
  float fStack_78;
  float fStack_74;
  float fStack_70;
  float fStack_6c;
  float fStack_68;
  float fStack_64;
  
  if ((param_1[0x30] != 0) &&
     (fVar5 = (float)(**(code **)**(undefined8 **)PTR__ZN4Aska6Global8m_pVSyncE_02cbd460)
                               (*(undefined8 **)PTR__ZN4Aska6Global8m_pVSyncE_02cbd460,0),
     _UNK_029cbdc8 <= fVar5)) {
    bVar3 = *(byte *)(param_1 + 0x25);
    if ((bVar3 & 1) != 0) {
      (**(code **)(*param_1 + 0xa8))(param_1);
      bVar3 = *(byte *)(param_1 + 0x25);
    }
    lVar1 = _UNK_027dbb38;
    lVar2 = _UNK_027dbb30;
    if ((bVar3 >> 2 & 1) == 0) {
      if ((*(byte *)((long)param_1 + 0x129) & 3) == 0) {
        fVar7 = *(float *)((long)param_1 + 0x4c);
        fVar8 = *(float *)((long)param_1 + 0x5c);
        fVar9 = *(float *)((long)param_1 + 0x6c);
        param_1[0x27] = CONCAT44((int)param_1[0xe],*(float *)(param_1 + 0xc));
        param_1[0x26] = CONCAT44(*(float *)(param_1 + 10),*(float *)(param_1 + 8));
        param_1[0x29] =
             CONCAT44(*(undefined4 *)((long)param_1 + 0x74),*(float *)((long)param_1 + 100));
        param_1[0x28] = CONCAT44(*(float *)((long)param_1 + 0x54),*(float *)((long)param_1 + 0x44));
        *(float *)((long)param_1 + 0x13c) =
             -(*(float *)(param_1 + 8) * fVar7 + *(float *)(param_1 + 10) * fVar8 +
              *(float *)(param_1 + 0xc) * fVar9);
        *(float *)((long)param_1 + 0x14c) =
             -(fVar7 * *(float *)((long)param_1 + 0x44) + fVar8 * *(float *)((long)param_1 + 0x54) +
              fVar9 * *(float *)((long)param_1 + 100));
        param_1[0x2b] = CONCAT44((int)param_1[0xf],*(float *)(param_1 + 0xd));
        param_1[0x2a] = CONCAT44(*(float *)(param_1 + 0xb),*(float *)(param_1 + 9));
        param_1[0x2d] = lVar1;
        param_1[0x2c] = lVar2;
        *(float *)((long)param_1 + 0x15c) =
             -(fVar7 * *(float *)(param_1 + 9) + fVar8 * *(float *)(param_1 + 0xb) +
              fVar9 * *(float *)(param_1 + 0xd));
      }
      else {
        Aska::Matrix::InvertLowError(Aska::Matrix*) const(param_1 + 8,param_1 + 0x26);
        bVar3 = *(byte *)(param_1 + 0x25);
      }
      *(byte *)(param_1 + 0x25) = bVar3 | 4;
    }
    lVar2 = (**(code **)(*param_1 + 0x98))(param_1);
    fVar7 = *(float *)(lVar2 + 0xc);
    fVar8 = *(float *)(lVar2 + 0x1c);
    fVar9 = *(float *)(lVar2 + 0x2c);
    Aska::Quaternion::Create(Aska::Matrix const*)(&fStack_70,lVar2);
    pfVar4 = (float *)param_1[0x30];
    fVar6 = *param_2;
    fVar10 = *pfVar4;
    fVar11 = pfVar4[1];
    fVar18 = pfVar4[6];
    fVar20 = pfVar4[7];
    fVar21 = pfVar4[4];
    fVar22 = pfVar4[5];
    fVar12 = pfVar4[2];
    *pfVar4 = fVar7;
    pfVar4[1] = fVar8;
    pfVar4[2] = fVar9;
    pfVar4[3] = 1.0;
    fVar14 = 1.0 / fVar5;
    fVar7 = fVar7 - fVar10;
    fVar13 = param_2[1];
    fVar8 = fVar8 - fVar11;
    fVar15 = 1.0 - fVar13;
    fVar9 = fVar9 - fVar12;
    fVar11 = pfVar4[0x14] * fVar15 + fVar13 * fVar14 * (fVar7 - pfVar4[0xc]);
    fVar16 = fVar15 * pfVar4[0x15] + fVar13 * fVar14 * (fVar8 - pfVar4[0xd]);
    fVar12 = fVar15 * pfVar4[0x16] + fVar13 * fVar14 * (fVar9 - pfVar4[0xe]);
    fVar10 = 1.0 / (fVar20 * fVar20 + fVar21 * fVar21 + fVar22 * fVar22 + fVar18 * fVar18);
    pfVar4[0x14] = fVar11;
    pfVar4[0x15] = fVar16;
    pfVar4[0x16] = fVar12;
    fVar18 = fVar18 * fVar10;
    fVar17 = param_2[2];
    fVar19 = param_2[3];
    fVar21 = fVar21 * fVar10;
    fVar22 = fVar22 * fVar10;
    fVar20 = fVar20 * fVar10;
    fVar10 = (0.0 - fVar7 * fVar17) - fVar19 * fVar11;
    fVar6 = (-fVar6 - fVar8 * fVar17) - fVar19 * fVar16;
    fVar11 = (0.0 - fVar9 * fVar17) - fVar19 * fVar12;
    pfVar4[0x1f] = 1.0;
    pfVar4[0x1c] = fVar10;
    pfVar4[0x1d] = fVar6;
    pfVar4[0x1e] = fVar11;
    fVar12 = param_2[4];
    pfVar4[0xc] = fVar7;
    pfVar4[0xd] = fVar8;
    pfVar4[0xe] = fVar9;
    pfVar4[0xf] = 1.0;
    fVar7 = -fVar12;
    if (fVar12 + fVar10 < 0.0) {
      fVar10 = fVar7;
    }
    fVar8 = fVar12;
    if (fVar10 - fVar12 < 0.0) {
      fVar8 = fVar10;
    }
    if (fVar12 + fVar6 < 0.0) {
      fVar6 = fVar7;
    }
    fVar9 = fVar12;
    if (fVar6 - fVar12 < 0.0) {
      fVar9 = fVar6;
    }
    pfVar4[0x1c] = fVar8;
    pfVar4[0x1d] = fVar9;
    if (fVar12 + fVar11 < 0.0) {
      fVar11 = fVar7;
    }
    if (fVar11 - fVar12 < 0.0) {
      fVar12 = fVar11;
    }
    pfVar4[0x1e] = fVar12;
    fStack_80 = ((fStack_70 * fVar20 - fStack_64 * fVar21) - fStack_68 * fVar22) +
                fStack_6c * fVar18;
    fStack_7c = ((fVar20 * fStack_6c - fStack_64 * fVar22) - fStack_70 * fVar18) +
                fStack_68 * fVar21;
    fStack_78 = ((fStack_68 * fVar20 - fStack_64 * fVar18) - fStack_6c * fVar21) +
                fStack_70 * fVar22;
    fStack_74 = fStack_64 * fVar20 + fStack_70 * fVar21 + fStack_6c * fVar22 + fStack_68 * fVar18;
    pfVar4[4] = fStack_70;
    pfVar4[5] = fStack_6c;
    pfVar4[6] = fStack_68;
    pfVar4[7] = fStack_64;
    Aska::Quaternion::Slerp(Aska::Quaternion const*, Aska::Quaternion const*, float)(fVar5 * 8.0,pfVar4 + 8,pfVar4 + 8,&fStack_80);
    fVar7 = pfVar4[8] * pfVar4[8] + pfVar4[9] * pfVar4[9] + pfVar4[10] * pfVar4[10] +
            pfVar4[0xb] * pfVar4[0xb];
    fVar5 = SQRT(fVar7);
    if (NAN(fVar5)) {
      fVar5 = (float)sqrtf(fVar7);
    }
    fVar5 = 1.0 / fVar5;
    fVar7 = (float)*(undefined8 *)(pfVar4 + 8) * fVar5;
    fVar9 = (float)((ulong)*(undefined8 *)(pfVar4 + 8) >> 0x20) * fVar5;
    fVar8 = (float)*(undefined8 *)(pfVar4 + 10) * fVar5;
    fVar5 = (float)((ulong)*(undefined8 *)(pfVar4 + 10) >> 0x20) * fVar5;
    *(ulong *)(pfVar4 + 10) = CONCAT44(fVar5,fVar8);
    *(ulong *)(pfVar4 + 8) = CONCAT44(fVar9,fVar7);
    fVar10 = param_2[5];
    fVar7 = fVar10 * fVar7;
    fVar9 = fVar10 * fVar9;
    fVar10 = fVar10 * fVar8;
    fVar8 = fVar15 * pfVar4[0x18] + fVar13 * fVar14 * (fVar7 - pfVar4[0x10]);
    fVar6 = fVar15 * pfVar4[0x19] + fVar13 * fVar14 * (fVar9 - pfVar4[0x11]);
    fVar11 = fVar15 * pfVar4[0x1a] + fVar13 * fVar14 * (fVar10 - pfVar4[0x12]);
    pfVar4[0x10] = fVar7;
    pfVar4[0x11] = fVar9;
    pfVar4[0x12] = fVar10;
    pfVar4[0x18] = fVar8;
    pfVar4[0x19] = fVar6;
    pfVar4[0x1a] = fVar11;
    pfVar4[0x13] = fVar5;
    fVar12 = param_2[6];
    fVar20 = param_2[7];
    fVar8 = fVar7 * fVar12 + fVar20 * fVar8;
    fVar9 = fVar9 * fVar12 + fVar20 * fVar6;
    fVar7 = fVar10 * fVar12 + fVar20 * fVar11;
    pfVar4[0x20] = fVar8;
    pfVar4[0x21] = fVar9;
    pfVar4[0x22] = fVar7;
    pfVar4[0x23] = fVar5;
    fVar5 = param_2[8];
    fVar10 = -fVar5;
    if (fVar5 + fVar8 < 0.0) {
      fVar8 = fVar10;
    }
    fVar6 = fVar5;
    if (fVar8 - fVar5 < 0.0) {
      fVar6 = fVar8;
    }
    if (fVar5 + fVar9 < 0.0) {
      fVar9 = fVar10;
    }
    fVar8 = fVar5;
    if (fVar9 - fVar5 < 0.0) {
      fVar8 = fVar9;
    }
    if (fVar5 + fVar7 < 0.0) {
      fVar7 = fVar10;
    }
    pfVar4[0x20] = fVar6;
    pfVar4[0x21] = fVar8;
    if (fVar7 - fVar5 < 0.0) {
      fVar5 = fVar7;
    }
    pfVar4[0x22] = fVar5;
    Aska::Vector::ApplyMatrixNoTransport(Aska::Matrix const*)(pfVar4 + 0x1c,param_1 + 0x26);
    Aska::Vector::ApplyMatrixNoTransport(Aska::Matrix const*)(pfVar4 + 0x20,param_1 + 0x26);
    *(byte *)(param_1 + 0x25) = *(byte *)(param_1 + 0x25) | 2;
  }
  return;
}

// ==== Aska::HierarchicalObject::SwapChangeling(Aska::HierarchicalObject*)
// vaddr 0x2133bd0 | ghidra 0x2233bd0 | size 160 | symbol _ZN4Aska18HierarchicalObject14SwapChangelingEPS0_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18HierarchicalObject14SwapChangelingEPS0_(long *param_1,long param_2)

{
  long lVar1;
  undefined8 *puVar2;
  undefined8 uStack_60;
  undefined8 uStack_58;
  undefined8 uStack_50;
  undefined8 uStack_48;
  undefined8 uStack_40;
  undefined8 uStack_38;
  undefined8 uStack_30;
  undefined8 uStack_28;
  
  if ((*(byte *)(param_1 + 0x25) & 1) != 0) {
    (**(code **)(*param_1 + 0xa8))(param_1);
  }
  puVar2 = (undefined8 *)(**(code **)(*param_1 + 0x98))(param_1);
  uStack_58 = puVar2[1];
  uStack_60 = *puVar2;
  lVar1 = 0;
  if (param_2 != 0) {
    lVar1 = param_2 + 0x30;
  }
  uStack_48 = puVar2[3];
  uStack_50 = puVar2[2];
  uStack_38 = puVar2[5];
  uStack_40 = puVar2[4];
  uStack_28 = puVar2[7];
  uStack_30 = puVar2[6];
  Aska::HierarchicalObjectContainer::SwapParent(Aska::HierarchicalObjectContainer*)(param_1 + 6,lVar1);
  (**(code **)(*param_1 + 0xa0))(param_1,&uStack_60);
  Aska::HierarchicalObjectContainer::MakeTransformParamEx()(param_1 + 6);
  return;
}

// ==== Aska::HierarchicalObject::InverseKinematics(Aska::Vector const*, int, int, float, float, bool)
// vaddr 0x2133c70 | ghidra 0x2233c70 | size 1336 | symbol _ZN4Aska18HierarchicalObject17InverseKinematicsEPKNS_6VectorEiiffb | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska18HierarchicalObject17InverseKinematicsEPKNS_6VectorEiiffb
               (float param_1,float param_2,long *param_3,float *param_4,int param_5,int param_6,
               uint param_7)

{
  undefined1 auVar1 [16];
  undefined1 auVar2 [16];
  undefined1 auVar3 [16];
  long lVar4;
  long lVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  float fVar8;
  byte bVar9;
  long *plVar10;
  int iVar11;
  int iVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  undefined1 auVar19 [16];
  undefined1 auVar20 [16];
  undefined1 auVar21 [16];
  float fVar22;
  float fVar23;
  undefined1 auVar24 [16];
  float fVar28;
  float fVar29;
  undefined1 auVar25 [16];
  undefined1 auVar26 [16];
  undefined1 auVar27 [16];
  float fVar30;
  float fVar31;
  float fVar32;
  undefined1 auVar33 [16];
  undefined1 auVar34 [16];
  undefined8 uVar35;
  undefined1 auVar36 [16];
  undefined1 auVar37 [16];
  float fVar38;
  float fVar39;
  float fStack_c0;
  float fStack_bc;
  float fStack_b8;
  float fStack_b4;
  undefined8 uStack_b0;
  undefined8 uStack_a8;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  float fStack_94;
  
  if ((*(byte *)(param_3 + 0x25) & 1) != 0) {
    (**(code **)(*param_3 + 0xa8))(param_3);
  }
  fVar8 = _UNK_029c4eec;
  uVar7 = _UNK_029c49f8;
  uVar6 = _UNK_029c49f0;
  lVar5 = _UNK_027dbb38;
  lVar4 = _UNK_027dbb30;
  fVar13 = *(float *)((long)param_3 + 0x4c) - *param_4;
  fVar17 = *(float *)((long)param_3 + 0x5c) - param_4[1];
  fVar22 = *(float *)((long)param_3 + 0x6c) - param_4[2];
  if ((param_2 <= fVar13 * fVar13 + fVar17 * fVar17 + fVar22 * fVar22) && (0 < param_6)) {
    iVar11 = 0;
    fVar13 = *(float *)((long)param_3 + 0x4c);
    fVar17 = *(float *)((long)param_3 + 0x5c);
    fVar22 = *(float *)((long)param_3 + 0x6c);
    do {
      fVar14 = fVar13;
      fVar15 = fVar17;
      fVar16 = fVar22;
      if (0 < param_5) {
        iVar12 = 0;
        plVar10 = param_3;
        do {
          if (((plVar10[0x1e] == 0) ||
              (plVar10 = *(long **)(plVar10[0x1e] + 0xe8), plVar10 == (long *)0x0)) ||
             (((param_7 & 1) == 0 &&
              ((plVar10[0x1e] == 0 || (*(long *)(plVar10[0x1e] + 0xe8) == 0)))))) break;
          fVar14 = *(float *)((long)param_3 + 0x4c);
          fVar15 = *(float *)((long)param_3 + 0x5c);
          fVar16 = *(float *)((long)param_3 + 0x6c);
          if ((*(byte *)(plVar10 + 0x25) & 1) != 0) {
            (**(code **)(*plVar10 + 0xa8))(plVar10);
          }
          fVar18 = *(float *)((long)plVar10 + 0x4c);
          fVar23 = *(float *)((long)plVar10 + 0x5c);
          fVar38 = *(float *)((long)plVar10 + 0x6c);
          auVar19._0_4_ = *param_4 - fVar18;
          auVar19._4_4_ = param_4[1] - fVar23;
          auVar19._8_4_ = param_4[2] - fVar38;
          auVar25._0_4_ = fVar14 - fVar18;
          auVar25._4_4_ = fVar15 - fVar23;
          auVar25._8_4_ = fVar16 - fVar38;
          auVar25._12_4_ = 0x3f800000;
          auVar19._12_4_ = 0x3f800000;
          auVar33 = NEON_ext(auVar25,auVar25,8,1);
          auVar36 = NEON_ext(auVar19,auVar19,8,1);
          fVar14 = auVar25._0_4_ * auVar25._0_4_ + auVar33._0_4_ * auVar33._0_4_ +
                   auVar25._4_4_ * auVar25._4_4_ + 0.0;
          fVar15 = auVar19._0_4_ * auVar19._0_4_ + auVar36._0_4_ * auVar36._0_4_ +
                   auVar19._4_4_ * auVar19._4_4_ + 0.0;
          auVar26._4_4_ = fVar14;
          auVar26._0_4_ = fVar14;
          auVar26._8_4_ = fVar14;
          auVar26._12_4_ = fVar14;
          auVar34._4_4_ = fVar15;
          auVar34._0_4_ = fVar15;
          auVar34._8_4_ = fVar15;
          auVar34._12_4_ = fVar15;
          auVar36 = NEON_frsqrte(auVar26,4);
          auVar37 = NEON_frsqrte(auVar34,4);
          fVar14 = auVar36._0_4_;
          fVar15 = auVar36._4_4_;
          fVar29 = auVar36._8_4_;
          auVar33._4_4_ = fVar15 * fVar15;
          auVar33._0_4_ = fVar14 * fVar14;
          auVar33._8_4_ = fVar29 * fVar29;
          auVar33._12_4_ = auVar36._12_4_ * auVar36._12_4_;
          auVar33 = NEON_frsqrts(auVar33,auVar26,4);
          fVar30 = auVar37._0_4_;
          fVar31 = auVar37._4_4_;
          fVar32 = auVar37._8_4_;
          auVar36._4_4_ = fVar31 * fVar31;
          auVar36._0_4_ = fVar30 * fVar30;
          auVar36._8_4_ = fVar32 * fVar32;
          auVar36._12_4_ = auVar37._12_4_ * auVar37._12_4_;
          auVar36 = NEON_frsqrts(auVar36,auVar34,4);
          fVar16 = auVar25._0_4_ * fVar14 * auVar33._0_4_;
          fVar28 = auVar25._4_4_ * fVar15 * auVar33._4_4_;
          fVar29 = auVar25._8_4_ * fVar29 * auVar33._8_4_;
          fVar30 = auVar19._0_4_ * fVar30 * auVar36._0_4_;
          fVar31 = auVar19._4_4_ * fVar31 * auVar36._4_4_;
          fVar32 = auVar19._8_4_ * fVar32 * auVar36._8_4_;
          auVar37._0_4_ = fVar16 * fVar30;
          auVar37._4_4_ = fVar28 * fVar31;
          auVar37._8_4_ = fVar29 * fVar32;
          auVar37._12_4_ = 0;
          auVar33 = NEON_ext(auVar37,auVar37,8,1);
          fVar14 = auVar33._0_4_ + auVar33._4_4_;
          uVar35 = NEON_rev64(CONCAT44(fVar14,auVar37._0_4_ + auVar37._4_4_),4);
          fVar15 = auVar37._0_4_ + auVar37._4_4_ + (float)uVar35;
          if (fVar15 < fVar8) {
            bVar9 = *(byte *)(plVar10 + 0x25);
            fVar39 = (fVar28 * fVar32 - fVar29 * fVar31) * (float)uVar6;
            fVar29 = (fVar16 * fVar32 - fVar29 * fVar30) * (float)((ulong)uVar6 >> 0x20);
            fVar16 = (fVar16 * fVar31 - fVar28 * fVar30) * (float)uVar7;
            if ((bVar9 >> 2 & 1) == 0) {
              if ((*(byte *)((long)plVar10 + 0x129) & 3) == 0) {
                *(float *)(plVar10 + 0x27) = *(float *)(plVar10 + 0xc);
                *(int *)((long)plVar10 + 0x13c) = (int)plVar10[0xe];
                *(float *)(plVar10 + 0x26) = *(float *)(plVar10 + 8);
                *(float *)((long)plVar10 + 0x134) = *(float *)(plVar10 + 10);
                *(float *)(plVar10 + 0x29) = *(float *)((long)plVar10 + 100);
                *(undefined4 *)((long)plVar10 + 0x14c) = *(undefined4 *)((long)plVar10 + 0x74);
                *(float *)(plVar10 + 0x28) = *(float *)((long)plVar10 + 0x44);
                *(float *)((long)plVar10 + 0x144) = *(float *)((long)plVar10 + 0x54);
                *(float *)((long)plVar10 + 0x13c) =
                     -(*(float *)(plVar10 + 8) * fVar18 + *(float *)(plVar10 + 10) * fVar23 +
                      *(float *)(plVar10 + 0xc) * fVar38);
                *(float *)((long)plVar10 + 0x14c) =
                     -(fVar18 * *(float *)((long)plVar10 + 0x44) +
                       fVar23 * *(float *)((long)plVar10 + 0x54) +
                      fVar38 * *(float *)((long)plVar10 + 100));
                plVar10[0x2b] = CONCAT44((int)plVar10[0xf],*(float *)(plVar10 + 0xd));
                plVar10[0x2a] = CONCAT44(*(float *)(plVar10 + 0xb),*(float *)(plVar10 + 9));
                *(float *)((long)plVar10 + 0x15c) =
                     -(fVar18 * *(float *)(plVar10 + 9) + fVar23 * *(float *)(plVar10 + 0xb) +
                      fVar38 * *(float *)(plVar10 + 0xd));
                plVar10[0x2d] = lVar5;
                plVar10[0x2c] = lVar4;
              }
              else {
                Aska::Matrix::InvertLowError(Aska::Matrix*) const(plVar10 + 8,plVar10 + 0x26);
                bVar9 = *(byte *)(plVar10 + 0x25);
              }
              *(byte *)(plVar10 + 0x25) = bVar9 | 4;
            }
            auVar33 = *(undefined1 (*) [16])(plVar10 + 0x26);
            auVar36 = *(undefined1 (*) [16])(plVar10 + 0x28);
            auVar25 = *(undefined1 (*) [16])(plVar10 + 0x2a);
            auVar1._4_4_ = fVar29;
            auVar1._0_4_ = fVar39;
            auVar1._8_4_ = fVar16;
            auVar1._12_4_ = 0x3f800000;
            auVar2._4_4_ = fVar29;
            auVar2._0_4_ = fVar39;
            auVar2._8_4_ = fVar16;
            auVar2._12_4_ = 0x3f800000;
            auVar19 = NEON_ext(auVar1,auVar2,8,1);
            auVar37 = NEON_ext(auVar33,auVar33,8,1);
            auVar34 = NEON_ext(auVar36,auVar36,8,1);
            auVar26 = NEON_ext(auVar25,auVar25,8,1);
            fVar18 = auVar19._0_4_;
            fVar16 = fVar39 * auVar33._0_4_ + fVar18 * auVar37._0_4_ + fVar29 * auVar33._4_4_ + 0.0;
            fVar28 = fVar39 * auVar36._0_4_ + fVar18 * auVar34._0_4_ + fVar29 * auVar36._4_4_ + 0.0;
            fVar18 = fVar39 * auVar25._0_4_ + fVar18 * auVar26._0_4_ + fVar29 * auVar25._4_4_ + 0.0;
            fVar23 = fVar18 * fVar18 + fVar16 * fVar16 + fVar28 * fVar28 + 0.0;
            auVar20._4_4_ = fVar23;
            auVar20._0_4_ = fVar23;
            auVar20._8_4_ = fVar23;
            auVar20._12_4_ = fVar23;
            auVar33 = NEON_frsqrte(auVar20,4);
            fVar23 = auVar33._0_4_;
            auVar27._0_4_ = fVar23 * fVar23;
            fVar29 = auVar33._4_4_;
            auVar27._4_4_ = fVar29 * fVar29;
            fVar30 = auVar33._8_4_;
            auVar27._8_4_ = fVar30 * fVar30;
            auVar27._12_4_ = auVar33._12_4_ * auVar33._12_4_;
            auVar33 = NEON_frsqrts(auVar27,auVar20,4);
            auVar24._0_8_ =
                 CONCAT44(fVar28 * fVar29 * auVar33._4_4_,fVar16 * fVar23 * auVar33._0_4_);
            auVar24._8_4_ = fVar18 * fVar30 * auVar33._8_4_;
            auVar24._12_4_ = 0x3f800000;
            uStack_a8 = auVar24._8_8_;
            uStack_b0 = auVar24._0_8_;
            fVar14 = (float)acosf(CONCAT44(fVar14 + (float)((ulong)uVar35 >> 0x20),fVar15)
                                           );
            auVar3._8_8_ = uStack_a8;
            auVar3._0_8_ = uStack_b0;
            auVar21._0_12_ = auVar3._0_12_;
            auVar21._12_4_ = fVar14 * param_1;
            uStack_a8 = auVar21._8_8_;
            Aska::Quaternion::Create(Aska::Vector const*)(&fStack_c0,&uStack_b0);
            fVar14 = *(float *)(plVar10 + 0x12);
            fVar15 = *(float *)((long)plVar10 + 0x94);
            fVar16 = *(float *)(plVar10 + 0x13);
            fVar18 = *(float *)((long)plVar10 + 0x9c);
            fStack_a0 = (fStack_c0 * fVar18 + fStack_b4 * fVar14 + fStack_b8 * fVar15) -
                        fStack_bc * fVar16;
            fStack_9c = fStack_c0 * fVar16 +
                        fStack_b4 * fVar15 + (fStack_bc * fVar18 - fStack_b8 * fVar14);
            fStack_98 = fStack_b4 * fVar16 +
                        ((fStack_b8 * fVar18 + fStack_bc * fVar14) - fStack_c0 * fVar15);
            fStack_94 = ((fStack_b4 * fVar18 - fStack_c0 * fVar14) - fStack_bc * fVar15) -
                        fStack_b8 * fVar16;
            (**(code **)(*plVar10 + 0xe8))(plVar10,&fStack_a0);
            (**(code **)(*param_3 + 0xa8))(param_3);
          }
          iVar12 = iVar12 + 1;
        } while (iVar12 < param_5);
        fVar14 = *(float *)((long)param_3 + 0x4c);
        fVar15 = *(float *)((long)param_3 + 0x5c);
        fVar16 = *(float *)((long)param_3 + 0x6c);
      }
    } while ((param_2 <=
              (fVar14 - fVar13) * (fVar14 - fVar13) + (fVar15 - fVar17) * (fVar15 - fVar17) +
              (fVar16 - fVar22) * (fVar16 - fVar22)) &&
            (iVar11 = iVar11 + 1, fVar13 = fVar14, fVar17 = fVar15, fVar22 = fVar16,
            iVar11 < param_6));
  }
  return;
}

// ==== Aska::HierarchicalObject::Get(unsigned long, void*) const
// vaddr 0x21341a8 | ghidra 0x22341a8 | size 372 | symbol _ZNK4Aska18HierarchicalObject3GetEmPv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska18HierarchicalObject3GetEmPv(long *param_1,undefined8 param_2,byte *param_3)

{
  undefined8 *puVar1;
  byte bVar2;
  undefined8 uVar3;
  
  if ((short)((ulong)param_2 >> 0x20) != 0) {
    return 0;
  }
  switch((uint)param_2 & 0xffff) {
  case 5:
    *(int *)param_3 = (int)param_1[0x10];
    *(undefined4 *)(param_3 + 4) = *(undefined4 *)((long)param_1 + 0x84);
    *(int *)(param_3 + 8) = (int)param_1[0x11];
    *(undefined4 *)(param_3 + 0xc) = *(undefined4 *)((long)param_1 + 0x8c);
    break;
  case 6:
    *(int *)param_3 = (int)param_1[0x12];
    *(undefined4 *)(param_3 + 4) = *(undefined4 *)((long)param_1 + 0x94);
    *(int *)(param_3 + 8) = (int)param_1[0x13];
    *(undefined4 *)(param_3 + 0xc) = *(undefined4 *)((long)param_1 + 0x9c);
    break;
  case 7:
    *(int *)param_3 = (int)param_1[0x14];
    *(undefined4 *)(param_3 + 4) = *(undefined4 *)((long)param_1 + 0xa4);
    *(int *)(param_3 + 8) = (int)param_1[0x15];
    *(undefined4 *)(param_3 + 0xc) = *(undefined4 *)((long)param_1 + 0xac);
    break;
  case 8:
    bVar2 = *(byte *)((long)param_1 + 0x129) & 3;
    goto code_r0x0223430c;
  case 9:
    *(int *)param_3 = (int)param_1[0x16];
    *(undefined4 *)(param_3 + 4) = *(undefined4 *)((long)param_1 + 0xb4);
    *(int *)(param_3 + 8) = (int)param_1[0x17];
    *(undefined4 *)(param_3 + 0xc) = *(undefined4 *)((long)param_1 + 0xbc);
    break;
  case 10:
    *(int *)param_3 = (int)param_1[0x1a];
    *(undefined4 *)(param_3 + 4) = *(undefined4 *)((long)param_1 + 0xd4);
    *(int *)(param_3 + 8) = (int)param_1[0x1b];
    *(undefined4 *)(param_3 + 0xc) = *(undefined4 *)((long)param_1 + 0xdc);
    break;
  case 0xb:
    *(int *)param_3 = (int)param_1[0x1c];
    *(undefined4 *)(param_3 + 4) = *(undefined4 *)((long)param_1 + 0xe4);
    *(int *)(param_3 + 8) = (int)param_1[0x1d];
    *(undefined4 *)(param_3 + 0xc) = *(undefined4 *)((long)param_1 + 0xec);
    break;
  case 0xc:
    puVar1 = (undefined8 *)(**(code **)(*param_1 + 0x98))();
    uVar3 = *puVar1;
    *(undefined8 *)(param_3 + 8) = puVar1[1];
    *(undefined8 *)param_3 = uVar3;
    uVar3 = puVar1[2];
    *(undefined8 *)(param_3 + 0x18) = puVar1[3];
    *(undefined8 *)(param_3 + 0x10) = uVar3;
    uVar3 = puVar1[4];
    *(undefined8 *)(param_3 + 0x28) = puVar1[5];
    *(undefined8 *)(param_3 + 0x20) = uVar3;
    uVar3 = puVar1[6];
    *(undefined8 *)(param_3 + 0x38) = puVar1[7];
    *(undefined8 *)(param_3 + 0x30) = uVar3;
    break;
  case 0xd:
    bVar2 = *(byte *)((long)param_1 + 0x194);
code_r0x0223430c:
    *param_3 = bVar2;
    break;
  default:
    return 0;
  }
  return 1;
}

// ==== Aska::HierarchicalObject::Set(unsigned long, void const*)
// vaddr 0x213431c | ghidra 0x223431c | size 280 | symbol _ZN4Aska18HierarchicalObject3SetEmPKv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZN4Aska18HierarchicalObject3SetEmPKv(long *param_1,ulong param_2,long *param_3)

{
  undefined4 uVar1;
  code *pcVar2;
  long lVar3;
  
  if ((param_2 & 0xffff00000000) != 0) {
    return 0;
  }
  uVar1 = 0;
  switch((uint)param_2 & 0xffff) {
  case 5:
    pcVar2 = *(code **)(*param_1 + 0xd0);
    goto code_r0x02234378;
  case 6:
    pcVar2 = *(code **)(*param_1 + 0xe8);
    goto code_r0x02234378;
  case 7:
    pcVar2 = *(code **)(*param_1 + 0x100);
code_r0x02234378:
    (*pcVar2)(param_1,param_3);
    break;
  default:
    goto code_r0x02234428;
  case 9:
    *(int *)(param_1 + 0x16) = (int)*param_3;
    *(undefined4 *)((long)param_1 + 0xb4) = *(undefined4 *)((long)param_3 + 4);
    *(int *)(param_1 + 0x17) = (int)param_3[1];
    *(undefined4 *)((long)param_1 + 0xbc) = *(undefined4 *)((long)param_3 + 0xc);
    lVar3 = *param_3;
    param_1[0x27] = param_3[1];
    param_1[0x26] = lVar3;
    lVar3 = param_3[2];
    param_1[0x29] = param_3[3];
    param_1[0x28] = lVar3;
    lVar3 = param_3[4];
    param_1[0x2b] = param_3[5];
    param_1[0x2a] = lVar3;
    lVar3 = param_3[6];
    param_1[0x2d] = param_3[7];
    param_1[0x2c] = lVar3;
    break;
  case 10:
    *(int *)(param_1 + 0x1a) = (int)*param_3;
    *(undefined4 *)((long)param_1 + 0xd4) = *(undefined4 *)((long)param_3 + 4);
    *(int *)(param_1 + 0x1b) = (int)param_3[1];
    *(undefined4 *)((long)param_1 + 0xdc) = *(undefined4 *)((long)param_3 + 0xc);
    break;
  case 0xb:
    *(int *)(param_1 + 0x1c) = (int)*param_3;
    *(undefined4 *)((long)param_1 + 0xe4) = *(undefined4 *)((long)param_3 + 4);
    *(int *)(param_1 + 0x1d) = (int)param_3[1];
    *(undefined4 *)((long)param_1 + 0xec) = *(undefined4 *)((long)param_3 + 0xc);
    break;
  case 0xd:
    *(char *)((long)param_1 + 0x194) = (char)*param_3;
    (**(code **)(*param_1 + 0x158))();
  }
  uVar1 = 1;
code_r0x02234428:
  return uVar1;
}

// ==== Aska::HierarchicalObject::~HierarchicalObject()
// vaddr 0x2134434 | ghidra 0x2234434 | size 24 | symbol _ZN4Aska18HierarchicalObjectD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18HierarchicalObjectD0Ev(undefined8 param_1)

{
  Aska::HierarchicalObject::~HierarchicalObject()();
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::HierarchicalObject::GetClassID(int) const
// vaddr 0x213444c | ghidra 0x223444c | size 68 | symbol _ZNK4Aska18HierarchicalObject10GetClassIDEi | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska18HierarchicalObject10GetClassIDEi(undefined8 param_1,int param_2)

{
  undefined8 uVar1;
  undefined8 uVar2;
  
  if (param_2 != 0) {
    uVar2 = 0xf000f001;
    if (param_2 != 2) {
      uVar2 = 0xf000;
    }
    uVar1 = 0xf000f001f002;
    if (param_2 != 1) {
      uVar1 = uVar2;
    }
    return uVar1;
  }
  return 0xf000f002f111;
}

// ==== Aska::HierarchicalObjectContainer::CopyParameter(Aska::HierarchicalObject const*)
// vaddr 0x2134490 | ghidra 0x2234490 | size 8 | symbol _ZN4Aska27HierarchicalObjectContainer13CopyParameterEPKNS_18HierarchicalObjectE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska27HierarchicalObjectContainer13CopyParameterEPKNS_18HierarchicalObjectE
               (undefined8 param_1,long param_2)

{
  (*(code *)PTR__ZN4Aska27HierarchicalObjectContainer13CopyParameterEPKS0__02c93590)
            (param_1,param_2 + 0x30);
  return;
}

// ==== Aska::HierarchicalObjectContainer::CopyParameter(Aska::HierarchicalObjectContainer const*)
// vaddr 0x2134498 | ghidra 0x2234498 | size 340 | symbol _ZN4Aska27HierarchicalObjectContainer13CopyParameterEPKS0_ | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska27HierarchicalObjectContainer13CopyParameterEPKS0_(long param_1,long param_2)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  undefined8 uVar4;
  
  if (param_2 != 0) {
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(param_2 + 0x50);
    *(undefined4 *)(param_1 + 0x54) = *(undefined4 *)(param_2 + 0x54);
    *(undefined4 *)(param_1 + 0x58) = *(undefined4 *)(param_2 + 0x58);
    *(undefined4 *)(param_1 + 0x5c) = *(undefined4 *)(param_2 + 0x5c);
    *(undefined4 *)(param_1 + 0x60) = *(undefined4 *)(param_2 + 0x60);
    *(undefined4 *)(param_1 + 100) = *(undefined4 *)(param_2 + 100);
    *(undefined4 *)(param_1 + 0x68) = *(undefined4 *)(param_2 + 0x68);
    *(undefined4 *)(param_1 + 0x6c) = *(undefined4 *)(param_2 + 0x6c);
    *(undefined4 *)(param_1 + 0x70) = *(undefined4 *)(param_2 + 0x70);
    *(undefined4 *)(param_1 + 0x74) = *(undefined4 *)(param_2 + 0x74);
    *(undefined4 *)(param_1 + 0x78) = *(undefined4 *)(param_2 + 0x78);
    bVar2 = *(byte *)(param_1 + 0xf9);
    *(undefined4 *)(param_1 + 0x7c) = *(undefined4 *)(param_2 + 0x7c);
    bVar1 = *(byte *)(param_2 + 0xf9) & 3;
    *(byte *)(param_1 + 0xf9) = bVar2 & 0xfc | bVar1;
    bVar3 = *(byte *)(param_2 + 0xf8);
    *(byte *)(param_1 + 0xf8) = *(byte *)(param_1 + 0xf8) & 0xfe | bVar3 & 1;
    if ((bVar3 & 1) == 0) {
      uVar4 = *(undefined8 *)(param_2 + 0x10);
      *(undefined8 *)(param_1 + 0x18) = *(undefined8 *)(param_2 + 0x18);
      *(undefined8 *)(param_1 + 0x10) = uVar4;
      uVar4 = *(undefined8 *)(param_2 + 0x20);
      *(undefined8 *)(param_1 + 0x28) = *(undefined8 *)(param_2 + 0x28);
      *(undefined8 *)(param_1 + 0x20) = uVar4;
      uVar4 = *(undefined8 *)(param_2 + 0x30);
      *(undefined8 *)(param_1 + 0x38) = *(undefined8 *)(param_2 + 0x38);
      *(undefined8 *)(param_1 + 0x30) = uVar4;
      uVar4 = *(undefined8 *)(param_2 + 0x40);
      *(undefined8 *)(param_1 + 0x48) = *(undefined8 *)(param_2 + 0x48);
      *(undefined8 *)(param_1 + 0x40) = uVar4;
    }
    *(undefined4 *)(param_1 + 0xb0) = *(undefined4 *)(param_2 + 0xb0);
    *(undefined4 *)(param_1 + 0xb4) = *(undefined4 *)(param_2 + 0xb4);
    *(undefined4 *)(param_1 + 0xb8) = *(undefined4 *)(param_2 + 0xb8);
    *(undefined4 *)(param_1 + 0xbc) = *(undefined4 *)(param_2 + 0xbc);
    *(undefined4 *)(param_1 + 0x80) = *(undefined4 *)(param_2 + 0x80);
    *(undefined4 *)(param_1 + 0x84) = *(undefined4 *)(param_2 + 0x84);
    *(undefined4 *)(param_1 + 0x88) = *(undefined4 *)(param_2 + 0x88);
    *(undefined4 *)(param_1 + 0x8c) = *(undefined4 *)(param_2 + 0x8c);
    *(undefined4 *)(param_1 + 0xa0) = *(undefined4 *)(param_2 + 0xa0);
    *(undefined4 *)(param_1 + 0xa4) = *(undefined4 *)(param_2 + 0xa4);
    *(undefined4 *)(param_1 + 0xa8) = *(undefined4 *)(param_2 + 0xa8);
    *(undefined4 *)(param_1 + 0xac) = *(undefined4 *)(param_2 + 0xac);
    *(undefined4 *)(param_1 + 0x90) = *(undefined4 *)(param_2 + 0x90);
    *(undefined4 *)(param_1 + 0x94) = *(undefined4 *)(param_2 + 0x94);
    *(undefined4 *)(param_1 + 0x98) = *(undefined4 *)(param_2 + 0x98);
    *(undefined4 *)(param_1 + 0x9c) = *(undefined4 *)(param_2 + 0x9c);
    *(byte *)(param_1 + 0xf9) = bVar2 & 0xf8 | bVar1 | *(byte *)(param_2 + 0xf9) & 4;
    return 1;
  }
  return 0;
}

// ==== Aska::HierarchicalObjectContainer::Clone(Aska::IAnimatable const*)
// vaddr 0x21345ec | ghidra 0x22345ec | size 532 | symbol _ZN4Aska27HierarchicalObjectContainer5CloneEPKNS_11IAnimatableE | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska27HierarchicalObjectContainer5CloneEPKNS_11IAnimatableE(long param_1,long param_2)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  ulong uVar4;
  long lVar5;
  undefined8 uVar6;
  long lVar7;
  
  uVar4 = Aska::IAnimatable::Clone(Aska::IAnimatable const*)();
  if ((uVar4 & 1) == 0) {
    uVar6 = 0;
  }
  else {
    bVar3 = *(byte *)(param_1 + 0xf8);
    bVar1 = *(byte *)(param_2 + 0xf8) & 4;
    *(byte *)(param_1 + 0xf8) = bVar3 & 0xfb | bVar1;
    bVar2 = *(byte *)(param_2 + 0xf8) & 8;
    *(byte *)(param_1 + 0xf8) = bVar3 & 0xf3 | bVar1 | bVar2;
    *(byte *)(param_1 + 0xf8) = bVar3 & 0xe3 | bVar1 | bVar2 | *(byte *)(param_2 + 0xf8) & 0x10;
    if ((bVar3 & 1) == 0) {
      uVar6 = *(undefined8 *)(param_2 + 0x10);
      *(undefined8 *)(param_1 + 0x18) = *(undefined8 *)(param_2 + 0x18);
      *(undefined8 *)(param_1 + 0x10) = uVar6;
      uVar6 = *(undefined8 *)(param_2 + 0x20);
      *(undefined8 *)(param_1 + 0x28) = *(undefined8 *)(param_2 + 0x28);
      *(undefined8 *)(param_1 + 0x20) = uVar6;
      uVar6 = *(undefined8 *)(param_2 + 0x30);
      *(undefined8 *)(param_1 + 0x38) = *(undefined8 *)(param_2 + 0x38);
      *(undefined8 *)(param_1 + 0x30) = uVar6;
      uVar6 = *(undefined8 *)(param_2 + 0x40);
      *(undefined8 *)(param_1 + 0x48) = *(undefined8 *)(param_2 + 0x48);
      *(undefined8 *)(param_1 + 0x40) = uVar6;
    }
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(param_2 + 0x50);
    *(undefined4 *)(param_1 + 0x54) = *(undefined4 *)(param_2 + 0x54);
    *(undefined4 *)(param_1 + 0x58) = *(undefined4 *)(param_2 + 0x58);
    *(undefined4 *)(param_1 + 0x5c) = *(undefined4 *)(param_2 + 0x5c);
    *(undefined4 *)(param_1 + 0x60) = *(undefined4 *)(param_2 + 0x60);
    *(undefined4 *)(param_1 + 100) = *(undefined4 *)(param_2 + 100);
    *(undefined4 *)(param_1 + 0x68) = *(undefined4 *)(param_2 + 0x68);
    *(undefined4 *)(param_1 + 0x6c) = *(undefined4 *)(param_2 + 0x6c);
    *(undefined4 *)(param_1 + 0x70) = *(undefined4 *)(param_2 + 0x70);
    *(undefined4 *)(param_1 + 0x74) = *(undefined4 *)(param_2 + 0x74);
    *(undefined4 *)(param_1 + 0x78) = *(undefined4 *)(param_2 + 0x78);
    *(undefined4 *)(param_1 + 0x7c) = *(undefined4 *)(param_2 + 0x7c);
    *(undefined4 *)(param_1 + 0xb0) = *(undefined4 *)(param_2 + 0xb0);
    *(undefined4 *)(param_1 + 0xb4) = *(undefined4 *)(param_2 + 0xb4);
    *(undefined4 *)(param_1 + 0xb8) = *(undefined4 *)(param_2 + 0xb8);
    *(undefined4 *)(param_1 + 0xbc) = *(undefined4 *)(param_2 + 0xbc);
    *(undefined4 *)(param_1 + 0x80) = *(undefined4 *)(param_2 + 0x80);
    *(undefined4 *)(param_1 + 0x84) = *(undefined4 *)(param_2 + 0x84);
    *(undefined4 *)(param_1 + 0x88) = *(undefined4 *)(param_2 + 0x88);
    *(undefined4 *)(param_1 + 0x8c) = *(undefined4 *)(param_2 + 0x8c);
    *(undefined4 *)(param_1 + 0xa0) = *(undefined4 *)(param_2 + 0xa0);
    *(undefined4 *)(param_1 + 0xa4) = *(undefined4 *)(param_2 + 0xa4);
    *(undefined4 *)(param_1 + 0xa8) = *(undefined4 *)(param_2 + 0xa8);
    *(undefined4 *)(param_1 + 0xac) = *(undefined4 *)(param_2 + 0xac);
    *(undefined4 *)(param_1 + 0x90) = *(undefined4 *)(param_2 + 0x90);
    *(undefined4 *)(param_1 + 0x94) = *(undefined4 *)(param_2 + 0x94);
    *(undefined4 *)(param_1 + 0x98) = *(undefined4 *)(param_2 + 0x98);
    *(undefined4 *)(param_1 + 0x9c) = *(undefined4 *)(param_2 + 0x9c);
    *(byte *)(param_1 + 0xf9) = *(byte *)(param_1 + 0xf9) & 0xfb | *(byte *)(param_2 + 0xf9) & 4;
    lVar7 = *(long *)(param_2 + 0xc0);
    if (lVar7 != 0) {
      if (*(long *)(param_1 + 0xc0) != 0) {
        Aska::HierarchicalObjectContainer::DetachFromParent()(param_1);
      }
      lVar5 = *(long *)(lVar7 + 200);
      if (lVar5 == 0) {
        *(long *)(lVar7 + 200) = param_1;
        *(long *)(param_1 + 0xc0) = lVar7;
        lVar5 = param_1;
        lVar7 = param_1;
      }
      else {
        uVar6 = *(undefined8 *)(lVar5 + 0xd0);
        *(long *)(param_1 + 0xc0) = lVar7;
        *(undefined8 *)(param_1 + 0xd0) = uVar6;
        *(long *)(param_1 + 0xd8) = lVar5;
        lVar7 = *(long *)(lVar5 + 0xd0);
      }
      *(long *)(lVar7 + 0xd8) = param_1;
      *(long *)(lVar5 + 0xd0) = param_1;
      if ((*(byte *)(param_1 + 0xf8) & 1) == 0) {
        void Function_UpdateHierarchicallyByUsingStack<256, false>(Aska::HierarchicalObjectContainer*)(param_1);
      }
    }
    uVar6 = 1;
    *(byte *)(param_1 + 0xf9) = *(byte *)(param_1 + 0xf9) & 0xfc | *(byte *)(param_2 + 0xf9) & 3;
    *(byte *)(param_1 + 0xf8) = *(byte *)(param_1 + 0xf8) & 0xfe | *(byte *)(param_2 + 0xf8) & 1;
  }
  return uVar6;
}

// ==== Aska::HierarchicalObjectContainer::DetachFromParent()
// vaddr 0x2134800 | ghidra 0x2234800 | size 280 | symbol _ZN4Aska27HierarchicalObjectContainer16DetachFromParentEv | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Possible PIC construction at 0x022348a4: Changing call to branch */

void _ZN4Aska27HierarchicalObjectContainer16DetachFromParentEv(long param_1)

{
  long lVar1;
  long lVar2;
  undefined8 uVar3;
  long lVar4;
  long lVar5;
  long lVar6;
  long lVar7;
  
  lVar5 = *(long *)(param_1 + 0xc0);
  if (lVar5 != 0) {
    if (*(long *)(lVar5 + 200) == param_1) {
      lVar6 = 0;
      if (*(long *)(param_1 + 0xd8) != param_1) {
        lVar6 = *(long *)(param_1 + 0xd8);
      }
      *(long *)(lVar5 + 200) = lVar6;
    }
    if (*(long *)(param_1 + 0xd8) != param_1) {
      *(undefined8 *)(*(long *)(param_1 + 0xd8) + 0xd0) = *(undefined8 *)(param_1 + 0xd0);
      *(undefined8 *)(*(long *)(param_1 + 0xd0) + 0xd8) = *(undefined8 *)(param_1 + 0xd8);
    }
  }
  lVar6 = *(long *)(param_1 + 200);
  if (lVar6 != 0) {
    lVar1 = lVar6;
    if (lVar5 == 0) {
      do {
        lVar5 = *(long *)(lVar1 + 0xd8);
        *(undefined8 *)(lVar1 + 0xc0) = 0;
        *(long *)(lVar1 + 0xd0) = lVar1;
        *(long *)(lVar1 + 0xd8) = lVar1;
        if ((*(byte *)(lVar1 + 0xf8) & 1) == 0) {
          void Function_UpdateHierarchicallyByUsingStack<256, false>(Aska::HierarchicalObjectContainer*)();
        }
        lVar1 = lVar5;
      } while (lVar5 != lVar6);
    }
    else {
      do {
        *(undefined8 *)(lVar1 + 0xc0) = 0;
        lVar2 = *(long *)(lVar5 + 200);
        lVar7 = *(long *)(lVar1 + 0xd8);
        if (lVar2 == 0) {
          *(long *)(lVar5 + 200) = lVar1;
          *(long *)(lVar1 + 0xc0) = lVar5;
          lVar2 = lVar1;
          lVar4 = lVar1;
        }
        else {
          uVar3 = *(undefined8 *)(lVar2 + 0xd0);
          *(long *)(lVar1 + 0xc0) = lVar5;
          *(undefined8 *)(lVar1 + 0xd0) = uVar3;
          *(long *)(lVar1 + 0xd8) = lVar2;
          lVar4 = *(long *)(lVar2 + 0xd0);
        }
        *(long *)(lVar4 + 0xd8) = lVar1;
        *(long *)(lVar2 + 0xd0) = lVar1;
        if ((*(byte *)(lVar1 + 0xf8) & 1) == 0) goto code_r0x011ca170;
        lVar1 = lVar7;
      } while (lVar7 != lVar6);
    }
    *(undefined8 *)(param_1 + 200) = 0;
  }
  *(undefined8 *)(param_1 + 0xc0) = 0;
  *(long *)(param_1 + 0xd0) = param_1;
  *(long *)(param_1 + 0xd8) = param_1;
  lVar1 = param_1;
  if ((*(byte *)(param_1 + 0xf8) & 1) != 0) {
    return;
  }
code_r0x011ca170:
  (*(code *)
    PTR__Z41Function_UpdateHierarchicallyByUsingStackILi256ELb0EEvPN4Aska27HierarchicalObjectContainerE_02c9d0a8
  )(lVar1);
  return;
}

// ==== Aska::HierarchicalObjectContainer::AttachChild(Aska::HierarchicalObjectContainer*)
// vaddr 0x2134918 | ghidra 0x2234918 | size 72 | symbol _ZN4Aska27HierarchicalObjectContainer11AttachChildEPS0_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska27HierarchicalObjectContainer11AttachChildEPS0_(long param_1,long param_2)

{
  long lVar1;
  undefined8 uVar2;
  long lVar3;
  
  lVar1 = *(long *)(param_1 + 200);
  if (lVar1 == 0) {
    *(long *)(param_1 + 200) = param_2;
    *(long *)(param_2 + 0xc0) = param_1;
    lVar1 = param_2;
    lVar3 = param_2;
  }
  else {
    uVar2 = *(undefined8 *)(lVar1 + 0xd0);
    *(long *)(param_2 + 0xc0) = param_1;
    *(undefined8 *)(param_2 + 0xd0) = uVar2;
    *(long *)(param_2 + 0xd8) = lVar1;
    lVar3 = *(long *)(lVar1 + 0xd0);
  }
  *(long *)(lVar3 + 0xd8) = param_2;
  *(long *)(lVar1 + 0xd0) = param_2;
  if ((*(byte *)(param_2 + 0xf8) & 1) == 0) {
    (*(code *)
      PTR__Z41Function_UpdateHierarchicallyByUsingStackILi256ELb0EEvPN4Aska27HierarchicalObjectContainerE_02c9d0a8
    )(param_2);
    return;
  }
  return;
}

// ==== Aska::HierarchicalObjectContainer::CreateClone(Aska::IAnimatable const*)
// vaddr 0x2134960 | ghidra 0x2234960 | size 204 | symbol _ZN4Aska27HierarchicalObjectContainer11CreateCloneEPKNS_11IAnimatableE | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

long * _ZN4Aska27HierarchicalObjectContainer11CreateCloneEPKNS_11IAnimatableE
                 (undefined8 param_1,undefined8 param_2)

{
  long lVar1;
  long lVar2;
  long *plVar3;
  ulong uVar4;
  long *plVar5;
  long *plVar6;
  undefined1 auVar7 [16];
  
  plVar3 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x100,PTR__ZSt7nothrow_02cb9a80);
  lVar2 = _UNK_027dbb38;
  lVar1 = _UNK_027dbb30;
  if (plVar3 != (long *)0x0) {
    auVar7 = NEON_fmov(0x3f800000,4);
    *plVar3 = (long)(PTR__ZTVN4Aska27HierarchicalObjectContainerE_02cb81a8 + 0x10);
    plVar3[0xd] = lVar2;
    plVar3[0xc] = lVar1;
    plVar3[0xf] = auVar7._8_8_;
    plVar3[0xe] = auVar7._0_8_;
    *(undefined2 *)(plVar3 + 0x1f) = 1;
    plVar3[0xb] = lVar2;
    plVar3[10] = lVar1;
    plVar5 = plVar3 + 0x12;
    do {
      plVar6 = (long *)((long)plVar5 + 0x7fU & 0xffffffffffffff81);
      Hint_Prefetch(plVar5,0,2,0);
      plVar5 = plVar6;
    } while (plVar6 < plVar3 + 0x14);
    *(undefined1 *)((long)plVar3 + 0xf9) = 0;
    plVar3[0x15] = lVar2;
    plVar3[0x14] = lVar1;
    plVar3[0x17] = lVar2;
    plVar3[0x16] = lVar1;
    plVar3[0x11] = lVar2;
    plVar3[0x10] = lVar1;
    plVar3[0x1c] = 0;
    plVar3[0x1d] = 0;
    plVar3[0x1a] = (long)plVar3;
    plVar3[0x1b] = (long)plVar3;
    plVar3[0x12] = 0;
    plVar3[0x13] = 0x3f80000000000000;
    plVar3[0x1e] = (long)(plVar3 + 2);
    plVar3[0x18] = 0;
    plVar3[0x19] = 0;
    uVar4 = Aska::HierarchicalObjectContainer::Clone(Aska::IAnimatable const*)(plVar3,param_2);
    if ((uVar4 & 1) == 0) {
      (**(code **)(*plVar3 + 8))(plVar3);
      plVar3 = (long *)0x0;
    }
  }
  return plVar3;
}

// ==== Aska::HierarchicalObjectContainer::InvalidateMatrixHierarchically()
// vaddr 0x2134a2c | ghidra 0x2234a2c | size 124 | symbol _ZN4Aska27HierarchicalObjectContainer30InvalidateMatrixHierarchicallyEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska27HierarchicalObjectContainer30InvalidateMatrixHierarchicallyEv(long param_1)

{
  bool bVar1;
  long lVar2;
  long lVar3;
  long lVar4;
  
  *(byte *)(param_1 + 0xf8) = *(byte *)(param_1 + 0xf8) & 0xe0 | 1;
  if (*(long *)(param_1 + 200) != 0) {
    bVar1 = false;
    lVar2 = *(long *)(param_1 + 200);
    do {
      lVar3 = lVar2;
      if (!bVar1) {
        do {
          lVar2 = lVar3;
          if ((*(byte *)(lVar2 + 0xf8) & 1) != 0) break;
          *(byte *)(lVar2 + 0xf8) = *(byte *)(lVar2 + 0xf8) & 0xe0 | 1;
          lVar3 = *(long *)(lVar2 + 200);
        } while (*(long *)(lVar2 + 200) != 0);
      }
      lVar3 = *(long *)(lVar2 + 0xd8);
      lVar4 = *(long *)(lVar2 + 0xc0);
    } while (((lVar3 != lVar2) && (bVar1 = false, lVar2 = lVar3, lVar3 != *(long *)(lVar4 + 200)))
            || (bVar1 = true, lVar2 = lVar4, lVar4 != param_1));
  }
  return;
}

// ==== Aska::HierarchicalObjectContainer::UpdateHierarchically()
// vaddr 0x2134aa8 | ghidra 0x2234aa8 | size 4 | symbol _ZN4Aska27HierarchicalObjectContainer20UpdateHierarchicallyEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska27HierarchicalObjectContainer20UpdateHierarchicallyEv(void)

{
  (*(code *)
    PTR__Z41Function_UpdateHierarchicallyByUsingStackILi256ELb0EEvPN4Aska27HierarchicalObjectContainerE_02c9d0a8
  )();
  return;
}

// ==== Aska::HierarchicalObjectContainer::ForceUpdateHierarchically()
// vaddr 0x2134cf8 | ghidra 0x2234cf8 | size 4 | symbol _ZN4Aska27HierarchicalObjectContainer25ForceUpdateHierarchicallyEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska27HierarchicalObjectContainer25ForceUpdateHierarchicallyEv(void)

{
  (*(code *)
    PTR__Z41Function_UpdateHierarchicallyByUsingStackILi256ELb1EEvPN4Aska27HierarchicalObjectContainerE_02c8faa0
  )();
  return;
}

// ==== Aska::HierarchicalObjectContainer::GetChildObjectCount() const
// vaddr 0x2134f5c | ghidra 0x2234f5c | size 44 | symbol _ZNK4Aska27HierarchicalObjectContainer19GetChildObjectCountEv | lib libSOA-3.7.0.so | 2026-10-04
int _ZNK4Aska27HierarchicalObjectContainer19GetChildObjectCountEv(long param_1)

{
  int iVar1;
  long lVar2;
  long lVar3;
  
  lVar2 = *(long *)(param_1 + 200);
  if (lVar2 != 0) {
    iVar1 = 0;
    lVar3 = lVar2;
    do {
      lVar3 = *(long *)(lVar3 + 0xd8);
      iVar1 = iVar1 + 1;
    } while (lVar3 != lVar2);
    return iVar1;
  }
  return 0;
}

// ==== Aska::HierarchicalObjectContainer::ChildObject(int) const
// vaddr 0x2134f88 | ghidra 0x2234f88 | size 44 | symbol _ZNK4Aska27HierarchicalObjectContainer11ChildObjectEi | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK4Aska27HierarchicalObjectContainer11ChildObjectEi(long param_1,int param_2)

{
  long lVar1;
  long lVar2;
  
  lVar2 = *(long *)(param_1 + 200);
  if (lVar2 != 0) {
    param_2 = param_2 + 1;
    lVar1 = lVar2;
    do {
      param_2 = param_2 + -1;
      if (param_2 == 0) {
        return lVar1;
      }
      lVar1 = *(long *)(lVar1 + 0xd8);
    } while (lVar1 != lVar2);
  }
  return 0;
}

// ==== Aska::HierarchicalObjectContainer::MakeTransformParam()
// vaddr 0x2134fb4 | ghidra 0x2234fb4 | size 364 | symbol _ZN4Aska27HierarchicalObjectContainer18MakeTransformParamEv | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska27HierarchicalObjectContainer18MakeTransformParamEv(long param_1)

{
  long *plVar1;
  undefined8 *puVar2;
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
  undefined8 uStack_60;
  undefined8 uStack_58;
  undefined8 uStack_50;
  undefined8 uStack_48;
  undefined8 uStack_40;
  undefined8 uStack_38;
  undefined8 uStack_30;
  undefined8 uStack_28;
  
  puVar2 = &uStack_60;
  lVar3 = *(long *)(param_1 + 0xc0);
  if (lVar3 == 0) {
    puVar2 = (undefined8 *)(param_1 + 0x10);
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(param_1 + 0x1c);
    *(undefined4 *)(param_1 + 0x54) = *(undefined4 *)(param_1 + 0x2c);
    *(undefined4 *)(param_1 + 0x58) = *(undefined4 *)(param_1 + 0x3c);
    *(undefined4 *)(param_1 + 0x5c) = 0x3f800000;
  }
  else {
    plVar1 = *(long **)(lVar3 + 0xe8);
    if (plVar1 == (long *)0x0) {
      if ((*(byte *)(lVar3 + 0xf8) & 1) != 0) {
        Aska::HierarchicalObjectContainer::MakeMatrix()(lVar3);
      }
    }
    else if ((*(byte *)(plVar1 + 0x25) & 1) != 0) {
      (**(code **)(*plVar1 + 0xa8))();
    }
    fVar13 = (float)((ulong)*(undefined8 *)(lVar3 + 0x10) >> 0x20);
    fVar9 = (float)((ulong)*(undefined8 *)(lVar3 + 0x20) >> 0x20);
    fVar14 = (float)*(undefined8 *)(lVar3 + 0x18);
    fVar10 = (float)*(undefined8 *)(lVar3 + 0x28);
    fVar15 = (float)((ulong)*(undefined8 *)(lVar3 + 0x18) >> 0x20);
    fVar11 = (float)((ulong)*(undefined8 *)(lVar3 + 0x28) >> 0x20);
    fVar12 = (float)*(undefined8 *)(lVar3 + 0x10);
    fVar8 = (float)*(undefined8 *)(lVar3 + 0x20);
    fVar5 = (float)((ulong)*(undefined8 *)(lVar3 + 0x30) >> 0x20);
    fVar6 = (float)*(undefined8 *)(lVar3 + 0x38);
    uStack_60 = CONCAT44(fVar8,fVar12);
    fVar7 = (float)((ulong)*(undefined8 *)(lVar3 + 0x38) >> 0x20);
    fVar4 = (float)*(undefined8 *)(lVar3 + 0x30);
    uStack_58 = CONCAT44(-(fVar15 * fVar12 + fVar11 * fVar8 + fVar7 * fVar4),fVar4);
    uStack_48 = CONCAT44(-(fVar13 * fVar15 + fVar9 * fVar11 + fVar5 * fVar7),fVar5);
    uStack_38 = CONCAT44(-(fVar14 * fVar15 + fVar10 * fVar11 + fVar6 * fVar7),fVar6);
    uStack_50 = CONCAT44(fVar9,fVar13);
    uStack_40 = CONCAT44(fVar10,fVar14);
    uStack_28 = _UNK_027dbb38;
    uStack_30 = _UNK_027dbb30;
    Aska::Matrix::Mul(Aska::Matrix const*, Aska::Matrix const*)(&uStack_60,&uStack_60,param_1 + 0x10);
    *(undefined4 *)(param_1 + 0x50) = uStack_58._4_4_;
    *(undefined4 *)(param_1 + 0x54) = uStack_48._4_4_;
    *(undefined4 *)(param_1 + 0x58) = uStack_38._4_4_;
    *(undefined4 *)(param_1 + 0x5c) = 0x3f800000;
  }
  Aska::Quaternion::Create(Aska::Matrix const*)(param_1 + 0x60,puVar2);
  *(byte *)(param_1 + 0xf8) = *(byte *)(param_1 + 0xf8) & 0xfe;
  return;
}

// ==== Aska::HierarchicalObjectContainer::MakeMatrix()
// vaddr 0x2135120 | ghidra 0x2235120 | size 584 | symbol _ZN4Aska27HierarchicalObjectContainer10MakeMatrixEv | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska27HierarchicalObjectContainer10MakeMatrixEv(long param_1)

{
  byte bVar1;
  undefined8 *puVar2;
  long lVar3;
  long lVar4;
  float fVar5;
  float fVar7;
  undefined8 uVar6;
  float fVar8;
  float fVar9;
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
  float fVar22;
  undefined1 auVar21 [16];
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
  float fVar38;
  float fVar39;
  undefined8 uVar10;
  
  lVar3 = *(long *)(param_1 + 0xc0);
  lVar4 = *(long *)(param_1 + 0xe8);
  if ((lVar3 != 0) && ((*(byte *)(lVar3 + 0xf8) & 1) != 0)) {
    if (*(long **)(lVar3 + 0xe8) == (long *)0x0) {
      _ZN4Aska27HierarchicalObjectContainer10MakeMatrixEv(lVar3);
    }
    else {
      (**(code **)(**(long **)(lVar3 + 0xe8) + 0xa8))();
    }
  }
  Hint_Prefetch(param_1 + 0x10,0,2,0);
  fVar5 = (float)*(undefined8 *)(param_1 + 0x50) + (float)*(undefined8 *)(param_1 + 0x80);
  fVar7 = (float)((ulong)*(undefined8 *)(param_1 + 0x50) >> 0x20) +
          (float)((ulong)*(undefined8 *)(param_1 + 0x80) >> 0x20);
  fVar8 = (float)*(undefined8 *)(param_1 + 0x58) + (float)*(undefined8 *)(param_1 + 0x88);
  fVar9 = (float)*(undefined8 *)(param_1 + 0x60);
  fVar11 = (float)((ulong)*(undefined8 *)(param_1 + 0x60) >> 0x20);
  fVar12 = (float)*(undefined8 *)(param_1 + 0x68);
  fVar14 = fVar12 + fVar12;
  fVar16 = (float)((ulong)*(undefined8 *)(param_1 + 0x68) >> 0x20);
  fVar16 = fVar16 + fVar16;
  fVar24 = (float)*(undefined8 *)(param_1 + 0x70);
  fVar25 = (float)((ulong)*(undefined8 *)(param_1 + 0x70) >> 0x20);
  fVar26 = (float)*(undefined8 *)(param_1 + 0x78);
  fVar27 = (fVar9 + fVar9) * fVar9;
  fVar28 = (fVar11 + fVar11) * fVar9;
  fVar35 = (fVar11 + fVar11) * fVar11;
  fVar17 = (float)*(undefined8 *)(param_1 + 0xa0) - (float)*(undefined8 *)(param_1 + 0xb0) * fVar24;
  fVar18 = (float)((ulong)*(undefined8 *)(param_1 + 0xa0) >> 0x20) -
           (float)((ulong)*(undefined8 *)(param_1 + 0xb0) >> 0x20) * fVar25;
  fVar19 = (float)*(undefined8 *)(param_1 + 0xa8) - (float)*(undefined8 *)(param_1 + 0xb8) * fVar26;
  fVar39 = fVar28 - fVar16 * fVar12;
  fVar28 = fVar28 + fVar16 * fVar12;
  fVar38 = fVar14 * fVar9 + fVar16 * fVar11;
  fVar23 = fVar14 * fVar9 - fVar16 * fVar11;
  fVar37 = fVar14 * fVar11 - fVar16 * fVar9;
  fVar36 = fVar14 * fVar11 + fVar16 * fVar9;
  auVar21 = NEON_fmov(0x3f800000,4);
  fVar20 = (auVar21._0_4_ - fVar35) - fVar14 * fVar12;
  fVar12 = (auVar21._4_4_ - fVar27) - fVar14 * fVar12;
  fVar35 = (auVar21._8_4_ - fVar27) - fVar35;
  fVar14 = (float)_UNK_027dbb30;
  fVar16 = (float)((ulong)_UNK_027dbb30 >> 0x20);
  fVar9 = (float)_UNK_027dbb38;
  fVar11 = (float)((ulong)_UNK_027dbb38 >> 0x20);
  puVar2 = (undefined8 *)0x0;
  if (lVar3 != 0) {
    puVar2 = (undefined8 *)(lVar3 + 0x10);
  }
  fVar27 = fVar14 * fVar8 + fVar35 * 0.0 + fVar24 * fVar23 + fVar36 * 0.0;
  fVar13 = fVar16 * fVar8 + fVar35 * 0.0 + fVar23 * 0.0 + fVar25 * fVar36;
  fVar15 = fVar9 * fVar8 + fVar26 * fVar35 + fVar23 * 0.0 + fVar36 * 0.0;
  fVar8 = fVar11 * fVar8 + fVar19 * fVar35 + fVar17 * fVar23 + fVar18 * fVar36;
  fVar23 = fVar14 * fVar5 + fVar38 * 0.0 + fVar24 * fVar20 + fVar39 * 0.0;
  fVar36 = fVar16 * fVar5 + fVar38 * 0.0 + fVar20 * 0.0 + fVar25 * fVar39;
  fVar22 = fVar9 * fVar5 + fVar26 * fVar38 + fVar20 * 0.0 + fVar39 * 0.0;
  fVar38 = fVar11 * fVar5 + fVar19 * fVar38 + fVar17 * fVar20 + fVar18 * fVar39;
  fVar5 = fVar14 * fVar7 + fVar37 * 0.0 + fVar24 * fVar28 + fVar12 * 0.0;
  fVar35 = fVar16 * fVar7 + fVar37 * 0.0 + fVar28 * 0.0 + fVar25 * fVar12;
  fVar20 = fVar9 * fVar7 + fVar26 * fVar37 + fVar28 * 0.0 + fVar12 * 0.0;
  fVar7 = fVar11 * fVar7 + fVar19 * fVar37 + fVar17 * fVar28 + fVar18 * fVar12;
  fVar14 = fVar24 * 0.0 + 0.0 + 0.0 + fVar14;
  fVar16 = fVar25 * 0.0 + 0.0 + 0.0 + fVar16;
  uVar6 = CONCAT44(fVar16,fVar14);
  fVar9 = fVar26 * 0.0 + 0.0 + fVar9;
  fVar11 = fVar19 * 0.0 + fVar17 * 0.0 + fVar18 * 0.0 + fVar11;
  uVar10 = CONCAT44(fVar11,fVar9);
  if (lVar3 == 0) {
    *(float *)(param_1 + 0x18) = fVar22;
    *(float *)(param_1 + 0x1c) = fVar38;
    *(float *)(param_1 + 0x10) = fVar23;
    *(float *)(param_1 + 0x14) = fVar36;
    *(ulong *)(param_1 + 0x28) = CONCAT44(fVar7,fVar20);
    *(ulong *)(param_1 + 0x20) = CONCAT44(fVar35,fVar5);
    *(ulong *)(param_1 + 0x38) = CONCAT44(fVar8,fVar15);
    *(ulong *)(param_1 + 0x30) = CONCAT44(fVar13,fVar27);
  }
  else {
    fVar12 = (float)*puVar2;
    fVar17 = (float)((ulong)*puVar2 >> 0x20);
    fVar28 = (float)puVar2[2];
    fVar24 = (float)((ulong)puVar2[2] >> 0x20);
    fVar37 = (float)puVar2[4];
    fVar39 = (float)((ulong)puVar2[4] >> 0x20);
    fVar18 = (float)puVar2[1];
    fVar19 = (float)((ulong)puVar2[1] >> 0x20);
    fVar25 = (float)puVar2[3];
    fVar26 = (float)((ulong)puVar2[3] >> 0x20);
    fVar29 = (float)puVar2[5];
    fVar30 = (float)((ulong)puVar2[5] >> 0x20);
    fVar31 = (float)puVar2[6];
    fVar32 = (float)((ulong)puVar2[6] >> 0x20);
    fVar33 = (float)puVar2[7];
    fVar34 = (float)((ulong)puVar2[7] >> 0x20);
    *(ulong *)(param_1 + 0x18) =
         CONCAT44(fVar11 * fVar19 + fVar8 * fVar18 + fVar38 * fVar12 + fVar7 * fVar17,
                  fVar9 * fVar19 + fVar15 * fVar18 + fVar22 * fVar12 + fVar20 * fVar17);
    *(ulong *)(param_1 + 0x10) =
         CONCAT44(fVar16 * fVar19 + fVar13 * fVar18 + fVar36 * fVar12 + fVar35 * fVar17,
                  fVar14 * fVar19 + fVar27 * fVar18 + fVar23 * fVar12 + fVar5 * fVar17);
    *(float *)(param_1 + 0x28) =
         fVar9 * fVar26 + fVar15 * fVar25 + fVar22 * fVar28 + fVar20 * fVar24;
    *(float *)(param_1 + 0x2c) = fVar11 * fVar26 + fVar8 * fVar25 + fVar38 * fVar28 + fVar7 * fVar24
    ;
    *(float *)(param_1 + 0x20) =
         fVar14 * fVar26 + fVar27 * fVar25 + fVar23 * fVar28 + fVar5 * fVar24;
    *(float *)(param_1 + 0x24) =
         fVar16 * fVar26 + fVar13 * fVar25 + fVar36 * fVar28 + fVar35 * fVar24;
    *(ulong *)(param_1 + 0x38) =
         CONCAT44(fVar11 * fVar30 + fVar8 * fVar29 + fVar38 * fVar37 + fVar7 * fVar39,
                  fVar9 * fVar30 + fVar15 * fVar29 + fVar22 * fVar37 + fVar20 * fVar39);
    *(ulong *)(param_1 + 0x30) =
         CONCAT44(fVar16 * fVar30 + fVar13 * fVar29 + fVar36 * fVar37 + fVar35 * fVar39,
                  fVar14 * fVar30 + fVar27 * fVar29 + fVar23 * fVar37 + fVar5 * fVar39);
    uVar6 = CONCAT44(fVar16 * fVar34 + fVar13 * fVar33 + fVar36 * fVar31 + fVar35 * fVar32,
                     fVar14 * fVar34 + fVar27 * fVar33 + fVar23 * fVar31 + fVar5 * fVar32);
    uVar10 = CONCAT44(fVar11 * fVar34 + fVar8 * fVar33 + fVar38 * fVar31 + fVar7 * fVar32,
                      fVar9 * fVar34 + fVar15 * fVar33 + fVar22 * fVar31 + fVar20 * fVar32);
  }
  *(undefined8 *)(param_1 + 0x48) = uVar10;
  *(undefined8 *)(param_1 + 0x40) = uVar6;
  bVar1 = *(byte *)(param_1 + 0xf8) & 0xfe;
  *(byte *)(param_1 + 0xf8) = bVar1;
  if (lVar4 == 0) {
    *(byte *)(param_1 + 0xf8) = bVar1;
  }
  else {
    *(byte *)(lVar4 + 0x128) = *(byte *)(lVar4 + 0x128) & 0xe2;
  }
  *(byte *)(param_1 + 0xf9) = *(byte *)(param_1 + 0xf9) | 3;
  return;
}

// ==== Aska::HierarchicalObjectContainer::MakeTransformParamEx()
// vaddr 0x2135368 | ghidra 0x2235368 | size 1628 | symbol _ZN4Aska27HierarchicalObjectContainer20MakeTransformParamExEv | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska27HierarchicalObjectContainer20MakeTransformParamExEv(long param_1)

{
  long lVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  bool bVar8;
  byte bVar9;
  float fVar10;
  long *plVar11;
  long lVar12;
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
  float fVar25;
  float fVar26;
  float fVar27;
  float fVar28;
  float fVar29;
  float fVar30;
  undefined1 auStack_180 [4];
  undefined4 uStack_17c;
  undefined4 uStack_178;
  undefined4 uStack_174;
  undefined4 uStack_170;
  undefined4 uStack_168;
  undefined4 uStack_164;
  undefined4 uStack_160;
  undefined4 uStack_15c;
  undefined4 uStack_154;
  undefined4 uStack_150;
  undefined4 uStack_14c;
  undefined4 uStack_148;
  undefined8 uStack_140;
  undefined8 uStack_138;
  undefined8 uStack_130;
  undefined8 uStack_128;
  undefined8 uStack_120;
  undefined8 uStack_118;
  long lStack_110;
  long lStack_108;
  float fStack_100;
  float fStack_fc;
  float fStack_f8;
  undefined4 uStack_f4;
  float fStack_f0;
  float fStack_ec;
  float fStack_e8;
  undefined4 uStack_e4;
  float fStack_e0;
  float fStack_dc;
  float fStack_d8;
  undefined4 uStack_d4;
  undefined8 uStack_d0;
  undefined8 uStack_c8;
  undefined8 uStack_c0;
  undefined8 uStack_b8;
  undefined8 uStack_b0;
  undefined8 uStack_a8;
  long lStack_a0;
  long lStack_98;
  
  lVar12 = *(long *)(param_1 + 0xc0);
  if (lVar12 == 0) {
    uStack_c8 = *(long *)(param_1 + 0x18);
    uStack_d0 = *(long *)(param_1 + 0x10);
    uStack_b8 = *(long *)(param_1 + 0x28);
    uStack_c0 = *(long *)(param_1 + 0x20);
    uStack_a8 = *(long *)(param_1 + 0x38);
    uStack_b0 = *(long *)(param_1 + 0x30);
    fVar19 = (float)((ulong)uStack_d0 >> 0x20);
    fVar20 = (float)uStack_c8;
    lStack_98 = *(long *)(param_1 + 0x48);
    lStack_a0 = *(long *)(param_1 + 0x40);
    fVar21 = (float)((ulong)uStack_c0 >> 0x20);
    fVar22 = (float)uStack_b8;
    fVar15 = (float)uStack_c0;
    fVar16 = (float)((ulong)uStack_b0 >> 0x20);
    fVar17 = (float)uStack_a8;
    fVar10 = (float)uStack_b0;
  }
  else {
    plVar11 = *(long **)(lVar12 + 0xe8);
    if (plVar11 == (long *)0x0) {
      if ((*(byte *)(lVar12 + 0xf8) & 1) != 0) {
        Aska::HierarchicalObjectContainer::MakeMatrix()(lVar12);
      }
      uStack_c8 = *(long *)(lVar12 + 0x18);
      uStack_d0 = *(long *)(lVar12 + 0x10);
      uStack_b8 = *(long *)(lVar12 + 0x28);
      uStack_c0 = *(long *)(lVar12 + 0x20);
      uStack_a8 = *(long *)(lVar12 + 0x38);
      uStack_b0 = *(long *)(lVar12 + 0x30);
      lStack_98 = *(long *)(lVar12 + 0x48);
      lStack_a0 = *(long *)(lVar12 + 0x40);
      Aska::Matrix::InvertLowError()(&uStack_d0);
    }
    else {
      bVar9 = *(byte *)(plVar11 + 0x25);
      if ((bVar9 & 1) != 0) {
        (**(code **)(*plVar11 + 0xa8))(plVar11);
        bVar9 = *(byte *)(plVar11 + 0x25);
      }
      lVar1 = _UNK_027dbb38;
      lVar12 = _UNK_027dbb30;
      if ((bVar9 >> 2 & 1) == 0) {
        if ((*(byte *)((long)plVar11 + 0x129) & 3) == 0) {
          fVar20 = *(float *)((long)plVar11 + 0x4c);
          fVar22 = *(float *)((long)plVar11 + 0x5c);
          fVar15 = *(float *)((long)plVar11 + 0x6c);
          plVar11[0x27] = CONCAT44((int)plVar11[0xe],*(float *)(plVar11 + 0xc));
          plVar11[0x26] = CONCAT44(*(float *)(plVar11 + 10),*(float *)(plVar11 + 8));
          plVar11[0x29] =
               CONCAT44(*(undefined4 *)((long)plVar11 + 0x74),*(float *)((long)plVar11 + 100));
          plVar11[0x28] =
               CONCAT44(*(float *)((long)plVar11 + 0x54),*(float *)((long)plVar11 + 0x44));
          *(float *)((long)plVar11 + 0x13c) =
               -(*(float *)(plVar11 + 8) * fVar20 + *(float *)(plVar11 + 10) * fVar22 +
                *(float *)(plVar11 + 0xc) * fVar15);
          *(float *)((long)plVar11 + 0x14c) =
               -(fVar20 * *(float *)((long)plVar11 + 0x44) +
                 fVar22 * *(float *)((long)plVar11 + 0x54) +
                fVar15 * *(float *)((long)plVar11 + 100));
          plVar11[0x2b] = CONCAT44((int)plVar11[0xf],*(float *)(plVar11 + 0xd));
          plVar11[0x2a] = CONCAT44(*(float *)(plVar11 + 0xb),*(float *)(plVar11 + 9));
          plVar11[0x2d] = lVar1;
          plVar11[0x2c] = lVar12;
          *(float *)((long)plVar11 + 0x15c) =
               -(fVar20 * *(float *)(plVar11 + 9) + fVar22 * *(float *)(plVar11 + 0xb) +
                fVar15 * *(float *)(plVar11 + 0xd));
        }
        else {
          Aska::Matrix::InvertLowError(Aska::Matrix*) const(plVar11 + 8,plVar11 + 0x26);
          bVar9 = *(byte *)(plVar11 + 0x25);
        }
        *(byte *)(plVar11 + 0x25) = bVar9 | 4;
      }
      uStack_c8 = plVar11[0x27];
      uStack_d0 = plVar11[0x26];
      uStack_b8 = plVar11[0x29];
      uStack_c0 = plVar11[0x28];
      uStack_a8 = plVar11[0x2b];
      uStack_b0 = plVar11[0x2a];
      lStack_98 = plVar11[0x2d];
      lStack_a0 = plVar11[0x2c];
    }
    Aska::Matrix::Mul(Aska::Matrix const*)(&uStack_d0,param_1 + 0x10);
    fVar19 = uStack_d0._4_4_;
    fVar21 = uStack_c0._4_4_;
    fVar15 = (float)uStack_c0;
    fVar16 = uStack_b0._4_4_;
    fVar10 = (float)uStack_b0;
    fVar20 = (float)uStack_c8;
    fVar22 = (float)uStack_b8;
    fVar17 = (float)uStack_a8;
  }
  fVar28 = fVar19 * fVar19 + fVar21 * fVar21 + fVar16 * fVar16;
  fVar29 = SQRT((float)uStack_d0 * (float)uStack_d0 + fVar15 * fVar15 + fVar10 * fVar10);
  uStack_f4 = 0x3f800000;
  uStack_e4 = 0x3f800000;
  uStack_d4 = 0x3f800000;
  fStack_100 = (float)uStack_d0;
  fStack_fc = fVar15;
  fStack_f8 = fVar10;
  fStack_f0 = fVar19;
  fStack_ec = fVar21;
  fStack_e8 = fVar16;
  fStack_e0 = fVar20;
  fStack_dc = fVar22;
  fStack_d8 = fVar17;
  if (NAN(fVar29)) {
    fVar29 = (float)sqrtf();
  }
  fVar30 = SQRT(fVar28);
  fVar27 = fVar20 * fVar20 + fVar22 * fVar22 + fVar17 * fVar17;
  if (NAN(fVar30)) {
    fVar30 = (float)sqrtf(fVar28);
  }
  fVar13 = SQRT(fVar27);
  if (NAN(fVar13)) {
    fVar13 = (float)sqrtf(fVar27);
  }
  bVar9 = *(byte *)(param_1 + 0xf9);
  fVar14 = 1.0;
  if (_UNK_027daba4 <= ABS(fVar29 + -1.0)) {
    fVar14 = fVar29;
  }
  fVar29 = 1.0;
  if (_UNK_027daba4 <= ABS(fVar30 + -1.0)) {
    fVar29 = fVar30;
  }
  bVar8 = _UNK_027daba4 <= ABS(fVar13 + -1.0);
  *(undefined4 *)(param_1 + 0x7c) = 0x3f800000;
  fVar30 = 1.0;
  if (bVar8) {
    fVar30 = fVar13;
  }
  *(float *)(param_1 + 0x70) = fVar14;
  *(float *)(param_1 + 0x74) = fVar29;
  *(float *)(param_1 + 0x78) = fVar30;
  *(byte *)(param_1 + 0xf9) = bVar9 | 3;
  if ((bVar9 >> 2 & 1) != 0) {
    fVar13 = *(float *)(param_1 + 0xa0) - *(float *)(param_1 + 0xb0) * fVar14;
    fVar18 = *(float *)(param_1 + 0xa4) - *(float *)(param_1 + 0xb4) * fVar29;
    fVar23 = *(float *)(param_1 + 0xa8) - *(float *)(param_1 + 0xb8) * fVar30;
    fVar24 = fVar18 * 0.0;
    fVar25 = fVar13 * 0.0;
    fVar26 = fVar23 * 0.0;
    uStack_138 = (ulong)(uint)-(fVar13 + fVar24 + fVar26) << 0x20;
    uStack_128 = (ulong)(uint)-(fVar25 + fVar18 + fVar26) << 0x20;
    uStack_118 = CONCAT44(-(fVar25 + fVar24 + fVar23),0x3f800000);
    uStack_140 = 0x3f800000;
    uStack_130 = 0x3f80000000000000;
    uStack_120 = 0;
    lStack_108 = _UNK_027dbb38;
    lStack_110 = _UNK_027dbb30;
    Aska::Matrix::Mul(Aska::Matrix const*)(&uStack_d0,&uStack_140);
  }
  fVar13 = fStack_100;
  if (fVar14 != 1.0) {
    fVar18 = fStack_100 * fStack_100 + fVar15 * fVar15 + fVar10 * fVar10;
    fVar14 = SQRT(fVar18);
    if (NAN(fVar14)) {
      fVar14 = (float)sqrtf(fVar18);
    }
    if (_UNK_027e519c <= fVar14) {
      fVar14 = 1.0 / fVar14;
      fStack_100 = fVar14 * fVar13;
      fStack_fc = fVar14 * fVar15;
      fStack_f8 = fVar14 * fVar10;
    }
  }
  if (fVar29 != 1.0) {
    fVar15 = SQRT(fVar28);
    if (NAN(fVar15)) {
      fVar15 = (float)sqrtf(fVar28);
    }
    if (_UNK_027e519c <= fVar15) {
      fVar15 = 1.0 / fVar15;
      fVar19 = fVar15 * fVar19;
      fVar21 = fVar15 * fVar21;
      fVar16 = fVar15 * fVar16;
      fStack_f0 = fVar19;
      fStack_ec = fVar21;
      fStack_e8 = fVar16;
    }
  }
  if (fVar30 != 1.0) {
    fVar15 = SQRT(fVar27);
    if (NAN(fVar15)) {
      fVar15 = (float)sqrtf(fVar27);
    }
    if (_UNK_027e519c <= fVar15) {
      fVar15 = 1.0 / fVar15;
      fVar20 = fVar15 * fVar20;
      fVar22 = fVar15 * fVar22;
      fVar17 = fVar15 * fVar17;
      fStack_e0 = fVar20;
      fStack_dc = fVar22;
      fStack_d8 = fVar17;
    }
  }
  lStack_108 = _UNK_027dbb38;
  lStack_110 = _UNK_027dbb30;
  uStack_140 = CONCAT44(fVar19,fStack_100);
  uStack_130 = CONCAT44(fVar21,fStack_fc);
  uStack_120 = CONCAT44(fVar16,fStack_f8);
  uStack_138 = CONCAT44((int)((ulong)_UNK_027dbb08 >> 0x20),fVar20);
  uStack_128 = CONCAT44((int)((ulong)_UNK_027dbb18 >> 0x20),fVar22);
  uStack_118 = CONCAT44((int)((ulong)_UNK_027dbb28 >> 0x20),fVar17);
  if ((((*(float *)(param_1 + 0x90) != 0.0) || (*(float *)(param_1 + 0x94) != 0.0)) ||
      (*(float *)(param_1 + 0x98) != 0.0)) || (*(float *)(param_1 + 0x9c) != 1.0)) {
    Aska::Matrix::Create(Aska::Quaternion const*)(auStack_180);
    uVar7 = uStack_154;
    uVar6 = uStack_164;
    uVar5 = uStack_168;
    uVar4 = uStack_174;
    uVar3 = uStack_178;
    uVar2 = uStack_17c;
    uStack_17c = uStack_170;
    uStack_170 = uVar2;
    uStack_178 = uStack_160;
    uStack_160 = uVar3;
    uStack_174 = uStack_150;
    uStack_150 = uVar4;
    uStack_168 = uStack_15c;
    uStack_15c = uVar5;
    uStack_164 = uStack_14c;
    uStack_14c = uVar6;
    uStack_154 = uStack_148;
    uStack_148 = uVar7;
    Aska::Matrix::MulFromLeft(Aska::Matrix const*)(&uStack_140,auStack_180);
  }
  Aska::Quaternion::Create(Aska::Matrix const*)(param_1 + 0x60,&uStack_140);
  *(undefined4 *)(param_1 + 0x5c) = 0x3f800000;
  *(float *)(param_1 + 0x50) = uStack_c8._4_4_ - *(float *)(param_1 + 0x80);
  *(float *)(param_1 + 0x54) = uStack_b8._4_4_ - *(float *)(param_1 + 0x84);
  *(float *)(param_1 + 0x58) = uStack_a8._4_4_ - *(float *)(param_1 + 0x88);
  *(byte *)(param_1 + 0xf8) = *(byte *)(param_1 + 0xf8) & 0xfe;
  return;
}

// ==== Aska::HierarchicalObjectContainer::SwapParent(Aska::HierarchicalObjectContainer*)
// vaddr 0x21359c4 | ghidra 0x22359c4 | size 152 | symbol _ZN4Aska27HierarchicalObjectContainer10SwapParentEPS0_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska27HierarchicalObjectContainer10SwapParentEPS0_(long param_1,long param_2)

{
  byte bVar1;
  long lVar2;
  undefined8 uVar3;
  long lVar4;
  
  lVar2 = *(long *)(param_1 + 0xc0);
  if (lVar2 != 0) {
    if (*(long *)(lVar2 + 200) == param_1) {
      lVar4 = 0;
      if (*(long *)(param_1 + 0xd8) != param_1) {
        lVar4 = *(long *)(param_1 + 0xd8);
      }
      *(long *)(lVar2 + 200) = lVar4;
    }
    if (*(long *)(param_1 + 0xd8) != param_1) {
      *(undefined8 *)(*(long *)(param_1 + 0xd8) + 0xd0) = *(undefined8 *)(param_1 + 0xd0);
      *(undefined8 *)(*(long *)(param_1 + 0xd0) + 0xd8) = *(undefined8 *)(param_1 + 0xd8);
    }
    *(undefined8 *)(param_1 + 0xc0) = 0;
  }
  if (param_2 == 0) {
    bVar1 = *(byte *)(param_1 + 0xf8);
  }
  else {
    lVar2 = *(long *)(param_2 + 200);
    if (lVar2 == 0) {
      *(long *)(param_2 + 200) = param_1;
      *(long *)(param_1 + 0xc0) = param_2;
      lVar2 = param_1;
      lVar4 = param_1;
    }
    else {
      uVar3 = *(undefined8 *)(lVar2 + 0xd0);
      *(long *)(param_1 + 0xc0) = param_2;
      *(undefined8 *)(param_1 + 0xd0) = uVar3;
      *(long *)(param_1 + 0xd8) = lVar2;
      lVar4 = *(long *)(lVar2 + 0xd0);
    }
    *(long *)(lVar4 + 0xd8) = param_1;
    *(long *)(lVar2 + 0xd0) = param_1;
    bVar1 = *(byte *)(param_1 + 0xf8);
  }
  if ((bVar1 & 1) == 0) {
    (*(code *)
      PTR__Z41Function_UpdateHierarchicallyByUsingStackILi256ELb0EEvPN4Aska27HierarchicalObjectContainerE_02c9d0a8
    )();
    return;
  }
  return;
}

// ==== Aska::HierarchicalObjectContainer::ReleaseHOCBuffer()
// vaddr 0x2135a5c | ghidra 0x2235a5c | size 36 | symbol _ZN4Aska27HierarchicalObjectContainer16ReleaseHOCBufferEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska27HierarchicalObjectContainer16ReleaseHOCBufferEv(void)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZN4Aska27HierarchicalObjectContainer10m_pHOCListE_02cc35e8;
  if (*(long *)PTR__ZN4Aska27HierarchicalObjectContainer10m_pHOCListE_02cc35e8 != 0) {
    operator delete[](void*)();
  }
  *(undefined8 *)puVar1 = 0;
  return;
}

// ==== Aska::HierarchicalObjectContainer::OpenIterator()
// vaddr 0x2135a80 | ghidra 0x2235a80 | size 84 | symbol _ZN4Aska27HierarchicalObjectContainer12OpenIteratorEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska27HierarchicalObjectContainer12OpenIteratorEv(void)

{
  undefined *puVar1;
  long lVar2;
  
  puVar1 = PTR__ZN4Aska27HierarchicalObjectContainer10m_pHOCListE_02cc35e8;
  lVar2 = *(long *)PTR__ZN4Aska27HierarchicalObjectContainer10m_pHOCListE_02cc35e8;
  *(undefined4 *)PTR__ZN4Aska27HierarchicalObjectContainer17m_nCurrentHOCListE_02cb7d58 = 0;
  if (lVar2 == 0) {
    lVar2 = operator new[](unsigned long, std::nothrow_t const&)(0x2000,PTR__ZSt7nothrow_02cb9a80);
    *(long *)puVar1 = lVar2;
    if (lVar2 == 0) {
      return 0;
    }
    *(undefined4 *)PTR__ZN4Aska27HierarchicalObjectContainer13m_nNumHOCListE_02cc34c8 = 0x400;
  }
  return 1;
}

// ==== Aska::HierarchicalObjectContainer::AddToIterator()
// vaddr 0x2135ad4 | ghidra 0x2235ad4 | size 340 | symbol _ZN4Aska27HierarchicalObjectContainer13AddToIteratorEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska27HierarchicalObjectContainer13AddToIteratorEv(long param_1)

{
  undefined1 auVar1 [16];
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  long lVar5;
  ulong uVar6;
  undefined8 uVar7;
  long *plVar8;
  long lVar9;
  long lVar10;
  int iVar11;
  
  puVar4 = PTR__ZN4Aska27HierarchicalObjectContainer10m_pHOCListE_02cc35e8;
  if (*(long *)PTR__ZN4Aska27HierarchicalObjectContainer10m_pHOCListE_02cc35e8 == 0) {
code_r0x02235c04:
    Aska::HierarchicalObjectContainer::MakeMatrix()(param_1);
    uVar7 = 0;
  }
  else {
    if ((*(byte *)(param_1 + 0xf8) >> 5 & 1) == 0) {
      lVar5 = *(long *)(param_1 + 0xc0);
      if ((lVar5 != 0) && ((*(byte *)(lVar5 + 0xf8) & 1) != 0)) {
        plVar8 = *(long **)(lVar5 + 0xe8);
        if (plVar8 == (long *)0x0) {
          _ZN4Aska27HierarchicalObjectContainer13AddToIteratorEv();
        }
        else {
          if (*(char *)((long)plVar8 + 0x197) == '\0') {
            uVar6 = _ZN4Aska27HierarchicalObjectContainer13AddToIteratorEv(plVar8 + 6);
            if ((uVar6 & 1) != 0) goto code_r0x02235b60;
          }
          else {
            (**(code **)(*plVar8 + 0xa8))(plVar8);
          }
          lVar5 = (**(code **)(*plVar8 + 0x98))(plVar8);
          plVar8[0x24] = lVar5;
        }
      }
code_r0x02235b60:
      puVar3 = PTR__ZN4Aska27HierarchicalObjectContainer13m_nNumHOCListE_02cc34c8;
      puVar2 = PTR__ZN4Aska27HierarchicalObjectContainer17m_nCurrentHOCListE_02cb7d58;
      iVar11 = *(int *)PTR__ZN4Aska27HierarchicalObjectContainer17m_nCurrentHOCListE_02cb7d58;
      lVar5 = (long)*(int *)PTR__ZN4Aska27HierarchicalObjectContainer13m_nNumHOCListE_02cc34c8;
      if (iVar11 < *(int *)PTR__ZN4Aska27HierarchicalObjectContainer13m_nNumHOCListE_02cc34c8 + -1)
      {
        lVar9 = *(long *)puVar4;
      }
      else {
        auVar1._8_8_ = 0;
        auVar1._0_8_ = lVar5 << 1;
        lVar9 = lVar5 << 4;
        if (SUB168(auVar1 * ZEXT816(8),8) != 0) {
          lVar9 = -1;
        }
        lVar9 = operator new[](unsigned long, std::nothrow_t const&)(lVar9,PTR__ZSt7nothrow_02cb9a80);
        if (lVar9 == 0) goto code_r0x02235c04;
        lVar10 = *(long *)puVar4;
        memcpy(lVar9,lVar10,lVar5 << 3);
        *(int *)puVar3 = (int)(lVar5 << 1);
        if (lVar10 != 0) {
          operator delete[](void*)(lVar10);
          iVar11 = *(int *)puVar2;
        }
        *(long *)puVar4 = lVar9;
      }
      *(int *)puVar2 = iVar11 + 1;
      *(long *)(lVar9 + (long)iVar11 * 8) = param_1;
      *(byte *)(param_1 + 0xf8) = *(byte *)(param_1 + 0xf8) | 0x20;
    }
    uVar7 = 1;
  }
  return uVar7;
}

// ==== Aska::HierarchicalObjectContainer::IterateMakeMatrix()
// vaddr 0x2135c28 | ghidra 0x2235c28 | size 880 | symbol _ZN4Aska27HierarchicalObjectContainer17IterateMakeMatrixEv | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska27HierarchicalObjectContainer17IterateMakeMatrixEv(void)

{
  byte bVar1;
  uint uVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  undefined8 uVar10;
  undefined8 uVar11;
  undefined8 uVar12;
  undefined8 uVar13;
  undefined8 uVar14;
  undefined8 uVar15;
  undefined *puVar16;
  long lVar17;
  long *plVar18;
  long lVar19;
  ulong uVar20;
  long lVar21;
  float fVar22;
  undefined1 auVar23 [16];
  undefined1 auVar24 [16];
  float fVar25;
  float fVar26;
  float fVar27;
  undefined1 auVar29 [16];
  undefined1 auVar30 [16];
  undefined1 auVar31 [16];
  float fVar32;
  undefined1 auVar33 [16];
  undefined1 auVar34 [16];
  float fVar35;
  float fVar36;
  float fVar37;
  float fVar38;
  float fVar40;
  undefined1 auVar39 [16];
  float fVar41;
  float fVar42;
  float fVar43;
  float fVar44;
  float fVar45;
  float fVar46;
  float fVar47;
  float fVar48;
  float fVar49;
  float fVar50;
  float fVar51;
  float fVar53;
  undefined1 auVar52 [16];
  undefined8 uVar54;
  undefined1 auVar55 [16];
  undefined1 auVar56 [16];
  undefined1 auVar57 [16];
  undefined8 uVar58;
  float fVar59;
  float fStack_80;
  float fStack_7c;
  float fStack_78;
  float fStack_74;
  float fStack_70;
  float fStack_6c;
  float fStack_68;
  float fStack_64;
  float fStack_60;
  float fStack_5c;
  float fStack_58;
  float fStack_50;
  float fStack_4c;
  float fStack_48;
  float fStack_44;
  undefined8 uVar28;
  
  puVar16 = PTR__ZN4Aska27HierarchicalObjectContainer10m_pHOCListE_02cc35e8;
  uVar2 = *(uint *)PTR__ZN4Aska27HierarchicalObjectContainer17m_nCurrentHOCListE_02cb7d58;
  if (uVar2 != 0) {
    lVar17 = *(long *)PTR__ZN4Aska27HierarchicalObjectContainer10m_pHOCListE_02cc35e8;
    if (lVar17 != 0) {
      *(undefined8 *)(lVar17 + (long)(int)uVar2 * 8) =
           *(undefined8 *)(lVar17 + (long)(int)(uVar2 - 1) * 8);
      uVar15 = _UNK_029c4a18;
      uVar14 = _UNK_029c4a10;
      uVar13 = _UNK_029c4a08;
      uVar12 = _UNK_029c4a00;
      uVar11 = _UNK_029c49f8;
      uVar10 = _UNK_029c49f0;
      uVar9 = _UNK_02961088;
      uVar8 = _UNK_02961080;
      uVar7 = _UNK_027dbb38;
      uVar6 = _UNK_027dbb30;
      if (0 < (int)uVar2) {
        auVar23 = NEON_fmov(0x3f800000,4);
        plVar18 = *(long **)puVar16;
        uVar20 = 1;
        lVar17 = *plVar18;
        while( true ) {
          lVar21 = plVar18[uVar20];
          lVar19 = *(long *)(lVar17 + 0xc0);
          plVar18 = *(long **)(lVar17 + 0xe8);
          Hint_Prefetch(lVar21 + 0x50,0,2,0);
          fVar22 = *(float *)(lVar17 + 0x60);
          fVar32 = *(float *)(lVar17 + 100);
          fVar40 = *(float *)(lVar17 + 0x68);
          fVar46 = *(float *)(lVar17 + 0x6c);
          fStack_50 = (float)uVar10;
          fStack_4c = (float)((ulong)uVar10 >> 0x20);
          fStack_48 = (float)uVar11;
          fStack_44 = (float)((ulong)uVar11 >> 0x20);
          fStack_80 = (float)uVar12;
          fStack_7c = (float)((ulong)uVar12 >> 0x20);
          fStack_78 = (float)uVar13;
          fStack_74 = (float)((ulong)uVar13 >> 0x20);
          fStack_70 = (float)uVar8;
          fStack_6c = (float)((ulong)uVar8 >> 0x20);
          fStack_68 = (float)uVar9;
          fStack_64 = (float)((ulong)uVar9 >> 0x20);
          fVar3 = *(float *)(lVar17 + 0x70);
          fVar4 = *(float *)(lVar17 + 0x74);
          fVar5 = *(float *)(lVar17 + 0x78);
          auVar30 = *(undefined1 (*) [16])(lVar17 + 0x90);
          auVar55._0_4_ = fVar22 * fStack_50;
          auVar55._4_4_ = fVar32 * fStack_4c;
          auVar55._8_4_ = fVar40 * fStack_48;
          auVar55._12_4_ = fVar46 * fStack_44;
          auVar57._0_4_ = fVar22 * fStack_70;
          auVar57._4_4_ = fVar32 * fStack_6c;
          auVar57._8_4_ = fVar40 * fStack_68;
          auVar57._12_4_ = fVar46 * fStack_64;
          fVar35 = (float)*(undefined8 *)(lVar17 + 0x50) + *(float *)(lVar17 + 0x80);
          fVar36 = (float)((ulong)*(undefined8 *)(lVar17 + 0x50) >> 0x20) +
                   *(float *)(lVar17 + 0x84);
          fVar37 = (float)*(undefined8 *)(lVar17 + 0x58) + *(float *)(lVar17 + 0x88);
          auVar33 = NEON_ext(auVar30,auVar30,0xc,1);
          auVar56._0_4_ = fVar22 * fStack_80;
          auVar56._4_4_ = fVar32 * fStack_7c;
          auVar56._8_4_ = fVar40 * fStack_78;
          auVar56._12_4_ = fVar46 * fStack_74;
          auVar29 = NEON_rev64(auVar55,4);
          auVar52 = NEON_ext(auVar57,auVar57,4,1);
          auVar55 = NEON_rev64(auVar56,4);
          auVar39._0_4_ = auVar30._0_4_ * fVar22 * (float)uVar14;
          auVar39._4_4_ = auVar30._4_4_ * fVar32 * (float)((ulong)uVar14 >> 0x20);
          auVar39._8_4_ = auVar30._8_4_ * fVar40 * (float)uVar15;
          auVar39._12_4_ = auVar30._12_4_ * fVar46 * (float)((ulong)uVar15 >> 0x20);
          fVar41 = *(float *)(lVar17 + 0xa0) - (float)*(undefined8 *)(lVar17 + 0xb0) * fVar3;
          fVar43 = *(float *)(lVar17 + 0xa4) -
                   (float)((ulong)*(undefined8 *)(lVar17 + 0xb0) >> 0x20) * fVar4;
          fVar44 = *(float *)(lVar17 + 0xa8) - (float)*(undefined8 *)(lVar17 + 0xb8) * fVar5;
          auVar30 = NEON_ext(auVar29,auVar29,4,1);
          fVar22 = auVar33._0_4_;
          fVar47 = fVar22 * auVar52._0_4_;
          fVar32 = auVar33._4_4_;
          fVar49 = fVar32 * auVar52._4_4_;
          fVar40 = auVar33._8_4_;
          fVar50 = fVar40 * auVar52._8_4_;
          fVar46 = auVar33._12_4_;
          fVar51 = fVar46 * auVar52._12_4_;
          auVar55 = NEON_ext(auVar55,auVar55,0xc,1);
          auVar39 = NEON_ext(auVar39,auVar39,0xc,1);
          auVar33._0_4_ = fVar22 * auVar30._0_4_;
          auVar33._4_4_ = fVar32 * auVar30._4_4_;
          auVar33._8_4_ = fVar40 * auVar30._8_4_;
          auVar33._12_4_ = fVar46 * auVar30._12_4_;
          auVar30._4_4_ = fVar49;
          auVar30._0_4_ = fVar47;
          auVar30._8_4_ = fVar50;
          auVar30._12_4_ = fVar51;
          auVar29._4_4_ = fVar49;
          auVar29._0_4_ = fVar47;
          auVar29._8_4_ = fVar50;
          auVar29._12_4_ = fVar51;
          auVar57 = NEON_ext(auVar30,auVar29,8,1);
          auVar52._0_4_ = fVar22 * auVar55._0_4_;
          auVar52._4_4_ = fVar32 * auVar55._4_4_;
          auVar52._8_4_ = fVar40 * auVar55._8_4_;
          auVar52._12_4_ = fVar46 * auVar55._12_4_;
          auVar29 = NEON_ext(auVar39,auVar39,8,1);
          auVar30 = NEON_ext(auVar33,auVar33,8,1);
          auVar55 = NEON_ext(auVar52,auVar52,8,1);
          fVar22 = auVar39._0_4_ + auVar39._4_4_;
          auVar31._0_8_ = NEON_rev64(CONCAT44(auVar57._0_4_ + auVar57._4_4_,fVar47 + fVar49),4);
          uVar54 = NEON_rev64(CONCAT44(auVar30._0_4_ + auVar30._4_4_,auVar33._0_4_ + auVar33._4_4_),
                              4);
          fVar48 = fVar47 + fVar49 + (float)auVar31._0_8_;
          auVar31._0_8_ = NEON_rev64(CONCAT44(auVar29._0_4_ + auVar29._4_4_,fVar22),4);
          uVar58 = NEON_rev64(CONCAT44(auVar55._0_4_ + auVar55._4_4_,auVar52._0_4_ + auVar52._4_4_),
                              4);
          fVar47 = auVar33._0_4_ + auVar33._4_4_ + (float)uVar54;
          fVar22 = fVar22 + (float)auVar31._0_8_;
          fVar32 = auVar52._0_4_ + auVar52._4_4_ + (float)uVar58;
          fVar40 = fVar32 + fVar32;
          fVar22 = fVar22 + fVar22;
          fVar49 = (fVar47 + fVar47) * fVar47;
          fVar50 = (fVar48 + fVar48) * fVar47;
          fVar46 = (fVar48 + fVar48) * fVar48;
          fVar59 = fVar40 * fVar47 + fVar22 * fVar48;
          fVar51 = fVar40 * fVar47 - fVar22 * fVar48;
          fVar53 = fVar40 * fVar48 - fVar22 * fVar47;
          fVar47 = fVar40 * fVar48 + fVar22 * fVar47;
          fStack_60 = auVar23._0_4_;
          fStack_5c = auVar23._4_4_;
          fStack_58 = auVar23._8_4_;
          fVar48 = fVar50 - fVar22 * fVar32;
          fVar50 = fVar50 + fVar22 * fVar32;
          fVar22 = (fStack_60 - fVar46) - fVar40 * fVar32;
          fVar32 = (fStack_5c - fVar49) - fVar40 * fVar32;
          fVar46 = (fStack_58 - fVar49) - fVar46;
          bVar1 = *(byte *)(lVar17 + 0xf8) & 0xde;
          fVar40 = (float)uVar6;
          fVar49 = (float)((ulong)uVar6 >> 0x20);
          fVar38 = (float)uVar7;
          fVar42 = (float)((ulong)uVar7 >> 0x20);
          *(byte *)(lVar17 + 0xf8) = bVar1;
          if (plVar18 == (long *)0x0) {
            *(byte *)(lVar17 + 0xf8) = bVar1;
          }
          else {
            *(byte *)(plVar18 + 0x25) = *(byte *)(plVar18 + 0x25) & 0xe2;
          }
          fVar25 = fVar40 * fVar35 + fVar59 * 0.0 + fVar48 * 0.0 + fVar3 * fVar22;
          fVar26 = fVar49 * fVar35 + fVar59 * 0.0 + fVar4 * fVar48 + fVar22 * 0.0;
          uVar58 = CONCAT44(fVar26,fVar25);
          fVar27 = fVar38 * fVar35 + fVar5 * fVar59 + fVar48 * 0.0 + fVar22 * 0.0;
          fVar48 = fVar42 * fVar35 + fVar44 * fVar59 + fVar43 * fVar48 + fVar41 * fVar22;
          uVar28 = CONCAT44(fVar48,fVar27);
          auVar34._0_4_ = fVar40 * fVar36 + fVar53 * 0.0 + fVar3 * fVar50 + fVar32 * 0.0;
          auVar34._4_4_ = fVar49 * fVar36 + fVar53 * 0.0 + fVar50 * 0.0 + fVar4 * fVar32;
          auVar34._8_4_ = fVar38 * fVar36 + fVar5 * fVar53 + fVar50 * 0.0 + fVar32 * 0.0;
          auVar34._12_4_ = fVar42 * fVar36 + fVar44 * fVar53 + fVar41 * fVar50 + fVar43 * fVar32;
          fVar22 = fVar40 * fVar37 + fVar3 * fVar51 + fVar47 * 0.0 + fVar46 * 0.0;
          fVar32 = fVar49 * fVar37 + fVar51 * 0.0 + fVar4 * fVar47 + fVar46 * 0.0;
          auVar31._0_8_ = CONCAT44(fVar32,fVar22);
          fVar35 = fVar38 * fVar37 + fVar51 * 0.0 + fVar47 * 0.0 + fVar5 * fVar46;
          fVar46 = fVar42 * fVar37 + fVar41 * fVar51 + fVar43 * fVar47 + fVar44 * fVar46;
          uVar54 = CONCAT44(fVar46,fVar35);
          auVar24._0_4_ = fVar3 * 0.0 + 0.0 + 0.0 + fVar40;
          auVar24._4_4_ = fVar4 * 0.0 + 0.0 + 0.0 + fVar49;
          auVar24._8_4_ = fVar5 * 0.0 + 0.0 + fVar38;
          auVar24._12_4_ = fVar44 * 0.0 + fVar41 * 0.0 + fVar43 * 0.0 + fVar42;
          *(byte *)(lVar17 + 0xf9) = *(byte *)(lVar17 + 0xf9) | 3;
          if (lVar19 != 0) {
            fVar40 = *(float *)(lVar19 + 0x10);
            fVar3 = *(float *)(lVar19 + 0x14);
            fVar4 = *(float *)(lVar19 + 0x18);
            fVar5 = *(float *)(lVar19 + 0x1c);
            fVar36 = *(float *)(lVar19 + 0x30);
            fVar37 = *(float *)(lVar19 + 0x34);
            fVar41 = *(float *)(lVar19 + 0x38);
            fVar47 = *(float *)(lVar19 + 0x3c);
            auVar30 = *(undefined1 (*) [16])(lVar19 + 0x40);
            fVar51 = (float)*(undefined8 *)(lVar19 + 0x20);
            fVar53 = (float)((ulong)*(undefined8 *)(lVar19 + 0x20) >> 0x20);
            fVar42 = auVar30._0_4_;
            fVar44 = auVar30._4_4_;
            fVar49 = auVar34._0_4_ * fVar44;
            fVar43 = auVar34._4_4_ * fVar44;
            fVar50 = auVar34._8_4_ * fVar44;
            fVar44 = auVar34._12_4_ * fVar44;
            fVar59 = (float)*(undefined8 *)(lVar19 + 0x28);
            fVar45 = auVar30._8_4_;
            fVar38 = (float)((ulong)*(undefined8 *)(lVar19 + 0x28) >> 0x20);
            uVar58 = CONCAT44(auVar24._4_4_ * fVar5 +
                              fVar32 * fVar4 + fVar26 * fVar40 + auVar34._4_4_ * fVar3,
                              auVar24._0_4_ * fVar5 +
                              fVar22 * fVar4 + fVar25 * fVar40 + auVar34._0_4_ * fVar3);
            uVar28 = CONCAT44(auVar24._12_4_ * fVar5 +
                              fVar46 * fVar4 + fVar48 * fVar40 + auVar34._12_4_ * fVar3,
                              auVar24._8_4_ * fVar5 +
                              fVar35 * fVar4 + fVar27 * fVar40 + auVar34._8_4_ * fVar3);
            auVar31._0_8_ =
                 CONCAT44(auVar24._4_4_ * fVar47 +
                          fVar32 * fVar41 + fVar26 * fVar36 + auVar34._4_4_ * fVar37,
                          auVar24._0_4_ * fVar47 +
                          fVar22 * fVar41 + fVar25 * fVar36 + auVar34._0_4_ * fVar37);
            auVar31._8_4_ =
                 auVar24._8_4_ * fVar47 + fVar35 * fVar41 + fVar27 * fVar36 + auVar34._8_4_ * fVar37
            ;
            auVar31._12_4_ =
                 auVar24._12_4_ * fVar47 +
                 fVar46 * fVar41 + fVar48 * fVar36 + auVar34._12_4_ * fVar37;
            fVar40 = auVar30._12_4_;
            auVar34._0_4_ =
                 auVar24._0_4_ * fVar38 + fVar22 * fVar59 + fVar25 * fVar51 + auVar34._0_4_ * fVar53
            ;
            auVar34._4_4_ =
                 auVar24._4_4_ * fVar38 + fVar32 * fVar59 + fVar26 * fVar51 + auVar34._4_4_ * fVar53
            ;
            auVar34._8_4_ =
                 auVar24._8_4_ * fVar38 + fVar35 * fVar59 + fVar27 * fVar51 + auVar34._8_4_ * fVar53
            ;
            auVar34._12_4_ =
                 auVar24._12_4_ * fVar38 +
                 fVar46 * fVar59 + fVar48 * fVar51 + auVar34._12_4_ * fVar53;
            auVar24._0_4_ = auVar24._0_4_ * fVar40 + fVar22 * fVar45 + fVar25 * fVar42 + fVar49;
            auVar24._4_4_ = auVar24._4_4_ * fVar40 + fVar32 * fVar45 + fVar26 * fVar42 + fVar43;
            auVar24._8_4_ = auVar24._8_4_ * fVar40 + fVar35 * fVar45 + fVar27 * fVar42 + fVar50;
            auVar24._12_4_ = auVar24._12_4_ * fVar40 + fVar46 * fVar45 + fVar48 * fVar42 + fVar44;
            uVar54 = auVar31._8_8_;
          }
          *(undefined8 *)(lVar17 + 0x18) = uVar28;
          *(undefined8 *)(lVar17 + 0x10) = uVar58;
          *(long *)(lVar17 + 0x28) = auVar34._8_8_;
          *(long *)(lVar17 + 0x20) = auVar34._0_8_;
          *(undefined8 *)(lVar17 + 0x38) = uVar54;
          *(undefined8 *)(lVar17 + 0x30) = auVar31._0_8_;
          *(long *)(lVar17 + 0x48) = auVar24._8_8_;
          *(long *)(lVar17 + 0x40) = auVar24._0_8_;
          lVar17 = (**(code **)(*plVar18 + 0x98))(plVar18);
          plVar18[0x24] = lVar17;
          if (uVar2 == uVar20) break;
          plVar18 = *(long **)puVar16;
          uVar20 = uVar20 + 1;
          lVar17 = lVar21;
        }
      }
    }
  }
  return;
}

// ==== Aska::HierarchicalObjectContainer::CallCalcTransformMatrix(Aska::HierarchicalObject*)
// vaddr 0x2135f98 | ghidra 0x2235f98 | size 524 | symbol _ZN4Aska27HierarchicalObjectContainer23CallCalcTransformMatrixEPNS_18HierarchicalObjectE | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska27HierarchicalObjectContainer23CallCalcTransformMatrixEPNS_18HierarchicalObjectE
               (long param_1,long param_2)

{
  undefined8 *puVar1;
  long lVar2;
  long lVar3;
  float fVar4;
  float fVar6;
  undefined8 uVar5;
  float fVar7;
  float fVar8;
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
  float fVar21;
  undefined1 auVar20 [16];
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
  float fVar38;
  undefined8 uVar9;
  
  lVar3 = 0;
  if (*(long *)(param_2 + 0xf0) != 0) {
    lVar2 = *(long *)(*(long *)(param_2 + 0xf0) + 0xe8);
    lVar3 = 0;
    if (lVar2 != 0) {
      lVar3 = lVar2 + 0x30;
    }
  }
  Hint_Prefetch(param_1 + 0x10,0,2,0);
  fVar4 = (float)*(undefined8 *)(param_1 + 0x50) + (float)*(undefined8 *)(param_1 + 0x80);
  fVar6 = (float)((ulong)*(undefined8 *)(param_1 + 0x50) >> 0x20) +
          (float)((ulong)*(undefined8 *)(param_1 + 0x80) >> 0x20);
  fVar7 = (float)*(undefined8 *)(param_1 + 0x58) + (float)*(undefined8 *)(param_1 + 0x88);
  fVar8 = (float)*(undefined8 *)(param_1 + 0x60);
  fVar10 = (float)((ulong)*(undefined8 *)(param_1 + 0x60) >> 0x20);
  fVar11 = (float)*(undefined8 *)(param_1 + 0x68);
  fVar13 = fVar11 + fVar11;
  fVar15 = (float)((ulong)*(undefined8 *)(param_1 + 0x68) >> 0x20);
  fVar15 = fVar15 + fVar15;
  fVar23 = (float)*(undefined8 *)(param_1 + 0x70);
  fVar24 = (float)((ulong)*(undefined8 *)(param_1 + 0x70) >> 0x20);
  fVar25 = (float)*(undefined8 *)(param_1 + 0x78);
  fVar26 = (fVar8 + fVar8) * fVar8;
  fVar27 = (fVar10 + fVar10) * fVar8;
  fVar34 = (fVar10 + fVar10) * fVar10;
  fVar16 = (float)*(undefined8 *)(param_1 + 0xa0) - (float)*(undefined8 *)(param_1 + 0xb0) * fVar23;
  fVar17 = (float)((ulong)*(undefined8 *)(param_1 + 0xa0) >> 0x20) -
           (float)((ulong)*(undefined8 *)(param_1 + 0xb0) >> 0x20) * fVar24;
  fVar18 = (float)*(undefined8 *)(param_1 + 0xa8) - (float)*(undefined8 *)(param_1 + 0xb8) * fVar25;
  fVar38 = fVar27 - fVar15 * fVar11;
  fVar27 = fVar27 + fVar15 * fVar11;
  fVar37 = fVar13 * fVar8 + fVar15 * fVar10;
  fVar22 = fVar13 * fVar8 - fVar15 * fVar10;
  fVar36 = fVar13 * fVar10 - fVar15 * fVar8;
  fVar35 = fVar13 * fVar10 + fVar15 * fVar8;
  auVar20 = NEON_fmov(0x3f800000,4);
  fVar19 = (auVar20._0_4_ - fVar34) - fVar13 * fVar11;
  fVar11 = (auVar20._4_4_ - fVar26) - fVar13 * fVar11;
  fVar34 = (auVar20._8_4_ - fVar26) - fVar34;
  fVar13 = (float)_UNK_027dbb30;
  fVar15 = (float)((ulong)_UNK_027dbb30 >> 0x20);
  fVar8 = (float)_UNK_027dbb38;
  fVar10 = (float)((ulong)_UNK_027dbb38 >> 0x20);
  puVar1 = (undefined8 *)0x0;
  if (lVar3 != 0) {
    puVar1 = (undefined8 *)(lVar3 + 0x10);
  }
  fVar26 = fVar13 * fVar7 + fVar34 * 0.0 + fVar23 * fVar22 + fVar35 * 0.0;
  fVar12 = fVar15 * fVar7 + fVar34 * 0.0 + fVar22 * 0.0 + fVar24 * fVar35;
  fVar14 = fVar8 * fVar7 + fVar25 * fVar34 + fVar22 * 0.0 + fVar35 * 0.0;
  fVar7 = fVar10 * fVar7 + fVar18 * fVar34 + fVar16 * fVar22 + fVar17 * fVar35;
  fVar22 = fVar13 * fVar4 + fVar37 * 0.0 + fVar23 * fVar19 + fVar38 * 0.0;
  fVar35 = fVar15 * fVar4 + fVar37 * 0.0 + fVar19 * 0.0 + fVar24 * fVar38;
  fVar21 = fVar8 * fVar4 + fVar25 * fVar37 + fVar19 * 0.0 + fVar38 * 0.0;
  fVar37 = fVar10 * fVar4 + fVar18 * fVar37 + fVar16 * fVar19 + fVar17 * fVar38;
  fVar4 = fVar13 * fVar6 + fVar36 * 0.0 + fVar23 * fVar27 + fVar11 * 0.0;
  fVar34 = fVar15 * fVar6 + fVar36 * 0.0 + fVar27 * 0.0 + fVar24 * fVar11;
  fVar19 = fVar8 * fVar6 + fVar25 * fVar36 + fVar27 * 0.0 + fVar11 * 0.0;
  fVar6 = fVar10 * fVar6 + fVar18 * fVar36 + fVar16 * fVar27 + fVar17 * fVar11;
  fVar13 = fVar23 * 0.0 + 0.0 + 0.0 + fVar13;
  fVar15 = fVar24 * 0.0 + 0.0 + 0.0 + fVar15;
  uVar5 = CONCAT44(fVar15,fVar13);
  fVar8 = fVar25 * 0.0 + 0.0 + fVar8;
  fVar10 = fVar18 * 0.0 + fVar16 * 0.0 + fVar17 * 0.0 + fVar10;
  uVar9 = CONCAT44(fVar10,fVar8);
  if (lVar3 == 0) {
    *(float *)(param_1 + 0x18) = fVar21;
    *(float *)(param_1 + 0x1c) = fVar37;
    *(float *)(param_1 + 0x10) = fVar22;
    *(float *)(param_1 + 0x14) = fVar35;
    *(ulong *)(param_1 + 0x28) = CONCAT44(fVar6,fVar19);
    *(ulong *)(param_1 + 0x20) = CONCAT44(fVar34,fVar4);
    *(ulong *)(param_1 + 0x38) = CONCAT44(fVar7,fVar14);
    *(ulong *)(param_1 + 0x30) = CONCAT44(fVar12,fVar26);
  }
  else {
    fVar11 = (float)*puVar1;
    fVar16 = (float)((ulong)*puVar1 >> 0x20);
    fVar27 = (float)puVar1[2];
    fVar23 = (float)((ulong)puVar1[2] >> 0x20);
    fVar36 = (float)puVar1[4];
    fVar38 = (float)((ulong)puVar1[4] >> 0x20);
    fVar17 = (float)puVar1[1];
    fVar18 = (float)((ulong)puVar1[1] >> 0x20);
    fVar24 = (float)puVar1[3];
    fVar25 = (float)((ulong)puVar1[3] >> 0x20);
    fVar28 = (float)puVar1[5];
    fVar29 = (float)((ulong)puVar1[5] >> 0x20);
    fVar30 = (float)puVar1[6];
    fVar31 = (float)((ulong)puVar1[6] >> 0x20);
    fVar32 = (float)puVar1[7];
    fVar33 = (float)((ulong)puVar1[7] >> 0x20);
    *(ulong *)(param_1 + 0x18) =
         CONCAT44(fVar10 * fVar18 + fVar7 * fVar17 + fVar37 * fVar11 + fVar6 * fVar16,
                  fVar8 * fVar18 + fVar14 * fVar17 + fVar21 * fVar11 + fVar19 * fVar16);
    *(ulong *)(param_1 + 0x10) =
         CONCAT44(fVar15 * fVar18 + fVar12 * fVar17 + fVar35 * fVar11 + fVar34 * fVar16,
                  fVar13 * fVar18 + fVar26 * fVar17 + fVar22 * fVar11 + fVar4 * fVar16);
    *(float *)(param_1 + 0x28) =
         fVar8 * fVar25 + fVar14 * fVar24 + fVar21 * fVar27 + fVar19 * fVar23;
    *(float *)(param_1 + 0x2c) = fVar10 * fVar25 + fVar7 * fVar24 + fVar37 * fVar27 + fVar6 * fVar23
    ;
    *(float *)(param_1 + 0x20) =
         fVar13 * fVar25 + fVar26 * fVar24 + fVar22 * fVar27 + fVar4 * fVar23;
    *(float *)(param_1 + 0x24) =
         fVar15 * fVar25 + fVar12 * fVar24 + fVar35 * fVar27 + fVar34 * fVar23;
    *(ulong *)(param_1 + 0x38) =
         CONCAT44(fVar10 * fVar29 + fVar7 * fVar28 + fVar37 * fVar36 + fVar6 * fVar38,
                  fVar8 * fVar29 + fVar14 * fVar28 + fVar21 * fVar36 + fVar19 * fVar38);
    *(ulong *)(param_1 + 0x30) =
         CONCAT44(fVar15 * fVar29 + fVar12 * fVar28 + fVar35 * fVar36 + fVar34 * fVar38,
                  fVar13 * fVar29 + fVar26 * fVar28 + fVar22 * fVar36 + fVar4 * fVar38);
    uVar5 = CONCAT44(fVar15 * fVar33 + fVar12 * fVar32 + fVar35 * fVar30 + fVar34 * fVar31,
                     fVar13 * fVar33 + fVar26 * fVar32 + fVar22 * fVar30 + fVar4 * fVar31);
    uVar9 = CONCAT44(fVar10 * fVar33 + fVar7 * fVar32 + fVar37 * fVar30 + fVar6 * fVar31,
                     fVar8 * fVar33 + fVar14 * fVar32 + fVar21 * fVar30 + fVar19 * fVar31);
  }
  *(undefined8 *)(param_1 + 0x48) = uVar9;
  *(undefined8 *)(param_1 + 0x40) = uVar5;
  *(byte *)(param_1 + 0xf8) = *(byte *)(param_1 + 0xf8) & 0xfe;
  *(byte *)(param_2 + 0x128) = *(byte *)(param_2 + 0x128) & 0xe2;
  *(byte *)(param_1 + 0xf9) = *(byte *)(param_1 + 0xf9) | 3;
  return;
}

// ==== Aska::HierarchicalObjectContainer::~HierarchicalObjectContainer()
// vaddr 0x21361a4 | ghidra 0x22361a4 | size 44 | symbol _ZN4Aska27HierarchicalObjectContainerD2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska27HierarchicalObjectContainerD2Ev(long *param_1)

{
  long lVar1;
  long lVar2;
  
  *param_1 = (long)(PTR__ZTVN4Aska27HierarchicalObjectContainerE_02cb81a8 + 0x10);
  lVar1 = param_1[0x1c];
  while (lVar1 != 0) {
    lVar2 = *(long *)(lVar1 + 8);
    *(undefined8 *)(lVar1 + 8) = 0;
    *(undefined8 *)(lVar1 + 0x10) = 0;
    lVar1 = lVar2;
  }
  (*(code *)PTR__ZN4Aska11IAnimatableD2Ev_02cb13b8)();
  return;
}

// ==== Aska::HierarchicalObjectContainer::~HierarchicalObjectContainer()
// vaddr 0x21361d0 | ghidra 0x22361d0 | size 68 | symbol _ZN4Aska27HierarchicalObjectContainerD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska27HierarchicalObjectContainerD0Ev(long *param_1)

{
  long lVar1;
  long lVar2;
  
  *param_1 = (long)(PTR__ZTVN4Aska27HierarchicalObjectContainerE_02cb81a8 + 0x10);
  lVar1 = param_1[0x1c];
  while (lVar1 != 0) {
    lVar2 = *(long *)(lVar1 + 8);
    *(undefined8 *)(lVar1 + 8) = 0;
    *(undefined8 *)(lVar1 + 0x10) = 0;
    lVar1 = lVar2;
  }
  Aska::IAnimatable::~IAnimatable()(param_1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::HierarchicalObjectContainer::GetClassID(int) const
// vaddr 0x2136214 | ghidra 0x2236214 | size 24 | symbol _ZNK4Aska27HierarchicalObjectContainer10GetClassIDEi | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska27HierarchicalObjectContainer10GetClassIDEi(undefined8 param_1,int param_2)

{
  undefined8 uVar1;
  
  uVar1 = 0xf000f03d;
  if (param_2 != 0) {
    uVar1 = 0xf000;
  }
  return uVar1;
}

// ==== Aska::HierarchicalObjectContainer::Get(unsigned long, void*) const
// vaddr 0x213622c | ghidra 0x223622c | size 8 | symbol _ZNK4Aska27HierarchicalObjectContainer3GetEmPv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska27HierarchicalObjectContainer3GetEmPv(void)

{
  return 0;
}

// ==== Aska::HierarchicalObjectContainer::Set(unsigned long, void const*)
// vaddr 0x2136234 | ghidra 0x2236234 | size 8 | symbol _ZN4Aska27HierarchicalObjectContainer3SetEmPKv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska27HierarchicalObjectContainer3SetEmPKv(void)

{
  return 0;
}


// FAILED to create function at 02bb4228 Aska::Task::vtable
// FAILED to create function at 02bb42d0 Aska::Task::typeinfo
// FAILED to create function at 02c4e208 Aska::HierarchicalObject::vtable
// FAILED to create function at 02c4e380 Aska::HierarchicalObject::typeinfo
// FAILED to create function at 02c4e398 Aska::HierarchicalObjectContainer::vtable
// FAILED to create function at 02c4e3e0 Aska::HierarchicalObjectContainer::typeinfo
// FAILED to create function at 02dce430 Aska::HierarchicalObject::m_vDefaultSphere
// FAILED to create function at 02dce478 Aska::HierarchicalObjectContainer::m_pHOCList
// FAILED to create function at 02dce480 Aska::HierarchicalObjectContainer::m_nNumHOCList
// FAILED to create function at 02dce484 Aska::HierarchicalObjectContainer::m_nCurrentHOCList
