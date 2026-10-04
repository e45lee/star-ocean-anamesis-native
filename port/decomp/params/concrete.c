// port/decomp/params/concrete.c: Ghidra decompiles for the params subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-04 06:14 UTC: tools/decomp.sh '--into' 'params/concrete' 'CParameterPlayer(Element)?::' 'CParameterCocosCommonResource(Element)?::'

// ==== CParameterCocosCommonResourceElement::CParameterCocosCommonResourceElement()
// vaddr 0x16e84c8 | ghidra 0x17e84c8 | size 192 | symbol _ZN36CParameterCocosCommonResourceElementC2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN36CParameterCocosCommonResourceElementC1Ev(long *param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  
  CParameterElementBase::CParameterElementBase()();
  puVar2 = PTR__ZTV22CParameterPropertyBaseILj30EE_02cbe830;
  puVar1 = PTR__ZTV36CParameterCocosCommonResourceElement_02cbb848;
  *(undefined1 *)(param_1 + 4) = 0;
  *param_1 = (long)(puVar1 + 0x10);
  param_1[2] = (long)(puVar2 + 0x10);
  param_1[3] = 0;
  Framework::CHash32::CHash32()(param_1 + 5);
  puVar1 = 
  PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj30EE_02cbb158
  ;
  param_1[7] = 0;
  param_1[8] = 0;
  param_1[0xb] = 0;
  puVar2 = PTR__ZTV22CParameterPropertyBaseILj31EE_02cc17e0;
  *(undefined1 *)(param_1 + 0xc) = 0;
  param_1[2] = (long)(puVar1 + 0x10);
  param_1[9] = 0;
  param_1[10] = (long)(puVar2 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0xd);
  puVar1 = 
  PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj31EE_02cba990
  ;
  param_1[0xf] = 0;
  param_1[0x10] = 0;
  param_1[0x13] = 0;
  puVar2 = PTR__ZTV22CParameterPropertyBaseILj32EE_02cc0fa8;
  *(undefined1 *)(param_1 + 0x14) = 0;
  param_1[10] = (long)(puVar1 + 0x10);
  param_1[0x11] = 0;
  param_1[0x12] = (long)(puVar2 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0x15);
  puVar1 = 
  PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj32EE_02cc31e8
  ;
  param_1[0x18] = 0;
  param_1[0x19] = 0;
  param_1[0x17] = 0;
  param_1[0x12] = (long)(puVar1 + 0x10);
  return;
}

// ==== CParameterCocosCommonResourceElement::~CParameterCocosCommonResourceElement()
// vaddr 0x16e8588 | ghidra 0x17e8588 | size 196 | symbol _ZN36CParameterCocosCommonResourceElementD2Ev | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Possible PIC construction at 0x017e85d4: Changing call to branch */
/* WARNING: Possible PIC construction at 0x017e860c: Changing call to branch */
/* WARNING: Removing unreachable block (ram,0x017e85d8) */
/* WARNING: Removing unreachable block (ram,0x017e85f0) */
/* WARNING: Removing unreachable block (ram,0x017e85f8) */
/* WARNING: Removing unreachable block (ram,0x017e8610) */
/* WARNING: Removing unreachable block (ram,0x017e8628) */
/* WARNING: Removing unreachable block (ram,0x017e8630) */

void _ZN36CParameterCocosCommonResourceElementD1Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTV36CParameterCocosCommonResourceElement_02cbb848 + 0x10);
  param_1[0x12] =
       (long)(
             PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj32EE_02cc31e8
             + 0x10);
  if ((*(byte *)(param_1 + 0x17) & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(param_1[0x19]);
  }
  param_1[0x12] = (long)(PTR__ZTV22CParameterPropertyBaseILj32EE_02cc0fa8 + 0x10);
  (*(code *)PTR__ZN9Framework7CHash32D1Ev_02cb3740)(param_1 + 0x15);
  return;
}

// ==== CParameterCocosCommonResourceElement::~CParameterCocosCommonResourceElement()
// vaddr 0x16e864c | ghidra 0x17e864c | size 24 | symbol _ZN36CParameterCocosCommonResourceElementD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN36CParameterCocosCommonResourceElementD0Ev(undefined8 param_1)

{
  CParameterCocosCommonResourceElement::~CParameterCocosCommonResourceElement()();
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== CParameterCocosCommonResourceElement::Initialize()
// vaddr 0x16e8664 | ghidra 0x17e8664 | size 316 | symbol _ZN36CParameterCocosCommonResourceElement10InitializeEv | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN36CParameterCocosCommonResourceElement10InitializeEv(long param_1)

{
  byte bStack_38;
  undefined7 uStack_37;
  undefined1 uStack_30;
  undefined2 uStack_2f;
  undefined1 uStack_2d;
  undefined4 uStack_2c;
  undefined1 uStack_28;
  undefined4 uStack_27;
  undefined3 uStack_23;
  
  uStack_23 = 0;
  bStack_38 = 0x26;
  uStack_2f = (undefined2)_UNK_0285e440;
  uStack_2d = (undefined1)((ulong)_UNK_0285e440 >> 0x10);
  uStack_2c = (undefined4)((ulong)_UNK_0285e440 >> 0x18);
  uStack_28 = (undefined1)((ulong)_UNK_0285e440 >> 0x38);
  uStack_37 = (undefined7)_UNK_0285e438;
  uStack_30 = (undefined1)((ulong)_UNK_0285e438 >> 0x38);
  uStack_27 = 0x797469;
  Framework::CHash32::operator=(char const*)(param_1 + 0x28,(ulong)&bStack_38 | 1);
  *(undefined1 *)(param_1 + 0x20) = 1;
  if ((bStack_38 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(CONCAT35(uStack_23,CONCAT41(uStack_27,uStack_28)));
  }
  CParameterElementBase::AddProperty(IParameterProperty*)(param_1,param_1 + 0x10);
  uStack_27 = 0;
  uStack_23 = 0;
  bStack_38 = 0x1e;
  uStack_37 = _UNK_0285e44c;
  uStack_30 = UNK_0285e453;
  uStack_2f = (undefined2)_UNK_0285e454;
  uStack_2d = (undefined1)((uint7)_UNK_0285e454 >> 0x10);
  uStack_2c = (undefined4)((uint7)_UNK_0285e454 >> 0x18);
  uStack_28 = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x68,(ulong)&bStack_38 | 1);
  *(undefined1 *)(param_1 + 0x60) = 1;
  if ((bStack_38 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(CONCAT35(uStack_23,CONCAT41(uStack_27,uStack_28)));
  }
  CParameterElementBase::AddProperty(IParameterProperty*)(param_1,param_1 + 0x50);
  uStack_2c = 0;
  uStack_28 = 0;
  uStack_27 = 0;
  uStack_23 = 0;
  bStack_38 = 0x14;
  uStack_37 = (undefined7)_UNK_0285e45c;
  uStack_30 = (undefined1)((ulong)_UNK_0285e45c >> 0x38);
  uStack_2f = 0x656d;
  uStack_2d = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0xa8,(ulong)&bStack_38 | 1);
  *(undefined1 *)(param_1 + 0xa0) = 1;
  if ((bStack_38 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(CONCAT35(uStack_23,CONCAT41(uStack_27,uStack_28)));
  }
  CParameterElementBase::AddProperty(IParameterProperty*)(param_1,param_1 + 0x90);
  return;
}

// ==== CParameterCocosCommonResource::CParameterCocosCommonResource()
// vaddr 0x16e87a0 | ghidra 0x17e87a0 | size 52 | symbol _ZN29CParameterCocosCommonResourceC2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN29CParameterCocosCommonResourceC1Ev(long *param_1)

{
  undefined *puVar1;
  
  CParameterBase::CParameterBase()();
  puVar1 = PTR__ZTV29CParameterCocosCommonResource_02cbe298;
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  *param_1 = (long)(puVar1 + 0x10);
  *(undefined4 *)(param_1 + 5) = 0x3f800000;
  return;
}

// ==== CParameterCocosCommonResource::~CParameterCocosCommonResource()
// vaddr 0x16e87d4 | ghidra 0x17e87d4 | size 216 | symbol _ZN29CParameterCocosCommonResourceD1Ev | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Possible PIC construction at 0x017e8818: Changing call to branch */
/* WARNING: Possible PIC construction at 0x017e8874: Changing call to branch */

void _ZN29CParameterCocosCommonResourceD2Ev(long *param_1)

{
  long *plVar1;
  long lVar2;
  long lVar3;
  
  *param_1 = (long)(PTR__ZTV29CParameterCocosCommonResource_02cbe298 + 0x10);
  if (param_1[4] != 0) {
    plVar1 = (long *)param_1[3];
    while (plVar1 != (long *)0x0) {
      lVar3 = *plVar1;
      CParameterCocosCommonResourceElement::~CParameterCocosCommonResourceElement()(plVar1 + 5);
      if ((*(byte *)(plVar1 + 2) & 1) != 0) {
        lVar3 = plVar1[4];
        goto code_r0x011d23a0;
      }
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar1);
      plVar1 = (long *)lVar3;
    }
    lVar3 = param_1[2];
    param_1[3] = 0;
    if (lVar3 != 0) {
      lVar2 = 0;
      do {
        *(undefined8 *)(param_1[1] + lVar2 * 8) = 0;
        lVar2 = lVar2 + 1;
      } while (lVar3 != lVar2);
    }
    param_1[4] = 0;
  }
  plVar1 = (long *)param_1[3];
  do {
    if (plVar1 == (long *)0x0) {
      lVar3 = param_1[1];
      param_1[1] = 0;
      if (lVar3 == 0) {
        return;
      }
code_r0x011d23a0:
      (*(code *)PTR__ZN9Framework37CAssignedMemoryManagerForSTLAllocator4FreeEPv_02ca11c0)(lVar3);
      return;
    }
    lVar3 = *plVar1;
    CParameterCocosCommonResourceElement::~CParameterCocosCommonResourceElement()(plVar1 + 5);
    if ((*(byte *)(plVar1 + 2) & 1) != 0) {
      lVar3 = plVar1[4];
      goto code_r0x011d23a0;
    }
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar1);
    plVar1 = (long *)lVar3;
  } while( true );
}

// ==== CParameterCocosCommonResource::Release()
// vaddr 0x16e88ac | ghidra 0x17e88ac | size 124 | symbol _ZN29CParameterCocosCommonResource7ReleaseEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN29CParameterCocosCommonResource7ReleaseEv(long param_1)

{
  long *plVar1;
  long lVar2;
  long lVar3;
  
  if (*(long *)(param_1 + 0x20) != 0) {
    plVar1 = (long *)*(long *)(param_1 + 0x18);
    while (plVar1 != (long *)0x0) {
      lVar3 = *plVar1;
      CParameterCocosCommonResourceElement::~CParameterCocosCommonResourceElement()(plVar1 + 5);
      if ((*(byte *)(plVar1 + 2) & 1) != 0) {
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar1[4]);
      }
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar1);
      plVar1 = (long *)lVar3;
    }
    lVar3 = *(long *)(param_1 + 0x10);
    *(undefined8 *)(param_1 + 0x18) = 0;
    if (lVar3 != 0) {
      lVar2 = 0;
      do {
        *(undefined8 *)(*(long *)(param_1 + 8) + lVar2 * 8) = 0;
        lVar2 = lVar2 + 1;
      } while (lVar3 != lVar2);
    }
    *(undefined8 *)(param_1 + 0x20) = 0;
  }
  return;
}

// ==== CParameterCocosCommonResource::~CParameterCocosCommonResource()
// vaddr 0x16e8928 | ghidra 0x17e8928 | size 24 | symbol _ZN29CParameterCocosCommonResourceD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN29CParameterCocosCommonResourceD0Ev(undefined8 param_1)

{
  CParameterCocosCommonResource::~CParameterCocosCommonResource()();
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== CParameterCocosCommonResource::pParseName() const
// vaddr 0x16e8940 | ghidra 0x17e8940 | size 12 | symbol _ZNK29CParameterCocosCommonResource10pParseNameEv | lib libSOA-3.7.0.so | 2026-10-04
undefined * _ZNK29CParameterCocosCommonResource10pParseNameEv(void)

{
  return &UNK_0285e467/*"CocosCommonResource"*/;
}

// ==== CParameterCocosCommonResource::rParameter() const
// vaddr 0x16e894c | ghidra 0x17e894c | size 8 | symbol _ZNK29CParameterCocosCommonResource10rParameterEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK29CParameterCocosCommonResource10rParameterEv(long param_1)

{
  return param_1 + 8;
}

// ==== CParameterCocosCommonResource::Deserialize(Aska::ASON::AValue::AMap const*)
// vaddr 0x16e8954 | ghidra 0x17e8954 | size 96 | symbol _ZN29CParameterCocosCommonResource11DeserializeEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-04
bool _ZN29CParameterCocosCommonResource11DeserializeEPKN4Aska4ASON6AValue4AMapE
               (long *param_1,long param_2)

{
  long lVar1;
  
  if (param_2 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0285e47b/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\ParameterCocosCommonResource.cpp"*/,0x43,&UNK_027dc58a/*"apParser is null."*/);
  }
  lVar1 = (**(code **)(*param_1 + 0x30))(param_1,param_2);
  if (lVar1 != 0) {
    CParameterCocosCommonResource::DeserializeParameter(Framework::CSTLUnorderedMap<string, CParameterCocosCommonResourceElement, std::__ndk1::hash<string >, std::__ndk1::equal_to<string > >&, Aska::ASON::AValue::AArray const*)(lVar1,param_1 + 1,lVar1 + 8);
  }
  return lVar1 != 0;
}

// ==== CParameterCocosCommonResource::DeserializeParameter(Framework::CSTLUnorderedMap<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> >, CParameterCocosCommonResourceElement, std::__ndk1::hash<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > >, std::__ndk1::equal_to<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > > >&, Aska::ASON::AValue::AArray const*)
// vaddr 0x16e89b4 | ghidra 0x17e89b4 | size 864 | symbol _ZN29CParameterCocosCommonResource20DeserializeParameterERN9Framework16CSTLUnorderedMapINSt6__ndk112basic_stringIcNS2_11char_traitsIcEENS0_13CSTLAllocatorIcNS0_22CSTLStringAllocatorInfEEEEE36CParameterCocosCommonResourceElementNS2_4hashIS9_EENS2_8equal_toIS9_EEEEPKN4Aska4ASON6AValue6AArrayE | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN29CParameterCocosCommonResource20DeserializeParameterERN9Framework16CSTLUnorderedMapINSt6__ndk112basic_stringIcNS2_11char_traitsIcEENS0_13CSTLAllocatorIcNS0_22CSTLStringAllocatorInfEEEEE36CParameterCocosCommonResourceElementNS2_4hashIS9_EENS2_8equal_toIS9_EEEEPKN4Aska4ASON6AValue6AArrayE
          (undefined8 param_1,undefined8 param_2,long *param_3)

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
  ulong uVar11;
  undefined *puVar12;
  long lVar13;
  ulong uVar14;
  ulong uVar15;
  long *plVar16;
  undefined1 auVar17 [16];
  undefined *puStack_158;
  ulong uStack_150;
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
  undefined1 auStack_88 [16];
  long alStack_78 [2];
  char cStack_68;
  
  if (param_3 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0285e47b/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\ParameterCocosCommonResource.cpp"*/,0x53,&UNK_02845e17/*"apArray is null."*/);
    iVar10 = iRam0000000000000008;
  }
  else {
    iVar10 = (int)param_3[1];
  }
  if (iVar10 != 0) {
    puVar2 = PTR__ZTV36CParameterCocosCommonResourceElement_02cbb848 + 0x10;
    puVar3 = PTR__ZTV22CParameterPropertyBaseILj30EE_02cbe830 + 0x10;
    puVar4 = PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj30EE_02cbb158
             + 0x10;
    puVar5 = PTR__ZTV22CParameterPropertyBaseILj31EE_02cc17e0 + 0x10;
    puVar6 = PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj31EE_02cba990
             + 0x10;
    puVar7 = PTR__ZTV22CParameterPropertyBaseILj32EE_02cc0fa8 + 0x10;
    uVar14 = 0;
    puVar8 = PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj32EE_02cc31e8
             + 0x10;
    do {
      lVar9 = *param_3 + uVar14 * 0x20;
      if (lVar9 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0285e47b/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\ParameterCocosCommonResource.cpp"*/,0x56,&UNK_0285e8d7/*"pValue is null."*/);
      }
      lVar9 = lVar9 + 8;
      auVar17 = std::__ndk1::pair<char*, bool> CParameterParser::GetValue<char*>(Aska::ASON::AValue::AMap const*, char const*)(lVar9,&UNK_0285e438/*"processing_priority"*/);
      auStack_88 = auVar17;
      if ((auVar17._8_8_ & 0xff) != 0) {
        uStack_150 = 0;
        puStack_148 = (undefined *)0x0;
        puStack_158 = (undefined *)0x0;
        uVar11 = strlen(auVar17._0_8_);
        if (uVar11 < 0x17) {
          puStack_158 = (undefined *)CONCAT71(puStack_158._1_7_,(char)(uVar11 << 1));
          puVar12 = (undefined *)((ulong)&puStack_158 | 1);
          if (uVar11 != 0) goto code_r0x017e8b90;
        }
        else {
          uVar15 = uVar11 + 0x10 & 0xfffffffffffffff0;
          if (uVar15 == 0) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
          }
          puVar12 = (undefined *)Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar15,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
          if (puVar12 == (undefined *)0x0) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
          }
          puStack_158 = (undefined *)(uVar15 | 1);
          uStack_150 = uVar11;
          puStack_148 = puVar12;
code_r0x017e8b90:
          memcpy(puVar12,auVar17._0_8_,uVar11);
        }
        puVar12[uVar11] = 0;
        lVar13 = std::__ndk1::__hash_iterator<std::__ndk1::__hash_node<std::__ndk1::__hash_value_type<string, CParameterCocosCommonResourceElement>, void*>*> std::__ndk1::__hash_table<std::__ndk1::__hash_value_type<string, CParameterCocosCommonResourceElement>, std::__ndk1::__unordered_map_hasher<string, std::__ndk1::__hash_value_type<string, CParameterCocosCommonResourceElement>, std::__ndk1::hash<string >, true>, std::__ndk1::__unordered_map_equal<string, std::__ndk1::__hash_value_type<string, CParameterCocosCommonResourceElement>, std::__ndk1::equal_to<string >, true>, Framework::CSTLAllocator<std::__ndk1::__hash_value_type<string, CParameterCocosCommonResourceElement>, Framework::CSTLUnorderedMapAllocatorInf> >::find<string >(string const&)(param_2,&puStack_158);
        if (((ulong)puStack_158 & 1) != 0) {
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puStack_148);
        }
        if (lVar13 == 0) {
          CParameterElementBase::CParameterElementBase()(&puStack_158);
          uStack_138 = 0;
          uStack_140 = 0;
          puStack_158 = puVar2;
          puStack_148 = puVar3;
          Framework::CHash32::CHash32()(auStack_130);
          uStack_118 = 0;
          uStack_110 = 0;
          uStack_120 = 0;
          uStack_f8 = 0;
          uStack_100 = 0;
          puStack_148 = puVar4;
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
          puStack_c8 = puVar8;
          std::__ndk1::unique_ptr<std::__ndk1::__hash_node<std::__ndk1::__hash_value_type<string, CParameterCocosCommonResourceElement>, void*>, std::__ndk1::__hash_node_destructor<Framework::CSTLAllocator<std::__ndk1::__hash_node<std::__ndk1::__hash_value_type<string, CParameterCocosCommonResourceElement>, void*>, Framework::CSTLUnorderedMapAllocatorInf> > > std::__ndk1::__hash_table<std::__ndk1::__hash_value_type<string, CParameterCocosCommonResourceElement>, std::__ndk1::__unordered_map_hasher<string, std::__ndk1::__hash_value_type<string, CParameterCocosCommonResourceElement>, std::__ndk1::hash<string >, true>, std::__ndk1::__unordered_map_equal<string, std::__ndk1::__hash_value_type<string, CParameterCocosCommonResourceElement>, std::__ndk1::equal_to<string >, true>, Framework::CSTLAllocator<std::__ndk1::__hash_value_type<string, CParameterCocosCommonResourceElement>, Framework::CSTLUnorderedMapAllocatorInf> >::__construct_node<char*&, CParameterCocosCommonResourceElement>(char*&, CParameterCocosCommonResourceElement&&)(alStack_78,param_2,auStack_88,&puStack_158);
          auVar17 = std::__ndk1::__hash_table<std::__ndk1::__hash_value_type<string, CParameterCocosCommonResourceElement>, std::__ndk1::__unordered_map_hasher<string, std::__ndk1::__hash_value_type<string, CParameterCocosCommonResourceElement>, std::__ndk1::hash<string >, true>, std::__ndk1::__unordered_map_equal<string, std::__ndk1::__hash_value_type<string, CParameterCocosCommonResourceElement>, std::__ndk1::equal_to<string >, true>, Framework::CSTLAllocator<std::__ndk1::__hash_value_type<string, CParameterCocosCommonResourceElement>, Framework::CSTLUnorderedMapAllocatorInf> >::__node_insert_unique(std::__ndk1::__hash_node<std::__ndk1::__hash_value_type<string, CParameterCocosCommonResourceElement>, void*>*)(param_2,alStack_78[0]);
          lVar13 = alStack_78[0];
          if ((auVar17._8_8_ & 1) == 0) {
            alStack_78[0] = 0;
            if (lVar13 != 0) {
              if (cStack_68 != '\0') {
                CParameterCocosCommonResourceElement::~CParameterCocosCommonResourceElement()(lVar13 + 0x28);
                if ((*(byte *)(lVar13 + 0x10) & 1) != 0) {
                  Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(*(undefined8 *)(lVar13 + 0x20));
                }
              }
              Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(lVar13);
            }
          }
          else {
            alStack_78[0] = 0;
          }
          CParameterCocosCommonResourceElement::~CParameterCocosCommonResourceElement()(&puStack_158);
          plVar16 = (long *)(auVar17._0_8_ + 0x28);
          (**(code **)*plVar16)(plVar16);
        }
        else {
          plVar16 = (long *)(lVar13 + 0x28);
        }
        (**(code **)(*plVar16 + 8))(plVar16,lVar9);
      }
      uVar1 = (int)uVar14 + 1;
      uVar14 = (ulong)uVar1;
    } while (uVar1 < *(uint *)(param_3 + 1));
  }
  return 1;
}

// ==== CParameterCocosCommonResourceElement::CParameterCocosCommonResourceElement(CParameterCocosCommonResourceElement const&)
// vaddr 0x16e9338 | ghidra 0x17e9338 | size 884 | symbol _ZN36CParameterCocosCommonResourceElementC2ERKS_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN36CParameterCocosCommonResourceElementC2ERKS_(long *param_1,long param_2)

{
  ulong uVar1;
  undefined8 uVar2;
  undefined4 uVar3;
  undefined1 uVar4;
  undefined *puVar5;
  undefined *puVar6;
  undefined *puVar7;
  long lVar8;
  long *plVar9;
  ulong uVar10;
  
  puVar7 = PTR__ZTV18IParameterProperty_02cbe818;
  puVar5 = PTR__ZTV36CParameterCocosCommonResourceElement_02cbb848;
  *param_1 = (long)(PTR__ZTV21CParameterElementBase_02cbbc00 + 0x10);
  lVar8 = *(long *)(param_2 + 8);
  *param_1 = (long)(puVar5 + 0x10);
  param_1[1] = lVar8;
  param_1[2] = (long)(puVar7 + 0x10);
  lVar8 = *(long *)(param_2 + 0x18);
  param_1[2] = (long)(PTR__ZTV22CParameterPropertyBaseILj30EE_02cbe830 + 0x10);
  param_1[3] = lVar8;
  puVar5 = PTR__ZTVN9Framework7CHash32E_02cba528;
  *(undefined1 *)(param_1 + 4) = *(undefined1 *)(param_2 + 0x20);
  param_1[5] = (long)(puVar5 + 0x10);
  puVar6 = 
  PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj30EE_02cbb158
  ;
  uVar3 = *(undefined4 *)(param_2 + 0x30);
  plVar9 = param_1 + 7;
  *plVar9 = 0;
  *(undefined4 *)(param_1 + 6) = uVar3;
  param_1[2] = (long)(puVar6 + 0x10);
  param_1[8] = 0;
  param_1[9] = 0;
  if ((*(byte *)(param_2 + 0x38) & 1) == 0) {
    param_1[9] = *(long *)(param_2 + 0x48);
    lVar8 = *(long *)(param_2 + 0x38);
    param_1[8] = *(long *)(param_2 + 0x40);
    *plVar9 = lVar8;
  }
  else {
    uVar1 = *(ulong *)(param_2 + 0x40);
    uVar2 = *(undefined8 *)(param_2 + 0x48);
    if (uVar1 < 0x17) {
      lVar8 = (long)param_1 + 0x39;
      *(char *)plVar9 = (char)(uVar1 << 1);
      if (uVar1 != 0) goto code_r0x017e9478;
    }
    else {
      uVar10 = uVar1 + 0x10 & 0xfffffffffffffff0;
      if (uVar10 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
      }
      lVar8 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar10,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
      if (lVar8 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
      }
      param_1[8] = uVar1;
      param_1[9] = lVar8;
      param_1[7] = uVar10 | 1;
code_r0x017e9478:
      memcpy(lVar8,uVar2,uVar1);
    }
    *(undefined1 *)(lVar8 + uVar1) = 0;
  }
  param_1[10] = (long)(puVar7 + 0x10);
  lVar8 = *(long *)(param_2 + 0x58);
  param_1[10] = (long)(PTR__ZTV22CParameterPropertyBaseILj31EE_02cc17e0 + 0x10);
  param_1[0xb] = lVar8;
  uVar4 = *(undefined1 *)(param_2 + 0x60);
  param_1[0xd] = (long)(puVar5 + 0x10);
  *(undefined1 *)(param_1 + 0xc) = uVar4;
  puVar6 = 
  PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj31EE_02cba990
  ;
  uVar3 = *(undefined4 *)(param_2 + 0x70);
  plVar9 = param_1 + 0xf;
  *plVar9 = 0;
  *(undefined4 *)(param_1 + 0xe) = uVar3;
  param_1[10] = (long)(puVar6 + 0x10);
  param_1[0x10] = 0;
  param_1[0x11] = 0;
  if ((*(byte *)(param_2 + 0x78) & 1) == 0) {
    param_1[0x11] = *(long *)(param_2 + 0x88);
    lVar8 = *(long *)(param_2 + 0x78);
    param_1[0x10] = *(long *)(param_2 + 0x80);
    *plVar9 = lVar8;
  }
  else {
    uVar1 = *(ulong *)(param_2 + 0x80);
    uVar2 = *(undefined8 *)(param_2 + 0x88);
    if (uVar1 < 0x17) {
      lVar8 = (long)param_1 + 0x79;
      *(char *)plVar9 = (char)(uVar1 << 1);
      if (uVar1 != 0) goto code_r0x017e957c;
    }
    else {
      uVar10 = uVar1 + 0x10 & 0xfffffffffffffff0;
      if (uVar10 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
      }
      lVar8 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar10,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
      if (lVar8 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
      }
      param_1[0x10] = uVar1;
      param_1[0x11] = lVar8;
      param_1[0xf] = uVar10 | 1;
code_r0x017e957c:
      memcpy(lVar8,uVar2,uVar1);
    }
    *(undefined1 *)(lVar8 + uVar1) = 0;
  }
  param_1[0x12] = (long)(puVar7 + 0x10);
  lVar8 = *(long *)(param_2 + 0x98);
  param_1[0x12] = (long)(PTR__ZTV22CParameterPropertyBaseILj32EE_02cc0fa8 + 0x10);
  param_1[0x13] = lVar8;
  uVar4 = *(undefined1 *)(param_2 + 0xa0);
  param_1[0x15] = (long)(puVar5 + 0x10);
  *(undefined1 *)(param_1 + 0x14) = uVar4;
  puVar5 = 
  PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj32EE_02cc31e8
  ;
  uVar3 = *(undefined4 *)(param_2 + 0xb0);
  plVar9 = param_1 + 0x17;
  *plVar9 = 0;
  *(undefined4 *)(param_1 + 0x16) = uVar3;
  param_1[0x12] = (long)(puVar5 + 0x10);
  param_1[0x18] = 0;
  param_1[0x19] = 0;
  if ((*(byte *)(param_2 + 0xb8) & 1) == 0) {
    param_1[0x19] = *(long *)(param_2 + 200);
    lVar8 = *(long *)(param_2 + 0xb8);
    param_1[0x18] = *(long *)(param_2 + 0xc0);
    *plVar9 = lVar8;
    return;
  }
  uVar1 = *(ulong *)(param_2 + 0xc0);
  uVar2 = *(undefined8 *)(param_2 + 200);
  if (uVar1 < 0x17) {
    lVar8 = (long)param_1 + 0xb9;
    *(char *)plVar9 = (char)(uVar1 << 1);
    if (uVar1 == 0) goto code_r0x017e9690;
  }
  else {
    uVar10 = uVar1 + 0x10 & 0xfffffffffffffff0;
    if (uVar10 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
    }
    lVar8 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar10,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
    if (lVar8 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    }
    param_1[0x18] = uVar1;
    param_1[0x19] = lVar8;
    param_1[0x17] = uVar10 | 1;
  }
  memcpy(lVar8,uVar2,uVar1);
code_r0x017e9690:
  *(undefined1 *)(lVar8 + uVar1) = 0;
  return;
}

// ==== CParameterPlayerElement::CParameterPlayerElement()
// vaddr 0x16f7f5c | ghidra 0x17f7f5c | size 352 | symbol _ZN23CParameterPlayerElementC2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN23CParameterPlayerElementC1Ev(long *param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  
  CParameterElementBase::CParameterElementBase()();
  puVar2 = PTR__ZTV23CParameterPlayerElement_02cc4358;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj36EE_02cb6f78;
  *(undefined1 *)(param_1 + 4) = 0;
  *param_1 = (long)(puVar2 + 0x10);
  param_1[2] = (long)(puVar1 + 0x10);
  param_1[3] = 0;
  Framework::CHash32::CHash32()(param_1 + 5);
  puVar2 = PTR__ZTV23CParameterPropertyValueIjLj36E18CPropertyConverterE_02cc2bf8;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj37EE_02cbda08;
  *(undefined1 *)(param_1 + 10) = 0;
  param_1[2] = (long)(puVar2 + 0x10);
  param_1[8] = (long)(puVar1 + 0x10);
  param_1[9] = 0;
  Framework::CHash32::CHash32()(param_1 + 0xb);
  puVar2 = PTR__ZTV22CParameterPropertyBaseILj38EE_02cc0aa0;
  puVar1 = PTR__ZTV23CParameterPropertyValueIjLj37E18CPropertyConverterE_02cba818;
  *(undefined1 *)(param_1 + 0x10) = 0;
  param_1[8] = (long)(puVar1 + 0x10);
  param_1[0xe] = (long)(puVar2 + 0x10);
  param_1[0xf] = 0;
  Framework::CHash32::CHash32()(param_1 + 0x11);
  puVar2 = PTR__ZTV23CParameterPropertyValueIjLj38E18CPropertyConverterE_02cc3fa0;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj39EE_02cc3d00;
  *(undefined1 *)(param_1 + 0x16) = 0;
  param_1[0xe] = (long)(puVar2 + 0x10);
  param_1[0x14] = (long)(puVar1 + 0x10);
  param_1[0x15] = 0;
  Framework::CHash32::CHash32()(param_1 + 0x17);
  puVar2 = PTR__ZTV22CParameterPropertyBaseILj40EE_02cbd2c0;
  puVar1 = PTR__ZTV23CParameterPropertyValueIiLj39E18CPropertyConverterE_02cbab88;
  *(undefined1 *)(param_1 + 0x1c) = 0;
  param_1[0x14] = (long)(puVar1 + 0x10);
  param_1[0x1a] = (long)(puVar2 + 0x10);
  param_1[0x1b] = 0;
  Framework::CHash32::CHash32()(param_1 + 0x1d);
  puVar2 = PTR__ZTV22CParameterPropertyBaseILj41EE_02cc2068;
  puVar1 = PTR__ZTV23CParameterPropertyValueIjLj40E18CPropertyConverterE_02cb8038;
  *(undefined1 *)(param_1 + 0x22) = 0;
  param_1[0x1a] = (long)(puVar1 + 0x10);
  param_1[0x20] = (long)(puVar2 + 0x10);
  param_1[0x21] = 0;
  Framework::CHash32::CHash32()(param_1 + 0x23);
  puVar2 = PTR__ZTV23CParameterPropertyValueIjLj41E18CPropertyConverterE_02cbafc0;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj42EE_02cb6c60;
  *(undefined1 *)(param_1 + 0x28) = 0;
  param_1[0x20] = (long)(puVar2 + 0x10);
  param_1[0x26] = (long)(puVar1 + 0x10);
  param_1[0x27] = 0;
  Framework::CHash32::CHash32()(param_1 + 0x29);
  puVar1 = 
  PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj42EE_02cbb858
  ;
  param_1[0x2c] = 0;
  param_1[0x2d] = 0;
  param_1[0x2b] = 0;
  param_1[0x26] = (long)(puVar1 + 0x10);
  return;
}

// ==== CParameterPlayerElement::~CParameterPlayerElement()
// vaddr 0x16f80bc | ghidra 0x17f80bc | size 228 | symbol _ZN23CParameterPlayerElementD1Ev | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Possible PIC construction at 0x017f8108: Changing call to branch */
/* WARNING: Possible PIC construction at 0x017f8138: Changing call to branch */
/* WARNING: Possible PIC construction at 0x017f8168: Changing call to branch */
/* WARNING: Removing unreachable block (ram,0x017f813c) */
/* WARNING: Removing unreachable block (ram,0x017f810c) */
/* WARNING: Removing unreachable block (ram,0x017f816c) */

void _ZN23CParameterPlayerElementD2Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTV23CParameterPlayerElement_02cc4358 + 0x10);
  param_1[0x26] =
       (long)(
             PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj42EE_02cbb858
             + 0x10);
  if ((*(byte *)(param_1 + 0x2b) & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(param_1[0x2d]);
  }
  param_1[0x26] = (long)(PTR__ZTV22CParameterPropertyBaseILj42EE_02cb6c60 + 0x10);
  (*(code *)PTR__ZN9Framework7CHash32D1Ev_02cb3740)(param_1 + 0x29);
  return;
}

// ==== CParameterPlayerElement::~CParameterPlayerElement()
// vaddr 0x16f81a0 | ghidra 0x17f81a0 | size 24 | symbol _ZN23CParameterPlayerElementD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN23CParameterPlayerElementD0Ev(undefined8 param_1)

{
  CParameterPlayerElement::~CParameterPlayerElement()();
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== CParameterPlayerElement::Initialize()
// vaddr 0x16f81b8 | ghidra 0x17f81b8 | size 668 | symbol _ZN23CParameterPlayerElement10InitializeEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN23CParameterPlayerElement10InitializeEv(long param_1)

{
  byte abStack_48 [16];
  undefined8 uStack_38;
  
  CParameterElementBase::Initialize()();
  abStack_48[8] = 0;
  abStack_48[9] = 0;
  abStack_48[10] = 0;
  abStack_48[0xb] = 0;
  abStack_48[0xc] = 0;
  abStack_48[0xd] = 0;
  abStack_48[0xe] = 0;
  abStack_48[0xf] = 0;
  uStack_38 = 0;
  abStack_48[4] = 0;
  abStack_48[5] = 0;
  abStack_48[6] = 0;
  abStack_48[7] = 0;
  abStack_48[0] = 4;
  abStack_48[1] = 0x49;
  abStack_48[2] = 100;
  abStack_48[3] = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x28,(ulong)abStack_48 | 1);
  *(undefined1 *)(param_1 + 0x20) = 1;
  *(undefined4 *)(param_1 + 0x38) = 0;
  if ((abStack_48[0] & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_38);
  }
  CParameterElementBase::AddProperty(IParameterProperty*)(param_1,param_1 + 0x10);
  abStack_48[8] = 0;
  abStack_48[9] = 0;
  abStack_48[10] = 0;
  abStack_48[0xb] = 0;
  abStack_48[0xc] = 0;
  abStack_48[0xd] = 0;
  abStack_48[0xe] = 0;
  abStack_48[0xf] = 0;
  uStack_38 = 0;
  abStack_48[7] = 0;
  abStack_48[0] = 10;
  abStack_48[5] = 0x6e;
  abStack_48[1] = 0x54;
  abStack_48[2] = 0x6f;
  abStack_48[3] = 0x6b;
  abStack_48[4] = 0x65;
  abStack_48[6] = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x58,(ulong)abStack_48 | 1);
  *(undefined1 *)(param_1 + 0x50) = 1;
  *(undefined4 *)(param_1 + 0x68) = 0xffffffff;
  if ((abStack_48[0] & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_38);
  }
  CParameterElementBase::AddProperty(IParameterProperty*)(param_1,param_1 + 0x40);
  abStack_48[8] = 0;
  abStack_48[9] = 0;
  abStack_48[10] = 0;
  abStack_48[0xb] = 0;
  abStack_48[0xc] = 0;
  abStack_48[0xd] = 0;
  abStack_48[0xe] = 0;
  abStack_48[0xf] = 0;
  uStack_38 = 0;
  abStack_48[7] = 0;
  abStack_48[0] = 10;
  abStack_48[5] = 0x6c;
  abStack_48[1] = 0x4c;
  abStack_48[2] = 0x65;
  abStack_48[3] = 0x76;
  abStack_48[4] = 0x65;
  abStack_48[6] = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x88,(ulong)abStack_48 | 1);
  *(undefined1 *)(param_1 + 0x80) = 1;
  *(undefined4 *)(param_1 + 0x98) = 0;
  if ((abStack_48[0] & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_38);
  }
  CParameterElementBase::AddProperty(IParameterProperty*)(param_1,param_1 + 0x70);
  abStack_48[8] = 0;
  abStack_48[9] = 0;
  abStack_48[10] = 0;
  abStack_48[0xb] = 0;
  abStack_48[0xc] = 0;
  abStack_48[0xd] = 0;
  abStack_48[0xe] = 0;
  abStack_48[0xf] = 0;
  uStack_38 = 0;
  abStack_48[6] = 0;
  abStack_48[7] = 0;
  abStack_48[0] = 8;
  abStack_48[1] = 0x52;
  abStack_48[2] = 0x6f;
  abStack_48[3] = 0x6c;
  abStack_48[4] = 0x65;
  abStack_48[5] = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0xb8,(ulong)abStack_48 | 1);
  *(undefined1 *)(param_1 + 0xb0) = 1;
  *(undefined4 *)(param_1 + 200) = 0;
  if ((abStack_48[0] & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_38);
  }
  CParameterElementBase::AddProperty(IParameterProperty*)(param_1,param_1 + 0xa0);
  abStack_48[10] = 0;
  abStack_48[0xb] = 0;
  abStack_48[0xc] = 0;
  abStack_48[0xd] = 0;
  abStack_48[0xe] = 0;
  abStack_48[0xf] = 0;
  uStack_38 = 0;
  abStack_48[0] = 0x10;
  abStack_48[1] = 0x50;
  abStack_48[2] = 0x65;
  abStack_48[3] = 0x72;
  abStack_48[4] = 0x73;
  abStack_48[5] = 0x6f;
  abStack_48[6] = 0x6e;
  abStack_48[7] = 0x49;
  abStack_48[8] = 0x44;
  abStack_48[9] = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0xe8,(ulong)abStack_48 | 1);
  *(undefined1 *)(param_1 + 0xe0) = 1;
  *(undefined4 *)(param_1 + 0xf8) = 0;
  if ((abStack_48[0] & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_38);
  }
  CParameterElementBase::AddProperty(IParameterProperty*)(param_1,param_1 + 0xd0);
  abStack_48[8] = 0;
  abStack_48[9] = 0;
  abStack_48[10] = 0;
  abStack_48[0xb] = 0;
  abStack_48[0xc] = 0;
  abStack_48[0xd] = 0;
  abStack_48[0xe] = 0;
  abStack_48[0xf] = 0;
  uStack_38 = 0;
  abStack_48[0] = 0xc;
  abStack_48[5] = 0x6f;
  abStack_48[6] = 0x6e;
  abStack_48[1] = 0x57;
  abStack_48[2] = 0x65;
  abStack_48[3] = 0x61;
  abStack_48[4] = 0x70;
  abStack_48[7] = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x118,(ulong)abStack_48 | 1);
  *(undefined1 *)(param_1 + 0x110) = 1;
  *(undefined4 *)(param_1 + 0x128) = 0;
  if ((abStack_48[0] & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_38);
  }
  CParameterElementBase::AddProperty(IParameterProperty*)(param_1,param_1 + 0x100);
  abStack_48[8] = 0;
  abStack_48[9] = 0;
  abStack_48[10] = 0;
  abStack_48[0xb] = 0;
  abStack_48[0xc] = 0;
  abStack_48[0xd] = 0;
  abStack_48[0xe] = 0;
  abStack_48[0xf] = 0;
  uStack_38 = 0;
  abStack_48[6] = 0;
  abStack_48[7] = 0;
  abStack_48[0] = 8;
  abStack_48[1] = 0x4e;
  abStack_48[2] = 0x61;
  abStack_48[3] = 0x6d;
  abStack_48[4] = 0x65;
  abStack_48[5] = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x148,(ulong)abStack_48 | 1);
  *(undefined1 *)(param_1 + 0x140) = 1;
  if ((abStack_48[0] & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_38);
  }
  CParameterElementBase::AddProperty(IParameterProperty*)(param_1,param_1 + 0x130);
  return;
}

// ==== CParameterPlayer::CParameterPlayer()
// vaddr 0x16f8454 | ghidra 0x17f8454 | size 48 | symbol _ZN16CParameterPlayerC1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN16CParameterPlayerC2Ev(long *param_1)

{
  CParameterBase::CParameterBase()();
  *param_1 = (long)(PTR__ZTV16CParameterPlayer_02cc18c0 + 0x10);
  CParameterPlayerElement::CParameterPlayerElement()(param_1 + 1);
  *(undefined1 *)(param_1 + 0x2f) = 0;
  return;
}

// ==== CParameterPlayer::~CParameterPlayer()
// vaddr 0x16f8484 | ghidra 0x17f8484 | size 32 | symbol _ZN16CParameterPlayerD2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN16CParameterPlayerD1Ev(long *param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZTV16CParameterPlayer_02cc18c0;
  *(undefined1 *)(param_1 + 0x2f) = 0;
  *param_1 = (long)(puVar1 + 0x10);
  (*(code *)PTR__ZN23CParameterPlayerElementD2Ev_02ca92b8)(param_1 + 1);
  return;
}

// ==== CParameterPlayer::~CParameterPlayer()
// vaddr 0x16f84a4 | ghidra 0x17f84a4 | size 48 | symbol _ZN16CParameterPlayerD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN16CParameterPlayerD0Ev(long *param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZTV16CParameterPlayer_02cc18c0;
  *(undefined1 *)(param_1 + 0x2f) = 0;
  *param_1 = (long)(puVar1 + 0x10);
  CParameterPlayerElement::~CParameterPlayerElement()(param_1 + 1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== CParameterPlayer::pParseName() const
// vaddr 0x16f84d4 | ghidra 0x17f84d4 | size 12 | symbol _ZNK16CParameterPlayer10pParseNameEv | lib libSOA-3.7.0.so | 2026-10-04
undefined * _ZNK16CParameterPlayer10pParseNameEv(void)

{
  return &UNK_028a4177/*"Player"*/;
}

// ==== CParameterPlayer::Deserialize(Aska::ASON::AValue::AMap const*)
// vaddr 0x16f84e0 | ghidra 0x17f84e0 | size 120 | symbol _ZN16CParameterPlayer11DeserializeEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-04
byte _ZN16CParameterPlayer11DeserializeEPKN4Aska4ASON6AValue4AMapE(long *param_1,long param_2)

{
  byte bVar1;
  long lVar2;
  
  if (param_2 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0285e95b/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\ParameterPlayer.cpp"*/,0x35,&UNK_027dc58a/*"apParser is null."*/);
  }
  lVar2 = (**(code **)(*param_1 + 0x30))(param_1,param_2);
  bVar1 = 0;
  if (lVar2 != 0) {
    CParameterPlayerElement::Initialize()(param_1 + 1);
    bVar1 = CParameterElementBase::Deserialize(Aska::ASON::AValue::AMap const*)(param_1 + 1,lVar2 + 8);
    *(byte *)(param_1 + 0x2f) = bVar1 & 1;
  }
  return bVar1 & 1;
}

// ==== CParameterPlayer::pParameter() const
// vaddr 0x16f8558 | ghidra 0x17f8558 | size 20 | symbol _ZNK16CParameterPlayer10pParameterEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK16CParameterPlayer10pParameterEv(long param_1)

{
  long lVar1;
  
  lVar1 = 0;
  if (*(char *)(param_1 + 0x178) != '\0') {
    lVar1 = param_1 + 8;
  }
  return lVar1;
}

// ==== CParameterPlayer::CopyForMultiplay(Aska::Yayoi::MultiplayRPC::PlayerDetailInfo*)
// vaddr 0x16f856c | ghidra 0x17f856c | size 176 | symbol _ZN16CParameterPlayer16CopyForMultiplayEPN4Aska5Yayoi12MultiplayRPC16PlayerDetailInfoE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN16CParameterPlayer16CopyForMultiplayEPN4Aska5Yayoi12MultiplayRPC16PlayerDetailInfoE
               (undefined8 *param_1,long param_2,long param_3)

{
  ulong uVar1;
  undefined8 uVar2;
  ulong auStack_38 [3];
  
  if (*(char *)(param_2 + 0x178) == '\0') {
    uVar2 = 0xfffffffffffffc5b;
  }
  else {
    *(undefined4 *)(param_3 + 0x6c) = *(undefined4 *)(param_2 + 0x40);
    *(short *)(param_3 + 0x2c) = (short)*(undefined4 *)(param_2 + 0xa0);
    *(undefined4 *)(param_3 + 0x14) = *(undefined4 *)(param_2 + 0xd0);
    auStack_38[1] = 0;
    auStack_38[2] = 0;
    auStack_38[0] = 0;
    void CParameterPropertyBase<42u>::CryptString<string >(string&, string const&)(auStack_38,param_2 + 0x160);
    uVar1 = (ulong)auStack_38 | 1;
    if ((auStack_38[0] & 1) != 0) {
      uVar1 = auStack_38[2];
    }
    snprintf(param_3 + 0x31,0x30,&UNK_027f6a37/*"%s"*/,uVar1);
    if ((auStack_38[0] & 1) != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(auStack_38[2]);
    }
    uVar2 = 0;
  }
  *param_1 = uVar2;
  return;
}

// ==== CParameterPlayer::Initialize()
// vaddr 0x16f861c | ghidra 0x17f861c | size 8 | symbol _ZN16CParameterPlayer10InitializeEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN16CParameterPlayer10InitializeEv(long param_1)

{
  *(undefined1 *)(param_1 + 0x178) = 0;
  (*(code *)PTR__ZN14CParameterBase10InitializeEv_02cb5e48)();
  return;
}


// FAILED to create function at 02b0b800 CParameterCocosCommonResourceElement::vtable
// FAILED to create function at 02b0b830 CParameterCocosCommonResource::vtable
// FAILED to create function at 02b0b880 CParameterCocosCommonResourceElement::typeinfo
// FAILED to create function at 02b0b8a0 CParameterCocosCommonResource::typeinfo
// FAILED to create function at 02b0ba18 CParameterPlayerElement::vtable
// FAILED to create function at 02b0ba48 CParameterPlayer::vtable
// FAILED to create function at 02b0ba90 CParameterPlayerElement::typeinfo
// FAILED to create function at 02b0bab0 CParameterPlayer::typeinfo
