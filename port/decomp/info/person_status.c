// port/decomp/info/person_status.c: Ghidra decompiles for the info subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-08 15:04 UTC: tools/decomp.sh '--into' 'info/person_status' 'CPersonStatusInfo::' '^\S+ InfoBase::'

// ==== InfoBase::DeserializeChild(Aska::ASON::AValue::AMap const*)
// vaddr 0x115ecd0 | ghidra 0x125ecd0 | size 452 | symbol _ZN8InfoBase16DeserializeChildEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN8InfoBase16DeserializeChildEPKN4Aska4ASON6AValue4AMapE(long param_1,long *param_2)

{
  long *plVar1;
  long *plVar2;
  long lVar3;
  int iVar4;
  uint uVar5;
  long *plVar6;
  long *plVar7;
  uint uVar8;
  long *plVar9;
  code *pcVar10;
  ulong uVar11;
  undefined1 auStack_40 [16];
  
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dc3b5/*"C:\BAS_Submission\Client\Project\Android\BASAndroid.NativeActivity\..\..\..\Source\Game/Parameter/Info/InfoBase.h"*/,0x86,&UNK_027dc58a/*"apParser is null."*/);
    iVar4 = iRam0000000000000008;
  }
  else {
    iVar4 = (int)param_2[1];
  }
  if (iVar4 != 0) {
    uVar8 = 0;
    plVar1 = (long *)(param_1 + 0x10);
    plVar2 = (long *)(param_1 + 0x28);
    do {
      uVar11 = (ulong)uVar8;
      Framework::CHash32::CHash32(char const*)(auStack_40,*(undefined8 *)(*param_2 + uVar11 * 0x40 + 0x10));
      uVar5 = Framework::CHash32::operator unsigned int() const(auStack_40);
      Framework::CHash32::~CHash32()(auStack_40);
      plVar7 = (long *)*plVar1;
      plVar6 = plVar1;
      if ((long *)*plVar1 != (long *)0x0) {
        do {
          while (plVar9 = plVar7, *(uint *)(plVar9 + 4) < uVar5) {
            plVar7 = (long *)plVar9[1];
            if ((long *)plVar9[1] == (long *)0x0) {
              plVar9 = plVar6;
              if (plVar6 == plVar1) goto code_r0x0125edc4;
              goto code_r0x0125ed9c;
            }
          }
          plVar7 = (long *)*plVar9;
          plVar6 = plVar9;
        } while ((long *)*plVar9 != (long *)0x0);
        if (plVar9 != plVar1) {
code_r0x0125ed9c:
          if ((*(uint *)(plVar9 + 4) <= uVar5) && (plVar9 != plVar1)) {
            (**(code **)(*(long *)plVar9[5] + 0x18))((long *)plVar9[5],param_2);
          }
        }
      }
code_r0x0125edc4:
      plVar7 = (long *)*plVar2;
      plVar6 = plVar2;
      if ((long *)*plVar2 != (long *)0x0) {
        do {
          while (plVar9 = plVar7, *(uint *)(plVar9 + 4) < uVar5) {
            plVar7 = (long *)plVar9[1];
            if ((long *)plVar9[1] == (long *)0x0) {
              plVar9 = plVar6;
              if (plVar6 == plVar2) goto code_r0x0125ee6c;
              goto code_r0x0125ee10;
            }
          }
          plVar7 = (long *)*plVar9;
          plVar6 = plVar9;
        } while ((long *)*plVar9 != (long *)0x0);
        if (plVar9 != plVar2) {
code_r0x0125ee10:
          if ((*(uint *)(plVar9 + 4) <= uVar5) && (plVar9 != plVar2)) {
            lVar3 = *param_2 + uVar11 * 0x40;
            if (*(int *)(lVar3 + 0x20) == 6) {
              plVar7 = (long *)plVar9[5];
              pcVar10 = *(code **)*plVar7;
            }
            else {
              if (*(int *)(lVar3 + 0x20) != 7) goto code_r0x0125ee6c;
              plVar7 = (long *)plVar9[5];
              lVar3 = *param_2 + uVar11 * 0x40;
              pcVar10 = *(code **)(*plVar7 + 8);
            }
            (*pcVar10)(plVar7,lVar3 + 0x28);
          }
        }
      }
code_r0x0125ee6c:
      uVar8 = uVar8 + 1;
    } while (uVar8 < *(uint *)(param_2 + 1));
  }
  return 1;
}

// ==== InfoBase::pParseName() const
// vaddr 0x115eea4 | ghidra 0x125eea4 | size 8 | symbol _ZNK8InfoBase10pParseNameEv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK8InfoBase10pParseNameEv(void)

{
  return 0;
}

// ==== InfoBase::DeserializeArray(Aska::ASON::AValue::AArray const*)
// vaddr 0x115eeac | ghidra 0x125eeac | size 8 | symbol _ZN8InfoBase16DeserializeArrayEPKN4Aska4ASON6AValue6AArrayE | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN8InfoBase16DeserializeArrayEPKN4Aska4ASON6AValue6AArrayE(void)

{
  return 0;
}

// ==== CPersonStatusInfo::CPersonStatusInfo()
// vaddr 0x12a51b8 | ghidra 0x13a51b8 | size 5768 | symbol _ZN17CPersonStatusInfoC2Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN17CPersonStatusInfoC2Ev(long *param_1)

{
  undefined *puVar1;
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
  undefined *puVar21;
  
  param_1[3] = 0;
  param_1[2] = 0;
  param_1[1] = (long)(param_1 + 2);
  puVar1 = PTR__ZTV17CPersonStatusInfo_02cbd500;
  param_1[6] = 0;
  param_1[5] = 0;
  *param_1 = (long)(puVar1 + 0x10);
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj163EE_02cbb018;
  *(undefined1 *)(param_1 + 9) = 0;
  param_1[4] = (long)(param_1 + 5);
  param_1[7] = (long)(puVar1 + 0x10);
  param_1[8] = 0;
  Framework::CHash32::CHash32()(param_1 + 10);
  puVar2 = PTR__ZTV23CParameterPropertyValueImLj163E18CPropertyConverterE_02cbb940;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj164EE_02cb6d78;
  *(undefined1 *)(param_1 + 0xf) = 0;
  param_1[7] = (long)(puVar2 + 0x10);
  param_1[0xd] = (long)(puVar1 + 0x10);
  param_1[0xe] = 0;
  Framework::CHash32::CHash32()(param_1 + 0x10);
  puVar2 = PTR__ZTV22CParameterPropertyBaseILj165EE_02cbe958;
  puVar1 = PTR__ZTV23CParameterPropertyValueIjLj164E18CPropertyConverterE_02cb6b60;
  *(undefined1 *)(param_1 + 0x15) = 0;
  param_1[0xd] = (long)(puVar1 + 0x10);
  param_1[0x13] = (long)(puVar2 + 0x10);
  param_1[0x14] = 0;
  Framework::CHash32::CHash32()(param_1 + 0x16);
  puVar1 = 
  PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj165EE_02cbd098
  ;
  param_1[0x18] = 0;
  param_1[0x19] = 0;
  param_1[0x1c] = 0;
  puVar2 = PTR__ZTV22CParameterPropertyBaseILj166EE_02cbf3d8;
  *(undefined1 *)(param_1 + 0x1d) = 0;
  param_1[0x13] = (long)(puVar1 + 0x10);
  param_1[0x1a] = 0;
  param_1[0x1b] = (long)(puVar2 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0x1e);
  puVar2 = PTR__ZTV23CParameterPropertyValueIjLj166E18CPropertyConverterE_02cc3d20;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj167EE_02cc36a8;
  *(undefined1 *)(param_1 + 0x23) = 0;
  param_1[0x1b] = (long)(puVar2 + 0x10);
  param_1[0x21] = (long)(puVar1 + 0x10);
  param_1[0x22] = 0;
  Framework::CHash32::CHash32()(param_1 + 0x24);
  puVar2 = PTR__ZTV23CParameterPropertyValueIjLj167E18CPropertyConverterE_02cbccd8;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj168EE_02cbb8a0;
  *(undefined1 *)(param_1 + 0x29) = 0;
  param_1[0x21] = (long)(puVar2 + 0x10);
  param_1[0x27] = (long)(puVar1 + 0x10);
  param_1[0x28] = 0;
  Framework::CHash32::CHash32()(param_1 + 0x2a);
  puVar2 = PTR__ZTV23CParameterPropertyValueImLj168E18CPropertyConverterE_02cc4290;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj169EE_02cbcf68;
  *(undefined1 *)(param_1 + 0x2f) = 0;
  param_1[0x27] = (long)(puVar2 + 0x10);
  param_1[0x2d] = (long)(puVar1 + 0x10);
  param_1[0x2e] = 0;
  Framework::CHash32::CHash32()(param_1 + 0x30);
  puVar2 = PTR__ZTV23CParameterPropertyValueImLj169E18CPropertyConverterE_02cc3730;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj170EE_02cc11c8;
  *(undefined1 *)(param_1 + 0x35) = 0;
  param_1[0x2d] = (long)(puVar2 + 0x10);
  param_1[0x33] = (long)(puVar1 + 0x10);
  param_1[0x34] = 0;
  Framework::CHash32::CHash32()(param_1 + 0x36);
  puVar2 = PTR__ZTV23CParameterPropertyValueIjLj170E18CPropertyConverterE_02cc4be0;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj171EE_02cb6eb8;
  *(undefined1 *)(param_1 + 0x3b) = 0;
  param_1[0x33] = (long)(puVar2 + 0x10);
  param_1[0x39] = (long)(puVar1 + 0x10);
  param_1[0x3a] = 0;
  Framework::CHash32::CHash32()(param_1 + 0x3c);
  puVar2 = PTR__ZTV23CParameterPropertyValueIjLj171E18CPropertyConverterE_02cbdc20;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj172EE_02cb79d0;
  *(undefined1 *)(param_1 + 0x41) = 0;
  param_1[0x39] = (long)(puVar2 + 0x10);
  param_1[0x3f] = (long)(puVar1 + 0x10);
  param_1[0x40] = 0;
  Framework::CHash32::CHash32()(param_1 + 0x42);
  puVar2 = PTR__ZTV23CParameterPropertyValueIjLj172E18CPropertyConverterE_02cc33c8;
  param_1[0x46] = 0;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj174EE_02cb7838;
  *(undefined1 *)(param_1 + 0x47) = 0;
  param_1[0x3f] = (long)(puVar2 + 0x10);
  param_1[0x45] = (long)(puVar1 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0x48);
  puVar1 = PTR__ZTV23CParameterPropertyValueIjLj174E18CPropertyConverterE_02cba740;
  param_1[0x4c] = 0;
  puVar2 = PTR__ZTV22CParameterPropertyBaseILj175EE_02cbe608;
  *(undefined1 *)(param_1 + 0x4d) = 0;
  param_1[0x45] = (long)(puVar1 + 0x10);
  param_1[0x4b] = (long)(puVar2 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0x4e);
  puVar2 = 
  PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj175EE_02cc2fd0
  ;
  param_1[0x52] = 0;
  param_1[0x51] = 0;
  param_1[0x50] = 0;
  param_1[0x54] = 0;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj176EE_02cb9b78;
  *(undefined1 *)(param_1 + 0x55) = 0;
  param_1[0x4b] = (long)(puVar2 + 0x10);
  param_1[0x53] = (long)(puVar1 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0x56);
  puVar1 = PTR__ZTV23CParameterPropertyValueIjLj176E18CPropertyConverterE_02cb8db0;
  param_1[0x5a] = 0;
  puVar2 = PTR__ZTV22CParameterPropertyBaseILj177EE_02cbeb68;
  *(undefined1 *)(param_1 + 0x5b) = 0;
  param_1[0x53] = (long)(puVar1 + 0x10);
  param_1[0x59] = (long)(puVar2 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0x5c);
  puVar1 = PTR__ZTV23CParameterPropertyValueIjLj177E18CPropertyConverterE_02cb9920;
  param_1[0x60] = 0;
  puVar2 = PTR__ZTV22CParameterPropertyBaseILj178EE_02cc1938;
  *(undefined1 *)(param_1 + 0x61) = 0;
  param_1[0x59] = (long)(puVar1 + 0x10);
  param_1[0x5f] = (long)(puVar2 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0x62);
  puVar1 = 
  PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj178EE_02cb8b38
  ;
  param_1[0x66] = 0;
  param_1[0x65] = 0;
  param_1[100] = 0;
  param_1[0x68] = 0;
  puVar2 = PTR__ZTV22CParameterPropertyBaseILj179EE_02cbae40;
  *(undefined1 *)(param_1 + 0x69) = 0;
  param_1[0x5f] = (long)(puVar1 + 0x10);
  param_1[0x67] = (long)(puVar2 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0x6a);
  puVar2 = PTR__ZTV23CParameterPropertyValueIjLj179E18CPropertyConverterE_02cc09e0;
  param_1[0x6e] = 0;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj180EE_02cba700;
  *(undefined1 *)(param_1 + 0x6f) = 0;
  param_1[0x67] = (long)(puVar2 + 0x10);
  param_1[0x6d] = (long)(puVar1 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0x70);
  puVar2 = PTR__ZTV23CParameterPropertyValueIjLj180E18CPropertyConverterE_02cc15d0;
  param_1[0x74] = 0;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj181EE_02cbb330;
  *(undefined1 *)(param_1 + 0x75) = 0;
  param_1[0x6d] = (long)(puVar2 + 0x10);
  param_1[0x73] = (long)(puVar1 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0x76);
  puVar1 = 
  PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj181EE_02cc0890
  ;
  param_1[0x7a] = 0;
  param_1[0x79] = 0;
  param_1[0x78] = 0;
  param_1[0x7c] = 0;
  puVar2 = PTR__ZTV22CParameterPropertyBaseILj182EE_02cc2f48;
  *(undefined1 *)(param_1 + 0x7d) = 0;
  param_1[0x73] = (long)(puVar1 + 0x10);
  param_1[0x7b] = (long)(puVar2 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0x7e);
  puVar1 = PTR__ZTV23CParameterPropertyValueIjLj182E18CPropertyConverterE_02cbd910;
  param_1[0x82] = 0;
  puVar2 = PTR__ZTV22CParameterPropertyBaseILj184EE_02cc1e78;
  *(undefined1 *)(param_1 + 0x83) = 0;
  param_1[0x7b] = (long)(puVar1 + 0x10);
  param_1[0x81] = (long)(puVar2 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0x84);
  puVar1 = PTR__ZTV23CParameterPropertyValueIfLj184E18CPropertyConverterE_02cbc170;
  param_1[0x88] = 0;
  puVar2 = PTR__ZTV22CParameterPropertyBaseILj185EE_02cbd450;
  *(undefined1 *)(param_1 + 0x89) = 0;
  param_1[0x81] = (long)(puVar1 + 0x10);
  param_1[0x87] = (long)(puVar2 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0x8a);
  puVar1 = PTR__ZTV23CParameterPropertyValueIfLj185E18CPropertyConverterE_02cba4f0;
  param_1[0x8e] = 0;
  puVar2 = PTR__ZTV22CParameterPropertyBaseILj186EE_02cc2420;
  *(undefined1 *)(param_1 + 0x8f) = 0;
  param_1[0x87] = (long)(puVar1 + 0x10);
  param_1[0x8d] = (long)(puVar2 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0x90);
  puVar1 = PTR__ZTV23CParameterPropertyValueIfLj186E18CPropertyConverterE_02cbcdb0;
  param_1[0x94] = 0;
  puVar2 = PTR__ZTV22CParameterPropertyBaseILj187EE_02cbe120;
  *(undefined1 *)(param_1 + 0x95) = 0;
  param_1[0x8d] = (long)(puVar1 + 0x10);
  param_1[0x93] = (long)(puVar2 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0x96);
  puVar2 = PTR__ZTV23CParameterPropertyValueIfLj187E18CPropertyConverterE_02cbd458;
  param_1[0x9a] = 0;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj188EE_02cb7598;
  *(undefined1 *)(param_1 + 0x9b) = 0;
  param_1[0x93] = (long)(puVar2 + 0x10);
  param_1[0x99] = (long)(puVar1 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0x9c);
  puVar2 = PTR__ZTV23CParameterPropertyValueIfLj188E18CPropertyConverterE_02cc14c8;
  param_1[0xa0] = 0;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj189EE_02cb80f0;
  *(undefined1 *)(param_1 + 0xa1) = 0;
  param_1[0x99] = (long)(puVar2 + 0x10);
  param_1[0x9f] = (long)(puVar1 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0xa2);
  puVar2 = PTR__ZTV23CParameterPropertyValueIfLj189E18CPropertyConverterE_02cb81d8;
  param_1[0xa6] = 0;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj190EE_02cb75d0;
  *(undefined1 *)(param_1 + 0xa7) = 0;
  param_1[0x9f] = (long)(puVar2 + 0x10);
  param_1[0xa5] = (long)(puVar1 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0xa8);
  puVar2 = PTR__ZTV23CParameterPropertyValueIfLj190E18CPropertyConverterE_02cc3d40;
  param_1[0xac] = 0;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj192EE_02cb9fb0;
  *(undefined1 *)(param_1 + 0xad) = 0;
  param_1[0xa5] = (long)(puVar2 + 0x10);
  param_1[0xab] = (long)(puVar1 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0xae);
  puVar1 = PTR__ZTV23CParameterPropertyValueIfLj192E18CPropertyConverterE_02cba1d8;
  param_1[0xb2] = 0;
  puVar2 = PTR__ZTV22CParameterPropertyBaseILj193EE_02cbe150;
  *(undefined1 *)(param_1 + 0xb3) = 0;
  param_1[0xab] = (long)(puVar1 + 0x10);
  param_1[0xb1] = (long)(puVar2 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0xb4);
  puVar1 = PTR__ZTV23CParameterPropertyValueIfLj193E18CPropertyConverterE_02cba8c0;
  param_1[0xb8] = 0;
  puVar2 = PTR__ZTV22CParameterPropertyBaseILj194EE_02cbed70;
  *(undefined1 *)(param_1 + 0xb9) = 0;
  param_1[0xb1] = (long)(puVar1 + 0x10);
  param_1[0xb7] = (long)(puVar2 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0xba);
  puVar2 = PTR__ZTV23CParameterPropertyValueIfLj194E18CPropertyConverterE_02cc3e30;
  param_1[0xbe] = 0;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj195EE_02cb80e8;
  *(undefined1 *)(param_1 + 0xbf) = 0;
  param_1[0xb7] = (long)(puVar2 + 0x10);
  param_1[0xbd] = (long)(puVar1 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0xc0);
  puVar1 = PTR__ZTV23CParameterPropertyValueIfLj195E18CPropertyConverterE_02cb9660;
  param_1[0xc4] = 0;
  puVar2 = PTR__ZTV22CParameterPropertyBaseILj196EE_02cbebf0;
  *(undefined1 *)(param_1 + 0xc5) = 0;
  param_1[0xbd] = (long)(puVar1 + 0x10);
  param_1[0xc3] = (long)(puVar2 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0xc6);
  puVar2 = PTR__ZTV23CParameterPropertyValueIfLj196E18CPropertyConverterE_02cbdc18;
  param_1[0xca] = 0;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj197EE_02cb7220;
  *(undefined1 *)(param_1 + 0xcb) = 0;
  param_1[0xc3] = (long)(puVar2 + 0x10);
  param_1[0xc9] = (long)(puVar1 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0xcc);
  puVar1 = PTR__ZTV23CParameterPropertyValueIfLj197E18CPropertyConverterE_02cb9418;
  param_1[0xd0] = 0;
  puVar2 = PTR__ZTV22CParameterPropertyBaseILj198EE_02cc0c68;
  *(undefined1 *)(param_1 + 0xd1) = 0;
  param_1[0xc9] = (long)(puVar1 + 0x10);
  param_1[0xcf] = (long)(puVar2 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0xd2);
  puVar1 = PTR__ZTV23CParameterPropertyValueIfLj198E18CPropertyConverterE_02cb8e90;
  param_1[0xd6] = 0;
  puVar2 = PTR__ZTV22CParameterPropertyBaseILj200EE_02cbc5b0;
  *(undefined1 *)(param_1 + 0xd7) = 0;
  param_1[0xcf] = (long)(puVar1 + 0x10);
  param_1[0xd5] = (long)(puVar2 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0xd8);
  puVar1 = PTR__ZTV23CParameterPropertyValueIjLj200E18CPropertyConverterE_02cbf2d0;
  param_1[0xdc] = 0;
  puVar2 = PTR__ZTV22CParameterPropertyBaseILj201EE_02cc3250;
  *(undefined1 *)(param_1 + 0xdd) = 0;
  param_1[0xd5] = (long)(puVar1 + 0x10);
  param_1[0xdb] = (long)(puVar2 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0xde);
  puVar1 = 
  PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj201EE_02cb6ee0
  ;
  param_1[0xe2] = 0;
  param_1[0xe1] = 0;
  param_1[0xe0] = 0;
  param_1[0xe4] = 0;
  puVar2 = PTR__ZTV22CParameterPropertyBaseILj202EE_02cbef50;
  *(undefined1 *)(param_1 + 0xe5) = 0;
  param_1[0xdb] = (long)(puVar1 + 0x10);
  param_1[0xe3] = (long)(puVar2 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0xe6);
  puVar2 = PTR__ZTV23CParameterPropertyValueIjLj202E18CPropertyConverterE_02cbef10;
  param_1[0xea] = 0;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj203EE_02cb83f0;
  *(undefined1 *)(param_1 + 0xeb) = 0;
  param_1[0xe3] = (long)(puVar2 + 0x10);
  param_1[0xe9] = (long)(puVar1 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0xec);
  puVar2 = PTR__ZTV23CParameterPropertyValueIjLj203E18CPropertyConverterE_02cc3330;
  param_1[0xf0] = 0;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj205EE_02cbb3f0;
  *(undefined1 *)(param_1 + 0xf1) = 0;
  param_1[0xe9] = (long)(puVar2 + 0x10);
  param_1[0xef] = (long)(puVar1 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0xf2);
  puVar2 = PTR__ZTV23CParameterPropertyValueIjLj205E18CPropertyConverterE_02cbdcf0;
  param_1[0xf6] = 0;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj207EE_02cb6b28;
  *(undefined1 *)(param_1 + 0xf7) = 0;
  param_1[0xef] = (long)(puVar2 + 0x10);
  param_1[0xf5] = (long)(puVar1 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0xf8);
  puVar2 = PTR__ZTV23CParameterPropertyValueIjLj207E18CPropertyConverterE_02cb9b10;
  param_1[0xfc] = 0;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj208EE_02cb7680;
  *(undefined1 *)(param_1 + 0xfd) = 0;
  param_1[0xf5] = (long)(puVar2 + 0x10);
  param_1[0xfb] = (long)(puVar1 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0xfe);
  puVar1 = PTR__ZTV23CParameterPropertyValueIjLj208E18CPropertyConverterE_02cb8c28;
  param_1[0x102] = 0;
  puVar2 = PTR__ZTV22CParameterPropertyBaseILj209EE_02cc1c38;
  *(undefined1 *)(param_1 + 0x103) = 0;
  param_1[0xfb] = (long)(puVar1 + 0x10);
  param_1[0x101] = (long)(puVar2 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0x104);
  puVar1 = 
  PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj209EE_02cba138
  ;
  param_1[0x108] = 0;
  param_1[0x107] = 0;
  param_1[0x106] = 0;
  param_1[0x10a] = 0;
  puVar2 = PTR__ZTV22CParameterPropertyBaseILj210EE_02cbf870;
  *(undefined1 *)(param_1 + 0x10b) = 0;
  param_1[0x101] = (long)(puVar1 + 0x10);
  param_1[0x109] = (long)(puVar2 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0x10c);
  puVar2 = PTR__ZTV23CParameterPropertyValueIjLj210E18CPropertyConverterE_02cc4330;
  param_1[0x110] = 0;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj211EE_02cc28b0;
  *(undefined1 *)(param_1 + 0x111) = 0;
  param_1[0x109] = (long)(puVar2 + 0x10);
  param_1[0x10f] = (long)(puVar1 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0x112);
  puVar1 = PTR__ZTV23CParameterPropertyValueIjLj211E18CPropertyConverterE_02cb7058;
  param_1[0x116] = 0;
  puVar2 = PTR__ZTV22CParameterPropertyBaseILj212EE_02cbbc90;
  *(undefined1 *)(param_1 + 0x117) = 0;
  param_1[0x10f] = (long)(puVar1 + 0x10);
  param_1[0x115] = (long)(puVar2 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0x118);
  puVar2 = PTR__ZTV23CParameterPropertyValueIjLj212E18CPropertyConverterE_02cbb0d8;
  param_1[0x11c] = 0;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj214EE_02cb7ad8;
  *(undefined1 *)(param_1 + 0x11d) = 0;
  param_1[0x115] = (long)(puVar2 + 0x10);
  param_1[0x11b] = (long)(puVar1 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0x11e);
  puVar1 = PTR__ZTV23CParameterPropertyValueIjLj214E18CPropertyConverterE_02cb9230;
  param_1[0x122] = 0;
  puVar2 = PTR__ZTV22CParameterPropertyBaseILj215EE_02cbe558;
  *(undefined1 *)(param_1 + 0x123) = 0;
  param_1[0x11b] = (long)(puVar1 + 0x10);
  param_1[0x121] = (long)(puVar2 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0x124);
  puVar1 = PTR__ZTV23CParameterPropertyValueIjLj215E18CPropertyConverterE_02cb8d88;
  param_1[0x128] = 0;
  puVar2 = PTR__ZTV22CParameterPropertyBaseILj216EE_02cc16a8;
  *(undefined1 *)(param_1 + 0x129) = 0;
  param_1[0x121] = (long)(puVar1 + 0x10);
  param_1[0x127] = (long)(puVar2 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0x12a);
  puVar2 = PTR__ZTV23CParameterPropertyValueIjLj216E18CPropertyConverterE_02cc47f0;
  param_1[0x12e] = 0;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj218EE_02cbe370;
  *(undefined1 *)(param_1 + 0x12f) = 0;
  param_1[0x127] = (long)(puVar2 + 0x10);
  param_1[0x12d] = (long)(puVar1 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0x130);
  puVar2 = PTR__ZTV23CParameterPropertyValueIjLj218E18CPropertyConverterE_02cbe2c0;
  param_1[0x134] = 0;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj219EE_02cbbca8;
  *(undefined1 *)(param_1 + 0x135) = 0;
  param_1[0x12d] = (long)(puVar2 + 0x10);
  param_1[0x133] = (long)(puVar1 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0x136);
  puVar2 = PTR__ZTV23CParameterPropertyValueIjLj219E18CPropertyConverterE_02cc2f70;
  param_1[0x13a] = 0;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj220EE_02cb7ab0;
  *(undefined1 *)(param_1 + 0x13b) = 0;
  param_1[0x133] = (long)(puVar2 + 0x10);
  param_1[0x139] = (long)(puVar1 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0x13c);
  puVar1 = PTR__ZTV23CParameterPropertyValueIjLj220E18CPropertyConverterE_02cb7fb8;
  param_1[0x140] = 0;
  puVar2 = PTR__ZTV22CParameterPropertyBaseILj221EE_02cbf5d8;
  *(undefined1 *)(param_1 + 0x141) = 0;
  param_1[0x139] = (long)(puVar1 + 0x10);
  param_1[0x13f] = (long)(puVar2 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0x142);
  puVar2 = PTR__ZTV23CParameterPropertyValueIjLj221E18CPropertyConverterE_02cc1d68;
  param_1[0x146] = 0;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj222EE_02cbe6b8;
  *(undefined1 *)(param_1 + 0x147) = 0;
  param_1[0x13f] = (long)(puVar2 + 0x10);
  param_1[0x145] = (long)(puVar1 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0x148);
  puVar2 = PTR__ZTV23CParameterPropertyValueIjLj222E18CPropertyConverterE_02cbe898;
  param_1[0x14c] = 0;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj224EE_02cba9c0;
  *(undefined1 *)(param_1 + 0x14d) = 0;
  param_1[0x145] = (long)(puVar2 + 0x10);
  param_1[0x14b] = (long)(puVar1 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0x14e);
  puVar2 = PTR__ZTV23CParameterPropertyValueIbLj224E18CPropertyConverterE_02cc40a8;
  param_1[0x152] = 0;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj225EE_02cbddf0;
  *(undefined1 *)(param_1 + 0x153) = 0;
  param_1[0x14b] = (long)(puVar2 + 0x10);
  param_1[0x151] = (long)(puVar1 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0x154);
  puVar2 = PTR__ZTV23CParameterPropertyValueIbLj225E18CPropertyConverterE_02cc07f8;
  param_1[0x158] = 0;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj226EE_02cbea60;
  *(undefined1 *)(param_1 + 0x159) = 0;
  param_1[0x151] = (long)(puVar2 + 0x10);
  param_1[0x157] = (long)(puVar1 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0x15a);
  puVar1 = PTR__ZTV23CParameterPropertyValueIjLj226E18CPropertyConverterE_02cbc950;
  param_1[0x15e] = 0;
  puVar2 = PTR__ZTV22CParameterPropertyBaseILj228EE_02cbf5e8;
  *(undefined1 *)(param_1 + 0x15f) = 0;
  param_1[0x157] = (long)(puVar1 + 0x10);
  param_1[0x15d] = (long)(puVar2 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0x160);
  puVar2 = PTR__ZTV23CParameterPropertyValueIjLj228E18CPropertyConverterE_02cc2500;
  param_1[0x164] = 0;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj229EE_02cba790;
  *(undefined1 *)(param_1 + 0x165) = 0;
  param_1[0x15d] = (long)(puVar2 + 0x10);
  param_1[0x163] = (long)(puVar1 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0x166);
  puVar2 = PTR__ZTV23CParameterPropertyValueIjLj229E18CPropertyConverterE_02cc4cc8;
  param_1[0x16a] = 0;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj230EE_02cc3050;
  *(undefined1 *)(param_1 + 0x16b) = 0;
  param_1[0x163] = (long)(puVar2 + 0x10);
  param_1[0x169] = (long)(puVar1 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0x16c);
  puVar1 = PTR__ZTV23CParameterPropertyValueIjLj230E18CPropertyConverterE_02cbe4b8;
  param_1[0x170] = 0;
  puVar2 = PTR__ZTV22CParameterPropertyBaseILj231EE_02cc1ee0;
  *(undefined1 *)(param_1 + 0x171) = 0;
  param_1[0x169] = (long)(puVar1 + 0x10);
  param_1[0x16f] = (long)(puVar2 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0x172);
  puVar2 = PTR__ZTV23CParameterPropertyValueIjLj231E18CPropertyConverterE_02cc2d08;
  param_1[0x176] = 0;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj232EE_02cbee90;
  *(undefined1 *)(param_1 + 0x177) = 0;
  param_1[0x16f] = (long)(puVar2 + 0x10);
  param_1[0x175] = (long)(puVar1 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0x178);
  puVar2 = PTR__ZTV23CParameterPropertyValueIjLj232E18CPropertyConverterE_02cc05f8;
  param_1[0x17c] = 0;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj233EE_02cb7178;
  *(undefined1 *)(param_1 + 0x17d) = 0;
  param_1[0x175] = (long)(puVar2 + 0x10);
  param_1[0x17b] = (long)(puVar1 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0x17e);
  puVar2 = PTR__ZTV23CParameterPropertyValueIjLj233E18CPropertyConverterE_02cbe3e0;
  param_1[0x182] = 0;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj234EE_02cba3b8;
  *(undefined1 *)(param_1 + 0x183) = 0;
  param_1[0x17b] = (long)(puVar2 + 0x10);
  param_1[0x181] = (long)(puVar1 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0x184);
  puVar2 = PTR__ZTV23CParameterPropertyValueIjLj234E18CPropertyConverterE_02cc2bd0;
  param_1[0x188] = 0;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj236EE_02cb7068;
  *(undefined1 *)(param_1 + 0x189) = 0;
  param_1[0x181] = (long)(puVar2 + 0x10);
  param_1[0x187] = (long)(puVar1 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0x18a);
  puVar2 = PTR__ZTV23CParameterPropertyValueIjLj236E18CPropertyConverterE_02cc2178;
  param_1[0x18e] = 0;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj238EE_02cb6ed0;
  *(undefined1 *)(param_1 + 399) = 0;
  param_1[0x187] = (long)(puVar2 + 0x10);
  param_1[0x18d] = (long)(puVar1 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 400);
  puVar1 = PTR__ZTV23CParameterPropertyValueIjLj238E18CPropertyConverterE_02cbdb78;
  param_1[0x194] = 0;
  puVar2 = PTR__ZTV22CParameterPropertyBaseILj239EE_02cbedf0;
  *(undefined1 *)(param_1 + 0x195) = 0;
  param_1[0x18d] = (long)(puVar1 + 0x10);
  param_1[0x193] = (long)(puVar2 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0x196);
  puVar1 = PTR__ZTV23CParameterPropertyValueIjLj239E18CPropertyConverterE_02cb84c8;
  param_1[0x19a] = 0;
  puVar2 = PTR__ZTV22CParameterPropertyBaseILj240EE_02cc1fa0;
  *(undefined1 *)(param_1 + 0x19b) = 0;
  param_1[0x193] = (long)(puVar1 + 0x10);
  param_1[0x199] = (long)(puVar2 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0x19c);
  puVar1 = PTR__ZTV23CParameterPropertyValueIjLj240E18CPropertyConverterE_02cbeba0;
  param_1[0x1a0] = 0;
  puVar2 = PTR__ZTV22CParameterPropertyBaseILj242EE_02cc2db0;
  *(undefined1 *)(param_1 + 0x1a1) = 0;
  param_1[0x199] = (long)(puVar1 + 0x10);
  param_1[0x19f] = (long)(puVar2 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0x1a2);
  puVar2 = PTR__ZTV23CParameterPropertyValueIbLj242E18CPropertyConverterE_02cc1718;
  param_1[0x1a6] = 0;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj243EE_02cbc5c0;
  *(undefined1 *)(param_1 + 0x1a7) = 0;
  param_1[0x19f] = (long)(puVar2 + 0x10);
  param_1[0x1a5] = (long)(puVar1 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0x1a8);
  puVar1 = PTR__ZTV23CParameterPropertyValueIjLj243E18CPropertyConverterE_02cb95c8;
  param_1[0x1ac] = 0;
  puVar2 = PTR__ZTV22CParameterPropertyBaseILj244EE_02cc32b0;
  *(undefined1 *)(param_1 + 0x1ad) = 0;
  param_1[0x1a5] = (long)(puVar1 + 0x10);
  param_1[0x1ab] = (long)(puVar2 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0x1ae);
  puVar1 = PTR__ZTV23CParameterPropertyValueIjLj244E18CPropertyConverterE_02cb9768;
  param_1[0x1b2] = 0;
  puVar2 = PTR__ZTV22CParameterPropertyBaseILj245EE_02cbef20;
  *(undefined1 *)(param_1 + 0x1b3) = 0;
  param_1[0x1ab] = (long)(puVar1 + 0x10);
  param_1[0x1b1] = (long)(puVar2 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0x1b4);
  puVar2 = PTR__ZTV23CParameterPropertyValueIjLj245E18CPropertyConverterE_02cbf180;
  param_1[0x1b8] = 0;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj247EE_02cb7350;
  *(undefined1 *)(param_1 + 0x1b9) = 0;
  param_1[0x1b1] = (long)(puVar2 + 0x10);
  param_1[0x1b7] = (long)(puVar1 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0x1ba);
  puVar2 = PTR__ZTV23CParameterPropertyValueIjLj247E18CPropertyConverterE_02cbf148;
  param_1[0x1be] = 0;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj248EE_02cbb3a0;
  *(undefined1 *)(param_1 + 0x1bf) = 0;
  param_1[0x1b7] = (long)(puVar2 + 0x10);
  param_1[0x1bd] = (long)(puVar1 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0x1c0);
  puVar2 = PTR__ZTV23CParameterPropertyValueIjLj248E18CPropertyConverterE_02cc34e0;
  param_1[0x1c4] = 0;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj249EE_02cc1d38;
  *(undefined1 *)(param_1 + 0x1c5) = 0;
  param_1[0x1bd] = (long)(puVar2 + 0x10);
  param_1[0x1c3] = (long)(puVar1 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0x1c6);
  param_1[0x1ca] = (long)(param_1 + 0x1cb);
  param_1[0x1cd] = (long)(param_1 + 0x1ce);
  puVar1 = PTR__ZTV23CParameterPropertyValueIjLj249E18CPropertyConverterE_02cba140;
  param_1[0x1cc] = 0;
  param_1[0x1cb] = 0;
  param_1[0x1cf] = 0;
  param_1[0x1ce] = 0;
  param_1[0x1c3] = (long)(puVar1 + 0x10);
  puVar1 = PTR__ZTV16AssistDetailInfo_02cc23a8;
  param_1[0x1d1] = 0;
  param_1[0x1c9] = (long)(puVar1 + 0x10);
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj20EE_02cc0d08;
  *(undefined1 *)(param_1 + 0x1d2) = 0;
  param_1[0x1d0] = (long)(puVar1 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0x1d3);
  puVar2 = PTR__ZTV23CParameterPropertyValueIjLj20E18CPropertyConverterE_02cc2ce0;
  param_1[0x1d7] = 0;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj21EE_02cc1310;
  *(undefined1 *)(param_1 + 0x1d8) = 0;
  param_1[0x1d0] = (long)(puVar2 + 0x10);
  param_1[0x1d6] = (long)(puVar1 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0x1d9);
  puVar1 = PTR__ZTV23CParameterPropertyValueIjLj21E18CPropertyConverterE_02cbeae0;
  param_1[0x1dd] = 0;
  puVar2 = PTR__ZTV22CParameterPropertyBaseILj22EE_02cc4630;
  *(undefined1 *)(param_1 + 0x1de) = 0;
  param_1[0x1d6] = (long)(puVar1 + 0x10);
  param_1[0x1dc] = (long)(puVar2 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0x1df);
  param_1[0x1e3] = (long)(param_1 + 0x1e4);
  param_1[0x1e6] = (long)(param_1 + 0x1e7);
  param_1[0x1e9] = (long)(param_1 + 0x1ea);
  param_1[0x1ed] = (long)(param_1 + 0x1ee);
  param_1[0x1f0] = (long)(param_1 + 0x1f1);
  param_1[0x1f7] = (long)(param_1 + 0x1f8);
  param_1[0x1fa] = (long)(param_1 + 0x1fb);
  puVar1 = PTR__ZTV23CParameterPropertyValueIjLj22E18CPropertyConverterE_02cb7420;
  param_1[0x1e5] = 0;
  param_1[0x1e4] = 0;
  param_1[0x1e8] = 0;
  param_1[0x1e7] = 0;
  param_1[0x1eb] = 0;
  param_1[0x1ea] = 0;
  param_1[0x1dc] = (long)(puVar1 + 0x10);
  puVar1 = PTR__ZTV14CFactorInfoMap_02cb9808;
  param_1[0x1ef] = 0;
  param_1[0x1ee] = 0;
  param_1[0x1f2] = 0;
  param_1[0x1f1] = 0;
  param_1[0x1f5] = 0;
  param_1[500] = 0;
  param_1[499] = 0;
  param_1[0x1e2] = (long)(puVar1 + 0x10);
  puVar1 = PTR__ZTV28CCharacterDecoObjectInfoList_02cc4040;
  param_1[0x1f9] = 0;
  param_1[0x1f8] = 0;
  param_1[0x1fc] = 0;
  param_1[0x1fb] = 0;
  param_1[0x1ff] = 0;
  param_1[0x1fe] = 0;
  param_1[0x1fd] = 0;
  param_1[0x1ec] = (long)(puVar1 + 0x10);
  puVar1 = PTR__ZTV31UniverseEffectualTalentInfoList_02cc2e78;
  param_1[0x203] = 0;
  param_1[0x202] = 0;
  param_1[0x206] = 0;
  param_1[0x1f6] = (long)(puVar1 + 0x10);
  param_1[0x201] = (long)(param_1 + 0x202);
  param_1[0x205] = 0;
  param_1[0x204] = (long)(param_1 + 0x205);
  puVar1 = PTR__ZTV21UniverseAddStatusInfo_02cbbaf8;
  param_1[0x208] = 0;
  param_1[0x200] = (long)(puVar1 + 0x10);
  param_1[0x207] = (long)(PTR__ZTV22CParameterPropertyBaseILj61EE_02cb7008 + 0x10);
  *(undefined1 *)(param_1 + 0x209) = 0;
  Framework::CHash32::CHash32()(param_1 + 0x20a);
  puVar2 = PTR__ZTV23CParameterPropertyValueIjLj61E18CPropertyConverterE_02cc4d48;
  param_1[0x20e] = 0;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj62EE_02cbaea8 + 0x10;
  param_1[0x207] = (long)(puVar2 + 0x10);
  param_1[0x20d] = (long)puVar1;
  *(undefined1 *)(param_1 + 0x20f) = 0;
  Framework::CHash32::CHash32()(param_1 + 0x210);
  puVar2 = PTR__ZTV23CParameterPropertyValueImLj62E18CPropertyConverterE_02cc1078;
  param_1[0x214] = 0;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj63EE_02cb6de0 + 0x10;
  param_1[0x20d] = (long)(puVar2 + 0x10);
  param_1[0x213] = (long)puVar1;
  *(undefined1 *)(param_1 + 0x215) = 0;
  Framework::CHash32::CHash32()(param_1 + 0x216);
  puVar2 = PTR__ZTV23CParameterPropertyValueIjLj63E18CPropertyConverterE_02cbd2a0;
  param_1[0x21a] = 0;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj64EE_02cbbba0 + 0x10;
  param_1[0x213] = (long)(puVar2 + 0x10);
  param_1[0x219] = (long)puVar1;
  *(undefined1 *)(param_1 + 0x21b) = 0;
  Framework::CHash32::CHash32()(param_1 + 0x21c);
  puVar2 = PTR__ZTV23CParameterPropertyValueIjLj64E18CPropertyConverterE_02cb96a8;
  param_1[0x220] = 0;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj65EE_02cb79a0 + 0x10;
  param_1[0x219] = (long)(puVar2 + 0x10);
  param_1[0x21f] = (long)puVar1;
  *(undefined1 *)(param_1 + 0x221) = 0;
  Framework::CHash32::CHash32()(param_1 + 0x222);
  puVar2 = PTR__ZTV23CParameterPropertyValueIjLj65E18CPropertyConverterE_02cbf1c8;
  param_1[0x226] = 0;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj66EE_02cc1e50 + 0x10;
  param_1[0x21f] = (long)(puVar2 + 0x10);
  param_1[0x225] = (long)puVar1;
  *(undefined1 *)(param_1 + 0x227) = 0;
  Framework::CHash32::CHash32()(param_1 + 0x228);
  puVar2 = PTR__ZTV23CParameterPropertyValueIjLj66E18CPropertyConverterE_02cb79f8;
  param_1[0x22c] = 0;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj67EE_02cc15a8 + 0x10;
  param_1[0x225] = (long)(puVar2 + 0x10);
  param_1[0x22b] = (long)puVar1;
  *(undefined1 *)(param_1 + 0x22d) = 0;
  Framework::CHash32::CHash32()(param_1 + 0x22e);
  puVar2 = PTR__ZTV23CParameterPropertyValueIjLj67E18CPropertyConverterE_02cb9090;
  param_1[0x232] = 0;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj68EE_02cb7090 + 0x10;
  param_1[0x22b] = (long)(puVar2 + 0x10);
  param_1[0x231] = (long)puVar1;
  *(undefined1 *)(param_1 + 0x233) = 0;
  Framework::CHash32::CHash32()(param_1 + 0x234);
  puVar2 = PTR__ZTV23CParameterPropertyValueIjLj68E18CPropertyConverterE_02cb7310;
  param_1[0x238] = 0;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj69EE_02cb76b8 + 0x10;
  param_1[0x231] = (long)(puVar2 + 0x10);
  param_1[0x237] = (long)puVar1;
  *(undefined1 *)(param_1 + 0x239) = 0;
  Framework::CHash32::CHash32()(param_1 + 0x23a);
  puVar1 = PTR__ZTV23CParameterPropertyValueIjLj69E18CPropertyConverterE_02cb8360;
  param_1[0x240] = 0;
  param_1[0x23f] = 0;
  param_1[0x243] = 0;
  param_1[0x242] = 0;
  param_1[0x237] = (long)(puVar1 + 0x10);
  puVar17 = PTR__ZTV22UniverseDeityBoostInfo_02cc0930;
  param_1[0x245] = 0;
  param_1[0x23e] = (long)(param_1 + 0x23f);
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj153EE_02cba5e0 + 0x10;
  param_1[0x241] = (long)(param_1 + 0x242);
  param_1[0x244] = (long)puVar1;
  param_1[0x23d] = (long)(puVar17 + 0x10);
  *(undefined1 *)(param_1 + 0x246) = 0;
  Framework::CHash32::CHash32()(param_1 + 0x247);
  puVar15 = PTR__ZTV23CParameterPropertyValueIjLj153E18CPropertyConverterE_02cbe240;
  param_1[0x24b] = 0;
  puVar2 = PTR__ZTV22CParameterPropertyBaseILj154EE_02cc2120 + 0x10;
  param_1[0x244] = (long)(puVar15 + 0x10);
  param_1[0x24a] = (long)puVar2;
  *(undefined1 *)(param_1 + 0x24c) = 0;
  Framework::CHash32::CHash32()(param_1 + 0x24d);
  puVar18 = PTR__ZTV23CParameterPropertyValueImLj154E18CPropertyConverterE_02cc1380;
  param_1[0x251] = 0;
  puVar3 = PTR__ZTV22CParameterPropertyBaseILj155EE_02cc2df8 + 0x10;
  param_1[0x24a] = (long)(puVar18 + 0x10);
  param_1[0x250] = (long)puVar3;
  *(undefined1 *)(param_1 + 0x252) = 0;
  Framework::CHash32::CHash32()(param_1 + 0x253);
  puVar19 = PTR__ZTV23CParameterPropertyValueIiLj155E18CPropertyConverterE_02cc1578;
  param_1[599] = 0;
  puVar4 = PTR__ZTV22CParameterPropertyBaseILj156EE_02cbfb78 + 0x10;
  param_1[0x250] = (long)(puVar19 + 0x10);
  param_1[0x256] = (long)puVar4;
  *(undefined1 *)(param_1 + 600) = 0;
  Framework::CHash32::CHash32()(param_1 + 0x259);
  puVar14 = PTR__ZTV23CParameterPropertyValueIiLj156E18CPropertyConverterE_02cbd848;
  param_1[0x25d] = 0;
  puVar5 = PTR__ZTV22CParameterPropertyBaseILj157EE_02cb7ec0 + 0x10;
  param_1[0x256] = (long)(puVar14 + 0x10);
  param_1[0x25c] = (long)puVar5;
  *(undefined1 *)(param_1 + 0x25e) = 0;
  Framework::CHash32::CHash32()(param_1 + 0x25f);
  puVar20 = PTR__ZTV23CParameterPropertyValueIiLj157E18CPropertyConverterE_02cc3b38;
  param_1[0x263] = 0;
  puVar6 = PTR__ZTV22CParameterPropertyBaseILj158EE_02cb96c8 + 0x10;
  param_1[0x25c] = (long)(puVar20 + 0x10);
  param_1[0x262] = (long)puVar6;
  *(undefined1 *)(param_1 + 0x264) = 0;
  Framework::CHash32::CHash32()(param_1 + 0x265);
  puVar11 = PTR__ZTV23CParameterPropertyValueIiLj158E18CPropertyConverterE_02cb6a38;
  param_1[0x269] = 0;
  puVar7 = PTR__ZTV22CParameterPropertyBaseILj159EE_02cc3140 + 0x10;
  param_1[0x262] = (long)(puVar11 + 0x10);
  param_1[0x268] = (long)puVar7;
  *(undefined1 *)(param_1 + 0x26a) = 0;
  Framework::CHash32::CHash32()(param_1 + 0x26b);
  puVar21 = PTR__ZTV23CParameterPropertyValueIiLj159E18CPropertyConverterE_02cc4eb0;
  param_1[0x26f] = 0;
  puVar8 = PTR__ZTV22CParameterPropertyBaseILj160EE_02cc2440 + 0x10;
  param_1[0x268] = (long)(puVar21 + 0x10);
  param_1[0x26e] = (long)puVar8;
  *(undefined1 *)(param_1 + 0x270) = 0;
  Framework::CHash32::CHash32()(param_1 + 0x271);
  puVar13 = PTR__ZTV23CParameterPropertyValueIiLj160E18CPropertyConverterE_02cba800;
  param_1[0x275] = 0;
  puVar9 = PTR__ZTV22CParameterPropertyBaseILj161EE_02cbaad0 + 0x10;
  param_1[0x26e] = (long)(puVar13 + 0x10);
  param_1[0x274] = (long)puVar9;
  *(undefined1 *)(param_1 + 0x276) = 0;
  Framework::CHash32::CHash32()(param_1 + 0x277);
  puVar12 = PTR__ZTV23CParameterPropertyValueIiLj161E18CPropertyConverterE_02cb9458;
  param_1[0x27b] = (long)(param_1 + 0x27c);
  param_1[0x27d] = 0;
  param_1[0x27c] = 0;
  param_1[0x280] = 0;
  param_1[0x27f] = 0;
  param_1[0x27e] = (long)(param_1 + 0x27f);
  puVar10 = PTR__ZTV9DeityInfo_02cc11d0;
  param_1[0x282] = 0;
  param_1[0x27a] = (long)(puVar10 + 0x10);
  puVar10 = PTR__ZTV22CParameterPropertyBaseILj47EE_02cba780;
  param_1[0x274] = (long)(puVar12 + 0x10);
  param_1[0x281] = (long)(puVar10 + 0x10);
  *(undefined1 *)(param_1 + 0x283) = 0;
  Framework::CHash32::CHash32()(param_1 + 0x284);
  puVar16 = PTR__ZTV23CParameterPropertyValueIjLj47E18CPropertyConverterE_02cc0678;
  param_1[0x288] = 0;
  puVar10 = PTR__ZTV22CParameterPropertyBaseILj48EE_02cba0d0 + 0x10;
  param_1[0x281] = (long)(puVar16 + 0x10);
  param_1[0x287] = (long)puVar10;
  *(undefined1 *)(param_1 + 0x289) = 0;
  Framework::CHash32::CHash32()(param_1 + 0x28a);
  puVar16 = PTR__ZTV23CParameterPropertyValueIjLj48E18CPropertyConverterE_02cc4e68;
  param_1[0x28e] = 0;
  puVar10 = PTR__ZTV22CParameterPropertyBaseILj49EE_02cc4550 + 0x10;
  param_1[0x287] = (long)(puVar16 + 0x10);
  param_1[0x28d] = (long)puVar10;
  *(undefined1 *)(param_1 + 0x28f) = 0;
  Framework::CHash32::CHash32()(param_1 + 0x290);
  puVar10 = PTR__ZTV23CParameterPropertyValueIjLj49E18CPropertyConverterE_02cc0590;
  param_1[0x296] = 0;
  param_1[0x295] = 0;
  param_1[0x293] = (long)(puVar17 + 0x10);
  param_1[0x294] = (long)(param_1 + 0x295);
  param_1[0x29a] = (long)puVar1;
  param_1[0x28d] = (long)(puVar10 + 0x10);
  param_1[0x299] = 0;
  param_1[0x298] = 0;
  param_1[0x29b] = 0;
  param_1[0x297] = (long)(param_1 + 0x298);
  *(undefined1 *)(param_1 + 0x29c) = 0;
  Framework::CHash32::CHash32()(param_1 + 0x29d);
  param_1[0x2a1] = 0;
  param_1[0x29a] = (long)(puVar15 + 0x10);
  param_1[0x2a0] = (long)puVar2;
  *(undefined1 *)(param_1 + 0x2a2) = 0;
  Framework::CHash32::CHash32()(param_1 + 0x2a3);
  param_1[0x2a7] = 0;
  param_1[0x2a0] = (long)(puVar18 + 0x10);
  param_1[0x2a6] = (long)puVar3;
  *(undefined1 *)(param_1 + 0x2a8) = 0;
  Framework::CHash32::CHash32()(param_1 + 0x2a9);
  param_1[0x2ad] = 0;
  param_1[0x2a6] = (long)(puVar19 + 0x10);
  param_1[0x2ac] = (long)puVar4;
  *(undefined1 *)(param_1 + 0x2ae) = 0;
  Framework::CHash32::CHash32()(param_1 + 0x2af);
  param_1[0x2ac] = (long)(puVar14 + 0x10);
  param_1[0x2b3] = 0;
  param_1[0x2b2] = (long)puVar5;
  *(undefined1 *)(param_1 + 0x2b4) = 0;
  Framework::CHash32::CHash32()(param_1 + 0x2b5);
  param_1[0x2b2] = (long)(puVar20 + 0x10);
  param_1[0x2b9] = 0;
  param_1[0x2b8] = (long)puVar6;
  *(undefined1 *)(param_1 + 0x2ba) = 0;
  Framework::CHash32::CHash32()(param_1 + 699);
  param_1[0x2b8] = (long)(puVar11 + 0x10);
  param_1[0x2bf] = 0;
  param_1[0x2be] = (long)puVar7;
  *(undefined1 *)(param_1 + 0x2c0) = 0;
  Framework::CHash32::CHash32()(param_1 + 0x2c1);
  param_1[0x2be] = (long)(puVar21 + 0x10);
  param_1[0x2c5] = 0;
  param_1[0x2c4] = (long)puVar8;
  *(undefined1 *)(param_1 + 0x2c6) = 0;
  Framework::CHash32::CHash32()(param_1 + 0x2c7);
  param_1[0x2c4] = (long)(puVar13 + 0x10);
  param_1[0x2cb] = 0;
  param_1[0x2ca] = (long)puVar9;
  *(undefined1 *)(param_1 + 0x2cc) = 0;
  Framework::CHash32::CHash32()(param_1 + 0x2cd);
  param_1[0x2ca] = (long)(puVar12 + 0x10);
  param_1[0x293] = (long)(PTR__ZTV23AddBuffByDeityCharacter_02cc2950 + 0x10);
  return;
}

// ==== CPersonStatusInfo::~CPersonStatusInfo()
// vaddr 0x12a6840 | ghidra 0x13a6840 | size 3356 | symbol _ZN17CPersonStatusInfoD2Ev | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Possible PIC construction at 0x013a69ac: Changing call to branch */
/* WARNING: Possible PIC construction at 0x013a6a34: Changing call to branch */
/* WARNING: Possible PIC construction at 0x013a6af0: Changing call to branch */
/* WARNING: Possible PIC construction at 0x013a6c20: Changing call to branch */
/* WARNING: Possible PIC construction at 0x013a6c88: Changing call to branch */
/* WARNING: Possible PIC construction at 0x013a6ce8: Changing call to branch */
/* WARNING: Possible PIC construction at 0x013a6d10: Changing call to branch */
/* WARNING: Possible PIC construction at 0x013a6d84: Changing call to branch */
/* WARNING: Removing unreachable block (ram,0x013a6d14) */
/* WARNING: Removing unreachable block (ram,0x013a6cec) */
/* WARNING: Removing unreachable block (ram,0x013a6c8c) */
/* WARNING: Removing unreachable block (ram,0x013a6c9c) */
/* WARNING: Removing unreachable block (ram,0x013a6ca8) */
/* WARNING: Removing unreachable block (ram,0x013a6cc0) */
/* WARNING: Removing unreachable block (ram,0x013a6cc4) */
/* WARNING: Removing unreachable block (ram,0x013a6ccc) */
/* WARNING: Removing unreachable block (ram,0x013a6c24) */
/* WARNING: Removing unreachable block (ram,0x013a6c2c) */
/* WARNING: Removing unreachable block (ram,0x013a6c38) */
/* WARNING: Removing unreachable block (ram,0x013a6c44) */
/* WARNING: Removing unreachable block (ram,0x013a6c64) */
/* WARNING: Removing unreachable block (ram,0x013a6c68) */
/* WARNING: Removing unreachable block (ram,0x013a6c70) */
/* WARNING: Removing unreachable block (ram,0x013a6af4) */
/* WARNING: Removing unreachable block (ram,0x013a6a38) */
/* WARNING: Removing unreachable block (ram,0x013a69b0) */
/* WARNING: Removing unreachable block (ram,0x013a6d88) */
/* WARNING: Removing unreachable block (ram,0x013a70a0) */
/* WARNING: Removing unreachable block (ram,0x013a70a8) */
/* WARNING: Removing unreachable block (ram,0x013a7150) */
/* WARNING: Removing unreachable block (ram,0x013a7158) */
/* WARNING: Removing unreachable block (ram,0x013a7308) */
/* WARNING: Removing unreachable block (ram,0x013a7310) */
/* WARNING: Removing unreachable block (ram,0x013a7370) */
/* WARNING: Removing unreachable block (ram,0x013a7378) */
/* WARNING: Removing unreachable block (ram,0x013a73d8) */
/* WARNING: Removing unreachable block (ram,0x013a73e0) */
/* WARNING: Removing unreachable block (ram,0x013a74d0) */
/* WARNING: Removing unreachable block (ram,0x013a74d8) */

void _ZN17CPersonStatusInfoD2Ev(long *param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  
  puVar1 = PTR__ZTV22UniverseDeityBoostInfo_02cc0930 + 0x10;
  puVar2 = PTR__ZTV22CParameterPropertyBaseILj161EE_02cbaad0 + 0x10;
  *param_1 = (long)(PTR__ZTV17CPersonStatusInfo_02cbd500 + 0x10);
  param_1[0x293] = (long)puVar1;
  param_1[0x2ca] = (long)puVar2;
  Framework::CHash32::~CHash32()(param_1 + 0x2cd);
  param_1[0x2c4] = (long)(PTR__ZTV22CParameterPropertyBaseILj160EE_02cc2440 + 0x10);
  Framework::CHash32::~CHash32()(param_1 + 0x2c7);
  param_1[0x2be] = (long)(PTR__ZTV22CParameterPropertyBaseILj159EE_02cc3140 + 0x10);
  Framework::CHash32::~CHash32()(param_1 + 0x2c1);
  param_1[0x2b8] = (long)(PTR__ZTV22CParameterPropertyBaseILj158EE_02cb96c8 + 0x10);
  Framework::CHash32::~CHash32()(param_1 + 699);
  param_1[0x2b2] = (long)(PTR__ZTV22CParameterPropertyBaseILj157EE_02cb7ec0 + 0x10);
  Framework::CHash32::~CHash32()(param_1 + 0x2b5);
  param_1[0x2ac] = (long)(PTR__ZTV22CParameterPropertyBaseILj156EE_02cbfb78 + 0x10);
  Framework::CHash32::~CHash32()(param_1 + 0x2af);
  param_1[0x2a6] = (long)(PTR__ZTV22CParameterPropertyBaseILj155EE_02cc2df8 + 0x10);
  Framework::CHash32::~CHash32()(param_1 + 0x2a9);
  param_1[0x2a0] = (long)(PTR__ZTV22CParameterPropertyBaseILj154EE_02cc2120 + 0x10);
  Framework::CHash32::~CHash32()(param_1 + 0x2a3);
  param_1[0x29a] = (long)(PTR__ZTV22CParameterPropertyBaseILj153EE_02cba5e0 + 0x10);
  Framework::CHash32::~CHash32()(param_1 + 0x29d);
  param_1[0x293] = (long)(PTR__ZTV8InfoBase_02cc49c8 + 0x10);
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*)(param_1 + 0x297,param_1[0x298]);
  (*(code *)
    PTR__ZNSt6__ndk16__treeINS_12__value_typeIjP18IParameterPropertyEENS_19__map_value_compareIjS4_NS_4lessIjEELb1EEEN9Framework13CSTLAllocatorIS4_NS9_19CSTLMapAllocatorInfEEEE7destroyEPNS_11__tree_nodeIS4_PvEE_02cad958
  )(param_1 + 0x294,param_1[0x295]);
  return;
}

// ==== CPersonStatusInfo::Initialize()
// vaddr 0x12ae5e8 | ghidra 0x13ae5e8 | size 10536 | symbol _ZN17CPersonStatusInfo10InitializeEv | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN17CPersonStatusInfo10InitializeEv(long param_1)

{
  long lVar1;
  long lVar2;
  ulong uVar3;
  undefined8 *puVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  byte bVar8;
  undefined2 uVar9;
  undefined1 uVar10;
  undefined1 uVar11;
  undefined1 uVar12;
  undefined1 uVar13;
  undefined1 uVar14;
  undefined1 uVar15;
  undefined1 uVar16;
  undefined1 uVar17;
  undefined1 uVar18;
  undefined1 uVar19;
  undefined1 uVar20;
  undefined1 uVar21;
  undefined1 uVar22;
  undefined4 uVar23;
  undefined8 *puVar24;
  undefined8 uVar25;
  long *plStack_78;
  ulong uStack_70;
  undefined8 uStack_68;
  byte bStack_60;
  undefined2 uStack_5f;
  undefined1 uStack_5d;
  undefined1 uStack_5c;
  undefined1 uStack_5b;
  undefined1 uStack_5a;
  undefined1 uStack_59;
  undefined1 uStack_58;
  undefined1 uStack_57;
  undefined1 uStack_56;
  undefined1 uStack_55;
  undefined1 uStack_54;
  undefined1 uStack_53;
  undefined1 uStack_52;
  undefined1 uStack_51;
  undefined1 uStack_50;
  undefined1 uStack_4f;
  undefined1 uStack_4e;
  undefined1 uStack_4d;
  undefined1 uStack_4c;
  undefined1 uStack_4b;
  undefined1 uStack_4a;
  undefined1 uStack_49;
  
  uStack_58 = 0;
  uStack_57 = 0;
  uStack_56 = 0;
  uStack_55 = 0;
  uStack_54 = 0;
  uStack_53 = 0;
  uStack_52 = 0;
  uStack_51 = 0;
  uStack_50 = 0;
  uStack_4f = 0;
  uStack_4e = 0;
  uStack_4d = 0;
  uStack_4c = 0;
  uStack_4b = 0;
  uStack_4a = 0;
  uStack_49 = 0;
  uStack_5c = 0;
  uStack_5b = 0;
  uStack_5a = 0;
  uStack_59 = 0;
  bStack_60 = 4;
  uStack_5f = 0x6469;
  uStack_5d = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x50,(ulong)&bStack_60 | 1);
  *(undefined1 *)(param_1 + 0x48) = 1;
  *(undefined8 *)(param_1 + 0x60) = 0;
  if ((bStack_60 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(CONCAT17(uStack_49,
                             CONCAT16(uStack_4a,
                                      CONCAT15(uStack_4b,
                                               CONCAT14(uStack_4c,
                                                        CONCAT13(uStack_4d,
                                                                 CONCAT12(uStack_4e,
                                                                          CONCAT11(uStack_4f,
                                                                                   uStack_50))))))))
    ;
  }
  lVar1 = param_1 + 0x38;
  bStack_60 = (byte)lVar1;
  uStack_5f = (undefined2)((ulong)lVar1 >> 8);
  uStack_5d = (undefined1)((ulong)lVar1 >> 0x18);
  uStack_5c = (undefined1)((ulong)lVar1 >> 0x20);
  uStack_5b = (undefined1)((ulong)lVar1 >> 0x28);
  uStack_5a = (undefined1)((ulong)lVar1 >> 0x30);
  uStack_59 = (undefined1)((ulong)lVar1 >> 0x38);
  uVar23 = (**(code **)(*(long *)(param_1 + 0x38) + 0x10))();
  lVar1 = param_1 + 8;
  plStack_78 = (long *)CONCAT44(plStack_78._4_4_,uVar23);
  std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, unsigned int, IParameterProperty*&>(unsigned int const&, unsigned int&&, IParameterProperty*&)(lVar1,&plStack_78,&plStack_78,&bStack_60);
  uStack_55 = 0;
  uStack_54 = 0;
  uStack_53 = 0;
  uStack_52 = 0;
  uStack_51 = 0;
  uStack_50 = 0;
  uStack_4f = 0;
  uStack_4e = 0;
  uStack_4d = 0;
  uStack_4c = 0;
  uStack_4b = 0;
  uStack_4a = 0;
  uStack_49 = 0;
  bStack_60 = 0x12;
  uStack_5f = (undefined2)_UNK_028ea11e;
  uStack_5d = (undefined1)((ulong)_UNK_028ea11e >> 0x10);
  uStack_5c = (undefined1)((ulong)_UNK_028ea11e >> 0x18);
  uStack_5b = (undefined1)((ulong)_UNK_028ea11e >> 0x20);
  uStack_5a = (undefined1)((ulong)_UNK_028ea11e >> 0x28);
  uStack_59 = (undefined1)((ulong)_UNK_028ea11e >> 0x30);
  uStack_58 = (undefined1)((ulong)_UNK_028ea11e >> 0x38);
  uStack_57 = 100;
  uStack_56 = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x80,(ulong)&bStack_60 | 1);
  *(undefined1 *)(param_1 + 0x78) = 1;
  *(undefined4 *)(param_1 + 0x90) = 0;
  if ((bStack_60 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(CONCAT17(uStack_49,
                             CONCAT16(uStack_4a,
                                      CONCAT15(uStack_4b,
                                               CONCAT14(uStack_4c,
                                                        CONCAT13(uStack_4d,
                                                                 CONCAT12(uStack_4e,
                                                                          CONCAT11(uStack_4f,
                                                                                   uStack_50))))))))
    ;
  }
  lVar2 = param_1 + 0x68;
  bStack_60 = (byte)lVar2;
  uStack_5f = (undefined2)((ulong)lVar2 >> 8);
  uStack_5d = (undefined1)((ulong)lVar2 >> 0x18);
  uStack_5c = (undefined1)((ulong)lVar2 >> 0x20);
  uStack_5b = (undefined1)((ulong)lVar2 >> 0x28);
  uStack_5a = (undefined1)((ulong)lVar2 >> 0x30);
  uStack_59 = (undefined1)((ulong)lVar2 >> 0x38);
  uVar23 = (**(code **)(*(long *)(param_1 + 0x68) + 0x10))();
  plStack_78 = (long *)CONCAT44(plStack_78._4_4_,uVar23);
  std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, unsigned int, IParameterProperty*&>(unsigned int const&, unsigned int&&, IParameterProperty*&)(lVar1,&plStack_78,&plStack_78,&bStack_60);
  uStack_52 = 0;
  uStack_51 = 0;
  uStack_50 = 0;
  uStack_4f = 0;
  uStack_4e = 0;
  uStack_4d = 0;
  uStack_4c = 0;
  uStack_4b = 0;
  uStack_4a = 0;
  uStack_49 = 0;
  bStack_60 = 0x18;
  uStack_5f = (undefined2)_UNK_02846c65;
  uStack_5d = (undefined1)((ulong)_UNK_02846c65 >> 0x10);
  uStack_5c = (undefined1)((ulong)_UNK_02846c65 >> 0x18);
  uStack_5b = (undefined1)((ulong)_UNK_02846c65 >> 0x20);
  uStack_5a = (undefined1)((ulong)_UNK_02846c65 >> 0x28);
  uStack_59 = (undefined1)((ulong)_UNK_02846c65 >> 0x30);
  uStack_58 = (undefined1)((ulong)_UNK_02846c65 >> 0x38);
  uStack_57 = 0x65;
  uStack_56 = 0x76;
  uStack_55 = 0x65;
  uStack_54 = 0x6c;
  uStack_53 = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0xf0,(ulong)&bStack_60 | 1);
  *(undefined1 *)(param_1 + 0xe8) = 1;
  *(undefined4 *)(param_1 + 0x100) = 0;
  if ((bStack_60 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(CONCAT17(uStack_49,
                             CONCAT16(uStack_4a,
                                      CONCAT15(uStack_4b,
                                               CONCAT14(uStack_4c,
                                                        CONCAT13(uStack_4d,
                                                                 CONCAT12(uStack_4e,
                                                                          CONCAT11(uStack_4f,
                                                                                   uStack_50))))))))
    ;
  }
  lVar2 = param_1 + 0xd8;
  bStack_60 = (byte)lVar2;
  uStack_5f = (undefined2)((ulong)lVar2 >> 8);
  uStack_5d = (undefined1)((ulong)lVar2 >> 0x18);
  uStack_5c = (undefined1)((ulong)lVar2 >> 0x20);
  uStack_5b = (undefined1)((ulong)lVar2 >> 0x28);
  uStack_5a = (undefined1)((ulong)lVar2 >> 0x30);
  uStack_59 = (undefined1)((ulong)lVar2 >> 0x38);
  uVar23 = (**(code **)(*(long *)(param_1 + 0xd8) + 0x10))();
  plStack_78 = (long *)CONCAT44(plStack_78._4_4_,uVar23);
  std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, unsigned int, IParameterProperty*&>(unsigned int const&, unsigned int&&, IParameterProperty*&)(lVar1,&plStack_78,&plStack_78,&bStack_60);
  uStack_53 = 0;
  uStack_52 = 0;
  uStack_51 = 0;
  uStack_50 = 0;
  uStack_4f = 0;
  uStack_4e = 0;
  uStack_4d = 0;
  uStack_4c = 0;
  uStack_4b = 0;
  uStack_4a = 0;
  uStack_49 = 0;
  uStack_68 = 0;
  plStack_78 = (long *)0x0;
  uStack_70 = 0;
  bStack_60 = 0x16;
  uStack_5f = (undefined2)_UNK_02891dee;
  uStack_5d = (undefined1)((ulong)_UNK_02891dee >> 0x10);
  uStack_5c = (undefined1)((ulong)_UNK_02891dee >> 0x18);
  uStack_5b = (undefined1)((ulong)_UNK_02891dee >> 0x20);
  uStack_5a = (undefined1)((ulong)_UNK_02891dee >> 0x28);
  uStack_59 = (undefined1)((ulong)_UNK_02891dee >> 0x30);
  uStack_58 = (undefined1)((ulong)_UNK_02891dee >> 0x38);
  uStack_57 = 0x61;
  uStack_56 = 0x6d;
  uStack_55 = 0x65;
  uStack_54 = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0xb0,(ulong)&bStack_60 | 1);
  *(undefined1 *)(param_1 + 0xa8) = 1;
  uVar3 = (ulong)plStack_78 >> 1 & 0x7f;
  if (((ulong)plStack_78 & 1) != 0) {
    uVar3 = uStack_70;
  }
  if (uVar3 != 0) {
    void CParameterPropertyBase<165u>::CryptString<string >(string&, string const&)(param_1 + 0xc0,&plStack_78);
  }
  if (((ulong)plStack_78 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_68);
  }
  if ((bStack_60 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(CONCAT17(uStack_49,
                             CONCAT16(uStack_4a,
                                      CONCAT15(uStack_4b,
                                               CONCAT14(uStack_4c,
                                                        CONCAT13(uStack_4d,
                                                                 CONCAT12(uStack_4e,
                                                                          CONCAT11(uStack_4f,
                                                                                   uStack_50))))))))
    ;
  }
  lVar2 = param_1 + 0x98;
  bStack_60 = (byte)lVar2;
  uStack_5f = (undefined2)((ulong)lVar2 >> 8);
  uStack_5d = (undefined1)((ulong)lVar2 >> 0x18);
  uStack_5c = (undefined1)((ulong)lVar2 >> 0x20);
  uStack_5b = (undefined1)((ulong)lVar2 >> 0x28);
  uStack_5a = (undefined1)((ulong)lVar2 >> 0x30);
  uStack_59 = (undefined1)((ulong)lVar2 >> 0x38);
  uVar23 = (**(code **)(*(long *)(param_1 + 0x98) + 0x10))();
  plStack_78 = (long *)CONCAT44(plStack_78._4_4_,uVar23);
  std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, unsigned int, IParameterProperty*&>(unsigned int const&, unsigned int&&, IParameterProperty*&)(lVar1,&plStack_78,&plStack_78,&bStack_60);
  uStack_50 = 0;
  uStack_4f = 0;
  uStack_4e = 0;
  uStack_4d = 0;
  uStack_4c = 0;
  uStack_4b = 0;
  uStack_4a = 0;
  uStack_49 = 0;
  bStack_60 = 0x1c;
  uStack_5f = (undefined2)_UNK_0280cbe6;
  uStack_5d = (undefined1)((uint6)_UNK_0280cbe6 >> 0x10);
  uStack_5c = (undefined1)((uint6)_UNK_0280cbe6 >> 0x18);
  uStack_5b = (undefined1)((uint6)_UNK_0280cbe6 >> 0x20);
  uStack_5a = (undefined1)((uint6)_UNK_0280cbe6 >> 0x28);
  uStack_59 = (undefined1)_UNK_0280cbec;
  uStack_58 = (undefined1)((ushort)_UNK_0280cbec >> 8);
  uStack_57 = (undefined1)_UNK_0280cbee;
  uStack_56 = (undefined1)((uint6)_UNK_0280cbee >> 8);
  uStack_55 = (undefined1)((uint6)_UNK_0280cbee >> 0x10);
  uStack_54 = (undefined1)((uint6)_UNK_0280cbee >> 0x18);
  uStack_53 = (undefined1)((uint6)_UNK_0280cbee >> 0x20);
  uStack_52 = (undefined1)((uint6)_UNK_0280cbee >> 0x28);
  uStack_51 = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x120,(ulong)&bStack_60 | 1);
  *(undefined1 *)(param_1 + 0x118) = 1;
  *(undefined4 *)(param_1 + 0x130) = 0;
  if ((bStack_60 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(CONCAT17(uStack_49,
                             CONCAT16(uStack_4a,
                                      CONCAT15(uStack_4b,
                                               CONCAT14(uStack_4c,
                                                        CONCAT13(uStack_4d,
                                                                 CONCAT12(uStack_4e,
                                                                          CONCAT11(uStack_4f,
                                                                                   uStack_50))))))))
    ;
  }
  lVar2 = param_1 + 0x108;
  bStack_60 = (byte)lVar2;
  uStack_5f = (undefined2)((ulong)lVar2 >> 8);
  uStack_5d = (undefined1)((ulong)lVar2 >> 0x18);
  uStack_5c = (undefined1)((ulong)lVar2 >> 0x20);
  uStack_5b = (undefined1)((ulong)lVar2 >> 0x28);
  uStack_5a = (undefined1)((ulong)lVar2 >> 0x30);
  uStack_59 = (undefined1)((ulong)lVar2 >> 0x38);
  uVar23 = (**(code **)(*(long *)(param_1 + 0x108) + 0x10))();
  plStack_78 = (long *)CONCAT44(plStack_78._4_4_,uVar23);
  std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, unsigned int, IParameterProperty*&>(unsigned int const&, unsigned int&&, IParameterProperty*&)(lVar1,&plStack_78,&plStack_78,&bStack_60);
  uStack_50 = 0;
  uStack_4f = 0;
  uStack_4e = 0;
  uStack_4d = 0;
  uStack_4c = 0;
  uStack_4b = 0;
  uStack_4a = 0;
  uStack_49 = 0;
  bStack_60 = 0x1c;
  uStack_5f = (undefined2)_UNK_027fb1f1;
  uStack_5d = (undefined1)((uint6)_UNK_027fb1f1 >> 0x10);
  uStack_5c = (undefined1)((uint6)_UNK_027fb1f1 >> 0x18);
  uStack_5b = (undefined1)((uint6)_UNK_027fb1f1 >> 0x20);
  uStack_5a = (undefined1)((uint6)_UNK_027fb1f1 >> 0x28);
  uStack_59 = (undefined1)_UNK_027fb1f7;
  uStack_58 = (undefined1)((ushort)_UNK_027fb1f7 >> 8);
  uStack_57 = (undefined1)_UNK_027fb1f9;
  uStack_56 = (undefined1)((uint6)_UNK_027fb1f9 >> 8);
  uStack_55 = (undefined1)((uint6)_UNK_027fb1f9 >> 0x10);
  uStack_54 = (undefined1)((uint6)_UNK_027fb1f9 >> 0x18);
  uStack_53 = (undefined1)((uint6)_UNK_027fb1f9 >> 0x20);
  uStack_52 = (undefined1)((uint6)_UNK_027fb1f9 >> 0x28);
  uStack_51 = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x150,(ulong)&bStack_60 | 1);
  *(undefined1 *)(param_1 + 0x148) = 1;
  *(undefined8 *)(param_1 + 0x160) = 0;
  if ((bStack_60 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(CONCAT17(uStack_49,
                             CONCAT16(uStack_4a,
                                      CONCAT15(uStack_4b,
                                               CONCAT14(uStack_4c,
                                                        CONCAT13(uStack_4d,
                                                                 CONCAT12(uStack_4e,
                                                                          CONCAT11(uStack_4f,
                                                                                   uStack_50))))))))
    ;
  }
  lVar2 = param_1 + 0x138;
  bStack_60 = (byte)lVar2;
  uStack_5f = (undefined2)((ulong)lVar2 >> 8);
  uStack_5d = (undefined1)((ulong)lVar2 >> 0x18);
  uStack_5c = (undefined1)((ulong)lVar2 >> 0x20);
  uStack_5b = (undefined1)((ulong)lVar2 >> 0x28);
  uStack_5a = (undefined1)((ulong)lVar2 >> 0x30);
  uStack_59 = (undefined1)((ulong)lVar2 >> 0x38);
  uVar23 = (**(code **)(*(long *)(param_1 + 0x138) + 0x10))();
  plStack_78 = (long *)CONCAT44(plStack_78._4_4_,uVar23);
  std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, unsigned int, IParameterProperty*&>(unsigned int const&, unsigned int&&, IParameterProperty*&)(lVar1,&plStack_78,&plStack_78,&bStack_60);
  uStack_4d = 0;
  uStack_4c = 0;
  uStack_4b = 0;
  uStack_4a = 0;
  uStack_49 = 0;
  bStack_60 = 0x22;
  uStack_57 = (undefined1)_UNK_027fb208;
  uStack_56 = (undefined1)((ulong)_UNK_027fb208 >> 8);
  uStack_55 = (undefined1)((ulong)_UNK_027fb208 >> 0x10);
  uStack_54 = (undefined1)((ulong)_UNK_027fb208 >> 0x18);
  uStack_53 = (undefined1)((ulong)_UNK_027fb208 >> 0x20);
  uStack_52 = (undefined1)((ulong)_UNK_027fb208 >> 0x28);
  uStack_51 = (undefined1)((ulong)_UNK_027fb208 >> 0x30);
  uStack_50 = (undefined1)((ulong)_UNK_027fb208 >> 0x38);
  uStack_5f = (undefined2)_UNK_027fb200;
  uStack_5d = (undefined1)((ulong)_UNK_027fb200 >> 0x10);
  uStack_5c = (undefined1)((ulong)_UNK_027fb200 >> 0x18);
  uStack_5b = (undefined1)((ulong)_UNK_027fb200 >> 0x20);
  uStack_5a = (undefined1)((ulong)_UNK_027fb200 >> 0x28);
  uStack_59 = (undefined1)((ulong)_UNK_027fb200 >> 0x30);
  uStack_58 = (undefined1)((ulong)_UNK_027fb200 >> 0x38);
  uStack_4f = 100;
  uStack_4e = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x180,(ulong)&bStack_60 | 1);
  *(undefined1 *)(param_1 + 0x178) = 1;
  *(undefined8 *)(param_1 + 400) = 0;
  if ((bStack_60 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(CONCAT17(uStack_49,
                             CONCAT16(uStack_4a,
                                      CONCAT15(uStack_4b,
                                               CONCAT14(uStack_4c,
                                                        CONCAT13(uStack_4d,
                                                                 CONCAT12(uStack_4e,
                                                                          CONCAT11(uStack_4f,
                                                                                   uStack_50))))))))
    ;
  }
  lVar2 = param_1 + 0x168;
  bStack_60 = (byte)lVar2;
  uStack_5f = (undefined2)((ulong)lVar2 >> 8);
  uStack_5d = (undefined1)((ulong)lVar2 >> 0x18);
  uStack_5c = (undefined1)((ulong)lVar2 >> 0x20);
  uStack_5b = (undefined1)((ulong)lVar2 >> 0x28);
  uStack_5a = (undefined1)((ulong)lVar2 >> 0x30);
  uStack_59 = (undefined1)((ulong)lVar2 >> 0x38);
  uVar23 = (**(code **)(*(long *)(param_1 + 0x168) + 0x10))();
  plStack_78 = (long *)CONCAT44(plStack_78._4_4_,uVar23);
  std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, unsigned int, IParameterProperty*&>(unsigned int const&, unsigned int&&, IParameterProperty*&)(lVar1,&plStack_78,&plStack_78,&bStack_60);
  uStack_58 = 0;
  uStack_57 = 0;
  uStack_56 = 0;
  uStack_55 = 0;
  uStack_54 = 0;
  uStack_53 = 0;
  uStack_52 = 0;
  uStack_51 = 0;
  uStack_50 = 0;
  uStack_4f = 0;
  uStack_4e = 0;
  uStack_4d = 0;
  uStack_4c = 0;
  uStack_4b = 0;
  uStack_4a = 0;
  uStack_49 = 0;
  uStack_59 = 0;
  bStack_60 = 10;
  uStack_5b = 0x6c;
  uStack_5f = 0x656c;
  uStack_5d = 0x76;
  uStack_5c = 0x65;
  uStack_5a = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x1b0,(ulong)&bStack_60 | 1);
  *(undefined1 *)(param_1 + 0x1a8) = 1;
  *(undefined4 *)(param_1 + 0x1c0) = 0;
  if ((bStack_60 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(CONCAT17(uStack_49,
                             CONCAT16(uStack_4a,
                                      CONCAT15(uStack_4b,
                                               CONCAT14(uStack_4c,
                                                        CONCAT13(uStack_4d,
                                                                 CONCAT12(uStack_4e,
                                                                          CONCAT11(uStack_4f,
                                                                                   uStack_50))))))))
    ;
  }
  lVar2 = param_1 + 0x198;
  bStack_60 = (byte)lVar2;
  uStack_5f = (undefined2)((ulong)lVar2 >> 8);
  uStack_5d = (undefined1)((ulong)lVar2 >> 0x18);
  uStack_5c = (undefined1)((ulong)lVar2 >> 0x20);
  uStack_5b = (undefined1)((ulong)lVar2 >> 0x28);
  uStack_5a = (undefined1)((ulong)lVar2 >> 0x30);
  uStack_59 = (undefined1)((ulong)lVar2 >> 0x38);
  uVar23 = (**(code **)(*(long *)(param_1 + 0x198) + 0x10))();
  plStack_78 = (long *)CONCAT44(plStack_78._4_4_,uVar23);
  std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, unsigned int, IParameterProperty*&>(unsigned int const&, unsigned int&&, IParameterProperty*&)(lVar1,&plStack_78,&plStack_78,&bStack_60);
  uStack_58 = 0;
  uStack_57 = 0;
  uStack_56 = 0;
  uStack_55 = 0;
  uStack_54 = 0;
  uStack_53 = 0;
  uStack_52 = 0;
  uStack_51 = 0;
  uStack_50 = 0;
  uStack_4f = 0;
  uStack_4e = 0;
  uStack_4d = 0;
  uStack_4c = 0;
  uStack_4b = 0;
  uStack_4a = 0;
  uStack_49 = 0;
  uStack_5b = 0;
  uStack_5a = 0;
  uStack_59 = 0;
  bStack_60 = 6;
  uStack_5d = 0x70;
  uStack_5f = 0x7865;
  uStack_5c = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x1e0,(ulong)&bStack_60 | 1);
  *(undefined1 *)(param_1 + 0x1d8) = 1;
  *(undefined4 *)(param_1 + 0x1f0) = 0;
  if ((bStack_60 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(CONCAT17(uStack_49,
                             CONCAT16(uStack_4a,
                                      CONCAT15(uStack_4b,
                                               CONCAT14(uStack_4c,
                                                        CONCAT13(uStack_4d,
                                                                 CONCAT12(uStack_4e,
                                                                          CONCAT11(uStack_4f,
                                                                                   uStack_50))))))))
    ;
  }
  lVar2 = param_1 + 0x1c8;
  bStack_60 = (byte)lVar2;
  uStack_5f = (undefined2)((ulong)lVar2 >> 8);
  uStack_5d = (undefined1)((ulong)lVar2 >> 0x18);
  uStack_5c = (undefined1)((ulong)lVar2 >> 0x20);
  uStack_5b = (undefined1)((ulong)lVar2 >> 0x28);
  uStack_5a = (undefined1)((ulong)lVar2 >> 0x30);
  uStack_59 = (undefined1)((ulong)lVar2 >> 0x38);
  uVar23 = (**(code **)(*(long *)(param_1 + 0x1c8) + 0x10))();
  plStack_78 = (long *)CONCAT44(plStack_78._4_4_,uVar23);
  std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, unsigned int, IParameterProperty*&>(unsigned int const&, unsigned int&&, IParameterProperty*&)(lVar1,&plStack_78,&plStack_78,&bStack_60);
  uStack_4d = 0;
  uStack_4c = 0;
  uStack_4b = 0;
  uStack_4a = 0;
  uStack_49 = 0;
  bStack_60 = 0x22;
  uStack_57 = (undefined1)_UNK_0280cc19;
  uStack_56 = (undefined1)((ulong)_UNK_0280cc19 >> 8);
  uStack_55 = (undefined1)((ulong)_UNK_0280cc19 >> 0x10);
  uStack_54 = (undefined1)((ulong)_UNK_0280cc19 >> 0x18);
  uStack_53 = (undefined1)((ulong)_UNK_0280cc19 >> 0x20);
  uStack_52 = (undefined1)((ulong)_UNK_0280cc19 >> 0x28);
  uStack_51 = (undefined1)((ulong)_UNK_0280cc19 >> 0x30);
  uStack_50 = (undefined1)((ulong)_UNK_0280cc19 >> 0x38);
  uStack_5f = (undefined2)_UNK_0280cc11;
  uStack_5d = (undefined1)((ulong)_UNK_0280cc11 >> 0x10);
  uStack_5c = (undefined1)((ulong)_UNK_0280cc11 >> 0x18);
  uStack_5b = (undefined1)((ulong)_UNK_0280cc11 >> 0x20);
  uStack_5a = (undefined1)((ulong)_UNK_0280cc11 >> 0x28);
  uStack_59 = (undefined1)((ulong)_UNK_0280cc11 >> 0x30);
  uStack_58 = (undefined1)((ulong)_UNK_0280cc11 >> 0x38);
  uStack_4f = 0x74;
  uStack_4e = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x210,(ulong)&bStack_60 | 1);
  *(undefined1 *)(param_1 + 0x208) = 1;
  *(undefined4 *)(param_1 + 0x220) = 0;
  if ((bStack_60 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(CONCAT17(uStack_49,
                             CONCAT16(uStack_4a,
                                      CONCAT15(uStack_4b,
                                               CONCAT14(uStack_4c,
                                                        CONCAT13(uStack_4d,
                                                                 CONCAT12(uStack_4e,
                                                                          CONCAT11(uStack_4f,
                                                                                   uStack_50))))))))
    ;
  }
  lVar2 = param_1 + 0x1f8;
  bStack_60 = (byte)lVar2;
  uStack_5f = (undefined2)((ulong)lVar2 >> 8);
  uStack_5d = (undefined1)((ulong)lVar2 >> 0x18);
  uStack_5c = (undefined1)((ulong)lVar2 >> 0x20);
  uStack_5b = (undefined1)((ulong)lVar2 >> 0x28);
  uStack_5a = (undefined1)((ulong)lVar2 >> 0x30);
  uStack_59 = (undefined1)((ulong)lVar2 >> 0x38);
  uVar23 = (**(code **)(*(long *)(param_1 + 0x1f8) + 0x10))();
  plStack_78 = (long *)CONCAT44(plStack_78._4_4_,uVar23);
  std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, unsigned int, IParameterProperty*&>(unsigned int const&, unsigned int&&, IParameterProperty*&)(lVar1,&plStack_78,&plStack_78,&bStack_60);
  uStack_58 = 0;
  uStack_57 = 0;
  uStack_56 = 0;
  uStack_55 = 0;
  uStack_54 = 0;
  uStack_53 = 0;
  uStack_52 = 0;
  uStack_51 = 0;
  uStack_50 = 0;
  uStack_4f = 0;
  uStack_4e = 0;
  uStack_4d = 0;
  uStack_4c = 0;
  uStack_4b = 0;
  uStack_4a = 0;
  uStack_49 = 0;
  bStack_60 = 0xc;
  uStack_5b = 0x6c;
  uStack_5a = 0x31;
  uStack_5f = 0x6b73;
  uStack_5d = 0x69;
  uStack_5c = 0x6c;
  uStack_59 = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x240,(ulong)&bStack_60 | 1);
  *(undefined1 *)(param_1 + 0x238) = 1;
  *(undefined4 *)(param_1 + 0x250) = 0;
  if ((bStack_60 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(CONCAT17(uStack_49,
                             CONCAT16(uStack_4a,
                                      CONCAT15(uStack_4b,
                                               CONCAT14(uStack_4c,
                                                        CONCAT13(uStack_4d,
                                                                 CONCAT12(uStack_4e,
                                                                          CONCAT11(uStack_4f,
                                                                                   uStack_50))))))))
    ;
  }
  lVar2 = param_1 + 0x228;
  bStack_60 = (byte)lVar2;
  uStack_5f = (undefined2)((ulong)lVar2 >> 8);
  uStack_5d = (undefined1)((ulong)lVar2 >> 0x18);
  uStack_5c = (undefined1)((ulong)lVar2 >> 0x20);
  uStack_5b = (undefined1)((ulong)lVar2 >> 0x28);
  uStack_5a = (undefined1)((ulong)lVar2 >> 0x30);
  uStack_59 = (undefined1)((ulong)lVar2 >> 0x38);
  uVar23 = (**(code **)(*(long *)(param_1 + 0x228) + 0x10))();
  plStack_78 = (long *)CONCAT44(plStack_78._4_4_,uVar23);
  std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, unsigned int, IParameterProperty*&>(unsigned int const&, unsigned int&&, IParameterProperty*&)(lVar1,&plStack_78,&plStack_78,&bStack_60);
  uStack_52 = 0;
  uStack_51 = 0;
  uStack_50 = 0;
  uStack_4f = 0;
  uStack_4e = 0;
  uStack_4d = 0;
  uStack_4c = 0;
  uStack_4b = 0;
  uStack_4a = 0;
  uStack_49 = 0;
  uStack_68 = 0;
  uStack_5f = (undefined2)_UNK_027fb219;
  uStack_5d = (undefined1)((ulong)_UNK_027fb219 >> 0x10);
  uStack_5c = (undefined1)((ulong)_UNK_027fb219 >> 0x18);
  uStack_5b = (undefined1)((ulong)_UNK_027fb219 >> 0x20);
  uStack_5a = (undefined1)((ulong)_UNK_027fb219 >> 0x28);
  uStack_59 = (undefined1)((ulong)_UNK_027fb219 >> 0x30);
  uStack_58 = (undefined1)((ulong)_UNK_027fb219 >> 0x38);
  bStack_60 = 0x18;
  plStack_78 = (long *)0x0;
  uStack_70 = 0;
  uStack_57 = 0x61;
  uStack_56 = 0x62;
  uStack_55 = 0x65;
  uStack_54 = 0x6c;
  uStack_53 = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x270,(ulong)&bStack_60 | 1);
  *(undefined1 *)(param_1 + 0x268) = 1;
  uVar3 = (ulong)plStack_78 >> 1 & 0x7f;
  if (((ulong)plStack_78 & 1) != 0) {
    uVar3 = uStack_70;
  }
  if (uVar3 != 0) {
    void CParameterPropertyBase<175u>::CryptString<string >(string&, string const&)(param_1 + 0x280,&plStack_78);
  }
  if (((ulong)plStack_78 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_68);
  }
  if ((bStack_60 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(CONCAT17(uStack_49,
                             CONCAT16(uStack_4a,
                                      CONCAT15(uStack_4b,
                                               CONCAT14(uStack_4c,
                                                        CONCAT13(uStack_4d,
                                                                 CONCAT12(uStack_4e,
                                                                          CONCAT11(uStack_4f,
                                                                                   uStack_50))))))))
    ;
  }
  lVar2 = param_1 + 600;
  bStack_60 = (byte)lVar2;
  uStack_5f = (undefined2)((ulong)lVar2 >> 8);
  uStack_5d = (undefined1)((ulong)lVar2 >> 0x18);
  uStack_5c = (undefined1)((ulong)lVar2 >> 0x20);
  uStack_5b = (undefined1)((ulong)lVar2 >> 0x28);
  uStack_5a = (undefined1)((ulong)lVar2 >> 0x30);
  uStack_59 = (undefined1)((ulong)lVar2 >> 0x38);
  uVar23 = (**(code **)(*(long *)(param_1 + 600) + 0x10))();
  plStack_78 = (long *)CONCAT44(plStack_78._4_4_,uVar23);
  std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, unsigned int, IParameterProperty*&>(unsigned int const&, unsigned int&&, IParameterProperty*&)(lVar1,&plStack_78,&plStack_78,&bStack_60);
  uStack_52 = 0;
  uStack_51 = 0;
  uStack_50 = 0;
  uStack_4f = 0;
  uStack_4e = 0;
  uStack_4d = 0;
  uStack_4c = 0;
  uStack_4b = 0;
  uStack_4a = 0;
  uStack_49 = 0;
  bStack_60 = 0x18;
  uStack_5f = (undefined2)_UNK_027fb49a;
  uStack_5d = (undefined1)((ulong)_UNK_027fb49a >> 0x10);
  uStack_5c = (undefined1)((ulong)_UNK_027fb49a >> 0x18);
  uStack_5b = (undefined1)((ulong)_UNK_027fb49a >> 0x20);
  uStack_5a = (undefined1)((ulong)_UNK_027fb49a >> 0x28);
  uStack_59 = (undefined1)((ulong)_UNK_027fb49a >> 0x30);
  uStack_58 = (undefined1)((ulong)_UNK_027fb49a >> 0x38);
  uStack_57 = 0x65;
  uStack_56 = 0x76;
  uStack_55 = 0x65;
  uStack_54 = 0x6c;
  uStack_53 = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x2b0,(ulong)&bStack_60 | 1);
  *(undefined1 *)(param_1 + 0x2a8) = 1;
  *(undefined4 *)(param_1 + 0x2c0) = 0;
  if ((bStack_60 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(CONCAT17(uStack_49,
                             CONCAT16(uStack_4a,
                                      CONCAT15(uStack_4b,
                                               CONCAT14(uStack_4c,
                                                        CONCAT13(uStack_4d,
                                                                 CONCAT12(uStack_4e,
                                                                          CONCAT11(uStack_4f,
                                                                                   uStack_50))))))))
    ;
  }
  lVar2 = param_1 + 0x298;
  bStack_60 = (byte)lVar2;
  uStack_5f = (undefined2)((ulong)lVar2 >> 8);
  uStack_5d = (undefined1)((ulong)lVar2 >> 0x18);
  uStack_5c = (undefined1)((ulong)lVar2 >> 0x20);
  uStack_5b = (undefined1)((ulong)lVar2 >> 0x28);
  uStack_5a = (undefined1)((ulong)lVar2 >> 0x30);
  uStack_59 = (undefined1)((ulong)lVar2 >> 0x38);
  uVar23 = (**(code **)(*(long *)(param_1 + 0x298) + 0x10))();
  plStack_78 = (long *)CONCAT44(plStack_78._4_4_,uVar23);
  std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, unsigned int, IParameterProperty*&>(unsigned int const&, unsigned int&&, IParameterProperty*&)(lVar1,&plStack_78,&plStack_78,&bStack_60);
  uStack_58 = 0;
  uStack_57 = 0;
  uStack_56 = 0;
  uStack_55 = 0;
  uStack_54 = 0;
  uStack_53 = 0;
  uStack_52 = 0;
  uStack_51 = 0;
  uStack_50 = 0;
  uStack_4f = 0;
  uStack_4e = 0;
  uStack_4d = 0;
  uStack_4c = 0;
  uStack_4b = 0;
  uStack_4a = 0;
  uStack_49 = 0;
  bStack_60 = 0xc;
  uStack_5b = 0x6c;
  uStack_5a = 0x32;
  uStack_5f = 0x6b73;
  uStack_5d = 0x69;
  uStack_5c = 0x6c;
  uStack_59 = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x2e0,(ulong)&bStack_60 | 1);
  *(undefined1 *)(param_1 + 0x2d8) = 1;
  *(undefined4 *)(param_1 + 0x2f0) = 0;
  if ((bStack_60 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(CONCAT17(uStack_49,
                             CONCAT16(uStack_4a,
                                      CONCAT15(uStack_4b,
                                               CONCAT14(uStack_4c,
                                                        CONCAT13(uStack_4d,
                                                                 CONCAT12(uStack_4e,
                                                                          CONCAT11(uStack_4f,
                                                                                   uStack_50))))))))
    ;
  }
  lVar2 = param_1 + 0x2c8;
  bStack_60 = (byte)lVar2;
  uStack_5f = (undefined2)((ulong)lVar2 >> 8);
  uStack_5d = (undefined1)((ulong)lVar2 >> 0x18);
  uStack_5c = (undefined1)((ulong)lVar2 >> 0x20);
  uStack_5b = (undefined1)((ulong)lVar2 >> 0x28);
  uStack_5a = (undefined1)((ulong)lVar2 >> 0x30);
  uStack_59 = (undefined1)((ulong)lVar2 >> 0x38);
  uVar23 = (**(code **)(*(long *)(param_1 + 0x2c8) + 0x10))();
  plStack_78 = (long *)CONCAT44(plStack_78._4_4_,uVar23);
  std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, unsigned int, IParameterProperty*&>(unsigned int const&, unsigned int&&, IParameterProperty*&)(lVar1,&plStack_78,&plStack_78,&bStack_60);
  uStack_52 = 0;
  uStack_51 = 0;
  uStack_50 = 0;
  uStack_4f = 0;
  uStack_4e = 0;
  uStack_4d = 0;
  uStack_4c = 0;
  uStack_4b = 0;
  uStack_4a = 0;
  uStack_49 = 0;
  uStack_68 = 0;
  uStack_5f = (undefined2)_UNK_027fb22d;
  uStack_5d = (undefined1)((ulong)_UNK_027fb22d >> 0x10);
  uStack_5c = (undefined1)((ulong)_UNK_027fb22d >> 0x18);
  uStack_5b = (undefined1)((ulong)_UNK_027fb22d >> 0x20);
  uStack_5a = (undefined1)((ulong)_UNK_027fb22d >> 0x28);
  uStack_59 = (undefined1)((ulong)_UNK_027fb22d >> 0x30);
  uStack_58 = (undefined1)((ulong)_UNK_027fb22d >> 0x38);
  bStack_60 = 0x18;
  plStack_78 = (long *)0x0;
  uStack_70 = 0;
  uStack_57 = 0x61;
  uStack_56 = 0x62;
  uStack_55 = 0x65;
  uStack_54 = 0x6c;
  uStack_53 = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x310,(ulong)&bStack_60 | 1);
  *(undefined1 *)(param_1 + 0x308) = 1;
  uVar3 = (ulong)plStack_78 >> 1 & 0x7f;
  if (((ulong)plStack_78 & 1) != 0) {
    uVar3 = uStack_70;
  }
  if (uVar3 != 0) {
    void CParameterPropertyBase<178u>::CryptString<string >(string&, string const&)(param_1 + 800,&plStack_78);
  }
  if (((ulong)plStack_78 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_68);
  }
  if ((bStack_60 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(CONCAT17(uStack_49,
                             CONCAT16(uStack_4a,
                                      CONCAT15(uStack_4b,
                                               CONCAT14(uStack_4c,
                                                        CONCAT13(uStack_4d,
                                                                 CONCAT12(uStack_4e,
                                                                          CONCAT11(uStack_4f,
                                                                                   uStack_50))))))))
    ;
  }
  lVar2 = param_1 + 0x2f8;
  bStack_60 = (byte)lVar2;
  uStack_5f = (undefined2)((ulong)lVar2 >> 8);
  uStack_5d = (undefined1)((ulong)lVar2 >> 0x18);
  uStack_5c = (undefined1)((ulong)lVar2 >> 0x20);
  uStack_5b = (undefined1)((ulong)lVar2 >> 0x28);
  uStack_5a = (undefined1)((ulong)lVar2 >> 0x30);
  uStack_59 = (undefined1)((ulong)lVar2 >> 0x38);
  uVar23 = (**(code **)(*(long *)(param_1 + 0x2f8) + 0x10))();
  plStack_78 = (long *)CONCAT44(plStack_78._4_4_,uVar23);
  std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, unsigned int, IParameterProperty*&>(unsigned int const&, unsigned int&&, IParameterProperty*&)(lVar1,&plStack_78,&plStack_78,&bStack_60);
  uStack_52 = 0;
  uStack_51 = 0;
  uStack_50 = 0;
  uStack_4f = 0;
  uStack_4e = 0;
  uStack_4d = 0;
  uStack_4c = 0;
  uStack_4b = 0;
  uStack_4a = 0;
  uStack_49 = 0;
  bStack_60 = 0x18;
  uStack_5f = (undefined2)_UNK_027ffcbd;
  uStack_5d = (undefined1)((ulong)_UNK_027ffcbd >> 0x10);
  uStack_5c = (undefined1)((ulong)_UNK_027ffcbd >> 0x18);
  uStack_5b = (undefined1)((ulong)_UNK_027ffcbd >> 0x20);
  uStack_5a = (undefined1)((ulong)_UNK_027ffcbd >> 0x28);
  uStack_59 = (undefined1)((ulong)_UNK_027ffcbd >> 0x30);
  uStack_58 = (undefined1)((ulong)_UNK_027ffcbd >> 0x38);
  uStack_57 = 0x65;
  uStack_56 = 0x76;
  uStack_55 = 0x65;
  uStack_54 = 0x6c;
  uStack_53 = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x350,(ulong)&bStack_60 | 1);
  *(undefined1 *)(param_1 + 0x348) = 1;
  *(undefined4 *)(param_1 + 0x360) = 0;
  if ((bStack_60 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(CONCAT17(uStack_49,
                             CONCAT16(uStack_4a,
                                      CONCAT15(uStack_4b,
                                               CONCAT14(uStack_4c,
                                                        CONCAT13(uStack_4d,
                                                                 CONCAT12(uStack_4e,
                                                                          CONCAT11(uStack_4f,
                                                                                   uStack_50))))))))
    ;
  }
  lVar2 = param_1 + 0x338;
  bStack_60 = (byte)lVar2;
  uStack_5f = (undefined2)((ulong)lVar2 >> 8);
  uStack_5d = (undefined1)((ulong)lVar2 >> 0x18);
  uStack_5c = (undefined1)((ulong)lVar2 >> 0x20);
  uStack_5b = (undefined1)((ulong)lVar2 >> 0x28);
  uStack_5a = (undefined1)((ulong)lVar2 >> 0x30);
  uStack_59 = (undefined1)((ulong)lVar2 >> 0x38);
  uVar23 = (**(code **)(*(long *)(param_1 + 0x338) + 0x10))();
  plStack_78 = (long *)CONCAT44(plStack_78._4_4_,uVar23);
  std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, unsigned int, IParameterProperty*&>(unsigned int const&, unsigned int&&, IParameterProperty*&)(lVar1,&plStack_78,&plStack_78,&bStack_60);
  uStack_58 = 0;
  uStack_57 = 0;
  uStack_56 = 0;
  uStack_55 = 0;
  uStack_54 = 0;
  uStack_53 = 0;
  uStack_52 = 0;
  uStack_51 = 0;
  uStack_50 = 0;
  uStack_4f = 0;
  uStack_4e = 0;
  uStack_4d = 0;
  uStack_4c = 0;
  uStack_4b = 0;
  uStack_4a = 0;
  uStack_49 = 0;
  bStack_60 = 0xc;
  uStack_5b = 0x6c;
  uStack_5a = 0x33;
  uStack_5f = 0x6b73;
  uStack_5d = 0x69;
  uStack_5c = 0x6c;
  uStack_59 = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x380,(ulong)&bStack_60 | 1);
  *(undefined1 *)(param_1 + 0x378) = 1;
  *(undefined4 *)(param_1 + 0x390) = 0;
  if ((bStack_60 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(CONCAT17(uStack_49,
                             CONCAT16(uStack_4a,
                                      CONCAT15(uStack_4b,
                                               CONCAT14(uStack_4c,
                                                        CONCAT13(uStack_4d,
                                                                 CONCAT12(uStack_4e,
                                                                          CONCAT11(uStack_4f,
                                                                                   uStack_50))))))))
    ;
  }
  lVar2 = param_1 + 0x368;
  bStack_60 = (byte)lVar2;
  uStack_5f = (undefined2)((ulong)lVar2 >> 8);
  uStack_5d = (undefined1)((ulong)lVar2 >> 0x18);
  uStack_5c = (undefined1)((ulong)lVar2 >> 0x20);
  uStack_5b = (undefined1)((ulong)lVar2 >> 0x28);
  uStack_5a = (undefined1)((ulong)lVar2 >> 0x30);
  uStack_59 = (undefined1)((ulong)lVar2 >> 0x38);
  uVar23 = (**(code **)(*(long *)(param_1 + 0x368) + 0x10))();
  plStack_78 = (long *)CONCAT44(plStack_78._4_4_,uVar23);
  std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, unsigned int, IParameterProperty*&>(unsigned int const&, unsigned int&&, IParameterProperty*&)(lVar1,&plStack_78,&plStack_78,&bStack_60);
  uStack_52 = 0;
  uStack_51 = 0;
  uStack_50 = 0;
  uStack_4f = 0;
  uStack_4e = 0;
  uStack_4d = 0;
  uStack_4c = 0;
  uStack_4b = 0;
  uStack_4a = 0;
  uStack_49 = 0;
  uStack_68 = 0;
  uStack_5f = (undefined2)_UNK_027fb23a;
  uStack_5d = (undefined1)((ulong)_UNK_027fb23a >> 0x10);
  uStack_5c = (undefined1)((ulong)_UNK_027fb23a >> 0x18);
  uStack_5b = (undefined1)((ulong)_UNK_027fb23a >> 0x20);
  uStack_5a = (undefined1)((ulong)_UNK_027fb23a >> 0x28);
  uStack_59 = (undefined1)((ulong)_UNK_027fb23a >> 0x30);
  uStack_58 = (undefined1)((ulong)_UNK_027fb23a >> 0x38);
  bStack_60 = 0x18;
  plStack_78 = (long *)0x0;
  uStack_70 = 0;
  uStack_57 = 0x61;
  uStack_56 = 0x62;
  uStack_55 = 0x65;
  uStack_54 = 0x6c;
  uStack_53 = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x3b0,(ulong)&bStack_60 | 1);
  *(undefined1 *)(param_1 + 0x3a8) = 1;
  uVar3 = (ulong)plStack_78 >> 1 & 0x7f;
  if (((ulong)plStack_78 & 1) != 0) {
    uVar3 = uStack_70;
  }
  if (uVar3 != 0) {
    void CParameterPropertyBase<181u>::CryptString<string >(string&, string const&)(param_1 + 0x3c0,&plStack_78);
  }
  if (((ulong)plStack_78 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_68);
  }
  if ((bStack_60 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(CONCAT17(uStack_49,
                             CONCAT16(uStack_4a,
                                      CONCAT15(uStack_4b,
                                               CONCAT14(uStack_4c,
                                                        CONCAT13(uStack_4d,
                                                                 CONCAT12(uStack_4e,
                                                                          CONCAT11(uStack_4f,
                                                                                   uStack_50))))))))
    ;
  }
  lVar2 = param_1 + 0x398;
  bStack_60 = (byte)lVar2;
  uStack_5f = (undefined2)((ulong)lVar2 >> 8);
  uStack_5d = (undefined1)((ulong)lVar2 >> 0x18);
  uStack_5c = (undefined1)((ulong)lVar2 >> 0x20);
  uStack_5b = (undefined1)((ulong)lVar2 >> 0x28);
  uStack_5a = (undefined1)((ulong)lVar2 >> 0x30);
  uStack_59 = (undefined1)((ulong)lVar2 >> 0x38);
  uVar23 = (**(code **)(*(long *)(param_1 + 0x398) + 0x10))();
  plStack_78 = (long *)CONCAT44(plStack_78._4_4_,uVar23);
  std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, unsigned int, IParameterProperty*&>(unsigned int const&, unsigned int&&, IParameterProperty*&)(lVar1,&plStack_78,&plStack_78,&bStack_60);
  uStack_52 = 0;
  uStack_51 = 0;
  uStack_50 = 0;
  uStack_4f = 0;
  uStack_4e = 0;
  uStack_4d = 0;
  uStack_4c = 0;
  uStack_4b = 0;
  uStack_4a = 0;
  uStack_49 = 0;
  bStack_60 = 0x18;
  uStack_5f = (undefined2)_UNK_027ffcd1;
  uStack_5d = (undefined1)((ulong)_UNK_027ffcd1 >> 0x10);
  uStack_5c = (undefined1)((ulong)_UNK_027ffcd1 >> 0x18);
  uStack_5b = (undefined1)((ulong)_UNK_027ffcd1 >> 0x20);
  uStack_5a = (undefined1)((ulong)_UNK_027ffcd1 >> 0x28);
  uStack_59 = (undefined1)((ulong)_UNK_027ffcd1 >> 0x30);
  uStack_58 = (undefined1)((ulong)_UNK_027ffcd1 >> 0x38);
  uStack_57 = 0x65;
  uStack_56 = 0x76;
  uStack_55 = 0x65;
  uStack_54 = 0x6c;
  uStack_53 = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x3f0,(ulong)&bStack_60 | 1);
  *(undefined1 *)(param_1 + 1000) = 1;
  *(undefined4 *)(param_1 + 0x400) = 0;
  if ((bStack_60 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(CONCAT17(uStack_49,
                             CONCAT16(uStack_4a,
                                      CONCAT15(uStack_4b,
                                               CONCAT14(uStack_4c,
                                                        CONCAT13(uStack_4d,
                                                                 CONCAT12(uStack_4e,
                                                                          CONCAT11(uStack_4f,
                                                                                   uStack_50))))))))
    ;
  }
  lVar2 = param_1 + 0x3d8;
  bStack_60 = (byte)lVar2;
  uStack_5f = (undefined2)((ulong)lVar2 >> 8);
  uStack_5d = (undefined1)((ulong)lVar2 >> 0x18);
  uStack_5c = (undefined1)((ulong)lVar2 >> 0x20);
  uStack_5b = (undefined1)((ulong)lVar2 >> 0x28);
  uStack_5a = (undefined1)((ulong)lVar2 >> 0x30);
  uStack_59 = (undefined1)((ulong)lVar2 >> 0x38);
  uVar23 = (**(code **)(*(long *)(param_1 + 0x3d8) + 0x10))();
  plStack_78 = (long *)CONCAT44(plStack_78._4_4_,uVar23);
  std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, unsigned int, IParameterProperty*&>(unsigned int const&, unsigned int&&, IParameterProperty*&)(lVar1,&plStack_78,&plStack_78,&bStack_60);
  uStack_58 = 0;
  uStack_57 = 0;
  uStack_56 = 0;
  uStack_55 = 0;
  uStack_54 = 0;
  uStack_53 = 0;
  uStack_52 = 0;
  uStack_51 = 0;
  uStack_50 = 0;
  uStack_4f = 0;
  uStack_4e = 0;
  uStack_4d = 0;
  uStack_4c = 0;
  uStack_4b = 0;
  uStack_4a = 0;
  uStack_49 = 0;
  uStack_5c = 0;
  uStack_5b = 0;
  uStack_5a = 0;
  uStack_59 = 0;
  bStack_60 = 4;
  uStack_5f = 0x7068;
  uStack_5d = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x420,(ulong)&bStack_60 | 1);
  *(undefined1 *)(param_1 + 0x418) = 1;
  *(undefined4 *)(param_1 + 0x430) = 0;
  if ((bStack_60 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(CONCAT17(uStack_49,
                             CONCAT16(uStack_4a,
                                      CONCAT15(uStack_4b,
                                               CONCAT14(uStack_4c,
                                                        CONCAT13(uStack_4d,
                                                                 CONCAT12(uStack_4e,
                                                                          CONCAT11(uStack_4f,
                                                                                   uStack_50))))))))
    ;
  }
  lVar2 = param_1 + 0x408;
  bStack_60 = (byte)lVar2;
  uStack_5f = (undefined2)((ulong)lVar2 >> 8);
  uStack_5d = (undefined1)((ulong)lVar2 >> 0x18);
  uStack_5c = (undefined1)((ulong)lVar2 >> 0x20);
  uStack_5b = (undefined1)((ulong)lVar2 >> 0x28);
  uStack_5a = (undefined1)((ulong)lVar2 >> 0x30);
  uStack_59 = (undefined1)((ulong)lVar2 >> 0x38);
  uVar23 = (**(code **)(*(long *)(param_1 + 0x408) + 0x10))();
  plStack_78 = (long *)CONCAT44(plStack_78._4_4_,uVar23);
  std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, unsigned int, IParameterProperty*&>(unsigned int const&, unsigned int&&, IParameterProperty*&)(lVar1,&plStack_78,&plStack_78,&bStack_60);
  uStack_58 = 0;
  uStack_57 = 0;
  uStack_56 = 0;
  uStack_55 = 0;
  uStack_54 = 0;
  uStack_53 = 0;
  uStack_52 = 0;
  uStack_51 = 0;
  uStack_50 = 0;
  uStack_4f = 0;
  uStack_4e = 0;
  uStack_4d = 0;
  uStack_4c = 0;
  uStack_4b = 0;
  uStack_4a = 0;
  uStack_49 = 0;
  bStack_60 = 0xc;
  uStack_5b = 99;
  uStack_5a = 0x6b;
  uStack_5f = 0x7461;
  uStack_5d = 0x74;
  uStack_5c = 0x61;
  uStack_59 = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x450,(ulong)&bStack_60 | 1);
  *(undefined1 *)(param_1 + 0x448) = 1;
  *(undefined4 *)(param_1 + 0x460) = 0;
  if ((bStack_60 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(CONCAT17(uStack_49,
                             CONCAT16(uStack_4a,
                                      CONCAT15(uStack_4b,
                                               CONCAT14(uStack_4c,
                                                        CONCAT13(uStack_4d,
                                                                 CONCAT12(uStack_4e,
                                                                          CONCAT11(uStack_4f,
                                                                                   uStack_50))))))))
    ;
  }
  lVar2 = param_1 + 0x438;
  bStack_60 = (byte)lVar2;
  uStack_5f = (undefined2)((ulong)lVar2 >> 8);
  uStack_5d = (undefined1)((ulong)lVar2 >> 0x18);
  uStack_5c = (undefined1)((ulong)lVar2 >> 0x20);
  uStack_5b = (undefined1)((ulong)lVar2 >> 0x28);
  uStack_5a = (undefined1)((ulong)lVar2 >> 0x30);
  uStack_59 = (undefined1)((ulong)lVar2 >> 0x38);
  uVar23 = (**(code **)(*(long *)(param_1 + 0x438) + 0x10))();
  plStack_78 = (long *)CONCAT44(plStack_78._4_4_,uVar23);
  std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, unsigned int, IParameterProperty*&>(unsigned int const&, unsigned int&&, IParameterProperty*&)(lVar1,&plStack_78,&plStack_78,&bStack_60);
  uStack_52 = 0;
  uStack_51 = 0;
  uStack_50 = 0;
  uStack_4f = 0;
  uStack_4e = 0;
  uStack_4d = 0;
  uStack_4c = 0;
  uStack_4b = 0;
  uStack_4a = 0;
  uStack_49 = 0;
  bStack_60 = 0x18;
  uStack_5f = (undefined2)_UNK_0282db95;
  uStack_5d = (undefined1)((uint)_UNK_0282db95 >> 0x10);
  uStack_5c = (undefined1)((uint)_UNK_0282db95 >> 0x18);
  uStack_5b = (undefined1)_UNK_0282db99;
  uStack_5a = (undefined1)((uint)_UNK_0282db99 >> 8);
  uStack_59 = (undefined1)((uint)_UNK_0282db99 >> 0x10);
  uStack_58 = (undefined1)((uint)_UNK_0282db99 >> 0x18);
  uStack_57 = 0x65;
  uStack_56 = 0x6e;
  uStack_55 = 99;
  uStack_54 = 0x65;
  uStack_53 = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x480,(ulong)&bStack_60 | 1);
  *(undefined1 *)(param_1 + 0x478) = 1;
  *(undefined4 *)(param_1 + 0x490) = 0;
  if ((bStack_60 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(CONCAT17(uStack_49,
                             CONCAT16(uStack_4a,
                                      CONCAT15(uStack_4b,
                                               CONCAT14(uStack_4c,
                                                        CONCAT13(uStack_4d,
                                                                 CONCAT12(uStack_4e,
                                                                          CONCAT11(uStack_4f,
                                                                                   uStack_50))))))))
    ;
  }
  lVar2 = param_1 + 0x468;
  bStack_60 = (byte)lVar2;
  uStack_5f = (undefined2)((ulong)lVar2 >> 8);
  uStack_5d = (undefined1)((ulong)lVar2 >> 0x18);
  uStack_5c = (undefined1)((ulong)lVar2 >> 0x20);
  uStack_5b = (undefined1)((ulong)lVar2 >> 0x28);
  uStack_5a = (undefined1)((ulong)lVar2 >> 0x30);
  uStack_59 = (undefined1)((ulong)lVar2 >> 0x38);
  uVar23 = (**(code **)(*(long *)(param_1 + 0x468) + 0x10))();
  plStack_78 = (long *)CONCAT44(plStack_78._4_4_,uVar23);
  std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, unsigned int, IParameterProperty*&>(unsigned int const&, unsigned int&&, IParameterProperty*&)(lVar1,&plStack_78,&plStack_78,&bStack_60);
  uStack_57 = 0;
  uStack_56 = 0;
  uStack_55 = 0;
  uStack_54 = 0;
  uStack_53 = 0;
  uStack_52 = 0;
  uStack_51 = 0;
  uStack_50 = 0;
  uStack_4f = 0;
  uStack_4e = 0;
  uStack_4d = 0;
  uStack_4c = 0;
  uStack_4b = 0;
  uStack_4a = 0;
  uStack_49 = 0;
  bStack_60 = 0xe;
  uStack_59 = 0x65;
  uStack_5b = 0x6e;
  uStack_5a = 99;
  uStack_5f = 0x6564;
  uStack_5d = 0x66;
  uStack_5c = 0x65;
  uStack_58 = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x4b0,(ulong)&bStack_60 | 1);
  *(undefined1 *)(param_1 + 0x4a8) = 1;
  *(undefined4 *)(param_1 + 0x4c0) = 0;
  if ((bStack_60 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(CONCAT17(uStack_49,
                             CONCAT16(uStack_4a,
                                      CONCAT15(uStack_4b,
                                               CONCAT14(uStack_4c,
                                                        CONCAT13(uStack_4d,
                                                                 CONCAT12(uStack_4e,
                                                                          CONCAT11(uStack_4f,
                                                                                   uStack_50))))))))
    ;
  }
  lVar2 = param_1 + 0x498;
  bStack_60 = (byte)lVar2;
  uStack_5f = (undefined2)((ulong)lVar2 >> 8);
  uStack_5d = (undefined1)((ulong)lVar2 >> 0x18);
  uStack_5c = (undefined1)((ulong)lVar2 >> 0x20);
  uStack_5b = (undefined1)((ulong)lVar2 >> 0x28);
  uStack_5a = (undefined1)((ulong)lVar2 >> 0x30);
  uStack_59 = (undefined1)((ulong)lVar2 >> 0x38);
  uVar23 = (**(code **)(*(long *)(param_1 + 0x498) + 0x10))();
  plStack_78 = (long *)CONCAT44(plStack_78._4_4_,uVar23);
  std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, unsigned int, IParameterProperty*&>(unsigned int const&, unsigned int&&, IParameterProperty*&)(lVar1,&plStack_78,&plStack_78,&bStack_60);
  uStack_58 = 0;
  uStack_57 = 0;
  uStack_56 = 0;
  uStack_55 = 0;
  uStack_54 = 0;
  uStack_53 = 0;
  uStack_52 = 0;
  uStack_51 = 0;
  uStack_50 = 0;
  uStack_4f = 0;
  uStack_4e = 0;
  uStack_4d = 0;
  uStack_4c = 0;
  uStack_4b = 0;
  uStack_4a = 0;
  uStack_49 = 0;
  uStack_5b = 0;
  uStack_5a = 0;
  uStack_59 = 0;
  bStack_60 = 6;
  uStack_5d = 0x74;
  uStack_5f = 0x6968;
  uStack_5c = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x4e0,(ulong)&bStack_60 | 1);
  *(undefined1 *)(param_1 + 0x4d8) = 1;
  *(undefined4 *)(param_1 + 0x4f0) = 0;
  if ((bStack_60 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(CONCAT17(uStack_49,
                             CONCAT16(uStack_4a,
                                      CONCAT15(uStack_4b,
                                               CONCAT14(uStack_4c,
                                                        CONCAT13(uStack_4d,
                                                                 CONCAT12(uStack_4e,
                                                                          CONCAT11(uStack_4f,
                                                                                   uStack_50))))))))
    ;
  }
  lVar2 = param_1 + 0x4c8;
  bStack_60 = (byte)lVar2;
  uStack_5f = (undefined2)((ulong)lVar2 >> 8);
  uStack_5d = (undefined1)((ulong)lVar2 >> 0x18);
  uStack_5c = (undefined1)((ulong)lVar2 >> 0x20);
  uStack_5b = (undefined1)((ulong)lVar2 >> 0x28);
  uStack_5a = (undefined1)((ulong)lVar2 >> 0x30);
  uStack_59 = (undefined1)((ulong)lVar2 >> 0x38);
  uVar23 = (**(code **)(*(long *)(param_1 + 0x4c8) + 0x10))();
  plStack_78 = (long *)CONCAT44(plStack_78._4_4_,uVar23);
  std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, unsigned int, IParameterProperty*&>(unsigned int const&, unsigned int&&, IParameterProperty*&)(lVar1,&plStack_78,&plStack_78,&bStack_60);
  uStack_58 = 0;
  uStack_57 = 0;
  uStack_56 = 0;
  uStack_55 = 0;
  uStack_54 = 0;
  uStack_53 = 0;
  uStack_52 = 0;
  uStack_51 = 0;
  uStack_50 = 0;
  uStack_4f = 0;
  uStack_4e = 0;
  uStack_4d = 0;
  uStack_4c = 0;
  uStack_4b = 0;
  uStack_4a = 0;
  uStack_49 = 0;
  uStack_59 = 0;
  bStack_60 = 10;
  uStack_5b = 100;
  uStack_5f = 0x7567;
  uStack_5d = 0x61;
  uStack_5c = 0x72;
  uStack_5a = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x510,(ulong)&bStack_60 | 1);
  *(undefined1 *)(param_1 + 0x508) = 1;
  *(undefined4 *)(param_1 + 0x520) = 0;
  if ((bStack_60 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(CONCAT17(uStack_49,
                             CONCAT16(uStack_4a,
                                      CONCAT15(uStack_4b,
                                               CONCAT14(uStack_4c,
                                                        CONCAT13(uStack_4d,
                                                                 CONCAT12(uStack_4e,
                                                                          CONCAT11(uStack_4f,
                                                                                   uStack_50))))))))
    ;
  }
  lVar2 = param_1 + 0x4f8;
  bStack_60 = (byte)lVar2;
  uStack_5f = (undefined2)((ulong)lVar2 >> 8);
  uStack_5d = (undefined1)((ulong)lVar2 >> 0x18);
  uStack_5c = (undefined1)((ulong)lVar2 >> 0x20);
  uStack_5b = (undefined1)((ulong)lVar2 >> 0x28);
  uStack_5a = (undefined1)((ulong)lVar2 >> 0x30);
  uStack_59 = (undefined1)((ulong)lVar2 >> 0x38);
  uVar23 = (**(code **)(*(long *)(param_1 + 0x4f8) + 0x10))();
  plStack_78 = (long *)CONCAT44(plStack_78._4_4_,uVar23);
  std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, unsigned int, IParameterProperty*&>(unsigned int const&, unsigned int&&, IParameterProperty*&)(lVar1,&plStack_78,&plStack_78,&bStack_60);
  uStack_58 = 0;
  uStack_57 = 0;
  uStack_56 = 0;
  uStack_55 = 0;
  uStack_54 = 0;
  uStack_53 = 0;
  uStack_52 = 0;
  uStack_51 = 0;
  uStack_50 = 0;
  uStack_4f = 0;
  uStack_4e = 0;
  uStack_4d = 0;
  uStack_4c = 0;
  uStack_4b = 0;
  uStack_4a = 0;
  uStack_49 = 0;
  uStack_5c = 0;
  uStack_5b = 0;
  uStack_5a = 0;
  uStack_59 = 0;
  bStack_60 = 4;
  uStack_5f = 0x7061;
  uStack_5d = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x540,(ulong)&bStack_60 | 1);
  *(undefined1 *)(param_1 + 0x538) = 1;
  *(undefined4 *)(param_1 + 0x550) = 0;
  if ((bStack_60 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(CONCAT17(uStack_49,
                             CONCAT16(uStack_4a,
                                      CONCAT15(uStack_4b,
                                               CONCAT14(uStack_4c,
                                                        CONCAT13(uStack_4d,
                                                                 CONCAT12(uStack_4e,
                                                                          CONCAT11(uStack_4f,
                                                                                   uStack_50))))))))
    ;
  }
  lVar2 = param_1 + 0x528;
  bStack_60 = (byte)lVar2;
  uStack_5f = (undefined2)((ulong)lVar2 >> 8);
  uStack_5d = (undefined1)((ulong)lVar2 >> 0x18);
  uStack_5c = (undefined1)((ulong)lVar2 >> 0x20);
  uStack_5b = (undefined1)((ulong)lVar2 >> 0x28);
  uStack_5a = (undefined1)((ulong)lVar2 >> 0x30);
  uStack_59 = (undefined1)((ulong)lVar2 >> 0x38);
  uVar23 = (**(code **)(*(long *)(param_1 + 0x528) + 0x10))();
  plStack_78 = (long *)CONCAT44(plStack_78._4_4_,uVar23);
  std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, unsigned int, IParameterProperty*&>(unsigned int const&, unsigned int&&, IParameterProperty*&)(lVar1,&plStack_78,&plStack_78,&bStack_60);
  uStack_56 = 0;
  uStack_55 = 0;
  uStack_54 = 0;
  uStack_53 = 0;
  uStack_52 = 0;
  uStack_51 = 0;
  uStack_50 = 0;
  uStack_4f = 0;
  uStack_4e = 0;
  uStack_4d = 0;
  uStack_4c = 0;
  uStack_4b = 0;
  uStack_4a = 0;
  uStack_49 = 0;
  bStack_60 = 0x10;
  uStack_5f = 0x6564;
  uStack_5d = 0x66;
  uStack_5c = 0x5f;
  uStack_5b = 0x66;
  uStack_5a = 0x69;
  uStack_59 = 0x72;
  uStack_58 = 0x65;
  uStack_57 = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x570,(ulong)&bStack_60 | 1);
  *(undefined1 *)(param_1 + 0x568) = 1;
  *(undefined4 *)(param_1 + 0x580) = 0;
  if ((bStack_60 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(CONCAT17(uStack_49,
                             CONCAT16(uStack_4a,
                                      CONCAT15(uStack_4b,
                                               CONCAT14(uStack_4c,
                                                        CONCAT13(uStack_4d,
                                                                 CONCAT12(uStack_4e,
                                                                          CONCAT11(uStack_4f,
                                                                                   uStack_50))))))))
    ;
  }
  lVar2 = param_1 + 0x558;
  bStack_60 = (byte)lVar2;
  uStack_5f = (undefined2)((ulong)lVar2 >> 8);
  uStack_5d = (undefined1)((ulong)lVar2 >> 0x18);
  uStack_5c = (undefined1)((ulong)lVar2 >> 0x20);
  uStack_5b = (undefined1)((ulong)lVar2 >> 0x28);
  uStack_5a = (undefined1)((ulong)lVar2 >> 0x30);
  uStack_59 = (undefined1)((ulong)lVar2 >> 0x38);
  uVar23 = (**(code **)(*(long *)(param_1 + 0x558) + 0x10))();
  plStack_78 = (long *)CONCAT44(plStack_78._4_4_,uVar23);
  std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, unsigned int, IParameterProperty*&>(unsigned int const&, unsigned int&&, IParameterProperty*&)(lVar1,&plStack_78,&plStack_78,&bStack_60);
  uStack_55 = 0;
  uStack_54 = 0;
  uStack_53 = 0;
  uStack_52 = 0;
  uStack_51 = 0;
  uStack_50 = 0;
  uStack_4f = 0;
  uStack_4e = 0;
  uStack_4d = 0;
  uStack_4c = 0;
  uStack_4b = 0;
  uStack_4a = 0;
  uStack_49 = 0;
  bStack_60 = 0x12;
  uStack_5f = (undefined2)_UNK_027fb247;
  uStack_5d = (undefined1)((ulong)_UNK_027fb247 >> 0x10);
  uStack_5c = (undefined1)((ulong)_UNK_027fb247 >> 0x18);
  uStack_5b = (undefined1)((ulong)_UNK_027fb247 >> 0x20);
  uStack_5a = (undefined1)((ulong)_UNK_027fb247 >> 0x28);
  uStack_59 = (undefined1)((ulong)_UNK_027fb247 >> 0x30);
  uStack_58 = (undefined1)((ulong)_UNK_027fb247 >> 0x38);
  uStack_57 = 0x72;
  uStack_56 = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x5a0,(ulong)&bStack_60 | 1);
  *(undefined1 *)(param_1 + 0x598) = 1;
  *(undefined4 *)(param_1 + 0x5b0) = 0;
  if ((bStack_60 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(CONCAT17(uStack_49,
                             CONCAT16(uStack_4a,
                                      CONCAT15(uStack_4b,
                                               CONCAT14(uStack_4c,
                                                        CONCAT13(uStack_4d,
                                                                 CONCAT12(uStack_4e,
                                                                          CONCAT11(uStack_4f,
                                                                                   uStack_50))))))))
    ;
  }
  lVar2 = param_1 + 0x588;
  bStack_60 = (byte)lVar2;
  uStack_5f = (undefined2)((ulong)lVar2 >> 8);
  uStack_5d = (undefined1)((ulong)lVar2 >> 0x18);
  uStack_5c = (undefined1)((ulong)lVar2 >> 0x20);
  uStack_5b = (undefined1)((ulong)lVar2 >> 0x28);
  uStack_5a = (undefined1)((ulong)lVar2 >> 0x30);
  uStack_59 = (undefined1)((ulong)lVar2 >> 0x38);
  uVar23 = (**(code **)(*(long *)(param_1 + 0x588) + 0x10))();
  plStack_78 = (long *)CONCAT44(plStack_78._4_4_,uVar23);
  std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, unsigned int, IParameterProperty*&>(unsigned int const&, unsigned int&&, IParameterProperty*&)(lVar1,&plStack_78,&plStack_78,&bStack_60);
  uStack_56 = 0;
  uStack_55 = 0;
  uStack_54 = 0;
  uStack_53 = 0;
  uStack_52 = 0;
  uStack_51 = 0;
  uStack_50 = 0;
  uStack_4f = 0;
  uStack_4e = 0;
  uStack_4d = 0;
  uStack_4c = 0;
  uStack_4b = 0;
  uStack_4a = 0;
  uStack_49 = 0;
  bStack_60 = 0x10;
  uStack_5f = 0x6564;
  uStack_5d = 0x66;
  uStack_5c = 0x5f;
  uStack_5b = 0x77;
  uStack_5a = 0x69;
  uStack_59 = 0x6e;
  uStack_58 = 100;
  uStack_57 = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x5d0,(ulong)&bStack_60 | 1);
  *(undefined1 *)(param_1 + 0x5c8) = 1;
  *(undefined4 *)(param_1 + 0x5e0) = 0;
  if ((bStack_60 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(CONCAT17(uStack_49,
                             CONCAT16(uStack_4a,
                                      CONCAT15(uStack_4b,
                                               CONCAT14(uStack_4c,
                                                        CONCAT13(uStack_4d,
                                                                 CONCAT12(uStack_4e,
                                                                          CONCAT11(uStack_4f,
                                                                                   uStack_50))))))))
    ;
  }
  lVar2 = param_1 + 0x5b8;
  bStack_60 = (byte)lVar2;
  uStack_5f = (undefined2)((ulong)lVar2 >> 8);
  uStack_5d = (undefined1)((ulong)lVar2 >> 0x18);
  uStack_5c = (undefined1)((ulong)lVar2 >> 0x20);
  uStack_5b = (undefined1)((ulong)lVar2 >> 0x28);
  uStack_5a = (undefined1)((ulong)lVar2 >> 0x30);
  uStack_59 = (undefined1)((ulong)lVar2 >> 0x38);
  uVar23 = (**(code **)(*(long *)(param_1 + 0x5b8) + 0x10))();
  plStack_78 = (long *)CONCAT44(plStack_78._4_4_,uVar23);
  std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, unsigned int, IParameterProperty*&>(unsigned int const&, unsigned int&&, IParameterProperty*&)(lVar1,&plStack_78,&plStack_78,&bStack_60);
  uStack_55 = 0;
  uStack_54 = 0;
  uStack_53 = 0;
  uStack_52 = 0;
  uStack_51 = 0;
  uStack_50 = 0;
  uStack_4f = 0;
  uStack_4e = 0;
  uStack_4d = 0;
  uStack_4c = 0;
  uStack_4b = 0;
  uStack_4a = 0;
  uStack_49 = 0;
  bStack_60 = 0x12;
  uStack_5f = (undefined2)_UNK_027fb251;
  uStack_5d = (undefined1)((ulong)_UNK_027fb251 >> 0x10);
  uStack_5c = (undefined1)((ulong)_UNK_027fb251 >> 0x18);
  uStack_5b = (undefined1)((ulong)_UNK_027fb251 >> 0x20);
  uStack_5a = (undefined1)((ulong)_UNK_027fb251 >> 0x28);
  uStack_59 = (undefined1)((ulong)_UNK_027fb251 >> 0x30);
  uStack_58 = (undefined1)((ulong)_UNK_027fb251 >> 0x38);
  uStack_57 = 0x68;
  uStack_56 = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x600,(ulong)&bStack_60 | 1);
  *(undefined1 *)(param_1 + 0x5f8) = 1;
  *(undefined4 *)(param_1 + 0x610) = 0;
  if ((bStack_60 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(CONCAT17(uStack_49,
                             CONCAT16(uStack_4a,
                                      CONCAT15(uStack_4b,
                                               CONCAT14(uStack_4c,
                                                        CONCAT13(uStack_4d,
                                                                 CONCAT12(uStack_4e,
                                                                          CONCAT11(uStack_4f,
                                                                                   uStack_50))))))))
    ;
  }
  lVar2 = param_1 + 0x5e8;
  bStack_60 = (byte)lVar2;
  uStack_5f = (undefined2)((ulong)lVar2 >> 8);
  uStack_5d = (undefined1)((ulong)lVar2 >> 0x18);
  uStack_5c = (undefined1)((ulong)lVar2 >> 0x20);
  uStack_5b = (undefined1)((ulong)lVar2 >> 0x28);
  uStack_5a = (undefined1)((ulong)lVar2 >> 0x30);
  uStack_59 = (undefined1)((ulong)lVar2 >> 0x38);
  uVar23 = (**(code **)(*(long *)(param_1 + 0x5e8) + 0x10))();
  plStack_78 = (long *)CONCAT44(plStack_78._4_4_,uVar23);
  std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, unsigned int, IParameterProperty*&>(unsigned int const&, unsigned int&&, IParameterProperty*&)(lVar1,&plStack_78,&plStack_78,&bStack_60);
  uStack_53 = 0;
  uStack_52 = 0;
  uStack_51 = 0;
  uStack_50 = 0;
  uStack_4f = 0;
  uStack_4e = 0;
  uStack_4d = 0;
  uStack_4c = 0;
  uStack_4b = 0;
  uStack_4a = 0;
  uStack_49 = 0;
  bStack_60 = 0x16;
  uStack_5f = (undefined2)_UNK_027fb25b;
  uStack_5d = (undefined1)((ulong)_UNK_027fb25b >> 0x10);
  uStack_5c = (undefined1)((ulong)_UNK_027fb25b >> 0x18);
  uStack_5b = (undefined1)((ulong)_UNK_027fb25b >> 0x20);
  uStack_5a = (undefined1)((ulong)_UNK_027fb25b >> 0x28);
  uStack_59 = (undefined1)((ulong)_UNK_027fb25b >> 0x30);
  uStack_58 = (undefined1)((ulong)_UNK_027fb25b >> 0x38);
  uStack_57 = 100;
  uStack_56 = 0x65;
  uStack_55 = 0x72;
  uStack_54 = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x630,(ulong)&bStack_60 | 1);
  *(undefined1 *)(param_1 + 0x628) = 1;
  *(undefined4 *)(param_1 + 0x640) = 0;
  if ((bStack_60 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(CONCAT17(uStack_49,
                             CONCAT16(uStack_4a,
                                      CONCAT15(uStack_4b,
                                               CONCAT14(uStack_4c,
                                                        CONCAT13(uStack_4d,
                                                                 CONCAT12(uStack_4e,
                                                                          CONCAT11(uStack_4f,
                                                                                   uStack_50))))))))
    ;
  }
  lVar2 = param_1 + 0x618;
  bStack_60 = (byte)lVar2;
  uStack_5f = (undefined2)((ulong)lVar2 >> 8);
  uStack_5d = (undefined1)((ulong)lVar2 >> 0x18);
  uStack_5c = (undefined1)((ulong)lVar2 >> 0x20);
  uStack_5b = (undefined1)((ulong)lVar2 >> 0x28);
  uStack_5a = (undefined1)((ulong)lVar2 >> 0x30);
  uStack_59 = (undefined1)((ulong)lVar2 >> 0x38);
  uVar23 = (**(code **)(*(long *)(param_1 + 0x618) + 0x10))();
  plStack_78 = (long *)CONCAT44(plStack_78._4_4_,uVar23);
  std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, unsigned int, IParameterProperty*&>(unsigned int const&, unsigned int&&, IParameterProperty*&)(lVar1,&plStack_78,&plStack_78,&bStack_60);
  uStack_55 = 0;
  uStack_54 = 0;
  uStack_53 = 0;
  uStack_52 = 0;
  uStack_51 = 0;
  uStack_50 = 0;
  uStack_4f = 0;
  uStack_4e = 0;
  uStack_4d = 0;
  uStack_4c = 0;
  uStack_4b = 0;
  uStack_4a = 0;
  uStack_49 = 0;
  bStack_60 = 0x12;
  uStack_5f = (undefined2)_UNK_027fb267;
  uStack_5d = (undefined1)((ulong)_UNK_027fb267 >> 0x10);
  uStack_5c = (undefined1)((ulong)_UNK_027fb267 >> 0x18);
  uStack_5b = (undefined1)((ulong)_UNK_027fb267 >> 0x20);
  uStack_5a = (undefined1)((ulong)_UNK_027fb267 >> 0x28);
  uStack_59 = (undefined1)((ulong)_UNK_027fb267 >> 0x30);
  uStack_58 = (undefined1)((ulong)_UNK_027fb267 >> 0x38);
  uStack_57 = 0x74;
  uStack_56 = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x660,(ulong)&bStack_60 | 1);
  *(undefined1 *)(param_1 + 0x658) = 1;
  *(undefined4 *)(param_1 + 0x670) = 0;
  if ((bStack_60 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(CONCAT17(uStack_49,
                             CONCAT16(uStack_4a,
                                      CONCAT15(uStack_4b,
                                               CONCAT14(uStack_4c,
                                                        CONCAT13(uStack_4d,
                                                                 CONCAT12(uStack_4e,
                                                                          CONCAT11(uStack_4f,
                                                                                   uStack_50))))))))
    ;
  }
  lVar2 = param_1 + 0x648;
  bStack_60 = (byte)lVar2;
  uStack_5f = (undefined2)((ulong)lVar2 >> 8);
  uStack_5d = (undefined1)((ulong)lVar2 >> 0x18);
  uStack_5c = (undefined1)((ulong)lVar2 >> 0x20);
  uStack_5b = (undefined1)((ulong)lVar2 >> 0x28);
  uStack_5a = (undefined1)((ulong)lVar2 >> 0x30);
  uStack_59 = (undefined1)((ulong)lVar2 >> 0x38);
  uVar23 = (**(code **)(*(long *)(param_1 + 0x648) + 0x10))();
  plStack_78 = (long *)CONCAT44(plStack_78._4_4_,uVar23);
  std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, unsigned int, IParameterProperty*&>(unsigned int const&, unsigned int&&, IParameterProperty*&)(lVar1,&plStack_78,&plStack_78,&bStack_60);
  uStack_56 = 0;
  uStack_55 = 0;
  uStack_54 = 0;
  uStack_53 = 0;
  uStack_52 = 0;
  uStack_51 = 0;
  uStack_50 = 0;
  uStack_4f = 0;
  uStack_4e = 0;
  uStack_4d = 0;
  uStack_4c = 0;
  uStack_4b = 0;
  uStack_4a = 0;
  uStack_49 = 0;
  bStack_60 = 0x10;
  uStack_5f = 0x6564;
  uStack_5d = 0x66;
  uStack_5c = 0x5f;
  uStack_5b = 100;
  uStack_5a = 0x61;
  uStack_59 = 0x72;
  uStack_58 = 0x6b;
  uStack_57 = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x690,(ulong)&bStack_60 | 1);
  *(undefined1 *)(param_1 + 0x688) = 1;
  *(undefined4 *)(param_1 + 0x6a0) = 0;
  if ((bStack_60 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(CONCAT17(uStack_49,
                             CONCAT16(uStack_4a,
                                      CONCAT15(uStack_4b,
                                               CONCAT14(uStack_4c,
                                                        CONCAT13(uStack_4d,
                                                                 CONCAT12(uStack_4e,
                                                                          CONCAT11(uStack_4f,
                                                                                   uStack_50))))))))
    ;
  }
  lVar2 = param_1 + 0x678;
  bStack_60 = (byte)lVar2;
  uStack_5f = (undefined2)((ulong)lVar2 >> 8);
  uStack_5d = (undefined1)((ulong)lVar2 >> 0x18);
  uStack_5c = (undefined1)((ulong)lVar2 >> 0x20);
  uStack_5b = (undefined1)((ulong)lVar2 >> 0x28);
  uStack_5a = (undefined1)((ulong)lVar2 >> 0x30);
  uStack_59 = (undefined1)((ulong)lVar2 >> 0x38);
  uVar23 = (**(code **)(*(long *)(param_1 + 0x678) + 0x10))();
  plStack_78 = (long *)CONCAT44(plStack_78._4_4_,uVar23);
  std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, unsigned int, IParameterProperty*&>(unsigned int const&, unsigned int&&, IParameterProperty*&)(lVar1,&plStack_78,&plStack_78,&bStack_60);
  uStack_58 = 0;
  uStack_57 = 0;
  uStack_56 = 0;
  uStack_55 = 0;
  uStack_54 = 0;
  uStack_53 = 0;
  uStack_52 = 0;
  uStack_51 = 0;
  uStack_50 = 0;
  uStack_4f = 0;
  uStack_4e = 0;
  uStack_4d = 0;
  uStack_4c = 0;
  uStack_4b = 0;
  uStack_4a = 0;
  uStack_49 = 0;
  uStack_59 = 0;
  bStack_60 = 10;
  uStack_5b = 0x31;
  uStack_5f = 0x7572;
  uStack_5d = 0x73;
  uStack_5c = 0x68;
  uStack_5a = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x6c0,(ulong)&bStack_60 | 1);
  *(undefined1 *)(param_1 + 0x6b8) = 1;
  *(undefined4 *)(param_1 + 0x6d0) = 0;
  if ((bStack_60 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(CONCAT17(uStack_49,
                             CONCAT16(uStack_4a,
                                      CONCAT15(uStack_4b,
                                               CONCAT14(uStack_4c,
                                                        CONCAT13(uStack_4d,
                                                                 CONCAT12(uStack_4e,
                                                                          CONCAT11(uStack_4f,
                                                                                   uStack_50))))))))
    ;
  }
  lVar2 = param_1 + 0x6a8;
  bStack_60 = (byte)lVar2;
  uStack_5f = (undefined2)((ulong)lVar2 >> 8);
  uStack_5d = (undefined1)((ulong)lVar2 >> 0x18);
  uStack_5c = (undefined1)((ulong)lVar2 >> 0x20);
  uStack_5b = (undefined1)((ulong)lVar2 >> 0x28);
  uStack_5a = (undefined1)((ulong)lVar2 >> 0x30);
  uStack_59 = (undefined1)((ulong)lVar2 >> 0x38);
  uVar23 = (**(code **)(*(long *)(param_1 + 0x6a8) + 0x10))();
  plStack_78 = (long *)CONCAT44(plStack_78._4_4_,uVar23);
  std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, unsigned int, IParameterProperty*&>(unsigned int const&, unsigned int&&, IParameterProperty*&)(lVar1,&plStack_78,&plStack_78,&bStack_60);
  uStack_53 = 0;
  uStack_52 = 0;
  uStack_51 = 0;
  uStack_50 = 0;
  uStack_4f = 0;
  uStack_4e = 0;
  uStack_4d = 0;
  uStack_4c = 0;
  uStack_4b = 0;
  uStack_4a = 0;
  uStack_49 = 0;
  uStack_68 = 0;
  plStack_78 = (long *)0x0;
  uStack_70 = 0;
  bStack_60 = 0x16;
  uStack_5f = (undefined2)_UNK_027fb277;
  uStack_5d = (undefined1)((ulong)_UNK_027fb277 >> 0x10);
  uStack_5c = (undefined1)((ulong)_UNK_027fb277 >> 0x18);
  uStack_5b = (undefined1)((ulong)_UNK_027fb277 >> 0x20);
  uStack_5a = (undefined1)((ulong)_UNK_027fb277 >> 0x28);
  uStack_59 = (undefined1)((ulong)_UNK_027fb277 >> 0x30);
  uStack_58 = (undefined1)((ulong)_UNK_027fb277 >> 0x38);
  uStack_57 = 0x62;
  uStack_56 = 0x65;
  uStack_55 = 0x6c;
  uStack_54 = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x6f0,(ulong)&bStack_60 | 1);
  *(undefined1 *)(param_1 + 0x6e8) = 1;
  uVar3 = (ulong)plStack_78 >> 1 & 0x7f;
  if (((ulong)plStack_78 & 1) != 0) {
    uVar3 = uStack_70;
  }
  if (uVar3 != 0) {
    void CParameterPropertyBase<201u>::CryptString<string >(string&, string const&)(param_1 + 0x700,&plStack_78);
  }
  if (((ulong)plStack_78 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_68);
  }
  if ((bStack_60 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(CONCAT17(uStack_49,
                             CONCAT16(uStack_4a,
                                      CONCAT15(uStack_4b,
                                               CONCAT14(uStack_4c,
                                                        CONCAT13(uStack_4d,
                                                                 CONCAT12(uStack_4e,
                                                                          CONCAT11(uStack_4f,
                                                                                   uStack_50))))))))
    ;
  }
  lVar2 = param_1 + 0x6d8;
  bStack_60 = (byte)lVar2;
  uStack_5f = (undefined2)((ulong)lVar2 >> 8);
  uStack_5d = (undefined1)((ulong)lVar2 >> 0x18);
  uStack_5c = (undefined1)((ulong)lVar2 >> 0x20);
  uStack_5b = (undefined1)((ulong)lVar2 >> 0x28);
  uStack_5a = (undefined1)((ulong)lVar2 >> 0x30);
  uStack_59 = (undefined1)((ulong)lVar2 >> 0x38);
  uVar23 = (**(code **)(*(long *)(param_1 + 0x6d8) + 0x10))();
  plStack_78 = (long *)CONCAT44(plStack_78._4_4_,uVar23);
  std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, unsigned int, IParameterProperty*&>(unsigned int const&, unsigned int&&, IParameterProperty*&)(lVar1,&plStack_78,&plStack_78,&bStack_60);
  uStack_49 = 0;
  bStack_60 = 0x2a;
  uStack_57 = (undefined1)_UNK_027dc722;
  uStack_56 = (undefined1)((uint5)_UNK_027dc722 >> 8);
  uStack_55 = (undefined1)((uint5)_UNK_027dc722 >> 0x10);
  uStack_54 = (undefined1)((uint5)_UNK_027dc722 >> 0x18);
  uStack_53 = (undefined1)((uint5)_UNK_027dc722 >> 0x20);
  uStack_5f = (undefined2)_UNK_027dc71a;
  uStack_5d = (undefined1)((ulong)_UNK_027dc71a >> 0x10);
  uStack_5c = (undefined1)((ulong)_UNK_027dc71a >> 0x18);
  uStack_5b = (undefined1)((ulong)_UNK_027dc71a >> 0x20);
  uStack_5a = (undefined1)((ulong)_UNK_027dc71a >> 0x28);
  uStack_59 = (undefined1)((ulong)_UNK_027dc71a >> 0x30);
  uStack_58 = (undefined1)((ulong)_UNK_027dc71a >> 0x38);
  uStack_52 = (undefined1)_UNK_027dc727;
  uStack_51 = (undefined1)((uint3)_UNK_027dc727 >> 8);
  uStack_50 = (undefined1)((uint3)_UNK_027dc727 >> 0x10);
  uStack_4f = (undefined1)_UNK_027dc72a;
  uStack_4e = (undefined1)((uint5)_UNK_027dc72a >> 8);
  uStack_4d = (undefined1)((uint5)_UNK_027dc72a >> 0x10);
  uStack_4c = (undefined1)((uint5)_UNK_027dc72a >> 0x18);
  uStack_4b = (undefined1)((uint5)_UNK_027dc72a >> 0x20);
  uStack_4a = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x730,(ulong)&bStack_60 | 1);
  *(undefined1 *)(param_1 + 0x728) = 1;
  *(undefined4 *)(param_1 + 0x740) = 0;
  if ((bStack_60 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(CONCAT17(uStack_49,
                             CONCAT16(uStack_4a,
                                      CONCAT15(uStack_4b,
                                               CONCAT14(uStack_4c,
                                                        CONCAT13(uStack_4d,
                                                                 CONCAT12(uStack_4e,
                                                                          CONCAT11(uStack_4f,
                                                                                   uStack_50))))))))
    ;
  }
  lVar2 = param_1 + 0x718;
  bStack_60 = (byte)lVar2;
  uStack_5f = (undefined2)((ulong)lVar2 >> 8);
  uStack_5d = (undefined1)((ulong)lVar2 >> 0x18);
  uStack_5c = (undefined1)((ulong)lVar2 >> 0x20);
  uStack_5b = (undefined1)((ulong)lVar2 >> 0x28);
  uStack_5a = (undefined1)((ulong)lVar2 >> 0x30);
  uStack_59 = (undefined1)((ulong)lVar2 >> 0x38);
  uVar23 = (**(code **)(*(long *)(param_1 + 0x718) + 0x10))();
  plStack_78 = (long *)CONCAT44(plStack_78._4_4_,uVar23);
  std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, unsigned int, IParameterProperty*&>(unsigned int const&, unsigned int&&, IParameterProperty*&)(lVar1,&plStack_78,&plStack_78,&bStack_60);
  uStack_53 = 0;
  uStack_52 = 0;
  uStack_51 = 0;
  uStack_50 = 0;
  uStack_4f = 0;
  uStack_4e = 0;
  uStack_4d = 0;
  uStack_4c = 0;
  uStack_4b = 0;
  uStack_4a = 0;
  uStack_49 = 0;
  bStack_60 = 0x16;
  uStack_5f = (undefined2)_UNK_027fb283;
  uStack_5d = (undefined1)((ulong)_UNK_027fb283 >> 0x10);
  uStack_5c = (undefined1)((ulong)_UNK_027fb283 >> 0x18);
  uStack_5b = (undefined1)((ulong)_UNK_027fb283 >> 0x20);
  uStack_5a = (undefined1)((ulong)_UNK_027fb283 >> 0x28);
  uStack_59 = (undefined1)((ulong)_UNK_027fb283 >> 0x30);
  uStack_58 = (undefined1)((ulong)_UNK_027fb283 >> 0x38);
  uStack_57 = 0x76;
  uStack_56 = 0x65;
  uStack_55 = 0x6c;
  uStack_54 = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x760,(ulong)&bStack_60 | 1);
  *(undefined1 *)(param_1 + 0x758) = 1;
  *(undefined4 *)(param_1 + 0x770) = 0;
  if ((bStack_60 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(CONCAT17(uStack_49,
                             CONCAT16(uStack_4a,
                                      CONCAT15(uStack_4b,
                                               CONCAT14(uStack_4c,
                                                        CONCAT13(uStack_4d,
                                                                 CONCAT12(uStack_4e,
                                                                          CONCAT11(uStack_4f,
                                                                                   uStack_50))))))))
    ;
  }
  lVar2 = param_1 + 0x748;
  bStack_60 = (byte)lVar2;
  uStack_5f = (undefined2)((ulong)lVar2 >> 8);
  uStack_5d = (undefined1)((ulong)lVar2 >> 0x18);
  uStack_5c = (undefined1)((ulong)lVar2 >> 0x20);
  uStack_5b = (undefined1)((ulong)lVar2 >> 0x28);
  uStack_5a = (undefined1)((ulong)lVar2 >> 0x30);
  uStack_59 = (undefined1)((ulong)lVar2 >> 0x38);
  uVar23 = (**(code **)(*(long *)(param_1 + 0x748) + 0x10))();
  plStack_78 = (long *)CONCAT44(plStack_78._4_4_,uVar23);
  std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, unsigned int, IParameterProperty*&>(unsigned int const&, unsigned int&&, IParameterProperty*&)(lVar1,&plStack_78,&plStack_78,&bStack_60);
  uStack_56 = 0;
  uStack_55 = 0;
  uStack_54 = 0;
  uStack_53 = 0;
  uStack_52 = 0;
  uStack_51 = 0;
  uStack_50 = 0;
  uStack_4f = 0;
  uStack_4e = 0;
  uStack_4d = 0;
  uStack_4c = 0;
  uStack_4b = 0;
  uStack_4a = 0;
  uStack_49 = 0;
  bStack_60 = 0x10;
  uStack_5f = 0x656e;
  uStack_5d = 0x78;
  uStack_5c = 0x74;
  uStack_5b = 0x5f;
  uStack_5a = 0x65;
  uStack_59 = 0x78;
  uStack_58 = 0x70;
  uStack_57 = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x790,(ulong)&bStack_60 | 1);
  *(undefined1 *)(param_1 + 0x788) = 1;
  *(undefined4 *)(param_1 + 0x7a0) = 0;
  if ((bStack_60 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(CONCAT17(uStack_49,
                             CONCAT16(uStack_4a,
                                      CONCAT15(uStack_4b,
                                               CONCAT14(uStack_4c,
                                                        CONCAT13(uStack_4d,
                                                                 CONCAT12(uStack_4e,
                                                                          CONCAT11(uStack_4f,
                                                                                   uStack_50))))))))
    ;
  }
  lVar2 = param_1 + 0x778;
  bStack_60 = (byte)lVar2;
  uStack_5f = (undefined2)((ulong)lVar2 >> 8);
  uStack_5d = (undefined1)((ulong)lVar2 >> 0x18);
  uStack_5c = (undefined1)((ulong)lVar2 >> 0x20);
  uStack_5b = (undefined1)((ulong)lVar2 >> 0x28);
  uStack_5a = (undefined1)((ulong)lVar2 >> 0x30);
  uStack_59 = (undefined1)((ulong)lVar2 >> 0x38);
  uVar23 = (**(code **)(*(long *)(param_1 + 0x778) + 0x10))();
  plStack_78 = (long *)CONCAT44(plStack_78._4_4_,uVar23);
  std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, unsigned int, IParameterProperty*&>(unsigned int const&, unsigned int&&, IParameterProperty*&)(lVar1,&plStack_78,&plStack_78,&bStack_60);
  uStack_55 = 0;
  uStack_54 = 0;
  uStack_53 = 0;
  uStack_52 = 0;
  uStack_51 = 0;
  uStack_50 = 0;
  uStack_4f = 0;
  uStack_4e = 0;
  uStack_4d = 0;
  uStack_4c = 0;
  uStack_4b = 0;
  uStack_4a = 0;
  uStack_49 = 0;
  bStack_60 = 0x12;
  uStack_5f = (undefined2)_UNK_027dcb30;
  uStack_5d = (undefined1)((ulong)_UNK_027dcb30 >> 0x10);
  uStack_5c = (undefined1)((ulong)_UNK_027dcb30 >> 0x18);
  uStack_5b = (undefined1)((ulong)_UNK_027dcb30 >> 0x20);
  uStack_5a = (undefined1)((ulong)_UNK_027dcb30 >> 0x28);
  uStack_59 = (undefined1)((ulong)_UNK_027dcb30 >> 0x30);
  uStack_58 = (undefined1)((ulong)_UNK_027dcb30 >> 0x38);
  uStack_57 = 100;
  uStack_56 = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x7c0,(ulong)&bStack_60 | 1);
  *(undefined1 *)(param_1 + 0x7b8) = 1;
  *(undefined4 *)(param_1 + 2000) = 0;
  if ((bStack_60 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(CONCAT17(uStack_49,
                             CONCAT16(uStack_4a,
                                      CONCAT15(uStack_4b,
                                               CONCAT14(uStack_4c,
                                                        CONCAT13(uStack_4d,
                                                                 CONCAT12(uStack_4e,
                                                                          CONCAT11(uStack_4f,
                                                                                   uStack_50))))))))
    ;
  }
  lVar2 = param_1 + 0x7a8;
  bStack_60 = (byte)lVar2;
  uStack_5f = (undefined2)((ulong)lVar2 >> 8);
  uStack_5d = (undefined1)((ulong)lVar2 >> 0x18);
  uStack_5c = (undefined1)((ulong)lVar2 >> 0x20);
  uStack_5b = (undefined1)((ulong)lVar2 >> 0x28);
  uStack_5a = (undefined1)((ulong)lVar2 >> 0x30);
  uStack_59 = (undefined1)((ulong)lVar2 >> 0x38);
  uVar23 = (**(code **)(*(long *)(param_1 + 0x7a8) + 0x10))();
  plStack_78 = (long *)CONCAT44(plStack_78._4_4_,uVar23);
  std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, unsigned int, IParameterProperty*&>(unsigned int const&, unsigned int&&, IParameterProperty*&)(lVar1,&plStack_78,&plStack_78,&bStack_60);
  uStack_49 = 0;
  bStack_60 = 0x2a;
  uStack_57 = (undefined1)_UNK_027dc63a;
  uStack_56 = (undefined1)((uint5)_UNK_027dc63a >> 8);
  uStack_55 = (undefined1)((uint5)_UNK_027dc63a >> 0x10);
  uStack_54 = (undefined1)((uint5)_UNK_027dc63a >> 0x18);
  uStack_53 = (undefined1)((uint5)_UNK_027dc63a >> 0x20);
  uStack_5f = (undefined2)_UNK_027dc632;
  uStack_5d = (undefined1)((ulong)_UNK_027dc632 >> 0x10);
  uStack_5c = (undefined1)((ulong)_UNK_027dc632 >> 0x18);
  uStack_5b = (undefined1)((ulong)_UNK_027dc632 >> 0x20);
  uStack_5a = (undefined1)((ulong)_UNK_027dc632 >> 0x28);
  uStack_59 = (undefined1)((ulong)_UNK_027dc632 >> 0x30);
  uStack_58 = (undefined1)((ulong)_UNK_027dc632 >> 0x38);
  uStack_52 = (undefined1)_UNK_027dc63f;
  uStack_51 = (undefined1)((uint3)_UNK_027dc63f >> 8);
  uStack_50 = (undefined1)((uint3)_UNK_027dc63f >> 0x10);
  uStack_4f = (undefined1)_UNK_027dc642;
  uStack_4e = (undefined1)((uint5)_UNK_027dc642 >> 8);
  uStack_4d = (undefined1)((uint5)_UNK_027dc642 >> 0x10);
  uStack_4c = (undefined1)((uint5)_UNK_027dc642 >> 0x18);
  uStack_4b = (undefined1)((uint5)_UNK_027dc642 >> 0x20);
  uStack_4a = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x7f0,(ulong)&bStack_60 | 1);
  *(undefined1 *)(param_1 + 0x7e8) = 1;
  *(undefined4 *)(param_1 + 0x800) = 0;
  if ((bStack_60 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(CONCAT17(uStack_49,
                             CONCAT16(uStack_4a,
                                      CONCAT15(uStack_4b,
                                               CONCAT14(uStack_4c,
                                                        CONCAT13(uStack_4d,
                                                                 CONCAT12(uStack_4e,
                                                                          CONCAT11(uStack_4f,
                                                                                   uStack_50))))))))
    ;
  }
  lVar2 = param_1 + 0x7d8;
  bStack_60 = (byte)lVar2;
  uStack_5f = (undefined2)((ulong)lVar2 >> 8);
  uStack_5d = (undefined1)((ulong)lVar2 >> 0x18);
  uStack_5c = (undefined1)((ulong)lVar2 >> 0x20);
  uStack_5b = (undefined1)((ulong)lVar2 >> 0x28);
  uStack_5a = (undefined1)((ulong)lVar2 >> 0x30);
  uStack_59 = (undefined1)((ulong)lVar2 >> 0x38);
  uVar23 = (**(code **)(*(long *)(param_1 + 0x7d8) + 0x10))();
  plStack_78 = (long *)CONCAT44(plStack_78._4_4_,uVar23);
  std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, unsigned int, IParameterProperty*&>(unsigned int const&, unsigned int&&, IParameterProperty*&)(lVar1,&plStack_78,&plStack_78,&bStack_60);
  uStack_68 = 0;
  bStack_60 = 0x28;
  uStack_4a = 0;
  uStack_49 = 0;
  plStack_78 = (long *)0x0;
  uStack_70 = 0;
  uStack_57 = (undefined1)_UNK_027dc65e;
  uStack_56 = (undefined1)((ulong)_UNK_027dc65e >> 8);
  uStack_55 = (undefined1)((ulong)_UNK_027dc65e >> 0x10);
  uStack_54 = (undefined1)((ulong)_UNK_027dc65e >> 0x18);
  uStack_53 = (undefined1)((ulong)_UNK_027dc65e >> 0x20);
  uStack_52 = (undefined1)((ulong)_UNK_027dc65e >> 0x28);
  uStack_51 = (undefined1)((ulong)_UNK_027dc65e >> 0x30);
  uStack_50 = (undefined1)((ulong)_UNK_027dc65e >> 0x38);
  uStack_5f = (undefined2)_UNK_027dc656;
  uStack_5d = (undefined1)((ulong)_UNK_027dc656 >> 0x10);
  uStack_5c = (undefined1)((ulong)_UNK_027dc656 >> 0x18);
  uStack_5b = (undefined1)((ulong)_UNK_027dc656 >> 0x20);
  uStack_5a = (undefined1)((ulong)_UNK_027dc656 >> 0x28);
  uStack_59 = (undefined1)((ulong)_UNK_027dc656 >> 0x30);
  uStack_58 = (undefined1)((ulong)_UNK_027dc656 >> 0x38);
  uStack_4f = 0x61;
  uStack_4e = 0x62;
  uStack_4d = 0x65;
  uStack_4c = 0x6c;
  uStack_4b = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x820,(ulong)&bStack_60 | 1);
  *(undefined1 *)(param_1 + 0x818) = 1;
  uVar3 = (ulong)plStack_78 >> 1 & 0x7f;
  if (((ulong)plStack_78 & 1) != 0) {
    uVar3 = uStack_70;
  }
  if (uVar3 != 0) {
    void CParameterPropertyBase<209u>::CryptString<string >(string&, string const&)(param_1 + 0x830,&plStack_78);
  }
  if (((ulong)plStack_78 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_68);
  }
  if ((bStack_60 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(CONCAT17(uStack_49,
                             CONCAT16(uStack_4a,
                                      CONCAT15(uStack_4b,
                                               CONCAT14(uStack_4c,
                                                        CONCAT13(uStack_4d,
                                                                 CONCAT12(uStack_4e,
                                                                          CONCAT11(uStack_4f,
                                                                                   uStack_50))))))))
    ;
  }
  lVar2 = param_1 + 0x808;
  bStack_60 = (byte)lVar2;
  uStack_5f = (undefined2)((ulong)lVar2 >> 8);
  uStack_5d = (undefined1)((ulong)lVar2 >> 0x18);
  uStack_5c = (undefined1)((ulong)lVar2 >> 0x20);
  uStack_5b = (undefined1)((ulong)lVar2 >> 0x28);
  uStack_5a = (undefined1)((ulong)lVar2 >> 0x30);
  uStack_59 = (undefined1)((ulong)lVar2 >> 0x38);
  uVar23 = (**(code **)(*(long *)(param_1 + 0x808) + 0x10))();
  plStack_78 = (long *)CONCAT44(plStack_78._4_4_,uVar23);
  std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, unsigned int, IParameterProperty*&>(unsigned int const&, unsigned int&&, IParameterProperty*&)(lVar1,&plStack_78,&plStack_78,&bStack_60);
  uStack_49 = 0;
  bStack_60 = 0x2a;
  uStack_57 = (undefined1)_UNK_027fb297;
  uStack_56 = (undefined1)((uint5)_UNK_027fb297 >> 8);
  uStack_55 = (undefined1)((uint5)_UNK_027fb297 >> 0x10);
  uStack_54 = (undefined1)((uint5)_UNK_027fb297 >> 0x18);
  uStack_53 = (undefined1)((uint5)_UNK_027fb297 >> 0x20);
  uStack_5f = (undefined2)_UNK_027fb28f;
  uStack_5d = (undefined1)((ulong)_UNK_027fb28f >> 0x10);
  uStack_5c = (undefined1)((ulong)_UNK_027fb28f >> 0x18);
  uStack_5b = (undefined1)((ulong)_UNK_027fb28f >> 0x20);
  uStack_5a = (undefined1)((ulong)_UNK_027fb28f >> 0x28);
  uStack_59 = (undefined1)((ulong)_UNK_027fb28f >> 0x30);
  uStack_58 = (undefined1)((ulong)_UNK_027fb28f >> 0x38);
  uStack_52 = (undefined1)_UNK_027fb29c;
  uStack_51 = (undefined1)((uint3)_UNK_027fb29c >> 8);
  uStack_50 = (undefined1)((uint3)_UNK_027fb29c >> 0x10);
  uStack_4f = (undefined1)_UNK_027fb29f;
  uStack_4e = (undefined1)((uint5)_UNK_027fb29f >> 8);
  uStack_4d = (undefined1)((uint5)_UNK_027fb29f >> 0x10);
  uStack_4c = (undefined1)((uint5)_UNK_027fb29f >> 0x18);
  uStack_4b = (undefined1)((uint5)_UNK_027fb29f >> 0x20);
  uStack_4a = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x860,(ulong)&bStack_60 | 1);
  *(undefined1 *)(param_1 + 0x858) = 1;
  *(undefined4 *)(param_1 + 0x870) = 0;
  if ((bStack_60 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(CONCAT17(uStack_49,
                             CONCAT16(uStack_4a,
                                      CONCAT15(uStack_4b,
                                               CONCAT14(uStack_4c,
                                                        CONCAT13(uStack_4d,
                                                                 CONCAT12(uStack_4e,
                                                                          CONCAT11(uStack_4f,
                                                                                   uStack_50))))))))
    ;
  }
  lVar2 = param_1 + 0x848;
  bStack_60 = (byte)lVar2;
  uStack_5f = (undefined2)((ulong)lVar2 >> 8);
  uStack_5d = (undefined1)((ulong)lVar2 >> 0x18);
  uStack_5c = (undefined1)((ulong)lVar2 >> 0x20);
  uStack_5b = (undefined1)((ulong)lVar2 >> 0x28);
  uStack_5a = (undefined1)((ulong)lVar2 >> 0x30);
  uStack_59 = (undefined1)((ulong)lVar2 >> 0x38);
  uVar23 = (**(code **)(*(long *)(param_1 + 0x848) + 0x10))();
  plStack_78 = (long *)CONCAT44(plStack_78._4_4_,uVar23);
  std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, unsigned int, IParameterProperty*&>(unsigned int const&, unsigned int&&, IParameterProperty*&)(lVar1,&plStack_78,&plStack_78,&bStack_60);
  uStack_58 = 0;
  uStack_57 = 0;
  uStack_56 = 0;
  uStack_55 = 0;
  uStack_54 = 0;
  uStack_53 = 0;
  uStack_52 = 0;
  uStack_51 = 0;
  uStack_50 = 0;
  uStack_4f = 0;
  uStack_4e = 0;
  uStack_4d = 0;
  uStack_4c = 0;
  uStack_4b = 0;
  uStack_4a = 0;
  uStack_49 = 0;
  bStack_60 = 0;
  uStack_5f = 0;
  uStack_5d = 0;
  uStack_5c = 0;
  uStack_5b = 0;
  uStack_5a = 0;
  uStack_59 = 0;
  puVar24 = (undefined8 *)Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(0x20,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
  if (puVar24 == (undefined8 *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
  }
  uVar5 = _UNK_027fb2ad;
  uVar25 = _UNK_027fb2a5;
  uVar3 = _UNK_027dbb50;
  uStack_50 = SUB81(puVar24,0);
  uStack_4f = (undefined1)((ulong)puVar24 >> 8);
  uStack_4e = (undefined1)((ulong)puVar24 >> 0x10);
  uStack_4d = (undefined1)((ulong)puVar24 >> 0x18);
  uStack_4c = (undefined1)((ulong)puVar24 >> 0x20);
  uStack_4b = (undefined1)((ulong)puVar24 >> 0x28);
  uStack_4a = (undefined1)((ulong)puVar24 >> 0x30);
  uStack_49 = (undefined1)((ulong)puVar24 >> 0x38);
  uStack_58 = (undefined1)_UNK_027dbb58;
  uVar15 = uStack_58;
  uStack_57 = (undefined1)((ulong)_UNK_027dbb58 >> 8);
  uVar16 = uStack_57;
  uStack_56 = (undefined1)((ulong)_UNK_027dbb58 >> 0x10);
  uVar17 = uStack_56;
  uStack_55 = (undefined1)((ulong)_UNK_027dbb58 >> 0x18);
  uVar18 = uStack_55;
  uStack_54 = (undefined1)((ulong)_UNK_027dbb58 >> 0x20);
  uVar19 = uStack_54;
  uStack_53 = (undefined1)((ulong)_UNK_027dbb58 >> 0x28);
  uVar20 = uStack_53;
  uStack_52 = (undefined1)((ulong)_UNK_027dbb58 >> 0x30);
  uVar21 = uStack_52;
  uStack_51 = (undefined1)((ulong)_UNK_027dbb58 >> 0x38);
  uVar22 = uStack_51;
  bStack_60 = (byte)_UNK_027dbb50;
  bVar8 = bStack_60;
  uStack_5f = (undefined2)(_UNK_027dbb50 >> 8);
  uVar9 = uStack_5f;
  uStack_5d = (undefined1)(_UNK_027dbb50 >> 0x18);
  uVar10 = uStack_5d;
  uStack_5c = (undefined1)(_UNK_027dbb50 >> 0x20);
  uVar11 = uStack_5c;
  uStack_5b = (undefined1)(_UNK_027dbb50 >> 0x28);
  uVar12 = uStack_5b;
  uStack_5a = (undefined1)(_UNK_027dbb50 >> 0x30);
  uVar13 = uStack_5a;
  uStack_59 = (undefined1)(_UNK_027dbb50 >> 0x38);
  uVar14 = uStack_59;
  puVar24[2] = _UNK_027fb2b5;
  puVar24[1] = uVar5;
  *puVar24 = uVar25;
  *(undefined1 *)(puVar24 + 3) = 0;
  puVar4 = (undefined8 *)((ulong)&bStack_60 | 1);
  if ((uVar3 & 1) != 0) {
    puVar4 = puVar24;
  }
  Framework::CHash32::operator=(char const*)(param_1 + 0x890,puVar4);
  *(undefined1 *)(param_1 + 0x888) = 1;
  *(undefined4 *)(param_1 + 0x8a0) = 0;
  if ((bStack_60 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(CONCAT17(uStack_49,
                             CONCAT16(uStack_4a,
                                      CONCAT15(uStack_4b,
                                               CONCAT14(uStack_4c,
                                                        CONCAT13(uStack_4d,
                                                                 CONCAT12(uStack_4e,
                                                                          CONCAT11(uStack_4f,
                                                                                   uStack_50))))))))
    ;
  }
  lVar2 = param_1 + 0x878;
  bStack_60 = (byte)lVar2;
  uStack_5f = (undefined2)((ulong)lVar2 >> 8);
  uStack_5d = (undefined1)((ulong)lVar2 >> 0x18);
  uStack_5c = (undefined1)((ulong)lVar2 >> 0x20);
  uStack_5b = (undefined1)((ulong)lVar2 >> 0x28);
  uStack_5a = (undefined1)((ulong)lVar2 >> 0x30);
  uStack_59 = (undefined1)((ulong)lVar2 >> 0x38);
  uVar23 = (**(code **)(*(long *)(param_1 + 0x878) + 0x10))();
  plStack_78 = (long *)CONCAT44(plStack_78._4_4_,uVar23);
  std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, unsigned int, IParameterProperty*&>(unsigned int const&, unsigned int&&, IParameterProperty*&)(lVar1,&plStack_78,&plStack_78,&bStack_60);
  uStack_52 = 0;
  uStack_51 = 0;
  uStack_50 = 0;
  uStack_4f = 0;
  uStack_4e = 0;
  uStack_4d = 0;
  uStack_4c = 0;
  uStack_4b = 0;
  uStack_4a = 0;
  uStack_49 = 0;
  bStack_60 = 0x18;
  uStack_5f = (undefined2)_UNK_027fb2be;
  uStack_5d = (undefined1)((ulong)_UNK_027fb2be >> 0x10);
  uStack_5c = (undefined1)((ulong)_UNK_027fb2be >> 0x18);
  uStack_5b = (undefined1)((ulong)_UNK_027fb2be >> 0x20);
  uStack_5a = (undefined1)((ulong)_UNK_027fb2be >> 0x28);
  uStack_59 = (undefined1)((ulong)_UNK_027fb2be >> 0x30);
  uStack_58 = (undefined1)((ulong)_UNK_027fb2be >> 0x38);
  uStack_57 = 0x65;
  uStack_56 = 0x76;
  uStack_55 = 0x65;
  uStack_54 = 0x6c;
  uStack_53 = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x8c0,(ulong)&bStack_60 | 1);
  *(undefined1 *)(param_1 + 0x8b8) = 1;
  *(undefined4 *)(param_1 + 0x8d0) = 0;
  if ((bStack_60 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(CONCAT17(uStack_49,
                             CONCAT16(uStack_4a,
                                      CONCAT15(uStack_4b,
                                               CONCAT14(uStack_4c,
                                                        CONCAT13(uStack_4d,
                                                                 CONCAT12(uStack_4e,
                                                                          CONCAT11(uStack_4f,
                                                                                   uStack_50))))))))
    ;
  }
  lVar2 = param_1 + 0x8a8;
  bStack_60 = (byte)lVar2;
  uStack_5f = (undefined2)((ulong)lVar2 >> 8);
  uStack_5d = (undefined1)((ulong)lVar2 >> 0x18);
  uStack_5c = (undefined1)((ulong)lVar2 >> 0x20);
  uStack_5b = (undefined1)((ulong)lVar2 >> 0x28);
  uStack_5a = (undefined1)((ulong)lVar2 >> 0x30);
  uStack_59 = (undefined1)((ulong)lVar2 >> 0x38);
  uVar23 = (**(code **)(*(long *)(param_1 + 0x8a8) + 0x10))();
  plStack_78 = (long *)CONCAT44(plStack_78._4_4_,uVar23);
  std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, unsigned int, IParameterProperty*&>(unsigned int const&, unsigned int&&, IParameterProperty*&)(lVar1,&plStack_78,&plStack_78,&bStack_60);
  uStack_58 = 0;
  uStack_57 = 0;
  uStack_56 = 0;
  uStack_55 = 0;
  uStack_54 = 0;
  uStack_53 = 0;
  uStack_52 = 0;
  uStack_51 = 0;
  uStack_50 = 0;
  uStack_4f = 0;
  uStack_4e = 0;
  uStack_4d = 0;
  uStack_4c = 0;
  uStack_4b = 0;
  uStack_4a = 0;
  uStack_49 = 0;
  bStack_60 = 0;
  uStack_5f = 0;
  uStack_5d = 0;
  uStack_5c = 0;
  uStack_5b = 0;
  uStack_5a = 0;
  uStack_59 = 0;
  puVar24 = (undefined8 *)Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(0x20,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
  if (puVar24 == (undefined8 *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
  }
  uVar6 = _UNK_027fb2db;
  uVar5 = _UNK_027fb2d3;
  uVar25 = _UNK_027fb2cb;
  uStack_50 = SUB81(puVar24,0);
  uStack_4f = (undefined1)((ulong)puVar24 >> 8);
  uStack_4e = (undefined1)((ulong)puVar24 >> 0x10);
  uStack_4d = (undefined1)((ulong)puVar24 >> 0x18);
  uStack_4c = (undefined1)((ulong)puVar24 >> 0x20);
  uStack_4b = (undefined1)((ulong)puVar24 >> 0x28);
  uStack_4a = (undefined1)((ulong)puVar24 >> 0x30);
  uStack_49 = (undefined1)((ulong)puVar24 >> 0x38);
  *(undefined1 *)(puVar24 + 3) = 0;
  puVar24[2] = uVar6;
  puVar24[1] = uVar5;
  *puVar24 = uVar25;
  puVar4 = (undefined8 *)((ulong)&bStack_60 | 1);
  if ((uVar3 & 1) != 0) {
    puVar4 = puVar24;
  }
  bStack_60 = bVar8;
  uStack_5f = uVar9;
  uStack_5d = uVar10;
  uStack_5c = uVar11;
  uStack_5b = uVar12;
  uStack_5a = uVar13;
  uStack_59 = uVar14;
  uStack_58 = uVar15;
  uStack_57 = uVar16;
  uStack_56 = uVar17;
  uStack_55 = uVar18;
  uStack_54 = uVar19;
  uStack_53 = uVar20;
  uStack_52 = uVar21;
  uStack_51 = uVar22;
  Framework::CHash32::operator=(char const*)(param_1 + 0x8f0,puVar4);
  *(undefined1 *)(param_1 + 0x8e8) = 1;
  *(undefined4 *)(param_1 + 0x900) = 0;
  if ((bStack_60 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(CONCAT17(uStack_49,
                             CONCAT16(uStack_4a,
                                      CONCAT15(uStack_4b,
                                               CONCAT14(uStack_4c,
                                                        CONCAT13(uStack_4d,
                                                                 CONCAT12(uStack_4e,
                                                                          CONCAT11(uStack_4f,
                                                                                   uStack_50))))))))
    ;
  }
  lVar2 = param_1 + 0x8d8;
  bStack_60 = (byte)lVar2;
  uStack_5f = (undefined2)((ulong)lVar2 >> 8);
  uStack_5d = (undefined1)((ulong)lVar2 >> 0x18);
  uStack_5c = (undefined1)((ulong)lVar2 >> 0x20);
  uStack_5b = (undefined1)((ulong)lVar2 >> 0x28);
  uStack_5a = (undefined1)((ulong)lVar2 >> 0x30);
  uStack_59 = (undefined1)((ulong)lVar2 >> 0x38);
  uVar23 = (**(code **)(*(long *)(param_1 + 0x8d8) + 0x10))();
  plStack_78 = (long *)CONCAT44(plStack_78._4_4_,uVar23);
  std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, unsigned int, IParameterProperty*&>(unsigned int const&, unsigned int&&, IParameterProperty*&)(lVar1,&plStack_78,&plStack_78,&bStack_60);
  puVar24 = (undefined8 *)Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(0x20,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
  if (puVar24 == (undefined8 *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
  }
  uVar7 = _UNK_027fb2f7;
  uVar6 = _UNK_027fb2e4;
  uVar5 = CONCAT35(_UNK_027fb2f4,_UNK_027fb2ef);
  uVar25 = CONCAT53(_UNK_027fb2ef,_UNK_027fb2ec);
  *(undefined1 *)((long)puVar24 + 0x1b) = 0;
  lVar2 = param_1 + 0x908;
  *(undefined8 *)((long)puVar24 + 0x13) = uVar7;
  *(undefined8 *)((long)puVar24 + 0xb) = uVar5;
  puVar24[1] = uVar25;
  *puVar24 = uVar6;
  Framework::CHash32::operator=(char const*)(param_1 + 0x920,puVar24);
  *(undefined1 *)(param_1 + 0x918) = 1;
  *(undefined4 *)(param_1 + 0x930) = 0;
  Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puVar24);
  bStack_60 = (byte)lVar2;
  uStack_5f = (undefined2)((ulong)lVar2 >> 8);
  uStack_5d = (undefined1)((ulong)lVar2 >> 0x18);
  uStack_5c = (undefined1)((ulong)lVar2 >> 0x20);
  uStack_5b = (undefined1)((ulong)lVar2 >> 0x28);
  uStack_5a = (undefined1)((ulong)lVar2 >> 0x30);
  uStack_59 = (undefined1)((ulong)lVar2 >> 0x38);
  uVar23 = (**(code **)(*(long *)(param_1 + 0x908) + 0x10))(lVar2);
  plStack_78 = (long *)CONCAT44(plStack_78._4_4_,uVar23);
  std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, unsigned int, IParameterProperty*&>(unsigned int const&, unsigned int&&, IParameterProperty*&)(lVar1,&plStack_78,&plStack_78,&bStack_60);
  uStack_4f = 0;
  uStack_4e = 0;
  uStack_4d = 0;
  uStack_4c = 0;
  uStack_4b = 0;
  uStack_4a = 0;
  uStack_49 = 0;
  bStack_60 = 0x1e;
  uStack_5f = (undefined2)_UNK_027fb300;
  uStack_5d = (undefined1)((uint7)_UNK_027fb300 >> 0x10);
  uStack_5c = (undefined1)((uint7)_UNK_027fb300 >> 0x18);
  uStack_5b = (undefined1)((uint7)_UNK_027fb300 >> 0x20);
  uStack_5a = (undefined1)((uint7)_UNK_027fb300 >> 0x28);
  uStack_59 = (undefined1)((uint7)_UNK_027fb300 >> 0x30);
  uStack_58 = UNK_027fb307;
  uStack_57 = (undefined1)_UNK_027fb308;
  uStack_56 = (undefined1)((uint7)_UNK_027fb308 >> 8);
  uStack_55 = (undefined1)((uint7)_UNK_027fb308 >> 0x10);
  uStack_54 = (undefined1)((uint7)_UNK_027fb308 >> 0x18);
  uStack_53 = (undefined1)((uint7)_UNK_027fb308 >> 0x20);
  uStack_52 = (undefined1)((uint7)_UNK_027fb308 >> 0x28);
  uStack_51 = (undefined1)((uint7)_UNK_027fb308 >> 0x30);
  uStack_50 = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x950,(ulong)&bStack_60 | 1);
  *(undefined1 *)(param_1 + 0x948) = 1;
  *(undefined4 *)(param_1 + 0x960) = 0;
  if ((bStack_60 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(CONCAT17(uStack_49,
                             CONCAT16(uStack_4a,
                                      CONCAT15(uStack_4b,
                                               CONCAT14(uStack_4c,
                                                        CONCAT13(uStack_4d,
                                                                 CONCAT12(uStack_4e,
                                                                          CONCAT11(uStack_4f,
                                                                                   uStack_50))))))))
    ;
  }
  lVar2 = param_1 + 0x938;
  bStack_60 = (byte)lVar2;
  uStack_5f = (undefined2)((ulong)lVar2 >> 8);
  uStack_5d = (undefined1)((ulong)lVar2 >> 0x18);
  uStack_5c = (undefined1)((ulong)lVar2 >> 0x20);
  uStack_5b = (undefined1)((ulong)lVar2 >> 0x28);
  uStack_5a = (undefined1)((ulong)lVar2 >> 0x30);
  uStack_59 = (undefined1)((ulong)lVar2 >> 0x38);
  uVar23 = (**(code **)(*(long *)(param_1 + 0x938) + 0x10))();
  plStack_78 = (long *)CONCAT44(plStack_78._4_4_,uVar23);
  std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, unsigned int, IParameterProperty*&>(unsigned int const&, unsigned int&&, IParameterProperty*&)(lVar1,&plStack_78,&plStack_78,&bStack_60);
  uStack_53 = 0;
  uStack_52 = 0;
  uStack_51 = 0;
  uStack_50 = 0;
  uStack_4f = 0;
  uStack_4e = 0;
  uStack_4d = 0;
  uStack_4c = 0;
  uStack_4b = 0;
  uStack_4a = 0;
  uStack_49 = 0;
  bStack_60 = 0x16;
  uStack_5f = (undefined2)_UNK_027fb310;
  uStack_5d = (undefined1)((ulong)_UNK_027fb310 >> 0x10);
  uStack_5c = (undefined1)((ulong)_UNK_027fb310 >> 0x18);
  uStack_5b = (undefined1)((ulong)_UNK_027fb310 >> 0x20);
  uStack_5a = (undefined1)((ulong)_UNK_027fb310 >> 0x28);
  uStack_59 = (undefined1)((ulong)_UNK_027fb310 >> 0x30);
  uStack_58 = (undefined1)((ulong)_UNK_027fb310 >> 0x38);
  uStack_57 = 0x61;
  uStack_56 = 0x74;
  uStack_55 = 0x65;
  uStack_54 = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x980,(ulong)&bStack_60 | 1);
  *(undefined1 *)(param_1 + 0x978) = 1;
  *(undefined4 *)(param_1 + 0x990) = 0;
  if ((bStack_60 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(CONCAT17(uStack_49,
                             CONCAT16(uStack_4a,
                                      CONCAT15(uStack_4b,
                                               CONCAT14(uStack_4c,
                                                        CONCAT13(uStack_4d,
                                                                 CONCAT12(uStack_4e,
                                                                          CONCAT11(uStack_4f,
                                                                                   uStack_50))))))))
    ;
  }
  lVar2 = param_1 + 0x968;
  bStack_60 = (byte)lVar2;
  uStack_5f = (undefined2)((ulong)lVar2 >> 8);
  uStack_5d = (undefined1)((ulong)lVar2 >> 0x18);
  uStack_5c = (undefined1)((ulong)lVar2 >> 0x20);
  uStack_5b = (undefined1)((ulong)lVar2 >> 0x28);
  uStack_5a = (undefined1)((ulong)lVar2 >> 0x30);
  uStack_59 = (undefined1)((ulong)lVar2 >> 0x38);
  uVar23 = (**(code **)(*(long *)(param_1 + 0x968) + 0x10))();
  plStack_78 = (long *)CONCAT44(plStack_78._4_4_,uVar23);
  std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, unsigned int, IParameterProperty*&>(unsigned int const&, unsigned int&&, IParameterProperty*&)(lVar1,&plStack_78,&plStack_78,&bStack_60);
  uStack_53 = 0;
  uStack_52 = 0;
  uStack_51 = 0;
  uStack_50 = 0;
  uStack_4f = 0;
  uStack_4e = 0;
  uStack_4d = 0;
  uStack_4c = 0;
  uStack_4b = 0;
  uStack_4a = 0;
  uStack_49 = 0;
  bStack_60 = 0x16;
  uStack_5f = (undefined2)_UNK_027fb31c;
  uStack_5d = (undefined1)((ulong)_UNK_027fb31c >> 0x10);
  uStack_5c = (undefined1)((ulong)_UNK_027fb31c >> 0x18);
  uStack_5b = (undefined1)((ulong)_UNK_027fb31c >> 0x20);
  uStack_5a = (undefined1)((ulong)_UNK_027fb31c >> 0x28);
  uStack_59 = (undefined1)((ulong)_UNK_027fb31c >> 0x30);
  uStack_58 = (undefined1)((ulong)_UNK_027fb31c >> 0x38);
  uStack_57 = 0x61;
  uStack_56 = 0x74;
  uStack_55 = 0x65;
  uStack_54 = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x9b0,(ulong)&bStack_60 | 1);
  *(undefined1 *)(param_1 + 0x9a8) = 1;
  *(undefined4 *)(param_1 + 0x9c0) = 0;
  if ((bStack_60 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(CONCAT17(uStack_49,
                             CONCAT16(uStack_4a,
                                      CONCAT15(uStack_4b,
                                               CONCAT14(uStack_4c,
                                                        CONCAT13(uStack_4d,
                                                                 CONCAT12(uStack_4e,
                                                                          CONCAT11(uStack_4f,
                                                                                   uStack_50))))))))
    ;
  }
  lVar2 = param_1 + 0x998;
  bStack_60 = (byte)lVar2;
  uStack_5f = (undefined2)((ulong)lVar2 >> 8);
  uStack_5d = (undefined1)((ulong)lVar2 >> 0x18);
  uStack_5c = (undefined1)((ulong)lVar2 >> 0x20);
  uStack_5b = (undefined1)((ulong)lVar2 >> 0x28);
  uStack_5a = (undefined1)((ulong)lVar2 >> 0x30);
  uStack_59 = (undefined1)((ulong)lVar2 >> 0x38);
  uVar23 = (**(code **)(*(long *)(param_1 + 0x998) + 0x10))();
  plStack_78 = (long *)CONCAT44(plStack_78._4_4_,uVar23);
  std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, unsigned int, IParameterProperty*&>(unsigned int const&, unsigned int&&, IParameterProperty*&)(lVar1,&plStack_78,&plStack_78,&bStack_60);
  uStack_52 = 0;
  uStack_51 = 0;
  uStack_50 = 0;
  uStack_4f = 0;
  uStack_4e = 0;
  uStack_4d = 0;
  uStack_4c = 0;
  uStack_4b = 0;
  uStack_4a = 0;
  uStack_49 = 0;
  bStack_60 = 0x18;
  uStack_5f = (undefined2)_UNK_027fb328;
  uStack_5d = (undefined1)((ulong)_UNK_027fb328 >> 0x10);
  uStack_5c = (undefined1)((ulong)_UNK_027fb328 >> 0x18);
  uStack_5b = (undefined1)((ulong)_UNK_027fb328 >> 0x20);
  uStack_5a = (undefined1)((ulong)_UNK_027fb328 >> 0x28);
  uStack_59 = (undefined1)((ulong)_UNK_027fb328 >> 0x30);
  uStack_58 = (undefined1)((ulong)_UNK_027fb328 >> 0x38);
  uStack_57 = 0x5f;
  uStack_56 = 0x6e;
  uStack_55 = 0x75;
  uStack_54 = 0x6d;
  uStack_53 = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x9e0,(ulong)&bStack_60 | 1);
  *(undefined1 *)(param_1 + 0x9d8) = 1;
  *(undefined4 *)(param_1 + 0x9f0) = 0;
  if ((bStack_60 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(CONCAT17(uStack_49,
                             CONCAT16(uStack_4a,
                                      CONCAT15(uStack_4b,
                                               CONCAT14(uStack_4c,
                                                        CONCAT13(uStack_4d,
                                                                 CONCAT12(uStack_4e,
                                                                          CONCAT11(uStack_4f,
                                                                                   uStack_50))))))))
    ;
  }
  lVar2 = param_1 + 0x9c8;
  bStack_60 = (byte)lVar2;
  uStack_5f = (undefined2)((ulong)lVar2 >> 8);
  uStack_5d = (undefined1)((ulong)lVar2 >> 0x18);
  uStack_5c = (undefined1)((ulong)lVar2 >> 0x20);
  uStack_5b = (undefined1)((ulong)lVar2 >> 0x28);
  uStack_5a = (undefined1)((ulong)lVar2 >> 0x30);
  uStack_59 = (undefined1)((ulong)lVar2 >> 0x38);
  uVar23 = (**(code **)(*(long *)(param_1 + 0x9c8) + 0x10))();
  plStack_78 = (long *)CONCAT44(plStack_78._4_4_,uVar23);
  std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, unsigned int, IParameterProperty*&>(unsigned int const&, unsigned int&&, IParameterProperty*&)(lVar1,&plStack_78,&plStack_78,&bStack_60);
  uStack_4b = 0;
  uStack_4a = 0;
  uStack_49 = 0;
  bStack_60 = 0x26;
  uStack_57 = (undefined1)_UNK_027fb33d;
  uStack_56 = (undefined1)((ulong)_UNK_027fb33d >> 8);
  uStack_55 = (undefined1)((ulong)_UNK_027fb33d >> 0x10);
  uStack_54 = (undefined1)((ulong)_UNK_027fb33d >> 0x18);
  uStack_53 = (undefined1)((ulong)_UNK_027fb33d >> 0x20);
  uStack_52 = (undefined1)((ulong)_UNK_027fb33d >> 0x28);
  uStack_51 = (undefined1)((ulong)_UNK_027fb33d >> 0x30);
  uStack_50 = (undefined1)((ulong)_UNK_027fb33d >> 0x38);
  uStack_5f = (undefined2)_UNK_027fb335;
  uStack_5d = (undefined1)((ulong)_UNK_027fb335 >> 0x10);
  uStack_5c = (undefined1)((ulong)_UNK_027fb335 >> 0x18);
  uStack_5b = (undefined1)((ulong)_UNK_027fb335 >> 0x20);
  uStack_5a = (undefined1)((ulong)_UNK_027fb335 >> 0x28);
  uStack_59 = (undefined1)((ulong)_UNK_027fb335 >> 0x30);
  uStack_58 = (undefined1)((ulong)_UNK_027fb335 >> 0x38);
  uStack_4f = 0x6e;
  uStack_4e = 0x75;
  uStack_4d = 0x73;
  uStack_4c = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0xa10,(ulong)&bStack_60 | 1);
  *(undefined1 *)(param_1 + 0xa08) = 1;
  *(undefined4 *)(param_1 + 0xa20) = 0;
  if ((bStack_60 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(CONCAT17(uStack_49,
                             CONCAT16(uStack_4a,
                                      CONCAT15(uStack_4b,
                                               CONCAT14(uStack_4c,
                                                        CONCAT13(uStack_4d,
                                                                 CONCAT12(uStack_4e,
                                                                          CONCAT11(uStack_4f,
                                                                                   uStack_50))))))))
    ;
  }
  lVar2 = param_1 + 0x9f8;
  bStack_60 = (byte)lVar2;
  uStack_5f = (undefined2)((ulong)lVar2 >> 8);
  uStack_5d = (undefined1)((ulong)lVar2 >> 0x18);
  uStack_5c = (undefined1)((ulong)lVar2 >> 0x20);
  uStack_5b = (undefined1)((ulong)lVar2 >> 0x28);
  uStack_5a = (undefined1)((ulong)lVar2 >> 0x30);
  uStack_59 = (undefined1)((ulong)lVar2 >> 0x38);
  uVar23 = (**(code **)(*(long *)(param_1 + 0x9f8) + 0x10))();
  plStack_78 = (long *)CONCAT44(plStack_78._4_4_,uVar23);
  std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, unsigned int, IParameterProperty*&>(unsigned int const&, unsigned int&&, IParameterProperty*&)(lVar1,&plStack_78,&plStack_78,&bStack_60);
  uStack_4c = 0;
  uStack_4b = 0;
  uStack_4a = 0;
  uStack_49 = 0;
  bStack_60 = 0x24;
  uStack_57 = (undefined1)_UNK_027fb351;
  uStack_56 = (undefined1)((ulong)_UNK_027fb351 >> 8);
  uStack_55 = (undefined1)((ulong)_UNK_027fb351 >> 0x10);
  uStack_54 = (undefined1)((ulong)_UNK_027fb351 >> 0x18);
  uStack_53 = (undefined1)((ulong)_UNK_027fb351 >> 0x20);
  uStack_52 = (undefined1)((ulong)_UNK_027fb351 >> 0x28);
  uStack_51 = (undefined1)((ulong)_UNK_027fb351 >> 0x30);
  uStack_50 = (undefined1)((ulong)_UNK_027fb351 >> 0x38);
  uStack_5f = (undefined2)_UNK_027fb349;
  uStack_5d = (undefined1)((ulong)_UNK_027fb349 >> 0x10);
  uStack_5c = (undefined1)((ulong)_UNK_027fb349 >> 0x18);
  uStack_5b = (undefined1)((ulong)_UNK_027fb349 >> 0x20);
  uStack_5a = (undefined1)((ulong)_UNK_027fb349 >> 0x28);
  uStack_59 = (undefined1)((ulong)_UNK_027fb349 >> 0x30);
  uStack_58 = (undefined1)((ulong)_UNK_027fb349 >> 0x38);
  uStack_4f = 0x75;
  uStack_4e = 0x6d;
  uStack_4d = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0xa40,(ulong)&bStack_60 | 1);
  *(undefined1 *)(param_1 + 0xa38) = 1;
  *(undefined4 *)(param_1 + 0xa50) = 0;
  if ((bStack_60 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(CONCAT17(uStack_49,
                             CONCAT16(uStack_4a,
                                      CONCAT15(uStack_4b,
                                               CONCAT14(uStack_4c,
                                                        CONCAT13(uStack_4d,
                                                                 CONCAT12(uStack_4e,
                                                                          CONCAT11(uStack_4f,
                                                                                   uStack_50))))))))
    ;
  }
  lVar2 = param_1 + 0xa28;
  bStack_60 = (byte)lVar2;
  uStack_5f = (undefined2)((ulong)lVar2 >> 8);
  uStack_5d = (undefined1)((ulong)lVar2 >> 0x18);
  uStack_5c = (undefined1)((ulong)lVar2 >> 0x20);
  uStack_5b = (undefined1)((ulong)lVar2 >> 0x28);
  uStack_5a = (undefined1)((ulong)lVar2 >> 0x30);
  uStack_59 = (undefined1)((ulong)lVar2 >> 0x38);
  uVar23 = (**(code **)(*(long *)(param_1 + 0xa28) + 0x10))();
  plStack_78 = (long *)CONCAT44(plStack_78._4_4_,uVar23);
  std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, unsigned int, IParameterProperty*&>(unsigned int const&, unsigned int&&, IParameterProperty*&)(lVar1,&plStack_78,&plStack_78,&bStack_60);
  uStack_55 = 0;
  uStack_54 = 0;
  uStack_53 = 0;
  uStack_52 = 0;
  uStack_51 = 0;
  uStack_50 = 0;
  uStack_4f = 0;
  uStack_4e = 0;
  uStack_4d = 0;
  uStack_4c = 0;
  uStack_4b = 0;
  uStack_4a = 0;
  uStack_49 = 0;
  bStack_60 = 0x12;
  uStack_5f = (undefined2)_UNK_027fb35c;
  uStack_5d = (undefined1)((ulong)_UNK_027fb35c >> 0x10);
  uStack_5c = (undefined1)((ulong)_UNK_027fb35c >> 0x18);
  uStack_5b = (undefined1)((ulong)_UNK_027fb35c >> 0x20);
  uStack_5a = (undefined1)((ulong)_UNK_027fb35c >> 0x28);
  uStack_59 = (undefined1)((ulong)_UNK_027fb35c >> 0x30);
  uStack_58 = (undefined1)((ulong)_UNK_027fb35c >> 0x38);
  uStack_57 = 0x65;
  uStack_56 = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0xa70,(ulong)&bStack_60 | 1);
  *(undefined1 *)(param_1 + 0xa68) = 1;
  *(undefined1 *)(param_1 + 0xa80) = 0;
  if ((bStack_60 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(CONCAT17(uStack_49,
                             CONCAT16(uStack_4a,
                                      CONCAT15(uStack_4b,
                                               CONCAT14(uStack_4c,
                                                        CONCAT13(uStack_4d,
                                                                 CONCAT12(uStack_4e,
                                                                          CONCAT11(uStack_4f,
                                                                                   uStack_50))))))))
    ;
  }
  lVar2 = param_1 + 0xa58;
  bStack_60 = (byte)lVar2;
  uStack_5f = (undefined2)((ulong)lVar2 >> 8);
  uStack_5d = (undefined1)((ulong)lVar2 >> 0x18);
  uStack_5c = (undefined1)((ulong)lVar2 >> 0x20);
  uStack_5b = (undefined1)((ulong)lVar2 >> 0x28);
  uStack_5a = (undefined1)((ulong)lVar2 >> 0x30);
  uStack_59 = (undefined1)((ulong)lVar2 >> 0x38);
  uVar23 = (**(code **)(*(long *)(param_1 + 0xa58) + 0x10))();
  plStack_78 = (long *)CONCAT44(plStack_78._4_4_,uVar23);
  std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, unsigned int, IParameterProperty*&>(unsigned int const&, unsigned int&&, IParameterProperty*&)(lVar1,&plStack_78,&plStack_78,&bStack_60);
  uStack_4f = 0;
  uStack_4e = 0;
  uStack_4d = 0;
  uStack_4c = 0;
  uStack_4b = 0;
  uStack_4a = 0;
  uStack_49 = 0;
  bStack_60 = 0x1e;
  uStack_5f = (undefined2)_UNK_027fb366;
  uStack_5d = (undefined1)((uint7)_UNK_027fb366 >> 0x10);
  uStack_5c = (undefined1)((uint7)_UNK_027fb366 >> 0x18);
  uStack_5b = (undefined1)((uint7)_UNK_027fb366 >> 0x20);
  uStack_5a = (undefined1)((uint7)_UNK_027fb366 >> 0x28);
  uStack_59 = (undefined1)((uint7)_UNK_027fb366 >> 0x30);
  uStack_58 = UNK_027fb36d;
  uStack_57 = (undefined1)_UNK_027fb36e;
  uStack_56 = (undefined1)((uint7)_UNK_027fb36e >> 8);
  uStack_55 = (undefined1)((uint7)_UNK_027fb36e >> 0x10);
  uStack_54 = (undefined1)((uint7)_UNK_027fb36e >> 0x18);
  uStack_53 = (undefined1)((uint7)_UNK_027fb36e >> 0x20);
  uStack_52 = (undefined1)((uint7)_UNK_027fb36e >> 0x28);
  uStack_51 = (undefined1)((uint7)_UNK_027fb36e >> 0x30);
  uStack_50 = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0xaa0,(ulong)&bStack_60 | 1);
  *(undefined1 *)(param_1 + 0xa98) = 1;
  *(undefined1 *)(param_1 + 0xab0) = 0;
  if ((bStack_60 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(CONCAT17(uStack_49,
                             CONCAT16(uStack_4a,
                                      CONCAT15(uStack_4b,
                                               CONCAT14(uStack_4c,
                                                        CONCAT13(uStack_4d,
                                                                 CONCAT12(uStack_4e,
                                                                          CONCAT11(uStack_4f,
                                                                                   uStack_50))))))))
    ;
  }
  lVar2 = param_1 + 0xa88;
  bStack_60 = (byte)lVar2;
  uStack_5f = (undefined2)((ulong)lVar2 >> 8);
  uStack_5d = (undefined1)((ulong)lVar2 >> 0x18);
  uStack_5c = (undefined1)((ulong)lVar2 >> 0x20);
  uStack_5b = (undefined1)((ulong)lVar2 >> 0x28);
  uStack_5a = (undefined1)((ulong)lVar2 >> 0x30);
  uStack_59 = (undefined1)((ulong)lVar2 >> 0x38);
  uVar23 = (**(code **)(*(long *)(param_1 + 0xa88) + 0x10))();
  plStack_78 = (long *)CONCAT44(plStack_78._4_4_,uVar23);
  std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, unsigned int, IParameterProperty*&>(unsigned int const&, unsigned int&&, IParameterProperty*&)(lVar1,&plStack_78,&plStack_78,&bStack_60);
  uStack_58 = 0;
  uStack_57 = 0;
  uStack_56 = 0;
  uStack_55 = 0;
  uStack_54 = 0;
  uStack_53 = 0;
  uStack_52 = 0;
  uStack_51 = 0;
  uStack_50 = 0;
  uStack_4f = 0;
  uStack_4e = 0;
  uStack_4d = 0;
  uStack_4c = 0;
  uStack_4b = 0;
  uStack_4a = 0;
  uStack_49 = 0;
  uStack_59 = 0;
  bStack_60 = 10;
  uStack_5b = 0x65;
  uStack_5f = 0x6974;
  uStack_5d = 0x74;
  uStack_5c = 0x6c;
  uStack_5a = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0xad0,(ulong)&bStack_60 | 1);
  *(undefined1 *)(param_1 + 0xac8) = 1;
  *(undefined4 *)(param_1 + 0xae0) = 0;
  if ((bStack_60 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(CONCAT17(uStack_49,
                             CONCAT16(uStack_4a,
                                      CONCAT15(uStack_4b,
                                               CONCAT14(uStack_4c,
                                                        CONCAT13(uStack_4d,
                                                                 CONCAT12(uStack_4e,
                                                                          CONCAT11(uStack_4f,
                                                                                   uStack_50))))))))
    ;
  }
  lVar2 = param_1 + 0xab8;
  bStack_60 = (byte)lVar2;
  uStack_5f = (undefined2)((ulong)lVar2 >> 8);
  uStack_5d = (undefined1)((ulong)lVar2 >> 0x18);
  uStack_5c = (undefined1)((ulong)lVar2 >> 0x20);
  uStack_5b = (undefined1)((ulong)lVar2 >> 0x28);
  uStack_5a = (undefined1)((ulong)lVar2 >> 0x30);
  uStack_59 = (undefined1)((ulong)lVar2 >> 0x38);
  uVar23 = (**(code **)(*(long *)(param_1 + 0xab8) + 0x10))();
  plStack_78 = (long *)CONCAT44(plStack_78._4_4_,uVar23);
  std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, unsigned int, IParameterProperty*&>(unsigned int const&, unsigned int&&, IParameterProperty*&)(lVar1,&plStack_78,&plStack_78,&bStack_60);
  uStack_58 = 0;
  uStack_57 = 0;
  uStack_56 = 0;
  uStack_55 = 0;
  uStack_54 = 0;
  uStack_53 = 0;
  uStack_52 = 0;
  uStack_51 = 0;
  uStack_50 = 0;
  uStack_4f = 0;
  uStack_4e = 0;
  uStack_4d = 0;
  uStack_4c = 0;
  uStack_4b = 0;
  uStack_4a = 0;
  uStack_49 = 0;
  bStack_60 = 0xc;
  uStack_5b = 0x68;
  uStack_5a = 0x70;
  uStack_5f = 0x6461;
  uStack_5d = 100;
  uStack_5c = 0x5f;
  uStack_59 = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0xb00,(ulong)&bStack_60 | 1);
  *(undefined1 *)(param_1 + 0xaf8) = 1;
  *(undefined4 *)(param_1 + 0xb10) = 0;
  if ((bStack_60 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(CONCAT17(uStack_49,
                             CONCAT16(uStack_4a,
                                      CONCAT15(uStack_4b,
                                               CONCAT14(uStack_4c,
                                                        CONCAT13(uStack_4d,
                                                                 CONCAT12(uStack_4e,
                                                                          CONCAT11(uStack_4f,
                                                                                   uStack_50))))))))
    ;
  }
  lVar2 = param_1 + 0xae8;
  bStack_60 = (byte)lVar2;
  uStack_5f = (undefined2)((ulong)lVar2 >> 8);
  uStack_5d = (undefined1)((ulong)lVar2 >> 0x18);
  uStack_5c = (undefined1)((ulong)lVar2 >> 0x20);
  uStack_5b = (undefined1)((ulong)lVar2 >> 0x28);
  uStack_5a = (undefined1)((ulong)lVar2 >> 0x30);
  uStack_59 = (undefined1)((ulong)lVar2 >> 0x38);
  uVar23 = (**(code **)(*(long *)(param_1 + 0xae8) + 0x10))();
  plStack_78 = (long *)CONCAT44(plStack_78._4_4_,uVar23);
  std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, unsigned int, IParameterProperty*&>(unsigned int const&, unsigned int&&, IParameterProperty*&)(lVar1,&plStack_78,&plStack_78,&bStack_60);
  uStack_54 = 0;
  uStack_53 = 0;
  uStack_52 = 0;
  uStack_51 = 0;
  uStack_50 = 0;
  uStack_4f = 0;
  uStack_4e = 0;
  uStack_4d = 0;
  uStack_4c = 0;
  uStack_4b = 0;
  uStack_4a = 0;
  uStack_49 = 0;
  bStack_60 = 0x14;
  uStack_5f = (undefined2)_UNK_0282db7f;
  uStack_5d = (undefined1)((ulong)_UNK_0282db7f >> 0x10);
  uStack_5c = (undefined1)((ulong)_UNK_0282db7f >> 0x18);
  uStack_5b = (undefined1)((ulong)_UNK_0282db7f >> 0x20);
  uStack_5a = (undefined1)((ulong)_UNK_0282db7f >> 0x28);
  uStack_59 = (undefined1)((ulong)_UNK_0282db7f >> 0x30);
  uStack_58 = (undefined1)((ulong)_UNK_0282db7f >> 0x38);
  uStack_57 = 99;
  uStack_56 = 0x6b;
  uStack_55 = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0xb30,(ulong)&bStack_60 | 1);
  *(undefined1 *)(param_1 + 0xb28) = 1;
  *(undefined4 *)(param_1 + 0xb40) = 0;
  if ((bStack_60 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(CONCAT17(uStack_49,
                             CONCAT16(uStack_4a,
                                      CONCAT15(uStack_4b,
                                               CONCAT14(uStack_4c,
                                                        CONCAT13(uStack_4d,
                                                                 CONCAT12(uStack_4e,
                                                                          CONCAT11(uStack_4f,
                                                                                   uStack_50))))))))
    ;
  }
  lVar2 = param_1 + 0xb18;
  bStack_60 = (byte)lVar2;
  uStack_5f = (undefined2)((ulong)lVar2 >> 8);
  uStack_5d = (undefined1)((ulong)lVar2 >> 0x18);
  uStack_5c = (undefined1)((ulong)lVar2 >> 0x20);
  uStack_5b = (undefined1)((ulong)lVar2 >> 0x28);
  uStack_5a = (undefined1)((ulong)lVar2 >> 0x30);
  uStack_59 = (undefined1)((ulong)lVar2 >> 0x38);
  uVar23 = (**(code **)(*(long *)(param_1 + 0xb18) + 0x10))();
  plStack_78 = (long *)CONCAT44(plStack_78._4_4_,uVar23);
  std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, unsigned int, IParameterProperty*&>(unsigned int const&, unsigned int&&, IParameterProperty*&)(lVar1,&plStack_78,&plStack_78,&bStack_60);
  uStack_4e = 0;
  uStack_4d = 0;
  uStack_4c = 0;
  uStack_4b = 0;
  uStack_4a = 0;
  uStack_49 = 0;
  bStack_60 = 0x20;
  uStack_57 = (undefined1)_UNK_0282db99;
  uStack_56 = (undefined1)((uint)_UNK_0282db99 >> 8);
  uStack_55 = (undefined1)((uint)_UNK_0282db99 >> 0x10);
  uStack_54 = (undefined1)((uint)_UNK_0282db99 >> 0x18);
  uStack_53 = (undefined1)_UNK_0282db9d;
  uStack_52 = (undefined1)((uint)_UNK_0282db9d >> 8);
  uStack_51 = (undefined1)((uint)_UNK_0282db9d >> 0x10);
  uStack_50 = (undefined1)((uint)_UNK_0282db9d >> 0x18);
  uStack_5f = (undefined2)_UNK_0282db91;
  uStack_5d = (undefined1)((uint)_UNK_0282db91 >> 0x10);
  uStack_5c = (undefined1)((uint)_UNK_0282db91 >> 0x18);
  uStack_5b = (undefined1)_UNK_0282db95;
  uStack_5a = (undefined1)((uint)_UNK_0282db95 >> 8);
  uStack_59 = (undefined1)((uint)_UNK_0282db95 >> 0x10);
  uStack_58 = (undefined1)((uint)_UNK_0282db95 >> 0x18);
  uStack_4f = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0xb60,(ulong)&bStack_60 | 1);
  *(undefined1 *)(param_1 + 0xb58) = 1;
  *(undefined4 *)(param_1 + 0xb70) = 0;
  if ((bStack_60 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(CONCAT17(uStack_49,
                             CONCAT16(uStack_4a,
                                      CONCAT15(uStack_4b,
                                               CONCAT14(uStack_4c,
                                                        CONCAT13(uStack_4d,
                                                                 CONCAT12(uStack_4e,
                                                                          CONCAT11(uStack_4f,
                                                                                   uStack_50))))))))
    ;
  }
  lVar2 = param_1 + 0xb48;
  bStack_60 = (byte)lVar2;
  uStack_5f = (undefined2)((ulong)lVar2 >> 8);
  uStack_5d = (undefined1)((ulong)lVar2 >> 0x18);
  uStack_5c = (undefined1)((ulong)lVar2 >> 0x20);
  uStack_5b = (undefined1)((ulong)lVar2 >> 0x28);
  uStack_5a = (undefined1)((ulong)lVar2 >> 0x30);
  uStack_59 = (undefined1)((ulong)lVar2 >> 0x38);
  uVar23 = (**(code **)(*(long *)(param_1 + 0xb48) + 0x10))();
  plStack_78 = (long *)CONCAT44(plStack_78._4_4_,uVar23);
  std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, unsigned int, IParameterProperty*&>(unsigned int const&, unsigned int&&, IParameterProperty*&)(lVar1,&plStack_78,&plStack_78,&bStack_60);
  uStack_53 = 0;
  uStack_52 = 0;
  uStack_51 = 0;
  uStack_50 = 0;
  uStack_4f = 0;
  uStack_4e = 0;
  uStack_4d = 0;
  uStack_4c = 0;
  uStack_4b = 0;
  uStack_4a = 0;
  uStack_49 = 0;
  bStack_60 = 0x16;
  uStack_5f = (undefined2)_UNK_0282dba9;
  uStack_5d = (undefined1)((ulong)_UNK_0282dba9 >> 0x10);
  uStack_5c = (undefined1)((ulong)_UNK_0282dba9 >> 0x18);
  uStack_5b = (undefined1)((ulong)_UNK_0282dba9 >> 0x20);
  uStack_5a = (undefined1)((ulong)_UNK_0282dba9 >> 0x28);
  uStack_59 = (undefined1)((ulong)_UNK_0282dba9 >> 0x30);
  uStack_58 = (undefined1)((ulong)_UNK_0282dba9 >> 0x38);
  uStack_57 = 0x6e;
  uStack_56 = 99;
  uStack_55 = 0x65;
  uStack_54 = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0xb90,(ulong)&bStack_60 | 1);
  *(undefined1 *)(param_1 + 0xb88) = 1;
  *(undefined4 *)(param_1 + 0xba0) = 0;
  if ((bStack_60 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(CONCAT17(uStack_49,
                             CONCAT16(uStack_4a,
                                      CONCAT15(uStack_4b,
                                               CONCAT14(uStack_4c,
                                                        CONCAT13(uStack_4d,
                                                                 CONCAT12(uStack_4e,
                                                                          CONCAT11(uStack_4f,
                                                                                   uStack_50))))))))
    ;
  }
  lVar2 = param_1 + 0xb78;
  bStack_60 = (byte)lVar2;
  uStack_5f = (undefined2)((ulong)lVar2 >> 8);
  uStack_5d = (undefined1)((ulong)lVar2 >> 0x18);
  uStack_5c = (undefined1)((ulong)lVar2 >> 0x20);
  uStack_5b = (undefined1)((ulong)lVar2 >> 0x28);
  uStack_5a = (undefined1)((ulong)lVar2 >> 0x30);
  uStack_59 = (undefined1)((ulong)lVar2 >> 0x38);
  uVar23 = (**(code **)(*(long *)(param_1 + 0xb78) + 0x10))();
  plStack_78 = (long *)CONCAT44(plStack_78._4_4_,uVar23);
  std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, unsigned int, IParameterProperty*&>(unsigned int const&, unsigned int&&, IParameterProperty*&)(lVar1,&plStack_78,&plStack_78,&bStack_60);
  uStack_57 = 0;
  uStack_56 = 0;
  uStack_55 = 0;
  uStack_54 = 0;
  uStack_53 = 0;
  uStack_52 = 0;
  uStack_51 = 0;
  uStack_50 = 0;
  uStack_4f = 0;
  uStack_4e = 0;
  uStack_4d = 0;
  uStack_4c = 0;
  uStack_4b = 0;
  uStack_4a = 0;
  uStack_49 = 0;
  bStack_60 = 0xe;
  uStack_59 = 0x74;
  uStack_5b = 0x68;
  uStack_5a = 0x69;
  uStack_5f = 0x6461;
  uStack_5d = 100;
  uStack_5c = 0x5f;
  uStack_58 = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0xbc0,(ulong)&bStack_60 | 1);
  *(undefined1 *)(param_1 + 3000) = 1;
  *(undefined4 *)(param_1 + 0xbd0) = 0;
  if ((bStack_60 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(CONCAT17(uStack_49,
                             CONCAT16(uStack_4a,
                                      CONCAT15(uStack_4b,
                                               CONCAT14(uStack_4c,
                                                        CONCAT13(uStack_4d,
                                                                 CONCAT12(uStack_4e,
                                                                          CONCAT11(uStack_4f,
                                                                                   uStack_50))))))))
    ;
  }
  lVar2 = param_1 + 0xba8;
  bStack_60 = (byte)lVar2;
  uStack_5f = (undefined2)((ulong)lVar2 >> 8);
  uStack_5d = (undefined1)((ulong)lVar2 >> 0x18);
  uStack_5c = (undefined1)((ulong)lVar2 >> 0x20);
  uStack_5b = (undefined1)((ulong)lVar2 >> 0x28);
  uStack_5a = (undefined1)((ulong)lVar2 >> 0x30);
  uStack_59 = (undefined1)((ulong)lVar2 >> 0x38);
  uVar23 = (**(code **)(*(long *)(param_1 + 0xba8) + 0x10))();
  plStack_78 = (long *)CONCAT44(plStack_78._4_4_,uVar23);
  std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, unsigned int, IParameterProperty*&>(unsigned int const&, unsigned int&&, IParameterProperty*&)(lVar1,&plStack_78,&plStack_78,&bStack_60);
  uStack_55 = 0;
  uStack_54 = 0;
  uStack_53 = 0;
  uStack_52 = 0;
  uStack_51 = 0;
  uStack_50 = 0;
  uStack_4f = 0;
  uStack_4e = 0;
  uStack_4d = 0;
  uStack_4c = 0;
  uStack_4b = 0;
  uStack_4a = 0;
  uStack_49 = 0;
  bStack_60 = 0x12;
  uStack_5f = (undefined2)_UNK_0282dbcb;
  uStack_5d = (undefined1)((ulong)_UNK_0282dbcb >> 0x10);
  uStack_5c = (undefined1)((ulong)_UNK_0282dbcb >> 0x18);
  uStack_5b = (undefined1)((ulong)_UNK_0282dbcb >> 0x20);
  uStack_5a = (undefined1)((ulong)_UNK_0282dbcb >> 0x28);
  uStack_59 = (undefined1)((ulong)_UNK_0282dbcb >> 0x30);
  uStack_58 = (undefined1)((ulong)_UNK_0282dbcb >> 0x38);
  uStack_57 = 100;
  uStack_56 = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0xbf0,(ulong)&bStack_60 | 1);
  *(undefined1 *)(param_1 + 0xbe8) = 1;
  *(undefined4 *)(param_1 + 0xc00) = 0;
  if ((bStack_60 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(CONCAT17(uStack_49,
                             CONCAT16(uStack_4a,
                                      CONCAT15(uStack_4b,
                                               CONCAT14(uStack_4c,
                                                        CONCAT13(uStack_4d,
                                                                 CONCAT12(uStack_4e,
                                                                          CONCAT11(uStack_4f,
                                                                                   uStack_50))))))))
    ;
  }
  lVar2 = param_1 + 0xbd8;
  bStack_60 = (byte)lVar2;
  uStack_5f = (undefined2)((ulong)lVar2 >> 8);
  uStack_5d = (undefined1)((ulong)lVar2 >> 0x18);
  uStack_5c = (undefined1)((ulong)lVar2 >> 0x20);
  uStack_5b = (undefined1)((ulong)lVar2 >> 0x28);
  uStack_5a = (undefined1)((ulong)lVar2 >> 0x30);
  uStack_59 = (undefined1)((ulong)lVar2 >> 0x38);
  uVar23 = (**(code **)(*(long *)(param_1 + 0xbd8) + 0x10))();
  plStack_78 = (long *)CONCAT44(plStack_78._4_4_,uVar23);
  std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, unsigned int, IParameterProperty*&>(unsigned int const&, unsigned int&&, IParameterProperty*&)(lVar1,&plStack_78,&plStack_78,&bStack_60);
  uStack_58 = 0;
  uStack_57 = 0;
  uStack_56 = 0;
  uStack_55 = 0;
  uStack_54 = 0;
  uStack_53 = 0;
  uStack_52 = 0;
  uStack_51 = 0;
  uStack_50 = 0;
  uStack_4f = 0;
  uStack_4e = 0;
  uStack_4d = 0;
  uStack_4c = 0;
  uStack_4b = 0;
  uStack_4a = 0;
  uStack_49 = 0;
  bStack_60 = 0xc;
  uStack_5b = 0x61;
  uStack_5a = 0x70;
  uStack_5f = 0x6461;
  uStack_5d = 100;
  uStack_5c = 0x5f;
  uStack_59 = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0xc20,(ulong)&bStack_60 | 1);
  *(undefined1 *)(param_1 + 0xc18) = 1;
  *(undefined4 *)(param_1 + 0xc30) = 0;
  if ((bStack_60 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(CONCAT17(uStack_49,
                             CONCAT16(uStack_4a,
                                      CONCAT15(uStack_4b,
                                               CONCAT14(uStack_4c,
                                                        CONCAT13(uStack_4d,
                                                                 CONCAT12(uStack_4e,
                                                                          CONCAT11(uStack_4f,
                                                                                   uStack_50))))))))
    ;
  }
  lVar2 = param_1 + 0xc08;
  bStack_60 = (byte)lVar2;
  uStack_5f = (undefined2)((ulong)lVar2 >> 8);
  uStack_5d = (undefined1)((ulong)lVar2 >> 0x18);
  uStack_5c = (undefined1)((ulong)lVar2 >> 0x20);
  uStack_5b = (undefined1)((ulong)lVar2 >> 0x28);
  uStack_5a = (undefined1)((ulong)lVar2 >> 0x30);
  uStack_59 = (undefined1)((ulong)lVar2 >> 0x38);
  uVar23 = (**(code **)(*(long *)(param_1 + 0xc08) + 0x10))();
  plStack_78 = (long *)CONCAT44(plStack_78._4_4_,uVar23);
  std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, unsigned int, IParameterProperty*&>(unsigned int const&, unsigned int&&, IParameterProperty*&)(lVar1,&plStack_78,&plStack_78,&bStack_60);
  uStack_4f = 0;
  uStack_4e = 0;
  uStack_4d = 0;
  uStack_4c = 0;
  uStack_4b = 0;
  uStack_4a = 0;
  uStack_49 = 0;
  bStack_60 = 0x1e;
  uStack_5f = (undefined2)_UNK_027fb376;
  uStack_5d = (undefined1)((uint7)_UNK_027fb376 >> 0x10);
  uStack_5c = (undefined1)((uint7)_UNK_027fb376 >> 0x18);
  uStack_5b = (undefined1)((uint7)_UNK_027fb376 >> 0x20);
  uStack_5a = (undefined1)((uint7)_UNK_027fb376 >> 0x28);
  uStack_59 = (undefined1)((uint7)_UNK_027fb376 >> 0x30);
  uStack_58 = UNK_027fb37d;
  uStack_57 = (undefined1)_UNK_027fb37e;
  uStack_56 = (undefined1)((uint7)_UNK_027fb37e >> 8);
  uStack_55 = (undefined1)((uint7)_UNK_027fb37e >> 0x10);
  uStack_54 = (undefined1)((uint7)_UNK_027fb37e >> 0x18);
  uStack_53 = (undefined1)((uint7)_UNK_027fb37e >> 0x20);
  uStack_52 = (undefined1)((uint7)_UNK_027fb37e >> 0x28);
  uStack_51 = (undefined1)((uint7)_UNK_027fb37e >> 0x30);
  uStack_50 = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0xc50,(ulong)&bStack_60 | 1);
  *(undefined1 *)(param_1 + 0xc48) = 1;
  *(undefined4 *)(param_1 + 0xc60) = 0;
  if ((bStack_60 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(CONCAT17(uStack_49,
                             CONCAT16(uStack_4a,
                                      CONCAT15(uStack_4b,
                                               CONCAT14(uStack_4c,
                                                        CONCAT13(uStack_4d,
                                                                 CONCAT12(uStack_4e,
                                                                          CONCAT11(uStack_4f,
                                                                                   uStack_50))))))))
    ;
  }
  lVar2 = param_1 + 0xc38;
  bStack_60 = (byte)lVar2;
  uStack_5f = (undefined2)((ulong)lVar2 >> 8);
  uStack_5d = (undefined1)((ulong)lVar2 >> 0x18);
  uStack_5c = (undefined1)((ulong)lVar2 >> 0x20);
  uStack_5b = (undefined1)((ulong)lVar2 >> 0x28);
  uStack_5a = (undefined1)((ulong)lVar2 >> 0x30);
  uStack_59 = (undefined1)((ulong)lVar2 >> 0x38);
  uVar23 = (**(code **)(*(long *)(param_1 + 0xc38) + 0x10))();
  plStack_78 = (long *)CONCAT44(plStack_78._4_4_,uVar23);
  std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, unsigned int, IParameterProperty*&>(unsigned int const&, unsigned int&&, IParameterProperty*&)(lVar1,&plStack_78,&plStack_78,&bStack_60);
  uStack_52 = 0;
  uStack_51 = 0;
  uStack_50 = 0;
  uStack_4f = 0;
  uStack_4e = 0;
  uStack_4d = 0;
  uStack_4c = 0;
  uStack_4b = 0;
  uStack_4a = 0;
  uStack_49 = 0;
  bStack_60 = 0x18;
  uStack_5f = (undefined2)_UNK_027fb386;
  uStack_5d = (undefined1)((ulong)_UNK_027fb386 >> 0x10);
  uStack_5c = (undefined1)((ulong)_UNK_027fb386 >> 0x18);
  uStack_5b = (undefined1)((ulong)_UNK_027fb386 >> 0x20);
  uStack_5a = (undefined1)((ulong)_UNK_027fb386 >> 0x28);
  uStack_59 = (undefined1)((ulong)_UNK_027fb386 >> 0x30);
  uStack_58 = (undefined1)((ulong)_UNK_027fb386 >> 0x38);
  uStack_57 = 0x65;
  uStack_56 = 0x76;
  uStack_55 = 0x65;
  uStack_54 = 0x6c;
  uStack_53 = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0xc80,(ulong)&bStack_60 | 1);
  *(undefined1 *)(param_1 + 0xc78) = 1;
  *(undefined4 *)(param_1 + 0xc90) = 0;
  if ((bStack_60 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(CONCAT17(uStack_49,
                             CONCAT16(uStack_4a,
                                      CONCAT15(uStack_4b,
                                               CONCAT14(uStack_4c,
                                                        CONCAT13(uStack_4d,
                                                                 CONCAT12(uStack_4e,
                                                                          CONCAT11(uStack_4f,
                                                                                   uStack_50))))))))
    ;
  }
  lVar2 = param_1 + 0xc68;
  bStack_60 = (byte)lVar2;
  uStack_5f = (undefined2)((ulong)lVar2 >> 8);
  uStack_5d = (undefined1)((ulong)lVar2 >> 0x18);
  uStack_5c = (undefined1)((ulong)lVar2 >> 0x20);
  uStack_5b = (undefined1)((ulong)lVar2 >> 0x28);
  uStack_5a = (undefined1)((ulong)lVar2 >> 0x30);
  uStack_59 = (undefined1)((ulong)lVar2 >> 0x38);
  uVar23 = (**(code **)(*(long *)(param_1 + 0xc68) + 0x10))();
  plStack_78 = (long *)CONCAT44(plStack_78._4_4_,uVar23);
  std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, unsigned int, IParameterProperty*&>(unsigned int const&, unsigned int&&, IParameterProperty*&)(lVar1,&plStack_78,&plStack_78,&bStack_60);
  uStack_50 = 0;
  uStack_4f = 0;
  uStack_4e = 0;
  uStack_4d = 0;
  uStack_4c = 0;
  uStack_4b = 0;
  uStack_4a = 0;
  uStack_49 = 0;
  bStack_60 = 0x1c;
  uStack_5f = (undefined2)_UNK_027dc6d8;
  uStack_5d = (undefined1)((uint6)_UNK_027dc6d8 >> 0x10);
  uStack_5c = (undefined1)((uint6)_UNK_027dc6d8 >> 0x18);
  uStack_5b = (undefined1)((uint6)_UNK_027dc6d8 >> 0x20);
  uStack_5a = (undefined1)((uint6)_UNK_027dc6d8 >> 0x28);
  uStack_59 = (undefined1)_UNK_027dc6de;
  uStack_58 = (undefined1)((ushort)_UNK_027dc6de >> 8);
  uStack_57 = (undefined1)_UNK_027dc6e0;
  uStack_56 = (undefined1)((uint6)_UNK_027dc6e0 >> 8);
  uStack_55 = (undefined1)((uint6)_UNK_027dc6e0 >> 0x10);
  uStack_54 = (undefined1)((uint6)_UNK_027dc6e0 >> 0x18);
  uStack_53 = (undefined1)((uint6)_UNK_027dc6e0 >> 0x20);
  uStack_52 = (undefined1)((uint6)_UNK_027dc6e0 >> 0x28);
  uStack_51 = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0xcb0,(ulong)&bStack_60 | 1);
  *(undefined1 *)(param_1 + 0xca8) = 1;
  *(undefined4 *)(param_1 + 0xcc0) = 0;
  if ((bStack_60 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(CONCAT17(uStack_49,
                             CONCAT16(uStack_4a,
                                      CONCAT15(uStack_4b,
                                               CONCAT14(uStack_4c,
                                                        CONCAT13(uStack_4d,
                                                                 CONCAT12(uStack_4e,
                                                                          CONCAT11(uStack_4f,
                                                                                   uStack_50))))))))
    ;
  }
  lVar2 = param_1 + 0xc98;
  bStack_60 = (byte)lVar2;
  uStack_5f = (undefined2)((ulong)lVar2 >> 8);
  uStack_5d = (undefined1)((ulong)lVar2 >> 0x18);
  uStack_5c = (undefined1)((ulong)lVar2 >> 0x20);
  uStack_5b = (undefined1)((ulong)lVar2 >> 0x28);
  uStack_5a = (undefined1)((ulong)lVar2 >> 0x30);
  uStack_59 = (undefined1)((ulong)lVar2 >> 0x38);
  uVar23 = (**(code **)(*(long *)(param_1 + 0xc98) + 0x10))();
  plStack_78 = (long *)CONCAT44(plStack_78._4_4_,uVar23);
  std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, unsigned int, IParameterProperty*&>(unsigned int const&, unsigned int&&, IParameterProperty*&)(lVar1,&plStack_78,&plStack_78,&bStack_60);
  uStack_50 = 0;
  uStack_4f = 0;
  uStack_4e = 0;
  uStack_4d = 0;
  uStack_4c = 0;
  uStack_4b = 0;
  uStack_4a = 0;
  uStack_49 = 0;
  bStack_60 = 0x1c;
  uStack_5f = (undefined2)_UNK_027dc6e7;
  uStack_5d = (undefined1)((uint6)_UNK_027dc6e7 >> 0x10);
  uStack_5c = (undefined1)((uint6)_UNK_027dc6e7 >> 0x18);
  uStack_5b = (undefined1)((uint6)_UNK_027dc6e7 >> 0x20);
  uStack_5a = (undefined1)((uint6)_UNK_027dc6e7 >> 0x28);
  uStack_59 = (undefined1)_UNK_027dc6ed;
  uStack_58 = (undefined1)((ushort)_UNK_027dc6ed >> 8);
  uStack_57 = (undefined1)_UNK_027dc6ef;
  uStack_56 = (undefined1)((uint6)_UNK_027dc6ef >> 8);
  uStack_55 = (undefined1)((uint6)_UNK_027dc6ef >> 0x10);
  uStack_54 = (undefined1)((uint6)_UNK_027dc6ef >> 0x18);
  uStack_53 = (undefined1)((uint6)_UNK_027dc6ef >> 0x20);
  uStack_52 = (undefined1)((uint6)_UNK_027dc6ef >> 0x28);
  uStack_51 = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0xce0,(ulong)&bStack_60 | 1);
  *(undefined1 *)(param_1 + 0xcd8) = 1;
  *(undefined4 *)(param_1 + 0xcf0) = 0;
  if ((bStack_60 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(CONCAT17(uStack_49,
                             CONCAT16(uStack_4a,
                                      CONCAT15(uStack_4b,
                                               CONCAT14(uStack_4c,
                                                        CONCAT13(uStack_4d,
                                                                 CONCAT12(uStack_4e,
                                                                          CONCAT11(uStack_4f,
                                                                                   uStack_50))))))))
    ;
  }
  lVar2 = param_1 + 0xcc8;
  bStack_60 = (byte)lVar2;
  uStack_5f = (undefined2)((ulong)lVar2 >> 8);
  uStack_5d = (undefined1)((ulong)lVar2 >> 0x18);
  uStack_5c = (undefined1)((ulong)lVar2 >> 0x20);
  uStack_5b = (undefined1)((ulong)lVar2 >> 0x28);
  uStack_5a = (undefined1)((ulong)lVar2 >> 0x30);
  uStack_59 = (undefined1)((ulong)lVar2 >> 0x38);
  uVar23 = (**(code **)(*(long *)(param_1 + 0xcc8) + 0x10))();
  plStack_78 = (long *)CONCAT44(plStack_78._4_4_,uVar23);
  std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, unsigned int, IParameterProperty*&>(unsigned int const&, unsigned int&&, IParameterProperty*&)(lVar1,&plStack_78,&plStack_78,&bStack_60);
  uStack_58 = 0;
  uStack_57 = 0;
  uStack_56 = 0;
  uStack_55 = 0;
  uStack_54 = 0;
  uStack_53 = 0;
  uStack_52 = 0;
  uStack_51 = 0;
  uStack_50 = 0;
  uStack_4f = 0;
  uStack_4e = 0;
  uStack_4d = 0;
  uStack_4c = 0;
  uStack_4b = 0;
  uStack_4a = 0;
  uStack_49 = 0;
  bStack_60 = 0;
  uStack_5f = 0;
  uStack_5d = 0;
  uStack_5c = 0;
  uStack_5b = 0;
  uStack_5a = 0;
  uStack_59 = 0;
  puVar24 = (undefined8 *)Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(0x20,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
  if (puVar24 == (undefined8 *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
  }
  uVar5 = _UNK_027fb393;
  uVar3 = _UNK_027dbb60;
  uVar25 = CONCAT17(UNK_027fb3a2,_UNK_027fb39b);
  uStack_50 = SUB81(puVar24,0);
  uStack_4f = (undefined1)((ulong)puVar24 >> 8);
  uStack_4e = (undefined1)((ulong)puVar24 >> 0x10);
  uStack_4d = (undefined1)((ulong)puVar24 >> 0x18);
  uStack_4c = (undefined1)((ulong)puVar24 >> 0x20);
  uStack_4b = (undefined1)((ulong)puVar24 >> 0x28);
  uStack_4a = (undefined1)((ulong)puVar24 >> 0x30);
  uStack_49 = (undefined1)((ulong)puVar24 >> 0x38);
  uStack_58 = (undefined1)_UNK_027dbb68;
  uStack_57 = (undefined1)((ulong)_UNK_027dbb68 >> 8);
  uStack_56 = (undefined1)((ulong)_UNK_027dbb68 >> 0x10);
  uStack_55 = (undefined1)((ulong)_UNK_027dbb68 >> 0x18);
  uStack_54 = (undefined1)((ulong)_UNK_027dbb68 >> 0x20);
  uStack_53 = (undefined1)((ulong)_UNK_027dbb68 >> 0x28);
  uStack_52 = (undefined1)((ulong)_UNK_027dbb68 >> 0x30);
  uStack_51 = (undefined1)((ulong)_UNK_027dbb68 >> 0x38);
  bStack_60 = (byte)_UNK_027dbb60;
  uStack_5f = (undefined2)(_UNK_027dbb60 >> 8);
  uStack_5d = (undefined1)(_UNK_027dbb60 >> 0x18);
  uStack_5c = (undefined1)(_UNK_027dbb60 >> 0x20);
  uStack_5b = (undefined1)(_UNK_027dbb60 >> 0x28);
  uStack_5a = (undefined1)(_UNK_027dbb60 >> 0x30);
  uStack_59 = (undefined1)(_UNK_027dbb60 >> 0x38);
  *(ulong *)((long)puVar24 + 0xf) = CONCAT71(_UNK_027fb3a3,UNK_027fb3a2);
  puVar24[1] = uVar25;
  *puVar24 = uVar5;
  *(undefined1 *)((long)puVar24 + 0x17) = 0;
  puVar4 = (undefined8 *)((ulong)&bStack_60 | 1);
  if ((uVar3 & 1) != 0) {
    puVar4 = puVar24;
  }
  Framework::CHash32::operator=(char const*)(param_1 + 0xd10,puVar4);
  *(undefined1 *)(param_1 + 0xd08) = 1;
  *(undefined1 *)(param_1 + 0xd20) = 0;
  if ((bStack_60 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(CONCAT17(uStack_49,
                             CONCAT16(uStack_4a,
                                      CONCAT15(uStack_4b,
                                               CONCAT14(uStack_4c,
                                                        CONCAT13(uStack_4d,
                                                                 CONCAT12(uStack_4e,
                                                                          CONCAT11(uStack_4f,
                                                                                   uStack_50))))))))
    ;
  }
  lVar2 = param_1 + 0xcf8;
  bStack_60 = (byte)lVar2;
  uStack_5f = (undefined2)((ulong)lVar2 >> 8);
  uStack_5d = (undefined1)((ulong)lVar2 >> 0x18);
  uStack_5c = (undefined1)((ulong)lVar2 >> 0x20);
  uStack_5b = (undefined1)((ulong)lVar2 >> 0x28);
  uStack_5a = (undefined1)((ulong)lVar2 >> 0x30);
  uStack_59 = (undefined1)((ulong)lVar2 >> 0x38);
  uVar23 = (**(code **)(*(long *)(param_1 + 0xcf8) + 0x10))();
  plStack_78 = (long *)CONCAT44(plStack_78._4_4_,uVar23);
  std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, unsigned int, IParameterProperty*&>(unsigned int const&, unsigned int&&, IParameterProperty*&)(lVar1,&plStack_78,&plStack_78,&bStack_60);
  uStack_53 = 0;
  uStack_52 = 0;
  uStack_51 = 0;
  uStack_50 = 0;
  uStack_4f = 0;
  uStack_4e = 0;
  uStack_4d = 0;
  uStack_4c = 0;
  uStack_4b = 0;
  uStack_4a = 0;
  uStack_49 = 0;
  bStack_60 = 0x16;
  uStack_5f = (undefined2)_UNK_0280c826;
  uStack_5d = (undefined1)((ulong)_UNK_0280c826 >> 0x10);
  uStack_5c = (undefined1)((ulong)_UNK_0280c826 >> 0x18);
  uStack_5b = (undefined1)((ulong)_UNK_0280c826 >> 0x20);
  uStack_5a = (undefined1)((ulong)_UNK_0280c826 >> 0x28);
  uStack_59 = (undefined1)((ulong)_UNK_0280c826 >> 0x30);
  uStack_58 = (undefined1)((ulong)_UNK_0280c826 >> 0x38);
  uStack_57 = 0x76;
  uStack_56 = 0x65;
  uStack_55 = 0x6c;
  uStack_54 = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0xd40,(ulong)&bStack_60 | 1);
  *(undefined1 *)(param_1 + 0xd38) = 1;
  *(undefined4 *)(param_1 + 0xd50) = 0;
  if ((bStack_60 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(CONCAT17(uStack_49,
                             CONCAT16(uStack_4a,
                                      CONCAT15(uStack_4b,
                                               CONCAT14(uStack_4c,
                                                        CONCAT13(uStack_4d,
                                                                 CONCAT12(uStack_4e,
                                                                          CONCAT11(uStack_4f,
                                                                                   uStack_50))))))))
    ;
  }
  lVar2 = param_1 + 0xd28;
  bStack_60 = (byte)lVar2;
  uStack_5f = (undefined2)((ulong)lVar2 >> 8);
  uStack_5d = (undefined1)((ulong)lVar2 >> 0x18);
  uStack_5c = (undefined1)((ulong)lVar2 >> 0x20);
  uStack_5b = (undefined1)((ulong)lVar2 >> 0x28);
  uStack_5a = (undefined1)((ulong)lVar2 >> 0x30);
  uStack_59 = (undefined1)((ulong)lVar2 >> 0x38);
  uVar23 = (**(code **)(*(long *)(param_1 + 0xd28) + 0x10))();
  plStack_78 = (long *)CONCAT44(plStack_78._4_4_,uVar23);
  std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, unsigned int, IParameterProperty*&>(unsigned int const&, unsigned int&&, IParameterProperty*&)(lVar1,&plStack_78,&plStack_78,&bStack_60);
  uStack_49 = 0;
  bStack_60 = 0x2a;
  uStack_57 = (undefined1)_UNK_027fb3b3;
  uStack_56 = (undefined1)((uint5)_UNK_027fb3b3 >> 8);
  uStack_55 = (undefined1)((uint5)_UNK_027fb3b3 >> 0x10);
  uStack_54 = (undefined1)((uint5)_UNK_027fb3b3 >> 0x18);
  uStack_53 = (undefined1)((uint5)_UNK_027fb3b3 >> 0x20);
  uStack_5f = (undefined2)_UNK_027fb3ab;
  uStack_5d = (undefined1)((ulong)_UNK_027fb3ab >> 0x10);
  uStack_5c = (undefined1)((ulong)_UNK_027fb3ab >> 0x18);
  uStack_5b = (undefined1)((ulong)_UNK_027fb3ab >> 0x20);
  uStack_5a = (undefined1)((ulong)_UNK_027fb3ab >> 0x28);
  uStack_59 = (undefined1)((ulong)_UNK_027fb3ab >> 0x30);
  uStack_58 = (undefined1)((ulong)_UNK_027fb3ab >> 0x38);
  uStack_52 = (undefined1)_UNK_027fb3b8;
  uStack_51 = (undefined1)((uint3)_UNK_027fb3b8 >> 8);
  uStack_50 = (undefined1)((uint3)_UNK_027fb3b8 >> 0x10);
  uStack_4f = (undefined1)_UNK_027fb3bb;
  uStack_4e = (undefined1)((uint5)_UNK_027fb3bb >> 8);
  uStack_4d = (undefined1)((uint5)_UNK_027fb3bb >> 0x10);
  uStack_4c = (undefined1)((uint5)_UNK_027fb3bb >> 0x18);
  uStack_4b = (undefined1)((uint5)_UNK_027fb3bb >> 0x20);
  uStack_4a = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0xd70,(ulong)&bStack_60 | 1);
  *(undefined1 *)(param_1 + 0xd68) = 1;
  *(undefined4 *)(param_1 + 0xd80) = 0;
  if ((bStack_60 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(CONCAT17(uStack_49,
                             CONCAT16(uStack_4a,
                                      CONCAT15(uStack_4b,
                                               CONCAT14(uStack_4c,
                                                        CONCAT13(uStack_4d,
                                                                 CONCAT12(uStack_4e,
                                                                          CONCAT11(uStack_4f,
                                                                                   uStack_50))))))))
    ;
  }
  lVar2 = param_1 + 0xd58;
  bStack_60 = (byte)lVar2;
  uStack_5f = (undefined2)((ulong)lVar2 >> 8);
  uStack_5d = (undefined1)((ulong)lVar2 >> 0x18);
  uStack_5c = (undefined1)((ulong)lVar2 >> 0x20);
  uStack_5b = (undefined1)((ulong)lVar2 >> 0x28);
  uStack_5a = (undefined1)((ulong)lVar2 >> 0x30);
  uStack_59 = (undefined1)((ulong)lVar2 >> 0x38);
  uVar23 = (**(code **)(*(long *)(param_1 + 0xd58) + 0x10))();
  plStack_78 = (long *)CONCAT44(plStack_78._4_4_,uVar23);
  std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, unsigned int, IParameterProperty*&>(unsigned int const&, unsigned int&&, IParameterProperty*&)(lVar1,&plStack_78,&plStack_78,&bStack_60);
  uStack_4d = 0;
  uStack_4c = 0;
  uStack_4b = 0;
  uStack_4a = 0;
  uStack_49 = 0;
  bStack_60 = 0x22;
  uStack_57 = (undefined1)_UNK_0282ea69;
  uStack_56 = (undefined1)((ulong)_UNK_0282ea69 >> 8);
  uStack_55 = (undefined1)((ulong)_UNK_0282ea69 >> 0x10);
  uStack_54 = (undefined1)((ulong)_UNK_0282ea69 >> 0x18);
  uStack_53 = (undefined1)((ulong)_UNK_0282ea69 >> 0x20);
  uStack_52 = (undefined1)((ulong)_UNK_0282ea69 >> 0x28);
  uStack_51 = (undefined1)((ulong)_UNK_0282ea69 >> 0x30);
  uStack_50 = (undefined1)((ulong)_UNK_0282ea69 >> 0x38);
  uStack_5f = (undefined2)_UNK_0282ea61;
  uStack_5d = (undefined1)((ulong)_UNK_0282ea61 >> 0x10);
  uStack_5c = (undefined1)((ulong)_UNK_0282ea61 >> 0x18);
  uStack_5b = (undefined1)((ulong)_UNK_0282ea61 >> 0x20);
  uStack_5a = (undefined1)((ulong)_UNK_0282ea61 >> 0x28);
  uStack_59 = (undefined1)((ulong)_UNK_0282ea61 >> 0x30);
  uStack_58 = (undefined1)((ulong)_UNK_0282ea61 >> 0x38);
  uStack_4f = 100;
  uStack_4e = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0xda0,(ulong)&bStack_60 | 1);
  *(undefined1 *)(param_1 + 0xd98) = 1;
  *(undefined4 *)(param_1 + 0xdb0) = 0;
  if ((bStack_60 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(CONCAT17(uStack_49,
                             CONCAT16(uStack_4a,
                                      CONCAT15(uStack_4b,
                                               CONCAT14(uStack_4c,
                                                        CONCAT13(uStack_4d,
                                                                 CONCAT12(uStack_4e,
                                                                          CONCAT11(uStack_4f,
                                                                                   uStack_50))))))))
    ;
  }
  lVar2 = param_1 + 0xd88;
  bStack_60 = (byte)lVar2;
  uStack_5f = (undefined2)((ulong)lVar2 >> 8);
  uStack_5d = (undefined1)((ulong)lVar2 >> 0x18);
  uStack_5c = (undefined1)((ulong)lVar2 >> 0x20);
  uStack_5b = (undefined1)((ulong)lVar2 >> 0x28);
  uStack_5a = (undefined1)((ulong)lVar2 >> 0x30);
  uStack_59 = (undefined1)((ulong)lVar2 >> 0x38);
  uVar23 = (**(code **)(*(long *)(param_1 + 0xd88) + 0x10))();
  plStack_78 = (long *)CONCAT44(plStack_78._4_4_,uVar23);
  std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, unsigned int, IParameterProperty*&>(unsigned int const&, unsigned int&&, IParameterProperty*&)(lVar1,&plStack_78,&plStack_78,&bStack_60);
  uStack_57 = 0;
  uStack_56 = 0;
  uStack_55 = 0;
  uStack_54 = 0;
  uStack_53 = 0;
  uStack_52 = 0;
  uStack_51 = 0;
  uStack_50 = 0;
  uStack_4f = 0;
  uStack_4e = 0;
  uStack_4d = 0;
  uStack_4c = 0;
  uStack_4b = 0;
  uStack_4a = 0;
  uStack_49 = 0;
  bStack_60 = 0xe;
  uStack_59 = 100;
  uStack_5b = 0x5f;
  uStack_5a = 0x69;
  uStack_5f = 0x6168;
  uStack_5d = 0x69;
  uStack_5c = 0x72;
  uStack_58 = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0xdd0,(ulong)&bStack_60 | 1);
  *(undefined1 *)(param_1 + 0xdc8) = 1;
  *(undefined4 *)(param_1 + 0xde0) = 0;
  if ((bStack_60 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(CONCAT17(uStack_49,
                             CONCAT16(uStack_4a,
                                      CONCAT15(uStack_4b,
                                               CONCAT14(uStack_4c,
                                                        CONCAT13(uStack_4d,
                                                                 CONCAT12(uStack_4e,
                                                                          CONCAT11(uStack_4f,
                                                                                   uStack_50))))))))
    ;
  }
  lVar2 = param_1 + 0xdb8;
  bStack_60 = (byte)lVar2;
  uStack_5f = (undefined2)((ulong)lVar2 >> 8);
  uStack_5d = (undefined1)((ulong)lVar2 >> 0x18);
  uStack_5c = (undefined1)((ulong)lVar2 >> 0x20);
  uStack_5b = (undefined1)((ulong)lVar2 >> 0x28);
  uStack_5a = (undefined1)((ulong)lVar2 >> 0x30);
  uStack_59 = (undefined1)((ulong)lVar2 >> 0x38);
  uVar23 = (**(code **)(*(long *)(param_1 + 0xdb8) + 0x10))();
  plStack_78 = (long *)CONCAT44(plStack_78._4_4_,uVar23);
  std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, unsigned int, IParameterProperty*&>(unsigned int const&, unsigned int&&, IParameterProperty*&)(lVar1,&plStack_78,&plStack_78,&bStack_60);
  uStack_57 = 0;
  uStack_56 = 0;
  uStack_55 = 0;
  uStack_54 = 0;
  uStack_53 = 0;
  uStack_52 = 0;
  uStack_51 = 0;
  uStack_50 = 0;
  uStack_4f = 0;
  uStack_4e = 0;
  uStack_4d = 0;
  uStack_4c = 0;
  uStack_4b = 0;
  uStack_4a = 0;
  uStack_49 = 0;
  bStack_60 = 0xe;
  uStack_59 = 100;
  uStack_5b = 0x5f;
  uStack_5a = 0x69;
  uStack_5f = 0x6f70;
  uStack_5d = 0x73;
  uStack_5c = 0x65;
  uStack_58 = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0xe00,(ulong)&bStack_60 | 1);
  *(undefined1 *)(param_1 + 0xdf8) = 1;
  *(undefined4 *)(param_1 + 0xe10) = 0;
  if ((bStack_60 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(CONCAT17(uStack_49,
                             CONCAT16(uStack_4a,
                                      CONCAT15(uStack_4b,
                                               CONCAT14(uStack_4c,
                                                        CONCAT13(uStack_4d,
                                                                 CONCAT12(uStack_4e,
                                                                          CONCAT11(uStack_4f,
                                                                                   uStack_50))))))))
    ;
  }
  lVar2 = param_1 + 0xde8;
  bStack_60 = (byte)lVar2;
  uStack_5f = (undefined2)((ulong)lVar2 >> 8);
  uStack_5d = (undefined1)((ulong)lVar2 >> 0x18);
  uStack_5c = (undefined1)((ulong)lVar2 >> 0x20);
  uStack_5b = (undefined1)((ulong)lVar2 >> 0x28);
  uStack_5a = (undefined1)((ulong)lVar2 >> 0x30);
  uStack_59 = (undefined1)((ulong)lVar2 >> 0x38);
  uVar23 = (**(code **)(*(long *)(param_1 + 0xde8) + 0x10))();
  plStack_78 = (long *)CONCAT44(plStack_78._4_4_,uVar23);
  std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, unsigned int, IParameterProperty*&>(unsigned int const&, unsigned int&&, IParameterProperty*&)(lVar1,&plStack_78,&plStack_78,&bStack_60);
  uStack_53 = 0;
  uStack_52 = 0;
  uStack_51 = 0;
  uStack_50 = 0;
  uStack_4f = 0;
  uStack_4e = 0;
  uStack_4d = 0;
  uStack_4c = 0;
  uStack_4b = 0;
  uStack_4a = 0;
  uStack_49 = 0;
  bStack_60 = 0x16;
  uStack_5f = (undefined2)_UNK_027fb3d1;
  uStack_5d = (undefined1)((ulong)_UNK_027fb3d1 >> 0x10);
  uStack_5c = (undefined1)((ulong)_UNK_027fb3d1 >> 0x18);
  uStack_5b = (undefined1)((ulong)_UNK_027fb3d1 >> 0x20);
  uStack_5a = (undefined1)((ulong)_UNK_027fb3d1 >> 0x28);
  uStack_59 = (undefined1)((ulong)_UNK_027fb3d1 >> 0x30);
  uStack_58 = (undefined1)((ulong)_UNK_027fb3d1 >> 0x38);
  uStack_57 = 0x79;
  uStack_56 = 0x5f;
  uStack_55 = 0x37;
  uStack_54 = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0xe30,(ulong)&bStack_60 | 1);
  *(undefined1 *)(param_1 + 0xe28) = 1;
  *(undefined4 *)(param_1 + 0xe40) = 0;
  if ((bStack_60 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(CONCAT17(uStack_49,
                             CONCAT16(uStack_4a,
                                      CONCAT15(uStack_4b,
                                               CONCAT14(uStack_4c,
                                                        CONCAT13(uStack_4d,
                                                                 CONCAT12(uStack_4e,
                                                                          CONCAT11(uStack_4f,
                                                                                   uStack_50))))))))
    ;
  }
  lVar2 = param_1 + 0xe18;
  bStack_60 = (byte)lVar2;
  uStack_5f = (undefined2)((ulong)lVar2 >> 8);
  uStack_5d = (undefined1)((ulong)lVar2 >> 0x18);
  uStack_5c = (undefined1)((ulong)lVar2 >> 0x20);
  uStack_5b = (undefined1)((ulong)lVar2 >> 0x28);
  uStack_5a = (undefined1)((ulong)lVar2 >> 0x30);
  uStack_59 = (undefined1)((ulong)lVar2 >> 0x38);
  uVar23 = (**(code **)(*(long *)(param_1 + 0xe18) + 0x10))();
  plStack_78 = (long *)CONCAT44(plStack_78._4_4_,uVar23);
  std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, unsigned int, IParameterProperty*&>(unsigned int const&, unsigned int&&, IParameterProperty*&)(lVar1,&plStack_78,&plStack_78,&bStack_60);
  plStack_78 = (long *)(param_1 + 0xf10);
  uVar25 = (**(code **)(*(long *)(param_1 + 0xf10) + 0x18))();
  Framework::CHash32::CHash32(char const*)(&bStack_60,uVar25);
  lVar1 = param_1 + 0x20;
  std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_impl<Framework::CHash32, InfoBase*&>(Framework::CHash32&&, InfoBase*&)(lVar1,&bStack_60,&plStack_78);
  Framework::CHash32::~CHash32()(&bStack_60);
  (**(code **)(*plStack_78 + 0x10))();
  plStack_78 = (long *)(param_1 + 0xe48);
  uVar25 = (**(code **)(*(long *)(param_1 + 0xe48) + 0x18))();
  Framework::CHash32::CHash32(char const*)(&bStack_60,uVar25);
  std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_impl<Framework::CHash32, InfoBase*&>(Framework::CHash32&&, InfoBase*&)(lVar1,&bStack_60,&plStack_78);
  Framework::CHash32::~CHash32()(&bStack_60);
  (**(code **)(*plStack_78 + 0x10))();
  plStack_78 = (long *)(param_1 + 0xf60);
  uVar25 = (**(code **)(*(long *)(param_1 + 0xf60) + 0x18))();
  Framework::CHash32::CHash32(char const*)(&bStack_60,uVar25);
  std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_impl<Framework::CHash32, InfoBase*&>(Framework::CHash32&&, InfoBase*&)(lVar1,&bStack_60,&plStack_78);
  Framework::CHash32::~CHash32()(&bStack_60);
  (**(code **)(*plStack_78 + 0x10))();
  plStack_78 = (long *)(param_1 + 0xfb0);
  uVar25 = (**(code **)(*(long *)(param_1 + 0xfb0) + 0x18))();
  Framework::CHash32::CHash32(char const*)(&bStack_60,uVar25);
  std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_impl<Framework::CHash32, InfoBase*&>(Framework::CHash32&&, InfoBase*&)(lVar1,&bStack_60,&plStack_78);
  Framework::CHash32::~CHash32()(&bStack_60);
  (**(code **)(*plStack_78 + 0x10))();
  plStack_78 = (long *)(param_1 + 0x1000);
  uVar25 = (**(code **)(*(long *)(param_1 + 0x1000) + 0x18))();
  Framework::CHash32::CHash32(char const*)(&bStack_60,uVar25);
  std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_impl<Framework::CHash32, InfoBase*&>(Framework::CHash32&&, InfoBase*&)(lVar1,&bStack_60,&plStack_78);
  Framework::CHash32::~CHash32()(&bStack_60);
  (**(code **)(*plStack_78 + 0x10))();
  plStack_78 = (long *)(param_1 + 0x11e8);
  uVar25 = (**(code **)(*(long *)(param_1 + 0x11e8) + 0x18))();
  Framework::CHash32::CHash32(char const*)(&bStack_60,uVar25);
  std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_impl<Framework::CHash32, InfoBase*&>(Framework::CHash32&&, InfoBase*&)(lVar1,&bStack_60,&plStack_78);
  Framework::CHash32::~CHash32()(&bStack_60);
  (**(code **)(*plStack_78 + 0x10))();
  plStack_78 = (long *)(param_1 + 0x13d0);
  uVar25 = (**(code **)(*(long *)(param_1 + 0x13d0) + 0x18))();
  Framework::CHash32::CHash32(char const*)(&bStack_60,uVar25);
  std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_impl<Framework::CHash32, InfoBase*&>(Framework::CHash32&&, InfoBase*&)(lVar1,&bStack_60,&plStack_78);
  Framework::CHash32::~CHash32()(&bStack_60);
  (**(code **)(*plStack_78 + 0x10))();
  plStack_78 = (long *)(param_1 + 0x1498);
  uVar25 = (**(code **)(*(long *)(param_1 + 0x1498) + 0x18))();
  Framework::CHash32::CHash32(char const*)(&bStack_60,uVar25);
  std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_impl<Framework::CHash32, InfoBase*&>(Framework::CHash32&&, InfoBase*&)(lVar1,&bStack_60,&plStack_78);
  Framework::CHash32::~CHash32()(&bStack_60);
  (**(code **)(*plStack_78 + 0x10))();
  return;
}

// ==== CPersonStatusInfo::pParseName() const
// vaddr 0x12b0f10 | ghidra 0x13b0f10 | size 8 | symbol _ZNK17CPersonStatusInfo10pParseNameEv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK17CPersonStatusInfo10pParseNameEv(void)

{
  return 0;
}

// ==== CPersonStatusInfo::operator==(CPersonStatusInfo const&)
// vaddr 0x12b0f18 | ghidra 0x13b0f18 | size 644 | symbol _ZN17CPersonStatusInfoeqERKS_ | lib libSOA-3.7.0.so | 2026-10-08
bool _ZN17CPersonStatusInfoeqERKS_(long param_1,long param_2)

{
  if (*(long *)(param_1 + 0x60) != *(long *)(param_2 + 0x60)) {
    return false;
  }
  if (*(int *)(param_1 + 0x90) != *(int *)(param_2 + 0x90)) {
    return false;
  }
  if (*(int *)(param_1 + 0x130) != *(int *)(param_2 + 0x130)) {
    return false;
  }
  if (*(long *)(param_1 + 0x160) != *(long *)(param_2 + 0x160)) {
    return false;
  }
  if (*(long *)(param_1 + 400) != *(long *)(param_2 + 400)) {
    return false;
  }
  if (*(int *)(param_1 + 0x1c0) != *(int *)(param_2 + 0x1c0)) {
    return false;
  }
  if (*(int *)(param_1 + 0x1f0) != *(int *)(param_2 + 0x1f0)) {
    return false;
  }
  if (*(int *)(param_1 + 0x220) != *(int *)(param_2 + 0x220)) {
    return false;
  }
  if (*(int *)(param_1 + 0x250) != *(int *)(param_2 + 0x250)) {
    return false;
  }
  if (*(int *)(param_1 + 0x2f0) != *(int *)(param_2 + 0x2f0)) {
    return false;
  }
  if (*(int *)(param_1 + 0x390) != *(int *)(param_2 + 0x390)) {
    return false;
  }
  if (*(float *)(param_1 + 0x430) != *(float *)(param_2 + 0x430)) {
    return false;
  }
  if (*(float *)(param_1 + 0x460) != *(float *)(param_2 + 0x460)) {
    return false;
  }
  if (*(float *)(param_1 + 0x490) != *(float *)(param_2 + 0x490)) {
    return false;
  }
  if (*(float *)(param_1 + 0x4c0) != *(float *)(param_2 + 0x4c0)) {
    return false;
  }
  if (*(float *)(param_1 + 0x4f0) != *(float *)(param_2 + 0x4f0)) {
    return false;
  }
  if (*(float *)(param_1 + 0x520) != *(float *)(param_2 + 0x520)) {
    return false;
  }
  if (*(float *)(param_1 + 0x580) != *(float *)(param_2 + 0x580)) {
    return false;
  }
  if (*(float *)(param_1 + 0x5b0) != *(float *)(param_2 + 0x5b0)) {
    return false;
  }
  if (*(float *)(param_1 + 0x5e0) != *(float *)(param_2 + 0x5e0)) {
    return false;
  }
  if (*(float *)(param_1 + 0x610) != *(float *)(param_2 + 0x610)) {
    return false;
  }
  if (*(float *)(param_1 + 0x640) != *(float *)(param_2 + 0x640)) {
    return false;
  }
  if (*(float *)(param_1 + 0x670) != *(float *)(param_2 + 0x670)) {
    return false;
  }
  if (*(float *)(param_1 + 0x6a0) != *(float *)(param_2 + 0x6a0)) {
    return false;
  }
  if (*(int *)(param_1 + 0x6d0) != *(int *)(param_2 + 0x6d0)) {
    return false;
  }
  if (*(int *)(param_1 + 0x740) == *(int *)(param_2 + 0x740)) {
    return *(int *)(param_1 + 0x7a0) == *(int *)(param_2 + 0x7a0);
  }
  return false;
}

// ==== CPersonStatusInfo::operator!=(CPersonStatusInfo const&)
// vaddr 0x12b119c | ghidra 0x13b119c | size 32 | symbol _ZN17CPersonStatusInfoneERKS_ | lib libSOA-3.7.0.so | 2026-10-08
uint _ZN17CPersonStatusInfoneERKS_(long *param_1)

{
  uint uVar1;
  
  uVar1 = (**(code **)(*param_1 + 0x20))();
  return ~uVar1 & 1;
}

// ==== CPersonStatusInfo::operator=(CPersonStatusInfo const&)
// vaddr 0x12ff888 | ghidra 0x13ff888 | size 4068 | symbol _ZN17CPersonStatusInfoaSERKS_ | lib libSOA-3.7.0.so | 2026-10-08
long _ZN17CPersonStatusInfoaSERKS_(long param_1,long param_2)

{
  ulong *puVar1;
  ulong uVar2;
  ulong uVar3;
  long lVar4;
  ulong uVar5;
  long lVar6;
  undefined8 uVar7;
  
  if (param_1 != param_2) {
    void std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::__assign_multi<std::__ndk1::__tree_const_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long> >(std::__ndk1::__tree_const_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>, std::__ndk1::__tree_const_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>)(param_1 + 8,*(undefined8 *)(param_2 + 8),param_2 + 0x10);
    void std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::__assign_multi<std::__ndk1::__tree_const_iterator<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*, long> >(std::__ndk1::__tree_const_iterator<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*, long>, std::__ndk1::__tree_const_iterator<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*, long>)(param_1 + 0x20,*(undefined8 *)(param_2 + 0x20),param_2 + 0x28);
  }
  *(undefined8 *)(param_1 + 0x40) = *(undefined8 *)(param_2 + 0x40);
  *(undefined1 *)(param_1 + 0x48) = *(undefined1 *)(param_2 + 0x48);
  *(undefined4 *)(param_1 + 0x58) = *(undefined4 *)(param_2 + 0x58);
  *(undefined8 *)(param_1 + 0x60) = *(undefined8 *)(param_2 + 0x60);
  *(undefined8 *)(param_1 + 0x70) = *(undefined8 *)(param_2 + 0x70);
  *(undefined1 *)(param_1 + 0x78) = *(undefined1 *)(param_2 + 0x78);
  *(undefined4 *)(param_1 + 0x88) = *(undefined4 *)(param_2 + 0x88);
  *(undefined4 *)(param_1 + 0x90) = *(undefined4 *)(param_2 + 0x90);
  *(undefined8 *)(param_1 + 0xa0) = *(undefined8 *)(param_2 + 0xa0);
  *(undefined1 *)(param_1 + 0xa8) = *(undefined1 *)(param_2 + 0xa8);
  *(undefined4 *)(param_1 + 0xb8) = *(undefined4 *)(param_2 + 0xb8);
  if (param_1 != param_2) {
    puVar1 = (ulong *)(param_1 + 0xc0);
    uVar5 = *(ulong *)(param_2 + 200);
    lVar4 = *(long *)(param_2 + 0xd0);
    uVar3 = (ulong)*(byte *)puVar1;
    if ((*(byte *)(param_2 + 0xc0) & 1) == 0) {
      lVar4 = param_2 + 0xc1;
      uVar5 = (ulong)(*(byte *)(param_2 + 0xc0) >> 1);
    }
    if ((*(byte *)puVar1 & 1) == 0) {
      uVar2 = 0x16;
      lVar6 = uVar5 - 0x16;
      if (0x15 < uVar5 && lVar6 != 0) {
code_r0x013ff97c:
        if ((uVar3 & 1) == 0) {
          uVar3 = (ulong)(((uint)uVar3 & 0xfe) >> 1);
        }
        else {
          uVar3 = *(ulong *)(param_1 + 200);
        }
        string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(puVar1,uVar2,lVar6,uVar3,0,uVar3,uVar5);
        goto code_r0x013ff9dc;
      }
    }
    else {
      uVar3 = *puVar1;
      uVar2 = (uVar3 & 0xfffffffffffffffe) - 1;
      lVar6 = uVar5 - uVar2;
      if (uVar2 <= uVar5 && lVar6 != 0) goto code_r0x013ff97c;
    }
    if ((uVar3 & 1) == 0) {
      lVar6 = param_1 + 0xc1;
    }
    else {
      lVar6 = *(long *)(param_1 + 0xd0);
    }
    if (uVar5 != 0) {
      memmove(lVar6,lVar4,uVar5);
    }
    *(undefined1 *)(lVar6 + uVar5) = 0;
    if ((*(byte *)puVar1 & 1) == 0) {
      *(byte *)puVar1 = (byte)(uVar5 << 1);
    }
    else {
      *(ulong *)(param_1 + 200) = uVar5;
    }
  }
code_r0x013ff9dc:
  *(undefined8 *)(param_1 + 0xe0) = *(undefined8 *)(param_2 + 0xe0);
  *(undefined1 *)(param_1 + 0xe8) = *(undefined1 *)(param_2 + 0xe8);
  *(undefined4 *)(param_1 + 0xf8) = *(undefined4 *)(param_2 + 0xf8);
  *(undefined4 *)(param_1 + 0x100) = *(undefined4 *)(param_2 + 0x100);
  *(undefined8 *)(param_1 + 0x110) = *(undefined8 *)(param_2 + 0x110);
  *(undefined1 *)(param_1 + 0x118) = *(undefined1 *)(param_2 + 0x118);
  *(undefined4 *)(param_1 + 0x128) = *(undefined4 *)(param_2 + 0x128);
  *(undefined4 *)(param_1 + 0x130) = *(undefined4 *)(param_2 + 0x130);
  *(undefined8 *)(param_1 + 0x140) = *(undefined8 *)(param_2 + 0x140);
  *(undefined1 *)(param_1 + 0x148) = *(undefined1 *)(param_2 + 0x148);
  *(undefined4 *)(param_1 + 0x158) = *(undefined4 *)(param_2 + 0x158);
  *(undefined8 *)(param_1 + 0x160) = *(undefined8 *)(param_2 + 0x160);
  *(undefined8 *)(param_1 + 0x170) = *(undefined8 *)(param_2 + 0x170);
  *(undefined1 *)(param_1 + 0x178) = *(undefined1 *)(param_2 + 0x178);
  *(undefined4 *)(param_1 + 0x188) = *(undefined4 *)(param_2 + 0x188);
  *(undefined8 *)(param_1 + 400) = *(undefined8 *)(param_2 + 400);
  *(undefined8 *)(param_1 + 0x1a0) = *(undefined8 *)(param_2 + 0x1a0);
  *(undefined1 *)(param_1 + 0x1a8) = *(undefined1 *)(param_2 + 0x1a8);
  *(undefined4 *)(param_1 + 0x1b8) = *(undefined4 *)(param_2 + 0x1b8);
  *(undefined4 *)(param_1 + 0x1c0) = *(undefined4 *)(param_2 + 0x1c0);
  *(undefined8 *)(param_1 + 0x1d0) = *(undefined8 *)(param_2 + 0x1d0);
  *(undefined1 *)(param_1 + 0x1d8) = *(undefined1 *)(param_2 + 0x1d8);
  *(undefined4 *)(param_1 + 0x1e8) = *(undefined4 *)(param_2 + 0x1e8);
  *(undefined4 *)(param_1 + 0x1f0) = *(undefined4 *)(param_2 + 0x1f0);
  *(undefined8 *)(param_1 + 0x200) = *(undefined8 *)(param_2 + 0x200);
  *(undefined1 *)(param_1 + 0x208) = *(undefined1 *)(param_2 + 0x208);
  *(undefined4 *)(param_1 + 0x218) = *(undefined4 *)(param_2 + 0x218);
  *(undefined4 *)(param_1 + 0x220) = *(undefined4 *)(param_2 + 0x220);
  *(undefined8 *)(param_1 + 0x230) = *(undefined8 *)(param_2 + 0x230);
  *(undefined1 *)(param_1 + 0x238) = *(undefined1 *)(param_2 + 0x238);
  *(undefined4 *)(param_1 + 0x248) = *(undefined4 *)(param_2 + 0x248);
  *(undefined4 *)(param_1 + 0x250) = *(undefined4 *)(param_2 + 0x250);
  *(undefined8 *)(param_1 + 0x260) = *(undefined8 *)(param_2 + 0x260);
  *(undefined1 *)(param_1 + 0x268) = *(undefined1 *)(param_2 + 0x268);
  *(undefined4 *)(param_1 + 0x278) = *(undefined4 *)(param_2 + 0x278);
  if (param_1 != param_2) {
    puVar1 = (ulong *)(param_1 + 0x280);
    lVar4 = *(long *)(param_2 + 0x290);
    uVar5 = *(ulong *)(param_2 + 0x288);
    uVar3 = (ulong)*(byte *)puVar1;
    if ((*(byte *)(param_2 + 0x280) & 1) == 0) {
      lVar4 = param_2 + 0x281;
      uVar5 = (ulong)(*(byte *)(param_2 + 0x280) >> 1);
    }
    if ((*(byte *)puVar1 & 1) == 0) {
      uVar2 = 0x16;
      lVar6 = uVar5 - 0x16;
      if (0x15 < uVar5 && lVar6 != 0) {
code_r0x013ffb58:
        if ((uVar3 & 1) == 0) {
          uVar3 = (ulong)(((uint)uVar3 & 0xfe) >> 1);
        }
        else {
          uVar3 = *(ulong *)(param_1 + 0x288);
        }
        string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(puVar1,uVar2,lVar6,uVar3,0,uVar3,uVar5);
        goto code_r0x013ffbb8;
      }
    }
    else {
      uVar3 = *puVar1;
      uVar2 = (uVar3 & 0xfffffffffffffffe) - 1;
      lVar6 = uVar5 - uVar2;
      if (uVar2 <= uVar5 && lVar6 != 0) goto code_r0x013ffb58;
    }
    if ((uVar3 & 1) == 0) {
      lVar6 = param_1 + 0x281;
    }
    else {
      lVar6 = *(long *)(param_1 + 0x290);
    }
    if (uVar5 != 0) {
      memmove(lVar6,lVar4,uVar5);
    }
    *(undefined1 *)(lVar6 + uVar5) = 0;
    if ((*(byte *)puVar1 & 1) == 0) {
      *(byte *)puVar1 = (byte)(uVar5 << 1);
    }
    else {
      *(ulong *)(param_1 + 0x288) = uVar5;
    }
  }
code_r0x013ffbb8:
  *(undefined8 *)(param_1 + 0x2a0) = *(undefined8 *)(param_2 + 0x2a0);
  *(undefined1 *)(param_1 + 0x2a8) = *(undefined1 *)(param_2 + 0x2a8);
  *(undefined4 *)(param_1 + 0x2b8) = *(undefined4 *)(param_2 + 0x2b8);
  *(undefined4 *)(param_1 + 0x2c0) = *(undefined4 *)(param_2 + 0x2c0);
  *(undefined8 *)(param_1 + 0x2d0) = *(undefined8 *)(param_2 + 0x2d0);
  *(undefined1 *)(param_1 + 0x2d8) = *(undefined1 *)(param_2 + 0x2d8);
  *(undefined4 *)(param_1 + 0x2e8) = *(undefined4 *)(param_2 + 0x2e8);
  *(undefined4 *)(param_1 + 0x2f0) = *(undefined4 *)(param_2 + 0x2f0);
  *(undefined8 *)(param_1 + 0x300) = *(undefined8 *)(param_2 + 0x300);
  *(undefined1 *)(param_1 + 0x308) = *(undefined1 *)(param_2 + 0x308);
  *(undefined4 *)(param_1 + 0x318) = *(undefined4 *)(param_2 + 0x318);
  if (param_1 != param_2) {
    puVar1 = (ulong *)(param_1 + 800);
    lVar4 = *(long *)(param_2 + 0x330);
    uVar5 = *(ulong *)(param_2 + 0x328);
    uVar3 = (ulong)*(byte *)puVar1;
    if ((*(byte *)(param_2 + 800) & 1) == 0) {
      lVar4 = param_2 + 0x321;
      uVar5 = (ulong)(*(byte *)(param_2 + 800) >> 1);
    }
    if ((*(byte *)puVar1 & 1) == 0) {
      uVar2 = 0x16;
      lVar6 = uVar5 - 0x16;
      if (0x15 < uVar5 && lVar6 != 0) {
code_r0x013ffc74:
        if ((uVar3 & 1) == 0) {
          uVar3 = (ulong)(((uint)uVar3 & 0xfe) >> 1);
        }
        else {
          uVar3 = *(ulong *)(param_1 + 0x328);
        }
        string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(puVar1,uVar2,lVar6,uVar3,0,uVar3,uVar5);
        goto code_r0x013ffcd4;
      }
    }
    else {
      uVar3 = *puVar1;
      uVar2 = (uVar3 & 0xfffffffffffffffe) - 1;
      lVar6 = uVar5 - uVar2;
      if (uVar2 <= uVar5 && lVar6 != 0) goto code_r0x013ffc74;
    }
    if ((uVar3 & 1) == 0) {
      lVar6 = param_1 + 0x321;
    }
    else {
      lVar6 = *(long *)(param_1 + 0x330);
    }
    if (uVar5 != 0) {
      memmove(lVar6,lVar4,uVar5);
    }
    *(undefined1 *)(lVar6 + uVar5) = 0;
    if ((*(byte *)puVar1 & 1) == 0) {
      *(byte *)puVar1 = (byte)(uVar5 << 1);
    }
    else {
      *(ulong *)(param_1 + 0x328) = uVar5;
    }
  }
code_r0x013ffcd4:
  *(undefined8 *)(param_1 + 0x340) = *(undefined8 *)(param_2 + 0x340);
  *(undefined1 *)(param_1 + 0x348) = *(undefined1 *)(param_2 + 0x348);
  *(undefined4 *)(param_1 + 0x358) = *(undefined4 *)(param_2 + 0x358);
  *(undefined4 *)(param_1 + 0x360) = *(undefined4 *)(param_2 + 0x360);
  *(undefined8 *)(param_1 + 0x370) = *(undefined8 *)(param_2 + 0x370);
  *(undefined1 *)(param_1 + 0x378) = *(undefined1 *)(param_2 + 0x378);
  *(undefined4 *)(param_1 + 0x388) = *(undefined4 *)(param_2 + 0x388);
  *(undefined4 *)(param_1 + 0x390) = *(undefined4 *)(param_2 + 0x390);
  *(undefined8 *)(param_1 + 0x3a0) = *(undefined8 *)(param_2 + 0x3a0);
  *(undefined1 *)(param_1 + 0x3a8) = *(undefined1 *)(param_2 + 0x3a8);
  *(undefined4 *)(param_1 + 0x3b8) = *(undefined4 *)(param_2 + 0x3b8);
  if (param_1 != param_2) {
    puVar1 = (ulong *)(param_1 + 0x3c0);
    lVar4 = *(long *)(param_2 + 0x3d0);
    uVar5 = *(ulong *)(param_2 + 0x3c8);
    uVar3 = (ulong)*(byte *)puVar1;
    if ((*(byte *)(param_2 + 0x3c0) & 1) == 0) {
      lVar4 = param_2 + 0x3c1;
      uVar5 = (ulong)(*(byte *)(param_2 + 0x3c0) >> 1);
    }
    if ((*(byte *)puVar1 & 1) == 0) {
      uVar2 = 0x16;
      lVar6 = uVar5 - 0x16;
      if (0x15 < uVar5 && lVar6 != 0) {
code_r0x013ffd90:
        if ((uVar3 & 1) == 0) {
          uVar3 = (ulong)(((uint)uVar3 & 0xfe) >> 1);
        }
        else {
          uVar3 = *(ulong *)(param_1 + 0x3c8);
        }
        string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(puVar1,uVar2,lVar6,uVar3,0,uVar3,uVar5);
        goto code_r0x013ffdf0;
      }
    }
    else {
      uVar3 = *puVar1;
      uVar2 = (uVar3 & 0xfffffffffffffffe) - 1;
      lVar6 = uVar5 - uVar2;
      if (uVar2 <= uVar5 && lVar6 != 0) goto code_r0x013ffd90;
    }
    if ((uVar3 & 1) == 0) {
      lVar6 = param_1 + 0x3c1;
    }
    else {
      lVar6 = *(long *)(param_1 + 0x3d0);
    }
    if (uVar5 != 0) {
      memmove(lVar6,lVar4,uVar5);
    }
    *(undefined1 *)(lVar6 + uVar5) = 0;
    if ((*(byte *)puVar1 & 1) == 0) {
      *(byte *)puVar1 = (byte)(uVar5 << 1);
    }
    else {
      *(ulong *)(param_1 + 0x3c8) = uVar5;
    }
  }
code_r0x013ffdf0:
  *(undefined8 *)(param_1 + 0x3e0) = *(undefined8 *)(param_2 + 0x3e0);
  *(undefined1 *)(param_1 + 1000) = *(undefined1 *)(param_2 + 1000);
  *(undefined4 *)(param_1 + 0x3f8) = *(undefined4 *)(param_2 + 0x3f8);
  *(undefined4 *)(param_1 + 0x400) = *(undefined4 *)(param_2 + 0x400);
  *(undefined8 *)(param_1 + 0x410) = *(undefined8 *)(param_2 + 0x410);
  *(undefined1 *)(param_1 + 0x418) = *(undefined1 *)(param_2 + 0x418);
  *(undefined4 *)(param_1 + 0x428) = *(undefined4 *)(param_2 + 0x428);
  *(undefined4 *)(param_1 + 0x430) = *(undefined4 *)(param_2 + 0x430);
  *(undefined8 *)(param_1 + 0x440) = *(undefined8 *)(param_2 + 0x440);
  *(undefined1 *)(param_1 + 0x448) = *(undefined1 *)(param_2 + 0x448);
  *(undefined4 *)(param_1 + 0x458) = *(undefined4 *)(param_2 + 0x458);
  *(undefined4 *)(param_1 + 0x460) = *(undefined4 *)(param_2 + 0x460);
  *(undefined8 *)(param_1 + 0x470) = *(undefined8 *)(param_2 + 0x470);
  *(undefined1 *)(param_1 + 0x478) = *(undefined1 *)(param_2 + 0x478);
  *(undefined4 *)(param_1 + 0x488) = *(undefined4 *)(param_2 + 0x488);
  *(undefined4 *)(param_1 + 0x490) = *(undefined4 *)(param_2 + 0x490);
  *(undefined8 *)(param_1 + 0x4a0) = *(undefined8 *)(param_2 + 0x4a0);
  *(undefined1 *)(param_1 + 0x4a8) = *(undefined1 *)(param_2 + 0x4a8);
  *(undefined4 *)(param_1 + 0x4b8) = *(undefined4 *)(param_2 + 0x4b8);
  *(undefined4 *)(param_1 + 0x4c0) = *(undefined4 *)(param_2 + 0x4c0);
  *(undefined8 *)(param_1 + 0x4d0) = *(undefined8 *)(param_2 + 0x4d0);
  *(undefined1 *)(param_1 + 0x4d8) = *(undefined1 *)(param_2 + 0x4d8);
  *(undefined4 *)(param_1 + 0x4e8) = *(undefined4 *)(param_2 + 0x4e8);
  *(undefined4 *)(param_1 + 0x4f0) = *(undefined4 *)(param_2 + 0x4f0);
  *(undefined8 *)(param_1 + 0x500) = *(undefined8 *)(param_2 + 0x500);
  *(undefined1 *)(param_1 + 0x508) = *(undefined1 *)(param_2 + 0x508);
  *(undefined4 *)(param_1 + 0x518) = *(undefined4 *)(param_2 + 0x518);
  *(undefined4 *)(param_1 + 0x520) = *(undefined4 *)(param_2 + 0x520);
  *(undefined8 *)(param_1 + 0x530) = *(undefined8 *)(param_2 + 0x530);
  *(undefined1 *)(param_1 + 0x538) = *(undefined1 *)(param_2 + 0x538);
  *(undefined4 *)(param_1 + 0x548) = *(undefined4 *)(param_2 + 0x548);
  *(undefined4 *)(param_1 + 0x550) = *(undefined4 *)(param_2 + 0x550);
  *(undefined8 *)(param_1 + 0x560) = *(undefined8 *)(param_2 + 0x560);
  *(undefined1 *)(param_1 + 0x568) = *(undefined1 *)(param_2 + 0x568);
  *(undefined4 *)(param_1 + 0x578) = *(undefined4 *)(param_2 + 0x578);
  *(undefined4 *)(param_1 + 0x580) = *(undefined4 *)(param_2 + 0x580);
  *(undefined8 *)(param_1 + 0x590) = *(undefined8 *)(param_2 + 0x590);
  *(undefined1 *)(param_1 + 0x598) = *(undefined1 *)(param_2 + 0x598);
  *(undefined4 *)(param_1 + 0x5a8) = *(undefined4 *)(param_2 + 0x5a8);
  *(undefined4 *)(param_1 + 0x5b0) = *(undefined4 *)(param_2 + 0x5b0);
  *(undefined8 *)(param_1 + 0x5c0) = *(undefined8 *)(param_2 + 0x5c0);
  *(undefined1 *)(param_1 + 0x5c8) = *(undefined1 *)(param_2 + 0x5c8);
  *(undefined4 *)(param_1 + 0x5d8) = *(undefined4 *)(param_2 + 0x5d8);
  *(undefined4 *)(param_1 + 0x5e0) = *(undefined4 *)(param_2 + 0x5e0);
  *(undefined8 *)(param_1 + 0x5f0) = *(undefined8 *)(param_2 + 0x5f0);
  *(undefined1 *)(param_1 + 0x5f8) = *(undefined1 *)(param_2 + 0x5f8);
  *(undefined4 *)(param_1 + 0x608) = *(undefined4 *)(param_2 + 0x608);
  *(undefined4 *)(param_1 + 0x610) = *(undefined4 *)(param_2 + 0x610);
  *(undefined8 *)(param_1 + 0x620) = *(undefined8 *)(param_2 + 0x620);
  *(undefined1 *)(param_1 + 0x628) = *(undefined1 *)(param_2 + 0x628);
  *(undefined4 *)(param_1 + 0x638) = *(undefined4 *)(param_2 + 0x638);
  *(undefined4 *)(param_1 + 0x640) = *(undefined4 *)(param_2 + 0x640);
  *(undefined8 *)(param_1 + 0x650) = *(undefined8 *)(param_2 + 0x650);
  *(undefined1 *)(param_1 + 0x658) = *(undefined1 *)(param_2 + 0x658);
  *(undefined4 *)(param_1 + 0x668) = *(undefined4 *)(param_2 + 0x668);
  *(undefined4 *)(param_1 + 0x670) = *(undefined4 *)(param_2 + 0x670);
  *(undefined8 *)(param_1 + 0x680) = *(undefined8 *)(param_2 + 0x680);
  *(undefined1 *)(param_1 + 0x688) = *(undefined1 *)(param_2 + 0x688);
  *(undefined4 *)(param_1 + 0x698) = *(undefined4 *)(param_2 + 0x698);
  *(undefined4 *)(param_1 + 0x6a0) = *(undefined4 *)(param_2 + 0x6a0);
  *(undefined8 *)(param_1 + 0x6b0) = *(undefined8 *)(param_2 + 0x6b0);
  *(undefined1 *)(param_1 + 0x6b8) = *(undefined1 *)(param_2 + 0x6b8);
  *(undefined4 *)(param_1 + 0x6c8) = *(undefined4 *)(param_2 + 0x6c8);
  *(undefined4 *)(param_1 + 0x6d0) = *(undefined4 *)(param_2 + 0x6d0);
  *(undefined8 *)(param_1 + 0x6e0) = *(undefined8 *)(param_2 + 0x6e0);
  *(undefined1 *)(param_1 + 0x6e8) = *(undefined1 *)(param_2 + 0x6e8);
  *(undefined4 *)(param_1 + 0x6f8) = *(undefined4 *)(param_2 + 0x6f8);
  if (param_1 != param_2) {
    puVar1 = (ulong *)(param_1 + 0x700);
    lVar4 = *(long *)(param_2 + 0x710);
    uVar5 = *(ulong *)(param_2 + 0x708);
    uVar3 = (ulong)*(byte *)puVar1;
    if ((*(byte *)(param_2 + 0x700) & 1) == 0) {
      lVar4 = param_2 + 0x701;
      uVar5 = (ulong)(*(byte *)(param_2 + 0x700) >> 1);
    }
    if ((*(byte *)puVar1 & 1) == 0) {
      uVar2 = 0x16;
      lVar6 = uVar5 - 0x16;
      if (0x15 < uVar5 && lVar6 != 0) {
code_r0x0140006c:
        if ((uVar3 & 1) == 0) {
          uVar3 = (ulong)(((uint)uVar3 & 0xfe) >> 1);
        }
        else {
          uVar3 = *(ulong *)(param_1 + 0x708);
        }
        string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(puVar1,uVar2,lVar6,uVar3,0,uVar3,uVar5);
        goto code_r0x014000cc;
      }
    }
    else {
      uVar3 = *puVar1;
      uVar2 = (uVar3 & 0xfffffffffffffffe) - 1;
      lVar6 = uVar5 - uVar2;
      if (uVar2 <= uVar5 && lVar6 != 0) goto code_r0x0140006c;
    }
    if ((uVar3 & 1) == 0) {
      lVar6 = param_1 + 0x701;
    }
    else {
      lVar6 = *(long *)(param_1 + 0x710);
    }
    if (uVar5 != 0) {
      memmove(lVar6,lVar4,uVar5);
    }
    *(undefined1 *)(lVar6 + uVar5) = 0;
    if ((*(byte *)puVar1 & 1) == 0) {
      *(byte *)puVar1 = (byte)(uVar5 << 1);
    }
    else {
      *(ulong *)(param_1 + 0x708) = uVar5;
    }
  }
code_r0x014000cc:
  *(undefined8 *)(param_1 + 0x720) = *(undefined8 *)(param_2 + 0x720);
  *(undefined1 *)(param_1 + 0x728) = *(undefined1 *)(param_2 + 0x728);
  *(undefined4 *)(param_1 + 0x738) = *(undefined4 *)(param_2 + 0x738);
  *(undefined4 *)(param_1 + 0x740) = *(undefined4 *)(param_2 + 0x740);
  *(undefined8 *)(param_1 + 0x750) = *(undefined8 *)(param_2 + 0x750);
  *(undefined1 *)(param_1 + 0x758) = *(undefined1 *)(param_2 + 0x758);
  *(undefined4 *)(param_1 + 0x768) = *(undefined4 *)(param_2 + 0x768);
  *(undefined4 *)(param_1 + 0x770) = *(undefined4 *)(param_2 + 0x770);
  *(undefined8 *)(param_1 + 0x780) = *(undefined8 *)(param_2 + 0x780);
  *(undefined1 *)(param_1 + 0x788) = *(undefined1 *)(param_2 + 0x788);
  *(undefined4 *)(param_1 + 0x798) = *(undefined4 *)(param_2 + 0x798);
  *(undefined4 *)(param_1 + 0x7a0) = *(undefined4 *)(param_2 + 0x7a0);
  *(undefined8 *)(param_1 + 0x7b0) = *(undefined8 *)(param_2 + 0x7b0);
  *(undefined1 *)(param_1 + 0x7b8) = *(undefined1 *)(param_2 + 0x7b8);
  *(undefined4 *)(param_1 + 0x7c8) = *(undefined4 *)(param_2 + 0x7c8);
  *(undefined4 *)(param_1 + 2000) = *(undefined4 *)(param_2 + 2000);
  *(undefined8 *)(param_1 + 0x7e0) = *(undefined8 *)(param_2 + 0x7e0);
  *(undefined1 *)(param_1 + 0x7e8) = *(undefined1 *)(param_2 + 0x7e8);
  *(undefined4 *)(param_1 + 0x7f8) = *(undefined4 *)(param_2 + 0x7f8);
  *(undefined4 *)(param_1 + 0x800) = *(undefined4 *)(param_2 + 0x800);
  *(undefined8 *)(param_1 + 0x810) = *(undefined8 *)(param_2 + 0x810);
  *(undefined1 *)(param_1 + 0x818) = *(undefined1 *)(param_2 + 0x818);
  *(undefined4 *)(param_1 + 0x828) = *(undefined4 *)(param_2 + 0x828);
  if (param_1 == param_2) goto code_r0x01400248;
  puVar1 = (ulong *)(param_1 + 0x830);
  lVar4 = *(long *)(param_2 + 0x840);
  uVar5 = *(ulong *)(param_2 + 0x838);
  uVar3 = (ulong)*(byte *)puVar1;
  if ((*(byte *)(param_2 + 0x830) & 1) == 0) {
    lVar4 = param_2 + 0x831;
    uVar5 = (ulong)(*(byte *)(param_2 + 0x830) >> 1);
  }
  if ((*(byte *)puVar1 & 1) == 0) {
    uVar2 = 0x16;
    lVar6 = uVar5 - 0x16;
    if (0x15 < uVar5 && lVar6 != 0) {
code_r0x014001e8:
      if ((uVar3 & 1) == 0) {
        uVar3 = (ulong)(((uint)uVar3 & 0xfe) >> 1);
      }
      else {
        uVar3 = *(ulong *)(param_1 + 0x838);
      }
      string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(puVar1,uVar2,lVar6,uVar3,0,uVar3,uVar5);
      goto code_r0x01400248;
    }
  }
  else {
    uVar3 = *puVar1;
    uVar2 = (uVar3 & 0xfffffffffffffffe) - 1;
    lVar6 = uVar5 - uVar2;
    if (uVar2 <= uVar5 && lVar6 != 0) goto code_r0x014001e8;
  }
  if ((uVar3 & 1) == 0) {
    lVar6 = param_1 + 0x831;
  }
  else {
    lVar6 = *(long *)(param_1 + 0x840);
  }
  if (uVar5 != 0) {
    memmove(lVar6,lVar4,uVar5);
  }
  *(undefined1 *)(lVar6 + uVar5) = 0;
  if ((*(byte *)puVar1 & 1) == 0) {
    *(byte *)puVar1 = (byte)(uVar5 << 1);
  }
  else {
    *(ulong *)(param_1 + 0x838) = uVar5;
  }
code_r0x01400248:
  *(undefined8 *)(param_1 + 0x850) = *(undefined8 *)(param_2 + 0x850);
  *(undefined1 *)(param_1 + 0x858) = *(undefined1 *)(param_2 + 0x858);
  *(undefined4 *)(param_1 + 0x868) = *(undefined4 *)(param_2 + 0x868);
  *(undefined4 *)(param_1 + 0x870) = *(undefined4 *)(param_2 + 0x870);
  *(undefined8 *)(param_1 + 0x880) = *(undefined8 *)(param_2 + 0x880);
  *(undefined1 *)(param_1 + 0x888) = *(undefined1 *)(param_2 + 0x888);
  *(undefined4 *)(param_1 + 0x898) = *(undefined4 *)(param_2 + 0x898);
  *(undefined4 *)(param_1 + 0x8a0) = *(undefined4 *)(param_2 + 0x8a0);
  *(undefined8 *)(param_1 + 0x8b0) = *(undefined8 *)(param_2 + 0x8b0);
  *(undefined1 *)(param_1 + 0x8b8) = *(undefined1 *)(param_2 + 0x8b8);
  *(undefined4 *)(param_1 + 0x8c8) = *(undefined4 *)(param_2 + 0x8c8);
  *(undefined4 *)(param_1 + 0x8d0) = *(undefined4 *)(param_2 + 0x8d0);
  *(undefined8 *)(param_1 + 0x8e0) = *(undefined8 *)(param_2 + 0x8e0);
  *(undefined1 *)(param_1 + 0x8e8) = *(undefined1 *)(param_2 + 0x8e8);
  *(undefined4 *)(param_1 + 0x8f8) = *(undefined4 *)(param_2 + 0x8f8);
  *(undefined4 *)(param_1 + 0x900) = *(undefined4 *)(param_2 + 0x900);
  *(undefined8 *)(param_1 + 0x910) = *(undefined8 *)(param_2 + 0x910);
  *(undefined1 *)(param_1 + 0x918) = *(undefined1 *)(param_2 + 0x918);
  *(undefined4 *)(param_1 + 0x928) = *(undefined4 *)(param_2 + 0x928);
  *(undefined4 *)(param_1 + 0x930) = *(undefined4 *)(param_2 + 0x930);
  *(undefined8 *)(param_1 + 0x940) = *(undefined8 *)(param_2 + 0x940);
  *(undefined1 *)(param_1 + 0x948) = *(undefined1 *)(param_2 + 0x948);
  *(undefined4 *)(param_1 + 0x958) = *(undefined4 *)(param_2 + 0x958);
  *(undefined4 *)(param_1 + 0x960) = *(undefined4 *)(param_2 + 0x960);
  *(undefined8 *)(param_1 + 0x970) = *(undefined8 *)(param_2 + 0x970);
  *(undefined1 *)(param_1 + 0x978) = *(undefined1 *)(param_2 + 0x978);
  *(undefined4 *)(param_1 + 0x988) = *(undefined4 *)(param_2 + 0x988);
  *(undefined4 *)(param_1 + 0x990) = *(undefined4 *)(param_2 + 0x990);
  *(undefined8 *)(param_1 + 0x9a0) = *(undefined8 *)(param_2 + 0x9a0);
  *(undefined1 *)(param_1 + 0x9a8) = *(undefined1 *)(param_2 + 0x9a8);
  *(undefined4 *)(param_1 + 0x9b8) = *(undefined4 *)(param_2 + 0x9b8);
  *(undefined4 *)(param_1 + 0x9c0) = *(undefined4 *)(param_2 + 0x9c0);
  *(undefined8 *)(param_1 + 0x9d0) = *(undefined8 *)(param_2 + 0x9d0);
  *(undefined1 *)(param_1 + 0x9d8) = *(undefined1 *)(param_2 + 0x9d8);
  *(undefined4 *)(param_1 + 0x9e8) = *(undefined4 *)(param_2 + 0x9e8);
  *(undefined4 *)(param_1 + 0x9f0) = *(undefined4 *)(param_2 + 0x9f0);
  *(undefined8 *)(param_1 + 0xa00) = *(undefined8 *)(param_2 + 0xa00);
  *(undefined1 *)(param_1 + 0xa08) = *(undefined1 *)(param_2 + 0xa08);
  *(undefined4 *)(param_1 + 0xa18) = *(undefined4 *)(param_2 + 0xa18);
  *(undefined4 *)(param_1 + 0xa20) = *(undefined4 *)(param_2 + 0xa20);
  *(undefined8 *)(param_1 + 0xa30) = *(undefined8 *)(param_2 + 0xa30);
  *(undefined1 *)(param_1 + 0xa38) = *(undefined1 *)(param_2 + 0xa38);
  *(undefined4 *)(param_1 + 0xa48) = *(undefined4 *)(param_2 + 0xa48);
  *(undefined4 *)(param_1 + 0xa50) = *(undefined4 *)(param_2 + 0xa50);
  *(undefined8 *)(param_1 + 0xa60) = *(undefined8 *)(param_2 + 0xa60);
  *(undefined1 *)(param_1 + 0xa68) = *(undefined1 *)(param_2 + 0xa68);
  *(undefined4 *)(param_1 + 0xa78) = *(undefined4 *)(param_2 + 0xa78);
  *(undefined1 *)(param_1 + 0xa80) = *(undefined1 *)(param_2 + 0xa80);
  *(undefined8 *)(param_1 + 0xa90) = *(undefined8 *)(param_2 + 0xa90);
  *(undefined1 *)(param_1 + 0xa98) = *(undefined1 *)(param_2 + 0xa98);
  *(undefined4 *)(param_1 + 0xaa8) = *(undefined4 *)(param_2 + 0xaa8);
  *(undefined1 *)(param_1 + 0xab0) = *(undefined1 *)(param_2 + 0xab0);
  *(undefined8 *)(param_1 + 0xac0) = *(undefined8 *)(param_2 + 0xac0);
  *(undefined1 *)(param_1 + 0xac8) = *(undefined1 *)(param_2 + 0xac8);
  *(undefined4 *)(param_1 + 0xad8) = *(undefined4 *)(param_2 + 0xad8);
  *(undefined4 *)(param_1 + 0xae0) = *(undefined4 *)(param_2 + 0xae0);
  *(undefined8 *)(param_1 + 0xaf0) = *(undefined8 *)(param_2 + 0xaf0);
  *(undefined1 *)(param_1 + 0xaf8) = *(undefined1 *)(param_2 + 0xaf8);
  *(undefined4 *)(param_1 + 0xb08) = *(undefined4 *)(param_2 + 0xb08);
  *(undefined4 *)(param_1 + 0xb10) = *(undefined4 *)(param_2 + 0xb10);
  *(undefined8 *)(param_1 + 0xb20) = *(undefined8 *)(param_2 + 0xb20);
  *(undefined1 *)(param_1 + 0xb28) = *(undefined1 *)(param_2 + 0xb28);
  *(undefined4 *)(param_1 + 0xb38) = *(undefined4 *)(param_2 + 0xb38);
  *(undefined4 *)(param_1 + 0xb40) = *(undefined4 *)(param_2 + 0xb40);
  *(undefined8 *)(param_1 + 0xb50) = *(undefined8 *)(param_2 + 0xb50);
  *(undefined1 *)(param_1 + 0xb58) = *(undefined1 *)(param_2 + 0xb58);
  *(undefined4 *)(param_1 + 0xb68) = *(undefined4 *)(param_2 + 0xb68);
  *(undefined4 *)(param_1 + 0xb70) = *(undefined4 *)(param_2 + 0xb70);
  *(undefined8 *)(param_1 + 0xb80) = *(undefined8 *)(param_2 + 0xb80);
  *(undefined1 *)(param_1 + 0xb88) = *(undefined1 *)(param_2 + 0xb88);
  *(undefined4 *)(param_1 + 0xb98) = *(undefined4 *)(param_2 + 0xb98);
  *(undefined4 *)(param_1 + 0xba0) = *(undefined4 *)(param_2 + 0xba0);
  *(undefined8 *)(param_1 + 0xbb0) = *(undefined8 *)(param_2 + 0xbb0);
  *(undefined1 *)(param_1 + 3000) = *(undefined1 *)(param_2 + 3000);
  *(undefined4 *)(param_1 + 0xbc8) = *(undefined4 *)(param_2 + 0xbc8);
  *(undefined4 *)(param_1 + 0xbd0) = *(undefined4 *)(param_2 + 0xbd0);
  *(undefined8 *)(param_1 + 0xbe0) = *(undefined8 *)(param_2 + 0xbe0);
  *(undefined1 *)(param_1 + 0xbe8) = *(undefined1 *)(param_2 + 0xbe8);
  *(undefined4 *)(param_1 + 0xbf8) = *(undefined4 *)(param_2 + 0xbf8);
  *(undefined4 *)(param_1 + 0xc00) = *(undefined4 *)(param_2 + 0xc00);
  *(undefined8 *)(param_1 + 0xc10) = *(undefined8 *)(param_2 + 0xc10);
  *(undefined1 *)(param_1 + 0xc18) = *(undefined1 *)(param_2 + 0xc18);
  *(undefined4 *)(param_1 + 0xc28) = *(undefined4 *)(param_2 + 0xc28);
  *(undefined4 *)(param_1 + 0xc30) = *(undefined4 *)(param_2 + 0xc30);
  *(undefined8 *)(param_1 + 0xc40) = *(undefined8 *)(param_2 + 0xc40);
  *(undefined1 *)(param_1 + 0xc48) = *(undefined1 *)(param_2 + 0xc48);
  *(undefined4 *)(param_1 + 0xc58) = *(undefined4 *)(param_2 + 0xc58);
  *(undefined4 *)(param_1 + 0xc60) = *(undefined4 *)(param_2 + 0xc60);
  *(undefined8 *)(param_1 + 0xc70) = *(undefined8 *)(param_2 + 0xc70);
  *(undefined1 *)(param_1 + 0xc78) = *(undefined1 *)(param_2 + 0xc78);
  *(undefined4 *)(param_1 + 0xc88) = *(undefined4 *)(param_2 + 0xc88);
  *(undefined4 *)(param_1 + 0xc90) = *(undefined4 *)(param_2 + 0xc90);
  *(undefined8 *)(param_1 + 0xca0) = *(undefined8 *)(param_2 + 0xca0);
  *(undefined1 *)(param_1 + 0xca8) = *(undefined1 *)(param_2 + 0xca8);
  *(undefined4 *)(param_1 + 0xcb8) = *(undefined4 *)(param_2 + 0xcb8);
  *(undefined4 *)(param_1 + 0xcc0) = *(undefined4 *)(param_2 + 0xcc0);
  *(undefined8 *)(param_1 + 0xcd0) = *(undefined8 *)(param_2 + 0xcd0);
  *(undefined1 *)(param_1 + 0xcd8) = *(undefined1 *)(param_2 + 0xcd8);
  *(undefined4 *)(param_1 + 0xce8) = *(undefined4 *)(param_2 + 0xce8);
  *(undefined4 *)(param_1 + 0xcf0) = *(undefined4 *)(param_2 + 0xcf0);
  *(undefined8 *)(param_1 + 0xd00) = *(undefined8 *)(param_2 + 0xd00);
  *(undefined1 *)(param_1 + 0xd08) = *(undefined1 *)(param_2 + 0xd08);
  *(undefined4 *)(param_1 + 0xd18) = *(undefined4 *)(param_2 + 0xd18);
  *(undefined1 *)(param_1 + 0xd20) = *(undefined1 *)(param_2 + 0xd20);
  *(undefined8 *)(param_1 + 0xd30) = *(undefined8 *)(param_2 + 0xd30);
  *(undefined1 *)(param_1 + 0xd38) = *(undefined1 *)(param_2 + 0xd38);
  *(undefined4 *)(param_1 + 0xd48) = *(undefined4 *)(param_2 + 0xd48);
  *(undefined4 *)(param_1 + 0xd50) = *(undefined4 *)(param_2 + 0xd50);
  *(undefined8 *)(param_1 + 0xd60) = *(undefined8 *)(param_2 + 0xd60);
  *(undefined1 *)(param_1 + 0xd68) = *(undefined1 *)(param_2 + 0xd68);
  *(undefined4 *)(param_1 + 0xd78) = *(undefined4 *)(param_2 + 0xd78);
  *(undefined4 *)(param_1 + 0xd80) = *(undefined4 *)(param_2 + 0xd80);
  *(undefined8 *)(param_1 + 0xd90) = *(undefined8 *)(param_2 + 0xd90);
  *(undefined1 *)(param_1 + 0xd98) = *(undefined1 *)(param_2 + 0xd98);
  *(undefined4 *)(param_1 + 0xda8) = *(undefined4 *)(param_2 + 0xda8);
  *(undefined4 *)(param_1 + 0xdb0) = *(undefined4 *)(param_2 + 0xdb0);
  *(undefined8 *)(param_1 + 0xdc0) = *(undefined8 *)(param_2 + 0xdc0);
  *(undefined1 *)(param_1 + 0xdc8) = *(undefined1 *)(param_2 + 0xdc8);
  *(undefined4 *)(param_1 + 0xdd8) = *(undefined4 *)(param_2 + 0xdd8);
  *(undefined4 *)(param_1 + 0xde0) = *(undefined4 *)(param_2 + 0xde0);
  *(undefined8 *)(param_1 + 0xdf0) = *(undefined8 *)(param_2 + 0xdf0);
  *(undefined1 *)(param_1 + 0xdf8) = *(undefined1 *)(param_2 + 0xdf8);
  *(undefined4 *)(param_1 + 0xe08) = *(undefined4 *)(param_2 + 0xe08);
  *(undefined4 *)(param_1 + 0xe10) = *(undefined4 *)(param_2 + 0xe10);
  *(undefined8 *)(param_1 + 0xe20) = *(undefined8 *)(param_2 + 0xe20);
  *(undefined1 *)(param_1 + 0xe28) = *(undefined1 *)(param_2 + 0xe28);
  *(undefined4 *)(param_1 + 0xe38) = *(undefined4 *)(param_2 + 0xe38);
  *(undefined4 *)(param_1 + 0xe40) = *(undefined4 *)(param_2 + 0xe40);
  if (param_1 != param_2) {
    void std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::__assign_multi<std::__ndk1::__tree_const_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long> >(std::__ndk1::__tree_const_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>, std::__ndk1::__tree_const_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>)(param_1 + 0xe50,*(undefined8 *)(param_2 + 0xe50),param_2 + 0xe58);
    void std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::__assign_multi<std::__ndk1::__tree_const_iterator<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*, long> >(std::__ndk1::__tree_const_iterator<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*, long>, std::__ndk1::__tree_const_iterator<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*, long>)(param_1 + 0xe68,*(undefined8 *)(param_2 + 0xe68),param_2 + 0xe70);
  }
  *(undefined8 *)(param_1 + 0xe88) = *(undefined8 *)(param_2 + 0xe88);
  *(undefined1 *)(param_1 + 0xe90) = *(undefined1 *)(param_2 + 0xe90);
  *(undefined4 *)(param_1 + 0xea0) = *(undefined4 *)(param_2 + 0xea0);
  *(undefined4 *)(param_1 + 0xea8) = *(undefined4 *)(param_2 + 0xea8);
  *(undefined8 *)(param_1 + 0xeb8) = *(undefined8 *)(param_2 + 0xeb8);
  *(undefined1 *)(param_1 + 0xec0) = *(undefined1 *)(param_2 + 0xec0);
  *(undefined4 *)(param_1 + 0xed0) = *(undefined4 *)(param_2 + 0xed0);
  *(undefined4 *)(param_1 + 0xed8) = *(undefined4 *)(param_2 + 0xed8);
  *(undefined8 *)(param_1 + 0xee8) = *(undefined8 *)(param_2 + 0xee8);
  *(undefined1 *)(param_1 + 0xef0) = *(undefined1 *)(param_2 + 0xef0);
  *(undefined4 *)(param_1 + 0xf00) = *(undefined4 *)(param_2 + 0xf00);
  *(undefined4 *)(param_1 + 0xf08) = *(undefined4 *)(param_2 + 0xf08);
  if (param_1 == param_2) {
    UniverseAddStatusInfo::operator=(UniverseAddStatusInfo const&)(param_1 + 0x1000,param_2 + 0x1000);
    UniverseDeityBoostInfo::operator=(UniverseDeityBoostInfo const&)(param_1 + 0x11e8,param_2 + 0x11e8);
  }
  else {
    void std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::__assign_multi<std::__ndk1::__tree_const_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long> >(std::__ndk1::__tree_const_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>, std::__ndk1::__tree_const_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>)(param_1 + 0xf18,*(undefined8 *)(param_2 + 0xf18),param_2 + 0xf20);
    void std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::__assign_multi<std::__ndk1::__tree_const_iterator<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*, long> >(std::__ndk1::__tree_const_iterator<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*, long>, std::__ndk1::__tree_const_iterator<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*, long>)(param_1 + 0xf30,*(undefined8 *)(param_2 + 0xf30),param_2 + 0xf38);
    void std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CFactorInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CFactorInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CFactorInfo>, Framework::CSTLMapAllocatorInf> >::__assign_multi<std::__ndk1::__tree_const_iterator<std::__ndk1::__value_type<unsigned long, CFactorInfo>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CFactorInfo>, void*>*, long> >(std::__ndk1::__tree_const_iterator<std::__ndk1::__value_type<unsigned long, CFactorInfo>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CFactorInfo>, void*>*, long>, std::__ndk1::__tree_const_iterator<std::__ndk1::__value_type<unsigned long, CFactorInfo>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CFactorInfo>, void*>*, long>)(param_1 + 0xf48,*(undefined8 *)(param_2 + 0xf48),param_2 + 0xf50);
    void std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::__assign_multi<std::__ndk1::__tree_const_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long> >(std::__ndk1::__tree_const_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>, std::__ndk1::__tree_const_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>)(param_1 + 0xf68,*(undefined8 *)(param_2 + 0xf68),param_2 + 0xf70);
    void std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::__assign_multi<std::__ndk1::__tree_const_iterator<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*, long> >(std::__ndk1::__tree_const_iterator<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*, long>, std::__ndk1::__tree_const_iterator<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*, long>)(param_1 + 0xf80,*(undefined8 *)(param_2 + 0xf80),param_2 + 0xf88);
    std::__ndk1::enable_if<__is_forward_iterator<CCharacterDecoObjectInfo*>::value&&is_constructible<CCharacterDecoObjectInfo, std::__ndk1::iterator_traits<CCharacterDecoObjectInfo*>::reference>::value, void>::type std::__ndk1::vector<CCharacterDecoObjectInfo, Framework::CSTLAllocator<CCharacterDecoObjectInfo, Framework::CSTLVectorAllocatorInf> >::assign<CCharacterDecoObjectInfo*>(CCharacterDecoObjectInfo*, CCharacterDecoObjectInfo*)(param_1 + 0xf98,*(undefined8 *)(param_2 + 0xf98),*(undefined8 *)(param_2 + 4000)
                   );
    void std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::__assign_multi<std::__ndk1::__tree_const_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long> >(std::__ndk1::__tree_const_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>, std::__ndk1::__tree_const_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>)(param_1 + 0xfb8,*(undefined8 *)(param_2 + 0xfb8),param_2 + 0xfc0);
    void std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::__assign_multi<std::__ndk1::__tree_const_iterator<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*, long> >(std::__ndk1::__tree_const_iterator<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*, long>, std::__ndk1::__tree_const_iterator<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*, long>)(param_1 + 0xfd0,*(undefined8 *)(param_2 + 0xfd0),param_2 + 0xfd8);
    std::__ndk1::enable_if<__is_forward_iterator<CParameterPropertyValue<unsigned int, 131u, CPropertyConverter>*>::value&&is_constructible<CParameterPropertyValue<unsigned int, 131u, CPropertyConverter>, std::__ndk1::iterator_traits<CParameterPropertyValue<unsigned int, 131u, CPropertyConverter>*>::reference>::value, void>::type std::__ndk1::vector<CParameterPropertyValue<unsigned int, 131u, CPropertyConverter>, Framework::CSTLAllocator<CParameterPropertyValue<unsigned int, 131u, CPropertyConverter>, Framework::CSTLVectorAllocatorInf> >::assign<CParameterPropertyValue<unsigned int, 131u, CPropertyConverter>*>(CParameterPropertyValue<unsigned int, 131u, CPropertyConverter>*, CParameterPropertyValue<unsigned int, 131u, CPropertyConverter>*)(param_1 + 0xfe8,*(undefined8 *)(param_2 + 0xfe8),
                    *(undefined8 *)(param_2 + 0xff0));
    UniverseAddStatusInfo::operator=(UniverseAddStatusInfo const&)(param_1 + 0x1000,param_2 + 0x1000);
    UniverseDeityBoostInfo::operator=(UniverseDeityBoostInfo const&)(param_1 + 0x11e8,param_2 + 0x11e8);
    void std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::__assign_multi<std::__ndk1::__tree_const_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long> >(std::__ndk1::__tree_const_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>, std::__ndk1::__tree_const_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>)(param_1 + 0x13d8,*(undefined8 *)(param_2 + 0x13d8),param_2 + 0x13e0);
    void std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::__assign_multi<std::__ndk1::__tree_const_iterator<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*, long> >(std::__ndk1::__tree_const_iterator<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*, long>, std::__ndk1::__tree_const_iterator<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*, long>)(param_1 + 0x13f0,*(undefined8 *)(param_2 + 0x13f0),param_2 + 0x13f8);
  }
  *(undefined8 *)(param_1 + 0x1410) = *(undefined8 *)(param_2 + 0x1410);
  *(undefined1 *)(param_1 + 0x1418) = *(undefined1 *)(param_2 + 0x1418);
  *(undefined4 *)(param_1 + 0x1428) = *(undefined4 *)(param_2 + 0x1428);
  *(undefined4 *)(param_1 + 0x1430) = *(undefined4 *)(param_2 + 0x1430);
  *(undefined8 *)(param_1 + 0x1440) = *(undefined8 *)(param_2 + 0x1440);
  *(undefined1 *)(param_1 + 0x1448) = *(undefined1 *)(param_2 + 0x1448);
  *(undefined4 *)(param_1 + 0x1458) = *(undefined4 *)(param_2 + 0x1458);
  *(undefined4 *)(param_1 + 0x1460) = *(undefined4 *)(param_2 + 0x1460);
  *(undefined8 *)(param_1 + 0x1470) = *(undefined8 *)(param_2 + 0x1470);
  *(undefined1 *)(param_1 + 0x1478) = *(undefined1 *)(param_2 + 0x1478);
  *(undefined4 *)(param_1 + 0x1488) = *(undefined4 *)(param_2 + 0x1488);
  *(undefined4 *)(param_1 + 0x1490) = *(undefined4 *)(param_2 + 0x1490);
  UniverseDeityBoostInfo::operator=(UniverseDeityBoostInfo const&)(param_1 + 0x1498,param_2 + 0x1498);
  uVar7 = *(undefined8 *)(param_2 + 0x1680);
  *(undefined8 *)(param_1 + 0x1688) = *(undefined8 *)(param_2 + 0x1688);
  *(undefined8 *)(param_1 + 0x1680) = uVar7;
  return param_1;
}

// ==== CPersonStatusInfo::CPersonStatusInfo(CPersonStatusInfo const&)
// vaddr 0x139a228 | ghidra 0x149a228 | size 7428 | symbol _ZN17CPersonStatusInfoC2ERKS_ | lib libSOA-3.7.0.so | 2026-10-08
void _ZN17CPersonStatusInfoC2ERKS_(long *param_1,long param_2)

{
  undefined *puVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined *puVar5;
  undefined4 uVar6;
  undefined1 uVar7;
  undefined *puVar8;
  long *plVar9;
  bool bVar10;
  long lVar11;
  long *plVar12;
  ulong uVar13;
  undefined8 uVar14;
  ulong uVar15;
  long *plVar16;
  
  puVar5 = PTR__ZTV8InfoBase_02cc49c8;
  *param_1 = (long)(PTR__ZTV8InfoBase_02cc49c8 + 0x10);
  Framework::CSTLMap<unsigned int, IParameterProperty*>::CSTLMap(Framework::CSTLMap<unsigned int, IParameterProperty*> const&)(param_1 + 1,param_2 + 8);
  Framework::CSTLMap<unsigned int, InfoBase*>::CSTLMap(Framework::CSTLMap<unsigned int, InfoBase*> const&)(param_1 + 4,param_2 + 0x20);
  puVar3 = PTR__ZTV18IParameterProperty_02cbe818;
  puVar1 = PTR__ZTV18IParameterProperty_02cbe818 + 0x10;
  *param_1 = (long)(PTR__ZTV17CPersonStatusInfo_02cbd500 + 0x10);
  param_1[7] = (long)puVar1;
  lVar11 = *(long *)(param_2 + 0x40);
  param_1[7] = (long)(PTR__ZTV22CParameterPropertyBaseILj163EE_02cbb018 + 0x10);
  param_1[8] = lVar11;
  puVar4 = PTR__ZTVN9Framework7CHash32E_02cba528;
  *(undefined1 *)(param_1 + 9) = *(undefined1 *)(param_2 + 0x48);
  puVar2 = puVar4 + 0x10;
  param_1[10] = (long)puVar2;
  puVar8 = PTR__ZTV23CParameterPropertyValueImLj163E18CPropertyConverterE_02cbb940;
  *(undefined4 *)(param_1 + 0xb) = *(undefined4 *)(param_2 + 0x58);
  param_1[7] = (long)(puVar8 + 0x10);
  param_1[0xc] = *(long *)(param_2 + 0x60);
  param_1[0xd] = (long)puVar1;
  lVar11 = *(long *)(param_2 + 0x70);
  param_1[0xd] = (long)(PTR__ZTV22CParameterPropertyBaseILj164EE_02cb6d78 + 0x10);
  param_1[0xe] = lVar11;
  uVar7 = *(undefined1 *)(param_2 + 0x78);
  param_1[0x10] = (long)puVar2;
  *(undefined1 *)(param_1 + 0xf) = uVar7;
  puVar8 = PTR__ZTV23CParameterPropertyValueIjLj164E18CPropertyConverterE_02cb6b60;
  *(undefined4 *)(param_1 + 0x11) = *(undefined4 *)(param_2 + 0x88);
  param_1[0xd] = (long)(puVar8 + 0x10);
  uVar6 = *(undefined4 *)(param_2 + 0x90);
  param_1[0x13] = (long)puVar1;
  *(undefined4 *)(param_1 + 0x12) = uVar6;
  lVar11 = *(long *)(param_2 + 0xa0);
  param_1[0x13] = (long)(PTR__ZTV22CParameterPropertyBaseILj165EE_02cbe958 + 0x10);
  param_1[0x14] = lVar11;
  uVar7 = *(undefined1 *)(param_2 + 0xa8);
  param_1[0x16] = (long)puVar2;
  *(undefined1 *)(param_1 + 0x15) = uVar7;
  puVar1 = 
  PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj165EE_02cbd098
  ;
  uVar6 = *(undefined4 *)(param_2 + 0xb8);
  plVar12 = param_1 + 0x18;
  *plVar12 = 0;
  *(undefined4 *)(param_1 + 0x17) = uVar6;
  param_1[0x13] = (long)(puVar1 + 0x10);
  param_1[0x19] = 0;
  param_1[0x1a] = 0;
  if ((*(byte *)(param_2 + 0xc0) & 1) == 0) {
    param_1[0x1a] = *(long *)(param_2 + 0xd0);
    lVar11 = *(long *)(param_2 + 0xc0);
    param_1[0x19] = *(long *)(param_2 + 200);
    *plVar12 = lVar11;
  }
  else {
    uVar13 = *(ulong *)(param_2 + 200);
    uVar14 = *(undefined8 *)(param_2 + 0xd0);
    if (uVar13 < 0x17) {
      lVar11 = (long)param_1 + 0xc1;
      *(char *)plVar12 = (char)(uVar13 << 1);
      if (uVar13 != 0) goto code_r0x0149a400;
    }
    else {
      uVar15 = uVar13 + 0x10 & 0xfffffffffffffff0;
      if (uVar15 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
      }
      lVar11 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar15,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
      if (lVar11 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
      }
      param_1[0x19] = uVar13;
      param_1[0x1a] = lVar11;
      param_1[0x18] = uVar15 | 1;
code_r0x0149a400:
      memcpy(lVar11,uVar14,uVar13);
    }
    *(undefined1 *)(lVar11 + uVar13) = 0;
  }
  puVar1 = puVar3 + 0x10;
  param_1[0x1b] = (long)puVar1;
  lVar11 = *(long *)(param_2 + 0xe0);
  param_1[0x1b] = (long)(PTR__ZTV22CParameterPropertyBaseILj166EE_02cbf3d8 + 0x10);
  param_1[0x1c] = lVar11;
  uVar7 = *(undefined1 *)(param_2 + 0xe8);
  puVar2 = puVar4 + 0x10;
  param_1[0x1e] = (long)puVar2;
  *(undefined1 *)(param_1 + 0x1d) = uVar7;
  puVar8 = PTR__ZTV23CParameterPropertyValueIjLj166E18CPropertyConverterE_02cc3d20;
  *(undefined4 *)(param_1 + 0x1f) = *(undefined4 *)(param_2 + 0xf8);
  param_1[0x1b] = (long)(puVar8 + 0x10);
  uVar6 = *(undefined4 *)(param_2 + 0x100);
  param_1[0x21] = (long)puVar1;
  *(undefined4 *)(param_1 + 0x20) = uVar6;
  lVar11 = *(long *)(param_2 + 0x110);
  param_1[0x21] = (long)(PTR__ZTV22CParameterPropertyBaseILj167EE_02cc36a8 + 0x10);
  param_1[0x22] = lVar11;
  uVar7 = *(undefined1 *)(param_2 + 0x118);
  param_1[0x24] = (long)puVar2;
  *(undefined1 *)(param_1 + 0x23) = uVar7;
  puVar8 = PTR__ZTV23CParameterPropertyValueIjLj167E18CPropertyConverterE_02cbccd8;
  *(undefined4 *)(param_1 + 0x25) = *(undefined4 *)(param_2 + 0x128);
  param_1[0x21] = (long)(puVar8 + 0x10);
  uVar6 = *(undefined4 *)(param_2 + 0x130);
  param_1[0x27] = (long)puVar1;
  *(undefined4 *)(param_1 + 0x26) = uVar6;
  lVar11 = *(long *)(param_2 + 0x140);
  param_1[0x27] = (long)(PTR__ZTV22CParameterPropertyBaseILj168EE_02cbb8a0 + 0x10);
  param_1[0x28] = lVar11;
  uVar7 = *(undefined1 *)(param_2 + 0x148);
  param_1[0x2a] = (long)puVar2;
  *(undefined1 *)(param_1 + 0x29) = uVar7;
  puVar8 = PTR__ZTV23CParameterPropertyValueImLj168E18CPropertyConverterE_02cc4290;
  *(undefined4 *)(param_1 + 0x2b) = *(undefined4 *)(param_2 + 0x158);
  param_1[0x27] = (long)(puVar8 + 0x10);
  param_1[0x2c] = *(long *)(param_2 + 0x160);
  param_1[0x2d] = (long)puVar1;
  lVar11 = *(long *)(param_2 + 0x170);
  param_1[0x2d] = (long)(PTR__ZTV22CParameterPropertyBaseILj169EE_02cbcf68 + 0x10);
  param_1[0x2e] = lVar11;
  uVar7 = *(undefined1 *)(param_2 + 0x178);
  param_1[0x30] = (long)puVar2;
  *(undefined1 *)(param_1 + 0x2f) = uVar7;
  puVar8 = PTR__ZTV23CParameterPropertyValueImLj169E18CPropertyConverterE_02cc3730;
  *(undefined4 *)(param_1 + 0x31) = *(undefined4 *)(param_2 + 0x188);
  param_1[0x2d] = (long)(puVar8 + 0x10);
  param_1[0x32] = *(long *)(param_2 + 400);
  param_1[0x33] = (long)puVar1;
  lVar11 = *(long *)(param_2 + 0x1a0);
  param_1[0x33] = (long)(PTR__ZTV22CParameterPropertyBaseILj170EE_02cc11c8 + 0x10);
  param_1[0x34] = lVar11;
  uVar7 = *(undefined1 *)(param_2 + 0x1a8);
  param_1[0x36] = (long)puVar2;
  *(undefined1 *)(param_1 + 0x35) = uVar7;
  puVar8 = PTR__ZTV23CParameterPropertyValueIjLj170E18CPropertyConverterE_02cc4be0;
  *(undefined4 *)(param_1 + 0x37) = *(undefined4 *)(param_2 + 0x1b8);
  param_1[0x33] = (long)(puVar8 + 0x10);
  uVar6 = *(undefined4 *)(param_2 + 0x1c0);
  param_1[0x39] = (long)puVar1;
  *(undefined4 *)(param_1 + 0x38) = uVar6;
  lVar11 = *(long *)(param_2 + 0x1d0);
  param_1[0x39] = (long)(PTR__ZTV22CParameterPropertyBaseILj171EE_02cb6eb8 + 0x10);
  param_1[0x3a] = lVar11;
  uVar7 = *(undefined1 *)(param_2 + 0x1d8);
  param_1[0x3c] = (long)puVar2;
  *(undefined1 *)(param_1 + 0x3b) = uVar7;
  puVar8 = PTR__ZTV23CParameterPropertyValueIjLj171E18CPropertyConverterE_02cbdc20;
  *(undefined4 *)(param_1 + 0x3d) = *(undefined4 *)(param_2 + 0x1e8);
  param_1[0x39] = (long)(puVar8 + 0x10);
  uVar6 = *(undefined4 *)(param_2 + 0x1f0);
  param_1[0x3f] = (long)puVar1;
  *(undefined4 *)(param_1 + 0x3e) = uVar6;
  lVar11 = *(long *)(param_2 + 0x200);
  param_1[0x3f] = (long)(PTR__ZTV22CParameterPropertyBaseILj172EE_02cb79d0 + 0x10);
  param_1[0x40] = lVar11;
  uVar7 = *(undefined1 *)(param_2 + 0x208);
  param_1[0x42] = (long)puVar2;
  *(undefined1 *)(param_1 + 0x41) = uVar7;
  puVar8 = PTR__ZTV23CParameterPropertyValueIjLj172E18CPropertyConverterE_02cc33c8;
  *(undefined4 *)(param_1 + 0x43) = *(undefined4 *)(param_2 + 0x218);
  param_1[0x3f] = (long)(puVar8 + 0x10);
  uVar6 = *(undefined4 *)(param_2 + 0x220);
  param_1[0x45] = (long)puVar1;
  *(undefined4 *)(param_1 + 0x44) = uVar6;
  puVar8 = PTR__ZTV22CParameterPropertyBaseILj174EE_02cb7838;
  param_1[0x46] = *(long *)(param_2 + 0x230);
  param_1[0x45] = (long)(puVar8 + 0x10);
  uVar7 = *(undefined1 *)(param_2 + 0x238);
  param_1[0x48] = (long)puVar2;
  *(undefined1 *)(param_1 + 0x47) = uVar7;
  puVar8 = PTR__ZTV23CParameterPropertyValueIjLj174E18CPropertyConverterE_02cba740;
  *(undefined4 *)(param_1 + 0x49) = *(undefined4 *)(param_2 + 0x248);
  param_1[0x45] = (long)(puVar8 + 0x10);
  uVar6 = *(undefined4 *)(param_2 + 0x250);
  param_1[0x4b] = (long)puVar1;
  *(undefined4 *)(param_1 + 0x4a) = uVar6;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj175EE_02cbe608;
  param_1[0x4c] = *(long *)(param_2 + 0x260);
  param_1[0x4b] = (long)(puVar1 + 0x10);
  puVar1 = 
  PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj175EE_02cc2fd0
  ;
  uVar7 = *(undefined1 *)(param_2 + 0x268);
  param_1[0x4e] = (long)puVar2;
  *(undefined1 *)(param_1 + 0x4d) = uVar7;
  uVar6 = *(undefined4 *)(param_2 + 0x278);
  param_1[0x4b] = (long)(puVar1 + 0x10);
  param_1[0x52] = 0;
  param_1[0x51] = 0;
  *(undefined4 *)(param_1 + 0x4f) = uVar6;
  param_1[0x50] = 0;
  if ((*(byte *)(param_2 + 0x280) & 1) == 0) {
    param_1[0x52] = *(long *)(param_2 + 0x290);
    lVar11 = *(long *)(param_2 + 0x280);
    param_1[0x51] = *(long *)(param_2 + 0x288);
    param_1[0x50] = lVar11;
  }
  else {
    uVar13 = *(ulong *)(param_2 + 0x288);
    uVar14 = *(undefined8 *)(param_2 + 0x290);
    if (uVar13 < 0x17) {
      lVar11 = (long)param_1 + 0x281;
      *(char *)(param_1 + 0x50) = (char)(uVar13 << 1);
      if (uVar13 != 0) goto code_r0x0149a730;
    }
    else {
      uVar15 = uVar13 + 0x10 & 0xfffffffffffffff0;
      if (uVar15 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
      }
      lVar11 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar15,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
      if (lVar11 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
      }
      param_1[0x52] = lVar11;
      param_1[0x50] = uVar15 | 1;
      param_1[0x51] = uVar13;
code_r0x0149a730:
      memcpy(lVar11,uVar14,uVar13);
    }
    *(undefined1 *)(lVar11 + uVar13) = 0;
  }
  puVar1 = puVar3 + 0x10;
  param_1[0x53] = (long)puVar1;
  puVar2 = PTR__ZTV22CParameterPropertyBaseILj176EE_02cb9b78;
  param_1[0x54] = *(long *)(param_2 + 0x2a0);
  param_1[0x53] = (long)(puVar2 + 0x10);
  uVar7 = *(undefined1 *)(param_2 + 0x2a8);
  puVar2 = puVar4 + 0x10;
  param_1[0x56] = (long)puVar2;
  *(undefined1 *)(param_1 + 0x55) = uVar7;
  puVar8 = PTR__ZTV23CParameterPropertyValueIjLj176E18CPropertyConverterE_02cb8db0;
  *(undefined4 *)(param_1 + 0x57) = *(undefined4 *)(param_2 + 0x2b8);
  param_1[0x53] = (long)(puVar8 + 0x10);
  uVar6 = *(undefined4 *)(param_2 + 0x2c0);
  param_1[0x59] = (long)puVar1;
  *(undefined4 *)(param_1 + 0x58) = uVar6;
  puVar8 = PTR__ZTV22CParameterPropertyBaseILj177EE_02cbeb68;
  param_1[0x5a] = *(long *)(param_2 + 0x2d0);
  param_1[0x59] = (long)(puVar8 + 0x10);
  uVar7 = *(undefined1 *)(param_2 + 0x2d8);
  param_1[0x5c] = (long)puVar2;
  *(undefined1 *)(param_1 + 0x5b) = uVar7;
  puVar8 = PTR__ZTV23CParameterPropertyValueIjLj177E18CPropertyConverterE_02cb9920;
  *(undefined4 *)(param_1 + 0x5d) = *(undefined4 *)(param_2 + 0x2e8);
  param_1[0x59] = (long)(puVar8 + 0x10);
  uVar6 = *(undefined4 *)(param_2 + 0x2f0);
  param_1[0x5f] = (long)puVar1;
  *(undefined4 *)(param_1 + 0x5e) = uVar6;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj178EE_02cc1938;
  param_1[0x60] = *(long *)(param_2 + 0x300);
  param_1[0x5f] = (long)(puVar1 + 0x10);
  puVar1 = 
  PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj178EE_02cb8b38
  ;
  uVar7 = *(undefined1 *)(param_2 + 0x308);
  param_1[0x62] = (long)puVar2;
  *(undefined1 *)(param_1 + 0x61) = uVar7;
  uVar6 = *(undefined4 *)(param_2 + 0x318);
  param_1[0x5f] = (long)(puVar1 + 0x10);
  param_1[0x66] = 0;
  param_1[0x65] = 0;
  *(undefined4 *)(param_1 + 99) = uVar6;
  param_1[100] = 0;
  if ((*(byte *)(param_2 + 800) & 1) == 0) {
    param_1[0x66] = *(long *)(param_2 + 0x330);
    lVar11 = *(long *)(param_2 + 800);
    param_1[0x65] = *(long *)(param_2 + 0x328);
    param_1[100] = lVar11;
  }
  else {
    uVar13 = *(ulong *)(param_2 + 0x328);
    uVar14 = *(undefined8 *)(param_2 + 0x330);
    if (uVar13 < 0x17) {
      lVar11 = (long)param_1 + 0x321;
      *(char *)(param_1 + 100) = (char)(uVar13 << 1);
      if (uVar13 != 0) goto code_r0x0149a8d4;
    }
    else {
      uVar15 = uVar13 + 0x10 & 0xfffffffffffffff0;
      if (uVar15 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
      }
      lVar11 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar15,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
      if (lVar11 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
      }
      param_1[0x66] = lVar11;
      param_1[100] = uVar15 | 1;
      param_1[0x65] = uVar13;
code_r0x0149a8d4:
      memcpy(lVar11,uVar14,uVar13);
    }
    *(undefined1 *)(lVar11 + uVar13) = 0;
  }
  puVar1 = puVar3 + 0x10;
  param_1[0x67] = (long)puVar1;
  puVar2 = PTR__ZTV22CParameterPropertyBaseILj179EE_02cbae40;
  param_1[0x68] = *(long *)(param_2 + 0x340);
  param_1[0x67] = (long)(puVar2 + 0x10);
  uVar7 = *(undefined1 *)(param_2 + 0x348);
  puVar2 = puVar4 + 0x10;
  param_1[0x6a] = (long)puVar2;
  *(undefined1 *)(param_1 + 0x69) = uVar7;
  puVar8 = PTR__ZTV23CParameterPropertyValueIjLj179E18CPropertyConverterE_02cc09e0;
  *(undefined4 *)(param_1 + 0x6b) = *(undefined4 *)(param_2 + 0x358);
  param_1[0x67] = (long)(puVar8 + 0x10);
  uVar6 = *(undefined4 *)(param_2 + 0x360);
  param_1[0x6d] = (long)puVar1;
  *(undefined4 *)(param_1 + 0x6c) = uVar6;
  puVar8 = PTR__ZTV22CParameterPropertyBaseILj180EE_02cba700;
  param_1[0x6e] = *(long *)(param_2 + 0x370);
  param_1[0x6d] = (long)(puVar8 + 0x10);
  uVar7 = *(undefined1 *)(param_2 + 0x378);
  param_1[0x70] = (long)puVar2;
  *(undefined1 *)(param_1 + 0x6f) = uVar7;
  puVar8 = PTR__ZTV23CParameterPropertyValueIjLj180E18CPropertyConverterE_02cc15d0;
  *(undefined4 *)(param_1 + 0x71) = *(undefined4 *)(param_2 + 0x388);
  param_1[0x6d] = (long)(puVar8 + 0x10);
  uVar6 = *(undefined4 *)(param_2 + 0x390);
  param_1[0x73] = (long)puVar1;
  *(undefined4 *)(param_1 + 0x72) = uVar6;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj181EE_02cbb330;
  param_1[0x74] = *(long *)(param_2 + 0x3a0);
  param_1[0x73] = (long)(puVar1 + 0x10);
  puVar1 = 
  PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj181EE_02cc0890
  ;
  uVar7 = *(undefined1 *)(param_2 + 0x3a8);
  param_1[0x76] = (long)puVar2;
  *(undefined1 *)(param_1 + 0x75) = uVar7;
  uVar6 = *(undefined4 *)(param_2 + 0x3b8);
  param_1[0x73] = (long)(puVar1 + 0x10);
  param_1[0x7a] = 0;
  param_1[0x79] = 0;
  *(undefined4 *)(param_1 + 0x77) = uVar6;
  param_1[0x78] = 0;
  if ((*(byte *)(param_2 + 0x3c0) & 1) == 0) {
    param_1[0x7a] = *(long *)(param_2 + 0x3d0);
    lVar11 = *(long *)(param_2 + 0x3c0);
    param_1[0x79] = *(long *)(param_2 + 0x3c8);
    param_1[0x78] = lVar11;
  }
  else {
    uVar13 = *(ulong *)(param_2 + 0x3c8);
    uVar14 = *(undefined8 *)(param_2 + 0x3d0);
    if (uVar13 < 0x17) {
      lVar11 = (long)param_1 + 0x3c1;
      *(char *)(param_1 + 0x78) = (char)(uVar13 << 1);
      if (uVar13 != 0) goto code_r0x0149aa78;
    }
    else {
      uVar15 = uVar13 + 0x10 & 0xfffffffffffffff0;
      if (uVar15 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
      }
      lVar11 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar15,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
      if (lVar11 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
      }
      param_1[0x7a] = lVar11;
      param_1[0x78] = uVar15 | 1;
      param_1[0x79] = uVar13;
code_r0x0149aa78:
      memcpy(lVar11,uVar14,uVar13);
    }
    *(undefined1 *)(lVar11 + uVar13) = 0;
  }
  puVar1 = puVar3 + 0x10;
  param_1[0x7b] = (long)puVar1;
  puVar2 = PTR__ZTV22CParameterPropertyBaseILj182EE_02cc2f48;
  param_1[0x7c] = *(long *)(param_2 + 0x3e0);
  param_1[0x7b] = (long)(puVar2 + 0x10);
  uVar7 = *(undefined1 *)(param_2 + 1000);
  puVar2 = puVar4 + 0x10;
  param_1[0x7e] = (long)puVar2;
  *(undefined1 *)(param_1 + 0x7d) = uVar7;
  puVar8 = PTR__ZTV23CParameterPropertyValueIjLj182E18CPropertyConverterE_02cbd910;
  *(undefined4 *)(param_1 + 0x7f) = *(undefined4 *)(param_2 + 0x3f8);
  param_1[0x7b] = (long)(puVar8 + 0x10);
  uVar6 = *(undefined4 *)(param_2 + 0x400);
  param_1[0x81] = (long)puVar1;
  *(undefined4 *)(param_1 + 0x80) = uVar6;
  puVar8 = PTR__ZTV22CParameterPropertyBaseILj184EE_02cc1e78;
  param_1[0x82] = *(long *)(param_2 + 0x410);
  param_1[0x81] = (long)(puVar8 + 0x10);
  uVar7 = *(undefined1 *)(param_2 + 0x418);
  param_1[0x84] = (long)puVar2;
  *(undefined1 *)(param_1 + 0x83) = uVar7;
  puVar8 = PTR__ZTV23CParameterPropertyValueIfLj184E18CPropertyConverterE_02cbc170;
  *(undefined4 *)(param_1 + 0x85) = *(undefined4 *)(param_2 + 0x428);
  param_1[0x81] = (long)(puVar8 + 0x10);
  uVar6 = *(undefined4 *)(param_2 + 0x430);
  param_1[0x87] = (long)puVar1;
  *(undefined4 *)(param_1 + 0x86) = uVar6;
  puVar8 = PTR__ZTV22CParameterPropertyBaseILj185EE_02cbd450;
  param_1[0x88] = *(long *)(param_2 + 0x440);
  param_1[0x87] = (long)(puVar8 + 0x10);
  uVar7 = *(undefined1 *)(param_2 + 0x448);
  param_1[0x8a] = (long)puVar2;
  *(undefined1 *)(param_1 + 0x89) = uVar7;
  puVar8 = PTR__ZTV23CParameterPropertyValueIfLj185E18CPropertyConverterE_02cba4f0;
  *(undefined4 *)(param_1 + 0x8b) = *(undefined4 *)(param_2 + 0x458);
  param_1[0x87] = (long)(puVar8 + 0x10);
  uVar6 = *(undefined4 *)(param_2 + 0x460);
  param_1[0x8d] = (long)puVar1;
  *(undefined4 *)(param_1 + 0x8c) = uVar6;
  puVar8 = PTR__ZTV22CParameterPropertyBaseILj186EE_02cc2420;
  param_1[0x8e] = *(long *)(param_2 + 0x470);
  param_1[0x8d] = (long)(puVar8 + 0x10);
  uVar7 = *(undefined1 *)(param_2 + 0x478);
  param_1[0x90] = (long)puVar2;
  *(undefined1 *)(param_1 + 0x8f) = uVar7;
  puVar8 = PTR__ZTV23CParameterPropertyValueIfLj186E18CPropertyConverterE_02cbcdb0;
  *(undefined4 *)(param_1 + 0x91) = *(undefined4 *)(param_2 + 0x488);
  param_1[0x8d] = (long)(puVar8 + 0x10);
  uVar6 = *(undefined4 *)(param_2 + 0x490);
  param_1[0x93] = (long)puVar1;
  *(undefined4 *)(param_1 + 0x92) = uVar6;
  puVar8 = PTR__ZTV22CParameterPropertyBaseILj187EE_02cbe120;
  param_1[0x94] = *(long *)(param_2 + 0x4a0);
  param_1[0x93] = (long)(puVar8 + 0x10);
  uVar7 = *(undefined1 *)(param_2 + 0x4a8);
  param_1[0x96] = (long)puVar2;
  *(undefined1 *)(param_1 + 0x95) = uVar7;
  puVar8 = PTR__ZTV23CParameterPropertyValueIfLj187E18CPropertyConverterE_02cbd458;
  *(undefined4 *)(param_1 + 0x97) = *(undefined4 *)(param_2 + 0x4b8);
  param_1[0x93] = (long)(puVar8 + 0x10);
  uVar6 = *(undefined4 *)(param_2 + 0x4c0);
  param_1[0x99] = (long)puVar1;
  *(undefined4 *)(param_1 + 0x98) = uVar6;
  puVar8 = PTR__ZTV22CParameterPropertyBaseILj188EE_02cb7598;
  param_1[0x9a] = *(long *)(param_2 + 0x4d0);
  param_1[0x99] = (long)(puVar8 + 0x10);
  uVar7 = *(undefined1 *)(param_2 + 0x4d8);
  param_1[0x9c] = (long)puVar2;
  *(undefined1 *)(param_1 + 0x9b) = uVar7;
  puVar8 = PTR__ZTV23CParameterPropertyValueIfLj188E18CPropertyConverterE_02cc14c8;
  *(undefined4 *)(param_1 + 0x9d) = *(undefined4 *)(param_2 + 0x4e8);
  param_1[0x99] = (long)(puVar8 + 0x10);
  uVar6 = *(undefined4 *)(param_2 + 0x4f0);
  param_1[0x9f] = (long)puVar1;
  *(undefined4 *)(param_1 + 0x9e) = uVar6;
  puVar8 = PTR__ZTV22CParameterPropertyBaseILj189EE_02cb80f0;
  param_1[0xa0] = *(long *)(param_2 + 0x500);
  param_1[0x9f] = (long)(puVar8 + 0x10);
  uVar7 = *(undefined1 *)(param_2 + 0x508);
  param_1[0xa2] = (long)puVar2;
  *(undefined1 *)(param_1 + 0xa1) = uVar7;
  puVar8 = PTR__ZTV23CParameterPropertyValueIfLj189E18CPropertyConverterE_02cb81d8;
  *(undefined4 *)(param_1 + 0xa3) = *(undefined4 *)(param_2 + 0x518);
  param_1[0x9f] = (long)(puVar8 + 0x10);
  uVar6 = *(undefined4 *)(param_2 + 0x520);
  param_1[0xa5] = (long)puVar1;
  *(undefined4 *)(param_1 + 0xa4) = uVar6;
  puVar8 = PTR__ZTV22CParameterPropertyBaseILj190EE_02cb75d0;
  param_1[0xa6] = *(long *)(param_2 + 0x530);
  param_1[0xa5] = (long)(puVar8 + 0x10);
  uVar7 = *(undefined1 *)(param_2 + 0x538);
  param_1[0xa8] = (long)puVar2;
  *(undefined1 *)(param_1 + 0xa7) = uVar7;
  puVar8 = PTR__ZTV23CParameterPropertyValueIfLj190E18CPropertyConverterE_02cc3d40;
  *(undefined4 *)(param_1 + 0xa9) = *(undefined4 *)(param_2 + 0x548);
  param_1[0xa5] = (long)(puVar8 + 0x10);
  uVar6 = *(undefined4 *)(param_2 + 0x550);
  param_1[0xab] = (long)puVar1;
  *(undefined4 *)(param_1 + 0xaa) = uVar6;
  puVar8 = PTR__ZTV22CParameterPropertyBaseILj192EE_02cb9fb0;
  param_1[0xac] = *(long *)(param_2 + 0x560);
  param_1[0xab] = (long)(puVar8 + 0x10);
  uVar7 = *(undefined1 *)(param_2 + 0x568);
  param_1[0xae] = (long)puVar2;
  *(undefined1 *)(param_1 + 0xad) = uVar7;
  puVar8 = PTR__ZTV23CParameterPropertyValueIfLj192E18CPropertyConverterE_02cba1d8;
  *(undefined4 *)(param_1 + 0xaf) = *(undefined4 *)(param_2 + 0x578);
  param_1[0xab] = (long)(puVar8 + 0x10);
  uVar6 = *(undefined4 *)(param_2 + 0x580);
  param_1[0xb1] = (long)puVar1;
  *(undefined4 *)(param_1 + 0xb0) = uVar6;
  puVar8 = PTR__ZTV22CParameterPropertyBaseILj193EE_02cbe150;
  param_1[0xb2] = *(long *)(param_2 + 0x590);
  param_1[0xb1] = (long)(puVar8 + 0x10);
  uVar7 = *(undefined1 *)(param_2 + 0x598);
  param_1[0xb4] = (long)puVar2;
  *(undefined1 *)(param_1 + 0xb3) = uVar7;
  puVar8 = PTR__ZTV23CParameterPropertyValueIfLj193E18CPropertyConverterE_02cba8c0;
  *(undefined4 *)(param_1 + 0xb5) = *(undefined4 *)(param_2 + 0x5a8);
  param_1[0xb1] = (long)(puVar8 + 0x10);
  uVar6 = *(undefined4 *)(param_2 + 0x5b0);
  param_1[0xb7] = (long)puVar1;
  *(undefined4 *)(param_1 + 0xb6) = uVar6;
  puVar8 = PTR__ZTV22CParameterPropertyBaseILj194EE_02cbed70;
  param_1[0xb8] = *(long *)(param_2 + 0x5c0);
  param_1[0xb7] = (long)(puVar8 + 0x10);
  uVar7 = *(undefined1 *)(param_2 + 0x5c8);
  param_1[0xba] = (long)puVar2;
  *(undefined1 *)(param_1 + 0xb9) = uVar7;
  puVar8 = PTR__ZTV23CParameterPropertyValueIfLj194E18CPropertyConverterE_02cc3e30;
  *(undefined4 *)(param_1 + 0xbb) = *(undefined4 *)(param_2 + 0x5d8);
  param_1[0xb7] = (long)(puVar8 + 0x10);
  uVar6 = *(undefined4 *)(param_2 + 0x5e0);
  param_1[0xbd] = (long)puVar1;
  *(undefined4 *)(param_1 + 0xbc) = uVar6;
  puVar8 = PTR__ZTV22CParameterPropertyBaseILj195EE_02cb80e8;
  param_1[0xbe] = *(long *)(param_2 + 0x5f0);
  param_1[0xbd] = (long)(puVar8 + 0x10);
  uVar7 = *(undefined1 *)(param_2 + 0x5f8);
  param_1[0xc0] = (long)puVar2;
  *(undefined1 *)(param_1 + 0xbf) = uVar7;
  puVar8 = PTR__ZTV23CParameterPropertyValueIfLj195E18CPropertyConverterE_02cb9660;
  *(undefined4 *)(param_1 + 0xc1) = *(undefined4 *)(param_2 + 0x608);
  param_1[0xbd] = (long)(puVar8 + 0x10);
  uVar6 = *(undefined4 *)(param_2 + 0x610);
  param_1[0xc3] = (long)puVar1;
  *(undefined4 *)(param_1 + 0xc2) = uVar6;
  puVar8 = PTR__ZTV22CParameterPropertyBaseILj196EE_02cbebf0;
  param_1[0xc4] = *(long *)(param_2 + 0x620);
  param_1[0xc3] = (long)(puVar8 + 0x10);
  uVar7 = *(undefined1 *)(param_2 + 0x628);
  param_1[0xc6] = (long)puVar2;
  *(undefined1 *)(param_1 + 0xc5) = uVar7;
  puVar8 = PTR__ZTV23CParameterPropertyValueIfLj196E18CPropertyConverterE_02cbdc18;
  *(undefined4 *)(param_1 + 199) = *(undefined4 *)(param_2 + 0x638);
  param_1[0xc3] = (long)(puVar8 + 0x10);
  uVar6 = *(undefined4 *)(param_2 + 0x640);
  param_1[0xc9] = (long)puVar1;
  *(undefined4 *)(param_1 + 200) = uVar6;
  puVar8 = PTR__ZTV22CParameterPropertyBaseILj197EE_02cb7220;
  param_1[0xca] = *(long *)(param_2 + 0x650);
  param_1[0xc9] = (long)(puVar8 + 0x10);
  uVar7 = *(undefined1 *)(param_2 + 0x658);
  param_1[0xcc] = (long)puVar2;
  *(undefined1 *)(param_1 + 0xcb) = uVar7;
  puVar8 = PTR__ZTV23CParameterPropertyValueIfLj197E18CPropertyConverterE_02cb9418;
  *(undefined4 *)(param_1 + 0xcd) = *(undefined4 *)(param_2 + 0x668);
  param_1[0xc9] = (long)(puVar8 + 0x10);
  uVar6 = *(undefined4 *)(param_2 + 0x670);
  param_1[0xcf] = (long)puVar1;
  *(undefined4 *)(param_1 + 0xce) = uVar6;
  puVar8 = PTR__ZTV22CParameterPropertyBaseILj198EE_02cc0c68;
  param_1[0xd0] = *(long *)(param_2 + 0x680);
  param_1[0xcf] = (long)(puVar8 + 0x10);
  uVar7 = *(undefined1 *)(param_2 + 0x688);
  param_1[0xd2] = (long)puVar2;
  *(undefined1 *)(param_1 + 0xd1) = uVar7;
  puVar8 = PTR__ZTV23CParameterPropertyValueIfLj198E18CPropertyConverterE_02cb8e90;
  *(undefined4 *)(param_1 + 0xd3) = *(undefined4 *)(param_2 + 0x698);
  param_1[0xcf] = (long)(puVar8 + 0x10);
  uVar6 = *(undefined4 *)(param_2 + 0x6a0);
  param_1[0xd5] = (long)puVar1;
  *(undefined4 *)(param_1 + 0xd4) = uVar6;
  puVar8 = PTR__ZTV22CParameterPropertyBaseILj200EE_02cbc5b0;
  param_1[0xd6] = *(long *)(param_2 + 0x6b0);
  param_1[0xd5] = (long)(puVar8 + 0x10);
  uVar7 = *(undefined1 *)(param_2 + 0x6b8);
  param_1[0xd8] = (long)puVar2;
  *(undefined1 *)(param_1 + 0xd7) = uVar7;
  puVar8 = PTR__ZTV23CParameterPropertyValueIjLj200E18CPropertyConverterE_02cbf2d0;
  *(undefined4 *)(param_1 + 0xd9) = *(undefined4 *)(param_2 + 0x6c8);
  param_1[0xd5] = (long)(puVar8 + 0x10);
  uVar6 = *(undefined4 *)(param_2 + 0x6d0);
  param_1[0xdb] = (long)puVar1;
  *(undefined4 *)(param_1 + 0xda) = uVar6;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj201EE_02cc3250;
  param_1[0xdc] = *(long *)(param_2 + 0x6e0);
  param_1[0xdb] = (long)(puVar1 + 0x10);
  puVar1 = 
  PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj201EE_02cb6ee0
  ;
  uVar7 = *(undefined1 *)(param_2 + 0x6e8);
  param_1[0xde] = (long)puVar2;
  *(undefined1 *)(param_1 + 0xdd) = uVar7;
  uVar6 = *(undefined4 *)(param_2 + 0x6f8);
  param_1[0xdb] = (long)(puVar1 + 0x10);
  param_1[0xe2] = 0;
  param_1[0xe1] = 0;
  *(undefined4 *)(param_1 + 0xdf) = uVar6;
  param_1[0xe0] = 0;
  if ((*(byte *)(param_2 + 0x700) & 1) == 0) {
    param_1[0xe2] = *(long *)(param_2 + 0x710);
    lVar11 = *(long *)(param_2 + 0x700);
    param_1[0xe1] = *(long *)(param_2 + 0x708);
    param_1[0xe0] = lVar11;
  }
  else {
    uVar13 = *(ulong *)(param_2 + 0x708);
    uVar14 = *(undefined8 *)(param_2 + 0x710);
    if (uVar13 < 0x17) {
      lVar11 = (long)param_1 + 0x701;
      *(char *)(param_1 + 0xe0) = (char)(uVar13 << 1);
      if (uVar13 != 0) goto code_r0x0149b00c;
    }
    else {
      uVar15 = uVar13 + 0x10 & 0xfffffffffffffff0;
      if (uVar15 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
      }
      lVar11 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar15,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
      if (lVar11 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
      }
      param_1[0xe2] = lVar11;
      param_1[0xe0] = uVar15 | 1;
      param_1[0xe1] = uVar13;
code_r0x0149b00c:
      memcpy(lVar11,uVar14,uVar13);
    }
    *(undefined1 *)(lVar11 + uVar13) = 0;
  }
  puVar1 = puVar3 + 0x10;
  param_1[0xe3] = (long)puVar1;
  puVar2 = PTR__ZTV22CParameterPropertyBaseILj202EE_02cbef50;
  param_1[0xe4] = *(long *)(param_2 + 0x720);
  param_1[0xe3] = (long)(puVar2 + 0x10);
  uVar7 = *(undefined1 *)(param_2 + 0x728);
  puVar2 = puVar4 + 0x10;
  param_1[0xe6] = (long)puVar2;
  *(undefined1 *)(param_1 + 0xe5) = uVar7;
  puVar8 = PTR__ZTV23CParameterPropertyValueIjLj202E18CPropertyConverterE_02cbef10;
  *(undefined4 *)(param_1 + 0xe7) = *(undefined4 *)(param_2 + 0x738);
  param_1[0xe3] = (long)(puVar8 + 0x10);
  uVar6 = *(undefined4 *)(param_2 + 0x740);
  param_1[0xe9] = (long)puVar1;
  *(undefined4 *)(param_1 + 0xe8) = uVar6;
  puVar8 = PTR__ZTV22CParameterPropertyBaseILj203EE_02cb83f0;
  param_1[0xea] = *(long *)(param_2 + 0x750);
  param_1[0xe9] = (long)(puVar8 + 0x10);
  uVar7 = *(undefined1 *)(param_2 + 0x758);
  param_1[0xec] = (long)puVar2;
  *(undefined1 *)(param_1 + 0xeb) = uVar7;
  puVar8 = PTR__ZTV23CParameterPropertyValueIjLj203E18CPropertyConverterE_02cc3330;
  *(undefined4 *)(param_1 + 0xed) = *(undefined4 *)(param_2 + 0x768);
  param_1[0xe9] = (long)(puVar8 + 0x10);
  uVar6 = *(undefined4 *)(param_2 + 0x770);
  param_1[0xef] = (long)puVar1;
  *(undefined4 *)(param_1 + 0xee) = uVar6;
  puVar8 = PTR__ZTV22CParameterPropertyBaseILj205EE_02cbb3f0;
  param_1[0xf0] = *(long *)(param_2 + 0x780);
  param_1[0xef] = (long)(puVar8 + 0x10);
  uVar7 = *(undefined1 *)(param_2 + 0x788);
  param_1[0xf2] = (long)puVar2;
  *(undefined1 *)(param_1 + 0xf1) = uVar7;
  puVar8 = PTR__ZTV23CParameterPropertyValueIjLj205E18CPropertyConverterE_02cbdcf0;
  *(undefined4 *)(param_1 + 0xf3) = *(undefined4 *)(param_2 + 0x798);
  param_1[0xef] = (long)(puVar8 + 0x10);
  uVar6 = *(undefined4 *)(param_2 + 0x7a0);
  param_1[0xf5] = (long)puVar1;
  *(undefined4 *)(param_1 + 0xf4) = uVar6;
  puVar8 = PTR__ZTV22CParameterPropertyBaseILj207EE_02cb6b28;
  param_1[0xf6] = *(long *)(param_2 + 0x7b0);
  param_1[0xf5] = (long)(puVar8 + 0x10);
  uVar7 = *(undefined1 *)(param_2 + 0x7b8);
  param_1[0xf8] = (long)puVar2;
  *(undefined1 *)(param_1 + 0xf7) = uVar7;
  puVar8 = PTR__ZTV23CParameterPropertyValueIjLj207E18CPropertyConverterE_02cb9b10;
  *(undefined4 *)(param_1 + 0xf9) = *(undefined4 *)(param_2 + 0x7c8);
  param_1[0xf5] = (long)(puVar8 + 0x10);
  uVar6 = *(undefined4 *)(param_2 + 2000);
  param_1[0xfb] = (long)puVar1;
  *(undefined4 *)(param_1 + 0xfa) = uVar6;
  puVar8 = PTR__ZTV22CParameterPropertyBaseILj208EE_02cb7680;
  param_1[0xfc] = *(long *)(param_2 + 0x7e0);
  param_1[0xfb] = (long)(puVar8 + 0x10);
  uVar7 = *(undefined1 *)(param_2 + 0x7e8);
  param_1[0xfe] = (long)puVar2;
  *(undefined1 *)(param_1 + 0xfd) = uVar7;
  puVar8 = PTR__ZTV23CParameterPropertyValueIjLj208E18CPropertyConverterE_02cb8c28;
  *(undefined4 *)(param_1 + 0xff) = *(undefined4 *)(param_2 + 0x7f8);
  param_1[0xfb] = (long)(puVar8 + 0x10);
  uVar6 = *(undefined4 *)(param_2 + 0x800);
  param_1[0x101] = (long)puVar1;
  *(undefined4 *)(param_1 + 0x100) = uVar6;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj209EE_02cc1c38;
  param_1[0x102] = *(long *)(param_2 + 0x810);
  param_1[0x101] = (long)(puVar1 + 0x10);
  puVar1 = 
  PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj209EE_02cba138
  ;
  uVar7 = *(undefined1 *)(param_2 + 0x818);
  param_1[0x104] = (long)puVar2;
  *(undefined1 *)(param_1 + 0x103) = uVar7;
  uVar6 = *(undefined4 *)(param_2 + 0x828);
  param_1[0x101] = (long)(puVar1 + 0x10);
  param_1[0x108] = 0;
  param_1[0x107] = 0;
  *(undefined4 *)(param_1 + 0x105) = uVar6;
  param_1[0x106] = 0;
  if ((*(byte *)(param_2 + 0x830) & 1) == 0) {
    param_1[0x108] = *(long *)(param_2 + 0x840);
    lVar11 = *(long *)(param_2 + 0x830);
    param_1[0x107] = *(long *)(param_2 + 0x838);
    param_1[0x106] = lVar11;
    goto code_r0x0149b29c;
  }
  uVar13 = *(ulong *)(param_2 + 0x838);
  uVar14 = *(undefined8 *)(param_2 + 0x840);
  if (uVar13 < 0x17) {
    lVar11 = (long)param_1 + 0x831;
    *(char *)(param_1 + 0x106) = (char)(uVar13 << 1);
    if (uVar13 != 0) goto code_r0x0149b288;
  }
  else {
    uVar15 = uVar13 + 0x10 & 0xfffffffffffffff0;
    if (uVar15 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
    }
    lVar11 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar15,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
    if (lVar11 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    }
    param_1[0x108] = lVar11;
    param_1[0x106] = uVar15 | 1;
    param_1[0x107] = uVar13;
code_r0x0149b288:
    memcpy(lVar11,uVar14,uVar13);
  }
  *(undefined1 *)(lVar11 + uVar13) = 0;
code_r0x0149b29c:
  puVar3 = puVar3 + 0x10;
  param_1[0x109] = (long)puVar3;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj210EE_02cbf870;
  puVar4 = puVar4 + 0x10;
  puVar5 = puVar5 + 0x10;
  param_1[0x10a] = *(long *)(param_2 + 0x850);
  param_1[0x109] = (long)(puVar1 + 0x10);
  uVar7 = *(undefined1 *)(param_2 + 0x858);
  param_1[0x10c] = (long)puVar4;
  *(undefined1 *)(param_1 + 0x10b) = uVar7;
  puVar1 = PTR__ZTV23CParameterPropertyValueIjLj210E18CPropertyConverterE_02cc4330;
  *(undefined4 *)(param_1 + 0x10d) = *(undefined4 *)(param_2 + 0x868);
  param_1[0x109] = (long)(puVar1 + 0x10);
  uVar6 = *(undefined4 *)(param_2 + 0x870);
  param_1[0x10f] = (long)puVar3;
  *(undefined4 *)(param_1 + 0x10e) = uVar6;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj211EE_02cc28b0;
  param_1[0x110] = *(long *)(param_2 + 0x880);
  param_1[0x10f] = (long)(puVar1 + 0x10);
  uVar7 = *(undefined1 *)(param_2 + 0x888);
  param_1[0x112] = (long)puVar4;
  *(undefined1 *)(param_1 + 0x111) = uVar7;
  puVar1 = PTR__ZTV23CParameterPropertyValueIjLj211E18CPropertyConverterE_02cb7058;
  *(undefined4 *)(param_1 + 0x113) = *(undefined4 *)(param_2 + 0x898);
  param_1[0x10f] = (long)(puVar1 + 0x10);
  uVar6 = *(undefined4 *)(param_2 + 0x8a0);
  param_1[0x115] = (long)puVar3;
  *(undefined4 *)(param_1 + 0x114) = uVar6;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj212EE_02cbbc90;
  param_1[0x116] = *(long *)(param_2 + 0x8b0);
  param_1[0x115] = (long)(puVar1 + 0x10);
  uVar7 = *(undefined1 *)(param_2 + 0x8b8);
  param_1[0x118] = (long)puVar4;
  *(undefined1 *)(param_1 + 0x117) = uVar7;
  puVar1 = PTR__ZTV23CParameterPropertyValueIjLj212E18CPropertyConverterE_02cbb0d8;
  *(undefined4 *)(param_1 + 0x119) = *(undefined4 *)(param_2 + 0x8c8);
  param_1[0x115] = (long)(puVar1 + 0x10);
  uVar6 = *(undefined4 *)(param_2 + 0x8d0);
  param_1[0x11b] = (long)puVar3;
  *(undefined4 *)(param_1 + 0x11a) = uVar6;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj214EE_02cb7ad8;
  param_1[0x11c] = *(long *)(param_2 + 0x8e0);
  param_1[0x11b] = (long)(puVar1 + 0x10);
  uVar7 = *(undefined1 *)(param_2 + 0x8e8);
  param_1[0x11e] = (long)puVar4;
  *(undefined1 *)(param_1 + 0x11d) = uVar7;
  puVar1 = PTR__ZTV23CParameterPropertyValueIjLj214E18CPropertyConverterE_02cb9230;
  *(undefined4 *)(param_1 + 0x11f) = *(undefined4 *)(param_2 + 0x8f8);
  param_1[0x11b] = (long)(puVar1 + 0x10);
  uVar6 = *(undefined4 *)(param_2 + 0x900);
  param_1[0x121] = (long)puVar3;
  *(undefined4 *)(param_1 + 0x120) = uVar6;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj215EE_02cbe558;
  param_1[0x122] = *(long *)(param_2 + 0x910);
  param_1[0x121] = (long)(puVar1 + 0x10);
  uVar7 = *(undefined1 *)(param_2 + 0x918);
  param_1[0x124] = (long)puVar4;
  *(undefined1 *)(param_1 + 0x123) = uVar7;
  puVar1 = PTR__ZTV23CParameterPropertyValueIjLj215E18CPropertyConverterE_02cb8d88;
  *(undefined4 *)(param_1 + 0x125) = *(undefined4 *)(param_2 + 0x928);
  param_1[0x121] = (long)(puVar1 + 0x10);
  uVar6 = *(undefined4 *)(param_2 + 0x930);
  param_1[0x127] = (long)puVar3;
  *(undefined4 *)(param_1 + 0x126) = uVar6;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj216EE_02cc16a8;
  param_1[0x128] = *(long *)(param_2 + 0x940);
  param_1[0x127] = (long)(puVar1 + 0x10);
  uVar7 = *(undefined1 *)(param_2 + 0x948);
  param_1[0x12a] = (long)puVar4;
  *(undefined1 *)(param_1 + 0x129) = uVar7;
  puVar1 = PTR__ZTV23CParameterPropertyValueIjLj216E18CPropertyConverterE_02cc47f0;
  *(undefined4 *)(param_1 + 299) = *(undefined4 *)(param_2 + 0x958);
  param_1[0x127] = (long)(puVar1 + 0x10);
  uVar6 = *(undefined4 *)(param_2 + 0x960);
  param_1[0x12d] = (long)puVar3;
  *(undefined4 *)(param_1 + 300) = uVar6;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj218EE_02cbe370;
  param_1[0x12e] = *(long *)(param_2 + 0x970);
  param_1[0x12d] = (long)(puVar1 + 0x10);
  uVar7 = *(undefined1 *)(param_2 + 0x978);
  param_1[0x130] = (long)puVar4;
  *(undefined1 *)(param_1 + 0x12f) = uVar7;
  puVar1 = PTR__ZTV23CParameterPropertyValueIjLj218E18CPropertyConverterE_02cbe2c0;
  *(undefined4 *)(param_1 + 0x131) = *(undefined4 *)(param_2 + 0x988);
  param_1[0x12d] = (long)(puVar1 + 0x10);
  uVar6 = *(undefined4 *)(param_2 + 0x990);
  param_1[0x133] = (long)puVar3;
  *(undefined4 *)(param_1 + 0x132) = uVar6;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj219EE_02cbbca8;
  param_1[0x134] = *(long *)(param_2 + 0x9a0);
  param_1[0x133] = (long)(puVar1 + 0x10);
  uVar7 = *(undefined1 *)(param_2 + 0x9a8);
  param_1[0x136] = (long)puVar4;
  *(undefined1 *)(param_1 + 0x135) = uVar7;
  puVar1 = PTR__ZTV23CParameterPropertyValueIjLj219E18CPropertyConverterE_02cc2f70;
  *(undefined4 *)(param_1 + 0x137) = *(undefined4 *)(param_2 + 0x9b8);
  param_1[0x133] = (long)(puVar1 + 0x10);
  uVar6 = *(undefined4 *)(param_2 + 0x9c0);
  param_1[0x139] = (long)puVar3;
  *(undefined4 *)(param_1 + 0x138) = uVar6;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj220EE_02cb7ab0;
  param_1[0x13a] = *(long *)(param_2 + 0x9d0);
  param_1[0x139] = (long)(puVar1 + 0x10);
  uVar7 = *(undefined1 *)(param_2 + 0x9d8);
  param_1[0x13c] = (long)puVar4;
  *(undefined1 *)(param_1 + 0x13b) = uVar7;
  puVar1 = PTR__ZTV23CParameterPropertyValueIjLj220E18CPropertyConverterE_02cb7fb8;
  *(undefined4 *)(param_1 + 0x13d) = *(undefined4 *)(param_2 + 0x9e8);
  param_1[0x139] = (long)(puVar1 + 0x10);
  uVar6 = *(undefined4 *)(param_2 + 0x9f0);
  param_1[0x13f] = (long)puVar3;
  *(undefined4 *)(param_1 + 0x13e) = uVar6;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj221EE_02cbf5d8;
  param_1[0x140] = *(long *)(param_2 + 0xa00);
  param_1[0x13f] = (long)(puVar1 + 0x10);
  uVar7 = *(undefined1 *)(param_2 + 0xa08);
  param_1[0x142] = (long)puVar4;
  *(undefined1 *)(param_1 + 0x141) = uVar7;
  puVar1 = PTR__ZTV23CParameterPropertyValueIjLj221E18CPropertyConverterE_02cc1d68;
  *(undefined4 *)(param_1 + 0x143) = *(undefined4 *)(param_2 + 0xa18);
  param_1[0x13f] = (long)(puVar1 + 0x10);
  uVar6 = *(undefined4 *)(param_2 + 0xa20);
  param_1[0x145] = (long)puVar3;
  *(undefined4 *)(param_1 + 0x144) = uVar6;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj222EE_02cbe6b8;
  param_1[0x146] = *(long *)(param_2 + 0xa30);
  param_1[0x145] = (long)(puVar1 + 0x10);
  uVar7 = *(undefined1 *)(param_2 + 0xa38);
  param_1[0x148] = (long)puVar4;
  *(undefined1 *)(param_1 + 0x147) = uVar7;
  puVar1 = PTR__ZTV23CParameterPropertyValueIjLj222E18CPropertyConverterE_02cbe898;
  *(undefined4 *)(param_1 + 0x149) = *(undefined4 *)(param_2 + 0xa48);
  param_1[0x145] = (long)(puVar1 + 0x10);
  uVar6 = *(undefined4 *)(param_2 + 0xa50);
  param_1[0x14b] = (long)puVar3;
  *(undefined4 *)(param_1 + 0x14a) = uVar6;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj224EE_02cba9c0;
  param_1[0x14c] = *(long *)(param_2 + 0xa60);
  param_1[0x14b] = (long)(puVar1 + 0x10);
  uVar7 = *(undefined1 *)(param_2 + 0xa68);
  param_1[0x14e] = (long)puVar4;
  *(undefined1 *)(param_1 + 0x14d) = uVar7;
  puVar1 = PTR__ZTV23CParameterPropertyValueIbLj224E18CPropertyConverterE_02cc40a8;
  *(undefined4 *)(param_1 + 0x14f) = *(undefined4 *)(param_2 + 0xa78);
  param_1[0x14b] = (long)(puVar1 + 0x10);
  uVar7 = *(undefined1 *)(param_2 + 0xa80);
  param_1[0x151] = (long)puVar3;
  *(undefined1 *)(param_1 + 0x150) = uVar7;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj225EE_02cbddf0;
  param_1[0x152] = *(long *)(param_2 + 0xa90);
  param_1[0x151] = (long)(puVar1 + 0x10);
  uVar7 = *(undefined1 *)(param_2 + 0xa98);
  param_1[0x154] = (long)puVar4;
  *(undefined1 *)(param_1 + 0x153) = uVar7;
  puVar1 = PTR__ZTV23CParameterPropertyValueIbLj225E18CPropertyConverterE_02cc07f8;
  *(undefined4 *)(param_1 + 0x155) = *(undefined4 *)(param_2 + 0xaa8);
  param_1[0x151] = (long)(puVar1 + 0x10);
  uVar7 = *(undefined1 *)(param_2 + 0xab0);
  param_1[0x157] = (long)puVar3;
  *(undefined1 *)(param_1 + 0x156) = uVar7;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj226EE_02cbea60;
  param_1[0x158] = *(long *)(param_2 + 0xac0);
  param_1[0x157] = (long)(puVar1 + 0x10);
  uVar7 = *(undefined1 *)(param_2 + 0xac8);
  param_1[0x15a] = (long)puVar4;
  *(undefined1 *)(param_1 + 0x159) = uVar7;
  puVar1 = PTR__ZTV23CParameterPropertyValueIjLj226E18CPropertyConverterE_02cbc950;
  *(undefined4 *)(param_1 + 0x15b) = *(undefined4 *)(param_2 + 0xad8);
  param_1[0x157] = (long)(puVar1 + 0x10);
  uVar6 = *(undefined4 *)(param_2 + 0xae0);
  param_1[0x15d] = (long)puVar3;
  *(undefined4 *)(param_1 + 0x15c) = uVar6;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj228EE_02cbf5e8;
  param_1[0x15e] = *(long *)(param_2 + 0xaf0);
  param_1[0x15d] = (long)(puVar1 + 0x10);
  uVar7 = *(undefined1 *)(param_2 + 0xaf8);
  param_1[0x160] = (long)puVar4;
  *(undefined1 *)(param_1 + 0x15f) = uVar7;
  puVar1 = PTR__ZTV23CParameterPropertyValueIjLj228E18CPropertyConverterE_02cc2500;
  *(undefined4 *)(param_1 + 0x161) = *(undefined4 *)(param_2 + 0xb08);
  param_1[0x15d] = (long)(puVar1 + 0x10);
  uVar6 = *(undefined4 *)(param_2 + 0xb10);
  param_1[0x163] = (long)puVar3;
  *(undefined4 *)(param_1 + 0x162) = uVar6;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj229EE_02cba790;
  param_1[0x164] = *(long *)(param_2 + 0xb20);
  param_1[0x163] = (long)(puVar1 + 0x10);
  uVar7 = *(undefined1 *)(param_2 + 0xb28);
  param_1[0x166] = (long)puVar4;
  *(undefined1 *)(param_1 + 0x165) = uVar7;
  puVar1 = PTR__ZTV23CParameterPropertyValueIjLj229E18CPropertyConverterE_02cc4cc8;
  *(undefined4 *)(param_1 + 0x167) = *(undefined4 *)(param_2 + 0xb38);
  param_1[0x163] = (long)(puVar1 + 0x10);
  uVar6 = *(undefined4 *)(param_2 + 0xb40);
  param_1[0x169] = (long)puVar3;
  *(undefined4 *)(param_1 + 0x168) = uVar6;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj230EE_02cc3050;
  param_1[0x16a] = *(long *)(param_2 + 0xb50);
  param_1[0x169] = (long)(puVar1 + 0x10);
  uVar7 = *(undefined1 *)(param_2 + 0xb58);
  param_1[0x16c] = (long)puVar4;
  *(undefined1 *)(param_1 + 0x16b) = uVar7;
  puVar1 = PTR__ZTV23CParameterPropertyValueIjLj230E18CPropertyConverterE_02cbe4b8;
  *(undefined4 *)(param_1 + 0x16d) = *(undefined4 *)(param_2 + 0xb68);
  param_1[0x169] = (long)(puVar1 + 0x10);
  uVar6 = *(undefined4 *)(param_2 + 0xb70);
  param_1[0x16f] = (long)puVar3;
  *(undefined4 *)(param_1 + 0x16e) = uVar6;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj231EE_02cc1ee0;
  param_1[0x170] = *(long *)(param_2 + 0xb80);
  param_1[0x16f] = (long)(puVar1 + 0x10);
  uVar7 = *(undefined1 *)(param_2 + 0xb88);
  param_1[0x172] = (long)puVar4;
  *(undefined1 *)(param_1 + 0x171) = uVar7;
  puVar1 = PTR__ZTV23CParameterPropertyValueIjLj231E18CPropertyConverterE_02cc2d08;
  *(undefined4 *)(param_1 + 0x173) = *(undefined4 *)(param_2 + 0xb98);
  param_1[0x16f] = (long)(puVar1 + 0x10);
  uVar6 = *(undefined4 *)(param_2 + 0xba0);
  param_1[0x175] = (long)puVar3;
  *(undefined4 *)(param_1 + 0x174) = uVar6;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj232EE_02cbee90;
  param_1[0x176] = *(long *)(param_2 + 0xbb0);
  param_1[0x175] = (long)(puVar1 + 0x10);
  uVar7 = *(undefined1 *)(param_2 + 3000);
  param_1[0x178] = (long)puVar4;
  *(undefined1 *)(param_1 + 0x177) = uVar7;
  puVar1 = PTR__ZTV23CParameterPropertyValueIjLj232E18CPropertyConverterE_02cc05f8;
  *(undefined4 *)(param_1 + 0x179) = *(undefined4 *)(param_2 + 0xbc8);
  param_1[0x175] = (long)(puVar1 + 0x10);
  uVar6 = *(undefined4 *)(param_2 + 0xbd0);
  param_1[0x17b] = (long)puVar3;
  *(undefined4 *)(param_1 + 0x17a) = uVar6;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj233EE_02cb7178;
  param_1[0x17c] = *(long *)(param_2 + 0xbe0);
  param_1[0x17b] = (long)(puVar1 + 0x10);
  uVar7 = *(undefined1 *)(param_2 + 0xbe8);
  param_1[0x17e] = (long)puVar4;
  *(undefined1 *)(param_1 + 0x17d) = uVar7;
  puVar1 = PTR__ZTV23CParameterPropertyValueIjLj233E18CPropertyConverterE_02cbe3e0;
  *(undefined4 *)(param_1 + 0x17f) = *(undefined4 *)(param_2 + 0xbf8);
  param_1[0x17b] = (long)(puVar1 + 0x10);
  uVar6 = *(undefined4 *)(param_2 + 0xc00);
  param_1[0x181] = (long)puVar3;
  *(undefined4 *)(param_1 + 0x180) = uVar6;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj234EE_02cba3b8;
  param_1[0x182] = *(long *)(param_2 + 0xc10);
  param_1[0x181] = (long)(puVar1 + 0x10);
  uVar7 = *(undefined1 *)(param_2 + 0xc18);
  param_1[0x184] = (long)puVar4;
  *(undefined1 *)(param_1 + 0x183) = uVar7;
  puVar1 = PTR__ZTV23CParameterPropertyValueIjLj234E18CPropertyConverterE_02cc2bd0;
  *(undefined4 *)(param_1 + 0x185) = *(undefined4 *)(param_2 + 0xc28);
  param_1[0x181] = (long)(puVar1 + 0x10);
  uVar6 = *(undefined4 *)(param_2 + 0xc30);
  param_1[0x187] = (long)puVar3;
  *(undefined4 *)(param_1 + 0x186) = uVar6;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj236EE_02cb7068;
  param_1[0x188] = *(long *)(param_2 + 0xc40);
  param_1[0x187] = (long)(puVar1 + 0x10);
  uVar7 = *(undefined1 *)(param_2 + 0xc48);
  param_1[0x18a] = (long)puVar4;
  *(undefined1 *)(param_1 + 0x189) = uVar7;
  puVar1 = PTR__ZTV23CParameterPropertyValueIjLj236E18CPropertyConverterE_02cc2178;
  *(undefined4 *)(param_1 + 0x18b) = *(undefined4 *)(param_2 + 0xc58);
  param_1[0x187] = (long)(puVar1 + 0x10);
  uVar6 = *(undefined4 *)(param_2 + 0xc60);
  param_1[0x18d] = (long)puVar3;
  *(undefined4 *)(param_1 + 0x18c) = uVar6;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj238EE_02cb6ed0;
  param_1[0x18e] = *(long *)(param_2 + 0xc70);
  param_1[0x18d] = (long)(puVar1 + 0x10);
  uVar7 = *(undefined1 *)(param_2 + 0xc78);
  param_1[400] = (long)puVar4;
  *(undefined1 *)(param_1 + 399) = uVar7;
  puVar1 = PTR__ZTV23CParameterPropertyValueIjLj238E18CPropertyConverterE_02cbdb78;
  *(undefined4 *)(param_1 + 0x191) = *(undefined4 *)(param_2 + 0xc88);
  param_1[0x18d] = (long)(puVar1 + 0x10);
  uVar6 = *(undefined4 *)(param_2 + 0xc90);
  param_1[0x193] = (long)puVar3;
  *(undefined4 *)(param_1 + 0x192) = uVar6;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj239EE_02cbedf0;
  param_1[0x194] = *(long *)(param_2 + 0xca0);
  param_1[0x193] = (long)(puVar1 + 0x10);
  uVar7 = *(undefined1 *)(param_2 + 0xca8);
  param_1[0x196] = (long)puVar4;
  *(undefined1 *)(param_1 + 0x195) = uVar7;
  puVar1 = PTR__ZTV23CParameterPropertyValueIjLj239E18CPropertyConverterE_02cb84c8;
  *(undefined4 *)(param_1 + 0x197) = *(undefined4 *)(param_2 + 0xcb8);
  param_1[0x193] = (long)(puVar1 + 0x10);
  uVar6 = *(undefined4 *)(param_2 + 0xcc0);
  param_1[0x199] = (long)puVar3;
  *(undefined4 *)(param_1 + 0x198) = uVar6;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj240EE_02cc1fa0;
  param_1[0x19a] = *(long *)(param_2 + 0xcd0);
  param_1[0x199] = (long)(puVar1 + 0x10);
  uVar7 = *(undefined1 *)(param_2 + 0xcd8);
  param_1[0x19c] = (long)puVar4;
  *(undefined1 *)(param_1 + 0x19b) = uVar7;
  puVar1 = PTR__ZTV23CParameterPropertyValueIjLj240E18CPropertyConverterE_02cbeba0;
  *(undefined4 *)(param_1 + 0x19d) = *(undefined4 *)(param_2 + 0xce8);
  param_1[0x199] = (long)(puVar1 + 0x10);
  uVar6 = *(undefined4 *)(param_2 + 0xcf0);
  param_1[0x19f] = (long)puVar3;
  *(undefined4 *)(param_1 + 0x19e) = uVar6;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj242EE_02cc2db0;
  param_1[0x1a0] = *(long *)(param_2 + 0xd00);
  param_1[0x19f] = (long)(puVar1 + 0x10);
  uVar7 = *(undefined1 *)(param_2 + 0xd08);
  param_1[0x1a2] = (long)puVar4;
  *(undefined1 *)(param_1 + 0x1a1) = uVar7;
  puVar1 = PTR__ZTV23CParameterPropertyValueIbLj242E18CPropertyConverterE_02cc1718;
  *(undefined4 *)(param_1 + 0x1a3) = *(undefined4 *)(param_2 + 0xd18);
  param_1[0x19f] = (long)(puVar1 + 0x10);
  uVar7 = *(undefined1 *)(param_2 + 0xd20);
  param_1[0x1a5] = (long)puVar3;
  *(undefined1 *)(param_1 + 0x1a4) = uVar7;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj243EE_02cbc5c0;
  param_1[0x1a6] = *(long *)(param_2 + 0xd30);
  param_1[0x1a5] = (long)(puVar1 + 0x10);
  uVar7 = *(undefined1 *)(param_2 + 0xd38);
  param_1[0x1a8] = (long)puVar4;
  *(undefined1 *)(param_1 + 0x1a7) = uVar7;
  puVar1 = PTR__ZTV23CParameterPropertyValueIjLj243E18CPropertyConverterE_02cb95c8;
  *(undefined4 *)(param_1 + 0x1a9) = *(undefined4 *)(param_2 + 0xd48);
  param_1[0x1a5] = (long)(puVar1 + 0x10);
  uVar6 = *(undefined4 *)(param_2 + 0xd50);
  param_1[0x1ab] = (long)puVar3;
  *(undefined4 *)(param_1 + 0x1aa) = uVar6;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj244EE_02cc32b0;
  param_1[0x1ac] = *(long *)(param_2 + 0xd60);
  param_1[0x1ab] = (long)(puVar1 + 0x10);
  uVar7 = *(undefined1 *)(param_2 + 0xd68);
  param_1[0x1ae] = (long)puVar4;
  *(undefined1 *)(param_1 + 0x1ad) = uVar7;
  puVar1 = PTR__ZTV23CParameterPropertyValueIjLj244E18CPropertyConverterE_02cb9768;
  *(undefined4 *)(param_1 + 0x1af) = *(undefined4 *)(param_2 + 0xd78);
  param_1[0x1ab] = (long)(puVar1 + 0x10);
  uVar6 = *(undefined4 *)(param_2 + 0xd80);
  param_1[0x1b1] = (long)puVar3;
  *(undefined4 *)(param_1 + 0x1b0) = uVar6;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj245EE_02cbef20;
  param_1[0x1b2] = *(long *)(param_2 + 0xd90);
  param_1[0x1b1] = (long)(puVar1 + 0x10);
  uVar7 = *(undefined1 *)(param_2 + 0xd98);
  param_1[0x1b4] = (long)puVar4;
  *(undefined1 *)(param_1 + 0x1b3) = uVar7;
  puVar1 = PTR__ZTV23CParameterPropertyValueIjLj245E18CPropertyConverterE_02cbf180;
  *(undefined4 *)(param_1 + 0x1b5) = *(undefined4 *)(param_2 + 0xda8);
  param_1[0x1b1] = (long)(puVar1 + 0x10);
  uVar6 = *(undefined4 *)(param_2 + 0xdb0);
  param_1[0x1b7] = (long)puVar3;
  *(undefined4 *)(param_1 + 0x1b6) = uVar6;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj247EE_02cb7350;
  param_1[0x1b8] = *(long *)(param_2 + 0xdc0);
  param_1[0x1b7] = (long)(puVar1 + 0x10);
  uVar7 = *(undefined1 *)(param_2 + 0xdc8);
  param_1[0x1ba] = (long)puVar4;
  *(undefined1 *)(param_1 + 0x1b9) = uVar7;
  puVar1 = PTR__ZTV23CParameterPropertyValueIjLj247E18CPropertyConverterE_02cbf148;
  *(undefined4 *)(param_1 + 0x1bb) = *(undefined4 *)(param_2 + 0xdd8);
  param_1[0x1b7] = (long)(puVar1 + 0x10);
  uVar6 = *(undefined4 *)(param_2 + 0xde0);
  param_1[0x1bd] = (long)puVar3;
  *(undefined4 *)(param_1 + 0x1bc) = uVar6;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj248EE_02cbb3a0;
  param_1[0x1be] = *(long *)(param_2 + 0xdf0);
  param_1[0x1bd] = (long)(puVar1 + 0x10);
  uVar7 = *(undefined1 *)(param_2 + 0xdf8);
  param_1[0x1c0] = (long)puVar4;
  *(undefined1 *)(param_1 + 0x1bf) = uVar7;
  puVar1 = PTR__ZTV23CParameterPropertyValueIjLj248E18CPropertyConverterE_02cc34e0;
  *(undefined4 *)(param_1 + 0x1c1) = *(undefined4 *)(param_2 + 0xe08);
  param_1[0x1bd] = (long)(puVar1 + 0x10);
  uVar6 = *(undefined4 *)(param_2 + 0xe10);
  param_1[0x1c3] = (long)puVar3;
  *(undefined4 *)(param_1 + 0x1c2) = uVar6;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj249EE_02cc1d38;
  param_1[0x1c4] = *(long *)(param_2 + 0xe20);
  param_1[0x1c3] = (long)(puVar1 + 0x10);
  uVar7 = *(undefined1 *)(param_2 + 0xe28);
  param_1[0x1c6] = (long)puVar4;
  *(undefined1 *)(param_1 + 0x1c5) = uVar7;
  puVar1 = PTR__ZTV23CParameterPropertyValueIjLj249E18CPropertyConverterE_02cba140;
  *(undefined4 *)(param_1 + 0x1c7) = *(undefined4 *)(param_2 + 0xe38);
  param_1[0x1c3] = (long)(puVar1 + 0x10);
  uVar6 = *(undefined4 *)(param_2 + 0xe40);
  param_1[0x1c9] = (long)puVar5;
  *(undefined4 *)(param_1 + 0x1c8) = uVar6;
  Framework::CSTLMap<unsigned int, IParameterProperty*>::CSTLMap(Framework::CSTLMap<unsigned int, IParameterProperty*> const&)(param_1 + 0x1ca,param_2 + 0xe50);
  Framework::CSTLMap<unsigned int, InfoBase*>::CSTLMap(Framework::CSTLMap<unsigned int, InfoBase*> const&)(param_1 + 0x1cd,param_2 + 0xe68);
  puVar1 = PTR__ZTV16AssistDetailInfo_02cc23a8;
  param_1[0x1d0] = (long)puVar3;
  param_1[0x1c9] = (long)(puVar1 + 0x10);
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj20EE_02cc0d08;
  param_1[0x1d1] = *(long *)(param_2 + 0xe88);
  param_1[0x1d0] = (long)(puVar1 + 0x10);
  uVar7 = *(undefined1 *)(param_2 + 0xe90);
  param_1[0x1d3] = (long)puVar4;
  *(undefined1 *)(param_1 + 0x1d2) = uVar7;
  puVar1 = PTR__ZTV23CParameterPropertyValueIjLj20E18CPropertyConverterE_02cc2ce0;
  *(undefined4 *)(param_1 + 0x1d4) = *(undefined4 *)(param_2 + 0xea0);
  param_1[0x1d0] = (long)(puVar1 + 0x10);
  uVar6 = *(undefined4 *)(param_2 + 0xea8);
  param_1[0x1d6] = (long)puVar3;
  *(undefined4 *)(param_1 + 0x1d5) = uVar6;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj21EE_02cc1310;
  param_1[0x1d7] = *(long *)(param_2 + 0xeb8);
  param_1[0x1d6] = (long)(puVar1 + 0x10);
  uVar7 = *(undefined1 *)(param_2 + 0xec0);
  param_1[0x1d9] = (long)puVar4;
  *(undefined1 *)(param_1 + 0x1d8) = uVar7;
  puVar1 = PTR__ZTV23CParameterPropertyValueIjLj21E18CPropertyConverterE_02cbeae0;
  *(undefined4 *)(param_1 + 0x1da) = *(undefined4 *)(param_2 + 0xed0);
  param_1[0x1d6] = (long)(puVar1 + 0x10);
  uVar6 = *(undefined4 *)(param_2 + 0xed8);
  param_1[0x1dc] = (long)puVar3;
  *(undefined4 *)(param_1 + 0x1db) = uVar6;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj22EE_02cc4630;
  param_1[0x1dd] = *(long *)(param_2 + 0xee8);
  param_1[0x1dc] = (long)(puVar1 + 0x10);
  uVar7 = *(undefined1 *)(param_2 + 0xef0);
  param_1[0x1df] = (long)puVar4;
  *(undefined1 *)(param_1 + 0x1de) = uVar7;
  puVar1 = PTR__ZTV23CParameterPropertyValueIjLj22E18CPropertyConverterE_02cb7420;
  *(undefined4 *)(param_1 + 0x1e0) = *(undefined4 *)(param_2 + 0xf00);
  param_1[0x1dc] = (long)(puVar1 + 0x10);
  uVar6 = *(undefined4 *)(param_2 + 0xf08);
  param_1[0x1e2] = (long)puVar5;
  *(undefined4 *)(param_1 + 0x1e1) = uVar6;
  Framework::CSTLMap<unsigned int, IParameterProperty*>::CSTLMap(Framework::CSTLMap<unsigned int, IParameterProperty*> const&)(param_1 + 0x1e3,param_2 + 0xf18);
  Framework::CSTLMap<unsigned int, InfoBase*>::CSTLMap(Framework::CSTLMap<unsigned int, InfoBase*> const&)(param_1 + 0x1e6,param_2 + 0xf30);
  param_1[0x1eb] = 0;
  param_1[0x1ea] = 0;
  param_1[0x1e9] = (long)(param_1 + 0x1ea);
  if (*(long **)(param_2 + 0xf48) != (long *)(param_2 + 0xf50)) {
    plVar12 = *(long **)(param_2 + 0xf48);
    do {
      std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned long, CFactorInfo>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CFactorInfo>, void*>*, long> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CFactorInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CFactorInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CFactorInfo>, Framework::CSTLMapAllocatorInf> >::__emplace_hint_unique_key_args<unsigned long, std::__ndk1::pair<unsigned long const, CFactorInfo> const&>(std::__ndk1::__tree_const_iterator<std::__ndk1::__value_type<unsigned long, CFactorInfo>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CFactorInfo>, void*>*, long>, unsigned long const&, std::__ndk1::pair<unsigned long const, CFactorInfo> const&)(param_1 + 0x1e9,param_1 + 0x1ea,plVar12 + 4,plVar12 + 4);
      plVar9 = (long *)plVar12[1];
      if ((long *)plVar12[1] == (long *)0x0) {
        do {
          plVar16 = (long *)plVar12[2];
          bVar10 = (long *)*plVar16 != plVar12;
          plVar12 = plVar16;
        } while (bVar10);
      }
      else {
        do {
          plVar16 = plVar9;
          plVar9 = (long *)*plVar16;
        } while ((long *)*plVar16 != (long *)0x0);
      }
      plVar12 = plVar16;
    } while (plVar16 != (long *)(param_2 + 0xf50));
  }
  puVar1 = PTR__ZTV14CFactorInfoMap_02cb9808;
  param_1[0x1ec] = (long)puVar5;
  param_1[0x1e2] = (long)(puVar1 + 0x10);
  Framework::CSTLMap<unsigned int, IParameterProperty*>::CSTLMap(Framework::CSTLMap<unsigned int, IParameterProperty*> const&)(param_1 + 0x1ed,param_2 + 0xf68);
  Framework::CSTLMap<unsigned int, InfoBase*>::CSTLMap(Framework::CSTLMap<unsigned int, InfoBase*> const&)(param_1 + 0x1f0,param_2 + 0xf80);
  std::__ndk1::vector<CCharacterDecoObjectInfo, Framework::CSTLAllocator<CCharacterDecoObjectInfo, Framework::CSTLVectorAllocatorInf> >::vector(std::__ndk1::vector<CCharacterDecoObjectInfo, Framework::CSTLAllocator<CCharacterDecoObjectInfo, Framework::CSTLVectorAllocatorInf> > const&)(param_1 + 499,param_2 + 0xf98);
  puVar1 = PTR__ZTV28CCharacterDecoObjectInfoList_02cc4040;
  param_1[0x1f6] = (long)puVar5;
  param_1[0x1ec] = (long)(puVar1 + 0x10);
  Framework::CSTLMap<unsigned int, IParameterProperty*>::CSTLMap(Framework::CSTLMap<unsigned int, IParameterProperty*> const&)(param_1 + 0x1f7,param_2 + 0xfb8);
  Framework::CSTLMap<unsigned int, InfoBase*>::CSTLMap(Framework::CSTLMap<unsigned int, InfoBase*> const&)(param_1 + 0x1fa,param_2 + 0xfd0);
  std::__ndk1::vector<CParameterPropertyValue<unsigned int, 131u, CPropertyConverter>, Framework::CSTLAllocator<CParameterPropertyValue<unsigned int, 131u, CPropertyConverter>, Framework::CSTLVectorAllocatorInf> >::vector(std::__ndk1::vector<CParameterPropertyValue<unsigned int, 131u, CPropertyConverter>, Framework::CSTLAllocator<CParameterPropertyValue<unsigned int, 131u, CPropertyConverter>, Framework::CSTLVectorAllocatorInf> > const&)(param_1 + 0x1fd,param_2 + 0xfe8);
  param_1[0x1f6] = (long)(PTR__ZTV31UniverseEffectualTalentInfoList_02cc2e78 + 0x10);
  UniverseAddStatusInfo::UniverseAddStatusInfo(UniverseAddStatusInfo const&)(param_1 + 0x200,param_2 + 0x1000);
  UniverseDeityBoostInfo::UniverseDeityBoostInfo(UniverseDeityBoostInfo const&)(param_1 + 0x23d,param_2 + 0x11e8);
  param_1[0x27a] = (long)puVar5;
  Framework::CSTLMap<unsigned int, IParameterProperty*>::CSTLMap(Framework::CSTLMap<unsigned int, IParameterProperty*> const&)(param_1 + 0x27b,param_2 + 0x13d8);
  Framework::CSTLMap<unsigned int, InfoBase*>::CSTLMap(Framework::CSTLMap<unsigned int, InfoBase*> const&)(param_1 + 0x27e,param_2 + 0x13f0);
  puVar2 = PTR__ZTV9DeityInfo_02cc11d0;
  param_1[0x281] = (long)puVar3;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj47EE_02cba780;
  param_1[0x27a] = (long)(puVar2 + 0x10);
  lVar11 = *(long *)(param_2 + 0x1410);
  param_1[0x281] = (long)(puVar1 + 0x10);
  param_1[0x282] = lVar11;
  *(undefined1 *)(param_1 + 0x283) = *(undefined1 *)(param_2 + 0x1418);
  param_1[0x284] = (long)puVar4;
  puVar1 = PTR__ZTV23CParameterPropertyValueIjLj47E18CPropertyConverterE_02cc0678;
  *(undefined4 *)(param_1 + 0x285) = *(undefined4 *)(param_2 + 0x1428);
  param_1[0x281] = (long)(puVar1 + 0x10);
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj48EE_02cba0d0;
  uVar6 = *(undefined4 *)(param_2 + 0x1430);
  param_1[0x287] = (long)puVar3;
  *(undefined4 *)(param_1 + 0x286) = uVar6;
  lVar11 = *(long *)(param_2 + 0x1440);
  param_1[0x287] = (long)(puVar1 + 0x10);
  param_1[0x288] = lVar11;
  *(undefined1 *)(param_1 + 0x289) = *(undefined1 *)(param_2 + 0x1448);
  param_1[0x28a] = (long)puVar4;
  puVar1 = PTR__ZTV23CParameterPropertyValueIjLj48E18CPropertyConverterE_02cc4e68;
  *(undefined4 *)(param_1 + 0x28b) = *(undefined4 *)(param_2 + 0x1458);
  param_1[0x287] = (long)(puVar1 + 0x10);
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj49EE_02cc4550;
  uVar6 = *(undefined4 *)(param_2 + 0x1460);
  param_1[0x28d] = (long)puVar3;
  *(undefined4 *)(param_1 + 0x28c) = uVar6;
  lVar11 = *(long *)(param_2 + 0x1470);
  param_1[0x28d] = (long)(puVar1 + 0x10);
  param_1[0x28e] = lVar11;
  *(undefined1 *)(param_1 + 0x28f) = *(undefined1 *)(param_2 + 0x1478);
  param_1[0x290] = (long)puVar4;
  puVar1 = PTR__ZTV23CParameterPropertyValueIjLj49E18CPropertyConverterE_02cc0590;
  *(undefined4 *)(param_1 + 0x291) = *(undefined4 *)(param_2 + 0x1488);
  param_1[0x28d] = (long)(puVar1 + 0x10);
  *(undefined4 *)(param_1 + 0x292) = *(undefined4 *)(param_2 + 0x1490);
  UniverseDeityBoostInfo::UniverseDeityBoostInfo(UniverseDeityBoostInfo const&)(param_1 + 0x293,param_2 + 0x1498);
  param_1[0x293] = (long)(PTR__ZTV23AddBuffByDeityCharacter_02cc2950 + 0x10);
  lVar11 = *(long *)(param_2 + 0x1680);
  param_1[0x2d1] = *(long *)(param_2 + 0x1688);
  param_1[0x2d0] = lVar11;
  return;
}

// ==== void CPersonStatusInfo::Accept<_Serializer<SerializerImpl> >(_Serializer<SerializerImpl>&, unsigned int)
// vaddr 0x14aa7c4 | ghidra 0x15aa7c4 | size 2596 | symbol _ZN17CPersonStatusInfo6AcceptI11_SerializerI14SerializerImplEEEvRT_j | lib libSOA-3.7.0.so | 2026-10-08
void _ZN17CPersonStatusInfo6AcceptI11_SerializerI14SerializerImplEEEvRT_j
               (long param_1,long *param_2)

{
  ulong auStack_38 [3];
  
  auStack_38[0] = *(ulong *)(param_1 + 0x60);
  (**(code **)*param_2)(param_2,&UNK_027ffe64/*"id"*/);
  (**(code **)(*param_2 + 0x40))(param_2,auStack_38);
  auStack_38[0]._0_4_ = *(undefined4 *)(param_1 + 0x90);
  (**(code **)*param_2)(param_2,&UNK_028ea11e/*"player_id"*/);
  (**(code **)(*param_2 + 0x30))(param_2,auStack_38);
  auStack_38[0] = CONCAT44(auStack_38[0]._4_4_,*(undefined4 *)(param_1 + 0x100));
  (**(code **)*param_2)(param_2,&UNK_02846c65/*"player_level"*/);
  (**(code **)(*param_2 + 0x30))(param_2,auStack_38);
  auStack_38[1] = 0;
  auStack_38[2] = 0;
  auStack_38[0] = 0;
  void CParameterPropertyBase<165u>::CryptString<string >(string&, string const&)(auStack_38,param_1 + 0xc0);
  (**(code **)*param_2)(param_2,&UNK_02891dee/*"player_name"*/);
  (**(code **)(*param_2 + 0x58))(param_2,auStack_38);
  if ((auStack_38[0] & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(auStack_38[2]);
  }
  auStack_38[0] = CONCAT44(auStack_38[0]._4_4_,*(undefined4 *)(param_1 + 0x130));
  (**(code **)*param_2)(param_2,&UNK_0280cbe6/*"master_role_id"*/);
  (**(code **)(*param_2 + 0x30))(param_2,auStack_38);
  auStack_38[0] = *(ulong *)(param_1 + 0x160);
  (**(code **)*param_2)(param_2,&UNK_027fb1f1/*"weapon_item_id"*/);
  (**(code **)(*param_2 + 0x40))(param_2,auStack_38);
  auStack_38[0] = *(ulong *)(param_1 + 400);
  (**(code **)*param_2)(param_2,&UNK_027fb200/*"accessory_item_id"*/);
  (**(code **)(*param_2 + 0x40))(param_2,auStack_38);
  auStack_38[0]._0_4_ = *(undefined4 *)(param_1 + 0x1c0);
  (**(code **)*param_2)(param_2,&UNK_029d7bac/*"level"*/);
  (**(code **)(*param_2 + 0x30))(param_2,auStack_38);
  auStack_38[0]._0_4_ = *(undefined4 *)(param_1 + 0x1f0);
  (**(code **)*param_2)(param_2,&UNK_027fdbc8/*"exp"*/);
  (**(code **)(*param_2 + 0x30))(param_2,auStack_38);
  auStack_38[0]._0_4_ = *(undefined4 *)(param_1 + 0x220);
  (**(code **)*param_2)(param_2,&UNK_0280cc11/*"limit_break_count"*/);
  (**(code **)(*param_2 + 0x30))(param_2,auStack_38);
  auStack_38[0] = CONCAT44(auStack_38[0]._4_4_,*(undefined4 *)(param_1 + 0x250));
  (**(code **)*param_2)(param_2,&UNK_027fb212/*"skill1"*/);
  (**(code **)(*param_2 + 0x30))(param_2,auStack_38);
  auStack_38[1] = 0;
  auStack_38[2] = 0;
  auStack_38[0] = 0;
  void CParameterPropertyBase<175u>::CryptString<string >(string&, string const&)(auStack_38,param_1 + 0x280);
  (**(code **)*param_2)(param_2,&UNK_027fb219/*"skill1_label"*/);
  (**(code **)(*param_2 + 0x58))(param_2,auStack_38);
  if ((auStack_38[0] & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(auStack_38[2]);
  }
  auStack_38[0]._0_4_ = *(undefined4 *)(param_1 + 0x2c0);
  (**(code **)*param_2)(param_2,&UNK_027fb49a/*"skill1_level"*/);
  (**(code **)(*param_2 + 0x30))(param_2,auStack_38);
  auStack_38[0] = CONCAT44(auStack_38[0]._4_4_,*(undefined4 *)(param_1 + 0x2f0));
  (**(code **)*param_2)(param_2,&UNK_027fb226/*"skill2"*/);
  (**(code **)(*param_2 + 0x30))(param_2,auStack_38);
  auStack_38[1] = 0;
  auStack_38[2] = 0;
  auStack_38[0] = 0;
  void CParameterPropertyBase<178u>::CryptString<string >(string&, string const&)(auStack_38,param_1 + 800);
  (**(code **)*param_2)(param_2,&UNK_027fb22d/*"skill2_label"*/);
  (**(code **)(*param_2 + 0x58))(param_2,auStack_38);
  if ((auStack_38[0] & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(auStack_38[2]);
  }
  auStack_38[0]._0_4_ = *(undefined4 *)(param_1 + 0x360);
  (**(code **)*param_2)(param_2,&UNK_027ffcbd/*"skill2_level"*/);
  (**(code **)(*param_2 + 0x30))(param_2,auStack_38);
  auStack_38[0] = CONCAT44(auStack_38[0]._4_4_,*(undefined4 *)(param_1 + 0x390));
  (**(code **)*param_2)(param_2,&UNK_02918cbc/*"skill3"*/);
  (**(code **)(*param_2 + 0x30))(param_2,auStack_38);
  auStack_38[1] = 0;
  auStack_38[2] = 0;
  auStack_38[0] = 0;
  void CParameterPropertyBase<181u>::CryptString<string >(string&, string const&)(auStack_38,param_1 + 0x3c0);
  (**(code **)*param_2)(param_2,&UNK_027fb23a/*"skill3_label"*/);
  (**(code **)(*param_2 + 0x58))(param_2,auStack_38);
  if ((auStack_38[0] & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(auStack_38[2]);
  }
  auStack_38[0]._0_4_ = *(undefined4 *)(param_1 + 0x400);
  (**(code **)*param_2)(param_2,&UNK_027ffcd1/*"skill3_level"*/);
  (**(code **)(*param_2 + 0x30))(param_2,auStack_38);
  auStack_38[0]._0_4_ = *(undefined4 *)(param_1 + 0x430);
  (**(code **)*param_2)(param_2,&UNK_0291ae07/*"hp"*/);
  (**(code **)(*param_2 + 0x50))(param_2,auStack_38);
  auStack_38[0]._0_4_ = *(undefined4 *)(param_1 + 0x460);
  (**(code **)*param_2)(param_2,&UNK_0282db83/*"attack"*/);
  (**(code **)(*param_2 + 0x50))(param_2,auStack_38);
  auStack_38[0]._0_4_ = *(undefined4 *)(param_1 + 0x490);
  (**(code **)*param_2)(param_2,&UNK_0282db95/*"intelligence"*/);
  (**(code **)(*param_2 + 0x50))(param_2,auStack_38);
  auStack_38[0]._0_4_ = *(undefined4 *)(param_1 + 0x4c0);
  (**(code **)*param_2)(param_2,&UNK_0282dbad/*"defence"*/);
  (**(code **)(*param_2 + 0x50))(param_2,auStack_38);
  auStack_38[0]._0_4_ = *(undefined4 *)(param_1 + 0x4f0);
  (**(code **)*param_2)(param_2,&UNK_0291afda/*"hit"*/);
  (**(code **)(*param_2 + 0x50))(param_2,auStack_38);
  auStack_38[0]._0_4_ = *(undefined4 *)(param_1 + 0x520);
  (**(code **)*param_2)(param_2,&UNK_0282dbcf/*"guard"*/);
  (**(code **)(*param_2 + 0x50))(param_2,auStack_38);
  auStack_38[0]._0_4_ = *(undefined4 *)(param_1 + 0x550);
  (**(code **)*param_2)(param_2,&UNK_0286c966/*"ap"*/);
  (**(code **)(*param_2 + 0x50))(param_2,auStack_38);
  auStack_38[0]._0_4_ = *(undefined4 *)(param_1 + 0x580);
  (**(code **)*param_2)(param_2,&UNK_0281ab22/*"def_fire"*/);
  (**(code **)(*param_2 + 0x50))(param_2,auStack_38);
  auStack_38[0]._0_4_ = *(undefined4 *)(param_1 + 0x5b0);
  (**(code **)*param_2)(param_2,&UNK_027fb247/*"def_water"*/);
  (**(code **)(*param_2 + 0x50))(param_2,auStack_38);
  auStack_38[0]._0_4_ = *(undefined4 *)(param_1 + 0x5e0);
  (**(code **)*param_2)(param_2,&UNK_0281ab2b/*"def_wind"*/);
  (**(code **)(*param_2 + 0x50))(param_2,auStack_38);
  auStack_38[0]._0_4_ = *(undefined4 *)(param_1 + 0x610);
  (**(code **)*param_2)(param_2,&UNK_027fb251/*"def_earth"*/);
  (**(code **)(*param_2 + 0x50))(param_2,auStack_38);
  auStack_38[0]._0_4_ = *(undefined4 *)(param_1 + 0x640);
  (**(code **)*param_2)(param_2,&UNK_027fb25b/*"def_thunder"*/);
  (**(code **)(*param_2 + 0x50))(param_2,auStack_38);
  auStack_38[0]._0_4_ = *(undefined4 *)(param_1 + 0x670);
  (**(code **)*param_2)(param_2,&UNK_027fb267/*"def_light"*/);
  (**(code **)(*param_2 + 0x50))(param_2,auStack_38);
  auStack_38[0]._0_4_ = *(undefined4 *)(param_1 + 0x6a0);
  (**(code **)*param_2)(param_2,&UNK_0281ab34/*"def_dark"*/);
  (**(code **)(*param_2 + 0x50))(param_2,auStack_38);
  auStack_38[0] = CONCAT44(auStack_38[0]._4_4_,*(undefined4 *)(param_1 + 0x6d0));
  (**(code **)*param_2)(param_2,&UNK_027fb271/*"rush1"*/);
  (**(code **)(*param_2 + 0x30))(param_2,auStack_38);
  auStack_38[1] = 0;
  auStack_38[2] = 0;
  auStack_38[0] = 0;
  void CParameterPropertyBase<201u>::CryptString<string >(string&, string const&)(auStack_38,param_1 + 0x700);
  (**(code **)*param_2)(param_2,&UNK_027fb277/*"rush1_label"*/);
  (**(code **)(*param_2 + 0x58))(param_2,auStack_38);
  if ((auStack_38[0] & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(auStack_38[2]);
  }
  auStack_38[0]._0_4_ = *(undefined4 *)(param_1 + 0x740);
  (**(code **)*param_2)(param_2,&UNK_027dc71a/*"rush_skill1_factor_id"*/);
  (**(code **)(*param_2 + 0x30))(param_2,auStack_38);
  auStack_38[0]._0_4_ = *(undefined4 *)(param_1 + 0x770);
  (**(code **)*param_2)(param_2,&UNK_027fb283/*"rush1_level"*/);
  (**(code **)(*param_2 + 0x30))(param_2,auStack_38);
  auStack_38[0]._0_4_ = *(undefined4 *)(param_1 + 0x7a0);
  (**(code **)*param_2)(param_2,&UNK_02892234/*"next_exp"*/);
  (**(code **)(*param_2 + 0x30))(param_2,auStack_38);
  auStack_38[0]._0_4_ = *(undefined4 *)(param_1 + 2000);
  (**(code **)*param_2)(param_2,&UNK_027dcb30/*"weapon_id"*/);
  (**(code **)(*param_2 + 0x30))(param_2,auStack_38);
  auStack_38[0] = CONCAT44(auStack_38[0]._4_4_,*(undefined4 *)(param_1 + 0x800));
  (**(code **)*param_2)(param_2,&UNK_027dc632/*"master_weapon_kind_id"*/);
  (**(code **)(*param_2 + 0x30))(param_2,auStack_38);
  auStack_38[1] = 0;
  auStack_38[2] = 0;
  auStack_38[0] = 0;
  void CParameterPropertyBase<209u>::CryptString<string >(string&, string const&)(auStack_38,param_1 + 0x830);
  (**(code **)*param_2)(param_2,&UNK_027dc656/*"weapon_kind_id_label"*/);
  (**(code **)(*param_2 + 0x58))(param_2,auStack_38);
  if ((auStack_38[0] & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(auStack_38[2]);
  }
  auStack_38[0]._0_4_ = *(undefined4 *)(param_1 + 0x870);
  (**(code **)*param_2)(param_2,&UNK_027fb28f/*"weapon_master_item_id"*/);
  (**(code **)(*param_2 + 0x30))(param_2,auStack_38);
  auStack_38[0]._0_4_ = *(undefined4 *)(param_1 + 0x900);
  (**(code **)*param_2)(param_2,&UNK_027fb2cb/*"accessory_master_item_id"*/);
  (**(code **)(*param_2 + 0x30))(param_2,auStack_38);
  auStack_38[0]._0_4_ = *(undefined4 *)(param_1 + 0x8a0);
  (**(code **)*param_2)(param_2,&UNK_027fb2a5/*"weapon_limit_break_count"*/);
  (**(code **)(*param_2 + 0x30))(param_2,auStack_38);
  auStack_38[0]._0_4_ = *(undefined4 *)(param_1 + 0x8d0);
  (**(code **)*param_2)(param_2,&UNK_027fb2be/*"weapon_level"*/);
  (**(code **)(*param_2 + 0x30))(param_2,auStack_38);
  auStack_38[0] = CONCAT44(auStack_38[0]._4_4_,*(undefined4 *)(param_1 + 0xe40));
  (**(code **)*param_2)(param_2,&UNK_027fb3d1/*"is_rarity_7"*/);
  (**(code **)(*param_2 + 0x30))(param_2,auStack_38);
  return;
}

// ==== CPersonStatusInfo::CPersonStatusInfo(CPersonStatusInfo&&)
// vaddr 0x16d28ec | ghidra 0x17d28ec | size 6400 | symbol _ZN17CPersonStatusInfoC2EOS_ | lib libSOA-3.7.0.so | 2026-10-08
void _ZN17CPersonStatusInfoC2EOS_(long *param_1,long param_2)

{
  undefined *puVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined4 uVar4;
  undefined1 uVar5;
  undefined *puVar6;
  long *plVar7;
  bool bVar8;
  long lVar9;
  long *plVar10;
  long *plVar11;
  
  puVar1 = PTR__ZTV8InfoBase_02cc49c8 + 0x10;
  *param_1 = (long)puVar1;
  Framework::CSTLMap<unsigned int, IParameterProperty*>::CSTLMap(Framework::CSTLMap<unsigned int, IParameterProperty*> const&)(param_1 + 1,param_2 + 8);
  Framework::CSTLMap<unsigned int, InfoBase*>::CSTLMap(Framework::CSTLMap<unsigned int, InfoBase*> const&)(param_1 + 4,param_2 + 0x20);
  puVar2 = PTR__ZTV18IParameterProperty_02cbe818 + 0x10;
  *param_1 = (long)(PTR__ZTV17CPersonStatusInfo_02cbd500 + 0x10);
  param_1[7] = (long)puVar2;
  lVar9 = *(long *)(param_2 + 0x40);
  param_1[7] = (long)(PTR__ZTV22CParameterPropertyBaseILj163EE_02cbb018 + 0x10);
  param_1[8] = lVar9;
  puVar3 = PTR__ZTVN9Framework7CHash32E_02cba528;
  *(undefined1 *)(param_1 + 9) = *(undefined1 *)(param_2 + 0x48);
  puVar3 = puVar3 + 0x10;
  param_1[10] = (long)puVar3;
  puVar6 = PTR__ZTV23CParameterPropertyValueImLj163E18CPropertyConverterE_02cbb940;
  *(undefined4 *)(param_1 + 0xb) = *(undefined4 *)(param_2 + 0x58);
  param_1[7] = (long)(puVar6 + 0x10);
  param_1[0xc] = *(long *)(param_2 + 0x60);
  param_1[0xd] = (long)puVar2;
  lVar9 = *(long *)(param_2 + 0x70);
  param_1[0xd] = (long)(PTR__ZTV22CParameterPropertyBaseILj164EE_02cb6d78 + 0x10);
  param_1[0xe] = lVar9;
  uVar5 = *(undefined1 *)(param_2 + 0x78);
  param_1[0x10] = (long)puVar3;
  *(undefined1 *)(param_1 + 0xf) = uVar5;
  puVar6 = PTR__ZTV23CParameterPropertyValueIjLj164E18CPropertyConverterE_02cb6b60;
  *(undefined4 *)(param_1 + 0x11) = *(undefined4 *)(param_2 + 0x88);
  param_1[0xd] = (long)(puVar6 + 0x10);
  uVar4 = *(undefined4 *)(param_2 + 0x90);
  param_1[0x13] = (long)puVar2;
  *(undefined4 *)(param_1 + 0x12) = uVar4;
  lVar9 = *(long *)(param_2 + 0xa0);
  param_1[0x13] = (long)(PTR__ZTV22CParameterPropertyBaseILj165EE_02cbe958 + 0x10);
  param_1[0x14] = lVar9;
  uVar5 = *(undefined1 *)(param_2 + 0xa8);
  param_1[0x16] = (long)puVar3;
  *(undefined1 *)(param_1 + 0x15) = uVar5;
  puVar6 = 
  PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj165EE_02cbd098
  ;
  *(undefined4 *)(param_1 + 0x17) = *(undefined4 *)(param_2 + 0xb8);
  param_1[0x13] = (long)(puVar6 + 0x10);
  param_1[0x1a] = *(long *)(param_2 + 0xd0);
  lVar9 = *(long *)(param_2 + 0xc0);
  param_1[0x19] = *(long *)(param_2 + 200);
  param_1[0x18] = lVar9;
  *(undefined8 *)(param_2 + 200) = 0;
  *(undefined8 *)(param_2 + 0xd0) = 0;
  *(undefined8 *)(param_2 + 0xc0) = 0;
  param_1[0x1b] = (long)puVar2;
  lVar9 = *(long *)(param_2 + 0xe0);
  param_1[0x1b] = (long)(PTR__ZTV22CParameterPropertyBaseILj166EE_02cbf3d8 + 0x10);
  param_1[0x1c] = lVar9;
  uVar5 = *(undefined1 *)(param_2 + 0xe8);
  param_1[0x1e] = (long)puVar3;
  *(undefined1 *)(param_1 + 0x1d) = uVar5;
  puVar6 = PTR__ZTV23CParameterPropertyValueIjLj166E18CPropertyConverterE_02cc3d20;
  *(undefined4 *)(param_1 + 0x1f) = *(undefined4 *)(param_2 + 0xf8);
  param_1[0x1b] = (long)(puVar6 + 0x10);
  uVar4 = *(undefined4 *)(param_2 + 0x100);
  param_1[0x21] = (long)puVar2;
  *(undefined4 *)(param_1 + 0x20) = uVar4;
  lVar9 = *(long *)(param_2 + 0x110);
  param_1[0x21] = (long)(PTR__ZTV22CParameterPropertyBaseILj167EE_02cc36a8 + 0x10);
  param_1[0x22] = lVar9;
  uVar5 = *(undefined1 *)(param_2 + 0x118);
  param_1[0x24] = (long)puVar3;
  *(undefined1 *)(param_1 + 0x23) = uVar5;
  puVar6 = PTR__ZTV23CParameterPropertyValueIjLj167E18CPropertyConverterE_02cbccd8;
  *(undefined4 *)(param_1 + 0x25) = *(undefined4 *)(param_2 + 0x128);
  param_1[0x21] = (long)(puVar6 + 0x10);
  uVar4 = *(undefined4 *)(param_2 + 0x130);
  param_1[0x27] = (long)puVar2;
  *(undefined4 *)(param_1 + 0x26) = uVar4;
  lVar9 = *(long *)(param_2 + 0x140);
  param_1[0x27] = (long)(PTR__ZTV22CParameterPropertyBaseILj168EE_02cbb8a0 + 0x10);
  param_1[0x28] = lVar9;
  uVar5 = *(undefined1 *)(param_2 + 0x148);
  param_1[0x2a] = (long)puVar3;
  *(undefined1 *)(param_1 + 0x29) = uVar5;
  puVar6 = PTR__ZTV23CParameterPropertyValueImLj168E18CPropertyConverterE_02cc4290;
  *(undefined4 *)(param_1 + 0x2b) = *(undefined4 *)(param_2 + 0x158);
  param_1[0x27] = (long)(puVar6 + 0x10);
  param_1[0x2c] = *(long *)(param_2 + 0x160);
  param_1[0x2d] = (long)puVar2;
  lVar9 = *(long *)(param_2 + 0x170);
  param_1[0x2d] = (long)(PTR__ZTV22CParameterPropertyBaseILj169EE_02cbcf68 + 0x10);
  param_1[0x2e] = lVar9;
  uVar5 = *(undefined1 *)(param_2 + 0x178);
  param_1[0x30] = (long)puVar3;
  *(undefined1 *)(param_1 + 0x2f) = uVar5;
  puVar6 = PTR__ZTV23CParameterPropertyValueImLj169E18CPropertyConverterE_02cc3730;
  *(undefined4 *)(param_1 + 0x31) = *(undefined4 *)(param_2 + 0x188);
  param_1[0x2d] = (long)(puVar6 + 0x10);
  param_1[0x32] = *(long *)(param_2 + 400);
  param_1[0x33] = (long)puVar2;
  lVar9 = *(long *)(param_2 + 0x1a0);
  param_1[0x33] = (long)(PTR__ZTV22CParameterPropertyBaseILj170EE_02cc11c8 + 0x10);
  param_1[0x34] = lVar9;
  uVar5 = *(undefined1 *)(param_2 + 0x1a8);
  param_1[0x36] = (long)puVar3;
  *(undefined1 *)(param_1 + 0x35) = uVar5;
  puVar6 = PTR__ZTV23CParameterPropertyValueIjLj170E18CPropertyConverterE_02cc4be0;
  *(undefined4 *)(param_1 + 0x37) = *(undefined4 *)(param_2 + 0x1b8);
  param_1[0x33] = (long)(puVar6 + 0x10);
  uVar4 = *(undefined4 *)(param_2 + 0x1c0);
  param_1[0x39] = (long)puVar2;
  *(undefined4 *)(param_1 + 0x38) = uVar4;
  lVar9 = *(long *)(param_2 + 0x1d0);
  param_1[0x39] = (long)(PTR__ZTV22CParameterPropertyBaseILj171EE_02cb6eb8 + 0x10);
  param_1[0x3a] = lVar9;
  uVar5 = *(undefined1 *)(param_2 + 0x1d8);
  param_1[0x3c] = (long)puVar3;
  *(undefined1 *)(param_1 + 0x3b) = uVar5;
  puVar6 = PTR__ZTV23CParameterPropertyValueIjLj171E18CPropertyConverterE_02cbdc20;
  *(undefined4 *)(param_1 + 0x3d) = *(undefined4 *)(param_2 + 0x1e8);
  param_1[0x39] = (long)(puVar6 + 0x10);
  uVar4 = *(undefined4 *)(param_2 + 0x1f0);
  param_1[0x3f] = (long)puVar2;
  *(undefined4 *)(param_1 + 0x3e) = uVar4;
  lVar9 = *(long *)(param_2 + 0x200);
  param_1[0x3f] = (long)(PTR__ZTV22CParameterPropertyBaseILj172EE_02cb79d0 + 0x10);
  param_1[0x40] = lVar9;
  uVar5 = *(undefined1 *)(param_2 + 0x208);
  param_1[0x42] = (long)puVar3;
  *(undefined1 *)(param_1 + 0x41) = uVar5;
  puVar6 = PTR__ZTV23CParameterPropertyValueIjLj172E18CPropertyConverterE_02cc33c8;
  *(undefined4 *)(param_1 + 0x43) = *(undefined4 *)(param_2 + 0x218);
  param_1[0x3f] = (long)(puVar6 + 0x10);
  uVar4 = *(undefined4 *)(param_2 + 0x220);
  param_1[0x45] = (long)puVar2;
  *(undefined4 *)(param_1 + 0x44) = uVar4;
  puVar6 = PTR__ZTV22CParameterPropertyBaseILj174EE_02cb7838;
  param_1[0x46] = *(long *)(param_2 + 0x230);
  param_1[0x45] = (long)(puVar6 + 0x10);
  uVar5 = *(undefined1 *)(param_2 + 0x238);
  param_1[0x48] = (long)puVar3;
  *(undefined1 *)(param_1 + 0x47) = uVar5;
  puVar6 = PTR__ZTV23CParameterPropertyValueIjLj174E18CPropertyConverterE_02cba740;
  *(undefined4 *)(param_1 + 0x49) = *(undefined4 *)(param_2 + 0x248);
  param_1[0x45] = (long)(puVar6 + 0x10);
  uVar4 = *(undefined4 *)(param_2 + 0x250);
  param_1[0x4b] = (long)puVar2;
  *(undefined4 *)(param_1 + 0x4a) = uVar4;
  puVar6 = PTR__ZTV22CParameterPropertyBaseILj175EE_02cbe608;
  param_1[0x4c] = *(long *)(param_2 + 0x260);
  param_1[0x4b] = (long)(puVar6 + 0x10);
  uVar5 = *(undefined1 *)(param_2 + 0x268);
  param_1[0x4e] = (long)puVar3;
  *(undefined1 *)(param_1 + 0x4d) = uVar5;
  puVar6 = 
  PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj175EE_02cc2fd0
  ;
  *(undefined4 *)(param_1 + 0x4f) = *(undefined4 *)(param_2 + 0x278);
  param_1[0x4b] = (long)(puVar6 + 0x10);
  param_1[0x52] = *(long *)(param_2 + 0x290);
  lVar9 = *(long *)(param_2 + 0x280);
  param_1[0x51] = *(long *)(param_2 + 0x288);
  param_1[0x50] = lVar9;
  *(undefined8 *)(param_2 + 0x290) = 0;
  *(undefined8 *)(param_2 + 0x288) = 0;
  *(undefined8 *)(param_2 + 0x280) = 0;
  param_1[0x53] = (long)puVar2;
  puVar6 = PTR__ZTV22CParameterPropertyBaseILj176EE_02cb9b78;
  param_1[0x54] = *(long *)(param_2 + 0x2a0);
  param_1[0x53] = (long)(puVar6 + 0x10);
  uVar5 = *(undefined1 *)(param_2 + 0x2a8);
  param_1[0x56] = (long)puVar3;
  *(undefined1 *)(param_1 + 0x55) = uVar5;
  puVar6 = PTR__ZTV23CParameterPropertyValueIjLj176E18CPropertyConverterE_02cb8db0;
  *(undefined4 *)(param_1 + 0x57) = *(undefined4 *)(param_2 + 0x2b8);
  param_1[0x53] = (long)(puVar6 + 0x10);
  uVar4 = *(undefined4 *)(param_2 + 0x2c0);
  param_1[0x59] = (long)puVar2;
  *(undefined4 *)(param_1 + 0x58) = uVar4;
  puVar6 = PTR__ZTV22CParameterPropertyBaseILj177EE_02cbeb68;
  param_1[0x5a] = *(long *)(param_2 + 0x2d0);
  param_1[0x59] = (long)(puVar6 + 0x10);
  uVar5 = *(undefined1 *)(param_2 + 0x2d8);
  param_1[0x5c] = (long)puVar3;
  *(undefined1 *)(param_1 + 0x5b) = uVar5;
  puVar6 = PTR__ZTV23CParameterPropertyValueIjLj177E18CPropertyConverterE_02cb9920;
  *(undefined4 *)(param_1 + 0x5d) = *(undefined4 *)(param_2 + 0x2e8);
  param_1[0x59] = (long)(puVar6 + 0x10);
  uVar4 = *(undefined4 *)(param_2 + 0x2f0);
  param_1[0x5f] = (long)puVar2;
  *(undefined4 *)(param_1 + 0x5e) = uVar4;
  puVar6 = PTR__ZTV22CParameterPropertyBaseILj178EE_02cc1938;
  param_1[0x60] = *(long *)(param_2 + 0x300);
  param_1[0x5f] = (long)(puVar6 + 0x10);
  uVar5 = *(undefined1 *)(param_2 + 0x308);
  param_1[0x62] = (long)puVar3;
  *(undefined1 *)(param_1 + 0x61) = uVar5;
  puVar6 = 
  PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj178EE_02cb8b38
  ;
  *(undefined4 *)(param_1 + 99) = *(undefined4 *)(param_2 + 0x318);
  param_1[0x5f] = (long)(puVar6 + 0x10);
  param_1[0x66] = *(long *)(param_2 + 0x330);
  lVar9 = *(long *)(param_2 + 800);
  param_1[0x65] = *(long *)(param_2 + 0x328);
  param_1[100] = lVar9;
  *(undefined8 *)(param_2 + 0x330) = 0;
  *(undefined8 *)(param_2 + 0x328) = 0;
  *(undefined8 *)(param_2 + 800) = 0;
  param_1[0x67] = (long)puVar2;
  puVar6 = PTR__ZTV22CParameterPropertyBaseILj179EE_02cbae40;
  param_1[0x68] = *(long *)(param_2 + 0x340);
  param_1[0x67] = (long)(puVar6 + 0x10);
  uVar5 = *(undefined1 *)(param_2 + 0x348);
  param_1[0x6a] = (long)puVar3;
  *(undefined1 *)(param_1 + 0x69) = uVar5;
  puVar6 = PTR__ZTV23CParameterPropertyValueIjLj179E18CPropertyConverterE_02cc09e0;
  *(undefined4 *)(param_1 + 0x6b) = *(undefined4 *)(param_2 + 0x358);
  param_1[0x67] = (long)(puVar6 + 0x10);
  uVar4 = *(undefined4 *)(param_2 + 0x360);
  param_1[0x6d] = (long)puVar2;
  *(undefined4 *)(param_1 + 0x6c) = uVar4;
  puVar6 = PTR__ZTV22CParameterPropertyBaseILj180EE_02cba700;
  param_1[0x6e] = *(long *)(param_2 + 0x370);
  param_1[0x6d] = (long)(puVar6 + 0x10);
  uVar5 = *(undefined1 *)(param_2 + 0x378);
  param_1[0x70] = (long)puVar3;
  *(undefined1 *)(param_1 + 0x6f) = uVar5;
  puVar6 = PTR__ZTV23CParameterPropertyValueIjLj180E18CPropertyConverterE_02cc15d0;
  *(undefined4 *)(param_1 + 0x71) = *(undefined4 *)(param_2 + 0x388);
  param_1[0x6d] = (long)(puVar6 + 0x10);
  uVar4 = *(undefined4 *)(param_2 + 0x390);
  param_1[0x73] = (long)puVar2;
  *(undefined4 *)(param_1 + 0x72) = uVar4;
  puVar6 = PTR__ZTV22CParameterPropertyBaseILj181EE_02cbb330;
  param_1[0x74] = *(long *)(param_2 + 0x3a0);
  param_1[0x73] = (long)(puVar6 + 0x10);
  uVar5 = *(undefined1 *)(param_2 + 0x3a8);
  param_1[0x76] = (long)puVar3;
  *(undefined1 *)(param_1 + 0x75) = uVar5;
  puVar6 = 
  PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj181EE_02cc0890
  ;
  *(undefined4 *)(param_1 + 0x77) = *(undefined4 *)(param_2 + 0x3b8);
  param_1[0x73] = (long)(puVar6 + 0x10);
  param_1[0x7a] = *(long *)(param_2 + 0x3d0);
  lVar9 = *(long *)(param_2 + 0x3c0);
  param_1[0x79] = *(long *)(param_2 + 0x3c8);
  param_1[0x78] = lVar9;
  *(undefined8 *)(param_2 + 0x3d0) = 0;
  *(undefined8 *)(param_2 + 0x3c8) = 0;
  *(undefined8 *)(param_2 + 0x3c0) = 0;
  param_1[0x7b] = (long)puVar2;
  puVar6 = PTR__ZTV22CParameterPropertyBaseILj182EE_02cc2f48;
  param_1[0x7c] = *(long *)(param_2 + 0x3e0);
  param_1[0x7b] = (long)(puVar6 + 0x10);
  uVar5 = *(undefined1 *)(param_2 + 1000);
  param_1[0x7e] = (long)puVar3;
  *(undefined1 *)(param_1 + 0x7d) = uVar5;
  puVar6 = PTR__ZTV23CParameterPropertyValueIjLj182E18CPropertyConverterE_02cbd910;
  *(undefined4 *)(param_1 + 0x7f) = *(undefined4 *)(param_2 + 0x3f8);
  param_1[0x7b] = (long)(puVar6 + 0x10);
  uVar4 = *(undefined4 *)(param_2 + 0x400);
  param_1[0x81] = (long)puVar2;
  *(undefined4 *)(param_1 + 0x80) = uVar4;
  puVar6 = PTR__ZTV22CParameterPropertyBaseILj184EE_02cc1e78;
  param_1[0x82] = *(long *)(param_2 + 0x410);
  param_1[0x81] = (long)(puVar6 + 0x10);
  uVar5 = *(undefined1 *)(param_2 + 0x418);
  param_1[0x84] = (long)puVar3;
  *(undefined1 *)(param_1 + 0x83) = uVar5;
  puVar6 = PTR__ZTV23CParameterPropertyValueIfLj184E18CPropertyConverterE_02cbc170;
  *(undefined4 *)(param_1 + 0x85) = *(undefined4 *)(param_2 + 0x428);
  param_1[0x81] = (long)(puVar6 + 0x10);
  uVar4 = *(undefined4 *)(param_2 + 0x430);
  param_1[0x87] = (long)puVar2;
  *(undefined4 *)(param_1 + 0x86) = uVar4;
  puVar6 = PTR__ZTV22CParameterPropertyBaseILj185EE_02cbd450;
  param_1[0x88] = *(long *)(param_2 + 0x440);
  param_1[0x87] = (long)(puVar6 + 0x10);
  uVar5 = *(undefined1 *)(param_2 + 0x448);
  param_1[0x8a] = (long)puVar3;
  *(undefined1 *)(param_1 + 0x89) = uVar5;
  puVar6 = PTR__ZTV23CParameterPropertyValueIfLj185E18CPropertyConverterE_02cba4f0;
  *(undefined4 *)(param_1 + 0x8b) = *(undefined4 *)(param_2 + 0x458);
  param_1[0x87] = (long)(puVar6 + 0x10);
  uVar4 = *(undefined4 *)(param_2 + 0x460);
  param_1[0x8d] = (long)puVar2;
  *(undefined4 *)(param_1 + 0x8c) = uVar4;
  puVar6 = PTR__ZTV22CParameterPropertyBaseILj186EE_02cc2420;
  param_1[0x8e] = *(long *)(param_2 + 0x470);
  param_1[0x8d] = (long)(puVar6 + 0x10);
  uVar5 = *(undefined1 *)(param_2 + 0x478);
  param_1[0x90] = (long)puVar3;
  *(undefined1 *)(param_1 + 0x8f) = uVar5;
  puVar6 = PTR__ZTV23CParameterPropertyValueIfLj186E18CPropertyConverterE_02cbcdb0;
  *(undefined4 *)(param_1 + 0x91) = *(undefined4 *)(param_2 + 0x488);
  param_1[0x8d] = (long)(puVar6 + 0x10);
  uVar4 = *(undefined4 *)(param_2 + 0x490);
  param_1[0x93] = (long)puVar2;
  *(undefined4 *)(param_1 + 0x92) = uVar4;
  puVar6 = PTR__ZTV22CParameterPropertyBaseILj187EE_02cbe120;
  param_1[0x94] = *(long *)(param_2 + 0x4a0);
  param_1[0x93] = (long)(puVar6 + 0x10);
  uVar5 = *(undefined1 *)(param_2 + 0x4a8);
  param_1[0x96] = (long)puVar3;
  *(undefined1 *)(param_1 + 0x95) = uVar5;
  puVar6 = PTR__ZTV23CParameterPropertyValueIfLj187E18CPropertyConverterE_02cbd458;
  *(undefined4 *)(param_1 + 0x97) = *(undefined4 *)(param_2 + 0x4b8);
  param_1[0x93] = (long)(puVar6 + 0x10);
  uVar4 = *(undefined4 *)(param_2 + 0x4c0);
  param_1[0x99] = (long)puVar2;
  *(undefined4 *)(param_1 + 0x98) = uVar4;
  puVar6 = PTR__ZTV22CParameterPropertyBaseILj188EE_02cb7598;
  param_1[0x9a] = *(long *)(param_2 + 0x4d0);
  param_1[0x99] = (long)(puVar6 + 0x10);
  uVar5 = *(undefined1 *)(param_2 + 0x4d8);
  param_1[0x9c] = (long)puVar3;
  *(undefined1 *)(param_1 + 0x9b) = uVar5;
  puVar6 = PTR__ZTV23CParameterPropertyValueIfLj188E18CPropertyConverterE_02cc14c8;
  *(undefined4 *)(param_1 + 0x9d) = *(undefined4 *)(param_2 + 0x4e8);
  param_1[0x99] = (long)(puVar6 + 0x10);
  uVar4 = *(undefined4 *)(param_2 + 0x4f0);
  param_1[0x9f] = (long)puVar2;
  *(undefined4 *)(param_1 + 0x9e) = uVar4;
  puVar6 = PTR__ZTV22CParameterPropertyBaseILj189EE_02cb80f0;
  param_1[0xa0] = *(long *)(param_2 + 0x500);
  param_1[0x9f] = (long)(puVar6 + 0x10);
  uVar5 = *(undefined1 *)(param_2 + 0x508);
  param_1[0xa2] = (long)puVar3;
  *(undefined1 *)(param_1 + 0xa1) = uVar5;
  puVar6 = PTR__ZTV23CParameterPropertyValueIfLj189E18CPropertyConverterE_02cb81d8;
  *(undefined4 *)(param_1 + 0xa3) = *(undefined4 *)(param_2 + 0x518);
  param_1[0x9f] = (long)(puVar6 + 0x10);
  uVar4 = *(undefined4 *)(param_2 + 0x520);
  param_1[0xa5] = (long)puVar2;
  *(undefined4 *)(param_1 + 0xa4) = uVar4;
  puVar6 = PTR__ZTV22CParameterPropertyBaseILj190EE_02cb75d0;
  param_1[0xa6] = *(long *)(param_2 + 0x530);
  param_1[0xa5] = (long)(puVar6 + 0x10);
  uVar5 = *(undefined1 *)(param_2 + 0x538);
  param_1[0xa8] = (long)puVar3;
  *(undefined1 *)(param_1 + 0xa7) = uVar5;
  puVar6 = PTR__ZTV23CParameterPropertyValueIfLj190E18CPropertyConverterE_02cc3d40;
  *(undefined4 *)(param_1 + 0xa9) = *(undefined4 *)(param_2 + 0x548);
  param_1[0xa5] = (long)(puVar6 + 0x10);
  uVar4 = *(undefined4 *)(param_2 + 0x550);
  param_1[0xab] = (long)puVar2;
  *(undefined4 *)(param_1 + 0xaa) = uVar4;
  puVar6 = PTR__ZTV22CParameterPropertyBaseILj192EE_02cb9fb0;
  param_1[0xac] = *(long *)(param_2 + 0x560);
  param_1[0xab] = (long)(puVar6 + 0x10);
  uVar5 = *(undefined1 *)(param_2 + 0x568);
  param_1[0xae] = (long)puVar3;
  *(undefined1 *)(param_1 + 0xad) = uVar5;
  puVar6 = PTR__ZTV23CParameterPropertyValueIfLj192E18CPropertyConverterE_02cba1d8;
  *(undefined4 *)(param_1 + 0xaf) = *(undefined4 *)(param_2 + 0x578);
  param_1[0xab] = (long)(puVar6 + 0x10);
  uVar4 = *(undefined4 *)(param_2 + 0x580);
  param_1[0xb1] = (long)puVar2;
  *(undefined4 *)(param_1 + 0xb0) = uVar4;
  puVar6 = PTR__ZTV22CParameterPropertyBaseILj193EE_02cbe150;
  param_1[0xb2] = *(long *)(param_2 + 0x590);
  param_1[0xb1] = (long)(puVar6 + 0x10);
  uVar5 = *(undefined1 *)(param_2 + 0x598);
  param_1[0xb4] = (long)puVar3;
  *(undefined1 *)(param_1 + 0xb3) = uVar5;
  puVar6 = PTR__ZTV23CParameterPropertyValueIfLj193E18CPropertyConverterE_02cba8c0;
  *(undefined4 *)(param_1 + 0xb5) = *(undefined4 *)(param_2 + 0x5a8);
  param_1[0xb1] = (long)(puVar6 + 0x10);
  uVar4 = *(undefined4 *)(param_2 + 0x5b0);
  param_1[0xb7] = (long)puVar2;
  *(undefined4 *)(param_1 + 0xb6) = uVar4;
  puVar6 = PTR__ZTV22CParameterPropertyBaseILj194EE_02cbed70;
  param_1[0xb8] = *(long *)(param_2 + 0x5c0);
  param_1[0xb7] = (long)(puVar6 + 0x10);
  uVar5 = *(undefined1 *)(param_2 + 0x5c8);
  param_1[0xba] = (long)puVar3;
  *(undefined1 *)(param_1 + 0xb9) = uVar5;
  puVar6 = PTR__ZTV23CParameterPropertyValueIfLj194E18CPropertyConverterE_02cc3e30;
  *(undefined4 *)(param_1 + 0xbb) = *(undefined4 *)(param_2 + 0x5d8);
  param_1[0xb7] = (long)(puVar6 + 0x10);
  uVar4 = *(undefined4 *)(param_2 + 0x5e0);
  param_1[0xbd] = (long)puVar2;
  *(undefined4 *)(param_1 + 0xbc) = uVar4;
  puVar6 = PTR__ZTV22CParameterPropertyBaseILj195EE_02cb80e8;
  param_1[0xbe] = *(long *)(param_2 + 0x5f0);
  param_1[0xbd] = (long)(puVar6 + 0x10);
  uVar5 = *(undefined1 *)(param_2 + 0x5f8);
  param_1[0xc0] = (long)puVar3;
  *(undefined1 *)(param_1 + 0xbf) = uVar5;
  puVar6 = PTR__ZTV23CParameterPropertyValueIfLj195E18CPropertyConverterE_02cb9660;
  *(undefined4 *)(param_1 + 0xc1) = *(undefined4 *)(param_2 + 0x608);
  param_1[0xbd] = (long)(puVar6 + 0x10);
  uVar4 = *(undefined4 *)(param_2 + 0x610);
  param_1[0xc3] = (long)puVar2;
  *(undefined4 *)(param_1 + 0xc2) = uVar4;
  puVar6 = PTR__ZTV22CParameterPropertyBaseILj196EE_02cbebf0;
  param_1[0xc4] = *(long *)(param_2 + 0x620);
  param_1[0xc3] = (long)(puVar6 + 0x10);
  uVar5 = *(undefined1 *)(param_2 + 0x628);
  param_1[0xc6] = (long)puVar3;
  *(undefined1 *)(param_1 + 0xc5) = uVar5;
  puVar6 = PTR__ZTV23CParameterPropertyValueIfLj196E18CPropertyConverterE_02cbdc18;
  *(undefined4 *)(param_1 + 199) = *(undefined4 *)(param_2 + 0x638);
  param_1[0xc3] = (long)(puVar6 + 0x10);
  uVar4 = *(undefined4 *)(param_2 + 0x640);
  param_1[0xc9] = (long)puVar2;
  *(undefined4 *)(param_1 + 200) = uVar4;
  puVar6 = PTR__ZTV22CParameterPropertyBaseILj197EE_02cb7220;
  param_1[0xca] = *(long *)(param_2 + 0x650);
  param_1[0xc9] = (long)(puVar6 + 0x10);
  uVar5 = *(undefined1 *)(param_2 + 0x658);
  param_1[0xcc] = (long)puVar3;
  *(undefined1 *)(param_1 + 0xcb) = uVar5;
  puVar6 = PTR__ZTV23CParameterPropertyValueIfLj197E18CPropertyConverterE_02cb9418;
  *(undefined4 *)(param_1 + 0xcd) = *(undefined4 *)(param_2 + 0x668);
  param_1[0xc9] = (long)(puVar6 + 0x10);
  uVar4 = *(undefined4 *)(param_2 + 0x670);
  param_1[0xcf] = (long)puVar2;
  *(undefined4 *)(param_1 + 0xce) = uVar4;
  puVar6 = PTR__ZTV22CParameterPropertyBaseILj198EE_02cc0c68;
  param_1[0xd0] = *(long *)(param_2 + 0x680);
  param_1[0xcf] = (long)(puVar6 + 0x10);
  uVar5 = *(undefined1 *)(param_2 + 0x688);
  param_1[0xd2] = (long)puVar3;
  *(undefined1 *)(param_1 + 0xd1) = uVar5;
  puVar6 = PTR__ZTV23CParameterPropertyValueIfLj198E18CPropertyConverterE_02cb8e90;
  *(undefined4 *)(param_1 + 0xd3) = *(undefined4 *)(param_2 + 0x698);
  param_1[0xcf] = (long)(puVar6 + 0x10);
  uVar4 = *(undefined4 *)(param_2 + 0x6a0);
  param_1[0xd5] = (long)puVar2;
  *(undefined4 *)(param_1 + 0xd4) = uVar4;
  puVar6 = PTR__ZTV22CParameterPropertyBaseILj200EE_02cbc5b0;
  param_1[0xd6] = *(long *)(param_2 + 0x6b0);
  param_1[0xd5] = (long)(puVar6 + 0x10);
  uVar5 = *(undefined1 *)(param_2 + 0x6b8);
  param_1[0xd8] = (long)puVar3;
  *(undefined1 *)(param_1 + 0xd7) = uVar5;
  puVar6 = PTR__ZTV23CParameterPropertyValueIjLj200E18CPropertyConverterE_02cbf2d0;
  *(undefined4 *)(param_1 + 0xd9) = *(undefined4 *)(param_2 + 0x6c8);
  param_1[0xd5] = (long)(puVar6 + 0x10);
  uVar4 = *(undefined4 *)(param_2 + 0x6d0);
  param_1[0xdb] = (long)puVar2;
  *(undefined4 *)(param_1 + 0xda) = uVar4;
  puVar6 = PTR__ZTV22CParameterPropertyBaseILj201EE_02cc3250;
  param_1[0xdc] = *(long *)(param_2 + 0x6e0);
  param_1[0xdb] = (long)(puVar6 + 0x10);
  uVar5 = *(undefined1 *)(param_2 + 0x6e8);
  param_1[0xde] = (long)puVar3;
  *(undefined1 *)(param_1 + 0xdd) = uVar5;
  puVar6 = 
  PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj201EE_02cb6ee0
  ;
  *(undefined4 *)(param_1 + 0xdf) = *(undefined4 *)(param_2 + 0x6f8);
  param_1[0xdb] = (long)(puVar6 + 0x10);
  param_1[0xe2] = *(long *)(param_2 + 0x710);
  lVar9 = *(long *)(param_2 + 0x700);
  param_1[0xe1] = *(long *)(param_2 + 0x708);
  param_1[0xe0] = lVar9;
  *(undefined8 *)(param_2 + 0x710) = 0;
  *(undefined8 *)(param_2 + 0x708) = 0;
  *(undefined8 *)(param_2 + 0x700) = 0;
  param_1[0xe3] = (long)puVar2;
  puVar6 = PTR__ZTV22CParameterPropertyBaseILj202EE_02cbef50;
  param_1[0xe4] = *(long *)(param_2 + 0x720);
  param_1[0xe3] = (long)(puVar6 + 0x10);
  uVar5 = *(undefined1 *)(param_2 + 0x728);
  param_1[0xe6] = (long)puVar3;
  *(undefined1 *)(param_1 + 0xe5) = uVar5;
  puVar6 = PTR__ZTV23CParameterPropertyValueIjLj202E18CPropertyConverterE_02cbef10;
  *(undefined4 *)(param_1 + 0xe7) = *(undefined4 *)(param_2 + 0x738);
  param_1[0xe3] = (long)(puVar6 + 0x10);
  uVar4 = *(undefined4 *)(param_2 + 0x740);
  param_1[0xe9] = (long)puVar2;
  *(undefined4 *)(param_1 + 0xe8) = uVar4;
  puVar6 = PTR__ZTV22CParameterPropertyBaseILj203EE_02cb83f0;
  param_1[0xea] = *(long *)(param_2 + 0x750);
  param_1[0xe9] = (long)(puVar6 + 0x10);
  uVar5 = *(undefined1 *)(param_2 + 0x758);
  param_1[0xec] = (long)puVar3;
  *(undefined1 *)(param_1 + 0xeb) = uVar5;
  puVar6 = PTR__ZTV23CParameterPropertyValueIjLj203E18CPropertyConverterE_02cc3330;
  *(undefined4 *)(param_1 + 0xed) = *(undefined4 *)(param_2 + 0x768);
  param_1[0xe9] = (long)(puVar6 + 0x10);
  uVar4 = *(undefined4 *)(param_2 + 0x770);
  param_1[0xef] = (long)puVar2;
  *(undefined4 *)(param_1 + 0xee) = uVar4;
  puVar6 = PTR__ZTV22CParameterPropertyBaseILj205EE_02cbb3f0;
  param_1[0xf0] = *(long *)(param_2 + 0x780);
  param_1[0xef] = (long)(puVar6 + 0x10);
  uVar5 = *(undefined1 *)(param_2 + 0x788);
  param_1[0xf2] = (long)puVar3;
  *(undefined1 *)(param_1 + 0xf1) = uVar5;
  puVar6 = PTR__ZTV23CParameterPropertyValueIjLj205E18CPropertyConverterE_02cbdcf0;
  *(undefined4 *)(param_1 + 0xf3) = *(undefined4 *)(param_2 + 0x798);
  param_1[0xef] = (long)(puVar6 + 0x10);
  uVar4 = *(undefined4 *)(param_2 + 0x7a0);
  param_1[0xf5] = (long)puVar2;
  *(undefined4 *)(param_1 + 0xf4) = uVar4;
  puVar6 = PTR__ZTV22CParameterPropertyBaseILj207EE_02cb6b28;
  param_1[0xf6] = *(long *)(param_2 + 0x7b0);
  param_1[0xf5] = (long)(puVar6 + 0x10);
  uVar5 = *(undefined1 *)(param_2 + 0x7b8);
  param_1[0xf8] = (long)puVar3;
  *(undefined1 *)(param_1 + 0xf7) = uVar5;
  puVar6 = PTR__ZTV23CParameterPropertyValueIjLj207E18CPropertyConverterE_02cb9b10;
  *(undefined4 *)(param_1 + 0xf9) = *(undefined4 *)(param_2 + 0x7c8);
  param_1[0xf5] = (long)(puVar6 + 0x10);
  uVar4 = *(undefined4 *)(param_2 + 2000);
  param_1[0xfb] = (long)puVar2;
  *(undefined4 *)(param_1 + 0xfa) = uVar4;
  puVar6 = PTR__ZTV22CParameterPropertyBaseILj208EE_02cb7680;
  param_1[0xfc] = *(long *)(param_2 + 0x7e0);
  param_1[0xfb] = (long)(puVar6 + 0x10);
  uVar5 = *(undefined1 *)(param_2 + 0x7e8);
  param_1[0xfe] = (long)puVar3;
  *(undefined1 *)(param_1 + 0xfd) = uVar5;
  puVar6 = PTR__ZTV23CParameterPropertyValueIjLj208E18CPropertyConverterE_02cb8c28;
  *(undefined4 *)(param_1 + 0xff) = *(undefined4 *)(param_2 + 0x7f8);
  param_1[0xfb] = (long)(puVar6 + 0x10);
  uVar4 = *(undefined4 *)(param_2 + 0x800);
  param_1[0x101] = (long)puVar2;
  *(undefined4 *)(param_1 + 0x100) = uVar4;
  puVar6 = PTR__ZTV22CParameterPropertyBaseILj209EE_02cc1c38;
  param_1[0x102] = *(long *)(param_2 + 0x810);
  param_1[0x101] = (long)(puVar6 + 0x10);
  uVar5 = *(undefined1 *)(param_2 + 0x818);
  param_1[0x104] = (long)puVar3;
  *(undefined1 *)(param_1 + 0x103) = uVar5;
  puVar6 = 
  PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj209EE_02cba138
  ;
  *(undefined4 *)(param_1 + 0x105) = *(undefined4 *)(param_2 + 0x828);
  param_1[0x101] = (long)(puVar6 + 0x10);
  param_1[0x108] = *(long *)(param_2 + 0x840);
  lVar9 = *(long *)(param_2 + 0x830);
  param_1[0x107] = *(long *)(param_2 + 0x838);
  param_1[0x106] = lVar9;
  *(undefined8 *)(param_2 + 0x840) = 0;
  *(undefined8 *)(param_2 + 0x838) = 0;
  *(undefined8 *)(param_2 + 0x830) = 0;
  param_1[0x109] = (long)puVar2;
  puVar6 = PTR__ZTV22CParameterPropertyBaseILj210EE_02cbf870;
  param_1[0x10a] = *(long *)(param_2 + 0x850);
  param_1[0x109] = (long)(puVar6 + 0x10);
  uVar5 = *(undefined1 *)(param_2 + 0x858);
  param_1[0x10c] = (long)puVar3;
  *(undefined1 *)(param_1 + 0x10b) = uVar5;
  puVar6 = PTR__ZTV23CParameterPropertyValueIjLj210E18CPropertyConverterE_02cc4330;
  *(undefined4 *)(param_1 + 0x10d) = *(undefined4 *)(param_2 + 0x868);
  param_1[0x109] = (long)(puVar6 + 0x10);
  uVar4 = *(undefined4 *)(param_2 + 0x870);
  param_1[0x10f] = (long)puVar2;
  *(undefined4 *)(param_1 + 0x10e) = uVar4;
  puVar6 = PTR__ZTV22CParameterPropertyBaseILj211EE_02cc28b0;
  param_1[0x110] = *(long *)(param_2 + 0x880);
  param_1[0x10f] = (long)(puVar6 + 0x10);
  uVar5 = *(undefined1 *)(param_2 + 0x888);
  param_1[0x112] = (long)puVar3;
  *(undefined1 *)(param_1 + 0x111) = uVar5;
  puVar6 = PTR__ZTV23CParameterPropertyValueIjLj211E18CPropertyConverterE_02cb7058;
  *(undefined4 *)(param_1 + 0x113) = *(undefined4 *)(param_2 + 0x898);
  param_1[0x10f] = (long)(puVar6 + 0x10);
  uVar4 = *(undefined4 *)(param_2 + 0x8a0);
  param_1[0x115] = (long)puVar2;
  *(undefined4 *)(param_1 + 0x114) = uVar4;
  puVar6 = PTR__ZTV22CParameterPropertyBaseILj212EE_02cbbc90;
  param_1[0x116] = *(long *)(param_2 + 0x8b0);
  param_1[0x115] = (long)(puVar6 + 0x10);
  uVar5 = *(undefined1 *)(param_2 + 0x8b8);
  param_1[0x118] = (long)puVar3;
  *(undefined1 *)(param_1 + 0x117) = uVar5;
  puVar6 = PTR__ZTV23CParameterPropertyValueIjLj212E18CPropertyConverterE_02cbb0d8;
  *(undefined4 *)(param_1 + 0x119) = *(undefined4 *)(param_2 + 0x8c8);
  param_1[0x115] = (long)(puVar6 + 0x10);
  uVar4 = *(undefined4 *)(param_2 + 0x8d0);
  param_1[0x11b] = (long)puVar2;
  *(undefined4 *)(param_1 + 0x11a) = uVar4;
  puVar6 = PTR__ZTV22CParameterPropertyBaseILj214EE_02cb7ad8;
  param_1[0x11c] = *(long *)(param_2 + 0x8e0);
  param_1[0x11b] = (long)(puVar6 + 0x10);
  uVar5 = *(undefined1 *)(param_2 + 0x8e8);
  param_1[0x11e] = (long)puVar3;
  *(undefined1 *)(param_1 + 0x11d) = uVar5;
  puVar6 = PTR__ZTV23CParameterPropertyValueIjLj214E18CPropertyConverterE_02cb9230;
  *(undefined4 *)(param_1 + 0x11f) = *(undefined4 *)(param_2 + 0x8f8);
  param_1[0x11b] = (long)(puVar6 + 0x10);
  uVar4 = *(undefined4 *)(param_2 + 0x900);
  param_1[0x121] = (long)puVar2;
  *(undefined4 *)(param_1 + 0x120) = uVar4;
  puVar6 = PTR__ZTV22CParameterPropertyBaseILj215EE_02cbe558;
  param_1[0x122] = *(long *)(param_2 + 0x910);
  param_1[0x121] = (long)(puVar6 + 0x10);
  uVar5 = *(undefined1 *)(param_2 + 0x918);
  param_1[0x124] = (long)puVar3;
  *(undefined1 *)(param_1 + 0x123) = uVar5;
  puVar6 = PTR__ZTV23CParameterPropertyValueIjLj215E18CPropertyConverterE_02cb8d88;
  *(undefined4 *)(param_1 + 0x125) = *(undefined4 *)(param_2 + 0x928);
  param_1[0x121] = (long)(puVar6 + 0x10);
  uVar4 = *(undefined4 *)(param_2 + 0x930);
  param_1[0x127] = (long)puVar2;
  *(undefined4 *)(param_1 + 0x126) = uVar4;
  puVar6 = PTR__ZTV22CParameterPropertyBaseILj216EE_02cc16a8;
  param_1[0x128] = *(long *)(param_2 + 0x940);
  param_1[0x127] = (long)(puVar6 + 0x10);
  uVar5 = *(undefined1 *)(param_2 + 0x948);
  param_1[0x12a] = (long)puVar3;
  *(undefined1 *)(param_1 + 0x129) = uVar5;
  puVar6 = PTR__ZTV23CParameterPropertyValueIjLj216E18CPropertyConverterE_02cc47f0;
  *(undefined4 *)(param_1 + 299) = *(undefined4 *)(param_2 + 0x958);
  param_1[0x127] = (long)(puVar6 + 0x10);
  uVar4 = *(undefined4 *)(param_2 + 0x960);
  param_1[0x12d] = (long)puVar2;
  *(undefined4 *)(param_1 + 300) = uVar4;
  puVar6 = PTR__ZTV22CParameterPropertyBaseILj218EE_02cbe370;
  param_1[0x12e] = *(long *)(param_2 + 0x970);
  param_1[0x12d] = (long)(puVar6 + 0x10);
  uVar5 = *(undefined1 *)(param_2 + 0x978);
  param_1[0x130] = (long)puVar3;
  *(undefined1 *)(param_1 + 0x12f) = uVar5;
  puVar6 = PTR__ZTV23CParameterPropertyValueIjLj218E18CPropertyConverterE_02cbe2c0;
  *(undefined4 *)(param_1 + 0x131) = *(undefined4 *)(param_2 + 0x988);
  param_1[0x12d] = (long)(puVar6 + 0x10);
  uVar4 = *(undefined4 *)(param_2 + 0x990);
  param_1[0x133] = (long)puVar2;
  *(undefined4 *)(param_1 + 0x132) = uVar4;
  puVar6 = PTR__ZTV22CParameterPropertyBaseILj219EE_02cbbca8;
  param_1[0x134] = *(long *)(param_2 + 0x9a0);
  param_1[0x133] = (long)(puVar6 + 0x10);
  uVar5 = *(undefined1 *)(param_2 + 0x9a8);
  param_1[0x136] = (long)puVar3;
  *(undefined1 *)(param_1 + 0x135) = uVar5;
  puVar6 = PTR__ZTV23CParameterPropertyValueIjLj219E18CPropertyConverterE_02cc2f70;
  *(undefined4 *)(param_1 + 0x137) = *(undefined4 *)(param_2 + 0x9b8);
  param_1[0x133] = (long)(puVar6 + 0x10);
  uVar4 = *(undefined4 *)(param_2 + 0x9c0);
  param_1[0x139] = (long)puVar2;
  *(undefined4 *)(param_1 + 0x138) = uVar4;
  puVar6 = PTR__ZTV22CParameterPropertyBaseILj220EE_02cb7ab0;
  param_1[0x13a] = *(long *)(param_2 + 0x9d0);
  param_1[0x139] = (long)(puVar6 + 0x10);
  uVar5 = *(undefined1 *)(param_2 + 0x9d8);
  param_1[0x13c] = (long)puVar3;
  *(undefined1 *)(param_1 + 0x13b) = uVar5;
  puVar6 = PTR__ZTV23CParameterPropertyValueIjLj220E18CPropertyConverterE_02cb7fb8;
  *(undefined4 *)(param_1 + 0x13d) = *(undefined4 *)(param_2 + 0x9e8);
  param_1[0x139] = (long)(puVar6 + 0x10);
  uVar4 = *(undefined4 *)(param_2 + 0x9f0);
  param_1[0x13f] = (long)puVar2;
  *(undefined4 *)(param_1 + 0x13e) = uVar4;
  puVar6 = PTR__ZTV22CParameterPropertyBaseILj221EE_02cbf5d8;
  param_1[0x140] = *(long *)(param_2 + 0xa00);
  param_1[0x13f] = (long)(puVar6 + 0x10);
  uVar5 = *(undefined1 *)(param_2 + 0xa08);
  param_1[0x142] = (long)puVar3;
  *(undefined1 *)(param_1 + 0x141) = uVar5;
  puVar6 = PTR__ZTV23CParameterPropertyValueIjLj221E18CPropertyConverterE_02cc1d68;
  *(undefined4 *)(param_1 + 0x143) = *(undefined4 *)(param_2 + 0xa18);
  param_1[0x13f] = (long)(puVar6 + 0x10);
  uVar4 = *(undefined4 *)(param_2 + 0xa20);
  param_1[0x145] = (long)puVar2;
  *(undefined4 *)(param_1 + 0x144) = uVar4;
  puVar6 = PTR__ZTV22CParameterPropertyBaseILj222EE_02cbe6b8;
  param_1[0x146] = *(long *)(param_2 + 0xa30);
  param_1[0x145] = (long)(puVar6 + 0x10);
  uVar5 = *(undefined1 *)(param_2 + 0xa38);
  param_1[0x148] = (long)puVar3;
  *(undefined1 *)(param_1 + 0x147) = uVar5;
  puVar6 = PTR__ZTV23CParameterPropertyValueIjLj222E18CPropertyConverterE_02cbe898;
  *(undefined4 *)(param_1 + 0x149) = *(undefined4 *)(param_2 + 0xa48);
  param_1[0x145] = (long)(puVar6 + 0x10);
  uVar4 = *(undefined4 *)(param_2 + 0xa50);
  param_1[0x14b] = (long)puVar2;
  *(undefined4 *)(param_1 + 0x14a) = uVar4;
  puVar6 = PTR__ZTV22CParameterPropertyBaseILj224EE_02cba9c0;
  param_1[0x14c] = *(long *)(param_2 + 0xa60);
  param_1[0x14b] = (long)(puVar6 + 0x10);
  uVar5 = *(undefined1 *)(param_2 + 0xa68);
  param_1[0x14e] = (long)puVar3;
  *(undefined1 *)(param_1 + 0x14d) = uVar5;
  puVar6 = PTR__ZTV23CParameterPropertyValueIbLj224E18CPropertyConverterE_02cc40a8;
  *(undefined4 *)(param_1 + 0x14f) = *(undefined4 *)(param_2 + 0xa78);
  param_1[0x14b] = (long)(puVar6 + 0x10);
  uVar5 = *(undefined1 *)(param_2 + 0xa80);
  param_1[0x151] = (long)puVar2;
  *(undefined1 *)(param_1 + 0x150) = uVar5;
  puVar6 = PTR__ZTV22CParameterPropertyBaseILj225EE_02cbddf0;
  param_1[0x152] = *(long *)(param_2 + 0xa90);
  param_1[0x151] = (long)(puVar6 + 0x10);
  uVar5 = *(undefined1 *)(param_2 + 0xa98);
  param_1[0x154] = (long)puVar3;
  *(undefined1 *)(param_1 + 0x153) = uVar5;
  puVar6 = PTR__ZTV23CParameterPropertyValueIbLj225E18CPropertyConverterE_02cc07f8;
  *(undefined4 *)(param_1 + 0x155) = *(undefined4 *)(param_2 + 0xaa8);
  param_1[0x151] = (long)(puVar6 + 0x10);
  uVar5 = *(undefined1 *)(param_2 + 0xab0);
  param_1[0x157] = (long)puVar2;
  *(undefined1 *)(param_1 + 0x156) = uVar5;
  puVar6 = PTR__ZTV22CParameterPropertyBaseILj226EE_02cbea60;
  param_1[0x158] = *(long *)(param_2 + 0xac0);
  param_1[0x157] = (long)(puVar6 + 0x10);
  uVar5 = *(undefined1 *)(param_2 + 0xac8);
  param_1[0x15a] = (long)puVar3;
  *(undefined1 *)(param_1 + 0x159) = uVar5;
  puVar6 = PTR__ZTV23CParameterPropertyValueIjLj226E18CPropertyConverterE_02cbc950;
  *(undefined4 *)(param_1 + 0x15b) = *(undefined4 *)(param_2 + 0xad8);
  param_1[0x157] = (long)(puVar6 + 0x10);
  uVar4 = *(undefined4 *)(param_2 + 0xae0);
  param_1[0x15d] = (long)puVar2;
  *(undefined4 *)(param_1 + 0x15c) = uVar4;
  puVar6 = PTR__ZTV22CParameterPropertyBaseILj228EE_02cbf5e8;
  param_1[0x15e] = *(long *)(param_2 + 0xaf0);
  param_1[0x15d] = (long)(puVar6 + 0x10);
  uVar5 = *(undefined1 *)(param_2 + 0xaf8);
  param_1[0x160] = (long)puVar3;
  *(undefined1 *)(param_1 + 0x15f) = uVar5;
  puVar6 = PTR__ZTV23CParameterPropertyValueIjLj228E18CPropertyConverterE_02cc2500;
  *(undefined4 *)(param_1 + 0x161) = *(undefined4 *)(param_2 + 0xb08);
  param_1[0x15d] = (long)(puVar6 + 0x10);
  uVar4 = *(undefined4 *)(param_2 + 0xb10);
  param_1[0x163] = (long)puVar2;
  *(undefined4 *)(param_1 + 0x162) = uVar4;
  puVar6 = PTR__ZTV22CParameterPropertyBaseILj229EE_02cba790;
  param_1[0x164] = *(long *)(param_2 + 0xb20);
  param_1[0x163] = (long)(puVar6 + 0x10);
  uVar5 = *(undefined1 *)(param_2 + 0xb28);
  param_1[0x166] = (long)puVar3;
  *(undefined1 *)(param_1 + 0x165) = uVar5;
  puVar6 = PTR__ZTV23CParameterPropertyValueIjLj229E18CPropertyConverterE_02cc4cc8;
  *(undefined4 *)(param_1 + 0x167) = *(undefined4 *)(param_2 + 0xb38);
  param_1[0x163] = (long)(puVar6 + 0x10);
  uVar4 = *(undefined4 *)(param_2 + 0xb40);
  param_1[0x169] = (long)puVar2;
  *(undefined4 *)(param_1 + 0x168) = uVar4;
  puVar6 = PTR__ZTV22CParameterPropertyBaseILj230EE_02cc3050;
  param_1[0x16a] = *(long *)(param_2 + 0xb50);
  param_1[0x169] = (long)(puVar6 + 0x10);
  uVar5 = *(undefined1 *)(param_2 + 0xb58);
  param_1[0x16c] = (long)puVar3;
  *(undefined1 *)(param_1 + 0x16b) = uVar5;
  puVar6 = PTR__ZTV23CParameterPropertyValueIjLj230E18CPropertyConverterE_02cbe4b8;
  *(undefined4 *)(param_1 + 0x16d) = *(undefined4 *)(param_2 + 0xb68);
  param_1[0x169] = (long)(puVar6 + 0x10);
  uVar4 = *(undefined4 *)(param_2 + 0xb70);
  param_1[0x16f] = (long)puVar2;
  *(undefined4 *)(param_1 + 0x16e) = uVar4;
  puVar6 = PTR__ZTV22CParameterPropertyBaseILj231EE_02cc1ee0;
  param_1[0x170] = *(long *)(param_2 + 0xb80);
  param_1[0x16f] = (long)(puVar6 + 0x10);
  uVar5 = *(undefined1 *)(param_2 + 0xb88);
  param_1[0x172] = (long)puVar3;
  *(undefined1 *)(param_1 + 0x171) = uVar5;
  puVar6 = PTR__ZTV23CParameterPropertyValueIjLj231E18CPropertyConverterE_02cc2d08;
  *(undefined4 *)(param_1 + 0x173) = *(undefined4 *)(param_2 + 0xb98);
  param_1[0x16f] = (long)(puVar6 + 0x10);
  uVar4 = *(undefined4 *)(param_2 + 0xba0);
  param_1[0x175] = (long)puVar2;
  *(undefined4 *)(param_1 + 0x174) = uVar4;
  puVar6 = PTR__ZTV22CParameterPropertyBaseILj232EE_02cbee90;
  param_1[0x176] = *(long *)(param_2 + 0xbb0);
  param_1[0x175] = (long)(puVar6 + 0x10);
  uVar5 = *(undefined1 *)(param_2 + 3000);
  param_1[0x178] = (long)puVar3;
  *(undefined1 *)(param_1 + 0x177) = uVar5;
  puVar6 = PTR__ZTV23CParameterPropertyValueIjLj232E18CPropertyConverterE_02cc05f8;
  *(undefined4 *)(param_1 + 0x179) = *(undefined4 *)(param_2 + 0xbc8);
  param_1[0x175] = (long)(puVar6 + 0x10);
  uVar4 = *(undefined4 *)(param_2 + 0xbd0);
  param_1[0x17b] = (long)puVar2;
  *(undefined4 *)(param_1 + 0x17a) = uVar4;
  puVar6 = PTR__ZTV22CParameterPropertyBaseILj233EE_02cb7178;
  param_1[0x17c] = *(long *)(param_2 + 0xbe0);
  param_1[0x17b] = (long)(puVar6 + 0x10);
  uVar5 = *(undefined1 *)(param_2 + 0xbe8);
  param_1[0x17e] = (long)puVar3;
  *(undefined1 *)(param_1 + 0x17d) = uVar5;
  puVar6 = PTR__ZTV23CParameterPropertyValueIjLj233E18CPropertyConverterE_02cbe3e0;
  *(undefined4 *)(param_1 + 0x17f) = *(undefined4 *)(param_2 + 0xbf8);
  param_1[0x17b] = (long)(puVar6 + 0x10);
  uVar4 = *(undefined4 *)(param_2 + 0xc00);
  param_1[0x181] = (long)puVar2;
  *(undefined4 *)(param_1 + 0x180) = uVar4;
  puVar6 = PTR__ZTV22CParameterPropertyBaseILj234EE_02cba3b8;
  param_1[0x182] = *(long *)(param_2 + 0xc10);
  param_1[0x181] = (long)(puVar6 + 0x10);
  uVar5 = *(undefined1 *)(param_2 + 0xc18);
  param_1[0x184] = (long)puVar3;
  *(undefined1 *)(param_1 + 0x183) = uVar5;
  puVar6 = PTR__ZTV23CParameterPropertyValueIjLj234E18CPropertyConverterE_02cc2bd0;
  *(undefined4 *)(param_1 + 0x185) = *(undefined4 *)(param_2 + 0xc28);
  param_1[0x181] = (long)(puVar6 + 0x10);
  uVar4 = *(undefined4 *)(param_2 + 0xc30);
  param_1[0x187] = (long)puVar2;
  *(undefined4 *)(param_1 + 0x186) = uVar4;
  puVar6 = PTR__ZTV22CParameterPropertyBaseILj236EE_02cb7068;
  param_1[0x188] = *(long *)(param_2 + 0xc40);
  param_1[0x187] = (long)(puVar6 + 0x10);
  uVar5 = *(undefined1 *)(param_2 + 0xc48);
  param_1[0x18a] = (long)puVar3;
  *(undefined1 *)(param_1 + 0x189) = uVar5;
  puVar6 = PTR__ZTV23CParameterPropertyValueIjLj236E18CPropertyConverterE_02cc2178;
  *(undefined4 *)(param_1 + 0x18b) = *(undefined4 *)(param_2 + 0xc58);
  param_1[0x187] = (long)(puVar6 + 0x10);
  uVar4 = *(undefined4 *)(param_2 + 0xc60);
  param_1[0x18d] = (long)puVar2;
  *(undefined4 *)(param_1 + 0x18c) = uVar4;
  puVar6 = PTR__ZTV22CParameterPropertyBaseILj238EE_02cb6ed0;
  param_1[0x18e] = *(long *)(param_2 + 0xc70);
  param_1[0x18d] = (long)(puVar6 + 0x10);
  uVar5 = *(undefined1 *)(param_2 + 0xc78);
  param_1[400] = (long)puVar3;
  *(undefined1 *)(param_1 + 399) = uVar5;
  puVar6 = PTR__ZTV23CParameterPropertyValueIjLj238E18CPropertyConverterE_02cbdb78;
  *(undefined4 *)(param_1 + 0x191) = *(undefined4 *)(param_2 + 0xc88);
  param_1[0x18d] = (long)(puVar6 + 0x10);
  uVar4 = *(undefined4 *)(param_2 + 0xc90);
  param_1[0x193] = (long)puVar2;
  *(undefined4 *)(param_1 + 0x192) = uVar4;
  puVar6 = PTR__ZTV22CParameterPropertyBaseILj239EE_02cbedf0;
  param_1[0x194] = *(long *)(param_2 + 0xca0);
  param_1[0x193] = (long)(puVar6 + 0x10);
  uVar5 = *(undefined1 *)(param_2 + 0xca8);
  param_1[0x196] = (long)puVar3;
  *(undefined1 *)(param_1 + 0x195) = uVar5;
  puVar6 = PTR__ZTV23CParameterPropertyValueIjLj239E18CPropertyConverterE_02cb84c8;
  *(undefined4 *)(param_1 + 0x197) = *(undefined4 *)(param_2 + 0xcb8);
  param_1[0x193] = (long)(puVar6 + 0x10);
  uVar4 = *(undefined4 *)(param_2 + 0xcc0);
  param_1[0x199] = (long)puVar2;
  *(undefined4 *)(param_1 + 0x198) = uVar4;
  puVar6 = PTR__ZTV22CParameterPropertyBaseILj240EE_02cc1fa0;
  param_1[0x19a] = *(long *)(param_2 + 0xcd0);
  param_1[0x199] = (long)(puVar6 + 0x10);
  uVar5 = *(undefined1 *)(param_2 + 0xcd8);
  param_1[0x19c] = (long)puVar3;
  *(undefined1 *)(param_1 + 0x19b) = uVar5;
  puVar6 = PTR__ZTV23CParameterPropertyValueIjLj240E18CPropertyConverterE_02cbeba0;
  *(undefined4 *)(param_1 + 0x19d) = *(undefined4 *)(param_2 + 0xce8);
  param_1[0x199] = (long)(puVar6 + 0x10);
  uVar4 = *(undefined4 *)(param_2 + 0xcf0);
  param_1[0x19f] = (long)puVar2;
  *(undefined4 *)(param_1 + 0x19e) = uVar4;
  puVar6 = PTR__ZTV22CParameterPropertyBaseILj242EE_02cc2db0;
  param_1[0x1a0] = *(long *)(param_2 + 0xd00);
  param_1[0x19f] = (long)(puVar6 + 0x10);
  uVar5 = *(undefined1 *)(param_2 + 0xd08);
  param_1[0x1a2] = (long)puVar3;
  *(undefined1 *)(param_1 + 0x1a1) = uVar5;
  puVar6 = PTR__ZTV23CParameterPropertyValueIbLj242E18CPropertyConverterE_02cc1718;
  *(undefined4 *)(param_1 + 0x1a3) = *(undefined4 *)(param_2 + 0xd18);
  param_1[0x19f] = (long)(puVar6 + 0x10);
  uVar5 = *(undefined1 *)(param_2 + 0xd20);
  param_1[0x1a5] = (long)puVar2;
  *(undefined1 *)(param_1 + 0x1a4) = uVar5;
  puVar6 = PTR__ZTV22CParameterPropertyBaseILj243EE_02cbc5c0;
  param_1[0x1a6] = *(long *)(param_2 + 0xd30);
  param_1[0x1a5] = (long)(puVar6 + 0x10);
  uVar5 = *(undefined1 *)(param_2 + 0xd38);
  param_1[0x1a8] = (long)puVar3;
  *(undefined1 *)(param_1 + 0x1a7) = uVar5;
  puVar6 = PTR__ZTV23CParameterPropertyValueIjLj243E18CPropertyConverterE_02cb95c8;
  *(undefined4 *)(param_1 + 0x1a9) = *(undefined4 *)(param_2 + 0xd48);
  param_1[0x1a5] = (long)(puVar6 + 0x10);
  uVar4 = *(undefined4 *)(param_2 + 0xd50);
  param_1[0x1ab] = (long)puVar2;
  *(undefined4 *)(param_1 + 0x1aa) = uVar4;
  puVar6 = PTR__ZTV22CParameterPropertyBaseILj244EE_02cc32b0;
  param_1[0x1ac] = *(long *)(param_2 + 0xd60);
  param_1[0x1ab] = (long)(puVar6 + 0x10);
  uVar5 = *(undefined1 *)(param_2 + 0xd68);
  param_1[0x1ae] = (long)puVar3;
  *(undefined1 *)(param_1 + 0x1ad) = uVar5;
  puVar6 = PTR__ZTV23CParameterPropertyValueIjLj244E18CPropertyConverterE_02cb9768;
  *(undefined4 *)(param_1 + 0x1af) = *(undefined4 *)(param_2 + 0xd78);
  param_1[0x1ab] = (long)(puVar6 + 0x10);
  uVar4 = *(undefined4 *)(param_2 + 0xd80);
  param_1[0x1b1] = (long)puVar2;
  *(undefined4 *)(param_1 + 0x1b0) = uVar4;
  puVar6 = PTR__ZTV22CParameterPropertyBaseILj245EE_02cbef20;
  param_1[0x1b2] = *(long *)(param_2 + 0xd90);
  param_1[0x1b1] = (long)(puVar6 + 0x10);
  uVar5 = *(undefined1 *)(param_2 + 0xd98);
  param_1[0x1b4] = (long)puVar3;
  *(undefined1 *)(param_1 + 0x1b3) = uVar5;
  puVar6 = PTR__ZTV23CParameterPropertyValueIjLj245E18CPropertyConverterE_02cbf180;
  *(undefined4 *)(param_1 + 0x1b5) = *(undefined4 *)(param_2 + 0xda8);
  param_1[0x1b1] = (long)(puVar6 + 0x10);
  uVar4 = *(undefined4 *)(param_2 + 0xdb0);
  param_1[0x1b7] = (long)puVar2;
  *(undefined4 *)(param_1 + 0x1b6) = uVar4;
  puVar6 = PTR__ZTV22CParameterPropertyBaseILj247EE_02cb7350;
  param_1[0x1b8] = *(long *)(param_2 + 0xdc0);
  param_1[0x1b7] = (long)(puVar6 + 0x10);
  uVar5 = *(undefined1 *)(param_2 + 0xdc8);
  param_1[0x1ba] = (long)puVar3;
  *(undefined1 *)(param_1 + 0x1b9) = uVar5;
  puVar6 = PTR__ZTV23CParameterPropertyValueIjLj247E18CPropertyConverterE_02cbf148;
  *(undefined4 *)(param_1 + 0x1bb) = *(undefined4 *)(param_2 + 0xdd8);
  param_1[0x1b7] = (long)(puVar6 + 0x10);
  uVar4 = *(undefined4 *)(param_2 + 0xde0);
  param_1[0x1bd] = (long)puVar2;
  *(undefined4 *)(param_1 + 0x1bc) = uVar4;
  puVar6 = PTR__ZTV22CParameterPropertyBaseILj248EE_02cbb3a0;
  param_1[0x1be] = *(long *)(param_2 + 0xdf0);
  param_1[0x1bd] = (long)(puVar6 + 0x10);
  uVar5 = *(undefined1 *)(param_2 + 0xdf8);
  param_1[0x1c0] = (long)puVar3;
  *(undefined1 *)(param_1 + 0x1bf) = uVar5;
  puVar6 = PTR__ZTV23CParameterPropertyValueIjLj248E18CPropertyConverterE_02cc34e0;
  *(undefined4 *)(param_1 + 0x1c1) = *(undefined4 *)(param_2 + 0xe08);
  param_1[0x1bd] = (long)(puVar6 + 0x10);
  uVar4 = *(undefined4 *)(param_2 + 0xe10);
  param_1[0x1c3] = (long)puVar2;
  *(undefined4 *)(param_1 + 0x1c2) = uVar4;
  puVar6 = PTR__ZTV22CParameterPropertyBaseILj249EE_02cc1d38;
  param_1[0x1c4] = *(long *)(param_2 + 0xe20);
  param_1[0x1c3] = (long)(puVar6 + 0x10);
  uVar5 = *(undefined1 *)(param_2 + 0xe28);
  param_1[0x1c6] = (long)puVar3;
  *(undefined1 *)(param_1 + 0x1c5) = uVar5;
  puVar6 = PTR__ZTV23CParameterPropertyValueIjLj249E18CPropertyConverterE_02cba140;
  *(undefined4 *)(param_1 + 0x1c7) = *(undefined4 *)(param_2 + 0xe38);
  param_1[0x1c3] = (long)(puVar6 + 0x10);
  uVar4 = *(undefined4 *)(param_2 + 0xe40);
  param_1[0x1c9] = (long)puVar1;
  *(undefined4 *)(param_1 + 0x1c8) = uVar4;
  Framework::CSTLMap<unsigned int, IParameterProperty*>::CSTLMap(Framework::CSTLMap<unsigned int, IParameterProperty*> const&)(param_1 + 0x1ca,param_2 + 0xe50);
  Framework::CSTLMap<unsigned int, InfoBase*>::CSTLMap(Framework::CSTLMap<unsigned int, InfoBase*> const&)(param_1 + 0x1cd,param_2 + 0xe68);
  puVar6 = PTR__ZTV16AssistDetailInfo_02cc23a8;
  param_1[0x1d0] = (long)puVar2;
  param_1[0x1c9] = (long)(puVar6 + 0x10);
  puVar6 = PTR__ZTV22CParameterPropertyBaseILj20EE_02cc0d08;
  param_1[0x1d1] = *(long *)(param_2 + 0xe88);
  param_1[0x1d0] = (long)(puVar6 + 0x10);
  uVar5 = *(undefined1 *)(param_2 + 0xe90);
  param_1[0x1d3] = (long)puVar3;
  *(undefined1 *)(param_1 + 0x1d2) = uVar5;
  puVar6 = PTR__ZTV23CParameterPropertyValueIjLj20E18CPropertyConverterE_02cc2ce0;
  *(undefined4 *)(param_1 + 0x1d4) = *(undefined4 *)(param_2 + 0xea0);
  param_1[0x1d0] = (long)(puVar6 + 0x10);
  uVar4 = *(undefined4 *)(param_2 + 0xea8);
  param_1[0x1d6] = (long)puVar2;
  *(undefined4 *)(param_1 + 0x1d5) = uVar4;
  puVar6 = PTR__ZTV22CParameterPropertyBaseILj21EE_02cc1310;
  param_1[0x1d7] = *(long *)(param_2 + 0xeb8);
  param_1[0x1d6] = (long)(puVar6 + 0x10);
  uVar5 = *(undefined1 *)(param_2 + 0xec0);
  param_1[0x1d9] = (long)puVar3;
  *(undefined1 *)(param_1 + 0x1d8) = uVar5;
  puVar6 = PTR__ZTV23CParameterPropertyValueIjLj21E18CPropertyConverterE_02cbeae0;
  *(undefined4 *)(param_1 + 0x1da) = *(undefined4 *)(param_2 + 0xed0);
  param_1[0x1d6] = (long)(puVar6 + 0x10);
  uVar4 = *(undefined4 *)(param_2 + 0xed8);
  param_1[0x1dc] = (long)puVar2;
  *(undefined4 *)(param_1 + 0x1db) = uVar4;
  puVar6 = PTR__ZTV22CParameterPropertyBaseILj22EE_02cc4630;
  param_1[0x1dd] = *(long *)(param_2 + 0xee8);
  param_1[0x1dc] = (long)(puVar6 + 0x10);
  uVar5 = *(undefined1 *)(param_2 + 0xef0);
  param_1[0x1df] = (long)puVar3;
  *(undefined1 *)(param_1 + 0x1de) = uVar5;
  puVar6 = PTR__ZTV23CParameterPropertyValueIjLj22E18CPropertyConverterE_02cb7420;
  *(undefined4 *)(param_1 + 0x1e0) = *(undefined4 *)(param_2 + 0xf00);
  param_1[0x1dc] = (long)(puVar6 + 0x10);
  uVar4 = *(undefined4 *)(param_2 + 0xf08);
  param_1[0x1e2] = (long)puVar1;
  *(undefined4 *)(param_1 + 0x1e1) = uVar4;
  Framework::CSTLMap<unsigned int, IParameterProperty*>::CSTLMap(Framework::CSTLMap<unsigned int, IParameterProperty*> const&)(param_1 + 0x1e3,param_2 + 0xf18);
  Framework::CSTLMap<unsigned int, InfoBase*>::CSTLMap(Framework::CSTLMap<unsigned int, InfoBase*> const&)(param_1 + 0x1e6,param_2 + 0xf30);
  param_1[0x1eb] = 0;
  param_1[0x1ea] = 0;
  param_1[0x1e9] = (long)(param_1 + 0x1ea);
  if (*(long **)(param_2 + 0xf48) != (long *)(param_2 + 0xf50)) {
    plVar10 = *(long **)(param_2 + 0xf48);
    do {
      std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned long, CFactorInfo>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CFactorInfo>, void*>*, long> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CFactorInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CFactorInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CFactorInfo>, Framework::CSTLMapAllocatorInf> >::__emplace_hint_unique_key_args<unsigned long, std::__ndk1::pair<unsigned long const, CFactorInfo> const&>(std::__ndk1::__tree_const_iterator<std::__ndk1::__value_type<unsigned long, CFactorInfo>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CFactorInfo>, void*>*, long>, unsigned long const&, std::__ndk1::pair<unsigned long const, CFactorInfo> const&)(param_1 + 0x1e9,param_1 + 0x1ea,plVar10 + 4,plVar10 + 4);
      plVar7 = (long *)plVar10[1];
      if ((long *)plVar10[1] == (long *)0x0) {
        do {
          plVar11 = (long *)plVar10[2];
          bVar8 = (long *)*plVar11 != plVar10;
          plVar10 = plVar11;
        } while (bVar8);
      }
      else {
        do {
          plVar11 = plVar7;
          plVar7 = (long *)*plVar11;
        } while ((long *)*plVar11 != (long *)0x0);
      }
      plVar10 = plVar11;
    } while (plVar11 != (long *)(param_2 + 0xf50));
  }
  puVar6 = PTR__ZTV14CFactorInfoMap_02cb9808;
  param_1[0x1ec] = (long)puVar1;
  param_1[0x1e2] = (long)(puVar6 + 0x10);
  Framework::CSTLMap<unsigned int, IParameterProperty*>::CSTLMap(Framework::CSTLMap<unsigned int, IParameterProperty*> const&)(param_1 + 0x1ed,param_2 + 0xf68);
  Framework::CSTLMap<unsigned int, InfoBase*>::CSTLMap(Framework::CSTLMap<unsigned int, InfoBase*> const&)(param_1 + 0x1f0,param_2 + 0xf80);
  param_1[0x1f5] = 0;
  param_1[500] = 0;
  param_1[499] = 0;
  param_1[499] = *(long *)(param_2 + 0xf98);
  param_1[500] = *(long *)(param_2 + 4000);
  puVar6 = PTR__ZTV28CCharacterDecoObjectInfoList_02cc4040;
  param_1[0x1f5] = *(long *)(param_2 + 0xfa8);
  *(undefined8 *)(param_2 + 0xfa8) = 0;
  *(undefined8 *)(param_2 + 4000) = 0;
  *(undefined8 *)(param_2 + 0xf98) = 0;
  param_1[0x1ec] = (long)(puVar6 + 0x10);
  param_1[0x1f6] = (long)puVar1;
  Framework::CSTLMap<unsigned int, IParameterProperty*>::CSTLMap(Framework::CSTLMap<unsigned int, IParameterProperty*> const&)(param_1 + 0x1f7,param_2 + 0xfb8);
  Framework::CSTLMap<unsigned int, InfoBase*>::CSTLMap(Framework::CSTLMap<unsigned int, InfoBase*> const&)(param_1 + 0x1fa,param_2 + 0xfd0);
  param_1[0x1ff] = 0;
  param_1[0x1fe] = 0;
  param_1[0x1fd] = 0;
  param_1[0x1fd] = *(long *)(param_2 + 0xfe8);
  param_1[0x1fe] = *(long *)(param_2 + 0xff0);
  puVar6 = PTR__ZTV31UniverseEffectualTalentInfoList_02cc2e78;
  param_1[0x1ff] = *(long *)(param_2 + 0xff8);
  *(undefined8 *)(param_2 + 0xff8) = 0;
  *(undefined8 *)(param_2 + 0xff0) = 0;
  *(undefined8 *)(param_2 + 0xfe8) = 0;
  param_1[0x1f6] = (long)(puVar6 + 0x10);
  UniverseAddStatusInfo::UniverseAddStatusInfo(UniverseAddStatusInfo&&)(param_1 + 0x200,param_2 + 0x1000);
  UniverseDeityBoostInfo::UniverseDeityBoostInfo(UniverseDeityBoostInfo&&)(param_1 + 0x23d,param_2 + 0x11e8);
  param_1[0x27a] = (long)puVar1;
  Framework::CSTLMap<unsigned int, IParameterProperty*>::CSTLMap(Framework::CSTLMap<unsigned int, IParameterProperty*> const&)(param_1 + 0x27b,param_2 + 0x13d8);
  Framework::CSTLMap<unsigned int, InfoBase*>::CSTLMap(Framework::CSTLMap<unsigned int, InfoBase*> const&)(param_1 + 0x27e,param_2 + 0x13f0);
  puVar6 = PTR__ZTV9DeityInfo_02cc11d0;
  param_1[0x281] = (long)puVar2;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj47EE_02cba780;
  param_1[0x27a] = (long)(puVar6 + 0x10);
  lVar9 = *(long *)(param_2 + 0x1410);
  param_1[0x281] = (long)(puVar1 + 0x10);
  param_1[0x282] = lVar9;
  *(undefined1 *)(param_1 + 0x283) = *(undefined1 *)(param_2 + 0x1418);
  param_1[0x284] = (long)puVar3;
  puVar1 = PTR__ZTV23CParameterPropertyValueIjLj47E18CPropertyConverterE_02cc0678;
  *(undefined4 *)(param_1 + 0x285) = *(undefined4 *)(param_2 + 0x1428);
  param_1[0x281] = (long)(puVar1 + 0x10);
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj48EE_02cba0d0;
  uVar4 = *(undefined4 *)(param_2 + 0x1430);
  param_1[0x287] = (long)puVar2;
  *(undefined4 *)(param_1 + 0x286) = uVar4;
  lVar9 = *(long *)(param_2 + 0x1440);
  param_1[0x287] = (long)(puVar1 + 0x10);
  param_1[0x288] = lVar9;
  *(undefined1 *)(param_1 + 0x289) = *(undefined1 *)(param_2 + 0x1448);
  param_1[0x28a] = (long)puVar3;
  puVar1 = PTR__ZTV23CParameterPropertyValueIjLj48E18CPropertyConverterE_02cc4e68;
  *(undefined4 *)(param_1 + 0x28b) = *(undefined4 *)(param_2 + 0x1458);
  param_1[0x287] = (long)(puVar1 + 0x10);
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj49EE_02cc4550;
  uVar4 = *(undefined4 *)(param_2 + 0x1460);
  param_1[0x28d] = (long)puVar2;
  *(undefined4 *)(param_1 + 0x28c) = uVar4;
  lVar9 = *(long *)(param_2 + 0x1470);
  param_1[0x28d] = (long)(puVar1 + 0x10);
  param_1[0x28e] = lVar9;
  *(undefined1 *)(param_1 + 0x28f) = *(undefined1 *)(param_2 + 0x1478);
  param_1[0x290] = (long)puVar3;
  puVar1 = PTR__ZTV23CParameterPropertyValueIjLj49E18CPropertyConverterE_02cc0590;
  *(undefined4 *)(param_1 + 0x291) = *(undefined4 *)(param_2 + 0x1488);
  param_1[0x28d] = (long)(puVar1 + 0x10);
  *(undefined4 *)(param_1 + 0x292) = *(undefined4 *)(param_2 + 0x1490);
  UniverseDeityBoostInfo::UniverseDeityBoostInfo(UniverseDeityBoostInfo&&)(param_1 + 0x293,param_2 + 0x1498);
  param_1[0x293] = (long)(PTR__ZTV23AddBuffByDeityCharacter_02cc2950 + 0x10);
  lVar9 = *(long *)(param_2 + 0x1680);
  param_1[0x2d1] = *(long *)(param_2 + 0x1688);
  param_1[0x2d0] = lVar9;
  return;
}

// ==== CPersonStatusInfo::operator=(CPersonStatusInfo&&)
// vaddr 0x16d764c | ghidra 0x17d764c | size 3328 | symbol _ZN17CPersonStatusInfoaSEOS_ | lib libSOA-3.7.0.so | 2026-10-08
long _ZN17CPersonStatusInfoaSEOS_(long param_1,long param_2)

{
  undefined8 *puVar1;
  byte *pbVar2;
  undefined8 uVar3;
  
  if (param_1 != param_2) {
    void std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::__assign_multi<std::__ndk1::__tree_const_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long> >(std::__ndk1::__tree_const_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>, std::__ndk1::__tree_const_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>)(param_1 + 8,*(undefined8 *)(param_2 + 8),param_2 + 0x10);
    void std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::__assign_multi<std::__ndk1::__tree_const_iterator<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*, long> >(std::__ndk1::__tree_const_iterator<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*, long>, std::__ndk1::__tree_const_iterator<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*, long>)(param_1 + 0x20,*(undefined8 *)(param_2 + 0x20),param_2 + 0x28);
  }
  *(undefined8 *)(param_1 + 0x40) = *(undefined8 *)(param_2 + 0x40);
  *(undefined1 *)(param_1 + 0x48) = *(undefined1 *)(param_2 + 0x48);
  *(undefined4 *)(param_1 + 0x58) = *(undefined4 *)(param_2 + 0x58);
  *(undefined8 *)(param_1 + 0x60) = *(undefined8 *)(param_2 + 0x60);
  *(undefined8 *)(param_1 + 0x70) = *(undefined8 *)(param_2 + 0x70);
  *(undefined1 *)(param_1 + 0x78) = *(undefined1 *)(param_2 + 0x78);
  *(undefined4 *)(param_1 + 0x88) = *(undefined4 *)(param_2 + 0x88);
  *(undefined4 *)(param_1 + 0x90) = *(undefined4 *)(param_2 + 0x90);
  *(undefined8 *)(param_1 + 0xa0) = *(undefined8 *)(param_2 + 0xa0);
  *(undefined1 *)(param_1 + 0xa8) = *(undefined1 *)(param_2 + 0xa8);
  *(undefined4 *)(param_1 + 0xb8) = *(undefined4 *)(param_2 + 0xb8);
  pbVar2 = (byte *)(param_1 + 0xc0);
  if ((*pbVar2 & 1) == 0) {
    pbVar2[0] = 0;
    pbVar2[1] = 0;
  }
  else {
    **(undefined1 **)(param_1 + 0xd0) = 0;
    *(undefined8 *)(param_1 + 200) = 0;
  }
  string::reserve(unsigned long)(pbVar2,0);
  *(undefined8 *)(param_1 + 0xd0) = *(undefined8 *)(param_2 + 0xd0);
  uVar3 = *(undefined8 *)(param_2 + 0xc0);
  *(undefined8 *)(param_1 + 200) = *(undefined8 *)(param_2 + 200);
  *(undefined8 *)pbVar2 = uVar3;
  *(undefined8 *)(param_2 + 200) = 0;
  *(undefined8 *)(param_2 + 0xd0) = 0;
  *(undefined8 *)(param_2 + 0xc0) = 0;
  puVar1 = (undefined8 *)(param_1 + 0x280);
  *(undefined8 *)(param_1 + 0xe0) = *(undefined8 *)(param_2 + 0xe0);
  *(undefined1 *)(param_1 + 0xe8) = *(undefined1 *)(param_2 + 0xe8);
  *(undefined4 *)(param_1 + 0xf8) = *(undefined4 *)(param_2 + 0xf8);
  *(undefined4 *)(param_1 + 0x100) = *(undefined4 *)(param_2 + 0x100);
  *(undefined8 *)(param_1 + 0x110) = *(undefined8 *)(param_2 + 0x110);
  *(undefined1 *)(param_1 + 0x118) = *(undefined1 *)(param_2 + 0x118);
  *(undefined4 *)(param_1 + 0x128) = *(undefined4 *)(param_2 + 0x128);
  *(undefined4 *)(param_1 + 0x130) = *(undefined4 *)(param_2 + 0x130);
  *(undefined8 *)(param_1 + 0x140) = *(undefined8 *)(param_2 + 0x140);
  *(undefined1 *)(param_1 + 0x148) = *(undefined1 *)(param_2 + 0x148);
  *(undefined4 *)(param_1 + 0x158) = *(undefined4 *)(param_2 + 0x158);
  *(undefined8 *)(param_1 + 0x160) = *(undefined8 *)(param_2 + 0x160);
  *(undefined8 *)(param_1 + 0x170) = *(undefined8 *)(param_2 + 0x170);
  *(undefined1 *)(param_1 + 0x178) = *(undefined1 *)(param_2 + 0x178);
  *(undefined4 *)(param_1 + 0x188) = *(undefined4 *)(param_2 + 0x188);
  *(undefined8 *)(param_1 + 400) = *(undefined8 *)(param_2 + 400);
  *(undefined8 *)(param_1 + 0x1a0) = *(undefined8 *)(param_2 + 0x1a0);
  *(undefined1 *)(param_1 + 0x1a8) = *(undefined1 *)(param_2 + 0x1a8);
  *(undefined4 *)(param_1 + 0x1b8) = *(undefined4 *)(param_2 + 0x1b8);
  *(undefined4 *)(param_1 + 0x1c0) = *(undefined4 *)(param_2 + 0x1c0);
  *(undefined8 *)(param_1 + 0x1d0) = *(undefined8 *)(param_2 + 0x1d0);
  *(undefined1 *)(param_1 + 0x1d8) = *(undefined1 *)(param_2 + 0x1d8);
  *(undefined4 *)(param_1 + 0x1e8) = *(undefined4 *)(param_2 + 0x1e8);
  *(undefined4 *)(param_1 + 0x1f0) = *(undefined4 *)(param_2 + 0x1f0);
  *(undefined8 *)(param_1 + 0x200) = *(undefined8 *)(param_2 + 0x200);
  *(undefined1 *)(param_1 + 0x208) = *(undefined1 *)(param_2 + 0x208);
  *(undefined4 *)(param_1 + 0x218) = *(undefined4 *)(param_2 + 0x218);
  *(undefined4 *)(param_1 + 0x220) = *(undefined4 *)(param_2 + 0x220);
  *(undefined8 *)(param_1 + 0x230) = *(undefined8 *)(param_2 + 0x230);
  *(undefined1 *)(param_1 + 0x238) = *(undefined1 *)(param_2 + 0x238);
  *(undefined4 *)(param_1 + 0x248) = *(undefined4 *)(param_2 + 0x248);
  *(undefined4 *)(param_1 + 0x250) = *(undefined4 *)(param_2 + 0x250);
  *(undefined8 *)(param_1 + 0x260) = *(undefined8 *)(param_2 + 0x260);
  *(undefined1 *)(param_1 + 0x268) = *(undefined1 *)(param_2 + 0x268);
  *(undefined4 *)(param_1 + 0x278) = *(undefined4 *)(param_2 + 0x278);
  if ((*(byte *)(param_1 + 0x280) & 1) == 0) {
    *(undefined2 *)puVar1 = 0;
  }
  else {
    **(undefined1 **)(param_1 + 0x290) = 0;
    *(undefined8 *)(param_1 + 0x288) = 0;
  }
  string::reserve(unsigned long)(puVar1,0);
  *(undefined8 *)(param_1 + 0x290) = *(undefined8 *)(param_2 + 0x290);
  uVar3 = *(undefined8 *)(param_2 + 0x280);
  *(undefined8 *)(param_1 + 0x288) = *(undefined8 *)(param_2 + 0x288);
  *puVar1 = uVar3;
  *(undefined8 *)(param_2 + 0x288) = 0;
  *(undefined8 *)(param_2 + 0x290) = 0;
  *(undefined8 *)(param_2 + 0x280) = 0;
  puVar1 = (undefined8 *)(param_1 + 800);
  *(undefined8 *)(param_1 + 0x2a0) = *(undefined8 *)(param_2 + 0x2a0);
  *(undefined1 *)(param_1 + 0x2a8) = *(undefined1 *)(param_2 + 0x2a8);
  *(undefined4 *)(param_1 + 0x2b8) = *(undefined4 *)(param_2 + 0x2b8);
  *(undefined4 *)(param_1 + 0x2c0) = *(undefined4 *)(param_2 + 0x2c0);
  *(undefined8 *)(param_1 + 0x2d0) = *(undefined8 *)(param_2 + 0x2d0);
  *(undefined1 *)(param_1 + 0x2d8) = *(undefined1 *)(param_2 + 0x2d8);
  *(undefined4 *)(param_1 + 0x2e8) = *(undefined4 *)(param_2 + 0x2e8);
  *(undefined4 *)(param_1 + 0x2f0) = *(undefined4 *)(param_2 + 0x2f0);
  *(undefined8 *)(param_1 + 0x300) = *(undefined8 *)(param_2 + 0x300);
  *(undefined1 *)(param_1 + 0x308) = *(undefined1 *)(param_2 + 0x308);
  *(undefined4 *)(param_1 + 0x318) = *(undefined4 *)(param_2 + 0x318);
  if ((*(byte *)(param_1 + 800) & 1) == 0) {
    *(undefined2 *)puVar1 = 0;
  }
  else {
    **(undefined1 **)(param_1 + 0x330) = 0;
    *(undefined8 *)(param_1 + 0x328) = 0;
  }
  string::reserve(unsigned long)(puVar1,0);
  *(undefined8 *)(param_1 + 0x330) = *(undefined8 *)(param_2 + 0x330);
  uVar3 = *(undefined8 *)(param_2 + 800);
  *(undefined8 *)(param_1 + 0x328) = *(undefined8 *)(param_2 + 0x328);
  *puVar1 = uVar3;
  *(undefined8 *)(param_2 + 0x328) = 0;
  *(undefined8 *)(param_2 + 0x330) = 0;
  *(undefined8 *)(param_2 + 800) = 0;
  puVar1 = (undefined8 *)(param_1 + 0x3c0);
  *(undefined8 *)(param_1 + 0x340) = *(undefined8 *)(param_2 + 0x340);
  *(undefined1 *)(param_1 + 0x348) = *(undefined1 *)(param_2 + 0x348);
  *(undefined4 *)(param_1 + 0x358) = *(undefined4 *)(param_2 + 0x358);
  *(undefined4 *)(param_1 + 0x360) = *(undefined4 *)(param_2 + 0x360);
  *(undefined8 *)(param_1 + 0x370) = *(undefined8 *)(param_2 + 0x370);
  *(undefined1 *)(param_1 + 0x378) = *(undefined1 *)(param_2 + 0x378);
  *(undefined4 *)(param_1 + 0x388) = *(undefined4 *)(param_2 + 0x388);
  *(undefined4 *)(param_1 + 0x390) = *(undefined4 *)(param_2 + 0x390);
  *(undefined8 *)(param_1 + 0x3a0) = *(undefined8 *)(param_2 + 0x3a0);
  *(undefined1 *)(param_1 + 0x3a8) = *(undefined1 *)(param_2 + 0x3a8);
  *(undefined4 *)(param_1 + 0x3b8) = *(undefined4 *)(param_2 + 0x3b8);
  if ((*(byte *)(param_1 + 0x3c0) & 1) == 0) {
    *(undefined2 *)puVar1 = 0;
  }
  else {
    **(undefined1 **)(param_1 + 0x3d0) = 0;
    *(undefined8 *)(param_1 + 0x3c8) = 0;
  }
  string::reserve(unsigned long)(puVar1,0);
  *(undefined8 *)(param_1 + 0x3d0) = *(undefined8 *)(param_2 + 0x3d0);
  uVar3 = *(undefined8 *)(param_2 + 0x3c0);
  *(undefined8 *)(param_1 + 0x3c8) = *(undefined8 *)(param_2 + 0x3c8);
  *puVar1 = uVar3;
  *(undefined8 *)(param_2 + 0x3c8) = 0;
  *(undefined8 *)(param_2 + 0x3d0) = 0;
  *(undefined8 *)(param_2 + 0x3c0) = 0;
  puVar1 = (undefined8 *)(param_1 + 0x700);
  *(undefined8 *)(param_1 + 0x3e0) = *(undefined8 *)(param_2 + 0x3e0);
  *(undefined1 *)(param_1 + 1000) = *(undefined1 *)(param_2 + 1000);
  *(undefined4 *)(param_1 + 0x3f8) = *(undefined4 *)(param_2 + 0x3f8);
  *(undefined4 *)(param_1 + 0x400) = *(undefined4 *)(param_2 + 0x400);
  *(undefined8 *)(param_1 + 0x410) = *(undefined8 *)(param_2 + 0x410);
  *(undefined1 *)(param_1 + 0x418) = *(undefined1 *)(param_2 + 0x418);
  *(undefined4 *)(param_1 + 0x428) = *(undefined4 *)(param_2 + 0x428);
  *(undefined4 *)(param_1 + 0x430) = *(undefined4 *)(param_2 + 0x430);
  *(undefined8 *)(param_1 + 0x440) = *(undefined8 *)(param_2 + 0x440);
  *(undefined1 *)(param_1 + 0x448) = *(undefined1 *)(param_2 + 0x448);
  *(undefined4 *)(param_1 + 0x458) = *(undefined4 *)(param_2 + 0x458);
  *(undefined4 *)(param_1 + 0x460) = *(undefined4 *)(param_2 + 0x460);
  *(undefined8 *)(param_1 + 0x470) = *(undefined8 *)(param_2 + 0x470);
  *(undefined1 *)(param_1 + 0x478) = *(undefined1 *)(param_2 + 0x478);
  *(undefined4 *)(param_1 + 0x488) = *(undefined4 *)(param_2 + 0x488);
  *(undefined4 *)(param_1 + 0x490) = *(undefined4 *)(param_2 + 0x490);
  *(undefined8 *)(param_1 + 0x4a0) = *(undefined8 *)(param_2 + 0x4a0);
  *(undefined1 *)(param_1 + 0x4a8) = *(undefined1 *)(param_2 + 0x4a8);
  *(undefined4 *)(param_1 + 0x4b8) = *(undefined4 *)(param_2 + 0x4b8);
  *(undefined4 *)(param_1 + 0x4c0) = *(undefined4 *)(param_2 + 0x4c0);
  *(undefined8 *)(param_1 + 0x4d0) = *(undefined8 *)(param_2 + 0x4d0);
  *(undefined1 *)(param_1 + 0x4d8) = *(undefined1 *)(param_2 + 0x4d8);
  *(undefined4 *)(param_1 + 0x4e8) = *(undefined4 *)(param_2 + 0x4e8);
  *(undefined4 *)(param_1 + 0x4f0) = *(undefined4 *)(param_2 + 0x4f0);
  *(undefined8 *)(param_1 + 0x500) = *(undefined8 *)(param_2 + 0x500);
  *(undefined1 *)(param_1 + 0x508) = *(undefined1 *)(param_2 + 0x508);
  *(undefined4 *)(param_1 + 0x518) = *(undefined4 *)(param_2 + 0x518);
  *(undefined4 *)(param_1 + 0x520) = *(undefined4 *)(param_2 + 0x520);
  *(undefined8 *)(param_1 + 0x530) = *(undefined8 *)(param_2 + 0x530);
  *(undefined1 *)(param_1 + 0x538) = *(undefined1 *)(param_2 + 0x538);
  *(undefined4 *)(param_1 + 0x548) = *(undefined4 *)(param_2 + 0x548);
  *(undefined4 *)(param_1 + 0x550) = *(undefined4 *)(param_2 + 0x550);
  *(undefined8 *)(param_1 + 0x560) = *(undefined8 *)(param_2 + 0x560);
  *(undefined1 *)(param_1 + 0x568) = *(undefined1 *)(param_2 + 0x568);
  *(undefined4 *)(param_1 + 0x578) = *(undefined4 *)(param_2 + 0x578);
  *(undefined4 *)(param_1 + 0x580) = *(undefined4 *)(param_2 + 0x580);
  *(undefined8 *)(param_1 + 0x590) = *(undefined8 *)(param_2 + 0x590);
  *(undefined1 *)(param_1 + 0x598) = *(undefined1 *)(param_2 + 0x598);
  *(undefined4 *)(param_1 + 0x5a8) = *(undefined4 *)(param_2 + 0x5a8);
  *(undefined4 *)(param_1 + 0x5b0) = *(undefined4 *)(param_2 + 0x5b0);
  *(undefined8 *)(param_1 + 0x5c0) = *(undefined8 *)(param_2 + 0x5c0);
  *(undefined1 *)(param_1 + 0x5c8) = *(undefined1 *)(param_2 + 0x5c8);
  *(undefined4 *)(param_1 + 0x5d8) = *(undefined4 *)(param_2 + 0x5d8);
  *(undefined4 *)(param_1 + 0x5e0) = *(undefined4 *)(param_2 + 0x5e0);
  *(undefined8 *)(param_1 + 0x5f0) = *(undefined8 *)(param_2 + 0x5f0);
  *(undefined1 *)(param_1 + 0x5f8) = *(undefined1 *)(param_2 + 0x5f8);
  *(undefined4 *)(param_1 + 0x608) = *(undefined4 *)(param_2 + 0x608);
  *(undefined4 *)(param_1 + 0x610) = *(undefined4 *)(param_2 + 0x610);
  *(undefined8 *)(param_1 + 0x620) = *(undefined8 *)(param_2 + 0x620);
  *(undefined1 *)(param_1 + 0x628) = *(undefined1 *)(param_2 + 0x628);
  *(undefined4 *)(param_1 + 0x638) = *(undefined4 *)(param_2 + 0x638);
  *(undefined4 *)(param_1 + 0x640) = *(undefined4 *)(param_2 + 0x640);
  *(undefined8 *)(param_1 + 0x650) = *(undefined8 *)(param_2 + 0x650);
  *(undefined1 *)(param_1 + 0x658) = *(undefined1 *)(param_2 + 0x658);
  *(undefined4 *)(param_1 + 0x668) = *(undefined4 *)(param_2 + 0x668);
  *(undefined4 *)(param_1 + 0x670) = *(undefined4 *)(param_2 + 0x670);
  *(undefined8 *)(param_1 + 0x680) = *(undefined8 *)(param_2 + 0x680);
  *(undefined1 *)(param_1 + 0x688) = *(undefined1 *)(param_2 + 0x688);
  *(undefined4 *)(param_1 + 0x698) = *(undefined4 *)(param_2 + 0x698);
  *(undefined4 *)(param_1 + 0x6a0) = *(undefined4 *)(param_2 + 0x6a0);
  *(undefined8 *)(param_1 + 0x6b0) = *(undefined8 *)(param_2 + 0x6b0);
  *(undefined1 *)(param_1 + 0x6b8) = *(undefined1 *)(param_2 + 0x6b8);
  *(undefined4 *)(param_1 + 0x6c8) = *(undefined4 *)(param_2 + 0x6c8);
  *(undefined4 *)(param_1 + 0x6d0) = *(undefined4 *)(param_2 + 0x6d0);
  *(undefined8 *)(param_1 + 0x6e0) = *(undefined8 *)(param_2 + 0x6e0);
  *(undefined1 *)(param_1 + 0x6e8) = *(undefined1 *)(param_2 + 0x6e8);
  *(undefined4 *)(param_1 + 0x6f8) = *(undefined4 *)(param_2 + 0x6f8);
  if ((*(byte *)(param_1 + 0x700) & 1) == 0) {
    *(undefined2 *)puVar1 = 0;
  }
  else {
    **(undefined1 **)(param_1 + 0x710) = 0;
    *(undefined8 *)(param_1 + 0x708) = 0;
  }
  string::reserve(unsigned long)(puVar1,0);
  *(undefined8 *)(param_1 + 0x710) = *(undefined8 *)(param_2 + 0x710);
  uVar3 = *(undefined8 *)(param_2 + 0x700);
  *(undefined8 *)(param_1 + 0x708) = *(undefined8 *)(param_2 + 0x708);
  *puVar1 = uVar3;
  *(undefined8 *)(param_2 + 0x708) = 0;
  *(undefined8 *)(param_2 + 0x710) = 0;
  *(undefined8 *)(param_2 + 0x700) = 0;
  puVar1 = (undefined8 *)(param_1 + 0x830);
  *(undefined8 *)(param_1 + 0x720) = *(undefined8 *)(param_2 + 0x720);
  *(undefined1 *)(param_1 + 0x728) = *(undefined1 *)(param_2 + 0x728);
  *(undefined4 *)(param_1 + 0x738) = *(undefined4 *)(param_2 + 0x738);
  *(undefined4 *)(param_1 + 0x740) = *(undefined4 *)(param_2 + 0x740);
  *(undefined8 *)(param_1 + 0x750) = *(undefined8 *)(param_2 + 0x750);
  *(undefined1 *)(param_1 + 0x758) = *(undefined1 *)(param_2 + 0x758);
  *(undefined4 *)(param_1 + 0x768) = *(undefined4 *)(param_2 + 0x768);
  *(undefined4 *)(param_1 + 0x770) = *(undefined4 *)(param_2 + 0x770);
  *(undefined8 *)(param_1 + 0x780) = *(undefined8 *)(param_2 + 0x780);
  *(undefined1 *)(param_1 + 0x788) = *(undefined1 *)(param_2 + 0x788);
  *(undefined4 *)(param_1 + 0x798) = *(undefined4 *)(param_2 + 0x798);
  *(undefined4 *)(param_1 + 0x7a0) = *(undefined4 *)(param_2 + 0x7a0);
  *(undefined8 *)(param_1 + 0x7b0) = *(undefined8 *)(param_2 + 0x7b0);
  *(undefined1 *)(param_1 + 0x7b8) = *(undefined1 *)(param_2 + 0x7b8);
  *(undefined4 *)(param_1 + 0x7c8) = *(undefined4 *)(param_2 + 0x7c8);
  *(undefined4 *)(param_1 + 2000) = *(undefined4 *)(param_2 + 2000);
  *(undefined8 *)(param_1 + 0x7e0) = *(undefined8 *)(param_2 + 0x7e0);
  *(undefined1 *)(param_1 + 0x7e8) = *(undefined1 *)(param_2 + 0x7e8);
  *(undefined4 *)(param_1 + 0x7f8) = *(undefined4 *)(param_2 + 0x7f8);
  *(undefined4 *)(param_1 + 0x800) = *(undefined4 *)(param_2 + 0x800);
  *(undefined8 *)(param_1 + 0x810) = *(undefined8 *)(param_2 + 0x810);
  *(undefined1 *)(param_1 + 0x818) = *(undefined1 *)(param_2 + 0x818);
  *(undefined4 *)(param_1 + 0x828) = *(undefined4 *)(param_2 + 0x828);
  if ((*(byte *)(param_1 + 0x830) & 1) == 0) {
    *(undefined2 *)puVar1 = 0;
  }
  else {
    **(undefined1 **)(param_1 + 0x840) = 0;
    *(undefined8 *)(param_1 + 0x838) = 0;
  }
  string::reserve(unsigned long)(puVar1,0);
  *(undefined8 *)(param_1 + 0x840) = *(undefined8 *)(param_2 + 0x840);
  uVar3 = *(undefined8 *)(param_2 + 0x830);
  *(undefined8 *)(param_1 + 0x838) = *(undefined8 *)(param_2 + 0x838);
  *puVar1 = uVar3;
  *(undefined8 *)(param_2 + 0x838) = 0;
  *(undefined8 *)(param_2 + 0x840) = 0;
  *(undefined8 *)(param_2 + 0x830) = 0;
  *(undefined8 *)(param_1 + 0x850) = *(undefined8 *)(param_2 + 0x850);
  *(undefined1 *)(param_1 + 0x858) = *(undefined1 *)(param_2 + 0x858);
  *(undefined4 *)(param_1 + 0x868) = *(undefined4 *)(param_2 + 0x868);
  *(undefined4 *)(param_1 + 0x870) = *(undefined4 *)(param_2 + 0x870);
  *(undefined8 *)(param_1 + 0x880) = *(undefined8 *)(param_2 + 0x880);
  *(undefined1 *)(param_1 + 0x888) = *(undefined1 *)(param_2 + 0x888);
  *(undefined4 *)(param_1 + 0x898) = *(undefined4 *)(param_2 + 0x898);
  *(undefined4 *)(param_1 + 0x8a0) = *(undefined4 *)(param_2 + 0x8a0);
  *(undefined8 *)(param_1 + 0x8b0) = *(undefined8 *)(param_2 + 0x8b0);
  *(undefined1 *)(param_1 + 0x8b8) = *(undefined1 *)(param_2 + 0x8b8);
  *(undefined4 *)(param_1 + 0x8c8) = *(undefined4 *)(param_2 + 0x8c8);
  *(undefined4 *)(param_1 + 0x8d0) = *(undefined4 *)(param_2 + 0x8d0);
  *(undefined8 *)(param_1 + 0x8e0) = *(undefined8 *)(param_2 + 0x8e0);
  *(undefined1 *)(param_1 + 0x8e8) = *(undefined1 *)(param_2 + 0x8e8);
  *(undefined4 *)(param_1 + 0x8f8) = *(undefined4 *)(param_2 + 0x8f8);
  *(undefined4 *)(param_1 + 0x900) = *(undefined4 *)(param_2 + 0x900);
  *(undefined8 *)(param_1 + 0x910) = *(undefined8 *)(param_2 + 0x910);
  *(undefined1 *)(param_1 + 0x918) = *(undefined1 *)(param_2 + 0x918);
  *(undefined4 *)(param_1 + 0x928) = *(undefined4 *)(param_2 + 0x928);
  *(undefined4 *)(param_1 + 0x930) = *(undefined4 *)(param_2 + 0x930);
  *(undefined8 *)(param_1 + 0x940) = *(undefined8 *)(param_2 + 0x940);
  *(undefined1 *)(param_1 + 0x948) = *(undefined1 *)(param_2 + 0x948);
  *(undefined4 *)(param_1 + 0x958) = *(undefined4 *)(param_2 + 0x958);
  *(undefined4 *)(param_1 + 0x960) = *(undefined4 *)(param_2 + 0x960);
  *(undefined8 *)(param_1 + 0x970) = *(undefined8 *)(param_2 + 0x970);
  *(undefined1 *)(param_1 + 0x978) = *(undefined1 *)(param_2 + 0x978);
  *(undefined4 *)(param_1 + 0x988) = *(undefined4 *)(param_2 + 0x988);
  *(undefined4 *)(param_1 + 0x990) = *(undefined4 *)(param_2 + 0x990);
  *(undefined8 *)(param_1 + 0x9a0) = *(undefined8 *)(param_2 + 0x9a0);
  *(undefined1 *)(param_1 + 0x9a8) = *(undefined1 *)(param_2 + 0x9a8);
  *(undefined4 *)(param_1 + 0x9b8) = *(undefined4 *)(param_2 + 0x9b8);
  *(undefined4 *)(param_1 + 0x9c0) = *(undefined4 *)(param_2 + 0x9c0);
  *(undefined8 *)(param_1 + 0x9d0) = *(undefined8 *)(param_2 + 0x9d0);
  *(undefined1 *)(param_1 + 0x9d8) = *(undefined1 *)(param_2 + 0x9d8);
  *(undefined4 *)(param_1 + 0x9e8) = *(undefined4 *)(param_2 + 0x9e8);
  *(undefined4 *)(param_1 + 0x9f0) = *(undefined4 *)(param_2 + 0x9f0);
  *(undefined8 *)(param_1 + 0xa00) = *(undefined8 *)(param_2 + 0xa00);
  *(undefined1 *)(param_1 + 0xa08) = *(undefined1 *)(param_2 + 0xa08);
  *(undefined4 *)(param_1 + 0xa18) = *(undefined4 *)(param_2 + 0xa18);
  *(undefined4 *)(param_1 + 0xa20) = *(undefined4 *)(param_2 + 0xa20);
  *(undefined8 *)(param_1 + 0xa30) = *(undefined8 *)(param_2 + 0xa30);
  *(undefined1 *)(param_1 + 0xa38) = *(undefined1 *)(param_2 + 0xa38);
  *(undefined4 *)(param_1 + 0xa48) = *(undefined4 *)(param_2 + 0xa48);
  *(undefined4 *)(param_1 + 0xa50) = *(undefined4 *)(param_2 + 0xa50);
  *(undefined8 *)(param_1 + 0xa60) = *(undefined8 *)(param_2 + 0xa60);
  *(undefined1 *)(param_1 + 0xa68) = *(undefined1 *)(param_2 + 0xa68);
  *(undefined4 *)(param_1 + 0xa78) = *(undefined4 *)(param_2 + 0xa78);
  *(undefined1 *)(param_1 + 0xa80) = *(undefined1 *)(param_2 + 0xa80);
  *(undefined8 *)(param_1 + 0xa90) = *(undefined8 *)(param_2 + 0xa90);
  *(undefined1 *)(param_1 + 0xa98) = *(undefined1 *)(param_2 + 0xa98);
  *(undefined4 *)(param_1 + 0xaa8) = *(undefined4 *)(param_2 + 0xaa8);
  *(undefined1 *)(param_1 + 0xab0) = *(undefined1 *)(param_2 + 0xab0);
  *(undefined8 *)(param_1 + 0xac0) = *(undefined8 *)(param_2 + 0xac0);
  *(undefined1 *)(param_1 + 0xac8) = *(undefined1 *)(param_2 + 0xac8);
  *(undefined4 *)(param_1 + 0xad8) = *(undefined4 *)(param_2 + 0xad8);
  *(undefined4 *)(param_1 + 0xae0) = *(undefined4 *)(param_2 + 0xae0);
  *(undefined8 *)(param_1 + 0xaf0) = *(undefined8 *)(param_2 + 0xaf0);
  *(undefined1 *)(param_1 + 0xaf8) = *(undefined1 *)(param_2 + 0xaf8);
  *(undefined4 *)(param_1 + 0xb08) = *(undefined4 *)(param_2 + 0xb08);
  *(undefined4 *)(param_1 + 0xb10) = *(undefined4 *)(param_2 + 0xb10);
  *(undefined8 *)(param_1 + 0xb20) = *(undefined8 *)(param_2 + 0xb20);
  *(undefined1 *)(param_1 + 0xb28) = *(undefined1 *)(param_2 + 0xb28);
  *(undefined4 *)(param_1 + 0xb38) = *(undefined4 *)(param_2 + 0xb38);
  *(undefined4 *)(param_1 + 0xb40) = *(undefined4 *)(param_2 + 0xb40);
  *(undefined8 *)(param_1 + 0xb50) = *(undefined8 *)(param_2 + 0xb50);
  *(undefined1 *)(param_1 + 0xb58) = *(undefined1 *)(param_2 + 0xb58);
  *(undefined4 *)(param_1 + 0xb68) = *(undefined4 *)(param_2 + 0xb68);
  *(undefined4 *)(param_1 + 0xb70) = *(undefined4 *)(param_2 + 0xb70);
  *(undefined8 *)(param_1 + 0xb80) = *(undefined8 *)(param_2 + 0xb80);
  *(undefined1 *)(param_1 + 0xb88) = *(undefined1 *)(param_2 + 0xb88);
  *(undefined4 *)(param_1 + 0xb98) = *(undefined4 *)(param_2 + 0xb98);
  *(undefined4 *)(param_1 + 0xba0) = *(undefined4 *)(param_2 + 0xba0);
  *(undefined8 *)(param_1 + 0xbb0) = *(undefined8 *)(param_2 + 0xbb0);
  *(undefined1 *)(param_1 + 3000) = *(undefined1 *)(param_2 + 3000);
  *(undefined4 *)(param_1 + 0xbc8) = *(undefined4 *)(param_2 + 0xbc8);
  *(undefined4 *)(param_1 + 0xbd0) = *(undefined4 *)(param_2 + 0xbd0);
  *(undefined8 *)(param_1 + 0xbe0) = *(undefined8 *)(param_2 + 0xbe0);
  *(undefined1 *)(param_1 + 0xbe8) = *(undefined1 *)(param_2 + 0xbe8);
  *(undefined4 *)(param_1 + 0xbf8) = *(undefined4 *)(param_2 + 0xbf8);
  *(undefined4 *)(param_1 + 0xc00) = *(undefined4 *)(param_2 + 0xc00);
  *(undefined8 *)(param_1 + 0xc10) = *(undefined8 *)(param_2 + 0xc10);
  *(undefined1 *)(param_1 + 0xc18) = *(undefined1 *)(param_2 + 0xc18);
  *(undefined4 *)(param_1 + 0xc28) = *(undefined4 *)(param_2 + 0xc28);
  *(undefined4 *)(param_1 + 0xc30) = *(undefined4 *)(param_2 + 0xc30);
  *(undefined8 *)(param_1 + 0xc40) = *(undefined8 *)(param_2 + 0xc40);
  *(undefined1 *)(param_1 + 0xc48) = *(undefined1 *)(param_2 + 0xc48);
  *(undefined4 *)(param_1 + 0xc58) = *(undefined4 *)(param_2 + 0xc58);
  *(undefined4 *)(param_1 + 0xc60) = *(undefined4 *)(param_2 + 0xc60);
  *(undefined8 *)(param_1 + 0xc70) = *(undefined8 *)(param_2 + 0xc70);
  *(undefined1 *)(param_1 + 0xc78) = *(undefined1 *)(param_2 + 0xc78);
  *(undefined4 *)(param_1 + 0xc88) = *(undefined4 *)(param_2 + 0xc88);
  *(undefined4 *)(param_1 + 0xc90) = *(undefined4 *)(param_2 + 0xc90);
  *(undefined8 *)(param_1 + 0xca0) = *(undefined8 *)(param_2 + 0xca0);
  *(undefined1 *)(param_1 + 0xca8) = *(undefined1 *)(param_2 + 0xca8);
  *(undefined4 *)(param_1 + 0xcb8) = *(undefined4 *)(param_2 + 0xcb8);
  *(undefined4 *)(param_1 + 0xcc0) = *(undefined4 *)(param_2 + 0xcc0);
  *(undefined8 *)(param_1 + 0xcd0) = *(undefined8 *)(param_2 + 0xcd0);
  *(undefined1 *)(param_1 + 0xcd8) = *(undefined1 *)(param_2 + 0xcd8);
  *(undefined4 *)(param_1 + 0xce8) = *(undefined4 *)(param_2 + 0xce8);
  *(undefined4 *)(param_1 + 0xcf0) = *(undefined4 *)(param_2 + 0xcf0);
  *(undefined8 *)(param_1 + 0xd00) = *(undefined8 *)(param_2 + 0xd00);
  *(undefined1 *)(param_1 + 0xd08) = *(undefined1 *)(param_2 + 0xd08);
  *(undefined4 *)(param_1 + 0xd18) = *(undefined4 *)(param_2 + 0xd18);
  *(undefined1 *)(param_1 + 0xd20) = *(undefined1 *)(param_2 + 0xd20);
  *(undefined8 *)(param_1 + 0xd30) = *(undefined8 *)(param_2 + 0xd30);
  *(undefined1 *)(param_1 + 0xd38) = *(undefined1 *)(param_2 + 0xd38);
  *(undefined4 *)(param_1 + 0xd48) = *(undefined4 *)(param_2 + 0xd48);
  *(undefined4 *)(param_1 + 0xd50) = *(undefined4 *)(param_2 + 0xd50);
  *(undefined8 *)(param_1 + 0xd60) = *(undefined8 *)(param_2 + 0xd60);
  *(undefined1 *)(param_1 + 0xd68) = *(undefined1 *)(param_2 + 0xd68);
  *(undefined4 *)(param_1 + 0xd78) = *(undefined4 *)(param_2 + 0xd78);
  *(undefined4 *)(param_1 + 0xd80) = *(undefined4 *)(param_2 + 0xd80);
  *(undefined8 *)(param_1 + 0xd90) = *(undefined8 *)(param_2 + 0xd90);
  *(undefined1 *)(param_1 + 0xd98) = *(undefined1 *)(param_2 + 0xd98);
  *(undefined4 *)(param_1 + 0xda8) = *(undefined4 *)(param_2 + 0xda8);
  *(undefined4 *)(param_1 + 0xdb0) = *(undefined4 *)(param_2 + 0xdb0);
  *(undefined8 *)(param_1 + 0xdc0) = *(undefined8 *)(param_2 + 0xdc0);
  *(undefined1 *)(param_1 + 0xdc8) = *(undefined1 *)(param_2 + 0xdc8);
  *(undefined4 *)(param_1 + 0xdd8) = *(undefined4 *)(param_2 + 0xdd8);
  *(undefined4 *)(param_1 + 0xde0) = *(undefined4 *)(param_2 + 0xde0);
  *(undefined8 *)(param_1 + 0xdf0) = *(undefined8 *)(param_2 + 0xdf0);
  *(undefined1 *)(param_1 + 0xdf8) = *(undefined1 *)(param_2 + 0xdf8);
  *(undefined4 *)(param_1 + 0xe08) = *(undefined4 *)(param_2 + 0xe08);
  *(undefined4 *)(param_1 + 0xe10) = *(undefined4 *)(param_2 + 0xe10);
  *(undefined8 *)(param_1 + 0xe20) = *(undefined8 *)(param_2 + 0xe20);
  *(undefined1 *)(param_1 + 0xe28) = *(undefined1 *)(param_2 + 0xe28);
  *(undefined4 *)(param_1 + 0xe38) = *(undefined4 *)(param_2 + 0xe38);
  *(undefined4 *)(param_1 + 0xe40) = *(undefined4 *)(param_2 + 0xe40);
  if (param_1 != param_2) {
    void std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::__assign_multi<std::__ndk1::__tree_const_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long> >(std::__ndk1::__tree_const_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>, std::__ndk1::__tree_const_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>)(param_1 + 0xe50,*(undefined8 *)(param_2 + 0xe50),param_2 + 0xe58);
    void std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::__assign_multi<std::__ndk1::__tree_const_iterator<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*, long> >(std::__ndk1::__tree_const_iterator<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*, long>, std::__ndk1::__tree_const_iterator<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*, long>)(param_1 + 0xe68,*(undefined8 *)(param_2 + 0xe68),param_2 + 0xe70);
  }
  *(undefined8 *)(param_1 + 0xe88) = *(undefined8 *)(param_2 + 0xe88);
  *(undefined1 *)(param_1 + 0xe90) = *(undefined1 *)(param_2 + 0xe90);
  *(undefined4 *)(param_1 + 0xea0) = *(undefined4 *)(param_2 + 0xea0);
  *(undefined4 *)(param_1 + 0xea8) = *(undefined4 *)(param_2 + 0xea8);
  *(undefined8 *)(param_1 + 0xeb8) = *(undefined8 *)(param_2 + 0xeb8);
  *(undefined1 *)(param_1 + 0xec0) = *(undefined1 *)(param_2 + 0xec0);
  *(undefined4 *)(param_1 + 0xed0) = *(undefined4 *)(param_2 + 0xed0);
  *(undefined4 *)(param_1 + 0xed8) = *(undefined4 *)(param_2 + 0xed8);
  *(undefined8 *)(param_1 + 0xee8) = *(undefined8 *)(param_2 + 0xee8);
  *(undefined1 *)(param_1 + 0xef0) = *(undefined1 *)(param_2 + 0xef0);
  *(undefined4 *)(param_1 + 0xf00) = *(undefined4 *)(param_2 + 0xf00);
  *(undefined4 *)(param_1 + 0xf08) = *(undefined4 *)(param_2 + 0xf08);
  if (param_1 == param_2) {
    UniverseAddStatusInfo::operator=(UniverseAddStatusInfo&&)(param_1 + 0x1000,param_2 + 0x1000);
    UniverseDeityBoostInfo::operator=(UniverseDeityBoostInfo&&)(param_1 + 0x11e8,param_2 + 0x11e8);
  }
  else {
    void std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::__assign_multi<std::__ndk1::__tree_const_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long> >(std::__ndk1::__tree_const_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>, std::__ndk1::__tree_const_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>)(param_1 + 0xf18,*(undefined8 *)(param_2 + 0xf18),param_2 + 0xf20);
    void std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::__assign_multi<std::__ndk1::__tree_const_iterator<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*, long> >(std::__ndk1::__tree_const_iterator<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*, long>, std::__ndk1::__tree_const_iterator<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*, long>)(param_1 + 0xf30,*(undefined8 *)(param_2 + 0xf30),param_2 + 0xf38);
    void std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, CFactorInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, CFactorInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, CFactorInfo>, Framework::CSTLMapAllocatorInf> >::__assign_multi<std::__ndk1::__tree_const_iterator<std::__ndk1::__value_type<unsigned long, CFactorInfo>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CFactorInfo>, void*>*, long> >(std::__ndk1::__tree_const_iterator<std::__ndk1::__value_type<unsigned long, CFactorInfo>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CFactorInfo>, void*>*, long>, std::__ndk1::__tree_const_iterator<std::__ndk1::__value_type<unsigned long, CFactorInfo>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, CFactorInfo>, void*>*, long>)(param_1 + 0xf48,*(undefined8 *)(param_2 + 0xf48),param_2 + 0xf50);
    void std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::__assign_multi<std::__ndk1::__tree_const_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long> >(std::__ndk1::__tree_const_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>, std::__ndk1::__tree_const_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>)(param_1 + 0xf68,*(undefined8 *)(param_2 + 0xf68),param_2 + 0xf70);
    void std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::__assign_multi<std::__ndk1::__tree_const_iterator<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*, long> >(std::__ndk1::__tree_const_iterator<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*, long>, std::__ndk1::__tree_const_iterator<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*, long>)(param_1 + 0xf80,*(undefined8 *)(param_2 + 0xf80),param_2 + 0xf88);
    std::__ndk1::enable_if<__is_forward_iterator<CCharacterDecoObjectInfo*>::value&&is_constructible<CCharacterDecoObjectInfo, std::__ndk1::iterator_traits<CCharacterDecoObjectInfo*>::reference>::value, void>::type std::__ndk1::vector<CCharacterDecoObjectInfo, Framework::CSTLAllocator<CCharacterDecoObjectInfo, Framework::CSTLVectorAllocatorInf> >::assign<CCharacterDecoObjectInfo*>(CCharacterDecoObjectInfo*, CCharacterDecoObjectInfo*)(param_1 + 0xf98,*(undefined8 *)(param_2 + 0xf98),*(undefined8 *)(param_2 + 4000)
                   );
    void std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::__assign_multi<std::__ndk1::__tree_const_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long> >(std::__ndk1::__tree_const_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>, std::__ndk1::__tree_const_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>)(param_1 + 0xfb8,*(undefined8 *)(param_2 + 0xfb8),param_2 + 0xfc0);
    void std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::__assign_multi<std::__ndk1::__tree_const_iterator<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*, long> >(std::__ndk1::__tree_const_iterator<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*, long>, std::__ndk1::__tree_const_iterator<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*, long>)(param_1 + 0xfd0,*(undefined8 *)(param_2 + 0xfd0),param_2 + 0xfd8);
    std::__ndk1::enable_if<__is_forward_iterator<CParameterPropertyValue<unsigned int, 131u, CPropertyConverter>*>::value&&is_constructible<CParameterPropertyValue<unsigned int, 131u, CPropertyConverter>, std::__ndk1::iterator_traits<CParameterPropertyValue<unsigned int, 131u, CPropertyConverter>*>::reference>::value, void>::type std::__ndk1::vector<CParameterPropertyValue<unsigned int, 131u, CPropertyConverter>, Framework::CSTLAllocator<CParameterPropertyValue<unsigned int, 131u, CPropertyConverter>, Framework::CSTLVectorAllocatorInf> >::assign<CParameterPropertyValue<unsigned int, 131u, CPropertyConverter>*>(CParameterPropertyValue<unsigned int, 131u, CPropertyConverter>*, CParameterPropertyValue<unsigned int, 131u, CPropertyConverter>*)(param_1 + 0xfe8,*(undefined8 *)(param_2 + 0xfe8),
                    *(undefined8 *)(param_2 + 0xff0));
    UniverseAddStatusInfo::operator=(UniverseAddStatusInfo&&)(param_1 + 0x1000,param_2 + 0x1000);
    UniverseDeityBoostInfo::operator=(UniverseDeityBoostInfo&&)(param_1 + 0x11e8,param_2 + 0x11e8);
    void std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::__assign_multi<std::__ndk1::__tree_const_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long> >(std::__ndk1::__tree_const_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>, std::__ndk1::__tree_const_iterator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*, long>)(param_1 + 0x13d8,*(undefined8 *)(param_2 + 0x13d8),param_2 + 0x13e0);
    void std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::__assign_multi<std::__ndk1::__tree_const_iterator<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*, long> >(std::__ndk1::__tree_const_iterator<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*, long>, std::__ndk1::__tree_const_iterator<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*, long>)(param_1 + 0x13f0,*(undefined8 *)(param_2 + 0x13f0),param_2 + 0x13f8);
  }
  *(undefined8 *)(param_1 + 0x1410) = *(undefined8 *)(param_2 + 0x1410);
  *(undefined1 *)(param_1 + 0x1418) = *(undefined1 *)(param_2 + 0x1418);
  *(undefined4 *)(param_1 + 0x1428) = *(undefined4 *)(param_2 + 0x1428);
  *(undefined4 *)(param_1 + 0x1430) = *(undefined4 *)(param_2 + 0x1430);
  *(undefined8 *)(param_1 + 0x1440) = *(undefined8 *)(param_2 + 0x1440);
  *(undefined1 *)(param_1 + 0x1448) = *(undefined1 *)(param_2 + 0x1448);
  *(undefined4 *)(param_1 + 0x1458) = *(undefined4 *)(param_2 + 0x1458);
  *(undefined4 *)(param_1 + 0x1460) = *(undefined4 *)(param_2 + 0x1460);
  *(undefined8 *)(param_1 + 0x1470) = *(undefined8 *)(param_2 + 0x1470);
  *(undefined1 *)(param_1 + 0x1478) = *(undefined1 *)(param_2 + 0x1478);
  *(undefined4 *)(param_1 + 0x1488) = *(undefined4 *)(param_2 + 0x1488);
  *(undefined4 *)(param_1 + 0x1490) = *(undefined4 *)(param_2 + 0x1490);
  UniverseDeityBoostInfo::operator=(UniverseDeityBoostInfo&&)(param_1 + 0x1498,param_2 + 0x1498);
  uVar3 = *(undefined8 *)(param_2 + 0x1680);
  *(undefined8 *)(param_1 + 0x1688) = *(undefined8 *)(param_2 + 0x1688);
  *(undefined8 *)(param_1 + 0x1680) = uVar3;
  return param_1;
}


// FAILED to create function at 02ab3948 CPersonStatusInfo::vtable
// FAILED to create function at 02ab3990 CPersonStatusInfo::typeinfo
