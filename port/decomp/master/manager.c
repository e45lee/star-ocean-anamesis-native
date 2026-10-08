// port/decomp/master/manager.c: Ghidra decompiles for the master subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-08 13:03 UTC: tools/decomp.sh '--into' 'master/manager' 'CMasterManager::' 'CMasterCache::'

// ==== CMasterCache::tLevelMaxCache::Get(unsigned int)
// vaddr 0x1591b04 | ghidra 0x1691b04 | size 920 | symbol _ZN12CMasterCache14tLevelMaxCache3GetEj | lib libSOA-3.7.0.so | 2026-10-08
int _ZN12CMasterCache14tLevelMaxCache3GetEj(long param_1,uint param_2)

{
  long *plVar1;
  ulong uVar2;
  uint *puVar3;
  undefined *puVar4;
  long *plVar5;
  int iVar6;
  long *plVar7;
  long lVar8;
  undefined8 uVar9;
  long *plVar10;
  long *plVar11;
  int iVar12;
  ulong uVar13;
  ulong uVar14;
  ulong uStack_1c0;
  ulong uStack_1b8;
  ulong uStack_1b0;
  byte bStack_1a0;
  undefined7 uStack_19f;
  ulong uStack_198;
  ulong uStack_190;
  uint uStack_184;
  undefined *puStack_180;
  undefined8 uStack_178;
  uint **ppuStack_170;
  undefined8 uStack_168;
  undefined4 uStack_160;
  undefined1 uStack_15c;
  uint *puStack_158;
  undefined8 uStack_150;
  long *plStack_148;
  undefined8 uStack_140;
  undefined4 uStack_138;
  byte bStack_58;
  undefined7 uStack_57;
  long lStack_50;
  ulong uStack_48;
  
  puVar4 = PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
  plVar10 = (long *)(param_1 + 8);
  plVar5 = (long *)*plVar10;
  plVar7 = plVar10;
  if ((long *)*plVar10 != (long *)0x0) {
    do {
      while (plVar11 = plVar5, param_2 <= *(uint *)((long)plVar11 + 0x1c)) {
        plVar5 = (long *)*plVar11;
        plVar7 = plVar11;
        if ((long *)*plVar11 == (long *)0x0) goto code_r0x01691b64;
      }
      plVar1 = plVar11 + 1;
      plVar11 = plVar7;
      plVar5 = (long *)*plVar1;
    } while ((long *)*plVar1 != (long *)0x0);
code_r0x01691b64:
    if (((plVar11 != plVar10) && (*(uint *)((long)plVar11 + 0x1c) <= param_2)) &&
       (plVar11 != plVar10)) {
      return (int)plVar11[4];
    }
  }
  uStack_184 = param_2;
  if (param_2 != 7) {
    lVar8 = *(long *)PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
    if (lVar8 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
      lVar8 = *(long *)puVar4;
    }
    uVar9 = CParameterManager::pMasterParameterRoleLevelMax() const(lVar8);
    snprintf(&puStack_158,0x100,&UNK_027e6d32/*"%u"*/,param_2);
    puStack_180 = &UNK_027ffc7f/*"rarity"*/;
    uStack_178 = 6;
    ppuStack_170 = &puStack_158;
    uStack_168 = strlen(&puStack_158);
    uStack_160 = 0;
    uStack_15c = 0;
    CMasterParameterBaseSqlite_Simple<CMasterParameterRoleLevelMaxElement>::ParameterByQuery(char const*, Aska::Yayoi::QueryParam*, unsigned int) const(&bStack_58,uVar9,&UNK_02844e4b/*"SELECT * FROM master_role_level_max WHERE rarity=?"*/,&puStack_180,1);
    if (CONCAT71(uStack_57,bStack_58) == 0) {
      iVar12 = 0;
    }
    else {
      iVar12 = *(int *)(CONCAT71(uStack_57,bStack_58) + 0xd8);
    }
    if (lStack_50 != 0) {
      std::__ndk1::__shared_weak_count::__release_shared()();
    }
    goto code_r0x01691e58;
  }
  uStack_140 = 0;
  plStack_148 = (long *)0x0;
  uStack_150 = 0;
  puStack_158 = (uint *)0x0;
  uStack_138 = 0x3f800000;
  CTimeUtility::NowTime()();
  CTimeUtility::Date(long)(&puStack_180);
  CTimeUtility::tDate::DateAndTimeStringFromatSqlite() const(&bStack_1a0,&puStack_180);
  puVar4 = PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
  lVar8 = *(long *)PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
  if (lVar8 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar8 = *(long *)puVar4;
  }
  uVar9 = CParameterManager::pMasterUniverseBoard() const(lVar8);
  uVar2 = uStack_190;
  uStack_1c0 = 0;
  uStack_1b8 = 0;
  uStack_1b0 = 0;
  if ((bStack_1a0 & 1) == 0) {
    uStack_1c0 = CONCAT71(uStack_19f,bStack_1a0);
    uStack_1b0 = uStack_190;
    uStack_1b8 = uStack_198;
  }
  else {
    if (uStack_198 < 0x17) {
      uVar13 = (ulong)&uStack_1c0 | 1;
      uStack_1c0 = (uStack_198 & 0x7f) << 1;
      if (uStack_198 != 0) goto code_r0x01691d5c;
    }
    else {
      uVar14 = uStack_198 + 0x10 & 0xfffffffffffffff0;
      if (uVar14 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
      }
      uVar13 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar14,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
      if (uVar13 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
      }
      uStack_1c0 = uVar14 | 1;
      uStack_1b8 = uStack_198;
      uStack_1b0 = uVar13;
code_r0x01691d5c:
      memcpy(uVar13,uVar2,uStack_198);
    }
    *(undefined1 *)(uVar13 + uStack_198) = 0;
  }
  uVar2 = (ulong)((byte)uStack_1c0 >> 1);
  if ((uStack_1c0 & 1) != 0) {
    uVar2 = uStack_1b8;
  }
  if (uVar2 != 0) {
    uVar2 = (ulong)&uStack_1c0 | 1;
    if ((uStack_1c0 & 1) != 0) {
      uVar2 = uStack_1b0;
    }
    Framework::CSTLStringUtility_Base<string >::Format(char const*, ...)(&bStack_58,&UNK_02844d4a/*"SELECT * FROM master_universe_board WHERE (`opened_at` IS NULL OR (`opened_at` IS NOT NULL AND '%s' >= `opened_at`)) AND ( `closed_at` IS NULL OR (`closed_at` IS NOT NULL AND '%s' <= `closed_at`))"*/,uVar2,uVar2);
    uVar2 = (ulong)&bStack_58 | 1;
    if ((bStack_58 & 1) != 0) {
      uVar2 = uStack_48;
    }
    CMasterParameterBaseSqlite_Simple<CMasterUniverseBoardElement>::ParameterByQuery(char const*, Framework::CSTLUnorderedMap<unsigned int, CMasterUniverseBoardElement, std::__ndk1::hash<unsigned int>, std::__ndk1::equal_to<unsigned int> >&, Aska::Yayoi::QueryParam*, unsigned int) const(uVar9,uVar2,&puStack_158,0,0);
    if ((bStack_58 & 1) != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_48);
    }
  }
  if (((byte)uStack_1c0 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_1b0);
  }
  iVar6 = _ZN12CMasterCache14tLevelMaxCache3GetEj(param_1,6);
  iVar12 = (int)uStack_140;
  puVar3 = puStack_158;
  plVar5 = plStack_148;
  if ((bStack_1a0 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_190);
    puVar3 = puStack_158;
    plVar5 = plStack_148;
  }
  while (plVar5 != (long *)0x0) {
    lVar8 = *plVar5;
    puStack_158 = puVar3;
    CMasterUniverseBoardElement::~CMasterUniverseBoardElement()(plVar5 + 3);
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar5);
    puVar3 = puStack_158;
    plVar5 = (long *)lVar8;
  }
  iVar12 = iVar12 + iVar6;
  puStack_158 = (uint *)0x0;
  if (puVar3 != (uint *)0x0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)();
  }
code_r0x01691e58:
  puStack_158 = &uStack_184;
  lVar8 = std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, unsigned int>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, unsigned int>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, unsigned int>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, unsigned int>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, unsigned int>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, std::__ndk1::piecewise_construct_t const&, std::__ndk1::tuple<unsigned int const&>, std::__ndk1::tuple<> >(unsigned int const&, std::__ndk1::piecewise_construct_t const&, std::__ndk1::tuple<unsigned int const&>&&, std::__ndk1::tuple<>&&)(param_1,&uStack_184,&UNK_02845184,&puStack_158,&puStack_180);
  *(int *)(lVar8 + 0x20) = iVar12;
  return iVar12;
}

// ==== CMasterCache::tLimitBreakMaxCache::Get(unsigned int)
// vaddr 0x1591e9c | ghidra 0x1691e9c | size 192 | symbol _ZN12CMasterCache19tLimitBreakMaxCache3GetEj | lib libSOA-3.7.0.so | 2026-10-08
undefined4 _ZN12CMasterCache19tLimitBreakMaxCache3GetEj(long param_1,uint param_2)

{
  long *plVar1;
  long *plVar2;
  undefined4 uVar3;
  long *plVar4;
  long lVar5;
  long *plVar6;
  long *plVar7;
  uint uStack_2c;
  undefined1 auStack_28 [8];
  uint *puStack_18;
  
  plVar6 = (long *)(param_1 + 8);
  plVar2 = (long *)*plVar6;
  plVar4 = plVar6;
  if ((long *)*plVar6 != (long *)0x0) {
    do {
      while (plVar7 = plVar2, *(uint *)((long)plVar7 + 0x1c) < param_2) {
        plVar1 = plVar7 + 1;
        plVar7 = plVar4;
        plVar2 = (long *)*plVar1;
        if ((long *)*plVar1 == (long *)0x0) goto code_r0x01691ef0;
      }
      plVar2 = (long *)*plVar7;
      plVar4 = plVar7;
    } while ((long *)*plVar7 != (long *)0x0);
code_r0x01691ef0:
    if (((plVar7 != plVar6) && (*(uint *)((long)plVar7 + 0x1c) <= param_2)) && (plVar7 != plVar6)) {
      return (int)plVar7[4];
    }
  }
  uStack_2c = param_2;
  uVar3 = CParameterUtility::CalcMasterRole2LimitBreakMax(unsigned int)(param_2);
  puStack_18 = &uStack_2c;
  lVar5 = std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, unsigned int>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, unsigned int>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, unsigned int>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, unsigned int>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, unsigned int>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, std::__ndk1::piecewise_construct_t const&, std::__ndk1::tuple<unsigned int const&>, std::__ndk1::tuple<> >(unsigned int const&, std::__ndk1::piecewise_construct_t const&, std::__ndk1::tuple<unsigned int const&>&&, std::__ndk1::tuple<>&&)(param_1,&uStack_2c,&UNK_02845184,&puStack_18,auStack_28);
  *(undefined4 *)(lVar5 + 0x20) = uVar3;
  return uVar3;
}

// ==== CMasterCache::tWeaponLevelMaxCache2::Get(unsigned int, unsigned int)
// vaddr 0x1591f5c | ghidra 0x1691f5c | size 196 | symbol _ZN12CMasterCache21tWeaponLevelMaxCache23GetEjj | lib libSOA-3.7.0.so | 2026-10-08
undefined4
_ZN12CMasterCache21tWeaponLevelMaxCache23GetEjj(long param_1,undefined4 param_2,uint param_3)

{
  long *plVar1;
  long *plVar2;
  undefined4 uVar3;
  long *plVar4;
  long lVar5;
  long *plVar6;
  long *plVar7;
  uint uStack_2c;
  undefined1 auStack_28 [8];
  uint *puStack_18;
  
  plVar6 = (long *)(param_1 + 8);
  plVar2 = (long *)*plVar6;
  plVar4 = plVar6;
  if ((long *)*plVar6 != (long *)0x0) {
    do {
      while (plVar7 = plVar2, *(uint *)((long)plVar7 + 0x1c) < param_3) {
        plVar1 = plVar7 + 1;
        plVar7 = plVar4;
        plVar2 = (long *)*plVar1;
        if ((long *)*plVar1 == (long *)0x0) goto code_r0x01691fb0;
      }
      plVar2 = (long *)*plVar7;
      plVar4 = plVar7;
    } while ((long *)*plVar7 != (long *)0x0);
code_r0x01691fb0:
    if (((plVar7 != plVar6) && (*(uint *)((long)plVar7 + 0x1c) <= param_3)) && (plVar7 != plVar6)) {
      return (int)plVar7[4];
    }
  }
  uStack_2c = param_3;
  uVar3 = ItemModel::GetMaxLevel(unsigned int, unsigned int)(param_2,param_3);
  puStack_18 = &uStack_2c;
  lVar5 = std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, unsigned int>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, unsigned int>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, unsigned int>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, unsigned int>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, unsigned int>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, std::__ndk1::piecewise_construct_t const&, std::__ndk1::tuple<unsigned int const&>, std::__ndk1::tuple<> >(unsigned int const&, std::__ndk1::piecewise_construct_t const&, std::__ndk1::tuple<unsigned int const&>&&, std::__ndk1::tuple<>&&)(param_1,&uStack_2c,&UNK_02845184,&puStack_18,auStack_28);
  *(undefined4 *)(lVar5 + 0x20) = uVar3;
  return uVar3;
}

// ==== CMasterCache::tRoleNameCache::Get(std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > const&)
// vaddr 0x1592020 | ghidra 0x1692020 | size 820 | symbol _ZN12CMasterCache14tRoleNameCache3GetERKNSt6__ndk112basic_stringIcNS1_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS5_22CSTLStringAllocatorInfEEEEE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Type propagation algorithm not settling */

void _ZN12CMasterCache14tRoleNameCache3GetERKNSt6__ndk112basic_stringIcNS1_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS5_22CSTLStringAllocatorInfEEEEE
               (ulong *param_1,long *param_2,undefined8 param_3)

{
  ulong *puVar1;
  long *plVar2;
  undefined8 *puVar3;
  undefined8 *puVar4;
  ulong uVar5;
  ulong uVar6;
  ulong uVar7;
  long lVar8;
  ulong uVar9;
  ulong uStack_78;
  ulong uStack_70;
  ulong uStack_68;
  undefined1 auStack_60 [8];
  undefined8 uStack_58;
  undefined8 *apuStack_50 [3];
  undefined8 uStack_38;
  
  plVar2 = (long *)std::__ndk1::__tree_iterator<std::__ndk1::__value_type<string, string >, std::__ndk1::__tree_node<std::__ndk1::__value_type<string, string >, void*>*, long> std::__ndk1::__tree<std::__ndk1::__value_type<string, string >, std::__ndk1::__map_value_compare<string, std::__ndk1::__value_type<string, string >, std::__ndk1::less<string >, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<string, string >, Framework::CSTLMapAllocatorInf> >::find<string >(string const&)();
  if (plVar2 != param_2 + 1) {
    param_1[1] = 0;
    param_1[2] = 0;
    *param_1 = 0;
    if ((plVar2[7] & 1U) == 0) {
      param_1[2] = plVar2[9];
      uVar9 = plVar2[7];
      param_1[1] = plVar2[8];
      *param_1 = uVar9;
      return;
    }
    uVar9 = plVar2[8];
    lVar8 = plVar2[9];
    if (uVar9 < 0x17) {
      uVar6 = (long)param_1 + 1;
      *(char *)param_1 = (char)(uVar9 << 1);
      if (uVar9 == 0) goto code_r0x016921f0;
    }
    else {
      uVar7 = uVar9 + 0x10 & 0xfffffffffffffff0;
      if (uVar7 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
      }
      uVar6 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar7,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
      if (uVar6 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
      }
      param_1[1] = uVar9;
      param_1[2] = uVar6;
      *param_1 = uVar7 | 1;
    }
    memcpy(uVar6,lVar8,uVar9);
code_r0x016921f0:
    *(undefined1 *)(uVar6 + uVar9) = 0;
    return;
  }
  CUIUtility::GetSystemMessage(string const&, long, bool*)(&uStack_78,param_3,0,0);
  uStack_58 = param_3;
  puVar3 = (undefined8 *)std::__ndk1::__tree_node_base<void*>*& std::__ndk1::__tree<std::__ndk1::__value_type<string, string >, std::__ndk1::__map_value_compare<string, std::__ndk1::__value_type<string, string >, std::__ndk1::less<string >, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<string, string >, Framework::CSTLMapAllocatorInf> >::__find_equal<string >(std::__ndk1::__tree_node_base<void*>*&, string const&)(param_2,&uStack_38,param_3);
  puVar4 = (undefined8 *)*puVar3;
  if ((undefined8 *)*puVar3 == (undefined8 *)0x0) {
    std::__ndk1::unique_ptr<std::__ndk1::__tree_node<std::__ndk1::__value_type<string, string >, void*>, std::__ndk1::__tree_node_destructor<Framework::CSTLAllocator<std::__ndk1::__tree_node<std::__ndk1::__value_type<string, string >, void*>, Framework::CSTLMapAllocatorInf> > > std::__ndk1::__tree<std::__ndk1::__value_type<string, string >, std::__ndk1::__map_value_compare<string, std::__ndk1::__value_type<string, string >, std::__ndk1::less<string >, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<string, string >, Framework::CSTLMapAllocatorInf> >::__construct_node<std::__ndk1::piecewise_construct_t const&, std::__ndk1::tuple<string const&>, std::__ndk1::tuple<> >(std::__ndk1::piecewise_construct_t const&, std::__ndk1::tuple<string const&>&&, std::__ndk1::tuple<>&&)(apuStack_50,param_2,&UNK_02845184,&uStack_58,auStack_60);
    *apuStack_50[0] = 0;
    apuStack_50[0][1] = 0;
    apuStack_50[0][2] = uStack_38;
    *puVar3 = apuStack_50[0];
    puVar4 = apuStack_50[0];
    if (*(long *)*param_2 != 0) {
      *param_2 = *(long *)*param_2;
      puVar4 = (undefined8 *)*puVar3;
    }
    void std::__ndk1::__tree_balance_after_insert<std::__ndk1::__tree_node_base<void*>*>(std::__ndk1::__tree_node_base<void*>*, std::__ndk1::__tree_node_base<void*>*)(param_2[1],puVar4);
    param_2[2] = param_2[2] + 1;
    puVar4 = apuStack_50[0];
  }
  puVar1 = puVar4 + 7;
  if (puVar1 != &uStack_78) {
    uVar6 = (ulong)(byte)*puVar1;
    uVar9 = (ulong)((byte)uStack_78 >> 1);
    uVar7 = (ulong)&uStack_78 | 1;
    if (((byte)uStack_78 & 1) != 0) {
      uVar9 = uStack_70;
      uVar7 = uStack_68;
    }
    if (((byte)*puVar1 & 1) == 0) {
      uVar5 = 0x16;
      lVar8 = uVar9 - 0x16;
      if (0x15 < uVar9 && lVar8 != 0) {
code_r0x0169220c:
        if ((uVar6 & 1) == 0) {
          uVar7 = (ulong)(((uint)uVar6 & 0xfe) >> 1);
        }
        else {
          uVar7 = puVar4[8];
        }
        string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(puVar1,uVar5,lVar8,uVar7,0,uVar7,uVar9);
        goto code_r0x0169226c;
      }
    }
    else {
      uVar6 = *puVar1;
      uVar5 = (uVar6 & 0xfffffffffffffffe) - 1;
      lVar8 = uVar9 - uVar5;
      if (uVar5 <= uVar9 && lVar8 != 0) goto code_r0x0169220c;
    }
    if ((uVar6 & 1) == 0) {
      lVar8 = (long)puVar4 + 0x39;
    }
    else {
      lVar8 = puVar4[9];
    }
    if (uVar9 != 0) {
      memmove(lVar8,uVar7,uVar9);
    }
    *(undefined1 *)(lVar8 + uVar9) = 0;
    if ((*puVar1 & 1) == 0) {
      *(byte *)puVar1 = (byte)(uVar9 << 1);
    }
    else {
      puVar4[8] = uVar9;
    }
  }
code_r0x0169226c:
  uVar9 = uStack_68;
  param_1[1] = 0;
  param_1[2] = 0;
  *param_1 = 0;
  if (((byte)uStack_78 & 1) == 0) {
    param_1[2] = uStack_68;
    param_1[1] = uStack_70;
    *param_1 = CONCAT71(uStack_78._1_7_,(byte)uStack_78);
    goto joined_r0x01692334;
  }
  if (uStack_70 < 0x17) {
    uVar6 = (long)param_1 + 1;
    *(char *)param_1 = (char)(uStack_70 << 1);
    if (uStack_70 != 0) goto code_r0x0169231c;
  }
  else {
    uVar7 = uStack_70 + 0x10 & 0xfffffffffffffff0;
    if (uVar7 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
    }
    uVar6 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar7,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
    if (uVar6 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    }
    param_1[1] = uStack_70;
    param_1[2] = uVar6;
    *param_1 = uVar7 | 1;
code_r0x0169231c:
    memcpy(uVar6,uVar9,uStack_70);
  }
  *(undefined1 *)(uVar6 + uStack_70) = 0;
joined_r0x01692334:
  if (((byte)uStack_78 & 1) == 0) {
    return;
  }
  Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_68);
  return;
}

// ==== CMasterCache::tWeaponLevelMaxCache::Get(unsigned int, unsigned int)
// vaddr 0x1592354 | ghidra 0x1692354 | size 444 | symbol _ZN12CMasterCache20tWeaponLevelMaxCache3GetEjj | lib libSOA-3.7.0.so | 2026-10-08
undefined4 _ZN12CMasterCache20tWeaponLevelMaxCache3GetEjj(long param_1,uint param_2,uint param_3)

{
  long *plVar1;
  long *plVar2;
  undefined4 uVar3;
  long *plVar4;
  long lVar5;
  long *plVar6;
  long *plVar7;
  long *plVar8;
  uint **ppuStack_68;
  uint *puStack_60;
  undefined8 uStack_58;
  uint uStack_4c;
  uint auStack_48 [2];
  undefined1 auStack_40 [8];
  uint *puStack_38;
  
  plVar6 = (long *)(param_1 + 8);
  plVar2 = (long *)*plVar6;
  plVar4 = plVar6;
  uStack_4c = param_2;
  if ((long *)*plVar6 != (long *)0x0) {
    do {
      while (plVar8 = plVar2, *(uint *)(plVar8 + 4) < param_2) {
        plVar7 = plVar8 + 1;
        plVar8 = plVar4;
        plVar2 = (long *)*plVar7;
        if ((long *)*plVar7 == (long *)0x0) goto code_r0x016923ac;
      }
      plVar2 = (long *)*plVar8;
      plVar4 = plVar8;
    } while ((long *)*plVar8 != (long *)0x0);
code_r0x016923ac:
    if (((plVar8 != plVar6) && (*(uint *)(plVar8 + 4) <= param_2)) && (plVar8 != plVar6)) {
      puStack_38 = (uint *)CONCAT44(puStack_38._4_4_,param_3);
      plVar6 = plVar8 + 6;
      plVar2 = (long *)*plVar6;
      plVar4 = plVar6;
      if ((long *)*plVar6 != (long *)0x0) {
        do {
          while (plVar7 = plVar2, *(uint *)((long)plVar7 + 0x1c) < param_3) {
            plVar1 = plVar7 + 1;
            plVar7 = plVar4;
            plVar2 = (long *)*plVar1;
            if ((long *)*plVar1 == (long *)0x0) goto code_r0x016924b8;
          }
          plVar2 = (long *)*plVar7;
          plVar4 = plVar7;
        } while ((long *)*plVar7 != (long *)0x0);
code_r0x016924b8:
        if ((plVar7 != plVar6) && (*(uint *)((long)plVar7 + 0x1c) <= param_3)) {
          return (int)plVar7[4];
        }
      }
      uVar3 = ItemModel::GetMaxLevel(unsigned int, unsigned int)(param_2,param_3);
      ppuStack_68 = &puStack_38;
      lVar5 = std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, unsigned int>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, unsigned int>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, unsigned int>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, unsigned int>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, unsigned int>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, std::__ndk1::piecewise_construct_t const&, std::__ndk1::tuple<unsigned int const&>, std::__ndk1::tuple<> >(unsigned int const&, std::__ndk1::piecewise_construct_t const&, std::__ndk1::tuple<unsigned int const&>&&, std::__ndk1::tuple<>&&)(plVar8 + 5,&puStack_38,&UNK_02845184,&ppuStack_68,auStack_48);
      *(undefined4 *)(lVar5 + 0x20) = uVar3;
      return uVar3;
    }
  }
  puStack_60 = (uint *)0x0;
  uStack_58 = 0;
  ppuStack_68 = &puStack_60;
  auStack_48[0] = param_3;
  uVar3 = ItemModel::GetMaxLevel(unsigned int, unsigned int)(param_2,param_3);
  puStack_38 = auStack_48;
  lVar5 = std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, unsigned int>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, unsigned int>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, unsigned int>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, unsigned int>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, unsigned int>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, std::__ndk1::piecewise_construct_t const&, std::__ndk1::tuple<unsigned int const&>, std::__ndk1::tuple<> >(unsigned int const&, std::__ndk1::piecewise_construct_t const&, std::__ndk1::tuple<unsigned int const&>&&, std::__ndk1::tuple<>&&)(&ppuStack_68,auStack_48,&UNK_02845184,&puStack_38,auStack_40);
  *(undefined4 *)(lVar5 + 0x20) = uVar3;
  puStack_38 = &uStack_4c;
  lVar5 = std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, CMasterCache::tWeaponLevelMaxCache2>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, CMasterCache::tWeaponLevelMaxCache2>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, CMasterCache::tWeaponLevelMaxCache2>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, CMasterCache::tWeaponLevelMaxCache2>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, CMasterCache::tWeaponLevelMaxCache2>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, std::__ndk1::piecewise_construct_t const&, std::__ndk1::tuple<unsigned int const&>, std::__ndk1::tuple<> >(unsigned int const&, std::__ndk1::piecewise_construct_t const&, std::__ndk1::tuple<unsigned int const&>&&, std::__ndk1::tuple<>&&)(param_1,&uStack_4c,&UNK_02845184,&puStack_38,auStack_48);
  if ((uint ***)(lVar5 + 0x28) != &ppuStack_68) {
    void std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, unsigned int>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, unsigned int>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, unsigned int>, Framework::CSTLMapAllocatorInf> >::__assign_multi<std::__ndk1::__tree_const_iterator<std::__ndk1::__value_type<unsigned int, unsigned int>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, unsigned int>, void*>*, long> >(std::__ndk1::__tree_const_iterator<std::__ndk1::__value_type<unsigned int, unsigned int>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, unsigned int>, void*>*, long>, std::__ndk1::__tree_const_iterator<std::__ndk1::__value_type<unsigned int, unsigned int>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, unsigned int>, void*>*, long>)((uint ***)(lVar5 + 0x28),ppuStack_68,&puStack_60);
  }
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, unsigned int>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, unsigned int>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, unsigned int>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, unsigned int>, void*>*)(&ppuStack_68,puStack_60);
  return uVar3;
}

// ==== CMasterCache::tWeaponKind::tWeaponKind()
// vaddr 0x1592510 | ghidra 0x1692510 | size 28 | symbol _ZN12CMasterCache11tWeaponKindC1Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN12CMasterCache11tWeaponKindC2Ev(undefined8 *param_1)

{
  *(undefined8 *)((long)param_1 + 0x15) = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  *param_1 = 0;
  param_1[5] = 0;
  param_1[6] = 0;
  *(undefined1 *)(param_1 + 7) = 0;
  param_1[4] = 0;
  return;
}

// ==== CMasterCache::tWeaponKindCache::Get(unsigned int)
// vaddr 0x159252c | ghidra 0x169252c | size 880 | symbol _ZN12CMasterCache16tWeaponKindCache3GetEj | lib libSOA-3.7.0.so | 2026-10-08
long * _ZN12CMasterCache16tWeaponKindCache3GetEj(long param_1,uint param_2)

{
  long *plVar1;
  char *pcVar2;
  char *pcVar3;
  ulong uVar4;
  long lVar5;
  char *pcVar6;
  long *plVar7;
  bool bVar8;
  long lVar9;
  long *plVar10;
  long *plVar11;
  char *pcVar12;
  char *pcVar13;
  long *plVar14;
  uint *puStack_b8;
  ulong uStack_b0;
  undefined1 *puStack_a8;
  uint *puStack_a0;
  ulong uStack_98;
  undefined5 uStack_90;
  undefined3 uStack_8b;
  undefined4 uStack_88;
  undefined1 uStack_84;
  uint *puStack_80;
  undefined8 uStack_78;
  undefined1 *puStack_70;
  bool bStack_68;
  long *plStack_58;
  long *plStack_50;
  undefined1 auStack_38 [4];
  uint uStack_34;
  
  plVar11 = (long *)(param_1 + 8);
  plVar7 = (long *)*plVar11;
  plVar14 = plVar11;
  if ((long *)*plVar11 != (long *)0x0) {
    do {
      while (plVar10 = plVar7, *(uint *)(plVar10 + 4) < param_2) {
        plVar1 = plVar10 + 1;
        plVar10 = plVar14;
        plVar7 = (long *)*plVar1;
        if ((long *)*plVar1 == (long *)0x0) goto code_r0x01692588;
      }
      plVar7 = (long *)*plVar10;
      plVar14 = plVar10;
    } while ((long *)*plVar10 != (long *)0x0);
code_r0x01692588:
    if (((plVar10 != plVar11) && (*(uint *)(plVar10 + 4) <= param_2)) && (plVar10 != plVar11))
    goto code_r0x01692880;
  }
  uStack_34 = param_2;
  CParameterUtility::CollectWeaponKind()(&plStack_58);
  plVar7 = plStack_50;
  uStack_88 = 0;
  uStack_84 = 0;
  uStack_98 = 0;
  uStack_90 = 0;
  uStack_8b = 0;
  puStack_a0 = (uint *)0x0;
  uStack_78 = 0;
  puStack_70 = (undefined1 *)0x0;
  bStack_68 = false;
  puStack_80 = (uint *)0x0;
  if (plStack_58 != plStack_50) {
    plVar14 = plStack_58;
    do {
      lVar9 = *plVar14;
      lVar5 = plVar14[1];
      if (lVar5 != 0) {
        std::__ndk1::__shared_weak_count::__add_shared()(lVar5);
      }
      if (uStack_34 == *(uint *)(lVar9 + 0x38)) {
        uStack_b0 = 0;
        puStack_a8 = (undefined1 *)0x0;
        puStack_b8 = (uint *)0x0;
        void CParameterPropertyBase<69u>::CryptString<string >(string&, string const&)(&puStack_b8,lVar9 + 0x68);
        if (((ulong)puStack_a0 & 1) == 0) {
          puStack_a0 = (uint *)((ulong)puStack_a0 & 0xffffffffffff0000);
        }
        else {
          *(undefined1 *)CONCAT35(uStack_8b,uStack_90) = 0;
          uStack_98 = 0;
        }
        string::reserve(unsigned long)(&puStack_a0,0);
        uStack_90 = SUB85(puStack_a8,0);
        uStack_8b = (undefined3)((ulong)puStack_a8 >> 0x28);
        uStack_98 = uStack_b0;
        puStack_a0 = puStack_b8;
        uStack_88 = *(undefined4 *)(lVar9 + 0x6c8);
        uStack_84 = *(undefined1 *)(lVar9 + 0x6f8);
        uStack_b0 = 0;
        puStack_a8 = (undefined1 *)0x0;
        puStack_b8 = (uint *)0x0;
        void CParameterPropertyBase<106u>::CryptString<string >(string&, string const&)(&puStack_b8,lVar9 + 0x728);
        if (((ulong)puStack_80 & 1) == 0) {
          puStack_80 = (uint *)((ulong)puStack_80 & 0xffffffffffff0000);
        }
        else {
          *puStack_70 = 0;
          uStack_78 = 0;
        }
        string::reserve(unsigned long)(&puStack_80,0);
        puStack_70 = puStack_a8;
        uStack_78 = uStack_b0;
        puStack_80 = puStack_b8;
        uVar4 = (ulong)puStack_a0 >> 1 & 0x7f;
        pcVar6 = (char *)((ulong)&puStack_a0 | 1);
        if (((ulong)puStack_a0 & 1) != 0) {
          uVar4 = uStack_98;
          pcVar6 = (char *)CONCAT35(uStack_8b,uStack_90);
        }
        if (uVar4 < 5) {
          bStack_68 = false;
          goto joined_r0x016926ec;
        }
        pcVar3 = pcVar6 + uVar4;
        pcVar12 = pcVar3;
        if (((long)uVar4 < 5) || (pcVar3 + -4 == pcVar6)) goto code_r0x01692780;
        pcVar13 = pcVar6;
        goto code_r0x01692728;
      }
      if (lVar5 != 0) {
        std::__ndk1::__shared_weak_count::__release_shared()(lVar5);
      }
      plVar14 = plVar14 + 2;
    } while (plVar14 != plVar7);
  }
  goto code_r0x016927a8;
  while (pcVar13 = pcVar13 + 1, pcVar12 = pcVar3, pcVar3 + -4 != pcVar13) {
code_r0x01692728:
    if (*pcVar13 == 'W') {
      lVar9 = 1;
      do {
        pcVar12 = pcVar13;
        if (lVar9 == 5) goto code_r0x01692780;
        pcVar12 = pcVar13 + lVar9;
        pcVar2 = &UNK_02844d37/*"W99St"*/ + lVar9;
        lVar9 = lVar9 + 1;
      } while (*pcVar12 == *pcVar2);
      bVar8 = pcVar3 + -5 == pcVar13;
      pcVar12 = pcVar3;
      pcVar13 = pcVar13 + 1;
      if (bVar8) break;
      goto code_r0x01692728;
    }
  }
code_r0x01692780:
  bStack_68 = (long)pcVar12 - (long)pcVar6 != -1 && pcVar3 != pcVar12;
joined_r0x016926ec:
  if (lVar5 != 0) {
    std::__ndk1::__shared_weak_count::__release_shared()(lVar5);
  }
code_r0x016927a8:
  puStack_b8 = &uStack_34;
  lVar9 = std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, CMasterCache::tWeaponKind>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, CMasterCache::tWeaponKind>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, CMasterCache::tWeaponKind>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, CMasterCache::tWeaponKind>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, CMasterCache::tWeaponKind>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, std::__ndk1::piecewise_construct_t const&, std::__ndk1::tuple<unsigned int const&>, std::__ndk1::tuple<> >(unsigned int const&, std::__ndk1::piecewise_construct_t const&, std::__ndk1::tuple<unsigned int const&>&&, std::__ndk1::tuple<>&&)(param_1,&uStack_34,&UNK_02845184,&puStack_b8,auStack_38);
  CMasterCache::tWeaponKind::operator=(CMasterCache::tWeaponKind const&)(lVar9 + 0x28,&puStack_a0);
  puStack_b8 = &uStack_34;
  plVar10 = (long *)std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, CMasterCache::tWeaponKind>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, CMasterCache::tWeaponKind>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, CMasterCache::tWeaponKind>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, CMasterCache::tWeaponKind>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, CMasterCache::tWeaponKind>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, std::__ndk1::piecewise_construct_t const&, std::__ndk1::tuple<unsigned int const&>, std::__ndk1::tuple<> >(unsigned int const&, std::__ndk1::piecewise_construct_t const&, std::__ndk1::tuple<unsigned int const&>&&, std::__ndk1::tuple<>&&)(param_1,&uStack_34,&UNK_02845184,&puStack_b8,auStack_38);
  if (((ulong)puStack_80 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puStack_70);
  }
  plVar7 = plStack_58;
  if (((ulong)puStack_a0 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(CONCAT35(uStack_8b,uStack_90));
    plVar7 = plStack_58;
  }
  plStack_58 = plVar7;
  if (plVar7 != (long *)0x0) {
    while (plStack_50 != plVar7) {
      while (plVar11 = plStack_50 + -2, plVar14 = plStack_50 + -1, plStack_50 = plVar11,
            *plVar14 != 0) {
        std::__ndk1::__shared_weak_count::__release_shared()();
        if (plStack_50 == plVar7) goto code_r0x01692878;
      }
    }
code_r0x01692878:
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plStack_58);
  }
code_r0x01692880:
  return plVar10 + 5;
}

// ==== CMasterCache::tWeaponKind::operator=(CMasterCache::tWeaponKind const&)
// vaddr 0x159289c | ghidra 0x169289c | size 452 | symbol _ZN12CMasterCache11tWeaponKindaSERKS0_ | lib libSOA-3.7.0.so | 2026-10-08
ulong * _ZN12CMasterCache11tWeaponKindaSERKS0_(ulong *param_1,ulong *param_2)

{
  ulong uVar1;
  byte *pbVar2;
  ulong uVar3;
  long lVar4;
  ulong uVar5;
  ulong *puVar6;
  byte *pbVar7;
  
  if (param_1 == param_2) {
    *(byte *)((long)param_1 + 0x1c) = *(byte *)((long)param_2 + 0x1c);
    *(int *)(param_1 + 3) = (int)param_2[3];
    goto code_r0x01692a44;
  }
  uVar1 = param_2[1];
  pbVar2 = (byte *)param_2[2];
  uVar5 = (ulong)(byte)*param_1;
  if (((byte)*param_2 & 1) == 0) {
    pbVar2 = (byte *)((long)param_2 + 1);
    uVar1 = (ulong)(byte)((byte)*param_2 >> 1);
  }
  if (((byte)*param_1 & 1) == 0) {
    uVar3 = 0x16;
    lVar4 = uVar1 - 0x16;
    if (0x15 < uVar1 && lVar4 != 0) goto code_r0x0169291c;
code_r0x016928e4:
    if ((uVar5 & 1) == 0) {
      pbVar7 = (byte *)((long)param_1 + 1);
    }
    else {
      pbVar7 = (byte *)param_1[2];
    }
    if (uVar1 != 0) {
      memmove(pbVar7,pbVar2,uVar1);
    }
    pbVar7[uVar1] = 0;
    if ((*param_1 & 1) == 0) {
      *(byte *)param_1 = (byte)(uVar1 << 1);
    }
    else {
      param_1[1] = uVar1;
    }
  }
  else {
    uVar5 = *param_1;
    uVar3 = (uVar5 & 0xfffffffffffffffe) - 1;
    lVar4 = uVar1 - uVar3;
    if (uVar1 < uVar3 || lVar4 == 0) goto code_r0x016928e4;
code_r0x0169291c:
    if ((uVar5 & 1) == 0) {
      uVar5 = (ulong)(((uint)uVar5 & 0xfe) >> 1);
    }
    else {
      uVar5 = param_1[1];
    }
    string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(param_1,uVar3,lVar4,uVar5,0,uVar5,uVar1);
  }
  puVar6 = param_1 + 4;
  uVar5 = (ulong)(byte)*puVar6;
  *(int *)(param_1 + 3) = (int)param_2[3];
  *(byte *)((long)param_1 + 0x1c) = *(byte *)((long)param_2 + 0x1c);
  uVar1 = (ulong)(byte)((byte)param_2[4] >> 1);
  pbVar2 = (byte *)((long)param_2 + 0x21);
  if (((byte)param_2[4] & 1) != 0) {
    uVar1 = param_2[5];
    pbVar2 = (byte *)param_2[6];
  }
  if (((byte)*puVar6 & 1) == 0) {
    uVar3 = 0x16;
    lVar4 = uVar1 - 0x16;
    if (0x15 < uVar1 && lVar4 != 0) {
code_r0x016929e4:
      if ((uVar5 & 1) == 0) {
        uVar5 = (ulong)(((uint)uVar5 & 0xfe) >> 1);
      }
      else {
        uVar5 = param_1[5];
      }
      string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(puVar6,uVar3,lVar4,uVar5,0,uVar5,uVar1);
      goto code_r0x01692a44;
    }
  }
  else {
    uVar5 = *puVar6;
    uVar3 = (uVar5 & 0xfffffffffffffffe) - 1;
    lVar4 = uVar1 - uVar3;
    if (uVar3 <= uVar1 && lVar4 != 0) goto code_r0x016929e4;
  }
  if ((uVar5 & 1) == 0) {
    pbVar7 = (byte *)((long)param_1 + 0x21);
  }
  else {
    pbVar7 = (byte *)param_1[6];
  }
  if (uVar1 != 0) {
    memmove(pbVar7,pbVar2,uVar1);
  }
  pbVar7[uVar1] = 0;
  if ((*puVar6 & 1) == 0) {
    *(byte *)puVar6 = (byte)(uVar1 << 1);
  }
  else {
    param_1[5] = uVar1;
  }
code_r0x01692a44:
  *(byte *)(param_1 + 7) = (byte)param_2[7];
  return param_1;
}

// ==== CMasterCache::tRoleEvolutionCache::Get(unsigned int, unsigned int, unsigned int)
// vaddr 0x1592a60 | ghidra 0x1692a60 | size 656 | symbol _ZN12CMasterCache19tRoleEvolutionCache3GetEjjj | lib libSOA-3.7.0.so | 2026-10-08
void _ZN12CMasterCache19tRoleEvolutionCache3GetEjjj
               (long *param_1,long param_2,int param_3,int param_4,int param_5)

{
  undefined *puVar1;
  long *plVar2;
  long *plVar3;
  long lVar4;
  undefined8 uVar5;
  long lVar6;
  long lVar7;
  long *plVar8;
  long *plVar9;
  undefined8 uStack_3e0;
  long lStack_3d8;
  uint uStack_3cc;
  undefined *puStack_3c8;
  undefined8 uStack_3c0;
  uint **ppuStack_3b8;
  undefined8 uStack_3b0;
  undefined4 uStack_3a8;
  undefined1 uStack_3a4;
  undefined *puStack_3a0;
  undefined8 uStack_398;
  undefined1 *puStack_390;
  undefined8 uStack_388;
  undefined4 uStack_380;
  undefined1 uStack_37c;
  undefined *puStack_378;
  undefined8 uStack_370;
  undefined1 *puStack_368;
  undefined8 uStack_360;
  undefined4 uStack_358;
  undefined1 uStack_354;
  undefined1 auStack_350 [256];
  undefined1 auStack_250 [256];
  uint *apuStack_150 [32];
  
  puVar1 = PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
  uStack_3cc = param_3 * 100000 + param_4 * 1000 + param_5 * 10;
  plVar9 = (long *)(param_2 + 8);
  plVar2 = (long *)*plVar9;
  plVar3 = plVar9;
  if ((long *)*plVar9 != (long *)0x0) {
    do {
      while (plVar8 = plVar2, *(uint *)(plVar8 + 4) < uStack_3cc) {
        plVar2 = (long *)plVar8[1];
        if ((long *)plVar8[1] == (long *)0x0) {
          plVar8 = plVar3;
          if (plVar3 == plVar9) goto code_r0x01692b2c;
          goto code_r0x01692afc;
        }
      }
      plVar2 = (long *)*plVar8;
      plVar3 = plVar8;
    } while ((long *)*plVar8 != (long *)0x0);
    if (plVar8 != plVar9) {
code_r0x01692afc:
      if ((*(uint *)(plVar8 + 4) <= uStack_3cc) && (plVar8 != plVar9)) {
        *param_1 = plVar8[5];
        lVar4 = plVar8[6];
        param_1[1] = lVar4;
        if (lVar4 == 0) {
          return;
        }
        std::__ndk1::__shared_weak_count::__add_shared()();
        return;
      }
    }
  }
code_r0x01692b2c:
  lVar4 = *(long *)PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
  if (lVar4 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar4 = *(long *)puVar1;
  }
  uVar5 = CParameterManager::pMasterParameterRoleEvolution() const(lVar4);
  snprintf(apuStack_150,0x100,&UNK_027e6d32/*"%u"*/,param_3);
  snprintf(auStack_250,0x100,&UNK_027e6d32/*"%u"*/,param_4);
  snprintf(auStack_350,0x100,&UNK_027e6d32/*"%u"*/,param_5);
  puStack_3c8 = &UNK_02935795/*"rank"*/;
  uStack_3c0 = 4;
  ppuStack_3b8 = apuStack_150;
  uStack_3b0 = strlen(apuStack_150);
  uStack_3a8 = 0;
  uStack_3a4 = 0;
  puStack_3a0 = &UNK_027ffc7f/*"rarity"*/;
  uStack_398 = 6;
  puStack_390 = auStack_250;
  uStack_388 = strlen(auStack_250);
  uStack_380 = 0;
  uStack_37c = 0;
  puStack_378 = &UNK_0282ee3e/*"category_type"*/;
  uStack_370 = 0xd;
  puStack_368 = auStack_350;
  uStack_360 = strlen(auStack_350);
  uStack_358 = 0;
  uStack_354 = 0;
  CMasterParameterBaseSqlite_Simple<CMasterParameterRoleEvolutionElement>::ParameterByQuery(char const*, Aska::Yayoi::QueryParam*, unsigned int) const(&uStack_3e0,uVar5,&UNK_02844e7e/*"SELECT * FROM master_role_evolution WHERE rank=? AND rarity=? AND category_type=?"*/,&puStack_3c8,3);
  apuStack_150[0] = &uStack_3cc;
  lVar6 = std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, std::__ndk1::shared_ptr<CMasterParameterRoleEvolutionElement> >, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, std::__ndk1::shared_ptr<CMasterParameterRoleEvolutionElement> >, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, std::__ndk1::shared_ptr<CMasterParameterRoleEvolutionElement> >, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, std::__ndk1::shared_ptr<CMasterParameterRoleEvolutionElement> >, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, std::__ndk1::shared_ptr<CMasterParameterRoleEvolutionElement> >, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, std::__ndk1::piecewise_construct_t const&, std::__ndk1::tuple<unsigned int const&>, std::__ndk1::tuple<> >(unsigned int const&, std::__ndk1::piecewise_construct_t const&, std::__ndk1::tuple<unsigned int const&>&&, std::__ndk1::tuple<>&&)(param_2,&uStack_3cc,&UNK_02845184,apuStack_150,auStack_250);
  lVar4 = lStack_3d8;
  if (lStack_3d8 != 0) {
    std::__ndk1::__shared_weak_count::__add_shared()(lStack_3d8);
  }
  lVar7 = *(long *)(lVar6 + 0x30);
  *(undefined8 *)(lVar6 + 0x28) = uStack_3e0;
  *(long *)(lVar6 + 0x30) = lVar4;
  if (lVar7 != 0) {
    std::__ndk1::__shared_weak_count::__release_shared()();
  }
  apuStack_150[0] = &uStack_3cc;
  lVar4 = std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, std::__ndk1::shared_ptr<CMasterParameterRoleEvolutionElement> >, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, std::__ndk1::shared_ptr<CMasterParameterRoleEvolutionElement> >, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, std::__ndk1::shared_ptr<CMasterParameterRoleEvolutionElement> >, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, std::__ndk1::shared_ptr<CMasterParameterRoleEvolutionElement> >, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, std::__ndk1::shared_ptr<CMasterParameterRoleEvolutionElement> >, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, std::__ndk1::piecewise_construct_t const&, std::__ndk1::tuple<unsigned int const&>, std::__ndk1::tuple<> >(unsigned int const&, std::__ndk1::piecewise_construct_t const&, std::__ndk1::tuple<unsigned int const&>&&, std::__ndk1::tuple<>&&)(param_2,&uStack_3cc,&UNK_02845184,apuStack_150,auStack_250);
  *param_1 = *(long *)(lVar4 + 0x28);
  lVar4 = *(long *)(lVar4 + 0x30);
  param_1[1] = lVar4;
  if (lVar4 != 0) {
    std::__ndk1::__shared_weak_count::__add_shared()();
  }
  if (lStack_3d8 != 0) {
    std::__ndk1::__shared_weak_count::__release_shared()();
  }
  return;
}

// ==== CMasterCache::CMasterCache()
// vaddr 0x1592cf0 | ghidra 0x1692cf0 | size 104 | symbol _ZN12CMasterCacheC1Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN12CMasterCacheC2Ev(undefined8 *param_1)

{
  param_1[2] = 0;
  param_1[1] = 0;
  *param_1 = param_1 + 1;
  param_1[5] = 0;
  param_1[4] = 0;
  param_1[3] = param_1 + 4;
  param_1[8] = 0;
  param_1[7] = 0;
  param_1[6] = param_1 + 7;
  param_1[0xb] = 0;
  param_1[10] = 0;
  param_1[9] = param_1 + 10;
  param_1[0xe] = 0;
  param_1[0xd] = 0;
  param_1[0x10] = 0;
  param_1[0xc] = param_1 + 0xd;
  param_1[0x11] = 0;
  param_1[0xf] = param_1 + 0x10;
  *(undefined4 *)(param_1 + 0x12) = 0xffffffff;
  return;
}

// ==== CMasterCache::Reset()
// vaddr 0x1592d58 | ghidra 0x1692d58 | size 188 | symbol _ZN12CMasterCache5ResetEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN12CMasterCache5ResetEv(undefined8 *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = param_1 + 1;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, unsigned int>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, unsigned int>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, unsigned int>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, unsigned int>, void*>*)(param_1,*puVar1);
  *param_1 = puVar1;
  param_1[2] = 0;
  *puVar1 = 0;
  puVar1 = param_1 + 4;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, unsigned int>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, unsigned int>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, unsigned int>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, unsigned int>, void*>*)(param_1 + 3,*puVar1);
  param_1[3] = puVar1;
  param_1[5] = 0;
  *puVar1 = 0;
  puVar1 = param_1 + 7;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, CMasterCache::tWeaponLevelMaxCache2>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, CMasterCache::tWeaponLevelMaxCache2>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, CMasterCache::tWeaponLevelMaxCache2>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, CMasterCache::tWeaponLevelMaxCache2>, void*>*)(param_1 + 6,*puVar1);
  param_1[6] = puVar1;
  param_1[8] = 0;
  *puVar1 = 0;
  puVar1 = param_1 + 10;
  std::__ndk1::__tree<std::__ndk1::__value_type<string, string >, std::__ndk1::__map_value_compare<string, std::__ndk1::__value_type<string, string >, std::__ndk1::less<string >, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<string, string >, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<string, string >, void*>*)(param_1 + 9,*puVar1);
  param_1[9] = puVar1;
  param_1[0xb] = 0;
  *puVar1 = 0;
  puVar1 = param_1 + 0xd;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, CMasterCache::tWeaponKind>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, CMasterCache::tWeaponKind>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, CMasterCache::tWeaponKind>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, CMasterCache::tWeaponKind>, void*>*)(param_1 + 0xc,*puVar1);
  param_1[0xc] = puVar1;
  *puVar1 = 0;
  param_1[0xe] = 0;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, std::__ndk1::shared_ptr<CMasterParameterRoleEvolutionElement> >, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, std::__ndk1::shared_ptr<CMasterParameterRoleEvolutionElement> >, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, std::__ndk1::shared_ptr<CMasterParameterRoleEvolutionElement> >, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, std::__ndk1::shared_ptr<CMasterParameterRoleEvolutionElement> >, void*>*)(param_1 + 0xf,param_1[0x10]);
  param_1[0xf] = param_1 + 0x10;
  param_1[0x10] = 0;
  param_1[0x11] = 0;
  *(undefined4 *)(param_1 + 0x12) = 0xffffffff;
  return;
}

// ==== CMasterCache::LevelMax(unsigned int)
// vaddr 0x1592e14 | ghidra 0x1692e14 | size 4 | symbol _ZN12CMasterCache8LevelMaxEj | lib libSOA-3.7.0.so | 2026-10-08
void _ZN12CMasterCache8LevelMaxEj(void)

{
  (*(code *)PTR__ZN12CMasterCache14tLevelMaxCache3GetEj_02c90b78)();
  return;
}

// ==== CMasterCache::LimitBreakMax(unsigned int)
// vaddr 0x1592e18 | ghidra 0x1692e18 | size 184 | symbol _ZN12CMasterCache13LimitBreakMaxEj | lib libSOA-3.7.0.so | 2026-10-08
undefined4 _ZN12CMasterCache13LimitBreakMaxEj(long param_1,uint param_2)

{
  long *plVar1;
  long *plVar2;
  undefined4 uVar3;
  long *plVar4;
  long lVar5;
  long *plVar6;
  long *plVar7;
  uint uStack_2c;
  undefined1 auStack_28 [8];
  uint *puStack_18;
  
  plVar6 = (long *)(param_1 + 0x20);
  plVar2 = (long *)*plVar6;
  plVar4 = plVar6;
  if ((long *)*plVar6 != (long *)0x0) {
    do {
      while (plVar7 = plVar2, *(uint *)((long)plVar7 + 0x1c) < param_2) {
        plVar1 = plVar7 + 1;
        plVar7 = plVar4;
        plVar2 = (long *)*plVar1;
        if ((long *)*plVar1 == (long *)0x0) goto code_r0x01692e6c;
      }
      plVar2 = (long *)*plVar7;
      plVar4 = plVar7;
    } while ((long *)*plVar7 != (long *)0x0);
code_r0x01692e6c:
    if ((plVar7 != plVar6) && (*(uint *)((long)plVar7 + 0x1c) <= param_2)) {
      return (int)plVar7[4];
    }
  }
  uStack_2c = param_2;
  uVar3 = CParameterUtility::CalcMasterRole2LimitBreakMax(unsigned int)(param_2);
  puStack_18 = &uStack_2c;
  lVar5 = std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, unsigned int>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, unsigned int>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, unsigned int>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, unsigned int>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, unsigned int>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, std::__ndk1::piecewise_construct_t const&, std::__ndk1::tuple<unsigned int const&>, std::__ndk1::tuple<> >(unsigned int const&, std::__ndk1::piecewise_construct_t const&, std::__ndk1::tuple<unsigned int const&>&&, std::__ndk1::tuple<>&&)(param_1 + 0x18,&uStack_2c,&UNK_02845184,&puStack_18,auStack_28);
  *(undefined4 *)(lVar5 + 0x20) = uVar3;
  return uVar3;
}

// ==== CMasterCache::WeaponLevelMax(unsigned int, unsigned int)
// vaddr 0x1592ed0 | ghidra 0x1692ed0 | size 8 | symbol _ZN12CMasterCache14WeaponLevelMaxEjj | lib libSOA-3.7.0.so | 2026-10-08
void _ZN12CMasterCache14WeaponLevelMaxEjj(long param_1)

{
  (*(code *)PTR__ZN12CMasterCache20tWeaponLevelMaxCache3GetEjj_02cace70)(param_1 + 0x30);
  return;
}

// ==== CMasterCache::RoleName(std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > const&)
// vaddr 0x1592ed8 | ghidra 0x1692ed8 | size 8 | symbol _ZN12CMasterCache8RoleNameERKNSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN12CMasterCache8RoleNameERKNSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEE
               (long param_1)

{
  (*(code *)
    PTR__ZN12CMasterCache14tRoleNameCache3GetERKNSt6__ndk112basic_stringIcNS1_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS5_22CSTLStringAllocatorInfEEEEE_02c96d50
  )(param_1 + 0x48);
  return;
}

// ==== CMasterCache::Instance()
// vaddr 0x1592ee0 | ghidra 0x1692ee0 | size 64 | symbol _ZN12CMasterCache8InstanceEv | lib libSOA-3.7.0.so | 2026-10-08
long _ZN12CMasterCache8InstanceEv(void)

{
  undefined *puVar1;
  long lVar2;
  
  puVar1 = PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
  lVar2 = *(long *)PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
  if (lVar2 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar2 = *(long *)puVar1;
  }
  lVar2 = CParameterManager::pParameterUI() const(lVar2);
  return lVar2 + 0x90;
}

// ==== CMasterCache::IsTick()
// vaddr 0x1592f20 | ghidra 0x1692f20 | size 124 | symbol _ZN12CMasterCache6IsTickEv | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

bool _ZN12CMasterCache6IsTickEv(long param_1)

{
  int iVar1;
  byte bStack_28;
  undefined7 uStack_27;
  undefined1 uStack_20;
  undefined4 uStack_1f;
  undefined1 uStack_1b;
  undefined2 uStack_1a;
  undefined8 uStack_18;
  
  iVar1 = *(int *)(param_1 + 0x90);
  if (iVar1 < 0) {
    uStack_1a = 0;
    uStack_18 = 0;
    bStack_28 = 0x18;
    uStack_27 = (undefined7)_UNK_02844d3d;
    uStack_20 = (undefined1)((ulong)_UNK_02844d3d >> 0x38);
    uStack_1f = 0x656c6261;
    uStack_1b = 0;
    iVar1 = CParameterUtility::FindGlobalNumberWithKey(string const&, unsigned int)(&bStack_28,0);
    *(int *)(param_1 + 0x90) = iVar1;
    if ((bStack_28 & 1) != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_18);
      iVar1 = *(int *)(param_1 + 0x90);
    }
  }
  return iVar1 == 0;
}

// ==== CMasterCache::IsStrengMaterial(unsigned int)
// vaddr 0x1592f9c | ghidra 0x1692f9c | size 24 | symbol _ZN12CMasterCache16IsStrengMaterialEj | lib libSOA-3.7.0.so | 2026-10-08
undefined1 _ZN12CMasterCache16IsStrengMaterialEj(long param_1)

{
  long lVar1;
  
  lVar1 = CMasterCache::tWeaponKindCache::Get(unsigned int)(param_1 + 0x60);
  return *(undefined1 *)(lVar1 + 0x38);
}

// ==== CMasterCache::WeaponKindOrderIndex(unsigned int)
// vaddr 0x1592fb4 | ghidra 0x1692fb4 | size 24 | symbol _ZN12CMasterCache20WeaponKindOrderIndexEj | lib libSOA-3.7.0.so | 2026-10-08
undefined4 _ZN12CMasterCache20WeaponKindOrderIndexEj(long param_1)

{
  long lVar1;
  
  lVar1 = CMasterCache::tWeaponKindCache::Get(unsigned int)(param_1 + 0x60);
  return *(undefined4 *)(lVar1 + 0x18);
}

// ==== CMasterCache::RoleEvolution(unsigned int, unsigned int, unsigned int)
// vaddr 0x1592fcc | ghidra 0x1692fcc | size 8 | symbol _ZN12CMasterCache13RoleEvolutionEjjj | lib libSOA-3.7.0.so | 2026-10-08
void _ZN12CMasterCache13RoleEvolutionEjjj(long param_1)

{
  (*(code *)PTR__ZN12CMasterCache19tRoleEvolutionCache3GetEjjj_02ca9f20)(param_1 + 0x78);
  return;
}

// ==== std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, CMasterCache::tWeaponLevelMaxCache2>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, CMasterCache::tWeaponLevelMaxCache2>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, CMasterCache::tWeaponLevelMaxCache2>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, CMasterCache::tWeaponLevelMaxCache2>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, CMasterCache::tWeaponLevelMaxCache2>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, std::__ndk1::piecewise_construct_t const&, std::__ndk1::tuple<unsigned int const&>, std::__ndk1::tuple<> >(unsigned int const&, std::__ndk1::piecewise_construct_t const&, std::__ndk1::tuple<unsigned int const&>&&, std::__ndk1::tuple<>&&)
// vaddr 0x159a028 | ghidra 0x169a028 | size 336 | symbol _ZNSt6__ndk16__treeINS_12__value_typeIjN12CMasterCache21tWeaponLevelMaxCache2EEENS_19__map_value_compareIjS4_NS_4lessIjEELb1EEEN9Framework13CSTLAllocatorIS4_NS9_19CSTLMapAllocatorInfEEEE25__emplace_unique_key_argsIjJRKNS_21piecewise_construct_tENS_5tupleIJRKjEEENSI_IJEEEEEENS_4pairINS_15__tree_iteratorIS4_PNS_11__tree_nodeIS4_PvEElEEbEERKT_DpOT0_ | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Type propagation algorithm not settling */

undefined1  [16]
_ZNSt6__ndk16__treeINS_12__value_typeIjN12CMasterCache21tWeaponLevelMaxCache2EEENS_19__map_value_compareIjS4_NS_4lessIjEELb1EEEN9Framework13CSTLAllocatorIS4_NS9_19CSTLMapAllocatorInfEEEE25__emplace_unique_key_argsIjJRKNS_21piecewise_construct_tENS_5tupleIJRKjEEENSI_IJEEEEEENS_4pairINS_15__tree_iteratorIS4_PNS_11__tree_nodeIS4_PvEElEEbEERKT_DpOT0_
          (long *param_1,uint *param_2,undefined8 param_3,undefined8 *param_4)

{
  undefined4 uVar1;
  long *******ppppppplVar2;
  undefined8 uVar3;
  long *******ppppppplVar4;
  long *******ppppppplVar5;
  undefined1 auVar6 [16];
  long *******ppppppplStack_38;
  
  ppppppplVar5 = (long *******)(param_1 + 1);
  if ((long *******)*ppppppplVar5 == (long *******)0x0) {
    ppppppplVar4 = (long *******)*ppppppplVar5;
    ppppppplVar2 = ppppppplVar5;
  }
  else {
    ppppppplVar4 = (long *******)*ppppppplVar5;
    do {
      while (ppppppplVar2 = ppppppplVar4, *param_2 < *(uint *)(ppppppplVar2 + 4)) {
        ppppppplVar4 = (long *******)*ppppppplVar2;
        if ((long *******)*ppppppplVar2 == (long *******)0x0) {
          ppppppplVar4 = (long *******)*ppppppplVar2;
          ppppppplVar5 = ppppppplVar2;
          goto joined_r0x0169a0cc;
        }
      }
      if (*param_2 <= *(uint *)(ppppppplVar2 + 4)) {
        ppppppplVar5 = (long *******)&ppppppplStack_38;
        ppppppplVar4 = ppppppplVar2;
        goto joined_r0x0169a0cc;
      }
      ppppppplVar5 = ppppppplVar2 + 1;
      ppppppplVar4 = (long *******)*ppppppplVar5;
    } while ((long *******)*ppppppplVar5 != (long *******)0x0);
    ppppppplVar4 = (long *******)*ppppppplVar5;
  }
joined_r0x0169a0cc:
  if (ppppppplVar4 == (long *******)0x0) {
    ppppppplStack_38 = ppppppplVar2;
    ppppppplVar4 = (long *******)Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(0x40,&UNK_027dc4e5/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Map.h"*/,0x21);
    if (ppppppplVar4 == (long *******)0x0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    }
    uVar1 = *(undefined4 *)*param_4;
    ppppppplVar4[7] = (long ******)0x0;
    *(undefined4 *)(ppppppplVar4 + 4) = uVar1;
    ppppppplVar4[6] = (long ******)0x0;
    *ppppppplVar4 = (long ******)0x0;
    ppppppplVar4[1] = (long ******)0x0;
    ppppppplVar4[2] = (long ******)ppppppplVar2;
    ppppppplVar4[5] = (long ******)(ppppppplVar4 + 6);
    *ppppppplVar5 = (long ******)ppppppplVar4;
    ppppppplVar2 = ppppppplVar4;
    if (*(long *)*param_1 != 0) {
      *param_1 = *(long *)*param_1;
      ppppppplVar2 = (long *******)*ppppppplVar5;
    }
    void std::__ndk1::__tree_balance_after_insert<std::__ndk1::__tree_node_base<void*>*>(std::__ndk1::__tree_node_base<void*>*, std::__ndk1::__tree_node_base<void*>*)(param_1[1],ppppppplVar2);
    uVar3 = 1;
    param_1[2] = param_1[2] + 1;
  }
  else {
    uVar3 = 0;
  }
  auVar6._8_8_ = uVar3;
  auVar6._0_8_ = ppppppplVar4;
  return auVar6;
}

// ==== std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, CMasterCache::tWeaponKind>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, CMasterCache::tWeaponKind>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, CMasterCache::tWeaponKind>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, CMasterCache::tWeaponKind>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, CMasterCache::tWeaponKind>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, std::__ndk1::piecewise_construct_t const&, std::__ndk1::tuple<unsigned int const&>, std::__ndk1::tuple<> >(unsigned int const&, std::__ndk1::piecewise_construct_t const&, std::__ndk1::tuple<unsigned int const&>&&, std::__ndk1::tuple<>&&)
// vaddr 0x159a178 | ghidra 0x169a178 | size 344 | symbol _ZNSt6__ndk16__treeINS_12__value_typeIjN12CMasterCache11tWeaponKindEEENS_19__map_value_compareIjS4_NS_4lessIjEELb1EEEN9Framework13CSTLAllocatorIS4_NS9_19CSTLMapAllocatorInfEEEE25__emplace_unique_key_argsIjJRKNS_21piecewise_construct_tENS_5tupleIJRKjEEENSI_IJEEEEEENS_4pairINS_15__tree_iteratorIS4_PNS_11__tree_nodeIS4_PvEElEEbEERKT_DpOT0_ | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Type propagation algorithm not settling */

undefined1  [16]
_ZNSt6__ndk16__treeINS_12__value_typeIjN12CMasterCache11tWeaponKindEEENS_19__map_value_compareIjS4_NS_4lessIjEELb1EEEN9Framework13CSTLAllocatorIS4_NS9_19CSTLMapAllocatorInfEEEE25__emplace_unique_key_argsIjJRKNS_21piecewise_construct_tENS_5tupleIJRKjEEENSI_IJEEEEEENS_4pairINS_15__tree_iteratorIS4_PNS_11__tree_nodeIS4_PvEElEEbEERKT_DpOT0_
          (long *param_1,uint *param_2,undefined8 param_3,undefined8 *param_4)

{
  undefined4 uVar1;
  long *******ppppppplVar2;
  undefined8 uVar3;
  long *******ppppppplVar4;
  long *******ppppppplVar5;
  undefined1 auVar6 [16];
  long *******ppppppplStack_38;
  
  ppppppplVar5 = (long *******)(param_1 + 1);
  if ((long *******)*ppppppplVar5 == (long *******)0x0) {
    ppppppplVar4 = (long *******)*ppppppplVar5;
    ppppppplVar2 = ppppppplVar5;
  }
  else {
    ppppppplVar4 = (long *******)*ppppppplVar5;
    do {
      while (ppppppplVar2 = ppppppplVar4, *param_2 < *(uint *)(ppppppplVar2 + 4)) {
        ppppppplVar4 = (long *******)*ppppppplVar2;
        if ((long *******)*ppppppplVar2 == (long *******)0x0) {
          ppppppplVar4 = (long *******)*ppppppplVar2;
          ppppppplVar5 = ppppppplVar2;
          goto joined_r0x0169a21c;
        }
      }
      if (*param_2 <= *(uint *)(ppppppplVar2 + 4)) {
        ppppppplVar5 = (long *******)&ppppppplStack_38;
        ppppppplVar4 = ppppppplVar2;
        goto joined_r0x0169a21c;
      }
      ppppppplVar5 = ppppppplVar2 + 1;
      ppppppplVar4 = (long *******)*ppppppplVar5;
    } while ((long *******)*ppppppplVar5 != (long *******)0x0);
    ppppppplVar4 = (long *******)*ppppppplVar5;
  }
joined_r0x0169a21c:
  if (ppppppplVar4 == (long *******)0x0) {
    ppppppplStack_38 = ppppppplVar2;
    ppppppplVar4 = (long *******)Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(0x68,&UNK_027dc4e5/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Map.h"*/,0x21);
    if (ppppppplVar4 == (long *******)0x0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    }
    uVar1 = *(undefined4 *)*param_4;
    *(undefined8 *)((long)ppppppplVar4 + 0x3d) = 0;
    ppppppplVar4[6] = (long ******)0x0;
    ppppppplVar4[7] = (long ******)0x0;
    ppppppplVar4[5] = (long ******)0x0;
    ppppppplVar4[10] = (long ******)0x0;
    ppppppplVar4[0xb] = (long ******)0x0;
    *(undefined1 *)(ppppppplVar4 + 0xc) = 0;
    ppppppplVar4[9] = (long ******)0x0;
    *ppppppplVar4 = (long ******)0x0;
    ppppppplVar4[1] = (long ******)0x0;
    ppppppplVar4[2] = (long ******)ppppppplVar2;
    *(undefined4 *)(ppppppplVar4 + 4) = uVar1;
    *ppppppplVar5 = (long ******)ppppppplVar4;
    ppppppplVar2 = ppppppplVar4;
    if (*(long *)*param_1 != 0) {
      *param_1 = *(long *)*param_1;
      ppppppplVar2 = (long *******)*ppppppplVar5;
    }
    void std::__ndk1::__tree_balance_after_insert<std::__ndk1::__tree_node_base<void*>*>(std::__ndk1::__tree_node_base<void*>*, std::__ndk1::__tree_node_base<void*>*)(param_1[1],ppppppplVar2);
    uVar3 = 1;
    param_1[2] = param_1[2] + 1;
  }
  else {
    uVar3 = 0;
  }
  auVar6._8_8_ = uVar3;
  auVar6._0_8_ = ppppppplVar4;
  return auVar6;
}

// ==== std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, CMasterCache::tWeaponLevelMaxCache2>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, CMasterCache::tWeaponLevelMaxCache2>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, CMasterCache::tWeaponLevelMaxCache2>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, CMasterCache::tWeaponLevelMaxCache2>, void*>*)
// vaddr 0x159a414 | ghidra 0x169a414 | size 84 | symbol _ZNSt6__ndk16__treeINS_12__value_typeIjN12CMasterCache21tWeaponLevelMaxCache2EEENS_19__map_value_compareIjS4_NS_4lessIjEELb1EEEN9Framework13CSTLAllocatorIS4_NS9_19CSTLMapAllocatorInfEEEE7destroyEPNS_11__tree_nodeIS4_PvEE | lib libSOA-3.7.0.so | 2026-10-08
void _ZNSt6__ndk16__treeINS_12__value_typeIjN12CMasterCache21tWeaponLevelMaxCache2EEENS_19__map_value_compareIjS4_NS_4lessIjEELb1EEEN9Framework13CSTLAllocatorIS4_NS9_19CSTLMapAllocatorInfEEEE7destroyEPNS_11__tree_nodeIS4_PvEE
               (undefined8 param_1,undefined8 *param_2)

{
  if (param_2 != (undefined8 *)0x0) {
    std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, CMasterCache::tWeaponLevelMaxCache2>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, CMasterCache::tWeaponLevelMaxCache2>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, CMasterCache::tWeaponLevelMaxCache2>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, CMasterCache::tWeaponLevelMaxCache2>, void*>*)(param_1,*param_2);
    std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, CMasterCache::tWeaponLevelMaxCache2>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, CMasterCache::tWeaponLevelMaxCache2>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, CMasterCache::tWeaponLevelMaxCache2>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, CMasterCache::tWeaponLevelMaxCache2>, void*>*)(param_1,param_2[1]);
    std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, unsigned int>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, unsigned int>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, unsigned int>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, unsigned int>, void*>*)(param_2 + 5,param_2[6]);
    (*(code *)PTR__ZN9Framework37CAssignedMemoryManagerForSTLAllocator4FreeEPv_02ca11c0)(param_2);
    return;
  }
  return;
}

// ==== std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, CMasterCache::tWeaponKind>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, CMasterCache::tWeaponKind>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, CMasterCache::tWeaponKind>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, CMasterCache::tWeaponKind>, void*>*)
// vaddr 0x159a468 | ghidra 0x169a468 | size 104 | symbol _ZNSt6__ndk16__treeINS_12__value_typeIjN12CMasterCache11tWeaponKindEEENS_19__map_value_compareIjS4_NS_4lessIjEELb1EEEN9Framework13CSTLAllocatorIS4_NS9_19CSTLMapAllocatorInfEEEE7destroyEPNS_11__tree_nodeIS4_PvEE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Possible PIC construction at 0x0169a4a0: Changing call to branch */

void _ZNSt6__ndk16__treeINS_12__value_typeIjN12CMasterCache11tWeaponKindEEENS_19__map_value_compareIjS4_NS_4lessIjEELb1EEEN9Framework13CSTLAllocatorIS4_NS9_19CSTLMapAllocatorInfEEEE7destroyEPNS_11__tree_nodeIS4_PvEE
               (undefined8 param_1,undefined8 *param_2)

{
  if (param_2 == (undefined8 *)0x0) {
    return;
  }
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, CMasterCache::tWeaponKind>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, CMasterCache::tWeaponKind>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, CMasterCache::tWeaponKind>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, CMasterCache::tWeaponKind>, void*>*)(param_1,*param_2);
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, CMasterCache::tWeaponKind>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, CMasterCache::tWeaponKind>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, CMasterCache::tWeaponKind>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, CMasterCache::tWeaponKind>, void*>*)(param_1,param_2[1]);
  if ((*(byte *)(param_2 + 9) & 1) == 0) {
    if ((*(byte *)(param_2 + 5) & 1) != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(param_2[7]);
    }
  }
  else {
    param_2 = (undefined8 *)param_2[0xb];
  }
  (*(code *)PTR__ZN9Framework37CAssignedMemoryManagerForSTLAllocator4FreeEPv_02ca11c0)(param_2);
  return;
}

// ==== CMasterManager::CMasterManager()
// vaddr 0x15ab470 | ghidra 0x16ab470 | size 124 | symbol _ZN14CMasterManagerC2Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN14CMasterManagerC1Ev(long *param_1)

{
  undefined *puVar1;
  long lVar2;
  long *plVar3;
  
  Framework::CFiberUnit::CFiberUnit(unsigned int)(param_1,0x600);
  puVar1 = PTR__ZTV14CMasterManager_02cb7e88;
  param_1[9] = 0;
  param_1[10] = 0;
  param_1[7] = 0;
  param_1[8] = 0;
  *(undefined4 *)(param_1 + 0xb) = 0x3f800000;
  *param_1 = (long)(puVar1 + 0x10);
  puVar1 = PTR__ZN9Framework10TSingletonINS_12CApplication9CMainTaskEE11m_pInstanceE_02cc41c8;
  lVar2 = *(long *)
           PTR__ZN9Framework10TSingletonINS_12CApplication9CMainTaskEE11m_pInstanceE_02cc41c8;
  if (lVar2 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar2 = *(long *)puVar1;
  }
  plVar3 = (long *)Framework::CApplication::CMainTask::rRootFiberKernel()(lVar2);
                    /* WARNING: Could not recover jumptable at 0x016ab4e8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*plVar3 + 0x48))(plVar3,param_1);
  return;
}

// ==== CMasterManager::~CMasterManager()
// vaddr 0x15ab4ec | ghidra 0x16ab4ec | size 104 | symbol _ZN14CMasterManagerD1Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN14CMasterManagerD2Ev(long *param_1)

{
  long *plVar1;
  long lVar2;
  
  *param_1 = (long)(PTR__ZTV14CMasterManager_02cb7e88 + 0x10);
  plVar1 = (long *)param_1[9];
  while (plVar1 != (long *)0x0) {
    lVar2 = *plVar1;
    if ((*(byte *)(plVar1 + 2) & 1) != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar1[4]);
    }
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar1);
    plVar1 = (long *)lVar2;
  }
  lVar2 = param_1[7];
  param_1[7] = 0;
  if (lVar2 != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)();
  }
  (*(code *)PTR__ZN9Framework10CFiberUnitD1Ev_02c90ac0)(param_1);
  return;
}

// ==== CMasterManager::~CMasterManager()
// vaddr 0x15ab554 | ghidra 0x16ab554 | size 112 | symbol _ZN14CMasterManagerD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN14CMasterManagerD0Ev(long *param_1)

{
  long *plVar1;
  long lVar2;
  
  *param_1 = (long)(PTR__ZTV14CMasterManager_02cb7e88 + 0x10);
  plVar1 = (long *)param_1[9];
  while (plVar1 != (long *)0x0) {
    lVar2 = *plVar1;
    if ((*(byte *)(plVar1 + 2) & 1) != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar1[4]);
    }
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar1);
    plVar1 = (long *)lVar2;
  }
  lVar2 = param_1[7];
  param_1[7] = 0;
  if (lVar2 != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)();
  }
  Framework::CFiberUnit::~CFiberUnit()(param_1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== CMasterManager::Request(char const*)
// vaddr 0x15ab5c4 | ghidra 0x16ab5c4 | size 1152 | symbol _ZN14CMasterManager7RequestEPKc | lib libSOA-3.7.0.so | 2026-10-08
void _ZN14CMasterManager7RequestEPKc(long param_1)

{
  long *plVar1;
  byte bVar2;
  ulong uVar3;
  ulong uVar4;
  int iVar5;
  long *plVar6;
  ulong uVar7;
  long *plVar8;
  undefined8 *puVar9;
  ulong uVar10;
  ulong uVar11;
  ulong unaff_x26;
  ulong uVar12;
  ulong uVar13;
  float fVar14;
  ulong uStack_a0;
  ulong uStack_98;
  ulong uStack_90;
  long lStack_88;
  byte bStack_78;
  undefined7 uStack_77;
  ulong uStack_70;
  ulong uStack_68;
  undefined1 auStack_58 [8];
  
  CMasterManager::Request(char const*)+0x480(&bStack_78);
  plVar1 = (long *)(param_1 + 0x38);
  plVar6 = (long *)std::__ndk1::__hash_iterator<std::__ndk1::__hash_node<std::__ndk1::__hash_value_type<string, CMasterManager::Status>, void*>*> std::__ndk1::__hash_table<std::__ndk1::__hash_value_type<string, CMasterManager::Status>, std::__ndk1::__unordered_map_hasher<string, std::__ndk1::__hash_value_type<string, CMasterManager::Status>, std::__ndk1::hash<string >, true>, std::__ndk1::__unordered_map_equal<string, std::__ndk1::__hash_value_type<string, CMasterManager::Status>, std::__ndk1::equal_to<string >, true>, Framework::CSTLAllocator<std::__ndk1::__hash_value_type<string, CMasterManager::Status>, Framework::CSTLUnorderedMapAllocatorInf> >::find<string >(string const&)(plVar1,&bStack_78);
  uVar7 = uStack_68;
  if (plVar6 != (long *)0x0) goto code_r0x016aba08;
  uStack_98 = 0;
  uStack_90 = 0;
  uStack_a0 = 0;
  if ((bStack_78 & 1) == 0) {
    uStack_a0 = CONCAT71(uStack_77,bStack_78);
    uStack_90 = uStack_68;
    uStack_98 = uStack_70;
  }
  else {
    if (uStack_70 < 0x17) {
      uVar13 = (ulong)&uStack_a0 | 1;
      uStack_a0 = (uStack_70 & 0x7f) << 1;
      if (uStack_70 != 0) goto code_r0x016ab6b0;
    }
    else {
      uVar11 = uStack_70 + 0x10 & 0xfffffffffffffff0;
      if (uVar11 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
      }
      uVar13 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar11,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
      if (uVar13 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
      }
      uStack_a0 = uVar11 | 1;
      uStack_98 = uStack_70;
      uStack_90 = uVar13;
code_r0x016ab6b0:
      memcpy(uVar13,uVar7,uStack_70);
    }
    *(undefined1 *)(uVar13 + uStack_70) = 0;
  }
  uVar7 = uStack_a0 >> 1 & 0x7f;
  uVar11 = (ulong)&uStack_a0 | 1;
  if ((uStack_a0 & 1) != 0) {
    uVar7 = uStack_98;
    uVar11 = uStack_90;
  }
  lStack_88 = 0;
  uVar7 = std::__ndk1::__murmur2_or_cityhash<unsigned long, 64ul>::operator()(void const*, unsigned long)(auStack_58,uVar11,uVar7);
  uVar11 = *(ulong *)(param_1 + 0x40);
  if (uVar11 != 0) {
    uVar13 = uVar11 - 1;
    if ((uVar13 & uVar11) == 0) {
      unaff_x26 = uVar13 & uVar7;
    }
    else {
      uVar3 = 0;
      if (uVar11 != 0) {
        uVar3 = uVar7 / uVar11;
      }
      unaff_x26 = uVar7 - uVar3 * uVar11;
    }
    puVar9 = *(undefined8 **)(*plVar1 + unaff_x26 * 8);
    if ((puVar9 != (undefined8 *)0x0) && (plVar6 = (long *)*puVar9, plVar6 != (long *)0x0)) {
      uVar12 = uStack_a0 & 0xff;
      uVar3 = (ulong)&uStack_a0 | 1;
      uVar4 = uStack_a0 >> 1 & 0x7f;
      if ((uStack_a0 & 1) != 0) {
        uVar3 = uStack_90;
        uVar4 = uStack_98;
      }
      if ((uVar13 & uVar11) == 0) {
        if (uVar4 == 0) {
          do {
            if ((plVar6[1] & uVar13) != unaff_x26) break;
            uVar3 = (ulong)(*(byte *)(plVar6 + 2) >> 1);
            if ((*(byte *)(plVar6 + 2) & 1) != 0) {
              uVar3 = plVar6[3];
            }
            if (uVar3 == 0) goto code_r0x016ab9fc;
            plVar6 = (long *)*plVar6;
          } while (plVar6 != (long *)0x0);
        }
        else {
          do {
            if ((plVar6[1] & uVar13) != unaff_x26) break;
            bVar2 = *(byte *)(plVar6 + 2);
            uVar10 = (ulong)(bVar2 >> 1);
            if ((bVar2 & 1) != 0) {
              uVar10 = plVar6[3];
            }
            if (uVar10 == uVar4) {
              if ((bVar2 & 1) == 0) {
                uVar10 = 0;
                while (*(char *)((long)plVar6 + uVar10 + 0x11) == *(char *)(uVar3 + uVar10)) {
                  uVar10 = uVar10 + 1;
                  if (bVar2 >> 1 == uVar10) goto code_r0x016ab9fc;
                }
              }
              else {
                iVar5 = memcmp(plVar6[4],uVar3,uVar4);
                if (iVar5 == 0) goto code_r0x016ab9fc;
              }
            }
            plVar6 = (long *)*plVar6;
          } while (plVar6 != (long *)0x0);
        }
      }
      else if (uVar4 == 0) {
        do {
          uVar13 = 0;
          if (uVar11 != 0) {
            uVar13 = (ulong)plVar6[1] / uVar11;
          }
          if (plVar6[1] - uVar13 * uVar11 != unaff_x26) break;
          uVar13 = (ulong)(*(byte *)(plVar6 + 2) >> 1);
          if ((*(byte *)(plVar6 + 2) & 1) != 0) {
            uVar13 = plVar6[3];
          }
          if (uVar13 == 0) goto code_r0x016ab9fc;
          plVar6 = (long *)*plVar6;
        } while (plVar6 != (long *)0x0);
      }
      else {
        do {
          uVar13 = 0;
          if (uVar11 != 0) {
            uVar13 = (ulong)plVar6[1] / uVar11;
          }
          if (plVar6[1] - uVar13 * uVar11 != unaff_x26) break;
          bVar2 = *(byte *)(plVar6 + 2);
          uVar13 = (ulong)(bVar2 >> 1);
          if ((bVar2 & 1) != 0) {
            uVar13 = plVar6[3];
          }
          if (uVar13 == uVar4) {
            if ((bVar2 & 1) == 0) {
              uVar13 = 0;
              while (*(char *)((long)plVar6 + uVar13 + 0x11) == *(char *)(uVar3 + uVar13)) {
                uVar13 = uVar13 + 1;
                if (bVar2 >> 1 == uVar13) goto code_r0x016ab9fc;
              }
            }
            else {
              iVar5 = memcmp(plVar6[4],uVar3,uVar4);
              if (iVar5 == 0) goto code_r0x016ab9fc;
            }
          }
          plVar6 = (long *)*plVar6;
        } while (plVar6 != (long *)0x0);
      }
    }
  }
  plVar6 = (long *)Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(0x30,&UNK_027dc2d5/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_UnorderedMap.h"*/,0x1c);
  if (plVar6 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
  }
  plVar6[4] = uStack_90;
  plVar6[3] = uStack_98;
  plVar6[2] = uStack_a0;
  uStack_98 = 0;
  uStack_90 = 0;
  uStack_a0 = 0;
  *plVar6 = 0;
  plVar6[1] = uVar7;
  plVar6[5] = lStack_88;
  fVar14 = (float)(*(long *)(param_1 + 0x50) + 1);
  if ((uVar11 == 0) || (*(float *)(param_1 + 0x58) * (float)uVar11 < fVar14)) {
    if (uVar11 < 3) {
      uVar13 = 1;
    }
    else {
      uVar13 = (ulong)((uVar11 - 1 & uVar11) != 0);
    }
    uVar13 = uVar13 | uVar11 << 1;
    uVar11 = (ulong)(fVar14 / *(float *)(param_1 + 0x58));
    if (uVar11 <= uVar13) {
      uVar11 = uVar13;
    }
    std::__ndk1::__hash_table<std::__ndk1::__hash_value_type<string, CMasterManager::Status>, std::__ndk1::__unordered_map_hasher<string, std::__ndk1::__hash_value_type<string, CMasterManager::Status>, std::__ndk1::hash<string >, true>, std::__ndk1::__unordered_map_equal<string, std::__ndk1::__hash_value_type<string, CMasterManager::Status>, std::__ndk1::equal_to<string >, true>, Framework::CSTLAllocator<std::__ndk1::__hash_value_type<string, CMasterManager::Status>, Framework::CSTLUnorderedMapAllocatorInf> >::rehash(unsigned long)(plVar1,uVar11);
    uVar11 = *(ulong *)(param_1 + 0x40);
    if ((uVar11 - 1 & uVar11) == 0) {
      unaff_x26 = uVar11 - 1 & uVar7;
    }
    else {
      uVar13 = 0;
      if (uVar11 != 0) {
        uVar13 = uVar7 / uVar11;
      }
      unaff_x26 = uVar7 - uVar13 * uVar11;
    }
  }
  plVar8 = *(long **)(*plVar1 + unaff_x26 * 8);
  if (plVar8 == (long *)0x0) {
    plVar8 = (long *)(param_1 + 0x48);
    *plVar6 = *plVar8;
    *plVar8 = (long)plVar6;
    *(long **)(*(long *)(param_1 + 0x38) + unaff_x26 * 8) = plVar8;
    if (*plVar6 != 0) {
      uVar7 = *(ulong *)(*plVar6 + 8);
      if ((uVar11 - 1 & uVar11) == 0) {
        uVar7 = uVar7 & uVar11 - 1;
      }
      else {
        uVar13 = 0;
        if (uVar11 != 0) {
          uVar13 = uVar7 / uVar11;
        }
        uVar7 = uVar7 - uVar13 * uVar11;
      }
      plVar8 = (long *)(*plVar1 + uVar7 * 8);
      goto code_r0x016ab9e8;
    }
  }
  else {
    *plVar6 = *plVar8;
code_r0x016ab9e8:
    *plVar8 = (long)plVar6;
  }
  *(long *)(param_1 + 0x50) = *(long *)(param_1 + 0x50) + 1;
  uVar12 = uStack_a0 & 0xff;
code_r0x016ab9fc:
  if ((uVar12 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_90);
  }
code_r0x016aba08:
  *(int *)((long)plVar6 + 0x2c) = *(int *)((long)plVar6 + 0x2c) + 1;
  if ((bStack_78 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_68);
  }
  return;
}

// ==== CMasterManager::IsReady(char const*)
// vaddr 0x15ac1dc | ghidra 0x16ac1dc | size 96 | symbol _ZN14CMasterManager7IsReadyEPKc | lib libSOA-3.7.0.so | 2026-10-08
bool _ZN14CMasterManager7IsReadyEPKc(long param_1)

{
  bool bVar1;
  long lVar2;
  byte abStack_28 [16];
  undefined8 uStack_18;
  
  CMasterManager::Request(char const*)+0x480(abStack_28);
  lVar2 = std::__ndk1::__hash_iterator<std::__ndk1::__hash_node<std::__ndk1::__hash_value_type<string, CMasterManager::Status>, void*>*> std::__ndk1::__hash_table<std::__ndk1::__hash_value_type<string, CMasterManager::Status>, std::__ndk1::__unordered_map_hasher<string, std::__ndk1::__hash_value_type<string, CMasterManager::Status>, std::__ndk1::hash<string >, true>, std::__ndk1::__unordered_map_equal<string, std::__ndk1::__hash_value_type<string, CMasterManager::Status>, std::__ndk1::equal_to<string >, true>, Framework::CSTLAllocator<std::__ndk1::__hash_value_type<string, CMasterManager::Status>, Framework::CSTLUnorderedMapAllocatorInf> >::find<string >(string const&)(param_1 + 0x38,abStack_28);
  if (lVar2 == 0) {
    bVar1 = false;
  }
  else {
    bVar1 = *(int *)(lVar2 + 0x28) == 2;
  }
  if ((abStack_28[0] & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_18);
  }
  return bVar1;
}

// ==== CMasterManager::Release(char const*)
// vaddr 0x15ac23c | ghidra 0x16ac23c | size 436 | symbol _ZN14CMasterManager7ReleaseEPKc | lib libSOA-3.7.0.so | 2026-10-08
void _ZN14CMasterManager7ReleaseEPKc(long param_1)

{
  long *plVar1;
  int iVar2;
  int iVar3;
  ulong uVar4;
  undefined *puVar5;
  long *plVar6;
  long *plVar7;
  long lVar8;
  ulong uVar9;
  ulong uVar10;
  ulong uVar11;
  ulong uVar12;
  long *plVar13;
  ulong uVar14;
  byte abStack_38 [16];
  ulong uStack_28;
  
  CMasterManager::Request(char const*)+0x480(abStack_38);
  plVar1 = (long *)(param_1 + 0x38);
  plVar7 = (long *)std::__ndk1::__hash_iterator<std::__ndk1::__hash_node<std::__ndk1::__hash_value_type<string, CMasterManager::Status>, void*>*> std::__ndk1::__hash_table<std::__ndk1::__hash_value_type<string, CMasterManager::Status>, std::__ndk1::__unordered_map_hasher<string, std::__ndk1::__hash_value_type<string, CMasterManager::Status>, std::__ndk1::hash<string >, true>, std::__ndk1::__unordered_map_equal<string, std::__ndk1::__hash_value_type<string, CMasterManager::Status>, std::__ndk1::equal_to<string >, true>, Framework::CSTLAllocator<std::__ndk1::__hash_value_type<string, CMasterManager::Status>, Framework::CSTLUnorderedMapAllocatorInf> >::find<string >(string const&)(plVar1,abStack_38);
  if ((plVar7 == (long *)0x0) ||
     (iVar2 = *(int *)((long)plVar7 + 0x2c), iVar3 = iVar2 + -1,
     *(int *)((long)plVar7 + 0x2c) = iVar3, iVar3 != 0 && 0 < iVar2)) goto code_r0x016ac3c0;
  uVar10 = *(ulong *)(param_1 + 0x40);
  uVar9 = plVar7[1];
  uVar11 = uVar10 - 1;
  uVar12 = uVar11 & uVar10;
  if (uVar12 == 0) {
    uVar9 = uVar11 & uVar9;
  }
  else {
    uVar14 = 0;
    if (uVar10 != 0) {
      uVar14 = uVar9 / uVar10;
    }
    uVar9 = uVar9 - uVar14 * uVar10;
  }
  plVar6 = *(long **)(*plVar1 + uVar9 * 8);
  do {
    plVar13 = plVar6;
    plVar6 = (long *)*plVar13;
  } while ((long *)*plVar13 != plVar7);
  if (plVar13 == (long *)(param_1 + 0x48)) {
code_r0x016ac2dc:
    if (*plVar7 != 0) {
      uVar14 = *(ulong *)(*plVar7 + 8);
      if (uVar12 == 0) {
        uVar14 = uVar14 & uVar11;
      }
      else {
        uVar4 = 0;
        if (uVar10 != 0) {
          uVar4 = uVar14 / uVar10;
        }
        uVar14 = uVar14 - uVar4 * uVar10;
      }
      if (uVar14 == uVar9) goto code_r0x016ac320;
    }
    *(undefined8 *)(*plVar1 + uVar9 * 8) = 0;
  }
  else {
    uVar14 = plVar13[1];
    if (uVar12 == 0) {
      uVar14 = uVar14 & uVar11;
    }
    else {
      uVar4 = 0;
      if (uVar10 != 0) {
        uVar4 = uVar14 / uVar10;
      }
      uVar14 = uVar14 - uVar4 * uVar10;
    }
    if (uVar14 != uVar9) goto code_r0x016ac2dc;
  }
code_r0x016ac320:
  if (*plVar7 != 0) {
    uVar14 = *(ulong *)(*plVar7 + 8);
    if (uVar12 == 0) {
      uVar14 = uVar14 & uVar11;
    }
    else {
      uVar11 = 0;
      if (uVar10 != 0) {
        uVar11 = uVar14 / uVar10;
      }
      uVar14 = uVar14 - uVar11 * uVar10;
    }
    if (uVar14 != uVar9) {
      *(long **)(*plVar1 + uVar14 * 8) = plVar13;
    }
  }
  *plVar13 = *plVar7;
  *plVar7 = 0;
  *(long *)(param_1 + 0x50) = *(long *)(param_1 + 0x50) + -1;
  if ((*(byte *)(plVar7 + 2) & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar7[4]);
  }
  Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar7);
  puVar5 = PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
  lVar8 = *(long *)PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
  if (lVar8 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar8 = *(long *)puVar5;
  }
  uVar9 = (ulong)abStack_38 | 1;
  if ((abStack_38[0] & 1) != 0) {
    uVar9 = uStack_28;
  }
  CParameterManager::ReleaseParameter(char const*)(lVar8,uVar9);
code_r0x016ac3c0:
  if ((abStack_38[0] & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_28);
  }
  return;
}

// ==== CMasterManager::Progress()
// vaddr 0x15ac3f0 | ghidra 0x16ac3f0 | size 672 | symbol _ZN14CMasterManager8ProgressEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN14CMasterManager8ProgressEv(long param_1)

{
  uint uVar1;
  bool bVar2;
  undefined *puVar3;
  int iVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  ulong uVar7;
  long *plVar8;
  long lVar9;
  long lVar10;
  undefined4 uVar11;
  long *plVar12;
  byte abStack_108 [16];
  ulong uStack_f8;
  undefined1 auStack_a0 [40];
  byte abStack_78 [16];
  ulong uStack_68;
  
  puVar3 = PTR__ZN9Framework10TSingletonI20CGameResourceManagerE11m_pInstanceE_02cc2018;
  plVar12 = *(long **)(param_1 + 0x48);
  if (plVar12 != (long *)0x0) {
    do {
      while( true ) {
        if ((int)plVar12[5] != 1) break;
        lVar10 = *(long *)puVar3;
        if (lVar10 == 0) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
          lVar10 = *(long *)puVar3;
        }
        uVar7 = CGameResourceManager::IsLoading() const(lVar10);
        if ((uVar7 & 1) != 0) goto code_r0x016ac668;
        if ((*(byte *)(plVar12 + 2) & 1) == 0) {
          lVar9 = (long)plVar12 + 0x11;
        }
        else {
          lVar9 = plVar12[4];
        }
        CMasterManager::Progress()+0x2a0(abStack_78,lVar9);
        CGameResourceManager::Lock()(lVar10);
        uVar7 = (ulong)abStack_78 | 1;
        if ((abStack_78[0] & 1) != 0) {
          uVar7 = uStack_68;
        }
        plVar8 = (long *)CGameResourceManager::crResourceElementDirectFile(char const*) const(lVar10,uVar7);
        Aska::ASON::ASON()(abStack_108);
        iVar4 = Framework::CFileLoader::Size() const(plVar8);
        uVar1 = iVar4 << 2;
        if (uVar1 < 0x2001) {
          uVar1 = 0x2000;
        }
        lVar9 = Aska::ASON::Init(unsigned int, bool)(abStack_108,uVar1,1);
        if (lVar9 == 0) {
          uVar5 = Framework::CFileLoader::Size() const(plVar8);
          uVar6 = (**(code **)(*plVar8 + 0x50))(plVar8);
          lVar9 = Aska::ASON::DeserializeBinary(void const*, unsigned long)(abStack_108,uVar6,uVar5);
          if (lVar9 == 0) goto code_r0x016ac640;
          lVar9 = *(long *)PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0
          ;
          if (lVar9 == 0) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
            lVar9 = *(long *)
                     PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
          }
          CParameterManager::Deserialize(Aska::ASON::AValue::AMap const*)(lVar9,auStack_a0);
          Aska::ASON::~ASON()(abStack_108);
          CGameResourceManager::Unlock()(lVar10);
          uVar7 = (ulong)abStack_78 | 1;
          if ((abStack_78[0] & 1) != 0) {
            uVar7 = uStack_68;
          }
          CGameResourceManager::RemoveDirectFile(char const*)(lVar10,uVar7);
          bVar2 = false;
          *(undefined4 *)(plVar12 + 5) = 2;
        }
        else {
code_r0x016ac640:
          Aska::ASON::~ASON()(abStack_108);
          CGameResourceManager::Unlock()(lVar10);
          bVar2 = true;
        }
        if ((abStack_78[0] & 1) != 0) {
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_68);
        }
        if (bVar2) {
          return;
        }
code_r0x016ac668:
        plVar12 = (long *)*plVar12;
        if (plVar12 == (long *)0x0) {
          return;
        }
      }
      if ((int)plVar12[5] != 0) goto code_r0x016ac668;
      if ((*(byte *)(plVar12 + 2) & 1) == 0) {
        lVar10 = (long)plVar12 + 0x11;
      }
      else {
        lVar10 = plVar12[4];
      }
      CMasterManager::Progress()+0x2a0(abStack_108,lVar10);
      lVar10 = *(long *)puVar3;
      if (lVar10 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
        lVar10 = *(long *)puVar3;
      }
      uVar7 = (ulong)abStack_108 | 1;
      if ((abStack_108[0] & 1) != 0) {
        uVar7 = uStack_f8;
      }
      uVar7 = CGameResourceManager::IsFileExist(char const*, bool) const(lVar10,uVar7,1);
      if ((uVar7 & 1) == 0) {
        uVar11 = 2;
      }
      else {
        uVar7 = (ulong)abStack_108 | 1;
        if ((abStack_108[0] & 1) != 0) {
          uVar7 = uStack_f8;
        }
        uVar11 = 1;
        CGameResourceManager::AddDirectFile(unsigned int, char const*, unsigned int, bool, CGameResourceManager::iPriorityMode)(lVar10,1,uVar7,0,0,0);
      }
      *(undefined4 *)(plVar12 + 5) = uVar11;
      if ((abStack_108[0] & 1) == 0) goto code_r0x016ac668;
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_f8);
      plVar12 = (long *)*plVar12;
    } while (plVar12 != (long *)0x0);
  }
  return;
}

// ==== CMasterManager::Initialize(CParameterManager*)
// vaddr 0x15acb7c | ghidra 0x16acb7c | size 31652 | symbol _ZN14CMasterManager10InitializeEP17CParameterManager | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Possible PIC construction at 0x016acc44: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016accf8: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016acdb0: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016ace64: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016acf18: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016acfcc: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016ad084: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016ad13c: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016ad1f4: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016ad2ac: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016ad364: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016ad41c: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016ad4d4: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016ad58c: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016ad644: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016ad6fc: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016ad7b4: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016ad86c: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016ad924: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016ad9dc: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016ada94: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016adb4c: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016adc04: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016adcbc: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016add74: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016ade2c: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016adee4: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016adf9c: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016ae054: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016ae10c: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016ae1c4: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016ae27c: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016ae334: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016ae3ec: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016ae4a4: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016ae55c: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016ae614: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016ae6cc: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016ae784: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016ae83c: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016ae8f4: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016ae9a8: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016aea60: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016aeb18: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016aebcc: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016aec84: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016aed3c: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016aedf4: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016aeeac: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016aef64: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016af01c: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016af0d4: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016af18c: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016af244: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016af2fc: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016af3b4: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016af46c: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016af524: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016af5dc: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016af694: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016af74c: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016af804: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016af8bc: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016af974: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016afa2c: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016afae4: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016afb9c: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016afc54: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016afd0c: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016afdc4: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016afe7c: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016aff34: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016affec: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b00a4: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b015c: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b0214: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b02cc: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b0384: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b043c: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b04f4: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b05ac: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b0664: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b071c: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b07d4: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b088c: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b0944: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b09fc: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b0ab4: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b0b6c: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b0c24: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b0cdc: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b0d94: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b0e4c: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b0f04: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b0fbc: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b1074: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b112c: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b11e4: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b1298: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b1350: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b1408: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b14c0: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b1578: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b1630: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b16e8: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b17a0: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b1858: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b1910: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b19c8: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b1a80: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b1b38: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b1bf0: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b1ca8: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b1d60: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b1e18: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b1ed0: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b1f88: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b2040: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b20f8: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b21b0: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b2268: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b2320: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b23d8: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b2490: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b2548: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b2600: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b26b8: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b2770: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b2828: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b28e0: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b2998: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b2a50: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b2b08: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b2bc0: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b2c78: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b2d30: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b2de8: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b2ea0: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b2f58: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b3010: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b30c8: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b3180: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b3238: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b32f0: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b33a8: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b3460: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b3518: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b35d0: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b3688: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b3740: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b37f8: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b38b0: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b3968: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b3a20: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b3ad8: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b3b90: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b3c48: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b3d00: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b3db8: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b3e70: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b3f28: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b3fe0: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b4098: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b4150: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b4208: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b42c0: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b4378: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b4430: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b44e8: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b45a0: Changing call to branch */
/* WARNING: Possible PIC construction at 0x016b4658: Changing call to branch */
/* WARNING: Removing unreachable block (ram,0x016b45a4) */
/* WARNING: Removing unreachable block (ram,0x016b45bc) */
/* WARNING: Removing unreachable block (ram,0x016b4630) */
/* WARNING: Removing unreachable block (ram,0x016b4654) */
/* WARNING: Removing unreachable block (ram,0x016b44ec) */
/* WARNING: Removing unreachable block (ram,0x016b4504) */
/* WARNING: Removing unreachable block (ram,0x016b4578) */
/* WARNING: Removing unreachable block (ram,0x016b459c) */
/* WARNING: Removing unreachable block (ram,0x016b4434) */
/* WARNING: Removing unreachable block (ram,0x016b444c) */
/* WARNING: Removing unreachable block (ram,0x016b44c0) */
/* WARNING: Removing unreachable block (ram,0x016b44e4) */
/* WARNING: Removing unreachable block (ram,0x016b437c) */
/* WARNING: Removing unreachable block (ram,0x016b4394) */
/* WARNING: Removing unreachable block (ram,0x016b4408) */
/* WARNING: Removing unreachable block (ram,0x016b442c) */
/* WARNING: Removing unreachable block (ram,0x016b42c4) */
/* WARNING: Removing unreachable block (ram,0x016b42dc) */
/* WARNING: Removing unreachable block (ram,0x016b4350) */
/* WARNING: Removing unreachable block (ram,0x016b4374) */
/* WARNING: Removing unreachable block (ram,0x016b420c) */
/* WARNING: Removing unreachable block (ram,0x016b4224) */
/* WARNING: Removing unreachable block (ram,0x016b4298) */
/* WARNING: Removing unreachable block (ram,0x016b42bc) */
/* WARNING: Removing unreachable block (ram,0x016b4154) */
/* WARNING: Removing unreachable block (ram,0x016b416c) */
/* WARNING: Removing unreachable block (ram,0x016b41e0) */
/* WARNING: Removing unreachable block (ram,0x016b4204) */
/* WARNING: Removing unreachable block (ram,0x016b409c) */
/* WARNING: Removing unreachable block (ram,0x016b40b4) */
/* WARNING: Removing unreachable block (ram,0x016b4128) */
/* WARNING: Removing unreachable block (ram,0x016b414c) */
/* WARNING: Removing unreachable block (ram,0x016b3fe4) */
/* WARNING: Removing unreachable block (ram,0x016b3ffc) */
/* WARNING: Removing unreachable block (ram,0x016b4070) */
/* WARNING: Removing unreachable block (ram,0x016b4094) */
/* WARNING: Removing unreachable block (ram,0x016b3f2c) */
/* WARNING: Removing unreachable block (ram,0x016b3f44) */
/* WARNING: Removing unreachable block (ram,0x016b3fb8) */
/* WARNING: Removing unreachable block (ram,0x016b3fdc) */
/* WARNING: Removing unreachable block (ram,0x016b3e74) */
/* WARNING: Removing unreachable block (ram,0x016b3e8c) */
/* WARNING: Removing unreachable block (ram,0x016b3f00) */
/* WARNING: Removing unreachable block (ram,0x016b3f24) */
/* WARNING: Removing unreachable block (ram,0x016b3dbc) */
/* WARNING: Removing unreachable block (ram,0x016b3dd4) */
/* WARNING: Removing unreachable block (ram,0x016b3e48) */
/* WARNING: Removing unreachable block (ram,0x016b3e6c) */
/* WARNING: Removing unreachable block (ram,0x016b3d04) */
/* WARNING: Removing unreachable block (ram,0x016b3d1c) */
/* WARNING: Removing unreachable block (ram,0x016b3d90) */
/* WARNING: Removing unreachable block (ram,0x016b3db4) */
/* WARNING: Removing unreachable block (ram,0x016b3c4c) */
/* WARNING: Removing unreachable block (ram,0x016b3c64) */
/* WARNING: Removing unreachable block (ram,0x016b3cd8) */
/* WARNING: Removing unreachable block (ram,0x016b3cfc) */
/* WARNING: Removing unreachable block (ram,0x016b3b94) */
/* WARNING: Removing unreachable block (ram,0x016b3bac) */
/* WARNING: Removing unreachable block (ram,0x016b3c20) */
/* WARNING: Removing unreachable block (ram,0x016b3c44) */
/* WARNING: Removing unreachable block (ram,0x016b3adc) */
/* WARNING: Removing unreachable block (ram,0x016b3af4) */
/* WARNING: Removing unreachable block (ram,0x016b3b68) */
/* WARNING: Removing unreachable block (ram,0x016b3b8c) */
/* WARNING: Removing unreachable block (ram,0x016b3a24) */
/* WARNING: Removing unreachable block (ram,0x016b3a3c) */
/* WARNING: Removing unreachable block (ram,0x016b3ab0) */
/* WARNING: Removing unreachable block (ram,0x016b3ad4) */
/* WARNING: Removing unreachable block (ram,0x016b396c) */
/* WARNING: Removing unreachable block (ram,0x016b3984) */
/* WARNING: Removing unreachable block (ram,0x016b39f8) */
/* WARNING: Removing unreachable block (ram,0x016b3a1c) */
/* WARNING: Removing unreachable block (ram,0x016b38b4) */
/* WARNING: Removing unreachable block (ram,0x016b38cc) */
/* WARNING: Removing unreachable block (ram,0x016b3940) */
/* WARNING: Removing unreachable block (ram,0x016b3964) */
/* WARNING: Removing unreachable block (ram,0x016b37fc) */
/* WARNING: Removing unreachable block (ram,0x016b3814) */
/* WARNING: Removing unreachable block (ram,0x016b3888) */
/* WARNING: Removing unreachable block (ram,0x016b38ac) */
/* WARNING: Removing unreachable block (ram,0x016b3744) */
/* WARNING: Removing unreachable block (ram,0x016b375c) */
/* WARNING: Removing unreachable block (ram,0x016b37d0) */
/* WARNING: Removing unreachable block (ram,0x016b37f4) */
/* WARNING: Removing unreachable block (ram,0x016b368c) */
/* WARNING: Removing unreachable block (ram,0x016b36a4) */
/* WARNING: Removing unreachable block (ram,0x016b3718) */
/* WARNING: Removing unreachable block (ram,0x016b373c) */
/* WARNING: Removing unreachable block (ram,0x016b35d4) */
/* WARNING: Removing unreachable block (ram,0x016b35ec) */
/* WARNING: Removing unreachable block (ram,0x016b3660) */
/* WARNING: Removing unreachable block (ram,0x016b3684) */
/* WARNING: Removing unreachable block (ram,0x016b351c) */
/* WARNING: Removing unreachable block (ram,0x016b3534) */
/* WARNING: Removing unreachable block (ram,0x016b35a8) */
/* WARNING: Removing unreachable block (ram,0x016b35cc) */
/* WARNING: Removing unreachable block (ram,0x016b3464) */
/* WARNING: Removing unreachable block (ram,0x016b347c) */
/* WARNING: Removing unreachable block (ram,0x016b34f0) */
/* WARNING: Removing unreachable block (ram,0x016b3514) */
/* WARNING: Removing unreachable block (ram,0x016b33ac) */
/* WARNING: Removing unreachable block (ram,0x016b33c4) */
/* WARNING: Removing unreachable block (ram,0x016b3438) */
/* WARNING: Removing unreachable block (ram,0x016b345c) */
/* WARNING: Removing unreachable block (ram,0x016b32f4) */
/* WARNING: Removing unreachable block (ram,0x016b330c) */
/* WARNING: Removing unreachable block (ram,0x016b3380) */
/* WARNING: Removing unreachable block (ram,0x016b33a4) */
/* WARNING: Removing unreachable block (ram,0x016b323c) */
/* WARNING: Removing unreachable block (ram,0x016b3254) */
/* WARNING: Removing unreachable block (ram,0x016b32c8) */
/* WARNING: Removing unreachable block (ram,0x016b32ec) */
/* WARNING: Removing unreachable block (ram,0x016b3184) */
/* WARNING: Removing unreachable block (ram,0x016b319c) */
/* WARNING: Removing unreachable block (ram,0x016b3210) */
/* WARNING: Removing unreachable block (ram,0x016b3234) */
/* WARNING: Removing unreachable block (ram,0x016b30cc) */
/* WARNING: Removing unreachable block (ram,0x016b30e4) */
/* WARNING: Removing unreachable block (ram,0x016b3158) */
/* WARNING: Removing unreachable block (ram,0x016b317c) */
/* WARNING: Removing unreachable block (ram,0x016b3014) */
/* WARNING: Removing unreachable block (ram,0x016b302c) */
/* WARNING: Removing unreachable block (ram,0x016b30a0) */
/* WARNING: Removing unreachable block (ram,0x016b30c4) */
/* WARNING: Removing unreachable block (ram,0x016b2f5c) */
/* WARNING: Removing unreachable block (ram,0x016b2f74) */
/* WARNING: Removing unreachable block (ram,0x016b2fe8) */
/* WARNING: Removing unreachable block (ram,0x016b300c) */
/* WARNING: Removing unreachable block (ram,0x016b2ea4) */
/* WARNING: Removing unreachable block (ram,0x016b2ebc) */
/* WARNING: Removing unreachable block (ram,0x016b2f30) */
/* WARNING: Removing unreachable block (ram,0x016b2f54) */
/* WARNING: Removing unreachable block (ram,0x016b2dec) */
/* WARNING: Removing unreachable block (ram,0x016b2e04) */
/* WARNING: Removing unreachable block (ram,0x016b2e78) */
/* WARNING: Removing unreachable block (ram,0x016b2e9c) */
/* WARNING: Removing unreachable block (ram,0x016b2d34) */
/* WARNING: Removing unreachable block (ram,0x016b2d4c) */
/* WARNING: Removing unreachable block (ram,0x016b2dc0) */
/* WARNING: Removing unreachable block (ram,0x016b2de4) */
/* WARNING: Removing unreachable block (ram,0x016b2c7c) */
/* WARNING: Removing unreachable block (ram,0x016b2c94) */
/* WARNING: Removing unreachable block (ram,0x016b2d08) */
/* WARNING: Removing unreachable block (ram,0x016b2d2c) */
/* WARNING: Removing unreachable block (ram,0x016b2bc4) */
/* WARNING: Removing unreachable block (ram,0x016b2bdc) */
/* WARNING: Removing unreachable block (ram,0x016b2c50) */
/* WARNING: Removing unreachable block (ram,0x016b2c74) */
/* WARNING: Removing unreachable block (ram,0x016b2b0c) */
/* WARNING: Removing unreachable block (ram,0x016b2b24) */
/* WARNING: Removing unreachable block (ram,0x016b2b98) */
/* WARNING: Removing unreachable block (ram,0x016b2bbc) */
/* WARNING: Removing unreachable block (ram,0x016b2a54) */
/* WARNING: Removing unreachable block (ram,0x016b2a6c) */
/* WARNING: Removing unreachable block (ram,0x016b2ae0) */
/* WARNING: Removing unreachable block (ram,0x016b2b04) */
/* WARNING: Removing unreachable block (ram,0x016b299c) */
/* WARNING: Removing unreachable block (ram,0x016b29b4) */
/* WARNING: Removing unreachable block (ram,0x016b2a28) */
/* WARNING: Removing unreachable block (ram,0x016b2a4c) */
/* WARNING: Removing unreachable block (ram,0x016b28e4) */
/* WARNING: Removing unreachable block (ram,0x016b28fc) */
/* WARNING: Removing unreachable block (ram,0x016b2970) */
/* WARNING: Removing unreachable block (ram,0x016b2994) */
/* WARNING: Removing unreachable block (ram,0x016b282c) */
/* WARNING: Removing unreachable block (ram,0x016b2844) */
/* WARNING: Removing unreachable block (ram,0x016b28b8) */
/* WARNING: Removing unreachable block (ram,0x016b28dc) */
/* WARNING: Removing unreachable block (ram,0x016b2774) */
/* WARNING: Removing unreachable block (ram,0x016b278c) */
/* WARNING: Removing unreachable block (ram,0x016b2800) */
/* WARNING: Removing unreachable block (ram,0x016b2824) */
/* WARNING: Removing unreachable block (ram,0x016b26bc) */
/* WARNING: Removing unreachable block (ram,0x016b26d4) */
/* WARNING: Removing unreachable block (ram,0x016b2748) */
/* WARNING: Removing unreachable block (ram,0x016b276c) */
/* WARNING: Removing unreachable block (ram,0x016b2604) */
/* WARNING: Removing unreachable block (ram,0x016b261c) */
/* WARNING: Removing unreachable block (ram,0x016b2690) */
/* WARNING: Removing unreachable block (ram,0x016b26b4) */
/* WARNING: Removing unreachable block (ram,0x016b254c) */
/* WARNING: Removing unreachable block (ram,0x016b2564) */
/* WARNING: Removing unreachable block (ram,0x016b25d8) */
/* WARNING: Removing unreachable block (ram,0x016b25fc) */
/* WARNING: Removing unreachable block (ram,0x016b2494) */
/* WARNING: Removing unreachable block (ram,0x016b24ac) */
/* WARNING: Removing unreachable block (ram,0x016b2520) */
/* WARNING: Removing unreachable block (ram,0x016b2544) */
/* WARNING: Removing unreachable block (ram,0x016b23dc) */
/* WARNING: Removing unreachable block (ram,0x016b23f4) */
/* WARNING: Removing unreachable block (ram,0x016b2468) */
/* WARNING: Removing unreachable block (ram,0x016b248c) */
/* WARNING: Removing unreachable block (ram,0x016b2324) */
/* WARNING: Removing unreachable block (ram,0x016b233c) */
/* WARNING: Removing unreachable block (ram,0x016b23b0) */
/* WARNING: Removing unreachable block (ram,0x016b23d4) */
/* WARNING: Removing unreachable block (ram,0x016b226c) */
/* WARNING: Removing unreachable block (ram,0x016b2284) */
/* WARNING: Removing unreachable block (ram,0x016b22f8) */
/* WARNING: Removing unreachable block (ram,0x016b231c) */
/* WARNING: Removing unreachable block (ram,0x016b21b4) */
/* WARNING: Removing unreachable block (ram,0x016b21cc) */
/* WARNING: Removing unreachable block (ram,0x016b2240) */
/* WARNING: Removing unreachable block (ram,0x016b2264) */
/* WARNING: Removing unreachable block (ram,0x016b20fc) */
/* WARNING: Removing unreachable block (ram,0x016b2114) */
/* WARNING: Removing unreachable block (ram,0x016b2188) */
/* WARNING: Removing unreachable block (ram,0x016b21ac) */
/* WARNING: Removing unreachable block (ram,0x016b2044) */
/* WARNING: Removing unreachable block (ram,0x016b205c) */
/* WARNING: Removing unreachable block (ram,0x016b20d0) */
/* WARNING: Removing unreachable block (ram,0x016b20f4) */
/* WARNING: Removing unreachable block (ram,0x016b1f8c) */
/* WARNING: Removing unreachable block (ram,0x016b1fa4) */
/* WARNING: Removing unreachable block (ram,0x016b2018) */
/* WARNING: Removing unreachable block (ram,0x016b203c) */
/* WARNING: Removing unreachable block (ram,0x016b1ed4) */
/* WARNING: Removing unreachable block (ram,0x016b1eec) */
/* WARNING: Removing unreachable block (ram,0x016b1f60) */
/* WARNING: Removing unreachable block (ram,0x016b1f84) */
/* WARNING: Removing unreachable block (ram,0x016b1e1c) */
/* WARNING: Removing unreachable block (ram,0x016b1e34) */
/* WARNING: Removing unreachable block (ram,0x016b1ea8) */
/* WARNING: Removing unreachable block (ram,0x016b1ecc) */
/* WARNING: Removing unreachable block (ram,0x016b1d64) */
/* WARNING: Removing unreachable block (ram,0x016b1d7c) */
/* WARNING: Removing unreachable block (ram,0x016b1df0) */
/* WARNING: Removing unreachable block (ram,0x016b1e14) */
/* WARNING: Removing unreachable block (ram,0x016b1cac) */
/* WARNING: Removing unreachable block (ram,0x016b1cc4) */
/* WARNING: Removing unreachable block (ram,0x016b1d38) */
/* WARNING: Removing unreachable block (ram,0x016b1d5c) */
/* WARNING: Removing unreachable block (ram,0x016b1bf4) */
/* WARNING: Removing unreachable block (ram,0x016b1c0c) */
/* WARNING: Removing unreachable block (ram,0x016b1c80) */
/* WARNING: Removing unreachable block (ram,0x016b1ca4) */
/* WARNING: Removing unreachable block (ram,0x016b1b3c) */
/* WARNING: Removing unreachable block (ram,0x016b1b54) */
/* WARNING: Removing unreachable block (ram,0x016b1bc8) */
/* WARNING: Removing unreachable block (ram,0x016b1bec) */
/* WARNING: Removing unreachable block (ram,0x016b1a84) */
/* WARNING: Removing unreachable block (ram,0x016b1a9c) */
/* WARNING: Removing unreachable block (ram,0x016b1b10) */
/* WARNING: Removing unreachable block (ram,0x016b1b34) */
/* WARNING: Removing unreachable block (ram,0x016b19cc) */
/* WARNING: Removing unreachable block (ram,0x016b19e4) */
/* WARNING: Removing unreachable block (ram,0x016b1a58) */
/* WARNING: Removing unreachable block (ram,0x016b1a7c) */
/* WARNING: Removing unreachable block (ram,0x016b1914) */
/* WARNING: Removing unreachable block (ram,0x016b192c) */
/* WARNING: Removing unreachable block (ram,0x016b19a0) */
/* WARNING: Removing unreachable block (ram,0x016b19c4) */
/* WARNING: Removing unreachable block (ram,0x016b185c) */
/* WARNING: Removing unreachable block (ram,0x016b1874) */
/* WARNING: Removing unreachable block (ram,0x016b18e8) */
/* WARNING: Removing unreachable block (ram,0x016b190c) */
/* WARNING: Removing unreachable block (ram,0x016b17a4) */
/* WARNING: Removing unreachable block (ram,0x016b17bc) */
/* WARNING: Removing unreachable block (ram,0x016b1830) */
/* WARNING: Removing unreachable block (ram,0x016b1854) */
/* WARNING: Removing unreachable block (ram,0x016b16ec) */
/* WARNING: Removing unreachable block (ram,0x016b1704) */
/* WARNING: Removing unreachable block (ram,0x016b1778) */
/* WARNING: Removing unreachable block (ram,0x016b179c) */
/* WARNING: Removing unreachable block (ram,0x016b1634) */
/* WARNING: Removing unreachable block (ram,0x016b164c) */
/* WARNING: Removing unreachable block (ram,0x016b16c0) */
/* WARNING: Removing unreachable block (ram,0x016b16e4) */
/* WARNING: Removing unreachable block (ram,0x016b157c) */
/* WARNING: Removing unreachable block (ram,0x016b1594) */
/* WARNING: Removing unreachable block (ram,0x016b1608) */
/* WARNING: Removing unreachable block (ram,0x016b162c) */
/* WARNING: Removing unreachable block (ram,0x016b14c4) */
/* WARNING: Removing unreachable block (ram,0x016b14dc) */
/* WARNING: Removing unreachable block (ram,0x016b1550) */
/* WARNING: Removing unreachable block (ram,0x016b1574) */
/* WARNING: Removing unreachable block (ram,0x016b140c) */
/* WARNING: Removing unreachable block (ram,0x016b1424) */
/* WARNING: Removing unreachable block (ram,0x016b1498) */
/* WARNING: Removing unreachable block (ram,0x016b14bc) */
/* WARNING: Removing unreachable block (ram,0x016b1354) */
/* WARNING: Removing unreachable block (ram,0x016b136c) */
/* WARNING: Removing unreachable block (ram,0x016b13e0) */
/* WARNING: Removing unreachable block (ram,0x016b1404) */
/* WARNING: Removing unreachable block (ram,0x016b129c) */
/* WARNING: Removing unreachable block (ram,0x016b12b4) */
/* WARNING: Removing unreachable block (ram,0x016b1328) */
/* WARNING: Removing unreachable block (ram,0x016b134c) */
/* WARNING: Removing unreachable block (ram,0x016b11e8) */
/* WARNING: Removing unreachable block (ram,0x016b1200) */
/* WARNING: Removing unreachable block (ram,0x016b1270) */
/* WARNING: Removing unreachable block (ram,0x016b1294) */
/* WARNING: Removing unreachable block (ram,0x016b1130) */
/* WARNING: Removing unreachable block (ram,0x016b1148) */
/* WARNING: Removing unreachable block (ram,0x016b11bc) */
/* WARNING: Removing unreachable block (ram,0x016b11e0) */
/* WARNING: Removing unreachable block (ram,0x016b1078) */
/* WARNING: Removing unreachable block (ram,0x016b1090) */
/* WARNING: Removing unreachable block (ram,0x016b1104) */
/* WARNING: Removing unreachable block (ram,0x016b1128) */
/* WARNING: Removing unreachable block (ram,0x016b0fc0) */
/* WARNING: Removing unreachable block (ram,0x016b0fd8) */
/* WARNING: Removing unreachable block (ram,0x016b104c) */
/* WARNING: Removing unreachable block (ram,0x016b1070) */
/* WARNING: Removing unreachable block (ram,0x016b0f08) */
/* WARNING: Removing unreachable block (ram,0x016b0f20) */
/* WARNING: Removing unreachable block (ram,0x016b0f94) */
/* WARNING: Removing unreachable block (ram,0x016b0fb8) */
/* WARNING: Removing unreachable block (ram,0x016b0e50) */
/* WARNING: Removing unreachable block (ram,0x016b0e68) */
/* WARNING: Removing unreachable block (ram,0x016b0edc) */
/* WARNING: Removing unreachable block (ram,0x016b0f00) */
/* WARNING: Removing unreachable block (ram,0x016b0d98) */
/* WARNING: Removing unreachable block (ram,0x016b0db0) */
/* WARNING: Removing unreachable block (ram,0x016b0e24) */
/* WARNING: Removing unreachable block (ram,0x016b0e48) */
/* WARNING: Removing unreachable block (ram,0x016b0ce0) */
/* WARNING: Removing unreachable block (ram,0x016b0cf8) */
/* WARNING: Removing unreachable block (ram,0x016b0d6c) */
/* WARNING: Removing unreachable block (ram,0x016b0d90) */
/* WARNING: Removing unreachable block (ram,0x016b0c28) */
/* WARNING: Removing unreachable block (ram,0x016b0c40) */
/* WARNING: Removing unreachable block (ram,0x016b0cb4) */
/* WARNING: Removing unreachable block (ram,0x016b0cd8) */
/* WARNING: Removing unreachable block (ram,0x016b0b70) */
/* WARNING: Removing unreachable block (ram,0x016b0b88) */
/* WARNING: Removing unreachable block (ram,0x016b0bfc) */
/* WARNING: Removing unreachable block (ram,0x016b0c20) */
/* WARNING: Removing unreachable block (ram,0x016b0ab8) */
/* WARNING: Removing unreachable block (ram,0x016b0ad0) */
/* WARNING: Removing unreachable block (ram,0x016b0b44) */
/* WARNING: Removing unreachable block (ram,0x016b0b68) */
/* WARNING: Removing unreachable block (ram,0x016b0a00) */
/* WARNING: Removing unreachable block (ram,0x016b0a18) */
/* WARNING: Removing unreachable block (ram,0x016b0a8c) */
/* WARNING: Removing unreachable block (ram,0x016b0ab0) */
/* WARNING: Removing unreachable block (ram,0x016b0948) */
/* WARNING: Removing unreachable block (ram,0x016b0960) */
/* WARNING: Removing unreachable block (ram,0x016b09d4) */
/* WARNING: Removing unreachable block (ram,0x016b09f8) */
/* WARNING: Removing unreachable block (ram,0x016b0890) */
/* WARNING: Removing unreachable block (ram,0x016b08a8) */
/* WARNING: Removing unreachable block (ram,0x016b091c) */
/* WARNING: Removing unreachable block (ram,0x016b0940) */
/* WARNING: Removing unreachable block (ram,0x016b07d8) */
/* WARNING: Removing unreachable block (ram,0x016b07f0) */
/* WARNING: Removing unreachable block (ram,0x016b0864) */
/* WARNING: Removing unreachable block (ram,0x016b0888) */
/* WARNING: Removing unreachable block (ram,0x016b0720) */
/* WARNING: Removing unreachable block (ram,0x016b0738) */
/* WARNING: Removing unreachable block (ram,0x016b07ac) */
/* WARNING: Removing unreachable block (ram,0x016b07d0) */
/* WARNING: Removing unreachable block (ram,0x016b0668) */
/* WARNING: Removing unreachable block (ram,0x016b0680) */
/* WARNING: Removing unreachable block (ram,0x016b06f4) */
/* WARNING: Removing unreachable block (ram,0x016b0718) */
/* WARNING: Removing unreachable block (ram,0x016b05b0) */
/* WARNING: Removing unreachable block (ram,0x016b05c8) */
/* WARNING: Removing unreachable block (ram,0x016b063c) */
/* WARNING: Removing unreachable block (ram,0x016b0660) */
/* WARNING: Removing unreachable block (ram,0x016b04f8) */
/* WARNING: Removing unreachable block (ram,0x016b0510) */
/* WARNING: Removing unreachable block (ram,0x016b0584) */
/* WARNING: Removing unreachable block (ram,0x016b05a8) */
/* WARNING: Removing unreachable block (ram,0x016b0440) */
/* WARNING: Removing unreachable block (ram,0x016b0458) */
/* WARNING: Removing unreachable block (ram,0x016b04cc) */
/* WARNING: Removing unreachable block (ram,0x016b04f0) */
/* WARNING: Removing unreachable block (ram,0x016b0388) */
/* WARNING: Removing unreachable block (ram,0x016b03a0) */
/* WARNING: Removing unreachable block (ram,0x016b0414) */
/* WARNING: Removing unreachable block (ram,0x016b0438) */
/* WARNING: Removing unreachable block (ram,0x016b02d0) */
/* WARNING: Removing unreachable block (ram,0x016b02e8) */
/* WARNING: Removing unreachable block (ram,0x016b035c) */
/* WARNING: Removing unreachable block (ram,0x016b0380) */
/* WARNING: Removing unreachable block (ram,0x016b0218) */
/* WARNING: Removing unreachable block (ram,0x016b0230) */
/* WARNING: Removing unreachable block (ram,0x016b02a4) */
/* WARNING: Removing unreachable block (ram,0x016b02c8) */
/* WARNING: Removing unreachable block (ram,0x016b0160) */
/* WARNING: Removing unreachable block (ram,0x016b0178) */
/* WARNING: Removing unreachable block (ram,0x016b01ec) */
/* WARNING: Removing unreachable block (ram,0x016b0210) */
/* WARNING: Removing unreachable block (ram,0x016b00a8) */
/* WARNING: Removing unreachable block (ram,0x016b00c0) */
/* WARNING: Removing unreachable block (ram,0x016b0134) */
/* WARNING: Removing unreachable block (ram,0x016b0158) */
/* WARNING: Removing unreachable block (ram,0x016afff0) */
/* WARNING: Removing unreachable block (ram,0x016b0008) */
/* WARNING: Removing unreachable block (ram,0x016b007c) */
/* WARNING: Removing unreachable block (ram,0x016b00a0) */
/* WARNING: Removing unreachable block (ram,0x016aff38) */
/* WARNING: Removing unreachable block (ram,0x016aff50) */
/* WARNING: Removing unreachable block (ram,0x016affc4) */
/* WARNING: Removing unreachable block (ram,0x016affe8) */
/* WARNING: Removing unreachable block (ram,0x016afe80) */
/* WARNING: Removing unreachable block (ram,0x016afe98) */
/* WARNING: Removing unreachable block (ram,0x016aff0c) */
/* WARNING: Removing unreachable block (ram,0x016aff30) */
/* WARNING: Removing unreachable block (ram,0x016afdc8) */
/* WARNING: Removing unreachable block (ram,0x016afde0) */
/* WARNING: Removing unreachable block (ram,0x016afe54) */
/* WARNING: Removing unreachable block (ram,0x016afe78) */
/* WARNING: Removing unreachable block (ram,0x016afd10) */
/* WARNING: Removing unreachable block (ram,0x016afd28) */
/* WARNING: Removing unreachable block (ram,0x016afd9c) */
/* WARNING: Removing unreachable block (ram,0x016afdc0) */
/* WARNING: Removing unreachable block (ram,0x016afc58) */
/* WARNING: Removing unreachable block (ram,0x016afc70) */
/* WARNING: Removing unreachable block (ram,0x016afce4) */
/* WARNING: Removing unreachable block (ram,0x016afd08) */
/* WARNING: Removing unreachable block (ram,0x016afba0) */
/* WARNING: Removing unreachable block (ram,0x016afbb8) */
/* WARNING: Removing unreachable block (ram,0x016afc2c) */
/* WARNING: Removing unreachable block (ram,0x016afc50) */
/* WARNING: Removing unreachable block (ram,0x016afae8) */
/* WARNING: Removing unreachable block (ram,0x016afb00) */
/* WARNING: Removing unreachable block (ram,0x016afb74) */
/* WARNING: Removing unreachable block (ram,0x016afb98) */
/* WARNING: Removing unreachable block (ram,0x016afa30) */
/* WARNING: Removing unreachable block (ram,0x016afa48) */
/* WARNING: Removing unreachable block (ram,0x016afabc) */
/* WARNING: Removing unreachable block (ram,0x016afae0) */
/* WARNING: Removing unreachable block (ram,0x016af978) */
/* WARNING: Removing unreachable block (ram,0x016af990) */
/* WARNING: Removing unreachable block (ram,0x016afa04) */
/* WARNING: Removing unreachable block (ram,0x016afa28) */
/* WARNING: Removing unreachable block (ram,0x016af8c0) */
/* WARNING: Removing unreachable block (ram,0x016af8d8) */
/* WARNING: Removing unreachable block (ram,0x016af94c) */
/* WARNING: Removing unreachable block (ram,0x016af970) */
/* WARNING: Removing unreachable block (ram,0x016af808) */
/* WARNING: Removing unreachable block (ram,0x016af820) */
/* WARNING: Removing unreachable block (ram,0x016af894) */
/* WARNING: Removing unreachable block (ram,0x016af8b8) */
/* WARNING: Removing unreachable block (ram,0x016af750) */
/* WARNING: Removing unreachable block (ram,0x016af768) */
/* WARNING: Removing unreachable block (ram,0x016af7dc) */
/* WARNING: Removing unreachable block (ram,0x016af800) */
/* WARNING: Removing unreachable block (ram,0x016af698) */
/* WARNING: Removing unreachable block (ram,0x016af6b0) */
/* WARNING: Removing unreachable block (ram,0x016af724) */
/* WARNING: Removing unreachable block (ram,0x016af748) */
/* WARNING: Removing unreachable block (ram,0x016af5e0) */
/* WARNING: Removing unreachable block (ram,0x016af5f8) */
/* WARNING: Removing unreachable block (ram,0x016af66c) */
/* WARNING: Removing unreachable block (ram,0x016af690) */
/* WARNING: Removing unreachable block (ram,0x016af528) */
/* WARNING: Removing unreachable block (ram,0x016af540) */
/* WARNING: Removing unreachable block (ram,0x016af5b4) */
/* WARNING: Removing unreachable block (ram,0x016af5d8) */
/* WARNING: Removing unreachable block (ram,0x016af470) */
/* WARNING: Removing unreachable block (ram,0x016af488) */
/* WARNING: Removing unreachable block (ram,0x016af4fc) */
/* WARNING: Removing unreachable block (ram,0x016af520) */
/* WARNING: Removing unreachable block (ram,0x016af3b8) */
/* WARNING: Removing unreachable block (ram,0x016af3d0) */
/* WARNING: Removing unreachable block (ram,0x016af444) */
/* WARNING: Removing unreachable block (ram,0x016af468) */
/* WARNING: Removing unreachable block (ram,0x016af300) */
/* WARNING: Removing unreachable block (ram,0x016af318) */
/* WARNING: Removing unreachable block (ram,0x016af38c) */
/* WARNING: Removing unreachable block (ram,0x016af3b0) */
/* WARNING: Removing unreachable block (ram,0x016af248) */
/* WARNING: Removing unreachable block (ram,0x016af260) */
/* WARNING: Removing unreachable block (ram,0x016af2d4) */
/* WARNING: Removing unreachable block (ram,0x016af2f8) */
/* WARNING: Removing unreachable block (ram,0x016af190) */
/* WARNING: Removing unreachable block (ram,0x016af1a8) */
/* WARNING: Removing unreachable block (ram,0x016af21c) */
/* WARNING: Removing unreachable block (ram,0x016af240) */
/* WARNING: Removing unreachable block (ram,0x016af0d8) */
/* WARNING: Removing unreachable block (ram,0x016af0f0) */
/* WARNING: Removing unreachable block (ram,0x016af164) */
/* WARNING: Removing unreachable block (ram,0x016af188) */
/* WARNING: Removing unreachable block (ram,0x016af020) */
/* WARNING: Removing unreachable block (ram,0x016af038) */
/* WARNING: Removing unreachable block (ram,0x016af0ac) */
/* WARNING: Removing unreachable block (ram,0x016af0d0) */
/* WARNING: Removing unreachable block (ram,0x016aef68) */
/* WARNING: Removing unreachable block (ram,0x016aef80) */
/* WARNING: Removing unreachable block (ram,0x016aeff4) */
/* WARNING: Removing unreachable block (ram,0x016af018) */
/* WARNING: Removing unreachable block (ram,0x016aeeb0) */
/* WARNING: Removing unreachable block (ram,0x016aeec8) */
/* WARNING: Removing unreachable block (ram,0x016aef3c) */
/* WARNING: Removing unreachable block (ram,0x016aef60) */
/* WARNING: Removing unreachable block (ram,0x016aedf8) */
/* WARNING: Removing unreachable block (ram,0x016aee10) */
/* WARNING: Removing unreachable block (ram,0x016aee84) */
/* WARNING: Removing unreachable block (ram,0x016aeea8) */
/* WARNING: Removing unreachable block (ram,0x016aed40) */
/* WARNING: Removing unreachable block (ram,0x016aed58) */
/* WARNING: Removing unreachable block (ram,0x016aedcc) */
/* WARNING: Removing unreachable block (ram,0x016aedf0) */
/* WARNING: Removing unreachable block (ram,0x016aec88) */
/* WARNING: Removing unreachable block (ram,0x016aeca0) */
/* WARNING: Removing unreachable block (ram,0x016aed14) */
/* WARNING: Removing unreachable block (ram,0x016aed38) */
/* WARNING: Removing unreachable block (ram,0x016aebd0) */
/* WARNING: Removing unreachable block (ram,0x016aebe8) */
/* WARNING: Removing unreachable block (ram,0x016aec5c) */
/* WARNING: Removing unreachable block (ram,0x016aec80) */
/* WARNING: Removing unreachable block (ram,0x016aeb1c) */
/* WARNING: Removing unreachable block (ram,0x016aeb34) */
/* WARNING: Removing unreachable block (ram,0x016aeba4) */
/* WARNING: Removing unreachable block (ram,0x016aebc8) */
/* WARNING: Removing unreachable block (ram,0x016aea64) */
/* WARNING: Removing unreachable block (ram,0x016aea7c) */
/* WARNING: Removing unreachable block (ram,0x016aeaf0) */
/* WARNING: Removing unreachable block (ram,0x016aeb14) */
/* WARNING: Removing unreachable block (ram,0x016ae9ac) */
/* WARNING: Removing unreachable block (ram,0x016ae9c4) */
/* WARNING: Removing unreachable block (ram,0x016aea38) */
/* WARNING: Removing unreachable block (ram,0x016aea5c) */
/* WARNING: Removing unreachable block (ram,0x016ae8f8) */
/* WARNING: Removing unreachable block (ram,0x016ae910) */
/* WARNING: Removing unreachable block (ram,0x016ae980) */
/* WARNING: Removing unreachable block (ram,0x016ae9a4) */
/* WARNING: Removing unreachable block (ram,0x016ae840) */
/* WARNING: Removing unreachable block (ram,0x016ae858) */
/* WARNING: Removing unreachable block (ram,0x016ae8cc) */
/* WARNING: Removing unreachable block (ram,0x016ae8f0) */
/* WARNING: Removing unreachable block (ram,0x016ae788) */
/* WARNING: Removing unreachable block (ram,0x016ae7a0) */
/* WARNING: Removing unreachable block (ram,0x016ae814) */
/* WARNING: Removing unreachable block (ram,0x016ae838) */
/* WARNING: Removing unreachable block (ram,0x016ae6d0) */
/* WARNING: Removing unreachable block (ram,0x016ae6e8) */
/* WARNING: Removing unreachable block (ram,0x016ae75c) */
/* WARNING: Removing unreachable block (ram,0x016ae780) */
/* WARNING: Removing unreachable block (ram,0x016ae618) */
/* WARNING: Removing unreachable block (ram,0x016ae630) */
/* WARNING: Removing unreachable block (ram,0x016ae6a4) */
/* WARNING: Removing unreachable block (ram,0x016ae6c8) */
/* WARNING: Removing unreachable block (ram,0x016ae560) */
/* WARNING: Removing unreachable block (ram,0x016ae578) */
/* WARNING: Removing unreachable block (ram,0x016ae5ec) */
/* WARNING: Removing unreachable block (ram,0x016ae610) */
/* WARNING: Removing unreachable block (ram,0x016ae4a8) */
/* WARNING: Removing unreachable block (ram,0x016ae4c0) */
/* WARNING: Removing unreachable block (ram,0x016ae534) */
/* WARNING: Removing unreachable block (ram,0x016ae558) */
/* WARNING: Removing unreachable block (ram,0x016ae3f0) */
/* WARNING: Removing unreachable block (ram,0x016ae408) */
/* WARNING: Removing unreachable block (ram,0x016ae47c) */
/* WARNING: Removing unreachable block (ram,0x016ae4a0) */
/* WARNING: Removing unreachable block (ram,0x016ae338) */
/* WARNING: Removing unreachable block (ram,0x016ae350) */
/* WARNING: Removing unreachable block (ram,0x016ae3c4) */
/* WARNING: Removing unreachable block (ram,0x016ae3e8) */
/* WARNING: Removing unreachable block (ram,0x016ae280) */
/* WARNING: Removing unreachable block (ram,0x016ae298) */
/* WARNING: Removing unreachable block (ram,0x016ae30c) */
/* WARNING: Removing unreachable block (ram,0x016ae330) */
/* WARNING: Removing unreachable block (ram,0x016ae1c8) */
/* WARNING: Removing unreachable block (ram,0x016ae1e0) */
/* WARNING: Removing unreachable block (ram,0x016ae254) */
/* WARNING: Removing unreachable block (ram,0x016ae278) */
/* WARNING: Removing unreachable block (ram,0x016ae110) */
/* WARNING: Removing unreachable block (ram,0x016ae128) */
/* WARNING: Removing unreachable block (ram,0x016ae19c) */
/* WARNING: Removing unreachable block (ram,0x016ae1c0) */
/* WARNING: Removing unreachable block (ram,0x016ae058) */
/* WARNING: Removing unreachable block (ram,0x016ae070) */
/* WARNING: Removing unreachable block (ram,0x016ae0e4) */
/* WARNING: Removing unreachable block (ram,0x016ae108) */
/* WARNING: Removing unreachable block (ram,0x016adfa0) */
/* WARNING: Removing unreachable block (ram,0x016adfb8) */
/* WARNING: Removing unreachable block (ram,0x016ae02c) */
/* WARNING: Removing unreachable block (ram,0x016ae050) */
/* WARNING: Removing unreachable block (ram,0x016adee8) */
/* WARNING: Removing unreachable block (ram,0x016adf00) */
/* WARNING: Removing unreachable block (ram,0x016adf74) */
/* WARNING: Removing unreachable block (ram,0x016adf98) */
/* WARNING: Removing unreachable block (ram,0x016ade30) */
/* WARNING: Removing unreachable block (ram,0x016ade48) */
/* WARNING: Removing unreachable block (ram,0x016adebc) */
/* WARNING: Removing unreachable block (ram,0x016adee0) */
/* WARNING: Removing unreachable block (ram,0x016add78) */
/* WARNING: Removing unreachable block (ram,0x016add90) */
/* WARNING: Removing unreachable block (ram,0x016ade04) */
/* WARNING: Removing unreachable block (ram,0x016ade28) */
/* WARNING: Removing unreachable block (ram,0x016adcc0) */
/* WARNING: Removing unreachable block (ram,0x016adcd8) */
/* WARNING: Removing unreachable block (ram,0x016add4c) */
/* WARNING: Removing unreachable block (ram,0x016add70) */
/* WARNING: Removing unreachable block (ram,0x016adc08) */
/* WARNING: Removing unreachable block (ram,0x016adc20) */
/* WARNING: Removing unreachable block (ram,0x016adc94) */
/* WARNING: Removing unreachable block (ram,0x016adcb8) */
/* WARNING: Removing unreachable block (ram,0x016adb50) */
/* WARNING: Removing unreachable block (ram,0x016adb68) */
/* WARNING: Removing unreachable block (ram,0x016adbdc) */
/* WARNING: Removing unreachable block (ram,0x016adc00) */
/* WARNING: Removing unreachable block (ram,0x016ada98) */
/* WARNING: Removing unreachable block (ram,0x016adab0) */
/* WARNING: Removing unreachable block (ram,0x016adb24) */
/* WARNING: Removing unreachable block (ram,0x016adb48) */
/* WARNING: Removing unreachable block (ram,0x016ad9e0) */
/* WARNING: Removing unreachable block (ram,0x016ad9f8) */
/* WARNING: Removing unreachable block (ram,0x016ada6c) */
/* WARNING: Removing unreachable block (ram,0x016ada90) */
/* WARNING: Removing unreachable block (ram,0x016ad928) */
/* WARNING: Removing unreachable block (ram,0x016ad940) */
/* WARNING: Removing unreachable block (ram,0x016ad9b4) */
/* WARNING: Removing unreachable block (ram,0x016ad9d8) */
/* WARNING: Removing unreachable block (ram,0x016ad870) */
/* WARNING: Removing unreachable block (ram,0x016ad888) */
/* WARNING: Removing unreachable block (ram,0x016ad8fc) */
/* WARNING: Removing unreachable block (ram,0x016ad920) */
/* WARNING: Removing unreachable block (ram,0x016ad7b8) */
/* WARNING: Removing unreachable block (ram,0x016ad7d0) */
/* WARNING: Removing unreachable block (ram,0x016ad844) */
/* WARNING: Removing unreachable block (ram,0x016ad868) */
/* WARNING: Removing unreachable block (ram,0x016ad700) */
/* WARNING: Removing unreachable block (ram,0x016ad718) */
/* WARNING: Removing unreachable block (ram,0x016ad78c) */
/* WARNING: Removing unreachable block (ram,0x016ad7b0) */
/* WARNING: Removing unreachable block (ram,0x016ad648) */
/* WARNING: Removing unreachable block (ram,0x016ad660) */
/* WARNING: Removing unreachable block (ram,0x016ad6d4) */
/* WARNING: Removing unreachable block (ram,0x016ad6f8) */
/* WARNING: Removing unreachable block (ram,0x016ad590) */
/* WARNING: Removing unreachable block (ram,0x016ad5a8) */
/* WARNING: Removing unreachable block (ram,0x016ad61c) */
/* WARNING: Removing unreachable block (ram,0x016ad640) */
/* WARNING: Removing unreachable block (ram,0x016ad4d8) */
/* WARNING: Removing unreachable block (ram,0x016ad4f0) */
/* WARNING: Removing unreachable block (ram,0x016ad564) */
/* WARNING: Removing unreachable block (ram,0x016ad588) */
/* WARNING: Removing unreachable block (ram,0x016ad420) */
/* WARNING: Removing unreachable block (ram,0x016ad438) */
/* WARNING: Removing unreachable block (ram,0x016ad4ac) */
/* WARNING: Removing unreachable block (ram,0x016ad4d0) */
/* WARNING: Removing unreachable block (ram,0x016ad368) */
/* WARNING: Removing unreachable block (ram,0x016ad380) */
/* WARNING: Removing unreachable block (ram,0x016ad3f4) */
/* WARNING: Removing unreachable block (ram,0x016ad418) */
/* WARNING: Removing unreachable block (ram,0x016ad2b0) */
/* WARNING: Removing unreachable block (ram,0x016ad2c8) */
/* WARNING: Removing unreachable block (ram,0x016ad33c) */
/* WARNING: Removing unreachable block (ram,0x016ad360) */
/* WARNING: Removing unreachable block (ram,0x016ad1f8) */
/* WARNING: Removing unreachable block (ram,0x016ad210) */
/* WARNING: Removing unreachable block (ram,0x016ad284) */
/* WARNING: Removing unreachable block (ram,0x016ad2a8) */
/* WARNING: Removing unreachable block (ram,0x016ad140) */
/* WARNING: Removing unreachable block (ram,0x016ad158) */
/* WARNING: Removing unreachable block (ram,0x016ad1cc) */
/* WARNING: Removing unreachable block (ram,0x016ad1f0) */
/* WARNING: Removing unreachable block (ram,0x016ad088) */
/* WARNING: Removing unreachable block (ram,0x016ad0a0) */
/* WARNING: Removing unreachable block (ram,0x016ad114) */
/* WARNING: Removing unreachable block (ram,0x016ad138) */
/* WARNING: Removing unreachable block (ram,0x016acfd0) */
/* WARNING: Removing unreachable block (ram,0x016acfe8) */
/* WARNING: Removing unreachable block (ram,0x016ad05c) */
/* WARNING: Removing unreachable block (ram,0x016ad080) */
/* WARNING: Removing unreachable block (ram,0x016acf1c) */
/* WARNING: Removing unreachable block (ram,0x016acf34) */
/* WARNING: Removing unreachable block (ram,0x016acfa4) */
/* WARNING: Removing unreachable block (ram,0x016acfc8) */
/* WARNING: Removing unreachable block (ram,0x016ace68) */
/* WARNING: Removing unreachable block (ram,0x016ace80) */
/* WARNING: Removing unreachable block (ram,0x016acef0) */
/* WARNING: Removing unreachable block (ram,0x016acf14) */
/* WARNING: Removing unreachable block (ram,0x016acdb4) */
/* WARNING: Removing unreachable block (ram,0x016acdcc) */
/* WARNING: Removing unreachable block (ram,0x016ace3c) */
/* WARNING: Removing unreachable block (ram,0x016ace60) */
/* WARNING: Removing unreachable block (ram,0x016accfc) */
/* WARNING: Removing unreachable block (ram,0x016acd14) */
/* WARNING: Removing unreachable block (ram,0x016acd88) */
/* WARNING: Removing unreachable block (ram,0x016acdac) */
/* WARNING: Removing unreachable block (ram,0x016acc48) */
/* WARNING: Removing unreachable block (ram,0x016acc60) */
/* WARNING: Removing unreachable block (ram,0x016accd0) */
/* WARNING: Removing unreachable block (ram,0x016accf4) */
/* WARNING: Removing unreachable block (ram,0x016b465c) */
/* WARNING: Removing unreachable block (ram,0x016b4674) */
/* WARNING: Removing unreachable block (ram,0x016b46e8) */
/* WARNING: Removing unreachable block (ram,0x016b4714) */

void _ZN14CMasterManager10InitializeEP17CParameterManager(long param_1,undefined8 param_2)

{
  long lVar1;
  undefined *puVar2;
  long *plVar3;
  
  plVar3 = (long *)operator new(unsigned long, std::nothrow_t const&)(0xa0,PTR__ZSt7nothrow_02cb9a80);
  if (plVar3 != (long *)0x0) {
    memset(plVar3 + 2,0,0x90);
    *plVar3 = (long)(PTR__ZTV26CMasterParameterBaseSqlite_02cc48f0 + 0x10);
    plVar3[1] = 0;
    CParameterBase::CParameterBase()(plVar3 + 2);
    *(undefined4 *)(plVar3 + 7) = 0x3f800000;
    *(undefined4 *)(plVar3 + 0xc) = 0x3f800000;
    *(undefined4 *)(plVar3 + 0x12) = 0x3f800000;
    puVar2 = PTR__ZTV25CMasterParameterWinCamera_02cbe6a0;
    plVar3[0xd] = 10;
    plVar3[0x13] = 10;
    plVar3[6] = 0;
    plVar3[5] = 0;
    plVar3[4] = 0;
    plVar3[3] = 0;
    plVar3[9] = 0;
    plVar3[8] = 0;
    plVar3[0xb] = 0;
    plVar3[10] = 0;
    plVar3[0xf] = 0;
    plVar3[0xe] = 0;
    plVar3[0x11] = 0;
    plVar3[0x10] = 0;
    *plVar3 = (long)(puVar2 + 0x10);
    plVar3[2] = (long)(puVar2 + 0x78);
  }
  *(long **)(param_1 + 0x60) = plVar3;
  (**(code **)(*plVar3 + 0x10))(plVar3);
  lVar1 = 0;
  if (*(long *)(param_1 + 0x60) != 0) {
    lVar1 = *(long *)(param_1 + 0x60) + 0x10;
  }
  (*(code *)PTR__ZN17CParameterManager12AddParameterEP14CParameterBase_02ca80b0)(param_2,lVar1);
  return;
}

// ==== std::__ndk1::__hash_iterator<std::__ndk1::__hash_node<std::__ndk1::__hash_value_type<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> >, CMasterManager::Status>, void*>*> std::__ndk1::__hash_table<std::__ndk1::__hash_value_type<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> >, CMasterManager::Status>, std::__ndk1::__unordered_map_hasher<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> >, std::__ndk1::__hash_value_type<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> >, CMasterManager::Status>, std::__ndk1::hash<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > >, true>, std::__ndk1::__unordered_map_equal<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> >, std::__ndk1::__hash_value_type<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> >, CMasterManager::Status>, std::__ndk1::equal_to<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > >, true>, Framework::CSTLAllocator<std::__ndk1::__hash_value_type<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> >, CMasterManager::Status>, Framework::CSTLUnorderedMapAllocatorInf> >::find<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > >(std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > const&)
// vaddr 0x16ae704 | ghidra 0x17ae704 | size 468 | symbol _ZNSt6__ndk112__hash_tableINS_17__hash_value_typeINS_12basic_stringIcNS_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS5_22CSTLStringAllocatorInfEEEEEN14CMasterManager6StatusEEENS_22__unordered_map_hasherIS9_SC_NS_4hashIS9_EELb1EEENS_21__unordered_map_equalIS9_SC_NS_8equal_toIS9_EELb1EEENS6_ISC_NS5_28CSTLUnorderedMapAllocatorInfEEEE4findIS9_EENS_15__hash_iteratorIPNS_11__hash_nodeISC_PvEEEERKT_ | lib libSOA-3.7.0.so | 2026-10-08
long * _ZNSt6__ndk112__hash_tableINS_17__hash_value_typeINS_12basic_stringIcNS_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS5_22CSTLStringAllocatorInfEEEEEN14CMasterManager6StatusEEENS_22__unordered_map_hasherIS9_SC_NS_4hashIS9_EELb1EEENS_21__unordered_map_equalIS9_SC_NS_8equal_toIS9_EELb1EEENS6_ISC_NS5_28CSTLUnorderedMapAllocatorInfEEEE4findIS9_EENS_15__hash_iteratorIPNS_11__hash_nodeISC_PvEEEERKT_
                 (long *param_1,byte *param_2)

{
  byte *pbVar1;
  byte bVar2;
  ulong uVar3;
  int iVar4;
  ulong uVar5;
  long *plVar6;
  long lVar7;
  ulong uVar8;
  ulong uVar9;
  undefined1 auStack_38 [8];
  
  uVar5 = *(ulong *)(param_2 + 8);
  pbVar1 = *(byte **)(param_2 + 0x10);
  if ((*param_2 & 1) == 0) {
    pbVar1 = param_2 + 1;
    uVar5 = (ulong)(*param_2 >> 1);
  }
  uVar5 = std::__ndk1::__murmur2_or_cityhash<unsigned long, 64ul>::operator()(void const*, unsigned long)(auStack_38,pbVar1,uVar5);
  uVar8 = param_1[1];
  if (uVar8 != 0) {
    uVar9 = uVar8 - 1;
    if ((uVar9 & uVar8) == 0) {
      uVar5 = uVar9 & uVar5;
    }
    else {
      uVar3 = 0;
      if (uVar8 != 0) {
        uVar3 = uVar5 / uVar8;
      }
      uVar5 = uVar5 - uVar3 * uVar8;
    }
    plVar6 = *(long **)(*param_1 + uVar5 * 8);
    if ((plVar6 != (long *)0x0) && (plVar6 = (long *)*plVar6, plVar6 != (long *)0x0)) {
      pbVar1 = param_2 + 1;
      uVar3 = (ulong)(*param_2 >> 1);
      if ((*param_2 & 1) != 0) {
        pbVar1 = *(byte **)(param_2 + 0x10);
        uVar3 = *(ulong *)(param_2 + 8);
      }
      if ((uVar9 & uVar8) == 0) {
        while ((plVar6[1] & uVar9) == uVar5) {
          bVar2 = *(byte *)(plVar6 + 2);
          uVar8 = (ulong)(bVar2 >> 1);
          if ((bVar2 & 1) != 0) {
            uVar8 = plVar6[3];
          }
          if (uVar8 == uVar3) {
            lVar7 = plVar6[4];
            if ((bVar2 & 1) == 0) {
              lVar7 = (long)plVar6 + 0x11;
            }
            if ((bVar2 & 1) == 0) {
              if (uVar3 == 0) {
                return plVar6;
              }
              uVar8 = 0;
              while (*(byte *)((long)plVar6 + uVar8 + 0x11) == pbVar1[uVar8]) {
                uVar8 = uVar8 + 1;
                if (bVar2 >> 1 == uVar8) {
                  return plVar6;
                }
              }
            }
            else {
              if (uVar3 == 0) {
                return plVar6;
              }
              iVar4 = memcmp(lVar7,pbVar1,uVar3);
              if (iVar4 == 0) {
                return plVar6;
              }
            }
          }
          plVar6 = (long *)*plVar6;
          if (plVar6 == (long *)0x0) {
            return (long *)0x0;
          }
        }
      }
      else {
        while( true ) {
          uVar9 = 0;
          if (uVar8 != 0) {
            uVar9 = (ulong)plVar6[1] / uVar8;
          }
          if (plVar6[1] - uVar9 * uVar8 != uVar5) break;
          bVar2 = *(byte *)(plVar6 + 2);
          uVar9 = (ulong)(bVar2 >> 1);
          if ((bVar2 & 1) != 0) {
            uVar9 = plVar6[3];
          }
          if (uVar9 == uVar3) {
            lVar7 = plVar6[4];
            if ((bVar2 & 1) == 0) {
              lVar7 = (long)plVar6 + 0x11;
            }
            if ((bVar2 & 1) == 0) {
              if (uVar3 == 0) {
                return plVar6;
              }
              uVar9 = 0;
              while (*(byte *)((long)plVar6 + uVar9 + 0x11) == pbVar1[uVar9]) {
                uVar9 = uVar9 + 1;
                if (bVar2 >> 1 == uVar9) {
                  return plVar6;
                }
              }
            }
            else {
              if (uVar3 == 0) {
                return plVar6;
              }
              iVar4 = memcmp(lVar7,pbVar1,uVar3);
              if (iVar4 == 0) {
                return plVar6;
              }
            }
          }
          plVar6 = (long *)*plVar6;
          if (plVar6 == (long *)0x0) {
            return (long *)0x0;
          }
        }
      }
    }
  }
  return (long *)0x0;
}

// ==== std::__ndk1::__hash_table<std::__ndk1::__hash_value_type<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> >, CMasterManager::Status>, std::__ndk1::__unordered_map_hasher<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> >, std::__ndk1::__hash_value_type<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> >, CMasterManager::Status>, std::__ndk1::hash<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > >, true>, std::__ndk1::__unordered_map_equal<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> >, std::__ndk1::__hash_value_type<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> >, CMasterManager::Status>, std::__ndk1::equal_to<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > >, true>, Framework::CSTLAllocator<std::__ndk1::__hash_value_type<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> >, CMasterManager::Status>, Framework::CSTLUnorderedMapAllocatorInf> >::rehash(unsigned long)
// vaddr 0x16ae8d8 | ghidra 0x17ae8d8 | size 208 | symbol _ZNSt6__ndk112__hash_tableINS_17__hash_value_typeINS_12basic_stringIcNS_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS5_22CSTLStringAllocatorInfEEEEEN14CMasterManager6StatusEEENS_22__unordered_map_hasherIS9_SC_NS_4hashIS9_EELb1EEENS_21__unordered_map_equalIS9_SC_NS_8equal_toIS9_EELb1EEENS6_ISC_NS5_28CSTLUnorderedMapAllocatorInfEEEE6rehashEm | lib libSOA-3.7.0.so | 2026-10-08
void _ZNSt6__ndk112__hash_tableINS_17__hash_value_typeINS_12basic_stringIcNS_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS5_22CSTLStringAllocatorInfEEEEEN14CMasterManager6StatusEEENS_22__unordered_map_hasherIS9_SC_NS_4hashIS9_EELb1EEENS_21__unordered_map_equalIS9_SC_NS_8equal_toIS9_EELb1EEENS6_ISC_NS5_28CSTLUnorderedMapAllocatorInfEEEE6rehashEm
               (long param_1,ulong param_2)

{
  ulong uVar1;
  ulong uVar2;
  
  if (param_2 - 1 == 0) {
    param_2 = 2;
  }
  else if ((param_2 - 1 & param_2) != 0) {
    param_2 = std::__ndk1::__next_prime(unsigned long)(param_2);
  }
  uVar2 = *(ulong *)(param_1 + 8);
  uVar1 = param_2;
  if (uVar2 < param_2) {
code_r0x011e3ba0:
    (*(code *)
      PTR__ZNSt6__ndk112__hash_tableINS_17__hash_value_typeINS_12basic_stringIcNS_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS5_22CSTLStringAllocatorInfEEEEEN14CMasterManager6StatusEEENS_22__unordered_map_hasherIS9_SC_NS_4hashIS9_EELb1EEENS_21__unordered_map_equalIS9_SC_NS_8equal_toIS9_EELb1EEENS6_ISC_NS5_28CSTLUnorderedMapAllocatorInfEEEE8__rehashEm_02ca9dc0
    )(param_1,uVar1);
    return;
  }
  if (param_2 < uVar2) {
    if (uVar2 < 3 || (uVar2 - 1 & uVar2) != 0) {
      uVar1 = std::__ndk1::__next_prime(unsigned long)();
    }
    else {
      uVar1 = 1L << (0x40U - LZCOUNT((long)((float)*(ulong *)(param_1 + 0x18) /
                                           *(float *)(param_1 + 0x20)) + -1) & 0x3f);
    }
    if (uVar1 <= param_2) {
      uVar1 = param_2;
    }
    if (uVar1 < uVar2) goto code_r0x011e3ba0;
  }
  return;
}

// ==== std::__ndk1::__hash_table<std::__ndk1::__hash_value_type<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> >, CMasterManager::Status>, std::__ndk1::__unordered_map_hasher<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> >, std::__ndk1::__hash_value_type<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> >, CMasterManager::Status>, std::__ndk1::hash<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > >, true>, std::__ndk1::__unordered_map_equal<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> >, std::__ndk1::__hash_value_type<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> >, CMasterManager::Status>, std::__ndk1::equal_to<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > >, true>, Framework::CSTLAllocator<std::__ndk1::__hash_value_type<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> >, CMasterManager::Status>, Framework::CSTLUnorderedMapAllocatorInf> >::__rehash(unsigned long)
// vaddr 0x16ae9a8 | ghidra 0x17ae9a8 | size 700 | symbol _ZNSt6__ndk112__hash_tableINS_17__hash_value_typeINS_12basic_stringIcNS_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS5_22CSTLStringAllocatorInfEEEEEN14CMasterManager6StatusEEENS_22__unordered_map_hasherIS9_SC_NS_4hashIS9_EELb1EEENS_21__unordered_map_equalIS9_SC_NS_8equal_toIS9_EELb1EEENS6_ISC_NS5_28CSTLUnorderedMapAllocatorInfEEEE8__rehashEm | lib libSOA-3.7.0.so | 2026-10-08
void _ZNSt6__ndk112__hash_tableINS_17__hash_value_typeINS_12basic_stringIcNS_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS5_22CSTLStringAllocatorInfEEEEEN14CMasterManager6StatusEEENS_22__unordered_map_hasherIS9_SC_NS_4hashIS9_EELb1EEENS_21__unordered_map_equalIS9_SC_NS_8equal_toIS9_EELb1EEENS6_ISC_NS5_28CSTLUnorderedMapAllocatorInfEEEE8__rehashEm
               (long *param_1,ulong param_2)

{
  ulong uVar1;
  byte bVar2;
  ulong uVar3;
  int iVar4;
  long lVar5;
  long lVar6;
  ulong uVar7;
  long *plVar8;
  ulong uVar9;
  long *plVar10;
  long *plVar11;
  ulong uVar12;
  char *pcVar13;
  char *pcVar14;
  long *plVar15;
  long *plVar16;
  
  if (param_2 == 0) {
    lVar5 = *param_1;
    *param_1 = 0;
    if (lVar5 != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)();
    }
    param_1[1] = 0;
  }
  else {
    lVar5 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(param_2 << 3,&UNK_027dc2d5/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_UnorderedMap.h"*/,0x1c);
    if (lVar5 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    }
    lVar6 = *param_1;
    *param_1 = lVar5;
    if (lVar6 != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)();
    }
    uVar7 = 0;
    param_1[1] = param_2;
    do {
      *(undefined8 *)(*param_1 + uVar7 * 8) = 0;
      uVar7 = uVar7 + 1;
    } while (param_2 != uVar7);
    plVar15 = (long *)param_1[2];
    if (plVar15 != (long *)0x0) {
      uVar7 = plVar15[1];
      uVar12 = param_2 - 1;
      if ((uVar12 & param_2) == 0) {
        uVar7 = uVar7 & uVar12;
      }
      else {
        uVar9 = 0;
        if (param_2 != 0) {
          uVar9 = uVar7 / param_2;
        }
        uVar7 = uVar7 - uVar9 * param_2;
      }
      *(long **)(*param_1 + uVar7 * 8) = param_1 + 2;
      plVar8 = (long *)*plVar15;
      while (plVar8 != (long *)0x0) {
        while( true ) {
          plVar16 = plVar8;
          uVar9 = plVar16[1];
          if ((uVar12 & param_2) == 0) {
            uVar9 = uVar9 & uVar12;
          }
          else {
            uVar3 = 0;
            if (param_2 != 0) {
              uVar3 = uVar9 / param_2;
            }
            uVar9 = uVar9 - uVar3 * param_2;
          }
          if (uVar9 != uVar7) break;
          plVar8 = (long *)*plVar16;
          plVar15 = plVar16;
          if ((long *)*plVar16 == (long *)0x0) {
            return;
          }
        }
        if (*(long *)(*param_1 + uVar9 * 8) == 0) {
          *(long **)(*param_1 + uVar9 * 8) = plVar15;
          plVar8 = (long *)*plVar16;
          plVar15 = plVar16;
          uVar7 = uVar9;
        }
        else {
          plVar10 = (long *)*plVar16;
          plVar8 = plVar16;
          if (plVar10 != (long *)0x0) {
            bVar2 = *(byte *)(plVar16 + 2);
            uVar3 = (ulong)(bVar2 >> 1);
            if ((bVar2 & 1) != 0) {
              uVar3 = plVar16[3];
            }
            if ((bVar2 & 1) == 0) {
              lVar5 = -(ulong)(bVar2 >> 1);
              do {
                plVar11 = plVar10;
                bVar2 = *(byte *)(plVar11 + 2);
                uVar1 = (ulong)(bVar2 >> 1);
                if ((bVar2 & 1) != 0) {
                  uVar1 = plVar11[3];
                }
                if (uVar3 != uVar1) break;
                if (uVar3 != 0) {
                  pcVar13 = (char *)plVar11[4];
                  lVar6 = lVar5;
                  pcVar14 = (char *)((long)plVar16 + 0x11);
                  if ((bVar2 & 1) == 0) {
                    pcVar13 = (char *)((long)plVar11 + 0x11);
                  }
                  do {
                    if (*pcVar14 != *pcVar13) goto code_r0x017aebc0;
                    lVar6 = lVar6 + 1;
                    pcVar13 = pcVar13 + 1;
                    pcVar14 = pcVar14 + 1;
                  } while (lVar6 != 0);
                }
                plVar8 = plVar11;
                plVar10 = (long *)*plVar11;
              } while ((long *)*plVar11 != (long *)0x0);
            }
            else if (uVar3 == 0) {
              do {
                plVar11 = plVar10;
                uVar3 = (ulong)(*(byte *)(plVar11 + 2) >> 1);
                if ((*(byte *)(plVar11 + 2) & 1) != 0) {
                  uVar3 = plVar11[3];
                }
              } while ((uVar3 == 0) &&
                      (plVar10 = (long *)*plVar11, plVar8 = plVar11, (long *)*plVar11 != (long *)0x0
                      ));
            }
            else {
              while( true ) {
                plVar11 = plVar10;
                bVar2 = *(byte *)(plVar11 + 2);
                uVar1 = (ulong)(bVar2 >> 1);
                if ((bVar2 & 1) != 0) {
                  uVar1 = plVar11[3];
                }
                if (uVar3 != uVar1) break;
                lVar5 = plVar11[4];
                if ((bVar2 & 1) == 0) {
                  lVar5 = (long)plVar11 + 0x11;
                }
                iVar4 = memcmp(plVar16[4],lVar5,uVar3);
                if ((iVar4 != 0) ||
                   (plVar10 = (long *)*plVar11, plVar8 = plVar11, (long *)*plVar11 == (long *)0x0))
                break;
              }
            }
          }
code_r0x017aebc0:
          *plVar15 = *plVar8;
          *plVar8 = **(long **)(*param_1 + uVar9 * 8);
          **(undefined8 **)(*param_1 + uVar9 * 8) = plVar16;
          plVar8 = (long *)*plVar15;
        }
      }
    }
  }
  return;
}


// FAILED to create function at 02ae8128 CMasterManager::vtable
// FAILED to create function at 02ae8190 CMasterManager::typeinfo
