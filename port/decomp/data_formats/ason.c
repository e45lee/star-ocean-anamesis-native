// port/decomp/data_formats/ason.c: Ghidra decompiles for the data_formats subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-04 05:13 UTC: tools/decomp.sh '--into' 'data_formats/ason' 'Aska::ASON::' 'Aska::TStack<Aska::ASON'

// ==== Aska::ASON::AValue::SetString(char const*, Aska::ASON*)
// vaddr 0x148ed90 | ghidra 0x158ed90 | size 320 | symbol _ZN4Aska4ASON6AValue9SetStringEPKcPS0_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska4ASON6AValue9SetStringEPKcPS0_
               (undefined8 *param_1,undefined4 *param_2,long param_3,long param_4)

{
  ulong uVar1;
  ulong uVar2;
  uint uVar3;
  long lVar4;
  ulong uVar5;
  undefined8 uVar6;
  ulong uVar7;
  
  if (param_3 == 0) {
    uVar6 = 0xfffffffffffffc43;
  }
  else {
    uVar3 = strlen(param_3);
    *param_2 = 5;
    if (uVar3 == 0) {
      uVar6 = 0;
      *(undefined8 *)(param_2 + 4) = 0;
      *(undefined8 *)(param_2 + 6) = 0xffffffff00000000;
      *(undefined8 *)(param_2 + 2) = 0;
    }
    else {
      uVar7 = (ulong)uVar3;
      lVar4 = Aska::ASON::Malloc(unsigned long)(param_4,uVar7);
      *(long *)(param_2 + 2) = lVar4;
      if (lVar4 != 0) {
        *(undefined2 *)(param_2 + 7) = *(undefined2 *)(param_4 + 0x58);
        memcpy(lVar4,param_3,uVar7);
        param_2[6] = uVar3;
        if (*(char *)(param_4 + 0x88) == '\0') {
          uVar6 = 0;
          *(undefined8 *)(param_2 + 4) = 0;
          *(undefined2 *)((long)param_2 + 0x1e) = 0xffff;
          goto code_r0x0158eeb8;
        }
        lVar4 = Aska::ASON::Malloc(unsigned long)(param_4,(ulong)(uVar3 + 1));
        *(long *)(param_2 + 4) = lVar4;
        if (lVar4 != 0) {
          *(undefined2 *)((long)param_2 + 0x1e) = *(undefined2 *)(param_4 + 0x58);
          uVar5 = strlen(param_3);
          uVar1 = uVar5 + 1;
          if (uVar1 != uVar7) {
            uVar5 = uVar5 + 1;
          }
          uVar2 = uVar7;
          if (uVar1 <= uVar7) {
            uVar2 = uVar5;
          }
          if (uVar2 < uVar3 + 1) {
            strncpy(lVar4,param_3,uVar2);
            if (uVar1 < uVar7) {
              uVar6 = 0;
            }
            else {
              uVar6 = 0;
              *(undefined1 *)(lVar4 + uVar2) = 0;
            }
          }
          else {
            raise(5);
            uVar6 = 0;
          }
          goto code_r0x0158eeb8;
        }
      }
      uVar6 = 0xfffffffffffffc41;
    }
  }
code_r0x0158eeb8:
  *param_1 = uVar6;
  return;
}

// ==== Aska::TStack<Aska::ASON::AValue*, 10>::CopyElement(Aska::ASON::AValue* const*, Aska::ASON::AValue**)
// vaddr 0x14ac47c | ghidra 0x15ac47c | size 16 | symbol _ZN4Aska6TStackIPNS_4ASON6AValueELi10EE11CopyElementEPKS3_PS3_ | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska6TStackIPNS_4ASON6AValueELi10EE11CopyElementEPKS3_PS3_
          (undefined8 param_1,undefined8 *param_2,undefined8 *param_3)

{
  *param_3 = *param_2;
  return 1;
}

// ==== Aska::TStack<Aska::ASON::AValue*, 10>::~TStack()
// vaddr 0x14ac48c | ghidra 0x15ac48c | size 80 | symbol _ZN4Aska6TStackIPNS_4ASON6AValueELi10EED2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6TStackIPNS_4ASON6AValueELi10EED2Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska6TStackIPNS_4ASON6AValueELi10EEE_02cc3888 + 0x10);
  if ((long *)param_1[0xb] != param_1 + 1) {
    if ((long *)param_1[0xb] != (long *)0x0) {
      operator delete[](void*)();
    }
    param_1[0xb] = (long)(param_1 + 1);
  }
  param_1[0xc] = -0xfffffff6;
  return;
}

// ==== Aska::TStack<Aska::ASON::AValue*, 10>::~TStack()
// vaddr 0x14ac4dc | ghidra 0x15ac4dc | size 60 | symbol _ZN4Aska6TStackIPNS_4ASON6AValueELi10EED0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6TStackIPNS_4ASON6AValueELi10EED0Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska6TStackIPNS_4ASON6AValueELi10EEE_02cc3888 + 0x10);
  if (((long *)param_1[0xb] != param_1 + 1) && ((long *)param_1[0xb] != (long *)0x0)) {
    operator delete[](void*)();
  }
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::TStack<Aska::ASON::AValue::AMap*, 10>::CopyElement(Aska::ASON::AValue::AMap* const*, Aska::ASON::AValue::AMap**)
// vaddr 0x14ac518 | ghidra 0x15ac518 | size 16 | symbol _ZN4Aska6TStackIPNS_4ASON6AValue4AMapELi10EE11CopyElementEPKS4_PS4_ | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska6TStackIPNS_4ASON6AValue4AMapELi10EE11CopyElementEPKS4_PS4_
          (undefined8 param_1,undefined8 *param_2,undefined8 *param_3)

{
  *param_3 = *param_2;
  return 1;
}

// ==== Aska::TStack<Aska::ASON::AValue::AMap*, 10>::~TStack()
// vaddr 0x14ac528 | ghidra 0x15ac528 | size 80 | symbol _ZN4Aska6TStackIPNS_4ASON6AValue4AMapELi10EED2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6TStackIPNS_4ASON6AValue4AMapELi10EED2Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska6TStackIPNS_4ASON6AValue4AMapELi10EEE_02cc3dc8 + 0x10);
  if ((long *)param_1[0xb] != param_1 + 1) {
    if ((long *)param_1[0xb] != (long *)0x0) {
      operator delete[](void*)();
    }
    param_1[0xb] = (long)(param_1 + 1);
  }
  param_1[0xc] = -0xfffffff6;
  return;
}

// ==== Aska::TStack<Aska::ASON::AValue::AMap*, 10>::~TStack()
// vaddr 0x14ac578 | ghidra 0x15ac578 | size 60 | symbol _ZN4Aska6TStackIPNS_4ASON6AValue4AMapELi10EED0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6TStackIPNS_4ASON6AValue4AMapELi10EED0Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska6TStackIPNS_4ASON6AValue4AMapELi10EEE_02cc3dc8 + 0x10);
  if (((long *)param_1[0xb] != param_1 + 1) && ((long *)param_1[0xb] != (long *)0x0)) {
    operator delete[](void*)();
  }
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::TStack<Aska::ASON::AValue::AArray*, 10>::CopyElement(Aska::ASON::AValue::AArray* const*, Aska::ASON::AValue::AArray**)
// vaddr 0x14ac5b4 | ghidra 0x15ac5b4 | size 16 | symbol _ZN4Aska6TStackIPNS_4ASON6AValue6AArrayELi10EE11CopyElementEPKS4_PS4_ | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska6TStackIPNS_4ASON6AValue6AArrayELi10EE11CopyElementEPKS4_PS4_
          (undefined8 param_1,undefined8 *param_2,undefined8 *param_3)

{
  *param_3 = *param_2;
  return 1;
}

// ==== Aska::TStack<Aska::ASON::AValue::AArray*, 10>::~TStack()
// vaddr 0x14ac5c4 | ghidra 0x15ac5c4 | size 80 | symbol _ZN4Aska6TStackIPNS_4ASON6AValue6AArrayELi10EED2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6TStackIPNS_4ASON6AValue6AArrayELi10EED2Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska6TStackIPNS_4ASON6AValue6AArrayELi10EEE_02cbddd8 + 0x10);
  if ((long *)param_1[0xb] != param_1 + 1) {
    if ((long *)param_1[0xb] != (long *)0x0) {
      operator delete[](void*)();
    }
    param_1[0xb] = (long)(param_1 + 1);
  }
  param_1[0xc] = -0xfffffff6;
  return;
}

// ==== Aska::TStack<Aska::ASON::AValue::AArray*, 10>::~TStack()
// vaddr 0x14ac614 | ghidra 0x15ac614 | size 60 | symbol _ZN4Aska6TStackIPNS_4ASON6AValue6AArrayELi10EED0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6TStackIPNS_4ASON6AValue6AArrayELi10EED0Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska6TStackIPNS_4ASON6AValue6AArrayELi10EEE_02cbddd8 + 0x10);
  if (((long *)param_1[0xb] != param_1 + 1) && ((long *)param_1[0xb] != (long *)0x0)) {
    operator delete[](void*)();
  }
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::ASON::ASON()
// vaddr 0x1f0bff0 | ghidra 0x200bff0 | size 80 | symbol _ZN4Aska4ASONC2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska4ASONC1Ev(long *param_1)

{
  undefined *puVar1;
  
  *param_1 = (long)(PTR__ZTVN4Aska4ASONE_02cbd150 + 0x10);
  puVar1 = 
  PTR__ZTVN4Aska13TDynamicArrayINS_4ASON17WorkBufferContextENS_10TAllocatorIS2_EEEE_02cbd630;
  param_1[7] = 0;
  *(undefined4 *)(param_1 + 0xc) = 0;
  *(undefined2 *)(param_1 + 0xb) = 0;
  *(undefined1 *)((long)param_1 + 0x8a) = 0;
  *(undefined2 *)(param_1 + 0x11) = 0;
  param_1[2] = 0;
  param_1[1] = 0;
  param_1[6] = 0;
  param_1[5] = 0;
  param_1[10] = 0;
  param_1[9] = 0;
  param_1[0xe] = 0;
  param_1[0xd] = 0;
  param_1[3] = 0;
  param_1[4] = (long)(puVar1 + 0x10);
  param_1[0x10] = 0;
  param_1[0xf] = 0;
  return;
}

// ==== Aska::ASON::ASON(Aska::ASON const&)
// vaddr 0x1f0c040 | ghidra 0x200c040 | size 124 | symbol _ZN4Aska4ASONC2ERKS0_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska4ASONC1ERKS0_(long *param_1,long *param_2)

{
  undefined *puVar1;
  undefined *puVar2;
  long lVar3;
  
  puVar1 = PTR__ZTVN4Aska4ASONE_02cbd150;
  param_1[2] = 0;
  param_1[3] = 0;
  puVar2 = 
  PTR__ZTVN4Aska13TDynamicArrayINS_4ASON17WorkBufferContextENS_10TAllocatorIS2_EEEE_02cbd630;
  param_1[6] = 0;
  param_1[7] = 0;
  *param_1 = (long)(puVar1 + 0x10);
  param_1[1] = 0;
  param_1[4] = (long)(puVar2 + 0x10);
  param_1[5] = 0;
  *(undefined4 *)(param_1 + 0xc) = 0;
  param_1[0xe] = 0;
  param_1[0xf] = 0;
  param_1[0xd] = 0;
  if (param_2 != param_1) {
    param_1[0x10] = param_2[0x10];
    *(char *)(param_1 + 0x11) = (char)param_2[0x11];
    *(undefined1 *)((long)param_1 + 0x89) = *(undefined1 *)((long)param_2 + 0x89);
    *(undefined1 *)((long)param_1 + 0x8a) = *(undefined1 *)((long)param_2 + 0x8a);
    lVar3 = param_2[0xe];
    param_1[0xf] = param_2[0xf];
    param_1[0xe] = lVar3;
    lVar3 = param_2[0xc];
    param_1[0xd] = param_2[0xd];
    param_1[0xc] = lVar3;
    (*(code *)PTR__ZN4Aska4ASON11CopyMemory_ERKS0_b_02c9af28)(param_1,param_2,0);
    return;
  }
  return;
}

// ==== Aska::ASON::Copy(Aska::ASON const&, bool)
// vaddr 0x1f0c0bc | ghidra 0x200c0bc | size 72 | symbol _ZN4Aska4ASON4CopyERKS0_b | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska4ASON4CopyERKS0_b(long param_1,long param_2,uint param_3)

{
  undefined8 uVar1;
  
  if (param_2 != param_1) {
    *(undefined8 *)(param_1 + 0x80) = *(undefined8 *)(param_2 + 0x80);
    *(undefined1 *)(param_1 + 0x88) = *(undefined1 *)(param_2 + 0x88);
    *(undefined1 *)(param_1 + 0x89) = *(undefined1 *)(param_2 + 0x89);
    *(undefined1 *)(param_1 + 0x8a) = *(undefined1 *)(param_2 + 0x8a);
    uVar1 = *(undefined8 *)(param_2 + 0x70);
    *(undefined8 *)(param_1 + 0x78) = *(undefined8 *)(param_2 + 0x78);
    *(undefined8 *)(param_1 + 0x70) = uVar1;
    uVar1 = *(undefined8 *)(param_2 + 0x60);
    *(undefined8 *)(param_1 + 0x68) = *(undefined8 *)(param_2 + 0x68);
    *(undefined8 *)(param_1 + 0x60) = uVar1;
    uVar1 = (*(code *)PTR__ZN4Aska4ASON11CopyMemory_ERKS0_b_02c9af28)(param_1,param_2,param_3 & 1);
    return uVar1;
  }
  return 1;
}

// ==== Aska::ASON::ASON(Aska::MoveConstruct<Aska::ASON>)
// vaddr 0x1f0c104 | ghidra 0x200c104 | size 144 | symbol _ZN4Aska4ASONC1ENS_13MoveConstructIS0_EE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska4ASONC2ENS_13MoveConstructIS0_EE(long *param_1,long *param_2)

{
  undefined *puVar1;
  undefined *puVar2;
  long lVar3;
  
  puVar2 = PTR__ZTVN4Aska4ASONE_02cbd150;
  param_1[2] = 0;
  param_1[3] = 0;
  puVar1 = PTR__ZTVN4Aska13TDynamicArrayINS_4ASON17WorkBufferContextENS_10TAllocatorIS2_EEEE_02cbd630
           + 0x10;
  param_1[6] = 0;
  param_1[7] = 0;
  *param_1 = (long)(puVar2 + 0x10);
  param_1[1] = 0;
  param_1[4] = (long)puVar1;
  param_1[5] = 0;
  *(undefined4 *)(param_1 + 0xc) = 0;
  param_1[0xe] = 0;
  param_1[0xf] = 0;
  param_1[0xd] = 0;
  if (param_2 != param_1) {
    param_1[0x10] = param_2[0x10];
    *(char *)(param_1 + 0x11) = (char)param_2[0x11];
    *(undefined1 *)((long)param_1 + 0x89) = *(undefined1 *)((long)param_2 + 0x89);
    *(undefined1 *)((long)param_1 + 0x8a) = *(undefined1 *)((long)param_2 + 0x8a);
    lVar3 = param_2[0xe];
    param_1[0xf] = param_2[0xf];
    param_1[0xe] = lVar3;
    lVar3 = param_2[0xc];
    param_1[0xd] = param_2[0xd];
    param_1[0xc] = lVar3;
    Aska::ASON::MoveMemory_(Aska::ASON&, bool)(param_1,param_2,0);
    *(undefined1 *)((long)param_2 + 0x8a) = 0;
  }
  return;
}

// ==== Aska::ASON::Move(Aska::ASON&, bool)
// vaddr 0x1f0c194 | ghidra 0x200c194 | size 108 | symbol _ZN4Aska4ASON4MoveERS0_b | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska4ASON4MoveERS0_b(long param_1,long param_2,uint param_3)

{
  undefined8 uVar1;
  
  if (param_2 != param_1) {
    *(undefined8 *)(param_1 + 0x80) = *(undefined8 *)(param_2 + 0x80);
    *(undefined1 *)(param_1 + 0x88) = *(undefined1 *)(param_2 + 0x88);
    *(undefined1 *)(param_1 + 0x89) = *(undefined1 *)(param_2 + 0x89);
    *(undefined1 *)(param_1 + 0x8a) = *(undefined1 *)(param_2 + 0x8a);
    uVar1 = *(undefined8 *)(param_2 + 0x70);
    *(undefined8 *)(param_1 + 0x78) = *(undefined8 *)(param_2 + 0x78);
    *(undefined8 *)(param_1 + 0x70) = uVar1;
    uVar1 = *(undefined8 *)(param_2 + 0x60);
    *(undefined8 *)(param_1 + 0x68) = *(undefined8 *)(param_2 + 0x68);
    *(undefined8 *)(param_1 + 0x60) = uVar1;
    Aska::ASON::MoveMemory_(Aska::ASON&, bool)(param_1,param_2,param_3 & 1);
    *(undefined1 *)(param_2 + 0x8a) = 0;
  }
  return param_1;
}

// ==== Aska::ASON::~ASON()
// vaddr 0x1f0c200 | ghidra 0x200c200 | size 96 | symbol _ZN4Aska4ASOND1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska4ASOND2Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska4ASONE_02cbd150 + 0x10);
  Aska::ASON::Term()();
  param_1[4] = (long)(
                     PTR__ZTVN4Aska13TDynamicArrayINS_4ASON17WorkBufferContextENS_10TAllocatorIS2_EEEE_02cbd630
                     + 0x10);
  if (param_1[7] != param_1[5]) {
    Aska::MemoryManagerAdapter::AlignedFree(void*)();
    param_1[6] = 0;
    param_1[7] = 0;
    param_1[5] = 0;
  }
  (*(code *)PTR__ZN4Aska11IAnimatableD2Ev_02cb13b8)(param_1);
  return;
}

// ==== Aska::ASON::Term()
// vaddr 0x1f0c260 | ghidra 0x200c260 | size 276 | symbol _ZN4Aska4ASON4TermEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska4ASON4TermEv(long param_1)

{
  long *plVar1;
  long lVar2;
  undefined8 uVar3;
  ulong uVar4;
  long lVar5;
  long lVar6;
  long *plVar7;
  
  if (*(char *)(param_1 + 0x8a) != '\0') {
    lVar2 = *(long *)(param_1 + 0x28);
    lVar6 = *(long *)(param_1 + 0x30);
    *(undefined4 *)(param_1 + 0x60) = 0;
    *(undefined8 *)(param_1 + 0x68) = 0;
    *(undefined1 *)(param_1 + 0x89) = 0;
    uVar4 = lVar6 - lVar2 >> 5;
    if (1 < uVar4) {
      lVar5 = uVar4 - 1;
      do {
        if (*(char *)(lVar6 + -8) != '\0') {
          if (*(long *)(lVar6 + -0x20) != 0) {
            operator delete[](void*)();
          }
          *(undefined1 *)(lVar6 + -8) = 0;
        }
        *(undefined8 *)(lVar6 + -0x18) = 0;
        *(undefined8 *)(lVar6 + -0x10) = 0;
        *(long *)(lVar6 + -0x20) = 0;
        lVar2 = *(long *)(param_1 + 0x28);
        lVar6 = lVar2;
        if (lVar2 != *(long *)(param_1 + 0x30)) {
          lVar6 = *(long *)(param_1 + 0x30) + -0x20;
          *(long *)(param_1 + 0x30) = lVar6;
        }
        lVar5 = lVar5 + -1;
      } while (lVar5 != 0);
    }
    *(undefined8 *)(lVar2 + 0x10) = 0;
    *(long *)(param_1 + 0x48) = lVar2;
    uVar3 = *(undefined8 *)(lVar2 + 8);
    *(undefined2 *)(param_1 + 0x58) = 0;
    *(undefined8 *)(param_1 + 0x10) = 0;
    *(undefined8 *)(param_1 + 0x18) = 0;
    *(undefined8 *)(param_1 + 0x50) = uVar3;
    *(undefined8 *)(param_1 + 8) = 0;
    Aska::ASON::Malloc(unsigned long)(param_1,0x200);
    plVar7 = *(long **)(param_1 + 0x28);
    plVar1 = *(long **)(param_1 + 0x30);
    *(undefined8 *)(param_1 + 0x10) = 0;
    *(undefined8 *)(param_1 + 0x18) = 0;
    *(undefined8 *)(param_1 + 8) = 0;
    if (plVar7 != plVar1) {
      do {
        if (((char)plVar7[3] != '\0') && (*plVar7 != 0)) {
          operator delete[](void*)();
        }
        plVar7 = plVar7 + 4;
      } while (plVar1 != plVar7);
      plVar7 = *(long **)(param_1 + 0x28);
    }
    if (*(long **)(param_1 + 0x38) != plVar7) {
      *(long **)(param_1 + 0x30) = plVar7;
    }
    *(undefined2 *)(param_1 + 0x58) = 0;
    *(long *)(param_1 + 0x48) = 0;
    *(undefined8 *)(param_1 + 0x50) = 0;
    *(undefined1 *)(param_1 + 0x88) = 0;
    *(undefined1 *)(param_1 + 0x8a) = 0;
  }
  return;
}

// ==== Aska::ASON::~ASON()
// vaddr 0x1f0c3b0 | ghidra 0x200c3b0 | size 104 | symbol _ZN4Aska4ASOND0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska4ASOND0Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska4ASONE_02cbd150 + 0x10);
  Aska::ASON::Term()();
  param_1[4] = (long)(
                     PTR__ZTVN4Aska13TDynamicArrayINS_4ASON17WorkBufferContextENS_10TAllocatorIS2_EEEE_02cbd630
                     + 0x10);
  if (param_1[7] != param_1[5]) {
    Aska::MemoryManagerAdapter::AlignedFree(void*)();
    param_1[6] = 0;
    param_1[7] = 0;
    param_1[5] = 0;
  }
  Aska::IAnimatable::~IAnimatable()(param_1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::ASON::operator=(Aska::ASON const&)
// vaddr 0x1f0c418 | ghidra 0x200c418 | size 88 | symbol _ZN4Aska4ASONaSERKS0_ | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska4ASONaSERKS0_(long param_1,long param_2)

{
  undefined8 uVar1;
  
  if (param_2 != param_1) {
    *(undefined8 *)(param_1 + 0x80) = *(undefined8 *)(param_2 + 0x80);
    *(undefined1 *)(param_1 + 0x88) = *(undefined1 *)(param_2 + 0x88);
    *(undefined1 *)(param_1 + 0x89) = *(undefined1 *)(param_2 + 0x89);
    *(undefined1 *)(param_1 + 0x8a) = *(undefined1 *)(param_2 + 0x8a);
    uVar1 = *(undefined8 *)(param_2 + 0x70);
    *(undefined8 *)(param_1 + 0x78) = *(undefined8 *)(param_2 + 0x78);
    *(undefined8 *)(param_1 + 0x70) = uVar1;
    uVar1 = *(undefined8 *)(param_2 + 0x60);
    *(undefined8 *)(param_1 + 0x68) = *(undefined8 *)(param_2 + 0x68);
    *(undefined8 *)(param_1 + 0x60) = uVar1;
    Aska::ASON::CopyMemory_(Aska::ASON const&, bool)(param_1,param_2,0);
  }
  return param_1;
}

// ==== Aska::ASON::operator=(Aska::MoveConstruct<Aska::ASON>)
// vaddr 0x1f0c470 | ghidra 0x200c470 | size 8 | symbol _ZN4Aska4ASONaSENS_13MoveConstructIS0_EE | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska4ASONaSENS_13MoveConstructIS0_EE(undefined8 param_1,undefined8 param_2)

{
  return param_2;
}

// ==== Aska::ASON::CopyMemory_(Aska::ASON const&, bool)
// vaddr 0x1f0c478 | ghidra 0x200c478 | size 592 | symbol _ZN4Aska4ASON11CopyMemory_ERKS0_b | lib libSOA-3.7.0.so | 2026-10-04
uint _ZN4Aska4ASON11CopyMemory_ERKS0_b(long param_1,long param_2,uint param_3)

{
  long *plVar1;
  undefined *puVar2;
  uint uVar3;
  long lVar4;
  long lVar5;
  long *plVar6;
  undefined8 uVar7;
  long lVar8;
  ulong uVar9;
  ulong uVar10;
  long lVar11;
  long lStack_90;
  long lStack_88;
  undefined8 uStack_80;
  undefined1 uStack_78;
  undefined8 uStack_70;
  undefined1 *puStack_68;
  
  plVar6 = *(long **)(param_1 + 0x28);
  plVar1 = *(long **)(param_1 + 0x30);
  *(undefined8 *)(param_1 + 0x10) = 0;
  *(undefined8 *)(param_1 + 0x18) = 0;
  *(undefined8 *)(param_1 + 8) = 0;
  if (plVar6 != plVar1) {
    do {
      if (((char)plVar6[3] != '\0') && (*plVar6 != 0)) {
        operator delete[](void*)();
      }
      plVar6 = plVar6 + 4;
    } while (plVar1 != plVar6);
    plVar6 = *(long **)(param_1 + 0x28);
  }
  if (*(long **)(param_1 + 0x38) != plVar6) {
    *(long **)(param_1 + 0x30) = plVar6;
  }
  *(undefined2 *)(param_1 + 0x58) = 0;
  *(undefined8 *)(param_1 + 0x48) = 0;
  *(undefined8 *)(param_1 + 0x50) = 0;
  if (*(long *)(param_2 + 0x30) == *(long *)(param_2 + 0x28)) {
    uVar3 = 1;
  }
  else {
    uVar7 = *(undefined8 *)(*(long *)(param_2 + 0x28) + 8);
    lVar4 = operator new[](unsigned long, std::nothrow_t const&)(uVar7,PTR__ZSt7nothrow_02cb9a80);
    uVar3 = 0;
    if (lVar4 != 0) {
      Aska::ASON::InitMemory(signed char*, unsigned long, bool)(param_1,lVar4,uVar7,1);
      lVar4 = *(long *)(param_2 + 0x28);
      lVar11 = *(long *)(param_2 + 0x30);
      uVar9 = lVar11 - lVar4 >> 5;
      if (uVar9 < 2) {
code_r0x0200c5f0:
        lVar11 = lVar11 - lVar4 >> 5;
        if (lVar11 != 0) {
          lVar8 = 0;
          while( true ) {
            lVar11 = lVar11 + -1;
            *(undefined8 *)(*(long *)(param_1 + 0x28) + lVar8 + 0x10) =
                 *(undefined8 *)(lVar4 + lVar8 + 0x10);
            plVar6 = (long *)(*(long *)(param_1 + 0x28) + lVar8);
            lVar4 = *plVar6;
            if (lVar4 != 0) {
              plVar1 = (long *)(*(long *)(param_2 + 0x28) + lVar8);
              lVar5 = *plVar1;
              if (lVar5 == 0) {
                memset();
              }
              else {
                uVar9 = plVar1[1];
                if ((ulong)plVar6[1] < uVar9) {
                  memset(lVar4,0);
                }
                else {
                  memcpy(lVar4,lVar5,uVar9);
                }
              }
            }
            if (lVar11 == 0) break;
            lVar4 = *(long *)(param_2 + 0x28);
            lVar8 = lVar8 + 0x20;
          }
        }
        Aska::ASON::RelocateAValueRef(Aska::ASON::AValue*, Aska::TDynamicArray<Aska::ASON::WorkBufferContext, Aska::TAllocator<Aska::ASON::WorkBufferContext> > const&, bool)(&lStack_90,param_1,param_1 + 0x60,param_2 + 0x20,param_3 & 1);
        uVar3 = (uint)((ulong)lStack_90 >> 0x3f) ^ 1;
      }
      else {
        lVar4 = *(long *)(lVar4 + 0x28);
        lStack_90 = operator new[](unsigned long, std::nothrow_t const&)(lVar4,PTR__ZSt7nothrow_02cb9a80);
        puVar2 = PTR__ZSt7nothrow_02cb9a80;
        uVar3 = 0;
        if (lStack_90 != 0) {
          lVar11 = 0x48;
          uVar10 = 1;
          do {
            uStack_78 = 1;
            uStack_80 = 0;
            uStack_70 = 1;
            lStack_88 = lVar4;
            puStack_68 = (undefined1 *)&lStack_90;
            Aska::TArrayIterator<Aska::TDynamicArray<Aska::ASON::WorkBufferContext, Aska::TAllocator<Aska::ASON::WorkBufferContext> > > Aska::TDynamicArray<Aska::ASON::WorkBufferContext, Aska::TAllocator<Aska::ASON::WorkBufferContext> >::Insert_<Aska::Memory::TUninitializedFillN<Aska::ASON::WorkBufferContext> >(Aska::ASON::WorkBufferContext const*, unsigned long, Aska::Memory::TUninitializedFillN<Aska::ASON::WorkBufferContext> const&)(param_1 + 0x20,*(undefined8 *)(param_1 + 0x30),1,&uStack_70);
            uVar10 = uVar10 + 1;
            *(long *)(param_1 + 0x48) = *(long *)(param_1 + 0x30) + -0x20;
            *(long *)(param_1 + 0x50) = *(long *)(param_1 + 0x50) + lVar4;
            *(short *)(param_1 + 0x58) = *(short *)(param_1 + 0x58) + 1;
            if (uVar9 <= uVar10) {
              lVar4 = *(long *)(param_2 + 0x28);
              lVar11 = *(long *)(param_2 + 0x30);
              goto code_r0x0200c5f0;
            }
            lVar4 = *(long *)(*(long *)(param_2 + 0x28) + lVar11);
            lVar11 = lVar11 + 0x20;
            lStack_90 = operator new[](unsigned long, std::nothrow_t const&)(lVar4,puVar2);
          } while (lStack_90 != 0);
          uVar3 = 0;
        }
      }
    }
  }
  return uVar3;
}

// ==== Aska::ASON::MoveMemory_(Aska::ASON&, bool)
// vaddr 0x1f0c6c8 | ghidra 0x200c6c8 | size 524 | symbol _ZN4Aska4ASON11MoveMemory_ERS0_b | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska4ASON11MoveMemory_ERS0_b(long param_1,long param_2,ulong param_3)

{
  undefined *puVar1;
  long lVar2;
  long *plVar3;
  undefined8 *puVar4;
  long *plVar5;
  undefined8 uVar6;
  undefined *puStack_78;
  long lStack_70;
  undefined8 uStack_68;
  long lStack_60;
  long lStack_50;
  long lStack_48;
  
  puVar4 = (undefined8 *)(param_1 + 0x28);
  plVar3 = (long *)*puVar4;
  *(undefined8 *)(param_1 + 8) = 0;
  plVar5 = *(long **)(param_1 + 0x30);
  *(undefined8 *)(param_1 + 0x10) = 0;
  *(undefined8 *)(param_1 + 0x18) = 0;
  if (plVar3 != plVar5) {
    do {
      if (((char)plVar3[3] != '\0') && (*plVar3 != 0)) {
        operator delete[](void*)();
      }
      plVar3 = plVar3 + 4;
    } while (plVar5 != plVar3);
    plVar3 = (long *)*puVar4;
  }
  if (*(long **)(param_1 + 0x38) != plVar3) {
    *(long **)(param_1 + 0x30) = plVar3;
  }
  *(undefined2 *)(param_1 + 0x58) = 0;
  *(undefined8 *)(param_1 + 0x48) = 0;
  *(undefined8 *)(param_1 + 0x50) = 0;
  *(undefined8 *)(param_1 + 0x18) = *(undefined8 *)(param_2 + 0x18);
  uVar6 = *(undefined8 *)(param_2 + 8);
  *(undefined8 *)(param_1 + 0x10) = *(undefined8 *)(param_2 + 0x10);
  *(undefined8 *)(param_1 + 8) = uVar6;
  *(undefined8 *)(param_1 + 0x48) = *(undefined8 *)(param_2 + 0x48);
  *(undefined8 *)(param_1 + 0x50) = *(undefined8 *)(param_2 + 0x50);
  *(undefined2 *)(param_1 + 0x58) = *(undefined2 *)(param_2 + 0x58);
  if ((param_3 & 1) == 0) {
    if (param_2 != param_1) {
      if (*(long **)(param_1 + 0x38) != plVar3) {
        Aska::MemoryManagerAdapter::AlignedFree(void*)(plVar3);
        *(undefined8 *)(param_1 + 0x30) = 0;
        *(undefined8 *)(param_1 + 0x38) = 0;
        *puVar4 = 0;
      }
      *(undefined8 *)(param_1 + 0x28) = *(undefined8 *)(param_2 + 0x28);
      *(undefined8 *)(param_1 + 0x30) = *(undefined8 *)(param_2 + 0x30);
      *(undefined8 *)(param_1 + 0x38) = *(undefined8 *)(param_2 + 0x38);
      *(undefined8 *)(param_2 + 0x30) = 0;
      *(undefined8 *)(param_2 + 0x38) = 0;
      *(undefined8 *)(param_2 + 0x28) = 0;
    }
  }
  else {
    uStack_68 = 0;
    lStack_60 = 0;
    puVar1 = PTR__ZTVN4Aska13TDynamicArrayINS_4ASON17WorkBufferContextENS_10TAllocatorIS2_EEEE_02cbd630
             + 0x10;
    lStack_70 = 0;
    lStack_50 = *(long *)(param_2 + 0x28);
    lStack_48 = *(long *)(param_2 + 0x30);
    puStack_78 = puVar1;
    Aska::TArrayIterator<Aska::TDynamicArray<Aska::ASON::WorkBufferContext, Aska::TAllocator<Aska::ASON::WorkBufferContext> > > Aska::TDynamicArray<Aska::ASON::WorkBufferContext, Aska::TAllocator<Aska::ASON::WorkBufferContext> >::Insert_<Aska::Memory::TUninitializedCopy<Aska::ASON::WorkBufferContext*> >(Aska::ASON::WorkBufferContext const*, unsigned long, Aska::Memory::TUninitializedCopy<Aska::ASON::WorkBufferContext*> const&)(&puStack_78,0,lStack_48 - lStack_50 >> 5,&lStack_50);
    if (param_2 != param_1) {
      if (*(long *)(param_1 + 0x38) != *(long *)(param_1 + 0x28)) {
        Aska::MemoryManagerAdapter::AlignedFree(void*)();
        *(undefined8 *)(param_1 + 0x30) = 0;
        *(undefined8 *)(param_1 + 0x38) = 0;
        *puVar4 = 0;
      }
      *(undefined8 *)(param_1 + 0x28) = *(undefined8 *)(param_2 + 0x28);
      *(undefined8 *)(param_1 + 0x30) = *(undefined8 *)(param_2 + 0x30);
      *(undefined8 *)(param_1 + 0x38) = *(undefined8 *)(param_2 + 0x38);
      *(undefined8 *)(param_2 + 0x30) = 0;
      *(undefined8 *)(param_2 + 0x38) = 0;
      *(long *)(param_2 + 0x28) = 0;
    }
    Aska::ASON::RelocateAValueRef(Aska::ASON::AValue*, Aska::TDynamicArray<Aska::ASON::WorkBufferContext, Aska::TAllocator<Aska::ASON::WorkBufferContext> > const&, bool)(&lStack_50,param_1,param_1 + 0x60,&puStack_78,1);
    lVar2 = lStack_50;
    if (lStack_60 != lStack_70) {
      puStack_78 = puVar1;
      Aska::MemoryManagerAdapter::AlignedFree(void*)();
    }
    if (lVar2 < 0) {
      return 0;
    }
  }
  *(undefined8 *)(param_2 + 0x10) = 0;
  *(undefined8 *)(param_2 + 0x18) = 0;
  *(undefined8 *)(param_2 + 8) = 0;
  if (*(long *)(param_2 + 0x38) != *(long *)(param_2 + 0x28)) {
    *(long *)(param_2 + 0x30) = *(long *)(param_2 + 0x28);
  }
  *(undefined2 *)(param_2 + 0x58) = 0;
  *(undefined8 *)(param_2 + 0x48) = 0;
  *(undefined8 *)(param_2 + 0x50) = 0;
  return 1;
}

// ==== Aska::ASON::Swap(Aska::ASON&)
// vaddr 0x1f0c8d4 | ghidra 0x200c8d4 | size 472 | symbol _ZN4Aska4ASON4SwapERS0_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska4ASON4SwapERS0_(undefined1 *param_1,undefined1 *param_2)

{
  undefined *puVar1;
  undefined *puVar2;
  undefined8 uVar3;
  undefined *puStack_c0;
  undefined8 uStack_b8;
  undefined8 uStack_b0;
  undefined8 uStack_a8;
  undefined *puStack_a0;
  long lStack_98;
  undefined8 uStack_90;
  long lStack_88;
  undefined8 uStack_78;
  undefined8 uStack_70;
  undefined2 uStack_68;
  ulong uStack_60;
  undefined8 uStack_58;
  undefined8 uStack_50;
  undefined8 uStack_48;
  undefined8 uStack_40;
  undefined2 uStack_38;
  undefined1 uStack_36;
  
  puVar2 = 
  PTR__ZTVN4Aska13TDynamicArrayINS_4ASON17WorkBufferContextENS_10TAllocatorIS2_EEEE_02cbd630;
  puVar1 = PTR__ZTVN4Aska4ASONE_02cbd150;
  puStack_c0 = PTR__ZTVN4Aska4ASONE_02cbd150 + 0x10;
  puStack_a0 = PTR__ZTVN4Aska13TDynamicArrayINS_4ASON17WorkBufferContextENS_10TAllocatorIS2_EEEE_02cbd630
               + 0x10;
  uStack_a8 = 0;
  uStack_b0 = 0;
  uStack_b8 = 0;
  lStack_88 = 0;
  uStack_90 = 0;
  lStack_98 = 0;
  uStack_60 = uStack_60 & 0xffffffff00000000;
  uStack_70 = 0;
  uStack_78 = 0;
  uStack_68 = 0;
  uStack_50 = 0;
  uStack_58 = 0;
  uStack_36 = 0;
  uStack_38 = 0;
  uStack_40 = 0;
  uStack_48 = 0;
  if (&puStack_c0 != (undefined **)param_1) {
    uStack_40 = *(undefined8 *)(param_1 + 0x80);
    uStack_38 = *(undefined2 *)(param_1 + 0x88);
    uStack_36 = param_1[0x8a];
    uStack_48 = *(undefined8 *)(param_1 + 0x78);
    uStack_50 = *(undefined8 *)(param_1 + 0x70);
    uStack_58 = *(undefined8 *)(param_1 + 0x68);
    uStack_60 = *(ulong *)(param_1 + 0x60);
    uStack_a8 = *(undefined8 *)(param_1 + 0x18);
    uStack_b0 = *(undefined8 *)(param_1 + 0x10);
    uStack_b8 = *(undefined8 *)(param_1 + 8);
    uStack_70 = *(undefined8 *)(param_1 + 0x50);
    uStack_78 = *(undefined8 *)(param_1 + 0x48);
    uStack_68 = *(undefined2 *)(param_1 + 0x58);
    uStack_90 = *(undefined8 *)(param_1 + 0x30);
    lStack_98 = *(long *)(param_1 + 0x28);
    lStack_88 = *(long *)(param_1 + 0x38);
    *(undefined8 *)(param_1 + 0x30) = 0;
    *(undefined8 *)(param_1 + 0x38) = 0;
    *(undefined8 *)(param_1 + 0x28) = 0;
    *(undefined8 *)(param_1 + 0x10) = 0;
    *(undefined8 *)(param_1 + 0x18) = 0;
    *(undefined8 *)(param_1 + 8) = 0;
    *(undefined2 *)(param_1 + 0x58) = 0;
    *(undefined8 *)(param_1 + 0x48) = 0;
    *(undefined8 *)(param_1 + 0x50) = 0;
    param_1[0x8a] = 0;
  }
  if (param_2 != param_1) {
    *(undefined8 *)(param_1 + 0x80) = *(undefined8 *)(param_2 + 0x80);
    param_1[0x88] = param_2[0x88];
    param_1[0x89] = param_2[0x89];
    param_1[0x8a] = param_2[0x8a];
    uVar3 = *(undefined8 *)(param_2 + 0x70);
    *(undefined8 *)(param_1 + 0x78) = *(undefined8 *)(param_2 + 0x78);
    *(undefined8 *)(param_1 + 0x70) = uVar3;
    uVar3 = *(undefined8 *)(param_2 + 0x60);
    *(undefined8 *)(param_1 + 0x68) = *(undefined8 *)(param_2 + 0x68);
    *(undefined8 *)(param_1 + 0x60) = uVar3;
    Aska::ASON::MoveMemory_(Aska::ASON&, bool)(param_1,param_2,0);
    param_2[0x8a] = 0;
  }
  if (&puStack_c0 != (undefined **)param_2) {
    *(undefined8 *)(param_2 + 0x80) = uStack_40;
    param_2[0x88] = (undefined1)uStack_38;
    param_2[0x89] = uStack_38._1_1_;
    param_2[0x8a] = uStack_36;
    *(undefined8 *)(param_2 + 0x78) = uStack_48;
    *(undefined8 *)(param_2 + 0x70) = uStack_50;
    *(undefined8 *)(param_2 + 0x68) = uStack_58;
    *(ulong *)(param_2 + 0x60) = uStack_60;
    Aska::ASON::MoveMemory_(Aska::ASON&, bool)(param_2,&puStack_c0,0);
    uStack_36 = 0;
  }
  puStack_c0 = puVar1 + 0x10;
  Aska::ASON::Term()(&puStack_c0);
  puStack_a0 = puVar2 + 0x10;
  if (lStack_88 != lStack_98) {
    Aska::MemoryManagerAdapter::AlignedFree(void*)();
    uStack_90 = 0;
    lStack_88 = 0;
    lStack_98 = 0;
  }
  Aska::IAnimatable::~IAnimatable()(&puStack_c0);
  return;
}

// ==== Aska::ASON::Init(unsigned int, bool)
// vaddr 0x1f0caac | ghidra 0x200caac | size 140 | symbol _ZN4Aska4ASON4InitEjb | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska4ASON4InitEjb(long param_1,ulong param_2,byte param_3)

{
  undefined8 uVar1;
  long lVar2;
  
  param_2 = param_2 & 0xffffffff;
  Aska::ASON::Term()();
  if ((int)(param_2 >> 0xd) == 0) {
    uVar1 = 0xfffffffffffffc43;
  }
  else {
    lVar2 = operator new[](unsigned long, std::nothrow_t const&)(param_2,PTR__ZSt7nothrow_02cb9a80);
    if (lVar2 != 0) {
      Aska::ASON::InitMemory(signed char*, unsigned long, bool)(param_1,lVar2,param_2,1);
      *(byte *)(param_1 + 0x88) = param_3 & 1;
      *(undefined1 *)(param_1 + 0x8a) = 1;
      return 0;
    }
    uVar1 = 0xfffffffffffffc41;
  }
  *(undefined8 *)(param_1 + 0x80) = uVar1;
  return uVar1;
}

// ==== Aska::ASON::InitMemory(signed char*, unsigned long, bool)
// vaddr 0x1f0cb38 | ghidra 0x200cb38 | size 304 | symbol _ZN4Aska4ASON10InitMemoryEPamb | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska4ASON10InitMemoryEPamb(long param_1,undefined8 param_2,long param_3,byte param_4)

{
  undefined8 *puVar1;
  long lVar2;
  undefined8 uVar3;
  undefined8 *puVar4;
  undefined8 *puVar5;
  undefined8 uVar6;
  undefined8 *puVar7;
  undefined8 *puVar8;
  undefined8 *puVar9;
  undefined8 uVar10;
  undefined8 uStack_70;
  long lStack_68;
  undefined8 uStack_60;
  byte bStack_58;
  undefined8 uStack_50;
  undefined1 *puStack_48;
  
  if (((ulong)(*(long *)(param_1 + 0x38) - *(long *)(param_1 + 0x28) >> 5) < 4) &&
     (puVar4 = (undefined8 *)Aska::MemoryManagerAdapter::AlignedMalloc(unsigned long, unsigned long)(0x80,8), puVar4 != (undefined8 *)0x0)) {
    puVar5 = *(undefined8 **)(param_1 + 0x28);
    puVar1 = *(undefined8 **)(param_1 + 0x30);
    puVar7 = puVar4;
    puVar8 = puVar5;
    if (puVar5 != puVar1) {
      do {
        uVar10 = puVar8[2];
        puVar7[3] = puVar8[3];
        puVar7[2] = uVar10;
        puVar9 = puVar8 + 4;
        uVar10 = *puVar8;
        puVar7[1] = puVar8[1];
        *puVar7 = uVar10;
        puVar7 = puVar7 + 4;
        puVar8 = puVar9;
      } while (puVar1 != puVar9);
      lVar2 = -0x20 - (long)puVar5;
      puVar5 = *(undefined8 **)(param_1 + 0x28);
      puVar7 = (undefined8 *)((long)puVar4 + ((long)puVar1 + lVar2 & 0xffffffffffffffe0U) + 0x20);
    }
    Aska::MemoryManagerAdapter::AlignedFree(void*)(puVar5);
    *(undefined8 **)(param_1 + 0x28) = puVar4;
    *(undefined8 **)(param_1 + 0x30) = puVar7;
    *(undefined8 **)(param_1 + 0x38) = puVar4 + 0x10;
  }
  bStack_58 = param_4 & 1;
  uStack_60 = 0;
  uStack_50 = 1;
  uStack_70 = param_2;
  lStack_68 = param_3;
  puStack_48 = (undefined1 *)&uStack_70;
  Aska::TArrayIterator<Aska::TDynamicArray<Aska::ASON::WorkBufferContext, Aska::TAllocator<Aska::ASON::WorkBufferContext> > > Aska::TDynamicArray<Aska::ASON::WorkBufferContext, Aska::TAllocator<Aska::ASON::WorkBufferContext> >::Insert_<Aska::Memory::TUninitializedFillN<Aska::ASON::WorkBufferContext> >(Aska::ASON::WorkBufferContext const*, unsigned long, Aska::Memory::TUninitializedFillN<Aska::ASON::WorkBufferContext> const&)(param_1 + 0x20,*(undefined8 *)(param_1 + 0x30),1,&uStack_50);
  *(long *)(param_1 + 0x48) = *(long *)(param_1 + 0x30) + -0x20;
  *(long *)(param_1 + 0x50) = *(long *)(param_1 + 0x50) + param_3;
  *(undefined2 *)(param_1 + 0x58) = 0;
  uVar6 = Aska::ASON::Malloc(unsigned long)(param_1,0x200);
  uVar3 = _UNK_0296e148;
  uVar10 = _UNK_0296e140;
  *(undefined8 *)(param_1 + 8) = uVar6;
  *(undefined8 *)(param_1 + 0x18) = uVar3;
  *(undefined8 *)(param_1 + 0x10) = uVar10;
  return;
}

// ==== Aska::ASON::Init(signed char*, unsigned int, bool)
// vaddr 0x1f0cc68 | ghidra 0x200cc68 | size 108 | symbol _ZN4Aska4ASON4InitEPajb | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska4ASON4InitEPajb(long param_1,undefined8 param_2,ulong param_3,byte param_4)

{
  undefined8 uVar1;
  
  Aska::ASON::Term()();
  if ((int)((param_3 & 0xffffffff) >> 0xd) == 0) {
    uVar1 = 0xfffffffffffffc43;
    *(undefined8 *)(param_1 + 0x80) = 0xfffffffffffffc43;
  }
  else {
    Aska::ASON::InitMemory(signed char*, unsigned long, bool)(param_1,param_2,param_3 & 0xffffffff,0);
    uVar1 = 0;
    *(byte *)(param_1 + 0x88) = param_4 & 1;
    *(undefined1 *)(param_1 + 0x8a) = 1;
  }
  return uVar1;
}

// ==== Aska::ASON::ClearRoot()
// vaddr 0x1f0ccd4 | ghidra 0x200ccd4 | size 192 | symbol _ZN4Aska4ASON9ClearRootEv | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska4ASON9ClearRootEv(long param_1)

{
  undefined8 uVar1;
  undefined8 uVar2;
  long lVar3;
  undefined8 uVar4;
  ulong uVar5;
  long lVar6;
  long lVar7;
  
  lVar3 = *(long *)(param_1 + 0x28);
  lVar7 = *(long *)(param_1 + 0x30);
  *(undefined4 *)(param_1 + 0x60) = 0;
  *(undefined8 *)(param_1 + 0x68) = 0;
  *(undefined1 *)(param_1 + 0x89) = 0;
  uVar5 = lVar7 - lVar3 >> 5;
  if (1 < uVar5) {
    lVar6 = uVar5 - 1;
    do {
      if (*(char *)(lVar7 + -8) != '\0') {
        if (*(long *)(lVar7 + -0x20) != 0) {
          operator delete[](void*)();
        }
        *(undefined1 *)(lVar7 + -8) = 0;
      }
      *(undefined8 *)(lVar7 + -0x18) = 0;
      *(undefined8 *)(lVar7 + -0x10) = 0;
      *(long *)(lVar7 + -0x20) = 0;
      lVar3 = *(long *)(param_1 + 0x28);
      lVar7 = lVar3;
      if (lVar3 != *(long *)(param_1 + 0x30)) {
        lVar7 = *(long *)(param_1 + 0x30) + -0x20;
        *(long *)(param_1 + 0x30) = lVar7;
      }
      lVar6 = lVar6 + -1;
    } while (lVar6 != 0);
  }
  *(undefined8 *)(lVar3 + 0x10) = 0;
  *(long *)(param_1 + 0x48) = lVar3;
  uVar4 = *(undefined8 *)(lVar3 + 8);
  *(undefined2 *)(param_1 + 0x58) = 0;
  *(undefined8 *)(param_1 + 0x10) = 0;
  *(undefined8 *)(param_1 + 0x18) = 0;
  *(undefined8 *)(param_1 + 0x50) = uVar4;
  *(undefined8 *)(param_1 + 8) = 0;
  uVar2 = Aska::ASON::Malloc(unsigned long)(param_1,0x200);
  uVar1 = _UNK_0296e148;
  uVar4 = _UNK_0296e140;
  *(undefined8 *)(param_1 + 8) = uVar2;
  *(undefined8 *)(param_1 + 0x18) = uVar1;
  *(undefined8 *)(param_1 + 0x10) = uVar4;
  return;
}

// ==== Aska::ASON::TermMemory()
// vaddr 0x1f0cd94 | ghidra 0x200cd94 | size 104 | symbol _ZN4Aska4ASON10TermMemoryEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska4ASON10TermMemoryEv(long param_1)

{
  long *plVar1;
  long *plVar2;
  
  plVar2 = *(long **)(param_1 + 0x28);
  plVar1 = *(long **)(param_1 + 0x30);
  *(undefined8 *)(param_1 + 0x10) = 0;
  *(undefined8 *)(param_1 + 0x18) = 0;
  *(undefined8 *)(param_1 + 8) = 0;
  if (plVar2 != plVar1) {
    do {
      if (((char)plVar2[3] != '\0') && (*plVar2 != 0)) {
        operator delete[](void*)();
      }
      plVar2 = plVar2 + 4;
    } while (plVar1 != plVar2);
    plVar2 = *(long **)(param_1 + 0x28);
  }
  if (*(long **)(param_1 + 0x38) != plVar2) {
    *(long **)(param_1 + 0x30) = plVar2;
  }
  *(undefined2 *)(param_1 + 0x58) = 0;
  *(undefined8 *)(param_1 + 0x48) = 0;
  *(undefined8 *)(param_1 + 0x50) = 0;
  return;
}

// ==== Aska::ASON::Serialize(void*, unsigned long) const
// vaddr 0x1f0cdfc | ghidra 0x200cdfc | size 296 | symbol _ZNK4Aska4ASON9SerializeEPvm | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK4Aska4ASON9SerializeEPvm(long param_1,long param_2,long param_3)

{
  long lVar1;
  uint uVar2;
  long lVar3;
  ulong uVar4;
  long lStack_58;
  long lStack_48;
  
  if (*(char *)(param_1 + 0x8a) == '\0') {
    lVar3 = -0x3bc;
  }
  else {
    if ((param_2 != 0) && (param_3 != 0)) {
      *(undefined8 *)(param_1 + 0x80) = 0;
      lStack_48 = 0;
      if (*(char *)(param_1 + 0x89) == '\0') {
        Aska::Status Aska::ASON::PackMessagePack<true>(Aska::ASON::AValue const*, unsigned char*, unsigned long, unsigned long*) const(&lStack_58,param_1,param_1 + 0x60,param_2,param_3,&lStack_48);
      }
      else {
        uVar2 = *(uint *)(param_1 + 0x70);
        if (uVar2 == 0) {
          lStack_48 = 0;
        }
        else {
          lVar3 = 0;
          uVar4 = 0;
          do {
            lVar1 = lStack_48;
            Aska::Status Aska::ASON::PackMessagePack<true>(Aska::ASON::AValue const*, unsigned char*, unsigned long, unsigned long*) const(&lStack_58,param_1,*(long *)(param_1 + 0x68) + lVar3,param_2,param_3,
                            &lStack_48);
            if (lStack_58 < 0) break;
            uVar4 = uVar4 + 1;
            param_2 = param_2 + (lStack_48 - lVar1);
            lVar3 = lVar3 + 0x20;
          } while (uVar4 < uVar2);
        }
      }
      lVar3 = *(long *)(param_1 + 0x80);
      goto code_r0x0200cef4;
    }
    lVar3 = -0x3bd;
  }
  lStack_48 = 0;
  *(long *)(param_1 + 0x80) = lVar3;
code_r0x0200cef4:
  lVar1 = -0x3b1;
  if (-1 < lStack_48) {
    lVar1 = lStack_48;
  }
  if (-1 < lVar3) {
    lVar3 = lVar1;
  }
  return lVar3;
}

// ==== Aska::ASON::Deserialize(void const*, unsigned long)
// vaddr 0x1f0cf24 | ghidra 0x200cf24 | size 44 | symbol _ZN4Aska4ASON11DeserializeEPKvm | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska4ASON11DeserializeEPKvm(long param_1)

{
  long lVar1;
  long lVar2;
  
  lVar2 = Aska::ASON::DeserializeBinary(void const*, unsigned long)();
  lVar1 = -0x3b1;
  if (-1 < lVar2) {
    lVar1 = lVar2;
  }
  lVar2 = *(long *)(param_1 + 0x80);
  if (-1 < *(long *)(param_1 + 0x80)) {
    lVar2 = lVar1;
  }
  return lVar2;
}

// ==== Aska::ASON::DeserializeBinary(void const*, unsigned long)
// vaddr 0x1f0cf50 | ghidra 0x200cf50 | size 1128 | symbol _ZN4Aska4ASON17DeserializeBinaryEPKvm | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 _ZN4Aska4ASON17DeserializeBinaryEPKvm(long param_1,long param_2,ulong param_3)

{
  undefined2 uVar1;
  uint uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  long lVar5;
  undefined8 uVar6;
  undefined8 *puVar7;
  ulong uVar8;
  long lVar9;
  undefined8 *puVar10;
  int iVar11;
  long lVar12;
  undefined8 uStack_a98;
  long lStack_a90;
  undefined1 auStack_a88 [48];
  undefined8 uStack_a58;
  undefined8 uStack_a50;
  undefined8 uStack_a48;
  undefined8 uStack_a40;
  undefined2 uStack_a30;
  undefined2 uStack_9e0;
  undefined2 uStack_990;
  undefined2 uStack_940;
  undefined2 uStack_8f0;
  undefined2 uStack_8a0;
  undefined2 uStack_850;
  undefined2 uStack_800;
  undefined2 uStack_7b0;
  undefined2 uStack_760;
  undefined2 uStack_710;
  undefined2 uStack_6c0;
  undefined2 uStack_670;
  undefined2 uStack_620;
  undefined2 uStack_5d0;
  undefined2 uStack_580;
  undefined2 uStack_530;
  undefined2 uStack_4e0;
  undefined2 uStack_490;
  undefined2 uStack_440;
  undefined2 uStack_3f0;
  undefined2 uStack_3a0;
  undefined2 uStack_350;
  undefined2 uStack_300;
  undefined2 uStack_2b0;
  undefined2 uStack_260;
  undefined2 uStack_210;
  undefined2 uStack_1c0;
  undefined2 uStack_170;
  undefined2 uStack_120;
  undefined2 uStack_d0;
  undefined2 uStack_80;
  ulong uStack_58;
  
  if (*(char *)(param_1 + 0x8a) == '\0') {
    uVar6 = 0xfffffffffffffc44;
  }
  else {
    if ((param_2 != 0) && (param_3 != 0)) {
      lVar5 = *(long *)(param_1 + 0x28);
      lVar12 = *(long *)(param_1 + 0x30);
      *(undefined8 *)(param_1 + 0x80) = 0;
      *(undefined4 *)(param_1 + 0x60) = 0;
      *(undefined8 *)(param_1 + 0x68) = 0;
      uVar8 = lVar12 - lVar5 >> 5;
      *(undefined1 *)(param_1 + 0x89) = 0;
      if (1 < uVar8) {
        lVar9 = uVar8 - 1;
        do {
          if (*(char *)(lVar12 + -8) != '\0') {
            if (*(long *)(lVar12 + -0x20) != 0) {
              operator delete[](void*)();
            }
            *(undefined1 *)(lVar12 + -8) = 0;
          }
          *(undefined8 *)(lVar12 + -0x18) = 0;
          *(undefined8 *)(lVar12 + -0x10) = 0;
          *(long *)(lVar12 + -0x20) = 0;
          lVar5 = *(long *)(param_1 + 0x28);
          lVar12 = lVar5;
          if (lVar5 != *(long *)(param_1 + 0x30)) {
            lVar12 = *(long *)(param_1 + 0x30) + -0x20;
            *(long *)(param_1 + 0x30) = lVar12;
          }
          lVar9 = lVar9 + -1;
        } while (lVar9 != 0);
      }
      *(undefined8 *)(lVar5 + 0x10) = 0;
      *(long *)(param_1 + 0x48) = lVar5;
      uVar6 = *(undefined8 *)(lVar5 + 8);
      *(undefined2 *)(param_1 + 0x58) = 0;
      *(undefined8 *)(param_1 + 0x50) = uVar6;
      puVar10 = (undefined8 *)(param_1 + 8);
      *puVar10 = 0;
      *(undefined8 *)(param_1 + 0x10) = 0;
      *(undefined8 *)(param_1 + 0x18) = 0;
      uVar4 = Aska::ASON::Malloc(unsigned long)(param_1,0x200);
      uVar3 = _UNK_0296e148;
      uVar6 = _UNK_0296e140;
      iVar11 = 0;
      *puVar10 = uVar4;
      *(undefined8 *)(param_1 + 0x18) = uVar3;
      *(undefined8 *)(param_1 + 0x10) = uVar6;
      uStack_a98 = 0;
      uStack_58 = 0;
      do {
        memset(auStack_a88,0,0xa30);
        Aska::Status Aska::ASON::UnpackMessagePack<false>(Aska::ASON::MessagePackContext*, signed char const*, unsigned long, unsigned long*)(&lStack_a90,param_1,auStack_a88,param_2,param_3,&uStack_58);
        if (lStack_a90 < 0) {
          if (iVar11 == 0) {
            uVar4 = 0xffffffffffffffff;
            goto code_r0x0200d2f4;
          }
          break;
        }
        iVar11 = iVar11 + -1;
      } while (uStack_58 < param_3);
      uVar2 = -iVar11;
      if (-1 < *(long *)(param_1 + 0x80)) {
        lVar5 = *(long *)(param_1 + 0x28);
        lVar12 = *(long *)(param_1 + 0x30);
        uVar8 = lVar12 - lVar5 >> 5;
        if (1 < uVar8) {
          lVar9 = uVar8 - 1;
          do {
            if (*(char *)(lVar12 + -8) != '\0') {
              if (*(long *)(lVar12 + -0x20) != 0) {
                operator delete[](void*)();
              }
              *(undefined1 *)(lVar12 + -8) = 0;
            }
            *(undefined8 *)(lVar12 + -0x18) = 0;
            *(undefined8 *)(lVar12 + -0x10) = 0;
            *(long *)(lVar12 + -0x20) = 0;
            lVar5 = *(long *)(param_1 + 0x28);
            lVar12 = lVar5;
            if (lVar5 != *(long *)(param_1 + 0x30)) {
              lVar12 = *(long *)(param_1 + 0x30) + -0x20;
              *(long *)(param_1 + 0x30) = lVar12;
            }
            lVar9 = lVar9 + -1;
          } while (lVar9 != 0);
        }
        *(undefined8 *)(lVar5 + 0x10) = 0;
        *(long *)(param_1 + 0x48) = lVar5;
        uVar4 = *(undefined8 *)(lVar5 + 8);
        *(undefined2 *)(param_1 + 0x58) = 0;
        *(undefined8 *)(param_1 + 0x50) = uVar4;
        *(undefined8 *)(param_1 + 0x10) = 0;
        *(undefined8 *)(param_1 + 0x18) = 0;
        *puVar10 = 0;
        uVar4 = Aska::ASON::Malloc(unsigned long)(param_1,0x200);
        *(undefined8 *)(param_1 + 8) = uVar4;
        *(undefined8 *)(param_1 + 0x18) = uVar3;
        *(undefined8 *)(param_1 + 0x10) = uVar6;
        if (uVar2 == 1) {
          memset(auStack_a88,0,0xa30);
          Aska::Status Aska::ASON::UnpackMessagePack<true>(Aska::ASON::MessagePackContext*, signed char const*, unsigned long, unsigned long*)(&uStack_58,param_1,auStack_a88,param_2,param_3,&uStack_a98);
          if (-1 < (long)uStack_58) {
            *(undefined8 *)(param_1 + 0x78) = uStack_a40;
            *(undefined8 *)(param_1 + 0x70) = uStack_a48;
            *(undefined1 *)(param_1 + 0x89) = 0;
            *(undefined8 *)(param_1 + 0x68) = uStack_a50;
            *(undefined8 *)(param_1 + 0x60) = uStack_a58;
            return uStack_a98;
          }
        }
        else {
          uVar8 = (ulong)uVar2;
          *(undefined4 *)(param_1 + 0x70) = 0;
          *(undefined4 *)(param_1 + 0x60) = 6;
          lVar5 = Aska::ASON::Malloc(unsigned long)(param_1,uVar8 << 5);
          if (lVar5 != 0) {
            puVar7 = (undefined8 *)(lVar5 + 8);
            do {
              *(undefined4 *)(puVar7 + -1) = 0;
              puVar7[1] = 0;
              puVar7[2] = 0;
              *puVar7 = 0;
              uVar8 = uVar8 - 1;
              puVar7 = puVar7 + 4;
            } while (uVar8 != 0);
            *(long *)(param_1 + 0x68) = lVar5;
            if (0 < (int)uVar2) {
              uVar1 = *(undefined2 *)(param_1 + 0x58);
              iVar11 = 0;
              do {
                *(int *)(param_1 + 0x70) = *(int *)(param_1 + 0x70) + 1;
                memset(auStack_a88,0,0xa30);
                uStack_a30 = uVar1;
                uStack_9e0 = uVar1;
                uStack_990 = uVar1;
                uStack_940 = uVar1;
                uStack_8f0 = uVar1;
                uStack_8a0 = uVar1;
                uStack_850 = uVar1;
                uStack_800 = uVar1;
                uStack_7b0 = uVar1;
                uStack_760 = uVar1;
                uStack_710 = uVar1;
                uStack_6c0 = uVar1;
                uStack_670 = uVar1;
                uStack_620 = uVar1;
                uStack_5d0 = uVar1;
                uStack_580 = uVar1;
                uStack_530 = uVar1;
                uStack_4e0 = uVar1;
                uStack_490 = uVar1;
                uStack_440 = uVar1;
                uStack_3f0 = uVar1;
                uStack_3a0 = uVar1;
                uStack_350 = uVar1;
                uStack_300 = uVar1;
                uStack_2b0 = uVar1;
                uStack_260 = uVar1;
                uStack_210 = uVar1;
                uStack_1c0 = uVar1;
                uStack_170 = uVar1;
                uStack_120 = uVar1;
                uStack_d0 = uVar1;
                uStack_80 = uVar1;
                Aska::Status Aska::ASON::UnpackMessagePack<true>(Aska::ASON::MessagePackContext*, signed char const*, unsigned long, unsigned long*)(&uStack_58,param_1,auStack_a88,param_2,param_3,&uStack_a98);
                if ((long)uStack_58 < 0) goto code_r0x0200d2f8;
                iVar11 = iVar11 + 1;
                puVar7 = (undefined8 *)
                         (*(long *)(param_1 + 0x68) + (ulong)(*(int *)(param_1 + 0x70) - 1) * 0x20);
                puVar7[3] = uStack_a40;
                puVar7[2] = uStack_a48;
                puVar7[1] = uStack_a50;
                *puVar7 = uStack_a58;
              } while (iVar11 < (int)uVar2);
            }
            *(undefined1 *)(param_1 + 0x89) = 1;
            return uStack_a98;
          }
          *(undefined8 *)(param_1 + 0x68) = 0;
          uVar4 = 0xfffffffffffffc41;
code_r0x0200d2f4:
          *(undefined8 *)(param_1 + 0x80) = uVar4;
        }
      }
code_r0x0200d2f8:
      lVar5 = *(long *)(param_1 + 0x28);
      lVar12 = *(long *)(param_1 + 0x30);
      *(undefined4 *)(param_1 + 0x60) = 0;
      *(undefined8 *)(param_1 + 0x68) = 0;
      *(undefined1 *)(param_1 + 0x89) = 0;
      uVar8 = lVar12 - lVar5 >> 5;
      if (1 < uVar8) {
        lVar9 = uVar8 - 1;
        do {
          if (*(char *)(lVar12 + -8) != '\0') {
            if (*(long *)(lVar12 + -0x20) != 0) {
              operator delete[](void*)();
            }
            *(undefined1 *)(lVar12 + -8) = 0;
          }
          *(undefined8 *)(lVar12 + -0x18) = 0;
          *(undefined8 *)(lVar12 + -0x10) = 0;
          *(long *)(lVar12 + -0x20) = 0;
          lVar5 = *(long *)(param_1 + 0x28);
          lVar12 = lVar5;
          if (lVar5 != *(long *)(param_1 + 0x30)) {
            lVar12 = *(long *)(param_1 + 0x30) + -0x20;
            *(long *)(param_1 + 0x30) = lVar12;
          }
          lVar9 = lVar9 + -1;
        } while (lVar9 != 0);
      }
      *(undefined8 *)(lVar5 + 0x10) = 0;
      *(long *)(param_1 + 0x48) = lVar5;
      uVar4 = *(undefined8 *)(lVar5 + 8);
      *(undefined2 *)(param_1 + 0x58) = 0;
      *(undefined8 *)(param_1 + 0x50) = uVar4;
      *(undefined8 *)(param_1 + 0x10) = 0;
      *(undefined8 *)(param_1 + 0x18) = 0;
      *puVar10 = 0;
      uVar4 = Aska::ASON::Malloc(unsigned long)(param_1,0x200);
      *(undefined8 *)(param_1 + 8) = uVar4;
      *(undefined8 *)(param_1 + 0x18) = uVar3;
      *(undefined8 *)(param_1 + 0x10) = uVar6;
      return 0;
    }
    uVar6 = 0xfffffffffffffc43;
  }
  *(undefined8 *)(param_1 + 0x80) = uVar6;
  return 0;
}

// ==== Aska::ASON::CalcSerializedSize() const
// vaddr 0x1f0d3b8 | ghidra 0x200d3b8 | size 228 | symbol _ZNK4Aska4ASON18CalcSerializedSizeEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK4Aska4ASON18CalcSerializedSizeEv(long param_1)

{
  long lVar1;
  uint uVar2;
  long lVar3;
  ulong uVar4;
  long lStack_38;
  long lStack_28;
  
  if (*(char *)(param_1 + 0x8a) == '\0') {
    lVar3 = -0x3bc;
    lStack_28 = 0;
    *(undefined8 *)(param_1 + 0x80) = 0xfffffffffffffc44;
  }
  else {
    *(undefined8 *)(param_1 + 0x80) = 0;
    lStack_28 = 0;
    if (*(char *)(param_1 + 0x89) == '\0') {
      Aska::Status Aska::ASON::PackMessagePack<false>(Aska::ASON::AValue const*, unsigned char*, unsigned long, unsigned long*) const(&lStack_38,param_1,param_1 + 0x60,0,0,&lStack_28);
      if (lStack_38 < 0) {
code_r0x0200d46c:
        lStack_28 = 0;
      }
    }
    else {
      uVar2 = *(uint *)(param_1 + 0x70);
      if (uVar2 != 0) {
        lVar3 = 0;
        uVar4 = 0;
        do {
          Aska::Status Aska::ASON::PackMessagePack<false>(Aska::ASON::AValue const*, unsigned char*, unsigned long, unsigned long*) const(&lStack_38,param_1,*(long *)(param_1 + 0x68) + lVar3,0,0,&lStack_28);
          if (lStack_38 < 0) goto code_r0x0200d46c;
          uVar4 = uVar4 + 1;
          lVar3 = lVar3 + 0x20;
        } while (uVar4 < uVar2);
      }
    }
    lVar3 = *(long *)(param_1 + 0x80);
  }
  lVar1 = -0x3b1;
  if (-1 < lStack_28) {
    lVar1 = lStack_28;
  }
  if (-1 < lVar3) {
    lVar3 = lVar1;
  }
  return lVar3;
}

// ==== Aska::ASON::SerializeBinary(void*, unsigned long, Aska::ASON::AValue const*) const
// vaddr 0x1f0d49c | ghidra 0x200d49c | size 288 | symbol _ZNK4Aska4ASON15SerializeBinaryEPvmPKNS0_6AValueE | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK4Aska4ASON15SerializeBinaryEPvmPKNS0_6AValueE
               (long param_1,long param_2,long param_3,long param_4)

{
  uint uVar1;
  long lVar2;
  undefined8 uVar3;
  long lVar4;
  ulong uVar5;
  long lStack_60;
  long lStack_58;
  
  if (*(char *)(param_1 + 0x8a) == '\0') {
    uVar3 = 0xfffffffffffffc44;
  }
  else {
    if (((param_2 != 0) && (param_3 != 0)) && (param_4 != 0)) {
      *(undefined8 *)(param_1 + 0x80) = 0;
      lStack_58 = 0;
      if ((param_1 + 0x60 == param_4) && (*(char *)(param_1 + 0x89) != '\0')) {
        uVar1 = *(uint *)(param_4 + 0x10);
        if (uVar1 == 0) {
          return 0;
        }
        lVar4 = 0;
        uVar5 = 0;
        do {
          lVar2 = lStack_58;
          Aska::Status Aska::ASON::PackMessagePack<true>(Aska::ASON::AValue const*, unsigned char*, unsigned long, unsigned long*) const(&lStack_60,param_1,*(long *)(param_4 + 8) + lVar4,param_2,param_3,
                          &lStack_58);
          if (lStack_60 < 0) {
            return lStack_58;
          }
          uVar5 = uVar5 + 1;
          param_2 = param_2 + (lStack_58 - lVar2);
          lVar4 = lVar4 + 0x20;
        } while (uVar5 < uVar1);
        return lStack_58;
      }
      Aska::Status Aska::ASON::PackMessagePack<true>(Aska::ASON::AValue const*, unsigned char*, unsigned long, unsigned long*) const(&lStack_60,param_1,param_4,param_2,param_3,&lStack_58);
      return lStack_58;
    }
    uVar3 = 0xfffffffffffffc43;
  }
  *(undefined8 *)(param_1 + 0x80) = uVar3;
  return 0;
}

// ==== Aska::Status Aska::ASON::PackMessagePack<true>(Aska::ASON::AValue const*, unsigned char*, unsigned long, unsigned long*) const
// vaddr 0x1f0d5bc | ghidra 0x200d5bc | size 1620 | symbol _ZNK4Aska4ASON15PackMessagePackILb1EEENS_6StatusEPKNS0_6AValueEPhmPm | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK4Aska4ASON15PackMessagePackILb1EEENS_6StatusEPKNS0_6AValueEPhmPm
               (long *param_1,long param_2,uint *param_3,byte *param_4,ulong param_5,ulong *param_6)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  long lVar5;
  undefined8 uVar6;
  byte bVar7;
  long lVar8;
  long lVar9;
  ulong uVar10;
  ulong uVar11;
  ulong uVar12;
  long lVar13;
  long lStack_68;
  
  if (param_5 <= *param_6) goto code_r0x0200dbb4;
  if (9 < *param_3) goto code_r0x0200dc08;
  uVar11 = param_5 - *param_6;
  switch(*param_3) {
  case 0:
    if (uVar11 == 0) break;
    bVar7 = 0xc0;
code_r0x0200d648:
    *param_4 = bVar7;
    uVar10 = *param_6 + 1;
    goto code_r0x0200dc00;
  case 1:
    if (uVar11 != 0) {
      bVar7 = 0xc2;
      if ((char)param_3[2] != '\0') {
        bVar7 = 0xc3;
      }
      goto code_r0x0200d648;
    }
    break;
  case 2:
    lVar5 = long Aska::ASON::PackValue_u64<true>(unsigned char*, unsigned long, unsigned long) const(param_2,param_4,*(undefined8 *)(param_3 + 2),uVar11);
    goto joined_r0x0200d690;
  case 3:
    lVar5 = long Aska::ASON::PackValue_s64<true>(unsigned char*, long, unsigned long) const(param_2,param_4,*(undefined8 *)(param_3 + 2),uVar11);
joined_r0x0200d690:
    if (0 < lVar5) {
      uVar10 = *param_6 + lVar5;
code_r0x0200dc00:
      *param_6 = uVar10;
      lVar5 = 0;
    }
    goto code_r0x0200dbbc;
  case 4:
    if (8 < uVar11) {
      uVar11 = *(ulong *)(param_3 + 2);
      *param_4 = 0xcb;
      uVar11 = (uVar11 & 0xff00ff00ff00ff00) >> 8 | (uVar11 & 0xff00ff00ff00ff) << 8;
      uVar11 = (uVar11 & 0xffff0000ffff0000) >> 0x10 | (uVar11 & 0xffff0000ffff) << 0x10;
      *(ulong *)(param_4 + 1) = uVar11 >> 0x20 | uVar11 << 0x20;
      uVar10 = *param_6 + 9;
      goto code_r0x0200dc00;
    }
    break;
  case 5:
    lVar5 = long Aska::ASON::PackValue_str<true>(unsigned char*, unsigned long, unsigned long) const(param_2,param_4,param_3[6],uVar11);
    if (lVar5 < 1) goto code_r0x0200dbbc;
    *param_6 = *param_6 + lVar5;
    uVar1 = param_3[6];
    goto joined_r0x0200d7cc;
  case 6:
    uVar1 = param_3[4];
    if (uVar1 < 0x10) {
      if (uVar11 == 0) break;
      *param_4 = (byte)uVar1 | 0x90;
      uVar11 = *param_6 + 1;
      *param_6 = uVar11;
      if (uVar1 == 0) goto code_r0x0200dc08;
      lVar5 = 1;
code_r0x0200d9c8:
      lVar13 = 0;
      uVar10 = 0;
      param_4 = param_4 + lVar5;
      do {
        Aska::Status Aska::ASON::PackMessagePack<true>(Aska::ASON::AValue const*, unsigned char*, unsigned long, unsigned long*) const(&lStack_68,param_2,*(long *)(param_3 + 2) + lVar13,param_4,param_5,param_6);
        lVar5 = lStack_68;
        if (lStack_68 < 0) break;
        uVar10 = uVar10 + 1;
        lVar5 = 0;
        param_4 = param_4 + (*param_6 - uVar11);
        lVar13 = lVar13 + 0x20;
        uVar11 = *param_6;
      } while (uVar10 < uVar1);
      goto code_r0x0200dbbc;
    }
    if (uVar1 >> 0x10 == 0) {
      if (2 < uVar11) {
        if (((*PTR__ZGVZN4Aska7Machine6_HTONSEtE9kMyEndian_02cc0910 & 1) == 0) &&
           (iVar4 = __cxa_guard_acquire(PTR__ZGVZN4Aska7Machine6_HTONSEtE9kMyEndian_02cc0910),
           iVar4 != 0)) {
          *(undefined4 *)PTR__ZZN4Aska7Machine6_HTONSEtE9kMyEndian_02cbc7a8 = 1;
          __cxa_guard_release(PTR__ZGVZN4Aska7Machine6_HTONSEtE9kMyEndian_02cc0910);
        }
        iVar4 = *(int *)PTR__ZZN4Aska7Machine6_HTONSEtE9kMyEndian_02cbc7a8;
        *param_4 = 0xdc;
        uVar3 = uVar1;
        if (iVar4 != 2) {
          uVar3 = ((uVar1 & 0xff00ff00) >> 8 | (uVar1 & 0xff00ff) << 8) & 0xffff;
        }
        *(short *)(param_4 + 1) = (short)uVar3;
        lVar5 = 3;
code_r0x0200d9bc:
        uVar11 = *param_6 + lVar5;
        *param_6 = uVar11;
        goto code_r0x0200d9c8;
      }
    }
    else if (4 < uVar11) {
      if (((*PTR__ZGVZN4Aska7Machine6_HTONLEjE9kMyEndian_02cbe508 & 1) == 0) &&
         (iVar4 = __cxa_guard_acquire(PTR__ZGVZN4Aska7Machine6_HTONLEjE9kMyEndian_02cbe508), iVar4 != 0)
         ) {
        *(undefined4 *)PTR__ZZN4Aska7Machine6_HTONLEjE9kMyEndian_02cc0b50 = 1;
        __cxa_guard_release(PTR__ZGVZN4Aska7Machine6_HTONLEjE9kMyEndian_02cbe508);
      }
      uVar2 = (uVar1 & 0xff00ff00) >> 8 | (uVar1 & 0xff00ff) << 8;
      iVar4 = *(int *)PTR__ZZN4Aska7Machine6_HTONLEjE9kMyEndian_02cc0b50;
      *param_4 = 0xdd;
      uVar3 = uVar1;
      if (iVar4 != 2) {
        uVar3 = uVar2 >> 0x10 | uVar2 << 0x10;
      }
      *(uint *)(param_4 + 1) = uVar3;
      lVar5 = 5;
      goto code_r0x0200d9bc;
    }
    break;
  case 7:
    uVar1 = param_3[4];
    if (uVar1 < 0x10) {
      if (uVar11 == 0) break;
      *param_4 = (byte)uVar1 | 0x80;
      uVar11 = *param_6 + 1;
      *param_6 = uVar11;
      if (uVar1 == 0) goto code_r0x0200dc08;
      lVar5 = 1;
code_r0x0200daa0:
      lVar13 = 0;
      uVar10 = 0;
      param_4 = param_4 + lVar5;
      do {
        lVar8 = *(long *)(param_3 + 2);
        Aska::Status Aska::ASON::PackMessagePack<true>(Aska::ASON::AValue const*, unsigned char*, unsigned long, unsigned long*) const(&lStack_68,param_2,lVar13 + lVar8,param_4,param_5,param_6);
        lVar5 = lStack_68;
        if (lStack_68 < 0) break;
        uVar12 = *param_6;
        lVar9 = uVar12 - uVar11;
        Aska::Status Aska::ASON::PackMessagePack<true>(Aska::ASON::AValue const*, unsigned char*, unsigned long, unsigned long*) const(&lStack_68,param_2,lVar13 + lVar8 + 0x20,param_4 + lVar9,param_5,param_6);
        lVar5 = lStack_68;
        if (lStack_68 < 0) break;
        uVar11 = *param_6;
        uVar10 = uVar10 + 1;
        lVar5 = 0;
        lVar13 = lVar13 + 0x40;
        param_4 = param_4 + lVar9 + (uVar11 - uVar12);
      } while (uVar10 < uVar1);
      goto code_r0x0200dbbc;
    }
    if (uVar1 >> 0x10 == 0) {
      if (2 < uVar11) {
        if (((*PTR__ZGVZN4Aska7Machine6_HTONSEtE9kMyEndian_02cc0910 & 1) == 0) &&
           (iVar4 = __cxa_guard_acquire(PTR__ZGVZN4Aska7Machine6_HTONSEtE9kMyEndian_02cc0910),
           iVar4 != 0)) {
          *(undefined4 *)PTR__ZZN4Aska7Machine6_HTONSEtE9kMyEndian_02cbc7a8 = 1;
          __cxa_guard_release(PTR__ZGVZN4Aska7Machine6_HTONSEtE9kMyEndian_02cc0910);
        }
        iVar4 = *(int *)PTR__ZZN4Aska7Machine6_HTONSEtE9kMyEndian_02cbc7a8;
        *param_4 = 0xde;
        uVar3 = uVar1;
        if (iVar4 != 2) {
          uVar3 = ((uVar1 & 0xff00ff00) >> 8 | (uVar1 & 0xff00ff) << 8) & 0xffff;
        }
        *(short *)(param_4 + 1) = (short)uVar3;
        lVar5 = 3;
code_r0x0200da90:
        uVar11 = *param_6 + lVar5;
        *param_6 = uVar11;
        goto code_r0x0200daa0;
      }
    }
    else if (4 < uVar11) {
      if (((*PTR__ZGVZN4Aska7Machine6_HTONLEjE9kMyEndian_02cbe508 & 1) == 0) &&
         (iVar4 = __cxa_guard_acquire(PTR__ZGVZN4Aska7Machine6_HTONLEjE9kMyEndian_02cbe508), iVar4 != 0)
         ) {
        *(undefined4 *)PTR__ZZN4Aska7Machine6_HTONLEjE9kMyEndian_02cc0b50 = 1;
        __cxa_guard_release(PTR__ZGVZN4Aska7Machine6_HTONLEjE9kMyEndian_02cbe508);
      }
      uVar2 = (uVar1 & 0xff00ff00) >> 8 | (uVar1 & 0xff00ff) << 8;
      iVar4 = *(int *)PTR__ZZN4Aska7Machine6_HTONLEjE9kMyEndian_02cc0b50;
      *param_4 = 0xdf;
      uVar3 = uVar1;
      if (iVar4 != 2) {
        uVar3 = uVar2 >> 0x10 | uVar2 << 0x10;
      }
      *(uint *)(param_4 + 1) = uVar3;
      lVar5 = 5;
      goto code_r0x0200da90;
    }
    break;
  case 8:
    uVar1 = param_3[4];
    if (uVar1 < 0x100) {
      if (1 < uVar11) {
        param_4[1] = (byte)uVar1;
        *param_4 = 0xc4;
        lVar5 = 2;
        goto code_r0x0200db9c;
      }
      break;
    }
    if (uVar1 >> 0x10 != 0) {
      if (4 < uVar11) {
        if (((*PTR__ZGVZN4Aska7Machine6_HTONLEjE9kMyEndian_02cbe508 & 1) == 0) &&
           (iVar4 = __cxa_guard_acquire(PTR__ZGVZN4Aska7Machine6_HTONLEjE9kMyEndian_02cbe508),
           iVar4 != 0)) {
          *(undefined4 *)PTR__ZZN4Aska7Machine6_HTONLEjE9kMyEndian_02cc0b50 = 1;
          __cxa_guard_release(PTR__ZGVZN4Aska7Machine6_HTONLEjE9kMyEndian_02cbe508);
        }
        uVar3 = (uVar1 & 0xff00ff00) >> 8 | (uVar1 & 0xff00ff) << 8;
        iVar4 = *(int *)PTR__ZZN4Aska7Machine6_HTONLEjE9kMyEndian_02cc0b50;
        *param_4 = 0xc6;
        if (iVar4 != 2) {
          uVar1 = uVar3 >> 0x10 | uVar3 << 0x10;
        }
        *(uint *)(param_4 + 1) = uVar1;
        lVar5 = 5;
        goto code_r0x0200db9c;
      }
      break;
    }
    if (uVar11 < 3) break;
    if (((*PTR__ZGVZN4Aska7Machine6_HTONSEtE9kMyEndian_02cc0910 & 1) == 0) &&
       (iVar4 = __cxa_guard_acquire(PTR__ZGVZN4Aska7Machine6_HTONSEtE9kMyEndian_02cc0910), iVar4 != 0))
    {
      *(undefined4 *)PTR__ZZN4Aska7Machine6_HTONSEtE9kMyEndian_02cbc7a8 = 1;
      __cxa_guard_release(PTR__ZGVZN4Aska7Machine6_HTONSEtE9kMyEndian_02cc0910);
    }
    iVar4 = *(int *)PTR__ZZN4Aska7Machine6_HTONSEtE9kMyEndian_02cbc7a8;
    *param_4 = 0xc5;
    if (iVar4 != 2) {
      uVar1 = ((uVar1 & 0xff00ff00) >> 8 | (uVar1 & 0xff00ff) << 8) & 0xffff;
    }
    *(short *)(param_4 + 1) = (short)uVar1;
    lVar5 = 3;
code_r0x0200db9c:
    *param_6 = *param_6 + lVar5;
    uVar10 = (ulong)param_3[4];
    if (uVar11 < uVar10) break;
    uVar6 = *(undefined8 *)(param_3 + 2);
    goto code_r0x0200dbe8;
  case 9:
    lVar5 = long Aska::ASON::PackValue_ext<true>(unsigned char*, unsigned long, signed char, unsigned long) const(param_2,param_4,param_3[4],(char)param_3[5],uVar11);
    if (lVar5 < 1) goto code_r0x0200dbbc;
    *param_6 = *param_6 + lVar5;
    uVar1 = param_3[4];
joined_r0x0200d7cc:
    uVar10 = (ulong)uVar1;
    if (uVar11 < uVar10) break;
    uVar6 = *(undefined8 *)(param_3 + 2);
code_r0x0200dbe8:
    memcpy(param_4 + lVar5,uVar6,uVar10);
    if ((int)uVar10 == 0) {
code_r0x0200dc08:
      lVar5 = 0;
      goto code_r0x0200dbbc;
    }
    uVar10 = *param_6 + uVar10;
    goto code_r0x0200dc00;
  }
code_r0x0200dbb4:
  *(undefined8 *)(param_2 + 0x80) = 0xfffffffffffffc3f;
  lVar5 = -0x3c1;
code_r0x0200dbbc:
  *param_1 = lVar5;
  return;
}

// ==== Aska::ASON::CalcRootCount(signed char const*, unsigned long)
// vaddr 0x1f0dc10 | ghidra 0x200dc10 | size 128 | symbol _ZN4Aska4ASON13CalcRootCountEPKam | lib libSOA-3.7.0.so | 2026-10-04
int _ZN4Aska4ASON13CalcRootCountEPKam(undefined8 param_1,undefined8 param_2,ulong param_3)

{
  int iVar1;
  long lStack_a70;
  undefined1 auStack_a68 [2608];
  ulong uStack_38;
  
  iVar1 = 0;
  uStack_38 = 0;
  do {
    memset(auStack_a68,0,0xa30);
    Aska::Status Aska::ASON::UnpackMessagePack<false>(Aska::ASON::MessagePackContext*, signed char const*, unsigned long, unsigned long*)(&lStack_a70,param_1,auStack_a68,param_2,param_3,&uStack_38);
    if (lStack_a70 < 0) {
      return iVar1;
    }
    iVar1 = iVar1 + 1;
  } while (uStack_38 < param_3);
  return iVar1;
}

// ==== Aska::ASON::AllFree()
// vaddr 0x1f0dc90 | ghidra 0x200dc90 | size 180 | symbol _ZN4Aska4ASON7AllFreeEv | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska4ASON7AllFreeEv(long param_1)

{
  undefined8 uVar1;
  undefined8 uVar2;
  long lVar3;
  undefined8 uVar4;
  ulong uVar5;
  long lVar6;
  long lVar7;
  
  lVar3 = *(long *)(param_1 + 0x28);
  lVar7 = *(long *)(param_1 + 0x30);
  uVar5 = lVar7 - lVar3 >> 5;
  if (1 < uVar5) {
    lVar6 = uVar5 - 1;
    do {
      if (*(char *)(lVar7 + -8) != '\0') {
        if (*(long *)(lVar7 + -0x20) != 0) {
          operator delete[](void*)();
        }
        *(undefined1 *)(lVar7 + -8) = 0;
      }
      *(undefined8 *)(lVar7 + -0x18) = 0;
      *(undefined8 *)(lVar7 + -0x10) = 0;
      *(long *)(lVar7 + -0x20) = 0;
      lVar3 = *(long *)(param_1 + 0x28);
      lVar7 = lVar3;
      if (lVar3 != *(long *)(param_1 + 0x30)) {
        lVar7 = *(long *)(param_1 + 0x30) + -0x20;
        *(long *)(param_1 + 0x30) = lVar7;
      }
      lVar6 = lVar6 + -1;
    } while (lVar6 != 0);
  }
  *(undefined8 *)(lVar3 + 0x10) = 0;
  *(long *)(param_1 + 0x48) = lVar3;
  uVar4 = *(undefined8 *)(lVar3 + 8);
  *(undefined2 *)(param_1 + 0x58) = 0;
  *(undefined8 *)(param_1 + 0x10) = 0;
  *(undefined8 *)(param_1 + 0x18) = 0;
  *(undefined8 *)(param_1 + 0x50) = uVar4;
  *(undefined8 *)(param_1 + 8) = 0;
  uVar2 = Aska::ASON::Malloc(unsigned long)(param_1,0x200);
  uVar1 = _UNK_0296e148;
  uVar4 = _UNK_0296e140;
  *(undefined8 *)(param_1 + 8) = uVar2;
  *(undefined8 *)(param_1 + 0x18) = uVar1;
  *(undefined8 *)(param_1 + 0x10) = uVar4;
  return;
}

// ==== Aska::Status Aska::ASON::UnpackMessagePack<true>(Aska::ASON::MessagePackContext*, signed char const*, unsigned long, unsigned long*)
// vaddr 0x1f0dd44 | ghidra 0x200dd44 | size 4732 | symbol _ZN4Aska4ASON17UnpackMessagePackILb1EEENS_6StatusEPNS0_18MessagePackContextEPKamPm | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Type propagation algorithm not settling */

void _ZN4Aska4ASON17UnpackMessagePackILb1EEENS_6StatusEPNS0_18MessagePackContextEPKamPm
               (undefined8 *param_1,long param_2,uint *param_3,long param_4,long param_5,
               long *param_6)

{
  float *pfVar1;
  undefined1 uVar2;
  ushort uVar3;
  byte bVar4;
  uint uVar5;
  int iVar6;
  long lVar7;
  uint uVar8;
  float fVar9;
  int *piVar10;
  undefined8 *puVar11;
  uint *puVar12;
  float fVar13;
  uint uVar14;
  undefined8 uVar15;
  float fVar16;
  uint *puVar17;
  float *pfVar18;
  float *pfVar19;
  uint uVar20;
  float *pfVar21;
  ulong uVar22;
  undefined8 uVar23;
  uint *puStack_a0;
  ulong uStack_70;
  
  uVar8 = param_3[8];
  fVar9 = (float)param_3[9];
  uVar20 = param_3[10];
  pfVar19 = (float *)(param_4 + *param_6);
  if (*param_6 != param_5) {
    pfVar18 = (float *)0x0;
    pfVar1 = (float *)(param_4 + param_5);
code_r0x0200ddb8:
    if (uVar8 != 0) goto code_r0x0200e0f4;
    bVar4 = *(byte *)pfVar19;
    pfVar21 = pfVar19;
    if (-1 < (long)(char)bVar4) {
      *param_3 = 2;
      *(ulong *)(param_3 + 2) = (ulong)bVar4;
joined_r0x0200dddc:
      uVar8 = 0;
      goto joined_r0x0200e6a4;
    }
    uVar14 = (uint)bVar4;
    if (0xdf < uVar14) {
      *param_3 = 3;
      *(long *)(param_3 + 2) = (long)(char)bVar4;
      goto joined_r0x0200dddc;
    }
    if (0xbf < bVar4) {
      uVar8 = 0;
      uVar15 = 0xffffffffffffffff;
      fVar16 = 2.38221e-44;
      uVar5 = 0x22;
      switch(uVar14) {
      case 0xc0:
        *param_3 = 0;
        goto joined_r0x0200e0b8;
      default:
        goto code_r0x0200ef88;
      case 0xc2:
        *param_3 = 1;
        *(undefined1 *)(param_3 + 2) = 0;
joined_r0x0200e0b8:
        uVar8 = 0;
        goto joined_r0x0200e6a4;
      case 0xc3:
        uVar8 = 0;
        *param_3 = 1;
        *(undefined1 *)(param_3 + 2) = 1;
        goto joined_r0x0200e6a4;
      case 0xc4:
      case 0xc5:
      case 0xc6:
        fVar16 = (float)(1 << (ulong)(bVar4 & 3));
        uVar5 = bVar4 & 0x1f;
        goto code_r0x0200e0e8;
      case 199:
      case 200:
      case 0xc9:
        uVar8 = (int)(char)bVar4 + 1U & 3;
        break;
      case 0xca:
      case 0xcb:
      case 0xcc:
      case 0xcd:
      case 0xce:
      case 0xcf:
      case 0xd0:
      case 0xd1:
      case 0xd2:
      case 0xd3:
        uVar8 = uVar14 & 3;
        break;
      case 0xd4:
      case 0xd5:
      case 0xd6:
      case 0xd7:
        uVar8 = 1 << (ulong)(uVar14 & 3);
        goto code_r0x0200e228;
      case 0xd8:
        goto code_r0x0200e0e8;
      case 0xd9:
      case 0xda:
      case 0xdb:
        uVar8 = (uVar14 & 3) - 1;
        break;
      case 0xdc:
      case 0xdd:
      case 0xde:
      case 0xdf:
        fVar16 = (float)(2 << (ulong)(uVar14 & 1));
        goto code_r0x0200df94;
      }
      fVar16 = (float)(1 << (ulong)(uVar8 & 0x1f));
code_r0x0200df94:
      uVar5 = uVar14 & 0x1f;
      goto code_r0x0200e0e8;
    }
    if (0x9f < uVar14) {
      fVar9 = (float)((int)(char)bVar4 & 0x1f);
      if (fVar9 != 0.0) {
code_r0x0200e0d8:
        fVar16 = fVar9;
        uVar5 = 0x20;
code_r0x0200e0e8:
        uVar8 = uVar5;
        fVar9 = fVar16;
        pfVar19 = (float *)((long)pfVar21 + 1);
code_r0x0200e0f4:
        if ((ulong)((long)pfVar1 - (long)pfVar19) < (ulong)(uint)fVar9) {
          uVar15 = 0;
          goto code_r0x0200ef88;
        }
        pfVar21 = (float *)((long)pfVar19 + (ulong)((int)fVar9 - 1));
        pfVar18 = pfVar19;
        fVar16 = 2.8026e-45;
        uVar14 = 0x20;
        uVar5 = 0x22;
        switch(uVar8) {
        case 4:
          fVar9 = (float)(uint)*(byte *)pfVar19;
          if (fVar9 != 0.0) {
            fVar16 = fVar9;
            uVar5 = 0x21;
            goto code_r0x0200e0e8;
          }
          break;
        case 5:
          uVar3 = *(ushort *)pfVar19;
          if (((*PTR__ZGVZN4Aska7Machine6_HTONSEtE9kMyEndian_02cc0910 & 1) == 0) &&
             (iVar6 = __cxa_guard_acquire(PTR__ZGVZN4Aska7Machine6_HTONSEtE9kMyEndian_02cc0910),
             iVar6 != 0)) {
            *(undefined4 *)PTR__ZZN4Aska7Machine6_HTONSEtE9kMyEndian_02cbc7a8 = 1;
            __cxa_guard_release(PTR__ZGVZN4Aska7Machine6_HTONSEtE9kMyEndian_02cc0910);
          }
          fVar9 = (float)(uint)uVar3;
          if (*(int *)PTR__ZZN4Aska7Machine6_HTONSEtE9kMyEndian_02cbc7a8 != 2) {
            fVar9 = (float)((uint)(uVar3 >> 8) | (uVar3 & 0xff00ff) << 8);
          }
          if (fVar9 != 0.0) {
code_r0x0200e21c:
            fVar16 = fVar9;
            uVar5 = 0x21;
            goto code_r0x0200e0e8;
          }
          break;
        case 6:
          fVar9 = *pfVar19;
          if (((*PTR__ZGVZN4Aska7Machine6_HTONLEjE9kMyEndian_02cbe508 & 1) == 0) &&
             (iVar6 = __cxa_guard_acquire(PTR__ZGVZN4Aska7Machine6_HTONLEjE9kMyEndian_02cbe508),
             iVar6 != 0)) {
            *(undefined4 *)PTR__ZZN4Aska7Machine6_HTONLEjE9kMyEndian_02cc0b50 = 1;
            __cxa_guard_release(PTR__ZGVZN4Aska7Machine6_HTONLEjE9kMyEndian_02cbe508);
          }
          uVar14 = ((uint)fVar9 & 0xff00ff00) >> 8 | ((uint)fVar9 & 0xff00ff) << 8;
          if (*(int *)PTR__ZZN4Aska7Machine6_HTONLEjE9kMyEndian_02cc0b50 != 2) {
            fVar9 = (float)(uVar14 >> 0x10 | uVar14 << 0x10);
          }
          if (fVar9 != 0.0) goto code_r0x0200e21c;
          fVar9 = 0.0;
          break;
        case 7:
          uVar8 = (uint)*(byte *)pfVar19;
          pfVar19 = pfVar21;
code_r0x0200e228:
          pfVar21 = pfVar19;
          fVar16 = (float)(uVar8 + 1);
          uVar5 = 0x22;
          goto code_r0x0200e0e8;
        case 8:
          uVar3 = *(ushort *)pfVar19;
          if (((*PTR__ZGVZN4Aska7Machine6_HTONSEtE9kMyEndian_02cc0910 & 1) == 0) &&
             (iVar6 = __cxa_guard_acquire(PTR__ZGVZN4Aska7Machine6_HTONSEtE9kMyEndian_02cc0910),
             iVar6 != 0)) {
            *(undefined4 *)PTR__ZZN4Aska7Machine6_HTONSEtE9kMyEndian_02cbc7a8 = 1;
            __cxa_guard_release(PTR__ZGVZN4Aska7Machine6_HTONSEtE9kMyEndian_02cc0910);
          }
          uVar8 = (uint)uVar3;
          if (*(int *)PTR__ZZN4Aska7Machine6_HTONSEtE9kMyEndian_02cbc7a8 != 2) {
            uVar8 = (uint)(uVar3 >> 8) | (uVar3 & 0xff00ff) << 8;
          }
          fVar16 = (float)(uVar8 + 1);
          uVar5 = 0x22;
          goto code_r0x0200e0e8;
        case 9:
          fVar9 = *pfVar19;
          if (((*PTR__ZGVZN4Aska7Machine6_HTONLEjE9kMyEndian_02cbe508 & 1) == 0) &&
             (iVar6 = __cxa_guard_acquire(PTR__ZGVZN4Aska7Machine6_HTONLEjE9kMyEndian_02cbe508),
             iVar6 != 0)) {
            *(undefined4 *)PTR__ZZN4Aska7Machine6_HTONLEjE9kMyEndian_02cc0b50 = 1;
            __cxa_guard_release(PTR__ZGVZN4Aska7Machine6_HTONLEjE9kMyEndian_02cbe508);
          }
          uVar14 = ((uint)fVar9 & 0xff00ff00) >> 8 | ((uint)fVar9 & 0xff00ff) << 8;
          if (*(int *)PTR__ZZN4Aska7Machine6_HTONLEjE9kMyEndian_02cc0b50 != 2) {
            fVar9 = (float)(uVar14 >> 0x10 | uVar14 << 0x10);
          }
          if ((float)((int)fVar9 + 1U) == 0.0) {
            fVar9 = 0.0;
            goto code_r0x0200eb9c;
          }
          fVar16 = (float)((int)fVar9 + 1U);
          uVar5 = 0x22;
          goto code_r0x0200e0e8;
        case 10:
          fVar16 = *pfVar19;
          if (((*PTR__ZGVZN4Aska7Machine6_HTONLEjE9kMyEndian_02cbe508 & 1) == 0) &&
             (iVar6 = __cxa_guard_acquire(PTR__ZGVZN4Aska7Machine6_HTONLEjE9kMyEndian_02cbe508),
             iVar6 != 0)) {
            *(undefined4 *)PTR__ZZN4Aska7Machine6_HTONLEjE9kMyEndian_02cc0b50 = 1;
            __cxa_guard_release(PTR__ZGVZN4Aska7Machine6_HTONLEjE9kMyEndian_02cbe508);
          }
          uVar14 = ((uint)fVar16 & 0xff00ff00) >> 8 | ((uint)fVar16 & 0xff00ff) << 8;
          uVar8 = 10;
          iVar6 = *(int *)PTR__ZZN4Aska7Machine6_HTONLEjE9kMyEndian_02cc0b50;
          *param_3 = 4;
          if (iVar6 != 2) {
            fVar16 = (float)(uVar14 >> 0x10 | uVar14 << 0x10);
          }
          *(double *)(param_3 + 2) = (double)fVar16;
          goto joined_r0x0200e6a4;
        case 0xb:
          uVar8 = 0xb;
          uStack_70 = *(ulong *)pfVar19;
          uVar14 = 4;
          goto code_r0x0200e514;
        case 0xc:
          bVar4 = *(byte *)pfVar19;
          *param_3 = 2;
          uVar8 = 0xc;
          *(ulong *)(param_3 + 2) = (ulong)bVar4;
          goto joined_r0x0200e6a4;
        case 0xd:
          uVar3 = *(ushort *)pfVar19;
          fVar16 = (float)(uint)uVar3;
          if (((*PTR__ZGVZN4Aska7Machine6_HTONSEtE9kMyEndian_02cc0910 & 1) == 0) &&
             (iVar6 = __cxa_guard_acquire(PTR__ZGVZN4Aska7Machine6_HTONSEtE9kMyEndian_02cc0910),
             iVar6 != 0)) {
            *(undefined4 *)PTR__ZZN4Aska7Machine6_HTONSEtE9kMyEndian_02cbc7a8 = 1;
            __cxa_guard_release(PTR__ZGVZN4Aska7Machine6_HTONSEtE9kMyEndian_02cc0910);
          }
          fVar13 = (float)((uint)(uVar3 >> 8) | (uVar3 & 0xff00ff) << 8);
          uVar8 = 0xd;
          piVar10 = (int *)PTR__ZZN4Aska7Machine6_HTONSEtE9kMyEndian_02cbc7a8;
          goto code_r0x0200e4d0;
        case 0xe:
          fVar16 = *pfVar19;
          if (((*PTR__ZGVZN4Aska7Machine6_HTONLEjE9kMyEndian_02cbe508 & 1) == 0) &&
             (iVar6 = __cxa_guard_acquire(PTR__ZGVZN4Aska7Machine6_HTONLEjE9kMyEndian_02cbe508),
             iVar6 != 0)) {
            *(undefined4 *)PTR__ZZN4Aska7Machine6_HTONLEjE9kMyEndian_02cc0b50 = 1;
            __cxa_guard_release(PTR__ZGVZN4Aska7Machine6_HTONLEjE9kMyEndian_02cbe508);
          }
          uVar8 = ((uint)fVar16 & 0xff00ff00) >> 8 | ((uint)fVar16 & 0xff00ff) << 8;
          fVar13 = (float)(uVar8 >> 0x10 | uVar8 << 0x10);
          uVar8 = 0xe;
          piVar10 = (int *)PTR__ZZN4Aska7Machine6_HTONLEjE9kMyEndian_02cc0b50;
code_r0x0200e4d0:
          iVar6 = *piVar10;
          *param_3 = 2;
          if (iVar6 != 2) {
            fVar16 = fVar13;
          }
          uVar22 = (ulong)(uint)fVar16;
code_r0x0200e640:
          *(ulong *)(param_3 + 2) = uVar22;
          goto joined_r0x0200e6a4;
        case 0xf:
          uVar8 = 0xf;
          uStack_70 = *(ulong *)pfVar19;
          uVar14 = 2;
code_r0x0200e514:
          *param_3 = uVar14;
          uVar22 = (uStack_70 & 0xff00ff00ff00ff00) >> 8 | (uStack_70 & 0xff00ff00ff00ff) << 8;
          uVar22 = (uVar22 & 0xffff0000ffff0000) >> 0x10 | (uVar22 & 0xffff0000ffff) << 0x10;
          *(ulong *)(param_3 + 2) = uVar22 >> 0x20 | uVar22 << 0x20;
          goto joined_r0x0200e6a4;
        case 0x10:
          uVar22 = (ulong)*(char *)pfVar19;
          uVar8 = 0x10;
          goto code_r0x0200e694;
        case 0x11:
          uVar3 = *(ushort *)pfVar19;
          if (((*PTR__ZGVZN4Aska7Machine6_HTONSEtE9kMyEndian_02cc0910 & 1) == 0) &&
             (iVar6 = __cxa_guard_acquire(PTR__ZGVZN4Aska7Machine6_HTONSEtE9kMyEndian_02cc0910),
             iVar6 != 0)) {
            *(undefined4 *)PTR__ZZN4Aska7Machine6_HTONSEtE9kMyEndian_02cbc7a8 = 1;
            __cxa_guard_release(PTR__ZGVZN4Aska7Machine6_HTONSEtE9kMyEndian_02cc0910);
          }
          uVar8 = 0x11;
          if (*(int *)PTR__ZZN4Aska7Machine6_HTONSEtE9kMyEndian_02cbc7a8 != 2) {
            uVar3 = uVar3 >> 8 | uVar3 << 8;
          }
          *(long *)(param_3 + 2) = (long)(short)uVar3;
          uVar14 = 2;
          if ((short)uVar3 < 0) {
            uVar14 = 3;
          }
          *param_3 = uVar14;
          goto joined_r0x0200e6a4;
        case 0x12:
          fVar16 = *pfVar19;
          if (((*PTR__ZGVZN4Aska7Machine6_HTONLEjE9kMyEndian_02cbe508 & 1) == 0) &&
             (iVar6 = __cxa_guard_acquire(PTR__ZGVZN4Aska7Machine6_HTONLEjE9kMyEndian_02cbe508),
             iVar6 != 0)) {
            *(undefined4 *)PTR__ZZN4Aska7Machine6_HTONLEjE9kMyEndian_02cc0b50 = 1;
            __cxa_guard_release(PTR__ZGVZN4Aska7Machine6_HTONLEjE9kMyEndian_02cbe508);
          }
          uVar14 = ((uint)fVar16 & 0xff00ff00) >> 8 | ((uint)fVar16 & 0xff00ff) << 8;
          uVar8 = 0x12;
          if (*(int *)PTR__ZZN4Aska7Machine6_HTONLEjE9kMyEndian_02cc0b50 != 2) {
            fVar16 = (float)(uVar14 >> 0x10 | uVar14 << 0x10);
          }
          uVar22 = (ulong)(int)fVar16;
          *param_3 = (uint)fVar16 >> 0x1f | 2;
          goto code_r0x0200e640;
        case 0x13:
          uVar8 = 0x13;
          uVar22 = (*(ulong *)pfVar19 & 0xff00ff00ff00ff00) >> 8 |
                   (*(ulong *)pfVar19 & 0xff00ff00ff00ff) << 8;
          uVar22 = (uVar22 & 0xffff0000ffff0000) >> 0x10 | (uVar22 & 0xffff0000ffff) << 0x10;
          uVar22 = uVar22 >> 0x20 | uVar22 << 0x20;
code_r0x0200e694:
          *(ulong *)(param_3 + 2) = uVar22;
          uVar14 = 2;
          if ((long)uVar22 < 0) {
            uVar14 = 3;
          }
          *param_3 = uVar14;
          goto joined_r0x0200e6a4;
        case 0x14:
          goto code_r0x0200e0e8;
        case 0x15:
          fVar16 = 4.2039e-45;
          uVar5 = 0x22;
          goto code_r0x0200e0e8;
        case 0x16:
          fVar16 = 7.00649e-45;
          uVar5 = 0x22;
          goto code_r0x0200e0e8;
        case 0x17:
          fVar16 = 1.26117e-44;
          uVar5 = 0x22;
          goto code_r0x0200e0e8;
        case 0x18:
          fVar16 = 2.38221e-44;
          uVar5 = 0x22;
          goto code_r0x0200e0e8;
        case 0x19:
          goto code_r0x0200e6dc;
        case 0x1a:
          uVar3 = *(ushort *)pfVar19;
          if (((*PTR__ZGVZN4Aska7Machine6_HTONSEtE9kMyEndian_02cc0910 & 1) == 0) &&
             (iVar6 = __cxa_guard_acquire(PTR__ZGVZN4Aska7Machine6_HTONSEtE9kMyEndian_02cc0910),
             iVar6 != 0)) {
            *(undefined4 *)PTR__ZZN4Aska7Machine6_HTONSEtE9kMyEndian_02cbc7a8 = 1;
            __cxa_guard_release(PTR__ZGVZN4Aska7Machine6_HTONSEtE9kMyEndian_02cc0910);
          }
          fVar9 = (float)(uint)uVar3;
          if (*(int *)PTR__ZZN4Aska7Machine6_HTONSEtE9kMyEndian_02cbc7a8 != 2) {
            fVar9 = (float)((uint)(uVar3 >> 8) | (uVar3 & 0xff00ff) << 8);
          }
          if (fVar9 != 0.0) goto code_r0x0200e7d0;
          uVar14 = 0x1a;
          goto code_r0x0200ebe8;
        case 0x1b:
          fVar9 = *pfVar19;
          if (((*PTR__ZGVZN4Aska7Machine6_HTONLEjE9kMyEndian_02cbe508 & 1) == 0) &&
             (iVar6 = __cxa_guard_acquire(PTR__ZGVZN4Aska7Machine6_HTONLEjE9kMyEndian_02cbe508),
             iVar6 != 0)) {
            *(undefined4 *)PTR__ZZN4Aska7Machine6_HTONLEjE9kMyEndian_02cc0b50 = 1;
            __cxa_guard_release(PTR__ZGVZN4Aska7Machine6_HTONLEjE9kMyEndian_02cbe508);
          }
          uVar8 = ((uint)fVar9 & 0xff00ff00) >> 8 | ((uint)fVar9 & 0xff00ff) << 8;
          if (*(int *)PTR__ZZN4Aska7Machine6_HTONLEjE9kMyEndian_02cc0b50 != 2) {
            fVar9 = (float)(uVar8 >> 0x10 | uVar8 << 0x10);
          }
          if (fVar9 == 0.0) {
            fVar9 = 0.0;
            uVar14 = 0x1b;
            goto code_r0x0200ebe8;
          }
code_r0x0200e7d0:
          fVar16 = fVar9;
          uVar5 = 0x20;
          goto code_r0x0200e0e8;
        case 0x1c:
          uVar3 = *(ushort *)pfVar19;
          if (((*PTR__ZGVZN4Aska7Machine6_HTONSEtE9kMyEndian_02cc0910 & 1) == 0) &&
             (iVar6 = __cxa_guard_acquire(PTR__ZGVZN4Aska7Machine6_HTONSEtE9kMyEndian_02cc0910),
             iVar6 != 0)) {
            *(undefined4 *)PTR__ZZN4Aska7Machine6_HTONSEtE9kMyEndian_02cbc7a8 = 1;
            __cxa_guard_release(PTR__ZGVZN4Aska7Machine6_HTONSEtE9kMyEndian_02cc0910);
          }
          fVar16 = (float)(uint)uVar3;
          if (*(int *)PTR__ZZN4Aska7Machine6_HTONSEtE9kMyEndian_02cbc7a8 != 2) {
            fVar16 = (float)((uint)(uVar3 >> 8) | (uVar3 & 0xff00ff) << 8);
          }
          if (0x1f < uVar20) {
            uVar8 = 0x1c;
            goto code_r0x0200ef84;
          }
          puVar17 = param_3 + (ulong)uVar20 * 0x14 + 0xc;
          *puVar17 = 6;
          uVar22 = (ulong)(uint)fVar16;
          puStack_a0 = param_3 + (ulong)uVar20 * 0x14 + 0x10;
          *puStack_a0 = 0;
          puVar12 = param_3 + (ulong)uVar20 * 0x14 + 0xe;
          lVar7 = Aska::ASON::Malloc(unsigned long)(param_2,uVar22 << 5);
          if (lVar7 != 0) {
            if (fVar16 != 0.0) {
              puVar11 = (undefined8 *)(lVar7 + 8);
              do {
                *(undefined4 *)(puVar11 + -1) = 0;
                puVar11[1] = 0;
                puVar11[2] = 0;
                *puVar11 = 0;
                uVar22 = uVar22 - 1;
                puVar11 = puVar11 + 4;
              } while (uVar22 != 0);
            }
            *(long *)puVar12 = lVar7;
code_r0x0200ec64:
            *(undefined2 *)(param_3 + (ulong)uVar20 * 0x14 + 0x11) = *(undefined2 *)(param_2 + 0x58)
            ;
            *(undefined2 *)(param_3 + (ulong)uVar20 * 0x14 + 0x16) = *(undefined2 *)(param_2 + 0x58)
            ;
            if (fVar16 != 0.0) {
code_r0x0200ecc8:
              param_3[(ulong)uVar20 * 0x14 + 0x14] = (uint)fVar16;
              param_3[(ulong)uVar20 * 0x14 + 0x15] = 0;
              goto code_r0x0200ed58;
            }
            uVar23 = *(undefined8 *)(param_3 + (ulong)uVar20 * 0x14 + 0x12);
            uVar15 = *(undefined8 *)(param_3 + (ulong)uVar20 * 0x14 + 0x10);
            uVar8 = 0x1c;
            goto code_r0x0200eda0;
          }
          puVar12[0] = 0;
          puVar12[1] = 0;
          if (fVar16 == 0.0) goto code_r0x0200ec64;
          uVar8 = 0x1c;
          goto code_r0x0200ef7c;
        case 0x1d:
          fVar16 = *pfVar19;
          if (((*PTR__ZGVZN4Aska7Machine6_HTONLEjE9kMyEndian_02cbe508 & 1) == 0) &&
             (iVar6 = __cxa_guard_acquire(PTR__ZGVZN4Aska7Machine6_HTONLEjE9kMyEndian_02cbe508),
             iVar6 != 0)) {
            *(undefined4 *)PTR__ZZN4Aska7Machine6_HTONLEjE9kMyEndian_02cc0b50 = 1;
            __cxa_guard_release(PTR__ZGVZN4Aska7Machine6_HTONLEjE9kMyEndian_02cbe508);
          }
          uVar8 = ((uint)fVar16 & 0xff00ff00) >> 8 | ((uint)fVar16 & 0xff00ff) << 8;
          if (*(int *)PTR__ZZN4Aska7Machine6_HTONLEjE9kMyEndian_02cc0b50 != 2) {
            fVar16 = (float)(uVar8 >> 0x10 | uVar8 << 0x10);
          }
          if (0x1f < uVar20) {
            uVar8 = 0x1d;
            goto code_r0x0200ef84;
          }
          puVar17 = param_3 + (ulong)uVar20 * 0x14 + 0xc;
          *puVar17 = 6;
          uVar22 = (ulong)(uint)fVar16;
          puStack_a0 = param_3 + (ulong)uVar20 * 0x14 + 0x10;
          *puStack_a0 = 0;
          puVar12 = param_3 + (ulong)uVar20 * 0x14 + 0xe;
          lVar7 = Aska::ASON::Malloc(unsigned long)(param_2,uVar22 << 5);
          if (lVar7 != 0) {
            if (fVar16 != 0.0) {
              puVar11 = (undefined8 *)(lVar7 + 8);
              do {
                *(undefined4 *)(puVar11 + -1) = 0;
                puVar11[1] = 0;
                puVar11[2] = 0;
                *puVar11 = 0;
                uVar22 = uVar22 - 1;
                puVar11 = puVar11 + 4;
              } while (uVar22 != 0);
            }
            *(long *)puVar12 = lVar7;
code_r0x0200eca4:
            *(undefined2 *)(param_3 + (ulong)uVar20 * 0x14 + 0x11) = *(undefined2 *)(param_2 + 0x58)
            ;
            *(undefined2 *)(param_3 + (ulong)uVar20 * 0x14 + 0x16) = *(undefined2 *)(param_2 + 0x58)
            ;
            if (fVar16 != 0.0) goto code_r0x0200ecc8;
            uVar23 = *(undefined8 *)(param_3 + (ulong)uVar20 * 0x14 + 0x12);
            uVar15 = *(undefined8 *)(param_3 + (ulong)uVar20 * 0x14 + 0x10);
            uVar8 = 0x1d;
code_r0x0200ed8c:
            *(undefined8 *)(param_3 + 6) = uVar23;
            *(undefined8 *)(param_3 + 4) = uVar15;
            uVar23 = *(undefined8 *)(puVar17 + 2);
            uVar15 = *(undefined8 *)puVar17;
            goto code_r0x0200eda8;
          }
          puVar12[0] = 0;
          puVar12[1] = 0;
          if (fVar16 == 0.0) goto code_r0x0200eca4;
          uVar8 = 0x1d;
          goto code_r0x0200ef7c;
        case 0x1e:
          uVar3 = *(ushort *)pfVar19;
          if (((*PTR__ZGVZN4Aska7Machine6_HTONSEtE9kMyEndian_02cc0910 & 1) == 0) &&
             (iVar6 = __cxa_guard_acquire(PTR__ZGVZN4Aska7Machine6_HTONSEtE9kMyEndian_02cc0910),
             iVar6 != 0)) {
            *(undefined4 *)PTR__ZZN4Aska7Machine6_HTONSEtE9kMyEndian_02cbc7a8 = 1;
            __cxa_guard_release(PTR__ZGVZN4Aska7Machine6_HTONSEtE9kMyEndian_02cc0910);
          }
          fVar16 = (float)(uint)uVar3;
          if (*(int *)PTR__ZZN4Aska7Machine6_HTONSEtE9kMyEndian_02cbc7a8 != 2) {
            fVar16 = (float)((uint)(uVar3 >> 8) | (uVar3 & 0xff00ff) << 8);
          }
          if (0x1f < uVar20) {
            uVar8 = 0x1e;
            goto code_r0x0200ef84;
          }
          puVar17 = param_3 + (ulong)uVar20 * 0x14 + 0xc;
          *puVar17 = 7;
          uVar22 = (ulong)(uint)fVar16;
          puStack_a0 = param_3 + (ulong)uVar20 * 0x14 + 0x10;
          *puStack_a0 = 0;
          puVar12 = param_3 + (ulong)uVar20 * 0x14 + 0xe;
          lVar7 = Aska::ASON::Malloc(unsigned long)(param_2,uVar22 << 6);
          if (lVar7 != 0) {
            if (fVar16 != 0.0) {
              puVar11 = (undefined8 *)(lVar7 + 0x28);
              do {
                *(undefined4 *)(puVar11 + -5) = 0;
                puVar11[1] = 0;
                puVar11[2] = 0;
                *puVar11 = 0;
                puVar11[-3] = 0;
                puVar11[-2] = 0;
                *(undefined4 *)(puVar11 + -1) = 0;
                puVar11[-4] = 0;
                uVar22 = uVar22 - 1;
                puVar11 = puVar11 + 8;
              } while (uVar22 != 0);
            }
            *(long *)puVar12 = lVar7;
code_r0x0200ece4:
            *(undefined2 *)(param_3 + (ulong)uVar20 * 0x14 + 0x11) = *(undefined2 *)(param_2 + 0x58)
            ;
            *(undefined2 *)(param_3 + (ulong)uVar20 * 0x14 + 0x16) = *(undefined2 *)(param_2 + 0x58)
            ;
            if (fVar16 == 0.0) {
              uVar23 = *(undefined8 *)(param_3 + (ulong)uVar20 * 0x14 + 0x12);
              uVar15 = *(undefined8 *)(param_3 + (ulong)uVar20 * 0x14 + 0x10);
              uVar8 = 0x1e;
              goto code_r0x0200ed8c;
            }
code_r0x0200ed48:
            param_3[(ulong)uVar20 * 0x14 + 0x14] = (uint)fVar16;
            param_3[(ulong)uVar20 * 0x14 + 0x15] = 1;
code_r0x0200ed58:
            uVar20 = uVar20 + 1;
            *puStack_a0 = *puStack_a0 + 1;
            goto code_r0x0200eec4;
          }
          puVar12[0] = 0;
          puVar12[1] = 0;
          if (fVar16 == 0.0) goto code_r0x0200ece4;
          uVar8 = 0x1e;
          goto code_r0x0200ef7c;
        case 0x1f:
          fVar16 = *pfVar19;
          if (((*PTR__ZGVZN4Aska7Machine6_HTONLEjE9kMyEndian_02cbe508 & 1) == 0) &&
             (iVar6 = __cxa_guard_acquire(PTR__ZGVZN4Aska7Machine6_HTONLEjE9kMyEndian_02cbe508),
             iVar6 != 0)) {
            *(undefined4 *)PTR__ZZN4Aska7Machine6_HTONLEjE9kMyEndian_02cc0b50 = 1;
            __cxa_guard_release(PTR__ZGVZN4Aska7Machine6_HTONLEjE9kMyEndian_02cbe508);
          }
          uVar8 = ((uint)fVar16 & 0xff00ff00) >> 8 | ((uint)fVar16 & 0xff00ff) << 8;
          if (*(int *)PTR__ZZN4Aska7Machine6_HTONLEjE9kMyEndian_02cc0b50 != 2) {
            fVar16 = (float)(uVar8 >> 0x10 | uVar8 << 0x10);
          }
          if (0x1f < uVar20) {
            uVar8 = 0x1f;
            goto code_r0x0200ef84;
          }
          puVar17 = param_3 + (ulong)uVar20 * 0x14 + 0xc;
          *puVar17 = 7;
          uVar22 = (ulong)(uint)fVar16;
          puStack_a0 = param_3 + (ulong)uVar20 * 0x14 + 0x10;
          *puStack_a0 = 0;
          puVar12 = param_3 + (ulong)uVar20 * 0x14 + 0xe;
          lVar7 = Aska::ASON::Malloc(unsigned long)(param_2,uVar22 << 6);
          if (lVar7 != 0) {
            if (fVar16 != 0.0) {
              puVar11 = (undefined8 *)(lVar7 + 0x28);
              do {
                *(undefined4 *)(puVar11 + -5) = 0;
                puVar11[1] = 0;
                puVar11[2] = 0;
                *puVar11 = 0;
                puVar11[-3] = 0;
                puVar11[-2] = 0;
                *(undefined4 *)(puVar11 + -1) = 0;
                puVar11[-4] = 0;
                uVar22 = uVar22 - 1;
                puVar11 = puVar11 + 8;
              } while (uVar22 != 0);
            }
            *(long *)puVar12 = lVar7;
code_r0x0200ed24:
            *(undefined2 *)(param_3 + (ulong)uVar20 * 0x14 + 0x11) = *(undefined2 *)(param_2 + 0x58)
            ;
            *(undefined2 *)(param_3 + (ulong)uVar20 * 0x14 + 0x16) = *(undefined2 *)(param_2 + 0x58)
            ;
            if (fVar16 != 0.0) goto code_r0x0200ed48;
            uVar23 = *(undefined8 *)(param_3 + (ulong)uVar20 * 0x14 + 0x12);
            uVar15 = *(undefined8 *)(param_3 + (ulong)uVar20 * 0x14 + 0x10);
            uVar8 = 0x1f;
code_r0x0200eda0:
            *(undefined8 *)(param_3 + 6) = uVar23;
            *(undefined8 *)(param_3 + 4) = uVar15;
            uVar23 = *(undefined8 *)(puVar17 + 2);
            uVar15 = *(undefined8 *)puVar17;
code_r0x0200eda8:
            *(undefined8 *)(param_3 + 2) = uVar23;
            *(undefined8 *)param_3 = uVar15;
            goto joined_r0x0200e6a4;
          }
          puVar12[0] = 0;
          puVar12[1] = 0;
          if (fVar16 == 0.0) goto code_r0x0200ed24;
          uVar8 = 0x1f;
          goto code_r0x0200ef7c;
        case 0x20:
          goto code_r0x0200ebe8;
        case 0x21:
          break;
        case 0x22:
code_r0x0200eb9c:
          uVar14 = param_3[(ulong)uVar20 * 0x14 + 0x16];
          *param_3 = 9;
          *(long *)(param_3 + 2) = (long)pfVar19 + 1;
          param_3[4] = (int)fVar9 - 1;
          uVar2 = *(undefined1 *)pfVar19;
          *(short *)((long)param_3 + 0x16) = (short)uVar14;
          *(undefined1 *)(param_3 + 5) = uVar2;
          goto joined_r0x0200e6a4;
        default:
          goto code_r0x0200ef84;
        }
        uVar14 = param_3[(ulong)uVar20 * 0x14 + 0x16];
        *param_3 = 8;
        *(float **)(param_3 + 2) = pfVar19;
        param_3[4] = (uint)fVar9;
        *(short *)(param_3 + 5) = (short)uVar14;
        goto joined_r0x0200e6a4;
      }
      uVar14 = 0;
      goto code_r0x0200ebe8;
    }
    uVar8 = uVar14 & 0xf;
    if (uVar14 < 0x90) {
      if (0x1f < uVar20) goto code_r0x0200ef3c;
      uVar22 = (ulong)uVar8;
      param_3[(ulong)uVar20 * 0x14 + 0xc] = 7;
      puVar12 = param_3 + (ulong)uVar20 * 0x14 + 0xe;
      puVar17 = param_3 + (ulong)uVar20 * 0x14 + 0x10;
      *puVar17 = 0;
      lVar7 = Aska::ASON::Malloc(unsigned long)(param_2,uVar22 << 6);
      if (lVar7 == 0) {
        puVar12[0] = 0;
        puVar12[1] = 0;
        if ((bVar4 & 0xf) != 0) goto code_r0x0200ef74;
      }
      else {
        if ((bVar4 & 0xf) != 0) {
          puVar11 = (undefined8 *)(lVar7 + 0x28);
          do {
            *(undefined4 *)(puVar11 + -5) = 0;
            puVar11[1] = 0;
            puVar11[2] = 0;
            *puVar11 = 0;
            puVar11[-3] = 0;
            puVar11[-2] = 0;
            *(undefined4 *)(puVar11 + -1) = 0;
            puVar11[-4] = 0;
            uVar22 = uVar22 - 1;
            puVar11 = puVar11 + 8;
          } while (uVar22 != 0);
        }
        *(long *)puVar12 = lVar7;
      }
      *(undefined2 *)(param_3 + (ulong)uVar20 * 0x14 + 0x11) = *(undefined2 *)(param_2 + 0x58);
      uVar22 = (ulong)uVar20;
      *(undefined2 *)(param_3 + uVar22 * 0x14 + 0x16) = *(undefined2 *)(param_2 + 0x58);
      if ((bVar4 & 0xf) == 0) {
        uVar8 = 0;
        uVar15 = *(undefined8 *)(param_3 + (ulong)uVar20 * 0x14 + 0x10);
        *(undefined8 *)(param_3 + 6) = *(undefined8 *)(param_3 + (ulong)uVar20 * 0x14 + 0x12);
        *(undefined8 *)(param_3 + 4) = uVar15;
        uVar23 = *(undefined8 *)(param_3 + (ulong)uVar20 * 0x14 + 0xe);
        uVar15 = *(undefined8 *)(param_3 + (ulong)uVar20 * 0x14 + 0xc);
        goto code_r0x0200e084;
      }
      param_3[uVar22 * 0x14 + 0x14] = uVar8;
      param_3[uVar22 * 0x14 + 0x15] = 1;
      *puVar17 = *puVar17 + 1;
    }
    else {
      if (0x1f < uVar20) {
code_r0x0200ef3c:
        uVar8 = 0;
code_r0x0200ef84:
        pfVar19 = pfVar21;
        uVar15 = 0xffffffffffffffff;
        goto code_r0x0200ef88;
      }
      param_3[(ulong)uVar20 * 0x14 + 0xc] = 6;
      uVar22 = (ulong)uVar8;
      puVar17 = param_3 + (ulong)uVar20 * 0x14 + 0x10;
      *puVar17 = 0;
      puVar12 = param_3 + (ulong)uVar20 * 0x14 + 0xe;
      lVar7 = Aska::ASON::Malloc(unsigned long)(param_2,uVar22 << 5);
      if (lVar7 == 0) {
        puVar12[0] = 0;
        puVar12[1] = 0;
        if ((bVar4 & 0xf) != 0) {
code_r0x0200ef74:
          uVar8 = 0;
code_r0x0200ef7c:
          *(undefined8 *)(param_2 + 0x80) = 0xfffffffffffffc41;
          goto code_r0x0200ef84;
        }
      }
      else {
        if ((bVar4 & 0xf) != 0) {
          puVar11 = (undefined8 *)(lVar7 + 8);
          do {
            *(undefined4 *)(puVar11 + -1) = 0;
            puVar11[1] = 0;
            puVar11[2] = 0;
            *puVar11 = 0;
            uVar22 = uVar22 - 1;
            puVar11 = puVar11 + 4;
          } while (uVar22 != 0);
        }
        *(long *)puVar12 = lVar7;
      }
      *(undefined2 *)(param_3 + (ulong)uVar20 * 0x14 + 0x11) = *(undefined2 *)(param_2 + 0x58);
      uVar22 = (ulong)uVar20;
      *(undefined2 *)(param_3 + uVar22 * 0x14 + 0x16) = *(undefined2 *)(param_2 + 0x58);
      if ((bVar4 & 0xf) == 0) {
        uVar15 = *(undefined8 *)(param_3 + (ulong)uVar20 * 0x14 + 0x10);
        *(undefined8 *)(param_3 + 6) = *(undefined8 *)(param_3 + (ulong)uVar20 * 0x14 + 0x12);
        *(undefined8 *)(param_3 + 4) = uVar15;
        uVar23 = *(undefined8 *)(param_3 + (ulong)uVar20 * 0x14 + 0xe);
        uVar15 = *(undefined8 *)(param_3 + (ulong)uVar20 * 0x14 + 0xc);
code_r0x0200e084:
        *(undefined8 *)(param_3 + 2) = uVar23;
        *(undefined8 *)param_3 = uVar15;
        goto joined_r0x0200e6a4;
      }
      param_3[uVar22 * 0x14 + 0x14] = uVar8;
      param_3[uVar22 * 0x14 + 0x15] = 0;
      *puVar17 = *puVar17 + 1;
    }
    uVar20 = uVar20 + 1;
    goto code_r0x0200eec4;
  }
  uVar15 = 0;
code_r0x0200ef88:
  *param_1 = uVar15;
  param_3[8] = uVar8;
  param_3[9] = (uint)fVar9;
  param_3[10] = uVar20;
  *param_6 = (long)pfVar19 - param_4;
  return;
code_r0x0200e6dc:
  fVar9 = (float)(uint)*(byte *)pfVar19;
  if (fVar9 == 0.0) goto code_r0x0200e6e4;
  goto code_r0x0200e0d8;
code_r0x0200e6e4:
  uVar14 = 0x19;
code_r0x0200ebe8:
  uVar8 = uVar14;
  pfVar19 = pfVar21;
  iVar6 = Aska::ASON::UnpackValue_str(Aska::ASON::AValue*, signed char const*, signed char const*, unsigned int, unsigned short)(param_2,param_3,param_4,pfVar18,fVar9,
                          (short)param_3[(ulong)uVar20 * 0x14 + 0x16]);
  pfVar21 = pfVar19;
  if (iVar6 < 0) {
    uVar15 = 0xffffffffffffffff;
    goto code_r0x0200ef88;
  }
joined_r0x0200e6a4:
  if (uVar20 != 0) {
    puVar12 = param_3 + (ulong)(uVar20 - 1) * 0x14 + 0x18;
    do {
      uVar14 = puVar12[-3];
      if (uVar14 == 0) {
        uVar15 = *(undefined8 *)(param_3 + 4);
        puVar11 = (undefined8 *)(*(long *)(puVar12 + -10) + (ulong)(puVar12[-8] - 1) * 0x20);
        puVar11[3] = *(undefined8 *)(param_3 + 6);
        puVar11[2] = uVar15;
        uVar15 = *(undefined8 *)param_3;
        puVar11[1] = *(undefined8 *)(param_3 + 2);
        *puVar11 = uVar15;
        uVar14 = puVar12[-4];
        puVar12[-4] = uVar14 - 1;
        if (uVar14 - 1 != 0) {
          puVar12[-8] = puVar12[-8] + 1;
          goto code_r0x0200eec4;
        }
      }
      else {
        if (uVar14 != 2) {
          if (uVar14 != 1) goto code_r0x0200ef84;
          uVar15 = *(undefined8 *)(param_3 + 4);
          *(undefined8 *)(puVar12 + 6) = *(undefined8 *)(param_3 + 6);
          *(undefined8 *)(puVar12 + 4) = uVar15;
          uVar23 = *(undefined8 *)(param_3 + 2);
          uVar15 = *(undefined8 *)param_3;
          puVar12[-3] = 2;
          *(undefined8 *)(puVar12 + 2) = uVar23;
          *(undefined8 *)puVar12 = uVar15;
          goto code_r0x0200eec4;
        }
        uVar15 = *(undefined8 *)(puVar12 + 4);
        puVar11 = (undefined8 *)(*(long *)(puVar12 + -10) + (ulong)(puVar12[-8] - 1) * 0x40);
        puVar11[3] = *(undefined8 *)(puVar12 + 6);
        puVar11[2] = uVar15;
        uVar15 = *(undefined8 *)puVar12;
        puVar11[1] = *(undefined8 *)(puVar12 + 2);
        *puVar11 = uVar15;
        uVar15 = *(undefined8 *)(param_3 + 4);
        lVar7 = *(long *)(puVar12 + -10) + (ulong)(puVar12[-8] - 1) * 0x40;
        *(undefined8 *)(lVar7 + 0x38) = *(undefined8 *)(param_3 + 6);
        *(undefined8 *)(lVar7 + 0x30) = uVar15;
        uVar15 = *(undefined8 *)param_3;
        *(undefined8 *)(lVar7 + 0x28) = *(undefined8 *)(param_3 + 2);
        *(undefined8 *)(lVar7 + 0x20) = uVar15;
        uVar14 = puVar12[-4];
        puVar12[-4] = uVar14 - 1;
        if (uVar14 - 1 != 0) goto code_r0x0200eea0;
      }
      uVar15 = *(undefined8 *)(puVar12 + -8);
      uVar20 = uVar20 - 1;
      *(undefined8 *)(param_3 + 6) = *(undefined8 *)(puVar12 + -6);
      *(undefined8 *)(param_3 + 4) = uVar15;
      puVar17 = puVar12 + -10;
      uVar15 = *(undefined8 *)(puVar12 + -0xc);
      puVar12 = puVar12 + -0x14;
      *(undefined8 *)(param_3 + 2) = *(undefined8 *)puVar17;
      *(undefined8 *)param_3 = uVar15;
      if (uVar20 == 0) break;
    } while( true );
  }
  goto code_r0x0200eed8;
code_r0x0200eea0:
  puVar12[-8] = puVar12[-8] + 1;
  puVar12[-3] = 1;
code_r0x0200eec4:
  pfVar19 = (float *)((long)pfVar21 + 1);
  uVar8 = 0;
  pfVar21 = pfVar1;
  if (pfVar19 == pfVar1) goto code_r0x0200eed8;
  goto code_r0x0200ddb8;
code_r0x0200eed8:
  uVar15 = 0;
  pfVar19 = (float *)((long)pfVar21 + 1);
  *(undefined8 *)(param_3 + 0x12) = *(undefined8 *)(param_3 + 6);
  *(undefined8 *)(param_3 + 0x10) = *(undefined8 *)(param_3 + 4);
  *(undefined8 *)(param_3 + 0xe) = *(undefined8 *)(param_3 + 2);
  *(undefined8 *)(param_3 + 0xc) = *(undefined8 *)param_3;
  goto code_r0x0200ef88;
}

// ==== Aska::ASON::SerializeText(void*, unsigned long, Aska::ASON::AValue const*) const
// vaddr 0x1f0efc0 | ghidra 0x200efc0 | size 380 | symbol _ZNK4Aska4ASON13SerializeTextEPvmPKNS0_6AValueE | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZNK4Aska4ASON13SerializeTextEPvmPKNS0_6AValueE(long param_1,long param_2,long param_3,int *param_4)

{
  undefined *puVar1;
  long *plVar2;
  ulong uVar3;
  undefined8 uVar4;
  long alStack_a0 [9];
  undefined8 uStack_58;
  undefined *puStack_50;
  int iStack_48;
  long *plStack_40;
  long lStack_38;
  
  if (*(char *)(param_1 + 0x8a) == '\0') {
    uVar4 = 0xfffffffffffffc44;
code_r0x0200f0a0:
    *(undefined8 *)(param_1 + 0x80) = uVar4;
    return 0;
  }
  if (((param_2 == 0) || (param_3 == 0)) || (param_4 == (int *)0x0)) {
    uVar4 = 0xfffffffffffffc43;
    goto code_r0x0200f0a0;
  }
  *(undefined8 *)(param_1 + 0x80) = 0;
  uVar3 = Aska::JsonParser::Initialize(bool, Aska::MemoryManager*)(0,0);
  if ((uVar3 & 1) == 0) {
    uVar4 = 0xffffffffffffffff;
    goto code_r0x0200f0a0;
  }
  if (*param_4 == 0) {
    uVar4 = 0xfffffffffffffc5c;
    goto code_r0x0200f0a0;
  }
  puVar1 = PTR__ZTVN4Aska10JsonParser6JValueE_02cbbfd0 + 0x10;
  iStack_48 = 0;
  plStack_40 = (long *)0x0;
  lStack_38 = 0;
  puStack_50 = puVar1;
  Aska::ASON::AValue2JValue(Aska::ASON::AValue const*, Aska::JsonParser::JValue*)(alStack_a0,param_1,param_4,&puStack_50);
  if (alStack_a0[0] < 0) {
    uVar4 = 0;
  }
  else {
    uStack_58 = 0;
    Aska::JsonParser::JsonParser()(alStack_a0);
    uVar3 = Aska::JsonParser::Serialize(Aska::JsonParser::JValue*, char*, unsigned long, unsigned long*)(alStack_a0,&puStack_50,param_2,param_3,&uStack_58);
    uVar4 = uStack_58;
    if ((uVar3 & 1) == 0) {
      *(undefined8 *)(param_1 + 0x80) = 0xffffffffffffffff;
    }
    Aska::JsonParser::~JsonParser()(alStack_a0);
  }
  plVar2 = plStack_40;
  if (iStack_48 == 3) {
    puStack_50 = puVar1;
    if (plStack_40 == (long *)0x0) goto code_r0x0200f128;
    operator delete[](void*)();
  }
  else if (iStack_48 == 5) {
    puStack_50 = puVar1;
    if (plStack_40 == (long *)0x0) goto code_r0x0200f128;
    Aska::JsonParser::JValue::JObject::~JObject()(plStack_40);
    operator delete(void*)(plVar2);
  }
  else {
    puStack_50 = puVar1;
    if ((iStack_48 != 4) || (plStack_40 == (long *)0x0)) goto code_r0x0200f128;
    (**(code **)(*plStack_40 + 8))();
  }
  plStack_40 = (long *)0x0;
code_r0x0200f128:
  if (lStack_38 == 0) {
    return uVar4;
  }
  operator delete[](void*)();
  return uVar4;
}

// ==== Aska::ASON::AValue2JValue(Aska::ASON::AValue const*, Aska::JsonParser::JValue*)
// vaddr 0x1f0f13c | ghidra 0x200f13c | size 1324 | symbol _ZN4Aska4ASON13AValue2JValueEPKNS0_6AValueEPNS_10JsonParser6JValueE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska4ASON13AValue2JValueEPKNS0_6AValueEPNS_10JsonParser6JValueE
               (long *param_1,long param_2,int *param_3,long param_4)

{
  uint uVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  long lVar5;
  int iVar6;
  long *plVar7;
  undefined8 *puVar8;
  undefined8 *puVar9;
  ulong uVar10;
  undefined8 uVar11;
  ulong uVar12;
  ulong uVar13;
  long lVar14;
  ulong uVar15;
  long lVar16;
  long lStack_70;
  long lStack_68;
  
  switch(*param_3) {
  case 0:
    *(undefined4 *)(param_4 + 8) = 0;
    goto code_r0x0200f200;
  case 1:
    *(undefined4 *)(param_4 + 8) = 1;
    iVar6 = param_3[2];
    *(undefined8 *)(param_4 + 0x18) = 0;
    *(char *)(param_4 + 0x10) = (char)iVar6;
    break;
  case 2:
    *(undefined4 *)(param_4 + 8) = 2;
    uVar11 = *(undefined8 *)(param_3 + 2);
    *(undefined8 *)(param_4 + 0x18) = 0;
    uVar11 = NEON_ucvtf(uVar11);
    *(undefined8 *)(param_4 + 0x10) = uVar11;
    break;
  case 3:
    *(undefined4 *)(param_4 + 8) = 2;
    lVar14 = *(long *)(param_3 + 2);
    *(undefined8 *)(param_4 + 0x18) = 0;
    *(double *)(param_4 + 0x10) = (double)lVar14;
    break;
  case 4:
    *(undefined4 *)(param_4 + 8) = 2;
    *(undefined8 *)(param_4 + 0x10) = *(undefined8 *)(param_3 + 2);
    *(undefined8 *)(param_4 + 0x18) = 0;
    break;
  case 5:
  case 8:
  case 9:
    *(undefined4 *)(param_4 + 8) = 3;
    puVar3 = PTR__ZN4Aska10JsonParser16s_pMemoryManagerE_02cc46b0;
    if (*param_3 == 5) {
      lVar14 = *(long *)(param_3 + 4);
      uVar1 = param_3[6];
    }
    else {
      lVar14 = 0;
      uVar1 = param_3[4];
    }
    if (uVar1 != 0) {
      uVar15 = (ulong)uVar1;
      lVar16 = *(long *)(param_3 + 2);
      if (lVar16 != 0) {
        if (lVar14 == 0) {
          if (*(long *)PTR__ZN4Aska10JsonParser16s_pMemoryManagerE_02cc46b0 == 0) {
            lVar14 = operator new[](unsigned long, std::nothrow_t const&)(uVar15 + 1,PTR__ZSt7nothrow_02cb9a80);
          }
          else {
            lVar14 = Aska::MemoryManager::Malloc(unsigned long)();
          }
          if (lVar14 == 0) goto code_r0x0200f568;
          memcpy(lVar14,lVar16,uVar15);
          *(undefined1 *)(lVar14 + uVar15) = 0;
          iVar6 = Aska::StringUtility::Utf8ToMultiByte(char const*, char*, unsigned int)(lVar14,0,0);
          lVar16 = (long)iVar6;
          if (iVar6 < 0) {
            operator delete[](void*)(lVar14);
            *(long *)(param_2 + 0x80) = lVar16;
            *param_1 = lVar16;
            return;
          }
          if (*(long *)puVar3 == 0) {
            uVar11 = operator new[](unsigned long, std::nothrow_t const&)(lVar16,PTR__ZSt7nothrow_02cb9a80);
          }
          else {
            uVar11 = Aska::MemoryManager::Malloc(unsigned long)(*(long *)puVar3,lVar16);
          }
          *(undefined8 *)(param_4 + 0x18) = uVar11;
          Aska::StringUtility::Utf8ToMultiByte(char const*, char*, unsigned int)(lVar14,uVar11,iVar6);
          uVar11 = Aska::JsonParser::_MultiToWide(char const*)(*(undefined8 *)(param_4 + 0x18));
          *(undefined8 *)(param_4 + 0x10) = uVar11;
          operator delete[](void*)(lVar14);
          break;
        }
        lVar16 = strlen(lVar14);
        uVar15 = lVar16 + 1;
        if (*(long *)PTR__ZN4Aska10JsonParser16s_pMemoryManagerE_02cc46b0 == 0) {
          lVar16 = operator new[](unsigned long, std::nothrow_t const&)(uVar15,PTR__ZSt7nothrow_02cb9a80);
        }
        else {
          lVar16 = Aska::MemoryManager::Malloc(unsigned long)(*(long *)PTR__ZN4Aska10JsonParser16s_pMemoryManagerE_02cc46b0,
                                   uVar15);
        }
        *(long *)(param_4 + 0x18) = lVar16;
        if (lVar16 != 0) {
          uVar10 = strlen(lVar14);
          if (uVar10 < uVar15) {
            strcpy(lVar16,lVar14);
          }
          else {
            raise(5);
          }
          uVar11 = Aska::JsonParser::_MultiToWide(char const*)(*(undefined8 *)(param_4 + 0x18));
          *(undefined8 *)(param_4 + 0x10) = uVar11;
          break;
        }
        goto code_r0x0200f568;
      }
    }
    *(undefined8 *)(param_4 + 0x10) = 0;
code_r0x0200f200:
    *(undefined8 *)(param_4 + 0x18) = 0;
    break;
  case 6:
    *(undefined8 *)(param_4 + 0x18) = 0;
    *(undefined4 *)(param_4 + 8) = 4;
    uVar1 = param_3[4];
    uVar15 = (ulong)uVar1;
    if (*(long *)PTR__ZN4Aska10JsonParser16s_pMemoryManagerE_02cc46b0 == 0) {
      plVar7 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x38,PTR__ZSt7nothrow_02cb9a80);
      puVar3 = PTR__ZTVN4Aska6TArrayINS_10JsonParser6JValueELb0EEE_02cb8c08;
    }
    else {
      plVar7 = (long *)Aska::MemoryManager::Malloc(unsigned long)(*(long *)PTR__ZN4Aska10JsonParser16s_pMemoryManagerE_02cc46b0
                                       ,0x38);
      puVar3 = PTR__ZTVN4Aska6TArrayINS_10JsonParser6JValueELb0EEE_02cb8c08;
    }
    PTR__ZTVN4Aska6TArrayINS_10JsonParser6JValueELb0EEE_02cb8c08 = puVar3;
    if (plVar7 != (long *)0x0) {
      plVar7[4] = 0;
      plVar7[3] = 0;
      plVar7[2] = 0;
      plVar7[1] = 0;
      plVar7[5] = 8;
      *plVar7 = (long)(puVar3 + 0x10);
      *(undefined4 *)(plVar7 + 6) = 0;
    }
    *(long **)(param_4 + 0x10) = plVar7;
    if (uVar1 != 0) {
      if (plVar7 == (long *)0x0) goto code_r0x0200f568;
      lVar14 = plVar7[2];
      if (lVar14 < (long)uVar15) {
        uVar10 = plVar7[3];
        uVar12 = plVar7[5];
        if (plVar7[5] <= (long)uVar15) {
          uVar12 = uVar15;
        }
code_r0x0200f2ec:
        Aska::TArray<Aska::JsonParser::JValue, false>::ForceRealloc(long, long, Aska::JsonParser::JValue const*, StBoolean<false>)(plVar7,uVar10,uVar12,0);
      }
      else if ((((long)uVar15 < lVar14) && (uVar10 = plVar7[3], (long)uVar10 < lVar14)) &&
              ((uVar13 = plVar7[5], uVar12 = uVar10, (long)uVar13 <= (long)uVar10 ||
               (uVar12 = uVar13, (long)uVar13 < lVar14)))) goto code_r0x0200f2ec;
      Aska::TArray<Aska::JsonParser::JValue, false>::Resize(long, bool)(plVar7,uVar15,0);
      lVar14 = 0;
      uVar10 = 0;
      do {
        _ZN4Aska4ASON13AValue2JValueEPKNS0_6AValueEPNS_10JsonParser6JValueE
                  (param_1,param_2,*(long *)(param_3 + 2) + lVar14,
                   *(long *)(*(long *)(param_4 + 0x10) + 8) + lVar14);
        if (*param_1 < 0) {
          return;
        }
        uVar10 = uVar10 + 1;
        lVar14 = lVar14 + 0x20;
      } while (uVar10 < uVar15);
      break;
    }
    goto joined_r0x0200f4a8;
  case 7:
    *(undefined8 *)(param_4 + 0x18) = 0;
    *(undefined4 *)(param_4 + 8) = 5;
    puVar3 = PTR__ZN4Aska10JsonParser16s_pMemoryManagerE_02cc46b0;
    uVar1 = param_3[4];
    if (*(long *)PTR__ZN4Aska10JsonParser16s_pMemoryManagerE_02cc46b0 == 0) {
      plVar7 = (long *)operator new(unsigned long, std::nothrow_t const&)(0xa8,PTR__ZSt7nothrow_02cb9a80);
    }
    else {
      plVar7 = (long *)Aska::MemoryManager::Malloc(unsigned long)(*(long *)PTR__ZN4Aska10JsonParser16s_pMemoryManagerE_02cc46b0
                                       ,0xa8);
    }
    if (plVar7 != (long *)0x0) {
      memset(plVar7,0,0xa1);
    }
    *(long **)(param_4 + 0x10) = plVar7;
    puVar4 = PTR__ZTVN4Aska10JsonParser6JValueE_02cbbfd0;
    if (uVar1 != 0) {
      if (plVar7 == (long *)0x0) goto code_r0x0200f568;
      lVar14 = 0;
      uVar15 = 0;
      do {
        lVar16 = *(long *)(param_3 + 2);
        Aska::ASON::AValue2String(Aska::ASON::AValue const*, char**)(&lStack_68,param_2,lVar14 + lVar16,&lStack_70);
        if (lStack_68 < 0) goto code_r0x0200f504;
        if (*(long *)puVar3 == 0) {
          puVar8 = (undefined8 *)operator new(unsigned long, std::nothrow_t const&)(0x20,PTR__ZSt7nothrow_02cb9a80);
          if (puVar8 != (undefined8 *)0x0) {
            *(undefined4 *)(puVar8 + 1) = 0;
            puVar2 = puVar4;
            goto code_r0x0200f3d0;
          }
        }
        else {
          puVar8 = (undefined8 *)Aska::MemoryManager::Malloc(unsigned long)(*(long *)puVar3,0x20);
          puVar2 = PTR__ZTVN4Aska10JsonParser6JValueE_02cbbfd0;
          if (puVar8 != (undefined8 *)0x0) {
            *(undefined4 *)(puVar8 + 1) = 0;
code_r0x0200f3d0:
            *puVar8 = puVar2 + 0x10;
            puVar8[2] = 0;
            puVar8[3] = 0;
          }
        }
        lVar5 = lStack_70;
        lStack_68 = lStack_70;
        puVar9 = (undefined8 *)Aska::Collection::TDictionary<char*, Aska::JsonParser::JValue*, false>::operator[](char* const&)(*(undefined8 *)(param_4 + 0x10),&lStack_68);
        *puVar9 = puVar8;
        lStack_68 = lVar5;
        puVar8 = (undefined8 *)Aska::Collection::TDictionary<char*, Aska::JsonParser::JValue*, false>::operator[](char* const&)(*(undefined8 *)(param_4 + 0x10),&lStack_68);
        uVar11 = *puVar8;
        if (lVar5 != 0) {
          operator delete[](void*)(lVar5);
        }
        _ZN4Aska4ASON13AValue2JValueEPKNS0_6AValueEPNS_10JsonParser6JValueE
                  (&lStack_68,param_2,lVar14 + lVar16 + 0x20,uVar11);
        if (lStack_68 < 0) {
code_r0x0200f504:
          *param_1 = lStack_68;
          return;
        }
        uVar15 = uVar15 + 1;
        lVar14 = lVar14 + 0x40;
      } while (uVar15 < uVar1);
      break;
    }
joined_r0x0200f4a8:
    if (plVar7 == (long *)0x0) {
code_r0x0200f568:
      *(undefined8 *)(param_2 + 0x80) = 0xfffffffffffffc41;
      *param_1 = -0x3bf;
      return;
    }
  }
  *param_1 = 0;
  return;
}

// ==== Aska::ASON::DeserializeText(void const*, unsigned long)
// vaddr 0x1f0f668 | ghidra 0x200f668 | size 684 | symbol _ZN4Aska4ASON15DeserializeTextEPKvm | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

long _ZN4Aska4ASON15DeserializeTextEPKvm(long param_1,long param_2,long param_3)

{
  undefined8 uVar1;
  undefined *puVar2;
  long *plVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  long lVar6;
  ulong uVar7;
  long lVar8;
  undefined8 *puVar9;
  long lVar10;
  undefined *puStack_a8;
  int iStack_a0;
  long *plStack_98;
  long lStack_90;
  undefined1 auStack_88 [72];
  long lStack_38;
  
  if (*(char *)(param_1 + 0x8a) == '\0') {
    uVar5 = 0xfffffffffffffc44;
code_r0x0200f7c4:
    *(undefined8 *)(param_1 + 0x80) = uVar5;
    return 0;
  }
  if ((param_2 == 0) || (param_3 == 0)) {
    uVar5 = 0xfffffffffffffc43;
    goto code_r0x0200f7c4;
  }
  lVar6 = *(long *)(param_1 + 0x28);
  lVar10 = *(long *)(param_1 + 0x30);
  *(undefined8 *)(param_1 + 0x80) = 0;
  *(undefined4 *)(param_1 + 0x60) = 0;
  *(undefined8 *)(param_1 + 0x68) = 0;
  uVar7 = lVar10 - lVar6 >> 5;
  *(undefined1 *)(param_1 + 0x89) = 0;
  if (1 < uVar7) {
    lVar8 = uVar7 - 1;
    do {
      if (*(char *)(lVar10 + -8) != '\0') {
        if (*(long *)(lVar10 + -0x20) != 0) {
          operator delete[](void*)();
        }
        *(undefined1 *)(lVar10 + -8) = 0;
      }
      *(undefined8 *)(lVar10 + -0x18) = 0;
      *(undefined8 *)(lVar10 + -0x10) = 0;
      *(long *)(lVar10 + -0x20) = 0;
      lVar6 = *(long *)(param_1 + 0x28);
      lVar10 = lVar6;
      if (lVar6 != *(long *)(param_1 + 0x30)) {
        lVar10 = *(long *)(param_1 + 0x30) + -0x20;
        *(long *)(param_1 + 0x30) = lVar10;
      }
      lVar8 = lVar8 + -1;
    } while (lVar8 != 0);
  }
  *(undefined8 *)(lVar6 + 0x10) = 0;
  *(long *)(param_1 + 0x48) = lVar6;
  uVar5 = *(undefined8 *)(lVar6 + 8);
  *(undefined2 *)(param_1 + 0x58) = 0;
  *(undefined8 *)(param_1 + 0x50) = uVar5;
  puVar9 = (undefined8 *)(param_1 + 8);
  *puVar9 = 0;
  *(undefined8 *)(param_1 + 0x10) = 0;
  *(undefined8 *)(param_1 + 0x18) = 0;
  uVar4 = Aska::ASON::Malloc(unsigned long)(param_1,0x200);
  uVar1 = _UNK_0296e148;
  uVar5 = _UNK_0296e140;
  *puVar9 = uVar4;
  *(undefined8 *)(param_1 + 0x18) = uVar1;
  *(undefined8 *)(param_1 + 0x10) = uVar5;
  Aska::JsonParser::JsonParser()(auStack_88);
  puVar2 = PTR__ZTVN4Aska10JsonParser6JValueE_02cbbfd0;
  iStack_a0 = 0;
  puStack_a8 = PTR__ZTVN4Aska10JsonParser6JValueE_02cbbfd0 + 0x10;
  plStack_98 = (long *)0x0;
  lStack_90 = 0;
  uVar7 = Aska::JsonParser::Initialize(bool, Aska::MemoryManager*)(0,0);
  if (((uVar7 & 1) == 0) ||
     (uVar7 = Aska::JsonParser::Deserialize(char const*, unsigned long, Aska::JsonParser::JValue*, bool, unsigned char*, unsigned long)(auStack_88,param_2,param_3,&puStack_a8,0,0,0), (uVar7 & 1) == 0)) {
    *(undefined8 *)(param_1 + 0x80) = 0xffffffffffffffff;
code_r0x0200f7d8:
    lVar6 = *(long *)(param_1 + 0x28);
    lVar10 = *(long *)(param_1 + 0x30);
    *(undefined4 *)(param_1 + 0x60) = 0;
    *(undefined8 *)(param_1 + 0x68) = 0;
    *(undefined1 *)(param_1 + 0x89) = 0;
    uVar7 = lVar10 - lVar6 >> 5;
    if (1 < uVar7) {
      lVar8 = uVar7 - 1;
      do {
        if (*(char *)(lVar10 + -8) != '\0') {
          if (*(long *)(lVar10 + -0x20) != 0) {
            operator delete[](void*)();
          }
          *(undefined1 *)(lVar10 + -8) = 0;
        }
        *(undefined8 *)(lVar10 + -0x18) = 0;
        *(undefined8 *)(lVar10 + -0x10) = 0;
        *(long *)(lVar10 + -0x20) = 0;
        lVar6 = *(long *)(param_1 + 0x28);
        lVar10 = lVar6;
        if (lVar6 != *(long *)(param_1 + 0x30)) {
          lVar10 = *(long *)(param_1 + 0x30) + -0x20;
          *(long *)(param_1 + 0x30) = lVar10;
        }
        lVar8 = lVar8 + -1;
      } while (lVar8 != 0);
    }
    *(undefined8 *)(lVar6 + 0x10) = 0;
    *(long *)(param_1 + 0x48) = lVar6;
    uVar4 = *(undefined8 *)(lVar6 + 8);
    *(undefined2 *)(param_1 + 0x58) = 0;
    *(undefined8 *)(param_1 + 0x50) = uVar4;
    *(undefined8 *)(param_1 + 0x10) = 0;
    *(undefined8 *)(param_1 + 0x18) = 0;
    *puVar9 = 0;
    uVar4 = Aska::ASON::Malloc(unsigned long)(param_1,0x200);
    *(undefined8 *)(param_1 + 8) = uVar4;
    param_3 = 0;
    *(undefined8 *)(param_1 + 0x18) = uVar1;
    *(undefined8 *)(param_1 + 0x10) = uVar5;
  }
  else {
    Aska::ASON::JValue2AValue(Aska::JsonParser::JValue const*, Aska::ASON::AValue*)(&lStack_38,param_1,&puStack_a8,param_1 + 0x60);
    if (lStack_38 < 0) goto code_r0x0200f7d8;
  }
  plVar3 = plStack_98;
  puStack_a8 = puVar2 + 0x10;
  if (iStack_a0 == 3) {
    if (plStack_98 == (long *)0x0) goto code_r0x0200f8e0;
    operator delete[](void*)();
  }
  else if (iStack_a0 == 5) {
    if (plStack_98 == (long *)0x0) goto code_r0x0200f8e0;
    Aska::JsonParser::JValue::JObject::~JObject()(plStack_98);
    operator delete(void*)(plVar3);
  }
  else {
    if ((iStack_a0 != 4) || (plStack_98 == (long *)0x0)) goto code_r0x0200f8e0;
    (**(code **)(*plStack_98 + 8))();
  }
  plStack_98 = (long *)0x0;
code_r0x0200f8e0:
  if (lStack_90 != 0) {
    operator delete[](void*)();
    lStack_90 = 0;
  }
  Aska::JsonParser::~JsonParser()(auStack_88);
  return param_3;
}

// ==== Aska::ASON::JValue2AValue(Aska::JsonParser::JValue const*, Aska::ASON::AValue*)
// vaddr 0x1f0f914 | ghidra 0x200f914 | size 1260 | symbol _ZN4Aska4ASON13JValue2AValueEPKNS_10JsonParser6JValueEPNS0_6AValueE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska4ASON13JValue2AValueEPKNS_10JsonParser6JValueEPNS0_6AValueE
               (long *param_1,long param_2,long param_3,undefined4 *param_4)

{
  bool bVar1;
  uint uVar2;
  long lVar3;
  long lVar4;
  undefined8 *puVar5;
  long lVar6;
  long *plVar7;
  long lVar8;
  long lVar9;
  long lVar10;
  long *plVar11;
  long lStack_68;
  
  switch(*(undefined4 *)(param_3 + 8)) {
  case 0:
    *param_4 = 0;
    *(undefined8 *)(param_4 + 6) = 0;
    goto code_r0x0200fb60;
  case 1:
    *param_4 = 1;
    *(undefined1 *)(param_4 + 2) = *(undefined1 *)(param_3 + 0x10);
    break;
  case 2:
    *param_4 = 4;
    *(undefined8 *)(param_4 + 2) = *(undefined8 *)(param_3 + 0x10);
    break;
  case 3:
    *param_4 = 5;
    if ((*(long *)(param_3 + 0x18) != 0) && (lVar3 = strlen(), lVar3 != 0)) {
      lVar6 = Aska::ASON::Malloc(unsigned long)(param_2,lVar3);
      if (lVar6 == 0) {
code_r0x0200fdf0:
        lStack_68 = -0x3bf;
        *(undefined8 *)(param_2 + 0x80) = 0xfffffffffffffc41;
code_r0x0200fdf8:
        *param_1 = lStack_68;
        return;
      }
      memcpy(lVar6,*(undefined8 *)(param_3 + 0x18),lVar3);
      param_4[6] = (int)lVar3;
      *(long *)(param_4 + 2) = lVar6;
      if ((int)lVar3 == 0) {
        *(undefined8 *)(param_4 + 4) = 0;
      }
      else if (*(char *)(param_2 + 0x88) == '\0') {
        *(undefined8 *)(param_4 + 4) = 0;
      }
      else {
        lVar4 = Aska::ASON::Malloc(unsigned long)(param_2,lVar3 + 1);
        if (lVar4 == 0) goto code_r0x0200fdf0;
        memcpy(lVar4,lVar6,lVar3 + 1);
        *(undefined1 *)(lVar4 + lVar3) = 0;
        *(long *)(param_4 + 4) = lVar4;
      }
      break;
    }
    param_4[6] = 0;
code_r0x0200fb60:
    *(undefined8 *)(param_4 + 2) = 0;
    *(undefined8 *)(param_4 + 4) = 0;
    break;
  case 4:
    *param_4 = 6;
    lVar3 = *(long *)(*(long *)(param_3 + 0x10) + 0x18);
    if (0 < lVar3) {
      lVar6 = Aska::ASON::Malloc(unsigned long)(param_2,lVar3 << 5);
      if (lVar6 == 0) goto code_r0x0200fdf0;
      puVar5 = (undefined8 *)(lVar6 + 8);
      lVar4 = lVar3;
      do {
        *(undefined4 *)(puVar5 + -1) = 0;
        puVar5[1] = 0;
        puVar5[2] = 0;
        *puVar5 = 0;
        lVar4 = lVar4 + -1;
        puVar5 = puVar5 + 4;
      } while (lVar4 != 0);
      *(long *)(param_4 + 2) = lVar6;
      param_4[4] = (int)lVar3;
      _ZN4Aska4ASON13JValue2AValueEPKNS_10JsonParser6JValueEPNS0_6AValueE
                (param_1,param_2,*(undefined8 *)(*(long *)(param_3 + 0x10) + 8),lVar6);
      if (*param_1 < 0) {
        return;
      }
      lVar6 = 0;
      lVar4 = 0x20;
      while (lVar6 = lVar6 + 1, lVar6 < lVar3) {
        _ZN4Aska4ASON13JValue2AValueEPKNS_10JsonParser6JValueEPNS0_6AValueE
                  (param_1,param_2,*(long *)(*(long *)(param_3 + 0x10) + 8) + lVar4,
                   *(long *)(param_4 + 2) + lVar4);
        lVar4 = lVar4 + 0x20;
        if (*param_1 < 0) {
          return;
        }
      }
      break;
    }
    goto code_r0x0200fb50;
  case 5:
    *param_4 = 7;
    uVar2 = Aska::Collection::TDictionary<char*, Aska::JsonParser::JValue*, false>::CalcCount() const(*(undefined8 *)(param_3 + 0x10));
    if (0 < (int)uVar2) {
      lVar3 = Aska::ASON::Malloc(unsigned long)(param_2,-(ulong)(uVar2 >> 0x1f) & 0xffffffc000000000 |
                                      (ulong)uVar2 << 6);
      if (lVar3 == 0) goto code_r0x0200fdf0;
      lVar6 = (long)(int)uVar2;
      puVar5 = (undefined8 *)(lVar3 + 0x28);
      do {
        *(undefined4 *)(puVar5 + -5) = 0;
        puVar5[1] = 0;
        puVar5[2] = 0;
        *puVar5 = 0;
        puVar5[-3] = 0;
        puVar5[-2] = 0;
        *(undefined4 *)(puVar5 + -1) = 0;
        puVar5[-4] = 0;
        lVar6 = lVar6 + -1;
        puVar5 = puVar5 + 8;
      } while (lVar6 != 0);
      *(long *)(param_4 + 2) = lVar3;
      param_4[4] = uVar2;
      plVar7 = *(long **)(param_3 + 0x10);
      lVar3 = *plVar7;
      *(undefined1 *)(plVar7 + 0x14) = 0;
      plVar7[0x12] = 0;
      plVar7[0x13] = 0;
      if (lVar3 == 0) {
        lVar3 = plVar7[1];
        if (lVar3 != 0) {
          lVar6 = 1;
          goto code_r0x0200fc98;
        }
        lVar3 = plVar7[2];
        if (lVar3 != 0) {
          lVar6 = 2;
          goto code_r0x0200fc98;
        }
        lVar3 = plVar7[3];
        if (lVar3 != 0) {
          lVar6 = 3;
          goto code_r0x0200fc98;
        }
        lVar3 = plVar7[4];
        if (lVar3 != 0) {
          lVar6 = 4;
          goto code_r0x0200fc98;
        }
        lVar3 = plVar7[5];
        if (lVar3 != 0) {
          lVar6 = 5;
          goto code_r0x0200fc98;
        }
        lVar3 = plVar7[6];
        if (lVar3 != 0) {
          lVar6 = 6;
          goto code_r0x0200fc98;
        }
        lVar3 = plVar7[7];
        if (lVar3 != 0) {
          lVar6 = 7;
          goto code_r0x0200fc98;
        }
        lVar3 = plVar7[8];
        if (lVar3 != 0) {
          lVar6 = 8;
          goto code_r0x0200fc98;
        }
        lVar3 = plVar7[9];
        if (lVar3 != 0) {
          lVar6 = 9;
          goto code_r0x0200fc98;
        }
        lVar3 = plVar7[10];
        if (lVar3 != 0) {
          lVar6 = 10;
          goto code_r0x0200fc98;
        }
        lVar3 = plVar7[0xb];
        if (lVar3 != 0) {
          lVar6 = 0xb;
          goto code_r0x0200fc98;
        }
        lVar3 = plVar7[0xc];
        if (lVar3 != 0) {
          lVar6 = 0xc;
          goto code_r0x0200fc98;
        }
        lVar3 = plVar7[0xd];
        if (lVar3 != 0) {
          lVar6 = 0xd;
          goto code_r0x0200fc98;
        }
        lVar3 = plVar7[0xe];
        if (lVar3 != 0) {
          lVar6 = 0xe;
          goto code_r0x0200fc98;
        }
        lVar3 = plVar7[0xf];
        if (lVar3 != 0) {
          lVar6 = 0xf;
          goto code_r0x0200fc98;
        }
        lVar3 = plVar7[0x10];
        if (lVar3 != 0) {
          lVar6 = 0x10;
          goto code_r0x0200fc98;
        }
      }
      else {
        lVar6 = 0;
code_r0x0200fc98:
        plVar7[0x12] = lVar6;
        plVar7[0x13] = lVar3;
      }
      if (*(char *)(*(long *)(param_3 + 0x10) + 0xa0) == '\0') {
        plVar7 = *(long **)(*(long *)(param_3 + 0x10) + 0x98);
        lVar3 = 0;
        do {
          lVar8 = *plVar7;
          lVar9 = *(long *)(param_4 + 2);
          lVar10 = lVar3 * 0x40;
          *(undefined4 *)(lVar9 + lVar10) = 5;
          lVar6 = strlen(lVar8);
          lVar4 = Aska::ASON::Malloc(unsigned long)(param_2,lVar6);
          if (lVar4 == 0) goto code_r0x0200fdf0;
          memcpy(lVar4,lVar8,lVar6);
          lVar8 = lVar9 + lVar3 * 0x40;
          *(long *)(lVar8 + 8) = lVar4;
          *(int *)(lVar8 + 0x18) = (int)lVar6;
          if (((int)lVar6 == 0) || (*(char *)(param_2 + 0x88) == '\0')) {
            lVar8 = 0;
          }
          else {
            lVar8 = Aska::ASON::Malloc(unsigned long)(param_2,lVar6 + 1);
            if (lVar8 == 0) goto code_r0x0200fdf0;
            memcpy(lVar8,lVar4,lVar6);
            *(undefined1 *)(lVar8 + lVar6) = 0;
          }
          *(long *)(lVar9 + lVar10 + 0x10) = lVar8;
          lStack_68 = *plVar7;
          puVar5 = (undefined8 *)Aska::Collection::TDictionary<char*, Aska::JsonParser::JValue*, false>::operator[](char* const&)(*(undefined8 *)(param_3 + 0x10),&lStack_68);
          _ZN4Aska4ASON13JValue2AValueEPKNS_10JsonParser6JValueEPNS0_6AValueE
                    (&lStack_68,param_2,*puVar5,*(long *)(param_4 + 2) + lVar10 + 0x20);
          if (lStack_68 < 0) goto code_r0x0200fdf8;
          lVar6 = *(long *)(param_3 + 0x10);
          lVar3 = lVar3 + 1;
          plVar11 = *(long **)(lVar6 + 0x98);
          plVar7 = plVar11;
          if (plVar11 != (long *)0x0) {
            plVar7 = (long *)plVar11[2];
            if (plVar7 == (long *)0x0) {
              lVar8 = *(long *)(lVar6 + 0x90);
              lVar4 = lVar8 + 1;
              *(long *)(lVar6 + 0x90) = lVar4;
              if (lVar4 < 0x11) {
                do {
                  plVar7 = *(long **)(lVar6 + lVar4 * 8);
                  if (plVar7 != (long *)0x0) {
                    *(long *)(lVar6 + 0x90) = lVar4;
                    *(long **)(lVar6 + 0x98) = plVar7;
                    goto code_r0x0200fde0;
                  }
                  bVar1 = lVar4 < 0x10;
                  lVar4 = lVar4 + 1;
                } while (bVar1);
              }
              *(undefined1 *)(lVar6 + 0xa0) = 1;
              *(long *)(lVar6 + 0x90) = lVar8;
              plVar7 = plVar11;
            }
            else {
              *(long **)(lVar6 + 0x98) = plVar7;
            }
          }
code_r0x0200fde0:
        } while (*(char *)(*(long *)(param_3 + 0x10) + 0xa0) == '\0');
      }
      break;
    }
code_r0x0200fb50:
    *(undefined8 *)(param_4 + 2) = 0;
    param_4[4] = 0;
  }
  *param_1 = 0;
  return;
}

// ==== Aska::ASON::CalcSerializedBinarySize(Aska::ASON::AValue const*) const
// vaddr 0x1f0fe00 | ghidra 0x200fe00 | size 220 | symbol _ZNK4Aska4ASON24CalcSerializedBinarySizeEPKNS0_6AValueE | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska4ASON24CalcSerializedBinarySizeEPKNS0_6AValueE(long param_1,long param_2)

{
  uint uVar1;
  undefined8 uVar2;
  long lVar3;
  ulong uVar4;
  long lStack_40;
  undefined8 uStack_38;
  
  if (*(char *)(param_1 + 0x8a) == '\0') {
    uVar2 = 0xfffffffffffffc44;
  }
  else {
    if (param_2 != 0) {
      *(undefined8 *)(param_1 + 0x80) = 0;
      uStack_38 = 0;
      if (*(char *)(param_1 + 0x89) == '\0') {
        Aska::Status Aska::ASON::PackMessagePack<false>(Aska::ASON::AValue const*, unsigned char*, unsigned long, unsigned long*) const(&lStack_40,param_1,param_2,0,0,&uStack_38);
        if (-1 < lStack_40) {
          return uStack_38;
        }
      }
      else {
        uVar1 = *(uint *)(param_2 + 0x10);
        if (uVar1 == 0) {
          return 0;
        }
        lVar3 = 0;
        uVar4 = 0;
        while (Aska::Status Aska::ASON::PackMessagePack<false>(Aska::ASON::AValue const*, unsigned char*, unsigned long, unsigned long*) const(&lStack_40,param_1,*(long *)(param_2 + 8) + lVar3,0,0,&uStack_38),
              -1 < lStack_40) {
          uVar4 = uVar4 + 1;
          lVar3 = lVar3 + 0x20;
          if (uVar1 <= uVar4) {
            return uStack_38;
          }
        }
      }
      return 0;
    }
    uVar2 = 0xfffffffffffffc43;
  }
  *(undefined8 *)(param_1 + 0x80) = uVar2;
  return 0;
}

// ==== Aska::Status Aska::ASON::PackMessagePack<false>(Aska::ASON::AValue const*, unsigned char*, unsigned long, unsigned long*) const
// vaddr 0x1f0fedc | ghidra 0x200fedc | size 924 | symbol _ZNK4Aska4ASON15PackMessagePackILb0EEENS_6StatusEPKNS0_6AValueEPhmPm | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK4Aska4ASON15PackMessagePackILb0EEENS_6StatusEPKNS0_6AValueEPhmPm
               (ulong *param_1,undefined8 param_2,undefined4 *param_3,undefined8 param_4,
               undefined8 param_5,long *param_6)

{
  uint uVar1;
  bool bVar2;
  long lVar3;
  ulong uVar4;
  long lVar5;
  long lVar6;
  long lVar7;
  long lVar8;
  ulong uVar9;
  ulong uStack_68;
  
  switch(*param_3) {
  case 0:
  case 1:
    lVar5 = *param_6 + 1;
    break;
  case 2:
    uVar4 = *(ulong *)(param_3 + 2);
    if (uVar4 < 0x100) {
      lVar5 = 1;
      if (0x7f < uVar4) {
        lVar5 = 2;
      }
    }
    else if (uVar4 < 0x10000) {
      lVar5 = 3;
    }
    else {
      lVar5 = 5;
      if (uVar4 >> 0x20 != 0) {
        lVar5 = 9;
      }
    }
    goto code_r0x02010230;
  case 3:
    lVar6 = *(long *)(param_3 + 2);
    if (lVar6 < -0x20) {
      if (lVar6 < -0x8000) {
        lVar8 = 5;
        bVar2 = SBORROW8(lVar6,-0x80000000);
        lVar6 = lVar6 + 0x80000000;
        lVar5 = 9;
code_r0x0201022c:
        if (lVar6 < 0 == bVar2) {
          lVar5 = lVar8;
        }
      }
      else {
        lVar5 = 2;
        if (lVar6 < -0x80) {
          lVar5 = 3;
        }
      }
    }
    else if (lVar6 < 0x80) {
      lVar5 = 1;
    }
    else {
      if (0xffff < lVar6) {
        lVar8 = 9;
        bVar2 = SBORROW8(lVar6,0x100000000);
        lVar6 = lVar6 + -0x100000000;
        lVar5 = 5;
        goto code_r0x0201022c;
      }
      lVar5 = 2;
      if (0xff < lVar6) {
        lVar5 = 3;
      }
    }
code_r0x02010230:
    lVar5 = *param_6 + lVar5;
    break;
  case 4:
    lVar5 = *param_6 + 9;
    break;
  case 5:
    uVar1 = param_3[6];
    if (uVar1 < 0x20) {
      lVar5 = 1;
    }
    else if (uVar1 < 0x100) {
      lVar5 = 2;
    }
    else {
      lVar5 = 3;
      if (0xffff < uVar1) {
        lVar5 = 5;
      }
    }
    lVar5 = *param_6 + lVar5;
    *param_6 = lVar5;
    uVar4 = (ulong)(uint)param_3[6];
    if (param_3[6] == 0) goto code_r0x02010240;
    goto code_r0x020101f8;
  case 6:
    uVar1 = param_3[4];
    lVar6 = *param_6;
    lVar5 = 3;
    if (0xffff < uVar1) {
      lVar5 = 5;
    }
    if (uVar1 < 0x10) {
      lVar5 = 1;
    }
    *param_6 = lVar5 + lVar6;
    if (uVar1 != 0) {
      lVar8 = 0;
      uVar9 = 0;
      lVar6 = lVar5 + lVar6;
      do {
        Aska::Status Aska::ASON::PackMessagePack<false>(Aska::ASON::AValue const*, unsigned char*, unsigned long, unsigned long*) const(&uStack_68,param_2,*(long *)(param_3 + 2) + lVar8,lVar5,param_5,param_6);
        uVar4 = uStack_68;
        if ((long)uStack_68 < 0) break;
        uVar9 = uVar9 + 1;
        uVar4 = 0;
        lVar5 = lVar5 + (*param_6 - lVar6);
        lVar8 = lVar8 + 0x20;
        lVar6 = *param_6;
      } while (uVar9 < uVar1);
      goto code_r0x02010240;
    }
  default:
code_r0x020100f0:
    uVar4 = 0;
    goto code_r0x02010240;
  case 7:
    uVar1 = param_3[4];
    lVar5 = 3;
    if (0xffff < uVar1) {
      lVar5 = 5;
    }
    if (uVar1 < 0x10) {
      lVar5 = 1;
    }
    lVar6 = lVar5 + *param_6;
    *param_6 = lVar6;
    if (uVar1 != 0) {
      lVar8 = 0;
      uVar9 = 0;
      do {
        lVar3 = *(long *)(param_3 + 2);
        Aska::Status Aska::ASON::PackMessagePack<false>(Aska::ASON::AValue const*, unsigned char*, unsigned long, unsigned long*) const(&uStack_68,param_2,lVar8 + lVar3,lVar5,param_5,param_6);
        uVar4 = uStack_68;
        if ((long)uStack_68 < 0) break;
        lVar7 = *param_6;
        lVar5 = lVar5 + (lVar7 - lVar6);
        Aska::Status Aska::ASON::PackMessagePack<false>(Aska::ASON::AValue const*, unsigned char*, unsigned long, unsigned long*) const(&uStack_68,param_2,lVar8 + lVar3 + 0x20,lVar5,param_5,param_6);
        uVar4 = uStack_68;
        if ((long)uStack_68 < 0) break;
        lVar6 = *param_6;
        uVar9 = uVar9 + 1;
        uVar4 = 0;
        lVar8 = lVar8 + 0x40;
        lVar5 = lVar5 + (lVar6 - lVar7);
      } while (uVar9 < uVar1);
      goto code_r0x02010240;
    }
    goto code_r0x020100f0;
  case 8:
    lVar6 = 3;
    if (0xffff < (uint)param_3[4]) {
      lVar6 = 5;
    }
    lVar5 = 2;
    if (0xff < (uint)param_3[4]) {
      lVar5 = lVar6;
    }
    lVar5 = lVar5 + *param_6;
    goto code_r0x02010154;
  case 9:
    uVar1 = param_3[4];
    if ((uVar1 < 0x11) && ((1 << (ulong)(uVar1 & 0x1f) & 0x10116U) != 0)) {
      lVar5 = 2;
    }
    else if (uVar1 < 0x100) {
      lVar5 = 3;
    }
    else {
      lVar5 = 4;
      if (0xffff < uVar1) {
        lVar5 = 6;
      }
    }
    lVar5 = *param_6 + lVar5;
code_r0x02010154:
    *param_6 = lVar5;
    uVar4 = (ulong)(uint)param_3[4];
    if (param_3[4] == 0) {
      uVar4 = 0;
      goto code_r0x02010240;
    }
code_r0x020101f8:
    lVar5 = lVar5 + uVar4;
  }
  *param_6 = lVar5;
  uVar4 = 0;
code_r0x02010240:
  *param_1 = uVar4;
  return;
}

// ==== Aska::ASON::GetAValue(Aska::ASON::Key const*, long, Aska::ASON::AValue**) const
// vaddr 0x1f10278 | ghidra 0x2010278 | size 32 | symbol _ZNK4Aska4ASON9GetAValueEPKNS0_3KeyElPPNS0_6AValueE | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska4ASON9GetAValueEPKNS0_3KeyElPPNS0_6AValueE(long param_1)

{
  undefined8 uVar1;
  
  if (*(char *)(param_1 + 0x8a) != '\0') {
    uVar1 = (*(code *)PTR__ZN4Aska4ASON9GetAValueEPKNS0_6AValueEPKNS0_3KeyElPPS1__02c9eea0)
                      (param_1 + 0x60);
    return uVar1;
  }
  *(undefined8 *)(param_1 + 0x80) = 0xfffffffffffffc44;
  return 0;
}

// ==== Aska::ASON::GetAValue(Aska::ASON::AValue const*, Aska::ASON::Key const*, long, Aska::ASON::AValue**)
// vaddr 0x1f10298 | ghidra 0x2010298 | size 340 | symbol _ZN4Aska4ASON9GetAValueEPKNS0_6AValueEPKNS0_3KeyElPPS1_ | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska4ASON9GetAValueEPKNS0_6AValueEPKNS0_3KeyElPPS1_
          (int *param_1,int *param_2,long param_3,undefined8 *param_4)

{
  uint uVar1;
  byte bVar2;
  int iVar3;
  int *piVar4;
  int *piVar5;
  long lVar6;
  long lVar7;
  ulong uVar8;
  
  if ((((param_1 != (int *)0x0) && (param_2 != (int *)0x0)) && (param_3 != 0)) &&
     ((param_4 != (undefined8 *)0x0 && (iVar3 = *param_1, iVar3 == *param_2)))) {
    lVar7 = 0;
    piVar4 = param_2;
    do {
      if (iVar3 == 7) {
        uVar1 = param_1[4];
        if (uVar1 == 0) {
          return 0;
        }
        lVar6 = *(long *)(piVar4 + 2);
        if (lVar6 == 0) {
          return 0;
        }
        uVar8 = 0;
        piVar4 = (int *)(*(long *)(param_1 + 2) + 0x20);
        piVar5 = param_1;
        while( true ) {
          param_1 = piVar5;
          if (piVar4[-8] == 5) {
            if (*(long *)(piVar4 + -4) == 0) {
              bVar2 = 0;
            }
            else {
              iVar3 = strcmp(*(long *)(piVar4 + -4),lVar6);
              bVar2 = iVar3 == 0;
              param_1 = piVar4;
              if (!(bool)bVar2) {
                param_1 = piVar5;
              }
            }
          }
          else {
            bVar2 = 4;
          }
          if ((bVar2 | 4) != 4) break;
          uVar8 = uVar8 + 1;
          piVar4 = piVar4 + 0x10;
          piVar5 = param_1;
          if (uVar1 <= uVar8) {
            return 0;
          }
        }
      }
      else {
        if (iVar3 != 6) {
          return 0;
        }
        if (param_1[4] == 0) {
          return 0;
        }
        if ((uint)param_1[4] <= (uint)*(ulong *)(piVar4 + 2)) {
          return 0;
        }
        param_1 = (int *)(*(long *)(param_1 + 2) + (*(ulong *)(piVar4 + 2) & 0xffffffff) * 0x20);
      }
      if (param_1 == (int *)0x0) {
        return 0;
      }
      lVar7 = lVar7 + 1;
      if (param_3 <= lVar7) {
        *param_4 = param_1;
        return 1;
      }
      piVar4 = param_2 + lVar7 * 4;
      iVar3 = *param_1;
    } while (iVar3 == *piVar4);
  }
  return 0;
}

// ==== Aska::ASON::GetValue(Aska::ASON::Key const*, long, void*) const
// vaddr 0x1f103ec | ghidra 0x20103ec | size 172 | symbol _ZNK4Aska4ASON8GetValueEPKNS0_3KeyElPv | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZNK4Aska4ASON8GetValueEPKNS0_3KeyElPv
          (long param_1,undefined8 param_2,undefined8 param_3,undefined8 *param_4)

{
  ulong uVar1;
  undefined8 uVar2;
  undefined4 *puStack_18;
  
  if (*(char *)(param_1 + 0x8a) == '\0') {
    *(undefined8 *)(param_1 + 0x80) = 0xfffffffffffffc44;
    return 0;
  }
  puStack_18 = (undefined4 *)0x0;
  uVar1 = Aska::ASON::GetAValue(Aska::ASON::AValue const*, Aska::ASON::Key const*, long, Aska::ASON::AValue**)(param_1 + 0x60,param_2,param_3,&puStack_18);
  if ((uVar1 & 1) == 0) {
code_r0x02010464:
    uVar2 = 0;
  }
  else {
    switch(*puStack_18) {
    case 1:
      *(undefined1 *)param_4 = *(undefined1 *)(puStack_18 + 2);
      break;
    case 5:
      param_4[2] = *(undefined8 *)(puStack_18 + 6);
    case 9:
      uVar2 = *(undefined8 *)(puStack_18 + 2);
      param_4[1] = *(undefined8 *)(puStack_18 + 4);
      *param_4 = uVar2;
      break;
    case 6:
    case 7:
    case 8:
      *(undefined8 *)((long)param_4 + 6) = *(undefined8 *)((long)puStack_18 + 0xe);
    case 2:
    case 3:
    case 4:
      *param_4 = *(undefined8 *)(puStack_18 + 2);
      break;
    default:
      goto code_r0x02010464;
    }
    uVar2 = 1;
  }
  return uVar2;
}

// ==== Aska::ASON::GetValue(Aska::ASON::AValue const*, Aska::ASON::Key const*, long, void*)
// vaddr 0x1f10498 | ghidra 0x2010498 | size 140 | symbol _ZN4Aska4ASON8GetValueEPKNS0_6AValueEPKNS0_3KeyElPv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska4ASON8GetValueEPKNS0_6AValueEPKNS0_3KeyElPv(void)

{
  ulong uVar1;
  undefined8 uVar2;
  undefined8 *in_x3;
  
  uVar1 = Aska::ASON::GetAValue(Aska::ASON::AValue const*, Aska::ASON::Key const*, long, Aska::ASON::AValue**)();
  if ((uVar1 & 1) == 0) {
code_r0x020104f0:
    uVar2 = 0;
  }
  else {
    switch(uRam0000000000000000) {
    case 1:
      *(undefined1 *)in_x3 = uRam0000000000000008;
      break;
    case 5:
      in_x3[2] = uRam0000000000000018;
    case 9:
      uVar2 = CONCAT26(uRam000000000000000e,CONCAT51(uRam0000000000000009,uRam0000000000000008));
      in_x3[1] = CONCAT26(uRam0000000000000016,uRam0000000000000010);
      *in_x3 = uVar2;
      break;
    case 6:
    case 7:
    case 8:
      *(ulong *)((long)in_x3 + 6) = CONCAT62(uRam0000000000000010,uRam000000000000000e);
    case 2:
    case 3:
    case 4:
      *in_x3 = CONCAT26(uRam000000000000000e,CONCAT51(uRam0000000000000009,uRam0000000000000008));
      break;
    default:
      goto code_r0x020104f0;
    }
    uVar2 = 1;
  }
  return uVar2;
}

// ==== Aska::ASON::SetValue(Aska::ASON::Key const*, long, void const*)
// vaddr 0x1f10524 | ghidra 0x2010524 | size 32 | symbol _ZN4Aska4ASON8SetValueEPKNS0_3KeyElPKv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska4ASON8SetValueEPKNS0_3KeyElPKv(long param_1)

{
  undefined8 uVar1;
  
  if (*(char *)(param_1 + 0x8a) != '\0') {
    uVar1 = (*(code *)PTR__ZN4Aska4ASON8SetValueEPKNS0_6AValueEPKNS0_3KeyElPKv_02c97fc0)
                      (param_1 + 0x60);
    return uVar1;
  }
  *(undefined8 *)(param_1 + 0x80) = 0xfffffffffffffc44;
  return 0;
}

// ==== Aska::ASON::SetValue(Aska::ASON::AValue const*, Aska::ASON::Key const*, long, void const*)
// vaddr 0x1f10544 | ghidra 0x2010544 | size 256 | symbol _ZN4Aska4ASON8SetValueEPKNS0_6AValueEPKNS0_3KeyElPKv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska4ASON8SetValueEPKNS0_6AValueEPKNS0_3KeyElPKv(void)

{
  ulong uVar1;
  undefined8 *in_x3;
  undefined8 uVar2;
  
  uVar1 = Aska::ASON::GetAValue(Aska::ASON::AValue const*, Aska::ASON::Key const*, long, Aska::ASON::AValue**)();
  if ((uVar1 & 1) == 0) {
    return 0;
  }
  switch(uRam0000000000000000) {
  case 1:
    if (in_x3 == (undefined8 *)0x0) {
      return 0;
    }
    uRam0000000000000000 = 1;
    uRam0000000000000008 = *(undefined1 *)in_x3;
    return 1;
  case 2:
    if (in_x3 == (undefined8 *)0x0) {
      return 0;
    }
    uRam0000000000000000 = 2;
    goto code_r0x0201060c;
  case 3:
    if (in_x3 == (undefined8 *)0x0) {
      return 0;
    }
    uRam0000000000000000 = 3;
    goto code_r0x0201060c;
  case 4:
    if (in_x3 == (undefined8 *)0x0) {
      return 0;
    }
    uRam0000000000000000 = 4;
    goto code_r0x0201060c;
  case 5:
    if (in_x3 == (undefined8 *)0x0) {
      return 0;
    }
    uRam0000000000000000 = 5;
    uRam0000000000000018 = in_x3[2];
    goto code_r0x02010624;
  case 6:
    if (in_x3 == (undefined8 *)0x0) {
      return 0;
    }
    uRam0000000000000000 = 6;
    break;
  case 7:
    if (in_x3 == (undefined8 *)0x0) {
      return 0;
    }
    uRam0000000000000000 = 7;
    break;
  case 8:
    if (in_x3 == (undefined8 *)0x0) {
      return 0;
    }
    uRam0000000000000000 = 8;
    break;
  case 9:
    if (in_x3 == (undefined8 *)0x0) {
      return 0;
    }
    uRam0000000000000000 = 9;
code_r0x02010624:
    uVar2 = *in_x3;
    uRam0000000000000010 = (undefined6)in_x3[1];
    uRam0000000000000016 = (undefined2)((ulong)in_x3[1] >> 0x30);
    uRam0000000000000008 = (undefined1)uVar2;
    uRam0000000000000009 = (undefined5)((ulong)uVar2 >> 8);
    uRam000000000000000e = (undefined2)((ulong)uVar2 >> 0x30);
    return 1;
  default:
    return 0;
  }
  uRam0000000000000010 = (undefined6)((ulong)*(undefined8 *)((long)in_x3 + 6) >> 0x10);
code_r0x0201060c:
  uVar2 = *in_x3;
  uRam0000000000000008 = (undefined1)uVar2;
  uRam0000000000000009 = (undefined5)((ulong)uVar2 >> 8);
  uRam000000000000000e = (undefined2)((ulong)uVar2 >> 0x30);
  return 1;
}

// ==== Aska::ASON::AValue::Get(void*) const
// vaddr 0x1f10644 | ghidra 0x2010644 | size 108 | symbol _ZNK4Aska4ASON6AValue3GetEPv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska4ASON6AValue3GetEPv(undefined4 *param_1,undefined8 *param_2)

{
  undefined8 uVar1;
  
  switch(*param_1) {
  case 1:
    *(undefined1 *)param_2 = *(undefined1 *)(param_1 + 2);
    return 1;
  case 5:
    param_2[2] = *(undefined8 *)(param_1 + 6);
  case 9:
    uVar1 = *(undefined8 *)(param_1 + 2);
    param_2[1] = *(undefined8 *)(param_1 + 4);
    *param_2 = uVar1;
    return 1;
  case 6:
  case 7:
  case 8:
    *(undefined8 *)((long)param_2 + 6) = *(undefined8 *)((long)param_1 + 0xe);
  case 2:
  case 3:
  case 4:
    *param_2 = *(undefined8 *)(param_1 + 2);
    return 1;
  default:
    return 0;
  }
}

// ==== Aska::ASON::AValue::Set(void const*)
// vaddr 0x1f106b0 | ghidra 0x20106b0 | size 336 | symbol _ZN4Aska4ASON6AValue3SetEPKv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska4ASON6AValue3SetEPKv(undefined4 *param_1,undefined8 *param_2)

{
  undefined4 uVar1;
  undefined8 uVar2;
  
  switch(*param_1) {
  case 1:
    if (param_2 != (undefined8 *)0x0) {
      *param_1 = 1;
      *(undefined1 *)(param_1 + 2) = *(undefined1 *)param_2;
      return 1;
    }
    return 0;
  case 2:
    if (param_2 == (undefined8 *)0x0) {
      return 0;
    }
    uVar1 = 2;
    break;
  case 3:
    if (param_2 == (undefined8 *)0x0) {
      return 0;
    }
    uVar1 = 3;
    break;
  case 4:
    if (param_2 == (undefined8 *)0x0) {
      return 0;
    }
    uVar1 = 4;
    break;
  case 5:
    if (param_2 == (undefined8 *)0x0) {
      return 0;
    }
    *param_1 = 5;
    *(undefined8 *)(param_1 + 6) = param_2[2];
    goto code_r0x02010780;
  case 6:
    if (param_2 == (undefined8 *)0x0) {
      return 0;
    }
    uVar1 = 6;
    goto code_r0x0201075c;
  case 7:
    if (param_2 == (undefined8 *)0x0) {
      return 0;
    }
    uVar1 = 7;
    goto code_r0x0201075c;
  case 8:
    if (param_2 == (undefined8 *)0x0) {
      return 0;
    }
    uVar1 = 8;
code_r0x0201075c:
    *param_1 = uVar1;
    *(undefined8 *)((long)param_1 + 0xe) = *(undefined8 *)((long)param_2 + 6);
    goto code_r0x02010768;
  case 9:
    if (param_2 == (undefined8 *)0x0) {
      return 0;
    }
    *param_1 = 9;
code_r0x02010780:
    uVar2 = *param_2;
    *(undefined8 *)(param_1 + 4) = param_2[1];
    *(undefined8 *)(param_1 + 2) = uVar2;
    return 1;
  default:
    return 0;
  }
  *param_1 = uVar1;
code_r0x02010768:
  *(undefined8 *)(param_1 + 2) = *param_2;
  return 1;
}

// ==== Aska::ASON::SetRoot(Aska::ASON::AValue const*)
// vaddr 0x1f10800 | ghidra 0x2010800 | size 276 | symbol _ZN4Aska4ASON7SetRootEPKNS0_6AValueE | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska4ASON7SetRootEPKNS0_6AValueE(undefined8 *param_1,long param_2,long param_3)

{
  undefined8 uVar1;
  undefined8 uVar2;
  long lVar3;
  undefined8 uVar4;
  ulong uVar5;
  long lVar6;
  long lVar7;
  
  if (*(char *)(param_2 + 0x8a) == '\0') {
    uVar4 = 0xfffffffffffffc44;
  }
  else {
    if (param_3 != 0) {
      lVar3 = *(long *)(param_2 + 0x28);
      lVar7 = *(long *)(param_2 + 0x30);
      *(undefined4 *)(param_2 + 0x60) = 0;
      *(undefined8 *)(param_2 + 0x68) = 0;
      *(undefined1 *)(param_2 + 0x89) = 0;
      uVar5 = lVar7 - lVar3 >> 5;
      if (1 < uVar5) {
        lVar6 = uVar5 - 1;
        do {
          if (*(char *)(lVar7 + -8) != '\0') {
            if (*(long *)(lVar7 + -0x20) != 0) {
              operator delete[](void*)();
            }
            *(undefined1 *)(lVar7 + -8) = 0;
          }
          *(undefined8 *)(lVar7 + -0x18) = 0;
          *(undefined8 *)(lVar7 + -0x10) = 0;
          *(long *)(lVar7 + -0x20) = 0;
          lVar3 = *(long *)(param_2 + 0x28);
          lVar7 = lVar3;
          if (lVar3 != *(long *)(param_2 + 0x30)) {
            lVar7 = *(long *)(param_2 + 0x30) + -0x20;
            *(long *)(param_2 + 0x30) = lVar7;
          }
          lVar6 = lVar6 + -1;
        } while (lVar6 != 0);
      }
      *(undefined8 *)(lVar3 + 0x10) = 0;
      *(long *)(param_2 + 0x48) = lVar3;
      uVar4 = *(undefined8 *)(lVar3 + 8);
      *(undefined2 *)(param_2 + 0x58) = 0;
      *(undefined8 *)(param_2 + 0x10) = 0;
      *(undefined8 *)(param_2 + 0x18) = 0;
      *(undefined8 *)(param_2 + 0x50) = uVar4;
      *(undefined8 *)(param_2 + 8) = 0;
      uVar2 = Aska::ASON::Malloc(unsigned long)(param_2,0x200);
      uVar1 = _UNK_0296e148;
      uVar4 = _UNK_0296e140;
      *(undefined8 *)(param_2 + 8) = uVar2;
      *(undefined8 *)(param_2 + 0x18) = uVar1;
      *(undefined8 *)(param_2 + 0x10) = uVar4;
      (*(code *)PTR__ZN4Aska4ASON18SetAValueRecursiveEPNS0_6AValueEPKS1__02cb3bc8)
                (param_1,param_2,param_2 + 0x60,param_3);
      return;
    }
    uVar4 = 0xfffffffffffffc43;
  }
  *(undefined8 *)(param_2 + 0x80) = uVar4;
  *param_1 = uVar4;
  return;
}

// ==== Aska::ASON::SetAValueRecursive(Aska::ASON::AValue*, Aska::ASON::AValue const*)
// vaddr 0x1f10914 | ghidra 0x2010914 | size 800 | symbol _ZN4Aska4ASON18SetAValueRecursiveEPNS0_6AValueEPKS1_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska4ASON18SetAValueRecursiveEPNS0_6AValueEPKS1_
               (long *param_1,long param_2,undefined8 *param_3,undefined8 *param_4)

{
  long lVar1;
  long lVar2;
  uint uVar3;
  int iVar4;
  undefined1 uVar5;
  undefined8 *puVar6;
  long lVar7;
  ulong uVar8;
  long lVar9;
  ulong uVar10;
  long lVar11;
  undefined8 uVar12;
  long lStack_58;
  
  switch(*(undefined4 *)param_4) {
  case 0:
    *(undefined4 *)param_3 = 0;
    param_3[2] = 0;
    param_3[3] = 0;
    break;
  default:
    uVar12 = param_4[2];
    param_3[3] = param_4[3];
    param_3[2] = uVar12;
    uVar12 = *param_4;
    param_3[1] = param_4[1];
    *param_3 = uVar12;
    goto code_r0x02010bf8;
  case 5:
    (*(code *)PTR__ZN4Aska4ASON6AValue9SetStringEPKcjPS0__02c9f180)
              (param_1,param_3,param_4[1],*(undefined4 *)(param_4 + 3),param_2);
    return;
  case 6:
    if (param_3 == (undefined8 *)0x0) goto code_r0x02010be8;
    uVar3 = *(uint *)(param_4 + 2);
    uVar10 = (ulong)uVar3;
    *(undefined4 *)param_3 = 6;
    if (uVar3 != 0) {
      lVar7 = Aska::ASON::Malloc(unsigned long)(param_2,uVar10 << 5);
      if (lVar7 != 0) {
        puVar6 = (undefined8 *)(lVar7 + 8);
        uVar8 = uVar10;
        do {
          *(undefined4 *)(puVar6 + -1) = 0;
          puVar6[1] = 0;
          puVar6[2] = 0;
          *puVar6 = 0;
          uVar8 = uVar8 - 1;
          puVar6 = puVar6 + 4;
        } while (uVar8 != 0);
        param_3[1] = lVar7;
        *(uint *)(param_3 + 2) = uVar3;
        if (uVar3 != 0) {
          _ZN4Aska4ASON18SetAValueRecursiveEPNS0_6AValueEPKS1_(&lStack_58,param_2,lVar7,param_4[1]);
          if (-1 < lStack_58) {
            uVar8 = 0;
            lVar7 = 0x20;
            do {
              uVar8 = uVar8 + 1;
              if (uVar10 <= uVar8) goto code_r0x02010bf8;
              _ZN4Aska4ASON18SetAValueRecursiveEPNS0_6AValueEPKS1_
                        (&lStack_58,param_2,param_3[1] + lVar7,param_4[1] + lVar7);
              lVar7 = lVar7 + 0x20;
            } while (-1 < lStack_58);
          }
          *(long *)(param_2 + 0x80) = lStack_58;
          *param_1 = lStack_58;
          return;
        }
        goto code_r0x02010bf8;
      }
      goto code_r0x02010c0c;
    }
code_r0x02010bf0:
    *(undefined4 *)(param_3 + 2) = 0;
    break;
  case 7:
    if (param_3 != (undefined8 *)0x0) {
      uVar3 = *(uint *)(param_4 + 2);
      uVar10 = (ulong)uVar3;
      *(undefined4 *)param_3 = 7;
      if (uVar3 == 0) goto code_r0x02010bf0;
      lVar7 = Aska::ASON::Malloc(unsigned long)(param_2,uVar10 << 6);
      if (lVar7 != 0) {
        puVar6 = (undefined8 *)(lVar7 + 0x28);
        uVar8 = uVar10;
        do {
          *(undefined4 *)(puVar6 + -5) = 0;
          puVar6[1] = 0;
          puVar6[2] = 0;
          *puVar6 = 0;
          puVar6[-3] = 0;
          puVar6[-2] = 0;
          *(undefined4 *)(puVar6 + -1) = 0;
          puVar6[-4] = 0;
          uVar8 = uVar8 - 1;
          puVar6 = puVar6 + 8;
        } while (uVar8 != 0);
        param_3[1] = lVar7;
        *(uint *)(param_3 + 2) = uVar3;
        if (uVar3 == 0) goto code_r0x02010bf8;
        lVar9 = param_4[1];
        _ZN4Aska4ASON18SetAValueRecursiveEPNS0_6AValueEPKS1_(&lStack_58,param_2,lVar7,lVar9);
        if (-1 < lStack_58) {
          uVar8 = 0;
          lVar11 = 0x40;
          do {
            _ZN4Aska4ASON18SetAValueRecursiveEPNS0_6AValueEPKS1_
                      (&lStack_58,param_2,lVar7 + lVar11 + -0x20,lVar9 + lVar11 + -0x20);
            if (lStack_58 < 0) break;
            uVar8 = uVar8 + 1;
            if (uVar10 <= uVar8) goto code_r0x02010bf8;
            lVar7 = param_3[1];
            lVar9 = param_4[1];
            lVar1 = lVar7 + lVar11;
            lVar2 = lVar9 + lVar11;
            lVar11 = lVar11 + 0x40;
            _ZN4Aska4ASON18SetAValueRecursiveEPNS0_6AValueEPKS1_(&lStack_58,param_2,lVar1,lVar2);
          } while (-1 < lStack_58);
        }
        goto code_r0x02010c10;
      }
code_r0x02010c0c:
      lStack_58 = -0x3bf;
      goto code_r0x02010c10;
    }
code_r0x02010be8:
    lStack_58 = -0x3bd;
code_r0x02010c10:
    *(long *)(param_2 + 0x80) = lStack_58;
    *param_1 = lStack_58;
    return;
  case 8:
    lVar9 = param_4[1];
    lVar7 = -0x3bd;
    if ((lVar9 != 0) && (iVar4 = *(int *)(param_4 + 2), iVar4 != 0)) {
      *(undefined4 *)param_3 = 8;
      lVar7 = Aska::ASON::Malloc(unsigned long)(param_2,iVar4);
      param_3[1] = lVar7;
      if (lVar7 == 0) {
code_r0x02010c00:
        *param_1 = -0x3bf;
        return;
      }
      memcpy(lVar7,lVar9,iVar4);
      lVar7 = 0;
      *(int *)(param_3 + 2) = iVar4;
    }
    goto code_r0x02010be0;
  case 9:
    lVar9 = param_4[1];
    lVar7 = -0x3bd;
    if ((lVar9 != 0) && (iVar4 = *(int *)(param_4 + 2), iVar4 != 0)) {
      uVar5 = *(undefined1 *)((long)param_4 + 0x14);
      *(undefined4 *)param_3 = 9;
      lVar7 = Aska::ASON::Malloc(unsigned long)(param_2,iVar4);
      param_3[1] = lVar7;
      if (lVar7 == 0) goto code_r0x02010c00;
      memcpy(lVar7,lVar9,iVar4);
      lVar7 = 0;
      *(int *)(param_3 + 2) = iVar4;
      *(undefined1 *)((long)param_3 + 0x14) = uVar5;
    }
code_r0x02010be0:
    *param_1 = lVar7;
    return;
  }
  param_3[1] = 0;
code_r0x02010bf8:
  *param_1 = 0;
  return;
}

// ==== Aska::ASON::CalcFreeWorkSize(long*, long*)
// vaddr 0x1f10c34 | ghidra 0x2010c34 | size 240 | symbol _ZN4Aska4ASON16CalcFreeWorkSizeEPlS1_ | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska4ASON16CalcFreeWorkSizeEPlS1_(long param_1,long *param_2,long *param_3)

{
  ulong uVar1;
  ulong uVar2;
  long lVar3;
  long *plVar4;
  long *plVar7;
  long *plVar10;
  long lVar11;
  long *plVar12;
  long lVar13;
  long lVar14;
  long lVar15;
  long lVar16;
  long lVar17;
  long lVar18;
  long lVar19;
  long lVar20;
  long lVar21;
  long lVar22;
  long *plVar5;
  long *plVar6;
  long *plVar8;
  long *plVar9;
  
  lVar14 = *(long *)(param_1 + 0x28);
  lVar3 = *(long *)(param_1 + 0x30);
  if (lVar14 == lVar3) {
    lVar13 = 0;
    lVar15 = 0;
    goto joined_r0x02010c68;
  }
  uVar1 = ((ulong)((lVar3 + -0x20) - lVar14) >> 5) + 1;
  if (uVar1 < 4) {
code_r0x02010cf0:
    lVar15 = 0;
    lVar13 = 0;
    lVar11 = lVar14;
  }
  else {
    uVar2 = 4;
    if ((uVar1 & 3) != 0) {
      uVar2 = uVar1 & 3;
    }
    lVar13 = uVar1 - uVar2;
    if (lVar13 == 0) goto code_r0x02010cf0;
    lVar11 = lVar14 + lVar13 * 0x20;
    plVar10 = (long *)(lVar14 + 0x48);
    lVar14 = 0;
    lVar15 = 0;
    lVar16 = 0;
    lVar17 = 0;
    lVar18 = 0;
    lVar19 = 0;
    lVar20 = 0;
    lVar21 = 0;
    do {
      plVar12 = plVar10 + -8;
      lVar22 = *plVar10;
      plVar4 = plVar10 + 1;
      plVar5 = plVar10 + 4;
      plVar6 = plVar10 + 5;
      plVar7 = plVar10 + -7;
      plVar8 = plVar10 + -4;
      plVar9 = plVar10 + -3;
      lVar13 = lVar13 + -4;
      plVar10 = plVar10 + 0x10;
      lVar20 = lVar22 + lVar20;
      lVar21 = *plVar5 + lVar21;
      lVar16 = *plVar4 + lVar16;
      lVar17 = *plVar6 + lVar17;
      lVar18 = *plVar12 + lVar18;
      lVar19 = *plVar8 + lVar19;
      lVar14 = *plVar7 + lVar14;
      lVar15 = *plVar9 + lVar15;
    } while (lVar13 != 0);
    lVar13 = lVar20 + lVar18 + lVar21 + lVar19;
    lVar15 = lVar16 + lVar14 + lVar17 + lVar15;
  }
  do {
    plVar10 = (long *)(lVar11 + 8);
    plVar4 = (long *)(lVar11 + 0x10);
    lVar11 = lVar11 + 0x20;
    lVar13 = *plVar10 + lVar13;
    lVar15 = *plVar4 + lVar15;
  } while (lVar3 != lVar11);
joined_r0x02010c68:
  if (param_2 != (long *)0x0) {
    *param_2 = lVar13;
  }
  if (param_3 != (long *)0x0) {
    *param_3 = lVar15;
  }
  return lVar13 - lVar15;
}

// ==== Aska::ASON::MakeAValue_Array(Aska::ASON::AValue*, unsigned int)
// vaddr 0x1f10d24 | ghidra 0x2010d24 | size 156 | symbol _ZN4Aska4ASON16MakeAValue_ArrayEPNS0_6AValueEj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska4ASON16MakeAValue_ArrayEPNS0_6AValueEj
               (undefined8 *param_1,long param_2,undefined4 *param_3,uint param_4)

{
  long lVar1;
  undefined8 *puVar2;
  undefined8 uVar3;
  ulong uVar4;
  
  if (param_3 == (undefined4 *)0x0) {
    uVar3 = 0xfffffffffffffc43;
  }
  else {
    *param_3 = 6;
    if (param_4 == 0) {
      uVar3 = 0;
      param_3[4] = 0;
      *(undefined8 *)(param_3 + 2) = 0;
      goto code_r0x02010dac;
    }
    uVar4 = (ulong)param_4;
    lVar1 = Aska::ASON::Malloc(unsigned long)(param_2,uVar4 << 5);
    if (lVar1 != 0) {
      puVar2 = (undefined8 *)(lVar1 + 8);
      do {
        *(undefined4 *)(puVar2 + -1) = 0;
        puVar2[1] = 0;
        puVar2[2] = 0;
        *puVar2 = 0;
        uVar4 = uVar4 - 1;
        puVar2 = puVar2 + 4;
      } while (uVar4 != 0);
      uVar3 = 0;
      *(long *)(param_3 + 2) = lVar1;
      param_3[4] = param_4;
      goto code_r0x02010dac;
    }
    uVar3 = 0xfffffffffffffc41;
  }
  *(undefined8 *)(param_2 + 0x80) = uVar3;
code_r0x02010dac:
  *param_1 = uVar3;
  return;
}

// ==== Aska::ASON::MakeAValue_Map(Aska::ASON::AValue*, unsigned int)
// vaddr 0x1f10dc0 | ghidra 0x2010dc0 | size 172 | symbol _ZN4Aska4ASON14MakeAValue_MapEPNS0_6AValueEj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska4ASON14MakeAValue_MapEPNS0_6AValueEj
               (undefined8 *param_1,long param_2,undefined4 *param_3,uint param_4)

{
  long lVar1;
  undefined8 *puVar2;
  undefined8 uVar3;
  ulong uVar4;
  
  if (param_3 == (undefined4 *)0x0) {
    uVar3 = 0xfffffffffffffc43;
  }
  else {
    *param_3 = 7;
    if (param_4 == 0) {
      uVar3 = 0;
      param_3[4] = 0;
      *(undefined8 *)(param_3 + 2) = 0;
      goto code_r0x02010e58;
    }
    uVar4 = (ulong)param_4;
    lVar1 = Aska::ASON::Malloc(unsigned long)(param_2,uVar4 << 6);
    if (lVar1 != 0) {
      puVar2 = (undefined8 *)(lVar1 + 0x28);
      do {
        *(undefined4 *)(puVar2 + -5) = 0;
        puVar2[1] = 0;
        puVar2[2] = 0;
        *puVar2 = 0;
        puVar2[-3] = 0;
        puVar2[-2] = 0;
        *(undefined4 *)(puVar2 + -1) = 0;
        puVar2[-4] = 0;
        uVar4 = uVar4 - 1;
        puVar2 = puVar2 + 8;
      } while (uVar4 != 0);
      uVar3 = 0;
      *(long *)(param_3 + 2) = lVar1;
      param_3[4] = param_4;
      goto code_r0x02010e58;
    }
    uVar3 = 0xfffffffffffffc41;
  }
  *(undefined8 *)(param_2 + 0x80) = uVar3;
code_r0x02010e58:
  *param_1 = uVar3;
  return;
}

// ==== Aska::ASON::Get(unsigned long, void*) const
// vaddr 0x1f10e6c | ghidra 0x2010e6c | size 8 | symbol _ZNK4Aska4ASON3GetEmPv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska4ASON3GetEmPv(void)

{
  return 0;
}

// ==== Aska::ASON::Set(unsigned long, void const*)
// vaddr 0x1f10e74 | ghidra 0x2010e74 | size 8 | symbol _ZN4Aska4ASON3SetEmPKv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska4ASON3SetEmPKv(void)

{
  return 0;
}

// ==== Aska::ASON::AValue::AMap::Get_(Aska::ASON::AValue const*)
// vaddr 0x1f10e7c | ghidra 0x2010e7c | size 416 | symbol _ZN4Aska4ASON6AValue4AMap4Get_EPKS1_ | lib libSOA-3.7.0.so | 2026-10-04
int * _ZN4Aska4ASON6AValue4AMap4Get_EPKS1_(undefined8 *param_1,int *param_2)

{
  int *piVar1;
  uint uVar2;
  int iVar3;
  bool bVar4;
  bool bVar5;
  byte bVar6;
  int iVar7;
  int *unaff_x20;
  int *piVar8;
  uint uVar9;
  int *piVar10;
  
  if (param_2 == (int *)0x0) {
    piVar10 = (int *)0x0;
  }
  else {
    uVar2 = *(uint *)(param_1 + 1);
    if (uVar2 == 0) {
      bVar6 = 2;
    }
    else {
      iVar3 = *param_2;
      piVar10 = (int *)*param_1;
      uVar9 = 0;
      piVar8 = unaff_x20;
      do {
        unaff_x20 = piVar8;
        if (*piVar10 != iVar3) {
          bVar6 = 4;
          goto code_r0x02010fc8;
        }
        switch(iVar3) {
        case 0:
          bVar6 = 1;
          unaff_x20 = piVar10 + 8;
          break;
        case 1:
          bVar4 = (char)param_2[2] != '\0';
          bVar5 = (char)piVar10[2] == '\0';
          bVar6 = bVar4 != bVar5;
          if ((!bVar4 || !bVar5) && (bVar4 || bVar5)) {
            unaff_x20 = piVar10 + 8;
          }
          break;
        case 2:
        case 3:
          bVar6 = *(long *)(piVar10 + 2) == *(long *)(param_2 + 2);
          unaff_x20 = piVar10 + 8;
          if (!(bool)bVar6) {
            unaff_x20 = piVar8;
          }
          break;
        case 4:
          bVar6 = *(double *)(piVar10 + 2) == *(double *)(param_2 + 2);
          piVar1 = piVar10 + 8;
          if (!(bool)bVar6) {
            piVar1 = piVar8;
          }
          unaff_x20 = piVar10 + 8;
          if (!NAN(*(double *)(piVar10 + 2)) && !NAN(*(double *)(param_2 + 2))) {
            unaff_x20 = piVar1;
          }
          break;
        case 5:
          if (piVar10[6] != param_2[6]) goto code_r0x02010fc4;
code_r0x02010fa4:
          iVar7 = memcmp(*(undefined8 *)(piVar10 + 2),*(undefined8 *)(param_2 + 2));
          bVar6 = iVar7 == 0;
          goto code_r0x02010fb4;
        case 6:
        case 7:
          bVar6 = param_2 == piVar10;
code_r0x02010fb4:
          unaff_x20 = piVar10 + 8;
          if (!(bool)bVar6) {
            unaff_x20 = piVar8;
          }
          break;
        case 8:
code_r0x02010f94:
          if (piVar10[4] == param_2[4]) goto code_r0x02010fa4;
        default:
code_r0x02010fc4:
          bVar6 = 0;
          break;
        case 9:
          if ((char)piVar10[5] == (char)param_2[5]) goto code_r0x02010f94;
          goto code_r0x02010fc4;
        }
code_r0x02010fc8:
        if ((bVar6 | 4) != 4) goto code_r0x02010ffc;
        uVar9 = uVar9 + 1;
        piVar10 = piVar10 + 0x10;
        piVar8 = unaff_x20;
      } while (uVar9 < uVar2);
      bVar6 = 2;
    }
code_r0x02010ffc:
    piVar10 = (int *)0x0;
    if (bVar6 != 2) {
      piVar10 = unaff_x20;
    }
  }
  return piVar10;
}

// ==== Aska::ASON::AValue::AMap::Get_(char const*)
// vaddr 0x1f1101c | ghidra 0x201101c | size 172 | symbol _ZN4Aska4ASON6AValue4AMap4Get_EPKc | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska4ASON6AValue4AMap4Get_EPKc(long *param_1,long param_2)

{
  uint uVar1;
  byte bVar2;
  int iVar3;
  long lVar4;
  long unaff_x20;
  long lVar5;
  uint uVar6;
  
  if (param_2 == 0) {
    lVar4 = 0;
  }
  else {
    uVar1 = *(uint *)(param_1 + 1);
    if (uVar1 == 0) {
      bVar2 = 2;
    }
    else {
      uVar6 = 0;
      lVar4 = *param_1 + 0x20;
      lVar5 = unaff_x20;
      do {
        unaff_x20 = lVar5;
        if (*(int *)(lVar4 + -0x20) == 5) {
          if (*(long *)(lVar4 + -0x10) == 0) {
            bVar2 = 0;
          }
          else {
            iVar3 = strcmp(*(long *)(lVar4 + -0x10),param_2);
            bVar2 = iVar3 == 0;
            unaff_x20 = lVar4;
            if (!(bool)bVar2) {
              unaff_x20 = lVar5;
            }
          }
        }
        else {
          bVar2 = 4;
        }
        if ((bVar2 | 4) != 4) goto code_r0x020110b0;
        uVar6 = uVar6 + 1;
        lVar4 = lVar4 + 0x40;
        lVar5 = unaff_x20;
      } while (uVar6 < uVar1);
      bVar2 = 2;
    }
code_r0x020110b0:
    lVar4 = 0;
    if (bVar2 != 2) {
      lVar4 = unaff_x20;
    }
  }
  return lVar4;
}

// ==== Aska::ASON::u64FromAddress(void const*)
// vaddr 0x1f110c8 | ghidra 0x20110c8 | size 44 | symbol _ZN4Aska4ASON14u64FromAddressEPKv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska4ASON14u64FromAddressEPKv(undefined8 param_1,undefined8 *param_2)

{
  return *param_2;
}

// ==== Aska::ASON::AValue::SetString(char const*, unsigned int, Aska::ASON*)
// vaddr 0x1f110f4 | ghidra 0x20110f4 | size 312 | symbol _ZN4Aska4ASON6AValue9SetStringEPKcjPS0_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska4ASON6AValue9SetStringEPKcjPS0_
               (undefined8 *param_1,undefined4 *param_2,long param_3,uint param_4,long param_5)

{
  ulong uVar1;
  ulong uVar2;
  long lVar3;
  ulong uVar4;
  undefined8 uVar5;
  ulong uVar6;
  
  if (param_3 == 0) {
    uVar5 = 0xfffffffffffffc43;
  }
  else {
    *param_2 = 5;
    if (param_4 == 0) {
      uVar5 = 0;
      *(undefined8 *)(param_2 + 4) = 0;
      *(undefined8 *)(param_2 + 6) = 0xffffffff00000000;
      *(undefined8 *)(param_2 + 2) = 0;
    }
    else {
      uVar6 = (ulong)param_4;
      lVar3 = Aska::ASON::Malloc(unsigned long)(param_5,uVar6);
      *(long *)(param_2 + 2) = lVar3;
      if (lVar3 != 0) {
        *(undefined2 *)(param_2 + 7) = *(undefined2 *)(param_5 + 0x58);
        memcpy(lVar3,param_3,uVar6);
        param_2[6] = param_4;
        if (*(char *)(param_5 + 0x88) == '\0') {
          uVar5 = 0;
          *(undefined8 *)(param_2 + 4) = 0;
          *(undefined2 *)((long)param_2 + 0x1e) = 0xffff;
          goto code_r0x02011214;
        }
        lVar3 = Aska::ASON::Malloc(unsigned long)(param_5,(ulong)(param_4 + 1));
        *(long *)(param_2 + 4) = lVar3;
        if (lVar3 != 0) {
          *(undefined2 *)((long)param_2 + 0x1e) = *(undefined2 *)(param_5 + 0x58);
          uVar4 = strlen(param_3);
          uVar1 = uVar4 + 1;
          if (uVar1 != uVar6) {
            uVar4 = uVar4 + 1;
          }
          uVar2 = uVar6;
          if (uVar1 <= uVar6) {
            uVar2 = uVar4;
          }
          if (uVar2 < param_4 + 1) {
            strncpy(lVar3,param_3,uVar2);
            if (uVar1 < uVar6) {
              uVar5 = 0;
            }
            else {
              uVar5 = 0;
              *(undefined1 *)(lVar3 + uVar2) = 0;
            }
          }
          else {
            raise(5);
            uVar5 = 0;
          }
          goto code_r0x02011214;
        }
      }
      uVar5 = 0xfffffffffffffc41;
    }
  }
code_r0x02011214:
  *param_1 = uVar5;
  return;
}

// ==== Aska::Status Aska::ASON::UnpackMessagePack<false>(Aska::ASON::MessagePackContext*, signed char const*, unsigned long, unsigned long*)
// vaddr 0x1f1122c | ghidra 0x201122c | size 3960 | symbol _ZN4Aska4ASON17UnpackMessagePackILb0EEENS_6StatusEPNS0_18MessagePackContextEPKamPm | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Type propagation algorithm not settling */

void _ZN4Aska4ASON17UnpackMessagePackILb0EEENS_6StatusEPNS0_18MessagePackContextEPKamPm
               (undefined8 *param_1,long param_2,undefined8 *param_3,long param_4,long param_5,
               long *param_6)

{
  uint *puVar1;
  ushort uVar2;
  byte bVar3;
  undefined *puVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  long lVar8;
  undefined8 *puVar9;
  undefined8 *puVar10;
  uint uVar11;
  undefined8 uVar12;
  uint uVar13;
  uint uVar14;
  uint *puVar15;
  byte *pbVar16;
  byte *pbVar17;
  ulong uVar18;
  uint uVar19;
  uint *puVar20;
  undefined8 uVar21;
  int *piStack_98;
  
  uVar13 = *(uint *)(param_3 + 4);
  uVar11 = *(uint *)((long)param_3 + 0x24);
  uVar19 = *(uint *)(param_3 + 5);
  puVar15 = (uint *)(param_4 + *param_6);
  if (*param_6 != param_5) {
    puVar1 = (uint *)(param_4 + param_5);
    pbVar16 = PTR__ZGVZN4Aska7Machine6_HTONSEtE9kMyEndian_02cc0910;
    pbVar17 = PTR__ZGVZN4Aska7Machine6_HTONLEjE9kMyEndian_02cbe508;
code_r0x020112a4:
    if (uVar13 != 0) goto code_r0x02011550;
    bVar3 = (byte)*puVar15;
    puVar20 = puVar15;
    if ((-1 < (char)bVar3) || (0xdf < bVar3)) {
code_r0x02011584:
      goto joined_r0x02011988;
    }
    uVar13 = (uint)bVar3;
    if ((uVar13 & 0xe0) == 0xa0) {
      uVar11 = uVar13 & 0x1f;
      if ((bVar3 & 0x1f) != 0) goto code_r0x02011540;
      uVar13 = 0;
      goto joined_r0x02011988;
    }
    uVar14 = (uint)bVar3;
    if ((uVar13 & 0xe0) == 0xc0) {
      uVar13 = 0;
      uVar12 = 0xffffffffffffffff;
      uVar5 = 0x11;
      uVar6 = 0x22;
      switch(uVar14) {
      case 0xc0:
      case 0xc2:
      case 0xc3:
        goto code_r0x02011584;
      default:
        goto code_r0x02012170;
      case 0xc4:
      case 0xc5:
      case 0xc6:
      case 0xca:
      case 0xcb:
      case 0xcc:
      case 0xcd:
      case 0xce:
      case 0xcf:
      case 0xd0:
      case 0xd1:
      case 0xd2:
      case 0xd3:
        uVar11 = uVar14 & 3;
        break;
      case 199:
      case 200:
      case 0xc9:
        uVar11 = uVar14 + 1 & 3;
        break;
      case 0xd4:
      case 0xd5:
      case 0xd6:
      case 0xd7:
        uVar11 = 1 << ((ulong)bVar3 & 3);
        goto code_r0x020117b4;
      case 0xd8:
        goto code_r0x02011544;
      case 0xd9:
      case 0xda:
      case 0xdb:
        uVar11 = (uVar14 & 3) - 1;
        break;
      case 0xdc:
      case 0xdd:
      case 0xde:
      case 0xdf:
        uVar11 = uVar14 & 1;
        iVar7 = 2;
        goto code_r0x02011314;
      }
      iVar7 = 1;
code_r0x02011314:
      uVar5 = iVar7 << (ulong)(uVar11 & 0x1f);
      uVar6 = uVar14 & 0x1f;
code_r0x02011544:
      uVar13 = uVar6;
      uVar11 = uVar5;
      puVar15 = (uint *)((long)puVar20 + 1);
code_r0x02011550:
      if ((ulong)((long)puVar1 - (long)puVar15) < (ulong)uVar11) {
        uVar12 = 0;
        goto code_r0x02012170;
      }
      puVar20 = (uint *)((long)puVar15 + (ulong)(uVar11 - 1));
      uVar5 = 2;
      uVar6 = 0x22;
      switch(uVar13) {
      case 4:
        uVar11 = (uint)(byte)*puVar15;
        if (uVar11 == 0) {
          uVar13 = 4;
          goto joined_r0x02011988;
        }
        uVar5 = uVar11;
        uVar6 = 0x21;
        goto code_r0x02011544;
      case 5:
        uVar2 = (ushort)*puVar15;
        if (((*pbVar16 & 1) == 0) &&
           (iVar7 = __cxa_guard_acquire(pbVar16),
           puVar4 = PTR__ZGVZN4Aska7Machine6_HTONSEtE9kMyEndian_02cc0910,
           pbVar16 = PTR__ZGVZN4Aska7Machine6_HTONSEtE9kMyEndian_02cc0910, iVar7 != 0)) {
          *(undefined4 *)PTR__ZZN4Aska7Machine6_HTONSEtE9kMyEndian_02cbc7a8 = 1;
          __cxa_guard_release(puVar4);
          pbVar16 = PTR__ZGVZN4Aska7Machine6_HTONSEtE9kMyEndian_02cc0910;
        }
        uVar11 = (uint)uVar2;
        if (*(int *)PTR__ZZN4Aska7Machine6_HTONSEtE9kMyEndian_02cbc7a8 != 2) {
          uVar11 = (uint)(uVar2 >> 8) | (uVar2 & 0xff00ff) << 8;
        }
        if (uVar11 == 0) {
          uVar13 = 5;
          goto joined_r0x02011988;
        }
        break;
      case 6:
        uVar11 = *puVar15;
        if (((*pbVar17 & 1) == 0) &&
           (iVar7 = __cxa_guard_acquire(pbVar17),
           pbVar16 = PTR__ZGVZN4Aska7Machine6_HTONSEtE9kMyEndian_02cc0910, iVar7 != 0)) {
          *(undefined4 *)PTR__ZZN4Aska7Machine6_HTONLEjE9kMyEndian_02cc0b50 = 1;
          __cxa_guard_release(pbVar17);
          pbVar16 = PTR__ZGVZN4Aska7Machine6_HTONSEtE9kMyEndian_02cc0910;
        }
        uVar13 = (uVar11 & 0xff00ff00) >> 8 | (uVar11 & 0xff00ff) << 8;
        if (*(int *)PTR__ZZN4Aska7Machine6_HTONLEjE9kMyEndian_02cc0b50 != 2) {
          uVar11 = uVar13 >> 0x10 | uVar13 << 0x10;
        }
        if (uVar11 == 0) {
          uVar11 = 0;
          uVar13 = 6;
          goto joined_r0x02011988;
        }
        break;
      case 7:
        uVar11 = (uint)(byte)*puVar15;
        puVar15 = puVar20;
code_r0x020117b4:
        puVar20 = puVar15;
        uVar5 = uVar11 + 1;
        uVar6 = 0x22;
        goto code_r0x02011544;
      case 8:
        uVar2 = (ushort)*puVar15;
        if (((*pbVar16 & 1) == 0) &&
           (iVar7 = __cxa_guard_acquire(pbVar16),
           puVar4 = PTR__ZGVZN4Aska7Machine6_HTONSEtE9kMyEndian_02cc0910,
           pbVar16 = PTR__ZGVZN4Aska7Machine6_HTONSEtE9kMyEndian_02cc0910, iVar7 != 0)) {
          *(undefined4 *)PTR__ZZN4Aska7Machine6_HTONSEtE9kMyEndian_02cbc7a8 = 1;
          __cxa_guard_release(puVar4);
          pbVar16 = PTR__ZGVZN4Aska7Machine6_HTONSEtE9kMyEndian_02cc0910;
        }
        uVar11 = (uint)uVar2;
        if (*(int *)PTR__ZZN4Aska7Machine6_HTONSEtE9kMyEndian_02cbc7a8 != 2) {
          uVar11 = (uint)(uVar2 >> 8) | (uVar2 & 0xff00ff) << 8;
        }
        uVar5 = uVar11 + 1;
        uVar6 = 0x22;
        goto code_r0x02011544;
      case 9:
        uVar11 = *puVar15;
        if (((*pbVar17 & 1) == 0) &&
           (iVar7 = __cxa_guard_acquire(pbVar17),
           pbVar16 = PTR__ZGVZN4Aska7Machine6_HTONSEtE9kMyEndian_02cc0910, iVar7 != 0)) {
          *(undefined4 *)PTR__ZZN4Aska7Machine6_HTONLEjE9kMyEndian_02cc0b50 = 1;
          __cxa_guard_release(pbVar17);
          pbVar16 = PTR__ZGVZN4Aska7Machine6_HTONSEtE9kMyEndian_02cc0910;
        }
        uVar13 = (uVar11 & 0xff00ff00) >> 8 | (uVar11 & 0xff00ff) << 8;
        if (*(int *)PTR__ZZN4Aska7Machine6_HTONLEjE9kMyEndian_02cc0b50 != 2) {
          uVar11 = uVar13 >> 0x10 | uVar13 << 0x10;
        }
        if (uVar11 + 1 == 0) {
          uVar11 = 0;
          uVar13 = 9;
          goto joined_r0x02011988;
        }
        uVar5 = uVar11 + 1;
        uVar6 = 0x22;
        goto code_r0x02011544;
      case 10:
        goto code_r0x020118d4;
      case 0xb:
        uVar13 = 0xb;
        goto joined_r0x02011988;
      case 0xc:
      case 0xd:
      case 0xe:
      case 0x10:
      case 0x11:
      case 0x12:
      case 0x20:
      case 0x21:
      case 0x22:
        goto code_r0x02011584;
      case 0xf:
        uVar13 = 0xf;
        goto joined_r0x02011988;
      case 0x13:
        uVar13 = 0x13;
        goto joined_r0x02011988;
      case 0x14:
        goto code_r0x02011544;
      case 0x15:
        uVar5 = 3;
        uVar6 = 0x22;
        goto code_r0x02011544;
      case 0x16:
        uVar5 = 5;
        uVar6 = 0x22;
        goto code_r0x02011544;
      case 0x17:
        uVar5 = 9;
        uVar6 = 0x22;
        goto code_r0x02011544;
      case 0x18:
        uVar5 = 0x11;
        uVar6 = 0x22;
        goto code_r0x02011544;
      case 0x19:
        uVar11 = (uint)(byte)*puVar15;
        if (uVar11 == 0) {
          uVar13 = 0x19;
          goto joined_r0x02011988;
        }
code_r0x02011540:
        uVar5 = uVar11;
        uVar6 = 0x20;
        goto code_r0x02011544;
      case 0x1a:
        uVar2 = (ushort)*puVar15;
        if (((*pbVar16 & 1) == 0) &&
           (iVar7 = __cxa_guard_acquire(pbVar16),
           puVar4 = PTR__ZGVZN4Aska7Machine6_HTONSEtE9kMyEndian_02cc0910,
           pbVar16 = PTR__ZGVZN4Aska7Machine6_HTONSEtE9kMyEndian_02cc0910, iVar7 != 0)) {
          *(undefined4 *)PTR__ZZN4Aska7Machine6_HTONSEtE9kMyEndian_02cbc7a8 = 1;
          __cxa_guard_release(puVar4);
          pbVar16 = PTR__ZGVZN4Aska7Machine6_HTONSEtE9kMyEndian_02cc0910;
        }
        uVar11 = (uint)uVar2;
        if (*(int *)PTR__ZZN4Aska7Machine6_HTONSEtE9kMyEndian_02cbc7a8 != 2) {
          uVar11 = (uint)(uVar2 >> 8) | (uVar2 & 0xff00ff) << 8;
        }
        if (uVar11 != 0) goto code_r0x02011b14;
        uVar13 = 0x1a;
        goto joined_r0x02011988;
      case 0x1b:
        uVar11 = *puVar15;
        if (((*pbVar17 & 1) == 0) &&
           (iVar7 = __cxa_guard_acquire(pbVar17),
           pbVar16 = PTR__ZGVZN4Aska7Machine6_HTONSEtE9kMyEndian_02cc0910, iVar7 != 0)) {
          *(undefined4 *)PTR__ZZN4Aska7Machine6_HTONLEjE9kMyEndian_02cc0b50 = 1;
          __cxa_guard_release(pbVar17);
          pbVar16 = PTR__ZGVZN4Aska7Machine6_HTONSEtE9kMyEndian_02cc0910;
        }
        uVar13 = (uVar11 & 0xff00ff00) >> 8 | (uVar11 & 0xff00ff) << 8;
        if (*(int *)PTR__ZZN4Aska7Machine6_HTONLEjE9kMyEndian_02cc0b50 != 2) {
          uVar11 = uVar13 >> 0x10 | uVar13 << 0x10;
        }
        if (uVar11 == 0) {
          uVar11 = 0;
          uVar13 = 0x1b;
          goto joined_r0x02011988;
        }
code_r0x02011b14:
        uVar5 = uVar11;
        uVar6 = 0x20;
        goto code_r0x02011544;
      case 0x1c:
        uVar2 = (ushort)*puVar15;
        if (((*pbVar16 & 1) == 0) &&
           (iVar7 = __cxa_guard_acquire(pbVar16),
           puVar4 = PTR__ZGVZN4Aska7Machine6_HTONSEtE9kMyEndian_02cc0910, iVar7 != 0)) {
          *(undefined4 *)PTR__ZZN4Aska7Machine6_HTONSEtE9kMyEndian_02cbc7a8 = 1;
          __cxa_guard_release(puVar4);
        }
        uVar13 = (uint)uVar2;
        if (*(int *)PTR__ZZN4Aska7Machine6_HTONSEtE9kMyEndian_02cbc7a8 != 2) {
          uVar13 = (uint)(uVar2 >> 8) | (uVar2 & 0xff00ff) << 8;
        }
        if (0x1f < uVar19) {
          uVar13 = 0x1c;
          goto code_r0x0201216c;
        }
        puVar10 = param_3 + (ulong)uVar19 * 10 + 6;
        *(undefined4 *)puVar10 = 6;
        uVar18 = (ulong)uVar13;
        piStack_98 = (int *)(param_3 + (ulong)uVar19 * 10 + 8);
        *piStack_98 = 0;
        lVar8 = Aska::ASON::Malloc(unsigned long)(param_2,uVar18 << 5);
        if (lVar8 != 0) {
          if (uVar13 != 0) {
            puVar9 = (undefined8 *)(lVar8 + 8);
            do {
              *(undefined4 *)(puVar9 + -1) = 0;
              puVar9[1] = 0;
              puVar9[2] = 0;
              *puVar9 = 0;
              uVar18 = uVar18 - 1;
              puVar9 = puVar9 + 4;
            } while (uVar18 != 0);
          }
          param_3[(ulong)uVar19 * 10 + 7] = lVar8;
code_r0x02011f48:
          pbVar16 = PTR__ZGVZN4Aska7Machine6_HTONSEtE9kMyEndian_02cc0910;
          pbVar17 = PTR__ZGVZN4Aska7Machine6_HTONLEjE9kMyEndian_02cbe508;
          *(undefined2 *)((long)param_3 + (ulong)uVar19 * 0x50 + 0x44) =
               *(undefined2 *)(param_2 + 0x58);
          *(undefined2 *)(param_3 + (ulong)uVar19 * 10 + 0xb) = *(undefined2 *)(param_2 + 0x58);
          if (uVar13 == 0) {
            uVar21 = param_3[(ulong)uVar19 * 10 + 9];
            uVar12 = param_3[(ulong)uVar19 * 10 + 8];
            uVar13 = 0x1c;
            goto code_r0x02012098;
          }
code_r0x02011fb0:
          puVar10 = param_3 + (ulong)uVar19 * 10;
          *(uint *)(puVar10 + 10) = uVar13;
          goto code_r0x02011fb8;
        }
        param_3[(ulong)uVar19 * 10 + 7] = 0;
        if (uVar13 == 0) goto code_r0x02011f48;
        uVar13 = 0x1c;
        goto code_r0x02012164;
      case 0x1d:
        uVar13 = *puVar15;
        if (((*pbVar17 & 1) == 0) &&
           (iVar7 = __cxa_guard_acquire(pbVar17),
           puVar4 = PTR__ZGVZN4Aska7Machine6_HTONLEjE9kMyEndian_02cbe508, iVar7 != 0)) {
          *(undefined4 *)PTR__ZZN4Aska7Machine6_HTONLEjE9kMyEndian_02cc0b50 = 1;
          __cxa_guard_release(puVar4);
        }
        uVar14 = (uVar13 & 0xff00ff00) >> 8 | (uVar13 & 0xff00ff) << 8;
        if (*(int *)PTR__ZZN4Aska7Machine6_HTONLEjE9kMyEndian_02cc0b50 != 2) {
          uVar13 = uVar14 >> 0x10 | uVar14 << 0x10;
        }
        if (0x1f < uVar19) {
          uVar13 = 0x1d;
          goto code_r0x0201216c;
        }
        puVar10 = param_3 + (ulong)uVar19 * 10 + 6;
        *(undefined4 *)puVar10 = 6;
        uVar18 = (ulong)uVar13;
        piStack_98 = (int *)(param_3 + (ulong)uVar19 * 10 + 8);
        *piStack_98 = 0;
        lVar8 = Aska::ASON::Malloc(unsigned long)(param_2,uVar18 << 5);
        if (lVar8 != 0) {
          if (uVar13 != 0) {
            puVar9 = (undefined8 *)(lVar8 + 8);
            do {
              *(undefined4 *)(puVar9 + -1) = 0;
              puVar9[1] = 0;
              puVar9[2] = 0;
              *puVar9 = 0;
              uVar18 = uVar18 - 1;
              puVar9 = puVar9 + 4;
            } while (uVar18 != 0);
          }
          param_3[(ulong)uVar19 * 10 + 7] = lVar8;
code_r0x02011f94:
          pbVar16 = PTR__ZGVZN4Aska7Machine6_HTONSEtE9kMyEndian_02cc0910;
          pbVar17 = PTR__ZGVZN4Aska7Machine6_HTONLEjE9kMyEndian_02cbe508;
          *(undefined2 *)((long)param_3 + (ulong)uVar19 * 0x50 + 0x44) =
               *(undefined2 *)(param_2 + 0x58);
          *(undefined2 *)(param_3 + (ulong)uVar19 * 10 + 0xb) = *(undefined2 *)(param_2 + 0x58);
          if (uVar13 != 0) goto code_r0x02011fb0;
          uVar21 = param_3[(ulong)uVar19 * 10 + 9];
          uVar12 = param_3[(ulong)uVar19 * 10 + 8];
          uVar13 = 0x1d;
          goto code_r0x02012098;
        }
        param_3[(ulong)uVar19 * 10 + 7] = 0;
        if (uVar13 == 0) goto code_r0x02011f94;
        uVar13 = 0x1d;
        goto code_r0x02012164;
      case 0x1e:
        uVar2 = (ushort)*puVar15;
        if (((*pbVar16 & 1) == 0) &&
           (iVar7 = __cxa_guard_acquire(pbVar16),
           puVar4 = PTR__ZGVZN4Aska7Machine6_HTONSEtE9kMyEndian_02cc0910, iVar7 != 0)) {
          *(undefined4 *)PTR__ZZN4Aska7Machine6_HTONSEtE9kMyEndian_02cbc7a8 = 1;
          __cxa_guard_release(puVar4);
        }
        uVar13 = (uint)uVar2;
        if (*(int *)PTR__ZZN4Aska7Machine6_HTONSEtE9kMyEndian_02cbc7a8 != 2) {
          uVar13 = (uint)(uVar2 >> 8) | (uVar2 & 0xff00ff) << 8;
        }
        if (0x1f < uVar19) {
          uVar13 = 0x1e;
          goto code_r0x0201216c;
        }
        puVar10 = param_3 + (ulong)uVar19 * 10 + 6;
        *(undefined4 *)puVar10 = 7;
        uVar18 = (ulong)uVar13;
        piStack_98 = (int *)(param_3 + (ulong)uVar19 * 10 + 8);
        *piStack_98 = 0;
        lVar8 = Aska::ASON::Malloc(unsigned long)(param_2,uVar18 << 6);
        if (lVar8 != 0) {
          if (uVar13 != 0) {
            puVar9 = (undefined8 *)(lVar8 + 0x28);
            do {
              *(undefined4 *)(puVar9 + -5) = 0;
              puVar9[1] = 0;
              puVar9[2] = 0;
              *puVar9 = 0;
              puVar9[-3] = 0;
              puVar9[-2] = 0;
              *(undefined4 *)(puVar9 + -1) = 0;
              puVar9[-4] = 0;
              uVar18 = uVar18 - 1;
              puVar9 = puVar9 + 8;
            } while (uVar18 != 0);
          }
          param_3[(ulong)uVar19 * 10 + 7] = lVar8;
code_r0x02011fe0:
          pbVar16 = PTR__ZGVZN4Aska7Machine6_HTONSEtE9kMyEndian_02cc0910;
          pbVar17 = PTR__ZGVZN4Aska7Machine6_HTONLEjE9kMyEndian_02cbe508;
          *(undefined2 *)((long)param_3 + (ulong)uVar19 * 0x50 + 0x44) =
               *(undefined2 *)(param_2 + 0x58);
          *(undefined2 *)(param_3 + (ulong)uVar19 * 10 + 0xb) = *(undefined2 *)(param_2 + 0x58);
          if (uVar13 == 0) {
            uVar21 = param_3[(ulong)uVar19 * 10 + 9];
            uVar12 = param_3[(ulong)uVar19 * 10 + 8];
            uVar13 = 0x1e;
            goto code_r0x020120ac;
          }
code_r0x02012048:
          puVar10 = param_3 + (ulong)uVar19 * 10;
          *(uint *)(puVar10 + 10) = uVar13;
          goto code_r0x02012050;
        }
        param_3[(ulong)uVar19 * 10 + 7] = 0;
        if (uVar13 == 0) goto code_r0x02011fe0;
        uVar13 = 0x1e;
        goto code_r0x02012164;
      case 0x1f:
        uVar13 = *puVar15;
        if (((*pbVar17 & 1) == 0) &&
           (iVar7 = __cxa_guard_acquire(pbVar17),
           puVar4 = PTR__ZGVZN4Aska7Machine6_HTONLEjE9kMyEndian_02cbe508, iVar7 != 0)) {
          *(undefined4 *)PTR__ZZN4Aska7Machine6_HTONLEjE9kMyEndian_02cc0b50 = 1;
          __cxa_guard_release(puVar4);
        }
        uVar14 = (uVar13 & 0xff00ff00) >> 8 | (uVar13 & 0xff00ff) << 8;
        if (*(int *)PTR__ZZN4Aska7Machine6_HTONLEjE9kMyEndian_02cc0b50 != 2) {
          uVar13 = uVar14 >> 0x10 | uVar14 << 0x10;
        }
        if (0x1f < uVar19) {
          uVar13 = 0x1f;
          goto code_r0x0201216c;
        }
        puVar10 = param_3 + (ulong)uVar19 * 10 + 6;
        *(undefined4 *)puVar10 = 7;
        uVar18 = (ulong)uVar13;
        piStack_98 = (int *)(param_3 + (ulong)uVar19 * 10 + 8);
        *piStack_98 = 0;
        lVar8 = Aska::ASON::Malloc(unsigned long)(param_2,uVar18 << 6);
        if (lVar8 != 0) {
          if (uVar13 != 0) {
            puVar9 = (undefined8 *)(lVar8 + 0x28);
            do {
              *(undefined4 *)(puVar9 + -5) = 0;
              puVar9[1] = 0;
              puVar9[2] = 0;
              *puVar9 = 0;
              puVar9[-3] = 0;
              puVar9[-2] = 0;
              *(undefined4 *)(puVar9 + -1) = 0;
              puVar9[-4] = 0;
              uVar18 = uVar18 - 1;
              puVar9 = puVar9 + 8;
            } while (uVar18 != 0);
          }
          param_3[(ulong)uVar19 * 10 + 7] = lVar8;
code_r0x0201202c:
          pbVar16 = PTR__ZGVZN4Aska7Machine6_HTONSEtE9kMyEndian_02cc0910;
          pbVar17 = PTR__ZGVZN4Aska7Machine6_HTONLEjE9kMyEndian_02cbe508;
          *(undefined2 *)((long)param_3 + (ulong)uVar19 * 0x50 + 0x44) =
               *(undefined2 *)(param_2 + 0x58);
          *(undefined2 *)(param_3 + (ulong)uVar19 * 10 + 0xb) = *(undefined2 *)(param_2 + 0x58);
          if (uVar13 != 0) goto code_r0x02012048;
          uVar21 = param_3[(ulong)uVar19 * 10 + 9];
          uVar12 = param_3[(ulong)uVar19 * 10 + 8];
          uVar13 = 0x1f;
          goto code_r0x020120ac;
        }
        param_3[(ulong)uVar19 * 10 + 7] = 0;
        if (uVar13 == 0) goto code_r0x0201202c;
        uVar13 = 0x1f;
        goto code_r0x02012164;
      default:
        goto code_r0x0201216c;
      }
      uVar5 = uVar11;
      uVar6 = 0x21;
      goto code_r0x02011544;
    }
    if ((uVar13 & 0xf0) == 0x90) {
      if (0x1f < uVar19) {
code_r0x020120fc:
        uVar13 = 0;
code_r0x0201216c:
        puVar15 = puVar20;
        uVar12 = 0xffffffffffffffff;
        goto code_r0x02012170;
      }
      puVar10 = param_3 + (ulong)uVar19 * 10 + 6;
      *(undefined4 *)puVar10 = 6;
      uVar18 = (ulong)(uVar14 & 0xf);
      piStack_98 = (int *)(param_3 + (ulong)uVar19 * 10 + 8);
      *piStack_98 = 0;
      lVar8 = Aska::ASON::Malloc(unsigned long)(param_2,uVar18 << 5);
      pbVar16 = PTR__ZGVZN4Aska7Machine6_HTONSEtE9kMyEndian_02cc0910;
      pbVar17 = PTR__ZGVZN4Aska7Machine6_HTONLEjE9kMyEndian_02cbe508;
      if (lVar8 == 0) {
        param_3[(ulong)uVar19 * 10 + 7] = 0;
        pbVar16 = PTR__ZGVZN4Aska7Machine6_HTONSEtE9kMyEndian_02cc0910;
        pbVar17 = PTR__ZGVZN4Aska7Machine6_HTONLEjE9kMyEndian_02cbe508;
        if ((bVar3 & 0xf) != 0) {
code_r0x0201212c:
          uVar13 = 0;
code_r0x02012164:
          *(undefined8 *)(param_2 + 0x80) = 0xfffffffffffffc41;
          goto code_r0x0201216c;
        }
      }
      else {
        if ((bVar3 & 0xf) != 0) {
          puVar9 = (undefined8 *)(lVar8 + 8);
          do {
            *(undefined4 *)(puVar9 + -1) = 0;
            puVar9[1] = 0;
            puVar9[2] = 0;
            *puVar9 = 0;
            uVar18 = uVar18 - 1;
            puVar9 = puVar9 + 4;
          } while (uVar18 != 0);
        }
        param_3[(ulong)uVar19 * 10 + 7] = lVar8;
      }
      *(undefined2 *)((long)param_3 + (ulong)uVar19 * 0x50 + 0x44) = *(undefined2 *)(param_2 + 0x58)
      ;
      *(undefined2 *)(param_3 + (ulong)uVar19 * 10 + 0xb) = *(undefined2 *)(param_2 + 0x58);
      if ((bVar3 & 0xf) == 0) {
        uVar21 = param_3[(ulong)uVar19 * 10 + 9];
        uVar12 = param_3[(ulong)uVar19 * 10 + 8];
        uVar13 = 0;
code_r0x02012098:
        param_3[3] = uVar21;
        param_3[2] = uVar12;
        uVar21 = puVar10[1];
        uVar12 = *puVar10;
code_r0x020120b4:
        param_3[1] = uVar21;
        *param_3 = uVar12;
        goto joined_r0x02011988;
      }
      puVar10 = param_3 + (ulong)uVar19 * 10;
      *(uint *)(puVar10 + 10) = uVar14 & 0xf;
code_r0x02011fb8:
      *(undefined4 *)((long)puVar10 + 0x54) = 0;
    }
    else {
      uVar12 = 0xffffffffffffffff;
      if ((-1 < (char)bVar3) || (0x8f < uVar14)) {
        uVar13 = 0;
        goto code_r0x02012170;
      }
      if (0x1f < uVar19) goto code_r0x020120fc;
      puVar10 = param_3 + (ulong)uVar19 * 10 + 6;
      *(undefined4 *)puVar10 = 7;
      uVar18 = (ulong)(uVar14 & 0xf);
      piStack_98 = (int *)(param_3 + (ulong)uVar19 * 10 + 8);
      *piStack_98 = 0;
      lVar8 = Aska::ASON::Malloc(unsigned long)(param_2,uVar18 << 6);
      pbVar16 = PTR__ZGVZN4Aska7Machine6_HTONSEtE9kMyEndian_02cc0910;
      pbVar17 = PTR__ZGVZN4Aska7Machine6_HTONLEjE9kMyEndian_02cbe508;
      if (lVar8 == 0) {
        param_3[(ulong)uVar19 * 10 + 7] = 0;
        pbVar16 = PTR__ZGVZN4Aska7Machine6_HTONSEtE9kMyEndian_02cc0910;
        pbVar17 = PTR__ZGVZN4Aska7Machine6_HTONLEjE9kMyEndian_02cbe508;
        if ((bVar3 & 0xf) != 0) goto code_r0x0201212c;
      }
      else {
        if ((bVar3 & 0xf) != 0) {
          puVar9 = (undefined8 *)(lVar8 + 0x28);
          do {
            *(undefined4 *)(puVar9 + -5) = 0;
            puVar9[1] = 0;
            puVar9[2] = 0;
            *puVar9 = 0;
            puVar9[-3] = 0;
            puVar9[-2] = 0;
            *(undefined4 *)(puVar9 + -1) = 0;
            puVar9[-4] = 0;
            uVar18 = uVar18 - 1;
            puVar9 = puVar9 + 8;
          } while (uVar18 != 0);
        }
        param_3[(ulong)uVar19 * 10 + 7] = lVar8;
      }
      *(undefined2 *)((long)param_3 + (ulong)uVar19 * 0x50 + 0x44) = *(undefined2 *)(param_2 + 0x58)
      ;
      *(undefined2 *)(param_3 + (ulong)uVar19 * 10 + 0xb) = *(undefined2 *)(param_2 + 0x58);
      if ((bVar3 & 0xf) == 0) {
        uVar21 = param_3[(ulong)uVar19 * 10 + 9];
        uVar12 = param_3[(ulong)uVar19 * 10 + 8];
        uVar13 = 0;
code_r0x020120ac:
        param_3[3] = uVar21;
        param_3[2] = uVar12;
        uVar21 = puVar10[1];
        uVar12 = *puVar10;
        goto code_r0x020120b4;
      }
      puVar10 = param_3 + (ulong)uVar19 * 10;
      *(uint *)(puVar10 + 10) = uVar14 & 0xf;
code_r0x02012050:
      *(undefined4 *)((long)puVar10 + 0x54) = 1;
    }
    uVar19 = uVar19 + 1;
    *piStack_98 = *piStack_98 + 1;
    goto code_r0x0201207c;
  }
  uVar12 = 0;
code_r0x02012170:
  *param_1 = uVar12;
  *(uint *)(param_3 + 4) = uVar13;
  *(uint *)((long)param_3 + 0x24) = uVar11;
  *(uint *)(param_3 + 5) = uVar19;
  *param_6 = (long)puVar15 - param_4;
  return;
code_r0x020118d4:
  if (((*pbVar17 & 1) == 0) &&
     (iVar7 = __cxa_guard_acquire(pbVar17),
     pbVar16 = PTR__ZGVZN4Aska7Machine6_HTONSEtE9kMyEndian_02cc0910, iVar7 != 0)) {
    *(undefined4 *)PTR__ZZN4Aska7Machine6_HTONLEjE9kMyEndian_02cc0b50 = 1;
    __cxa_guard_release(pbVar17);
    pbVar16 = PTR__ZGVZN4Aska7Machine6_HTONSEtE9kMyEndian_02cc0910;
  }
  uVar13 = 10;
joined_r0x02011988:
  if (uVar19 != 0) {
    puVar10 = param_3 + (ulong)(uVar19 - 1) * 10 + 0xc;
    do {
      iVar7 = *(int *)((long)puVar10 + -0xc);
      if (iVar7 == 0) {
        uVar12 = param_3[2];
        puVar9 = (undefined8 *)(puVar10[-5] + (ulong)(*(int *)(puVar10 + -4) - 1) * 0x20);
        puVar9[3] = param_3[3];
        puVar9[2] = uVar12;
        uVar12 = *param_3;
        puVar9[1] = param_3[1];
        *puVar9 = uVar12;
        iVar7 = *(int *)(puVar10 + -2);
        *(int *)(puVar10 + -2) = iVar7 + -1;
        if (iVar7 + -1 != 0) {
          *(int *)(puVar10 + -4) = *(int *)(puVar10 + -4) + 1;
          goto code_r0x0201207c;
        }
      }
      else {
        if (iVar7 != 2) {
          if (iVar7 != 1) goto code_r0x0201216c;
          uVar12 = param_3[2];
          puVar10[3] = param_3[3];
          puVar10[2] = uVar12;
          uVar21 = param_3[1];
          uVar12 = *param_3;
          *(undefined4 *)((long)puVar10 + -0xc) = 2;
          puVar10[1] = uVar21;
          *puVar10 = uVar12;
          goto code_r0x0201207c;
        }
        uVar12 = puVar10[2];
        puVar9 = (undefined8 *)(puVar10[-5] + (ulong)(*(int *)(puVar10 + -4) - 1) * 0x40);
        puVar9[3] = puVar10[3];
        puVar9[2] = uVar12;
        uVar12 = *puVar10;
        puVar9[1] = puVar10[1];
        *puVar9 = uVar12;
        uVar12 = param_3[2];
        lVar8 = puVar10[-5] + (ulong)(*(int *)(puVar10 + -4) - 1) * 0x40;
        *(undefined8 *)(lVar8 + 0x38) = param_3[3];
        *(undefined8 *)(lVar8 + 0x30) = uVar12;
        uVar12 = *param_3;
        *(undefined8 *)(lVar8 + 0x28) = param_3[1];
        *(undefined8 *)(lVar8 + 0x20) = uVar12;
        iVar7 = *(int *)(puVar10 + -2);
        *(int *)(puVar10 + -2) = iVar7 + -1;
        if (iVar7 + -1 != 0) goto code_r0x02011668;
      }
      uVar12 = puVar10[-4];
      uVar19 = uVar19 - 1;
      param_3[3] = puVar10[-3];
      param_3[2] = uVar12;
      puVar9 = puVar10 + -5;
      uVar12 = puVar10[-6];
      puVar10 = puVar10 + -10;
      param_3[1] = *puVar9;
      *param_3 = uVar12;
      if (uVar19 == 0) break;
    } while( true );
  }
  goto code_r0x020120e0;
code_r0x02011668:
  *(int *)(puVar10 + -4) = *(int *)(puVar10 + -4) + 1;
  *(undefined4 *)((long)puVar10 + -0xc) = 1;
code_r0x0201207c:
  puVar15 = (uint *)((long)puVar20 + 1);
  uVar13 = 0;
  puVar20 = puVar1;
  if (puVar15 == puVar1) goto code_r0x020120e0;
  goto code_r0x020112a4;
code_r0x020120e0:
  uVar12 = 0;
  puVar15 = (uint *)((long)puVar20 + 1);
  param_3[9] = param_3[3];
  param_3[8] = param_3[2];
  param_3[7] = param_3[1];
  param_3[6] = *param_3;
  goto code_r0x02012170;
}

// ==== Aska::ASON::PushBackWorkBuffer(signed char*, unsigned long, bool)
// vaddr 0x1f121a4 | ghidra 0x20121a4 | size 120 | symbol _ZN4Aska4ASON18PushBackWorkBufferEPamb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska4ASON18PushBackWorkBufferEPamb
               (long param_1,undefined8 param_2,long param_3,byte param_4)

{
  undefined8 uStack_50;
  long lStack_48;
  undefined8 uStack_40;
  byte bStack_38;
  undefined8 uStack_30;
  undefined1 *puStack_28;
  
  puStack_28 = (undefined1 *)&uStack_50;
  bStack_38 = param_4 & 1;
  uStack_40 = 0;
  uStack_30 = 1;
  uStack_50 = param_2;
  lStack_48 = param_3;
  Aska::TArrayIterator<Aska::TDynamicArray<Aska::ASON::WorkBufferContext, Aska::TAllocator<Aska::ASON::WorkBufferContext> > > Aska::TDynamicArray<Aska::ASON::WorkBufferContext, Aska::TAllocator<Aska::ASON::WorkBufferContext> >::Insert_<Aska::Memory::TUninitializedFillN<Aska::ASON::WorkBufferContext> >(Aska::ASON::WorkBufferContext const*, unsigned long, Aska::Memory::TUninitializedFillN<Aska::ASON::WorkBufferContext> const&)(param_1 + 0x20,*(undefined8 *)(param_1 + 0x30),1,&uStack_30);
  *(long *)(param_1 + 0x48) = *(long *)(param_1 + 0x30) + -0x20;
  *(long *)(param_1 + 0x50) = *(long *)(param_1 + 0x50) + param_3;
  *(short *)(param_1 + 0x58) = *(short *)(param_1 + 0x58) + 1;
  return;
}

// ==== Aska::ASON::Malloc(unsigned long)
// vaddr 0x1f1221c | ghidra 0x201221c | size 224 | symbol _ZN4Aska4ASON6MallocEm | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska4ASON6MallocEm(long param_1,long param_2)

{
  ulong uVar1;
  undefined *puVar2;
  long lVar3;
  undefined8 uVar4;
  long *plVar5;
  long lVar6;
  long lStack_70;
  long lStack_68;
  undefined8 uStack_60;
  undefined1 uStack_58;
  undefined8 uStack_50;
  undefined1 *puStack_48;
  
  puVar2 = PTR__ZSt7nothrow_02cb9a80;
  if (param_2 != 0) {
    plVar5 = *(long **)(param_1 + 0x48);
    while( true ) {
      lVar3 = plVar5[2];
      uVar1 = lVar3 + (param_2 + 3U & 0xfffffffffffffffc);
      if (uVar1 <= (ulong)plVar5[1]) {
        plVar5[2] = uVar1;
        lVar3 = *plVar5 + lVar3;
        if (lVar3 != 0) {
          return lVar3;
        }
      }
      lVar6 = *(long *)(param_1 + 0x50);
      lVar3 = operator new[](unsigned long, std::nothrow_t const&)(lVar6,puVar2);
      if (lVar3 == 0) break;
      uStack_58 = 1;
      uStack_60 = 0;
      uStack_50 = 1;
      lStack_70 = lVar3;
      lStack_68 = lVar6;
      puStack_48 = (undefined1 *)&lStack_70;
      Aska::TArrayIterator<Aska::TDynamicArray<Aska::ASON::WorkBufferContext, Aska::TAllocator<Aska::ASON::WorkBufferContext> > > Aska::TDynamicArray<Aska::ASON::WorkBufferContext, Aska::TAllocator<Aska::ASON::WorkBufferContext> >::Insert_<Aska::Memory::TUninitializedFillN<Aska::ASON::WorkBufferContext> >(Aska::ASON::WorkBufferContext const*, unsigned long, Aska::Memory::TUninitializedFillN<Aska::ASON::WorkBufferContext> const&)(param_1 + 0x20,*(undefined8 *)(param_1 + 0x30),1,&uStack_50);
      plVar5 = (long *)(*(long *)(param_1 + 0x30) + -0x20);
      *(long **)(param_1 + 0x48) = plVar5;
      *(long *)(param_1 + 0x50) = *(long *)(param_1 + 0x50) + lVar6;
      *(short *)(param_1 + 0x58) = *(short *)(param_1 + 0x58) + 1;
    }
    uVar4 = Aska::Global::GetAvailableMemoryManager()();
    Aska::MemoryManager::CalcFreeSize(bool)(uVar4,0);
  }
  return 0;
}

// ==== Aska::ASON::RelocateAValueRef(Aska::ASON::AValue*, Aska::TDynamicArray<Aska::ASON::WorkBufferContext, Aska::TAllocator<Aska::ASON::WorkBufferContext> > const&, bool)
// vaddr 0x1f122fc | ghidra 0x20122fc | size 1136 | symbol _ZN4Aska4ASON17RelocateAValueRefEPNS0_6AValueERKNS_13TDynamicArrayINS0_17WorkBufferContextENS_10TAllocatorIS4_EEEEb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska4ASON17RelocateAValueRefEPNS0_6AValueERKNS_13TDynamicArrayINS0_17WorkBufferContextENS_10TAllocatorIS4_EEEEb
               (long *param_1,long param_2,undefined4 *param_3,long param_4,uint param_5)

{
  ulong *puVar1;
  uint uVar2;
  int iVar3;
  ushort uVar4;
  long lVar5;
  long lVar6;
  undefined8 *puVar7;
  undefined8 *puVar8;
  ulong uVar9;
  ulong uVar10;
  long lVar11;
  undefined8 *puVar12;
  undefined8 uVar13;
  long lStack_58;
  
  if (param_3 != (undefined4 *)0x0) {
    switch(*param_3) {
    case 5:
      iVar3 = param_3[6];
      if (iVar3 != 0) {
        uVar10 = *(ulong *)(param_3 + 2);
        puVar1 = (ulong *)(*(long *)(param_4 + 8) + (ulong)*(ushort *)(param_3 + 7) * 0x20);
        uVar9 = *puVar1;
        if ((uVar10 < uVar9) || (puVar1[1] + uVar9 <= uVar10)) {
          if ((param_5 & 1) == 0) goto code_r0x020124f4;
          lVar5 = Aska::ASON::Malloc(unsigned long)(param_2,iVar3);
          if (lVar5 != 0) {
            if (*(long *)(param_3 + 2) == 0) {
              memset(lVar5,0,iVar3);
            }
            else {
              memcpy(lVar5,*(long *)(param_3 + 2),iVar3);
            }
            goto code_r0x02012394;
          }
code_r0x02012708:
          lStack_58 = -0x3bf;
          *(undefined8 *)(param_2 + 0x80) = 0xfffffffffffffc41;
          goto code_r0x020126e8;
        }
        lVar5 = (uVar10 - uVar9) +
                *(long *)(*(long *)(param_2 + 0x28) + (ulong)*(ushort *)(param_3 + 7) * 0x20);
code_r0x02012394:
        *(long *)(param_3 + 2) = lVar5;
code_r0x020124f4:
        uVar9 = *(ulong *)(param_3 + 4);
        if (uVar9 != 0) {
          puVar1 = (ulong *)(*(long *)(param_4 + 8) +
                            (ulong)*(ushort *)((long)param_3 + 0x1e) * 0x20);
          uVar10 = *puVar1;
          if ((uVar10 <= uVar9) && (uVar9 < puVar1[1] + uVar10)) {
            lStack_58 = 0;
            *(ulong *)(param_3 + 4) =
                 (uVar9 - uVar10) +
                 *(long *)(*(long *)(param_2 + 0x28) +
                          (ulong)*(ushort *)((long)param_3 + 0x1e) * 0x20);
            goto code_r0x020126e8;
          }
          if ((param_5 & 1) != 0) {
            lVar5 = strlen();
            lVar5 = Aska::ASON::Malloc(unsigned long)(param_2,lVar5 + 1);
            if (lVar5 != 0) {
              lVar11 = *(long *)(param_3 + 4);
              lVar6 = strlen(lVar11);
              if (lVar11 == 0) {
                memset(lVar5,0,lVar6 + 1);
              }
              else {
                memcpy(lVar5,lVar11);
              }
              lStack_58 = 0;
              *(long *)(param_3 + 4) = lVar5;
              goto code_r0x020126e8;
            }
            goto code_r0x02012708;
          }
        }
      }
      break;
    case 6:
      uVar2 = param_3[4];
      if (uVar2 != 0) {
        puVar12 = *(undefined8 **)(param_3 + 2);
        puVar7 = (undefined8 *)(*(long *)(param_4 + 8) + (ulong)*(ushort *)(param_3 + 5) * 0x20);
        puVar8 = (undefined8 *)*puVar7;
        if ((puVar12 < puVar8) || ((undefined8 *)(puVar7[1] + (long)puVar8) <= puVar12)) {
          if ((param_5 & 1) != 0) {
            puVar12 = (undefined8 *)Aska::ASON::Malloc(unsigned long)(param_2,0x20);
            if (puVar12 == (undefined8 *)0x0) goto code_r0x02012708;
            puVar7 = *(undefined8 **)(param_3 + 2);
            if (puVar7 == (undefined8 *)0x0) {
              puVar12[1] = 0;
              *puVar12 = 0;
              puVar12[3] = 0;
              puVar12[2] = 0;
            }
            else {
              uVar13 = puVar7[2];
              puVar12[3] = puVar7[3];
              puVar12[2] = uVar13;
              uVar13 = *puVar7;
              puVar12[1] = puVar7[1];
              *puVar12 = uVar13;
            }
            goto code_r0x020123e0;
          }
        }
        else {
          puVar12 = (undefined8 *)
                    ((long)puVar12 +
                    (*(long *)(*(long *)(param_2 + 0x28) + (ulong)*(ushort *)(param_3 + 5) * 0x20) -
                    (long)puVar8));
code_r0x020123e0:
          *(undefined8 **)(param_3 + 2) = puVar12;
        }
        _ZN4Aska4ASON17RelocateAValueRefEPNS0_6AValueERKNS_13TDynamicArrayINS0_17WorkBufferContextENS_10TAllocatorIS4_EEEEb
                  (&lStack_58,param_2,puVar12,param_4,param_5 & 1);
        if (-1 < lStack_58) {
          uVar9 = 0;
          lVar5 = 0x20;
          do {
            uVar9 = uVar9 + 1;
            if (uVar2 <= uVar9) goto code_r0x020126e4;
            lVar6 = *(long *)(param_3 + 2) + lVar5;
            lVar5 = lVar5 + 0x20;
            _ZN4Aska4ASON17RelocateAValueRefEPNS0_6AValueERKNS_13TDynamicArrayINS0_17WorkBufferContextENS_10TAllocatorIS4_EEEEb
                      (&lStack_58,param_2,lVar6,param_4,param_5 & 1);
          } while (-1 < lStack_58);
        }
        goto code_r0x020126e8;
      }
      break;
    case 7:
      uVar2 = param_3[4];
      if (uVar2 != 0) {
        puVar12 = *(undefined8 **)(param_3 + 2);
        puVar7 = (undefined8 *)(*(long *)(param_4 + 8) + (ulong)*(ushort *)(param_3 + 5) * 0x20);
        puVar8 = (undefined8 *)*puVar7;
        if ((puVar12 < puVar8) || ((undefined8 *)(puVar7[1] + (long)puVar8) <= puVar12)) {
          if ((param_5 & 1) != 0) {
            puVar12 = (undefined8 *)Aska::ASON::Malloc(unsigned long)(param_2,0x40);
            if (puVar12 == (undefined8 *)0x0) goto code_r0x02012708;
            puVar7 = *(undefined8 **)(param_3 + 2);
            if (puVar7 == (undefined8 *)0x0) {
              puVar12[5] = 0;
              puVar12[4] = 0;
              puVar12[7] = 0;
              puVar12[6] = 0;
              puVar12[1] = 0;
              *puVar12 = 0;
              puVar12[3] = 0;
              puVar12[2] = 0;
            }
            else {
              uVar13 = puVar7[6];
              puVar12[7] = puVar7[7];
              puVar12[6] = uVar13;
              uVar13 = puVar7[4];
              puVar12[5] = puVar7[5];
              puVar12[4] = uVar13;
              uVar13 = puVar7[2];
              puVar12[3] = puVar7[3];
              puVar12[2] = uVar13;
              uVar13 = *puVar7;
              puVar12[1] = puVar7[1];
              *puVar12 = uVar13;
            }
            goto code_r0x0201242c;
          }
        }
        else {
          puVar12 = (undefined8 *)
                    ((long)puVar12 +
                    (*(long *)(*(long *)(param_2 + 0x28) + (ulong)*(ushort *)(param_3 + 5) * 0x20) -
                    (long)puVar8));
code_r0x0201242c:
          *(undefined8 **)(param_3 + 2) = puVar12;
        }
        _ZN4Aska4ASON17RelocateAValueRefEPNS0_6AValueERKNS_13TDynamicArrayINS0_17WorkBufferContextENS_10TAllocatorIS4_EEEEb
                  (&lStack_58,param_2,puVar12,param_4,param_5 & 1);
        if (-1 < lStack_58) {
          uVar9 = 0;
          lVar5 = 0x40;
          do {
            _ZN4Aska4ASON17RelocateAValueRefEPNS0_6AValueERKNS_13TDynamicArrayINS0_17WorkBufferContextENS_10TAllocatorIS4_EEEEb
                      (&lStack_58,param_2,(long)puVar12 + lVar5 + -0x20,param_4,param_5 & 1);
            if (lStack_58 < 0) break;
            uVar9 = uVar9 + 1;
            if (uVar2 <= uVar9) goto code_r0x020126e4;
            puVar12 = *(undefined8 **)(param_3 + 2);
            lVar6 = (long)puVar12 + lVar5;
            lVar5 = lVar5 + 0x40;
            _ZN4Aska4ASON17RelocateAValueRefEPNS0_6AValueERKNS_13TDynamicArrayINS0_17WorkBufferContextENS_10TAllocatorIS4_EEEEb
                      (&lStack_58,param_2,lVar6,param_4,param_5 & 1);
          } while (-1 < lStack_58);
        }
        goto code_r0x020126e8;
      }
      break;
    case 8:
      iVar3 = param_3[4];
      if (iVar3 != 0) {
        uVar4 = *(ushort *)(param_3 + 5);
code_r0x02012450:
        uVar10 = *(ulong *)(param_3 + 2);
        puVar1 = (ulong *)(*(long *)(param_4 + 8) + (ulong)uVar4 * 0x20);
        uVar9 = *puVar1;
        if ((uVar9 <= uVar10) && (uVar10 < puVar1[1] + uVar9)) {
          lStack_58 = 0;
          *(ulong *)(param_3 + 2) =
               (uVar10 - uVar9) + *(long *)(*(long *)(param_2 + 0x28) + (ulong)uVar4 * 0x20);
          goto code_r0x020126e8;
        }
        if ((param_5 & 1) != 0) {
          lVar5 = Aska::ASON::Malloc(unsigned long)(param_2,iVar3);
          if (lVar5 != 0) {
            if (*(long *)(param_3 + 2) == 0) {
              memset(lVar5,0,iVar3);
            }
            else {
              memcpy(lVar5,*(long *)(param_3 + 2),iVar3);
            }
            lStack_58 = 0;
            *(long *)(param_3 + 2) = lVar5;
            goto code_r0x020126e8;
          }
          goto code_r0x02012708;
        }
      }
      break;
    case 9:
      iVar3 = param_3[4];
      if (iVar3 != 0) {
        uVar4 = *(ushort *)((long)param_3 + 0x16);
        goto code_r0x02012450;
      }
    }
  }
code_r0x020126e4:
  lStack_58 = 0;
code_r0x020126e8:
  *param_1 = lStack_58;
  return;
}

// ==== Aska::ASON::ClearWorkBuffer()
// vaddr 0x1f1276c | ghidra 0x201276c | size 180 | symbol _ZN4Aska4ASON15ClearWorkBufferEv | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska4ASON15ClearWorkBufferEv(long param_1)

{
  undefined8 uVar1;
  undefined8 uVar2;
  long lVar3;
  undefined8 uVar4;
  ulong uVar5;
  long lVar6;
  long lVar7;
  
  lVar3 = *(long *)(param_1 + 0x28);
  lVar7 = *(long *)(param_1 + 0x30);
  uVar5 = lVar7 - lVar3 >> 5;
  if (1 < uVar5) {
    lVar6 = uVar5 - 1;
    do {
      if (*(char *)(lVar7 + -8) != '\0') {
        if (*(long *)(lVar7 + -0x20) != 0) {
          operator delete[](void*)();
        }
        *(undefined1 *)(lVar7 + -8) = 0;
      }
      *(undefined8 *)(lVar7 + -0x18) = 0;
      *(undefined8 *)(lVar7 + -0x10) = 0;
      *(long *)(lVar7 + -0x20) = 0;
      lVar3 = *(long *)(param_1 + 0x28);
      lVar7 = lVar3;
      if (lVar3 != *(long *)(param_1 + 0x30)) {
        lVar7 = *(long *)(param_1 + 0x30) + -0x20;
        *(long *)(param_1 + 0x30) = lVar7;
      }
      lVar6 = lVar6 + -1;
    } while (lVar6 != 0);
  }
  *(undefined8 *)(lVar3 + 0x10) = 0;
  *(long *)(param_1 + 0x48) = lVar3;
  uVar4 = *(undefined8 *)(lVar3 + 8);
  *(undefined2 *)(param_1 + 0x58) = 0;
  *(undefined8 *)(param_1 + 0x10) = 0;
  *(undefined8 *)(param_1 + 0x18) = 0;
  *(undefined8 *)(param_1 + 0x50) = uVar4;
  *(undefined8 *)(param_1 + 8) = 0;
  uVar2 = Aska::ASON::Malloc(unsigned long)(param_1,0x200);
  uVar1 = _UNK_0296e148;
  uVar4 = _UNK_0296e140;
  *(undefined8 *)(param_1 + 8) = uVar2;
  *(undefined8 *)(param_1 + 0x18) = uVar1;
  *(undefined8 *)(param_1 + 0x10) = uVar4;
  return;
}

// ==== Aska::ASON::TemporaryMalloc(unsigned long)
// vaddr 0x1f12820 | ghidra 0x2012820 | size 68 | symbol _ZN4Aska4ASON15TemporaryMallocEm | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska4ASON15TemporaryMallocEm(long param_1,long param_2)

{
  ulong uVar1;
  long lVar2;
  
  lVar2 = *(long *)(param_1 + 0x18);
  uVar1 = lVar2 + (param_2 + 3U & 0xfffffffffffffffc);
  if (uVar1 <= *(ulong *)(param_1 + 0x10)) {
    *(ulong *)(param_1 + 0x18) = uVar1;
    lVar2 = *(long *)(param_1 + 8) + lVar2;
    if (lVar2 != 0) {
      return lVar2;
    }
  }
  lVar2 = (*(code *)PTR__ZnamRKSt9nothrow_t_02cb0738)(param_2,PTR__ZSt7nothrow_02cb9a80);
  return lVar2;
}

// ==== Aska::ASON::TemporaryFree(void*)
// vaddr 0x1f12864 | ghidra 0x2012864 | size 48 | symbol _ZN4Aska4ASON13TemporaryFreeEPv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska4ASON13TemporaryFreeEPv(long param_1,ulong param_2)

{
  if (param_2 != 0) {
    if ((param_2 < *(ulong *)(param_1 + 8)) ||
       (*(long *)(param_1 + 0x10) + *(ulong *)(param_1 + 8) <= param_2)) {
      (*(code *)PTR__ZdaPv_02cb5db8)(param_2);
      return;
    }
    *(undefined8 *)(param_1 + 0x18) = 0;
  }
  return;
}

// ==== Aska::ASON::AValue2String(Aska::ASON::AValue const*, char**)
// vaddr 0x1f12894 | ghidra 0x2012894 | size 788 | symbol _ZN4Aska4ASON13AValue2StringEPKNS0_6AValueEPPc | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska4ASON13AValue2StringEPKNS0_6AValueEPPc
               (undefined8 *param_1,long param_2,int *param_3,undefined8 *param_4)

{
  ulong uVar1;
  uint *puVar2;
  ulong uVar3;
  ulong uVar4;
  long lVar5;
  undefined *puVar6;
  undefined8 uVar7;
  undefined4 *puVar8;
  ulong uVar9;
  
  puVar8 = (undefined4 *)0x0;
  switch(*param_3) {
  case 0:
    if (*(long *)PTR__ZN4Aska10JsonParser16s_pMemoryManagerE_02cc46b0 == 0) {
      puVar8 = (undefined4 *)operator new[](unsigned long, std::nothrow_t const&)(5,PTR__ZSt7nothrow_02cb9a80);
    }
    else {
      puVar8 = (undefined4 *)
               Aska::MemoryManager::Malloc(unsigned long)(*(long *)PTR__ZN4Aska10JsonParser16s_pMemoryManagerE_02cc46b0,5);
    }
    if (puVar8 != (undefined4 *)0x0) {
      *puVar8 = 0x6c6c756e;
      *(undefined1 *)(puVar8 + 1) = 0;
      goto code_r0x02012b7c;
    }
    break;
  case 1:
    lVar5 = *(long *)PTR__ZN4Aska10JsonParser16s_pMemoryManagerE_02cc46b0;
    if ((char)param_3[2] == '\0') {
      if (lVar5 == 0) {
        puVar8 = (undefined4 *)operator new[](unsigned long, std::nothrow_t const&)(6,PTR__ZSt7nothrow_02cb9a80);
      }
      else {
        puVar8 = (undefined4 *)Aska::MemoryManager::Malloc(unsigned long)(lVar5,6);
      }
      if (puVar8 != (undefined4 *)0x0) {
        *(undefined2 *)(puVar8 + 1) = 0x65;
        lVar5 = 5;
        *puVar8 = 0x736c6166;
        goto code_r0x02012b78;
      }
    }
    else {
      if (lVar5 == 0) {
        puVar8 = (undefined4 *)operator new[](unsigned long, std::nothrow_t const&)(5,PTR__ZSt7nothrow_02cb9a80);
      }
      else {
        puVar8 = (undefined4 *)Aska::MemoryManager::Malloc(unsigned long)(lVar5,5);
      }
      if (puVar8 != (undefined4 *)0x0) {
        *puVar8 = 0x65757274;
        lVar5 = 4;
        *(undefined1 *)(puVar8 + 1) = 0;
code_r0x02012b78:
        *(undefined1 *)((long)puVar8 + lVar5) = 0;
        goto code_r0x02012b7c;
      }
    }
    break;
  case 2:
    if (*(long *)PTR__ZN4Aska10JsonParser16s_pMemoryManagerE_02cc46b0 == 0) {
      puVar8 = (undefined4 *)operator new[](unsigned long, std::nothrow_t const&)(0x41,PTR__ZSt7nothrow_02cb9a80);
    }
    else {
      puVar8 = (undefined4 *)
               Aska::MemoryManager::Malloc(unsigned long)(*(long *)PTR__ZN4Aska10JsonParser16s_pMemoryManagerE_02cc46b0,0x41);
    }
    if (puVar8 != (undefined4 *)0x0) {
      uVar7 = *(undefined8 *)(param_3 + 2);
      puVar6 = &UNK_029df1a7/*"%llu"*/;
code_r0x02012acc:
      __aska_snprintf_s(char*, unsigned long, unsigned long, char const*, ...)(puVar8,0x40,0xffffffffffffffff,puVar6,uVar7);
      goto code_r0x02012b7c;
    }
    break;
  case 3:
    if (*(long *)PTR__ZN4Aska10JsonParser16s_pMemoryManagerE_02cc46b0 == 0) {
      puVar8 = (undefined4 *)operator new[](unsigned long, std::nothrow_t const&)(0x41,PTR__ZSt7nothrow_02cb9a80);
    }
    else {
      puVar8 = (undefined4 *)
               Aska::MemoryManager::Malloc(unsigned long)(*(long *)PTR__ZN4Aska10JsonParser16s_pMemoryManagerE_02cc46b0,0x41);
    }
    if (puVar8 != (undefined4 *)0x0) {
      uVar7 = *(undefined8 *)(param_3 + 2);
      puVar6 = &UNK_029dd0e4/*"%lld"*/;
      goto code_r0x02012acc;
    }
    break;
  case 4:
    if (*(long *)PTR__ZN4Aska10JsonParser16s_pMemoryManagerE_02cc46b0 == 0) {
      puVar8 = (undefined4 *)operator new[](unsigned long, std::nothrow_t const&)(0x41,PTR__ZSt7nothrow_02cb9a80);
    }
    else {
      puVar8 = (undefined4 *)
               Aska::MemoryManager::Malloc(unsigned long)(*(long *)PTR__ZN4Aska10JsonParser16s_pMemoryManagerE_02cc46b0,0x41);
    }
    if (puVar8 != (undefined4 *)0x0) {
      __aska_snprintf_s(char*, unsigned long, unsigned long, char const*, ...)(*(undefined8 *)(param_3 + 2),puVar8,0x40,0xffffffffffffffff,&UNK_0296e5a8/*"%+.6f"*/);
      goto code_r0x02012b7c;
    }
    break;
  case 5:
  case 8:
  case 9:
    puVar2 = (uint *)(param_3 + 6);
    if (*param_3 != 5) {
      puVar2 = (uint *)(param_3 + 4);
    }
    uVar9 = (ulong)*puVar2;
    uVar7 = *(undefined8 *)(param_3 + 2);
    if (*(long *)PTR__ZN4Aska10JsonParser16s_pMemoryManagerE_02cc46b0 == 0) {
      puVar8 = (undefined4 *)operator new[](unsigned long, std::nothrow_t const&)(uVar9 + 1,PTR__ZSt7nothrow_02cb9a80);
    }
    else {
      puVar8 = (undefined4 *)Aska::MemoryManager::Malloc(unsigned long)();
    }
    if (puVar8 != (undefined4 *)0x0) {
      uVar4 = strlen(uVar7);
      uVar1 = uVar4 + 1;
      if (uVar1 != uVar9) {
        uVar4 = uVar4 + 1;
      }
      uVar3 = uVar9;
      if (uVar1 <= uVar9) {
        uVar3 = uVar4;
      }
      if (uVar9 < uVar3) {
        raise(5);
      }
      else {
        strncpy(puVar8,uVar7,uVar3);
        if (uVar9 <= uVar1) {
          *(undefined1 *)((long)puVar8 + uVar3) = 0;
        }
      }
      *(undefined1 *)((long)puVar8 + uVar9) = 0;
      goto code_r0x02012b7c;
    }
    break;
  default:
code_r0x02012b7c:
    uVar7 = 0;
    *param_4 = puVar8;
    goto code_r0x02012b90;
  }
  uVar7 = 0xfffffffffffffc41;
  *(undefined8 *)(param_2 + 0x80) = 0xfffffffffffffc41;
code_r0x02012b90:
  *param_1 = uVar7;
  return;
}

// ==== Aska::ASON::GetClassID(int) const
// vaddr 0x1f12ba8 | ghidra 0x2012ba8 | size 44 | symbol _ZNK4Aska4ASON10GetClassIDEi | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska4ASON10GetClassIDEi(undefined8 param_1,int param_2)

{
  undefined8 uVar1;
  undefined8 uVar2;
  
  uVar2 = 0xf000f19e;
  if (param_2 != 1) {
    uVar2 = 0xf000;
  }
  uVar1 = 0xf000f19ef18f;
  if (param_2 != 0) {
    uVar1 = uVar2;
  }
  return uVar1;
}

// ==== long Aska::ASON::PackValue_u64<true>(unsigned char*, unsigned long, unsigned long) const
// vaddr 0x1f13524 | ghidra 0x2013524 | size 376 | symbol _ZNK4Aska4ASON13PackValue_u64ILb1EEElPhmm | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZNK4Aska4ASON13PackValue_u64ILb1EEElPhmm
          (long param_1,undefined1 *param_2,ulong param_3,ulong param_4)

{
  uint uVar1;
  ulong uVar2;
  int iVar3;
  uint uVar4;
  
  uVar4 = (uint)param_3;
  if (param_3 < 0x100) {
    if (param_3 < 0x80) {
      if (param_4 != 0) {
        *param_2 = (char)param_3;
        return 1;
      }
    }
    else if (1 < param_4) {
      param_2[1] = (char)param_3;
      *param_2 = 0xcc;
      return 2;
    }
  }
  else if (param_3 >> 0x10 == 0) {
    if (2 < param_4) {
      if (((*PTR__ZGVZN4Aska7Machine6_HTONSEtE9kMyEndian_02cc0910 & 1) == 0) &&
         (iVar3 = __cxa_guard_acquire(PTR__ZGVZN4Aska7Machine6_HTONSEtE9kMyEndian_02cc0910), iVar3 != 0)
         ) {
        *(undefined4 *)PTR__ZZN4Aska7Machine6_HTONSEtE9kMyEndian_02cbc7a8 = 1;
        __cxa_guard_release(PTR__ZGVZN4Aska7Machine6_HTONSEtE9kMyEndian_02cc0910);
      }
      iVar3 = *(int *)PTR__ZZN4Aska7Machine6_HTONSEtE9kMyEndian_02cbc7a8;
      *param_2 = 0xcd;
      if (iVar3 != 2) {
        uVar4 = ((uVar4 & 0xff00ff00) >> 8 | (uVar4 & 0xff00ff) << 8) & 0xffff;
      }
      *(short *)(param_2 + 1) = (short)uVar4;
      return 3;
    }
  }
  else if (param_3 >> 0x20 == 0) {
    if (4 < param_4) {
      if (((*PTR__ZGVZN4Aska7Machine6_HTONLEjE9kMyEndian_02cbe508 & 1) == 0) &&
         (iVar3 = __cxa_guard_acquire(PTR__ZGVZN4Aska7Machine6_HTONLEjE9kMyEndian_02cbe508), iVar3 != 0)
         ) {
        *(undefined4 *)PTR__ZZN4Aska7Machine6_HTONLEjE9kMyEndian_02cc0b50 = 1;
        __cxa_guard_release(PTR__ZGVZN4Aska7Machine6_HTONLEjE9kMyEndian_02cbe508);
      }
      uVar1 = (uVar4 & 0xff00ff00) >> 8 | (uVar4 & 0xff00ff) << 8;
      iVar3 = *(int *)PTR__ZZN4Aska7Machine6_HTONLEjE9kMyEndian_02cc0b50;
      *param_2 = 0xce;
      if (iVar3 != 2) {
        uVar4 = uVar1 >> 0x10 | uVar1 << 0x10;
      }
      *(uint *)(param_2 + 1) = uVar4;
      return 5;
    }
  }
  else if (8 < param_4) {
    uVar2 = (param_3 & 0xff00ff00ff00ff00) >> 8 | (param_3 & 0xff00ff00ff00ff) << 8;
    uVar2 = (uVar2 & 0xffff0000ffff0000) >> 0x10 | (uVar2 & 0xffff0000ffff) << 0x10;
    *(ulong *)(param_2 + 1) = uVar2 >> 0x20 | uVar2 << 0x20;
    *param_2 = 0xcf;
    return 9;
  }
  *(undefined8 *)(param_1 + 0x80) = 0xfffffffffffffc3f;
  return 0xfffffffffffffc3f;
}

// ==== long Aska::ASON::PackValue_s64<true>(unsigned char*, long, unsigned long) const
// vaddr 0x1f1369c | ghidra 0x201369c | size 632 | symbol _ZNK4Aska4ASON13PackValue_s64ILb1EEElPhlm | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZNK4Aska4ASON13PackValue_s64ILb1EEElPhlm
          (long param_1,undefined1 *param_2,ulong param_3,ulong param_4)

{
  int iVar1;
  undefined1 uVar2;
  ulong uVar3;
  uint uVar4;
  uint uVar5;
  
  uVar5 = (uint)param_3;
  if ((long)param_3 < -0x20) {
    if ((long)param_3 < -0x8000) {
      if ((long)param_3 < -0x80000000) {
        if (8 < param_4) {
          uVar3 = (param_3 & 0xff00ff00ff00ff00) >> 8 | (param_3 & 0xff00ff00ff00ff) << 8;
          uVar3 = (uVar3 & 0xffff0000ffff0000) >> 0x10 | (uVar3 & 0xffff0000ffff) << 0x10;
          uVar3 = uVar3 >> 0x20 | uVar3 << 0x20;
          uVar2 = 0xd3;
code_r0x02013904:
          *(ulong *)(param_2 + 1) = uVar3;
          *param_2 = uVar2;
          return 9;
        }
      }
      else if (4 < param_4) {
        if (((*PTR__ZGVZN4Aska7Machine6_HTONLEjE9kMyEndian_02cbe508 & 1) == 0) &&
           (iVar1 = __cxa_guard_acquire(PTR__ZGVZN4Aska7Machine6_HTONLEjE9kMyEndian_02cbe508),
           iVar1 != 0)) {
          *(undefined4 *)PTR__ZZN4Aska7Machine6_HTONLEjE9kMyEndian_02cc0b50 = 1;
          __cxa_guard_release(PTR__ZGVZN4Aska7Machine6_HTONLEjE9kMyEndian_02cbe508);
        }
        uVar4 = (uVar5 & 0xff00ff00) >> 8 | (uVar5 & 0xff00ff) << 8;
        uVar4 = uVar4 >> 0x10 | uVar4 << 0x10;
        uVar2 = 0xd2;
code_r0x0201384c:
        if (*(int *)PTR__ZZN4Aska7Machine6_HTONLEjE9kMyEndian_02cc0b50 != 2) {
          uVar5 = uVar4;
        }
        *param_2 = uVar2;
        *(uint *)(param_2 + 1) = uVar5;
        return 5;
      }
    }
    else if ((long)param_3 < -0x80) {
      if (2 < param_4) {
        if (((*PTR__ZGVZN4Aska7Machine6_HTONSEtE9kMyEndian_02cc0910 & 1) == 0) &&
           (iVar1 = __cxa_guard_acquire(PTR__ZGVZN4Aska7Machine6_HTONSEtE9kMyEndian_02cc0910),
           iVar1 != 0)) {
          *(undefined4 *)PTR__ZZN4Aska7Machine6_HTONSEtE9kMyEndian_02cbc7a8 = 1;
          __cxa_guard_release(PTR__ZGVZN4Aska7Machine6_HTONSEtE9kMyEndian_02cc0910);
        }
        uVar4 = (uVar5 & 0xff00ff00) >> 8 | (uVar5 & 0xff00ff) << 8;
        uVar2 = 0xd1;
code_r0x020138bc:
        if (*(int *)PTR__ZZN4Aska7Machine6_HTONSEtE9kMyEndian_02cbc7a8 != 2) {
          uVar5 = uVar4 & 0xffff;
        }
        *param_2 = uVar2;
        *(short *)(param_2 + 1) = (short)uVar5;
        return 3;
      }
    }
    else if (1 < param_4) {
      uVar2 = 0xd0;
code_r0x020137dc:
      param_2[1] = (char)param_3;
      *param_2 = uVar2;
      return 2;
    }
  }
  else if ((long)param_3 < 0x80) {
    if (param_4 != 0) {
      *param_2 = (char)param_3;
      return 1;
    }
  }
  else if ((long)param_3 < 0x10000) {
    if ((long)param_3 < 0x100) {
      if (1 < param_4) {
        uVar2 = 0xcc;
        goto code_r0x020137dc;
      }
    }
    else if (2 < param_4) {
      if (((*PTR__ZGVZN4Aska7Machine6_HTONSEtE9kMyEndian_02cc0910 & 1) == 0) &&
         (iVar1 = __cxa_guard_acquire(PTR__ZGVZN4Aska7Machine6_HTONSEtE9kMyEndian_02cc0910), iVar1 != 0)
         ) {
        *(undefined4 *)PTR__ZZN4Aska7Machine6_HTONSEtE9kMyEndian_02cbc7a8 = 1;
        __cxa_guard_release(PTR__ZGVZN4Aska7Machine6_HTONSEtE9kMyEndian_02cc0910);
      }
      uVar4 = (uVar5 & 0xff00ff00) >> 8 | (uVar5 & 0xff00ff) << 8;
      uVar2 = 0xcd;
      goto code_r0x020138bc;
    }
  }
  else if ((long)param_3 < 0x100000000) {
    if (4 < param_4) {
      if (((*PTR__ZGVZN4Aska7Machine6_HTONLEjE9kMyEndian_02cbe508 & 1) == 0) &&
         (iVar1 = __cxa_guard_acquire(PTR__ZGVZN4Aska7Machine6_HTONLEjE9kMyEndian_02cbe508), iVar1 != 0)
         ) {
        *(undefined4 *)PTR__ZZN4Aska7Machine6_HTONLEjE9kMyEndian_02cc0b50 = 1;
        __cxa_guard_release(PTR__ZGVZN4Aska7Machine6_HTONLEjE9kMyEndian_02cbe508);
      }
      uVar4 = (uVar5 & 0xff00ff00) >> 8 | (uVar5 & 0xff00ff) << 8;
      uVar4 = uVar4 >> 0x10 | uVar4 << 0x10;
      uVar2 = 0xce;
      goto code_r0x0201384c;
    }
  }
  else if (8 < param_4) {
    uVar3 = (param_3 & 0xff00ff00ff00ff00) >> 8 | (param_3 & 0xff00ff00ff00ff) << 8;
    uVar3 = (uVar3 & 0xffff0000ffff0000) >> 0x10 | (uVar3 & 0xffff0000ffff) << 0x10;
    uVar3 = uVar3 >> 0x20 | uVar3 << 0x20;
    uVar2 = 0xcf;
    goto code_r0x02013904;
  }
  *(undefined8 *)(param_1 + 0x80) = 0xfffffffffffffc3f;
  return 0xfffffffffffffc3f;
}

// ==== long Aska::ASON::PackValue_str<true>(unsigned char*, unsigned long, unsigned long) const
// vaddr 0x1f13914 | ghidra 0x2013914 | size 344 | symbol _ZNK4Aska4ASON13PackValue_strILb1EEElPhmm | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZNK4Aska4ASON13PackValue_strILb1EEElPhmm(long param_1,byte *param_2,ulong param_3,ulong param_4)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  
  uVar3 = (uint)param_3;
  if (param_3 < 0x20) {
    if (param_4 != 0) {
      *param_2 = (byte)param_3 | 0xa0;
      return 1;
    }
  }
  else if (param_3 < 0x100) {
    if (1 < param_4) {
      param_2[1] = (byte)param_3;
      *param_2 = 0xd9;
      return 2;
    }
  }
  else if (param_3 >> 0x10 == 0) {
    if (2 < param_4) {
      if (((*PTR__ZGVZN4Aska7Machine6_HTONSEtE9kMyEndian_02cc0910 & 1) == 0) &&
         (iVar2 = __cxa_guard_acquire(PTR__ZGVZN4Aska7Machine6_HTONSEtE9kMyEndian_02cc0910), iVar2 != 0)
         ) {
        *(undefined4 *)PTR__ZZN4Aska7Machine6_HTONSEtE9kMyEndian_02cbc7a8 = 1;
        __cxa_guard_release(PTR__ZGVZN4Aska7Machine6_HTONSEtE9kMyEndian_02cc0910);
      }
      iVar2 = *(int *)PTR__ZZN4Aska7Machine6_HTONSEtE9kMyEndian_02cbc7a8;
      *param_2 = 0xda;
      if (iVar2 != 2) {
        uVar3 = ((uVar3 & 0xff00ff00) >> 8 | (uVar3 & 0xff00ff) << 8) & 0xffff;
      }
      *(short *)(param_2 + 1) = (short)uVar3;
      return 3;
    }
  }
  else if (4 < param_4) {
    if (((*PTR__ZGVZN4Aska7Machine6_HTONLEjE9kMyEndian_02cbe508 & 1) == 0) &&
       (iVar2 = __cxa_guard_acquire(PTR__ZGVZN4Aska7Machine6_HTONLEjE9kMyEndian_02cbe508), iVar2 != 0))
    {
      *(undefined4 *)PTR__ZZN4Aska7Machine6_HTONLEjE9kMyEndian_02cc0b50 = 1;
      __cxa_guard_release(PTR__ZGVZN4Aska7Machine6_HTONLEjE9kMyEndian_02cbe508);
    }
    uVar1 = (uVar3 & 0xff00ff00) >> 8 | (uVar3 & 0xff00ff) << 8;
    iVar2 = *(int *)PTR__ZZN4Aska7Machine6_HTONLEjE9kMyEndian_02cc0b50;
    *param_2 = 0xdb;
    if (iVar2 != 2) {
      uVar3 = uVar1 >> 0x10 | uVar1 << 0x10;
    }
    *(uint *)(param_2 + 1) = uVar3;
    return 5;
  }
  *(undefined8 *)(param_1 + 0x80) = 0xfffffffffffffc3f;
  return 0xfffffffffffffc3f;
}

// ==== long Aska::ASON::PackValue_ext<true>(unsigned char*, unsigned long, signed char, unsigned long) const
// vaddr 0x1f13a6c | ghidra 0x2013a6c | size 452 | symbol _ZNK4Aska4ASON13PackValue_extILb1EEElPhmam | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZNK4Aska4ASON13PackValue_extILb1EEElPhmam
          (long param_1,undefined1 *param_2,ulong param_3,undefined1 param_4,ulong param_5)

{
  uint uVar1;
  int iVar2;
  undefined1 uVar3;
  uint uVar4;
  
  switch(param_3) {
  case 1:
    if (1 < param_5) {
      uVar3 = 0xd4;
code_r0x02013ba4:
      param_2[1] = param_4;
      *param_2 = uVar3;
      return 2;
    }
    break;
  case 2:
    if (1 < param_5) {
      uVar3 = 0xd5;
      goto code_r0x02013ba4;
    }
    break;
  default:
    if (param_3 < 0x100) {
      if (2 < param_5) {
        param_2[1] = (char)param_3;
        param_2[2] = param_4;
        *param_2 = 199;
        return 3;
      }
    }
    else {
      uVar4 = (uint)param_3;
      if (param_3 >> 0x10 == 0) {
        if (3 < param_5) {
          if (((*PTR__ZGVZN4Aska7Machine6_HTONSEtE9kMyEndian_02cc0910 & 1) == 0) &&
             (iVar2 = __cxa_guard_acquire(PTR__ZGVZN4Aska7Machine6_HTONSEtE9kMyEndian_02cc0910),
             iVar2 != 0)) {
            *(undefined4 *)PTR__ZZN4Aska7Machine6_HTONSEtE9kMyEndian_02cbc7a8 = 1;
            __cxa_guard_release(PTR__ZGVZN4Aska7Machine6_HTONSEtE9kMyEndian_02cc0910);
          }
          iVar2 = *(int *)PTR__ZZN4Aska7Machine6_HTONSEtE9kMyEndian_02cbc7a8;
          *param_2 = 200;
          param_2[3] = param_4;
          if (iVar2 != 2) {
            uVar4 = ((uVar4 & 0xff00ff00) >> 8 | (uVar4 & 0xff00ff) << 8) & 0xffff;
          }
          *(short *)(param_2 + 1) = (short)uVar4;
          return 4;
        }
      }
      else if (5 < param_5) {
        if (((*PTR__ZGVZN4Aska7Machine6_HTONLEjE9kMyEndian_02cbe508 & 1) == 0) &&
           (iVar2 = __cxa_guard_acquire(PTR__ZGVZN4Aska7Machine6_HTONLEjE9kMyEndian_02cbe508),
           iVar2 != 0)) {
          *(undefined4 *)PTR__ZZN4Aska7Machine6_HTONLEjE9kMyEndian_02cc0b50 = 1;
          __cxa_guard_release(PTR__ZGVZN4Aska7Machine6_HTONLEjE9kMyEndian_02cbe508);
        }
        uVar1 = (uVar4 & 0xff00ff00) >> 8 | (uVar4 & 0xff00ff) << 8;
        iVar2 = *(int *)PTR__ZZN4Aska7Machine6_HTONLEjE9kMyEndian_02cc0b50;
        *param_2 = 0xc9;
        param_2[5] = param_4;
        if (iVar2 != 2) {
          uVar4 = uVar1 >> 0x10 | uVar1 << 0x10;
        }
        *(uint *)(param_2 + 1) = uVar4;
        return 6;
      }
    }
    break;
  case 4:
    if (1 < param_5) {
      uVar3 = 0xd6;
      goto code_r0x02013ba4;
    }
    break;
  case 8:
    if (1 < param_5) {
      uVar3 = 0xd7;
      goto code_r0x02013ba4;
    }
    break;
  case 0x10:
    if (1 < param_5) {
      uVar3 = 0xd8;
      goto code_r0x02013ba4;
    }
  }
  *(undefined8 *)(param_1 + 0x80) = 0xfffffffffffffc3f;
  return 0xfffffffffffffc3f;
}

// ==== Aska::ASON::UnpackValue_str(Aska::ASON::AValue*, signed char const*, signed char const*, unsigned int, unsigned short)
// vaddr 0x1f13c30 | ghidra 0x2013c30 | size 416 | symbol _ZN4Aska4ASON15UnpackValue_strEPNS0_6AValueEPKaS4_jt | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska4ASON15UnpackValue_strEPNS0_6AValueEPKaS4_jt
          (long param_1,undefined4 *param_2,undefined8 param_3,long param_4,uint param_5,
          undefined2 param_6)

{
  int iVar1;
  ulong uVar2;
  long lVar3;
  undefined8 uVar4;
  undefined2 uVar5;
  ulong uVar6;
  
  *(long *)(param_2 + 2) = param_4;
  param_2[6] = param_5;
  *param_2 = 5;
  *(undefined2 *)(param_2 + 7) = param_6;
  if (((param_4 == 0) || (param_5 == 0)) || (*(char *)(param_1 + 0x88) == '\0')) {
    uVar5 = 0xffff;
    *(undefined8 *)(param_2 + 4) = 0;
code_r0x02013d2c:
    uVar4 = 0;
    *(undefined2 *)((long)param_2 + 0x1e) = uVar5;
  }
  else {
    lVar3 = *(long *)(param_1 + 0x18);
    uVar6 = (ulong)param_5;
    uVar2 = lVar3 + (uVar6 + 4 & 0x1fffffffc);
    if (*(ulong *)(param_1 + 0x10) < uVar2) {
code_r0x02013c94:
      uVar2 = operator new[](unsigned long, std::nothrow_t const&)(uVar6 + 1,PTR__ZSt7nothrow_02cb9a80);
    }
    else {
      *(ulong *)(param_1 + 0x18) = uVar2;
      uVar2 = *(long *)(param_1 + 8) + lVar3;
      if (uVar2 == 0) goto code_r0x02013c94;
    }
    if (uVar2 != 0) {
      memcpy(uVar2,*(undefined8 *)(param_2 + 2),uVar6);
      *(undefined1 *)(uVar2 + uVar6) = 0;
      iVar1 = Aska::StringUtility::Utf8ToMultiByte(char const*, char*, unsigned int)(uVar2,0,0);
      if (iVar1 == 0) {
        if ((uVar2 < *(ulong *)(param_1 + 8)) ||
           (*(long *)(param_1 + 0x10) + *(ulong *)(param_1 + 8) <= uVar2)) {
          operator delete[](void*)(uVar2);
        }
        else {
          *(undefined8 *)(param_1 + 0x18) = 0;
        }
        *(undefined8 *)(param_1 + 0x80) = 0xffffffffffffffff;
        return 0xffffffff;
      }
      lVar3 = Aska::ASON::Malloc(unsigned long)(param_1,iVar1);
      if (lVar3 != 0) {
        Aska::StringUtility::Utf8ToMultiByte(char const*, char*, unsigned int)(uVar2,lVar3,iVar1);
        if ((uVar2 < *(ulong *)(param_1 + 8)) ||
           (*(long *)(param_1 + 0x10) + *(ulong *)(param_1 + 8) <= uVar2)) {
          operator delete[](void*)(uVar2);
        }
        else {
          *(undefined8 *)(param_1 + 0x18) = 0;
        }
        *(long *)(param_2 + 4) = lVar3;
        uVar5 = *(undefined2 *)(param_1 + 0x58);
        goto code_r0x02013d2c;
      }
      if ((uVar2 < *(ulong *)(param_1 + 8)) ||
         (*(long *)(param_1 + 0x10) + *(ulong *)(param_1 + 8) <= uVar2)) {
        operator delete[](void*)(uVar2);
      }
      else {
        *(undefined8 *)(param_1 + 0x18) = 0;
      }
    }
    *(undefined8 *)(param_1 + 0x80) = 0xfffffffffffffc41;
    uVar4 = 0xfffffc41;
  }
  return uVar4;
}

