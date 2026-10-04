// port/decomp/data_formats/csv.c: Ghidra decompiles for the data_formats subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-04 05:14 UTC: tools/decomp.sh '--into' 'data_formats/csv' 'Framework::CACSV::' 'Framework::CCSV::'

// ==== Framework::CCSV::tElement::tElement()
// vaddr 0x1e6c630 | ghidra 0x1f6c630 | size 8 | symbol _ZN9Framework4CCSV8tElementC2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework4CCSV8tElementC1Ev(undefined4 *param_1)

{
  *param_1 = 0;
  return;
}

// ==== Framework::CCSV::tElement::tElement(double)
// vaddr 0x1e6c638 | ghidra 0x1f6c638 | size 16 | symbol _ZN9Framework4CCSV8tElementC1Ed | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework4CCSV8tElementC2Ed(undefined8 param_1,undefined4 *param_2)

{
  *param_2 = 1;
  *(undefined8 *)(param_2 + 2) = param_1;
  return;
}

// ==== Framework::CCSV::tElement::tElement(std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > const&)
// vaddr 0x1e6c648 | ghidra 0x1f6c648 | size 520 | symbol _ZN9Framework4CCSV8tElementC2ERKNSt6__ndk112basic_stringIcNS2_11char_traitsIcEENS_13CSTLAllocatorIcNS_22CSTLStringAllocatorInfEEEEE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework4CCSV8tElementC1ERKNSt6__ndk112basic_stringIcNS2_11char_traitsIcEENS_13CSTLAllocatorIcNS_22CSTLStringAllocatorInfEEEEE
               (undefined4 *param_1,ulong *param_2)

{
  byte *pbVar1;
  long lVar2;
  undefined8 uVar3;
  undefined8 *puVar4;
  ulong uVar5;
  ulong uVar6;
  ulong *puVar7;
  byte *pbVar8;
  ulong uVar9;
  ulong uVar10;
  
  *param_1 = 2;
  lVar2 = Framework::CAssignedMemoryManagerForSTLAllocator::pAttachFixedLengthAllocator()();
  if (lVar2 != 0) {
    uVar3 = Framework::CAssignedMemoryManagerForSTLAllocator::pAttachFixedLengthAllocator()();
    puVar4 = (undefined8 *)Framework::CFixedLengthAllocatorContainer::pAllocate(unsigned long, char const*, unsigned int)(uVar3,0x18,&UNK_02962238/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\CSV.cpp"*/,0x36);
    *(undefined8 **)(param_1 + 2) = puVar4;
    if (puVar4 != (undefined8 *)0x0) {
      puVar4[1] = 0;
      puVar4[2] = 0;
      *puVar4 = 0;
      puVar7 = *(ulong **)(param_1 + 2);
      if (puVar7 == param_2) {
        return;
      }
      uVar10 = param_2[1];
      pbVar1 = (byte *)param_2[2];
      uVar6 = (ulong)(byte)*puVar7;
      if (((byte)*param_2 & 1) == 0) {
        pbVar1 = (byte *)((long)param_2 + 1);
        uVar10 = (ulong)(byte)((byte)*param_2 >> 1);
      }
      if (((byte)*puVar7 & 1) == 0) {
        uVar5 = 0x16;
        lVar2 = uVar10 - 0x16;
        if (0x15 < uVar10 && lVar2 != 0) {
code_r0x01f6c750:
          if ((uVar6 & 1) == 0) {
            uVar6 = (ulong)(((uint)uVar6 & 0xfe) >> 1);
          }
          else {
            uVar6 = puVar7[1];
          }
          (*(code *)
            PTR__ZNSt6__ndk112basic_stringIcNS_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS3_22CSTLStringAllocatorInfEEEE21__grow_by_and_replaceEmmmmmmPKc_02ca6d40
          )(puVar7,uVar5,lVar2,uVar6,0,uVar6,uVar10);
          return;
        }
      }
      else {
        uVar6 = *puVar7;
        uVar5 = (uVar6 & 0xfffffffffffffffe) - 1;
        lVar2 = uVar10 - uVar5;
        if (uVar5 <= uVar10 && lVar2 != 0) goto code_r0x01f6c750;
      }
      if ((uVar6 & 1) == 0) {
        pbVar8 = (byte *)((long)puVar7 + 1);
      }
      else {
        pbVar8 = (byte *)puVar7[2];
      }
      if (uVar10 != 0) {
        memmove(pbVar8,pbVar1,uVar10);
      }
      pbVar8[uVar10] = 0;
      if ((*puVar7 & 1) == 0) {
        *(byte *)puVar7 = (byte)(uVar10 << 1);
        return;
      }
      puVar7[1] = uVar10;
      return;
    }
  }
  puVar7 = (ulong *)operator new(unsigned long, std::nothrow_t const&)(0x18,PTR__ZSt7nothrow_02cb9a80);
  if (puVar7 == (ulong *)0x0) goto code_r0x01f6c7d8;
  puVar7[1] = 0;
  puVar7[2] = 0;
  *puVar7 = 0;
  if ((*param_2 & 1) == 0) {
    puVar7[2] = param_2[2];
    uVar10 = *param_2;
    puVar7[1] = param_2[1];
    *puVar7 = uVar10;
    goto code_r0x01f6c7d8;
  }
  uVar10 = param_2[1];
  uVar6 = param_2[2];
  if (uVar10 < 0x17) {
    uVar9 = (long)puVar7 + 1;
    *(char *)puVar7 = (char)(uVar10 << 1);
    if (uVar10 != 0) goto code_r0x01f6c7c4;
  }
  else {
    uVar5 = uVar10 + 0x10 & 0xfffffffffffffff0;
    if (uVar5 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296188c/*"C:\BAS_Submission\Client\Library\Framework\Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
    }
    uVar9 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar5,&UNK_029618d8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/STL_String.h"*/,0x1c);
    if (uVar9 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296188c/*"C:\BAS_Submission\Client\Library\Framework\Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    }
    puVar7[1] = uVar10;
    puVar7[2] = uVar9;
    *puVar7 = uVar5 | 1;
code_r0x01f6c7c4:
    memcpy(uVar9,uVar6,uVar10);
  }
  *(undefined1 *)(uVar9 + uVar10) = 0;
code_r0x01f6c7d8:
  *(ulong **)(param_1 + 2) = puVar7;
  return;
}

// ==== Framework::CCSV::tElement::tElement(Framework::CCSV::tElement&&)
// vaddr 0x1e6c850 | ghidra 0x1f6c850 | size 140 | symbol _ZN9Framework4CCSV8tElementC2EOS1_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework4CCSV8tElementC1EOS1_(int *param_1,int *param_2)

{
  int iVar1;
  
  iVar1 = *param_2;
  if (iVar1 == 0) {
    iVar1 = 0;
  }
  else {
    if (iVar1 == 1) {
      *param_1 = 1;
      *(undefined8 *)(param_1 + 2) = *(undefined8 *)(param_2 + 2);
      return;
    }
    if (iVar1 == 2) {
      *param_1 = 2;
      *(undefined8 *)(param_1 + 2) = *(undefined8 *)(param_2 + 2);
      param_2[2] = 0;
      param_2[3] = 0;
      *param_2 = 0;
      return;
    }
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02962238/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\CSV.cpp"*/,0x4f,&UNK_027ec344/*"Illegal type.(%d)"*/);
    iVar1 = *param_2;
  }
  *param_1 = iVar1;
  return;
}

// ==== Framework::CCSV::tElement::tElement(Framework::CCSV::tElement const&)
// vaddr 0x1e6c8dc | ghidra 0x1f6c8dc | size 132 | symbol _ZN9Framework4CCSV8tElementC1ERKS1_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework4CCSV8tElementC2ERKS1_(int *param_1,int *param_2)

{
  int iVar1;
  
  iVar1 = *param_2;
  if (iVar1 == 0) {
    iVar1 = 0;
  }
  else {
    if (iVar1 == 1) {
      *param_1 = 1;
      *(undefined8 *)(param_1 + 2) = *(undefined8 *)(param_2 + 2);
      return;
    }
    if (iVar1 == 2) {
      (*(code *)
        PTR__ZN9Framework4CCSV8tElementC1ERKNSt6__ndk112basic_stringIcNS2_11char_traitsIcEENS_13CSTLAllocatorIcNS_22CSTLStringAllocatorInfEEEEE_02ca09a0
      )(param_1,*(undefined8 *)(param_2 + 2));
      return;
    }
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02962238/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\CSV.cpp"*/,0x6d,&UNK_027ec344/*"Illegal type.(%d)"*/);
    iVar1 = *param_2;
  }
  *param_1 = iVar1;
  return;
}

// ==== Framework::CCSV::tElement::operator=(Framework::CCSV::tElement const&)
// vaddr 0x1e6c960 | ghidra 0x1f6c960 | size 136 | symbol _ZN9Framework4CCSV8tElementaSERKS1_ | lib libSOA-3.7.0.so | 2026-10-04
int * _ZN9Framework4CCSV8tElementaSERKS1_(int *param_1,int *param_2)

{
  int iVar1;
  
  Framework::CCSV::tElement::Delete()();
  iVar1 = *param_2;
  if (iVar1 == 0) {
    iVar1 = 0;
  }
  else {
    if (iVar1 == 1) {
      *param_1 = 1;
      *(undefined8 *)(param_1 + 2) = *(undefined8 *)(param_2 + 2);
      return param_1;
    }
    if (iVar1 == 2) {
      Framework::CCSV::tElement::tElement(string const&)(param_1,*(undefined8 *)(param_2 + 2));
      return param_1;
    }
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02962238/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\CSV.cpp"*/,0x6d,&UNK_027ec344/*"Illegal type.(%d)"*/);
    iVar1 = *param_2;
  }
  *param_1 = iVar1;
  return param_1;
}

// ==== Framework::CCSV::tElement::Delete()
// vaddr 0x1e6c9e8 | ghidra 0x1f6c9e8 | size 180 | symbol _ZN9Framework4CCSV8tElement6DeleteEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework4CCSV8tElement6DeleteEv(int *param_1)

{
  long lVar1;
  undefined8 uVar2;
  ulong uVar3;
  byte *pbVar4;
  int *piVar5;
  
  if (*param_1 != 2) goto code_r0x01f6ca84;
  lVar1 = Framework::CAssignedMemoryManagerForSTLAllocator::pAttachFixedLengthAllocator()();
  if (lVar1 == 0) {
    pbVar4 = *(byte **)(param_1 + 2);
joined_r0x01f6ca64:
    if (pbVar4 != (byte *)0x0) {
      if ((*pbVar4 & 1) != 0) {
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(*(undefined8 *)(pbVar4 + 0x10));
      }
      operator delete(void*)(pbVar4);
    }
  }
  else {
    uVar2 = Framework::CAssignedMemoryManagerForSTLAllocator::pAttachFixedLengthAllocator()();
    piVar5 = param_1 + 2;
    uVar3 = Framework::CFixedLengthAllocatorContainer::IsMine(void*) const(uVar2,*(undefined8 *)piVar5);
    pbVar4 = *(byte **)piVar5;
    if ((uVar3 & 1) == 0) goto joined_r0x01f6ca64;
    if ((*pbVar4 & 1) != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(*(undefined8 *)(pbVar4 + 0x10));
    }
    uVar2 = Framework::CAssignedMemoryManagerForSTLAllocator::pAttachFixedLengthAllocator()();
    uVar3 = Framework::CFixedLengthAllocatorContainer::Free(void*)(uVar2,*(undefined8 *)piVar5);
    if ((uVar3 & 1) == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02962238/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\CSV.cpp"*/,0xa2,&UNK_029614eb/*"result is null."*/);
    }
  }
  param_1[2] = 0;
  param_1[3] = 0;
code_r0x01f6ca84:
  *param_1 = 0;
  return;
}

// ==== Framework::CCSV::tElement::operator=(Framework::CCSV::tElement&&)
// vaddr 0x1e6ca9c | ghidra 0x1f6ca9c | size 136 | symbol _ZN9Framework4CCSV8tElementaSEOS1_ | lib libSOA-3.7.0.so | 2026-10-04
int * _ZN9Framework4CCSV8tElementaSEOS1_(int *param_1,int *param_2)

{
  int iVar1;
  
  Framework::CCSV::tElement::Delete()();
  iVar1 = *param_2;
  if (iVar1 == 0) {
    iVar1 = 0;
  }
  else {
    if (iVar1 == 1) {
      *param_1 = 1;
      *(undefined8 *)(param_1 + 2) = *(undefined8 *)(param_2 + 2);
      return param_1;
    }
    if (iVar1 == 2) {
      Framework::CCSV::tElement::tElement(string const&)(param_1,*(undefined8 *)(param_2 + 2));
      return param_1;
    }
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02962238/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\CSV.cpp"*/,0x6d,&UNK_027ec344/*"Illegal type.(%d)"*/);
    iVar1 = *param_2;
  }
  *param_1 = iVar1;
  return param_1;
}

// ==== Framework::CCSV::tElement::IsString() const
// vaddr 0x1e6cb24 | ghidra 0x1f6cb24 | size 16 | symbol _ZNK9Framework4CCSV8tElement8IsStringEv | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK9Framework4CCSV8tElement8IsStringEv(int *param_1)

{
  return *param_1 == 2;
}

// ==== Framework::CCSV::tElement::~tElement()
// vaddr 0x1e6cb34 | ghidra 0x1f6cb34 | size 4 | symbol _ZN9Framework4CCSV8tElementD1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework4CCSV8tElementD2Ev(void)

{
  (*(code *)PTR__ZN9Framework4CCSV8tElement6DeleteEv_02c956b0)();
  return;
}

// ==== Framework::CCSV::tElement::Type() const
// vaddr 0x1e6cb38 | ghidra 0x1f6cb38 | size 8 | symbol _ZNK9Framework4CCSV8tElement4TypeEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK9Framework4CCSV8tElement4TypeEv(undefined4 *param_1)

{
  return *param_1;
}

// ==== Framework::CCSV::tElement::IsBlank() const
// vaddr 0x1e6cb40 | ghidra 0x1f6cb40 | size 16 | symbol _ZNK9Framework4CCSV8tElement7IsBlankEv | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK9Framework4CCSV8tElement7IsBlankEv(int *param_1)

{
  return *param_1 == 0;
}

// ==== Framework::CCSV::tElement::IsValue() const
// vaddr 0x1e6cb50 | ghidra 0x1f6cb50 | size 16 | symbol _ZNK9Framework4CCSV8tElement7IsValueEv | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK9Framework4CCSV8tElement7IsValueEv(int *param_1)

{
  return *param_1 == 1;
}

// ==== Framework::CCSV::tElement::Value() const
// vaddr 0x1e6cb60 | ghidra 0x1f6cb60 | size 56 | symbol _ZNK9Framework4CCSV8tElement5ValueEv | lib libSOA-3.7.0.so | 2026-10-04
undefined1  [16] _ZNK9Framework4CCSV8tElement5ValueEv(int *param_1)

{
  undefined1 auVar1 [16];
  
  if (*param_1 != 1) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02962238/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\CSV.cpp"*/,0xd3,&UNK_02962287/*"IsValue() is null."*/);
  }
  auVar1._0_8_ = *(ulong *)(param_1 + 2);
  auVar1._8_8_ = 0;
  return auVar1;
}

// ==== Framework::CCSV::tElement::ValueSafe(double) const
// vaddr 0x1e6cb98 | ghidra 0x1f6cb98 | size 20 | symbol _ZNK9Framework4CCSV8tElement9ValueSafeEd | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK9Framework4CCSV8tElement9ValueSafeEd(undefined8 param_1,int *param_2)

{
  if (*param_2 == 1) {
    param_1 = *(undefined8 *)(param_2 + 2);
  }
  return param_1;
}

// ==== Framework::CCSV::tElement::String() const
// vaddr 0x1e6cbac | ghidra 0x1f6cbac | size 104 | symbol _ZNK9Framework4CCSV8tElement6StringEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK9Framework4CCSV8tElement6StringEv(int *param_1)

{
  long lVar1;
  
  if (*param_1 == 2) {
    lVar1 = *(long *)(param_1 + 2);
  }
  else {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02962238/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\CSV.cpp"*/,0xe0,&UNK_0296229a/*"IsString() is null."*/);
    lVar1 = *(long *)(param_1 + 2);
  }
  if (lVar1 != 0) {
    return lVar1;
  }
  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02962238/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\CSV.cpp"*/,0xe1,&UNK_029622ae/*"m_pString is null."*/);
  return *(long *)(param_1 + 2);
}

// ==== Framework::CCSV::tElement::StringSafe(std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > const&) const
// vaddr 0x1e6cc14 | ghidra 0x1f6cc14 | size 528 | symbol _ZNK9Framework4CCSV8tElement10StringSafeERKNSt6__ndk112basic_stringIcNS2_11char_traitsIcEENS_13CSTLAllocatorIcNS_22CSTLStringAllocatorInfEEEEE | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK9Framework4CCSV8tElement10StringSafeERKNSt6__ndk112basic_stringIcNS2_11char_traitsIcEENS_13CSTLAllocatorIcNS_22CSTLStringAllocatorInfEEEEE
               (ulong *param_1,int *param_2,ulong *param_3)

{
  ulong uVar1;
  ulong uVar2;
  undefined1 *puVar3;
  ulong *puVar4;
  ulong uVar5;
  undefined1 auStack_b0 [128];
  
  puVar3 = auStack_b0;
  if (*param_2 == 1) {
    snprintf(*(undefined8 *)(param_2 + 2),auStack_b0,0x80,&UNK_029622c1/*"%f"*/);
    param_1[1] = 0;
    param_1[2] = 0;
    *param_1 = 0;
    uVar1 = strlen(auStack_b0);
    if (uVar1 < 0x17) {
      *(char *)param_1 = (char)(uVar1 << 1);
      puVar3 = auStack_b0;
      goto joined_r0x01f6ccc8;
    }
    uVar5 = uVar1 + 0x10 & 0xfffffffffffffff0;
    if (uVar5 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296188c/*"C:\BAS_Submission\Client\Library\Framework\Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
    }
    uVar2 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar5,&UNK_029618d8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/STL_String.h"*/,0x1c);
    if (uVar2 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296188c/*"C:\BAS_Submission\Client\Library\Framework\Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    }
    param_1[1] = uVar1;
    param_1[2] = uVar2;
    *param_1 = uVar5 | 1;
  }
  else {
    if (*param_2 == 2) {
      puVar4 = *(ulong **)(param_2 + 2);
      if (puVar4 == (ulong *)0x0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02962238/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\CSV.cpp"*/,0xee,&UNK_029622ae/*"m_pString is null."*/);
        puVar4 = *(ulong **)(param_2 + 2);
      }
      param_1[1] = 0;
      param_1[2] = 0;
      *param_1 = 0;
      if ((*puVar4 & 1) == 0) {
        param_1[2] = puVar4[2];
        uVar1 = *puVar4;
        param_1[1] = puVar4[1];
        *param_1 = uVar1;
        return;
      }
      uVar1 = puVar4[1];
      puVar3 = (undefined1 *)puVar4[2];
    }
    else {
      param_1[1] = 0;
      param_1[2] = 0;
      *param_1 = 0;
      if ((*param_3 & 1) == 0) {
        param_1[2] = param_3[2];
        uVar1 = *param_3;
        param_1[1] = param_3[1];
        *param_1 = uVar1;
        return;
      }
      uVar1 = param_3[1];
      puVar3 = (undefined1 *)param_3[2];
    }
    if (uVar1 < 0x17) {
      *(char *)param_1 = (char)(uVar1 << 1);
joined_r0x01f6ccc8:
      uVar2 = (long)param_1 + 1;
      if (uVar1 == 0) goto code_r0x01f6ce0c;
    }
    else {
      uVar5 = uVar1 + 0x10 & 0xfffffffffffffff0;
      if (uVar5 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296188c/*"C:\BAS_Submission\Client\Library\Framework\Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
      }
      uVar2 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar5,&UNK_029618d8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/STL_String.h"*/,0x1c);
      if (uVar2 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296188c/*"C:\BAS_Submission\Client\Library\Framework\Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
      }
      param_1[1] = uVar1;
      param_1[2] = uVar2;
      *param_1 = uVar5 | 1;
    }
  }
  memcpy(uVar2,puVar3,uVar1);
code_r0x01f6ce0c:
  *(undefined1 *)(uVar2 + uVar1) = 0;
  return;
}

// ==== Framework::CCSV::tElement::Value(double)
// vaddr 0x1e6ce24 | ghidra 0x1f6ce24 | size 72 | symbol _ZN9Framework4CCSV8tElement5ValueEd | lib libSOA-3.7.0.so | 2026-10-04
undefined1  [16] _ZN9Framework4CCSV8tElement5ValueEd(undefined8 param_1,int *param_2)

{
  undefined1 auVar1 [16];
  
  if (*param_2 != 1) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02962238/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\CSV.cpp"*/,0x104,&UNK_02962287/*"IsValue() is null."*/);
  }
  auVar1._0_8_ = *(ulong *)(param_2 + 2);
  *(undefined8 *)(param_2 + 2) = param_1;
  auVar1._8_8_ = 0;
  return auVar1;
}

// ==== Framework::CCSV::tElement::String(std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > const&)
// vaddr 0x1e6ce6c | ghidra 0x1f6ce6c | size 336 | symbol _ZN9Framework4CCSV8tElement6StringERKNSt6__ndk112basic_stringIcNS2_11char_traitsIcEENS_13CSTLAllocatorIcNS_22CSTLStringAllocatorInfEEEEE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework4CCSV8tElement6StringERKNSt6__ndk112basic_stringIcNS2_11char_traitsIcEENS_13CSTLAllocatorIcNS_22CSTLStringAllocatorInfEEEEE
               (int *param_1,ulong *param_2)

{
  ulong uVar1;
  ulong uVar2;
  long lVar3;
  byte *pbVar4;
  ulong uVar5;
  ulong *puVar6;
  byte *pbVar7;
  
  if (*param_1 == 2) {
    pbVar4 = *(byte **)(param_1 + 2);
    if (pbVar4 == (byte *)0x0) goto code_r0x01f6cec0;
code_r0x01f6ce90:
    if ((*pbVar4 & 1) != 0) goto code_r0x01f6cee4;
code_r0x01f6ce98:
    pbVar4[0] = 0;
    pbVar4[1] = 0;
  }
  else {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02962238/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\CSV.cpp"*/,0x10f,&UNK_0296229a/*"IsString() is null."*/);
    pbVar4 = *(byte **)(param_1 + 2);
    if (pbVar4 != (byte *)0x0) goto code_r0x01f6ce90;
code_r0x01f6cec0:
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02962238/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\CSV.cpp"*/,0x110,&UNK_029622ae/*"m_pString is null."*/);
    pbVar4 = *(byte **)(param_1 + 2);
    if ((*pbVar4 & 1) == 0) goto code_r0x01f6ce98;
code_r0x01f6cee4:
    **(undefined1 **)(pbVar4 + 0x10) = 0;
    pbVar4[8] = 0;
    pbVar4[9] = 0;
    pbVar4[10] = 0;
    pbVar4[0xb] = 0;
    pbVar4[0xc] = 0;
    pbVar4[0xd] = 0;
    pbVar4[0xe] = 0;
    pbVar4[0xf] = 0;
  }
  puVar6 = *(ulong **)(param_1 + 2);
  if (puVar6 != param_2) {
    uVar1 = param_2[1];
    pbVar4 = (byte *)param_2[2];
    uVar5 = (ulong)(byte)*puVar6;
    if (((byte)*param_2 & 1) == 0) {
      pbVar4 = (byte *)((long)param_2 + 1);
      uVar1 = (ulong)(byte)((byte)*param_2 >> 1);
    }
    if (((byte)*puVar6 & 1) == 0) {
      uVar2 = 0x16;
      lVar3 = uVar1 - 0x16;
      if (0x15 < uVar1 && lVar3 != 0) {
code_r0x01f6cf4c:
        if ((uVar5 & 1) == 0) {
          uVar5 = (ulong)(((uint)uVar5 & 0xfe) >> 1);
        }
        else {
          uVar5 = puVar6[1];
        }
        (*(code *)
          PTR__ZNSt6__ndk112basic_stringIcNS_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS3_22CSTLStringAllocatorInfEEEE21__grow_by_and_replaceEmmmmmmPKc_02ca6d40
        )(puVar6,uVar2,lVar3,uVar5,0,uVar5,uVar1);
        return;
      }
    }
    else {
      uVar5 = *puVar6;
      uVar2 = (uVar5 & 0xfffffffffffffffe) - 1;
      lVar3 = uVar1 - uVar2;
      if (uVar2 <= uVar1 && lVar3 != 0) goto code_r0x01f6cf4c;
    }
    if ((uVar5 & 1) == 0) {
      pbVar7 = (byte *)((long)puVar6 + 1);
    }
    else {
      pbVar7 = (byte *)puVar6[2];
    }
    if (uVar1 != 0) {
      memmove(pbVar7,pbVar4,uVar1);
    }
    pbVar7[uVar1] = 0;
    if ((*puVar6 & 1) == 0) {
      *(byte *)puVar6 = (byte)(uVar1 << 1);
    }
    else {
      puVar6[1] = uVar1;
    }
  }
  return;
}

// ==== Framework::CCSV::tElement::rString()
// vaddr 0x1e6cfbc | ghidra 0x1f6cfbc | size 104 | symbol _ZN9Framework4CCSV8tElement7rStringEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZN9Framework4CCSV8tElement7rStringEv(int *param_1)

{
  long lVar1;
  
  if (*param_1 == 2) {
    lVar1 = *(long *)(param_1 + 2);
  }
  else {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02962238/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\CSV.cpp"*/,0x119,&UNK_0296229a/*"IsString() is null."*/);
    lVar1 = *(long *)(param_1 + 2);
  }
  if (lVar1 != 0) {
    return lVar1;
  }
  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02962238/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\CSV.cpp"*/,0x11a,&UNK_029622ae/*"m_pString is null."*/);
  return *(long *)(param_1 + 2);
}

// ==== Framework::CCSV::CCSV()
// vaddr 0x1e6d024 | ghidra 0x1f6d024 | size 36 | symbol _ZN9Framework4CCSVC1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework4CCSVC2Ev(undefined1 *param_1)

{
  *param_1 = 0;
  *(undefined8 *)(param_1 + 0x10) = 0;
  *(undefined8 *)(param_1 + 0x18) = 0;
  *(undefined4 *)(param_1 + 0x20) = 0;
  param_1[2] = 0x2c;
  param_1[3] = 0x22;
  *(undefined8 *)(param_1 + 8) = 0;
  return;
}

// ==== Framework::CCSV::~CCSV()
// vaddr 0x1e6d048 | ghidra 0x1f6d048 | size 260 | symbol _ZN9Framework4CCSVD2Ev | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Possible PIC construction at 0x01f6d0a0: Changing call to branch */
/* WARNING: Possible PIC construction at 0x01f6d110: Changing call to branch */
/* WARNING: Removing unreachable block (ram,0x01f6d0a4) */
/* WARNING: Removing unreachable block (ram,0x01f6d114) */

void _ZN9Framework4CCSVD1Ev(undefined1 *param_1)

{
  long lVar1;
  long lVar2;
  long *plVar3;
  long *plVar4;
  long *plVar5;
  
  plVar4 = *(long **)(param_1 + 0x10);
  do {
    plVar5 = plVar4;
    if (plVar5 == *(long **)(param_1 + 8)) {
      *param_1 = 0;
      Framework::CCSV::tElement::Delete()(param_1 + 0x20);
      plVar3 = *(long **)(param_1 + 8);
      if (plVar3 == (long *)0x0) {
        return;
      }
      plVar4 = *(long **)(param_1 + 0x10);
      if (*(long **)(param_1 + 0x10) == plVar3) goto code_r0x011d23a0;
      goto code_r0x01f6d0d4;
    }
    plVar4 = plVar5 + -3;
    *(long **)(param_1 + 0x10) = plVar4;
    plVar3 = (long *)plVar5[-3];
  } while (plVar3 == (long *)0x0);
  lVar1 = plVar5[-2];
  if ((long *)lVar1 != plVar3) {
    do {
      plVar5[-2] = lVar1 + -0x10;
      Framework::CCSV::tElement::Delete()();
      lVar1 = plVar5[-2];
    } while ((long *)lVar1 != plVar3);
    plVar3 = (long *)*plVar4;
  }
  goto code_r0x011d23a0;
  while (plVar4 = plVar5, plVar5 != plVar3) {
code_r0x01f6d0d4:
    plVar5 = plVar4 + -3;
    *(long **)(param_1 + 0x10) = plVar5;
    lVar1 = plVar4[-3];
    if (lVar1 != 0) {
      lVar2 = plVar4[-2];
      plVar3 = (long *)lVar1;
      if (lVar2 != lVar1) {
        do {
          plVar4[-2] = lVar2 + -0x10;
          Framework::CCSV::tElement::Delete()();
          lVar2 = plVar4[-2];
        } while (lVar2 != lVar1);
        plVar3 = (long *)*plVar5;
      }
      goto code_r0x011d23a0;
    }
  }
  plVar3 = *(long **)(param_1 + 8);
code_r0x011d23a0:
  (*(code *)PTR__ZN9Framework37CAssignedMemoryManagerForSTLAllocator4FreeEPv_02ca11c0)(plVar3);
  return;
}

// ==== Framework::CCSV::Release()
// vaddr 0x1e6d14c | ghidra 0x1f6d14c | size 128 | symbol _ZN9Framework4CCSV7ReleaseEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework4CCSV7ReleaseEv(undefined1 *param_1)

{
  long *plVar1;
  long *plVar2;
  long lVar3;
  long lVar4;
  long *plVar5;
  
  plVar1 = *(long **)(param_1 + 8);
  plVar5 = *(long **)(param_1 + 0x10);
  while (plVar2 = plVar5, plVar2 != plVar1) {
    plVar5 = plVar2 + -3;
    *(long **)(param_1 + 0x10) = plVar5;
    lVar4 = plVar2[-3];
    if (lVar4 != 0) {
      lVar3 = plVar2[-2];
      if (lVar3 != lVar4) {
        do {
          plVar2[-2] = lVar3 + -0x10;
          Framework::CCSV::tElement::Delete()();
          lVar3 = plVar2[-2];
        } while (lVar3 != lVar4);
        lVar4 = *plVar5;
      }
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(lVar4);
      plVar5 = *(long **)(param_1 + 0x10);
    }
  }
  *param_1 = 0;
  return;
}

// ==== Framework::CCSV::Initialize()
// vaddr 0x1e6d1cc | ghidra 0x1f6d1cc | size 128 | symbol _ZN9Framework4CCSV10InitializeEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework4CCSV10InitializeEv(undefined1 *param_1)

{
  long *plVar1;
  long *plVar2;
  long lVar3;
  long lVar4;
  long *plVar5;
  
  plVar1 = *(long **)(param_1 + 8);
  plVar5 = *(long **)(param_1 + 0x10);
  while (plVar2 = plVar5, plVar2 != plVar1) {
    plVar5 = plVar2 + -3;
    *(long **)(param_1 + 0x10) = plVar5;
    lVar4 = plVar2[-3];
    if (lVar4 != 0) {
      lVar3 = plVar2[-2];
      if (lVar3 != lVar4) {
        do {
          plVar2[-2] = lVar3 + -0x10;
          Framework::CCSV::tElement::Delete()();
          lVar3 = plVar2[-2];
        } while (lVar3 != lVar4);
        lVar4 = *plVar5;
      }
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(lVar4);
      plVar5 = *(long **)(param_1 + 0x10);
    }
  }
  *param_1 = 0;
  return;
}

// ==== Framework::CCSV::IsParsed() const
// vaddr 0x1e6d24c | ghidra 0x1f6d24c | size 8 | symbol _ZNK9Framework4CCSV8IsParsedEv | lib libSOA-3.7.0.so | 2026-10-04
undefined1 _ZNK9Framework4CCSV8IsParsedEv(undefined1 *param_1)

{
  return *param_1;
}

// ==== Framework::CCSV::Separator(char)
// vaddr 0x1e6d254 | ghidra 0x1f6d254 | size 64 | symbol _ZN9Framework4CCSV9SeparatorEc | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework4CCSV9SeparatorEc(long param_1,char param_2)

{
  if (param_2 == '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02962238/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\CSV.cpp"*/,0x144,&UNK_029622c4/*"aValue is null."*/);
  }
  *(char *)(param_1 + 2) = param_2;
  return;
}

// ==== Framework::CCSV::Quote(char)
// vaddr 0x1e6d294 | ghidra 0x1f6d294 | size 64 | symbol _ZN9Framework4CCSV5QuoteEc | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework4CCSV5QuoteEc(long param_1,char param_2)

{
  if (param_2 == '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02962238/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\CSV.cpp"*/,0x14b,&UNK_029622c4/*"aValue is null."*/);
  }
  *(char *)(param_1 + 3) = param_2;
  return;
}

// ==== Framework::CCSV::Parse(char const*, bool)
// vaddr 0x1e6d2d4 | ghidra 0x1f6d2d4 | size 88 | symbol _ZN9Framework4CCSV5ParseEPKcb | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN9Framework4CCSV5ParseEPKcb(char *param_1,undefined8 param_2,uint param_3)

{
  if (*param_1 != '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02962238/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\CSV.cpp"*/,0x156,&UNK_029622d4/*"m_IsParsed isn't null.(%08x)"*/);
  }
  param_1[0x30] = '\0';
  param_1[0x31] = '\0';
  param_1[0x32] = '\0';
  param_1[0x33] = '\0';
  param_1[0x34] = '\0';
  param_1[0x35] = '\0';
  param_1[0x36] = '\0';
  param_1[0x37] = '\0';
  Framework::CCSV::AddParse(char const*, bool)(param_1,param_2,param_3 & 1);
  return 1;
}

// ==== Framework::CCSV::AddParse(char const*, bool)
// vaddr 0x1e6d32c | ghidra 0x1f6d32c | size 1840 | symbol _ZN9Framework4CCSV8AddParseEPKcb | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Restarted to delay deadcode elimination for space: stack */

undefined8 _ZN9Framework4CCSV8AddParseEPKcb(undefined1 *param_1,char *param_2,uint param_3)

{
  undefined1 *puVar1;
  char cVar2;
  bool bVar3;
  long lVar4;
  undefined1 *puVar5;
  undefined8 *puVar6;
  long lVar7;
  int iVar8;
  ulong uVar9;
  char *pcVar10;
  long *plVar11;
  long *plVar12;
  long *plVar13;
  undefined1 *puVar14;
  char cVar15;
  ulong uVar16;
  ulong uVar17;
  undefined1 *puVar18;
  ulong uStack_78;
  ulong uStack_70;
  undefined1 *puStack_68;
  
  uStack_70 = 0;
  puStack_68 = (undefined1 *)0x0;
  uStack_78 = 0;
  string::reserve(unsigned long)(&uStack_78,0x100);
  lVar4 = strlen(param_2);
  puVar1 = param_1 + 8;
  std::__ndk1::vector<Framework::CSTLVector<Framework::CCSV::tElement>, Framework::CSTLAllocator<Framework::CSTLVector<Framework::CCSV::tElement>, Framework::CSTLVectorAllocatorInf> >::reserve(unsigned long)(puVar1,lVar4 << 1);
  puVar6 = *(undefined8 **)(param_1 + 0x10);
  if (puVar6 < *(undefined8 **)(param_1 + 0x18)) {
    puVar6[1] = 0;
    puVar6[2] = 0;
    *puVar6 = 0;
    lVar4 = *(long *)(param_1 + 0x10) + 0x18;
    *(long *)(param_1 + 0x10) = lVar4;
  }
  else {
    void std::__ndk1::vector<Framework::CSTLVector<Framework::CCSV::tElement>, Framework::CSTLAllocator<Framework::CSTLVector<Framework::CCSV::tElement>, Framework::CSTLVectorAllocatorInf> >::__emplace_back_slow_path<>()(puVar1);
    lVar4 = *(long *)(param_1 + 0x10);
  }
  iVar8 = 0;
  pcVar10 = param_2;
  while (cVar15 = *pcVar10, cVar15 != '\0') {
    if (cVar15 == param_1[2]) {
      iVar8 = iVar8 + 1;
    }
    if ((cVar15 == '\r') || (pcVar10 = pcVar10 + 1, cVar15 == '\n')) break;
  }
  std::__ndk1::vector<Framework::CCSV::tElement, Framework::CSTLAllocator<Framework::CCSV::tElement, Framework::CSTLVectorAllocatorInf> >::reserve(unsigned long)(lVar4 + -0x18,(long)iVar8);
  cVar15 = *param_2;
  if (cVar15 != '\0') {
    bVar3 = false;
    puVar18 = (undefined1 *)((ulong)&uStack_78 | 1);
code_r0x01f6d408:
    do {
      cVar2 = param_1[3];
      pcVar10 = param_2;
      while( true ) {
        param_2 = pcVar10 + 1;
        if (cVar15 != cVar2) break;
        cVar15 = *param_2;
        if (cVar15 == cVar2) {
          if ((uStack_78 & 1) == 0) {
            uVar16 = (ulong)((byte)uStack_78 >> 1);
            uVar9 = uStack_78 & 0xff;
            uVar17 = 0x16;
          }
          else {
            uVar17 = (uStack_78 & 0xfffffffffffffffe) - 1;
            uVar9 = uStack_78;
            uVar16 = uStack_70;
          }
          param_2 = pcVar10 + 2;
          if (uVar16 == uVar17) {
            puVar14 = puVar18;
            if ((uVar9 & 1) != 0) {
              puVar14 = puStack_68;
            }
            if (uVar17 < 0x7fffffffffffffe7) {
              uVar9 = uVar17 << 1;
              if (uVar9 <= uVar17 + 1) {
                uVar9 = uVar17 + 1;
              }
              if (uVar9 < 0x17) {
                uVar9 = 0x17;
              }
              else {
                uVar9 = uVar9 + 0x10 & 0xfffffffffffffff0;
                if (uVar9 == 0) {
                  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296188c/*"C:\BAS_Submission\Client\Library\Framework\Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
                }
              }
            }
            else {
              uVar9 = 0xffffffffffffffef;
            }
            puVar5 = (undefined1 *)Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar9,&UNK_029618d8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/STL_String.h"*/,0x1c);
            if (puVar5 == (undefined1 *)0x0) {
              Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296188c/*"C:\BAS_Submission\Client\Library\Framework\Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
            }
            memcpy(puVar5,puVar14,uVar17);
            if (uVar17 != 0x16) {
              Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puVar14);
            }
            uStack_78 = uVar9 | 1;
            puStack_68 = puVar5;
code_r0x01f6d74c:
            uStack_70 = uVar16 + 1;
            puVar14 = puStack_68;
          }
          else {
            if ((uStack_78 & 1) != 0) goto code_r0x01f6d74c;
            uStack_78 = CONCAT71(uStack_78._1_7_,(char)uVar16 * '\x02' + '\x02');
            puVar14 = puVar18;
          }
          puVar14[uVar16] = cVar2;
          (puVar14 + uVar16)[1] = '\0';
          cVar15 = *param_2;
          goto joined_r0x01f6d840;
        }
        bVar3 = (bool)(bVar3 ^ 1);
        pcVar10 = param_2;
        if (cVar15 == '\0') goto code_r0x01f6d990;
      }
      if (bVar3) {
        if ((uStack_78 & 1) == 0) {
          uVar16 = (ulong)((byte)uStack_78 >> 1);
          uVar9 = uStack_78 & 0xff;
          uVar17 = 0x16;
          if (uVar16 == 0x16) goto code_r0x01f6d524;
code_r0x01f6d458:
          if ((uStack_78 & 1) != 0) goto code_r0x01f6d824;
          uStack_78 = CONCAT71(uStack_78._1_7_,(char)uVar16 * '\x02' + '\x02');
          puVar14 = puVar18;
        }
        else {
          uVar17 = (uStack_78 & 0xfffffffffffffffe) - 1;
          uVar9 = uStack_78;
          uVar16 = uStack_70;
          if (uStack_70 != uVar17) goto code_r0x01f6d458;
code_r0x01f6d524:
          puVar14 = puVar18;
          if ((uVar9 & 1) != 0) {
            puVar14 = puStack_68;
          }
          if (uVar17 < 0x7fffffffffffffe7) {
            uVar9 = uVar17 << 1;
            if (uVar9 <= uVar17 + 1) {
              uVar9 = uVar17 + 1;
            }
            if (uVar9 < 0x17) {
              uVar9 = 0x17;
            }
            else {
              uVar9 = uVar9 + 0x10 & 0xfffffffffffffff0;
              if (uVar9 == 0) {
                Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296188c/*"C:\BAS_Submission\Client\Library\Framework\Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
              }
            }
          }
          else {
            uVar9 = 0xffffffffffffffef;
          }
          puVar5 = (undefined1 *)Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar9,&UNK_029618d8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/STL_String.h"*/,0x1c);
          if (puVar5 == (undefined1 *)0x0) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296188c/*"C:\BAS_Submission\Client\Library\Framework\Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
          }
          memcpy(puVar5,puVar14,uVar17);
          if (uVar17 != 0x16) {
            Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puVar14);
          }
          uStack_78 = uVar9 | 1;
          puStack_68 = puVar5;
code_r0x01f6d824:
          uStack_70 = uVar16 + 1;
          puVar14 = puStack_68;
        }
        puVar14[uVar16] = cVar15;
        (puVar14 + uVar16)[1] = '\0';
        bVar3 = true;
        cVar15 = *param_2;
joined_r0x01f6d840:
        if (cVar15 == '\0') break;
        goto code_r0x01f6d408;
      }
      if (cVar15 == '\r') {
        if (*param_2 == '\n') {
code_r0x01f6d594:
          param_2 = pcVar10 + 2;
        }
code_r0x01f6d59c:
        Framework::CCSV::AddElementAtLast(string const&, bool)(param_1,&uStack_78,param_3 & 1);
        if ((uStack_78 & 1) == 0) {
          uStack_78 = uStack_78 & 0xffffffffffff0000;
        }
        else {
          *puStack_68 = 0;
          uStack_70 = 0;
        }
        puVar6 = *(undefined8 **)(param_1 + 0x10);
        uVar9 = (long)(puVar6[-2] - puVar6[-3]) >> 4;
        if (*(ulong *)(param_1 + 0x30) < uVar9) {
          *(ulong *)(param_1 + 0x30) = uVar9;
        }
        if (puVar6 < *(undefined8 **)(param_1 + 0x18)) {
          puVar6[1] = 0;
          puVar6[2] = 0;
          *puVar6 = 0;
          lVar4 = *(long *)(param_1 + 0x10) + 0x18;
          *(long *)(param_1 + 0x10) = lVar4;
        }
        else {
          void std::__ndk1::vector<Framework::CSTLVector<Framework::CCSV::tElement>, Framework::CSTLAllocator<Framework::CSTLVector<Framework::CCSV::tElement>, Framework::CSTLVectorAllocatorInf> >::__emplace_back_slow_path<>()(puVar1);
          lVar4 = *(long *)(param_1 + 0x10);
        }
        iVar8 = 0;
        pcVar10 = param_2;
        while (cVar15 = *pcVar10, cVar15 != '\0') {
          if (cVar15 == param_1[2]) {
            iVar8 = iVar8 + 1;
          }
          if ((cVar15 == '\r') || (pcVar10 = pcVar10 + 1, cVar15 == '\n')) break;
        }
        std::__ndk1::vector<Framework::CCSV::tElement, Framework::CSTLAllocator<Framework::CCSV::tElement, Framework::CSTLVectorAllocatorInf> >::reserve(unsigned long)(lVar4 + -0x18,(long)iVar8);
code_r0x01f6d690:
        bVar3 = false;
        cVar15 = *param_2;
        goto joined_r0x01f6d840;
      }
      if (cVar15 == '\n') {
        if (*param_2 == '\r') goto code_r0x01f6d594;
        goto code_r0x01f6d59c;
      }
      if (cVar15 == param_1[2]) {
        Framework::CCSV::AddElementAtLast(string const&, bool)(param_1,&uStack_78,param_3 & 1);
        if ((uStack_78 & 1) == 0) {
          uStack_78 = uStack_78 & 0xffffffffffff0000;
        }
        else {
          *puStack_68 = 0;
          uStack_70 = 0;
        }
        goto code_r0x01f6d690;
      }
      if ((uStack_78 & 1) == 0) {
        uVar16 = (ulong)((byte)uStack_78 >> 1);
        uVar9 = uStack_78 & 0xff;
        uVar17 = 0x16;
        if (uVar16 == 0x16) goto code_r0x01f6d870;
code_r0x01f6d788:
        if ((uStack_78 & 1) != 0) goto code_r0x01f6d964;
        uStack_78 = CONCAT71(uStack_78._1_7_,(char)uVar16 * '\x02' + '\x02');
        puVar14 = puVar18;
      }
      else {
        uVar17 = (uStack_78 & 0xfffffffffffffffe) - 1;
        uVar9 = uStack_78;
        uVar16 = uStack_70;
        if (uStack_70 != uVar17) goto code_r0x01f6d788;
code_r0x01f6d870:
        puVar14 = puVar18;
        if ((uVar9 & 1) != 0) {
          puVar14 = puStack_68;
        }
        if (uVar17 < 0x7fffffffffffffe7) {
          uVar9 = uVar17 << 1;
          if (uVar9 <= uVar17 + 1) {
            uVar9 = uVar17 + 1;
          }
          if (uVar9 < 0x17) {
            uVar9 = 0x17;
          }
          else {
            uVar9 = uVar9 + 0x10 & 0xfffffffffffffff0;
            if (uVar9 == 0) {
              Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296188c/*"C:\BAS_Submission\Client\Library\Framework\Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
            }
          }
        }
        else {
          uVar9 = 0xffffffffffffffef;
        }
        puVar5 = (undefined1 *)Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar9,&UNK_029618d8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/STL_String.h"*/,0x1c);
        if (puVar5 == (undefined1 *)0x0) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296188c/*"C:\BAS_Submission\Client\Library\Framework\Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
        }
        memcpy(puVar5,puVar14,uVar17);
        if (uVar17 != 0x16) {
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puVar14);
        }
        uStack_78 = uVar9 | 1;
        puStack_68 = puVar5;
code_r0x01f6d964:
        uStack_70 = uVar16 + 1;
        puVar14 = puStack_68;
      }
      bVar3 = false;
      puVar14[uVar16] = cVar15;
      (puVar14 + uVar16)[1] = '\0';
      cVar15 = *param_2;
    } while (cVar15 != '\0');
  }
code_r0x01f6d990:
  uVar9 = uStack_78 >> 1 & 0x7f;
  if ((uStack_78 & 1) != 0) {
    uVar9 = uStack_70;
  }
  if (uVar9 != 0) {
    Framework::CCSV::AddElementAtLast(string const&, bool)(param_1,&uStack_78,param_3 & 1);
  }
  plVar12 = *(long **)(param_1 + 0x10);
  plVar11 = plVar12 + -3;
  if (*plVar11 == plVar12[-2]) {
    do {
      plVar13 = plVar12 + -3;
      *(long **)(param_1 + 0x10) = plVar13;
      lVar4 = plVar12[-3];
      if (lVar4 != 0) {
        lVar7 = plVar12[-2];
        if (lVar7 != lVar4) {
          do {
            plVar12[-2] = lVar7 + -0x10;
            Framework::CCSV::tElement::Delete()();
            lVar7 = plVar12[-2];
          } while (lVar7 != lVar4);
          lVar4 = *plVar13;
        }
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(lVar4);
        plVar13 = *(long **)(param_1 + 0x10);
      }
      plVar12 = plVar13;
    } while (plVar12 != plVar11);
  }
  *param_1 = 1;
  if ((uStack_78 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puStack_68);
  }
  return 1;
}

// ==== Framework::CCSV::AddElementAtLast(std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > const&, bool)
// vaddr 0x1e6dd34 | ghidra 0x1f6dd34 | size 220 | symbol _ZN9Framework4CCSV16AddElementAtLastERKNSt6__ndk112basic_stringIcNS1_11char_traitsIcEENS_13CSTLAllocatorIcNS_22CSTLStringAllocatorInfEEEEEb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework4CCSV16AddElementAtLastERKNSt6__ndk112basic_stringIcNS1_11char_traitsIcEENS_13CSTLAllocatorIcNS_22CSTLStringAllocatorInfEEEEEb
               (long param_1,byte *param_2,ulong param_3)

{
  undefined4 *puVar1;
  ulong uVar2;
  long lVar3;
  long lVar4;
  undefined8 uStack_28;
  
  lVar4 = *(long *)(param_1 + 0x10);
  uVar2 = (ulong)(*param_2 >> 1);
  if ((*param_2 & 1) != 0) {
    uVar2 = *(ulong *)(param_2 + 8);
  }
  lVar3 = lVar4 + -0x18;
  if (uVar2 == 0) {
    if (*(undefined4 **)(lVar4 + -8) <= *(undefined4 **)(lVar4 + -0x10)) {
      void std::__ndk1::vector<Framework::CCSV::tElement, Framework::CSTLAllocator<Framework::CCSV::tElement, Framework::CSTLVectorAllocatorInf> >::__emplace_back_slow_path<>()(lVar3);
      return;
    }
    **(undefined4 **)(lVar4 + -0x10) = 0;
  }
  else if (((param_3 & 1) == 0) &&
          (uVar2 = Framework::CSTLStringUtility_Base<string >::IsDigits(string const&, bool, float*, double*)(param_2,1,0,&uStack_28), (uVar2 & 1) != 0)) {
    puVar1 = *(undefined4 **)(lVar4 + -0x10);
    if (*(undefined4 **)(lVar4 + -8) <= puVar1) {
      void std::__ndk1::vector<Framework::CCSV::tElement, Framework::CSTLAllocator<Framework::CCSV::tElement, Framework::CSTLVectorAllocatorInf> >::__emplace_back_slow_path<double&>(double&)(lVar3,&uStack_28);
      return;
    }
    *puVar1 = 1;
    *(undefined8 *)(puVar1 + 2) = uStack_28;
  }
  else {
    if (*(ulong *)(lVar4 + -8) <= *(ulong *)(lVar4 + -0x10)) {
      void std::__ndk1::vector<Framework::CCSV::tElement, Framework::CSTLAllocator<Framework::CCSV::tElement, Framework::CSTLVectorAllocatorInf> >::__emplace_back_slow_path<string const&>(string const&)(lVar3,param_2);
      return;
    }
    Framework::CCSV::tElement::tElement(string const&)(*(ulong *)(lVar4 + -0x10),param_2);
  }
  *(long *)(lVar4 + -0x10) = *(long *)(lVar4 + -0x10) + 0x10;
  return;
}

// ==== Framework::CCSV::ParseSingleLine(char const*, char const**, bool)
// vaddr 0x1e6de10 | ghidra 0x1f6de10 | size 604 | symbol _ZN9Framework4CCSV15ParseSingleLineEPKcPS2_b | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN9Framework4CCSV15ParseSingleLineEPKcPS2_b
          (char *param_1,char *param_2,undefined8 *param_3,uint param_4)

{
  ulong uVar1;
  ulong uVar2;
  ulong uVar3;
  char cVar4;
  ulong uVar5;
  ulong uVar6;
  ulong uVar7;
  ulong uStack_78;
  ulong uStack_70;
  ulong uStack_68;
  
  uVar5 = (ulong)&uStack_78 | 1;
  uStack_78 = 0;
  uStack_70 = 0;
  uStack_68 = 0;
  cVar4 = *param_2;
  while (cVar4 != '\0') {
    if ((cVar4 == '\r') || (cVar4 == '\n')) goto code_r0x01f6dfa4;
    if ((uStack_78 & 1) == 0) {
      uVar6 = uStack_78 >> 1 & 0x7f;
      uVar3 = uStack_78 & 0xff;
      uVar7 = 0x16;
    }
    else {
      uVar7 = (uStack_78 & 0xfffffffffffffffe) - 1;
      uVar3 = uStack_78;
      uVar6 = uStack_70;
    }
    param_2 = param_2 + 1;
    if (uVar6 == uVar7) {
      uVar1 = uVar5;
      if ((uVar3 & 1) != 0) {
        uVar1 = uStack_68;
      }
      if (uVar7 < 0x7fffffffffffffe7) {
        uVar3 = uVar7 << 1;
        if (uVar3 <= uVar7 + 1) {
          uVar3 = uVar7 + 1;
        }
        if (uVar3 < 0x17) {
          uVar3 = 0x17;
        }
        else {
          uVar3 = uVar3 + 0x10 & 0xfffffffffffffff0;
          if (uVar3 == 0) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296188c/*"C:\BAS_Submission\Client\Library\Framework\Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
          }
        }
      }
      else {
        uVar3 = 0xffffffffffffffef;
      }
      uVar2 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar3,&UNK_029618d8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/STL_String.h"*/,0x1c);
      if (uVar2 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296188c/*"C:\BAS_Submission\Client\Library\Framework\Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
      }
      memcpy(uVar2,uVar1,uVar7);
      if (uVar7 != 0x16) {
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uVar1);
      }
      uStack_78 = uVar3 | 1;
      uStack_68 = uVar2;
code_r0x01f6df94:
      uStack_70 = uVar6 + 1;
      uVar3 = uStack_68;
    }
    else {
      if ((uStack_78 & 1) != 0) goto code_r0x01f6df94;
      uVar3 = uStack_78 >> 8;
      uStack_78 = CONCAT71((int7)uVar3,(char)uVar6 * '\x02' + '\x02');
      uVar3 = uVar5;
    }
    *(char *)(uVar3 + uVar6) = cVar4;
    ((char *)(uVar3 + uVar6))[1] = '\0';
    cVar4 = *param_2;
  }
code_r0x01f6dfb8:
  uVar3 = uStack_78 >> 1 & 0x7f;
  if ((uStack_78 & 1) != 0) {
    uVar3 = uStack_70;
  }
  if (uVar3 == 0) {
    *param_3 = 0;
  }
  else {
    if (cVar4 == '\0') {
      param_2 = (char *)0x0;
    }
    *param_3 = param_2;
    if ((uStack_78 & 1) != 0) {
      uVar5 = uStack_68;
    }
    if (*param_1 != '\0') {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02962238/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\CSV.cpp"*/,0x156,&UNK_029622d4/*"m_IsParsed isn't null.(%08x)"*/);
    }
    param_1[0x30] = '\0';
    param_1[0x31] = '\0';
    param_1[0x32] = '\0';
    param_1[0x33] = '\0';
    param_1[0x34] = '\0';
    param_1[0x35] = '\0';
    param_1[0x36] = '\0';
    param_1[0x37] = '\0';
    Framework::CCSV::AddParse(char const*, bool)(param_1,uVar5,param_4 & 1);
  }
  if ((uStack_78 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_68);
  }
  return 1;
code_r0x01f6dfa4:
  while ((cVar4 == '\r' || (cVar4 == '\n'))) {
    param_2 = param_2 + 1;
    cVar4 = *param_2;
  }
  goto code_r0x01f6dfb8;
}

// ==== Framework::CCSV::NumRows() const
// vaddr 0x1e6e06c | ghidra 0x1f6e06c | size 72 | symbol _ZNK9Framework4CCSV7NumRowsEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK9Framework4CCSV7NumRowsEv(char *param_1)

{
  if (*param_1 == '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02962238/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\CSV.cpp"*/,0x236,&UNK_029622f1/*"m_IsParsed is null."*/);
  }
  return (*(long *)(param_1 + 0x10) - *(long *)(param_1 + 8) >> 3) * -0x5555555555555555;
}

// ==== Framework::CCSV::MaxElements() const
// vaddr 0x1e6e0b4 | ghidra 0x1f6e0b4 | size 52 | symbol _ZNK9Framework4CCSV11MaxElementsEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK9Framework4CCSV11MaxElementsEv(char *param_1)

{
  if (*param_1 == '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02962238/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\CSV.cpp"*/,0x23d,&UNK_029622f1/*"m_IsParsed is null."*/);
  }
  return *(undefined8 *)(param_1 + 0x30);
}

// ==== Framework::CCSV::NumElements(unsigned long) const
// vaddr 0x1e6e0e8 | ghidra 0x1f6e0e8 | size 240 | symbol _ZNK9Framework4CCSV11NumElementsEm | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK9Framework4CCSV11NumElementsEm(char *param_1,ulong param_2)

{
  long lVar1;
  long *plVar2;
  long lVar3;
  ulong uVar4;
  
  if (*param_1 == '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02962238/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\CSV.cpp"*/,0x245,&UNK_029622f1/*"m_IsParsed is null."*/);
    if (*param_1 == '\0') {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02962238/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\CSV.cpp"*/,0x236,&UNK_029622f1/*"m_IsParsed is null."*/);
    }
  }
  lVar1 = *(long *)(param_1 + 8);
  lVar3 = *(long *)(param_1 + 0x10);
  uVar4 = (lVar3 - lVar1 >> 3) * -0x5555555555555555;
  if (uVar4 < param_2 || uVar4 - param_2 == 0) {
    if (*param_1 == '\0') {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02962238/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\CSV.cpp"*/,0x236,&UNK_029622f1/*"m_IsParsed is null."*/);
      lVar1 = *(long *)(param_1 + 8);
      lVar3 = *(long *)(param_1 + 0x10);
    }
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02962238/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\CSV.cpp"*/,0x246,&UNK_02962305/*"Required CSV element out of range.(%d/%d)[%s]"*/,param_2,
                    (lVar3 - lVar1 >> 3) * -0x5555555555555555,&UNK_02962333/*"NoDebugTag"*/);
    lVar1 = *(long *)(param_1 + 8);
  }
  plVar2 = (long *)(lVar1 + param_2 * 0x18);
  return plVar2[1] - *plVar2 >> 4;
}

// ==== Framework::CCSV::NumElementsSafe(unsigned long) const
// vaddr 0x1e6e1d8 | ghidra 0x1f6e1d8 | size 152 | symbol _ZNK9Framework4CCSV15NumElementsSafeEm | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK9Framework4CCSV15NumElementsSafeEm(char *param_1,ulong param_2)

{
  long lVar1;
  long *plVar2;
  ulong uVar3;
  
  if (*param_1 == '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02962238/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\CSV.cpp"*/,0x24f,&UNK_029622f1/*"m_IsParsed is null."*/);
    if (*param_1 == '\0') {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02962238/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\CSV.cpp"*/,0x236,&UNK_029622f1/*"m_IsParsed is null."*/);
    }
  }
  uVar3 = (*(long *)(param_1 + 0x10) - *(long *)(param_1 + 8) >> 3) * -0x5555555555555555;
  if (uVar3 < param_2 || uVar3 - param_2 == 0) {
    lVar1 = 0;
  }
  else {
    plVar2 = (long *)(*(long *)(param_1 + 8) + param_2 * 0x18);
    lVar1 = plVar2[1] - *plVar2 >> 4;
  }
  return lVar1;
}

// ==== Framework::CCSV::Element(unsigned long, unsigned long) const
// vaddr 0x1e6e270 | ghidra 0x1f6e270 | size 312 | symbol _ZNK9Framework4CCSV7ElementEmm | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK9Framework4CCSV7ElementEmm(char *param_1,ulong param_2,ulong param_3)

{
  undefined8 uVar1;
  long lVar2;
  long lVar3;
  ulong uVar4;
  
  if (*param_1 == '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02962238/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\CSV.cpp"*/,0x25a,&UNK_029622f1/*"m_IsParsed is null."*/);
    if (*param_1 == '\0') {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02962238/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\CSV.cpp"*/,0x236,&UNK_029622f1/*"m_IsParsed is null."*/);
    }
  }
  lVar2 = *(long *)(param_1 + 8);
  lVar3 = *(long *)(param_1 + 0x10);
  uVar4 = (lVar3 - lVar2 >> 3) * -0x5555555555555555;
  if (uVar4 < param_2 || uVar4 - param_2 == 0) {
    if (*param_1 == '\0') {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02962238/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\CSV.cpp"*/,0x236,&UNK_029622f1/*"m_IsParsed is null."*/);
      lVar2 = *(long *)(param_1 + 8);
      lVar3 = *(long *)(param_1 + 0x10);
    }
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02962238/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\CSV.cpp"*/,0x25b,&UNK_02962305/*"Required CSV element out of range.(%d/%d)[%s]"*/,param_2,
                    (lVar3 - lVar2 >> 3) * -0x5555555555555555,&UNK_02962333/*"NoDebugTag"*/);
  }
  uVar4 = Framework::CCSV::NumElements(unsigned long) const(param_1,param_2);
  if (uVar4 <= param_3) {
    uVar1 = Framework::CCSV::NumElements(unsigned long) const(param_1,param_2);
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02962238/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\CSV.cpp"*/,0x25c,&UNK_02962305/*"Required CSV element out of range.(%d/%d)[%s]"*/,param_3,uVar1,&UNK_02962333/*"NoDebugTag"*/);
  }
  return *(long *)(*(long *)(param_1 + 8) + param_2 * 0x18) + param_3 * 0x10;
}

// ==== Framework::CCSV::rElement(unsigned long, unsigned long)
// vaddr 0x1e6e3a8 | ghidra 0x1f6e3a8 | size 312 | symbol _ZN9Framework4CCSV8rElementEmm | lib libSOA-3.7.0.so | 2026-10-04
long _ZN9Framework4CCSV8rElementEmm(char *param_1,ulong param_2,ulong param_3)

{
  undefined8 uVar1;
  long lVar2;
  long lVar3;
  ulong uVar4;
  
  if (*param_1 == '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02962238/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\CSV.cpp"*/,0x265,&UNK_029622f1/*"m_IsParsed is null."*/);
    if (*param_1 == '\0') {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02962238/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\CSV.cpp"*/,0x236,&UNK_029622f1/*"m_IsParsed is null."*/);
    }
  }
  lVar2 = *(long *)(param_1 + 8);
  lVar3 = *(long *)(param_1 + 0x10);
  uVar4 = (lVar3 - lVar2 >> 3) * -0x5555555555555555;
  if (uVar4 < param_2 || uVar4 - param_2 == 0) {
    if (*param_1 == '\0') {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02962238/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\CSV.cpp"*/,0x236,&UNK_029622f1/*"m_IsParsed is null."*/);
      lVar2 = *(long *)(param_1 + 8);
      lVar3 = *(long *)(param_1 + 0x10);
    }
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02962238/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\CSV.cpp"*/,0x266,&UNK_02962305/*"Required CSV element out of range.(%d/%d)[%s]"*/,param_2,
                    (lVar3 - lVar2 >> 3) * -0x5555555555555555,&UNK_02962333/*"NoDebugTag"*/);
  }
  uVar4 = Framework::CCSV::NumElements(unsigned long) const(param_1,param_2);
  if (uVar4 <= param_3) {
    uVar1 = Framework::CCSV::NumElements(unsigned long) const(param_1,param_2);
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02962238/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\CSV.cpp"*/,0x267,&UNK_02962305/*"Required CSV element out of range.(%d/%d)[%s]"*/,param_3,uVar1,&UNK_02962333/*"NoDebugTag"*/);
  }
  return *(long *)(*(long *)(param_1 + 8) + param_2 * 0x18) + param_3 * 0x10;
}

// ==== Framework::CCSV::ElementSafe(unsigned long, unsigned long) const
// vaddr 0x1e6e4e0 | ghidra 0x1f6e4e0 | size 176 | symbol _ZNK9Framework4CCSV11ElementSafeEmm | lib libSOA-3.7.0.so | 2026-10-04
char * _ZNK9Framework4CCSV11ElementSafeEmm(char *param_1,ulong param_2,ulong param_3)

{
  ulong uVar1;
  
  if (*param_1 == '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02962238/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\CSV.cpp"*/,0x271,&UNK_029622f1/*"m_IsParsed is null."*/);
    if (*param_1 == '\0') {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02962238/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\CSV.cpp"*/,0x236,&UNK_029622f1/*"m_IsParsed is null."*/);
    }
  }
  uVar1 = (*(long *)(param_1 + 0x10) - *(long *)(param_1 + 8) >> 3) * -0x5555555555555555;
  if ((uVar1 < param_2 || uVar1 - param_2 == 0) ||
     (uVar1 = Framework::CCSV::NumElements(unsigned long) const(param_1,param_2), uVar1 <= param_3)) {
    param_1 = param_1 + 0x20;
  }
  else {
    param_1 = (char *)(*(long *)(*(long *)(param_1 + 8) + param_2 * 0x18) + param_3 * 0x10);
  }
  return param_1;
}

// ==== Framework::CCSV::HasElement(unsigned long, unsigned long) const
// vaddr 0x1e6e590 | ghidra 0x1f6e590 | size 156 | symbol _ZNK9Framework4CCSV10HasElementEmm | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK9Framework4CCSV10HasElementEmm(char *param_1,ulong param_2,ulong param_3)

{
  bool bVar1;
  ulong uVar2;
  
  if (*param_1 == '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02962238/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\CSV.cpp"*/,0x27c,&UNK_029622f1/*"m_IsParsed is null."*/);
    if (*param_1 == '\0') {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02962238/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\CSV.cpp"*/,0x236,&UNK_029622f1/*"m_IsParsed is null."*/);
    }
  }
  uVar2 = (*(long *)(param_1 + 0x10) - *(long *)(param_1 + 8) >> 3) * -0x5555555555555555;
  if (uVar2 < param_2 || uVar2 - param_2 == 0) {
    bVar1 = false;
  }
  else {
    uVar2 = Framework::CCSV::NumElements(unsigned long) const(param_1,param_2);
    bVar1 = param_3 < uVar2;
  }
  return bVar1;
}

// ==== Framework::CCSV::Serialize() const
// vaddr 0x1e6e62c | ghidra 0x1f6e62c | size 720 | symbol _ZNK9Framework4CCSV9SerializeEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK9Framework4CCSV9SerializeEv(ulong *param_1,char *param_2)

{
  ulong uVar1;
  long lVar2;
  long lVar3;
  char cVar4;
  long lVar5;
  undefined8 uVar6;
  long lVar7;
  ulong uVar8;
  byte bVar9;
  ulong uVar10;
  ulong uVar11;
  ulong uVar12;
  long lVar13;
  ulong uVar14;
  ulong uVar15;
  undefined8 uStack_90;
  undefined8 uStack_88;
  undefined8 uStack_80;
  byte abStack_78 [8];
  ulong uStack_70;
  ulong uStack_68;
  
  param_1[1] = 0;
  param_1[2] = 0;
  *param_1 = 0;
  if (*param_2 == '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02962238/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\CSV.cpp"*/,0x236,&UNK_029622f1/*"m_IsParsed is null."*/);
  }
  lVar2 = *(long *)(param_2 + 8);
  lVar3 = *(long *)(param_2 + 0x10);
  if (lVar3 - lVar2 != 0) {
    uVar11 = 0;
    uVar1 = (long)param_1 + 1;
    do {
      lVar5 = Framework::CCSV::NumElements(unsigned long) const(param_2,uVar11);
      if (lVar5 != 0) {
        lVar13 = 0;
        do {
          uVar6 = Framework::CCSV::Element(unsigned long, unsigned long) const(param_2,uVar11,lVar13);
          uStack_88 = 0;
          uStack_80 = 0;
          uStack_90 = 0;
          Framework::CCSV::tElement::StringSafe(string const&) const(abStack_78,uVar6,&uStack_90);
          bVar9 = (byte)*param_1;
          uVar10 = (ulong)bVar9;
          uVar12 = (ulong)(abStack_78[0] >> 1);
          uVar8 = (ulong)abStack_78 | 1;
          if ((abStack_78[0] & 1) != 0) {
            uVar12 = uStack_70;
            uVar8 = uStack_68;
          }
          if ((bVar9 & 1) == 0) {
            lVar7 = 0x16;
            if ((bVar9 & 1) == 0) goto code_r0x01f6e738;
code_r0x01f6e720:
            uVar14 = param_1[1];
          }
          else {
            uVar10 = *param_1;
            lVar7 = (uVar10 & 0xfffffffffffffffe) - 1;
            if ((uVar10 & 1) != 0) goto code_r0x01f6e720;
code_r0x01f6e738:
            uVar14 = (ulong)(((uint)uVar10 & 0xfe) >> 1);
          }
          if (lVar7 - uVar14 < uVar12) {
            string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(param_1,lVar7,(uVar12 - lVar7) + uVar14,uVar14,uVar14,0,uVar12);
          }
          else if (uVar12 != 0) {
            uVar15 = uVar1;
            if ((uVar10 & 1) != 0) {
              uVar15 = param_1[2];
            }
            memcpy(uVar15 + uVar14,uVar8,uVar12);
            uVar14 = uVar14 + uVar12;
            if ((*param_1 & 1) == 0) {
              *(char *)param_1 = (char)uVar14 * '\x02';
              *(undefined1 *)(uVar15 + uVar14) = 0;
            }
            else {
              param_1[1] = uVar14;
              *(undefined1 *)(uVar15 + uVar14) = 0;
            }
          }
          if ((abStack_78[0] & 1) != 0) {
            Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_68);
          }
          bVar9 = (byte)*param_1;
          cVar4 = param_2[2];
          if ((bVar9 & 1) == 0) {
            uVar12 = (ulong)(bVar9 >> 1);
            uVar8 = 0x16;
            if (uVar12 == 0x16) goto code_r0x01f6e7f4;
          }
          else {
            uVar12 = param_1[1];
            uVar8 = (*param_1 & 0xfffffffffffffffe) - 1;
            if (uVar12 == uVar8) {
code_r0x01f6e7f4:
              string::__grow_by(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long)(param_1,uVar8,1,uVar8,uVar8,0,0);
              bVar9 = (byte)*param_1;
            }
          }
          if ((bVar9 & 1) == 0) {
            *(char *)param_1 = (char)uVar12 * '\x02' + '\x02';
            uVar8 = uVar1;
          }
          else {
            param_1[1] = uVar12 + 1;
            uVar8 = param_1[2];
          }
          lVar13 = lVar13 + 1;
          *(char *)(uVar8 + uVar12) = cVar4;
          ((char *)(uVar8 + uVar12))[1] = '\0';
        } while (lVar5 != lVar13);
      }
      bVar9 = (byte)*param_1;
      if ((bVar9 & 1) == 0) {
        uVar12 = (ulong)(bVar9 >> 1);
        uVar8 = 0x16;
        if (uVar12 == 0x16) goto code_r0x01f6e894;
code_r0x01f6e880:
        if ((bVar9 & 1) == 0) goto code_r0x01f6e8b8;
code_r0x01f6e884:
        uVar8 = param_1[2];
        param_1[1] = uVar12 + 1;
      }
      else {
        uVar12 = param_1[1];
        uVar8 = (*param_1 & 0xfffffffffffffffe) - 1;
        if (uVar12 != uVar8) goto code_r0x01f6e880;
code_r0x01f6e894:
        string::__grow_by(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long)(param_1,uVar8,1,uVar8,uVar8,0,0);
        if ((*param_1 & 1) != 0) goto code_r0x01f6e884;
code_r0x01f6e8b8:
        *(char *)param_1 = (char)uVar12 * '\x02' + '\x02';
        uVar8 = uVar1;
      }
      uVar11 = uVar11 + 1;
      *(undefined2 *)(uVar8 + uVar12) = 10;
    } while (uVar11 < (ulong)((lVar3 - lVar2 >> 3) * -0x5555555555555555));
  }
  return;
}

// ==== Framework::CCSV::PrintC() const
// vaddr 0x1e6e8fc | ghidra 0x1f6e8fc | size 4 | symbol _ZNK9Framework4CCSV6PrintCEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK9Framework4CCSV6PrintCEv(void)

{
  return;
}

// ==== Framework::CCSV::gRegressionTest()
// vaddr 0x1e6e900 | ghidra 0x1f6e900 | size 4 | symbol _ZN9Framework4CCSV15gRegressionTestEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework4CCSV15gRegressionTestEv(void)

{
  return;
}

// ==== Framework::CACSV::CACSV()
// vaddr 0x1ece68c | ghidra 0x1fce68c | size 32 | symbol _ZN9Framework5CACSVC1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework5CACSVC2Ev(undefined1 *param_1)

{
  *param_1 = 0;
  Aska::ACSV::ACSV()(param_1 + 8);
  *(undefined8 *)(param_1 + 0xf0) = 0;
  return;
}

// ==== Framework::CACSV::~CACSV()
// vaddr 0x1ece6ac | ghidra 0x1fce6ac | size 44 | symbol _ZN9Framework5CACSVD2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework5CACSVD1Ev(undefined1 *param_1)

{
  Aska::ACSV::Term()(param_1 + 8);
  *param_1 = 0;
  (*(code *)PTR__ZN4Aska4ACSVD1Ev_02ca97b0)(param_1 + 8);
  return;
}

// ==== Framework::CACSV::Release()
// vaddr 0x1ece6d8 | ghidra 0x1fce6d8 | size 28 | symbol _ZN9Framework5CACSV7ReleaseEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework5CACSV7ReleaseEv(undefined1 *param_1)

{
  Aska::ACSV::Term()(param_1 + 8);
  *param_1 = 0;
  return;
}

// ==== Framework::CACSV::Initialize()
// vaddr 0x1ece6f4 | ghidra 0x1fce6f4 | size 28 | symbol _ZN9Framework5CACSV10InitializeEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework5CACSV10InitializeEv(undefined1 *param_1)

{
  Aska::ACSV::Term()(param_1 + 8);
  *param_1 = 0;
  return;
}

// ==== Framework::CACSV::IsParsed() const
// vaddr 0x1ece710 | ghidra 0x1fce710 | size 8 | symbol _ZNK9Framework5CACSV8IsParsedEv | lib libSOA-3.7.0.so | 2026-10-04
undefined1 _ZNK9Framework5CACSV8IsParsedEv(undefined1 *param_1)

{
  return *param_1;
}

// ==== Framework::CACSV::Parse(char const*)
// vaddr 0x1ece718 | ghidra 0x1fce718 | size 312 | symbol _ZN9Framework5CACSV5ParseEPKc | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework5CACSV5ParseEPKc(byte *param_1,char *param_2)

{
  bool bVar1;
  ulong uVar2;
  char cVar3;
  ulong uVar4;
  undefined8 uVar5;
  byte extraout_var;
  ulong uVar6;
  long lVar7;
  ulong uVar8;
  ulong uVar9;
  char *pcVar10;
  char *pcVar11;
  undefined1 auStack_28 [8];
  
  if (*param_1 != 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296a118/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ACSV.cpp"*/,0x35,&UNK_029622d4/*"m_IsParsed isn't null.(%08x)"*/);
  }
  lVar7 = 0;
  uVar6 = 0;
  uVar4 = 0;
  uVar9 = 0;
  pcVar10 = param_2;
code_r0x01fce7b8:
  uVar8 = uVar4;
  cVar3 = *pcVar10;
  if (cVar3 == '\"') {
    do {
      while( true ) {
        pcVar11 = pcVar10 + 1;
        cVar3 = *pcVar11;
        if (cVar3 == '\"') break;
        if ((cVar3 == '\0') || (pcVar10 = pcVar11, cVar3 == '\n')) goto joined_r0x01fce770;
      }
      pcVar10 = pcVar10 + 2;
      cVar3 = *pcVar10;
      pcVar11 = pcVar10;
    } while (cVar3 == '\"');
  }
  else {
    pcVar11 = pcVar10;
    if (cVar3 == '\0') {
      Aska::ACSV::Init(unsigned long, unsigned long, Aska::ACSV::Extension)(auStack_28,param_1 + 8,uVar6,lVar7 + 1,3);
      uVar5 = strlen(param_2);
      Aska::ACSV::DeserializeText(void const*, unsigned long)(param_1 + 8,param_2,uVar5);
      *param_1 = extraout_var >> 7 ^ 1;
      return;
    }
  }
joined_r0x01fce770:
  do {
    pcVar10 = pcVar11 + 1;
    if (cVar3 == '\0') break;
    if (cVar3 == '\n') {
      lVar7 = lVar7 + 1;
      uVar2 = uVar8;
      uVar4 = uVar8;
      if (uVar8 <= uVar9) {
        uVar2 = uVar9;
        uVar4 = uVar6;
      }
      uVar6 = uVar4;
      bVar1 = uVar8 <= uVar9;
      uVar4 = 0;
      uVar9 = uVar2;
      if (bVar1) {
        uVar4 = uVar8;
      }
      goto code_r0x01fce7b8;
    }
    if (cVar3 == ',') {
      uVar4 = uVar8 + 1;
      goto code_r0x01fce7b8;
    }
    cVar3 = *pcVar10;
    pcVar11 = pcVar10;
  } while( true );
  pcVar10 = pcVar10 + -1;
  uVar4 = uVar8;
  goto code_r0x01fce7b8;
}

// ==== Framework::CACSV::AnalyzeCsvTextElement(char const*, unsigned long&, unsigned long&)
// vaddr 0x1ece850 | ghidra 0x1fce850 | size 212 | symbol _ZN9Framework5CACSV21AnalyzeCsvTextElementEPKcRmS3_ | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN9Framework5CACSV21AnalyzeCsvTextElementEPKcRmS3_(char *param_1,long *param_2,ulong *param_3)

{
  long lVar1;
  ulong uVar2;
  ulong uVar3;
  ulong uVar4;
  char cVar5;
  char cVar6;
  char *pcVar7;
  char *pcVar8;
  
  uVar4 = 0;
  lVar1 = 0;
  *param_2 = 0;
  *param_3 = 0;
  uVar3 = 0;
  do {
    cVar6 = *param_1;
    pcVar7 = param_1;
    if (cVar6 == '\"') {
      do {
        while( true ) {
          param_1 = pcVar7 + 1;
          cVar6 = *param_1;
          if (cVar6 == '\"') break;
          if ((cVar6 == '\0') || (pcVar7 = param_1, cVar6 == '\n')) goto code_r0x01fce8e8;
        }
        param_1 = pcVar7 + 2;
        cVar6 = *param_1;
        pcVar7 = param_1;
      } while (cVar6 == '\"');
    }
    else if (cVar6 == '\0') {
      *param_2 = lVar1 + 1;
      return 1;
    }
code_r0x01fce8e8:
    cVar5 = '\0';
    uVar2 = uVar3;
    pcVar7 = param_1 + 1;
    if (cVar6 != '\0') {
      do {
        if (cVar6 == '\n') {
          lVar1 = lVar1 + 1;
          if (uVar4 < uVar3) {
            *param_3 = uVar3;
            cVar5 = pcVar7[-1];
            uVar2 = 0;
            uVar4 = uVar3;
          }
          else {
code_r0x01fce88c:
            cVar5 = ',';
            uVar2 = uVar3;
          }
          goto code_r0x01fce890;
        }
        if (cVar6 == ',') {
          uVar3 = uVar3 + 1;
          goto code_r0x01fce88c;
        }
        pcVar8 = pcVar7 + 1;
        cVar6 = *pcVar7;
        pcVar7 = pcVar8;
      } while (cVar6 != '\0');
      cVar5 = '\0';
    }
code_r0x01fce890:
    param_1 = pcVar7 + -1;
    uVar3 = uVar2;
    if (cVar5 != '\0') {
      param_1 = pcVar7;
    }
  } while( true );
}

// ==== Framework::CACSV::ParseBinary(void const*, unsigned long)
// vaddr 0x1ece924 | ghidra 0x1fce924 | size 188 | symbol _ZN9Framework5CACSV11ParseBinaryEPKvm | lib libSOA-3.7.0.so | 2026-10-04
uint _ZN9Framework5CACSV11ParseBinaryEPKvm(char *param_1,int *param_2,undefined8 param_3)

{
  uint uVar1;
  uint uVar2;
  uint extraout_var;
  undefined1 auStack_28 [8];
  
  if (*param_1 != '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296a118/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ACSV.cpp"*/,0x45,&UNK_029622d4/*"m_IsParsed isn't null.(%08x)"*/);
  }
  if ((((*param_2 == 0x41435356) && (param_2[4] == 0x10001)) && (uVar1 = param_2[5], uVar1 != 0)) &&
     (param_2[6] != 0)) {
    uVar2 = 0;
    if (uVar1 != 0) {
      uVar2 = (uint)param_2[6] / uVar1;
    }
    Aska::ACSV::Init(unsigned long, unsigned long, Aska::ACSV::Extension)(auStack_28,param_1 + 8,uVar1,uVar2 + 1,1);
    Aska::ACSV::DeserializeBinary(void const*, unsigned long)(param_1 + 8,param_2,param_3);
    uVar1 = extraout_var >> 0x1f ^ 1;
    *param_1 = (char)uVar1;
    return uVar1;
  }
  return 0;
}

// ==== Framework::CACSV::AnalyzeAcsvBinaryElement(void const*, unsigned long, unsigned long&, unsigned long&)
// vaddr 0x1ece9e0 | ghidra 0x1fce9e0 | size 112 | symbol _ZN9Framework5CACSV24AnalyzeAcsvBinaryElementEPKvmRmS3_ | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN9Framework5CACSV24AnalyzeAcsvBinaryElementEPKvmRmS3_
          (int *param_1,undefined8 param_2,ulong *param_3,ulong *param_4)

{
  uint uVar1;
  
  if (*param_1 != 0x41435356) {
    return 0;
  }
  if (param_1[4] != 0x10001) {
    return 0;
  }
  if (param_1[5] == 0) {
    return 0;
  }
  if (param_1[6] != 0) {
    *param_4 = (ulong)(uint)param_1[5];
    uVar1 = 0;
    if (param_1[5] != 0) {
      uVar1 = (uint)param_1[6] / (uint)param_1[5];
    }
    *param_3 = (ulong)(uVar1 + 1);
    return 1;
  }
  return 0;
}

// ==== Framework::CACSV::NumRows() const
// vaddr 0x1ecea50 | ghidra 0x1fcea50 | size 52 | symbol _ZNK9Framework5CACSV7NumRowsEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK9Framework5CACSV7NumRowsEv(char *param_1)

{
  if (*param_1 == '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296a118/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ACSV.cpp"*/,0x5f,&UNK_029622f1/*"m_IsParsed is null."*/);
  }
  return *(undefined8 *)(param_1 + 0x50);
}

// ==== Framework::CACSV::NumColumns() const
// vaddr 0x1ecea84 | ghidra 0x1fcea84 | size 52 | symbol _ZNK9Framework5CACSV10NumColumnsEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK9Framework5CACSV10NumColumnsEv(char *param_1)

{
  if (*param_1 == '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296a118/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ACSV.cpp"*/,0x66,&UNK_029622f1/*"m_IsParsed is null."*/);
  }
  return *(undefined8 *)(param_1 + 0x48);
}

// ==== Framework::CACSV::Serialize() const
// vaddr 0x1eceab8 | ghidra 0x1fceab8 | size 268 | symbol _ZNK9Framework5CACSV9SerializeEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK9Framework5CACSV9SerializeEv(byte *param_1,char *param_2)

{
  undefined8 uVar1;
  long lVar2;
  ulong uVar3;
  
  if (*param_2 == '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296a118/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ACSV.cpp"*/,0x71,&UNK_029622f1/*"m_IsParsed is null."*/);
  }
  param_1[8] = 0;
  param_1[9] = 0;
  param_1[10] = 0;
  param_1[0xb] = 0;
  param_1[0xc] = 0;
  param_1[0xd] = 0;
  param_1[0xe] = 0;
  param_1[0xf] = 0;
  param_1[0x10] = 0;
  param_1[0x11] = 0;
  param_1[0x12] = 0;
  param_1[0x13] = 0;
  param_1[0x14] = 0;
  param_1[0x15] = 0;
  param_1[0x16] = 0;
  param_1[0x17] = 0;
  param_1[0] = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  param_1[6] = 0;
  param_1[7] = 0;
  uVar1 = Aska::ACSV::SerializeText(void*, unsigned long) const(param_2 + 8,0,0);
  lVar2 = operator new[](unsigned long, std::nothrow_t const&)(uVar1,PTR__ZSt7nothrow_02cb9a80);
  Aska::ACSV::SerializeText(void*, unsigned long) const(param_2 + 8,lVar2,uVar1);
  uVar3 = strlen(lVar2);
  if (uVar3 < 0x16 || uVar3 - 0x16 == 0) {
    if (uVar3 != 0) {
      memcpy(param_1 + 1,lVar2,uVar3);
    }
    param_1[uVar3 + 1] = 0;
    if ((*param_1 & 1) == 0) {
      *param_1 = (byte)(uVar3 << 1);
    }
    else {
      *(ulong *)(param_1 + 8) = uVar3;
    }
  }
  else {
    string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(param_1,0x16,uVar3 - 0x16,0,0,0,uVar3,lVar2);
  }
  if (lVar2 == 0) {
    return;
  }
  (*(code *)PTR__ZdlPv_02ca4758)(lVar2);
  return;
}

// ==== Framework::CACSV::Type(unsigned long, unsigned long) const
// vaddr 0x1ecebc4 | ghidra 0x1fcebc4 | size 88 | symbol _ZNK9Framework5CACSV4TypeEmm | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK9Framework5CACSV4TypeEmm(long param_1,undefined8 param_2,ulong param_3)

{
  uint uVar1;
  
  if ((*(long *)(param_1 + 0x40) != 0) && (param_3 < *(ulong *)(param_1 + 0x48))) {
    uVar1 = *(uint *)(*(long *)(param_1 + 0x40) + param_3 * 4);
    if (uVar1 < 0xd) {
      return *(undefined4 *)(&UNK_0296a1d0 + (long)(int)uVar1 * 4);
    }
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296a118/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ACSV.cpp"*/,0x99,&UNK_0296a168);
  }
  return 0;
}

// ==== Framework::CACSV::IsBlank(unsigned long, unsigned long) const
// vaddr 0x1ecec1c | ghidra 0x1fcec1c | size 48 | symbol _ZNK9Framework5CACSV7IsBlankEmm | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK9Framework5CACSV7IsBlankEmm(long param_1,long param_2,long param_3)

{
  ulong uVar1;
  
  uVar1 = param_3 + *(long *)(param_1 + 0x48) * param_2;
  return (1 << (ulong)((uint)uVar1 & 0x1f) &
         *(uint *)(*(long *)(param_1 + 0x20) + (uVar1 >> 5 & 0x7ffffff) * 4)) != 0;
}

// ==== Framework::CACSV::IsValue(unsigned long, unsigned long) const
// vaddr 0x1ecec4c | ghidra 0x1fcec4c | size 92 | symbol _ZNK9Framework5CACSV7IsValueEmm | lib libSOA-3.7.0.so | 2026-10-04
uint _ZNK9Framework5CACSV7IsValueEmm(long param_1,undefined8 param_2,ulong param_3)

{
  uint uVar1;
  
  if ((*(long *)(param_1 + 0x40) != 0) && (param_3 < *(ulong *)(param_1 + 0x48))) {
    uVar1 = *(uint *)(*(long *)(param_1 + 0x40) + param_3 * 4);
    if (uVar1 < 0xd) {
      return 0xffeU >> (ulong)(uVar1 & 0x1f) & 1;
    }
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296a118/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ACSV.cpp"*/,0x99,&UNK_0296a168);
  }
  return 0;
}

// ==== Framework::CACSV::IsString(unsigned long, unsigned long) const
// vaddr 0x1ececa8 | ghidra 0x1fceca8 | size 88 | symbol _ZNK9Framework5CACSV8IsStringEmm | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK9Framework5CACSV8IsStringEmm(long param_1,undefined8 param_2,ulong param_3)

{
  uint uVar1;
  
  if ((*(long *)(param_1 + 0x40) != 0) && (param_3 < *(ulong *)(param_1 + 0x48))) {
    uVar1 = *(uint *)(*(long *)(param_1 + 0x40) + param_3 * 4);
    if (uVar1 < 0xd) {
      return (uVar1 & 0x1fff) == 0xc;
    }
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296a118/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ACSV.cpp"*/,0x99,&UNK_0296a168);
  }
  return false;
}

// ==== Framework::CACSV::String(unsigned long, unsigned long) const
// vaddr 0x1eced00 | ghidra 0x1fced00 | size 344 | symbol _ZNK9Framework5CACSV6StringEmm | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK9Framework5CACSV6StringEmm(ulong *param_1,long param_2,long param_3,ulong param_4)

{
  undefined8 *puVar1;
  undefined8 uVar2;
  uint uVar3;
  ulong uVar4;
  ulong uVar5;
  ulong uVar6;
  
  uVar4 = param_4 + *(ulong *)(param_2 + 0x48) * param_3;
  if (((((1 << (ulong)((uint)uVar4 & 0x1f) &
         *(uint *)(*(long *)(param_2 + 0x20) + (uVar4 >> 5 & 0x7ffffff) * 4)) != 0) ||
       (*(ulong *)(param_2 + 0x48) <= param_4)) || (*(long *)(param_2 + 0x40) == 0)) ||
     (uVar3 = *(uint *)(*(long *)(param_2 + 0x40) + param_4 * 4), uVar3 < 0xc)) {
code_r0x01fced54:
    param_1[1] = 0;
    param_1[2] = 0;
    *param_1 = 0;
    return;
  }
  if (uVar3 != 0xc) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296a118/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ACSV.cpp"*/,0x99,&UNK_0296a168);
    goto code_r0x01fced54;
  }
  puVar1 = (undefined8 *)(*(long *)(param_2 + 0x38) + uVar4 * 0x10);
  if (puVar1 == (undefined8 *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296a118/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ACSV.cpp"*/,0xc5,&UNK_029622b0/*"pString is null."*/);
  }
  uVar2 = *puVar1;
  uVar4 = puVar1[1];
  param_1[1] = 0;
  param_1[2] = 0;
  *param_1 = 0;
  if (uVar4 < 0x17) {
    uVar5 = (long)param_1 + 1;
    *(char *)param_1 = (char)(uVar4 << 1);
    if (uVar4 == 0) goto code_r0x01fcee50;
  }
  else {
    uVar6 = uVar4 + 0x10 & 0xfffffffffffffff0;
    if (uVar6 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296188c/*"C:\BAS_Submission\Client\Library\Framework\Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
    }
    uVar5 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar6,&UNK_029618d8/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/STL_String.h"*/,0x1c);
    if (uVar5 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296188c/*"C:\BAS_Submission\Client\Library\Framework\Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    }
    param_1[1] = uVar4;
    param_1[2] = uVar5;
    *param_1 = uVar6 | 1;
  }
  memcpy(uVar5,uVar2,uVar4);
code_r0x01fcee50:
  *(undefined1 *)(uVar5 + uVar4) = 0;
  return;
}

// ==== Framework::CACSV::Value(unsigned long, unsigned long) const
// vaddr 0x1ecee58 | ghidra 0x1fcee58 | size 480 | symbol _ZNK9Framework5CACSV5ValueEmm | lib libSOA-3.7.0.so | 2026-10-04
float _ZNK9Framework5CACSV5ValueEmm(long param_1,long param_2,ulong param_3)

{
  int iVar1;
  ulong uVar2;
  float fVar3;
  byte bStack_8;
  undefined1 uStack_7;
  undefined2 uStack_6;
  undefined4 uStack_4;
  
  uVar2 = param_3 + *(ulong *)(param_1 + 0x48) * param_2;
  if (((((1 << (ulong)((uint)uVar2 & 0x1f) &
         *(uint *)(*(long *)(param_1 + 0x20) + (uVar2 >> 5 & 0x7ffffff) * 4)) == 0) &&
       (*(long *)(param_1 + 0x40) != 0)) && (param_3 < *(ulong *)(param_1 + 0x48))) &&
     (iVar1 = *(int *)(*(long *)(param_1 + 0x40) + param_3 * 4), iVar1 - 1U < 0xb)) {
    param_1 = param_1 + 8;
    switch(iVar1) {
    case 2:
      Aska::ACSV::GetValue(Aska::ACSV::Type, unsigned long, unsigned long, void*) const(0,param_1,2,param_3,param_2,&bStack_8);
      return (float)(int)(char)bStack_8;
    case 3:
      Aska::ACSV::GetValue(Aska::ACSV::Type, unsigned long, unsigned long, void*) const(0,param_1,3,param_3,param_2,&bStack_8);
      fVar3 = (float)NEON_ucvtf((uint)bStack_8);
      return fVar3;
    case 4:
      Aska::ACSV::GetValue(Aska::ACSV::Type, unsigned long, unsigned long, void*) const(0,param_1,4,param_3,param_2,&bStack_8);
      return (float)(int)CONCAT11(uStack_7,bStack_8);
    case 5:
      Aska::ACSV::GetValue(Aska::ACSV::Type, unsigned long, unsigned long, void*) const(0,param_1,5,param_3,param_2,&bStack_8);
      fVar3 = (float)NEON_ucvtf((uint)CONCAT11(uStack_7,bStack_8));
      return fVar3;
    case 6:
      Aska::ACSV::GetValue(Aska::ACSV::Type, unsigned long, unsigned long, void*) const(0,param_1,6,param_3,param_2,&bStack_8);
      return (float)CONCAT22(uStack_6,CONCAT11(uStack_7,bStack_8));
    case 7:
      Aska::ACSV::GetValue(Aska::ACSV::Type, unsigned long, unsigned long, void*) const(0,param_1,7,param_3,param_2,&bStack_8);
      fVar3 = (float)NEON_ucvtf(CONCAT22(uStack_6,CONCAT11(uStack_7,bStack_8)));
      return fVar3;
    case 8:
      Aska::ACSV::GetValue(Aska::ACSV::Type, unsigned long, unsigned long, void*) const(0,param_1,8,param_3,param_2,&bStack_8);
      return (float)CONCAT44(uStack_4,CONCAT22(uStack_6,CONCAT11(uStack_7,bStack_8)));
    case 9:
      Aska::ACSV::GetValue(Aska::ACSV::Type, unsigned long, unsigned long, void*) const(0,param_1,9,param_3,param_2,&bStack_8);
      return (float)CONCAT44(uStack_4,CONCAT22(uStack_6,CONCAT11(uStack_7,bStack_8)));
    case 10:
      Aska::ACSV::GetValue(Aska::ACSV::Type, unsigned long, unsigned long, void*) const(0,param_1,10,param_3,param_2,&bStack_8);
      return (float)CONCAT22(uStack_6,CONCAT11(uStack_7,bStack_8));
    case 0xb:
      Aska::ACSV::GetValue(Aska::ACSV::Type, unsigned long, unsigned long, void*) const(0,param_1,0xb,param_3,param_2,&bStack_8);
      return (float)(double)CONCAT44(uStack_4,CONCAT22(uStack_6,CONCAT11(uStack_7,bStack_8)));
    }
    Aska::ACSV::GetValue(Aska::ACSV::Type, unsigned long, unsigned long, void*) const(0,param_1,1,param_3,param_2,&bStack_8);
    fVar3 = 1.0;
    if (bStack_8 == 0) {
      fVar3 = 0.0;
    }
    return fVar3;
  }
  return 0.0;
}

// ==== Framework::CACSV::Value(unsigned long, unsigned long, float)
// vaddr 0x1ecf038 | ghidra 0x1fcf038 | size 224 | symbol _ZN9Framework5CACSV5ValueEmmf | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework5CACSV5ValueEmmf(float param_1,long param_2,long param_3,ulong param_4)

{
  int iVar1;
  long lVar2;
  ulong uVar3;
  
  lVar2 = *(long *)(param_2 + 0x40);
  if ((lVar2 == 0) || (*(ulong *)(param_2 + 0x48) <= param_4)) {
code_r0x01fcf09c:
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296a118/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ACSV.cpp"*/,0xf4,&UNK_0296a17c/*"IsValue( aRow, aColunm ) is null."*/);
    lVar2 = *(long *)(param_2 + 0x40);
    if (lVar2 == 0) {
      uVar3 = *(ulong *)(param_2 + 0x48);
      goto code_r0x01fcf0f4;
    }
  }
  else {
    iVar1 = *(int *)(lVar2 + param_4 * 4);
    if (10 < iVar1 - 1U) {
      if ((iVar1 != 0) && (iVar1 != 0xc)) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296a118/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ACSV.cpp"*/,0x99,&UNK_0296a168);
      }
      goto code_r0x01fcf09c;
    }
  }
  uVar3 = *(ulong *)(param_2 + 0x48);
  if ((param_4 < uVar3) && (*(int *)(lVar2 + param_4 * 4) == 1)) {
    *(bool *)(*(long *)(param_2 + 0x38) + (param_4 + uVar3 * param_3) * 0x10) = param_1 != 0.0;
    return;
  }
code_r0x01fcf0f4:
  *(float *)(*(long *)(param_2 + 0x38) + (param_4 + uVar3 * param_3) * 0x10) = param_1;
  return;
}

// ==== Framework::CACSV::String(unsigned long, unsigned long, std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > const&)
// vaddr 0x1ecf118 | ghidra 0x1fcf118 | size 224 | symbol _ZN9Framework5CACSV6StringEmmRKNSt6__ndk112basic_stringIcNS1_11char_traitsIcEENS_13CSTLAllocatorIcNS_22CSTLStringAllocatorInfEEEEE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework5CACSV6StringEmmRKNSt6__ndk112basic_stringIcNS1_11char_traitsIcEENS_13CSTLAllocatorIcNS_22CSTLStringAllocatorInfEEEEE
               (long param_1,long param_2,ulong param_3,byte *param_4)

{
  undefined8 *puVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  uint uVar4;
  ulong uVar5;
  byte *pbVar6;
  
  if (((*(long *)(param_1 + 0x40) != 0) && (uVar5 = *(ulong *)(param_1 + 0x48), param_3 < uVar5)) &&
     (uVar4 = *(uint *)(*(long *)(param_1 + 0x40) + param_3 * 4), 0xb < uVar4)) {
    if (uVar4 == 0xc) goto code_r0x01fcf174;
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296a118/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ACSV.cpp"*/,0x99,&UNK_0296a168);
  }
  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296a118/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\ACSV.cpp"*/,0x107,&UNK_0296a19e/*"IsString( aRow, aColunm ) is null."*/);
  uVar5 = *(ulong *)(param_1 + 0x48);
code_r0x01fcf174:
  pbVar6 = *(byte **)(param_4 + 0x10);
  puVar1 = (undefined8 *)(*(long *)(param_1 + 0x38) + (param_3 + uVar5 * param_2) * 0x10);
  uVar2 = *puVar1;
  uVar3 = puVar1[1];
  if ((*param_4 & 1) == 0) {
    pbVar6 = param_4 + 1;
  }
  snprintf(uVar2,uVar3,&UNK_027f6a37/*"%s"*/,pbVar6);
  puVar1 = (undefined8 *)
           (*(long *)(param_1 + 0x38) + (param_3 + *(long *)(param_1 + 0x48) * param_2) * 0x10);
  *puVar1 = uVar2;
  puVar1[1] = uVar3;
  return;
}

// ==== Framework::CACSV::PrintC() const
// vaddr 0x1ecf1f8 | ghidra 0x1fcf1f8 | size 4 | symbol _ZNK9Framework5CACSV6PrintCEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK9Framework5CACSV6PrintCEv(void)

{
  return;
}


// FAILED to create function at 02962236 Framework::CCSV::sDefaultSeparator
// FAILED to create function at 02962237 Framework::CCSV::sDefaultQuote
