// port/decomp/data_formats/acsv.c: Ghidra decompiles for the data_formats subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-04 05:12 UTC: tools/decomp.sh '--into' 'data_formats/acsv' 'Aska::ACSV::'

// ==== Aska::ACSV::ACSV()
// vaddr 0x1efd508 | ghidra 0x1ffd508 | size 108 | symbol _ZN4Aska4ACSVC1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska4ACSVC2Ev(long *param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  
  *(undefined4 *)(param_1 + 2) = 0;
  *(undefined1 *)((long)param_1 + 0x54) = 0x2c;
  puVar2 = PTR__ZTVN4Aska4ACSVE_02cc18f0;
  param_1[4] = 0;
  param_1[3] = 0;
  param_1[7] = 0;
  param_1[6] = 0;
  param_1[9] = 0;
  param_1[8] = 0;
  puVar1 = PTR__ZTVN4Aska9TBitArrayIjLb0EEE_02cba038;
  *(undefined1 *)(param_1 + 5) = 0;
  *(undefined4 *)(param_1 + 10) = 0;
  *(undefined1 *)(param_1 + 0xd) = 0;
  param_1[1] = (long)(puVar1 + 0x10);
  *param_1 = (long)(puVar2 + 0x10);
  param_1[0xb] = 0;
  param_1[0xc] = 0;
  memset(param_1 + 0xe,0,0x78);
  return;
}

// ==== Aska::ACSV::~ACSV()
// vaddr 0x1efd574 | ghidra 0x1ffd574 | size 148 | symbol _ZN4Aska4ACSVD2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska4ACSVD1Ev(long *param_1)

{
  undefined *puVar1;
  
  *param_1 = (long)(PTR__ZTVN4Aska4ACSVE_02cc18f0 + 0x10);
  Aska::ACSV::Clear()();
  if (param_1[0xb] != 0) {
    if ((char)param_1[0xd] != '\0') {
      operator delete[](void*)();
      *(undefined1 *)(param_1 + 0xd) = 0;
    }
    param_1[0xb] = 0;
  }
  puVar1 = PTR__ZTVN4Aska9TBitArrayIjLb0EEE_02cba038;
  param_1[0xc] = 0;
  param_1[0xf] = 0;
  param_1[0x10] = 0;
  param_1[1] = (long)(puVar1 + 0x10);
  if ((param_1[3] != 0) && ((char)param_1[5] != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 5) = 0;
  }
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[1] = (long)(PTR__ZTVN4Aska13TSmartPointerILb0EEE_02cc2320 + 0x10);
  (*(code *)PTR__ZN4Aska11IAnimatableD2Ev_02cb13b8)(param_1);
  return;
}

// ==== Aska::ACSV::Term()
// vaddr 0x1efd608 | ghidra 0x1ffd608 | size 56 | symbol _ZN4Aska4ACSV4TermEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska4ACSV4TermEv(long param_1)

{
  Aska::ACSV::Clear()();
  if (*(long *)(param_1 + 0x58) != 0) {
    if (*(char *)(param_1 + 0x68) != '\0') {
      operator delete[](void*)();
      *(undefined1 *)(param_1 + 0x68) = 0;
    }
    *(undefined8 *)(param_1 + 0x58) = 0;
  }
  *(undefined8 *)(param_1 + 0x60) = 0;
  *(undefined8 *)(param_1 + 0x78) = 0;
  *(undefined8 *)(param_1 + 0x80) = 0;
  return;
}

// ==== Aska::ACSV::~ACSV()
// vaddr 0x1efd640 | ghidra 0x1ffd640 | size 156 | symbol _ZN4Aska4ACSVD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska4ACSVD0Ev(long *param_1)

{
  undefined *puVar1;
  
  *param_1 = (long)(PTR__ZTVN4Aska4ACSVE_02cc18f0 + 0x10);
  Aska::ACSV::Clear()();
  if (param_1[0xb] != 0) {
    if ((char)param_1[0xd] != '\0') {
      operator delete[](void*)();
      *(undefined1 *)(param_1 + 0xd) = 0;
    }
    param_1[0xb] = 0;
  }
  puVar1 = PTR__ZTVN4Aska9TBitArrayIjLb0EEE_02cba038;
  param_1[0xc] = 0;
  param_1[0xf] = 0;
  param_1[0x10] = 0;
  param_1[1] = (long)(puVar1 + 0x10);
  if ((param_1[3] != 0) && ((char)param_1[5] != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 5) = 0;
  }
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[1] = (long)(PTR__ZTVN4Aska13TSmartPointerILb0EEE_02cc2320 + 0x10);
  Aska::IAnimatable::~IAnimatable()(param_1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::ACSV::CalcWorkSize(unsigned long, unsigned long, Aska::ACSV::Extension)
// vaddr 0x1efd6dc | ghidra 0x1ffd6dc | size 44 | symbol _ZN4Aska4ACSV12CalcWorkSizeEmmNS0_9ExtensionE | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska4ACSV12CalcWorkSizeEmmNS0_9ExtensionE(long param_1,long param_2,uint param_3)

{
  long lVar1;
  
  lVar1 = param_1 * param_2 * 0x10 + param_1 * 4;
  if ((param_3 & 1) != 0) {
    lVar1 = (param_2 * param_1 + 0x1fU >> 3 & 0x1ffffffffffffffc) + lVar1;
  }
  return lVar1;
}

// ==== Aska::ACSV::Init(unsigned long, unsigned long, Aska::ACSV::Extension)
// vaddr 0x1efd708 | ghidra 0x1ffd708 | size 268 | symbol _ZN4Aska4ACSV4InitEmmNS0_9ExtensionE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska4ACSV4InitEmmNS0_9ExtensionE
               (undefined8 *param_1,long param_2,long param_3,long param_4,uint param_5)

{
  ulong uVar1;
  undefined8 uVar2;
  ulong uVar3;
  ulong uVar4;
  
  uVar2 = 0xfffffffffffffc43;
  if ((param_3 != 0) && (param_4 != 0)) {
    uVar4 = param_3 * param_4 * 0x10 + param_3 * 4;
    uVar3 = uVar4;
    if ((param_5 & 1) != 0) {
      uVar3 = (param_4 * param_3 + 0x1fU >> 3 & 0x1ffffffffffffffc) + uVar4;
    }
    uVar1 = operator new[](unsigned long, unsigned long, bool)(uVar3,0x10,1);
    if (uVar1 == 0) {
      uVar2 = 0xfffffffffffffc41;
    }
    else {
      *(undefined1 *)(param_2 + 0x68) = 1;
      if ((uVar3 != 0) && ((uVar1 & 0xf) == 0)) {
        if ((param_5 & 1) != 0) {
          uVar4 = (param_4 * param_3 + 0x1fU >> 3 & 0x1ffffffffffffffc) + uVar4;
        }
        if (uVar4 <= uVar3) {
          uVar2 = 0;
          *(ulong *)(param_2 + 0x58) = uVar1;
          *(ulong *)(param_2 + 0x60) = uVar3;
          *(long *)(param_2 + 0x78) = param_3;
          *(long *)(param_2 + 0x80) = param_4;
          *(uint *)(param_2 + 0x50) = param_5;
          goto code_r0x01ffd7e4;
        }
      }
      Aska::ACSV::Clear()(param_2);
      if (*(long *)(param_2 + 0x58) != 0) {
        if (*(char *)(param_2 + 0x68) != '\0') {
          operator delete[](void*)();
          *(undefined1 *)(param_2 + 0x68) = 0;
        }
        *(undefined8 *)(param_2 + 0x58) = 0;
      }
      *(undefined8 *)(param_2 + 0x60) = 0;
      *(undefined8 *)(param_2 + 0x78) = 0;
      *(undefined8 *)(param_2 + 0x80) = 0;
      uVar2 = 0xfffffffffffffc43;
    }
  }
code_r0x01ffd7e4:
  *param_1 = uVar2;
  return;
}

// ==== Aska::ACSV::Init(signed char*, unsigned long, unsigned long, unsigned long, Aska::ACSV::Extension)
// vaddr 0x1efd814 | ghidra 0x1ffd814 | size 112 | symbol _ZN4Aska4ACSV4InitEPammmNS0_9ExtensionE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska4ACSV4InitEPammmNS0_9ExtensionE
               (undefined8 *param_1,long param_2,ulong param_3,ulong param_4,long param_5,
               long param_6,uint param_7)

{
  undefined8 uVar1;
  ulong uVar2;
  
  uVar1 = 0xfffffffffffffc43;
  if ((param_3 != 0) && (param_4 != 0)) {
    if ((param_3 & 0xf) != 0) {
      *param_1 = 0xfffffffffffffc43;
      return;
    }
    uVar2 = param_5 * param_6 * 0x10 + param_5 * 4;
    if ((param_7 & 1) != 0) {
      uVar2 = (param_6 * param_5 + 0x1fU >> 3 & 0x1ffffffffffffffc) + uVar2;
    }
    if (param_4 < uVar2) {
      *param_1 = 0xfffffffffffffc43;
      return;
    }
    uVar1 = 0;
    *(ulong *)(param_2 + 0x58) = param_3;
    *(ulong *)(param_2 + 0x60) = param_4;
    *(long *)(param_2 + 0x78) = param_5;
    *(long *)(param_2 + 0x80) = param_6;
    *(uint *)(param_2 + 0x50) = param_7;
  }
  *param_1 = uVar1;
  return;
}

// ==== Aska::ACSV::Clear()
// vaddr 0x1efd884 | ghidra 0x1ffd884 | size 156 | symbol _ZN4Aska4ACSV5ClearEv | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Possible PIC construction at 0x01ffd904: Changing call to branch */
/* WARNING: Removing unreachable block (ram,0x01ffd908) */

void _ZN4Aska4ACSV5ClearEv(long param_1)

{
  *(undefined8 *)(param_1 + 0x30) = 0;
  *(undefined8 *)(param_1 + 0x48) = 0;
  if ((*(long *)(param_1 + 200) != 0) || (*(long *)(param_1 + 0xd0) != 0)) {
    if (*(long *)(param_1 + 0xe0) == 0) {
      *(undefined8 *)(param_1 + 200) = 0;
      *(long *)(param_1 + 0x70) = *(long *)(param_1 + 0x70) - *(long *)(param_1 + 0xd0);
    }
    else {
      if (*(long *)(param_1 + 200) != 0) {
        operator delete[](void*)();
        *(undefined8 *)(param_1 + 200) = 0;
      }
      *(undefined8 *)(param_1 + 0xe0) = 0;
    }
    *(undefined8 *)(param_1 + 0xd0) = 0;
    *(undefined8 *)(param_1 + 0xd8) = 0;
  }
  if ((*(long *)(param_1 + 0x18) != 0) && (*(char *)(param_1 + 0x28) != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 0x28) = 0;
  }
  *(long *)(param_1 + 0x18) = 0;
  *(undefined8 *)(param_1 + 0x20) = 0;
  (*(code *)PTR__ZN4Aska4ACSV10TermMemoryENS0_12WorkMemoryIDE_02ca32c0)(param_1,1);
  return;
}

// ==== Aska::ACSV::DeserializeBinary(void const*, unsigned long)
// vaddr 0x1efd920 | ghidra 0x1ffd920 | size 416 | symbol _ZN4Aska4ACSV17DeserializeBinaryEPKvm | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska4ACSV17DeserializeBinaryEPKvm(long param_1,int *param_2,long param_3)

{
  long lVar1;
  uint uVar2;
  undefined1 *puVar3;
  ulong uVar4;
  ulong uVar5;
  long lVar6;
  long lStack_b8;
  undefined1 auStack_b0 [128];
  long lStack_28;
  
  if (param_2 == (int *)0x0) {
    return -0x3bd;
  }
  if (param_3 == 0) {
    return -0x3bd;
  }
  if ((*(long *)(param_1 + 0x58) == 0) || (*(long *)(param_1 + 0x60) == 0)) {
    return -0x3bc;
  }
  if (*param_2 != 0x41435356) {
    return -0x3b8;
  }
  if (param_2[4] != 0x10001) {
    return -0x3b9;
  }
  uVar2 = param_2[5];
  uVar5 = (ulong)uVar2;
  if (uVar2 < 0x21) {
    puVar3 = auStack_b0;
    if (uVar2 == 0) {
      uVar5 = 0;
      goto code_r0x01ffd9e0;
    }
  }
  else {
    puVar3 = (undefined1 *)operator new[](unsigned long, std::nothrow_t const&)(uVar5 << 2,PTR__ZSt7nothrow_02cb9a80);
    if (puVar3 == (undefined1 *)0x0) {
      return -0x3bf;
    }
  }
  uVar4 = 0;
  do {
    *(uint *)(puVar3 + uVar4 * 4) = (uint)*(byte *)((long)param_2 + uVar4 + 0x20);
    uVar4 = uVar4 + 1;
  } while (uVar5 != uVar4);
code_r0x01ffd9e0:
  Aska::ACSV::SetTypes(Aska::ACSV::Type const*, unsigned long)(&lStack_28,param_1,puVar3,uVar5);
  if ((puVar3 != auStack_b0) && (puVar3 != (undefined1 *)0x0)) {
    operator delete[](void*)(puVar3);
  }
  if (-1 < lStack_28) {
    uVar2 = param_2[6];
    lVar6 = ((ulong)(uint)param_2[5] + 0xf & 0x1fffffff0) + 0x20;
    if (uVar2 != 0) {
      if ((*(byte *)(param_1 + 0x50) & 1) != 0) {
        Aska::ACSV::SetBlankBits(unsigned char const*, unsigned long)(&lStack_b8,param_1,lVar6 + (long)param_2);
        if (lStack_b8 < 0) {
          return lStack_b8;
        }
        uVar2 = param_2[6];
      }
      lVar6 = lVar6 + (ulong)((uVar2 >> 3) + 0xf & 0x3ffffff0);
    }
    lStack_28 = -0x3bd;
    if ((lVar6 + (long)param_2 != 0) && (param_2[7] != 0)) {
      if ((*(long *)(param_1 + 0x58) == 0) || (*(long *)(param_1 + 0x60) == 0)) {
        lStack_28 = -0x3bc;
      }
      else {
        lStack_28 = Aska::ACSV::UnpackBinaryValues(void const*, unsigned long)(param_1);
      }
    }
    lVar1 = 0;
    if (-1 < lStack_28) {
      lVar1 = lStack_28;
    }
    if (-1 < lStack_28) {
      lStack_28 = lVar1 + lVar6;
    }
  }
  return lStack_28;
}

// ==== Aska::ACSV::SetTypes(Aska::ACSV::Type const*, unsigned long)
// vaddr 0x1efdac0 | ghidra 0x1ffdac0 | size 252 | symbol _ZN4Aska4ACSV8SetTypesEPKNS0_4TypeEm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska4ACSV8SetTypesEPKNS0_4TypeEm
               (undefined8 *param_1,long param_2,long param_3,long param_4)

{
  ulong uVar1;
  undefined8 uVar2;
  long lVar3;
  ulong uVar4;
  
  uVar2 = 0xfffffffffffffc43;
  if ((param_3 != 0) && (param_4 != 0)) {
    if ((*(long *)(param_2 + 0x58) == 0) || (*(long *)(param_2 + 0x60) == 0)) {
      uVar2 = 0xfffffffffffffc44;
    }
    else {
      *(undefined8 *)(param_2 + 0x38) = 0;
      *(undefined8 *)(param_2 + 0x40) = 0;
      Aska::ACSV::TermMemory(Aska::ACSV::WorkMemoryID)(param_2,0);
      lVar3 = *(long *)(param_2 + 0x70);
      uVar4 = param_4 * 4;
      uVar1 = lVar3 + uVar4;
      if (*(ulong *)(param_2 + 0x60) < uVar1) {
        if (*(ulong *)(param_2 + 0xa0) < uVar4) {
          if ((*(ulong *)(param_2 + 0xa0) != 0) && (*(long *)(param_2 + 0x88) != 0)) {
            operator delete[](void*)();
            *(undefined8 *)(param_2 + 0x88) = 0;
          }
          lVar3 = operator new[](unsigned long, std::nothrow_t const&)(uVar4,PTR__ZSt7nothrow_02cb9a80);
          *(long *)(param_2 + 0x88) = lVar3;
          if (lVar3 == 0) {
            uVar2 = 0xfffffffffffffc41;
            goto code_r0x01ffdba0;
          }
          *(ulong *)(param_2 + 0xa0) = uVar4;
        }
        else {
          lVar3 = *(long *)(param_2 + 0x88);
        }
      }
      else {
        *(undefined8 *)(param_2 + 0xa0) = 0;
        *(ulong *)(param_2 + 0x70) = uVar1;
        lVar3 = *(long *)(param_2 + 0x58) + lVar3;
        *(long *)(param_2 + 0x88) = lVar3;
      }
      *(ulong *)(param_2 + 0x90) = uVar4;
      *(undefined8 *)(param_2 + 0x98) = 0;
      *(long *)(param_2 + 0x38) = lVar3;
      memcpy(lVar3,param_3,uVar4);
      uVar2 = 0;
      *(long *)(param_2 + 0x40) = param_4;
    }
  }
code_r0x01ffdba0:
  *param_1 = uVar2;
  return;
}

// ==== Aska::ACSV::SetBlankBits(unsigned char const*, unsigned long)
// vaddr 0x1efdbbc | ghidra 0x1ffdbbc | size 220 | symbol _ZN4Aska4ACSV12SetBlankBitsEPKhm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska4ACSV12SetBlankBitsEPKhm(long *param_1,long param_2,long param_3,long param_4)

{
  uint uVar1;
  long lVar2;
  long *plVar3;
  long lStack_38;
  
  plVar3 = (long *)(param_2 + 0x18);
  if ((*plVar3 != 0) && (*(char *)(param_2 + 0x28) != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_2 + 0x28) = 0;
  }
  *plVar3 = 0;
  *(undefined8 *)(param_2 + 0x20) = 0;
  Aska::ACSV::TermMemory(Aska::ACSV::WorkMemoryID)(param_2,1);
  Aska::ACSV::InitMemory(Aska::ACSV::WorkMemoryID, unsigned long)(&lStack_38,param_2,1,param_4 + 0x1fU >> 3 & 0x1ffffffffffffffc);
  if (-1 < lStack_38) {
    if ((uint)param_4 != 0) {
      uVar1 = 0;
      do {
        if ((1 << (ulong)(uVar1 & 7) & (uint)*(byte *)(param_3 + (ulong)(uVar1 >> 3))) != 0) {
          lVar2 = (ulong)(uVar1 >> 5) * 4;
          *(uint *)(*plVar3 + lVar2) = *(uint *)(*plVar3 + lVar2) | 1 << (ulong)(uVar1 & 0x1f);
        }
        uVar1 = uVar1 + 1;
      } while ((uint)param_4 != uVar1);
    }
    lStack_38 = 0;
  }
  *param_1 = lStack_38;
  return;
}

// ==== Aska::ACSV::DeserializeBinaryValues(void const*, unsigned long)
// vaddr 0x1efdc98 | ghidra 0x1ffdc98 | size 48 | symbol _ZN4Aska4ACSV23DeserializeBinaryValuesEPKvm | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska4ACSV23DeserializeBinaryValuesEPKvm(long param_1,long param_2,long param_3)

{
  undefined8 uVar1;
  
  uVar1 = 0xfffffffffffffc43;
  if ((param_2 != 0) && (param_3 != 0)) {
    if ((*(long *)(param_1 + 0x58) != 0) && (*(long *)(param_1 + 0x60) != 0)) {
      uVar1 = (*(code *)PTR__ZN4Aska4ACSV18UnpackBinaryValuesEPKvm_02cae688)(param_1);
      return uVar1;
    }
    uVar1 = 0xfffffffffffffc44;
  }
  return uVar1;
}

// ==== Aska::ACSV::SerializeBinary(Aska::IStream*) const
// vaddr 0x1efdcc8 | ghidra 0x1ffdcc8 | size 1116 | symbol _ZNK4Aska4ACSV15SerializeBinaryEPNS_7IStreamE | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

long _ZNK4Aska4ACSV15SerializeBinaryEPNS_7IStreamE(long param_1,long *param_2)

{
  uint uVar1;
  long lVar2;
  long lVar3;
  long lVar4;
  uint uVar5;
  ulong uVar6;
  ulong uVar7;
  long lVar8;
  ulong uVar9;
  long lVar10;
  long lVar11;
  ulong uVar12;
  ulong uVar13;
  undefined1 auStack_84 [4];
  undefined8 uStack_80;
  undefined8 uStack_78;
  undefined4 uStack_70;
  int iStack_6c;
  uint uStack_68;
  undefined4 uStack_64;
  
  if (((((*(long *)(param_1 + 0x58) == 0) || (*(long *)(param_1 + 0x60) == 0)) ||
       (*(long *)(param_1 + 0x38) == 0)) ||
      ((lVar8 = *(long *)(param_1 + 0x30), lVar8 == 0 ||
       (uVar6 = *(ulong *)(param_1 + 0x40), uVar6 == 0)))) ||
     (uVar7 = *(ulong *)(param_1 + 0x48), uVar7 == 0)) {
    lVar2 = -0x3bc;
  }
  else if (param_2 == (long *)0x0) {
    uVar13 = uVar6 + 0x2f & 0xfffffffffffffff0;
    if (((*(byte *)(param_1 + 0x50) & 1) != 0) && (*(int *)(param_1 + 0x24) != 0)) {
      uVar13 = ((uVar7 * uVar6 >> 3) + 0xf & 0x3ffffffffffffff0) + uVar13;
    }
    uVar12 = 0;
    lVar11 = 0;
    do {
      uVar9 = 0;
      do {
        lVar2 = 0;
        switch(*(undefined4 *)(*(long *)(param_1 + 0x38) + uVar9 * 4)) {
        case 0:
          break;
        case 1:
        case 2:
        case 3:
          lVar2 = 1;
          break;
        case 4:
        case 5:
          lVar2 = 2;
          break;
        case 6:
        case 7:
        case 10:
          lVar2 = 4;
          break;
        case 8:
        case 9:
        case 0xb:
          lVar2 = 8;
          break;
        case 0xc:
          lVar2 = *(long *)(lVar8 + 8) + 4;
          if (lVar2 < 0) goto code_r0x01ffe0dc;
          break;
        default:
          lVar2 = -1;
          goto code_r0x01ffe0dc;
        }
        uVar9 = uVar9 + 1;
        lVar11 = lVar2 + lVar11;
        lVar8 = lVar8 + 0x10;
      } while (uVar9 < uVar6);
      uVar12 = uVar12 + 1;
      lVar2 = lVar11;
    } while (uVar12 < uVar7);
code_r0x01ffe0dc:
    uVar6 = 0;
    if (-1 < lVar2) {
      uVar6 = uVar13;
    }
    lVar2 = uVar6 + lVar2;
  }
  else {
    iStack_6c = (int)uVar6;
    uStack_70 = 0x10001;
    uStack_64 = 0;
    uStack_78 = _UNK_0296d7b8;
    uStack_80 = _UNK_0296d7b0;
    uStack_68 = 0;
    if (((*(byte *)(param_1 + 0x50) & 1) != 0) && (uStack_68 = 0, *(int *)(param_1 + 0x24) != 0)) {
      uStack_68 = (int)uVar7 * iStack_6c;
    }
    lVar8 = ((uVar6 & 0xffffffff) + 0xf & 0x1fffffff0) + 0x20;
    if (uStack_68 != 0) {
      lVar8 = lVar8 + (ulong)((uStack_68 >> 3) + 0xf & 0x3ffffff0);
    }
    auStack_84[0] = 0;
    lVar2 = (**(code **)(*param_2 + 0x30))(param_2,auStack_84,1,lVar8);
    if ((lVar2 == lVar8) || (lVar2 = (**(code **)(*param_2 + 0x50))(param_2), -1 < lVar2)) {
      lVar11 = *(long *)(param_1 + 0x38);
      lVar2 = -0x3bc;
      if ((lVar11 != 0) &&
         (((lVar10 = *(long *)(param_1 + 0x30), lVar10 != 0 &&
           (uVar6 = *(ulong *)(param_1 + 0x40), uVar6 != 0)) &&
          (uVar7 = *(ulong *)(param_1 + 0x48), uVar7 != 0)))) {
        uVar13 = 0;
        lVar2 = 0;
        do {
          uVar12 = 0;
          do {
            lVar3 = Aska::ACSV::PackBinaryValue(Aska::ACSV::AValue const*, Aska::ACSV::Type, Aska::IStream*)(lVar10,*(undefined4 *)(lVar11 + uVar12 * 4),param_2);
            lVar4 = (**(code **)(*param_2 + 0x50))(param_2);
            if (lVar4 < 0) {
              return lVar4;
            }
            uVar12 = uVar12 + 1;
            lVar2 = lVar3 + lVar2;
            lVar10 = lVar10 + 0x10;
          } while (uVar12 < uVar6);
          lVar11 = *(long *)(param_1 + 0x38);
          uVar13 = uVar13 + 1;
        } while (uVar13 < uVar7);
        if (-1 < lVar2) {
          lVar8 = lVar2 + lVar8;
          uStack_80 = CONCAT44((int)lVar8,(undefined4)uStack_80);
          uStack_64 = (undefined4)lVar2;
          lVar2 = (**(code **)(*param_2 + 0x20))(param_2,0,0);
          if ((-1 < lVar2) &&
             ((lVar2 = (**(code **)(*param_2 + 0x30))(param_2,&uStack_80,4,8), lVar2 == 8 ||
              (lVar2 = (**(code **)(*param_2 + 0x50))(param_2), -1 < lVar2)))) {
            uVar6 = *(ulong *)(param_1 + 0x40);
            lVar2 = operator new[](unsigned long, std::nothrow_t const&)(uVar6,PTR__ZSt7nothrow_02cb9a80);
            if (lVar2 != 0) {
              if (uVar6 != 0) {
                lVar11 = *(long *)(param_1 + 0x38);
                uVar7 = 0;
                do {
                  *(char *)(lVar2 + uVar7) = (char)*(undefined4 *)(lVar11 + uVar7 * 4);
                  uVar7 = uVar7 + 1;
                } while (uVar7 < uVar6);
              }
              lVar11 = (**(code **)(*param_2 + 0x30))(param_2,lVar2,1,uVar6);
              if ((lVar11 != *(long *)(param_1 + 0x40)) &&
                 (lVar11 = (**(code **)(*param_2 + 0x50))(param_2), lVar11 < 0)) {
                operator delete[](void*)(lVar2);
                return lVar11;
              }
              operator delete[](void*)(lVar2);
              lVar2 = Aska::IStream::SeekAlign(Aska::IStream*, unsigned long, long)(param_2,0x10,0);
              uVar1 = uStack_68;
              if (lVar2 < 0) {
                return lVar2;
              }
              if (uStack_68 == 0) {
                return lVar8;
              }
              uVar6 = (ulong)(uStack_68 >> 3);
              lVar2 = operator new[](unsigned long, std::nothrow_t const&)(uVar6,PTR__ZSt7nothrow_02cb9a80);
              if (lVar2 != 0) {
                memset(lVar2,0,uVar6);
                lVar11 = *(long *)(param_1 + 0x18);
                uVar5 = 0;
                do {
                  if ((*(uint *)(lVar11 + (ulong)(uVar5 >> 5) * 4) & 1 << (ulong)(uVar5 & 0x1f)) !=
                      0) {
                    *(byte *)(lVar2 + (ulong)(uVar5 >> 3)) =
                         (byte)(1 << (ulong)(uVar5 & 7)) | *(byte *)(lVar2 + (ulong)(uVar5 >> 3));
                  }
                  uVar5 = uVar5 + 1;
                } while (uVar5 < uVar1);
                uVar7 = (**(code **)(*param_2 + 0x30))(param_2,lVar2,1,uVar6);
                if ((uVar7 != uVar6) &&
                   (lVar11 = (**(code **)(*param_2 + 0x50))(param_2), lVar11 < 0)) {
                  operator delete[](void*)(lVar2);
                  return lVar11;
                }
                operator delete[](void*)(lVar2);
                return lVar8;
              }
            }
            lVar2 = -0x3bf;
          }
        }
      }
    }
  }
  return lVar2;
}

// ==== Aska::ACSV::SerializeBinary(void*, unsigned long, Aska::Machine::Endian) const
// vaddr 0x1efe124 | ghidra 0x1ffe124 | size 1384 | symbol _ZNK4Aska4ACSV15SerializeBinaryEPvmNS_7Machine6EndianE | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK4Aska4ACSV15SerializeBinaryEPvmNS_7Machine6EndianE
               (long param_1,long param_2,long param_3,byte param_4)

{
  int iVar1;
  char cVar2;
  bool bVar3;
  undefined *puVar4;
  undefined *puVar5;
  undefined *puVar6;
  long lVar7;
  ulong uVar8;
  ulong uVar9;
  ulong uVar10;
  ulong uVar11;
  long lVar12;
  ulong uVar13;
  long lVar14;
  undefined *puStack_540;
  long *plStack_538;
  int *piStack_530;
  undefined **ppuStack_528;
  undefined8 uStack_520;
  byte bStack_518;
  undefined *puStack_510;
  undefined4 auStack_508 [2];
  undefined8 uStack_500;
  undefined8 uStack_4e0;
  undefined8 uStack_4d8;
  undefined *puStack_4c8;
  undefined4 auStack_4c0 [2];
  undefined8 uStack_4b8;
  undefined8 uStack_498;
  undefined8 uStack_490;
  undefined *puStack_480;
  undefined4 auStack_478 [2];
  undefined8 uStack_470;
  undefined8 uStack_450;
  undefined8 uStack_448;
  undefined *puStack_438;
  undefined4 auStack_430 [2];
  undefined8 uStack_428;
  undefined8 uStack_408;
  undefined8 uStack_400;
  undefined *puStack_3f0;
  undefined4 auStack_3e8 [2];
  undefined8 uStack_3e0;
  undefined8 uStack_3c0;
  undefined8 uStack_3b8;
  undefined *puStack_3a8;
  undefined4 auStack_3a0 [2];
  undefined8 uStack_398;
  undefined8 uStack_378;
  undefined8 uStack_370;
  undefined *puStack_360;
  undefined4 auStack_358 [2];
  undefined8 uStack_350;
  undefined8 uStack_330;
  undefined8 uStack_328;
  undefined *puStack_318;
  undefined4 auStack_310 [2];
  undefined8 uStack_308;
  undefined8 uStack_2e8;
  undefined8 uStack_2e0;
  undefined *puStack_2d0;
  undefined4 auStack_2c8 [2];
  undefined8 uStack_2c0;
  undefined8 uStack_2a0;
  undefined8 uStack_298;
  undefined *puStack_288;
  undefined4 auStack_280 [2];
  undefined8 uStack_278;
  undefined8 uStack_258;
  undefined8 uStack_250;
  undefined *puStack_240;
  undefined4 auStack_238 [2];
  undefined8 uStack_230;
  undefined8 uStack_210;
  undefined8 uStack_208;
  undefined *puStack_1f8;
  undefined4 auStack_1f0 [2];
  undefined8 uStack_1e8;
  undefined8 uStack_1c8;
  undefined8 uStack_1c0;
  undefined *puStack_1b0;
  undefined4 auStack_1a8 [2];
  undefined8 uStack_1a0;
  undefined8 uStack_180;
  undefined8 uStack_178;
  undefined *puStack_168;
  undefined4 auStack_160 [2];
  undefined8 uStack_158;
  undefined8 uStack_138;
  undefined8 uStack_130;
  undefined *puStack_120;
  undefined4 auStack_118 [2];
  undefined8 uStack_110;
  undefined8 uStack_f0;
  undefined8 uStack_e8;
  undefined *puStack_d8;
  undefined4 auStack_d0 [2];
  undefined8 uStack_c8;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined *puStack_90;
  long lStack_88;
  int *piStack_80;
  long lStack_78;
  int *piStack_70;
  undefined8 uStack_68;
  
  puVar5 = PTR__ZTVN4Aska12StaticStreamE_02cba478;
  if ((*(long *)(param_1 + 0x58) == 0) || (*(long *)(param_1 + 0x60) == 0)) {
    return -0x3bc;
  }
  if ((param_2 == 0) && (param_3 == 0)) {
    if (*(long *)(param_1 + 0x38) == 0) {
      return -0x3bc;
    }
    lVar7 = *(long *)(param_1 + 0x30);
    if (lVar7 == 0) {
      return -0x3bc;
    }
    uVar8 = *(ulong *)(param_1 + 0x40);
    if (uVar8 == 0) {
      return -0x3bc;
    }
    uVar10 = *(ulong *)(param_1 + 0x48);
    if (uVar10 == 0) {
      return -0x3bc;
    }
    uVar9 = uVar8 + 0x2f & 0xfffffffffffffff0;
    if (((*(byte *)(param_1 + 0x50) & 1) != 0) && (*(int *)(param_1 + 0x24) != 0)) {
      uVar9 = ((uVar10 * uVar8 >> 3) + 0xf & 0x3ffffffffffffff0) + uVar9;
    }
    uVar11 = 0;
    lVar12 = 0;
    do {
      uVar13 = 0;
      do {
        lVar14 = 0;
        switch(*(undefined4 *)(*(long *)(param_1 + 0x38) + uVar13 * 4)) {
        case 0:
          break;
        case 1:
        case 2:
        case 3:
          lVar14 = 1;
          break;
        case 4:
        case 5:
          lVar14 = 2;
          break;
        case 6:
        case 7:
        case 10:
          lVar14 = 4;
          break;
        case 8:
        case 9:
        case 0xb:
          lVar14 = 8;
          break;
        case 0xc:
          lVar14 = *(long *)(lVar7 + 8) + 4;
          if (lVar14 < 0) goto code_r0x01ffe67c;
          break;
        default:
          lVar14 = -1;
          goto code_r0x01ffe67c;
        }
        uVar13 = uVar13 + 1;
        lVar12 = lVar14 + lVar12;
        lVar7 = lVar7 + 0x10;
      } while (uVar13 < uVar8);
      uVar11 = uVar11 + 1;
      lVar14 = lVar12;
    } while (uVar11 < uVar10);
code_r0x01ffe67c:
    uVar8 = 0;
    if (-1 < lVar14) {
      uVar8 = uVar9;
    }
    return uVar8 + lVar14;
  }
  if (param_2 == 0) {
    return -0x3bd;
  }
  if (param_3 == 0) {
    return -0x3bd;
  }
  puStack_90 = PTR__ZTVN4Aska12StaticStreamE_02cba478 + 0x10;
  uStack_68 = 0;
  piStack_70 = (int *)0x0;
  lStack_78 = 0;
  piStack_80 = (int *)0x0;
  lStack_88 = 0;
  Aska::StaticStream::Open(signed char const*, unsigned long)(&puStack_90);
  puVar6 = PTR__ZTVN4Aska15ByteOrderStream13NotifyWrapperE_02cbf2f0;
  puVar4 = PTR__ZTVN4Aska15ByteOrderStreamE_02cb98d0;
  plStack_538 = (long *)0x0;
  piStack_530 = (int *)0x0;
  uStack_520 = 0;
  puStack_540 = PTR__ZTVN4Aska15ByteOrderStreamE_02cb98d0 + 0x10;
  puStack_510 = PTR__ZTVN4Aska15ByteOrderStream13NotifyWrapperE_02cbf2f0 + 0x10;
  uStack_500 = 0;
  uStack_4e0 = 0;
  uStack_4d8 = 0;
  do {
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(auStack_508,0x10);
    if (bVar3) {
      auStack_508[0] = 0;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
  puStack_4c8 = PTR__ZTVN4Aska15ByteOrderStream13NotifyWrapperE_02cbf2f0 + 0x10;
  uStack_4b8 = 0;
  uStack_498 = 0;
  uStack_490 = 0;
  do {
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(auStack_4c0,0x10);
    if (bVar3) {
      auStack_4c0[0] = 0;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
  puStack_480 = PTR__ZTVN4Aska15ByteOrderStream13NotifyWrapperE_02cbf2f0 + 0x10;
  uStack_470 = 0;
  uStack_450 = 0;
  uStack_448 = 0;
  do {
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(auStack_478,0x10);
    if (bVar3) {
      auStack_478[0] = 0;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
  puStack_438 = PTR__ZTVN4Aska15ByteOrderStream13NotifyWrapperE_02cbf2f0 + 0x10;
  uStack_428 = 0;
  uStack_408 = 0;
  uStack_400 = 0;
  do {
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(auStack_430,0x10);
    if (bVar3) {
      auStack_430[0] = 0;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
  puStack_3f0 = PTR__ZTVN4Aska15ByteOrderStream13NotifyWrapperE_02cbf2f0 + 0x10;
  uStack_3e0 = 0;
  uStack_3c0 = 0;
  uStack_3b8 = 0;
  do {
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(auStack_3e8,0x10);
    if (bVar3) {
      auStack_3e8[0] = 0;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
  puStack_3a8 = PTR__ZTVN4Aska15ByteOrderStream13NotifyWrapperE_02cbf2f0 + 0x10;
  uStack_398 = 0;
  uStack_378 = 0;
  uStack_370 = 0;
  do {
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(auStack_3a0,0x10);
    if (bVar3) {
      auStack_3a0[0] = 0;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
  puStack_360 = PTR__ZTVN4Aska15ByteOrderStream13NotifyWrapperE_02cbf2f0 + 0x10;
  uStack_350 = 0;
  uStack_328 = 0;
  uStack_330 = 0;
  do {
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(auStack_358,0x10);
    if (bVar3) {
      auStack_358[0] = 0;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
  puStack_318 = PTR__ZTVN4Aska15ByteOrderStream13NotifyWrapperE_02cbf2f0 + 0x10;
  uStack_308 = 0;
  uStack_2e0 = 0;
  uStack_2e8 = 0;
  do {
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(auStack_310,0x10);
    if (bVar3) {
      auStack_310[0] = 0;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
  puStack_2d0 = PTR__ZTVN4Aska15ByteOrderStream13NotifyWrapperE_02cbf2f0 + 0x10;
  uStack_2c0 = 0;
  uStack_298 = 0;
  uStack_2a0 = 0;
  do {
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(auStack_2c8,0x10);
    if (bVar3) {
      auStack_2c8[0] = 0;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
  puStack_288 = PTR__ZTVN4Aska15ByteOrderStream13NotifyWrapperE_02cbf2f0 + 0x10;
  uStack_278 = 0;
  uStack_250 = 0;
  uStack_258 = 0;
  do {
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(auStack_280,0x10);
    if (bVar3) {
      auStack_280[0] = 0;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
  puStack_240 = PTR__ZTVN4Aska15ByteOrderStream13NotifyWrapperE_02cbf2f0 + 0x10;
  uStack_230 = 0;
  uStack_208 = 0;
  uStack_210 = 0;
  do {
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(auStack_238,0x10);
    if (bVar3) {
      auStack_238[0] = 0;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
  puStack_1f8 = PTR__ZTVN4Aska15ByteOrderStream13NotifyWrapperE_02cbf2f0 + 0x10;
  uStack_1e8 = 0;
  uStack_1c0 = 0;
  uStack_1c8 = 0;
  do {
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(auStack_1f0,0x10);
    if (bVar3) {
      auStack_1f0[0] = 0;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
  puStack_1b0 = PTR__ZTVN4Aska15ByteOrderStream13NotifyWrapperE_02cbf2f0 + 0x10;
  uStack_1a0 = 0;
  uStack_178 = 0;
  uStack_180 = 0;
  do {
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(auStack_1a8,0x10);
    if (bVar3) {
      auStack_1a8[0] = 0;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
  puStack_168 = PTR__ZTVN4Aska15ByteOrderStream13NotifyWrapperE_02cbf2f0 + 0x10;
  uStack_158 = 0;
  uStack_130 = 0;
  uStack_138 = 0;
  do {
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(auStack_160,0x10);
    if (bVar3) {
      auStack_160[0] = 0;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
  puStack_120 = PTR__ZTVN4Aska15ByteOrderStream13NotifyWrapperE_02cbf2f0 + 0x10;
  uStack_110 = 0;
  uStack_e8 = 0;
  uStack_f0 = 0;
  do {
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(auStack_118,0x10);
    if (bVar3) {
      auStack_118[0] = 0;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
  puStack_d8 = PTR__ZTVN4Aska15ByteOrderStream13NotifyWrapperE_02cbf2f0 + 0x10;
  uStack_c8 = 0;
  uStack_a0 = 0;
  uStack_a8 = 0;
  do {
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(auStack_d0,0x10);
    if (bVar3) {
      auStack_d0[0] = 0;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
  bStack_518 = ~param_4 & 1;
  ppuStack_528 = &puStack_90;
  lVar7 = Aska::ACSV::SerializeBinary(Aska::IStream*) const(param_1,&puStack_540);
  puStack_540 = puVar4 + 0x10;
  if (((ppuStack_528 != (undefined **)0x0) &&
      (uVar8 = (**(code **)(*ppuStack_528 + 0x68))(ppuStack_528), (uVar8 & 1) != 0)) &&
     (ppuStack_528 != (undefined **)0x0)) {
    (**(code **)(*ppuStack_528 + 0x78))(ppuStack_528,0xffffffff);
  }
  puStack_510 = puVar6 + 0x10;
  puStack_540 = PTR__ZTVN4Aska14ExtendedStreamE_02cb7e70 + 0x10;
  puStack_4c8 = puStack_510;
  puStack_480 = puStack_510;
  puStack_438 = puStack_510;
  puStack_3f0 = puStack_510;
  puStack_3a8 = puStack_510;
  puStack_360 = puStack_510;
  puStack_318 = puStack_510;
  puStack_2d0 = puStack_510;
  puStack_288 = puStack_510;
  puStack_240 = puStack_510;
  puStack_1f8 = puStack_510;
  puStack_1b0 = puStack_510;
  puStack_168 = puStack_510;
  puStack_120 = puStack_510;
  puStack_d8 = puStack_510;
  if (piStack_530 == (int *)0x0) {
code_r0x01ffe5d4:
    if (plStack_538 != (long *)0x0) {
      (**(code **)(*plStack_538 + 8))();
    }
    if (piStack_530 != (int *)0x0) {
      Aska::TSharedPointerCode::DeleteCounter(int*)();
    }
  }
  else {
    do {
      iVar1 = *piStack_530;
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piStack_530,0x10);
      if (bVar3) {
        *piStack_530 = iVar1 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    if (iVar1 + -1 == 0) goto code_r0x01ffe5d4;
  }
  puStack_90 = puVar5 + 0x10;
  plStack_538 = (long *)0x0;
  if (piStack_70 != (int *)0x0) {
    do {
      iVar1 = *piStack_70;
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piStack_70,0x10);
      if (bVar3) {
        *piStack_70 = iVar1 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    if (iVar1 + -1 != 0) goto code_r0x01ffe634;
  }
  if (lStack_78 != 0) {
    operator delete[](void*)();
  }
  if (piStack_70 != (int *)0x0) {
    Aska::TSharedPointerCode::DeleteCounter(int*)();
  }
code_r0x01ffe634:
  piStack_70 = (int *)0x0;
  lStack_78 = 0;
  if (piStack_80 != (int *)0x0) {
    do {
      iVar1 = *piStack_80;
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piStack_80,0x10);
      if (bVar3) {
        *piStack_80 = iVar1 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    if (iVar1 + -1 != 0) {
      return lVar7;
    }
  }
  if (lStack_88 != 0) {
    operator delete[](void*)();
  }
  if (piStack_80 != (int *)0x0) {
    Aska::TSharedPointerCode::DeleteCounter(int*)();
    return lVar7;
  }
  return lVar7;
}

// ==== Aska::ACSV::DeserializeText(void const*, unsigned long)
// vaddr 0x1efe778 | ghidra 0x1ffe778 | size 424 | symbol _ZN4Aska4ACSV15DeserializeTextEPKvm | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska4ACSV15DeserializeTextEPKvm(long param_1,long param_2,long param_3)

{
  undefined1 auVar1 [16];
  undefined1 auVar2 [16];
  ulong uVar3;
  long lVar4;
  undefined1 *puVar5;
  long *plVar6;
  long lStack_300;
  undefined1 auStack_2f8 [128];
  long lStack_278;
  long lStack_270;
  undefined1 *puStack_268;
  ulong uStack_260;
  long *plStack_258;
  long lStack_250;
  long lStack_248;
  ulong *puStack_240;
  ulong uStack_48;
  
  if (param_2 == 0) {
    return -0x3bd;
  }
  if (param_3 == 0) {
    return -0x3bd;
  }
  if ((*(long *)(param_1 + 0x58) == 0) || (*(long *)(param_1 + 0x60) == 0)) {
    return -0x3bc;
  }
  puStack_240 = &uStack_48;
  uStack_48 = 0;
  lStack_250 = param_2;
  lStack_248 = param_3;
  lVar4 = long Aska::ACSV::UnpackTextValues<0, Aska::ACSV::UnpackColumnNumArgs>(Aska::ACSV::UnpackColumnNumArgs const*)(param_1,&lStack_250);
  uVar3 = uStack_48;
  if (lVar4 < 0) {
    return lVar4;
  }
  if (uStack_48 == 0) {
    return -0x3c8;
  }
  if (uStack_48 < 0x21) {
    puVar5 = auStack_2f8;
    plVar6 = &lStack_250;
  }
  else {
    auVar1._8_8_ = 0;
    auVar1._0_8_ = uStack_48;
    lVar4 = uStack_48 << 2;
    if (SUB168(auVar1 * ZEXT816(4),8) != 0) {
      lVar4 = -1;
    }
    puVar5 = (undefined1 *)operator new[](unsigned long, std::nothrow_t const&)(lVar4,PTR__ZSt7nothrow_02cb9a80);
    if (puVar5 == (undefined1 *)0x0) {
      return -0x3bf;
    }
    auVar2._8_8_ = 0;
    auVar2._0_8_ = uVar3;
    lVar4 = uVar3 << 4;
    if (SUB168(auVar2 * ZEXT816(0x10),8) != 0) {
      lVar4 = -1;
    }
    plVar6 = (long *)operator new[](unsigned long, std::nothrow_t const&)(lVar4,PTR__ZSt7nothrow_02cb9a80);
    if (plVar6 == (long *)0x0) {
      lVar4 = -0x3bf;
      goto code_r0x01ffe908;
    }
  }
  uStack_260 = uVar3;
  lStack_278 = param_2;
  lStack_270 = param_3;
  puStack_268 = puVar5;
  plStack_258 = plVar6;
  lVar4 = long Aska::ACSV::UnpackTextValues<1, Aska::ACSV::UnpackTypeArgs>(Aska::ACSV::UnpackTypeArgs const*)(param_1,&lStack_278);
  if ((plVar6 != &lStack_250) && (plVar6 != (long *)0x0)) {
    operator delete[](void*)(plVar6);
  }
  if ((-1 < lVar4) &&
     (Aska::ACSV::SetTypes(Aska::ACSV::Type const*, unsigned long)(&lStack_300,param_1,puVar5,uStack_48), lVar4 = lStack_300, -1 < lStack_300)) {
    if ((*(long *)(param_1 + 0x58) == 0) || (*(long *)(param_1 + 0x60) == 0)) {
      lVar4 = -0x3bc;
    }
    else {
      lStack_250 = param_2;
      lStack_248 = param_3;
      lVar4 = long Aska::ACSV::UnpackTextValues<2, Aska::ACSV::UnpackValueArgs>(Aska::ACSV::UnpackValueArgs const*)(param_1,&lStack_250);
    }
  }
code_r0x01ffe908:
  if (puVar5 != auStack_2f8) {
    operator delete[](void*)(puVar5);
  }
  return lVar4;
}

// ==== Aska::ACSV::AnalyzeTextColumnNum(void const*, unsigned long, unsigned long*)
// vaddr 0x1efe920 | ghidra 0x1ffe920 | size 64 | symbol _ZN4Aska4ACSV20AnalyzeTextColumnNumEPKvmPm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska4ACSV20AnalyzeTextColumnNumEPKvmPm
               (ulong *param_1,undefined8 param_2,long param_3,long param_4,long param_5)

{
  ulong uVar1;
  long lStack_28;
  long lStack_20;
  long lStack_18;
  
  uVar1 = 0xfffffffffffffc43;
  if (((param_3 != 0) && (param_4 != 0)) && (param_5 != 0)) {
    lStack_28 = param_3;
    lStack_20 = param_4;
    lStack_18 = param_5;
    uVar1 = long Aska::ACSV::UnpackTextValues<0, Aska::ACSV::UnpackColumnNumArgs>(Aska::ACSV::UnpackColumnNumArgs const*)(param_2,&lStack_28);
    uVar1 = uVar1 & (long)uVar1 >> 0x3f;
  }
  *param_1 = uVar1;
  return;
}

// ==== Aska::ACSV::AnalyzeTextTypes(void const*, unsigned long, Aska::ACSV::Type*, unsigned long)
// vaddr 0x1efe960 | ghidra 0x1ffe960 | size 228 | symbol _ZN4Aska4ACSV16AnalyzeTextTypesEPKvmPNS0_4TypeEm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska4ACSV16AnalyzeTextTypesEPKvmPNS0_4TypeEm
               (ulong *param_1,undefined8 param_2,long param_3,long param_4,long param_5,
               ulong param_6)

{
  undefined1 auVar1 [16];
  undefined1 *puVar2;
  ulong uVar3;
  long lVar4;
  long lStack_278;
  long lStack_270;
  long lStack_268;
  ulong uStack_260;
  undefined1 *puStack_258;
  undefined1 auStack_250 [512];
  
  if ((((param_3 == 0) || (param_4 == 0)) || (param_5 == 0)) || (param_6 == 0)) {
    uVar3 = 0xfffffffffffffc43;
  }
  else {
    if (param_6 < 0x21) {
      puVar2 = auStack_250;
    }
    else {
      auVar1._8_8_ = 0;
      auVar1._0_8_ = param_6;
      lVar4 = param_6 << 4;
      if (SUB168(auVar1 * ZEXT816(0x10),8) != 0) {
        lVar4 = -1;
      }
      puVar2 = (undefined1 *)operator new[](unsigned long, std::nothrow_t const&)(lVar4,PTR__ZSt7nothrow_02cb9a80);
      if (puVar2 == (undefined1 *)0x0) {
        uVar3 = 0xfffffffffffffc41;
        goto code_r0x01ffea24;
      }
    }
    lStack_278 = param_3;
    lStack_270 = param_4;
    lStack_268 = param_5;
    uStack_260 = param_6;
    puStack_258 = puVar2;
    uVar3 = long Aska::ACSV::UnpackTextValues<1, Aska::ACSV::UnpackTypeArgs>(Aska::ACSV::UnpackTypeArgs const*)(param_2,&lStack_278);
    if ((puVar2 != auStack_250) && (puVar2 != (undefined1 *)0x0)) {
      operator delete[](void*)(puVar2);
    }
    uVar3 = uVar3 & (long)uVar3 >> 0x3f;
  }
code_r0x01ffea24:
  *param_1 = uVar3;
  return;
}

// ==== Aska::ACSV::DeserializeTextValues(void const*, unsigned long)
// vaddr 0x1efea44 | ghidra 0x1ffea44 | size 84 | symbol _ZN4Aska4ACSV21DeserializeTextValuesEPKvm | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska4ACSV21DeserializeTextValuesEPKvm(long param_1,long param_2,long param_3)

{
  undefined8 uVar1;
  long lStack_20;
  long lStack_18;
  
  uVar1 = 0xfffffffffffffc43;
  if ((param_2 != 0) && (param_3 != 0)) {
    if (*(long *)(param_1 + 0x58) == 0) {
      return 0xfffffffffffffc44;
    }
    if (*(long *)(param_1 + 0x60) == 0) {
      return 0xfffffffffffffc44;
    }
    lStack_20 = param_2;
    lStack_18 = param_3;
    uVar1 = long Aska::ACSV::UnpackTextValues<2, Aska::ACSV::UnpackValueArgs>(Aska::ACSV::UnpackValueArgs const*)(param_1,&lStack_20);
  }
  return uVar1;
}

// ==== Aska::ACSV::SerializeText(void*, unsigned long) const
// vaddr 0x1efea98 | ghidra 0x1ffea98 | size 456 | symbol _ZNK4Aska4ACSV13SerializeTextEPvm | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK4Aska4ACSV13SerializeTextEPvm(long param_1,long param_2,long param_3)

{
  long lVar1;
  ulong uVar2;
  ulong uVar3;
  ulong uVar4;
  long lVar5;
  long lVar6;
  ulong uVar7;
  ulong uVar8;
  ulong uVar9;
  
  if ((*(long *)(param_1 + 0x58) == 0) || (*(long *)(param_1 + 0x60) == 0)) {
    return -0x3bc;
  }
  if ((param_2 != 0) || (param_3 != 0)) {
    if (param_2 == 0) {
      return -0x3bd;
    }
    if (param_3 == 0) {
      return -0x3bd;
    }
    if ((*(byte *)(param_1 + 0x50) >> 1 & 1) == 0) {
      lVar5 = long Aska::ACSV::PackTextValues<1, false>(char*, unsigned long)(param_1,param_2,param_3);
    }
    else {
      lVar5 = long Aska::ACSV::PackTextValues<1, true>(char*, unsigned long)(param_1,param_2,param_3);
    }
    if (lVar5 < 0) {
      return lVar5;
    }
    if (param_3 < lVar5) {
      return -0x3b1;
    }
    *(undefined1 *)(param_2 + lVar5) = 0;
    return lVar5 + 1;
  }
  lVar5 = *(long *)(param_1 + 0x30);
  lVar6 = *(long *)(param_1 + 0x38);
  uVar2 = *(ulong *)(param_1 + 0x40);
  uVar3 = *(ulong *)(param_1 + 0x48);
  if ((*(byte *)(param_1 + 0x50) >> 1 & 1) == 0) {
    if (((lVar6 != 0 && lVar5 != 0) && uVar2 != 0) && uVar3 != 0) {
      uVar8 = 0;
      uVar7 = 0;
      do {
        uVar9 = 0;
        do {
          uVar4 = long Aska::ACSV::CalcSizeTextValue<false>(Aska::ACSV::AValue const*, Aska::ACSV::Type)(lVar5,*(undefined4 *)(lVar6 + uVar9 * 4));
          if ((long)uVar4 < 0) goto code_r0x01ffec24;
          lVar1 = 1;
          if (uVar2 - 1 <= uVar9) {
            lVar1 = 2;
          }
          uVar9 = uVar9 + 1;
          uVar4 = uVar4 + lVar1;
          uVar7 = uVar4 + uVar7;
          lVar5 = lVar5 + 0x10;
        } while (uVar9 < uVar2);
        lVar6 = *(long *)(param_1 + 0x38);
        uVar8 = uVar8 + 1;
      } while (uVar8 < uVar3);
code_r0x01ffec24:
      if (-1 < (long)uVar4) {
        uVar4 = uVar7;
      }
      goto code_r0x01ffec2c;
    }
  }
  else if (((lVar6 != 0 && lVar5 != 0) && uVar2 != 0) && uVar3 != 0) {
    uVar8 = 0;
    uVar7 = 0;
    do {
      uVar9 = 0;
      do {
        uVar4 = long Aska::ACSV::CalcSizeTextValue<true>(Aska::ACSV::AValue const*, Aska::ACSV::Type)(lVar5,*(undefined4 *)(lVar6 + uVar9 * 4));
        if ((long)uVar4 < 0) goto code_r0x01ffec24;
        lVar1 = 1;
        if (uVar2 - 1 <= uVar9) {
          lVar1 = 2;
        }
        uVar9 = uVar9 + 1;
        uVar4 = uVar4 + lVar1;
        uVar7 = uVar4 + uVar7;
        lVar5 = lVar5 + 0x10;
      } while (uVar9 < uVar2);
      lVar6 = *(long *)(param_1 + 0x38);
      uVar8 = uVar8 + 1;
    } while (uVar8 < uVar3);
    goto code_r0x01ffec24;
  }
  uVar4 = 0xfffffffffffffc44;
code_r0x01ffec2c:
  return (uVar4 >> 0x3f ^ 1) + uVar4;
}

// ==== long Aska::ACSV::PackTextValues<1, true>(char*, unsigned long)
// vaddr 0x1efec60 | ghidra 0x1ffec60 | size 300 | symbol _ZN4Aska4ACSV14PackTextValuesILi1ELb1EEElPcm | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska4ACSV14PackTextValuesILi1ELb1EEElPcm(long param_1,long param_2,long param_3)

{
  undefined2 *puVar1;
  long lVar2;
  ulong uVar3;
  long lVar4;
  long lVar5;
  long lVar6;
  ulong uVar7;
  ulong uVar8;
  ulong uVar9;
  ulong uVar10;
  
  lVar6 = *(long *)(param_1 + 0x38);
  lVar2 = -0x3bc;
  if ((((lVar6 != 0) && (lVar4 = *(long *)(param_1 + 0x30), lVar4 != 0)) &&
      (uVar7 = *(ulong *)(param_1 + 0x40), uVar7 != 0)) &&
     (uVar8 = *(ulong *)(param_1 + 0x48), uVar8 != 0)) {
    uVar9 = 0;
    lVar5 = 0;
    do {
      uVar10 = 0;
      do {
        lVar2 = long Aska::ACSV::PackTextValue<true>(Aska::ACSV::AValue const*, Aska::ACSV::Type, char*, unsigned long)(lVar4,*(undefined4 *)(lVar6 + uVar10 * 4),param_2,param_3 - lVar5);
        if (lVar2 < 0) goto code_r0x01ffed68;
        lVar5 = lVar2 + lVar5;
        puVar1 = (undefined2 *)(param_2 + lVar2);
        uVar3 = (param_3 - lVar5) - lVar2;
        if (uVar10 < uVar7 - 1) {
          if (uVar3 == 1) {
            raise(5);
          }
          else {
            if (param_3 - lVar5 == lVar2) goto code_r0x01ffed64;
            *puVar1 = 0x2c;
          }
          lVar2 = 1;
        }
        else {
          if (uVar3 < 2) {
code_r0x01ffed64:
            lVar2 = -0x3c1;
            goto code_r0x01ffed68;
          }
          if (uVar3 == 2) {
            raise(5);
          }
          else {
            *puVar1 = 0xa0d;
            *(undefined1 *)(puVar1 + 1) = 0;
          }
          lVar2 = 2;
        }
        uVar10 = uVar10 + 1;
        lVar5 = lVar2 + lVar5;
        param_2 = (long)puVar1 + lVar2;
        lVar4 = lVar4 + 0x10;
      } while (uVar10 < uVar7);
      lVar6 = *(long *)(param_1 + 0x38);
      uVar9 = uVar9 + 1;
    } while (uVar9 < uVar8);
code_r0x01ffed68:
    if (-1 < lVar2) {
      lVar2 = lVar5;
    }
  }
  return lVar2;
}

// ==== long Aska::ACSV::PackTextValues<1, false>(char*, unsigned long)
// vaddr 0x1efed8c | ghidra 0x1ffed8c | size 300 | symbol _ZN4Aska4ACSV14PackTextValuesILi1ELb0EEElPcm | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska4ACSV14PackTextValuesILi1ELb0EEElPcm(long param_1,long param_2,long param_3)

{
  undefined2 *puVar1;
  long lVar2;
  ulong uVar3;
  long lVar4;
  long lVar5;
  long lVar6;
  ulong uVar7;
  ulong uVar8;
  ulong uVar9;
  ulong uVar10;
  
  lVar6 = *(long *)(param_1 + 0x38);
  lVar2 = -0x3bc;
  if ((((lVar6 != 0) && (lVar4 = *(long *)(param_1 + 0x30), lVar4 != 0)) &&
      (uVar7 = *(ulong *)(param_1 + 0x40), uVar7 != 0)) &&
     (uVar8 = *(ulong *)(param_1 + 0x48), uVar8 != 0)) {
    uVar9 = 0;
    lVar5 = 0;
    do {
      uVar10 = 0;
      do {
        lVar2 = long Aska::ACSV::PackTextValue<false>(Aska::ACSV::AValue const*, Aska::ACSV::Type, char*, unsigned long)(lVar4,*(undefined4 *)(lVar6 + uVar10 * 4),param_2,param_3 - lVar5);
        if (lVar2 < 0) goto code_r0x01ffee94;
        lVar5 = lVar2 + lVar5;
        puVar1 = (undefined2 *)(param_2 + lVar2);
        uVar3 = (param_3 - lVar5) - lVar2;
        if (uVar10 < uVar7 - 1) {
          if (uVar3 == 1) {
            raise(5);
          }
          else {
            if (param_3 - lVar5 == lVar2) goto code_r0x01ffee90;
            *puVar1 = 0x2c;
          }
          lVar2 = 1;
        }
        else {
          if (uVar3 < 2) {
code_r0x01ffee90:
            lVar2 = -0x3c1;
            goto code_r0x01ffee94;
          }
          if (uVar3 == 2) {
            raise(5);
          }
          else {
            *puVar1 = 0xa0d;
            *(undefined1 *)(puVar1 + 1) = 0;
          }
          lVar2 = 2;
        }
        uVar10 = uVar10 + 1;
        lVar5 = lVar2 + lVar5;
        param_2 = (long)puVar1 + lVar2;
        lVar4 = lVar4 + 0x10;
      } while (uVar10 < uVar7);
      lVar6 = *(long *)(param_1 + 0x38);
      uVar9 = uVar9 + 1;
    } while (uVar9 < uVar8);
code_r0x01ffee94:
    if (-1 < lVar2) {
      lVar2 = lVar5;
    }
  }
  return lVar2;
}

// ==== Aska::ACSV::GetValue(Aska::ACSV::Type, unsigned long, unsigned long, void*) const
// vaddr 0x1efeeb8 | ghidra 0x1ffeeb8 | size 232 | symbol _ZNK4Aska4ACSV8GetValueENS0_4TypeEmmPv | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZNK4Aska4ACSV8GetValueENS0_4TypeEmmPv
          (long param_1,undefined4 param_2,ulong param_3,ulong param_4,undefined8 *param_5)

{
  undefined8 *puVar1;
  undefined8 uVar2;
  ulong uVar3;
  
  uVar3 = *(ulong *)(param_1 + 0x40);
  if (param_3 < uVar3) {
    uVar2 = 0;
    if ((param_5 != (undefined8 *)0x0) && (param_4 < *(ulong *)(param_1 + 0x48))) {
      switch(param_2) {
      case 0:
        *param_5 = 0;
        break;
      case 1:
      case 2:
      case 3:
        *(undefined1 *)param_5 =
             *(undefined1 *)(*(long *)(param_1 + 0x30) + (param_3 + uVar3 * param_4) * 0x10);
        break;
      case 4:
      case 5:
        *(undefined2 *)param_5 =
             *(undefined2 *)(*(long *)(param_1 + 0x30) + (param_3 + uVar3 * param_4) * 0x10);
        break;
      case 6:
      case 7:
      case 10:
        *(undefined4 *)param_5 =
             *(undefined4 *)(*(long *)(param_1 + 0x30) + (param_3 + uVar3 * param_4) * 0x10);
        break;
      case 8:
      case 9:
      case 0xb:
        *param_5 = *(undefined8 *)(*(long *)(param_1 + 0x30) + (param_3 + uVar3 * param_4) * 0x10);
        break;
      case 0xc:
        puVar1 = (undefined8 *)(*(long *)(param_1 + 0x30) + (param_3 + uVar3 * param_4) * 0x10);
        uVar2 = *puVar1;
        param_5[1] = puVar1[1];
        *param_5 = uVar2;
        break;
      default:
        return 0;
      }
      uVar2 = 1;
    }
    return uVar2;
  }
  return 0;
}

// ==== Aska::ACSV::SetValue(Aska::ACSV::Type, unsigned long, unsigned long, void const*)
// vaddr 0x1efefa0 | ghidra 0x1ffefa0 | size 236 | symbol _ZN4Aska4ACSV8SetValueENS0_4TypeEmmPKv | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska4ACSV8SetValueENS0_4TypeEmmPKv
          (long param_1,undefined4 param_2,ulong param_3,ulong param_4,undefined8 *param_5)

{
  undefined8 *puVar1;
  ulong uVar2;
  undefined8 uVar3;
  
  uVar2 = *(ulong *)(param_1 + 0x40);
  if (param_3 < uVar2) {
    if (param_5 == (undefined8 *)0x0) {
      return 0;
    }
    if (*(ulong *)(param_1 + 0x48) <= param_4) {
      return 0;
    }
    switch(param_2) {
    case 0:
      return 1;
    case 1:
    case 2:
    case 3:
      *(undefined1 *)(*(long *)(param_1 + 0x30) + (param_3 + uVar2 * param_4) * 0x10) =
           *(undefined1 *)param_5;
      return 1;
    case 4:
    case 5:
      *(undefined2 *)(*(long *)(param_1 + 0x30) + (param_3 + uVar2 * param_4) * 0x10) =
           *(undefined2 *)param_5;
      return 1;
    case 6:
    case 7:
    case 10:
      *(undefined4 *)(*(long *)(param_1 + 0x30) + (param_3 + uVar2 * param_4) * 0x10) =
           *(undefined4 *)param_5;
      return 1;
    case 8:
    case 9:
    case 0xb:
      *(undefined8 *)(*(long *)(param_1 + 0x30) + (param_3 + uVar2 * param_4) * 0x10) = *param_5;
      return 1;
    case 0xc:
      uVar3 = *param_5;
      puVar1 = (undefined8 *)(*(long *)(param_1 + 0x30) + (param_3 + uVar2 * param_4) * 0x10);
      puVar1[1] = param_5[1];
      *puVar1 = uVar3;
      return 1;
    }
  }
  return 0;
}

// ==== Aska::ACSV::ClearValues()
// vaddr 0x1eff08c | ghidra 0x1fff08c | size 92 | symbol _ZN4Aska4ACSV11ClearValuesEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska4ACSV11ClearValuesEv(long param_1)

{
  *(undefined8 *)(param_1 + 0x30) = 0;
  *(undefined8 *)(param_1 + 0x48) = 0;
  if ((*(long *)(param_1 + 200) != 0) || (*(long *)(param_1 + 0xd0) != 0)) {
    if (*(long *)(param_1 + 0xe0) == 0) {
      *(undefined8 *)(param_1 + 200) = 0;
      *(long *)(param_1 + 0x70) = *(long *)(param_1 + 0x70) - *(long *)(param_1 + 0xd0);
    }
    else {
      if (*(long *)(param_1 + 200) != 0) {
        operator delete[](void*)();
        *(undefined8 *)(param_1 + 200) = 0;
      }
      *(undefined8 *)(param_1 + 0xe0) = 0;
    }
    *(undefined8 *)(param_1 + 0xd0) = 0;
    *(undefined8 *)(param_1 + 0xd8) = 0;
  }
  return;
}

// ==== Aska::ACSV::ClearBlankBits()
// vaddr 0x1eff0e8 | ghidra 0x1fff0e8 | size 64 | symbol _ZN4Aska4ACSV14ClearBlankBitsEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska4ACSV14ClearBlankBitsEv(long param_1)

{
  if ((*(long *)(param_1 + 0x18) != 0) && (*(char *)(param_1 + 0x28) != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 0x28) = 0;
  }
  *(long *)(param_1 + 0x18) = 0;
  *(undefined8 *)(param_1 + 0x20) = 0;
  (*(code *)PTR__ZN4Aska4ACSV10TermMemoryENS0_12WorkMemoryIDE_02ca32c0)(param_1,1);
  return;
}

// ==== Aska::ACSV::ClearTypes()
// vaddr 0x1eff128 | ghidra 0x1fff128 | size 12 | symbol _ZN4Aska4ACSV10ClearTypesEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska4ACSV10ClearTypesEv(long param_1)

{
  *(undefined8 *)(param_1 + 0x38) = 0;
  *(undefined8 *)(param_1 + 0x40) = 0;
  (*(code *)PTR__ZN4Aska4ACSV10TermMemoryENS0_12WorkMemoryIDE_02ca32c0)(param_1,0);
  return;
}

// ==== Aska::ACSV::TermMemory(Aska::ACSV::WorkMemoryID)
// vaddr 0x1eff134 | ghidra 0x1fff134 | size 156 | symbol _ZN4Aska4ACSV10TermMemoryENS0_12WorkMemoryIDE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska4ACSV10TermMemoryENS0_12WorkMemoryIDE(long param_1,uint param_2)

{
  long lVar1;
  ulong uVar2;
  long *plVar3;
  
  if ((int)param_2 < 2) {
    _ZN4Aska4ACSV10TermMemoryENS0_12WorkMemoryIDE(param_1,param_2 + 1);
  }
  uVar2 = (ulong)param_2;
  lVar1 = param_1 + uVar2 * 0x20;
  plVar3 = (long *)(lVar1 + 0x88);
  if ((*plVar3 != 0) || (*(long *)(lVar1 + 0x90) != 0)) {
    if (*(long *)(lVar1 + 0xa0) == 0) {
      *plVar3 = 0;
      plVar3 = (long *)(param_1 + uVar2 * 0x20 + 0x90);
      *(long *)(param_1 + 0x70) = *(long *)(param_1 + 0x70) - *plVar3;
    }
    else {
      if (*plVar3 != 0) {
        operator delete[](void*)();
        *plVar3 = 0;
      }
      *(long *)(lVar1 + 0xa0) = 0;
      plVar3 = (long *)(param_1 + uVar2 * 0x20 + 0x90);
    }
    *(undefined8 *)(param_1 + uVar2 * 0x20 + 0x98) = 0;
    *plVar3 = 0;
  }
  return;
}

// ==== Aska::ACSV::InitMemory(Aska::ACSV::WorkMemoryID, unsigned long)
// vaddr 0x1eff1d0 | ghidra 0x1fff1d0 | size 448 | symbol _ZN4Aska4ACSV10InitMemoryENS0_12WorkMemoryIDEm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska4ACSV10InitMemoryENS0_12WorkMemoryIDEm
               (undefined8 *param_1,long param_2,uint param_3,ulong param_4)

{
  long *plVar1;
  uint uVar2;
  uint uVar3;
  long lVar4;
  ulong uVar5;
  undefined8 uVar6;
  uint uVar7;
  long lVar8;
  uint *puVar9;
  
  lVar8 = param_2 + (ulong)param_3 * 0x20;
  uVar5 = *(long *)(param_2 + 0x70) + param_4;
  plVar1 = (long *)(lVar8 + 0x88);
  if (*(ulong *)(param_2 + 0x60) < uVar5) {
    uVar5 = *(ulong *)(lVar8 + 0xa0);
    if (uVar5 < param_4) {
      if ((uVar5 != 0) && (*plVar1 != 0)) {
        operator delete[](void*)();
        *plVar1 = 0;
      }
      lVar4 = operator new[](unsigned long, std::nothrow_t const&)(param_4,PTR__ZSt7nothrow_02cb9a80);
      *plVar1 = lVar4;
      if (lVar4 == 0) {
        uVar6 = 0xfffffffffffffc41;
        goto code_r0x01fff368;
      }
      *(ulong *)(lVar8 + 0xa0) = param_4;
    }
  }
  else {
    *plVar1 = *(long *)(param_2 + 0x58) + *(long *)(param_2 + 0x70);
    *(undefined8 *)(lVar8 + 0xa0) = 0;
    *(ulong *)(param_2 + 0x70) = uVar5;
  }
  lVar8 = param_2 + (ulong)param_3 * 0x20;
  *(ulong *)(lVar8 + 0x90) = param_4;
  *(undefined8 *)(lVar8 + 0x98) = 0;
  if (param_3 == 2) {
    uVar6 = 0;
    *(long *)(param_2 + 0x30) = *plVar1;
    goto code_r0x01fff368;
  }
  if (param_3 != 1) {
    uVar6 = 0;
    if (param_3 == 0) {
      uVar6 = 0;
      *(long *)(param_2 + 0x38) = *plVar1;
    }
    goto code_r0x01fff368;
  }
  lVar8 = *plVar1;
  uVar3 = (int)param_4 << 3;
  uVar5 = (ulong)uVar3 + 0x1f >> 5;
  uVar7 = (uint)uVar5;
  if (((lVar8 == 0) && (*(char *)(param_2 + 0x28) != '\0')) &&
     (uVar2 = *(uint *)(param_2 + 0x20), uVar7 <= uVar2)) {
    *(uint *)(param_2 + 0x24) = uVar3;
    if (uVar2 != 0) {
      lVar8 = *(long *)(param_2 + 0x18);
      uVar5 = (ulong)(uVar2 << 2);
code_r0x01fff35c:
      memset(lVar8,0,uVar5);
    }
  }
  else {
    if ((*(long *)(param_2 + 0x18) != 0) && (*(char *)(param_2 + 0x28) != '\0')) {
      operator delete[](void*)();
      *(undefined1 *)(param_2 + 0x28) = 0;
    }
    *(long *)(param_2 + 0x18) = 0;
    *(undefined8 *)(param_2 + 0x20) = 0;
    if (uVar3 != 0) {
      puVar9 = (uint *)(param_2 + 0x20);
      *puVar9 = uVar7;
      *(uint *)(param_2 + 0x24) = uVar3;
      if (lVar8 == 0) {
        lVar8 = operator new[](unsigned long, std::nothrow_t const&)(uVar5 << 2,PTR__ZSt7nothrow_02cb9a80);
        *(long *)(param_2 + 0x18) = lVar8;
        *(undefined1 *)(param_2 + 0x28) = 1;
        if (lVar8 == 0) {
          *(undefined1 *)(param_2 + 0x28) = 0;
          puVar9[0] = 0;
          puVar9[1] = 0;
          uVar6 = 0xfffffffffffffc41;
          goto code_r0x01fff368;
        }
      }
      else {
        *(long *)(param_2 + 0x18) = lVar8;
        *(undefined1 *)(param_2 + 0x28) = 0;
      }
      if (uVar7 != 0) {
        uVar5 = uVar5 << 2;
        goto code_r0x01fff35c;
      }
    }
  }
  uVar6 = 0;
code_r0x01fff368:
  *param_1 = uVar6;
  return;
}

// ==== Aska::ACSV::UnpackBinaryValues(void const*, unsigned long)
// vaddr 0x1eff390 | ghidra 0x1fff390 | size 680 | symbol _ZN4Aska4ACSV18UnpackBinaryValuesEPKvm | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska4ACSV18UnpackBinaryValuesEPKvm(long param_1,long param_2,long param_3)

{
  ulong uVar1;
  long lVar2;
  long lVar3;
  long lVar4;
  ulong uVar5;
  ulong uVar6;
  undefined4 *puVar7;
  ulong *puVar8;
  undefined4 *puVar9;
  long lVar10;
  ulong uVar11;
  
  uVar6 = *(ulong *)(param_1 + 0x40);
  lVar4 = -0x3bc;
  if ((uVar6 != 0) && (*(long *)(param_1 + 0x38) != 0)) {
    lVar4 = *(long *)(param_1 + 200);
    *(undefined8 *)(param_1 + 0x30) = 0;
    *(undefined8 *)(param_1 + 0x48) = 0;
    uVar11 = uVar6;
    if ((lVar4 != 0) || (*(long *)(param_1 + 0xd0) != 0)) {
      if (*(long *)(param_1 + 0xe0) == 0) {
        lVar4 = 0;
        *(undefined8 *)(param_1 + 200) = 0;
        *(long *)(param_1 + 0x70) = *(long *)(param_1 + 0x70) - *(long *)(param_1 + 0xd0);
      }
      else {
        if (lVar4 != 0) {
          operator delete[](void*)();
          lVar4 = 0;
          *(undefined8 *)(param_1 + 200) = 0;
          uVar11 = *(ulong *)(param_1 + 0x40);
        }
        *(undefined8 *)(param_1 + 0xe0) = 0;
      }
      *(undefined8 *)(param_1 + 0xd0) = 0;
      *(undefined8 *)(param_1 + 0xd8) = 0;
    }
    lVar3 = *(long *)(param_1 + 0x70);
    uVar5 = uVar11 * 0x10 * *(long *)(param_1 + 0x80);
    uVar1 = lVar3 + uVar5;
    if (*(ulong *)(param_1 + 0x60) < uVar1) {
      if (*(ulong *)(param_1 + 0xe0) < uVar5) {
        lVar4 = operator new[](unsigned long, std::nothrow_t const&)(uVar5,PTR__ZSt7nothrow_02cb9a80);
        *(long *)(param_1 + 200) = lVar4;
        if (lVar4 == 0) {
          if ((*(long *)(param_1 + 0x18) != 0) && (*(char *)(param_1 + 0x28) != '\0')) {
            operator delete[](void*)();
            *(undefined1 *)(param_1 + 0x28) = 0;
          }
          *(long *)(param_1 + 0x18) = 0;
          *(undefined8 *)(param_1 + 0x20) = 0;
          Aska::ACSV::TermMemory(Aska::ACSV::WorkMemoryID)(param_1,1);
          return -0x3bf;
        }
        *(ulong *)(param_1 + 0xe0) = uVar5;
      }
    }
    else {
      *(undefined8 *)(param_1 + 0xe0) = 0;
      *(ulong *)(param_1 + 0x70) = uVar1;
      lVar4 = *(long *)(param_1 + 0x58) + lVar3;
      *(long *)(param_1 + 200) = lVar4;
    }
    puVar8 = (ulong *)(param_1 + 0xd0);
    *puVar8 = uVar5;
    puVar7 = *(undefined4 **)(param_1 + 0x38);
    *(long *)(param_1 + 0x30) = lVar4;
    *(undefined8 *)(param_1 + 0xd8) = 0;
    lVar3 = Aska::ACSV::AllocateMemory(Aska::ACSV::WorkMemoryID, unsigned long)(param_1,2,uVar11 * 0x10);
    if (param_3 < 1) {
      lVar10 = 0;
      lVar4 = 0;
    }
    else {
      lVar4 = 0;
      lVar10 = 0;
      uVar11 = 0;
      puVar9 = puVar7;
      do {
        lVar2 = Aska::ACSV::UnpackBinaryValue(unsigned char const*, unsigned long, Aska::ACSV::AValue*, Aska::ACSV::Type)(param_2,param_3 - lVar4,lVar3,*puVar9);
        if (lVar2 < 0) {
          *(undefined8 *)(param_1 + 0x30) = 0;
          *(undefined8 *)(param_1 + 0x48) = 0;
          if ((*(long *)(param_1 + 200) != 0) || (*puVar8 != 0)) {
            if (*(long *)(param_1 + 0xe0) == 0) {
              *(undefined8 *)(param_1 + 200) = 0;
              *(long *)(param_1 + 0x70) = *(long *)(param_1 + 0x70) - *(long *)(param_1 + 0xd0);
            }
            else {
              if (*(long *)(param_1 + 200) != 0) {
                operator delete[](void*)();
                *(undefined8 *)(param_1 + 200) = 0;
              }
              *(undefined8 *)(param_1 + 0xe0) = 0;
            }
            *puVar8 = 0;
            *(undefined8 *)(param_1 + 0xd8) = 0;
          }
          if ((*(long *)(param_1 + 0x18) != 0) && (*(char *)(param_1 + 0x28) != '\0')) {
            operator delete[](void*)();
            *(undefined1 *)(param_1 + 0x28) = 0;
          }
          *(long *)(param_1 + 0x18) = 0;
          *(undefined8 *)(param_1 + 0x20) = 0;
          Aska::ACSV::TermMemory(Aska::ACSV::WorkMemoryID)(param_1,1);
          return lVar2;
        }
        uVar11 = uVar11 + 1;
        lVar3 = lVar3 + 0x10;
        puVar9 = puVar9 + 1;
        lVar4 = lVar2 + lVar4;
        if ((uVar6 <= uVar11) && (lVar4 < param_3)) {
          lVar3 = Aska::ACSV::AllocateMemory(Aska::ACSV::WorkMemoryID, unsigned long)(param_1,2,*(long *)(param_1 + 0x40) << 4);
          uVar11 = 0;
          lVar10 = lVar10 + 1;
          puVar9 = puVar7;
        }
        param_2 = param_2 + lVar2;
      } while (lVar4 < param_3);
    }
    *(long *)(param_1 + 0x48) = lVar10 + 1;
  }
  return lVar4;
}

// ==== long Aska::ACSV::UnpackTextValues<2, Aska::ACSV::UnpackValueArgs>(Aska::ACSV::UnpackValueArgs const*)
// vaddr 0x1eff638 | ghidra 0x1fff638 | size 2032 | symbol _ZN4Aska4ACSV16UnpackTextValuesILi2ENS0_15UnpackValueArgsEEElPKT0_ | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska4ACSV16UnpackTextValuesILi2ENS0_15UnpackValueArgsEEElPKT0_(long param_1,long *param_2)

{
  char *pcVar1;
  uint uVar2;
  char cVar3;
  char cVar4;
  ulong uVar5;
  char *pcVar6;
  long lVar7;
  ulong uVar8;
  long lVar9;
  char *pcVar10;
  ulong uVar11;
  char *pcVar12;
  long lVar13;
  ulong uVar14;
  long *plVar15;
  undefined4 *puVar16;
  undefined4 *puVar17;
  char *pcVar18;
  long lStack_88;
  char acStack_7c [4];
  char acStack_78 [4];
  char acStack_74 [4];
  char acStack_70 [4];
  char acStack_6c [4];
  long lStack_68;
  
  if (((*(long *)(param_1 + 0x38) == 0) || (*(long *)(param_1 + 0x40) == 0)) ||
     (lVar13 = *(long *)(param_1 + 0x48), lVar13 == 0)) {
    lVar9 = -0x3bc;
  }
  else {
    pcVar1 = (char *)*param_2;
    uVar5 = param_2[1];
    *(undefined8 *)(param_1 + 0x30) = 0;
    *(undefined8 *)(param_1 + 0x48) = 0;
    if ((*(long *)(param_1 + 200) != 0) || (*(long *)(param_1 + 0xd0) != 0)) {
      if (*(long *)(param_1 + 0xe0) == 0) {
        *(undefined8 *)(param_1 + 200) = 0;
        *(long *)(param_1 + 0x70) = *(long *)(param_1 + 0x70) - *(long *)(param_1 + 0xd0);
      }
      else {
        if (*(long *)(param_1 + 200) != 0) {
          operator delete[](void*)();
          *(undefined8 *)(param_1 + 200) = 0;
        }
        *(undefined8 *)(param_1 + 0xe0) = 0;
      }
      *(undefined8 *)(param_1 + 0xd0) = 0;
      *(undefined8 *)(param_1 + 0xd8) = 0;
    }
    plVar15 = (long *)(param_1 + 0x18);
    if ((*plVar15 != 0) && (*(char *)(param_1 + 0x28) != '\0')) {
      operator delete[](void*)();
      *(undefined1 *)(param_1 + 0x28) = 0;
    }
    *plVar15 = 0;
    *(undefined8 *)(param_1 + 0x20) = 0;
    Aska::ACSV::TermMemory(Aska::ACSV::WorkMemoryID)(param_1,1);
    uVar2 = *(uint *)(param_1 + 0x50);
    if (((uVar2 & 1) == 0) ||
       (Aska::ACSV::InitMemory(Aska::ACSV::WorkMemoryID, unsigned long)(&lStack_68,param_1,1,
                        *(long *)(param_1 + 0x40) * lVar13 + 0x1fU >> 3 & 0x1ffffffffffffffc),
       lVar9 = lStack_68, -1 < lStack_68)) {
      lVar7 = *(long *)(param_1 + 0x40);
      lVar9 = *(long *)(param_1 + 0x70);
      uVar14 = lVar7 * lVar13 * 0x10;
      uVar8 = uVar14 + lVar9;
      if (*(ulong *)(param_1 + 0x60) < uVar8) {
        if (*(ulong *)(param_1 + 0xe0) < uVar14) {
          if ((*(ulong *)(param_1 + 0xe0) != 0) && (*(long *)(param_1 + 200) != 0)) {
            operator delete[](void*)();
            *(undefined8 *)(param_1 + 200) = 0;
          }
          lVar9 = operator new[](unsigned long, std::nothrow_t const&)(uVar14,PTR__ZSt7nothrow_02cb9a80);
          *(long *)(param_1 + 200) = lVar9;
          if (lVar9 == 0) {
            lVar9 = -0x3bf;
            goto code_r0x01fff6ac;
          }
          lVar7 = *(long *)(param_1 + 0x40);
          *(ulong *)(param_1 + 0xe0) = uVar14;
        }
        else {
          lVar9 = *(long *)(param_1 + 200);
        }
      }
      else {
        *(undefined8 *)(param_1 + 0xe0) = 0;
        *(ulong *)(param_1 + 0x70) = uVar8;
        lVar9 = *(long *)(param_1 + 0x58) + lVar9;
        *(long *)(param_1 + 200) = lVar9;
      }
      puVar16 = *(undefined4 **)(param_1 + 0x38);
      *(long *)(param_1 + 0x30) = lVar9;
      *(ulong *)(param_1 + 0xd0) = uVar14;
      *(undefined8 *)(param_1 + 0xd8) = 0;
      lVar13 = Aska::ACSV::AllocateMemory(Aska::ACSV::WorkMemoryID, unsigned long)(param_1,2,lVar7 << 4);
      lStack_88 = 0;
      uVar8 = *(ulong *)(param_1 + 0x40);
      lVar7 = 0;
      cVar3 = *(char *)(param_1 + 0x54);
      pcVar12 = pcVar1;
      puVar17 = puVar16;
      pcVar18 = pcVar1;
      do {
        cVar4 = *pcVar18;
        if ((cVar4 == '\0') || (uVar5 <= (ulong)((long)pcVar18 - (long)pcVar1))) {
          if ((pcVar18 <= pcVar12) || (lVar7 == 0)) goto code_r0x01fffda8;
          pcVar6 = pcVar12;
          if (pcVar18 != pcVar12) goto code_r0x01fffd40;
          pcVar6 = (char *)0x0;
          pcVar10 = pcVar12;
          goto joined_r0x01fffd88;
        }
        if (cVar4 == '\n') {
          pcVar6 = pcVar12;
          if (pcVar18 == pcVar12) {
            pcVar6 = (char *)0x0;
            if ((uVar2 & 1) == 0) goto code_r0x01fffa0c;
code_r0x01fffad0:
            uVar14 = bool Aska::ACSV::UnpackTextValue<true>(char const*, unsigned long, Aska::ACSV::AValue*, Aska::ACSV::Type, char, bool*)(pcVar12,pcVar6,lVar13,*puVar17,cVar3,acStack_74);
            if (acStack_74[0] != '\0') {
              uVar11 = lVar7 + lStack_88 * uVar8;
              lVar9 = (uVar11 >> 5 & 0x7ffffff) * 4;
              *(uint *)(*plVar15 + lVar9) =
                   *(uint *)(*plVar15 + lVar9) | 1 << (ulong)((uint)uVar11 & 0x1f);
            }
          }
          else {
            do {
              pcVar10 = pcVar6;
              pcVar6 = pcVar10 + 1;
            } while (*pcVar10 == ' ');
            pcVar12 = pcVar18 + (-2 - (long)pcVar12);
            do {
              pcVar6 = pcVar12;
              if (pcVar6 == (char *)0xfffffffffffffffe) {
                pcVar6 = (char *)0x0;
                goto code_r0x01fffac4;
              }
              pcVar12 = pcVar6 + -1;
            } while ((pcVar10 + 1)[(long)pcVar6] == ' ');
            pcVar6 = pcVar6 + 2;
code_r0x01fffac4:
            pcVar12 = pcVar10;
            if ((uVar2 & 1) != 0) goto code_r0x01fffad0;
code_r0x01fffa0c:
            uVar14 = bool Aska::ACSV::UnpackTextValue<false>(char const*, unsigned long, Aska::ACSV::AValue*, Aska::ACSV::Type, char, bool*)(pcVar12,pcVar6,lVar13,*puVar17,cVar3,0);
          }
          if ((uVar14 & 1) == 0) goto code_r0x01fffe20;
code_r0x01fffb24:
          pcVar12 = pcVar18 + 1;
          puVar17 = puVar16;
          if (*pcVar12 != '\0') {
code_r0x01fffb30:
            puVar17 = puVar16;
            if ((ulong)((long)pcVar12 - (long)pcVar1) < uVar5) {
              lVar13 = Aska::ACSV::AllocateMemory(Aska::ACSV::WorkMemoryID, unsigned long)(param_1,2,*(long *)(param_1 + 0x40) << 4);
              lVar7 = 0;
              lStack_88 = lStack_88 + 1;
            }
          }
        }
        else {
          if (cVar4 == '\"') {
            pcVar6 = pcVar18 + 1;
            while( true ) {
              while( true ) {
                if (uVar5 < (ulong)((long)pcVar6 - (long)pcVar1)) goto code_r0x01fffd24;
                if (*pcVar6 == '\"') break;
                if (*pcVar6 == '\0') goto code_r0x01fffe20;
                pcVar6 = pcVar6 + 1;
              }
              pcVar18 = pcVar6 + 1;
              cVar4 = *pcVar18;
              if (cVar4 == cVar3) goto code_r0x01fffc40;
              if (cVar4 != '\"') break;
              pcVar6 = pcVar6 + 2;
            }
            if ((cVar4 != '\r') && (cVar4 != '\n')) goto code_r0x01fffe20;
code_r0x01fffc40:
            if ((ulong)((long)pcVar18 - (long)pcVar1) <= uVar5) {
              if ((uVar2 & 1) == 0) {
                uVar14 = bool Aska::ACSV::UnpackTextValue<false>(char const*, unsigned long, Aska::ACSV::AValue*, Aska::ACSV::Type, char, bool*)(pcVar12,(long)pcVar18 - (long)pcVar12,lVar13,*puVar17,cVar3
                                         ,0);
              }
              else {
                uVar14 = bool Aska::ACSV::UnpackTextValue<true>(char const*, unsigned long, Aska::ACSV::AValue*, Aska::ACSV::Type, char, bool*)(pcVar12,(long)pcVar18 - (long)pcVar12,lVar13,*puVar17,cVar3
                                         ,acStack_78);
                if (acStack_78[0] != '\0') {
                  uVar11 = lVar7 + lStack_88 * uVar8;
                  lVar9 = (uVar11 >> 5 & 0x7ffffff) * 4;
                  *(uint *)(*plVar15 + lVar9) =
                       *(uint *)(*plVar15 + lVar9) | 1 << (ulong)((uint)uVar11 & 0x1f);
                }
              }
              if ((uVar14 & 1) != 0) {
                if (*pcVar18 != '\r') {
                  pcVar12 = pcVar6 + 2;
                  if (*pcVar18 != '\n') {
                    if (uVar8 <= lVar7 + 1U) goto code_r0x01fffd24;
                    goto code_r0x01fffc10;
                  }
                  cVar4 = *pcVar12;
                  goto joined_r0x01fffd0c;
                }
                pcVar6 = pcVar6 + 2;
                if ((*pcVar6 == '\n') &&
                   (pcVar18 = pcVar6, uVar5 < (ulong)((long)pcVar6 - (long)pcVar1)))
                goto code_r0x01fffd24;
                goto code_r0x01fffb24;
              }
              goto code_r0x01fffe20;
            }
code_r0x01fffd24:
            lVar9 = -0x3c1;
            break;
          }
          if (cVar4 == '\r') {
            pcVar6 = pcVar12;
            if (pcVar18 == pcVar12) {
              pcVar6 = (char *)0x0;
              if ((uVar2 & 1) == 0) goto code_r0x01fff9e0;
code_r0x01fffa3c:
              uVar14 = bool Aska::ACSV::UnpackTextValue<true>(char const*, unsigned long, Aska::ACSV::AValue*, Aska::ACSV::Type, char, bool*)(pcVar12,pcVar6,lVar13,*puVar17,cVar3,acStack_70);
              if (acStack_70[0] != '\0') {
                uVar11 = lVar7 + lStack_88 * uVar8;
                lVar9 = (uVar11 >> 5 & 0x7ffffff) * 4;
                *(uint *)(*plVar15 + lVar9) =
                     *(uint *)(*plVar15 + lVar9) | 1 << (ulong)((uint)uVar11 & 0x1f);
              }
            }
            else {
              do {
                pcVar10 = pcVar6;
                pcVar6 = pcVar10 + 1;
              } while (*pcVar10 == ' ');
              pcVar12 = pcVar18 + (-2 - (long)pcVar12);
              do {
                pcVar6 = pcVar12;
                if (pcVar6 == (char *)0xfffffffffffffffe) {
                  pcVar6 = (char *)0x0;
                  goto code_r0x01fffa30;
                }
                pcVar12 = pcVar6 + -1;
              } while ((pcVar10 + 1)[(long)pcVar6] == ' ');
              pcVar6 = pcVar6 + 2;
code_r0x01fffa30:
              pcVar12 = pcVar10;
              if ((uVar2 & 1) != 0) goto code_r0x01fffa3c;
code_r0x01fff9e0:
              uVar14 = bool Aska::ACSV::UnpackTextValue<false>(char const*, unsigned long, Aska::ACSV::AValue*, Aska::ACSV::Type, char, bool*)(pcVar12,pcVar6,lVar13,*puVar17,cVar3,0);
            }
            if ((uVar14 & 1) != 0) {
              pcVar12 = pcVar18 + 1;
              cVar4 = *pcVar12;
              if (cVar4 == '\n') {
                if (uVar5 < (ulong)((long)pcVar12 - (long)pcVar1)) goto code_r0x01fffd24;
                cVar4 = pcVar18[2];
                pcVar18 = pcVar12;
              }
              pcVar12 = pcVar18 + 1;
joined_r0x01fffd0c:
              puVar17 = puVar16;
              if (cVar4 == '\0') goto code_r0x01fffc18;
              goto code_r0x01fffb30;
            }
            goto code_r0x01fffe20;
          }
          if (cVar4 == cVar3) {
            pcVar6 = pcVar12;
            if (pcVar18 == pcVar12) {
              pcVar6 = (char *)0x0;
              if ((uVar2 & 1) == 0) goto code_r0x01fffb78;
code_r0x01fffba8:
              uVar14 = bool Aska::ACSV::UnpackTextValue<true>(char const*, unsigned long, Aska::ACSV::AValue*, Aska::ACSV::Type, char, bool*)(pcVar12,pcVar6,lVar13,*puVar17,cVar3,acStack_7c);
              if (acStack_7c[0] != '\0') {
                uVar11 = lVar7 + lStack_88 * uVar8;
                lVar9 = (uVar11 >> 5 & 0x7ffffff) * 4;
                *(uint *)(*plVar15 + lVar9) =
                     *(uint *)(*plVar15 + lVar9) | 1 << (ulong)((uint)uVar11 & 0x1f);
              }
            }
            else {
              do {
                pcVar10 = pcVar6;
                pcVar6 = pcVar10 + 1;
              } while (*pcVar10 == ' ');
              pcVar12 = pcVar18 + (-2 - (long)pcVar12);
              do {
                pcVar6 = pcVar12;
                if (pcVar6 == (char *)0xfffffffffffffffe) {
                  pcVar6 = (char *)0x0;
                  goto code_r0x01fffb9c;
                }
                pcVar12 = pcVar6 + -1;
              } while ((pcVar10 + 1)[(long)pcVar6] == ' ');
              pcVar6 = pcVar6 + 2;
code_r0x01fffb9c:
              pcVar12 = pcVar10;
              if ((uVar2 & 1) != 0) goto code_r0x01fffba8;
code_r0x01fffb78:
              uVar14 = bool Aska::ACSV::UnpackTextValue<false>(char const*, unsigned long, Aska::ACSV::AValue*, Aska::ACSV::Type, char, bool*)(pcVar12,pcVar6,lVar13,*puVar17,cVar3,0);
            }
            if ((uVar14 & 1) == 0) goto code_r0x01fffe20;
            if (uVar8 <= lVar7 + 1U) goto code_r0x01fffd24;
            pcVar12 = pcVar18 + 1;
code_r0x01fffc10:
            lVar7 = lVar7 + 1;
            lVar13 = lVar13 + 0x10;
            puVar17 = puVar17 + 1;
          }
        }
code_r0x01fffc18:
        pcVar18 = pcVar18 + 1;
        lVar9 = -0x3c1;
      } while ((ulong)((long)pcVar18 - (long)pcVar1) <= uVar5);
    }
  }
  goto code_r0x01fff6ac;
code_r0x01fffd40:
  do {
    pcVar10 = pcVar6;
    pcVar6 = pcVar10 + 1;
  } while (*pcVar10 == ' ');
  pcVar12 = pcVar18 + (-2 - (long)pcVar12);
  do {
    pcVar6 = pcVar12;
    if (pcVar6 == (char *)0xfffffffffffffffe) {
      pcVar6 = (char *)0x0;
      goto joined_r0x01fffd88;
    }
    pcVar12 = pcVar6 + -1;
  } while ((pcVar10 + 1)[(long)pcVar6] == ' ');
  pcVar6 = pcVar6 + 2;
joined_r0x01fffd88:
  if ((uVar2 & 1) == 0) {
    uVar5 = bool Aska::ACSV::UnpackTextValue<false>(char const*, unsigned long, Aska::ACSV::AValue*, Aska::ACSV::Type, char, bool*)(pcVar10,pcVar6,lVar13,*puVar17,cVar3,0);
  }
  else {
    uVar5 = bool Aska::ACSV::UnpackTextValue<true>(char const*, unsigned long, Aska::ACSV::AValue*, Aska::ACSV::Type, char, bool*)(pcVar10,pcVar6,lVar13,*puVar17,cVar3,acStack_6c);
    if (acStack_6c[0] != '\0') {
      uVar8 = lVar7 + lStack_88 * uVar8;
      lVar13 = (uVar8 >> 5 & 0x7ffffff) * 4;
      *(uint *)(*plVar15 + lVar13) = *(uint *)(*plVar15 + lVar13) | 1 << (ulong)((uint)uVar8 & 0x1f)
      ;
    }
  }
  if ((uVar5 & 1) != 0) {
code_r0x01fffda8:
    *(long *)(param_1 + 0x48) = lStack_88 + 1;
    return (long)pcVar18 - (long)pcVar1;
  }
code_r0x01fffe20:
  lVar9 = -0x3b8;
code_r0x01fff6ac:
  *(undefined8 *)(param_1 + 0x30) = 0;
  *(undefined8 *)(param_1 + 0x48) = 0;
  if ((*(long *)(param_1 + 200) != 0) || (*(long *)(param_1 + 0xd0) != 0)) {
    if (*(long *)(param_1 + 0xe0) == 0) {
      *(undefined8 *)(param_1 + 200) = 0;
      *(long *)(param_1 + 0x70) = *(long *)(param_1 + 0x70) - *(long *)(param_1 + 0xd0);
    }
    else {
      if (*(long *)(param_1 + 200) != 0) {
        operator delete[](void*)();
        *(undefined8 *)(param_1 + 200) = 0;
      }
      *(undefined8 *)(param_1 + 0xe0) = 0;
    }
    *(undefined8 *)(param_1 + 0xd0) = 0;
    *(undefined8 *)(param_1 + 0xd8) = 0;
  }
  if ((*(long *)(param_1 + 0x18) != 0) && (*(char *)(param_1 + 0x28) != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 0x28) = 0;
  }
  *(long *)(param_1 + 0x18) = 0;
  *(undefined8 *)(param_1 + 0x20) = 0;
  Aska::ACSV::TermMemory(Aska::ACSV::WorkMemoryID)(param_1,1);
  return lVar9;
}

// ==== long Aska::ACSV::UnpackTextValues<0, Aska::ACSV::UnpackColumnNumArgs>(Aska::ACSV::UnpackColumnNumArgs const*)
// vaddr 0x1effe28 | ghidra 0x1fffe28 | size 380 | symbol _ZN4Aska4ACSV16UnpackTextValuesILi0ENS0_19UnpackColumnNumArgsEEElPKT0_ | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska4ACSV16UnpackTextValuesILi0ENS0_19UnpackColumnNumArgsEEElPKT0_
               (long param_1,long *param_2)

{
  char *pcVar1;
  ulong uVar2;
  char cVar3;
  char cVar4;
  long lVar5;
  long lVar6;
  char *pcVar7;
  char *pcVar8;
  char *pcVar9;
  
  pcVar1 = (char *)*param_2;
  uVar2 = param_2[1];
  cVar3 = *(char *)(param_1 + 0x54);
  lVar5 = 0;
  pcVar7 = pcVar1;
  pcVar8 = pcVar1;
code_r0x01ffff44:
  cVar4 = *pcVar8;
  if ((cVar4 != '\0') && ((ulong)((long)pcVar8 - (long)pcVar1) < uVar2)) {
    if (cVar4 == '\"') {
      pcVar8 = pcVar8 + 1;
      do {
        while( true ) {
          if (uVar2 < (ulong)((long)pcVar8 - (long)pcVar1)) goto code_r0x01ffff60;
          if (*pcVar8 == '\"') break;
          if (*pcVar8 == '\0') {
code_r0x01ffff88:
            lVar6 = -0x3b8;
            goto code_r0x01ffff8c;
          }
          pcVar8 = pcVar8 + 1;
        }
        pcVar9 = pcVar8 + 1;
        cVar4 = *pcVar9;
        if (cVar4 == cVar3) goto code_r0x01fffef0;
        if (cVar4 != '\"') {
          if ((cVar4 != '\n') && (cVar4 != '\r')) goto code_r0x01ffff88;
          goto code_r0x01ffff78;
        }
        pcVar8 = pcVar8 + 2;
      } while( true );
    }
    if ((cVar4 == '\n') || (cVar4 == '\r')) goto code_r0x01ffff4c;
    pcVar9 = pcVar8;
    if (cVar4 == cVar3) {
      if (pcVar8 != pcVar7) {
        do {
          cVar4 = *pcVar7;
          pcVar7 = pcVar7 + 1;
        } while (cVar4 == ' ');
      }
      lVar5 = lVar5 + 1;
      pcVar7 = pcVar8 + 1;
    }
    goto code_r0x01fffe90;
  }
code_r0x01ffff4c:
  lVar6 = 0;
  *(long *)param_2[2] = lVar5 + 1;
  goto code_r0x01ffff8c;
code_r0x01fffef0:
  if ((cVar3 == '\r') || (cVar3 == '\n')) {
code_r0x01ffff78:
    lVar6 = 0;
    *(long *)param_2[2] = lVar5 + 1;
    goto code_r0x01ffff8c;
  }
  if (uVar2 < (ulong)((long)pcVar9 - (long)pcVar1)) goto code_r0x01ffff9c;
  pcVar8 = pcVar8 + 2;
  if (cVar3 == '\r') {
    if ((*pcVar8 == '\n') && (pcVar9 = pcVar8, uVar2 < (ulong)((long)pcVar8 - (long)pcVar1))) {
code_r0x01ffff60:
      lVar6 = -0x3c1;
      goto code_r0x01ffff8c;
    }
  }
  else {
    lVar5 = lVar5 + 1;
    pcVar7 = pcVar8;
  }
code_r0x01fffe90:
  pcVar8 = pcVar9 + 1;
  pcVar9 = pcVar8;
  if (uVar2 < (ulong)((long)pcVar8 - (long)pcVar1)) {
code_r0x01ffff9c:
    pcVar8 = pcVar9;
    lVar6 = -0x3c1;
code_r0x01ffff8c:
    lVar5 = (long)pcVar8 - (long)pcVar1;
    if (lVar6 < 0) {
      lVar5 = lVar6;
    }
    return lVar5;
  }
  goto code_r0x01ffff44;
}

// ==== long Aska::ACSV::UnpackTextValues<1, Aska::ACSV::UnpackTypeArgs>(Aska::ACSV::UnpackTypeArgs const*)
// vaddr 0x1efffa4 | ghidra 0x1ffffa4 | size 1724 | symbol _ZN4Aska4ACSV16UnpackTextValuesILi1ENS0_14UnpackTypeArgsEEElPKT0_ | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Type propagation algorithm not settling */

long _ZN4Aska4ACSV16UnpackTextValuesILi1ENS0_14UnpackTypeArgsEEElPKT0_(long param_1,long *param_2)

{
  int *piVar1;
  char *pcVar2;
  ulong uVar3;
  ulong uVar4;
  char cVar5;
  char cVar6;
  bool bVar7;
  int iVar8;
  char *pcVar9;
  char *pcVar10;
  int iVar11;
  char *pcVar12;
  long lVar13;
  long *plVar14;
  long *plVar15;
  long lVar16;
  ulong uVar17;
  char *pcVar18;
  int *piVar19;
  
  piVar1 = (int *)param_2[2];
  uVar3 = param_2[3];
  pcVar2 = (char *)*param_2;
  uVar4 = param_2[1];
  plVar14 = (long *)param_2[4];
  memset(piVar1,0,uVar3 << 2);
  memset(plVar14,0,uVar3 << 4);
  cVar5 = *(char *)(param_1 + 0x54);
  uVar17 = 0;
  lVar16 = 0;
  pcVar10 = pcVar2;
  plVar15 = plVar14;
  pcVar18 = pcVar2;
  piVar19 = piVar1;
  do {
    cVar6 = *pcVar18;
    if ((cVar6 == '\0') || (uVar4 <= (ulong)((long)pcVar18 - (long)pcVar2))) {
      if ((pcVar18 <= pcVar10) || (uVar17 == 0)) goto code_r0x02000624;
      pcVar12 = pcVar10;
      if (pcVar18 != pcVar10) goto code_r0x02000514;
      pcVar12 = (char *)0x0;
      pcVar9 = pcVar10;
      goto code_r0x0200055c;
    }
    if (cVar6 == '\n') {
      pcVar12 = pcVar10;
      if (pcVar18 == pcVar10) {
        pcVar12 = (char *)0x0;
        pcVar9 = pcVar10;
      }
      else {
        do {
          pcVar9 = pcVar12;
          pcVar12 = pcVar9 + 1;
        } while (*pcVar9 == ' ');
        pcVar10 = pcVar18 + (-2 - (long)pcVar10);
        do {
          pcVar12 = pcVar10;
          if (pcVar12 == (char *)0xfffffffffffffffe) {
            pcVar12 = (char *)0x0;
            goto code_r0x020001bc;
          }
          pcVar10 = pcVar12 + -1;
        } while ((pcVar9 + 1)[(long)pcVar12] == ' ');
        pcVar12 = pcVar12 + 2;
      }
code_r0x020001bc:
      if (*piVar19 < 0xc) {
        iVar8 = Aska::ACSV::UnpackTextType(char const*, unsigned long, Aska::ACSV::PriorityContext*)(pcVar9,pcVar12,plVar15);
        iVar11 = *piVar19;
        if (iVar8 != iVar11) {
          if ((iVar11 - 2U | iVar8 - 2U) < 8) {
            lVar13 = *plVar15;
            if ((char)plVar15[1] == '\0') {
              if (lVar13 < 0x100) {
                iVar8 = 3;
              }
              else {
                if (0xffff < lVar13) {
                  bVar7 = SBORROW8(lVar13,0x100000000);
                  lVar13 = lVar13 + -0x100000000;
                  iVar11 = 9;
                  iVar8 = 7;
                  goto code_r0x02000464;
                }
                iVar8 = 5;
              }
            }
            else if (lVar13 < 0x81) {
              iVar8 = 2;
            }
            else if (lVar13 < 0x8001) {
              iVar8 = 4;
            }
            else {
              bVar7 = SBORROW8(lVar13,0x80000001);
              lVar13 = lVar13 + -0x80000001;
              iVar11 = 8;
              iVar8 = 6;
code_r0x02000464:
              if (lVar13 < 0 == bVar7) {
                iVar8 = iVar11;
              }
            }
          }
          else if (iVar8 <= iVar11) {
            iVar8 = iVar11;
          }
        }
        *piVar19 = iVar8;
      }
      pcVar10 = pcVar18 + 1;
      plVar15 = plVar14;
      piVar19 = piVar1;
      if ((*pcVar10 != '\0') && ((ulong)((long)pcVar10 - (long)pcVar2) < uVar4)) {
        lVar16 = lVar16 + 1;
        uVar17 = 0;
      }
    }
    else {
      if (cVar6 == '\"') {
        do {
          pcVar18 = pcVar18 + 1;
          while( true ) {
            if (uVar4 < (ulong)((long)pcVar18 - (long)pcVar2)) goto code_r0x020004f0;
            if (*pcVar18 != '\"') break;
            pcVar12 = pcVar18 + 1;
            cVar6 = *pcVar12;
            if (cVar6 == cVar5) {
code_r0x0200025c:
              if (uVar4 < (ulong)((long)pcVar12 - (long)pcVar2)) goto code_r0x0200059c;
              if (*piVar19 < 0xc) {
                *piVar19 = 0xc;
                cVar6 = *pcVar12;
              }
              if (cVar6 != '\r') {
                pcVar10 = pcVar18 + 2;
                pcVar18 = pcVar12;
                if (cVar6 == '\n') {
                  cVar6 = *pcVar10;
                  goto joined_r0x020002ac;
                }
                if (uVar3 <= uVar17 + 1) goto code_r0x0200059c;
                plVar15 = plVar15 + 2;
                uVar17 = uVar17 + 1;
                piVar19 = piVar19 + 1;
                goto code_r0x020004e0;
              }
              pcVar18 = pcVar18 + 2;
              if ((*pcVar18 == '\n') &&
                 (pcVar12 = pcVar18, uVar4 < (ulong)((long)pcVar18 - (long)pcVar2)))
              goto code_r0x020004f0;
              pcVar10 = pcVar12 + 1;
              cVar6 = *pcVar10;
              pcVar18 = pcVar12;
              goto joined_r0x020002ac;
            }
            if (cVar6 != '\"') {
              if ((cVar6 == '\r') || (cVar6 == '\n')) goto code_r0x0200025c;
              goto code_r0x020004f8;
            }
            pcVar18 = pcVar18 + 2;
          }
        } while (*pcVar18 != '\0');
code_r0x020004f8:
        lVar13 = -0x3b8;
        goto code_r0x02000634;
      }
      if (cVar6 == '\r') {
        pcVar12 = pcVar10;
        if (pcVar18 == pcVar10) {
          pcVar12 = (char *)0x0;
          pcVar9 = pcVar10;
        }
        else {
          do {
            pcVar9 = pcVar12;
            pcVar12 = pcVar9 + 1;
          } while (*pcVar9 == ' ');
          pcVar10 = pcVar18 + (-2 - (long)pcVar10);
          do {
            pcVar12 = pcVar10;
            if (pcVar12 == (char *)0xfffffffffffffffe) {
              pcVar12 = (char *)0x0;
              goto code_r0x02000174;
            }
            pcVar10 = pcVar12 + -1;
          } while ((pcVar9 + 1)[(long)pcVar12] == ' ');
          pcVar12 = pcVar12 + 2;
        }
code_r0x02000174:
        if (*piVar19 < 0xc) {
          iVar8 = Aska::ACSV::UnpackTextType(char const*, unsigned long, Aska::ACSV::PriorityContext*)(pcVar9,pcVar12,plVar15);
          iVar11 = *piVar19;
          if (iVar8 != iVar11) {
            if ((iVar11 - 2U | iVar8 - 2U) < 8) {
              lVar13 = *plVar15;
              if ((char)plVar15[1] == '\0') {
                if (lVar13 < 0x100) {
                  iVar8 = 3;
                }
                else {
                  if (0xffff < lVar13) {
                    bVar7 = SBORROW8(lVar13,0x100000000);
                    lVar13 = lVar13 + -0x100000000;
                    iVar11 = 9;
                    iVar8 = 7;
                    goto code_r0x02000400;
                  }
                  iVar8 = 5;
                }
              }
              else if (lVar13 < 0x81) {
                iVar8 = 2;
              }
              else if (lVar13 < 0x8001) {
                iVar8 = 4;
              }
              else {
                bVar7 = SBORROW8(lVar13,0x80000001);
                lVar13 = lVar13 + -0x80000001;
                iVar11 = 8;
                iVar8 = 6;
code_r0x02000400:
                if (lVar13 < 0 == bVar7) {
                  iVar8 = iVar11;
                }
              }
            }
            else if (iVar8 <= iVar11) {
              iVar8 = iVar11;
            }
          }
          *piVar19 = iVar8;
        }
        pcVar12 = pcVar18 + 1;
        cVar6 = *pcVar12;
        if (cVar6 == '\n') {
          if (uVar4 < (ulong)((long)pcVar12 - (long)pcVar2)) {
code_r0x0200059c:
            lVar13 = -0x3c1;
            pcVar18 = pcVar12;
            goto code_r0x02000634;
          }
          cVar6 = pcVar18[2];
          pcVar10 = pcVar18 + 2;
          pcVar18 = pcVar12;
        }
        else {
          pcVar10 = pcVar18 + 1;
        }
joined_r0x020002ac:
        plVar15 = plVar14;
        piVar19 = piVar1;
        if ((cVar6 != '\0') && ((ulong)((long)pcVar10 - (long)pcVar2) < uVar4)) {
          lVar16 = lVar16 + 1;
          uVar17 = 0;
        }
      }
      else if (cVar6 == cVar5) {
        pcVar12 = pcVar10;
        if (pcVar18 == pcVar10) {
          pcVar12 = (char *)0x0;
          pcVar9 = pcVar10;
        }
        else {
          do {
            pcVar9 = pcVar12;
            pcVar12 = pcVar9 + 1;
          } while (*pcVar9 == ' ');
          pcVar10 = pcVar18 + (-2 - (long)pcVar10);
          do {
            pcVar12 = pcVar10;
            if (pcVar12 == (char *)0xfffffffffffffffe) {
              pcVar12 = (char *)0x0;
              goto code_r0x0200020c;
            }
            pcVar10 = pcVar12 + -1;
          } while ((pcVar9 + 1)[(long)pcVar12] == ' ');
          pcVar12 = pcVar12 + 2;
        }
code_r0x0200020c:
        if (*piVar19 < 0xc) {
          iVar8 = Aska::ACSV::UnpackTextType(char const*, unsigned long, Aska::ACSV::PriorityContext*)(pcVar9,pcVar12,plVar15);
          iVar11 = *piVar19;
          if (iVar8 != iVar11) {
            if ((iVar11 - 2U | iVar8 - 2U) < 8) {
              lVar13 = *plVar15;
              if ((char)plVar15[1] == '\0') {
                if (lVar13 < 0x100) {
                  iVar8 = 3;
                }
                else {
                  if (0xffff < lVar13) {
                    bVar7 = SBORROW8(lVar13,0x100000000);
                    lVar13 = lVar13 + -0x100000000;
                    iVar11 = 9;
                    iVar8 = 7;
                    goto code_r0x020004bc;
                  }
                  iVar8 = 5;
                }
              }
              else if (lVar13 < 0x81) {
                iVar8 = 2;
              }
              else if (lVar13 < 0x8001) {
                iVar8 = 4;
              }
              else {
                bVar7 = SBORROW8(lVar13,0x80000001);
                lVar13 = lVar13 + -0x80000001;
                iVar11 = 8;
                iVar8 = 6;
code_r0x020004bc:
                if (lVar13 < 0 == bVar7) {
                  iVar8 = iVar11;
                }
              }
            }
            else if (iVar8 <= iVar11) {
              iVar8 = iVar11;
            }
          }
          *piVar19 = iVar8;
        }
        if (uVar3 <= uVar17 + 1) break;
        pcVar10 = pcVar18 + 1;
        plVar15 = plVar15 + 2;
        uVar17 = uVar17 + 1;
        piVar19 = piVar19 + 1;
      }
    }
code_r0x020004e0:
    pcVar18 = pcVar18 + 1;
  } while ((ulong)((long)pcVar18 - (long)pcVar2) <= uVar4);
code_r0x020004f0:
  lVar13 = -0x3c1;
  goto code_r0x02000634;
code_r0x02000514:
  do {
    pcVar9 = pcVar12;
    pcVar12 = pcVar9 + 1;
  } while (*pcVar9 == ' ');
  pcVar10 = pcVar18 + (-2 - (long)pcVar10);
  do {
    pcVar12 = pcVar10;
    if (pcVar12 == (char *)0xfffffffffffffffe) {
      pcVar12 = (char *)0x0;
      goto code_r0x0200055c;
    }
    pcVar10 = pcVar12 + -1;
  } while ((pcVar9 + 1)[(long)pcVar12] == ' ');
  pcVar12 = pcVar12 + 2;
code_r0x0200055c:
  if (*piVar19 < 0xc) {
    iVar8 = Aska::ACSV::UnpackTextType(char const*, unsigned long, Aska::ACSV::PriorityContext*)(pcVar9,pcVar12,plVar15);
    iVar11 = *piVar19;
    if (iVar8 != iVar11) {
      if ((iVar11 - 2U | iVar8 - 2U) < 8) {
        lVar13 = *plVar15;
        if ((char)plVar15[1] == '\0') {
          if (lVar13 < 0x100) {
            iVar8 = 3;
          }
          else if (lVar13 < 0x10000) {
            iVar8 = 5;
          }
          else {
            iVar8 = 7;
            if (0xffffffff < lVar13) {
              iVar8 = 9;
            }
          }
        }
        else if (lVar13 < 0x81) {
          iVar8 = 2;
        }
        else if (lVar13 < 0x8001) {
          iVar8 = 4;
        }
        else {
          iVar8 = 6;
          if (0x80000000 < lVar13) {
            iVar8 = 8;
          }
        }
      }
      else if (iVar8 <= iVar11) {
        iVar8 = iVar11;
      }
    }
    *piVar19 = iVar8;
  }
code_r0x02000624:
  lVar13 = 0;
  *(long *)(param_1 + 0x48) = lVar16 + 1;
code_r0x02000634:
  lVar16 = (long)pcVar18 - (long)pcVar2;
  if (lVar13 < 0) {
    lVar16 = lVar13;
  }
  return lVar16;
}

// ==== Aska::ACSV::AllocateMemory(Aska::ACSV::WorkMemoryID, unsigned long)
// vaddr 0x1f00660 | ghidra 0x2000660 | size 232 | symbol _ZN4Aska4ACSV14AllocateMemoryENS0_12WorkMemoryIDEm | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska4ACSV14AllocateMemoryENS0_12WorkMemoryIDEm(long param_1,uint param_2,long param_3)

{
  long lVar1;
  long lVar2;
  ulong uVar3;
  ulong *puVar4;
  ulong uVar5;
  long *plVar6;
  long lStack_48;
  
  lVar2 = param_1 + (ulong)param_2 * 0x20;
  puVar4 = (ulong *)(lVar2 + 0x98);
  uVar5 = *puVar4;
  uVar3 = *(ulong *)(lVar2 + 0x90);
  plVar6 = (long *)(lVar2 + 0x88);
  if (uVar3 < uVar5 + param_3) {
    lVar1 = operator new[](unsigned long, std::nothrow_t const&)(uVar3,PTR__ZSt7nothrow_02cb9a80);
    lVar2 = 0;
    if (lVar1 != 0) {
      memcpy(lVar1,*plVar6,uVar3);
      Aska::ACSV::InitMemory(Aska::ACSV::WorkMemoryID, unsigned long)(&lStack_48,param_1,param_2,uVar3 << 1);
      if (lStack_48 < 0) {
        operator delete[](void*)(lVar1);
        lVar2 = 0;
      }
      else {
        memcpy(*plVar6,lVar1,uVar3);
        *puVar4 = uVar5;
        operator delete[](void*)(lVar1);
        lVar2 = _ZN4Aska4ACSV14AllocateMemoryENS0_12WorkMemoryIDEm(param_1,param_2,param_3);
      }
    }
  }
  else {
    *puVar4 = uVar5 + param_3;
    lVar2 = *plVar6 + uVar5;
  }
  return lVar2;
}

// ==== Aska::ACSV::FreeMemory(Aska::ACSV::WorkMemoryID)
// vaddr 0x1f00748 | ghidra 0x2000748 | size 16 | symbol _ZN4Aska4ACSV10FreeMemoryENS0_12WorkMemoryIDE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska4ACSV10FreeMemoryENS0_12WorkMemoryIDE(long param_1,uint param_2)

{
  *(undefined8 *)(param_1 + (ulong)param_2 * 0x20 + 0x98) = 0;
  return;
}

// ==== Aska::ACSV::EncodeDoubleQuotation(char const*, unsigned long, char*, unsigned long)
// vaddr 0x1f00758 | ghidra 0x2000758 | size 676 | symbol _ZN4Aska4ACSV21EncodeDoubleQuotationEPKcmPcm | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZN4Aska4ACSV21EncodeDoubleQuotationEPKcmPcm
                (char *param_1,ulong param_2,char *param_3,ulong param_4)

{
  ulong uVar1;
  byte bVar2;
  bool bVar3;
  undefined1 *puVar4;
  ulong uVar5;
  ulong uVar6;
  long lVar7;
  ulong uVar8;
  undefined1 auStack_240 [512];
  
  puVar4 = auStack_240;
  if (param_2 == 0) {
    return 0;
  }
  if (param_2 == 1) {
    if (*param_1 != '\"') {
      if (param_3 != (char *)0x0 && param_4 != 0) {
        *param_3 = *param_1;
        return 1;
      }
      return 1;
    }
    if (param_3 == (char *)0x0 || param_4 == 0) {
      return 4;
    }
    if (3 < param_4) {
      *param_3 = '\0';
      return 4;
    }
  }
  else {
    uVar8 = 0;
    lVar7 = 0;
    bVar3 = false;
    do {
      bVar2 = param_1[uVar8];
      if (bVar2 == 0x22) {
        lVar7 = lVar7 + 1;
      }
      if (bVar3) {
code_r0x02000804:
        bVar3 = true;
      }
      else {
        bVar3 = false;
        if ((bVar2 < 0x2d) && ((1L << ((ulong)bVar2 & 0x3f) & 0x100000002400U) != 0)) {
          lVar7 = lVar7 + 2;
          goto code_r0x02000804;
        }
      }
      uVar8 = uVar8 + 1;
    } while (param_2 != uVar8);
    uVar8 = lVar7 + param_2;
    if ((long)uVar8 < 0) {
      return uVar8;
    }
    if (param_3 == (char *)0x0) {
      return uVar8;
    }
    if (param_4 == 0) {
      return uVar8;
    }
    if (lVar7 != 0) {
      if ((0x200 < (long)uVar8) &&
         (puVar4 = (undefined1 *)operator new[](unsigned long, std::nothrow_t const&)(uVar8,PTR__ZSt7nothrow_02cb9a80),
         puVar4 == (undefined1 *)0x0)) {
        return 0xfffffffffffffc41;
      }
      uVar5 = Aska::ACSV::InsertDoubleQuotation(char const*, unsigned long, char*, unsigned long, signed char)(param_1,param_2,puVar4,uVar8,0x2c);
      if ((long)uVar5 < 0) {
        if (puVar4 == auStack_240) {
          return uVar5;
        }
        if (puVar4 == (undefined1 *)0x0) {
          return uVar5;
        }
        operator delete[](void*)(puVar4);
        return uVar5;
      }
      if (uVar8 <= param_4) {
        uVar6 = strlen(puVar4);
        uVar5 = uVar6 + 1;
        if (uVar8 == 0xffffffffffffffff) {
          if (uVar5 <= param_4) {
            param_4 = uVar5;
          }
          strncpy(param_3,puVar4,param_4);
        }
        else {
          if (uVar5 != uVar8) {
            uVar6 = uVar5;
          }
          uVar1 = uVar8;
          if (uVar5 <= uVar8) {
            uVar1 = uVar6;
          }
          if (uVar1 < param_4) {
            strncpy(param_3,puVar4,uVar1);
            if (uVar8 <= uVar5) {
              param_3[uVar1] = '\0';
            }
          }
          else {
            raise(5);
          }
        }
        if (puVar4 == auStack_240) {
          return uVar8;
        }
        if (puVar4 == (undefined1 *)0x0) {
          return uVar8;
        }
        operator delete[](void*)(puVar4);
        return uVar8;
      }
      if (puVar4 == auStack_240) {
        return 0xfffffffffffffc3f;
      }
      if (puVar4 == (undefined1 *)0x0) {
        return 0xfffffffffffffc3f;
      }
      operator delete[](void*)(puVar4);
      return 0xfffffffffffffc3f;
    }
    if (param_2 <= param_4) {
      uVar5 = strlen(param_1);
      uVar8 = uVar5 + 1;
      if (param_2 == 0xffffffffffffffff) {
        if (uVar8 <= param_4) {
          param_4 = uVar8;
        }
        strncpy(param_3,param_1,param_4);
        return 0xffffffffffffffff;
      }
      if (uVar8 != param_2) {
        uVar5 = uVar8;
      }
      uVar6 = param_2;
      if (uVar8 <= param_2) {
        uVar6 = uVar5;
      }
      if (uVar6 < param_4) {
        strncpy(param_3,param_1,uVar6);
        if (uVar8 < param_2) {
          return param_2;
        }
        param_3[uVar6] = '\0';
        return param_2;
      }
      raise(5);
      return param_2;
    }
  }
  return 0xfffffffffffffc3f;
}

// ==== Aska::ACSV::InsertDoubleQuotation(char const*, unsigned long, char*, unsigned long, signed char)
// vaddr 0x1f009fc | ghidra 0x20009fc | size 280 | symbol _ZN4Aska4ACSV21InsertDoubleQuotationEPKcmPcma | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZN4Aska4ACSV21InsertDoubleQuotationEPKcmPcma
                (char *param_1,ulong param_2,long param_3,ulong param_4,char param_5)

{
  ulong uVar1;
  char cVar2;
  bool bVar3;
  ulong uVar4;
  long lVar5;
  ulong uVar6;
  
  if ((param_3 == 0) || (param_4 == 0)) {
    lVar5 = 0;
    if (param_2 != 0) {
      bVar3 = false;
      uVar6 = param_2;
      do {
        cVar2 = *param_1;
        if (cVar2 == '\"') {
          lVar5 = lVar5 + 1;
        }
        if (bVar3) {
code_r0x02000a7c:
          bVar3 = true;
        }
        else {
          if (((cVar2 == '\n') || (cVar2 == '\r')) || (cVar2 == param_5)) {
            lVar5 = lVar5 + 2;
            goto code_r0x02000a7c;
          }
          bVar3 = false;
        }
        uVar6 = uVar6 - 1;
        param_1 = param_1 + 1;
      } while (uVar6 != 0);
    }
    param_2 = lVar5 + param_2;
  }
  else if (param_4 < param_2) {
    param_2 = 0;
  }
  else {
    uVar4 = strlen(param_1);
    uVar6 = uVar4 + 1;
    if (param_2 == 0xffffffffffffffff) {
      if (uVar6 <= param_4) {
        param_4 = uVar6;
      }
      strncpy(param_3,param_1,param_4);
    }
    else {
      if (uVar6 != param_2) {
        uVar4 = uVar6;
      }
      uVar1 = param_2;
      if (uVar6 <= param_2) {
        uVar1 = uVar4;
      }
      if (uVar1 < param_4) {
        strncpy(param_3,param_1,uVar1);
        if (param_2 <= uVar6) {
          *(undefined1 *)(param_3 + uVar1) = 0;
        }
      }
      else {
        raise(5);
      }
    }
  }
  return param_2;
}

// ==== Aska::ACSV::Get(unsigned long, void*) const
// vaddr 0x1f00b14 | ghidra 0x2000b14 | size 248 | symbol _ZNK4Aska4ACSV3GetEmPv | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Possible PIC construction at 0x02000ba8: Changing call to branch */
/* WARNING: Removing unreachable block (ram,0x02000bac) */
/* WARNING: Removing unreachable block (ram,0x02000bb0) */

undefined8 _ZNK4Aska4ACSV3GetEmPv(long param_1,ulong param_2,undefined8 *param_3)

{
  uint uVar1;
  undefined8 uVar2;
  int iVar3;
  ulong uVar4;
  ulong uVar5;
  undefined4 uVar6;
  undefined8 uStack_20;
  undefined8 uStack_18;
  
  if ((((*(long *)(param_1 + 0x58) != 0) && (*(long *)(param_1 + 0x60) != 0)) &&
      (*(long *)(param_1 + 0x38) != 0)) && (*(long *)(param_1 + 0x30) != 0)) {
    if (((uint)(param_2 >> 0x20) & 0xffff) == 1) {
      uVar1 = (uint)param_2 & 0xffff;
      uVar4 = (ulong)uVar1;
      if (((int)uVar1 < (int)*(ulong *)(param_1 + 0x40)) &&
         (uVar5 = param_2 >> 0x10 & 0xffff, (int)uVar5 < *(int *)(param_1 + 0x48))) {
        if (uVar4 < *(ulong *)(param_1 + 0x40)) {
          iVar3 = *(int *)(*(long *)(param_1 + 0x38) + uVar4 * 4);
          if (iVar3 == 0xc) {
            uVar4 = Aska::ACSV::GetValue(Aska::ACSV::Type, unsigned long, unsigned long, void*) const();
            if ((uVar4 & 1) != 0) {
              *param_3 = uStack_20;
              param_3[1] = uStack_18;
              return 1;
            }
            return 0;
          }
          if (iVar3 == 0xb) {
            param_3 = &uStack_20;
          }
        }
        else {
          iVar3 = 0;
        }
        uVar2 = (*(code *)PTR__ZNK4Aska4ACSV8GetValueENS0_4TypeEmmPv_02c99e30)
                          (param_1,iVar3,uVar4,uVar5,param_3);
        return uVar2;
      }
    }
    else if ((param_2 & 0xffff00000000) == 0) {
      if (((uint)param_2 & 0xffff) == 1) {
        uVar6 = (undefined4)*(undefined8 *)(param_1 + 0x48);
      }
      else {
        if ((param_2 & 0xffff) != 0) {
          return 0;
        }
        uVar6 = (undefined4)*(undefined8 *)(param_1 + 0x40);
      }
      *(undefined4 *)param_3 = uVar6;
      return 1;
    }
  }
  return 0;
}

// ==== Aska::ACSV::Set(unsigned long, void const*)
// vaddr 0x1f00c0c | ghidra 0x2000c0c | size 200 | symbol _ZN4Aska4ACSV3SetEmPKv | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Possible PIC construction at 0x02000ccc: Changing call to branch */
/* WARNING: Removing unreachable block (ram,0x02000cd0) */

undefined8 _ZN4Aska4ACSV3SetEmPKv(long param_1,ulong param_2,double *param_3)

{
  uint uVar1;
  undefined8 uVar2;
  int iVar3;
  ulong uVar4;
  ulong uVar5;
  double *pdVar6;
  double adStack_20 [2];
  
  pdVar6 = adStack_20;
  if ((((*(long *)(param_1 + 0x58) != 0) && (*(long *)(param_1 + 0x60) != 0)) &&
      (*(long *)(param_1 + 0x38) != 0)) &&
     ((*(long *)(param_1 + 0x30) != 0 && ((param_2 & 0xffff00000000) == 0x100000000)))) {
    uVar1 = (uint)param_2 & 0xffff;
    uVar4 = (ulong)uVar1;
    if (((int)uVar1 < (int)*(ulong *)(param_1 + 0x40)) &&
       (uVar5 = param_2 >> 0x10 & 0xffff, (int)uVar5 < *(int *)(param_1 + 0x48))) {
      if (uVar4 < *(ulong *)(param_1 + 0x40)) {
        iVar3 = *(int *)(*(long *)(param_1 + 0x38) + uVar4 * 4);
        if (iVar3 == 0xc) {
          adStack_20[0] = *param_3;
          adStack_20[1] = 1.58101006669199e-322;
        }
        else {
          pdVar6 = param_3;
          if (iVar3 == 0xb) {
            adStack_20[0] = (double)*(float *)param_3;
            pdVar6 = adStack_20;
          }
        }
      }
      else {
        iVar3 = 0;
        pdVar6 = param_3;
      }
      uVar2 = (*(code *)PTR__ZN4Aska4ACSV8SetValueENS0_4TypeEmmPKv_02c9a890)
                        (param_1,iVar3,uVar4,uVar5,pdVar6);
      return uVar2;
    }
  }
  return 0;
}

// ==== Aska::ACSV::GetClassID(int) const
// vaddr 0x1f01ba8 | ghidra 0x2001ba8 | size 24 | symbol _ZNK4Aska4ACSV10GetClassIDEi | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska4ACSV10GetClassIDEi(undefined8 param_1,int param_2)

{
  undefined8 uVar1;
  
  uVar1 = 0xf000f190;
  if (param_2 != 0) {
    uVar1 = 0xf000;
  }
  return uVar1;
}

// ==== Aska::ACSV::Serialize(void*, unsigned long) const
// vaddr 0x1f01bc0 | ghidra 0x2001bc0 | size 8 | symbol _ZNK4Aska4ACSV9SerializeEPvm | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK4Aska4ACSV9SerializeEPvm(void)

{
  (*(code *)PTR__ZNK4Aska4ACSV15SerializeBinaryEPvmNS_7Machine6EndianE_02c9adf0)();
  return;
}

// ==== Aska::ACSV::Deserialize(void const*, unsigned long)
// vaddr 0x1f01bc8 | ghidra 0x2001bc8 | size 4 | symbol _ZN4Aska4ACSV11DeserializeEPKvm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska4ACSV11DeserializeEPKvm(void)

{
  (*(code *)PTR__ZN4Aska4ACSV17DeserializeBinaryEPKvm_02c9bd50)();
  return;
}

// ==== Aska::ACSV::CalcSerializedSize() const
// vaddr 0x1f01bcc | ghidra 0x2001bcc | size 292 | symbol _ZNK4Aska4ACSV18CalcSerializedSizeEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK4Aska4ACSV18CalcSerializedSizeEv(long param_1)

{
  long lVar1;
  ulong uVar2;
  ulong uVar3;
  ulong uVar4;
  ulong uVar5;
  long lVar6;
  ulong uVar7;
  long lVar8;
  
  if (*(long *)(param_1 + 0x58) == 0) {
    return -0x3bc;
  }
  if (*(long *)(param_1 + 0x60) == 0) {
    return -0x3bc;
  }
  if (*(long *)(param_1 + 0x38) == 0) {
    return -0x3bc;
  }
  lVar1 = *(long *)(param_1 + 0x30);
  if (lVar1 == 0) {
    return -0x3bc;
  }
  uVar2 = *(ulong *)(param_1 + 0x40);
  if (uVar2 == 0) {
    return -0x3bc;
  }
  uVar4 = *(ulong *)(param_1 + 0x48);
  if (uVar4 == 0) {
    return -0x3bc;
  }
  uVar3 = uVar2 + 0x2f & 0xfffffffffffffff0;
  if (((*(byte *)(param_1 + 0x50) & 1) != 0) && (*(int *)(param_1 + 0x24) != 0)) {
    uVar3 = ((uVar4 * uVar2 >> 3) + 0xf & 0x3ffffffffffffff0) + uVar3;
  }
  uVar5 = 0;
  lVar6 = 0;
  do {
    uVar7 = 0;
    do {
      lVar8 = 0;
      switch(*(undefined4 *)(*(long *)(param_1 + 0x38) + uVar7 * 4)) {
      case 0:
        break;
      case 1:
      case 2:
      case 3:
        lVar8 = 1;
        break;
      case 4:
      case 5:
        lVar8 = 2;
        break;
      case 6:
      case 7:
      case 10:
        lVar8 = 4;
        break;
      case 8:
      case 9:
      case 0xb:
        lVar8 = 8;
        break;
      case 0xc:
        lVar8 = *(long *)(lVar1 + 8) + 4;
        if (lVar8 < 0) goto code_r0x02001cd8;
        break;
      default:
        lVar8 = -1;
        goto code_r0x02001cd8;
      }
      uVar7 = uVar7 + 1;
      lVar6 = lVar8 + lVar6;
      lVar1 = lVar1 + 0x10;
    } while (uVar7 < uVar2);
    uVar5 = uVar5 + 1;
    lVar8 = lVar6;
  } while (uVar5 < uVar4);
code_r0x02001cd8:
  uVar2 = 0;
  if (-1 < lVar8) {
    uVar2 = uVar3;
  }
  return uVar2 + lVar8;
}

// ==== Aska::ACSV::Serialize(Aska::IStream*) const
// vaddr 0x1f01cf0 | ghidra 0x2001cf0 | size 4 | symbol _ZNK4Aska4ACSV9SerializeEPNS_7IStreamE | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK4Aska4ACSV9SerializeEPNS_7IStreamE(void)

{
  (*(code *)PTR__ZNK4Aska4ACSV15SerializeBinaryEPNS_7IStreamE_02ca34d0)();
  return;
}

// ==== Aska::ACSV::Deserialize(Aska::IStream const*)
// vaddr 0x1f01cf4 | ghidra 0x2001cf4 | size 212 | symbol _ZN4Aska4ACSV11DeserializeEPKNS_7IStreamE | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska4ACSV11DeserializeEPKNS_7IStreamE(long *param_1,long *param_2)

{
  ulong uVar1;
  long lVar2;
  long lVar3;
  long lVar4;
  undefined8 uVar5;
  
  if ((param_2 == (long *)0x0) ||
     (uVar1 = (**(code **)(*param_2 + 0x10))(param_2), (uVar1 & 1) == 0)) {
    uVar5 = 0xfffffffffffffc43;
  }
  else {
    lVar2 = (**(code **)(*param_2 + 0x60))(param_2);
    lVar3 = operator new[](unsigned long, std::nothrow_t const&)(lVar2,PTR__ZSt7nothrow_02cb9a80);
    if (lVar3 == 0) {
      uVar5 = 0xfffffffffffffc41;
    }
    else {
      lVar4 = (**(code **)(*param_2 + 0x28))(param_2,lVar3,1,lVar2);
      if (lVar4 == lVar2) {
        uVar5 = (**(code **)(*param_1 + 0x40))(param_1,lVar3,lVar2);
      }
      else {
        uVar5 = (**(code **)(*param_2 + 0x50))(param_2);
      }
      operator delete[](void*)(lVar3);
    }
  }
  return uVar5;
}

// ==== Aska::ACSV::UnpackBinaryValue(unsigned char const*, unsigned long, Aska::ACSV::AValue*, Aska::ACSV::Type)
// vaddr 0x1f0212c | ghidra 0x200212c | size 496 | symbol _ZN4Aska4ACSV17UnpackBinaryValueEPKhmPNS0_6AValueENS0_4TypeE | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZN4Aska4ACSV17UnpackBinaryValueEPKhmPNS0_6AValueENS0_4TypeE
                (uint *param_1,ulong param_2,uint *param_3,undefined4 param_4)

{
  ulong uVar1;
  undefined1 uVar2;
  long lVar3;
  
  switch(param_4) {
  case 0:
    param_3[0] = 0;
    param_3[1] = 0;
    return 0;
  case 1:
    if (param_2 == 0) {
      return 0xfffffffffffffc3f;
    }
    uVar2 = (char)*param_1 != '\0';
    goto code_r0x020021d8;
  case 2:
    if (param_2 == 0) {
      return 0xfffffffffffffc3f;
    }
    goto code_r0x020021d4;
  case 3:
    if (param_2 == 0) {
      return 0xfffffffffffffc3f;
    }
code_r0x020021d4:
    uVar2 = (undefined1)*param_1;
code_r0x020021d8:
    *(undefined1 *)param_3 = uVar2;
    return 1;
  case 4:
    if (param_2 < 2) {
      return 0xfffffffffffffc3f;
    }
    goto code_r0x02002274;
  case 5:
    if (param_2 < 2) {
      return 0xfffffffffffffc3f;
    }
code_r0x02002274:
    *(short *)param_3 = (short)*param_1;
    return 2;
  case 6:
    if (param_2 < 4) {
      return 0xfffffffffffffc3f;
    }
    break;
  case 7:
    if (param_2 < 4) {
      return 0xfffffffffffffc3f;
    }
    break;
  case 8:
    if (param_2 < 8) {
      return 0xfffffffffffffc3f;
    }
    goto code_r0x02002288;
  case 9:
    if (param_2 < 8) {
      return 0xfffffffffffffc3f;
    }
code_r0x02002288:
    lVar3 = *(long *)param_1;
code_r0x020022c4:
    *(long *)param_3 = lVar3;
    return 8;
  case 10:
    if (param_2 < 4) {
      return 0xfffffffffffffc3f;
    }
    break;
  case 0xb:
    if (param_2 < 8) {
      return 0xfffffffffffffc3f;
    }
    lVar3 = *(long *)param_1;
    goto code_r0x020022c4;
  case 0xc:
    if (param_2 < 4) {
      return 0xfffffffffffffc3f;
    }
    uVar1 = (ulong)*param_1 + 4;
    *(ulong *)(param_3 + 2) = (ulong)*param_1;
    if (uVar1 <= param_2) {
      *(uint **)param_3 = param_1 + 1;
      return uVar1;
    }
    return 0xfffffffffffffc3f;
  default:
    return 0xffffffffffffffff;
  }
  *param_3 = *param_1;
  return 4;
}

// ==== Aska::ACSV::PackBinaryValue(Aska::ACSV::AValue const*, Aska::ACSV::Type, Aska::IStream*)
// vaddr 0x1f0291c | ghidra 0x200291c | size 352 | symbol _ZN4Aska4ACSV15PackBinaryValueEPKNS0_6AValueENS0_4TypeEPNS_7IStreamE | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska4ACSV15PackBinaryValueEPKNS0_6AValueENS0_4TypeEPNS_7IStreamE
               (undefined8 *param_1,undefined4 param_2,long *param_3)

{
  long lVar1;
  long lVar2;
  undefined4 uStack_28;
  undefined1 auStack_24 [4];
  
  lVar2 = 0;
  switch(param_2) {
  case 0:
    break;
  case 1:
    auStack_24[0] = *(undefined1 *)param_1;
    lVar2 = (**(code **)(*param_3 + 0x30))(param_3,auStack_24,1,1);
    break;
  case 2:
  case 3:
                    /* WARNING: Could not recover jumptable at 0x020029c0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    lVar2 = (**(code **)(*param_3 + 0x30))(param_3,param_1,1,1);
    return lVar2;
  case 4:
  case 5:
    lVar2 = (**(code **)(*param_3 + 0x30))(param_3,param_1,2,1);
    lVar2 = lVar2 << 1;
    break;
  case 6:
  case 7:
  case 10:
    lVar2 = (**(code **)(*param_3 + 0x30))(param_3,param_1,4,1);
    lVar2 = lVar2 << 2;
    break;
  case 8:
  case 9:
  case 0xb:
    lVar2 = (**(code **)(*param_3 + 0x30))(param_3,param_1,8,1);
    lVar2 = lVar2 << 3;
    break;
  case 0xc:
    uStack_28 = (undefined4)param_1[1];
    lVar2 = (**(code **)(*param_3 + 0x30))(param_3,&uStack_28,4,1);
    lVar2 = lVar2 * 4;
    if (param_1[1] != 0) {
      lVar1 = (**(code **)(*param_3 + 0x30))(param_3,*param_1,1);
      lVar2 = lVar1 + lVar2;
    }
    break;
  default:
    lVar2 = -1;
  }
  return lVar2;
}

// ==== long Aska::ACSV::CalcSizeTextValue<true>(Aska::ACSV::AValue const*, Aska::ACSV::Type)
// vaddr 0x1f02a7c | ghidra 0x2002a7c | size 648 | symbol _ZN4Aska4ACSV17CalcSizeTextValueILb1EEElPKNS0_6AValueENS0_4TypeE | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZN4Aska4ACSV17CalcSizeTextValueILb1EEElPKNS0_6AValueENS0_4TypeE
                (double *param_1,undefined4 param_2)

{
  ulong uVar1;
  bool bVar2;
  int iVar3;
  ulong uVar4;
  undefined *puVar5;
  uint uVar6;
  char cVar7;
  short sVar8;
  float fVar9;
  uint uVar10;
  double dVar11;
  undefined1 auStack_50 [64];
  
  uVar4 = 0;
  switch(param_2) {
  case 0:
    goto code_r0x02002ce0;
  case 1:
    if (*(char *)param_1 != '\0') {
      return 4;
    }
    return 5;
  case 2:
    uVar6 = (uint)*(byte *)param_1;
    if (uVar6 != 0) {
      cVar7 = '\0';
      do {
        uVar10 = uVar6 + 9;
        uVar6 = (int)(char)uVar6 / 10;
        cVar7 = cVar7 + '\x01';
      } while (0x12 < (uVar10 & 0xff));
      return (long)(char)(cVar7 - ((char)*(byte *)param_1 >> 7));
    }
    break;
  case 3:
    if (*(byte *)param_1 != 0) {
      uVar6 = 0;
      uVar10 = (uint)*(byte *)param_1;
      do {
        uVar6 = uVar6 + 1;
        bVar2 = 9 < uVar10;
        uVar10 = uVar10 / 10;
      } while (bVar2);
      return (ulong)(uVar6 & 0xff);
    }
    break;
  case 4:
    uVar6 = (uint)*(ushort *)param_1;
    if (uVar6 != 0) {
      sVar8 = 0;
      do {
        uVar10 = uVar6 + 9;
        uVar6 = (int)(short)uVar6 / 10;
        sVar8 = sVar8 + 1;
      } while (0x12 < (uVar10 & 0xffff));
      return (long)(short)(sVar8 - ((short)*(ushort *)param_1 >> 0xf));
    }
    break;
  case 5:
    if (*(ushort *)param_1 != 0) {
      uVar6 = 0;
      uVar10 = (uint)*(ushort *)param_1;
      do {
        uVar6 = uVar6 + 1;
        bVar2 = 9 < uVar10;
        uVar10 = uVar10 / 10;
      } while (bVar2);
      return (ulong)(uVar6 & 0xffff);
    }
    break;
  case 6:
    fVar9 = *(float *)param_1;
    if (fVar9 != 0.0) {
      uVar6 = (uint)fVar9 >> 0x1f;
      do {
        uVar10 = (int)fVar9 + 9;
        fVar9 = (float)((int)fVar9 / 10);
        uVar6 = uVar6 + 1;
      } while (0x12 < uVar10);
      return (long)(int)uVar6;
    }
    break;
  case 7:
    if (*(float *)param_1 != 0.0) {
      uVar6 = 0;
      fVar9 = *(float *)param_1;
      do {
        uVar6 = uVar6 + 1;
        bVar2 = 9 < (uint)fVar9;
        fVar9 = (float)((uint)fVar9 / 10);
      } while (bVar2);
      return (ulong)uVar6;
    }
    break;
  case 8:
    dVar11 = *param_1;
    if (dVar11 != 0.0) {
      uVar4 = (ulong)dVar11 >> 0x3f;
      do {
        uVar1 = (long)dVar11 + 9;
        uVar4 = uVar4 + 1;
        dVar11 = (double)((long)dVar11 / 10);
      } while (0x12 < uVar1);
      return uVar4;
    }
    break;
  case 9:
    dVar11 = *param_1;
    if (dVar11 != 0.0) {
      uVar4 = 0;
      do {
        bVar2 = 9 < (ulong)dVar11;
        dVar11 = (double)((ulong)dVar11 / 10);
        uVar4 = uVar4 + 1;
      } while (bVar2);
      return uVar4;
    }
    break;
  case 10:
    puVar5 = &UNK_029622c1/*"%f"*/;
    dVar11 = (double)*(float *)param_1;
    goto code_r0x02002ccc;
  case 0xb:
    dVar11 = *param_1;
    puVar5 = &UNK_0295c70e/*"%lf"*/;
code_r0x02002ccc:
    iVar3 = __aska_snprintf_s(char*, unsigned long, unsigned long, char const*, ...)(dVar11,auStack_50,0x40,0xffffffffffffffff,puVar5);
    return (long)iVar3;
  case 0xc:
    uVar4 = (*(code *)PTR__ZN4Aska4ACSV21EncodeDoubleQuotationEPKcmPcm_02c91c38)
                      (*param_1,param_1[1],0,0);
    return uVar4;
  default:
    uVar4 = 0xffffffffffffffff;
    goto code_r0x02002ce0;
  }
  uVar4 = 1;
code_r0x02002ce0:
  return uVar4;
}

// ==== long Aska::ACSV::CalcSizeTextValue<false>(Aska::ACSV::AValue const*, Aska::ACSV::Type)
// vaddr 0x1f02d04 | ghidra 0x2002d04 | size 632 | symbol _ZN4Aska4ACSV17CalcSizeTextValueILb0EEElPKNS0_6AValueENS0_4TypeE | lib libSOA-3.7.0.so | 2026-10-04
double _ZN4Aska4ACSV17CalcSizeTextValueILb0EEElPKNS0_6AValueENS0_4TypeE
                 (double *param_1,undefined4 param_2)

{
  ulong uVar1;
  bool bVar2;
  int iVar3;
  double dVar4;
  double dVar5;
  undefined *puVar6;
  uint uVar7;
  char cVar8;
  short sVar9;
  float fVar10;
  uint uVar11;
  undefined1 auStack_50 [64];
  
  dVar4 = 0.0;
  switch(param_2) {
  case 0:
    goto code_r0x02002f70;
  case 1:
    if (*(char *)param_1 != '\0') {
      return 1.97626258336499e-323;
    }
    return 2.47032822920623e-323;
  case 2:
    uVar7 = (uint)*(byte *)param_1;
    if (uVar7 != 0) {
      cVar8 = '\0';
      do {
        uVar11 = uVar7 + 9;
        uVar7 = (int)(char)uVar7 / 10;
        cVar8 = cVar8 + '\x01';
      } while (0x12 < (uVar11 & 0xff));
      return (double)(long)(char)(cVar8 - ((char)*(byte *)param_1 >> 7));
    }
    break;
  case 3:
    if (*(byte *)param_1 != 0) {
      uVar7 = 0;
      uVar11 = (uint)*(byte *)param_1;
      do {
        uVar7 = uVar7 + 1;
        bVar2 = 9 < uVar11;
        uVar11 = uVar11 / 10;
      } while (bVar2);
      return (double)(ulong)(uVar7 & 0xff);
    }
    break;
  case 4:
    uVar7 = (uint)*(ushort *)param_1;
    if (uVar7 != 0) {
      sVar9 = 0;
      do {
        uVar11 = uVar7 + 9;
        uVar7 = (int)(short)uVar7 / 10;
        sVar9 = sVar9 + 1;
      } while (0x12 < (uVar11 & 0xffff));
      return (double)(long)(short)(sVar9 - ((short)*(ushort *)param_1 >> 0xf));
    }
    break;
  case 5:
    if (*(ushort *)param_1 != 0) {
      uVar7 = 0;
      uVar11 = (uint)*(ushort *)param_1;
      do {
        uVar7 = uVar7 + 1;
        bVar2 = 9 < uVar11;
        uVar11 = uVar11 / 10;
      } while (bVar2);
      return (double)(ulong)(uVar7 & 0xffff);
    }
    break;
  case 6:
    fVar10 = *(float *)param_1;
    if (fVar10 != 0.0) {
      uVar7 = (uint)fVar10 >> 0x1f;
      do {
        uVar11 = (int)fVar10 + 9;
        fVar10 = (float)((int)fVar10 / 10);
        uVar7 = uVar7 + 1;
      } while (0x12 < uVar11);
      return (double)(long)(int)uVar7;
    }
    break;
  case 7:
    if (*(float *)param_1 != 0.0) {
      uVar7 = 0;
      fVar10 = *(float *)param_1;
      do {
        uVar7 = uVar7 + 1;
        bVar2 = 9 < (uint)fVar10;
        fVar10 = (float)((uint)fVar10 / 10);
      } while (bVar2);
      return (double)(ulong)uVar7;
    }
    break;
  case 8:
    dVar4 = *param_1;
    if (dVar4 != 0.0) {
      dVar5 = (double)((ulong)dVar4 >> 0x3f);
      do {
        uVar1 = (long)dVar4 + 9;
        dVar5 = (double)((long)dVar5 + 1);
        dVar4 = (double)((long)dVar4 / 10);
      } while (0x12 < uVar1);
      return dVar5;
    }
    break;
  case 9:
    dVar4 = *param_1;
    if (dVar4 != 0.0) {
      dVar5 = 0.0;
      do {
        bVar2 = 9 < (ulong)dVar4;
        dVar4 = (double)((ulong)dVar4 / 10);
        dVar5 = (double)((long)dVar5 + 1);
      } while (bVar2);
      return dVar5;
    }
    break;
  case 10:
    puVar6 = &UNK_029622c1/*"%f"*/;
    dVar4 = (double)*(float *)param_1;
    goto code_r0x02002f54;
  case 0xb:
    dVar4 = *param_1;
    puVar6 = &UNK_0295c70e/*"%lf"*/;
code_r0x02002f54:
    iVar3 = __aska_snprintf_s(char*, unsigned long, unsigned long, char const*, ...)(dVar4,auStack_50,0x40,0xffffffffffffffff,puVar6);
    return (double)(long)iVar3;
  case 0xc:
    return param_1[1];
  default:
    dVar4 = -NAN;
    goto code_r0x02002f70;
  }
  dVar4 = 4.94065645841247e-324;
code_r0x02002f70:
  return dVar4;
}

// ==== long Aska::ACSV::PackTextValue<true>(Aska::ACSV::AValue const*, Aska::ACSV::Type, char*, unsigned long)
// vaddr 0x1f02f7c | ghidra 0x2002f7c | size 1184 | symbol _ZN4Aska4ACSV13PackTextValueILb1EEElPKNS0_6AValueENS0_4TypeEPcm | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska4ACSV13PackTextValueILb1EEElPKNS0_6AValueENS0_4TypeEPcm
               (double *param_1,undefined4 param_2,undefined4 *param_3,ulong param_4)

{
  bool bVar1;
  byte bVar2;
  ushort uVar3;
  int iVar4;
  undefined *puVar5;
  uint uVar6;
  ulong uVar7;
  long lVar8;
  char cVar9;
  short sVar11;
  uint uVar13;
  float fVar14;
  float fVar15;
  double dVar16;
  long lVar17;
  double dVar18;
  undefined1 auStack_70 [64];
  char cVar10;
  short sVar12;
  
  lVar17 = 0;
  switch(param_2) {
  case 0:
    goto code_r0x020033bc;
  case 1:
    if (*(byte *)param_1 == 0) {
      if (4 < param_4) {
        if (param_4 == 5) {
          raise(5);
          return 5;
        }
        *param_3 = 0x534c4146;
        *(undefined2 *)(param_3 + 1) = 0x45;
        return 5;
      }
    }
    else if (3 < param_4) {
      if (param_4 == 4) {
        raise(5);
        return 4;
      }
      *(undefined1 *)(param_3 + 1) = 0;
      *param_3 = 0x45555254;
      return 4;
    }
    return -0x3c1;
  case 2:
    bVar2 = *(byte *)param_1;
    cVar10 = '\0';
    cVar9 = '\0';
    uVar6 = (uint)bVar2;
    if (bVar2 != 0) {
      do {
        uVar13 = uVar6 + 9;
        uVar6 = (int)(char)uVar6 / 10;
        cVar9 = cVar10 + '\x01';
        cVar10 = cVar9;
      } while (0x12 < (uVar13 & 0xff));
    }
    if (param_4 < 2) {
      return -0x3c1;
    }
    lVar8 = (long)(char)(cVar9 - ((char)bVar2 >> 7));
    break;
  case 3:
    if (*(byte *)param_1 == 0) {
      uVar6 = 0;
    }
    else {
      uVar6 = 0;
      uVar13 = (uint)*(byte *)param_1;
      do {
        uVar6 = uVar6 + 1;
        bVar1 = 9 < uVar13;
        uVar13 = uVar13 / 10;
      } while (bVar1);
    }
    if (param_4 < 2) {
      return -0x3c1;
    }
    uVar6 = uVar6 & 0xff;
    goto code_r0x0200333c;
  case 4:
    uVar3 = *(ushort *)param_1;
    sVar12 = 0;
    sVar11 = 0;
    uVar6 = (uint)uVar3;
    if (uVar3 != 0) {
      do {
        uVar13 = uVar6 + 9;
        uVar6 = (int)(short)uVar6 / 10;
        sVar11 = sVar12 + 1;
        sVar12 = sVar11;
      } while (0x12 < (uVar13 & 0xffff));
    }
    if (param_4 < 2) {
      return -0x3c1;
    }
    lVar8 = (long)(short)(sVar11 - ((short)uVar3 >> 0xf));
    break;
  case 5:
    if (*(ushort *)param_1 == 0) {
      uVar6 = 0;
    }
    else {
      uVar6 = 0;
      uVar13 = (uint)*(ushort *)param_1;
      do {
        uVar6 = uVar6 + 1;
        bVar1 = 9 < uVar13;
        uVar13 = uVar13 / 10;
      } while (bVar1);
    }
    if (param_4 < 2) {
      return -0x3c1;
    }
    uVar6 = uVar6 & 0xffff;
code_r0x0200333c:
    if (param_4 <= uVar6) {
      return -0x3c1;
    }
    goto code_r0x02003368;
  case 6:
    fVar15 = *(float *)param_1;
    if (fVar15 == 0.0) {
      iVar4 = 0;
    }
    else {
      iVar4 = 0;
      fVar14 = fVar15;
      do {
        uVar6 = (int)fVar14 + 9;
        fVar14 = (float)((int)fVar14 / 10);
        iVar4 = iVar4 + 1;
      } while (0x12 < uVar6);
    }
    if (param_4 < 2) {
      return -0x3c1;
    }
    lVar8 = (long)(iVar4 - ((int)fVar15 >> 0x1f));
    break;
  case 7:
    if (*(float *)param_1 == 0.0) {
      uVar7 = 0;
    }
    else {
      uVar6 = 0;
      fVar15 = *(float *)param_1;
      do {
        uVar6 = uVar6 + 1;
        bVar1 = 9 < (uint)fVar15;
        fVar15 = (float)((uint)fVar15 / 10);
      } while (bVar1);
      uVar7 = (ulong)uVar6;
    }
    if (param_4 < 2) {
      return -0x3c1;
    }
    if (param_4 <= uVar7) {
      return -0x3c1;
    }
    puVar5 = &UNK_027e6d32/*"%u"*/;
    goto code_r0x02003370;
  case 8:
    dVar18 = *param_1;
    if (dVar18 == 0.0) {
      lVar17 = 0;
    }
    else {
      lVar17 = 0;
      dVar16 = dVar18;
      do {
        uVar7 = (long)dVar16 + 9;
        lVar17 = lVar17 + 1;
        dVar16 = (double)((long)dVar16 / 10);
      } while (0x12 < uVar7);
    }
    if (param_4 < 2) {
      return -0x3c1;
    }
    if ((long)param_4 <= lVar17 - ((long)dVar18 >> 0x3f)) {
      return -0x3c1;
    }
    puVar5 = &UNK_029dd0e4/*"%lld"*/;
    goto code_r0x020033a8;
  case 9:
    if (*param_1 == 0.0) {
      uVar7 = 1;
    }
    else {
      uVar7 = 1;
      dVar18 = *param_1;
      do {
        uVar7 = uVar7 + 1;
        bVar1 = 9 < (ulong)dVar18;
        dVar18 = (double)((ulong)dVar18 / 10);
      } while (bVar1);
    }
    if (param_4 < 2) {
      return -0x3c1;
    }
    if (param_4 < uVar7) {
      return -0x3c1;
    }
    puVar5 = &UNK_029df1a7/*"%llu"*/;
code_r0x020033a8:
    iVar4 = __aska_snprintf_s(char*, unsigned long, unsigned long, char const*, ...)(param_3,param_4,0xffffffffffffffff,puVar5);
    goto code_r0x020033b8;
  case 10:
    iVar4 = __aska_snprintf_s(char*, unsigned long, unsigned long, char const*, ...)((double)*(float *)param_1,auStack_70,0x40,0xffffffffffffffff,
                            &UNK_029622c1/*"%f"*/);
    if (param_4 < 2) {
      return -0x3c1;
    }
    if ((int)param_4 <= iVar4) {
      return -0x3c1;
    }
    puVar5 = &UNK_029622c1/*"%f"*/;
    dVar18 = (double)*(float *)param_1;
    goto code_r0x02003284;
  case 0xb:
    iVar4 = __aska_snprintf_s(char*, unsigned long, unsigned long, char const*, ...)(*param_1,auStack_70,0x40,0xffffffffffffffff,&UNK_0295c70e/*"%lf"*/);
    if (param_4 < 2) {
      return -0x3c1;
    }
    if ((int)param_4 <= iVar4) {
      return -0x3c1;
    }
    dVar18 = *param_1;
    puVar5 = &UNK_0295c70e/*"%lf"*/;
code_r0x02003284:
    iVar4 = __aska_snprintf_s(char*, unsigned long, unsigned long, char const*, ...)(dVar18,param_3,param_4,0xffffffffffffffff,puVar5);
    goto code_r0x020033b8;
  case 0xc:
    lVar17 = (*(code *)PTR__ZN4Aska4ACSV21EncodeDoubleQuotationEPKcmPcm_02c91c38)
                       (*param_1,param_1[1],param_3,param_4);
    return lVar17;
  default:
    lVar17 = -1;
    goto code_r0x020033bc;
  }
  lVar17 = -0x3c1;
  if (lVar8 < (long)param_4) {
code_r0x02003368:
    puVar5 = &UNK_02a3d191/*"%d"*/;
code_r0x02003370:
    iVar4 = __aska_snprintf_s(char*, unsigned long, unsigned long, char const*, ...)(param_3,param_4,0xffffffffffffffff,puVar5);
code_r0x020033b8:
    lVar17 = (long)iVar4;
  }
code_r0x020033bc:
  return lVar17;
}

// ==== long Aska::ACSV::PackTextValue<false>(Aska::ACSV::AValue const*, Aska::ACSV::Type, char*, unsigned long)
// vaddr 0x1f0341c | ghidra 0x200341c | size 1296 | symbol _ZN4Aska4ACSV13PackTextValueILb0EEElPKNS0_6AValueENS0_4TypeEPcm | lib libSOA-3.7.0.so | 2026-10-04
double _ZN4Aska4ACSV13PackTextValueILb0EEElPKNS0_6AValueENS0_4TypeEPcm
                 (double *param_1,undefined4 param_2,undefined4 *param_3,double param_4)

{
  bool bVar1;
  ulong uVar2;
  double dVar3;
  byte bVar4;
  ushort uVar5;
  int iVar6;
  double dVar7;
  undefined *puVar8;
  uint uVar9;
  long lVar10;
  char cVar11;
  short sVar13;
  uint uVar15;
  float fVar16;
  float fVar17;
  double dVar18;
  double dVar19;
  double dVar20;
  undefined1 auStack_80 [64];
  char cVar12;
  short sVar14;
  
  dVar19 = 0.0;
  switch(param_2) {
  case 0:
    goto code_r0x0200389c;
  case 1:
    if (*(byte *)param_1 == 0) {
      if ((ulong)param_4 < 5) {
        return -NAN;
      }
      if (param_4 != 2.47032822920623e-323) {
        *param_3 = 0x534c4146;
        *(undefined2 *)(param_3 + 1) = 0x45;
        return 2.47032822920623e-323;
      }
      raise(5);
      return 2.47032822920623e-323;
    }
    if ((ulong)param_4 < 4) {
      return -NAN;
    }
    if (param_4 != 1.97626258336499e-323) {
      *(undefined1 *)(param_3 + 1) = 0;
      *param_3 = 0x45555254;
      return 1.97626258336499e-323;
    }
    raise(5);
    return 1.97626258336499e-323;
  case 2:
    bVar4 = *(byte *)param_1;
    cVar12 = '\0';
    cVar11 = '\0';
    uVar9 = (uint)bVar4;
    if (bVar4 != 0) {
      do {
        uVar15 = uVar9 + 9;
        uVar9 = (int)(char)uVar9 / 10;
        cVar11 = cVar12 + '\x01';
        cVar12 = cVar11;
      } while (0x12 < (uVar15 & 0xff));
    }
    if ((ulong)param_4 < 2) {
      return -NAN;
    }
    lVar10 = (long)(char)(cVar11 - ((char)bVar4 >> 7));
    break;
  case 3:
    if (*(byte *)param_1 == 0) {
      uVar9 = 0;
    }
    else {
      uVar9 = 0;
      uVar15 = (uint)*(byte *)param_1;
      do {
        uVar9 = uVar9 + 1;
        bVar1 = 9 < uVar15;
        uVar15 = uVar15 / 10;
      } while (bVar1);
    }
    if ((ulong)param_4 < 2) {
      return -NAN;
    }
    uVar9 = uVar9 & 0xff;
    goto code_r0x020037d4;
  case 4:
    uVar5 = *(ushort *)param_1;
    sVar14 = 0;
    sVar13 = 0;
    uVar9 = (uint)uVar5;
    if (uVar5 != 0) {
      do {
        uVar15 = uVar9 + 9;
        uVar9 = (int)(short)uVar9 / 10;
        sVar13 = sVar14 + 1;
        sVar14 = sVar13;
      } while (0x12 < (uVar15 & 0xffff));
    }
    if ((ulong)param_4 < 2) {
      return -NAN;
    }
    lVar10 = (long)(short)(sVar13 - ((short)uVar5 >> 0xf));
    break;
  case 5:
    if (*(ushort *)param_1 == 0) {
      uVar9 = 0;
    }
    else {
      uVar9 = 0;
      uVar15 = (uint)*(ushort *)param_1;
      do {
        uVar9 = uVar9 + 1;
        bVar1 = 9 < uVar15;
        uVar15 = uVar15 / 10;
      } while (bVar1);
    }
    if ((ulong)param_4 < 2) {
      return -NAN;
    }
    uVar9 = uVar9 & 0xffff;
code_r0x020037d4:
    if ((ulong)param_4 <= (ulong)uVar9) {
      return -NAN;
    }
    goto code_r0x02003800;
  case 6:
    fVar17 = *(float *)param_1;
    if (fVar17 == 0.0) {
      iVar6 = 0;
    }
    else {
      iVar6 = 0;
      fVar16 = fVar17;
      do {
        uVar9 = (int)fVar16 + 9;
        fVar16 = (float)((int)fVar16 / 10);
        iVar6 = iVar6 + 1;
      } while (0x12 < uVar9);
    }
    if ((ulong)param_4 < 2) {
      return -NAN;
    }
    lVar10 = (long)(iVar6 - ((int)fVar17 >> 0x1f));
    break;
  case 7:
    if (*(float *)param_1 == 0.0) {
      dVar19 = 0.0;
    }
    else {
      uVar9 = 0;
      fVar17 = *(float *)param_1;
      do {
        uVar9 = uVar9 + 1;
        bVar1 = 9 < (uint)fVar17;
        fVar17 = (float)((uint)fVar17 / 10);
      } while (bVar1);
      dVar19 = (double)(ulong)uVar9;
    }
    if ((ulong)param_4 < 2) {
      return -NAN;
    }
    if ((ulong)param_4 <= (ulong)dVar19) {
      return -NAN;
    }
    puVar8 = &UNK_027e6d32/*"%u"*/;
    goto code_r0x02003808;
  case 8:
    dVar19 = *param_1;
    if (dVar19 == 0.0) {
      lVar10 = 0;
    }
    else {
      lVar10 = 0;
      dVar18 = dVar19;
      do {
        uVar2 = (long)dVar18 + 9;
        lVar10 = lVar10 + 1;
        dVar18 = (double)((long)dVar18 / 10);
      } while (0x12 < uVar2);
    }
    if ((ulong)param_4 < 2) {
      return -NAN;
    }
    if ((long)param_4 <= lVar10 - ((long)dVar19 >> 0x3f)) {
      return -NAN;
    }
    puVar8 = &UNK_029dd0e4/*"%lld"*/;
    goto code_r0x02003888;
  case 9:
    if (*param_1 == 0.0) {
      dVar19 = 4.94065645841247e-324;
    }
    else {
      dVar19 = 4.94065645841247e-324;
      dVar18 = *param_1;
      do {
        dVar19 = (double)((long)dVar19 + 1);
        bVar1 = 9 < (ulong)dVar18;
        dVar18 = (double)((ulong)dVar18 / 10);
      } while (bVar1);
    }
    if ((ulong)param_4 < 2) {
      return -NAN;
    }
    if ((ulong)param_4 < (ulong)dVar19) {
      return -NAN;
    }
    puVar8 = &UNK_029df1a7/*"%llu"*/;
code_r0x02003888:
    iVar6 = __aska_snprintf_s(char*, unsigned long, unsigned long, char const*, ...)(param_3,param_4,0xffffffffffffffff,puVar8);
    goto code_r0x02003898;
  case 10:
    iVar6 = __aska_snprintf_s(char*, unsigned long, unsigned long, char const*, ...)((double)*(float *)param_1,auStack_80,0x40,0xffffffffffffffff,
                            &UNK_029622c1/*"%f"*/);
    if ((ulong)param_4 < 2) {
      return -NAN;
    }
    if (SUB84(param_4,0) <= iVar6) {
      return -NAN;
    }
    puVar8 = &UNK_029622c1/*"%f"*/;
    dVar19 = (double)*(float *)param_1;
    goto code_r0x02003728;
  case 0xb:
    iVar6 = __aska_snprintf_s(char*, unsigned long, unsigned long, char const*, ...)(*param_1,auStack_80,0x40,0xffffffffffffffff,&UNK_0295c70e/*"%lf"*/);
    if ((ulong)param_4 < 2) {
      return -NAN;
    }
    if (SUB84(param_4,0) <= iVar6) {
      return -NAN;
    }
    dVar19 = *param_1;
    puVar8 = &UNK_0295c70e/*"%lf"*/;
code_r0x02003728:
    iVar6 = __aska_snprintf_s(char*, unsigned long, unsigned long, char const*, ...)(dVar19,param_3,param_4,0xffffffffffffffff,puVar8);
    goto code_r0x02003898;
  case 0xc:
    dVar19 = param_1[1];
    if ((ulong)param_4 < (ulong)dVar19) {
      return -NAN;
    }
    dVar20 = *param_1;
    dVar7 = (double)strlen(dVar20);
    dVar18 = (double)((long)dVar7 + 1);
    if (dVar19 != -NAN) {
      if (dVar18 != dVar19) {
        dVar7 = dVar18;
      }
      dVar3 = dVar19;
      if ((ulong)dVar18 <= (ulong)dVar19) {
        dVar3 = dVar7;
      }
      if ((ulong)param_4 <= (ulong)dVar3) {
        raise(5);
        return param_1[1];
      }
      strncpy(param_3,dVar20,dVar3);
      if ((ulong)dVar19 <= (ulong)dVar18) {
        *(undefined1 *)((long)param_3 + (long)dVar3) = 0;
      }
      return param_1[1];
    }
    if ((ulong)dVar18 <= (ulong)param_4) {
      param_4 = dVar18;
    }
    strncpy(param_3,dVar20,param_4);
    return param_1[1];
  default:
    dVar19 = -NAN;
    goto code_r0x0200389c;
  }
  dVar19 = -NAN;
  if (lVar10 < (long)param_4) {
code_r0x02003800:
    puVar8 = &UNK_02a3d191/*"%d"*/;
code_r0x02003808:
    iVar6 = __aska_snprintf_s(char*, unsigned long, unsigned long, char const*, ...)(param_3,param_4,0xffffffffffffffff,puVar8);
code_r0x02003898:
    dVar19 = (double)(long)iVar6;
  }
code_r0x0200389c:
  return dVar19;
}

// ==== bool Aska::ACSV::UnpackTextValue<true>(char const*, unsigned long, Aska::ACSV::AValue*, Aska::ACSV::Type, char, bool*)
// vaddr 0x1f0392c | ghidra 0x200392c | size 828 | symbol _ZN4Aska4ACSV15UnpackTextValueILb1EEEbPKcmPNS0_6AValueENS0_4TypeEcPb | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska4ACSV15UnpackTextValueILb1EEEbPKcmPNS0_6AValueENS0_4TypeEcPb
          (byte *param_1,ulong param_2,float *param_3,undefined4 param_4,byte param_5,
          undefined1 *param_6)

{
  byte bVar1;
  double dVar2;
  undefined1 uVar3;
  undefined2 uVar4;
  float fVar5;
  int iVar6;
  undefined8 uVar7;
  undefined1 auStack_18 [8];
  
  switch(param_4) {
  case 0:
    if ((param_2 != 0) ||
       ((bVar1 = *param_1, bVar1 != param_5 &&
        ((0xd < bVar1 || ((1 << (ulong)(bVar1 & 0x1f) & 0x2401U) == 0)))))) {
      *param_6 = 0;
      return 0;
    }
    goto code_r0x02003c14;
  case 1:
    if (param_2 == 0) {
code_r0x02003a38:
      *param_6 = 1;
      *(undefined1 *)param_3 = 0;
      return 1;
    }
    *param_6 = 0;
    if (((param_2 != 1) && (*param_1 != 0x30)) &&
       ((param_2 != 5 ||
        ((iVar6 = strncmp(param_1,&UNK_02866b5d/*"FALSE"*/,5), iVar6 != 0 &&
         (iVar6 = strncmp(param_1,&UNK_02941a92/*"false"*/,5), iVar6 != 0)))))) {
      *(undefined1 *)param_3 = 1;
      return 1;
    }
    *(undefined1 *)param_3 = 0;
    break;
  case 2:
  case 3:
    if (param_2 == 0) goto code_r0x02003a38;
    *param_6 = 0;
    if (((param_2 < 3) || (*param_1 != 0x30)) || (param_1[1] != 0x78)) {
      uVar3 = atoi(param_1);
      *(undefined1 *)param_3 = uVar3;
    }
    else {
      uVar3 = strtol(param_1,auStack_18,0x10);
      *(undefined1 *)param_3 = uVar3;
    }
    break;
  case 4:
  case 5:
    if (param_2 == 0) {
      *param_6 = 1;
      *(undefined2 *)param_3 = 0;
      return 1;
    }
    *param_6 = 0;
    if (((param_2 < 3) || (*param_1 != 0x30)) || (param_1[1] != 0x78)) {
      uVar4 = atoi(param_1);
      *(undefined2 *)param_3 = uVar4;
    }
    else {
      uVar4 = strtol(param_1,auStack_18,0x10);
      *(undefined2 *)param_3 = uVar4;
    }
    break;
  case 6:
    if (param_2 == 0) {
code_r0x02003b40:
      *param_6 = 1;
      *param_3 = 0.0;
      return 1;
    }
    *param_6 = 0;
    if (((param_2 < 3) || (*param_1 != 0x30)) || (param_1[1] != 0x78)) {
      fVar5 = (float)atoi(param_1);
      *param_3 = fVar5;
    }
    else {
      fVar5 = (float)strtol(param_1,auStack_18,0x10);
      *param_3 = fVar5;
    }
    break;
  case 7:
    if (param_2 == 0) goto code_r0x02003b40;
    *param_6 = 0;
    if (((param_2 < 3) || (*param_1 != 0x30)) || (param_1[1] != 0x78)) {
      uVar7 = 10;
    }
    else {
      uVar7 = 0x10;
    }
    fVar5 = (float)strtoul(param_1,auStack_18,uVar7);
    *param_3 = fVar5;
    break;
  case 8:
    if (param_2 == 0) goto code_r0x02003c14;
    *param_6 = 0;
    if (((param_2 < 3) || (*param_1 != 0x30)) || (param_1[1] != 0x78)) {
      uVar7 = 10;
    }
    else {
      uVar7 = 0x10;
    }
    uVar7 = strtol(param_1,auStack_18,uVar7);
    goto code_r0x02003bd8;
  case 9:
    if (param_2 == 0) goto code_r0x02003c14;
    *param_6 = 0;
    if (((param_2 < 3) || (*param_1 != 0x30)) || (param_1[1] != 0x78)) {
      uVar7 = 10;
    }
    else {
      uVar7 = 0x10;
    }
    uVar7 = strtoul(param_1,auStack_18,uVar7);
code_r0x02003bd8:
    *(undefined8 *)param_3 = uVar7;
    break;
  case 10:
    if (param_2 == 0) goto code_r0x02003b40;
    *param_6 = 0;
    dVar2 = (double)atof(param_1);
    *param_3 = (float)dVar2;
    break;
  case 0xb:
    if (param_2 != 0) {
      *param_6 = 0;
      uVar7 = atof(param_1);
      *(undefined8 *)param_3 = uVar7;
      return 1;
    }
code_r0x02003c14:
    *param_6 = 1;
    param_3[0] = 0.0;
    param_3[1] = 0.0;
    return 1;
  case 0xc:
    *param_6 = param_2 == 0;
    *(byte **)param_3 = param_1;
    *(ulong *)(param_3 + 2) = param_2;
    break;
  default:
    return 0;
  }
  return 1;
}

// ==== bool Aska::ACSV::UnpackTextValue<false>(char const*, unsigned long, Aska::ACSV::AValue*, Aska::ACSV::Type, char, bool*)
// vaddr 0x1f03c68 | ghidra 0x2003c68 | size 736 | symbol _ZN4Aska4ACSV15UnpackTextValueILb0EEEbPKcmPNS0_6AValueENS0_4TypeEcPb | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska4ACSV15UnpackTextValueILb0EEEbPKcmPNS0_6AValueENS0_4TypeEcPb
          (byte *param_1,ulong param_2,float *param_3,undefined4 param_4,byte param_5)

{
  byte bVar1;
  double dVar2;
  undefined1 uVar3;
  undefined2 uVar4;
  float fVar5;
  int iVar6;
  undefined8 uVar7;
  undefined1 auStack_18 [8];
  
  switch(param_4) {
  case 0:
    if (param_2 != 0) {
      return 0;
    }
    bVar1 = *param_1;
    if (bVar1 != param_5) {
      if (0xd < bVar1) {
        return 0;
      }
      if ((1 << (ulong)(bVar1 & 0x1f) & 0x2401U) == 0) {
        return 0;
      }
    }
    break;
  case 1:
    if ((((param_2 != 1) && (param_2 != 0)) && (*param_1 != 0x30)) &&
       ((param_2 != 5 ||
        ((iVar6 = strncmp(param_1,&UNK_02866b5d/*"FALSE"*/,5), iVar6 != 0 &&
         (iVar6 = strncmp(param_1,&UNK_02941a92/*"false"*/,5), iVar6 != 0)))))) {
      *(undefined1 *)param_3 = 1;
      return 1;
    }
    goto code_r0x02003d54;
  case 2:
  case 3:
    if (param_2 != 0) {
      if (((2 < param_2) && (*param_1 == 0x30)) && (param_1[1] == 0x78)) {
        uVar3 = strtol(param_1,auStack_18,0x10);
        *(undefined1 *)param_3 = uVar3;
        return 1;
      }
      uVar3 = atoi(param_1);
      *(undefined1 *)param_3 = uVar3;
      return 1;
    }
code_r0x02003d54:
    *(undefined1 *)param_3 = 0;
    return 1;
  case 4:
  case 5:
    if (param_2 == 0) {
      *(undefined2 *)param_3 = 0;
      return 1;
    }
    if (((2 < param_2) && (*param_1 == 0x30)) && (param_1[1] == 0x78)) {
      uVar4 = strtol(param_1,auStack_18,0x10);
      *(undefined2 *)param_3 = uVar4;
      return 1;
    }
    uVar4 = atoi(param_1);
    *(undefined2 *)param_3 = uVar4;
    return 1;
  case 6:
    if (param_2 != 0) {
      if (((2 < param_2) && (*param_1 == 0x30)) && (param_1[1] == 0x78)) {
        fVar5 = (float)strtol(param_1,auStack_18,0x10);
        *param_3 = fVar5;
        return 1;
      }
      fVar5 = (float)atoi(param_1);
      *param_3 = fVar5;
      return 1;
    }
    goto code_r0x02003e40;
  case 7:
    if (param_2 != 0) {
      if (((param_2 < 3) || (*param_1 != 0x30)) || (param_1[1] != 0x78)) {
        uVar7 = 10;
      }
      else {
        uVar7 = 0x10;
      }
      fVar5 = (float)strtoul(param_1,auStack_18,uVar7);
      *param_3 = fVar5;
      return 1;
    }
    goto code_r0x02003e40;
  case 8:
    if (param_2 != 0) {
      if (((param_2 < 3) || (*param_1 != 0x30)) || (param_1[1] != 0x78)) {
        uVar7 = 10;
      }
      else {
        uVar7 = 0x10;
      }
      uVar7 = strtol(param_1,auStack_18,uVar7);
      *(undefined8 *)param_3 = uVar7;
      return 1;
    }
    break;
  case 9:
    if (param_2 != 0) {
      if (((param_2 < 3) || (*param_1 != 0x30)) || (param_1[1] != 0x78)) {
        uVar7 = 10;
      }
      else {
        uVar7 = 0x10;
      }
      uVar7 = strtoul(param_1,auStack_18,uVar7);
      *(undefined8 *)param_3 = uVar7;
      return 1;
    }
    break;
  case 10:
    if (param_2 != 0) {
      dVar2 = (double)atof(param_1);
      *param_3 = (float)dVar2;
      return 1;
    }
code_r0x02003e40:
    *param_3 = 0.0;
    return 1;
  case 0xb:
    if (param_2 != 0) {
      uVar7 = atof(param_1);
      *(undefined8 *)param_3 = uVar7;
      return 1;
    }
    break;
  case 0xc:
    *(byte **)param_3 = param_1;
    *(ulong *)(param_3 + 2) = param_2;
    return 1;
  default:
    return 0;
  }
  param_3[0] = 0.0;
  param_3[1] = 0.0;
  return 1;
}

// ==== Aska::ACSV::UnpackTextType(char const*, unsigned long, Aska::ACSV::PriorityContext*)
// vaddr 0x1f03f48 | ghidra 0x2003f48 | size 604 | symbol _ZN4Aska4ACSV14UnpackTextTypeEPKcmPNS0_15PriorityContextE | lib libSOA-3.7.0.so | 2026-10-04
undefined4
_ZN4Aska4ACSV14UnpackTextTypeEPKcmPNS0_15PriorityContextE(char *param_1,ulong param_2,long *param_3)

{
  bool bVar1;
  bool bVar2;
  int iVar3;
  long lVar4;
  undefined *puVar5;
  undefined8 uVar6;
  ulong uVar7;
  undefined4 uVar8;
  char cVar9;
  undefined1 auStack_28 [8];
  
  if ((param_2 == 0) || (cVar9 = *param_1, cVar9 == '\0')) {
    return 0;
  }
  if (param_2 == 5) {
    puVar5 = &UNK_02866b5d/*"FALSE"*/;
    uVar6 = 5;
code_r0x02003fac:
    iVar3 = strncmp(param_1,puVar5,uVar6);
    if (iVar3 == 0) {
      return 1;
    }
  }
  else {
    if (param_2 == 4) {
      puVar5 = &UNK_0296dbc8/*"TRUE"*/;
      uVar6 = 4;
      goto code_r0x02003fac;
    }
    if (param_2 < 3) goto code_r0x02004030;
  }
  if (cVar9 == '0') {
    if (param_1[1] == 'x') {
      uVar7 = 2;
      do {
        if (0x36 < (int)param_1[uVar7] - 0x30U) {
          return 0xc;
        }
        if ((1L << ((ulong)((int)param_1[uVar7] - 0x30U) & 0x3f) & 0x7e0000007e03ffU) == 0) {
          return 0xc;
        }
        uVar7 = uVar7 + 1;
      } while (uVar7 < param_2);
      lVar4 = strtol(param_1,auStack_28,0x10);
joined_r0x02004024:
      if ((param_3 != (long *)0x0) && (*param_3 < lVar4)) {
        *param_3 = lVar4;
      }
      if (lVar4 < 0x100) {
        uVar8 = 3;
      }
      else if (lVar4 < 0x10000) {
        uVar8 = 5;
      }
      else {
        uVar8 = 7;
        if (0xffffffff < lVar4) {
          uVar8 = 9;
        }
      }
code_r0x02003f90:
      return uVar8;
    }
    cVar9 = '0';
  }
code_r0x02004030:
  iVar3 = 0;
  bVar1 = false;
  bVar2 = false;
  uVar7 = 1;
  uVar8 = 0xc;
  do {
    switch(cVar9) {
    case '+':
      if (uVar7 != 1) {
        return 0xc;
      }
      break;
    default:
      goto code_r0x02003f90;
    case '-':
      if (uVar7 != 1) {
        return 0xc;
      }
      bVar2 = true;
      if (param_2 < 2) goto code_r0x020040bc;
      goto code_r0x02004050;
    case '.':
      if (bVar1) {
        return 0xc;
      }
      bVar1 = true;
      break;
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      iVar3 = iVar3 + 1;
    }
    if (param_2 <= uVar7) {
code_r0x020040bc:
      if (bVar1) {
        if (7 < iVar3) {
          return 0xb;
        }
        return 10;
      }
      if (bVar2) {
        if (param_3 == (long *)0x0) {
          lVar4 = atol(param_1);
        }
        else {
          *(undefined1 *)(param_3 + 1) = 1;
          lVar4 = atol(param_1);
          if (*param_3 < -lVar4) {
            *param_3 = -lVar4;
          }
        }
        if (-0x81 < lVar4) {
          return 2;
        }
        if (-0x8001 < lVar4) {
          return 4;
        }
        if (lVar4 < -0x80000000) {
          return 8;
        }
        return 6;
      }
      lVar4 = atol(param_1);
      goto joined_r0x02004024;
    }
code_r0x02004050:
    cVar9 = param_1[uVar7];
    uVar7 = uVar7 + 1;
  } while( true );
}


// FAILED to create function at 02baee88 Aska::ACSV::vtable
// FAILED to create function at 02baf0d0 Aska::ACSV::typeinfo
