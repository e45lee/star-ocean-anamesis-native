// port/decomp/master/category_skill.c: Ghidra decompiles for the master subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-08 14:52 UTC: tools/decomp.sh '--into' 'master/category_skill' 'CMasterParameterBaseSqlite_Category<CMasterParameterSkillElement>::'

// ==== CMasterParameterBaseSqlite_Category<CMasterParameterSkillElement>::pParameter(char const*, char const*) const
// vaddr 0x125fd58 | ghidra 0x135fd58 | size 456 | symbol _ZNK35CMasterParameterBaseSqlite_CategoryI28CMasterParameterSkillElementE10pParameterEPKcS3_ | lib libSOA-3.7.0.so | 2026-10-08
void _ZNK35CMasterParameterBaseSqlite_CategoryI28CMasterParameterSkillElementE10pParameterEPKcS3_
               (undefined8 param_1,long *param_2,undefined8 param_3,undefined8 param_4)

{
  ulong uVar1;
  ulong uVar2;
  uint uVar3;
  undefined4 uVar4;
  ulong uVar5;
  ulong uVar6;
  long lVar7;
  undefined1 auStack_68 [16];
  undefined8 uStack_58;
  ulong uStack_50;
  ulong uStack_48;
  
  uStack_50 = 0;
  uStack_48 = 0;
  uStack_58 = 0;
  uVar5 = (**(code **)(*param_2 + 0x58))();
  if ((uVar5 & 1) == 0) {
    uVar6 = strlen(param_4);
    uVar5 = 0;
    lVar7 = 0x16;
  }
  else {
    uVar6 = strlen(param_3);
    if (uVar6 < 0x16 || uVar6 - 0x16 == 0) {
      if (uVar6 != 0) {
        memcpy((ulong)&uStack_58 | 1,param_3,uVar6);
      }
      uVar3 = (int)uVar6 << 1;
      uVar5 = (ulong)uVar3;
      *(undefined1 *)((long)&uStack_58 + uVar6 + 1) = 0;
      uStack_58 = CONCAT71(uStack_58._1_7_,(char)uVar3);
    }
    else {
      string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&uStack_58,0x16,uVar6 - 0x16,0,0,0,uVar6,param_3);
      uVar5 = uStack_58 & 0xff;
    }
    uVar6 = strlen(param_4);
    if ((uVar5 & 1) == 0) {
      lVar7 = 0x16;
    }
    else {
      lVar7 = (uStack_58 & 0xfffffffffffffffe) - 1;
      uVar5 = uStack_58;
    }
  }
  uVar1 = (ulong)(((uint)uVar5 & 0xfe) >> 1);
  if ((uVar5 & 1) != 0) {
    uVar1 = uStack_50;
  }
  if (lVar7 - uVar1 < uVar6) {
    string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&uStack_58,lVar7,(uVar6 - lVar7) + uVar1,uVar1,uVar1,0,uVar6,param_4);
  }
  else if (uVar6 != 0) {
    uVar2 = (ulong)&uStack_58 | 1;
    if ((uVar5 & 1) != 0) {
      uVar2 = uStack_48;
    }
    memcpy(uVar2 + uVar1,param_4,uVar6);
    uVar1 = uVar1 + uVar6;
    uVar5 = uVar1;
    if ((uStack_58 & 1) == 0) {
      uStack_58 = CONCAT71(uStack_58._1_7_,(char)uVar1 * '\x02');
      uVar5 = uStack_50;
    }
    uStack_50 = uVar5;
    *(undefined1 *)(uVar2 + uVar1) = 0;
  }
  Framework::CHash32::CHash32(string const&)(auStack_68,&uStack_58);
  uVar4 = Framework::CHash32::operator unsigned int() const(auStack_68);
  CMasterParameterBaseSqlite_Category<CMasterParameterSkillElement>::pParameterFromHash(char const*, unsigned int) const(param_1,param_2,param_3,uVar4);
  Framework::CHash32::~CHash32()(auStack_68);
  if ((uStack_58 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_48);
  }
  return;
}

// ==== CMasterParameterBaseSqlite_Category<CMasterParameterSkillElement>::pParameterFromHash(char const*, unsigned int) const
// vaddr 0x127529c | ghidra 0x137529c | size 320 | symbol _ZNK35CMasterParameterBaseSqlite_CategoryI28CMasterParameterSkillElementE18pParameterFromHashEPKcj | lib libSOA-3.7.0.so | 2026-10-08
void _ZNK35CMasterParameterBaseSqlite_CategoryI28CMasterParameterSkillElementE18pParameterFromHashEPKcj
               (long *param_1,undefined8 param_2,undefined8 param_3,uint param_4)

{
  long *plVar1;
  ulong uVar2;
  undefined4 uVar3;
  long *plVar4;
  ulong uVar5;
  ulong uVar6;
  ulong uVar7;
  long *plVar8;
  long *plStack_50;
  long lStack_48;
  undefined1 auStack_40 [16];
  
  Framework::CHash32::CHash32(char const*)(auStack_40);
  uVar3 = Framework::CHash32::operator unsigned int() const(auStack_40);
  CMasterParameterBaseSqlite_Category<CMasterParameterSkillElement>::pParameterFromHash(unsigned int) const(&plStack_50,param_2,uVar3);
  Framework::CHash32::~CHash32()(auStack_40);
  if ((plStack_50 != (long *)0x0) && (uVar6 = plStack_50[1], uVar6 != 0)) {
    uVar7 = uVar6 - 1;
    uVar5 = (ulong)param_4;
    if ((uVar7 & uVar6) == 0) {
      uVar5 = uVar7 & uVar5;
    }
    else {
      uVar2 = 0;
      if (uVar6 != 0) {
        uVar2 = uVar5 / uVar6;
      }
      uVar5 = uVar5 - uVar2 * uVar6;
    }
    plVar8 = *(long **)(*plStack_50 + uVar5 * 8);
    if (plVar8 != (long *)0x0) {
      if ((uVar7 & uVar6) == 0) {
        do {
          plVar8 = (long *)*plVar8;
          if ((plVar8 == (long *)0x0) || ((plVar8[1] & uVar7) != uVar5)) goto code_r0x013753b8;
        } while (*(uint *)(plVar8 + 2) != param_4);
      }
      else {
        do {
          plVar8 = (long *)*plVar8;
          if (plVar8 == (long *)0x0) goto code_r0x013753b8;
          uVar7 = 0;
          if (uVar6 != 0) {
            uVar7 = (ulong)plVar8[1] / uVar6;
          }
          if (plVar8[1] - uVar7 * uVar6 != uVar5) goto code_r0x013753b8;
        } while (*(uint *)(plVar8 + 2) != param_4);
      }
      plVar4 = (long *)operator new(unsigned long)(0x798);
      plVar4[2] = 0;
      plVar1 = plVar4 + 3;
      *plVar4 = (long)(
                      PTR__ZTVNSt6__ndk120__shared_ptr_emplaceI28CMasterParameterSkillElement18ParameterAllocatorIS1_EEE_02cb94c8
                      + 0x10);
      plVar4[1] = 0;
      CMasterParameterSkillElement::CMasterParameterSkillElement()(plVar1);
      CMasterParameterSkillElement::operator=(CMasterParameterSkillElement const&)(plVar1,plVar8 + 3);
      *param_1 = (long)plVar1;
      param_1[1] = (long)plVar4;
      goto joined_r0x013753c0;
    }
  }
code_r0x013753b8:
  *param_1 = 0;
  param_1[1] = 0;
joined_r0x013753c0:
  if (lStack_48 != 0) {
    std::__ndk1::__shared_weak_count::__release_shared()();
  }
  return;
}

// ==== CMasterParameterBaseSqlite_Category<CMasterParameterSkillElement>::pParameterFromHash(unsigned int) const
// vaddr 0x1276090 | ghidra 0x1376090 | size 1908 | symbol _ZNK35CMasterParameterBaseSqlite_CategoryI28CMasterParameterSkillElementE18pParameterFromHashEj | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Possible PIC construction at 0x0137654c: Changing call to branch */

void _ZNK35CMasterParameterBaseSqlite_CategoryI28CMasterParameterSkillElementE18pParameterFromHashEj
               (long *param_1,long *param_2,uint param_3)

{
  int iVar1;
  long *plVar2;
  uint uVar3;
  char cVar4;
  bool bVar5;
  long *plVar6;
  ulong uVar7;
  long *plVar8;
  long *plVar9;
  ulong uVar10;
  long lVar11;
  long *plVar12;
  ulong uVar13;
  ulong uVar14;
  long lVar15;
  long lStack_a8;
  undefined8 uStack_a0;
  long *plStack_98;
  undefined8 uStack_90;
  undefined4 uStack_88;
  long lStack_80;
  long lStack_78;
  int *piStack_70;
  uint uStack_64;
  
  uVar13 = param_2[4];
  plVar2 = param_2 + 3;
  uVar7 = (ulong)param_3;
  uStack_64 = param_3;
  if (uVar13 != 0) {
    uVar14 = uVar13 - 1;
    if ((uVar14 & uVar13) == 0) {
      uVar10 = uVar14 & uVar7;
    }
    else {
      uVar10 = 0;
      if (uVar13 != 0) {
        uVar10 = uVar7 / uVar13;
      }
      uVar10 = uVar7 - uVar10 * uVar13;
    }
    plVar12 = *(long **)(*plVar2 + uVar10 * 8);
    if (plVar12 == (long *)0x0) goto code_r0x01376154;
    if ((uVar14 & uVar13) == 0) {
      do {
        plVar12 = (long *)*plVar12;
        if ((plVar12 == (long *)0x0) || ((plVar12[1] & uVar14) != uVar10)) goto code_r0x01376154;
      } while (*(uint *)(plVar12 + 2) != param_3);
    }
    else {
      do {
        plVar12 = (long *)*plVar12;
        if (plVar12 == (long *)0x0) goto code_r0x01376154;
        uVar14 = 0;
        if (uVar13 != 0) {
          uVar14 = (ulong)plVar12[1] / uVar13;
        }
        if (plVar12[1] - uVar14 * uVar13 != uVar10) goto code_r0x01376154;
      } while (*(uint *)(plVar12 + 2) != param_3);
    }
    if (plVar12 == (long *)0x0) goto code_r0x01376154;
    lVar15 = plVar12[3];
    lVar11 = plVar12[4];
code_r0x013761e0:
    *param_1 = lVar15;
    param_1[1] = lVar11;
    if (lVar11 == 0) {
      return;
    }
    goto code_r0x011d44c0;
  }
code_r0x01376154:
  uVar13 = param_2[10];
  if (uVar13 != 0) {
    uVar14 = uVar13 - 1;
    if ((uVar14 & uVar13) == 0) {
      uVar7 = uVar14 & uVar7;
    }
    else {
      uVar10 = 0;
      if (uVar13 != 0) {
        uVar10 = uVar7 / uVar13;
      }
      uVar7 = uVar7 - uVar10 * uVar13;
    }
    plVar12 = *(long **)(param_2[9] + uVar7 * 8);
    if (plVar12 != (long *)0x0) {
      if ((uVar14 & uVar13) == 0) {
        do {
          plVar12 = (long *)*plVar12;
          if ((plVar12 == (long *)0x0) || ((plVar12[1] & uVar14) != uVar7)) goto code_r0x0137620c;
        } while (*(uint *)(plVar12 + 2) != param_3);
      }
      else {
        do {
          plVar12 = (long *)*plVar12;
          if (plVar12 == (long *)0x0) goto code_r0x0137620c;
          uVar14 = 0;
          if (uVar13 != 0) {
            uVar14 = (ulong)plVar12[1] / uVar13;
          }
          if (plVar12[1] - uVar14 * uVar13 != uVar7) goto code_r0x0137620c;
        } while (*(uint *)(plVar12 + 2) != param_3);
      }
      if (plVar12 != (long *)0x0) {
        lVar15 = plVar12[3];
        lVar11 = plVar12[4];
        goto code_r0x013761e0;
      }
    }
  }
code_r0x0137620c:
  uVar7 = (**(code **)(*param_2 + 0x28))(param_2);
  if ((uVar7 & 1) == 0) {
    *param_1 = 0;
    param_1[1] = 0;
    return;
  }
  plVar12 = (long *)param_2[1];
  if (plVar12 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dc023/*"C:\BAS_Submission\Client\Project\Android\BASAndroid.NativeActivity\..\..\..\Source\Game/Parameter/Master/MasterParameterBaseSqlite.h"*/,0x4d,&UNK_027dc0a8/*"m_pConnector is null."*/);
  }
  (**(code **)(*plVar12 + 0x10))(plVar12,&UNK_027dc00a/*"sqlite/basmaster.sqlite3"*/);
  lStack_78 = 0;
  piStack_70 = (int *)0x0;
  lStack_80 = 0;
  (**(code **)(*plVar12 + 0x28))(plVar12,2,param_3,&lStack_78,&lStack_80);
  if (lStack_80 < 1) {
    *param_1 = 0;
    param_1[1] = 0;
  }
  else {
    if ((ulong)param_2[8] < (ulong)param_2[6]) {
      plVar6 = (long *)param_2[5];
      while (plVar6 != (long *)0x0) {
        lVar15 = *plVar6;
        if (plVar6[4] != 0) {
          std::__ndk1::__shared_weak_count::__release_shared()();
        }
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar6);
        plVar6 = (long *)lVar15;
      }
      lVar15 = param_2[4];
      param_2[5] = 0;
      if (lVar15 != 0) {
        lVar11 = 0;
        do {
          *(undefined8 *)(*plVar2 + lVar11 * 8) = 0;
          lVar11 = lVar11 + 1;
        } while (lVar15 != lVar11);
      }
      param_2[6] = 0;
    }
    uVar7 = 0x3f800000;
    uStack_90 = 0;
    plStack_98 = (long *)0x0;
    uStack_a0 = 0;
    lStack_a8 = 0;
    uStack_88 = 0x3f800000;
    void CMasterParameterBaseSqlite::DeserializeMsgPack<CMasterParameterSkillElement>(Aska::TSharedArray<signed char> const&, long const&, CMasterParameterSkillElement*, Framework::CSTLUnorderedMap<unsigned int, CMasterParameterSkillElement, std::__ndk1::hash<unsigned int>, std::__ndk1::equal_to<unsigned int> >*) const(param_2,&lStack_78,&lStack_80,0,&lStack_a8);
    plVar6 = (long *)operator new(unsigned long)(0x40);
    plVar6[2] = 0;
    plVar6[1] = 0;
    uVar14 = (ulong)uStack_64;
    *plVar6 = (long)(
                    PTR__ZTVNSt6__ndk120__shared_ptr_emplaceIN9Framework16CSTLUnorderedMapIj28CMasterParameterSkillElementNS_4hashIjEENS_8equal_toIjEEEE18ParameterAllocatorIS3_EEE_02cc1748
                    + 0x10);
    plVar6[4] = 0;
    plVar6[3] = 0;
    plVar6[6] = 0;
    plVar6[5] = 0;
    *(undefined4 *)(plVar6 + 7) = 0x3f800000;
    uVar13 = param_2[4];
    if (uVar13 == 0) {
code_r0x01376400:
      plVar8 = (long *)Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(0x28,&UNK_027dc2d5/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_UnorderedMap.h"*/,0x1c);
      if (plVar8 == (long *)0x0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
      }
      plVar8[3] = (long)(plVar6 + 3);
      plVar8[4] = (long)plVar6;
      *plVar8 = 0;
      plVar8[1] = uVar14;
      *(uint *)(plVar8 + 2) = uStack_64;
      if ((uVar13 == 0) || (*(float *)(param_2 + 7) * (float)uVar13 < (float)(param_2[6] + 1))) {
        if (uVar13 < 3) {
          uVar7 = 1;
        }
        else {
          uVar7 = (ulong)((uVar13 - 1 & uVar13) != 0);
        }
        uVar7 = uVar7 | uVar13 << 1;
        uVar13 = (ulong)((float)(param_2[6] + 1) / *(float *)(param_2 + 7));
        if (uVar13 <= uVar7) {
          uVar13 = uVar7;
        }
        std::__ndk1::__hash_table<std::__ndk1::__hash_value_type<unsigned int, std::__ndk1::shared_ptr<Framework::CSTLUnorderedMap<unsigned int, CMasterParameterSkillElement, std::__ndk1::hash<unsigned int>, std::__ndk1::equal_to<unsigned int> > > >, std::__ndk1::__unordered_map_hasher<unsigned int, std::__ndk1::__hash_value_type<unsigned int, std::__ndk1::shared_ptr<Framework::CSTLUnorderedMap<unsigned int, CMasterParameterSkillElement, std::__ndk1::hash<unsigned int>, std::__ndk1::equal_to<unsigned int> > > >, std::__ndk1::hash<unsigned int>, true>, std::__ndk1::__unordered_map_equal<unsigned int, std::__ndk1::__hash_value_type<unsigned int, std::__ndk1::shared_ptr<Framework::CSTLUnorderedMap<unsigned int, CMasterParameterSkillElement, std::__ndk1::hash<unsigned int>, std::__ndk1::equal_to<unsigned int> > > >, std::__ndk1::equal_to<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__hash_value_type<unsigned int, std::__ndk1::shared_ptr<Framework::CSTLUnorderedMap<unsigned int, CMasterParameterSkillElement, std::__ndk1::hash<unsigned int>, std::__ndk1::equal_to<unsigned int> > > >, Framework::CSTLUnorderedMapAllocatorInf> >::rehash(unsigned long)(plVar2,uVar13);
        uVar13 = param_2[4];
        if ((uVar13 - 1 & uVar13) == 0) {
          uVar7 = uVar13 - 1 & uVar14;
        }
        else {
          uVar7 = 0;
          if (uVar13 != 0) {
            uVar7 = uVar14 / uVar13;
          }
          uVar7 = uVar14 - uVar7 * uVar13;
        }
      }
      plVar6 = *(long **)(*plVar2 + uVar7 * 8);
      if (plVar6 == (long *)0x0) {
        plVar6 = param_2 + 5;
        *plVar8 = *plVar6;
        *plVar6 = (long)plVar8;
        *(long **)(param_2[3] + uVar7 * 8) = plVar6;
        if (*plVar8 != 0) {
          uVar7 = *(ulong *)(*plVar8 + 8);
          if ((uVar13 - 1 & uVar13) == 0) {
            uVar7 = uVar7 & uVar13 - 1;
          }
          else {
            uVar14 = 0;
            if (uVar13 != 0) {
              uVar14 = uVar7 / uVar13;
            }
            uVar7 = uVar7 - uVar14 * uVar13;
          }
          plVar6 = (long *)(*plVar2 + uVar7 * 8);
          goto code_r0x01376524;
        }
      }
      else {
        *plVar8 = *plVar6;
code_r0x01376524:
        *plVar6 = (long)plVar8;
      }
      param_2[6] = param_2[6] + 1;
    }
    else {
      uVar10 = uVar13 - 1;
      if ((uVar10 & uVar13) == 0) {
        uVar7 = uVar10 & uVar14;
      }
      else {
        uVar7 = 0;
        if (uVar13 != 0) {
          uVar7 = uVar14 / uVar13;
        }
        uVar7 = uVar14 - uVar7 * uVar13;
      }
      plVar8 = *(long **)(*plVar2 + uVar7 * 8);
      if (plVar8 == (long *)0x0) goto code_r0x01376400;
      if ((uVar10 & uVar13) == 0) {
        do {
          plVar8 = (long *)*plVar8;
          if ((plVar8 == (long *)0x0) || ((plVar8[1] & uVar10) != uVar7)) goto code_r0x01376400;
        } while (*(uint *)(plVar8 + 2) != uStack_64);
      }
      else {
        do {
          plVar8 = (long *)*plVar8;
          if (plVar8 == (long *)0x0) goto code_r0x01376400;
          uVar10 = 0;
          if (uVar13 != 0) {
            uVar10 = (ulong)plVar8[1] / uVar13;
          }
          if (plVar8[1] - uVar10 * uVar13 != uVar7) goto code_r0x01376400;
        } while (*(uint *)(plVar8 + 2) != uStack_64);
      }
      std::__ndk1::__shared_weak_count::__release_shared()(plVar6);
    }
    plVar6 = (long *)std::__ndk1::unordered_map<unsigned int, std::__ndk1::shared_ptr<Framework::CSTLUnorderedMap<unsigned int, CMasterParameterSkillElement, std::__ndk1::hash<unsigned int>, std::__ndk1::equal_to<unsigned int> > >, std::__ndk1::hash<unsigned int>, std::__ndk1::equal_to<unsigned int>, Framework::CSTLAllocator<std::__ndk1::pair<unsigned int const, std::__ndk1::shared_ptr<Framework::CSTLUnorderedMap<unsigned int, CMasterParameterSkillElement, std::__ndk1::hash<unsigned int>, std::__ndk1::equal_to<unsigned int> > > >, Framework::CSTLUnorderedMapAllocatorInf> >::operator[](unsigned int const&)(plVar2,&uStack_64);
    plVar2 = (long *)*plVar6;
    lVar11 = plVar6[1];
    if (lVar11 != 0) {
code_r0x011d44c0:
      (*(code *)PTR__ZNSt6__ndk119__shared_weak_count12__add_sharedEv_02ca2250)(lVar11);
      return;
    }
    if (plStack_98 != (long *)0x0) {
      plVar6 = plStack_98;
      do {
        while( true ) {
          uVar14 = plVar2[1];
          uVar3 = *(uint *)(plVar6 + 2);
          uVar7 = (ulong)uVar3;
          if (uVar14 != 0) break;
code_r0x01376604:
          plVar8 = (long *)Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(0x798,&UNK_027dc2d5/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_UnorderedMap.h"*/,0x1c);
          if (plVar8 == (long *)0x0) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
          }
          *(int *)(plVar8 + 2) = (int)plVar6[2];
          CMasterParameterSkillElement::CMasterParameterSkillElement(CMasterParameterSkillElement const&)(plVar8 + 3,plVar6 + 3);
          *plVar8 = 0;
          plVar8[1] = uVar7;
          if ((uVar14 == 0) || (*(float *)(plVar2 + 4) * (float)uVar14 < (float)(plVar2[3] + 1))) {
            if (uVar14 < 3) {
              uVar13 = 1;
            }
            else {
              uVar13 = (ulong)((uVar14 - 1 & uVar14) != 0);
            }
            uVar13 = uVar13 | uVar14 << 1;
            uVar14 = (ulong)((float)(plVar2[3] + 1) / *(float *)(plVar2 + 4));
            if (uVar14 <= uVar13) {
              uVar14 = uVar13;
            }
            std::__ndk1::__hash_table<std::__ndk1::__hash_value_type<unsigned int, CMasterParameterSkillElement>, std::__ndk1::__unordered_map_hasher<unsigned int, std::__ndk1::__hash_value_type<unsigned int, CMasterParameterSkillElement>, std::__ndk1::hash<unsigned int>, true>, std::__ndk1::__unordered_map_equal<unsigned int, std::__ndk1::__hash_value_type<unsigned int, CMasterParameterSkillElement>, std::__ndk1::equal_to<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__hash_value_type<unsigned int, CMasterParameterSkillElement>, Framework::CSTLUnorderedMapAllocatorInf> >::rehash(unsigned long)(plVar2,uVar14);
            uVar14 = plVar2[1];
            if ((uVar14 - 1 & uVar14) == 0) {
              uVar13 = uVar14 - 1 & uVar7;
            }
            else {
              uVar13 = 0;
              if (uVar14 != 0) {
                uVar13 = uVar7 / uVar14;
              }
              uVar13 = uVar7 - uVar13 * uVar14;
            }
          }
          plVar9 = *(long **)(*plVar2 + uVar13 * 8);
          if (plVar9 == (long *)0x0) {
            *plVar8 = plVar2[2];
            plVar2[2] = (long)plVar8;
            *(long **)(*plVar2 + uVar13 * 8) = plVar2 + 2;
            if (*plVar8 != 0) {
              uVar7 = *(ulong *)(*plVar8 + 8);
              if ((uVar14 - 1 & uVar14) == 0) {
                uVar7 = uVar7 & uVar14 - 1;
              }
              else {
                uVar10 = 0;
                if (uVar14 != 0) {
                  uVar10 = uVar7 / uVar14;
                }
                uVar7 = uVar7 - uVar10 * uVar14;
              }
              plVar9 = (long *)(*plVar2 + uVar7 * 8);
              goto code_r0x01376728;
            }
          }
          else {
            *plVar8 = *plVar9;
code_r0x01376728:
            *plVar9 = (long)plVar8;
          }
          plVar2[3] = plVar2[3] + 1;
          plVar6 = (long *)*plVar6;
          if (plVar6 == (long *)0x0) goto code_r0x01376748;
        }
        uVar10 = uVar14 - 1;
        if ((uVar10 & uVar14) == 0) {
          uVar13 = uVar10 & uVar7;
        }
        else {
          uVar13 = 0;
          if (uVar14 != 0) {
            uVar13 = uVar7 / uVar14;
          }
          uVar13 = uVar7 - uVar13 * uVar14;
        }
        plVar8 = *(long **)(*plVar2 + uVar13 * 8);
        if (plVar8 == (long *)0x0) goto code_r0x01376604;
        if ((uVar10 & uVar14) == 0) {
          do {
            plVar8 = (long *)*plVar8;
            if ((plVar8 == (long *)0x0) || ((plVar8[1] & uVar10) != uVar13)) goto code_r0x01376604;
          } while (*(uint *)(plVar8 + 2) != uVar3);
        }
        else {
          do {
            plVar8 = (long *)*plVar8;
            if (plVar8 == (long *)0x0) goto code_r0x01376604;
            uVar10 = 0;
            if (uVar14 != 0) {
              uVar10 = (ulong)plVar8[1] / uVar14;
            }
            if (plVar8[1] - uVar10 * uVar14 != uVar13) goto code_r0x01376604;
          } while (*(uint *)(plVar8 + 2) != uVar3);
        }
        plVar6 = (long *)*plVar6;
      } while (plVar6 != (long *)0x0);
    }
code_r0x01376748:
    *param_1 = (long)plVar2;
    param_1[1] = 0;
    lVar15 = lStack_a8;
    plVar2 = plStack_98;
    while (plVar2 != (long *)0x0) {
      lVar11 = *plVar2;
      lStack_a8 = lVar15;
      CMasterParameterSkillElement::~CMasterParameterSkillElement()(plVar2 + 3);
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar2);
      lVar15 = lStack_a8;
      plVar2 = (long *)lVar11;
    }
    lStack_a8 = 0;
    if (lVar15 != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)();
    }
  }
  if (piStack_70 != (int *)0x0) {
    do {
      iVar1 = *piStack_70;
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piStack_70,0x10);
      if (bVar5) {
        *piStack_70 = iVar1 + -1;
        cVar4 = ExclusiveMonitorsStatus();
      }
    } while (cVar4 != '\0');
    if (iVar1 + -1 != 0) goto code_r0x013767b4;
  }
  if (lStack_78 != 0) {
    operator delete[](void*)();
  }
  if (piStack_70 != (int *)0x0) {
    Aska::TSharedPointerCode::DeleteCounter(int*)();
  }
code_r0x013767b4:
  lStack_78 = 0;
  if (plVar12 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dc023/*"C:\BAS_Submission\Client\Project\Android\BASAndroid.NativeActivity\..\..\..\Source\Game/Parameter/Master/MasterParameterBaseSqlite.h"*/,0x52,&UNK_027dc0a8/*"m_pConnector is null."*/);
  }
  (**(code **)(*plVar12 + 0x18))(plVar12);
  return;
}

// ==== CMasterParameterBaseSqlite_Category<CMasterParameterSkillElement>::ParameterByQuery(char const*, Aska::Yayoi::QueryParam*, unsigned int) const
// vaddr 0x130c4f0 | ghidra 0x140c4f0 | size 380 | symbol _ZNK35CMasterParameterBaseSqlite_CategoryI28CMasterParameterSkillElementE16ParameterByQueryEPKcPN4Aska5Yayoi10QueryParamEj | lib libSOA-3.7.0.so | 2026-10-08
void _ZNK35CMasterParameterBaseSqlite_CategoryI28CMasterParameterSkillElementE16ParameterByQueryEPKcPN4Aska5Yayoi10QueryParamEj
               (long *param_1,long *param_2,undefined8 param_3,undefined8 param_4,undefined4 param_5
               )

{
  int iVar1;
  char cVar2;
  bool bVar3;
  undefined *puVar4;
  ulong uVar5;
  long lVar6;
  long *plVar7;
  long *plVar8;
  long lStack_50;
  int *piStack_48;
  long lStack_38;
  
  uVar5 = (**(code **)(*param_2 + 0x28))();
  if ((uVar5 & 1) == 0) {
    *param_1 = 0;
    param_1[1] = 0;
    return;
  }
  plVar8 = (long *)param_2[1];
  if (plVar8 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dc023/*"C:\BAS_Submission\Client\Project\Android\BASAndroid.NativeActivity\..\..\..\Source\Game/Parameter/Master/MasterParameterBaseSqlite.h"*/,0x4d,&UNK_027dc0a8/*"m_pConnector is null."*/);
  }
  (**(code **)(*plVar8 + 0x10))(plVar8,&UNK_027dc00a/*"sqlite/basmaster.sqlite3"*/);
  lStack_50 = 0;
  piStack_48 = (int *)0x0;
  lStack_38 = 0;
  (**(code **)(*plVar8 + 0x30))(plVar8,param_3,&lStack_50,&lStack_38,param_4,param_5);
  if (lStack_38 < 1) {
    *param_1 = 0;
    param_1[1] = 0;
  }
  else {
    lVar6 = operator new(unsigned long, std::nothrow_t const&)(0x780,PTR__ZSt7nothrow_02cb9a80);
    if (lVar6 != 0) {
      CMasterParameterSkillElement::CMasterParameterSkillElement()(lVar6);
    }
    void CMasterParameterBaseSqlite::DeserializeMsgPack<CMasterParameterSkillElement>(Aska::TSharedArray<signed char> const&, long const&, CMasterParameterSkillElement*, Framework::CSTLUnorderedMap<unsigned int, CMasterParameterSkillElement, std::__ndk1::hash<unsigned int>, std::__ndk1::equal_to<unsigned int> >*) const(param_2,&lStack_50,&lStack_38,lVar6,0);
    *param_1 = lVar6;
    plVar7 = (long *)operator new(unsigned long)(0x20);
    puVar4 = 
    PTR__ZTVNSt6__ndk120__shared_ptr_pointerIP28CMasterParameterSkillElementNS_14default_deleteIS1_EENS_9allocatorIS1_EEEE_02cb9f90
    ;
    plVar7[2] = 0;
    plVar7[3] = lVar6;
    param_1[1] = (long)plVar7;
    *plVar7 = (long)(puVar4 + 0x10);
    plVar7[1] = 0;
  }
  if (piStack_48 != (int *)0x0) {
    do {
      iVar1 = *piStack_48;
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piStack_48,0x10);
      if (bVar3) {
        *piStack_48 = iVar1 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    if (iVar1 + -1 != 0) goto code_r0x0140c640;
  }
  if (lStack_50 != 0) {
    operator delete[](void*)();
  }
  if (piStack_48 != (int *)0x0) {
    Aska::TSharedPointerCode::DeleteCounter(int*)();
  }
code_r0x0140c640:
  lStack_50 = 0;
  (**(code **)(*plVar8 + 0x18))(plVar8);
  return;
}

// ==== CMasterParameterBaseSqlite_Category<CMasterParameterSkillElement>::Initialize()
// vaddr 0x15b9f3c | ghidra 0x16b9f3c | size 64 | symbol _ZN35CMasterParameterBaseSqlite_CategoryI28CMasterParameterSkillElementE10InitializeEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN35CMasterParameterBaseSqlite_CategoryI28CMasterParameterSkillElementE10InitializeEv
               (long *param_1)

{
  long lVar1;
  
  lVar1 = (**(code **)(*param_1 + 0x30))();
  param_1[1] = lVar1;
  if (lVar1 != 0) {
    return;
  }
  (*(code *)PTR__ZN9Framework9gDoAssertEPKciS1_z_02ca3240)(&UNK_027dc023/*"C:\BAS_Submission\Client\Project\Android\BASAndroid.NativeActivity\..\..\..\Source\Game/Parameter/Master/MasterParameterBaseSqlite.h"*/,0x165,&UNK_02845d79/*"m_pSqlConnector is null."*/);
  return;
}

// ==== CMasterParameterBaseSqlite_Category<CMasterParameterSkillElement>::GetQueryIndex() const
// vaddr 0x15b9f7c | ghidra 0x16b9f7c | size 8 | symbol _ZNK35CMasterParameterBaseSqlite_CategoryI28CMasterParameterSkillElementE13GetQueryIndexEv | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZNK35CMasterParameterBaseSqlite_CategoryI28CMasterParameterSkillElementE13GetQueryIndexEv(void)

{
  return 2;
}

// ==== CMasterParameterBaseSqlite_Category<CMasterParameterSkillElement>::Deserialize(Aska::ASON::AValue::AMap const*)
// vaddr 0x15b9fcc | ghidra 0x16b9fcc | size 600 | symbol _ZN35CMasterParameterBaseSqlite_CategoryI28CMasterParameterSkillElementE11DeserializeEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN35CMasterParameterBaseSqlite_CategoryI28CMasterParameterSkillElementE11DeserializeEPKN4Aska4ASON6AValue4AMapE
          (long *param_1,long param_2)

{
  undefined *puVar1;
  ulong uVar2;
  uint uVar3;
  undefined4 uVar4;
  long lVar5;
  undefined8 *puVar6;
  undefined8 uVar7;
  ulong extraout_x1;
  uint uVar8;
  ulong uVar9;
  long lVar10;
  long *plVar11;
  ulong uVar12;
  ulong uVar13;
  long *plVar14;
  undefined1 auStack_70 [16];
  
  if (param_2 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dc023/*"C:\BAS_Submission\Client\Project\Android\BASAndroid.NativeActivity\..\..\..\Source\Game/Parameter/Master/MasterParameterBaseSqlite.h"*/,0x381,&UNK_027dc58a/*"apParser is null."*/);
  }
  lVar5 = (**(code **)(param_1[2] + 0x30))(param_1 + 2,param_2);
  uVar7 = 0;
  if (lVar5 != 0) {
    if (*(int *)(lVar5 + 0x10) != 0) {
      uVar8 = 0;
      puVar1 = PTR__ZTVNSt6__ndk120__shared_ptr_emplaceIN9Framework16CSTLUnorderedMapIj28CMasterParameterSkillElementNS_4hashIjEENS_8equal_toIjEEEE18ParameterAllocatorIS3_EEE_02cc1748
               + 0x10;
      do {
        Framework::CHash32::CHash32(char const*)(auStack_70,
                        *(undefined8 *)(*(long *)(lVar5 + 8) + (ulong)uVar8 * 0x40 + 0x10));
        uVar3 = Framework::CHash32::operator unsigned int() const(auStack_70);
        uVar12 = param_1[10];
        if (uVar12 == 0) {
code_r0x016ba10c:
          plVar11 = (long *)operator new(unsigned long)(0x40);
          plVar11[2] = 0;
          plVar11[1] = 0;
          *plVar11 = (long)puVar1;
          plVar14 = plVar11 + 3;
          plVar11[4] = 0;
          *plVar14 = 0;
          plVar11[6] = 0;
          plVar11[5] = 0;
          *(undefined4 *)(plVar11 + 7) = 0x3f800000;
          puVar6 = (undefined8 *)Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(0x28,&UNK_027dc2d5/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_UnorderedMap.h"*/,0x1c);
          if (puVar6 == (undefined8 *)0x0) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
          }
          uVar4 = Framework::CHash32::operator unsigned int() const(auStack_70);
          *(undefined4 *)(puVar6 + 2) = uVar4;
          puVar6[3] = plVar14;
          puVar6[4] = plVar11;
          std::__ndk1::__shared_weak_count::__add_shared()(plVar11);
          *puVar6 = 0;
          puVar6[1] = (ulong)*(uint *)(puVar6 + 2);
          std::__ndk1::__hash_table<std::__ndk1::__hash_value_type<unsigned int, std::__ndk1::shared_ptr<Framework::CSTLUnorderedMap<unsigned int, CMasterParameterSkillElement, std::__ndk1::hash<unsigned int>, std::__ndk1::equal_to<unsigned int> > > >, std::__ndk1::__unordered_map_hasher<unsigned int, std::__ndk1::__hash_value_type<unsigned int, std::__ndk1::shared_ptr<Framework::CSTLUnorderedMap<unsigned int, CMasterParameterSkillElement, std::__ndk1::hash<unsigned int>, std::__ndk1::equal_to<unsigned int> > > >, std::__ndk1::hash<unsigned int>, true>, std::__ndk1::__unordered_map_equal<unsigned int, std::__ndk1::__hash_value_type<unsigned int, std::__ndk1::shared_ptr<Framework::CSTLUnorderedMap<unsigned int, CMasterParameterSkillElement, std::__ndk1::hash<unsigned int>, std::__ndk1::equal_to<unsigned int> > > >, std::__ndk1::equal_to<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__hash_value_type<unsigned int, std::__ndk1::shared_ptr<Framework::CSTLUnorderedMap<unsigned int, CMasterParameterSkillElement, std::__ndk1::hash<unsigned int>, std::__ndk1::equal_to<unsigned int> > > >, Framework::CSTLUnorderedMapAllocatorInf> >::__node_insert_unique(std::__ndk1::__hash_node<std::__ndk1::__hash_value_type<unsigned int, std::__ndk1::shared_ptr<Framework::CSTLUnorderedMap<unsigned int, CMasterParameterSkillElement, std::__ndk1::hash<unsigned int>, std::__ndk1::equal_to<unsigned int> > > >, void*>*)(param_1 + 9,puVar6);
          if ((puVar6 != (undefined8 *)0x0) && ((extraout_x1 & 1) == 0)) {
            if (puVar6[4] != 0) {
              std::__ndk1::__shared_weak_count::__release_shared()();
            }
            Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puVar6);
          }
          std::__ndk1::__shared_weak_count::__release_shared()(plVar11);
        }
        else {
          uVar13 = uVar12 - 1;
          uVar9 = (ulong)uVar3;
          if ((uVar13 & uVar12) == 0) {
            uVar9 = uVar13 & uVar9;
          }
          else {
            uVar2 = 0;
            if (uVar12 != 0) {
              uVar2 = uVar9 / uVar12;
            }
            uVar9 = uVar9 - uVar2 * uVar12;
          }
          plVar11 = *(long **)(param_1[9] + uVar9 * 8);
          if (plVar11 == (long *)0x0) goto code_r0x016ba10c;
          if ((uVar13 & uVar12) == 0) {
            do {
              plVar11 = (long *)*plVar11;
              if ((plVar11 == (long *)0x0) || ((plVar11[1] & uVar13) != uVar9))
              goto code_r0x016ba10c;
            } while (*(uint *)(plVar11 + 2) != uVar3);
          }
          else {
            do {
              plVar11 = (long *)*plVar11;
              if (plVar11 == (long *)0x0) goto code_r0x016ba10c;
              uVar13 = 0;
              if (uVar12 != 0) {
                uVar13 = (ulong)plVar11[1] / uVar12;
              }
              if (plVar11[1] - uVar13 * uVar12 != uVar9) goto code_r0x016ba10c;
            } while (*(uint *)(plVar11 + 2) != uVar3);
          }
          if (plVar11 == (long *)0x0) goto code_r0x016ba10c;
          plVar14 = (long *)plVar11[3];
        }
        if (uVar8 < *(uint *)(lVar5 + 0x10)) {
          lVar10 = *(long *)(lVar5 + 8) + (ulong)uVar8 * 0x40 + 0x20;
        }
        else {
          lVar10 = 0;
        }
        (**(code **)(*param_1 + 0x48))(param_1,plVar14,lVar10 + 8);
        Framework::CHash32::~CHash32()(auStack_70);
        uVar8 = uVar8 + 1;
      } while (uVar8 < *(uint *)(lVar5 + 0x10));
    }
    uVar7 = 1;
  }
  return uVar7;
}

// ==== CMasterParameterBaseSqlite_Category<CMasterParameterSkillElement>::ReleaseParameter(char const*)
// vaddr 0x15ba224 | ghidra 0x16ba224 | size 572 | symbol _ZN35CMasterParameterBaseSqlite_CategoryI28CMasterParameterSkillElementE16ReleaseParameterEPKc | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN35CMasterParameterBaseSqlite_CategoryI28CMasterParameterSkillElementE16ReleaseParameterEPKc
          (long param_1)

{
  ulong uVar1;
  uint uVar2;
  ulong uVar3;
  long lVar4;
  ulong uVar5;
  ulong uVar6;
  ulong uVar7;
  long *plVar8;
  ulong uVar9;
  long *plVar10;
  long *plVar11;
  long lVar12;
  undefined1 auStack_40 [16];
  
  Framework::CHash32::CHash32(char const*)(auStack_40);
  uVar2 = Framework::CHash32::operator unsigned int() const(auStack_40);
  uVar5 = *(ulong *)(param_1 + 0x50);
  if (uVar5 == 0) {
code_r0x016ba354:
    Framework::CHash32::~CHash32()(auStack_40);
    return 1;
  }
  uVar6 = uVar5 - 1;
  uVar3 = (ulong)uVar2;
  if ((uVar6 & uVar5) == 0) {
    uVar3 = uVar6 & uVar3;
  }
  else {
    uVar7 = 0;
    if (uVar5 != 0) {
      uVar7 = uVar3 / uVar5;
    }
    uVar3 = uVar3 - uVar7 * uVar5;
  }
  plVar10 = *(long **)(*(long *)(param_1 + 0x48) + uVar3 * 8);
  if (plVar10 == (long *)0x0) goto code_r0x016ba354;
  if ((uVar6 & uVar5) == 0) {
    do {
      plVar10 = (long *)*plVar10;
      if ((plVar10 == (long *)0x0) || ((plVar10[1] & uVar6) != uVar3)) goto code_r0x016ba354;
    } while (*(uint *)(plVar10 + 2) != uVar2);
  }
  else {
    do {
      plVar10 = (long *)*plVar10;
      if (plVar10 == (long *)0x0) goto code_r0x016ba354;
      uVar6 = 0;
      if (uVar5 != 0) {
        uVar6 = (ulong)plVar10[1] / uVar5;
      }
      if (plVar10[1] - uVar6 * uVar5 != uVar3) goto code_r0x016ba354;
    } while (*(uint *)(plVar10 + 2) != uVar2);
  }
  Framework::CHash32::~CHash32()(auStack_40);
  if (plVar10 == (long *)0x0) {
    return 1;
  }
  plVar11 = (long *)plVar10[3];
  if (plVar11[3] != 0) {
    plVar8 = (long *)plVar11[2];
    while (plVar8 != (long *)0x0) {
      lVar12 = *plVar8;
      CMasterParameterSkillElement::~CMasterParameterSkillElement()(plVar8 + 3);
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar8);
      plVar8 = (long *)lVar12;
    }
    lVar12 = plVar11[1];
    plVar11[2] = 0;
    if (lVar12 != 0) {
      lVar4 = 0;
      do {
        *(undefined8 *)(*plVar11 + lVar4 * 8) = 0;
        lVar4 = lVar4 + 1;
      } while (lVar12 != lVar4);
    }
    plVar11[3] = 0;
  }
  uVar3 = *(ulong *)(param_1 + 0x50);
  uVar5 = plVar10[1];
  uVar6 = uVar3 - 1;
  uVar7 = uVar6 & uVar3;
  if (uVar7 == 0) {
    uVar5 = uVar6 & uVar5;
  }
  else {
    uVar9 = 0;
    if (uVar3 != 0) {
      uVar9 = uVar5 / uVar3;
    }
    uVar5 = uVar5 - uVar9 * uVar3;
  }
  plVar11 = *(long **)(*(long *)(param_1 + 0x48) + uVar5 * 8);
  do {
    plVar8 = plVar11;
    plVar11 = (long *)*plVar8;
  } while ((long *)*plVar8 != plVar10);
  if (plVar8 != (long *)(param_1 + 0x58)) {
    uVar9 = plVar8[1];
    if (uVar7 == 0) {
      uVar9 = uVar9 & uVar6;
    }
    else {
      uVar1 = 0;
      if (uVar3 != 0) {
        uVar1 = uVar9 / uVar3;
      }
      uVar9 = uVar9 - uVar1 * uVar3;
    }
    if (uVar9 == uVar5) goto code_r0x016ba3f8;
  }
  if (*plVar10 != 0) {
    uVar9 = *(ulong *)(*plVar10 + 8);
    if (uVar7 == 0) {
      uVar9 = uVar9 & uVar6;
    }
    else {
      uVar1 = 0;
      if (uVar3 != 0) {
        uVar1 = uVar9 / uVar3;
      }
      uVar9 = uVar9 - uVar1 * uVar3;
    }
    if (uVar9 == uVar5) goto code_r0x016ba3f8;
  }
  *(undefined8 *)(*(long *)(param_1 + 0x48) + uVar5 * 8) = 0;
code_r0x016ba3f8:
  if (*plVar10 != 0) {
    uVar9 = *(ulong *)(*plVar10 + 8);
    if (uVar7 == 0) {
      uVar9 = uVar9 & uVar6;
    }
    else {
      uVar6 = 0;
      if (uVar3 != 0) {
        uVar6 = uVar9 / uVar3;
      }
      uVar9 = uVar9 - uVar6 * uVar3;
    }
    if (uVar9 != uVar5) {
      *(long **)(*(long *)(param_1 + 0x48) + uVar9 * 8) = plVar8;
    }
  }
  *plVar8 = *plVar10;
  *plVar10 = 0;
  *(long *)(param_1 + 0x60) = *(long *)(param_1 + 0x60) + -1;
  if (plVar10[4] != 0) {
    std::__ndk1::__shared_weak_count::__release_shared()();
  }
  Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar10);
  return 1;
}

// ==== CMasterParameterBaseSqlite_Category<CMasterParameterSkillElement>::DeserializeParameter(Framework::CSTLUnorderedMap<unsigned int, CMasterParameterSkillElement, std::__ndk1::hash<unsigned int>, std::__ndk1::equal_to<unsigned int> >*, Aska::ASON::AValue::AArray const*)
// vaddr 0x15ba460 | ghidra 0x16ba460 | size 888 | symbol _ZN35CMasterParameterBaseSqlite_CategoryI28CMasterParameterSkillElementE20DeserializeParameterEPN9Framework16CSTLUnorderedMapIjS0_NSt6__ndk14hashIjEENS4_8equal_toIjEEEEPKN4Aska4ASON6AValue6AArrayE | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN35CMasterParameterBaseSqlite_CategoryI28CMasterParameterSkillElementE20DeserializeParameterEPN9Framework16CSTLUnorderedMapIjS0_NSt6__ndk14hashIjEENS4_8equal_toIjEEEEPKN4Aska4ASON6AValue6AArrayE
          (long *param_1,long *param_2,long *param_3)

{
  uint uVar1;
  long lVar2;
  undefined8 uVar3;
  ulong uVar4;
  ulong uVar5;
  ulong uVar6;
  long *plVar7;
  long *plVar8;
  ulong uVar9;
  ulong uVar10;
  ulong unaff_x25;
  int iVar11;
  undefined1 auStack_7e0 [1920];
  
  if (param_3 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dc023/*"C:\BAS_Submission\Client\Project\Android\BASAndroid.NativeActivity\..\..\..\Source\Game/Parameter/Master/MasterParameterBaseSqlite.h"*/,0x3ac,&UNK_02845e17/*"apArray is null."*/);
    iVar11 = iRam0000000000000008;
  }
  else {
    iVar11 = (int)param_3[1];
  }
  if (iVar11 != 0) {
    uVar5 = 0;
    do {
      lVar2 = *param_3 + uVar5 * 0x20;
      if (lVar2 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dc023/*"C:\BAS_Submission\Client\Project\Android\BASAndroid.NativeActivity\..\..\..\Source\Game/Parameter/Master/MasterParameterBaseSqlite.h"*/,0x3af,&UNK_0285e8d7/*"pValue is null."*/);
      }
      lVar2 = lVar2 + 8;
      uVar3 = (**(code **)(*param_1 + 0x18))(param_1);
      uVar4 = std::__ndk1::pair<unsigned int, bool> CParameterParser::GetValue<unsigned int>(Aska::ASON::AValue::AMap const*, char const*)(lVar2,uVar3);
      if ((uVar4 & 0xff00000000) != 0) {
        uVar9 = param_2[1];
        uVar10 = uVar4 & 0xffffffff;
        iVar11 = (int)uVar4;
        if (uVar9 == 0) {
code_r0x016ba5b4:
          CMasterParameterSkillElement::CMasterParameterSkillElement()(auStack_7e0);
          uVar4 = param_2[1];
          if (uVar4 == 0) {
code_r0x016ba644:
            plVar8 = (long *)Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(0x798,&UNK_027dc2d5/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_UnorderedMap.h"*/,0x1c);
            if (plVar8 == (long *)0x0) {
              Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
            }
            *(int *)(plVar8 + 2) = iVar11;
            CMasterParameterSkillElement::CMasterParameterSkillElement(CMasterParameterSkillElement const&)(plVar8 + 3,auStack_7e0);
            *plVar8 = 0;
            plVar8[1] = uVar10;
            if ((uVar4 == 0) || (*(float *)(param_2 + 4) * (float)uVar4 < (float)(param_2[3] + 1)))
            {
              if (uVar4 < 3) {
                uVar9 = 1;
              }
              else {
                uVar9 = (ulong)((uVar4 - 1 & uVar4) != 0);
              }
              uVar9 = uVar9 | uVar4 << 1;
              uVar4 = (ulong)((float)(param_2[3] + 1) / *(float *)(param_2 + 4));
              if (uVar4 <= uVar9) {
                uVar4 = uVar9;
              }
              std::__ndk1::__hash_table<std::__ndk1::__hash_value_type<unsigned int, CMasterParameterSkillElement>, std::__ndk1::__unordered_map_hasher<unsigned int, std::__ndk1::__hash_value_type<unsigned int, CMasterParameterSkillElement>, std::__ndk1::hash<unsigned int>, true>, std::__ndk1::__unordered_map_equal<unsigned int, std::__ndk1::__hash_value_type<unsigned int, CMasterParameterSkillElement>, std::__ndk1::equal_to<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__hash_value_type<unsigned int, CMasterParameterSkillElement>, Framework::CSTLUnorderedMapAllocatorInf> >::rehash(unsigned long)(param_2,uVar4);
              uVar4 = param_2[1];
              if ((uVar4 - 1 & uVar4) == 0) {
                unaff_x25 = uVar4 - 1 & uVar10;
              }
              else {
                uVar9 = 0;
                if (uVar4 != 0) {
                  uVar9 = uVar10 / uVar4;
                }
                unaff_x25 = uVar10 - uVar9 * uVar4;
              }
            }
            plVar7 = *(long **)(*param_2 + unaff_x25 * 8);
            if (plVar7 == (long *)0x0) {
              *plVar8 = param_2[2];
              param_2[2] = (long)plVar8;
              *(long **)(*param_2 + unaff_x25 * 8) = param_2 + 2;
              if (*plVar8 != 0) {
                uVar9 = *(ulong *)(*plVar8 + 8);
                if ((uVar4 - 1 & uVar4) == 0) {
                  uVar9 = uVar9 & uVar4 - 1;
                }
                else {
                  uVar10 = 0;
                  if (uVar4 != 0) {
                    uVar10 = uVar9 / uVar4;
                  }
                  uVar9 = uVar9 - uVar10 * uVar4;
                }
                plVar7 = (long *)(*param_2 + uVar9 * 8);
                goto code_r0x016ba768;
              }
            }
            else {
              *plVar8 = *plVar7;
code_r0x016ba768:
              *plVar7 = (long)plVar8;
            }
            param_2[3] = param_2[3] + 1;
          }
          else {
            uVar9 = uVar4 - 1;
            if ((uVar9 & uVar4) == 0) {
              unaff_x25 = uVar9 & uVar10;
            }
            else {
              uVar6 = 0;
              if (uVar4 != 0) {
                uVar6 = uVar10 / uVar4;
              }
              unaff_x25 = uVar10 - uVar6 * uVar4;
            }
            plVar8 = *(long **)(*param_2 + unaff_x25 * 8);
            if (plVar8 == (long *)0x0) goto code_r0x016ba644;
            if ((uVar9 & uVar4) == 0) {
              do {
                plVar8 = (long *)*plVar8;
                if ((plVar8 == (long *)0x0) || ((plVar8[1] & uVar9) != unaff_x25))
                goto code_r0x016ba644;
              } while ((int)plVar8[2] != iVar11);
            }
            else {
              do {
                plVar8 = (long *)*plVar8;
                if (plVar8 == (long *)0x0) goto code_r0x016ba644;
                uVar9 = 0;
                if (uVar4 != 0) {
                  uVar9 = (ulong)plVar8[1] / uVar4;
                }
                if (plVar8[1] - uVar9 * uVar4 != unaff_x25) goto code_r0x016ba644;
              } while ((int)plVar8[2] != iVar11);
            }
          }
          CMasterParameterSkillElement::~CMasterParameterSkillElement()(auStack_7e0);
          plVar8 = plVar8 + 3;
          (**(code **)*plVar8)(plVar8);
        }
        else {
          uVar4 = uVar9 - 1;
          if ((uVar4 & uVar9) == 0) {
            uVar6 = uVar4 & uVar10;
          }
          else {
            uVar6 = 0;
            if (uVar9 != 0) {
              uVar6 = uVar10 / uVar9;
            }
            uVar6 = uVar10 - uVar6 * uVar9;
          }
          plVar8 = *(long **)(*param_2 + uVar6 * 8);
          if (plVar8 == (long *)0x0) goto code_r0x016ba5b4;
          if ((uVar4 & uVar9) == 0) {
            do {
              plVar8 = (long *)*plVar8;
              if ((plVar8 == (long *)0x0) || ((plVar8[1] & uVar4) != uVar6)) goto code_r0x016ba5b4;
            } while ((int)plVar8[2] != iVar11);
          }
          else {
            do {
              plVar8 = (long *)*plVar8;
              if (plVar8 == (long *)0x0) goto code_r0x016ba5b4;
              uVar4 = 0;
              if (uVar9 != 0) {
                uVar4 = (ulong)plVar8[1] / uVar9;
              }
              if (plVar8[1] - uVar4 * uVar9 != uVar6) goto code_r0x016ba5b4;
            } while (*(int *)(plVar8 + 2) != iVar11);
          }
          if (plVar8 == (long *)0x0) goto code_r0x016ba5b4;
          plVar8 = plVar8 + 3;
        }
        (**(code **)(*plVar8 + 8))(plVar8,lVar2);
      }
      uVar1 = (int)uVar5 + 1;
      uVar5 = (ulong)uVar1;
    } while (uVar1 < *(uint *)(param_3 + 1));
  }
  return 1;
}

// ==== CMasterParameterBaseSqlite_Category<CMasterParameterSkillElement>::pGroupKeyName() const
// vaddr 0x15ba7d8 | ghidra 0x16ba7d8 | size 12 | symbol _ZNK35CMasterParameterBaseSqlite_CategoryI28CMasterParameterSkillElementE13pGroupKeyNameEv | lib libSOA-3.7.0.so | 2026-10-08
undefined *
_ZNK35CMasterParameterBaseSqlite_CategoryI28CMasterParameterSkillElementE13pGroupKeyNameEv(void)

{
  return &UNK_02847bef/*"group_id"*/;
}

// ==== non-virtual thunk to CMasterParameterBaseSqlite_Category<CMasterParameterSkillElement>::Initialize()
// vaddr 0x15ba81c | ghidra 0x16ba81c | size 68 | symbol _ZThn16_N35CMasterParameterBaseSqlite_CategoryI28CMasterParameterSkillElementE10InitializeEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZThn16_N35CMasterParameterBaseSqlite_CategoryI28CMasterParameterSkillElementE10InitializeEv
               (long param_1)

{
  long lVar1;
  
  lVar1 = (**(code **)(*(long *)(param_1 + -0x10) + 0x30))((long *)(param_1 + -0x10));
  *(long *)(param_1 + -8) = lVar1;
  if (lVar1 != 0) {
    return;
  }
  (*(code *)PTR__ZN9Framework9gDoAssertEPKciS1_z_02ca3240)(&UNK_027dc023/*"C:\BAS_Submission\Client\Project\Android\BASAndroid.NativeActivity\..\..\..\Source\Game/Parameter/Master/MasterParameterBaseSqlite.h"*/,0x165,&UNK_02845d79/*"m_pSqlConnector is null."*/);
  return;
}

// ==== non-virtual thunk to CMasterParameterBaseSqlite_Category<CMasterParameterSkillElement>::Deserialize(Aska::ASON::AValue::AMap const*)
// vaddr 0x15ba86c | ghidra 0x16ba86c | size 8 | symbol _ZThn16_N35CMasterParameterBaseSqlite_CategoryI28CMasterParameterSkillElementE11DeserializeEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
void _ZThn16_N35CMasterParameterBaseSqlite_CategoryI28CMasterParameterSkillElementE11DeserializeEPKN4Aska4ASON6AValue4AMapE
               (long param_1)

{
  (*(code *)
    PTR__ZN35CMasterParameterBaseSqlite_CategoryI28CMasterParameterSkillElementE11DeserializeEPKN4Aska4ASON6AValue4AMapE_02ca6108
  )(param_1 + -0x10);
  return;
}

// ==== non-virtual thunk to CMasterParameterBaseSqlite_Category<CMasterParameterSkillElement>::ReleaseParameter(char const*)
// vaddr 0x15ba874 | ghidra 0x16ba874 | size 8 | symbol _ZThn16_N35CMasterParameterBaseSqlite_CategoryI28CMasterParameterSkillElementE16ReleaseParameterEPKc | lib libSOA-3.7.0.so | 2026-10-08
void _ZThn16_N35CMasterParameterBaseSqlite_CategoryI28CMasterParameterSkillElementE16ReleaseParameterEPKc
               (long param_1)

{
  (*(code *)
    PTR__ZN35CMasterParameterBaseSqlite_CategoryI28CMasterParameterSkillElementE16ReleaseParameterEPKc_02c9c2f0
  )(param_1 + -0x10);
  return;
}

// ==== CMasterParameterBaseSqlite_Category<CMasterParameterSkillElement>::~CMasterParameterBaseSqlite_Category()
// vaddr 0x15ba87c | ghidra 0x16ba87c | size 200 | symbol _ZN35CMasterParameterBaseSqlite_CategoryI28CMasterParameterSkillElementED2Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN35CMasterParameterBaseSqlite_CategoryI28CMasterParameterSkillElementED2Ev(long *param_1)

{
  undefined *puVar1;
  long *plVar2;
  long lVar3;
  
  puVar1 = PTR__ZTV35CMasterParameterBaseSqlite_CategoryI28CMasterParameterSkillElementE_02cbb9a0 +
           0x80;
  *param_1 = (long)(
                   PTR__ZTV35CMasterParameterBaseSqlite_CategoryI28CMasterParameterSkillElementE_02cbb9a0
                   + 0x10);
  param_1[2] = (long)puVar1;
  plVar2 = (long *)param_1[0xb];
  while (plVar2 != (long *)0x0) {
    lVar3 = *plVar2;
    if (plVar2[4] != 0) {
      std::__ndk1::__shared_weak_count::__release_shared()();
    }
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar2);
    plVar2 = (long *)lVar3;
  }
  lVar3 = param_1[9];
  param_1[9] = 0;
  if (lVar3 != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)();
  }
  plVar2 = (long *)param_1[5];
  while (plVar2 != (long *)0x0) {
    lVar3 = *plVar2;
    if (plVar2[4] != 0) {
      std::__ndk1::__shared_weak_count::__release_shared()();
    }
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar2);
    plVar2 = (long *)lVar3;
  }
  lVar3 = param_1[3];
  param_1[3] = 0;
  if (lVar3 != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)();
  }
  *param_1 = (long)(PTR__ZTV26CMasterParameterBaseSqlite_02cc48f0 + 0x10);
  if ((long *)param_1[1] != (long *)0x0) {
    (**(code **)(*(long *)param_1[1] + 8))();
    param_1[1] = 0;
  }
  return;
}

// ==== CMasterParameterBaseSqlite_Category<CMasterParameterSkillElement>::~CMasterParameterBaseSqlite_Category()
// vaddr 0x15ba944 | ghidra 0x16ba944 | size 4 | symbol _ZN35CMasterParameterBaseSqlite_CategoryI28CMasterParameterSkillElementED0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN35CMasterParameterBaseSqlite_CategoryI28CMasterParameterSkillElementED0Ev(void)

{
  code *pcVar1;
  
                    /* WARNING: Does not return */
  pcVar1 = (code *)SoftwareBreakpoint(1,0x16ba948);
  (*pcVar1)();
}

// ==== CMasterParameterBaseSqlite_Category<CMasterParameterSkillElement>::IsAddCategoryId() const
// vaddr 0x15ba948 | ghidra 0x16ba948 | size 8 | symbol _ZNK35CMasterParameterBaseSqlite_CategoryI28CMasterParameterSkillElementE15IsAddCategoryIdEv | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZNK35CMasterParameterBaseSqlite_CategoryI28CMasterParameterSkillElementE15IsAddCategoryIdEv(void)

{
  return 1;
}

// ==== non-virtual thunk to CMasterParameterBaseSqlite_Category<CMasterParameterSkillElement>::~CMasterParameterBaseSqlite_Category()
// vaddr 0x15ba950 | ghidra 0x16ba950 | size 8 | symbol _ZThn16_N35CMasterParameterBaseSqlite_CategoryI28CMasterParameterSkillElementED1Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZThn16_N35CMasterParameterBaseSqlite_CategoryI28CMasterParameterSkillElementED1Ev
               (long param_1)

{
  (*(code *)
    PTR__ZN35CMasterParameterBaseSqlite_CategoryI28CMasterParameterSkillElementED2Ev_02c984b8)
            (param_1 + -0x10);
  return;
}

// ==== non-virtual thunk to CMasterParameterBaseSqlite_Category<CMasterParameterSkillElement>::~CMasterParameterBaseSqlite_Category()
// vaddr 0x15ba958 | ghidra 0x16ba958 | size 4 | symbol _ZThn16_N35CMasterParameterBaseSqlite_CategoryI28CMasterParameterSkillElementED0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZThn16_N35CMasterParameterBaseSqlite_CategoryI28CMasterParameterSkillElementED0Ev(void)

{
  code *pcVar1;
  
                    /* WARNING: Does not return */
  pcVar1 = (code *)SoftwareBreakpoint(1,0x16ba95c);
  (*pcVar1)();
}


// FAILED to create function at 02ae8ed0 CMasterParameterBaseSqlite_Category<CMasterParameterSkillElement>::typeinfo
// FAILED to create function at 02ae8f28 CMasterParameterBaseSqlite_Category<CMasterParameterSkillElement>::vtable
