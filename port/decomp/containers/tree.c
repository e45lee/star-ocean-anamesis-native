// port/decomp/containers/tree.c: Ghidra decompiles for the containers subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileAt.java, tools/resolve_decomp.py
// run      2026-10-04 05:12 UTC: tools/decomp_at.sh '--into' 'containers/tree' '1260db8' '1260efc' '13b8344' '161f5a4' '1622ec0' '1f9c698' '1f9c69c' '1f9d6b8' '1f9eb64' '1fb593c' '202df5c' '202df64' '202df6c' '202df70' '202dfcc' '202e38c' '202e398' '202e520' '202e6cc' '202e6d4' '202e6d8' '202e70c' '202e87c' '202ef14' '202f638' '202f810' '202fde4' '2030720' '20310c4' '2031334' '20314a4' '2031b80' '2036e68' '2050efc' '2050f88' '2052198' '2075090' '21dfb48' '21e03dc' '21e0b84' '21e0df8' '21e19a0' '21e2140' '21f87c4' '21fa15c' '21fa2c4' '21fb4ec' '21fd088' '22deb20' '22e0d08' '22e22ac' '22e241c' '22e43c0' '22e5818' '230aef8' '230b6a0' '232ea48'

// ==== Framework::CSTLMap<unsigned int, IParameterProperty*>::CSTLMap(Framework::CSTLMap<unsigned int, IParameterProperty*> const&)
// vaddr 0x1160db8 | ghidra 0x1260db8 | size 324 | symbol _ZN9Framework7CSTLMapIjP18IParameterPropertyEC2ERKS3_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework7CSTLMapIjP18IParameterPropertyEC2ERKS3_(long *param_1,long *param_2)

{
  bool bVar1;
  long *plVar2;
  undefined8 *puVar3;
  long *plVar4;
  long *plVar5;
  undefined8 uVar6;
  undefined8 uStack_58;
  
  plVar5 = param_1 + 1;
  *plVar5 = 0;
  param_1[2] = 0;
  *param_1 = (long)plVar5;
  plVar4 = (long *)*param_2;
  do {
    while( true ) {
      if (plVar4 == param_2 + 1) {
        return;
      }
      plVar2 = (long *)std::__ndk1::__tree_node_base<void*>*& std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::__find_equal<unsigned int>(std::__ndk1::__tree_const_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>, std::__ndk1::__tree_node_base<void*>*&, unsigned int const&)(param_1,plVar5,&uStack_58,plVar4 + 4);
      if (*plVar2 != 0) break;
      puVar3 = (undefined8 *)Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(0x30,&UNK_027dc4e5/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Map.h"*/,0x21);
      if (puVar3 == (undefined8 *)0x0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
      }
      uVar6 = plVar4[4];
      puVar3[5] = plVar4[5];
      puVar3[4] = uVar6;
      *puVar3 = 0;
      puVar3[1] = 0;
      puVar3[2] = uStack_58;
      *plVar2 = (long)puVar3;
      if (*(long *)*param_1 != 0) {
        *param_1 = *(long *)*param_1;
        puVar3 = (undefined8 *)*plVar2;
      }
      void std::__ndk1::__tree_balance_after_insert<std::__ndk1::__tree_node_base<void*>*>(std::__ndk1::__tree_node_base<void*>*, std::__ndk1::__tree_node_base<void*>*)(param_1[1],puVar3);
      param_1[2] = param_1[2] + 1;
      plVar2 = (long *)plVar4[1];
      if ((long *)plVar4[1] == (long *)0x0) goto code_r0x01260ec4;
code_r0x01260eb0:
      do {
        plVar4 = plVar2;
        plVar2 = (long *)*plVar4;
      } while ((long *)*plVar4 != (long *)0x0);
    }
    plVar2 = (long *)plVar4[1];
    if ((long *)plVar4[1] != (long *)0x0) goto code_r0x01260eb0;
code_r0x01260ec4:
    do {
      plVar2 = (long *)plVar4[2];
      bVar1 = (long *)*plVar2 != plVar4;
      plVar4 = plVar2;
    } while (bVar1);
  } while( true );
}

// ==== Framework::CSTLMap<unsigned int, InfoBase*>::CSTLMap(Framework::CSTLMap<unsigned int, InfoBase*> const&)
// vaddr 0x1160efc | ghidra 0x1260efc | size 324 | symbol _ZN9Framework7CSTLMapIjP8InfoBaseEC2ERKS3_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework7CSTLMapIjP8InfoBaseEC2ERKS3_(long *param_1,long *param_2)

{
  bool bVar1;
  long *plVar2;
  undefined8 *puVar3;
  long *plVar4;
  long *plVar5;
  undefined8 uVar6;
  undefined8 uStack_58;
  
  plVar5 = param_1 + 1;
  *plVar5 = 0;
  param_1[2] = 0;
  *param_1 = (long)plVar5;
  plVar4 = (long *)*param_2;
  do {
    while( true ) {
      if (plVar4 == param_2 + 1) {
        return;
      }
      plVar2 = (long *)std::__ndk1::__tree_node_base<void*>*& std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::__find_equal<unsigned int>(std::__ndk1::__tree_const_iterator<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*, long>, std::__ndk1::__tree_node_base<void*>*&, unsigned int const&)(param_1,plVar5,&uStack_58,plVar4 + 4);
      if (*plVar2 != 0) break;
      puVar3 = (undefined8 *)Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(0x30,&UNK_027dc4e5/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Map.h"*/,0x21);
      if (puVar3 == (undefined8 *)0x0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
      }
      uVar6 = plVar4[4];
      puVar3[5] = plVar4[5];
      puVar3[4] = uVar6;
      *puVar3 = 0;
      puVar3[1] = 0;
      puVar3[2] = uStack_58;
      *plVar2 = (long)puVar3;
      if (*(long *)*param_1 != 0) {
        *param_1 = *(long *)*param_1;
        puVar3 = (undefined8 *)*plVar2;
      }
      void std::__ndk1::__tree_balance_after_insert<std::__ndk1::__tree_node_base<void*>*>(std::__ndk1::__tree_node_base<void*>*, std::__ndk1::__tree_node_base<void*>*)(param_1[1],puVar3);
      param_1[2] = param_1[2] + 1;
      plVar2 = (long *)plVar4[1];
      if ((long *)plVar4[1] == (long *)0x0) goto code_r0x01261008;
code_r0x01260ff4:
      do {
        plVar4 = plVar2;
        plVar2 = (long *)*plVar4;
      } while ((long *)*plVar4 != (long *)0x0);
    }
    plVar2 = (long *)plVar4[1];
    if ((long *)plVar4[1] != (long *)0x0) goto code_r0x01260ff4;
code_r0x01261008:
    do {
      plVar2 = (long *)plVar4[2];
      bVar1 = (long *)*plVar2 != plVar4;
      plVar4 = plVar2;
    } while (bVar1);
  } while( true );
}

// ==== Framework::CSTLMap<Parameter::eAttackID, CBattleUtility::SetupAttackInfo>::CSTLMap(Framework::CSTLMap<Parameter::eAttackID, CBattleUtility::SetupAttackInfo> const&)
// vaddr 0x12b8344 | ghidra 0x13b8344 | size 256 | symbol _ZN9Framework7CSTLMapIN9Parameter9eAttackIDEN14CBattleUtility15SetupAttackInfoEEC2ERKS5_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework7CSTLMapIN9Parameter9eAttackIDEN14CBattleUtility15SetupAttackInfoEEC2ERKS5_
               (long *param_1,undefined8 *param_2)

{
  bool bVar1;
  long *plVar2;
  undefined8 *puVar3;
  long *plVar4;
  long *plVar5;
  undefined8 *apuStack_58 [3];
  undefined8 uStack_38;
  
  plVar5 = param_1 + 1;
  *plVar5 = 0;
  param_1[2] = 0;
  *param_1 = (long)plVar5;
  plVar4 = (long *)*param_2;
  do {
    while( true ) {
      if (plVar4 == param_2 + 1) {
        return;
      }
      plVar2 = (long *)std::__ndk1::__tree_node_base<void*>*& std::__ndk1::__tree<std::__ndk1::__value_type<Parameter::eAttackID, CBattleUtility::SetupAttackInfo>, std::__ndk1::__map_value_compare<Parameter::eAttackID, std::__ndk1::__value_type<Parameter::eAttackID, CBattleUtility::SetupAttackInfo>, std::__ndk1::less<Parameter::eAttackID>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<Parameter::eAttackID, CBattleUtility::SetupAttackInfo>, Framework::CSTLMapAllocatorInf> >::__find_equal<Parameter::eAttackID>(std::__ndk1::__tree_const_iterator<std::__ndk1::__value_type<Parameter::eAttackID, CBattleUtility::SetupAttackInfo>, std::__ndk1::__tree_node<std::__ndk1::__value_type<Parameter::eAttackID, CBattleUtility::SetupAttackInfo>, void*>*, long>, std::__ndk1::__tree_node_base<void*>*&, Parameter::eAttackID const&)(param_1,plVar5,&uStack_38,plVar4 + 4);
      if (*plVar2 == 0) break;
      plVar2 = (long *)plVar4[1];
      if ((long *)plVar4[1] != (long *)0x0) goto code_r0x013b83fc;
code_r0x013b8410:
      do {
        plVar2 = (long *)plVar4[2];
        bVar1 = (long *)*plVar2 != plVar4;
        plVar4 = plVar2;
      } while (bVar1);
    }
    std::__ndk1::unique_ptr<std::__ndk1::__tree_node<std::__ndk1::__value_type<Parameter::eAttackID, CBattleUtility::SetupAttackInfo>, void*>, std::__ndk1::__tree_node_destructor<Framework::CSTLAllocator<std::__ndk1::__tree_node<std::__ndk1::__value_type<Parameter::eAttackID, CBattleUtility::SetupAttackInfo>, void*>, Framework::CSTLMapAllocatorInf> > > std::__ndk1::__tree<std::__ndk1::__value_type<Parameter::eAttackID, CBattleUtility::SetupAttackInfo>, std::__ndk1::__map_value_compare<Parameter::eAttackID, std::__ndk1::__value_type<Parameter::eAttackID, CBattleUtility::SetupAttackInfo>, std::__ndk1::less<Parameter::eAttackID>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<Parameter::eAttackID, CBattleUtility::SetupAttackInfo>, Framework::CSTLMapAllocatorInf> >::__construct_node<std::__ndk1::pair<Parameter::eAttackID const, CBattleUtility::SetupAttackInfo> const&>(std::__ndk1::pair<Parameter::eAttackID const, CBattleUtility::SetupAttackInfo> const&)(apuStack_58,param_1,plVar4 + 4);
    *apuStack_58[0] = 0;
    apuStack_58[0][1] = 0;
    apuStack_58[0][2] = uStack_38;
    *plVar2 = (long)apuStack_58[0];
    puVar3 = apuStack_58[0];
    if (*(long *)*param_1 != 0) {
      *param_1 = *(long *)*param_1;
      puVar3 = (undefined8 *)*plVar2;
    }
    void std::__ndk1::__tree_balance_after_insert<std::__ndk1::__tree_node_base<void*>*>(std::__ndk1::__tree_node_base<void*>*, std::__ndk1::__tree_node_base<void*>*)(param_1[1],puVar3);
    param_1[2] = param_1[2] + 1;
    plVar2 = (long *)plVar4[1];
    if ((long *)plVar4[1] == (long *)0x0) goto code_r0x013b8410;
code_r0x013b83fc:
    do {
      plVar4 = plVar2;
      plVar2 = (long *)*plVar4;
    } while ((long *)*plVar4 != (long *)0x0);
  } while( true );
}

// ==== Framework::CSTLMap<unsigned long, CAreaInfo>::CSTLMap(Framework::CSTLMap<unsigned long, CAreaInfo> const&)
// vaddr 0x151f5a4 | ghidra 0x161f5a4 | size 256 | symbol _ZN9Framework7CSTLMapIm9CAreaInfoEC2ERKS2_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework7CSTLMapIm9CAreaInfoEC2ERKS2_(long *param_1,undefined8 *param_2)

{
  bool bVar1;
  long *plVar2;
  undefined8 *puVar3;
  long *plVar4;
  long *plVar5;
  undefined8 *apuStack_58 [3];
  undefined8 uStack_38;
  
  plVar5 = param_1 + 1;
  *plVar5 = 0;
  param_1[2] = 0;
  *param_1 = (long)plVar5;
  plVar4 = (long *)*param_2;
  do {
    while( true ) {
      if (plVar4 == param_2 + 1) {
        return;
      }
      plVar2 = (long *)std::__ndk1::__tree_node_base<void*>*& std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CAreaInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CAreaInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CAreaInfo>, Framework::CSTLMapAllocatorInf> >::__find_equal<unsigned long>(std::__ndk1::__tree_const_iterator<std::__ndk1::__value_type<unsigned long, CAreaInfo>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CAreaInfo>, void*>*, long>, std::__ndk1::__tree_node_base<void*>*&, unsigned long const&)(param_1,plVar5,&uStack_38,plVar4 + 4);
      if (*plVar2 == 0) break;
      plVar2 = (long *)plVar4[1];
      if ((long *)plVar4[1] != (long *)0x0) goto code_r0x0161f65c;
code_r0x0161f670:
      do {
        plVar2 = (long *)plVar4[2];
        bVar1 = (long *)*plVar2 != plVar4;
        plVar4 = plVar2;
      } while (bVar1);
    }
    std::__ndk1::unique_ptr<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CAreaInfo>, void*>, std::__ndk1::__tree_node_destructor<Framework::CSTLAllocator<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CAreaInfo>, void*>, Framework::CSTLMapAllocatorInf> > > std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CAreaInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CAreaInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CAreaInfo>, Framework::CSTLMapAllocatorInf> >::__construct_node<std::__ndk1::pair<unsigned long const, CAreaInfo> const&>(std::__ndk1::pair<unsigned long const, CAreaInfo> const&)(apuStack_58,param_1,plVar4 + 4);
    *apuStack_58[0] = 0;
    apuStack_58[0][1] = 0;
    apuStack_58[0][2] = uStack_38;
    *plVar2 = (long)apuStack_58[0];
    puVar3 = apuStack_58[0];
    if (*(long *)*param_1 != 0) {
      *param_1 = *(long *)*param_1;
      puVar3 = (undefined8 *)*plVar2;
    }
    void std::__ndk1::__tree_balance_after_insert<std::__ndk1::__tree_node_base<void*>*>(std::__ndk1::__tree_node_base<void*>*, std::__ndk1::__tree_node_base<void*>*)(param_1[1],puVar3);
    param_1[2] = param_1[2] + 1;
    plVar2 = (long *)plVar4[1];
    if ((long *)plVar4[1] == (long *)0x0) goto code_r0x0161f670;
code_r0x0161f65c:
    do {
      plVar4 = plVar2;
      plVar2 = (long *)*plVar4;
    } while ((long *)*plVar4 != (long *)0x0);
  } while( true );
}

// ==== Framework::CSTLMap<unsigned long, CWorldMapCellInfo>::CSTLMap(Framework::CSTLMap<unsigned long, CWorldMapCellInfo> const&)
// vaddr 0x1522ec0 | ghidra 0x1622ec0 | size 256 | symbol _ZN9Framework7CSTLMapIm17CWorldMapCellInfoEC2ERKS2_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework7CSTLMapIm17CWorldMapCellInfoEC2ERKS2_(long *param_1,undefined8 *param_2)

{
  bool bVar1;
  long *plVar2;
  undefined8 *puVar3;
  long *plVar4;
  long *plVar5;
  undefined8 *apuStack_58 [3];
  undefined8 uStack_38;
  
  plVar5 = param_1 + 1;
  *plVar5 = 0;
  param_1[2] = 0;
  *param_1 = (long)plVar5;
  plVar4 = (long *)*param_2;
  do {
    while( true ) {
      if (plVar4 == param_2 + 1) {
        return;
      }
      plVar2 = (long *)std::__ndk1::__tree_node_base<void*>*& std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CWorldMapCellInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CWorldMapCellInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CWorldMapCellInfo>, Framework::CSTLMapAllocatorInf> >::__find_equal<unsigned long>(std::__ndk1::__tree_const_iterator<std::__ndk1::__value_type<unsigned long, CWorldMapCellInfo>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CWorldMapCellInfo>, void*>*, long>, std::__ndk1::__tree_node_base<void*>*&, unsigned long const&)(param_1,plVar5,&uStack_38,plVar4 + 4);
      if (*plVar2 == 0) break;
      plVar2 = (long *)plVar4[1];
      if ((long *)plVar4[1] != (long *)0x0) goto code_r0x01622f78;
code_r0x01622f8c:
      do {
        plVar2 = (long *)plVar4[2];
        bVar1 = (long *)*plVar2 != plVar4;
        plVar4 = plVar2;
      } while (bVar1);
    }
    std::__ndk1::unique_ptr<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CWorldMapCellInfo>, void*>, std::__ndk1::__tree_node_destructor<Framework::CSTLAllocator<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CWorldMapCellInfo>, void*>, Framework::CSTLMapAllocatorInf> > > std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CWorldMapCellInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CWorldMapCellInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CWorldMapCellInfo>, Framework::CSTLMapAllocatorInf> >::__construct_node<std::__ndk1::pair<unsigned long const, CWorldMapCellInfo> const&>(std::__ndk1::pair<unsigned long const, CWorldMapCellInfo> const&)(apuStack_58,param_1,plVar4 + 4);
    *apuStack_58[0] = 0;
    apuStack_58[0][1] = 0;
    apuStack_58[0][2] = uStack_38;
    *plVar2 = (long)apuStack_58[0];
    puVar3 = apuStack_58[0];
    if (*(long *)*param_1 != 0) {
      *param_1 = *(long *)*param_1;
      puVar3 = (undefined8 *)*plVar2;
    }
    void std::__ndk1::__tree_balance_after_insert<std::__ndk1::__tree_node_base<void*>*>(std::__ndk1::__tree_node_base<void*>*, std::__ndk1::__tree_node_base<void*>*)(param_1[1],puVar3);
    param_1[2] = param_1[2] + 1;
    plVar2 = (long *)plVar4[1];
    if ((long *)plVar4[1] == (long *)0x0) goto code_r0x01622f8c;
code_r0x01622f78:
    do {
      plVar4 = plVar2;
      plVar2 = (long *)*plVar4;
    } while ((long *)*plVar4 != (long *)0x0);
  } while( true );
}

// ==== Aska::TBinaryNode<8u>::Init()
// vaddr 0x1e9c698 | ghidra 0x1f9c698 | size 4 | symbol _ZN4Aska11TBinaryNodeILj8EE4InitEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11TBinaryNodeILj8EE4InitEv(void)

{
  return;
}

// ==== Aska::TBinaryNode<8u>::Term()
// vaddr 0x1e9c69c | ghidra 0x1f9c69c | size 4 | symbol _ZN4Aska11TBinaryNodeILj8EE4TermEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11TBinaryNodeILj8EE4TermEv(void)

{
  return;
}

// ==== Aska::TBinaryNode<8u>::~TBinaryNode()
// vaddr 0x1e9d6b8 | ghidra 0x1f9d6b8 | size 4 | symbol _ZN4Aska11TBinaryNodeILj8EED2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11TBinaryNodeILj8EED2Ev(void)

{
  return;
}

// ==== Framework::THierarchy<Framework::CTimeElement>::DetachSelf(Framework::CTimeElement*)
// vaddr 0x1e9eb64 | ghidra 0x1f9eb64 | size 256 | symbol _ZN9Framework10THierarchyINS_12CTimeElementEE10DetachSelfEPS1_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework10THierarchyINS_12CTimeElementEE10DetachSelfEPS1_(long param_1,long param_2)

{
  long lVar1;
  long lVar2;
  long *plVar3;
  long lVar4;
  long *plVar5;
  
  plVar3 = (long *)(param_1 + 8);
  lVar4 = *plVar3;
  lVar1 = lVar4;
  if (param_2 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02966694/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/THierarchy.h"*/,0x77,&UNK_02966727/*"apSelf is null"*/);
    lVar1 = *plVar3;
  }
  if (lVar1 != 0) {
    plVar5 = (long *)(lVar1 + 0x18);
    lVar1 = *plVar5;
    while (lVar1 != param_2) {
      plVar5 = (long *)(*plVar5 + 0x10);
      lVar1 = *plVar5;
    }
    *plVar5 = *(long *)(param_1 + 0x10);
  }
  lVar1 = *(long *)(param_1 + 0x18);
  *(undefined8 *)(param_1 + 8) = 0;
  *(undefined8 *)(param_1 + 0x10) = 0;
  if (lVar1 != 0) {
    *(long *)(lVar1 + 8) = lVar4;
    lVar1 = *(long *)(lVar1 + 0x10);
    if (*(long *)(*(long *)(param_1 + 0x18) + 8) == 0) {
      *(undefined8 *)(*(long *)(param_1 + 0x18) + 0x10) = 0;
    }
    if (lVar1 != 0) {
      if (lVar4 == 0) {
        do {
          lVar2 = *(long *)(lVar1 + 0x10);
          *(undefined8 *)(lVar1 + 8) = 0;
          *(undefined8 *)(lVar1 + 0x10) = 0;
          lVar1 = lVar2;
        } while (lVar2 != 0);
      }
      else {
        do {
          plVar5 = (long *)(lVar1 + 0x10);
          *(long *)(lVar1 + 8) = lVar4;
          lVar1 = *plVar5;
        } while (*plVar5 != 0);
      }
    }
    if (lVar4 != 0) {
      plVar5 = (long *)(lVar4 + 0x18);
      lVar1 = *plVar5;
      while (lVar1 != 0) {
        plVar5 = (long *)(lVar1 + 0x10);
        lVar1 = *plVar5;
      }
      *plVar5 = *(long *)(param_1 + 0x18);
    }
  }
  *(undefined8 *)(param_1 + 0x10) = 0;
  *plVar3 = 0;
  *(undefined8 *)(param_1 + 0x20) = 0;
  *(undefined8 *)(param_1 + 0x18) = 0;
  return;
}

// ==== Framework::THierarchy<Framework::Cocos::CCocosNode>::AddChild(Framework::Cocos::CCocosNode*, Framework::Cocos::CCocosNode*)
// vaddr 0x1eb593c | ghidra 0x1fb593c | size 216 | symbol _ZN9Framework10THierarchyINS_5Cocos10CCocosNodeEE8AddChildEPS2_S4_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework10THierarchyINS_5Cocos10CCocosNodeEE8AddChildEPS2_S4_
               (long param_1,long param_2,long param_3)

{
  long lVar1;
  long *plVar2;
  
  if (param_2 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02966694/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/THierarchy.h"*/,0x58,&UNK_029666e8/*"apParent is null"*/);
  }
  if (param_3 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02966694/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/THierarchy.h"*/,0x59,&UNK_029666f9/*"apTarget is null"*/);
    lVar1 = lRam0000000000000008;
  }
  else {
    lVar1 = *(long *)(param_3 + 8);
  }
  if (lVar1 != 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02966694/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/THierarchy.h"*/,0x5a,&UNK_02805036/*"Argument 'target' arleady has parent."*/);
  }
  if (param_3 == param_2) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02966694/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/THierarchy.h"*/,0x5b,&UNK_0296670a/*"Argument 'target' is itself."*/);
    lVar1 = *(long *)(param_1 + 0x18);
  }
  else {
    lVar1 = *(long *)(param_1 + 0x18);
  }
  if (lVar1 == 0) {
    *(long *)(param_1 + 0x18) = param_3;
  }
  else {
    while (plVar2 = (long *)(lVar1 + 0x10), *plVar2 != 0) {
      lVar1 = *plVar2;
    }
    *plVar2 = param_3;
  }
  *(long *)(param_3 + 8) = param_2;
  return;
}

// ==== Aska::TBinaryNode<8u>::GetKey() const
// vaddr 0x1f2df5c | ghidra 0x202df5c | size 8 | symbol _ZNK4Aska11TBinaryNodeILj8EE6GetKeyEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK4Aska11TBinaryNodeILj8EE6GetKeyEv(long param_1)

{
  return param_1 + 0x28;
}

// ==== Aska::TBinaryNode<24u>::~TBinaryNode()
// vaddr 0x1f2df64 | ghidra 0x202df64 | size 4 | symbol _ZN4Aska11TBinaryNodeILj24EED2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11TBinaryNodeILj24EED2Ev(void)

{
  return;
}

// ==== Aska::TBinaryNode<24u>::Init()
// vaddr 0x1f2df6c | ghidra 0x202df6c | size 4 | symbol _ZN4Aska11TBinaryNodeILj24EE4InitEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11TBinaryNodeILj24EE4InitEv(void)

{
  return;
}

// ==== Aska::TBinaryNode<24u>::Term()
// vaddr 0x1f2df70 | ghidra 0x202df70 | size 4 | symbol _ZN4Aska11TBinaryNodeILj24EE4TermEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11TBinaryNodeILj24EE4TermEv(void)

{
  return;
}

// ==== Aska::TBinaryNode<24u>::GetKey() const
// vaddr 0x1f2dfcc | ghidra 0x202dfcc | size 8 | symbol _ZNK4Aska11TBinaryNodeILj24EE6GetKeyEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK4Aska11TBinaryNodeILj24EE6GetKeyEv(long param_1)

{
  return param_1 + 0x28;
}

// ==== Aska::TBinaryNode<16u>::GetKey() const
// vaddr 0x1f2e38c | ghidra 0x202e38c | size 8 | symbol _ZNK4Aska11TBinaryNodeILj16EE6GetKeyEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK4Aska11TBinaryNodeILj16EE6GetKeyEv(long param_1)

{
  return param_1 + 0x28;
}

// ==== Aska::TBinaryNode<32u>::Term()
// vaddr 0x1f2e398 | ghidra 0x202e398 | size 4 | symbol _ZN4Aska11TBinaryNodeILj32EE4TermEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11TBinaryNodeILj32EE4TermEv(void)

{
  return;
}

// ==== Aska::TBinaryNode<32u>::GetKey() const
// vaddr 0x1f2e520 | ghidra 0x202e520 | size 8 | symbol _ZNK4Aska11TBinaryNodeILj32EE6GetKeyEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK4Aska11TBinaryNodeILj32EE6GetKeyEv(long param_1)

{
  return param_1 + 0x28;
}

// ==== Aska::TBinaryNode<16u>::~TBinaryNode()
// vaddr 0x1f2e6cc | ghidra 0x202e6cc | size 4 | symbol _ZN4Aska11TBinaryNodeILj16EED2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11TBinaryNodeILj16EED2Ev(void)

{
  return;
}

// ==== Aska::TBinaryNode<16u>::Init()
// vaddr 0x1f2e6d4 | ghidra 0x202e6d4 | size 4 | symbol _ZN4Aska11TBinaryNodeILj16EE4InitEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11TBinaryNodeILj16EE4InitEv(void)

{
  return;
}

// ==== Aska::TBinaryNode<16u>::Term()
// vaddr 0x1f2e6d8 | ghidra 0x202e6d8 | size 4 | symbol _ZN4Aska11TBinaryNodeILj16EE4TermEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11TBinaryNodeILj16EE4TermEv(void)

{
  return;
}

// ==== Aska::TBinaryTree<Aska::AUIDNode>::AllocNode(void const*)
// vaddr 0x1f2e70c | ghidra 0x202e70c | size 368 | symbol _ZN4Aska11TBinaryTreeINS_8AUIDNodeEE9AllocNodeEPKv | lib libSOA-3.7.0.so | 2026-10-04
long * _ZN4Aska11TBinaryTreeINS_8AUIDNodeEE9AllocNodeEPKv(long param_1,undefined8 param_2)

{
  undefined *puVar1;
  uint uVar2;
  uint uVar3;
  long *plVar4;
  long lVar5;
  uint uVar6;
  long lVar7;
  ulong uVar8;
  ulong uVar9;
  ulong uVar10;
  
  if (*(uint *)(param_1 + 0x3c) < *(uint *)(param_1 + 0x2c)) {
    lVar5 = *(long *)(param_1 + 0x20);
    uVar3 = *(uint *)(param_1 + 0x38);
    do {
      uVar6 = uVar3;
      if (*(uint *)(param_1 + 0x2c) <= uVar6) {
        uVar6 = 0;
      }
      uVar2 = 1 << (ulong)(uVar6 & 0x1f);
      uVar3 = uVar6 + 1;
    } while ((uVar2 & *(uint *)(lVar5 + (ulong)(uVar6 >> 5) * 4)) != 0);
    uVar8 = *(long *)(param_1 + 0x40) + (ulong)uVar6 * 0x38;
    uVar9 = uVar8;
    do {
      uVar10 = uVar9 + 0x7f & 0xffffffffffffff81;
      Hint_Prefetch(uVar9,0,2,0);
      uVar9 = uVar10;
    } while (uVar10 < uVar8 + 0x38);
    lVar7 = (ulong)(uVar6 >> 5) * 4;
    *(uint *)(param_1 + 0x38) = uVar6 + 1;
    *(uint *)(param_1 + 0x3c) = *(uint *)(param_1 + 0x3c) + 1;
    *(uint *)(lVar5 + lVar7) = *(uint *)(lVar5 + lVar7) | uVar2;
    plVar4 = (long *)(*(long *)(param_1 + 0x40) + (ulong)uVar6 * 0x38);
    puVar1 = PTR__ZTVN4Aska8AUIDNodeE_02cbb428 + 0x10;
    plVar4[4] = 0;
    plVar4[3] = 0;
    plVar4[2] = 0;
    plVar4[1] = 0;
    *plVar4 = (long)puVar1;
    plVar4 = (long *)(*(long *)(param_1 + 0x40) + (ulong)uVar6 * 0x38);
    if (plVar4 == (long *)0x0) goto code_r0x0202e7d8;
  }
  else {
code_r0x0202e7d8:
    plVar4 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x38,PTR__ZSt7nothrow_02cb9a80);
    puVar1 = PTR__ZTVN4Aska8AUIDNodeE_02cbb428;
    if (plVar4 == (long *)0x0) {
      return (long *)0x0;
    }
    plVar4[4] = 0;
    plVar4[3] = 0;
    plVar4[2] = 0;
    plVar4[1] = 0;
    *plVar4 = (long)(puVar1 + 0x10);
  }
  *(int *)(param_1 + 0x8c) = *(int *)(param_1 + 0x8c) + 1;
  if (*(long *)(param_1 + 0x70) == 0) {
    *(long **)(param_1 + 0x70) = plVar4;
    lVar5 = *(long *)(param_1 + 0x78);
    if (lVar5 == 0) {
      lVar7 = 0;
      goto code_r0x0202e830;
    }
  }
  else {
    lVar5 = *(long *)(param_1 + 0x78);
    lVar7 = 0;
    if (lVar5 == 0) goto code_r0x0202e830;
  }
  *(long **)(lVar5 + 0x10) = plVar4;
  lVar7 = *(long *)(param_1 + 0x78);
code_r0x0202e830:
  plVar4[1] = lVar7;
  plVar4[2] = 0;
  *(long **)(param_1 + 0x78) = plVar4;
  (**(code **)(*plVar4 + 0x28))(plVar4,param_2);
  (**(code **)(*plVar4 + 0x10))(plVar4);
  return plVar4;
}

// ==== Aska::TBinaryTree<Aska::AUIDNode>::FreeNode(Aska::AUIDNode**)
// vaddr 0x1f2e87c | ghidra 0x202e87c | size 408 | symbol _ZN4Aska11TBinaryTreeINS_8AUIDNodeEE8FreeNodeEPPS1_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11TBinaryTreeINS_8AUIDNodeEE8FreeNodeEPPS1_(long *param_1,ulong *param_2)

{
  long *plVar1;
  ulong uVar2;
  long *plVar3;
  long lVar4;
  
  uVar2 = *param_2;
  if (uVar2 != 0) {
    if (param_1[0xe] == uVar2) {
      param_1[0xe] = *(long *)(uVar2 + 0x10);
      uVar2 = *param_2;
    }
    if (param_1[0xf] == uVar2) {
      param_1[0xf] = *(long *)(uVar2 + 8);
      uVar2 = *param_2;
    }
    if (param_1[0x10] == uVar2) {
      param_1[0x10] = *(long *)(uVar2 + 8);
      uVar2 = *param_2;
    }
    lVar4 = *(long *)(uVar2 + 0x10);
    if (*(long *)(uVar2 + 8) != 0) {
      *(long *)(*(long *)(uVar2 + 8) + 0x10) = lVar4;
    }
    if (lVar4 != 0) {
      *(undefined8 *)(lVar4 + 8) = *(undefined8 *)(*param_2 + 8);
    }
    *(undefined8 *)(*param_2 + 0x10) = 0;
    *(undefined8 *)(*param_2 + 8) = 0;
    plVar1 = (long *)*param_2;
    if (plVar1[4] != 0) {
      (**(code **)(*param_1 + 0x18))(param_1);
      plVar1 = (long *)*param_2;
    }
    if (plVar1[3] != 0) {
      (**(code **)(*param_1 + 0x18))(param_1);
      plVar1 = (long *)*param_2;
    }
    (**(code **)(*plVar1 + 0x18))();
    *(int *)((long)param_1 + 0x8c) = *(int *)((long)param_1 + 0x8c) + -1;
    plVar3 = (long *)param_1[8];
    plVar1 = (long *)*param_2;
    if (((plVar3 == (long *)0x0) || (plVar1 < plVar3)) ||
       (plVar3 + (ulong)*(uint *)((long)param_1 + 0x2c) * 7 <= plVar1)) {
      if (plVar1 != (long *)0x0) {
        (**(code **)(*plVar1 + 8))();
      }
    }
    else {
      uVar2 = ((long)plVar1 - (long)plVar3 >> 3) * 0x6db6db6db6db6db7;
      (**(code **)plVar3[(uVar2 & 0xffffffff) * 7])();
      lVar4 = (uVar2 >> 5 & 0x7ffffff) * 4;
      *(uint *)(param_1[4] + lVar4) =
           *(uint *)(param_1[4] + lVar4) & (1 << (ulong)((uint)uVar2 & 0x1f) ^ 0xffffffffU);
      *(int *)((long)param_1 + 0x3c) = *(int *)((long)param_1 + 0x3c) + -1;
    }
    *param_2 = 0;
  }
  return;
}

// ==== Aska::TBinaryTree<Aska::MappedMemoryPointer>::AllocNode(void const*)
// vaddr 0x1f2ef14 | ghidra 0x202ef14 | size 376 | symbol _ZN4Aska11TBinaryTreeINS_19MappedMemoryPointerEE9AllocNodeEPKv | lib libSOA-3.7.0.so | 2026-10-04
long * _ZN4Aska11TBinaryTreeINS_19MappedMemoryPointerEE9AllocNodeEPKv
                 (long param_1,undefined8 param_2)

{
  undefined *puVar1;
  uint uVar2;
  uint uVar3;
  long *plVar4;
  long lVar5;
  uint uVar6;
  long lVar7;
  ulong uVar8;
  ulong uVar9;
  ulong uVar10;
  
  if (*(uint *)(param_1 + 0x3c) < *(uint *)(param_1 + 0x2c)) {
    lVar5 = *(long *)(param_1 + 0x20);
    uVar3 = *(uint *)(param_1 + 0x38);
    do {
      uVar6 = uVar3;
      if (*(uint *)(param_1 + 0x2c) <= uVar6) {
        uVar6 = 0;
      }
      uVar2 = 1 << (ulong)(uVar6 & 0x1f);
      uVar3 = uVar6 + 1;
    } while ((uVar2 & *(uint *)(lVar5 + (ulong)(uVar6 >> 5) * 4)) != 0);
    uVar8 = *(long *)(param_1 + 0x40) + (ulong)uVar6 * 0x50;
    uVar9 = uVar8;
    do {
      uVar10 = uVar9 + 0x7f & 0xffffffffffffff81;
      Hint_Prefetch(uVar9,0,2,0);
      uVar9 = uVar10;
    } while (uVar10 < uVar8 + 0x50);
    lVar7 = (ulong)(uVar6 >> 5) * 4;
    *(uint *)(param_1 + 0x38) = uVar6 + 1;
    *(uint *)(param_1 + 0x3c) = *(uint *)(param_1 + 0x3c) + 1;
    *(uint *)(lVar5 + lVar7) = *(uint *)(lVar5 + lVar7) | uVar2;
    plVar4 = (long *)(*(long *)(param_1 + 0x40) + (ulong)uVar6 * 0x50);
    puVar1 = PTR__ZTVN4Aska19MappedMemoryPointerE_02cc34c0 + 0x10;
    plVar4[4] = 0;
    plVar4[3] = 0;
    plVar4[2] = 0;
    plVar4[1] = 0;
    plVar4[8] = 0;
    plVar4[9] = 0;
    *plVar4 = (long)puVar1;
    plVar4 = (long *)(*(long *)(param_1 + 0x40) + (ulong)uVar6 * 0x50);
    if (plVar4 == (long *)0x0) goto code_r0x0202efe4;
  }
  else {
code_r0x0202efe4:
    plVar4 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x50,PTR__ZSt7nothrow_02cb9a80);
    if (plVar4 == (long *)0x0) {
      return (long *)0x0;
    }
    plVar4[8] = 0;
    plVar4[9] = 0;
    puVar1 = PTR__ZTVN4Aska19MappedMemoryPointerE_02cc34c0;
    plVar4[4] = 0;
    plVar4[3] = 0;
    plVar4[2] = 0;
    plVar4[1] = 0;
    *plVar4 = (long)(puVar1 + 0x10);
  }
  *(int *)(param_1 + 0x8c) = *(int *)(param_1 + 0x8c) + 1;
  if (*(long *)(param_1 + 0x70) == 0) {
    *(long **)(param_1 + 0x70) = plVar4;
    lVar5 = *(long *)(param_1 + 0x78);
    if (lVar5 == 0) {
      lVar7 = 0;
      goto code_r0x0202f040;
    }
  }
  else {
    lVar5 = *(long *)(param_1 + 0x78);
    lVar7 = 0;
    if (lVar5 == 0) goto code_r0x0202f040;
  }
  *(long **)(lVar5 + 0x10) = plVar4;
  lVar7 = *(long *)(param_1 + 0x78);
code_r0x0202f040:
  plVar4[1] = lVar7;
  plVar4[2] = 0;
  *(long **)(param_1 + 0x78) = plVar4;
  (**(code **)(*plVar4 + 0x28))(plVar4,param_2);
  (**(code **)(*plVar4 + 0x10))(plVar4);
  return plVar4;
}

// ==== Aska::TBinaryTree<Aska::MappedMemoryRelation>::AllocNode(void const*)
// vaddr 0x1f2f638 | ghidra 0x202f638 | size 472 | symbol _ZN4Aska11TBinaryTreeINS_20MappedMemoryRelationEE9AllocNodeEPKv | lib libSOA-3.7.0.so | 2026-10-04
long * _ZN4Aska11TBinaryTreeINS_20MappedMemoryRelationEE9AllocNodeEPKv
                 (long param_1,undefined8 param_2)

{
  undefined *puVar1;
  undefined *puVar2;
  uint uVar3;
  undefined *puVar4;
  uint uVar5;
  long *plVar6;
  long lVar7;
  uint uVar8;
  long lVar9;
  ulong uVar10;
  ulong uVar11;
  ulong uVar12;
  
  if (*(uint *)(param_1 + 0x3c) < *(uint *)(param_1 + 0x2c)) {
    lVar7 = *(long *)(param_1 + 0x20);
    uVar5 = *(uint *)(param_1 + 0x38);
    do {
      uVar8 = uVar5;
      if (*(uint *)(param_1 + 0x2c) <= uVar8) {
        uVar8 = 0;
      }
      uVar3 = 1 << (ulong)(uVar8 & 0x1f);
      uVar5 = uVar8 + 1;
    } while ((uVar3 & *(uint *)(lVar7 + (ulong)(uVar8 >> 5) * 4)) != 0);
    uVar10 = *(long *)(param_1 + 0x40) + (ulong)uVar8 * 0x648;
    uVar11 = uVar10;
    do {
      uVar12 = uVar11 + 0x7f & 0xffffffffffffff81;
      Hint_Prefetch(uVar11,0,2,0);
      uVar11 = uVar12;
    } while (uVar12 < uVar10 + 0x400);
    lVar9 = (ulong)(uVar8 >> 5) * 4;
    *(uint *)(param_1 + 0x38) = uVar8 + 1;
    *(uint *)(param_1 + 0x3c) = *(uint *)(param_1 + 0x3c) + 1;
    puVar4 = PTR__ZTVN4Aska20MappedMemoryRelationE_02cc4cf0;
    *(uint *)(lVar7 + lVar9) = *(uint *)(lVar7 + lVar9) | uVar3;
    puVar1 = PTR__ZTVN4Aska5TListINS_8AUIDElemEEE_02cc3dd0 + 0x10;
    puVar2 = PTR__ZTVN4Aska8AUIDElemE_02cb7e98 + 0x10;
    plVar6 = (long *)(*(long *)(param_1 + 0x40) + (ulong)uVar8 * 0x648);
    plVar6[4] = 0;
    plVar6[3] = 0;
    plVar6[2] = 0;
    plVar6[1] = 0;
    *plVar6 = (long)(puVar4 + 0x10);
    plVar6[0xc3] = (long)puVar2;
    plVar6[0xc2] = (long)puVar1;
    *(undefined4 *)(plVar6 + 200) = 0;
    plVar6[0xc4] = (long)(plVar6 + 0xc3);
    plVar6[0xc5] = (long)(plVar6 + 0xc3);
    plVar6 = (long *)(*(long *)(param_1 + 0x40) + (ulong)uVar8 * 0x648);
    if (plVar6 == (long *)0x0) goto code_r0x0202f738;
  }
  else {
code_r0x0202f738:
    plVar6 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x648,PTR__ZSt7nothrow_02cb9a80);
    if (plVar6 == (long *)0x0) {
      return (long *)0x0;
    }
    *plVar6 = (long)(PTR__ZTVN4Aska20MappedMemoryRelationE_02cc4cf0 + 0x10);
    puVar2 = PTR__ZTVN4Aska5TListINS_8AUIDElemEEE_02cc3dd0;
    plVar6[4] = 0;
    plVar6[3] = 0;
    plVar6[2] = 0;
    plVar6[1] = 0;
    puVar1 = PTR__ZTVN4Aska8AUIDElemE_02cb7e98;
    *(undefined4 *)(plVar6 + 200) = 0;
    plVar6[0xc4] = (long)(plVar6 + 0xc3);
    plVar6[0xc5] = (long)(plVar6 + 0xc3);
    plVar6[0xc3] = (long)(puVar1 + 0x10);
    plVar6[0xc2] = (long)(puVar2 + 0x10);
  }
  *(int *)(param_1 + 0x8c) = *(int *)(param_1 + 0x8c) + 1;
  if (*(long *)(param_1 + 0x70) == 0) {
    *(long **)(param_1 + 0x70) = plVar6;
    lVar7 = *(long *)(param_1 + 0x78);
    if (lVar7 == 0) {
      lVar9 = 0;
      goto code_r0x0202f7c4;
    }
  }
  else {
    lVar7 = *(long *)(param_1 + 0x78);
    lVar9 = 0;
    if (lVar7 == 0) goto code_r0x0202f7c4;
  }
  *(long **)(lVar7 + 0x10) = plVar6;
  lVar9 = *(long *)(param_1 + 0x78);
code_r0x0202f7c4:
  plVar6[1] = lVar9;
  plVar6[2] = 0;
  *(long **)(param_1 + 0x78) = plVar6;
  (**(code **)(*plVar6 + 0x28))(plVar6,param_2);
  (**(code **)(*plVar6 + 0x10))(plVar6);
  return plVar6;
}

// ==== Aska::TBinaryTree<Aska::MappedMemoryRelation>::FreeNode(Aska::MappedMemoryRelation**)
// vaddr 0x1f2f810 | ghidra 0x202f810 | size 408 | symbol _ZN4Aska11TBinaryTreeINS_20MappedMemoryRelationEE8FreeNodeEPPS1_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11TBinaryTreeINS_20MappedMemoryRelationEE8FreeNodeEPPS1_(long *param_1,ulong *param_2)

{
  long *plVar1;
  ulong uVar2;
  long *plVar3;
  long lVar4;
  
  uVar2 = *param_2;
  if (uVar2 != 0) {
    if (param_1[0xe] == uVar2) {
      param_1[0xe] = *(long *)(uVar2 + 0x10);
      uVar2 = *param_2;
    }
    if (param_1[0xf] == uVar2) {
      param_1[0xf] = *(long *)(uVar2 + 8);
      uVar2 = *param_2;
    }
    if (param_1[0x10] == uVar2) {
      param_1[0x10] = *(long *)(uVar2 + 8);
      uVar2 = *param_2;
    }
    lVar4 = *(long *)(uVar2 + 0x10);
    if (*(long *)(uVar2 + 8) != 0) {
      *(long *)(*(long *)(uVar2 + 8) + 0x10) = lVar4;
    }
    if (lVar4 != 0) {
      *(undefined8 *)(lVar4 + 8) = *(undefined8 *)(*param_2 + 8);
    }
    *(undefined8 *)(*param_2 + 0x10) = 0;
    *(undefined8 *)(*param_2 + 8) = 0;
    plVar1 = (long *)*param_2;
    if (plVar1[4] != 0) {
      (**(code **)(*param_1 + 0x18))(param_1);
      plVar1 = (long *)*param_2;
    }
    if (plVar1[3] != 0) {
      (**(code **)(*param_1 + 0x18))(param_1);
      plVar1 = (long *)*param_2;
    }
    (**(code **)(*plVar1 + 0x18))();
    *(int *)((long)param_1 + 0x8c) = *(int *)((long)param_1 + 0x8c) + -1;
    plVar3 = (long *)param_1[8];
    plVar1 = (long *)*param_2;
    if (((plVar3 == (long *)0x0) || (plVar1 < plVar3)) ||
       (plVar3 + (ulong)*(uint *)((long)param_1 + 0x2c) * 0xc9 <= plVar1)) {
      if (plVar1 != (long *)0x0) {
        (**(code **)(*plVar1 + 8))();
      }
    }
    else {
      uVar2 = ((long)plVar1 - (long)plVar3 >> 3) * -0x51832f1fd73e687;
      (**(code **)plVar3[(uVar2 & 0xffffffff) * 0xc9])();
      lVar4 = (uVar2 >> 5 & 0x7ffffff) * 4;
      *(uint *)(param_1[4] + lVar4) =
           *(uint *)(param_1[4] + lVar4) & (1 << (ulong)((uint)uVar2 & 0x1f) ^ 0xffffffffU);
      *(int *)((long)param_1 + 0x3c) = *(int *)((long)param_1 + 0x3c) + -1;
    }
    *param_2 = 0;
  }
  return;
}

// ==== Aska::TBinaryTree<Aska::MappedMemoryLocation>::AllocNode(void const*)
// vaddr 0x1f2fde4 | ghidra 0x202fde4 | size 384 | symbol _ZN4Aska11TBinaryTreeINS_20MappedMemoryLocationEE9AllocNodeEPKv | lib libSOA-3.7.0.so | 2026-10-04
long * _ZN4Aska11TBinaryTreeINS_20MappedMemoryLocationEE9AllocNodeEPKv
                 (long param_1,undefined8 param_2)

{
  undefined *puVar1;
  ulong uVar2;
  uint uVar3;
  uint uVar4;
  long *plVar5;
  long lVar6;
  uint uVar7;
  long lVar8;
  long lVar9;
  ulong uVar10;
  ulong uVar11;
  
  if (*(uint *)(param_1 + 0x3c) < *(uint *)(param_1 + 0x2c)) {
    lVar6 = *(long *)(param_1 + 0x20);
    uVar4 = *(uint *)(param_1 + 0x38);
    do {
      uVar7 = uVar4;
      if (*(uint *)(param_1 + 0x2c) <= uVar7) {
        uVar7 = 0;
      }
      uVar3 = 1 << (ulong)(uVar7 & 0x1f);
      uVar4 = uVar7 + 1;
    } while ((uVar3 & *(uint *)(lVar6 + (ulong)(uVar7 >> 5) * 4)) != 0);
    uVar2 = *(long *)(param_1 + 0x40) + (ulong)uVar7 * 0x80;
    uVar10 = uVar2;
    do {
      uVar11 = uVar10 + 0x7f & 0xffffffffffffff81;
      Hint_Prefetch(uVar10,0,2,0);
      uVar10 = uVar11;
    } while (uVar11 < uVar2 + 0x80);
    lVar9 = (ulong)(uVar7 >> 5) * 4;
    *(uint *)(param_1 + 0x38) = uVar7 + 1;
    *(uint *)(param_1 + 0x3c) = *(uint *)(param_1 + 0x3c) + 1;
    lVar8 = (ulong)uVar7 * 0x80;
    *(uint *)(lVar6 + lVar9) = *(uint *)(lVar6 + lVar9) | uVar3;
    plVar5 = (long *)(*(long *)(param_1 + 0x40) + lVar8);
    puVar1 = PTR__ZTVN4Aska20MappedMemoryLocationE_02cbeb40 + 0x10;
    plVar5[4] = 0;
    plVar5[3] = 0;
    plVar5[2] = 0;
    plVar5[1] = 0;
    plVar5[9] = 0;
    plVar5[10] = 0;
    *plVar5 = (long)puVar1;
    *(undefined2 *)(plVar5 + 0xb) = 0x13;
    plVar5 = (long *)(*(long *)(param_1 + 0x40) + lVar8);
    if (plVar5 == (long *)0x0) goto code_r0x0202feb4;
  }
  else {
code_r0x0202feb4:
    plVar5 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x80,PTR__ZSt7nothrow_02cb9a80);
    if (plVar5 == (long *)0x0) {
      return (long *)0x0;
    }
    plVar5[9] = 0;
    plVar5[10] = 0;
    puVar1 = PTR__ZTVN4Aska20MappedMemoryLocationE_02cbeb40;
    plVar5[4] = 0;
    plVar5[3] = 0;
    plVar5[2] = 0;
    plVar5[1] = 0;
    *plVar5 = (long)(puVar1 + 0x10);
    *(undefined2 *)(plVar5 + 0xb) = 0x13;
  }
  *(int *)(param_1 + 0x8c) = *(int *)(param_1 + 0x8c) + 1;
  if (*(long *)(param_1 + 0x70) == 0) {
    *(long **)(param_1 + 0x70) = plVar5;
    lVar6 = *(long *)(param_1 + 0x78);
    if (lVar6 == 0) {
      lVar8 = 0;
      goto code_r0x0202ff18;
    }
  }
  else {
    lVar6 = *(long *)(param_1 + 0x78);
    lVar8 = 0;
    if (lVar6 == 0) goto code_r0x0202ff18;
  }
  *(long **)(lVar6 + 0x10) = plVar5;
  lVar8 = *(long *)(param_1 + 0x78);
code_r0x0202ff18:
  plVar5[1] = lVar8;
  plVar5[2] = 0;
  *(long **)(param_1 + 0x78) = plVar5;
  (**(code **)(*plVar5 + 0x28))(plVar5,param_2);
  (**(code **)(*plVar5 + 0x10))(plVar5);
  return plVar5;
}

// ==== Aska::TBinaryTree<Aska::MappedMemoryIdentifier>::AllocNode(void const*)
// vaddr 0x1f30720 | ghidra 0x2030720 | size 376 | symbol _ZN4Aska11TBinaryTreeINS_22MappedMemoryIdentifierEE9AllocNodeEPKv | lib libSOA-3.7.0.so | 2026-10-04
long * _ZN4Aska11TBinaryTreeINS_22MappedMemoryIdentifierEE9AllocNodeEPKv
                 (long param_1,undefined8 param_2)

{
  undefined *puVar1;
  uint uVar2;
  uint uVar3;
  long *plVar4;
  long lVar5;
  uint uVar6;
  long lVar7;
  ulong uVar8;
  ulong uVar9;
  ulong uVar10;
  
  if (*(uint *)(param_1 + 0x3c) < *(uint *)(param_1 + 0x2c)) {
    lVar5 = *(long *)(param_1 + 0x20);
    uVar3 = *(uint *)(param_1 + 0x38);
    do {
      uVar6 = uVar3;
      if (*(uint *)(param_1 + 0x2c) <= uVar6) {
        uVar6 = 0;
      }
      uVar2 = 1 << (ulong)(uVar6 & 0x1f);
      uVar3 = uVar6 + 1;
    } while ((uVar2 & *(uint *)(lVar5 + (ulong)(uVar6 >> 5) * 4)) != 0);
    uVar8 = *(long *)(param_1 + 0x40) + (ulong)uVar6 * 0x50;
    uVar9 = uVar8;
    do {
      uVar10 = uVar9 + 0x7f & 0xffffffffffffff81;
      Hint_Prefetch(uVar9,0,2,0);
      uVar9 = uVar10;
    } while (uVar10 < uVar8 + 0x50);
    lVar7 = (ulong)(uVar6 >> 5) * 4;
    *(uint *)(param_1 + 0x38) = uVar6 + 1;
    *(uint *)(param_1 + 0x3c) = *(uint *)(param_1 + 0x3c) + 1;
    *(uint *)(lVar5 + lVar7) = *(uint *)(lVar5 + lVar7) | uVar2;
    plVar4 = (long *)(*(long *)(param_1 + 0x40) + (ulong)uVar6 * 0x50);
    puVar1 = PTR__ZTVN4Aska22MappedMemoryIdentifierE_02cbad38 + 0x10;
    plVar4[4] = 0;
    plVar4[3] = 0;
    plVar4[2] = 0;
    plVar4[1] = 0;
    plVar4[8] = 0;
    plVar4[9] = 0;
    *plVar4 = (long)puVar1;
    plVar4 = (long *)(*(long *)(param_1 + 0x40) + (ulong)uVar6 * 0x50);
    if (plVar4 == (long *)0x0) goto code_r0x020307f0;
  }
  else {
code_r0x020307f0:
    plVar4 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x50,PTR__ZSt7nothrow_02cb9a80);
    if (plVar4 == (long *)0x0) {
      return (long *)0x0;
    }
    plVar4[8] = 0;
    plVar4[9] = 0;
    puVar1 = PTR__ZTVN4Aska22MappedMemoryIdentifierE_02cbad38;
    plVar4[4] = 0;
    plVar4[3] = 0;
    plVar4[2] = 0;
    plVar4[1] = 0;
    *plVar4 = (long)(puVar1 + 0x10);
  }
  *(int *)(param_1 + 0x8c) = *(int *)(param_1 + 0x8c) + 1;
  if (*(long *)(param_1 + 0x70) == 0) {
    *(long **)(param_1 + 0x70) = plVar4;
    lVar5 = *(long *)(param_1 + 0x78);
    if (lVar5 == 0) {
      lVar7 = 0;
      goto code_r0x0203084c;
    }
  }
  else {
    lVar5 = *(long *)(param_1 + 0x78);
    lVar7 = 0;
    if (lVar5 == 0) goto code_r0x0203084c;
  }
  *(long **)(lVar5 + 0x10) = plVar4;
  lVar7 = *(long *)(param_1 + 0x78);
code_r0x0203084c:
  plVar4[1] = lVar7;
  plVar4[2] = 0;
  *(long **)(param_1 + 0x78) = plVar4;
  (**(code **)(*plVar4 + 0x28))(plVar4,param_2);
  (**(code **)(*plVar4 + 0x10))(plVar4);
  return plVar4;
}

// ==== Aska::TBinaryTree<Aska::AddressNode>::FreeTable()
// vaddr 0x1f310c4 | ghidra 0x20310c4 | size 536 | symbol _ZN4Aska11TBinaryTreeINS_11AddressNodeEE9FreeTableEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11TBinaryTreeINS_11AddressNodeEE9FreeTableEv(long *param_1)

{
  int iVar1;
  long lVar2;
  long *plVar3;
  long *plVar4;
  ulong uVar5;
  long *plVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  long *plVar10;
  
  iVar8 = *(int *)((long)param_1 + 0x8c);
  iVar1 = (int)param_1[0xb];
  plVar4 = (long *)param_1[10];
  if (iVar8 == *(int *)((long)param_1 + 0x3c)) {
    iVar9 = iVar8 + -1;
    if (0 < iVar8) {
      lVar2 = 0;
      uVar7 = 0;
      if (*(uint *)((long)param_1 + 0x2c) != 0) goto code_r0x0203112c;
      do {
        do {
          uVar7 = uVar7 + 1;
          lVar2 = lVar2 + 0x30;
        } while (*(uint *)((long)param_1 + 0x2c) <= uVar7);
code_r0x0203112c:
      } while ((*(uint *)(param_1[4] + (ulong)(uVar7 >> 5) * 4) & 1 << (ulong)(uVar7 & 0x1f)) == 0);
      Hint_Prefetch((long *)(param_1[8] + lVar2),0,2,0);
      plVar6 = (long *)(param_1[8] + lVar2);
      do {
        if (iVar9 < 1) {
          plVar10 = (long *)0x0;
        }
        else {
          do {
            do {
              uVar7 = uVar7 + 1;
            } while (*(uint *)((long)param_1 + 0x2c) <= uVar7);
          } while ((*(uint *)(param_1[4] + (ulong)(uVar7 >> 5) * 4) & 1 << (ulong)(uVar7 & 0x1f)) ==
                   0);
          plVar10 = (long *)(param_1[8] + (ulong)uVar7 * 0x30);
          Hint_Prefetch(plVar10,0,2,0);
          iVar9 = iVar9 + -1;
        }
        (**(code **)(*plVar6 + 0x18))(plVar6);
        plVar3 = (long *)param_1[8];
        if (((plVar3 != (long *)0x0) && (plVar3 <= plVar6)) &&
           (plVar6 < plVar3 + (ulong)*(uint *)((long)param_1 + 0x2c) * 6)) {
          uVar5 = ((long)plVar6 - (long)plVar3 >> 4) * -0x5555555555555555;
          (**(code **)plVar3[(uVar5 & 0xffffffff) * 6])();
          lVar2 = (uVar5 >> 5 & 0x7ffffff) * 4;
          *(uint *)(param_1[4] + lVar2) =
               *(uint *)(param_1[4] + lVar2) & (1 << (ulong)((uint)uVar5 & 0x1f) ^ 0xffffffffU);
          *(int *)((long)param_1 + 0x3c) = *(int *)((long)param_1 + 0x3c) + -1;
        }
        *(int *)((long)param_1 + 0x8c) = *(int *)((long)param_1 + 0x8c) + -1;
        plVar6 = plVar10;
      } while (plVar10 != (long *)0x0);
    }
  }
  else if (iVar1 != 0) {
    plVar6 = plVar4 + (iVar1 - 1);
    iVar8 = iVar1;
    do {
      (**(code **)(*param_1 + 0x18))(param_1,plVar6);
      iVar8 = iVar8 + -1;
      plVar6 = plVar6 + -1;
    } while (iVar8 != 0);
  }
  param_1[0xc] = 0;
  *(undefined4 *)(param_1 + 0xb) = 0;
  param_1[10] = 0;
  param_1[0xf] = 0;
  param_1[0x10] = 0;
  *(undefined1 *)(param_1 + 0x11) = 0;
  param_1[0xe] = 0;
  if (((plVar4 != (long *)0x0) && (iVar1 != 0)) && (plVar4 != param_1 + 0xd)) {
    (*(code *)PTR__ZdaPv_02cb5db8)(plVar4);
    return;
  }
  return;
}

// ==== Aska::TBinaryTree<Aska::AddressNode>::AllocNode(void const*)
// vaddr 0x1f31334 | ghidra 0x2031334 | size 368 | symbol _ZN4Aska11TBinaryTreeINS_11AddressNodeEE9AllocNodeEPKv | lib libSOA-3.7.0.so | 2026-10-04
long * _ZN4Aska11TBinaryTreeINS_11AddressNodeEE9AllocNodeEPKv(long param_1,undefined8 param_2)

{
  undefined *puVar1;
  uint uVar2;
  uint uVar3;
  long *plVar4;
  long lVar5;
  uint uVar6;
  long lVar7;
  ulong uVar8;
  ulong uVar9;
  ulong uVar10;
  
  if (*(uint *)(param_1 + 0x3c) < *(uint *)(param_1 + 0x2c)) {
    lVar5 = *(long *)(param_1 + 0x20);
    uVar3 = *(uint *)(param_1 + 0x38);
    do {
      uVar6 = uVar3;
      if (*(uint *)(param_1 + 0x2c) <= uVar6) {
        uVar6 = 0;
      }
      uVar2 = 1 << (ulong)(uVar6 & 0x1f);
      uVar3 = uVar6 + 1;
    } while ((uVar2 & *(uint *)(lVar5 + (ulong)(uVar6 >> 5) * 4)) != 0);
    uVar8 = *(long *)(param_1 + 0x40) + (ulong)uVar6 * 0x30;
    uVar9 = uVar8;
    do {
      uVar10 = uVar9 + 0x7f & 0xffffffffffffff81;
      Hint_Prefetch(uVar9,0,2,0);
      uVar9 = uVar10;
    } while (uVar10 < uVar8 + 0x30);
    lVar7 = (ulong)(uVar6 >> 5) * 4;
    *(uint *)(param_1 + 0x38) = uVar6 + 1;
    *(uint *)(param_1 + 0x3c) = *(uint *)(param_1 + 0x3c) + 1;
    *(uint *)(lVar5 + lVar7) = *(uint *)(lVar5 + lVar7) | uVar2;
    plVar4 = (long *)(*(long *)(param_1 + 0x40) + (ulong)uVar6 * 0x30);
    puVar1 = PTR__ZTVN4Aska11AddressNodeE_02cb6f68 + 0x10;
    plVar4[4] = 0;
    plVar4[3] = 0;
    plVar4[2] = 0;
    plVar4[1] = 0;
    *plVar4 = (long)puVar1;
    plVar4 = (long *)(*(long *)(param_1 + 0x40) + (ulong)uVar6 * 0x30);
    if (plVar4 == (long *)0x0) goto code_r0x02031400;
  }
  else {
code_r0x02031400:
    plVar4 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x30,PTR__ZSt7nothrow_02cb9a80);
    puVar1 = PTR__ZTVN4Aska11AddressNodeE_02cb6f68;
    if (plVar4 == (long *)0x0) {
      return (long *)0x0;
    }
    plVar4[4] = 0;
    plVar4[3] = 0;
    plVar4[2] = 0;
    plVar4[1] = 0;
    *plVar4 = (long)(puVar1 + 0x10);
  }
  *(int *)(param_1 + 0x8c) = *(int *)(param_1 + 0x8c) + 1;
  if (*(long *)(param_1 + 0x70) == 0) {
    *(long **)(param_1 + 0x70) = plVar4;
    lVar5 = *(long *)(param_1 + 0x78);
    if (lVar5 == 0) {
      lVar7 = 0;
      goto code_r0x02031458;
    }
  }
  else {
    lVar5 = *(long *)(param_1 + 0x78);
    lVar7 = 0;
    if (lVar5 == 0) goto code_r0x02031458;
  }
  *(long **)(lVar5 + 0x10) = plVar4;
  lVar7 = *(long *)(param_1 + 0x78);
code_r0x02031458:
  plVar4[1] = lVar7;
  plVar4[2] = 0;
  *(long **)(param_1 + 0x78) = plVar4;
  (**(code **)(*plVar4 + 0x28))(plVar4,param_2);
  (**(code **)(*plVar4 + 0x10))(plVar4);
  return plVar4;
}

// ==== Aska::TBinaryTree<Aska::AddressNode>::FreeNode(Aska::AddressNode**)
// vaddr 0x1f314a4 | ghidra 0x20314a4 | size 400 | symbol _ZN4Aska11TBinaryTreeINS_11AddressNodeEE8FreeNodeEPPS1_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11TBinaryTreeINS_11AddressNodeEE8FreeNodeEPPS1_(long *param_1,ulong *param_2)

{
  long *plVar1;
  ulong uVar2;
  long *plVar3;
  long lVar4;
  
  uVar2 = *param_2;
  if (uVar2 != 0) {
    if (param_1[0xe] == uVar2) {
      param_1[0xe] = *(long *)(uVar2 + 0x10);
      uVar2 = *param_2;
    }
    if (param_1[0xf] == uVar2) {
      param_1[0xf] = *(long *)(uVar2 + 8);
      uVar2 = *param_2;
    }
    if (param_1[0x10] == uVar2) {
      param_1[0x10] = *(long *)(uVar2 + 8);
      uVar2 = *param_2;
    }
    lVar4 = *(long *)(uVar2 + 0x10);
    if (*(long *)(uVar2 + 8) != 0) {
      *(long *)(*(long *)(uVar2 + 8) + 0x10) = lVar4;
    }
    if (lVar4 != 0) {
      *(undefined8 *)(lVar4 + 8) = *(undefined8 *)(*param_2 + 8);
    }
    *(undefined8 *)(*param_2 + 0x10) = 0;
    *(undefined8 *)(*param_2 + 8) = 0;
    plVar1 = (long *)*param_2;
    if (plVar1[4] != 0) {
      (**(code **)(*param_1 + 0x18))(param_1);
      plVar1 = (long *)*param_2;
    }
    if (plVar1[3] != 0) {
      (**(code **)(*param_1 + 0x18))(param_1);
      plVar1 = (long *)*param_2;
    }
    (**(code **)(*plVar1 + 0x18))();
    *(int *)((long)param_1 + 0x8c) = *(int *)((long)param_1 + 0x8c) + -1;
    plVar3 = (long *)param_1[8];
    plVar1 = (long *)*param_2;
    if (((plVar3 == (long *)0x0) || (plVar1 < plVar3)) ||
       (plVar3 + (ulong)*(uint *)((long)param_1 + 0x2c) * 6 <= plVar1)) {
      if (plVar1 != (long *)0x0) {
        (**(code **)(*plVar1 + 8))();
      }
    }
    else {
      uVar2 = ((long)plVar1 - (long)plVar3 >> 4) * -0x5555555555555555;
      (**(code **)plVar3[(uVar2 & 0xffffffff) * 6])();
      lVar4 = (uVar2 >> 5 & 0x7ffffff) * 4;
      *(uint *)(param_1[4] + lVar4) =
           *(uint *)(param_1[4] + lVar4) & (1 << (ulong)((uint)uVar2 & 0x1f) ^ 0xffffffffU);
      *(int *)((long)param_1 + 0x3c) = *(int *)((long)param_1 + 0x3c) + -1;
    }
    *param_2 = 0;
  }
  return;
}

// ==== Aska::TBinaryTree<Aska::AddressNode>::~TBinaryTree()
// vaddr 0x1f31b80 | ghidra 0x2031b80 | size 240 | symbol _ZN4Aska11TBinaryTreeINS_11AddressNodeEED2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11TBinaryTreeINS_11AddressNodeEED2Ev(long *param_1)

{
  undefined *puVar1;
  long *plVar2;
  
  *param_1 = (long)(PTR__ZTVN4Aska11TBinaryTreeINS_11AddressNodeEEE_02cb9e00 + 0x10);
  Aska::TBinaryTree<Aska::AddressNode>::FreeTable()();
  plVar2 = param_1 + 4;
  *param_1 = (long)(PTR__ZTVN4Aska11TPoolLegacyINS_11AddressNodeELb0EEE_02cb9ff8 + 0x10);
  if ((*plVar2 != 0) && ((char)param_1[6] != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 6) = 0;
  }
  *plVar2 = 0;
  param_1[5] = 0;
  param_1[7] = 0;
  if (param_1[8] == 0) {
    param_1[2] = (long)(PTR__ZTVN4Aska9TBitArrayIjLb0EEE_02cba038 + 0x10);
  }
  else if ((char)param_1[9] == '\0') {
    param_1[2] = (long)(PTR__ZTVN4Aska9TBitArrayIjLb0EEE_02cba038 + 0x10);
    param_1[8] = 0;
  }
  else {
    operator delete[](void*)();
    param_1[2] = (long)(PTR__ZTVN4Aska9TBitArrayIjLb0EEE_02cba038 + 0x10);
    param_1[8] = 0;
    if ((param_1[4] != 0) && ((char)param_1[6] != '\0')) {
      operator delete[](void*)();
      *(undefined1 *)(param_1 + 6) = 0;
    }
  }
  *plVar2 = 0;
  param_1[5] = 0;
  puVar1 = PTR__ZTVN4Aska13TSmartPointerILb0EEE_02cc2320 + 0x10;
  param_1[2] = (long)puVar1;
  *param_1 = (long)puVar1;
  return;
}

// ==== Aska::TBinaryNode<32u>::~TBinaryNode()
// vaddr 0x1f36e68 | ghidra 0x2036e68 | size 4 | symbol _ZN4Aska11TBinaryNodeILj32EED2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11TBinaryNodeILj32EED2Ev(void)

{
  return;
}

// ==== Aska::TBinaryNode<8u>::Compare(void const*)
// vaddr 0x1f50efc | ghidra 0x2050efc | size 36 | symbol _ZN4Aska11TBinaryNodeILj8EE7CompareEPKv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11TBinaryNodeILj8EE7CompareEPKv(long *param_1,undefined8 param_2)

{
  undefined8 uVar1;
  
  uVar1 = (**(code **)(*param_1 + 0x30))();
  (*(code *)PTR_strcmp_02c937a8)(param_2,uVar1);
  return;
}

// ==== Aska::TBinaryTree<Aska::ClassNameSet>::AllocNode(void const*)
// vaddr 0x1f50f88 | ghidra 0x2050f88 | size 368 | symbol _ZN4Aska11TBinaryTreeINS_12ClassNameSetEE9AllocNodeEPKv | lib libSOA-3.7.0.so | 2026-10-04
long * _ZN4Aska11TBinaryTreeINS_12ClassNameSetEE9AllocNodeEPKv(long param_1,undefined8 param_2)

{
  undefined *puVar1;
  ulong uVar2;
  uint uVar3;
  uint uVar4;
  long *plVar5;
  long lVar6;
  uint uVar7;
  long lVar8;
  long lVar9;
  ulong uVar10;
  ulong uVar11;
  
  if (*(uint *)(param_1 + 0x3c) < *(uint *)(param_1 + 0x2c)) {
    lVar6 = *(long *)(param_1 + 0x20);
    uVar4 = *(uint *)(param_1 + 0x38);
    do {
      uVar7 = uVar4;
      if (*(uint *)(param_1 + 0x2c) <= uVar7) {
        uVar7 = 0;
      }
      uVar3 = 1 << (ulong)(uVar7 & 0x1f);
      uVar4 = uVar7 + 1;
    } while ((uVar3 & *(uint *)(lVar6 + (ulong)(uVar7 >> 5) * 4)) != 0);
    uVar2 = *(long *)(param_1 + 0x40) + (ulong)uVar7 * 0x40;
    uVar10 = uVar2;
    do {
      uVar11 = uVar10 + 0x7f & 0xffffffffffffff81;
      Hint_Prefetch(uVar10,0,2,0);
      uVar10 = uVar11;
    } while (uVar11 < uVar2 + 0x40);
    lVar9 = (ulong)(uVar7 >> 5) * 4;
    *(uint *)(param_1 + 0x38) = uVar7 + 1;
    *(uint *)(param_1 + 0x3c) = *(uint *)(param_1 + 0x3c) + 1;
    lVar8 = (ulong)uVar7 * 0x40;
    *(uint *)(lVar6 + lVar9) = *(uint *)(lVar6 + lVar9) | uVar3;
    plVar5 = (long *)(*(long *)(param_1 + 0x40) + lVar8);
    puVar1 = PTR__ZTVN4Aska12ClassNameSetE_02cc1b38 + 0x10;
    plVar5[4] = 0;
    plVar5[3] = 0;
    plVar5[2] = 0;
    plVar5[1] = 0;
    *plVar5 = (long)puVar1;
    plVar5[5] = 0;
    plVar5[6] = 0;
    plVar5 = (long *)(*(long *)(param_1 + 0x40) + lVar8);
    if (plVar5 == (long *)0x0) goto code_r0x02051050;
  }
  else {
code_r0x02051050:
    plVar5 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x40,PTR__ZSt7nothrow_02cb9a80);
    puVar1 = PTR__ZTVN4Aska12ClassNameSetE_02cc1b38;
    if (plVar5 == (long *)0x0) {
      return (long *)0x0;
    }
    plVar5[4] = 0;
    plVar5[3] = 0;
    plVar5[2] = 0;
    plVar5[1] = 0;
    *plVar5 = (long)(puVar1 + 0x10);
    plVar5[5] = 0;
    plVar5[6] = 0;
  }
  *(int *)(param_1 + 0x8c) = *(int *)(param_1 + 0x8c) + 1;
  if (*(long *)(param_1 + 0x70) == 0) {
    *(long **)(param_1 + 0x70) = plVar5;
    lVar6 = *(long *)(param_1 + 0x78);
    if (lVar6 == 0) {
      lVar8 = 0;
      goto code_r0x020510ac;
    }
  }
  else {
    lVar6 = *(long *)(param_1 + 0x78);
    lVar8 = 0;
    if (lVar6 == 0) goto code_r0x020510ac;
  }
  *(long **)(lVar6 + 0x10) = plVar5;
  lVar8 = *(long *)(param_1 + 0x78);
code_r0x020510ac:
  plVar5[1] = lVar8;
  plVar5[2] = 0;
  *(long **)(param_1 + 0x78) = plVar5;
  (**(code **)(*plVar5 + 0x28))(plVar5,param_2);
  (**(code **)(*plVar5 + 0x10))(plVar5);
  return plVar5;
}

// ==== Aska::TBinaryTree<Aska::ParamNameSet>::AllocNode(void const*)
// vaddr 0x1f52198 | ghidra 0x2052198 | size 368 | symbol _ZN4Aska11TBinaryTreeINS_12ParamNameSetEE9AllocNodeEPKv | lib libSOA-3.7.0.so | 2026-10-04
long * _ZN4Aska11TBinaryTreeINS_12ParamNameSetEE9AllocNodeEPKv(long param_1,undefined8 param_2)

{
  undefined *puVar1;
  ulong uVar2;
  uint uVar3;
  uint uVar4;
  long *plVar5;
  long lVar6;
  uint uVar7;
  long lVar8;
  long lVar9;
  ulong uVar10;
  ulong uVar11;
  
  if (*(uint *)(param_1 + 0x3c) < *(uint *)(param_1 + 0x2c)) {
    lVar6 = *(long *)(param_1 + 0x20);
    uVar4 = *(uint *)(param_1 + 0x38);
    do {
      uVar7 = uVar4;
      if (*(uint *)(param_1 + 0x2c) <= uVar7) {
        uVar7 = 0;
      }
      uVar3 = 1 << (ulong)(uVar7 & 0x1f);
      uVar4 = uVar7 + 1;
    } while ((uVar3 & *(uint *)(lVar6 + (ulong)(uVar7 >> 5) * 4)) != 0);
    uVar2 = *(long *)(param_1 + 0x40) + (ulong)uVar7 * 0x40;
    uVar10 = uVar2;
    do {
      uVar11 = uVar10 + 0x7f & 0xffffffffffffff81;
      Hint_Prefetch(uVar10,0,2,0);
      uVar10 = uVar11;
    } while (uVar11 < uVar2 + 0x40);
    lVar9 = (ulong)(uVar7 >> 5) * 4;
    *(uint *)(param_1 + 0x38) = uVar7 + 1;
    *(uint *)(param_1 + 0x3c) = *(uint *)(param_1 + 0x3c) + 1;
    lVar8 = (ulong)uVar7 * 0x40;
    *(uint *)(lVar6 + lVar9) = *(uint *)(lVar6 + lVar9) | uVar3;
    plVar5 = (long *)(*(long *)(param_1 + 0x40) + lVar8);
    puVar1 = PTR__ZTVN4Aska12ParamNameSetE_02cba840 + 0x10;
    plVar5[5] = 0;
    plVar5[4] = 0;
    plVar5[3] = 0;
    plVar5[2] = 0;
    plVar5[1] = 0;
    *plVar5 = (long)puVar1;
    plVar5 = (long *)(*(long *)(param_1 + 0x40) + lVar8);
    if (plVar5 == (long *)0x0) goto code_r0x02052260;
  }
  else {
code_r0x02052260:
    plVar5 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x40,PTR__ZSt7nothrow_02cb9a80);
    if (plVar5 == (long *)0x0) {
      return (long *)0x0;
    }
    plVar5[5] = 0;
    puVar1 = PTR__ZTVN4Aska12ParamNameSetE_02cba840;
    plVar5[4] = 0;
    plVar5[3] = 0;
    plVar5[2] = 0;
    plVar5[1] = 0;
    *plVar5 = (long)(puVar1 + 0x10);
  }
  *(int *)(param_1 + 0x8c) = *(int *)(param_1 + 0x8c) + 1;
  if (*(long *)(param_1 + 0x70) == 0) {
    *(long **)(param_1 + 0x70) = plVar5;
    lVar6 = *(long *)(param_1 + 0x78);
    if (lVar6 == 0) {
      lVar8 = 0;
      goto code_r0x020522bc;
    }
  }
  else {
    lVar6 = *(long *)(param_1 + 0x78);
    lVar8 = 0;
    if (lVar6 == 0) goto code_r0x020522bc;
  }
  *(long **)(lVar6 + 0x10) = plVar5;
  lVar8 = *(long *)(param_1 + 0x78);
code_r0x020522bc:
  plVar5[1] = lVar8;
  plVar5[2] = 0;
  *(long **)(param_1 + 0x78) = plVar5;
  (**(code **)(*plVar5 + 0x28))(plVar5,param_2);
  (**(code **)(*plVar5 + 0x10))(plVar5);
  return plVar5;
}

// ==== Aska::TDelegate<Aska::AaoStreamingStream>::operator()(void*)
// vaddr 0x1f75090 | ghidra 0x2075090 | size 60 | symbol _ZN4Aska9TDelegateINS_18AaoStreamingStreamEEclEPv | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska9TDelegateINS_18AaoStreamingStreamEEclEPv(long param_1,undefined8 param_2)

{
  int iVar1;
  long lVar2;
  code *UNRECOVERED_JUMPTABLE;
  
  if (*(long *)(param_1 + 8) != 0) {
    UNRECOVERED_JUMPTABLE = *(code **)(param_1 + 0x10);
    if ((*(ulong *)(param_1 + 0x18) & 1) != 0) {
      UNRECOVERED_JUMPTABLE =
           *(code **)(UNRECOVERED_JUMPTABLE +
                     *(long *)(*(long *)(param_1 + 8) + ((long)*(ulong *)(param_1 + 0x18) >> 1)));
    }
                    /* WARNING: Could not recover jumptable at 0x020750ac. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    lVar2 = (*UNRECOVERED_JUMPTABLE)();
    return lVar2;
  }
  iVar1 = (**(code **)(param_1 + 0x10))(param_2);
  return (long)iVar1;
}

// ==== Aska::TBinaryTree<Aska::AsfNode>::AllocNode(void const*)
// vaddr 0x20dfb48 | ghidra 0x21dfb48 | size 392 | symbol _ZN4Aska11TBinaryTreeINS_7AsfNodeEE9AllocNodeEPKv | lib libSOA-3.7.0.so | 2026-10-04
long * _ZN4Aska11TBinaryTreeINS_7AsfNodeEE9AllocNodeEPKv(long param_1,undefined8 param_2)

{
  undefined *puVar1;
  uint uVar2;
  uint uVar3;
  long *plVar4;
  long lVar5;
  uint uVar6;
  long lVar7;
  ulong uVar8;
  ulong uVar9;
  ulong uVar10;
  
  if (*(uint *)(param_1 + 0x3c) < *(uint *)(param_1 + 0x2c)) {
    lVar5 = *(long *)(param_1 + 0x20);
    uVar3 = *(uint *)(param_1 + 0x38);
    do {
      uVar6 = uVar3;
      if (*(uint *)(param_1 + 0x2c) <= uVar6) {
        uVar6 = 0;
      }
      uVar2 = 1 << (ulong)(uVar6 & 0x1f);
      uVar3 = uVar6 + 1;
    } while ((uVar2 & *(uint *)(lVar5 + (ulong)(uVar6 >> 5) * 4)) != 0);
    uVar8 = *(long *)(param_1 + 0x40) + (ulong)uVar6 * 0x50;
    uVar9 = uVar8;
    do {
      uVar10 = uVar9 + 0x7f & 0xffffffffffffff81;
      Hint_Prefetch(uVar9,0,2,0);
      uVar9 = uVar10;
    } while (uVar10 < uVar8 + 0x50);
    lVar7 = (ulong)(uVar6 >> 5) * 4;
    *(uint *)(param_1 + 0x38) = uVar6 + 1;
    *(uint *)(param_1 + 0x3c) = *(uint *)(param_1 + 0x3c) + 1;
    *(uint *)(lVar5 + lVar7) = *(uint *)(lVar5 + lVar7) | uVar2;
    plVar4 = (long *)(*(long *)(param_1 + 0x40) + (ulong)uVar6 * 0x50);
    puVar1 = PTR__ZTVN4Aska7AsfNodeE_02cb8560 + 0x10;
    plVar4[4] = 0;
    plVar4[3] = 0;
    plVar4[2] = 0;
    plVar4[1] = 0;
    *plVar4 = (long)puVar1;
    *(undefined4 *)(plVar4 + 9) = 0;
    plVar4[7] = 0;
    plVar4[8] = 0;
    plVar4[5] = 0;
    plVar4[6] = 0;
    plVar4 = (long *)(*(long *)(param_1 + 0x40) + (ulong)uVar6 * 0x50);
    if (plVar4 == (long *)0x0) goto code_r0x021dfc20;
  }
  else {
code_r0x021dfc20:
    plVar4 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x50,PTR__ZSt7nothrow_02cb9a80);
    puVar1 = PTR__ZTVN4Aska7AsfNodeE_02cb8560;
    if (plVar4 == (long *)0x0) {
      return (long *)0x0;
    }
    *(undefined4 *)(plVar4 + 9) = 0;
    plVar4[7] = 0;
    plVar4[8] = 0;
    plVar4[4] = 0;
    plVar4[3] = 0;
    plVar4[2] = 0;
    plVar4[1] = 0;
    *plVar4 = (long)(puVar1 + 0x10);
    plVar4[5] = 0;
    plVar4[6] = 0;
  }
  *(int *)(param_1 + 0x8c) = *(int *)(param_1 + 0x8c) + 1;
  if (*(long *)(param_1 + 0x70) == 0) {
    *(long **)(param_1 + 0x70) = plVar4;
    lVar5 = *(long *)(param_1 + 0x78);
    if (lVar5 == 0) {
      lVar7 = 0;
      goto code_r0x021dfc84;
    }
  }
  else {
    lVar5 = *(long *)(param_1 + 0x78);
    lVar7 = 0;
    if (lVar5 == 0) goto code_r0x021dfc84;
  }
  *(long **)(lVar5 + 0x10) = plVar4;
  lVar7 = *(long *)(param_1 + 0x78);
code_r0x021dfc84:
  plVar4[1] = lVar7;
  plVar4[2] = 0;
  *(long **)(param_1 + 0x78) = plVar4;
  (**(code **)(*plVar4 + 0x28))(plVar4,param_2);
  (**(code **)(*plVar4 + 0x10))(plVar4);
  return plVar4;
}

// ==== Aska::TBinaryTree<Aska::AsfNode>::~TBinaryTree()
// vaddr 0x20e03dc | ghidra 0x21e03dc | size 240 | symbol _ZN4Aska11TBinaryTreeINS_7AsfNodeEED2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11TBinaryTreeINS_7AsfNodeEED2Ev(long *param_1)

{
  undefined *puVar1;
  long *plVar2;
  
  *param_1 = (long)(PTR__ZTVN4Aska11TBinaryTreeINS_7AsfNodeEEE_02cbf940 + 0x10);
  Aska::TBinaryTree<Aska::AsfNode>::FreeTable()();
  plVar2 = param_1 + 4;
  *param_1 = (long)(PTR__ZTVN4Aska11TPoolLegacyINS_7AsfNodeELb0EEE_02cbd778 + 0x10);
  if ((*plVar2 != 0) && ((char)param_1[6] != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 6) = 0;
  }
  *plVar2 = 0;
  param_1[5] = 0;
  param_1[7] = 0;
  if (param_1[8] == 0) {
    param_1[2] = (long)(PTR__ZTVN4Aska9TBitArrayIjLb0EEE_02cba038 + 0x10);
  }
  else if ((char)param_1[9] == '\0') {
    param_1[2] = (long)(PTR__ZTVN4Aska9TBitArrayIjLb0EEE_02cba038 + 0x10);
    param_1[8] = 0;
  }
  else {
    operator delete[](void*)();
    param_1[2] = (long)(PTR__ZTVN4Aska9TBitArrayIjLb0EEE_02cba038 + 0x10);
    param_1[8] = 0;
    if ((param_1[4] != 0) && ((char)param_1[6] != '\0')) {
      operator delete[](void*)();
      *(undefined1 *)(param_1 + 6) = 0;
    }
  }
  *plVar2 = 0;
  param_1[5] = 0;
  puVar1 = PTR__ZTVN4Aska13TSmartPointerILb0EEE_02cc2320 + 0x10;
  param_1[2] = (long)puVar1;
  *param_1 = (long)puVar1;
  return;
}

// ==== Aska::TBinaryTree<Aska::AsfNode>::FreeTable()
// vaddr 0x20e0b84 | ghidra 0x21e0b84 | size 536 | symbol _ZN4Aska11TBinaryTreeINS_7AsfNodeEE9FreeTableEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11TBinaryTreeINS_7AsfNodeEE9FreeTableEv(long *param_1)

{
  int iVar1;
  long lVar2;
  long *plVar3;
  long *plVar4;
  ulong uVar5;
  long *plVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  long *plVar10;
  
  iVar8 = *(int *)((long)param_1 + 0x8c);
  iVar1 = (int)param_1[0xb];
  plVar4 = (long *)param_1[10];
  if (iVar8 == *(int *)((long)param_1 + 0x3c)) {
    iVar9 = iVar8 + -1;
    if (0 < iVar8) {
      lVar2 = 0;
      uVar7 = 0;
      if (*(uint *)((long)param_1 + 0x2c) != 0) goto code_r0x021e0bec;
      do {
        do {
          uVar7 = uVar7 + 1;
          lVar2 = lVar2 + 0x50;
        } while (*(uint *)((long)param_1 + 0x2c) <= uVar7);
code_r0x021e0bec:
      } while ((*(uint *)(param_1[4] + (ulong)(uVar7 >> 5) * 4) & 1 << (ulong)(uVar7 & 0x1f)) == 0);
      Hint_Prefetch((long *)(param_1[8] + lVar2),0,2,0);
      plVar6 = (long *)(param_1[8] + lVar2);
      do {
        if (iVar9 < 1) {
          plVar10 = (long *)0x0;
        }
        else {
          do {
            do {
              uVar7 = uVar7 + 1;
            } while (*(uint *)((long)param_1 + 0x2c) <= uVar7);
          } while ((*(uint *)(param_1[4] + (ulong)(uVar7 >> 5) * 4) & 1 << (ulong)(uVar7 & 0x1f)) ==
                   0);
          plVar10 = (long *)(param_1[8] + (ulong)uVar7 * 0x50);
          Hint_Prefetch(plVar10,0,2,0);
          iVar9 = iVar9 + -1;
        }
        (**(code **)(*plVar6 + 0x18))(plVar6);
        plVar3 = (long *)param_1[8];
        if (((plVar3 != (long *)0x0) && (plVar3 <= plVar6)) &&
           (plVar6 < plVar3 + (ulong)*(uint *)((long)param_1 + 0x2c) * 10)) {
          uVar5 = ((long)plVar6 - (long)plVar3 >> 4) * -0x3333333333333333;
          (**(code **)plVar3[(uVar5 & 0xffffffff) * 10])();
          lVar2 = (uVar5 >> 5 & 0x7ffffff) * 4;
          *(uint *)(param_1[4] + lVar2) =
               *(uint *)(param_1[4] + lVar2) & (1 << (ulong)((uint)uVar5 & 0x1f) ^ 0xffffffffU);
          *(int *)((long)param_1 + 0x3c) = *(int *)((long)param_1 + 0x3c) + -1;
        }
        *(int *)((long)param_1 + 0x8c) = *(int *)((long)param_1 + 0x8c) + -1;
        plVar6 = plVar10;
      } while (plVar10 != (long *)0x0);
    }
  }
  else if (iVar1 != 0) {
    plVar6 = plVar4 + (iVar1 - 1);
    iVar8 = iVar1;
    do {
      (**(code **)(*param_1 + 0x18))(param_1,plVar6);
      iVar8 = iVar8 + -1;
      plVar6 = plVar6 + -1;
    } while (iVar8 != 0);
  }
  param_1[0xc] = 0;
  *(undefined4 *)(param_1 + 0xb) = 0;
  param_1[10] = 0;
  param_1[0xf] = 0;
  param_1[0x10] = 0;
  *(undefined1 *)(param_1 + 0x11) = 0;
  param_1[0xe] = 0;
  if (((plVar4 != (long *)0x0) && (iVar1 != 0)) && (plVar4 != param_1 + 0xd)) {
    (*(code *)PTR__ZdaPv_02cb5db8)(plVar4);
    return;
  }
  return;
}

// ==== Aska::TBinaryTree<Aska::AsfHandler::IAnimatableSet>::AllocNode(void const*)
// vaddr 0x20e0df8 | ghidra 0x21e0df8 | size 384 | symbol _ZN4Aska11TBinaryTreeINS_10AsfHandler14IAnimatableSetEE9AllocNodeEPKv | lib libSOA-3.7.0.so | 2026-10-04
long * _ZN4Aska11TBinaryTreeINS_10AsfHandler14IAnimatableSetEE9AllocNodeEPKv
                 (long param_1,undefined8 param_2)

{
  undefined *puVar1;
  ulong uVar2;
  uint uVar3;
  uint uVar4;
  long *plVar5;
  long lVar6;
  uint uVar7;
  long lVar8;
  long lVar9;
  ulong uVar10;
  ulong uVar11;
  
  if (*(uint *)(param_1 + 0x3c) < *(uint *)(param_1 + 0x2c)) {
    lVar6 = *(long *)(param_1 + 0x20);
    uVar4 = *(uint *)(param_1 + 0x38);
    do {
      uVar7 = uVar4;
      if (*(uint *)(param_1 + 0x2c) <= uVar7) {
        uVar7 = 0;
      }
      uVar3 = 1 << (ulong)(uVar7 & 0x1f);
      uVar4 = uVar7 + 1;
    } while ((uVar3 & *(uint *)(lVar6 + (ulong)(uVar7 >> 5) * 4)) != 0);
    uVar2 = *(long *)(param_1 + 0x40) + (ulong)uVar7 * 0x40;
    uVar10 = uVar2;
    do {
      uVar11 = uVar10 + 0x7f & 0xffffffffffffff81;
      Hint_Prefetch(uVar10,0,2,0);
      uVar10 = uVar11;
    } while (uVar11 < uVar2 + 0x40);
    lVar9 = (ulong)(uVar7 >> 5) * 4;
    *(uint *)(param_1 + 0x38) = uVar7 + 1;
    *(uint *)(param_1 + 0x3c) = *(uint *)(param_1 + 0x3c) + 1;
    lVar8 = (ulong)uVar7 * 0x40;
    *(uint *)(lVar6 + lVar9) = *(uint *)(lVar6 + lVar9) | uVar3;
    plVar5 = (long *)(*(long *)(param_1 + 0x40) + lVar8);
    puVar1 = PTR__ZTVN4Aska10AsfHandler14IAnimatableSetE_02cbc760 + 0x10;
    plVar5[4] = 0;
    plVar5[3] = 0;
    plVar5[2] = 0;
    plVar5[1] = 0;
    *plVar5 = (long)puVar1;
    plVar5[6] = 0;
    *(undefined4 *)(plVar5 + 7) = 0xffffffff;
    plVar5 = (long *)(*(long *)(param_1 + 0x40) + lVar8);
    if (plVar5 == (long *)0x0) goto code_r0x021e0ec8;
  }
  else {
code_r0x021e0ec8:
    plVar5 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x40,PTR__ZSt7nothrow_02cb9a80);
    puVar1 = PTR__ZTVN4Aska10AsfHandler14IAnimatableSetE_02cbc760;
    if (plVar5 == (long *)0x0) {
      return (long *)0x0;
    }
    plVar5[6] = 0;
    plVar5[4] = 0;
    plVar5[3] = 0;
    plVar5[2] = 0;
    plVar5[1] = 0;
    *plVar5 = (long)(puVar1 + 0x10);
    *(undefined4 *)(plVar5 + 7) = 0xffffffff;
  }
  *(int *)(param_1 + 0x8c) = *(int *)(param_1 + 0x8c) + 1;
  if (*(long *)(param_1 + 0x70) == 0) {
    *(long **)(param_1 + 0x70) = plVar5;
    lVar6 = *(long *)(param_1 + 0x78);
    if (lVar6 == 0) {
      lVar8 = 0;
      goto code_r0x021e0f2c;
    }
  }
  else {
    lVar6 = *(long *)(param_1 + 0x78);
    lVar8 = 0;
    if (lVar6 == 0) goto code_r0x021e0f2c;
  }
  *(long **)(lVar6 + 0x10) = plVar5;
  lVar8 = *(long *)(param_1 + 0x78);
code_r0x021e0f2c:
  plVar5[1] = lVar8;
  plVar5[2] = 0;
  *(long **)(param_1 + 0x78) = plVar5;
  (**(code **)(*plVar5 + 0x28))(plVar5,param_2);
  (**(code **)(*plVar5 + 0x10))(plVar5);
  return plVar5;
}

// ==== Aska::TBinaryTree<Aska::AsfHandler::IAnimatableSet>::~TBinaryTree()
// vaddr 0x20e19a0 | ghidra 0x21e19a0 | size 240 | symbol _ZN4Aska11TBinaryTreeINS_10AsfHandler14IAnimatableSetEED2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11TBinaryTreeINS_10AsfHandler14IAnimatableSetEED2Ev(long *param_1)

{
  undefined *puVar1;
  long *plVar2;
  
  *param_1 = (long)(PTR__ZTVN4Aska11TBinaryTreeINS_10AsfHandler14IAnimatableSetEEE_02cba090 + 0x10);
  Aska::TBinaryTree<Aska::AsfHandler::IAnimatableSet>::FreeTable()();
  plVar2 = param_1 + 4;
  *param_1 = (long)(PTR__ZTVN4Aska11TPoolLegacyINS_10AsfHandler14IAnimatableSetELb0EEE_02cbf1b8 +
                   0x10);
  if ((*plVar2 != 0) && ((char)param_1[6] != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 6) = 0;
  }
  *plVar2 = 0;
  param_1[5] = 0;
  param_1[7] = 0;
  if (param_1[8] == 0) {
    param_1[2] = (long)(PTR__ZTVN4Aska9TBitArrayIjLb0EEE_02cba038 + 0x10);
  }
  else if ((char)param_1[9] == '\0') {
    param_1[2] = (long)(PTR__ZTVN4Aska9TBitArrayIjLb0EEE_02cba038 + 0x10);
    param_1[8] = 0;
  }
  else {
    operator delete[](void*)();
    param_1[2] = (long)(PTR__ZTVN4Aska9TBitArrayIjLb0EEE_02cba038 + 0x10);
    param_1[8] = 0;
    if ((param_1[4] != 0) && ((char)param_1[6] != '\0')) {
      operator delete[](void*)();
      *(undefined1 *)(param_1 + 6) = 0;
    }
  }
  *plVar2 = 0;
  param_1[5] = 0;
  puVar1 = PTR__ZTVN4Aska13TSmartPointerILb0EEE_02cc2320 + 0x10;
  param_1[2] = (long)puVar1;
  *param_1 = (long)puVar1;
  return;
}

// ==== Aska::TBinaryTree<Aska::AsfHandler::IAnimatableSet>::FreeTable()
// vaddr 0x20e2140 | ghidra 0x21e2140 | size 504 | symbol _ZN4Aska11TBinaryTreeINS_10AsfHandler14IAnimatableSetEE9FreeTableEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11TBinaryTreeINS_10AsfHandler14IAnimatableSetEE9FreeTableEv(long *param_1)

{
  int iVar1;
  long lVar2;
  long *plVar3;
  long *plVar4;
  ulong uVar5;
  long *plVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  long *plVar10;
  
  iVar8 = *(int *)((long)param_1 + 0x8c);
  iVar1 = (int)param_1[0xb];
  plVar4 = (long *)param_1[10];
  if (iVar8 == *(int *)((long)param_1 + 0x3c)) {
    iVar9 = iVar8 + -1;
    if (0 < iVar8) {
      lVar2 = 0;
      uVar7 = 0;
      if (*(uint *)((long)param_1 + 0x2c) != 0) goto code_r0x021e21a4;
      do {
        do {
          uVar7 = uVar7 + 1;
          lVar2 = lVar2 + 0x40;
        } while (*(uint *)((long)param_1 + 0x2c) <= uVar7);
code_r0x021e21a4:
      } while ((*(uint *)(param_1[4] + (ulong)(uVar7 >> 5) * 4) & 1 << (ulong)(uVar7 & 0x1f)) == 0);
      Hint_Prefetch((long *)(param_1[8] + lVar2),0,2,0);
      plVar6 = (long *)(param_1[8] + lVar2);
      do {
        if (iVar9 < 1) {
          plVar10 = (long *)0x0;
        }
        else {
          do {
            do {
              uVar7 = uVar7 + 1;
            } while (*(uint *)((long)param_1 + 0x2c) <= uVar7);
          } while ((*(uint *)(param_1[4] + (ulong)(uVar7 >> 5) * 4) & 1 << (ulong)(uVar7 & 0x1f)) ==
                   0);
          plVar10 = (long *)(param_1[8] + (ulong)uVar7 * 0x40);
          Hint_Prefetch(plVar10,0,2,0);
          iVar9 = iVar9 + -1;
        }
        (**(code **)(*plVar6 + 0x18))(plVar6);
        plVar3 = (long *)param_1[8];
        if (((plVar3 != (long *)0x0) && (plVar3 <= plVar6)) &&
           (plVar6 < plVar3 + (ulong)*(uint *)((long)param_1 + 0x2c) * 8)) {
          uVar5 = (long)plVar6 - (long)plVar3;
          (**(code **)plVar3[(uVar5 >> 6 & 0xffffffff) * 8])();
          lVar2 = (uVar5 >> 0xb & 0x7ffffff) * 4;
          *(uint *)(param_1[4] + lVar2) =
               *(uint *)(param_1[4] + lVar2) & (1 << (uVar5 >> 6 & 0x1f) ^ 0xffffffffU);
          *(int *)((long)param_1 + 0x3c) = *(int *)((long)param_1 + 0x3c) + -1;
        }
        *(int *)((long)param_1 + 0x8c) = *(int *)((long)param_1 + 0x8c) + -1;
        plVar6 = plVar10;
      } while (plVar10 != (long *)0x0);
    }
  }
  else if (iVar1 != 0) {
    plVar6 = plVar4 + (iVar1 - 1);
    iVar8 = iVar1;
    do {
      (**(code **)(*param_1 + 0x18))(param_1,plVar6);
      iVar8 = iVar8 + -1;
      plVar6 = plVar6 + -1;
    } while (iVar8 != 0);
  }
  param_1[0xc] = 0;
  *(undefined4 *)(param_1 + 0xb) = 0;
  param_1[10] = 0;
  param_1[0xf] = 0;
  param_1[0x10] = 0;
  *(undefined1 *)(param_1 + 0x11) = 0;
  param_1[0xe] = 0;
  if (((plVar4 != (long *)0x0) && (iVar1 != 0)) && (plVar4 != param_1 + 0xd)) {
    (*(code *)PTR__ZdaPv_02cb5db8)(plVar4);
    return;
  }
  return;
}

// ==== Aska::TBinaryTree<Aska::DecodeTextureQueue::TextureMemoryEx>::AllocNode(void const*)
// vaddr 0x20f87c4 | ghidra 0x21f87c4 | size 384 | symbol _ZN4Aska11TBinaryTreeINS_18DecodeTextureQueue15TextureMemoryExEE9AllocNodeEPKv | lib libSOA-3.7.0.so | 2026-10-04
long * _ZN4Aska11TBinaryTreeINS_18DecodeTextureQueue15TextureMemoryExEE9AllocNodeEPKv
                 (long param_1,undefined8 param_2)

{
  undefined *puVar1;
  uint uVar2;
  uint uVar3;
  long *plVar4;
  long lVar5;
  uint uVar6;
  long lVar7;
  ulong uVar8;
  ulong uVar9;
  ulong uVar10;
  
  if (*(uint *)(param_1 + 0x3c) < *(uint *)(param_1 + 0x2c)) {
    lVar5 = *(long *)(param_1 + 0x20);
    uVar3 = *(uint *)(param_1 + 0x38);
    do {
      uVar6 = uVar3;
      if (*(uint *)(param_1 + 0x2c) <= uVar6) {
        uVar6 = 0;
      }
      uVar2 = 1 << (ulong)(uVar6 & 0x1f);
      uVar3 = uVar6 + 1;
    } while ((uVar2 & *(uint *)(lVar5 + (ulong)(uVar6 >> 5) * 4)) != 0);
    uVar8 = *(long *)(param_1 + 0x40) + (ulong)uVar6 * 0x50;
    uVar9 = uVar8;
    do {
      uVar10 = uVar9 + 0x7f & 0xffffffffffffff81;
      Hint_Prefetch(uVar9,0,2,0);
      uVar9 = uVar10;
    } while (uVar10 < uVar8 + 0x50);
    lVar7 = (ulong)(uVar6 >> 5) * 4;
    *(uint *)(param_1 + 0x38) = uVar6 + 1;
    *(uint *)(param_1 + 0x3c) = *(uint *)(param_1 + 0x3c) + 1;
    *(uint *)(lVar5 + lVar7) = *(uint *)(lVar5 + lVar7) | uVar2;
    plVar4 = (long *)(*(long *)(param_1 + 0x40) + (ulong)uVar6 * 0x50);
    puVar1 = PTR__ZTVN4Aska18DecodeTextureQueue15TextureMemoryExE_02cbad00 + 0x10;
    plVar4[4] = 0;
    plVar4[3] = 0;
    plVar4[2] = 0;
    plVar4[1] = 0;
    plVar4[7] = 0;
    plVar4[8] = 0;
    *plVar4 = (long)puVar1;
    *(undefined4 *)(plVar4 + 9) = 0;
    plVar4 = (long *)(*(long *)(param_1 + 0x40) + (ulong)uVar6 * 0x50);
    if (plVar4 == (long *)0x0) goto code_r0x021f8898;
  }
  else {
code_r0x021f8898:
    plVar4 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x50,PTR__ZSt7nothrow_02cb9a80);
    if (plVar4 == (long *)0x0) {
      return (long *)0x0;
    }
    plVar4[7] = 0;
    plVar4[8] = 0;
    puVar1 = PTR__ZTVN4Aska18DecodeTextureQueue15TextureMemoryExE_02cbad00;
    plVar4[4] = 0;
    plVar4[3] = 0;
    plVar4[2] = 0;
    plVar4[1] = 0;
    *plVar4 = (long)(puVar1 + 0x10);
    *(undefined4 *)(plVar4 + 9) = 0;
  }
  *(int *)(param_1 + 0x8c) = *(int *)(param_1 + 0x8c) + 1;
  if (*(long *)(param_1 + 0x70) == 0) {
    *(long **)(param_1 + 0x70) = plVar4;
    lVar5 = *(long *)(param_1 + 0x78);
    if (lVar5 == 0) {
      lVar7 = 0;
      goto code_r0x021f88f8;
    }
  }
  else {
    lVar5 = *(long *)(param_1 + 0x78);
    lVar7 = 0;
    if (lVar5 == 0) goto code_r0x021f88f8;
  }
  *(long **)(lVar5 + 0x10) = plVar4;
  lVar7 = *(long *)(param_1 + 0x78);
code_r0x021f88f8:
  plVar4[1] = lVar7;
  plVar4[2] = 0;
  *(long **)(param_1 + 0x78) = plVar4;
  (**(code **)(*plVar4 + 0x28))(plVar4,param_2);
  (**(code **)(*plVar4 + 0x10))(plVar4);
  return plVar4;
}

// ==== Aska::TBinaryTree<Aska::DecodeTextureQueue::DecodeTextureIdIterator>::AllocNode(void const*)
// vaddr 0x20fa15c | ghidra 0x21fa15c | size 360 | symbol _ZN4Aska11TBinaryTreeINS_18DecodeTextureQueue23DecodeTextureIdIteratorEE9AllocNodeEPKv | lib libSOA-3.7.0.so | 2026-10-04
long * _ZN4Aska11TBinaryTreeINS_18DecodeTextureQueue23DecodeTextureIdIteratorEE9AllocNodeEPKv
                 (long param_1,undefined8 param_2)

{
  undefined *puVar1;
  ulong uVar2;
  uint uVar3;
  uint uVar4;
  long *plVar5;
  long lVar6;
  uint uVar7;
  long lVar8;
  long lVar9;
  ulong uVar10;
  ulong uVar11;
  
  if (*(uint *)(param_1 + 0x3c) < *(uint *)(param_1 + 0x2c)) {
    lVar6 = *(long *)(param_1 + 0x20);
    uVar4 = *(uint *)(param_1 + 0x38);
    do {
      uVar7 = uVar4;
      if (*(uint *)(param_1 + 0x2c) <= uVar7) {
        uVar7 = 0;
      }
      uVar3 = 1 << (ulong)(uVar7 & 0x1f);
      uVar4 = uVar7 + 1;
    } while ((uVar3 & *(uint *)(lVar6 + (ulong)(uVar7 >> 5) * 4)) != 0);
    uVar2 = *(long *)(param_1 + 0x40) + (ulong)uVar7 * 0x40;
    uVar10 = uVar2;
    do {
      uVar11 = uVar10 + 0x7f & 0xffffffffffffff81;
      Hint_Prefetch(uVar10,0,2,0);
      uVar10 = uVar11;
    } while (uVar11 < uVar2 + 0x40);
    lVar9 = (ulong)(uVar7 >> 5) * 4;
    *(uint *)(param_1 + 0x38) = uVar7 + 1;
    *(uint *)(param_1 + 0x3c) = *(uint *)(param_1 + 0x3c) + 1;
    lVar8 = (ulong)uVar7 * 0x40;
    *(uint *)(lVar6 + lVar9) = *(uint *)(lVar6 + lVar9) | uVar3;
    plVar5 = (long *)(*(long *)(param_1 + 0x40) + lVar8);
    puVar1 = PTR__ZTVN4Aska18DecodeTextureQueue23DecodeTextureIdIteratorE_02cbc398 + 0x10;
    plVar5[4] = 0;
    plVar5[3] = 0;
    plVar5[2] = 0;
    plVar5[1] = 0;
    *plVar5 = (long)puVar1;
    plVar5 = (long *)(*(long *)(param_1 + 0x40) + lVar8);
    if (plVar5 == (long *)0x0) goto code_r0x021fa220;
  }
  else {
code_r0x021fa220:
    plVar5 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x40,PTR__ZSt7nothrow_02cb9a80);
    puVar1 = PTR__ZTVN4Aska18DecodeTextureQueue23DecodeTextureIdIteratorE_02cbc398;
    if (plVar5 == (long *)0x0) {
      return (long *)0x0;
    }
    plVar5[4] = 0;
    plVar5[3] = 0;
    plVar5[2] = 0;
    plVar5[1] = 0;
    *plVar5 = (long)(puVar1 + 0x10);
  }
  *(int *)(param_1 + 0x8c) = *(int *)(param_1 + 0x8c) + 1;
  if (*(long *)(param_1 + 0x70) == 0) {
    *(long **)(param_1 + 0x70) = plVar5;
    lVar6 = *(long *)(param_1 + 0x78);
    if (lVar6 == 0) {
      lVar8 = 0;
      goto code_r0x021fa278;
    }
  }
  else {
    lVar6 = *(long *)(param_1 + 0x78);
    lVar8 = 0;
    if (lVar6 == 0) goto code_r0x021fa278;
  }
  *(long **)(lVar6 + 0x10) = plVar5;
  lVar8 = *(long *)(param_1 + 0x78);
code_r0x021fa278:
  plVar5[1] = lVar8;
  plVar5[2] = 0;
  *(long **)(param_1 + 0x78) = plVar5;
  (**(code **)(*plVar5 + 0x28))(plVar5,param_2);
  (**(code **)(*plVar5 + 0x10))(plVar5);
  return plVar5;
}

// ==== Aska::TBinaryTree<Aska::DecodeTextureQueue::DecodeTextureIdIterator>::FreeNode(Aska::DecodeTextureQueue::DecodeTextureIdIterator**)
// vaddr 0x20fa2c4 | ghidra 0x21fa2c4 | size 376 | symbol _ZN4Aska11TBinaryTreeINS_18DecodeTextureQueue23DecodeTextureIdIteratorEE8FreeNodeEPPS2_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11TBinaryTreeINS_18DecodeTextureQueue23DecodeTextureIdIteratorEE8FreeNodeEPPS2_
               (long *param_1,ulong *param_2)

{
  long *plVar1;
  ulong uVar2;
  long *plVar3;
  long lVar4;
  
  uVar2 = *param_2;
  if (uVar2 != 0) {
    if (param_1[0xe] == uVar2) {
      param_1[0xe] = *(long *)(uVar2 + 0x10);
      uVar2 = *param_2;
    }
    if (param_1[0xf] == uVar2) {
      param_1[0xf] = *(long *)(uVar2 + 8);
      uVar2 = *param_2;
    }
    if (param_1[0x10] == uVar2) {
      param_1[0x10] = *(long *)(uVar2 + 8);
      uVar2 = *param_2;
    }
    lVar4 = *(long *)(uVar2 + 0x10);
    if (*(long *)(uVar2 + 8) != 0) {
      *(long *)(*(long *)(uVar2 + 8) + 0x10) = lVar4;
    }
    if (lVar4 != 0) {
      *(undefined8 *)(lVar4 + 8) = *(undefined8 *)(*param_2 + 8);
    }
    *(undefined8 *)(*param_2 + 0x10) = 0;
    *(undefined8 *)(*param_2 + 8) = 0;
    plVar1 = (long *)*param_2;
    if (plVar1[4] != 0) {
      (**(code **)(*param_1 + 0x18))(param_1);
      plVar1 = (long *)*param_2;
    }
    if (plVar1[3] != 0) {
      (**(code **)(*param_1 + 0x18))(param_1);
      plVar1 = (long *)*param_2;
    }
    (**(code **)(*plVar1 + 0x18))();
    *(int *)((long)param_1 + 0x8c) = *(int *)((long)param_1 + 0x8c) + -1;
    plVar3 = (long *)param_1[8];
    plVar1 = (long *)*param_2;
    if (((plVar3 == (long *)0x0) || (plVar1 < plVar3)) ||
       (plVar3 + (ulong)*(uint *)((long)param_1 + 0x2c) * 8 <= plVar1)) {
      if (plVar1 != (long *)0x0) {
        (**(code **)(*plVar1 + 8))();
      }
    }
    else {
      uVar2 = (long)plVar1 - (long)plVar3;
      (**(code **)plVar3[(uVar2 >> 6 & 0xffffffff) * 8])();
      lVar4 = (uVar2 >> 0xb & 0x7ffffff) * 4;
      *(uint *)(param_1[4] + lVar4) =
           *(uint *)(param_1[4] + lVar4) & (1 << (uVar2 >> 6 & 0x1f) ^ 0xffffffffU);
      *(int *)((long)param_1 + 0x3c) = *(int *)((long)param_1 + 0x3c) + -1;
    }
    *param_2 = 0;
  }
  return;
}

// ==== Aska::TBinaryTree<Aska::DecodeTextureQueue::TextureDecoderIterator>::AllocNode(void const*)
// vaddr 0x20fb4ec | ghidra 0x21fb4ec | size 376 | symbol _ZN4Aska11TBinaryTreeINS_18DecodeTextureQueue22TextureDecoderIteratorEE9AllocNodeEPKv | lib libSOA-3.7.0.so | 2026-10-04
long * _ZN4Aska11TBinaryTreeINS_18DecodeTextureQueue22TextureDecoderIteratorEE9AllocNodeEPKv
                 (long param_1,undefined8 param_2)

{
  undefined *puVar1;
  uint uVar2;
  uint uVar3;
  long *plVar4;
  long lVar5;
  uint uVar6;
  long lVar7;
  ulong uVar8;
  ulong uVar9;
  ulong uVar10;
  
  if (*(uint *)(param_1 + 0x3c) < *(uint *)(param_1 + 0x2c)) {
    lVar5 = *(long *)(param_1 + 0x20);
    uVar3 = *(uint *)(param_1 + 0x38);
    do {
      uVar6 = uVar3;
      if (*(uint *)(param_1 + 0x2c) <= uVar6) {
        uVar6 = 0;
      }
      uVar2 = 1 << (ulong)(uVar6 & 0x1f);
      uVar3 = uVar6 + 1;
    } while ((uVar2 & *(uint *)(lVar5 + (ulong)(uVar6 >> 5) * 4)) != 0);
    uVar8 = *(long *)(param_1 + 0x40) + (ulong)uVar6 * 0x58;
    uVar9 = uVar8;
    do {
      uVar10 = uVar9 + 0x7f & 0xffffffffffffff81;
      Hint_Prefetch(uVar9,0,2,0);
      uVar9 = uVar10;
    } while (uVar10 < uVar8 + 0x58);
    lVar7 = (ulong)(uVar6 >> 5) * 4;
    *(uint *)(param_1 + 0x38) = uVar6 + 1;
    *(uint *)(param_1 + 0x3c) = *(uint *)(param_1 + 0x3c) + 1;
    *(uint *)(lVar5 + lVar7) = *(uint *)(lVar5 + lVar7) | uVar2;
    plVar4 = (long *)(*(long *)(param_1 + 0x40) + (ulong)uVar6 * 0x58);
    puVar1 = PTR__ZTVN4Aska18DecodeTextureQueue22TextureDecoderIteratorE_02cbd8e8 + 0x10;
    plVar4[4] = 0;
    plVar4[3] = 0;
    plVar4[2] = 0;
    plVar4[1] = 0;
    plVar4[8] = 0;
    plVar4[9] = 0;
    *plVar4 = (long)puVar1;
    plVar4 = (long *)(*(long *)(param_1 + 0x40) + (ulong)uVar6 * 0x58);
    if (plVar4 == (long *)0x0) goto code_r0x021fb5bc;
  }
  else {
code_r0x021fb5bc:
    plVar4 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x58,PTR__ZSt7nothrow_02cb9a80);
    if (plVar4 == (long *)0x0) {
      return (long *)0x0;
    }
    plVar4[8] = 0;
    plVar4[9] = 0;
    puVar1 = PTR__ZTVN4Aska18DecodeTextureQueue22TextureDecoderIteratorE_02cbd8e8;
    plVar4[4] = 0;
    plVar4[3] = 0;
    plVar4[2] = 0;
    plVar4[1] = 0;
    *plVar4 = (long)(puVar1 + 0x10);
  }
  *(int *)(param_1 + 0x8c) = *(int *)(param_1 + 0x8c) + 1;
  if (*(long *)(param_1 + 0x70) == 0) {
    *(long **)(param_1 + 0x70) = plVar4;
    lVar5 = *(long *)(param_1 + 0x78);
    if (lVar5 == 0) {
      lVar7 = 0;
      goto code_r0x021fb618;
    }
  }
  else {
    lVar5 = *(long *)(param_1 + 0x78);
    lVar7 = 0;
    if (lVar5 == 0) goto code_r0x021fb618;
  }
  *(long **)(lVar5 + 0x10) = plVar4;
  lVar7 = *(long *)(param_1 + 0x78);
code_r0x021fb618:
  plVar4[1] = lVar7;
  plVar4[2] = 0;
  *(long **)(param_1 + 0x78) = plVar4;
  (**(code **)(*plVar4 + 0x28))(plVar4,param_2);
  (**(code **)(*plVar4 + 0x10))(plVar4);
  return plVar4;
}

// ==== Aska::TBinaryTree<Aska::DecodeTextureQueue::TextureMemoryIterator>::AllocNode(void const*)
// vaddr 0x20fd088 | ghidra 0x21fd088 | size 376 | symbol _ZN4Aska11TBinaryTreeINS_18DecodeTextureQueue21TextureMemoryIteratorEE9AllocNodeEPKv | lib libSOA-3.7.0.so | 2026-10-04
long * _ZN4Aska11TBinaryTreeINS_18DecodeTextureQueue21TextureMemoryIteratorEE9AllocNodeEPKv
                 (long param_1,undefined8 param_2)

{
  undefined *puVar1;
  uint uVar2;
  uint uVar3;
  long *plVar4;
  long lVar5;
  uint uVar6;
  long lVar7;
  ulong uVar8;
  ulong uVar9;
  ulong uVar10;
  
  if (*(uint *)(param_1 + 0x3c) < *(uint *)(param_1 + 0x2c)) {
    lVar5 = *(long *)(param_1 + 0x20);
    uVar3 = *(uint *)(param_1 + 0x38);
    do {
      uVar6 = uVar3;
      if (*(uint *)(param_1 + 0x2c) <= uVar6) {
        uVar6 = 0;
      }
      uVar2 = 1 << (ulong)(uVar6 & 0x1f);
      uVar3 = uVar6 + 1;
    } while ((uVar2 & *(uint *)(lVar5 + (ulong)(uVar6 >> 5) * 4)) != 0);
    uVar8 = *(long *)(param_1 + 0x40) + (ulong)uVar6 * 0x58;
    uVar9 = uVar8;
    do {
      uVar10 = uVar9 + 0x7f & 0xffffffffffffff81;
      Hint_Prefetch(uVar9,0,2,0);
      uVar9 = uVar10;
    } while (uVar10 < uVar8 + 0x58);
    lVar7 = (ulong)(uVar6 >> 5) * 4;
    *(uint *)(param_1 + 0x38) = uVar6 + 1;
    *(uint *)(param_1 + 0x3c) = *(uint *)(param_1 + 0x3c) + 1;
    *(uint *)(lVar5 + lVar7) = *(uint *)(lVar5 + lVar7) | uVar2;
    plVar4 = (long *)(*(long *)(param_1 + 0x40) + (ulong)uVar6 * 0x58);
    puVar1 = PTR__ZTVN4Aska18DecodeTextureQueue21TextureMemoryIteratorE_02cc0938 + 0x10;
    plVar4[4] = 0;
    plVar4[3] = 0;
    plVar4[2] = 0;
    plVar4[1] = 0;
    plVar4[8] = 0;
    plVar4[9] = 0;
    *plVar4 = (long)puVar1;
    plVar4 = (long *)(*(long *)(param_1 + 0x40) + (ulong)uVar6 * 0x58);
    if (plVar4 == (long *)0x0) goto code_r0x021fd158;
  }
  else {
code_r0x021fd158:
    plVar4 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x58,PTR__ZSt7nothrow_02cb9a80);
    if (plVar4 == (long *)0x0) {
      return (long *)0x0;
    }
    plVar4[8] = 0;
    plVar4[9] = 0;
    puVar1 = PTR__ZTVN4Aska18DecodeTextureQueue21TextureMemoryIteratorE_02cc0938;
    plVar4[4] = 0;
    plVar4[3] = 0;
    plVar4[2] = 0;
    plVar4[1] = 0;
    *plVar4 = (long)(puVar1 + 0x10);
  }
  *(int *)(param_1 + 0x8c) = *(int *)(param_1 + 0x8c) + 1;
  if (*(long *)(param_1 + 0x70) == 0) {
    *(long **)(param_1 + 0x70) = plVar4;
    lVar5 = *(long *)(param_1 + 0x78);
    if (lVar5 == 0) {
      lVar7 = 0;
      goto code_r0x021fd1b4;
    }
  }
  else {
    lVar5 = *(long *)(param_1 + 0x78);
    lVar7 = 0;
    if (lVar5 == 0) goto code_r0x021fd1b4;
  }
  *(long **)(lVar5 + 0x10) = plVar4;
  lVar7 = *(long *)(param_1 + 0x78);
code_r0x021fd1b4:
  plVar4[1] = lVar7;
  plVar4[2] = 0;
  *(long **)(param_1 + 0x78) = plVar4;
  (**(code **)(*plVar4 + 0x28))(plVar4,param_2);
  (**(code **)(*plVar4 + 0x10))(plVar4);
  return plVar4;
}

// ==== Aska::TBinaryTree<Aska::TextureNode>::AllocNode(void const*)
// vaddr 0x21deb20 | ghidra 0x22deb20 | size 392 | symbol _ZN4Aska11TBinaryTreeINS_11TextureNodeEE9AllocNodeEPKv | lib libSOA-3.7.0.so | 2026-10-04
long * _ZN4Aska11TBinaryTreeINS_11TextureNodeEE9AllocNodeEPKv(long param_1,undefined8 param_2)

{
  uint uVar1;
  undefined *puVar2;
  uint uVar3;
  long *plVar4;
  long lVar5;
  uint uVar6;
  long lVar7;
  ulong uVar8;
  ulong uVar9;
  ulong uVar10;
  
  if (*(uint *)(param_1 + 0x3c) < *(uint *)(param_1 + 0x2c)) {
    lVar5 = *(long *)(param_1 + 0x20);
    uVar3 = *(uint *)(param_1 + 0x38);
    do {
      uVar6 = uVar3;
      if (*(uint *)(param_1 + 0x2c) <= uVar6) {
        uVar6 = 0;
      }
      uVar1 = 1 << (ulong)(uVar6 & 0x1f);
      uVar3 = uVar6 + 1;
    } while ((uVar1 & *(uint *)(lVar5 + (ulong)(uVar6 >> 5) * 4)) != 0);
    uVar8 = *(long *)(param_1 + 0x40) + (ulong)uVar6 * 0x108;
    uVar9 = uVar8;
    do {
      uVar10 = uVar9 + 0x7f & 0xffffffffffffff81;
      Hint_Prefetch(uVar9,0,2,0);
      uVar9 = uVar10;
    } while (uVar10 < uVar8 + 0x108);
    lVar7 = (ulong)(uVar6 >> 5) * 4;
    *(uint *)(param_1 + 0x38) = uVar6 + 1;
    *(uint *)(param_1 + 0x3c) = *(uint *)(param_1 + 0x3c) + 1;
    puVar2 = PTR__ZTVN4Aska11TextureNodeE_02cbb318;
    *(uint *)(lVar5 + lVar7) = *(uint *)(lVar5 + lVar7) | uVar1;
    plVar4 = (long *)(*(long *)(param_1 + 0x40) + (ulong)uVar6 * 0x108);
    plVar4[4] = 0;
    plVar4[3] = 0;
    plVar4[2] = 0;
    plVar4[1] = 0;
    plVar4[7] = 0;
    plVar4[8] = 0;
    *plVar4 = (long)(puVar2 + 0x10);
    plVar4[9] = (long)(puVar2 + 0x68);
    plVar4 = (long *)(*(long *)(param_1 + 0x40) + (ulong)uVar6 * 0x108);
    if (plVar4 == (long *)0x0) goto code_r0x022debf8;
  }
  else {
code_r0x022debf8:
    plVar4 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x108,PTR__ZSt7nothrow_02cb9a80);
    if (plVar4 == (long *)0x0) {
      return (long *)0x0;
    }
    plVar4[7] = 0;
    plVar4[8] = 0;
    puVar2 = PTR__ZTVN4Aska11TextureNodeE_02cbb318;
    plVar4[4] = 0;
    plVar4[3] = 0;
    plVar4[2] = 0;
    plVar4[1] = 0;
    *plVar4 = (long)(puVar2 + 0x10);
    plVar4[9] = (long)(puVar2 + 0x68);
  }
  *(int *)(param_1 + 0x8c) = *(int *)(param_1 + 0x8c) + 1;
  if (*(long *)(param_1 + 0x70) == 0) {
    *(long **)(param_1 + 0x70) = plVar4;
    lVar5 = *(long *)(param_1 + 0x78);
    if (lVar5 == 0) {
      lVar7 = 0;
      goto code_r0x022dec5c;
    }
  }
  else {
    lVar5 = *(long *)(param_1 + 0x78);
    lVar7 = 0;
    if (lVar5 == 0) goto code_r0x022dec5c;
  }
  *(long **)(lVar5 + 0x10) = plVar4;
  lVar7 = *(long *)(param_1 + 0x78);
code_r0x022dec5c:
  plVar4[1] = lVar7;
  plVar4[2] = 0;
  *(long **)(param_1 + 0x78) = plVar4;
  (**(code **)(*plVar4 + 0x28))(plVar4,param_2);
  (**(code **)(*plVar4 + 0x10))(plVar4);
  return plVar4;
}

// ==== Aska::TBinaryTree<Aska::RelatedTextureIDSet>::AllocNode(void const*)
// vaddr 0x21e0d08 | ghidra 0x22e0d08 | size 368 | symbol _ZN4Aska11TBinaryTreeINS_19RelatedTextureIDSetEE9AllocNodeEPKv | lib libSOA-3.7.0.so | 2026-10-04
long * _ZN4Aska11TBinaryTreeINS_19RelatedTextureIDSetEE9AllocNodeEPKv
                 (long param_1,undefined8 param_2)

{
  undefined *puVar1;
  uint uVar2;
  uint uVar3;
  long *plVar4;
  long lVar5;
  uint uVar6;
  long lVar7;
  ulong uVar8;
  ulong uVar9;
  ulong uVar10;
  
  if (*(uint *)(param_1 + 0x3c) < *(uint *)(param_1 + 0x2c)) {
    lVar5 = *(long *)(param_1 + 0x20);
    uVar3 = *(uint *)(param_1 + 0x38);
    do {
      uVar6 = uVar3;
      if (*(uint *)(param_1 + 0x2c) <= uVar6) {
        uVar6 = 0;
      }
      uVar2 = 1 << (ulong)(uVar6 & 0x1f);
      uVar3 = uVar6 + 1;
    } while ((uVar2 & *(uint *)(lVar5 + (ulong)(uVar6 >> 5) * 4)) != 0);
    uVar8 = *(long *)(param_1 + 0x40) + (ulong)uVar6 * 0x38;
    uVar9 = uVar8;
    do {
      uVar10 = uVar9 + 0x7f & 0xffffffffffffff81;
      Hint_Prefetch(uVar9,0,2,0);
      uVar9 = uVar10;
    } while (uVar10 < uVar8 + 0x38);
    lVar7 = (ulong)(uVar6 >> 5) * 4;
    *(uint *)(param_1 + 0x38) = uVar6 + 1;
    *(uint *)(param_1 + 0x3c) = *(uint *)(param_1 + 0x3c) + 1;
    *(uint *)(lVar5 + lVar7) = *(uint *)(lVar5 + lVar7) | uVar2;
    plVar4 = (long *)(*(long *)(param_1 + 0x40) + (ulong)uVar6 * 0x38);
    puVar1 = PTR__ZTVN4Aska19RelatedTextureIDSetE_02cbe338 + 0x10;
    plVar4[4] = 0;
    plVar4[3] = 0;
    plVar4[2] = 0;
    plVar4[1] = 0;
    *plVar4 = (long)puVar1;
    plVar4 = (long *)(*(long *)(param_1 + 0x40) + (ulong)uVar6 * 0x38);
    if (plVar4 == (long *)0x0) goto code_r0x022e0dd4;
  }
  else {
code_r0x022e0dd4:
    plVar4 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x38,PTR__ZSt7nothrow_02cb9a80);
    puVar1 = PTR__ZTVN4Aska19RelatedTextureIDSetE_02cbe338;
    if (plVar4 == (long *)0x0) {
      return (long *)0x0;
    }
    plVar4[4] = 0;
    plVar4[3] = 0;
    plVar4[2] = 0;
    plVar4[1] = 0;
    *plVar4 = (long)(puVar1 + 0x10);
  }
  *(int *)(param_1 + 0x8c) = *(int *)(param_1 + 0x8c) + 1;
  if (*(long *)(param_1 + 0x70) == 0) {
    *(long **)(param_1 + 0x70) = plVar4;
    lVar5 = *(long *)(param_1 + 0x78);
    if (lVar5 == 0) {
      lVar7 = 0;
      goto code_r0x022e0e2c;
    }
  }
  else {
    lVar5 = *(long *)(param_1 + 0x78);
    lVar7 = 0;
    if (lVar5 == 0) goto code_r0x022e0e2c;
  }
  *(long **)(lVar5 + 0x10) = plVar4;
  lVar7 = *(long *)(param_1 + 0x78);
code_r0x022e0e2c:
  plVar4[1] = lVar7;
  plVar4[2] = 0;
  *(long **)(param_1 + 0x78) = plVar4;
  (**(code **)(*plVar4 + 0x28))(plVar4,param_2);
  (**(code **)(*plVar4 + 0x10))(plVar4);
  return plVar4;
}

// ==== Aska::TBinaryTree<Aska::TextureID>::AllocNode(void const*)
// vaddr 0x21e22ac | ghidra 0x22e22ac | size 368 | symbol _ZN4Aska11TBinaryTreeINS_9TextureIDEE9AllocNodeEPKv | lib libSOA-3.7.0.so | 2026-10-04
long * _ZN4Aska11TBinaryTreeINS_9TextureIDEE9AllocNodeEPKv(long param_1,undefined8 param_2)

{
  undefined *puVar1;
  uint uVar2;
  uint uVar3;
  long *plVar4;
  long lVar5;
  uint uVar6;
  long lVar7;
  ulong uVar8;
  ulong uVar9;
  ulong uVar10;
  
  if (*(uint *)(param_1 + 0x3c) < *(uint *)(param_1 + 0x2c)) {
    lVar5 = *(long *)(param_1 + 0x20);
    uVar3 = *(uint *)(param_1 + 0x38);
    do {
      uVar6 = uVar3;
      if (*(uint *)(param_1 + 0x2c) <= uVar6) {
        uVar6 = 0;
      }
      uVar2 = 1 << (ulong)(uVar6 & 0x1f);
      uVar3 = uVar6 + 1;
    } while ((uVar2 & *(uint *)(lVar5 + (ulong)(uVar6 >> 5) * 4)) != 0);
    uVar8 = *(long *)(param_1 + 0x40) + (ulong)uVar6 * 0x30;
    uVar9 = uVar8;
    do {
      uVar10 = uVar9 + 0x7f & 0xffffffffffffff81;
      Hint_Prefetch(uVar9,0,2,0);
      uVar9 = uVar10;
    } while (uVar10 < uVar8 + 0x30);
    lVar7 = (ulong)(uVar6 >> 5) * 4;
    *(uint *)(param_1 + 0x38) = uVar6 + 1;
    *(uint *)(param_1 + 0x3c) = *(uint *)(param_1 + 0x3c) + 1;
    *(uint *)(lVar5 + lVar7) = *(uint *)(lVar5 + lVar7) | uVar2;
    plVar4 = (long *)(*(long *)(param_1 + 0x40) + (ulong)uVar6 * 0x30);
    puVar1 = PTR__ZTVN4Aska9TextureIDE_02cbd9b0 + 0x10;
    plVar4[4] = 0;
    plVar4[3] = 0;
    plVar4[2] = 0;
    plVar4[1] = 0;
    *plVar4 = (long)puVar1;
    plVar4 = (long *)(*(long *)(param_1 + 0x40) + (ulong)uVar6 * 0x30);
    if (plVar4 == (long *)0x0) goto code_r0x022e2378;
  }
  else {
code_r0x022e2378:
    plVar4 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x30,PTR__ZSt7nothrow_02cb9a80);
    puVar1 = PTR__ZTVN4Aska9TextureIDE_02cbd9b0;
    if (plVar4 == (long *)0x0) {
      return (long *)0x0;
    }
    plVar4[4] = 0;
    plVar4[3] = 0;
    plVar4[2] = 0;
    plVar4[1] = 0;
    *plVar4 = (long)(puVar1 + 0x10);
  }
  *(int *)(param_1 + 0x8c) = *(int *)(param_1 + 0x8c) + 1;
  if (*(long *)(param_1 + 0x70) == 0) {
    *(long **)(param_1 + 0x70) = plVar4;
    lVar5 = *(long *)(param_1 + 0x78);
    if (lVar5 == 0) {
      lVar7 = 0;
      goto code_r0x022e23d0;
    }
  }
  else {
    lVar5 = *(long *)(param_1 + 0x78);
    lVar7 = 0;
    if (lVar5 == 0) goto code_r0x022e23d0;
  }
  *(long **)(lVar5 + 0x10) = plVar4;
  lVar7 = *(long *)(param_1 + 0x78);
code_r0x022e23d0:
  plVar4[1] = lVar7;
  plVar4[2] = 0;
  *(long **)(param_1 + 0x78) = plVar4;
  (**(code **)(*plVar4 + 0x28))(plVar4,param_2);
  (**(code **)(*plVar4 + 0x10))(plVar4);
  return plVar4;
}

// ==== Aska::TBinaryTree<Aska::TextureID>::FreeNode(Aska::TextureID**)
// vaddr 0x21e241c | ghidra 0x22e241c | size 400 | symbol _ZN4Aska11TBinaryTreeINS_9TextureIDEE8FreeNodeEPPS1_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11TBinaryTreeINS_9TextureIDEE8FreeNodeEPPS1_(long *param_1,ulong *param_2)

{
  long *plVar1;
  ulong uVar2;
  long *plVar3;
  long lVar4;
  
  uVar2 = *param_2;
  if (uVar2 != 0) {
    if (param_1[0xe] == uVar2) {
      param_1[0xe] = *(long *)(uVar2 + 0x10);
      uVar2 = *param_2;
    }
    if (param_1[0xf] == uVar2) {
      param_1[0xf] = *(long *)(uVar2 + 8);
      uVar2 = *param_2;
    }
    if (param_1[0x10] == uVar2) {
      param_1[0x10] = *(long *)(uVar2 + 8);
      uVar2 = *param_2;
    }
    lVar4 = *(long *)(uVar2 + 0x10);
    if (*(long *)(uVar2 + 8) != 0) {
      *(long *)(*(long *)(uVar2 + 8) + 0x10) = lVar4;
    }
    if (lVar4 != 0) {
      *(undefined8 *)(lVar4 + 8) = *(undefined8 *)(*param_2 + 8);
    }
    *(undefined8 *)(*param_2 + 0x10) = 0;
    *(undefined8 *)(*param_2 + 8) = 0;
    plVar1 = (long *)*param_2;
    if (plVar1[4] != 0) {
      (**(code **)(*param_1 + 0x18))(param_1);
      plVar1 = (long *)*param_2;
    }
    if (plVar1[3] != 0) {
      (**(code **)(*param_1 + 0x18))(param_1);
      plVar1 = (long *)*param_2;
    }
    (**(code **)(*plVar1 + 0x18))();
    *(int *)((long)param_1 + 0x8c) = *(int *)((long)param_1 + 0x8c) + -1;
    plVar3 = (long *)param_1[8];
    plVar1 = (long *)*param_2;
    if (((plVar3 == (long *)0x0) || (plVar1 < plVar3)) ||
       (plVar3 + (ulong)*(uint *)((long)param_1 + 0x2c) * 6 <= plVar1)) {
      if (plVar1 != (long *)0x0) {
        (**(code **)(*plVar1 + 8))();
      }
    }
    else {
      uVar2 = ((long)plVar1 - (long)plVar3 >> 4) * -0x5555555555555555;
      (**(code **)plVar3[(uVar2 & 0xffffffff) * 6])();
      lVar4 = (uVar2 >> 5 & 0x7ffffff) * 4;
      *(uint *)(param_1[4] + lVar4) =
           *(uint *)(param_1[4] + lVar4) & (1 << (ulong)((uint)uVar2 & 0x1f) ^ 0xffffffffU);
      *(int *)((long)param_1 + 0x3c) = *(int *)((long)param_1 + 0x3c) + -1;
    }
    *param_2 = 0;
  }
  return;
}

// ==== Aska::TBinaryTree<Aska::TextureMemory>::AllocNode(void const*)
// vaddr 0x21e43c0 | ghidra 0x22e43c0 | size 376 | symbol _ZN4Aska11TBinaryTreeINS_13TextureMemoryEE9AllocNodeEPKv | lib libSOA-3.7.0.so | 2026-10-04
long * _ZN4Aska11TBinaryTreeINS_13TextureMemoryEE9AllocNodeEPKv(long param_1,undefined8 param_2)

{
  undefined *puVar1;
  uint uVar2;
  uint uVar3;
  long *plVar4;
  long lVar5;
  uint uVar6;
  long lVar7;
  ulong uVar8;
  ulong uVar9;
  ulong uVar10;
  
  if (*(uint *)(param_1 + 0x3c) < *(uint *)(param_1 + 0x2c)) {
    lVar5 = *(long *)(param_1 + 0x20);
    uVar3 = *(uint *)(param_1 + 0x38);
    do {
      uVar6 = uVar3;
      if (*(uint *)(param_1 + 0x2c) <= uVar6) {
        uVar6 = 0;
      }
      uVar2 = 1 << (ulong)(uVar6 & 0x1f);
      uVar3 = uVar6 + 1;
    } while ((uVar2 & *(uint *)(lVar5 + (ulong)(uVar6 >> 5) * 4)) != 0);
    uVar8 = *(long *)(param_1 + 0x40) + (ulong)uVar6 * 0x48;
    uVar9 = uVar8;
    do {
      uVar10 = uVar9 + 0x7f & 0xffffffffffffff81;
      Hint_Prefetch(uVar9,0,2,0);
      uVar9 = uVar10;
    } while (uVar10 < uVar8 + 0x48);
    lVar7 = (ulong)(uVar6 >> 5) * 4;
    *(uint *)(param_1 + 0x38) = uVar6 + 1;
    *(uint *)(param_1 + 0x3c) = *(uint *)(param_1 + 0x3c) + 1;
    *(uint *)(lVar5 + lVar7) = *(uint *)(lVar5 + lVar7) | uVar2;
    plVar4 = (long *)(*(long *)(param_1 + 0x40) + (ulong)uVar6 * 0x48);
    puVar1 = PTR__ZTVN4Aska13TextureMemoryE_02cc37d8 + 0x10;
    plVar4[4] = 0;
    plVar4[3] = 0;
    plVar4[2] = 0;
    plVar4[1] = 0;
    plVar4[7] = 0;
    plVar4[8] = 0;
    *plVar4 = (long)puVar1;
    plVar4 = (long *)(*(long *)(param_1 + 0x40) + (ulong)uVar6 * 0x48);
    if (plVar4 == (long *)0x0) goto code_r0x022e4490;
  }
  else {
code_r0x022e4490:
    plVar4 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x48,PTR__ZSt7nothrow_02cb9a80);
    if (plVar4 == (long *)0x0) {
      return (long *)0x0;
    }
    plVar4[7] = 0;
    plVar4[8] = 0;
    puVar1 = PTR__ZTVN4Aska13TextureMemoryE_02cc37d8;
    plVar4[4] = 0;
    plVar4[3] = 0;
    plVar4[2] = 0;
    plVar4[1] = 0;
    *plVar4 = (long)(puVar1 + 0x10);
  }
  *(int *)(param_1 + 0x8c) = *(int *)(param_1 + 0x8c) + 1;
  if (*(long *)(param_1 + 0x70) == 0) {
    *(long **)(param_1 + 0x70) = plVar4;
    lVar5 = *(long *)(param_1 + 0x78);
    if (lVar5 == 0) {
      lVar7 = 0;
      goto code_r0x022e44ec;
    }
  }
  else {
    lVar5 = *(long *)(param_1 + 0x78);
    lVar7 = 0;
    if (lVar5 == 0) goto code_r0x022e44ec;
  }
  *(long **)(lVar5 + 0x10) = plVar4;
  lVar7 = *(long *)(param_1 + 0x78);
code_r0x022e44ec:
  plVar4[1] = lVar7;
  plVar4[2] = 0;
  *(long **)(param_1 + 0x78) = plVar4;
  (**(code **)(*plVar4 + 0x28))(plVar4,param_2);
  (**(code **)(*plVar4 + 0x10))(plVar4);
  return plVar4;
}

// ==== Aska::TSharedPointer<Aska::DecompressStream::DataContext>::Release()
// vaddr 0x21e5818 | ghidra 0x22e5818 | size 144 | symbol _ZN4Aska14TSharedPointerINS_16DecompressStream11DataContextEE7ReleaseEv | lib libSOA-3.7.0.so | 2026-10-04
int _ZN4Aska14TSharedPointerINS_16DecompressStream11DataContextEE7ReleaseEv(long *param_1)

{
  char cVar1;
  bool bVar2;
  int iVar3;
  int *piVar4;
  long lVar5;
  
  piVar4 = (int *)param_1[1];
  if (piVar4 != (int *)0x0) {
    do {
      iVar3 = *piVar4 + -1;
      cVar1 = '\x01';
      bVar2 = (bool)ExclusiveMonitorPass(piVar4,0x10);
      if (bVar2) {
        *piVar4 = iVar3;
        cVar1 = ExclusiveMonitorsStatus();
      }
    } while (cVar1 != '\0');
    if (iVar3 != 0) goto code_r0x022e5898;
  }
  lVar5 = *param_1;
  if (lVar5 != 0) {
    piVar4 = *(int **)(lVar5 + 0x148);
    if (piVar4 == (int *)0x0) {
code_r0x022e5864:
      if (*(long *)(lVar5 + 0x140) != 0) {
        operator delete[](void*)();
      }
      if (*(long *)(lVar5 + 0x148) != 0) {
        Aska::TSharedPointerCode::DeleteCounter(int*)();
      }
    }
    else {
      do {
        iVar3 = *piVar4;
        cVar1 = '\x01';
        bVar2 = (bool)ExclusiveMonitorPass(piVar4,0x10);
        if (bVar2) {
          *piVar4 = iVar3 + -1;
          cVar1 = ExclusiveMonitorsStatus();
        }
      } while (cVar1 != '\0');
      if (iVar3 + -1 == 0) goto code_r0x022e5864;
    }
    *(undefined8 *)(lVar5 + 0x140) = 0;
    *(undefined8 *)(lVar5 + 0x148) = 0;
    operator delete(void*)(lVar5);
  }
  iVar3 = 0;
  if (param_1[1] != 0) {
    Aska::TSharedPointerCode::DeleteCounter(int*)();
    iVar3 = 0;
  }
code_r0x022e5898:
  *param_1 = 0;
  param_1[1] = 0;
  return iVar3;
}

// ==== Aska::TBinaryTree<Aska::Yayoi::RawdatPair>::~TBinaryTree()
// vaddr 0x220aef8 | ghidra 0x230aef8 | size 240 | symbol _ZN4Aska11TBinaryTreeINS_5Yayoi10RawdatPairEED2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11TBinaryTreeINS_5Yayoi10RawdatPairEED2Ev(long *param_1)

{
  undefined *puVar1;
  long *plVar2;
  
  *param_1 = (long)(PTR__ZTVN4Aska11TBinaryTreeINS_5Yayoi10RawdatPairEEE_02cb98f0 + 0x10);
  Aska::TBinaryTree<Aska::Yayoi::RawdatPair>::FreeTable()();
  plVar2 = param_1 + 4;
  *param_1 = (long)(PTR__ZTVN4Aska11TPoolLegacyINS_5Yayoi10RawdatPairELb0EEE_02cc15b8 + 0x10);
  if ((*plVar2 != 0) && ((char)param_1[6] != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 6) = 0;
  }
  *plVar2 = 0;
  param_1[5] = 0;
  param_1[7] = 0;
  if (param_1[8] == 0) {
    param_1[2] = (long)(PTR__ZTVN4Aska9TBitArrayIjLb0EEE_02cba038 + 0x10);
  }
  else if ((char)param_1[9] == '\0') {
    param_1[2] = (long)(PTR__ZTVN4Aska9TBitArrayIjLb0EEE_02cba038 + 0x10);
    param_1[8] = 0;
  }
  else {
    operator delete[](void*)();
    param_1[2] = (long)(PTR__ZTVN4Aska9TBitArrayIjLb0EEE_02cba038 + 0x10);
    param_1[8] = 0;
    if ((param_1[4] != 0) && ((char)param_1[6] != '\0')) {
      operator delete[](void*)();
      *(undefined1 *)(param_1 + 6) = 0;
    }
  }
  *plVar2 = 0;
  param_1[5] = 0;
  puVar1 = PTR__ZTVN4Aska13TSmartPointerILb0EEE_02cc2320 + 0x10;
  param_1[2] = (long)puVar1;
  *param_1 = (long)puVar1;
  return;
}

// ==== Aska::TBinaryTree<Aska::Yayoi::RawdatPair>::FreeTable()
// vaddr 0x220b6a0 | ghidra 0x230b6a0 | size 536 | symbol _ZN4Aska11TBinaryTreeINS_5Yayoi10RawdatPairEE9FreeTableEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11TBinaryTreeINS_5Yayoi10RawdatPairEE9FreeTableEv(long *param_1)

{
  int iVar1;
  long lVar2;
  long *plVar3;
  long *plVar4;
  ulong uVar5;
  long *plVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  long *plVar10;
  
  iVar8 = *(int *)((long)param_1 + 0x8c);
  iVar1 = (int)param_1[0xb];
  plVar4 = (long *)param_1[10];
  if (iVar8 == *(int *)((long)param_1 + 0x3c)) {
    iVar9 = iVar8 + -1;
    if (0 < iVar8) {
      lVar2 = 0;
      uVar7 = 0;
      if (*(uint *)((long)param_1 + 0x2c) != 0) goto code_r0x0230b708;
      do {
        do {
          uVar7 = uVar7 + 1;
          lVar2 = lVar2 + 0x60;
        } while (*(uint *)((long)param_1 + 0x2c) <= uVar7);
code_r0x0230b708:
      } while ((*(uint *)(param_1[4] + (ulong)(uVar7 >> 5) * 4) & 1 << (ulong)(uVar7 & 0x1f)) == 0);
      Hint_Prefetch((long *)(param_1[8] + lVar2),0,2,0);
      plVar6 = (long *)(param_1[8] + lVar2);
      do {
        if (iVar9 < 1) {
          plVar10 = (long *)0x0;
        }
        else {
          do {
            do {
              uVar7 = uVar7 + 1;
            } while (*(uint *)((long)param_1 + 0x2c) <= uVar7);
          } while ((*(uint *)(param_1[4] + (ulong)(uVar7 >> 5) * 4) & 1 << (ulong)(uVar7 & 0x1f)) ==
                   0);
          plVar10 = (long *)(param_1[8] + (ulong)uVar7 * 0x60);
          Hint_Prefetch(plVar10,0,2,0);
          iVar9 = iVar9 + -1;
        }
        (**(code **)(*plVar6 + 0x18))(plVar6);
        plVar3 = (long *)param_1[8];
        if (((plVar3 != (long *)0x0) && (plVar3 <= plVar6)) &&
           (plVar6 < plVar3 + (ulong)*(uint *)((long)param_1 + 0x2c) * 0xc)) {
          uVar5 = ((long)plVar6 - (long)plVar3 >> 5) * -0x5555555555555555;
          (**(code **)plVar3[(uVar5 & 0xffffffff) * 0xc])();
          lVar2 = (uVar5 >> 5 & 0x7ffffff) * 4;
          *(uint *)(param_1[4] + lVar2) =
               *(uint *)(param_1[4] + lVar2) & (1 << (ulong)((uint)uVar5 & 0x1f) ^ 0xffffffffU);
          *(int *)((long)param_1 + 0x3c) = *(int *)((long)param_1 + 0x3c) + -1;
        }
        *(int *)((long)param_1 + 0x8c) = *(int *)((long)param_1 + 0x8c) + -1;
        plVar6 = plVar10;
      } while (plVar10 != (long *)0x0);
    }
  }
  else if (iVar1 != 0) {
    plVar6 = plVar4 + (iVar1 - 1);
    iVar8 = iVar1;
    do {
      (**(code **)(*param_1 + 0x18))(param_1,plVar6);
      iVar8 = iVar8 + -1;
      plVar6 = plVar6 + -1;
    } while (iVar8 != 0);
  }
  param_1[0xc] = 0;
  *(undefined4 *)(param_1 + 0xb) = 0;
  param_1[10] = 0;
  param_1[0xf] = 0;
  param_1[0x10] = 0;
  *(undefined1 *)(param_1 + 0x11) = 0;
  param_1[0xe] = 0;
  if (((plVar4 != (long *)0x0) && (iVar1 != 0)) && (plVar4 != param_1 + 0xd)) {
    (*(code *)PTR__ZdaPv_02cb5db8)(plVar4);
    return;
  }
  return;
}

// ==== Aska::TBinaryTree<Aska::MappedAddressSet>::AllocNode(void const*)
// vaddr 0x222ea48 | ghidra 0x232ea48 | size 392 | symbol _ZN4Aska11TBinaryTreeINS_16MappedAddressSetEE9AllocNodeEPKv | lib libSOA-3.7.0.so | 2026-10-04
long * _ZN4Aska11TBinaryTreeINS_16MappedAddressSetEE9AllocNodeEPKv(long param_1,undefined8 param_2)

{
  uint uVar1;
  undefined *puVar2;
  uint uVar3;
  long *plVar4;
  long lVar5;
  uint uVar6;
  long lVar7;
  ulong uVar8;
  ulong uVar9;
  ulong uVar10;
  
  if (*(uint *)(param_1 + 0x3c) < *(uint *)(param_1 + 0x2c)) {
    lVar5 = *(long *)(param_1 + 0x20);
    uVar3 = *(uint *)(param_1 + 0x38);
    do {
      uVar6 = uVar3;
      if (*(uint *)(param_1 + 0x2c) <= uVar6) {
        uVar6 = 0;
      }
      uVar1 = 1 << (ulong)(uVar6 & 0x1f);
      uVar3 = uVar6 + 1;
    } while ((uVar1 & *(uint *)(lVar5 + (ulong)(uVar6 >> 5) * 4)) != 0);
    uVar8 = *(long *)(param_1 + 0x40) + (ulong)uVar6 * 0xb0;
    uVar9 = uVar8;
    do {
      uVar10 = uVar9 + 0x7f & 0xffffffffffffff81;
      Hint_Prefetch(uVar9,0,2,0);
      uVar9 = uVar10;
    } while (uVar10 < uVar8 + 0xb0);
    lVar7 = (ulong)(uVar6 >> 5) * 4;
    *(uint *)(param_1 + 0x38) = uVar6 + 1;
    *(uint *)(param_1 + 0x3c) = *(uint *)(param_1 + 0x3c) + 1;
    puVar2 = PTR__ZTVN4Aska16MappedAddressSetE_02cb8458;
    *(uint *)(lVar5 + lVar7) = *(uint *)(lVar5 + lVar7) | uVar1;
    plVar4 = (long *)(*(long *)(param_1 + 0x40) + (ulong)uVar6 * 0xb0);
    plVar4[4] = 0;
    plVar4[3] = 0;
    plVar4[2] = 0;
    plVar4[1] = 0;
    plVar4[8] = 0;
    plVar4[9] = 0;
    *plVar4 = (long)(puVar2 + 0x10);
    *(undefined2 *)((long)plVar4 + 0x8c) = 0x13;
    plVar4 = (long *)(*(long *)(param_1 + 0x40) + (ulong)uVar6 * 0xb0);
    if (plVar4 == (long *)0x0) goto code_r0x0232eb20;
  }
  else {
code_r0x0232eb20:
    plVar4 = (long *)operator new(unsigned long, std::nothrow_t const&)(0xb0,PTR__ZSt7nothrow_02cb9a80);
    if (plVar4 == (long *)0x0) {
      return (long *)0x0;
    }
    plVar4[8] = 0;
    plVar4[9] = 0;
    puVar2 = PTR__ZTVN4Aska16MappedAddressSetE_02cb8458;
    plVar4[4] = 0;
    plVar4[3] = 0;
    plVar4[2] = 0;
    plVar4[1] = 0;
    *plVar4 = (long)(puVar2 + 0x10);
    *(undefined2 *)((long)plVar4 + 0x8c) = 0x13;
  }
  *(int *)(param_1 + 0x8c) = *(int *)(param_1 + 0x8c) + 1;
  if (*(long *)(param_1 + 0x70) == 0) {
    *(long **)(param_1 + 0x70) = plVar4;
    lVar5 = *(long *)(param_1 + 0x78);
    if (lVar5 == 0) {
      lVar7 = 0;
      goto code_r0x0232eb84;
    }
  }
  else {
    lVar5 = *(long *)(param_1 + 0x78);
    lVar7 = 0;
    if (lVar5 == 0) goto code_r0x0232eb84;
  }
  *(long **)(lVar5 + 0x10) = plVar4;
  lVar7 = *(long *)(param_1 + 0x78);
code_r0x0232eb84:
  plVar4[1] = lVar7;
  plVar4[2] = 0;
  *(long **)(param_1 + 0x78) = plVar4;
  (**(code **)(*plVar4 + 0x28))(plVar4,param_2);
  (**(code **)(*plVar4 + 0x10))(plVar4);
  return plVar4;
}
