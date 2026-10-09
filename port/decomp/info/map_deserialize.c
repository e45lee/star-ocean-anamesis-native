// port/decomp/info/map_deserialize.c: Ghidra decompiles for the info subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-08 23:34 UTC: tools/decomp.sh '--into' 'info/map_deserialize' 'IInfoBaseMap<.*>::DeserializeChild'

// ==== IInfoBaseMap<unsigned long, CFactorInfo>::DeserializeChild(Aska::ASON::AValue::AMap const*)
// vaddr 0x12b2990 | ghidra 0x13b2990 | size 596 | symbol _ZN12IInfoBaseMapIm11CFactorInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN12IInfoBaseMapIm11CFactorInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE
          (long *param_1,long *param_2)

{
  uint uVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined *puVar5;
  int iVar6;
  long *plVar7;
  long lVar8;
  long *plVar9;
  ulong uVar10;
  long *plVar11;
  long *plVar12;
  undefined *puStack_d0;
  undefined8 *puStack_c8;
  undefined8 auStack_c0 [2];
  undefined8 *puStack_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined *puStack_98;
  undefined8 uStack_90;
  undefined1 uStack_88;
  undefined1 auStack_80 [24];
  ulong uStack_68;
  
  plVar12 = param_1 + 8;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CFactorInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CFactorInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CFactorInfo>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CFactorInfo>, void*>*)(param_1 + 7,*plVar12);
  param_1[7] = (long)plVar12;
  param_1[8] = 0;
  param_1[9] = 0;
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027fb04d/*"C:\BAS_Submission\Client\Project\Android\BASAndroid.NativeActivity\..\..\..\Source\Game/Battle/Utility/../../Parameter/Info/InfoBase.h"*/,0x1c1,&UNK_027dc58a/*"apParser is null."*/);
    iVar6 = iRam0000000000000008;
  }
  else {
    iVar6 = (int)param_2[1];
  }
  if (iVar6 != 0) {
    uVar10 = 0;
    puVar2 = PTR__ZTV11CFactorInfo_02cc25f0 + 0x10;
    puVar3 = PTR__ZTV22CParameterPropertyBaseILj19EE_02cc4c98 + 0x10;
    puVar4 = PTR__ZTV23CParameterPropertyValueIjLj19E18CPropertyConverterE_02cc13e8 + 0x10;
    puVar5 = PTR__ZTV8InfoBase_02cc49c8 + 0x10;
    do {
      uStack_68 = (**(code **)(*param_1 + 0x20))(param_1,*param_2 + uVar10 * 0x40);
      plVar7 = (long *)param_1[8];
      plVar9 = plVar12;
      if ((long *)param_1[8] == (long *)0x0) {
code_r0x013b2adc:
        memset(auStack_c0,0,0x58);
        uStack_a8 = 0;
        uStack_a0 = 0;
        uStack_90 = 0;
        uStack_88 = 0;
        puStack_d0 = puVar2;
        puStack_c8 = auStack_c0;
        puStack_b0 = &uStack_a8;
        puStack_98 = puVar3;
        Framework::CHash32::CHash32()(auStack_80);
        puStack_98 = puVar4;
        lVar8 = std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned long, CFactorInfo>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CFactorInfo>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CFactorInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CFactorInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CFactorInfo>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned long, unsigned long&, CFactorInfo>(unsigned long const&, unsigned long&, CFactorInfo&&)(param_1 + 7,&uStack_68,&uStack_68,&puStack_d0);
        puStack_d0 = puVar2;
        puStack_98 = puVar3;
        Framework::CHash32::~CHash32()(auStack_80);
        puStack_d0 = puVar5;
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*)(&puStack_b0,uStack_a8);
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*)(&puStack_c8,auStack_c0[0]);
        plVar11 = (long *)(lVar8 + 0x28);
        (**(code **)(*plVar11 + 0x10))(plVar11);
      }
      else {
        do {
          while (plVar11 = plVar7, (ulong)plVar11[4] < uStack_68) {
            plVar7 = (long *)plVar11[1];
            if ((long *)plVar11[1] == (long *)0x0) {
              plVar11 = plVar9;
              if (plVar9 != plVar12) goto code_r0x013b2ac0;
              goto code_r0x013b2adc;
            }
          }
          plVar7 = (long *)*plVar11;
          plVar9 = plVar11;
        } while ((long *)*plVar11 != (long *)0x0);
        if (plVar11 == plVar12) goto code_r0x013b2adc;
code_r0x013b2ac0:
        if ((uStack_68 < (ulong)plVar11[4]) || (plVar11 == plVar12)) goto code_r0x013b2adc;
        plVar11 = plVar11 + 5;
      }
      lVar8 = *param_2 + uVar10 * 0x40;
      iVar6 = *(int *)(lVar8 + 0x20);
      if (iVar6 == 6) {
        (**(code **)*plVar11)(plVar11,lVar8 + 0x28);
      }
      else if (iVar6 == 7) {
        (**(code **)(*plVar11 + 8))(plVar11,*param_2 + uVar10 * 0x40 + 0x28);
      }
      uVar1 = (int)uVar10 + 1;
      uVar10 = (ulong)uVar1;
    } while (uVar1 < *(uint *)(param_2 + 1));
  }
  return 1;
}

// ==== IInfoBaseMap<unsigned long, CStackItemInfo>::DeserializeChild(Aska::ASON::AValue::AMap const*)
// vaddr 0x13efd30 | ghidra 0x14efd30 | size 1420 | symbol _ZN12IInfoBaseMapIm14CStackItemInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Type propagation algorithm not settling */

undefined8
_ZN12IInfoBaseMapIm14CStackItemInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE
          (long *param_1,long *param_2)

{
  uint uVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined *puVar5;
  undefined *puVar6;
  undefined *puVar7;
  undefined *puVar8;
  undefined *puVar9;
  undefined *puVar10;
  undefined *puVar11;
  undefined *puVar12;
  undefined *puVar13;
  undefined *puVar14;
  undefined *puVar15;
  undefined *puVar16;
  undefined *puVar17;
  long lVar18;
  int iVar19;
  long *plVar20;
  long *******ppppppplVar21;
  long *******ppppppplVar22;
  ulong uVar23;
  long *******ppppppplVar24;
  long *******ppppppplVar25;
  long *******ppppppplVar26;
  undefined *puStack_210;
  undefined8 *puStack_208;
  undefined8 auStack_200 [2];
  undefined8 *puStack_1f0;
  undefined8 uStack_1e8;
  undefined8 uStack_1e0;
  undefined *puStack_1d8;
  undefined8 uStack_1d0;
  undefined1 uStack_1c8;
  undefined1 auStack_1c0 [24];
  undefined *puStack_1a8;
  undefined8 uStack_1a0;
  undefined1 uStack_198;
  undefined1 auStack_190 [24];
  undefined *puStack_178;
  undefined8 uStack_170;
  undefined1 uStack_168;
  undefined1 auStack_160 [24];
  undefined *puStack_148;
  undefined8 uStack_140;
  undefined1 uStack_138;
  undefined1 auStack_130 [24];
  undefined *puStack_118;
  undefined8 uStack_110;
  undefined1 uStack_108;
  undefined1 auStack_100 [24];
  undefined *puStack_e8;
  undefined8 uStack_e0;
  undefined1 uStack_d8;
  undefined1 auStack_d0 [24];
  undefined *puStack_b8;
  undefined8 uStack_b0;
  undefined1 uStack_a8;
  undefined1 auStack_a0 [24];
  long ******pppppplStack_88;
  long *******appppppplStack_80 [3];
  long *******ppppppplStack_68;
  
  ppppppplVar24 = (long *******)(param_1 + 8);
  plVar20 = param_1 + 7;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CStackItemInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CStackItemInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CStackItemInfo>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CStackItemInfo>, void*>*)(plVar20,*ppppppplVar24);
  param_1[7] = (long)ppppppplVar24;
  param_1[8] = 0;
  param_1[9] = 0;
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dc3b5/*"C:\BAS_Submission\Client\Project\Android\BASAndroid.NativeActivity\..\..\..\Source\Game/Parameter/Info/InfoBase.h"*/,0x1c1,&UNK_027dc58a/*"apParser is null."*/);
    iVar19 = iRam0000000000000008;
  }
  else {
    iVar19 = (int)param_2[1];
  }
  if (iVar19 != 0) {
    puVar2 = PTR__ZTV14CStackItemInfo_02cc42e8 + 0x10;
    puVar3 = PTR__ZTV22CParameterPropertyBaseILj16EE_02cb9c20 + 0x10;
    puVar4 = PTR__ZTV23CParameterPropertyValueIjLj16E18CPropertyConverterE_02cbd008 + 0x10;
    puVar5 = PTR__ZTV22CParameterPropertyBaseILj17EE_02cba1e8 + 0x10;
    puVar6 = PTR__ZTV23CParameterPropertyValueIjLj17E18CPropertyConverterE_02cbb3b8 + 0x10;
    puVar7 = PTR__ZTV23CParameterPropertyValueIjLj18E18CPropertyConverterE_02cbcd58 + 0x10;
    puVar8 = PTR__ZTV23CParameterPropertyValueIjLj19E18CPropertyConverterE_02cc13e8 + 0x10;
    puVar9 = PTR__ZTV23CParameterPropertyValueIjLj20E18CPropertyConverterE_02cc2ce0 + 0x10;
    puVar10 = PTR__ZTV23CParameterPropertyValueIjLj21E18CPropertyConverterE_02cbeae0 + 0x10;
    puVar11 = PTR__ZTV23CParameterPropertyValueIjLj23E18CPropertyConverterE_02cb7d90 + 0x10;
    puVar12 = PTR__ZTV8InfoBase_02cc49c8 + 0x10;
    puVar13 = PTR__ZTV22CParameterPropertyBaseILj18EE_02cbe238 + 0x10;
    puVar14 = PTR__ZTV22CParameterPropertyBaseILj19EE_02cc4c98 + 0x10;
    puVar15 = PTR__ZTV22CParameterPropertyBaseILj20EE_02cc0d08 + 0x10;
    puVar16 = PTR__ZTV22CParameterPropertyBaseILj21EE_02cc1310 + 0x10;
    uVar23 = 0;
    puVar17 = PTR__ZTV22CParameterPropertyBaseILj23EE_02cbad98 + 0x10;
    do {
      pppppplStack_88 =
           (long ******)(**(code **)(*param_1 + 0x20))(param_1,*param_2 + uVar23 * 0x40);
      ppppppplVar22 = (long *******)param_1[8];
      ppppppplVar21 = ppppppplVar24;
      if ((long *******)param_1[8] == (long *******)0x0) {
code_r0x014eff78:
        memset(auStack_200,0,0x178);
        uStack_1e8 = 0;
        uStack_1e0 = 0;
        uStack_1c8 = 0;
        uStack_1d0 = 0;
        puStack_210 = puVar2;
        puStack_208 = auStack_200;
        puStack_1f0 = &uStack_1e8;
        puStack_1d8 = puVar3;
        Framework::CHash32::CHash32()(auStack_1c0);
        uStack_198 = 0;
        uStack_1a0 = 0;
        puStack_1d8 = puVar4;
        puStack_1a8 = puVar5;
        Framework::CHash32::CHash32()(auStack_190);
        uStack_168 = 0;
        uStack_170 = 0;
        puStack_1a8 = puVar6;
        puStack_178 = puVar13;
        Framework::CHash32::CHash32()(auStack_160);
        uStack_138 = 0;
        uStack_140 = 0;
        puStack_178 = puVar7;
        puStack_148 = puVar14;
        Framework::CHash32::CHash32()(auStack_130);
        uStack_108 = 0;
        uStack_110 = 0;
        puStack_148 = puVar8;
        puStack_118 = puVar15;
        Framework::CHash32::CHash32()(auStack_100);
        uStack_d8 = 0;
        uStack_e0 = 0;
        puStack_118 = puVar9;
        puStack_e8 = puVar16;
        Framework::CHash32::CHash32()(auStack_d0);
        uStack_b0 = 0;
        uStack_a8 = 0;
        puStack_e8 = puVar10;
        puStack_b8 = puVar17;
        Framework::CHash32::CHash32()(auStack_a0);
        ppppppplVar22 = (long *******)*ppppppplVar24;
        if ((long *******)*ppppppplVar24 == (long *******)0x0) {
          ppppppplVar25 = (long *******)*ppppppplVar24;
          ppppppplVar21 = ppppppplVar24;
          ppppppplVar26 = ppppppplVar24;
        }
        else {
          do {
            while (ppppppplVar21 = ppppppplVar22, ppppppplVar21[4] <= pppppplStack_88) {
              if (pppppplStack_88 <= ppppppplVar21[4]) {
                ppppppplVar25 = ppppppplVar21;
                ppppppplVar26 = (long *******)&ppppppplStack_68;
                goto joined_r0x014f00e0;
              }
              ppppppplVar26 = ppppppplVar21 + 1;
              ppppppplVar22 = (long *******)*ppppppplVar26;
              if ((long *******)*ppppppplVar26 == (long *******)0x0) {
                ppppppplVar25 = (long *******)*ppppppplVar26;
                goto joined_r0x014f00e0;
              }
            }
            ppppppplVar22 = (long *******)*ppppppplVar21;
          } while ((long *******)*ppppppplVar21 != (long *******)0x0);
          ppppppplVar25 = (long *******)*ppppppplVar21;
          ppppppplVar26 = ppppppplVar21;
        }
joined_r0x014f00e0:
        ppppppplStack_68 = ppppppplVar21;
        if (ppppppplVar25 == (long *******)0x0) {
          puStack_b8 = puVar11;
          std::__ndk1::unique_ptr<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CStackItemInfo>, void*>, std::__ndk1::__tree_node_destructor<Framework::CSTLAllocator<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CStackItemInfo>, void*>, Framework::CSTLMapAllocatorInf> > > std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CStackItemInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CStackItemInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CStackItemInfo>, Framework::CSTLMapAllocatorInf> >::__construct_node<unsigned long&, CStackItemInfo>(unsigned long&, CStackItemInfo&&)(appppppplStack_80,plVar20,&pppppplStack_88,&puStack_210);
          *appppppplStack_80[0] = (long ******)0x0;
          appppppplStack_80[0][1] = (long ******)0x0;
          appppppplStack_80[0][2] = (long ******)ppppppplVar21;
          *ppppppplVar26 = (long ******)appppppplStack_80[0];
          ppppppplVar22 = appppppplStack_80[0];
          if (*(long *)*plVar20 != 0) {
            *plVar20 = *(long *)*plVar20;
            ppppppplVar22 = (long *******)*ppppppplVar26;
          }
          void std::__ndk1::__tree_balance_after_insert<std::__ndk1::__tree_node_base<void*>*>(std::__ndk1::__tree_node_base<void*>*, std::__ndk1::__tree_node_base<void*>*)(param_1[8],ppppppplVar22);
          param_1[9] = param_1[9] + 1;
          ppppppplVar25 = appppppplStack_80[0];
        }
        puStack_210 = PTR__ZTV14CStackItemInfo_02cc42e8 + 0x10;
        puStack_b8 = PTR__ZTV22CParameterPropertyBaseILj23EE_02cbad98 + 0x10;
        Framework::CHash32::~CHash32()(auStack_a0);
        puStack_e8 = PTR__ZTV22CParameterPropertyBaseILj21EE_02cc1310 + 0x10;
        Framework::CHash32::~CHash32()(auStack_d0);
        puStack_118 = PTR__ZTV22CParameterPropertyBaseILj20EE_02cc0d08 + 0x10;
        Framework::CHash32::~CHash32()(auStack_100);
        puStack_148 = PTR__ZTV22CParameterPropertyBaseILj19EE_02cc4c98 + 0x10;
        Framework::CHash32::~CHash32()(auStack_130);
        puStack_178 = PTR__ZTV22CParameterPropertyBaseILj18EE_02cbe238 + 0x10;
        Framework::CHash32::~CHash32()(auStack_160);
        puStack_1a8 = PTR__ZTV22CParameterPropertyBaseILj17EE_02cba1e8 + 0x10;
        Framework::CHash32::~CHash32()(auStack_190);
        puStack_1d8 = PTR__ZTV22CParameterPropertyBaseILj16EE_02cb9c20 + 0x10;
        Framework::CHash32::~CHash32()(auStack_1c0);
        puStack_210 = puVar12;
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*)(&puStack_1f0,uStack_1e8);
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*)(&puStack_208,auStack_200[0]);
        ppppppplVar25 = ppppppplVar25 + 5;
        (*(code *)(*ppppppplVar25)[2])(ppppppplVar25);
      }
      else {
        do {
          while (ppppppplVar25 = ppppppplVar22, ppppppplVar25[4] < pppppplStack_88) {
            ppppppplVar22 = (long *******)ppppppplVar25[1];
            if ((long *******)ppppppplVar25[1] == (long *******)0x0) {
              ppppppplVar25 = ppppppplVar21;
              if (ppppppplVar21 != ppppppplVar24) goto code_r0x014eff5c;
              goto code_r0x014eff78;
            }
          }
          ppppppplVar22 = (long *******)*ppppppplVar25;
          ppppppplVar21 = ppppppplVar25;
        } while ((long *******)*ppppppplVar25 != (long *******)0x0);
        if (ppppppplVar25 == ppppppplVar24) goto code_r0x014eff78;
code_r0x014eff5c:
        if ((pppppplStack_88 < ppppppplVar25[4]) || (ppppppplVar25 == ppppppplVar24))
        goto code_r0x014eff78;
        ppppppplVar25 = ppppppplVar25 + 5;
      }
      lVar18 = *param_2 + uVar23 * 0x40;
      iVar19 = *(int *)(lVar18 + 0x20);
      if (iVar19 == 6) {
        (*(code *)**ppppppplVar25)(ppppppplVar25,lVar18 + 0x28);
      }
      else if (iVar19 == 7) {
        (*(code *)(*ppppppplVar25)[1])(ppppppplVar25,*param_2 + uVar23 * 0x40 + 0x28);
      }
      uVar1 = (int)uVar23 + 1;
      uVar23 = (ulong)uVar1;
    } while (uVar1 < *(uint *)(param_2 + 1));
  }
  return 1;
}

// ==== IInfoBaseMap<unsigned long, CDeepSpaceMissionInfo>::DeserializeChild(Aska::ASON::AValue::AMap const*)
// vaddr 0x13f31a8 | ghidra 0x14f31a8 | size 436 | symbol _ZN12IInfoBaseMapIm21CDeepSpaceMissionInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN12IInfoBaseMapIm21CDeepSpaceMissionInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE
          (long *param_1,long *param_2)

{
  uint uVar1;
  int iVar2;
  long *plVar3;
  long lVar4;
  long *plVar5;
  ulong uVar6;
  long *plVar7;
  long *plVar8;
  undefined1 auStack_290 [584];
  ulong uStack_48;
  
  plVar8 = param_1 + 8;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CDeepSpaceMissionInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CDeepSpaceMissionInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CDeepSpaceMissionInfo>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CDeepSpaceMissionInfo>, void*>*)(param_1 + 7,*plVar8);
  param_1[7] = (long)plVar8;
  param_1[8] = 0;
  param_1[9] = 0;
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dc3b5/*"C:\BAS_Submission\Client\Project\Android\BASAndroid.NativeActivity\..\..\..\Source\Game/Parameter/Info/InfoBase.h"*/,0x1c1,&UNK_027dc58a/*"apParser is null."*/);
    iVar2 = iRam0000000000000008;
  }
  else {
    iVar2 = (int)param_2[1];
  }
  if (iVar2 != 0) {
    uVar6 = 0;
    do {
      uStack_48 = (**(code **)(*param_1 + 0x20))(param_1,*param_2 + uVar6 * 0x40);
      plVar3 = (long *)param_1[8];
      plVar5 = plVar8;
      if ((long *)param_1[8] == (long *)0x0) {
code_r0x014f329c:
        memset(auStack_290,0,0x248);
        CDeepSpaceMissionInfo::CDeepSpaceMissionInfo()(auStack_290);
        lVar4 = std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned long, CDeepSpaceMissionInfo>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CDeepSpaceMissionInfo>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CDeepSpaceMissionInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CDeepSpaceMissionInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CDeepSpaceMissionInfo>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned long, unsigned long&, CDeepSpaceMissionInfo>(unsigned long const&, unsigned long&, CDeepSpaceMissionInfo&&)(param_1 + 7,&uStack_48,&uStack_48,auStack_290);
        CDeepSpaceMissionInfo::~CDeepSpaceMissionInfo()(auStack_290);
        plVar7 = (long *)(lVar4 + 0x28);
        (**(code **)(*plVar7 + 0x10))(plVar7);
      }
      else {
        do {
          while (plVar7 = plVar3, (ulong)plVar7[4] < uStack_48) {
            plVar3 = (long *)plVar7[1];
            if ((long *)plVar7[1] == (long *)0x0) {
              plVar7 = plVar5;
              if (plVar5 != plVar8) goto code_r0x014f3280;
              goto code_r0x014f329c;
            }
          }
          plVar3 = (long *)*plVar7;
          plVar5 = plVar7;
        } while ((long *)*plVar7 != (long *)0x0);
        if (plVar7 == plVar8) goto code_r0x014f329c;
code_r0x014f3280:
        if ((uStack_48 < (ulong)plVar7[4]) || (plVar7 == plVar8)) goto code_r0x014f329c;
        plVar7 = plVar7 + 5;
      }
      lVar4 = *param_2 + uVar6 * 0x40;
      iVar2 = *(int *)(lVar4 + 0x20);
      if (iVar2 == 6) {
        (**(code **)*plVar7)(plVar7,lVar4 + 0x28);
      }
      else if (iVar2 == 7) {
        (**(code **)(*plVar7 + 8))(plVar7,*param_2 + uVar6 * 0x40 + 0x28);
      }
      uVar1 = (int)uVar6 + 1;
      uVar6 = (ulong)uVar1;
    } while (uVar1 < *(uint *)(param_2 + 1));
  }
  return 1;
}

// ==== IInfoBaseMap<unsigned long, CDeepSpaceBonusApplyInfoList>::DeserializeChild(Aska::ASON::AValue::AMap const*)
// vaddr 0x13f3df8 | ghidra 0x14f3df8 | size 792 | symbol _ZN12IInfoBaseMapIm28CDeepSpaceBonusApplyInfoListE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Type propagation algorithm not settling */

undefined8
_ZN12IInfoBaseMapIm28CDeepSpaceBonusApplyInfoListE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE
          (long *param_1,long *param_2)

{
  uint uVar1;
  undefined *puVar2;
  undefined *puVar3;
  long lVar4;
  int iVar5;
  undefined *puVar6;
  long *plVar7;
  long *******ppppppplVar8;
  ulong uVar9;
  long *******ppppppplVar10;
  long *******ppppppplVar11;
  long *******ppppppplVar12;
  long *******ppppppplVar13;
  undefined *puStack_d8;
  undefined8 *puStack_d0;
  undefined8 uStack_c8;
  undefined8 uStack_c0;
  undefined8 *puStack_b8;
  undefined8 uStack_b0;
  undefined8 uStack_a8;
  undefined8 *puStack_a0;
  undefined8 uStack_98;
  undefined8 uStack_90;
  long ******pppppplStack_88;
  long *******appppppplStack_80 [3];
  long *******ppppppplStack_68;
  
  ppppppplVar13 = (long *******)(param_1 + 8);
  plVar7 = param_1 + 7;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CDeepSpaceBonusApplyInfoList>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CDeepSpaceBonusApplyInfoList>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CDeepSpaceBonusApplyInfoList>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CDeepSpaceBonusApplyInfoList>, void*>*)(plVar7,*ppppppplVar13);
  param_1[7] = (long)ppppppplVar13;
  param_1[8] = 0;
  param_1[9] = 0;
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dc3b5/*"C:\BAS_Submission\Client\Project\Android\BASAndroid.NativeActivity\..\..\..\Source\Game/Parameter/Info/InfoBase.h"*/,0x1c1,&UNK_027dc58a/*"apParser is null."*/);
    iVar5 = iRam0000000000000008;
  }
  else {
    iVar5 = (int)param_2[1];
  }
  if (iVar5 != 0) {
    puVar2 = PTR__ZTV28CDeepSpaceBonusApplyInfoList_02cbb3b0 + 0x10;
    uVar9 = 0;
    puVar3 = PTR__ZTV8InfoBase_02cc49c8 + 0x10;
    do {
      pppppplStack_88 = (long ******)(**(code **)(*param_1 + 0x20))(param_1,*param_2 + uVar9 * 0x40)
      ;
      ppppppplVar11 = (long *******)param_1[8];
      ppppppplVar10 = ppppppplVar11;
      puVar6 = puVar2;
      ppppppplVar8 = ppppppplVar13;
      if (ppppppplVar11 == (long *******)0x0) {
code_r0x014f3fc4:
        puStack_d8 = puVar6;
        ppppppplVar12 = (long *******)*ppppppplVar13;
        ppppppplVar10 = ppppppplVar13;
        ppppppplVar8 = ppppppplVar13;
joined_r0x014f3fa0:
        puStack_d0 = &uStack_c8;
        puStack_b8 = &uStack_b0;
        puStack_a0 = &uStack_98;
        ppppppplStack_68 = ppppppplVar8;
        if (ppppppplVar12 == (long *******)0x0) {
          uStack_90 = 0;
          uStack_98 = 0;
          uStack_a8 = 0;
          uStack_b0 = 0;
          uStack_c0 = 0;
          uStack_c8 = 0;
          std::__ndk1::unique_ptr<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CDeepSpaceBonusApplyInfoList>, void*>, std::__ndk1::__tree_node_destructor<Framework::CSTLAllocator<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CDeepSpaceBonusApplyInfoList>, void*>, Framework::CSTLMapAllocatorInf> > > std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CDeepSpaceBonusApplyInfoList>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CDeepSpaceBonusApplyInfoList>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CDeepSpaceBonusApplyInfoList>, Framework::CSTLMapAllocatorInf> >::__construct_node<unsigned long&, CDeepSpaceBonusApplyInfoList>(unsigned long&, CDeepSpaceBonusApplyInfoList&&)(appppppplStack_80,plVar7,&pppppplStack_88,&puStack_d8);
          *appppppplStack_80[0] = (long ******)0x0;
          appppppplStack_80[0][1] = (long ******)0x0;
          appppppplStack_80[0][2] = (long ******)ppppppplVar8;
          *ppppppplVar10 = (long ******)appppppplStack_80[0];
          ppppppplVar11 = appppppplStack_80[0];
          if (*(long *)*plVar7 != 0) {
            *plVar7 = *(long *)*plVar7;
            ppppppplVar11 = (long *******)*ppppppplVar10;
          }
          void std::__ndk1::__tree_balance_after_insert<std::__ndk1::__tree_node_base<void*>*>(std::__ndk1::__tree_node_base<void*>*, std::__ndk1::__tree_node_base<void*>*)(param_1[8],ppppppplVar11);
          param_1[9] = param_1[9] + 1;
          ppppppplVar12 = appppppplStack_80[0];
        }
        else {
          uStack_90 = 0;
          uStack_98 = 0;
          uStack_a8 = 0;
          uStack_b0 = 0;
          uStack_c0 = 0;
          uStack_c8 = 0;
        }
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CDeepSpaceBonusApplyInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CDeepSpaceBonusApplyInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CDeepSpaceBonusApplyInfo>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CDeepSpaceBonusApplyInfo>, void*>*)(&puStack_a0,uStack_98);
        puStack_d8 = puVar3;
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*)(&puStack_b8,uStack_b0);
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*)(&puStack_d0,uStack_c8);
        ppppppplVar12 = ppppppplVar12 + 5;
        (*(code *)(*ppppppplVar12)[2])(ppppppplVar12);
      }
      else {
        do {
          while (ppppppplVar12 = ppppppplVar10, pppppplStack_88 <= ppppppplVar12[4]) {
            ppppppplVar10 = (long *******)*ppppppplVar12;
            ppppppplVar8 = ppppppplVar12;
            if ((long *******)*ppppppplVar12 == (long *******)0x0) {
              if (ppppppplVar12 != ppppppplVar13) goto code_r0x014f3f1c;
              goto code_r0x014f3f38;
            }
          }
          ppppppplVar10 = (long *******)ppppppplVar12[1];
        } while ((long *******)ppppppplVar12[1] != (long *******)0x0);
        ppppppplVar12 = ppppppplVar8;
        if (ppppppplVar8 == ppppppplVar13) {
code_r0x014f3f38:
          puStack_d8 = PTR__ZTV28CDeepSpaceBonusApplyInfoList_02cbb3b0 + 0x10;
          puVar6 = puStack_d8;
          if (ppppppplVar11 == (long *******)0x0) goto code_r0x014f3fc4;
          do {
            while (ppppppplVar8 = ppppppplVar11, pppppplStack_88 < ppppppplVar8[4]) {
              ppppppplVar11 = (long *******)*ppppppplVar8;
              if ((long *******)*ppppppplVar8 == (long *******)0x0) {
                ppppppplVar10 = ppppppplVar8;
                ppppppplVar12 = (long *******)*ppppppplVar8;
                goto joined_r0x014f3fa0;
              }
            }
            if (pppppplStack_88 <= ppppppplVar8[4]) {
              ppppppplVar10 = (long *******)&ppppppplStack_68;
              ppppppplVar12 = ppppppplVar8;
              goto joined_r0x014f3fa0;
            }
            ppppppplVar10 = ppppppplVar8 + 1;
            ppppppplVar11 = (long *******)*ppppppplVar10;
          } while ((long *******)*ppppppplVar10 != (long *******)0x0);
          ppppppplVar12 = (long *******)*ppppppplVar10;
          goto joined_r0x014f3fa0;
        }
code_r0x014f3f1c:
        if ((pppppplStack_88 < ppppppplVar12[4]) || (ppppppplVar12 == ppppppplVar13))
        goto code_r0x014f3f38;
        ppppppplVar12 = ppppppplVar12 + 5;
      }
      lVar4 = *param_2 + uVar9 * 0x40;
      iVar5 = *(int *)(lVar4 + 0x20);
      if (iVar5 == 6) {
        (*(code *)**ppppppplVar12)(ppppppplVar12,lVar4 + 0x28);
      }
      else if (iVar5 == 7) {
        (*(code *)(*ppppppplVar12)[1])(ppppppplVar12,*param_2 + uVar9 * 0x40 + 0x28);
      }
      uVar1 = (int)uVar9 + 1;
      uVar9 = (ulong)uVar1;
    } while (uVar1 < *(uint *)(param_2 + 1));
  }
  return 1;
}

// ==== IInfoBaseMap<unsigned long, CDeepSpaceBonusApplyInfo>::DeserializeChild(Aska::ASON::AValue::AMap const*)
// vaddr 0x13f4704 | ghidra 0x14f4704 | size 596 | symbol _ZN12IInfoBaseMapIm24CDeepSpaceBonusApplyInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN12IInfoBaseMapIm24CDeepSpaceBonusApplyInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE
          (long *param_1,long *param_2)

{
  uint uVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined *puVar5;
  int iVar6;
  long *plVar7;
  long lVar8;
  long *plVar9;
  ulong uVar10;
  long *plVar11;
  long *plVar12;
  undefined *puStack_d0;
  undefined8 *puStack_c8;
  undefined8 auStack_c0 [2];
  undefined8 *puStack_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined *puStack_98;
  undefined8 uStack_90;
  undefined1 uStack_88;
  undefined1 auStack_80 [24];
  ulong uStack_68;
  
  plVar12 = param_1 + 8;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CDeepSpaceBonusApplyInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CDeepSpaceBonusApplyInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CDeepSpaceBonusApplyInfo>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CDeepSpaceBonusApplyInfo>, void*>*)(param_1 + 7,*plVar12);
  param_1[7] = (long)plVar12;
  param_1[8] = 0;
  param_1[9] = 0;
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dc3b5/*"C:\BAS_Submission\Client\Project\Android\BASAndroid.NativeActivity\..\..\..\Source\Game/Parameter/Info/InfoBase.h"*/,0x1c1,&UNK_027dc58a/*"apParser is null."*/);
    iVar6 = iRam0000000000000008;
  }
  else {
    iVar6 = (int)param_2[1];
  }
  if (iVar6 != 0) {
    uVar10 = 0;
    puVar2 = PTR__ZTV24CDeepSpaceBonusApplyInfo_02cc0530 + 0x10;
    puVar3 = PTR__ZTV22CParameterPropertyBaseILj20EE_02cc0d08 + 0x10;
    puVar4 = PTR__ZTV23CParameterPropertyValueIfLj20E18CPropertyConverterE_02cb91c8 + 0x10;
    puVar5 = PTR__ZTV8InfoBase_02cc49c8 + 0x10;
    do {
      uStack_68 = (**(code **)(*param_1 + 0x20))(param_1,*param_2 + uVar10 * 0x40);
      plVar7 = (long *)param_1[8];
      plVar9 = plVar12;
      if ((long *)param_1[8] == (long *)0x0) {
code_r0x014f4850:
        memset(auStack_c0,0,0x58);
        uStack_a8 = 0;
        uStack_a0 = 0;
        uStack_90 = 0;
        uStack_88 = 0;
        puStack_d0 = puVar2;
        puStack_c8 = auStack_c0;
        puStack_b0 = &uStack_a8;
        puStack_98 = puVar3;
        Framework::CHash32::CHash32()(auStack_80);
        puStack_98 = puVar4;
        lVar8 = std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned long, CDeepSpaceBonusApplyInfo>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CDeepSpaceBonusApplyInfo>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CDeepSpaceBonusApplyInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CDeepSpaceBonusApplyInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CDeepSpaceBonusApplyInfo>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned long, unsigned long&, CDeepSpaceBonusApplyInfo>(unsigned long const&, unsigned long&, CDeepSpaceBonusApplyInfo&&)(param_1 + 7,&uStack_68,&uStack_68,&puStack_d0);
        puStack_d0 = puVar2;
        puStack_98 = puVar3;
        Framework::CHash32::~CHash32()(auStack_80);
        puStack_d0 = puVar5;
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*)(&puStack_b0,uStack_a8);
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*)(&puStack_c8,auStack_c0[0]);
        plVar11 = (long *)(lVar8 + 0x28);
        (**(code **)(*plVar11 + 0x10))(plVar11);
      }
      else {
        do {
          while (plVar11 = plVar7, (ulong)plVar11[4] < uStack_68) {
            plVar7 = (long *)plVar11[1];
            if ((long *)plVar11[1] == (long *)0x0) {
              plVar11 = plVar9;
              if (plVar9 != plVar12) goto code_r0x014f4834;
              goto code_r0x014f4850;
            }
          }
          plVar7 = (long *)*plVar11;
          plVar9 = plVar11;
        } while ((long *)*plVar11 != (long *)0x0);
        if (plVar11 == plVar12) goto code_r0x014f4850;
code_r0x014f4834:
        if ((uStack_68 < (ulong)plVar11[4]) || (plVar11 == plVar12)) goto code_r0x014f4850;
        plVar11 = plVar11 + 5;
      }
      lVar8 = *param_2 + uVar10 * 0x40;
      iVar6 = *(int *)(lVar8 + 0x20);
      if (iVar6 == 6) {
        (**(code **)*plVar11)(plVar11,lVar8 + 0x28);
      }
      else if (iVar6 == 7) {
        (**(code **)(*plVar11 + 8))(plVar11,*param_2 + uVar10 * 0x40 + 0x28);
      }
      uVar1 = (int)uVar10 + 1;
      uVar10 = (ulong)uVar1;
    } while (uVar1 < *(uint *)(param_2 + 1));
  }
  return 1;
}

// ==== IInfoBaseMap<unsigned long, CBoxGachaListInfo>::DeserializeChild(Aska::ASON::AValue::AMap const*)
// vaddr 0x14fa614 | ghidra 0x15fa614 | size 1360 | symbol _ZN12IInfoBaseMapIm17CBoxGachaListInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN12IInfoBaseMapIm17CBoxGachaListInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE
          (long *param_1,long *param_2)

{
  long *plVar1;
  uint uVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined *puVar5;
  undefined *puVar6;
  undefined *puVar7;
  undefined *puVar8;
  undefined *puVar9;
  undefined *puVar10;
  undefined *puVar11;
  undefined *puVar12;
  undefined *puVar13;
  undefined *puVar14;
  undefined *puVar15;
  undefined *puVar16;
  undefined *puVar17;
  undefined *puVar18;
  undefined *puVar19;
  undefined *puVar20;
  undefined *puVar21;
  undefined *puVar22;
  int iVar23;
  long *plVar24;
  long lVar25;
  long *plVar26;
  ulong uVar27;
  long *plVar28;
  long *plVar29;
  undefined *puStack_250;
  undefined8 *puStack_248;
  undefined8 auStack_240 [2];
  undefined8 *puStack_230;
  undefined8 uStack_228;
  undefined8 uStack_220;
  undefined *puStack_218;
  undefined8 uStack_210;
  undefined1 uStack_208;
  undefined1 auStack_200 [24];
  undefined *puStack_1e8;
  undefined8 uStack_1e0;
  undefined1 uStack_1d8;
  undefined1 auStack_1d0 [24];
  undefined *puStack_1b8;
  undefined8 uStack_1b0;
  undefined1 uStack_1a8;
  undefined1 auStack_1a0 [24];
  undefined *puStack_188;
  undefined8 uStack_180;
  undefined1 uStack_178;
  undefined1 auStack_170 [24];
  undefined *puStack_158;
  undefined8 uStack_150;
  undefined1 uStack_148;
  undefined1 auStack_140 [24];
  undefined *puStack_128;
  undefined8 uStack_120;
  undefined1 uStack_118;
  undefined1 auStack_110 [24];
  undefined *puStack_f8;
  undefined8 uStack_f0;
  undefined1 uStack_e8;
  undefined1 auStack_e0 [24];
  undefined *puStack_c8;
  undefined8 uStack_c0;
  undefined1 uStack_b8;
  undefined1 auStack_b0 [24];
  undefined *puStack_98;
  undefined8 uStack_90;
  undefined1 uStack_88;
  undefined1 auStack_80 [24];
  ulong uStack_68;
  
  plVar28 = param_1 + 8;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CBoxGachaListInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CBoxGachaListInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CBoxGachaListInfo>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CBoxGachaListInfo>, void*>*)(param_1 + 7,*plVar28);
  param_1[7] = (long)plVar28;
  param_1[8] = 0;
  param_1[9] = 0;
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0282d54e/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\Info/InfoBase.h"*/,0x1c1,&UNK_027dc58a/*"apParser is null."*/);
    iVar23 = iRam0000000000000008;
  }
  else {
    iVar23 = (int)param_2[1];
  }
  if (iVar23 != 0) {
    puVar3 = PTR__ZTV17CBoxGachaListInfo_02cc3010 + 0x10;
    puVar4 = PTR__ZTV22CParameterPropertyBaseILj16EE_02cb9c20 + 0x10;
    puVar5 = PTR__ZTV23CParameterPropertyValueIjLj16E18CPropertyConverterE_02cbd008 + 0x10;
    puVar6 = PTR__ZTV22CParameterPropertyBaseILj17EE_02cba1e8 + 0x10;
    puVar7 = PTR__ZTV23CParameterPropertyValueIjLj17E18CPropertyConverterE_02cbb3b8 + 0x10;
    puVar8 = PTR__ZTV22CParameterPropertyBaseILj18EE_02cbe238 + 0x10;
    puVar9 = PTR__ZTV23CParameterPropertyValueIjLj18E18CPropertyConverterE_02cbcd58 + 0x10;
    puVar10 = PTR__ZTV22CParameterPropertyBaseILj19EE_02cc4c98 + 0x10;
    puVar11 = PTR__ZTV23CParameterPropertyValueIjLj19E18CPropertyConverterE_02cc13e8 + 0x10;
    puVar12 = PTR__ZTV22CParameterPropertyBaseILj20EE_02cc0d08 + 0x10;
    puVar13 = PTR__ZTV23CParameterPropertyValueIjLj20E18CPropertyConverterE_02cc2ce0 + 0x10;
    puVar14 = PTR__ZTV22CParameterPropertyBaseILj21EE_02cc1310 + 0x10;
    puVar15 = PTR__ZTV23CParameterPropertyValueIjLj21E18CPropertyConverterE_02cbeae0 + 0x10;
    puVar16 = PTR__ZTV22CParameterPropertyBaseILj23EE_02cbad98 + 0x10;
    puVar17 = PTR__ZTV23CParameterPropertyValueIjLj23E18CPropertyConverterE_02cb7d90 + 0x10;
    puVar18 = PTR__ZTV22CParameterPropertyBaseILj24EE_02cbdf68 + 0x10;
    puVar19 = PTR__ZTV23CParameterPropertyValueIjLj24E18CPropertyConverterE_02cb6cf8 + 0x10;
    uVar27 = 0;
    puVar20 = PTR__ZTV22CParameterPropertyBaseILj26EE_02cc41e8 + 0x10;
    puVar21 = PTR__ZTV23CParameterPropertyValueIbLj26E18CPropertyConverterE_02cc4d40 + 0x10;
    puVar22 = PTR__ZTV8InfoBase_02cc49c8 + 0x10;
    do {
      uStack_68 = (**(code **)(*param_1 + 0x20))(param_1,*param_2 + uVar27 * 0x40);
      plVar24 = (long *)param_1[8];
      plVar26 = plVar28;
      if ((long *)param_1[8] == (long *)0x0) {
code_r0x015fa8e0:
        memset(auStack_240,0,0x1d8);
        uStack_228 = 0;
        uStack_220 = 0;
        uStack_208 = 0;
        uStack_210 = 0;
        puStack_250 = puVar3;
        puStack_248 = auStack_240;
        puStack_230 = &uStack_228;
        puStack_218 = puVar4;
        Framework::CHash32::CHash32()(auStack_200);
        uStack_1d8 = 0;
        uStack_1e0 = 0;
        puStack_218 = puVar5;
        puStack_1e8 = puVar6;
        Framework::CHash32::CHash32()(auStack_1d0);
        uStack_1a8 = 0;
        uStack_1b0 = 0;
        puStack_1e8 = puVar7;
        puStack_1b8 = puVar8;
        Framework::CHash32::CHash32()(auStack_1a0);
        uStack_178 = 0;
        uStack_180 = 0;
        puStack_1b8 = puVar9;
        puStack_188 = puVar10;
        Framework::CHash32::CHash32()(auStack_170);
        uStack_150 = 0;
        uStack_148 = 0;
        puStack_188 = puVar11;
        puStack_158 = puVar12;
        Framework::CHash32::CHash32()(auStack_140);
        uStack_120 = 0;
        uStack_118 = 0;
        puStack_158 = puVar13;
        puStack_128 = puVar14;
        Framework::CHash32::CHash32()(auStack_110);
        uStack_f0 = 0;
        uStack_e8 = 0;
        puStack_128 = puVar15;
        puStack_f8 = puVar16;
        Framework::CHash32::CHash32()(auStack_e0);
        uStack_c0 = 0;
        uStack_b8 = 0;
        puStack_f8 = puVar17;
        puStack_c8 = puVar18;
        Framework::CHash32::CHash32()(auStack_b0);
        uStack_90 = 0;
        uStack_88 = 0;
        puStack_c8 = puVar19;
        puStack_98 = puVar20;
        Framework::CHash32::CHash32()(auStack_80);
        puStack_98 = puVar21;
        lVar25 = std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned long, CBoxGachaListInfo>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CBoxGachaListInfo>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CBoxGachaListInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CBoxGachaListInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CBoxGachaListInfo>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned long, unsigned long&, CBoxGachaListInfo>(unsigned long const&, unsigned long&, CBoxGachaListInfo&&)(param_1 + 7,&uStack_68,&uStack_68,&puStack_250);
        puStack_250 = puVar3;
        puStack_98 = puVar20;
        Framework::CHash32::~CHash32()(auStack_80);
        puStack_c8 = puVar18;
        Framework::CHash32::~CHash32()(auStack_b0);
        puStack_f8 = puVar16;
        Framework::CHash32::~CHash32()(auStack_e0);
        puStack_128 = puVar14;
        Framework::CHash32::~CHash32()(auStack_110);
        puStack_158 = puVar12;
        Framework::CHash32::~CHash32()(auStack_140);
        puStack_188 = puVar10;
        Framework::CHash32::~CHash32()(auStack_170);
        puStack_1b8 = puVar8;
        Framework::CHash32::~CHash32()(auStack_1a0);
        puStack_1e8 = puVar6;
        Framework::CHash32::~CHash32()(auStack_1d0);
        puStack_218 = puVar4;
        Framework::CHash32::~CHash32()(auStack_200);
        puStack_250 = puVar22;
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*)(&puStack_230,uStack_228);
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*)(&puStack_248,auStack_240[0]);
        plVar29 = (long *)(lVar25 + 0x28);
        (**(code **)(*plVar29 + 0x10))(plVar29);
      }
      else {
        do {
          while (plVar29 = plVar24, (ulong)plVar29[4] < uStack_68) {
            plVar1 = plVar29 + 1;
            plVar29 = plVar26;
            plVar24 = (long *)*plVar1;
            if ((long *)*plVar1 == (long *)0x0) goto code_r0x015fa8b4;
          }
          plVar24 = (long *)*plVar29;
          plVar26 = plVar29;
        } while ((long *)*plVar29 != (long *)0x0);
code_r0x015fa8b4:
        if (((plVar29 == plVar28) || (uStack_68 < (ulong)plVar29[4])) || (plVar29 == plVar28))
        goto code_r0x015fa8e0;
        plVar29 = plVar29 + 5;
      }
      lVar25 = *param_2 + uVar27 * 0x40;
      iVar23 = *(int *)(lVar25 + 0x20);
      if (iVar23 == 6) {
        (**(code **)*plVar29)(plVar29,lVar25 + 0x28);
      }
      else if (iVar23 == 7) {
        (**(code **)(*plVar29 + 8))(plVar29,*param_2 + uVar27 * 0x40 + 0x28);
      }
      uVar2 = (int)uVar27 + 1;
      uVar27 = (ulong)uVar2;
    } while (uVar2 < *(uint *)(param_2 + 1));
  }
  return 1;
}

// ==== IInfoBaseMap<unsigned long, CBoostCharacterResultInfo>::DeserializeChild(Aska::ASON::AValue::AMap const*)
// vaddr 0x1519574 | ghidra 0x1619574 | size 1360 | symbol _ZN12IInfoBaseMapIm25CBoostCharacterResultInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN12IInfoBaseMapIm25CBoostCharacterResultInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE
          (long *param_1,long *param_2)

{
  long *plVar1;
  uint uVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined *puVar5;
  undefined *puVar6;
  undefined *puVar7;
  undefined *puVar8;
  undefined *puVar9;
  undefined *puVar10;
  undefined *puVar11;
  undefined *puVar12;
  undefined *puVar13;
  undefined *puVar14;
  undefined *puVar15;
  undefined *puVar16;
  undefined *puVar17;
  undefined *puVar18;
  undefined *puVar19;
  undefined *puVar20;
  undefined *puVar21;
  undefined *puVar22;
  int iVar23;
  long *plVar24;
  long lVar25;
  long *plVar26;
  ulong uVar27;
  long *plVar28;
  long *plVar29;
  undefined *puStack_250;
  undefined8 *puStack_248;
  undefined8 auStack_240 [2];
  undefined8 *puStack_230;
  undefined8 uStack_228;
  undefined8 uStack_220;
  undefined *puStack_218;
  undefined8 uStack_210;
  undefined1 uStack_208;
  undefined1 auStack_200 [24];
  undefined *puStack_1e8;
  undefined8 uStack_1e0;
  undefined1 uStack_1d8;
  undefined1 auStack_1d0 [24];
  undefined *puStack_1b8;
  undefined8 uStack_1b0;
  undefined1 uStack_1a8;
  undefined1 auStack_1a0 [24];
  undefined *puStack_188;
  undefined8 uStack_180;
  undefined1 uStack_178;
  undefined1 auStack_170 [24];
  undefined *puStack_158;
  undefined8 uStack_150;
  undefined1 uStack_148;
  undefined1 auStack_140 [24];
  undefined *puStack_128;
  undefined8 uStack_120;
  undefined1 uStack_118;
  undefined1 auStack_110 [24];
  undefined *puStack_f8;
  undefined8 uStack_f0;
  undefined1 uStack_e8;
  undefined1 auStack_e0 [24];
  undefined *puStack_c8;
  undefined8 uStack_c0;
  undefined1 uStack_b8;
  undefined1 auStack_b0 [24];
  undefined *puStack_98;
  undefined8 uStack_90;
  undefined1 uStack_88;
  undefined1 auStack_80 [24];
  ulong uStack_68;
  
  plVar28 = param_1 + 8;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CBoostCharacterResultInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CBoostCharacterResultInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CBoostCharacterResultInfo>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CBoostCharacterResultInfo>, void*>*)(param_1 + 7,*plVar28);
  param_1[7] = (long)plVar28;
  param_1[8] = 0;
  param_1[9] = 0;
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0282d54e/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\Info/InfoBase.h"*/,0x1c1,&UNK_027dc58a/*"apParser is null."*/);
    iVar23 = iRam0000000000000008;
  }
  else {
    iVar23 = (int)param_2[1];
  }
  if (iVar23 != 0) {
    puVar3 = PTR__ZTV25CBoostCharacterResultInfo_02cc1320 + 0x10;
    puVar4 = PTR__ZTV22CParameterPropertyBaseILj16EE_02cb9c20 + 0x10;
    puVar5 = PTR__ZTV23CParameterPropertyValueImLj16E18CPropertyConverterE_02cbcfa0 + 0x10;
    puVar6 = PTR__ZTV22CParameterPropertyBaseILj17EE_02cba1e8 + 0x10;
    puVar7 = PTR__ZTV23CParameterPropertyValueIjLj17E18CPropertyConverterE_02cbb3b8 + 0x10;
    puVar8 = PTR__ZTV22CParameterPropertyBaseILj18EE_02cbe238 + 0x10;
    puVar9 = PTR__ZTV23CParameterPropertyValueIjLj18E18CPropertyConverterE_02cbcd58 + 0x10;
    puVar10 = PTR__ZTV22CParameterPropertyBaseILj19EE_02cc4c98 + 0x10;
    puVar11 = PTR__ZTV23CParameterPropertyValueIjLj19E18CPropertyConverterE_02cc13e8 + 0x10;
    puVar12 = PTR__ZTV22CParameterPropertyBaseILj20EE_02cc0d08 + 0x10;
    puVar13 = PTR__ZTV23CParameterPropertyValueIjLj20E18CPropertyConverterE_02cc2ce0 + 0x10;
    puVar14 = PTR__ZTV22CParameterPropertyBaseILj21EE_02cc1310 + 0x10;
    puVar15 = PTR__ZTV23CParameterPropertyValueIjLj21E18CPropertyConverterE_02cbeae0 + 0x10;
    puVar16 = PTR__ZTV22CParameterPropertyBaseILj22EE_02cc4630 + 0x10;
    puVar17 = PTR__ZTV23CParameterPropertyValueIbLj22E18CPropertyConverterE_02cc37e0 + 0x10;
    puVar18 = PTR__ZTV22CParameterPropertyBaseILj23EE_02cbad98 + 0x10;
    puVar19 = PTR__ZTV23CParameterPropertyValueIjLj23E18CPropertyConverterE_02cb7d90 + 0x10;
    uVar27 = 0;
    puVar20 = PTR__ZTV22CParameterPropertyBaseILj24EE_02cbdf68 + 0x10;
    puVar21 = PTR__ZTV23CParameterPropertyValueIjLj24E18CPropertyConverterE_02cb6cf8 + 0x10;
    puVar22 = PTR__ZTV8InfoBase_02cc49c8 + 0x10;
    do {
      uStack_68 = (**(code **)(*param_1 + 0x20))(param_1,*param_2 + uVar27 * 0x40);
      plVar24 = (long *)param_1[8];
      plVar26 = plVar28;
      if ((long *)param_1[8] == (long *)0x0) {
code_r0x01619840:
        memset(auStack_240,0,0x1d8);
        uStack_228 = 0;
        uStack_220 = 0;
        uStack_208 = 0;
        uStack_210 = 0;
        puStack_250 = puVar3;
        puStack_248 = auStack_240;
        puStack_230 = &uStack_228;
        puStack_218 = puVar4;
        Framework::CHash32::CHash32()(auStack_200);
        uStack_1d8 = 0;
        uStack_1e0 = 0;
        puStack_218 = puVar5;
        puStack_1e8 = puVar6;
        Framework::CHash32::CHash32()(auStack_1d0);
        uStack_1a8 = 0;
        uStack_1b0 = 0;
        puStack_1e8 = puVar7;
        puStack_1b8 = puVar8;
        Framework::CHash32::CHash32()(auStack_1a0);
        uStack_178 = 0;
        uStack_180 = 0;
        puStack_1b8 = puVar9;
        puStack_188 = puVar10;
        Framework::CHash32::CHash32()(auStack_170);
        uStack_150 = 0;
        uStack_148 = 0;
        puStack_188 = puVar11;
        puStack_158 = puVar12;
        Framework::CHash32::CHash32()(auStack_140);
        uStack_120 = 0;
        uStack_118 = 0;
        puStack_158 = puVar13;
        puStack_128 = puVar14;
        Framework::CHash32::CHash32()(auStack_110);
        uStack_f0 = 0;
        uStack_e8 = 0;
        puStack_128 = puVar15;
        puStack_f8 = puVar16;
        Framework::CHash32::CHash32()(auStack_e0);
        uStack_c0 = 0;
        uStack_b8 = 0;
        puStack_f8 = puVar17;
        puStack_c8 = puVar18;
        Framework::CHash32::CHash32()(auStack_b0);
        uStack_90 = 0;
        uStack_88 = 0;
        puStack_c8 = puVar19;
        puStack_98 = puVar20;
        Framework::CHash32::CHash32()(auStack_80);
        puStack_98 = puVar21;
        lVar25 = std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned long, CBoostCharacterResultInfo>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CBoostCharacterResultInfo>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CBoostCharacterResultInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CBoostCharacterResultInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CBoostCharacterResultInfo>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned long, unsigned long&, CBoostCharacterResultInfo>(unsigned long const&, unsigned long&, CBoostCharacterResultInfo&&)(param_1 + 7,&uStack_68,&uStack_68,&puStack_250);
        puStack_250 = puVar3;
        puStack_98 = puVar20;
        Framework::CHash32::~CHash32()(auStack_80);
        puStack_c8 = puVar18;
        Framework::CHash32::~CHash32()(auStack_b0);
        puStack_f8 = puVar16;
        Framework::CHash32::~CHash32()(auStack_e0);
        puStack_128 = puVar14;
        Framework::CHash32::~CHash32()(auStack_110);
        puStack_158 = puVar12;
        Framework::CHash32::~CHash32()(auStack_140);
        puStack_188 = puVar10;
        Framework::CHash32::~CHash32()(auStack_170);
        puStack_1b8 = puVar8;
        Framework::CHash32::~CHash32()(auStack_1a0);
        puStack_1e8 = puVar6;
        Framework::CHash32::~CHash32()(auStack_1d0);
        puStack_218 = puVar4;
        Framework::CHash32::~CHash32()(auStack_200);
        puStack_250 = puVar22;
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*)(&puStack_230,uStack_228);
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*)(&puStack_248,auStack_240[0]);
        plVar29 = (long *)(lVar25 + 0x28);
        (**(code **)(*plVar29 + 0x10))(plVar29);
      }
      else {
        do {
          while (plVar29 = plVar24, (ulong)plVar29[4] < uStack_68) {
            plVar1 = plVar29 + 1;
            plVar29 = plVar26;
            plVar24 = (long *)*plVar1;
            if ((long *)*plVar1 == (long *)0x0) goto code_r0x01619814;
          }
          plVar24 = (long *)*plVar29;
          plVar26 = plVar29;
        } while ((long *)*plVar29 != (long *)0x0);
code_r0x01619814:
        if (((plVar29 == plVar28) || (uStack_68 < (ulong)plVar29[4])) || (plVar29 == plVar28))
        goto code_r0x01619840;
        plVar29 = plVar29 + 5;
      }
      lVar25 = *param_2 + uVar27 * 0x40;
      iVar23 = *(int *)(lVar25 + 0x20);
      if (iVar23 == 6) {
        (**(code **)*plVar29)(plVar29,lVar25 + 0x28);
      }
      else if (iVar23 == 7) {
        (**(code **)(*plVar29 + 8))(plVar29,*param_2 + uVar27 * 0x40 + 0x28);
      }
      uVar2 = (int)uVar27 + 1;
      uVar27 = (ulong)uVar2;
    } while (uVar2 < *(uint *)(param_2 + 1));
  }
  return 1;
}

// ==== IInfoBaseMap<unsigned int, CSkillInfoArray>::DeserializeChild(Aska::ASON::AValue::AMap const*)
// vaddr 0x151b9b4 | ghidra 0x161b9b4 | size 480 | symbol _ZN12IInfoBaseMapIj15CSkillInfoArrayE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN12IInfoBaseMapIj15CSkillInfoArrayE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE
          (long *param_1,long *param_2)

{
  uint uVar1;
  undefined *puVar2;
  int iVar3;
  long *plVar4;
  long lVar5;
  long *plVar6;
  ulong uVar7;
  long *plVar8;
  long *plVar9;
  undefined *puStack_b0;
  undefined8 *puStack_a8;
  undefined8 uStack_a0;
  undefined8 uStack_98;
  undefined8 *puStack_90;
  undefined8 uStack_88;
  undefined8 uStack_80;
  undefined8 uStack_78;
  undefined8 uStack_70;
  undefined8 uStack_68;
  uint uStack_54;
  
  plVar9 = param_1 + 8;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, CSkillInfoArray>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, CSkillInfoArray>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, CSkillInfoArray>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, CSkillInfoArray>, void*>*)(param_1 + 7,*plVar9);
  param_1[7] = (long)plVar9;
  param_1[8] = 0;
  param_1[9] = 0;
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0282d54e/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\Info/InfoBase.h"*/,0x1c1,&UNK_027dc58a/*"apParser is null."*/);
    iVar3 = iRam0000000000000008;
  }
  else {
    iVar3 = (int)param_2[1];
  }
  if (iVar3 != 0) {
    uVar7 = 0;
    puVar2 = PTR__ZTV15CSkillInfoArray_02cc00d8 + 0x10;
    do {
      uStack_54 = (**(code **)(*param_1 + 0x20))(param_1,*param_2 + uVar7 * 0x40);
      plVar4 = (long *)param_1[8];
      plVar6 = plVar9;
      if ((long *)param_1[8] == (long *)0x0) {
code_r0x0161bacc:
        uStack_a0 = 0;
        uStack_98 = 0;
        uStack_88 = 0;
        uStack_80 = 0;
        uStack_70 = 0;
        uStack_68 = 0;
        uStack_78 = 0;
        puStack_b0 = puVar2;
        puStack_a8 = &uStack_a0;
        puStack_90 = &uStack_88;
        lVar5 = std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, CSkillInfoArray>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, CSkillInfoArray>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, CSkillInfoArray>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, CSkillInfoArray>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, CSkillInfoArray>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, unsigned int&, CSkillInfoArray>(unsigned int const&, unsigned int&, CSkillInfoArray&&)(param_1 + 7,&uStack_54,&uStack_54,&puStack_b0);
        InfoBaseArray<CSkillInfo>::~InfoBaseArray()(&puStack_b0);
        plVar8 = (long *)(lVar5 + 0x28);
        (**(code **)(*plVar8 + 0x10))(plVar8);
      }
      else {
        do {
          while (plVar8 = plVar4, *(uint *)(plVar8 + 4) < uStack_54) {
            plVar4 = (long *)plVar8[1];
            if ((long *)plVar8[1] == (long *)0x0) {
              plVar8 = plVar6;
              if (plVar6 != plVar9) goto code_r0x0161bab0;
              goto code_r0x0161bacc;
            }
          }
          plVar4 = (long *)*plVar8;
          plVar6 = plVar8;
        } while ((long *)*plVar8 != (long *)0x0);
        if (plVar8 == plVar9) goto code_r0x0161bacc;
code_r0x0161bab0:
        if ((uStack_54 < *(uint *)(plVar8 + 4)) || (plVar8 == plVar9)) goto code_r0x0161bacc;
        plVar8 = plVar8 + 5;
      }
      lVar5 = *param_2 + uVar7 * 0x40;
      iVar3 = *(int *)(lVar5 + 0x20);
      if (iVar3 == 6) {
        (**(code **)*plVar8)(plVar8,lVar5 + 0x28);
      }
      else if (iVar3 == 7) {
        (**(code **)(*plVar8 + 8))(plVar8,*param_2 + uVar7 * 0x40 + 0x28);
      }
      uVar1 = (int)uVar7 + 1;
      uVar7 = (ulong)uVar1;
    } while (uVar1 < *(uint *)(param_2 + 1));
  }
  return 1;
}

// ==== IInfoBaseMap<unsigned long, PartySetInfo>::DeserializeChild(Aska::ASON::AValue::AMap const*)
// vaddr 0x151d15c | ghidra 0x161d15c | size 1160 | symbol _ZN12IInfoBaseMapIm12PartySetInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Type propagation algorithm not settling */

undefined8
_ZN12IInfoBaseMapIm12PartySetInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE
          (long *param_1,long *param_2)

{
  uint uVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined *puVar5;
  undefined *puVar6;
  undefined *puVar7;
  undefined *puVar8;
  undefined *puVar9;
  undefined *puVar10;
  long lVar11;
  int iVar12;
  long *plVar13;
  long *******ppppppplVar14;
  long *******ppppppplVar15;
  ulong uVar16;
  long *******ppppppplVar17;
  long *******ppppppplVar18;
  long *******ppppppplVar19;
  undefined *puStack_1a0;
  undefined8 *puStack_198;
  undefined8 auStack_190 [2];
  undefined8 *puStack_180;
  undefined8 uStack_178;
  undefined8 uStack_170;
  undefined *puStack_168;
  undefined8 uStack_160;
  undefined1 uStack_158;
  undefined1 auStack_150 [24];
  undefined *puStack_138;
  undefined8 uStack_130;
  undefined1 uStack_128;
  undefined1 auStack_120 [24];
  undefined *puStack_108;
  undefined8 uStack_100;
  undefined1 uStack_f8;
  undefined1 auStack_f0 [24];
  undefined *puStack_d8;
  undefined8 *puStack_d0;
  undefined8 uStack_c8;
  undefined8 uStack_c0;
  undefined8 *puStack_b8;
  undefined8 uStack_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined8 uStack_98;
  undefined8 uStack_90;
  long ******pppppplStack_88;
  long *******appppppplStack_80 [3];
  long *******ppppppplStack_68;
  
  ppppppplVar18 = (long *******)(param_1 + 8);
  plVar13 = param_1 + 7;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, PartySetInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, PartySetInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, PartySetInfo>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, PartySetInfo>, void*>*)(plVar13,*ppppppplVar18);
  param_1[7] = (long)ppppppplVar18;
  param_1[8] = 0;
  param_1[9] = 0;
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0282d54e/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\Info/InfoBase.h"*/,0x1c1,&UNK_027dc58a/*"apParser is null."*/);
    iVar12 = iRam0000000000000008;
  }
  else {
    iVar12 = (int)param_2[1];
  }
  if (iVar12 != 0) {
    puVar2 = PTR__ZTV12PartySetInfo_02cb7940 + 0x10;
    puVar3 = PTR__ZTV22CParameterPropertyBaseILj64EE_02cbbba0 + 0x10;
    puVar4 = PTR__ZTV23CParameterPropertyValueIjLj64E18CPropertyConverterE_02cb96a8 + 0x10;
    puVar5 = PTR__ZTV22CParameterPropertyBaseILj65EE_02cb79a0 + 0x10;
    puVar6 = PTR__ZTV23CParameterPropertyValueIjLj65E18CPropertyConverterE_02cbf1c8 + 0x10;
    puVar7 = PTR__ZTV22CParameterPropertyBaseILj66EE_02cc1e50 + 0x10;
    puVar8 = PTR__ZTV23CParameterPropertyValueIbLj66E18CPropertyConverterE_02cbc8d8 + 0x10;
    puVar9 = PTR__ZTV25PartySetCharacterInfoList_02cb8610 + 0x10;
    uVar16 = 0;
    puVar10 = PTR__ZTV8InfoBase_02cc49c8 + 0x10;
    do {
      pppppplStack_88 =
           (long ******)(**(code **)(*param_1 + 0x20))(param_1,*param_2 + uVar16 * 0x40);
      ppppppplVar15 = (long *******)param_1[8];
      ppppppplVar14 = ppppppplVar18;
      if ((long *******)param_1[8] == (long *******)0x0) {
code_r0x0161d338:
        memset(auStack_190,0,0x108);
        uStack_178 = 0;
        uStack_170 = 0;
        uStack_158 = 0;
        uStack_160 = 0;
        puStack_1a0 = puVar2;
        puStack_198 = auStack_190;
        puStack_180 = &uStack_178;
        puStack_168 = puVar3;
        Framework::CHash32::CHash32()(auStack_150);
        uStack_128 = 0;
        uStack_130 = 0;
        puStack_168 = puVar4;
        puStack_138 = puVar5;
        Framework::CHash32::CHash32()(auStack_120);
        uStack_f8 = 0;
        uStack_100 = 0;
        puStack_138 = puVar6;
        puStack_108 = puVar7;
        Framework::CHash32::CHash32()(auStack_f0);
        uStack_c8 = 0;
        uStack_c0 = 0;
        uStack_b0 = 0;
        uStack_a8 = 0;
        uStack_98 = 0;
        uStack_90 = 0;
        uStack_a0 = 0;
        ppppppplVar15 = (long *******)*ppppppplVar18;
        if ((long *******)*ppppppplVar18 == (long *******)0x0) {
          ppppppplVar17 = (long *******)*ppppppplVar18;
          ppppppplVar14 = ppppppplVar18;
          ppppppplVar19 = ppppppplVar18;
        }
        else {
          do {
            while (ppppppplVar14 = ppppppplVar15, ppppppplVar14[4] <= pppppplStack_88) {
              if (pppppplStack_88 <= ppppppplVar14[4]) {
                ppppppplVar17 = ppppppplVar14;
                ppppppplVar19 = (long *******)&ppppppplStack_68;
                goto joined_r0x0161d448;
              }
              ppppppplVar19 = ppppppplVar14 + 1;
              ppppppplVar15 = (long *******)*ppppppplVar19;
              if ((long *******)*ppppppplVar19 == (long *******)0x0) {
                ppppppplVar17 = (long *******)*ppppppplVar19;
                goto joined_r0x0161d448;
              }
            }
            ppppppplVar15 = (long *******)*ppppppplVar14;
          } while ((long *******)*ppppppplVar14 != (long *******)0x0);
          ppppppplVar17 = (long *******)*ppppppplVar14;
          ppppppplVar19 = ppppppplVar14;
        }
joined_r0x0161d448:
        puStack_108 = puVar8;
        puStack_d8 = puVar9;
        puStack_d0 = &uStack_c8;
        puStack_b8 = &uStack_b0;
        ppppppplStack_68 = ppppppplVar14;
        if (ppppppplVar17 == (long *******)0x0) {
          std::__ndk1::unique_ptr<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, PartySetInfo>, void*>, std::__ndk1::__tree_node_destructor<Framework::CSTLAllocator<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, PartySetInfo>, void*>, Framework::CSTLMapAllocatorInf> > > std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, PartySetInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, PartySetInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, PartySetInfo>, Framework::CSTLMapAllocatorInf> >::__construct_node<unsigned long&, PartySetInfo>(unsigned long&, PartySetInfo&&)(appppppplStack_80,plVar13,&pppppplStack_88,&puStack_1a0);
          *appppppplStack_80[0] = (long ******)0x0;
          appppppplStack_80[0][1] = (long ******)0x0;
          appppppplStack_80[0][2] = (long ******)ppppppplVar14;
          *ppppppplVar19 = (long ******)appppppplStack_80[0];
          ppppppplVar15 = appppppplStack_80[0];
          if (*(long *)*plVar13 != 0) {
            *plVar13 = *(long *)*plVar13;
            ppppppplVar15 = (long *******)*ppppppplVar19;
          }
          void std::__ndk1::__tree_balance_after_insert<std::__ndk1::__tree_node_base<void*>*>(std::__ndk1::__tree_node_base<void*>*, std::__ndk1::__tree_node_base<void*>*)(param_1[8],ppppppplVar15);
          param_1[9] = param_1[9] + 1;
          ppppppplVar17 = appppppplStack_80[0];
        }
        puStack_1a0 = PTR__ZTV12PartySetInfo_02cb7940 + 0x10;
        std::__ndk1::__vector_base<PartySetCharacterInfo, Framework::CSTLAllocator<PartySetCharacterInfo, Framework::CSTLVectorAllocatorInf> >::~__vector_base()(&uStack_a0);
        puStack_d8 = puVar10;
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*)(&puStack_b8,uStack_b0);
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*)(&puStack_d0,uStack_c8);
        puStack_108 = PTR__ZTV22CParameterPropertyBaseILj66EE_02cc1e50 + 0x10;
        Framework::CHash32::~CHash32()(auStack_f0);
        puStack_138 = PTR__ZTV22CParameterPropertyBaseILj65EE_02cb79a0 + 0x10;
        Framework::CHash32::~CHash32()(auStack_120);
        puStack_168 = PTR__ZTV22CParameterPropertyBaseILj64EE_02cbbba0 + 0x10;
        Framework::CHash32::~CHash32()(auStack_150);
        puStack_1a0 = puVar10;
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*)(&puStack_180,uStack_178);
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*)(&puStack_198,auStack_190[0]);
        ppppppplVar17 = ppppppplVar17 + 5;
        (*(code *)(*ppppppplVar17)[2])(ppppppplVar17);
      }
      else {
        do {
          while (ppppppplVar17 = ppppppplVar15, ppppppplVar17[4] < pppppplStack_88) {
            ppppppplVar15 = (long *******)ppppppplVar17[1];
            if ((long *******)ppppppplVar17[1] == (long *******)0x0) {
              ppppppplVar17 = ppppppplVar14;
              if (ppppppplVar14 != ppppppplVar18) goto code_r0x0161d31c;
              goto code_r0x0161d338;
            }
          }
          ppppppplVar15 = (long *******)*ppppppplVar17;
          ppppppplVar14 = ppppppplVar17;
        } while ((long *******)*ppppppplVar17 != (long *******)0x0);
        if (ppppppplVar17 == ppppppplVar18) goto code_r0x0161d338;
code_r0x0161d31c:
        if ((pppppplStack_88 < ppppppplVar17[4]) || (ppppppplVar17 == ppppppplVar18))
        goto code_r0x0161d338;
        ppppppplVar17 = ppppppplVar17 + 5;
      }
      lVar11 = *param_2 + uVar16 * 0x40;
      iVar12 = *(int *)(lVar11 + 0x20);
      if (iVar12 == 6) {
        (*(code *)**ppppppplVar17)(ppppppplVar17,lVar11 + 0x28);
      }
      else if (iVar12 == 7) {
        (*(code *)(*ppppppplVar17)[1])(ppppppplVar17,*param_2 + uVar16 * 0x40 + 0x28);
      }
      uVar1 = (int)uVar16 + 1;
      uVar16 = (ulong)uVar1;
    } while (uVar1 < *(uint *)(param_2 + 1));
  }
  return 1;
}

// ==== IInfoBaseMap<unsigned long, CPlanetInfo>::DeserializeChild(Aska::ASON::AValue::AMap const*)
// vaddr 0x151dfbc | ghidra 0x161dfbc | size 1028 | symbol _ZN12IInfoBaseMapIm11CPlanetInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Type propagation algorithm not settling */

undefined8
_ZN12IInfoBaseMapIm11CPlanetInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE
          (long *param_1,long *param_2)

{
  uint uVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined *puVar5;
  undefined *puVar6;
  undefined *puVar7;
  undefined *puVar8;
  undefined *puVar9;
  long lVar10;
  int iVar11;
  long *plVar12;
  long *******ppppppplVar13;
  long *******ppppppplVar14;
  ulong uVar15;
  long *******ppppppplVar16;
  long *******ppppppplVar17;
  long *******ppppppplVar18;
  undefined *puStack_150;
  undefined8 *puStack_148;
  undefined8 auStack_140 [2];
  undefined8 *puStack_130;
  undefined8 uStack_128;
  undefined8 uStack_120;
  undefined *puStack_118;
  undefined8 uStack_110;
  undefined1 uStack_108;
  undefined1 auStack_100 [24];
  undefined *puStack_e8;
  undefined8 uStack_e0;
  undefined1 uStack_d8;
  undefined1 auStack_d0 [24];
  undefined *puStack_b8;
  undefined8 uStack_b0;
  undefined1 uStack_a8;
  undefined1 auStack_a0 [24];
  long ******pppppplStack_88;
  long *******appppppplStack_80 [3];
  long *******ppppppplStack_68;
  
  ppppppplVar18 = (long *******)(param_1 + 8);
  plVar12 = param_1 + 7;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CPlanetInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CPlanetInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CPlanetInfo>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CPlanetInfo>, void*>*)(plVar12,*ppppppplVar18);
  param_1[7] = (long)ppppppplVar18;
  param_1[8] = 0;
  param_1[9] = 0;
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0282d54e/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\Info/InfoBase.h"*/,0x1c1,&UNK_027dc58a/*"apParser is null."*/);
    iVar11 = iRam0000000000000008;
  }
  else {
    iVar11 = (int)param_2[1];
  }
  if (iVar11 != 0) {
    puVar2 = PTR__ZTV11CPlanetInfo_02cc2988 + 0x10;
    puVar3 = PTR__ZTV22CParameterPropertyBaseILj13EE_02cba498 + 0x10;
    puVar4 = PTR__ZTV23CParameterPropertyValueIjLj13E18CPropertyConverterE_02cbd818 + 0x10;
    puVar5 = PTR__ZTV22CParameterPropertyBaseILj14EE_02cb9db0 + 0x10;
    puVar6 = PTR__ZTV23CParameterPropertyValueIbLj14E18CPropertyConverterE_02cbe940 + 0x10;
    puVar7 = PTR__ZTV22CParameterPropertyBaseILj15EE_02cc0790 + 0x10;
    puVar8 = PTR__ZTV23CParameterPropertyValueIbLj15E18CPropertyConverterE_02cbfef0 + 0x10;
    uVar15 = 0;
    puVar9 = PTR__ZTV8InfoBase_02cc49c8 + 0x10;
    do {
      pppppplStack_88 =
           (long ******)(**(code **)(*param_1 + 0x20))(param_1,*param_2 + uVar15 * 0x40);
      ppppppplVar14 = (long *******)param_1[8];
      ppppppplVar13 = ppppppplVar18;
      if ((long *******)param_1[8] == (long *******)0x0) {
code_r0x0161e160:
        memset(auStack_140,0,0xb8);
        uStack_128 = 0;
        uStack_120 = 0;
        uStack_108 = 0;
        uStack_110 = 0;
        puStack_150 = puVar2;
        puStack_148 = auStack_140;
        puStack_130 = &uStack_128;
        puStack_118 = puVar3;
        Framework::CHash32::CHash32()(auStack_100);
        uStack_d8 = 0;
        uStack_e0 = 0;
        puStack_118 = puVar4;
        puStack_e8 = puVar5;
        Framework::CHash32::CHash32()(auStack_d0);
        uStack_a8 = 0;
        uStack_b0 = 0;
        puStack_e8 = puVar6;
        puStack_b8 = puVar7;
        Framework::CHash32::CHash32()(auStack_a0);
        ppppppplVar14 = (long *******)*ppppppplVar18;
        if ((long *******)*ppppppplVar18 == (long *******)0x0) {
          ppppppplVar17 = (long *******)*ppppppplVar18;
          ppppppplVar13 = ppppppplVar18;
          ppppppplVar16 = ppppppplVar18;
        }
        else {
          do {
            while (ppppppplVar13 = ppppppplVar14, ppppppplVar13[4] <= pppppplStack_88) {
              if (pppppplStack_88 <= ppppppplVar13[4]) {
                ppppppplVar17 = ppppppplVar13;
                ppppppplVar16 = (long *******)&ppppppplStack_68;
                goto joined_r0x0161e24c;
              }
              ppppppplVar16 = ppppppplVar13 + 1;
              ppppppplVar14 = (long *******)*ppppppplVar16;
              if ((long *******)*ppppppplVar16 == (long *******)0x0) {
                ppppppplVar17 = (long *******)*ppppppplVar16;
                goto joined_r0x0161e24c;
              }
            }
            ppppppplVar14 = (long *******)*ppppppplVar13;
          } while ((long *******)*ppppppplVar13 != (long *******)0x0);
          ppppppplVar17 = (long *******)*ppppppplVar13;
          ppppppplVar16 = ppppppplVar13;
        }
joined_r0x0161e24c:
        ppppppplStack_68 = ppppppplVar13;
        if (ppppppplVar17 == (long *******)0x0) {
          puStack_b8 = puVar8;
          std::__ndk1::unique_ptr<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CPlanetInfo>, void*>, std::__ndk1::__tree_node_destructor<Framework::CSTLAllocator<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CPlanetInfo>, void*>, Framework::CSTLMapAllocatorInf> > > std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CPlanetInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CPlanetInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CPlanetInfo>, Framework::CSTLMapAllocatorInf> >::__construct_node<unsigned long&, CPlanetInfo>(unsigned long&, CPlanetInfo&&)(appppppplStack_80,plVar12,&pppppplStack_88,&puStack_150);
          *appppppplStack_80[0] = (long ******)0x0;
          appppppplStack_80[0][1] = (long ******)0x0;
          appppppplStack_80[0][2] = (long ******)ppppppplVar13;
          *ppppppplVar16 = (long ******)appppppplStack_80[0];
          ppppppplVar14 = appppppplStack_80[0];
          if (*(long *)*plVar12 != 0) {
            *plVar12 = *(long *)*plVar12;
            ppppppplVar14 = (long *******)*ppppppplVar16;
          }
          void std::__ndk1::__tree_balance_after_insert<std::__ndk1::__tree_node_base<void*>*>(std::__ndk1::__tree_node_base<void*>*, std::__ndk1::__tree_node_base<void*>*)(param_1[8],ppppppplVar14);
          param_1[9] = param_1[9] + 1;
          ppppppplVar17 = appppppplStack_80[0];
        }
        puStack_150 = PTR__ZTV11CPlanetInfo_02cc2988 + 0x10;
        puStack_b8 = PTR__ZTV22CParameterPropertyBaseILj15EE_02cc0790 + 0x10;
        Framework::CHash32::~CHash32()(auStack_a0);
        puStack_e8 = PTR__ZTV22CParameterPropertyBaseILj14EE_02cb9db0 + 0x10;
        Framework::CHash32::~CHash32()(auStack_d0);
        puStack_118 = PTR__ZTV22CParameterPropertyBaseILj13EE_02cba498 + 0x10;
        Framework::CHash32::~CHash32()(auStack_100);
        puStack_150 = puVar9;
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*)(&puStack_130,uStack_128);
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*)(&puStack_148,auStack_140[0]);
        ppppppplVar17 = ppppppplVar17 + 5;
        (*(code *)(*ppppppplVar17)[2])(ppppppplVar17);
      }
      else {
        do {
          while (ppppppplVar17 = ppppppplVar14, ppppppplVar17[4] < pppppplStack_88) {
            ppppppplVar14 = (long *******)ppppppplVar17[1];
            if ((long *******)ppppppplVar17[1] == (long *******)0x0) {
              ppppppplVar17 = ppppppplVar13;
              if (ppppppplVar13 != ppppppplVar18) goto code_r0x0161e144;
              goto code_r0x0161e160;
            }
          }
          ppppppplVar14 = (long *******)*ppppppplVar17;
          ppppppplVar13 = ppppppplVar17;
        } while ((long *******)*ppppppplVar17 != (long *******)0x0);
        if (ppppppplVar17 == ppppppplVar18) goto code_r0x0161e160;
code_r0x0161e144:
        if ((pppppplStack_88 < ppppppplVar17[4]) || (ppppppplVar17 == ppppppplVar18))
        goto code_r0x0161e160;
        ppppppplVar17 = ppppppplVar17 + 5;
      }
      lVar10 = *param_2 + uVar15 * 0x40;
      iVar11 = *(int *)(lVar10 + 0x20);
      if (iVar11 == 6) {
        (*(code *)**ppppppplVar17)(ppppppplVar17,lVar10 + 0x28);
      }
      else if (iVar11 == 7) {
        (*(code *)(*ppppppplVar17)[1])(ppppppplVar17,*param_2 + uVar15 * 0x40 + 0x28);
      }
      uVar1 = (int)uVar15 + 1;
      uVar15 = (ulong)uVar1;
    } while (uVar1 < *(uint *)(param_2 + 1));
  }
  return 1;
}

// ==== IInfoBaseMap<unsigned long, CAreaInfoCategoryList>::DeserializeChild(Aska::ASON::AValue::AMap const*)
// vaddr 0x151e9ac | ghidra 0x161e9ac | size 544 | symbol _ZN12IInfoBaseMapIm21CAreaInfoCategoryListE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN12IInfoBaseMapIm21CAreaInfoCategoryListE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE
          (long *param_1,long *param_2)

{
  uint uVar1;
  undefined *puVar2;
  undefined *puVar3;
  int iVar4;
  long *plVar5;
  long lVar6;
  long *plVar7;
  ulong uVar8;
  long *plVar9;
  long *plVar10;
  undefined *puStack_b8;
  undefined8 *puStack_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined8 *puStack_98;
  undefined8 uStack_90;
  undefined8 uStack_88;
  undefined8 *puStack_80;
  undefined8 uStack_78;
  undefined8 uStack_70;
  ulong uStack_68;
  
  plVar10 = param_1 + 8;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CAreaInfoCategoryList>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CAreaInfoCategoryList>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CAreaInfoCategoryList>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CAreaInfoCategoryList>, void*>*)(param_1 + 7,*plVar10);
  param_1[7] = (long)plVar10;
  param_1[8] = 0;
  param_1[9] = 0;
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0282d54e/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\Info/InfoBase.h"*/,0x1c1,&UNK_027dc58a/*"apParser is null."*/);
    iVar4 = iRam0000000000000008;
  }
  else {
    iVar4 = (int)param_2[1];
  }
  if (iVar4 != 0) {
    uVar8 = 0;
    puVar2 = PTR__ZTV21CAreaInfoCategoryList_02cc1c80 + 0x10;
    puVar3 = PTR__ZTV8InfoBase_02cc49c8 + 0x10;
    do {
      uStack_68 = (**(code **)(*param_1 + 0x20))(param_1,*param_2 + uVar8 * 0x40);
      plVar5 = (long *)param_1[8];
      plVar7 = plVar10;
      if ((long *)param_1[8] == (long *)0x0) {
code_r0x0161eae0:
        uStack_a8 = 0;
        uStack_a0 = 0;
        uStack_90 = 0;
        uStack_88 = 0;
        uStack_78 = 0;
        uStack_70 = 0;
        puStack_b8 = puVar2;
        puStack_b0 = &uStack_a8;
        puStack_98 = &uStack_90;
        puStack_80 = &uStack_78;
        lVar6 = std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned long, CAreaInfoCategoryList>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CAreaInfoCategoryList>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CAreaInfoCategoryList>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CAreaInfoCategoryList>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CAreaInfoCategoryList>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned long, unsigned long&, CAreaInfoCategoryList>(unsigned long const&, unsigned long&, CAreaInfoCategoryList&&)(param_1 + 7,&uStack_68,&uStack_68,&puStack_b8);
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CAreaInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CAreaInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CAreaInfo>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CAreaInfo>, void*>*)(&puStack_80,uStack_78);
        puStack_b8 = puVar3;
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*)(&puStack_98,uStack_90);
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*)(&puStack_b0,uStack_a8);
        plVar9 = (long *)(lVar6 + 0x28);
        (**(code **)(*plVar9 + 0x10))(plVar9);
      }
      else {
        do {
          while (plVar9 = plVar5, (ulong)plVar9[4] < uStack_68) {
            plVar5 = (long *)plVar9[1];
            if ((long *)plVar9[1] == (long *)0x0) {
              plVar9 = plVar7;
              if (plVar7 != plVar10) goto code_r0x0161eac4;
              goto code_r0x0161eae0;
            }
          }
          plVar5 = (long *)*plVar9;
          plVar7 = plVar9;
        } while ((long *)*plVar9 != (long *)0x0);
        if (plVar9 == plVar10) goto code_r0x0161eae0;
code_r0x0161eac4:
        if ((uStack_68 < (ulong)plVar9[4]) || (plVar9 == plVar10)) goto code_r0x0161eae0;
        plVar9 = plVar9 + 5;
      }
      lVar6 = *param_2 + uVar8 * 0x40;
      iVar4 = *(int *)(lVar6 + 0x20);
      if (iVar4 == 6) {
        (**(code **)*plVar9)(plVar9,lVar6 + 0x28);
      }
      else if (iVar4 == 7) {
        (**(code **)(*plVar9 + 8))(plVar9,*param_2 + uVar8 * 0x40 + 0x28);
      }
      uVar1 = (int)uVar8 + 1;
      uVar8 = (ulong)uVar1;
    } while (uVar1 < *(uint *)(param_2 + 1));
  }
  return 1;
}

// ==== IInfoBaseMap<unsigned long, CAreaInfo>::DeserializeChild(Aska::ASON::AValue::AMap const*)
// vaddr 0x151ef48 | ghidra 0x161ef48 | size 1132 | symbol _ZN12IInfoBaseMapIm9CAreaInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Type propagation algorithm not settling */

undefined8
_ZN12IInfoBaseMapIm9CAreaInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE
          (long *param_1,long *param_2)

{
  uint uVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined *puVar5;
  undefined *puVar6;
  undefined *puVar7;
  undefined *puVar8;
  undefined *puVar9;
  undefined *puVar10;
  undefined *puVar11;
  long lVar12;
  int iVar13;
  long *plVar14;
  long *******ppppppplVar15;
  long *******ppppppplVar16;
  ulong uVar17;
  long *******ppppppplVar18;
  long *******ppppppplVar19;
  long *******ppppppplVar20;
  undefined *puStack_180;
  undefined8 *puStack_178;
  undefined8 auStack_170 [2];
  undefined8 *puStack_160;
  undefined8 uStack_158;
  undefined8 uStack_150;
  undefined *puStack_148;
  undefined8 uStack_140;
  undefined1 uStack_138;
  undefined1 auStack_130 [24];
  undefined *puStack_118;
  undefined8 uStack_110;
  undefined1 uStack_108;
  undefined1 auStack_100 [24];
  undefined *puStack_e8;
  undefined8 uStack_e0;
  undefined1 uStack_d8;
  undefined1 auStack_d0 [24];
  undefined *puStack_b8;
  undefined8 uStack_b0;
  undefined1 uStack_a8;
  undefined1 auStack_a0 [24];
  long ******pppppplStack_88;
  long *******appppppplStack_80 [3];
  long *******ppppppplStack_68;
  
  ppppppplVar18 = (long *******)(param_1 + 8);
  plVar14 = param_1 + 7;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CAreaInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CAreaInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CAreaInfo>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CAreaInfo>, void*>*)(plVar14,*ppppppplVar18);
  param_1[7] = (long)ppppppplVar18;
  param_1[8] = 0;
  param_1[9] = 0;
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0282d54e/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\Info/InfoBase.h"*/,0x1c1,&UNK_027dc58a/*"apParser is null."*/);
    iVar13 = iRam0000000000000008;
  }
  else {
    iVar13 = (int)param_2[1];
  }
  if (iVar13 != 0) {
    puVar2 = PTR__ZTV9CAreaInfo_02cb8cb8 + 0x10;
    puVar3 = PTR__ZTV22CParameterPropertyBaseILj13EE_02cba498 + 0x10;
    puVar4 = PTR__ZTV23CParameterPropertyValueIjLj13E18CPropertyConverterE_02cbd818 + 0x10;
    puVar5 = PTR__ZTV22CParameterPropertyBaseILj14EE_02cb9db0 + 0x10;
    puVar6 = PTR__ZTV23CParameterPropertyValueIbLj14E18CPropertyConverterE_02cbe940 + 0x10;
    puVar7 = PTR__ZTV22CParameterPropertyBaseILj15EE_02cc0790 + 0x10;
    puVar8 = PTR__ZTV23CParameterPropertyValueIbLj15E18CPropertyConverterE_02cbfef0 + 0x10;
    puVar9 = PTR__ZTV22CParameterPropertyBaseILj16EE_02cb9c20 + 0x10;
    puVar10 = PTR__ZTV23CParameterPropertyValueIbLj16E18CPropertyConverterE_02cc0000 + 0x10;
    uVar17 = 0;
    puVar11 = PTR__ZTV8InfoBase_02cc49c8 + 0x10;
    do {
      pppppplStack_88 =
           (long ******)(**(code **)(*param_1 + 0x20))(param_1,*param_2 + uVar17 * 0x40);
      ppppppplVar16 = (long *******)param_1[8];
      ppppppplVar15 = ppppppplVar18;
      if ((long *******)param_1[8] == (long *******)0x0) {
code_r0x0161f118:
        memset(auStack_170,0,0xe8);
        uStack_158 = 0;
        uStack_150 = 0;
        uStack_138 = 0;
        uStack_140 = 0;
        puStack_180 = puVar2;
        puStack_178 = auStack_170;
        puStack_160 = &uStack_158;
        puStack_148 = puVar3;
        Framework::CHash32::CHash32()(auStack_130);
        uStack_108 = 0;
        uStack_110 = 0;
        puStack_148 = puVar4;
        puStack_118 = puVar5;
        Framework::CHash32::CHash32()(auStack_100);
        uStack_d8 = 0;
        uStack_e0 = 0;
        puStack_118 = puVar6;
        puStack_e8 = puVar7;
        Framework::CHash32::CHash32()(auStack_d0);
        uStack_a8 = 0;
        uStack_b0 = 0;
        puStack_e8 = puVar8;
        puStack_b8 = puVar9;
        Framework::CHash32::CHash32()(auStack_a0);
        ppppppplVar16 = (long *******)*ppppppplVar18;
        if ((long *******)*ppppppplVar18 == (long *******)0x0) {
          ppppppplVar20 = (long *******)*ppppppplVar18;
          ppppppplVar15 = ppppppplVar18;
          ppppppplVar19 = ppppppplVar18;
        }
        else {
          do {
            while (ppppppplVar15 = ppppppplVar16, ppppppplVar15[4] <= pppppplStack_88) {
              if (pppppplStack_88 <= ppppppplVar15[4]) {
                ppppppplVar20 = ppppppplVar15;
                ppppppplVar19 = (long *******)&ppppppplStack_68;
                goto joined_r0x0161f224;
              }
              ppppppplVar19 = ppppppplVar15 + 1;
              ppppppplVar16 = (long *******)*ppppppplVar19;
              if ((long *******)*ppppppplVar19 == (long *******)0x0) {
                ppppppplVar20 = (long *******)*ppppppplVar19;
                goto joined_r0x0161f224;
              }
            }
            ppppppplVar16 = (long *******)*ppppppplVar15;
          } while ((long *******)*ppppppplVar15 != (long *******)0x0);
          ppppppplVar20 = (long *******)*ppppppplVar15;
          ppppppplVar19 = ppppppplVar15;
        }
joined_r0x0161f224:
        ppppppplStack_68 = ppppppplVar15;
        if (ppppppplVar20 == (long *******)0x0) {
          puStack_b8 = puVar10;
          std::__ndk1::unique_ptr<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CAreaInfo>, void*>, std::__ndk1::__tree_node_destructor<Framework::CSTLAllocator<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CAreaInfo>, void*>, Framework::CSTLMapAllocatorInf> > > std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CAreaInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CAreaInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CAreaInfo>, Framework::CSTLMapAllocatorInf> >::__construct_node<unsigned long&, CAreaInfo>(unsigned long&, CAreaInfo&&)(appppppplStack_80,plVar14,&pppppplStack_88,&puStack_180);
          *appppppplStack_80[0] = (long ******)0x0;
          appppppplStack_80[0][1] = (long ******)0x0;
          appppppplStack_80[0][2] = (long ******)ppppppplVar15;
          *ppppppplVar19 = (long ******)appppppplStack_80[0];
          ppppppplVar16 = appppppplStack_80[0];
          if (*(long *)*plVar14 != 0) {
            *plVar14 = *(long *)*plVar14;
            ppppppplVar16 = (long *******)*ppppppplVar19;
          }
          void std::__ndk1::__tree_balance_after_insert<std::__ndk1::__tree_node_base<void*>*>(std::__ndk1::__tree_node_base<void*>*, std::__ndk1::__tree_node_base<void*>*)(param_1[8],ppppppplVar16);
          param_1[9] = param_1[9] + 1;
          ppppppplVar20 = appppppplStack_80[0];
        }
        puStack_180 = PTR__ZTV9CAreaInfo_02cb8cb8 + 0x10;
        puStack_b8 = PTR__ZTV22CParameterPropertyBaseILj16EE_02cb9c20 + 0x10;
        Framework::CHash32::~CHash32()(auStack_a0);
        puStack_e8 = PTR__ZTV22CParameterPropertyBaseILj15EE_02cc0790 + 0x10;
        Framework::CHash32::~CHash32()(auStack_d0);
        puStack_118 = PTR__ZTV22CParameterPropertyBaseILj14EE_02cb9db0 + 0x10;
        Framework::CHash32::~CHash32()(auStack_100);
        puStack_148 = PTR__ZTV22CParameterPropertyBaseILj13EE_02cba498 + 0x10;
        Framework::CHash32::~CHash32()(auStack_130);
        puStack_180 = puVar11;
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*)(&puStack_160,uStack_158);
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*)(&puStack_178,auStack_170[0]);
        ppppppplVar20 = ppppppplVar20 + 5;
        (*(code *)(*ppppppplVar20)[2])(ppppppplVar20);
      }
      else {
        do {
          while (ppppppplVar20 = ppppppplVar16, ppppppplVar20[4] < pppppplStack_88) {
            ppppppplVar16 = (long *******)ppppppplVar20[1];
            if ((long *******)ppppppplVar20[1] == (long *******)0x0) {
              ppppppplVar20 = ppppppplVar15;
              if (ppppppplVar15 != ppppppplVar18) goto code_r0x0161f0fc;
              goto code_r0x0161f118;
            }
          }
          ppppppplVar16 = (long *******)*ppppppplVar20;
          ppppppplVar15 = ppppppplVar20;
        } while ((long *******)*ppppppplVar20 != (long *******)0x0);
        if (ppppppplVar20 == ppppppplVar18) goto code_r0x0161f118;
code_r0x0161f0fc:
        if ((pppppplStack_88 < ppppppplVar20[4]) || (ppppppplVar20 == ppppppplVar18))
        goto code_r0x0161f118;
        ppppppplVar20 = ppppppplVar20 + 5;
      }
      lVar12 = *param_2 + uVar17 * 0x40;
      iVar13 = *(int *)(lVar12 + 0x20);
      if (iVar13 == 6) {
        (*(code *)**ppppppplVar20)(ppppppplVar20,lVar12 + 0x28);
      }
      else if (iVar13 == 7) {
        (*(code *)(*ppppppplVar20)[1])(ppppppplVar20,*param_2 + uVar17 * 0x40 + 0x28);
      }
      uVar1 = (int)uVar17 + 1;
      uVar17 = (ulong)uVar1;
    } while (uVar1 < *(uint *)(param_2 + 1));
  }
  return 1;
}

// ==== IInfoBaseMap<unsigned long, CMissionInfoList>::DeserializeChild(Aska::ASON::AValue::AMap const*)
// vaddr 0x151ff34 | ghidra 0x161ff34 | size 532 | symbol _ZN12IInfoBaseMapIm16CMissionInfoListE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN12IInfoBaseMapIm16CMissionInfoListE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE
          (long *param_1,long *param_2)

{
  uint uVar1;
  undefined *puVar2;
  undefined *puVar3;
  int iVar4;
  long *plVar5;
  long lVar6;
  long *plVar7;
  ulong uVar8;
  long *plVar9;
  long *plVar10;
  undefined *puStack_b8;
  undefined8 *puStack_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined8 *puStack_98;
  undefined8 uStack_90;
  undefined8 uStack_88;
  undefined8 uStack_80;
  undefined8 uStack_78;
  undefined8 uStack_70;
  ulong uStack_68;
  
  plVar10 = param_1 + 8;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CMissionInfoList>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CMissionInfoList>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CMissionInfoList>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CMissionInfoList>, void*>*)(param_1 + 7,*plVar10);
  param_1[7] = (long)plVar10;
  param_1[8] = 0;
  param_1[9] = 0;
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0282d54e/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\Info/InfoBase.h"*/,0x1c1,&UNK_027dc58a/*"apParser is null."*/);
    iVar4 = iRam0000000000000008;
  }
  else {
    iVar4 = (int)param_2[1];
  }
  if (iVar4 != 0) {
    uVar8 = 0;
    puVar2 = PTR__ZTV16CMissionInfoList_02cbb218 + 0x10;
    puVar3 = PTR__ZTV8InfoBase_02cc49c8 + 0x10;
    do {
      uStack_68 = (**(code **)(*param_1 + 0x20))(param_1,*param_2 + uVar8 * 0x40);
      plVar5 = (long *)param_1[8];
      plVar7 = plVar10;
      if ((long *)param_1[8] == (long *)0x0) {
code_r0x01620064:
        uStack_a8 = 0;
        uStack_a0 = 0;
        uStack_90 = 0;
        uStack_88 = 0;
        uStack_78 = 0;
        uStack_70 = 0;
        uStack_80 = 0;
        puStack_b8 = puVar2;
        puStack_b0 = &uStack_a8;
        puStack_98 = &uStack_90;
        lVar6 = std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned long, CMissionInfoList>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CMissionInfoList>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CMissionInfoList>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CMissionInfoList>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CMissionInfoList>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned long, unsigned long&, CMissionInfoList>(unsigned long const&, unsigned long&, CMissionInfoList&&)(param_1 + 7,&uStack_68,&uStack_68,&puStack_b8);
        std::__ndk1::__vector_base<CMissionElementInfo, Framework::CSTLAllocator<CMissionElementInfo, Framework::CSTLVectorAllocatorInf> >::~__vector_base()(&uStack_80);
        puStack_b8 = puVar3;
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*)(&puStack_98,uStack_90);
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*)(&puStack_b0,uStack_a8);
        plVar9 = (long *)(lVar6 + 0x28);
        (**(code **)(*plVar9 + 0x10))(plVar9);
      }
      else {
        do {
          while (plVar9 = plVar5, (ulong)plVar9[4] < uStack_68) {
            plVar5 = (long *)plVar9[1];
            if ((long *)plVar9[1] == (long *)0x0) {
              plVar9 = plVar7;
              if (plVar7 != plVar10) goto code_r0x01620048;
              goto code_r0x01620064;
            }
          }
          plVar5 = (long *)*plVar9;
          plVar7 = plVar9;
        } while ((long *)*plVar9 != (long *)0x0);
        if (plVar9 == plVar10) goto code_r0x01620064;
code_r0x01620048:
        if ((uStack_68 < (ulong)plVar9[4]) || (plVar9 == plVar10)) goto code_r0x01620064;
        plVar9 = plVar9 + 5;
      }
      lVar6 = *param_2 + uVar8 * 0x40;
      iVar4 = *(int *)(lVar6 + 0x20);
      if (iVar4 == 6) {
        (**(code **)*plVar9)(plVar9,lVar6 + 0x28);
      }
      else if (iVar4 == 7) {
        (**(code **)(*plVar9 + 8))(plVar9,*param_2 + uVar8 * 0x40 + 0x28);
      }
      uVar1 = (int)uVar8 + 1;
      uVar8 = (ulong)uVar1;
    } while (uVar1 < *(uint *)(param_2 + 1));
  }
  return 1;
}

// ==== IInfoBaseMap<unsigned long, CWorldMapInfo>::DeserializeChild(Aska::ASON::AValue::AMap const*)
// vaddr 0x152164c | ghidra 0x162164c | size 1072 | symbol _ZN12IInfoBaseMapIm13CWorldMapInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Type propagation algorithm not settling */

undefined8
_ZN12IInfoBaseMapIm13CWorldMapInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE
          (long *param_1,long *param_2)

{
  uint uVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined *puVar5;
  undefined *puVar6;
  undefined *puVar7;
  undefined *puVar8;
  undefined *puVar9;
  undefined *puVar10;
  undefined *puVar11;
  undefined *puVar12;
  undefined *puVar13;
  long lVar14;
  int iVar15;
  long *plVar16;
  long *******ppppppplVar17;
  long *******ppppppplVar18;
  ulong uVar19;
  long *******ppppppplVar20;
  long *******ppppppplVar21;
  long *******ppppppplVar22;
  undefined *puStack_1d0;
  undefined1 *puStack_1c8;
  undefined1 auStack_1c0 [16];
  undefined8 *puStack_1b0;
  undefined8 uStack_1a8;
  undefined8 uStack_1a0;
  undefined *puStack_198;
  undefined8 uStack_190;
  undefined1 uStack_188;
  undefined1 auStack_180 [24];
  undefined *puStack_168;
  undefined8 uStack_160;
  undefined1 uStack_158;
  undefined1 auStack_150 [24];
  undefined *puStack_138;
  undefined8 uStack_130;
  undefined1 uStack_128;
  undefined1 auStack_120 [24];
  undefined *puStack_108;
  undefined8 uStack_100;
  undefined1 uStack_f8;
  undefined1 auStack_f0 [16];
  undefined8 uStack_e0;
  undefined8 uStack_d8;
  undefined8 uStack_d0;
  undefined *puStack_c8;
  undefined8 uStack_c0;
  undefined1 uStack_b8;
  undefined1 auStack_b0 [16];
  undefined8 uStack_a0;
  undefined8 uStack_98;
  undefined8 uStack_90;
  long ******pppppplStack_88;
  long *******appppppplStack_80 [3];
  long *******ppppppplStack_68;
  
  ppppppplVar22 = (long *******)(param_1 + 8);
  plVar16 = param_1 + 7;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CWorldMapInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CWorldMapInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CWorldMapInfo>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CWorldMapInfo>, void*>*)(plVar16,*ppppppplVar22);
  param_1[7] = (long)ppppppplVar22;
  param_1[8] = 0;
  param_1[9] = 0;
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0282d54e/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\Info/InfoBase.h"*/,0x1c1,&UNK_027dc58a/*"apParser is null."*/);
    iVar15 = iRam0000000000000008;
  }
  else {
    iVar15 = (int)param_2[1];
  }
  if (iVar15 != 0) {
    puVar2 = PTR__ZTV11CPlanetInfo_02cc2988 + 0x10;
    puVar3 = PTR__ZTV22CParameterPropertyBaseILj13EE_02cba498 + 0x10;
    puVar4 = PTR__ZTV23CParameterPropertyValueIjLj13E18CPropertyConverterE_02cbd818 + 0x10;
    puVar5 = PTR__ZTV22CParameterPropertyBaseILj14EE_02cb9db0 + 0x10;
    puVar6 = PTR__ZTV23CParameterPropertyValueIbLj14E18CPropertyConverterE_02cbe940 + 0x10;
    puVar7 = PTR__ZTV22CParameterPropertyBaseILj15EE_02cc0790 + 0x10;
    puVar8 = PTR__ZTV23CParameterPropertyValueIbLj15E18CPropertyConverterE_02cbfef0 + 0x10;
    puVar9 = PTR__ZTV13CWorldMapInfo_02cbc5f8 + 0x10;
    puVar10 = PTR__ZTV22CParameterPropertyBaseILj33EE_02cb96b8 + 0x10;
    puVar11 = PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj33EE_02cb7cb0
              + 0x10;
    puVar12 = PTR__ZTV22CParameterPropertyBaseILj34EE_02cc0de8 + 0x10;
    uVar19 = 0;
    puVar13 = PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj34EE_02cb8320
              + 0x10;
    do {
      pppppplStack_88 =
           (long ******)(**(code **)(*param_1 + 0x20))(param_1,*param_2 + uVar19 * 0x40);
      ppppppplVar18 = (long *******)param_1[8];
      ppppppplVar17 = ppppppplVar22;
      if ((long *******)param_1[8] == (long *******)0x0) {
code_r0x01621840:
        memset(auStack_1c0,0,0x138);
        uStack_1a8 = 0;
        uStack_1a0 = 0;
        uStack_188 = 0;
        uStack_190 = 0;
        puStack_1d0 = puVar2;
        puStack_1c8 = auStack_1c0;
        puStack_1b0 = &uStack_1a8;
        puStack_198 = puVar3;
        Framework::CHash32::CHash32()(auStack_180);
        uStack_158 = 0;
        uStack_160 = 0;
        puStack_198 = puVar4;
        puStack_168 = puVar5;
        Framework::CHash32::CHash32()(auStack_150);
        uStack_128 = 0;
        uStack_130 = 0;
        puStack_168 = puVar6;
        puStack_138 = puVar7;
        Framework::CHash32::CHash32()(auStack_120);
        uStack_f8 = 0;
        uStack_100 = 0;
        puStack_1d0 = puVar9;
        puStack_138 = puVar8;
        puStack_108 = puVar10;
        Framework::CHash32::CHash32()(auStack_f0);
        uStack_d8 = 0;
        uStack_d0 = 0;
        uStack_e0 = 0;
        uStack_b8 = 0;
        uStack_c0 = 0;
        puStack_108 = puVar11;
        puStack_c8 = puVar12;
        Framework::CHash32::CHash32()(auStack_b0);
        uStack_98 = 0;
        uStack_90 = 0;
        uStack_a0 = 0;
        ppppppplVar18 = (long *******)*ppppppplVar22;
        if ((long *******)*ppppppplVar22 == (long *******)0x0) {
          ppppppplVar21 = (long *******)*ppppppplVar22;
          ppppppplVar17 = ppppppplVar22;
          ppppppplVar20 = ppppppplVar22;
        }
        else {
          do {
            while (ppppppplVar17 = ppppppplVar18, ppppppplVar17[4] <= pppppplStack_88) {
              if (pppppplStack_88 <= ppppppplVar17[4]) {
                ppppppplVar21 = ppppppplVar17;
                ppppppplVar20 = (long *******)&ppppppplStack_68;
                goto joined_r0x01621978;
              }
              ppppppplVar20 = ppppppplVar17 + 1;
              ppppppplVar18 = (long *******)*ppppppplVar20;
              if ((long *******)*ppppppplVar20 == (long *******)0x0) {
                ppppppplVar21 = (long *******)*ppppppplVar20;
                goto joined_r0x01621978;
              }
            }
            ppppppplVar18 = (long *******)*ppppppplVar17;
          } while ((long *******)*ppppppplVar17 != (long *******)0x0);
          ppppppplVar21 = (long *******)*ppppppplVar17;
          ppppppplVar20 = ppppppplVar17;
        }
joined_r0x01621978:
        puStack_c8 = puVar13;
        ppppppplStack_68 = ppppppplVar17;
        if (ppppppplVar21 == (long *******)0x0) {
          std::__ndk1::unique_ptr<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CWorldMapInfo>, void*>, std::__ndk1::__tree_node_destructor<Framework::CSTLAllocator<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CWorldMapInfo>, void*>, Framework::CSTLMapAllocatorInf> > > std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CWorldMapInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CWorldMapInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CWorldMapInfo>, Framework::CSTLMapAllocatorInf> >::__construct_node<unsigned long&, CWorldMapInfo>(unsigned long&, CWorldMapInfo&&)(appppppplStack_80,plVar16,&pppppplStack_88,&puStack_1d0);
          *appppppplStack_80[0] = (long ******)0x0;
          appppppplStack_80[0][1] = (long ******)0x0;
          appppppplStack_80[0][2] = (long ******)ppppppplVar17;
          *ppppppplVar20 = (long ******)appppppplStack_80[0];
          ppppppplVar18 = appppppplStack_80[0];
          if (*(long *)*plVar16 != 0) {
            *plVar16 = *(long *)*plVar16;
            ppppppplVar18 = (long *******)*ppppppplVar20;
          }
          void std::__ndk1::__tree_balance_after_insert<std::__ndk1::__tree_node_base<void*>*>(std::__ndk1::__tree_node_base<void*>*, std::__ndk1::__tree_node_base<void*>*)(param_1[8],ppppppplVar18);
          param_1[9] = param_1[9] + 1;
          ppppppplVar21 = appppppplStack_80[0];
        }
        CWorldMapInfo::~CWorldMapInfo()(&puStack_1d0);
        ppppppplVar21 = ppppppplVar21 + 5;
        (*(code *)(*ppppppplVar21)[2])(ppppppplVar21);
      }
      else {
        do {
          while (ppppppplVar21 = ppppppplVar18, ppppppplVar21[4] < pppppplStack_88) {
            ppppppplVar18 = (long *******)ppppppplVar21[1];
            if ((long *******)ppppppplVar21[1] == (long *******)0x0) {
              ppppppplVar21 = ppppppplVar17;
              if (ppppppplVar17 != ppppppplVar22) goto code_r0x01621824;
              goto code_r0x01621840;
            }
          }
          ppppppplVar18 = (long *******)*ppppppplVar21;
          ppppppplVar17 = ppppppplVar21;
        } while ((long *******)*ppppppplVar21 != (long *******)0x0);
        if (ppppppplVar21 == ppppppplVar22) goto code_r0x01621840;
code_r0x01621824:
        if ((pppppplStack_88 < ppppppplVar21[4]) || (ppppppplVar21 == ppppppplVar22))
        goto code_r0x01621840;
        ppppppplVar21 = ppppppplVar21 + 5;
      }
      lVar14 = *param_2 + uVar19 * 0x40;
      iVar15 = *(int *)(lVar14 + 0x20);
      if (iVar15 == 6) {
        (*(code *)**ppppppplVar21)(ppppppplVar21,lVar14 + 0x28);
      }
      else if (iVar15 == 7) {
        (*(code *)(*ppppppplVar21)[1])(ppppppplVar21,*param_2 + uVar19 * 0x40 + 0x28);
      }
      uVar1 = (int)uVar19 + 1;
      uVar19 = (ulong)uVar1;
    } while (uVar1 < *(uint *)(param_2 + 1));
  }
  return 1;
}

// ==== IInfoBaseMap<unsigned long, CWorldMapCellInfoList>::DeserializeChild(Aska::ASON::AValue::AMap const*)
// vaddr 0x15222ac | ghidra 0x16222ac | size 544 | symbol _ZN12IInfoBaseMapIm21CWorldMapCellInfoListE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN12IInfoBaseMapIm21CWorldMapCellInfoListE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE
          (long *param_1,long *param_2)

{
  uint uVar1;
  undefined *puVar2;
  undefined *puVar3;
  int iVar4;
  long *plVar5;
  long lVar6;
  long *plVar7;
  ulong uVar8;
  long *plVar9;
  long *plVar10;
  undefined *puStack_b8;
  undefined8 *puStack_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined8 *puStack_98;
  undefined8 uStack_90;
  undefined8 uStack_88;
  undefined8 *puStack_80;
  undefined8 uStack_78;
  undefined8 uStack_70;
  ulong uStack_68;
  
  plVar10 = param_1 + 8;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CWorldMapCellInfoList>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CWorldMapCellInfoList>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CWorldMapCellInfoList>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CWorldMapCellInfoList>, void*>*)(param_1 + 7,*plVar10);
  param_1[7] = (long)plVar10;
  param_1[8] = 0;
  param_1[9] = 0;
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0282d54e/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\Info/InfoBase.h"*/,0x1c1,&UNK_027dc58a/*"apParser is null."*/);
    iVar4 = iRam0000000000000008;
  }
  else {
    iVar4 = (int)param_2[1];
  }
  if (iVar4 != 0) {
    uVar8 = 0;
    puVar2 = PTR__ZTV21CWorldMapCellInfoList_02cc27d0 + 0x10;
    puVar3 = PTR__ZTV8InfoBase_02cc49c8 + 0x10;
    do {
      uStack_68 = (**(code **)(*param_1 + 0x20))(param_1,*param_2 + uVar8 * 0x40);
      plVar5 = (long *)param_1[8];
      plVar7 = plVar10;
      if ((long *)param_1[8] == (long *)0x0) {
code_r0x016223e0:
        uStack_a8 = 0;
        uStack_a0 = 0;
        uStack_90 = 0;
        uStack_88 = 0;
        uStack_78 = 0;
        uStack_70 = 0;
        puStack_b8 = puVar2;
        puStack_b0 = &uStack_a8;
        puStack_98 = &uStack_90;
        puStack_80 = &uStack_78;
        lVar6 = std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned long, CWorldMapCellInfoList>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CWorldMapCellInfoList>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CWorldMapCellInfoList>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CWorldMapCellInfoList>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CWorldMapCellInfoList>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned long, unsigned long&, CWorldMapCellInfoList>(unsigned long const&, unsigned long&, CWorldMapCellInfoList&&)(param_1 + 7,&uStack_68,&uStack_68,&puStack_b8);
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CWorldMapCellInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CWorldMapCellInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CWorldMapCellInfo>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CWorldMapCellInfo>, void*>*)(&puStack_80,uStack_78);
        puStack_b8 = puVar3;
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*)(&puStack_98,uStack_90);
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*)(&puStack_b0,uStack_a8);
        plVar9 = (long *)(lVar6 + 0x28);
        (**(code **)(*plVar9 + 0x10))(plVar9);
      }
      else {
        do {
          while (plVar9 = plVar5, (ulong)plVar9[4] < uStack_68) {
            plVar5 = (long *)plVar9[1];
            if ((long *)plVar9[1] == (long *)0x0) {
              plVar9 = plVar7;
              if (plVar7 != plVar10) goto code_r0x016223c4;
              goto code_r0x016223e0;
            }
          }
          plVar5 = (long *)*plVar9;
          plVar7 = plVar9;
        } while ((long *)*plVar9 != (long *)0x0);
        if (plVar9 == plVar10) goto code_r0x016223e0;
code_r0x016223c4:
        if ((uStack_68 < (ulong)plVar9[4]) || (plVar9 == plVar10)) goto code_r0x016223e0;
        plVar9 = plVar9 + 5;
      }
      lVar6 = *param_2 + uVar8 * 0x40;
      iVar4 = *(int *)(lVar6 + 0x20);
      if (iVar4 == 6) {
        (**(code **)*plVar9)(plVar9,lVar6 + 0x28);
      }
      else if (iVar4 == 7) {
        (**(code **)(*plVar9 + 8))(plVar9,*param_2 + uVar8 * 0x40 + 0x28);
      }
      uVar1 = (int)uVar8 + 1;
      uVar8 = (ulong)uVar1;
    } while (uVar1 < *(uint *)(param_2 + 1));
  }
  return 1;
}

// ==== IInfoBaseMap<unsigned long, CWorldMapCellInfo>::DeserializeChild(Aska::ASON::AValue::AMap const*)
// vaddr 0x1522848 | ghidra 0x1622848 | size 1156 | symbol _ZN12IInfoBaseMapIm17CWorldMapCellInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Type propagation algorithm not settling */

undefined8
_ZN12IInfoBaseMapIm17CWorldMapCellInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE
          (long *param_1,long *param_2)

{
  uint uVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined *puVar5;
  undefined *puVar6;
  undefined *puVar7;
  undefined *puVar8;
  undefined *puVar9;
  undefined *puVar10;
  undefined *puVar11;
  undefined *puVar12;
  long lVar13;
  int iVar14;
  long *plVar15;
  long *******ppppppplVar16;
  long *******ppppppplVar17;
  ulong uVar18;
  long *******ppppppplVar19;
  long *******ppppppplVar20;
  long *******ppppppplVar21;
  undefined *puStack_180;
  undefined8 *puStack_178;
  undefined8 auStack_170 [2];
  undefined8 *puStack_160;
  undefined8 uStack_158;
  undefined8 uStack_150;
  undefined *puStack_148;
  undefined8 uStack_140;
  undefined1 uStack_138;
  undefined1 auStack_130 [24];
  undefined *puStack_118;
  undefined8 uStack_110;
  undefined1 uStack_108;
  undefined1 auStack_100 [24];
  undefined *puStack_e8;
  undefined8 uStack_e0;
  undefined1 uStack_d8;
  undefined1 auStack_d0 [24];
  undefined *puStack_b8;
  undefined8 uStack_b0;
  undefined1 uStack_a8;
  undefined1 auStack_a0 [24];
  long ******pppppplStack_88;
  long *******appppppplStack_80 [3];
  long *******ppppppplStack_68;
  
  ppppppplVar19 = (long *******)(param_1 + 8);
  plVar15 = param_1 + 7;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CWorldMapCellInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CWorldMapCellInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CWorldMapCellInfo>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CWorldMapCellInfo>, void*>*)(plVar15,*ppppppplVar19);
  param_1[7] = (long)ppppppplVar19;
  param_1[8] = 0;
  param_1[9] = 0;
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0282d54e/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\Info/InfoBase.h"*/,0x1c1,&UNK_027dc58a/*"apParser is null."*/);
    iVar14 = iRam0000000000000008;
  }
  else {
    iVar14 = (int)param_2[1];
  }
  if (iVar14 != 0) {
    puVar2 = PTR__ZTV9CAreaInfo_02cb8cb8 + 0x10;
    puVar3 = PTR__ZTV22CParameterPropertyBaseILj13EE_02cba498 + 0x10;
    puVar4 = PTR__ZTV23CParameterPropertyValueIjLj13E18CPropertyConverterE_02cbd818 + 0x10;
    puVar5 = PTR__ZTV22CParameterPropertyBaseILj14EE_02cb9db0 + 0x10;
    puVar6 = PTR__ZTV23CParameterPropertyValueIbLj14E18CPropertyConverterE_02cbe940 + 0x10;
    puVar7 = PTR__ZTV22CParameterPropertyBaseILj15EE_02cc0790 + 0x10;
    puVar8 = PTR__ZTV23CParameterPropertyValueIbLj15E18CPropertyConverterE_02cbfef0 + 0x10;
    puVar9 = PTR__ZTV22CParameterPropertyBaseILj16EE_02cb9c20 + 0x10;
    puVar10 = PTR__ZTV23CParameterPropertyValueIbLj16E18CPropertyConverterE_02cc0000 + 0x10;
    puVar11 = PTR__ZTV17CWorldMapCellInfo_02cbebe8 + 0x10;
    uVar18 = 0;
    puVar12 = PTR__ZTV8InfoBase_02cc49c8 + 0x10;
    do {
      pppppplStack_88 =
           (long ******)(**(code **)(*param_1 + 0x20))(param_1,*param_2 + uVar18 * 0x40);
      ppppppplVar17 = (long *******)param_1[8];
      ppppppplVar16 = ppppppplVar19;
      if ((long *******)param_1[8] == (long *******)0x0) {
code_r0x01622a28:
        memset(auStack_170,0,0xe8);
        uStack_158 = 0;
        uStack_150 = 0;
        uStack_138 = 0;
        uStack_140 = 0;
        puStack_180 = puVar2;
        puStack_178 = auStack_170;
        puStack_160 = &uStack_158;
        puStack_148 = puVar3;
        Framework::CHash32::CHash32()(auStack_130);
        uStack_108 = 0;
        uStack_110 = 0;
        puStack_148 = puVar4;
        puStack_118 = puVar5;
        Framework::CHash32::CHash32()(auStack_100);
        uStack_d8 = 0;
        uStack_e0 = 0;
        puStack_118 = puVar6;
        puStack_e8 = puVar7;
        Framework::CHash32::CHash32()(auStack_d0);
        uStack_a8 = 0;
        uStack_b0 = 0;
        puStack_e8 = puVar8;
        puStack_b8 = puVar9;
        Framework::CHash32::CHash32()(auStack_a0);
        ppppppplVar17 = (long *******)*ppppppplVar19;
        if ((long *******)*ppppppplVar19 == (long *******)0x0) {
          ppppppplVar21 = (long *******)*ppppppplVar19;
          ppppppplVar16 = ppppppplVar19;
          ppppppplVar20 = ppppppplVar19;
        }
        else {
          do {
            while (ppppppplVar16 = ppppppplVar17, ppppppplVar16[4] <= pppppplStack_88) {
              if (pppppplStack_88 <= ppppppplVar16[4]) {
                ppppppplVar21 = ppppppplVar16;
                ppppppplVar20 = (long *******)&ppppppplStack_68;
                goto joined_r0x01622b3c;
              }
              ppppppplVar20 = ppppppplVar16 + 1;
              ppppppplVar17 = (long *******)*ppppppplVar20;
              if ((long *******)*ppppppplVar20 == (long *******)0x0) {
                ppppppplVar21 = (long *******)*ppppppplVar20;
                goto joined_r0x01622b3c;
              }
            }
            ppppppplVar17 = (long *******)*ppppppplVar16;
          } while ((long *******)*ppppppplVar16 != (long *******)0x0);
          ppppppplVar21 = (long *******)*ppppppplVar16;
          ppppppplVar20 = ppppppplVar16;
        }
joined_r0x01622b3c:
        ppppppplStack_68 = ppppppplVar16;
        if (ppppppplVar21 == (long *******)0x0) {
          puStack_180 = puVar11;
          puStack_b8 = puVar10;
          std::__ndk1::unique_ptr<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CWorldMapCellInfo>, void*>, std::__ndk1::__tree_node_destructor<Framework::CSTLAllocator<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CWorldMapCellInfo>, void*>, Framework::CSTLMapAllocatorInf> > > std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CWorldMapCellInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CWorldMapCellInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CWorldMapCellInfo>, Framework::CSTLMapAllocatorInf> >::__construct_node<unsigned long&, CWorldMapCellInfo>(unsigned long&, CWorldMapCellInfo&&)(appppppplStack_80,plVar15,&pppppplStack_88,&puStack_180);
          *appppppplStack_80[0] = (long ******)0x0;
          appppppplStack_80[0][1] = (long ******)0x0;
          appppppplStack_80[0][2] = (long ******)ppppppplVar16;
          *ppppppplVar20 = (long ******)appppppplStack_80[0];
          ppppppplVar17 = appppppplStack_80[0];
          if (*(long *)*plVar15 != 0) {
            *plVar15 = *(long *)*plVar15;
            ppppppplVar17 = (long *******)*ppppppplVar20;
          }
          void std::__ndk1::__tree_balance_after_insert<std::__ndk1::__tree_node_base<void*>*>(std::__ndk1::__tree_node_base<void*>*, std::__ndk1::__tree_node_base<void*>*)(param_1[8],ppppppplVar17);
          param_1[9] = param_1[9] + 1;
          ppppppplVar21 = appppppplStack_80[0];
        }
        puStack_180 = PTR__ZTV9CAreaInfo_02cb8cb8 + 0x10;
        puStack_b8 = PTR__ZTV22CParameterPropertyBaseILj16EE_02cb9c20 + 0x10;
        Framework::CHash32::~CHash32()(auStack_a0);
        puStack_e8 = PTR__ZTV22CParameterPropertyBaseILj15EE_02cc0790 + 0x10;
        Framework::CHash32::~CHash32()(auStack_d0);
        puStack_118 = PTR__ZTV22CParameterPropertyBaseILj14EE_02cb9db0 + 0x10;
        Framework::CHash32::~CHash32()(auStack_100);
        puStack_148 = PTR__ZTV22CParameterPropertyBaseILj13EE_02cba498 + 0x10;
        Framework::CHash32::~CHash32()(auStack_130);
        puStack_180 = puVar12;
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*)(&puStack_160,uStack_158);
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*)(&puStack_178,auStack_170[0]);
        ppppppplVar21 = ppppppplVar21 + 5;
        (*(code *)(*ppppppplVar21)[2])(ppppppplVar21);
      }
      else {
        do {
          while (ppppppplVar21 = ppppppplVar17, ppppppplVar21[4] < pppppplStack_88) {
            ppppppplVar17 = (long *******)ppppppplVar21[1];
            if ((long *******)ppppppplVar21[1] == (long *******)0x0) {
              ppppppplVar21 = ppppppplVar16;
              if (ppppppplVar16 != ppppppplVar19) goto code_r0x01622a0c;
              goto code_r0x01622a28;
            }
          }
          ppppppplVar17 = (long *******)*ppppppplVar21;
          ppppppplVar16 = ppppppplVar21;
        } while ((long *******)*ppppppplVar21 != (long *******)0x0);
        if (ppppppplVar21 == ppppppplVar19) goto code_r0x01622a28;
code_r0x01622a0c:
        if ((pppppplStack_88 < ppppppplVar21[4]) || (ppppppplVar21 == ppppppplVar19))
        goto code_r0x01622a28;
        ppppppplVar21 = ppppppplVar21 + 5;
      }
      lVar13 = *param_2 + uVar18 * 0x40;
      iVar14 = *(int *)(lVar13 + 0x20);
      if (iVar14 == 6) {
        (*(code *)**ppppppplVar21)(ppppppplVar21,lVar13 + 0x28);
      }
      else if (iVar14 == 7) {
        (*(code *)(*ppppppplVar21)[1])(ppppppplVar21,*param_2 + uVar18 * 0x40 + 0x28);
      }
      uVar1 = (int)uVar18 + 1;
      uVar18 = (ulong)uVar1;
    } while (uVar1 < *(uint *)(param_2 + 1));
  }
  return 1;
}

// ==== IInfoBaseMap<unsigned long, CWorldMapMissionInfoList>::DeserializeChild(Aska::ASON::AValue::AMap const*)
// vaddr 0x1523650 | ghidra 0x1623650 | size 532 | symbol _ZN12IInfoBaseMapIm24CWorldMapMissionInfoListE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN12IInfoBaseMapIm24CWorldMapMissionInfoListE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE
          (long *param_1,long *param_2)

{
  uint uVar1;
  undefined *puVar2;
  undefined *puVar3;
  int iVar4;
  long *plVar5;
  long lVar6;
  long *plVar7;
  ulong uVar8;
  long *plVar9;
  long *plVar10;
  undefined *puStack_b8;
  undefined8 *puStack_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined8 *puStack_98;
  undefined8 uStack_90;
  undefined8 uStack_88;
  undefined8 uStack_80;
  undefined8 uStack_78;
  undefined8 uStack_70;
  ulong uStack_68;
  
  plVar10 = param_1 + 8;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CWorldMapMissionInfoList>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CWorldMapMissionInfoList>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CWorldMapMissionInfoList>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CWorldMapMissionInfoList>, void*>*)(param_1 + 7,*plVar10);
  param_1[7] = (long)plVar10;
  param_1[8] = 0;
  param_1[9] = 0;
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0282d54e/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\Info/InfoBase.h"*/,0x1c1,&UNK_027dc58a/*"apParser is null."*/);
    iVar4 = iRam0000000000000008;
  }
  else {
    iVar4 = (int)param_2[1];
  }
  if (iVar4 != 0) {
    uVar8 = 0;
    puVar2 = PTR__ZTV24CWorldMapMissionInfoList_02cbe148 + 0x10;
    puVar3 = PTR__ZTV8InfoBase_02cc49c8 + 0x10;
    do {
      uStack_68 = (**(code **)(*param_1 + 0x20))(param_1,*param_2 + uVar8 * 0x40);
      plVar5 = (long *)param_1[8];
      plVar7 = plVar10;
      if ((long *)param_1[8] == (long *)0x0) {
code_r0x01623780:
        uStack_a8 = 0;
        uStack_a0 = 0;
        uStack_90 = 0;
        uStack_88 = 0;
        uStack_78 = 0;
        uStack_70 = 0;
        uStack_80 = 0;
        puStack_b8 = puVar2;
        puStack_b0 = &uStack_a8;
        puStack_98 = &uStack_90;
        lVar6 = std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned long, CWorldMapMissionInfoList>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CWorldMapMissionInfoList>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CWorldMapMissionInfoList>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CWorldMapMissionInfoList>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CWorldMapMissionInfoList>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned long, unsigned long&, CWorldMapMissionInfoList>(unsigned long const&, unsigned long&, CWorldMapMissionInfoList&&)(param_1 + 7,&uStack_68,&uStack_68,&puStack_b8);
        std::__ndk1::__vector_base<CWorldMapMissionElementInfo, Framework::CSTLAllocator<CWorldMapMissionElementInfo, Framework::CSTLVectorAllocatorInf> >::~__vector_base()(&uStack_80);
        puStack_b8 = puVar3;
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*)(&puStack_98,uStack_90);
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*)(&puStack_b0,uStack_a8);
        plVar9 = (long *)(lVar6 + 0x28);
        (**(code **)(*plVar9 + 0x10))(plVar9);
      }
      else {
        do {
          while (plVar9 = plVar5, (ulong)plVar9[4] < uStack_68) {
            plVar5 = (long *)plVar9[1];
            if ((long *)plVar9[1] == (long *)0x0) {
              plVar9 = plVar7;
              if (plVar7 != plVar10) goto code_r0x01623764;
              goto code_r0x01623780;
            }
          }
          plVar5 = (long *)*plVar9;
          plVar7 = plVar9;
        } while ((long *)*plVar9 != (long *)0x0);
        if (plVar9 == plVar10) goto code_r0x01623780;
code_r0x01623764:
        if ((uStack_68 < (ulong)plVar9[4]) || (plVar9 == plVar10)) goto code_r0x01623780;
        plVar9 = plVar9 + 5;
      }
      lVar6 = *param_2 + uVar8 * 0x40;
      iVar4 = *(int *)(lVar6 + 0x20);
      if (iVar4 == 6) {
        (**(code **)*plVar9)(plVar9,lVar6 + 0x28);
      }
      else if (iVar4 == 7) {
        (**(code **)(*plVar9 + 8))(plVar9,*param_2 + uVar8 * 0x40 + 0x28);
      }
      uVar1 = (int)uVar8 + 1;
      uVar8 = (ulong)uVar1;
    } while (uVar1 < *(uint *)(param_2 + 1));
  }
  return 1;
}

// ==== IInfoBaseMap<unsigned long, _CAttachedGearInfoList>::DeserializeChild(Aska::ASON::AValue::AMap const*)
// vaddr 0x1527cfc | ghidra 0x1627cfc | size 532 | symbol _ZN12IInfoBaseMapIm22_CAttachedGearInfoListE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN12IInfoBaseMapIm22_CAttachedGearInfoListE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE
          (long *param_1,long *param_2)

{
  uint uVar1;
  undefined *puVar2;
  undefined *puVar3;
  int iVar4;
  long *plVar5;
  long lVar6;
  long *plVar7;
  ulong uVar8;
  long *plVar9;
  long *plVar10;
  undefined *puStack_b8;
  undefined8 *puStack_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined8 *puStack_98;
  undefined8 uStack_90;
  undefined8 uStack_88;
  undefined8 uStack_80;
  undefined8 uStack_78;
  undefined8 uStack_70;
  ulong uStack_68;
  
  plVar10 = param_1 + 8;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, _CAttachedGearInfoList>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, _CAttachedGearInfoList>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, _CAttachedGearInfoList>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, _CAttachedGearInfoList>, void*>*)(param_1 + 7,*plVar10);
  param_1[7] = (long)plVar10;
  param_1[8] = 0;
  param_1[9] = 0;
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0282d54e/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\Info/InfoBase.h"*/,0x1c1,&UNK_027dc58a/*"apParser is null."*/);
    iVar4 = iRam0000000000000008;
  }
  else {
    iVar4 = (int)param_2[1];
  }
  if (iVar4 != 0) {
    uVar8 = 0;
    puVar2 = PTR__ZTV22_CAttachedGearInfoList_02cbdeb0 + 0x10;
    puVar3 = PTR__ZTV8InfoBase_02cc49c8 + 0x10;
    do {
      uStack_68 = (**(code **)(*param_1 + 0x20))(param_1,*param_2 + uVar8 * 0x40);
      plVar5 = (long *)param_1[8];
      plVar7 = plVar10;
      if ((long *)param_1[8] == (long *)0x0) {
code_r0x01627e2c:
        uStack_a8 = 0;
        uStack_a0 = 0;
        uStack_90 = 0;
        uStack_88 = 0;
        uStack_78 = 0;
        uStack_70 = 0;
        uStack_80 = 0;
        puStack_b8 = puVar2;
        puStack_b0 = &uStack_a8;
        puStack_98 = &uStack_90;
        lVar6 = std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned long, _CAttachedGearInfoList>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, _CAttachedGearInfoList>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, _CAttachedGearInfoList>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, _CAttachedGearInfoList>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, _CAttachedGearInfoList>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned long, unsigned long&, _CAttachedGearInfoList>(unsigned long const&, unsigned long&, _CAttachedGearInfoList&&)(param_1 + 7,&uStack_68,&uStack_68,&puStack_b8);
        std::__ndk1::__vector_base<CAttachedGearInfo, Framework::CSTLAllocator<CAttachedGearInfo, Framework::CSTLVectorAllocatorInf> >::~__vector_base()(&uStack_80);
        puStack_b8 = puVar3;
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*)(&puStack_98,uStack_90);
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*)(&puStack_b0,uStack_a8);
        plVar9 = (long *)(lVar6 + 0x28);
        (**(code **)(*plVar9 + 0x10))(plVar9);
      }
      else {
        do {
          while (plVar9 = plVar5, (ulong)plVar9[4] < uStack_68) {
            plVar5 = (long *)plVar9[1];
            if ((long *)plVar9[1] == (long *)0x0) {
              plVar9 = plVar7;
              if (plVar7 != plVar10) goto code_r0x01627e10;
              goto code_r0x01627e2c;
            }
          }
          plVar5 = (long *)*plVar9;
          plVar7 = plVar9;
        } while ((long *)*plVar9 != (long *)0x0);
        if (plVar9 == plVar10) goto code_r0x01627e2c;
code_r0x01627e10:
        if ((uStack_68 < (ulong)plVar9[4]) || (plVar9 == plVar10)) goto code_r0x01627e2c;
        plVar9 = plVar9 + 5;
      }
      lVar6 = *param_2 + uVar8 * 0x40;
      iVar4 = *(int *)(lVar6 + 0x20);
      if (iVar4 == 6) {
        (**(code **)*plVar9)(plVar9,lVar6 + 0x28);
      }
      else if (iVar4 == 7) {
        (**(code **)(*plVar9 + 8))(plVar9,*param_2 + uVar8 * 0x40 + 0x28);
      }
      uVar1 = (int)uVar8 + 1;
      uVar8 = (ulong)uVar1;
    } while (uVar1 < *(uint *)(param_2 + 1));
  }
  return 1;
}

// ==== IInfoBaseMap<unsigned long, InheritItemInfo>::DeserializeChild(Aska::ASON::AValue::AMap const*)
// vaddr 0x15282a8 | ghidra 0x16282a8 | size 932 | symbol _ZN12IInfoBaseMapIm15InheritItemInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Type propagation algorithm not settling */

undefined8
_ZN12IInfoBaseMapIm15InheritItemInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE
          (long *param_1,long *param_2)

{
  uint uVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined *puVar5;
  undefined *puVar6;
  undefined *puVar7;
  long lVar8;
  int iVar9;
  long *plVar10;
  long *******ppppppplVar11;
  long *******ppppppplVar12;
  ulong uVar13;
  long *******ppppppplVar14;
  long *******ppppppplVar15;
  long *******ppppppplVar16;
  undefined *puStack_120;
  undefined8 *puStack_118;
  undefined8 auStack_110 [2];
  undefined8 *puStack_100;
  undefined8 uStack_f8;
  undefined8 uStack_f0;
  undefined *puStack_e8;
  undefined8 uStack_e0;
  undefined1 uStack_d8;
  undefined1 auStack_d0 [24];
  undefined *puStack_b8;
  undefined8 uStack_b0;
  undefined1 uStack_a8;
  undefined1 auStack_a0 [24];
  long ******pppppplStack_88;
  long *******appppppplStack_80 [3];
  long *******ppppppplStack_68;
  
  ppppppplVar16 = (long *******)(param_1 + 8);
  plVar10 = param_1 + 7;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, InheritItemInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, InheritItemInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, InheritItemInfo>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, InheritItemInfo>, void*>*)(plVar10,*ppppppplVar16);
  param_1[7] = (long)ppppppplVar16;
  param_1[8] = 0;
  param_1[9] = 0;
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0282d54e/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\Info/InfoBase.h"*/,0x1c1,&UNK_027dc58a/*"apParser is null."*/);
    iVar9 = iRam0000000000000008;
  }
  else {
    iVar9 = (int)param_2[1];
  }
  if (iVar9 != 0) {
    puVar2 = PTR__ZTV15InheritItemInfo_02cc2698 + 0x10;
    puVar3 = PTR__ZTV22CParameterPropertyBaseILj14EE_02cb9db0 + 0x10;
    puVar4 = PTR__ZTV23CParameterPropertyValueIjLj14E18CPropertyConverterE_02cbaef8 + 0x10;
    puVar5 = PTR__ZTV22CParameterPropertyBaseILj15EE_02cc0790 + 0x10;
    puVar6 = PTR__ZTV23CParameterPropertyValueIjLj15E18CPropertyConverterE_02cc1598 + 0x10;
    uVar13 = 0;
    puVar7 = PTR__ZTV8InfoBase_02cc49c8 + 0x10;
    do {
      pppppplStack_88 =
           (long ******)(**(code **)(*param_1 + 0x20))(param_1,*param_2 + uVar13 * 0x40);
      ppppppplVar12 = (long *******)param_1[8];
      ppppppplVar11 = ppppppplVar16;
      if ((long *******)param_1[8] == (long *******)0x0) {
code_r0x01628424:
        memset(auStack_110,0,0x88);
        uStack_f8 = 0;
        uStack_f0 = 0;
        uStack_d8 = 0;
        uStack_e0 = 0;
        puStack_120 = puVar2;
        puStack_118 = auStack_110;
        puStack_100 = &uStack_f8;
        puStack_e8 = puVar3;
        Framework::CHash32::CHash32()(auStack_d0);
        uStack_a8 = 0;
        uStack_b0 = 0;
        puStack_e8 = puVar4;
        puStack_b8 = puVar5;
        Framework::CHash32::CHash32()(auStack_a0);
        ppppppplVar12 = (long *******)*ppppppplVar16;
        if ((long *******)*ppppppplVar16 == (long *******)0x0) {
          ppppppplVar15 = (long *******)*ppppppplVar16;
          ppppppplVar11 = ppppppplVar16;
          ppppppplVar14 = ppppppplVar16;
        }
        else {
          do {
            while (ppppppplVar11 = ppppppplVar12, ppppppplVar11[4] <= pppppplStack_88) {
              if (pppppplStack_88 <= ppppppplVar11[4]) {
                ppppppplVar15 = ppppppplVar11;
                ppppppplVar14 = (long *******)&ppppppplStack_68;
                goto joined_r0x016284f0;
              }
              ppppppplVar14 = ppppppplVar11 + 1;
              ppppppplVar12 = (long *******)*ppppppplVar14;
              if ((long *******)*ppppppplVar14 == (long *******)0x0) {
                ppppppplVar15 = (long *******)*ppppppplVar14;
                goto joined_r0x016284f0;
              }
            }
            ppppppplVar12 = (long *******)*ppppppplVar11;
          } while ((long *******)*ppppppplVar11 != (long *******)0x0);
          ppppppplVar15 = (long *******)*ppppppplVar11;
          ppppppplVar14 = ppppppplVar11;
        }
joined_r0x016284f0:
        ppppppplStack_68 = ppppppplVar11;
        if (ppppppplVar15 == (long *******)0x0) {
          puStack_b8 = puVar6;
          std::__ndk1::unique_ptr<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, InheritItemInfo>, void*>, std::__ndk1::__tree_node_destructor<Framework::CSTLAllocator<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, InheritItemInfo>, void*>, Framework::CSTLMapAllocatorInf> > > std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, InheritItemInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, InheritItemInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, InheritItemInfo>, Framework::CSTLMapAllocatorInf> >::__construct_node<unsigned long&, InheritItemInfo>(unsigned long&, InheritItemInfo&&)(appppppplStack_80,plVar10,&pppppplStack_88,&puStack_120);
          *appppppplStack_80[0] = (long ******)0x0;
          appppppplStack_80[0][1] = (long ******)0x0;
          appppppplStack_80[0][2] = (long ******)ppppppplVar11;
          *ppppppplVar14 = (long ******)appppppplStack_80[0];
          ppppppplVar12 = appppppplStack_80[0];
          if (*(long *)*plVar10 != 0) {
            *plVar10 = *(long *)*plVar10;
            ppppppplVar12 = (long *******)*ppppppplVar14;
          }
          void std::__ndk1::__tree_balance_after_insert<std::__ndk1::__tree_node_base<void*>*>(std::__ndk1::__tree_node_base<void*>*, std::__ndk1::__tree_node_base<void*>*)(param_1[8],ppppppplVar12);
          param_1[9] = param_1[9] + 1;
          ppppppplVar15 = appppppplStack_80[0];
        }
        puStack_120 = PTR__ZTV15InheritItemInfo_02cc2698 + 0x10;
        puStack_b8 = PTR__ZTV22CParameterPropertyBaseILj15EE_02cc0790 + 0x10;
        Framework::CHash32::~CHash32()(auStack_a0);
        puStack_e8 = PTR__ZTV22CParameterPropertyBaseILj14EE_02cb9db0 + 0x10;
        Framework::CHash32::~CHash32()(auStack_d0);
        puStack_120 = puVar7;
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*)(&puStack_100,uStack_f8);
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*)(&puStack_118,auStack_110[0]);
        ppppppplVar15 = ppppppplVar15 + 5;
        (*(code *)(*ppppppplVar15)[2])(ppppppplVar15);
      }
      else {
        do {
          while (ppppppplVar15 = ppppppplVar12, ppppppplVar15[4] < pppppplStack_88) {
            ppppppplVar12 = (long *******)ppppppplVar15[1];
            if ((long *******)ppppppplVar15[1] == (long *******)0x0) {
              ppppppplVar15 = ppppppplVar11;
              if (ppppppplVar11 != ppppppplVar16) goto code_r0x01628408;
              goto code_r0x01628424;
            }
          }
          ppppppplVar12 = (long *******)*ppppppplVar15;
          ppppppplVar11 = ppppppplVar15;
        } while ((long *******)*ppppppplVar15 != (long *******)0x0);
        if (ppppppplVar15 == ppppppplVar16) goto code_r0x01628424;
code_r0x01628408:
        if ((pppppplStack_88 < ppppppplVar15[4]) || (ppppppplVar15 == ppppppplVar16))
        goto code_r0x01628424;
        ppppppplVar15 = ppppppplVar15 + 5;
      }
      lVar8 = *param_2 + uVar13 * 0x40;
      iVar9 = *(int *)(lVar8 + 0x20);
      if (iVar9 == 6) {
        (*(code *)**ppppppplVar15)(ppppppplVar15,lVar8 + 0x28);
      }
      else if (iVar9 == 7) {
        (*(code *)(*ppppppplVar15)[1])(ppppppplVar15,*param_2 + uVar13 * 0x40 + 0x28);
      }
      uVar1 = (int)uVar13 + 1;
      uVar13 = (ulong)uVar1;
    } while (uVar1 < *(uint *)(param_2 + 1));
  }
  return 1;
}

// ==== IInfoBaseMap<unsigned long, CMissionDropInfoList>::DeserializeChild(Aska::ASON::AValue::AMap const*)
// vaddr 0x1529f24 | ghidra 0x1629f24 | size 532 | symbol _ZN12IInfoBaseMapIm20CMissionDropInfoListE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN12IInfoBaseMapIm20CMissionDropInfoListE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE
          (long *param_1,long *param_2)

{
  uint uVar1;
  undefined *puVar2;
  undefined *puVar3;
  int iVar4;
  long *plVar5;
  long lVar6;
  long *plVar7;
  ulong uVar8;
  long *plVar9;
  long *plVar10;
  undefined *puStack_b8;
  undefined8 *puStack_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined8 *puStack_98;
  undefined8 uStack_90;
  undefined8 uStack_88;
  undefined8 uStack_80;
  undefined8 uStack_78;
  undefined8 uStack_70;
  ulong uStack_68;
  
  plVar10 = param_1 + 8;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CMissionDropInfoList>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CMissionDropInfoList>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CMissionDropInfoList>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CMissionDropInfoList>, void*>*)(param_1 + 7,*plVar10);
  param_1[7] = (long)plVar10;
  param_1[8] = 0;
  param_1[9] = 0;
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0282d54e/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\Info/InfoBase.h"*/,0x1c1,&UNK_027dc58a/*"apParser is null."*/);
    iVar4 = iRam0000000000000008;
  }
  else {
    iVar4 = (int)param_2[1];
  }
  if (iVar4 != 0) {
    uVar8 = 0;
    puVar2 = PTR__ZTV20CMissionDropInfoList_02cb7040 + 0x10;
    puVar3 = PTR__ZTV8InfoBase_02cc49c8 + 0x10;
    do {
      uStack_68 = (**(code **)(*param_1 + 0x20))(param_1,*param_2 + uVar8 * 0x40);
      plVar5 = (long *)param_1[8];
      plVar7 = plVar10;
      if ((long *)param_1[8] == (long *)0x0) {
code_r0x0162a054:
        uStack_a8 = 0;
        uStack_a0 = 0;
        uStack_90 = 0;
        uStack_88 = 0;
        uStack_78 = 0;
        uStack_70 = 0;
        uStack_80 = 0;
        puStack_b8 = puVar2;
        puStack_b0 = &uStack_a8;
        puStack_98 = &uStack_90;
        lVar6 = std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned long, CMissionDropInfoList>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CMissionDropInfoList>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CMissionDropInfoList>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CMissionDropInfoList>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CMissionDropInfoList>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned long, unsigned long&, CMissionDropInfoList>(unsigned long const&, unsigned long&, CMissionDropInfoList&&)(param_1 + 7,&uStack_68,&uStack_68,&puStack_b8);
        std::__ndk1::__vector_base<CMissionDropInfo, Framework::CSTLAllocator<CMissionDropInfo, Framework::CSTLVectorAllocatorInf> >::~__vector_base()(&uStack_80);
        puStack_b8 = puVar3;
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*)(&puStack_98,uStack_90);
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*)(&puStack_b0,uStack_a8);
        plVar9 = (long *)(lVar6 + 0x28);
        (**(code **)(*plVar9 + 0x10))(plVar9);
      }
      else {
        do {
          while (plVar9 = plVar5, (ulong)plVar9[4] < uStack_68) {
            plVar5 = (long *)plVar9[1];
            if ((long *)plVar9[1] == (long *)0x0) {
              plVar9 = plVar7;
              if (plVar7 != plVar10) goto code_r0x0162a038;
              goto code_r0x0162a054;
            }
          }
          plVar5 = (long *)*plVar9;
          plVar7 = plVar9;
        } while ((long *)*plVar9 != (long *)0x0);
        if (plVar9 == plVar10) goto code_r0x0162a054;
code_r0x0162a038:
        if ((uStack_68 < (ulong)plVar9[4]) || (plVar9 == plVar10)) goto code_r0x0162a054;
        plVar9 = plVar9 + 5;
      }
      lVar6 = *param_2 + uVar8 * 0x40;
      iVar4 = *(int *)(lVar6 + 0x20);
      if (iVar4 == 6) {
        (**(code **)*plVar9)(plVar9,lVar6 + 0x28);
      }
      else if (iVar4 == 7) {
        (**(code **)(*plVar9 + 8))(plVar9,*param_2 + uVar8 * 0x40 + 0x28);
      }
      uVar1 = (int)uVar8 + 1;
      uVar8 = (ulong)uVar1;
    } while (uVar1 < *(uint *)(param_2 + 1));
  }
  return 1;
}

// ==== IInfoBaseMap<unsigned long, CMissionResultCharacterInfo>::DeserializeChild(Aska::ASON::AValue::AMap const*)
// vaddr 0x152a648 | ghidra 0x162a648 | size 1132 | symbol _ZN12IInfoBaseMapIm27CMissionResultCharacterInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Type propagation algorithm not settling */

undefined8
_ZN12IInfoBaseMapIm27CMissionResultCharacterInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE
          (long *param_1,long *param_2)

{
  uint uVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined *puVar5;
  undefined *puVar6;
  undefined *puVar7;
  undefined *puVar8;
  undefined *puVar9;
  undefined *puVar10;
  undefined *puVar11;
  long lVar12;
  int iVar13;
  long *plVar14;
  long *******ppppppplVar15;
  long *******ppppppplVar16;
  ulong uVar17;
  long *******ppppppplVar18;
  long *******ppppppplVar19;
  long *******ppppppplVar20;
  undefined *puStack_180;
  undefined8 *puStack_178;
  undefined8 auStack_170 [2];
  undefined8 *puStack_160;
  undefined8 uStack_158;
  undefined8 uStack_150;
  undefined *puStack_148;
  undefined8 uStack_140;
  undefined1 uStack_138;
  undefined1 auStack_130 [24];
  undefined *puStack_118;
  undefined8 uStack_110;
  undefined1 uStack_108;
  undefined1 auStack_100 [24];
  undefined *puStack_e8;
  undefined8 uStack_e0;
  undefined1 uStack_d8;
  undefined1 auStack_d0 [24];
  undefined *puStack_b8;
  undefined8 uStack_b0;
  undefined1 uStack_a8;
  undefined1 auStack_a0 [24];
  long ******pppppplStack_88;
  long *******appppppplStack_80 [3];
  long *******ppppppplStack_68;
  
  ppppppplVar18 = (long *******)(param_1 + 8);
  plVar14 = param_1 + 7;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CMissionResultCharacterInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CMissionResultCharacterInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CMissionResultCharacterInfo>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CMissionResultCharacterInfo>, void*>*)(plVar14,*ppppppplVar18);
  param_1[7] = (long)ppppppplVar18;
  param_1[8] = 0;
  param_1[9] = 0;
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0282d54e/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\Info/InfoBase.h"*/,0x1c1,&UNK_027dc58a/*"apParser is null."*/);
    iVar13 = iRam0000000000000008;
  }
  else {
    iVar13 = (int)param_2[1];
  }
  if (iVar13 != 0) {
    puVar2 = PTR__ZTV27CMissionResultCharacterInfo_02cb79b0 + 0x10;
    puVar3 = PTR__ZTV22CParameterPropertyBaseILj162EE_02cc4740 + 0x10;
    puVar4 = PTR__ZTV23CParameterPropertyValueIjLj162E18CPropertyConverterE_02cba0b8 + 0x10;
    puVar5 = PTR__ZTV22CParameterPropertyBaseILj163EE_02cbb018 + 0x10;
    puVar6 = PTR__ZTV23CParameterPropertyValueIjLj163E18CPropertyConverterE_02cbf990 + 0x10;
    puVar7 = PTR__ZTV22CParameterPropertyBaseILj164EE_02cb6d78 + 0x10;
    puVar8 = PTR__ZTV23CParameterPropertyValueIjLj164E18CPropertyConverterE_02cb6b60 + 0x10;
    puVar9 = PTR__ZTV22CParameterPropertyBaseILj165EE_02cbe958 + 0x10;
    puVar10 = PTR__ZTV23CParameterPropertyValueIjLj165E18CPropertyConverterE_02cbe168 + 0x10;
    uVar17 = 0;
    puVar11 = PTR__ZTV8InfoBase_02cc49c8 + 0x10;
    do {
      pppppplStack_88 =
           (long ******)(**(code **)(*param_1 + 0x20))(param_1,*param_2 + uVar17 * 0x40);
      ppppppplVar16 = (long *******)param_1[8];
      ppppppplVar15 = ppppppplVar18;
      if ((long *******)param_1[8] == (long *******)0x0) {
code_r0x0162a818:
        memset(auStack_170,0,0xe8);
        uStack_158 = 0;
        uStack_150 = 0;
        uStack_138 = 0;
        uStack_140 = 0;
        puStack_180 = puVar2;
        puStack_178 = auStack_170;
        puStack_160 = &uStack_158;
        puStack_148 = puVar3;
        Framework::CHash32::CHash32()(auStack_130);
        uStack_108 = 0;
        uStack_110 = 0;
        puStack_148 = puVar4;
        puStack_118 = puVar5;
        Framework::CHash32::CHash32()(auStack_100);
        uStack_d8 = 0;
        uStack_e0 = 0;
        puStack_118 = puVar6;
        puStack_e8 = puVar7;
        Framework::CHash32::CHash32()(auStack_d0);
        uStack_a8 = 0;
        uStack_b0 = 0;
        puStack_e8 = puVar8;
        puStack_b8 = puVar9;
        Framework::CHash32::CHash32()(auStack_a0);
        ppppppplVar16 = (long *******)*ppppppplVar18;
        if ((long *******)*ppppppplVar18 == (long *******)0x0) {
          ppppppplVar20 = (long *******)*ppppppplVar18;
          ppppppplVar15 = ppppppplVar18;
          ppppppplVar19 = ppppppplVar18;
        }
        else {
          do {
            while (ppppppplVar15 = ppppppplVar16, ppppppplVar15[4] <= pppppplStack_88) {
              if (pppppplStack_88 <= ppppppplVar15[4]) {
                ppppppplVar20 = ppppppplVar15;
                ppppppplVar19 = (long *******)&ppppppplStack_68;
                goto joined_r0x0162a924;
              }
              ppppppplVar19 = ppppppplVar15 + 1;
              ppppppplVar16 = (long *******)*ppppppplVar19;
              if ((long *******)*ppppppplVar19 == (long *******)0x0) {
                ppppppplVar20 = (long *******)*ppppppplVar19;
                goto joined_r0x0162a924;
              }
            }
            ppppppplVar16 = (long *******)*ppppppplVar15;
          } while ((long *******)*ppppppplVar15 != (long *******)0x0);
          ppppppplVar20 = (long *******)*ppppppplVar15;
          ppppppplVar19 = ppppppplVar15;
        }
joined_r0x0162a924:
        ppppppplStack_68 = ppppppplVar15;
        if (ppppppplVar20 == (long *******)0x0) {
          puStack_b8 = puVar10;
          std::__ndk1::unique_ptr<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CMissionResultCharacterInfo>, void*>, std::__ndk1::__tree_node_destructor<Framework::CSTLAllocator<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CMissionResultCharacterInfo>, void*>, Framework::CSTLMapAllocatorInf> > > std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CMissionResultCharacterInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CMissionResultCharacterInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CMissionResultCharacterInfo>, Framework::CSTLMapAllocatorInf> >::__construct_node<unsigned long&, CMissionResultCharacterInfo>(unsigned long&, CMissionResultCharacterInfo&&)(appppppplStack_80,plVar14,&pppppplStack_88,&puStack_180);
          *appppppplStack_80[0] = (long ******)0x0;
          appppppplStack_80[0][1] = (long ******)0x0;
          appppppplStack_80[0][2] = (long ******)ppppppplVar15;
          *ppppppplVar19 = (long ******)appppppplStack_80[0];
          ppppppplVar16 = appppppplStack_80[0];
          if (*(long *)*plVar14 != 0) {
            *plVar14 = *(long *)*plVar14;
            ppppppplVar16 = (long *******)*ppppppplVar19;
          }
          void std::__ndk1::__tree_balance_after_insert<std::__ndk1::__tree_node_base<void*>*>(std::__ndk1::__tree_node_base<void*>*, std::__ndk1::__tree_node_base<void*>*)(param_1[8],ppppppplVar16);
          param_1[9] = param_1[9] + 1;
          ppppppplVar20 = appppppplStack_80[0];
        }
        puStack_180 = PTR__ZTV27CMissionResultCharacterInfo_02cb79b0 + 0x10;
        puStack_b8 = PTR__ZTV22CParameterPropertyBaseILj165EE_02cbe958 + 0x10;
        Framework::CHash32::~CHash32()(auStack_a0);
        puStack_e8 = PTR__ZTV22CParameterPropertyBaseILj164EE_02cb6d78 + 0x10;
        Framework::CHash32::~CHash32()(auStack_d0);
        puStack_118 = PTR__ZTV22CParameterPropertyBaseILj163EE_02cbb018 + 0x10;
        Framework::CHash32::~CHash32()(auStack_100);
        puStack_148 = PTR__ZTV22CParameterPropertyBaseILj162EE_02cc4740 + 0x10;
        Framework::CHash32::~CHash32()(auStack_130);
        puStack_180 = puVar11;
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*)(&puStack_160,uStack_158);
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*)(&puStack_178,auStack_170[0]);
        ppppppplVar20 = ppppppplVar20 + 5;
        (*(code *)(*ppppppplVar20)[2])(ppppppplVar20);
      }
      else {
        do {
          while (ppppppplVar20 = ppppppplVar16, ppppppplVar20[4] < pppppplStack_88) {
            ppppppplVar16 = (long *******)ppppppplVar20[1];
            if ((long *******)ppppppplVar20[1] == (long *******)0x0) {
              ppppppplVar20 = ppppppplVar15;
              if (ppppppplVar15 != ppppppplVar18) goto code_r0x0162a7fc;
              goto code_r0x0162a818;
            }
          }
          ppppppplVar16 = (long *******)*ppppppplVar20;
          ppppppplVar15 = ppppppplVar20;
        } while ((long *******)*ppppppplVar20 != (long *******)0x0);
        if (ppppppplVar20 == ppppppplVar18) goto code_r0x0162a818;
code_r0x0162a7fc:
        if ((pppppplStack_88 < ppppppplVar20[4]) || (ppppppplVar20 == ppppppplVar18))
        goto code_r0x0162a818;
        ppppppplVar20 = ppppppplVar20 + 5;
      }
      lVar12 = *param_2 + uVar17 * 0x40;
      iVar13 = *(int *)(lVar12 + 0x20);
      if (iVar13 == 6) {
        (*(code *)**ppppppplVar20)(ppppppplVar20,lVar12 + 0x28);
      }
      else if (iVar13 == 7) {
        (*(code *)(*ppppppplVar20)[1])(ppppppplVar20,*param_2 + uVar17 * 0x40 + 0x28);
      }
      uVar1 = (int)uVar17 + 1;
      uVar17 = (ulong)uVar1;
    } while (uVar1 < *(uint *)(param_2 + 1));
  }
  return 1;
}

// ==== IInfoBaseMap<unsigned long, CMissionResultCharacterFavorInfo>::DeserializeChild(Aska::ASON::AValue::AMap const*)
// vaddr 0x152cc68 | ghidra 0x162cc68 | size 1096 | symbol _ZN12IInfoBaseMapIm32CMissionResultCharacterFavorInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Type propagation algorithm not settling */

undefined8
_ZN12IInfoBaseMapIm32CMissionResultCharacterFavorInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE
          (long *param_1,long *param_2)

{
  uint uVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined *puVar5;
  undefined *puVar6;
  undefined *puVar7;
  undefined *puVar8;
  undefined *puVar9;
  undefined *puVar10;
  undefined *puVar11;
  undefined *puVar12;
  undefined *puVar13;
  undefined *puVar14;
  long lVar15;
  int iVar16;
  long *plVar17;
  long *******ppppppplVar18;
  long *******ppppppplVar19;
  ulong uVar20;
  long *******ppppppplVar21;
  long *******ppppppplVar22;
  long *******ppppppplVar23;
  undefined *puStack_1f0;
  undefined1 *puStack_1e8;
  undefined1 auStack_1e0 [16];
  undefined8 *puStack_1d0;
  undefined8 uStack_1c8;
  undefined8 uStack_1c0;
  undefined *puStack_1b8;
  undefined8 uStack_1b0;
  undefined1 uStack_1a8;
  undefined1 auStack_1a0 [24];
  undefined *puStack_188;
  undefined8 uStack_180;
  undefined1 uStack_178;
  undefined1 auStack_170 [24];
  undefined *puStack_158;
  undefined8 uStack_150;
  undefined1 uStack_148;
  undefined1 auStack_140 [24];
  undefined *puStack_128;
  undefined8 uStack_120;
  undefined1 uStack_118;
  undefined1 auStack_110 [24];
  undefined *puStack_f8;
  undefined8 uStack_f0;
  undefined1 uStack_e8;
  undefined1 auStack_e0 [24];
  undefined *puStack_c8;
  undefined8 uStack_c0;
  undefined1 uStack_b8;
  undefined1 auStack_b0 [16];
  undefined8 uStack_a0;
  undefined8 uStack_98;
  undefined8 uStack_90;
  long ******pppppplStack_88;
  long *******appppppplStack_80 [3];
  long *******ppppppplStack_68;
  
  ppppppplVar21 = (long *******)(param_1 + 8);
  plVar17 = param_1 + 7;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CMissionResultCharacterFavorInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CMissionResultCharacterFavorInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CMissionResultCharacterFavorInfo>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CMissionResultCharacterFavorInfo>, void*>*)(plVar17,*ppppppplVar21);
  param_1[7] = (long)ppppppplVar21;
  param_1[8] = 0;
  param_1[9] = 0;
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0282d54e/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\Info/InfoBase.h"*/,0x1c1,&UNK_027dc58a/*"apParser is null."*/);
    iVar16 = iRam0000000000000008;
  }
  else {
    iVar16 = (int)param_2[1];
  }
  if (iVar16 != 0) {
    puVar2 = PTR__ZTV32CMissionResultCharacterFavorInfo_02cc35b0 + 0x10;
    puVar3 = PTR__ZTV22CParameterPropertyBaseILj196EE_02cbebf0 + 0x10;
    puVar4 = PTR__ZTV23CParameterPropertyValueIjLj196E18CPropertyConverterE_02cbf4b8 + 0x10;
    puVar5 = PTR__ZTV22CParameterPropertyBaseILj197EE_02cb7220 + 0x10;
    puVar6 = PTR__ZTV23CParameterPropertyValueIjLj197E18CPropertyConverterE_02cba1f8 + 0x10;
    puVar7 = PTR__ZTV22CParameterPropertyBaseILj198EE_02cc0c68 + 0x10;
    puVar8 = PTR__ZTV23CParameterPropertyValueIjLj198E18CPropertyConverterE_02cb7da0 + 0x10;
    puVar9 = PTR__ZTV22CParameterPropertyBaseILj199EE_02cb76f8 + 0x10;
    puVar10 = PTR__ZTV23CParameterPropertyValueIjLj199E18CPropertyConverterE_02cbde70 + 0x10;
    puVar11 = PTR__ZTV22CParameterPropertyBaseILj200EE_02cbc5b0 + 0x10;
    puVar12 = PTR__ZTV23CParameterPropertyValueIjLj200E18CPropertyConverterE_02cbf2d0 + 0x10;
    uVar20 = 0;
    puVar13 = PTR__ZTV22CParameterPropertyBaseILj201EE_02cc3250 + 0x10;
    puVar14 = PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj201EE_02cb6ee0
              + 0x10;
    do {
      pppppplStack_88 =
           (long ******)(**(code **)(*param_1 + 0x20))(param_1,*param_2 + uVar20 * 0x40);
      ppppppplVar19 = (long *******)param_1[8];
      ppppppplVar18 = ppppppplVar21;
      if ((long *******)param_1[8] == (long *******)0x0) {
code_r0x0162ce6c:
        memset(auStack_1e0,0,0x158);
        uStack_1c8 = 0;
        uStack_1c0 = 0;
        uStack_1a8 = 0;
        uStack_1b0 = 0;
        puStack_1f0 = puVar2;
        puStack_1e8 = auStack_1e0;
        puStack_1d0 = &uStack_1c8;
        puStack_1b8 = puVar3;
        Framework::CHash32::CHash32()(auStack_1a0);
        uStack_178 = 0;
        uStack_180 = 0;
        puStack_1b8 = puVar4;
        puStack_188 = puVar5;
        Framework::CHash32::CHash32()(auStack_170);
        uStack_148 = 0;
        uStack_150 = 0;
        puStack_188 = puVar6;
        puStack_158 = puVar7;
        Framework::CHash32::CHash32()(auStack_140);
        uStack_118 = 0;
        uStack_120 = 0;
        puStack_158 = puVar8;
        puStack_128 = puVar9;
        Framework::CHash32::CHash32()(auStack_110);
        uStack_e8 = 0;
        uStack_f0 = 0;
        puStack_128 = puVar10;
        puStack_f8 = puVar11;
        Framework::CHash32::CHash32()(auStack_e0);
        uStack_b8 = 0;
        uStack_c0 = 0;
        puStack_f8 = puVar12;
        puStack_c8 = puVar13;
        Framework::CHash32::CHash32()(auStack_b0);
        uStack_98 = 0;
        uStack_90 = 0;
        uStack_a0 = 0;
        ppppppplVar19 = (long *******)*ppppppplVar21;
        if ((long *******)*ppppppplVar21 == (long *******)0x0) {
          ppppppplVar23 = (long *******)*ppppppplVar21;
          ppppppplVar18 = ppppppplVar21;
          ppppppplVar22 = ppppppplVar21;
        }
        else {
          do {
            while (ppppppplVar18 = ppppppplVar19, ppppppplVar18[4] <= pppppplStack_88) {
              if (pppppplStack_88 <= ppppppplVar18[4]) {
                ppppppplVar23 = ppppppplVar18;
                ppppppplVar22 = (long *******)&ppppppplStack_68;
                goto joined_r0x0162cfac;
              }
              ppppppplVar22 = ppppppplVar18 + 1;
              ppppppplVar19 = (long *******)*ppppppplVar22;
              if ((long *******)*ppppppplVar22 == (long *******)0x0) {
                ppppppplVar23 = (long *******)*ppppppplVar22;
                goto joined_r0x0162cfac;
              }
            }
            ppppppplVar19 = (long *******)*ppppppplVar18;
          } while ((long *******)*ppppppplVar18 != (long *******)0x0);
          ppppppplVar23 = (long *******)*ppppppplVar18;
          ppppppplVar22 = ppppppplVar18;
        }
joined_r0x0162cfac:
        puStack_c8 = puVar14;
        ppppppplStack_68 = ppppppplVar18;
        if (ppppppplVar23 == (long *******)0x0) {
          std::__ndk1::unique_ptr<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CMissionResultCharacterFavorInfo>, void*>, std::__ndk1::__tree_node_destructor<Framework::CSTLAllocator<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CMissionResultCharacterFavorInfo>, void*>, Framework::CSTLMapAllocatorInf> > > std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CMissionResultCharacterFavorInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CMissionResultCharacterFavorInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CMissionResultCharacterFavorInfo>, Framework::CSTLMapAllocatorInf> >::__construct_node<unsigned long&, CMissionResultCharacterFavorInfo>(unsigned long&, CMissionResultCharacterFavorInfo&&)(appppppplStack_80,plVar17,&pppppplStack_88,&puStack_1f0);
          *appppppplStack_80[0] = (long ******)0x0;
          appppppplStack_80[0][1] = (long ******)0x0;
          appppppplStack_80[0][2] = (long ******)ppppppplVar18;
          *ppppppplVar22 = (long ******)appppppplStack_80[0];
          ppppppplVar19 = appppppplStack_80[0];
          if (*(long *)*plVar17 != 0) {
            *plVar17 = *(long *)*plVar17;
            ppppppplVar19 = (long *******)*ppppppplVar22;
          }
          void std::__ndk1::__tree_balance_after_insert<std::__ndk1::__tree_node_base<void*>*>(std::__ndk1::__tree_node_base<void*>*, std::__ndk1::__tree_node_base<void*>*)(param_1[8],ppppppplVar19);
          param_1[9] = param_1[9] + 1;
          ppppppplVar23 = appppppplStack_80[0];
        }
        CMissionResultCharacterFavorInfo::~CMissionResultCharacterFavorInfo()(&puStack_1f0);
        ppppppplVar23 = ppppppplVar23 + 5;
        (*(code *)(*ppppppplVar23)[2])(ppppppplVar23);
      }
      else {
        do {
          while (ppppppplVar23 = ppppppplVar19, ppppppplVar23[4] < pppppplStack_88) {
            ppppppplVar19 = (long *******)ppppppplVar23[1];
            if ((long *******)ppppppplVar23[1] == (long *******)0x0) {
              ppppppplVar23 = ppppppplVar18;
              if (ppppppplVar18 != ppppppplVar21) goto code_r0x0162ce50;
              goto code_r0x0162ce6c;
            }
          }
          ppppppplVar19 = (long *******)*ppppppplVar23;
          ppppppplVar18 = ppppppplVar23;
        } while ((long *******)*ppppppplVar23 != (long *******)0x0);
        if (ppppppplVar23 == ppppppplVar21) goto code_r0x0162ce6c;
code_r0x0162ce50:
        if ((pppppplStack_88 < ppppppplVar23[4]) || (ppppppplVar23 == ppppppplVar21))
        goto code_r0x0162ce6c;
        ppppppplVar23 = ppppppplVar23 + 5;
      }
      lVar15 = *param_2 + uVar20 * 0x40;
      iVar16 = *(int *)(lVar15 + 0x20);
      if (iVar16 == 6) {
        (*(code *)**ppppppplVar23)(ppppppplVar23,lVar15 + 0x28);
      }
      else if (iVar16 == 7) {
        (*(code *)(*ppppppplVar23)[1])(ppppppplVar23,*param_2 + uVar20 * 0x40 + 0x28);
      }
      uVar1 = (int)uVar20 + 1;
      uVar20 = (ulong)uVar1;
    } while (uVar1 < *(uint *)(param_2 + 1));
  }
  return 1;
}

// ==== IInfoBaseMap<unsigned long, CDeepSpaceCharacterInfo>::DeserializeChild(Aska::ASON::AValue::AMap const*)
// vaddr 0x152dad8 | ghidra 0x162dad8 | size 1028 | symbol _ZN12IInfoBaseMapIm23CDeepSpaceCharacterInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Type propagation algorithm not settling */

undefined8
_ZN12IInfoBaseMapIm23CDeepSpaceCharacterInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE
          (long *param_1,long *param_2)

{
  uint uVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined *puVar5;
  undefined *puVar6;
  undefined *puVar7;
  undefined *puVar8;
  undefined *puVar9;
  long lVar10;
  int iVar11;
  long *plVar12;
  long *******ppppppplVar13;
  long *******ppppppplVar14;
  ulong uVar15;
  long *******ppppppplVar16;
  long *******ppppppplVar17;
  long *******ppppppplVar18;
  undefined *puStack_150;
  undefined8 *puStack_148;
  undefined8 auStack_140 [2];
  undefined8 *puStack_130;
  undefined8 uStack_128;
  undefined8 uStack_120;
  undefined *puStack_118;
  undefined8 uStack_110;
  undefined1 uStack_108;
  undefined1 auStack_100 [24];
  undefined *puStack_e8;
  undefined8 uStack_e0;
  undefined1 uStack_d8;
  undefined1 auStack_d0 [24];
  undefined *puStack_b8;
  undefined8 uStack_b0;
  undefined1 uStack_a8;
  undefined1 auStack_a0 [24];
  long ******pppppplStack_88;
  long *******appppppplStack_80 [3];
  long *******ppppppplStack_68;
  
  ppppppplVar18 = (long *******)(param_1 + 8);
  plVar12 = param_1 + 7;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CDeepSpaceCharacterInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CDeepSpaceCharacterInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CDeepSpaceCharacterInfo>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CDeepSpaceCharacterInfo>, void*>*)(plVar12,*ppppppplVar18);
  param_1[7] = (long)ppppppplVar18;
  param_1[8] = 0;
  param_1[9] = 0;
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0282d54e/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\Info/InfoBase.h"*/,0x1c1,&UNK_027dc58a/*"apParser is null."*/);
    iVar11 = iRam0000000000000008;
  }
  else {
    iVar11 = (int)param_2[1];
  }
  if (iVar11 != 0) {
    puVar2 = PTR__ZTV23CDeepSpaceCharacterInfo_02cc4d20 + 0x10;
    puVar3 = PTR__ZTV22CParameterPropertyBaseILj62EE_02cbaea8 + 0x10;
    puVar4 = PTR__ZTV23CParameterPropertyValueImLj62E18CPropertyConverterE_02cc1078 + 0x10;
    puVar5 = PTR__ZTV22CParameterPropertyBaseILj63EE_02cb6de0 + 0x10;
    puVar6 = PTR__ZTV23CParameterPropertyValueIjLj63E18CPropertyConverterE_02cbd2a0 + 0x10;
    puVar7 = PTR__ZTV22CParameterPropertyBaseILj64EE_02cbbba0 + 0x10;
    puVar8 = PTR__ZTV23CParameterPropertyValueIjLj64E18CPropertyConverterE_02cb96a8 + 0x10;
    uVar15 = 0;
    puVar9 = PTR__ZTV8InfoBase_02cc49c8 + 0x10;
    do {
      pppppplStack_88 =
           (long ******)(**(code **)(*param_1 + 0x20))(param_1,*param_2 + uVar15 * 0x40);
      ppppppplVar14 = (long *******)param_1[8];
      ppppppplVar13 = ppppppplVar18;
      if ((long *******)param_1[8] == (long *******)0x0) {
code_r0x0162dc7c:
        memset(auStack_140,0,0xb8);
        uStack_128 = 0;
        uStack_120 = 0;
        uStack_108 = 0;
        uStack_110 = 0;
        puStack_150 = puVar2;
        puStack_148 = auStack_140;
        puStack_130 = &uStack_128;
        puStack_118 = puVar3;
        Framework::CHash32::CHash32()(auStack_100);
        uStack_d8 = 0;
        uStack_e0 = 0;
        puStack_118 = puVar4;
        puStack_e8 = puVar5;
        Framework::CHash32::CHash32()(auStack_d0);
        uStack_a8 = 0;
        uStack_b0 = 0;
        puStack_e8 = puVar6;
        puStack_b8 = puVar7;
        Framework::CHash32::CHash32()(auStack_a0);
        ppppppplVar14 = (long *******)*ppppppplVar18;
        if ((long *******)*ppppppplVar18 == (long *******)0x0) {
          ppppppplVar17 = (long *******)*ppppppplVar18;
          ppppppplVar13 = ppppppplVar18;
          ppppppplVar16 = ppppppplVar18;
        }
        else {
          do {
            while (ppppppplVar13 = ppppppplVar14, ppppppplVar13[4] <= pppppplStack_88) {
              if (pppppplStack_88 <= ppppppplVar13[4]) {
                ppppppplVar17 = ppppppplVar13;
                ppppppplVar16 = (long *******)&ppppppplStack_68;
                goto joined_r0x0162dd68;
              }
              ppppppplVar16 = ppppppplVar13 + 1;
              ppppppplVar14 = (long *******)*ppppppplVar16;
              if ((long *******)*ppppppplVar16 == (long *******)0x0) {
                ppppppplVar17 = (long *******)*ppppppplVar16;
                goto joined_r0x0162dd68;
              }
            }
            ppppppplVar14 = (long *******)*ppppppplVar13;
          } while ((long *******)*ppppppplVar13 != (long *******)0x0);
          ppppppplVar17 = (long *******)*ppppppplVar13;
          ppppppplVar16 = ppppppplVar13;
        }
joined_r0x0162dd68:
        ppppppplStack_68 = ppppppplVar13;
        if (ppppppplVar17 == (long *******)0x0) {
          puStack_b8 = puVar8;
          std::__ndk1::unique_ptr<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CDeepSpaceCharacterInfo>, void*>, std::__ndk1::__tree_node_destructor<Framework::CSTLAllocator<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CDeepSpaceCharacterInfo>, void*>, Framework::CSTLMapAllocatorInf> > > std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CDeepSpaceCharacterInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CDeepSpaceCharacterInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CDeepSpaceCharacterInfo>, Framework::CSTLMapAllocatorInf> >::__construct_node<unsigned long&, CDeepSpaceCharacterInfo>(unsigned long&, CDeepSpaceCharacterInfo&&)(appppppplStack_80,plVar12,&pppppplStack_88,&puStack_150);
          *appppppplStack_80[0] = (long ******)0x0;
          appppppplStack_80[0][1] = (long ******)0x0;
          appppppplStack_80[0][2] = (long ******)ppppppplVar13;
          *ppppppplVar16 = (long ******)appppppplStack_80[0];
          ppppppplVar14 = appppppplStack_80[0];
          if (*(long *)*plVar12 != 0) {
            *plVar12 = *(long *)*plVar12;
            ppppppplVar14 = (long *******)*ppppppplVar16;
          }
          void std::__ndk1::__tree_balance_after_insert<std::__ndk1::__tree_node_base<void*>*>(std::__ndk1::__tree_node_base<void*>*, std::__ndk1::__tree_node_base<void*>*)(param_1[8],ppppppplVar14);
          param_1[9] = param_1[9] + 1;
          ppppppplVar17 = appppppplStack_80[0];
        }
        puStack_150 = PTR__ZTV23CDeepSpaceCharacterInfo_02cc4d20 + 0x10;
        puStack_b8 = PTR__ZTV22CParameterPropertyBaseILj64EE_02cbbba0 + 0x10;
        Framework::CHash32::~CHash32()(auStack_a0);
        puStack_e8 = PTR__ZTV22CParameterPropertyBaseILj63EE_02cb6de0 + 0x10;
        Framework::CHash32::~CHash32()(auStack_d0);
        puStack_118 = PTR__ZTV22CParameterPropertyBaseILj62EE_02cbaea8 + 0x10;
        Framework::CHash32::~CHash32()(auStack_100);
        puStack_150 = puVar9;
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*)(&puStack_130,uStack_128);
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*)(&puStack_148,auStack_140[0]);
        ppppppplVar17 = ppppppplVar17 + 5;
        (*(code *)(*ppppppplVar17)[2])(ppppppplVar17);
      }
      else {
        do {
          while (ppppppplVar17 = ppppppplVar14, ppppppplVar17[4] < pppppplStack_88) {
            ppppppplVar14 = (long *******)ppppppplVar17[1];
            if ((long *******)ppppppplVar17[1] == (long *******)0x0) {
              ppppppplVar17 = ppppppplVar13;
              if (ppppppplVar13 != ppppppplVar18) goto code_r0x0162dc60;
              goto code_r0x0162dc7c;
            }
          }
          ppppppplVar14 = (long *******)*ppppppplVar17;
          ppppppplVar13 = ppppppplVar17;
        } while ((long *******)*ppppppplVar17 != (long *******)0x0);
        if (ppppppplVar17 == ppppppplVar18) goto code_r0x0162dc7c;
code_r0x0162dc60:
        if ((pppppplStack_88 < ppppppplVar17[4]) || (ppppppplVar17 == ppppppplVar18))
        goto code_r0x0162dc7c;
        ppppppplVar17 = ppppppplVar17 + 5;
      }
      lVar10 = *param_2 + uVar15 * 0x40;
      iVar11 = *(int *)(lVar10 + 0x20);
      if (iVar11 == 6) {
        (*(code *)**ppppppplVar17)(ppppppplVar17,lVar10 + 0x28);
      }
      else if (iVar11 == 7) {
        (*(code *)(*ppppppplVar17)[1])(ppppppplVar17,*param_2 + uVar15 * 0x40 + 0x28);
      }
      uVar1 = (int)uVar15 + 1;
      uVar15 = (ulong)uVar1;
    } while (uVar1 < *(uint *)(param_2 + 1));
  }
  return 1;
}

// ==== IInfoBaseMap<unsigned long, CDeepSpaceAreaInfo>::DeserializeChild(Aska::ASON::AValue::AMap const*)
// vaddr 0x152e420 | ghidra 0x162e420 | size 1092 | symbol _ZN12IInfoBaseMapIm18CDeepSpaceAreaInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN12IInfoBaseMapIm18CDeepSpaceAreaInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE
          (long *param_1,long *param_2)

{
  uint uVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined *puVar5;
  undefined *puVar6;
  undefined *puVar7;
  undefined *puVar8;
  undefined *puVar9;
  undefined *puVar10;
  undefined *puVar11;
  undefined *puVar12;
  undefined *puVar13;
  undefined *puVar14;
  undefined *puVar15;
  undefined *puVar16;
  undefined *puVar17;
  undefined *puVar18;
  undefined *puVar19;
  int iVar20;
  long *plVar21;
  long lVar22;
  long *plVar23;
  ulong uVar24;
  long *plVar25;
  long *plVar26;
  undefined *puStack_270;
  undefined1 *puStack_268;
  undefined1 auStack_260 [16];
  undefined8 *puStack_250;
  undefined8 uStack_248;
  undefined8 uStack_240;
  undefined *puStack_238;
  undefined8 *puStack_230;
  undefined8 uStack_228;
  undefined8 uStack_220;
  undefined8 *puStack_218;
  undefined8 uStack_210;
  undefined8 uStack_208;
  undefined8 *puStack_200;
  undefined8 uStack_1f8;
  undefined8 uStack_1f0;
  undefined *puStack_1e8;
  undefined8 uStack_1e0;
  undefined1 uStack_1d8;
  undefined1 auStack_1d0 [24];
  undefined *puStack_1b8;
  undefined8 uStack_1b0;
  undefined1 uStack_1a8;
  undefined1 auStack_1a0 [24];
  undefined *puStack_188;
  undefined8 uStack_180;
  undefined1 uStack_178;
  undefined1 auStack_170 [24];
  undefined *puStack_158;
  undefined8 uStack_150;
  undefined1 uStack_148;
  undefined1 auStack_140 [24];
  undefined *puStack_128;
  undefined8 uStack_120;
  undefined1 uStack_118;
  undefined1 auStack_110 [24];
  undefined *puStack_f8;
  undefined8 uStack_f0;
  undefined1 uStack_e8;
  undefined1 auStack_e0 [24];
  undefined *puStack_c8;
  undefined8 uStack_c0;
  undefined1 uStack_b8;
  undefined1 auStack_b0 [24];
  undefined *puStack_98;
  undefined8 uStack_90;
  undefined1 uStack_88;
  undefined1 auStack_80 [24];
  ulong uStack_68;
  
  plVar26 = param_1 + 8;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CDeepSpaceAreaInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CDeepSpaceAreaInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CDeepSpaceAreaInfo>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CDeepSpaceAreaInfo>, void*>*)(param_1 + 7,*plVar26);
  param_1[7] = (long)plVar26;
  param_1[8] = 0;
  param_1[9] = 0;
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0282d54e/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\Info/InfoBase.h"*/,0x1c1,&UNK_027dc58a/*"apParser is null."*/);
    iVar20 = iRam0000000000000008;
  }
  else {
    iVar20 = (int)param_2[1];
  }
  if (iVar20 != 0) {
    puVar2 = PTR__ZTV18CDeepSpaceAreaInfo_02cc0440 + 0x10;
    puVar3 = PTR__ZTV24CDeepSpaceMissionInfoMap_02cc33f8 + 0x10;
    puVar4 = PTR__ZTV22CParameterPropertyBaseILj61EE_02cb7008 + 0x10;
    puVar5 = PTR__ZTV23CParameterPropertyValueIjLj61E18CPropertyConverterE_02cc4d48 + 0x10;
    puVar6 = PTR__ZTV22CParameterPropertyBaseILj62EE_02cbaea8 + 0x10;
    puVar7 = PTR__ZTV23CParameterPropertyValueIjLj62E18CPropertyConverterE_02cb9140 + 0x10;
    puVar8 = PTR__ZTV22CParameterPropertyBaseILj63EE_02cb6de0 + 0x10;
    puVar9 = PTR__ZTV23CParameterPropertyValueIjLj63E18CPropertyConverterE_02cbd2a0 + 0x10;
    puVar10 = PTR__ZTV22CParameterPropertyBaseILj64EE_02cbbba0 + 0x10;
    puVar11 = PTR__ZTV23CParameterPropertyValueIjLj64E18CPropertyConverterE_02cb96a8 + 0x10;
    puVar12 = PTR__ZTV22CParameterPropertyBaseILj65EE_02cb79a0 + 0x10;
    puVar13 = PTR__ZTV23CParameterPropertyValueIjLj65E18CPropertyConverterE_02cbf1c8 + 0x10;
    puVar14 = PTR__ZTV22CParameterPropertyBaseILj66EE_02cc1e50 + 0x10;
    puVar15 = PTR__ZTV23CParameterPropertyValueIbLj66E18CPropertyConverterE_02cbc8d8 + 0x10;
    puVar16 = PTR__ZTV22CParameterPropertyBaseILj67EE_02cc15a8 + 0x10;
    puVar17 = PTR__ZTV23CParameterPropertyValueIbLj67E18CPropertyConverterE_02cc38c8 + 0x10;
    puVar18 = PTR__ZTV22CParameterPropertyBaseILj68EE_02cb7090 + 0x10;
    uVar24 = 0;
    puVar19 = PTR__ZTV23CParameterPropertyValueIbLj68E18CPropertyConverterE_02cba440 + 0x10;
    do {
      uStack_68 = (**(code **)(*param_1 + 0x20))(param_1,*param_2 + uVar24 * 0x40);
      plVar21 = (long *)param_1[8];
      plVar23 = plVar26;
      if ((long *)param_1[8] == (long *)0x0) {
code_r0x0162e68c:
        memset(auStack_260,0,0x1f8);
        uStack_248 = 0;
        uStack_240 = 0;
        uStack_228 = 0;
        uStack_220 = 0;
        uStack_210 = 0;
        uStack_208 = 0;
        uStack_1f8 = 0;
        uStack_1f0 = 0;
        uStack_1d8 = 0;
        uStack_1e0 = 0;
        puStack_270 = puVar2;
        puStack_268 = auStack_260;
        puStack_250 = &uStack_248;
        puStack_238 = puVar3;
        puStack_230 = &uStack_228;
        puStack_218 = &uStack_210;
        puStack_200 = &uStack_1f8;
        puStack_1e8 = puVar4;
        Framework::CHash32::CHash32()(auStack_1d0);
        uStack_1a8 = 0;
        uStack_1b0 = 0;
        puStack_1e8 = puVar5;
        puStack_1b8 = puVar6;
        Framework::CHash32::CHash32()(auStack_1a0);
        uStack_178 = 0;
        uStack_180 = 0;
        puStack_1b8 = puVar7;
        puStack_188 = puVar8;
        Framework::CHash32::CHash32()(auStack_170);
        uStack_148 = 0;
        uStack_150 = 0;
        puStack_188 = puVar9;
        puStack_158 = puVar10;
        Framework::CHash32::CHash32()(auStack_140);
        uStack_120 = 0;
        uStack_118 = 0;
        puStack_158 = puVar11;
        puStack_128 = puVar12;
        Framework::CHash32::CHash32()(auStack_110);
        uStack_f0 = 0;
        uStack_e8 = 0;
        puStack_128 = puVar13;
        puStack_f8 = puVar14;
        Framework::CHash32::CHash32()(auStack_e0);
        uStack_c0 = 0;
        uStack_b8 = 0;
        puStack_f8 = puVar15;
        puStack_c8 = puVar16;
        Framework::CHash32::CHash32()(auStack_b0);
        uStack_90 = 0;
        uStack_88 = 0;
        puStack_c8 = puVar17;
        puStack_98 = puVar18;
        Framework::CHash32::CHash32()(auStack_80);
        puStack_98 = puVar19;
        lVar22 = std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned long, CDeepSpaceAreaInfo>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CDeepSpaceAreaInfo>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CDeepSpaceAreaInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CDeepSpaceAreaInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CDeepSpaceAreaInfo>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned long, unsigned long&, CDeepSpaceAreaInfo>(unsigned long const&, unsigned long&, CDeepSpaceAreaInfo&&)(param_1 + 7,&uStack_68,&uStack_68,&puStack_270);
        CDeepSpaceAreaInfo::~CDeepSpaceAreaInfo()(&puStack_270);
        plVar25 = (long *)(lVar22 + 0x28);
        (**(code **)(*plVar25 + 0x10))(plVar25);
      }
      else {
        do {
          while (plVar25 = plVar21, (ulong)plVar25[4] < uStack_68) {
            plVar21 = (long *)plVar25[1];
            if ((long *)plVar25[1] == (long *)0x0) {
              plVar25 = plVar23;
              if (plVar23 != plVar26) goto code_r0x0162e670;
              goto code_r0x0162e68c;
            }
          }
          plVar21 = (long *)*plVar25;
          plVar23 = plVar25;
        } while ((long *)*plVar25 != (long *)0x0);
        if (plVar25 == plVar26) goto code_r0x0162e68c;
code_r0x0162e670:
        if ((uStack_68 < (ulong)plVar25[4]) || (plVar25 == plVar26)) goto code_r0x0162e68c;
        plVar25 = plVar25 + 5;
      }
      lVar22 = *param_2 + uVar24 * 0x40;
      iVar20 = *(int *)(lVar22 + 0x20);
      if (iVar20 == 6) {
        (**(code **)*plVar25)(plVar25,lVar22 + 0x28);
      }
      else if (iVar20 == 7) {
        (**(code **)(*plVar25 + 8))(plVar25,*param_2 + uVar24 * 0x40 + 0x28);
      }
      uVar1 = (int)uVar24 + 1;
      uVar24 = (ulong)uVar1;
    } while (uVar1 < *(uint *)(param_2 + 1));
  }
  return 1;
}

// ==== IInfoBaseMap<unsigned long, CDeepSpaceShipInfo>::DeserializeChild(Aska::ASON::AValue::AMap const*)
// vaddr 0x152eee4 | ghidra 0x162eee4 | size 1188 | symbol _ZN12IInfoBaseMapIm18CDeepSpaceShipInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Type propagation algorithm not settling */

undefined8
_ZN12IInfoBaseMapIm18CDeepSpaceShipInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE
          (long *param_1,long *param_2)

{
  uint uVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined *puVar5;
  undefined *puVar6;
  undefined *puVar7;
  undefined *puVar8;
  undefined *puVar9;
  undefined *puVar10;
  undefined *puVar11;
  undefined *puVar12;
  undefined *puVar13;
  undefined *puVar14;
  undefined *puVar15;
  undefined *puVar16;
  long lVar17;
  int iVar18;
  long *plVar19;
  long *******ppppppplVar20;
  long *******ppppppplVar21;
  ulong uVar22;
  long *******ppppppplVar23;
  long *******ppppppplVar24;
  long *******ppppppplVar25;
  undefined *puStack_230;
  undefined1 *puStack_228;
  undefined1 auStack_220 [16];
  undefined8 *puStack_210;
  undefined8 uStack_208;
  undefined8 uStack_200;
  undefined *puStack_1f8;
  undefined8 uStack_1f0;
  undefined1 uStack_1e8;
  undefined1 auStack_1e0 [24];
  undefined *puStack_1c8;
  undefined8 uStack_1c0;
  undefined1 uStack_1b8;
  undefined1 auStack_1b0 [24];
  undefined *puStack_198;
  undefined8 uStack_190;
  undefined1 uStack_188;
  undefined1 auStack_180 [24];
  undefined *puStack_168;
  undefined8 uStack_160;
  undefined1 uStack_158;
  undefined1 auStack_150 [24];
  undefined *puStack_138;
  undefined8 uStack_130;
  undefined1 uStack_128;
  undefined1 auStack_120 [24];
  undefined *puStack_108;
  undefined8 uStack_100;
  undefined1 uStack_f8;
  undefined1 auStack_f0 [16];
  undefined8 uStack_e0;
  undefined8 uStack_d8;
  undefined8 uStack_d0;
  undefined *puStack_c8;
  undefined8 uStack_c0;
  undefined1 uStack_b8;
  undefined1 auStack_b0 [16];
  undefined8 uStack_a0;
  undefined8 uStack_98;
  undefined8 uStack_90;
  long ******pppppplStack_88;
  long *******appppppplStack_80 [3];
  long *******ppppppplStack_68;
  
  ppppppplVar24 = (long *******)(param_1 + 8);
  plVar19 = param_1 + 7;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CDeepSpaceShipInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CDeepSpaceShipInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CDeepSpaceShipInfo>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CDeepSpaceShipInfo>, void*>*)(plVar19,*ppppppplVar24);
  param_1[7] = (long)ppppppplVar24;
  param_1[8] = 0;
  param_1[9] = 0;
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0282d54e/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\Info/InfoBase.h"*/,0x1c1,&UNK_027dc58a/*"apParser is null."*/);
    iVar18 = iRam0000000000000008;
  }
  else {
    iVar18 = (int)param_2[1];
  }
  if (iVar18 != 0) {
    puVar2 = PTR__ZTV18CDeepSpaceShipInfo_02cc04b8 + 0x10;
    puVar3 = PTR__ZTV22CParameterPropertyBaseILj15EE_02cc0790 + 0x10;
    puVar4 = PTR__ZTV23CParameterPropertyValueIjLj15E18CPropertyConverterE_02cc1598 + 0x10;
    puVar5 = PTR__ZTV22CParameterPropertyBaseILj16EE_02cb9c20 + 0x10;
    puVar6 = PTR__ZTV23CParameterPropertyValueIjLj16E18CPropertyConverterE_02cbd008 + 0x10;
    puVar7 = PTR__ZTV22CParameterPropertyBaseILj17EE_02cba1e8 + 0x10;
    puVar8 = PTR__ZTV23CParameterPropertyValueIjLj17E18CPropertyConverterE_02cbb3b8 + 0x10;
    puVar9 = PTR__ZTV22CParameterPropertyBaseILj18EE_02cbe238 + 0x10;
    puVar10 = PTR__ZTV23CParameterPropertyValueIjLj18E18CPropertyConverterE_02cbcd58 + 0x10;
    puVar11 = PTR__ZTV22CParameterPropertyBaseILj19EE_02cc4c98 + 0x10;
    puVar12 = PTR__ZTV23CParameterPropertyValueIjLj19E18CPropertyConverterE_02cc13e8 + 0x10;
    puVar13 = PTR__ZTV22CParameterPropertyBaseILj20EE_02cc0d08 + 0x10;
    puVar14 = PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj20EE_02cba938
              + 0x10;
    puVar15 = PTR__ZTV22CParameterPropertyBaseILj21EE_02cc1310 + 0x10;
    uVar22 = 0;
    puVar16 = PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj21EE_02cbede0
              + 0x10;
    do {
      pppppplStack_88 =
           (long ******)(**(code **)(*param_1 + 0x20))(param_1,*param_2 + uVar22 * 0x40);
      ppppppplVar21 = (long *******)param_1[8];
      ppppppplVar20 = ppppppplVar24;
      if ((long *******)param_1[8] == (long *******)0x0) {
code_r0x0162f118:
        memset(auStack_220,0,0x198);
        uStack_208 = 0;
        uStack_200 = 0;
        uStack_1e8 = 0;
        uStack_1f0 = 0;
        puStack_230 = puVar2;
        puStack_228 = auStack_220;
        puStack_210 = &uStack_208;
        puStack_1f8 = puVar3;
        Framework::CHash32::CHash32()(auStack_1e0);
        uStack_1b8 = 0;
        uStack_1c0 = 0;
        puStack_1f8 = puVar4;
        puStack_1c8 = puVar5;
        Framework::CHash32::CHash32()(auStack_1b0);
        uStack_188 = 0;
        uStack_190 = 0;
        puStack_1c8 = puVar6;
        puStack_198 = puVar7;
        Framework::CHash32::CHash32()(auStack_180);
        uStack_158 = 0;
        uStack_160 = 0;
        puStack_198 = puVar8;
        puStack_168 = puVar9;
        Framework::CHash32::CHash32()(auStack_150);
        uStack_128 = 0;
        uStack_130 = 0;
        puStack_168 = puVar10;
        puStack_138 = puVar11;
        Framework::CHash32::CHash32()(auStack_120);
        uStack_f8 = 0;
        uStack_100 = 0;
        puStack_138 = puVar12;
        puStack_108 = puVar13;
        Framework::CHash32::CHash32()(auStack_f0);
        uStack_d8 = 0;
        uStack_d0 = 0;
        uStack_e0 = 0;
        uStack_c0 = 0;
        uStack_b8 = 0;
        puStack_108 = puVar14;
        puStack_c8 = puVar15;
        Framework::CHash32::CHash32()(auStack_b0);
        uStack_98 = 0;
        uStack_90 = 0;
        uStack_a0 = 0;
        ppppppplVar21 = (long *******)*ppppppplVar24;
        if ((long *******)*ppppppplVar24 == (long *******)0x0) {
          ppppppplVar23 = (long *******)*ppppppplVar24;
          ppppppplVar20 = ppppppplVar24;
          ppppppplVar25 = ppppppplVar24;
        }
        else {
          do {
            while (ppppppplVar20 = ppppppplVar21, ppppppplVar20[4] <= pppppplStack_88) {
              if (pppppplStack_88 <= ppppppplVar20[4]) {
                ppppppplVar23 = ppppppplVar20;
                ppppppplVar25 = (long *******)&ppppppplStack_68;
                goto joined_r0x0162f284;
              }
              ppppppplVar25 = ppppppplVar20 + 1;
              ppppppplVar21 = (long *******)*ppppppplVar25;
              if ((long *******)*ppppppplVar25 == (long *******)0x0) {
                ppppppplVar23 = (long *******)*ppppppplVar25;
                goto joined_r0x0162f284;
              }
            }
            ppppppplVar21 = (long *******)*ppppppplVar20;
          } while ((long *******)*ppppppplVar20 != (long *******)0x0);
          ppppppplVar23 = (long *******)*ppppppplVar20;
          ppppppplVar25 = ppppppplVar20;
        }
joined_r0x0162f284:
        puStack_c8 = puVar16;
        ppppppplStack_68 = ppppppplVar20;
        if (ppppppplVar23 == (long *******)0x0) {
          std::__ndk1::unique_ptr<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CDeepSpaceShipInfo>, void*>, std::__ndk1::__tree_node_destructor<Framework::CSTLAllocator<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CDeepSpaceShipInfo>, void*>, Framework::CSTLMapAllocatorInf> > > std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CDeepSpaceShipInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CDeepSpaceShipInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CDeepSpaceShipInfo>, Framework::CSTLMapAllocatorInf> >::__construct_node<unsigned long&, CDeepSpaceShipInfo>(unsigned long&, CDeepSpaceShipInfo&&)(appppppplStack_80,plVar19,&pppppplStack_88,&puStack_230);
          *appppppplStack_80[0] = (long ******)0x0;
          appppppplStack_80[0][1] = (long ******)0x0;
          appppppplStack_80[0][2] = (long ******)ppppppplVar20;
          *ppppppplVar25 = (long ******)appppppplStack_80[0];
          ppppppplVar21 = appppppplStack_80[0];
          if (*(long *)*plVar19 != 0) {
            *plVar19 = *(long *)*plVar19;
            ppppppplVar21 = (long *******)*ppppppplVar25;
          }
          void std::__ndk1::__tree_balance_after_insert<std::__ndk1::__tree_node_base<void*>*>(std::__ndk1::__tree_node_base<void*>*, std::__ndk1::__tree_node_base<void*>*)(param_1[8],ppppppplVar21);
          param_1[9] = param_1[9] + 1;
          ppppppplVar23 = appppppplStack_80[0];
        }
        CDeepSpaceShipInfo::~CDeepSpaceShipInfo()(&puStack_230);
        ppppppplVar23 = ppppppplVar23 + 5;
        (*(code *)(*ppppppplVar23)[2])(ppppppplVar23);
      }
      else {
        do {
          while (ppppppplVar23 = ppppppplVar21, ppppppplVar23[4] < pppppplStack_88) {
            ppppppplVar21 = (long *******)ppppppplVar23[1];
            if ((long *******)ppppppplVar23[1] == (long *******)0x0) {
              ppppppplVar23 = ppppppplVar20;
              if (ppppppplVar20 != ppppppplVar24) goto code_r0x0162f0fc;
              goto code_r0x0162f118;
            }
          }
          ppppppplVar21 = (long *******)*ppppppplVar23;
          ppppppplVar20 = ppppppplVar23;
        } while ((long *******)*ppppppplVar23 != (long *******)0x0);
        if (ppppppplVar23 == ppppppplVar24) goto code_r0x0162f118;
code_r0x0162f0fc:
        if ((pppppplStack_88 < ppppppplVar23[4]) || (ppppppplVar23 == ppppppplVar24))
        goto code_r0x0162f118;
        ppppppplVar23 = ppppppplVar23 + 5;
      }
      lVar17 = *param_2 + uVar22 * 0x40;
      iVar18 = *(int *)(lVar17 + 0x20);
      if (iVar18 == 6) {
        (*(code *)**ppppppplVar23)(ppppppplVar23,lVar17 + 0x28);
      }
      else if (iVar18 == 7) {
        (*(code *)(*ppppppplVar23)[1])(ppppppplVar23,*param_2 + uVar22 * 0x40 + 0x28);
      }
      uVar1 = (int)uVar22 + 1;
      uVar22 = (ulong)uVar1;
    } while (uVar1 < *(uint *)(param_2 + 1));
  }
  return 1;
}

// ==== IInfoBaseMap<unsigned long, CAddCharacterExpInfo>::DeserializeChild(Aska::ASON::AValue::AMap const*)
// vaddr 0x152f858 | ghidra 0x162f858 | size 1420 | symbol _ZN12IInfoBaseMapIm20CAddCharacterExpInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Type propagation algorithm not settling */

undefined8
_ZN12IInfoBaseMapIm20CAddCharacterExpInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE
          (long *param_1,long *param_2)

{
  uint uVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined *puVar5;
  undefined *puVar6;
  undefined *puVar7;
  undefined *puVar8;
  undefined *puVar9;
  undefined *puVar10;
  undefined *puVar11;
  undefined *puVar12;
  undefined *puVar13;
  undefined *puVar14;
  undefined *puVar15;
  undefined *puVar16;
  undefined *puVar17;
  long lVar18;
  int iVar19;
  long *plVar20;
  long *******ppppppplVar21;
  long *******ppppppplVar22;
  ulong uVar23;
  long *******ppppppplVar24;
  long *******ppppppplVar25;
  long *******ppppppplVar26;
  undefined *puStack_210;
  undefined8 *puStack_208;
  undefined8 auStack_200 [2];
  undefined8 *puStack_1f0;
  undefined8 uStack_1e8;
  undefined8 uStack_1e0;
  undefined *puStack_1d8;
  undefined8 uStack_1d0;
  undefined1 uStack_1c8;
  undefined1 auStack_1c0 [24];
  undefined *puStack_1a8;
  undefined8 uStack_1a0;
  undefined1 uStack_198;
  undefined1 auStack_190 [24];
  undefined *puStack_178;
  undefined8 uStack_170;
  undefined1 uStack_168;
  undefined1 auStack_160 [24];
  undefined *puStack_148;
  undefined8 uStack_140;
  undefined1 uStack_138;
  undefined1 auStack_130 [24];
  undefined *puStack_118;
  undefined8 uStack_110;
  undefined1 uStack_108;
  undefined1 auStack_100 [24];
  undefined *puStack_e8;
  undefined8 uStack_e0;
  undefined1 uStack_d8;
  undefined1 auStack_d0 [24];
  undefined *puStack_b8;
  undefined8 uStack_b0;
  undefined1 uStack_a8;
  undefined1 auStack_a0 [24];
  long ******pppppplStack_88;
  long *******appppppplStack_80 [3];
  long *******ppppppplStack_68;
  
  ppppppplVar24 = (long *******)(param_1 + 8);
  plVar20 = param_1 + 7;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CAddCharacterExpInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CAddCharacterExpInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CAddCharacterExpInfo>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CAddCharacterExpInfo>, void*>*)(plVar20,*ppppppplVar24);
  param_1[7] = (long)ppppppplVar24;
  param_1[8] = 0;
  param_1[9] = 0;
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0282d54e/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\Info/InfoBase.h"*/,0x1c1,&UNK_027dc58a/*"apParser is null."*/);
    iVar19 = iRam0000000000000008;
  }
  else {
    iVar19 = (int)param_2[1];
  }
  if (iVar19 != 0) {
    puVar2 = PTR__ZTV20CAddCharacterExpInfo_02cb7320 + 0x10;
    puVar3 = PTR__ZTV22CParameterPropertyBaseILj24EE_02cbdf68 + 0x10;
    puVar4 = PTR__ZTV23CParameterPropertyValueImLj24E18CPropertyConverterE_02cc3a90 + 0x10;
    puVar5 = PTR__ZTV22CParameterPropertyBaseILj25EE_02cbd6c8 + 0x10;
    puVar6 = PTR__ZTV23CParameterPropertyValueIjLj25E18CPropertyConverterE_02cb9440 + 0x10;
    puVar7 = PTR__ZTV23CParameterPropertyValueIjLj27E18CPropertyConverterE_02cb9a58 + 0x10;
    puVar8 = PTR__ZTV23CParameterPropertyValueIjLj28E18CPropertyConverterE_02cbedd8 + 0x10;
    puVar9 = PTR__ZTV23CParameterPropertyValueIjLj29E18CPropertyConverterE_02cb7988 + 0x10;
    puVar10 = PTR__ZTV23CParameterPropertyValueIjLj30E18CPropertyConverterE_02cc1c18 + 0x10;
    puVar11 = PTR__ZTV23CParameterPropertyValueIjLj32E18CPropertyConverterE_02cb7660 + 0x10;
    puVar12 = PTR__ZTV8InfoBase_02cc49c8 + 0x10;
    puVar13 = PTR__ZTV22CParameterPropertyBaseILj27EE_02cbd4a8 + 0x10;
    puVar14 = PTR__ZTV22CParameterPropertyBaseILj28EE_02cbdb40 + 0x10;
    puVar15 = PTR__ZTV22CParameterPropertyBaseILj29EE_02cc1a28 + 0x10;
    puVar16 = PTR__ZTV22CParameterPropertyBaseILj30EE_02cbe830 + 0x10;
    uVar23 = 0;
    puVar17 = PTR__ZTV22CParameterPropertyBaseILj32EE_02cc0fa8 + 0x10;
    do {
      pppppplStack_88 =
           (long ******)(**(code **)(*param_1 + 0x20))(param_1,*param_2 + uVar23 * 0x40);
      ppppppplVar22 = (long *******)param_1[8];
      ppppppplVar21 = ppppppplVar24;
      if ((long *******)param_1[8] == (long *******)0x0) {
code_r0x0162faa0:
        memset(auStack_200,0,0x178);
        uStack_1e8 = 0;
        uStack_1e0 = 0;
        uStack_1c8 = 0;
        uStack_1d0 = 0;
        puStack_210 = puVar2;
        puStack_208 = auStack_200;
        puStack_1f0 = &uStack_1e8;
        puStack_1d8 = puVar3;
        Framework::CHash32::CHash32()(auStack_1c0);
        uStack_198 = 0;
        uStack_1a0 = 0;
        puStack_1d8 = puVar4;
        puStack_1a8 = puVar5;
        Framework::CHash32::CHash32()(auStack_190);
        uStack_168 = 0;
        uStack_170 = 0;
        puStack_1a8 = puVar6;
        puStack_178 = puVar13;
        Framework::CHash32::CHash32()(auStack_160);
        uStack_138 = 0;
        uStack_140 = 0;
        puStack_178 = puVar7;
        puStack_148 = puVar14;
        Framework::CHash32::CHash32()(auStack_130);
        uStack_108 = 0;
        uStack_110 = 0;
        puStack_148 = puVar8;
        puStack_118 = puVar15;
        Framework::CHash32::CHash32()(auStack_100);
        uStack_d8 = 0;
        uStack_e0 = 0;
        puStack_118 = puVar9;
        puStack_e8 = puVar16;
        Framework::CHash32::CHash32()(auStack_d0);
        uStack_b0 = 0;
        uStack_a8 = 0;
        puStack_e8 = puVar10;
        puStack_b8 = puVar17;
        Framework::CHash32::CHash32()(auStack_a0);
        ppppppplVar22 = (long *******)*ppppppplVar24;
        if ((long *******)*ppppppplVar24 == (long *******)0x0) {
          ppppppplVar25 = (long *******)*ppppppplVar24;
          ppppppplVar21 = ppppppplVar24;
          ppppppplVar26 = ppppppplVar24;
        }
        else {
          do {
            while (ppppppplVar21 = ppppppplVar22, ppppppplVar21[4] <= pppppplStack_88) {
              if (pppppplStack_88 <= ppppppplVar21[4]) {
                ppppppplVar25 = ppppppplVar21;
                ppppppplVar26 = (long *******)&ppppppplStack_68;
                goto joined_r0x0162fc08;
              }
              ppppppplVar26 = ppppppplVar21 + 1;
              ppppppplVar22 = (long *******)*ppppppplVar26;
              if ((long *******)*ppppppplVar26 == (long *******)0x0) {
                ppppppplVar25 = (long *******)*ppppppplVar26;
                goto joined_r0x0162fc08;
              }
            }
            ppppppplVar22 = (long *******)*ppppppplVar21;
          } while ((long *******)*ppppppplVar21 != (long *******)0x0);
          ppppppplVar25 = (long *******)*ppppppplVar21;
          ppppppplVar26 = ppppppplVar21;
        }
joined_r0x0162fc08:
        ppppppplStack_68 = ppppppplVar21;
        if (ppppppplVar25 == (long *******)0x0) {
          puStack_b8 = puVar11;
          std::__ndk1::unique_ptr<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CAddCharacterExpInfo>, void*>, std::__ndk1::__tree_node_destructor<Framework::CSTLAllocator<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CAddCharacterExpInfo>, void*>, Framework::CSTLMapAllocatorInf> > > std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CAddCharacterExpInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CAddCharacterExpInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CAddCharacterExpInfo>, Framework::CSTLMapAllocatorInf> >::__construct_node<unsigned long&, CAddCharacterExpInfo>(unsigned long&, CAddCharacterExpInfo&&)(appppppplStack_80,plVar20,&pppppplStack_88,&puStack_210);
          *appppppplStack_80[0] = (long ******)0x0;
          appppppplStack_80[0][1] = (long ******)0x0;
          appppppplStack_80[0][2] = (long ******)ppppppplVar21;
          *ppppppplVar26 = (long ******)appppppplStack_80[0];
          ppppppplVar22 = appppppplStack_80[0];
          if (*(long *)*plVar20 != 0) {
            *plVar20 = *(long *)*plVar20;
            ppppppplVar22 = (long *******)*ppppppplVar26;
          }
          void std::__ndk1::__tree_balance_after_insert<std::__ndk1::__tree_node_base<void*>*>(std::__ndk1::__tree_node_base<void*>*, std::__ndk1::__tree_node_base<void*>*)(param_1[8],ppppppplVar22);
          param_1[9] = param_1[9] + 1;
          ppppppplVar25 = appppppplStack_80[0];
        }
        puStack_210 = PTR__ZTV20CAddCharacterExpInfo_02cb7320 + 0x10;
        puStack_b8 = PTR__ZTV22CParameterPropertyBaseILj32EE_02cc0fa8 + 0x10;
        Framework::CHash32::~CHash32()(auStack_a0);
        puStack_e8 = PTR__ZTV22CParameterPropertyBaseILj30EE_02cbe830 + 0x10;
        Framework::CHash32::~CHash32()(auStack_d0);
        puStack_118 = PTR__ZTV22CParameterPropertyBaseILj29EE_02cc1a28 + 0x10;
        Framework::CHash32::~CHash32()(auStack_100);
        puStack_148 = PTR__ZTV22CParameterPropertyBaseILj28EE_02cbdb40 + 0x10;
        Framework::CHash32::~CHash32()(auStack_130);
        puStack_178 = PTR__ZTV22CParameterPropertyBaseILj27EE_02cbd4a8 + 0x10;
        Framework::CHash32::~CHash32()(auStack_160);
        puStack_1a8 = PTR__ZTV22CParameterPropertyBaseILj25EE_02cbd6c8 + 0x10;
        Framework::CHash32::~CHash32()(auStack_190);
        puStack_1d8 = PTR__ZTV22CParameterPropertyBaseILj24EE_02cbdf68 + 0x10;
        Framework::CHash32::~CHash32()(auStack_1c0);
        puStack_210 = puVar12;
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*)(&puStack_1f0,uStack_1e8);
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*)(&puStack_208,auStack_200[0]);
        ppppppplVar25 = ppppppplVar25 + 5;
        (*(code *)(*ppppppplVar25)[2])(ppppppplVar25);
      }
      else {
        do {
          while (ppppppplVar25 = ppppppplVar22, ppppppplVar25[4] < pppppplStack_88) {
            ppppppplVar22 = (long *******)ppppppplVar25[1];
            if ((long *******)ppppppplVar25[1] == (long *******)0x0) {
              ppppppplVar25 = ppppppplVar21;
              if (ppppppplVar21 != ppppppplVar24) goto code_r0x0162fa84;
              goto code_r0x0162faa0;
            }
          }
          ppppppplVar22 = (long *******)*ppppppplVar25;
          ppppppplVar21 = ppppppplVar25;
        } while ((long *******)*ppppppplVar25 != (long *******)0x0);
        if (ppppppplVar25 == ppppppplVar24) goto code_r0x0162faa0;
code_r0x0162fa84:
        if ((pppppplStack_88 < ppppppplVar25[4]) || (ppppppplVar25 == ppppppplVar24))
        goto code_r0x0162faa0;
        ppppppplVar25 = ppppppplVar25 + 5;
      }
      lVar18 = *param_2 + uVar23 * 0x40;
      iVar19 = *(int *)(lVar18 + 0x20);
      if (iVar19 == 6) {
        (*(code *)**ppppppplVar25)(ppppppplVar25,lVar18 + 0x28);
      }
      else if (iVar19 == 7) {
        (*(code *)(*ppppppplVar25)[1])(ppppppplVar25,*param_2 + uVar23 * 0x40 + 0x28);
      }
      uVar1 = (int)uVar23 + 1;
      uVar23 = (ulong)uVar1;
    } while (uVar1 < *(uint *)(param_2 + 1));
  }
  return 1;
}

// ==== IInfoBaseMap<unsigned long, CDropContentInfo>::DeserializeChild(Aska::ASON::AValue::AMap const*)
// vaddr 0x15302c8 | ghidra 0x16302c8 | size 436 | symbol _ZN12IInfoBaseMapIm16CDropContentInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN12IInfoBaseMapIm16CDropContentInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE
          (long *param_1,long *param_2)

{
  uint uVar1;
  int iVar2;
  long *plVar3;
  long lVar4;
  long *plVar5;
  ulong uVar6;
  long *plVar7;
  long *plVar8;
  undefined1 auStack_290 [584];
  ulong uStack_48;
  
  plVar8 = param_1 + 8;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CDropContentInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CDropContentInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CDropContentInfo>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CDropContentInfo>, void*>*)(param_1 + 7,*plVar8);
  param_1[7] = (long)plVar8;
  param_1[8] = 0;
  param_1[9] = 0;
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0282d54e/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\Info/InfoBase.h"*/,0x1c1,&UNK_027dc58a/*"apParser is null."*/);
    iVar2 = iRam0000000000000008;
  }
  else {
    iVar2 = (int)param_2[1];
  }
  if (iVar2 != 0) {
    uVar6 = 0;
    do {
      uStack_48 = (**(code **)(*param_1 + 0x20))(param_1,*param_2 + uVar6 * 0x40);
      plVar3 = (long *)param_1[8];
      plVar5 = plVar8;
      if ((long *)param_1[8] == (long *)0x0) {
code_r0x016303bc:
        memset(auStack_290,0,0x248);
        CDropContentInfo::CDropContentInfo()(auStack_290);
        lVar4 = std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned long, CDropContentInfo>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CDropContentInfo>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CDropContentInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CDropContentInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CDropContentInfo>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned long, unsigned long&, CDropContentInfo>(unsigned long const&, unsigned long&, CDropContentInfo&&)(param_1 + 7,&uStack_48,&uStack_48,auStack_290);
        CDropContentInfo::~CDropContentInfo()(auStack_290);
        plVar7 = (long *)(lVar4 + 0x28);
        (**(code **)(*plVar7 + 0x10))(plVar7);
      }
      else {
        do {
          while (plVar7 = plVar3, (ulong)plVar7[4] < uStack_48) {
            plVar3 = (long *)plVar7[1];
            if ((long *)plVar7[1] == (long *)0x0) {
              plVar7 = plVar5;
              if (plVar5 != plVar8) goto code_r0x016303a0;
              goto code_r0x016303bc;
            }
          }
          plVar3 = (long *)*plVar7;
          plVar5 = plVar7;
        } while ((long *)*plVar7 != (long *)0x0);
        if (plVar7 == plVar8) goto code_r0x016303bc;
code_r0x016303a0:
        if ((uStack_48 < (ulong)plVar7[4]) || (plVar7 == plVar8)) goto code_r0x016303bc;
        plVar7 = plVar7 + 5;
      }
      lVar4 = *param_2 + uVar6 * 0x40;
      iVar2 = *(int *)(lVar4 + 0x20);
      if (iVar2 == 6) {
        (**(code **)*plVar7)(plVar7,lVar4 + 0x28);
      }
      else if (iVar2 == 7) {
        (**(code **)(*plVar7 + 8))(plVar7,*param_2 + uVar6 * 0x40 + 0x28);
      }
      uVar1 = (int)uVar6 + 1;
      uVar6 = (ulong)uVar1;
    } while (uVar1 < *(uint *)(param_2 + 1));
  }
  return 1;
}

// ==== IInfoBaseMap<unsigned long, CDebugBonusInfo>::DeserializeChild(Aska::ASON::AValue::AMap const*)
// vaddr 0x15311cc | ghidra 0x16311cc | size 1016 | symbol _ZN12IInfoBaseMapIm15CDebugBonusInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Type propagation algorithm not settling */

undefined8
_ZN12IInfoBaseMapIm15CDebugBonusInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE
          (long *param_1,long *param_2)

{
  uint uVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined *puVar5;
  undefined *puVar6;
  undefined *puVar7;
  long lVar8;
  int iVar9;
  long *plVar10;
  long *******ppppppplVar11;
  long *******ppppppplVar12;
  ulong uVar13;
  long *******ppppppplVar14;
  long *******ppppppplVar15;
  long *******ppppppplVar16;
  undefined *puStack_130;
  undefined8 *puStack_128;
  undefined8 auStack_120 [2];
  undefined8 *puStack_110;
  undefined8 uStack_108;
  undefined8 uStack_100;
  undefined *puStack_f8;
  undefined8 uStack_f0;
  undefined1 uStack_e8;
  undefined1 auStack_e0 [24];
  undefined *puStack_c8;
  undefined8 uStack_c0;
  undefined1 uStack_b8;
  undefined1 auStack_b0 [16];
  ulong uStack_a0;
  undefined8 uStack_98;
  undefined8 uStack_90;
  long ******pppppplStack_88;
  long *******appppppplStack_80 [3];
  long *******ppppppplStack_68;
  
  ppppppplVar16 = (long *******)(param_1 + 8);
  plVar10 = param_1 + 7;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CDebugBonusInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CDebugBonusInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CDebugBonusInfo>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CDebugBonusInfo>, void*>*)(plVar10,*ppppppplVar16);
  param_1[7] = (long)ppppppplVar16;
  param_1[8] = 0;
  param_1[9] = 0;
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0282d54e/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\Info/InfoBase.h"*/,0x1c1,&UNK_027dc58a/*"apParser is null."*/);
    iVar9 = iRam0000000000000008;
  }
  else {
    iVar9 = (int)param_2[1];
  }
  if (iVar9 != 0) {
    puVar2 = PTR__ZTV15CDebugBonusInfo_02cbe880 + 0x10;
    puVar3 = PTR__ZTV22CParameterPropertyBaseILj337EE_02cc0ec0 + 0x10;
    puVar4 = PTR__ZTV23CParameterPropertyValueIjLj337E18CPropertyConverterE_02cc3138 + 0x10;
    puVar5 = PTR__ZTV22CParameterPropertyBaseILj338EE_02cbece8 + 0x10;
    puVar6 = PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj338EE_02cba658
             + 0x10;
    uVar13 = 0;
    puVar7 = PTR__ZTV8InfoBase_02cc49c8 + 0x10;
    do {
      pppppplStack_88 =
           (long ******)(**(code **)(*param_1 + 0x20))(param_1,*param_2 + uVar13 * 0x40);
      ppppppplVar12 = (long *******)param_1[8];
      ppppppplVar11 = ppppppplVar16;
      if ((long *******)param_1[8] == (long *******)0x0) {
code_r0x01631350:
        memset(auStack_120,0,0x98);
        uStack_108 = 0;
        uStack_100 = 0;
        uStack_e8 = 0;
        uStack_f0 = 0;
        puStack_130 = puVar2;
        puStack_128 = auStack_120;
        puStack_110 = &uStack_108;
        puStack_f8 = puVar3;
        Framework::CHash32::CHash32()(auStack_e0);
        uStack_b8 = 0;
        uStack_c0 = 0;
        puStack_f8 = puVar4;
        puStack_c8 = puVar5;
        Framework::CHash32::CHash32()(auStack_b0);
        uStack_98 = 0;
        uStack_90 = 0;
        uStack_a0 = 0;
        ppppppplVar12 = (long *******)*ppppppplVar16;
        if ((long *******)*ppppppplVar16 == (long *******)0x0) {
          ppppppplVar15 = (long *******)*ppppppplVar16;
          ppppppplVar11 = ppppppplVar16;
          ppppppplVar14 = ppppppplVar16;
        }
        else {
          do {
            while (ppppppplVar11 = ppppppplVar12, ppppppplVar11[4] <= pppppplStack_88) {
              if (pppppplStack_88 <= ppppppplVar11[4]) {
                ppppppplVar14 = (long *******)&ppppppplStack_68;
                ppppppplVar15 = ppppppplVar11;
                goto joined_r0x0163145c;
              }
              ppppppplVar14 = ppppppplVar11 + 1;
              ppppppplVar12 = (long *******)*ppppppplVar14;
              if ((long *******)*ppppppplVar14 == (long *******)0x0) {
                ppppppplVar15 = (long *******)*ppppppplVar14;
                goto joined_r0x0163145c;
              }
            }
            ppppppplVar12 = (long *******)*ppppppplVar11;
          } while ((long *******)*ppppppplVar11 != (long *******)0x0);
          ppppppplVar15 = (long *******)*ppppppplVar11;
          ppppppplVar14 = ppppppplVar11;
        }
joined_r0x0163145c:
        ppppppplStack_68 = ppppppplVar11;
        if (ppppppplVar15 == (long *******)0x0) {
          puStack_c8 = puVar6;
          std::__ndk1::unique_ptr<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CDebugBonusInfo>, void*>, std::__ndk1::__tree_node_destructor<Framework::CSTLAllocator<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CDebugBonusInfo>, void*>, Framework::CSTLMapAllocatorInf> > > std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CDebugBonusInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CDebugBonusInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CDebugBonusInfo>, Framework::CSTLMapAllocatorInf> >::__construct_node<unsigned long&, CDebugBonusInfo>(unsigned long&, CDebugBonusInfo&&)(appppppplStack_80,plVar10,&pppppplStack_88,&puStack_130);
          *appppppplStack_80[0] = (long ******)0x0;
          appppppplStack_80[0][1] = (long ******)0x0;
          appppppplStack_80[0][2] = (long ******)ppppppplVar11;
          *ppppppplVar14 = (long ******)appppppplStack_80[0];
          ppppppplVar12 = appppppplStack_80[0];
          if (*(long *)*plVar10 != 0) {
            *plVar10 = *(long *)*plVar10;
            ppppppplVar12 = (long *******)*ppppppplVar14;
          }
          void std::__ndk1::__tree_balance_after_insert<std::__ndk1::__tree_node_base<void*>*>(std::__ndk1::__tree_node_base<void*>*, std::__ndk1::__tree_node_base<void*>*)(param_1[8],ppppppplVar12);
          ppppppplVar15 = appppppplStack_80[0];
          param_1[9] = param_1[9] + 1;
          puStack_130 = PTR__ZTV15CDebugBonusInfo_02cbe880 + 0x10;
          puStack_c8 = PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj338EE_02cba658
                       + 0x10;
          if ((uStack_a0 & 1) != 0) {
            Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_90);
          }
        }
        else {
          puStack_130 = PTR__ZTV15CDebugBonusInfo_02cbe880 + 0x10;
        }
        puStack_c8 = PTR__ZTV22CParameterPropertyBaseILj338EE_02cbece8 + 0x10;
        Framework::CHash32::~CHash32()(auStack_b0);
        puStack_f8 = PTR__ZTV22CParameterPropertyBaseILj337EE_02cc0ec0 + 0x10;
        Framework::CHash32::~CHash32()(auStack_e0);
        puStack_130 = puVar7;
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*)(&puStack_110,uStack_108);
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*)(&puStack_128,auStack_120[0]);
        ppppppplVar15 = ppppppplVar15 + 5;
        (*(code *)(*ppppppplVar15)[2])(ppppppplVar15);
      }
      else {
        do {
          while (ppppppplVar15 = ppppppplVar12, ppppppplVar15[4] < pppppplStack_88) {
            ppppppplVar12 = (long *******)ppppppplVar15[1];
            if ((long *******)ppppppplVar15[1] == (long *******)0x0) {
              ppppppplVar15 = ppppppplVar11;
              if (ppppppplVar11 != ppppppplVar16) goto code_r0x01631334;
              goto code_r0x01631350;
            }
          }
          ppppppplVar12 = (long *******)*ppppppplVar15;
          ppppppplVar11 = ppppppplVar15;
        } while ((long *******)*ppppppplVar15 != (long *******)0x0);
        if (ppppppplVar15 == ppppppplVar16) goto code_r0x01631350;
code_r0x01631334:
        if ((pppppplStack_88 < ppppppplVar15[4]) || (ppppppplVar15 == ppppppplVar16))
        goto code_r0x01631350;
        ppppppplVar15 = ppppppplVar15 + 5;
      }
      lVar8 = *param_2 + uVar13 * 0x40;
      iVar9 = *(int *)(lVar8 + 0x20);
      if (iVar9 == 6) {
        (*(code *)**ppppppplVar15)(ppppppplVar15,lVar8 + 0x28);
      }
      else if (iVar9 == 7) {
        (*(code *)(*ppppppplVar15)[1])(ppppppplVar15,*param_2 + uVar13 * 0x40 + 0x28);
      }
      uVar1 = (int)uVar13 + 1;
      uVar13 = (ulong)uVar1;
    } while (uVar1 < *(uint *)(param_2 + 1));
  }
  return 1;
}

// ==== IInfoBaseMap<unsigned long, CDeepSpaceDebugCharacterInfo>::DeserializeChild(Aska::ASON::AValue::AMap const*)
// vaddr 0x153196c | ghidra 0x163196c | size 1168 | symbol _ZN12IInfoBaseMapIm28CDeepSpaceDebugCharacterInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Type propagation algorithm not settling */

undefined8
_ZN12IInfoBaseMapIm28CDeepSpaceDebugCharacterInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE
          (long *param_1,long *param_2)

{
  uint uVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined *puVar5;
  undefined *puVar6;
  undefined *puVar7;
  undefined *puVar8;
  undefined *puVar9;
  undefined *puVar10;
  undefined *puVar11;
  undefined *puVar12;
  undefined *puVar13;
  undefined *puVar14;
  undefined *puVar15;
  undefined *puVar16;
  long lVar17;
  int iVar18;
  long *plVar19;
  long *******ppppppplVar20;
  long *******ppppppplVar21;
  ulong uVar22;
  long *******ppppppplVar23;
  long *******ppppppplVar24;
  long *******ppppppplVar25;
  undefined *puStack_220;
  undefined1 *puStack_218;
  undefined1 auStack_210 [16];
  undefined8 *puStack_200;
  undefined8 uStack_1f8;
  undefined8 uStack_1f0;
  undefined *puStack_1e8;
  undefined8 uStack_1e0;
  undefined1 uStack_1d8;
  undefined1 auStack_1d0 [24];
  undefined *puStack_1b8;
  undefined8 uStack_1b0;
  undefined1 uStack_1a8;
  undefined1 auStack_1a0 [24];
  undefined *puStack_188;
  undefined8 uStack_180;
  undefined1 uStack_178;
  undefined1 auStack_170 [16];
  undefined8 uStack_160;
  undefined8 uStack_158;
  undefined8 uStack_150;
  undefined *puStack_148;
  undefined8 uStack_140;
  undefined1 uStack_138;
  undefined1 auStack_130 [24];
  undefined *puStack_118;
  undefined8 uStack_110;
  undefined1 uStack_108;
  undefined1 auStack_100 [24];
  undefined *puStack_e8;
  undefined8 uStack_e0;
  undefined1 uStack_d8;
  undefined1 auStack_d0 [24];
  undefined *puStack_b8;
  undefined8 uStack_b0;
  undefined1 uStack_a8;
  undefined1 auStack_a0 [24];
  long ******pppppplStack_88;
  long *******appppppplStack_80 [3];
  long *******ppppppplStack_68;
  
  ppppppplVar24 = (long *******)(param_1 + 8);
  plVar19 = param_1 + 7;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CDeepSpaceDebugCharacterInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CDeepSpaceDebugCharacterInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CDeepSpaceDebugCharacterInfo>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CDeepSpaceDebugCharacterInfo>, void*>*)(plVar19,*ppppppplVar24);
  param_1[7] = (long)ppppppplVar24;
  param_1[8] = 0;
  param_1[9] = 0;
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0282d54e/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\Info/InfoBase.h"*/,0x1c1,&UNK_027dc58a/*"apParser is null."*/);
    iVar18 = iRam0000000000000008;
  }
  else {
    iVar18 = (int)param_2[1];
  }
  if (iVar18 != 0) {
    puVar2 = PTR__ZTV28CDeepSpaceDebugCharacterInfo_02cc2180 + 0x10;
    puVar3 = PTR__ZTV22CParameterPropertyBaseILj356EE_02cbf100 + 0x10;
    puVar4 = PTR__ZTV23CParameterPropertyValueImLj356E18CPropertyConverterE_02cc0cd8 + 0x10;
    puVar5 = PTR__ZTV22CParameterPropertyBaseILj357EE_02cb9508 + 0x10;
    puVar6 = PTR__ZTV23CParameterPropertyValueIjLj357E18CPropertyConverterE_02cbca90 + 0x10;
    puVar7 = PTR__ZTV22CParameterPropertyBaseILj358EE_02cbc2f0 + 0x10;
    puVar8 = PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj358EE_02cbe260
             + 0x10;
    puVar9 = PTR__ZTV22CParameterPropertyBaseILj359EE_02cc3ed0 + 0x10;
    puVar10 = PTR__ZTV23CParameterPropertyValueIjLj359E18CPropertyConverterE_02cc1ec8 + 0x10;
    puVar11 = PTR__ZTV22CParameterPropertyBaseILj360EE_02cc37b8 + 0x10;
    puVar12 = PTR__ZTV23CParameterPropertyValueIbLj360E18CPropertyConverterE_02cc22a8 + 0x10;
    puVar13 = PTR__ZTV22CParameterPropertyBaseILj361EE_02cc4368 + 0x10;
    puVar14 = PTR__ZTV23CParameterPropertyValueIjLj361E18CPropertyConverterE_02cb9ba8 + 0x10;
    uVar22 = 0;
    puVar15 = PTR__ZTV22CParameterPropertyBaseILj362EE_02cbd770 + 0x10;
    puVar16 = PTR__ZTV23CParameterPropertyValueIjLj362E18CPropertyConverterE_02cbf8d8 + 0x10;
    do {
      pppppplStack_88 =
           (long ******)(**(code **)(*param_1 + 0x20))(param_1,*param_2 + uVar22 * 0x40);
      ppppppplVar21 = (long *******)param_1[8];
      ppppppplVar20 = ppppppplVar24;
      if ((long *******)param_1[8] == (long *******)0x0) {
code_r0x01631b98:
        memset(auStack_210,0,0x188);
        uStack_1f8 = 0;
        uStack_1f0 = 0;
        uStack_1d8 = 0;
        uStack_1e0 = 0;
        puStack_220 = puVar2;
        puStack_218 = auStack_210;
        puStack_200 = &uStack_1f8;
        puStack_1e8 = puVar3;
        Framework::CHash32::CHash32()(auStack_1d0);
        uStack_1a8 = 0;
        uStack_1b0 = 0;
        puStack_1e8 = puVar4;
        puStack_1b8 = puVar5;
        Framework::CHash32::CHash32()(auStack_1a0);
        uStack_178 = 0;
        uStack_180 = 0;
        puStack_1b8 = puVar6;
        puStack_188 = puVar7;
        Framework::CHash32::CHash32()(auStack_170);
        uStack_158 = 0;
        uStack_150 = 0;
        uStack_160 = 0;
        uStack_138 = 0;
        uStack_140 = 0;
        puStack_188 = puVar8;
        puStack_148 = puVar9;
        Framework::CHash32::CHash32()(auStack_130);
        uStack_108 = 0;
        uStack_110 = 0;
        puStack_148 = puVar10;
        puStack_118 = puVar11;
        Framework::CHash32::CHash32()(auStack_100);
        uStack_d8 = 0;
        uStack_e0 = 0;
        puStack_118 = puVar12;
        puStack_e8 = puVar13;
        Framework::CHash32::CHash32()(auStack_d0);
        uStack_b0 = 0;
        uStack_a8 = 0;
        puStack_e8 = puVar14;
        puStack_b8 = puVar15;
        Framework::CHash32::CHash32()(auStack_a0);
        ppppppplVar21 = (long *******)*ppppppplVar24;
        if ((long *******)*ppppppplVar24 == (long *******)0x0) {
          ppppppplVar23 = (long *******)*ppppppplVar24;
          ppppppplVar20 = ppppppplVar24;
          ppppppplVar25 = ppppppplVar24;
        }
        else {
          do {
            while (ppppppplVar20 = ppppppplVar21, ppppppplVar20[4] <= pppppplStack_88) {
              if (pppppplStack_88 <= ppppppplVar20[4]) {
                ppppppplVar23 = ppppppplVar20;
                ppppppplVar25 = (long *******)&ppppppplStack_68;
                goto joined_r0x01631cf8;
              }
              ppppppplVar25 = ppppppplVar20 + 1;
              ppppppplVar21 = (long *******)*ppppppplVar25;
              if ((long *******)*ppppppplVar25 == (long *******)0x0) {
                ppppppplVar23 = (long *******)*ppppppplVar25;
                goto joined_r0x01631cf8;
              }
            }
            ppppppplVar21 = (long *******)*ppppppplVar20;
          } while ((long *******)*ppppppplVar20 != (long *******)0x0);
          ppppppplVar23 = (long *******)*ppppppplVar20;
          ppppppplVar25 = ppppppplVar20;
        }
joined_r0x01631cf8:
        puStack_b8 = puVar16;
        ppppppplStack_68 = ppppppplVar20;
        if (ppppppplVar23 == (long *******)0x0) {
          std::__ndk1::unique_ptr<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CDeepSpaceDebugCharacterInfo>, void*>, std::__ndk1::__tree_node_destructor<Framework::CSTLAllocator<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CDeepSpaceDebugCharacterInfo>, void*>, Framework::CSTLMapAllocatorInf> > > std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CDeepSpaceDebugCharacterInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CDeepSpaceDebugCharacterInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CDeepSpaceDebugCharacterInfo>, Framework::CSTLMapAllocatorInf> >::__construct_node<unsigned long&, CDeepSpaceDebugCharacterInfo>(unsigned long&, CDeepSpaceDebugCharacterInfo&&)(appppppplStack_80,plVar19,&pppppplStack_88,&puStack_220);
          *appppppplStack_80[0] = (long ******)0x0;
          appppppplStack_80[0][1] = (long ******)0x0;
          appppppplStack_80[0][2] = (long ******)ppppppplVar20;
          *ppppppplVar25 = (long ******)appppppplStack_80[0];
          ppppppplVar21 = appppppplStack_80[0];
          if (*(long *)*plVar19 != 0) {
            *plVar19 = *(long *)*plVar19;
            ppppppplVar21 = (long *******)*ppppppplVar25;
          }
          void std::__ndk1::__tree_balance_after_insert<std::__ndk1::__tree_node_base<void*>*>(std::__ndk1::__tree_node_base<void*>*, std::__ndk1::__tree_node_base<void*>*)(param_1[8],ppppppplVar21);
          param_1[9] = param_1[9] + 1;
          ppppppplVar23 = appppppplStack_80[0];
        }
        CDeepSpaceDebugCharacterInfo::~CDeepSpaceDebugCharacterInfo()(&puStack_220);
        ppppppplVar23 = ppppppplVar23 + 5;
        (*(code *)(*ppppppplVar23)[2])(ppppppplVar23);
      }
      else {
        do {
          while (ppppppplVar23 = ppppppplVar21, ppppppplVar23[4] < pppppplStack_88) {
            ppppppplVar21 = (long *******)ppppppplVar23[1];
            if ((long *******)ppppppplVar23[1] == (long *******)0x0) {
              ppppppplVar23 = ppppppplVar20;
              if (ppppppplVar20 != ppppppplVar24) goto code_r0x01631b7c;
              goto code_r0x01631b98;
            }
          }
          ppppppplVar21 = (long *******)*ppppppplVar23;
          ppppppplVar20 = ppppppplVar23;
        } while ((long *******)*ppppppplVar23 != (long *******)0x0);
        if (ppppppplVar23 == ppppppplVar24) goto code_r0x01631b98;
code_r0x01631b7c:
        if ((pppppplStack_88 < ppppppplVar23[4]) || (ppppppplVar23 == ppppppplVar24))
        goto code_r0x01631b98;
        ppppppplVar23 = ppppppplVar23 + 5;
      }
      lVar17 = *param_2 + uVar22 * 0x40;
      iVar18 = *(int *)(lVar17 + 0x20);
      if (iVar18 == 6) {
        (*(code *)**ppppppplVar23)(ppppppplVar23,lVar17 + 0x28);
      }
      else if (iVar18 == 7) {
        (*(code *)(*ppppppplVar23)[1])(ppppppplVar23,*param_2 + uVar22 * 0x40 + 0x28);
      }
      uVar1 = (int)uVar22 + 1;
      uVar22 = (ulong)uVar1;
    } while (uVar1 < *(uint *)(param_2 + 1));
  }
  return 1;
}

// ==== IInfoBaseMap<unsigned long, CDebugDropContentInfoList>::DeserializeChild(Aska::ASON::AValue::AMap const*)
// vaddr 0x1534980 | ghidra 0x1634980 | size 584 | symbol _ZN12IInfoBaseMapIm25CDebugDropContentInfoListE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN12IInfoBaseMapIm25CDebugDropContentInfoListE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE
          (long *param_1,long *param_2)

{
  uint uVar1;
  undefined *puVar2;
  undefined *puVar3;
  long lVar4;
  int iVar5;
  long *plVar6;
  long lVar7;
  long *plVar8;
  ulong uVar9;
  long *plVar10;
  long *plVar11;
  undefined *puStack_b8;
  undefined8 *puStack_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined8 *puStack_98;
  undefined8 uStack_90;
  undefined8 uStack_88;
  long lStack_80;
  long lStack_78;
  undefined8 uStack_70;
  ulong uStack_68;
  
  plVar11 = param_1 + 8;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CDebugDropContentInfoList>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CDebugDropContentInfoList>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CDebugDropContentInfoList>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CDebugDropContentInfoList>, void*>*)(param_1 + 7,*plVar11);
  param_1[7] = (long)plVar11;
  param_1[8] = 0;
  param_1[9] = 0;
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0282d54e/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\Info/InfoBase.h"*/,0x1c1,&UNK_027dc58a/*"apParser is null."*/);
    iVar5 = iRam0000000000000008;
  }
  else {
    iVar5 = (int)param_2[1];
  }
  if (iVar5 != 0) {
    uVar9 = 0;
    puVar2 = PTR__ZTV25CDebugDropContentInfoList_02cb6fb8 + 0x10;
    puVar3 = PTR__ZTV8InfoBase_02cc49c8 + 0x10;
    do {
      uStack_68 = (**(code **)(*param_1 + 0x20))(param_1,*param_2 + uVar9 * 0x40);
      plVar6 = (long *)param_1[8];
      plVar8 = plVar11;
      if ((long *)param_1[8] == (long *)0x0) {
code_r0x01634ab0:
        uStack_a8 = 0;
        uStack_a0 = 0;
        uStack_90 = 0;
        uStack_88 = 0;
        lStack_78 = 0;
        uStack_70 = 0;
        lStack_80 = 0;
        puStack_b8 = puVar2;
        puStack_b0 = &uStack_a8;
        puStack_98 = &uStack_90;
        lVar7 = std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned long, CDebugDropContentInfoList>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CDebugDropContentInfoList>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CDebugDropContentInfoList>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CDebugDropContentInfoList>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CDebugDropContentInfoList>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned long, unsigned long&, CDebugDropContentInfoList>(unsigned long const&, unsigned long&, CDebugDropContentInfoList&&)(param_1 + 7,&uStack_68,&uStack_68,&puStack_b8);
        lVar4 = lStack_80;
        if (lStack_80 != 0) {
          while (lStack_78 != lVar4) {
            lStack_78 = lStack_78 + -0x248;
            CDropContentInfo::~CDropContentInfo()();
          }
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(lStack_80);
        }
        puStack_b8 = puVar3;
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*)(&puStack_98,uStack_90);
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*)(&puStack_b0,uStack_a8);
        plVar10 = (long *)(lVar7 + 0x28);
        (**(code **)(*plVar10 + 0x10))(plVar10);
      }
      else {
        do {
          while (plVar10 = plVar6, uStack_68 <= (ulong)plVar10[4]) {
            plVar6 = (long *)*plVar10;
            plVar8 = plVar10;
            if ((long *)*plVar10 == (long *)0x0) {
              if (plVar10 != plVar11) goto code_r0x01634a94;
              goto code_r0x01634ab0;
            }
          }
          plVar6 = (long *)plVar10[1];
        } while ((long *)plVar10[1] != (long *)0x0);
        plVar10 = plVar8;
        if (plVar8 == plVar11) goto code_r0x01634ab0;
code_r0x01634a94:
        if ((uStack_68 < (ulong)plVar10[4]) || (plVar10 == plVar11)) goto code_r0x01634ab0;
        plVar10 = plVar10 + 5;
      }
      lVar4 = *param_2 + uVar9 * 0x40;
      iVar5 = *(int *)(lVar4 + 0x20);
      if (iVar5 == 6) {
        (**(code **)*plVar10)(plVar10,lVar4 + 0x28);
      }
      else if (iVar5 == 7) {
        (**(code **)(*plVar10 + 8))(plVar10,*param_2 + uVar9 * 0x40 + 0x28);
      }
      uVar1 = (int)uVar9 + 1;
      uVar9 = (ulong)uVar1;
    } while (uVar1 < *(uint *)(param_2 + 1));
  }
  return 1;
}

// ==== IInfoBaseMap<unsigned long, CWorldBossPlayerInfo>::DeserializeChild(Aska::ASON::AValue::AMap const*)
// vaddr 0x15360d4 | ghidra 0x16360d4 | size 436 | symbol _ZN12IInfoBaseMapIm20CWorldBossPlayerInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN12IInfoBaseMapIm20CWorldBossPlayerInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE
          (long *param_1,long *param_2)

{
  uint uVar1;
  int iVar2;
  long *plVar3;
  long lVar4;
  long *plVar5;
  ulong uVar6;
  long *plVar7;
  long *plVar8;
  undefined1 auStack_290 [584];
  ulong uStack_48;
  
  plVar8 = param_1 + 8;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CWorldBossPlayerInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CWorldBossPlayerInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CWorldBossPlayerInfo>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CWorldBossPlayerInfo>, void*>*)(param_1 + 7,*plVar8);
  param_1[7] = (long)plVar8;
  param_1[8] = 0;
  param_1[9] = 0;
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0282d54e/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\Info/InfoBase.h"*/,0x1c1,&UNK_027dc58a/*"apParser is null."*/);
    iVar2 = iRam0000000000000008;
  }
  else {
    iVar2 = (int)param_2[1];
  }
  if (iVar2 != 0) {
    uVar6 = 0;
    do {
      uStack_48 = (**(code **)(*param_1 + 0x20))(param_1,*param_2 + uVar6 * 0x40);
      plVar3 = (long *)param_1[8];
      plVar5 = plVar8;
      if ((long *)param_1[8] == (long *)0x0) {
code_r0x016361c8:
        memset(auStack_290,0,0x248);
        CWorldBossPlayerInfo::CWorldBossPlayerInfo()(auStack_290);
        lVar4 = std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned long, CWorldBossPlayerInfo>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CWorldBossPlayerInfo>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CWorldBossPlayerInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CWorldBossPlayerInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CWorldBossPlayerInfo>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned long, unsigned long&, CWorldBossPlayerInfo>(unsigned long const&, unsigned long&, CWorldBossPlayerInfo&&)(param_1 + 7,&uStack_48,&uStack_48,auStack_290);
        CWorldBossPlayerInfo::~CWorldBossPlayerInfo()(auStack_290);
        plVar7 = (long *)(lVar4 + 0x28);
        (**(code **)(*plVar7 + 0x10))(plVar7);
      }
      else {
        do {
          while (plVar7 = plVar3, (ulong)plVar7[4] < uStack_48) {
            plVar3 = (long *)plVar7[1];
            if ((long *)plVar7[1] == (long *)0x0) {
              plVar7 = plVar5;
              if (plVar5 != plVar8) goto code_r0x016361ac;
              goto code_r0x016361c8;
            }
          }
          plVar3 = (long *)*plVar7;
          plVar5 = plVar7;
        } while ((long *)*plVar7 != (long *)0x0);
        if (plVar7 == plVar8) goto code_r0x016361c8;
code_r0x016361ac:
        if ((uStack_48 < (ulong)plVar7[4]) || (plVar7 == plVar8)) goto code_r0x016361c8;
        plVar7 = plVar7 + 5;
      }
      lVar4 = *param_2 + uVar6 * 0x40;
      iVar2 = *(int *)(lVar4 + 0x20);
      if (iVar2 == 6) {
        (**(code **)*plVar7)(plVar7,lVar4 + 0x28);
      }
      else if (iVar2 == 7) {
        (**(code **)(*plVar7 + 8))(plVar7,*param_2 + uVar6 * 0x40 + 0x28);
      }
      uVar1 = (int)uVar6 + 1;
      uVar6 = (ulong)uVar1;
    } while (uVar1 < *(uint *)(param_2 + 1));
  }
  return 1;
}

// ==== IInfoBaseMap<unsigned long, CEquipWeaponResultPersonInfo>::DeserializeChild(Aska::ASON::AValue::AMap const*)
// vaddr 0x153b0e4 | ghidra 0x163b0e4 | size 932 | symbol _ZN12IInfoBaseMapIm28CEquipWeaponResultPersonInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Type propagation algorithm not settling */

undefined8
_ZN12IInfoBaseMapIm28CEquipWeaponResultPersonInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE
          (long *param_1,long *param_2)

{
  uint uVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined *puVar5;
  undefined *puVar6;
  undefined *puVar7;
  long lVar8;
  int iVar9;
  long *plVar10;
  long *******ppppppplVar11;
  long *******ppppppplVar12;
  ulong uVar13;
  long *******ppppppplVar14;
  long *******ppppppplVar15;
  long *******ppppppplVar16;
  undefined *puStack_120;
  undefined8 *puStack_118;
  undefined8 auStack_110 [2];
  undefined8 *puStack_100;
  undefined8 uStack_f8;
  undefined8 uStack_f0;
  undefined *puStack_e8;
  undefined8 uStack_e0;
  undefined1 uStack_d8;
  undefined1 auStack_d0 [24];
  undefined *puStack_b8;
  undefined8 uStack_b0;
  undefined1 uStack_a8;
  undefined1 auStack_a0 [24];
  long ******pppppplStack_88;
  long *******appppppplStack_80 [3];
  long *******ppppppplStack_68;
  
  ppppppplVar16 = (long *******)(param_1 + 8);
  plVar10 = param_1 + 7;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CEquipWeaponResultPersonInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CEquipWeaponResultPersonInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CEquipWeaponResultPersonInfo>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CEquipWeaponResultPersonInfo>, void*>*)(plVar10,*ppppppplVar16);
  param_1[7] = (long)ppppppplVar16;
  param_1[8] = 0;
  param_1[9] = 0;
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0282d54e/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\Info/InfoBase.h"*/,0x1c1,&UNK_027dc58a/*"apParser is null."*/);
    iVar9 = iRam0000000000000008;
  }
  else {
    iVar9 = (int)param_2[1];
  }
  if (iVar9 != 0) {
    puVar2 = PTR__ZTV28CEquipWeaponResultPersonInfo_02cbf0b8 + 0x10;
    puVar3 = PTR__ZTV22CParameterPropertyBaseILj13EE_02cba498 + 0x10;
    puVar4 = PTR__ZTV23CParameterPropertyValueImLj13E18CPropertyConverterE_02cb9810 + 0x10;
    puVar5 = PTR__ZTV22CParameterPropertyBaseILj14EE_02cb9db0 + 0x10;
    puVar6 = PTR__ZTV23CParameterPropertyValueImLj14E18CPropertyConverterE_02cc2760 + 0x10;
    uVar13 = 0;
    puVar7 = PTR__ZTV8InfoBase_02cc49c8 + 0x10;
    do {
      pppppplStack_88 =
           (long ******)(**(code **)(*param_1 + 0x20))(param_1,*param_2 + uVar13 * 0x40);
      ppppppplVar12 = (long *******)param_1[8];
      ppppppplVar11 = ppppppplVar16;
      if ((long *******)param_1[8] == (long *******)0x0) {
code_r0x0163b260:
        memset(auStack_110,0,0x88);
        uStack_f8 = 0;
        uStack_f0 = 0;
        uStack_d8 = 0;
        uStack_e0 = 0;
        puStack_120 = puVar2;
        puStack_118 = auStack_110;
        puStack_100 = &uStack_f8;
        puStack_e8 = puVar3;
        Framework::CHash32::CHash32()(auStack_d0);
        uStack_a8 = 0;
        uStack_b0 = 0;
        puStack_e8 = puVar4;
        puStack_b8 = puVar5;
        Framework::CHash32::CHash32()(auStack_a0);
        ppppppplVar12 = (long *******)*ppppppplVar16;
        if ((long *******)*ppppppplVar16 == (long *******)0x0) {
          ppppppplVar15 = (long *******)*ppppppplVar16;
          ppppppplVar11 = ppppppplVar16;
          ppppppplVar14 = ppppppplVar16;
        }
        else {
          do {
            while (ppppppplVar11 = ppppppplVar12, ppppppplVar11[4] <= pppppplStack_88) {
              if (pppppplStack_88 <= ppppppplVar11[4]) {
                ppppppplVar15 = ppppppplVar11;
                ppppppplVar14 = (long *******)&ppppppplStack_68;
                goto joined_r0x0163b32c;
              }
              ppppppplVar14 = ppppppplVar11 + 1;
              ppppppplVar12 = (long *******)*ppppppplVar14;
              if ((long *******)*ppppppplVar14 == (long *******)0x0) {
                ppppppplVar15 = (long *******)*ppppppplVar14;
                goto joined_r0x0163b32c;
              }
            }
            ppppppplVar12 = (long *******)*ppppppplVar11;
          } while ((long *******)*ppppppplVar11 != (long *******)0x0);
          ppppppplVar15 = (long *******)*ppppppplVar11;
          ppppppplVar14 = ppppppplVar11;
        }
joined_r0x0163b32c:
        ppppppplStack_68 = ppppppplVar11;
        if (ppppppplVar15 == (long *******)0x0) {
          puStack_b8 = puVar6;
          std::__ndk1::unique_ptr<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CEquipWeaponResultPersonInfo>, void*>, std::__ndk1::__tree_node_destructor<Framework::CSTLAllocator<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CEquipWeaponResultPersonInfo>, void*>, Framework::CSTLMapAllocatorInf> > > std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CEquipWeaponResultPersonInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CEquipWeaponResultPersonInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CEquipWeaponResultPersonInfo>, Framework::CSTLMapAllocatorInf> >::__construct_node<unsigned long&, CEquipWeaponResultPersonInfo>(unsigned long&, CEquipWeaponResultPersonInfo&&)(appppppplStack_80,plVar10,&pppppplStack_88,&puStack_120);
          *appppppplStack_80[0] = (long ******)0x0;
          appppppplStack_80[0][1] = (long ******)0x0;
          appppppplStack_80[0][2] = (long ******)ppppppplVar11;
          *ppppppplVar14 = (long ******)appppppplStack_80[0];
          ppppppplVar12 = appppppplStack_80[0];
          if (*(long *)*plVar10 != 0) {
            *plVar10 = *(long *)*plVar10;
            ppppppplVar12 = (long *******)*ppppppplVar14;
          }
          void std::__ndk1::__tree_balance_after_insert<std::__ndk1::__tree_node_base<void*>*>(std::__ndk1::__tree_node_base<void*>*, std::__ndk1::__tree_node_base<void*>*)(param_1[8],ppppppplVar12);
          param_1[9] = param_1[9] + 1;
          ppppppplVar15 = appppppplStack_80[0];
        }
        puStack_120 = PTR__ZTV28CEquipWeaponResultPersonInfo_02cbf0b8 + 0x10;
        puStack_b8 = PTR__ZTV22CParameterPropertyBaseILj14EE_02cb9db0 + 0x10;
        Framework::CHash32::~CHash32()(auStack_a0);
        puStack_e8 = PTR__ZTV22CParameterPropertyBaseILj13EE_02cba498 + 0x10;
        Framework::CHash32::~CHash32()(auStack_d0);
        puStack_120 = puVar7;
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*)(&puStack_100,uStack_f8);
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*)(&puStack_118,auStack_110[0]);
        ppppppplVar15 = ppppppplVar15 + 5;
        (*(code *)(*ppppppplVar15)[2])(ppppppplVar15);
      }
      else {
        do {
          while (ppppppplVar15 = ppppppplVar12, ppppppplVar15[4] < pppppplStack_88) {
            ppppppplVar12 = (long *******)ppppppplVar15[1];
            if ((long *******)ppppppplVar15[1] == (long *******)0x0) {
              ppppppplVar15 = ppppppplVar11;
              if (ppppppplVar11 != ppppppplVar16) goto code_r0x0163b244;
              goto code_r0x0163b260;
            }
          }
          ppppppplVar12 = (long *******)*ppppppplVar15;
          ppppppplVar11 = ppppppplVar15;
        } while ((long *******)*ppppppplVar15 != (long *******)0x0);
        if (ppppppplVar15 == ppppppplVar16) goto code_r0x0163b260;
code_r0x0163b244:
        if ((pppppplStack_88 < ppppppplVar15[4]) || (ppppppplVar15 == ppppppplVar16))
        goto code_r0x0163b260;
        ppppppplVar15 = ppppppplVar15 + 5;
      }
      lVar8 = *param_2 + uVar13 * 0x40;
      iVar9 = *(int *)(lVar8 + 0x20);
      if (iVar9 == 6) {
        (*(code *)**ppppppplVar15)(ppppppplVar15,lVar8 + 0x28);
      }
      else if (iVar9 == 7) {
        (*(code *)(*ppppppplVar15)[1])(ppppppplVar15,*param_2 + uVar13 * 0x40 + 0x28);
      }
      uVar1 = (int)uVar13 + 1;
      uVar13 = (ulong)uVar1;
    } while (uVar1 < *(uint *)(param_2 + 1));
  }
  return 1;
}

// ==== IInfoBaseMap<unsigned long, CEquipWeaponResultItemInfo>::DeserializeChild(Aska::ASON::AValue::AMap const*)
// vaddr 0x153b7cc | ghidra 0x163b7cc | size 596 | symbol _ZN12IInfoBaseMapIm26CEquipWeaponResultItemInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN12IInfoBaseMapIm26CEquipWeaponResultItemInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE
          (long *param_1,long *param_2)

{
  uint uVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined *puVar5;
  int iVar6;
  long *plVar7;
  long lVar8;
  long *plVar9;
  ulong uVar10;
  long *plVar11;
  long *plVar12;
  undefined *puStack_d0;
  undefined8 *puStack_c8;
  undefined8 auStack_c0 [2];
  undefined8 *puStack_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined *puStack_98;
  undefined8 uStack_90;
  undefined1 uStack_88;
  undefined1 auStack_80 [24];
  ulong uStack_68;
  
  plVar12 = param_1 + 8;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CEquipWeaponResultItemInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CEquipWeaponResultItemInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CEquipWeaponResultItemInfo>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CEquipWeaponResultItemInfo>, void*>*)(param_1 + 7,*plVar12);
  param_1[7] = (long)plVar12;
  param_1[8] = 0;
  param_1[9] = 0;
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0282d54e/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\Info/InfoBase.h"*/,0x1c1,&UNK_027dc58a/*"apParser is null."*/);
    iVar6 = iRam0000000000000008;
  }
  else {
    iVar6 = (int)param_2[1];
  }
  if (iVar6 != 0) {
    uVar10 = 0;
    puVar2 = PTR__ZTV26CEquipWeaponResultItemInfo_02cbde00 + 0x10;
    puVar3 = PTR__ZTV22CParameterPropertyBaseILj35EE_02cc13f0 + 0x10;
    puVar4 = PTR__ZTV23CParameterPropertyValueIjLj35E18CPropertyConverterE_02cb7f18 + 0x10;
    puVar5 = PTR__ZTV8InfoBase_02cc49c8 + 0x10;
    do {
      uStack_68 = (**(code **)(*param_1 + 0x20))(param_1,*param_2 + uVar10 * 0x40);
      plVar7 = (long *)param_1[8];
      plVar9 = plVar12;
      if ((long *)param_1[8] == (long *)0x0) {
code_r0x0163b918:
        memset(auStack_c0,0,0x58);
        uStack_a8 = 0;
        uStack_a0 = 0;
        uStack_90 = 0;
        uStack_88 = 0;
        puStack_d0 = puVar2;
        puStack_c8 = auStack_c0;
        puStack_b0 = &uStack_a8;
        puStack_98 = puVar3;
        Framework::CHash32::CHash32()(auStack_80);
        puStack_98 = puVar4;
        lVar8 = std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned long, CEquipWeaponResultItemInfo>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CEquipWeaponResultItemInfo>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CEquipWeaponResultItemInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CEquipWeaponResultItemInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CEquipWeaponResultItemInfo>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned long, unsigned long&, CEquipWeaponResultItemInfo>(unsigned long const&, unsigned long&, CEquipWeaponResultItemInfo&&)(param_1 + 7,&uStack_68,&uStack_68,&puStack_d0);
        puStack_d0 = puVar2;
        puStack_98 = puVar3;
        Framework::CHash32::~CHash32()(auStack_80);
        puStack_d0 = puVar5;
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*)(&puStack_b0,uStack_a8);
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*)(&puStack_c8,auStack_c0[0]);
        plVar11 = (long *)(lVar8 + 0x28);
        (**(code **)(*plVar11 + 0x10))(plVar11);
      }
      else {
        do {
          while (plVar11 = plVar7, (ulong)plVar11[4] < uStack_68) {
            plVar7 = (long *)plVar11[1];
            if ((long *)plVar11[1] == (long *)0x0) {
              plVar11 = plVar9;
              if (plVar9 != plVar12) goto code_r0x0163b8fc;
              goto code_r0x0163b918;
            }
          }
          plVar7 = (long *)*plVar11;
          plVar9 = plVar11;
        } while ((long *)*plVar11 != (long *)0x0);
        if (plVar11 == plVar12) goto code_r0x0163b918;
code_r0x0163b8fc:
        if ((uStack_68 < (ulong)plVar11[4]) || (plVar11 == plVar12)) goto code_r0x0163b918;
        plVar11 = plVar11 + 5;
      }
      lVar8 = *param_2 + uVar10 * 0x40;
      iVar6 = *(int *)(lVar8 + 0x20);
      if (iVar6 == 6) {
        (**(code **)*plVar11)(plVar11,lVar8 + 0x28);
      }
      else if (iVar6 == 7) {
        (**(code **)(*plVar11 + 8))(plVar11,*param_2 + uVar10 * 0x40 + 0x28);
      }
      uVar1 = (int)uVar10 + 1;
      uVar10 = (ulong)uVar1;
    } while (uVar1 < *(uint *)(param_2 + 1));
  }
  return 1;
}

// ==== IInfoBaseMap<unsigned long, CEquipAccessoryResultPersonInfo>::DeserializeChild(Aska::ASON::AValue::AMap const*)
// vaddr 0x153bea8 | ghidra 0x163bea8 | size 932 | symbol _ZN12IInfoBaseMapIm31CEquipAccessoryResultPersonInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Type propagation algorithm not settling */

undefined8
_ZN12IInfoBaseMapIm31CEquipAccessoryResultPersonInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE
          (long *param_1,long *param_2)

{
  uint uVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined *puVar5;
  undefined *puVar6;
  undefined *puVar7;
  long lVar8;
  int iVar9;
  long *plVar10;
  long *******ppppppplVar11;
  long *******ppppppplVar12;
  ulong uVar13;
  long *******ppppppplVar14;
  long *******ppppppplVar15;
  long *******ppppppplVar16;
  undefined *puStack_120;
  undefined8 *puStack_118;
  undefined8 auStack_110 [2];
  undefined8 *puStack_100;
  undefined8 uStack_f8;
  undefined8 uStack_f0;
  undefined *puStack_e8;
  undefined8 uStack_e0;
  undefined1 uStack_d8;
  undefined1 auStack_d0 [24];
  undefined *puStack_b8;
  undefined8 uStack_b0;
  undefined1 uStack_a8;
  undefined1 auStack_a0 [24];
  long ******pppppplStack_88;
  long *******appppppplStack_80 [3];
  long *******ppppppplStack_68;
  
  ppppppplVar16 = (long *******)(param_1 + 8);
  plVar10 = param_1 + 7;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CEquipAccessoryResultPersonInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CEquipAccessoryResultPersonInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CEquipAccessoryResultPersonInfo>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CEquipAccessoryResultPersonInfo>, void*>*)(plVar10,*ppppppplVar16);
  param_1[7] = (long)ppppppplVar16;
  param_1[8] = 0;
  param_1[9] = 0;
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0282d54e/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\Info/InfoBase.h"*/,0x1c1,&UNK_027dc58a/*"apParser is null."*/);
    iVar9 = iRam0000000000000008;
  }
  else {
    iVar9 = (int)param_2[1];
  }
  if (iVar9 != 0) {
    puVar2 = PTR__ZTV31CEquipAccessoryResultPersonInfo_02cb8200 + 0x10;
    puVar3 = PTR__ZTV22CParameterPropertyBaseILj13EE_02cba498 + 0x10;
    puVar4 = PTR__ZTV23CParameterPropertyValueImLj13E18CPropertyConverterE_02cb9810 + 0x10;
    puVar5 = PTR__ZTV22CParameterPropertyBaseILj14EE_02cb9db0 + 0x10;
    puVar6 = PTR__ZTV23CParameterPropertyValueImLj14E18CPropertyConverterE_02cc2760 + 0x10;
    uVar13 = 0;
    puVar7 = PTR__ZTV8InfoBase_02cc49c8 + 0x10;
    do {
      pppppplStack_88 =
           (long ******)(**(code **)(*param_1 + 0x20))(param_1,*param_2 + uVar13 * 0x40);
      ppppppplVar12 = (long *******)param_1[8];
      ppppppplVar11 = ppppppplVar16;
      if ((long *******)param_1[8] == (long *******)0x0) {
code_r0x0163c024:
        memset(auStack_110,0,0x88);
        uStack_f8 = 0;
        uStack_f0 = 0;
        uStack_d8 = 0;
        uStack_e0 = 0;
        puStack_120 = puVar2;
        puStack_118 = auStack_110;
        puStack_100 = &uStack_f8;
        puStack_e8 = puVar3;
        Framework::CHash32::CHash32()(auStack_d0);
        uStack_a8 = 0;
        uStack_b0 = 0;
        puStack_e8 = puVar4;
        puStack_b8 = puVar5;
        Framework::CHash32::CHash32()(auStack_a0);
        ppppppplVar12 = (long *******)*ppppppplVar16;
        if ((long *******)*ppppppplVar16 == (long *******)0x0) {
          ppppppplVar15 = (long *******)*ppppppplVar16;
          ppppppplVar11 = ppppppplVar16;
          ppppppplVar14 = ppppppplVar16;
        }
        else {
          do {
            while (ppppppplVar11 = ppppppplVar12, ppppppplVar11[4] <= pppppplStack_88) {
              if (pppppplStack_88 <= ppppppplVar11[4]) {
                ppppppplVar15 = ppppppplVar11;
                ppppppplVar14 = (long *******)&ppppppplStack_68;
                goto joined_r0x0163c0f0;
              }
              ppppppplVar14 = ppppppplVar11 + 1;
              ppppppplVar12 = (long *******)*ppppppplVar14;
              if ((long *******)*ppppppplVar14 == (long *******)0x0) {
                ppppppplVar15 = (long *******)*ppppppplVar14;
                goto joined_r0x0163c0f0;
              }
            }
            ppppppplVar12 = (long *******)*ppppppplVar11;
          } while ((long *******)*ppppppplVar11 != (long *******)0x0);
          ppppppplVar15 = (long *******)*ppppppplVar11;
          ppppppplVar14 = ppppppplVar11;
        }
joined_r0x0163c0f0:
        ppppppplStack_68 = ppppppplVar11;
        if (ppppppplVar15 == (long *******)0x0) {
          puStack_b8 = puVar6;
          std::__ndk1::unique_ptr<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CEquipAccessoryResultPersonInfo>, void*>, std::__ndk1::__tree_node_destructor<Framework::CSTLAllocator<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CEquipAccessoryResultPersonInfo>, void*>, Framework::CSTLMapAllocatorInf> > > std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CEquipAccessoryResultPersonInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CEquipAccessoryResultPersonInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CEquipAccessoryResultPersonInfo>, Framework::CSTLMapAllocatorInf> >::__construct_node<unsigned long&, CEquipAccessoryResultPersonInfo>(unsigned long&, CEquipAccessoryResultPersonInfo&&)(appppppplStack_80,plVar10,&pppppplStack_88,&puStack_120);
          *appppppplStack_80[0] = (long ******)0x0;
          appppppplStack_80[0][1] = (long ******)0x0;
          appppppplStack_80[0][2] = (long ******)ppppppplVar11;
          *ppppppplVar14 = (long ******)appppppplStack_80[0];
          ppppppplVar12 = appppppplStack_80[0];
          if (*(long *)*plVar10 != 0) {
            *plVar10 = *(long *)*plVar10;
            ppppppplVar12 = (long *******)*ppppppplVar14;
          }
          void std::__ndk1::__tree_balance_after_insert<std::__ndk1::__tree_node_base<void*>*>(std::__ndk1::__tree_node_base<void*>*, std::__ndk1::__tree_node_base<void*>*)(param_1[8],ppppppplVar12);
          param_1[9] = param_1[9] + 1;
          ppppppplVar15 = appppppplStack_80[0];
        }
        puStack_120 = PTR__ZTV31CEquipAccessoryResultPersonInfo_02cb8200 + 0x10;
        puStack_b8 = PTR__ZTV22CParameterPropertyBaseILj14EE_02cb9db0 + 0x10;
        Framework::CHash32::~CHash32()(auStack_a0);
        puStack_e8 = PTR__ZTV22CParameterPropertyBaseILj13EE_02cba498 + 0x10;
        Framework::CHash32::~CHash32()(auStack_d0);
        puStack_120 = puVar7;
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*)(&puStack_100,uStack_f8);
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*)(&puStack_118,auStack_110[0]);
        ppppppplVar15 = ppppppplVar15 + 5;
        (*(code *)(*ppppppplVar15)[2])(ppppppplVar15);
      }
      else {
        do {
          while (ppppppplVar15 = ppppppplVar12, ppppppplVar15[4] < pppppplStack_88) {
            ppppppplVar12 = (long *******)ppppppplVar15[1];
            if ((long *******)ppppppplVar15[1] == (long *******)0x0) {
              ppppppplVar15 = ppppppplVar11;
              if (ppppppplVar11 != ppppppplVar16) goto code_r0x0163c008;
              goto code_r0x0163c024;
            }
          }
          ppppppplVar12 = (long *******)*ppppppplVar15;
          ppppppplVar11 = ppppppplVar15;
        } while ((long *******)*ppppppplVar15 != (long *******)0x0);
        if (ppppppplVar15 == ppppppplVar16) goto code_r0x0163c024;
code_r0x0163c008:
        if ((pppppplStack_88 < ppppppplVar15[4]) || (ppppppplVar15 == ppppppplVar16))
        goto code_r0x0163c024;
        ppppppplVar15 = ppppppplVar15 + 5;
      }
      lVar8 = *param_2 + uVar13 * 0x40;
      iVar9 = *(int *)(lVar8 + 0x20);
      if (iVar9 == 6) {
        (*(code *)**ppppppplVar15)(ppppppplVar15,lVar8 + 0x28);
      }
      else if (iVar9 == 7) {
        (*(code *)(*ppppppplVar15)[1])(ppppppplVar15,*param_2 + uVar13 * 0x40 + 0x28);
      }
      uVar1 = (int)uVar13 + 1;
      uVar13 = (ulong)uVar1;
    } while (uVar1 < *(uint *)(param_2 + 1));
  }
  return 1;
}

// ==== IInfoBaseMap<unsigned long, CEquipAccessoryResultItemInfo>::DeserializeChild(Aska::ASON::AValue::AMap const*)
// vaddr 0x153c590 | ghidra 0x163c590 | size 596 | symbol _ZN12IInfoBaseMapIm29CEquipAccessoryResultItemInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN12IInfoBaseMapIm29CEquipAccessoryResultItemInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE
          (long *param_1,long *param_2)

{
  uint uVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined *puVar5;
  int iVar6;
  long *plVar7;
  long lVar8;
  long *plVar9;
  ulong uVar10;
  long *plVar11;
  long *plVar12;
  undefined *puStack_d0;
  undefined8 *puStack_c8;
  undefined8 auStack_c0 [2];
  undefined8 *puStack_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined *puStack_98;
  undefined8 uStack_90;
  undefined1 uStack_88;
  undefined1 auStack_80 [24];
  ulong uStack_68;
  
  plVar12 = param_1 + 8;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CEquipAccessoryResultItemInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CEquipAccessoryResultItemInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CEquipAccessoryResultItemInfo>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CEquipAccessoryResultItemInfo>, void*>*)(param_1 + 7,*plVar12);
  param_1[7] = (long)plVar12;
  param_1[8] = 0;
  param_1[9] = 0;
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0282d54e/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\Info/InfoBase.h"*/,0x1c1,&UNK_027dc58a/*"apParser is null."*/);
    iVar6 = iRam0000000000000008;
  }
  else {
    iVar6 = (int)param_2[1];
  }
  if (iVar6 != 0) {
    uVar10 = 0;
    puVar2 = PTR__ZTV29CEquipAccessoryResultItemInfo_02cb8f90 + 0x10;
    puVar3 = PTR__ZTV22CParameterPropertyBaseILj35EE_02cc13f0 + 0x10;
    puVar4 = PTR__ZTV23CParameterPropertyValueIjLj35E18CPropertyConverterE_02cb7f18 + 0x10;
    puVar5 = PTR__ZTV8InfoBase_02cc49c8 + 0x10;
    do {
      uStack_68 = (**(code **)(*param_1 + 0x20))(param_1,*param_2 + uVar10 * 0x40);
      plVar7 = (long *)param_1[8];
      plVar9 = plVar12;
      if ((long *)param_1[8] == (long *)0x0) {
code_r0x0163c6dc:
        memset(auStack_c0,0,0x58);
        uStack_a8 = 0;
        uStack_a0 = 0;
        uStack_90 = 0;
        uStack_88 = 0;
        puStack_d0 = puVar2;
        puStack_c8 = auStack_c0;
        puStack_b0 = &uStack_a8;
        puStack_98 = puVar3;
        Framework::CHash32::CHash32()(auStack_80);
        puStack_98 = puVar4;
        lVar8 = std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned long, CEquipAccessoryResultItemInfo>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CEquipAccessoryResultItemInfo>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CEquipAccessoryResultItemInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CEquipAccessoryResultItemInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CEquipAccessoryResultItemInfo>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned long, unsigned long&, CEquipAccessoryResultItemInfo>(unsigned long const&, unsigned long&, CEquipAccessoryResultItemInfo&&)(param_1 + 7,&uStack_68,&uStack_68,&puStack_d0);
        puStack_d0 = puVar2;
        puStack_98 = puVar3;
        Framework::CHash32::~CHash32()(auStack_80);
        puStack_d0 = puVar5;
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*)(&puStack_b0,uStack_a8);
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*)(&puStack_c8,auStack_c0[0]);
        plVar11 = (long *)(lVar8 + 0x28);
        (**(code **)(*plVar11 + 0x10))(plVar11);
      }
      else {
        do {
          while (plVar11 = plVar7, (ulong)plVar11[4] < uStack_68) {
            plVar7 = (long *)plVar11[1];
            if ((long *)plVar11[1] == (long *)0x0) {
              plVar11 = plVar9;
              if (plVar9 != plVar12) goto code_r0x0163c6c0;
              goto code_r0x0163c6dc;
            }
          }
          plVar7 = (long *)*plVar11;
          plVar9 = plVar11;
        } while ((long *)*plVar11 != (long *)0x0);
        if (plVar11 == plVar12) goto code_r0x0163c6dc;
code_r0x0163c6c0:
        if ((uStack_68 < (ulong)plVar11[4]) || (plVar11 == plVar12)) goto code_r0x0163c6dc;
        plVar11 = plVar11 + 5;
      }
      lVar8 = *param_2 + uVar10 * 0x40;
      iVar6 = *(int *)(lVar8 + 0x20);
      if (iVar6 == 6) {
        (**(code **)*plVar11)(plVar11,lVar8 + 0x28);
      }
      else if (iVar6 == 7) {
        (**(code **)(*plVar11 + 8))(plVar11,*param_2 + uVar10 * 0x40 + 0x28);
      }
      uVar1 = (int)uVar10 + 1;
      uVar10 = (ulong)uVar1;
    } while (uVar1 < *(uint *)(param_2 + 1));
  }
  return 1;
}

// ==== IInfoBaseMap<unsigned long, CItemInfo>::DeserializeChild(Aska::ASON::AValue::AMap const*)
// vaddr 0x153d57c | ghidra 0x163d57c | size 436 | symbol _ZN12IInfoBaseMapIm9CItemInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN12IInfoBaseMapIm9CItemInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE
          (long *param_1,long *param_2)

{
  uint uVar1;
  int iVar2;
  long *plVar3;
  long lVar4;
  long *plVar5;
  ulong uVar6;
  long *plVar7;
  long *plVar8;
  undefined1 auStack_378 [816];
  ulong uStack_48;
  
  plVar8 = param_1 + 8;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CItemInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CItemInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CItemInfo>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CItemInfo>, void*>*)(param_1 + 7,*plVar8);
  param_1[7] = (long)plVar8;
  param_1[8] = 0;
  param_1[9] = 0;
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0282d54e/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\Info/InfoBase.h"*/,0x1c1,&UNK_027dc58a/*"apParser is null."*/);
    iVar2 = iRam0000000000000008;
  }
  else {
    iVar2 = (int)param_2[1];
  }
  if (iVar2 != 0) {
    uVar6 = 0;
    do {
      uStack_48 = (**(code **)(*param_1 + 0x20))(param_1,*param_2 + uVar6 * 0x40);
      plVar3 = (long *)param_1[8];
      plVar5 = plVar8;
      if ((long *)param_1[8] == (long *)0x0) {
code_r0x0163d670:
        memset(auStack_378,0,0x330);
        CItemInfo::CItemInfo()(auStack_378);
        lVar4 = std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned long, CItemInfo>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CItemInfo>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CItemInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CItemInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CItemInfo>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned long, unsigned long&, CItemInfo>(unsigned long const&, unsigned long&, CItemInfo&&)(param_1 + 7,&uStack_48,&uStack_48,auStack_378);
        CItemInfo::~CItemInfo()(auStack_378);
        plVar7 = (long *)(lVar4 + 0x28);
        (**(code **)(*plVar7 + 0x10))(plVar7);
      }
      else {
        do {
          while (plVar7 = plVar3, (ulong)plVar7[4] < uStack_48) {
            plVar3 = (long *)plVar7[1];
            if ((long *)plVar7[1] == (long *)0x0) {
              plVar7 = plVar5;
              if (plVar5 != plVar8) goto code_r0x0163d654;
              goto code_r0x0163d670;
            }
          }
          plVar3 = (long *)*plVar7;
          plVar5 = plVar7;
        } while ((long *)*plVar7 != (long *)0x0);
        if (plVar7 == plVar8) goto code_r0x0163d670;
code_r0x0163d654:
        if ((uStack_48 < (ulong)plVar7[4]) || (plVar7 == plVar8)) goto code_r0x0163d670;
        plVar7 = plVar7 + 5;
      }
      lVar4 = *param_2 + uVar6 * 0x40;
      iVar2 = *(int *)(lVar4 + 0x20);
      if (iVar2 == 6) {
        (**(code **)*plVar7)(plVar7,lVar4 + 0x28);
      }
      else if (iVar2 == 7) {
        (**(code **)(*plVar7 + 8))(plVar7,*param_2 + uVar6 * 0x40 + 0x28);
      }
      uVar1 = (int)uVar6 + 1;
      uVar6 = (ulong)uVar1;
    } while (uVar1 < *(uint *)(param_2 + 1));
  }
  return 1;
}

// ==== IInfoBaseMap<unsigned long, CPersonInfo>::DeserializeChild(Aska::ASON::AValue::AMap const*)
// vaddr 0x153defc | ghidra 0x163defc | size 436 | symbol _ZN12IInfoBaseMapIm11CPersonInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN12IInfoBaseMapIm11CPersonInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE
          (long *param_1,long *param_2)

{
  uint uVar1;
  int iVar2;
  long *plVar3;
  long lVar4;
  long *plVar5;
  ulong uVar6;
  long *plVar7;
  long *plVar8;
  undefined1 auStack_bd0 [2952];
  ulong uStack_48;
  
  plVar8 = param_1 + 8;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CPersonInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CPersonInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CPersonInfo>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CPersonInfo>, void*>*)(param_1 + 7,*plVar8);
  param_1[7] = (long)plVar8;
  param_1[8] = 0;
  param_1[9] = 0;
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0282d54e/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\Info/InfoBase.h"*/,0x1c1,&UNK_027dc58a/*"apParser is null."*/);
    iVar2 = iRam0000000000000008;
  }
  else {
    iVar2 = (int)param_2[1];
  }
  if (iVar2 != 0) {
    uVar6 = 0;
    do {
      uStack_48 = (**(code **)(*param_1 + 0x20))(param_1,*param_2 + uVar6 * 0x40);
      plVar3 = (long *)param_1[8];
      plVar5 = plVar8;
      if ((long *)param_1[8] == (long *)0x0) {
code_r0x0163dff0:
        memset(auStack_bd0,0,0xb88);
        CPersonInfo::CPersonInfo()(auStack_bd0);
        lVar4 = std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned long, CPersonInfo>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CPersonInfo>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CPersonInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CPersonInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CPersonInfo>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned long, unsigned long&, CPersonInfo>(unsigned long const&, unsigned long&, CPersonInfo&&)(param_1 + 7,&uStack_48,&uStack_48,auStack_bd0);
        CPersonInfo::~CPersonInfo()(auStack_bd0);
        plVar7 = (long *)(lVar4 + 0x28);
        (**(code **)(*plVar7 + 0x10))(plVar7);
      }
      else {
        do {
          while (plVar7 = plVar3, (ulong)plVar7[4] < uStack_48) {
            plVar3 = (long *)plVar7[1];
            if ((long *)plVar7[1] == (long *)0x0) {
              plVar7 = plVar5;
              if (plVar5 != plVar8) goto code_r0x0163dfd4;
              goto code_r0x0163dff0;
            }
          }
          plVar3 = (long *)*plVar7;
          plVar5 = plVar7;
        } while ((long *)*plVar7 != (long *)0x0);
        if (plVar7 == plVar8) goto code_r0x0163dff0;
code_r0x0163dfd4:
        if ((uStack_48 < (ulong)plVar7[4]) || (plVar7 == plVar8)) goto code_r0x0163dff0;
        plVar7 = plVar7 + 5;
      }
      lVar4 = *param_2 + uVar6 * 0x40;
      iVar2 = *(int *)(lVar4 + 0x20);
      if (iVar2 == 6) {
        (**(code **)*plVar7)(plVar7,lVar4 + 0x28);
      }
      else if (iVar2 == 7) {
        (**(code **)(*plVar7 + 8))(plVar7,*param_2 + uVar6 * 0x40 + 0x28);
      }
      uVar1 = (int)uVar6 + 1;
      uVar6 = (ulong)uVar1;
    } while (uVar1 < *(uint *)(param_2 + 1));
  }
  return 1;
}

// ==== IInfoBaseMap<unsigned long, CGachaHashInfoListInfo>::DeserializeChild(Aska::ASON::AValue::AMap const*)
// vaddr 0x1543fbc | ghidra 0x1643fbc | size 912 | symbol _ZN12IInfoBaseMapIm22CGachaHashInfoListInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Type propagation algorithm not settling */

undefined8
_ZN12IInfoBaseMapIm22CGachaHashInfoListInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE
          (long *param_1,long *param_2)

{
  long *******ppppppplVar1;
  uint uVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined *puVar5;
  long lVar6;
  int iVar7;
  long *plVar8;
  long *******ppppppplVar9;
  ulong uVar10;
  long *******ppppppplVar11;
  long *******ppppppplVar12;
  long *******ppppppplVar13;
  long *******ppppppplVar14;
  undefined *puStack_110;
  undefined8 *puStack_108;
  undefined8 uStack_100;
  undefined8 uStack_f8;
  undefined8 *puStack_f0;
  undefined8 uStack_e8;
  undefined8 uStack_e0;
  undefined *puStack_d8;
  undefined8 *puStack_d0;
  undefined8 uStack_c8;
  undefined8 uStack_c0;
  undefined8 *puStack_b8;
  undefined8 uStack_b0;
  undefined8 uStack_a8;
  long lStack_a0;
  long lStack_98;
  undefined8 uStack_90;
  long ******pppppplStack_88;
  long *******appppppplStack_80 [3];
  long *******ppppppplStack_68;
  
  ppppppplVar11 = (long *******)(param_1 + 8);
  plVar8 = param_1 + 7;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CGachaHashInfoListInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CGachaHashInfoListInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CGachaHashInfoListInfo>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CGachaHashInfoListInfo>, void*>*)(plVar8,*ppppppplVar11);
  param_1[7] = (long)ppppppplVar11;
  param_1[8] = 0;
  param_1[9] = 0;
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0282d54e/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\Info/InfoBase.h"*/,0x1c1,&UNK_027dc58a/*"apParser is null."*/);
    iVar7 = iRam0000000000000008;
  }
  else {
    iVar7 = (int)param_2[1];
  }
  if (iVar7 != 0) {
    puVar3 = PTR__ZTV22CGachaHashInfoListInfo_02cc1618 + 0x10;
    puVar4 = PTR__ZTV18CGachaHashInfoList_02cc0eb8 + 0x10;
    uVar10 = 0;
    puVar5 = PTR__ZTV8InfoBase_02cc49c8 + 0x10;
    do {
      pppppplStack_88 =
           (long ******)(**(code **)(*param_1 + 0x20))(param_1,*param_2 + uVar10 * 0x40);
      ppppppplVar14 = (long *******)param_1[8];
      ppppppplVar13 = ppppppplVar14;
      ppppppplVar9 = ppppppplVar11;
      if (ppppppplVar14 == (long *******)0x0) {
code_r0x01644124:
        uStack_100 = 0;
        uStack_f8 = 0;
        uStack_e8 = 0;
        uStack_e0 = 0;
        uStack_c8 = 0;
        uStack_c0 = 0;
        uStack_b0 = 0;
        uStack_a8 = 0;
        lStack_98 = 0;
        uStack_90 = 0;
        lStack_a0 = 0;
        puStack_108 = &uStack_100;
        puStack_f0 = &uStack_e8;
        puStack_d0 = &uStack_c8;
        puStack_b8 = &uStack_b0;
        if (ppppppplVar14 == (long *******)0x0) {
          ppppppplVar12 = (long *******)*ppppppplVar11;
          ppppppplVar13 = ppppppplVar11;
          ppppppplStack_68 = ppppppplVar11;
joined_r0x016441e0:
          if (ppppppplVar12 != (long *******)0x0) goto code_r0x0164416c;
code_r0x016441e4:
          ppppppplVar14 = ppppppplStack_68;
          puStack_110 = puVar3;
          puStack_d8 = puVar4;
          std::__ndk1::unique_ptr<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CGachaHashInfoListInfo>, void*>, std::__ndk1::__tree_node_destructor<Framework::CSTLAllocator<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CGachaHashInfoListInfo>, void*>, Framework::CSTLMapAllocatorInf> > > std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CGachaHashInfoListInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CGachaHashInfoListInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CGachaHashInfoListInfo>, Framework::CSTLMapAllocatorInf> >::__construct_node<unsigned long&, CGachaHashInfoListInfo>(unsigned long&, CGachaHashInfoListInfo&&)(appppppplStack_80,plVar8,&pppppplStack_88,&puStack_110);
          *appppppplStack_80[0] = (long ******)0x0;
          appppppplStack_80[0][1] = (long ******)0x0;
          appppppplStack_80[0][2] = (long ******)ppppppplVar14;
          *ppppppplVar13 = (long ******)appppppplStack_80[0];
          ppppppplVar14 = appppppplStack_80[0];
          if (*(long *)*plVar8 != 0) {
            *plVar8 = *(long *)*plVar8;
            ppppppplVar14 = (long *******)*ppppppplVar13;
          }
          void std::__ndk1::__tree_balance_after_insert<std::__ndk1::__tree_node_base<void*>*>(std::__ndk1::__tree_node_base<void*>*, std::__ndk1::__tree_node_base<void*>*)(param_1[8],ppppppplVar14);
          ppppppplVar12 = appppppplStack_80[0];
          lVar6 = lStack_a0;
          param_1[9] = param_1[9] + 1;
          puStack_110 = PTR__ZTV22CGachaHashInfoListInfo_02cc1618 + 0x10;
          if (lStack_a0 != 0) {
            while (lStack_98 != lVar6) {
              lStack_98 = lStack_98 + -0x128;
              CGachaHashInfo::~CGachaHashInfo()();
            }
            Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(lStack_a0);
          }
        }
        else {
          do {
            while (ppppppplStack_68 = ppppppplVar14, pppppplStack_88 < ppppppplStack_68[4]) {
              ppppppplVar14 = (long *******)*ppppppplStack_68;
              if ((long *******)*ppppppplStack_68 == (long *******)0x0) {
                ppppppplVar12 = (long *******)*ppppppplStack_68;
                ppppppplVar13 = ppppppplStack_68;
                goto joined_r0x016441b8;
              }
            }
            if (pppppplStack_88 <= ppppppplStack_68[4]) {
              ppppppplVar13 = (long *******)&ppppppplStack_68;
              ppppppplVar12 = ppppppplStack_68;
              goto joined_r0x016441e0;
            }
            ppppppplVar13 = ppppppplStack_68 + 1;
            ppppppplVar14 = (long *******)*ppppppplVar13;
          } while ((long *******)*ppppppplVar13 != (long *******)0x0);
          ppppppplVar12 = (long *******)*ppppppplVar13;
joined_r0x016441b8:
          if (ppppppplVar12 == (long *******)0x0) goto code_r0x016441e4;
code_r0x0164416c:
          puStack_110 = PTR__ZTV22CGachaHashInfoListInfo_02cc1618 + 0x10;
        }
        puStack_d8 = puVar5;
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*)(&puStack_b8,uStack_b0);
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*)(&puStack_d0,uStack_c8);
        puStack_110 = puVar5;
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*)(&puStack_f0,uStack_e8);
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*)(&puStack_108,uStack_100);
        ppppppplVar12 = ppppppplVar12 + 5;
        (*(code *)(*ppppppplVar12)[2])(ppppppplVar12);
      }
      else {
        do {
          while (ppppppplVar12 = ppppppplVar13, pppppplStack_88 <= ppppppplVar12[4]) {
            ppppppplVar13 = (long *******)*ppppppplVar12;
            ppppppplVar9 = ppppppplVar12;
            if ((long *******)*ppppppplVar12 == (long *******)0x0) goto code_r0x016440f8;
          }
          ppppppplVar1 = ppppppplVar12 + 1;
          ppppppplVar12 = ppppppplVar9;
          ppppppplVar13 = (long *******)*ppppppplVar1;
        } while ((long *******)*ppppppplVar1 != (long *******)0x0);
code_r0x016440f8:
        if (((ppppppplVar12 == ppppppplVar11) || (pppppplStack_88 < ppppppplVar12[4])) ||
           (ppppppplVar12 == ppppppplVar11)) goto code_r0x01644124;
        ppppppplVar12 = ppppppplVar12 + 5;
      }
      lVar6 = *param_2 + uVar10 * 0x40;
      iVar7 = *(int *)(lVar6 + 0x20);
      if (iVar7 == 6) {
        (*(code *)**ppppppplVar12)(ppppppplVar12,lVar6 + 0x28);
      }
      else if (iVar7 == 7) {
        (*(code *)(*ppppppplVar12)[1])(ppppppplVar12,*param_2 + uVar10 * 0x40 + 0x28);
      }
      uVar2 = (int)uVar10 + 1;
      uVar10 = (ulong)uVar2;
    } while (uVar2 < *(uint *)(param_2 + 1));
  }
  return 1;
}

// ==== IInfoBaseMap<unsigned long, CExchangeShopExCountInfoCategory>::DeserializeChild(Aska::ASON::AValue::AMap const*)
// vaddr 0x1549ea0 | ghidra 0x1649ea0 | size 792 | symbol _ZN12IInfoBaseMapIm32CExchangeShopExCountInfoCategoryE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Type propagation algorithm not settling */

undefined8
_ZN12IInfoBaseMapIm32CExchangeShopExCountInfoCategoryE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE
          (long *param_1,long *param_2)

{
  uint uVar1;
  undefined *puVar2;
  undefined *puVar3;
  long lVar4;
  int iVar5;
  undefined *puVar6;
  long *plVar7;
  long *******ppppppplVar8;
  ulong uVar9;
  long *******ppppppplVar10;
  long *******ppppppplVar11;
  long *******ppppppplVar12;
  long *******ppppppplVar13;
  undefined *puStack_d8;
  undefined8 *puStack_d0;
  undefined8 uStack_c8;
  undefined8 uStack_c0;
  undefined8 *puStack_b8;
  undefined8 uStack_b0;
  undefined8 uStack_a8;
  undefined8 *puStack_a0;
  undefined8 uStack_98;
  undefined8 uStack_90;
  long ******pppppplStack_88;
  long *******appppppplStack_80 [3];
  long *******ppppppplStack_68;
  
  ppppppplVar13 = (long *******)(param_1 + 8);
  plVar7 = param_1 + 7;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CExchangeShopExCountInfoCategory>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CExchangeShopExCountInfoCategory>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CExchangeShopExCountInfoCategory>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CExchangeShopExCountInfoCategory>, void*>*)(plVar7,*ppppppplVar13);
  param_1[7] = (long)ppppppplVar13;
  param_1[8] = 0;
  param_1[9] = 0;
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0282d54e/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\Info/InfoBase.h"*/,0x1c1,&UNK_027dc58a/*"apParser is null."*/);
    iVar5 = iRam0000000000000008;
  }
  else {
    iVar5 = (int)param_2[1];
  }
  if (iVar5 != 0) {
    puVar2 = PTR__ZTV32CExchangeShopExCountInfoCategory_02cc2e90 + 0x10;
    uVar9 = 0;
    puVar3 = PTR__ZTV8InfoBase_02cc49c8 + 0x10;
    do {
      pppppplStack_88 = (long ******)(**(code **)(*param_1 + 0x20))(param_1,*param_2 + uVar9 * 0x40)
      ;
      ppppppplVar11 = (long *******)param_1[8];
      ppppppplVar10 = ppppppplVar11;
      puVar6 = puVar2;
      ppppppplVar8 = ppppppplVar13;
      if (ppppppplVar11 == (long *******)0x0) {
code_r0x0164a06c:
        puStack_d8 = puVar6;
        ppppppplVar12 = (long *******)*ppppppplVar13;
        ppppppplVar10 = ppppppplVar13;
        ppppppplVar8 = ppppppplVar13;
joined_r0x0164a048:
        puStack_d0 = &uStack_c8;
        puStack_b8 = &uStack_b0;
        puStack_a0 = &uStack_98;
        ppppppplStack_68 = ppppppplVar8;
        if (ppppppplVar12 == (long *******)0x0) {
          uStack_90 = 0;
          uStack_98 = 0;
          uStack_a8 = 0;
          uStack_b0 = 0;
          uStack_c0 = 0;
          uStack_c8 = 0;
          std::__ndk1::unique_ptr<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CExchangeShopExCountInfoCategory>, void*>, std::__ndk1::__tree_node_destructor<Framework::CSTLAllocator<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CExchangeShopExCountInfoCategory>, void*>, Framework::CSTLMapAllocatorInf> > > std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CExchangeShopExCountInfoCategory>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CExchangeShopExCountInfoCategory>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CExchangeShopExCountInfoCategory>, Framework::CSTLMapAllocatorInf> >::__construct_node<unsigned long&, CExchangeShopExCountInfoCategory>(unsigned long&, CExchangeShopExCountInfoCategory&&)(appppppplStack_80,plVar7,&pppppplStack_88,&puStack_d8);
          *appppppplStack_80[0] = (long ******)0x0;
          appppppplStack_80[0][1] = (long ******)0x0;
          appppppplStack_80[0][2] = (long ******)ppppppplVar8;
          *ppppppplVar10 = (long ******)appppppplStack_80[0];
          ppppppplVar11 = appppppplStack_80[0];
          if (*(long *)*plVar7 != 0) {
            *plVar7 = *(long *)*plVar7;
            ppppppplVar11 = (long *******)*ppppppplVar10;
          }
          void std::__ndk1::__tree_balance_after_insert<std::__ndk1::__tree_node_base<void*>*>(std::__ndk1::__tree_node_base<void*>*, std::__ndk1::__tree_node_base<void*>*)(param_1[8],ppppppplVar11);
          param_1[9] = param_1[9] + 1;
          ppppppplVar12 = appppppplStack_80[0];
        }
        else {
          uStack_90 = 0;
          uStack_98 = 0;
          uStack_a8 = 0;
          uStack_b0 = 0;
          uStack_c0 = 0;
          uStack_c8 = 0;
        }
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CExchangeShopExCountInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CExchangeShopExCountInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CExchangeShopExCountInfo>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CExchangeShopExCountInfo>, void*>*)(&puStack_a0,uStack_98);
        puStack_d8 = puVar3;
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*)(&puStack_b8,uStack_b0);
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*)(&puStack_d0,uStack_c8);
        ppppppplVar12 = ppppppplVar12 + 5;
        (*(code *)(*ppppppplVar12)[2])(ppppppplVar12);
      }
      else {
        do {
          while (ppppppplVar12 = ppppppplVar10, pppppplStack_88 <= ppppppplVar12[4]) {
            ppppppplVar10 = (long *******)*ppppppplVar12;
            ppppppplVar8 = ppppppplVar12;
            if ((long *******)*ppppppplVar12 == (long *******)0x0) {
              if (ppppppplVar12 != ppppppplVar13) goto code_r0x01649fc4;
              goto code_r0x01649fe0;
            }
          }
          ppppppplVar10 = (long *******)ppppppplVar12[1];
        } while ((long *******)ppppppplVar12[1] != (long *******)0x0);
        ppppppplVar12 = ppppppplVar8;
        if (ppppppplVar8 == ppppppplVar13) {
code_r0x01649fe0:
          puStack_d8 = PTR__ZTV32CExchangeShopExCountInfoCategory_02cc2e90 + 0x10;
          puVar6 = puStack_d8;
          if (ppppppplVar11 == (long *******)0x0) goto code_r0x0164a06c;
          do {
            while (ppppppplVar8 = ppppppplVar11, pppppplStack_88 < ppppppplVar8[4]) {
              ppppppplVar11 = (long *******)*ppppppplVar8;
              if ((long *******)*ppppppplVar8 == (long *******)0x0) {
                ppppppplVar10 = ppppppplVar8;
                ppppppplVar12 = (long *******)*ppppppplVar8;
                goto joined_r0x0164a048;
              }
            }
            if (pppppplStack_88 <= ppppppplVar8[4]) {
              ppppppplVar10 = (long *******)&ppppppplStack_68;
              ppppppplVar12 = ppppppplVar8;
              goto joined_r0x0164a048;
            }
            ppppppplVar10 = ppppppplVar8 + 1;
            ppppppplVar11 = (long *******)*ppppppplVar10;
          } while ((long *******)*ppppppplVar10 != (long *******)0x0);
          ppppppplVar12 = (long *******)*ppppppplVar10;
          goto joined_r0x0164a048;
        }
code_r0x01649fc4:
        if ((pppppplStack_88 < ppppppplVar12[4]) || (ppppppplVar12 == ppppppplVar13))
        goto code_r0x01649fe0;
        ppppppplVar12 = ppppppplVar12 + 5;
      }
      lVar4 = *param_2 + uVar9 * 0x40;
      iVar5 = *(int *)(lVar4 + 0x20);
      if (iVar5 == 6) {
        (*(code *)**ppppppplVar12)(ppppppplVar12,lVar4 + 0x28);
      }
      else if (iVar5 == 7) {
        (*(code *)(*ppppppplVar12)[1])(ppppppplVar12,*param_2 + uVar9 * 0x40 + 0x28);
      }
      uVar1 = (int)uVar9 + 1;
      uVar9 = (ulong)uVar1;
    } while (uVar1 < *(uint *)(param_2 + 1));
  }
  return 1;
}

// ==== IInfoBaseMap<unsigned long, CExchangeShopExCountInfo>::DeserializeChild(Aska::ASON::AValue::AMap const*)
// vaddr 0x154a4d8 | ghidra 0x164a4d8 | size 596 | symbol _ZN12IInfoBaseMapIm24CExchangeShopExCountInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN12IInfoBaseMapIm24CExchangeShopExCountInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE
          (long *param_1,long *param_2)

{
  uint uVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined *puVar5;
  int iVar6;
  long *plVar7;
  long lVar8;
  long *plVar9;
  ulong uVar10;
  long *plVar11;
  long *plVar12;
  undefined *puStack_d0;
  undefined8 *puStack_c8;
  undefined8 auStack_c0 [2];
  undefined8 *puStack_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined *puStack_98;
  undefined8 uStack_90;
  undefined1 uStack_88;
  undefined1 auStack_80 [24];
  ulong uStack_68;
  
  plVar12 = param_1 + 8;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CExchangeShopExCountInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CExchangeShopExCountInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CExchangeShopExCountInfo>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CExchangeShopExCountInfo>, void*>*)(param_1 + 7,*plVar12);
  param_1[7] = (long)plVar12;
  param_1[8] = 0;
  param_1[9] = 0;
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0282d54e/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\Info/InfoBase.h"*/,0x1c1,&UNK_027dc58a/*"apParser is null."*/);
    iVar6 = iRam0000000000000008;
  }
  else {
    iVar6 = (int)param_2[1];
  }
  if (iVar6 != 0) {
    uVar10 = 0;
    puVar2 = PTR__ZTV24CExchangeShopExCountInfo_02cbe890 + 0x10;
    puVar3 = PTR__ZTV22CParameterPropertyBaseILj68EE_02cb7090 + 0x10;
    puVar4 = PTR__ZTV23CParameterPropertyValueIjLj68E18CPropertyConverterE_02cb7310 + 0x10;
    puVar5 = PTR__ZTV8InfoBase_02cc49c8 + 0x10;
    do {
      uStack_68 = (**(code **)(*param_1 + 0x20))(param_1,*param_2 + uVar10 * 0x40);
      plVar7 = (long *)param_1[8];
      plVar9 = plVar12;
      if ((long *)param_1[8] == (long *)0x0) {
code_r0x0164a624:
        memset(auStack_c0,0,0x58);
        uStack_a8 = 0;
        uStack_a0 = 0;
        uStack_90 = 0;
        uStack_88 = 0;
        puStack_d0 = puVar2;
        puStack_c8 = auStack_c0;
        puStack_b0 = &uStack_a8;
        puStack_98 = puVar3;
        Framework::CHash32::CHash32()(auStack_80);
        puStack_98 = puVar4;
        lVar8 = std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned long, CExchangeShopExCountInfo>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CExchangeShopExCountInfo>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CExchangeShopExCountInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CExchangeShopExCountInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CExchangeShopExCountInfo>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned long, unsigned long&, CExchangeShopExCountInfo>(unsigned long const&, unsigned long&, CExchangeShopExCountInfo&&)(param_1 + 7,&uStack_68,&uStack_68,&puStack_d0);
        puStack_d0 = puVar2;
        puStack_98 = puVar3;
        Framework::CHash32::~CHash32()(auStack_80);
        puStack_d0 = puVar5;
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*)(&puStack_b0,uStack_a8);
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*)(&puStack_c8,auStack_c0[0]);
        plVar11 = (long *)(lVar8 + 0x28);
        (**(code **)(*plVar11 + 0x10))(plVar11);
      }
      else {
        do {
          while (plVar11 = plVar7, (ulong)plVar11[4] < uStack_68) {
            plVar7 = (long *)plVar11[1];
            if ((long *)plVar11[1] == (long *)0x0) {
              plVar11 = plVar9;
              if (plVar9 != plVar12) goto code_r0x0164a608;
              goto code_r0x0164a624;
            }
          }
          plVar7 = (long *)*plVar11;
          plVar9 = plVar11;
        } while ((long *)*plVar11 != (long *)0x0);
        if (plVar11 == plVar12) goto code_r0x0164a624;
code_r0x0164a608:
        if ((uStack_68 < (ulong)plVar11[4]) || (plVar11 == plVar12)) goto code_r0x0164a624;
        plVar11 = plVar11 + 5;
      }
      lVar8 = *param_2 + uVar10 * 0x40;
      iVar6 = *(int *)(lVar8 + 0x20);
      if (iVar6 == 6) {
        (**(code **)*plVar11)(plVar11,lVar8 + 0x28);
      }
      else if (iVar6 == 7) {
        (**(code **)(*plVar11 + 8))(plVar11,*param_2 + uVar10 * 0x40 + 0x28);
      }
      uVar1 = (int)uVar10 + 1;
      uVar10 = (ulong)uVar1;
    } while (uVar1 < *(uint *)(param_2 + 1));
  }
  return 1;
}

// ==== IInfoBaseMap<unsigned long, CLimitBreakInfo>::DeserializeChild(Aska::ASON::AValue::AMap const*)
// vaddr 0x154b92c | ghidra 0x164b92c | size 1324 | symbol _ZN12IInfoBaseMapIm15CLimitBreakInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Type propagation algorithm not settling */

undefined8
_ZN12IInfoBaseMapIm15CLimitBreakInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE
          (long *param_1,long *param_2)

{
  uint uVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined *puVar5;
  undefined *puVar6;
  undefined *puVar7;
  undefined *puVar8;
  undefined *puVar9;
  undefined *puVar10;
  undefined *puVar11;
  undefined *puVar12;
  undefined *puVar13;
  undefined *puVar14;
  undefined *puVar15;
  long lVar16;
  int iVar17;
  long *plVar18;
  long *******ppppppplVar19;
  long *******ppppppplVar20;
  ulong uVar21;
  long *******ppppppplVar22;
  long *******ppppppplVar23;
  long *******ppppppplVar24;
  undefined *puStack_1e0;
  undefined8 *puStack_1d8;
  undefined8 auStack_1d0 [2];
  undefined8 *puStack_1c0;
  undefined8 uStack_1b8;
  undefined8 uStack_1b0;
  undefined *puStack_1a8;
  undefined8 uStack_1a0;
  undefined1 uStack_198;
  undefined1 auStack_190 [24];
  undefined *puStack_178;
  undefined8 uStack_170;
  undefined1 uStack_168;
  undefined1 auStack_160 [24];
  undefined *puStack_148;
  undefined8 uStack_140;
  undefined1 uStack_138;
  undefined1 auStack_130 [24];
  undefined *puStack_118;
  undefined8 uStack_110;
  undefined1 uStack_108;
  undefined1 auStack_100 [24];
  undefined *puStack_e8;
  undefined8 uStack_e0;
  undefined1 uStack_d8;
  undefined1 auStack_d0 [24];
  undefined *puStack_b8;
  undefined8 uStack_b0;
  undefined1 uStack_a8;
  undefined1 auStack_a0 [24];
  long ******pppppplStack_88;
  long *******appppppplStack_80 [3];
  long *******ppppppplStack_68;
  
  ppppppplVar23 = (long *******)(param_1 + 8);
  plVar18 = param_1 + 7;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CLimitBreakInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CLimitBreakInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CLimitBreakInfo>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CLimitBreakInfo>, void*>*)(plVar18,*ppppppplVar23);
  param_1[7] = (long)ppppppplVar23;
  param_1[8] = 0;
  param_1[9] = 0;
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0282d54e/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\Info/InfoBase.h"*/,0x1c1,&UNK_027dc58a/*"apParser is null."*/);
    iVar17 = iRam0000000000000008;
  }
  else {
    iVar17 = (int)param_2[1];
  }
  if (iVar17 != 0) {
    puVar2 = PTR__ZTV15CLimitBreakInfo_02cb9040 + 0x10;
    puVar3 = PTR__ZTV22CParameterPropertyBaseILj36EE_02cb6f78 + 0x10;
    puVar4 = PTR__ZTV23CParameterPropertyValueImLj36E18CPropertyConverterE_02cbcde0 + 0x10;
    puVar5 = PTR__ZTV22CParameterPropertyBaseILj37EE_02cbda08 + 0x10;
    puVar6 = PTR__ZTV23CParameterPropertyValueIjLj37E18CPropertyConverterE_02cba818 + 0x10;
    puVar7 = PTR__ZTV22CParameterPropertyBaseILj38EE_02cc0aa0 + 0x10;
    puVar8 = PTR__ZTV23CParameterPropertyValueIjLj38E18CPropertyConverterE_02cc3fa0 + 0x10;
    puVar9 = PTR__ZTV22CParameterPropertyBaseILj39EE_02cc3d00 + 0x10;
    puVar10 = PTR__ZTV23CParameterPropertyValueIjLj39E18CPropertyConverterE_02cc2560 + 0x10;
    puVar11 = PTR__ZTV22CParameterPropertyBaseILj40EE_02cbd2c0 + 0x10;
    puVar12 = PTR__ZTV23CParameterPropertyValueIjLj40E18CPropertyConverterE_02cb8038 + 0x10;
    puVar13 = PTR__ZTV23CParameterPropertyValueIjLj41E18CPropertyConverterE_02cbafc0 + 0x10;
    puVar14 = PTR__ZTV8InfoBase_02cc49c8 + 0x10;
    uVar21 = 0;
    puVar15 = PTR__ZTV22CParameterPropertyBaseILj41EE_02cc2068 + 0x10;
    do {
      pppppplStack_88 =
           (long ******)(**(code **)(*param_1 + 0x20))(param_1,*param_2 + uVar21 * 0x40);
      ppppppplVar20 = (long *******)param_1[8];
      ppppppplVar19 = ppppppplVar23;
      if ((long *******)param_1[8] == (long *******)0x0) {
code_r0x0164bb4c:
        memset(auStack_1d0,0,0x148);
        uStack_1b8 = 0;
        uStack_1b0 = 0;
        uStack_198 = 0;
        uStack_1a0 = 0;
        puStack_1e0 = puVar2;
        puStack_1d8 = auStack_1d0;
        puStack_1c0 = &uStack_1b8;
        puStack_1a8 = puVar3;
        Framework::CHash32::CHash32()(auStack_190);
        uStack_168 = 0;
        uStack_170 = 0;
        puStack_1a8 = puVar4;
        puStack_178 = puVar5;
        Framework::CHash32::CHash32()(auStack_160);
        uStack_138 = 0;
        uStack_140 = 0;
        puStack_178 = puVar6;
        puStack_148 = puVar7;
        Framework::CHash32::CHash32()(auStack_130);
        uStack_108 = 0;
        uStack_110 = 0;
        puStack_148 = puVar8;
        puStack_118 = puVar9;
        Framework::CHash32::CHash32()(auStack_100);
        uStack_d8 = 0;
        uStack_e0 = 0;
        puStack_118 = puVar10;
        puStack_e8 = puVar11;
        Framework::CHash32::CHash32()(auStack_d0);
        uStack_a8 = 0;
        uStack_b0 = 0;
        puStack_e8 = puVar12;
        puStack_b8 = puVar15;
        Framework::CHash32::CHash32()(auStack_a0);
        ppppppplVar20 = (long *******)*ppppppplVar23;
        if ((long *******)*ppppppplVar23 == (long *******)0x0) {
          ppppppplVar22 = (long *******)*ppppppplVar23;
          ppppppplVar19 = ppppppplVar23;
          ppppppplVar24 = ppppppplVar23;
        }
        else {
          do {
            while (ppppppplVar19 = ppppppplVar20, ppppppplVar19[4] <= pppppplStack_88) {
              if (pppppplStack_88 <= ppppppplVar19[4]) {
                ppppppplVar22 = ppppppplVar19;
                ppppppplVar24 = (long *******)&ppppppplStack_68;
                goto joined_r0x0164bc94;
              }
              ppppppplVar24 = ppppppplVar19 + 1;
              ppppppplVar20 = (long *******)*ppppppplVar24;
              if ((long *******)*ppppppplVar24 == (long *******)0x0) {
                ppppppplVar22 = (long *******)*ppppppplVar24;
                goto joined_r0x0164bc94;
              }
            }
            ppppppplVar20 = (long *******)*ppppppplVar19;
          } while ((long *******)*ppppppplVar19 != (long *******)0x0);
          ppppppplVar22 = (long *******)*ppppppplVar19;
          ppppppplVar24 = ppppppplVar19;
        }
joined_r0x0164bc94:
        ppppppplStack_68 = ppppppplVar19;
        if (ppppppplVar22 == (long *******)0x0) {
          puStack_b8 = puVar13;
          std::__ndk1::unique_ptr<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CLimitBreakInfo>, void*>, std::__ndk1::__tree_node_destructor<Framework::CSTLAllocator<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CLimitBreakInfo>, void*>, Framework::CSTLMapAllocatorInf> > > std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CLimitBreakInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CLimitBreakInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CLimitBreakInfo>, Framework::CSTLMapAllocatorInf> >::__construct_node<unsigned long&, CLimitBreakInfo>(unsigned long&, CLimitBreakInfo&&)(appppppplStack_80,plVar18,&pppppplStack_88,&puStack_1e0);
          *appppppplStack_80[0] = (long ******)0x0;
          appppppplStack_80[0][1] = (long ******)0x0;
          appppppplStack_80[0][2] = (long ******)ppppppplVar19;
          *ppppppplVar24 = (long ******)appppppplStack_80[0];
          ppppppplVar20 = appppppplStack_80[0];
          if (*(long *)*plVar18 != 0) {
            *plVar18 = *(long *)*plVar18;
            ppppppplVar20 = (long *******)*ppppppplVar24;
          }
          void std::__ndk1::__tree_balance_after_insert<std::__ndk1::__tree_node_base<void*>*>(std::__ndk1::__tree_node_base<void*>*, std::__ndk1::__tree_node_base<void*>*)(param_1[8],ppppppplVar20);
          param_1[9] = param_1[9] + 1;
          ppppppplVar22 = appppppplStack_80[0];
        }
        puStack_1e0 = PTR__ZTV15CLimitBreakInfo_02cb9040 + 0x10;
        puStack_b8 = PTR__ZTV22CParameterPropertyBaseILj41EE_02cc2068 + 0x10;
        Framework::CHash32::~CHash32()(auStack_a0);
        puStack_e8 = PTR__ZTV22CParameterPropertyBaseILj40EE_02cbd2c0 + 0x10;
        Framework::CHash32::~CHash32()(auStack_d0);
        puStack_118 = PTR__ZTV22CParameterPropertyBaseILj39EE_02cc3d00 + 0x10;
        Framework::CHash32::~CHash32()(auStack_100);
        puStack_148 = PTR__ZTV22CParameterPropertyBaseILj38EE_02cc0aa0 + 0x10;
        Framework::CHash32::~CHash32()(auStack_130);
        puStack_178 = PTR__ZTV22CParameterPropertyBaseILj37EE_02cbda08 + 0x10;
        Framework::CHash32::~CHash32()(auStack_160);
        puStack_1a8 = PTR__ZTV22CParameterPropertyBaseILj36EE_02cb6f78 + 0x10;
        Framework::CHash32::~CHash32()(auStack_190);
        puStack_1e0 = puVar14;
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*)(&puStack_1c0,uStack_1b8);
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*)(&puStack_1d8,auStack_1d0[0]);
        ppppppplVar22 = ppppppplVar22 + 5;
        (*(code *)(*ppppppplVar22)[2])(ppppppplVar22);
      }
      else {
        do {
          while (ppppppplVar22 = ppppppplVar20, ppppppplVar22[4] < pppppplStack_88) {
            ppppppplVar20 = (long *******)ppppppplVar22[1];
            if ((long *******)ppppppplVar22[1] == (long *******)0x0) {
              ppppppplVar22 = ppppppplVar19;
              if (ppppppplVar19 != ppppppplVar23) goto code_r0x0164bb30;
              goto code_r0x0164bb4c;
            }
          }
          ppppppplVar20 = (long *******)*ppppppplVar22;
          ppppppplVar19 = ppppppplVar22;
        } while ((long *******)*ppppppplVar22 != (long *******)0x0);
        if (ppppppplVar22 == ppppppplVar23) goto code_r0x0164bb4c;
code_r0x0164bb30:
        if ((pppppplStack_88 < ppppppplVar22[4]) || (ppppppplVar22 == ppppppplVar23))
        goto code_r0x0164bb4c;
        ppppppplVar22 = ppppppplVar22 + 5;
      }
      lVar16 = *param_2 + uVar21 * 0x40;
      iVar17 = *(int *)(lVar16 + 0x20);
      if (iVar17 == 6) {
        (*(code *)**ppppppplVar22)(ppppppplVar22,lVar16 + 0x28);
      }
      else if (iVar17 == 7) {
        (*(code *)(*ppppppplVar22)[1])(ppppppplVar22,*param_2 + uVar21 * 0x40 + 0x28);
      }
      uVar1 = (int)uVar21 + 1;
      uVar21 = (ulong)uVar1;
    } while (uVar1 < *(uint *)(param_2 + 1));
  }
  return 1;
}

// ==== IInfoBaseMap<unsigned long, CLimitBreakItemInfo>::DeserializeChild(Aska::ASON::AValue::AMap const*)
// vaddr 0x154c2ac | ghidra 0x164c2ac | size 1132 | symbol _ZN12IInfoBaseMapIm19CLimitBreakItemInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Type propagation algorithm not settling */

undefined8
_ZN12IInfoBaseMapIm19CLimitBreakItemInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE
          (long *param_1,long *param_2)

{
  uint uVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined *puVar5;
  undefined *puVar6;
  undefined *puVar7;
  undefined *puVar8;
  undefined *puVar9;
  undefined *puVar10;
  undefined *puVar11;
  long lVar12;
  int iVar13;
  long *plVar14;
  long *******ppppppplVar15;
  long *******ppppppplVar16;
  ulong uVar17;
  long *******ppppppplVar18;
  long *******ppppppplVar19;
  long *******ppppppplVar20;
  undefined *puStack_180;
  undefined8 *puStack_178;
  undefined8 auStack_170 [2];
  undefined8 *puStack_160;
  undefined8 uStack_158;
  undefined8 uStack_150;
  undefined *puStack_148;
  undefined8 uStack_140;
  undefined1 uStack_138;
  undefined1 auStack_130 [24];
  undefined *puStack_118;
  undefined8 uStack_110;
  undefined1 uStack_108;
  undefined1 auStack_100 [24];
  undefined *puStack_e8;
  undefined8 uStack_e0;
  undefined1 uStack_d8;
  undefined1 auStack_d0 [24];
  undefined *puStack_b8;
  undefined8 uStack_b0;
  undefined1 uStack_a8;
  undefined1 auStack_a0 [24];
  long ******pppppplStack_88;
  long *******appppppplStack_80 [3];
  long *******ppppppplStack_68;
  
  ppppppplVar18 = (long *******)(param_1 + 8);
  plVar14 = param_1 + 7;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CLimitBreakItemInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CLimitBreakItemInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CLimitBreakItemInfo>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CLimitBreakItemInfo>, void*>*)(plVar14,*ppppppplVar18);
  param_1[7] = (long)ppppppplVar18;
  param_1[8] = 0;
  param_1[9] = 0;
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0282d54e/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\Info/InfoBase.h"*/,0x1c1,&UNK_027dc58a/*"apParser is null."*/);
    iVar13 = iRam0000000000000008;
  }
  else {
    iVar13 = (int)param_2[1];
  }
  if (iVar13 != 0) {
    puVar2 = PTR__ZTV19CLimitBreakItemInfo_02cba188 + 0x10;
    puVar3 = PTR__ZTV22CParameterPropertyBaseILj75EE_02cbea40 + 0x10;
    puVar4 = PTR__ZTV23CParameterPropertyValueImLj75E18CPropertyConverterE_02cb9890 + 0x10;
    puVar5 = PTR__ZTV22CParameterPropertyBaseILj76EE_02cc1a08 + 0x10;
    puVar6 = PTR__ZTV23CParameterPropertyValueIjLj76E18CPropertyConverterE_02cbb508 + 0x10;
    puVar7 = PTR__ZTV22CParameterPropertyBaseILj77EE_02cbf550 + 0x10;
    puVar8 = PTR__ZTV23CParameterPropertyValueIjLj77E18CPropertyConverterE_02cc2248 + 0x10;
    puVar9 = PTR__ZTV22CParameterPropertyBaseILj78EE_02cc2748 + 0x10;
    puVar10 = PTR__ZTV23CParameterPropertyValueIjLj78E18CPropertyConverterE_02cc32c0 + 0x10;
    uVar17 = 0;
    puVar11 = PTR__ZTV8InfoBase_02cc49c8 + 0x10;
    do {
      pppppplStack_88 =
           (long ******)(**(code **)(*param_1 + 0x20))(param_1,*param_2 + uVar17 * 0x40);
      ppppppplVar16 = (long *******)param_1[8];
      ppppppplVar15 = ppppppplVar18;
      if ((long *******)param_1[8] == (long *******)0x0) {
code_r0x0164c47c:
        memset(auStack_170,0,0xe8);
        uStack_158 = 0;
        uStack_150 = 0;
        uStack_138 = 0;
        uStack_140 = 0;
        puStack_180 = puVar2;
        puStack_178 = auStack_170;
        puStack_160 = &uStack_158;
        puStack_148 = puVar3;
        Framework::CHash32::CHash32()(auStack_130);
        uStack_108 = 0;
        uStack_110 = 0;
        puStack_148 = puVar4;
        puStack_118 = puVar5;
        Framework::CHash32::CHash32()(auStack_100);
        uStack_d8 = 0;
        uStack_e0 = 0;
        puStack_118 = puVar6;
        puStack_e8 = puVar7;
        Framework::CHash32::CHash32()(auStack_d0);
        uStack_a8 = 0;
        uStack_b0 = 0;
        puStack_e8 = puVar8;
        puStack_b8 = puVar9;
        Framework::CHash32::CHash32()(auStack_a0);
        ppppppplVar16 = (long *******)*ppppppplVar18;
        if ((long *******)*ppppppplVar18 == (long *******)0x0) {
          ppppppplVar20 = (long *******)*ppppppplVar18;
          ppppppplVar15 = ppppppplVar18;
          ppppppplVar19 = ppppppplVar18;
        }
        else {
          do {
            while (ppppppplVar15 = ppppppplVar16, ppppppplVar15[4] <= pppppplStack_88) {
              if (pppppplStack_88 <= ppppppplVar15[4]) {
                ppppppplVar20 = ppppppplVar15;
                ppppppplVar19 = (long *******)&ppppppplStack_68;
                goto joined_r0x0164c588;
              }
              ppppppplVar19 = ppppppplVar15 + 1;
              ppppppplVar16 = (long *******)*ppppppplVar19;
              if ((long *******)*ppppppplVar19 == (long *******)0x0) {
                ppppppplVar20 = (long *******)*ppppppplVar19;
                goto joined_r0x0164c588;
              }
            }
            ppppppplVar16 = (long *******)*ppppppplVar15;
          } while ((long *******)*ppppppplVar15 != (long *******)0x0);
          ppppppplVar20 = (long *******)*ppppppplVar15;
          ppppppplVar19 = ppppppplVar15;
        }
joined_r0x0164c588:
        ppppppplStack_68 = ppppppplVar15;
        if (ppppppplVar20 == (long *******)0x0) {
          puStack_b8 = puVar10;
          std::__ndk1::unique_ptr<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CLimitBreakItemInfo>, void*>, std::__ndk1::__tree_node_destructor<Framework::CSTLAllocator<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CLimitBreakItemInfo>, void*>, Framework::CSTLMapAllocatorInf> > > std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CLimitBreakItemInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CLimitBreakItemInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CLimitBreakItemInfo>, Framework::CSTLMapAllocatorInf> >::__construct_node<unsigned long&, CLimitBreakItemInfo>(unsigned long&, CLimitBreakItemInfo&&)(appppppplStack_80,plVar14,&pppppplStack_88,&puStack_180);
          *appppppplStack_80[0] = (long ******)0x0;
          appppppplStack_80[0][1] = (long ******)0x0;
          appppppplStack_80[0][2] = (long ******)ppppppplVar15;
          *ppppppplVar19 = (long ******)appppppplStack_80[0];
          ppppppplVar16 = appppppplStack_80[0];
          if (*(long *)*plVar14 != 0) {
            *plVar14 = *(long *)*plVar14;
            ppppppplVar16 = (long *******)*ppppppplVar19;
          }
          void std::__ndk1::__tree_balance_after_insert<std::__ndk1::__tree_node_base<void*>*>(std::__ndk1::__tree_node_base<void*>*, std::__ndk1::__tree_node_base<void*>*)(param_1[8],ppppppplVar16);
          param_1[9] = param_1[9] + 1;
          ppppppplVar20 = appppppplStack_80[0];
        }
        puStack_180 = PTR__ZTV19CLimitBreakItemInfo_02cba188 + 0x10;
        puStack_b8 = PTR__ZTV22CParameterPropertyBaseILj78EE_02cc2748 + 0x10;
        Framework::CHash32::~CHash32()(auStack_a0);
        puStack_e8 = PTR__ZTV22CParameterPropertyBaseILj77EE_02cbf550 + 0x10;
        Framework::CHash32::~CHash32()(auStack_d0);
        puStack_118 = PTR__ZTV22CParameterPropertyBaseILj76EE_02cc1a08 + 0x10;
        Framework::CHash32::~CHash32()(auStack_100);
        puStack_148 = PTR__ZTV22CParameterPropertyBaseILj75EE_02cbea40 + 0x10;
        Framework::CHash32::~CHash32()(auStack_130);
        puStack_180 = puVar11;
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*)(&puStack_160,uStack_158);
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*)(&puStack_178,auStack_170[0]);
        ppppppplVar20 = ppppppplVar20 + 5;
        (*(code *)(*ppppppplVar20)[2])(ppppppplVar20);
      }
      else {
        do {
          while (ppppppplVar20 = ppppppplVar16, ppppppplVar20[4] < pppppplStack_88) {
            ppppppplVar16 = (long *******)ppppppplVar20[1];
            if ((long *******)ppppppplVar20[1] == (long *******)0x0) {
              ppppppplVar20 = ppppppplVar15;
              if (ppppppplVar15 != ppppppplVar18) goto code_r0x0164c460;
              goto code_r0x0164c47c;
            }
          }
          ppppppplVar16 = (long *******)*ppppppplVar20;
          ppppppplVar15 = ppppppplVar20;
        } while ((long *******)*ppppppplVar20 != (long *******)0x0);
        if (ppppppplVar20 == ppppppplVar18) goto code_r0x0164c47c;
code_r0x0164c460:
        if ((pppppplStack_88 < ppppppplVar20[4]) || (ppppppplVar20 == ppppppplVar18))
        goto code_r0x0164c47c;
        ppppppplVar20 = ppppppplVar20 + 5;
      }
      lVar12 = *param_2 + uVar17 * 0x40;
      iVar13 = *(int *)(lVar12 + 0x20);
      if (iVar13 == 6) {
        (*(code *)**ppppppplVar20)(ppppppplVar20,lVar12 + 0x28);
      }
      else if (iVar13 == 7) {
        (*(code *)(*ppppppplVar20)[1])(ppppppplVar20,*param_2 + uVar17 * 0x40 + 0x28);
      }
      uVar1 = (int)uVar17 + 1;
      uVar17 = (ulong)uVar1;
    } while (uVar1 < *(uint *)(param_2 + 1));
  }
  return 1;
}

// ==== IInfoBaseMap<unsigned long, CharacterChipInfo>::DeserializeChild(Aska::ASON::AValue::AMap const*)
// vaddr 0x154cb30 | ghidra 0x164cb30 | size 1156 | symbol _ZN12IInfoBaseMapIm17CharacterChipInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Type propagation algorithm not settling */

undefined8
_ZN12IInfoBaseMapIm17CharacterChipInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE
          (long *param_1,long *param_2)

{
  uint uVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined *puVar5;
  undefined *puVar6;
  undefined *puVar7;
  undefined *puVar8;
  undefined *puVar9;
  undefined *puVar10;
  undefined *puVar11;
  undefined *puVar12;
  long lVar13;
  int iVar14;
  long *plVar15;
  long *******ppppppplVar16;
  long *******ppppppplVar17;
  ulong uVar18;
  long *******ppppppplVar19;
  long *******ppppppplVar20;
  long *******ppppppplVar21;
  undefined *puStack_180;
  undefined8 *puStack_178;
  undefined8 auStack_170 [2];
  undefined8 *puStack_160;
  undefined8 uStack_158;
  undefined8 uStack_150;
  undefined *puStack_148;
  undefined8 uStack_140;
  undefined1 uStack_138;
  undefined1 auStack_130 [24];
  undefined *puStack_118;
  undefined8 uStack_110;
  undefined1 uStack_108;
  undefined1 auStack_100 [24];
  undefined *puStack_e8;
  undefined8 uStack_e0;
  undefined1 uStack_d8;
  undefined1 auStack_d0 [24];
  undefined *puStack_b8;
  undefined8 uStack_b0;
  undefined1 uStack_a8;
  undefined1 auStack_a0 [24];
  long ******pppppplStack_88;
  long *******appppppplStack_80 [3];
  long *******ppppppplStack_68;
  
  ppppppplVar19 = (long *******)(param_1 + 8);
  plVar15 = param_1 + 7;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CharacterChipInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CharacterChipInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CharacterChipInfo>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CharacterChipInfo>, void*>*)(plVar15,*ppppppplVar19);
  param_1[7] = (long)ppppppplVar19;
  param_1[8] = 0;
  param_1[9] = 0;
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0282d54e/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\Info/InfoBase.h"*/,0x1c1,&UNK_027dc58a/*"apParser is null."*/);
    iVar14 = iRam0000000000000008;
  }
  else {
    iVar14 = (int)param_2[1];
  }
  if (iVar14 != 0) {
    puVar2 = PTR__ZTV19CLimitBreakItemInfo_02cba188 + 0x10;
    puVar3 = PTR__ZTV22CParameterPropertyBaseILj75EE_02cbea40 + 0x10;
    puVar4 = PTR__ZTV23CParameterPropertyValueImLj75E18CPropertyConverterE_02cb9890 + 0x10;
    puVar5 = PTR__ZTV22CParameterPropertyBaseILj76EE_02cc1a08 + 0x10;
    puVar6 = PTR__ZTV23CParameterPropertyValueIjLj76E18CPropertyConverterE_02cbb508 + 0x10;
    puVar7 = PTR__ZTV22CParameterPropertyBaseILj77EE_02cbf550 + 0x10;
    puVar8 = PTR__ZTV23CParameterPropertyValueIjLj77E18CPropertyConverterE_02cc2248 + 0x10;
    puVar9 = PTR__ZTV22CParameterPropertyBaseILj78EE_02cc2748 + 0x10;
    puVar10 = PTR__ZTV23CParameterPropertyValueIjLj78E18CPropertyConverterE_02cc32c0 + 0x10;
    puVar11 = PTR__ZTV17CharacterChipInfo_02cbd650 + 0x10;
    uVar18 = 0;
    puVar12 = PTR__ZTV8InfoBase_02cc49c8 + 0x10;
    do {
      pppppplStack_88 =
           (long ******)(**(code **)(*param_1 + 0x20))(param_1,*param_2 + uVar18 * 0x40);
      ppppppplVar17 = (long *******)param_1[8];
      ppppppplVar16 = ppppppplVar19;
      if ((long *******)param_1[8] == (long *******)0x0) {
code_r0x0164cd10:
        memset(auStack_170,0,0xe8);
        uStack_158 = 0;
        uStack_150 = 0;
        uStack_138 = 0;
        uStack_140 = 0;
        puStack_180 = puVar2;
        puStack_178 = auStack_170;
        puStack_160 = &uStack_158;
        puStack_148 = puVar3;
        Framework::CHash32::CHash32()(auStack_130);
        uStack_108 = 0;
        uStack_110 = 0;
        puStack_148 = puVar4;
        puStack_118 = puVar5;
        Framework::CHash32::CHash32()(auStack_100);
        uStack_d8 = 0;
        uStack_e0 = 0;
        puStack_118 = puVar6;
        puStack_e8 = puVar7;
        Framework::CHash32::CHash32()(auStack_d0);
        uStack_a8 = 0;
        uStack_b0 = 0;
        puStack_e8 = puVar8;
        puStack_b8 = puVar9;
        Framework::CHash32::CHash32()(auStack_a0);
        ppppppplVar17 = (long *******)*ppppppplVar19;
        if ((long *******)*ppppppplVar19 == (long *******)0x0) {
          ppppppplVar21 = (long *******)*ppppppplVar19;
          ppppppplVar16 = ppppppplVar19;
          ppppppplVar20 = ppppppplVar19;
        }
        else {
          do {
            while (ppppppplVar16 = ppppppplVar17, ppppppplVar16[4] <= pppppplStack_88) {
              if (pppppplStack_88 <= ppppppplVar16[4]) {
                ppppppplVar21 = ppppppplVar16;
                ppppppplVar20 = (long *******)&ppppppplStack_68;
                goto joined_r0x0164ce24;
              }
              ppppppplVar20 = ppppppplVar16 + 1;
              ppppppplVar17 = (long *******)*ppppppplVar20;
              if ((long *******)*ppppppplVar20 == (long *******)0x0) {
                ppppppplVar21 = (long *******)*ppppppplVar20;
                goto joined_r0x0164ce24;
              }
            }
            ppppppplVar17 = (long *******)*ppppppplVar16;
          } while ((long *******)*ppppppplVar16 != (long *******)0x0);
          ppppppplVar21 = (long *******)*ppppppplVar16;
          ppppppplVar20 = ppppppplVar16;
        }
joined_r0x0164ce24:
        ppppppplStack_68 = ppppppplVar16;
        if (ppppppplVar21 == (long *******)0x0) {
          puStack_180 = puVar11;
          puStack_b8 = puVar10;
          std::__ndk1::unique_ptr<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CharacterChipInfo>, void*>, std::__ndk1::__tree_node_destructor<Framework::CSTLAllocator<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CharacterChipInfo>, void*>, Framework::CSTLMapAllocatorInf> > > std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CharacterChipInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CharacterChipInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CharacterChipInfo>, Framework::CSTLMapAllocatorInf> >::__construct_node<unsigned long&, CharacterChipInfo>(unsigned long&, CharacterChipInfo&&)(appppppplStack_80,plVar15,&pppppplStack_88,&puStack_180);
          *appppppplStack_80[0] = (long ******)0x0;
          appppppplStack_80[0][1] = (long ******)0x0;
          appppppplStack_80[0][2] = (long ******)ppppppplVar16;
          *ppppppplVar20 = (long ******)appppppplStack_80[0];
          ppppppplVar17 = appppppplStack_80[0];
          if (*(long *)*plVar15 != 0) {
            *plVar15 = *(long *)*plVar15;
            ppppppplVar17 = (long *******)*ppppppplVar20;
          }
          void std::__ndk1::__tree_balance_after_insert<std::__ndk1::__tree_node_base<void*>*>(std::__ndk1::__tree_node_base<void*>*, std::__ndk1::__tree_node_base<void*>*)(param_1[8],ppppppplVar17);
          param_1[9] = param_1[9] + 1;
          ppppppplVar21 = appppppplStack_80[0];
        }
        puStack_180 = PTR__ZTV19CLimitBreakItemInfo_02cba188 + 0x10;
        puStack_b8 = PTR__ZTV22CParameterPropertyBaseILj78EE_02cc2748 + 0x10;
        Framework::CHash32::~CHash32()(auStack_a0);
        puStack_e8 = PTR__ZTV22CParameterPropertyBaseILj77EE_02cbf550 + 0x10;
        Framework::CHash32::~CHash32()(auStack_d0);
        puStack_118 = PTR__ZTV22CParameterPropertyBaseILj76EE_02cc1a08 + 0x10;
        Framework::CHash32::~CHash32()(auStack_100);
        puStack_148 = PTR__ZTV22CParameterPropertyBaseILj75EE_02cbea40 + 0x10;
        Framework::CHash32::~CHash32()(auStack_130);
        puStack_180 = puVar12;
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*)(&puStack_160,uStack_158);
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*)(&puStack_178,auStack_170[0]);
        ppppppplVar21 = ppppppplVar21 + 5;
        (*(code *)(*ppppppplVar21)[2])(ppppppplVar21);
      }
      else {
        do {
          while (ppppppplVar21 = ppppppplVar17, ppppppplVar21[4] < pppppplStack_88) {
            ppppppplVar17 = (long *******)ppppppplVar21[1];
            if ((long *******)ppppppplVar21[1] == (long *******)0x0) {
              ppppppplVar21 = ppppppplVar16;
              if (ppppppplVar16 != ppppppplVar19) goto code_r0x0164ccf4;
              goto code_r0x0164cd10;
            }
          }
          ppppppplVar17 = (long *******)*ppppppplVar21;
          ppppppplVar16 = ppppppplVar21;
        } while ((long *******)*ppppppplVar21 != (long *******)0x0);
        if (ppppppplVar21 == ppppppplVar19) goto code_r0x0164cd10;
code_r0x0164ccf4:
        if ((pppppplStack_88 < ppppppplVar21[4]) || (ppppppplVar21 == ppppppplVar19))
        goto code_r0x0164cd10;
        ppppppplVar21 = ppppppplVar21 + 5;
      }
      lVar13 = *param_2 + uVar18 * 0x40;
      iVar14 = *(int *)(lVar13 + 0x20);
      if (iVar14 == 6) {
        (*(code *)**ppppppplVar21)(ppppppplVar21,lVar13 + 0x28);
      }
      else if (iVar14 == 7) {
        (*(code *)(*ppppppplVar21)[1])(ppppppplVar21,*param_2 + uVar18 * 0x40 + 0x28);
      }
      uVar1 = (int)uVar18 + 1;
      uVar18 = (ulong)uVar1;
    } while (uVar1 < *(uint *)(param_2 + 1));
  }
  return 1;
}

// ==== IInfoBaseMap<unsigned long, DeityInfo>::DeserializeChild(Aska::ASON::AValue::AMap const*)
// vaddr 0x154d39c | ghidra 0x164d39c | size 1028 | symbol _ZN12IInfoBaseMapIm9DeityInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Type propagation algorithm not settling */

undefined8
_ZN12IInfoBaseMapIm9DeityInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE
          (long *param_1,long *param_2)

{
  uint uVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined *puVar5;
  undefined *puVar6;
  undefined *puVar7;
  undefined *puVar8;
  undefined *puVar9;
  long lVar10;
  int iVar11;
  long *plVar12;
  long *******ppppppplVar13;
  long *******ppppppplVar14;
  ulong uVar15;
  long *******ppppppplVar16;
  long *******ppppppplVar17;
  long *******ppppppplVar18;
  undefined *puStack_150;
  undefined8 *puStack_148;
  undefined8 auStack_140 [2];
  undefined8 *puStack_130;
  undefined8 uStack_128;
  undefined8 uStack_120;
  undefined *puStack_118;
  undefined8 uStack_110;
  undefined1 uStack_108;
  undefined1 auStack_100 [24];
  undefined *puStack_e8;
  undefined8 uStack_e0;
  undefined1 uStack_d8;
  undefined1 auStack_d0 [24];
  undefined *puStack_b8;
  undefined8 uStack_b0;
  undefined1 uStack_a8;
  undefined1 auStack_a0 [24];
  long ******pppppplStack_88;
  long *******appppppplStack_80 [3];
  long *******ppppppplStack_68;
  
  ppppppplVar18 = (long *******)(param_1 + 8);
  plVar12 = param_1 + 7;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, DeityInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, DeityInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, DeityInfo>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, DeityInfo>, void*>*)(plVar12,*ppppppplVar18);
  param_1[7] = (long)ppppppplVar18;
  param_1[8] = 0;
  param_1[9] = 0;
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0282d54e/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\Info/InfoBase.h"*/,0x1c1,&UNK_027dc58a/*"apParser is null."*/);
    iVar11 = iRam0000000000000008;
  }
  else {
    iVar11 = (int)param_2[1];
  }
  if (iVar11 != 0) {
    puVar2 = PTR__ZTV9DeityInfo_02cc11d0 + 0x10;
    puVar3 = PTR__ZTV22CParameterPropertyBaseILj47EE_02cba780 + 0x10;
    puVar4 = PTR__ZTV23CParameterPropertyValueIjLj47E18CPropertyConverterE_02cc0678 + 0x10;
    puVar5 = PTR__ZTV22CParameterPropertyBaseILj48EE_02cba0d0 + 0x10;
    puVar6 = PTR__ZTV23CParameterPropertyValueIjLj48E18CPropertyConverterE_02cc4e68 + 0x10;
    puVar7 = PTR__ZTV22CParameterPropertyBaseILj49EE_02cc4550 + 0x10;
    puVar8 = PTR__ZTV23CParameterPropertyValueIjLj49E18CPropertyConverterE_02cc0590 + 0x10;
    uVar15 = 0;
    puVar9 = PTR__ZTV8InfoBase_02cc49c8 + 0x10;
    do {
      pppppplStack_88 =
           (long ******)(**(code **)(*param_1 + 0x20))(param_1,*param_2 + uVar15 * 0x40);
      ppppppplVar14 = (long *******)param_1[8];
      ppppppplVar13 = ppppppplVar18;
      if ((long *******)param_1[8] == (long *******)0x0) {
code_r0x0164d540:
        memset(auStack_140,0,0xb8);
        uStack_128 = 0;
        uStack_120 = 0;
        uStack_108 = 0;
        uStack_110 = 0;
        puStack_150 = puVar2;
        puStack_148 = auStack_140;
        puStack_130 = &uStack_128;
        puStack_118 = puVar3;
        Framework::CHash32::CHash32()(auStack_100);
        uStack_d8 = 0;
        uStack_e0 = 0;
        puStack_118 = puVar4;
        puStack_e8 = puVar5;
        Framework::CHash32::CHash32()(auStack_d0);
        uStack_a8 = 0;
        uStack_b0 = 0;
        puStack_e8 = puVar6;
        puStack_b8 = puVar7;
        Framework::CHash32::CHash32()(auStack_a0);
        ppppppplVar14 = (long *******)*ppppppplVar18;
        if ((long *******)*ppppppplVar18 == (long *******)0x0) {
          ppppppplVar17 = (long *******)*ppppppplVar18;
          ppppppplVar13 = ppppppplVar18;
          ppppppplVar16 = ppppppplVar18;
        }
        else {
          do {
            while (ppppppplVar13 = ppppppplVar14, ppppppplVar13[4] <= pppppplStack_88) {
              if (pppppplStack_88 <= ppppppplVar13[4]) {
                ppppppplVar17 = ppppppplVar13;
                ppppppplVar16 = (long *******)&ppppppplStack_68;
                goto joined_r0x0164d62c;
              }
              ppppppplVar16 = ppppppplVar13 + 1;
              ppppppplVar14 = (long *******)*ppppppplVar16;
              if ((long *******)*ppppppplVar16 == (long *******)0x0) {
                ppppppplVar17 = (long *******)*ppppppplVar16;
                goto joined_r0x0164d62c;
              }
            }
            ppppppplVar14 = (long *******)*ppppppplVar13;
          } while ((long *******)*ppppppplVar13 != (long *******)0x0);
          ppppppplVar17 = (long *******)*ppppppplVar13;
          ppppppplVar16 = ppppppplVar13;
        }
joined_r0x0164d62c:
        ppppppplStack_68 = ppppppplVar13;
        if (ppppppplVar17 == (long *******)0x0) {
          puStack_b8 = puVar8;
          std::__ndk1::unique_ptr<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, DeityInfo>, void*>, std::__ndk1::__tree_node_destructor<Framework::CSTLAllocator<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, DeityInfo>, void*>, Framework::CSTLMapAllocatorInf> > > std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, DeityInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, DeityInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, DeityInfo>, Framework::CSTLMapAllocatorInf> >::__construct_node<unsigned long&, DeityInfo>(unsigned long&, DeityInfo&&)(appppppplStack_80,plVar12,&pppppplStack_88,&puStack_150);
          *appppppplStack_80[0] = (long ******)0x0;
          appppppplStack_80[0][1] = (long ******)0x0;
          appppppplStack_80[0][2] = (long ******)ppppppplVar13;
          *ppppppplVar16 = (long ******)appppppplStack_80[0];
          ppppppplVar14 = appppppplStack_80[0];
          if (*(long *)*plVar12 != 0) {
            *plVar12 = *(long *)*plVar12;
            ppppppplVar14 = (long *******)*ppppppplVar16;
          }
          void std::__ndk1::__tree_balance_after_insert<std::__ndk1::__tree_node_base<void*>*>(std::__ndk1::__tree_node_base<void*>*, std::__ndk1::__tree_node_base<void*>*)(param_1[8],ppppppplVar14);
          param_1[9] = param_1[9] + 1;
          ppppppplVar17 = appppppplStack_80[0];
        }
        puStack_150 = PTR__ZTV9DeityInfo_02cc11d0 + 0x10;
        puStack_b8 = PTR__ZTV22CParameterPropertyBaseILj49EE_02cc4550 + 0x10;
        Framework::CHash32::~CHash32()(auStack_a0);
        puStack_e8 = PTR__ZTV22CParameterPropertyBaseILj48EE_02cba0d0 + 0x10;
        Framework::CHash32::~CHash32()(auStack_d0);
        puStack_118 = PTR__ZTV22CParameterPropertyBaseILj47EE_02cba780 + 0x10;
        Framework::CHash32::~CHash32()(auStack_100);
        puStack_150 = puVar9;
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*)(&puStack_130,uStack_128);
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*)(&puStack_148,auStack_140[0]);
        ppppppplVar17 = ppppppplVar17 + 5;
        (*(code *)(*ppppppplVar17)[2])(ppppppplVar17);
      }
      else {
        do {
          while (ppppppplVar17 = ppppppplVar14, ppppppplVar17[4] < pppppplStack_88) {
            ppppppplVar14 = (long *******)ppppppplVar17[1];
            if ((long *******)ppppppplVar17[1] == (long *******)0x0) {
              ppppppplVar17 = ppppppplVar13;
              if (ppppppplVar13 != ppppppplVar18) goto code_r0x0164d524;
              goto code_r0x0164d540;
            }
          }
          ppppppplVar14 = (long *******)*ppppppplVar17;
          ppppppplVar13 = ppppppplVar17;
        } while ((long *******)*ppppppplVar17 != (long *******)0x0);
        if (ppppppplVar17 == ppppppplVar18) goto code_r0x0164d540;
code_r0x0164d524:
        if ((pppppplStack_88 < ppppppplVar17[4]) || (ppppppplVar17 == ppppppplVar18))
        goto code_r0x0164d540;
        ppppppplVar17 = ppppppplVar17 + 5;
      }
      lVar10 = *param_2 + uVar15 * 0x40;
      iVar11 = *(int *)(lVar10 + 0x20);
      if (iVar11 == 6) {
        (*(code *)**ppppppplVar17)(ppppppplVar17,lVar10 + 0x28);
      }
      else if (iVar11 == 7) {
        (*(code *)(*ppppppplVar17)[1])(ppppppplVar17,*param_2 + uVar15 * 0x40 + 0x28);
      }
      uVar1 = (int)uVar15 + 1;
      uVar15 = (ulong)uVar1;
    } while (uVar1 < *(uint *)(param_2 + 1));
  }
  return 1;
}

// ==== IInfoBaseMap<unsigned long, CFollowInfo>::DeserializeChild(Aska::ASON::AValue::AMap const*)
// vaddr 0x154dfa8 | ghidra 0x164dfa8 | size 892 | symbol _ZN12IInfoBaseMapIm11CFollowInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Type propagation algorithm not settling */

undefined8
_ZN12IInfoBaseMapIm11CFollowInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE
          (long *param_1,long *param_2)

{
  uint uVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined *puVar5;
  long lVar6;
  int iVar7;
  long *plVar8;
  long *******ppppppplVar9;
  long *******ppppppplVar10;
  ulong uVar11;
  long *******ppppppplVar12;
  long *******ppppppplVar13;
  long *******ppppppplVar14;
  undefined *puStack_f90;
  undefined8 *puStack_f88;
  undefined8 auStack_f80 [2];
  undefined8 *puStack_f70;
  undefined8 uStack_f68;
  undefined8 uStack_f60;
  undefined *puStack_f58;
  undefined8 uStack_f50;
  undefined1 uStack_f48;
  undefined1 auStack_f40 [24];
  undefined1 auStack_f28 [632];
  undefined1 auStack_cb0 [3112];
  long ******pppppplStack_88;
  long *******appppppplStack_80 [3];
  long *******ppppppplStack_68;
  
  ppppppplVar14 = (long *******)(param_1 + 8);
  plVar8 = param_1 + 7;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CFollowInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CFollowInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CFollowInfo>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CFollowInfo>, void*>*)(plVar8,*ppppppplVar14);
  param_1[7] = (long)ppppppplVar14;
  param_1[8] = 0;
  param_1[9] = 0;
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0282d54e/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\Info/InfoBase.h"*/,0x1c1,&UNK_027dc58a/*"apParser is null."*/);
    iVar7 = iRam0000000000000008;
  }
  else {
    iVar7 = (int)param_2[1];
  }
  if (iVar7 != 0) {
    puVar2 = PTR__ZTV11CFollowInfo_02cbfba0 + 0x10;
    puVar3 = PTR__ZTV22CParameterPropertyBaseILj191EE_02cc1c00 + 0x10;
    puVar4 = PTR__ZTV23CParameterPropertyValueIjLj191E18CPropertyConverterE_02cb9fe8 + 0x10;
    uVar11 = 0;
    puVar5 = PTR__ZTV8InfoBase_02cc49c8 + 0x10;
    do {
      pppppplStack_88 =
           (long ******)(**(code **)(*param_1 + 0x20))(param_1,*param_2 + uVar11 * 0x40);
      ppppppplVar10 = (long *******)param_1[8];
      ppppppplVar9 = ppppppplVar14;
      if ((long *******)param_1[8] == (long *******)0x0) {
code_r0x0164e10c:
        memset(auStack_f80,0,0xef8);
        uStack_f68 = 0;
        uStack_f60 = 0;
        uStack_f48 = 0;
        uStack_f50 = 0;
        puStack_f90 = puVar2;
        puStack_f88 = auStack_f80;
        puStack_f70 = &uStack_f68;
        puStack_f58 = puVar3;
        Framework::CHash32::CHash32()(auStack_f40);
        puStack_f58 = puVar4;
        CFollowPlayerInfo::CFollowPlayerInfo()(auStack_f28);
        CFollowPersonInfo::CFollowPersonInfo()(auStack_cb0);
        ppppppplVar10 = (long *******)*ppppppplVar14;
        if ((long *******)*ppppppplVar14 == (long *******)0x0) {
          ppppppplVar13 = (long *******)*ppppppplVar14;
          ppppppplVar9 = ppppppplVar14;
          ppppppplVar12 = ppppppplVar14;
        }
        else {
          do {
            while (ppppppplVar9 = ppppppplVar10, ppppppplVar9[4] <= pppppplStack_88) {
              if (pppppplStack_88 <= ppppppplVar9[4]) {
                ppppppplVar13 = ppppppplVar9;
                ppppppplVar12 = (long *******)&ppppppplStack_68;
                goto joined_r0x0164e1d0;
              }
              ppppppplVar12 = ppppppplVar9 + 1;
              ppppppplVar10 = (long *******)*ppppppplVar12;
              if ((long *******)*ppppppplVar12 == (long *******)0x0) {
                ppppppplVar13 = (long *******)*ppppppplVar12;
                goto joined_r0x0164e1d0;
              }
            }
            ppppppplVar10 = (long *******)*ppppppplVar9;
          } while ((long *******)*ppppppplVar9 != (long *******)0x0);
          ppppppplVar13 = (long *******)*ppppppplVar9;
          ppppppplVar12 = ppppppplVar9;
        }
joined_r0x0164e1d0:
        ppppppplStack_68 = ppppppplVar9;
        if (ppppppplVar13 == (long *******)0x0) {
          std::__ndk1::unique_ptr<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CFollowInfo>, void*>, std::__ndk1::__tree_node_destructor<Framework::CSTLAllocator<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CFollowInfo>, void*>, Framework::CSTLMapAllocatorInf> > > std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CFollowInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CFollowInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CFollowInfo>, Framework::CSTLMapAllocatorInf> >::__construct_node<unsigned long&, CFollowInfo>(unsigned long&, CFollowInfo&&)(appppppplStack_80,plVar8,&pppppplStack_88,&puStack_f90);
          *appppppplStack_80[0] = (long ******)0x0;
          appppppplStack_80[0][1] = (long ******)0x0;
          appppppplStack_80[0][2] = (long ******)ppppppplVar9;
          *ppppppplVar12 = (long ******)appppppplStack_80[0];
          ppppppplVar10 = appppppplStack_80[0];
          if (*(long *)*plVar8 != 0) {
            *plVar8 = *(long *)*plVar8;
            ppppppplVar10 = (long *******)*ppppppplVar12;
          }
          void std::__ndk1::__tree_balance_after_insert<std::__ndk1::__tree_node_base<void*>*>(std::__ndk1::__tree_node_base<void*>*, std::__ndk1::__tree_node_base<void*>*)(param_1[8],ppppppplVar10);
          param_1[9] = param_1[9] + 1;
          ppppppplVar13 = appppppplStack_80[0];
        }
        puStack_f90 = PTR__ZTV11CFollowInfo_02cbfba0 + 0x10;
        CFollowPersonInfo::~CFollowPersonInfo()(auStack_cb0);
        CFollowPlayerInfo::~CFollowPlayerInfo()(auStack_f28);
        puStack_f58 = PTR__ZTV22CParameterPropertyBaseILj191EE_02cc1c00 + 0x10;
        Framework::CHash32::~CHash32()(auStack_f40);
        puStack_f90 = puVar5;
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*)(&puStack_f70,uStack_f68);
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*)(&puStack_f88,auStack_f80[0]);
        ppppppplVar13 = ppppppplVar13 + 5;
        (*(code *)(*ppppppplVar13)[2])(ppppppplVar13);
      }
      else {
        do {
          while (ppppppplVar13 = ppppppplVar10, ppppppplVar13[4] < pppppplStack_88) {
            ppppppplVar10 = (long *******)ppppppplVar13[1];
            if ((long *******)ppppppplVar13[1] == (long *******)0x0) {
              ppppppplVar13 = ppppppplVar9;
              if (ppppppplVar9 != ppppppplVar14) goto code_r0x0164e0f0;
              goto code_r0x0164e10c;
            }
          }
          ppppppplVar10 = (long *******)*ppppppplVar13;
          ppppppplVar9 = ppppppplVar13;
        } while ((long *******)*ppppppplVar13 != (long *******)0x0);
        if (ppppppplVar13 == ppppppplVar14) goto code_r0x0164e10c;
code_r0x0164e0f0:
        if ((pppppplStack_88 < ppppppplVar13[4]) || (ppppppplVar13 == ppppppplVar14))
        goto code_r0x0164e10c;
        ppppppplVar13 = ppppppplVar13 + 5;
      }
      lVar6 = *param_2 + uVar11 * 0x40;
      iVar7 = *(int *)(lVar6 + 0x20);
      if (iVar7 == 6) {
        (*(code *)**ppppppplVar13)(ppppppplVar13,lVar6 + 0x28);
      }
      else if (iVar7 == 7) {
        (*(code *)(*ppppppplVar13)[1])(ppppppplVar13,*param_2 + uVar11 * 0x40 + 0x28);
      }
      uVar1 = (int)uVar11 + 1;
      uVar11 = (ulong)uVar1;
    } while (uVar1 < *(uint *)(param_2 + 1));
  }
  return 1;
}

// ==== IInfoBaseMap<unsigned long, CFollowPlayerListElementInfo>::DeserializeChild(Aska::ASON::AValue::AMap const*)
// vaddr 0x1550eb8 | ghidra 0x1650eb8 | size 1028 | symbol _ZN12IInfoBaseMapIm28CFollowPlayerListElementInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Type propagation algorithm not settling */

undefined8
_ZN12IInfoBaseMapIm28CFollowPlayerListElementInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE
          (long *param_1,long *param_2)

{
  uint uVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined *puVar5;
  undefined *puVar6;
  undefined *puVar7;
  undefined *puVar8;
  undefined *puVar9;
  undefined *puVar10;
  undefined *puVar11;
  undefined *puVar12;
  long lVar13;
  int iVar14;
  long *plVar15;
  long *******ppppppplVar16;
  long *******ppppppplVar17;
  ulong uVar18;
  long *******ppppppplVar19;
  long *******ppppppplVar20;
  long *******ppppppplVar21;
  undefined *puStack_1c0;
  undefined1 *puStack_1b8;
  undefined1 auStack_1b0 [16];
  undefined8 *puStack_1a0;
  undefined8 uStack_198;
  undefined8 uStack_190;
  undefined *puStack_188;
  undefined8 uStack_180;
  undefined1 uStack_178;
  undefined1 auStack_170 [24];
  undefined *puStack_158;
  undefined8 uStack_150;
  undefined1 uStack_148;
  undefined1 auStack_140 [24];
  undefined *puStack_128;
  undefined8 uStack_120;
  undefined1 uStack_118;
  undefined1 auStack_110 [16];
  undefined8 uStack_100;
  undefined8 uStack_f8;
  undefined8 uStack_f0;
  undefined *puStack_e8;
  undefined8 uStack_e0;
  undefined1 uStack_d8;
  undefined1 auStack_d0 [24];
  undefined *puStack_b8;
  undefined8 uStack_b0;
  undefined1 uStack_a8;
  undefined1 auStack_a0 [24];
  long ******pppppplStack_88;
  long *******appppppplStack_80 [3];
  long *******ppppppplStack_68;
  
  ppppppplVar21 = (long *******)(param_1 + 8);
  plVar15 = param_1 + 7;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CFollowPlayerListElementInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CFollowPlayerListElementInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CFollowPlayerListElementInfo>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CFollowPlayerListElementInfo>, void*>*)(plVar15,*ppppppplVar21);
  param_1[7] = (long)ppppppplVar21;
  param_1[8] = 0;
  param_1[9] = 0;
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0282d54e/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\Info/InfoBase.h"*/,0x1c1,&UNK_027dc58a/*"apParser is null."*/);
    iVar14 = iRam0000000000000008;
  }
  else {
    iVar14 = (int)param_2[1];
  }
  if (iVar14 != 0) {
    puVar2 = PTR__ZTV28CFollowPlayerListElementInfo_02cb7a60 + 0x10;
    puVar3 = PTR__ZTV22CParameterPropertyBaseILj231EE_02cc1ee0 + 0x10;
    puVar4 = PTR__ZTV23CParameterPropertyValueIjLj231E18CPropertyConverterE_02cc2d08 + 0x10;
    puVar5 = PTR__ZTV22CParameterPropertyBaseILj232EE_02cbee90 + 0x10;
    puVar6 = PTR__ZTV23CParameterPropertyValueIjLj232E18CPropertyConverterE_02cc05f8 + 0x10;
    puVar7 = PTR__ZTV22CParameterPropertyBaseILj233EE_02cb7178 + 0x10;
    puVar8 = PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj233EE_02cbdac0
             + 0x10;
    puVar9 = PTR__ZTV22CParameterPropertyBaseILj234EE_02cba3b8 + 0x10;
    puVar10 = PTR__ZTV23CParameterPropertyValueIjLj234E18CPropertyConverterE_02cc2bd0 + 0x10;
    uVar18 = 0;
    puVar11 = PTR__ZTV22CParameterPropertyBaseILj235EE_02cc2298 + 0x10;
    puVar12 = PTR__ZTV23CParameterPropertyValueIbLj235E18CPropertyConverterE_02cc3468 + 0x10;
    do {
      pppppplStack_88 =
           (long ******)(**(code **)(*param_1 + 0x20))(param_1,*param_2 + uVar18 * 0x40);
      ppppppplVar17 = (long *******)param_1[8];
      ppppppplVar16 = ppppppplVar21;
      if ((long *******)param_1[8] == (long *******)0x0) {
code_r0x01651094:
        memset(auStack_1b0,0,0x128);
        uStack_198 = 0;
        uStack_190 = 0;
        uStack_178 = 0;
        uStack_180 = 0;
        puStack_1c0 = puVar2;
        puStack_1b8 = auStack_1b0;
        puStack_1a0 = &uStack_198;
        puStack_188 = puVar3;
        Framework::CHash32::CHash32()(auStack_170);
        uStack_148 = 0;
        uStack_150 = 0;
        puStack_188 = puVar4;
        puStack_158 = puVar5;
        Framework::CHash32::CHash32()(auStack_140);
        uStack_118 = 0;
        uStack_120 = 0;
        puStack_158 = puVar6;
        puStack_128 = puVar7;
        Framework::CHash32::CHash32()(auStack_110);
        uStack_f8 = 0;
        uStack_f0 = 0;
        uStack_100 = 0;
        uStack_d8 = 0;
        uStack_e0 = 0;
        puStack_128 = puVar8;
        puStack_e8 = puVar9;
        Framework::CHash32::CHash32()(auStack_d0);
        uStack_a8 = 0;
        uStack_b0 = 0;
        puStack_e8 = puVar10;
        puStack_b8 = puVar11;
        Framework::CHash32::CHash32()(auStack_a0);
        ppppppplVar17 = (long *******)*ppppppplVar21;
        if ((long *******)*ppppppplVar21 == (long *******)0x0) {
          ppppppplVar20 = (long *******)*ppppppplVar21;
          ppppppplVar16 = ppppppplVar21;
          ppppppplVar19 = ppppppplVar21;
        }
        else {
          do {
            while (ppppppplVar16 = ppppppplVar17, ppppppplVar16[4] <= pppppplStack_88) {
              if (pppppplStack_88 <= ppppppplVar16[4]) {
                ppppppplVar20 = ppppppplVar16;
                ppppppplVar19 = (long *******)&ppppppplStack_68;
                goto joined_r0x016511b8;
              }
              ppppppplVar19 = ppppppplVar16 + 1;
              ppppppplVar17 = (long *******)*ppppppplVar19;
              if ((long *******)*ppppppplVar19 == (long *******)0x0) {
                ppppppplVar20 = (long *******)*ppppppplVar19;
                goto joined_r0x016511b8;
              }
            }
            ppppppplVar17 = (long *******)*ppppppplVar16;
          } while ((long *******)*ppppppplVar16 != (long *******)0x0);
          ppppppplVar20 = (long *******)*ppppppplVar16;
          ppppppplVar19 = ppppppplVar16;
        }
joined_r0x016511b8:
        puStack_b8 = puVar12;
        ppppppplStack_68 = ppppppplVar16;
        if (ppppppplVar20 == (long *******)0x0) {
          std::__ndk1::unique_ptr<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CFollowPlayerListElementInfo>, void*>, std::__ndk1::__tree_node_destructor<Framework::CSTLAllocator<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CFollowPlayerListElementInfo>, void*>, Framework::CSTLMapAllocatorInf> > > std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CFollowPlayerListElementInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CFollowPlayerListElementInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CFollowPlayerListElementInfo>, Framework::CSTLMapAllocatorInf> >::__construct_node<unsigned long&, CFollowPlayerListElementInfo>(unsigned long&, CFollowPlayerListElementInfo&&)(appppppplStack_80,plVar15,&pppppplStack_88,&puStack_1c0);
          *appppppplStack_80[0] = (long ******)0x0;
          appppppplStack_80[0][1] = (long ******)0x0;
          appppppplStack_80[0][2] = (long ******)ppppppplVar16;
          *ppppppplVar19 = (long ******)appppppplStack_80[0];
          ppppppplVar17 = appppppplStack_80[0];
          if (*(long *)*plVar15 != 0) {
            *plVar15 = *(long *)*plVar15;
            ppppppplVar17 = (long *******)*ppppppplVar19;
          }
          void std::__ndk1::__tree_balance_after_insert<std::__ndk1::__tree_node_base<void*>*>(std::__ndk1::__tree_node_base<void*>*, std::__ndk1::__tree_node_base<void*>*)(param_1[8],ppppppplVar17);
          param_1[9] = param_1[9] + 1;
          ppppppplVar20 = appppppplStack_80[0];
        }
        CFollowPlayerListElementInfo::~CFollowPlayerListElementInfo()(&puStack_1c0);
        ppppppplVar20 = ppppppplVar20 + 5;
        (*(code *)(*ppppppplVar20)[2])(ppppppplVar20);
      }
      else {
        do {
          while (ppppppplVar20 = ppppppplVar17, ppppppplVar20[4] < pppppplStack_88) {
            ppppppplVar17 = (long *******)ppppppplVar20[1];
            if ((long *******)ppppppplVar20[1] == (long *******)0x0) {
              ppppppplVar20 = ppppppplVar16;
              if (ppppppplVar16 != ppppppplVar21) goto code_r0x01651078;
              goto code_r0x01651094;
            }
          }
          ppppppplVar17 = (long *******)*ppppppplVar20;
          ppppppplVar16 = ppppppplVar20;
        } while ((long *******)*ppppppplVar20 != (long *******)0x0);
        if (ppppppplVar20 == ppppppplVar21) goto code_r0x01651094;
code_r0x01651078:
        if ((pppppplStack_88 < ppppppplVar20[4]) || (ppppppplVar20 == ppppppplVar21))
        goto code_r0x01651094;
        ppppppplVar20 = ppppppplVar20 + 5;
      }
      lVar13 = *param_2 + uVar18 * 0x40;
      iVar14 = *(int *)(lVar13 + 0x20);
      if (iVar14 == 6) {
        (*(code *)**ppppppplVar20)(ppppppplVar20,lVar13 + 0x28);
      }
      else if (iVar14 == 7) {
        (*(code *)(*ppppppplVar20)[1])(ppppppplVar20,*param_2 + uVar18 * 0x40 + 0x28);
      }
      uVar1 = (int)uVar18 + 1;
      uVar18 = (ulong)uVar1;
    } while (uVar1 < *(uint *)(param_2 + 1));
  }
  return 1;
}

// ==== IInfoBaseMap<unsigned long, CFriendGaugeInfo>::DeserializeChild(Aska::ASON::AValue::AMap const*)
// vaddr 0x1551d78 | ghidra 0x1651d78 | size 1188 | symbol _ZN12IInfoBaseMapIm16CFriendGaugeInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Type propagation algorithm not settling */

undefined8
_ZN12IInfoBaseMapIm16CFriendGaugeInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE
          (long *param_1,long *param_2)

{
  uint uVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined *puVar5;
  undefined *puVar6;
  undefined *puVar7;
  undefined *puVar8;
  undefined *puVar9;
  undefined *puVar10;
  undefined *puVar11;
  undefined *puVar12;
  undefined *puVar13;
  undefined *puVar14;
  undefined *puVar15;
  undefined *puVar16;
  long lVar17;
  int iVar18;
  long *plVar19;
  long *******ppppppplVar20;
  long *******ppppppplVar21;
  ulong uVar22;
  long *******ppppppplVar23;
  long *******ppppppplVar24;
  long *******ppppppplVar25;
  undefined *puStack_230;
  undefined1 *puStack_228;
  undefined1 auStack_220 [16];
  undefined8 *puStack_210;
  undefined8 uStack_208;
  undefined8 uStack_200;
  undefined *puStack_1f8;
  undefined8 uStack_1f0;
  undefined1 uStack_1e8;
  undefined1 auStack_1e0 [24];
  undefined *puStack_1c8;
  undefined8 uStack_1c0;
  undefined1 uStack_1b8;
  undefined1 auStack_1b0 [24];
  undefined *puStack_198;
  undefined8 uStack_190;
  undefined1 uStack_188;
  undefined1 auStack_180 [24];
  undefined *puStack_168;
  undefined8 uStack_160;
  undefined1 uStack_158;
  undefined1 auStack_150 [24];
  undefined *puStack_138;
  undefined8 uStack_130;
  undefined1 uStack_128;
  undefined1 auStack_120 [24];
  undefined *puStack_108;
  undefined8 uStack_100;
  undefined1 uStack_f8;
  undefined1 auStack_f0 [16];
  undefined8 uStack_e0;
  undefined8 uStack_d8;
  undefined8 uStack_d0;
  undefined *puStack_c8;
  undefined8 uStack_c0;
  undefined1 uStack_b8;
  undefined1 auStack_b0 [16];
  undefined8 uStack_a0;
  undefined8 uStack_98;
  undefined8 uStack_90;
  long ******pppppplStack_88;
  long *******appppppplStack_80 [3];
  long *******ppppppplStack_68;
  
  ppppppplVar24 = (long *******)(param_1 + 8);
  plVar19 = param_1 + 7;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CFriendGaugeInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CFriendGaugeInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CFriendGaugeInfo>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CFriendGaugeInfo>, void*>*)(plVar19,*ppppppplVar24);
  param_1[7] = (long)ppppppplVar24;
  param_1[8] = 0;
  param_1[9] = 0;
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0282d54e/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\Info/InfoBase.h"*/,0x1c1,&UNK_027dc58a/*"apParser is null."*/);
    iVar18 = iRam0000000000000008;
  }
  else {
    iVar18 = (int)param_2[1];
  }
  if (iVar18 != 0) {
    puVar2 = PTR__ZTV16CFriendGaugeInfo_02cb7c80 + 0x10;
    puVar3 = PTR__ZTV22CParameterPropertyBaseILj17EE_02cba1e8 + 0x10;
    puVar4 = PTR__ZTV23CParameterPropertyValueIjLj17E18CPropertyConverterE_02cbb3b8 + 0x10;
    puVar5 = PTR__ZTV22CParameterPropertyBaseILj18EE_02cbe238 + 0x10;
    puVar6 = PTR__ZTV23CParameterPropertyValueIjLj18E18CPropertyConverterE_02cbcd58 + 0x10;
    puVar7 = PTR__ZTV22CParameterPropertyBaseILj19EE_02cc4c98 + 0x10;
    puVar8 = PTR__ZTV23CParameterPropertyValueIjLj19E18CPropertyConverterE_02cc13e8 + 0x10;
    puVar9 = PTR__ZTV22CParameterPropertyBaseILj20EE_02cc0d08 + 0x10;
    puVar10 = PTR__ZTV23CParameterPropertyValueIjLj20E18CPropertyConverterE_02cc2ce0 + 0x10;
    puVar11 = PTR__ZTV22CParameterPropertyBaseILj21EE_02cc1310 + 0x10;
    puVar12 = PTR__ZTV23CParameterPropertyValueIjLj21E18CPropertyConverterE_02cbeae0 + 0x10;
    puVar13 = PTR__ZTV22CParameterPropertyBaseILj22EE_02cc4630 + 0x10;
    puVar14 = PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj22EE_02cbe640
              + 0x10;
    puVar15 = PTR__ZTV22CParameterPropertyBaseILj23EE_02cbad98 + 0x10;
    uVar22 = 0;
    puVar16 = PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj23EE_02cb8300
              + 0x10;
    do {
      pppppplStack_88 =
           (long ******)(**(code **)(*param_1 + 0x20))(param_1,*param_2 + uVar22 * 0x40);
      ppppppplVar21 = (long *******)param_1[8];
      ppppppplVar20 = ppppppplVar24;
      if ((long *******)param_1[8] == (long *******)0x0) {
code_r0x01651fac:
        memset(auStack_220,0,0x198);
        uStack_208 = 0;
        uStack_200 = 0;
        uStack_1e8 = 0;
        uStack_1f0 = 0;
        puStack_230 = puVar2;
        puStack_228 = auStack_220;
        puStack_210 = &uStack_208;
        puStack_1f8 = puVar3;
        Framework::CHash32::CHash32()(auStack_1e0);
        uStack_1b8 = 0;
        uStack_1c0 = 0;
        puStack_1f8 = puVar4;
        puStack_1c8 = puVar5;
        Framework::CHash32::CHash32()(auStack_1b0);
        uStack_188 = 0;
        uStack_190 = 0;
        puStack_1c8 = puVar6;
        puStack_198 = puVar7;
        Framework::CHash32::CHash32()(auStack_180);
        uStack_158 = 0;
        uStack_160 = 0;
        puStack_198 = puVar8;
        puStack_168 = puVar9;
        Framework::CHash32::CHash32()(auStack_150);
        uStack_128 = 0;
        uStack_130 = 0;
        puStack_168 = puVar10;
        puStack_138 = puVar11;
        Framework::CHash32::CHash32()(auStack_120);
        uStack_f8 = 0;
        uStack_100 = 0;
        puStack_138 = puVar12;
        puStack_108 = puVar13;
        Framework::CHash32::CHash32()(auStack_f0);
        uStack_d8 = 0;
        uStack_d0 = 0;
        uStack_e0 = 0;
        uStack_c0 = 0;
        uStack_b8 = 0;
        puStack_108 = puVar14;
        puStack_c8 = puVar15;
        Framework::CHash32::CHash32()(auStack_b0);
        uStack_98 = 0;
        uStack_90 = 0;
        uStack_a0 = 0;
        ppppppplVar21 = (long *******)*ppppppplVar24;
        if ((long *******)*ppppppplVar24 == (long *******)0x0) {
          ppppppplVar23 = (long *******)*ppppppplVar24;
          ppppppplVar20 = ppppppplVar24;
          ppppppplVar25 = ppppppplVar24;
        }
        else {
          do {
            while (ppppppplVar20 = ppppppplVar21, ppppppplVar20[4] <= pppppplStack_88) {
              if (pppppplStack_88 <= ppppppplVar20[4]) {
                ppppppplVar23 = ppppppplVar20;
                ppppppplVar25 = (long *******)&ppppppplStack_68;
                goto joined_r0x01652118;
              }
              ppppppplVar25 = ppppppplVar20 + 1;
              ppppppplVar21 = (long *******)*ppppppplVar25;
              if ((long *******)*ppppppplVar25 == (long *******)0x0) {
                ppppppplVar23 = (long *******)*ppppppplVar25;
                goto joined_r0x01652118;
              }
            }
            ppppppplVar21 = (long *******)*ppppppplVar20;
          } while ((long *******)*ppppppplVar20 != (long *******)0x0);
          ppppppplVar23 = (long *******)*ppppppplVar20;
          ppppppplVar25 = ppppppplVar20;
        }
joined_r0x01652118:
        puStack_c8 = puVar16;
        ppppppplStack_68 = ppppppplVar20;
        if (ppppppplVar23 == (long *******)0x0) {
          std::__ndk1::unique_ptr<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CFriendGaugeInfo>, void*>, std::__ndk1::__tree_node_destructor<Framework::CSTLAllocator<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CFriendGaugeInfo>, void*>, Framework::CSTLMapAllocatorInf> > > std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CFriendGaugeInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CFriendGaugeInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CFriendGaugeInfo>, Framework::CSTLMapAllocatorInf> >::__construct_node<unsigned long&, CFriendGaugeInfo>(unsigned long&, CFriendGaugeInfo&&)(appppppplStack_80,plVar19,&pppppplStack_88,&puStack_230);
          *appppppplStack_80[0] = (long ******)0x0;
          appppppplStack_80[0][1] = (long ******)0x0;
          appppppplStack_80[0][2] = (long ******)ppppppplVar20;
          *ppppppplVar25 = (long ******)appppppplStack_80[0];
          ppppppplVar21 = appppppplStack_80[0];
          if (*(long *)*plVar19 != 0) {
            *plVar19 = *(long *)*plVar19;
            ppppppplVar21 = (long *******)*ppppppplVar25;
          }
          void std::__ndk1::__tree_balance_after_insert<std::__ndk1::__tree_node_base<void*>*>(std::__ndk1::__tree_node_base<void*>*, std::__ndk1::__tree_node_base<void*>*)(param_1[8],ppppppplVar21);
          param_1[9] = param_1[9] + 1;
          ppppppplVar23 = appppppplStack_80[0];
        }
        CFriendGaugeInfo::~CFriendGaugeInfo()(&puStack_230);
        ppppppplVar23 = ppppppplVar23 + 5;
        (*(code *)(*ppppppplVar23)[2])(ppppppplVar23);
      }
      else {
        do {
          while (ppppppplVar23 = ppppppplVar21, ppppppplVar23[4] < pppppplStack_88) {
            ppppppplVar21 = (long *******)ppppppplVar23[1];
            if ((long *******)ppppppplVar23[1] == (long *******)0x0) {
              ppppppplVar23 = ppppppplVar20;
              if (ppppppplVar20 != ppppppplVar24) goto code_r0x01651f90;
              goto code_r0x01651fac;
            }
          }
          ppppppplVar21 = (long *******)*ppppppplVar23;
          ppppppplVar20 = ppppppplVar23;
        } while ((long *******)*ppppppplVar23 != (long *******)0x0);
        if (ppppppplVar23 == ppppppplVar24) goto code_r0x01651fac;
code_r0x01651f90:
        if ((pppppplStack_88 < ppppppplVar23[4]) || (ppppppplVar23 == ppppppplVar24))
        goto code_r0x01651fac;
        ppppppplVar23 = ppppppplVar23 + 5;
      }
      lVar17 = *param_2 + uVar22 * 0x40;
      iVar18 = *(int *)(lVar17 + 0x20);
      if (iVar18 == 6) {
        (*(code *)**ppppppplVar23)(ppppppplVar23,lVar17 + 0x28);
      }
      else if (iVar18 == 7) {
        (*(code *)(*ppppppplVar23)[1])(ppppppplVar23,*param_2 + uVar22 * 0x40 + 0x28);
      }
      uVar1 = (int)uVar22 + 1;
      uVar22 = (ulong)uVar1;
    } while (uVar1 < *(uint *)(param_2 + 1));
  }
  return 1;
}

// ==== IInfoBaseMap<unsigned long, CAchievementInfo>::DeserializeChild(Aska::ASON::AValue::AMap const*)
// vaddr 0x1554e34 | ghidra 0x1654e34 | size 1168 | symbol _ZN12IInfoBaseMapIm16CAchievementInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Type propagation algorithm not settling */

undefined8
_ZN12IInfoBaseMapIm16CAchievementInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE
          (long *param_1,long *param_2)

{
  uint uVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined *puVar5;
  undefined *puVar6;
  undefined *puVar7;
  undefined *puVar8;
  undefined *puVar9;
  undefined *puVar10;
  undefined *puVar11;
  undefined *puVar12;
  undefined *puVar13;
  undefined *puVar14;
  undefined *puVar15;
  undefined *puVar16;
  long lVar17;
  int iVar18;
  long *plVar19;
  long *******ppppppplVar20;
  long *******ppppppplVar21;
  ulong uVar22;
  long *******ppppppplVar23;
  long *******ppppppplVar24;
  long *******ppppppplVar25;
  undefined *puStack_220;
  undefined1 *puStack_218;
  undefined1 auStack_210 [16];
  undefined8 *puStack_200;
  undefined8 uStack_1f8;
  undefined8 uStack_1f0;
  undefined *puStack_1e8;
  undefined8 uStack_1e0;
  undefined1 uStack_1d8;
  undefined1 auStack_1d0 [24];
  undefined *puStack_1b8;
  undefined8 uStack_1b0;
  undefined1 uStack_1a8;
  undefined1 auStack_1a0 [24];
  undefined *puStack_188;
  undefined8 uStack_180;
  undefined1 uStack_178;
  undefined1 auStack_170 [24];
  undefined *puStack_158;
  undefined8 uStack_150;
  undefined1 uStack_148;
  undefined1 auStack_140 [16];
  undefined8 uStack_130;
  undefined8 uStack_128;
  undefined8 uStack_120;
  undefined *puStack_118;
  undefined8 uStack_110;
  undefined1 uStack_108;
  undefined1 auStack_100 [24];
  undefined *puStack_e8;
  undefined8 uStack_e0;
  undefined1 uStack_d8;
  undefined1 auStack_d0 [24];
  undefined *puStack_b8;
  undefined8 uStack_b0;
  undefined1 uStack_a8;
  undefined1 auStack_a0 [24];
  long ******pppppplStack_88;
  long *******appppppplStack_80 [3];
  long *******ppppppplStack_68;
  
  ppppppplVar24 = (long *******)(param_1 + 8);
  plVar19 = param_1 + 7;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CAchievementInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CAchievementInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CAchievementInfo>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CAchievementInfo>, void*>*)(plVar19,*ppppppplVar24);
  param_1[7] = (long)ppppppplVar24;
  param_1[8] = 0;
  param_1[9] = 0;
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0282d54e/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\Info/InfoBase.h"*/,0x1c1,&UNK_027dc58a/*"apParser is null."*/);
    iVar18 = iRam0000000000000008;
  }
  else {
    iVar18 = (int)param_2[1];
  }
  if (iVar18 != 0) {
    puVar2 = PTR__ZTV16CAchievementInfo_02cbcd98 + 0x10;
    puVar3 = PTR__ZTV22CParameterPropertyBaseILj51EE_02cba2b8 + 0x10;
    puVar4 = PTR__ZTV23CParameterPropertyValueImLj51E18CPropertyConverterE_02cc47a0 + 0x10;
    puVar5 = PTR__ZTV22CParameterPropertyBaseILj52EE_02cba830 + 0x10;
    puVar6 = PTR__ZTV23CParameterPropertyValueIjLj52E18CPropertyConverterE_02cbb590 + 0x10;
    puVar7 = PTR__ZTV22CParameterPropertyBaseILj53EE_02cb75b8 + 0x10;
    puVar8 = PTR__ZTV23CParameterPropertyValueIjLj53E18CPropertyConverterE_02cbe708 + 0x10;
    puVar9 = PTR__ZTV22CParameterPropertyBaseILj54EE_02cba678 + 0x10;
    puVar10 = PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj54EE_02cb72a8
              + 0x10;
    puVar11 = PTR__ZTV22CParameterPropertyBaseILj55EE_02cb81c8 + 0x10;
    puVar12 = PTR__ZTV23CParameterPropertyValueIjLj55E18CPropertyConverterE_02cbb740 + 0x10;
    puVar13 = PTR__ZTV22CParameterPropertyBaseILj56EE_02cbb320 + 0x10;
    puVar14 = PTR__ZTV23CParameterPropertyValueIjLj56E18CPropertyConverterE_02cbc420 + 0x10;
    uVar22 = 0;
    puVar15 = PTR__ZTV22CParameterPropertyBaseILj57EE_02cbe5f0 + 0x10;
    puVar16 = PTR__ZTV23CParameterPropertyValueIbLj57E18CPropertyConverterE_02cbdda8 + 0x10;
    do {
      pppppplStack_88 =
           (long ******)(**(code **)(*param_1 + 0x20))(param_1,*param_2 + uVar22 * 0x40);
      ppppppplVar21 = (long *******)param_1[8];
      ppppppplVar20 = ppppppplVar24;
      if ((long *******)param_1[8] == (long *******)0x0) {
code_r0x01655060:
        memset(auStack_210,0,0x188);
        uStack_1f8 = 0;
        uStack_1f0 = 0;
        uStack_1d8 = 0;
        uStack_1e0 = 0;
        puStack_220 = puVar2;
        puStack_218 = auStack_210;
        puStack_200 = &uStack_1f8;
        puStack_1e8 = puVar3;
        Framework::CHash32::CHash32()(auStack_1d0);
        uStack_1a8 = 0;
        uStack_1b0 = 0;
        puStack_1e8 = puVar4;
        puStack_1b8 = puVar5;
        Framework::CHash32::CHash32()(auStack_1a0);
        uStack_178 = 0;
        uStack_180 = 0;
        puStack_1b8 = puVar6;
        puStack_188 = puVar7;
        Framework::CHash32::CHash32()(auStack_170);
        uStack_148 = 0;
        uStack_150 = 0;
        puStack_188 = puVar8;
        puStack_158 = puVar9;
        Framework::CHash32::CHash32()(auStack_140);
        uStack_128 = 0;
        uStack_120 = 0;
        uStack_130 = 0;
        uStack_108 = 0;
        uStack_110 = 0;
        puStack_158 = puVar10;
        puStack_118 = puVar11;
        Framework::CHash32::CHash32()(auStack_100);
        uStack_d8 = 0;
        uStack_e0 = 0;
        puStack_118 = puVar12;
        puStack_e8 = puVar13;
        Framework::CHash32::CHash32()(auStack_d0);
        uStack_b0 = 0;
        uStack_a8 = 0;
        puStack_e8 = puVar14;
        puStack_b8 = puVar15;
        Framework::CHash32::CHash32()(auStack_a0);
        ppppppplVar21 = (long *******)*ppppppplVar24;
        if ((long *******)*ppppppplVar24 == (long *******)0x0) {
          ppppppplVar23 = (long *******)*ppppppplVar24;
          ppppppplVar20 = ppppppplVar24;
          ppppppplVar25 = ppppppplVar24;
        }
        else {
          do {
            while (ppppppplVar20 = ppppppplVar21, ppppppplVar20[4] <= pppppplStack_88) {
              if (pppppplStack_88 <= ppppppplVar20[4]) {
                ppppppplVar23 = ppppppplVar20;
                ppppppplVar25 = (long *******)&ppppppplStack_68;
                goto joined_r0x016551c0;
              }
              ppppppplVar25 = ppppppplVar20 + 1;
              ppppppplVar21 = (long *******)*ppppppplVar25;
              if ((long *******)*ppppppplVar25 == (long *******)0x0) {
                ppppppplVar23 = (long *******)*ppppppplVar25;
                goto joined_r0x016551c0;
              }
            }
            ppppppplVar21 = (long *******)*ppppppplVar20;
          } while ((long *******)*ppppppplVar20 != (long *******)0x0);
          ppppppplVar23 = (long *******)*ppppppplVar20;
          ppppppplVar25 = ppppppplVar20;
        }
joined_r0x016551c0:
        puStack_b8 = puVar16;
        ppppppplStack_68 = ppppppplVar20;
        if (ppppppplVar23 == (long *******)0x0) {
          std::__ndk1::unique_ptr<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CAchievementInfo>, void*>, std::__ndk1::__tree_node_destructor<Framework::CSTLAllocator<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CAchievementInfo>, void*>, Framework::CSTLMapAllocatorInf> > > std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CAchievementInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CAchievementInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CAchievementInfo>, Framework::CSTLMapAllocatorInf> >::__construct_node<unsigned long&, CAchievementInfo>(unsigned long&, CAchievementInfo&&)(appppppplStack_80,plVar19,&pppppplStack_88,&puStack_220);
          *appppppplStack_80[0] = (long ******)0x0;
          appppppplStack_80[0][1] = (long ******)0x0;
          appppppplStack_80[0][2] = (long ******)ppppppplVar20;
          *ppppppplVar25 = (long ******)appppppplStack_80[0];
          ppppppplVar21 = appppppplStack_80[0];
          if (*(long *)*plVar19 != 0) {
            *plVar19 = *(long *)*plVar19;
            ppppppplVar21 = (long *******)*ppppppplVar25;
          }
          void std::__ndk1::__tree_balance_after_insert<std::__ndk1::__tree_node_base<void*>*>(std::__ndk1::__tree_node_base<void*>*, std::__ndk1::__tree_node_base<void*>*)(param_1[8],ppppppplVar21);
          param_1[9] = param_1[9] + 1;
          ppppppplVar23 = appppppplStack_80[0];
        }
        CAchievementInfo::~CAchievementInfo()(&puStack_220);
        ppppppplVar23 = ppppppplVar23 + 5;
        (*(code *)(*ppppppplVar23)[2])(ppppppplVar23);
      }
      else {
        do {
          while (ppppppplVar23 = ppppppplVar21, ppppppplVar23[4] < pppppplStack_88) {
            ppppppplVar21 = (long *******)ppppppplVar23[1];
            if ((long *******)ppppppplVar23[1] == (long *******)0x0) {
              ppppppplVar23 = ppppppplVar20;
              if (ppppppplVar20 != ppppppplVar24) goto code_r0x01655044;
              goto code_r0x01655060;
            }
          }
          ppppppplVar21 = (long *******)*ppppppplVar23;
          ppppppplVar20 = ppppppplVar23;
        } while ((long *******)*ppppppplVar23 != (long *******)0x0);
        if (ppppppplVar23 == ppppppplVar24) goto code_r0x01655060;
code_r0x01655044:
        if ((pppppplStack_88 < ppppppplVar23[4]) || (ppppppplVar23 == ppppppplVar24))
        goto code_r0x01655060;
        ppppppplVar23 = ppppppplVar23 + 5;
      }
      lVar17 = *param_2 + uVar22 * 0x40;
      iVar18 = *(int *)(lVar17 + 0x20);
      if (iVar18 == 6) {
        (*(code *)**ppppppplVar23)(ppppppplVar23,lVar17 + 0x28);
      }
      else if (iVar18 == 7) {
        (*(code *)(*ppppppplVar23)[1])(ppppppplVar23,*param_2 + uVar22 * 0x40 + 0x28);
      }
      uVar1 = (int)uVar22 + 1;
      uVar22 = (ulong)uVar1;
    } while (uVar1 < *(uint *)(param_2 + 1));
  }
  return 1;
}

// ==== IInfoBaseMap<unsigned long, CPresentBoxInfo>::DeserializeChild(Aska::ASON::AValue::AMap const*)
// vaddr 0x1555788 | ghidra 0x1655788 | size 436 | symbol _ZN12IInfoBaseMapIm15CPresentBoxInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN12IInfoBaseMapIm15CPresentBoxInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE
          (long *param_1,long *param_2)

{
  uint uVar1;
  int iVar2;
  long *plVar3;
  long lVar4;
  long *plVar5;
  ulong uVar6;
  long *plVar7;
  long *plVar8;
  undefined1 auStack_290 [584];
  ulong uStack_48;
  
  plVar8 = param_1 + 8;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CPresentBoxInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CPresentBoxInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CPresentBoxInfo>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CPresentBoxInfo>, void*>*)(param_1 + 7,*plVar8);
  param_1[7] = (long)plVar8;
  param_1[8] = 0;
  param_1[9] = 0;
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0282d54e/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\Info/InfoBase.h"*/,0x1c1,&UNK_027dc58a/*"apParser is null."*/);
    iVar2 = iRam0000000000000008;
  }
  else {
    iVar2 = (int)param_2[1];
  }
  if (iVar2 != 0) {
    uVar6 = 0;
    do {
      uStack_48 = (**(code **)(*param_1 + 0x20))(param_1,*param_2 + uVar6 * 0x40);
      plVar3 = (long *)param_1[8];
      plVar5 = plVar8;
      if ((long *)param_1[8] == (long *)0x0) {
code_r0x0165587c:
        memset(auStack_290,0,0x248);
        CPresentBoxInfo::CPresentBoxInfo()(auStack_290);
        lVar4 = std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned long, CPresentBoxInfo>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CPresentBoxInfo>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CPresentBoxInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CPresentBoxInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CPresentBoxInfo>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned long, unsigned long&, CPresentBoxInfo>(unsigned long const&, unsigned long&, CPresentBoxInfo&&)(param_1 + 7,&uStack_48,&uStack_48,auStack_290);
        CPresentBoxInfo::~CPresentBoxInfo()(auStack_290);
        plVar7 = (long *)(lVar4 + 0x28);
        (**(code **)(*plVar7 + 0x10))(plVar7);
      }
      else {
        do {
          while (plVar7 = plVar3, (ulong)plVar7[4] < uStack_48) {
            plVar3 = (long *)plVar7[1];
            if ((long *)plVar7[1] == (long *)0x0) {
              plVar7 = plVar5;
              if (plVar5 != plVar8) goto code_r0x01655860;
              goto code_r0x0165587c;
            }
          }
          plVar3 = (long *)*plVar7;
          plVar5 = plVar7;
        } while ((long *)*plVar7 != (long *)0x0);
        if (plVar7 == plVar8) goto code_r0x0165587c;
code_r0x01655860:
        if ((uStack_48 < (ulong)plVar7[4]) || (plVar7 == plVar8)) goto code_r0x0165587c;
        plVar7 = plVar7 + 5;
      }
      lVar4 = *param_2 + uVar6 * 0x40;
      iVar2 = *(int *)(lVar4 + 0x20);
      if (iVar2 == 6) {
        (**(code **)*plVar7)(plVar7,lVar4 + 0x28);
      }
      else if (iVar2 == 7) {
        (**(code **)(*plVar7 + 8))(plVar7,*param_2 + uVar6 * 0x40 + 0x28);
      }
      uVar1 = (int)uVar6 + 1;
      uVar6 = (ulong)uVar1;
    } while (uVar1 < *(uint *)(param_2 + 1));
  }
  return 1;
}

// ==== IInfoBaseMap<unsigned long, TowerScheduleInfo_S2C>::DeserializeChild(Aska::ASON::AValue::AMap const*)
// vaddr 0x1556e28 | ghidra 0x1656e28 | size 1080 | symbol _ZN12IInfoBaseMapIm21TowerScheduleInfo_S2CE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Type propagation algorithm not settling */

undefined8
_ZN12IInfoBaseMapIm21TowerScheduleInfo_S2CE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE
          (long *param_1,long *param_2)

{
  uint uVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined *puVar5;
  undefined *puVar6;
  undefined *puVar7;
  long lVar8;
  int iVar9;
  long *plVar10;
  long *******ppppppplVar11;
  long *******ppppppplVar12;
  ulong uVar13;
  long *******ppppppplVar14;
  long *******ppppppplVar15;
  long *******ppppppplVar16;
  undefined *puStack_140;
  undefined8 *puStack_138;
  undefined8 auStack_130 [2];
  undefined8 *puStack_120;
  undefined8 uStack_118;
  undefined8 uStack_110;
  undefined *puStack_108;
  undefined8 uStack_100;
  undefined1 uStack_f8;
  undefined1 auStack_f0 [16];
  ulong uStack_e0;
  undefined8 uStack_d8;
  undefined8 uStack_d0;
  undefined *puStack_c8;
  undefined8 uStack_c0;
  undefined1 uStack_b8;
  undefined1 auStack_b0 [16];
  ulong uStack_a0;
  undefined8 uStack_98;
  undefined8 uStack_90;
  long ******pppppplStack_88;
  long *******appppppplStack_80 [3];
  long *******ppppppplStack_68;
  
  ppppppplVar16 = (long *******)(param_1 + 8);
  plVar10 = param_1 + 7;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, TowerScheduleInfo_S2C>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, TowerScheduleInfo_S2C>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, TowerScheduleInfo_S2C>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, TowerScheduleInfo_S2C>, void*>*)(plVar10,*ppppppplVar16);
  param_1[7] = (long)ppppppplVar16;
  param_1[8] = 0;
  param_1[9] = 0;
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0282d54e/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\Info/InfoBase.h"*/,0x1c1,&UNK_027dc58a/*"apParser is null."*/);
    iVar9 = iRam0000000000000008;
  }
  else {
    iVar9 = (int)param_2[1];
  }
  if (iVar9 != 0) {
    puVar2 = PTR__ZTV21TowerScheduleInfo_S2C_02cbb8c0 + 0x10;
    puVar3 = PTR__ZTV22CParameterPropertyBaseILj42EE_02cb6c60 + 0x10;
    puVar4 = PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj42EE_02cbb858
             + 0x10;
    puVar5 = PTR__ZTV22CParameterPropertyBaseILj43EE_02cc4ac0 + 0x10;
    puVar6 = PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj43EE_02cbca20
             + 0x10;
    uVar13 = 0;
    puVar7 = PTR__ZTV8InfoBase_02cc49c8 + 0x10;
    do {
      pppppplStack_88 =
           (long ******)(**(code **)(*param_1 + 0x20))(param_1,*param_2 + uVar13 * 0x40);
      ppppppplVar12 = (long *******)param_1[8];
      ppppppplVar11 = ppppppplVar16;
      if ((long *******)param_1[8] == (long *******)0x0) {
code_r0x01656fb8:
        memset(auStack_130,0,0xa8);
        uStack_118 = 0;
        uStack_110 = 0;
        uStack_f8 = 0;
        uStack_100 = 0;
        puStack_140 = puVar2;
        puStack_138 = auStack_130;
        puStack_120 = &uStack_118;
        puStack_108 = puVar3;
        Framework::CHash32::CHash32()(auStack_f0);
        uStack_d8 = 0;
        uStack_d0 = 0;
        uStack_e0 = 0;
        uStack_b8 = 0;
        uStack_c0 = 0;
        puStack_108 = puVar4;
        puStack_c8 = puVar5;
        Framework::CHash32::CHash32()(auStack_b0);
        uStack_98 = 0;
        uStack_90 = 0;
        uStack_a0 = 0;
        ppppppplVar12 = (long *******)*ppppppplVar16;
        if ((long *******)*ppppppplVar16 == (long *******)0x0) {
          ppppppplVar15 = (long *******)*ppppppplVar16;
          ppppppplVar11 = ppppppplVar16;
          ppppppplVar14 = ppppppplVar16;
        }
        else {
          do {
            while (ppppppplVar11 = ppppppplVar12, ppppppplVar11[4] <= pppppplStack_88) {
              if (pppppplStack_88 <= ppppppplVar11[4]) {
                ppppppplVar14 = (long *******)&ppppppplStack_68;
                ppppppplVar15 = ppppppplVar11;
                goto joined_r0x016570d4;
              }
              ppppppplVar14 = ppppppplVar11 + 1;
              ppppppplVar12 = (long *******)*ppppppplVar14;
              if ((long *******)*ppppppplVar14 == (long *******)0x0) {
                ppppppplVar15 = (long *******)*ppppppplVar14;
                goto joined_r0x016570d4;
              }
            }
            ppppppplVar12 = (long *******)*ppppppplVar11;
          } while ((long *******)*ppppppplVar11 != (long *******)0x0);
          ppppppplVar15 = (long *******)*ppppppplVar11;
          ppppppplVar14 = ppppppplVar11;
        }
joined_r0x016570d4:
        ppppppplStack_68 = ppppppplVar11;
        if (ppppppplVar15 == (long *******)0x0) {
          puStack_c8 = puVar6;
          std::__ndk1::unique_ptr<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, TowerScheduleInfo_S2C>, void*>, std::__ndk1::__tree_node_destructor<Framework::CSTLAllocator<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, TowerScheduleInfo_S2C>, void*>, Framework::CSTLMapAllocatorInf> > > std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, TowerScheduleInfo_S2C>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, TowerScheduleInfo_S2C>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, TowerScheduleInfo_S2C>, Framework::CSTLMapAllocatorInf> >::__construct_node<unsigned long&, TowerScheduleInfo_S2C>(unsigned long&, TowerScheduleInfo_S2C&&)(appppppplStack_80,plVar10,&pppppplStack_88,&puStack_140);
          *appppppplStack_80[0] = (long ******)0x0;
          appppppplStack_80[0][1] = (long ******)0x0;
          appppppplStack_80[0][2] = (long ******)ppppppplVar11;
          *ppppppplVar14 = (long ******)appppppplStack_80[0];
          ppppppplVar12 = appppppplStack_80[0];
          if (*(long *)*plVar10 != 0) {
            *plVar10 = *(long *)*plVar10;
            ppppppplVar12 = (long *******)*ppppppplVar14;
          }
          void std::__ndk1::__tree_balance_after_insert<std::__ndk1::__tree_node_base<void*>*>(std::__ndk1::__tree_node_base<void*>*, std::__ndk1::__tree_node_base<void*>*)(param_1[8],ppppppplVar12);
          ppppppplVar15 = appppppplStack_80[0];
          param_1[9] = param_1[9] + 1;
          puStack_140 = PTR__ZTV21TowerScheduleInfo_S2C_02cbb8c0 + 0x10;
          puStack_c8 = PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj43EE_02cbca20
                       + 0x10;
          if ((uStack_a0 & 1) != 0) {
            Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_90);
          }
        }
        else {
          puStack_140 = PTR__ZTV21TowerScheduleInfo_S2C_02cbb8c0 + 0x10;
        }
        puStack_c8 = PTR__ZTV22CParameterPropertyBaseILj43EE_02cc4ac0 + 0x10;
        Framework::CHash32::~CHash32()(auStack_b0);
        puStack_108 = PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj42EE_02cbb858
                      + 0x10;
        if ((uStack_e0 & 1) != 0) {
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_d0);
        }
        puStack_108 = PTR__ZTV22CParameterPropertyBaseILj42EE_02cb6c60 + 0x10;
        Framework::CHash32::~CHash32()(auStack_f0);
        puStack_140 = puVar7;
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*)(&puStack_120,uStack_118);
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*)(&puStack_138,auStack_130[0]);
        ppppppplVar15 = ppppppplVar15 + 5;
        (*(code *)(*ppppppplVar15)[2])(ppppppplVar15);
      }
      else {
        do {
          while (ppppppplVar15 = ppppppplVar12, ppppppplVar15[4] < pppppplStack_88) {
            ppppppplVar12 = (long *******)ppppppplVar15[1];
            if ((long *******)ppppppplVar15[1] == (long *******)0x0) {
              ppppppplVar15 = ppppppplVar11;
              if (ppppppplVar11 != ppppppplVar16) goto code_r0x01656f9c;
              goto code_r0x01656fb8;
            }
          }
          ppppppplVar12 = (long *******)*ppppppplVar15;
          ppppppplVar11 = ppppppplVar15;
        } while ((long *******)*ppppppplVar15 != (long *******)0x0);
        if (ppppppplVar15 == ppppppplVar16) goto code_r0x01656fb8;
code_r0x01656f9c:
        if ((pppppplStack_88 < ppppppplVar15[4]) || (ppppppplVar15 == ppppppplVar16))
        goto code_r0x01656fb8;
        ppppppplVar15 = ppppppplVar15 + 5;
      }
      lVar8 = *param_2 + uVar13 * 0x40;
      iVar9 = *(int *)(lVar8 + 0x20);
      if (iVar9 == 6) {
        (*(code *)**ppppppplVar15)(ppppppplVar15,lVar8 + 0x28);
      }
      else if (iVar9 == 7) {
        (*(code *)(*ppppppplVar15)[1])(ppppppplVar15,*param_2 + uVar13 * 0x40 + 0x28);
      }
      uVar1 = (int)uVar13 + 1;
      uVar13 = (ulong)uVar1;
    } while (uVar1 < *(uint *)(param_2 + 1));
  }
  return 1;
}

// ==== IInfoBaseMap<unsigned long, CCoinInfo>::DeserializeChild(Aska::ASON::AValue::AMap const*)
// vaddr 0x1557cf0 | ghidra 0x1657cf0 | size 436 | symbol _ZN12IInfoBaseMapIm9CCoinInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN12IInfoBaseMapIm9CCoinInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE
          (long *param_1,long *param_2)

{
  uint uVar1;
  int iVar2;
  long *plVar3;
  long lVar4;
  long *plVar5;
  ulong uVar6;
  long *plVar7;
  long *plVar8;
  undefined1 auStack_590 [1352];
  ulong uStack_48;
  
  plVar8 = param_1 + 8;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CCoinInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CCoinInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CCoinInfo>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CCoinInfo>, void*>*)(param_1 + 7,*plVar8);
  param_1[7] = (long)plVar8;
  param_1[8] = 0;
  param_1[9] = 0;
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0282d54e/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\Info/InfoBase.h"*/,0x1c1,&UNK_027dc58a/*"apParser is null."*/);
    iVar2 = iRam0000000000000008;
  }
  else {
    iVar2 = (int)param_2[1];
  }
  if (iVar2 != 0) {
    uVar6 = 0;
    do {
      uStack_48 = (**(code **)(*param_1 + 0x20))(param_1,*param_2 + uVar6 * 0x40);
      plVar3 = (long *)param_1[8];
      plVar5 = plVar8;
      if ((long *)param_1[8] == (long *)0x0) {
code_r0x01657de4:
        memset(auStack_590,0,0x548);
        CCoinInfo::CCoinInfo()(auStack_590);
        lVar4 = std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned long, CCoinInfo>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CCoinInfo>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CCoinInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CCoinInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CCoinInfo>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned long, unsigned long&, CCoinInfo>(unsigned long const&, unsigned long&, CCoinInfo&&)(param_1 + 7,&uStack_48,&uStack_48,auStack_590);
        CCoinInfo::~CCoinInfo()(auStack_590);
        plVar7 = (long *)(lVar4 + 0x28);
        (**(code **)(*plVar7 + 0x10))(plVar7);
      }
      else {
        do {
          while (plVar7 = plVar3, (ulong)plVar7[4] < uStack_48) {
            plVar3 = (long *)plVar7[1];
            if ((long *)plVar7[1] == (long *)0x0) {
              plVar7 = plVar5;
              if (plVar5 != plVar8) goto code_r0x01657dc8;
              goto code_r0x01657de4;
            }
          }
          plVar3 = (long *)*plVar7;
          plVar5 = plVar7;
        } while ((long *)*plVar7 != (long *)0x0);
        if (plVar7 == plVar8) goto code_r0x01657de4;
code_r0x01657dc8:
        if ((uStack_48 < (ulong)plVar7[4]) || (plVar7 == plVar8)) goto code_r0x01657de4;
        plVar7 = plVar7 + 5;
      }
      lVar4 = *param_2 + uVar6 * 0x40;
      iVar2 = *(int *)(lVar4 + 0x20);
      if (iVar2 == 6) {
        (**(code **)*plVar7)(plVar7,lVar4 + 0x28);
      }
      else if (iVar2 == 7) {
        (**(code **)(*plVar7 + 8))(plVar7,*param_2 + uVar6 * 0x40 + 0x28);
      }
      uVar1 = (int)uVar6 + 1;
      uVar6 = (ulong)uVar1;
    } while (uVar1 < *(uint *)(param_2 + 1));
  }
  return 1;
}

// ==== IInfoBaseMap<unsigned long, CGachaCountInfo>::DeserializeChild(Aska::ASON::AValue::AMap const*)
// vaddr 0x155a7b0 | ghidra 0x165a7b0 | size 1028 | symbol _ZN12IInfoBaseMapIm15CGachaCountInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Type propagation algorithm not settling */

undefined8
_ZN12IInfoBaseMapIm15CGachaCountInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE
          (long *param_1,long *param_2)

{
  uint uVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined *puVar5;
  undefined *puVar6;
  undefined *puVar7;
  undefined *puVar8;
  undefined *puVar9;
  undefined *puVar10;
  undefined *puVar11;
  undefined *puVar12;
  long lVar13;
  int iVar14;
  long *plVar15;
  long *******ppppppplVar16;
  long *******ppppppplVar17;
  ulong uVar18;
  long *******ppppppplVar19;
  long *******ppppppplVar20;
  long *******ppppppplVar21;
  undefined *puStack_1c0;
  undefined1 *puStack_1b8;
  undefined1 auStack_1b0 [16];
  undefined8 *puStack_1a0;
  undefined8 uStack_198;
  undefined8 uStack_190;
  undefined *puStack_188;
  undefined8 uStack_180;
  undefined1 uStack_178;
  undefined1 auStack_170 [24];
  undefined *puStack_158;
  undefined8 uStack_150;
  undefined1 uStack_148;
  undefined1 auStack_140 [24];
  undefined *puStack_128;
  undefined8 uStack_120;
  undefined1 uStack_118;
  undefined1 auStack_110 [24];
  undefined *puStack_f8;
  undefined8 uStack_f0;
  undefined1 uStack_e8;
  undefined1 auStack_e0 [16];
  undefined8 uStack_d0;
  undefined8 uStack_c8;
  undefined8 uStack_c0;
  undefined *puStack_b8;
  undefined8 uStack_b0;
  undefined1 uStack_a8;
  undefined1 auStack_a0 [24];
  long ******pppppplStack_88;
  long *******appppppplStack_80 [3];
  long *******ppppppplStack_68;
  
  ppppppplVar21 = (long *******)(param_1 + 8);
  plVar15 = param_1 + 7;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CGachaCountInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CGachaCountInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CGachaCountInfo>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CGachaCountInfo>, void*>*)(plVar15,*ppppppplVar21);
  param_1[7] = (long)ppppppplVar21;
  param_1[8] = 0;
  param_1[9] = 0;
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0282d54e/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\Info/InfoBase.h"*/,0x1c1,&UNK_027dc58a/*"apParser is null."*/);
    iVar14 = iRam0000000000000008;
  }
  else {
    iVar14 = (int)param_2[1];
  }
  if (iVar14 != 0) {
    puVar2 = PTR__ZTV15CGachaCountInfo_02cb76e8 + 0x10;
    puVar3 = PTR__ZTV22CParameterPropertyBaseILj16EE_02cb9c20 + 0x10;
    puVar4 = PTR__ZTV23CParameterPropertyValueIjLj16E18CPropertyConverterE_02cbd008 + 0x10;
    puVar5 = PTR__ZTV22CParameterPropertyBaseILj17EE_02cba1e8 + 0x10;
    puVar6 = PTR__ZTV23CParameterPropertyValueIjLj17E18CPropertyConverterE_02cbb3b8 + 0x10;
    puVar7 = PTR__ZTV22CParameterPropertyBaseILj18EE_02cbe238 + 0x10;
    puVar8 = PTR__ZTV23CParameterPropertyValueIjLj18E18CPropertyConverterE_02cbcd58 + 0x10;
    puVar9 = PTR__ZTV22CParameterPropertyBaseILj19EE_02cc4c98 + 0x10;
    puVar10 = PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj19EE_02cbf9d0
              + 0x10;
    uVar18 = 0;
    puVar11 = PTR__ZTV22CParameterPropertyBaseILj20EE_02cc0d08 + 0x10;
    puVar12 = PTR__ZTV23CParameterPropertyValueIbLj20E18CPropertyConverterE_02cb77b8 + 0x10;
    do {
      pppppplStack_88 =
           (long ******)(**(code **)(*param_1 + 0x20))(param_1,*param_2 + uVar18 * 0x40);
      ppppppplVar17 = (long *******)param_1[8];
      ppppppplVar16 = ppppppplVar21;
      if ((long *******)param_1[8] == (long *******)0x0) {
code_r0x0165a98c:
        memset(auStack_1b0,0,0x128);
        uStack_198 = 0;
        uStack_190 = 0;
        uStack_178 = 0;
        uStack_180 = 0;
        puStack_1c0 = puVar2;
        puStack_1b8 = auStack_1b0;
        puStack_1a0 = &uStack_198;
        puStack_188 = puVar3;
        Framework::CHash32::CHash32()(auStack_170);
        uStack_148 = 0;
        uStack_150 = 0;
        puStack_188 = puVar4;
        puStack_158 = puVar5;
        Framework::CHash32::CHash32()(auStack_140);
        uStack_118 = 0;
        uStack_120 = 0;
        puStack_158 = puVar6;
        puStack_128 = puVar7;
        Framework::CHash32::CHash32()(auStack_110);
        uStack_e8 = 0;
        uStack_f0 = 0;
        puStack_128 = puVar8;
        puStack_f8 = puVar9;
        Framework::CHash32::CHash32()(auStack_e0);
        uStack_c8 = 0;
        uStack_c0 = 0;
        uStack_d0 = 0;
        uStack_a8 = 0;
        uStack_b0 = 0;
        puStack_f8 = puVar10;
        puStack_b8 = puVar11;
        Framework::CHash32::CHash32()(auStack_a0);
        ppppppplVar17 = (long *******)*ppppppplVar21;
        if ((long *******)*ppppppplVar21 == (long *******)0x0) {
          ppppppplVar20 = (long *******)*ppppppplVar21;
          ppppppplVar16 = ppppppplVar21;
          ppppppplVar19 = ppppppplVar21;
        }
        else {
          do {
            while (ppppppplVar16 = ppppppplVar17, ppppppplVar16[4] <= pppppplStack_88) {
              if (pppppplStack_88 <= ppppppplVar16[4]) {
                ppppppplVar20 = ppppppplVar16;
                ppppppplVar19 = (long *******)&ppppppplStack_68;
                goto joined_r0x0165aab0;
              }
              ppppppplVar19 = ppppppplVar16 + 1;
              ppppppplVar17 = (long *******)*ppppppplVar19;
              if ((long *******)*ppppppplVar19 == (long *******)0x0) {
                ppppppplVar20 = (long *******)*ppppppplVar19;
                goto joined_r0x0165aab0;
              }
            }
            ppppppplVar17 = (long *******)*ppppppplVar16;
          } while ((long *******)*ppppppplVar16 != (long *******)0x0);
          ppppppplVar20 = (long *******)*ppppppplVar16;
          ppppppplVar19 = ppppppplVar16;
        }
joined_r0x0165aab0:
        puStack_b8 = puVar12;
        ppppppplStack_68 = ppppppplVar16;
        if (ppppppplVar20 == (long *******)0x0) {
          std::__ndk1::unique_ptr<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CGachaCountInfo>, void*>, std::__ndk1::__tree_node_destructor<Framework::CSTLAllocator<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CGachaCountInfo>, void*>, Framework::CSTLMapAllocatorInf> > > std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CGachaCountInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CGachaCountInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CGachaCountInfo>, Framework::CSTLMapAllocatorInf> >::__construct_node<unsigned long&, CGachaCountInfo>(unsigned long&, CGachaCountInfo&&)(appppppplStack_80,plVar15,&pppppplStack_88,&puStack_1c0);
          *appppppplStack_80[0] = (long ******)0x0;
          appppppplStack_80[0][1] = (long ******)0x0;
          appppppplStack_80[0][2] = (long ******)ppppppplVar16;
          *ppppppplVar19 = (long ******)appppppplStack_80[0];
          ppppppplVar17 = appppppplStack_80[0];
          if (*(long *)*plVar15 != 0) {
            *plVar15 = *(long *)*plVar15;
            ppppppplVar17 = (long *******)*ppppppplVar19;
          }
          void std::__ndk1::__tree_balance_after_insert<std::__ndk1::__tree_node_base<void*>*>(std::__ndk1::__tree_node_base<void*>*, std::__ndk1::__tree_node_base<void*>*)(param_1[8],ppppppplVar17);
          param_1[9] = param_1[9] + 1;
          ppppppplVar20 = appppppplStack_80[0];
        }
        CGachaCountInfo::~CGachaCountInfo()(&puStack_1c0);
        ppppppplVar20 = ppppppplVar20 + 5;
        (*(code *)(*ppppppplVar20)[2])(ppppppplVar20);
      }
      else {
        do {
          while (ppppppplVar20 = ppppppplVar17, ppppppplVar20[4] < pppppplStack_88) {
            ppppppplVar17 = (long *******)ppppppplVar20[1];
            if ((long *******)ppppppplVar20[1] == (long *******)0x0) {
              ppppppplVar20 = ppppppplVar16;
              if (ppppppplVar16 != ppppppplVar21) goto code_r0x0165a970;
              goto code_r0x0165a98c;
            }
          }
          ppppppplVar17 = (long *******)*ppppppplVar20;
          ppppppplVar16 = ppppppplVar20;
        } while ((long *******)*ppppppplVar20 != (long *******)0x0);
        if (ppppppplVar20 == ppppppplVar21) goto code_r0x0165a98c;
code_r0x0165a970:
        if ((pppppplStack_88 < ppppppplVar20[4]) || (ppppppplVar20 == ppppppplVar21))
        goto code_r0x0165a98c;
        ppppppplVar20 = ppppppplVar20 + 5;
      }
      lVar13 = *param_2 + uVar18 * 0x40;
      iVar14 = *(int *)(lVar13 + 0x20);
      if (iVar14 == 6) {
        (*(code *)**ppppppplVar20)(ppppppplVar20,lVar13 + 0x28);
      }
      else if (iVar14 == 7) {
        (*(code *)(*ppppppplVar20)[1])(ppppppplVar20,*param_2 + uVar18 * 0x40 + 0x28);
      }
      uVar1 = (int)uVar18 + 1;
      uVar18 = (ulong)uVar1;
    } while (uVar1 < *(uint *)(param_2 + 1));
  }
  return 1;
}

// ==== IInfoBaseMap<unsigned long, CSaleGachaCountInfo>::DeserializeChild(Aska::ASON::AValue::AMap const*)
// vaddr 0x155c088 | ghidra 0x165c088 | size 1028 | symbol _ZN12IInfoBaseMapIm19CSaleGachaCountInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Type propagation algorithm not settling */

undefined8
_ZN12IInfoBaseMapIm19CSaleGachaCountInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE
          (long *param_1,long *param_2)

{
  uint uVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined *puVar5;
  undefined *puVar6;
  undefined *puVar7;
  undefined *puVar8;
  undefined *puVar9;
  long lVar10;
  int iVar11;
  long *plVar12;
  long *******ppppppplVar13;
  long *******ppppppplVar14;
  ulong uVar15;
  long *******ppppppplVar16;
  long *******ppppppplVar17;
  long *******ppppppplVar18;
  undefined *puStack_150;
  undefined8 *puStack_148;
  undefined8 auStack_140 [2];
  undefined8 *puStack_130;
  undefined8 uStack_128;
  undefined8 uStack_120;
  undefined *puStack_118;
  undefined8 uStack_110;
  undefined1 uStack_108;
  undefined1 auStack_100 [24];
  undefined *puStack_e8;
  undefined8 uStack_e0;
  undefined1 uStack_d8;
  undefined1 auStack_d0 [24];
  undefined *puStack_b8;
  undefined8 uStack_b0;
  undefined1 uStack_a8;
  undefined1 auStack_a0 [24];
  long ******pppppplStack_88;
  long *******appppppplStack_80 [3];
  long *******ppppppplStack_68;
  
  ppppppplVar18 = (long *******)(param_1 + 8);
  plVar12 = param_1 + 7;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CSaleGachaCountInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CSaleGachaCountInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CSaleGachaCountInfo>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CSaleGachaCountInfo>, void*>*)(plVar12,*ppppppplVar18);
  param_1[7] = (long)ppppppplVar18;
  param_1[8] = 0;
  param_1[9] = 0;
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0282d54e/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\Info/InfoBase.h"*/,0x1c1,&UNK_027dc58a/*"apParser is null."*/);
    iVar11 = iRam0000000000000008;
  }
  else {
    iVar11 = (int)param_2[1];
  }
  if (iVar11 != 0) {
    puVar2 = PTR__ZTV19CSaleGachaCountInfo_02cc0ed8 + 0x10;
    puVar3 = PTR__ZTV22CParameterPropertyBaseILj16EE_02cb9c20 + 0x10;
    puVar4 = PTR__ZTV23CParameterPropertyValueIjLj16E18CPropertyConverterE_02cbd008 + 0x10;
    puVar5 = PTR__ZTV22CParameterPropertyBaseILj17EE_02cba1e8 + 0x10;
    puVar6 = PTR__ZTV23CParameterPropertyValueIjLj17E18CPropertyConverterE_02cbb3b8 + 0x10;
    puVar7 = PTR__ZTV22CParameterPropertyBaseILj18EE_02cbe238 + 0x10;
    puVar8 = PTR__ZTV23CParameterPropertyValueIjLj18E18CPropertyConverterE_02cbcd58 + 0x10;
    uVar15 = 0;
    puVar9 = PTR__ZTV8InfoBase_02cc49c8 + 0x10;
    do {
      pppppplStack_88 =
           (long ******)(**(code **)(*param_1 + 0x20))(param_1,*param_2 + uVar15 * 0x40);
      ppppppplVar14 = (long *******)param_1[8];
      ppppppplVar13 = ppppppplVar18;
      if ((long *******)param_1[8] == (long *******)0x0) {
code_r0x0165c22c:
        memset(auStack_140,0,0xb8);
        uStack_128 = 0;
        uStack_120 = 0;
        uStack_108 = 0;
        uStack_110 = 0;
        puStack_150 = puVar2;
        puStack_148 = auStack_140;
        puStack_130 = &uStack_128;
        puStack_118 = puVar3;
        Framework::CHash32::CHash32()(auStack_100);
        uStack_d8 = 0;
        uStack_e0 = 0;
        puStack_118 = puVar4;
        puStack_e8 = puVar5;
        Framework::CHash32::CHash32()(auStack_d0);
        uStack_a8 = 0;
        uStack_b0 = 0;
        puStack_e8 = puVar6;
        puStack_b8 = puVar7;
        Framework::CHash32::CHash32()(auStack_a0);
        ppppppplVar14 = (long *******)*ppppppplVar18;
        if ((long *******)*ppppppplVar18 == (long *******)0x0) {
          ppppppplVar17 = (long *******)*ppppppplVar18;
          ppppppplVar13 = ppppppplVar18;
          ppppppplVar16 = ppppppplVar18;
        }
        else {
          do {
            while (ppppppplVar13 = ppppppplVar14, ppppppplVar13[4] <= pppppplStack_88) {
              if (pppppplStack_88 <= ppppppplVar13[4]) {
                ppppppplVar17 = ppppppplVar13;
                ppppppplVar16 = (long *******)&ppppppplStack_68;
                goto joined_r0x0165c318;
              }
              ppppppplVar16 = ppppppplVar13 + 1;
              ppppppplVar14 = (long *******)*ppppppplVar16;
              if ((long *******)*ppppppplVar16 == (long *******)0x0) {
                ppppppplVar17 = (long *******)*ppppppplVar16;
                goto joined_r0x0165c318;
              }
            }
            ppppppplVar14 = (long *******)*ppppppplVar13;
          } while ((long *******)*ppppppplVar13 != (long *******)0x0);
          ppppppplVar17 = (long *******)*ppppppplVar13;
          ppppppplVar16 = ppppppplVar13;
        }
joined_r0x0165c318:
        ppppppplStack_68 = ppppppplVar13;
        if (ppppppplVar17 == (long *******)0x0) {
          puStack_b8 = puVar8;
          std::__ndk1::unique_ptr<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CSaleGachaCountInfo>, void*>, std::__ndk1::__tree_node_destructor<Framework::CSTLAllocator<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CSaleGachaCountInfo>, void*>, Framework::CSTLMapAllocatorInf> > > std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CSaleGachaCountInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CSaleGachaCountInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CSaleGachaCountInfo>, Framework::CSTLMapAllocatorInf> >::__construct_node<unsigned long&, CSaleGachaCountInfo>(unsigned long&, CSaleGachaCountInfo&&)(appppppplStack_80,plVar12,&pppppplStack_88,&puStack_150);
          *appppppplStack_80[0] = (long ******)0x0;
          appppppplStack_80[0][1] = (long ******)0x0;
          appppppplStack_80[0][2] = (long ******)ppppppplVar13;
          *ppppppplVar16 = (long ******)appppppplStack_80[0];
          ppppppplVar14 = appppppplStack_80[0];
          if (*(long *)*plVar12 != 0) {
            *plVar12 = *(long *)*plVar12;
            ppppppplVar14 = (long *******)*ppppppplVar16;
          }
          void std::__ndk1::__tree_balance_after_insert<std::__ndk1::__tree_node_base<void*>*>(std::__ndk1::__tree_node_base<void*>*, std::__ndk1::__tree_node_base<void*>*)(param_1[8],ppppppplVar14);
          param_1[9] = param_1[9] + 1;
          ppppppplVar17 = appppppplStack_80[0];
        }
        puStack_150 = PTR__ZTV19CSaleGachaCountInfo_02cc0ed8 + 0x10;
        puStack_b8 = PTR__ZTV22CParameterPropertyBaseILj18EE_02cbe238 + 0x10;
        Framework::CHash32::~CHash32()(auStack_a0);
        puStack_e8 = PTR__ZTV22CParameterPropertyBaseILj17EE_02cba1e8 + 0x10;
        Framework::CHash32::~CHash32()(auStack_d0);
        puStack_118 = PTR__ZTV22CParameterPropertyBaseILj16EE_02cb9c20 + 0x10;
        Framework::CHash32::~CHash32()(auStack_100);
        puStack_150 = puVar9;
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*)(&puStack_130,uStack_128);
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*)(&puStack_148,auStack_140[0]);
        ppppppplVar17 = ppppppplVar17 + 5;
        (*(code *)(*ppppppplVar17)[2])(ppppppplVar17);
      }
      else {
        do {
          while (ppppppplVar17 = ppppppplVar14, ppppppplVar17[4] < pppppplStack_88) {
            ppppppplVar14 = (long *******)ppppppplVar17[1];
            if ((long *******)ppppppplVar17[1] == (long *******)0x0) {
              ppppppplVar17 = ppppppplVar13;
              if (ppppppplVar13 != ppppppplVar18) goto code_r0x0165c210;
              goto code_r0x0165c22c;
            }
          }
          ppppppplVar14 = (long *******)*ppppppplVar17;
          ppppppplVar13 = ppppppplVar17;
        } while ((long *******)*ppppppplVar17 != (long *******)0x0);
        if (ppppppplVar17 == ppppppplVar18) goto code_r0x0165c22c;
code_r0x0165c210:
        if ((pppppplStack_88 < ppppppplVar17[4]) || (ppppppplVar17 == ppppppplVar18))
        goto code_r0x0165c22c;
        ppppppplVar17 = ppppppplVar17 + 5;
      }
      lVar10 = *param_2 + uVar15 * 0x40;
      iVar11 = *(int *)(lVar10 + 0x20);
      if (iVar11 == 6) {
        (*(code *)**ppppppplVar17)(ppppppplVar17,lVar10 + 0x28);
      }
      else if (iVar11 == 7) {
        (*(code *)(*ppppppplVar17)[1])(ppppppplVar17,*param_2 + uVar15 * 0x40 + 0x28);
      }
      uVar1 = (int)uVar15 + 1;
      uVar15 = (ulong)uVar1;
    } while (uVar1 < *(uint *)(param_2 + 1));
  }
  return 1;
}

// ==== IInfoBaseMap<unsigned long, CBoxGachaInfo>::DeserializeChild(Aska::ASON::AValue::AMap const*)
// vaddr 0x155e3bc | ghidra 0x165e3bc | size 884 | symbol _ZN12IInfoBaseMapIm13CBoxGachaInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN12IInfoBaseMapIm13CBoxGachaInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE
          (long *param_1,long *param_2)

{
  uint uVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined *puVar5;
  undefined *puVar6;
  undefined *puVar7;
  undefined *puVar8;
  undefined *puVar9;
  undefined *puVar10;
  undefined *puVar11;
  undefined *puVar12;
  undefined *puVar13;
  int iVar14;
  long *plVar15;
  long lVar16;
  long *plVar17;
  ulong uVar18;
  long *plVar19;
  long *plVar20;
  undefined *puStack_280;
  undefined1 auStack_278 [8];
  undefined8 uStack_270;
  undefined1 auStack_260 [8];
  undefined8 uStack_258;
  undefined *puStack_248;
  undefined1 auStack_230 [24];
  undefined *puStack_218;
  undefined1 auStack_200 [24];
  undefined *puStack_1e8;
  undefined1 auStack_1d0 [24];
  undefined *puStack_1b8;
  undefined1 auStack_1a0 [24];
  undefined *puStack_188;
  undefined1 auStack_170 [24];
  undefined *puStack_158;
  undefined1 auStack_140 [24];
  undefined *puStack_128;
  undefined1 auStack_110 [24];
  undefined *puStack_f8;
  undefined1 auStack_e0 [24];
  undefined *puStack_c8;
  undefined1 auStack_b0 [24];
  undefined *puStack_98;
  undefined1 auStack_80 [24];
  ulong uStack_68;
  
  plVar20 = param_1 + 8;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CBoxGachaInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CBoxGachaInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CBoxGachaInfo>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CBoxGachaInfo>, void*>*)(param_1 + 7,*plVar20);
  param_1[7] = (long)plVar20;
  param_1[8] = 0;
  param_1[9] = 0;
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0282d54e/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\Info/InfoBase.h"*/,0x1c1,&UNK_027dc58a/*"apParser is null."*/);
    iVar14 = iRam0000000000000008;
  }
  else {
    iVar14 = (int)param_2[1];
  }
  if (iVar14 != 0) {
    puVar2 = PTR__ZTV13CBoxGachaInfo_02cbb500 + 0x10;
    puVar3 = PTR__ZTV22CParameterPropertyBaseILj40EE_02cbd2c0 + 0x10;
    puVar4 = PTR__ZTV22CParameterPropertyBaseILj38EE_02cc0aa0 + 0x10;
    puVar5 = PTR__ZTV22CParameterPropertyBaseILj37EE_02cbda08 + 0x10;
    puVar6 = PTR__ZTV22CParameterPropertyBaseILj36EE_02cb6f78 + 0x10;
    uVar18 = 0;
    puVar7 = PTR__ZTV22CParameterPropertyBaseILj35EE_02cc13f0 + 0x10;
    puVar8 = PTR__ZTV22CParameterPropertyBaseILj33EE_02cb96b8 + 0x10;
    puVar9 = PTR__ZTV22CParameterPropertyBaseILj32EE_02cc0fa8 + 0x10;
    puVar10 = PTR__ZTV22CParameterPropertyBaseILj31EE_02cc17e0 + 0x10;
    puVar11 = PTR__ZTV22CParameterPropertyBaseILj30EE_02cbe830 + 0x10;
    puVar12 = PTR__ZTV22CParameterPropertyBaseILj29EE_02cc1a28 + 0x10;
    puVar13 = PTR__ZTV8InfoBase_02cc49c8 + 0x10;
    do {
      uStack_68 = (**(code **)(*param_1 + 0x20))(param_1,*param_2 + uVar18 * 0x40);
      plVar15 = (long *)param_1[8];
      plVar17 = plVar20;
      if ((long *)param_1[8] == (long *)0x0) {
code_r0x0165e5c0:
        memset(&puStack_280,0,0x218);
        CBoxGachaInfo::CBoxGachaInfo()(&puStack_280);
        lVar16 = std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned long, CBoxGachaInfo>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CBoxGachaInfo>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CBoxGachaInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CBoxGachaInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CBoxGachaInfo>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned long, unsigned long&, CBoxGachaInfo>(unsigned long const&, unsigned long&, CBoxGachaInfo&&)(param_1 + 7,&uStack_68,&uStack_68,&puStack_280);
        puStack_280 = puVar2;
        puStack_98 = puVar3;
        Framework::CHash32::~CHash32()(auStack_80);
        puStack_c8 = puVar4;
        Framework::CHash32::~CHash32()(auStack_b0);
        puStack_f8 = puVar5;
        Framework::CHash32::~CHash32()(auStack_e0);
        puStack_128 = puVar6;
        Framework::CHash32::~CHash32()(auStack_110);
        puStack_158 = puVar7;
        Framework::CHash32::~CHash32()(auStack_140);
        puStack_188 = puVar8;
        Framework::CHash32::~CHash32()(auStack_170);
        puStack_1b8 = puVar9;
        Framework::CHash32::~CHash32()(auStack_1a0);
        puStack_1e8 = puVar10;
        Framework::CHash32::~CHash32()(auStack_1d0);
        puStack_218 = puVar11;
        Framework::CHash32::~CHash32()(auStack_200);
        puStack_248 = puVar12;
        Framework::CHash32::~CHash32()(auStack_230);
        puStack_280 = puVar13;
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*)(auStack_260,uStack_258);
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*)(auStack_278,uStack_270);
        plVar19 = (long *)(lVar16 + 0x28);
        (**(code **)(*plVar19 + 0x10))(plVar19);
      }
      else {
        do {
          while (plVar19 = plVar15, (ulong)plVar19[4] < uStack_68) {
            plVar15 = (long *)plVar19[1];
            if ((long *)plVar19[1] == (long *)0x0) {
              plVar19 = plVar17;
              if (plVar17 != plVar20) goto code_r0x0165e5a4;
              goto code_r0x0165e5c0;
            }
          }
          plVar15 = (long *)*plVar19;
          plVar17 = plVar19;
        } while ((long *)*plVar19 != (long *)0x0);
        if (plVar19 == plVar20) goto code_r0x0165e5c0;
code_r0x0165e5a4:
        if ((uStack_68 < (ulong)plVar19[4]) || (plVar19 == plVar20)) goto code_r0x0165e5c0;
        plVar19 = plVar19 + 5;
      }
      lVar16 = *param_2 + uVar18 * 0x40;
      iVar14 = *(int *)(lVar16 + 0x20);
      if (iVar14 == 6) {
        (**(code **)*plVar19)(plVar19,lVar16 + 0x28);
      }
      else if (iVar14 == 7) {
        (**(code **)(*plVar19 + 8))(plVar19,*param_2 + uVar18 * 0x40 + 0x28);
      }
      uVar1 = (int)uVar18 + 1;
      uVar18 = (ulong)uVar1;
    } while (uVar1 < *(uint *)(param_2 + 1));
  }
  return 1;
}

// ==== IInfoBaseMap<unsigned long, CStepUpGachaInfo>::DeserializeChild(Aska::ASON::AValue::AMap const*)
// vaddr 0x1560170 | ghidra 0x1660170 | size 1324 | symbol _ZN12IInfoBaseMapIm16CStepUpGachaInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Type propagation algorithm not settling */

undefined8
_ZN12IInfoBaseMapIm16CStepUpGachaInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE
          (long *param_1,long *param_2)

{
  uint uVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined *puVar5;
  undefined *puVar6;
  undefined *puVar7;
  undefined *puVar8;
  undefined *puVar9;
  undefined *puVar10;
  undefined *puVar11;
  undefined *puVar12;
  undefined *puVar13;
  undefined *puVar14;
  undefined *puVar15;
  long lVar16;
  int iVar17;
  long *plVar18;
  long *******ppppppplVar19;
  long *******ppppppplVar20;
  ulong uVar21;
  long *******ppppppplVar22;
  long *******ppppppplVar23;
  long *******ppppppplVar24;
  undefined *puStack_1e0;
  undefined8 *puStack_1d8;
  undefined8 auStack_1d0 [2];
  undefined8 *puStack_1c0;
  undefined8 uStack_1b8;
  undefined8 uStack_1b0;
  undefined *puStack_1a8;
  undefined8 uStack_1a0;
  undefined1 uStack_198;
  undefined1 auStack_190 [24];
  undefined *puStack_178;
  undefined8 uStack_170;
  undefined1 uStack_168;
  undefined1 auStack_160 [24];
  undefined *puStack_148;
  undefined8 uStack_140;
  undefined1 uStack_138;
  undefined1 auStack_130 [24];
  undefined *puStack_118;
  undefined8 uStack_110;
  undefined1 uStack_108;
  undefined1 auStack_100 [24];
  undefined *puStack_e8;
  undefined8 uStack_e0;
  undefined1 uStack_d8;
  undefined1 auStack_d0 [24];
  undefined *puStack_b8;
  undefined8 uStack_b0;
  undefined1 uStack_a8;
  undefined1 auStack_a0 [24];
  long ******pppppplStack_88;
  long *******appppppplStack_80 [3];
  long *******ppppppplStack_68;
  
  ppppppplVar23 = (long *******)(param_1 + 8);
  plVar18 = param_1 + 7;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CStepUpGachaInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CStepUpGachaInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CStepUpGachaInfo>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CStepUpGachaInfo>, void*>*)(plVar18,*ppppppplVar23);
  param_1[7] = (long)ppppppplVar23;
  param_1[8] = 0;
  param_1[9] = 0;
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0282d54e/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\Info/InfoBase.h"*/,0x1c1,&UNK_027dc58a/*"apParser is null."*/);
    iVar17 = iRam0000000000000008;
  }
  else {
    iVar17 = (int)param_2[1];
  }
  if (iVar17 != 0) {
    puVar2 = PTR__ZTV16CStepUpGachaInfo_02cb8d98 + 0x10;
    puVar3 = PTR__ZTV22CParameterPropertyBaseILj36EE_02cb6f78 + 0x10;
    puVar4 = PTR__ZTV23CParameterPropertyValueIjLj36E18CPropertyConverterE_02cc2bf8 + 0x10;
    puVar5 = PTR__ZTV22CParameterPropertyBaseILj37EE_02cbda08 + 0x10;
    puVar6 = PTR__ZTV23CParameterPropertyValueIjLj37E18CPropertyConverterE_02cba818 + 0x10;
    puVar7 = PTR__ZTV22CParameterPropertyBaseILj38EE_02cc0aa0 + 0x10;
    puVar8 = PTR__ZTV23CParameterPropertyValueIjLj38E18CPropertyConverterE_02cc3fa0 + 0x10;
    puVar9 = PTR__ZTV22CParameterPropertyBaseILj39EE_02cc3d00 + 0x10;
    puVar10 = PTR__ZTV23CParameterPropertyValueIjLj39E18CPropertyConverterE_02cc2560 + 0x10;
    puVar11 = PTR__ZTV22CParameterPropertyBaseILj40EE_02cbd2c0 + 0x10;
    puVar12 = PTR__ZTV23CParameterPropertyValueIjLj40E18CPropertyConverterE_02cb8038 + 0x10;
    puVar13 = PTR__ZTV23CParameterPropertyValueIjLj42E18CPropertyConverterE_02cba8a0 + 0x10;
    puVar14 = PTR__ZTV8InfoBase_02cc49c8 + 0x10;
    uVar21 = 0;
    puVar15 = PTR__ZTV22CParameterPropertyBaseILj42EE_02cb6c60 + 0x10;
    do {
      pppppplStack_88 =
           (long ******)(**(code **)(*param_1 + 0x20))(param_1,*param_2 + uVar21 * 0x40);
      ppppppplVar20 = (long *******)param_1[8];
      ppppppplVar19 = ppppppplVar23;
      if ((long *******)param_1[8] == (long *******)0x0) {
code_r0x01660390:
        memset(auStack_1d0,0,0x148);
        uStack_1b8 = 0;
        uStack_1b0 = 0;
        uStack_198 = 0;
        uStack_1a0 = 0;
        puStack_1e0 = puVar2;
        puStack_1d8 = auStack_1d0;
        puStack_1c0 = &uStack_1b8;
        puStack_1a8 = puVar3;
        Framework::CHash32::CHash32()(auStack_190);
        uStack_168 = 0;
        uStack_170 = 0;
        puStack_1a8 = puVar4;
        puStack_178 = puVar5;
        Framework::CHash32::CHash32()(auStack_160);
        uStack_138 = 0;
        uStack_140 = 0;
        puStack_178 = puVar6;
        puStack_148 = puVar7;
        Framework::CHash32::CHash32()(auStack_130);
        uStack_108 = 0;
        uStack_110 = 0;
        puStack_148 = puVar8;
        puStack_118 = puVar9;
        Framework::CHash32::CHash32()(auStack_100);
        uStack_d8 = 0;
        uStack_e0 = 0;
        puStack_118 = puVar10;
        puStack_e8 = puVar11;
        Framework::CHash32::CHash32()(auStack_d0);
        uStack_a8 = 0;
        uStack_b0 = 0;
        puStack_e8 = puVar12;
        puStack_b8 = puVar15;
        Framework::CHash32::CHash32()(auStack_a0);
        ppppppplVar20 = (long *******)*ppppppplVar23;
        if ((long *******)*ppppppplVar23 == (long *******)0x0) {
          ppppppplVar22 = (long *******)*ppppppplVar23;
          ppppppplVar19 = ppppppplVar23;
          ppppppplVar24 = ppppppplVar23;
        }
        else {
          do {
            while (ppppppplVar19 = ppppppplVar20, ppppppplVar19[4] <= pppppplStack_88) {
              if (pppppplStack_88 <= ppppppplVar19[4]) {
                ppppppplVar22 = ppppppplVar19;
                ppppppplVar24 = (long *******)&ppppppplStack_68;
                goto joined_r0x016604d8;
              }
              ppppppplVar24 = ppppppplVar19 + 1;
              ppppppplVar20 = (long *******)*ppppppplVar24;
              if ((long *******)*ppppppplVar24 == (long *******)0x0) {
                ppppppplVar22 = (long *******)*ppppppplVar24;
                goto joined_r0x016604d8;
              }
            }
            ppppppplVar20 = (long *******)*ppppppplVar19;
          } while ((long *******)*ppppppplVar19 != (long *******)0x0);
          ppppppplVar22 = (long *******)*ppppppplVar19;
          ppppppplVar24 = ppppppplVar19;
        }
joined_r0x016604d8:
        ppppppplStack_68 = ppppppplVar19;
        if (ppppppplVar22 == (long *******)0x0) {
          puStack_b8 = puVar13;
          std::__ndk1::unique_ptr<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CStepUpGachaInfo>, void*>, std::__ndk1::__tree_node_destructor<Framework::CSTLAllocator<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CStepUpGachaInfo>, void*>, Framework::CSTLMapAllocatorInf> > > std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CStepUpGachaInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CStepUpGachaInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CStepUpGachaInfo>, Framework::CSTLMapAllocatorInf> >::__construct_node<unsigned long&, CStepUpGachaInfo>(unsigned long&, CStepUpGachaInfo&&)(appppppplStack_80,plVar18,&pppppplStack_88,&puStack_1e0);
          *appppppplStack_80[0] = (long ******)0x0;
          appppppplStack_80[0][1] = (long ******)0x0;
          appppppplStack_80[0][2] = (long ******)ppppppplVar19;
          *ppppppplVar24 = (long ******)appppppplStack_80[0];
          ppppppplVar20 = appppppplStack_80[0];
          if (*(long *)*plVar18 != 0) {
            *plVar18 = *(long *)*plVar18;
            ppppppplVar20 = (long *******)*ppppppplVar24;
          }
          void std::__ndk1::__tree_balance_after_insert<std::__ndk1::__tree_node_base<void*>*>(std::__ndk1::__tree_node_base<void*>*, std::__ndk1::__tree_node_base<void*>*)(param_1[8],ppppppplVar20);
          param_1[9] = param_1[9] + 1;
          ppppppplVar22 = appppppplStack_80[0];
        }
        puStack_1e0 = PTR__ZTV16CStepUpGachaInfo_02cb8d98 + 0x10;
        puStack_b8 = PTR__ZTV22CParameterPropertyBaseILj42EE_02cb6c60 + 0x10;
        Framework::CHash32::~CHash32()(auStack_a0);
        puStack_e8 = PTR__ZTV22CParameterPropertyBaseILj40EE_02cbd2c0 + 0x10;
        Framework::CHash32::~CHash32()(auStack_d0);
        puStack_118 = PTR__ZTV22CParameterPropertyBaseILj39EE_02cc3d00 + 0x10;
        Framework::CHash32::~CHash32()(auStack_100);
        puStack_148 = PTR__ZTV22CParameterPropertyBaseILj38EE_02cc0aa0 + 0x10;
        Framework::CHash32::~CHash32()(auStack_130);
        puStack_178 = PTR__ZTV22CParameterPropertyBaseILj37EE_02cbda08 + 0x10;
        Framework::CHash32::~CHash32()(auStack_160);
        puStack_1a8 = PTR__ZTV22CParameterPropertyBaseILj36EE_02cb6f78 + 0x10;
        Framework::CHash32::~CHash32()(auStack_190);
        puStack_1e0 = puVar14;
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*)(&puStack_1c0,uStack_1b8);
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*)(&puStack_1d8,auStack_1d0[0]);
        ppppppplVar22 = ppppppplVar22 + 5;
        (*(code *)(*ppppppplVar22)[2])(ppppppplVar22);
      }
      else {
        do {
          while (ppppppplVar22 = ppppppplVar20, ppppppplVar22[4] < pppppplStack_88) {
            ppppppplVar20 = (long *******)ppppppplVar22[1];
            if ((long *******)ppppppplVar22[1] == (long *******)0x0) {
              ppppppplVar22 = ppppppplVar19;
              if (ppppppplVar19 != ppppppplVar23) goto code_r0x01660374;
              goto code_r0x01660390;
            }
          }
          ppppppplVar20 = (long *******)*ppppppplVar22;
          ppppppplVar19 = ppppppplVar22;
        } while ((long *******)*ppppppplVar22 != (long *******)0x0);
        if (ppppppplVar22 == ppppppplVar23) goto code_r0x01660390;
code_r0x01660374:
        if ((pppppplStack_88 < ppppppplVar22[4]) || (ppppppplVar22 == ppppppplVar23))
        goto code_r0x01660390;
        ppppppplVar22 = ppppppplVar22 + 5;
      }
      lVar16 = *param_2 + uVar21 * 0x40;
      iVar17 = *(int *)(lVar16 + 0x20);
      if (iVar17 == 6) {
        (*(code *)**ppppppplVar22)(ppppppplVar22,lVar16 + 0x28);
      }
      else if (iVar17 == 7) {
        (*(code *)(*ppppppplVar22)[1])(ppppppplVar22,*param_2 + uVar21 * 0x40 + 0x28);
      }
      uVar1 = (int)uVar21 + 1;
      uVar21 = (ulong)uVar1;
    } while (uVar1 < *(uint *)(param_2 + 1));
  }
  return 1;
}

// ==== IInfoBaseMap<unsigned long, CPartialMaintenanceInfo>::DeserializeChild(Aska::ASON::AValue::AMap const*)
// vaddr 0x1560b00 | ghidra 0x1660b00 | size 596 | symbol _ZN12IInfoBaseMapIm23CPartialMaintenanceInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN12IInfoBaseMapIm23CPartialMaintenanceInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE
          (long *param_1,long *param_2)

{
  uint uVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined *puVar5;
  int iVar6;
  long *plVar7;
  long lVar8;
  long *plVar9;
  ulong uVar10;
  long *plVar11;
  long *plVar12;
  undefined *puStack_d0;
  undefined8 *puStack_c8;
  undefined8 auStack_c0 [2];
  undefined8 *puStack_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined *puStack_98;
  undefined8 uStack_90;
  undefined1 uStack_88;
  undefined1 auStack_80 [24];
  ulong uStack_68;
  
  plVar12 = param_1 + 8;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CPartialMaintenanceInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CPartialMaintenanceInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CPartialMaintenanceInfo>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CPartialMaintenanceInfo>, void*>*)(param_1 + 7,*plVar12);
  param_1[7] = (long)plVar12;
  param_1[8] = 0;
  param_1[9] = 0;
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0282d54e/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\Info/InfoBase.h"*/,0x1c1,&UNK_027dc58a/*"apParser is null."*/);
    iVar6 = iRam0000000000000008;
  }
  else {
    iVar6 = (int)param_2[1];
  }
  if (iVar6 != 0) {
    uVar10 = 0;
    puVar2 = PTR__ZTV23CPartialMaintenanceInfo_02cbe3f0 + 0x10;
    puVar3 = PTR__ZTV22CParameterPropertyBaseILj20EE_02cc0d08 + 0x10;
    puVar4 = PTR__ZTV23CParameterPropertyValueIjLj20E18CPropertyConverterE_02cc2ce0 + 0x10;
    puVar5 = PTR__ZTV8InfoBase_02cc49c8 + 0x10;
    do {
      uStack_68 = (**(code **)(*param_1 + 0x20))(param_1,*param_2 + uVar10 * 0x40);
      plVar7 = (long *)param_1[8];
      plVar9 = plVar12;
      if ((long *)param_1[8] == (long *)0x0) {
code_r0x01660c4c:
        memset(auStack_c0,0,0x58);
        uStack_a8 = 0;
        uStack_a0 = 0;
        uStack_90 = 0;
        uStack_88 = 0;
        puStack_d0 = puVar2;
        puStack_c8 = auStack_c0;
        puStack_b0 = &uStack_a8;
        puStack_98 = puVar3;
        Framework::CHash32::CHash32()(auStack_80);
        puStack_98 = puVar4;
        lVar8 = std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned long, CPartialMaintenanceInfo>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CPartialMaintenanceInfo>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CPartialMaintenanceInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CPartialMaintenanceInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CPartialMaintenanceInfo>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned long, unsigned long&, CPartialMaintenanceInfo>(unsigned long const&, unsigned long&, CPartialMaintenanceInfo&&)(param_1 + 7,&uStack_68,&uStack_68,&puStack_d0);
        puStack_d0 = puVar2;
        puStack_98 = puVar3;
        Framework::CHash32::~CHash32()(auStack_80);
        puStack_d0 = puVar5;
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*)(&puStack_b0,uStack_a8);
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*)(&puStack_c8,auStack_c0[0]);
        plVar11 = (long *)(lVar8 + 0x28);
        (**(code **)(*plVar11 + 0x10))(plVar11);
      }
      else {
        do {
          while (plVar11 = plVar7, (ulong)plVar11[4] < uStack_68) {
            plVar7 = (long *)plVar11[1];
            if ((long *)plVar11[1] == (long *)0x0) {
              plVar11 = plVar9;
              if (plVar9 != plVar12) goto code_r0x01660c30;
              goto code_r0x01660c4c;
            }
          }
          plVar7 = (long *)*plVar11;
          plVar9 = plVar11;
        } while ((long *)*plVar11 != (long *)0x0);
        if (plVar11 == plVar12) goto code_r0x01660c4c;
code_r0x01660c30:
        if ((uStack_68 < (ulong)plVar11[4]) || (plVar11 == plVar12)) goto code_r0x01660c4c;
        plVar11 = plVar11 + 5;
      }
      lVar8 = *param_2 + uVar10 * 0x40;
      iVar6 = *(int *)(lVar8 + 0x20);
      if (iVar6 == 6) {
        (**(code **)*plVar11)(plVar11,lVar8 + 0x28);
      }
      else if (iVar6 == 7) {
        (**(code **)(*plVar11 + 8))(plVar11,*param_2 + uVar10 * 0x40 + 0x28);
      }
      uVar1 = (int)uVar10 + 1;
      uVar10 = (ulong)uVar1;
    } while (uVar1 < *(uint *)(param_2 + 1));
  }
  return 1;
}

// ==== IInfoBaseMap<unsigned long, CFriendGaugeUpdateInfo>::DeserializeChild(Aska::ASON::AValue::AMap const*)
// vaddr 0x156233c | ghidra 0x166233c | size 1336 | symbol _ZN12IInfoBaseMapIm22CFriendGaugeUpdateInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Type propagation algorithm not settling */

undefined8
_ZN12IInfoBaseMapIm22CFriendGaugeUpdateInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE
          (long *param_1,long *param_2)

{
  uint uVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined *puVar5;
  undefined *puVar6;
  undefined *puVar7;
  undefined *puVar8;
  undefined *puVar9;
  undefined *puVar10;
  undefined *puVar11;
  undefined *puVar12;
  undefined *puVar13;
  undefined *puVar14;
  undefined *puVar15;
  undefined *puVar16;
  undefined *puVar17;
  undefined *puVar18;
  undefined *puVar19;
  long lVar20;
  int iVar21;
  long *plVar22;
  long *******ppppppplVar23;
  long *******ppppppplVar24;
  ulong uVar25;
  long *******ppppppplVar26;
  long *******ppppppplVar27;
  long *******ppppppplVar28;
  undefined *puStack_260;
  undefined1 *puStack_258;
  undefined1 auStack_250 [16];
  undefined8 *puStack_240;
  undefined8 uStack_238;
  undefined8 uStack_230;
  undefined *puStack_228;
  undefined8 uStack_220;
  undefined1 uStack_218;
  undefined1 auStack_210 [24];
  undefined *puStack_1f8;
  undefined8 uStack_1f0;
  undefined1 uStack_1e8;
  undefined1 auStack_1e0 [24];
  undefined *puStack_1c8;
  undefined8 uStack_1c0;
  undefined1 uStack_1b8;
  undefined1 auStack_1b0 [24];
  undefined *puStack_198;
  undefined8 uStack_190;
  undefined1 uStack_188;
  undefined1 auStack_180 [24];
  undefined *puStack_168;
  undefined8 uStack_160;
  undefined1 uStack_158;
  undefined1 auStack_150 [24];
  undefined *puStack_138;
  undefined8 uStack_130;
  undefined1 uStack_128;
  undefined1 auStack_120 [16];
  undefined8 uStack_110;
  undefined8 uStack_108;
  undefined8 uStack_100;
  undefined *puStack_f8;
  undefined8 uStack_f0;
  undefined1 uStack_e8;
  undefined1 auStack_e0 [16];
  undefined8 uStack_d0;
  undefined8 uStack_c8;
  undefined8 uStack_c0;
  undefined *puStack_b8;
  undefined8 uStack_b0;
  undefined1 uStack_a8;
  undefined1 auStack_a0 [24];
  long ******pppppplStack_88;
  long *******appppppplStack_80 [3];
  long *******ppppppplStack_68;
  
  ppppppplVar27 = (long *******)(param_1 + 8);
  plVar22 = param_1 + 7;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CFriendGaugeUpdateInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CFriendGaugeUpdateInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CFriendGaugeUpdateInfo>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CFriendGaugeUpdateInfo>, void*>*)(plVar22,*ppppppplVar27);
  param_1[7] = (long)ppppppplVar27;
  param_1[8] = 0;
  param_1[9] = 0;
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0282d54e/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\Info/InfoBase.h"*/,0x1c1,&UNK_027dc58a/*"apParser is null."*/);
    iVar21 = iRam0000000000000008;
  }
  else {
    iVar21 = (int)param_2[1];
  }
  if (iVar21 != 0) {
    puVar2 = PTR__ZTV16CFriendGaugeInfo_02cb7c80 + 0x10;
    puVar3 = PTR__ZTV22CParameterPropertyBaseILj17EE_02cba1e8 + 0x10;
    puVar4 = PTR__ZTV23CParameterPropertyValueIjLj17E18CPropertyConverterE_02cbb3b8 + 0x10;
    puVar5 = PTR__ZTV22CParameterPropertyBaseILj18EE_02cbe238 + 0x10;
    puVar6 = PTR__ZTV23CParameterPropertyValueIjLj18E18CPropertyConverterE_02cbcd58 + 0x10;
    puVar7 = PTR__ZTV22CParameterPropertyBaseILj19EE_02cc4c98 + 0x10;
    puVar8 = PTR__ZTV23CParameterPropertyValueIjLj19E18CPropertyConverterE_02cc13e8 + 0x10;
    puVar9 = PTR__ZTV22CParameterPropertyBaseILj20EE_02cc0d08 + 0x10;
    puVar10 = PTR__ZTV23CParameterPropertyValueIjLj20E18CPropertyConverterE_02cc2ce0 + 0x10;
    puVar11 = PTR__ZTV22CParameterPropertyBaseILj21EE_02cc1310 + 0x10;
    puVar12 = PTR__ZTV23CParameterPropertyValueIjLj21E18CPropertyConverterE_02cbeae0 + 0x10;
    puVar13 = PTR__ZTV22CParameterPropertyBaseILj22EE_02cc4630 + 0x10;
    puVar14 = PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj22EE_02cbe640
              + 0x10;
    puVar15 = PTR__ZTV22CParameterPropertyBaseILj23EE_02cbad98 + 0x10;
    puVar16 = PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj23EE_02cb8300
              + 0x10;
    puVar17 = PTR__ZTV23CParameterPropertyValueIjLj53E18CPropertyConverterE_02cbe708 + 0x10;
    puVar18 = PTR__ZTV22CFriendGaugeUpdateInfo_02cc0250 + 0x10;
    uVar25 = 0;
    puVar19 = PTR__ZTV22CParameterPropertyBaseILj53EE_02cb75b8 + 0x10;
    do {
      pppppplStack_88 =
           (long ******)(**(code **)(*param_1 + 0x20))(param_1,*param_2 + uVar25 * 0x40);
      ppppppplVar24 = (long *******)param_1[8];
      ppppppplVar23 = ppppppplVar27;
      if ((long *******)param_1[8] == (long *******)0x0) {
code_r0x016625ac:
        memset(auStack_250,0,0x1c8);
        uStack_238 = 0;
        uStack_230 = 0;
        uStack_218 = 0;
        uStack_220 = 0;
        puStack_260 = puVar2;
        puStack_258 = auStack_250;
        puStack_240 = &uStack_238;
        puStack_228 = puVar3;
        Framework::CHash32::CHash32()(auStack_210);
        uStack_1e8 = 0;
        uStack_1f0 = 0;
        puStack_228 = puVar4;
        puStack_1f8 = puVar5;
        Framework::CHash32::CHash32()(auStack_1e0);
        uStack_1b8 = 0;
        uStack_1c0 = 0;
        puStack_1f8 = puVar6;
        puStack_1c8 = puVar7;
        Framework::CHash32::CHash32()(auStack_1b0);
        uStack_188 = 0;
        uStack_190 = 0;
        puStack_1c8 = puVar8;
        puStack_198 = puVar9;
        Framework::CHash32::CHash32()(auStack_180);
        uStack_158 = 0;
        uStack_160 = 0;
        puStack_198 = puVar10;
        puStack_168 = puVar11;
        Framework::CHash32::CHash32()(auStack_150);
        uStack_130 = 0;
        uStack_128 = 0;
        puStack_168 = puVar12;
        puStack_138 = puVar13;
        Framework::CHash32::CHash32()(auStack_120);
        uStack_108 = 0;
        uStack_100 = 0;
        uStack_110 = 0;
        uStack_f0 = 0;
        uStack_e8 = 0;
        puStack_138 = puVar14;
        puStack_f8 = puVar15;
        Framework::CHash32::CHash32()(auStack_e0);
        uStack_c8 = 0;
        uStack_c0 = 0;
        uStack_d0 = 0;
        uStack_b0 = 0;
        uStack_a8 = 0;
        puStack_260 = puVar18;
        puStack_f8 = puVar16;
        puStack_b8 = puVar19;
        Framework::CHash32::CHash32()(auStack_a0);
        ppppppplVar24 = (long *******)*ppppppplVar27;
        if ((long *******)*ppppppplVar27 == (long *******)0x0) {
          ppppppplVar26 = (long *******)*ppppppplVar27;
          ppppppplVar23 = ppppppplVar27;
          ppppppplVar28 = ppppppplVar27;
        }
        else {
          do {
            while (ppppppplVar23 = ppppppplVar24, ppppppplVar23[4] <= pppppplStack_88) {
              if (pppppplStack_88 <= ppppppplVar23[4]) {
                ppppppplVar26 = ppppppplVar23;
                ppppppplVar28 = (long *******)&ppppppplStack_68;
                goto joined_r0x01662748;
              }
              ppppppplVar28 = ppppppplVar23 + 1;
              ppppppplVar24 = (long *******)*ppppppplVar28;
              if ((long *******)*ppppppplVar28 == (long *******)0x0) {
                ppppppplVar26 = (long *******)*ppppppplVar28;
                goto joined_r0x01662748;
              }
            }
            ppppppplVar24 = (long *******)*ppppppplVar23;
          } while ((long *******)*ppppppplVar23 != (long *******)0x0);
          ppppppplVar26 = (long *******)*ppppppplVar23;
          ppppppplVar28 = ppppppplVar23;
        }
joined_r0x01662748:
        ppppppplStack_68 = ppppppplVar23;
        if (ppppppplVar26 == (long *******)0x0) {
          puStack_b8 = puVar17;
          std::__ndk1::unique_ptr<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CFriendGaugeUpdateInfo>, void*>, std::__ndk1::__tree_node_destructor<Framework::CSTLAllocator<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CFriendGaugeUpdateInfo>, void*>, Framework::CSTLMapAllocatorInf> > > std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CFriendGaugeUpdateInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CFriendGaugeUpdateInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CFriendGaugeUpdateInfo>, Framework::CSTLMapAllocatorInf> >::__construct_node<unsigned long&, CFriendGaugeUpdateInfo>(unsigned long&, CFriendGaugeUpdateInfo&&)(appppppplStack_80,plVar22,&pppppplStack_88,&puStack_260);
          *appppppplStack_80[0] = (long ******)0x0;
          appppppplStack_80[0][1] = (long ******)0x0;
          appppppplStack_80[0][2] = (long ******)ppppppplVar23;
          *ppppppplVar28 = (long ******)appppppplStack_80[0];
          ppppppplVar24 = appppppplStack_80[0];
          if (*(long *)*plVar22 != 0) {
            *plVar22 = *(long *)*plVar22;
            ppppppplVar24 = (long *******)*ppppppplVar28;
          }
          void std::__ndk1::__tree_balance_after_insert<std::__ndk1::__tree_node_base<void*>*>(std::__ndk1::__tree_node_base<void*>*, std::__ndk1::__tree_node_base<void*>*)(param_1[8],ppppppplVar24);
          param_1[9] = param_1[9] + 1;
          ppppppplVar26 = appppppplStack_80[0];
        }
        puStack_260 = PTR__ZTV22CFriendGaugeUpdateInfo_02cc0250 + 0x10;
        puStack_b8 = PTR__ZTV22CParameterPropertyBaseILj53EE_02cb75b8 + 0x10;
        Framework::CHash32::~CHash32()(auStack_a0);
        CFriendGaugeInfo::~CFriendGaugeInfo()(&puStack_260);
        ppppppplVar26 = ppppppplVar26 + 5;
        (*(code *)(*ppppppplVar26)[2])(ppppppplVar26);
      }
      else {
        do {
          while (ppppppplVar26 = ppppppplVar24, ppppppplVar26[4] < pppppplStack_88) {
            ppppppplVar24 = (long *******)ppppppplVar26[1];
            if ((long *******)ppppppplVar26[1] == (long *******)0x0) {
              ppppppplVar26 = ppppppplVar23;
              if (ppppppplVar23 != ppppppplVar27) goto code_r0x01662590;
              goto code_r0x016625ac;
            }
          }
          ppppppplVar24 = (long *******)*ppppppplVar26;
          ppppppplVar23 = ppppppplVar26;
        } while ((long *******)*ppppppplVar26 != (long *******)0x0);
        if (ppppppplVar26 == ppppppplVar27) goto code_r0x016625ac;
code_r0x01662590:
        if ((pppppplStack_88 < ppppppplVar26[4]) || (ppppppplVar26 == ppppppplVar27))
        goto code_r0x016625ac;
        ppppppplVar26 = ppppppplVar26 + 5;
      }
      lVar20 = *param_2 + uVar25 * 0x40;
      iVar21 = *(int *)(lVar20 + 0x20);
      if (iVar21 == 6) {
        (*(code *)**ppppppplVar26)(ppppppplVar26,lVar20 + 0x28);
      }
      else if (iVar21 == 7) {
        (*(code *)(*ppppppplVar26)[1])(ppppppplVar26,*param_2 + uVar25 * 0x40 + 0x28);
      }
      uVar1 = (int)uVar25 + 1;
      uVar25 = (ulong)uVar1;
    } while (uVar1 < *(uint *)(param_2 + 1));
  }
  return 1;
}

// ==== IInfoBaseMap<unsigned long, CPlayerCharacterFavorInfoElement>::DeserializeChild(Aska::ASON::AValue::AMap const*)
// vaddr 0x156733c | ghidra 0x166733c | size 1116 | symbol _ZN12IInfoBaseMapIm32CPlayerCharacterFavorInfoElementE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Type propagation algorithm not settling */

undefined8
_ZN12IInfoBaseMapIm32CPlayerCharacterFavorInfoElementE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE
          (long *param_1,long *param_2)

{
  uint uVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined *puVar5;
  undefined *puVar6;
  undefined *puVar7;
  undefined *puVar8;
  undefined *puVar9;
  undefined *puVar10;
  undefined *puVar11;
  undefined *puVar12;
  undefined *puVar13;
  undefined *puVar14;
  long lVar15;
  int iVar16;
  long *plVar17;
  long *******ppppppplVar18;
  long *******ppppppplVar19;
  ulong uVar20;
  long *******ppppppplVar21;
  long *******ppppppplVar22;
  long *******ppppppplVar23;
  undefined *puStack_200;
  undefined1 *puStack_1f8;
  undefined1 auStack_1f0 [16];
  undefined8 *puStack_1e0;
  undefined8 uStack_1d8;
  undefined8 uStack_1d0;
  undefined *puStack_1c8;
  undefined8 uStack_1c0;
  undefined1 uStack_1b8;
  undefined1 auStack_1b0 [24];
  undefined *puStack_198;
  undefined8 uStack_190;
  undefined1 uStack_188;
  undefined1 auStack_180 [24];
  undefined *puStack_168;
  undefined8 uStack_160;
  undefined1 uStack_158;
  undefined1 auStack_150 [24];
  undefined *puStack_138;
  undefined8 uStack_130;
  undefined1 uStack_128;
  undefined1 auStack_120 [16];
  undefined8 uStack_110;
  undefined8 uStack_108;
  undefined8 uStack_100;
  undefined *puStack_f8;
  undefined8 uStack_f0;
  undefined1 uStack_e8;
  undefined1 auStack_e0 [24];
  undefined *puStack_c8;
  undefined8 uStack_c0;
  undefined1 uStack_b8;
  undefined1 auStack_b0 [16];
  undefined8 uStack_a0;
  undefined8 uStack_98;
  undefined8 uStack_90;
  long ******pppppplStack_88;
  long *******appppppplStack_80 [3];
  long *******ppppppplStack_68;
  
  ppppppplVar21 = (long *******)(param_1 + 8);
  plVar17 = param_1 + 7;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CPlayerCharacterFavorInfoElement>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CPlayerCharacterFavorInfoElement>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CPlayerCharacterFavorInfoElement>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CPlayerCharacterFavorInfoElement>, void*>*)(plVar17,*ppppppplVar21);
  param_1[7] = (long)ppppppplVar21;
  param_1[8] = 0;
  param_1[9] = 0;
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0282d54e/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\Info/InfoBase.h"*/,0x1c1,&UNK_027dc58a/*"apParser is null."*/);
    iVar16 = iRam0000000000000008;
  }
  else {
    iVar16 = (int)param_2[1];
  }
  if (iVar16 != 0) {
    puVar2 = PTR__ZTV32CPlayerCharacterFavorInfoElement_02cc0980 + 0x10;
    puVar3 = PTR__ZTV22CParameterPropertyBaseILj13EE_02cba498 + 0x10;
    puVar4 = PTR__ZTV23CParameterPropertyValueIjLj13E18CPropertyConverterE_02cbd818 + 0x10;
    puVar5 = PTR__ZTV22CParameterPropertyBaseILj14EE_02cb9db0 + 0x10;
    puVar6 = PTR__ZTV23CParameterPropertyValueIjLj14E18CPropertyConverterE_02cbaef8 + 0x10;
    puVar7 = PTR__ZTV22CParameterPropertyBaseILj15EE_02cc0790 + 0x10;
    puVar8 = PTR__ZTV23CParameterPropertyValueIjLj15E18CPropertyConverterE_02cc1598 + 0x10;
    puVar9 = PTR__ZTV22CParameterPropertyBaseILj16EE_02cb9c20 + 0x10;
    puVar10 = PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj16EE_02cbf570
              + 0x10;
    puVar11 = PTR__ZTV22CParameterPropertyBaseILj17EE_02cba1e8 + 0x10;
    puVar12 = PTR__ZTV23CParameterPropertyValueIjLj17E18CPropertyConverterE_02cbb3b8 + 0x10;
    puVar13 = PTR__ZTV22CParameterPropertyBaseILj18EE_02cbe238 + 0x10;
    uVar20 = 0;
    puVar14 = PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj18EE_02cc2e68
              + 0x10;
    do {
      pppppplStack_88 =
           (long ******)(**(code **)(*param_1 + 0x20))(param_1,*param_2 + uVar20 * 0x40);
      ppppppplVar19 = (long *******)param_1[8];
      ppppppplVar18 = ppppppplVar21;
      if ((long *******)param_1[8] == (long *******)0x0) {
code_r0x01667548:
        memset(auStack_1f0,0,0x168);
        uStack_1d8 = 0;
        uStack_1d0 = 0;
        uStack_1b8 = 0;
        uStack_1c0 = 0;
        puStack_200 = puVar2;
        puStack_1f8 = auStack_1f0;
        puStack_1e0 = &uStack_1d8;
        puStack_1c8 = puVar3;
        Framework::CHash32::CHash32()(auStack_1b0);
        uStack_188 = 0;
        uStack_190 = 0;
        puStack_1c8 = puVar4;
        puStack_198 = puVar5;
        Framework::CHash32::CHash32()(auStack_180);
        uStack_158 = 0;
        uStack_160 = 0;
        puStack_198 = puVar6;
        puStack_168 = puVar7;
        Framework::CHash32::CHash32()(auStack_150);
        uStack_128 = 0;
        uStack_130 = 0;
        puStack_168 = puVar8;
        puStack_138 = puVar9;
        Framework::CHash32::CHash32()(auStack_120);
        uStack_108 = 0;
        uStack_100 = 0;
        uStack_110 = 0;
        uStack_e8 = 0;
        uStack_f0 = 0;
        puStack_138 = puVar10;
        puStack_f8 = puVar11;
        Framework::CHash32::CHash32()(auStack_e0);
        uStack_b8 = 0;
        uStack_c0 = 0;
        puStack_f8 = puVar12;
        puStack_c8 = puVar13;
        Framework::CHash32::CHash32()(auStack_b0);
        uStack_98 = 0;
        uStack_90 = 0;
        uStack_a0 = 0;
        ppppppplVar19 = (long *******)*ppppppplVar21;
        if ((long *******)*ppppppplVar21 == (long *******)0x0) {
          ppppppplVar23 = (long *******)*ppppppplVar21;
          ppppppplVar18 = ppppppplVar21;
          ppppppplVar22 = ppppppplVar21;
        }
        else {
          do {
            while (ppppppplVar18 = ppppppplVar19, ppppppplVar18[4] <= pppppplStack_88) {
              if (pppppplStack_88 <= ppppppplVar18[4]) {
                ppppppplVar23 = ppppppplVar18;
                ppppppplVar22 = (long *******)&ppppppplStack_68;
                goto joined_r0x01667694;
              }
              ppppppplVar22 = ppppppplVar18 + 1;
              ppppppplVar19 = (long *******)*ppppppplVar22;
              if ((long *******)*ppppppplVar22 == (long *******)0x0) {
                ppppppplVar23 = (long *******)*ppppppplVar22;
                goto joined_r0x01667694;
              }
            }
            ppppppplVar19 = (long *******)*ppppppplVar18;
          } while ((long *******)*ppppppplVar18 != (long *******)0x0);
          ppppppplVar23 = (long *******)*ppppppplVar18;
          ppppppplVar22 = ppppppplVar18;
        }
joined_r0x01667694:
        puStack_c8 = puVar14;
        ppppppplStack_68 = ppppppplVar18;
        if (ppppppplVar23 == (long *******)0x0) {
          std::__ndk1::unique_ptr<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CPlayerCharacterFavorInfoElement>, void*>, std::__ndk1::__tree_node_destructor<Framework::CSTLAllocator<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CPlayerCharacterFavorInfoElement>, void*>, Framework::CSTLMapAllocatorInf> > > std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CPlayerCharacterFavorInfoElement>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CPlayerCharacterFavorInfoElement>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CPlayerCharacterFavorInfoElement>, Framework::CSTLMapAllocatorInf> >::__construct_node<unsigned long&, CPlayerCharacterFavorInfoElement>(unsigned long&, CPlayerCharacterFavorInfoElement&&)(appppppplStack_80,plVar17,&pppppplStack_88,&puStack_200);
          *appppppplStack_80[0] = (long ******)0x0;
          appppppplStack_80[0][1] = (long ******)0x0;
          appppppplStack_80[0][2] = (long ******)ppppppplVar18;
          *ppppppplVar22 = (long ******)appppppplStack_80[0];
          ppppppplVar19 = appppppplStack_80[0];
          if (*(long *)*plVar17 != 0) {
            *plVar17 = *(long *)*plVar17;
            ppppppplVar19 = (long *******)*ppppppplVar22;
          }
          void std::__ndk1::__tree_balance_after_insert<std::__ndk1::__tree_node_base<void*>*>(std::__ndk1::__tree_node_base<void*>*, std::__ndk1::__tree_node_base<void*>*)(param_1[8],ppppppplVar19);
          param_1[9] = param_1[9] + 1;
          ppppppplVar23 = appppppplStack_80[0];
        }
        CPlayerCharacterFavorInfoElement::~CPlayerCharacterFavorInfoElement()(&puStack_200);
        ppppppplVar23 = ppppppplVar23 + 5;
        (*(code *)(*ppppppplVar23)[2])(ppppppplVar23);
      }
      else {
        do {
          while (ppppppplVar23 = ppppppplVar19, ppppppplVar23[4] < pppppplStack_88) {
            ppppppplVar19 = (long *******)ppppppplVar23[1];
            if ((long *******)ppppppplVar23[1] == (long *******)0x0) {
              ppppppplVar23 = ppppppplVar18;
              if (ppppppplVar18 != ppppppplVar21) goto code_r0x0166752c;
              goto code_r0x01667548;
            }
          }
          ppppppplVar19 = (long *******)*ppppppplVar23;
          ppppppplVar18 = ppppppplVar23;
        } while ((long *******)*ppppppplVar23 != (long *******)0x0);
        if (ppppppplVar23 == ppppppplVar21) goto code_r0x01667548;
code_r0x0166752c:
        if ((pppppplStack_88 < ppppppplVar23[4]) || (ppppppplVar23 == ppppppplVar21))
        goto code_r0x01667548;
        ppppppplVar23 = ppppppplVar23 + 5;
      }
      lVar15 = *param_2 + uVar20 * 0x40;
      iVar16 = *(int *)(lVar15 + 0x20);
      if (iVar16 == 6) {
        (*(code *)**ppppppplVar23)(ppppppplVar23,lVar15 + 0x28);
      }
      else if (iVar16 == 7) {
        (*(code *)(*ppppppplVar23)[1])(ppppppplVar23,*param_2 + uVar20 * 0x40 + 0x28);
      }
      uVar1 = (int)uVar20 + 1;
      uVar20 = (ulong)uVar1;
    } while (uVar1 < *(uint *)(param_2 + 1));
  }
  return 1;
}

// ==== IInfoBaseMap<unsigned long, CDecoObjectInfo>::DeserializeChild(Aska::ASON::AValue::AMap const*)
// vaddr 0x1569254 | ghidra 0x1669254 | size 1132 | symbol _ZN12IInfoBaseMapIm15CDecoObjectInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Type propagation algorithm not settling */

undefined8
_ZN12IInfoBaseMapIm15CDecoObjectInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE
          (long *param_1,long *param_2)

{
  uint uVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined *puVar5;
  undefined *puVar6;
  undefined *puVar7;
  undefined *puVar8;
  undefined *puVar9;
  undefined *puVar10;
  undefined *puVar11;
  long lVar12;
  int iVar13;
  long *plVar14;
  long *******ppppppplVar15;
  long *******ppppppplVar16;
  ulong uVar17;
  long *******ppppppplVar18;
  long *******ppppppplVar19;
  long *******ppppppplVar20;
  undefined *puStack_180;
  undefined8 *puStack_178;
  undefined8 auStack_170 [2];
  undefined8 *puStack_160;
  undefined8 uStack_158;
  undefined8 uStack_150;
  undefined *puStack_148;
  undefined8 uStack_140;
  undefined1 uStack_138;
  undefined1 auStack_130 [24];
  undefined *puStack_118;
  undefined8 uStack_110;
  undefined1 uStack_108;
  undefined1 auStack_100 [24];
  undefined *puStack_e8;
  undefined8 uStack_e0;
  undefined1 uStack_d8;
  undefined1 auStack_d0 [24];
  undefined *puStack_b8;
  undefined8 uStack_b0;
  undefined1 uStack_a8;
  undefined1 auStack_a0 [24];
  long ******pppppplStack_88;
  long *******appppppplStack_80 [3];
  long *******ppppppplStack_68;
  
  ppppppplVar18 = (long *******)(param_1 + 8);
  plVar14 = param_1 + 7;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CDecoObjectInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CDecoObjectInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CDecoObjectInfo>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CDecoObjectInfo>, void*>*)(plVar14,*ppppppplVar18);
  param_1[7] = (long)ppppppplVar18;
  param_1[8] = 0;
  param_1[9] = 0;
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0282d54e/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\Info/InfoBase.h"*/,0x1c1,&UNK_027dc58a/*"apParser is null."*/);
    iVar13 = iRam0000000000000008;
  }
  else {
    iVar13 = (int)param_2[1];
  }
  if (iVar13 != 0) {
    puVar2 = PTR__ZTV15CDecoObjectInfo_02cbae28 + 0x10;
    puVar3 = PTR__ZTV22CParameterPropertyBaseILj16EE_02cb9c20 + 0x10;
    puVar4 = PTR__ZTV23CParameterPropertyValueImLj16E18CPropertyConverterE_02cbcfa0 + 0x10;
    puVar5 = PTR__ZTV22CParameterPropertyBaseILj17EE_02cba1e8 + 0x10;
    puVar6 = PTR__ZTV23CParameterPropertyValueIjLj17E18CPropertyConverterE_02cbb3b8 + 0x10;
    puVar7 = PTR__ZTV22CParameterPropertyBaseILj18EE_02cbe238 + 0x10;
    puVar8 = PTR__ZTV23CParameterPropertyValueIjLj18E18CPropertyConverterE_02cbcd58 + 0x10;
    puVar9 = PTR__ZTV22CParameterPropertyBaseILj19EE_02cc4c98 + 0x10;
    puVar10 = PTR__ZTV23CParameterPropertyValueIjLj19E18CPropertyConverterE_02cc13e8 + 0x10;
    uVar17 = 0;
    puVar11 = PTR__ZTV8InfoBase_02cc49c8 + 0x10;
    do {
      pppppplStack_88 =
           (long ******)(**(code **)(*param_1 + 0x20))(param_1,*param_2 + uVar17 * 0x40);
      ppppppplVar16 = (long *******)param_1[8];
      ppppppplVar15 = ppppppplVar18;
      if ((long *******)param_1[8] == (long *******)0x0) {
code_r0x01669424:
        memset(auStack_170,0,0xe8);
        uStack_158 = 0;
        uStack_150 = 0;
        uStack_138 = 0;
        uStack_140 = 0;
        puStack_180 = puVar2;
        puStack_178 = auStack_170;
        puStack_160 = &uStack_158;
        puStack_148 = puVar3;
        Framework::CHash32::CHash32()(auStack_130);
        uStack_108 = 0;
        uStack_110 = 0;
        puStack_148 = puVar4;
        puStack_118 = puVar5;
        Framework::CHash32::CHash32()(auStack_100);
        uStack_d8 = 0;
        uStack_e0 = 0;
        puStack_118 = puVar6;
        puStack_e8 = puVar7;
        Framework::CHash32::CHash32()(auStack_d0);
        uStack_a8 = 0;
        uStack_b0 = 0;
        puStack_e8 = puVar8;
        puStack_b8 = puVar9;
        Framework::CHash32::CHash32()(auStack_a0);
        ppppppplVar16 = (long *******)*ppppppplVar18;
        if ((long *******)*ppppppplVar18 == (long *******)0x0) {
          ppppppplVar20 = (long *******)*ppppppplVar18;
          ppppppplVar15 = ppppppplVar18;
          ppppppplVar19 = ppppppplVar18;
        }
        else {
          do {
            while (ppppppplVar15 = ppppppplVar16, ppppppplVar15[4] <= pppppplStack_88) {
              if (pppppplStack_88 <= ppppppplVar15[4]) {
                ppppppplVar20 = ppppppplVar15;
                ppppppplVar19 = (long *******)&ppppppplStack_68;
                goto joined_r0x01669530;
              }
              ppppppplVar19 = ppppppplVar15 + 1;
              ppppppplVar16 = (long *******)*ppppppplVar19;
              if ((long *******)*ppppppplVar19 == (long *******)0x0) {
                ppppppplVar20 = (long *******)*ppppppplVar19;
                goto joined_r0x01669530;
              }
            }
            ppppppplVar16 = (long *******)*ppppppplVar15;
          } while ((long *******)*ppppppplVar15 != (long *******)0x0);
          ppppppplVar20 = (long *******)*ppppppplVar15;
          ppppppplVar19 = ppppppplVar15;
        }
joined_r0x01669530:
        ppppppplStack_68 = ppppppplVar15;
        if (ppppppplVar20 == (long *******)0x0) {
          puStack_b8 = puVar10;
          std::__ndk1::unique_ptr<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CDecoObjectInfo>, void*>, std::__ndk1::__tree_node_destructor<Framework::CSTLAllocator<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CDecoObjectInfo>, void*>, Framework::CSTLMapAllocatorInf> > > std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CDecoObjectInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CDecoObjectInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CDecoObjectInfo>, Framework::CSTLMapAllocatorInf> >::__construct_node<unsigned long&, CDecoObjectInfo>(unsigned long&, CDecoObjectInfo&&)(appppppplStack_80,plVar14,&pppppplStack_88,&puStack_180);
          *appppppplStack_80[0] = (long ******)0x0;
          appppppplStack_80[0][1] = (long ******)0x0;
          appppppplStack_80[0][2] = (long ******)ppppppplVar15;
          *ppppppplVar19 = (long ******)appppppplStack_80[0];
          ppppppplVar16 = appppppplStack_80[0];
          if (*(long *)*plVar14 != 0) {
            *plVar14 = *(long *)*plVar14;
            ppppppplVar16 = (long *******)*ppppppplVar19;
          }
          void std::__ndk1::__tree_balance_after_insert<std::__ndk1::__tree_node_base<void*>*>(std::__ndk1::__tree_node_base<void*>*, std::__ndk1::__tree_node_base<void*>*)(param_1[8],ppppppplVar16);
          param_1[9] = param_1[9] + 1;
          ppppppplVar20 = appppppplStack_80[0];
        }
        puStack_180 = PTR__ZTV15CDecoObjectInfo_02cbae28 + 0x10;
        puStack_b8 = PTR__ZTV22CParameterPropertyBaseILj19EE_02cc4c98 + 0x10;
        Framework::CHash32::~CHash32()(auStack_a0);
        puStack_e8 = PTR__ZTV22CParameterPropertyBaseILj18EE_02cbe238 + 0x10;
        Framework::CHash32::~CHash32()(auStack_d0);
        puStack_118 = PTR__ZTV22CParameterPropertyBaseILj17EE_02cba1e8 + 0x10;
        Framework::CHash32::~CHash32()(auStack_100);
        puStack_148 = PTR__ZTV22CParameterPropertyBaseILj16EE_02cb9c20 + 0x10;
        Framework::CHash32::~CHash32()(auStack_130);
        puStack_180 = puVar11;
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*)(&puStack_160,uStack_158);
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*)(&puStack_178,auStack_170[0]);
        ppppppplVar20 = ppppppplVar20 + 5;
        (*(code *)(*ppppppplVar20)[2])(ppppppplVar20);
      }
      else {
        do {
          while (ppppppplVar20 = ppppppplVar16, ppppppplVar20[4] < pppppplStack_88) {
            ppppppplVar16 = (long *******)ppppppplVar20[1];
            if ((long *******)ppppppplVar20[1] == (long *******)0x0) {
              ppppppplVar20 = ppppppplVar15;
              if (ppppppplVar15 != ppppppplVar18) goto code_r0x01669408;
              goto code_r0x01669424;
            }
          }
          ppppppplVar16 = (long *******)*ppppppplVar20;
          ppppppplVar15 = ppppppplVar20;
        } while ((long *******)*ppppppplVar20 != (long *******)0x0);
        if (ppppppplVar20 == ppppppplVar18) goto code_r0x01669424;
code_r0x01669408:
        if ((pppppplStack_88 < ppppppplVar20[4]) || (ppppppplVar20 == ppppppplVar18))
        goto code_r0x01669424;
        ppppppplVar20 = ppppppplVar20 + 5;
      }
      lVar12 = *param_2 + uVar17 * 0x40;
      iVar13 = *(int *)(lVar12 + 0x20);
      if (iVar13 == 6) {
        (*(code *)**ppppppplVar20)(ppppppplVar20,lVar12 + 0x28);
      }
      else if (iVar13 == 7) {
        (*(code *)(*ppppppplVar20)[1])(ppppppplVar20,*param_2 + uVar17 * 0x40 + 0x28);
      }
      uVar1 = (int)uVar17 + 1;
      uVar17 = (ulong)uVar1;
    } while (uVar1 < *(uint *)(param_2 + 1));
  }
  return 1;
}

// ==== IInfoBaseMap<unsigned long, CBattleEvaluationResultInfo>::DeserializeChild(Aska::ASON::AValue::AMap const*)
// vaddr 0x156a158 | ghidra 0x166a158 | size 1660 | symbol _ZN12IInfoBaseMapIm27CBattleEvaluationResultInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Type propagation algorithm not settling */

undefined8
_ZN12IInfoBaseMapIm27CBattleEvaluationResultInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE
          (long *param_1,long *param_2)

{
  uint uVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined *puVar5;
  undefined *puVar6;
  undefined *puVar7;
  undefined *puVar8;
  undefined *puVar9;
  undefined *puVar10;
  undefined *puVar11;
  undefined *puVar12;
  undefined *puVar13;
  undefined *puVar14;
  undefined *puVar15;
  undefined *puVar16;
  undefined *puVar17;
  undefined *puVar18;
  undefined *puVar19;
  undefined *puVar20;
  long lVar21;
  int iVar22;
  long *plVar23;
  long *******ppppppplVar24;
  long *******ppppppplVar25;
  ulong uVar26;
  long *******ppppppplVar27;
  long *******ppppppplVar28;
  long *******ppppppplVar29;
  undefined *puStack_358;
  undefined8 *puStack_350;
  undefined8 auStack_348 [2];
  undefined8 *puStack_338;
  undefined8 uStack_330;
  undefined8 uStack_328;
  undefined *puStack_320;
  undefined8 uStack_318;
  undefined1 uStack_310;
  undefined1 auStack_308 [24];
  undefined *puStack_2f0;
  undefined8 uStack_2e8;
  undefined1 uStack_2e0;
  undefined1 auStack_2d8 [24];
  undefined *puStack_2c0;
  undefined8 uStack_2b8;
  undefined1 uStack_2b0;
  undefined1 auStack_2a8 [24];
  undefined *puStack_290;
  undefined8 *puStack_288;
  undefined8 uStack_280;
  undefined8 uStack_278;
  undefined8 *puStack_270;
  undefined8 uStack_268;
  undefined8 uStack_260;
  undefined *puStack_258;
  undefined8 uStack_250;
  undefined1 uStack_248;
  undefined1 auStack_240 [24];
  undefined *puStack_228;
  undefined8 uStack_220;
  undefined1 uStack_218;
  undefined1 auStack_210 [24];
  undefined *puStack_1f8;
  undefined8 uStack_1f0;
  undefined1 uStack_1e8;
  undefined1 auStack_1e0 [24];
  undefined *puStack_1c8;
  undefined8 *puStack_1c0;
  undefined8 uStack_1b8;
  undefined8 uStack_1b0;
  undefined8 *puStack_1a8;
  undefined8 uStack_1a0;
  undefined8 uStack_198;
  undefined8 uStack_190;
  undefined8 uStack_188;
  undefined8 uStack_180;
  undefined *puStack_178;
  undefined8 *puStack_170;
  undefined8 uStack_168;
  undefined8 uStack_160;
  undefined8 *puStack_158;
  undefined8 uStack_150;
  undefined8 uStack_148;
  undefined8 uStack_140;
  undefined8 uStack_138;
  undefined8 uStack_130;
  undefined *puStack_128;
  undefined8 *puStack_120;
  undefined8 uStack_118;
  undefined8 uStack_110;
  undefined8 *puStack_108;
  undefined8 uStack_100;
  undefined8 uStack_f8;
  undefined8 uStack_f0;
  undefined8 uStack_e8;
  undefined8 uStack_e0;
  undefined *puStack_d8;
  undefined8 *puStack_d0;
  undefined8 uStack_c8;
  undefined8 uStack_c0;
  undefined8 *puStack_b8;
  undefined8 uStack_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined8 uStack_98;
  undefined8 uStack_90;
  long ******pppppplStack_88;
  long *******appppppplStack_80 [3];
  long *******ppppppplStack_68;
  
  ppppppplVar29 = (long *******)(param_1 + 8);
  plVar23 = param_1 + 7;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CBattleEvaluationResultInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CBattleEvaluationResultInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CBattleEvaluationResultInfo>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CBattleEvaluationResultInfo>, void*>*)(plVar23,*ppppppplVar29);
  param_1[7] = (long)ppppppplVar29;
  param_1[8] = 0;
  param_1[9] = 0;
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0282d54e/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\Info/InfoBase.h"*/,0x1c1,&UNK_027dc58a/*"apParser is null."*/);
    iVar22 = iRam0000000000000008;
  }
  else {
    iVar22 = (int)param_2[1];
  }
  if (iVar22 != 0) {
    puVar2 = PTR__ZTV23CParameterPropertyValueIjLj228E18CPropertyConverterE_02cc2500 + 0x10;
    puVar3 = PTR__ZTV23CParameterPropertyValueIjLj229E18CPropertyConverterE_02cc4cc8 + 0x10;
    puVar4 = PTR__ZTV23CParameterPropertyValueIjLj230E18CPropertyConverterE_02cbe4b8 + 0x10;
    puVar5 = PTR__ZTV22CMissionResultDropInfo_02cb75c0 + 0x10;
    puVar6 = PTR__ZTV22CParameterPropertyBaseILj101EE_02cbe0f0 + 0x10;
    puVar7 = PTR__ZTV23CParameterPropertyValueIjLj101E18CPropertyConverterE_02cbfd40 + 0x10;
    uVar26 = 0;
    puVar8 = PTR__ZTV22CParameterPropertyBaseILj102EE_02cb7580 + 0x10;
    puVar9 = PTR__ZTV23CParameterPropertyValueIjLj102E18CPropertyConverterE_02cb7cf8 + 0x10;
    puVar10 = PTR__ZTV22CParameterPropertyBaseILj103EE_02cb80d8 + 0x10;
    puVar11 = PTR__ZTV23CParameterPropertyValueIjLj103E18CPropertyConverterE_02cbef30 + 0x10;
    puVar12 = PTR__ZTV24CMissionDropItemInfoList_02cbc908 + 0x10;
    puVar13 = PTR__ZTV29CMissionDropStackItemInfoList_02cba928 + 0x10;
    puVar14 = PTR__ZTV13CAddStampList_02cbd958 + 0x10;
    puVar15 = PTR__ZTV29CMissionDropCharacterInfoList_02cbc8b0 + 0x10;
    puVar16 = PTR__ZTV8InfoBase_02cc49c8 + 0x10;
    puVar17 = PTR__ZTV27CBattleEvaluationResultInfo_02cc3748 + 0x10;
    puVar18 = PTR__ZTV22CParameterPropertyBaseILj228EE_02cbf5e8 + 0x10;
    puVar19 = PTR__ZTV22CParameterPropertyBaseILj229EE_02cba790 + 0x10;
    puVar20 = PTR__ZTV22CParameterPropertyBaseILj230EE_02cc3050 + 0x10;
    do {
      pppppplStack_88 =
           (long ******)(**(code **)(*param_1 + 0x20))(param_1,*param_2 + uVar26 * 0x40);
      ppppppplVar25 = (long *******)param_1[8];
      ppppppplVar24 = ppppppplVar29;
      if ((long *******)param_1[8] == (long *******)0x0) {
code_r0x0166a43c:
        memset(auStack_348,0,0x2c0);
        uStack_330 = 0;
        uStack_328 = 0;
        uStack_310 = 0;
        uStack_318 = 0;
        puStack_358 = puVar17;
        puStack_350 = auStack_348;
        puStack_338 = &uStack_330;
        puStack_320 = puVar18;
        Framework::CHash32::CHash32()(auStack_308);
        uStack_2e0 = 0;
        uStack_2e8 = 0;
        puStack_320 = puVar2;
        puStack_2f0 = puVar19;
        Framework::CHash32::CHash32()(auStack_2d8);
        uStack_2b0 = 0;
        uStack_2b8 = 0;
        puStack_2f0 = puVar3;
        puStack_2c0 = puVar20;
        Framework::CHash32::CHash32()(auStack_2a8);
        uStack_280 = 0;
        uStack_278 = 0;
        uStack_268 = 0;
        uStack_260 = 0;
        uStack_250 = 0;
        uStack_248 = 0;
        puStack_2c0 = puVar4;
        puStack_290 = puVar5;
        puStack_288 = &uStack_280;
        puStack_270 = &uStack_268;
        puStack_258 = puVar6;
        Framework::CHash32::CHash32()(auStack_240);
        uStack_220 = 0;
        uStack_218 = 0;
        puStack_258 = puVar7;
        puStack_228 = puVar8;
        Framework::CHash32::CHash32()(auStack_210);
        uStack_1f0 = 0;
        uStack_1e8 = 0;
        puStack_228 = puVar9;
        puStack_1f8 = puVar10;
        Framework::CHash32::CHash32()(auStack_1e0);
        uStack_1b8 = 0;
        uStack_1b0 = 0;
        uStack_1a0 = 0;
        uStack_198 = 0;
        uStack_188 = 0;
        uStack_180 = 0;
        uStack_190 = 0;
        uStack_168 = 0;
        uStack_160 = 0;
        uStack_150 = 0;
        uStack_148 = 0;
        uStack_138 = 0;
        uStack_130 = 0;
        uStack_140 = 0;
        uStack_118 = 0;
        uStack_110 = 0;
        uStack_100 = 0;
        uStack_f8 = 0;
        uStack_e8 = 0;
        uStack_e0 = 0;
        uStack_f0 = 0;
        uStack_c8 = 0;
        uStack_c0 = 0;
        uStack_b0 = 0;
        uStack_a8 = 0;
        uStack_98 = 0;
        uStack_90 = 0;
        uStack_a0 = 0;
        ppppppplVar25 = (long *******)*ppppppplVar29;
        if ((long *******)*ppppppplVar29 == (long *******)0x0) {
          ppppppplVar28 = (long *******)*ppppppplVar29;
          ppppppplVar24 = ppppppplVar29;
          ppppppplVar27 = ppppppplVar29;
        }
        else {
          do {
            while (ppppppplVar24 = ppppppplVar25, ppppppplVar24[4] <= pppppplStack_88) {
              if (pppppplStack_88 <= ppppppplVar24[4]) {
                ppppppplVar28 = ppppppplVar24;
                ppppppplVar27 = (long *******)&ppppppplStack_68;
                goto joined_r0x0166a650;
              }
              ppppppplVar27 = ppppppplVar24 + 1;
              ppppppplVar25 = (long *******)*ppppppplVar27;
              if ((long *******)*ppppppplVar27 == (long *******)0x0) {
                ppppppplVar28 = (long *******)*ppppppplVar27;
                goto joined_r0x0166a650;
              }
            }
            ppppppplVar25 = (long *******)*ppppppplVar24;
          } while ((long *******)*ppppppplVar24 != (long *******)0x0);
          ppppppplVar28 = (long *******)*ppppppplVar24;
          ppppppplVar27 = ppppppplVar24;
        }
joined_r0x0166a650:
        puStack_1f8 = puVar11;
        puStack_1c8 = puVar12;
        puStack_1c0 = &uStack_1b8;
        puStack_1a8 = &uStack_1a0;
        puStack_178 = puVar13;
        puStack_170 = &uStack_168;
        puStack_158 = &uStack_150;
        puStack_128 = puVar14;
        puStack_120 = &uStack_118;
        puStack_108 = &uStack_100;
        puStack_d8 = puVar15;
        puStack_d0 = &uStack_c8;
        puStack_b8 = &uStack_b0;
        ppppppplStack_68 = ppppppplVar24;
        if (ppppppplVar28 == (long *******)0x0) {
          std::__ndk1::unique_ptr<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CBattleEvaluationResultInfo>, void*>, std::__ndk1::__tree_node_destructor<Framework::CSTLAllocator<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CBattleEvaluationResultInfo>, void*>, Framework::CSTLMapAllocatorInf> > > std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CBattleEvaluationResultInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CBattleEvaluationResultInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CBattleEvaluationResultInfo>, Framework::CSTLMapAllocatorInf> >::__construct_node<unsigned long&, CBattleEvaluationResultInfo>(unsigned long&, CBattleEvaluationResultInfo&&)(appppppplStack_80,plVar23,&pppppplStack_88,&puStack_358);
          *appppppplStack_80[0] = (long ******)0x0;
          appppppplStack_80[0][1] = (long ******)0x0;
          appppppplStack_80[0][2] = (long ******)ppppppplVar24;
          *ppppppplVar27 = (long ******)appppppplStack_80[0];
          ppppppplVar25 = appppppplStack_80[0];
          if (*(long *)*plVar23 != 0) {
            *plVar23 = *(long *)*plVar23;
            ppppppplVar25 = (long *******)*ppppppplVar27;
          }
          void std::__ndk1::__tree_balance_after_insert<std::__ndk1::__tree_node_base<void*>*>(std::__ndk1::__tree_node_base<void*>*, std::__ndk1::__tree_node_base<void*>*)(param_1[8],ppppppplVar25);
          param_1[9] = param_1[9] + 1;
          ppppppplVar28 = appppppplStack_80[0];
        }
        puStack_358 = PTR__ZTV27CBattleEvaluationResultInfo_02cc3748 + 0x10;
        CMissionResultDropInfo::~CMissionResultDropInfo()(&puStack_290);
        puStack_2c0 = PTR__ZTV22CParameterPropertyBaseILj230EE_02cc3050 + 0x10;
        Framework::CHash32::~CHash32()(auStack_2a8);
        puStack_2f0 = PTR__ZTV22CParameterPropertyBaseILj229EE_02cba790 + 0x10;
        Framework::CHash32::~CHash32()(auStack_2d8);
        puStack_320 = PTR__ZTV22CParameterPropertyBaseILj228EE_02cbf5e8 + 0x10;
        Framework::CHash32::~CHash32()(auStack_308);
        puStack_358 = puVar16;
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*)(&puStack_338,uStack_330);
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*)(&puStack_350,auStack_348[0]);
        ppppppplVar28 = ppppppplVar28 + 5;
        (*(code *)(*ppppppplVar28)[2])(ppppppplVar28);
      }
      else {
        do {
          while (ppppppplVar28 = ppppppplVar25, ppppppplVar28[4] < pppppplStack_88) {
            ppppppplVar25 = (long *******)ppppppplVar28[1];
            if ((long *******)ppppppplVar28[1] == (long *******)0x0) {
              ppppppplVar28 = ppppppplVar24;
              if (ppppppplVar24 != ppppppplVar29) goto code_r0x0166a420;
              goto code_r0x0166a43c;
            }
          }
          ppppppplVar25 = (long *******)*ppppppplVar28;
          ppppppplVar24 = ppppppplVar28;
        } while ((long *******)*ppppppplVar28 != (long *******)0x0);
        if (ppppppplVar28 == ppppppplVar29) goto code_r0x0166a43c;
code_r0x0166a420:
        if ((pppppplStack_88 < ppppppplVar28[4]) || (ppppppplVar28 == ppppppplVar29))
        goto code_r0x0166a43c;
        ppppppplVar28 = ppppppplVar28 + 5;
      }
      lVar21 = *param_2 + uVar26 * 0x40;
      iVar22 = *(int *)(lVar21 + 0x20);
      if (iVar22 == 6) {
        (*(code *)**ppppppplVar28)(ppppppplVar28,lVar21 + 0x28);
      }
      else if (iVar22 == 7) {
        (*(code *)(*ppppppplVar28)[1])(ppppppplVar28,*param_2 + uVar26 * 0x40 + 0x28);
      }
      uVar1 = (int)uVar26 + 1;
      uVar26 = (ulong)uVar1;
    } while (uVar1 < *(uint *)(param_2 + 1));
  }
  return 1;
}

// ==== IInfoBaseMap<unsigned long, CMascontInfo>::DeserializeChild(Aska::ASON::AValue::AMap const*)
// vaddr 0x156adf4 | ghidra 0x166adf4 | size 932 | symbol _ZN12IInfoBaseMapIm12CMascontInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Type propagation algorithm not settling */

undefined8
_ZN12IInfoBaseMapIm12CMascontInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE
          (long *param_1,long *param_2)

{
  uint uVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined *puVar5;
  undefined *puVar6;
  undefined *puVar7;
  long lVar8;
  int iVar9;
  long *plVar10;
  long *******ppppppplVar11;
  long *******ppppppplVar12;
  ulong uVar13;
  long *******ppppppplVar14;
  long *******ppppppplVar15;
  long *******ppppppplVar16;
  undefined *puStack_120;
  undefined8 *puStack_118;
  undefined8 auStack_110 [2];
  undefined8 *puStack_100;
  undefined8 uStack_f8;
  undefined8 uStack_f0;
  undefined *puStack_e8;
  undefined8 uStack_e0;
  undefined1 uStack_d8;
  undefined1 auStack_d0 [24];
  undefined *puStack_b8;
  undefined8 uStack_b0;
  undefined1 uStack_a8;
  undefined1 auStack_a0 [24];
  long ******pppppplStack_88;
  long *******appppppplStack_80 [3];
  long *******ppppppplStack_68;
  
  ppppppplVar16 = (long *******)(param_1 + 8);
  plVar10 = param_1 + 7;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CMascontInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CMascontInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CMascontInfo>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CMascontInfo>, void*>*)(plVar10,*ppppppplVar16);
  param_1[7] = (long)ppppppplVar16;
  param_1[8] = 0;
  param_1[9] = 0;
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0282d54e/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\Info/InfoBase.h"*/,0x1c1,&UNK_027dc58a/*"apParser is null."*/);
    iVar9 = iRam0000000000000008;
  }
  else {
    iVar9 = (int)param_2[1];
  }
  if (iVar9 != 0) {
    puVar2 = PTR__ZTV12CMascontInfo_02cb7f40 + 0x10;
    puVar3 = PTR__ZTV22CParameterPropertyBaseILj13EE_02cba498 + 0x10;
    puVar4 = PTR__ZTV23CParameterPropertyValueIjLj13E18CPropertyConverterE_02cbd818 + 0x10;
    puVar5 = PTR__ZTV22CParameterPropertyBaseILj14EE_02cb9db0 + 0x10;
    puVar6 = PTR__ZTV23CParameterPropertyValueIjLj14E18CPropertyConverterE_02cbaef8 + 0x10;
    uVar13 = 0;
    puVar7 = PTR__ZTV8InfoBase_02cc49c8 + 0x10;
    do {
      pppppplStack_88 =
           (long ******)(**(code **)(*param_1 + 0x20))(param_1,*param_2 + uVar13 * 0x40);
      ppppppplVar12 = (long *******)param_1[8];
      ppppppplVar11 = ppppppplVar16;
      if ((long *******)param_1[8] == (long *******)0x0) {
code_r0x0166af70:
        memset(auStack_110,0,0x88);
        uStack_f8 = 0;
        uStack_f0 = 0;
        uStack_d8 = 0;
        uStack_e0 = 0;
        puStack_120 = puVar2;
        puStack_118 = auStack_110;
        puStack_100 = &uStack_f8;
        puStack_e8 = puVar3;
        Framework::CHash32::CHash32()(auStack_d0);
        uStack_a8 = 0;
        uStack_b0 = 0;
        puStack_e8 = puVar4;
        puStack_b8 = puVar5;
        Framework::CHash32::CHash32()(auStack_a0);
        ppppppplVar12 = (long *******)*ppppppplVar16;
        if ((long *******)*ppppppplVar16 == (long *******)0x0) {
          ppppppplVar15 = (long *******)*ppppppplVar16;
          ppppppplVar11 = ppppppplVar16;
          ppppppplVar14 = ppppppplVar16;
        }
        else {
          do {
            while (ppppppplVar11 = ppppppplVar12, ppppppplVar11[4] <= pppppplStack_88) {
              if (pppppplStack_88 <= ppppppplVar11[4]) {
                ppppppplVar15 = ppppppplVar11;
                ppppppplVar14 = (long *******)&ppppppplStack_68;
                goto joined_r0x0166b03c;
              }
              ppppppplVar14 = ppppppplVar11 + 1;
              ppppppplVar12 = (long *******)*ppppppplVar14;
              if ((long *******)*ppppppplVar14 == (long *******)0x0) {
                ppppppplVar15 = (long *******)*ppppppplVar14;
                goto joined_r0x0166b03c;
              }
            }
            ppppppplVar12 = (long *******)*ppppppplVar11;
          } while ((long *******)*ppppppplVar11 != (long *******)0x0);
          ppppppplVar15 = (long *******)*ppppppplVar11;
          ppppppplVar14 = ppppppplVar11;
        }
joined_r0x0166b03c:
        ppppppplStack_68 = ppppppplVar11;
        if (ppppppplVar15 == (long *******)0x0) {
          puStack_b8 = puVar6;
          std::__ndk1::unique_ptr<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CMascontInfo>, void*>, std::__ndk1::__tree_node_destructor<Framework::CSTLAllocator<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CMascontInfo>, void*>, Framework::CSTLMapAllocatorInf> > > std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CMascontInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CMascontInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CMascontInfo>, Framework::CSTLMapAllocatorInf> >::__construct_node<unsigned long&, CMascontInfo>(unsigned long&, CMascontInfo&&)(appppppplStack_80,plVar10,&pppppplStack_88,&puStack_120);
          *appppppplStack_80[0] = (long ******)0x0;
          appppppplStack_80[0][1] = (long ******)0x0;
          appppppplStack_80[0][2] = (long ******)ppppppplVar11;
          *ppppppplVar14 = (long ******)appppppplStack_80[0];
          ppppppplVar12 = appppppplStack_80[0];
          if (*(long *)*plVar10 != 0) {
            *plVar10 = *(long *)*plVar10;
            ppppppplVar12 = (long *******)*ppppppplVar14;
          }
          void std::__ndk1::__tree_balance_after_insert<std::__ndk1::__tree_node_base<void*>*>(std::__ndk1::__tree_node_base<void*>*, std::__ndk1::__tree_node_base<void*>*)(param_1[8],ppppppplVar12);
          param_1[9] = param_1[9] + 1;
          ppppppplVar15 = appppppplStack_80[0];
        }
        puStack_120 = PTR__ZTV12CMascontInfo_02cb7f40 + 0x10;
        puStack_b8 = PTR__ZTV22CParameterPropertyBaseILj14EE_02cb9db0 + 0x10;
        Framework::CHash32::~CHash32()(auStack_a0);
        puStack_e8 = PTR__ZTV22CParameterPropertyBaseILj13EE_02cba498 + 0x10;
        Framework::CHash32::~CHash32()(auStack_d0);
        puStack_120 = puVar7;
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*)(&puStack_100,uStack_f8);
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*)(&puStack_118,auStack_110[0]);
        ppppppplVar15 = ppppppplVar15 + 5;
        (*(code *)(*ppppppplVar15)[2])(ppppppplVar15);
      }
      else {
        do {
          while (ppppppplVar15 = ppppppplVar12, ppppppplVar15[4] < pppppplStack_88) {
            ppppppplVar12 = (long *******)ppppppplVar15[1];
            if ((long *******)ppppppplVar15[1] == (long *******)0x0) {
              ppppppplVar15 = ppppppplVar11;
              if (ppppppplVar11 != ppppppplVar16) goto code_r0x0166af54;
              goto code_r0x0166af70;
            }
          }
          ppppppplVar12 = (long *******)*ppppppplVar15;
          ppppppplVar11 = ppppppplVar15;
        } while ((long *******)*ppppppplVar15 != (long *******)0x0);
        if (ppppppplVar15 == ppppppplVar16) goto code_r0x0166af70;
code_r0x0166af54:
        if ((pppppplStack_88 < ppppppplVar15[4]) || (ppppppplVar15 == ppppppplVar16))
        goto code_r0x0166af70;
        ppppppplVar15 = ppppppplVar15 + 5;
      }
      lVar8 = *param_2 + uVar13 * 0x40;
      iVar9 = *(int *)(lVar8 + 0x20);
      if (iVar9 == 6) {
        (*(code *)**ppppppplVar15)(ppppppplVar15,lVar8 + 0x28);
      }
      else if (iVar9 == 7) {
        (*(code *)(*ppppppplVar15)[1])(ppppppplVar15,*param_2 + uVar13 * 0x40 + 0x28);
      }
      uVar1 = (int)uVar13 + 1;
      uVar13 = (ulong)uVar1;
    } while (uVar1 < *(uint *)(param_2 + 1));
  }
  return 1;
}

// ==== IInfoBaseMap<unsigned long, CStorageItemInfo>::DeserializeChild(Aska::ASON::AValue::AMap const*)
// vaddr 0x156be28 | ghidra 0x166be28 | size 540 | symbol _ZN12IInfoBaseMapIm16CStorageItemInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN12IInfoBaseMapIm16CStorageItemInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE
          (long *param_1,long *param_2)

{
  uint uVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  int iVar5;
  long *plVar6;
  long lVar7;
  long *plVar8;
  ulong uVar9;
  long *plVar10;
  long *plVar11;
  undefined *apuStack_3c8 [102];
  undefined *puStack_98;
  undefined8 uStack_90;
  undefined1 uStack_88;
  undefined1 auStack_80 [24];
  ulong uStack_68;
  
  plVar11 = param_1 + 8;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CStorageItemInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CStorageItemInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CStorageItemInfo>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CStorageItemInfo>, void*>*)(param_1 + 7,*plVar11);
  param_1[7] = (long)plVar11;
  param_1[8] = 0;
  param_1[9] = 0;
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0282d54e/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\Info/InfoBase.h"*/,0x1c1,&UNK_027dc58a/*"apParser is null."*/);
    iVar5 = iRam0000000000000008;
  }
  else {
    iVar5 = (int)param_2[1];
  }
  if (iVar5 != 0) {
    uVar9 = 0;
    puVar2 = PTR__ZTV16CStorageItemInfo_02cc3f98 + 0x10;
    puVar3 = PTR__ZTV22CParameterPropertyBaseILj18EE_02cbe238 + 0x10;
    puVar4 = PTR__ZTV23CParameterPropertyValueImLj18E18CPropertyConverterE_02cc40e8 + 0x10;
    do {
      uStack_68 = (**(code **)(*param_1 + 0x20))(param_1,*param_2 + uVar9 * 0x40);
      plVar6 = (long *)param_1[8];
      plVar8 = plVar11;
      if ((long *)param_1[8] == (long *)0x0) {
code_r0x0166bf50:
        memset(apuStack_3c8,0,0x360);
        CItemInfo::CItemInfo()(apuStack_3c8);
        uStack_90 = 0;
        uStack_88 = 0;
        apuStack_3c8[0] = puVar2;
        puStack_98 = puVar3;
        Framework::CHash32::CHash32()(auStack_80);
        puStack_98 = puVar4;
        lVar7 = std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned long, CStorageItemInfo>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CStorageItemInfo>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CStorageItemInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CStorageItemInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CStorageItemInfo>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned long, unsigned long&, CStorageItemInfo>(unsigned long const&, unsigned long&, CStorageItemInfo&&)(param_1 + 7,&uStack_68,&uStack_68,apuStack_3c8);
        apuStack_3c8[0] = puVar2;
        puStack_98 = puVar3;
        Framework::CHash32::~CHash32()(auStack_80);
        CItemInfo::~CItemInfo()(apuStack_3c8);
        plVar10 = (long *)(lVar7 + 0x28);
        (**(code **)(*plVar10 + 0x10))(plVar10);
      }
      else {
        do {
          while (plVar10 = plVar6, (ulong)plVar10[4] < uStack_68) {
            plVar6 = (long *)plVar10[1];
            if ((long *)plVar10[1] == (long *)0x0) {
              plVar10 = plVar8;
              if (plVar8 != plVar11) goto code_r0x0166bf34;
              goto code_r0x0166bf50;
            }
          }
          plVar6 = (long *)*plVar10;
          plVar8 = plVar10;
        } while ((long *)*plVar10 != (long *)0x0);
        if (plVar10 == plVar11) goto code_r0x0166bf50;
code_r0x0166bf34:
        if ((uStack_68 < (ulong)plVar10[4]) || (plVar10 == plVar11)) goto code_r0x0166bf50;
        plVar10 = plVar10 + 5;
      }
      lVar7 = *param_2 + uVar9 * 0x40;
      iVar5 = *(int *)(lVar7 + 0x20);
      if (iVar5 == 6) {
        (**(code **)*plVar10)(plVar10,lVar7 + 0x28);
      }
      else if (iVar5 == 7) {
        (**(code **)(*plVar10 + 8))(plVar10,*param_2 + uVar9 * 0x40 + 0x28);
      }
      uVar1 = (int)uVar9 + 1;
      uVar9 = (ulong)uVar1;
    } while (uVar1 < *(uint *)(param_2 + 1));
  }
  return 1;
}

// ==== IInfoBaseMap<unsigned long, CGearInfo>::DeserializeChild(Aska::ASON::AValue::AMap const*)
// vaddr 0x156d098 | ghidra 0x166d098 | size 1324 | symbol _ZN12IInfoBaseMapIm9CGearInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Type propagation algorithm not settling */

undefined8
_ZN12IInfoBaseMapIm9CGearInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE
          (long *param_1,long *param_2)

{
  uint uVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined *puVar5;
  undefined *puVar6;
  undefined *puVar7;
  undefined *puVar8;
  undefined *puVar9;
  undefined *puVar10;
  undefined *puVar11;
  undefined *puVar12;
  undefined *puVar13;
  undefined *puVar14;
  undefined *puVar15;
  long lVar16;
  int iVar17;
  long *plVar18;
  long *******ppppppplVar19;
  long *******ppppppplVar20;
  ulong uVar21;
  long *******ppppppplVar22;
  long *******ppppppplVar23;
  long *******ppppppplVar24;
  undefined *puStack_1e0;
  undefined8 *puStack_1d8;
  undefined8 auStack_1d0 [2];
  undefined8 *puStack_1c0;
  undefined8 uStack_1b8;
  undefined8 uStack_1b0;
  undefined *puStack_1a8;
  undefined8 uStack_1a0;
  undefined1 uStack_198;
  undefined1 auStack_190 [24];
  undefined *puStack_178;
  undefined8 uStack_170;
  undefined1 uStack_168;
  undefined1 auStack_160 [24];
  undefined *puStack_148;
  undefined8 uStack_140;
  undefined1 uStack_138;
  undefined1 auStack_130 [24];
  undefined *puStack_118;
  undefined8 uStack_110;
  undefined1 uStack_108;
  undefined1 auStack_100 [24];
  undefined *puStack_e8;
  undefined8 uStack_e0;
  undefined1 uStack_d8;
  undefined1 auStack_d0 [24];
  undefined *puStack_b8;
  undefined8 uStack_b0;
  undefined1 uStack_a8;
  undefined1 auStack_a0 [24];
  long ******pppppplStack_88;
  long *******appppppplStack_80 [3];
  long *******ppppppplStack_68;
  
  ppppppplVar23 = (long *******)(param_1 + 8);
  plVar18 = param_1 + 7;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CGearInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CGearInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CGearInfo>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CGearInfo>, void*>*)(plVar18,*ppppppplVar23);
  param_1[7] = (long)ppppppplVar23;
  param_1[8] = 0;
  param_1[9] = 0;
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0282d54e/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\Info/InfoBase.h"*/,0x1c1,&UNK_027dc58a/*"apParser is null."*/);
    iVar17 = iRam0000000000000008;
  }
  else {
    iVar17 = (int)param_2[1];
  }
  if (iVar17 != 0) {
    puVar2 = PTR__ZTV9CGearInfo_02cbd798 + 0x10;
    puVar3 = PTR__ZTV22CParameterPropertyBaseILj16EE_02cb9c20 + 0x10;
    puVar4 = PTR__ZTV23CParameterPropertyValueIbLj16E18CPropertyConverterE_02cc0000 + 0x10;
    puVar5 = PTR__ZTV22CParameterPropertyBaseILj20EE_02cc0d08 + 0x10;
    puVar6 = PTR__ZTV23CParameterPropertyValueIjLj20E18CPropertyConverterE_02cc2ce0 + 0x10;
    puVar7 = PTR__ZTV22CParameterPropertyBaseILj21EE_02cc1310 + 0x10;
    puVar8 = PTR__ZTV23CParameterPropertyValueIjLj21E18CPropertyConverterE_02cbeae0 + 0x10;
    puVar9 = PTR__ZTV22CParameterPropertyBaseILj22EE_02cc4630 + 0x10;
    puVar10 = PTR__ZTV23CParameterPropertyValueImLj22E18CPropertyConverterE_02cb9830 + 0x10;
    puVar11 = PTR__ZTV22CParameterPropertyBaseILj23EE_02cbad98 + 0x10;
    puVar12 = PTR__ZTV23CParameterPropertyValueIjLj23E18CPropertyConverterE_02cb7d90 + 0x10;
    puVar13 = PTR__ZTV23CParameterPropertyValueIbLj24E18CPropertyConverterE_02cc3b80 + 0x10;
    puVar14 = PTR__ZTV8InfoBase_02cc49c8 + 0x10;
    uVar21 = 0;
    puVar15 = PTR__ZTV22CParameterPropertyBaseILj24EE_02cbdf68 + 0x10;
    do {
      pppppplStack_88 =
           (long ******)(**(code **)(*param_1 + 0x20))(param_1,*param_2 + uVar21 * 0x40);
      ppppppplVar20 = (long *******)param_1[8];
      ppppppplVar19 = ppppppplVar23;
      if ((long *******)param_1[8] == (long *******)0x0) {
code_r0x0166d2b8:
        memset(auStack_1d0,0,0x148);
        uStack_1b8 = 0;
        uStack_1b0 = 0;
        uStack_198 = 0;
        uStack_1a0 = 0;
        puStack_1e0 = puVar2;
        puStack_1d8 = auStack_1d0;
        puStack_1c0 = &uStack_1b8;
        puStack_1a8 = puVar3;
        Framework::CHash32::CHash32()(auStack_190);
        uStack_168 = 0;
        uStack_170 = 0;
        puStack_1a8 = puVar4;
        puStack_178 = puVar5;
        Framework::CHash32::CHash32()(auStack_160);
        uStack_138 = 0;
        uStack_140 = 0;
        puStack_178 = puVar6;
        puStack_148 = puVar7;
        Framework::CHash32::CHash32()(auStack_130);
        uStack_108 = 0;
        uStack_110 = 0;
        puStack_148 = puVar8;
        puStack_118 = puVar9;
        Framework::CHash32::CHash32()(auStack_100);
        uStack_d8 = 0;
        uStack_e0 = 0;
        puStack_118 = puVar10;
        puStack_e8 = puVar11;
        Framework::CHash32::CHash32()(auStack_d0);
        uStack_a8 = 0;
        uStack_b0 = 0;
        puStack_e8 = puVar12;
        puStack_b8 = puVar15;
        Framework::CHash32::CHash32()(auStack_a0);
        ppppppplVar20 = (long *******)*ppppppplVar23;
        if ((long *******)*ppppppplVar23 == (long *******)0x0) {
          ppppppplVar22 = (long *******)*ppppppplVar23;
          ppppppplVar19 = ppppppplVar23;
          ppppppplVar24 = ppppppplVar23;
        }
        else {
          do {
            while (ppppppplVar19 = ppppppplVar20, ppppppplVar19[4] <= pppppplStack_88) {
              if (pppppplStack_88 <= ppppppplVar19[4]) {
                ppppppplVar22 = ppppppplVar19;
                ppppppplVar24 = (long *******)&ppppppplStack_68;
                goto joined_r0x0166d400;
              }
              ppppppplVar24 = ppppppplVar19 + 1;
              ppppppplVar20 = (long *******)*ppppppplVar24;
              if ((long *******)*ppppppplVar24 == (long *******)0x0) {
                ppppppplVar22 = (long *******)*ppppppplVar24;
                goto joined_r0x0166d400;
              }
            }
            ppppppplVar20 = (long *******)*ppppppplVar19;
          } while ((long *******)*ppppppplVar19 != (long *******)0x0);
          ppppppplVar22 = (long *******)*ppppppplVar19;
          ppppppplVar24 = ppppppplVar19;
        }
joined_r0x0166d400:
        ppppppplStack_68 = ppppppplVar19;
        if (ppppppplVar22 == (long *******)0x0) {
          puStack_b8 = puVar13;
          std::__ndk1::unique_ptr<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CGearInfo>, void*>, std::__ndk1::__tree_node_destructor<Framework::CSTLAllocator<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CGearInfo>, void*>, Framework::CSTLMapAllocatorInf> > > std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CGearInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CGearInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CGearInfo>, Framework::CSTLMapAllocatorInf> >::__construct_node<unsigned long&, CGearInfo>(unsigned long&, CGearInfo&&)(appppppplStack_80,plVar18,&pppppplStack_88,&puStack_1e0);
          *appppppplStack_80[0] = (long ******)0x0;
          appppppplStack_80[0][1] = (long ******)0x0;
          appppppplStack_80[0][2] = (long ******)ppppppplVar19;
          *ppppppplVar24 = (long ******)appppppplStack_80[0];
          ppppppplVar20 = appppppplStack_80[0];
          if (*(long *)*plVar18 != 0) {
            *plVar18 = *(long *)*plVar18;
            ppppppplVar20 = (long *******)*ppppppplVar24;
          }
          void std::__ndk1::__tree_balance_after_insert<std::__ndk1::__tree_node_base<void*>*>(std::__ndk1::__tree_node_base<void*>*, std::__ndk1::__tree_node_base<void*>*)(param_1[8],ppppppplVar20);
          param_1[9] = param_1[9] + 1;
          ppppppplVar22 = appppppplStack_80[0];
        }
        puStack_1e0 = PTR__ZTV9CGearInfo_02cbd798 + 0x10;
        puStack_b8 = PTR__ZTV22CParameterPropertyBaseILj24EE_02cbdf68 + 0x10;
        Framework::CHash32::~CHash32()(auStack_a0);
        puStack_e8 = PTR__ZTV22CParameterPropertyBaseILj23EE_02cbad98 + 0x10;
        Framework::CHash32::~CHash32()(auStack_d0);
        puStack_118 = PTR__ZTV22CParameterPropertyBaseILj22EE_02cc4630 + 0x10;
        Framework::CHash32::~CHash32()(auStack_100);
        puStack_148 = PTR__ZTV22CParameterPropertyBaseILj21EE_02cc1310 + 0x10;
        Framework::CHash32::~CHash32()(auStack_130);
        puStack_178 = PTR__ZTV22CParameterPropertyBaseILj20EE_02cc0d08 + 0x10;
        Framework::CHash32::~CHash32()(auStack_160);
        puStack_1a8 = PTR__ZTV22CParameterPropertyBaseILj16EE_02cb9c20 + 0x10;
        Framework::CHash32::~CHash32()(auStack_190);
        puStack_1e0 = puVar14;
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*)(&puStack_1c0,uStack_1b8);
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*)(&puStack_1d8,auStack_1d0[0]);
        ppppppplVar22 = ppppppplVar22 + 5;
        (*(code *)(*ppppppplVar22)[2])(ppppppplVar22);
      }
      else {
        do {
          while (ppppppplVar22 = ppppppplVar20, ppppppplVar22[4] < pppppplStack_88) {
            ppppppplVar20 = (long *******)ppppppplVar22[1];
            if ((long *******)ppppppplVar22[1] == (long *******)0x0) {
              ppppppplVar22 = ppppppplVar19;
              if (ppppppplVar19 != ppppppplVar23) goto code_r0x0166d29c;
              goto code_r0x0166d2b8;
            }
          }
          ppppppplVar20 = (long *******)*ppppppplVar22;
          ppppppplVar19 = ppppppplVar22;
        } while ((long *******)*ppppppplVar22 != (long *******)0x0);
        if (ppppppplVar22 == ppppppplVar23) goto code_r0x0166d2b8;
code_r0x0166d29c:
        if ((pppppplStack_88 < ppppppplVar22[4]) || (ppppppplVar22 == ppppppplVar23))
        goto code_r0x0166d2b8;
        ppppppplVar22 = ppppppplVar22 + 5;
      }
      lVar16 = *param_2 + uVar21 * 0x40;
      iVar17 = *(int *)(lVar16 + 0x20);
      if (iVar17 == 6) {
        (*(code *)**ppppppplVar22)(ppppppplVar22,lVar16 + 0x28);
      }
      else if (iVar17 == 7) {
        (*(code *)(*ppppppplVar22)[1])(ppppppplVar22,*param_2 + uVar21 * 0x40 + 0x28);
      }
      uVar1 = (int)uVar21 + 1;
      uVar21 = (ulong)uVar1;
    } while (uVar1 < *(uint *)(param_2 + 1));
  }
  return 1;
}

// ==== IInfoBaseMap<unsigned long, CFooterBadgeInfoList>::DeserializeChild(Aska::ASON::AValue::AMap const*)
// vaddr 0x1570dcc | ghidra 0x1670dcc | size 584 | symbol _ZN12IInfoBaseMapIm20CFooterBadgeInfoListE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN12IInfoBaseMapIm20CFooterBadgeInfoListE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE
          (long *param_1,long *param_2)

{
  uint uVar1;
  undefined *puVar2;
  undefined *puVar3;
  long lVar4;
  int iVar5;
  long *plVar6;
  long lVar7;
  long *plVar8;
  ulong uVar9;
  long *plVar10;
  long *plVar11;
  undefined *puStack_b8;
  undefined8 *puStack_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined8 *puStack_98;
  undefined8 uStack_90;
  undefined8 uStack_88;
  long lStack_80;
  long lStack_78;
  undefined8 uStack_70;
  ulong uStack_68;
  
  plVar11 = param_1 + 8;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CFooterBadgeInfoList>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CFooterBadgeInfoList>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CFooterBadgeInfoList>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CFooterBadgeInfoList>, void*>*)(param_1 + 7,*plVar11);
  param_1[7] = (long)plVar11;
  param_1[8] = 0;
  param_1[9] = 0;
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0282d54e/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\Info/InfoBase.h"*/,0x1c1,&UNK_027dc58a/*"apParser is null."*/);
    iVar5 = iRam0000000000000008;
  }
  else {
    iVar5 = (int)param_2[1];
  }
  if (iVar5 != 0) {
    uVar9 = 0;
    puVar2 = PTR__ZTV20CFooterBadgeInfoList_02cbd5e0 + 0x10;
    puVar3 = PTR__ZTV8InfoBase_02cc49c8 + 0x10;
    do {
      uStack_68 = (**(code **)(*param_1 + 0x20))(param_1,*param_2 + uVar9 * 0x40);
      plVar6 = (long *)param_1[8];
      plVar8 = plVar11;
      if ((long *)param_1[8] == (long *)0x0) {
code_r0x01670efc:
        uStack_a8 = 0;
        uStack_a0 = 0;
        uStack_90 = 0;
        uStack_88 = 0;
        lStack_78 = 0;
        uStack_70 = 0;
        lStack_80 = 0;
        puStack_b8 = puVar2;
        puStack_b0 = &uStack_a8;
        puStack_98 = &uStack_90;
        lVar7 = std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned long, CFooterBadgeInfoList>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CFooterBadgeInfoList>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CFooterBadgeInfoList>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CFooterBadgeInfoList>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CFooterBadgeInfoList>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned long, unsigned long&, CFooterBadgeInfoList>(unsigned long const&, unsigned long&, CFooterBadgeInfoList&&)(param_1 + 7,&uStack_68,&uStack_68,&puStack_b8);
        lVar4 = lStack_80;
        if (lStack_80 != 0) {
          while (lStack_78 != lVar4) {
            lStack_78 = lStack_78 + -0x148;
            CFooterBadgeInfo::~CFooterBadgeInfo()();
          }
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(lStack_80);
        }
        puStack_b8 = puVar3;
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*)(&puStack_98,uStack_90);
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*)(&puStack_b0,uStack_a8);
        plVar10 = (long *)(lVar7 + 0x28);
        (**(code **)(*plVar10 + 0x10))(plVar10);
      }
      else {
        do {
          while (plVar10 = plVar6, uStack_68 <= (ulong)plVar10[4]) {
            plVar6 = (long *)*plVar10;
            plVar8 = plVar10;
            if ((long *)*plVar10 == (long *)0x0) {
              if (plVar10 != plVar11) goto code_r0x01670ee0;
              goto code_r0x01670efc;
            }
          }
          plVar6 = (long *)plVar10[1];
        } while ((long *)plVar10[1] != (long *)0x0);
        plVar10 = plVar8;
        if (plVar8 == plVar11) goto code_r0x01670efc;
code_r0x01670ee0:
        if ((uStack_68 < (ulong)plVar10[4]) || (plVar10 == plVar11)) goto code_r0x01670efc;
        plVar10 = plVar10 + 5;
      }
      lVar4 = *param_2 + uVar9 * 0x40;
      iVar5 = *(int *)(lVar4 + 0x20);
      if (iVar5 == 6) {
        (**(code **)*plVar10)(plVar10,lVar4 + 0x28);
      }
      else if (iVar5 == 7) {
        (**(code **)(*plVar10 + 8))(plVar10,*param_2 + uVar9 * 0x40 + 0x28);
      }
      uVar1 = (int)uVar9 + 1;
      uVar9 = (ulong)uVar1;
    } while (uVar1 < *(uint *)(param_2 + 1));
  }
  return 1;
}

// ==== IInfoBaseMap<unsigned long, CPlayerCharacterMasteryInfo>::DeserializeChild(Aska::ASON::AValue::AMap const*)
// vaddr 0x15720c0 | ghidra 0x16720c0 | size 436 | symbol _ZN12IInfoBaseMapIm27CPlayerCharacterMasteryInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN12IInfoBaseMapIm27CPlayerCharacterMasteryInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE
          (long *param_1,long *param_2)

{
  uint uVar1;
  int iVar2;
  long *plVar3;
  long lVar4;
  long *plVar5;
  ulong uVar6;
  long *plVar7;
  long *plVar8;
  undefined1 auStack_2e0 [664];
  ulong uStack_48;
  
  plVar8 = param_1 + 8;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CPlayerCharacterMasteryInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CPlayerCharacterMasteryInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CPlayerCharacterMasteryInfo>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CPlayerCharacterMasteryInfo>, void*>*)(param_1 + 7,*plVar8);
  param_1[7] = (long)plVar8;
  param_1[8] = 0;
  param_1[9] = 0;
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0282d54e/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\Info/InfoBase.h"*/,0x1c1,&UNK_027dc58a/*"apParser is null."*/);
    iVar2 = iRam0000000000000008;
  }
  else {
    iVar2 = (int)param_2[1];
  }
  if (iVar2 != 0) {
    uVar6 = 0;
    do {
      uStack_48 = (**(code **)(*param_1 + 0x20))(param_1,*param_2 + uVar6 * 0x40);
      plVar3 = (long *)param_1[8];
      plVar5 = plVar8;
      if ((long *)param_1[8] == (long *)0x0) {
code_r0x016721b4:
        memset(auStack_2e0,0,0x298);
        CPlayerCharacterMasteryInfo::CPlayerCharacterMasteryInfo()(auStack_2e0);
        lVar4 = std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned long, CPlayerCharacterMasteryInfo>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CPlayerCharacterMasteryInfo>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CPlayerCharacterMasteryInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CPlayerCharacterMasteryInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CPlayerCharacterMasteryInfo>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned long, unsigned long&, CPlayerCharacterMasteryInfo>(unsigned long const&, unsigned long&, CPlayerCharacterMasteryInfo&&)(param_1 + 7,&uStack_48,&uStack_48,auStack_2e0);
        CPlayerCharacterMasteryInfo::~CPlayerCharacterMasteryInfo()(auStack_2e0);
        plVar7 = (long *)(lVar4 + 0x28);
        (**(code **)(*plVar7 + 0x10))(plVar7);
      }
      else {
        do {
          while (plVar7 = plVar3, (ulong)plVar7[4] < uStack_48) {
            plVar3 = (long *)plVar7[1];
            if ((long *)plVar7[1] == (long *)0x0) {
              plVar7 = plVar5;
              if (plVar5 != plVar8) goto code_r0x01672198;
              goto code_r0x016721b4;
            }
          }
          plVar3 = (long *)*plVar7;
          plVar5 = plVar7;
        } while ((long *)*plVar7 != (long *)0x0);
        if (plVar7 == plVar8) goto code_r0x016721b4;
code_r0x01672198:
        if ((uStack_48 < (ulong)plVar7[4]) || (plVar7 == plVar8)) goto code_r0x016721b4;
        plVar7 = plVar7 + 5;
      }
      lVar4 = *param_2 + uVar6 * 0x40;
      iVar2 = *(int *)(lVar4 + 0x20);
      if (iVar2 == 6) {
        (**(code **)*plVar7)(plVar7,lVar4 + 0x28);
      }
      else if (iVar2 == 7) {
        (**(code **)(*plVar7 + 8))(plVar7,*param_2 + uVar6 * 0x40 + 0x28);
      }
      uVar1 = (int)uVar6 + 1;
      uVar6 = (ulong)uVar1;
    } while (uVar1 < *(uint *)(param_2 + 1));
  }
  return 1;
}

// ==== IInfoBaseMap<unsigned long, SubscriptionPlanInfo>::DeserializeChild(Aska::ASON::AValue::AMap const*)
// vaddr 0x157367c | ghidra 0x167367c | size 1000 | symbol _ZN12IInfoBaseMapIm20SubscriptionPlanInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Type propagation algorithm not settling */

undefined8
_ZN12IInfoBaseMapIm20SubscriptionPlanInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE
          (long *param_1,long *param_2)

{
  uint uVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined *puVar5;
  undefined *puVar6;
  undefined *puVar7;
  undefined *puVar8;
  undefined *puVar9;
  undefined *puVar10;
  long lVar11;
  int iVar12;
  long *plVar13;
  long *******ppppppplVar14;
  long *******ppppppplVar15;
  ulong uVar16;
  long *******ppppppplVar17;
  long *******ppppppplVar18;
  long *******ppppppplVar19;
  undefined *puStack_1b0;
  undefined1 *puStack_1a8;
  undefined1 auStack_1a0 [16];
  undefined8 *puStack_190;
  undefined8 uStack_188;
  undefined8 uStack_180;
  undefined *puStack_178;
  undefined8 uStack_170;
  undefined1 uStack_168;
  undefined1 auStack_160 [24];
  undefined *puStack_148;
  undefined8 uStack_140;
  undefined1 uStack_138;
  undefined1 auStack_130 [16];
  undefined8 uStack_120;
  undefined8 uStack_118;
  undefined8 uStack_110;
  undefined *puStack_108;
  undefined8 uStack_100;
  undefined1 uStack_f8;
  undefined1 auStack_f0 [16];
  undefined8 uStack_e0;
  undefined8 uStack_d8;
  undefined8 uStack_d0;
  undefined *puStack_c8;
  undefined8 uStack_c0;
  undefined1 uStack_b8;
  undefined1 auStack_b0 [16];
  undefined8 uStack_a0;
  undefined8 uStack_98;
  undefined8 uStack_90;
  long ******pppppplStack_88;
  long *******appppppplStack_80 [3];
  long *******ppppppplStack_68;
  
  ppppppplVar19 = (long *******)(param_1 + 8);
  plVar13 = param_1 + 7;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, SubscriptionPlanInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, SubscriptionPlanInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, SubscriptionPlanInfo>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, SubscriptionPlanInfo>, void*>*)(plVar13,*ppppppplVar19);
  param_1[7] = (long)ppppppplVar19;
  param_1[8] = 0;
  param_1[9] = 0;
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0282d54e/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\Info/InfoBase.h"*/,0x1c1,&UNK_027dc58a/*"apParser is null."*/);
    iVar12 = iRam0000000000000008;
  }
  else {
    iVar12 = (int)param_2[1];
  }
  if (iVar12 != 0) {
    puVar2 = PTR__ZTV20SubscriptionPlanInfo_02cbf078 + 0x10;
    puVar3 = PTR__ZTV22CParameterPropertyBaseILj46EE_02cc4ed0 + 0x10;
    puVar4 = PTR__ZTV23CParameterPropertyValueIjLj46E18CPropertyConverterE_02cbb308 + 0x10;
    puVar5 = PTR__ZTV22CParameterPropertyBaseILj47EE_02cba780 + 0x10;
    puVar6 = PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj47EE_02cb85d0
             + 0x10;
    puVar7 = PTR__ZTV22CParameterPropertyBaseILj48EE_02cba0d0 + 0x10;
    puVar8 = PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj48EE_02cbbdb0
             + 0x10;
    puVar9 = PTR__ZTV22CParameterPropertyBaseILj49EE_02cc4550 + 0x10;
    uVar16 = 0;
    puVar10 = PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj49EE_02cc3420
              + 0x10;
    do {
      pppppplStack_88 =
           (long ******)(**(code **)(*param_1 + 0x20))(param_1,*param_2 + uVar16 * 0x40);
      ppppppplVar15 = (long *******)param_1[8];
      ppppppplVar14 = ppppppplVar19;
      if ((long *******)param_1[8] == (long *******)0x0) {
code_r0x01673840:
        memset(auStack_1a0,0,0x118);
        uStack_188 = 0;
        uStack_180 = 0;
        uStack_168 = 0;
        uStack_170 = 0;
        puStack_1b0 = puVar2;
        puStack_1a8 = auStack_1a0;
        puStack_190 = &uStack_188;
        puStack_178 = puVar3;
        Framework::CHash32::CHash32()(auStack_160);
        uStack_138 = 0;
        uStack_140 = 0;
        puStack_178 = puVar4;
        puStack_148 = puVar5;
        Framework::CHash32::CHash32()(auStack_130);
        uStack_118 = 0;
        uStack_110 = 0;
        uStack_120 = 0;
        uStack_f8 = 0;
        uStack_100 = 0;
        puStack_148 = puVar6;
        puStack_108 = puVar7;
        Framework::CHash32::CHash32()(auStack_f0);
        uStack_d8 = 0;
        uStack_d0 = 0;
        uStack_e0 = 0;
        uStack_b8 = 0;
        uStack_c0 = 0;
        puStack_108 = puVar8;
        puStack_c8 = puVar9;
        Framework::CHash32::CHash32()(auStack_b0);
        uStack_98 = 0;
        uStack_90 = 0;
        uStack_a0 = 0;
        ppppppplVar15 = (long *******)*ppppppplVar19;
        if ((long *******)*ppppppplVar19 == (long *******)0x0) {
          ppppppplVar18 = (long *******)*ppppppplVar19;
          ppppppplVar14 = ppppppplVar19;
          ppppppplVar17 = ppppppplVar19;
        }
        else {
          do {
            while (ppppppplVar14 = ppppppplVar15, ppppppplVar14[4] <= pppppplStack_88) {
              if (pppppplStack_88 <= ppppppplVar14[4]) {
                ppppppplVar18 = ppppppplVar14;
                ppppppplVar17 = (long *******)&ppppppplStack_68;
                goto joined_r0x01673960;
              }
              ppppppplVar17 = ppppppplVar14 + 1;
              ppppppplVar15 = (long *******)*ppppppplVar17;
              if ((long *******)*ppppppplVar17 == (long *******)0x0) {
                ppppppplVar18 = (long *******)*ppppppplVar17;
                goto joined_r0x01673960;
              }
            }
            ppppppplVar15 = (long *******)*ppppppplVar14;
          } while ((long *******)*ppppppplVar14 != (long *******)0x0);
          ppppppplVar18 = (long *******)*ppppppplVar14;
          ppppppplVar17 = ppppppplVar14;
        }
joined_r0x01673960:
        puStack_c8 = puVar10;
        ppppppplStack_68 = ppppppplVar14;
        if (ppppppplVar18 == (long *******)0x0) {
          std::__ndk1::unique_ptr<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, SubscriptionPlanInfo>, void*>, std::__ndk1::__tree_node_destructor<Framework::CSTLAllocator<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, SubscriptionPlanInfo>, void*>, Framework::CSTLMapAllocatorInf> > > std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, SubscriptionPlanInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, SubscriptionPlanInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, SubscriptionPlanInfo>, Framework::CSTLMapAllocatorInf> >::__construct_node<unsigned long&, SubscriptionPlanInfo>(unsigned long&, SubscriptionPlanInfo&&)(appppppplStack_80,plVar13,&pppppplStack_88,&puStack_1b0);
          *appppppplStack_80[0] = (long ******)0x0;
          appppppplStack_80[0][1] = (long ******)0x0;
          appppppplStack_80[0][2] = (long ******)ppppppplVar14;
          *ppppppplVar17 = (long ******)appppppplStack_80[0];
          ppppppplVar15 = appppppplStack_80[0];
          if (*(long *)*plVar13 != 0) {
            *plVar13 = *(long *)*plVar13;
            ppppppplVar15 = (long *******)*ppppppplVar17;
          }
          void std::__ndk1::__tree_balance_after_insert<std::__ndk1::__tree_node_base<void*>*>(std::__ndk1::__tree_node_base<void*>*, std::__ndk1::__tree_node_base<void*>*)(param_1[8],ppppppplVar15);
          param_1[9] = param_1[9] + 1;
          ppppppplVar18 = appppppplStack_80[0];
        }
        SubscriptionPlanInfo::~SubscriptionPlanInfo()(&puStack_1b0);
        ppppppplVar18 = ppppppplVar18 + 5;
        (*(code *)(*ppppppplVar18)[2])(ppppppplVar18);
      }
      else {
        do {
          while (ppppppplVar18 = ppppppplVar15, ppppppplVar18[4] < pppppplStack_88) {
            ppppppplVar15 = (long *******)ppppppplVar18[1];
            if ((long *******)ppppppplVar18[1] == (long *******)0x0) {
              ppppppplVar18 = ppppppplVar14;
              if (ppppppplVar14 != ppppppplVar19) goto code_r0x01673824;
              goto code_r0x01673840;
            }
          }
          ppppppplVar15 = (long *******)*ppppppplVar18;
          ppppppplVar14 = ppppppplVar18;
        } while ((long *******)*ppppppplVar18 != (long *******)0x0);
        if (ppppppplVar18 == ppppppplVar19) goto code_r0x01673840;
code_r0x01673824:
        if ((pppppplStack_88 < ppppppplVar18[4]) || (ppppppplVar18 == ppppppplVar19))
        goto code_r0x01673840;
        ppppppplVar18 = ppppppplVar18 + 5;
      }
      lVar11 = *param_2 + uVar16 * 0x40;
      iVar12 = *(int *)(lVar11 + 0x20);
      if (iVar12 == 6) {
        (*(code *)**ppppppplVar18)(ppppppplVar18,lVar11 + 0x28);
      }
      else if (iVar12 == 7) {
        (*(code *)(*ppppppplVar18)[1])(ppppppplVar18,*param_2 + uVar16 * 0x40 + 0x28);
      }
      uVar1 = (int)uVar16 + 1;
      uVar16 = (ulong)uVar1;
    } while (uVar1 < *(uint *)(param_2 + 1));
  }
  return 1;
}

// ==== IInfoBaseMap<unsigned long, SubscriptionInfo>::DeserializeChild(Aska::ASON::AValue::AMap const*)
// vaddr 0x15741f8 | ghidra 0x16741f8 | size 1172 | symbol _ZN12IInfoBaseMapIm16SubscriptionInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Type propagation algorithm not settling */

undefined8
_ZN12IInfoBaseMapIm16SubscriptionInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE
          (long *param_1,long *param_2)

{
  uint uVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined *puVar5;
  undefined *puVar6;
  undefined *puVar7;
  undefined *puVar8;
  undefined *puVar9;
  long lVar10;
  int iVar11;
  long *plVar12;
  long *******ppppppplVar13;
  long *******ppppppplVar14;
  ulong uVar15;
  long *******ppppppplVar16;
  long *******ppppppplVar17;
  long *******ppppppplVar18;
  undefined *puStack_170;
  undefined8 *puStack_168;
  undefined8 auStack_160 [2];
  undefined8 *puStack_150;
  undefined8 uStack_148;
  undefined8 uStack_140;
  undefined *puStack_138;
  undefined8 uStack_130;
  undefined1 uStack_128;
  undefined1 auStack_120 [24];
  undefined *puStack_108;
  undefined8 uStack_100;
  undefined1 uStack_f8;
  undefined1 auStack_f0 [16];
  ulong uStack_e0;
  undefined8 uStack_d8;
  undefined8 uStack_d0;
  undefined *puStack_c8;
  undefined8 uStack_c0;
  undefined1 uStack_b8;
  undefined1 auStack_b0 [16];
  ulong uStack_a0;
  undefined8 uStack_98;
  undefined8 uStack_90;
  long ******pppppplStack_88;
  long *******appppppplStack_80 [3];
  long *******ppppppplStack_68;
  
  ppppppplVar18 = (long *******)(param_1 + 8);
  plVar12 = param_1 + 7;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, SubscriptionInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, SubscriptionInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, SubscriptionInfo>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, SubscriptionInfo>, void*>*)(plVar12,*ppppppplVar18);
  param_1[7] = (long)ppppppplVar18;
  param_1[8] = 0;
  param_1[9] = 0;
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0282d54e/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\Info/InfoBase.h"*/,0x1c1,&UNK_027dc58a/*"apParser is null."*/);
    iVar11 = iRam0000000000000008;
  }
  else {
    iVar11 = (int)param_2[1];
  }
  if (iVar11 != 0) {
    puVar2 = PTR__ZTV16SubscriptionInfo_02cb9878 + 0x10;
    puVar3 = PTR__ZTV22CParameterPropertyBaseILj18EE_02cbe238 + 0x10;
    puVar4 = PTR__ZTV23CParameterPropertyValueIjLj18E18CPropertyConverterE_02cbcd58 + 0x10;
    puVar5 = PTR__ZTV22CParameterPropertyBaseILj19EE_02cc4c98 + 0x10;
    puVar6 = PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj19EE_02cbf9d0
             + 0x10;
    puVar7 = PTR__ZTV22CParameterPropertyBaseILj20EE_02cc0d08 + 0x10;
    puVar8 = PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj20EE_02cba938
             + 0x10;
    uVar15 = 0;
    puVar9 = PTR__ZTV8InfoBase_02cc49c8 + 0x10;
    do {
      pppppplStack_88 =
           (long ******)(**(code **)(*param_1 + 0x20))(param_1,*param_2 + uVar15 * 0x40);
      ppppppplVar14 = (long *******)param_1[8];
      ppppppplVar13 = ppppppplVar18;
      if ((long *******)param_1[8] == (long *******)0x0) {
code_r0x016743b0:
        memset(auStack_160,0,0xd8);
        uStack_148 = 0;
        uStack_140 = 0;
        uStack_128 = 0;
        uStack_130 = 0;
        puStack_170 = puVar2;
        puStack_168 = auStack_160;
        puStack_150 = &uStack_148;
        puStack_138 = puVar3;
        Framework::CHash32::CHash32()(auStack_120);
        uStack_f8 = 0;
        uStack_100 = 0;
        puStack_138 = puVar4;
        puStack_108 = puVar5;
        Framework::CHash32::CHash32()(auStack_f0);
        uStack_d8 = 0;
        uStack_d0 = 0;
        uStack_e0 = 0;
        uStack_b8 = 0;
        uStack_c0 = 0;
        puStack_108 = puVar6;
        puStack_c8 = puVar7;
        Framework::CHash32::CHash32()(auStack_b0);
        uStack_98 = 0;
        uStack_90 = 0;
        uStack_a0 = 0;
        ppppppplVar14 = (long *******)*ppppppplVar18;
        if ((long *******)*ppppppplVar18 == (long *******)0x0) {
          ppppppplVar17 = (long *******)*ppppppplVar18;
          ppppppplVar13 = ppppppplVar18;
          ppppppplVar16 = ppppppplVar18;
        }
        else {
          do {
            while (ppppppplVar13 = ppppppplVar14, ppppppplVar13[4] <= pppppplStack_88) {
              if (pppppplStack_88 <= ppppppplVar13[4]) {
                ppppppplVar16 = (long *******)&ppppppplStack_68;
                ppppppplVar17 = ppppppplVar13;
                goto joined_r0x016744e8;
              }
              ppppppplVar16 = ppppppplVar13 + 1;
              ppppppplVar14 = (long *******)*ppppppplVar16;
              if ((long *******)*ppppppplVar16 == (long *******)0x0) {
                ppppppplVar17 = (long *******)*ppppppplVar16;
                goto joined_r0x016744e8;
              }
            }
            ppppppplVar14 = (long *******)*ppppppplVar13;
          } while ((long *******)*ppppppplVar13 != (long *******)0x0);
          ppppppplVar17 = (long *******)*ppppppplVar13;
          ppppppplVar16 = ppppppplVar13;
        }
joined_r0x016744e8:
        ppppppplStack_68 = ppppppplVar13;
        if (ppppppplVar17 == (long *******)0x0) {
          puStack_c8 = puVar8;
          std::__ndk1::unique_ptr<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, SubscriptionInfo>, void*>, std::__ndk1::__tree_node_destructor<Framework::CSTLAllocator<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, SubscriptionInfo>, void*>, Framework::CSTLMapAllocatorInf> > > std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, SubscriptionInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, SubscriptionInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, SubscriptionInfo>, Framework::CSTLMapAllocatorInf> >::__construct_node<unsigned long&, SubscriptionInfo>(unsigned long&, SubscriptionInfo&&)(appppppplStack_80,plVar12,&pppppplStack_88,&puStack_170);
          *appppppplStack_80[0] = (long ******)0x0;
          appppppplStack_80[0][1] = (long ******)0x0;
          appppppplStack_80[0][2] = (long ******)ppppppplVar13;
          *ppppppplVar16 = (long ******)appppppplStack_80[0];
          ppppppplVar14 = appppppplStack_80[0];
          if (*(long *)*plVar12 != 0) {
            *plVar12 = *(long *)*plVar12;
            ppppppplVar14 = (long *******)*ppppppplVar16;
          }
          void std::__ndk1::__tree_balance_after_insert<std::__ndk1::__tree_node_base<void*>*>(std::__ndk1::__tree_node_base<void*>*, std::__ndk1::__tree_node_base<void*>*)(param_1[8],ppppppplVar14);
          ppppppplVar17 = appppppplStack_80[0];
          param_1[9] = param_1[9] + 1;
          puStack_170 = PTR__ZTV16SubscriptionInfo_02cb9878 + 0x10;
          puStack_c8 = PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj20EE_02cba938
                       + 0x10;
          if ((uStack_a0 & 1) != 0) {
            Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_90);
          }
        }
        else {
          puStack_170 = PTR__ZTV16SubscriptionInfo_02cb9878 + 0x10;
        }
        puStack_c8 = PTR__ZTV22CParameterPropertyBaseILj20EE_02cc0d08 + 0x10;
        Framework::CHash32::~CHash32()(auStack_b0);
        puStack_108 = PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj19EE_02cbf9d0
                      + 0x10;
        if ((uStack_e0 & 1) != 0) {
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_d0);
        }
        puStack_108 = PTR__ZTV22CParameterPropertyBaseILj19EE_02cc4c98 + 0x10;
        Framework::CHash32::~CHash32()(auStack_f0);
        puStack_138 = PTR__ZTV22CParameterPropertyBaseILj18EE_02cbe238 + 0x10;
        Framework::CHash32::~CHash32()(auStack_120);
        puStack_170 = puVar9;
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*)(&puStack_150,uStack_148);
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*)(&puStack_168,auStack_160[0]);
        ppppppplVar17 = ppppppplVar17 + 5;
        (*(code *)(*ppppppplVar17)[2])(ppppppplVar17);
      }
      else {
        do {
          while (ppppppplVar17 = ppppppplVar14, ppppppplVar17[4] < pppppplStack_88) {
            ppppppplVar14 = (long *******)ppppppplVar17[1];
            if ((long *******)ppppppplVar17[1] == (long *******)0x0) {
              ppppppplVar17 = ppppppplVar13;
              if (ppppppplVar13 != ppppppplVar18) goto code_r0x01674394;
              goto code_r0x016743b0;
            }
          }
          ppppppplVar14 = (long *******)*ppppppplVar17;
          ppppppplVar13 = ppppppplVar17;
        } while ((long *******)*ppppppplVar17 != (long *******)0x0);
        if (ppppppplVar17 == ppppppplVar18) goto code_r0x016743b0;
code_r0x01674394:
        if ((pppppplStack_88 < ppppppplVar17[4]) || (ppppppplVar17 == ppppppplVar18))
        goto code_r0x016743b0;
        ppppppplVar17 = ppppppplVar17 + 5;
      }
      lVar10 = *param_2 + uVar15 * 0x40;
      iVar11 = *(int *)(lVar10 + 0x20);
      if (iVar11 == 6) {
        (*(code *)**ppppppplVar17)(ppppppplVar17,lVar10 + 0x28);
      }
      else if (iVar11 == 7) {
        (*(code *)(*ppppppplVar17)[1])(ppppppplVar17,*param_2 + uVar15 * 0x40 + 0x28);
      }
      uVar1 = (int)uVar15 + 1;
      uVar15 = (ulong)uVar1;
    } while (uVar1 < *(uint *)(param_2 + 1));
  }
  return 1;
}

// ==== IInfoBaseMap<unsigned long, CGachaMaintenanceInfo>::DeserializeChild(Aska::ASON::AValue::AMap const*)
// vaddr 0x1576d84 | ghidra 0x1676d84 | size 932 | symbol _ZN12IInfoBaseMapIm21CGachaMaintenanceInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Type propagation algorithm not settling */

undefined8
_ZN12IInfoBaseMapIm21CGachaMaintenanceInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE
          (long *param_1,long *param_2)

{
  uint uVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined *puVar5;
  undefined *puVar6;
  undefined *puVar7;
  long lVar8;
  int iVar9;
  long *plVar10;
  long *******ppppppplVar11;
  long *******ppppppplVar12;
  ulong uVar13;
  long *******ppppppplVar14;
  long *******ppppppplVar15;
  long *******ppppppplVar16;
  undefined *puStack_120;
  undefined8 *puStack_118;
  undefined8 auStack_110 [2];
  undefined8 *puStack_100;
  undefined8 uStack_f8;
  undefined8 uStack_f0;
  undefined *puStack_e8;
  undefined8 uStack_e0;
  undefined1 uStack_d8;
  undefined1 auStack_d0 [24];
  undefined *puStack_b8;
  undefined8 uStack_b0;
  undefined1 uStack_a8;
  undefined1 auStack_a0 [24];
  long ******pppppplStack_88;
  long *******appppppplStack_80 [3];
  long *******ppppppplStack_68;
  
  ppppppplVar16 = (long *******)(param_1 + 8);
  plVar10 = param_1 + 7;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CGachaMaintenanceInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CGachaMaintenanceInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CGachaMaintenanceInfo>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CGachaMaintenanceInfo>, void*>*)(plVar10,*ppppppplVar16);
  param_1[7] = (long)ppppppplVar16;
  param_1[8] = 0;
  param_1[9] = 0;
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0282d54e/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\Info/InfoBase.h"*/,0x1c1,&UNK_027dc58a/*"apParser is null."*/);
    iVar9 = iRam0000000000000008;
  }
  else {
    iVar9 = (int)param_2[1];
  }
  if (iVar9 != 0) {
    puVar2 = PTR__ZTV21CGachaMaintenanceInfo_02cb9a18 + 0x10;
    puVar3 = PTR__ZTV22CParameterPropertyBaseILj21EE_02cc1310 + 0x10;
    puVar4 = PTR__ZTV23CParameterPropertyValueIjLj21E18CPropertyConverterE_02cbeae0 + 0x10;
    puVar5 = PTR__ZTV22CParameterPropertyBaseILj22EE_02cc4630 + 0x10;
    puVar6 = PTR__ZTV23CParameterPropertyValueIjLj22E18CPropertyConverterE_02cb7420 + 0x10;
    uVar13 = 0;
    puVar7 = PTR__ZTV8InfoBase_02cc49c8 + 0x10;
    do {
      pppppplStack_88 =
           (long ******)(**(code **)(*param_1 + 0x20))(param_1,*param_2 + uVar13 * 0x40);
      ppppppplVar12 = (long *******)param_1[8];
      ppppppplVar11 = ppppppplVar16;
      if ((long *******)param_1[8] == (long *******)0x0) {
code_r0x01676f00:
        memset(auStack_110,0,0x88);
        uStack_f8 = 0;
        uStack_f0 = 0;
        uStack_d8 = 0;
        uStack_e0 = 0;
        puStack_120 = puVar2;
        puStack_118 = auStack_110;
        puStack_100 = &uStack_f8;
        puStack_e8 = puVar3;
        Framework::CHash32::CHash32()(auStack_d0);
        uStack_a8 = 0;
        uStack_b0 = 0;
        puStack_e8 = puVar4;
        puStack_b8 = puVar5;
        Framework::CHash32::CHash32()(auStack_a0);
        ppppppplVar12 = (long *******)*ppppppplVar16;
        if ((long *******)*ppppppplVar16 == (long *******)0x0) {
          ppppppplVar15 = (long *******)*ppppppplVar16;
          ppppppplVar11 = ppppppplVar16;
          ppppppplVar14 = ppppppplVar16;
        }
        else {
          do {
            while (ppppppplVar11 = ppppppplVar12, ppppppplVar11[4] <= pppppplStack_88) {
              if (pppppplStack_88 <= ppppppplVar11[4]) {
                ppppppplVar15 = ppppppplVar11;
                ppppppplVar14 = (long *******)&ppppppplStack_68;
                goto joined_r0x01676fcc;
              }
              ppppppplVar14 = ppppppplVar11 + 1;
              ppppppplVar12 = (long *******)*ppppppplVar14;
              if ((long *******)*ppppppplVar14 == (long *******)0x0) {
                ppppppplVar15 = (long *******)*ppppppplVar14;
                goto joined_r0x01676fcc;
              }
            }
            ppppppplVar12 = (long *******)*ppppppplVar11;
          } while ((long *******)*ppppppplVar11 != (long *******)0x0);
          ppppppplVar15 = (long *******)*ppppppplVar11;
          ppppppplVar14 = ppppppplVar11;
        }
joined_r0x01676fcc:
        ppppppplStack_68 = ppppppplVar11;
        if (ppppppplVar15 == (long *******)0x0) {
          puStack_b8 = puVar6;
          std::__ndk1::unique_ptr<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CGachaMaintenanceInfo>, void*>, std::__ndk1::__tree_node_destructor<Framework::CSTLAllocator<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CGachaMaintenanceInfo>, void*>, Framework::CSTLMapAllocatorInf> > > std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CGachaMaintenanceInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CGachaMaintenanceInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CGachaMaintenanceInfo>, Framework::CSTLMapAllocatorInf> >::__construct_node<unsigned long&, CGachaMaintenanceInfo>(unsigned long&, CGachaMaintenanceInfo&&)(appppppplStack_80,plVar10,&pppppplStack_88,&puStack_120);
          *appppppplStack_80[0] = (long ******)0x0;
          appppppplStack_80[0][1] = (long ******)0x0;
          appppppplStack_80[0][2] = (long ******)ppppppplVar11;
          *ppppppplVar14 = (long ******)appppppplStack_80[0];
          ppppppplVar12 = appppppplStack_80[0];
          if (*(long *)*plVar10 != 0) {
            *plVar10 = *(long *)*plVar10;
            ppppppplVar12 = (long *******)*ppppppplVar14;
          }
          void std::__ndk1::__tree_balance_after_insert<std::__ndk1::__tree_node_base<void*>*>(std::__ndk1::__tree_node_base<void*>*, std::__ndk1::__tree_node_base<void*>*)(param_1[8],ppppppplVar12);
          param_1[9] = param_1[9] + 1;
          ppppppplVar15 = appppppplStack_80[0];
        }
        puStack_120 = PTR__ZTV21CGachaMaintenanceInfo_02cb9a18 + 0x10;
        puStack_b8 = PTR__ZTV22CParameterPropertyBaseILj22EE_02cc4630 + 0x10;
        Framework::CHash32::~CHash32()(auStack_a0);
        puStack_e8 = PTR__ZTV22CParameterPropertyBaseILj21EE_02cc1310 + 0x10;
        Framework::CHash32::~CHash32()(auStack_d0);
        puStack_120 = puVar7;
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*)(&puStack_100,uStack_f8);
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*)(&puStack_118,auStack_110[0]);
        ppppppplVar15 = ppppppplVar15 + 5;
        (*(code *)(*ppppppplVar15)[2])(ppppppplVar15);
      }
      else {
        do {
          while (ppppppplVar15 = ppppppplVar12, ppppppplVar15[4] < pppppplStack_88) {
            ppppppplVar12 = (long *******)ppppppplVar15[1];
            if ((long *******)ppppppplVar15[1] == (long *******)0x0) {
              ppppppplVar15 = ppppppplVar11;
              if (ppppppplVar11 != ppppppplVar16) goto code_r0x01676ee4;
              goto code_r0x01676f00;
            }
          }
          ppppppplVar12 = (long *******)*ppppppplVar15;
          ppppppplVar11 = ppppppplVar15;
        } while ((long *******)*ppppppplVar15 != (long *******)0x0);
        if (ppppppplVar15 == ppppppplVar16) goto code_r0x01676f00;
code_r0x01676ee4:
        if ((pppppplStack_88 < ppppppplVar15[4]) || (ppppppplVar15 == ppppppplVar16))
        goto code_r0x01676f00;
        ppppppplVar15 = ppppppplVar15 + 5;
      }
      lVar8 = *param_2 + uVar13 * 0x40;
      iVar9 = *(int *)(lVar8 + 0x20);
      if (iVar9 == 6) {
        (*(code *)**ppppppplVar15)(ppppppplVar15,lVar8 + 0x28);
      }
      else if (iVar9 == 7) {
        (*(code *)(*ppppppplVar15)[1])(ppppppplVar15,*param_2 + uVar13 * 0x40 + 0x28);
      }
      uVar1 = (int)uVar13 + 1;
      uVar13 = (ulong)uVar1;
    } while (uVar1 < *(uint *)(param_2 + 1));
  }
  return 1;
}

// ==== IInfoBaseMap<unsigned long, CEventMaintenanceInfo>::DeserializeChild(Aska::ASON::AValue::AMap const*)
// vaddr 0x1577650 | ghidra 0x1677650 | size 932 | symbol _ZN12IInfoBaseMapIm21CEventMaintenanceInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Type propagation algorithm not settling */

undefined8
_ZN12IInfoBaseMapIm21CEventMaintenanceInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE
          (long *param_1,long *param_2)

{
  uint uVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined *puVar5;
  undefined *puVar6;
  undefined *puVar7;
  long lVar8;
  int iVar9;
  long *plVar10;
  long *******ppppppplVar11;
  long *******ppppppplVar12;
  ulong uVar13;
  long *******ppppppplVar14;
  long *******ppppppplVar15;
  long *******ppppppplVar16;
  undefined *puStack_120;
  undefined8 *puStack_118;
  undefined8 auStack_110 [2];
  undefined8 *puStack_100;
  undefined8 uStack_f8;
  undefined8 uStack_f0;
  undefined *puStack_e8;
  undefined8 uStack_e0;
  undefined1 uStack_d8;
  undefined1 auStack_d0 [24];
  undefined *puStack_b8;
  undefined8 uStack_b0;
  undefined1 uStack_a8;
  undefined1 auStack_a0 [24];
  long ******pppppplStack_88;
  long *******appppppplStack_80 [3];
  long *******ppppppplStack_68;
  
  ppppppplVar16 = (long *******)(param_1 + 8);
  plVar10 = param_1 + 7;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CEventMaintenanceInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CEventMaintenanceInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CEventMaintenanceInfo>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CEventMaintenanceInfo>, void*>*)(plVar10,*ppppppplVar16);
  param_1[7] = (long)ppppppplVar16;
  param_1[8] = 0;
  param_1[9] = 0;
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0282d54e/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\Info/InfoBase.h"*/,0x1c1,&UNK_027dc58a/*"apParser is null."*/);
    iVar9 = iRam0000000000000008;
  }
  else {
    iVar9 = (int)param_2[1];
  }
  if (iVar9 != 0) {
    puVar2 = PTR__ZTV21CEventMaintenanceInfo_02cc3d78 + 0x10;
    puVar3 = PTR__ZTV22CParameterPropertyBaseILj21EE_02cc1310 + 0x10;
    puVar4 = PTR__ZTV23CParameterPropertyValueIjLj21E18CPropertyConverterE_02cbeae0 + 0x10;
    puVar5 = PTR__ZTV22CParameterPropertyBaseILj22EE_02cc4630 + 0x10;
    puVar6 = PTR__ZTV23CParameterPropertyValueIjLj22E18CPropertyConverterE_02cb7420 + 0x10;
    uVar13 = 0;
    puVar7 = PTR__ZTV8InfoBase_02cc49c8 + 0x10;
    do {
      pppppplStack_88 =
           (long ******)(**(code **)(*param_1 + 0x20))(param_1,*param_2 + uVar13 * 0x40);
      ppppppplVar12 = (long *******)param_1[8];
      ppppppplVar11 = ppppppplVar16;
      if ((long *******)param_1[8] == (long *******)0x0) {
code_r0x016777cc:
        memset(auStack_110,0,0x88);
        uStack_f8 = 0;
        uStack_f0 = 0;
        uStack_d8 = 0;
        uStack_e0 = 0;
        puStack_120 = puVar2;
        puStack_118 = auStack_110;
        puStack_100 = &uStack_f8;
        puStack_e8 = puVar3;
        Framework::CHash32::CHash32()(auStack_d0);
        uStack_a8 = 0;
        uStack_b0 = 0;
        puStack_e8 = puVar4;
        puStack_b8 = puVar5;
        Framework::CHash32::CHash32()(auStack_a0);
        ppppppplVar12 = (long *******)*ppppppplVar16;
        if ((long *******)*ppppppplVar16 == (long *******)0x0) {
          ppppppplVar15 = (long *******)*ppppppplVar16;
          ppppppplVar11 = ppppppplVar16;
          ppppppplVar14 = ppppppplVar16;
        }
        else {
          do {
            while (ppppppplVar11 = ppppppplVar12, ppppppplVar11[4] <= pppppplStack_88) {
              if (pppppplStack_88 <= ppppppplVar11[4]) {
                ppppppplVar15 = ppppppplVar11;
                ppppppplVar14 = (long *******)&ppppppplStack_68;
                goto joined_r0x01677898;
              }
              ppppppplVar14 = ppppppplVar11 + 1;
              ppppppplVar12 = (long *******)*ppppppplVar14;
              if ((long *******)*ppppppplVar14 == (long *******)0x0) {
                ppppppplVar15 = (long *******)*ppppppplVar14;
                goto joined_r0x01677898;
              }
            }
            ppppppplVar12 = (long *******)*ppppppplVar11;
          } while ((long *******)*ppppppplVar11 != (long *******)0x0);
          ppppppplVar15 = (long *******)*ppppppplVar11;
          ppppppplVar14 = ppppppplVar11;
        }
joined_r0x01677898:
        ppppppplStack_68 = ppppppplVar11;
        if (ppppppplVar15 == (long *******)0x0) {
          puStack_b8 = puVar6;
          std::__ndk1::unique_ptr<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CEventMaintenanceInfo>, void*>, std::__ndk1::__tree_node_destructor<Framework::CSTLAllocator<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CEventMaintenanceInfo>, void*>, Framework::CSTLMapAllocatorInf> > > std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CEventMaintenanceInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CEventMaintenanceInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CEventMaintenanceInfo>, Framework::CSTLMapAllocatorInf> >::__construct_node<unsigned long&, CEventMaintenanceInfo>(unsigned long&, CEventMaintenanceInfo&&)(appppppplStack_80,plVar10,&pppppplStack_88,&puStack_120);
          *appppppplStack_80[0] = (long ******)0x0;
          appppppplStack_80[0][1] = (long ******)0x0;
          appppppplStack_80[0][2] = (long ******)ppppppplVar11;
          *ppppppplVar14 = (long ******)appppppplStack_80[0];
          ppppppplVar12 = appppppplStack_80[0];
          if (*(long *)*plVar10 != 0) {
            *plVar10 = *(long *)*plVar10;
            ppppppplVar12 = (long *******)*ppppppplVar14;
          }
          void std::__ndk1::__tree_balance_after_insert<std::__ndk1::__tree_node_base<void*>*>(std::__ndk1::__tree_node_base<void*>*, std::__ndk1::__tree_node_base<void*>*)(param_1[8],ppppppplVar12);
          param_1[9] = param_1[9] + 1;
          ppppppplVar15 = appppppplStack_80[0];
        }
        puStack_120 = PTR__ZTV21CEventMaintenanceInfo_02cc3d78 + 0x10;
        puStack_b8 = PTR__ZTV22CParameterPropertyBaseILj22EE_02cc4630 + 0x10;
        Framework::CHash32::~CHash32()(auStack_a0);
        puStack_e8 = PTR__ZTV22CParameterPropertyBaseILj21EE_02cc1310 + 0x10;
        Framework::CHash32::~CHash32()(auStack_d0);
        puStack_120 = puVar7;
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*)(&puStack_100,uStack_f8);
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*)(&puStack_118,auStack_110[0]);
        ppppppplVar15 = ppppppplVar15 + 5;
        (*(code *)(*ppppppplVar15)[2])(ppppppplVar15);
      }
      else {
        do {
          while (ppppppplVar15 = ppppppplVar12, ppppppplVar15[4] < pppppplStack_88) {
            ppppppplVar12 = (long *******)ppppppplVar15[1];
            if ((long *******)ppppppplVar15[1] == (long *******)0x0) {
              ppppppplVar15 = ppppppplVar11;
              if (ppppppplVar11 != ppppppplVar16) goto code_r0x016777b0;
              goto code_r0x016777cc;
            }
          }
          ppppppplVar12 = (long *******)*ppppppplVar15;
          ppppppplVar11 = ppppppplVar15;
        } while ((long *******)*ppppppplVar15 != (long *******)0x0);
        if (ppppppplVar15 == ppppppplVar16) goto code_r0x016777cc;
code_r0x016777b0:
        if ((pppppplStack_88 < ppppppplVar15[4]) || (ppppppplVar15 == ppppppplVar16))
        goto code_r0x016777cc;
        ppppppplVar15 = ppppppplVar15 + 5;
      }
      lVar8 = *param_2 + uVar13 * 0x40;
      iVar9 = *(int *)(lVar8 + 0x20);
      if (iVar9 == 6) {
        (*(code *)**ppppppplVar15)(ppppppplVar15,lVar8 + 0x28);
      }
      else if (iVar9 == 7) {
        (*(code *)(*ppppppplVar15)[1])(ppppppplVar15,*param_2 + uVar13 * 0x40 + 0x28);
      }
      uVar1 = (int)uVar13 + 1;
      uVar13 = (ulong)uVar1;
    } while (uVar1 < *(uint *)(param_2 + 1));
  }
  return 1;
}

// ==== IInfoBaseMap<unsigned long, CExchangeMaintenanceInfo>::DeserializeChild(Aska::ASON::AValue::AMap const*)
// vaddr 0x1577f20 | ghidra 0x1677f20 | size 972 | symbol _ZN12IInfoBaseMapIm24CExchangeMaintenanceInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Type propagation algorithm not settling */

undefined8
_ZN12IInfoBaseMapIm24CExchangeMaintenanceInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE
          (long *param_1,long *param_2)

{
  uint uVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined *puVar5;
  undefined *puVar6;
  undefined *puVar7;
  undefined *puVar8;
  long lVar9;
  int iVar10;
  long *plVar11;
  long *******ppppppplVar12;
  long *******ppppppplVar13;
  ulong uVar14;
  long *******ppppppplVar15;
  long *******ppppppplVar16;
  long *******ppppppplVar17;
  undefined *puStack_120;
  undefined8 *puStack_118;
  undefined8 auStack_110 [2];
  undefined8 *puStack_100;
  undefined8 uStack_f8;
  undefined8 uStack_f0;
  undefined *puStack_e8;
  undefined8 uStack_e0;
  undefined1 uStack_d8;
  undefined1 auStack_d0 [24];
  undefined *puStack_b8;
  undefined8 uStack_b0;
  undefined1 uStack_a8;
  undefined1 auStack_a0 [24];
  long ******pppppplStack_88;
  long *******appppppplStack_80 [3];
  long *******ppppppplStack_68;
  
  ppppppplVar17 = (long *******)(param_1 + 8);
  plVar11 = param_1 + 7;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CExchangeMaintenanceInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CExchangeMaintenanceInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CExchangeMaintenanceInfo>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CExchangeMaintenanceInfo>, void*>*)(plVar11,*ppppppplVar17);
  param_1[7] = (long)ppppppplVar17;
  param_1[8] = 0;
  param_1[9] = 0;
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0282d54e/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\Info/InfoBase.h"*/,0x1c1,&UNK_027dc58a/*"apParser is null."*/);
    iVar10 = iRam0000000000000008;
  }
  else {
    iVar10 = (int)param_2[1];
  }
  if (iVar10 != 0) {
    puVar2 = PTR__ZTV23CPartialMaintenanceInfo_02cbe3f0 + 0x10;
    puVar3 = PTR__ZTV22CParameterPropertyBaseILj20EE_02cc0d08 + 0x10;
    puVar4 = PTR__ZTV23CParameterPropertyValueIjLj20E18CPropertyConverterE_02cc2ce0 + 0x10;
    puVar5 = PTR__ZTV24CExchangeMaintenanceInfo_02cbc5d8 + 0x10;
    puVar6 = PTR__ZTV22CParameterPropertyBaseILj14EE_02cb9db0 + 0x10;
    puVar7 = PTR__ZTV23CParameterPropertyValueIjLj14E18CPropertyConverterE_02cbaef8 + 0x10;
    uVar14 = 0;
    puVar8 = PTR__ZTV8InfoBase_02cc49c8 + 0x10;
    do {
      pppppplStack_88 =
           (long ******)(**(code **)(*param_1 + 0x20))(param_1,*param_2 + uVar14 * 0x40);
      ppppppplVar13 = (long *******)param_1[8];
      ppppppplVar12 = ppppppplVar17;
      if ((long *******)param_1[8] == (long *******)0x0) {
code_r0x016780ac:
        memset(auStack_110,0,0x88);
        uStack_f8 = 0;
        uStack_f0 = 0;
        uStack_d8 = 0;
        uStack_e0 = 0;
        puStack_120 = puVar2;
        puStack_118 = auStack_110;
        puStack_100 = &uStack_f8;
        puStack_e8 = puVar3;
        Framework::CHash32::CHash32()(auStack_d0);
        uStack_a8 = 0;
        uStack_b0 = 0;
        puStack_120 = puVar5;
        puStack_e8 = puVar4;
        puStack_b8 = puVar6;
        Framework::CHash32::CHash32()(auStack_a0);
        ppppppplVar13 = (long *******)*ppppppplVar17;
        if ((long *******)*ppppppplVar17 == (long *******)0x0) {
          ppppppplVar16 = (long *******)*ppppppplVar17;
          ppppppplVar12 = ppppppplVar17;
          ppppppplVar15 = ppppppplVar17;
        }
        else {
          do {
            while (ppppppplVar12 = ppppppplVar13, ppppppplVar12[4] <= pppppplStack_88) {
              if (pppppplStack_88 <= ppppppplVar12[4]) {
                ppppppplVar16 = ppppppplVar12;
                ppppppplVar15 = (long *******)&ppppppplStack_68;
                goto joined_r0x01678180;
              }
              ppppppplVar15 = ppppppplVar12 + 1;
              ppppppplVar13 = (long *******)*ppppppplVar15;
              if ((long *******)*ppppppplVar15 == (long *******)0x0) {
                ppppppplVar16 = (long *******)*ppppppplVar15;
                goto joined_r0x01678180;
              }
            }
            ppppppplVar13 = (long *******)*ppppppplVar12;
          } while ((long *******)*ppppppplVar12 != (long *******)0x0);
          ppppppplVar16 = (long *******)*ppppppplVar12;
          ppppppplVar15 = ppppppplVar12;
        }
joined_r0x01678180:
        ppppppplStack_68 = ppppppplVar12;
        if (ppppppplVar16 == (long *******)0x0) {
          puStack_b8 = puVar7;
          std::__ndk1::unique_ptr<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CExchangeMaintenanceInfo>, void*>, std::__ndk1::__tree_node_destructor<Framework::CSTLAllocator<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CExchangeMaintenanceInfo>, void*>, Framework::CSTLMapAllocatorInf> > > std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CExchangeMaintenanceInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CExchangeMaintenanceInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CExchangeMaintenanceInfo>, Framework::CSTLMapAllocatorInf> >::__construct_node<unsigned long&, CExchangeMaintenanceInfo>(unsigned long&, CExchangeMaintenanceInfo&&)(appppppplStack_80,plVar11,&pppppplStack_88,&puStack_120);
          *appppppplStack_80[0] = (long ******)0x0;
          appppppplStack_80[0][1] = (long ******)0x0;
          appppppplStack_80[0][2] = (long ******)ppppppplVar12;
          *ppppppplVar15 = (long ******)appppppplStack_80[0];
          ppppppplVar13 = appppppplStack_80[0];
          if (*(long *)*plVar11 != 0) {
            *plVar11 = *(long *)*plVar11;
            ppppppplVar13 = (long *******)*ppppppplVar15;
          }
          void std::__ndk1::__tree_balance_after_insert<std::__ndk1::__tree_node_base<void*>*>(std::__ndk1::__tree_node_base<void*>*, std::__ndk1::__tree_node_base<void*>*)(param_1[8],ppppppplVar13);
          param_1[9] = param_1[9] + 1;
          ppppppplVar16 = appppppplStack_80[0];
        }
        puStack_120 = PTR__ZTV24CExchangeMaintenanceInfo_02cbc5d8 + 0x10;
        puStack_b8 = PTR__ZTV22CParameterPropertyBaseILj14EE_02cb9db0 + 0x10;
        Framework::CHash32::~CHash32()(auStack_a0);
        puStack_120 = PTR__ZTV23CPartialMaintenanceInfo_02cbe3f0 + 0x10;
        puStack_e8 = PTR__ZTV22CParameterPropertyBaseILj20EE_02cc0d08 + 0x10;
        Framework::CHash32::~CHash32()(auStack_d0);
        puStack_120 = puVar8;
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*)(&puStack_100,uStack_f8);
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*)(&puStack_118,auStack_110[0]);
        ppppppplVar16 = ppppppplVar16 + 5;
        (*(code *)(*ppppppplVar16)[2])(ppppppplVar16);
      }
      else {
        do {
          while (ppppppplVar16 = ppppppplVar13, ppppppplVar16[4] < pppppplStack_88) {
            ppppppplVar13 = (long *******)ppppppplVar16[1];
            if ((long *******)ppppppplVar16[1] == (long *******)0x0) {
              ppppppplVar16 = ppppppplVar12;
              if (ppppppplVar12 != ppppppplVar17) goto code_r0x01678090;
              goto code_r0x016780ac;
            }
          }
          ppppppplVar13 = (long *******)*ppppppplVar16;
          ppppppplVar12 = ppppppplVar16;
        } while ((long *******)*ppppppplVar16 != (long *******)0x0);
        if (ppppppplVar16 == ppppppplVar17) goto code_r0x016780ac;
code_r0x01678090:
        if ((pppppplStack_88 < ppppppplVar16[4]) || (ppppppplVar16 == ppppppplVar17))
        goto code_r0x016780ac;
        ppppppplVar16 = ppppppplVar16 + 5;
      }
      lVar9 = *param_2 + uVar14 * 0x40;
      iVar10 = *(int *)(lVar9 + 0x20);
      if (iVar10 == 6) {
        (*(code *)**ppppppplVar16)(ppppppplVar16,lVar9 + 0x28);
      }
      else if (iVar10 == 7) {
        (*(code *)(*ppppppplVar16)[1])(ppppppplVar16,*param_2 + uVar14 * 0x40 + 0x28);
      }
      uVar1 = (int)uVar14 + 1;
      uVar14 = (ulong)uVar1;
    } while (uVar1 < *(uint *)(param_2 + 1));
  }
  return 1;
}

// ==== IInfoBaseMap<unsigned long, CWorldMapMaintenanceInfo>::DeserializeChild(Aska::ASON::AValue::AMap const*)
// vaddr 0x1578884 | ghidra 0x1678884 | size 972 | symbol _ZN12IInfoBaseMapIm24CWorldMapMaintenanceInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Type propagation algorithm not settling */

undefined8
_ZN12IInfoBaseMapIm24CWorldMapMaintenanceInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE
          (long *param_1,long *param_2)

{
  uint uVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined *puVar5;
  undefined *puVar6;
  undefined *puVar7;
  undefined *puVar8;
  long lVar9;
  int iVar10;
  long *plVar11;
  long *******ppppppplVar12;
  long *******ppppppplVar13;
  ulong uVar14;
  long *******ppppppplVar15;
  long *******ppppppplVar16;
  long *******ppppppplVar17;
  undefined *puStack_120;
  undefined8 *puStack_118;
  undefined8 auStack_110 [2];
  undefined8 *puStack_100;
  undefined8 uStack_f8;
  undefined8 uStack_f0;
  undefined *puStack_e8;
  undefined8 uStack_e0;
  undefined1 uStack_d8;
  undefined1 auStack_d0 [24];
  undefined *puStack_b8;
  undefined8 uStack_b0;
  undefined1 uStack_a8;
  undefined1 auStack_a0 [24];
  long ******pppppplStack_88;
  long *******appppppplStack_80 [3];
  long *******ppppppplStack_68;
  
  ppppppplVar17 = (long *******)(param_1 + 8);
  plVar11 = param_1 + 7;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CWorldMapMaintenanceInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CWorldMapMaintenanceInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CWorldMapMaintenanceInfo>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CWorldMapMaintenanceInfo>, void*>*)(plVar11,*ppppppplVar17);
  param_1[7] = (long)ppppppplVar17;
  param_1[8] = 0;
  param_1[9] = 0;
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0282d54e/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\Info/InfoBase.h"*/,0x1c1,&UNK_027dc58a/*"apParser is null."*/);
    iVar10 = iRam0000000000000008;
  }
  else {
    iVar10 = (int)param_2[1];
  }
  if (iVar10 != 0) {
    puVar2 = PTR__ZTV23CPartialMaintenanceInfo_02cbe3f0 + 0x10;
    puVar3 = PTR__ZTV22CParameterPropertyBaseILj20EE_02cc0d08 + 0x10;
    puVar4 = PTR__ZTV23CParameterPropertyValueIjLj20E18CPropertyConverterE_02cc2ce0 + 0x10;
    puVar5 = PTR__ZTV24CWorldMapMaintenanceInfo_02cbd720 + 0x10;
    puVar6 = PTR__ZTV22CParameterPropertyBaseILj13EE_02cba498 + 0x10;
    puVar7 = PTR__ZTV23CParameterPropertyValueIjLj13E18CPropertyConverterE_02cbd818 + 0x10;
    uVar14 = 0;
    puVar8 = PTR__ZTV8InfoBase_02cc49c8 + 0x10;
    do {
      pppppplStack_88 =
           (long ******)(**(code **)(*param_1 + 0x20))(param_1,*param_2 + uVar14 * 0x40);
      ppppppplVar13 = (long *******)param_1[8];
      ppppppplVar12 = ppppppplVar17;
      if ((long *******)param_1[8] == (long *******)0x0) {
code_r0x01678a10:
        memset(auStack_110,0,0x88);
        uStack_f8 = 0;
        uStack_f0 = 0;
        uStack_d8 = 0;
        uStack_e0 = 0;
        puStack_120 = puVar2;
        puStack_118 = auStack_110;
        puStack_100 = &uStack_f8;
        puStack_e8 = puVar3;
        Framework::CHash32::CHash32()(auStack_d0);
        uStack_a8 = 0;
        uStack_b0 = 0;
        puStack_120 = puVar5;
        puStack_e8 = puVar4;
        puStack_b8 = puVar6;
        Framework::CHash32::CHash32()(auStack_a0);
        ppppppplVar13 = (long *******)*ppppppplVar17;
        if ((long *******)*ppppppplVar17 == (long *******)0x0) {
          ppppppplVar16 = (long *******)*ppppppplVar17;
          ppppppplVar12 = ppppppplVar17;
          ppppppplVar15 = ppppppplVar17;
        }
        else {
          do {
            while (ppppppplVar12 = ppppppplVar13, ppppppplVar12[4] <= pppppplStack_88) {
              if (pppppplStack_88 <= ppppppplVar12[4]) {
                ppppppplVar16 = ppppppplVar12;
                ppppppplVar15 = (long *******)&ppppppplStack_68;
                goto joined_r0x01678ae4;
              }
              ppppppplVar15 = ppppppplVar12 + 1;
              ppppppplVar13 = (long *******)*ppppppplVar15;
              if ((long *******)*ppppppplVar15 == (long *******)0x0) {
                ppppppplVar16 = (long *******)*ppppppplVar15;
                goto joined_r0x01678ae4;
              }
            }
            ppppppplVar13 = (long *******)*ppppppplVar12;
          } while ((long *******)*ppppppplVar12 != (long *******)0x0);
          ppppppplVar16 = (long *******)*ppppppplVar12;
          ppppppplVar15 = ppppppplVar12;
        }
joined_r0x01678ae4:
        ppppppplStack_68 = ppppppplVar12;
        if (ppppppplVar16 == (long *******)0x0) {
          puStack_b8 = puVar7;
          std::__ndk1::unique_ptr<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CWorldMapMaintenanceInfo>, void*>, std::__ndk1::__tree_node_destructor<Framework::CSTLAllocator<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CWorldMapMaintenanceInfo>, void*>, Framework::CSTLMapAllocatorInf> > > std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CWorldMapMaintenanceInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CWorldMapMaintenanceInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CWorldMapMaintenanceInfo>, Framework::CSTLMapAllocatorInf> >::__construct_node<unsigned long&, CWorldMapMaintenanceInfo>(unsigned long&, CWorldMapMaintenanceInfo&&)(appppppplStack_80,plVar11,&pppppplStack_88,&puStack_120);
          *appppppplStack_80[0] = (long ******)0x0;
          appppppplStack_80[0][1] = (long ******)0x0;
          appppppplStack_80[0][2] = (long ******)ppppppplVar12;
          *ppppppplVar15 = (long ******)appppppplStack_80[0];
          ppppppplVar13 = appppppplStack_80[0];
          if (*(long *)*plVar11 != 0) {
            *plVar11 = *(long *)*plVar11;
            ppppppplVar13 = (long *******)*ppppppplVar15;
          }
          void std::__ndk1::__tree_balance_after_insert<std::__ndk1::__tree_node_base<void*>*>(std::__ndk1::__tree_node_base<void*>*, std::__ndk1::__tree_node_base<void*>*)(param_1[8],ppppppplVar13);
          param_1[9] = param_1[9] + 1;
          ppppppplVar16 = appppppplStack_80[0];
        }
        puStack_120 = PTR__ZTV24CWorldMapMaintenanceInfo_02cbd720 + 0x10;
        puStack_b8 = PTR__ZTV22CParameterPropertyBaseILj13EE_02cba498 + 0x10;
        Framework::CHash32::~CHash32()(auStack_a0);
        puStack_120 = PTR__ZTV23CPartialMaintenanceInfo_02cbe3f0 + 0x10;
        puStack_e8 = PTR__ZTV22CParameterPropertyBaseILj20EE_02cc0d08 + 0x10;
        Framework::CHash32::~CHash32()(auStack_d0);
        puStack_120 = puVar8;
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*)(&puStack_100,uStack_f8);
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*)(&puStack_118,auStack_110[0]);
        ppppppplVar16 = ppppppplVar16 + 5;
        (*(code *)(*ppppppplVar16)[2])(ppppppplVar16);
      }
      else {
        do {
          while (ppppppplVar16 = ppppppplVar13, ppppppplVar16[4] < pppppplStack_88) {
            ppppppplVar13 = (long *******)ppppppplVar16[1];
            if ((long *******)ppppppplVar16[1] == (long *******)0x0) {
              ppppppplVar16 = ppppppplVar12;
              if (ppppppplVar12 != ppppppplVar17) goto code_r0x016789f4;
              goto code_r0x01678a10;
            }
          }
          ppppppplVar13 = (long *******)*ppppppplVar16;
          ppppppplVar12 = ppppppplVar16;
        } while ((long *******)*ppppppplVar16 != (long *******)0x0);
        if (ppppppplVar16 == ppppppplVar17) goto code_r0x01678a10;
code_r0x016789f4:
        if ((pppppplStack_88 < ppppppplVar16[4]) || (ppppppplVar16 == ppppppplVar17))
        goto code_r0x01678a10;
        ppppppplVar16 = ppppppplVar16 + 5;
      }
      lVar9 = *param_2 + uVar14 * 0x40;
      iVar10 = *(int *)(lVar9 + 0x20);
      if (iVar10 == 6) {
        (*(code *)**ppppppplVar16)(ppppppplVar16,lVar9 + 0x28);
      }
      else if (iVar10 == 7) {
        (*(code *)(*ppppppplVar16)[1])(ppppppplVar16,*param_2 + uVar14 * 0x40 + 0x28);
      }
      uVar1 = (int)uVar14 + 1;
      uVar14 = (ulong)uVar1;
    } while (uVar1 < *(uint *)(param_2 + 1));
  }
  return 1;
}

// ==== IInfoBaseMap<unsigned long, CExpirationInfo>::DeserializeChild(Aska::ASON::AValue::AMap const*)
// vaddr 0x1579198 | ghidra 0x1679198 | size 1096 | symbol _ZN12IInfoBaseMapIm15CExpirationInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Type propagation algorithm not settling */

undefined8
_ZN12IInfoBaseMapIm15CExpirationInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE
          (long *param_1,long *param_2)

{
  uint uVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined *puVar5;
  undefined *puVar6;
  undefined *puVar7;
  undefined *puVar8;
  undefined *puVar9;
  undefined *puVar10;
  undefined *puVar11;
  undefined *puVar12;
  undefined *puVar13;
  undefined *puVar14;
  long lVar15;
  int iVar16;
  long *plVar17;
  long *******ppppppplVar18;
  long *******ppppppplVar19;
  ulong uVar20;
  long *******ppppppplVar21;
  long *******ppppppplVar22;
  long *******ppppppplVar23;
  undefined *puStack_1f0;
  undefined1 *puStack_1e8;
  undefined1 auStack_1e0 [16];
  undefined8 *puStack_1d0;
  undefined8 uStack_1c8;
  undefined8 uStack_1c0;
  undefined *puStack_1b8;
  undefined8 uStack_1b0;
  undefined1 uStack_1a8;
  undefined1 auStack_1a0 [24];
  undefined *puStack_188;
  undefined8 uStack_180;
  undefined1 uStack_178;
  undefined1 auStack_170 [24];
  undefined *puStack_158;
  undefined8 uStack_150;
  undefined1 uStack_148;
  undefined1 auStack_140 [24];
  undefined *puStack_128;
  undefined8 uStack_120;
  undefined1 uStack_118;
  undefined1 auStack_110 [16];
  undefined8 uStack_100;
  undefined8 uStack_f8;
  undefined8 uStack_f0;
  undefined *puStack_e8;
  undefined8 uStack_e0;
  undefined1 uStack_d8;
  undefined1 auStack_d0 [24];
  undefined *puStack_b8;
  undefined8 uStack_b0;
  undefined1 uStack_a8;
  undefined1 auStack_a0 [24];
  long ******pppppplStack_88;
  long *******appppppplStack_80 [3];
  long *******ppppppplStack_68;
  
  ppppppplVar21 = (long *******)(param_1 + 8);
  plVar17 = param_1 + 7;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CExpirationInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CExpirationInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CExpirationInfo>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CExpirationInfo>, void*>*)(plVar17,*ppppppplVar21);
  param_1[7] = (long)ppppppplVar21;
  param_1[8] = 0;
  param_1[9] = 0;
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0282d54e/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\Info/InfoBase.h"*/,0x1c1,&UNK_027dc58a/*"apParser is null."*/);
    iVar16 = iRam0000000000000008;
  }
  else {
    iVar16 = (int)param_2[1];
  }
  if (iVar16 != 0) {
    puVar2 = PTR__ZTV15CExpirationInfo_02cb9a28 + 0x10;
    puVar3 = PTR__ZTV22CParameterPropertyBaseILj34EE_02cc0de8 + 0x10;
    puVar4 = PTR__ZTV23CParameterPropertyValueIbLj34E18CPropertyConverterE_02cb8ea8 + 0x10;
    puVar5 = PTR__ZTV22CParameterPropertyBaseILj35EE_02cc13f0 + 0x10;
    puVar6 = PTR__ZTV23CParameterPropertyValueIjLj35E18CPropertyConverterE_02cb7f18 + 0x10;
    puVar7 = PTR__ZTV22CParameterPropertyBaseILj36EE_02cb6f78 + 0x10;
    puVar8 = PTR__ZTV23CParameterPropertyValueIjLj36E18CPropertyConverterE_02cc2bf8 + 0x10;
    puVar9 = PTR__ZTV22CParameterPropertyBaseILj37EE_02cbda08 + 0x10;
    puVar10 = PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj37EE_02cb87f0
              + 0x10;
    puVar11 = PTR__ZTV22CParameterPropertyBaseILj39EE_02cc3d00 + 0x10;
    puVar12 = PTR__ZTV23CParameterPropertyValueIbLj39E18CPropertyConverterE_02cc0aa8 + 0x10;
    uVar20 = 0;
    puVar13 = PTR__ZTV22CParameterPropertyBaseILj42EE_02cb6c60 + 0x10;
    puVar14 = PTR__ZTV23CParameterPropertyValueIjLj42E18CPropertyConverterE_02cba8a0 + 0x10;
    do {
      pppppplStack_88 =
           (long ******)(**(code **)(*param_1 + 0x20))(param_1,*param_2 + uVar20 * 0x40);
      ppppppplVar19 = (long *******)param_1[8];
      ppppppplVar18 = ppppppplVar21;
      if ((long *******)param_1[8] == (long *******)0x0) {
code_r0x0167939c:
        memset(auStack_1e0,0,0x158);
        uStack_1c8 = 0;
        uStack_1c0 = 0;
        uStack_1a8 = 0;
        uStack_1b0 = 0;
        puStack_1f0 = puVar2;
        puStack_1e8 = auStack_1e0;
        puStack_1d0 = &uStack_1c8;
        puStack_1b8 = puVar3;
        Framework::CHash32::CHash32()(auStack_1a0);
        uStack_178 = 0;
        uStack_180 = 0;
        puStack_1b8 = puVar4;
        puStack_188 = puVar5;
        Framework::CHash32::CHash32()(auStack_170);
        uStack_148 = 0;
        uStack_150 = 0;
        puStack_188 = puVar6;
        puStack_158 = puVar7;
        Framework::CHash32::CHash32()(auStack_140);
        uStack_118 = 0;
        uStack_120 = 0;
        puStack_158 = puVar8;
        puStack_128 = puVar9;
        Framework::CHash32::CHash32()(auStack_110);
        uStack_f8 = 0;
        uStack_f0 = 0;
        uStack_100 = 0;
        uStack_d8 = 0;
        uStack_e0 = 0;
        puStack_128 = puVar10;
        puStack_e8 = puVar11;
        Framework::CHash32::CHash32()(auStack_d0);
        uStack_a8 = 0;
        uStack_b0 = 0;
        puStack_e8 = puVar12;
        puStack_b8 = puVar13;
        Framework::CHash32::CHash32()(auStack_a0);
        ppppppplVar19 = (long *******)*ppppppplVar21;
        if ((long *******)*ppppppplVar21 == (long *******)0x0) {
          ppppppplVar23 = (long *******)*ppppppplVar21;
          ppppppplVar18 = ppppppplVar21;
          ppppppplVar22 = ppppppplVar21;
        }
        else {
          do {
            while (ppppppplVar18 = ppppppplVar19, ppppppplVar18[4] <= pppppplStack_88) {
              if (pppppplStack_88 <= ppppppplVar18[4]) {
                ppppppplVar23 = ppppppplVar18;
                ppppppplVar22 = (long *******)&ppppppplStack_68;
                goto joined_r0x016794dc;
              }
              ppppppplVar22 = ppppppplVar18 + 1;
              ppppppplVar19 = (long *******)*ppppppplVar22;
              if ((long *******)*ppppppplVar22 == (long *******)0x0) {
                ppppppplVar23 = (long *******)*ppppppplVar22;
                goto joined_r0x016794dc;
              }
            }
            ppppppplVar19 = (long *******)*ppppppplVar18;
          } while ((long *******)*ppppppplVar18 != (long *******)0x0);
          ppppppplVar23 = (long *******)*ppppppplVar18;
          ppppppplVar22 = ppppppplVar18;
        }
joined_r0x016794dc:
        puStack_b8 = puVar14;
        ppppppplStack_68 = ppppppplVar18;
        if (ppppppplVar23 == (long *******)0x0) {
          std::__ndk1::unique_ptr<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CExpirationInfo>, void*>, std::__ndk1::__tree_node_destructor<Framework::CSTLAllocator<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CExpirationInfo>, void*>, Framework::CSTLMapAllocatorInf> > > std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CExpirationInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CExpirationInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CExpirationInfo>, Framework::CSTLMapAllocatorInf> >::__construct_node<unsigned long&, CExpirationInfo>(unsigned long&, CExpirationInfo&&)(appppppplStack_80,plVar17,&pppppplStack_88,&puStack_1f0);
          *appppppplStack_80[0] = (long ******)0x0;
          appppppplStack_80[0][1] = (long ******)0x0;
          appppppplStack_80[0][2] = (long ******)ppppppplVar18;
          *ppppppplVar22 = (long ******)appppppplStack_80[0];
          ppppppplVar19 = appppppplStack_80[0];
          if (*(long *)*plVar17 != 0) {
            *plVar17 = *(long *)*plVar17;
            ppppppplVar19 = (long *******)*ppppppplVar22;
          }
          void std::__ndk1::__tree_balance_after_insert<std::__ndk1::__tree_node_base<void*>*>(std::__ndk1::__tree_node_base<void*>*, std::__ndk1::__tree_node_base<void*>*)(param_1[8],ppppppplVar19);
          param_1[9] = param_1[9] + 1;
          ppppppplVar23 = appppppplStack_80[0];
        }
        CExpirationInfo::~CExpirationInfo()(&puStack_1f0);
        ppppppplVar23 = ppppppplVar23 + 5;
        (*(code *)(*ppppppplVar23)[2])(ppppppplVar23);
      }
      else {
        do {
          while (ppppppplVar23 = ppppppplVar19, ppppppplVar23[4] < pppppplStack_88) {
            ppppppplVar19 = (long *******)ppppppplVar23[1];
            if ((long *******)ppppppplVar23[1] == (long *******)0x0) {
              ppppppplVar23 = ppppppplVar18;
              if (ppppppplVar18 != ppppppplVar21) goto code_r0x01679380;
              goto code_r0x0167939c;
            }
          }
          ppppppplVar19 = (long *******)*ppppppplVar23;
          ppppppplVar18 = ppppppplVar23;
        } while ((long *******)*ppppppplVar23 != (long *******)0x0);
        if (ppppppplVar23 == ppppppplVar21) goto code_r0x0167939c;
code_r0x01679380:
        if ((pppppplStack_88 < ppppppplVar23[4]) || (ppppppplVar23 == ppppppplVar21))
        goto code_r0x0167939c;
        ppppppplVar23 = ppppppplVar23 + 5;
      }
      lVar15 = *param_2 + uVar20 * 0x40;
      iVar16 = *(int *)(lVar15 + 0x20);
      if (iVar16 == 6) {
        (*(code *)**ppppppplVar23)(ppppppplVar23,lVar15 + 0x28);
      }
      else if (iVar16 == 7) {
        (*(code *)(*ppppppplVar23)[1])(ppppppplVar23,*param_2 + uVar20 * 0x40 + 0x28);
      }
      uVar1 = (int)uVar20 + 1;
      uVar20 = (ulong)uVar1;
    } while (uVar1 < *(uint *)(param_2 + 1));
  }
  return 1;
}

// ==== IInfoBaseMap<unsigned long, _CExpirationInfoList>::DeserializeChild(Aska::ASON::AValue::AMap const*)
// vaddr 0x1579a9c | ghidra 0x1679a9c | size 584 | symbol _ZN12IInfoBaseMapIm20_CExpirationInfoListE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN12IInfoBaseMapIm20_CExpirationInfoListE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE
          (long *param_1,long *param_2)

{
  uint uVar1;
  undefined *puVar2;
  undefined *puVar3;
  long lVar4;
  int iVar5;
  long *plVar6;
  long lVar7;
  long *plVar8;
  ulong uVar9;
  long *plVar10;
  long *plVar11;
  undefined *puStack_b8;
  undefined8 *puStack_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined8 *puStack_98;
  undefined8 uStack_90;
  undefined8 uStack_88;
  long lStack_80;
  long lStack_78;
  undefined8 uStack_70;
  ulong uStack_68;
  
  plVar11 = param_1 + 8;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, _CExpirationInfoList>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, _CExpirationInfoList>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, _CExpirationInfoList>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, _CExpirationInfoList>, void*>*)(param_1 + 7,*plVar11);
  param_1[7] = (long)plVar11;
  param_1[8] = 0;
  param_1[9] = 0;
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0282d54e/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\Info/InfoBase.h"*/,0x1c1,&UNK_027dc58a/*"apParser is null."*/);
    iVar5 = iRam0000000000000008;
  }
  else {
    iVar5 = (int)param_2[1];
  }
  if (iVar5 != 0) {
    uVar9 = 0;
    puVar2 = PTR__ZTV20_CExpirationInfoList_02cc2300 + 0x10;
    puVar3 = PTR__ZTV8InfoBase_02cc49c8 + 0x10;
    do {
      uStack_68 = (**(code **)(*param_1 + 0x20))(param_1,*param_2 + uVar9 * 0x40);
      plVar6 = (long *)param_1[8];
      plVar8 = plVar11;
      if ((long *)param_1[8] == (long *)0x0) {
code_r0x01679bcc:
        uStack_a8 = 0;
        uStack_a0 = 0;
        uStack_90 = 0;
        uStack_88 = 0;
        lStack_78 = 0;
        uStack_70 = 0;
        lStack_80 = 0;
        puStack_b8 = puVar2;
        puStack_b0 = &uStack_a8;
        puStack_98 = &uStack_90;
        lVar7 = std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned long, _CExpirationInfoList>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, _CExpirationInfoList>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, _CExpirationInfoList>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, _CExpirationInfoList>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, _CExpirationInfoList>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned long, unsigned long&, _CExpirationInfoList>(unsigned long const&, unsigned long&, _CExpirationInfoList&&)(param_1 + 7,&uStack_68,&uStack_68,&puStack_b8);
        lVar4 = lStack_80;
        if (lStack_80 != 0) {
          while (lStack_78 != lVar4) {
            lStack_78 = lStack_78 + -0x168;
            CExpirationInfo::~CExpirationInfo()();
          }
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(lStack_80);
        }
        puStack_b8 = puVar3;
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*)(&puStack_98,uStack_90);
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*)(&puStack_b0,uStack_a8);
        plVar10 = (long *)(lVar7 + 0x28);
        (**(code **)(*plVar10 + 0x10))(plVar10);
      }
      else {
        do {
          while (plVar10 = plVar6, uStack_68 <= (ulong)plVar10[4]) {
            plVar6 = (long *)*plVar10;
            plVar8 = plVar10;
            if ((long *)*plVar10 == (long *)0x0) {
              if (plVar10 != plVar11) goto code_r0x01679bb0;
              goto code_r0x01679bcc;
            }
          }
          plVar6 = (long *)plVar10[1];
        } while ((long *)plVar10[1] != (long *)0x0);
        plVar10 = plVar8;
        if (plVar8 == plVar11) goto code_r0x01679bcc;
code_r0x01679bb0:
        if ((uStack_68 < (ulong)plVar10[4]) || (plVar10 == plVar11)) goto code_r0x01679bcc;
        plVar10 = plVar10 + 5;
      }
      lVar4 = *param_2 + uVar9 * 0x40;
      iVar5 = *(int *)(lVar4 + 0x20);
      if (iVar5 == 6) {
        (**(code **)*plVar10)(plVar10,lVar4 + 0x28);
      }
      else if (iVar5 == 7) {
        (**(code **)(*plVar10 + 8))(plVar10,*param_2 + uVar9 * 0x40 + 0x28);
      }
      uVar1 = (int)uVar9 + 1;
      uVar9 = (ulong)uVar1;
    } while (uVar1 < *(uint *)(param_2 + 1));
  }
  return 1;
}

// ==== IInfoBaseMap<unsigned long, Sphere211TreasureResultInfoList>::DeserializeChild(Aska::ASON::AValue::AMap const*)
// vaddr 0x157a8ac | ghidra 0x167a8ac | size 480 | symbol _ZN12IInfoBaseMapIm31Sphere211TreasureResultInfoListE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN12IInfoBaseMapIm31Sphere211TreasureResultInfoListE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE
          (long *param_1,long *param_2)

{
  uint uVar1;
  undefined *puVar2;
  int iVar3;
  long *plVar4;
  long lVar5;
  long *plVar6;
  ulong uVar7;
  long *plVar8;
  long *plVar9;
  undefined *puStack_b0;
  undefined8 *puStack_a8;
  undefined8 uStack_a0;
  undefined8 uStack_98;
  undefined8 *puStack_90;
  undefined8 uStack_88;
  undefined8 uStack_80;
  undefined8 uStack_78;
  undefined8 uStack_70;
  undefined8 uStack_68;
  ulong uStack_58;
  
  plVar9 = param_1 + 8;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, Sphere211TreasureResultInfoList>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, Sphere211TreasureResultInfoList>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, Sphere211TreasureResultInfoList>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, Sphere211TreasureResultInfoList>, void*>*)(param_1 + 7,*plVar9);
  param_1[7] = (long)plVar9;
  param_1[8] = 0;
  param_1[9] = 0;
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0282d54e/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\Info/InfoBase.h"*/,0x1c1,&UNK_027dc58a/*"apParser is null."*/);
    iVar3 = iRam0000000000000008;
  }
  else {
    iVar3 = (int)param_2[1];
  }
  if (iVar3 != 0) {
    uVar7 = 0;
    puVar2 = PTR__ZTV31Sphere211TreasureResultInfoList_02cb6fe8 + 0x10;
    do {
      uStack_58 = (**(code **)(*param_1 + 0x20))(param_1,*param_2 + uVar7 * 0x40);
      plVar4 = (long *)param_1[8];
      plVar6 = plVar9;
      if ((long *)param_1[8] == (long *)0x0) {
code_r0x0167a9c4:
        uStack_a0 = 0;
        uStack_98 = 0;
        uStack_88 = 0;
        uStack_80 = 0;
        uStack_70 = 0;
        uStack_68 = 0;
        uStack_78 = 0;
        puStack_b0 = puVar2;
        puStack_a8 = &uStack_a0;
        puStack_90 = &uStack_88;
        lVar5 = std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned long, Sphere211TreasureResultInfoList>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, Sphere211TreasureResultInfoList>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, Sphere211TreasureResultInfoList>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, Sphere211TreasureResultInfoList>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, Sphere211TreasureResultInfoList>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned long, unsigned long&, Sphere211TreasureResultInfoList>(unsigned long const&, unsigned long&, Sphere211TreasureResultInfoList&&)(param_1 + 7,&uStack_58,&uStack_58,&puStack_b0);
        InfoBaseArray<Sphere211TreasureResultInfo>::~InfoBaseArray()(&puStack_b0);
        plVar8 = (long *)(lVar5 + 0x28);
        (**(code **)(*plVar8 + 0x10))(plVar8);
      }
      else {
        do {
          while (plVar8 = plVar4, (ulong)plVar8[4] < uStack_58) {
            plVar4 = (long *)plVar8[1];
            if ((long *)plVar8[1] == (long *)0x0) {
              plVar8 = plVar6;
              if (plVar6 != plVar9) goto code_r0x0167a9a8;
              goto code_r0x0167a9c4;
            }
          }
          plVar4 = (long *)*plVar8;
          plVar6 = plVar8;
        } while ((long *)*plVar8 != (long *)0x0);
        if (plVar8 == plVar9) goto code_r0x0167a9c4;
code_r0x0167a9a8:
        if ((uStack_58 < (ulong)plVar8[4]) || (plVar8 == plVar9)) goto code_r0x0167a9c4;
        plVar8 = plVar8 + 5;
      }
      lVar5 = *param_2 + uVar7 * 0x40;
      iVar3 = *(int *)(lVar5 + 0x20);
      if (iVar3 == 6) {
        (**(code **)*plVar8)(plVar8,lVar5 + 0x28);
      }
      else if (iVar3 == 7) {
        (**(code **)(*plVar8 + 8))(plVar8,*param_2 + uVar7 * 0x40 + 0x28);
      }
      uVar1 = (int)uVar7 + 1;
      uVar7 = (ulong)uVar1;
    } while (uVar1 < *(uint *)(param_2 + 1));
  }
  return 1;
}

// ==== IInfoBaseMap<unsigned long, Sphere211TreasureResultLotInfo>::DeserializeChild(Aska::ASON::AValue::AMap const*)
// vaddr 0x157b61c | ghidra 0x167b61c | size 596 | symbol _ZN12IInfoBaseMapIm30Sphere211TreasureResultLotInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN12IInfoBaseMapIm30Sphere211TreasureResultLotInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE
          (long *param_1,long *param_2)

{
  uint uVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined *puVar5;
  int iVar6;
  long *plVar7;
  long lVar8;
  long *plVar9;
  ulong uVar10;
  long *plVar11;
  long *plVar12;
  undefined *puStack_d0;
  undefined8 *puStack_c8;
  undefined8 auStack_c0 [2];
  undefined8 *puStack_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined *puStack_98;
  undefined8 uStack_90;
  undefined1 uStack_88;
  undefined1 auStack_80 [24];
  ulong uStack_68;
  
  plVar12 = param_1 + 8;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, Sphere211TreasureResultLotInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, Sphere211TreasureResultLotInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, Sphere211TreasureResultLotInfo>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, Sphere211TreasureResultLotInfo>, void*>*)(param_1 + 7,*plVar12);
  param_1[7] = (long)plVar12;
  param_1[8] = 0;
  param_1[9] = 0;
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0282d54e/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\Info/InfoBase.h"*/,0x1c1,&UNK_027dc58a/*"apParser is null."*/);
    iVar6 = iRam0000000000000008;
  }
  else {
    iVar6 = (int)param_2[1];
  }
  if (iVar6 != 0) {
    uVar10 = 0;
    puVar2 = PTR__ZTV30Sphere211TreasureResultLotInfo_02cc4858 + 0x10;
    puVar3 = PTR__ZTV22CParameterPropertyBaseILj306EE_02cc48a8 + 0x10;
    puVar4 = PTR__ZTV23CParameterPropertyValueIjLj306E18CPropertyConverterE_02cb91d0 + 0x10;
    puVar5 = PTR__ZTV8InfoBase_02cc49c8 + 0x10;
    do {
      uStack_68 = (**(code **)(*param_1 + 0x20))(param_1,*param_2 + uVar10 * 0x40);
      plVar7 = (long *)param_1[8];
      plVar9 = plVar12;
      if ((long *)param_1[8] == (long *)0x0) {
code_r0x0167b768:
        memset(auStack_c0,0,0x58);
        uStack_a8 = 0;
        uStack_a0 = 0;
        uStack_90 = 0;
        uStack_88 = 0;
        puStack_d0 = puVar2;
        puStack_c8 = auStack_c0;
        puStack_b0 = &uStack_a8;
        puStack_98 = puVar3;
        Framework::CHash32::CHash32()(auStack_80);
        puStack_98 = puVar4;
        lVar8 = std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned long, Sphere211TreasureResultLotInfo>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, Sphere211TreasureResultLotInfo>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, Sphere211TreasureResultLotInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, Sphere211TreasureResultLotInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, Sphere211TreasureResultLotInfo>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned long, unsigned long&, Sphere211TreasureResultLotInfo>(unsigned long const&, unsigned long&, Sphere211TreasureResultLotInfo&&)(param_1 + 7,&uStack_68,&uStack_68,&puStack_d0);
        puStack_d0 = puVar2;
        puStack_98 = puVar3;
        Framework::CHash32::~CHash32()(auStack_80);
        puStack_d0 = puVar5;
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*)(&puStack_b0,uStack_a8);
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*)(&puStack_c8,auStack_c0[0]);
        plVar11 = (long *)(lVar8 + 0x28);
        (**(code **)(*plVar11 + 0x10))(plVar11);
      }
      else {
        do {
          while (plVar11 = plVar7, (ulong)plVar11[4] < uStack_68) {
            plVar7 = (long *)plVar11[1];
            if ((long *)plVar11[1] == (long *)0x0) {
              plVar11 = plVar9;
              if (plVar9 != plVar12) goto code_r0x0167b74c;
              goto code_r0x0167b768;
            }
          }
          plVar7 = (long *)*plVar11;
          plVar9 = plVar11;
        } while ((long *)*plVar11 != (long *)0x0);
        if (plVar11 == plVar12) goto code_r0x0167b768;
code_r0x0167b74c:
        if ((uStack_68 < (ulong)plVar11[4]) || (plVar11 == plVar12)) goto code_r0x0167b768;
        plVar11 = plVar11 + 5;
      }
      lVar8 = *param_2 + uVar10 * 0x40;
      iVar6 = *(int *)(lVar8 + 0x20);
      if (iVar6 == 6) {
        (**(code **)*plVar11)(plVar11,lVar8 + 0x28);
      }
      else if (iVar6 == 7) {
        (**(code **)(*plVar11 + 8))(plVar11,*param_2 + uVar10 * 0x40 + 0x28);
      }
      uVar1 = (int)uVar10 + 1;
      uVar10 = (ulong)uVar1;
    } while (uVar1 < *(uint *)(param_2 + 1));
  }
  return 1;
}

// ==== IInfoBaseMap<unsigned long, Sphere211FloorAssetInfo>::DeserializeChild(Aska::ASON::AValue::AMap const*)
// vaddr 0x157c128 | ghidra 0x167c128 | size 436 | symbol _ZN12IInfoBaseMapIm23Sphere211FloorAssetInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN12IInfoBaseMapIm23Sphere211FloorAssetInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE
          (long *param_1,long *param_2)

{
  uint uVar1;
  int iVar2;
  long *plVar3;
  long lVar4;
  long *plVar5;
  ulong uVar6;
  long *plVar7;
  long *plVar8;
  undefined1 auStack_2b0 [616];
  ulong uStack_48;
  
  plVar8 = param_1 + 8;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, Sphere211FloorAssetInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, Sphere211FloorAssetInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, Sphere211FloorAssetInfo>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, Sphere211FloorAssetInfo>, void*>*)(param_1 + 7,*plVar8);
  param_1[7] = (long)plVar8;
  param_1[8] = 0;
  param_1[9] = 0;
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0282d54e/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\Info/InfoBase.h"*/,0x1c1,&UNK_027dc58a/*"apParser is null."*/);
    iVar2 = iRam0000000000000008;
  }
  else {
    iVar2 = (int)param_2[1];
  }
  if (iVar2 != 0) {
    uVar6 = 0;
    do {
      uStack_48 = (**(code **)(*param_1 + 0x20))(param_1,*param_2 + uVar6 * 0x40);
      plVar3 = (long *)param_1[8];
      plVar5 = plVar8;
      if ((long *)param_1[8] == (long *)0x0) {
code_r0x0167c21c:
        memset(auStack_2b0,0,0x268);
        Sphere211FloorAssetInfo::Sphere211FloorAssetInfo()(auStack_2b0);
        lVar4 = std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned long, Sphere211FloorAssetInfo>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, Sphere211FloorAssetInfo>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, Sphere211FloorAssetInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, Sphere211FloorAssetInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, Sphere211FloorAssetInfo>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned long, unsigned long&, Sphere211FloorAssetInfo>(unsigned long const&, unsigned long&, Sphere211FloorAssetInfo&&)(param_1 + 7,&uStack_48,&uStack_48,auStack_2b0);
        Sphere211FloorAssetInfo::~Sphere211FloorAssetInfo()(auStack_2b0);
        plVar7 = (long *)(lVar4 + 0x28);
        (**(code **)(*plVar7 + 0x10))(plVar7);
      }
      else {
        do {
          while (plVar7 = plVar3, (ulong)plVar7[4] < uStack_48) {
            plVar3 = (long *)plVar7[1];
            if ((long *)plVar7[1] == (long *)0x0) {
              plVar7 = plVar5;
              if (plVar5 != plVar8) goto code_r0x0167c200;
              goto code_r0x0167c21c;
            }
          }
          plVar3 = (long *)*plVar7;
          plVar5 = plVar7;
        } while ((long *)*plVar7 != (long *)0x0);
        if (plVar7 == plVar8) goto code_r0x0167c21c;
code_r0x0167c200:
        if ((uStack_48 < (ulong)plVar7[4]) || (plVar7 == plVar8)) goto code_r0x0167c21c;
        plVar7 = plVar7 + 5;
      }
      lVar4 = *param_2 + uVar6 * 0x40;
      iVar2 = *(int *)(lVar4 + 0x20);
      if (iVar2 == 6) {
        (**(code **)*plVar7)(plVar7,lVar4 + 0x28);
      }
      else if (iVar2 == 7) {
        (**(code **)(*plVar7 + 8))(plVar7,*param_2 + uVar6 * 0x40 + 0x28);
      }
      uVar1 = (int)uVar6 + 1;
      uVar6 = (ulong)uVar1;
    } while (uVar1 < *(uint *)(param_2 + 1));
  }
  return 1;
}

// ==== IInfoBaseMap<unsigned long, Sphere211CharacterInfo>::DeserializeChild(Aska::ASON::AValue::AMap const*)
// vaddr 0x157dd3c | ghidra 0x167dd3c | size 596 | symbol _ZN12IInfoBaseMapIm22Sphere211CharacterInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN12IInfoBaseMapIm22Sphere211CharacterInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE
          (long *param_1,long *param_2)

{
  uint uVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined *puVar5;
  int iVar6;
  long *plVar7;
  long lVar8;
  long *plVar9;
  ulong uVar10;
  long *plVar11;
  long *plVar12;
  undefined *puStack_d0;
  undefined8 *puStack_c8;
  undefined8 auStack_c0 [2];
  undefined8 *puStack_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined *puStack_98;
  undefined8 uStack_90;
  undefined1 uStack_88;
  undefined1 auStack_80 [24];
  ulong uStack_68;
  
  plVar12 = param_1 + 8;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, Sphere211CharacterInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, Sphere211CharacterInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, Sphere211CharacterInfo>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, Sphere211CharacterInfo>, void*>*)(param_1 + 7,*plVar12);
  param_1[7] = (long)plVar12;
  param_1[8] = 0;
  param_1[9] = 0;
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0282d54e/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\Info/InfoBase.h"*/,0x1c1,&UNK_027dc58a/*"apParser is null."*/);
    iVar6 = iRam0000000000000008;
  }
  else {
    iVar6 = (int)param_2[1];
  }
  if (iVar6 != 0) {
    uVar10 = 0;
    puVar2 = PTR__ZTV22Sphere211CharacterInfo_02cbb7d0 + 0x10;
    puVar3 = PTR__ZTV22CParameterPropertyBaseILj18EE_02cbe238 + 0x10;
    puVar4 = PTR__ZTV23CParameterPropertyValueIjLj18E18CPropertyConverterE_02cbcd58 + 0x10;
    puVar5 = PTR__ZTV8InfoBase_02cc49c8 + 0x10;
    do {
      uStack_68 = (**(code **)(*param_1 + 0x20))(param_1,*param_2 + uVar10 * 0x40);
      plVar7 = (long *)param_1[8];
      plVar9 = plVar12;
      if ((long *)param_1[8] == (long *)0x0) {
code_r0x0167de88:
        memset(auStack_c0,0,0x58);
        uStack_a8 = 0;
        uStack_a0 = 0;
        uStack_90 = 0;
        uStack_88 = 0;
        puStack_d0 = puVar2;
        puStack_c8 = auStack_c0;
        puStack_b0 = &uStack_a8;
        puStack_98 = puVar3;
        Framework::CHash32::CHash32()(auStack_80);
        puStack_98 = puVar4;
        lVar8 = std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned long, Sphere211CharacterInfo>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, Sphere211CharacterInfo>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, Sphere211CharacterInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, Sphere211CharacterInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, Sphere211CharacterInfo>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned long, unsigned long&, Sphere211CharacterInfo>(unsigned long const&, unsigned long&, Sphere211CharacterInfo&&)(param_1 + 7,&uStack_68,&uStack_68,&puStack_d0);
        puStack_d0 = puVar2;
        puStack_98 = puVar3;
        Framework::CHash32::~CHash32()(auStack_80);
        puStack_d0 = puVar5;
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*)(&puStack_b0,uStack_a8);
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*)(&puStack_c8,auStack_c0[0]);
        plVar11 = (long *)(lVar8 + 0x28);
        (**(code **)(*plVar11 + 0x10))(plVar11);
      }
      else {
        do {
          while (plVar11 = plVar7, (ulong)plVar11[4] < uStack_68) {
            plVar7 = (long *)plVar11[1];
            if ((long *)plVar11[1] == (long *)0x0) {
              plVar11 = plVar9;
              if (plVar9 != plVar12) goto code_r0x0167de6c;
              goto code_r0x0167de88;
            }
          }
          plVar7 = (long *)*plVar11;
          plVar9 = plVar11;
        } while ((long *)*plVar11 != (long *)0x0);
        if (plVar11 == plVar12) goto code_r0x0167de88;
code_r0x0167de6c:
        if ((uStack_68 < (ulong)plVar11[4]) || (plVar11 == plVar12)) goto code_r0x0167de88;
        plVar11 = plVar11 + 5;
      }
      lVar8 = *param_2 + uVar10 * 0x40;
      iVar6 = *(int *)(lVar8 + 0x20);
      if (iVar6 == 6) {
        (**(code **)*plVar11)(plVar11,lVar8 + 0x28);
      }
      else if (iVar6 == 7) {
        (**(code **)(*plVar11 + 8))(plVar11,*param_2 + uVar10 * 0x40 + 0x28);
      }
      uVar1 = (int)uVar10 + 1;
      uVar10 = (ulong)uVar1;
    } while (uVar1 < *(uint *)(param_2 + 1));
  }
  return 1;
}

// ==== IInfoBaseMap<unsigned long, Sphere211RentalCharacterInfo>::DeserializeChild(Aska::ASON::AValue::AMap const*)
// vaddr 0x157e57c | ghidra 0x167e57c | size 1216 | symbol _ZN12IInfoBaseMapIm28Sphere211RentalCharacterInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Type propagation algorithm not settling */

undefined8
_ZN12IInfoBaseMapIm28Sphere211RentalCharacterInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE
          (long *param_1,long *param_2)

{
  uint uVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined *puVar5;
  undefined *puVar6;
  undefined *puVar7;
  undefined *puVar8;
  undefined *puVar9;
  undefined *puVar10;
  undefined *puVar11;
  long lVar12;
  int iVar13;
  long *plVar14;
  long *******ppppppplVar15;
  long *******ppppppplVar16;
  ulong uVar17;
  long *******ppppppplVar18;
  long *******ppppppplVar19;
  long *******ppppppplVar20;
  undefined *puStack_190;
  undefined8 *puStack_188;
  undefined8 auStack_180 [2];
  undefined8 *puStack_170;
  undefined8 uStack_168;
  undefined8 uStack_160;
  undefined *puStack_158;
  undefined8 uStack_150;
  undefined1 uStack_148;
  undefined1 auStack_140 [24];
  undefined *puStack_128;
  undefined8 uStack_120;
  undefined1 uStack_118;
  undefined1 auStack_110 [24];
  undefined *puStack_f8;
  undefined8 uStack_f0;
  undefined1 uStack_e8;
  undefined1 auStack_e0 [24];
  undefined *puStack_c8;
  undefined8 uStack_c0;
  undefined1 uStack_b8;
  undefined1 auStack_b0 [16];
  ulong uStack_a0;
  undefined8 uStack_98;
  undefined8 uStack_90;
  long ******pppppplStack_88;
  long *******appppppplStack_80 [3];
  long *******ppppppplStack_68;
  
  ppppppplVar18 = (long *******)(param_1 + 8);
  plVar14 = param_1 + 7;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, Sphere211RentalCharacterInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, Sphere211RentalCharacterInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, Sphere211RentalCharacterInfo>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, Sphere211RentalCharacterInfo>, void*>*)(plVar14,*ppppppplVar18);
  param_1[7] = (long)ppppppplVar18;
  param_1[8] = 0;
  param_1[9] = 0;
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0282d54e/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\Info/InfoBase.h"*/,0x1c1,&UNK_027dc58a/*"apParser is null."*/);
    iVar13 = iRam0000000000000008;
  }
  else {
    iVar13 = (int)param_2[1];
  }
  if (iVar13 != 0) {
    puVar2 = PTR__ZTV28Sphere211RentalCharacterInfo_02cba788 + 0x10;
    puVar3 = PTR__ZTV22CParameterPropertyBaseILj263EE_02cb7a90 + 0x10;
    puVar4 = PTR__ZTV23CParameterPropertyValueIjLj263E18CPropertyConverterE_02cc4638 + 0x10;
    puVar5 = PTR__ZTV22CParameterPropertyBaseILj264EE_02cbf5f8 + 0x10;
    puVar6 = PTR__ZTV23CParameterPropertyValueIjLj264E18CPropertyConverterE_02cbd4b0 + 0x10;
    puVar7 = PTR__ZTV22CParameterPropertyBaseILj265EE_02cbe760 + 0x10;
    puVar8 = PTR__ZTV23CParameterPropertyValueIjLj265E18CPropertyConverterE_02cc2190 + 0x10;
    puVar9 = PTR__ZTV22CParameterPropertyBaseILj266EE_02cc27f0 + 0x10;
    puVar10 = PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj266EE_02cb9988
              + 0x10;
    uVar17 = 0;
    puVar11 = PTR__ZTV8InfoBase_02cc49c8 + 0x10;
    do {
      pppppplStack_88 =
           (long ******)(**(code **)(*param_1 + 0x20))(param_1,*param_2 + uVar17 * 0x40);
      ppppppplVar16 = (long *******)param_1[8];
      ppppppplVar15 = ppppppplVar18;
      if ((long *******)param_1[8] == (long *******)0x0) {
code_r0x0167e754:
        memset(auStack_180,0,0xf8);
        uStack_168 = 0;
        uStack_160 = 0;
        uStack_148 = 0;
        uStack_150 = 0;
        puStack_190 = puVar2;
        puStack_188 = auStack_180;
        puStack_170 = &uStack_168;
        puStack_158 = puVar3;
        Framework::CHash32::CHash32()(auStack_140);
        uStack_118 = 0;
        uStack_120 = 0;
        puStack_158 = puVar4;
        puStack_128 = puVar5;
        Framework::CHash32::CHash32()(auStack_110);
        uStack_e8 = 0;
        uStack_f0 = 0;
        puStack_128 = puVar6;
        puStack_f8 = puVar7;
        Framework::CHash32::CHash32()(auStack_e0);
        uStack_b8 = 0;
        uStack_c0 = 0;
        puStack_f8 = puVar8;
        puStack_c8 = puVar9;
        Framework::CHash32::CHash32()(auStack_b0);
        uStack_98 = 0;
        uStack_90 = 0;
        uStack_a0 = 0;
        ppppppplVar16 = (long *******)*ppppppplVar18;
        if ((long *******)*ppppppplVar18 == (long *******)0x0) {
          ppppppplVar20 = (long *******)*ppppppplVar18;
          ppppppplVar15 = ppppppplVar18;
          ppppppplVar19 = ppppppplVar18;
        }
        else {
          do {
            while (ppppppplVar15 = ppppppplVar16, ppppppplVar15[4] <= pppppplStack_88) {
              if (pppppplStack_88 <= ppppppplVar15[4]) {
                ppppppplVar19 = (long *******)&ppppppplStack_68;
                ppppppplVar20 = ppppppplVar15;
                goto joined_r0x0167e8a0;
              }
              ppppppplVar19 = ppppppplVar15 + 1;
              ppppppplVar16 = (long *******)*ppppppplVar19;
              if ((long *******)*ppppppplVar19 == (long *******)0x0) {
                ppppppplVar20 = (long *******)*ppppppplVar19;
                goto joined_r0x0167e8a0;
              }
            }
            ppppppplVar16 = (long *******)*ppppppplVar15;
          } while ((long *******)*ppppppplVar15 != (long *******)0x0);
          ppppppplVar20 = (long *******)*ppppppplVar15;
          ppppppplVar19 = ppppppplVar15;
        }
joined_r0x0167e8a0:
        ppppppplStack_68 = ppppppplVar15;
        if (ppppppplVar20 == (long *******)0x0) {
          puStack_c8 = puVar10;
          std::__ndk1::unique_ptr<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, Sphere211RentalCharacterInfo>, void*>, std::__ndk1::__tree_node_destructor<Framework::CSTLAllocator<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, Sphere211RentalCharacterInfo>, void*>, Framework::CSTLMapAllocatorInf> > > std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, Sphere211RentalCharacterInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, Sphere211RentalCharacterInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, Sphere211RentalCharacterInfo>, Framework::CSTLMapAllocatorInf> >::__construct_node<unsigned long&, Sphere211RentalCharacterInfo>(unsigned long&, Sphere211RentalCharacterInfo&&)(appppppplStack_80,plVar14,&pppppplStack_88,&puStack_190);
          *appppppplStack_80[0] = (long ******)0x0;
          appppppplStack_80[0][1] = (long ******)0x0;
          appppppplStack_80[0][2] = (long ******)ppppppplVar15;
          *ppppppplVar19 = (long ******)appppppplStack_80[0];
          ppppppplVar16 = appppppplStack_80[0];
          if (*(long *)*plVar14 != 0) {
            *plVar14 = *(long *)*plVar14;
            ppppppplVar16 = (long *******)*ppppppplVar19;
          }
          void std::__ndk1::__tree_balance_after_insert<std::__ndk1::__tree_node_base<void*>*>(std::__ndk1::__tree_node_base<void*>*, std::__ndk1::__tree_node_base<void*>*)(param_1[8],ppppppplVar16);
          ppppppplVar20 = appppppplStack_80[0];
          param_1[9] = param_1[9] + 1;
          puStack_190 = PTR__ZTV28Sphere211RentalCharacterInfo_02cba788 + 0x10;
          puStack_c8 = PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj266EE_02cb9988
                       + 0x10;
          if ((uStack_a0 & 1) != 0) {
            Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_90);
          }
        }
        else {
          puStack_190 = PTR__ZTV28Sphere211RentalCharacterInfo_02cba788 + 0x10;
        }
        puStack_c8 = PTR__ZTV22CParameterPropertyBaseILj266EE_02cc27f0 + 0x10;
        Framework::CHash32::~CHash32()(auStack_b0);
        puStack_f8 = PTR__ZTV22CParameterPropertyBaseILj265EE_02cbe760 + 0x10;
        Framework::CHash32::~CHash32()(auStack_e0);
        puStack_128 = PTR__ZTV22CParameterPropertyBaseILj264EE_02cbf5f8 + 0x10;
        Framework::CHash32::~CHash32()(auStack_110);
        puStack_158 = PTR__ZTV22CParameterPropertyBaseILj263EE_02cb7a90 + 0x10;
        Framework::CHash32::~CHash32()(auStack_140);
        puStack_190 = puVar11;
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*)(&puStack_170,uStack_168);
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*)(&puStack_188,auStack_180[0]);
        ppppppplVar20 = ppppppplVar20 + 5;
        (*(code *)(*ppppppplVar20)[2])(ppppppplVar20);
      }
      else {
        do {
          while (ppppppplVar20 = ppppppplVar16, ppppppplVar20[4] < pppppplStack_88) {
            ppppppplVar16 = (long *******)ppppppplVar20[1];
            if ((long *******)ppppppplVar20[1] == (long *******)0x0) {
              ppppppplVar20 = ppppppplVar15;
              if (ppppppplVar15 != ppppppplVar18) goto code_r0x0167e738;
              goto code_r0x0167e754;
            }
          }
          ppppppplVar16 = (long *******)*ppppppplVar20;
          ppppppplVar15 = ppppppplVar20;
        } while ((long *******)*ppppppplVar20 != (long *******)0x0);
        if (ppppppplVar20 == ppppppplVar18) goto code_r0x0167e754;
code_r0x0167e738:
        if ((pppppplStack_88 < ppppppplVar20[4]) || (ppppppplVar20 == ppppppplVar18))
        goto code_r0x0167e754;
        ppppppplVar20 = ppppppplVar20 + 5;
      }
      lVar12 = *param_2 + uVar17 * 0x40;
      iVar13 = *(int *)(lVar12 + 0x20);
      if (iVar13 == 6) {
        (*(code *)**ppppppplVar20)(ppppppplVar20,lVar12 + 0x28);
      }
      else if (iVar13 == 7) {
        (*(code *)(*ppppppplVar20)[1])(ppppppplVar20,*param_2 + uVar17 * 0x40 + 0x28);
      }
      uVar1 = (int)uVar17 + 1;
      uVar17 = (ulong)uVar1;
    } while (uVar1 < *(uint *)(param_2 + 1));
  }
  return 1;
}

// ==== IInfoBaseMap<unsigned long, Sphere211RankingInfo>::DeserializeChild(Aska::ASON::AValue::AMap const*)
// vaddr 0x157ef1c | ghidra 0x167ef1c | size 1028 | symbol _ZN12IInfoBaseMapIm20Sphere211RankingInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Type propagation algorithm not settling */

undefined8
_ZN12IInfoBaseMapIm20Sphere211RankingInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE
          (long *param_1,long *param_2)

{
  uint uVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined *puVar5;
  undefined *puVar6;
  undefined *puVar7;
  undefined *puVar8;
  undefined *puVar9;
  undefined *puVar10;
  undefined *puVar11;
  undefined *puVar12;
  long lVar13;
  int iVar14;
  long *plVar15;
  long *******ppppppplVar16;
  long *******ppppppplVar17;
  ulong uVar18;
  long *******ppppppplVar19;
  long *******ppppppplVar20;
  long *******ppppppplVar21;
  undefined *puStack_1c0;
  undefined1 *puStack_1b8;
  undefined1 auStack_1b0 [16];
  undefined8 *puStack_1a0;
  undefined8 uStack_198;
  undefined8 uStack_190;
  undefined *puStack_188;
  undefined8 uStack_180;
  undefined1 uStack_178;
  undefined1 auStack_170 [24];
  undefined *puStack_158;
  undefined8 uStack_150;
  undefined1 uStack_148;
  undefined1 auStack_140 [24];
  undefined *puStack_128;
  undefined8 uStack_120;
  undefined1 uStack_118;
  undefined1 auStack_110 [24];
  undefined *puStack_f8;
  undefined8 uStack_f0;
  undefined1 uStack_e8;
  undefined1 auStack_e0 [24];
  undefined *puStack_c8;
  undefined8 uStack_c0;
  undefined1 uStack_b8;
  undefined1 auStack_b0 [16];
  undefined8 uStack_a0;
  undefined8 uStack_98;
  undefined8 uStack_90;
  long ******pppppplStack_88;
  long *******appppppplStack_80 [3];
  long *******ppppppplStack_68;
  
  ppppppplVar21 = (long *******)(param_1 + 8);
  plVar15 = param_1 + 7;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, Sphere211RankingInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, Sphere211RankingInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, Sphere211RankingInfo>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, Sphere211RankingInfo>, void*>*)(plVar15,*ppppppplVar21);
  param_1[7] = (long)ppppppplVar21;
  param_1[8] = 0;
  param_1[9] = 0;
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0282d54e/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\Info/InfoBase.h"*/,0x1c1,&UNK_027dc58a/*"apParser is null."*/);
    iVar14 = iRam0000000000000008;
  }
  else {
    iVar14 = (int)param_2[1];
  }
  if (iVar14 != 0) {
    puVar2 = PTR__ZTV20Sphere211RankingInfo_02cc2a60 + 0x10;
    puVar3 = PTR__ZTV22CParameterPropertyBaseILj465EE_02cbd660 + 0x10;
    puVar4 = PTR__ZTV23CParameterPropertyValueIjLj465E18CPropertyConverterE_02cb9de0 + 0x10;
    puVar5 = PTR__ZTV22CParameterPropertyBaseILj466EE_02cc1c90 + 0x10;
    puVar6 = PTR__ZTV23CParameterPropertyValueIjLj466E18CPropertyConverterE_02cbe1f0 + 0x10;
    puVar7 = PTR__ZTV22CParameterPropertyBaseILj467EE_02cbdc08 + 0x10;
    puVar8 = PTR__ZTV23CParameterPropertyValueIjLj467E18CPropertyConverterE_02cb99b8 + 0x10;
    puVar9 = PTR__ZTV22CParameterPropertyBaseILj468EE_02cb98d8 + 0x10;
    puVar10 = PTR__ZTV23CParameterPropertyValueIjLj468E18CPropertyConverterE_02cbe0d0 + 0x10;
    uVar18 = 0;
    puVar11 = PTR__ZTV22CParameterPropertyBaseILj469EE_02cc1208 + 0x10;
    puVar12 = PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj469EE_02cc2480
              + 0x10;
    do {
      pppppplStack_88 =
           (long ******)(**(code **)(*param_1 + 0x20))(param_1,*param_2 + uVar18 * 0x40);
      ppppppplVar17 = (long *******)param_1[8];
      ppppppplVar16 = ppppppplVar21;
      if ((long *******)param_1[8] == (long *******)0x0) {
code_r0x0167f0f8:
        memset(auStack_1b0,0,0x128);
        uStack_198 = 0;
        uStack_190 = 0;
        uStack_178 = 0;
        uStack_180 = 0;
        puStack_1c0 = puVar2;
        puStack_1b8 = auStack_1b0;
        puStack_1a0 = &uStack_198;
        puStack_188 = puVar3;
        Framework::CHash32::CHash32()(auStack_170);
        uStack_148 = 0;
        uStack_150 = 0;
        puStack_188 = puVar4;
        puStack_158 = puVar5;
        Framework::CHash32::CHash32()(auStack_140);
        uStack_118 = 0;
        uStack_120 = 0;
        puStack_158 = puVar6;
        puStack_128 = puVar7;
        Framework::CHash32::CHash32()(auStack_110);
        uStack_e8 = 0;
        uStack_f0 = 0;
        puStack_128 = puVar8;
        puStack_f8 = puVar9;
        Framework::CHash32::CHash32()(auStack_e0);
        uStack_b8 = 0;
        uStack_c0 = 0;
        puStack_f8 = puVar10;
        puStack_c8 = puVar11;
        Framework::CHash32::CHash32()(auStack_b0);
        uStack_98 = 0;
        uStack_90 = 0;
        uStack_a0 = 0;
        ppppppplVar17 = (long *******)*ppppppplVar21;
        if ((long *******)*ppppppplVar21 == (long *******)0x0) {
          ppppppplVar20 = (long *******)*ppppppplVar21;
          ppppppplVar16 = ppppppplVar21;
          ppppppplVar19 = ppppppplVar21;
        }
        else {
          do {
            while (ppppppplVar16 = ppppppplVar17, ppppppplVar16[4] <= pppppplStack_88) {
              if (pppppplStack_88 <= ppppppplVar16[4]) {
                ppppppplVar20 = ppppppplVar16;
                ppppppplVar19 = (long *******)&ppppppplStack_68;
                goto joined_r0x0167f21c;
              }
              ppppppplVar19 = ppppppplVar16 + 1;
              ppppppplVar17 = (long *******)*ppppppplVar19;
              if ((long *******)*ppppppplVar19 == (long *******)0x0) {
                ppppppplVar20 = (long *******)*ppppppplVar19;
                goto joined_r0x0167f21c;
              }
            }
            ppppppplVar17 = (long *******)*ppppppplVar16;
          } while ((long *******)*ppppppplVar16 != (long *******)0x0);
          ppppppplVar20 = (long *******)*ppppppplVar16;
          ppppppplVar19 = ppppppplVar16;
        }
joined_r0x0167f21c:
        puStack_c8 = puVar12;
        ppppppplStack_68 = ppppppplVar16;
        if (ppppppplVar20 == (long *******)0x0) {
          std::__ndk1::unique_ptr<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, Sphere211RankingInfo>, void*>, std::__ndk1::__tree_node_destructor<Framework::CSTLAllocator<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, Sphere211RankingInfo>, void*>, Framework::CSTLMapAllocatorInf> > > std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, Sphere211RankingInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, Sphere211RankingInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, Sphere211RankingInfo>, Framework::CSTLMapAllocatorInf> >::__construct_node<unsigned long&, Sphere211RankingInfo>(unsigned long&, Sphere211RankingInfo&&)(appppppplStack_80,plVar15,&pppppplStack_88,&puStack_1c0);
          *appppppplStack_80[0] = (long ******)0x0;
          appppppplStack_80[0][1] = (long ******)0x0;
          appppppplStack_80[0][2] = (long ******)ppppppplVar16;
          *ppppppplVar19 = (long ******)appppppplStack_80[0];
          ppppppplVar17 = appppppplStack_80[0];
          if (*(long *)*plVar15 != 0) {
            *plVar15 = *(long *)*plVar15;
            ppppppplVar17 = (long *******)*ppppppplVar19;
          }
          void std::__ndk1::__tree_balance_after_insert<std::__ndk1::__tree_node_base<void*>*>(std::__ndk1::__tree_node_base<void*>*, std::__ndk1::__tree_node_base<void*>*)(param_1[8],ppppppplVar17);
          param_1[9] = param_1[9] + 1;
          ppppppplVar20 = appppppplStack_80[0];
        }
        Sphere211RankingInfo::~Sphere211RankingInfo()(&puStack_1c0);
        ppppppplVar20 = ppppppplVar20 + 5;
        (*(code *)(*ppppppplVar20)[2])(ppppppplVar20);
      }
      else {
        do {
          while (ppppppplVar20 = ppppppplVar17, ppppppplVar20[4] < pppppplStack_88) {
            ppppppplVar17 = (long *******)ppppppplVar20[1];
            if ((long *******)ppppppplVar20[1] == (long *******)0x0) {
              ppppppplVar20 = ppppppplVar16;
              if (ppppppplVar16 != ppppppplVar21) goto code_r0x0167f0dc;
              goto code_r0x0167f0f8;
            }
          }
          ppppppplVar17 = (long *******)*ppppppplVar20;
          ppppppplVar16 = ppppppplVar20;
        } while ((long *******)*ppppppplVar20 != (long *******)0x0);
        if (ppppppplVar20 == ppppppplVar21) goto code_r0x0167f0f8;
code_r0x0167f0dc:
        if ((pppppplStack_88 < ppppppplVar20[4]) || (ppppppplVar20 == ppppppplVar21))
        goto code_r0x0167f0f8;
        ppppppplVar20 = ppppppplVar20 + 5;
      }
      lVar13 = *param_2 + uVar18 * 0x40;
      iVar14 = *(int *)(lVar13 + 0x20);
      if (iVar14 == 6) {
        (*(code *)**ppppppplVar20)(ppppppplVar20,lVar13 + 0x28);
      }
      else if (iVar14 == 7) {
        (*(code *)(*ppppppplVar20)[1])(ppppppplVar20,*param_2 + uVar18 * 0x40 + 0x28);
      }
      uVar1 = (int)uVar18 + 1;
      uVar18 = (ulong)uVar1;
    } while (uVar1 < *(uint *)(param_2 + 1));
  }
  return 1;
}

// ==== IInfoBaseMap<unsigned long, CDebugSphere211CommonDropIdList>::DeserializeChild(Aska::ASON::AValue::AMap const*)
// vaddr 0x1580dc8 | ghidra 0x1680dc8 | size 612 | symbol _ZN12IInfoBaseMapIm31CDebugSphere211CommonDropIdListE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN12IInfoBaseMapIm31CDebugSphere211CommonDropIdListE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE
          (long *param_1,long *param_2)

{
  uint uVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  long lVar5;
  int iVar6;
  long lVar7;
  long *plVar8;
  long lVar9;
  long *plVar10;
  ulong uVar11;
  long *plVar12;
  long *plVar13;
  undefined *puStack_b8;
  undefined8 *puStack_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined8 *puStack_98;
  undefined8 uStack_90;
  undefined8 uStack_88;
  long lStack_80;
  long lStack_78;
  undefined8 uStack_70;
  ulong uStack_68;
  
  plVar13 = param_1 + 8;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CDebugSphere211CommonDropIdList>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CDebugSphere211CommonDropIdList>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CDebugSphere211CommonDropIdList>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CDebugSphere211CommonDropIdList>, void*>*)(param_1 + 7,*plVar13);
  param_1[7] = (long)plVar13;
  param_1[8] = 0;
  param_1[9] = 0;
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0282d54e/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\Info/InfoBase.h"*/,0x1c1,&UNK_027dc58a/*"apParser is null."*/);
    iVar6 = iRam0000000000000008;
  }
  else {
    iVar6 = (int)param_2[1];
  }
  if (iVar6 != 0) {
    puVar2 = PTR__ZTV31CDebugSphere211CommonDropIdList_02cbaae0 + 0x10;
    uVar11 = 0;
    puVar3 = PTR__ZTV8InfoBase_02cc49c8 + 0x10;
    puVar4 = PTR__ZTV22CParameterPropertyBaseILj505EE_02cb9fb8 + 0x10;
    do {
      uStack_68 = (**(code **)(*param_1 + 0x20))(param_1,*param_2 + uVar11 * 0x40);
      plVar8 = (long *)param_1[8];
      plVar10 = plVar13;
      if ((long *)param_1[8] == (long *)0x0) {
code_r0x01680f08:
        uStack_a8 = 0;
        uStack_a0 = 0;
        uStack_90 = 0;
        uStack_88 = 0;
        lStack_78 = 0;
        uStack_70 = 0;
        lStack_80 = 0;
        puStack_b8 = puVar2;
        puStack_b0 = &uStack_a8;
        puStack_98 = &uStack_90;
        lVar9 = std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned long, CDebugSphere211CommonDropIdList>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CDebugSphere211CommonDropIdList>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CDebugSphere211CommonDropIdList>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CDebugSphere211CommonDropIdList>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CDebugSphere211CommonDropIdList>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned long, unsigned long&, CDebugSphere211CommonDropIdList>(unsigned long const&, unsigned long&, CDebugSphere211CommonDropIdList&&)(param_1 + 7,&uStack_68,&uStack_68,&puStack_b8);
        lVar7 = lStack_80;
        lVar5 = lStack_78;
        if (lStack_80 != 0) {
          while (lVar5 != lVar7) {
            lStack_78 = lVar5 + -0x30;
            *(undefined **)(lVar5 + -0x30) = puVar4;
            Framework::CHash32::~CHash32()(lVar5 + -0x18);
            lVar5 = lStack_78;
          }
          lStack_78 = lVar5;
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(lStack_80);
        }
        puStack_b8 = puVar3;
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*)(&puStack_98,uStack_90);
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*)(&puStack_b0,uStack_a8);
        plVar12 = (long *)(lVar9 + 0x28);
        (**(code **)(*plVar12 + 0x10))(plVar12);
      }
      else {
        do {
          while (plVar12 = plVar8, uStack_68 <= (ulong)plVar12[4]) {
            plVar8 = (long *)*plVar12;
            plVar10 = plVar12;
            if ((long *)*plVar12 == (long *)0x0) {
              if (plVar12 != plVar13) goto code_r0x01680eec;
              goto code_r0x01680f08;
            }
          }
          plVar8 = (long *)plVar12[1];
        } while ((long *)plVar12[1] != (long *)0x0);
        plVar12 = plVar10;
        if (plVar10 == plVar13) goto code_r0x01680f08;
code_r0x01680eec:
        if ((uStack_68 < (ulong)plVar12[4]) || (plVar12 == plVar13)) goto code_r0x01680f08;
        plVar12 = plVar12 + 5;
      }
      lVar5 = *param_2 + uVar11 * 0x40;
      iVar6 = *(int *)(lVar5 + 0x20);
      if (iVar6 == 6) {
        (**(code **)*plVar12)(plVar12,lVar5 + 0x28);
      }
      else if (iVar6 == 7) {
        (**(code **)(*plVar12 + 8))(plVar12,*param_2 + uVar11 * 0x40 + 0x28);
      }
      uVar1 = (int)uVar11 + 1;
      uVar11 = (ulong)uVar1;
    } while (uVar1 < *(uint *)(param_2 + 1));
  }
  return 1;
}

// ==== IInfoBaseMap<unsigned long, CUniverseBoardIdList>::DeserializeChild(Aska::ASON::AValue::AMap const*)
// vaddr 0x15826bc | ghidra 0x16826bc | size 612 | symbol _ZN12IInfoBaseMapIm20CUniverseBoardIdListE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN12IInfoBaseMapIm20CUniverseBoardIdListE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE
          (long *param_1,long *param_2)

{
  uint uVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  long lVar5;
  int iVar6;
  long lVar7;
  long *plVar8;
  long lVar9;
  long *plVar10;
  ulong uVar11;
  long *plVar12;
  long *plVar13;
  undefined *puStack_b8;
  undefined8 *puStack_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined8 *puStack_98;
  undefined8 uStack_90;
  undefined8 uStack_88;
  long lStack_80;
  long lStack_78;
  undefined8 uStack_70;
  ulong uStack_68;
  
  plVar13 = param_1 + 8;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CUniverseBoardIdList>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CUniverseBoardIdList>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CUniverseBoardIdList>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CUniverseBoardIdList>, void*>*)(param_1 + 7,*plVar13);
  param_1[7] = (long)plVar13;
  param_1[8] = 0;
  param_1[9] = 0;
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0282d54e/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\Info/InfoBase.h"*/,0x1c1,&UNK_027dc58a/*"apParser is null."*/);
    iVar6 = iRam0000000000000008;
  }
  else {
    iVar6 = (int)param_2[1];
  }
  if (iVar6 != 0) {
    puVar2 = PTR__ZTV20CUniverseBoardIdList_02cbf438 + 0x10;
    uVar11 = 0;
    puVar3 = PTR__ZTV8InfoBase_02cc49c8 + 0x10;
    puVar4 = PTR__ZTV22CParameterPropertyBaseILj40EE_02cbd2c0 + 0x10;
    do {
      uStack_68 = (**(code **)(*param_1 + 0x20))(param_1,*param_2 + uVar11 * 0x40);
      plVar8 = (long *)param_1[8];
      plVar10 = plVar13;
      if ((long *)param_1[8] == (long *)0x0) {
code_r0x016827fc:
        uStack_a8 = 0;
        uStack_a0 = 0;
        uStack_90 = 0;
        uStack_88 = 0;
        lStack_78 = 0;
        uStack_70 = 0;
        lStack_80 = 0;
        puStack_b8 = puVar2;
        puStack_b0 = &uStack_a8;
        puStack_98 = &uStack_90;
        lVar9 = std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned long, CUniverseBoardIdList>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CUniverseBoardIdList>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CUniverseBoardIdList>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CUniverseBoardIdList>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CUniverseBoardIdList>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned long, unsigned long&, CUniverseBoardIdList>(unsigned long const&, unsigned long&, CUniverseBoardIdList&&)(param_1 + 7,&uStack_68,&uStack_68,&puStack_b8);
        lVar7 = lStack_80;
        lVar5 = lStack_78;
        if (lStack_80 != 0) {
          while (lVar5 != lVar7) {
            lStack_78 = lVar5 + -0x30;
            *(undefined **)(lVar5 + -0x30) = puVar4;
            Framework::CHash32::~CHash32()(lVar5 + -0x18);
            lVar5 = lStack_78;
          }
          lStack_78 = lVar5;
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(lStack_80);
        }
        puStack_b8 = puVar3;
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*)(&puStack_98,uStack_90);
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*)(&puStack_b0,uStack_a8);
        plVar12 = (long *)(lVar9 + 0x28);
        (**(code **)(*plVar12 + 0x10))(plVar12);
      }
      else {
        do {
          while (plVar12 = plVar8, uStack_68 <= (ulong)plVar12[4]) {
            plVar8 = (long *)*plVar12;
            plVar10 = plVar12;
            if ((long *)*plVar12 == (long *)0x0) {
              if (plVar12 != plVar13) goto code_r0x016827e0;
              goto code_r0x016827fc;
            }
          }
          plVar8 = (long *)plVar12[1];
        } while ((long *)plVar12[1] != (long *)0x0);
        plVar12 = plVar10;
        if (plVar10 == plVar13) goto code_r0x016827fc;
code_r0x016827e0:
        if ((uStack_68 < (ulong)plVar12[4]) || (plVar12 == plVar13)) goto code_r0x016827fc;
        plVar12 = plVar12 + 5;
      }
      lVar5 = *param_2 + uVar11 * 0x40;
      iVar6 = *(int *)(lVar5 + 0x20);
      if (iVar6 == 6) {
        (**(code **)*plVar12)(plVar12,lVar5 + 0x28);
      }
      else if (iVar6 == 7) {
        (**(code **)(*plVar12 + 8))(plVar12,*param_2 + uVar11 * 0x40 + 0x28);
      }
      uVar1 = (int)uVar11 + 1;
      uVar11 = (ulong)uVar1;
    } while (uVar1 < *(uint *)(param_2 + 1));
  }
  return 1;
}

// ==== IInfoBaseMap<unsigned long, UniverseAddStatusInfo>::DeserializeChild(Aska::ASON::AValue::AMap const*)
// vaddr 0x15840f0 | ghidra 0x16840f0 | size 1360 | symbol _ZN12IInfoBaseMapIm21UniverseAddStatusInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN12IInfoBaseMapIm21UniverseAddStatusInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE
          (long *param_1,long *param_2)

{
  long *plVar1;
  uint uVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined *puVar5;
  undefined *puVar6;
  undefined *puVar7;
  undefined *puVar8;
  undefined *puVar9;
  undefined *puVar10;
  undefined *puVar11;
  undefined *puVar12;
  undefined *puVar13;
  undefined *puVar14;
  undefined *puVar15;
  undefined *puVar16;
  undefined *puVar17;
  undefined *puVar18;
  undefined *puVar19;
  undefined *puVar20;
  undefined *puVar21;
  undefined *puVar22;
  int iVar23;
  long *plVar24;
  long lVar25;
  long *plVar26;
  ulong uVar27;
  long *plVar28;
  long *plVar29;
  undefined *puStack_250;
  undefined8 *puStack_248;
  undefined8 auStack_240 [2];
  undefined8 *puStack_230;
  undefined8 uStack_228;
  undefined8 uStack_220;
  undefined *puStack_218;
  undefined8 uStack_210;
  undefined1 uStack_208;
  undefined1 auStack_200 [24];
  undefined *puStack_1e8;
  undefined8 uStack_1e0;
  undefined1 uStack_1d8;
  undefined1 auStack_1d0 [24];
  undefined *puStack_1b8;
  undefined8 uStack_1b0;
  undefined1 uStack_1a8;
  undefined1 auStack_1a0 [24];
  undefined *puStack_188;
  undefined8 uStack_180;
  undefined1 uStack_178;
  undefined1 auStack_170 [24];
  undefined *puStack_158;
  undefined8 uStack_150;
  undefined1 uStack_148;
  undefined1 auStack_140 [24];
  undefined *puStack_128;
  undefined8 uStack_120;
  undefined1 uStack_118;
  undefined1 auStack_110 [24];
  undefined *puStack_f8;
  undefined8 uStack_f0;
  undefined1 uStack_e8;
  undefined1 auStack_e0 [24];
  undefined *puStack_c8;
  undefined8 uStack_c0;
  undefined1 uStack_b8;
  undefined1 auStack_b0 [24];
  undefined *puStack_98;
  undefined8 uStack_90;
  undefined1 uStack_88;
  undefined1 auStack_80 [24];
  ulong uStack_68;
  
  plVar28 = param_1 + 8;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, UniverseAddStatusInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, UniverseAddStatusInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, UniverseAddStatusInfo>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, UniverseAddStatusInfo>, void*>*)(param_1 + 7,*plVar28);
  param_1[7] = (long)plVar28;
  param_1[8] = 0;
  param_1[9] = 0;
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0282d54e/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\Info/InfoBase.h"*/,0x1c1,&UNK_027dc58a/*"apParser is null."*/);
    iVar23 = iRam0000000000000008;
  }
  else {
    iVar23 = (int)param_2[1];
  }
  if (iVar23 != 0) {
    puVar3 = PTR__ZTV21UniverseAddStatusInfo_02cbbaf8 + 0x10;
    puVar4 = PTR__ZTV22CParameterPropertyBaseILj61EE_02cb7008 + 0x10;
    puVar5 = PTR__ZTV23CParameterPropertyValueIjLj61E18CPropertyConverterE_02cc4d48 + 0x10;
    puVar6 = PTR__ZTV22CParameterPropertyBaseILj62EE_02cbaea8 + 0x10;
    puVar7 = PTR__ZTV23CParameterPropertyValueImLj62E18CPropertyConverterE_02cc1078 + 0x10;
    puVar8 = PTR__ZTV22CParameterPropertyBaseILj63EE_02cb6de0 + 0x10;
    puVar9 = PTR__ZTV23CParameterPropertyValueIjLj63E18CPropertyConverterE_02cbd2a0 + 0x10;
    puVar10 = PTR__ZTV22CParameterPropertyBaseILj64EE_02cbbba0 + 0x10;
    puVar11 = PTR__ZTV23CParameterPropertyValueIjLj64E18CPropertyConverterE_02cb96a8 + 0x10;
    puVar12 = PTR__ZTV22CParameterPropertyBaseILj65EE_02cb79a0 + 0x10;
    puVar13 = PTR__ZTV23CParameterPropertyValueIjLj65E18CPropertyConverterE_02cbf1c8 + 0x10;
    puVar14 = PTR__ZTV22CParameterPropertyBaseILj66EE_02cc1e50 + 0x10;
    puVar15 = PTR__ZTV23CParameterPropertyValueIjLj66E18CPropertyConverterE_02cb79f8 + 0x10;
    puVar16 = PTR__ZTV22CParameterPropertyBaseILj67EE_02cc15a8 + 0x10;
    puVar17 = PTR__ZTV23CParameterPropertyValueIjLj67E18CPropertyConverterE_02cb9090 + 0x10;
    puVar18 = PTR__ZTV22CParameterPropertyBaseILj68EE_02cb7090 + 0x10;
    puVar19 = PTR__ZTV23CParameterPropertyValueIjLj68E18CPropertyConverterE_02cb7310 + 0x10;
    uVar27 = 0;
    puVar20 = PTR__ZTV22CParameterPropertyBaseILj69EE_02cb76b8 + 0x10;
    puVar21 = PTR__ZTV23CParameterPropertyValueIjLj69E18CPropertyConverterE_02cb8360 + 0x10;
    puVar22 = PTR__ZTV8InfoBase_02cc49c8 + 0x10;
    do {
      uStack_68 = (**(code **)(*param_1 + 0x20))(param_1,*param_2 + uVar27 * 0x40);
      plVar24 = (long *)param_1[8];
      plVar26 = plVar28;
      if ((long *)param_1[8] == (long *)0x0) {
code_r0x016843bc:
        memset(auStack_240,0,0x1d8);
        uStack_228 = 0;
        uStack_220 = 0;
        uStack_208 = 0;
        uStack_210 = 0;
        puStack_250 = puVar3;
        puStack_248 = auStack_240;
        puStack_230 = &uStack_228;
        puStack_218 = puVar4;
        Framework::CHash32::CHash32()(auStack_200);
        uStack_1d8 = 0;
        uStack_1e0 = 0;
        puStack_218 = puVar5;
        puStack_1e8 = puVar6;
        Framework::CHash32::CHash32()(auStack_1d0);
        uStack_1a8 = 0;
        uStack_1b0 = 0;
        puStack_1e8 = puVar7;
        puStack_1b8 = puVar8;
        Framework::CHash32::CHash32()(auStack_1a0);
        uStack_178 = 0;
        uStack_180 = 0;
        puStack_1b8 = puVar9;
        puStack_188 = puVar10;
        Framework::CHash32::CHash32()(auStack_170);
        uStack_150 = 0;
        uStack_148 = 0;
        puStack_188 = puVar11;
        puStack_158 = puVar12;
        Framework::CHash32::CHash32()(auStack_140);
        uStack_120 = 0;
        uStack_118 = 0;
        puStack_158 = puVar13;
        puStack_128 = puVar14;
        Framework::CHash32::CHash32()(auStack_110);
        uStack_f0 = 0;
        uStack_e8 = 0;
        puStack_128 = puVar15;
        puStack_f8 = puVar16;
        Framework::CHash32::CHash32()(auStack_e0);
        uStack_c0 = 0;
        uStack_b8 = 0;
        puStack_f8 = puVar17;
        puStack_c8 = puVar18;
        Framework::CHash32::CHash32()(auStack_b0);
        uStack_90 = 0;
        uStack_88 = 0;
        puStack_c8 = puVar19;
        puStack_98 = puVar20;
        Framework::CHash32::CHash32()(auStack_80);
        puStack_98 = puVar21;
        lVar25 = std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned long, UniverseAddStatusInfo>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, UniverseAddStatusInfo>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, UniverseAddStatusInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, UniverseAddStatusInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, UniverseAddStatusInfo>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned long, unsigned long&, UniverseAddStatusInfo>(unsigned long const&, unsigned long&, UniverseAddStatusInfo&&)(param_1 + 7,&uStack_68,&uStack_68,&puStack_250);
        puStack_250 = puVar3;
        puStack_98 = puVar20;
        Framework::CHash32::~CHash32()(auStack_80);
        puStack_c8 = puVar18;
        Framework::CHash32::~CHash32()(auStack_b0);
        puStack_f8 = puVar16;
        Framework::CHash32::~CHash32()(auStack_e0);
        puStack_128 = puVar14;
        Framework::CHash32::~CHash32()(auStack_110);
        puStack_158 = puVar12;
        Framework::CHash32::~CHash32()(auStack_140);
        puStack_188 = puVar10;
        Framework::CHash32::~CHash32()(auStack_170);
        puStack_1b8 = puVar8;
        Framework::CHash32::~CHash32()(auStack_1a0);
        puStack_1e8 = puVar6;
        Framework::CHash32::~CHash32()(auStack_1d0);
        puStack_218 = puVar4;
        Framework::CHash32::~CHash32()(auStack_200);
        puStack_250 = puVar22;
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*)(&puStack_230,uStack_228);
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*)(&puStack_248,auStack_240[0]);
        plVar29 = (long *)(lVar25 + 0x28);
        (**(code **)(*plVar29 + 0x10))(plVar29);
      }
      else {
        do {
          while (plVar29 = plVar24, (ulong)plVar29[4] < uStack_68) {
            plVar1 = plVar29 + 1;
            plVar29 = plVar26;
            plVar24 = (long *)*plVar1;
            if ((long *)*plVar1 == (long *)0x0) goto code_r0x01684390;
          }
          plVar24 = (long *)*plVar29;
          plVar26 = plVar29;
        } while ((long *)*plVar29 != (long *)0x0);
code_r0x01684390:
        if (((plVar29 == plVar28) || (uStack_68 < (ulong)plVar29[4])) || (plVar29 == plVar28))
        goto code_r0x016843bc;
        plVar29 = plVar29 + 5;
      }
      lVar25 = *param_2 + uVar27 * 0x40;
      iVar23 = *(int *)(lVar25 + 0x20);
      if (iVar23 == 6) {
        (**(code **)*plVar29)(plVar29,lVar25 + 0x28);
      }
      else if (iVar23 == 7) {
        (**(code **)(*plVar29 + 8))(plVar29,*param_2 + uVar27 * 0x40 + 0x28);
      }
      uVar2 = (int)uVar27 + 1;
      uVar27 = (ulong)uVar2;
    } while (uVar2 < *(uint *)(param_2 + 1));
  }
  return 1;
}

// ==== IInfoBaseMap<unsigned long, EventRankingInfoList>::DeserializeChild(Aska::ASON::AValue::AMap const*)
// vaddr 0x1584a90 | ghidra 0x1684a90 | size 584 | symbol _ZN12IInfoBaseMapIm20EventRankingInfoListE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN12IInfoBaseMapIm20EventRankingInfoListE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE
          (long *param_1,long *param_2)

{
  uint uVar1;
  undefined *puVar2;
  undefined *puVar3;
  long lVar4;
  int iVar5;
  long *plVar6;
  long lVar7;
  long *plVar8;
  ulong uVar9;
  long *plVar10;
  long *plVar11;
  undefined *puStack_b8;
  undefined8 *puStack_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined8 *puStack_98;
  undefined8 uStack_90;
  undefined8 uStack_88;
  long lStack_80;
  long lStack_78;
  undefined8 uStack_70;
  ulong uStack_68;
  
  plVar11 = param_1 + 8;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, EventRankingInfoList>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, EventRankingInfoList>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, EventRankingInfoList>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, EventRankingInfoList>, void*>*)(param_1 + 7,*plVar11);
  param_1[7] = (long)plVar11;
  param_1[8] = 0;
  param_1[9] = 0;
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0282d54e/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\Info/InfoBase.h"*/,0x1c1,&UNK_027dc58a/*"apParser is null."*/);
    iVar5 = iRam0000000000000008;
  }
  else {
    iVar5 = (int)param_2[1];
  }
  if (iVar5 != 0) {
    uVar9 = 0;
    puVar2 = PTR__ZTV20EventRankingInfoList_02cc0d28 + 0x10;
    puVar3 = PTR__ZTV8InfoBase_02cc49c8 + 0x10;
    do {
      uStack_68 = (**(code **)(*param_1 + 0x20))(param_1,*param_2 + uVar9 * 0x40);
      plVar6 = (long *)param_1[8];
      plVar8 = plVar11;
      if ((long *)param_1[8] == (long *)0x0) {
code_r0x01684bc0:
        uStack_a8 = 0;
        uStack_a0 = 0;
        uStack_90 = 0;
        uStack_88 = 0;
        lStack_78 = 0;
        uStack_70 = 0;
        lStack_80 = 0;
        puStack_b8 = puVar2;
        puStack_b0 = &uStack_a8;
        puStack_98 = &uStack_90;
        lVar7 = std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned long, EventRankingInfoList>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, EventRankingInfoList>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, EventRankingInfoList>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, EventRankingInfoList>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, EventRankingInfoList>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned long, unsigned long&, EventRankingInfoList>(unsigned long const&, unsigned long&, EventRankingInfoList&&)(param_1 + 7,&uStack_68,&uStack_68,&puStack_b8);
        lVar4 = lStack_80;
        if (lStack_80 != 0) {
          while (lStack_78 != lVar4) {
            lStack_78 = lStack_78 + -0x3a8;
            EventRankingInfo::~EventRankingInfo()();
          }
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(lStack_80);
        }
        puStack_b8 = puVar3;
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*)(&puStack_98,uStack_90);
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*)(&puStack_b0,uStack_a8);
        plVar10 = (long *)(lVar7 + 0x28);
        (**(code **)(*plVar10 + 0x10))(plVar10);
      }
      else {
        do {
          while (plVar10 = plVar6, uStack_68 <= (ulong)plVar10[4]) {
            plVar6 = (long *)*plVar10;
            plVar8 = plVar10;
            if ((long *)*plVar10 == (long *)0x0) {
              if (plVar10 != plVar11) goto code_r0x01684ba4;
              goto code_r0x01684bc0;
            }
          }
          plVar6 = (long *)plVar10[1];
        } while ((long *)plVar10[1] != (long *)0x0);
        plVar10 = plVar8;
        if (plVar8 == plVar11) goto code_r0x01684bc0;
code_r0x01684ba4:
        if ((uStack_68 < (ulong)plVar10[4]) || (plVar10 == plVar11)) goto code_r0x01684bc0;
        plVar10 = plVar10 + 5;
      }
      lVar4 = *param_2 + uVar9 * 0x40;
      iVar5 = *(int *)(lVar4 + 0x20);
      if (iVar5 == 6) {
        (**(code **)*plVar10)(plVar10,lVar4 + 0x28);
      }
      else if (iVar5 == 7) {
        (**(code **)(*plVar10 + 8))(plVar10,*param_2 + uVar9 * 0x40 + 0x28);
      }
      uVar1 = (int)uVar9 + 1;
      uVar9 = (ulong)uVar1;
    } while (uVar1 < *(uint *)(param_2 + 1));
  }
  return 1;
}

// ==== IInfoBaseMap<unsigned long, EventRankingTopInfoList>::DeserializeChild(Aska::ASON::AValue::AMap const*)
// vaddr 0x1586990 | ghidra 0x1686990 | size 584 | symbol _ZN12IInfoBaseMapIm23EventRankingTopInfoListE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN12IInfoBaseMapIm23EventRankingTopInfoListE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE
          (long *param_1,long *param_2)

{
  uint uVar1;
  undefined *puVar2;
  undefined *puVar3;
  long lVar4;
  int iVar5;
  long *plVar6;
  long lVar7;
  long *plVar8;
  ulong uVar9;
  long *plVar10;
  long *plVar11;
  undefined *puStack_b8;
  undefined8 *puStack_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined8 *puStack_98;
  undefined8 uStack_90;
  undefined8 uStack_88;
  long lStack_80;
  long lStack_78;
  undefined8 uStack_70;
  ulong uStack_68;
  
  plVar11 = param_1 + 8;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, EventRankingTopInfoList>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, EventRankingTopInfoList>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, EventRankingTopInfoList>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, EventRankingTopInfoList>, void*>*)(param_1 + 7,*plVar11);
  param_1[7] = (long)plVar11;
  param_1[8] = 0;
  param_1[9] = 0;
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0282d54e/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\Info/InfoBase.h"*/,0x1c1,&UNK_027dc58a/*"apParser is null."*/);
    iVar5 = iRam0000000000000008;
  }
  else {
    iVar5 = (int)param_2[1];
  }
  if (iVar5 != 0) {
    uVar9 = 0;
    puVar2 = PTR__ZTV23EventRankingTopInfoList_02cb9f88 + 0x10;
    puVar3 = PTR__ZTV8InfoBase_02cc49c8 + 0x10;
    do {
      uStack_68 = (**(code **)(*param_1 + 0x20))(param_1,*param_2 + uVar9 * 0x40);
      plVar6 = (long *)param_1[8];
      plVar8 = plVar11;
      if ((long *)param_1[8] == (long *)0x0) {
code_r0x01686ac0:
        uStack_a8 = 0;
        uStack_a0 = 0;
        uStack_90 = 0;
        uStack_88 = 0;
        lStack_78 = 0;
        uStack_70 = 0;
        lStack_80 = 0;
        puStack_b8 = puVar2;
        puStack_b0 = &uStack_a8;
        puStack_98 = &uStack_90;
        lVar7 = std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned long, EventRankingTopInfoList>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, EventRankingTopInfoList>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, EventRankingTopInfoList>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, EventRankingTopInfoList>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, EventRankingTopInfoList>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned long, unsigned long&, EventRankingTopInfoList>(unsigned long const&, unsigned long&, EventRankingTopInfoList&&)(param_1 + 7,&uStack_68,&uStack_68,&puStack_b8);
        lVar4 = lStack_80;
        if (lStack_80 != 0) {
          while (lStack_78 != lVar4) {
            lStack_78 = lStack_78 + -0x3a8;
            EventRankingInfo::~EventRankingInfo()();
          }
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(lStack_80);
        }
        puStack_b8 = puVar3;
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*)(&puStack_98,uStack_90);
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*)(&puStack_b0,uStack_a8);
        plVar10 = (long *)(lVar7 + 0x28);
        (**(code **)(*plVar10 + 0x10))(plVar10);
      }
      else {
        do {
          while (plVar10 = plVar6, uStack_68 <= (ulong)plVar10[4]) {
            plVar6 = (long *)*plVar10;
            plVar8 = plVar10;
            if ((long *)*plVar10 == (long *)0x0) {
              if (plVar10 != plVar11) goto code_r0x01686aa4;
              goto code_r0x01686ac0;
            }
          }
          plVar6 = (long *)plVar10[1];
        } while ((long *)plVar10[1] != (long *)0x0);
        plVar10 = plVar8;
        if (plVar8 == plVar11) goto code_r0x01686ac0;
code_r0x01686aa4:
        if ((uStack_68 < (ulong)plVar10[4]) || (plVar10 == plVar11)) goto code_r0x01686ac0;
        plVar10 = plVar10 + 5;
      }
      lVar4 = *param_2 + uVar9 * 0x40;
      iVar5 = *(int *)(lVar4 + 0x20);
      if (iVar5 == 6) {
        (**(code **)*plVar10)(plVar10,lVar4 + 0x28);
      }
      else if (iVar5 == 7) {
        (**(code **)(*plVar10 + 8))(plVar10,*param_2 + uVar9 * 0x40 + 0x28);
      }
      uVar1 = (int)uVar9 + 1;
      uVar9 = (ulong)uVar1;
    } while (uVar1 < *(uint *)(param_2 + 1));
  }
  return 1;
}

// ==== IInfoBaseMap<unsigned long, EventRankingPlayerInfo>::DeserializeChild(Aska::ASON::AValue::AMap const*)
// vaddr 0x1587020 | ghidra 0x1687020 | size 648 | symbol _ZN12IInfoBaseMapIm22EventRankingPlayerInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN12IInfoBaseMapIm22EventRankingPlayerInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE
          (long *param_1,long *param_2)

{
  uint uVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined *puVar5;
  int iVar6;
  long *plVar7;
  long lVar8;
  long *plVar9;
  ulong uVar10;
  long *plVar11;
  long *plVar12;
  undefined *puStack_e0;
  undefined8 *puStack_d8;
  undefined8 auStack_d0 [2];
  undefined8 *puStack_c0;
  undefined8 uStack_b8;
  undefined8 uStack_b0;
  undefined *puStack_a8;
  undefined8 uStack_a0;
  undefined1 uStack_98;
  undefined1 auStack_90 [16];
  ulong uStack_80;
  undefined8 uStack_78;
  undefined8 uStack_70;
  ulong uStack_68;
  
  plVar12 = param_1 + 8;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, EventRankingPlayerInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, EventRankingPlayerInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, EventRankingPlayerInfo>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, EventRankingPlayerInfo>, void*>*)(param_1 + 7,*plVar12);
  param_1[7] = (long)plVar12;
  param_1[8] = 0;
  param_1[9] = 0;
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0282d54e/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\Info/InfoBase.h"*/,0x1c1,&UNK_027dc58a/*"apParser is null."*/);
    iVar6 = iRam0000000000000008;
  }
  else {
    iVar6 = (int)param_2[1];
  }
  if (iVar6 != 0) {
    puVar2 = PTR__ZTV22CParameterPropertyBaseILj91EE_02cbc970 + 0x10;
    uVar10 = 0;
    puVar3 = PTR__ZTV22EventRankingPlayerInfo_02cc4288 + 0x10;
    puVar4 = PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj91EE_02cbeb50
             + 0x10;
    puVar5 = PTR__ZTV8InfoBase_02cc49c8 + 0x10;
    do {
      uStack_68 = (**(code **)(*param_1 + 0x20))(param_1,*param_2 + uVar10 * 0x40);
      plVar7 = (long *)param_1[8];
      plVar9 = plVar12;
      if ((long *)param_1[8] == (long *)0x0) {
code_r0x01687174:
        memset(auStack_d0,0,0x68);
        uStack_b8 = 0;
        uStack_b0 = 0;
        uStack_a0 = 0;
        uStack_98 = 0;
        puStack_e0 = puVar3;
        puStack_d8 = auStack_d0;
        puStack_c0 = &uStack_b8;
        puStack_a8 = puVar2;
        Framework::CHash32::CHash32()(auStack_90);
        uStack_78 = 0;
        uStack_70 = 0;
        uStack_80 = 0;
        puStack_a8 = puVar4;
        lVar8 = std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned long, EventRankingPlayerInfo>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, EventRankingPlayerInfo>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, EventRankingPlayerInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, EventRankingPlayerInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, EventRankingPlayerInfo>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned long, unsigned long&, EventRankingPlayerInfo>(unsigned long const&, unsigned long&, EventRankingPlayerInfo&&)(param_1 + 7,&uStack_68,&uStack_68,&puStack_e0);
        puStack_e0 = puVar3;
        if ((uStack_80 & 1) != 0) {
          puStack_a8 = puVar4;
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_70);
        }
        puStack_a8 = PTR__ZTV22CParameterPropertyBaseILj91EE_02cbc970 + 0x10;
        Framework::CHash32::~CHash32()(auStack_90);
        puStack_e0 = puVar5;
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*)(&puStack_c0,uStack_b8);
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*)(&puStack_d8,auStack_d0[0]);
        plVar11 = (long *)(lVar8 + 0x28);
        (**(code **)(*plVar11 + 0x10))(plVar11);
      }
      else {
        do {
          while (plVar11 = plVar7, (ulong)plVar11[4] < uStack_68) {
            plVar7 = (long *)plVar11[1];
            if ((long *)plVar11[1] == (long *)0x0) {
              plVar11 = plVar9;
              if (plVar9 != plVar12) goto code_r0x01687158;
              goto code_r0x01687174;
            }
          }
          plVar7 = (long *)*plVar11;
          plVar9 = plVar11;
        } while ((long *)*plVar11 != (long *)0x0);
        if (plVar11 == plVar12) goto code_r0x01687174;
code_r0x01687158:
        if ((uStack_68 < (ulong)plVar11[4]) || (plVar11 == plVar12)) goto code_r0x01687174;
        plVar11 = plVar11 + 5;
      }
      lVar8 = *param_2 + uVar10 * 0x40;
      iVar6 = *(int *)(lVar8 + 0x20);
      if (iVar6 == 6) {
        (**(code **)*plVar11)(plVar11,lVar8 + 0x28);
      }
      else if (iVar6 == 7) {
        (**(code **)(*plVar11 + 8))(plVar11,*param_2 + uVar10 * 0x40 + 0x28);
      }
      uVar1 = (int)uVar10 + 1;
      uVar10 = (ulong)uVar1;
    } while (uVar1 < *(uint *)(param_2 + 1));
  }
  return 1;
}

// ==== IInfoBaseMap<unsigned long, _PickupCharaterChipResultInfoList>::DeserializeChild(Aska::ASON::AValue::AMap const*)
// vaddr 0x15888b8 | ghidra 0x16888b8 | size 612 | symbol _ZN12IInfoBaseMapIm33_PickupCharaterChipResultInfoListE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN12IInfoBaseMapIm33_PickupCharaterChipResultInfoListE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE
          (long *param_1,long *param_2)

{
  uint uVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  long lVar5;
  int iVar6;
  long lVar7;
  long *plVar8;
  long lVar9;
  long *plVar10;
  ulong uVar11;
  long *plVar12;
  long *plVar13;
  undefined *puStack_b8;
  undefined8 *puStack_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined8 *puStack_98;
  undefined8 uStack_90;
  undefined8 uStack_88;
  long lStack_80;
  long lStack_78;
  undefined8 uStack_70;
  ulong uStack_68;
  
  plVar13 = param_1 + 8;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, _PickupCharaterChipResultInfoList>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, _PickupCharaterChipResultInfoList>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, _PickupCharaterChipResultInfoList>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, _PickupCharaterChipResultInfoList>, void*>*)(param_1 + 7,*plVar13);
  param_1[7] = (long)plVar13;
  param_1[8] = 0;
  param_1[9] = 0;
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0282d54e/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\Info/InfoBase.h"*/,0x1c1,&UNK_027dc58a/*"apParser is null."*/);
    iVar6 = iRam0000000000000008;
  }
  else {
    iVar6 = (int)param_2[1];
  }
  if (iVar6 != 0) {
    puVar2 = PTR__ZTV33_PickupCharaterChipResultInfoList_02cbb598 + 0x10;
    uVar11 = 0;
    puVar3 = PTR__ZTV8InfoBase_02cc49c8 + 0x10;
    puVar4 = PTR__ZTV22CParameterPropertyBaseILj50EE_02cbd5f0 + 0x10;
    do {
      uStack_68 = (**(code **)(*param_1 + 0x20))(param_1,*param_2 + uVar11 * 0x40);
      plVar8 = (long *)param_1[8];
      plVar10 = plVar13;
      if ((long *)param_1[8] == (long *)0x0) {
code_r0x016889f8:
        uStack_a8 = 0;
        uStack_a0 = 0;
        uStack_90 = 0;
        uStack_88 = 0;
        lStack_78 = 0;
        uStack_70 = 0;
        lStack_80 = 0;
        puStack_b8 = puVar2;
        puStack_b0 = &uStack_a8;
        puStack_98 = &uStack_90;
        lVar9 = std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned long, _PickupCharaterChipResultInfoList>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, _PickupCharaterChipResultInfoList>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, _PickupCharaterChipResultInfoList>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, _PickupCharaterChipResultInfoList>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, _PickupCharaterChipResultInfoList>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned long, unsigned long&, _PickupCharaterChipResultInfoList>(unsigned long const&, unsigned long&, _PickupCharaterChipResultInfoList&&)(param_1 + 7,&uStack_68,&uStack_68,&puStack_b8);
        lVar7 = lStack_80;
        lVar5 = lStack_78;
        if (lStack_80 != 0) {
          while (lVar5 != lVar7) {
            lStack_78 = lVar5 + -0x30;
            *(undefined **)(lVar5 + -0x30) = puVar4;
            Framework::CHash32::~CHash32()(lVar5 + -0x18);
            lVar5 = lStack_78;
          }
          lStack_78 = lVar5;
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(lStack_80);
        }
        puStack_b8 = puVar3;
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*)(&puStack_98,uStack_90);
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*)(&puStack_b0,uStack_a8);
        plVar12 = (long *)(lVar9 + 0x28);
        (**(code **)(*plVar12 + 0x10))(plVar12);
      }
      else {
        do {
          while (plVar12 = plVar8, uStack_68 <= (ulong)plVar12[4]) {
            plVar8 = (long *)*plVar12;
            plVar10 = plVar12;
            if ((long *)*plVar12 == (long *)0x0) {
              if (plVar12 != plVar13) goto code_r0x016889dc;
              goto code_r0x016889f8;
            }
          }
          plVar8 = (long *)plVar12[1];
        } while ((long *)plVar12[1] != (long *)0x0);
        plVar12 = plVar10;
        if (plVar10 == plVar13) goto code_r0x016889f8;
code_r0x016889dc:
        if ((uStack_68 < (ulong)plVar12[4]) || (plVar12 == plVar13)) goto code_r0x016889f8;
        plVar12 = plVar12 + 5;
      }
      lVar5 = *param_2 + uVar11 * 0x40;
      iVar6 = *(int *)(lVar5 + 0x20);
      if (iVar6 == 6) {
        (**(code **)*plVar12)(plVar12,lVar5 + 0x28);
      }
      else if (iVar6 == 7) {
        (**(code **)(*plVar12 + 8))(plVar12,*param_2 + uVar11 * 0x40 + 0x28);
      }
      uVar1 = (int)uVar11 + 1;
      uVar11 = (ulong)uVar1;
    } while (uVar1 < *(uint *)(param_2 + 1));
  }
  return 1;
}

// ==== IInfoBaseMap<unsigned long, CGachaTestResultInfo>::DeserializeChild(Aska::ASON::AValue::AMap const*)
// vaddr 0x1589654 | ghidra 0x1689654 | size 436 | symbol _ZN12IInfoBaseMapIm20CGachaTestResultInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN12IInfoBaseMapIm20CGachaTestResultInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE
          (long *param_1,long *param_2)

{
  uint uVar1;
  int iVar2;
  long *plVar3;
  long lVar4;
  long *plVar5;
  ulong uVar6;
  long *plVar7;
  long *plVar8;
  undefined1 auStack_250 [520];
  ulong uStack_48;
  
  plVar8 = param_1 + 8;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CGachaTestResultInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CGachaTestResultInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CGachaTestResultInfo>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CGachaTestResultInfo>, void*>*)(param_1 + 7,*plVar8);
  param_1[7] = (long)plVar8;
  param_1[8] = 0;
  param_1[9] = 0;
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0282d54e/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\Info/InfoBase.h"*/,0x1c1,&UNK_027dc58a/*"apParser is null."*/);
    iVar2 = iRam0000000000000008;
  }
  else {
    iVar2 = (int)param_2[1];
  }
  if (iVar2 != 0) {
    uVar6 = 0;
    do {
      uStack_48 = (**(code **)(*param_1 + 0x20))(param_1,*param_2 + uVar6 * 0x40);
      plVar3 = (long *)param_1[8];
      plVar5 = plVar8;
      if ((long *)param_1[8] == (long *)0x0) {
code_r0x01689748:
        memset(auStack_250,0,0x208);
        CGachaTestResultInfo::CGachaTestResultInfo()(auStack_250);
        lVar4 = std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned long, CGachaTestResultInfo>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CGachaTestResultInfo>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CGachaTestResultInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CGachaTestResultInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CGachaTestResultInfo>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned long, unsigned long&, CGachaTestResultInfo>(unsigned long const&, unsigned long&, CGachaTestResultInfo&&)(param_1 + 7,&uStack_48,&uStack_48,auStack_250);
        CGachaTestResultInfo::~CGachaTestResultInfo()(auStack_250);
        plVar7 = (long *)(lVar4 + 0x28);
        (**(code **)(*plVar7 + 0x10))(plVar7);
      }
      else {
        do {
          while (plVar7 = plVar3, (ulong)plVar7[4] < uStack_48) {
            plVar3 = (long *)plVar7[1];
            if ((long *)plVar7[1] == (long *)0x0) {
              plVar7 = plVar5;
              if (plVar5 != plVar8) goto code_r0x0168972c;
              goto code_r0x01689748;
            }
          }
          plVar3 = (long *)*plVar7;
          plVar5 = plVar7;
        } while ((long *)*plVar7 != (long *)0x0);
        if (plVar7 == plVar8) goto code_r0x01689748;
code_r0x0168972c:
        if ((uStack_48 < (ulong)plVar7[4]) || (plVar7 == plVar8)) goto code_r0x01689748;
        plVar7 = plVar7 + 5;
      }
      lVar4 = *param_2 + uVar6 * 0x40;
      iVar2 = *(int *)(lVar4 + 0x20);
      if (iVar2 == 6) {
        (**(code **)*plVar7)(plVar7,lVar4 + 0x28);
      }
      else if (iVar2 == 7) {
        (**(code **)(*plVar7 + 8))(plVar7,*param_2 + uVar6 * 0x40 + 0x28);
      }
      uVar1 = (int)uVar6 + 1;
      uVar6 = (ulong)uVar1;
    } while (uVar1 < *(uint *)(param_2 + 1));
  }
  return 1;
}

// ==== IInfoBaseMap<unsigned long, CGachaMutationTestResultInfo>::DeserializeChild(Aska::ASON::AValue::AMap const*)
// vaddr 0x158a868 | ghidra 0x168a868 | size 1180 | symbol _ZN12IInfoBaseMapIm28CGachaMutationTestResultInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Type propagation algorithm not settling */

undefined8
_ZN12IInfoBaseMapIm28CGachaMutationTestResultInfoE16DeserializeChildEPKN4Aska4ASON6AValue4AMapE
          (long *param_1,long *param_2)

{
  uint uVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined *puVar5;
  undefined *puVar6;
  undefined *puVar7;
  undefined *puVar8;
  undefined *puVar9;
  undefined *puVar10;
  undefined *puVar11;
  long lVar12;
  int iVar13;
  long *plVar14;
  long *******ppppppplVar15;
  long *******ppppppplVar16;
  ulong uVar17;
  long *******ppppppplVar18;
  long *******ppppppplVar19;
  long *******ppppppplVar20;
  undefined *puStack_190;
  undefined8 *puStack_188;
  undefined8 auStack_180 [2];
  undefined8 *puStack_170;
  undefined8 uStack_168;
  undefined8 uStack_160;
  undefined *puStack_158;
  undefined8 uStack_150;
  undefined1 uStack_148;
  undefined1 auStack_140 [24];
  undefined *puStack_128;
  undefined8 uStack_120;
  undefined1 uStack_118;
  undefined1 auStack_110 [16];
  ulong uStack_100;
  undefined8 uStack_f8;
  undefined8 uStack_f0;
  undefined *puStack_e8;
  undefined8 uStack_e0;
  undefined1 uStack_d8;
  undefined1 auStack_d0 [24];
  undefined *puStack_b8;
  undefined8 uStack_b0;
  undefined1 uStack_a8;
  undefined1 auStack_a0 [24];
  long ******pppppplStack_88;
  long *******appppppplStack_80 [3];
  long *******ppppppplStack_68;
  
  ppppppplVar18 = (long *******)(param_1 + 8);
  plVar14 = param_1 + 7;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CGachaMutationTestResultInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CGachaMutationTestResultInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CGachaMutationTestResultInfo>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CGachaMutationTestResultInfo>, void*>*)(plVar14,*ppppppplVar18);
  param_1[7] = (long)ppppppplVar18;
  param_1[8] = 0;
  param_1[9] = 0;
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0282d54e/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\Info/InfoBase.h"*/,0x1c1,&UNK_027dc58a/*"apParser is null."*/);
    iVar13 = iRam0000000000000008;
  }
  else {
    iVar13 = (int)param_2[1];
  }
  if (iVar13 != 0) {
    puVar2 = PTR__ZTV28CGachaMutationTestResultInfo_02cb9a68 + 0x10;
    puVar3 = PTR__ZTV22CParameterPropertyBaseILj13EE_02cba498 + 0x10;
    puVar4 = PTR__ZTV23CParameterPropertyValueIjLj13E18CPropertyConverterE_02cbd818 + 0x10;
    puVar5 = PTR__ZTV22CParameterPropertyBaseILj14EE_02cb9db0 + 0x10;
    puVar6 = PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj14EE_02cbbde0
             + 0x10;
    puVar7 = PTR__ZTV22CParameterPropertyBaseILj15EE_02cc0790 + 0x10;
    puVar8 = PTR__ZTV23CParameterPropertyValueIjLj15E18CPropertyConverterE_02cc1598 + 0x10;
    puVar9 = PTR__ZTV22CParameterPropertyBaseILj16EE_02cb9c20 + 0x10;
    puVar10 = PTR__ZTV23CParameterPropertyValueIbLj16E18CPropertyConverterE_02cc0000 + 0x10;
    uVar17 = 0;
    puVar11 = PTR__ZTV8InfoBase_02cc49c8 + 0x10;
    do {
      pppppplStack_88 =
           (long ******)(**(code **)(*param_1 + 0x20))(param_1,*param_2 + uVar17 * 0x40);
      ppppppplVar16 = (long *******)param_1[8];
      ppppppplVar15 = ppppppplVar18;
      if ((long *******)param_1[8] == (long *******)0x0) {
code_r0x0168aa40:
        memset(auStack_180,0,0xf8);
        uStack_168 = 0;
        uStack_160 = 0;
        uStack_148 = 0;
        uStack_150 = 0;
        puStack_190 = puVar2;
        puStack_188 = auStack_180;
        puStack_170 = &uStack_168;
        puStack_158 = puVar3;
        Framework::CHash32::CHash32()(auStack_140);
        uStack_118 = 0;
        uStack_120 = 0;
        puStack_158 = puVar4;
        puStack_128 = puVar5;
        Framework::CHash32::CHash32()(auStack_110);
        uStack_f8 = 0;
        uStack_f0 = 0;
        uStack_100 = 0;
        uStack_d8 = 0;
        uStack_e0 = 0;
        puStack_128 = puVar6;
        puStack_e8 = puVar7;
        Framework::CHash32::CHash32()(auStack_d0);
        uStack_a8 = 0;
        uStack_b0 = 0;
        puStack_e8 = puVar8;
        puStack_b8 = puVar9;
        Framework::CHash32::CHash32()(auStack_a0);
        ppppppplVar16 = (long *******)*ppppppplVar18;
        if ((long *******)*ppppppplVar18 == (long *******)0x0) {
          ppppppplVar20 = (long *******)*ppppppplVar18;
          ppppppplVar15 = ppppppplVar18;
          ppppppplVar19 = ppppppplVar18;
        }
        else {
          do {
            while (ppppppplVar15 = ppppppplVar16, ppppppplVar15[4] <= pppppplStack_88) {
              if (pppppplStack_88 <= ppppppplVar15[4]) {
                ppppppplVar20 = ppppppplVar15;
                ppppppplVar19 = (long *******)&ppppppplStack_68;
                goto joined_r0x0168ab54;
              }
              ppppppplVar19 = ppppppplVar15 + 1;
              ppppppplVar16 = (long *******)*ppppppplVar19;
              if ((long *******)*ppppppplVar19 == (long *******)0x0) {
                ppppppplVar20 = (long *******)*ppppppplVar19;
                goto joined_r0x0168ab54;
              }
            }
            ppppppplVar16 = (long *******)*ppppppplVar15;
          } while ((long *******)*ppppppplVar15 != (long *******)0x0);
          ppppppplVar20 = (long *******)*ppppppplVar15;
          ppppppplVar19 = ppppppplVar15;
        }
joined_r0x0168ab54:
        ppppppplStack_68 = ppppppplVar15;
        if (ppppppplVar20 == (long *******)0x0) {
          puStack_b8 = puVar10;
          std::__ndk1::unique_ptr<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CGachaMutationTestResultInfo>, void*>, std::__ndk1::__tree_node_destructor<Framework::CSTLAllocator<std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CGachaMutationTestResultInfo>, void*>, Framework::CSTLMapAllocatorInf> > > std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CGachaMutationTestResultInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CGachaMutationTestResultInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CGachaMutationTestResultInfo>, Framework::CSTLMapAllocatorInf> >::__construct_node<unsigned long&, CGachaMutationTestResultInfo>(unsigned long&, CGachaMutationTestResultInfo&&)(appppppplStack_80,plVar14,&pppppplStack_88,&puStack_190);
          *appppppplStack_80[0] = (long ******)0x0;
          appppppplStack_80[0][1] = (long ******)0x0;
          appppppplStack_80[0][2] = (long ******)ppppppplVar15;
          *ppppppplVar19 = (long ******)appppppplStack_80[0];
          ppppppplVar16 = appppppplStack_80[0];
          if (*(long *)*plVar14 != 0) {
            *plVar14 = *(long *)*plVar14;
            ppppppplVar16 = (long *******)*ppppppplVar19;
          }
          void std::__ndk1::__tree_balance_after_insert<std::__ndk1::__tree_node_base<void*>*>(std::__ndk1::__tree_node_base<void*>*, std::__ndk1::__tree_node_base<void*>*)(param_1[8],ppppppplVar16);
          param_1[9] = param_1[9] + 1;
          ppppppplVar20 = appppppplStack_80[0];
        }
        puStack_190 = PTR__ZTV28CGachaMutationTestResultInfo_02cb9a68 + 0x10;
        puStack_b8 = PTR__ZTV22CParameterPropertyBaseILj16EE_02cb9c20 + 0x10;
        Framework::CHash32::~CHash32()(auStack_a0);
        puStack_e8 = PTR__ZTV22CParameterPropertyBaseILj15EE_02cc0790 + 0x10;
        Framework::CHash32::~CHash32()(auStack_d0);
        puStack_128 = PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj14EE_02cbbde0
                      + 0x10;
        if ((uStack_100 & 1) != 0) {
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_f0);
        }
        puStack_128 = PTR__ZTV22CParameterPropertyBaseILj14EE_02cb9db0 + 0x10;
        Framework::CHash32::~CHash32()(auStack_110);
        puStack_158 = PTR__ZTV22CParameterPropertyBaseILj13EE_02cba498 + 0x10;
        Framework::CHash32::~CHash32()(auStack_140);
        puStack_190 = puVar11;
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*)(&puStack_170,uStack_168);
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*)(&puStack_188,auStack_180[0]);
        ppppppplVar20 = ppppppplVar20 + 5;
        (*(code *)(*ppppppplVar20)[2])(ppppppplVar20);
      }
      else {
        do {
          while (ppppppplVar20 = ppppppplVar16, ppppppplVar20[4] < pppppplStack_88) {
            ppppppplVar16 = (long *******)ppppppplVar20[1];
            if ((long *******)ppppppplVar20[1] == (long *******)0x0) {
              ppppppplVar20 = ppppppplVar15;
              if (ppppppplVar15 != ppppppplVar18) goto code_r0x0168aa24;
              goto code_r0x0168aa40;
            }
          }
          ppppppplVar16 = (long *******)*ppppppplVar20;
          ppppppplVar15 = ppppppplVar20;
        } while ((long *******)*ppppppplVar20 != (long *******)0x0);
        if (ppppppplVar20 == ppppppplVar18) goto code_r0x0168aa40;
code_r0x0168aa24:
        if ((pppppplStack_88 < ppppppplVar20[4]) || (ppppppplVar20 == ppppppplVar18))
        goto code_r0x0168aa40;
        ppppppplVar20 = ppppppplVar20 + 5;
      }
      lVar12 = *param_2 + uVar17 * 0x40;
      iVar13 = *(int *)(lVar12 + 0x20);
      if (iVar13 == 6) {
        (*(code *)**ppppppplVar20)(ppppppplVar20,lVar12 + 0x28);
      }
      else if (iVar13 == 7) {
        (*(code *)(*ppppppplVar20)[1])(ppppppplVar20,*param_2 + uVar17 * 0x40 + 0x28);
      }
      uVar1 = (int)uVar17 + 1;
      uVar17 = (ulong)uVar1;
    } while (uVar1 < *(uint *)(param_2 + 1));
  }
  return 1;
}
