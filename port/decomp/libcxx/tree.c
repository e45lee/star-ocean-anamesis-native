// port/decomp/libcxx/tree.c: Ghidra decompiles for the libcxx subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-04 05:14 UTC: tools/decomp.sh '--into' 'libcxx/tree' '__tree_balance_after_insert' '__value_type<unsigned_int,IParameterProperty\*>.*::(__emplace_unique_key_args|destroy)'

// ==== std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, unsigned int, IParameterProperty*&>(unsigned int const&, unsigned int&&, IParameterProperty*&)
// vaddr 0x1160314 | ghidra 0x1260314 | size 328 | symbol _ZNSt6__ndk16__treeINS_12__value_typeIjP18IParameterPropertyEENS_19__map_value_compareIjS4_NS_4lessIjEELb1EEEN9Framework13CSTLAllocatorIS4_NS9_19CSTLMapAllocatorInfEEEE25__emplace_unique_key_argsIjJjRS3_EEENS_4pairINS_15__tree_iteratorIS4_PNS_11__tree_nodeIS4_PvEElEEbEERKT_DpOT0_ | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Type propagation algorithm not settling */

undefined1  [16]
_ZNSt6__ndk16__treeINS_12__value_typeIjP18IParameterPropertyEENS_19__map_value_compareIjS4_NS_4lessIjEELb1EEEN9Framework13CSTLAllocatorIS4_NS9_19CSTLMapAllocatorInfEEEE25__emplace_unique_key_argsIjJjRS3_EEENS_4pairINS_15__tree_iteratorIS4_PNS_11__tree_nodeIS4_PvEElEEbEERKT_DpOT0_
          (long *param_1,uint *param_2,undefined4 *param_3,undefined8 *param_4)

{
  long *******ppppppplVar1;
  undefined8 uVar2;
  long ******pppppplVar3;
  long *******ppppppplVar4;
  long *******ppppppplVar5;
  undefined1 auVar6 [16];
  long *******ppppppplStack_38;
  
  ppppppplVar5 = (long *******)(param_1 + 1);
  if ((long *******)*ppppppplVar5 == (long *******)0x0) {
    ppppppplVar4 = (long *******)*ppppppplVar5;
    ppppppplVar1 = ppppppplVar5;
  }
  else {
    ppppppplVar4 = (long *******)*ppppppplVar5;
    do {
      while (ppppppplVar1 = ppppppplVar4, *param_2 < *(uint *)(ppppppplVar1 + 4)) {
        ppppppplVar4 = (long *******)*ppppppplVar1;
        if ((long *******)*ppppppplVar1 == (long *******)0x0) {
          ppppppplVar4 = (long *******)*ppppppplVar1;
          ppppppplVar5 = ppppppplVar1;
          goto joined_r0x012603bc;
        }
      }
      if (*param_2 <= *(uint *)(ppppppplVar1 + 4)) {
        ppppppplVar5 = (long *******)&ppppppplStack_38;
        ppppppplVar4 = ppppppplVar1;
        goto joined_r0x012603bc;
      }
      ppppppplVar5 = ppppppplVar1 + 1;
      ppppppplVar4 = (long *******)*ppppppplVar5;
    } while ((long *******)*ppppppplVar5 != (long *******)0x0);
    ppppppplVar4 = (long *******)*ppppppplVar5;
  }
joined_r0x012603bc:
  if (ppppppplVar4 == (long *******)0x0) {
    ppppppplStack_38 = ppppppplVar1;
    ppppppplVar4 = (long *******)Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(0x30,&UNK_027dc4e5/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Map.h"*/,0x21);
    if (ppppppplVar4 == (long *******)0x0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    }
    *(undefined4 *)(ppppppplVar4 + 4) = *param_3;
    pppppplVar3 = (long ******)*param_4;
    *ppppppplVar4 = (long ******)0x0;
    ppppppplVar4[1] = (long ******)0x0;
    ppppppplVar4[2] = (long ******)ppppppplVar1;
    ppppppplVar4[5] = pppppplVar3;
    *ppppppplVar5 = (long ******)ppppppplVar4;
    ppppppplVar1 = ppppppplVar4;
    if (*(long *)*param_1 != 0) {
      *param_1 = *(long *)*param_1;
      ppppppplVar1 = (long *******)*ppppppplVar5;
    }
    void std::__ndk1::__tree_balance_after_insert<std::__ndk1::__tree_node_base<void*>*>(std::__ndk1::__tree_node_base<void*>*, std::__ndk1::__tree_node_base<void*>*)(param_1[1],ppppppplVar1);
    uVar2 = 1;
    param_1[2] = param_1[2] + 1;
  }
  else {
    uVar2 = 0;
  }
  auVar6._8_8_ = uVar2;
  auVar6._0_8_ = ppppppplVar4;
  return auVar6;
}

// ==== void std::__ndk1::__tree_balance_after_insert<std::__ndk1::__tree_node_base<void*>*>(std::__ndk1::__tree_node_base<void*>*, std::__ndk1::__tree_node_base<void*>*)
// vaddr 0x116045c | ghidra 0x126045c | size 432 | symbol _ZNSt6__ndk127__tree_balance_after_insertIPNS_16__tree_node_baseIPvEEEEvT_S5_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZNSt6__ndk127__tree_balance_after_insertIPNS_16__tree_node_baseIPvEEEEvT_S5_
               (long *param_1,long *param_2)

{
  bool bVar1;
  long *plVar2;
  long *plVar3;
  long lVar4;
  undefined8 *puVar5;
  long lVar6;
  long *plVar7;
  
  bVar1 = param_2 == param_1;
  *(bool *)(param_2 + 3) = bVar1;
  do {
    if ((bVar1) || (plVar3 = (long *)param_2[2], (char)plVar3[3] != '\0')) {
      return;
    }
    plVar2 = (long *)plVar3[2];
    plVar7 = (long *)*plVar2;
    if (plVar7 == plVar3) {
      if ((plVar2[1] == 0) || (plVar7 = (long *)(plVar2[1] + 0x18), *(char *)plVar7 != '\0')) {
        if ((long *)*plVar3 != param_2) {
          plVar7 = (long *)plVar3[1];
          lVar4 = *plVar7;
          plVar3[1] = lVar4;
          if (lVar4 != 0) {
            *(long **)(lVar4 + 0x10) = plVar3;
            plVar2 = (long *)plVar3[2];
          }
          plVar7[2] = (long)plVar2;
          puVar5 = (undefined8 *)plVar3[2];
          if ((long *)*puVar5 != plVar3) {
            puVar5 = puVar5 + 1;
          }
          *puVar5 = plVar7;
          *plVar7 = (long)plVar3;
          plVar3[2] = (long)plVar7;
          plVar2 = (long *)plVar7[2];
          plVar3 = plVar7;
        }
        *(undefined1 *)(plVar3 + 3) = 1;
        lVar4 = *plVar2;
        *(undefined1 *)(plVar2 + 3) = 0;
        lVar6 = *(long *)(lVar4 + 8);
        *plVar2 = lVar6;
        if (lVar6 != 0) {
          *(long **)(lVar6 + 0x10) = plVar2;
        }
        *(long *)(lVar4 + 0x10) = plVar2[2];
        plVar3 = (long *)plVar2[2];
        if ((long *)*plVar3 != plVar2) {
          plVar3 = plVar3 + 1;
        }
        *plVar3 = lVar4;
        *(long **)(lVar4 + 8) = plVar2;
        plVar2[2] = lVar4;
        return;
      }
    }
    else if ((plVar7 == (long *)0x0) || (plVar7 = plVar7 + 3, (char)*plVar7 != '\0')) {
      if ((long *)*plVar3 == param_2) {
        plVar7 = (long *)*plVar3;
        lVar4 = plVar7[1];
        *plVar3 = lVar4;
        if (lVar4 != 0) {
          *(long **)(lVar4 + 0x10) = plVar3;
          plVar2 = (long *)plVar3[2];
        }
        plVar7[2] = (long)plVar2;
        puVar5 = (undefined8 *)plVar3[2];
        if ((long *)*puVar5 != plVar3) {
          puVar5 = puVar5 + 1;
        }
        *puVar5 = plVar7;
        plVar7[1] = (long)plVar3;
        plVar3[2] = (long)plVar7;
        plVar2 = (long *)plVar7[2];
        plVar3 = plVar7;
      }
      *(undefined1 *)(plVar3 + 3) = 1;
      plVar3 = (long *)plVar2[1];
      *(undefined1 *)(plVar2 + 3) = 0;
      lVar4 = *plVar3;
      plVar2[1] = lVar4;
      if (lVar4 != 0) {
        *(long **)(lVar4 + 0x10) = plVar2;
      }
      plVar3[2] = plVar2[2];
      puVar5 = (undefined8 *)plVar2[2];
      if ((long *)*puVar5 != plVar2) {
        puVar5 = puVar5 + 1;
      }
      *puVar5 = plVar3;
      *plVar3 = (long)plVar2;
      plVar2[2] = (long)plVar3;
      return;
    }
    bVar1 = plVar2 == param_1;
    *(undefined1 *)(plVar3 + 3) = 1;
    *(bool *)(plVar2 + 3) = bVar1;
    *(char *)plVar7 = '\x01';
    param_2 = plVar2;
  } while( true );
}

// ==== std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*)
// vaddr 0x1161438 | ghidra 0x1261438 | size 72 | symbol _ZNSt6__ndk16__treeINS_12__value_typeIjP18IParameterPropertyEENS_19__map_value_compareIjS4_NS_4lessIjEELb1EEEN9Framework13CSTLAllocatorIS4_NS9_19CSTLMapAllocatorInfEEEE7destroyEPNS_11__tree_nodeIS4_PvEE | lib libSOA-3.7.0.so | 2026-10-04
void _ZNSt6__ndk16__treeINS_12__value_typeIjP18IParameterPropertyEENS_19__map_value_compareIjS4_NS_4lessIjEELb1EEEN9Framework13CSTLAllocatorIS4_NS9_19CSTLMapAllocatorInfEEEE7destroyEPNS_11__tree_nodeIS4_PvEE
               (undefined8 param_1,undefined8 *param_2)

{
  if (param_2 != (undefined8 *)0x0) {
    std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*)(param_1,*param_2);
    std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*)(param_1,param_2[1]);
    (*(code *)PTR__ZN9Framework37CAssignedMemoryManagerForSTLAllocator4FreeEPv_02ca11c0)(param_2);
    return;
  }
  return;
}
