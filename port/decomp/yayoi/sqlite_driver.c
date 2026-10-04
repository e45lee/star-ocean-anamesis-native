// port/decomp/yayoi/sqlite_driver.c: Ghidra decompiles for the yayoi subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileAt.java, tools/resolve_decomp.py
// run      2026-10-04 06:27 UTC: tools/decomp_at.sh '--into' 'yayoi/sqlite_driver' '0x22f26cc' '0x22f2224' '0x22f210c' '0x22f2084' '0x22f2310' '0x22f2020' '0x22f23e4' '0x22f27d8' '0x22f28e4' '0x22f25c0' '0x22f219c' '0x22f29f4' '0x22f20bc' '0x22f24c4' '0x22f22dc' '0x22f1fe0' '0x22f1fe0' '0x22f1fec' '0x22f1fec' '0x22f2b28' '0x22f352c' '0x22f36c0' '0x22f3330' '0x22f34c4' '0x22f2bbc' '0x22f42bc' '0x22f4bc8' '0x22f4090' '0x22f2b4c' '0x22f4240' '0x22f40fc' '0x22f2ea0' '0x22f3054' '0x22f3728' '0x22f38bc' '0x22f2d34' '0x22f2e88' '0x22f3f40' '0x22f3f20' '0x22f2b04' '0x22f3924' '0x22f3abc' '0x22f3d24' '0x22f3eb8' '0x22f3b28' '0x22f3cbc' '0x22f30e8' '0x22f329c' '0x22f42fc' '0x22f2bcc' '0x22f2bcc' '0x22f2ca4' '0x22f2ca4' '0x22f2b00' '0x22f2b00' '0x22f4d08' '0x22f4d44' '0x22f4fa8' '0x22f5250' '0x22f4c90' '0x22f4db4' '0x22f50f4' '0x22f4e9c' '0x22f4e3c' '0x22f4ea4' '0x22f4ff8' '0x22f4bd0' '0x22f4bd0' '0x22f4bf0' '0x22f4bf0' '0x22f5714' '0x22f5410' '0x22f52a0' '0x22f5270' '0x22f2cf4' '0x22f2008' '0x22f1ff0'
// run      2026-10-04 07:42 UTC: tools/decomp_at.sh '--into' 'yayoi/sqlite_driver' '0x22f5614'

// ==== Aska::Yayoi::EntityCache::EntityCache()
// vaddr 0x21f1fe0 | ghidra 0x22f1fe0 | size 12 | symbol _ZN4Aska5Yayoi11EntityCacheC2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi11EntityCacheC1Ev(undefined8 *param_1)

{
  *(undefined1 *)(param_1 + 2) = 0;
  *param_1 = 0;
  param_1[1] = 0;
  return;
}

// ==== Aska::Yayoi::EntityCache::~EntityCache()
// vaddr 0x21f1fec | ghidra 0x22f1fec | size 4 | symbol _ZN4Aska5Yayoi11EntityCacheD1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi11EntityCacheD2Ev(void)

{
  return;
}

// ==== Aska::Yayoi::EntityCache::GetRowNum() const
// vaddr 0x21f1ff0 | ghidra 0x22f1ff0 | size 24 | symbol _ZNK4Aska5Yayoi11EntityCache9GetRowNumEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK4Aska5Yayoi11EntityCache9GetRowNumEv(undefined8 *param_1)

{
  if ((undefined4 *)*param_1 != (undefined4 *)0x0) {
    return *(undefined4 *)*param_1;
  }
  return 0;
}

// ==== Aska::Yayoi::EntityCache::GetColNum() const
// vaddr 0x21f2008 | ghidra 0x22f2008 | size 24 | symbol _ZNK4Aska5Yayoi11EntityCache9GetColNumEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK4Aska5Yayoi11EntityCache9GetColNumEv(long *param_1)

{
  if (*param_1 != 0) {
    return *(undefined4 *)(*param_1 + 4);
  }
  return 0;
}

// ==== Aska::Yayoi::EntityCache::SetRowAddrtbl(int, unsigned long)
// vaddr 0x21f2020 | ghidra 0x22f2020 | size 100 | symbol _ZN4Aska5Yayoi11EntityCache13SetRowAddrtblEim | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi11EntityCache13SetRowAddrtblEim
               (undefined8 *param_1,undefined8 *param_2,int param_3,undefined8 param_4)

{
  int *piVar1;
  
  piVar1 = (int *)*param_2;
  if (piVar1 == (int *)0x0) {
    *param_1 = 0xfffffffffffffc15;
    return;
  }
  if (*(char *)(param_2 + 2) == '\0') {
    *param_1 = 0xfffffffffffffc0a;
    return;
  }
  if (*piVar1 <= param_3) {
    *param_1 = 0xfffffffffffffc4f;
    return;
  }
  if (param_3 != 0) {
    *(undefined8 *)(piVar1 + (long)param_3 + 1) = param_4;
    *param_1 = 0;
    return;
  }
  *param_1 = 0;
  return;
}

// ==== Aska::Yayoi::EntityCache::GetRowAddress(int)
// vaddr 0x21f2084 | ghidra 0x22f2084 | size 56 | symbol _ZN4Aska5Yayoi11EntityCache13GetRowAddressEi | lib libSOA-3.7.0.so | 2026-10-04
int * _ZN4Aska5Yayoi11EntityCache13GetRowAddressEi(undefined8 *param_1,int param_2)

{
  int *piVar1;
  
  piVar1 = (int *)*param_1;
  if (piVar1 == (int *)0x0) {
    return (int *)0x0;
  }
  if (*(char *)(param_1 + 2) != '\0') {
    if (param_2 != 0) {
      return *(int **)(piVar1 + (long)param_2 * 2);
    }
    return piVar1 + (long)*piVar1 * 2;
  }
  return (int *)0x0;
}

// ==== Aska::Yayoi::EntityCache::GetRowPtr(int)
// vaddr 0x21f20bc | ghidra 0x22f20bc | size 80 | symbol _ZN4Aska5Yayoi11EntityCache9GetRowPtrEi | lib libSOA-3.7.0.so | 2026-10-04
int * _ZN4Aska5Yayoi11EntityCache9GetRowPtrEi(undefined8 *param_1,int param_2)

{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  
  piVar2 = (int *)*param_1;
  if ((piVar2 != (int *)0x0) && (*(char *)(param_1 + 2) != '\0')) {
    if (param_2 == 0) {
      piVar3 = piVar2 + (long)*piVar2 * 2;
    }
    else {
      piVar3 = *(int **)(piVar2 + (long)param_2 * 2);
      if (piVar3 == (int *)0x0) {
        return (int *)0x0;
      }
    }
    if (piVar2 <= piVar3) {
      piVar1 = (int *)0x0;
      if (piVar3 <= (int *)(param_1[1] + (long)piVar2)) {
        piVar1 = piVar3;
      }
      return piVar1;
    }
  }
  return (int *)0x0;
}

// ==== Aska::Yayoi::EntityCache::GetColAddress(int, int)
// vaddr 0x21f210c | ghidra 0x22f210c | size 144 | symbol _ZN4Aska5Yayoi11EntityCache13GetColAddressEii | lib libSOA-3.7.0.so | 2026-10-04
int * _ZN4Aska5Yayoi11EntityCache13GetColAddressEii(undefined8 *param_1,int param_2,int param_3)

{
  int *piVar1;
  int *piVar2;
  
  piVar1 = (int *)*param_1;
  if (piVar1 == (int *)0x0) {
    return (int *)0x0;
  }
  if (*(char *)(param_1 + 2) == '\0') {
    return (int *)0x0;
  }
  if (param_2 == 0) {
    piVar2 = piVar1 + (long)*piVar1 * 2;
  }
  else {
    piVar2 = *(int **)(piVar1 + (long)param_2 * 2);
    if (piVar2 == (int *)0x0) {
      return (int *)0x0;
    }
  }
  if (piVar1 <= piVar2) {
    if ((ulong)(param_1[1] + (long)piVar1) <= (long)piVar2 - 1U) {
      return (int *)0x0;
    }
    if (param_3 != 0) {
      return *(int **)(piVar2 + (long)param_3 * 2 + -2);
    }
    return piVar2 + (long)(piVar1[1] + -1) * 2;
  }
  return (int *)0x0;
}

// ==== Aska::Yayoi::EntityCache::GetColPtr(int, int)
// vaddr 0x21f219c | ghidra 0x22f219c | size 136 | symbol _ZN4Aska5Yayoi11EntityCache9GetColPtrEii | lib libSOA-3.7.0.so | 2026-10-04
int * _ZN4Aska5Yayoi11EntityCache9GetColPtrEii(undefined8 *param_1,int param_2,int param_3)

{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  
  piVar2 = (int *)*param_1;
  if ((piVar2 != (int *)0x0) && (*(char *)(param_1 + 2) != '\0')) {
    if (param_2 == 0) {
      piVar3 = piVar2 + (long)*piVar2 * 2;
    }
    else {
      piVar3 = *(int **)(piVar2 + (long)param_2 * 2);
      if (piVar3 == (int *)0x0) {
        return (int *)0x0;
      }
    }
    if ((piVar2 <= piVar3) && ((int *)((long)piVar3 + -1) < (int *)(param_1[1] + (long)piVar2))) {
      if (param_3 == 0) {
        piVar3 = piVar3 + (long)(piVar2[1] + -1) * 2;
      }
      else {
        piVar3 = *(int **)(piVar3 + (long)param_3 * 2 + -2);
      }
      if ((piVar3 != (int *)0x0) && (piVar2 <= piVar3)) {
        piVar1 = (int *)0x0;
        if (piVar3 <= (int *)(param_1[1] + (long)piVar2)) {
          piVar1 = piVar3;
        }
        return piVar1;
      }
    }
  }
  return (int *)0x0;
}

// ==== Aska::Yayoi::EntityCache::GetColValue(int, int, unsigned long*)
// vaddr 0x21f2224 | ghidra 0x22f2224 | size 184 | symbol _ZN4Aska5Yayoi11EntityCache11GetColValueEiiPm | lib libSOA-3.7.0.so | 2026-10-04
int * _ZN4Aska5Yayoi11EntityCache11GetColValueEiiPm
                (undefined8 *param_1,int param_2,int param_3,undefined8 *param_4)

{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  
  piVar2 = (int *)*param_1;
  if (piVar2 == (int *)0x0) {
    return (int *)0x0;
  }
  if (*(char *)(param_1 + 2) == '\0') {
    return (int *)0x0;
  }
  if (param_2 == 0) {
    piVar3 = piVar2 + (long)*piVar2 * 2;
  }
  else {
    piVar3 = *(int **)(piVar2 + (long)param_2 * 2);
    if (piVar3 == (int *)0x0) {
      return (int *)0x0;
    }
  }
  if (piVar2 <= piVar3) {
    if ((long)piVar3 - 1U < (ulong)(param_1[1] + (long)piVar2)) {
      if (param_3 == 0) {
        piVar3 = piVar3 + (long)(piVar2[1] + -1) * 2;
      }
      else {
        piVar3 = *(int **)(piVar3 + (long)param_3 * 2 + -2);
      }
      piVar1 = (int *)0x0;
      if (((piVar2 <= piVar3) && (piVar3 != (int *)0x0)) &&
         ((long)piVar3 - 1U < (ulong)(param_1[1] + (long)piVar2))) {
        piVar1 = piVar3 + 2;
        *param_4 = *(undefined8 *)piVar3;
      }
      return piVar1;
    }
    return (int *)0x0;
  }
  return (int *)0x0;
}

// ==== Aska::Yayoi::EntityCache::SetHeader(int, int)
// vaddr 0x21f22dc | ghidra 0x22f22dc | size 52 | symbol _ZN4Aska5Yayoi11EntityCache9SetHeaderEii | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi11EntityCache9SetHeaderEii
               (undefined8 *param_1,long *param_2,undefined4 param_3,undefined4 param_4)

{
  if ((undefined4 *)*param_2 != (undefined4 *)0x0) {
    *(undefined4 *)*param_2 = param_3;
    *(undefined4 *)(*param_2 + 4) = param_4;
    *(undefined1 *)(param_2 + 2) = 1;
    *param_1 = 0;
    return;
  }
  *param_1 = 0xfffffffffffffc15;
  return;
}

// ==== Aska::Yayoi::EntityCache::SetColAddrtbl(int, int, unsigned long)
// vaddr 0x21f2310 | ghidra 0x22f2310 | size 212 | symbol _ZN4Aska5Yayoi11EntityCache13SetColAddrtblEiim | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi11EntityCache13SetColAddrtblEiim
               (undefined8 *param_1,undefined8 *param_2,int param_3,int param_4,undefined8 param_5)

{
  int *piVar1;
  int *piVar2;
  
  piVar1 = (int *)*param_2;
  if (piVar1 == (int *)0x0) {
    *param_1 = 0xfffffffffffffc15;
    return;
  }
  if (*(char *)(param_2 + 2) == '\0') {
    *param_1 = 0xfffffffffffffc0a;
    return;
  }
  if (*piVar1 <= param_3) {
    *param_1 = 0xfffffffffffffc4f;
    return;
  }
  if (param_4 < piVar1[1]) {
    if (param_4 == 0) {
      *param_1 = 0;
      return;
    }
    if (param_3 == 0) {
      piVar2 = piVar1 + (long)(*piVar1 + -1) * 2 + 2;
    }
    else {
      piVar2 = *(int **)(piVar1 + (long)param_3 * 2);
      if (piVar2 == (int *)0x0) {
        *param_1 = 0xfffffffffffffc21;
        return;
      }
    }
    if (piVar2 < piVar1) {
      *param_1 = 0xfffffffffffffc21;
      return;
    }
    if ((long)piVar2 - 1U < (ulong)(param_2[1] + (long)piVar1)) {
      *(undefined8 *)(piVar2 + (long)(param_4 + -1) * 2) = param_5;
      *param_1 = 0;
      return;
    }
    *param_1 = 0xfffffffffffffc21;
    return;
  }
  *param_1 = 0xfffffffffffffc4f;
  return;
}

// ==== Aska::Yayoi::EntityCache::GetData(int, char*, unsigned long*, unsigned long)
// vaddr 0x21f23e4 | ghidra 0x22f23e4 | size 224 | symbol _ZN4Aska5Yayoi11EntityCache7GetDataEiPcPmm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi11EntityCache7GetDataEiPcPmm
               (undefined8 *param_1,undefined8 *param_2,int param_3,undefined8 param_4,
               ulong *param_5,uint param_6)

{
  ulong *puVar1;
  undefined8 uVar2;
  ulong *puVar3;
  ulong uVar4;
  
  puVar3 = (ulong *)*param_2;
  if ((puVar3 != (ulong *)0x0) && (*(char *)(param_2 + 2) != '\0')) {
    if (param_6 == 0) {
      puVar1 = puVar3 + (int)*puVar3;
    }
    else {
      puVar1 = *(ulong **)
                ((long)puVar3 +
                (-(ulong)(param_6 >> 0x1f) & 0xfffffff800000000 | (ulong)param_6 << 3));
      if (puVar1 == (ulong *)0x0) goto code_r0x022f2454;
    }
    if ((puVar3 <= puVar1) && ((long)puVar1 - 1U < (ulong)(param_2[1] + (long)puVar3))) {
      if (param_3 == 0) {
        puVar1 = puVar1 + (*(int *)((long)puVar3 + 4) + -1);
      }
      else {
        puVar1 = (ulong *)puVar1[(long)param_3 + -1];
      }
      uVar2 = 0xffffffffffffffff;
      if (((puVar3 <= puVar1) && (puVar1 != (ulong *)0x0)) &&
         ((long)puVar1 - 1U < (ulong)(param_2[1] + (long)puVar3))) {
        uVar4 = *puVar1;
        if (*param_5 < uVar4) {
          uVar2 = 0xfffffffffffffc15;
        }
        else {
          memcpy(param_4,puVar1 + 1,uVar4);
          uVar2 = 0;
          *param_5 = uVar4;
        }
      }
      goto code_r0x022f2458;
    }
  }
code_r0x022f2454:
  uVar2 = 0xffffffffffffffff;
code_r0x022f2458:
  *param_1 = uVar2;
  return;
}

// ==== Aska::Yayoi::EntityCache::GetString(int, char*, unsigned long*, unsigned long)
// vaddr 0x21f24c4 | ghidra 0x22f24c4 | size 252 | symbol _ZN4Aska5Yayoi11EntityCache9GetStringEiPcPmm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi11EntityCache9GetStringEiPcPmm
               (undefined8 *param_1,undefined8 *param_2,int param_3,long param_4,ulong *param_5,
               uint param_6)

{
  ulong *puVar1;
  undefined8 uVar2;
  ulong *puVar3;
  ulong uVar4;
  ulong uVar5;
  
  puVar3 = (ulong *)*param_2;
  if ((puVar3 != (ulong *)0x0) && (*(char *)(param_2 + 2) != '\0')) {
    uVar5 = *param_5;
    if (param_6 == 0) {
      puVar1 = puVar3 + (int)*puVar3;
    }
    else {
      puVar1 = *(ulong **)
                ((long)puVar3 +
                (-(ulong)(param_6 >> 0x1f) & 0xfffffff800000000 | (ulong)param_6 << 3));
      if (puVar1 == (ulong *)0x0) goto code_r0x022f2540;
    }
    if ((puVar3 <= puVar1) && ((long)puVar1 - 1U < (ulong)(param_2[1] + (long)puVar3))) {
      if (param_3 == 0) {
        puVar1 = puVar1 + (*(int *)((long)puVar3 + 4) + -1);
      }
      else {
        puVar1 = (ulong *)puVar1[(long)param_3 + -1];
      }
      uVar2 = 0xffffffffffffffff;
      if (((puVar3 <= puVar1) && (puVar1 != (ulong *)0x0)) &&
         ((long)puVar1 - 1U < (ulong)(param_2[1] + (long)puVar3))) {
        uVar4 = *puVar1;
        if (uVar4 <= uVar5) {
          memcpy(param_4,puVar1 + 1,uVar4);
          *param_5 = uVar4;
          if (uVar4 <= uVar5 - 1) {
            uVar2 = 0;
            *(undefined1 *)(param_4 + uVar4) = 0;
            goto code_r0x022f2544;
          }
        }
        uVar2 = 0xfffffffffffffc15;
      }
      goto code_r0x022f2544;
    }
  }
code_r0x022f2540:
  uVar2 = 0xffffffffffffffff;
code_r0x022f2544:
  *param_1 = uVar2;
  return;
}

// ==== Aska::Yayoi::EntityCache::GetShort(int, short*, unsigned long)
// vaddr 0x21f25c0 | ghidra 0x22f25c0 | size 268 | symbol _ZN4Aska5Yayoi11EntityCache8GetShortEiPsm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi11EntityCache8GetShortEiPsm
               (undefined8 *param_1,undefined8 *param_2,int param_3,undefined2 *param_4,uint param_5
               )

{
  undefined2 uVar1;
  ulong *puVar2;
  undefined8 uVar3;
  ulong *puVar4;
  ulong uVar5;
  undefined8 uStack_40;
  undefined4 uStack_38;
  
  uStack_38 = 0;
  uStack_40 = 0;
  puVar4 = (ulong *)*param_2;
  if ((puVar4 != (ulong *)0x0) && (*(char *)(param_2 + 2) != '\0')) {
    if (param_5 == 0) {
      puVar2 = puVar4 + (int)*puVar4;
    }
    else {
      puVar2 = *(ulong **)
                ((long)puVar4 +
                (-(ulong)(param_5 >> 0x1f) & 0xfffffff800000000 | (ulong)param_5 << 3));
      if (puVar2 == (ulong *)0x0) goto code_r0x022f2640;
    }
    if ((puVar4 <= puVar2) && ((long)puVar2 - 1U < (ulong)(param_2[1] + (long)puVar4))) {
      if (param_3 == 0) {
        puVar2 = puVar2 + (*(int *)((long)puVar4 + 4) + -1);
      }
      else {
        puVar2 = (ulong *)puVar2[(long)param_3 + -1];
      }
      uVar3 = 0xffffffffffffffff;
      if (((puVar4 <= puVar2) && (puVar2 != (ulong *)0x0)) &&
         ((long)puVar2 - 1U < (ulong)(param_2[1] + (long)puVar4))) {
        uVar5 = *puVar2;
        if ((uVar5 < 0xd) && (memcpy(&uStack_40,puVar2 + 1,uVar5), uVar5 != 0xc)) {
          *(undefined1 *)((long)&uStack_40 + uVar5) = 0;
          uVar1 = atoi(&uStack_40);
          uVar3 = 0;
          *param_4 = uVar1;
        }
        else {
          uVar3 = 0xfffffffffffffc15;
        }
      }
      goto code_r0x022f2644;
    }
  }
code_r0x022f2640:
  uVar3 = 0xffffffffffffffff;
code_r0x022f2644:
  *param_1 = uVar3;
  return;
}

// ==== Aska::Yayoi::EntityCache::GetInteger(int, int*, unsigned long)
// vaddr 0x21f26cc | ghidra 0x22f26cc | size 268 | symbol _ZN4Aska5Yayoi11EntityCache10GetIntegerEiPim | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi11EntityCache10GetIntegerEiPim
               (undefined8 *param_1,undefined8 *param_2,int param_3,undefined4 *param_4,uint param_5
               )

{
  undefined4 uVar1;
  ulong *puVar2;
  undefined8 uVar3;
  ulong *puVar4;
  ulong uVar5;
  undefined8 uStack_40;
  undefined4 uStack_38;
  
  uStack_38 = 0;
  uStack_40 = 0;
  puVar4 = (ulong *)*param_2;
  if ((puVar4 != (ulong *)0x0) && (*(char *)(param_2 + 2) != '\0')) {
    if (param_5 == 0) {
      puVar2 = puVar4 + (int)*puVar4;
    }
    else {
      puVar2 = *(ulong **)
                ((long)puVar4 +
                (-(ulong)(param_5 >> 0x1f) & 0xfffffff800000000 | (ulong)param_5 << 3));
      if (puVar2 == (ulong *)0x0) goto code_r0x022f274c;
    }
    if ((puVar4 <= puVar2) && ((long)puVar2 - 1U < (ulong)(param_2[1] + (long)puVar4))) {
      if (param_3 == 0) {
        puVar2 = puVar2 + (*(int *)((long)puVar4 + 4) + -1);
      }
      else {
        puVar2 = (ulong *)puVar2[(long)param_3 + -1];
      }
      uVar3 = 0xffffffffffffffff;
      if (((puVar4 <= puVar2) && (puVar2 != (ulong *)0x0)) &&
         ((long)puVar2 - 1U < (ulong)(param_2[1] + (long)puVar4))) {
        uVar5 = *puVar2;
        if ((uVar5 < 0xd) && (memcpy(&uStack_40,puVar2 + 1,uVar5), uVar5 != 0xc)) {
          *(undefined1 *)((long)&uStack_40 + uVar5) = 0;
          uVar1 = atoi(&uStack_40);
          uVar3 = 0;
          *param_4 = uVar1;
        }
        else {
          uVar3 = 0xfffffffffffffc15;
        }
      }
      goto code_r0x022f2750;
    }
  }
code_r0x022f274c:
  uVar3 = 0xffffffffffffffff;
code_r0x022f2750:
  *param_1 = uVar3;
  return;
}

// ==== Aska::Yayoi::EntityCache::GetLong(int, long*, unsigned long)
// vaddr 0x21f27d8 | ghidra 0x22f27d8 | size 268 | symbol _ZN4Aska5Yayoi11EntityCache7GetLongEiPlm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi11EntityCache7GetLongEiPlm
               (undefined8 *param_1,undefined8 *param_2,int param_3,undefined8 *param_4,uint param_5
               )

{
  undefined8 uVar1;
  ulong *puVar2;
  undefined8 uVar3;
  ulong *puVar4;
  ulong uVar5;
  undefined8 uStack_48;
  undefined5 uStack_40;
  undefined3 uStack_3b;
  undefined5 uStack_38;
  
  uStack_38 = 0;
  uStack_48 = 0;
  uStack_40 = 0;
  uStack_3b = 0;
  puVar4 = (ulong *)*param_2;
  if ((puVar4 != (ulong *)0x0) && (*(char *)(param_2 + 2) != '\0')) {
    if (param_5 == 0) {
      puVar2 = puVar4 + (int)*puVar4;
    }
    else {
      puVar2 = *(ulong **)
                ((long)puVar4 +
                (-(ulong)(param_5 >> 0x1f) & 0xfffffff800000000 | (ulong)param_5 << 3));
      if (puVar2 == (ulong *)0x0) goto code_r0x022f2858;
    }
    if ((puVar4 <= puVar2) && ((long)puVar2 - 1U < (ulong)(param_2[1] + (long)puVar4))) {
      if (param_3 == 0) {
        puVar2 = puVar2 + (*(int *)((long)puVar4 + 4) + -1);
      }
      else {
        puVar2 = (ulong *)puVar2[(long)param_3 + -1];
      }
      uVar3 = 0xffffffffffffffff;
      if (((puVar4 <= puVar2) && (puVar2 != (ulong *)0x0)) &&
         ((long)puVar2 - 1U < (ulong)(param_2[1] + (long)puVar4))) {
        uVar5 = *puVar2;
        if ((uVar5 < 0x16) && (memcpy(&uStack_48,puVar2 + 1,uVar5), uVar5 != 0x15)) {
          *(undefined1 *)((long)&uStack_48 + uVar5) = 0;
          uVar1 = atol(&uStack_48);
          uVar3 = 0;
          *param_4 = uVar1;
        }
        else {
          uVar3 = 0xfffffffffffffc15;
        }
      }
      goto code_r0x022f285c;
    }
  }
code_r0x022f2858:
  uVar3 = 0xffffffffffffffff;
code_r0x022f285c:
  *param_1 = uVar3;
  return;
}

// ==== Aska::Yayoi::EntityCache::GetFloat(int, float*, unsigned long)
// vaddr 0x21f28e4 | ghidra 0x22f28e4 | size 272 | symbol _ZN4Aska5Yayoi11EntityCache8GetFloatEiPfm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi11EntityCache8GetFloatEiPfm
               (undefined8 *param_1,undefined8 *param_2,int param_3,float *param_4,uint param_5)

{
  double dVar1;
  ulong *puVar2;
  undefined8 uVar3;
  ulong *puVar4;
  ulong uVar5;
  undefined8 uStack_48;
  undefined5 uStack_40;
  undefined3 uStack_3b;
  undefined5 uStack_38;
  
  uStack_38 = 0;
  uStack_48 = 0;
  uStack_40 = 0;
  uStack_3b = 0;
  puVar4 = (ulong *)*param_2;
  if ((puVar4 != (ulong *)0x0) && (*(char *)(param_2 + 2) != '\0')) {
    if (param_5 == 0) {
      puVar2 = puVar4 + (int)*puVar4;
    }
    else {
      puVar2 = *(ulong **)
                ((long)puVar4 +
                (-(ulong)(param_5 >> 0x1f) & 0xfffffff800000000 | (ulong)param_5 << 3));
      if (puVar2 == (ulong *)0x0) goto code_r0x022f2964;
    }
    if ((puVar4 <= puVar2) && ((long)puVar2 - 1U < (ulong)(param_2[1] + (long)puVar4))) {
      if (param_3 == 0) {
        puVar2 = puVar2 + (*(int *)((long)puVar4 + 4) + -1);
      }
      else {
        puVar2 = (ulong *)puVar2[(long)param_3 + -1];
      }
      uVar3 = 0xffffffffffffffff;
      if (((puVar4 <= puVar2) && (puVar2 != (ulong *)0x0)) &&
         ((long)puVar2 - 1U < (ulong)(param_2[1] + (long)puVar4))) {
        uVar5 = *puVar2;
        if ((uVar5 < 0x16) && (memcpy(&uStack_48,puVar2 + 1,uVar5), uVar5 != 0x15)) {
          *(undefined1 *)((long)&uStack_48 + uVar5) = 0;
          dVar1 = (double)atof(&uStack_48);
          uVar3 = 0;
          *param_4 = (float)dVar1;
        }
        else {
          uVar3 = 0xfffffffffffffc15;
        }
      }
      goto code_r0x022f2968;
    }
  }
code_r0x022f2964:
  uVar3 = 0xffffffffffffffff;
code_r0x022f2968:
  *param_1 = uVar3;
  return;
}

// ==== Aska::Yayoi::EntityCache::GetDouble(int, double*, unsigned long)
// vaddr 0x21f29f4 | ghidra 0x22f29f4 | size 268 | symbol _ZN4Aska5Yayoi11EntityCache9GetDoubleEiPdm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi11EntityCache9GetDoubleEiPdm
               (undefined8 *param_1,undefined8 *param_2,int param_3,undefined8 *param_4,uint param_5
               )

{
  ulong *puVar1;
  undefined8 uVar2;
  ulong *puVar3;
  ulong uVar4;
  undefined8 uVar5;
  undefined8 uStack_48;
  undefined5 uStack_40;
  undefined3 uStack_3b;
  undefined5 uStack_38;
  
  uStack_38 = 0;
  uStack_48 = 0;
  uStack_40 = 0;
  uStack_3b = 0;
  puVar3 = (ulong *)*param_2;
  if ((puVar3 != (ulong *)0x0) && (*(char *)(param_2 + 2) != '\0')) {
    if (param_5 == 0) {
      puVar1 = puVar3 + (int)*puVar3;
    }
    else {
      puVar1 = *(ulong **)
                ((long)puVar3 +
                (-(ulong)(param_5 >> 0x1f) & 0xfffffff800000000 | (ulong)param_5 << 3));
      if (puVar1 == (ulong *)0x0) goto code_r0x022f2a74;
    }
    if ((puVar3 <= puVar1) && ((long)puVar1 - 1U < (ulong)(param_2[1] + (long)puVar3))) {
      if (param_3 == 0) {
        puVar1 = puVar1 + (*(int *)((long)puVar3 + 4) + -1);
      }
      else {
        puVar1 = (ulong *)puVar1[(long)param_3 + -1];
      }
      uVar2 = 0xffffffffffffffff;
      if (((puVar3 <= puVar1) && (puVar1 != (ulong *)0x0)) &&
         ((long)puVar1 - 1U < (ulong)(param_2[1] + (long)puVar3))) {
        uVar4 = *puVar1;
        if ((uVar4 < 0x16) && (memcpy(&uStack_48,puVar1 + 1,uVar4), uVar4 != 0x15)) {
          *(undefined1 *)((long)&uStack_48 + uVar4) = 0;
          uVar5 = atof(&uStack_48);
          uVar2 = 0;
          *param_4 = uVar5;
        }
        else {
          uVar2 = 0xfffffffffffffc15;
        }
      }
      goto code_r0x022f2a78;
    }
  }
code_r0x022f2a74:
  uVar2 = 0xffffffffffffffff;
code_r0x022f2a78:
  *param_1 = uVar2;
  return;
}

// ==== Aska::Yayoi::SQLiteDriver::ConnectionSet::~ConnectionSet()
// vaddr 0x21f2b00 | ghidra 0x22f2b00 | size 4 | symbol _ZN4Aska5Yayoi12SQLiteDriver13ConnectionSetD2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi12SQLiteDriver13ConnectionSetD1Ev(void)

{
  return;
}

// ==== Aska::Yayoi::SQLiteDriver::EntityObject::Release()
// vaddr 0x21f2b04 | ghidra 0x22f2b04 | size 36 | symbol _ZN4Aska5Yayoi12SQLiteDriver12EntityObject7ReleaseEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi12SQLiteDriver12EntityObject7ReleaseEv(long param_1)

{
  if (*(long *)(param_1 + 0x10) != 0) {
    operator delete[](void*)();
    *(undefined8 *)(param_1 + 0x10) = 0;
  }
  *(undefined8 *)(param_1 + 0x18) = 0;
  return;
}

// ==== Aska::Yayoi::SQLiteDriver::EntityObject::ClearCache()
// vaddr 0x21f2b28 | ghidra 0x22f2b28 | size 36 | symbol _ZN4Aska5Yayoi12SQLiteDriver12EntityObject10ClearCacheEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi12SQLiteDriver12EntityObject10ClearCacheEv(long param_1)

{
  if (*(long *)(param_1 + 0x10) != 0) {
    operator delete[](void*)();
    *(undefined8 *)(param_1 + 0x10) = 0;
  }
  *(undefined8 *)(param_1 + 0x18) = 0;
  return;
}

// ==== Aska::Yayoi::SQLiteDriver::EntityObject::CreateCacheBuffer(unsigned long)
// vaddr 0x21f2b4c | ghidra 0x22f2b4c | size 112 | symbol _ZN4Aska5Yayoi12SQLiteDriver12EntityObject17CreateCacheBufferEm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi12SQLiteDriver12EntityObject17CreateCacheBufferEm
               (undefined8 *param_1,long param_2,ulong param_3)

{
  long lVar1;
  undefined8 uVar2;
  
  if (*(ulong *)(param_2 + 0x18) < param_3) {
    if (*(long *)(param_2 + 0x10) != 0) {
      operator delete[](void*)();
      *(undefined8 *)(param_2 + 0x10) = 0;
    }
    lVar1 = operator new[](unsigned long, std::nothrow_t const&)(param_3,PTR__ZSt7nothrow_02cb9a80);
    *(long *)(param_2 + 0x10) = lVar1;
    if (lVar1 == 0) {
      uVar2 = 0xfffffffffffffc41;
    }
    else {
      uVar2 = 0;
      *(ulong *)(param_2 + 0x18) = param_3;
    }
  }
  else {
    uVar2 = 0;
  }
  *param_1 = uVar2;
  return;
}

// ==== Aska::Yayoi::SQLiteDriver::EntityObject::GetCacheBuffer(unsigned long*)
// vaddr 0x21f2bbc | ghidra 0x22f2bbc | size 16 | symbol _ZN4Aska5Yayoi12SQLiteDriver12EntityObject14GetCacheBufferEPm | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska5Yayoi12SQLiteDriver12EntityObject14GetCacheBufferEPm(long param_1,undefined8 *param_2)

{
  *param_2 = *(undefined8 *)(param_1 + 0x18);
  return *(undefined8 *)(param_1 + 0x10);
}

// ==== Aska::Yayoi::SQLiteDriver::EntityObject::EntityObject()
// vaddr 0x21f2bcc | ghidra 0x22f2bcc | size 216 | symbol _ZN4Aska5Yayoi12SQLiteDriver12EntityObjectC1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi12SQLiteDriver12EntityObjectC2Ev(undefined8 *param_1)

{
  undefined *puVar1;
  ulong uVar2;
  long lVar3;
  undefined1 *puVar4;
  undefined1 *puVar5;
  ulong uVar7;
  ulong uVar8;
  undefined1 *puVar6;
  
  *param_1 = 0;
  *(undefined4 *)(param_1 + 1) = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  puVar1 = PTR__ZTVN4Aska8THashMapIPKciNS_5Yayoi12SQLiteDriver12EntityObject12StringHasherENS5_13StringEqualToENS_10TAllocatorINS_5TPairIKS2_iEEEEEE_02cc1328
           + 0x10;
  *(undefined8 *)((long)param_1 + 0x2c) = 0x3f400000;
  param_1[4] = puVar1;
  *(undefined4 *)((long)param_1 + 0x34) = 0;
  puVar4 = (undefined1 *)Aska::MemoryManagerAdapter::AlignedMalloc(unsigned long, unsigned long)(0x198,8);
  lVar3 = 0x11;
  if (puVar4 == (undefined1 *)0x0) {
    lVar3 = 0;
  }
  param_1[8] = puVar4;
  param_1[9] = lVar3;
  if (puVar4 != (undefined1 *)0x0) {
    uVar2 = (lVar3 * 0x18 - 0x18U) / 0x18 + 1;
    puVar6 = puVar4;
    if ((1 < uVar2) && (uVar7 = uVar2 & 0x1ffffffffffffffe, uVar7 != 0)) {
      uVar8 = uVar7;
      do {
        *puVar6 = 0;
        puVar6[0x18] = 0;
        uVar8 = uVar8 - 2;
        puVar6 = puVar6 + 0x30;
      } while (uVar8 != 0);
      puVar6 = puVar4 + uVar7 * 0x18;
      if (uVar2 == uVar7) goto code_r0x022f2c98;
    }
    do {
      puVar5 = puVar6 + 0x18;
      *puVar6 = 0;
      puVar6 = puVar5;
    } while (puVar4 + lVar3 * 0x18 != puVar5);
  }
code_r0x022f2c98:
  param_1[10] = 0;
  param_1[0xb] = 0;
  return;
}

// ==== Aska::Yayoi::SQLiteDriver::EntityObject::~EntityObject()
// vaddr 0x21f2ca4 | ghidra 0x22f2ca4 | size 80 | symbol _ZN4Aska5Yayoi12SQLiteDriver12EntityObjectD2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi12SQLiteDriver12EntityObjectD1Ev(long param_1)

{
  undefined *puVar1;
  
  if (*(long *)(param_1 + 0x10) != 0) {
    operator delete[](void*)();
    *(undefined8 *)(param_1 + 0x10) = 0;
  }
  puVar1 = PTR__ZTVN4Aska8THashMapIPKciNS_5Yayoi12SQLiteDriver12EntityObject12StringHasherENS5_13StringEqualToENS_10TAllocatorINS_5TPairIKS2_iEEEEEE_02cc1328
           + 0x10;
  *(undefined8 *)(param_1 + 0x18) = 0;
  *(undefined **)(param_1 + 0x20) = puVar1;
  if (*(long *)(param_1 + 0x40) != 0) {
    Aska::MemoryManagerAdapter::AlignedFree(void*)();
    *(long *)(param_1 + 0x40) = 0;
    *(undefined8 *)(param_1 + 0x48) = 0;
  }
  *(undefined8 *)(param_1 + 0x30) = 0;
  return;
}

// ==== Aska::THashMap<char const*, int, Aska::Yayoi::SQLiteDriver::EntityObject::StringHasher, Aska::Yayoi::SQLiteDriver::EntityObject::StringEqualTo, Aska::TAllocator<Aska::TPair<char const* const, int> > >::~THashMap()
// vaddr 0x21f2cf4 | ghidra 0x22f2cf4 | size 64 | symbol _ZN4Aska8THashMapIPKciNS_5Yayoi12SQLiteDriver12EntityObject12StringHasherENS5_13StringEqualToENS_10TAllocatorINS_5TPairIKS2_iEEEEED2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska8THashMapIPKciNS_5Yayoi12SQLiteDriver12EntityObject12StringHasherENS5_13StringEqualToENS_10TAllocatorINS_5TPairIKS2_iEEEEED2Ev
               (long *param_1)

{
  *param_1 = (long)(
                   PTR__ZTVN4Aska8THashMapIPKciNS_5Yayoi12SQLiteDriver12EntityObject12StringHasherENS5_13StringEqualToENS_10TAllocatorINS_5TPairIKS2_iEEEEEE_02cc1328
                   + 0x10);
  if (param_1[4] != 0) {
    Aska::MemoryManagerAdapter::AlignedFree(void*)();
    param_1[4] = 0;
    param_1[5] = 0;
  }
  param_1[2] = 0;
  return;
}

// ==== Aska::Yayoi::SQLiteDriver::EntityObject::GetTime(char const*, char*, unsigned long*, unsigned long)
// vaddr 0x21f2d34 | ghidra 0x22f2d34 | size 340 | symbol _ZN4Aska5Yayoi12SQLiteDriver12EntityObject7GetTimeEPKcPcPmm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi12SQLiteDriver12EntityObject7GetTimeEPKcPcPmm
               (undefined8 *param_1,long param_2,undefined8 param_3,long param_4)

{
  ulong uVar1;
  long lVar2;
  int iVar3;
  undefined8 uVar4;
  long lVar5;
  ulong uVar6;
  long lVar7;
  ulong uVar8;
  char *pcVar9;
  undefined8 uStack_88;
  undefined8 auStack_80 [4];
  long lStack_58;
  
  lVar7 = *(long *)(param_2 + 0x40);
  uVar6 = *(ulong *)(param_2 + 0x48);
  uStack_88 = param_3;
  uVar4 = strlen(param_3);
  auStack_80[0] = 0;
  lStack_58 = 0;
  Aska::detail::SpookyHashV2::Hash128(void const*, unsigned long, unsigned long*, unsigned long*)(param_3,uVar4,&lStack_58,auStack_80);
  lVar2 = lStack_58;
  if (uVar6 != 0) {
    uVar8 = 0;
    do {
      uVar1 = 0;
      if (uVar6 != 0) {
        uVar1 = (lVar2 + uVar8) / uVar6;
      }
      lVar5 = (lVar2 + uVar8) - uVar1 * uVar6;
      pcVar9 = (char *)(lVar7 + lVar5 * 0x18);
      if (*pcVar9 == '\x01') {
        iVar3 = strcmp(*(undefined8 *)(lVar7 + lVar5 * 0x18 + 8),param_3);
        if (iVar3 == 0) {
          lVar7 = *(long *)(param_2 + 0x40);
          uVar6 = *(ulong *)(param_2 + 0x48);
          goto code_r0x022f2dec;
        }
      }
      else if (*pcVar9 == '\0') break;
      uVar8 = uVar8 + 1;
    } while (uVar8 < uVar6);
  }
  lVar7 = *(long *)(param_2 + 0x40);
  uVar6 = *(ulong *)(param_2 + 0x48);
  pcVar9 = (char *)(lVar7 + uVar6 * 0x18);
code_r0x022f2dec:
  if (pcVar9 == (char *)(lVar7 + uVar6 * 0x18)) {
    uVar4 = 0xfffffffffffffc38;
  }
  else {
    uVar8 = (ulong)((float)((ulong)*(uint *)(param_2 + 0x30) + (ulong)*(uint *)(param_2 + 0x34) + 1)
                   / *(float *)(param_2 + 0x2c));
    if (uVar6 < uVar8) {
      Aska::THashMap<char const*, int, Aska::Yayoi::SQLiteDriver::EntityObject::StringHasher, Aska::Yayoi::SQLiteDriver::EntityObject::StringEqualTo, Aska::TAllocator<Aska::TPair<char const* const, int> > >::Rehash_(unsigned long)(param_2 + 0x20,uVar8 << 1 | 1);
    }
    Aska::THashMap<char const*, int, Aska::Yayoi::SQLiteDriver::EntityObject::StringHasher, Aska::Yayoi::SQLiteDriver::EntityObject::StringEqualTo, Aska::TAllocator<Aska::TPair<char const* const, int> > >::Emplace_(char const* const&)(auStack_80,param_2 + 0x20,&uStack_88);
    uVar4 = 0xfffffffffffffc12;
    if (param_4 != 0) {
      uVar4 = 0xfffffffffffffc46;
    }
  }
  *param_1 = uVar4;
  return;
}

// ==== Aska::Yayoi::SQLiteDriver::EntityObject::GetTime(int, char*, unsigned long*, unsigned long)
// vaddr 0x21f2e88 | ghidra 0x22f2e88 | size 24 | symbol _ZN4Aska5Yayoi12SQLiteDriver12EntityObject7GetTimeEiPcPmm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi12SQLiteDriver12EntityObject7GetTimeEiPcPmm
               (undefined8 *param_1,undefined8 param_2,undefined8 param_3,long param_4)

{
  undefined8 uVar1;
  
  uVar1 = 0xfffffffffffffc12;
  if (param_4 != 0) {
    uVar1 = 0xfffffffffffffc46;
  }
  *param_1 = uVar1;
  return;
}

// ==== Aska::Yayoi::SQLiteDriver::EntityObject::GetData(char const*, char*, unsigned long*, unsigned long)
// vaddr 0x21f2ea0 | ghidra 0x22f2ea0 | size 436 | symbol _ZN4Aska5Yayoi12SQLiteDriver12EntityObject7GetDataEPKcPcPmm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi12SQLiteDriver12EntityObject7GetDataEPKcPcPmm
               (undefined8 *param_1,long param_2,undefined8 param_3,long param_4,long *param_5)

{
  ulong uVar1;
  long lVar2;
  int iVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  long lVar6;
  ulong uVar7;
  long lVar8;
  ulong uVar9;
  char *pcVar10;
  undefined8 uStack_90;
  long lStack_88;
  long alStack_80 [4];
  
  lVar8 = *(long *)(param_2 + 0x40);
  uVar7 = *(ulong *)(param_2 + 0x48);
  uStack_90 = param_3;
  uVar4 = strlen(param_3);
  lStack_88 = 0;
  alStack_80[0] = 0;
  Aska::detail::SpookyHashV2::Hash128(void const*, unsigned long, unsigned long*, unsigned long*)(param_3,uVar4,&lStack_88,alStack_80);
  lVar2 = lStack_88;
  if (uVar7 != 0) {
    uVar9 = 0;
    do {
      uVar1 = 0;
      if (uVar7 != 0) {
        uVar1 = (lVar2 + uVar9) / uVar7;
      }
      lVar6 = (lVar2 + uVar9) - uVar1 * uVar7;
      pcVar10 = (char *)(lVar8 + lVar6 * 0x18);
      if (*pcVar10 == '\x01') {
        iVar3 = strcmp(*(undefined8 *)(lVar8 + lVar6 * 0x18 + 8),param_3);
        if (iVar3 == 0) {
          lVar8 = *(long *)(param_2 + 0x40);
          uVar7 = *(ulong *)(param_2 + 0x48);
          goto code_r0x022f2f58;
        }
      }
      else if (*pcVar10 == '\0') break;
      uVar9 = uVar9 + 1;
    } while (uVar9 < uVar7);
  }
  lVar8 = *(long *)(param_2 + 0x40);
  uVar7 = *(ulong *)(param_2 + 0x48);
  pcVar10 = (char *)(lVar8 + uVar7 * 0x18);
code_r0x022f2f58:
  if (pcVar10 == (char *)(lVar8 + uVar7 * 0x18)) {
    uVar4 = 0xfffffffffffffc38;
  }
  else {
    uVar9 = (ulong)((float)((ulong)*(uint *)(param_2 + 0x30) + (ulong)*(uint *)(param_2 + 0x34) + 1)
                   / *(float *)(param_2 + 0x2c));
    if (uVar7 < uVar9) {
      Aska::THashMap<char const*, int, Aska::Yayoi::SQLiteDriver::EntityObject::StringHasher, Aska::Yayoi::SQLiteDriver::EntityObject::StringEqualTo, Aska::TAllocator<Aska::TPair<char const* const, int> > >::Rehash_(unsigned long)(param_2 + 0x20,uVar9 << 1 | 1);
    }
    Aska::THashMap<char const*, int, Aska::Yayoi::SQLiteDriver::EntityObject::StringHasher, Aska::Yayoi::SQLiteDriver::EntityObject::StringEqualTo, Aska::TAllocator<Aska::TPair<char const* const, int> > >::Emplace_(char const* const&)(alStack_80,param_2 + 0x20,&uStack_90);
    if (param_4 == 0) {
      uVar4 = 0xfffffffffffffc12;
    }
    else if (*(long *)(param_2 + 0x50) == 0) {
      uVar4 = 0xfffffffffffffc4d;
    }
    else {
      uVar4 = sqlite3_column_value(*(long *)(param_2 + 0x50),*(undefined4 *)(alStack_80[0] + 0x10));
      iVar3 = sqlite3_value_type();
      if (iVar3 == 5) {
        uVar4 = 0xfffffffffffffc71;
      }
      else {
        uVar5 = sqlite3_value_blob(uVar4);
        iVar3 = sqlite3_value_bytes(uVar4);
        memcpy(param_4,uVar5,(long)iVar3);
        uVar4 = 0;
        *param_5 = (long)iVar3;
      }
    }
  }
  *param_1 = uVar4;
  return;
}

// ==== Aska::Yayoi::SQLiteDriver::EntityObject::GetData(int, char*, unsigned long*, unsigned long)
// vaddr 0x21f3054 | ghidra 0x22f3054 | size 148 | symbol _ZN4Aska5Yayoi12SQLiteDriver12EntityObject7GetDataEiPcPmm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi12SQLiteDriver12EntityObject7GetDataEiPcPmm
               (undefined8 *param_1,long param_2,undefined8 param_3,long param_4,long *param_5)

{
  int iVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  
  if (param_4 == 0) {
    uVar2 = 0xfffffffffffffc12;
  }
  else if (*(long *)(param_2 + 0x50) == 0) {
    uVar2 = 0xfffffffffffffc4d;
  }
  else {
    uVar2 = sqlite3_column_value();
    iVar1 = sqlite3_value_type();
    if (iVar1 == 5) {
      uVar2 = 0xfffffffffffffc71;
    }
    else {
      uVar3 = sqlite3_value_blob(uVar2);
      iVar1 = sqlite3_value_bytes(uVar2);
      memcpy(param_4,uVar3,(long)iVar1);
      uVar2 = 0;
      *param_5 = (long)iVar1;
    }
  }
  *param_1 = uVar2;
  return;
}

// ==== Aska::Yayoi::SQLiteDriver::EntityObject::GetString(char const*, char*, unsigned long*, unsigned long)
// vaddr 0x21f30e8 | ghidra 0x22f30e8 | size 436 | symbol _ZN4Aska5Yayoi12SQLiteDriver12EntityObject9GetStringEPKcPcPmm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi12SQLiteDriver12EntityObject9GetStringEPKcPcPmm
               (undefined8 *param_1,long param_2,undefined8 param_3,long param_4,long *param_5)

{
  ulong uVar1;
  long lVar2;
  int iVar3;
  undefined8 uVar4;
  long lVar5;
  ulong uVar6;
  long lVar7;
  ulong uVar8;
  char *pcVar9;
  undefined8 uStack_90;
  long lStack_88;
  long alStack_80 [4];
  
  lVar7 = *(long *)(param_2 + 0x40);
  uVar6 = *(ulong *)(param_2 + 0x48);
  uStack_90 = param_3;
  uVar4 = strlen(param_3);
  lStack_88 = 0;
  alStack_80[0] = 0;
  Aska::detail::SpookyHashV2::Hash128(void const*, unsigned long, unsigned long*, unsigned long*)(param_3,uVar4,&lStack_88,alStack_80);
  lVar2 = lStack_88;
  if (uVar6 != 0) {
    uVar8 = 0;
    do {
      uVar1 = 0;
      if (uVar6 != 0) {
        uVar1 = (lVar2 + uVar8) / uVar6;
      }
      lVar5 = (lVar2 + uVar8) - uVar1 * uVar6;
      pcVar9 = (char *)(lVar7 + lVar5 * 0x18);
      if (*pcVar9 == '\x01') {
        iVar3 = strcmp(*(undefined8 *)(lVar7 + lVar5 * 0x18 + 8),param_3);
        if (iVar3 == 0) {
          lVar7 = *(long *)(param_2 + 0x40);
          uVar6 = *(ulong *)(param_2 + 0x48);
          goto code_r0x022f31a0;
        }
      }
      else if (*pcVar9 == '\0') break;
      uVar8 = uVar8 + 1;
    } while (uVar8 < uVar6);
  }
  lVar7 = *(long *)(param_2 + 0x40);
  uVar6 = *(ulong *)(param_2 + 0x48);
  pcVar9 = (char *)(lVar7 + uVar6 * 0x18);
code_r0x022f31a0:
  if (pcVar9 == (char *)(lVar7 + uVar6 * 0x18)) {
    uVar4 = 0xfffffffffffffc38;
  }
  else {
    uVar8 = (ulong)((float)((ulong)*(uint *)(param_2 + 0x30) + (ulong)*(uint *)(param_2 + 0x34) + 1)
                   / *(float *)(param_2 + 0x2c));
    if (uVar6 < uVar8) {
      Aska::THashMap<char const*, int, Aska::Yayoi::SQLiteDriver::EntityObject::StringHasher, Aska::Yayoi::SQLiteDriver::EntityObject::StringEqualTo, Aska::TAllocator<Aska::TPair<char const* const, int> > >::Rehash_(unsigned long)(param_2 + 0x20,uVar8 << 1 | 1);
    }
    Aska::THashMap<char const*, int, Aska::Yayoi::SQLiteDriver::EntityObject::StringHasher, Aska::Yayoi::SQLiteDriver::EntityObject::StringEqualTo, Aska::TAllocator<Aska::TPair<char const* const, int> > >::Emplace_(char const* const&)(alStack_80,param_2 + 0x20,&uStack_90);
    if (param_4 == 0) {
      uVar4 = 0xfffffffffffffc12;
    }
    else if (*(long *)(param_2 + 0x50) == 0) {
      uVar4 = 0xfffffffffffffc4d;
    }
    else {
      uVar4 = sqlite3_column_value(*(long *)(param_2 + 0x50),*(undefined4 *)(alStack_80[0] + 0x10));
      iVar3 = sqlite3_value_type();
      if (iVar3 == 5) {
        uVar4 = 0xfffffffffffffc71;
      }
      else {
        uVar4 = sqlite3_value_text(uVar4);
        iVar3 = __aska_snprintf_s(char*, unsigned long, unsigned long, char const*, ...)(param_4,*param_5,0xffffffffffffffff,&UNK_027f6a37/*"%s"*/,uVar4);
        uVar4 = 0;
        *param_5 = (long)iVar3;
      }
    }
  }
  *param_1 = uVar4;
  return;
}

// ==== Aska::Yayoi::SQLiteDriver::EntityObject::GetString(int, char*, unsigned long*, unsigned long)
// vaddr 0x21f329c | ghidra 0x22f329c | size 148 | symbol _ZN4Aska5Yayoi12SQLiteDriver12EntityObject9GetStringEiPcPmm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi12SQLiteDriver12EntityObject9GetStringEiPcPmm
               (undefined8 *param_1,long param_2,undefined8 param_3,long param_4,long *param_5)

{
  int iVar1;
  undefined8 uVar2;
  
  if (param_4 == 0) {
    uVar2 = 0xfffffffffffffc12;
  }
  else if (*(long *)(param_2 + 0x50) == 0) {
    uVar2 = 0xfffffffffffffc4d;
  }
  else {
    uVar2 = sqlite3_column_value();
    iVar1 = sqlite3_value_type();
    if (iVar1 == 5) {
      uVar2 = 0xfffffffffffffc71;
    }
    else {
      uVar2 = sqlite3_value_text(uVar2);
      iVar1 = __aska_snprintf_s(char*, unsigned long, unsigned long, char const*, ...)(param_4,*param_5,0xffffffffffffffff,&UNK_027f6a37/*"%s"*/,uVar2);
      uVar2 = 0;
      *param_5 = (long)iVar1;
    }
  }
  *param_1 = uVar2;
  return;
}

// ==== Aska::Yayoi::SQLiteDriver::EntityObject::GetTinyInt(char const*, signed char*, unsigned long)
// vaddr 0x21f3330 | ghidra 0x22f3330 | size 404 | symbol _ZN4Aska5Yayoi12SQLiteDriver12EntityObject10GetTinyIntEPKcPam | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi12SQLiteDriver12EntityObject10GetTinyIntEPKcPam
               (undefined8 *param_1,long param_2,undefined8 param_3,undefined1 *param_4)

{
  ulong uVar1;
  long lVar2;
  undefined1 uVar3;
  int iVar4;
  undefined8 uVar5;
  long lVar6;
  ulong uVar7;
  long lVar8;
  ulong uVar9;
  char *pcVar10;
  undefined8 uStack_88;
  long alStack_80 [4];
  long lStack_58;
  
  lVar8 = *(long *)(param_2 + 0x40);
  uVar7 = *(ulong *)(param_2 + 0x48);
  uStack_88 = param_3;
  uVar5 = strlen(param_3);
  alStack_80[0] = 0;
  lStack_58 = 0;
  Aska::detail::SpookyHashV2::Hash128(void const*, unsigned long, unsigned long*, unsigned long*)(param_3,uVar5,&lStack_58,alStack_80);
  lVar2 = lStack_58;
  if (uVar7 != 0) {
    uVar9 = 0;
    do {
      uVar1 = 0;
      if (uVar7 != 0) {
        uVar1 = (lVar2 + uVar9) / uVar7;
      }
      lVar6 = (lVar2 + uVar9) - uVar1 * uVar7;
      pcVar10 = (char *)(lVar8 + lVar6 * 0x18);
      if (*pcVar10 == '\x01') {
        iVar4 = strcmp(*(undefined8 *)(lVar8 + lVar6 * 0x18 + 8),param_3);
        if (iVar4 == 0) {
          lVar8 = *(long *)(param_2 + 0x40);
          uVar7 = *(ulong *)(param_2 + 0x48);
          goto code_r0x022f33e8;
        }
      }
      else if (*pcVar10 == '\0') break;
      uVar9 = uVar9 + 1;
    } while (uVar9 < uVar7);
  }
  lVar8 = *(long *)(param_2 + 0x40);
  uVar7 = *(ulong *)(param_2 + 0x48);
  pcVar10 = (char *)(lVar8 + uVar7 * 0x18);
code_r0x022f33e8:
  if (pcVar10 == (char *)(lVar8 + uVar7 * 0x18)) {
    uVar5 = 0xfffffffffffffc38;
  }
  else {
    uVar9 = (ulong)((float)((ulong)*(uint *)(param_2 + 0x30) + (ulong)*(uint *)(param_2 + 0x34) + 1)
                   / *(float *)(param_2 + 0x2c));
    if (uVar7 < uVar9) {
      Aska::THashMap<char const*, int, Aska::Yayoi::SQLiteDriver::EntityObject::StringHasher, Aska::Yayoi::SQLiteDriver::EntityObject::StringEqualTo, Aska::TAllocator<Aska::TPair<char const* const, int> > >::Rehash_(unsigned long)(param_2 + 0x20,uVar9 << 1 | 1);
    }
    Aska::THashMap<char const*, int, Aska::Yayoi::SQLiteDriver::EntityObject::StringHasher, Aska::Yayoi::SQLiteDriver::EntityObject::StringEqualTo, Aska::TAllocator<Aska::TPair<char const* const, int> > >::Emplace_(char const* const&)(alStack_80,param_2 + 0x20,&uStack_88);
    if (param_4 == (undefined1 *)0x0) {
      uVar5 = 0xfffffffffffffc12;
    }
    else if (*(long *)(param_2 + 0x50) == 0) {
      uVar5 = 0xfffffffffffffc4d;
    }
    else {
      uVar5 = sqlite3_column_value(*(long *)(param_2 + 0x50),*(undefined4 *)(alStack_80[0] + 0x10));
      iVar4 = sqlite3_value_type();
      if (iVar4 == 5) {
        uVar5 = 0xfffffffffffffc71;
      }
      else {
        uVar3 = sqlite3_value_int(uVar5);
        uVar5 = 0;
        *param_4 = uVar3;
      }
    }
  }
  *param_1 = uVar5;
  return;
}

// ==== Aska::Yayoi::SQLiteDriver::EntityObject::GetTinyInt(int, signed char*, unsigned long)
// vaddr 0x21f34c4 | ghidra 0x22f34c4 | size 104 | symbol _ZN4Aska5Yayoi12SQLiteDriver12EntityObject10GetTinyIntEiPam | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi12SQLiteDriver12EntityObject10GetTinyIntEiPam
               (undefined8 *param_1,long param_2,undefined8 param_3,undefined1 *param_4)

{
  undefined1 uVar1;
  int iVar2;
  undefined8 uVar3;
  
  if (param_4 == (undefined1 *)0x0) {
    uVar3 = 0xfffffffffffffc12;
  }
  else if (*(long *)(param_2 + 0x50) == 0) {
    uVar3 = 0xfffffffffffffc4d;
  }
  else {
    uVar3 = sqlite3_column_value();
    iVar2 = sqlite3_value_type();
    if (iVar2 == 5) {
      uVar3 = 0xfffffffffffffc71;
    }
    else {
      uVar1 = sqlite3_value_int(uVar3);
      uVar3 = 0;
      *param_4 = uVar1;
    }
  }
  *param_1 = uVar3;
  return;
}

// ==== Aska::Yayoi::SQLiteDriver::EntityObject::GetInteger(char const*, int*, unsigned long)
// vaddr 0x21f352c | ghidra 0x22f352c | size 404 | symbol _ZN4Aska5Yayoi12SQLiteDriver12EntityObject10GetIntegerEPKcPim | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi12SQLiteDriver12EntityObject10GetIntegerEPKcPim
               (undefined8 *param_1,long param_2,undefined8 param_3,undefined4 *param_4)

{
  ulong uVar1;
  long lVar2;
  int iVar3;
  undefined4 uVar4;
  undefined8 uVar5;
  long lVar6;
  ulong uVar7;
  long lVar8;
  ulong uVar9;
  char *pcVar10;
  undefined8 uStack_88;
  long alStack_80 [4];
  long lStack_58;
  
  lVar8 = *(long *)(param_2 + 0x40);
  uVar7 = *(ulong *)(param_2 + 0x48);
  uStack_88 = param_3;
  uVar5 = strlen(param_3);
  alStack_80[0] = 0;
  lStack_58 = 0;
  Aska::detail::SpookyHashV2::Hash128(void const*, unsigned long, unsigned long*, unsigned long*)(param_3,uVar5,&lStack_58,alStack_80);
  lVar2 = lStack_58;
  if (uVar7 != 0) {
    uVar9 = 0;
    do {
      uVar1 = 0;
      if (uVar7 != 0) {
        uVar1 = (lVar2 + uVar9) / uVar7;
      }
      lVar6 = (lVar2 + uVar9) - uVar1 * uVar7;
      pcVar10 = (char *)(lVar8 + lVar6 * 0x18);
      if (*pcVar10 == '\x01') {
        iVar3 = strcmp(*(undefined8 *)(lVar8 + lVar6 * 0x18 + 8),param_3);
        if (iVar3 == 0) {
          lVar8 = *(long *)(param_2 + 0x40);
          uVar7 = *(ulong *)(param_2 + 0x48);
          goto code_r0x022f35e4;
        }
      }
      else if (*pcVar10 == '\0') break;
      uVar9 = uVar9 + 1;
    } while (uVar9 < uVar7);
  }
  lVar8 = *(long *)(param_2 + 0x40);
  uVar7 = *(ulong *)(param_2 + 0x48);
  pcVar10 = (char *)(lVar8 + uVar7 * 0x18);
code_r0x022f35e4:
  if (pcVar10 == (char *)(lVar8 + uVar7 * 0x18)) {
    uVar5 = 0xfffffffffffffc38;
  }
  else {
    uVar9 = (ulong)((float)((ulong)*(uint *)(param_2 + 0x30) + (ulong)*(uint *)(param_2 + 0x34) + 1)
                   / *(float *)(param_2 + 0x2c));
    if (uVar7 < uVar9) {
      Aska::THashMap<char const*, int, Aska::Yayoi::SQLiteDriver::EntityObject::StringHasher, Aska::Yayoi::SQLiteDriver::EntityObject::StringEqualTo, Aska::TAllocator<Aska::TPair<char const* const, int> > >::Rehash_(unsigned long)(param_2 + 0x20,uVar9 << 1 | 1);
    }
    Aska::THashMap<char const*, int, Aska::Yayoi::SQLiteDriver::EntityObject::StringHasher, Aska::Yayoi::SQLiteDriver::EntityObject::StringEqualTo, Aska::TAllocator<Aska::TPair<char const* const, int> > >::Emplace_(char const* const&)(alStack_80,param_2 + 0x20,&uStack_88);
    if (param_4 == (undefined4 *)0x0) {
      uVar5 = 0xfffffffffffffc12;
    }
    else if (*(long *)(param_2 + 0x50) == 0) {
      uVar5 = 0xfffffffffffffc4d;
    }
    else {
      uVar5 = sqlite3_column_value(*(long *)(param_2 + 0x50),*(undefined4 *)(alStack_80[0] + 0x10));
      iVar3 = sqlite3_value_type();
      if (iVar3 == 5) {
        uVar5 = 0xfffffffffffffc71;
      }
      else {
        uVar4 = sqlite3_value_int(uVar5);
        uVar5 = 0;
        *param_4 = uVar4;
      }
    }
  }
  *param_1 = uVar5;
  return;
}

// ==== Aska::Yayoi::SQLiteDriver::EntityObject::GetInteger(int, int*, unsigned long)
// vaddr 0x21f36c0 | ghidra 0x22f36c0 | size 104 | symbol _ZN4Aska5Yayoi12SQLiteDriver12EntityObject10GetIntegerEiPim | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi12SQLiteDriver12EntityObject10GetIntegerEiPim
               (undefined8 *param_1,long param_2,undefined8 param_3,undefined4 *param_4)

{
  int iVar1;
  undefined4 uVar2;
  undefined8 uVar3;
  
  if (param_4 == (undefined4 *)0x0) {
    uVar3 = 0xfffffffffffffc12;
  }
  else if (*(long *)(param_2 + 0x50) == 0) {
    uVar3 = 0xfffffffffffffc4d;
  }
  else {
    uVar3 = sqlite3_column_value();
    iVar1 = sqlite3_value_type();
    if (iVar1 == 5) {
      uVar3 = 0xfffffffffffffc71;
    }
    else {
      uVar2 = sqlite3_value_int(uVar3);
      uVar3 = 0;
      *param_4 = uVar2;
    }
  }
  *param_1 = uVar3;
  return;
}

// ==== Aska::Yayoi::SQLiteDriver::EntityObject::GetLong(char const*, long*, unsigned long)
// vaddr 0x21f3728 | ghidra 0x22f3728 | size 404 | symbol _ZN4Aska5Yayoi12SQLiteDriver12EntityObject7GetLongEPKcPlm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi12SQLiteDriver12EntityObject7GetLongEPKcPlm
               (undefined8 *param_1,long param_2,undefined8 param_3,undefined8 *param_4)

{
  ulong uVar1;
  long lVar2;
  int iVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  long lVar6;
  ulong uVar7;
  long lVar8;
  ulong uVar9;
  char *pcVar10;
  undefined8 uStack_88;
  long alStack_80 [4];
  long lStack_58;
  
  lVar8 = *(long *)(param_2 + 0x40);
  uVar7 = *(ulong *)(param_2 + 0x48);
  uStack_88 = param_3;
  uVar4 = strlen(param_3);
  alStack_80[0] = 0;
  lStack_58 = 0;
  Aska::detail::SpookyHashV2::Hash128(void const*, unsigned long, unsigned long*, unsigned long*)(param_3,uVar4,&lStack_58,alStack_80);
  lVar2 = lStack_58;
  if (uVar7 != 0) {
    uVar9 = 0;
    do {
      uVar1 = 0;
      if (uVar7 != 0) {
        uVar1 = (lVar2 + uVar9) / uVar7;
      }
      lVar6 = (lVar2 + uVar9) - uVar1 * uVar7;
      pcVar10 = (char *)(lVar8 + lVar6 * 0x18);
      if (*pcVar10 == '\x01') {
        iVar3 = strcmp(*(undefined8 *)(lVar8 + lVar6 * 0x18 + 8),param_3);
        if (iVar3 == 0) {
          lVar8 = *(long *)(param_2 + 0x40);
          uVar7 = *(ulong *)(param_2 + 0x48);
          goto code_r0x022f37e0;
        }
      }
      else if (*pcVar10 == '\0') break;
      uVar9 = uVar9 + 1;
    } while (uVar9 < uVar7);
  }
  lVar8 = *(long *)(param_2 + 0x40);
  uVar7 = *(ulong *)(param_2 + 0x48);
  pcVar10 = (char *)(lVar8 + uVar7 * 0x18);
code_r0x022f37e0:
  if (pcVar10 == (char *)(lVar8 + uVar7 * 0x18)) {
    uVar4 = 0xfffffffffffffc38;
  }
  else {
    uVar9 = (ulong)((float)((ulong)*(uint *)(param_2 + 0x30) + (ulong)*(uint *)(param_2 + 0x34) + 1)
                   / *(float *)(param_2 + 0x2c));
    if (uVar7 < uVar9) {
      Aska::THashMap<char const*, int, Aska::Yayoi::SQLiteDriver::EntityObject::StringHasher, Aska::Yayoi::SQLiteDriver::EntityObject::StringEqualTo, Aska::TAllocator<Aska::TPair<char const* const, int> > >::Rehash_(unsigned long)(param_2 + 0x20,uVar9 << 1 | 1);
    }
    Aska::THashMap<char const*, int, Aska::Yayoi::SQLiteDriver::EntityObject::StringHasher, Aska::Yayoi::SQLiteDriver::EntityObject::StringEqualTo, Aska::TAllocator<Aska::TPair<char const* const, int> > >::Emplace_(char const* const&)(alStack_80,param_2 + 0x20,&uStack_88);
    if (param_4 == (undefined8 *)0x0) {
      uVar4 = 0xfffffffffffffc12;
    }
    else if (*(long *)(param_2 + 0x50) == 0) {
      uVar4 = 0xfffffffffffffc4d;
    }
    else {
      uVar4 = sqlite3_column_value(*(long *)(param_2 + 0x50),*(undefined4 *)(alStack_80[0] + 0x10));
      iVar3 = sqlite3_value_type();
      if (iVar3 == 5) {
        uVar4 = 0xfffffffffffffc71;
      }
      else {
        uVar5 = sqlite3_value_int64(uVar4);
        uVar4 = 0;
        *param_4 = uVar5;
      }
    }
  }
  *param_1 = uVar4;
  return;
}

// ==== Aska::Yayoi::SQLiteDriver::EntityObject::GetLong(int, long*, unsigned long)
// vaddr 0x21f38bc | ghidra 0x22f38bc | size 104 | symbol _ZN4Aska5Yayoi12SQLiteDriver12EntityObject7GetLongEiPlm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi12SQLiteDriver12EntityObject7GetLongEiPlm
               (undefined8 *param_1,long param_2,undefined8 param_3,undefined8 *param_4)

{
  int iVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  
  if (param_4 == (undefined8 *)0x0) {
    uVar2 = 0xfffffffffffffc12;
  }
  else if (*(long *)(param_2 + 0x50) == 0) {
    uVar2 = 0xfffffffffffffc4d;
  }
  else {
    uVar2 = sqlite3_column_value();
    iVar1 = sqlite3_value_type();
    if (iVar1 == 5) {
      uVar2 = 0xfffffffffffffc71;
    }
    else {
      uVar3 = sqlite3_value_int64(uVar2);
      uVar2 = 0;
      *param_4 = uVar3;
    }
  }
  *param_1 = uVar2;
  return;
}

// ==== Aska::Yayoi::SQLiteDriver::EntityObject::GetFloat(char const*, float*, unsigned long)
// vaddr 0x21f3924 | ghidra 0x22f3924 | size 408 | symbol _ZN4Aska5Yayoi12SQLiteDriver12EntityObject8GetFloatEPKcPfm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi12SQLiteDriver12EntityObject8GetFloatEPKcPfm
               (undefined8 *param_1,long param_2,undefined8 param_3,float *param_4)

{
  ulong uVar1;
  double dVar2;
  long lVar3;
  int iVar4;
  undefined8 uVar5;
  long lVar6;
  ulong uVar7;
  long lVar8;
  ulong uVar9;
  char *pcVar10;
  undefined8 uStack_88;
  long alStack_80 [4];
  long lStack_58;
  
  lVar8 = *(long *)(param_2 + 0x40);
  uVar7 = *(ulong *)(param_2 + 0x48);
  uStack_88 = param_3;
  uVar5 = strlen(param_3);
  alStack_80[0] = 0;
  lStack_58 = 0;
  Aska::detail::SpookyHashV2::Hash128(void const*, unsigned long, unsigned long*, unsigned long*)(param_3,uVar5,&lStack_58,alStack_80);
  lVar3 = lStack_58;
  if (uVar7 != 0) {
    uVar9 = 0;
    do {
      uVar1 = 0;
      if (uVar7 != 0) {
        uVar1 = (lVar3 + uVar9) / uVar7;
      }
      lVar6 = (lVar3 + uVar9) - uVar1 * uVar7;
      pcVar10 = (char *)(lVar8 + lVar6 * 0x18);
      if (*pcVar10 == '\x01') {
        iVar4 = strcmp(*(undefined8 *)(lVar8 + lVar6 * 0x18 + 8),param_3);
        if (iVar4 == 0) {
          lVar8 = *(long *)(param_2 + 0x40);
          uVar7 = *(ulong *)(param_2 + 0x48);
          goto code_r0x022f39dc;
        }
      }
      else if (*pcVar10 == '\0') break;
      uVar9 = uVar9 + 1;
    } while (uVar9 < uVar7);
  }
  lVar8 = *(long *)(param_2 + 0x40);
  uVar7 = *(ulong *)(param_2 + 0x48);
  pcVar10 = (char *)(lVar8 + uVar7 * 0x18);
code_r0x022f39dc:
  if (pcVar10 == (char *)(lVar8 + uVar7 * 0x18)) {
    uVar5 = 0xfffffffffffffc38;
  }
  else {
    uVar9 = (ulong)((float)((ulong)*(uint *)(param_2 + 0x30) + (ulong)*(uint *)(param_2 + 0x34) + 1)
                   / *(float *)(param_2 + 0x2c));
    if (uVar7 < uVar9) {
      Aska::THashMap<char const*, int, Aska::Yayoi::SQLiteDriver::EntityObject::StringHasher, Aska::Yayoi::SQLiteDriver::EntityObject::StringEqualTo, Aska::TAllocator<Aska::TPair<char const* const, int> > >::Rehash_(unsigned long)(param_2 + 0x20,uVar9 << 1 | 1);
    }
    Aska::THashMap<char const*, int, Aska::Yayoi::SQLiteDriver::EntityObject::StringHasher, Aska::Yayoi::SQLiteDriver::EntityObject::StringEqualTo, Aska::TAllocator<Aska::TPair<char const* const, int> > >::Emplace_(char const* const&)(alStack_80,param_2 + 0x20,&uStack_88);
    if (param_4 == (float *)0x0) {
      uVar5 = 0xfffffffffffffc12;
    }
    else if (*(long *)(param_2 + 0x50) == 0) {
      uVar5 = 0xfffffffffffffc4d;
    }
    else {
      uVar5 = sqlite3_column_value(*(long *)(param_2 + 0x50),*(undefined4 *)(alStack_80[0] + 0x10));
      iVar4 = sqlite3_value_type();
      if (iVar4 == 5) {
        uVar5 = 0xfffffffffffffc71;
      }
      else {
        dVar2 = (double)sqlite3_value_double(uVar5);
        uVar5 = 0;
        *param_4 = (float)dVar2;
      }
    }
  }
  *param_1 = uVar5;
  return;
}

// ==== Aska::Yayoi::SQLiteDriver::EntityObject::GetFloat(int, float*, unsigned long)
// vaddr 0x21f3abc | ghidra 0x22f3abc | size 108 | symbol _ZN4Aska5Yayoi12SQLiteDriver12EntityObject8GetFloatEiPfm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi12SQLiteDriver12EntityObject8GetFloatEiPfm
               (undefined8 *param_1,long param_2,undefined8 param_3,float *param_4)

{
  double dVar1;
  int iVar2;
  undefined8 uVar3;
  
  if (param_4 == (float *)0x0) {
    uVar3 = 0xfffffffffffffc12;
  }
  else if (*(long *)(param_2 + 0x50) == 0) {
    uVar3 = 0xfffffffffffffc4d;
  }
  else {
    uVar3 = sqlite3_column_value();
    iVar2 = sqlite3_value_type();
    if (iVar2 == 5) {
      uVar3 = 0xfffffffffffffc71;
    }
    else {
      dVar1 = (double)sqlite3_value_double(uVar3);
      uVar3 = 0;
      *param_4 = (float)dVar1;
    }
  }
  *param_1 = uVar3;
  return;
}

// ==== Aska::Yayoi::SQLiteDriver::EntityObject::GetDouble(char const*, double*, unsigned long)
// vaddr 0x21f3b28 | ghidra 0x22f3b28 | size 404 | symbol _ZN4Aska5Yayoi12SQLiteDriver12EntityObject9GetDoubleEPKcPdm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi12SQLiteDriver12EntityObject9GetDoubleEPKcPdm
               (undefined8 *param_1,long param_2,undefined8 param_3,undefined8 *param_4)

{
  ulong uVar1;
  undefined8 uVar2;
  long lVar3;
  int iVar4;
  undefined8 uVar5;
  long lVar6;
  ulong uVar7;
  long lVar8;
  ulong uVar9;
  char *pcVar10;
  undefined8 uStack_88;
  long alStack_80 [4];
  long lStack_58;
  
  lVar8 = *(long *)(param_2 + 0x40);
  uVar7 = *(ulong *)(param_2 + 0x48);
  uStack_88 = param_3;
  uVar5 = strlen(param_3);
  alStack_80[0] = 0;
  lStack_58 = 0;
  Aska::detail::SpookyHashV2::Hash128(void const*, unsigned long, unsigned long*, unsigned long*)(param_3,uVar5,&lStack_58,alStack_80);
  lVar3 = lStack_58;
  if (uVar7 != 0) {
    uVar9 = 0;
    do {
      uVar1 = 0;
      if (uVar7 != 0) {
        uVar1 = (lVar3 + uVar9) / uVar7;
      }
      lVar6 = (lVar3 + uVar9) - uVar1 * uVar7;
      pcVar10 = (char *)(lVar8 + lVar6 * 0x18);
      if (*pcVar10 == '\x01') {
        iVar4 = strcmp(*(undefined8 *)(lVar8 + lVar6 * 0x18 + 8),param_3);
        if (iVar4 == 0) {
          lVar8 = *(long *)(param_2 + 0x40);
          uVar7 = *(ulong *)(param_2 + 0x48);
          goto code_r0x022f3be0;
        }
      }
      else if (*pcVar10 == '\0') break;
      uVar9 = uVar9 + 1;
    } while (uVar9 < uVar7);
  }
  lVar8 = *(long *)(param_2 + 0x40);
  uVar7 = *(ulong *)(param_2 + 0x48);
  pcVar10 = (char *)(lVar8 + uVar7 * 0x18);
code_r0x022f3be0:
  if (pcVar10 == (char *)(lVar8 + uVar7 * 0x18)) {
    uVar5 = 0xfffffffffffffc38;
  }
  else {
    uVar9 = (ulong)((float)((ulong)*(uint *)(param_2 + 0x30) + (ulong)*(uint *)(param_2 + 0x34) + 1)
                   / *(float *)(param_2 + 0x2c));
    if (uVar7 < uVar9) {
      Aska::THashMap<char const*, int, Aska::Yayoi::SQLiteDriver::EntityObject::StringHasher, Aska::Yayoi::SQLiteDriver::EntityObject::StringEqualTo, Aska::TAllocator<Aska::TPair<char const* const, int> > >::Rehash_(unsigned long)(param_2 + 0x20,uVar9 << 1 | 1);
    }
    Aska::THashMap<char const*, int, Aska::Yayoi::SQLiteDriver::EntityObject::StringHasher, Aska::Yayoi::SQLiteDriver::EntityObject::StringEqualTo, Aska::TAllocator<Aska::TPair<char const* const, int> > >::Emplace_(char const* const&)(alStack_80,param_2 + 0x20,&uStack_88);
    if (param_4 == (undefined8 *)0x0) {
      uVar5 = 0xfffffffffffffc12;
    }
    else if (*(long *)(param_2 + 0x50) == 0) {
      uVar5 = 0xfffffffffffffc4d;
    }
    else {
      uVar5 = sqlite3_column_value(*(long *)(param_2 + 0x50),*(undefined4 *)(alStack_80[0] + 0x10));
      iVar4 = sqlite3_value_type();
      if (iVar4 == 5) {
        uVar5 = 0xfffffffffffffc71;
      }
      else {
        uVar2 = sqlite3_value_double(uVar5);
        uVar5 = 0;
        *param_4 = uVar2;
      }
    }
  }
  *param_1 = uVar5;
  return;
}

// ==== Aska::Yayoi::SQLiteDriver::EntityObject::GetDouble(int, double*, unsigned long)
// vaddr 0x21f3cbc | ghidra 0x22f3cbc | size 104 | symbol _ZN4Aska5Yayoi12SQLiteDriver12EntityObject9GetDoubleEiPdm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi12SQLiteDriver12EntityObject9GetDoubleEiPdm
               (undefined8 *param_1,long param_2,undefined8 param_3,undefined8 *param_4)

{
  int iVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  
  if (param_4 == (undefined8 *)0x0) {
    uVar2 = 0xfffffffffffffc12;
  }
  else if (*(long *)(param_2 + 0x50) == 0) {
    uVar2 = 0xfffffffffffffc4d;
  }
  else {
    uVar2 = sqlite3_column_value();
    iVar1 = sqlite3_value_type();
    if (iVar1 == 5) {
      uVar2 = 0xfffffffffffffc71;
    }
    else {
      uVar3 = sqlite3_value_double(uVar2);
      uVar2 = 0;
      *param_4 = uVar3;
    }
  }
  *param_1 = uVar2;
  return;
}

// ==== Aska::Yayoi::SQLiteDriver::EntityObject::GetShort(char const*, short*, unsigned long)
// vaddr 0x21f3d24 | ghidra 0x22f3d24 | size 404 | symbol _ZN4Aska5Yayoi12SQLiteDriver12EntityObject8GetShortEPKcPsm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi12SQLiteDriver12EntityObject8GetShortEPKcPsm
               (undefined8 *param_1,long param_2,undefined8 param_3,undefined2 *param_4)

{
  ulong uVar1;
  long lVar2;
  undefined2 uVar3;
  int iVar4;
  undefined8 uVar5;
  long lVar6;
  ulong uVar7;
  long lVar8;
  ulong uVar9;
  char *pcVar10;
  undefined8 uStack_88;
  long alStack_80 [4];
  long lStack_58;
  
  lVar8 = *(long *)(param_2 + 0x40);
  uVar7 = *(ulong *)(param_2 + 0x48);
  uStack_88 = param_3;
  uVar5 = strlen(param_3);
  alStack_80[0] = 0;
  lStack_58 = 0;
  Aska::detail::SpookyHashV2::Hash128(void const*, unsigned long, unsigned long*, unsigned long*)(param_3,uVar5,&lStack_58,alStack_80);
  lVar2 = lStack_58;
  if (uVar7 != 0) {
    uVar9 = 0;
    do {
      uVar1 = 0;
      if (uVar7 != 0) {
        uVar1 = (lVar2 + uVar9) / uVar7;
      }
      lVar6 = (lVar2 + uVar9) - uVar1 * uVar7;
      pcVar10 = (char *)(lVar8 + lVar6 * 0x18);
      if (*pcVar10 == '\x01') {
        iVar4 = strcmp(*(undefined8 *)(lVar8 + lVar6 * 0x18 + 8),param_3);
        if (iVar4 == 0) {
          lVar8 = *(long *)(param_2 + 0x40);
          uVar7 = *(ulong *)(param_2 + 0x48);
          goto code_r0x022f3ddc;
        }
      }
      else if (*pcVar10 == '\0') break;
      uVar9 = uVar9 + 1;
    } while (uVar9 < uVar7);
  }
  lVar8 = *(long *)(param_2 + 0x40);
  uVar7 = *(ulong *)(param_2 + 0x48);
  pcVar10 = (char *)(lVar8 + uVar7 * 0x18);
code_r0x022f3ddc:
  if (pcVar10 == (char *)(lVar8 + uVar7 * 0x18)) {
    uVar5 = 0xfffffffffffffc38;
  }
  else {
    uVar9 = (ulong)((float)((ulong)*(uint *)(param_2 + 0x30) + (ulong)*(uint *)(param_2 + 0x34) + 1)
                   / *(float *)(param_2 + 0x2c));
    if (uVar7 < uVar9) {
      Aska::THashMap<char const*, int, Aska::Yayoi::SQLiteDriver::EntityObject::StringHasher, Aska::Yayoi::SQLiteDriver::EntityObject::StringEqualTo, Aska::TAllocator<Aska::TPair<char const* const, int> > >::Rehash_(unsigned long)(param_2 + 0x20,uVar9 << 1 | 1);
    }
    Aska::THashMap<char const*, int, Aska::Yayoi::SQLiteDriver::EntityObject::StringHasher, Aska::Yayoi::SQLiteDriver::EntityObject::StringEqualTo, Aska::TAllocator<Aska::TPair<char const* const, int> > >::Emplace_(char const* const&)(alStack_80,param_2 + 0x20,&uStack_88);
    if (param_4 == (undefined2 *)0x0) {
      uVar5 = 0xfffffffffffffc12;
    }
    else if (*(long *)(param_2 + 0x50) == 0) {
      uVar5 = 0xfffffffffffffc4d;
    }
    else {
      uVar5 = sqlite3_column_value(*(long *)(param_2 + 0x50),*(undefined4 *)(alStack_80[0] + 0x10));
      iVar4 = sqlite3_value_type();
      if (iVar4 == 5) {
        uVar5 = 0xfffffffffffffc71;
      }
      else {
        uVar3 = sqlite3_value_int(uVar5);
        uVar5 = 0;
        *param_4 = uVar3;
      }
    }
  }
  *param_1 = uVar5;
  return;
}

// ==== Aska::Yayoi::SQLiteDriver::EntityObject::GetShort(int, short*, unsigned long)
// vaddr 0x21f3eb8 | ghidra 0x22f3eb8 | size 104 | symbol _ZN4Aska5Yayoi12SQLiteDriver12EntityObject8GetShortEiPsm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi12SQLiteDriver12EntityObject8GetShortEiPsm
               (undefined8 *param_1,long param_2,undefined8 param_3,undefined2 *param_4)

{
  undefined2 uVar1;
  int iVar2;
  undefined8 uVar3;
  
  if (param_4 == (undefined2 *)0x0) {
    uVar3 = 0xfffffffffffffc12;
  }
  else if (*(long *)(param_2 + 0x50) == 0) {
    uVar3 = 0xfffffffffffffc4d;
  }
  else {
    uVar3 = sqlite3_column_value();
    iVar2 = sqlite3_value_type();
    if (iVar2 == 5) {
      uVar3 = 0xfffffffffffffc71;
    }
    else {
      uVar1 = sqlite3_value_int(uVar3);
      uVar3 = 0;
      *param_4 = uVar1;
    }
  }
  *param_1 = uVar3;
  return;
}

// ==== Aska::Yayoi::SQLiteDriver::EntityObject::GetType(int, unsigned long)
// vaddr 0x21f3f20 | ghidra 0x22f3f20 | size 32 | symbol _ZN4Aska5Yayoi12SQLiteDriver12EntityObject7GetTypeEim | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska5Yayoi12SQLiteDriver12EntityObject7GetTypeEim(long param_1)

{
  undefined8 uVar1;
  
  if (*(long *)(param_1 + 0x50) != 0) {
    sqlite3_column_value();
    uVar1 = (*(code *)PTR_sqlite3_value_type_02cab148)();
    return uVar1;
  }
  return 0xfffffc4d;
}

// ==== Aska::Yayoi::SQLiteDriver::EntityObject::GetType(char const*, unsigned long)
// vaddr 0x21f3f40 | ghidra 0x22f3f40 | size 336 | symbol _ZN4Aska5Yayoi12SQLiteDriver12EntityObject7GetTypeEPKcm | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska5Yayoi12SQLiteDriver12EntityObject7GetTypeEPKcm(long param_1,undefined8 param_2)

{
  ulong uVar1;
  long lVar2;
  int iVar3;
  undefined8 uVar4;
  long lVar5;
  ulong uVar6;
  long lVar7;
  ulong uVar8;
  char *pcVar9;
  undefined8 uStack_78;
  long alStack_70 [4];
  long lStack_48;
  
  lVar7 = *(long *)(param_1 + 0x40);
  uVar6 = *(ulong *)(param_1 + 0x48);
  uStack_78 = param_2;
  uVar4 = strlen(param_2);
  alStack_70[0] = 0;
  lStack_48 = 0;
  Aska::detail::SpookyHashV2::Hash128(void const*, unsigned long, unsigned long*, unsigned long*)(param_2,uVar4,&lStack_48,alStack_70);
  lVar2 = lStack_48;
  if (uVar6 != 0) {
    uVar8 = 0;
    do {
      uVar1 = 0;
      if (uVar6 != 0) {
        uVar1 = (lVar2 + uVar8) / uVar6;
      }
      lVar5 = (lVar2 + uVar8) - uVar1 * uVar6;
      pcVar9 = (char *)(lVar7 + lVar5 * 0x18);
      if (*pcVar9 == '\x01') {
        iVar3 = strcmp(*(undefined8 *)(lVar7 + lVar5 * 0x18 + 8),param_2);
        if (iVar3 == 0) {
          lVar7 = *(long *)(param_1 + 0x40);
          uVar6 = *(ulong *)(param_1 + 0x48);
          goto code_r0x022f3fec;
        }
      }
      else if (*pcVar9 == '\0') break;
      uVar8 = uVar8 + 1;
    } while (uVar8 < uVar6);
  }
  lVar7 = *(long *)(param_1 + 0x40);
  uVar6 = *(ulong *)(param_1 + 0x48);
  pcVar9 = (char *)(lVar7 + uVar6 * 0x18);
code_r0x022f3fec:
  if (pcVar9 == (char *)(lVar7 + uVar6 * 0x18)) {
    uVar4 = 0xfffffc38;
  }
  else {
    uVar8 = (ulong)((float)((ulong)*(uint *)(param_1 + 0x30) + (ulong)*(uint *)(param_1 + 0x34) + 1)
                   / *(float *)(param_1 + 0x2c));
    if (uVar6 < uVar8) {
      Aska::THashMap<char const*, int, Aska::Yayoi::SQLiteDriver::EntityObject::StringHasher, Aska::Yayoi::SQLiteDriver::EntityObject::StringEqualTo, Aska::TAllocator<Aska::TPair<char const* const, int> > >::Rehash_(unsigned long)(param_1 + 0x20,uVar8 << 1 | 1);
    }
    Aska::THashMap<char const*, int, Aska::Yayoi::SQLiteDriver::EntityObject::StringHasher, Aska::Yayoi::SQLiteDriver::EntityObject::StringEqualTo, Aska::TAllocator<Aska::TPair<char const* const, int> > >::Emplace_(char const* const&)(alStack_70,param_1 + 0x20,&uStack_78);
    if (*(long *)(param_1 + 0x50) == 0) {
      uVar4 = 0xfffffc4d;
    }
    else {
      sqlite3_column_value(*(long *)(param_1 + 0x50),*(undefined4 *)(alStack_70[0] + 0x10));
      uVar4 = sqlite3_value_type();
    }
  }
  return uVar4;
}

// ==== Aska::Yayoi::SQLiteDriver::EntityObject::GetStringLength(int, unsigned long*, unsigned long)
// vaddr 0x21f4090 | ghidra 0x22f4090 | size 108 | symbol _ZN4Aska5Yayoi12SQLiteDriver12EntityObject15GetStringLengthEiPmm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi12SQLiteDriver12EntityObject15GetStringLengthEiPmm
               (undefined8 *param_1,long param_2,undefined8 param_3,undefined8 *param_4)

{
  int iVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  
  if (param_4 == (undefined8 *)0x0) {
    uVar2 = 0xfffffffffffffc12;
  }
  else if (*(long *)(param_2 + 0x50) == 0) {
    uVar2 = 0xfffffffffffffc4d;
  }
  else {
    uVar2 = sqlite3_column_value();
    iVar1 = sqlite3_value_type();
    if (iVar1 == 5) {
      uVar2 = 0xfffffffffffffc71;
    }
    else {
      sqlite3_value_text(uVar2);
      uVar3 = strlen();
      uVar2 = 0;
      *param_4 = uVar3;
    }
  }
  *param_1 = uVar2;
  return;
}

// ==== Aska::Yayoi::SQLiteDriver::EntityObject::Store(sqlite3*, sqlite3_stmt*)
// vaddr 0x21f40fc | ghidra 0x22f40fc | size 324 | symbol _ZN4Aska5Yayoi12SQLiteDriver12EntityObject5StoreEP7sqlite3P12sqlite3_stmt | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi12SQLiteDriver12EntityObject5StoreEP7sqlite3P12sqlite3_stmt
               (undefined8 *param_1,long param_2,long param_3,long param_4)

{
  int iVar1;
  char *pcVar2;
  ulong uVar3;
  long lVar4;
  int *piVar5;
  undefined8 uStack_58;
  long alStack_50 [4];
  
  if (*(long *)(param_2 + 0x50) != param_4) {
    *(long *)(param_2 + 0x50) = param_4;
    iVar1 = sqlite3_column_count(param_4);
    pcVar2 = *(char **)(param_2 + 0x40);
    *(int *)(param_2 + 8) = iVar1;
    if ((pcVar2 != (char *)0x0) && (*(long *)(param_2 + 0x48) != 0)) {
      lVar4 = *(long *)(param_2 + 0x48) * 0x18;
      do {
        piVar5 = (int *)(param_2 + 0x30);
        if ((*pcVar2 == '\x01') || (piVar5 = (int *)(param_2 + 0x34), *pcVar2 == '\x02')) {
          *piVar5 = *piVar5 + -1;
          *pcVar2 = '\0';
        }
        lVar4 = lVar4 + -0x18;
        pcVar2 = pcVar2 + 0x18;
      } while (lVar4 != 0);
      iVar1 = *(int *)(param_2 + 8);
    }
    *(undefined8 *)(param_2 + 0x30) = 0;
    if (0 < iVar1) {
      iVar1 = 0;
      do {
        uStack_58 = sqlite3_column_name(*(undefined8 *)(param_2 + 0x50),iVar1);
        uVar3 = (ulong)((float)((ulong)*(uint *)(param_2 + 0x30) + (ulong)*(uint *)(param_2 + 0x34)
                               + 1) / *(float *)(param_2 + 0x2c));
        if (*(ulong *)(param_2 + 0x48) < uVar3) {
          Aska::THashMap<char const*, int, Aska::Yayoi::SQLiteDriver::EntityObject::StringHasher, Aska::Yayoi::SQLiteDriver::EntityObject::StringEqualTo, Aska::TAllocator<Aska::TPair<char const* const, int> > >::Rehash_(unsigned long)(param_2 + 0x20,uVar3 << 1 | 1);
        }
        Aska::THashMap<char const*, int, Aska::Yayoi::SQLiteDriver::EntityObject::StringHasher, Aska::Yayoi::SQLiteDriver::EntityObject::StringEqualTo, Aska::TAllocator<Aska::TPair<char const* const, int> > >::Emplace_(char const* const&)(alStack_50,param_2 + 0x20,&uStack_58);
        *(int *)(alStack_50[0] + 0x10) = iVar1;
        iVar1 = iVar1 + 1;
      } while (iVar1 < *(int *)(param_2 + 8));
    }
  }
  if (*(long *)(param_2 + 0x58) != param_3) {
    *(long *)(param_2 + 0x58) = param_3;
  }
  *param_1 = 0;
  return;
}

// ==== Aska::Yayoi::SQLiteDriver::EntityObject::Fetch()
// vaddr 0x21f4240 | ghidra 0x22f4240 | size 124 | symbol _ZN4Aska5Yayoi12SQLiteDriver12EntityObject5FetchEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi12SQLiteDriver12EntityObject5FetchEv(undefined8 *param_1,long param_2)

{
  int iVar1;
  long lVar2;
  undefined8 uVar3;
  
  lVar2 = *(long *)(param_2 + 0x50);
  if (lVar2 == 0) {
    uVar3 = 0xfffffffffffffc4d;
  }
  else {
    while (iVar1 = sqlite3_step(lVar2), iVar1 < 100) {
      if (iVar1 != 5) {
        if (iVar1 != 1) goto code_r0x022f42a8;
        uVar3 = 0xffffffffffffffff;
        goto code_r0x022f42ac;
      }
      lVar2 = *(long *)(param_2 + 0x50);
    }
    if (iVar1 == 100) {
      uVar3 = 0;
    }
    else if (iVar1 == 0x65) {
      uVar3 = 0xfffffffffffffc56;
    }
    else {
code_r0x022f42a8:
      uVar3 = 0xfffffffffffffc00;
    }
  }
code_r0x022f42ac:
  *param_1 = uVar3;
  return;
}

// ==== Aska::Yayoi::SQLiteDriver::EntityObject::GetFieldLength(int, int)
// vaddr 0x21f42bc | ghidra 0x22f42bc | size 64 | symbol _ZN4Aska5Yayoi12SQLiteDriver12EntityObject14GetFieldLengthEii | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska5Yayoi12SQLiteDriver12EntityObject14GetFieldLengthEii(long param_1)

{
  int iVar1;
  undefined8 uVar2;
  
  if (*(long *)(param_1 + 0x50) != 0) {
    uVar2 = sqlite3_column_value();
    iVar1 = sqlite3_value_type();
    if (iVar1 != 5) {
      sqlite3_value_blob(uVar2);
      uVar2 = (*(code *)PTR_sqlite3_value_bytes_02cb65e0)(uVar2);
      return uVar2;
    }
  }
  return 0;
}

// ==== Aska::Yayoi::SQLiteDriver::EntityObject::Serialize(long*)
// vaddr 0x21f42fc | ghidra 0x22f42fc | size 2252 | symbol _ZN4Aska5Yayoi12SQLiteDriver12EntityObject9SerializeEPl | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Type propagation algorithm not settling */

void _ZN4Aska5Yayoi12SQLiteDriver12EntityObject9SerializeEPl
               (long *param_1,long param_2,long *param_3)

{
  int iVar1;
  ulong uVar2;
  uint uVar3;
  char cVar4;
  bool bVar5;
  int iVar6;
  uint uVar7;
  undefined4 uVar8;
  int iVar9;
  long lVar10;
  undefined8 uVar11;
  undefined1 *puVar12;
  int *piVar13;
  ulong uVar14;
  int **ppiVar15;
  char *pcVar16;
  char *pcVar17;
  char *pcVar18;
  ulong uVar19;
  long lVar20;
  int *piVar21;
  undefined4 *puVar22;
  ulong uVar23;
  ulong uVar24;
  ulong uVar25;
  ulong uVar26;
  int *piVar27;
  ulong uVar28;
  int *piStack_400;
  int *apiStack_3f8 [32];
  undefined1 auStack_2f8 [512];
  undefined1 auStack_f8 [88];
  undefined2 uStack_a0;
  undefined1 auStack_98 [8];
  long lStack_90;
  uint uStack_88;
  char cStack_70;
  long lStack_68;
  
  if (param_3 == (long *)0x0) {
code_r0x022f43e0:
    *param_1 = 0;
    param_1[1] = 0;
    return;
  }
  uVar3 = *(uint *)(param_2 + 8);
  sqlite3_reset(*(undefined8 *)(param_2 + 0x50));
  lVar10 = *(long *)(param_2 + 0x50);
  if (lVar10 == 0) {
    uVar23 = 0;
    sqlite3_reset();
  }
  else {
    uVar23 = 0;
    do {
      while (iVar6 = sqlite3_step(lVar10), iVar6 == 5) {
        lVar10 = *(long *)(param_2 + 0x50);
      }
      if (iVar6 != 100) {
        uVar11 = *(undefined8 *)(param_2 + 0x50);
        goto code_r0x022f4370;
      }
      lVar10 = *(long *)(param_2 + 0x50);
      uVar23 = uVar23 + 1;
    } while (lVar10 != 0);
    uVar11 = 0;
code_r0x022f4370:
    sqlite3_reset(uVar11);
  }
  if ((uVar3 == 0) || (uVar23 == 0)) {
    *param_3 = -0x3a4;
    goto code_r0x022f43e0;
  }
  lStack_68 = 0;
  Aska::ASON::ASON()(auStack_f8);
  if (uVar3 < 0x41) {
    puVar12 = auStack_2f8;
    iVar6 = *(int *)(param_2 + 0x30);
joined_r0x022f4418:
    if (iVar6 != 0) {
      pcVar18 = *(char **)(param_2 + 0x40);
      lVar10 = *(long *)(param_2 + 0x48);
      pcVar17 = pcVar18;
      if (lVar10 == 0) {
code_r0x022f4424:
        pcVar18 = pcVar18 + lVar10 * 0x18;
        if (pcVar17 != pcVar18) {
          do {
            *(undefined8 *)(puVar12 + (long)*(int *)(pcVar17 + 0x10) * 8) =
                 *(undefined8 *)(pcVar17 + 8);
            pcVar16 = pcVar17;
            do {
              pcVar17 = pcVar18;
              if (pcVar18 == pcVar16) break;
              pcVar17 = pcVar16 + 0x18;
              pcVar16 = pcVar17;
            } while (*pcVar17 != '\x01');
          } while (pcVar17 != (char *)(*(long *)(param_2 + 0x40) + *(long *)(param_2 + 0x48) * 0x18)
                  );
        }
      }
      else {
        lVar20 = lVar10 * 0x18;
        do {
          if (*pcVar17 == '\x01') goto code_r0x022f4424;
          lVar20 = lVar20 + -0x18;
          pcVar17 = pcVar17 + 0x18;
        } while (lVar20 != 0);
      }
    }
    uVar7 = (int)uVar23 * uVar3 * 0x80;
    if (uVar7 < 0x2001) {
      uVar7 = 0x2000;
    }
    piVar13 = (int *)Aska::ASON::Init(unsigned int, bool)(auStack_f8,uVar7,1);
    if (((long)piVar13 < 0) ||
       (Aska::ASON::MakeAValue_Array(Aska::ASON::AValue*, unsigned int)(apiStack_3f8,auStack_f8,auStack_98,uVar23 & 0xffffffff),
       piVar13 = apiStack_3f8[0], (long)apiStack_3f8[0] < 0)) {
joined_r0x022f4a58:
      lVar10 = 0;
      piVar21 = (int *)0x0;
    }
    else {
      uVar25 = 0;
      do {
        lVar10 = *(long *)(param_2 + 0x50);
        if (lVar10 != 0) {
          while (iVar6 = sqlite3_step(lVar10), iVar6 == 5) {
            lVar10 = *(long *)(param_2 + 0x50);
          }
        }
        uVar19 = uVar25 & 0xffffffff;
        lVar10 = lStack_90 + uVar19 * 0x20;
        if (uStack_88 <= (uint)uVar25) {
          lVar10 = 0;
        }
        Aska::ASON::MakeAValue_Map(Aska::ASON::AValue*, unsigned int)(&piStack_400,auStack_f8,lVar10,uVar3);
        piVar13 = piStack_400;
        if ((long)piStack_400 < 0) goto code_r0x022f4bb0;
        uVar24 = 0;
        do {
          puVar22 = (undefined4 *)0x0;
          lVar10 = lStack_90 + uVar19 * 0x20;
          if (uStack_88 <= (uint)uVar25) {
            lVar10 = 0;
          }
          if ((uint)uVar24 < *(uint *)(lVar10 + 0x10)) {
            puVar22 = (undefined4 *)(*(long *)(lVar10 + 8) + (uVar24 & 0xffffffff) * 0x40);
          }
          lVar10 = *(long *)(puVar12 + uVar24 * 8);
          if (lVar10 != 0) {
            uVar7 = strlen(lVar10);
            *puVar22 = 5;
            if (uVar7 == 0) {
              *(undefined8 *)(puVar22 + 4) = 0;
              *(undefined8 *)(puVar22 + 6) = 0xffffffff00000000;
              *(undefined8 *)(puVar22 + 2) = 0;
            }
            else {
              uVar26 = (ulong)uVar7;
              lVar20 = Aska::ASON::Malloc(unsigned long)(auStack_f8,uVar26);
              *(long *)(puVar22 + 2) = lVar20;
              if (lVar20 != 0) {
                *(undefined2 *)(puVar22 + 7) = uStack_a0;
                memcpy(lVar20,lVar10,uVar26);
                puVar22[6] = uVar7;
                if (cStack_70 == '\0') {
                  *(undefined8 *)(puVar22 + 4) = 0;
                  *(undefined2 *)((long)puVar22 + 0x1e) = 0xffff;
                }
                else {
                  lVar20 = Aska::ASON::Malloc(unsigned long)(auStack_f8,(ulong)(uVar7 + 1));
                  *(long *)(puVar22 + 4) = lVar20;
                  if (lVar20 != 0) {
                    *(undefined2 *)((long)puVar22 + 0x1e) = uStack_a0;
                    uVar14 = strlen(lVar10);
                    uVar28 = uVar14 + 1;
                    if (uVar28 != uVar26) {
                      uVar14 = uVar14 + 1;
                    }
                    uVar2 = uVar26;
                    if (uVar28 <= uVar26) {
                      uVar2 = uVar14;
                    }
                    if (uVar2 < uVar7 + 1) {
                      strncpy(lVar20,lVar10,uVar2);
                      if (uVar26 <= uVar28) {
                        *(undefined1 *)(lVar20 + uVar2) = 0;
                      }
                    }
                    else {
                      raise(5);
                    }
                  }
                }
              }
            }
          }
          lVar10 = lStack_90 + uVar19 * 0x20;
          if (*(uint *)(lVar10 + 0x10) <= (uint)uVar24) {
            puVar22 = (undefined4 *)0x0;
            lVar10 = *(long *)(param_2 + 0x50);
            if (lVar10 != 0) goto code_r0x022f467c;
code_r0x022f4b0c:
            piVar21 = (int *)0x0;
            lVar10 = 0;
            piVar13 = (int *)0xfffffffffffffc48;
            goto joined_r0x022f4b64;
          }
          puVar22 = (undefined4 *)(*(long *)(lVar10 + 8) + (uVar24 & 0xffffffff) * 0x40 + 0x20);
          lVar10 = *(long *)(param_2 + 0x50);
          if (lVar10 == 0) goto code_r0x022f4b0c;
code_r0x022f467c:
          sqlite3_column_value(lVar10,uVar24 & 0xffffffff);
          uVar8 = sqlite3_value_type();
          switch(uVar8) {
          case 1:
            if (*(long *)(param_2 + 0x50) == 0) {
code_r0x022f4b24:
              piVar27 = (int *)0xfffffffffffffc4d;
joined_r0x022f4b64:
              lVar10 = 0;
              piVar21 = (int *)0x0;
              piVar13 = piVar27;
              goto joined_r0x022f4b64;
            }
            uVar11 = sqlite3_column_value(*(long *)(param_2 + 0x50),uVar24 & 0xffffffff);
            iVar6 = sqlite3_value_type();
            if (iVar6 == 5) {
code_r0x022f4b3c:
              piVar27 = (int *)0xfffffffffffffc71;
              goto joined_r0x022f4b64;
            }
            iVar6 = sqlite3_value_int(uVar11);
            piVar13 = (int *)0x0;
            *puVar22 = 3;
            *(long *)(puVar22 + 2) = (long)iVar6;
            break;
          case 2:
            if (*(long *)(param_2 + 0x50) == 0) goto code_r0x022f4b24;
            uVar11 = sqlite3_column_value(*(long *)(param_2 + 0x50),uVar24 & 0xffffffff);
            iVar6 = sqlite3_value_type();
            if (iVar6 == 5) goto code_r0x022f4b3c;
            uVar11 = sqlite3_value_double(uVar11);
            piVar13 = (int *)0x0;
            *puVar22 = 4;
            *(undefined8 *)(puVar22 + 2) = uVar11;
            break;
          case 3:
          case 4:
            iVar6 = 0;
            ppiVar15 = apiStack_3f8;
            uVar26 = 0x100;
            do {
              if (*(long *)(param_2 + 0x50) == 0) {
code_r0x022f46d8:
                uVar28 = 0;
                if (uVar26 == 0) goto joined_r0x022f47b8;
code_r0x022f46e4:
                if (ppiVar15 == (int **)0x0) {
                  piVar13 = (int *)0xfffffffffffffc12;
                  goto code_r0x022f474c;
                }
                if (*(long *)(param_2 + 0x50) == 0) {
                  piVar13 = (int *)0xfffffffffffffc4d;
                  goto joined_r0x022f47b8;
                }
                uVar11 = sqlite3_column_value(*(long *)(param_2 + 0x50),uVar24 & 0xffffffff);
                iVar9 = sqlite3_value_type();
                if (iVar9 == 5) {
                  piVar13 = (int *)0xfffffffffffffc71;
                  goto joined_r0x022f47b8;
                }
                uVar11 = sqlite3_value_text(uVar11);
                iVar9 = __aska_snprintf_s(char*, unsigned long, unsigned long, char const*, ...)(ppiVar15,uVar26,0xffffffffffffffff,&UNK_027f6a37/*"%s"*/,uVar11);
                piVar13 = (int *)0x0;
                uVar26 = (ulong)iVar9;
                iVar9 = 0x10;
              }
              else {
                uVar11 = sqlite3_column_value(*(long *)(param_2 + 0x50),uVar24 & 0xffffffff);
                iVar9 = sqlite3_value_type();
                if (iVar9 == 5) goto code_r0x022f46d8;
                sqlite3_value_text(uVar11);
                uVar28 = strlen();
                if (uVar28 < uVar26) goto code_r0x022f46e4;
joined_r0x022f47b8:
                if ((ppiVar15 != (int **)0x0) && (ppiVar15 != apiStack_3f8)) {
                  operator delete[](void*)(ppiVar15);
                }
code_r0x022f474c:
                iVar1 = iVar6 + 1;
                if (iVar6 < 8) {
                  uVar26 = (uVar28 + 1) * (long)iVar1;
                  if (uVar26 != 0) {
                    lVar10 = **(long **)PTR__ZN4Aska6Global19m_pNetworkAllocatorE_02cbc200;
                    if (lVar10 == 0) {
                      lVar10 = Aska::Global::GetAvailableMemoryManager()();
                    }
                    ppiVar15 = (int **)Aska::MemoryManager::Malloc(unsigned long)(lVar10,uVar26);
                    if (ppiVar15 != (int **)0x0) {
                      iVar9 = 0;
                      iVar6 = iVar1;
                      goto code_r0x022f47f0;
                    }
                  }
                  ppiVar15 = (int **)0x0;
                  iVar9 = 4;
                  piVar13 = (int *)0xfffffffffffffc41;
                  iVar6 = iVar1;
                }
                else {
                  iVar9 = 4;
                  piVar13 = (int *)0xffffffffffffffff;
                  iVar6 = iVar1;
                }
              }
code_r0x022f47f0:
            } while (iVar9 == 0);
            if (iVar9 == 4) goto code_r0x022f4bb0;
            if (iVar9 != 0x10) {
              piVar21 = (int *)0x0;
              goto code_r0x022f4aa8;
            }
            if (ppiVar15 == (int **)0x0) {
              piVar27 = (int *)0xfffffffffffffc43;
              goto joined_r0x022f4b64;
            }
            uVar7 = strlen(ppiVar15);
            *puVar22 = 5;
            if (uVar7 == 0) {
              piVar27 = (int *)0x0;
              *(undefined8 *)(puVar22 + 4) = 0;
              *(undefined8 *)(puVar22 + 6) = 0xffffffff00000000;
              *(undefined8 *)(puVar22 + 2) = 0;
            }
            else {
              uVar26 = (ulong)uVar7;
              lVar10 = Aska::ASON::Malloc(unsigned long)(auStack_f8,uVar26);
              *(long *)(puVar22 + 2) = lVar10;
              if (lVar10 == 0) {
code_r0x022f4954:
                piVar27 = (int *)0xfffffffffffffc41;
              }
              else {
                *(undefined2 *)(puVar22 + 7) = uStack_a0;
                memcpy(lVar10,ppiVar15,uVar26);
                puVar22[6] = uVar7;
                if (cStack_70 == '\0') {
                  piVar27 = (int *)0x0;
                  *(undefined8 *)(puVar22 + 4) = 0;
                  *(undefined2 *)((long)puVar22 + 0x1e) = 0xffff;
                }
                else {
                  lVar10 = Aska::ASON::Malloc(unsigned long)(auStack_f8,(ulong)(uVar7 + 1));
                  *(long *)(puVar22 + 4) = lVar10;
                  if (lVar10 == 0) goto code_r0x022f4954;
                  *(undefined2 *)((long)puVar22 + 0x1e) = uStack_a0;
                  uVar14 = strlen(ppiVar15);
                  uVar28 = uVar14 + 1;
                  if (uVar28 != uVar26) {
                    uVar14 = uVar14 + 1;
                  }
                  uVar2 = uVar26;
                  if (uVar28 <= uVar26) {
                    uVar2 = uVar14;
                  }
                  if (uVar2 < uVar7 + 1) {
                    strncpy(lVar10,ppiVar15,uVar2);
                    if (uVar28 < uVar26) {
                      piVar27 = (int *)0x0;
                    }
                    else {
                      piVar27 = (int *)0x0;
                      *(undefined1 *)(lVar10 + uVar2) = 0;
                    }
                  }
                  else {
                    raise(5);
                    piVar27 = (int *)0x0;
                  }
                }
              }
            }
            if (ppiVar15 != apiStack_3f8) {
              operator delete[](void*)(ppiVar15);
            }
            piVar13 = (int *)0x0;
            if ((long)piVar27 < 0) goto joined_r0x022f4b64;
            break;
          case 5:
            break;
          default:
            goto code_r0x022f4b0c;
          }
          uVar24 = uVar24 + 1;
        } while (uVar24 < (ulong)(long)(int)uVar3);
        uVar25 = uVar25 + 1;
      } while (uVar25 < uVar23);
      if ((puVar12 != (undefined1 *)0x0) && (puVar12 != auStack_2f8)) {
        operator delete[](void*)(puVar12);
        puVar12 = (undefined1 *)0x0;
      }
      lVar10 = Aska::ASON::CalcSerializedSize() const(auStack_f8);
      if (lVar10 < 0) {
        piVar21 = (int *)0x0;
        lVar10 = 0;
      }
      else {
        lVar20 = operator new[](unsigned long, std::nothrow_t const&)(lVar10,PTR__ZSt7nothrow_02cb9a80);
        if (lVar20 == 0) {
          piVar13 = (int *)0xfffffffffffffc41;
          goto joined_r0x022f4a58;
        }
        lVar10 = Aska::ASON::Serialize(void*, unsigned long) const(auStack_f8,lVar20,lVar10);
        if (lVar10 < 0) {
          operator delete[](void*)(lVar20);
code_r0x022f4bb0:
          piVar21 = (int *)0x0;
          lVar10 = 0;
        }
        else {
          lStack_68 = 0;
          piVar21 = (int *)Aska::TSharedPointerCode::CreateCounter(int)(0);
          if (piVar21 != (int *)0x0) {
            do {
              cVar4 = '\x01';
              bVar5 = (bool)ExclusiveMonitorPass(piVar21,0x10);
              if (bVar5) {
                *piVar21 = *piVar21 + 1;
                cVar4 = ExclusiveMonitorsStatus();
              }
              lStack_68 = lVar20;
            } while (cVar4 != '\0');
          }
        }
      }
    }
joined_r0x022f4b64:
    if ((puVar12 != (undefined1 *)0x0) && (puVar12 != auStack_2f8)) {
      operator delete[](void*)(puVar12);
    }
    if (-1 < (long)piVar13) {
      *param_3 = lVar10;
      *param_1 = lStack_68;
      param_1[1] = (long)piVar21;
      if (piVar21 != (int *)0x0) {
        do {
          cVar4 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(piVar21,0x10);
          if (bVar5) {
            *piVar21 = *piVar21 + 1;
            cVar4 = ExclusiveMonitorsStatus();
          }
        } while (cVar4 != '\0');
      }
      goto code_r0x022f4aa8;
    }
  }
  else {
    lVar10 = **(long **)PTR__ZN4Aska6Global19m_pNetworkAllocatorE_02cbc200;
    if (lVar10 == 0) {
      lVar10 = Aska::Global::GetAvailableMemoryManager()();
    }
    puVar12 = (undefined1 *)Aska::MemoryManager::Malloc(unsigned long)(lVar10,(long)(int)uVar3 << 3);
    if (puVar12 != (undefined1 *)0x0) {
      iVar6 = *(int *)(param_2 + 0x30);
      goto joined_r0x022f4418;
    }
    piVar21 = (int *)0x0;
    piVar13 = (int *)0xfffffffffffffc41;
  }
  *param_3 = (long)piVar13;
  *param_1 = 0;
  param_1[1] = 0;
code_r0x022f4aa8:
  Aska::ASON::~ASON()(auStack_f8);
  if (piVar21 != (int *)0x0) {
    do {
      iVar6 = *piVar21;
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar21,0x10);
      if (bVar5) {
        *piVar21 = iVar6 + -1;
        cVar4 = ExclusiveMonitorsStatus();
      }
    } while (cVar4 != '\0');
    if (iVar6 + -1 != 0) {
      return;
    }
  }
  if (lStack_68 != 0) {
    operator delete[](void*)();
  }
  if (piVar21 == (int *)0x0) {
    return;
  }
  Aska::TSharedPointerCode::DeleteCounter(int*)(piVar21);
  return;
}

// ==== Aska::Yayoi::SQLiteDriver::EntityObject::SerializeCache(unsigned long*)
// vaddr 0x21f4bc8 | ghidra 0x22f4bc8 | size 8 | symbol _ZN4Aska5Yayoi12SQLiteDriver12EntityObject14SerializeCacheEPm | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska5Yayoi12SQLiteDriver12EntityObject14SerializeCacheEPm(void)

{
  return 0;
}

// ==== Aska::Yayoi::SQLiteDriver::SQLiteDriver()
// vaddr 0x21f4bd0 | ghidra 0x22f4bd0 | size 32 | symbol _ZN4Aska5Yayoi12SQLiteDriverC1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi12SQLiteDriverC2Ev(undefined8 *param_1)

{
  *(undefined2 *)(param_1 + 5) = 0;
  param_1[4] = 0;
  param_1[1] = 0;
  *param_1 = 0;
  param_1[3] = 0;
  param_1[2] = 0;
  param_1[9] = 0;
  param_1[8] = 0;
  param_1[0xb] = 0;
  param_1[10] = 0;
  param_1[7] = 0;
  param_1[6] = 0;
  *(undefined1 *)(param_1 + 0xc) = 0;
  return;
}

// ==== Aska::Yayoi::SQLiteDriver::~SQLiteDriver()
// vaddr 0x21f4bf0 | ghidra 0x22f4bf0 | size 160 | symbol _ZN4Aska5Yayoi12SQLiteDriverD1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi12SQLiteDriverD2Ev(long param_1)

{
  int iVar1;
  long lVar2;
  
  if ((*(char *)(param_1 + 0x28) == '\0') ||
     (iVar1 = sqlite3_exec(*(undefined8 *)(param_1 + 0x18),&UNK_029d3653/*"ROLLBACK;"*/,0,0,0), iVar1 != 0)) {
    lVar2 = *(long *)(param_1 + 0x18);
  }
  else {
    *(undefined1 *)(param_1 + 0x28) = 0;
    lVar2 = *(long *)(param_1 + 0x18);
  }
  if (lVar2 != 0) {
    if (*(long *)(param_1 + 0x20) != 0) {
      sqlite3_finalize(*(long *)(param_1 + 0x20));
      lVar2 = *(long *)(param_1 + 0x18);
      *(undefined8 *)(param_1 + 0x20) = 0;
    }
    sqlite3_close(lVar2);
    *(undefined8 *)(param_1 + 0x18) = 0;
  }
  *(undefined8 *)(param_1 + 0x30) = 0;
  *(undefined8 *)(param_1 + 0x48) = 0;
  if (*(long *)(param_1 + 0x38) != 0) {
    operator delete[](void*)();
    *(undefined8 *)(param_1 + 0x38) = 0;
  }
  if (*(long *)(param_1 + 0x50) != 0) {
    operator delete[](void*)();
    *(undefined8 *)(param_1 + 0x50) = 0;
  }
  *(undefined8 *)(param_1 + 0x40) = 0;
  *(undefined8 *)(param_1 + 0x58) = 0;
  return;
}

// ==== Aska::Yayoi::SQLiteDriver::Close()
// vaddr 0x21f4c90 | ghidra 0x22f4c90 | size 120 | symbol _ZN4Aska5Yayoi12SQLiteDriver5CloseEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi12SQLiteDriver5CloseEv(long param_1)

{
  int iVar1;
  long lVar2;
  
  if ((*(char *)(param_1 + 0x28) == '\0') ||
     (iVar1 = sqlite3_exec(*(undefined8 *)(param_1 + 0x18),&UNK_029d3653/*"ROLLBACK;"*/,0,0,0), iVar1 != 0)) {
    lVar2 = *(long *)(param_1 + 0x18);
  }
  else {
    *(undefined1 *)(param_1 + 0x28) = 0;
    lVar2 = *(long *)(param_1 + 0x18);
  }
  if (lVar2 != 0) {
    if (*(long *)(param_1 + 0x20) != 0) {
      sqlite3_finalize(*(long *)(param_1 + 0x20));
      lVar2 = *(long *)(param_1 + 0x18);
      *(undefined8 *)(param_1 + 0x20) = 0;
    }
    sqlite3_close(lVar2);
    *(undefined8 *)(param_1 + 0x18) = 0;
  }
  *(undefined8 *)(param_1 + 0x30) = 0;
  *(undefined8 *)(param_1 + 0x48) = 0;
  return;
}

// ==== Aska::Yayoi::SQLiteDriver::BeginTransaction()
// vaddr 0x21f4d08 | ghidra 0x22f4d08 | size 60 | symbol _ZN4Aska5Yayoi12SQLiteDriver16BeginTransactionEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi12SQLiteDriver16BeginTransactionEv(undefined8 *param_1,long param_2)

{
  if (*(char *)(param_2 + 0x29) != '\0') {
    *param_1 = 0xfffffffffffffc16;
    return;
  }
  if (*(char *)(param_2 + 0x28) != '\0') {
    *param_1 = 0xfffffffffffffc16;
    return;
  }
  *(undefined1 *)(param_2 + 0x29) = 1;
  *param_1 = 0;
  return;
}

// ==== Aska::Yayoi::SQLiteDriver::_BeginTransaction()
// vaddr 0x21f4d44 | ghidra 0x22f4d44 | size 112 | symbol _ZN4Aska5Yayoi12SQLiteDriver17_BeginTransactionEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi12SQLiteDriver17_BeginTransactionEv(undefined8 *param_1,long param_2)

{
  int iVar1;
  undefined8 uVar2;
  
  if ((*(char *)(param_2 + 0x28) == '\0') && (*(char *)(param_2 + 0x29) != '\0')) {
    *(undefined1 *)(param_2 + 0x29) = 0;
    iVar1 = sqlite3_exec(*(undefined8 *)(param_2 + 0x18),&UNK_029d3644/*"BEGIN;"*/,0,0,0);
    if (iVar1 == 0) {
      uVar2 = 0;
      *(undefined1 *)(param_2 + 0x28) = 1;
    }
    else {
      uVar2 = 0xffffffffffffffff;
    }
  }
  else {
    uVar2 = 0;
  }
  *param_1 = uVar2;
  return;
}

// ==== Aska::Yayoi::SQLiteDriver::Commit()
// vaddr 0x21f4db4 | ghidra 0x22f4db4 | size 136 | symbol _ZN4Aska5Yayoi12SQLiteDriver6CommitEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi12SQLiteDriver6CommitEv(undefined8 *param_1,long param_2)

{
  int iVar1;
  undefined8 uVar2;
  
  if (*(char *)(param_2 + 0x28) == '\0') {
code_r0x022f4e1c:
    uVar2 = 0xfffffffffffffc4d;
  }
  else {
    iVar1 = sqlite3_exec(*(undefined8 *)(param_2 + 0x18),&UNK_029d364b/*"COMMIT;"*/,0,0,0);
    if (iVar1 != 0) {
      if (*(char *)(param_2 + 0x28) == '\0') goto code_r0x022f4e1c;
      iVar1 = sqlite3_exec(*(undefined8 *)(param_2 + 0x18),&UNK_029d3653/*"ROLLBACK;"*/,0,0,0);
      if (iVar1 != 0) {
        uVar2 = 0xffffffffffffffff;
        goto code_r0x022f4e2c;
      }
    }
    uVar2 = 0;
    *(undefined1 *)(param_2 + 0x28) = 0;
  }
code_r0x022f4e2c:
  *param_1 = uVar2;
  return;
}

// ==== Aska::Yayoi::SQLiteDriver::Rollback()
// vaddr 0x21f4e3c | ghidra 0x22f4e3c | size 96 | symbol _ZN4Aska5Yayoi12SQLiteDriver8RollbackEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi12SQLiteDriver8RollbackEv(undefined8 *param_1,long param_2)

{
  int iVar1;
  undefined8 uVar2;
  
  if (*(char *)(param_2 + 0x28) == '\0') {
    uVar2 = 0xfffffffffffffc4d;
  }
  else {
    iVar1 = sqlite3_exec(*(undefined8 *)(param_2 + 0x18),&UNK_029d3653/*"ROLLBACK;"*/,0,0,0);
    if (iVar1 == 0) {
      uVar2 = 0;
      *(undefined1 *)(param_2 + 0x28) = 0;
    }
    else {
      uVar2 = 0xffffffffffffffff;
    }
  }
  *param_1 = uVar2;
  return;
}

// ==== Aska::Yayoi::SQLiteDriver::Execute(char const*, Aska::Yayoi::QueryParam const*, unsigned long)
// vaddr 0x21f4e9c | ghidra 0x22f4e9c | size 8 | symbol _ZN4Aska5Yayoi12SQLiteDriver7ExecuteEPKcPKNS0_10QueryParamEm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi12SQLiteDriver7ExecuteEPKcPKNS0_10QueryParamEm(void)

{
  (*(code *)
    PTR__ZN4Aska5Yayoi12SQLiteDriver8_ExecuteEPKcPKNS0_10QueryParamEmPNS1_12EntityObjectE_02cb6668)
            ();
  return;
}

// ==== Aska::Yayoi::SQLiteDriver::_Execute(char const*, Aska::Yayoi::QueryParam const*, unsigned long, Aska::Yayoi::SQLiteDriver::EntityObject*)
// vaddr 0x21f4ea4 | ghidra 0x22f4ea4 | size 260 | symbol _ZN4Aska5Yayoi12SQLiteDriver8_ExecuteEPKcPKNS0_10QueryParamEmPNS1_12EntityObjectE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi12SQLiteDriver8_ExecuteEPKcPKNS0_10QueryParamEmPNS1_12EntityObjectE
               (long *param_1,long param_2,undefined8 param_3,long param_4,long param_5,long param_6
               )

{
  int iVar1;
  ulong uVar2;
  undefined4 *puVar3;
  long lStack_50;
  int iStack_44;
  
  iStack_44 = 0;
  Aska::Yayoi::SQLiteDriver::_Prepare(char const*, int*)(&lStack_50,param_2,param_3,&iStack_44);
  if (-1 < lStack_50) {
    if (iStack_44 == param_5) {
      if ((iStack_44 < 1) || (*(long *)(param_2 + 0x10) == param_4)) {
code_r0x022f4f50:
        if (param_6 == 0) {
          do {
            iVar1 = sqlite3_step(*(undefined8 *)(param_2 + 0x20));
          } while (iVar1 == 5);
          if (iVar1 != 100) {
            if (iVar1 != 0x65) {
              lStack_50 = -1;
              goto code_r0x022f4f58;
            }
            sqlite3_reset(*(undefined8 *)(param_2 + 0x20));
          }
        }
        lStack_50 = 0;
      }
      else {
        sqlite3_reset(*(undefined8 *)(param_2 + 0x20));
        uVar2 = 0;
        puVar3 = (undefined4 *)(param_4 + 0x18);
        do {
          if (param_5 <= (long)uVar2) {
            *(long *)(param_2 + 0x10) = param_4;
            goto code_r0x022f4f50;
          }
          uVar2 = uVar2 + 1;
          iVar1 = sqlite3_bind_text(*(undefined8 *)(param_2 + 0x20),uVar2 & 0xffffffff,
                                  *(undefined8 *)(puVar3 + -2),*puVar3,0);
          puVar3 = puVar3 + 10;
        } while (iVar1 == 0);
        lStack_50 = -0x3b3;
      }
    }
    else {
      lStack_50 = -0x3ee;
    }
  }
code_r0x022f4f58:
  *param_1 = lStack_50;
  return;
}

// ==== Aska::Yayoi::SQLiteDriver::Find(char const*, Aska::Yayoi::QueryParam const*, unsigned long, Aska::Yayoi::SQLiteDriver::EntityObject*)
// vaddr 0x21f4fa8 | ghidra 0x22f4fa8 | size 80 | symbol _ZN4Aska5Yayoi12SQLiteDriver4FindEPKcPKNS0_10QueryParamEmPNS1_12EntityObjectE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi12SQLiteDriver4FindEPKcPKNS0_10QueryParamEmPNS1_12EntityObjectE
               (long *param_1,long param_2)

{
  undefined8 in_x4;
  undefined1 auStack_30 [8];
  long lStack_28;
  
  Aska::Yayoi::SQLiteDriver::_Execute(char const*, Aska::Yayoi::QueryParam const*, unsigned long, Aska::Yayoi::SQLiteDriver::EntityObject*)(&lStack_28);
  if (-1 < lStack_28) {
    Aska::Yayoi::SQLiteDriver::EntityObject::Store(sqlite3*, sqlite3_stmt*)(auStack_30,in_x4,*(undefined8 *)(param_2 + 0x18),*(undefined8 *)(param_2 + 0x20)
                   );
    lStack_28 = 0;
  }
  *param_1 = lStack_28;
  return;
}

// ==== Aska::Yayoi::SQLiteDriver::_Prepare(char const*, int*)
// vaddr 0x21f4ff8 | ghidra 0x22f4ff8 | size 252 | symbol _ZN4Aska5Yayoi12SQLiteDriver8_PrepareEPKcPi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi12SQLiteDriver8_PrepareEPKcPi
               (undefined8 *param_1,long param_2,undefined8 param_3,undefined4 *param_4)

{
  int iVar1;
  undefined4 uVar2;
  undefined8 uVar3;
  long lVar4;
  long *plVar5;
  undefined8 uVar6;
  
  plVar5 = (long *)(param_2 + 0x20);
  if (*plVar5 != 0) {
    sqlite3_finalize();
    *plVar5 = 0;
  }
  uVar6 = *(undefined8 *)(param_2 + 0x18);
  *(undefined8 *)(param_2 + 0x10) = 0;
  uVar3 = strlen(param_3);
  iVar1 = sqlite3_prepare_v2(uVar6,param_3,uVar3,plVar5,0);
  if (iVar1 == 0) {
    *(undefined1 *)(param_2 + 0x60) = 1;
    uVar2 = sqlite3_bind_parameter_count(*(undefined8 *)(param_2 + 0x20));
    uVar3 = 0;
    *param_4 = uVar2;
  }
  else {
    sqlite3_errmsg(*(undefined8 *)(param_2 + 0x18));
    if ((*(char *)(param_2 + 0x28) != '\0') &&
       (iVar1 = sqlite3_exec(*(undefined8 *)(param_2 + 0x18),&UNK_029d3653/*"ROLLBACK;"*/,0,0,0), iVar1 == 0)) {
      *(undefined1 *)(param_2 + 0x28) = 0;
    }
    lVar4 = *(long *)(param_2 + 0x18);
    if (lVar4 != 0) {
      if (*plVar5 != 0) {
        sqlite3_finalize(*plVar5);
        lVar4 = *(long *)(param_2 + 0x18);
        *(undefined8 *)(param_2 + 0x20) = 0;
      }
      sqlite3_close(lVar4);
      *(undefined8 *)(param_2 + 0x18) = 0;
    }
    *(undefined8 *)(param_2 + 0x30) = 0;
    *(undefined8 *)(param_2 + 0x48) = 0;
    uVar3 = 0xffffffffffffffff;
  }
  *param_1 = uVar3;
  return;
}

// ==== Aska::Yayoi::SQLiteDriver::DoOpen(Aska::Yayoi::Entity::Mode, char const*, Aska::Yayoi::DBAddress const*)
// vaddr 0x21f50f4 | ghidra 0x22f50f4 | size 348 | symbol _ZN4Aska5Yayoi12SQLiteDriver6DoOpenENS0_6Entity4ModeEPKcPKNS0_9DBAddressE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi12SQLiteDriver6DoOpenENS0_6Entity4ModeEPKcPKNS0_9DBAddressE
               (undefined8 *param_1,undefined8 *param_2,ulong param_3,undefined8 param_4,
               undefined8 *param_5)

{
  long *plVar1;
  int iVar2;
  long lVar3;
  uint uVar4;
  undefined8 uVar5;
  
  if ((int)param_3 == 0) {
    uVar4 = 0;
    if (*(char *)(param_2 + 5) != '\0') {
      uVar4 = 2;
    }
    param_3 = (ulong)uVar4;
  }
  if (param_5 == (undefined8 *)0x0) {
    param_5 = (undefined8 *)(*(code *)**(undefined8 **)*param_2)((undefined8 *)*param_2,param_3);
  }
  if (param_5 == (undefined8 *)param_2[6]) {
    lVar3 = param_2[3];
    if (lVar3 == 0) goto code_r0x022f5180;
    if ((*(char *)(param_2 + 5) == '\0') && (*(char *)((long)param_2 + 0x29) != '\0'))
    goto code_r0x022f5218;
  }
  else {
    plVar1 = param_2 + 3;
    if ((*(char *)(param_2 + 5) != '\0') &&
       (iVar2 = sqlite3_exec(*plVar1,&UNK_029d3653/*"ROLLBACK;"*/,0,0,0), iVar2 == 0)) {
      *(undefined1 *)(param_2 + 5) = 0;
    }
    lVar3 = *plVar1;
    if (lVar3 != 0) {
      if (param_2[4] != 0) {
        sqlite3_finalize(param_2[4]);
        lVar3 = param_2[3];
        param_2[4] = 0;
      }
      sqlite3_close(lVar3);
      *plVar1 = 0;
    }
    param_2[6] = 0;
    param_2[9] = 0;
code_r0x022f5180:
    *(undefined1 *)(param_2 + 0xc) = 0;
    iVar2 = sqlite3_open(*param_5,param_2 + 3);
    if (iVar2 != 0) {
      uVar5 = 0xfffffffffffffc2b;
      goto code_r0x022f51f8;
    }
    param_2[6] = param_5;
    if ((*(char *)(param_2 + 5) == '\0') && (*(char *)((long)param_2 + 0x29) != '\0')) {
      lVar3 = param_2[3];
code_r0x022f5218:
      *(undefined1 *)((long)param_2 + 0x29) = 0;
      iVar2 = sqlite3_exec(lVar3,&UNK_029d3644/*"BEGIN;"*/,0,0,0);
      if (iVar2 == 0) {
        uVar5 = 0;
        *(undefined1 *)(param_2 + 5) = 1;
      }
      else {
        uVar5 = 0xffffffffffffffff;
      }
      goto code_r0x022f51f8;
    }
  }
  uVar5 = 0;
code_r0x022f51f8:
  *param_1 = uVar5;
  return;
}

// ==== Aska::Yayoi::SQLiteDriver::Open(Aska::Yayoi::IDriverSetting<Aska::Yayoi::SQLiteDriver>*)
// vaddr 0x21f5250 | ghidra 0x22f5250 | size 32 | symbol _ZN4Aska5Yayoi12SQLiteDriver4OpenEPNS0_14IDriverSettingIS1_EE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Yayoi12SQLiteDriver4OpenEPNS0_14IDriverSettingIS1_EE
               (undefined8 *param_1,long *param_2,long param_3)

{
  if (param_3 != 0) {
    *param_2 = param_3;
    *param_1 = 0;
    return;
  }
  *param_1 = 0xfffffffffffffc12;
  return;
}

// ==== Aska::THashMap<char const*, int, Aska::Yayoi::SQLiteDriver::EntityObject::StringHasher, Aska::Yayoi::SQLiteDriver::EntityObject::StringEqualTo, Aska::TAllocator<Aska::TPair<char const* const, int> > >::~THashMap()
// vaddr 0x21f5270 | ghidra 0x22f5270 | size 48 | symbol _ZN4Aska8THashMapIPKciNS_5Yayoi12SQLiteDriver12EntityObject12StringHasherENS5_13StringEqualToENS_10TAllocatorINS_5TPairIKS2_iEEEEED0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska8THashMapIPKciNS_5Yayoi12SQLiteDriver12EntityObject12StringHasherENS5_13StringEqualToENS_10TAllocatorINS_5TPairIKS2_iEEEEED0Ev
               (long *param_1)

{
  *param_1 = (long)(
                   PTR__ZTVN4Aska8THashMapIPKciNS_5Yayoi12SQLiteDriver12EntityObject12StringHasherENS5_13StringEqualToENS_10TAllocatorINS_5TPairIKS2_iEEEEEE_02cc1328
                   + 0x10);
  if (param_1[4] != 0) {
    Aska::MemoryManagerAdapter::AlignedFree(void*)();
  }
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::THashMap<char const*, int, Aska::Yayoi::SQLiteDriver::EntityObject::StringHasher, Aska::Yayoi::SQLiteDriver::EntityObject::StringEqualTo, Aska::TAllocator<Aska::TPair<char const* const, int> > >::Emplace_(char const* const&)
// vaddr 0x21f52a0 | ghidra 0x22f52a0 | size 368 | symbol _ZN4Aska8THashMapIPKciNS_5Yayoi12SQLiteDriver12EntityObject12StringHasherENS5_13StringEqualToENS_10TAllocatorINS_5TPairIKS2_iEEEEE8Emplace_ERSA_ | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Type propagation algorithm not settling */

void _ZN4Aska8THashMapIPKciNS_5Yayoi12SQLiteDriver12EntityObject12StringHasherENS5_13StringEqualToENS_10TAllocatorINS_5TPairIKS2_iEEEEE8Emplace_ERSA_
               (undefined8 *param_1,long param_2,undefined8 *param_3)

{
  ulong uVar1;
  char cVar2;
  ulong uVar3;
  long lVar4;
  int iVar5;
  undefined8 uVar6;
  undefined1 uVar7;
  long lVar8;
  undefined8 uVar9;
  long lVar10;
  char *pcVar11;
  ulong uVar12;
  char *pcVar13;
  long alStack_70 [2];
  
  uVar9 = *param_3;
  lVar10 = *(long *)(param_2 + 0x20);
  uVar1 = *(ulong *)(param_2 + 0x28);
  uVar6 = strlen(uVar9);
  alStack_70[0] = 0;
  alStack_70[1] = 0;
  Aska::detail::SpookyHashV2::Hash128(void const*, unsigned long, unsigned long*, unsigned long*)(uVar9,uVar6,alStack_70,alStack_70 + 1);
  lVar4 = alStack_70[0];
  if (uVar1 != 0) {
    uVar6 = *param_3;
    uVar12 = 0;
    pcVar11 = (char *)0x0;
    do {
      uVar3 = 0;
      if (uVar1 != 0) {
        uVar3 = (lVar4 + uVar12) / uVar1;
      }
      lVar8 = (lVar4 + uVar12) - uVar3 * uVar1;
      pcVar13 = (char *)(lVar10 + lVar8 * 0x18);
      cVar2 = *pcVar13;
      if (cVar2 == '\x01') {
        iVar5 = strcmp(*(undefined8 *)(lVar10 + lVar8 * 0x18 + 8),uVar6);
        if (iVar5 == 0) {
          uVar7 = 0;
          pcVar11 = (char *)(lVar10 + uVar1 * 0x18);
          goto code_r0x022f53d0;
        }
      }
      else if (cVar2 == '\0') {
        if (pcVar11 != (char *)0x0) {
          pcVar13 = pcVar11;
        }
        if (pcVar13 == (char *)0x0) goto code_r0x022f53bc;
        goto code_r0x022f5364;
      }
      uVar12 = uVar12 + 1;
      if (cVar2 != '\x02' || pcVar11 != (char *)0x0) {
        pcVar13 = pcVar11;
      }
      pcVar11 = pcVar13;
    } while (uVar12 < uVar1);
    if (pcVar13 != (char *)0x0) {
code_r0x022f5364:
      *(undefined8 *)(pcVar13 + 8) = *param_3;
      if (*pcVar13 == '\0') {
code_r0x022f5388:
        *(int *)(param_2 + 0x10) = *(int *)(param_2 + 0x10) + 1;
      }
      else if (*pcVar13 == '\x02') {
        *(int *)(param_2 + 0x14) = *(int *)(param_2 + 0x14) + -1;
        goto code_r0x022f5388;
      }
      uVar7 = 1;
      *pcVar13 = '\x01';
      pcVar11 = (char *)(lVar10 + *(long *)(param_2 + 0x28) * 0x18);
      goto code_r0x022f53d0;
    }
  }
code_r0x022f53bc:
  lVar10 = *(long *)(param_2 + 0x20);
  uVar7 = 0;
  pcVar11 = (char *)(lVar10 + *(long *)(param_2 + 0x28) * 0x18);
  pcVar13 = pcVar11;
code_r0x022f53d0:
  *param_1 = pcVar13;
  param_1[1] = lVar10;
  param_1[2] = pcVar11;
  *(undefined1 *)(param_1 + 3) = uVar7;
  return;
}

// ==== Aska::THashMap<char const*, int, Aska::Yayoi::SQLiteDriver::EntityObject::StringHasher, Aska::Yayoi::SQLiteDriver::EntityObject::StringEqualTo, Aska::TAllocator<Aska::TPair<char const* const, int> > >::Rehash_(unsigned long)
// vaddr 0x21f5410 | ghidra 0x22f5410 | size 516 | symbol _ZN4Aska8THashMapIPKciNS_5Yayoi12SQLiteDriver12EntityObject12StringHasherENS5_13StringEqualToENS_10TAllocatorINS_5TPairIKS2_iEEEEE7Rehash_Em | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska8THashMapIPKciNS_5Yayoi12SQLiteDriver12EntityObject12StringHasherENS5_13StringEqualToENS_10TAllocatorINS_5TPairIKS2_iEEEEE7Rehash_Em
               (undefined1 *param_1,ulong param_2)

{
  ulong uVar1;
  undefined *puVar2;
  undefined1 *puVar3;
  undefined1 *puVar4;
  undefined8 uVar5;
  char *pcVar6;
  ulong uVar7;
  long lVar8;
  ulong uVar9;
  float fVar10;
  float fVar11;
  undefined *puStack_90;
  float fStack_84;
  undefined4 uStack_80;
  undefined4 uStack_7c;
  undefined1 *puStack_70;
  ulong uStack_68;
  char *pcStack_60;
  char *pcStack_58;
  char *pcStack_50;
  char *pcStack_48;
  char *pcStack_40;
  char *pcStack_38;
  
  puVar2 = 
  PTR__ZTVN4Aska8THashMapIPKciNS_5Yayoi12SQLiteDriver12EntityObject12StringHasherENS5_13StringEqualToENS_10TAllocatorINS_5TPairIKS2_iEEEEEE_02cc1328
  ;
  puStack_90 = PTR__ZTVN4Aska8THashMapIPKciNS_5Yayoi12SQLiteDriver12EntityObject12StringHasherENS5_13StringEqualToENS_10TAllocatorINS_5TPairIKS2_iEEEEEE_02cc1328
               + 0x10;
  fStack_84 = 0.75;
  uStack_80 = 0;
  uStack_7c = 0;
  if (param_2 < 0xaaaaaaaaaaaaaab) {
    puStack_70 = (undefined1 *)Aska::MemoryManagerAdapter::AlignedMalloc(unsigned long, unsigned long)(param_2 * 0x18,8);
  }
  else {
    puStack_70 = (undefined1 *)0x0;
  }
  if (puStack_70 == (undefined1 *)0x0) {
    param_2 = 0;
  }
  if (param_2 == 0) {
    fVar10 = *(float *)(param_1 + 0xc);
code_r0x022f5528:
    if (fVar10 <= 0.0) goto code_r0x022f5538;
  }
  else {
    uVar1 = (param_2 * 0x18 - 0x18) / 0x18 + 1;
    puVar3 = puStack_70;
    if ((uVar1 < 2) || (uVar7 = uVar1 & 0x1ffffffffffffffe, uVar7 == 0)) {
code_r0x022f54e0:
      do {
        puVar4 = puVar3 + 0x18;
        *puVar3 = 0;
        puVar3 = puVar4;
      } while (puStack_70 + param_2 * 0x18 != puVar4);
    }
    else {
      puVar3 = puStack_70 + uVar7 * 0x18;
      uVar9 = uVar7;
      puVar4 = puStack_70;
      do {
        *puVar4 = 0;
        puVar4[0x18] = 0;
        uVar9 = uVar9 - 2;
        puVar4 = puVar4 + 0x30;
      } while (uVar9 != 0);
      if (uVar1 != uVar7) goto code_r0x022f54e0;
    }
    fVar10 = *(float *)(param_1 + 0xc);
    if (param_2 == 0) goto code_r0x022f5528;
    fVar11 = (float)NEON_ucvtf(uStack_80);
    if (fVar10 <= fVar11 / (float)param_2) goto code_r0x022f5538;
  }
  fStack_84 = fVar10;
code_r0x022f5538:
  pcStack_58 = *(char **)(param_1 + 0x20);
  lVar8 = *(long *)(param_1 + 0x28);
  pcStack_60 = pcStack_58 + lVar8 * 0x18;
  pcStack_48 = pcStack_60;
  if ((*(int *)(param_1 + 0x10) != 0) && (pcStack_48 = pcStack_58, lVar8 != 0)) {
    lVar8 = lVar8 * 0x18;
    pcVar6 = pcStack_58;
    do {
      pcStack_48 = pcVar6;
      if (*pcVar6 == '\x01') break;
      lVar8 = lVar8 + -0x18;
      pcVar6 = pcVar6 + 0x18;
      pcStack_48 = pcStack_60;
    } while (lVar8 != 0);
  }
  uStack_68 = param_2;
  pcStack_50 = pcStack_60;
  pcStack_40 = pcStack_58;
  pcStack_38 = pcStack_60;
  void Aska::THashMap<char const*, int, Aska::Yayoi::SQLiteDriver::EntityObject::StringHasher, Aska::Yayoi::SQLiteDriver::EntityObject::StringEqualTo, Aska::TAllocator<Aska::TPair<char const* const, int> > >::Insert<Aska::THashMapIterator<Aska::detail::THashMapBucketArray<Aska::detail::THashMapBucket<Aska::TPair<char const* const, int> >, Aska::TAllocator<Aska::detail::THashMapBucket<Aska::TPair<char const* const, int> > > > > >(Aska::THashMapIterator<Aska::detail::THashMapBucketArray<Aska::detail::THashMapBucket<Aska::TPair<char const* const, int> >, Aska::TAllocator<Aska::detail::THashMapBucket<Aska::TPair<char const* const, int> > > > >, Aska::THashMapIterator<Aska::detail::THashMapBucketArray<Aska::detail::THashMapBucket<Aska::TPair<char const* const, int> >, Aska::TAllocator<Aska::detail::THashMapBucket<Aska::TPair<char const* const, int> > > > >)(&puStack_90,&pcStack_48,&pcStack_60);
  if (&puStack_90 != (undefined **)param_1) {
    uVar5 = *(undefined8 *)(param_1 + 0x10);
    *(ulong *)(param_1 + 0x10) = CONCAT44(uStack_7c,uStack_80);
    uStack_80 = (undefined4)uVar5;
    uStack_7c = (undefined4)((ulong)uVar5 >> 0x20);
    puVar3 = *(undefined1 **)(param_1 + 0x20);
    uVar1 = *(ulong *)(param_1 + 0x28);
    *(ulong *)(param_1 + 0x28) = uStack_68;
    *(undefined1 **)(param_1 + 0x20) = puStack_70;
    fVar10 = *(float *)(param_1 + 0xc);
    *(float *)(param_1 + 0xc) = fStack_84;
    fStack_84 = fVar10;
    puStack_70 = puVar3;
    uStack_68 = uVar1;
  }
  puStack_90 = puVar2 + 0x10;
  if (puStack_70 != (undefined1 *)0x0) {
    Aska::MemoryManagerAdapter::AlignedFree(void*)();
  }
  return;
}

// ==== void Aska::THashMap<char const*, int, Aska::Yayoi::SQLiteDriver::EntityObject::StringHasher, Aska::Yayoi::SQLiteDriver::EntityObject::StringEqualTo, Aska::TAllocator<Aska::TPair<char const* const, int> > >::Insert<Aska::THashMapIterator<Aska::detail::THashMapBucketArray<Aska::detail::THashMapBucket<Aska::TPair<char const* const, int> >, Aska::TAllocator<Aska::detail::THashMapBucket<Aska::TPair<char const* const, int> > > > > >(Aska::THashMapIterator<Aska::detail::THashMapBucketArray<Aska::detail::THashMapBucket<Aska::TPair<char const* const, int> >, Aska::TAllocator<Aska::detail::THashMapBucket<Aska::TPair<char const* const, int> > > > >, Aska::THashMapIterator<Aska::detail::THashMapBucketArray<Aska::detail::THashMapBucket<Aska::TPair<char const* const, int> >, Aska::TAllocator<Aska::detail::THashMapBucket<Aska::TPair<char const* const, int> > > > >)
// vaddr 0x21f5614 | ghidra 0x22f5614 | size 256 | symbol _ZN4Aska8THashMapIPKciNS_5Yayoi12SQLiteDriver12EntityObject12StringHasherENS5_13StringEqualToENS_10TAllocatorINS_5TPairIKS2_iEEEEE6InsertINS_16THashMapIteratorINS_6detail19THashMapBucketArrayINSG_14THashMapBucketISB_EENS8_ISJ_EEEEEEEEvT_SN_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska8THashMapIPKciNS_5Yayoi12SQLiteDriver12EntityObject12StringHasherENS5_13StringEqualToENS_10TAllocatorINS_5TPairIKS2_iEEEEE6InsertINS_16THashMapIteratorINS_6detail19THashMapBucketArrayINSG_14THashMapBucketISB_EENS8_ISJ_EEEEEEEEvT_SN_
               (long param_1,long *param_2,undefined8 *param_3)

{
  char *pcVar1;
  char *pcVar2;
  char *pcVar3;
  long lVar4;
  ulong uVar5;
  char *pcVar6;
  undefined1 auStack_40 [32];
  
  pcVar2 = (char *)*param_2;
  pcVar3 = (char *)*param_3;
  lVar4 = 0;
  if (pcVar2 != pcVar3) {
    pcVar6 = pcVar2;
    do {
      lVar4 = lVar4 + 1;
      do {
        pcVar1 = (char *)param_2[2];
        if ((char *)param_2[2] == pcVar6) break;
        pcVar6 = pcVar6 + 0x18;
        pcVar1 = pcVar6;
      } while (*pcVar6 != '\x01');
      pcVar6 = pcVar1;
    } while (pcVar6 != pcVar3);
  }
  uVar5 = (ulong)((float)(lVar4 + (ulong)*(uint *)(param_1 + 0x10) +
                         (ulong)*(uint *)(param_1 + 0x14)) / *(float *)(param_1 + 0xc));
  if (uVar5 <= *(ulong *)(param_1 + 0x28)) goto code_r0x022f56b8;
  Aska::THashMap<char const*, int, Aska::Yayoi::SQLiteDriver::EntityObject::StringHasher, Aska::Yayoi::SQLiteDriver::EntityObject::StringEqualTo, Aska::TAllocator<Aska::TPair<char const* const, int> > >::Rehash_(unsigned long)(param_1,uVar5 << 1 | 1);
  pcVar2 = (char *)*param_2;
  do {
    pcVar3 = (char *)*param_3;
code_r0x022f56b8:
    if (pcVar2 == pcVar3) {
      return;
    }
    Aska::THashMap<char const*, int, Aska::Yayoi::SQLiteDriver::EntityObject::StringHasher, Aska::Yayoi::SQLiteDriver::EntityObject::StringEqualTo, Aska::TAllocator<Aska::TPair<char const* const, int> > >::Insert_(Aska::TPair<char const* const, int> const&)(auStack_40,param_1,pcVar2 + 8);
    pcVar3 = (char *)*param_2;
    do {
      pcVar2 = (char *)param_2[2];
      if ((char *)param_2[2] == pcVar3) break;
      pcVar2 = pcVar3 + 0x18;
      *param_2 = (long)pcVar2;
      pcVar6 = pcVar3 + 0x18;
      pcVar3 = pcVar2;
    } while (*pcVar6 != '\x01');
  } while( true );
}

// ==== Aska::THashMap<char const*, int, Aska::Yayoi::SQLiteDriver::EntityObject::StringHasher, Aska::Yayoi::SQLiteDriver::EntityObject::StringEqualTo, Aska::TAllocator<Aska::TPair<char const* const, int> > >::Insert_(Aska::TPair<char const* const, int> const&)
// vaddr 0x21f5714 | ghidra 0x22f5714 | size 360 | symbol _ZN4Aska8THashMapIPKciNS_5Yayoi12SQLiteDriver12EntityObject12StringHasherENS5_13StringEqualToENS_10TAllocatorINS_5TPairIKS2_iEEEEE7Insert_ERKSB_ | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Type propagation algorithm not settling */

void _ZN4Aska8THashMapIPKciNS_5Yayoi12SQLiteDriver12EntityObject12StringHasherENS5_13StringEqualToENS_10TAllocatorINS_5TPairIKS2_iEEEEE7Insert_ERKSB_
               (undefined8 *param_1,long param_2,undefined8 *param_3)

{
  ulong uVar1;
  char cVar2;
  ulong uVar3;
  long lVar4;
  int iVar5;
  undefined8 uVar6;
  undefined1 uVar7;
  long lVar8;
  undefined8 uVar9;
  char *pcVar10;
  long lVar11;
  ulong uVar12;
  char *pcVar13;
  long alStack_70 [2];
  
  uVar9 = *param_3;
  lVar11 = *(long *)(param_2 + 0x20);
  uVar1 = *(ulong *)(param_2 + 0x28);
  uVar6 = strlen(uVar9);
  alStack_70[0] = 0;
  alStack_70[1] = 0;
  Aska::detail::SpookyHashV2::Hash128(void const*, unsigned long, unsigned long*, unsigned long*)(uVar9,uVar6,alStack_70,alStack_70 + 1);
  lVar4 = alStack_70[0];
  if (uVar1 != 0) {
    uVar12 = 0;
    pcVar10 = (char *)0x0;
    do {
      uVar3 = 0;
      if (uVar1 != 0) {
        uVar3 = (lVar4 + uVar12) / uVar1;
      }
      lVar8 = (lVar4 + uVar12) - uVar3 * uVar1;
      pcVar13 = (char *)(lVar11 + lVar8 * 0x18);
      cVar2 = *pcVar13;
      if (cVar2 == '\x01') {
        iVar5 = strcmp(*(undefined8 *)(lVar11 + lVar8 * 0x18 + 8),*param_3);
        if (iVar5 == 0) {
          uVar7 = 0;
          pcVar10 = (char *)(lVar11 + uVar1 * 0x18);
          goto code_r0x022f583c;
        }
      }
      else if (cVar2 == '\0') {
        if (pcVar10 != (char *)0x0) {
          pcVar13 = pcVar10;
        }
        if (pcVar13 == (char *)0x0) goto code_r0x022f5828;
        goto code_r0x022f57cc;
      }
      uVar12 = uVar12 + 1;
      if (cVar2 != '\x02' || pcVar10 != (char *)0x0) {
        pcVar13 = pcVar10;
      }
      pcVar10 = pcVar13;
    } while (uVar12 < uVar1);
    if (pcVar13 != (char *)0x0) {
code_r0x022f57cc:
      *(undefined8 *)(pcVar13 + 8) = *param_3;
      *(undefined4 *)(pcVar13 + 0x10) = *(undefined4 *)(param_3 + 1);
      if (*pcVar13 == '\0') {
code_r0x022f57f8:
        *(int *)(param_2 + 0x10) = *(int *)(param_2 + 0x10) + 1;
      }
      else if (*pcVar13 == '\x02') {
        *(int *)(param_2 + 0x14) = *(int *)(param_2 + 0x14) + -1;
        goto code_r0x022f57f8;
      }
      uVar7 = 1;
      *pcVar13 = '\x01';
      pcVar10 = (char *)(lVar11 + *(long *)(param_2 + 0x28) * 0x18);
      goto code_r0x022f583c;
    }
  }
code_r0x022f5828:
  lVar11 = *(long *)(param_2 + 0x20);
  uVar7 = 0;
  pcVar10 = (char *)(lVar11 + *(long *)(param_2 + 0x28) * 0x18);
  pcVar13 = pcVar10;
code_r0x022f583c:
  *param_1 = pcVar13;
  param_1[1] = lVar11;
  param_1[2] = pcVar10;
  *(undefined1 *)(param_1 + 3) = uVar7;
  return;
}
