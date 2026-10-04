// port/decomp/containers/array_u32.c: Ghidra decompiles for the containers subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileAt.java, tools/resolve_decomp.py
// run      2026-10-04 05:15 UTC: tools/decomp.sh '--into' 'containers/array_u32' 'Aska::TArray<unsigned int, (false|true)>::' 'Aska::TDynamicArray<unsigned int, Aska::TAllocator<unsigned int> >::' 'Aska::TStack<unsigned int, 10>::' 'Framework::TStaticString<(16|32)ul>::'
// run      2026-10-04 05:16 UTC: tools/decomp_at.sh '--into' 'containers/array_u32' '2285a7c' '2285a44' '2285a08' '12ab4c4' '12ab488' '12a9e34' '26a238c' '26a2488' '26a1ed0' '15a9ca0' '15a9d00' '15a9cb0' '22c8080' '21bd7f8' '22c86cc' '22c85ec'

// ==== Aska::TArray<unsigned int, false>::~TArray()
// vaddr 0x11a9e34 | ghidra 0x12a9e34 | size 68 | symbol _ZN4Aska6TArrayIjLb0EED2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6TArrayIjLb0EED2Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska6TArrayIjLb0EEE_02cb84e8 + 0x10);
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

// ==== Aska::TArray<unsigned int, false>::~TArray()
// vaddr 0x11ab488 | ghidra 0x12ab488 | size 60 | symbol _ZN4Aska6TArrayIjLb0EED0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6TArrayIjLb0EED0Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska6TArrayIjLb0EEE_02cb84e8 + 0x10);
  *(ushort *)((long)param_1 + 0x32) = *(ushort *)((long)param_1 + 0x32) | 1;
  if (param_1[1] != 0) {
    operator delete[](void*)();
  }
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::TArray<unsigned int, false>::Resize(long, bool)
// vaddr 0x11ab4c4 | ghidra 0x12ab4c4 | size 460 | symbol _ZN4Aska6TArrayIjLb0EE6ResizeElb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6TArrayIjLb0EE6ResizeElb(long param_1,ulong param_2)

{
  ulong uVar1;
  long lVar2;
  undefined8 *puVar3;
  ulong uVar4;
  ushort uVar5;
  long lVar6;
  ulong uVar7;
  undefined4 *puVar8;
  ulong uVar9;
  undefined4 *puVar10;
  undefined8 *puVar11;
  undefined8 *puVar12;
  ulong uVar13;
  ulong uVar14;
  ulong uVar15;
  undefined8 uVar16;
  undefined8 uVar17;
  undefined8 uVar18;
  
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
  lVar6 = *(long *)(param_1 + 0x10);
  if (lVar6 < (long)param_2) {
    uVar15 = param_2 << 1;
  }
  else {
    lVar2 = lVar6 + 3;
    if (-1 < lVar6) {
      lVar2 = lVar6;
    }
    if (((lVar2 >> 2 < (long)param_2) || ((*(ushort *)(param_1 + 0x32) & 1) == 0)) ||
       (uVar15 = param_2 * 2,
       uVar15 - *(long *)(param_1 + 0x28) == 0 || (long)uVar15 < *(long *)(param_1 + 0x28)))
    goto code_r0x012ab640;
  }
  uVar14 = *(ulong *)(param_1 + 8);
  if (uVar14 == 0) {
    uVar15 = *(ulong *)(param_1 + 0x28);
    if ((long)*(ulong *)(param_1 + 0x28) <= (long)param_2) {
      uVar15 = param_2;
    }
    lVar6 = operator new[](unsigned long, std::nothrow_t const&)(uVar15 << 2,PTR__ZSt7nothrow_02cb9a80);
    *(long *)(param_1 + 8) = lVar6;
    if (lVar6 == 0) {
      *(ushort *)(param_1 + 0x30) = *(ushort *)(param_1 + 0x30) | 1;
      return;
    }
    uVar5 = *(ushort *)(param_1 + 0x30) & 0xfffe;
code_r0x012ab638:
    *(ushort *)(param_1 + 0x30) = uVar5;
  }
  else {
    uVar4 = operator new[](unsigned long, std::nothrow_t const&)(param_2 << 3,PTR__ZSt7nothrow_02cb9a80);
    *(ulong *)(param_1 + 8) = uVar4;
    if (uVar4 == 0) {
      uVar5 = *(ushort *)(param_1 + 0x30) | 1;
      goto code_r0x012ab638;
    }
    uVar7 = *(ulong *)(param_1 + 0x18);
    uVar1 = param_2;
    if ((long)uVar7 <= (long)param_2) {
      uVar1 = uVar7;
    }
    if (0 < (long)uVar1) {
      if (uVar1 < 8) {
code_r0x012ab560:
        uVar9 = 0;
      }
      else {
        uVar9 = uVar1 & 0xfffffffffffffff8;
        if (uVar9 != 0) {
          uVar13 = param_2;
          if ((long)uVar7 <= (long)param_2) {
            uVar13 = uVar7;
          }
          if ((uVar4 < uVar14 + uVar1 * 4) &&
             (uVar14 < uVar4 + (-4 - (uVar13 << 2 ^ 0xfffffffffffffffc)))) goto code_r0x012ab560;
          puVar11 = (undefined8 *)(uVar4 + 0x10);
          puVar12 = (undefined8 *)(uVar14 + 0x10);
          uVar13 = uVar9;
          do {
            puVar3 = puVar12 + -1;
            uVar16 = puVar12[-2];
            uVar18 = puVar12[1];
            uVar17 = *puVar12;
            uVar13 = uVar13 - 8;
            puVar12 = puVar12 + 4;
            puVar11[-1] = *puVar3;
            puVar11[-2] = uVar16;
            puVar11[1] = uVar18;
            *puVar11 = uVar17;
            puVar11 = puVar11 + 4;
          } while (uVar13 != 0);
          if (uVar1 == uVar9) goto code_r0x012ab598;
        }
      }
      uVar7 = ~uVar7;
      if ((long)uVar7 < (long)~param_2) {
        uVar7 = ~param_2;
      }
      lVar6 = ~uVar9 - uVar7;
      puVar8 = (undefined4 *)(uVar14 + uVar9 * 4);
      puVar10 = (undefined4 *)(uVar4 + uVar9 * 4);
      do {
        lVar6 = lVar6 + -1;
        *puVar10 = *puVar8;
        puVar8 = puVar8 + 1;
        puVar10 = puVar10 + 1;
      } while (lVar6 != 0);
    }
code_r0x012ab598:
    operator delete[](void*)(uVar14);
    *(ulong *)(param_1 + 0x10) = uVar15;
    *(ulong *)(param_1 + 0x18) = param_2;
  }
  *(ulong *)(param_1 + 0x10) = uVar15;
code_r0x012ab640:
  *(ulong *)(param_1 + 0x18) = param_2;
  return;
}

// ==== Aska::TStack<unsigned int, 10>::CopyElement(unsigned int const*, unsigned int*)
// vaddr 0x14a9ca0 | ghidra 0x15a9ca0 | size 16 | symbol _ZN4Aska6TStackIjLi10EE11CopyElementEPKjPj | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska6TStackIjLi10EE11CopyElementEPKjPj
          (undefined8 param_1,undefined4 *param_2,undefined4 *param_3)

{
  *param_3 = *param_2;
  return 1;
}

// ==== Aska::TStack<unsigned int, 10>::~TStack()
// vaddr 0x14a9cb0 | ghidra 0x15a9cb0 | size 80 | symbol _ZN4Aska6TStackIjLi10EED2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6TStackIjLi10EED2Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska6TStackIjLi10EEE_02cbdcb8 + 0x10);
  if ((long *)param_1[6] != param_1 + 1) {
    if ((long *)param_1[6] != (long *)0x0) {
      operator delete[](void*)();
    }
    param_1[6] = (long)(param_1 + 1);
  }
  param_1[7] = -0xfffffff6;
  return;
}

// ==== Aska::TStack<unsigned int, 10>::~TStack()
// vaddr 0x14a9d00 | ghidra 0x15a9d00 | size 60 | symbol _ZN4Aska6TStackIjLi10EED0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6TStackIjLi10EED0Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska6TStackIjLi10EEE_02cbdcb8 + 0x10);
  if (((long *)param_1[6] != param_1 + 1) && ((long *)param_1[6] != (long *)0x0)) {
    operator delete[](void*)();
  }
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Framework::TStaticString<32ul>::Set(char const*)
// vaddr 0x1e3bd3c | ghidra 0x1f3bd3c | size 380 | symbol _ZN9Framework13TStaticStringILm32EE3SetEPKc | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework13TStaticStringILm32EE3SetEPKc(char *param_1,char *param_2)

{
  char cVar1;
  
  cVar1 = *param_2;
  *param_1 = cVar1;
  if ((((((cVar1 != '\0') && (cVar1 = param_2[1], param_1[1] = cVar1, cVar1 != '\0')) &&
        (cVar1 = param_2[2], param_1[2] = cVar1, cVar1 != '\0')) &&
       (((cVar1 = param_2[3], param_1[3] = cVar1, cVar1 != '\0' &&
         (cVar1 = param_2[4], param_1[4] = cVar1, cVar1 != '\0')) &&
        ((cVar1 = param_2[5], param_1[5] = cVar1, cVar1 != '\0' &&
         ((cVar1 = param_2[6], param_1[6] = cVar1, cVar1 != '\0' &&
          (cVar1 = param_2[7], param_1[7] = cVar1, cVar1 != '\0')))))))) &&
      ((cVar1 = param_2[8], param_1[8] = cVar1, cVar1 != '\0' &&
       (((cVar1 = param_2[9], param_1[9] = cVar1, cVar1 != '\0' &&
         (cVar1 = param_2[10], param_1[10] = cVar1, cVar1 != '\0')) &&
        (cVar1 = param_2[0xb], param_1[0xb] = cVar1, cVar1 != '\0')))))) &&
     (((((cVar1 = param_2[0xc], param_1[0xc] = cVar1, cVar1 != '\0' &&
         (cVar1 = param_2[0xd], param_1[0xd] = cVar1, cVar1 != '\0')) &&
        ((cVar1 = param_2[0xe], param_1[0xe] = cVar1, cVar1 != '\0' &&
         ((cVar1 = param_2[0xf], param_1[0xf] = cVar1, cVar1 != '\0' &&
          (cVar1 = param_2[0x10], param_1[0x10] = cVar1, cVar1 != '\0')))))) &&
       (cVar1 = param_2[0x11], param_1[0x11] = cVar1, cVar1 != '\0')) &&
      (((((cVar1 = param_2[0x12], param_1[0x12] = cVar1, cVar1 != '\0' &&
          (cVar1 = param_2[0x13], param_1[0x13] = cVar1, cVar1 != '\0')) &&
         (cVar1 = param_2[0x14], param_1[0x14] = cVar1, cVar1 != '\0')) &&
        ((cVar1 = param_2[0x15], param_1[0x15] = cVar1, cVar1 != '\0' &&
         (cVar1 = param_2[0x16], param_1[0x16] = cVar1, cVar1 != '\0')))) &&
       ((((cVar1 = param_2[0x17], param_1[0x17] = cVar1, cVar1 != '\0' &&
          ((cVar1 = param_2[0x18], param_1[0x18] = cVar1, cVar1 != '\0' &&
           (cVar1 = param_2[0x19], param_1[0x19] = cVar1, cVar1 != '\0')))) &&
         (cVar1 = param_2[0x1a], param_1[0x1a] = cVar1, cVar1 != '\0')) &&
        ((((cVar1 = param_2[0x1b], param_1[0x1b] = cVar1, cVar1 != '\0' &&
           (cVar1 = param_2[0x1c], param_1[0x1c] = cVar1, cVar1 != '\0')) &&
          (cVar1 = param_2[0x1d], param_1[0x1d] = cVar1, cVar1 != '\0')) &&
         (cVar1 = param_2[0x1e], param_1[0x1e] = cVar1, cVar1 != '\0')))))))))) {
    param_1[0x1f] = '\0';
  }
  return;
}

// ==== Framework::TStaticString<16ul>::Set(char const*)
// vaddr 0x1e80d04 | ghidra 0x1f80d04 | size 188 | symbol _ZN9Framework13TStaticStringILm16EE3SetEPKc | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework13TStaticStringILm16EE3SetEPKc(char *param_1,char *param_2)

{
  char cVar1;
  
  cVar1 = *param_2;
  *param_1 = cVar1;
  if (((((cVar1 != '\0') && (cVar1 = param_2[1], param_1[1] = cVar1, cVar1 != '\0')) &&
       (cVar1 = param_2[2], param_1[2] = cVar1, cVar1 != '\0')) &&
      (((cVar1 = param_2[3], param_1[3] = cVar1, cVar1 != '\0' &&
        (cVar1 = param_2[4], param_1[4] = cVar1, cVar1 != '\0')) &&
       ((cVar1 = param_2[5], param_1[5] = cVar1, cVar1 != '\0' &&
        ((cVar1 = param_2[6], param_1[6] = cVar1, cVar1 != '\0' &&
         (cVar1 = param_2[7], param_1[7] = cVar1, cVar1 != '\0')))))))) &&
     ((cVar1 = param_2[8], param_1[8] = cVar1, cVar1 != '\0' &&
      (((((cVar1 = param_2[9], param_1[9] = cVar1, cVar1 != '\0' &&
          (cVar1 = param_2[10], param_1[10] = cVar1, cVar1 != '\0')) &&
         (cVar1 = param_2[0xb], param_1[0xb] = cVar1, cVar1 != '\0')) &&
        ((cVar1 = param_2[0xc], param_1[0xc] = cVar1, cVar1 != '\0' &&
         (cVar1 = param_2[0xd], param_1[0xd] = cVar1, cVar1 != '\0')))) &&
       (cVar1 = param_2[0xe], param_1[0xe] = cVar1, cVar1 != '\0')))))) {
    param_1[0xf] = '\0';
  }
  return;
}

// ==== Aska::TPoolFast<Aska::Vector, false>::Scoop(int)
// vaddr 0x20bd7f8 | ghidra 0x21bd7f8 | size 508 | symbol _ZN4Aska9TPoolFastINS_6VectorELb0EE5ScoopEi | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska9TPoolFastINS_6VectorELb0EE5ScoopEi(long param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  ulong *puVar9;
  int iVar10;
  ulong uVar11;
  uint uVar12;
  long lVar13;
  int iVar14;
  long lVar15;
  
  uVar4 = *(uint *)(param_1 + 0x24);
  if ((uint)(*(int *)(param_1 + 0x3c) + param_2) <= uVar4) {
    uVar5 = *(uint *)(param_1 + 0x38);
    iVar6 = param_2 + -1;
    iVar14 = (uVar4 + iVar6) - uVar5;
    if ((int)(uVar5 + param_2) <= (int)uVar4) {
      iVar14 = iVar6;
    }
    uVar12 = 0;
    if ((int)(uVar5 + param_2) <= (int)uVar4) {
      uVar12 = uVar5;
    }
    if (iVar14 < (int)uVar4) {
      if (param_2 == 0) {
code_r0x021bd9c4:
        uVar5 = 0;
        if (uVar4 != 0) {
          uVar5 = (uVar12 + param_2) / uVar4;
        }
        *(uint *)(param_1 + 0x38) = (uVar12 + param_2) - uVar5 * uVar4;
        *(int *)(param_1 + 0x3c) = *(int *)(param_1 + 0x3c) + param_2;
        return *(long *)(param_1 + 0x30) + (long)(int)uVar12 * 0x10;
      }
      lVar13 = *(long *)(param_1 + 0x18);
      do {
        uVar5 = uVar12 + 0x3f;
        if (-1 < (int)uVar12) {
          uVar5 = uVar12;
        }
        uVar7 = (int)uVar12 % 0x40;
        puVar9 = (ulong *)(lVar13 + (long)((int)uVar5 >> 6) * 8);
        iVar10 = param_2;
        uVar1 = uVar7;
        while( true ) {
          uVar11 = 0xffffffffffffffff >> ((ulong)(0x40 - iVar10) & 0x3f);
          if (0x3f < iVar10) {
            uVar11 = 0xffffffffffffffff;
          }
          iVar2 = 0;
          if (iVar10 < 0x40) {
            iVar2 = iVar10;
          }
          if ((uVar11 << ((ulong)uVar1 & 0x3f) & *puVar9) != 0) break;
          iVar3 = 0x40 - uVar1;
          if (iVar2 <= (int)(0x40 - uVar1)) {
            iVar3 = iVar2;
          }
          iVar10 = iVar10 - iVar3;
          puVar9 = puVar9 + 1;
          uVar1 = 0;
          if (iVar10 == 0) {
            uVar11 = 0xffffffffffffffff >> ((ulong)(0x40 - param_2) & 0x3f);
            lVar15 = ((long)((ulong)uVar5 << 0x20) >> 0x26) * 8;
            if (0x3f < param_2) {
              uVar11 = 0xffffffffffffffff;
            }
            iVar14 = 0;
            if (param_2 < 0x40) {
              iVar14 = param_2;
            }
            iVar6 = 0x40 - uVar7;
            if (iVar14 <= (int)(0x40 - uVar7)) {
              iVar6 = iVar14;
            }
            *(ulong *)(lVar13 + lVar15) =
                 *(ulong *)(lVar13 + lVar15) | uVar11 << ((ulong)uVar7 & 0x3f);
            for (iVar6 = param_2 - iVar6; iVar6 != 0; iVar6 = iVar6 - iVar14) {
              lVar15 = lVar15 + 8;
              uVar11 = 0xffffffffffffffff >> ((ulong)(0x40 - iVar6) & 0x3f);
              iVar14 = iVar6;
              if (0x3f < iVar6) {
                uVar11 = 0xffffffffffffffff;
                iVar14 = 0x40;
              }
              if (0x3f < iVar14) {
                iVar14 = 0x40;
              }
              *(ulong *)(*(long *)(param_1 + 0x18) + lVar15) =
                   uVar11 | *(ulong *)(*(long *)(param_1 + 0x18) + lVar15);
            }
            goto code_r0x021bd9c4;
          }
        }
        iVar10 = 0;
        do {
          uVar5 = uVar12 + iVar6 + iVar10;
          iVar10 = iVar10 + -1;
        } while ((1L << (uVar5 & 0x3f) & *(ulong *)(lVar13 + (ulong)(uVar5 >> 6) * 8)) == 0);
        iVar2 = (param_2 << 1 | 1U) + uVar12;
        iVar3 = param_2 + 1 + uVar12;
        iVar8 = (((uVar4 - 1) - param_2) - uVar12) - iVar10;
        uVar12 = 0;
        if (iVar2 + iVar10 <= (int)uVar4) {
          iVar8 = 0;
          uVar12 = iVar3 + iVar10;
        }
        iVar14 = iVar8 + param_2 + 1 + iVar14 + iVar10;
        if ((int)uVar4 <= iVar14) {
          return 0;
        }
      } while( true );
    }
  }
  return 0;
}

// ==== Aska::TDynamicArray<unsigned int, Aska::TAllocator<unsigned int> >::~TDynamicArray()
// vaddr 0x2185a08 | ghidra 0x2285a08 | size 60 | symbol _ZN4Aska13TDynamicArrayIjNS_10TAllocatorIjEEED2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13TDynamicArrayIjNS_10TAllocatorIjEEED2Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska13TDynamicArrayIjNS_10TAllocatorIjEEEE_02cbf118 + 0x10);
  if (param_1[3] != param_1[1]) {
    Aska::MemoryManagerAdapter::AlignedFree(void*)();
    param_1[2] = 0;
    param_1[3] = 0;
    param_1[1] = 0;
  }
  return;
}

// ==== Aska::TDynamicArray<unsigned int, Aska::TAllocator<unsigned int> >::~TDynamicArray()
// vaddr 0x2185a44 | ghidra 0x2285a44 | size 56 | symbol _ZN4Aska13TDynamicArrayIjNS_10TAllocatorIjEEED0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13TDynamicArrayIjNS_10TAllocatorIjEEED0Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska13TDynamicArrayIjNS_10TAllocatorIjEEEE_02cbf118 + 0x10);
  if (param_1[3] != param_1[1]) {
    Aska::MemoryManagerAdapter::AlignedFree(void*)();
  }
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::TArrayIterator<Aska::TDynamicArray<unsigned int, Aska::TAllocator<unsigned int> > > Aska::TDynamicArray<unsigned int, Aska::TAllocator<unsigned int> >::Insert_<Aska::Memory::TUninitializedFillN<unsigned int> >(unsigned int const*, unsigned long, Aska::Memory::TUninitializedFillN<unsigned int> const&)
// vaddr 0x2185a7c | ghidra 0x2285a7c | size 872 | symbol _ZN4Aska13TDynamicArrayIjNS_10TAllocatorIjEEE7Insert_INS_6Memory19TUninitializedFillNIjEEEENS_14TArrayIteratorIS3_EEPKjmRKT_ | lib libSOA-3.7.0.so | 2026-10-04
undefined4 *
_ZN4Aska13TDynamicArrayIjNS_10TAllocatorIjEEE7Insert_INS_6Memory19TUninitializedFillNIjEEEENS_14TArrayIteratorIS3_EEPKjmRKT_
          (long param_1,undefined4 *param_2,long param_3,ulong *param_4)

{
  undefined4 uVar1;
  undefined8 *puVar2;
  bool bVar3;
  undefined4 *puVar4;
  ulong uVar5;
  ulong uVar6;
  ulong uVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;
  long lVar10;
  undefined4 *puVar11;
  ulong uVar12;
  undefined4 *puVar13;
  ulong uVar14;
  undefined8 *puVar15;
  undefined8 *puVar16;
  undefined4 *puVar17;
  undefined8 uVar18;
  undefined8 uVar19;
  undefined8 uVar20;
  
  if (param_3 == 0) {
    return param_2;
  }
  puVar4 = *(undefined4 **)(param_1 + 0x10);
  uVar7 = param_3 + ((long)puVar4 - *(long *)(param_1 + 8) >> 2);
  lVar10 = *(long *)(param_1 + 0x18) - *(long *)(param_1 + 8);
  if (uVar7 <= (ulong)(lVar10 >> 2)) {
    while (puVar4 != param_2) {
      puVar4[param_3 + -1] = puVar4[-1];
      puVar4 = puVar4 + -1;
    }
    uVar7 = *param_4;
    if (uVar7 != 0) {
      puVar8 = (undefined4 *)param_4[1];
      puVar4 = param_2;
      if (((7 < uVar7) && (uVar5 = uVar7 & 0xfffffffffffffff8, uVar5 != 0)) &&
         (((undefined4 *)((long)puVar8 + 1U) <= param_2 || (param_2 + uVar7 <= puVar8)))) {
        uVar1 = *puVar8;
        puVar15 = (undefined8 *)(param_2 + 4);
        uVar6 = uVar5;
        do {
          puVar15[-1] = CONCAT44(uVar1,uVar1);
          puVar15[-2] = CONCAT44(uVar1,uVar1);
          puVar15[1] = CONCAT44(uVar1,uVar1);
          *puVar15 = CONCAT44(uVar1,uVar1);
          uVar6 = uVar6 - 8;
          puVar15 = puVar15 + 4;
        } while (uVar6 != 0);
        bVar3 = uVar7 == uVar5;
        uVar7 = uVar7 - uVar5;
        puVar4 = param_2 + uVar5;
        if (bVar3) goto code_r0x02285bc8;
      }
      do {
        uVar7 = uVar7 - 1;
        *puVar4 = *puVar8;
        puVar4 = puVar4 + 1;
      } while (uVar7 != 0);
    }
code_r0x02285bc8:
    *(long *)(param_1 + 0x10) = *(long *)(param_1 + 0x10) + param_3 * 4;
    return param_2;
  }
  uVar5 = lVar10 >> 1;
  if (uVar7 <= uVar5) {
    uVar7 = uVar5;
  }
  if (uVar7 >> 0x3e != 0) {
    return param_2;
  }
  puVar4 = (undefined4 *)Aska::MemoryManagerAdapter::AlignedMalloc(unsigned long, unsigned long)(uVar7 << 2,4);
  if (puVar4 == (undefined4 *)0x0) {
    return param_2;
  }
  puVar8 = *(undefined4 **)(param_1 + 8);
  if (puVar8 == param_2) {
    uVar5 = *param_4;
    puVar8 = puVar4;
  }
  else {
    uVar6 = (long)param_2 + (-4 - (long)puVar8);
    uVar5 = (uVar6 >> 2) + 1;
    puVar11 = puVar4;
    if (((uVar5 < 8) || (uVar12 = uVar5 & 0x7ffffffffffffff8, uVar12 == 0)) ||
       ((puVar4 < (undefined4 *)((long)puVar8 + (uVar6 & 0xfffffffffffffffc) + 4) &&
        (puVar8 < (undefined4 *)((long)puVar4 + (uVar6 + 4 & 0xfffffffffffffffc)))))) {
code_r0x02285c4c:
      do {
        puVar9 = puVar8 + 1;
        *puVar11 = *puVar8;
        puVar8 = puVar9;
        puVar11 = puVar11 + 1;
      } while (param_2 != puVar9);
    }
    else {
      puVar15 = (undefined8 *)(puVar8 + 4);
      puVar8 = puVar8 + uVar12;
      puVar16 = (undefined8 *)(puVar4 + 4);
      uVar14 = uVar12;
      do {
        puVar2 = puVar15 + -1;
        uVar18 = puVar15[-2];
        uVar20 = puVar15[1];
        uVar19 = *puVar15;
        puVar15 = puVar15 + 4;
        uVar14 = uVar14 - 8;
        puVar16[-1] = *puVar2;
        puVar16[-2] = uVar18;
        puVar16[1] = uVar20;
        *puVar16 = uVar19;
        puVar16 = puVar16 + 4;
      } while (uVar14 != 0);
      puVar11 = puVar4 + uVar12;
      if (uVar5 != uVar12) goto code_r0x02285c4c;
    }
    puVar8 = (undefined4 *)((long)puVar4 + (uVar6 & 0xfffffffffffffffc) + 4);
    uVar5 = *param_4;
  }
  if (uVar5 != 0) {
    puVar9 = (undefined4 *)param_4[1];
    puVar11 = puVar8;
    if (((7 < uVar5) && (uVar6 = uVar5 & 0xfffffffffffffff8, uVar6 != 0)) &&
       (((undefined4 *)((long)puVar9 + 1U) <= puVar8 || (puVar8 + uVar5 <= puVar9)))) {
      uVar1 = *puVar9;
      puVar15 = (undefined8 *)(puVar8 + 4);
      uVar12 = uVar6;
      do {
        puVar15[-1] = CONCAT44(uVar1,uVar1);
        puVar15[-2] = CONCAT44(uVar1,uVar1);
        puVar15[1] = CONCAT44(uVar1,uVar1);
        *puVar15 = CONCAT44(uVar1,uVar1);
        uVar12 = uVar12 - 8;
        puVar15 = puVar15 + 4;
      } while (uVar12 != 0);
      bVar3 = uVar5 == uVar6;
      uVar5 = uVar5 - uVar6;
      puVar11 = puVar8 + uVar6;
      if (bVar3) goto code_r0x02285cf0;
    }
    do {
      uVar5 = uVar5 - 1;
      *puVar11 = *puVar9;
      puVar11 = puVar11 + 1;
    } while (uVar5 != 0);
  }
code_r0x02285cf0:
  puVar9 = *(undefined4 **)(param_1 + 0x10);
  puVar11 = puVar8 + param_3;
  if (puVar9 == param_2) goto code_r0x02285db4;
  uVar6 = (long)puVar9 + (-4 - (long)param_2);
  uVar12 = uVar6 >> 2;
  uVar5 = uVar12 + 1;
  puVar13 = puVar11;
  if (((uVar5 < 8) || (uVar14 = uVar5 & 0x7ffffffffffffff8, uVar14 == 0)) ||
     ((puVar11 < param_2 + uVar12 + 1 && (param_2 < puVar8 + uVar12 + param_3 + 1)))) {
code_r0x02285d98:
    do {
      puVar17 = param_2 + 1;
      *puVar13 = *param_2;
      puVar13 = puVar13 + 1;
      param_2 = puVar17;
    } while (puVar9 != puVar17);
  }
  else {
    puVar15 = (undefined8 *)(param_2 + 4);
    param_2 = param_2 + uVar14;
    puVar16 = (undefined8 *)(puVar8 + param_3 + 4);
    uVar12 = uVar14;
    do {
      puVar2 = puVar15 + -1;
      uVar18 = puVar15[-2];
      uVar20 = puVar15[1];
      uVar19 = *puVar15;
      puVar15 = puVar15 + 4;
      uVar12 = uVar12 - 8;
      puVar16[-1] = *puVar2;
      puVar16[-2] = uVar18;
      puVar16[1] = uVar20;
      *puVar16 = uVar19;
      puVar16 = puVar16 + 4;
    } while (uVar12 != 0);
    puVar13 = puVar11 + uVar14;
    if (uVar5 != uVar14) goto code_r0x02285d98;
  }
  puVar11 = (undefined4 *)((long)puVar11 + (uVar6 & 0xfffffffffffffffc) + 4);
code_r0x02285db4:
  Aska::MemoryManagerAdapter::AlignedFree(void*)(*(undefined8 *)(param_1 + 8));
  *(undefined4 **)(param_1 + 8) = puVar4;
  *(undefined4 **)(param_1 + 0x10) = puVar11;
  *(undefined4 **)(param_1 + 0x18) = puVar4 + uVar7;
  return puVar8;
}

// ==== Aska::TPoolFast<Aska::Vector, false>::SecurePool(unsigned int, Aska::Vector*)
// vaddr 0x21c8080 | ghidra 0x22c8080 | size 408 | symbol _ZN4Aska9TPoolFastINS_6VectorELb0EE10SecurePoolEjPS1_ | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska9TPoolFastINS_6VectorELb0EE10SecurePoolEjPS1_(long param_1,uint param_2,long param_3)

{
  bool bVar1;
  char cVar2;
  long lVar3;
  ulong uVar4;
  long lVar5;
  long *plVar6;
  
  if (*(char *)(param_1 + 0x41) == '\0') {
    *(undefined8 *)(param_1 + 0x30) = 0;
  }
  else {
    if (*(long *)(param_1 + 0x30) != 0) {
      operator delete[](void*)();
      *(undefined8 *)(param_1 + 0x30) = 0;
    }
    *(undefined1 *)(param_1 + 0x41) = 0;
  }
  plVar6 = (long *)(param_1 + 0x18);
  if ((*plVar6 != 0) && (*(char *)(param_1 + 0x28) != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 0x28) = 0;
  }
  *plVar6 = 0;
  *(undefined8 *)(param_1 + 0x20) = 0;
  if (param_2 == 0) {
    return 1;
  }
  if (param_3 == 0) {
    param_3 = operator new[](unsigned long, std::nothrow_t const&)((ulong)param_2 << 4,PTR__ZSt7nothrow_02cb9a80);
    if (param_3 == 0) {
      *(undefined8 *)(param_1 + 0x30) = 0;
      cVar2 = *(char *)(param_1 + 0x41);
      goto joined_r0x022c81dc;
    }
    *(long *)(param_1 + 0x30) = param_3;
    *(undefined1 *)(param_1 + 0x41) = 1;
  }
  else {
    *(long *)(param_1 + 0x30) = param_3;
  }
  uVar4 = (ulong)param_2 + 0x3f >> 6;
  *(int *)(param_1 + 0x20) = (int)uVar4;
  *(uint *)(param_1 + 0x24) = param_2;
  lVar5 = uVar4 << 3;
  lVar3 = operator new[](unsigned long, std::nothrow_t const&)(lVar5,PTR__ZSt7nothrow_02cb9a80);
  *(long *)(param_1 + 0x18) = lVar3;
  *(undefined1 *)(param_1 + 0x28) = 1;
  if (lVar3 != 0) {
    memset(lVar3,0,lVar5);
    *(undefined8 *)(param_1 + 0x38) = 0;
    memset(lVar3,0,lVar5);
    return 1;
  }
  *(undefined1 *)(param_1 + 0x28) = 0;
  *(undefined8 *)(param_1 + 0x20) = 0;
  cVar2 = *(char *)(param_1 + 0x41);
joined_r0x022c81dc:
  if (cVar2 == '\0') {
    *(undefined8 *)(param_1 + 0x30) = 0;
  }
  else {
    if (param_3 == 0) {
      lVar3 = 0;
      *(undefined1 *)(param_1 + 0x41) = 0;
      bVar1 = false;
    }
    else {
      operator delete[](void*)(param_3);
      lVar3 = *(long *)(param_1 + 0x18);
      *(undefined8 *)(param_1 + 0x30) = 0;
      *(undefined1 *)(param_1 + 0x41) = 0;
      bVar1 = lVar3 != 0;
    }
    if ((bVar1) && (*(char *)(param_1 + 0x28) != '\0')) {
      operator delete[](void*)(lVar3);
      *(undefined1 *)(param_1 + 0x28) = 0;
    }
  }
  *plVar6 = 0;
  *(undefined8 *)(param_1 + 0x20) = 0;
  return 0;
}

// ==== Aska::TPoolFast<Aska::Vector, false>::~TPoolFast()
// vaddr 0x21c85ec | ghidra 0x22c85ec | size 124 | symbol _ZN4Aska9TPoolFastINS_6VectorELb0EED2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska9TPoolFastINS_6VectorELb0EED2Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska9TPoolFastINS_6VectorELb0EEE_02cc3840 + 0x10);
  if (*(char *)((long)param_1 + 0x41) == '\0') {
    param_1[6] = 0;
  }
  else {
    if (param_1[6] != 0) {
      operator delete[](void*)();
      param_1[6] = 0;
    }
    *(undefined1 *)((long)param_1 + 0x41) = 0;
  }
  if ((param_1[3] != 0) && ((char)param_1[5] != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 5) = 0;
  }
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[1] = (long)(PTR__ZTVN4Aska13TSmartPointerILb0EEE_02cc2320 + 0x10);
  return;
}

// ==== Aska::TPoolFast<Aska::Vector, false>::~TPoolFast()
// vaddr 0x21c86cc | ghidra 0x22c86cc | size 100 | symbol _ZN4Aska9TPoolFastINS_6VectorELb0EED0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska9TPoolFastINS_6VectorELb0EED0Ev(long *param_1)

{
  long lVar1;
  
  *param_1 = (long)(PTR__ZTVN4Aska9TPoolFastINS_6VectorELb0EEE_02cc3840 + 0x10);
  if (*(char *)((long)param_1 + 0x41) == '\0') {
    param_1[6] = 0;
    lVar1 = param_1[3];
  }
  else {
    if (param_1[6] != 0) {
      operator delete[](void*)();
      param_1[6] = 0;
    }
    *(undefined1 *)((long)param_1 + 0x41) = 0;
    lVar1 = param_1[3];
  }
  if ((lVar1 != 0) && ((char)param_1[5] != '\0')) {
    operator delete[](void*)();
  }
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::TArray<unsigned int, true>::~TArray()
// vaddr 0x25a1ed0 | ghidra 0x26a1ed0 | size 68 | symbol _ZN4Aska6TArrayIjLb1EED2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6TArrayIjLb1EED2Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska6TArrayIjLb1EEE_02cc3a70 + 0x10);
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

// ==== Aska::TArray<unsigned int, true>::Resize(long, bool)
// vaddr 0x25a238c | ghidra 0x26a238c | size 252 | symbol _ZN4Aska6TArrayIjLb1EE6ResizeElb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6TArrayIjLb1EE6ResizeElb(long param_1,long param_2)

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
    goto code_r0x026a246c;
  }
  if (*(long *)(param_1 + 8) == 0) {
    lVar3 = *(long *)(param_1 + 0x28);
    if (*(long *)(param_1 + 0x28) <= param_2) {
      lVar3 = param_2;
    }
    lVar1 = operator new[](unsigned long, std::nothrow_t const&)(lVar3 << 2,PTR__ZSt7nothrow_02cb9a80);
    *(long *)(param_1 + 8) = lVar1;
    if (lVar1 == 0) {
      *(ushort *)(param_1 + 0x30) = *(ushort *)(param_1 + 0x30) | 1;
      return;
    }
    uVar2 = *(ushort *)(param_1 + 0x30) & 0xfffe;
code_r0x026a2464:
    *(ushort *)(param_1 + 0x30) = uVar2;
  }
  else {
    lVar1 = operator new[](unsigned long, void*, unsigned long)(param_2 << 3,*(long *)(param_1 + 8),4);
    if (lVar1 == 0) {
      uVar2 = *(ushort *)(param_1 + 0x30) | 1;
      goto code_r0x026a2464;
    }
    *(long *)(param_1 + 8) = lVar1;
    *(long *)(param_1 + 0x10) = lVar3;
    *(long *)(param_1 + 0x18) = param_2;
  }
  *(long *)(param_1 + 0x10) = lVar3;
code_r0x026a246c:
  *(long *)(param_1 + 0x18) = param_2;
  return;
}

// ==== Aska::TArray<unsigned int, true>::~TArray()
// vaddr 0x25a2488 | ghidra 0x26a2488 | size 60 | symbol _ZN4Aska6TArrayIjLb1EED0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6TArrayIjLb1EED0Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska6TArrayIjLb1EEE_02cc3a70 + 0x10);
  *(ushort *)((long)param_1 + 0x32) = *(ushort *)((long)param_1 + 0x32) | 1;
  if (param_1[1] != 0) {
    operator delete[](void*)();
  }
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}
