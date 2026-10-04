// port/decomp/anim/aaf_handler.c: Ghidra decompiles for the anim subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-04 06:27 UTC: tools/decomp.sh '--into' 'anim/aaf_handler' 'Aska::AafHandler::' 'Aska::AafBlendManager::' 'Aska::AafController::'

// ==== Aska::AafBlendManager::~AafBlendManager()
// vaddr 0x1f8db44 | ghidra 0x208db44 | size 36 | symbol _ZN4Aska15AafBlendManagerD2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska15AafBlendManagerD1Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska15AafBlendManagerE_02cb9d28 + 0x10);
  if (param_1[7] != 0) {
    (*(code *)PTR__ZdaPv_02cb5db8)();
    return;
  }
  return;
}

// ==== Aska::AafBlendManager::~AafBlendManager()
// vaddr 0x1f8db68 | ghidra 0x208db68 | size 48 | symbol _ZN4Aska15AafBlendManagerD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska15AafBlendManagerD0Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska15AafBlendManagerE_02cb9d28 + 0x10);
  if (param_1[7] != 0) {
    operator delete[](void*)();
  }
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::AafBlendManager::Create(int)
// vaddr 0x1f8db98 | ghidra 0x208db98 | size 124 | symbol _ZN4Aska15AafBlendManager6CreateEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska15AafBlendManager6CreateEi(long param_1,int param_2)

{
  int iVar1;
  undefined1 auVar2 [16];
  bool bVar3;
  long lVar4;
  
  if (*(long *)(param_1 + 0x38) != 0) {
    if (*(int *)(param_1 + 0x24) == param_2) {
      bVar3 = true;
      goto code_r0x0208dc04;
    }
    operator delete[](void*)();
  }
  auVar2._8_8_ = 0;
  auVar2._0_8_ = (long)param_2;
  lVar4 = ((long)param_2 + (long)param_2 * 2) * 0x10;
  if (SUB168(auVar2 * ZEXT816(0x30),8) != 0) {
    lVar4 = -1;
  }
  lVar4 = operator new[](unsigned long, unsigned long, bool)(lVar4,0x10,1);
  bVar3 = lVar4 != 0;
  *(long *)(param_1 + 0x38) = lVar4;
  iVar1 = 0;
  if (bVar3) {
    iVar1 = param_2;
  }
  *(int *)(param_1 + 0x24) = iVar1;
code_r0x0208dc04:
  *(bool *)(param_1 + 8) = bVar3;
  return;
}

// ==== Aska::AafBlendManager::Open(int)
// vaddr 0x1f8dc14 | ghidra 0x208dc14 | size 100 | symbol _ZN4Aska15AafBlendManager4OpenEi | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska15AafBlendManager4OpenEi(long param_1,int param_2)

{
  undefined4 uVar1;
  
  if (*(char *)(param_1 + 8) == '\0') {
    return 0;
  }
  if (*(long *)(param_1 + 0x38) != 0) {
    if (*(int *)(param_1 + 0x24) < param_2) {
      return 0;
    }
    uVar1 = *(undefined4 *)(param_1 + 0x28);
    *(undefined4 *)(param_1 + 0x30) = 0;
    *(int *)(param_1 + 0x28) = param_2;
    *(undefined4 *)(param_1 + 0x2c) = uVar1;
    memset(*(long *)(param_1 + 0x38),0,(long)param_2 * 0x30);
    return 1;
  }
  return 0;
}

// ==== Aska::AafBlendManager::Close(unsigned char)
// vaddr 0x1f8dc78 | ghidra 0x208dc78 | size 112 | symbol _ZN4Aska15AafBlendManager5CloseEh | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska15AafBlendManager5CloseEh(long param_1,undefined1 param_2)

{
  long lVar1;
  long *plVar2;
  
  if (0 < *(int *)(param_1 + 0x30)) {
    *(undefined1 *)(param_1 + 9) = param_2;
    if (*(int *)(param_1 + 0x30) == 1) {
      *(undefined4 *)(param_1 + 0x40) = 0;
    }
    else {
      *(undefined4 *)(param_1 + 0x20) = 0xffffffff;
      if (0 < *(int *)(param_1 + 0x28)) {
        lVar1 = 0;
        plVar2 = (long *)(*(long *)(param_1 + 0x38) + 0x10);
        do {
          if (*plVar2 != 0) {
            *(int *)(param_1 + 0x20) = (int)lVar1;
            break;
          }
          lVar1 = lVar1 + 1;
          plVar2 = plVar2 + 6;
        } while (lVar1 < *(int *)(param_1 + 0x28));
      }
    }
  }
  *(undefined4 *)(param_1 + 0x30) = 0xffffffff;
  return 1;
}

// ==== Aska::AafBlendManager::AllocateControllerBuffer()
// vaddr 0x1f8dce8 | ghidra 0x208dce8 | size 76 | symbol _ZN4Aska15AafBlendManager24AllocateControllerBufferEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska15AafBlendManager24AllocateControllerBufferEv(long param_1)

{
  long lVar1;
  long *plVar2;
  
  *(undefined4 *)(param_1 + 0x20) = 0xffffffff;
  if (0 < *(int *)(param_1 + 0x28)) {
    lVar1 = 0;
    plVar2 = (long *)(*(long *)(param_1 + 0x38) + 0x10);
    do {
      if (*plVar2 != 0) {
        *(int *)(param_1 + 0x20) = (int)lVar1;
        return 1;
      }
      lVar1 = lVar1 + 1;
      plVar2 = plVar2 + 6;
    } while (lVar1 < *(int *)(param_1 + 0x28));
  }
  return 1;
}

// ==== Aska::AafBlendManager::FreeControllerBuffer()
// vaddr 0x1f8dd34 | ghidra 0x208dd34 | size 8 | symbol _ZN4Aska15AafBlendManager20FreeControllerBufferEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska15AafBlendManager20FreeControllerBufferEv(long param_1)

{
  *(undefined4 *)(param_1 + 0x40) = 0;
  return;
}

// ==== Aska::AafBlendManager::AddAaf(Aska::AafHandler*)
// vaddr 0x1f8dd3c | ghidra 0x208dd3c | size 68 | symbol _ZN4Aska15AafBlendManager6AddAafEPNS_10AafHandlerE | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZN4Aska15AafBlendManager6AddAafEPNS_10AafHandlerE(long param_1,undefined8 param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = *(int *)(param_1 + 0x30);
  uVar2 = 0;
  if ((iVar1 < *(int *)(param_1 + 0x28)) && (-1 < iVar1)) {
    *(int *)(param_1 + 0x30) = iVar1 + 1;
    *(undefined8 *)(*(long *)(param_1 + 0x38) + (long)iVar1 * 0x30 + 0x10) = param_2;
    uVar2 = 1;
  }
  return uVar2;
}

// ==== Aska::AafBlendManager::GetPlayFrame(int) const
// vaddr 0x1f8dd80 | ghidra 0x208dd80 | size 52 | symbol _ZNK4Aska15AafBlendManager12GetPlayFrameEi | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK4Aska15AafBlendManager12GetPlayFrameEi(long param_1,int param_2)

{
  undefined4 uVar1;
  
  uVar1 = 0;
  if ((((*(char *)(param_1 + 8) != '\0') && (*(long *)(param_1 + 0x38) != 0)) && (-1 < param_2)) &&
     (param_2 < *(int *)(param_1 + 0x28))) {
    uVar1 = *(undefined4 *)(*(long *)(param_1 + 0x38) + (long)param_2 * 0x30);
  }
  return uVar1;
}

// ==== Aska::AafBlendManager::GetPlayFrame(Aska::AafHandler const*) const
// vaddr 0x1f8ddb4 | ghidra 0x208ddb4 | size 104 | symbol _ZNK4Aska15AafBlendManager12GetPlayFrameEPKNS_10AafHandlerE | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK4Aska15AafBlendManager12GetPlayFrameEPKNS_10AafHandlerE(long param_1,long param_2)

{
  int iVar1;
  long lVar2;
  int iVar3;
  long lVar4;
  long *plVar5;
  undefined4 uVar6;
  
  uVar6 = 0;
  if ((*(char *)(param_1 + 8) != '\0') && (lVar2 = *(long *)(param_1 + 0x38), lVar2 != 0)) {
    iVar1 = *(int *)(param_1 + 0x28);
    if (iVar1 < 1) {
      lVar4 = 0;
    }
    else {
      lVar4 = 0;
      plVar5 = (long *)(lVar2 + 0x10);
      do {
        if (*plVar5 == param_2) break;
        lVar4 = lVar4 + 1;
        plVar5 = plVar5 + 6;
      } while (lVar4 < iVar1);
    }
    iVar3 = (int)lVar4;
    if ((-1 < iVar3) && (iVar3 < iVar1)) {
      uVar6 = *(undefined4 *)(lVar2 + (long)iVar3 * 0x30);
    }
  }
  return uVar6;
}

// ==== Aska::AafBlendManager::SetPlayFrame(int, float)
// vaddr 0x1f8de1c | ghidra 0x208de1c | size 76 | symbol _ZN4Aska15AafBlendManager12SetPlayFrameEif | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska15AafBlendManager12SetPlayFrameEif(undefined4 param_1,long param_2,int param_3)

{
  undefined8 uVar1;
  
  if (*(char *)(param_2 + 8) == '\0') {
    return 0;
  }
  if (*(long *)(param_2 + 0x38) != 0) {
    uVar1 = 0;
    if ((-1 < param_3) && (param_3 < *(int *)(param_2 + 0x28))) {
      uVar1 = 1;
      *(undefined4 *)(*(long *)(param_2 + 0x38) + (long)param_3 * 0x30) = param_1;
    }
    return uVar1;
  }
  return 0;
}

// ==== Aska::AafBlendManager::SetPlayFrame(Aska::AafHandler const*, float)
// vaddr 0x1f8de68 | ghidra 0x208de68 | size 124 | symbol _ZN4Aska15AafBlendManager12SetPlayFrameEPKNS_10AafHandlerEf | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska15AafBlendManager12SetPlayFrameEPKNS_10AafHandlerEf
          (undefined4 param_1,long param_2,long param_3)

{
  int iVar1;
  undefined8 uVar2;
  long lVar3;
  int iVar4;
  long lVar5;
  long *plVar6;
  
  if (*(char *)(param_2 + 8) == '\0') {
    return 0;
  }
  lVar3 = *(long *)(param_2 + 0x38);
  if (lVar3 == 0) {
    return 0;
  }
  iVar1 = *(int *)(param_2 + 0x28);
  if (iVar1 < 1) {
    lVar5 = 0;
  }
  else {
    lVar5 = 0;
    plVar6 = (long *)(lVar3 + 0x10);
    do {
      if (*plVar6 == param_3) break;
      lVar5 = lVar5 + 1;
      plVar6 = plVar6 + 6;
    } while (lVar5 < iVar1);
  }
  uVar2 = 0;
  iVar4 = (int)lVar5;
  if ((-1 < iVar4) && (iVar4 < iVar1)) {
    uVar2 = 1;
    *(undefined4 *)(lVar3 + (long)iVar4 * 0x30) = param_1;
  }
  return uVar2;
}

// ==== Aska::AafBlendManager::GetWeight(int) const
// vaddr 0x1f8dee4 | ghidra 0x208dee4 | size 52 | symbol _ZNK4Aska15AafBlendManager9GetWeightEi | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK4Aska15AafBlendManager9GetWeightEi(long param_1,int param_2)

{
  undefined4 uVar1;
  
  uVar1 = 0;
  if ((((*(char *)(param_1 + 8) != '\0') && (*(long *)(param_1 + 0x38) != 0)) && (-1 < param_2)) &&
     (param_2 < *(int *)(param_1 + 0x28))) {
    uVar1 = *(undefined4 *)(*(long *)(param_1 + 0x38) + (long)param_2 * 0x30 + 8);
  }
  return uVar1;
}

// ==== Aska::AafBlendManager::GetWeight(Aska::AafHandler const*) const
// vaddr 0x1f8df18 | ghidra 0x208df18 | size 104 | symbol _ZNK4Aska15AafBlendManager9GetWeightEPKNS_10AafHandlerE | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK4Aska15AafBlendManager9GetWeightEPKNS_10AafHandlerE(long param_1,long param_2)

{
  int iVar1;
  long lVar2;
  int iVar3;
  long lVar4;
  long *plVar5;
  undefined4 uVar6;
  
  uVar6 = 0;
  if ((*(char *)(param_1 + 8) != '\0') && (lVar2 = *(long *)(param_1 + 0x38), lVar2 != 0)) {
    iVar1 = *(int *)(param_1 + 0x28);
    if (iVar1 < 1) {
      lVar4 = 0;
    }
    else {
      lVar4 = 0;
      plVar5 = (long *)(lVar2 + 0x10);
      do {
        if (*plVar5 == param_2) break;
        lVar4 = lVar4 + 1;
        plVar5 = plVar5 + 6;
      } while (lVar4 < iVar1);
    }
    iVar3 = (int)lVar4;
    if ((-1 < iVar3) && (iVar3 < iVar1)) {
      uVar6 = *(undefined4 *)(lVar2 + (long)iVar3 * 0x30 + 8);
    }
  }
  return uVar6;
}

// ==== Aska::AafBlendManager::SetWeight(int, float)
// vaddr 0x1f8df80 | ghidra 0x208df80 | size 76 | symbol _ZN4Aska15AafBlendManager9SetWeightEif | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska15AafBlendManager9SetWeightEif(undefined4 param_1,long param_2,int param_3)

{
  undefined8 uVar1;
  
  if (*(char *)(param_2 + 8) == '\0') {
    return 0;
  }
  if (*(long *)(param_2 + 0x38) != 0) {
    uVar1 = 0;
    if ((-1 < param_3) && (param_3 < *(int *)(param_2 + 0x28))) {
      uVar1 = 1;
      *(undefined4 *)(*(long *)(param_2 + 0x38) + (long)param_3 * 0x30 + 8) = param_1;
    }
    return uVar1;
  }
  return 0;
}

// ==== Aska::AafBlendManager::SetWeight(Aska::AafHandler const*, float)
// vaddr 0x1f8dfcc | ghidra 0x208dfcc | size 124 | symbol _ZN4Aska15AafBlendManager9SetWeightEPKNS_10AafHandlerEf | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska15AafBlendManager9SetWeightEPKNS_10AafHandlerEf
          (undefined4 param_1,long param_2,long param_3)

{
  int iVar1;
  undefined8 uVar2;
  long lVar3;
  int iVar4;
  long lVar5;
  long *plVar6;
  
  if (*(char *)(param_2 + 8) == '\0') {
    return 0;
  }
  lVar3 = *(long *)(param_2 + 0x38);
  if (lVar3 == 0) {
    return 0;
  }
  iVar1 = *(int *)(param_2 + 0x28);
  if (iVar1 < 1) {
    lVar5 = 0;
  }
  else {
    lVar5 = 0;
    plVar6 = (long *)(lVar3 + 0x10);
    do {
      if (*plVar6 == param_3) break;
      lVar5 = lVar5 + 1;
      plVar6 = plVar6 + 6;
    } while (lVar5 < iVar1);
  }
  uVar2 = 0;
  iVar4 = (int)lVar5;
  if ((-1 < iVar4) && (iVar4 < iVar1)) {
    uVar2 = 1;
    *(undefined4 *)(lVar3 + (long)iVar4 * 0x30 + 8) = param_1;
  }
  return uVar2;
}

// ==== Aska::AafBlendManager::GetNotify(int)
// vaddr 0x1f8e048 | ghidra 0x208e048 | size 72 | symbol _ZN4Aska15AafBlendManager9GetNotifyEi | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska15AafBlendManager9GetNotifyEi(long param_1,int param_2)

{
  undefined8 uVar1;
  
  if (*(char *)(param_1 + 8) == '\0') {
    return 0;
  }
  if (*(long *)(param_1 + 0x38) != 0) {
    uVar1 = 0;
    if ((-1 < param_2) && (param_2 < *(int *)(param_1 + 0x28))) {
      uVar1 = *(undefined8 *)(*(long *)(param_1 + 0x38) + (long)param_2 * 0x30 + 0x18);
    }
    return uVar1;
  }
  return 0;
}

// ==== Aska::AafBlendManager::GetNotify(Aska::AafHandler const*)
// vaddr 0x1f8e090 | ghidra 0x208e090 | size 120 | symbol _ZN4Aska15AafBlendManager9GetNotifyEPKNS_10AafHandlerE | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska15AafBlendManager9GetNotifyEPKNS_10AafHandlerE(long param_1,long param_2)

{
  int iVar1;
  undefined8 uVar2;
  long lVar3;
  int iVar4;
  long lVar5;
  long *plVar6;
  
  if (*(char *)(param_1 + 8) == '\0') {
    return 0;
  }
  lVar3 = *(long *)(param_1 + 0x38);
  if (lVar3 == 0) {
    return 0;
  }
  iVar1 = *(int *)(param_1 + 0x28);
  if (iVar1 < 1) {
    lVar5 = 0;
  }
  else {
    lVar5 = 0;
    plVar6 = (long *)(lVar3 + 0x10);
    do {
      if (*plVar6 == param_2) break;
      lVar5 = lVar5 + 1;
      plVar6 = plVar6 + 6;
    } while (lVar5 < iVar1);
  }
  uVar2 = 0;
  iVar4 = (int)lVar5;
  if ((-1 < iVar4) && (iVar4 < iVar1)) {
    uVar2 = *(undefined8 *)(lVar3 + (long)iVar4 * 0x30 + 0x18);
  }
  return uVar2;
}

// ==== Aska::AafBlendManager::SetNotify(int, Aska::INotify*)
// vaddr 0x1f8e108 | ghidra 0x208e108 | size 76 | symbol _ZN4Aska15AafBlendManager9SetNotifyEiPNS_7INotifyE | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska15AafBlendManager9SetNotifyEiPNS_7INotifyE(long param_1,int param_2,undefined8 param_3)

{
  undefined8 uVar1;
  
  if (*(char *)(param_1 + 8) == '\0') {
    return 0;
  }
  if (*(long *)(param_1 + 0x38) != 0) {
    uVar1 = 0;
    if ((-1 < param_2) && (param_2 < *(int *)(param_1 + 0x28))) {
      uVar1 = 1;
      *(undefined8 *)(*(long *)(param_1 + 0x38) + (long)param_2 * 0x30 + 0x18) = param_3;
    }
    return uVar1;
  }
  return 0;
}

// ==== Aska::AafBlendManager::SetNotify(Aska::AafHandler const*, Aska::INotify*)
// vaddr 0x1f8e154 | ghidra 0x208e154 | size 124 | symbol _ZN4Aska15AafBlendManager9SetNotifyEPKNS_10AafHandlerEPNS_7INotifyE | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska15AafBlendManager9SetNotifyEPKNS_10AafHandlerEPNS_7INotifyE
          (long param_1,long param_2,undefined8 param_3)

{
  int iVar1;
  undefined8 uVar2;
  long lVar3;
  int iVar4;
  long lVar5;
  long *plVar6;
  
  if (*(char *)(param_1 + 8) == '\0') {
    return 0;
  }
  lVar3 = *(long *)(param_1 + 0x38);
  if (lVar3 == 0) {
    return 0;
  }
  iVar1 = *(int *)(param_1 + 0x28);
  if (iVar1 < 1) {
    lVar5 = 0;
  }
  else {
    lVar5 = 0;
    plVar6 = (long *)(lVar3 + 0x10);
    do {
      if (*plVar6 == param_2) break;
      lVar5 = lVar5 + 1;
      plVar6 = plVar6 + 6;
    } while (lVar5 < iVar1);
  }
  uVar2 = 0;
  iVar4 = (int)lVar5;
  if ((-1 < iVar4) && (iVar4 < iVar1)) {
    uVar2 = 1;
    *(undefined8 *)(lVar3 + (long)iVar4 * 0x30 + 0x18) = param_3;
  }
  return uVar2;
}

// ==== Aska::AafBlendManager::NormalizeWeights()
// vaddr 0x1f8e1d0 | ghidra 0x208e1d0 | size 156 | symbol _ZN4Aska15AafBlendManager16NormalizeWeightsEv | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 _ZN4Aska15AafBlendManager16NormalizeWeightsEv(long param_1)

{
  float *pfVar1;
  long lVar2;
  uint uVar3;
  ulong uVar4;
  long lVar5;
  long *plVar6;
  float fVar7;
  float fVar8;
  
  uVar3 = *(uint *)(param_1 + 0x28);
  if (0 < (int)uVar3) {
    lVar5 = 0;
    uVar4 = (ulong)uVar3;
    fVar7 = 0.0;
    plVar6 = (long *)(*(long *)(param_1 + 0x38) + 0x10);
    do {
      if ((*plVar6 != 0) && ((*(byte *)(*plVar6 + 0xc) >> 1 & 1) == 0)) {
        return 0;
      }
      pfVar1 = (float *)(plVar6 + -1);
      lVar5 = lVar5 + 1;
      plVar6 = plVar6 + 6;
      fVar7 = fVar7 + *pfVar1;
    } while (lVar5 < (int)uVar3);
    fVar8 = 1.0;
    if (_UNK_027e519c < fVar7) {
      fVar8 = 1.0 / fVar7;
    }
    if (0 < (int)uVar3) {
      lVar5 = 0;
      do {
        uVar4 = uVar4 - 1;
        lVar2 = *(long *)(param_1 + 0x38) + lVar5;
        lVar5 = lVar5 + 0x30;
        *(float *)(lVar2 + 4) = fVar8 * *(float *)(lVar2 + 8);
      } while (uVar4 != 0);
    }
  }
  return 1;
}

// ==== Aska::AafBlendManager::StaticCalcValues_NoFiber(Aska::AafBlendManager*, int)
// vaddr 0x1f8e26c | ghidra 0x208e26c | size 184 | symbol _ZN4Aska15AafBlendManager24StaticCalcValues_NoFiberEPS0_i | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska15AafBlendManager24StaticCalcValues_NoFiberEPS0_i(long param_1,int param_2)

{
  undefined8 *puVar1;
  undefined4 *puVar2;
  long lVar3;
  float *pfVar4;
  
  lVar3 = *(long *)(param_1 + 0x38);
  puVar2 = (undefined4 *)(lVar3 + (long)param_2 * 0x30);
  puVar1 = *(undefined8 **)(puVar2 + 6);
  if (puVar1 != (undefined8 *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x0208e2a0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)*puVar1)();
    return;
  }
  pfVar4 = (float *)(lVar3 + (long)param_2 * 0x30 + 4);
  if (0.0 < *pfVar4) {
    lVar3 = *(long *)(lVar3 + (long)param_2 * 0x30 + 0x10);
    if (lVar3 != 0) {
      *(uint *)(lVar3 + 0xc) = *(uint *)(lVar3 + 0xc) | 0x20;
      if (*(float *)(param_1 + 0xc) == 0.0) {
        Aska::AafHandler::SetValues(float)();
      }
      else {
        Aska::AafHandler::BlendValues(float, float)(*puVar2,*pfVar4 / (*(float *)(param_1 + 0xc) + *pfVar4));
      }
    }
    *(float *)(param_1 + 0xc) = *pfVar4 + *(float *)(param_1 + 0xc);
  }
  return;
}

// ==== Aska::AafBlendManager::CalcValues()
// vaddr 0x1f8e324 | ghidra 0x208e324 | size 288 | symbol _ZN4Aska15AafBlendManager10CalcValuesEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska15AafBlendManager10CalcValuesEv(long param_1)

{
  undefined8 uVar1;
  undefined8 uVar2;
  int iVar3;
  undefined *puVar4;
  long lVar5;
  long lVar6;
  long lVar7;
  long lVar8;
  
  puVar4 = PTR__ZN4Aska6Global20m_pMessageDispatcherE_02cb77c8;
  iVar3 = *(int *)(param_1 + 0x28);
  if (0 < iVar3) {
    lVar5 = *(long *)(param_1 + 0x38);
    lVar8 = 0;
    lVar6 = *(long *)(lVar5 + (long)*(int *)(param_1 + 0x20) * 0x30 + 0x10);
    lVar7 = 0;
    uVar1 = *(undefined8 *)(lVar6 + 0x100);
    uVar2 = *(undefined8 *)(lVar6 + 0x108);
    while( true ) {
      if ((*(long *)(lVar5 + lVar8 + 0x10) == 0) && (0.0 < *(float *)(lVar5 + lVar8 + 4))) {
        Aska::SimpleMessageDispatcher::SendMessage(unsigned short, Aska::INotify*, void*, void*, unsigned long, unsigned long, signed char)(*(undefined8 *)puVar4,0,param_1 + 0x10,lVar7,0,uVar1,uVar2,0);
      }
      if ((long)iVar3 + -1 == lVar7) break;
      lVar5 = *(long *)(param_1 + 0x38);
      lVar7 = lVar7 + 1;
      lVar8 = lVar8 + 0x30;
    }
    if (0 < iVar3) {
      lVar8 = 0;
      lVar7 = 0;
      do {
        lVar5 = *(long *)(param_1 + 0x38) + lVar8;
        lVar6 = *(long *)(lVar5 + 0x10);
        if ((lVar6 != 0) && (0.0 < *(float *)(lVar5 + 4))) {
          Aska::SimpleMessageDispatcher::SendMessage(unsigned short, Aska::INotify*, void*, void*, unsigned long, unsigned long, signed char)(*(undefined8 *)puVar4,0,param_1 + 0x10,lVar7,0,
                          *(undefined8 *)(lVar6 + 0x100),*(undefined8 *)(lVar6 + 0x108),0);
        }
        lVar7 = lVar7 + 1;
        lVar8 = lVar8 + 0x30;
      } while (iVar3 != lVar7);
    }
  }
  return;
}

// ==== Aska::AafBlendManager::CopyMatrices(int)
// vaddr 0x1f8e444 | ghidra 0x208e444 | size 80 | symbol _ZN4Aska15AafBlendManager12CopyMatricesEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska15AafBlendManager12CopyMatricesEi(long param_1,int param_2)

{
  long lVar1;
  
  lVar1 = *(long *)(*(long *)(param_1 + 0x38) + (long)param_2 * 0x30 + 0x10);
  if (lVar1 == 0) {
    lVar1 = *(long *)(*(long *)(param_1 + 0x38) + (long)*(int *)(param_1 + 0x20) * 0x30 + 0x10);
  }
  (*(code *)PTR__ZN4Aska23SimpleMessageDispatcher11SendMessageEtPNS_7INotifyEPvS3_mma_02c904d0)
            (*(undefined8 *)PTR__ZN4Aska6Global20m_pMessageDispatcherE_02cb77c8,1,param_1 + 0x10,
             (long)param_2,0,*(undefined8 *)(lVar1 + 0x100),*(undefined8 *)(lVar1 + 0x108),0);
  return;
}

// ==== Aska::AafBlendManager::SetValues()
// vaddr 0x1f8e494 | ghidra 0x208e494 | size 32 | symbol _ZN4Aska15AafBlendManager9SetValuesEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska15AafBlendManager9SetValuesEv(undefined8 *param_1)

{
  *(undefined4 *)((long)param_1 + 0xc) = 0;
  (**(code **)*param_1)();
  return 1;
}

// ==== Aska::AafBlendManager::RestoreSnapShot(Aska::SceneSnapShot*, Aska::IAafBlendManager::_AafInfo&)
// vaddr 0x1f8e4b4 | ghidra 0x208e4b4 | size 192 | symbol _ZN4Aska15AafBlendManager15RestoreSnapShotEPNS_13SceneSnapShotERNS_16IAafBlendManager8_AafInfoE | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska15AafBlendManager15RestoreSnapShotEPNS_13SceneSnapShotERNS_16IAafBlendManager8_AafInfoE
          (undefined8 param_1,long param_2,long param_3)

{
  ulong uVar1;
  long lVar2;
  undefined8 uVar3;
  
  if (param_2 == 0) {
    return 0;
  }
  if (*(long *)(param_3 + 0x10) == 0) {
    return 0;
  }
  lVar2 = *(long *)(*(long *)(param_3 + 0x10) + 0x30);
  if (lVar2 == 0) {
    return 0;
  }
  if (*(int *)(param_2 + 8) == 2) {
    uVar1 = Aska::SceneSnapShot::Restore(Aska::AsfHandler*)(param_2,lVar2);
    if ((uVar1 & 1) == 0) {
      return 0;
    }
  }
  else {
    if (*(int *)(param_2 + 8) != 1) {
      return 0;
    }
    if (*(int *)(lVar2 + 0xb0) < 1) {
      uVar3 = 0;
    }
    else {
      uVar3 = *(undefined8 *)(**(long **)(lVar2 + 0xd8) + 0x38);
    }
    uVar1 = Aska::SceneSnapShot::Restore(Aska::HierarchicalObject*)(param_2,uVar3);
    if ((uVar1 & 1) == 0) {
      return 0;
    }
  }
  return 1;
}

// ==== Aska::AafBlendManager::SetValues(Aska::SceneSnapShot**)
// vaddr 0x1f8e574 | ghidra 0x208e574 | size 436 | symbol _ZN4Aska15AafBlendManager9SetValuesEPPNS_13SceneSnapShotE | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska15AafBlendManager9SetValuesEPPNS_13SceneSnapShotE(long param_1,long param_2)

{
  undefined8 uVar1;
  int iVar2;
  undefined *puVar3;
  ulong uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  long lVar9;
  long lVar10;
  long lVar11;
  long lVar12;
  
  puVar3 = PTR__ZN4Aska6Global20m_pMessageDispatcherE_02cb77c8;
  if (param_2 == 0) {
code_r0x0208e708:
    uVar6 = 0;
  }
  else {
    iVar2 = *(int *)(param_1 + 0x28);
    if (0 < iVar2) {
      lVar11 = 0;
      lVar10 = *(long *)(*(long *)(param_1 + 0x38) + (long)*(int *)(param_1 + 0x20) * 0x30 + 0x10);
      lVar12 = 0x10;
      uVar6 = *(undefined8 *)(lVar10 + 0x100);
      uVar1 = *(undefined8 *)(lVar10 + 0x108);
      lVar10 = *(long *)(*(long *)(param_1 + 0x38) + 0x10);
      while( true ) {
        if ((lVar10 == 0) && (*(long *)(param_2 + lVar11 * 8) == 0)) {
          Aska::SimpleMessageDispatcher::SendMessage(unsigned short, Aska::INotify*, void*, void*, unsigned long, unsigned long, signed char)(*(undefined8 *)puVar3,0,param_1 + 0x10,lVar11,0,uVar6,uVar1,0);
        }
        if ((long)iVar2 + -1 == lVar11) break;
        lVar11 = lVar11 + 1;
        lVar12 = lVar12 + 0x30;
        lVar10 = *(long *)(*(long *)(param_1 + 0x38) + lVar12);
      }
      if (0 < iVar2) {
        lVar11 = 0;
        lVar12 = 0x10;
        do {
          lVar10 = *(long *)(param_2 + lVar11 * 8);
          lVar9 = *(long *)(*(long *)(param_1 + 0x38) + lVar12);
          if (lVar10 == 0) {
            if (lVar9 != 0) {
              uVar5 = *(undefined8 *)puVar3;
              uVar7 = *(undefined8 *)(lVar9 + 0x100);
              uVar8 = *(undefined8 *)(lVar9 + 0x108);
              goto code_r0x0208e6e8;
            }
          }
          else {
            if ((lVar9 == 0) || (lVar9 = *(long *)(lVar9 + 0x30), lVar9 == 0))
            goto code_r0x0208e708;
            if (*(int *)(lVar10 + 8) == 2) {
              uVar4 = Aska::SceneSnapShot::Restore(Aska::AsfHandler*)();
            }
            else {
              if (*(int *)(lVar10 + 8) != 1) goto code_r0x0208e708;
              if (*(int *)(lVar9 + 0xb0) < 1) {
                uVar4 = Aska::SceneSnapShot::Restore(Aska::HierarchicalObject*)(lVar10,0);
              }
              else {
                uVar4 = Aska::SceneSnapShot::Restore(Aska::HierarchicalObject*)(lVar10,*(undefined8 *)(**(long **)(lVar9 + 0xd8) + 0x38));
              }
            }
            if ((uVar4 & 1) == 0) goto code_r0x0208e708;
            uVar5 = *(undefined8 *)puVar3;
            uVar7 = uVar6;
            uVar8 = uVar1;
code_r0x0208e6e8:
            Aska::SimpleMessageDispatcher::SendMessage(unsigned short, Aska::INotify*, void*, void*, unsigned long, unsigned long, signed char)(uVar5,0,param_1 + 0x10,lVar11,0,uVar7,uVar8,0);
          }
          lVar11 = lVar11 + 1;
          lVar12 = lVar12 + 0x30;
        } while (lVar11 < iVar2);
      }
    }
    uVar6 = 1;
  }
  return uVar6;
}

// ==== Aska::AafBlendManager::Initialize()
// vaddr 0x1f8e728 | ghidra 0x208e728 | size 36 | symbol _ZN4Aska15AafBlendManager10InitializeEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska15AafBlendManager10InitializeEv(long param_1)

{
  *(undefined8 *)(param_1 + 0x38) = 0;
  *(undefined4 *)(param_1 + 0x40) = 0;
  *(undefined8 *)(param_1 + 0x20) = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  *(long *)(param_1 + 0x18) = param_1;
  *(undefined2 *)(param_1 + 8) = 0x200;
  *(undefined4 *)(param_1 + 0x30) = 0xffffffff;
  return;
}

// ==== Aska::AafBlendManager::_CalcNotify::Handler(unsigned long)
// vaddr 0x1f8e74c | ghidra 0x208e74c | size 184 | symbol _ZN4Aska15AafBlendManager11_CalcNotify7HandlerEm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska15AafBlendManager11_CalcNotify7HandlerEm(long param_1,long param_2)

{
  undefined8 *puVar1;
  undefined4 *puVar2;
  long lVar3;
  long lVar4;
  long lVar5;
  float *pfVar6;
  
  lVar5 = *(long *)(param_1 + 8);
  lVar3 = (long)*(int *)(param_2 + 0x30);
  lVar4 = *(long *)(lVar5 + 0x38);
  puVar2 = (undefined4 *)(lVar4 + lVar3 * 0x30);
  puVar1 = *(undefined8 **)(puVar2 + 6);
  if (puVar1 != (undefined8 *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x0208e784. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)*puVar1)();
    return;
  }
  pfVar6 = (float *)(lVar4 + lVar3 * 0x30 + 4);
  if (0.0 < *pfVar6) {
    lVar3 = *(long *)(lVar4 + lVar3 * 0x30 + 0x10);
    if (lVar3 != 0) {
      *(uint *)(lVar3 + 0xc) = *(uint *)(lVar3 + 0xc) | 0x20;
      if (*(float *)(lVar5 + 0xc) == 0.0) {
        Aska::AafHandler::SetValues(float)();
      }
      else {
        Aska::AafHandler::BlendValues(float, float)(*puVar2,*pfVar6 / (*(float *)(lVar5 + 0xc) + *pfVar6));
      }
    }
    *(float *)(lVar5 + 0xc) = *pfVar6 + *(float *)(lVar5 + 0xc);
  }
  return;
}

// ==== Aska::AafBlendManager::_CalcNotify::~_CalcNotify()
// vaddr 0x1f8e804 | ghidra 0x208e804 | size 4 | symbol _ZN4Aska15AafBlendManager11_CalcNotifyD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska15AafBlendManager11_CalcNotifyD0Ev(void)

{
  (*(code *)PTR__ZdlPv_02ca4758)();
  return;
}

// ==== Aska::AafHandler::Function_SearchKeyFrameData(void*&, Aska::FrameSortDataForSearchOld*&, int&, unsigned int, Aska::FrameSortDataForSearchOld*, unsigned short, int, int, bool)
// vaddr 0x1f8e808 | ghidra 0x208e808 | size 132 | symbol _ZN4Aska10AafHandler27Function_SearchKeyFrameDataERPvRPNS_25FrameSortDataForSearchOldERijS4_tiib | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska10AafHandler27Function_SearchKeyFrameDataERPvRPNS_25FrameSortDataForSearchOldERijS4_tiib
          (long *param_1,long *param_2,int *param_3,int param_4,long param_5,ushort param_6,
          int param_7,int param_8)

{
  uint *puVar1;
  int *piVar2;
  long lVar3;
  int iVar4;
  ushort *puVar5;
  
  if (param_8 < 0) {
    param_4 = -1;
  }
  if (*param_3 + param_7 != param_4) {
    lVar3 = (long)(*param_3 + param_7);
    do {
      puVar1 = (uint *)(param_5 + lVar3 * 8);
      *param_2 = (long)puVar1;
      piVar2 = (int *)((ulong)*puVar1 + (long)puVar1);
      iVar4 = *piVar2;
      if (iVar4 != 0) {
        puVar5 = (ushort *)((long)piVar2 + 6);
        do {
          Hint_Prefetch(puVar5 + 1,0,2,0);
          if (puVar5[-1] == param_6) {
            *param_1 = (long)piVar2 + (ulong)*puVar5;
            *param_3 = (int)lVar3;
            return 1;
          }
          iVar4 = iVar4 + -1;
          puVar5 = puVar5 + 2;
        } while (iVar4 != 0);
      }
      lVar3 = lVar3 + param_8;
    } while (param_4 != (int)lVar3);
  }
  return 0;
}

// ==== Aska::AafHandler::Function_RenewalAllControllerCache(float, unsigned int*, unsigned int*, unsigned int, Aska::AafControllerInfo*, unsigned int, Aska::FrameSortDataForSearchOld*, unsigned int, bool)
// vaddr 0x1f8e88c | ghidra 0x208e88c | size 1120 | symbol _ZN4Aska10AafHandler34Function_RenewalAllControllerCacheEfPjS1_jPNS_17AafControllerInfoEjPNS_25FrameSortDataForSearchOldEjb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10AafHandler34Function_RenewalAllControllerCacheEfPjS1_jPNS_17AafControllerInfoEjPNS_25FrameSortDataForSearchOldEjb
               (float param_1,long param_2,long param_3,uint param_4,long param_5,int param_6,
               long param_7,uint param_8,ulong param_9)

{
  undefined8 *puVar1;
  uint *puVar2;
  uint *puVar3;
  uint uVar4;
  undefined8 *puVar5;
  undefined8 *puVar6;
  bool bVar7;
  long lVar8;
  uint *puVar9;
  uint uVar10;
  long lVar11;
  uint uVar12;
  int *piVar13;
  undefined8 *puVar14;
  uint *puVar15;
  long *plVar16;
  ulong uVar17;
  uint uVar18;
  ulong uVar19;
  float fVar20;
  int iVar21;
  int iVar22;
  int iVar23;
  int iVar24;
  int iVar25;
  int iVar26;
  int iVar27;
  int iVar28;
  int iVar29;
  int iVar30;
  int iVar31;
  int iVar32;
  int iVar33;
  undefined8 uVar34;
  int iVar35;
  int iVar36;
  int iVar37;
  uint uVar38;
  int iStack_78;
  int iStack_74;
  
  if ((param_9 & 1) == 0) {
    uVar4 = param_8 - 1;
    uVar18 = uVar4 >> 1;
    fVar20 = *(float *)(param_7 + (ulong)uVar18 * 8 + 4);
    if ((int)uVar18 < (int)uVar4) {
      if (uVar18 == 0) {
        if (param_1 <= fVar20) goto joined_r0x0208e9f0;
      }
      else {
        if ((param_1 < *(float *)(param_7 + (ulong)(uVar18 + 1) * 8 + 4)) && (fVar20 <= param_1))
        goto joined_r0x0208e9f0;
        uVar10 = uVar18;
        if ((int)uVar18 < (int)(param_8 - 2)) {
          uVar10 = uVar18 + 1;
        }
        uVar12 = uVar18 - 1;
        bVar7 = (int)uVar18 < (int)(param_8 - 2);
        uVar18 = uVar10;
        if (param_1 < fVar20 && bVar7) {
          uVar18 = uVar12;
        }
        fVar20 = *(float *)(param_7 + (ulong)uVar18 * 8 + 4);
        if (param_1 < *(float *)(param_7 + (ulong)(uVar18 + 1) * 8 + 4)) goto code_r0x0208e958;
      }
    }
    else {
code_r0x0208e958:
      if (fVar20 <= param_1) goto joined_r0x0208e9f0;
    }
    uVar10 = 0;
    if (fVar20 <= param_1) {
      uVar10 = param_8;
    }
    iVar21 = uVar10 + uVar18;
    if (1 < iVar21) {
      uVar10 = uVar18;
      if (fVar20 <= param_1) {
        uVar10 = param_8;
      }
      uVar12 = 0;
      if (fVar20 <= param_1) {
        uVar12 = uVar18;
      }
      do {
        if (iVar21 < 0) {
          iVar21 = iVar21 + 1;
        }
        uVar38 = iVar21 >> 1;
        uVar18 = uVar4;
        if (((int)uVar4 <= (int)uVar38) ||
           ((fVar20 = *(float *)(param_7 + (ulong)uVar38 * 8 + 4),
            param_1 < *(float *)(param_7 + (ulong)(uVar38 + 1) * 8 + 4) &&
            (uVar18 = uVar38, fVar20 <= param_1)))) goto joined_r0x0208e9f0;
        uVar18 = uVar38;
        if (fVar20 <= param_1) {
          uVar18 = uVar10;
          uVar12 = uVar38;
        }
        iVar21 = uVar18 + uVar12;
        uVar10 = uVar18;
      } while (1 < iVar21);
    }
    uVar18 = 0;
joined_r0x0208e9f0:
    if (param_4 == 0) {
      return;
    }
    iStack_74 = 0;
    iStack_78 = 0;
    uVar17 = 0;
    do {
      if (*(int *)(param_3 + uVar17 * 4) != 0) {
        iStack_78 = iStack_78 + 1;
        iStack_74 = iStack_78;
      }
      uVar17 = uVar17 + 1;
    } while (param_4 != uVar17);
    if (iStack_78 == 0) {
      return;
    }
    bool Aska::AafHandler::Function_UpdateKeyFrameData_All<0u>(unsigned int*, unsigned int&, unsigned int*, unsigned int&, Aska::AafControllerInfo*, unsigned int, unsigned int, Aska::FrameSortDataForSearchOld*, unsigned int, int, int, bool)(param_3,&iStack_74,param_2,&iStack_78,param_5,param_6,param_8,param_7,uVar18,0,
                    0xffffffff,0);
    if (iStack_78 == 0) {
      return;
    }
    uVar17 = bool Aska::AafHandler::Function_UpdateKeyFrameData_All<1u>(unsigned int*, unsigned int&, unsigned int*, unsigned int&, Aska::AafControllerInfo*, unsigned int, unsigned int, Aska::FrameSortDataForSearchOld*, unsigned int, int, int, bool)(param_3,&iStack_74,param_2,&iStack_78,param_5,param_6,param_8,param_7,
                             uVar18,1,1,0);
    if ((uVar17 & 1) != 0) {
      return;
    }
    bool Aska::AafHandler::Function_UpdateKeyFrameData_All<2u>(unsigned int*, unsigned int&, unsigned int*, unsigned int&, Aska::AafControllerInfo*, unsigned int, unsigned int, Aska::FrameSortDataForSearchOld*, unsigned int, int, int, bool)(param_3,&iStack_74,param_2,&iStack_78,param_5,param_6,param_8,param_7,uVar18,0,
                    0xffffffff,0);
    return;
  }
  if (param_4 == 0) {
    return;
  }
  if (param_4 < 8) {
    lVar11 = 0;
code_r0x0208eb3c:
    iVar21 = 0;
  }
  else {
    lVar11 = (ulong)param_4 - (ulong)(param_4 & 7);
    if (lVar11 == 0) goto code_r0x0208eb3c;
    puVar14 = (undefined8 *)(param_2 + 0x10);
    iVar21 = 0;
    iVar22 = 0;
    iVar23 = 0;
    iVar24 = 0;
    iVar25 = 0;
    iVar26 = 0;
    iVar27 = 0;
    iVar28 = 0;
    lVar8 = lVar11;
    do {
      puVar1 = puVar14 + -2;
      puVar5 = puVar14 + -1;
      puVar6 = puVar14 + 1;
      uVar34 = *puVar14;
      lVar8 = lVar8 + -8;
      puVar14 = puVar14 + 4;
      iVar29 = -(uint)((int)*puVar1 == 0);
      iVar30 = -(uint)((int)((ulong)*puVar1 >> 0x20) == 0);
      iVar31 = -(uint)((int)*puVar5 == 0);
      iVar32 = -(uint)((int)((ulong)*puVar5 >> 0x20) == 0);
      iVar33 = -(uint)((int)uVar34 == 0);
      iVar35 = -(uint)((int)((ulong)uVar34 >> 0x20) == 0);
      iVar36 = -(uint)((int)*puVar6 == 0);
      iVar37 = -(uint)((int)((ulong)*puVar6 >> 0x20) == 0);
      iVar29 = CONCAT13(~(byte)((uint)iVar29 >> 0x18),
                        CONCAT12(~(byte)((uint)iVar29 >> 0x10),
                                 CONCAT11(~(byte)((uint)iVar29 >> 8),~(byte)iVar29)));
      iVar31 = CONCAT13(~(byte)((uint)iVar31 >> 0x18),
                        CONCAT12(~(byte)((uint)iVar31 >> 0x10),
                                 CONCAT11(~(byte)((uint)iVar31 >> 8),~(byte)iVar31)));
      iVar33 = CONCAT13(~(byte)((uint)iVar33 >> 0x18),
                        CONCAT12(~(byte)((uint)iVar33 >> 0x10),
                                 CONCAT11(~(byte)((uint)iVar33 >> 8),~(byte)iVar33)));
      iVar36 = CONCAT13(~(byte)((uint)iVar36 >> 0x18),
                        CONCAT12(~(byte)((uint)iVar36 >> 0x10),
                                 CONCAT11(~(byte)((uint)iVar36 >> 8),~(byte)iVar36)));
      iVar21 = iVar21 - iVar29;
      iVar22 = iVar22 - (int)(CONCAT17(~(byte)((uint)iVar30 >> 0x18),
                                       CONCAT16(~(byte)((uint)iVar30 >> 0x10),
                                                CONCAT15(~(byte)((uint)iVar30 >> 8),
                                                         CONCAT14(~(byte)iVar30,iVar29)))) >> 0x20);
      iVar23 = iVar23 - iVar31;
      iVar24 = iVar24 - (int)(CONCAT17(~(byte)((uint)iVar32 >> 0x18),
                                       CONCAT16(~(byte)((uint)iVar32 >> 0x10),
                                                CONCAT15(~(byte)((uint)iVar32 >> 8),
                                                         CONCAT14(~(byte)iVar32,iVar31)))) >> 0x20);
      iVar25 = iVar25 - iVar33;
      iVar26 = iVar26 - (int)(CONCAT17(~(byte)((uint)iVar35 >> 0x18),
                                       CONCAT16(~(byte)((uint)iVar35 >> 0x10),
                                                CONCAT15(~(byte)((uint)iVar35 >> 8),
                                                         CONCAT14(~(byte)iVar35,iVar33)))) >> 0x20);
      iVar27 = iVar27 - iVar36;
      iVar28 = iVar28 - (int)(CONCAT17(~(byte)((uint)iVar37 >> 0x18),
                                       CONCAT16(~(byte)((uint)iVar37 >> 0x10),
                                                CONCAT15(~(byte)((uint)iVar37 >> 8),
                                                         CONCAT14(~(byte)iVar37,iVar36)))) >> 0x20);
    } while (lVar8 != 0);
    iVar21 = iVar25 + iVar21 + iVar26 + iVar22 + iVar27 + iVar23 + iVar28 + iVar24;
    if ((param_4 & 7) == 0) goto code_r0x0208eb5c;
  }
  lVar8 = (ulong)param_4 - lVar11;
  piVar13 = (int *)(param_2 + lVar11 * 4);
  do {
    lVar8 = lVar8 + -1;
    if (*piVar13 != 0) {
      iVar21 = iVar21 + 1;
    }
    piVar13 = piVar13 + 1;
  } while (lVar8 != 0);
code_r0x0208eb5c:
  if ((iVar21 != 0) && (0 < param_6)) {
    uVar17 = 0;
    do {
      uVar19 = uVar17 >> 5 & 0x7ffffff;
      uVar18 = *(uint *)(param_2 + uVar19 * 4);
      uVar4 = 1 << (ulong)((uint)uVar17 & 0x1f);
      if ((uVar18 & uVar4) != 0) {
        plVar16 = *(long **)(param_5 + uVar17 * 0x30 + 8);
        if (plVar16 != (long *)0x0) {
          lVar11 = param_5 + uVar17 * 0x30;
          puVar9 = (uint *)(lVar11 + 0x28);
          uVar18 = *puVar9;
          iVar22 = *(int *)(*(long *)(param_5 + uVar17 * 0x30 + 0x18) + 0x14);
          uVar10 = iVar22 - 2;
          if (iVar22 == 1) {
            uVar10 = 0;
          }
          while( true ) {
            while( true ) {
              puVar2 = (uint *)(*(long *)(lVar11 + 0x20) + (ulong)uVar18 * 8);
              puVar3 = puVar2 + 2;
              puVar15 = puVar3;
              if (param_1 < (float)puVar2[1]) break;
              uVar12 = uVar10;
              if (((uVar18 == uVar10) || (puVar15 = puVar2, uVar12 = uVar18, uVar10 <= uVar18)) ||
                 (puVar15 = puVar3, param_1 < (float)puVar2[3])) goto code_r0x0208ec28;
              uVar18 = uVar18 + 1;
            }
            if (uVar18 == 0) break;
            uVar18 = uVar18 - 1;
          }
          uVar12 = 0;
code_r0x0208ec28:
          uVar18 = *puVar2;
          uVar10 = *puVar15;
          uVar38 = puVar15[1];
          *puVar9 = uVar12;
          lVar11 = param_5 + uVar17 * 0x30;
          *(byte *)(lVar11 + 0x2e) = *(byte *)(lVar11 + 0x2e) & 0xef;
          (**(code **)(*plVar16 + 0xd8))(plVar16,0,(ulong)uVar18 + (long)puVar2);
          (**(code **)(*plVar16 + 0xd8))(uVar38,plVar16,1,(ulong)uVar10 + (long)puVar15);
          (**(code **)(*plVar16 + 0x1c8))(plVar16);
          uVar18 = *(uint *)(param_2 + uVar19 * 4);
        }
        uVar18 = uVar18 & (uVar4 ^ 0xffffffff);
        *(uint *)(param_2 + uVar19 * 4) = uVar18;
        if ((uVar18 == 0) && (iVar21 = iVar21 + -1, iVar21 == 0)) {
          return;
        }
      }
      uVar17 = uVar17 + 1;
    } while ((long)uVar17 < (long)param_6);
  }
  return;
}

// ==== bool Aska::AafHandler::Function_UpdateKeyFrameData_All<0u>(unsigned int*, unsigned int&, unsigned int*, unsigned int&, Aska::AafControllerInfo*, unsigned int, unsigned int, Aska::FrameSortDataForSearchOld*, unsigned int, int, int, bool)
// vaddr 0x1f8ecec | ghidra 0x208ecec | size 476 | symbol _ZN4Aska10AafHandler31Function_UpdateKeyFrameData_AllILj0EEEbPjRjS2_S3_PNS_17AafControllerInfoEjjPNS_25FrameSortDataForSearchOldEjiib | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska10AafHandler31Function_UpdateKeyFrameData_AllILj0EEEbPjRjS2_S3_PNS_17AafControllerInfoEjjPNS_25FrameSortDataForSearchOldEjiib
          (long param_1,int *param_2,long param_3,int *param_4,long param_5,undefined8 param_6,
          int param_7,long param_8,int param_9,int param_10,int param_11)

{
  uint *puVar1;
  int *piVar2;
  long lVar3;
  ushort uVar4;
  uint uVar5;
  ulong uVar6;
  int iVar7;
  long lVar8;
  long *plVar9;
  int iVar10;
  long lVar11;
  int *piVar12;
  uint uVar13;
  
  if (param_11 < 0) {
    param_7 = -1;
  }
  if (param_10 + param_9 != param_7) {
    lVar8 = (long)(param_10 + param_9);
    do {
      puVar1 = (uint *)(param_8 + lVar8 * 8);
      piVar2 = (int *)((ulong)*puVar1 + (long)puVar1);
      iVar10 = *piVar2;
      if (iVar10 != 0) {
        piVar12 = piVar2 + 2;
        do {
          Hint_Prefetch(piVar12,0,2,0);
          uVar4 = *(ushort *)(piVar12 + -1);
          uVar6 = (ulong)(uVar4 >> 5);
          uVar5 = 1 << ((ulong)uVar4 & 0x1f);
          if ((uVar5 & *(uint *)(param_1 + uVar6 * 4)) != 0) {
            lVar11 = param_5 + (ulong)uVar4 * 0x30;
            plVar9 = *(long **)(lVar11 + 8);
            uVar4 = *(ushort *)((long)piVar12 + -2);
            uVar13 = puVar1[1];
            *(int *)(lVar11 + 0x28) = (int)lVar8;
            *(byte *)(lVar11 + 0x2e) = *(byte *)(lVar11 + 0x2e) & 0xef;
            lVar3 = (long)piVar2 + (ulong)uVar4;
            (**(code **)(*plVar9 + 0xd8))(uVar13,plVar9,0,lVar3);
            if ((*(byte *)(lVar11 + 0x2e) >> 6 & 1) != 0) {
              (**(code **)(*plVar9 + 0xe0))(uVar13,plVar9,1,lVar3);
              uVar13 = *(uint *)(param_3 + uVar6 * 4) & (uVar5 ^ 0xffffffff);
              *(uint *)(param_3 + uVar6 * 4) = uVar13;
              if (uVar13 == 0) {
                *param_4 = *param_4 + -1;
              }
            }
            (**(code **)(*plVar9 + 0x1c8))(plVar9);
            uVar5 = *(uint *)(param_1 + uVar6 * 4) & ~uVar5;
            *(uint *)(param_1 + uVar6 * 4) = uVar5;
            iVar7 = *param_2;
            if (uVar5 == 0) {
              iVar7 = iVar7 + -1;
              *param_2 = iVar7;
            }
            if (iVar7 == 0) {
              return 1;
            }
          }
          iVar10 = iVar10 + -1;
          piVar12 = piVar12 + 1;
        } while (iVar10 != 0);
      }
      lVar8 = lVar8 + param_11;
    } while (param_7 != (int)lVar8);
  }
  return 0;
}

// ==== bool Aska::AafHandler::Function_UpdateKeyFrameData_All<1u>(unsigned int*, unsigned int&, unsigned int*, unsigned int&, Aska::AafControllerInfo*, unsigned int, unsigned int, Aska::FrameSortDataForSearchOld*, unsigned int, int, int, bool)
// vaddr 0x1f8eec8 | ghidra 0x208eec8 | size 476 | symbol _ZN4Aska10AafHandler31Function_UpdateKeyFrameData_AllILj1EEEbPjRjS2_S3_PNS_17AafControllerInfoEjjPNS_25FrameSortDataForSearchOldEjiib | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska10AafHandler31Function_UpdateKeyFrameData_AllILj1EEEbPjRjS2_S3_PNS_17AafControllerInfoEjjPNS_25FrameSortDataForSearchOldEjiib
          (long param_1,undefined8 param_2,long param_3,int *param_4,long param_5,undefined8 param_6
          ,int param_7,long param_8,int param_9,int param_10,int param_11)

{
  uint *puVar1;
  int *piVar2;
  long lVar3;
  uint uVar4;
  ulong uVar5;
  int iVar6;
  ulong uVar7;
  long lVar8;
  long lVar9;
  int iVar10;
  long *plVar11;
  int *piVar12;
  uint uVar13;
  
  if (param_11 < 0) {
    param_7 = -1;
  }
  if (param_10 + param_9 != param_7) {
    lVar9 = (long)(param_10 + param_9);
    do {
      puVar1 = (uint *)(param_8 + lVar9 * 8);
      piVar2 = (int *)((ulong)*puVar1 + (long)puVar1);
      iVar10 = *piVar2;
      if (iVar10 != 0) {
        piVar12 = piVar2 + 2;
        do {
          Hint_Prefetch(piVar12,0,2,0);
          uVar7 = (ulong)*(ushort *)(piVar12 + -1);
          uVar5 = (ulong)(*(ushort *)(piVar12 + -1) >> 5);
          uVar4 = 1 << (uVar7 & 0x1f);
          if ((uVar4 & *(uint *)(param_3 + uVar5 * 4)) != 0) {
            plVar11 = *(long **)(param_5 + uVar7 * 0x30 + 8);
            uVar13 = puVar1[1];
            lVar3 = (long)piVar2 + (ulong)*(ushort *)((long)piVar12 + -2);
            if ((*(uint *)(param_1 + uVar5 * 4) & uVar4) != 0) {
              lVar8 = param_5 + uVar7 * 0x30;
              *(int *)(lVar8 + 0x28) = (int)lVar9;
              *(byte *)(lVar8 + 0x2e) = *(byte *)(lVar8 + 0x2e) & 0xef;
              (**(code **)(*plVar11 + 0xd8))(uVar13,plVar11,0,lVar3);
              *(uint *)(param_1 + uVar5 * 4) = *(uint *)(param_1 + uVar5 * 4) & (uVar4 ^ 0xffffffff)
              ;
            }
            (**(code **)(*plVar11 + 0xd8))(uVar13,plVar11,1,lVar3);
            (**(code **)(*plVar11 + 0x1c8))(plVar11);
            uVar4 = *(uint *)(param_3 + uVar5 * 4) & ~uVar4;
            *(uint *)(param_3 + uVar5 * 4) = uVar4;
            iVar6 = *param_4;
            if (uVar4 == 0) {
              iVar6 = iVar6 + -1;
              *param_4 = iVar6;
            }
            if (iVar6 == 0) {
              return 1;
            }
          }
          iVar10 = iVar10 + -1;
          piVar12 = piVar12 + 1;
        } while (iVar10 != 0);
      }
      lVar9 = lVar9 + param_11;
    } while (param_7 != (int)lVar9);
  }
  return 0;
}

// ==== bool Aska::AafHandler::Function_UpdateKeyFrameData_All<2u>(unsigned int*, unsigned int&, unsigned int*, unsigned int&, Aska::AafControllerInfo*, unsigned int, unsigned int, Aska::FrameSortDataForSearchOld*, unsigned int, int, int, bool)
// vaddr 0x1f8f0a4 | ghidra 0x208f0a4 | size 464 | symbol _ZN4Aska10AafHandler31Function_UpdateKeyFrameData_AllILj2EEEbPjRjS2_S3_PNS_17AafControllerInfoEjjPNS_25FrameSortDataForSearchOldEjiib | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska10AafHandler31Function_UpdateKeyFrameData_AllILj2EEEbPjRjS2_S3_PNS_17AafControllerInfoEjjPNS_25FrameSortDataForSearchOldEjiib
          (undefined8 param_1,undefined8 param_2,long param_3,int *param_4,long param_5,
          undefined8 param_6,int param_7,long param_8,int param_9,int param_10,int param_11)

{
  float *pfVar1;
  uint *puVar2;
  int *piVar3;
  int iVar4;
  ushort uVar5;
  uint uVar6;
  ulong uVar7;
  uint uVar8;
  long lVar9;
  long lVar10;
  int iVar11;
  long *plVar12;
  ulong uVar13;
  int *piVar14;
  float fVar15;
  float fVar16;
  
  if (param_11 < 0) {
    param_7 = -1;
  }
  if (param_10 + param_9 != param_7) {
    lVar10 = (long)(param_10 + param_9);
    do {
      puVar2 = (uint *)(param_8 + lVar10 * 8);
      piVar3 = (int *)((ulong)*puVar2 + (long)puVar2);
      iVar11 = *piVar3;
      if (iVar11 != 0) {
        pfVar1 = (float *)(puVar2 + 1);
        piVar14 = piVar3 + 2;
        do {
          Hint_Prefetch(piVar14,0,2,0);
          uVar13 = (ulong)*(ushort *)(piVar14 + -1);
          uVar7 = (ulong)(*(ushort *)(piVar14 + -1) >> 5);
          uVar8 = *(uint *)(param_3 + uVar7 * 4);
          uVar6 = 1 << (uVar13 & 0x1f);
          if ((uVar6 & uVar8) != 0) {
            plVar12 = *(long **)(param_5 + uVar13 * 0x30 + 8);
            if (plVar12 == (long *)0x0) {
code_r0x0208f1f8:
              uVar8 = uVar8 & (uVar6 ^ 0xffffffff);
              *(uint *)(param_3 + uVar7 * 4) = uVar8;
              if (uVar8 != 0) goto code_r0x0208f204;
              iVar4 = *param_4 + -1;
              *param_4 = iVar4;
            }
            else {
              uVar5 = *(ushort *)((long)piVar14 + -2);
              fVar16 = *pfVar1;
              fVar15 = (float)(**(code **)(*plVar12 + 0x1e0))(plVar12,0);
              if (*pfVar1 != fVar15) {
                (**(code **)(*plVar12 + 0xd8))(fVar16,plVar12,1,(long)piVar3 + (ulong)uVar5);
                if (*pfVar1 < fVar15) {
                  lVar9 = param_5 + uVar13 * 0x30;
                  *(int *)(lVar9 + 0x28) = (int)lVar10;
                  *(byte *)(lVar9 + 0x2e) = *(byte *)(lVar9 + 0x2e) & 0xef;
                  (**(code **)(*plVar12 + 0xe8))(plVar12);
                }
                (**(code **)(*plVar12 + 0x1c8))(plVar12);
                uVar8 = *(uint *)(param_3 + uVar7 * 4);
                goto code_r0x0208f1f8;
              }
code_r0x0208f204:
              iVar4 = *param_4;
            }
            if (iVar4 == 0) {
              return 1;
            }
          }
          iVar11 = iVar11 + -1;
          piVar14 = piVar14 + 1;
        } while (iVar11 != 0);
      }
      lVar10 = lVar10 + param_11;
    } while (param_7 != (int)lVar10);
  }
  return 0;
}

// ==== Aska::AafHandler::Function_GetChunkInfo(Aska::AafHandler const*, Aska::AafHeader const*, float&, unsigned int&, unsigned long&, Aska::AafFrameSortChunkInfo*&)
// vaddr 0x1f8f274 | ghidra 0x208f274 | size 152 | symbol _ZN4Aska10AafHandler21Function_GetChunkInfoEPKS0_PKNS_9AafHeaderERfRjRmRPNS_21AafFrameSortChunkInfoE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10AafHandler21Function_GetChunkInfoEPKS0_PKNS_9AafHeaderERfRjRmRPNS_21AafFrameSortChunkInfoE
               (long param_1,long param_2,float *param_3,uint *param_4,undefined8 *param_5,
               long *param_6)

{
  ushort uVar1;
  long lVar2;
  int iVar3;
  float fVar4;
  
  uVar1 = *(ushort *)(param_2 + 0xe);
  *param_4 = (uint)uVar1;
  if ((uVar1 == 0) || (lVar2 = *(long *)(param_1 + 0x118), lVar2 == 0)) {
    *param_5 = 0;
    *param_6 = 0;
    return;
  }
  fVar4 = *param_3 / *(float *)(param_2 + 0x2c);
  if (0.0 <= fVar4) {
    iVar3 = (int)fVar4;
    if (iVar3 < (int)(uint)uVar1) {
      fVar4 = *(float *)(param_2 + 0x10);
      if (*param_3 <= fVar4) goto code_r0x0208f2e8;
    }
    else {
      fVar4 = *(float *)(param_2 + 0x10);
    }
    *param_3 = fVar4;
    iVar3 = *param_4 - 1;
  }
  else {
    iVar3 = 0;
    *param_3 = 0.0;
  }
code_r0x0208f2e8:
  *param_5 = *(undefined8 *)(lVar2 + (long)iVar3 * 8);
  *param_6 = *(long *)(param_1 + 0x10) + (ulong)*(uint *)(param_2 + 0x28) + (long)iVar3 * 0xc;
  return;
}

// ==== Aska::AafHandler::Instantiate()
// vaddr 0x1f95324 | ghidra 0x2095324 | size 140 | symbol _ZN4Aska10AafHandler11InstantiateEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10AafHandler11InstantiateEv(void)

{
  undefined *puVar1;
  long *plVar2;
  
  if (*(long *)PTR__ZN4Aska10AafHandler16m_pMemoryManagerE_02cb6d40 == 0) {
    plVar2 = (long *)operator new(unsigned long)(0x120);
  }
  else {
    plVar2 = (long *)Aska::MemoryManager::Malloc(unsigned long)(*(long *)PTR__ZN4Aska10AafHandler16m_pMemoryManagerE_02cb6d40,
                                     0x120);
    if (plVar2 == (long *)0x0) {
      return;
    }
  }
  *(undefined1 *)((long)plVar2 + 0xfa) = 1;
  puVar1 = PTR__ZTVN4Aska10AafHandlerE_02cbc038;
  plVar2[8] = 0;
  plVar2[0x10] = 0;
  plVar2[0x14] = 0;
  *(undefined4 *)(plVar2 + 0x15) = 0;
  plVar2[0x16] = 0;
  plVar2[0x1c] = 0;
  *(undefined4 *)((long)plVar2 + 0xf4) = 0;
  plVar2[6] = 0;
  *(undefined4 *)(plVar2 + 7) = 0;
  *(undefined2 *)(plVar2 + 0x1f) = 0;
  plVar2[3] = 0;
  plVar2[2] = 0;
  plVar2[5] = 0;
  plVar2[4] = 0;
  plVar2[0xb] = 0;
  plVar2[10] = 0;
  plVar2[0xd] = 0;
  plVar2[0xc] = 0;
  *plVar2 = (long)(puVar1 + 0x10);
  plVar2[1] = 0x2000000000;
  plVar2[0x21] = 0;
  plVar2[0x20] = 0;
  plVar2[0x23] = 0;
  plVar2[0x22] = 0;
  return;
}

// ==== Aska::AafHandler::operator new(unsigned long, std::nothrow_t const&)
// vaddr 0x1f953b0 | ghidra 0x20953b0 | size 40 | symbol _ZN4Aska10AafHandlernwEmRKSt9nothrow_t | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10AafHandlernwEmRKSt9nothrow_t(undefined8 param_1)

{
  if (*(long *)PTR__ZN4Aska10AafHandler16m_pMemoryManagerE_02cb6d40 != 0) {
    (*(code *)PTR__ZN4Aska13MemoryManager6MallocEm_02ca1310)
              (*(long *)PTR__ZN4Aska10AafHandler16m_pMemoryManagerE_02cb6d40,param_1);
    return;
  }
  (*(code *)PTR__Znwm_02ca3250)(param_1);
  return;
}

// ==== Aska::AafHandler::DeleteThis()
// vaddr 0x1f953d8 | ghidra 0x20953d8 | size 20 | symbol _ZN4Aska10AafHandler10DeleteThisEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10AafHandler10DeleteThisEv(long *param_1)

{
  if (param_1 != (long *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x020953e4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(*param_1 + 8))();
    return;
  }
  return;
}

// ==== Aska::AafHandler::DecodeData(void*)
// vaddr 0x1f953ec | ghidra 0x20953ec | size 368 | symbol _ZN4Aska10AafHandler10DecodeDataEPv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska10AafHandler10DecodeDataEPv(long param_1,undefined8 param_2)

{
  uint uVar1;
  long lVar2;
  ulong uVar3;
  undefined8 uVar4;
  uint uVar5;
  undefined *puStack_d0;
  undefined1 *puStack_c8;
  undefined1 auStack_c0 [104];
  undefined4 auStack_58 [4];
  long lStack_48;
  undefined4 uStack_3c;
  
  if ((*(byte *)(param_1 + 0xc) >> 4 & 1) != 0) {
    Aska::AafHandler::DetachObject()(param_1);
  }
  *(undefined2 *)(param_1 + 0xf4) = 0;
  *(undefined4 *)(param_1 + 0xa8) = 0;
  *(undefined4 *)(param_1 + 0x48) = 0;
  *(undefined8 *)(param_1 + 0x98) = 0;
  *(undefined8 *)(param_1 + 0x40) = 0;
  *(undefined8 *)(param_1 + 0x38) = 0;
  *(undefined8 *)(param_1 + 0x90) = 0;
  *(undefined8 *)(param_1 + 0x88) = 0;
  *(undefined8 *)(param_1 + 0x80) = 0;
  *(undefined8 *)(param_1 + 0x78) = 0;
  *(undefined8 *)(param_1 + 0xe0) = 0;
  *(undefined8 *)(param_1 + 200) = 0;
  *(undefined8 *)(param_1 + 0xc0) = 0;
  *(undefined8 *)(param_1 + 0xd8) = 0;
  *(undefined8 *)(param_1 + 0xd0) = 0;
  *(undefined8 *)(param_1 + 0xb8) = 0;
  *(undefined8 *)(param_1 + 0xb0) = 0;
  if (*(long *)(param_1 + 0x50) != 0) {
    operator delete[](void*)();
    *(undefined8 *)(param_1 + 0x50) = 0;
  }
  uVar1 = *(uint *)(param_1 + 0xc);
  *(undefined8 *)(param_1 + 0x20) = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  *(undefined8 *)(param_1 + 0x18) = 0;
  uVar5 = uVar1 & 0xfffffe34;
  *(uint *)(param_1 + 0xc) = uVar5;
  *(undefined1 *)(param_1 + 0xf7) = 0;
  if (((uVar1 >> 2 & 1) == 0) && (*(long *)(param_1 + 0x10) != 0)) {
    operator delete[](void*)();
    uVar5 = *(uint *)(param_1 + 0xc);
    *(undefined8 *)(param_1 + 0x10) = 0;
  }
  *(uint *)(param_1 + 0xc) = uVar5 & 0xfffffffa;
  lVar2 = Aska::Decompress::AllocDecodeBuffer(Aska::COMPRESSHEADER const*, int, unsigned int)(param_2,0,0x10);
  uVar4 = 0;
  if (lVar2 != 0) {
    auStack_58[0] = 4;
    uStack_3c = 0;
    lStack_48 = lVar2;
    Aska::Event::Event()(auStack_c0);
    uVar3 = Aska::Event::Create(bool, bool)(auStack_c0,1,0);
    if ((uVar3 & 1) == 0) {
      Aska::Decompress::Decode(Aska::COMPRESSHEADER*, unsigned char*, int)(param_2,lVar2,0);
    }
    else {
      puStack_d0 = PTR__ZTVN4Aska11EventNotifyE_02cb7e68 + 0x10;
      puStack_c8 = auStack_c0;
      Aska::DecompressQueue::Add(void const*, Aska::DecompressInfo*, int, Aska::INotify*, Aska::IMemoryManager*, Aska::IMemoryManager*, Aska::IMemoryManager*, Aska::IMemoryManager*)(*(undefined8 *)PTR__ZN4Aska6Global18m_pDecompressQueueE_02cc0f20,param_2,
                      auStack_58,0,&puStack_d0,0,0,0,0);
      Aska::Event::Wait(unsigned int) const(auStack_c0,0);
    }
    *(long *)(param_1 + 0x10) = lVar2;
    Aska::Event::Exit()(auStack_c0);
    uVar4 = 1;
  }
  return uVar4;
}

// ==== Aska::AafHandler::DeleteControllers()
// vaddr 0x1f9555c | ghidra 0x209555c | size 120 | symbol _ZN4Aska10AafHandler17DeleteControllersEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10AafHandler17DeleteControllersEv(long param_1)

{
  if ((*(byte *)(param_1 + 0xc) >> 4 & 1) != 0) {
    Aska::AafHandler::DetachObject()(param_1);
  }
  *(undefined2 *)(param_1 + 0xf4) = 0;
  *(undefined4 *)(param_1 + 0xa8) = 0;
  *(undefined4 *)(param_1 + 0x48) = 0;
  *(undefined8 *)(param_1 + 0x98) = 0;
  *(undefined8 *)(param_1 + 0x40) = 0;
  *(undefined8 *)(param_1 + 0x38) = 0;
  *(undefined8 *)(param_1 + 0x90) = 0;
  *(undefined8 *)(param_1 + 0x88) = 0;
  *(undefined8 *)(param_1 + 0x80) = 0;
  *(undefined8 *)(param_1 + 0x78) = 0;
  *(undefined8 *)(param_1 + 0xe0) = 0;
  *(undefined8 *)(param_1 + 200) = 0;
  *(undefined8 *)(param_1 + 0xc0) = 0;
  *(undefined8 *)(param_1 + 0xd8) = 0;
  *(undefined8 *)(param_1 + 0xd0) = 0;
  *(undefined8 *)(param_1 + 0xb8) = 0;
  *(undefined8 *)(param_1 + 0xb0) = 0;
  if (*(long *)(param_1 + 0x50) != 0) {
    operator delete[](void*)();
    *(undefined8 *)(param_1 + 0x50) = 0;
  }
  *(undefined8 *)(param_1 + 0x20) = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  *(undefined8 *)(param_1 + 0x18) = 0;
  *(uint *)(param_1 + 0xc) = *(uint *)(param_1 + 0xc) & 0xfffffe34;
  *(undefined1 *)(param_1 + 0xf7) = 0;
  return;
}

// ==== Aska::AafHandler::AttachResource(Aska::ResourceManager*)
// vaddr 0x1f955d4 | ghidra 0x20955d4 | size 184 | symbol _ZN4Aska10AafHandler14AttachResourceEPNS_15ResourceManagerE | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska10AafHandler14AttachResourceEPNS_15ResourceManagerE(long param_1,long param_2)

{
  long lVar1;
  undefined8 uVar2;
  
  if (param_2 == 0) {
    if ((*(uint *)(param_1 + 0xc) >> 1 & 1) == 0) {
      uVar2 = 0;
    }
    else {
      if ((*(uint *)(param_1 + 0xc) >> 4 & 1) != 0) {
        Aska::AafHandler::DetachObject()(param_1);
      }
      *(undefined2 *)(param_1 + 0xf4) = 0;
      *(undefined4 *)(param_1 + 0xa8) = 0;
      *(undefined4 *)(param_1 + 0x48) = 0;
      *(undefined8 *)(param_1 + 0x98) = 0;
      *(undefined8 *)(param_1 + 0x40) = 0;
      *(undefined8 *)(param_1 + 0x38) = 0;
      *(undefined8 *)(param_1 + 0x90) = 0;
      *(undefined8 *)(param_1 + 0x88) = 0;
      *(undefined8 *)(param_1 + 0x80) = 0;
      *(undefined8 *)(param_1 + 0x78) = 0;
      *(undefined8 *)(param_1 + 0xe0) = 0;
      *(undefined8 *)(param_1 + 200) = 0;
      *(undefined8 *)(param_1 + 0xc0) = 0;
      *(undefined8 *)(param_1 + 0xd8) = 0;
      *(undefined8 *)(param_1 + 0xd0) = 0;
      *(undefined8 *)(param_1 + 0xb8) = 0;
      *(undefined8 *)(param_1 + 0xb0) = 0;
      if (*(long *)(param_1 + 0x50) != 0) {
        operator delete[](void*)();
        *(undefined8 *)(param_1 + 0x50) = 0;
      }
      uVar2 = 0;
      *(undefined8 *)(param_1 + 0x20) = 0;
      *(undefined8 *)(param_1 + 0x28) = 0;
      *(undefined8 *)(param_1 + 0x18) = 0;
      *(uint *)(param_1 + 0xc) = *(uint *)(param_1 + 0xc) & 0xfffffe34;
      *(undefined1 *)(param_1 + 0xf7) = 0;
    }
  }
  else {
    lVar1 = Aska::ResourceManager::Lock()(param_2);
    *(long *)(param_1 + 0x10) = lVar1;
    uVar2 = 0;
    if (lVar1 != 0) {
      Aska::ResourceManager::Unlock()(param_2);
      uVar2 = 1;
    }
  }
  return uVar2;
}

// ==== Aska::AafHandler::GetTargetName(Aska::AafTargetHeaderBase const*) const
// vaddr 0x1f9568c | ghidra 0x209568c | size 64 | symbol _ZNK4Aska10AafHandler13GetTargetNameEPKNS_19AafTargetHeaderBaseE | lib libSOA-3.7.0.so | 2026-10-04
byte * _ZNK4Aska10AafHandler13GetTargetNameEPKNS_19AafTargetHeaderBaseE(long param_1,byte *param_2)

{
  byte *pbVar1;
  uint *puVar2;
  
  if ((*param_2 >> 2 & 1) == 0) {
    return param_2 + 8;
  }
  puVar2 = *(uint **)(param_1 + 0x18);
  if (puVar2 != (uint *)0x0) {
    pbVar1 = (byte *)((long)puVar2 + (ulong)(*(uint *)(param_2 + 8) << 5) + 4);
    if (*puVar2 <= *(uint *)(param_2 + 8)) {
      pbVar1 = (byte *)0x0;
    }
    return pbVar1;
  }
  return (byte *)0x0;
}

// ==== Aska::AafHandler::ResolveConstraints(float)
// vaddr 0x1f956cc | ghidra 0x20956cc | size 220 | symbol _ZN4Aska10AafHandler18ResolveConstraintsEf | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10AafHandler18ResolveConstraintsEf(undefined8 param_1,long param_2)

{
  ulong uVar1;
  long *plVar2;
  byte *pbVar3;
  long lVar4;
  undefined8 uStack_60;
  undefined8 uStack_58;
  undefined1 auStack_40 [16];
  
  if (*(uint *)(param_2 + 0x44) != 0) {
    lVar4 = (ulong)*(uint *)(param_2 + 0x44) * 0x30;
    pbVar3 = (byte *)(*(long *)(param_2 + 0x98) + 0x2e);
    do {
      uStack_58 = *(undefined8 *)
                   (*(long *)(param_2 + 0x78) + (ulong)*(ushort *)(pbVar3 + -2) * 0x10 + 8);
      if ((*pbVar3 & 7) == 0) {
        plVar2 = *(long **)(pbVar3 + -0x26);
        uVar1 = (**(code **)(*plVar2 + 0x1d8))(plVar2);
        if ((uVar1 & 1) == 0) {
          (**(code **)(*plVar2 + 0x60))(param_1,plVar2,auStack_40);
        }
        uVar1 = (**(code **)(*plVar2 + 0x1d8))(plVar2);
        if ((uVar1 & 1) == 0) {
          uStack_60 = *(undefined8 *)(pbVar3 + -0x2e);
          (**(code **)(*plVar2 + 0x168))(plVar2,auStack_40,&uStack_60);
        }
      }
      lVar4 = lVar4 + -0x30;
      pbVar3 = pbVar3 + 0x30;
    } while (lVar4 != 0);
  }
  return;
}

// ==== Aska::AafHandler::AddAutoControllerTask(Aska::TaskManager*, float*)
// vaddr 0x1f957a8 | ghidra 0x20957a8 | size 156 | symbol _ZN4Aska10AafHandler21AddAutoControllerTaskEPNS_11TaskManagerEPf | lib libSOA-3.7.0.so | 2026-10-04
bool _ZN4Aska10AafHandler21AddAutoControllerTaskEPNS_11TaskManagerEPf
               (long param_1,undefined8 param_2,long param_3)

{
  undefined *puVar1;
  undefined4 uVar2;
  long *plVar3;
  code *pcVar4;
  
  plVar3 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x38,PTR__ZSt7nothrow_02cb9a80);
  puVar1 = PTR__ZTVN4Aska4TaskE_02cbe020;
  if (plVar3 == (long *)0x0) {
    *(undefined8 *)(param_1 + 0xa0) = 0;
  }
  else {
    plVar3[2] = 0;
    plVar3[3] = 0;
    *(undefined2 *)((long)plVar3 + 0x24) = 0;
    pcVar4 = *(code **)(puVar1 + 0x68);
    *plVar3 = (long)(puVar1 + 0x10);
    plVar3[1] = 0;
    *(undefined1 *)((long)plVar3 + 0x26) = 0;
    uVar2 = (*pcVar4)(plVar3);
    *(undefined4 *)(plVar3 + 4) = uVar2;
    *plVar3 = (long)(PTR__ZTVN4Aska14AafAutoRunTaskE_02cc01e0 + 0x10);
    *(long **)(param_1 + 0xa0) = plVar3;
    plVar3[5] = param_1;
    plVar3[6] = param_3;
    Aska::TaskManager::Add(Aska::Task*)(param_2,plVar3);
  }
  return plVar3 != (long *)0x0;
}

// ==== Aska::AafHandler::RemoveAutoControllerTask()
// vaddr 0x1f95844 | ghidra 0x2095844 | size 48 | symbol _ZN4Aska10AafHandler24RemoveAutoControllerTaskEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10AafHandler24RemoveAutoControllerTaskEv(long param_1)

{
  if (*(long *)(param_1 + 0xa0) != 0) {
    Aska::Task::Remove()();
    (**(code **)(**(long **)(param_1 + 0xa0) + 0x50))();
    *(undefined8 *)(param_1 + 0xa0) = 0;
  }
  return;
}

// ==== Aska::AafHandler::Clone(Aska::AsfHandler*, Aska::AafHandler*, Aska::CollisionHandler*, Aska::AsfTargetNameList*, bool)
// vaddr 0x1f95874 | ghidra 0x2095874 | size 268 | symbol _ZN4Aska10AafHandler5CloneEPNS_10AsfHandlerEPS0_PNS_16CollisionHandlerEPNS_17AsfTargetNameListEb | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska10AafHandler5CloneEPNS_10AsfHandlerEPS0_PNS_16CollisionHandlerEPNS_17AsfTargetNameListEb
          (long param_1,undefined8 param_2,long param_3,undefined8 param_4,undefined8 param_5,
          uint param_6)

{
  uint uVar1;
  undefined8 uVar2;
  
  if (*(long *)(param_3 + 0x80) != 0) {
    uVar1 = *(uint *)(param_1 + 0xc);
    uVar2 = *(undefined8 *)(param_3 + 0x20);
    if ((uVar1 & 0x18) != 0) {
      if ((uVar1 >> 4 & 1) != 0) {
        Aska::AafHandler::DetachObject()(param_1);
      }
      *(undefined2 *)(param_1 + 0xf4) = 0;
      *(undefined4 *)(param_1 + 0xa8) = 0;
      *(undefined4 *)(param_1 + 0x48) = 0;
      *(undefined8 *)(param_1 + 0x98) = 0;
      *(undefined8 *)(param_1 + 0x40) = 0;
      *(undefined8 *)(param_1 + 0x38) = 0;
      *(undefined8 *)(param_1 + 0x90) = 0;
      *(undefined8 *)(param_1 + 0x88) = 0;
      *(undefined8 *)(param_1 + 0x80) = 0;
      *(undefined8 *)(param_1 + 0x78) = 0;
      *(undefined8 *)(param_1 + 0xe0) = 0;
      *(undefined8 *)(param_1 + 200) = 0;
      *(undefined8 *)(param_1 + 0xc0) = 0;
      *(undefined8 *)(param_1 + 0xd8) = 0;
      *(undefined8 *)(param_1 + 0xd0) = 0;
      *(undefined8 *)(param_1 + 0xb8) = 0;
      *(undefined8 *)(param_1 + 0xb0) = 0;
      if (*(long *)(param_1 + 0x50) != 0) {
        operator delete[](void*)();
        *(undefined8 *)(param_1 + 0x50) = 0;
      }
      *(undefined8 *)(param_1 + 0x20) = 0;
      *(undefined8 *)(param_1 + 0x28) = 0;
      *(undefined8 *)(param_1 + 0x18) = 0;
      uVar1 = *(uint *)(param_1 + 0xc) & 0xfffffe34;
      *(uint *)(param_1 + 0xc) = uVar1;
      *(undefined1 *)(param_1 + 0xf7) = 0;
    }
    if (((uVar1 >> 2 & 1) == 0) && (*(long *)(param_1 + 0x10) != 0)) {
      operator delete[](void*)();
      uVar1 = *(uint *)(param_1 + 0xc);
      *(undefined8 *)(param_1 + 0x10) = 0;
    }
    *(uint *)(param_1 + 0xc) = uVar1 & 0xfffffffa | 4;
    *(undefined8 *)(param_1 + 0x10) = uVar2;
    uVar2 = (*(code *)
              PTR__ZN4Aska10AafHandler17CreateControllersEPNS_10AsfHandlerEPNS_16CollisionHandlerEPNS_17AsfTargetNameListEb_02cb3140
            )(param_1,param_2,param_4,param_5,param_6 & 1);
    return uVar2;
  }
  return 0;
}

// ==== Aska::AafHandler::CreateControllers(Aska::AsfHandler*, Aska::CollisionHandler*, Aska::AsfTargetNameList*, bool)
// vaddr 0x1f95980 | ghidra 0x2095980 | size 1236 | symbol _ZN4Aska10AafHandler17CreateControllersEPNS_10AsfHandlerEPNS_16CollisionHandlerEPNS_17AsfTargetNameListEb | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska10AafHandler17CreateControllersEPNS_10AsfHandlerEPNS_16CollisionHandlerEPNS_17AsfTargetNameListEb
          (long param_1,long param_2,undefined8 param_3,undefined8 param_4,byte param_5)

{
  ushort *puVar1;
  undefined8 uVar2;
  int iVar3;
  ulong uVar4;
  long lVar5;
  long lVar6;
  int *piVar7;
  uint uVar8;
  ulong uVar9;
  undefined8 *puVar10;
  uint *puVar11;
  ushort *puVar12;
  undefined8 *puVar13;
  long *plVar14;
  undefined8 uStack_90;
  undefined8 uStack_88;
  undefined8 uStack_80;
  long lStack_78;
  
  uVar8 = *(uint *)(param_1 + 0xc);
  if ((uVar8 & 1) == 0) {
    if (param_2 == 0) {
      return 0;
    }
    piVar7 = *(int **)(param_1 + 0x10);
    if (piVar7 == (int *)0x0) {
      return 0;
    }
    iVar3 = *piVar7;
    while (iVar3 != 0x41414620) {
      if (piVar7[3] == 0) {
        return 0;
      }
      piVar7 = (int *)((long)piVar7 + (ulong)(uint)piVar7[3]);
      iVar3 = *piVar7;
    }
    uVar4 = Aska::AafHandler::AttachAaf(void const*, Aska::AsfHandler*, Aska::CollisionHandler*, Aska::AsfTargetNameList*)(param_1,piVar7,param_2,param_3,param_4);
    if ((uVar4 & 1) == 0) {
      return 0;
    }
    uVar8 = *(uint *)(param_1 + 0xc) | 1;
    *(uint *)(param_1 + 0xc) = uVar8;
  }
  if ((uVar8 >> 4 & 1) != 0) {
    Aska::AafHandler::DetachObject()(param_1);
  }
  *(undefined1 *)(param_1 + 0xf7) = 0;
  if (param_2 == 0) {
    return 0;
  }
  uVar2 = *(undefined8 *)(param_1 + 0x20);
  lVar6 = *(long *)(param_1 + 0x28);
  *(long *)(param_1 + 0x30) = param_2;
  *(long *)(param_1 + 0x100) = param_2;
  if (*(long *)(param_1 + 0x58) != 0) {
    operator delete[](void*)();
    *(undefined8 *)(param_1 + 0x58) = 0;
  }
  if (*(long *)(param_1 + 0x60) != 0) {
    operator delete[](void*)();
    *(undefined8 *)(param_1 + 0x60) = 0;
  }
  if ((*(char *)(param_1 + 0x71) != '\0') && (*(long *)(param_1 + 0x68) != 0)) {
    operator delete[](void*)();
    *(undefined8 *)(param_1 + 0x68) = 0;
  }
  *(undefined8 *)(param_1 + 0x68) = 0;
  iVar3 = Aska::AafHandler::CalcRuntimeMemorySize1(Aska::AFF::AskaFile const*, Aska::AafHeader const*)(uVar2,lVar6);
  if (iVar3 == 0) {
    uVar8 = *(uint *)(param_1 + 0xc);
    goto code_r0x02095e1c;
  }
  lVar5 = operator new[](unsigned long, unsigned long, bool)(iVar3,0x10,1);
  *(long *)(param_1 + 0x58) = lVar5;
  if (lVar5 == 0) {
    return 0;
  }
  if (*(int *)(lVar6 + 0x14) != 0) {
    lVar5 = operator new[](unsigned long, unsigned long, bool)(*(int *)(lVar6 + 0x14),0x10,1);
    *(long *)(param_1 + 0x60) = lVar5;
    if (lVar5 == 0) {
      if (*(long *)(param_1 + 0x58) != 0) {
        operator delete[](void*)();
        *(undefined8 *)(param_1 + 0x58) = 0;
        return 0;
      }
      return 0;
    }
  }
  if (*(int *)(lVar6 + 0x18) == 0) {
    *(undefined1 *)(param_1 + 0x70) = 0;
  }
  else {
    *(undefined1 *)(param_1 + 0x70) = 1;
    *(byte *)(param_1 + 0x71) = param_5 & 1;
    if ((param_5 & 1) != 0) {
      lVar6 = operator new[](unsigned long, unsigned long, bool)(*(undefined4 *)(lVar6 + 0x18),0x10,1);
      *(long *)(param_1 + 0x68) = lVar6;
      if (lVar6 == 0) {
        if (*(long *)(param_1 + 0x58) != 0) {
          operator delete[](void*)();
          *(undefined8 *)(param_1 + 0x58) = 0;
        }
        if (*(long *)(param_1 + 0x60) != 0) {
          operator delete[](void*)();
          *(undefined8 *)(param_1 + 0x60) = 0;
          return 0;
        }
        return 0;
      }
    }
    *(undefined1 *)(param_1 + 0x72) = 0;
  }
  uStack_88 = *(undefined8 *)(param_1 + 0x58);
  uStack_90 = *(undefined8 *)(param_1 + 0x60);
  puVar11 = (uint *)(param_1 + 0x38);
  uVar8 = *puVar11;
  puVar13 = *(undefined8 **)(param_1 + 0x80);
  puVar10 = puVar13;
  if (uVar8 != 0) {
    lVar6 = (ulong)uVar8 * 0x30;
    do {
      uVar4 = Aska::AafHandler::SetController(Aska::AafControllerInfo*, unsigned char**, unsigned char**)(param_1,puVar10,&uStack_88,&uStack_90);
      if ((uVar4 & 1) == 0) goto code_r0x02095d78;
      lVar6 = lVar6 + -0x30;
      puVar10 = puVar10 + 6;
    } while (lVar6 != 0);
    puVar10 = *(undefined8 **)(param_1 + 0x80);
  }
  for (; puVar10 != puVar13 + (ulong)uVar8 * 6; puVar10 = puVar10 + 6) {
    plVar14 = (long *)(*(long *)(param_1 + 0x78) + (ulong)*(ushort *)((long)puVar10 + 0x2c) * 0x10 +
                      8);
    if (*plVar14 == 0) {
      lVar6 = *(long *)(*(long *)(param_1 + 0x78) + (ulong)*(ushort *)((long)puVar10 + 0x2c) * 0x10)
      ;
      if ((lVar6 != 0) && (*(char *)(lVar6 + 1) == '\x02')) {
        if ((*(short *)(lVar6 + 10) == 4) && (*(uint *)(param_1 + 0x44) != 0)) {
          uVar4 = *(ulong *)(param_1 + 0x98);
          uVar9 = uVar4 + (ulong)*(uint *)(param_1 + 0x44) * 0x30;
          do {
            if ((*(short *)(uVar4 + 0x2c) == *(short *)(lVar6 + 8)) &&
               (**(char **)(uVar4 + 0x10) == '\x04')) {
              if (*(long **)(uVar4 + 8) != (long *)0x0) {
                lVar6 = (**(code **)(**(long **)(uVar4 + 8) + 0xa8))();
                *plVar14 = lVar6;
                if (lVar6 != 0) goto code_r0x02095cf4;
                goto code_r0x02095ce8;
              }
              break;
            }
            uVar4 = uVar4 + 0x30;
          } while (uVar4 < uVar9);
        }
        *plVar14 = 0;
      }
code_r0x02095ce8:
      *(byte *)((long)puVar10 + 0x2e) = *(byte *)((long)puVar10 + 0x2e) | 2;
    }
    else {
      if ((*(byte *)(puVar10[2] + 8) < 0xf) &&
         ((1 << (ulong)(*(byte *)(puVar10[2] + 8) & 0x1f) & 0x7274U) != 0)) goto code_r0x02095ce8;
      *(byte *)((long)puVar10 + 0x2e) = *(byte *)((long)puVar10 + 0x2e) & 0xfd;
      if ((puVar10[3] != 0) && (*(char *)(puVar10[3] + 6) == '$')) {
        uVar4 = Aska::IAnimatable::IsThisIt(unsigned short) const(*plVar14,0xf138);
        if ((uVar4 & 1) == 0) {
          uVar4 = Aska::IAnimatable::IsThisIt(unsigned short) const(*plVar14,0xf112);
          if ((uVar4 & 1) == 0) goto code_r0x02095ce8;
        }
        else {
          *puVar10 = 0xa5;
        }
      }
      uStack_80 = *puVar10;
      lStack_78 = *plVar14;
      uVar4 = (**(code **)(*(long *)puVar10[1] + 0xb8))
                        ((long *)puVar10[1],param_2,&uStack_80,puVar10[2]);
      if ((uVar4 & 1) == 0) {
        *(byte *)((long)puVar10 + 0x2e) = *(byte *)((long)puVar10 + 0x2e) | 2;
      }
      *puVar10 = uStack_80;
    }
code_r0x02095cf4:
  }
  if (*(long *)(param_1 + 0x28) == 0) {
code_r0x02095d78:
    if ((*(byte *)(param_1 + 0xc) >> 4 & 1) != 0) {
      Aska::AafHandler::DetachObject()(param_1);
    }
    *(undefined2 *)(param_1 + 0xf4) = 0;
    *(undefined4 *)(param_1 + 0xa8) = 0;
    *(undefined4 *)(param_1 + 0x48) = 0;
    *(undefined8 *)(param_1 + 0x40) = 0;
    puVar11[0] = 0;
    puVar11[1] = 0;
    *(undefined8 *)(param_1 + 0x98) = 0;
    *(undefined8 *)(param_1 + 0x90) = 0;
    *(undefined8 *)(param_1 + 0x88) = 0;
    *(undefined8 *)(param_1 + 0x80) = 0;
    *(undefined8 *)(param_1 + 0x78) = 0;
    *(undefined8 *)(param_1 + 0xe0) = 0;
    *(undefined8 *)(param_1 + 200) = 0;
    *(undefined8 *)(param_1 + 0xc0) = 0;
    *(undefined8 *)(param_1 + 0xd8) = 0;
    *(undefined8 *)(param_1 + 0xd0) = 0;
    *(undefined8 *)(param_1 + 0xb8) = 0;
    *(undefined8 *)(param_1 + 0xb0) = 0;
    if (*(long *)(param_1 + 0x50) != 0) {
      operator delete[](void*)();
      *(undefined8 *)(param_1 + 0x50) = 0;
    }
    *(undefined8 *)(param_1 + 0x20) = 0;
    *(undefined8 *)(param_1 + 0x28) = 0;
    *(undefined8 *)(param_1 + 0x18) = 0;
    *(uint *)(param_1 + 0xc) = *(uint *)(param_1 + 0xc) & 0xfffffe34;
    *(undefined1 *)(param_1 + 0xf7) = 0;
    return 0;
  }
  uVar4 = (ulong)*(uint *)(param_1 + 0x40);
  if (*(uint *)(param_1 + 0x40) == 0) {
code_r0x02095d68:
    uVar8 = *(uint *)(param_1 + 0xc) | 0x100;
    *(uint *)(param_1 + 0xc) = uVar8;
  }
  else {
    if (*(long *)(param_1 + 0x110) != 0) {
      puVar1 = (ushort *)(*(long *)(param_1 + 0x110) + 2);
      lVar6 = 0;
      puVar12 = puVar1;
      do {
        lVar5 = *(long *)(param_1 + 0x90) + lVar6;
        if ((*(byte *)(*(long *)(lVar5 + 0x10) + 5) >> 6 & 1) == 0) {
          plVar14 = *(long **)(lVar5 + 8);
          (**(code **)(*plVar14 + 0xd8))(0,plVar14,1,(ulong)*puVar12 + (long)puVar1);
        }
        lVar6 = lVar6 + 0x30;
        uVar4 = uVar4 - 1;
        puVar12 = puVar12 + 1;
      } while (uVar4 != 0);
      goto code_r0x02095d68;
    }
    uVar8 = *(uint *)(param_1 + 0xc);
  }
  uVar8 = uVar8 | 0x80;
  *(uint *)(param_1 + 0xc) = uVar8;
code_r0x02095e1c:
  *(uint *)(param_1 + 0xc) = uVar8 | uVar8 >> 2 & 2 | 0x10;
  return 1;
}

// ==== Aska::AafHandler::Copy(Aska::AsfHandler*, Aska::AafHandler*, Aska::CollisionHandler*, Aska::AsfTargetNameList*, bool)
// vaddr 0x1f95e54 | ghidra 0x2095e54 | size 548 | symbol _ZN4Aska10AafHandler4CopyEPNS_10AsfHandlerEPS0_PNS_16CollisionHandlerEPNS_17AsfTargetNameListEb | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska10AafHandler4CopyEPNS_10AsfHandlerEPS0_PNS_16CollisionHandlerEPNS_17AsfTargetNameListEb
          (long param_1,undefined8 param_2,long param_3,undefined8 param_4,undefined8 param_5,
          uint param_6)

{
  long lVar1;
  undefined4 uVar2;
  long lVar3;
  ulong uVar4;
  long *plVar5;
  uint uVar6;
  ulong uVar7;
  ushort *puVar8;
  long lVar9;
  
  if ((*(long *)(param_3 + 0x80) == 0) || (lVar9 = *(long *)(param_3 + 0x20), lVar9 == 0)) {
    return 0;
  }
  uVar2 = *(undefined4 *)(lVar9 + 4);
  lVar3 = operator new[](unsigned long, std::nothrow_t const&)(uVar2,PTR__ZSt7nothrow_02cb9a80);
  if (lVar3 == 0) {
    return 0;
  }
  memcpy(lVar3,lVar9,uVar2);
  uVar6 = *(uint *)(param_1 + 0xc);
  if ((uVar6 & 0x18) != 0) {
    if ((uVar6 >> 4 & 1) != 0) {
      Aska::AafHandler::DetachObject()(param_1);
    }
    *(undefined2 *)(param_1 + 0xf4) = 0;
    *(undefined4 *)(param_1 + 0xa8) = 0;
    *(undefined4 *)(param_1 + 0x48) = 0;
    *(undefined8 *)(param_1 + 0x98) = 0;
    *(undefined8 *)(param_1 + 0x40) = 0;
    *(undefined8 *)(param_1 + 0x38) = 0;
    *(undefined8 *)(param_1 + 0x90) = 0;
    *(undefined8 *)(param_1 + 0x88) = 0;
    *(undefined8 *)(param_1 + 0x80) = 0;
    *(undefined8 *)(param_1 + 0x78) = 0;
    *(undefined8 *)(param_1 + 0xe0) = 0;
    *(undefined8 *)(param_1 + 200) = 0;
    *(undefined8 *)(param_1 + 0xc0) = 0;
    *(undefined8 *)(param_1 + 0xd8) = 0;
    *(undefined8 *)(param_1 + 0xd0) = 0;
    *(undefined8 *)(param_1 + 0xb8) = 0;
    *(undefined8 *)(param_1 + 0xb0) = 0;
    if (*(long *)(param_1 + 0x50) != 0) {
      operator delete[](void*)();
      *(undefined8 *)(param_1 + 0x50) = 0;
    }
    *(undefined8 *)(param_1 + 0x20) = 0;
    *(undefined8 *)(param_1 + 0x28) = 0;
    *(undefined8 *)(param_1 + 0x18) = 0;
    uVar6 = *(uint *)(param_1 + 0xc) & 0xfffffe34;
    *(uint *)(param_1 + 0xc) = uVar6;
    *(undefined1 *)(param_1 + 0xf7) = 0;
  }
  if (((uVar6 >> 2 & 1) == 0) && (*(long *)(param_1 + 0x10) != 0)) {
    operator delete[](void*)();
    uVar6 = *(uint *)(param_1 + 0xc);
    *(undefined8 *)(param_1 + 0x10) = 0;
  }
  *(uint *)(param_1 + 0xc) = uVar6 & 0xfffffffa;
  *(long *)(param_1 + 0x10) = lVar3;
  uVar4 = Aska::AafHandler::CreateControllers(Aska::AsfHandler*, Aska::CollisionHandler*, Aska::AsfTargetNameList*, bool)(param_1,param_2,param_4,param_5,param_6 & 1);
  if ((uVar4 & 1) == 0) {
    return 0;
  }
  if (((*(long *)(param_1 + 0x110) == 0) && (lVar9 = *(long *)(param_3 + 0x110), lVar9 != 0)) &&
     (*(long *)(param_1 + 0x28) != 0)) {
    uVar6 = *(uint *)(param_1 + 0xc);
    *(long *)(param_1 + 0x110) = lVar9;
    if ((uVar6 >> 1 & 1) != 0) {
      uVar4 = (ulong)*(uint *)(param_1 + 0x40);
      if (*(uint *)(param_1 + 0x40) != 0) {
        lVar3 = 0;
        puVar8 = (ushort *)(lVar9 + 2);
        do {
          lVar1 = *(long *)(param_1 + 0x90) + lVar3;
          if ((*(byte *)(*(long *)(lVar1 + 0x10) + 5) >> 6 & 1) == 0) {
            plVar5 = *(long **)(lVar1 + 8);
            (**(code **)(*plVar5 + 0xd8))(0,plVar5,1,(ulong)*puVar8 + lVar9 + 2);
          }
          lVar3 = lVar3 + 0x30;
          uVar4 = uVar4 - 1;
          puVar8 = puVar8 + 1;
        } while (uVar4 != 0);
        uVar6 = *(uint *)(param_1 + 0xc);
      }
      *(uint *)(param_1 + 0xc) = uVar6 | 0x100;
      lVar9 = *(long *)(param_1 + 0x118);
      goto joined_r0x02095f7c;
    }
  }
  lVar9 = *(long *)(param_1 + 0x118);
joined_r0x02095f7c:
  if ((lVar9 != 0) && (uVar4 = (ulong)*(ushort *)(*(long *)(param_1 + 0x28) + 0xe), uVar4 != 0)) {
    uVar7 = 0;
    do {
      lVar9 = *(long *)(*(long *)(param_3 + 0x118) + uVar7 * 8);
      if (((lVar9 != 0) && (*(long *)(param_1 + 0x118) != 0)) &&
         ((*(long *)(param_1 + 0x28) != 0 &&
          ((long)uVar7 < (long)(ulong)*(ushort *)(*(long *)(param_1 + 0x28) + 0xe))))) {
        *(long *)(*(long *)(param_1 + 0x118) + uVar7 * 8) = lVar9;
      }
      uVar7 = uVar7 + 1;
    } while (uVar4 != uVar7);
  }
  return 1;
}

// ==== Aska::AafHandler::AttachConstantChunkData(unsigned char*)
// vaddr 0x1f96078 | ghidra 0x2096078 | size 168 | symbol _ZN4Aska10AafHandler23AttachConstantChunkDataEPh | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska10AafHandler23AttachConstantChunkDataEPh(long param_1,long param_2)

{
  long lVar1;
  long *plVar2;
  undefined8 uVar3;
  uint uVar4;
  ulong uVar5;
  long lVar6;
  ushort *puVar7;
  
  if ((param_2 == 0) || (*(long *)(param_1 + 0x28) == 0)) {
    uVar3 = 0;
  }
  else {
    uVar4 = *(uint *)(param_1 + 0xc);
    *(long *)(param_1 + 0x110) = param_2;
    if ((uVar4 >> 1 & 1) != 0) {
      uVar5 = (ulong)*(uint *)(param_1 + 0x40);
      if (*(uint *)(param_1 + 0x40) != 0) {
        lVar6 = 0;
        puVar7 = (ushort *)(param_2 + 2);
        do {
          lVar1 = *(long *)(param_1 + 0x90) + lVar6;
          if ((*(byte *)(*(long *)(lVar1 + 0x10) + 5) >> 6 & 1) == 0) {
            plVar2 = *(long **)(lVar1 + 8);
            (**(code **)(*plVar2 + 0xd8))(0,plVar2,1,(ulong)*puVar7 + param_2 + 2);
          }
          lVar6 = lVar6 + 0x30;
          uVar5 = uVar5 - 1;
          puVar7 = puVar7 + 1;
        } while (uVar5 != 0);
        uVar4 = *(uint *)(param_1 + 0xc);
      }
      *(uint *)(param_1 + 0xc) = uVar4 | 0x100;
    }
    uVar3 = 1;
  }
  return uVar3;
}

// ==== Aska::AafHandler::AttachChunkData(int, unsigned char*)
// vaddr 0x1f96120 | ghidra 0x2096120 | size 80 | symbol _ZN4Aska10AafHandler15AttachChunkDataEiPh | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska10AafHandler15AttachChunkDataEiPh(long param_1,int param_2,long param_3)

{
  undefined8 uVar1;
  
  if (param_3 == 0) {
    return 0;
  }
  if (*(long *)(param_1 + 0x118) != 0) {
    uVar1 = 0;
    if ((-1 < param_2) && (*(long *)(param_1 + 0x28) != 0)) {
      if ((int)(uint)*(ushort *)(*(long *)(param_1 + 0x28) + 0xe) <= param_2) {
        return 0;
      }
      uVar1 = 1;
      *(long *)(*(long *)(param_1 + 0x118) + (long)param_2 * 8) = param_3;
    }
    return uVar1;
  }
  return 0;
}

// ==== Aska::AafHandler::PrecreateControllers(Aska::AsfHandler*, Aska::CollisionHandler*, Aska::AsfTargetNameList*)
// vaddr 0x1f96170 | ghidra 0x2096170 | size 164 | symbol _ZN4Aska10AafHandler20PrecreateControllersEPNS_10AsfHandlerEPNS_16CollisionHandlerEPNS_17AsfTargetNameListE | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska10AafHandler20PrecreateControllersEPNS_10AsfHandlerEPNS_16CollisionHandlerEPNS_17AsfTargetNameListE
          (long param_1,long param_2,undefined8 param_3,undefined8 param_4)

{
  int iVar1;
  undefined8 uVar2;
  ulong uVar3;
  int *piVar4;
  
  uVar2 = 0;
  if ((param_2 != 0) && (piVar4 = *(int **)(param_1 + 0x10), piVar4 != (int *)0x0)) {
    if ((*(byte *)(param_1 + 0xc) & 1) == 0) {
      iVar1 = *piVar4;
      while (iVar1 != 0x41414620) {
        if (piVar4[3] == 0) {
          return 0;
        }
        piVar4 = (int *)((long)piVar4 + (ulong)(uint)piVar4[3]);
        iVar1 = *piVar4;
      }
      uVar3 = Aska::AafHandler::AttachAaf(void const*, Aska::AsfHandler*, Aska::CollisionHandler*, Aska::AsfTargetNameList*)(param_1,piVar4,param_2,param_3,param_4);
      if ((uVar3 & 1) == 0) {
        return 0;
      }
      *(uint *)(param_1 + 0xc) = *(uint *)(param_1 + 0xc) | 1;
    }
    uVar2 = 1;
  }
  return uVar2;
}

// ==== Aska::AafHandler::AttachAaf(void const*, Aska::AsfHandler*, Aska::CollisionHandler*, Aska::AsfTargetNameList*)
// vaddr 0x1f96214 | ghidra 0x2096214 | size 2256 | symbol _ZN4Aska10AafHandler9AttachAafEPKvPNS_10AsfHandlerEPNS_16CollisionHandlerEPNS_17AsfTargetNameListE | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska10AafHandler9AttachAafEPKvPNS_10AsfHandlerEPNS_16CollisionHandlerEPNS_17AsfTargetNameListE
          (long param_1,int *param_2,long param_3,long param_4,undefined8 param_5)

{
  undefined8 *puVar1;
  byte bVar2;
  byte bVar3;
  ushort uVar4;
  ushort uVar5;
  ushort uVar6;
  uint uVar7;
  int iVar8;
  ulong uVar9;
  long lVar10;
  ulong uVar11;
  long lVar12;
  ushort *puVar13;
  byte *pbVar14;
  byte *pbVar15;
  long lVar16;
  uint *puVar17;
  long lVar18;
  uint unaff_w20;
  long lVar19;
  uint uVar20;
  ulong unaff_x21;
  long *plVar21;
  uint uVar22;
  ulong *puVar23;
  byte *pbVar24;
  ulong uVar25;
  int *unaff_x27;
  byte bVar26;
  uint uStack_c4;
  uint uStack_ac;
  uint uStack_9c;
  undefined *puStack_78;
  long lStack_70;
  int iStack_64;
  
  if ((*(uint *)(param_1 + 0xc) >> 3 & 1) != 0) {
    if ((*(uint *)(param_1 + 0xc) >> 4 & 1) != 0) {
      Aska::AafHandler::DetachObject()(param_1);
    }
    *(undefined2 *)(param_1 + 0xf4) = 0;
    *(undefined4 *)(param_1 + 0xa8) = 0;
    *(undefined4 *)(param_1 + 0x48) = 0;
    *(undefined8 *)(param_1 + 0x98) = 0;
    *(undefined8 *)(param_1 + 0x40) = 0;
    *(undefined8 *)(param_1 + 0x38) = 0;
    *(undefined8 *)(param_1 + 0x90) = 0;
    *(undefined8 *)(param_1 + 0x88) = 0;
    *(undefined8 *)(param_1 + 0x80) = 0;
    *(undefined8 *)(param_1 + 0x78) = 0;
    *(undefined8 *)(param_1 + 0xe0) = 0;
    *(undefined8 *)(param_1 + 200) = 0;
    *(undefined8 *)(param_1 + 0xc0) = 0;
    *(undefined8 *)(param_1 + 0xd8) = 0;
    *(undefined8 *)(param_1 + 0xd0) = 0;
    *(undefined8 *)(param_1 + 0xb8) = 0;
    *(undefined8 *)(param_1 + 0xb0) = 0;
    if (*(long *)(param_1 + 0x50) != 0) {
      operator delete[](void*)();
      *(undefined8 *)(param_1 + 0x50) = 0;
    }
    *(undefined8 *)(param_1 + 0x20) = 0;
    *(undefined8 *)(param_1 + 0x28) = 0;
    *(undefined8 *)(param_1 + 0x18) = 0;
    *(uint *)(param_1 + 0xc) = *(uint *)(param_1 + 0xc) & 0xfffffe34;
    *(undefined1 *)(param_1 + 0xf7) = 0;
  }
  if ((param_3 == 0) || (uStack_c4 = *(uint *)(param_3 + 0xb0), uStack_c4 == 0)) {
    return 0;
  }
  if (param_2 == (int *)0x0) {
code_r0x02096330:
    iVar8 = 0;
    *(int **)(param_1 + 0x20) = param_2;
    *(int **)(param_1 + 0x28) = unaff_x27;
  }
  else {
    if (*param_2 != 0x41414620) goto code_r0x02096754;
    puStack_78 = PTR__ZTVN4Aska10ArfHandlerE_02cbeb70 + 0x10;
    lStack_70 = 0;
    unaff_x27 = param_2 + 4;
    uVar9 = Aska::ArfHandler::Attach(Aska::AFF::AskaResource const*)(&puStack_78,unaff_x27);
    if ((((uVar9 & 1) != 0) &&
        (((lStack_70 == 0 || (*(uint *)(lStack_70 + 0xc) == 0)) ||
         (unaff_x27 = (int *)(lStack_70 + (ulong)*(uint *)(lStack_70 + 0xc)),
         unaff_x27 == (int *)0x0)))) || ((short)*unaff_x27 != 0x2e)) goto code_r0x02096754;
    uVar4 = *(ushort *)(unaff_x27 + 2);
    unaff_x21 = (ulong)uVar4;
    unaff_w20 = (uint)uVar4 + (uint)*(ushort *)((long)unaff_x27 + 6) +
                (uint)*(ushort *)((long)unaff_x27 + 10);
    uStack_c4 = (uint)*(ushort *)(unaff_x27 + 1);
    uVar7 = uVar4 + 0x1f >> 5;
    iVar8 = unaff_w20 * 0x30 + uStack_c4 * 0x10 + (uint)*(ushort *)((long)unaff_x27 + 0xe) * 8;
    if (uVar7 != 0) {
      iVar8 = (uint)uVar4 * 0xc + uVar7 * 8 + iVar8;
    }
    if (iVar8 + 2U < 2) goto code_r0x02096754;
    if (iVar8 == 0) goto code_r0x02096330;
    *(int **)(param_1 + 0x20) = param_2;
    *(int **)(param_1 + 0x28) = unaff_x27;
    if ((*unaff_x27 & 0x10000) != 0) {
      *(uint *)(param_1 + 0xc) = *(uint *)(param_1 + 0xc) | 0x40;
    }
    *(uint *)(param_1 + 0xa8) = uVar7;
  }
  *(undefined8 *)(param_1 + 0x18) = param_5;
  if (*(long *)(param_1 + 0x50) != 0) {
    operator delete[](void*)();
  }
  if (iVar8 == 0) {
    *(undefined8 *)(param_1 + 0x50) = 0;
    *(undefined8 *)(param_1 + 0xd0) = 0;
    *(undefined8 *)(param_1 + 0x80) = 0;
    *(undefined8 *)(param_1 + 0x78) = 0;
    *(undefined8 *)(param_1 + 0xb8) = 0;
    *(undefined8 *)(param_1 + 0xb0) = 0;
    *(undefined8 *)(param_1 + 200) = 0;
    *(undefined8 *)(param_1 + 0xc0) = 0;
  }
  else {
    lVar10 = operator new[](unsigned long, std::nothrow_t const&)(iVar8,PTR__ZSt7nothrow_02cb9a80);
    *(long *)(param_1 + 0x50) = lVar10;
    if (lVar10 == 0) {
code_r0x02096754:
      if ((*(byte *)(param_1 + 0xc) >> 4 & 1) != 0) {
        Aska::AafHandler::DetachObject()(param_1);
      }
      *(undefined2 *)(param_1 + 0xf4) = 0;
      *(undefined4 *)(param_1 + 0xa8) = 0;
      *(undefined4 *)(param_1 + 0x48) = 0;
      *(undefined8 *)(param_1 + 0x98) = 0;
      *(undefined8 *)(param_1 + 0x40) = 0;
      *(undefined8 *)(param_1 + 0x38) = 0;
      *(undefined8 *)(param_1 + 0x90) = 0;
      *(undefined8 *)(param_1 + 0x88) = 0;
      *(undefined8 *)(param_1 + 0x80) = 0;
      *(undefined8 *)(param_1 + 0x78) = 0;
      *(undefined8 *)(param_1 + 0xe0) = 0;
      *(undefined8 *)(param_1 + 200) = 0;
      *(undefined8 *)(param_1 + 0xc0) = 0;
      *(undefined8 *)(param_1 + 0xd8) = 0;
      *(undefined8 *)(param_1 + 0xd0) = 0;
      *(undefined8 *)(param_1 + 0xb8) = 0;
      *(undefined8 *)(param_1 + 0xb0) = 0;
      if (*(long *)(param_1 + 0x50) != 0) {
        operator delete[](void*)();
        *(undefined8 *)(param_1 + 0x50) = 0;
      }
      *(undefined8 *)(param_1 + 0x20) = 0;
      *(undefined8 *)(param_1 + 0x28) = 0;
      *(undefined8 *)(param_1 + 0x18) = 0;
      *(uint *)(param_1 + 0xc) = *(uint *)(param_1 + 0xc) & 0xfffffe34;
      *(undefined1 *)(param_1 + 0xf7) = 0;
      return 0;
    }
    lVar18 = lVar10 + (ulong)uStack_c4 * 0x10;
    lVar12 = lVar18 + (ulong)unaff_w20 * 0x30;
    lVar16 = (ulong)*(uint *)(param_1 + 0xa8) * 4;
    lVar19 = lVar12 + lVar16;
    *(long *)(param_1 + 0xb0) = lVar12;
    *(long *)(param_1 + 0xb8) = lVar19;
    lVar19 = lVar19 + lVar16;
    lVar12 = lVar19 + (unaff_x21 & 0xffffffff) * 8;
    *(long *)(param_1 + 0xc0) = lVar19;
    *(long *)(param_1 + 200) = lVar12;
    lVar12 = lVar12 + (unaff_x21 & 0xffffffff) * 2;
    *(long *)(param_1 + 0x78) = lVar10;
    *(long *)(param_1 + 0x80) = lVar18;
    *(long *)(param_1 + 0xd0) = lVar12;
    if (*(short *)((long)unaff_x27 + 0xe) == 0) {
      *(undefined8 *)(param_1 + 0x118) = 0;
    }
    else {
      lVar12 = lVar12 + (unaff_x21 & 0xffffffff) * 2;
      *(long *)(param_1 + 0x118) = lVar12;
      memset(lVar12,0,(ulong)*(ushort *)((long)unaff_x27 + 0xe) << 3);
    }
    memset(lVar18,0,(ulong)unaff_w20 * 0x30);
  }
  *(short *)(param_1 + 0xf4) = (short)uStack_c4;
  *(uint *)(param_1 + 0x38) = unaff_w20;
  uVar4 = *(ushort *)((long)unaff_x27 + 6);
  *(uint *)(param_1 + 0x44) = (uint)uVar4;
  uVar5 = *(ushort *)(unaff_x27 + 2);
  *(uint *)(param_1 + 0x3c) = (uint)uVar5;
  uVar6 = *(ushort *)((long)unaff_x27 + 10);
  *(uint *)(param_1 + 0x40) = (uint)uVar6;
  if (uVar5 == 0) {
    lVar10 = 0;
  }
  else {
    lVar10 = *(long *)(param_1 + 0x80);
  }
  *(long *)(param_1 + 0x88) = lVar10;
  if (uVar6 == 0) {
    lVar18 = 0;
    *(undefined8 *)(param_1 + 0x90) = 0;
    if (uVar4 != 0) goto code_r0x020964d4;
code_r0x020964f4:
    lVar12 = 0;
  }
  else {
    lVar18 = *(long *)(param_1 + 0x80) + (ulong)uVar5 * 0x30;
    *(long *)(param_1 + 0x90) = lVar18;
    if (uVar4 == 0) goto code_r0x020964f4;
code_r0x020964d4:
    lVar12 = *(long *)(param_1 + 0x80) + ((ulong)uVar6 + (ulong)uVar5) * 0x30;
  }
  *(long *)(param_1 + 0x98) = lVar12;
  uVar7 = uStack_c4 & 0xffff;
  *(uint *)(param_1 + 0x48) = (uint)*(ushort *)(unaff_x27 + 3);
  pbVar15 = (byte *)((ulong)(uint)unaff_x27[8] + (long)param_2);
  if (uVar7 != 0) {
    uVar9 = 0;
    uVar22 = 0;
    puVar23 = (ulong *)0x0;
    uStack_9c = 0;
    uStack_ac = 0;
    do {
      puVar1 = (undefined8 *)(*(long *)(param_1 + 0x78) + uVar9 * 0x10);
      *puVar1 = pbVar15;
      puVar1[1] = 0;
      uVar4 = *(ushort *)(pbVar15 + 2);
      if (uVar4 != 0) {
        uVar20 = 0;
        bVar3 = *pbVar15 & 1;
        pbVar24 = pbVar15 + 0x28;
        if ((*pbVar15 & 4) != 0) {
          pbVar24 = pbVar15 + 0xc;
        }
        do {
          uVar5 = *(ushort *)(pbVar24 + 2);
          Hint_Prefetch(pbVar24 + uVar5,0,2,0);
          bVar26 = pbVar24[5];
          if ((char)bVar26 < '\0') {
            puVar23 = (ulong *)(lVar18 + (ulong)uVar22 * 0x30);
            uVar22 = uVar22 + 1;
          }
          else if ((bVar26 >> 6 & 1) == 0) {
            if ((bVar26 >> 5 & 1) != 0) {
              puVar23 = (ulong *)(lVar10 + (ulong)uStack_ac * 0x30);
              uStack_ac = uStack_ac + 1;
            }
          }
          else {
            puVar23 = (ulong *)(lVar12 + (ulong)uStack_9c * 0x30);
            uStack_9c = uStack_9c + 1;
          }
          bVar2 = *pbVar24;
          bVar26 = bVar3 | 4;
          if (bVar2 != 2) {
            bVar26 = bVar3;
          }
          if ((ulong)*(ushort *)(pbVar24 + 6) == 0) {
            if (bVar2 == 0xb) {
              uVar25 = Aska::AafValueArrayController::MakeAnimatedIndex(Aska::AafControllerHeader const*)(pbVar24);
            }
            else if (bVar2 == 4) {
              uVar25 = Aska::AafNoiseController::MakeAnimatedIndex(Aska::AafControllerHeader const*)(pbVar24);
            }
            else {
              uVar25 = 0xffffffffffffffff;
            }
            puVar13 = (ushort *)0x0;
code_r0x02096678:
            *puVar23 = uVar25;
          }
          else {
            puVar13 = (ushort *)(pbVar24 + *(ushort *)(pbVar24 + 6));
            uVar25 = (ulong)(byte)puVar13[1] << 0x20 | (ulong)*(byte *)((long)puVar13 + 3) << 0x10 |
                     (ulong)*puVar13;
            *puVar23 = uVar25;
            bVar2 = bVar26 | 0x40;
            if (*(int *)(puVar13 + 10) != 1) {
              bVar2 = bVar26;
            }
            bVar26 = bVar2;
            if ((puVar13 != (ushort *)0x0) && (*puVar13 == 0xffff)) {
              uVar25 = 0xffffffffffffffff;
              goto code_r0x02096678;
            }
          }
          *(byte *)((long)puVar23 + 0x2e) = bVar26;
          *(short *)((long)puVar23 + 0x2c) = (short)uVar9;
          puVar23[1] = 0;
          puVar23[2] = (ulong)pbVar24;
          puVar23[3] = (ulong)puVar13;
          if ((param_4 != 0) && (pbVar14 = (byte *)*puVar1, pbVar14[1] == 1)) {
            if ((*pbVar14 >> 2 & 1) == 0) {
              pbVar14 = pbVar14 + 8;
            }
            else {
              puVar17 = *(uint **)(param_1 + 0x18);
              if (((puVar17 == (uint *)0x0) || (*puVar17 <= *(uint *)(pbVar14 + 8))) ||
                 (pbVar14 = (byte *)((long)puVar17 + (ulong)(*(uint *)(pbVar14 + 8) << 5) + 4),
                 pbVar14 == (byte *)0x0)) goto code_r0x02096754;
            }
            iVar8 = Aska::CollisionHandler::SearchIndexByName(char const*) const(param_4,pbVar14);
            if (iVar8 < 0) {
              *(byte *)((long)puVar23 + 0x2e) = *(byte *)((long)puVar23 + 0x2e) | 4;
              uVar25 = 0xffffffffffffffff;
            }
            else {
              uVar25 = uVar25 & 0xffff0000ffff | (ulong)(uint)(iVar8 << 0x10);
            }
            *puVar23 = uVar25;
          }
          uVar20 = uVar20 + 1;
          pbVar24 = pbVar24 + uVar5;
        } while (uVar20 < uVar4);
      }
      uVar9 = uVar9 + 1;
      pbVar15 = pbVar15 + *(uint *)(pbVar15 + 4);
    } while (uVar9 < uVar7);
  }
  if ((*(byte *)(param_1 + 0xc) >> 6 & 1) == 0) {
    *(byte **)(param_1 + 0xe0) = pbVar15;
  }
  else if (0 < *(int *)(param_1 + 0x3c)) {
    uVar9 = *(ulong *)(param_1 + 0x88);
    uVar25 = uVar9 + (long)*(int *)(param_1 + 0x3c) * 0x30;
    do {
      if (*(long *)(uVar9 + 0x18) != 0) {
        *(byte **)(uVar9 + 0x20) = pbVar15;
        *(undefined4 *)(uVar9 + 0x28) = 0;
        pbVar15 = pbVar15 + (ulong)*(uint *)(*(long *)(uVar9 + 0x18) + 0x14) * 8;
      }
      uVar9 = uVar9 + 0x30;
    } while (uVar9 < uVar25);
  }
  if ((uStack_c4 & 0xffff) != 0) {
    uVar9 = 0;
    do {
      lVar10 = *(long *)(param_1 + 0x78);
      pbVar15 = *(byte **)(lVar10 + uVar9 * 0x10);
      bVar3 = pbVar15[1];
      if (bVar3 - 4 < 2 || bVar3 == 2) {
        *(undefined8 *)(lVar10 + uVar9 * 0x10 + 8) = 0;
      }
      else if (bVar3 == 1) {
        *(long *)(lVar10 + uVar9 * 0x10 + 8) = param_4;
      }
      else {
        if ((*pbVar15 >> 2 & 1) == 0) {
          pbVar15 = pbVar15 + 8;
        }
        else {
          puVar17 = *(uint **)(param_1 + 0x18);
          if (((puVar17 == (uint *)0x0) || (*puVar17 <= *(uint *)(pbVar15 + 8))) ||
             (pbVar15 = (byte *)((long)puVar17 + (ulong)(*(uint *)(pbVar15 + 8) << 5) + 4),
             pbVar15 == (byte *)0x0)) goto code_r0x02096938;
        }
        lVar18 = Aska::AsfHandler::QuickSearchByNameEx(char const*) const(param_3,pbVar15);
        plVar21 = (long *)(lVar10 + uVar9 * 0x10 + 8);
        *plVar21 = lVar18;
        if (lVar18 == 0) {
          uVar25 = Aska::AsfHandler::GetModifierAnimationId(char const*, Aska::IAnimatable**, int*) const(param_3,pbVar15,&puStack_78,&iStack_64);
          if ((uVar25 & 1) == 0) {
            *plVar21 = 0;
          }
          else {
            *plVar21 = (long)puStack_78;
            if ((puStack_78 != (undefined *)0x0) &&
               (uVar25 = (ulong)*(uint *)(param_1 + 0x38), *(uint *)(param_1 + 0x38) != 0)) {
              lVar10 = 0;
              do {
                lVar18 = *(long *)(param_1 + 0x80);
                if (uVar9 == *(ushort *)(lVar18 + lVar10 + 0x2c)) {
                  *(ulong *)(lVar18 + lVar10) =
                       (ulong)*(ushort *)(lVar18 + lVar10) | (ulong)(uint)(iStack_64 << 0x10) |
                       0x200000000;
                }
                uVar25 = uVar25 - 1;
                lVar10 = lVar10 + 0x30;
              } while (uVar25 != 0);
            }
          }
        }
      }
code_r0x02096938:
      uVar9 = uVar9 + 1;
    } while (uVar9 != uVar7);
  }
  uVar7 = *(uint *)(param_1 + 0x40);
  if (0 < (int)uVar7) {
    if (*(long *)(param_1 + 0x118) == 0) {
      puVar13 = (ushort *)
                ((long)((ulong)(uint)unaff_x27[9] + (long)param_2) +
                (ulong)*(uint *)((ulong)(uint)unaff_x27[9] + (long)param_2));
      *(ushort **)(param_1 + 0x110) = puVar13;
      if ((*(byte *)(param_1 + 0xc) >> 6 & 1) == 0) {
        *(ulong *)(param_1 + 0xd8) = (long)puVar13 + (ulong)*puVar13;
      }
    }
    lVar10 = *(long *)(param_1 + 0x90);
    if (uVar7 < 2) {
      lVar18 = 0;
    }
    else {
      lVar18 = (ulong)uVar7 - (ulong)(uVar7 & 1);
      if (lVar18 != 0) {
        pbVar15 = (byte *)(lVar10 + 0x5e);
        lVar12 = lVar18;
        do {
          lVar12 = lVar12 + -2;
          pbVar15[-0x30] = pbVar15[-0x30] | 8;
          *pbVar15 = *pbVar15 | 8;
          pbVar15 = pbVar15 + 0x60;
        } while (lVar12 != 0);
        if ((uVar7 & 1) == 0) goto code_r0x020969f0;
      }
    }
    lVar12 = (ulong)uVar7 - lVar18;
    pbVar15 = (byte *)(lVar10 + lVar18 * 0x30 + 0x2e);
    do {
      lVar12 = lVar12 + -1;
      *pbVar15 = *pbVar15 | 8;
      pbVar15 = pbVar15 + 0x30;
    } while (lVar12 != 0);
  }
code_r0x020969f0:
  uVar9 = (ulong)*(uint *)(param_1 + 0x38);
  if (*(uint *)(param_1 + 0x38) != 0) {
    lVar10 = 0;
    do {
      lVar18 = *(long *)(param_1 + 0x80);
      lVar12 = *(long *)(lVar18 + lVar10 + 0x10);
      if ((((lVar12 != 0) && ((*(byte *)(lVar12 + 5) & 0x11) == 1)) &&
          (lVar19 = *(long *)(*(long *)(param_1 + 0x78) +
                              (ulong)*(ushort *)(lVar18 + lVar10 + 0x2c) * 0x10 + 8), lVar19 != 0))
         && ((uVar25 = *(ulong *)(lVar18 + lVar10), (uVar25 & 0xffff00000000) == 0x100000000 &&
             (uVar11 = Aska::IAnimatable::IsThisIt(unsigned short) const(lVar19,0xf113), (uVar11 & 1) != 0)))) {
        iVar8 = Aska::AofObject::GetRenderNodeIndex(char const*)(lVar19,lVar12 + 0xc);
        if (iVar8 == -1) {
          iVar8 = 0;
          *(byte *)(lVar18 + lVar10 + 0x2e) = *(byte *)(lVar18 + lVar10 + 0x2e) | 2;
        }
        *(ulong *)(lVar18 + lVar10) = uVar25 & 0xffff | (ulong)(uint)(iVar8 << 0x10) | 0x100000000;
      }
      uVar9 = uVar9 - 1;
      lVar10 = lVar10 + 0x30;
    } while (uVar9 != 0);
  }
  *(uint *)(param_1 + 0xc) = *(uint *)(param_1 + 0xc) | 8;
  return 1;
}

// ==== Aska::AafHandler::DetachObject()
// vaddr 0x1f96ae4 | ghidra 0x2096ae4 | size 236 | symbol _ZN4Aska10AafHandler12DetachObjectEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10AafHandler12DetachObjectEv(long param_1)

{
  long lVar1;
  long lVar2;
  ulong uVar3;
  int iVar4;
  byte *pbVar5;
  
  *(undefined8 *)(param_1 + 0x30) = 0;
  *(uint *)(param_1 + 0xc) = *(uint *)(param_1 + 0xc) & 0xffffffed;
  if ((*(long *)(param_1 + 0x80) != 0) && (iVar4 = *(int *)(param_1 + 0x38), iVar4 != 0)) {
    pbVar5 = (byte *)(*(long *)(param_1 + 0x80) + 0x2e);
    do {
      if (*(long **)(pbVar5 + -0x26) != (long *)0x0) {
        (**(code **)(**(long **)(pbVar5 + -0x26) + 0xb0))();
        pbVar5[-0x26] = 0;
        pbVar5[-0x25] = 0;
        pbVar5[-0x24] = 0;
        pbVar5[-0x23] = 0;
        pbVar5[-0x22] = 0;
        pbVar5[-0x21] = 0;
        pbVar5[-0x20] = 0;
        pbVar5[-0x1f] = 0;
      }
      iVar4 = iVar4 + -1;
      *pbVar5 = *pbVar5 | 2;
      pbVar5 = pbVar5 + 0x30;
    } while (iVar4 != 0);
  }
  if (*(long *)(param_1 + 0x58) != 0) {
    operator delete[](void*)();
    *(undefined8 *)(param_1 + 0x58) = 0;
  }
  if (*(long *)(param_1 + 0x60) != 0) {
    operator delete[](void*)();
    *(undefined8 *)(param_1 + 0x60) = 0;
  }
  if ((*(char *)(param_1 + 0x71) != '\0') && (*(long *)(param_1 + 0x68) != 0)) {
    operator delete[](void*)();
    *(undefined8 *)(param_1 + 0x68) = 0;
  }
  lVar1 = *(long *)(param_1 + 0x78);
  *(undefined8 *)(param_1 + 0x68) = 0;
  if ((lVar1 != 0) && (uVar3 = (ulong)*(ushort *)(param_1 + 0xf4), uVar3 != 0)) {
    lVar2 = 0;
    while( true ) {
      uVar3 = uVar3 - 1;
      if ((*(byte *)(*(long *)(lVar1 + lVar2) + 1) & 0xfe) == 4) {
        *(undefined8 *)(lVar1 + lVar2 + 8) = 0;
      }
      if (uVar3 == 0) break;
      lVar1 = *(long *)(param_1 + 0x78);
      lVar2 = lVar2 + 0x10;
    }
  }
  return;
}

// ==== Aska::AafHandler::CalcRuntimeMemorySize1(Aska::AFF::AskaFile const*, Aska::AafHeader const*)
// vaddr 0x1f96bd0 | ghidra 0x2096bd0 | size 424 | symbol _ZN4Aska10AafHandler22CalcRuntimeMemorySize1EPKNS_3AFF8AskaFileEPKNS_9AafHeaderE | lib libSOA-3.7.0.so | 2026-10-04
int _ZN4Aska10AafHandler22CalcRuntimeMemorySize1EPKNS_3AFF8AskaFileEPKNS_9AafHeaderE
              (long param_1,long param_2)

{
  byte *pbVar1;
  ushort uVar2;
  ushort uVar3;
  int iVar4;
  byte *pbVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  byte *pbVar9;
  uint uVar10;
  
  uVar2 = *(ushort *)(param_2 + 4);
  if (uVar2 == 0) {
    iVar6 = 0;
  }
  else {
    uVar7 = 0;
    iVar6 = 0;
    pbVar9 = (byte *)((ulong)*(uint *)(param_2 + 0x20) + param_1);
    do {
      uVar10 = (uint)*(ushort *)(pbVar9 + 2);
      if (*(ushort *)(pbVar9 + 2) != 0) {
        pbVar5 = pbVar9 + 0x28;
        if ((*pbVar9 & 4) != 0) {
          pbVar5 = pbVar9 + 0xc;
        }
        do {
          uVar3 = *(ushort *)(pbVar5 + 2);
          pbVar1 = (byte *)0x0;
          if (*(ushort *)(pbVar5 + 6) != 0) {
            pbVar1 = pbVar5 + *(ushort *)(pbVar5 + 6);
          }
          if ((char)pbVar5[5] < '\0') {
            iVar4 = 0x60;
            switch(*pbVar5 - 4) {
            case 0:
            case 3:
              break;
            default:
code_r0x02096d08:
              iVar4 = int Aska::AafGetControllerSizeLocal<false>(Aska::AafControllerHeader const*, Aska::AafKeyframeHeader const*, unsigned int*, unsigned int*)(pbVar5,pbVar1,0,0);
              break;
            case 2:
              goto code_r0x02096cc0;
            case 4:
              goto code_r0x02096cf8;
            case 5:
              goto code_r0x02096cc8;
            case 6:
              goto code_r0x02096ce0;
            case 7:
              goto code_r0x02096d00;
            }
          }
          else {
            iVar4 = 0x60;
            switch(*pbVar5 - 4) {
            case 0:
            case 3:
              break;
            default:
              if ((pbVar1[8] != 3) && (pbVar1[9] != 3)) goto code_r0x02096d08;
              iVar4 = int Aska::AafGetControllerSizeLocal<true>(Aska::AafControllerHeader const*, Aska::AafKeyframeHeader const*, unsigned int*, unsigned int*)(pbVar5,pbVar1,0,0);
              break;
            case 2:
code_r0x02096cc0:
              iVar4 = 0x70;
              break;
            case 4:
code_r0x02096cf8:
              iVar4 = 0x50;
              break;
            case 5:
code_r0x02096cc8:
              iVar8 = 0x28;
              if (pbVar5[1] != 4) {
                iVar8 = 0;
              }
              iVar4 = 0x20;
              if (pbVar5[1] != 2) {
                iVar4 = iVar8;
              }
              break;
            case 6:
code_r0x02096ce0:
              iVar8 = 0x60;
              if (pbVar5[1] != 4) {
                iVar8 = 0;
              }
              iVar4 = 0x40;
              if (pbVar5[1] != 2) {
                iVar4 = iVar8;
              }
              break;
            case 7:
code_r0x02096d00:
              iVar4 = 0x20;
            }
          }
          uVar10 = uVar10 - 1;
          iVar6 = (iVar4 + 0xfU & 0xfffffff0) + iVar6;
          pbVar5 = pbVar5 + uVar3;
        } while (uVar10 != 0);
      }
      uVar7 = uVar7 + 1;
      pbVar9 = pbVar9 + *(uint *)(pbVar9 + 4);
    } while (uVar7 != uVar2);
  }
  return iVar6;
}

// ==== Aska::AafHandler::GetTargetControllerObject(int, int, int)
// vaddr 0x1f96d78 | ghidra 0x2096d78 | size 96 | symbol _ZN4Aska10AafHandler25GetTargetControllerObjectEiii | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska10AafHandler25GetTargetControllerObjectEiii(long param_1,uint param_2,int param_3)

{
  undefined8 uVar1;
  ulong uVar2;
  ulong uVar3;
  
  if ((param_3 == 4) && (*(uint *)(param_1 + 0x44) != 0)) {
    uVar2 = *(ulong *)(param_1 + 0x98);
    uVar3 = uVar2 + (ulong)*(uint *)(param_1 + 0x44) * 0x30;
    do {
      if ((*(ushort *)(uVar2 + 0x2c) == param_2) && (**(char **)(uVar2 + 0x10) == '\x04')) {
        if (*(long **)(uVar2 + 8) == (long *)0x0) {
          return 0;
        }
                    /* WARNING: Could not recover jumptable at 0x02096dd4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
        uVar1 = (**(code **)(**(long **)(uVar2 + 8) + 0xa8))();
        return uVar1;
      }
      uVar2 = uVar2 + 0x30;
    } while (uVar2 < uVar3);
  }
  return 0;
}

// ==== Aska::AafHandler::CheckPlatformID(Aska::AafControllerHeader const*)
// vaddr 0x1f96dd8 | ghidra 0x2096dd8 | size 44 | symbol _ZN4Aska10AafHandler15CheckPlatformIDEPKNS_19AafControllerHeaderE | lib libSOA-3.7.0.so | 2026-10-04
uint _ZN4Aska10AafHandler15CheckPlatformIDEPKNS_19AafControllerHeaderE(long param_1)

{
  uint uVar1;
  
  uVar1 = *(byte *)(param_1 + 8) - 2;
  if (uVar1 < 0xd) {
    return 0x362U >> (ulong)(uVar1 & 0x1f) & 1;
  }
  return 1;
}

// ==== Aska::AafHandler::InitializeAllConstantCache(unsigned short*)
// vaddr 0x1f96e04 | ghidra 0x2096e04 | size 156 | symbol _ZN4Aska10AafHandler26InitializeAllConstantCacheEPt | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska10AafHandler26InitializeAllConstantCacheEPt(long param_1,long param_2)

{
  long lVar1;
  long *plVar2;
  ulong uVar3;
  long lVar4;
  ushort *puVar5;
  
  if (*(long *)(param_1 + 0x28) == 0) {
    return 0;
  }
  uVar3 = (ulong)*(uint *)(param_1 + 0x40);
  if (*(uint *)(param_1 + 0x40) != 0) {
    if (param_2 == 0) {
      return 1;
    }
    lVar4 = 0;
    puVar5 = (ushort *)(param_2 + 2);
    do {
      lVar1 = *(long *)(param_1 + 0x90) + lVar4;
      if ((*(byte *)(*(long *)(lVar1 + 0x10) + 5) >> 6 & 1) == 0) {
        plVar2 = *(long **)(lVar1 + 8);
        (**(code **)(*plVar2 + 0xd8))(0,plVar2,1,(ulong)*puVar5 + param_2 + 2);
      }
      puVar5 = puVar5 + 1;
      uVar3 = uVar3 - 1;
      lVar4 = lVar4 + 0x30;
    } while (uVar3 != 0);
  }
  *(uint *)(param_1 + 0xc) = *(uint *)(param_1 + 0xc) | 0x100;
  return 1;
}

// ==== Aska::AafHandler::GetComplementBufferSize() const
// vaddr 0x1f96ea0 | ghidra 0x2096ea0 | size 60 | symbol _ZNK4Aska10AafHandler23GetComplementBufferSizeEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK4Aska10AafHandler23GetComplementBufferSizeEv(long param_1)

{
  if ((*(byte *)(param_1 + 0xc) >> 1 & 1) == 0) {
    return 0;
  }
  if (*(char *)(param_1 + 0x70) != '\0') {
    if (*(char *)(param_1 + 0x71) != '\0') {
      return 0;
    }
    return *(undefined4 *)(*(long *)(param_1 + 0x28) + 0x18);
  }
  return 0;
}

// ==== Aska::AafHandler::AttachComplementBuffer(void*, unsigned int)
// vaddr 0x1f96edc | ghidra 0x2096edc | size 84 | symbol _ZN4Aska10AafHandler22AttachComplementBufferEPvj | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska10AafHandler22AttachComplementBufferEPvj(long param_1,undefined8 param_2,uint param_3)

{
  if ((*(byte *)(param_1 + 0xc) >> 1 & 1) == 0) {
    return 0;
  }
  if ((*(char *)(param_1 + 0x70) != '\0') && (*(char *)(param_1 + 0x71) == '\0')) {
    if (param_3 < *(uint *)(*(long *)(param_1 + 0x28) + 0x18)) {
      return 0;
    }
    *(undefined8 *)(param_1 + 0xe8) = 0;
    *(undefined8 *)(param_1 + 0x68) = param_2;
    *(undefined1 *)(param_1 + 0x72) = 0;
    return 1;
  }
  return 1;
}

// ==== Aska::AafHandler::DetachComplementBuffer()
// vaddr 0x1f96f30 | ghidra 0x2096f30 | size 44 | symbol _ZN4Aska10AafHandler22DetachComplementBufferEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10AafHandler22DetachComplementBufferEv(long param_1)

{
  if ((((*(byte *)(param_1 + 0xc) >> 1 & 1) != 0) && (*(char *)(param_1 + 0x70) != '\0')) &&
     (*(char *)(param_1 + 0x71) == '\0')) {
    *(undefined8 *)(param_1 + 0xe8) = 0;
    *(undefined8 *)(param_1 + 0x68) = 0;
    *(undefined1 *)(param_1 + 0x72) = 0;
    return;
  }
  return;
}

// ==== Aska::AafHandler::IsAttachedComplementBuffer() const
// vaddr 0x1f96f5c | ghidra 0x2096f5c | size 48 | symbol _ZNK4Aska10AafHandler26IsAttachedComplementBufferEv | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK4Aska10AafHandler26IsAttachedComplementBufferEv(long param_1)

{
  if ((*(byte *)(param_1 + 0xc) >> 1 & 1) == 0) {
    return false;
  }
  if (*(char *)(param_1 + 0x70) != '\0') {
    return *(long *)(param_1 + 0x68) != 0;
  }
  return true;
}

// ==== Aska::AafHandler::HaltAnimation(Aska::IAnimatable*, bool)
// vaddr 0x1f96f8c | ghidra 0x2096f8c | size 316 | symbol _ZN4Aska10AafHandler13HaltAnimationEPNS_11IAnimatableEb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10AafHandler13HaltAnimationEPNS_11IAnimatableEb(long param_1,long param_2,uint param_3)

{
  ushort uVar1;
  ulong uVar2;
  ulong uVar3;
  uint uVar4;
  ulong uVar5;
  
  uVar1 = *(ushort *)(param_1 + 0xf4);
  if (uVar1 != 0) {
    uVar3 = *(ulong *)(param_1 + 0x80);
    uVar2 = uVar3 + (ulong)*(uint *)(param_1 + 0x38) * 0x30;
    if (param_2 == 0) {
      uVar4 = 0;
      while( true ) {
        if (uVar3 < uVar2) {
          if ((param_3 & 1) == 0) {
            do {
              if ((*(long *)(uVar3 + 8) != 0) && (uVar4 == *(ushort *)(uVar3 + 0x2c))) {
                *(byte *)(uVar3 + 0x2e) = *(byte *)(uVar3 + 0x2e) & 0xfe;
              }
              uVar3 = uVar3 + 0x30;
            } while (uVar3 < uVar2);
          }
          else {
            do {
              if ((*(long *)(uVar3 + 8) != 0) && (uVar4 == *(ushort *)(uVar3 + 0x2c))) {
                *(byte *)(uVar3 + 0x2e) = *(byte *)(uVar3 + 0x2e) | 1;
              }
              uVar3 = uVar3 + 0x30;
            } while (uVar3 < uVar2);
          }
        }
        uVar4 = uVar4 + 1;
        if (uVar4 == uVar1) break;
        uVar3 = *(ulong *)(param_1 + 0x80);
      }
    }
    else {
      uVar3 = 0;
      do {
        if ((*(long *)(*(long *)(param_1 + 0x78) + uVar3 * 0x10 + 8) == param_2) &&
           (uVar5 = *(ulong *)(param_1 + 0x80), uVar5 < uVar2)) {
          if ((param_3 & 1) == 0) {
            do {
              if ((*(long *)(uVar5 + 8) != 0) && (uVar3 == *(ushort *)(uVar5 + 0x2c))) {
                *(byte *)(uVar5 + 0x2e) = *(byte *)(uVar5 + 0x2e) & 0xfe;
              }
              uVar5 = uVar5 + 0x30;
            } while (uVar5 < uVar2);
          }
          else {
            do {
              if ((*(long *)(uVar5 + 8) != 0) && (uVar3 == *(ushort *)(uVar5 + 0x2c))) {
                *(byte *)(uVar5 + 0x2e) = *(byte *)(uVar5 + 0x2e) | 1;
              }
              uVar5 = uVar5 + 0x30;
            } while (uVar5 < uVar2);
          }
        }
        uVar3 = uVar3 + 1;
      } while (uVar3 != uVar1);
    }
  }
  return;
}

// ==== Aska::AafHandler::HaltAnimation(char const*, bool)
// vaddr 0x1f970c8 | ghidra 0x20970c8 | size 368 | symbol _ZN4Aska10AafHandler13HaltAnimationEPKcb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10AafHandler13HaltAnimationEPKcb(long param_1,undefined8 param_2,uint param_3)

{
  int iVar1;
  uint *puVar2;
  long lVar3;
  byte *pbVar4;
  ulong uVar5;
  long lVar6;
  ulong uVar7;
  
  uVar5 = (ulong)*(ushort *)(param_1 + 0xf4);
  if (uVar5 != 0) {
    uVar7 = 0;
    lVar6 = *(long *)(param_1 + 0x80) + (ulong)*(uint *)(param_1 + 0x38) * 0x30;
    if ((param_3 & 1) == 0) {
      do {
        pbVar4 = *(byte **)(*(long *)(param_1 + 0x78) + uVar7 * 0x10);
        if ((*pbVar4 >> 2 & 1) == 0) {
          pbVar4 = pbVar4 + 8;
code_r0x020971d8:
          iVar1 = strcmp(pbVar4,param_2);
          if (iVar1 == 0) goto code_r0x020971e4;
        }
        else {
          puVar2 = *(uint **)(param_1 + 0x18);
          if (((puVar2 != (uint *)0x0) && (*(uint *)(pbVar4 + 8) < *puVar2)) &&
             (pbVar4 = (byte *)((long)puVar2 + (ulong)(*(uint *)(pbVar4 + 8) << 5) + 4),
             pbVar4 != (byte *)0x0)) goto code_r0x020971d8;
code_r0x020971e4:
          for (lVar3 = *(long *)(param_1 + 0x80); lVar3 != lVar6; lVar3 = lVar3 + 0x30) {
            if ((*(long *)(lVar3 + 8) != 0) && (uVar7 == *(ushort *)(lVar3 + 0x2c))) {
              *(byte *)(lVar3 + 0x2e) = *(byte *)(lVar3 + 0x2e) & 0xfe;
            }
          }
        }
        uVar7 = uVar7 + 1;
      } while (uVar7 != uVar5);
    }
    else {
      do {
        pbVar4 = *(byte **)(*(long *)(param_1 + 0x78) + uVar7 * 0x10);
        if ((*pbVar4 >> 2 & 1) == 0) {
          pbVar4 = pbVar4 + 8;
code_r0x02097140:
          iVar1 = strcmp(pbVar4,param_2);
          if (iVar1 == 0) goto code_r0x0209714c;
        }
        else {
          puVar2 = *(uint **)(param_1 + 0x18);
          if (((puVar2 != (uint *)0x0) && (*(uint *)(pbVar4 + 8) < *puVar2)) &&
             (pbVar4 = (byte *)((long)puVar2 + (ulong)(*(uint *)(pbVar4 + 8) << 5) + 4),
             pbVar4 != (byte *)0x0)) goto code_r0x02097140;
code_r0x0209714c:
          for (lVar3 = *(long *)(param_1 + 0x80); lVar3 != lVar6; lVar3 = lVar3 + 0x30) {
            if ((*(long *)(lVar3 + 8) != 0) && (uVar7 == *(ushort *)(lVar3 + 0x2c))) {
              *(byte *)(lVar3 + 0x2e) = *(byte *)(lVar3 + 0x2e) | 1;
            }
          }
        }
        uVar7 = uVar7 + 1;
      } while (uVar7 != uVar5);
    }
  }
  return;
}

// ==== Aska::AafHandler::HaltAnimation(Aska::IAnimatable*, bool, Aska::EnumAafControllerType)
// vaddr 0x1f97238 | ghidra 0x2097238 | size 396 | symbol _ZN4Aska10AafHandler13HaltAnimationEPNS_11IAnimatableEbNS_21EnumAafControllerTypeE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10AafHandler13HaltAnimationEPNS_11IAnimatableEbNS_21EnumAafControllerTypeE
               (long param_1,long param_2,uint param_3,char param_4)

{
  ushort uVar1;
  ulong uVar2;
  ulong uVar3;
  uint uVar4;
  ulong uVar5;
  
  uVar1 = *(ushort *)(param_1 + 0xf4);
  if (uVar1 != 0) {
    uVar3 = *(ulong *)(param_1 + 0x80);
    uVar2 = uVar3 + (ulong)*(uint *)(param_1 + 0x38) * 0x30;
    if (param_2 == 0) {
      uVar4 = 0;
      while( true ) {
        if (uVar3 < uVar2) {
          if ((param_3 & 1) == 0) {
            do {
              if ((((*(long *)(uVar3 + 8) != 0) && (uVar4 == *(ushort *)(uVar3 + 0x2c))) &&
                  (*(char **)(uVar3 + 0x10) != (char *)0x0)) &&
                 (**(char **)(uVar3 + 0x10) == param_4)) {
                *(byte *)(uVar3 + 0x2e) = *(byte *)(uVar3 + 0x2e) & 0xfe;
              }
              uVar3 = uVar3 + 0x30;
            } while (uVar3 < uVar2);
          }
          else {
            do {
              if (((*(long *)(uVar3 + 8) != 0) && (uVar4 == *(ushort *)(uVar3 + 0x2c))) &&
                 ((*(char **)(uVar3 + 0x10) != (char *)0x0 && (**(char **)(uVar3 + 0x10) == param_4)
                  ))) {
                *(byte *)(uVar3 + 0x2e) = *(byte *)(uVar3 + 0x2e) | 1;
              }
              uVar3 = uVar3 + 0x30;
            } while (uVar3 < uVar2);
          }
        }
        uVar4 = uVar4 + 1;
        if (uVar4 == uVar1) break;
        uVar3 = *(ulong *)(param_1 + 0x80);
      }
    }
    else {
      uVar3 = 0;
      do {
        if ((*(long *)(*(long *)(param_1 + 0x78) + uVar3 * 0x10 + 8) == param_2) &&
           (uVar5 = *(ulong *)(param_1 + 0x80), uVar5 < uVar2)) {
          if ((param_3 & 1) == 0) {
            do {
              if ((((*(long *)(uVar5 + 8) != 0) && (uVar3 == *(ushort *)(uVar5 + 0x2c))) &&
                  (*(char **)(uVar5 + 0x10) != (char *)0x0)) &&
                 (**(char **)(uVar5 + 0x10) == param_4)) {
                *(byte *)(uVar5 + 0x2e) = *(byte *)(uVar5 + 0x2e) & 0xfe;
              }
              uVar5 = uVar5 + 0x30;
            } while (uVar5 < uVar2);
          }
          else {
            do {
              if (((*(long *)(uVar5 + 8) != 0) && (uVar3 == *(ushort *)(uVar5 + 0x2c))) &&
                 ((*(char **)(uVar5 + 0x10) != (char *)0x0 && (**(char **)(uVar5 + 0x10) == param_4)
                  ))) {
                *(byte *)(uVar5 + 0x2e) = *(byte *)(uVar5 + 0x2e) | 1;
              }
              uVar5 = uVar5 + 0x30;
            } while (uVar5 < uVar2);
          }
        }
        uVar3 = uVar3 + 1;
      } while (uVar3 != uVar1);
    }
  }
  return;
}

// ==== Aska::AafHandler::GetControllerInterface(Aska::IAnimatable*, Aska::EnumAafDetailAttribute)
// vaddr 0x1f973c4 | ghidra 0x20973c4 | size 232 | symbol _ZN4Aska10AafHandler22GetControllerInterfaceEPNS_11IAnimatableENS_22EnumAafDetailAttributeE | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska10AafHandler22GetControllerInterfaceEPNS_11IAnimatableENS_22EnumAafDetailAttributeE
          (long param_1,long param_2,char param_3)

{
  ushort uVar1;
  ulong uVar2;
  ulong uVar3;
  ulong uVar4;
  uint uVar5;
  ulong uVar6;
  
  uVar1 = *(ushort *)(param_1 + 0xf4);
  if (uVar1 == 0) {
    return 0;
  }
  uVar5 = *(uint *)(param_1 + 0x38);
  uVar2 = *(ulong *)(param_1 + 0x80);
  uVar3 = uVar2 + (ulong)uVar5 * 0x30;
  if (param_2 == 0) {
    if (uVar5 == 0) {
      return 0;
    }
    uVar5 = 0;
    uVar4 = uVar2;
    while (((*(long *)(uVar4 + 0x18) == 0 || (uVar5 != *(ushort *)(uVar4 + 0x2c))) ||
           (*(char *)(*(long *)(uVar4 + 0x18) + 6) != param_3))) {
      uVar4 = uVar4 + 0x30;
      if ((uVar3 <= uVar4) && (uVar5 = uVar5 + 1, uVar4 = uVar2, (int)(uint)uVar1 <= (int)uVar5)) {
        return 0;
      }
    }
code_r0x02097494:
    return *(undefined8 *)(uVar4 + 8);
  }
  if (uVar5 == 0) {
    return 0;
  }
  uVar6 = 0;
  do {
    uVar4 = uVar2;
    if (*(long *)(*(long *)(param_1 + 0x78) + uVar6 * 0x10 + 8) == param_2) {
      do {
        if (((*(long *)(uVar4 + 0x18) != 0) && (uVar6 == *(ushort *)(uVar4 + 0x2c))) &&
           (*(char *)(*(long *)(uVar4 + 0x18) + 6) == param_3)) goto code_r0x02097494;
        uVar4 = uVar4 + 0x30;
      } while (uVar4 < uVar3);
    }
    uVar6 = uVar6 + 1;
    if ((long)(ulong)uVar1 <= (long)uVar6) {
      return 0;
    }
  } while( true );
}

// ==== Aska::AafHandler::LocalGetControllerInterface(Aska::IAnimatable*, Aska::EnumAafDetailAttribute)
// vaddr 0x1f974ac | ghidra 0x20974ac | size 216 | symbol _ZN4Aska10AafHandler27LocalGetControllerInterfaceEPNS_11IAnimatableENS_22EnumAafDetailAttributeE | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska10AafHandler27LocalGetControllerInterfaceEPNS_11IAnimatableENS_22EnumAafDetailAttributeE
          (long param_1,long param_2,char param_3)

{
  uint uVar1;
  ushort uVar2;
  ulong uVar3;
  ulong uVar4;
  ulong uVar5;
  uint uVar6;
  ulong uVar7;
  
  uVar2 = *(ushort *)(param_1 + 0xf4);
  if (uVar2 == 0) {
    return 0;
  }
  uVar1 = *(uint *)(param_1 + 0x38);
  uVar3 = *(ulong *)(param_1 + 0x80);
  uVar4 = uVar3 + (ulong)uVar1 * 0x30;
  if (param_2 == 0) {
    uVar6 = 0;
    do {
      uVar5 = uVar3;
      if (uVar1 != 0) {
        do {
          if (((*(long *)(uVar5 + 0x18) != 0) && (uVar6 == *(ushort *)(uVar5 + 0x2c))) &&
             (*(char *)(*(long *)(uVar5 + 0x18) + 6) == param_3)) {
code_r0x0209757c:
            return *(undefined8 *)(uVar5 + 8);
          }
          uVar5 = uVar5 + 0x30;
        } while (uVar5 < uVar4);
      }
      uVar6 = uVar6 + 1;
      if ((int)(uint)uVar2 <= (int)uVar6) {
        return 0;
      }
    } while( true );
  }
  uVar7 = 0;
  do {
    if ((*(long *)(*(long *)(param_1 + 0x78) + uVar7 * 0x10 + 8) == param_2) &&
       (uVar5 = uVar3, uVar1 != 0)) {
      do {
        if ((*(long *)(uVar5 + 0x18) != 0) &&
           ((uVar7 == *(ushort *)(uVar5 + 0x2c) &&
            (*(char *)(*(long *)(uVar5 + 0x18) + 6) == param_3)))) goto code_r0x0209757c;
        uVar5 = uVar5 + 0x30;
      } while (uVar5 < uVar4);
    }
    uVar7 = uVar7 + 1;
    if ((long)(ulong)uVar2 <= (long)uVar7) {
      return 0;
    }
  } while( true );
}

// ==== Aska::AafHandler::GetControllerInterface(char const*, Aska::EnumAafDetailAttribute)
// vaddr 0x1f97584 | ghidra 0x2097584 | size 236 | symbol _ZN4Aska10AafHandler22GetControllerInterfaceEPKcNS_22EnumAafDetailAttributeE | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska10AafHandler22GetControllerInterfaceEPKcNS_22EnumAafDetailAttributeE
          (long param_1,undefined8 param_2,char param_3)

{
  long lVar1;
  ulong uVar2;
  uint uVar3;
  ushort uVar4;
  int iVar5;
  uint *puVar6;
  ulong uVar7;
  byte *pbVar8;
  ulong uVar9;
  
  uVar4 = *(ushort *)(param_1 + 0xf4);
  if ((ulong)uVar4 != 0) {
    uVar3 = *(uint *)(param_1 + 0x38);
    lVar1 = *(long *)(param_1 + 0x78);
    uVar2 = *(ulong *)(param_1 + 0x80);
    uVar9 = 0;
    do {
      pbVar8 = *(byte **)(lVar1 + uVar9 * 0x10);
      if ((*pbVar8 >> 2 & 1) == 0) {
        pbVar8 = pbVar8 + 8;
code_r0x02097600:
        iVar5 = strcmp(pbVar8,param_2);
        if (iVar5 == 0) goto code_r0x0209760c;
      }
      else {
        puVar6 = *(uint **)(param_1 + 0x18);
        if (((puVar6 != (uint *)0x0) && (*(uint *)(pbVar8 + 8) < *puVar6)) &&
           (pbVar8 = (byte *)((long)puVar6 + (ulong)(*(uint *)(pbVar8 + 8) << 5) + 4),
           pbVar8 != (byte *)0x0)) goto code_r0x02097600;
code_r0x0209760c:
        uVar7 = uVar2;
        if (uVar3 != 0) {
          do {
            if (((uVar9 == *(ushort *)(uVar7 + 0x2c)) && (*(long *)(uVar7 + 0x18) != 0)) &&
               (*(char *)(*(long *)(uVar7 + 0x18) + 6) == param_3)) {
              return *(undefined8 *)(uVar7 + 8);
            }
            uVar7 = uVar7 + 0x30;
          } while (uVar7 < uVar2 + (ulong)uVar3 * 0x30);
        }
      }
      uVar9 = uVar9 + 1;
    } while ((long)uVar9 < (long)(ulong)uVar4);
  }
  return 0;
}

// ==== Aska::AafHandler::GetAllControllerInterface(Aska::IController**, int, Aska::IAnimatable*, Aska::EnumAafControllerType, int*)
// vaddr 0x1f97670 | ghidra 0x2097670 | size 464 | symbol _ZN4Aska10AafHandler25GetAllControllerInterfaceEPPNS_11IControllerEiPNS_11IAnimatableENS_21EnumAafControllerTypeEPi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10AafHandler25GetAllControllerInterfaceEPPNS_11IControllerEiPNS_11IAnimatableENS_21EnumAafControllerTypeEPi
               (long param_1,long param_2,int param_3,long param_4,char param_5,int *param_6)

{
  ushort uVar1;
  ulong uVar2;
  ulong uVar3;
  uint uVar4;
  ulong uVar5;
  int iVar6;
  int iVar7;
  
  uVar1 = *(ushort *)(param_1 + 0xf4);
  if (uVar1 == 0) {
    iVar6 = 0;
  }
  else {
    uVar3 = *(ulong *)(param_1 + 0x80);
    uVar2 = uVar3 + (ulong)*(uint *)(param_1 + 0x38) * 0x30;
    if (param_4 == 0) {
      iVar7 = 0;
      uVar4 = 0;
      while( true ) {
        if (uVar3 < uVar2) {
          iVar6 = iVar7;
          if (param_2 == 0) {
            do {
              if (((uVar4 == *(ushort *)(uVar3 + 0x2c)) && (*(char **)(uVar3 + 0x10) != (char *)0x0)
                  ) && (**(char **)(uVar3 + 0x10) == param_5)) {
                iVar7 = iVar7 + 1;
              }
              uVar3 = uVar3 + 0x30;
            } while (uVar3 < uVar2);
          }
          else {
            do {
              iVar7 = iVar6;
              if (((uVar4 == *(ushort *)(uVar3 + 0x2c)) && (*(char **)(uVar3 + 0x10) != (char *)0x0)
                  ) && (**(char **)(uVar3 + 0x10) == param_5)) {
                if (*(long *)(uVar3 + 8) == 0) {
                  iVar7 = iVar6 + 1;
                }
                else {
                  *(long *)(param_2 + (long)iVar6 * 8) = *(long *)(uVar3 + 8);
                  iVar7 = iVar6 + 1;
                  if (param_3 <= iVar6 + 1) goto joined_r0x02097768;
                }
              }
              uVar3 = uVar3 + 0x30;
              iVar6 = iVar7;
            } while (uVar3 < uVar2);
          }
        }
        uVar4 = uVar4 + 1;
        iVar6 = iVar7;
        if ((int)(uint)uVar1 <= (int)uVar4) break;
        uVar3 = *(ulong *)(param_1 + 0x80);
      }
    }
    else {
      uVar3 = 0;
      iVar6 = 0;
      do {
        if ((*(long *)(*(long *)(param_1 + 0x78) + uVar3 * 0x10 + 8) == param_4) &&
           (uVar5 = *(ulong *)(param_1 + 0x80), uVar5 < uVar2)) {
          if (param_2 == 0) {
            do {
              if (((uVar3 == *(ushort *)(uVar5 + 0x2c)) && (*(char **)(uVar5 + 0x10) != (char *)0x0)
                  ) && (**(char **)(uVar5 + 0x10) == param_5)) {
                iVar6 = iVar6 + 1;
              }
              uVar5 = uVar5 + 0x30;
            } while (uVar5 < uVar2);
          }
          else {
            do {
              iVar7 = iVar6;
              if (((uVar3 == *(ushort *)(uVar5 + 0x2c)) && (*(char **)(uVar5 + 0x10) != (char *)0x0)
                  ) && (**(char **)(uVar5 + 0x10) == param_5)) {
                if (*(long *)(uVar5 + 8) == 0) {
                  iVar7 = iVar6 + 1;
                }
                else {
                  *(long *)(param_2 + (long)iVar6 * 8) = *(long *)(uVar5 + 8);
                  iVar7 = iVar6 + 1;
                  if (param_3 <= iVar6 + 1) goto joined_r0x02097768;
                }
              }
              iVar6 = iVar7;
              uVar5 = uVar5 + 0x30;
            } while (uVar5 < uVar2);
          }
        }
        uVar3 = uVar3 + 1;
      } while ((long)uVar3 < (long)(ulong)uVar1);
    }
  }
joined_r0x02097768:
  if (param_6 != (int *)0x0) {
    *param_6 = iVar6;
  }
  return;
}

// ==== Aska::AafHandler::GetControllerInterface(Aska::IAnimatable*, Aska::EnumAafControllerType, int)
// vaddr 0x1f97840 | ghidra 0x2097840 | size 220 | symbol _ZN4Aska10AafHandler22GetControllerInterfaceEPNS_11IAnimatableENS_21EnumAafControllerTypeEi | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska10AafHandler22GetControllerInterfaceEPNS_11IAnimatableENS_21EnumAafControllerTypeEi
          (long param_1,long param_2,char param_3,int param_4)

{
  bool bVar1;
  uint uVar2;
  ushort uVar3;
  int iVar4;
  ulong uVar5;
  ulong uVar6;
  ulong uVar7;
  uint uVar8;
  ulong uVar9;
  
  uVar3 = *(ushort *)(param_1 + 0xf4);
  if (uVar3 != 0) {
    uVar2 = *(uint *)(param_1 + 0x38);
    uVar5 = *(ulong *)(param_1 + 0x80);
    uVar6 = uVar5 + (ulong)uVar2 * 0x30;
    if (param_2 == 0) {
      uVar8 = 0;
      do {
        uVar7 = uVar5;
        if (uVar2 != 0) {
          do {
            if ((((uVar8 == *(ushort *)(uVar7 + 0x2c)) && (*(char **)(uVar7 + 0x10) != (char *)0x0))
                && (**(char **)(uVar7 + 0x10) == param_3)) &&
               (bVar1 = param_4 < 1, param_4 = param_4 + -1, bVar1)) goto code_r0x02097914;
            uVar7 = uVar7 + 0x30;
          } while (uVar7 < uVar6);
        }
        uVar8 = uVar8 + 1;
      } while ((int)uVar8 < (int)(uint)uVar3);
    }
    else {
      uVar9 = 0;
      do {
        if ((*(long *)(*(long *)(param_1 + 0x78) + uVar9 * 0x10 + 8) == param_2) &&
           (uVar7 = uVar5, iVar4 = param_4, uVar2 != 0)) {
          do {
            param_4 = iVar4;
            if (((uVar9 == *(ushort *)(uVar7 + 0x2c)) &&
                ((*(char **)(uVar7 + 0x10) != (char *)0x0 && (**(char **)(uVar7 + 0x10) == param_3))
                )) && (param_4 = iVar4 + -1, iVar4 < 1)) {
code_r0x02097914:
              return *(undefined8 *)(uVar7 + 8);
            }
            uVar7 = uVar7 + 0x30;
            iVar4 = param_4;
          } while (uVar7 < uVar6);
        }
        uVar9 = uVar9 + 1;
      } while ((long)uVar9 < (long)(ulong)uVar3);
    }
  }
  return 0;
}

// ==== Aska::AafHandler::GetControllerInterface(char const*, Aska::EnumAafControllerType, int)
// vaddr 0x1f9791c | ghidra 0x209791c | size 260 | symbol _ZN4Aska10AafHandler22GetControllerInterfaceEPKcNS_21EnumAafControllerTypeEi | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska10AafHandler22GetControllerInterfaceEPKcNS_21EnumAafControllerTypeEi
          (long param_1,undefined8 param_2,char param_3,int param_4)

{
  long lVar1;
  ulong uVar2;
  uint uVar3;
  ushort uVar4;
  int iVar5;
  uint *puVar6;
  byte *pbVar7;
  ulong uVar8;
  ulong uVar9;
  
  uVar4 = *(ushort *)(param_1 + 0xf4);
  if ((ulong)uVar4 != 0) {
    uVar3 = *(uint *)(param_1 + 0x38);
    lVar1 = *(long *)(param_1 + 0x78);
    uVar2 = *(ulong *)(param_1 + 0x80);
    uVar9 = 0;
    do {
      pbVar7 = *(byte **)(lVar1 + uVar9 * 0x10);
      if ((*pbVar7 >> 2 & 1) == 0) {
        pbVar7 = pbVar7 + 8;
code_r0x020979a0:
        iVar5 = strcmp(pbVar7,param_2);
        if (iVar5 == 0) goto code_r0x020979ac;
      }
      else {
        puVar6 = *(uint **)(param_1 + 0x18);
        if (((puVar6 != (uint *)0x0) && (*(uint *)(pbVar7 + 8) < *puVar6)) &&
           (pbVar7 = (byte *)((long)puVar6 + (ulong)(*(uint *)(pbVar7 + 8) << 5) + 4),
           pbVar7 != (byte *)0x0)) goto code_r0x020979a0;
code_r0x020979ac:
        if (uVar3 != 0) {
          iVar5 = 0;
          uVar8 = uVar2;
          do {
            if ((uVar9 == *(ushort *)(uVar8 + 0x2c)) && (**(char **)(uVar8 + 0x10) == param_3)) {
              if (iVar5 == param_4) {
                return *(undefined8 *)(uVar8 + 8);
              }
              iVar5 = iVar5 + 1;
            }
            uVar8 = uVar8 + 0x30;
          } while (uVar8 < uVar2 + (ulong)uVar3 * 0x30);
        }
      }
      uVar9 = uVar9 + 1;
    } while ((long)uVar9 < (long)(ulong)uVar4);
  }
  return 0;
}

// ==== Aska::AafHandler::DisableControllers(Aska::EnumAafControllerType)
// vaddr 0x1f97a20 | ghidra 0x2097a20 | size 72 | symbol _ZN4Aska10AafHandler18DisableControllersENS_21EnumAafControllerTypeE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10AafHandler18DisableControllersENS_21EnumAafControllerTypeE
               (long param_1,ushort param_2)

{
  byte *pbVar1;
  long lVar2;
  
  if (*(uint *)(param_1 + 0x38) != 0) {
    pbVar1 = (byte *)(*(long *)(param_1 + 0x80) + 0x2e);
    lVar2 = (ulong)*(uint *)(param_1 + 0x38) * 0x30;
    do {
      if (param_2 == **(byte **)(pbVar1 + -0x1e)) {
        *pbVar1 = *pbVar1 | 1;
      }
      lVar2 = lVar2 + -0x30;
      pbVar1 = pbVar1 + 0x30;
    } while (lVar2 != 0);
  }
  return;
}

// ==== Aska::AafHandler::DetachController(Aska::IAnimatable*)
// vaddr 0x1f97a68 | ghidra 0x2097a68 | size 128 | symbol _ZN4Aska10AafHandler16DetachControllerEPNS_11IAnimatableE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10AafHandler16DetachControllerEPNS_11IAnimatableE(long param_1,long param_2)

{
  ushort uVar1;
  ulong uVar2;
  long *plVar3;
  byte *pbVar4;
  long lVar5;
  
  if ((((*(uint *)(param_1 + 0xc) ^ 0xffffffff) & 0x82) == 0) &&
     (uVar1 = *(ushort *)(param_1 + 0xf4), (ulong)uVar1 != 0)) {
    uVar2 = 0;
    do {
      plVar3 = (long *)(*(long *)(param_1 + 0x78) + uVar2 * 0x10 + 8);
      if (*plVar3 == param_2) {
        *plVar3 = 0;
        if (*(uint *)(param_1 + 0x38) != 0) {
          pbVar4 = (byte *)(*(long *)(param_1 + 0x80) + 0x2e);
          lVar5 = (ulong)*(uint *)(param_1 + 0x38) * 0x30;
          do {
            if (uVar2 == *(ushort *)(pbVar4 + -2)) {
              *pbVar4 = *pbVar4 | 2;
            }
            lVar5 = lVar5 + -0x30;
            pbVar4 = pbVar4 + 0x30;
          } while (lVar5 != 0);
        }
      }
      uVar2 = uVar2 + 1;
    } while (uVar2 != uVar1);
  }
  return;
}

// ==== Aska::AafHandler::DetachControllers(Aska::EnumAafControllerType)
// vaddr 0x1f97ae8 | ghidra 0x2097ae8 | size 88 | symbol _ZN4Aska10AafHandler17DetachControllersENS_21EnumAafControllerTypeE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10AafHandler17DetachControllersENS_21EnumAafControllerTypeE(long param_1,char param_2)

{
  byte *pbVar1;
  long lVar2;
  
  if ((((*(uint *)(param_1 + 0xc) ^ 0xffffffff) & 0x82) == 0) && (*(uint *)(param_1 + 0x38) != 0)) {
    pbVar1 = (byte *)(*(long *)(param_1 + 0x80) + 0x2e);
    lVar2 = (ulong)*(uint *)(param_1 + 0x38) * 0x30;
    do {
      if ((*(char **)(pbVar1 + -0x1e) != (char *)0x0) && (**(char **)(pbVar1 + -0x1e) == param_2)) {
        *pbVar1 = *pbVar1 | 2;
      }
      lVar2 = lVar2 + -0x30;
      pbVar1 = pbVar1 + 0x30;
    } while (lVar2 != 0);
  }
  return;
}

// ==== Aska::AafHandler::DetachAllControllers()
// vaddr 0x1f97b40 | ghidra 0x2097b40 | size 212 | symbol _ZN4Aska10AafHandler20DetachAllControllersEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10AafHandler20DetachAllControllersEv(long param_1)

{
  uint uVar1;
  ulong uVar2;
  long lVar3;
  long lVar4;
  ulong uVar5;
  byte *pbVar6;
  ulong uVar7;
  
  if (((*(uint *)(param_1 + 0xc) ^ 0xffffffff) & 0x82) == 0) {
    uVar2 = (ulong)*(ushort *)(param_1 + 0xf4);
    if (uVar2 != 0) {
      lVar3 = 8;
      do {
        uVar2 = uVar2 - 1;
        *(undefined8 *)(*(long *)(param_1 + 0x78) + lVar3) = 0;
        lVar3 = lVar3 + 0x10;
      } while (uVar2 != 0);
    }
    uVar1 = *(uint *)(param_1 + 0x38);
    if (uVar1 != 0) {
      lVar4 = *(long *)(param_1 + 0x80);
      uVar2 = ((ulong)uVar1 * 0x30 - 0x30) / 0x30 + 1;
      lVar3 = lVar4;
      if ((1 < uVar2) && (uVar5 = uVar2 & 0xffffffffffffffe, uVar5 != 0)) {
        pbVar6 = (byte *)(lVar4 + 0x5e);
        uVar7 = uVar5;
        do {
          uVar7 = uVar7 - 2;
          pbVar6[-0x30] = pbVar6[-0x30] | 2;
          *pbVar6 = *pbVar6 | 2;
          pbVar6 = pbVar6 + 0x60;
        } while (uVar7 != 0);
        lVar3 = lVar4 + uVar5 * 0x30;
        if (uVar2 == uVar5) {
          return;
        }
      }
      do {
        *(byte *)(lVar3 + 0x2e) = *(byte *)(lVar3 + 0x2e) | 2;
        lVar3 = lVar3 + 0x30;
      } while (lVar4 + (ulong)uVar1 * 0x30 != lVar3);
    }
  }
  return;
}

// ==== Aska::AafHandler::AttachController(Aska::IAnimatable*, char const*)
// vaddr 0x1f97c14 | ghidra 0x2097c14 | size 252 | symbol _ZN4Aska10AafHandler16AttachControllerEPNS_11IAnimatableEPKc | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10AafHandler16AttachControllerEPNS_11IAnimatableEPKc
               (long param_1,undefined8 param_2,undefined8 param_3)

{
  uint uVar1;
  ushort uVar2;
  int iVar3;
  uint *puVar4;
  long lVar5;
  byte *pbVar6;
  long lVar7;
  undefined8 *puVar8;
  
  uVar2 = *(ushort *)(param_1 + 0xf4);
  if ((ulong)uVar2 == 0) {
    lVar7 = 0;
    uVar1 = *(uint *)(param_1 + 0x38);
  }
  else {
    lVar7 = 0;
    puVar8 = (undefined8 *)(*(long *)(param_1 + 0x78) + 8);
    do {
      pbVar6 = (byte *)puVar8[-1];
      if ((*pbVar6 >> 2 & 1) == 0) {
        pbVar6 = pbVar6 + 8;
code_r0x02097c80:
        iVar3 = strcmp(pbVar6,param_3);
        if (iVar3 == 0) {
          *puVar8 = param_2;
          uVar1 = *(uint *)(param_1 + 0x38);
          goto joined_r0x02097cc0;
        }
      }
      else {
        puVar4 = *(uint **)(param_1 + 0x18);
        if (((puVar4 != (uint *)0x0) && (*(uint *)(pbVar6 + 8) < *puVar4)) &&
           (pbVar6 = (byte *)((long)puVar4 + (ulong)(*(uint *)(pbVar6 + 8) << 5) + 4),
           pbVar6 != (byte *)0x0)) goto code_r0x02097c80;
      }
      lVar7 = lVar7 + 1;
      puVar8 = puVar8 + 2;
    } while (lVar7 < (long)(ulong)uVar2);
    uVar1 = *(uint *)(param_1 + 0x38);
  }
joined_r0x02097cc0:
  if (uVar1 != 0) {
    lVar5 = (ulong)uVar1 * 0x30;
    pbVar6 = (byte *)(*(long *)(param_1 + 0x80) + 0x2e);
    do {
      if ((uint)lVar7 == (uint)*(ushort *)(pbVar6 + -2)) {
        *pbVar6 = *pbVar6 & 0xfd;
      }
      lVar5 = lVar5 + -0x30;
      pbVar6 = pbVar6 + 0x30;
    } while (lVar5 != 0);
  }
  return;
}

// ==== Aska::AafHandler::AttachController(char const*)
// vaddr 0x1f97d10 | ghidra 0x2097d10 | size 272 | symbol _ZN4Aska10AafHandler16AttachControllerEPKc | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska10AafHandler16AttachControllerEPKc(long param_1,undefined8 param_2)

{
  ushort uVar1;
  int iVar2;
  undefined8 uVar3;
  uint *puVar4;
  byte *pbVar5;
  long lVar6;
  long lVar7;
  long lVar8;
  long lVar9;
  
  lVar6 = *(long *)(param_1 + 0x30);
  if ((lVar6 != 0) && (uVar1 = *(ushort *)(param_1 + 0xf4), (ulong)uVar1 != 0)) {
    lVar9 = *(long *)(param_1 + 0x78);
    lVar8 = 0;
    lVar7 = 0;
    do {
      pbVar5 = *(byte **)(lVar9 + lVar8);
      if ((*pbVar5 >> 2 & 1) == 0) {
        pbVar5 = pbVar5 + 8;
code_r0x02097d84:
        iVar2 = strcmp(pbVar5,param_2);
        if (iVar2 == 0) {
          uVar3 = Aska::AsfHandler::QuickSearchByNameEx(char const*) const(lVar6,pbVar5);
          *(undefined8 *)(*(long *)(param_1 + 0x78) + lVar8 + 8) = uVar3;
          if (*(uint *)(param_1 + 0x38) != 0) {
            lVar6 = (ulong)*(uint *)(param_1 + 0x38) * 0x30;
            pbVar5 = (byte *)(*(long *)(param_1 + 0x80) + 0x2e);
            do {
              if ((uint)*(ushort *)(pbVar5 + -2) == (uint)lVar7) {
                *pbVar5 = *pbVar5 & 0xfd;
              }
              lVar6 = lVar6 + -0x30;
              pbVar5 = pbVar5 + 0x30;
            } while (lVar6 != 0);
          }
          return 1;
        }
      }
      else {
        puVar4 = *(uint **)(param_1 + 0x18);
        if (((puVar4 != (uint *)0x0) && (*(uint *)(pbVar5 + 8) < *puVar4)) &&
           (pbVar5 = (byte *)((long)puVar4 + (ulong)(*(uint *)(pbVar5 + 8) << 5) + 4),
           pbVar5 != (byte *)0x0)) goto code_r0x02097d84;
      }
      lVar7 = lVar7 + 1;
      lVar8 = lVar8 + 0x10;
    } while (lVar7 < (long)(ulong)uVar1);
  }
  return 0;
}

// ==== Aska::AafHandler::MakeBiArray(float)
// vaddr 0x1f97e20 | ghidra 0x2097e20 | size 272 | symbol _ZN4Aska10AafHandler11MakeBiArrayEf | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10AafHandler11MakeBiArrayEf(undefined8 param_1,long param_2)

{
  long lVar1;
  undefined8 uVar2;
  uint uVar3;
  int iVar4;
  ulong uVar5;
  long lVar6;
  long lVar7;
  ulong uVar8;
  
  uVar3 = *(uint *)(param_2 + 0x3c);
  if ((uVar3 != 0) && (*(int *)(param_2 + 0x48) != 0)) {
    lVar1 = *(long *)(param_2 + 0xb0);
    uVar2 = *(undefined8 *)(param_2 + 0xb8);
    iVar4 = *(int *)(param_2 + 0xa8) << 2;
    memset(lVar1,0,iVar4);
    lVar7 = 0;
    uVar8 = 0;
    do {
      lVar6 = *(long *)(param_2 + 0x88) + lVar7;
      if ((*(byte *)(lVar6 + 0x2e) & 3) == 0) {
        if ((((float)param_1 < *(float *)(*(long *)(lVar6 + 0x18) + 0xc)) ||
            (*(float *)(*(long *)(lVar6 + 0x18) + 0x10) < (float)param_1)) ||
           (uVar5 = (**(code **)(**(long **)(lVar6 + 8) + 0x108))(param_1), (uVar5 & 1) != 0)) {
          lVar6 = (uVar8 >> 5 & 0x7ffffff) * 4;
          *(uint *)(lVar1 + lVar6) = *(uint *)(lVar1 + lVar6) | 1 << (ulong)((uint)uVar8 & 0x1f);
        }
      }
      uVar8 = uVar8 + 1;
      lVar7 = lVar7 + 0x30;
    } while (uVar3 != uVar8);
    (*(code *)PTR_memcpy_02cae5d8)(uVar2,lVar1,iVar4);
    return;
  }
  return;
}

// ==== Aska::AafHandler::RenewalAllControllerCache(float)
// vaddr 0x1f97f30 | ghidra 0x2097f30 | size 212 | symbol _ZN4Aska10AafHandler25RenewalAllControllerCacheEf | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10AafHandler25RenewalAllControllerCacheEf(float param_1,long param_2)

{
  int iVar1;
  ushort uVar2;
  uint uVar3;
  long lVar4;
  long lVar5;
  uint uVar6;
  uint uVar7;
  long lVar8;
  float fVar9;
  
  iVar1 = *(int *)(param_2 + 0x48);
  if (iVar1 == 0) {
    return;
  }
  lVar5 = *(long *)(param_2 + 0x28);
  lVar4 = 0;
  uVar2 = *(ushort *)(lVar5 + 0xe);
  uVar6 = (uint)uVar2;
  if ((uVar2 == 0) || (*(long *)(param_2 + 0x118) == 0)) {
    lVar8 = 0;
    fVar9 = param_1;
  }
  else {
    fVar9 = param_1 / *(float *)(lVar5 + 0x2c);
    if (0.0 <= fVar9) {
      uVar7 = (uint)fVar9;
      fVar9 = *(float *)(lVar5 + 0x10);
      uVar3 = uVar6 - 1;
      if ((uVar6 != uVar7 && (int)uVar7 <= (int)(uint)uVar2) && param_1 <= *(float *)(lVar5 + 0x10))
      {
        fVar9 = param_1;
        uVar3 = uVar7;
      }
      lVar8 = (long)(int)uVar3;
    }
    else {
      lVar8 = 0;
      fVar9 = 0.0;
    }
    lVar4 = *(long *)(*(long *)(param_2 + 0x118) + lVar8 * 8);
    lVar8 = *(long *)(param_2 + 0x10) + (ulong)*(uint *)(lVar5 + 0x28) + lVar8 * 0xc;
  }
  if (uVar6 == 0) {
    lVar4 = *(long *)(param_2 + 0xe0);
  }
  else {
    if ((lVar4 == 0) && (*(short *)(lVar5 + 8) != 0)) {
      return;
    }
    iVar1 = *(int *)(lVar8 + 8);
    *(long *)(param_2 + 0xe0) = lVar4;
    *(int *)(param_2 + 0x48) = iVar1;
  }
  (*(code *)
    PTR__ZN4Aska10AafHandler34Function_RenewalAllControllerCacheEfPjS1_jPNS_17AafControllerInfoEjPNS_25FrameSortDataForSearchOldEjb_02cae0f0
  )(fVar9,*(undefined8 *)(param_2 + 0xb8),*(undefined8 *)(param_2 + 0xb0),
    *(undefined4 *)(param_2 + 0xa8),*(undefined8 *)(param_2 + 0x88),*(undefined4 *)(param_2 + 0x3c),
    lVar4,iVar1,*(uint *)(param_2 + 0xc) >> 6 & 1);
  return;
}

// ==== Aska::AafHandler::CalcRuntimeMemorySize0(unsigned int&, unsigned int&, unsigned int&, void const*, Aska::AafHeader*&)
// vaddr 0x1f98014 | ghidra 0x2098014 | size 300 | symbol _ZN4Aska10AafHandler22CalcRuntimeMemorySize0ERjS1_S1_PKvRPNS_9AafHeaderE | lib libSOA-3.7.0.so | 2026-10-04
int _ZN4Aska10AafHandler22CalcRuntimeMemorySize0ERjS1_S1_PKvRPNS_9AafHeaderE
              (uint *param_1,int *param_2,uint *param_3,int *param_4,long *param_5)

{
  ushort uVar1;
  uint uVar2;
  int iVar3;
  ulong uVar4;
  long lVar5;
  undefined *puStack_40;
  long lStack_38;
  
  if (param_4 == (int *)0x0) {
    return 0;
  }
  if (*param_4 == 0x41414620) {
    param_4 = param_4 + 4;
    puStack_40 = PTR__ZTVN4Aska10ArfHandlerE_02cbeb70 + 0x10;
    lStack_38 = 0;
    uVar4 = Aska::ArfHandler::Attach(Aska::AFF::AskaResource const*)(&puStack_40,param_4);
    if ((uVar4 & 1) == 0) {
      *param_5 = (long)param_4;
    }
    else {
      if ((lStack_38 == 0) || (*(uint *)(lStack_38 + 0xc) == 0)) {
        *param_5 = 0;
        return -1;
      }
      param_4 = (int *)(lStack_38 + (ulong)*(uint *)(lStack_38 + 0xc));
      *param_5 = (long)param_4;
      if (param_4 == (int *)0x0) goto code_r0x0209808c;
    }
    if ((short)*param_4 == 0x2e) {
      *param_1 = (uint)*(ushort *)(param_4 + 1);
      lVar5 = *param_5;
      *param_2 = (uint)*(ushort *)(lVar5 + 8) + (uint)*(ushort *)(lVar5 + 6) +
                 (uint)*(ushort *)(lVar5 + 10);
      uVar1 = *(ushort *)(*param_5 + 8);
      *param_3 = (uint)uVar1;
      uVar2 = *(ushort *)(*param_5 + 8) + 0x1f >> 5;
      iVar3 = *param_2 * 0x30 + *param_1 * 0x10 + (uint)*(ushort *)(*param_5 + 0xe) * 8;
      if (uVar2 != 0) {
        iVar3 = iVar3 + (uint)uVar1 * 0xc + uVar2 * 8;
      }
    }
    else {
      iVar3 = -2;
    }
  }
  else {
code_r0x0209808c:
    iVar3 = -1;
  }
  return iVar3;
}

// ==== Aska::AafHandler::SearchModifierTarget(char const*, int*, Aska::AsfHandler*)
// vaddr 0x1f98140 | ghidra 0x2098140 | size 72 | symbol _ZN4Aska10AafHandler20SearchModifierTargetEPKcPiPNS_10AsfHandlerE | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska10AafHandler20SearchModifierTargetEPKcPiPNS_10AsfHandlerE
          (undefined8 param_1,undefined8 param_2,undefined4 *param_3,undefined8 param_4)

{
  ulong uVar1;
  undefined8 uStack_20;
  undefined4 uStack_14;
  
  uVar1 = Aska::AsfHandler::GetModifierAnimationId(char const*, Aska::IAnimatable**, int*) const(param_4,param_2,&uStack_20,&uStack_14);
  if ((uVar1 & 1) == 0) {
    uStack_20 = 0;
  }
  else if (param_3 != (undefined4 *)0x0) {
    *param_3 = uStack_14;
  }
  return uStack_20;
}

// ==== Aska::AafHandler::PrepareForComplement()
// vaddr 0x1f98188 | ghidra 0x2098188 | size 136 | symbol _ZN4Aska10AafHandler20PrepareForComplementEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska10AafHandler20PrepareForComplementEv(long param_1)

{
  undefined8 uVar1;
  undefined8 *puVar2;
  long lVar3;
  long lStack_28;
  
  if ((*(char *)(param_1 + 0x70) == '\0') || (*(char *)(param_1 + 0x72) != '\0')) {
    uVar1 = 1;
  }
  else {
    lStack_28 = *(long *)(param_1 + 0x68);
    if (lStack_28 == 0) {
      uVar1 = 0;
    }
    else {
      if (*(uint *)(param_1 + 0x38) != 0) {
        lVar3 = (ulong)*(uint *)(param_1 + 0x38) * 0x30;
        puVar2 = (undefined8 *)(*(long *)(param_1 + 0x80) + 8);
        do {
          (**(code **)(*(long *)*puVar2 + 0xd0))((long *)*puVar2,&lStack_28);
          lVar3 = lVar3 + -0x30;
          puVar2 = puVar2 + 6;
        } while (lVar3 != 0);
      }
      uVar1 = 1;
      *(undefined1 *)(param_1 + 0x72) = 1;
    }
  }
  return uVar1;
}

// ==== Aska::AafHandler::CalcDifferenceOfValue(void*, unsigned long, float, float)
// vaddr 0x1f98210 | ghidra 0x2098210 | size 248 | symbol _ZN4Aska10AafHandler21CalcDifferenceOfValueEPvmff | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10AafHandler21CalcDifferenceOfValueEPvmff
               (undefined8 param_1,undefined8 param_2,long param_3,undefined8 param_4,long param_5)

{
  undefined4 uVar1;
  long lVar2;
  
  lVar2 = *(long *)(param_3 + 0x88) + param_5 * 0x30;
  uVar1 = (**(code **)(**(long **)(lVar2 + 8) + 0x28))();
  switch(uVar1) {
  case 0:
  case 1:
  case 2:
    (*(code *)PTR__ZN4Aska10AafHandler21CalcDifferenceOfValueEPfPNS_17AafControllerInfoEff_02c9fa70)
              (param_1,param_2,param_3,param_4,lVar2);
    return;
  case 3:
  case 4:
    (*(code *)PTR__ZN4Aska10AafHandler21CalcDifferenceOfValueEPiPNS_17AafControllerInfoEff_02cb6848)
              (param_1,param_2,param_3,param_4,lVar2);
    return;
  case 5:
  case 6:
  case 7:
  case 8:
  case 9:
  case 10:
    (*(code *)
      PTR__ZN4Aska10AafHandler21CalcDifferenceOfValueEPNS_6VectorEPNS_17AafControllerInfoEff_02c9b1e8
    )(param_1,param_2,param_3,param_4,lVar2);
    return;
  case 0xb:
  case 0xc:
  case 0xd:
    (*(code *)
      PTR__ZN4Aska10AafHandler21CalcDifferenceOfValueEPNS_10QuaternionEPNS_17AafControllerInfoEff_02cb5708
    )(param_1,param_2,param_3,param_4,lVar2);
    return;
  default:
    return;
  }
}

// ==== Aska::AafHandler::CalcDifferenceOfValue(float*, Aska::AafControllerInfo*, float, float)
// vaddr 0x1f98308 | ghidra 0x2098308 | size 492 | symbol _ZN4Aska10AafHandler21CalcDifferenceOfValueEPfPNS_17AafControllerInfoEff | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10AafHandler21CalcDifferenceOfValueEPfPNS_17AafControllerInfoEff
               (float param_1,float param_2,long param_3,float *param_4,long param_5)

{
  uint *puVar1;
  uint uVar2;
  int iVar3;
  long *plVar4;
  long lVar5;
  uint *puVar6;
  ushort *puVar7;
  long lVar8;
  ulong uVar9;
  long lVar10;
  float fVar11;
  float fStack_48;
  float fStack_44;
  
  if ((*(byte *)(param_3 + 0xc) >> 6 & 1) == 0) {
    uVar2 = *(uint *)(param_3 + 0x48);
    if (uVar2 != 0) {
      lVar10 = *(long *)(param_3 + 0xe0);
      lVar5 = param_5 - *(long *)(param_3 + 0x88) >> 4;
      uVar9 = 0;
      do {
        puVar6 = (uint *)(lVar10 + uVar9 * 8);
        fVar11 = (float)puVar6[1];
        if (fVar11 == param_1) {
          puVar1 = (uint *)((ulong)*puVar6 + (long)puVar6);
          if (*puVar1 != 0) {
            puVar7 = (ushort *)((long)puVar1 + 6);
            lVar8 = (ulong)*puVar1 << 2;
            do {
              if (lVar5 * -0x5555555555555555 - (ulong)puVar7[-1] == 0) {
                plVar4 = *(long **)(*(long *)(param_3 + 0x88) + lVar5 * 0x10 + 8);
                (**(code **)(*plVar4 + 0x128))(plVar4,&fStack_44,(long)puVar1 + (ulong)*puVar7);
                break;
              }
              lVar8 = lVar8 + -4;
              puVar7 = puVar7 + 2;
            } while (lVar8 != 0);
          }
        }
        if (fVar11 == param_2) {
          puVar6 = (uint *)((ulong)*puVar6 + (long)puVar6);
          if (*puVar6 != 0) {
            puVar7 = (ushort *)((long)puVar6 + 6);
            lVar8 = (ulong)*puVar6 << 2;
            do {
              if (lVar5 * -0x5555555555555555 - (ulong)puVar7[-1] == 0) {
                plVar4 = *(long **)(*(long *)(param_3 + 0x88) + lVar5 * 0x10 + 8);
                (**(code **)(*plVar4 + 0x128))(plVar4,&fStack_48,(long)puVar6 + (ulong)*puVar7);
                *param_4 = fStack_48 - fStack_44;
                return;
              }
              lVar8 = lVar8 + -4;
              puVar7 = puVar7 + 2;
            } while (lVar8 != 0);
          }
        }
        uVar9 = uVar9 + 1;
      } while (uVar9 < uVar2);
    }
    *param_4 = 0.0;
  }
  else {
    plVar4 = *(long **)(param_5 + 8);
    if (((plVar4 == (long *)0x0) || (*(long *)(param_5 + 0x18) == 0)) ||
       (puVar6 = *(uint **)(param_5 + 0x20), puVar6 == (uint *)0x0)) {
      *param_4 = 0.0;
    }
    else {
      iVar3 = *(int *)(*(long *)(param_5 + 0x18) + 0x14);
      uVar2 = puVar6[(ulong)(iVar3 - 1) * 2];
      (**(code **)(*plVar4 + 0x128))(plVar4,&fStack_44,(ulong)*puVar6 + (long)puVar6);
      (**(code **)(*plVar4 + 0x128))
                (plVar4,&fStack_48,(ulong)uVar2 + (long)(puVar6 + (ulong)(iVar3 - 1) * 2));
      *param_4 = fStack_48 - fStack_44;
    }
  }
  return;
}

// ==== Aska::AafHandler::CalcDifferenceOfValue(Aska::Vector*, Aska::AafControllerInfo*, float, float)
// vaddr 0x1f984f4 | ghidra 0x20984f4 | size 604 | symbol _ZN4Aska10AafHandler21CalcDifferenceOfValueEPNS_6VectorEPNS_17AafControllerInfoEff | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10AafHandler21CalcDifferenceOfValueEPNS_6VectorEPNS_17AafControllerInfoEff
               (float param_1,float param_2,long param_3,float *param_4,long param_5)

{
  uint *puVar1;
  uint uVar2;
  int iVar3;
  long *plVar4;
  long lVar5;
  uint *puVar6;
  ushort *puVar7;
  long lVar8;
  ulong uVar9;
  long lVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fStack_80;
  float fStack_7c;
  float fStack_78;
  float fStack_74;
  float fStack_70;
  float fStack_6c;
  float fStack_68;
  float fStack_64;
  
  if ((*(byte *)(param_3 + 0xc) >> 6 & 1) == 0) {
    uVar2 = *(uint *)(param_3 + 0x48);
    if (uVar2 != 0) {
      lVar10 = *(long *)(param_3 + 0xe0);
      lVar5 = param_5 - *(long *)(param_3 + 0x88) >> 4;
      uVar9 = 0;
      do {
        puVar6 = (uint *)(lVar10 + uVar9 * 8);
        fVar14 = (float)puVar6[1];
        if (fVar14 == param_1) {
          puVar1 = (uint *)((ulong)*puVar6 + (long)puVar6);
          if (*puVar1 != 0) {
            puVar7 = (ushort *)((long)puVar1 + 6);
            lVar8 = (ulong)*puVar1 << 2;
            do {
              if (lVar5 * -0x5555555555555555 - (ulong)puVar7[-1] == 0) {
                plVar4 = *(long **)(*(long *)(param_3 + 0x88) + lVar5 * 0x10 + 8);
                (**(code **)(*plVar4 + 0x128))(plVar4,&fStack_70,(long)puVar1 + (ulong)*puVar7);
                if (fVar14 != param_2) goto code_r0x02098600;
                goto code_r0x020985a0;
              }
              lVar8 = lVar8 + -4;
              puVar7 = puVar7 + 2;
            } while (lVar8 != 0);
          }
        }
        if (fVar14 == param_2) {
code_r0x020985a0:
          puVar6 = (uint *)((ulong)*puVar6 + (long)puVar6);
          if (*puVar6 != 0) {
            puVar7 = (ushort *)((long)puVar6 + 6);
            lVar8 = (ulong)*puVar6 << 2;
            do {
              if (lVar5 * -0x5555555555555555 - (ulong)puVar7[-1] == 0) {
                plVar4 = *(long **)(*(long *)(param_3 + 0x88) + lVar5 * 0x10 + 8);
                (**(code **)(*plVar4 + 0x128))(plVar4,&fStack_80,(long)puVar6 + (ulong)*puVar7);
                *param_4 = fStack_80 - fStack_70;
                param_4[1] = fStack_7c - fStack_6c;
                param_4[2] = fStack_78 - fStack_68;
                fVar14 = fStack_74 - fStack_64;
                goto code_r0x02098728;
              }
              lVar8 = lVar8 + -4;
              puVar7 = puVar7 + 2;
            } while (lVar8 != 0);
          }
        }
code_r0x02098600:
        uVar9 = uVar9 + 1;
      } while (uVar9 < uVar2);
    }
    fVar14 = 0.0;
    param_4[0] = 0.0;
    param_4[1] = 0.0;
    param_4[2] = 0.0;
  }
  else {
    plVar4 = *(long **)(param_5 + 8);
    fVar14 = 1.0;
    fVar11 = 0.0;
    if ((plVar4 == (long *)0x0) || (*(long *)(param_5 + 0x18) == 0)) {
      fVar12 = 0.0;
      fVar13 = 0.0;
    }
    else {
      puVar6 = *(uint **)(param_5 + 0x20);
      fVar12 = 0.0;
      fVar13 = 0.0;
      if (puVar6 != (uint *)0x0) {
        iVar3 = *(int *)(*(long *)(param_5 + 0x18) + 0x14);
        uVar2 = puVar6[(ulong)(iVar3 - 1) * 2];
        (**(code **)(*plVar4 + 0x128))(plVar4,&fStack_70,(ulong)*puVar6 + (long)puVar6);
        (**(code **)(*plVar4 + 0x128))
                  (plVar4,&fStack_80,(ulong)uVar2 + (long)(puVar6 + (ulong)(iVar3 - 1) * 2));
        fVar11 = fStack_80 - fStack_70;
        fVar12 = fStack_7c - fStack_6c;
        fVar13 = fStack_78 - fStack_68;
        fVar14 = fStack_74 - fStack_64;
      }
    }
    *param_4 = fVar11;
    param_4[1] = fVar12;
    param_4[2] = fVar13;
  }
code_r0x02098728:
  param_4[3] = fVar14;
  return;
}

// ==== Aska::AafHandler::CalcDifferenceOfValue(int*, Aska::AafControllerInfo*, float, float)
// vaddr 0x1f98750 | ghidra 0x2098750 | size 492 | symbol _ZN4Aska10AafHandler21CalcDifferenceOfValueEPiPNS_17AafControllerInfoEff | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10AafHandler21CalcDifferenceOfValueEPiPNS_17AafControllerInfoEff
               (float param_1,float param_2,long param_3,int *param_4,long param_5)

{
  uint *puVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  long *plVar5;
  long lVar6;
  long lVar7;
  uint *puVar8;
  ushort *puVar9;
  ulong uVar10;
  long lVar11;
  uint *puVar12;
  float fVar13;
  int iStack_78;
  int iStack_74;
  
  if ((*(byte *)(param_3 + 0xc) >> 6 & 1) == 0) {
    uVar2 = *(uint *)(param_3 + 0x48);
    if (uVar2 != 0) {
      lVar11 = *(long *)(param_3 + 0xe0);
      lVar6 = param_5 - *(long *)(param_3 + 0x88) >> 4;
      uVar10 = 0;
      do {
        puVar8 = (uint *)(lVar11 + uVar10 * 8);
        fVar13 = (float)puVar8[1];
        if (fVar13 == param_1) {
          puVar1 = (uint *)((ulong)*puVar8 + (long)puVar8);
          puVar12 = puVar1 + 1;
          uVar4 = *puVar1;
          if (uVar4 != 0) {
            lVar7 = (ulong)uVar4 << 2;
            while (lVar6 * -0x5555555555555555 - (ulong)(ushort)*puVar12 != 0) {
              lVar7 = lVar7 + -4;
              puVar12 = puVar12 + 1;
              if (lVar7 == 0) {
                iStack_78 = 0;
                goto code_r0x02098914;
              }
            }
            plVar5 = *(long **)(*(long *)(param_3 + 0x88) + lVar6 * 0x10 + 8);
            (**(code **)(*plVar5 + 0x128))
                      (plVar5,&iStack_74,(long)puVar1 + (ulong)*(ushort *)((long)puVar12 + 2));
          }
          if (puVar1 + (ulong)uVar4 + 1 <= puVar12) break;
        }
        if (fVar13 == param_2) {
          puVar8 = (uint *)((ulong)*puVar8 + (long)puVar8);
          if (*puVar8 != 0) {
            puVar9 = (ushort *)((long)puVar8 + 6);
            lVar7 = (ulong)*puVar8 << 2;
            do {
              if (lVar6 * -0x5555555555555555 - (ulong)puVar9[-1] == 0) {
                plVar5 = *(long **)(*(long *)(param_3 + 0x88) + lVar6 * 0x10 + 8);
                (**(code **)(*plVar5 + 0x128))(plVar5,&iStack_78,(long)puVar8 + (ulong)*puVar9);
                goto code_r0x0209890c;
              }
              lVar7 = lVar7 + -4;
              puVar9 = puVar9 + 2;
            } while (lVar7 != 0);
          }
        }
        uVar10 = uVar10 + 1;
      } while (uVar10 < uVar2);
    }
    iStack_78 = 0;
  }
  else {
    plVar5 = *(long **)(param_5 + 8);
    if (((plVar5 == (long *)0x0) || (*(long *)(param_5 + 0x18) == 0)) ||
       (puVar8 = *(uint **)(param_5 + 0x20), puVar8 == (uint *)0x0)) {
      *param_4 = 0;
      return;
    }
    iVar3 = *(int *)(*(long *)(param_5 + 0x18) + 0x14);
    uVar2 = puVar8[(ulong)(iVar3 - 1) * 2];
    (**(code **)(*plVar5 + 0x128))(plVar5,&iStack_74,(ulong)*puVar8 + (long)puVar8);
    (**(code **)(*plVar5 + 0x128))
              (plVar5,&iStack_78,(ulong)uVar2 + (long)(puVar8 + (ulong)(iVar3 - 1) * 2));
code_r0x0209890c:
    iStack_78 = iStack_78 - iStack_74;
  }
code_r0x02098914:
  *param_4 = iStack_78;
  return;
}

// ==== Aska::AafHandler::CalcDifferenceOfValue(Aska::Quaternion*, Aska::AafControllerInfo*, float, float)
// vaddr 0x1f9893c | ghidra 0x209893c | size 584 | symbol _ZN4Aska10AafHandler21CalcDifferenceOfValueEPNS_10QuaternionEPNS_17AafControllerInfoEff | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10AafHandler21CalcDifferenceOfValueEPNS_10QuaternionEPNS_17AafControllerInfoEff
               (float param_1,float param_2,long param_3,float *param_4,long param_5)

{
  uint *puVar1;
  uint uVar2;
  int iVar3;
  long *plVar4;
  long lVar5;
  uint *puVar6;
  ushort *puVar7;
  long lVar8;
  ulong uVar9;
  long lVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fStack_90;
  float fStack_8c;
  float fStack_88;
  float fStack_84;
  float fStack_80;
  float fStack_7c;
  float fStack_78;
  float fStack_74;
  
  if ((*(byte *)(param_3 + 0xc) >> 6 & 1) == 0) {
    uVar2 = *(uint *)(param_3 + 0x48);
    fVar13 = 0.0;
    if (uVar2 != 0) {
      lVar10 = *(long *)(param_3 + 0xe0);
      lVar5 = param_5 - *(long *)(param_3 + 0x88) >> 4;
      uVar9 = 0;
      do {
        puVar6 = (uint *)(lVar10 + uVar9 * 8);
        fVar14 = (float)puVar6[1];
        if (fVar14 == param_1) {
          puVar1 = (uint *)((ulong)*puVar6 + (long)puVar6);
          if (*puVar1 != 0) {
            puVar7 = (ushort *)((long)puVar1 + 6);
            lVar8 = (ulong)*puVar1 << 2;
            do {
              if (lVar5 * -0x5555555555555555 - (ulong)puVar7[-1] == 0) {
                plVar4 = *(long **)(*(long *)(param_3 + 0x88) + lVar5 * 0x10 + 8);
                (**(code **)(*plVar4 + 0x128))(plVar4,&fStack_80,(long)puVar1 + (ulong)*puVar7);
                if (fVar14 != param_2) goto code_r0x02098a4c;
                goto code_r0x020989ec;
              }
              lVar8 = lVar8 + -4;
              puVar7 = puVar7 + 2;
            } while (lVar8 != 0);
          }
        }
        if (fVar14 == param_2) {
code_r0x020989ec:
          puVar6 = (uint *)((ulong)*puVar6 + (long)puVar6);
          if (*puVar6 != 0) {
            puVar7 = (ushort *)((long)puVar6 + 6);
            lVar8 = (ulong)*puVar6 << 2;
            do {
              if (lVar5 * -0x5555555555555555 - (ulong)puVar7[-1] == 0) {
                plVar4 = *(long **)(*(long *)(param_3 + 0x88) + lVar5 * 0x10 + 8);
                (**(code **)(*plVar4 + 0x128))(plVar4,&fStack_90,(long)puVar6 + (ulong)*puVar7);
                fVar13 = fStack_90 - fStack_80;
                fStack_8c = fStack_8c - fStack_7c;
                fStack_88 = fStack_88 - fStack_78;
                fStack_84 = fStack_84 - fStack_74;
                goto code_r0x02098b44;
              }
              lVar8 = lVar8 + -4;
              puVar7 = puVar7 + 2;
            } while (lVar8 != 0);
          }
        }
code_r0x02098a4c:
        uVar9 = uVar9 + 1;
      } while (uVar9 < uVar2);
    }
    fStack_8c = 0.0;
    fStack_88 = 0.0;
    fStack_84 = 0.0;
code_r0x02098b44:
    *param_4 = fVar13;
    param_4[1] = fStack_8c;
    param_4[2] = fStack_88;
    param_4[3] = fStack_84;
  }
  else {
    plVar4 = *(long **)(param_5 + 8);
    fVar13 = 1.0;
    fVar14 = 0.0;
    if ((plVar4 == (long *)0x0) || (*(long *)(param_5 + 0x18) == 0)) {
      fVar11 = 0.0;
      fVar12 = 0.0;
    }
    else {
      puVar6 = *(uint **)(param_5 + 0x20);
      fVar11 = 0.0;
      fVar12 = 0.0;
      if (puVar6 != (uint *)0x0) {
        iVar3 = *(int *)(*(long *)(param_5 + 0x18) + 0x14);
        uVar2 = puVar6[(ulong)(iVar3 - 1) * 2];
        (**(code **)(*plVar4 + 0x128))(plVar4,&fStack_80,(ulong)*puVar6 + (long)puVar6);
        (**(code **)(*plVar4 + 0x128))
                  (plVar4,&fStack_90,(ulong)uVar2 + (long)(puVar6 + (ulong)(iVar3 - 1) * 2));
        fVar14 = fStack_90 - fStack_80;
        fVar11 = fStack_8c - fStack_7c;
        fVar12 = fStack_88 - fStack_78;
        fVar13 = fStack_84 - fStack_74;
      }
    }
    *param_4 = fVar14;
    param_4[1] = fVar11;
    param_4[2] = fVar12;
    param_4[3] = fVar13;
  }
  return;
}

// ==== Aska::AafHandler::GetAafHeader(Aska::AFF::AskaFile*)
// vaddr 0x1f98b84 | ghidra 0x2098b84 | size 92 | symbol _ZN4Aska10AafHandler12GetAafHeaderEPNS_3AFF8AskaFileE | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska10AafHandler12GetAafHeaderEPNS_3AFF8AskaFileE(long param_1)

{
  ulong uVar1;
  long lVar2;
  undefined *puStack_20;
  long lStack_18;
  
  puStack_20 = PTR__ZTVN4Aska10ArfHandlerE_02cbeb70 + 0x10;
  lStack_18 = 0;
  uVar1 = Aska::ArfHandler::Attach(Aska::AFF::AskaResource const*)(&puStack_20,param_1 + 0x10);
  lVar2 = param_1 + 0x10;
  if ((uVar1 & 1) != 0) {
    if (lStack_18 == 0) {
      lVar2 = 0;
    }
    else {
      lVar2 = 0;
      if (*(uint *)(lStack_18 + 0xc) != 0) {
        lVar2 = lStack_18 + (ulong)*(uint *)(lStack_18 + 0xc);
      }
    }
  }
  return lVar2;
}

// ==== Aska::AafHandler::SetValues(float)
// vaddr 0x1f98be0 | ghidra 0x2098be0 | size 52 | symbol _ZN4Aska10AafHandler9SetValuesEf | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10AafHandler9SetValuesEf(undefined1 param_1 [16],long param_2)

{
  undefined1 auStack_8 [8];
  
  if ((*(byte *)(param_2 + 0xc) >> 1 & 1) != 0) {
    Aska::AafCalcCommonFunctor::CalcAndSetSubFunctor<Aska::AafCalcType<(Aska::kTYPE_AAFCALCCNTR)0, (Aska::kTYPE_AAFCALCANDSET)0, (Aska::kTYPE_AAFCALCSPEED)0, (Aska::kTYPE_AAFCALC)0, (Aska::kTYPE_AAFLOOPCONDITION)0>, false, false, (Aska::kTYPE_AAFCALCCNTR)0>::operator()(Aska::AafHandler*, Aska::IAnimatable*, Aska::IController*, float, float, unsigned int)(param_1,0xbf800000,auStack_8,param_2,0,0,0);
  }
  return;
}

// ==== Aska::AafHandler::SetValues(float, int)
// vaddr 0x1f98c14 | ghidra 0x2098c14 | size 100 | symbol _ZN4Aska10AafHandler9SetValuesEfi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10AafHandler9SetValuesEfi(undefined1 param_1 [16],long param_2,int param_3)

{
  undefined1 auStack_18 [8];
  undefined1 auStack_8 [8];
  
  if (param_3 == 0) {
    if ((*(uint *)(param_2 + 0xc) >> 1 & 1) != 0) {
      Aska::AafCalcCommonFunctor::CalcAndSetSubFunctor<Aska::AafCalcType<(Aska::kTYPE_AAFCALCCNTR)0, (Aska::kTYPE_AAFCALCANDSET)0, (Aska::kTYPE_AAFCALCSPEED)0, (Aska::kTYPE_AAFCALC)0, (Aska::kTYPE_AAFLOOPCONDITION)0>, false, false, (Aska::kTYPE_AAFCALCCNTR)0>::operator()(Aska::AafHandler*, Aska::IAnimatable*, Aska::IController*, float, float, unsigned int)(param_1,0xbf800000,auStack_8,param_2,0,0,0);
    }
  }
  else if ((*(uint *)(param_2 + 0xc) >> 1 & 1) != 0) {
    Aska::AafCalcCommonFunctor::CalcAndSetSubFunctor<Aska::AafCalcType<(Aska::kTYPE_AAFCALCCNTR)0, (Aska::kTYPE_AAFCALCANDSET)0, (Aska::kTYPE_AAFCALCSPEED)0, (Aska::kTYPE_AAFCALC)0, (Aska::kTYPE_AAFLOOPCONDITION)1>, false, false, (Aska::kTYPE_AAFCALCCNTR)0>::operator()(Aska::AafHandler*, Aska::IAnimatable*, Aska::IController*, float, float, unsigned int)(param_1,0xbf800000,auStack_18,param_2,0,0,0);
  }
  return;
}

// ==== Aska::AafHandler::AddValues(float)
// vaddr 0x1f98c78 | ghidra 0x2098c78 | size 52 | symbol _ZN4Aska10AafHandler9AddValuesEf | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10AafHandler9AddValuesEf(undefined1 param_1 [16],long param_2)

{
  undefined1 auStack_8 [8];
  
  if ((*(byte *)(param_2 + 0xc) >> 1 & 1) != 0) {
    Aska::AafCalcCommonFunctor::CalcAndSetSubFunctor<Aska::AafCalcType<(Aska::kTYPE_AAFCALCCNTR)0, (Aska::kTYPE_AAFCALCANDSET)0, (Aska::kTYPE_AAFCALCSPEED)0, (Aska::kTYPE_AAFCALC)0, (Aska::kTYPE_AAFLOOPCONDITION)0>, true, false, (Aska::kTYPE_AAFCALCCNTR)0>::operator()(Aska::AafHandler*, Aska::IAnimatable*, Aska::IController*, float, float, unsigned int)(param_1,0xbf800000,auStack_8,param_2,0,0,0);
  }
  return;
}

// ==== Aska::AafHandler::BlendValues(float, float)
// vaddr 0x1f98cac | ghidra 0x2098cac | size 48 | symbol _ZN4Aska10AafHandler11BlendValuesEff | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10AafHandler11BlendValuesEff(long param_1)

{
  undefined1 auStack_8 [8];
  
  if ((*(byte *)(param_1 + 0xc) >> 1 & 1) != 0) {
    Aska::AafCalcCommonFunctor::CalcAndSetSubFunctor<Aska::AafCalcType<(Aska::kTYPE_AAFCALCCNTR)0, (Aska::kTYPE_AAFCALCANDSET)0, (Aska::kTYPE_AAFCALCSPEED)0, (Aska::kTYPE_AAFCALC)0, (Aska::kTYPE_AAFLOOPCONDITION)0>, false, true, (Aska::kTYPE_AAFCALCCNTR)0>::operator()(Aska::AafHandler*, Aska::IAnimatable*, Aska::IController*, float, float, unsigned int)(auStack_8,param_1,0,0,0);
  }
  return;
}

// ==== Aska::AafHandler::SetValuesHighSpeed(float)
// vaddr 0x1f98cdc | ghidra 0x2098cdc | size 52 | symbol _ZN4Aska10AafHandler18SetValuesHighSpeedEf | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10AafHandler18SetValuesHighSpeedEf(undefined1 param_1 [16],long param_2)

{
  undefined1 auStack_8 [8];
  
  if ((*(byte *)(param_2 + 0xc) >> 1 & 1) != 0) {
    Aska::AafCalcCommonFunctor::CalcAndSetSubFunctor<Aska::AafCalcType<(Aska::kTYPE_AAFCALCCNTR)0, (Aska::kTYPE_AAFCALCANDSET)0, (Aska::kTYPE_AAFCALCSPEED)1, (Aska::kTYPE_AAFCALC)0, (Aska::kTYPE_AAFLOOPCONDITION)0>, false, false, (Aska::kTYPE_AAFCALCCNTR)0>::operator()(Aska::AafHandler*, Aska::IAnimatable*, Aska::IController*, float, float, unsigned int)(param_1,0xbf800000,auStack_8,param_2,0,0,0);
  }
  return;
}

// ==== Aska::AafHandler::SetValuesHighSpeed(float, int)
// vaddr 0x1f98d10 | ghidra 0x2098d10 | size 104 | symbol _ZN4Aska10AafHandler18SetValuesHighSpeedEfi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10AafHandler18SetValuesHighSpeedEfi(undefined1 param_1 [16],long param_2,int param_3)

{
  undefined1 auStack_18 [8];
  undefined1 auStack_8 [8];
  
  if (param_3 == 0) {
    if ((*(uint *)(param_2 + 0xc) >> 1 & 1) != 0) {
      Aska::AafCalcCommonFunctor::CalcAndSetSubFunctor<Aska::AafCalcType<(Aska::kTYPE_AAFCALCCNTR)0, (Aska::kTYPE_AAFCALCANDSET)0, (Aska::kTYPE_AAFCALCSPEED)1, (Aska::kTYPE_AAFCALC)0, (Aska::kTYPE_AAFLOOPCONDITION)0>, false, false, (Aska::kTYPE_AAFCALCCNTR)0>::operator()(Aska::AafHandler*, Aska::IAnimatable*, Aska::IController*, float, float, unsigned int)(param_1,0xbf800000,auStack_8,param_2,0,0,0);
    }
  }
  else if ((*(uint *)(param_2 + 0xc) >> 1 & 1) != 0) {
    Aska::AafCalcCommonFunctor::CalcAndSetSubFunctor<Aska::AafCalcType<(Aska::kTYPE_AAFCALCCNTR)0, (Aska::kTYPE_AAFCALCANDSET)0, (Aska::kTYPE_AAFCALCSPEED)1, (Aska::kTYPE_AAFCALC)0, (Aska::kTYPE_AAFLOOPCONDITION)1>, false, false, (Aska::kTYPE_AAFCALCCNTR)0>::operator()(Aska::AafHandler*, Aska::IAnimatable*, Aska::IController*, float, float, unsigned int)(param_1,0xbf800000,auStack_18,param_2,0,0,param_3);
  }
  return;
}

// ==== Aska::AafHandler::SetOneValue(Aska::IAnimatable*, float)
// vaddr 0x1f98d78 | ghidra 0x2098d78 | size 56 | symbol _ZN4Aska10AafHandler11SetOneValueEPNS_11IAnimatableEf | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10AafHandler11SetOneValueEPNS_11IAnimatableEf
               (undefined1 param_1 [16],long param_2,undefined8 param_3)

{
  undefined1 auStack_8 [8];
  
  if ((*(byte *)(param_2 + 0xc) >> 1 & 1) != 0) {
    Aska::AafCalcCommonFunctor::CalcAndSetSubFunctor<Aska::AafCalcType<(Aska::kTYPE_AAFCALCCNTR)0, (Aska::kTYPE_AAFCALCANDSET)0, (Aska::kTYPE_AAFCALCSPEED)0, (Aska::kTYPE_AAFCALC)1, (Aska::kTYPE_AAFLOOPCONDITION)0>, false, false, (Aska::kTYPE_AAFCALCCNTR)0>::operator()(Aska::AafHandler*, Aska::IAnimatable*, Aska::IController*, float, float, unsigned int)(param_1,0xbf800000,auStack_8,param_2,param_3,0,0);
  }
  return;
}

// ==== Aska::AafHandler::SetOneValue(Aska::IAnimatable*, float, int)
// vaddr 0x1f98db0 | ghidra 0x2098db0 | size 108 | symbol _ZN4Aska10AafHandler11SetOneValueEPNS_11IAnimatableEfi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10AafHandler11SetOneValueEPNS_11IAnimatableEfi
               (undefined1 param_1 [16],long param_2,undefined8 param_3,int param_4)

{
  undefined1 auStack_18 [8];
  undefined1 auStack_8 [8];
  
  if (param_4 == 0) {
    if ((*(uint *)(param_2 + 0xc) >> 1 & 1) != 0) {
      Aska::AafCalcCommonFunctor::CalcAndSetSubFunctor<Aska::AafCalcType<(Aska::kTYPE_AAFCALCCNTR)0, (Aska::kTYPE_AAFCALCANDSET)0, (Aska::kTYPE_AAFCALCSPEED)0, (Aska::kTYPE_AAFCALC)1, (Aska::kTYPE_AAFLOOPCONDITION)0>, false, false, (Aska::kTYPE_AAFCALCCNTR)0>::operator()(Aska::AafHandler*, Aska::IAnimatable*, Aska::IController*, float, float, unsigned int)(param_1,0xbf800000,auStack_8,param_2,param_3,0,0);
    }
  }
  else if ((*(uint *)(param_2 + 0xc) >> 1 & 1) != 0) {
    Aska::AafCalcCommonFunctor::CalcAndSetSubFunctor<Aska::AafCalcType<(Aska::kTYPE_AAFCALCCNTR)0, (Aska::kTYPE_AAFCALCANDSET)0, (Aska::kTYPE_AAFCALCSPEED)0, (Aska::kTYPE_AAFCALC)1, (Aska::kTYPE_AAFLOOPCONDITION)1>, false, false, (Aska::kTYPE_AAFCALCCNTR)0>::operator()(Aska::AafHandler*, Aska::IAnimatable*, Aska::IController*, float, float, unsigned int)(param_1,0xbf800000,auStack_18,param_2,param_3,0,param_4);
  }
  return;
}

// ==== Aska::AafHandler::SetOneValue(Aska::IController*, float)
// vaddr 0x1f98e1c | ghidra 0x2098e1c | size 56 | symbol _ZN4Aska10AafHandler11SetOneValueEPNS_11IControllerEf | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10AafHandler11SetOneValueEPNS_11IControllerEf
               (undefined1 param_1 [16],long param_2,undefined8 param_3)

{
  undefined1 auStack_8 [8];
  
  if ((*(byte *)(param_2 + 0xc) >> 1 & 1) != 0) {
    Aska::AafCalcCommonFunctor::CalcAndSetSubFunctor<Aska::AafCalcType<(Aska::kTYPE_AAFCALCCNTR)1, (Aska::kTYPE_AAFCALCANDSET)0, (Aska::kTYPE_AAFCALCSPEED)0, (Aska::kTYPE_AAFCALC)1, (Aska::kTYPE_AAFLOOPCONDITION)0>, false, false, (Aska::kTYPE_AAFCALCCNTR)1>::operator()(Aska::AafHandler*, Aska::IAnimatable*, Aska::IController*, float, float, unsigned int)(param_1,0xbf800000,auStack_8,param_2,0,param_3,0);
  }
  return;
}

// ==== Aska::AafHandler::SetOneValue(Aska::IController*, float, int)
// vaddr 0x1f98e54 | ghidra 0x2098e54 | size 108 | symbol _ZN4Aska10AafHandler11SetOneValueEPNS_11IControllerEfi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10AafHandler11SetOneValueEPNS_11IControllerEfi
               (undefined1 param_1 [16],long param_2,undefined8 param_3,int param_4)

{
  undefined1 auStack_18 [8];
  undefined1 auStack_8 [8];
  
  if (param_4 == 0) {
    if ((*(uint *)(param_2 + 0xc) >> 1 & 1) != 0) {
      Aska::AafCalcCommonFunctor::CalcAndSetSubFunctor<Aska::AafCalcType<(Aska::kTYPE_AAFCALCCNTR)1, (Aska::kTYPE_AAFCALCANDSET)0, (Aska::kTYPE_AAFCALCSPEED)0, (Aska::kTYPE_AAFCALC)1, (Aska::kTYPE_AAFLOOPCONDITION)0>, false, false, (Aska::kTYPE_AAFCALCCNTR)1>::operator()(Aska::AafHandler*, Aska::IAnimatable*, Aska::IController*, float, float, unsigned int)(param_1,0xbf800000,auStack_8,param_2,0,param_3,0);
    }
  }
  else if ((*(uint *)(param_2 + 0xc) >> 1 & 1) != 0) {
    Aska::AafCalcCommonFunctor::CalcAndSetSubFunctor<Aska::AafCalcType<(Aska::kTYPE_AAFCALCCNTR)1, (Aska::kTYPE_AAFCALCANDSET)0, (Aska::kTYPE_AAFCALCSPEED)0, (Aska::kTYPE_AAFCALC)1, (Aska::kTYPE_AAFLOOPCONDITION)1>, false, false, (Aska::kTYPE_AAFCALCCNTR)1>::operator()(Aska::AafHandler*, Aska::IAnimatable*, Aska::IController*, float, float, unsigned int)(param_1,0xbf800000,auStack_18,param_2,0,param_3,param_4);
  }
  return;
}

// ==== Aska::AafHandler::SetAutoComplement(float, float, Aska::AafHandler*, float, Aska::AsfHandler*)
// vaddr 0x1f98ec0 | ghidra 0x2098ec0 | size 9140 | symbol _ZN4Aska10AafHandler17SetAutoComplementEffPS0_fPNS_10AsfHandlerE | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4
_ZN4Aska10AafHandler17SetAutoComplementEffPS0_fPNS_10AsfHandlerE
          (float param_1,undefined1 param_2 [16],undefined1 param_3 [16],long param_4,long param_5,
          long param_6)

{
  bool bVar1;
  char cVar2;
  byte bVar3;
  ushort uVar4;
  int iVar5;
  ulong uVar6;
  bool bVar7;
  ulong uVar8;
  undefined8 uVar9;
  undefined8 *puVar10;
  float *pfVar11;
  float *pfVar12;
  undefined4 uVar13;
  long lVar14;
  long lVar15;
  uint *puVar16;
  code *pcVar17;
  undefined1 uVar18;
  long lVar19;
  ulong uVar20;
  ulong uVar21;
  long lVar22;
  uint uVar23;
  uint uVar24;
  uint uVar25;
  long *plVar26;
  byte *pbVar27;
  ulong uVar28;
  long *plVar29;
  long *plVar30;
  long *plVar31;
  ulong uVar32;
  ulong uVar33;
  long *plVar34;
  uint uVar35;
  long lVar36;
  byte *pbVar37;
  ulong uVar38;
  ulong uVar39;
  ulong uVar40;
  long *plVar41;
  float fVar42;
  float fVar43;
  float fVar44;
  float fVar45;
  float fVar46;
  float fVar47;
  undefined8 uStack_108;
  long *plStack_100;
  byte *pbStack_f8;
  long *plStack_f0;
  undefined8 uStack_e8;
  long *plStack_e0;
  long lStack_d8;
  float afStack_d0 [4];
  undefined8 uStack_c0;
  undefined8 uStack_b8;
  undefined8 uStack_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined8 uStack_98;
  float fStack_88;
  undefined4 uStack_84;
  
  fVar46 = param_3._0_4_;
  fVar44 = param_2._0_4_;
  uVar39 = param_3._0_8_;
  uVar6 = param_2._0_8_;
  if (((*(uint *)(param_4 + 0xc) ^ 0xffffffff) & 0x82) != 0) {
    return 0;
  }
  if ((*(char *)(param_4 + 0x70) == '\0') || (*(char *)(param_4 + 0x72) != '\0')) {
    lVar14 = *(long *)(param_4 + 0x118);
  }
  else {
    uStack_a0 = *(long **)(param_4 + 0x68);
    if (uStack_a0 == (long *)0x0) {
      return 0;
    }
    if (*(uint *)(param_4 + 0x38) != 0) {
      lVar14 = (ulong)*(uint *)(param_4 + 0x38) * 0x30;
      puVar10 = (undefined8 *)(*(long *)(param_4 + 0x80) + 8);
      do {
        (**(code **)(*(long *)*puVar10 + 0xd0))((long *)*puVar10,&uStack_a0);
        lVar14 = lVar14 + -0x30;
        puVar10 = puVar10 + 6;
      } while (lVar14 != 0);
    }
    *(undefined1 *)(param_4 + 0x72) = 1;
    lVar14 = *(long *)(param_4 + 0x118);
  }
  if (lVar14 != 0) {
    lVar19 = *(long *)(param_4 + 0x28);
    if (lVar19 == 0) {
      return 0;
    }
    uVar4 = *(ushort *)(lVar19 + 0xe);
    if (uVar4 == 0) {
      return 0;
    }
    fVar42 = fVar44 / *(float *)(lVar19 + 0x2c);
    if (0.0 <= fVar42) {
      uVar23 = (uint)fVar42;
      if ((uVar4 == uVar23 || (int)(uint)uVar4 < (int)uVar23) ||
         (*(float *)(lVar19 + 0x10) < fVar44)) {
        uVar23 = uVar4 - 1;
      }
    }
    else {
      uVar23 = 0;
    }
    if (*(long *)(param_4 + 0x10) + (ulong)*(uint *)(lVar19 + 0x28) + (long)(int)uVar23 * 0xc == 0)
    {
      return 0;
    }
    if (*(long *)(lVar14 + (long)(int)uVar23 * 8) == 0) {
      return 0;
    }
  }
  if ((*(byte *)(param_4 + 0xd) & 1) == 0) {
    return 0;
  }
  uVar23 = *(uint *)(param_4 + 0x38);
  uVar38 = (ulong)uVar23;
  *(float *)(param_4 + 0xe8) = fVar44 - param_1;
  *(float *)(param_4 + 0xec) = fVar44;
  fVar42 = 1.0;
  if (param_1 != 0.0) {
    fVar42 = param_1;
  }
  *(float *)(param_4 + 0xf0) = fVar42;
  if (param_5 != 0) {
    if (*(long *)(param_5 + 0x118) != 0) {
      lVar14 = *(long *)(param_5 + 0x28);
      if (lVar14 == 0) {
        return 0;
      }
      uVar4 = *(ushort *)(lVar14 + 0xe);
      if (uVar4 == 0) {
        return 0;
      }
      fVar43 = fVar46 / *(float *)(lVar14 + 0x2c);
      if (0.0 <= fVar43) {
        uVar24 = (uint)fVar43;
        if ((uVar4 == uVar24 || (int)(uint)uVar4 < (int)uVar24) ||
           (*(float *)(lVar14 + 0x10) < fVar46)) {
          uVar24 = uVar4 - 1;
        }
      }
      else {
        uVar24 = 0;
      }
      if (*(long *)(param_5 + 0x10) + (ulong)*(uint *)(lVar14 + 0x28) + (long)(int)uVar24 * 0xc == 0
         ) {
        return 0;
      }
      if (*(long *)(*(long *)(param_5 + 0x118) + (long)(int)uVar24 * 8) == 0) {
        return 0;
      }
    }
    if ((*(byte *)(param_5 + 0xd) & 1) == 0) {
      return 0;
    }
    uVar24 = *(uint *)(param_5 + 0x3c);
    if ((uVar24 != 0) && (*(int *)(param_5 + 0x48) != 0)) {
      lVar19 = *(long *)(param_5 + 0xb0);
      uVar9 = *(undefined8 *)(param_5 + 0xb8);
      iVar5 = *(int *)(param_5 + 0xa8) << 2;
      memset(lVar19,0,iVar5);
      lVar14 = 0;
      uVar40 = 0;
      do {
        lVar15 = *(long *)(param_5 + 0x88) + lVar14;
        if (((*(byte *)(lVar15 + 0x2e) & 3) == 0) &&
           (((fVar46 < *(float *)(*(long *)(lVar15 + 0x18) + 0xc) ||
             (*(float *)(*(long *)(lVar15 + 0x18) + 0x10) < fVar46)) ||
            (uVar8 = (**(code **)(**(long **)(lVar15 + 8) + 0x108))(uVar39), (uVar8 & 1) != 0)))) {
          lVar15 = (uVar40 >> 5 & 0x7ffffff) * 4;
          *(uint *)(lVar19 + lVar15) =
               *(uint *)(lVar19 + lVar15) | 1 << (ulong)((uint)uVar40 & 0x1f);
        }
        uVar40 = uVar40 + 1;
        lVar14 = lVar14 + 0x30;
      } while (uVar24 != uVar40);
      memcpy(uVar9,lVar19,iVar5);
    }
    Aska::AafHandler::RenewalAllControllerCache(float)(uVar39,param_5);
  }
  plVar30 = _UNK_027dbb30;
  fVar42 = _UNK_02801508 / fVar42;
  lStack_d8 = param_6;
  if (0 < (int)uVar23) {
    uVar40 = 0;
    plVar29 = (long *)0x0;
    pbVar27 = (byte *)0x0;
    plVar26 = (long *)0x0;
    plVar34 = (long *)0x0;
    uVar24 = 0xffffffff;
    uStack_108 = _UNK_027dbb38;
code_r0x0209abc4:
    lVar14 = *(long *)(param_4 + 0x80);
    plVar41 = (long *)(lVar14 + uVar40 * 0x30);
    if ((*(byte *)((long)plVar41 + 0x2e) & 7) != 0) goto code_r0x0209abdc;
    uVar4 = *(ushort *)(lVar14 + uVar40 * 0x30 + 0x2c);
    if (uVar24 != uVar4) {
      puVar10 = (undefined8 *)(*(long *)(param_4 + 0x78) + (ulong)uVar4 * 0x10);
      pbVar27 = (byte *)*puVar10;
      plVar29 = (long *)puVar10[1];
      uVar24 = (uint)uVar4;
    }
    plVar31 = *(long **)(lVar14 + uVar40 * 0x30 + 8);
    if ((plVar31 == (long *)0x0) || (**(char **)(lVar14 + uVar40 * 0x30 + 0x10) != '\0'))
    goto code_r0x0209abdc;
    if (param_6 == 0) {
      plVar34 = plVar29;
      if (plVar29 == (long *)0x0) {
        plVar34 = (long *)0x0;
        goto code_r0x0209abdc;
      }
    }
    else {
      if (plVar26 == plVar29) {
code_r0x020992c0:
        if (plVar34 != (long *)0x0) goto code_r0x020992cc;
        goto code_r0x0209abdc;
      }
      plVar26 = plVar29;
      if ((*pbVar27 >> 2 & 1) == 0) {
        pbVar37 = pbVar27 + 8;
code_r0x0209922c:
        plStack_f0 = plVar31;
        plVar34 = (long *)Aska::AsfHandler::QuickSearchByNameEx(char const*) const(param_6,pbVar37);
        plVar31 = plStack_f0;
        if (plVar34 != (long *)0x0) goto code_r0x020992cc;
        uVar8 = Aska::AsfHandler::GetModifierAnimationId(char const*, Aska::IAnimatable**, int*) const(lStack_d8,pbVar37,&uStack_a0,&uStack_b0);
        plVar31 = plStack_f0;
        plVar34 = uStack_a0;
        param_6 = lStack_d8;
        if ((uVar8 & 1) == 0) {
          plVar34 = (long *)0x0;
          goto code_r0x0209abdc;
        }
      }
      else {
        puVar16 = *(uint **)(param_4 + 0x18);
        if (puVar16 != (uint *)0x0) {
          if ((*puVar16 <= *(uint *)(pbVar27 + 8)) ||
             (pbVar37 = (byte *)((long)puVar16 + (ulong)(*(uint *)(pbVar27 + 8) << 5) + 4),
             pbVar37 == (byte *)0x0)) goto code_r0x020992c0;
          goto code_r0x0209922c;
        }
      }
      if (plVar34 == (long *)0x0) goto code_r0x0209abdc;
    }
code_r0x020992cc:
    plStack_f0 = plVar31;
    param_6 = lStack_d8;
    lVar14 = *(long *)(lVar14 + uVar40 * 0x30 + 0x18);
    if (lVar14 == 0) goto code_r0x0209abdc;
    if (*(byte *)(lVar14 + 4) < 4) {
      uVar8 = (ulong)*(byte *)(lVar14 + 6);
    }
    else {
      uVar8 = 0;
    }
    uVar25 = (uint)uVar8;
    plStack_100 = plVar29;
    pbStack_f8 = pbVar27;
    plStack_e0 = plVar26;
    switch(uVar25) {
    case 1:
    case 2:
    case 3:
      if ((param_5 != 0) && (uVar20 = (ulong)*(ushort *)(param_5 + 0xf4), uVar20 != 0)) {
        uVar35 = *(uint *)(param_5 + 0x38);
        if (uVar35 != 0) {
          uVar28 = *(ulong *)(param_5 + 0x80);
          uVar21 = 0;
          uVar33 = uVar28 + (ulong)uVar35 * 0x30;
          do {
            uVar32 = uVar28;
            if (*(long **)(*(long *)(param_5 + 0x78) + uVar21 * 0x10 + 8) == plVar34) {
              do {
                if ((((uVar21 == *(ushort *)(uVar32 + 0x2c)) &&
                     (plVar29 = *(long **)(uVar32 + 8), plVar29 != (long *)0x0)) &&
                    (lVar19 = *(long *)(uVar32 + 0x18), lVar19 != 0)) &&
                   (*(byte *)(lVar19 + 6) == uVar25)) {
                  if ((*(byte *)(uVar32 + 0x2e) >> 3 & 1) == 0) goto code_r0x02099d1c;
                  fStack_88 = 0.0;
                  (**(code **)(*plVar29 + 0x148))(plVar29,&uStack_84,1);
                  goto code_r0x02099d74;
                }
                uVar32 = uVar32 + 0x30;
              } while (uVar32 < uVar33);
            }
            uVar21 = uVar21 + 1;
          } while ((long)uVar21 < (long)uVar20);
          if (uVar35 != 0) {
            uVar21 = 0;
            do {
              uVar32 = uVar28;
              if (*(long **)(*(long *)(param_5 + 0x78) + uVar21 * 0x10 + 8) == plVar34) {
                do {
                  if (((uVar21 == *(ushort *)(uVar32 + 0x2c)) &&
                      (plVar29 = *(long **)(uVar32 + 8), plVar29 != (long *)0x0)) &&
                     ((lVar14 = *(long *)(uVar32 + 0x18), lVar14 != 0 &&
                      (*(char *)(lVar14 + 6) == '\x04')))) {
                    if ((*(byte *)(uVar32 + 0x2e) >> 3 & 1) != 0) {
                      (**(code **)(*plVar29 + 0x148))(plVar29,&uStack_a0,1);
                      uStack_b8 = uStack_108;
                      uStack_c0 = plVar30;
                      goto code_r0x02099d74;
                    }
                    uVar20 = (ulong)(uint)*(float *)(lVar14 + 0xc);
                    if ((*(float *)(lVar14 + 0xc) <= fVar46) &&
                       (uVar20 = uVar39, *(float *)(lVar14 + 0x10) < fVar46)) {
                      uVar20 = (ulong)(uint)*(float *)(lVar14 + 0x10);
                    }
                    (**(code **)(*plVar29 + 0x80))(uVar20,plVar29,&uStack_a0,&uStack_c0);
                    lVar14 = (uVar8 - 1) * 4;
                    uStack_84 = *(undefined4 *)((long)&uStack_a0 + lVar14);
                    fStack_88 = *(float *)((long)&uStack_c0 + lVar14);
                    goto code_r0x02099d54;
                  }
                  uVar32 = uVar32 + 0x30;
                } while (uVar32 < uVar33);
              }
              uVar21 = uVar21 + 1;
            } while ((long)uVar21 < (long)uVar20);
          }
        }
      }
      uVar13 = *(undefined4 *)((long)plVar34 + (long)(int)(uVar8 - 1) * 4 + 0x80);
      goto code_r0x02099670;
    case 4:
      if (param_5 == 0) {
code_r0x02099f24:
        plVar29 = plVar34 + 0x10;
        break;
      }
      uVar25 = *(uint *)(param_5 + 0x38);
      uVar8 = (ulong)uVar25;
      uVar21 = (ulong)*(ushort *)(param_5 + 0xf4);
      uVar20 = *(ulong *)(param_5 + 0x80);
      if ((uVar21 != 0) && (uVar25 != 0)) {
        uVar28 = 0;
        do {
          uVar32 = uVar20;
          if (*(long **)(*(long *)(param_5 + 0x78) + uVar28 * 0x10 + 8) == plVar34) {
            do {
              if ((((uVar28 == *(ushort *)(uVar32 + 0x2c)) &&
                   (plVar26 = *(long **)(uVar32 + 8), plVar26 != (long *)0x0)) &&
                  (lVar14 = *(long *)(uVar32 + 0x18), lVar14 != 0)) &&
                 (*(char *)(lVar14 + 6) == '\x04')) goto code_r0x02099db8;
              uVar32 = uVar32 + 0x30;
            } while (uVar32 < uVar20 + (ulong)uVar25 * 0x30);
          }
          uVar28 = uVar28 + 1;
        } while ((long)uVar28 < (long)uVar21);
      }
      uStack_98 = uStack_108;
      uStack_a0 = plVar30;
      uStack_b8 = uStack_108;
      uStack_c0 = plVar30;
      if (*(ushort *)(param_5 + 0xf4) == 0) {
        bVar7 = false;
      }
      else {
        uVar25 = 0;
        bVar7 = false;
        uVar28 = uVar20 + uVar8 * 0x30;
code_r0x02099714:
        uVar35 = uVar25;
        do {
          uVar25 = uVar35 + 1;
          if ((int)uVar8 != 0) {
            uVar33 = 0;
            do {
              uVar32 = uVar20;
              if (*(long **)(*(long *)(param_5 + 0x78) + uVar33 * 0x10 + 8) == plVar34) {
                do {
                  if (((uVar33 == *(ushort *)(uVar32 + 0x2c)) &&
                      (plVar29 = *(long **)(uVar32 + 8), plVar29 != (long *)0x0)) &&
                     ((lVar14 = *(long *)(uVar32 + 0x18), lVar14 != 0 &&
                      ((uint)*(byte *)(lVar14 + 6) == (uVar25 & 0xff))))) {
                    if ((*(byte *)(uVar32 + 0x2e) >> 3 & 1) == 0) {
                      uVar8 = (ulong)(uint)*(float *)(lVar14 + 0xc);
                      if ((*(float *)(lVar14 + 0xc) <= fVar46) &&
                         (uVar8 = uVar39, *(float *)(lVar14 + 0x10) < fVar46)) {
                        uVar8 = (ulong)(uint)*(float *)(lVar14 + 0x10);
                      }
                      (**(code **)(*plVar29 + 0x80))(uVar8,plVar29,&uStack_84,&fStack_88);
                      fVar43 = (float)(**(code **)(*plVar29 + 0x1d0))(plVar29);
                      fStack_88 = fStack_88 * fVar42 * fVar43;
                      *(float *)((long)&uStack_c0 + (long)(int)uVar35 * 4) = fStack_88;
                    }
                    else {
                      (**(code **)(*plVar29 + 0x148))(plVar29,&uStack_84,1);
                    }
                    *(undefined4 *)((long)&uStack_a0 + (long)(int)uVar35 * 4) = uStack_84;
                    if (1 < (int)uVar35) goto code_r0x0209a190;
                    uVar8 = (ulong)*(uint *)(param_5 + 0x38);
                    uVar20 = *(ulong *)(param_5 + 0x80);
                    uVar21 = (ulong)*(ushort *)(param_5 + 0xf4);
                    bVar7 = true;
                    uVar28 = uVar20 + uVar8 * 0x30;
                    if (uVar21 == 0) goto code_r0x02099f1c;
                    goto code_r0x02099714;
                  }
                  uVar32 = uVar32 + 0x30;
                } while (uVar32 < uVar28);
              }
              uVar33 = uVar33 + 1;
            } while ((long)uVar33 < (long)uVar21);
          }
          bVar1 = (int)uVar35 < 2;
          uVar35 = uVar25;
        } while (bVar1);
      }
code_r0x02099f1c:
      if (!bVar7) goto code_r0x02099f24;
      goto code_r0x0209a190;
    case 5:
    case 6:
    case 7:
      if ((param_5 != 0) && (uVar20 = (ulong)*(ushort *)(param_5 + 0xf4), uVar20 != 0)) {
        uVar35 = *(uint *)(param_5 + 0x38);
        if (uVar35 != 0) {
          uVar28 = *(ulong *)(param_5 + 0x80);
          uVar21 = 0;
          uVar33 = uVar28 + (ulong)uVar35 * 0x30;
          do {
            uVar32 = uVar28;
            if (*(long **)(*(long *)(param_5 + 0x78) + uVar21 * 0x10 + 8) == plVar34) {
              do {
                if ((((uVar21 == *(ushort *)(uVar32 + 0x2c)) &&
                     (plVar29 = *(long **)(uVar32 + 8), plVar29 != (long *)0x0)) &&
                    (lVar19 = *(long *)(uVar32 + 0x18), lVar19 != 0)) &&
                   (*(byte *)(lVar19 + 6) == uVar25)) {
                  if ((*(byte *)(uVar32 + 0x2e) >> 3 & 1) == 0) goto code_r0x02099d1c;
                  (**(code **)(*plVar29 + 0x148))(plVar29,&uStack_84,1);
                  fStack_88 = 0.0;
                  goto code_r0x02099d74;
                }
                uVar32 = uVar32 + 0x30;
              } while (uVar32 < uVar33);
            }
            uVar21 = uVar21 + 1;
          } while ((long)uVar21 < (long)uVar20);
          if (uVar35 != 0) {
            uVar21 = 0;
            do {
              uVar32 = uVar28;
              if (*(long **)(*(long *)(param_5 + 0x78) + uVar21 * 0x10 + 8) == plVar34) {
                do {
                  if (((uVar21 == *(ushort *)(uVar32 + 0x2c)) &&
                      (plVar29 = *(long **)(uVar32 + 8), plVar29 != (long *)0x0)) &&
                     ((lVar14 = *(long *)(uVar32 + 0x18), lVar14 != 0 &&
                      (*(char *)(lVar14 + 6) == '\b')))) {
                    if ((*(byte *)(uVar32 + 0x2e) >> 3 & 1) == 0) {
                      uVar20 = (ulong)(uint)*(float *)(lVar14 + 0xc);
                      if ((*(float *)(lVar14 + 0xc) <= fVar46) &&
                         (uVar20 = uVar39, *(float *)(lVar14 + 0x10) < fVar46)) {
                        uVar20 = (ulong)(uint)*(float *)(lVar14 + 0x10);
                      }
                      (**(code **)(*plVar29 + 0x80))(uVar20,plVar29,&uStack_b0,&fStack_88);
                      fVar43 = (float)(**(code **)(*plVar29 + 0x1d0))(plVar29);
                      fStack_88 = fStack_88 * fVar42 * fVar43;
                    }
                    else {
                      (**(code **)(*plVar29 + 0x148))(plVar29,&uStack_b0,1);
                      fStack_88 = 0.0;
                    }
                    uStack_84 = *(undefined4 *)((long)&uStack_a0 + (uVar8 - 5) * 4);
                    goto code_r0x0209a2c4;
                  }
                  uVar32 = uVar32 + 0x30;
                } while (uVar32 < uVar33);
              }
              uVar21 = uVar21 + 1;
            } while ((long)uVar21 < (long)uVar20);
          }
        }
      }
code_r0x0209a2c4:
      Aska::Quaternion::CalcEuler(Aska::Vector*, EnumRotateType) const(plVar34 + 0x12,&uStack_c0,0);
      uStack_84 = *(undefined4 *)((long)&uStack_c0 + (long)(int)(uVar8 - 5) * 4);
      plVar29 = (long *)&uStack_84;
      break;
    case 8:
      Aska::Quaternion::CalcEuler(Aska::Vector*, EnumRotateType) const(plVar34 + 0x12,&uStack_c0,0);
      if (param_5 == 0) goto code_r0x02099e7c;
      uVar4 = *(ushort *)(param_5 + 0xf4);
      uVar8 = (ulong)uVar4;
      if (uVar8 == 0) {
code_r0x02099d90:
        bVar7 = false;
        uStack_98 = uStack_108;
        uStack_a0 = plVar30;
      }
      else {
        uVar25 = *(uint *)(param_5 + 0x38);
        uVar20 = (ulong)uVar25;
        if (uVar25 == 0) goto code_r0x02099d90;
        uVar28 = *(ulong *)(param_5 + 0x80);
        uVar21 = 0;
        uVar33 = uVar28 + uVar20 * 0x30;
        do {
          uVar32 = uVar28;
          if (*(long **)(*(long *)(param_5 + 0x78) + uVar21 * 0x10 + 8) == plVar34) {
            do {
              if (((uVar21 == *(ushort *)(uVar32 + 0x2c)) &&
                  (plVar29 = *(long **)(uVar32 + 8), plVar29 != (long *)0x0)) &&
                 ((lVar14 = *(long *)(uVar32 + 0x18), lVar14 != 0 && (*(char *)(lVar14 + 6) == '\b')
                  ))) {
                if ((*(byte *)(uVar32 + 0x2e) >> 3 & 1) != 0) {
                  (**(code **)(*plVar29 + 0x148))(plVar29,&uStack_b0,1);
                  goto code_r0x0209a148;
                }
                uVar8 = (ulong)(uint)*(float *)(lVar14 + 0xc);
                if ((*(float *)(lVar14 + 0xc) <= fVar46) &&
                   (uVar8 = uVar39, *(float *)(lVar14 + 0x10) < fVar46)) {
                  uVar8 = (ulong)(uint)*(float *)(lVar14 + 0x10);
                }
                (**(code **)(*plVar29 + 0x80))(uVar8,plVar29,&uStack_b0,&fStack_88);
                fVar43 = (float)(**(code **)(*plVar29 + 0x1d0))(plVar29);
                goto code_r0x02099f84;
              }
              uVar32 = uVar32 + 0x30;
            } while (uVar32 < uVar33);
          }
          uVar21 = uVar21 + 1;
        } while ((long)uVar21 < (long)uVar8);
        if (uVar25 != 0) {
          uVar21 = 0;
          do {
            uVar32 = uVar28;
            if (*(long **)(*(long *)(param_5 + 0x78) + uVar21 * 0x10 + 8) == plVar34) {
code_r0x020998f4:
              if ((((uVar21 != *(ushort *)(uVar32 + 0x2c)) ||
                   (plVar29 = *(long **)(uVar32 + 8), plVar29 == (long *)0x0)) ||
                  (lVar14 = *(long *)(uVar32 + 0x18), lVar14 == 0)) ||
                 (*(char *)(lVar14 + 6) != '\t')) goto code_r0x0209991c;
              if ((*(byte *)(uVar32 + 0x2e) >> 3 & 1) == 0) {
                uVar8 = (ulong)(uint)*(float *)(lVar14 + 0xc);
                if ((*(float *)(lVar14 + 0xc) <= fVar46) &&
                   (uVar8 = uVar39, *(float *)(lVar14 + 0x10) < fVar46)) {
                  uVar8 = (ulong)(uint)*(float *)(lVar14 + 0x10);
                }
                (**(code **)(*plVar29 + 0x80))(uVar8,plVar29,&uStack_b0,&fStack_88);
                fVar43 = (float)(**(code **)(*plVar29 + 0x1d0))(plVar29);
                param_6 = lStack_d8;
code_r0x02099f84:
                fStack_88 = fStack_88 * fVar42 * fVar43;
              }
              else {
                (**(code **)(*plVar29 + 0x148))(plVar29,&uStack_b0,1);
                param_6 = lStack_d8;
code_r0x0209a148:
                fStack_88 = 0.0;
              }
              goto code_r0x0209a14c;
            }
code_r0x02099928:
            uVar21 = uVar21 + 1;
          } while ((long)uVar21 < (long)uVar8);
        }
        uStack_98 = uStack_108;
        uStack_a0 = plVar30;
        if (uVar4 == 0) {
          bVar7 = false;
        }
        else if (uVar25 == 0) {
          bVar7 = false;
          param_6 = lStack_d8;
        }
        else {
          uVar21 = 0;
          do {
            uVar32 = uVar28;
            if (*(long **)(*(long *)(param_5 + 0x78) + uVar21 * 0x10 + 8) == plVar34) {
              do {
                if (((uVar21 == *(ushort *)(uVar32 + 0x2c)) &&
                    (plVar29 = *(long **)(uVar32 + 8), plVar29 != (long *)0x0)) &&
                   ((lVar14 = *(long *)(uVar32 + 0x18), lVar14 != 0 &&
                    (*(char *)(lVar14 + 6) == '\x05')))) {
                  if ((*(byte *)(uVar32 + 0x2e) >> 3 & 1) == 0) {
                    uVar8 = (ulong)(uint)*(float *)(lVar14 + 0xc);
                    if ((*(float *)(lVar14 + 0xc) <= fVar46) &&
                       (uVar8 = uVar39, *(float *)(lVar14 + 0x10) < fVar46)) {
                      uVar8 = (ulong)(uint)*(float *)(lVar14 + 0x10);
                    }
                    (**(code **)(*plVar29 + 0x80))(uVar8,plVar29,&uStack_84,&fStack_88);
                    fVar43 = (float)(**(code **)(*plVar29 + 0x1d0))(plVar29);
                    fStack_88 = fStack_88 * fVar42 * fVar43;
                  }
                  else {
                    (**(code **)(*plVar29 + 0x148))(plVar29,&uStack_84,1);
                  }
                  bVar7 = true;
                  uStack_a0 = (long *)CONCAT44(uStack_a0._4_4_,uStack_84);
                  uVar20 = (ulong)*(uint *)(param_5 + 0x38);
                  uVar28 = *(ulong *)(param_5 + 0x80);
                  uVar4 = *(ushort *)(param_5 + 0xf4);
                  uVar8 = (ulong)uVar4;
                  goto joined_r0x0209a95c;
                }
                uVar32 = uVar32 + 0x30;
              } while (uVar32 < uVar33);
            }
            uVar21 = uVar21 + 1;
          } while ((long)uVar21 < (long)uVar8);
          bVar7 = false;
joined_r0x0209a95c:
          param_6 = lStack_d8;
          if ((uVar4 != 0) && (uVar25 = (uint)uVar20, uVar25 != 0)) {
            uVar21 = 0;
            do {
              uVar33 = uVar28;
              if (*(long **)(*(long *)(param_5 + 0x78) + uVar21 * 0x10 + 8) == plVar34) {
                do {
                  if ((((uVar21 == *(ushort *)(uVar33 + 0x2c)) &&
                       (plVar29 = *(long **)(uVar33 + 8), plVar29 != (long *)0x0)) &&
                      (lVar14 = *(long *)(uVar33 + 0x18), lVar14 != 0)) &&
                     (*(char *)(lVar14 + 6) == '\x06')) {
                    if ((*(byte *)(uVar33 + 0x2e) >> 3 & 1) == 0) {
                      uVar8 = (ulong)(uint)*(float *)(lVar14 + 0xc);
                      if ((*(float *)(lVar14 + 0xc) <= fVar46) &&
                         (uVar8 = uVar39, *(float *)(lVar14 + 0x10) < fVar46)) {
                        uVar8 = (ulong)(uint)*(float *)(lVar14 + 0x10);
                      }
                      (**(code **)(*plVar29 + 0x80))(uVar8,plVar29,&uStack_84,&fStack_88);
                      fVar43 = (float)(**(code **)(*plVar29 + 0x1d0))(plVar29);
                      fStack_88 = fStack_88 * fVar42 * fVar43;
                    }
                    else {
                      (**(code **)(*plVar29 + 0x148))(plVar29,&uStack_84,1);
                    }
                    bVar7 = true;
                    uStack_a0 = (long *)CONCAT44(uStack_84,(float)uStack_a0);
                    uVar25 = *(uint *)(param_5 + 0x38);
                    uVar28 = *(ulong *)(param_5 + 0x80);
                    uVar8 = (ulong)*(ushort *)(param_5 + 0xf4);
                    goto code_r0x0209aac8;
                  }
                  uVar33 = uVar33 + 0x30;
                } while (uVar33 < uVar28 + uVar20 * 0x30);
              }
              uVar21 = uVar21 + 1;
            } while ((long)uVar21 < (long)uVar8);
code_r0x0209aac8:
            param_6 = lStack_d8;
            if (((int)uVar8 != 0) && (uVar25 != 0)) {
              uVar20 = 0;
              do {
                uVar21 = uVar28;
                if (*(long **)(*(long *)(param_5 + 0x78) + uVar20 * 0x10 + 8) == plVar34) {
                  do {
                    if ((((uVar20 == *(ushort *)(uVar21 + 0x2c)) &&
                         (plVar29 = *(long **)(uVar21 + 8), plVar29 != (long *)0x0)) &&
                        (lVar14 = *(long *)(uVar21 + 0x18), lVar14 != 0)) &&
                       (*(char *)(lVar14 + 6) == '\a')) {
                      if ((*(byte *)(uVar21 + 0x2e) >> 3 & 1) == 0) {
                        uVar8 = (ulong)(uint)*(float *)(lVar14 + 0xc);
                        if ((*(float *)(lVar14 + 0xc) <= fVar46) &&
                           (uVar8 = uVar39, *(float *)(lVar14 + 0x10) < fVar46)) {
                          uVar8 = (ulong)(uint)*(float *)(lVar14 + 0x10);
                        }
                        (**(code **)(*plVar29 + 0x80))(uVar8,plVar29,&uStack_84,&fStack_88);
                        fVar43 = (float)(**(code **)(*plVar29 + 0x1d0))(plVar29);
                        fStack_88 = fStack_88 * fVar42 * fVar43;
                      }
                      else {
                        (**(code **)(*plVar29 + 0x148))(plVar29,&uStack_84,1);
                      }
                      bVar7 = true;
                      uStack_98 = CONCAT44(uStack_98._4_4_,uStack_84);
                      param_6 = lStack_d8;
                      goto code_r0x02099d9c;
                    }
                    uVar21 = uVar21 + 0x30;
                  } while (uVar21 < uVar28 + (ulong)uVar25 * 0x30);
                }
                uVar20 = uVar20 + 1;
              } while ((long)uVar20 < (long)uVar8);
            }
          }
        }
      }
code_r0x02099d9c:
      Aska::Quaternion::CreateFromEuler(float, float, float, EnumRotateType)((ulong)uStack_a0 & 0xffffffff,uStack_a0._4_4_,(undefined4)uStack_98,&uStack_b0
                      ,0);
      if (!bVar7) goto code_r0x02099e7c;
code_r0x0209a14c:
      plVar29 = &uStack_b0;
      break;
    case 9:
      Aska::Quaternion::CalcEuler(Aska::Vector*, EnumRotateType) const(plVar34 + 0x12,afStack_d0,0);
      if (param_5 != 0) {
        uVar4 = *(ushort *)(param_5 + 0xf4);
        uVar8 = (ulong)uVar4;
        if (uVar8 == 0) {
          uStack_98 = uStack_108;
          uStack_a0 = plVar30;
          uStack_b8 = uStack_108;
          uStack_c0 = plVar30;
          goto code_r0x02099e7c;
        }
        uVar25 = *(uint *)(param_5 + 0x38);
        uVar20 = (ulong)uVar25;
        uVar21 = *(ulong *)(param_5 + 0x80);
        uVar28 = uVar21 + uVar20 * 0x30;
        if (uVar25 != 0) {
          uVar33 = 0;
          do {
            uVar32 = uVar21;
            if (*(long **)(*(long *)(param_5 + 0x78) + uVar33 * 0x10 + 8) == plVar34) {
              do {
                if ((((uVar33 == *(ushort *)(uVar32 + 0x2c)) &&
                     (plVar29 = *(long **)(uVar32 + 8), plVar29 != (long *)0x0)) &&
                    (lVar14 = *(long *)(uVar32 + 0x18), lVar14 != 0)) &&
                   (*(char *)(lVar14 + 6) == '\t')) {
                  if ((*(byte *)(uVar32 + 0x2e) >> 3 & 1) != 0) {
                    (**(code **)(*plVar29 + 0x148))(plVar29,&uStack_b0,1);
                    fStack_88 = 0.0;
                    goto code_r0x0209a85c;
                  }
                  uVar8 = (ulong)(uint)*(float *)(lVar14 + 0xc);
                  if ((*(float *)(lVar14 + 0xc) <= fVar46) &&
                     (uVar8 = uVar39, *(float *)(lVar14 + 0x10) < fVar46)) {
                    uVar8 = (ulong)(uint)*(float *)(lVar14 + 0x10);
                  }
                  (**(code **)(*plVar29 + 0x80))(uVar8,plVar29,&uStack_b0,&fStack_88);
                  fVar43 = (float)(**(code **)(*plVar29 + 0x1d0))(plVar29);
                  goto code_r0x02099fe8;
                }
                uVar32 = uVar32 + 0x30;
              } while (uVar32 < uVar28);
            }
            uVar33 = uVar33 + 1;
          } while ((long)uVar33 < (long)uVar8);
          if (uVar25 != 0) {
            uVar33 = 0;
            do {
              uVar32 = uVar21;
              if (*(long **)(*(long *)(param_5 + 0x78) + uVar33 * 0x10 + 8) == plVar34) {
                do {
                  if (((uVar33 == *(ushort *)(uVar32 + 0x2c)) &&
                      (plVar29 = *(long **)(uVar32 + 8), plVar29 != (long *)0x0)) &&
                     ((lVar14 = *(long *)(uVar32 + 0x18), lVar14 != 0 &&
                      (*(char *)(lVar14 + 6) == '\b')))) {
                    if ((*(byte *)(uVar32 + 0x2e) >> 3 & 1) == 0) {
                      uVar8 = (ulong)(uint)*(float *)(lVar14 + 0xc);
                      if ((*(float *)(lVar14 + 0xc) <= fVar46) &&
                         (uVar8 = uVar39, *(float *)(lVar14 + 0x10) < fVar46)) {
                        uVar8 = (ulong)(uint)*(float *)(lVar14 + 0x10);
                      }
                      (**(code **)(*plVar29 + 0x80))(uVar8,plVar29,&uStack_b0,&fStack_88);
                      fVar43 = (float)(**(code **)(*plVar29 + 0x1d0))(plVar29);
                      param_6 = lStack_d8;
code_r0x02099fe8:
                      fStack_88 = fStack_88 * fVar42 * fVar43;
                    }
                    else {
                      (**(code **)(*plVar29 + 0x148))(plVar29,&uStack_b0,1);
                      fStack_88 = 0.0;
                      param_6 = lStack_d8;
                    }
                    goto code_r0x0209a85c;
                  }
                  uVar32 = uVar32 + 0x30;
                } while (uVar32 < uVar28);
              }
              uVar33 = uVar33 + 1;
            } while ((long)uVar33 < (long)uVar8);
          }
        }
        uStack_98 = uStack_108;
        uStack_a0 = plVar30;
        uStack_b8 = uStack_108;
        uStack_c0 = plVar30;
        if ((uVar4 == 0) || (uVar25 == 0)) goto code_r0x02099e7c;
        uVar33 = 0;
        do {
          uVar32 = uVar21;
          if (*(long **)(*(long *)(param_5 + 0x78) + uVar33 * 0x10 + 8) == plVar34) {
            do {
              if ((((uVar33 == *(ushort *)(uVar32 + 0x2c)) &&
                   (plVar29 = *(long **)(uVar32 + 8), plVar29 != (long *)0x0)) &&
                  (lVar14 = *(long *)(uVar32 + 0x18), lVar14 != 0)) &&
                 (*(char *)(lVar14 + 6) == '\x05')) {
                if ((*(byte *)(uVar32 + 0x2e) >> 3 & 1) == 0) {
                  uVar8 = (ulong)(uint)*(float *)(lVar14 + 0xc);
                  if ((*(float *)(lVar14 + 0xc) <= fVar46) &&
                     (uVar8 = uVar39, *(float *)(lVar14 + 0x10) < fVar46)) {
                    uVar8 = (ulong)(uint)*(float *)(lVar14 + 0x10);
                  }
                  (**(code **)(*plVar29 + 0x80))(uVar8,plVar29,&uStack_84,&fStack_88);
                  fVar43 = (float)(**(code **)(*plVar29 + 0x1d0))(plVar29);
                  fStack_88 = fStack_88 * fVar42 * fVar43;
                }
                else {
                  (**(code **)(*plVar29 + 0x148))(plVar29,&uStack_84,1);
                  fStack_88 = 0.0;
                }
                uStack_c0 = (long *)CONCAT44(uStack_c0._4_4_,fStack_88);
                bVar7 = true;
                uStack_a0 = (long *)CONCAT44(uStack_a0._4_4_,uStack_84);
                uVar20 = (ulong)*(uint *)(param_5 + 0x38);
                uVar21 = *(ulong *)(param_5 + 0x80);
                uVar4 = *(ushort *)(param_5 + 0xf4);
                uVar8 = (ulong)uVar4;
                goto joined_r0x0209a4ec;
              }
              uVar32 = uVar32 + 0x30;
            } while (uVar32 < uVar28);
          }
          uVar33 = uVar33 + 1;
        } while ((long)uVar33 < (long)uVar8);
        bVar7 = false;
joined_r0x0209a4ec:
        if ((uVar4 != 0) && (uVar25 = (uint)uVar20, uVar25 != 0)) {
          uVar28 = 0;
          do {
            uVar33 = uVar21;
            if (*(long **)(*(long *)(param_5 + 0x78) + uVar28 * 0x10 + 8) == plVar34) {
              do {
                if ((((uVar28 == *(ushort *)(uVar33 + 0x2c)) &&
                     (plVar29 = *(long **)(uVar33 + 8), plVar29 != (long *)0x0)) &&
                    (lVar14 = *(long *)(uVar33 + 0x18), lVar14 != 0)) &&
                   (*(char *)(lVar14 + 6) == '\x06')) {
                  if ((*(byte *)(uVar33 + 0x2e) >> 3 & 1) == 0) {
                    uVar8 = (ulong)(uint)*(float *)(lVar14 + 0xc);
                    if ((*(float *)(lVar14 + 0xc) <= fVar46) &&
                       (uVar8 = uVar39, *(float *)(lVar14 + 0x10) < fVar46)) {
                      uVar8 = (ulong)(uint)*(float *)(lVar14 + 0x10);
                    }
                    (**(code **)(*plVar29 + 0x80))(uVar8,plVar29,&uStack_84,&fStack_88);
                    fVar43 = (float)(**(code **)(*plVar29 + 0x1d0))(plVar29);
                    fStack_88 = fStack_88 * fVar42 * fVar43;
                  }
                  else {
                    (**(code **)(*plVar29 + 0x148))(plVar29,&uStack_84,1);
                    fStack_88 = 0.0;
                  }
                  uStack_c0 = (long *)CONCAT44(fStack_88,(float)uStack_c0);
                  bVar7 = true;
                  uStack_a0 = (long *)CONCAT44(uStack_84,(float)uStack_a0);
                  uVar25 = *(uint *)(param_5 + 0x38);
                  uVar21 = *(ulong *)(param_5 + 0x80);
                  uVar8 = (ulong)*(ushort *)(param_5 + 0xf4);
                  goto code_r0x0209a7d4;
                }
                uVar33 = uVar33 + 0x30;
              } while (uVar33 < uVar21 + uVar20 * 0x30);
            }
            uVar28 = uVar28 + 1;
          } while ((long)uVar28 < (long)uVar8);
code_r0x0209a7d4:
          if (((int)uVar8 != 0) && (uVar25 != 0)) {
            uVar20 = 0;
            do {
              uVar28 = uVar21;
              if (*(long **)(*(long *)(param_5 + 0x78) + uVar20 * 0x10 + 8) == plVar34) {
                do {
                  if ((((uVar20 == *(ushort *)(uVar28 + 0x2c)) &&
                       (plVar29 = *(long **)(uVar28 + 8), plVar29 != (long *)0x0)) &&
                      (lVar14 = *(long *)(uVar28 + 0x18), lVar14 != 0)) &&
                     (*(char *)(lVar14 + 6) == '\a')) {
                    if ((*(byte *)(uVar28 + 0x2e) >> 3 & 1) == 0) {
                      uVar8 = (ulong)(uint)*(float *)(lVar14 + 0xc);
                      if ((*(float *)(lVar14 + 0xc) <= fVar46) &&
                         (uVar8 = uVar39, *(float *)(lVar14 + 0x10) < fVar46)) {
                        uVar8 = (ulong)(uint)*(float *)(lVar14 + 0x10);
                      }
                      (**(code **)(*plVar29 + 0x80))(uVar8,plVar29,&uStack_84,&fStack_88);
                      fVar43 = (float)(**(code **)(*plVar29 + 0x1d0))(plVar29);
                      fStack_88 = fStack_88 * fVar42 * fVar43;
                    }
                    else {
                      (**(code **)(*plVar29 + 0x148))(plVar29,&uStack_84,1);
                      fStack_88 = 0.0;
                    }
                    uStack_b8 = CONCAT44(uStack_b8._4_4_,fStack_88);
                    uStack_98 = CONCAT44(uStack_98._4_4_,uStack_84);
                    goto code_r0x0209a848;
                  }
                  uVar28 = uVar28 + 0x30;
                } while (uVar28 < uVar21 + (ulong)uVar25 * 0x30);
              }
              uVar20 = uVar20 + 1;
            } while ((long)uVar20 < (long)uVar8);
          }
        }
        param_6 = lStack_d8;
        if (!bVar7) goto code_r0x02099e7c;
code_r0x0209a848:
        param_6 = lStack_d8;
        Aska::Quaternion::CreateFromEuler(float, float, float, EnumRotateType)((ulong)uStack_a0 & 0xffffffff,uStack_a0._4_4_,(undefined4)uStack_98,
                        &uStack_b0,0);
code_r0x0209a85c:
        plVar29 = &uStack_b0;
        goto code_r0x02099d7c;
      }
code_r0x02099e7c:
      plVar29 = plVar34 + 0x12;
      pcVar17 = *(code **)(*plStack_f0 + 0x48);
      goto code_r0x0209a2f4;
    case 10:
    case 0xb:
    case 0xc:
      lVar14 = uVar8 - 10;
      if ((param_5 != 0) && (uVar8 = (ulong)*(ushort *)(param_5 + 0xf4), uVar8 != 0)) {
        uVar35 = *(uint *)(param_5 + 0x38);
        if (uVar35 != 0) {
          uVar21 = *(ulong *)(param_5 + 0x80);
          uVar20 = 0;
          uVar28 = uVar21 + (ulong)uVar35 * 0x30;
          do {
            uVar33 = uVar21;
            if (*(long **)(*(long *)(param_5 + 0x78) + uVar20 * 0x10 + 8) == plVar34) {
              do {
                if ((((uVar20 == *(ushort *)(uVar33 + 0x2c)) &&
                     (plVar29 = *(long **)(uVar33 + 8), plVar29 != (long *)0x0)) &&
                    (lVar19 = *(long *)(uVar33 + 0x18), lVar19 != 0)) &&
                   (*(byte *)(lVar19 + 6) == uVar25)) {
                  if ((*(byte *)(uVar33 + 0x2e) >> 3 & 1) == 0) goto code_r0x02099d1c;
                  (**(code **)(*plVar29 + 0x148))(plVar29,&uStack_84,1);
                  fStack_88 = 0.0;
                  goto code_r0x02099d74;
                }
                uVar33 = uVar33 + 0x30;
              } while (uVar33 < uVar28);
            }
            uVar20 = uVar20 + 1;
          } while ((long)uVar20 < (long)uVar8);
          if (uVar35 != 0) {
            uVar20 = 0;
            do {
              uVar33 = uVar21;
              if (*(long **)(*(long *)(param_5 + 0x78) + uVar20 * 0x10 + 8) == plVar34) {
                do {
                  if (((uVar20 == *(ushort *)(uVar33 + 0x2c)) &&
                      (plVar29 = *(long **)(uVar33 + 8), plVar29 != (long *)0x0)) &&
                     ((lVar19 = *(long *)(uVar33 + 0x18), lVar19 != 0 &&
                      (*(char *)(lVar19 + 6) == '\r')))) {
                    if ((*(byte *)(uVar33 + 0x2e) >> 3 & 1) == 0) {
                      uVar8 = (ulong)(uint)*(float *)(lVar19 + 0xc);
                      if ((*(float *)(lVar19 + 0xc) <= fVar46) &&
                         (uVar8 = uVar39, *(float *)(lVar19 + 0x10) < fVar46)) {
                        uVar8 = (ulong)(uint)*(float *)(lVar19 + 0x10);
                      }
                      (**(code **)(*plVar29 + 0x80))(uVar8,plVar29,&uStack_a0,&uStack_c0);
                      fStack_88 = *(float *)((long)&uStack_c0 + lVar14 * 4);
                      fVar43 = (float)(**(code **)(*plVar29 + 0x1d0))(plVar29);
                      fStack_88 = fStack_88 * fVar42 * fVar43;
                    }
                    else {
                      (**(code **)(*plVar29 + 0x148))(plVar29,&uStack_a0,1);
                      lVar14 = (long)(int)lVar14;
                      fStack_88 = 0.0;
                    }
                    uStack_84 = *(undefined4 *)((long)&uStack_a0 + lVar14 * 4);
                    goto code_r0x02099d74;
                  }
                  uVar33 = uVar33 + 0x30;
                } while (uVar33 < uVar28);
              }
              uVar20 = uVar20 + 1;
            } while ((long)uVar20 < (long)uVar8);
          }
        }
      }
      uVar13 = *(undefined4 *)((long)plVar34 + (long)(int)lVar14 * 4 + 0xa0);
code_r0x02099670:
      uStack_a0 = (long *)CONCAT44(uStack_a0._4_4_,uVar13);
      plVar29 = &uStack_a0;
      break;
    case 0xd:
      if (param_5 != 0) {
        uVar4 = *(ushort *)(param_5 + 0xf4);
        uVar8 = (ulong)uVar4;
        if (uVar8 == 0) {
          uStack_98 = uStack_108;
          uStack_a0 = plVar30;
          uStack_b8 = uStack_108;
          uStack_c0 = plVar30;
        }
        else {
          uVar25 = *(uint *)(param_5 + 0x38);
          uVar20 = (ulong)uVar25;
          uVar21 = *(ulong *)(param_5 + 0x80);
          uVar28 = uVar21 + uVar20 * 0x30;
          if (uVar25 != 0) {
            uVar33 = 0;
            do {
              uVar32 = uVar21;
              if (*(long **)(*(long *)(param_5 + 0x78) + uVar33 * 0x10 + 8) == plVar34) {
                do {
                  if ((((uVar33 == *(ushort *)(uVar32 + 0x2c)) &&
                       (plVar26 = *(long **)(uVar32 + 8), plVar26 != (long *)0x0)) &&
                      (lVar14 = *(long *)(uVar32 + 0x18), lVar14 != 0)) &&
                     (*(char *)(lVar14 + 6) == '\r')) goto code_r0x02099db8;
                  uVar32 = uVar32 + 0x30;
                } while (uVar32 < uVar28);
              }
              uVar33 = uVar33 + 1;
            } while ((long)uVar33 < (long)uVar8);
          }
          uStack_98 = uStack_108;
          uStack_a0 = plVar30;
          uStack_b8 = uStack_108;
          uStack_c0 = plVar30;
          if ((uVar4 != 0) && (uVar25 != 0)) {
            uVar33 = 0;
            do {
              uVar32 = uVar21;
              if (*(long **)(*(long *)(param_5 + 0x78) + uVar33 * 0x10 + 8) == plVar34) {
                do {
                  if (((uVar33 == *(ushort *)(uVar32 + 0x2c)) &&
                      (plVar29 = *(long **)(uVar32 + 8), plVar29 != (long *)0x0)) &&
                     ((lVar14 = *(long *)(uVar32 + 0x18), lVar14 != 0 &&
                      (*(char *)(lVar14 + 6) == '\x05')))) {
                    if ((*(byte *)(uVar32 + 0x2e) >> 3 & 1) == 0) {
                      uVar8 = (ulong)(uint)*(float *)(lVar14 + 0xc);
                      if ((*(float *)(lVar14 + 0xc) <= fVar46) &&
                         (uVar8 = uVar39, *(float *)(lVar14 + 0x10) < fVar46)) {
                        uVar8 = (ulong)(uint)*(float *)(lVar14 + 0x10);
                      }
                      (**(code **)(*plVar29 + 0x80))(uVar8,plVar29,&uStack_84,&fStack_88);
                      fVar43 = (float)(**(code **)(*plVar29 + 0x1d0))(plVar29);
                      fStack_88 = fStack_88 * fVar42 * fVar43;
                    }
                    else {
                      (**(code **)(*plVar29 + 0x148))(plVar29,&uStack_84,1);
                      fStack_88 = 0.0;
                    }
                    uStack_c0 = (long *)CONCAT44(uStack_c0._4_4_,fStack_88);
                    bVar7 = true;
                    uStack_a0 = (long *)CONCAT44(uStack_a0._4_4_,uStack_84);
                    uVar20 = (ulong)*(uint *)(param_5 + 0x38);
                    uVar21 = *(ulong *)(param_5 + 0x80);
                    uVar4 = *(ushort *)(param_5 + 0xf4);
                    uVar8 = (ulong)uVar4;
                    goto joined_r0x0209a444;
                  }
                  uVar32 = uVar32 + 0x30;
                } while (uVar32 < uVar28);
              }
              uVar33 = uVar33 + 1;
            } while ((long)uVar33 < (long)uVar8);
            bVar7 = false;
joined_r0x0209a444:
            if ((uVar4 != 0) && (uVar25 = (uint)uVar20, uVar25 != 0)) {
              uVar28 = 0;
              do {
                uVar33 = uVar21;
                if (*(long **)(*(long *)(param_5 + 0x78) + uVar28 * 0x10 + 8) == plVar34) {
                  do {
                    if ((((uVar28 == *(ushort *)(uVar33 + 0x2c)) &&
                         (plVar29 = *(long **)(uVar33 + 8), plVar29 != (long *)0x0)) &&
                        (lVar14 = *(long *)(uVar33 + 0x18), lVar14 != 0)) &&
                       (*(char *)(lVar14 + 6) == '\x06')) {
                      if ((*(byte *)(uVar33 + 0x2e) >> 3 & 1) == 0) {
                        uVar8 = (ulong)(uint)*(float *)(lVar14 + 0xc);
                        if ((*(float *)(lVar14 + 0xc) <= fVar46) &&
                           (uVar8 = uVar39, *(float *)(lVar14 + 0x10) < fVar46)) {
                          uVar8 = (ulong)(uint)*(float *)(lVar14 + 0x10);
                        }
                        (**(code **)(*plVar29 + 0x80))(uVar8,plVar29,&uStack_84,&fStack_88);
                        fVar43 = (float)(**(code **)(*plVar29 + 0x1d0))(plVar29);
                        fStack_88 = fStack_88 * fVar42 * fVar43;
                      }
                      else {
                        (**(code **)(*plVar29 + 0x148))(plVar29,&uStack_84,1);
                        fStack_88 = 0.0;
                      }
                      uStack_c0 = (long *)CONCAT44(fStack_88,(float)uStack_c0);
                      bVar7 = true;
                      uStack_a0 = (long *)CONCAT44(uStack_84,(float)uStack_a0);
                      uVar25 = *(uint *)(param_5 + 0x38);
                      uVar21 = *(ulong *)(param_5 + 0x80);
                      uVar8 = (ulong)*(ushort *)(param_5 + 0xf4);
                      goto code_r0x0209a708;
                    }
                    uVar33 = uVar33 + 0x30;
                  } while (uVar33 < uVar21 + uVar20 * 0x30);
                }
                uVar28 = uVar28 + 1;
              } while ((long)uVar28 < (long)uVar8);
code_r0x0209a708:
              if (((int)uVar8 == 0) || (uVar25 == 0)) {
                param_6 = lStack_d8;
                if (bVar7) goto code_r0x0209a190;
                goto code_r0x02099ea0;
              }
              uVar20 = 0;
              do {
                uVar28 = uVar21;
                if (*(long **)(*(long *)(param_5 + 0x78) + uVar20 * 0x10 + 8) == plVar34) {
                  do {
                    if ((((uVar20 == *(ushort *)(uVar28 + 0x2c)) &&
                         (plVar29 = *(long **)(uVar28 + 8), plVar29 != (long *)0x0)) &&
                        (lVar14 = *(long *)(uVar28 + 0x18), lVar14 != 0)) &&
                       (*(char *)(lVar14 + 6) == '\a')) {
                      if ((*(byte *)(uVar28 + 0x2e) >> 3 & 1) == 0) {
                        uVar8 = (ulong)(uint)*(float *)(lVar14 + 0xc);
                        if ((*(float *)(lVar14 + 0xc) <= fVar46) &&
                           (uVar8 = uVar39, *(float *)(lVar14 + 0x10) < fVar46)) {
                          uVar8 = (ulong)(uint)*(float *)(lVar14 + 0x10);
                        }
                        (**(code **)(*plVar29 + 0x80))(uVar8,plVar29,&uStack_84,&fStack_88);
                        fVar43 = (float)(**(code **)(*plVar29 + 0x1d0))(plVar29);
                        fStack_88 = fStack_88 * fVar42 * fVar43;
                      }
                      else {
                        (**(code **)(*plVar29 + 0x148))(plVar29,&uStack_84,1);
                        fStack_88 = 0.0;
                      }
                      uStack_b8 = CONCAT44(uStack_b8._4_4_,fStack_88);
                      uStack_98 = CONCAT44(uStack_98._4_4_,uStack_84);
                      param_6 = lStack_d8;
                      goto code_r0x0209a190;
                    }
                    uVar28 = uVar28 + 0x30;
                  } while (uVar28 < uVar21 + (ulong)uVar25 * 0x30);
                }
                uVar20 = uVar20 + 1;
              } while ((long)uVar20 < (long)uVar8);
            }
            param_6 = lStack_d8;
            if (bVar7) goto code_r0x0209a190;
          }
        }
      }
code_r0x02099ea0:
      plVar29 = plVar34 + 0x14;
      param_6 = lStack_d8;
      break;
    default:
      lVar14 = *plVar41;
      if (((param_5 != 0) && ((ulong)*(ushort *)(param_5 + 0xf4) != 0)) &&
         (*(uint *)(param_5 + 0x38) != 0)) {
        uVar8 = 0;
        do {
          plVar29 = *(long **)(param_5 + 0x80);
          if (*(long **)(*(long *)(param_5 + 0x78) + uVar8 * 0x10 + 8) == plVar34) {
            do {
              if ((uVar8 == *(ushort *)((long)plVar29 + 0x2c)) && (*plVar29 == lVar14)) {
                plVar26 = (long *)plVar29[1];
                if (plVar26 == (long *)0x0) goto code_r0x02099ef8;
                if ((*(byte *)((long)plVar29 + 0x2e) >> 3 & 1) != 0) {
                  lVar14 = *plVar26;
                  goto code_r0x0209a180;
                }
                fVar43 = *(float *)(plVar29[3] + 0xc);
                uVar8 = (ulong)(uint)fVar43;
                if ((fVar43 <= fVar46) &&
                   (fVar43 = *(float *)(plVar29[3] + 0x10), uVar8 = uVar39, fVar43 < fVar46)) {
                  uVar8 = (ulong)(uint)fVar43;
                }
                (**(code **)(*plVar26 + 0x80))(uVar8,plVar26,&uStack_a0,&uStack_b0);
                goto code_r0x0209a188;
              }
              plVar29 = plVar29 + 6;
            } while (plVar29 < *(long **)(param_5 + 0x80) + (ulong)*(uint *)(param_5 + 0x38) * 6);
          }
          uVar8 = uVar8 + 1;
        } while ((long)uVar8 < (long)(ulong)*(ushort *)(param_5 + 0xf4));
      }
code_r0x02099ef8:
      if (lVar14 != -1) {
        (**(code **)(*plVar34 + 0x28))(plVar34,lVar14,&uStack_a0);
      }
      goto code_r0x0209a188;
    case 0x1a:
    case 0x1b:
    case 0x1c:
    case 0x1d:
      lVar14 = *plVar41;
      if (((param_5 != 0) && ((ulong)*(ushort *)(param_5 + 0xf4) != 0)) &&
         (*(uint *)(param_5 + 0x38) != 0)) {
        uVar20 = 0;
        do {
          plVar29 = *(long **)(param_5 + 0x80);
          if (*(long **)(*(long *)(param_5 + 0x78) + uVar20 * 0x10 + 8) == plVar34) {
            do {
              if (((uVar20 == *(ushort *)((long)plVar29 + 0x2c)) &&
                  (plVar26 = (long *)plVar29[1], plVar26 != (long *)0x0)) &&
                 ((*plVar29 == lVar14 &&
                  ((lVar19 = plVar29[3], lVar19 != 0 && (*(byte *)(lVar19 + 6) == uVar25)))))) {
                if ((*(byte *)((long)plVar29 + 0x2e) >> 3 & 1) != 0) {
                  (**(code **)(*plVar26 + 0x148))(plVar26,&uStack_84,1);
                  fStack_88 = 0.0;
                  goto code_r0x02099d74;
                }
                uVar8 = (ulong)(uint)*(float *)(lVar19 + 0xc);
                if ((*(float *)(lVar19 + 0xc) <= fVar46) &&
                   (uVar8 = uVar39, *(float *)(lVar19 + 0x10) < fVar46)) {
                  uVar8 = (ulong)(uint)*(float *)(lVar19 + 0x10);
                }
                (**(code **)(*plVar26 + 0x80))(uVar8,plVar26,&uStack_84,&fStack_88);
                goto code_r0x02099cbc;
              }
              plVar29 = plVar29 + 6;
            } while (plVar29 < *(long **)(param_5 + 0x80) + (ulong)*(uint *)(param_5 + 0x38) * 6);
          }
          uVar20 = uVar20 + 1;
        } while ((long)uVar20 < (long)(ulong)*(ushort *)(param_5 + 0xf4));
      }
      if (lVar14 == -1) {
code_r0x02099cbc:
        fStack_88 = 0.0;
      }
      else {
        (**(code **)(*plVar34 + 0x28))(plVar34,lVar14,&uStack_a0);
        uStack_84 = *(undefined4 *)((long)&uStack_108 + uVar8 * 4);
        fStack_88 = 0.0;
      }
      goto code_r0x02099d74;
    }
    pcVar17 = *(code **)(*plStack_f0 + 0x48);
code_r0x0209a2f4:
    pfVar11 = (float *)0x0;
    pfVar12 = (float *)0x0;
    goto code_r0x0209a2fc;
  }
  plVar34 = (long *)0x0;
  plVar26 = (long *)0x0;
  pbVar27 = (byte *)0x0;
  plVar29 = (long *)0x0;
  uVar24 = 0xffffffff;
code_r0x0209ac00:
  uVar25 = *(uint *)(param_4 + 0x3c);
  plStack_e0 = plVar26;
  if ((uVar25 != 0) && (*(int *)(param_4 + 0x48) != 0)) {
    lVar19 = *(long *)(param_4 + 0xb0);
    pbStack_f8 = *(byte **)(param_4 + 0xb8);
    plStack_f0 = (long *)(ulong)(uint)(*(int *)(param_4 + 0xa8) << 2);
    memset(lVar19,0);
    lVar14 = 0;
    uVar39 = 0;
    do {
      lVar15 = *(long *)(param_4 + 0x88) + lVar14;
      if (((*(byte *)(lVar15 + 0x2e) & 3) == 0) &&
         (((fVar44 < *(float *)(*(long *)(lVar15 + 0x18) + 0xc) ||
           (*(float *)(*(long *)(lVar15 + 0x18) + 0x10) < fVar44)) ||
          (uVar40 = (**(code **)(**(long **)(lVar15 + 8) + 0x108))(uVar6), (uVar40 & 1) != 0)))) {
        lVar15 = (uVar39 >> 5 & 0x7ffffff) * 4;
        *(uint *)(lVar19 + lVar15) = *(uint *)(lVar19 + lVar15) | 1 << (ulong)((uint)uVar39 & 0x1f);
      }
      uVar39 = uVar39 + 1;
      lVar14 = lVar14 + 0x30;
    } while (uVar25 != uVar39);
    memcpy(pbStack_f8,lVar19,plStack_f0);
  }
  Aska::AafHandler::RenewalAllControllerCache(float)(uVar6,param_4);
  fVar43 = _UNK_027edb3c;
  fVar46 = _UNK_027edb34;
  if (0 < (int)uVar23) {
    lVar14 = 0;
    uStack_e8 = _UNK_027dbb38;
    plStack_f0 = _UNK_027dbb30;
    plVar30 = plStack_e0;
    lVar19 = lStack_d8;
    do {
      lVar36 = *(long *)(param_4 + 0x80);
      lVar15 = lVar36 + lVar14;
      bVar3 = *(byte *)(lVar15 + 0x2e);
      *(byte *)(lVar15 + 0x2e) = bVar3 | 0x20;
      if ((bVar3 & 7) == 0) {
        uVar4 = *(ushort *)(lVar15 + 0x2c);
        if (uVar24 != uVar4) {
          puVar10 = (undefined8 *)(*(long *)(param_4 + 0x78) + (ulong)uVar4 * 0x10);
          pbVar27 = (byte *)*puVar10;
          plVar29 = (long *)puVar10[1];
          uVar24 = (uint)uVar4;
        }
        plVar26 = *(long **)(lVar36 + lVar14 + 8);
        if ((plVar26 == (long *)0x0) || (**(char **)(lVar36 + lVar14 + 0x10) != '\0'))
        goto code_r0x0209b22c;
        if (lVar19 == 0) {
          plVar34 = plVar29;
          if (plVar29 != (long *)0x0) goto code_r0x0209ae04;
          plVar34 = (long *)0x0;
          goto code_r0x0209b22c;
        }
        if (plVar30 != plVar29) {
          plVar30 = plVar29;
          if ((*pbVar27 >> 2 & 1) == 0) {
            pbVar37 = pbVar27 + 8;
          }
          else {
            puVar16 = *(uint **)(param_4 + 0x18);
            if ((puVar16 == (uint *)0x0) || (*puVar16 <= *(uint *)(pbVar27 + 8))) {
              if (plVar34 != (long *)0x0) goto code_r0x0209ae04;
              goto code_r0x0209b22c;
            }
            pbVar37 = (byte *)((long)puVar16 + (ulong)(*(uint *)(pbVar27 + 8) << 5) + 4);
            if (pbVar37 == (byte *)0x0) goto code_r0x0209adec;
          }
          plVar34 = (long *)Aska::AsfHandler::QuickSearchByNameEx(char const*) const(lVar19,pbVar37);
          if (plVar34 != (long *)0x0) goto code_r0x0209ae04;
          uVar39 = Aska::AsfHandler::GetModifierAnimationId(char const*, Aska::IAnimatable**, int*) const(lStack_d8,pbVar37,&uStack_a0,&uStack_b0);
          plVar34 = uStack_a0;
          lVar19 = lStack_d8;
          if ((uVar39 & 1) == 0) {
            plVar34 = (long *)0x0;
            goto code_r0x0209b22c;
          }
        }
code_r0x0209adec:
        if (plVar34 == (long *)0x0) goto code_r0x0209b22c;
code_r0x0209ae04:
        lVar19 = lStack_d8;
        lVar22 = *(long *)(lVar36 + lVar14 + 0x18);
        if (lVar22 == 0) goto code_r0x0209b22c;
        bVar3 = *(byte *)(lVar15 + 0x2e);
        uVar23 = bVar3 & 0xdf;
        *(char *)(lVar15 + 0x2e) = (char)uVar23;
        uVar39 = uVar6;
        if ((bVar3 >> 3 & 1) == 0) {
          fVar47 = *(float *)(lVar22 + 0xc);
          if (fVar47 <= fVar44) {
            fVar47 = *(float *)(lVar22 + 0x10);
            if (fVar44 <= fVar47) goto code_r0x0209ae74;
            cVar2 = *(char *)(lVar22 + 9);
          }
          else {
            cVar2 = *(char *)(lVar22 + 8);
          }
          uVar39 = (ulong)(uint)fVar47;
          if (cVar2 == '\x05') {
            uVar23 = uVar23 | 0x20;
            *(char *)(lVar15 + 0x2e) = (char)uVar23;
          }
        }
code_r0x0209ae74:
        if (*(byte *)(lVar22 + 4) < 4) {
          uVar18 = *(undefined1 *)(lVar22 + 6);
        }
        else {
          uVar18 = 0;
        }
        plStack_e0 = plVar30;
        switch(uVar18) {
        case 1:
        case 2:
        case 3:
        case 10:
        case 0xb:
        case 0xc:
          if ((uVar23 >> 3 & 1) == 0) {
            (**(code **)(*plVar26 + 0x80))(uVar39,plVar26,&uStack_c0,afStack_d0);
            fVar47 = (float)(**(code **)(*plVar26 + 0x1d0))(plVar26);
            afStack_d0[0] = afStack_d0[0] * fVar42 * fVar47;
          }
          else {
            (**(code **)(*plVar26 + 0x148))(plVar26,&uStack_c0,1);
            afStack_d0[0] = 0.0;
          }
          break;
        case 4:
        case 0xd:
          if ((uVar23 >> 3 & 1) == 0) {
            (**(code **)(*plVar26 + 0x80))(uVar39,plVar26,&uStack_a0,&uStack_b0);
            fVar47 = (float)(**(code **)(*plVar26 + 0x1d0))(plVar26);
            fVar47 = fVar42 * fVar47;
            uStack_b0 = (long *)CONCAT44(fVar47 * uStack_b0._4_4_,(float)uStack_b0 * fVar47);
            uStack_a8 = CONCAT44(uStack_a8._4_4_,fVar47 * (float)uStack_a8);
          }
          else {
            (**(code **)(*plVar26 + 0x148))(plVar26,&uStack_a0,1);
            uStack_a8 = uStack_e8;
            uStack_b0 = plStack_f0;
          }
          puVar10 = &uStack_a0;
          pfVar11 = (float *)&uStack_b0;
          pcVar17 = *(code **)(*plVar26 + 0x48);
          pfVar12 = (float *)&uStack_b0;
          goto code_r0x0209b0f4;
        case 5:
        case 6:
        case 7:
          (**(code **)(*plVar26 + 0x130))(plVar26,0,&uStack_a0);
          if ((*(byte *)(lVar15 + 0x2e) >> 3 & 1) == 0) {
            (**(code **)(*plVar26 + 0x80))(uVar39,plVar26,&uStack_c0,afStack_d0);
            fVar47 = (float)(**(code **)(*plVar26 + 0x1d0))(plVar26);
            afStack_d0[0] = afStack_d0[0] * fVar42 * fVar47;
          }
          else {
            (**(code **)(*plVar26 + 0x148))(plVar26,&uStack_c0,1);
            afStack_d0[0] = 0.0;
          }
          if ((float)uStack_c0 <= (float)uStack_a0) {
            fVar45 = (float)uStack_a0 - (float)uStack_c0;
            fVar47 = fVar43;
          }
          else {
            fVar45 = (float)uStack_c0 - (float)uStack_a0;
            fVar47 = fVar46;
          }
          if (fVar46 < fVar45) {
            uStack_a0 = (long *)CONCAT44(uStack_a0._4_4_,(float)uStack_a0 + fVar47);
            (**(code **)(*plVar26 + 0x138))(plVar26,0,&uStack_b0,&uStack_84);
            (**(code **)(*plVar26 + 0x48))(plVar26,0,&uStack_a0,&uStack_b0,&uStack_84);
          }
          break;
        case 8:
        case 9:
          if ((uVar23 >> 3 & 1) == 0) {
            (**(code **)(*plVar26 + 0x80))(uVar39,plVar26,&uStack_a0,afStack_d0);
            fVar47 = (float)(**(code **)(*plVar26 + 0x1d0))(plVar26);
            afStack_d0[0] = afStack_d0[0] * fVar42 * fVar47;
          }
          else {
            (**(code **)(*plVar26 + 0x148))(plVar26,&uStack_a0,1);
            afStack_d0[0] = 0.0;
          }
          lVar15 = *plVar26;
          puVar10 = &uStack_a0;
          goto code_r0x0209b0e8;
        default:
          if ((uVar23 >> 3 & 1) == 0) {
            (**(code **)(*plVar26 + 0x80))(uVar39,plVar26,&uStack_a0,&uStack_b0);
          }
          else {
            (**(code **)(*plVar26 + 0x148))(plVar26,&uStack_a0,1);
          }
          uStack_a8 = uStack_e8;
          uStack_b0 = plStack_f0;
          (**(code **)(*plVar26 + 0x48))(plVar26,1,&uStack_a0,&uStack_b0,&uStack_b0);
          plVar30 = plStack_e0;
          if (*(long *)(lVar36 + lVar14) != -1) goto code_r0x0209b22c;
          puVar10 = &uStack_a0;
          pfVar11 = (float *)&uStack_b0;
          pfVar12 = (float *)&uStack_b0;
          pcVar17 = *(code **)(*plVar26 + 0x48);
          uVar9 = 0;
          goto code_r0x0209b0f8;
        }
        lVar15 = *plVar26;
        puVar10 = &uStack_c0;
code_r0x0209b0e8:
        pcVar17 = *(code **)(lVar15 + 0x48);
        pfVar11 = afStack_d0;
        pfVar12 = afStack_d0;
code_r0x0209b0f4:
        uVar9 = 1;
code_r0x0209b0f8:
        (*pcVar17)(plVar26,uVar9,puVar10,pfVar11,pfVar12);
        plVar30 = plStack_e0;
      }
code_r0x0209b22c:
      uVar38 = uVar38 - 1;
      lVar14 = lVar14 + 0x30;
    } while (uVar38 != 0);
  }
  *(undefined1 *)(param_4 + 0xf7) = 1;
  return *(undefined4 *)(param_4 + 0xe8);
code_r0x0209991c:
  uVar32 = uVar32 + 0x30;
  if (uVar33 <= uVar32) goto code_r0x02099928;
  goto code_r0x020998f4;
code_r0x02099db8:
  if ((*(byte *)(uVar32 + 0x2e) >> 3 & 1) == 0) {
    uVar8 = (ulong)(uint)*(float *)(lVar14 + 0xc);
    if ((*(float *)(lVar14 + 0xc) <= fVar46) && (uVar8 = uVar39, *(float *)(lVar14 + 0x10) < fVar46)
       ) {
      uVar8 = (ulong)(uint)*(float *)(lVar14 + 0x10);
    }
    (**(code **)(*plVar26 + 0x80))(uVar8,plVar26,&uStack_a0,&uStack_c0);
    fVar43 = (float)(**(code **)(*plVar26 + 0x1d0))(plVar26);
    fVar43 = fVar42 * fVar43;
    uStack_c0 = (long *)CONCAT44(fVar43 * uStack_c0._4_4_,(float)uStack_c0 * fVar43);
    uStack_b8 = CONCAT44(uStack_b8._4_4_,fVar43 * (float)uStack_b8);
  }
  else {
    lVar14 = *plVar26;
code_r0x0209a180:
    (**(code **)(lVar14 + 0x148))(plVar26,&uStack_a0,1);
code_r0x0209a188:
    uStack_b8 = uStack_108;
    uStack_c0 = plVar30;
  }
code_r0x0209a190:
  plVar29 = &uStack_a0;
  pfVar11 = (float *)&uStack_c0;
  pfVar12 = (float *)&uStack_c0;
  pcVar17 = *(code **)(*plStack_f0 + 0x48);
  goto code_r0x0209a2fc;
code_r0x02099d1c:
  uVar8 = (ulong)(uint)*(float *)(lVar19 + 0xc);
  if ((*(float *)(lVar19 + 0xc) <= fVar46) && (uVar8 = uVar39, *(float *)(lVar19 + 0x10) < fVar46))
  {
    uVar8 = (ulong)(uint)*(float *)(lVar19 + 0x10);
  }
  (**(code **)(*plVar29 + 0x80))(uVar8,plVar29,&uStack_84,&fStack_88);
code_r0x02099d54:
  fVar43 = (float)(**(code **)(*plVar29 + 0x1d0))(plVar29);
  fStack_88 = fStack_88 * fVar42 * fVar43;
code_r0x02099d74:
  plVar29 = (long *)&uStack_84;
code_r0x02099d7c:
  pcVar17 = *(code **)(*plStack_f0 + 0x48);
  pfVar11 = &fStack_88;
  pfVar12 = &fStack_88;
code_r0x0209a2fc:
  (*pcVar17)(plStack_f0,0,plVar29,pfVar11,pfVar12);
  plVar26 = plStack_e0;
  pbVar27 = pbStack_f8;
  plVar29 = plStack_100;
code_r0x0209abdc:
  uVar40 = uVar40 + 1;
  if (uVar40 == uVar38) goto code_r0x0209ac00;
  goto code_r0x0209abc4;
}

// ==== Aska::AafHandler::IsChunkReady(float) const
// vaddr 0x1f9b274 | ghidra 0x209b274 | size 152 | symbol _ZNK4Aska10AafHandler12IsChunkReadyEf | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK4Aska10AafHandler12IsChunkReadyEf(float param_1,long param_2)

{
  ushort uVar1;
  long lVar2;
  uint uVar3;
  float fVar4;
  
  if (*(long *)(param_2 + 0x118) == 0) {
    return true;
  }
  lVar2 = *(long *)(param_2 + 0x28);
  if (lVar2 == 0) {
    return false;
  }
  uVar1 = *(ushort *)(lVar2 + 0xe);
  if (uVar1 == 0) {
    return false;
  }
  fVar4 = param_1 / *(float *)(lVar2 + 0x2c);
  if (0.0 <= fVar4) {
    uVar3 = (uint)fVar4;
    if ((uVar1 == uVar3 || (int)(uint)uVar1 < (int)uVar3) || (*(float *)(lVar2 + 0x10) < param_1)) {
      uVar3 = uVar1 - 1;
    }
  }
  else {
    uVar3 = 0;
  }
  if (*(long *)(param_2 + 0x10) + (ulong)*(uint *)(lVar2 + 0x28) + (long)(int)uVar3 * 0xc != 0) {
    return *(long *)(*(long *)(param_2 + 0x118) + (long)(int)uVar3 * 8) != 0;
  }
  return false;
}

// ==== Aska::AafHandler::SearchTarget(char const*, Aska::AsfHandler*)
// vaddr 0x1f9b30c | ghidra 0x209b30c | size 80 | symbol _ZN4Aska10AafHandler12SearchTargetEPKcPNS_10AsfHandlerE | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska10AafHandler12SearchTargetEPKcPNS_10AsfHandlerE
               (undefined8 param_1,undefined8 param_2,undefined8 param_3)

{
  long lVar1;
  ulong uVar2;
  long lStack_28;
  undefined1 auStack_14 [4];
  
  lVar1 = Aska::AsfHandler::QuickSearchByNameEx(char const*) const(param_3);
  if ((lVar1 == 0) &&
     (uVar2 = Aska::AsfHandler::GetModifierAnimationId(char const*, Aska::IAnimatable**, int*) const(param_3,param_2,&lStack_28,auStack_14), lVar1 = lStack_28,
     (uVar2 & 1) == 0)) {
    lVar1 = 0;
  }
  return lVar1;
}

// ==== Aska::AafHandler::LocalGetControllerInfoByDetail(Aska::IAnimatable*, Aska::EnumAafDetailAttribute)
// vaddr 0x1f9b35c | ghidra 0x209b35c | size 212 | symbol _ZN4Aska10AafHandler30LocalGetControllerInfoByDetailEPNS_11IAnimatableENS_22EnumAafDetailAttributeE | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZN4Aska10AafHandler30LocalGetControllerInfoByDetailEPNS_11IAnimatableENS_22EnumAafDetailAttributeE
                (long param_1,long param_2,char param_3)

{
  uint uVar1;
  ushort uVar2;
  ulong uVar3;
  ulong uVar4;
  ulong uVar5;
  uint uVar6;
  ulong uVar7;
  
  uVar2 = *(ushort *)(param_1 + 0xf4);
  if (uVar2 != 0) {
    uVar1 = *(uint *)(param_1 + 0x38);
    uVar4 = *(ulong *)(param_1 + 0x80);
    uVar5 = uVar4 + (ulong)uVar1 * 0x30;
    if (param_2 == 0) {
      uVar6 = 0;
      do {
        uVar7 = uVar4;
        if (uVar1 != 0) {
          do {
            if ((((uVar6 == *(ushort *)(uVar7 + 0x2c)) && (*(long *)(uVar7 + 8) != 0)) &&
                (*(long *)(uVar7 + 0x18) != 0)) &&
               (*(char *)(*(long *)(uVar7 + 0x18) + 6) == param_3)) {
              return uVar7;
            }
            uVar7 = uVar7 + 0x30;
          } while (uVar7 < uVar5);
        }
        uVar6 = uVar6 + 1;
      } while ((int)uVar6 < (int)(uint)uVar2);
    }
    else {
      uVar7 = 0;
      do {
        if ((*(long *)(*(long *)(param_1 + 0x78) + uVar7 * 0x10 + 8) == param_2) &&
           (uVar3 = uVar4, uVar1 != 0)) {
          do {
            if (((uVar7 == *(ushort *)(uVar3 + 0x2c)) &&
                ((*(long *)(uVar3 + 8) != 0 && (*(long *)(uVar3 + 0x18) != 0)))) &&
               (*(char *)(*(long *)(uVar3 + 0x18) + 6) == param_3)) {
              return uVar3;
            }
            uVar3 = uVar3 + 0x30;
          } while (uVar3 < uVar5);
        }
        uVar7 = uVar7 + 1;
      } while ((long)uVar7 < (long)(ulong)uVar2);
    }
  }
  return 0;
}

// ==== Aska::AafHandler::LocalGetControllerInfoByIndexAndDetail(Aska::IAnimatable*, unsigned long, Aska::EnumAafDetailAttribute)
// vaddr 0x1f9b430 | ghidra 0x209b430 | size 236 | symbol _ZN4Aska10AafHandler38LocalGetControllerInfoByIndexAndDetailEPNS_11IAnimatableEmNS_22EnumAafDetailAttributeE | lib libSOA-3.7.0.so | 2026-10-04
long * _ZN4Aska10AafHandler38LocalGetControllerInfoByIndexAndDetailEPNS_11IAnimatableEmNS_22EnumAafDetailAttributeE
                 (long param_1,long param_2,long param_3,char param_4)

{
  uint uVar1;
  ushort uVar2;
  long *plVar3;
  long *plVar4;
  uint uVar5;
  ulong uVar6;
  
  uVar2 = *(ushort *)(param_1 + 0xf4);
  if (uVar2 != 0) {
    uVar1 = *(uint *)(param_1 + 0x38);
    plVar4 = *(long **)(param_1 + 0x80);
    if (param_2 == 0) {
      uVar5 = 0;
      do {
        plVar3 = plVar4;
        if (uVar1 != 0) {
          do {
            if ((((uVar5 == *(ushort *)((long)plVar3 + 0x2c)) && (plVar3[1] != 0)) &&
                (*plVar3 == param_3)) && ((plVar3[3] != 0 && (*(char *)(plVar3[3] + 6) == param_4)))
               ) {
              return plVar3;
            }
            plVar3 = plVar3 + 6;
          } while (plVar3 < plVar4 + (ulong)uVar1 * 6);
        }
        uVar5 = uVar5 + 1;
      } while ((int)uVar5 < (int)(uint)uVar2);
    }
    else {
      uVar6 = 0;
      do {
        if ((*(long *)(*(long *)(param_1 + 0x78) + uVar6 * 0x10 + 8) == param_2) &&
           (plVar3 = plVar4, uVar1 != 0)) {
          do {
            if (((uVar6 == *(ushort *)((long)plVar3 + 0x2c)) &&
                (((plVar3[1] != 0 && (*plVar3 == param_3)) && (plVar3[3] != 0)))) &&
               (*(char *)(plVar3[3] + 6) == param_4)) {
              return plVar3;
            }
            plVar3 = plVar3 + 6;
          } while (plVar3 < plVar4 + (ulong)uVar1 * 6);
        }
        uVar6 = uVar6 + 1;
      } while ((long)uVar6 < (long)(ulong)uVar2);
    }
  }
  return (long *)0x0;
}

// ==== Aska::AafHandler::LocalGetControllerInfoByIndex(Aska::IAnimatable*, unsigned long)
// vaddr 0x1f9b51c | ghidra 0x209b51c | size 184 | symbol _ZN4Aska10AafHandler29LocalGetControllerInfoByIndexEPNS_11IAnimatableEm | lib libSOA-3.7.0.so | 2026-10-04
long * _ZN4Aska10AafHandler29LocalGetControllerInfoByIndexEPNS_11IAnimatableEm
                 (long param_1,long param_2,long param_3)

{
  uint uVar1;
  ushort uVar2;
  long *plVar3;
  long *plVar4;
  uint uVar5;
  ulong uVar6;
  
  uVar2 = *(ushort *)(param_1 + 0xf4);
  if (uVar2 != 0) {
    uVar1 = *(uint *)(param_1 + 0x38);
    plVar4 = *(long **)(param_1 + 0x80);
    if (param_2 == 0) {
      uVar5 = 0;
      do {
        plVar3 = plVar4;
        if (uVar1 != 0) {
          do {
            if ((uVar5 == *(ushort *)((long)plVar3 + 0x2c)) && (*plVar3 == param_3)) {
              return plVar3;
            }
            plVar3 = plVar3 + 6;
          } while (plVar3 < plVar4 + (ulong)uVar1 * 6);
        }
        uVar5 = uVar5 + 1;
        if ((int)(uint)uVar2 <= (int)uVar5) {
          return (long *)0x0;
        }
      } while( true );
    }
    uVar6 = 0;
    do {
      if ((*(long *)(*(long *)(param_1 + 0x78) + uVar6 * 0x10 + 8) == param_2) &&
         (plVar3 = plVar4, uVar1 != 0)) {
        do {
          if ((uVar6 == *(ushort *)((long)plVar3 + 0x2c)) && (*plVar3 == param_3)) {
            return plVar3;
          }
          plVar3 = plVar3 + 6;
        } while (plVar3 < plVar4 + (ulong)uVar1 * 6);
      }
      uVar6 = uVar6 + 1;
    } while ((long)uVar6 < (long)(ulong)uVar2);
  }
  return (long *)0x0;
}

// ==== Aska::AafHandler::Length() const
// vaddr 0x1f9b5d4 | ghidra 0x209b5d4 | size 24 | symbol _ZNK4Aska10AafHandler6LengthEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK4Aska10AafHandler6LengthEv(long param_1)

{
  if (*(long *)(param_1 + 0x28) != 0) {
    return *(undefined4 *)(*(long *)(param_1 + 0x28) + 0x10);
  }
  return 0;
}

// ==== Aska::AafHandler::DisappearHandler(bool)
// vaddr 0x1f9b5ec | ghidra 0x209b5ec | size 296 | symbol _ZN4Aska10AafHandler16DisappearHandlerEb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10AafHandler16DisappearHandlerEb(long param_1,uint param_2)

{
  uint uVar1;
  bool bVar2;
  byte *pbVar3;
  ulong uVar4;
  long lVar5;
  long lVar6;
  ulong uVar7;
  ulong uVar8;
  
  bVar2 = (*(uint *)(param_1 + 0xc) & 0x82) == 0x82;
  if ((param_2 & 1) == 0) {
    if (bVar2) {
      uVar4 = (ulong)*(ushort *)(param_1 + 0xf4);
      if (uVar4 != 0) {
        lVar5 = 8;
        do {
          uVar4 = uVar4 - 1;
          *(undefined8 *)(*(long *)(param_1 + 0x78) + lVar5) = 0;
          lVar5 = lVar5 + 0x10;
        } while (uVar4 != 0);
      }
      uVar1 = *(uint *)(param_1 + 0x38);
      if (uVar1 != 0) {
        lVar6 = *(long *)(param_1 + 0x80);
        uVar4 = ((ulong)uVar1 * 0x30 - 0x30) / 0x30 + 1;
        lVar5 = lVar6;
        if ((1 < uVar4) && (uVar7 = uVar4 & 0xffffffffffffffe, uVar7 != 0)) {
          pbVar3 = (byte *)(lVar6 + 0x5e);
          uVar8 = uVar7;
          do {
            uVar8 = uVar8 - 2;
            pbVar3[-0x30] = pbVar3[-0x30] | 2;
            *pbVar3 = *pbVar3 | 2;
            pbVar3 = pbVar3 + 0x60;
          } while (uVar8 != 0);
          lVar5 = lVar6 + uVar7 * 0x30;
          if (uVar4 == uVar7) {
            return;
          }
        }
        do {
          *(byte *)(lVar5 + 0x2e) = *(byte *)(lVar5 + 0x2e) | 2;
          lVar5 = lVar5 + 0x30;
        } while (lVar6 + (ulong)uVar1 * 0x30 != lVar5);
      }
    }
  }
  else if ((bVar2) && (*(uint *)(param_1 + 0x38) != 0)) {
    pbVar3 = (byte *)(*(long *)(param_1 + 0x80) + 0x2e);
    lVar5 = (ulong)*(uint *)(param_1 + 0x38) * 0x30;
    do {
      if ((*(char **)(pbVar3 + -0x1e) != (char *)0x0) && (**(char **)(pbVar3 + -0x1e) == '\x03')) {
        *pbVar3 = *pbVar3 | 2;
      }
      lVar5 = lVar5 + -0x30;
      pbVar3 = pbVar3 + 0x30;
    } while (lVar5 != 0);
  }
  return;
}

// ==== Aska::AafHandler::CalcAndSetDifferenceOfValueMain(Aska::AafControllerInfo*)
// vaddr 0x1f9b714 | ghidra 0x209b714 | size 268 | symbol _ZN4Aska10AafHandler31CalcAndSetDifferenceOfValueMainEPNS_17AafControllerInfoE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10AafHandler31CalcAndSetDifferenceOfValueMainEPNS_17AafControllerInfoE
               (long param_1,long param_2)

{
  undefined4 uVar1;
  long lVar2;
  long *plVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined1 auStack_40 [16];
  
  lVar2 = *(long *)(param_2 + 0x18);
  if ((lVar2 != 0) && (plVar3 = *(long **)(param_2 + 8), plVar3 != (long *)0x0)) {
    uVar5 = *(undefined4 *)(lVar2 + 0xc);
    uVar4 = *(undefined4 *)(lVar2 + 0x10);
    lVar2 = *(long *)(param_1 + 0x88) + ((ulong)(param_2 - *(long *)(param_1 + 0x88)) / 0x30) * 0x30
    ;
    uVar1 = (**(code **)(**(long **)(lVar2 + 8) + 0x28))();
    switch(uVar1) {
    case 0:
    case 1:
    case 2:
      Aska::AafHandler::CalcDifferenceOfValue(float*, Aska::AafControllerInfo*, float, float)(uVar5,uVar4,param_1,auStack_40,lVar2);
      break;
    case 3:
    case 4:
      Aska::AafHandler::CalcDifferenceOfValue(int*, Aska::AafControllerInfo*, float, float)(uVar5,uVar4,param_1,auStack_40,lVar2);
      break;
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
      Aska::AafHandler::CalcDifferenceOfValue(Aska::Vector*, Aska::AafControllerInfo*, float, float)(uVar5,uVar4,param_1,auStack_40,lVar2);
      break;
    case 0xb:
    case 0xc:
    case 0xd:
      Aska::AafHandler::CalcDifferenceOfValue(Aska::Quaternion*, Aska::AafControllerInfo*, float, float)(uVar5,uVar4,param_1,auStack_40,lVar2);
    }
    (**(code **)(*plVar3 + 0x118))(plVar3,auStack_40);
  }
  return;
}

// ==== Aska::AafHandler::CalcRuntimeMemorySize(void const*)
// vaddr 0x1f9b820 | ghidra 0x209b820 | size 252 | symbol _ZN4Aska10AafHandler21CalcRuntimeMemorySizeEPKv | lib libSOA-3.7.0.so | 2026-10-04
int _ZN4Aska10AafHandler21CalcRuntimeMemorySizeEPKv(int *param_1)

{
  ushort uVar1;
  uint uVar2;
  int iVar3;
  ulong uVar4;
  int *unaff_x20;
  int iVar5;
  undefined *puStack_30;
  long lStack_28;
  
  if (param_1 == (int *)0x0) {
    iVar5 = 0;
    goto code_r0x0209b8fc;
  }
  if (*param_1 != 0x41414620) {
    iVar5 = -1;
    goto code_r0x0209b8fc;
  }
  unaff_x20 = param_1 + 4;
  puStack_30 = PTR__ZTVN4Aska10ArfHandlerE_02cbeb70 + 0x10;
  lStack_28 = 0;
  uVar4 = Aska::ArfHandler::Attach(Aska::AFF::AskaResource const*)(&puStack_30,unaff_x20);
  if ((uVar4 & 1) == 0) {
code_r0x0209b884:
    if ((short)*unaff_x20 == 0x2e) {
      uVar1 = *(ushort *)(unaff_x20 + 2);
      uVar2 = uVar1 + 0x1f >> 5;
      iVar5 = ((uint)uVar1 + (uint)*(ushort *)((long)unaff_x20 + 6) +
              (uint)*(ushort *)((long)unaff_x20 + 10)) * 0x30 +
              (uint)*(ushort *)(unaff_x20 + 1) * 0x10 + (uint)*(ushort *)((long)unaff_x20 + 0xe) * 8
      ;
      if (uVar2 != 0) {
        iVar5 = (uint)uVar1 * 0xc + uVar2 * 8 + iVar5;
      }
    }
    else {
      iVar5 = -2;
    }
  }
  else {
    if ((lStack_28 == 0) || (*(uint *)(lStack_28 + 0xc) == 0)) {
      unaff_x20 = (int *)0x0;
    }
    else {
      unaff_x20 = (int *)(lStack_28 + (ulong)*(uint *)(lStack_28 + 0xc));
      if (unaff_x20 != (int *)0x0) goto code_r0x0209b884;
    }
    iVar5 = -1;
  }
code_r0x0209b8fc:
  iVar3 = Aska::AafHandler::CalcRuntimeMemorySize1(Aska::AFF::AskaFile const*, Aska::AafHeader const*)(param_1,unaff_x20);
  return iVar3 + iVar5;
}

// ==== Aska::AafHandler::operator new(unsigned long, unsigned long, bool)
// vaddr 0x1f9b91c | ghidra 0x209b91c | size 48 | symbol _ZN4Aska10AafHandlernwEmmb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10AafHandlernwEmmb(undefined8 param_1,undefined8 param_2)

{
  if (*(long *)PTR__ZN4Aska10AafHandler16m_pMemoryManagerE_02cb6d40 != 0) {
    (*(code *)PTR__ZN4Aska13MemoryManager13AlignedMallocEml_02cae360)
              (*(long *)PTR__ZN4Aska10AafHandler16m_pMemoryManagerE_02cb6d40,param_1,
               (long)(int)param_2);
    return;
  }
  (*(code *)PTR__Znwmmb_02c9f858)(param_1,param_2,1);
  return;
}

// ==== Aska::AafHandler::operator new[](unsigned long, unsigned long, bool)
// vaddr 0x1f9b94c | ghidra 0x209b94c | size 48 | symbol _ZN4Aska10AafHandlernaEmmb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10AafHandlernaEmmb(undefined8 param_1,undefined8 param_2)

{
  if (*(long *)PTR__ZN4Aska10AafHandler16m_pMemoryManagerE_02cb6d40 != 0) {
    (*(code *)PTR__ZN4Aska13MemoryManager13AlignedMallocEml_02cae360)
              (*(long *)PTR__ZN4Aska10AafHandler16m_pMemoryManagerE_02cb6d40,param_1,
               (long)(int)param_2);
    return;
  }
  (*(code *)PTR__Znammb_02c9d8d8)(param_1,param_2,1);
  return;
}

// ==== Aska::AafHandler::operator new[](unsigned long, std::nothrow_t const&)
// vaddr 0x1f9b97c | ghidra 0x209b97c | size 40 | symbol _ZN4Aska10AafHandlernaEmRKSt9nothrow_t | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10AafHandlernaEmRKSt9nothrow_t(undefined8 param_1)

{
  if (*(long *)PTR__ZN4Aska10AafHandler16m_pMemoryManagerE_02cb6d40 != 0) {
    (*(code *)PTR__ZN4Aska13MemoryManager6MallocEm_02ca1310)
              (*(long *)PTR__ZN4Aska10AafHandler16m_pMemoryManagerE_02cb6d40,param_1);
    return;
  }
  (*(code *)PTR__Znam_02cae9a8)(param_1);
  return;
}

// ==== Aska::AafHandler::GetFigureRate(unsigned char, unsigned char) const
// vaddr 0x1f9b9a4 | ghidra 0x209b9a4 | size 96 | symbol _ZNK4Aska10AafHandler13GetFigureRateEhh | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 _ZNK4Aska10AafHandler13GetFigureRateEhh(undefined8 param_1,byte param_2,char param_3)

{
  if (param_3 != '\x01') {
    if (param_2 < 8) {
      return *(undefined4 *)(&UNK_029739d0 + (long)(char)param_2 * 4);
    }
    return _UNK_027e5198;
  }
  if (param_2 < 8) {
    return *(undefined4 *)(&UNK_029739b0 + (long)(char)param_2 * 4);
  }
  return _UNK_027e6ae0;
}

// ==== Aska::AafHandler::LocalGetControllerInfoAndIndex(int*, Aska::IAnimatable*, Aska::EnumAafDetailAttribute)
// vaddr 0x1f9ba04 | ghidra 0x209ba04 | size 240 | symbol _ZN4Aska10AafHandler30LocalGetControllerInfoAndIndexEPiPNS_11IAnimatableENS_22EnumAafDetailAttributeE | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZN4Aska10AafHandler30LocalGetControllerInfoAndIndexEPiPNS_11IAnimatableENS_22EnumAafDetailAttributeE
                (long param_1,int *param_2,long param_3,char param_4)

{
  uint uVar1;
  ushort uVar2;
  ulong uVar3;
  ulong uVar4;
  ulong uVar5;
  uint uVar6;
  ulong uVar7;
  
  uVar2 = *(ushort *)(param_1 + 0xf4);
  if (uVar2 != 0) {
    uVar1 = *(uint *)(param_1 + 0x38);
    uVar4 = *(ulong *)(param_1 + 0x80);
    uVar5 = uVar4 + (ulong)uVar1 * 0x30;
    if (param_3 == 0) {
      uVar6 = 0;
      do {
        uVar3 = uVar4;
        if (uVar1 != 0) {
          do {
            if ((((uVar6 == *(ushort *)(uVar3 + 0x2c)) && (*(long *)(uVar3 + 8) != 0)) &&
                (*(long *)(uVar3 + 0x18) != 0)) &&
               (*(char *)(*(long *)(uVar3 + 0x18) + 6) == param_4)) goto code_r0x0209bad8;
            uVar3 = uVar3 + 0x30;
          } while (uVar3 < uVar5);
        }
        uVar6 = uVar6 + 1;
      } while ((int)uVar6 < (int)(uint)uVar2);
    }
    else {
      uVar7 = 0;
      do {
        if ((*(long *)(*(long *)(param_1 + 0x78) + uVar7 * 0x10 + 8) == param_3) &&
           (uVar3 = uVar4, uVar1 != 0)) {
          do {
            if (((uVar7 == *(ushort *)(uVar3 + 0x2c)) &&
                ((*(long *)(uVar3 + 8) != 0 && (*(long *)(uVar3 + 0x18) != 0)))) &&
               (*(char *)(*(long *)(uVar3 + 0x18) + 6) == param_4)) {
code_r0x0209bad8:
              *param_2 = (int)(uVar3 - uVar4 >> 4) * -0x55555555;
              return uVar3;
            }
            uVar3 = uVar3 + 0x30;
          } while (uVar3 < uVar5);
        }
        uVar7 = uVar7 + 1;
      } while ((long)uVar7 < (long)(ulong)uVar2);
    }
  }
  return 0;
}

// ==== Aska::AafHandler::LocalGetControllerInfoByType(Aska::IAnimatable*, Aska::EnumAafControllerType, int)
// vaddr 0x1f9baf4 | ghidra 0x209baf4 | size 212 | symbol _ZN4Aska10AafHandler28LocalGetControllerInfoByTypeEPNS_11IAnimatableENS_21EnumAafControllerTypeEi | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZN4Aska10AafHandler28LocalGetControllerInfoByTypeEPNS_11IAnimatableENS_21EnumAafControllerTypeEi
                (long param_1,long param_2,char param_3,int param_4)

{
  bool bVar1;
  uint uVar2;
  ushort uVar3;
  ulong uVar4;
  int iVar5;
  ulong uVar6;
  ulong uVar7;
  uint uVar8;
  ulong uVar9;
  
  uVar3 = *(ushort *)(param_1 + 0xf4);
  if (uVar3 != 0) {
    uVar2 = *(uint *)(param_1 + 0x38);
    uVar6 = *(ulong *)(param_1 + 0x80);
    uVar7 = uVar6 + (ulong)uVar2 * 0x30;
    if (param_2 == 0) {
      uVar8 = 0;
      do {
        uVar9 = uVar6;
        if (uVar2 != 0) {
          do {
            if ((((uVar8 == *(ushort *)(uVar9 + 0x2c)) && (*(char **)(uVar9 + 0x10) != (char *)0x0))
                && (**(char **)(uVar9 + 0x10) == param_3)) &&
               (bVar1 = param_4 < 1, param_4 = param_4 + -1, bVar1)) {
              return uVar9;
            }
            uVar9 = uVar9 + 0x30;
          } while (uVar9 < uVar7);
        }
        uVar8 = uVar8 + 1;
      } while ((int)uVar8 < (int)(uint)uVar3);
    }
    else {
      uVar9 = 0;
      do {
        if ((*(long *)(*(long *)(param_1 + 0x78) + uVar9 * 0x10 + 8) == param_2) &&
           (uVar4 = uVar6, iVar5 = param_4, uVar2 != 0)) {
          do {
            param_4 = iVar5;
            if (((uVar9 == *(ushort *)(uVar4 + 0x2c)) &&
                ((*(char **)(uVar4 + 0x10) != (char *)0x0 && (**(char **)(uVar4 + 0x10) == param_3))
                )) && (param_4 = iVar5 + -1, iVar5 < 1)) {
              return uVar4;
            }
            uVar4 = uVar4 + 0x30;
            iVar5 = param_4;
          } while (uVar4 < uVar7);
        }
        uVar9 = uVar9 + 1;
      } while ((long)uVar9 < (long)(ulong)uVar3);
    }
  }
  return 0;
}

// ==== Aska::AafHandler::LocalGetAllControllerInfoByType(Aska::AafControllerInfo**, int, Aska::IAnimatable*, Aska::EnumAafControllerType, int*)
// vaddr 0x1f9bbc8 | ghidra 0x209bbc8 | size 464 | symbol _ZN4Aska10AafHandler31LocalGetAllControllerInfoByTypeEPPNS_17AafControllerInfoEiPNS_11IAnimatableENS_21EnumAafControllerTypeEPi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10AafHandler31LocalGetAllControllerInfoByTypeEPPNS_17AafControllerInfoEiPNS_11IAnimatableENS_21EnumAafControllerTypeEPi
               (long param_1,long param_2,int param_3,long param_4,char param_5,int *param_6)

{
  ushort uVar1;
  ulong uVar2;
  ulong uVar3;
  uint uVar4;
  ulong uVar5;
  int iVar6;
  int iVar7;
  
  uVar1 = *(ushort *)(param_1 + 0xf4);
  if (uVar1 == 0) {
    iVar6 = 0;
  }
  else {
    uVar3 = *(ulong *)(param_1 + 0x80);
    uVar2 = uVar3 + (ulong)*(uint *)(param_1 + 0x38) * 0x30;
    if (param_4 == 0) {
      iVar7 = 0;
      uVar4 = 0;
      while( true ) {
        if (uVar3 < uVar2) {
          iVar6 = iVar7;
          if (param_2 == 0) {
            do {
              if (((uVar4 == *(ushort *)(uVar3 + 0x2c)) && (*(char **)(uVar3 + 0x10) != (char *)0x0)
                  ) && (**(char **)(uVar3 + 0x10) == param_5)) {
                iVar7 = iVar7 + 1;
              }
              uVar3 = uVar3 + 0x30;
            } while (uVar3 < uVar2);
          }
          else {
            do {
              iVar7 = iVar6;
              if (((uVar4 == *(ushort *)(uVar3 + 0x2c)) && (*(char **)(uVar3 + 0x10) != (char *)0x0)
                  ) && (**(char **)(uVar3 + 0x10) == param_5)) {
                if (*(long *)(uVar3 + 8) == 0) {
                  iVar7 = iVar6 + 1;
                }
                else {
                  *(ulong *)(param_2 + (long)iVar6 * 8) = uVar3;
                  iVar7 = iVar6 + 1;
                  if (param_3 <= iVar6 + 1) goto joined_r0x0209bcc0;
                }
              }
              uVar3 = uVar3 + 0x30;
              iVar6 = iVar7;
            } while (uVar3 < uVar2);
          }
        }
        uVar4 = uVar4 + 1;
        iVar6 = iVar7;
        if ((int)(uint)uVar1 <= (int)uVar4) break;
        uVar3 = *(ulong *)(param_1 + 0x80);
      }
    }
    else {
      uVar3 = 0;
      iVar6 = 0;
      do {
        if ((*(long *)(*(long *)(param_1 + 0x78) + uVar3 * 0x10 + 8) == param_4) &&
           (uVar5 = *(ulong *)(param_1 + 0x80), uVar5 < uVar2)) {
          if (param_2 == 0) {
            do {
              if (((uVar3 == *(ushort *)(uVar5 + 0x2c)) && (*(char **)(uVar5 + 0x10) != (char *)0x0)
                  ) && (**(char **)(uVar5 + 0x10) == param_5)) {
                iVar6 = iVar6 + 1;
              }
              uVar5 = uVar5 + 0x30;
            } while (uVar5 < uVar2);
          }
          else {
            do {
              iVar7 = iVar6;
              if (((uVar3 == *(ushort *)(uVar5 + 0x2c)) && (*(char **)(uVar5 + 0x10) != (char *)0x0)
                  ) && (**(char **)(uVar5 + 0x10) == param_5)) {
                if (*(long *)(uVar5 + 8) == 0) {
                  iVar7 = iVar6 + 1;
                }
                else {
                  *(ulong *)(param_2 + (long)iVar6 * 8) = uVar5;
                  iVar7 = iVar6 + 1;
                  if (param_3 <= iVar6 + 1) goto joined_r0x0209bcc0;
                }
              }
              iVar6 = iVar7;
              uVar5 = uVar5 + 0x30;
            } while (uVar5 < uVar2);
          }
        }
        uVar3 = uVar3 + 1;
      } while ((long)uVar3 < (long)(ulong)uVar1);
    }
  }
joined_r0x0209bcc0:
  if (param_6 != (int *)0x0) {
    *param_6 = iVar6;
  }
  return;
}

// ==== Aska::AafHandler::GetControllerInfoByDetail(Aska::IAnimatable*, Aska::EnumAafDetailAttribute)
// vaddr 0x1f9bd98 | ghidra 0x209bd98 | size 220 | symbol _ZN4Aska10AafHandler25GetControllerInfoByDetailEPNS_11IAnimatableENS_22EnumAafDetailAttributeE | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZN4Aska10AafHandler25GetControllerInfoByDetailEPNS_11IAnimatableENS_22EnumAafDetailAttributeE
                (long param_1,long param_2,char param_3)

{
  ushort uVar1;
  ulong uVar2;
  ulong uVar3;
  ulong uVar4;
  uint uVar5;
  ulong uVar6;
  
  uVar1 = *(ushort *)(param_1 + 0xf4);
  if (uVar1 != 0) {
    uVar5 = *(uint *)(param_1 + 0x38);
    uVar3 = *(ulong *)(param_1 + 0x80);
    uVar4 = uVar3 + (ulong)uVar5 * 0x30;
    if (param_2 == 0) {
      if (uVar5 != 0) {
        uVar5 = 0;
        uVar6 = uVar3;
        while ((((uVar5 != *(ushort *)(uVar6 + 0x2c) || (*(long *)(uVar6 + 8) == 0)) ||
                (*(long *)(uVar6 + 0x18) == 0)) ||
               (*(char *)(*(long *)(uVar6 + 0x18) + 6) != param_3))) {
          uVar6 = uVar6 + 0x30;
          if ((uVar4 <= uVar6) && (uVar5 = uVar5 + 1, uVar6 = uVar3, (int)(uint)uVar1 <= (int)uVar5)
             ) {
            return 0;
          }
        }
        return uVar6;
      }
    }
    else if (uVar5 != 0) {
      uVar6 = 0;
      do {
        uVar2 = uVar3;
        if (*(long *)(*(long *)(param_1 + 0x78) + uVar6 * 0x10 + 8) == param_2) {
          do {
            if (((uVar6 == *(ushort *)(uVar2 + 0x2c)) && (*(long *)(uVar2 + 8) != 0)) &&
               ((*(long *)(uVar2 + 0x18) != 0 && (*(char *)(*(long *)(uVar2 + 0x18) + 6) == param_3)
                ))) {
              return uVar2;
            }
            uVar2 = uVar2 + 0x30;
          } while (uVar2 < uVar4);
        }
        uVar6 = uVar6 + 1;
      } while ((long)uVar6 < (long)(ulong)uVar1);
    }
  }
  return 0;
}

// ==== Aska::AafHandler::GetControllerInfoByIndex(Aska::IAnimatable*, unsigned long)
// vaddr 0x1f9be74 | ghidra 0x209be74 | size 188 | symbol _ZN4Aska10AafHandler24GetControllerInfoByIndexEPNS_11IAnimatableEm | lib libSOA-3.7.0.so | 2026-10-04
long * _ZN4Aska10AafHandler24GetControllerInfoByIndexEPNS_11IAnimatableEm
                 (long param_1,long param_2,long param_3)

{
  uint uVar1;
  ushort uVar2;
  long *plVar3;
  long *plVar4;
  uint uVar5;
  ulong uVar6;
  
  uVar2 = *(ushort *)(param_1 + 0xf4);
  if (uVar2 != 0) {
    uVar1 = *(uint *)(param_1 + 0x38);
    plVar4 = *(long **)(param_1 + 0x80);
    if (param_2 == 0) {
      if (uVar1 != 0) {
        uVar5 = 0;
        plVar3 = plVar4;
        do {
          if ((uVar5 == *(ushort *)((long)plVar3 + 0x2c)) && (*plVar3 == param_3)) {
            return plVar3;
          }
          plVar3 = plVar3 + 6;
        } while ((plVar3 < plVar4 + (ulong)uVar1 * 6) ||
                (uVar5 = uVar5 + 1, plVar3 = plVar4, (int)uVar5 < (int)(uint)uVar2));
        return (long *)0x0;
      }
    }
    else if (uVar1 != 0) {
      uVar6 = 0;
      do {
        plVar3 = plVar4;
        if (*(long *)(*(long *)(param_1 + 0x78) + uVar6 * 0x10 + 8) == param_2) {
          do {
            if ((uVar6 == *(ushort *)((long)plVar3 + 0x2c)) && (*plVar3 == param_3)) {
              return plVar3;
            }
            plVar3 = plVar3 + 6;
          } while (plVar3 < plVar4 + (ulong)uVar1 * 6);
        }
        uVar6 = uVar6 + 1;
      } while ((long)uVar6 < (long)(ulong)uVar2);
    }
  }
  return (long *)0x0;
}

// ==== Aska::AafHandler::GetControllerInfoByIndexAndDetail(Aska::IAnimatable*, unsigned long, Aska::EnumAafDetailAttribute)
// vaddr 0x1f9bf30 | ghidra 0x209bf30 | size 4 | symbol _ZN4Aska10AafHandler33GetControllerInfoByIndexAndDetailEPNS_11IAnimatableEmNS_22EnumAafDetailAttributeE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10AafHandler33GetControllerInfoByIndexAndDetailEPNS_11IAnimatableEmNS_22EnumAafDetailAttributeE
               (void)

{
  (*(code *)
    PTR__ZN4Aska10AafHandler38LocalGetControllerInfoByIndexAndDetailEPNS_11IAnimatableEmNS_22EnumAafDetailAttributeE_02c93050
  )();
  return;
}

// ==== Aska::AafHandler::GetControllerInfoAndIndex(int*, Aska::IAnimatable*, Aska::EnumAafDetailAttribute)
// vaddr 0x1f9bf34 | ghidra 0x209bf34 | size 248 | symbol _ZN4Aska10AafHandler25GetControllerInfoAndIndexEPiPNS_11IAnimatableENS_22EnumAafDetailAttributeE | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZN4Aska10AafHandler25GetControllerInfoAndIndexEPiPNS_11IAnimatableENS_22EnumAafDetailAttributeE
                (long param_1,int *param_2,long param_3,char param_4)

{
  ushort uVar1;
  ulong uVar2;
  ulong uVar3;
  ulong uVar4;
  uint uVar5;
  ulong uVar6;
  
  uVar1 = *(ushort *)(param_1 + 0xf4);
  if (uVar1 != 0) {
    uVar5 = *(uint *)(param_1 + 0x38);
    uVar3 = *(ulong *)(param_1 + 0x80);
    uVar4 = uVar3 + (ulong)uVar5 * 0x30;
    if (param_3 == 0) {
      if (uVar5 != 0) {
        uVar5 = 0;
        uVar2 = uVar3;
        do {
          if ((((uVar5 == *(ushort *)(uVar2 + 0x2c)) && (*(long *)(uVar2 + 8) != 0)) &&
              (*(long *)(uVar2 + 0x18) != 0)) && (*(char *)(*(long *)(uVar2 + 0x18) + 6) == param_4)
             ) {
code_r0x0209c010:
            *param_2 = (int)(uVar2 - uVar3 >> 4) * -0x55555555;
            return uVar2;
          }
          uVar2 = uVar2 + 0x30;
        } while ((uVar2 < uVar4) ||
                (uVar5 = uVar5 + 1, uVar2 = uVar3, (int)uVar5 < (int)(uint)uVar1));
      }
    }
    else if (uVar5 != 0) {
      uVar6 = 0;
      do {
        uVar2 = uVar3;
        if (*(long *)(*(long *)(param_1 + 0x78) + uVar6 * 0x10 + 8) == param_3) {
          do {
            if (((uVar6 == *(ushort *)(uVar2 + 0x2c)) && (*(long *)(uVar2 + 8) != 0)) &&
               ((*(long *)(uVar2 + 0x18) != 0 && (*(char *)(*(long *)(uVar2 + 0x18) + 6) == param_4)
                ))) goto code_r0x0209c010;
            uVar2 = uVar2 + 0x30;
          } while (uVar2 < uVar4);
        }
        uVar6 = uVar6 + 1;
      } while ((long)uVar6 < (long)(ulong)uVar1);
    }
  }
  return 0;
}

// ==== Aska::AafHandler::GetControllerInfoByType(Aska::IAnimatable*, Aska::EnumAafControllerType, int)
// vaddr 0x1f9c02c | ghidra 0x209c02c | size 220 | symbol _ZN4Aska10AafHandler23GetControllerInfoByTypeEPNS_11IAnimatableENS_21EnumAafControllerTypeEi | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZN4Aska10AafHandler23GetControllerInfoByTypeEPNS_11IAnimatableENS_21EnumAafControllerTypeEi
                (long param_1,long param_2,char param_3,int param_4)

{
  bool bVar1;
  ushort uVar2;
  ulong uVar3;
  int iVar4;
  ulong uVar5;
  ulong uVar6;
  uint uVar7;
  ulong uVar8;
  
  uVar2 = *(ushort *)(param_1 + 0xf4);
  if (uVar2 != 0) {
    uVar7 = *(uint *)(param_1 + 0x38);
    uVar5 = *(ulong *)(param_1 + 0x80);
    uVar6 = uVar5 + (ulong)uVar7 * 0x30;
    if (param_2 == 0) {
      if (uVar7 != 0) {
        uVar7 = 0;
        uVar8 = uVar5;
        while ((((uVar7 != *(ushort *)(uVar8 + 0x2c) || (*(char **)(uVar8 + 0x10) == (char *)0x0))
                || (**(char **)(uVar8 + 0x10) != param_3)) ||
               (bVar1 = 0 < param_4, param_4 = param_4 + -1, bVar1))) {
          uVar8 = uVar8 + 0x30;
          if ((uVar6 <= uVar8) && (uVar7 = uVar7 + 1, uVar8 = uVar5, (int)(uint)uVar2 <= (int)uVar7)
             ) {
            return 0;
          }
        }
        return uVar8;
      }
    }
    else if (uVar7 != 0) {
      uVar8 = 0;
      do {
        uVar3 = uVar5;
        iVar4 = param_4;
        if (*(long *)(*(long *)(param_1 + 0x78) + uVar8 * 0x10 + 8) == param_2) {
          do {
            param_4 = iVar4;
            if (((uVar8 == *(ushort *)(uVar3 + 0x2c)) && (*(char **)(uVar3 + 0x10) != (char *)0x0))
               && ((**(char **)(uVar3 + 0x10) == param_3 && (param_4 = iVar4 + -1, iVar4 < 1)))) {
              return uVar3;
            }
            uVar3 = uVar3 + 0x30;
            iVar4 = param_4;
          } while (uVar3 < uVar6);
        }
        uVar8 = uVar8 + 1;
      } while ((long)uVar8 < (long)(ulong)uVar2);
    }
  }
  return 0;
}

// ==== Aska::AafHandler::GetAllControllerInfoByType(Aska::AafControllerInfo**, int, Aska::IAnimatable*, Aska::EnumAafControllerType, int*)
// vaddr 0x1f9c108 | ghidra 0x209c108 | size 4 | symbol _ZN4Aska10AafHandler26GetAllControllerInfoByTypeEPPNS_17AafControllerInfoEiPNS_11IAnimatableENS_21EnumAafControllerTypeEPi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10AafHandler26GetAllControllerInfoByTypeEPPNS_17AafControllerInfoEiPNS_11IAnimatableENS_21EnumAafControllerTypeEPi
               (void)

{
  (*(code *)
    PTR__ZN4Aska10AafHandler31LocalGetAllControllerInfoByTypeEPPNS_17AafControllerInfoEiPNS_11IAnimatableENS_21EnumAafControllerTypeEPi_02cab0c0
  )();
  return;
}

// ==== Aska::AafHandler::GetChunkSize(int, unsigned long*, unsigned long*, unsigned long*, unsigned long*)
// vaddr 0x1f9c1d4 | ghidra 0x209c1d4 | size 140 | symbol _ZN4Aska10AafHandler12GetChunkSizeEiPmS1_S1_S1_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10AafHandler12GetChunkSizeEiPmS1_S1_S1_
               (long param_1,int param_2,ulong *param_3,long *param_4,ulong *param_5,ulong *param_6)

{
  ulong uVar1;
  uint uVar2;
  uint *puVar3;
  
  if (*(short *)(*(long *)(param_1 + 0x28) + 0xe) == 0) {
    if (param_3 != (ulong *)0x0) {
      *param_3 = 0;
    }
    if (param_4 != (long *)0x0) {
      *param_4 = 0;
    }
    if (param_5 != (ulong *)0x0) {
      *param_5 = 0;
    }
    if (param_6 != (ulong *)0x0) {
      *param_6 = 0;
      return;
    }
  }
  else {
    puVar3 = (uint *)(*(long *)(param_1 + 0x20) + (ulong)*(uint *)(*(long *)(param_1 + 0x28) + 0x28)
                     + (long)param_2 * 0xc);
    uVar2 = puVar3[1];
    uVar1 = ((ulong)*puVar3 - *(long *)(param_1 + 0x20)) + (long)puVar3;
    if (param_3 != (ulong *)0x0) {
      *param_3 = uVar1 & 0xfffffffffffffe00;
    }
    if (param_4 != (long *)0x0) {
      *param_4 = uVar1 - (uVar1 & 0xfffffffffffffe00);
    }
    if (param_5 != (ulong *)0x0) {
      *param_5 = uVar2 + uVar1 + 0x1ff & 0xfffffffffffffe00;
    }
    if (param_6 != (ulong *)0x0) {
      *param_6 = (ulong)uVar2;
    }
  }
  return;
}

// ==== Aska::AafHandler::GetChunkSize(Aska::AFF::AskaFile const*, Aska::AafHeader const*, int, unsigned long*, unsigned long*, unsigned long*, unsigned long*)
// vaddr 0x1f9c260 | ghidra 0x209c260 | size 132 | symbol _ZN4Aska10AafHandler12GetChunkSizeEPKNS_3AFF8AskaFileEPKNS_9AafHeaderEiPmS8_S8_S8_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10AafHandler12GetChunkSizeEPKNS_3AFF8AskaFileEPKNS_9AafHeaderEiPmS8_S8_S8_
               (long param_1,long param_2,int param_3,ulong *param_4,long *param_5,ulong *param_6,
               ulong *param_7)

{
  ulong uVar1;
  uint uVar2;
  uint *puVar3;
  
  if (*(short *)(param_2 + 0xe) == 0) {
    if (param_4 != (ulong *)0x0) {
      *param_4 = 0;
    }
    if (param_5 != (long *)0x0) {
      *param_5 = 0;
    }
    if (param_6 != (ulong *)0x0) {
      *param_6 = 0;
    }
    if (param_7 != (ulong *)0x0) {
      *param_7 = 0;
      return;
    }
  }
  else {
    puVar3 = (uint *)((ulong)*(uint *)(param_2 + 0x28) + param_1 + (long)param_3 * 0xc);
    uVar2 = puVar3[1];
    uVar1 = ((ulong)*puVar3 - param_1) + (long)puVar3;
    if (param_4 != (ulong *)0x0) {
      *param_4 = uVar1 & 0xfffffffffffffe00;
    }
    if (param_5 != (long *)0x0) {
      *param_5 = uVar1 - (uVar1 & 0xfffffffffffffe00);
    }
    if (param_6 != (ulong *)0x0) {
      *param_6 = uVar2 + uVar1 + 0x1ff & 0xfffffffffffffe00;
    }
    if (param_7 != (ulong *)0x0) {
      *param_7 = (ulong)uVar2;
    }
  }
  return;
}

// ==== Aska::AafHandler::GetConstantChunkSize(unsigned long*, unsigned long*, unsigned long*, unsigned long*)
// vaddr 0x1f9c2e4 | ghidra 0x209c2e4 | size 76 | symbol _ZN4Aska10AafHandler20GetConstantChunkSizeEPmS1_S1_S1_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10AafHandler20GetConstantChunkSizeEPmS1_S1_S1_
               (long param_1,ulong *param_2,long *param_3,ulong *param_4,ulong *param_5)

{
  uint *puVar1;
  ulong uVar2;
  ulong uVar3;
  
  uVar3 = (ulong)*(uint *)(*(long *)(param_1 + 0x28) + 0x24);
  puVar1 = (uint *)(*(long *)(param_1 + 0x20) + uVar3);
  uVar2 = (ulong)puVar1[1];
  uVar3 = *puVar1 + uVar3;
  if (param_2 != (ulong *)0x0) {
    *param_2 = uVar3 & 0x1fffffe00;
  }
  if (param_3 != (long *)0x0) {
    *param_3 = uVar3 - (uVar3 & 0x1fffffe00);
  }
  if (param_4 != (ulong *)0x0) {
    *param_4 = uVar2 + uVar3 + 0x1ff & 0x3fffffe00;
  }
  if (param_5 != (ulong *)0x0) {
    *param_5 = uVar2;
  }
  return;
}

// ==== Aska::AafHandler::GetConstantChunkSize(Aska::AFF::AskaFile const*, Aska::AafHeader const*, unsigned long*, unsigned long*, unsigned long*, unsigned long*)
// vaddr 0x1f9c330 | ghidra 0x209c330 | size 72 | symbol _ZN4Aska10AafHandler20GetConstantChunkSizeEPKNS_3AFF8AskaFileEPKNS_9AafHeaderEPmS8_S8_S8_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10AafHandler20GetConstantChunkSizeEPKNS_3AFF8AskaFileEPKNS_9AafHeaderEPmS8_S8_S8_
               (long param_1,long param_2,ulong *param_3,long *param_4,ulong *param_5,ulong *param_6
               )

{
  uint *puVar1;
  ulong uVar2;
  ulong uVar3;
  
  puVar1 = (uint *)((ulong)*(uint *)(param_2 + 0x24) + param_1);
  uVar3 = (ulong)puVar1[1];
  uVar2 = (ulong)*(uint *)(param_2 + 0x24) + (ulong)*puVar1;
  if (param_3 != (ulong *)0x0) {
    *param_3 = uVar2 & 0x1fffffe00;
  }
  if (param_4 != (long *)0x0) {
    *param_4 = uVar2 - (uVar2 & 0x1fffffe00);
  }
  if (param_5 != (ulong *)0x0) {
    *param_5 = uVar3 + uVar2 + 0x1ff & 0x3fffffe00;
  }
  if (param_6 != (ulong *)0x0) {
    *param_6 = uVar3;
  }
  return;
}

// ==== Aska::AafHandler::DetachConstantChunkData()
// vaddr 0x1f9c378 | ghidra 0x209c378 | size 8 | symbol _ZN4Aska10AafHandler23DetachConstantChunkDataEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10AafHandler23DetachConstantChunkDataEv(long param_1)

{
  *(undefined8 *)(param_1 + 0x110) = 0;
  return;
}

// ==== Aska::AafHandler::DetachChunkData(int)
// vaddr 0x1f9c380 | ghidra 0x209c380 | size 40 | symbol _ZN4Aska10AafHandler15DetachChunkDataEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10AafHandler15DetachChunkDataEi(long param_1,int param_2)

{
  if ((((*(long *)(param_1 + 0x118) != 0) && (-1 < param_2)) && (*(long *)(param_1 + 0x28) != 0)) &&
     (param_2 < (int)(uint)*(ushort *)(*(long *)(param_1 + 0x28) + 0xe))) {
    *(undefined8 *)(*(long *)(param_1 + 0x118) + (long)param_2 * 8) = 0;
  }
  return;
}

// ==== Aska::AafHandler::IsChunkReadyByIndex(int) const
// vaddr 0x1f9c3a8 | ghidra 0x209c3a8 | size 72 | symbol _ZNK4Aska10AafHandler19IsChunkReadyByIndexEi | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK4Aska10AafHandler19IsChunkReadyByIndexEi(long param_1,int param_2)

{
  bool bVar1;
  
  if (*(long *)(param_1 + 0x118) == 0) {
    return false;
  }
  bVar1 = false;
  if ((-1 < param_2) && (*(long *)(param_1 + 0x28) != 0)) {
    if ((int)(uint)*(ushort *)(*(long *)(param_1 + 0x28) + 0xe) <= param_2) {
      return false;
    }
    bVar1 = *(long *)(*(long *)(param_1 + 0x118) + (long)param_2 * 8) != 0;
  }
  return bVar1;
}

// ==== Aska::AafHandler::~AafHandler()
// vaddr 0x1f9c410 | ghidra 0x209c410 | size 212 | symbol _ZN4Aska10AafHandlerD2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10AafHandlerD2Ev(long *param_1)

{
  uint uVar1;
  
  *param_1 = (long)(PTR__ZTVN4Aska10AafHandlerE_02cbc038 + 0x10);
  if (param_1[0x14] != 0) {
    Aska::Task::Remove()();
    (**(code **)(*(long *)param_1[0x14] + 0x50))();
    param_1[0x14] = 0;
  }
  Aska::AafHandler::DetachObject()(param_1);
  if ((*(byte *)((long)param_1 + 0xc) >> 4 & 1) != 0) {
    Aska::AafHandler::DetachObject()(param_1);
  }
  *(undefined2 *)((long)param_1 + 0xf4) = 0;
  *(undefined4 *)(param_1 + 0x15) = 0;
  *(undefined4 *)(param_1 + 9) = 0;
  param_1[0x13] = 0;
  param_1[8] = 0;
  param_1[7] = 0;
  param_1[0x12] = 0;
  param_1[0x11] = 0;
  param_1[0x10] = 0;
  param_1[0xf] = 0;
  param_1[0x1c] = 0;
  param_1[0x19] = 0;
  param_1[0x18] = 0;
  param_1[0x1b] = 0;
  param_1[0x1a] = 0;
  param_1[0x17] = 0;
  param_1[0x16] = 0;
  if (param_1[10] != 0) {
    operator delete[](void*)();
    param_1[10] = 0;
  }
  uVar1 = *(uint *)((long)param_1 + 0xc);
  param_1[4] = 0;
  param_1[5] = 0;
  param_1[3] = 0;
  *(uint *)((long)param_1 + 0xc) = uVar1 & 0xfffffe34;
  *(undefined1 *)((long)param_1 + 0xf7) = 0;
  if (((uVar1 >> 2 & 1) == 0) && (param_1[2] != 0)) {
    operator delete[](void*)();
    param_1[2] = 0;
  }
  *param_1 = (long)(PTR__ZTVN4Aska13TSmartPointerILb0EEE_02cc2320 + 0x10);
  return;
}

// ==== Aska::AafHandler::~AafHandler()
// vaddr 0x1f9c4e4 | ghidra 0x209c4e4 | size 24 | symbol _ZN4Aska10AafHandlerD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10AafHandlerD0Ev(undefined8 param_1)

{
  Aska::AafHandler::~AafHandler()();
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== void Aska::AafHandler::RenewalOneControllerCache<1>(float, int)
// vaddr 0x1f9d198 | ghidra 0x209d198 | size 220 | symbol _ZN4Aska10AafHandler25RenewalOneControllerCacheILi1EEEvfi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10AafHandler25RenewalOneControllerCacheILi1EEEvfi(long param_1,int param_2)

{
  long lVar1;
  long *plVar2;
  undefined8 uStack_40;
  undefined4 uStack_38;
  undefined8 uStack_30;
  undefined4 uStack_28;
  
  plVar2 = *(long **)(*(long *)(param_1 + 0x88) + (long)param_2 * 0x30 + 8);
  if (plVar2 != (long *)0x0) {
    lVar1 = *(long *)(param_1 + 0x88) + (long)param_2 * 0x30;
    Aska::AafHandler::Function_RenewalOneControllerCache(float, unsigned short, int, Aska::AafControllerInfo*, Aska::AAF_RENEWAL_ONE_CP*, Aska::AafKeyframeHeader*, Aska::FrameSortDataForSearchOld*, unsigned int, bool)(param_2,1,lVar1,&uStack_40,*(undefined8 *)(lVar1 + 0x18),
                    *(undefined8 *)(param_1 + 0xe0),*(undefined4 *)(param_1 + 0x48),
                    *(uint *)(param_1 + 0xc) >> 6 & 1);
    if ((*(byte *)(param_1 + 0xc) >> 6 & 1) == 0) {
      (**(code **)(*plVar2 + 0xd8))(uStack_28,plVar2,1,uStack_30);
    }
    else {
      (**(code **)(*plVar2 + 0xd8))(uStack_38,plVar2,0,uStack_40);
      (**(code **)(*plVar2 + 0xd8))(uStack_28,plVar2,1,uStack_30);
      (**(code **)(*plVar2 + 0x1c8))(plVar2);
    }
  }
  return;
}

// ==== Aska::AafHandler::Function_RenewalOneControllerCache(float, unsigned short, int, Aska::AafControllerInfo*, Aska::AAF_RENEWAL_ONE_CP*, Aska::AafKeyframeHeader*, Aska::FrameSortDataForSearchOld*, unsigned int, bool)
// vaddr 0x1f9d274 | ghidra 0x209d274 | size 1520 | symbol _ZN4Aska10AafHandler34Function_RenewalOneControllerCacheEftiPNS_17AafControllerInfoEPNS_18AAF_RENEWAL_ONE_CPEPNS_17AafKeyframeHeaderEPNS_25FrameSortDataForSearchOldEjb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10AafHandler34Function_RenewalOneControllerCacheEftiPNS_17AafControllerInfoEPNS_18AAF_RENEWAL_ONE_CPEPNS_17AafKeyframeHeaderEPNS_25FrameSortDataForSearchOldEjb
               (float param_1,ushort param_2,int param_3,long param_4,long *param_5,long param_6,
               long param_7,uint param_8,uint param_9)

{
  int *piVar1;
  uint *puVar2;
  uint uVar3;
  undefined4 uVar4;
  uint uVar5;
  bool bVar6;
  ushort *puVar7;
  uint uVar8;
  float *pfVar9;
  long lVar10;
  uint *puVar11;
  ushort *puVar12;
  uint uVar13;
  uint uVar14;
  long lVar15;
  ushort *puVar16;
  long lVar17;
  int iVar18;
  uint *puVar19;
  int iVar20;
  float fVar21;
  
  if (param_8 == 0) {
    return;
  }
  if ((param_9 & 1) != 0) {
    if (*(long *)(param_4 + 0x20) == 0) {
      return;
    }
    if (*(long *)(param_4 + 0x18) == 0) {
      return;
    }
    uVar13 = *(uint *)(param_4 + 0x28);
    uVar5 = *(int *)(param_6 + 0x14) - 2;
    if (*(int *)(param_6 + 0x14) == 1) {
      uVar5 = 0;
    }
    while( true ) {
      while( true ) {
        puVar11 = (uint *)(*(long *)(param_4 + 0x20) + (ulong)uVar13 * 8);
        puVar2 = puVar11 + 2;
        puVar19 = puVar2;
        if (param_1 < (float)puVar11[1]) break;
        uVar8 = uVar5;
        if (((uVar13 == uVar5) || (puVar19 = puVar11, uVar8 = uVar13, uVar5 <= uVar13)) ||
           (puVar19 = puVar2, param_1 < (float)puVar11[3])) goto code_r0x0209d650;
        uVar13 = uVar13 + 1;
      }
      if (uVar13 == 0) break;
      uVar13 = uVar13 - 1;
    }
    uVar8 = 0;
code_r0x0209d650:
    uVar13 = *puVar11;
    uVar5 = *puVar19;
    *(uint *)(param_5 + 1) = puVar11[1];
    *param_5 = (ulong)uVar13 + (long)puVar11;
    uVar13 = puVar19[1];
    param_5[2] = (ulong)uVar5 + (long)puVar19;
    *(uint *)(param_5 + 3) = uVar13;
    *(uint *)(param_4 + 0x28) = uVar8;
    return;
  }
  uVar13 = *(uint *)(param_4 + 0x28);
  fVar21 = *(float *)(param_7 + (ulong)uVar13 * 8 + 4);
  uVar5 = param_8 - 1;
  if ((int)uVar13 < (int)uVar5) {
    if ((int)uVar13 < 1) {
      if (param_1 <= fVar21) goto code_r0x0209d3f0;
    }
    else {
      if ((param_1 < *(float *)(param_7 + (ulong)(uVar13 + 1) * 8 + 4)) && (fVar21 <= param_1))
      goto code_r0x0209d3f0;
      uVar8 = uVar13;
      if ((int)uVar13 < (int)(param_8 - 2)) {
        uVar8 = uVar13 + 1;
      }
      uVar14 = uVar13 - 1;
      bVar6 = (int)uVar13 < (int)(param_8 - 2);
      uVar13 = uVar8;
      if (param_1 < fVar21 && bVar6) {
        uVar13 = uVar14;
      }
      fVar21 = *(float *)(param_7 + (ulong)uVar13 * 8 + 4);
      if (param_1 < *(float *)(param_7 + (ulong)(uVar13 + 1) * 8 + 4)) goto code_r0x0209d364;
    }
  }
  else {
code_r0x0209d364:
    if (fVar21 <= param_1) goto code_r0x0209d3f0;
  }
  uVar8 = 0;
  if (fVar21 <= param_1) {
    uVar8 = param_8;
  }
  iVar18 = uVar8 + uVar13;
  if (1 < iVar18) {
    uVar8 = uVar13;
    if (fVar21 <= param_1) {
      uVar8 = param_8;
    }
    uVar14 = 0;
    if (fVar21 <= param_1) {
      uVar14 = uVar13;
    }
    do {
      if (iVar18 < 0) {
        iVar18 = iVar18 + 1;
      }
      uVar3 = iVar18 >> 1;
      uVar13 = uVar5;
      if (((int)uVar5 <= (int)uVar3) ||
         ((fVar21 = *(float *)(param_7 + (ulong)uVar3 * 8 + 4),
          param_1 < *(float *)(param_7 + (ulong)(uVar3 + 1) * 8 + 4) &&
          (uVar13 = uVar3, fVar21 <= param_1)))) goto code_r0x0209d3f0;
      uVar13 = uVar3;
      if (fVar21 <= param_1) {
        uVar13 = uVar8;
        uVar14 = uVar3;
      }
      iVar18 = uVar13 + uVar14;
      uVar8 = uVar13;
    } while (1 < iVar18);
  }
  uVar13 = 0;
code_r0x0209d3f0:
  *(uint *)(param_4 + 0x28) = uVar13;
  *(byte *)(param_4 + 0x2e) = *(byte *)(param_4 + 0x2e) | 0x10;
  if (param_3 == 1) {
    if (uVar13 != param_8) {
      lVar10 = (long)(int)uVar13;
      do {
        puVar11 = (uint *)(param_7 + lVar10 * 8);
        puVar12 = (ushort *)((ulong)*puVar11 + (long)puVar11);
        puVar7 = puVar12;
        for (iVar18 = *(int *)puVar12; iVar18 != 0; iVar18 = iVar18 + -1) {
          puVar16 = puVar7 + 2;
          Hint_Prefetch(puVar7 + 4,0,2,0);
          if (*puVar16 == param_2) goto code_r0x0209d618;
          puVar7 = puVar16;
        }
        lVar10 = lVar10 + 1;
      } while ((uint)lVar10 != param_8);
    }
    if (uVar13 != 0) {
      lVar10 = (long)(int)(uVar13 - 1);
      do {
        puVar11 = (uint *)(param_7 + lVar10 * 8);
        puVar12 = (ushort *)((ulong)*puVar11 + (long)puVar11);
        puVar7 = puVar12;
        for (iVar18 = *(int *)puVar12; iVar18 != 0; iVar18 = iVar18 + -1) {
          puVar16 = puVar7 + 2;
          Hint_Prefetch(puVar7 + 4,0,2,0);
          if (*puVar16 == param_2) {
code_r0x0209d618:
            uVar4 = *(undefined4 *)(param_7 + lVar10 * 8 + 4);
            param_5[2] = (long)puVar12 + (ulong)puVar16[1];
            *(undefined4 *)(param_5 + 3) = uVar4;
            *(int *)(param_4 + 0x28) = (int)lVar10;
            return;
          }
          puVar7 = puVar16;
        }
        lVar10 = lVar10 + -1;
      } while ((int)lVar10 != -1);
    }
  }
  else if (param_3 == 0) {
    if (uVar13 != 0xffffffff) {
      lVar10 = (long)(int)uVar13;
      do {
        puVar11 = (uint *)(param_7 + lVar10 * 8);
        puVar12 = (ushort *)((ulong)*puVar11 + (long)puVar11);
        puVar7 = puVar12;
        for (iVar18 = *(int *)puVar12; iVar18 != 0; iVar18 = iVar18 + -1) {
          puVar16 = puVar7 + 2;
          Hint_Prefetch(puVar7 + 4,0,2,0);
          if (*puVar16 == param_2) goto code_r0x0209d5f8;
          puVar7 = puVar16;
        }
        lVar10 = lVar10 + -1;
      } while ((int)lVar10 != -1);
    }
    if (uVar13 + 1 != param_8) {
      lVar10 = (long)(int)(uVar13 + 1);
      do {
        puVar11 = (uint *)(param_7 + lVar10 * 8);
        puVar12 = (ushort *)((ulong)*puVar11 + (long)puVar11);
        puVar7 = puVar12;
        for (iVar18 = *(int *)puVar12; iVar18 != 0; iVar18 = iVar18 + -1) {
          puVar16 = puVar7 + 2;
          Hint_Prefetch(puVar7 + 4,0,2,0);
          if (*puVar16 == param_2) {
code_r0x0209d5f8:
            uVar4 = *(undefined4 *)(param_7 + lVar10 * 8 + 4);
            *param_5 = (long)puVar12 + (ulong)puVar16[1];
            *(undefined4 *)(param_5 + 1) = uVar4;
            *(int *)(param_4 + 0x28) = (int)lVar10;
            return;
          }
          puVar7 = puVar16;
        }
        lVar10 = lVar10 + 1;
      } while ((uint)lVar10 != param_8);
    }
  }
  else {
    puVar11 = (uint *)0x0;
    if ((uVar13 != 0xffffffff) && (*(float *)(param_6 + 0xc) < param_1)) {
      lVar10 = (long)(int)uVar13;
      do {
        puVar11 = (uint *)(param_7 + lVar10 * 8);
        piVar1 = (int *)((ulong)*puVar11 + (long)puVar11);
        iVar18 = *piVar1;
        if (iVar18 != 0) {
          puVar12 = (ushort *)((long)piVar1 + 6);
          do {
            Hint_Prefetch(puVar12 + 1,0,2,0);
            if (puVar12[-1] == param_2) {
              pfVar9 = (float *)(param_7 + lVar10 * 8 + 4);
              fVar21 = *pfVar9;
              lVar15 = (long)piVar1 + (ulong)*puVar12;
              *param_5 = lVar15;
              *(float *)(param_5 + 1) = fVar21;
              if ((*(byte *)(param_4 + 0x2e) >> 6 & 1) == 0) {
                iVar18 = (int)lVar10;
                if (*pfVar9 < *(float *)(param_6 + 0x10)) {
                  iVar20 = *(int *)(param_4 + 0x28);
                  *(int *)(param_4 + 0x28) = iVar18;
                  uVar13 = iVar20 + 1;
                  if (uVar13 != param_8) {
                    lVar17 = (long)(int)uVar13;
                    do {
                      puVar11 = (uint *)(param_7 + lVar17 * 8);
                      piVar1 = (int *)((ulong)*puVar11 + (long)puVar11);
                      iVar20 = *piVar1;
                      if (iVar20 != 0) {
                        puVar12 = (ushort *)((long)piVar1 + 6);
                        do {
                          Hint_Prefetch(puVar12 + 1,0,2,0);
                          if (puVar12[-1] == param_2) {
                            uVar4 = *(undefined4 *)(param_7 + lVar17 * 8 + 4);
                            param_5[2] = (long)piVar1 + (ulong)*puVar12;
                            *(undefined4 *)(param_5 + 3) = uVar4;
                            return;
                          }
                          iVar20 = iVar20 + -1;
                          puVar12 = puVar12 + 2;
                        } while (iVar20 != 0);
                      }
                      lVar17 = lVar17 + 1;
                    } while ((uint)lVar17 != param_8);
                  }
                }
                fVar21 = *pfVar9;
                param_5[2] = lVar15;
                *(float *)(param_5 + 3) = fVar21;
                if (iVar18 != 0) {
                  lVar10 = (lVar10 << 0x20) + -0x100000000 >> 0x20;
                  do {
                    puVar11 = (uint *)(param_7 + lVar10 * 8);
                    piVar1 = (int *)((ulong)*puVar11 + (long)puVar11);
                    iVar20 = *piVar1;
                    if (iVar20 != 0) {
                      puVar12 = (ushort *)((long)piVar1 + 6);
                      do {
                        Hint_Prefetch(puVar12 + 1,0,2,0);
                        if (puVar12[-1] == param_2) {
                          uVar4 = *(undefined4 *)(param_7 + lVar10 * 8 + 4);
                          *param_5 = (long)piVar1 + (ulong)*puVar12;
                          *(undefined4 *)(param_5 + 1) = uVar4;
                          *(int *)(param_4 + 0x28) = (int)lVar10;
                          return;
                        }
                        iVar20 = iVar20 + -1;
                        puVar12 = puVar12 + 2;
                      } while (iVar20 != 0);
                    }
                    lVar10 = lVar10 + -1;
                  } while ((int)lVar10 != -1);
                }
                *(int *)(param_4 + 0x28) = iVar18;
                return;
              }
              fVar21 = *pfVar9;
              goto code_r0x0209d70c;
            }
            iVar18 = iVar18 + -1;
            puVar12 = puVar12 + 2;
          } while (iVar18 != 0);
        }
        lVar10 = lVar10 + -1;
      } while ((int)lVar10 != -1);
    }
    if (uVar13 == param_8) {
      lVar10 = 0;
      uVar13 = param_8;
    }
    else {
      lVar15 = (long)(int)uVar13;
      do {
        puVar11 = (uint *)(param_7 + lVar15 * 8);
        piVar1 = (int *)((ulong)*puVar11 + (long)puVar11);
        iVar18 = *piVar1;
        if (iVar18 != 0) {
          puVar12 = (ushort *)((long)piVar1 + 6);
          do {
            Hint_Prefetch(puVar12 + 1,0,2,0);
            if (puVar12[-1] == param_2) {
              lVar10 = (long)piVar1 + (ulong)*puVar12;
              uVar13 = (uint)lVar15;
              goto code_r0x0209d688;
            }
            iVar18 = iVar18 + -1;
            puVar12 = puVar12 + 2;
          } while (iVar18 != 0);
        }
        lVar15 = lVar15 + 1;
      } while ((uint)lVar15 != param_8);
      lVar10 = 0;
    }
code_r0x0209d688:
    uVar5 = puVar11[1];
    *param_5 = lVar10;
    *(uint *)(param_5 + 1) = uVar5;
    if ((*(byte *)(param_4 + 0x2e) >> 6 & 1) == 0) {
      *(uint *)(param_4 + 0x28) = uVar13;
      if (uVar13 + 1 != param_8) {
        lVar15 = (long)(int)(uVar13 + 1);
        do {
          puVar2 = (uint *)(param_7 + lVar15 * 8);
          piVar1 = (int *)((ulong)*puVar2 + (long)puVar2);
          iVar18 = *piVar1;
          if (iVar18 != 0) {
            puVar12 = (ushort *)((long)piVar1 + 6);
code_r0x0209d6c8:
            Hint_Prefetch(puVar12 + 1,0,2,0);
            if (puVar12[-1] != param_2) goto code_r0x0209d6d8;
            fVar21 = *(float *)(param_7 + lVar15 * 8 + 4);
            lVar15 = (long)piVar1 + (ulong)*puVar12;
code_r0x0209d70c:
            param_5[2] = lVar15;
            goto code_r0x0209d710;
          }
code_r0x0209d6e4:
          lVar15 = lVar15 + 1;
        } while ((uint)lVar15 != param_8);
      }
    }
    fVar21 = (float)puVar11[1];
    param_5[2] = lVar10;
code_r0x0209d710:
    *(float *)(param_5 + 3) = fVar21;
  }
  return;
code_r0x0209d6d8:
  iVar18 = iVar18 + -1;
  puVar12 = puVar12 + 2;
  if (iVar18 == 0) goto code_r0x0209d6e4;
  goto code_r0x0209d6c8;
}

// ==== Aska::AafHandler::SetController(Aska::AafControllerInfo*, unsigned char**, unsigned char**)
// vaddr 0x1fa7290 | ghidra 0x20a7290 | size 1376 | symbol _ZN4Aska10AafHandler13SetControllerEPNS_17AafControllerInfoEPPhS4_ | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8
_ZN4Aska10AafHandler13SetControllerEPNS_17AafControllerInfoEPPhS4_
          (long param_1,long param_2,ulong *param_3)

{
  byte bVar1;
  ushort uVar2;
  ushort uVar3;
  undefined *puVar4;
  undefined *puVar5;
  undefined *puVar6;
  undefined *puVar7;
  int iVar8;
  ulong uVar9;
  long lVar10;
  long lVar11;
  undefined8 uVar12;
  long *plVar13;
  undefined1 *puVar14;
  long lVar15;
  long lVar16;
  undefined1 auVar17 [16];
  
  puVar5 = PTR__ZTVN4Aska18AafNoiseControllerE_02cb8cf8;
  puVar4 = PTR__ZTVN4Aska23AafValueArrayControllerE_02cb7918;
  auVar17 = _UNK_027f44a0;
  lVar16 = _UNK_027ed898;
  lVar15 = _UNK_027ed890;
  puVar14 = *(undefined1 **)(param_2 + 0x10);
  switch(*puVar14) {
  case 4:
    plVar13 = (long *)*param_3;
    *(undefined4 *)((long)plVar13 + 0xc) = 0;
    *plVar13 = (long)(puVar5 + 0x10);
    plVar13[2] = (long)(puVar5 + 0x220);
    plVar13[6] = 0;
    plVar13[7] = 0;
    *(undefined4 *)((long)plVar13 + 0x44) = 0x3f800000;
    plVar13[9] = 0;
    plVar13[10] = 0;
    *(ulong *)(param_2 + 8) = *param_3;
    uVar9 = *param_3 + 0x60;
    goto code_r0x020a7644;
  default:
    if ((((*(byte *)(param_2 + 0x2e) >> 3 & 1) == 0) &&
        ((*(char *)(*(long *)(param_2 + 0x18) + 8) == '\x03' ||
         (*(char *)(*(long *)(param_2 + 0x18) + 9) == '\x03')))) &&
       (((byte)puVar14[5] >> 6 & 1) == 0)) {
      uVar9 = bool LocalSetController<true>(Aska::AafHandler*, Aska::AafControllerInfo*, unsigned char**, unsigned char**)(param_1,param_2,param_3);
      uVar9 = uVar9 & 1;
    }
    else {
      uVar9 = bool LocalSetController<false>(Aska::AafHandler*, Aska::AafControllerInfo*, unsigned char**, unsigned char**)(param_1,param_2,param_3);
      uVar9 = uVar9 & 1;
    }
    goto joined_r0x020a735c;
  case 6:
    plVar13 = (long *)*param_3;
    auVar17 = NEON_fmov(0x3f800000,4);
    *plVar13 = (long)(PTR__ZTVN4Aska26AafPRSConstraintControllerE_02cbe088 + 0x10);
    puVar4 = PTR__ZTVN4Aska22AafPRSConstraintObjectE_02cc12a0;
    *(undefined4 *)((long)plVar13 + 0xc) = 0;
    *(undefined4 *)(plVar13 + 8) = 0;
    plVar13[0xb] = 0;
    plVar13[0xc] = 0;
    plVar13[6] = (long)(puVar4 + 0x10);
    plVar13[7] = 0;
    plVar13[5] = auVar17._8_8_;
    plVar13[4] = auVar17._0_8_;
    *(ulong *)(param_2 + 8) = *param_3;
    *param_3 = *param_3 + 0x70;
    if (*(long *)(param_2 + 8) == 0) break;
    bVar1 = puVar14[0x1f];
    if ((ushort)bVar1 < *(ushort *)(param_1 + 0xf4)) {
      lVar15 = *(long *)(*(long *)(param_1 + 0x78) + (ulong)bVar1 * 0x10);
      if (((lVar15 != 0) && (*(char *)(lVar15 + 1) == '\x05')) &&
         (plVar13 = (long *)(*(long *)(param_1 + 0x78) + (ulong)bVar1 * 0x10 + 8), *plVar13 == 0)) {
        *plVar13 = *(long *)(param_2 + 8) + 0x30;
      }
    }
    goto code_r0x020a7668;
  case 7:
    plVar13 = (long *)*param_3;
    *plVar13 = (long)(PTR__ZTVN4Aska26AafAimConstraintControllerE_02cbbec8 + 0x10);
    puVar4 = PTR__ZTVN4Aska22AafAimConstraintObjectE_02cc4e78;
    *(undefined4 *)((long)plVar13 + 0xc) = 0;
    *(undefined4 *)(plVar13 + 5) = 0;
    plVar13[9] = auVar17._8_8_;
    plVar13[8] = auVar17._0_8_;
    plVar13[0xb] = lVar16;
    plVar13[10] = lVar15;
    plVar13[3] = (long)(puVar4 + 0x10);
    plVar13[4] = 0;
    *(ulong *)(param_2 + 8) = *param_3;
    *param_3 = *param_3 + 0x60;
    lVar15 = *(long *)(param_2 + 8);
    if (lVar15 != 0) {
      bVar1 = puVar14[0x3f];
code_r0x020a74ac:
      if ((ushort)bVar1 < *(ushort *)(param_1 + 0xf4)) {
        lVar16 = *(long *)(*(long *)(param_1 + 0x78) + (ulong)bVar1 * 0x10);
        if (((lVar16 != 0) && (*(char *)(lVar16 + 1) == '\x05')) &&
           (plVar13 = (long *)(*(long *)(param_1 + 0x78) + (ulong)bVar1 * 0x10 + 8), *plVar13 == 0))
        {
          *plVar13 = lVar15 + 0x18;
        }
      }
      goto code_r0x020a7668;
    }
    break;
  case 8:
    plVar13 = (long *)*param_3;
    *plVar13 = (long)(PTR__ZTVN4Aska29AafParentConstraintControllerE_02cbac20 + 0x10);
    puVar4 = PTR__ZTVN4Aska25AafParentConstraintObjectE_02cc0920;
    *(undefined4 *)((long)plVar13 + 0xc) = 0;
    *(undefined4 *)(plVar13 + 5) = 0;
    plVar13[3] = (long)(puVar4 + 0x10);
    plVar13[4] = 0;
    *(ulong *)(param_2 + 8) = *param_3;
    *param_3 = *param_3 + 0x50;
    lVar15 = *(long *)(param_2 + 8);
    if (lVar15 != 0) {
      bVar1 = puVar14[0xf];
      goto code_r0x020a74ac;
    }
    break;
  case 9:
    uVar2 = *(ushort *)(param_2 + 0x2c);
    plVar13 = (long *)(*(long *)(param_1 + 0x78) + (ulong)uVar2 * 0x10);
    if ((*plVar13 != 0) && (uVar3 = *(ushort *)(param_1 + 0xf4), uVar3 != 0)) {
      lVar15 = 0;
      uVar9 = 0;
code_r0x020a7510:
      if (uVar2 == uVar9) {
code_r0x020a7570:
        uVar9 = uVar9 + 1;
        lVar15 = lVar15 + 0x10;
        if ((long)(ulong)uVar3 <= (long)uVar9) break;
        goto code_r0x020a7510;
      }
      lVar16 = *(long *)(param_1 + 0x78);
      if (((*(long *)(lVar16 + lVar15) == 0) ||
          (*(char *)(*(long *)(lVar16 + lVar15) + 1) != '\x04')) ||
         (*(long *)(lVar16 + lVar15 + 8) != 0)) goto code_r0x020a7570;
      lVar10 = Aska::AafHandler::GetTargetName(Aska::AafTargetHeaderBase const*) const(param_1);
      lVar11 = Aska::AafHandler::GetTargetName(Aska::AafTargetHeaderBase const*) const(param_1,*plVar13);
      if (((lVar10 == 0) || (lVar11 == 0)) ||
         (iVar8 = strcmp(lVar10,lVar11),
         puVar7 = PTR__ZTVN4Aska19TAafMultiControllerIfLi2EEE_02cc2270,
         puVar6 = PTR__ZTVN4Aska19TAafAnimatableValueIfLi2EEE_02cc1db0,
         puVar5 = PTR__ZTVN4Aska19TAafAnimatableValueIfLi4EEE_02cbcaf0,
         puVar4 = PTR__ZTVN4Aska19TAafMultiControllerIfLi4EEE_02cbc428, iVar8 != 0))
      goto code_r0x020a7570;
      if (puVar14[1] == '\x04') {
        plVar13 = (long *)*param_3;
        *(undefined4 *)((long)plVar13 + 0xc) = 0;
        *plVar13 = (long)(puVar4 + 0x10);
        plVar13[3] = 0;
        plVar13[4] = 0;
        plVar13[2] = (long)(puVar5 + 0x10);
        lVar10 = *param_3 + 0x10;
        lVar11 = 0x28;
        goto code_r0x020a77d0;
      }
      if (puVar14[1] != '\x02') break;
      plVar13 = (long *)*param_3;
      *(undefined4 *)((long)plVar13 + 0xc) = 0;
      *plVar13 = (long)(puVar7 + 0x10);
      plVar13[2] = (long)(puVar6 + 0x10);
      plVar13[3] = 0;
      lVar10 = *param_3 + 0x10;
      lVar11 = 0x20;
code_r0x020a77d0:
      *(long *)(lVar16 + lVar15 + 8) = lVar10;
      *(ulong *)(param_2 + 8) = *param_3;
      *param_3 = *param_3 + lVar11;
      goto code_r0x020a7668;
    }
    break;
  case 10:
    uVar2 = *(ushort *)(param_2 + 0x2c);
    plVar13 = (long *)(*(long *)(param_1 + 0x78) + (ulong)uVar2 * 0x10);
    if ((*plVar13 != 0) && (uVar3 = *(ushort *)(param_1 + 0xf4), uVar3 != 0)) {
      lVar15 = 0;
      uVar9 = 0;
      do {
        if (uVar2 != uVar9) {
          lVar16 = *(long *)(param_1 + 0x78);
          if (((*(long *)(lVar16 + lVar15) != 0) &&
              (*(char *)(*(long *)(lVar16 + lVar15) + 1) == '\x04')) &&
             (*(long *)(lVar16 + lVar15 + 8) == 0)) {
            lVar10 = Aska::AafHandler::GetTargetName(Aska::AafTargetHeaderBase const*) const(param_1);
            lVar11 = Aska::AafHandler::GetTargetName(Aska::AafTargetHeaderBase const*) const(param_1,*plVar13);
            if (((lVar10 != 0) && (lVar11 != 0)) &&
               (iVar8 = strcmp(lVar10,lVar11),
               puVar5 = PTR__ZTVN4Aska19TAafMultiControllerINS_6VectorELi2EEE_02cb9760,
               puVar4 = PTR__ZTVN4Aska19TAafAnimatableValueINS_6VectorELi2EEE_02cb9738, iVar8 == 0))
            {
              if (puVar14[1] == '\x04') {
                plVar13 = (long *)*param_3;
                *plVar13 = (long)(PTR__ZTVN4Aska19TAafMultiControllerINS_6VectorELi4EEE_02cc1da0 +
                                 0x10);
                puVar4 = PTR__ZTVN4Aska19TAafAnimatableValueINS_6VectorELi4EEE_02cc0a78;
                *(undefined4 *)((long)plVar13 + 0xc) = 0;
                plVar13[9] = 0;
                plVar13[8] = 0;
                plVar13[0xb] = 0;
                plVar13[10] = 0;
                plVar13[5] = 0;
                plVar13[4] = 0;
                plVar13[7] = 0;
                plVar13[6] = 0;
                plVar13[2] = (long)(puVar4 + 0x10);
                lVar10 = *param_3 + 0x10;
                lVar11 = 0x60;
                goto code_r0x020a77d0;
              }
              if (puVar14[1] == '\x02') {
                plVar13 = (long *)*param_3;
                *(undefined4 *)((long)plVar13 + 0xc) = 0;
                *plVar13 = (long)(puVar5 + 0x10);
                plVar13[2] = (long)(puVar4 + 0x10);
                plVar13[5] = 0;
                plVar13[4] = 0;
                plVar13[7] = 0;
                plVar13[6] = 0;
                lVar10 = *param_3 + 0x10;
                lVar11 = 0x40;
                goto code_r0x020a77d0;
              }
              break;
            }
          }
        }
        uVar9 = uVar9 + 1;
        lVar15 = lVar15 + 0x10;
      } while ((long)uVar9 < (long)(ulong)uVar3);
    }
    break;
  case 0xb:
    plVar13 = (long *)*param_3;
    *(undefined4 *)((long)plVar13 + 0xc) = 0;
    *plVar13 = (long)(puVar4 + 0x10);
    *(ulong *)(param_2 + 8) = *param_3;
    uVar9 = *param_3 + 0x20;
code_r0x020a7644:
    *param_3 = uVar9;
    uVar9 = *(ulong *)(param_2 + 8);
joined_r0x020a735c:
    if (uVar9 != 0) {
code_r0x020a7668:
      uVar12 = 1;
      goto code_r0x020a7728;
    }
  }
  uVar12 = 0;
  if (*(long **)(param_2 + 8) != (long *)0x0) {
    (**(code **)(**(long **)(param_2 + 8) + 0xb0))();
    uVar12 = 0;
  }
code_r0x020a7728:
  *param_3 = *param_3 + 0xf & 0xfffffffffffffff0;
  return uVar12;
}

// ==== Aska::AafController::Clone(Aska::IController*, bool)
// vaddr 0x1fa7b3c | ghidra 0x20a7b3c | size 8 | symbol _ZN4Aska13AafController5CloneEPNS_11IControllerEb | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska13AafController5CloneEPNS_11IControllerEb(void)

{
  return 0;
}

// ==== Aska::AafController::Copy(Aska::IController*, bool)
// vaddr 0x1fa7b44 | ghidra 0x20a7b44 | size 8 | symbol _ZN4Aska13AafController4CopyEPNS_11IControllerEb | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska13AafController4CopyEPNS_11IControllerEb(void)

{
  return 0;
}

// ==== Aska::AafController::CalcValue(void*, float)
// vaddr 0x1fa7b64 | ghidra 0x20a7b64 | size 4 | symbol _ZN4Aska13AafController9CalcValueEPvf | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13AafController9CalcValueEPvf(void)

{
  return;
}

// ==== Aska::AafController::GetAafKeyframeHeader() const
// vaddr 0x1fa7b7c | ghidra 0x20a7b7c | size 8 | symbol _ZNK4Aska13AafController20GetAafKeyframeHeaderEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska13AafController20GetAafKeyframeHeaderEv(void)

{
  return 0;
}

// ==== Aska::AafController::GetKeyframe(float*, int) const
// vaddr 0x1fa7b84 | ghidra 0x20a7b84 | size 8 | symbol _ZNK4Aska13AafController11GetKeyframeEPfi | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska13AafController11GetKeyframeEPfi(void)

{
  return 0;
}

// ==== Aska::AafController::GetControlPoint(void*, int) const
// vaddr 0x1fa7b8c | ghidra 0x20a7b8c | size 8 | symbol _ZNK4Aska13AafController15GetControlPointEPvi | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska13AafController15GetControlPointEPvi(void)

{
  return 0;
}

// ==== Aska::AafController::GetIAnimatable()
// vaddr 0x1fa7b94 | ghidra 0x20a7b94 | size 8 | symbol _ZN4Aska13AafController14GetIAnimatableEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska13AafController14GetIAnimatableEv(void)

{
  return 0;
}

// ==== Aska::AafController::CallDestructor()
// vaddr 0x1fa7b9c | ghidra 0x20a7b9c | size 12 | symbol _ZN4Aska13AafController14CallDestructorEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13AafController14CallDestructorEv(undefined8 *param_1)

{
                    /* WARNING: Could not recover jumptable at 0x020a7ba4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)*param_1)();
  return;
}

// ==== Aska::AafController::DetachObject()
// vaddr 0x1fa7ba8 | ghidra 0x20a7ba8 | size 4 | symbol _ZN4Aska13AafController12DetachObjectEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13AafController12DetachObjectEv(void)

{
  return;
}

// ==== Aska::AafController::SetControlBuffer(unsigned char**, int)
// vaddr 0x1fa7bac | ghidra 0x20a7bac | size 4 | symbol _ZN4Aska13AafController16SetControlBufferEPPhi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13AafController16SetControlBufferEPPhi(void)

{
  return;
}

// ==== Aska::AafController::SetComplementBuffer(unsigned char**)
// vaddr 0x1fa7bb0 | ghidra 0x20a7bb0 | size 4 | symbol _ZN4Aska13AafController19SetComplementBufferEPPh | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13AafController19SetComplementBufferEPPh(void)

{
  return;
}

// ==== Aska::AafController::SetControlPoint(int, float, void*)
// vaddr 0x1fa7bb4 | ghidra 0x20a7bb4 | size 4 | symbol _ZN4Aska13AafController15SetControlPointEifPv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13AafController15SetControlPointEifPv(void)

{
  return;
}

// ==== Aska::AafController::ForceSetControlPoint(int, float, void*)
// vaddr 0x1fa7bb8 | ghidra 0x20a7bb8 | size 12 | symbol _ZN4Aska13AafController20ForceSetControlPointEifPv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13AafController20ForceSetControlPointEifPv(long *param_1)

{
                    /* WARNING: Could not recover jumptable at 0x020a7bc0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*param_1 + 0xd8))();
  return;
}

// ==== Aska::AafController::SwapControlPoint()
// vaddr 0x1fa7bc4 | ghidra 0x20a7bc4 | size 4 | symbol _ZN4Aska13AafController16SwapControlPointEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13AafController16SwapControlPointEv(void)

{
  return;
}

// ==== Aska::AafController::SetLoopCount(int)
// vaddr 0x1fa7bc8 | ghidra 0x20a7bc8 | size 4 | symbol _ZN4Aska13AafController12SetLoopCountEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13AafController12SetLoopCountEi(void)

{
  return;
}

// ==== Aska::AafController::SetLoopCount(float)
// vaddr 0x1fa7bcc | ghidra 0x20a7bcc | size 4 | symbol _ZN4Aska13AafController12SetLoopCountEf | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13AafController12SetLoopCountEf(void)

{
  return;
}

// ==== Aska::AafController::SetFigureRate(float)
// vaddr 0x1fa7bd0 | ghidra 0x20a7bd0 | size 4 | symbol _ZN4Aska13AafController13SetFigureRateEf | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13AafController13SetFigureRateEf(void)

{
  return;
}

// ==== Aska::AafController::IsNecessaryToRenewalCache(float, float, float)
// vaddr 0x1fa7bd4 | ghidra 0x20a7bd4 | size 8 | symbol _ZN4Aska13AafController25IsNecessaryToRenewalCacheEfff | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska13AafController25IsNecessaryToRenewalCacheEfff(void)

{
  return 0;
}

// ==== Aska::AafController::GetDifferenceOfValue(void*)
// vaddr 0x1fa7bdc | ghidra 0x20a7bdc | size 4 | symbol _ZN4Aska13AafController20GetDifferenceOfValueEPv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13AafController20GetDifferenceOfValueEPv(void)

{
  return;
}

// ==== Aska::AafController::SetDifferenceOfValue(void*)
// vaddr 0x1fa7be0 | ghidra 0x20a7be0 | size 4 | symbol _ZN4Aska13AafController20SetDifferenceOfValueEPv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13AafController20SetDifferenceOfValueEPv(void)

{
  return;
}

// ==== Aska::AafController::AddDifferenceOfValue(void*, float)
// vaddr 0x1fa7be4 | ghidra 0x20a7be4 | size 4 | symbol _ZN4Aska13AafController20AddDifferenceOfValueEPvf | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13AafController20AddDifferenceOfValueEPvf(void)

{
  return;
}

// ==== Aska::AafController::GetValue(void*, void*)
// vaddr 0x1fa7be8 | ghidra 0x20a7be8 | size 4 | symbol _ZN4Aska13AafController8GetValueEPvS1_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13AafController8GetValueEPvS1_(void)

{
  return;
}

// ==== Aska::AafController::GetComplementValue(int, void*)
// vaddr 0x1fa7bec | ghidra 0x20a7bec | size 4 | symbol _ZN4Aska13AafController18GetComplementValueEiPv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13AafController18GetComplementValueEiPv(void)

{
  return;
}

// ==== Aska::AafController::GetComplementTangent(int, void*, void*)
// vaddr 0x1fa7bf0 | ghidra 0x20a7bf0 | size 4 | symbol _ZN4Aska13AafController20GetComplementTangentEiPvS1_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13AafController20GetComplementTangentEiPvS1_(void)

{
  return;
}

// ==== Aska::AafController::CalcValueComplement(void*, float, float, float)
// vaddr 0x1fa7bf4 | ghidra 0x20a7bf4 | size 4 | symbol _ZN4Aska13AafController19CalcValueComplementEPvfff | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13AafController19CalcValueComplementEPvfff(void)

{
  return;
}

// ==== Aska::AafController::CalcValueConstant(void*, int)
// vaddr 0x1fa7bf8 | ghidra 0x20a7bf8 | size 4 | symbol _ZN4Aska13AafController17CalcValueConstantEPvi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13AafController17CalcValueConstantEPvi(void)

{
  return;
}

// ==== Aska::AafController::CalcValueByLinearAtPreOutOfRange(void*, float)
// vaddr 0x1fa7bfc | ghidra 0x20a7bfc | size 4 | symbol _ZN4Aska13AafController32CalcValueByLinearAtPreOutOfRangeEPvf | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13AafController32CalcValueByLinearAtPreOutOfRangeEPvf(void)

{
  return;
}

// ==== Aska::AafController::CalcValueByLinearAtPostOutOfRange(void*, float)
// vaddr 0x1fa7c00 | ghidra 0x20a7c00 | size 4 | symbol _ZN4Aska13AafController33CalcValueByLinearAtPostOutOfRangeEPvf | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13AafController33CalcValueByLinearAtPostOutOfRangeEPvf(void)

{
  return;
}

// ==== Aska::AafController::SetValueOfDirectAddr(void*, void*)
// vaddr 0x1fa7c04 | ghidra 0x20a7c04 | size 4 | symbol _ZN4Aska13AafController20SetValueOfDirectAddrEPvS1_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13AafController20SetValueOfDirectAddrEPvS1_(void)

{
  return;
}

// ==== Aska::AafController::AddValueOfDirectAddr(void*, void*)
// vaddr 0x1fa7c08 | ghidra 0x20a7c08 | size 4 | symbol _ZN4Aska13AafController20AddValueOfDirectAddrEPvS1_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13AafController20AddValueOfDirectAddrEPvS1_(void)

{
  return;
}

// ==== Aska::AafController::AddValueToTarget(void*, Aska::AafSetValueArg*)
// vaddr 0x1fa7c0c | ghidra 0x20a7c0c | size 4 | symbol _ZN4Aska13AafController16AddValueToTargetEPvPNS_14AafSetValueArgE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13AafController16AddValueToTargetEPvPNS_14AafSetValueArgE(void)

{
  return;
}

// ==== Aska::AafController::BlendValueOfDirectAddr(void*, void*, float)
// vaddr 0x1fa7c10 | ghidra 0x20a7c10 | size 4 | symbol _ZN4Aska13AafController22BlendValueOfDirectAddrEPvS1_f | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13AafController22BlendValueOfDirectAddrEPvS1_f(void)

{
  return;
}

// ==== Aska::AafController::BlendValueToTarget(void*, Aska::AafSetValueArg*)
// vaddr 0x1fa7c14 | ghidra 0x20a7c14 | size 4 | symbol _ZN4Aska13AafController18BlendValueToTargetEPvPNS_14AafSetValueArgE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13AafController18BlendValueToTargetEPvPNS_14AafSetValueArgE(void)

{
  return;
}

// ==== Aska::AafController::GetInputAddrForValue(Aska::AafSetValueArg*)
// vaddr 0x1fa7c18 | ghidra 0x20a7c18 | size 8 | symbol _ZN4Aska13AafController20GetInputAddrForValueEPNS_14AafSetValueArgE | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska13AafController20GetInputAddrForValueEPNS_14AafSetValueArgE(void)

{
  return 0;
}

// ==== Aska::AafController::GetOutputAddrForValue(Aska::AafSetValueArg*)
// vaddr 0x1fa7c20 | ghidra 0x20a7c20 | size 8 | symbol _ZN4Aska13AafController21GetOutputAddrForValueEPNS_14AafSetValueArgE | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska13AafController21GetOutputAddrForValueEPNS_14AafSetValueArgE(void)

{
  return 0;
}

// ==== Aska::AafController::GetInputAddrForValue(Aska::IAnimatable*)
// vaddr 0x1fa7c28 | ghidra 0x20a7c28 | size 8 | symbol _ZN4Aska13AafController20GetInputAddrForValueEPNS_11IAnimatableE | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska13AafController20GetInputAddrForValueEPNS_11IAnimatableE(void)

{
  return 0;
}

// ==== Aska::AafController::GetOutputAddrForValue(Aska::IAnimatable*)
// vaddr 0x1fa7c30 | ghidra 0x20a7c30 | size 8 | symbol _ZN4Aska13AafController21GetOutputAddrForValueEPNS_11IAnimatableE | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska13AafController21GetOutputAddrForValueEPNS_11IAnimatableE(void)

{
  return 0;
}

// ==== Aska::AafController::UpdateTargetForValue(Aska::AafSetValueArg*)
// vaddr 0x1fa7c38 | ghidra 0x20a7c38 | size 4 | symbol _ZN4Aska13AafController20UpdateTargetForValueEPNS_14AafSetValueArgE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13AafController20UpdateTargetForValueEPNS_14AafSetValueArgE(void)

{
  return;
}

// ==== Aska::AafController::GetControllerSize()
// vaddr 0x1fa7c3c | ghidra 0x20a7c3c | size 8 | symbol _ZN4Aska13AafController17GetControllerSizeEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska13AafController17GetControllerSizeEv(void)

{
  return 0x10;
}

// ==== Aska::AafController::SetConstantComplementPoint()
// vaddr 0x1fa7c44 | ghidra 0x20a7c44 | size 4 | symbol _ZN4Aska13AafController26SetConstantComplementPointEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13AafController26SetConstantComplementPointEv(void)

{
  return;
}

// ==== Aska::AafController::UpdateCurrentRange()
// vaddr 0x1fa7c48 | ghidra 0x20a7c48 | size 4 | symbol _ZN4Aska13AafController18UpdateCurrentRangeEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13AafController18UpdateCurrentRangeEv(void)

{
  return;
}

// ==== Aska::AafController::GetCurrentRange()
// vaddr 0x1fa7c4c | ghidra 0x20a7c4c | size 8 | symbol _ZN4Aska13AafController15GetCurrentRangeEv | lib libSOA-3.7.0.so | 2026-10-04
undefined1  [16] _ZN4Aska13AafController15GetCurrentRangeEv(void)

{
  return ZEXT816(0x3f800000);
}

// ==== Aska::AafController::GetKeyframe(int) const
// vaddr 0x1fa7c54 | ghidra 0x20a7c54 | size 8 | symbol _ZNK4Aska13AafController11GetKeyframeEi | lib libSOA-3.7.0.so | 2026-10-04
undefined1  [16] _ZNK4Aska13AafController11GetKeyframeEi(void)

{
  return ZEXT816(0);
}

// ==== Aska::AafController::AttachObject(Aska::AsfHandler*, Aska::AafSetValueArg*, Aska::AafControllerHeader const*)
// vaddr 0x1fa8c18 | ghidra 0x20a8c18 | size 8 | symbol _ZN4Aska13AafController12AttachObjectEPNS_10AsfHandlerEPNS_14AafSetValueArgEPKNS_19AafControllerHeaderE | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska13AafController12AttachObjectEPNS_10AsfHandlerEPNS_14AafSetValueArgEPKNS_19AafControllerHeaderE
          (void)

{
  return 1;
}

// ==== Aska::AafController::IsIndependentController()
// vaddr 0x1fa8e84 | ghidra 0x20a8e84 | size 8 | symbol _ZN4Aska13AafController23IsIndependentControllerEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska13AafController23IsIndependentControllerEv(void)

{
  return 1;
}

// ==== Aska::AafController::SetValueToTarget(void*, Aska::AafSetValueArg*)
// vaddr 0x2072c88 | ghidra 0x2172c88 | size 4 | symbol _ZN4Aska13AafController16SetValueToTargetEPvPNS_14AafSetValueArgE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13AafController16SetValueToTargetEPvPNS_14AafSetValueArgE(void)

{
  return;
}


// FAILED to create function at 02972fd0 typeinfo name for Aska::AafBlendManager::_CalcNotify
// FAILED to create function at 02bb4c10 Aska::AafBlendManager::vtable
// FAILED to create function at 02bb4c48 Aska::AafBlendManager::_CalcNotify::vtable
// FAILED to create function at 02bb4c70 Aska::AafBlendManager::_CalcNotify::typeinfo
// FAILED to create function at 02bb4ca0 Aska::AafBlendManager::typeinfo
// FAILED to create function at 02bb4d78 Aska::AafHandler::vtable
// FAILED to create function at 02bb4da0 Aska::AafHandler::typeinfo
// FAILED to create function at 02bb4e10 Aska::AafController::typeinfo
// FAILED to create function at 02dcda98 Aska::AafHandler::m_pMemoryManager
