// port/decomp/libcxx/hash.c: Ghidra decompiles for the libcxx subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-04 05:14 UTC: tools/decomp.sh '--into' 'libcxx/hash' 'unordered_map<unsigned_int,bool.*operator\[\]' '__hash_value_type<unsigned_int,bool>.*__rehash' '__next_prime'

// ==== std::__ndk1::unordered_map<unsigned int, bool, std::__ndk1::hash<unsigned int>, std::__ndk1::equal_to<unsigned int>, Framework::CSTLAllocator<std::__ndk1::pair<unsigned int const, bool>, Framework::CSTLUnorderedMapAllocatorInf> >::operator[](unsigned int&&)
// vaddr 0x17e59a4 | ghidra 0x18e59a4 | size 500 | symbol _ZNSt6__ndk113unordered_mapIjbNS_4hashIjEENS_8equal_toIjEEN9Framework13CSTLAllocatorINS_4pairIKjbEENS5_28CSTLUnorderedMapAllocatorInfEEEEixEOj | lib libSOA-3.7.0.so | 2026-10-04
long _ZNSt6__ndk113unordered_mapIjbNS_4hashIjEENS_8equal_toIjEEN9Framework13CSTLAllocatorINS_4pairIKjbEENS5_28CSTLUnorderedMapAllocatorInfEEEEixEOj
               (long *param_1,uint *param_2)

{
  uint uVar1;
  ulong uVar2;
  ulong uVar3;
  long *plVar4;
  long *plVar5;
  ulong uVar6;
  ulong uVar7;
  ulong unaff_x24;
  
  uVar6 = param_1[1];
  uVar1 = *param_2;
  uVar7 = (ulong)uVar1;
  if (uVar6 != 0) {
    uVar3 = uVar6 - 1;
    if ((uVar3 & uVar6) == 0) {
      unaff_x24 = uVar3 & uVar7;
    }
    else {
      uVar2 = 0;
      if (uVar6 != 0) {
        uVar2 = uVar7 / uVar6;
      }
      unaff_x24 = uVar7 - uVar2 * uVar6;
    }
    plVar5 = *(long **)(*param_1 + unaff_x24 * 8);
    if (plVar5 != (long *)0x0) {
      if ((uVar3 & uVar6) == 0) {
        do {
          plVar5 = (long *)*plVar5;
          if ((plVar5 == (long *)0x0) || ((plVar5[1] & uVar3) != unaff_x24)) goto code_r0x018e5a4c;
        } while (*(uint *)(plVar5 + 2) != uVar1);
      }
      else {
        do {
          plVar5 = (long *)*plVar5;
          if (plVar5 == (long *)0x0) goto code_r0x018e5a4c;
          uVar3 = 0;
          if (uVar6 != 0) {
            uVar3 = (ulong)plVar5[1] / uVar6;
          }
          if (plVar5[1] - uVar3 * uVar6 != unaff_x24) goto code_r0x018e5a4c;
        } while (*(uint *)(plVar5 + 2) != uVar1);
      }
      goto code_r0x018e5b80;
    }
  }
code_r0x018e5a4c:
  plVar5 = (long *)Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(0x18,&UNK_027dc2d5/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_UnorderedMap.h"*/,0x1c);
  if (plVar5 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
  }
  uVar1 = *param_2;
  *(undefined1 *)((long)plVar5 + 0x14) = 0;
  *plVar5 = 0;
  plVar5[1] = uVar7;
  *(uint *)(plVar5 + 2) = uVar1;
  if ((uVar6 == 0) || (*(float *)(param_1 + 4) * (float)uVar6 < (float)(param_1[3] + 1))) {
    if (uVar6 < 3) {
      uVar3 = 1;
    }
    else {
      uVar3 = (ulong)((uVar6 - 1 & uVar6) != 0);
    }
    uVar3 = uVar3 | uVar6 << 1;
    uVar6 = (ulong)((float)(param_1[3] + 1) / *(float *)(param_1 + 4));
    if (uVar6 <= uVar3) {
      uVar6 = uVar3;
    }
    std::__ndk1::__hash_table<std::__ndk1::__hash_value_type<unsigned int, bool>, std::__ndk1::__unordered_map_hasher<unsigned int, std::__ndk1::__hash_value_type<unsigned int, bool>, std::__ndk1::hash<unsigned int>, true>, std::__ndk1::__unordered_map_equal<unsigned int, std::__ndk1::__hash_value_type<unsigned int, bool>, std::__ndk1::equal_to<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__hash_value_type<unsigned int, bool>, Framework::CSTLUnorderedMapAllocatorInf> >::rehash(unsigned long)(param_1,uVar6);
    uVar6 = param_1[1];
    if ((uVar6 - 1 & uVar6) == 0) {
      unaff_x24 = uVar6 - 1 & uVar7;
    }
    else {
      uVar3 = 0;
      if (uVar6 != 0) {
        uVar3 = uVar7 / uVar6;
      }
      unaff_x24 = uVar7 - uVar3 * uVar6;
    }
  }
  plVar4 = *(long **)(*param_1 + unaff_x24 * 8);
  if (plVar4 == (long *)0x0) {
    plVar4 = param_1 + 2;
    *plVar5 = *plVar4;
    *plVar4 = (long)plVar5;
    *(long **)(*param_1 + unaff_x24 * 8) = plVar4;
    if (*plVar5 != 0) {
      uVar7 = *(ulong *)(*plVar5 + 8);
      if ((uVar6 - 1 & uVar6) == 0) {
        uVar7 = uVar7 & uVar6 - 1;
      }
      else {
        uVar3 = 0;
        if (uVar6 != 0) {
          uVar3 = uVar7 / uVar6;
        }
        uVar7 = uVar7 - uVar3 * uVar6;
      }
      plVar4 = (long *)(*param_1 + uVar7 * 8);
      goto code_r0x018e5b70;
    }
  }
  else {
    *plVar5 = *plVar4;
code_r0x018e5b70:
    *plVar4 = (long)plVar5;
  }
  param_1[3] = param_1[3] + 1;
code_r0x018e5b80:
  return (long)plVar5 + 0x14;
}

// ==== std::__ndk1::__hash_table<std::__ndk1::__hash_value_type<unsigned int, bool>, std::__ndk1::__unordered_map_hasher<unsigned int, std::__ndk1::__hash_value_type<unsigned int, bool>, std::__ndk1::hash<unsigned int>, true>, std::__ndk1::__unordered_map_equal<unsigned int, std::__ndk1::__hash_value_type<unsigned int, bool>, std::__ndk1::equal_to<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__hash_value_type<unsigned int, bool>, Framework::CSTLUnorderedMapAllocatorInf> >::__rehash(unsigned long)
// vaddr 0x17f6818 | ghidra 0x18f6818 | size 524 | symbol _ZNSt6__ndk112__hash_tableINS_17__hash_value_typeIjbEENS_22__unordered_map_hasherIjS2_NS_4hashIjEELb1EEENS_21__unordered_map_equalIjS2_NS_8equal_toIjEELb1EEEN9Framework13CSTLAllocatorIS2_NSB_28CSTLUnorderedMapAllocatorInfEEEE8__rehashEm | lib libSOA-3.7.0.so | 2026-10-04
void _ZNSt6__ndk112__hash_tableINS_17__hash_value_typeIjbEENS_22__unordered_map_hasherIjS2_NS_4hashIjEELb1EEENS_21__unordered_map_equalIjS2_NS_8equal_toIjEELb1EEEN9Framework13CSTLAllocatorIS2_NSB_28CSTLUnorderedMapAllocatorInfEEEE8__rehashEm
               (long *param_1,ulong param_2)

{
  long lVar1;
  long lVar2;
  ulong uVar3;
  ulong uVar4;
  long *plVar5;
  long *plVar6;
  ulong uVar7;
  long *plVar8;
  long *plVar9;
  
  if (param_2 == 0) {
    lVar1 = *param_1;
    *param_1 = 0;
    if (lVar1 != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)();
    }
    param_1[1] = 0;
  }
  else {
    lVar1 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(param_2 << 3,&UNK_027dc2d5/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_UnorderedMap.h"*/,0x1c);
    if (lVar1 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    }
    lVar2 = *param_1;
    *param_1 = lVar1;
    if (lVar2 != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)();
    }
    uVar3 = 0;
    param_1[1] = param_2;
    do {
      *(undefined8 *)(*param_1 + uVar3 * 8) = 0;
      uVar3 = uVar3 + 1;
    } while (param_2 != uVar3);
    plVar5 = (long *)param_1[2];
    if (plVar5 != (long *)0x0) {
      uVar3 = plVar5[1];
      uVar4 = param_2 - 1;
      if ((uVar4 & param_2) == 0) {
        uVar3 = uVar3 & uVar4;
      }
      else {
        uVar7 = 0;
        if (param_2 != 0) {
          uVar7 = uVar3 / param_2;
        }
        uVar3 = uVar3 - uVar7 * param_2;
      }
      *(long **)(*param_1 + uVar3 * 8) = param_1 + 2;
      plVar6 = (long *)*plVar5;
joined_r0x018f68dc:
      if (plVar6 != (long *)0x0) {
        if ((uVar4 & param_2) == 0) {
          do {
            uVar7 = plVar6[1] & uVar4;
            if (uVar7 == uVar3) {
              plVar8 = (long *)*plVar6;
              plVar5 = plVar6;
            }
            else {
              plVar8 = (long *)(*param_1 + uVar7 * 8);
              plVar9 = plVar6;
              if (*plVar8 == 0) goto code_r0x018f6a00;
              do {
                plVar8 = plVar9;
                plVar9 = (long *)*plVar8;
                if (plVar9 == (long *)0x0) break;
              } while ((int)plVar6[2] == (int)plVar9[2]);
              *plVar5 = (long)plVar9;
              *plVar8 = **(long **)(*param_1 + uVar7 * 8);
              **(undefined8 **)(*param_1 + uVar7 * 8) = plVar6;
              plVar8 = (long *)*plVar5;
            }
            plVar6 = plVar8;
            if (plVar6 == (long *)0x0) {
              return;
            }
          } while( true );
        }
        do {
          uVar7 = 0;
          if (param_2 != 0) {
            uVar7 = (ulong)plVar6[1] / param_2;
          }
          uVar7 = plVar6[1] - uVar7 * param_2;
          if (uVar7 == uVar3) {
            plVar8 = (long *)*plVar6;
            plVar5 = plVar6;
          }
          else {
            plVar8 = (long *)(*param_1 + uVar7 * 8);
            plVar9 = plVar6;
            if (*plVar8 == 0) goto code_r0x018f6a00;
            do {
              plVar8 = plVar9;
              plVar9 = (long *)*plVar8;
              if (plVar9 == (long *)0x0) break;
            } while ((int)plVar6[2] == (int)plVar9[2]);
            *plVar5 = (long)plVar9;
            *plVar8 = **(long **)(*param_1 + uVar7 * 8);
            **(undefined8 **)(*param_1 + uVar7 * 8) = plVar6;
            plVar8 = (long *)*plVar5;
          }
          plVar6 = plVar8;
          if (plVar6 == (long *)0x0) {
            return;
          }
        } while( true );
      }
    }
  }
  return;
code_r0x018f6a00:
  *plVar8 = (long)plVar5;
  plVar5 = plVar6;
  plVar6 = (long *)*plVar6;
  uVar3 = uVar7;
  goto joined_r0x018f68dc;
}

// ==== std::__ndk1::__next_prime(unsigned long)
// vaddr 0x265aba8 | ghidra 0x275aba8 | size 1868 | symbol _ZNSt6__ndk112__next_primeEm | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZNSt6__ndk112__next_primeEm(ulong param_1)

{
  ulong uVar1;
  ulong uVar2;
  ulong uVar3;
  long *plVar4;
  undefined8 uVar5;
  uint *puVar6;
  ulong uVar7;
  long lVar8;
  long lVar9;
  int iVar10;
  ulong uVar11;
  ulong uVar12;
  
  if (param_1 < 0xd4) {
    puVar6 = (uint *)&UNK_02a4d6c8;
    lVar9 = 0x30;
    while (lVar8 = lVar9, lVar8 != 0) {
      lVar9 = lVar8;
      if (lVar8 < 0) {
        lVar9 = lVar8 + 1;
      }
      lVar9 = lVar9 >> 1;
      if (puVar6[lVar9] < param_1) {
        puVar6 = puVar6 + lVar9 + 1;
        lVar9 = (lVar8 + -1) - lVar9;
      }
    }
    return (ulong)*puVar6;
  }
  if (0xffffffffffffffc5 < param_1) {
    plVar4 = (long *)__cxa_allocate_exception(0x10);
    std::runtime_error::runtime_error(char const*)(plVar4,&UNK_02a4d848/*"__next_prime overflow"*/);
    *plVar4 = (long)(PTR__ZTVSt14overflow_error_02cbed90 + 0x10);
    uVar5 = __cxa_throw(plVar4,PTR__ZTISt14overflow_error_02cc4448,
                            PTR__ZNSt15underflow_errorD1Ev_02cb6d30);
    __cxa_free_exception(plVar4);
    lVar9 = _Unwind_Resume(uVar5);
    return (ulong)((*(byte *)(lVar9 + 0x20) & 5) == 0);
  }
  uVar7 = param_1 / 0xd2;
  puVar6 = (uint *)&UNK_02a4d788;
  lVar9 = 0x30;
  while (lVar8 = lVar9, lVar8 != 0) {
    lVar9 = lVar8;
    if (lVar8 < 0) {
      lVar9 = lVar8 + 1;
    }
    lVar9 = lVar9 >> 1;
    if ((ulong)puVar6[lVar9] < param_1 % 0xd2) {
      puVar6 = puVar6 + lVar9 + 1;
      lVar9 = (lVar8 + -1) - lVar9;
    }
  }
  lVar9 = (long)(puVar6 + -0xa935e2) >> 2;
  do {
    lVar8 = lVar9;
    uVar2 = uVar7 * 0xd2 + (ulong)*(uint *)(&UNK_02a4d788 + lVar8 * 4);
    uVar11 = 5;
    do {
      uVar12 = (ulong)*(uint *)(&UNK_02a4d6c8 + uVar11 * 4);
      uVar3 = 0;
      if (uVar12 != 0) {
        uVar3 = uVar2 / uVar12;
      }
      if (uVar3 < uVar12) {
        return uVar2;
      }
      if (uVar2 == uVar3 * uVar12) goto code_r0x0275ac98;
      uVar11 = uVar11 + 1;
    } while (uVar11 < 0x2f);
    uVar11 = 0xd3;
    do {
      uVar3 = 0;
      if (uVar11 != 0) {
        uVar3 = uVar2 / uVar11;
      }
      if (uVar3 < uVar11) {
        iVar10 = 1;
        param_1 = uVar2;
        break;
      }
      if (uVar2 == uVar3 * uVar11) {
        iVar10 = 9;
        break;
      }
      uVar3 = uVar11 + 10;
      uVar12 = 0;
      if (uVar3 != 0) {
        uVar12 = uVar2 / uVar3;
      }
      if (uVar12 < uVar3) {
code_r0x0275ad30:
        iVar10 = 1;
        param_1 = uVar2;
        break;
      }
      if (uVar2 == uVar12 * uVar3) {
code_r0x0275ad54:
        iVar10 = 9;
        break;
      }
      uVar3 = uVar11 + 0xc;
      uVar12 = 0;
      if (uVar3 != 0) {
        uVar12 = uVar2 / uVar3;
      }
      if (uVar12 < uVar3) goto code_r0x0275ad30;
      if (uVar2 == uVar12 * uVar3) goto code_r0x0275ad54;
      uVar3 = uVar11 + 0x10;
      uVar12 = 0;
      if (uVar3 != 0) {
        uVar12 = uVar2 / uVar3;
      }
      if (uVar12 < uVar3) goto code_r0x0275ad30;
      if (uVar2 == uVar12 * uVar3) goto code_r0x0275ad54;
      uVar3 = uVar11 + 0x12;
      uVar12 = 0;
      if (uVar3 != 0) {
        uVar12 = uVar2 / uVar3;
      }
      if (uVar12 < uVar3) goto code_r0x0275ad30;
      if (uVar2 == uVar12 * uVar3) goto code_r0x0275ad54;
      uVar3 = uVar11 + 0x16;
      uVar12 = 0;
      if (uVar3 != 0) {
        uVar12 = uVar2 / uVar3;
      }
      if (uVar12 < uVar3) goto code_r0x0275ad30;
      if (uVar2 == uVar12 * uVar3) goto code_r0x0275ad54;
      uVar3 = uVar11 + 0x1c;
      uVar12 = 0;
      if (uVar3 != 0) {
        uVar12 = uVar2 / uVar3;
      }
      if (uVar12 < uVar3) goto code_r0x0275ad30;
      if (uVar2 == uVar12 * uVar3) goto code_r0x0275ad54;
      uVar3 = uVar11 + 0x1e;
      uVar12 = 0;
      if (uVar3 != 0) {
        uVar12 = uVar2 / uVar3;
      }
      if (uVar12 < uVar3) goto code_r0x0275ad30;
      if (uVar2 == uVar12 * uVar3) goto code_r0x0275ad54;
      uVar3 = uVar11 + 0x24;
      uVar12 = 0;
      if (uVar3 != 0) {
        uVar12 = uVar2 / uVar3;
      }
      if (uVar12 < uVar3) goto code_r0x0275ad30;
      if (uVar2 == uVar12 * uVar3) goto code_r0x0275ad54;
      uVar3 = uVar11 + 0x28;
      uVar12 = 0;
      if (uVar3 != 0) {
        uVar12 = uVar2 / uVar3;
      }
      if (uVar12 < uVar3) goto code_r0x0275ad30;
      if (uVar2 == uVar12 * uVar3) goto code_r0x0275ad54;
      uVar3 = uVar11 + 0x2a;
      uVar12 = 0;
      if (uVar3 != 0) {
        uVar12 = uVar2 / uVar3;
      }
      if (uVar12 < uVar3) goto code_r0x0275ad30;
      if (uVar2 == uVar12 * uVar3) goto code_r0x0275ad54;
      uVar3 = uVar11 + 0x2e;
      uVar12 = 0;
      if (uVar3 != 0) {
        uVar12 = uVar2 / uVar3;
      }
      if (uVar12 < uVar3) goto code_r0x0275ad30;
      if (uVar2 == uVar12 * uVar3) goto code_r0x0275ad54;
      uVar3 = uVar11 + 0x34;
      uVar12 = 0;
      if (uVar3 != 0) {
        uVar12 = uVar2 / uVar3;
      }
      if (uVar12 < uVar3) goto code_r0x0275ad30;
      if (uVar2 == uVar12 * uVar3) goto code_r0x0275ad54;
      uVar3 = uVar11 + 0x3a;
      uVar12 = 0;
      if (uVar3 != 0) {
        uVar12 = uVar2 / uVar3;
      }
      if (uVar12 < uVar3) goto code_r0x0275ad30;
      if (uVar2 == uVar12 * uVar3) goto code_r0x0275ad54;
      uVar3 = uVar11 + 0x3c;
      uVar12 = 0;
      if (uVar3 != 0) {
        uVar12 = uVar2 / uVar3;
      }
      if (uVar12 < uVar3) goto code_r0x0275ad30;
      if (uVar2 == uVar12 * uVar3) goto code_r0x0275ad54;
      uVar3 = uVar11 + 0x42;
      uVar12 = 0;
      if (uVar3 != 0) {
        uVar12 = uVar2 / uVar3;
      }
      if (uVar12 < uVar3) goto code_r0x0275ad30;
      if (uVar2 == uVar12 * uVar3) goto code_r0x0275ad54;
      uVar3 = uVar11 + 0x46;
      uVar12 = 0;
      if (uVar3 != 0) {
        uVar12 = uVar2 / uVar3;
      }
      if (uVar12 < uVar3) goto code_r0x0275ad30;
      if (uVar2 == uVar12 * uVar3) goto code_r0x0275ad54;
      uVar3 = uVar11 + 0x48;
      uVar12 = 0;
      if (uVar3 != 0) {
        uVar12 = uVar2 / uVar3;
      }
      if (uVar12 < uVar3) goto code_r0x0275ad30;
      if (uVar2 == uVar12 * uVar3) goto code_r0x0275ad54;
      uVar3 = uVar11 + 0x4e;
      uVar12 = 0;
      if (uVar3 != 0) {
        uVar12 = uVar2 / uVar3;
      }
      if (uVar12 < uVar3) goto code_r0x0275ad30;
      if (uVar2 == uVar12 * uVar3) goto code_r0x0275ad54;
      uVar3 = uVar11 + 0x52;
      uVar12 = 0;
      if (uVar3 != 0) {
        uVar12 = uVar2 / uVar3;
      }
      if (uVar12 < uVar3) goto code_r0x0275ad30;
      if (uVar2 == uVar12 * uVar3) goto code_r0x0275ad54;
      uVar3 = uVar11 + 0x58;
      uVar12 = 0;
      if (uVar3 != 0) {
        uVar12 = uVar2 / uVar3;
      }
      if (uVar12 < uVar3) goto code_r0x0275ad30;
      if (uVar2 == uVar12 * uVar3) goto code_r0x0275ad54;
      uVar3 = uVar11 + 0x60;
      uVar12 = 0;
      if (uVar3 != 0) {
        uVar12 = uVar2 / uVar3;
      }
      if (uVar12 < uVar3) goto code_r0x0275ad30;
      if (uVar2 == uVar12 * uVar3) goto code_r0x0275ad54;
      uVar3 = uVar11 + 100;
      uVar12 = 0;
      if (uVar3 != 0) {
        uVar12 = uVar2 / uVar3;
      }
      if (uVar12 < uVar3) goto code_r0x0275ad30;
      if (uVar2 == uVar12 * uVar3) goto code_r0x0275ad54;
      uVar3 = uVar11 + 0x66;
      uVar12 = 0;
      if (uVar3 != 0) {
        uVar12 = uVar2 / uVar3;
      }
      if (uVar12 < uVar3) goto code_r0x0275ad30;
      if (uVar2 == uVar12 * uVar3) goto code_r0x0275ad54;
      uVar3 = uVar11 + 0x6a;
      uVar12 = 0;
      if (uVar3 != 0) {
        uVar12 = uVar2 / uVar3;
      }
      if (uVar12 < uVar3) goto code_r0x0275ad30;
      if (uVar2 == uVar12 * uVar3) goto code_r0x0275ad54;
      uVar3 = uVar11 + 0x6c;
      uVar12 = 0;
      if (uVar3 != 0) {
        uVar12 = uVar2 / uVar3;
      }
      if (uVar12 < uVar3) goto code_r0x0275ad30;
      if (uVar2 == uVar12 * uVar3) goto code_r0x0275ad54;
      uVar3 = uVar11 + 0x70;
      uVar12 = 0;
      if (uVar3 != 0) {
        uVar12 = uVar2 / uVar3;
      }
      if (uVar12 < uVar3) goto code_r0x0275ad30;
      if (uVar2 == uVar12 * uVar3) goto code_r0x0275ad54;
      uVar3 = uVar11 + 0x78;
      uVar12 = 0;
      if (uVar3 != 0) {
        uVar12 = uVar2 / uVar3;
      }
      if (uVar12 < uVar3) goto code_r0x0275ad30;
      if (uVar2 == uVar12 * uVar3) goto code_r0x0275ad54;
      uVar3 = uVar11 + 0x7e;
      uVar12 = 0;
      if (uVar3 != 0) {
        uVar12 = uVar2 / uVar3;
      }
      if (uVar12 < uVar3) goto code_r0x0275ad30;
      if (uVar2 == uVar12 * uVar3) goto code_r0x0275ad54;
      uVar3 = uVar11 + 0x82;
      uVar12 = 0;
      if (uVar3 != 0) {
        uVar12 = uVar2 / uVar3;
      }
      if (uVar12 < uVar3) goto code_r0x0275ad30;
      if (uVar2 == uVar12 * uVar3) goto code_r0x0275ad54;
      uVar3 = uVar11 + 0x88;
      uVar12 = 0;
      if (uVar3 != 0) {
        uVar12 = uVar2 / uVar3;
      }
      if (uVar12 < uVar3) goto code_r0x0275ad30;
      if (uVar2 == uVar12 * uVar3) goto code_r0x0275ad54;
      uVar3 = uVar11 + 0x8a;
      uVar12 = 0;
      if (uVar3 != 0) {
        uVar12 = uVar2 / uVar3;
      }
      if (uVar12 < uVar3) goto code_r0x0275ad30;
      if (uVar2 == uVar12 * uVar3) goto code_r0x0275ad54;
      uVar3 = uVar11 + 0x8e;
      uVar12 = 0;
      if (uVar3 != 0) {
        uVar12 = uVar2 / uVar3;
      }
      if (uVar12 < uVar3) goto code_r0x0275ad30;
      if (uVar2 == uVar12 * uVar3) goto code_r0x0275ad54;
      uVar3 = uVar11 + 0x94;
      uVar12 = 0;
      if (uVar3 != 0) {
        uVar12 = uVar2 / uVar3;
      }
      if (uVar12 < uVar3) goto code_r0x0275ad30;
      if (uVar2 == uVar12 * uVar3) goto code_r0x0275ad54;
      uVar3 = uVar11 + 0x96;
      uVar12 = 0;
      if (uVar3 != 0) {
        uVar12 = uVar2 / uVar3;
      }
      if (uVar12 < uVar3) goto code_r0x0275ad30;
      if (uVar2 == uVar12 * uVar3) goto code_r0x0275ad54;
      uVar3 = uVar11 + 0x9c;
      uVar12 = 0;
      if (uVar3 != 0) {
        uVar12 = uVar2 / uVar3;
      }
      if (uVar12 < uVar3) goto code_r0x0275ad30;
      if (uVar2 == uVar12 * uVar3) goto code_r0x0275ad54;
      uVar3 = uVar11 + 0xa2;
      uVar12 = 0;
      if (uVar3 != 0) {
        uVar12 = uVar2 / uVar3;
      }
      if (uVar12 < uVar3) goto code_r0x0275ad30;
      if (uVar2 == uVar12 * uVar3) goto code_r0x0275ad54;
      uVar3 = uVar11 + 0xa6;
      uVar12 = 0;
      if (uVar3 != 0) {
        uVar12 = uVar2 / uVar3;
      }
      if (uVar12 < uVar3) goto code_r0x0275ad30;
      if (uVar2 == uVar12 * uVar3) goto code_r0x0275ad54;
      uVar3 = uVar11 + 0xa8;
      uVar12 = 0;
      if (uVar3 != 0) {
        uVar12 = uVar2 / uVar3;
      }
      if (uVar12 < uVar3) goto code_r0x0275ad30;
      if (uVar2 == uVar12 * uVar3) goto code_r0x0275ad54;
      uVar3 = uVar11 + 0xac;
      uVar12 = 0;
      if (uVar3 != 0) {
        uVar12 = uVar2 / uVar3;
      }
      if (uVar12 < uVar3) goto code_r0x0275ad30;
      if (uVar2 == uVar12 * uVar3) goto code_r0x0275ad54;
      uVar3 = uVar11 + 0xb2;
      uVar12 = 0;
      if (uVar3 != 0) {
        uVar12 = uVar2 / uVar3;
      }
      if (uVar12 < uVar3) goto code_r0x0275ad30;
      if (uVar2 == uVar12 * uVar3) goto code_r0x0275ad54;
      uVar3 = uVar11 + 0xb4;
      uVar12 = 0;
      if (uVar3 != 0) {
        uVar12 = uVar2 / uVar3;
      }
      if (uVar12 < uVar3) goto code_r0x0275ad30;
      if (uVar2 == uVar12 * uVar3) goto code_r0x0275ad54;
      uVar3 = uVar11 + 0xba;
      uVar12 = 0;
      if (uVar3 != 0) {
        uVar12 = uVar2 / uVar3;
      }
      if (uVar12 < uVar3) goto code_r0x0275ad30;
      if (uVar2 == uVar12 * uVar3) goto code_r0x0275ad54;
      uVar3 = uVar11 + 0xbe;
      uVar12 = 0;
      if (uVar3 != 0) {
        uVar12 = uVar2 / uVar3;
      }
      if (uVar12 < uVar3) goto code_r0x0275ad30;
      if (uVar2 == uVar12 * uVar3) goto code_r0x0275ad54;
      uVar3 = uVar11 + 0xc0;
      uVar12 = 0;
      if (uVar3 != 0) {
        uVar12 = uVar2 / uVar3;
      }
      if (uVar12 < uVar3) goto code_r0x0275ad30;
      if (uVar2 == uVar12 * uVar3) goto code_r0x0275ad54;
      uVar3 = uVar11 + 0xc4;
      uVar12 = 0;
      if (uVar3 != 0) {
        uVar12 = uVar2 / uVar3;
      }
      if (uVar12 < uVar3) goto code_r0x0275ad30;
      if (uVar2 == uVar12 * uVar3) goto code_r0x0275ad54;
      uVar3 = uVar11 + 0xc6;
      uVar12 = 0;
      if (uVar3 != 0) {
        uVar12 = uVar2 / uVar3;
      }
      if (uVar12 < uVar3) goto code_r0x0275ad30;
      if (uVar2 == uVar12 * uVar3) goto code_r0x0275ad54;
      uVar3 = uVar11 + 0xd0;
      uVar12 = 0;
      if (uVar3 != 0) {
        uVar12 = uVar2 / uVar3;
      }
      if (uVar12 < uVar3) goto code_r0x0275ad30;
      uVar1 = uVar11 + 0xd2;
      iVar10 = 9;
      uVar11 = uVar3;
      if (uVar2 != uVar12 * uVar3) {
        iVar10 = 0;
        uVar11 = uVar1;
      }
    } while (iVar10 == 0);
    if ((iVar10 != 9) && (iVar10 != 0)) {
      return param_1;
    }
code_r0x0275ac98:
    if (lVar8 == 0x2f) {
      uVar7 = uVar7 + 1;
    }
    lVar9 = 0;
    if (lVar8 != 0x2f) {
      lVar9 = lVar8 + 1;
    }
  } while( true );
}
