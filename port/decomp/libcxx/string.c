// port/decomp/libcxx/string.c: Ghidra decompiles for the libcxx subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-04 05:14 UTC: tools/decomp.sh '--into' 'libcxx/string' 'basic_string<char,std::__ndk1::char_traits<char>,Framework::CSTLAllocator<char,Framework::CSTLStringAllocatorInf>>::(reserve|__grow_by|__grow_by_and_replace|replace|insert|~basic_string)\('

// ==== std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> >::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)
// vaddr 0x1148a4c | ghidra 0x1248a4c | size 360 | symbol _ZNSt6__ndk112basic_stringIcNS_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS3_22CSTLStringAllocatorInfEEEE21__grow_by_and_replaceEmmmmmmPKc | lib libSOA-3.7.0.so | 2026-10-04
void _ZNSt6__ndk112basic_stringIcNS_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS3_22CSTLStringAllocatorInfEEEE21__grow_by_and_replaceEmmmmmmPKc
               (ulong *param_1,ulong param_2,long param_3,long param_4,long param_5,long param_6,
               long param_7,undefined8 param_8)

{
  ulong uVar1;
  ulong uVar2;
  byte *pbVar3;
  ulong uVar4;
  
  if ((*param_1 & 1) == 0) {
    pbVar3 = (byte *)((long)param_1 + 1);
  }
  else {
    pbVar3 = (byte *)param_1[2];
  }
  if (param_2 < 0x7fffffffffffffe7) {
    uVar4 = param_2 << 1;
    if (param_2 << 1 <= param_3 + param_2) {
      uVar4 = param_3 + param_2;
    }
    if (uVar4 < 0x17) {
      uVar4 = 0x17;
    }
    else {
      uVar4 = uVar4 + 0x10 & 0xfffffffffffffff0;
      if (uVar4 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
      }
    }
  }
  else {
    uVar4 = 0xffffffffffffffef;
  }
  uVar2 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar4,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
  if (uVar2 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
  }
  if (param_5 != 0) {
    memcpy(uVar2,pbVar3,param_5);
  }
  if (param_7 != 0) {
    memcpy(uVar2 + param_5,param_8,param_7);
  }
  if (param_4 - param_6 != param_5) {
    memcpy(uVar2 + param_5 + param_7,pbVar3 + param_6 + param_5);
  }
  if (param_2 != 0x16) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(pbVar3);
  }
  uVar1 = (param_4 - param_6) + param_7;
  *param_1 = uVar4 | 1;
  param_1[1] = uVar1;
  param_1[2] = uVar2;
  *(undefined1 *)(uVar2 + uVar1) = 0;
  return;
}

// ==== std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> >::replace(unsigned long, unsigned long, char const*, unsigned long)
// vaddr 0x1148e70 | ghidra 0x1248e70 | size 432 | symbol _ZNSt6__ndk112basic_stringIcNS_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS3_22CSTLStringAllocatorInfEEEE7replaceEmmPKcm | lib libSOA-3.7.0.so | 2026-10-04
ulong * _ZNSt6__ndk112basic_stringIcNS_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS3_22CSTLStringAllocatorInfEEEE7replaceEmmPKcm
                  (ulong *param_1,long param_2,ulong param_3,ulong param_4,ulong param_5)

{
  ulong uVar1;
  byte bVar2;
  long lVar3;
  ulong uVar4;
  ulong uVar5;
  ulong uVar6;
  ulong uVar7;
  
  bVar2 = (byte)*param_1;
  uVar5 = (ulong)bVar2;
  if ((bVar2 & 1) == 0) {
    uVar6 = (ulong)(bVar2 >> 1);
    uVar4 = uVar6 - param_2;
    uVar7 = uVar4;
    if (param_3 <= uVar4) {
      uVar7 = param_3;
    }
    lVar3 = 0x16;
  }
  else {
    uVar5 = *param_1;
    uVar6 = param_1[1];
    uVar4 = uVar6 - param_2;
    uVar7 = uVar4;
    if (param_3 <= uVar4) {
      uVar7 = param_3;
    }
    lVar3 = (uVar5 & 0xfffffffffffffffe) - 1;
  }
  if ((uVar7 - uVar6) + lVar3 < param_5) {
    string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(param_1,lVar3,((uVar6 + param_5) - uVar7) - lVar3,uVar6,param_2,uVar7,param_5,
                    param_4);
    return param_1;
  }
  uVar1 = param_5;
  if ((uVar5 & 1) == 0) {
    uVar5 = (long)param_1 + 1;
    if (uVar7 == param_5) goto joined_r0x01249018;
code_r0x01248f18:
    uVar4 = uVar4 - uVar7;
    uVar1 = uVar7;
    if (uVar4 == 0) goto joined_r0x01249018;
    uVar1 = uVar5 + param_2;
    if (uVar7 <= param_5) {
      if ((uVar1 < param_4) && (param_4 < uVar5 + uVar6)) {
        if (param_4 < uVar1 + uVar7) {
          if (uVar7 != 0) {
            memmove(uVar1,param_4,uVar7);
          }
          param_2 = uVar7 + param_2;
          param_4 = param_4 + param_5;
          param_5 = param_5 - uVar7;
          uVar7 = 0;
        }
        else {
          param_4 = param_4 + (param_5 - uVar7);
        }
      }
      memmove(uVar5 + param_2 + param_5,uVar5 + param_2 + uVar7,uVar4);
      uVar1 = uVar7;
      goto joined_r0x01249018;
    }
    if (param_5 != 0) {
      memmove(uVar1,param_4,param_5);
    }
    param_2 = uVar1 + param_5;
    param_4 = uVar1 + uVar7;
  }
  else {
    uVar5 = param_1[2];
    if (uVar7 != param_5) goto code_r0x01248f18;
joined_r0x01249018:
    uVar7 = uVar1;
    uVar4 = param_5;
    if (uVar4 == 0) goto code_r0x01248f74;
    param_2 = uVar5 + param_2;
    param_5 = uVar4;
  }
  memmove(param_2,param_4,uVar4);
  uVar4 = param_5;
code_r0x01248f74:
  uVar6 = (uVar4 - uVar7) + uVar6;
  if ((*param_1 & 1) == 0) {
    *(char *)param_1 = (char)uVar6 * '\x02';
  }
  else {
    param_1[1] = uVar6;
  }
  *(undefined1 *)(uVar5 + uVar6) = 0;
  return param_1;
}

// ==== std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> >::reserve(unsigned long)
// vaddr 0x1149020 | ghidra 0x1249020 | size 392 | symbol _ZNSt6__ndk112basic_stringIcNS_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS3_22CSTLStringAllocatorInfEEEE7reserveEm | lib libSOA-3.7.0.so | 2026-10-04
void _ZNSt6__ndk112basic_stringIcNS_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS3_22CSTLStringAllocatorInfEEEE7reserveEm
               (ulong *param_1,ulong param_2)

{
  byte bVar1;
  bool bVar2;
  bool bVar3;
  byte *pbVar4;
  uint uVar5;
  ulong uVar6;
  ulong uVar7;
  byte *pbVar8;
  ulong uVar9;
  ulong uVar10;
  
  bVar1 = (byte)*param_1;
  uVar6 = (ulong)bVar1;
  if ((bVar1 & 1) == 0) {
    uVar7 = 0x16;
    if ((bVar1 & 1) != 0) goto code_r0x01249044;
code_r0x0124905c:
    uVar9 = (ulong)(((uint)uVar6 & 0xfe) >> 1);
  }
  else {
    uVar6 = *param_1;
    uVar7 = (uVar6 & 0xfffffffffffffffe) - 1;
    if ((uVar6 & 1) == 0) goto code_r0x0124905c;
code_r0x01249044:
    uVar9 = param_1[1];
  }
  uVar5 = (uint)uVar6;
  uVar10 = uVar9;
  if (uVar9 <= param_2) {
    uVar10 = param_2;
  }
  if (uVar10 < 0x17) {
    uVar10 = 0x16;
    if (uVar7 == 0x16) {
      return;
    }
  }
  else {
    uVar10 = (uVar10 + 0x10 & 0xfffffffffffffff0) - 1;
    if (uVar10 == uVar7) {
      return;
    }
  }
  if (uVar10 == 0x16) {
    pbVar8 = (byte *)param_1[2];
    bVar3 = false;
    pbVar4 = (byte *)((long)param_1 + 1);
    bVar2 = true;
    if ((uVar6 & 1) != 0) goto code_r0x01249150;
code_r0x0124909c:
    if ((uVar5 & 0xfe) >> 1 == 0xffffffff) goto code_r0x01249168;
  }
  else {
    if (uVar10 + 1 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
    }
    pbVar4 = (byte *)Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar10 + 1,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
    if ((pbVar4 == (byte *)0x0) &&
       (Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/), uVar10 <= uVar7)) {
      return;
    }
    bVar1 = (byte)*param_1;
    uVar5 = (uint)bVar1;
    if ((bVar1 & 1) != 0) {
      pbVar8 = (byte *)param_1[2];
      bVar2 = true;
      bVar3 = true;
      if ((bVar1 & 1) != 0) goto code_r0x01249150;
      goto code_r0x0124909c;
    }
    bVar2 = false;
    pbVar8 = (byte *)((long)param_1 + 1);
    bVar3 = true;
    if ((bVar1 & 1) == 0) goto code_r0x0124909c;
code_r0x01249150:
    if (param_1[1] == 0xffffffffffffffff) goto code_r0x01249168;
  }
  memcpy(pbVar4,pbVar8);
code_r0x01249168:
  if (bVar2) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(pbVar8);
  }
  if (bVar3) {
    *param_1 = uVar10 + 1 | 1;
    param_1[1] = uVar9;
    param_1[2] = (ulong)pbVar4;
  }
  else {
    *(byte *)param_1 = (byte)(uVar9 << 1);
  }
  return;
}

// ==== std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> >::__grow_by(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long)
// vaddr 0x1157808 | ghidra 0x1257808 | size 320 | symbol _ZNSt6__ndk112basic_stringIcNS_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS3_22CSTLStringAllocatorInfEEEE9__grow_byEmmmmmm | lib libSOA-3.7.0.so | 2026-10-04
void _ZNSt6__ndk112basic_stringIcNS_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS3_22CSTLStringAllocatorInfEEEE9__grow_byEmmmmmm
               (ulong *param_1,ulong param_2,long param_3,long param_4,long param_5,long param_6,
               long param_7)

{
  ulong uVar1;
  byte *pbVar2;
  ulong uVar3;
  
  if ((*param_1 & 1) == 0) {
    pbVar2 = (byte *)((long)param_1 + 1);
  }
  else {
    pbVar2 = (byte *)param_1[2];
  }
  if (param_2 < 0x7fffffffffffffe7) {
    uVar3 = param_2 << 1;
    if (param_2 << 1 <= param_3 + param_2) {
      uVar3 = param_3 + param_2;
    }
    if (uVar3 < 0x17) {
      uVar3 = 0x17;
    }
    else {
      uVar3 = uVar3 + 0x10 & 0xfffffffffffffff0;
      if (uVar3 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
      }
    }
  }
  else {
    uVar3 = 0xffffffffffffffef;
  }
  uVar1 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar3,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
  if (uVar1 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
  }
  if (param_5 != 0) {
    memcpy(uVar1,pbVar2,param_5);
  }
  if (param_4 - param_6 != param_5) {
    memcpy(uVar1 + param_5 + param_7,pbVar2 + param_6 + param_5);
  }
  if (param_2 != 0x16) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(pbVar2);
  }
  param_1[2] = uVar1;
  *param_1 = uVar3 | 1;
  return;
}

// ==== std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> >::insert(unsigned long, char const*)
// vaddr 0x1311f44 | ghidra 0x1411f44 | size 260 | symbol _ZNSt6__ndk112basic_stringIcNS_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS3_22CSTLStringAllocatorInfEEEE6insertEmPKc | lib libSOA-3.7.0.so | 2026-10-04
ulong * _ZNSt6__ndk112basic_stringIcNS_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS3_22CSTLStringAllocatorInfEEEE6insertEmPKc
                  (ulong *param_1,ulong param_2,ulong param_3)

{
  ulong uVar1;
  byte bVar2;
  ulong uVar3;
  long lVar4;
  ulong uVar5;
  ulong uVar6;
  ulong uVar7;
  
  uVar3 = strlen(param_3);
  bVar2 = (byte)*param_1;
  uVar5 = (ulong)bVar2;
  if ((bVar2 & 1) == 0) {
    uVar7 = (ulong)(bVar2 >> 1);
    lVar4 = 0x16;
  }
  else {
    uVar5 = *param_1;
    uVar7 = param_1[1];
    lVar4 = (uVar5 & 0xfffffffffffffffe) - 1;
  }
  if (lVar4 - uVar7 < uVar3) {
    string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(param_1,lVar4,(uVar7 + uVar3) - lVar4,uVar7,param_2,0,uVar3,param_3);
  }
  else if (uVar3 != 0) {
    if ((uVar5 & 1) == 0) {
      uVar5 = (long)param_1 + 1;
    }
    else {
      uVar5 = param_1[2];
    }
    uVar1 = uVar5 + param_2;
    uVar6 = param_3;
    if (uVar7 != param_2) {
      uVar6 = param_3 + uVar3;
      if (uVar5 + uVar7 <= param_3 || param_3 < uVar1) {
        uVar6 = param_3;
      }
      memmove(uVar1 + uVar3,uVar1);
    }
    memmove(uVar1,uVar6,uVar3);
    uVar7 = uVar7 + uVar3;
    if ((*param_1 & 1) == 0) {
      *(char *)param_1 = (char)uVar7 * '\x02';
    }
    else {
      param_1[1] = uVar7;
    }
    *(undefined1 *)(uVar5 + uVar7) = 0;
  }
  return param_1;
}

// ==== std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> >::~basic_string()
// vaddr 0x1dc5f88 | ghidra 0x1ec5f88 | size 20 | symbol _ZNSt6__ndk112basic_stringIcNS_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS3_22CSTLStringAllocatorInfEEEED2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZNSt6__ndk112basic_stringIcNS_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS3_22CSTLStringAllocatorInfEEEED2Ev
               (byte *param_1)

{
  if ((*param_1 & 1) == 0) {
    return;
  }
  (*(code *)PTR__ZN9Framework37CAssignedMemoryManagerForSTLAllocator4FreeEPv_02ca11c0)
            (*(undefined8 *)(param_1 + 0x10));
  return;
}
