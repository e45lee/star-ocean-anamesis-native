// port/decomp/containers/strings.c: Ghidra decompiles for the containers subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileAt.java, tools/resolve_decomp.py
// run      2026-10-04 05:13 UTC: tools/decomp_at.sh '--into' 'containers/strings' '1241df0' '1248bb4' '124b2e0' '124b5e4' '124b5f8' '124b600' '124b81c' '124b830' '124b838' '125100c' '13328f4' '13540c4' '1440d3c' '148ddc8' '14b45b4' '14b4664' '18e8070' '2055408' '2055524' '205563c' '2055788' '207de20' '207de7c' '207ded8' '207df04' '207e0c4' '207eb9c' '207f290'

// ==== Framework::CSTLStringUtility_Base<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > >::Replace(std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > const&, std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > const&, std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > const&, bool*)
// vaddr 0x1141df0 | ghidra 0x1241df0 | size 496 | symbol _ZN9Framework22CSTLStringUtility_BaseINSt6__ndk112basic_stringIcNS1_11char_traitsIcEENS_13CSTLAllocatorIcNS_22CSTLStringAllocatorInfEEEEEE7ReplaceERKS8_SB_SB_Pb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework22CSTLStringUtility_BaseINSt6__ndk112basic_stringIcNS1_11char_traitsIcEENS_13CSTLAllocatorIcNS_22CSTLStringAllocatorInfEEEEEE7ReplaceERKS8_SB_SB_Pb
               (ulong *param_1,ulong *param_2,undefined8 param_3,undefined8 param_4,
               undefined8 param_5)

{
  ulong uVar1;
  ulong *puVar2;
  ulong uVar3;
  ulong uVar4;
  ulong uVar5;
  ulong uStack_70;
  ulong uStack_68;
  ulong uStack_60;
  
  uStack_68 = 0;
  uStack_60 = 0;
  uStack_70 = 0;
  if ((*param_2 & 1) == 0) {
    uStack_60 = param_2[2];
    uStack_68 = param_2[1];
    uStack_70 = *param_2;
  }
  else {
    uVar5 = param_2[1];
    uVar1 = param_2[2];
    if (uVar5 < 0x17) {
      uVar3 = (ulong)&uStack_70 | 1;
      uStack_70 = (uVar5 & 0x7f) << 1;
      if (uVar5 != 0) goto code_r0x01241ec4;
    }
    else {
      uVar4 = uVar5 + 0x10 & 0xfffffffffffffff0;
      if (uVar4 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
      }
      uVar3 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar4,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
      if (uVar3 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
      }
      uStack_70 = uVar4 | 1;
      uStack_68 = uVar5;
      uStack_60 = uVar3;
code_r0x01241ec4:
      memcpy(uVar3,uVar1,uVar5);
    }
    *(undefined1 *)(uVar3 + uVar5) = 0;
  }
  puVar2 = (ulong *)Framework::CSTLStringUtility_Base<string >::ReplaceSelf(string&, string const&, string const&, bool*)(&uStack_70,param_3,param_4,param_5);
  param_1[1] = 0;
  param_1[2] = 0;
  *param_1 = 0;
  if ((*puVar2 & 1) == 0) {
    param_1[2] = puVar2[2];
    uVar5 = *puVar2;
    param_1[1] = puVar2[1];
    *param_1 = uVar5;
    goto joined_r0x01241fb8;
  }
  uVar5 = puVar2[1];
  uVar1 = puVar2[2];
  if (uVar5 < 0x17) {
    uVar3 = (long)param_1 + 1;
    *(char *)param_1 = (char)(uVar5 << 1);
    if (uVar5 != 0) goto code_r0x01241fa0;
  }
  else {
    uVar4 = uVar5 + 0x10 & 0xfffffffffffffff0;
    if (uVar4 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
    }
    uVar3 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar4,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
    if (uVar3 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    }
    param_1[1] = uVar5;
    param_1[2] = uVar3;
    *param_1 = uVar4 | 1;
code_r0x01241fa0:
    memcpy(uVar3,uVar1,uVar5);
  }
  *(undefined1 *)(uVar3 + uVar5) = 0;
joined_r0x01241fb8:
  if ((uStack_70 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_60);
  }
  return;
}

// ==== Framework::CSTLStringUtility_Base<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > >::ReplaceSelf(std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> >&, std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > const&, std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > const&, bool*)
// vaddr 0x1148bb4 | ghidra 0x1248bb4 | size 700 | symbol _ZN9Framework22CSTLStringUtility_BaseINSt6__ndk112basic_stringIcNS1_11char_traitsIcEENS_13CSTLAllocatorIcNS_22CSTLStringAllocatorInfEEEEEE11ReplaceSelfERS8_RKS8_SC_Pb | lib libSOA-3.7.0.so | 2026-10-04
byte * _ZN9Framework22CSTLStringUtility_BaseINSt6__ndk112basic_stringIcNS1_11char_traitsIcEENS_13CSTLAllocatorIcNS_22CSTLStringAllocatorInfEEEEEE11ReplaceSelfERS8_RKS8_SC_Pb
                 (byte *param_1,byte *param_2,byte *param_3,undefined1 *param_4)

{
  byte *pbVar1;
  byte *pbVar2;
  ulong uVar3;
  byte bVar4;
  byte *pbVar5;
  byte *pbVar6;
  ulong uVar7;
  byte *pbVar8;
  byte *pbVar9;
  long lVar10;
  ulong uVar11;
  
  if (param_4 != (undefined1 *)0x0) {
    *param_4 = 0;
    uVar11 = 0;
    do {
      uVar3 = (ulong)(*param_1 >> 1);
      pbVar5 = param_1 + 1;
      if ((*param_1 & 1) != 0) {
        uVar3 = *(ulong *)(param_1 + 8);
        pbVar5 = *(byte **)(param_1 + 0x10);
      }
      uVar7 = (ulong)(*param_2 >> 1);
      pbVar6 = param_2 + 1;
      if ((*param_2 & 1) != 0) {
        uVar7 = *(ulong *)(param_2 + 8);
        pbVar6 = *(byte **)(param_2 + 0x10);
      }
      if (uVar3 < uVar11) {
        return param_1;
      }
      if (uVar3 - uVar11 < uVar7) {
        return param_1;
      }
      if (uVar7 != 0) {
        pbVar9 = pbVar5 + uVar11;
        pbVar2 = pbVar5 + uVar3;
        pbVar8 = pbVar2;
        if (((long)uVar7 <= (long)pbVar2 - (long)pbVar9) && (pbVar2 + (1 - uVar7) != pbVar9)) {
          lVar10 = (uVar7 - (long)pbVar5) - uVar3;
          do {
            while (*pbVar9 == *pbVar6) {
              uVar11 = 1;
              do {
                pbVar8 = pbVar9;
                if (uVar7 == uVar11) goto code_r0x01248c00;
                pbVar8 = pbVar9 + uVar11;
                pbVar1 = pbVar6 + uVar11;
                uVar11 = uVar11 + 1;
              } while (*pbVar8 == *pbVar1);
              pbVar1 = pbVar9 + lVar10;
              pbVar9 = pbVar9 + 1;
              pbVar8 = pbVar2;
              if (pbVar1 == (byte *)0x0) goto code_r0x01248c00;
            }
            pbVar9 = pbVar9 + 1;
            pbVar8 = pbVar2;
          } while (pbVar9 + lVar10 != (byte *)0x1);
        }
code_r0x01248c00:
        if (pbVar2 == pbVar8) {
          return param_1;
        }
        uVar11 = (long)pbVar8 - (long)pbVar5;
      }
      if (uVar11 == 0xffffffffffffffff) {
        return param_1;
      }
      uVar3 = (ulong)(*param_3 >> 1);
      pbVar5 = param_3 + 1;
      if ((*param_3 & 1) != 0) {
        uVar3 = *(ulong *)(param_3 + 8);
        pbVar5 = *(byte **)(param_3 + 0x10);
      }
      string::replace(unsigned long, unsigned long, char const*, unsigned long)(param_1,uVar11,uVar7,pbVar5,uVar3);
      bVar4 = *param_3;
      uVar7 = *(ulong *)(param_3 + 8);
      *param_4 = 1;
      uVar3 = (ulong)(bVar4 >> 1);
      if ((bVar4 & 1) != 0) {
        uVar3 = uVar7;
      }
      uVar11 = uVar3 + uVar11;
    } while( true );
  }
  uVar11 = 0;
  do {
    uVar3 = (ulong)(*param_1 >> 1);
    pbVar5 = param_1 + 1;
    if ((*param_1 & 1) != 0) {
      uVar3 = *(ulong *)(param_1 + 8);
      pbVar5 = *(byte **)(param_1 + 0x10);
    }
    uVar7 = (ulong)(*param_2 >> 1);
    pbVar6 = param_2 + 1;
    if ((*param_2 & 1) != 0) {
      uVar7 = *(ulong *)(param_2 + 8);
      pbVar6 = *(byte **)(param_2 + 0x10);
    }
    if (uVar3 < uVar11) {
      return param_1;
    }
    if (uVar3 - uVar11 < uVar7) {
      return param_1;
    }
    if (uVar7 != 0) {
      pbVar9 = pbVar5 + uVar11;
      pbVar2 = pbVar5 + uVar3;
      pbVar8 = pbVar2;
      if (((long)uVar7 <= (long)pbVar2 - (long)pbVar9) && (pbVar2 + (1 - uVar7) != pbVar9)) {
        lVar10 = (uVar7 - (long)pbVar5) - uVar3;
        do {
          while (*pbVar9 == *pbVar6) {
            uVar11 = 1;
            do {
              pbVar8 = pbVar9;
              if (uVar7 == uVar11) goto code_r0x01248d2c;
              pbVar8 = pbVar9 + uVar11;
              pbVar1 = pbVar6 + uVar11;
              uVar11 = uVar11 + 1;
            } while (*pbVar8 == *pbVar1);
            pbVar1 = pbVar9 + lVar10;
            pbVar8 = pbVar2;
            pbVar9 = pbVar9 + 1;
            if (pbVar1 == (byte *)0x0) goto code_r0x01248d2c;
          }
          pbVar9 = pbVar9 + 1;
          pbVar8 = pbVar2;
        } while (pbVar9 + lVar10 != (byte *)0x1);
      }
code_r0x01248d2c:
      if (pbVar2 == pbVar8) {
        return param_1;
      }
      uVar11 = (long)pbVar8 - (long)pbVar5;
    }
    if (uVar11 == 0xffffffffffffffff) {
      return param_1;
    }
    uVar3 = (ulong)(*param_3 >> 1);
    pbVar5 = param_3 + 1;
    if ((*param_3 & 1) != 0) {
      uVar3 = *(ulong *)(param_3 + 8);
      pbVar5 = *(byte **)(param_3 + 0x10);
    }
    string::replace(unsigned long, unsigned long, char const*, unsigned long)(param_1,uVar11,uVar7,pbVar5,uVar3);
    uVar3 = (ulong)(*param_3 >> 1);
    if ((*param_3 & 1) != 0) {
      uVar3 = *(ulong *)(param_3 + 8);
    }
    uVar11 = uVar3 + uVar11;
  } while( true );
}

// ==== Framework::TStaticString<256ul>::operator+=(char const*)
// vaddr 0x114b2e0 | ghidra 0x124b2e0 | size 732 | symbol _ZN9Framework13TStaticStringILm256EEpLEPKc | lib libSOA-3.7.0.so | 2026-10-04
char * _ZN9Framework13TStaticStringILm256EEpLEPKc(char *param_1,undefined8 param_2)

{
  long lVar1;
  ulong uVar2;
  ulong uVar3;
  long lVar4;
  char cVar5;
  char *pcVar6;
  ulong uVar7;
  ulong uVar8;
  ulong uStack_80;
  ulong uStack_78;
  ulong uStack_70;
  ulong uStack_68;
  ulong uStack_60;
  char *pcStack_58;
  ulong uStack_50;
  ulong uStack_48;
  char *pcStack_40;
  
  uStack_60 = 0;
  pcStack_58 = (char *)0x0;
  uStack_68 = 0;
  uVar3 = strlen();
  if (uVar3 < 0x17) {
    pcVar6 = (char *)((ulong)&uStack_68 | 1);
    uStack_68 = CONCAT71(uStack_68._1_7_,(char)(uVar3 << 1));
    if (uVar3 != 0) goto code_r0x0124b38c;
  }
  else {
    uVar8 = uVar3 + 0x10 & 0xfffffffffffffff0;
    if (uVar8 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
    }
    pcVar6 = (char *)Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar8,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
    if (pcVar6 == (char *)0x0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    }
    uStack_68 = uVar8 | 1;
    uStack_60 = uVar3;
    pcStack_58 = pcVar6;
code_r0x0124b38c:
    memcpy(pcVar6,param_1,uVar3);
  }
  pcVar6[uVar3] = '\0';
  uStack_78 = 0;
  uStack_70 = 0;
  uStack_80 = 0;
  uVar3 = strlen(param_2);
  if (uVar3 < 0x17) {
    uVar7 = (ulong)&uStack_80 | 1;
    uStack_80 = CONCAT71(uStack_80._1_7_,(char)(uVar3 << 1));
    if (uVar3 == 0) goto code_r0x0124b454;
  }
  else {
    uVar8 = uVar3 + 0x10 & 0xfffffffffffffff0;
    if (uVar8 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
    }
    uVar7 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar8,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
    if (uVar7 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    }
    uStack_80 = uVar8 | 1;
    uStack_78 = uVar3;
    uStack_70 = uVar7;
  }
  memcpy(uVar7,param_2,uVar3);
code_r0x0124b454:
  *(undefined1 *)(uVar7 + uVar3) = 0;
  uVar3 = uStack_80 >> 1 & 0x7f;
  uVar8 = (ulong)&uStack_80 | 1;
  if ((uStack_80 & 1) != 0) {
    uVar3 = uStack_78;
    uVar8 = uStack_70;
  }
  if ((uStack_68 & 1) == 0) {
    lVar4 = 0x16;
    uVar7 = uStack_68 & 0xff;
  }
  else {
    lVar4 = (uStack_68 & 0xfffffffffffffffe) - 1;
    uVar7 = uStack_68;
  }
  uVar2 = (ulong)(((uint)uVar7 & 0xfe) >> 1);
  if ((uVar7 & 1) != 0) {
    uVar2 = uStack_60;
  }
  if (lVar4 - uVar2 < uVar3) {
    string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&uStack_68,lVar4,(uVar3 - lVar4) + uVar2,uVar2,uVar2,0,uVar3);
  }
  else if (uVar3 != 0) {
    pcVar6 = (char *)((ulong)&uStack_68 | 1);
    if ((uVar7 & 1) != 0) {
      pcVar6 = pcStack_58;
    }
    memcpy(pcVar6 + uVar2,uVar8,uVar3);
    uVar2 = uVar2 + uVar3;
    uVar3 = uVar2;
    if ((uStack_68 & 1) == 0) {
      uStack_68 = CONCAT71(uStack_68._1_7_,(char)uVar2 * '\x02');
      uVar3 = uStack_60;
    }
    uStack_60 = uVar3;
    pcVar6[uVar2] = '\0';
  }
  pcStack_40 = pcStack_58;
  uStack_48 = uStack_60;
  uStack_50 = uStack_68;
  uStack_60 = 0;
  pcStack_58 = (char *)0x0;
  uStack_68 = 0;
  if (((uStack_80 & 1) != 0) && (Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_70), (uStack_68 & 1) != 0)) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(pcStack_58);
  }
  pcVar6 = (char *)((ulong)&uStack_50 | 1);
  if ((uStack_50 & 1) != 0) {
    pcVar6 = pcStack_40;
  }
  cVar5 = *pcVar6;
  *param_1 = cVar5;
  lVar4 = 0;
  do {
    if (cVar5 == '\0') goto code_r0x0124b598;
    cVar5 = pcVar6[lVar4 + 1];
    lVar1 = lVar4 + 1;
    param_1[lVar4 + 1] = cVar5;
    lVar4 = lVar1;
  } while ((int)lVar1 < 0xff);
  param_1[lVar1] = '\0';
code_r0x0124b598:
  if ((uStack_50 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(pcStack_40);
  }
  return param_1;
}

// ==== FUN_0124b5e4
// vaddr 0x114b5e4 | ghidra 0x124b5e4 | size 0 | symbol FUN_0124b5e4 | lib libSOA-3.7.0.so | 2026-10-04
void FUN_0124b5e4(undefined8 param_1,undefined8 *param_2)

{
  *param_2 = &UNK_02a96d58;
  return;
}

// ==== FUN_0124b5f8
// vaddr 0x114b5f8 | ghidra 0x124b5f8 | size 0 | symbol FUN_0124b5f8 | lib libSOA-3.7.0.so | 2026-10-04
void FUN_0124b5f8(void)

{
  return;
}

// ==== FUN_0124b600
// vaddr 0x114b600 | ghidra 0x124b600 | size 0 | symbol FUN_0124b600 | lib libSOA-3.7.0.so | 2026-10-04
void FUN_0124b600(void)

{
  byte *pbVar1;
  uint uVar2;
  ulong uVar3;
  undefined4 uVar4;
  int *piVar5;
  long lVar6;
  undefined8 uVar7;
  undefined8 *in_x3;
  undefined8 *in_x4;
  ulong *in_x5;
  ulong uVar8;
  ulong uVar9;
  long *plVar10;
  undefined1 auStack_140 [16];
  byte abStack_130 [256];
  
  plVar10 = (long *)*in_x4;
  if (*(int *)*plVar10 == 0x444c4441) {
    uVar2 = ((int *)*plVar10)[1];
    uVar7 = *in_x3;
    if ((uVar2 & 1) == 0) {
      *in_x5 = *in_x5 - 0x10;
      if ((uVar2 >> 1 & 1) != 0) {
        Framework::CHash32::CHash32(char const*)(auStack_140,uVar7);
        uVar4 = Framework::CHash32::Get() const(auStack_140);
        snprintf(abStack_130,0x100,&UNK_027db267/*"%00000000000000000000000000000032u"*/,uVar4);
        Framework::CHash32::~CHash32()(auStack_140);
        uVar9 = *in_x5;
        piVar5 = (int *)operator new[](unsigned long, std::nothrow_t const&)(uVar9,PTR__ZSt7nothrow_02cb9a80);
        DecryptAES128(char const*, unsigned char const*, unsigned int, unsigned char*, unsigned int)(abStack_130,*plVar10 + 0x10,uVar9 & 0xffffffff,piVar5,uVar9 & 0xffffffff);
        if (*plVar10 != 0) {
          operator delete[](void*)();
          *plVar10 = 0;
        }
        *plVar10 = (long)piVar5;
        if ((*piVar5 == 0x454e4344) && (piVar5[1] == 1)) {
          uVar9 = (ulong)(uint)piVar5[2] - 0x10;
          *in_x5 = uVar9;
          lVar6 = operator new[](unsigned long, std::nothrow_t const&)(uVar9,PTR__ZSt7nothrow_02cb9a80);
          memcpy(lVar6,piVar5 + 4,uVar9);
          if (*plVar10 != 0) {
            operator delete[](void*)();
            *plVar10 = 0;
          }
          *plVar10 = lVar6;
        }
      }
    }
    else {
      *in_x5 = *in_x5 - 0x10;
      Framework::CHash32::CHash32(char const*)(auStack_140,uVar7);
      uVar4 = Framework::CHash32::Get() const(auStack_140);
      snprintf(abStack_130,0x100,&UNK_02815ba9/*"%x"*/,uVar4);
      Framework::CHash32::~CHash32()(auStack_140);
      uVar9 = strlen(abStack_130);
      if (*in_x5 != 0) {
        uVar8 = 0;
        lVar6 = 0;
        do {
          pbVar1 = (byte *)(*plVar10 + uVar8);
          uVar8 = uVar8 + 1;
          *pbVar1 = abStack_130[lVar6] ^ pbVar1[0x10];
          uVar3 = 0;
          if (uVar9 != 0) {
            uVar3 = (lVar6 + 1U) / uVar9;
          }
          lVar6 = (lVar6 + 1U) - uVar3 * uVar9;
        } while (uVar8 < *in_x5);
      }
    }
  }
  return;
}

// ==== FUN_0124b81c
// vaddr 0x114b81c | ghidra 0x124b81c | size 0 | symbol FUN_0124b81c | lib libSOA-3.7.0.so | 2026-10-04
void FUN_0124b81c(undefined8 param_1,undefined8 *param_2)

{
  *param_2 = &UNK_02a96de8;
  return;
}

// ==== FUN_0124b830
// vaddr 0x114b830 | ghidra 0x124b830 | size 0 | symbol FUN_0124b830 | lib libSOA-3.7.0.so | 2026-10-04
void FUN_0124b830(void)

{
  return;
}

// ==== FUN_0124b838
// vaddr 0x114b838 | ghidra 0x124b838 | size 0 | symbol FUN_0124b838 | lib libSOA-3.7.0.so | 2026-10-04
void FUN_0124b838(undefined8 param_1,undefined4 *param_2)

{
  (*(code *)PTR__ZN10CUIUtility12PlaySystemSeEib_02ca9ee8)(*param_2,0);
  return;
}

// ==== Framework::CSTLStringUtility_Base<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > >::Format(char const*, ...)
// vaddr 0x115100c | ghidra 0x125100c | size 428 | symbol _ZN9Framework22CSTLStringUtility_BaseINSt6__ndk112basic_stringIcNS1_11char_traitsIcEENS_13CSTLAllocatorIcNS_22CSTLStringAllocatorInfEEEEEE6FormatEPKcz | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Type propagation algorithm not settling */

void _ZN9Framework22CSTLStringUtility_BaseINSt6__ndk112basic_stringIcNS1_11char_traitsIcEENS_13CSTLAllocatorIcNS_22CSTLStringAllocatorInfEEEEEE6FormatEPKcz
               (ulong *param_1,long param_2,undefined8 param_3,undefined8 param_4,undefined8 param_5
               ,undefined8 param_6,undefined8 param_7,undefined8 param_8,undefined8 param_9)

{
  int iVar1;
  long lVar2;
  ulong uVar3;
  ulong uVar4;
  long lVar5;
  ulong uVar6;
  byte *pbVar7;
  undefined1 auStack_f0 [8];
  undefined8 uStack_e8;
  undefined8 uStack_e0;
  undefined8 uStack_d8;
  undefined8 uStack_d0;
  undefined8 uStack_c8;
  undefined8 uStack_c0;
  undefined8 uStack_b8;
  undefined1 *puStack_b0;
  undefined1 **ppuStack_a8;
  undefined1 *puStack_a0;
  undefined8 uStack_98;
  undefined1 *puStack_90;
  undefined1 **ppuStack_88;
  undefined1 *puStack_80;
  undefined8 uStack_78;
  
  param_1[1] = 0;
  param_1[2] = 0;
  *param_1 = 0;
  if (param_2 == 0) {
    return;
  }
  uStack_78 = 0xffffff80ffffffc8;
  uStack_e8 = param_3;
  uStack_e0 = param_4;
  uStack_d8 = param_5;
  uStack_d0 = param_6;
  uStack_c8 = param_7;
  uStack_c0 = param_8;
  uStack_b8 = param_9;
  puStack_90 = (undefined1 *)register0x00000008;
  ppuStack_88 = &puStack_b0;
  puStack_80 = auStack_f0;
  iVar1 = vsnprintf(0,0,param_2,&puStack_90);
  if (iVar1 == 0) {
    return;
  }
  lVar2 = Framework::gMAllocHigh(unsigned long, unsigned long)((long)iVar1 + 2,0x10);
  uStack_98 = 0xffffff80ffffffc8;
  puStack_b0 = (undefined1 *)register0x00000008;
  ppuStack_a8 = &puStack_b0;
  puStack_a0 = auStack_f0;
  vsnprintf(lVar2,(long)iVar1 + 1,param_2,&puStack_b0);
  uVar3 = strlen(lVar2);
  uVar6 = (ulong)(byte)*param_1;
  if (((byte)*param_1 & 1) == 0) {
    uVar4 = 0x16;
    lVar5 = uVar3 - 0x16;
    if (uVar3 < 0x16 || lVar5 == 0) {
code_r0x01251100:
      if ((uVar6 & 1) == 0) {
        pbVar7 = (byte *)((long)param_1 + 1);
      }
      else {
        pbVar7 = (byte *)param_1[2];
      }
      if (uVar3 != 0) {
        memmove(pbVar7,lVar2,uVar3);
      }
      pbVar7[uVar3] = 0;
      if ((*param_1 & 1) == 0) {
        *(byte *)param_1 = (byte)(uVar3 << 1);
      }
      else {
        param_1[1] = uVar3;
      }
      goto joined_r0x012511b0;
    }
  }
  else {
    uVar6 = *param_1;
    uVar4 = (uVar6 & 0xfffffffffffffffe) - 1;
    lVar5 = uVar3 - uVar4;
    if (uVar3 < uVar4 || lVar5 == 0) goto code_r0x01251100;
  }
  if ((uVar6 & 1) == 0) {
    uVar6 = (ulong)(((uint)uVar6 & 0xfe) >> 1);
  }
  else {
    uVar6 = param_1[1];
  }
  string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(param_1,uVar4,lVar5,uVar6,0,uVar6,uVar3,lVar2);
joined_r0x012511b0:
  if (lVar2 != 0) {
    operator delete[](void*)(lVar2);
  }
  return;
}

// ==== Framework::CSTLStringUtility_Base<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > >::Split(std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > const&, std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > const&)
// vaddr 0x12328f4 | ghidra 0x13328f4 | size 1284 | symbol _ZN9Framework22CSTLStringUtility_BaseINSt6__ndk112basic_stringIcNS1_11char_traitsIcEENS_13CSTLAllocatorIcNS_22CSTLStringAllocatorInfEEEEEE5SplitERKS8_SB_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework22CSTLStringUtility_BaseINSt6__ndk112basic_stringIcNS1_11char_traitsIcEENS_13CSTLAllocatorIcNS_22CSTLStringAllocatorInfEEEEEE5SplitERKS8_SB_
               (undefined8 *param_1,byte *param_2,byte *param_3)

{
  byte *pbVar1;
  byte *pbVar2;
  ulong *puVar3;
  byte bVar4;
  byte *pbVar5;
  byte *pbVar6;
  ulong uVar7;
  byte *pbVar8;
  long lVar9;
  byte *pbVar10;
  ulong uVar11;
  ulong uVar12;
  ulong uVar13;
  ulong uVar14;
  ulong uStack_78;
  ulong uStack_70;
  ulong uStack_68;
  
  param_1[1] = 0;
  param_1[2] = 0;
  *param_1 = 0;
  bVar4 = *param_3;
  uVar7 = *(ulong *)(param_3 + 8);
  uVar12 = 0;
  do {
    uVar14 = (ulong)(*param_2 >> 1);
    pbVar5 = param_2 + 1;
    if ((*param_2 & 1) != 0) {
      uVar14 = *(ulong *)(param_2 + 8);
      pbVar5 = *(byte **)(param_2 + 0x10);
    }
    uVar13 = (ulong)(bVar4 >> 1);
    pbVar6 = param_3 + 1;
    if ((bVar4 & 1) != 0) {
      uVar13 = uVar7;
      pbVar6 = *(byte **)(param_3 + 0x10);
    }
    uVar7 = uVar14 - uVar12;
    if ((uVar14 < uVar12) || (uVar7 < uVar13)) break;
    uVar11 = uVar12;
    if (uVar13 != 0) {
      pbVar10 = pbVar5 + uVar12;
      pbVar2 = pbVar5 + uVar14;
      pbVar8 = pbVar2;
      if (((long)uVar13 <= (long)pbVar2 - (long)pbVar10) && (pbVar2 + (1 - uVar13) != pbVar10)) {
        lVar9 = (uVar13 - (long)pbVar5) - uVar14;
        do {
          while (*pbVar10 == *pbVar6) {
            uVar14 = 1;
            do {
              pbVar8 = pbVar10;
              if (uVar13 == uVar14) goto code_r0x0133294c;
              pbVar8 = pbVar10 + uVar14;
              pbVar1 = pbVar6 + uVar14;
              uVar14 = uVar14 + 1;
            } while (*pbVar8 == *pbVar1);
            pbVar1 = pbVar10 + lVar9;
            pbVar8 = pbVar2;
            pbVar10 = pbVar10 + 1;
            if (pbVar1 == (byte *)0x0) goto code_r0x0133294c;
          }
          pbVar10 = pbVar10 + 1;
          pbVar8 = pbVar2;
        } while (pbVar10 + lVar9 != (byte *)0x1);
      }
code_r0x0133294c:
      if (pbVar2 == pbVar8) break;
      uVar11 = (long)pbVar8 - (long)pbVar5;
    }
    if (uVar11 == 0xffffffffffffffff) break;
    if (uVar11 - uVar12 <= uVar7) {
      uVar7 = uVar11 - uVar12;
    }
    uStack_70 = 0;
    uStack_68 = 0;
    uStack_78 = 0;
    if (uVar7 < 0x17) {
      uStack_78 = (uVar7 & 0x7f) << 1;
      uVar13 = (ulong)&uStack_78 | 1;
      if (uVar7 != 0) goto code_r0x013329f4;
    }
    else {
      uVar14 = uVar7 + 0x10 & 0xfffffffffffffff0;
      if (uVar14 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
      }
      uVar13 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar14,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
      if (uVar13 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
      }
      uStack_78 = uVar14 | 1;
      uStack_70 = uVar7;
      uStack_68 = uVar13;
code_r0x013329f4:
      memcpy(uVar13,pbVar5 + uVar12,uVar7);
    }
    *(undefined1 *)(uVar13 + uVar7) = 0;
    puVar3 = (ulong *)param_1[1];
    if (puVar3 < (ulong *)param_1[2]) {
      if (puVar3 == (ulong *)0x0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
      }
      uVar7 = uStack_68;
      uVar12 = uStack_70;
      puVar3[1] = 0;
      puVar3[2] = 0;
      *puVar3 = 0;
      if ((uStack_78 & 1) == 0) {
        puVar3[2] = uStack_68;
        puVar3[1] = uStack_70;
        *puVar3 = uStack_78;
      }
      else {
        if (uStack_70 < 0x17) {
          uVar13 = (long)puVar3 + 1;
          *(char *)puVar3 = (char)(uStack_70 << 1);
          if (uStack_70 != 0) goto code_r0x01332af4;
        }
        else {
          uVar14 = uStack_70 + 0x10 & 0xfffffffffffffff0;
          if (uVar14 == 0) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
          }
          uVar13 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar14,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
          if (uVar13 == 0) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
          }
          puVar3[1] = uVar12;
          puVar3[2] = uVar13;
          *puVar3 = uVar14 | 1;
code_r0x01332af4:
          memcpy(uVar13,uVar7,uVar12);
        }
        *(undefined1 *)(uVar13 + uVar12) = 0;
      }
      param_1[1] = param_1[1] + 0x18;
    }
    else {
      void std::__ndk1::vector<string, Framework::CSTLAllocator<string, Framework::CSTLVectorAllocatorInf> >::__emplace_back_slow_path<string >(string&&)(param_1,&uStack_78);
    }
    if ((uStack_78 & 1) != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_68);
    }
    bVar4 = *param_3;
    uVar7 = *(ulong *)(param_3 + 8);
    uVar12 = (ulong)(bVar4 >> 1);
    if ((bVar4 & 1) != 0) {
      uVar12 = uVar7;
    }
    uVar12 = uVar12 + uVar11;
  } while( true );
  uStack_70 = 0;
  uStack_68 = 0;
  uStack_78 = 0;
  if (uVar7 < 0x17) {
    uVar13 = (ulong)&uStack_78 | 1;
    uStack_78 = (ulong)(byte)((char)uVar7 * '\x02');
    if (uVar7 != 0) goto code_r0x01332ca8;
  }
  else {
    uVar14 = uVar7 + 0x10 & 0xfffffffffffffff0;
    if (uVar14 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
    }
    uVar13 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar14,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
    if (uVar13 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    }
    uStack_78 = uVar14 | 1;
    uStack_70 = uVar7;
    uStack_68 = uVar13;
code_r0x01332ca8:
    memcpy(uVar13,pbVar5 + uVar12,uVar7);
  }
  *(undefined1 *)(uVar13 + uVar7) = 0;
  puVar3 = (ulong *)param_1[1];
  if ((ulong *)param_1[2] <= puVar3) {
    void std::__ndk1::vector<string, Framework::CSTLAllocator<string, Framework::CSTLVectorAllocatorInf> >::__push_back_slow_path<string >(string&&)(param_1,&uStack_78);
    goto joined_r0x01332d18;
  }
  if (puVar3 == (ulong *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
  }
  uVar7 = uStack_68;
  uVar12 = uStack_70;
  puVar3[1] = 0;
  puVar3[2] = 0;
  *puVar3 = 0;
  if ((uStack_78 & 1) == 0) {
    puVar3[2] = uStack_68;
    puVar3[1] = uStack_70;
    *puVar3 = uStack_78;
  }
  else {
    if (uStack_70 < 0x17) {
      uVar13 = (long)puVar3 + 1;
      *(char *)puVar3 = (char)(uStack_70 << 1);
      if (uStack_70 != 0) goto code_r0x01332da8;
    }
    else {
      uVar14 = uStack_70 + 0x10 & 0xfffffffffffffff0;
      if (uVar14 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
      }
      uVar13 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar14,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
      if (uVar13 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
      }
      puVar3[1] = uVar12;
      puVar3[2] = uVar13;
      *puVar3 = uVar14 | 1;
code_r0x01332da8:
      memcpy(uVar13,uVar7,uVar12);
    }
    *(undefined1 *)(uVar13 + uVar12) = 0;
  }
  param_1[1] = param_1[1] + 0x18;
joined_r0x01332d18:
  if ((uStack_78 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_68);
  }
  return;
}

// ==== Framework::CSTLStringUtility_Base<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > >::Substr(std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > const&, unsigned long, unsigned long)
// vaddr 0x12540c4 | ghidra 0x13540c4 | size 308 | symbol _ZN9Framework22CSTLStringUtility_BaseINSt6__ndk112basic_stringIcNS1_11char_traitsIcEENS_13CSTLAllocatorIcNS_22CSTLStringAllocatorInfEEEEEE6SubstrERKS8_mm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework22CSTLStringUtility_BaseINSt6__ndk112basic_stringIcNS1_11char_traitsIcEENS_13CSTLAllocatorIcNS_22CSTLStringAllocatorInfEEEEEE6SubstrERKS8_mm
               (ulong *param_1,byte *param_2,long param_3,ulong param_4)

{
  ulong uVar1;
  byte *pbVar2;
  bool bVar3;
  ulong uVar4;
  ulong uVar5;
  ulong uStack_58;
  ulong uStack_50;
  ulong uStack_48;
  
  uStack_48 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  *param_1 = 0;
  uStack_58 = 0;
  uStack_50 = 0;
  pbVar2 = *(byte **)(param_2 + 0x10);
  bVar3 = (*param_2 & 1) != 0;
  uVar5 = (ulong)(*param_2 >> 1);
  if (bVar3) {
    uVar5 = *(ulong *)(param_2 + 8);
  }
  if (!bVar3) {
    pbVar2 = param_2 + 1;
  }
  uVar1 = uVar5 - param_3;
  if (param_4 <= uVar5 - param_3) {
    uVar1 = param_4;
  }
  if (uVar1 < 0x17) {
    uVar4 = (ulong)&uStack_58 | 1;
    uStack_58 = (uVar1 & 0x7f) << 1;
    if (uVar1 == 0) goto code_r0x013541a4;
  }
  else {
    uVar5 = uVar1 + 0x10 & 0xfffffffffffffff0;
    if (uVar5 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
    }
    uVar4 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar5,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
    if (uVar4 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    }
    uStack_58 = uVar5 | 1;
    uStack_50 = uVar1;
    uStack_48 = uVar4;
  }
  memcpy(uVar4,pbVar2 + param_3,uVar1);
code_r0x013541a4:
  *(undefined1 *)(uVar4 + uVar1) = 0;
  if ((*param_1 & 1) == 0) {
    *(undefined2 *)param_1 = 0;
  }
  else {
    *(undefined1 *)param_1[2] = 0;
    param_1[1] = 0;
  }
  string::reserve(unsigned long)(param_1,0);
  param_1[2] = uStack_48;
  param_1[1] = uStack_50;
  *param_1 = uStack_58;
  return;
}

// ==== Framework::CSTLStringUtility_Base<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > >::GetExtension(std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > const&, std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > const&)
// vaddr 0x1340d3c | ghidra 0x1440d3c | size 424 | symbol _ZN9Framework22CSTLStringUtility_BaseINSt6__ndk112basic_stringIcNS1_11char_traitsIcEENS_13CSTLAllocatorIcNS_22CSTLStringAllocatorInfEEEEEE12GetExtensionERKS8_SB_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework22CSTLStringUtility_BaseINSt6__ndk112basic_stringIcNS1_11char_traitsIcEENS_13CSTLAllocatorIcNS_22CSTLStringAllocatorInfEEEEEE12GetExtensionERKS8_SB_
               (ulong *param_1,byte *param_2,byte *param_3)

{
  byte *pbVar1;
  byte *pbVar2;
  byte *pbVar3;
  long lVar4;
  long lVar5;
  byte *pbVar6;
  byte *pbVar7;
  long lVar8;
  char *pcVar9;
  ulong uVar10;
  ulong uVar11;
  
  uVar10 = *(ulong *)(param_2 + 8);
  pbVar2 = *(byte **)(param_2 + 0x10);
  uVar11 = *(ulong *)(param_3 + 8);
  pbVar3 = *(byte **)(param_3 + 0x10);
  if ((*param_2 & 1) == 0) {
    pbVar2 = param_2 + 1;
    uVar10 = (ulong)(*param_2 >> 1);
  }
  if ((*param_3 & 1) == 0) {
    pbVar3 = param_3 + 1;
    uVar11 = (ulong)(*param_3 >> 1);
  }
  pbVar1 = pbVar2 + uVar10;
  pbVar6 = pbVar1;
  if ((uVar11 != 0) && ((long)uVar11 <= (long)uVar10)) {
    pbVar7 = pbVar1;
    while (pbVar2 + (uVar11 - 1) != pbVar7) {
      pbVar7 = pbVar7 + -1;
      if (*pbVar7 == pbVar3[uVar11 - 1]) {
        lVar8 = 0;
        do {
          if (1 - uVar11 == lVar8) {
            pbVar6 = pbVar7 + lVar8;
            goto code_r0x01440df0;
          }
          lVar5 = lVar8 + -1;
          lVar4 = lVar8 + (uVar11 - 2);
          lVar8 = lVar8 + -1;
        } while (pbVar7[lVar5] == pbVar3[lVar4]);
      }
    }
  }
code_r0x01440df0:
  if ((uVar11 != 0 && pbVar6 == pbVar1) || ((long)pbVar6 - (long)pbVar2 == -1)) {
    param_1[1] = 0;
    param_1[2] = 0;
    *param_1 = 0;
    return;
  }
  lVar8 = ((long)pbVar6 - (long)pbVar2) + 1;
  uVar10 = uVar10 - lVar8;
  param_1[1] = 0;
  param_1[2] = 0;
  *param_1 = 0;
  if (uVar10 < 0x17) {
    pcVar9 = (char *)((long)param_1 + 1);
    *(char *)param_1 = (char)uVar10 * '\x02';
    if (uVar10 == 0) goto code_r0x01440ec4;
  }
  else {
    uVar11 = uVar10 + 0x10 & 0xfffffffffffffff0;
    if (uVar11 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
    }
    pcVar9 = (char *)Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar11,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
    if (pcVar9 == (char *)0x0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    }
    param_1[1] = uVar10;
    param_1[2] = (ulong)pcVar9;
    *param_1 = uVar11 | 1;
  }
  memcpy(pcVar9,pbVar2 + lVar8,uVar10);
code_r0x01440ec4:
  pcVar9[uVar10] = '\0';
  return;
}

// ==== Framework::CSTLStringUtility_Base<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > >::IntToString(int)
// vaddr 0x138ddc8 | ghidra 0x148ddc8 | size 260 | symbol _ZN9Framework22CSTLStringUtility_BaseINSt6__ndk112basic_stringIcNS1_11char_traitsIcEENS_13CSTLAllocatorIcNS_22CSTLStringAllocatorInfEEEEEE11IntToStringEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework22CSTLStringUtility_BaseINSt6__ndk112basic_stringIcNS1_11char_traitsIcEENS_13CSTLAllocatorIcNS_22CSTLStringAllocatorInfEEEEEE11IntToStringEi
               (ulong *param_1)

{
  ulong uVar1;
  ulong uVar2;
  ulong uVar3;
  ulong uVar4;
  byte abStack_48 [16];
  ulong uStack_38;
  
  std::__ndk1::to_string(int)(abStack_48);
  param_1[1] = 0;
  param_1[2] = 0;
  uVar1 = (ulong)abStack_48 | 1;
  if ((abStack_48[0] & 1) != 0) {
    uVar1 = uStack_38;
  }
  *param_1 = 0;
  uVar2 = strlen(uVar1);
  if (uVar2 < 0x17) {
    uVar3 = (long)param_1 + 1;
    *(char *)param_1 = (char)(uVar2 << 1);
    if (uVar2 == 0) goto code_r0x0148dea4;
  }
  else {
    uVar4 = uVar2 + 0x10 & 0xfffffffffffffff0;
    if (uVar4 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
    }
    uVar3 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar4,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
    if (uVar3 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    }
    param_1[1] = uVar2;
    param_1[2] = uVar3;
    *param_1 = uVar4 | 1;
  }
  memcpy(uVar3,uVar1,uVar2);
code_r0x0148dea4:
  *(undefined1 *)(uVar3 + uVar2) = 0;
  if ((abStack_48[0] & 1) != 0) {
    operator delete(void*)(uStack_38);
  }
  return;
}

// ==== Framework::CSTLStringUtility_Base<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > >::AToF(std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > const&)
// vaddr 0x13b45b4 | ghidra 0x14b45b4 | size 176 | symbol _ZN9Framework22CSTLStringUtility_BaseINSt6__ndk112basic_stringIcNS1_11char_traitsIcEENS_13CSTLAllocatorIcNS_22CSTLStringAllocatorInfEEEEEE4AToFERKS8_ | lib libSOA-3.7.0.so | 2026-10-04
float _ZN9Framework22CSTLStringUtility_BaseINSt6__ndk112basic_stringIcNS1_11char_traitsIcEENS_13CSTLAllocatorIcNS_22CSTLStringAllocatorInfEEEEEE4AToFERKS8_
                (byte *param_1)

{
  byte bVar1;
  double dVar2;
  int iVar3;
  ulong uVar4;
  byte *pbVar5;
  
  uVar4 = Framework::CSTLStringUtility_Base<string >::IsDigits(string const&, bool, float*, double*)(param_1,0,0,0);
  bVar1 = *param_1;
  if ((uVar4 & 1) == 0) {
    pbVar5 = *(byte **)(param_1 + 0x10);
    if ((bVar1 & 1) == 0) {
      pbVar5 = param_1 + 1;
    }
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0xeb,&UNK_0280bba5/*"Illegal strings.[%s]"*/,pbVar5);
    return 0.0;
  }
  uVar4 = *(ulong *)(param_1 + 8);
  pbVar5 = *(byte **)(param_1 + 0x10);
  if ((bVar1 & 1) == 0) {
    pbVar5 = param_1 + 1;
    uVar4 = (ulong)(bVar1 >> 1);
  }
  if (((2 < uVar4) && (*pbVar5 == 0x30)) && (pbVar5[1] == 0x78)) {
    iVar3 = strtoul(pbVar5,0,0);
    return (float)iVar3;
  }
  dVar2 = (double)strtod(pbVar5,0);
  return (float)dVar2;
}

// ==== Framework::CSTLStringUtility_Base<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > >::IsDigits(std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > const&, bool, float*, double*)
// vaddr 0x13b4664 | ghidra 0x14b4664 | size 1204 | symbol _ZN9Framework22CSTLStringUtility_BaseINSt6__ndk112basic_stringIcNS1_11char_traitsIcEENS_13CSTLAllocatorIcNS_22CSTLStringAllocatorInfEEEEEE8IsDigitsERKS8_bPfPd | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN9Framework22CSTLStringUtility_BaseINSt6__ndk112basic_stringIcNS1_11char_traitsIcEENS_13CSTLAllocatorIcNS_22CSTLStringAllocatorInfEEEEEE8IsDigitsERKS8_bPfPd
          (ulong *param_1,ulong param_2,float *param_3,double *param_4)

{
  byte bVar1;
  byte bVar2;
  bool bVar3;
  int iVar4;
  ulong uVar5;
  byte *pbVar6;
  ulong uVar7;
  uint uVar8;
  ulong uVar9;
  ulong uVar10;
  float fVar11;
  double dVar12;
  ulong auStack_a0 [10];
  char *pcStack_48;
  
  pcStack_48 = (char *)0x0;
  if ((param_2 & 1) == 0) {
    pbVar6 = (byte *)param_1[2];
    if ((*param_1 & 1) == 0) {
      pbVar6 = (byte *)((long)param_1 + 1);
    }
    dVar12 = (double)strtod(pbVar6,&pcStack_48);
    if ((pcStack_48 == (char *)0x0) || (*pcStack_48 == '\0')) {
      if (param_3 != (float *)0x0) {
        *param_3 = (float)dVar12;
      }
      if (param_4 == (double *)0x0) {
        return 1;
      }
      *param_4 = dVar12;
      return 1;
    }
  }
  else {
    auStack_a0[7] = 0;
    auStack_a0[8] = 0;
    auStack_a0[6] = 0;
    if ((*param_1 & 1) == 0) {
      auStack_a0[8] = param_1[2];
      auStack_a0[7] = param_1[1];
      auStack_a0[6] = *param_1;
    }
    else {
      uVar5 = param_1[1];
      uVar7 = param_1[2];
      if (uVar5 < 0x17) {
        uVar9 = (ulong)(auStack_a0 + 6) | 1;
        auStack_a0[6] = (uVar5 & 0x7f) << 1;
        if (uVar5 != 0) goto code_r0x014b477c;
      }
      else {
        uVar10 = uVar5 + 0x10 & 0xfffffffffffffff0;
        if (uVar10 == 0) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
        }
        uVar9 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar10,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
        if (uVar9 == 0) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
        }
        auStack_a0[6] = uVar10 | 1;
        auStack_a0[7] = uVar5;
        auStack_a0[8] = uVar9;
code_r0x014b477c:
        memcpy(uVar9,uVar7,uVar5);
      }
      *(undefined1 *)(uVar9 + uVar5) = 0;
    }
    auStack_a0[4] = 0;
    auStack_a0[5] = 0;
    auStack_a0[2] = 0;
    auStack_a0[0] = 0;
    auStack_a0[1] = 0;
    auStack_a0[3] = 0x2002;
    Framework::CSTLStringUtility_Base<string >::ReplaceSelf(string&, string const&, string const&, bool*)(auStack_a0 + 6,auStack_a0 + 3,auStack_a0,0);
    if ((auStack_a0[0] & 1) != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(auStack_a0[2]);
    }
    if ((auStack_a0[3] & 1) != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(auStack_a0[5]);
    }
    auStack_a0[4] = 0;
    auStack_a0[5] = 0;
    auStack_a0[2] = 0;
    auStack_a0[0] = 0;
    auStack_a0[1] = 0;
    auStack_a0[3] = 0x902;
    Framework::CSTLStringUtility_Base<string >::ReplaceSelf(string&, string const&, string const&, bool*)(auStack_a0 + 6,auStack_a0 + 3,auStack_a0,0);
    if ((auStack_a0[0] & 1) != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(auStack_a0[2]);
    }
    if ((auStack_a0[3] & 1) != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(auStack_a0[5]);
    }
    uVar5 = (ulong)(auStack_a0 + 6) | 1;
    if ((auStack_a0[6] & 1) != 0) {
      uVar5 = auStack_a0[8];
    }
    dVar12 = (double)strtod(uVar5,&pcStack_48);
    if ((pcStack_48 == (char *)0x0) || (*pcStack_48 == '\0')) {
      if (param_3 != (float *)0x0) {
        *param_3 = (float)dVar12;
      }
      if (param_4 != (double *)0x0) {
        *param_4 = dVar12;
      }
      bVar3 = true;
    }
    else {
      bVar3 = false;
    }
    if ((auStack_a0[6] & 1) != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(auStack_a0[8]);
    }
    if (bVar3) {
      return 1;
    }
  }
  bVar1 = (byte)*param_1;
  uVar5 = (ulong)(bVar1 >> 1);
  if ((bVar1 & 1) != 0) {
    uVar5 = param_1[1];
  }
  if (2 < uVar5) {
    pbVar6 = (byte *)param_1[2];
    if ((bVar1 & 1) == 0) {
      pbVar6 = (byte *)((long)param_1 + 1);
    }
    if (*pbVar6 == 0x30) {
      bVar3 = pbVar6[1] == 0x78;
      goto code_r0x014b48dc;
    }
  }
  bVar3 = false;
code_r0x014b48dc:
  uVar7 = 2;
  if (!bVar3) {
    uVar7 = 0;
  }
  if (uVar7 < uVar5) {
    pbVar6 = (byte *)param_1[2];
    if ((bVar1 & 1) == 0) {
      pbVar6 = (byte *)((long)param_1 + 1);
    }
    if (bVar3) {
      if ((param_2 & 1) == 0) {
        uVar8 = 3;
        do {
          if (0x3b < (int)(char)pbVar6[uVar7] - 0x2bU) {
            return 0;
          }
          if ((1L << ((ulong)((int)(char)pbVar6[uVar7] - 0x2bU) & 0x3f) & 0xfc000000fc07fedU) == 0)
          {
            return 0;
          }
          uVar7 = (ulong)uVar8;
          uVar8 = uVar8 + 1;
        } while (uVar7 < uVar5);
      }
      else {
        uVar8 = 3;
        do {
          bVar2 = pbVar6[uVar7];
          if ((((0x3b < (int)(char)bVar2 - 0x2bU) ||
               ((1L << ((ulong)((int)(char)bVar2 - 0x2bU) & 0x3f) & 0xfc000000fc07fedU) == 0)) &&
              (bVar2 != 0x20)) && (bVar2 != 9)) {
            return 0;
          }
          uVar7 = (ulong)uVar8;
          uVar8 = uVar8 + 1;
        } while (uVar7 < uVar5);
      }
    }
    else if ((param_2 & 1) == 0) {
      uVar10 = 1;
      do {
        if (0x39 < pbVar6[uVar7]) {
          return 0;
        }
        if ((1L << ((long)(char)pbVar6[uVar7] & 0x3fU) & 0x3ff680000000000U) == 0) {
          return 0;
        }
        bVar3 = uVar10 < uVar5;
        uVar7 = uVar10;
        uVar10 = (ulong)((int)uVar10 + 1);
      } while (bVar3);
    }
    else {
      uVar10 = 1;
      do {
        bVar2 = pbVar6[uVar7];
        uVar8 = (int)(char)bVar2 - 0x2b;
        if (uVar8 < 0x3c) {
          if ((1L << ((ulong)uVar8 & 0x3f) & 0x7fedU) == 0) {
            if ((1L << ((ulong)uVar8 & 0x3f) & 0xfc000000fc00000U) != 0) {
              return 0;
            }
            goto code_r0x014b49a8;
          }
        }
        else {
code_r0x014b49a8:
          if ((bVar2 != 0x20) && (bVar2 != 9)) {
            return 0;
          }
        }
        bVar3 = uVar10 < uVar5;
        uVar7 = uVar10;
        uVar10 = (ulong)((int)uVar10 + 1);
      } while (bVar3);
    }
  }
  if (param_3 != (float *)0x0) {
    pbVar6 = (byte *)param_1[2];
    if ((bVar1 & 1) == 0) {
      pbVar6 = (byte *)((long)param_1 + 1);
    }
    if (((uVar5 < 3) || (*pbVar6 != 0x30)) || (pbVar6[1] != 0x78)) {
      dVar12 = (double)strtod(pbVar6,0);
      fVar11 = (float)dVar12;
    }
    else {
      iVar4 = strtoul(pbVar6,0,0);
      fVar11 = (float)iVar4;
    }
    *param_3 = fVar11;
  }
  if (param_4 != (double *)0x0) {
    uVar5 = param_1[1];
    pbVar6 = (byte *)param_1[2];
    if (((byte)*param_1 & 1) == 0) {
      pbVar6 = (byte *)((long)param_1 + 1);
      uVar5 = (ulong)(byte)((byte)*param_1 >> 1);
    }
    if (((uVar5 < 3) || (*pbVar6 != 0x30)) || (pbVar6[1] != 0x78)) {
      dVar12 = (double)strtod(pbVar6,0);
    }
    else {
      uVar5 = strtoull(pbVar6,0,0x10);
      dVar12 = (double)uVar5;
    }
    *param_4 = (double)(float)dVar12;
  }
  return 1;
}

// ==== Framework::CSTLStringUtility_Base<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > >::AToDoubleWithTrimming(std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > const&)
// vaddr 0x17e8070 | ghidra 0x18e8070 | size 576 | symbol _ZN9Framework22CSTLStringUtility_BaseINSt6__ndk112basic_stringIcNS1_11char_traitsIcEENS_13CSTLAllocatorIcNS_22CSTLStringAllocatorInfEEEEEE21AToDoubleWithTrimmingERKS8_ | lib libSOA-3.7.0.so | 2026-10-04
undefined1  [16]
_ZN9Framework22CSTLStringUtility_BaseINSt6__ndk112basic_stringIcNS1_11char_traitsIcEENS_13CSTLAllocatorIcNS_22CSTLStringAllocatorInfEEEEEE21AToDoubleWithTrimmingERKS8_
          (ulong *param_1)

{
  ulong uVar1;
  ulong uVar2;
  byte *pbVar3;
  char *pcVar4;
  ulong uVar5;
  double dVar6;
  undefined1 auVar7 [16];
  ulong auStack_80 [8];
  char *pcStack_40;
  
  uVar2 = Framework::CSTLStringUtility_Base<string >::IsDigits(string const&, bool, float*, double*)(param_1,1,0,0);
  if ((uVar2 & 1) == 0) {
    pbVar3 = (byte *)param_1[2];
    if ((*param_1 & 1) == 0) {
      pbVar3 = (byte *)((long)param_1 + 1);
    }
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x12f,&UNK_0280bba5/*"Illegal strings.[%s]"*/,pbVar3);
    dVar6 = 0.0;
    goto code_r0x018e8298;
  }
  auStack_80[7] = 0;
  pcStack_40 = (char *)0x0;
  auStack_80[6] = 0;
  if ((*param_1 & 1) == 0) {
    pcStack_40 = (char *)param_1[2];
    auStack_80[7] = param_1[1];
    auStack_80[6] = *param_1;
  }
  else {
    uVar2 = param_1[1];
    uVar1 = param_1[2];
    if (uVar2 < 0x17) {
      pcVar4 = (char *)((ulong)(auStack_80 + 6) | 1);
      auStack_80[6] = (uVar2 & 0x7f) << 1;
      if (uVar2 != 0) goto code_r0x018e8178;
    }
    else {
      uVar5 = uVar2 + 0x10 & 0xfffffffffffffff0;
      if (uVar5 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
      }
      pcVar4 = (char *)Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar5,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
      if (pcVar4 == (char *)0x0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
      }
      auStack_80[6] = uVar5 | 1;
      auStack_80[7] = uVar2;
      pcStack_40 = pcVar4;
code_r0x018e8178:
      memcpy(pcVar4,uVar1,uVar2);
    }
    pcVar4[uVar2] = '\0';
  }
  auStack_80[4] = 0;
  auStack_80[5] = 0;
  auStack_80[2] = 0;
  auStack_80[0] = 0;
  auStack_80[1] = 0;
  auStack_80[3] = 0x2002;
  Framework::CSTLStringUtility_Base<string >::ReplaceSelf(string&, string const&, string const&, bool*)(auStack_80 + 6,auStack_80 + 3,auStack_80,0);
  if ((auStack_80[0] & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(auStack_80[2]);
  }
  if ((auStack_80[3] & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(auStack_80[5]);
  }
  auStack_80[4] = 0;
  auStack_80[5] = 0;
  auStack_80[2] = 0;
  auStack_80[0] = 0;
  auStack_80[1] = 0;
  auStack_80[3] = 0x902;
  Framework::CSTLStringUtility_Base<string >::ReplaceSelf(string&, string const&, string const&, bool*)(auStack_80 + 6,auStack_80 + 3,auStack_80,0);
  if ((auStack_80[0] & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(auStack_80[2]);
  }
  if ((auStack_80[3] & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(auStack_80[5]);
  }
  pcVar4 = (char *)((ulong)(auStack_80 + 6) | 1);
  uVar2 = auStack_80[6] >> 1 & 0x7f;
  if ((auStack_80[6] & 1) != 0) {
    pcVar4 = pcStack_40;
    uVar2 = auStack_80[7];
  }
  if (((uVar2 < 3) || (*pcVar4 != '0')) || (pcVar4[1] != 'x')) {
    dVar6 = (double)strtod(pcVar4,0);
  }
  else {
    uVar2 = strtoull(pcVar4,0,0x10);
    dVar6 = (double)uVar2;
  }
  if ((auStack_80[6] & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(pcStack_40);
  }
  dVar6 = (double)(float)dVar6;
code_r0x018e8298:
  auVar7._8_8_ = 0;
  auVar7._0_8_ = dVar6;
  return auVar7;
}

// ==== Aska::PathUtil::GetTailName(char const*, unsigned long*)
// vaddr 0x1f55408 | ghidra 0x2055408 | size 132 | symbol _ZN4Aska8PathUtil11GetTailNameEPKcPm | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska8PathUtil11GetTailNameEPKcPm(long param_1,long *param_2)

{
  long lVar1;
  uint uVar2;
  long lVar3;
  long lVar4;
  
  if (param_1 != 0) {
    uVar2 = strlen(param_1);
    lVar3 = ((ulong)uVar2 << 0x20) + 0x100000000;
    lVar4 = (long)(int)uVar2;
    do {
      if (lVar4 < 1) {
        if (param_2 == (long *)0x0) {
          return param_1;
        }
        *param_2 = (long)(int)uVar2;
        return param_1;
      }
      lVar1 = param_1 + lVar4;
      lVar3 = lVar3 + -0x100000000;
      lVar4 = lVar4 + -1;
    } while (*(char *)(lVar1 + -1) != '/');
    if (param_2 != (long *)0x0) {
      *param_2 = (long)(((ulong)uVar2 << 0x20) - lVar3) >> 0x20;
    }
    param_1 = param_1 + (lVar3 >> 0x20);
  }
  return param_1;
}

// ==== Aska::PathUtil::GetExtentionName(char const*, unsigned long*)
// vaddr 0x1f55524 | ghidra 0x2055524 | size 188 | symbol _ZN4Aska8PathUtil16GetExtentionNameEPKcPm | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska8PathUtil16GetExtentionNameEPKcPm(long param_1,long *param_2)

{
  char *pcVar1;
  uint uVar2;
  long lVar3;
  long lVar4;
  
  if (param_1 != 0) {
    uVar2 = strlen(param_1);
    lVar4 = 0;
    lVar3 = -((ulong)uVar2 << 0x20);
    do {
      if ((int)uVar2 + lVar4 < 1) goto code_r0x020555a0;
      pcVar1 = (char *)(param_1 + (int)uVar2 + -1 + lVar4);
      lVar3 = lVar3 + 0x100000000;
      lVar4 = lVar4 + -1;
    } while (*pcVar1 != '.');
    if (((int)(uVar2 + (int)lVar4 + 1) < 2) ||
       (*(char *)(param_1 + (-0x100000000 - lVar3 >> 0x20)) == '/')) {
code_r0x020555a0:
      if (param_2 == (long *)0x0) {
        param_1 = 0;
      }
      else {
        param_1 = 0;
        *param_2 = 0;
      }
    }
    else {
      if (param_2 != (long *)0x0) {
        *param_2 = (long)-(int)lVar4;
      }
      param_1 = param_1 + (-lVar3 >> 0x20);
    }
  }
  return param_1;
}

// ==== Aska::PathUtil::CatenatePathName(char const*, char const*, char*, unsigned long)
// vaddr 0x1f5563c | ghidra 0x205563c | size 332 | symbol _ZN4Aska8PathUtil16CatenatePathNameEPKcS2_Pcm | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska8PathUtil16CatenatePathNameEPKcS2_Pcm
               (long param_1,long param_2,undefined1 *param_3,ulong param_4)

{
  bool bVar1;
  long lVar2;
  ulong uVar3;
  long lVar4;
  long lVar5;
  
  if (param_1 == 0) {
    lVar2 = 0;
joined_r0x020556a8:
    bVar1 = false;
    lVar4 = 0;
  }
  else {
    lVar2 = strlen(param_1);
    if (lVar2 == 0) goto joined_r0x020556a8;
    bVar1 = *(char *)(param_1 + lVar2) != '/';
    lVar4 = lVar2;
    if (bVar1) {
      lVar4 = lVar2 + 1;
    }
  }
  if (param_2 == 0) {
    lVar5 = 0;
    if (lVar2 != 0) goto code_r0x020556c4;
  }
  else {
    lVar5 = strlen(param_2);
    lVar4 = lVar5 + lVar4;
    if (lVar5 != 0 || lVar2 != 0) {
code_r0x020556c4:
      if (param_4 < lVar4 + 1U) {
        return lVar4;
      }
      *param_3 = 0;
      if (lVar2 != 0) {
        uVar3 = strlen(param_1);
        if (uVar3 < param_4) {
          strcat(param_3,param_1);
        }
        else {
          raise(5);
        }
        if (bVar1) {
          if (param_4 < 2) {
            raise(5);
          }
          else {
            lVar2 = strlen(param_3);
            *(undefined2 *)(param_3 + lVar2) = 0x2f;
          }
        }
      }
      if (lVar5 == 0) {
        return lVar4;
      }
      uVar3 = strlen(param_2);
      if (uVar3 < param_4) {
        strcat(param_3,param_2);
        return lVar4;
      }
      raise(5);
      return lVar4;
    }
  }
  return -0x3bd;
}

// ==== Aska::PathUtil::CatenatePathName(char const*, char const*)
// vaddr 0x1f55788 | ghidra 0x2055788 | size 296 | symbol _ZN4Aska8PathUtil16CatenatePathNameEPKcS2_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska8PathUtil16CatenatePathNameEPKcS2_(long *param_1,undefined8 param_2,undefined8 param_3)

{
  ulong uVar1;
  int iVar2;
  char cVar3;
  bool bVar4;
  long lVar5;
  long lVar6;
  int *piVar7;
  long lStack_38;
  
  lVar5 = Aska::PathUtil::CatenatePathName(char const*, char const*, char*, unsigned long)(param_2,param_3,0,0);
  if (lVar5 < 0) {
    *param_1 = 0;
    param_1[1] = 0;
    return;
  }
  uVar1 = lVar5 + 1;
  piVar7 = (int *)0x0;
  lStack_38 = 0;
  if (uVar1 < 2) {
code_r0x0205584c:
    *param_1 = 0;
    param_1[1] = 0;
    if (piVar7 == (int *)0x0) {
      bVar4 = true;
      goto joined_r0x02055884;
    }
  }
  else {
    lVar5 = operator new[](unsigned long, std::nothrow_t const&)(uVar1,PTR__ZSt7nothrow_02cb9a80);
    if (lVar5 == 0) {
      piVar7 = (int *)0x0;
      goto code_r0x0205584c;
    }
    lStack_38 = 0;
    piVar7 = (int *)Aska::TSharedPointerCode::CreateCounter(int)(0);
    if (piVar7 == (int *)0x0) goto code_r0x0205584c;
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar7,0x10);
      if (bVar4) {
        *piVar7 = *piVar7 + 1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
    lStack_38 = lVar5;
    if ((lVar5 == 0) || (lVar6 = Aska::PathUtil::CatenatePathName(char const*, char const*, char*, unsigned long)(param_2,param_3,lVar5,uVar1), lVar6 < 0))
    goto code_r0x0205584c;
    *param_1 = lVar5;
    param_1[1] = (long)piVar7;
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar7,0x10);
      if (bVar4) {
        *piVar7 = *piVar7 + 1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
  }
  do {
    iVar2 = *piVar7;
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar7,0x10);
    if (bVar4) {
      *piVar7 = iVar2 + -1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
  if (iVar2 != 1) {
    return;
  }
  bVar4 = false;
joined_r0x02055884:
  if (lStack_38 != 0) {
    operator delete[](void*)();
  }
  if (!bVar4) {
    Aska::TSharedPointerCode::DeleteCounter(int*)(piVar7);
  }
  return;
}

// ==== Aska::StringUtility::SeekStartOfNextLine(char*)
// vaddr 0x1f7de20 | ghidra 0x207de20 | size 92 | symbol _ZN4Aska13StringUtility19SeekStartOfNextLineEPc | lib libSOA-3.7.0.so | 2026-10-04
char * _ZN4Aska13StringUtility19SeekStartOfNextLineEPc(char *param_1)

{
  char cVar1;
  char cVar2;
  char *pcVar3;
  
  cVar1 = *param_1;
  do {
    pcVar3 = param_1;
    cVar2 = cVar1;
    if (cVar2 == '\0') {
      return pcVar3;
    }
    param_1 = pcVar3 + 1;
    cVar1 = *param_1;
  } while ((cVar2 == '\r') != (cVar2 != '\n'));
  if (((cVar1 == '\n') || (cVar1 == '\r')) && (cVar1 != cVar2)) {
    param_1 = pcVar3 + 2;
  }
  return param_1;
}

// ==== Aska::StringUtility::SeekStartOfNextLine(char const*)
// vaddr 0x1f7de7c | ghidra 0x207de7c | size 92 | symbol _ZN4Aska13StringUtility19SeekStartOfNextLineEPKc | lib libSOA-3.7.0.so | 2026-10-04
char * _ZN4Aska13StringUtility19SeekStartOfNextLineEPKc(char *param_1)

{
  char cVar1;
  char cVar2;
  char *pcVar3;
  
  cVar1 = *param_1;
  do {
    pcVar3 = param_1;
    cVar2 = cVar1;
    if (cVar2 == '\0') {
      return pcVar3;
    }
    param_1 = pcVar3 + 1;
    cVar1 = *param_1;
  } while ((cVar2 == '\r') != (cVar2 != '\n'));
  if (((cVar1 == '\n') || (cVar1 == '\r')) && (cVar1 != cVar2)) {
    param_1 = pcVar3 + 2;
  }
  return param_1;
}

// ==== Aska::StringUtility::CheckForSingleLineComment(char const*)
// vaddr 0x1f7ded8 | ghidra 0x207ded8 | size 44 | symbol _ZN4Aska13StringUtility25CheckForSingleLineCommentEPKc | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska13StringUtility25CheckForSingleLineCommentEPKc(char *param_1)

{
  if (((param_1 != (char *)0x0) && (*param_1 == '/')) && (param_1[1] == '/')) {
    return 1;
  }
  return 0;
}

// ==== Aska::StringUtility::CopyLine(char*, int, char const*)
// vaddr 0x1f7df04 | ghidra 0x207df04 | size 88 | symbol _ZN4Aska13StringUtility8CopyLineEPciPKc | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska13StringUtility8CopyLineEPciPKc(long param_1,int param_2,char *param_3)

{
  long lVar1;
  char cVar2;
  
  cVar2 = *param_3;
  if (cVar2 == '\0') {
    return 0;
  }
  lVar1 = 0;
  while( true ) {
    if (param_2 == (int)lVar1) {
      return lVar1;
    }
    if ((cVar2 == '\r') == (cVar2 != '\n')) break;
    *(char *)(param_1 + lVar1) = cVar2;
    cVar2 = param_3[lVar1 + 1];
    lVar1 = lVar1 + 1;
    if (cVar2 == '\0') {
      return lVar1;
    }
  }
  return lVar1;
}

// ==== Aska::StringUtility::ConvertFullPathToDirectory(char*, int, char const*)
// vaddr 0x1f7e0c4 | ghidra 0x207e0c4 | size 260 | symbol _ZN4Aska13StringUtility26ConvertFullPathToDirectoryEPciPKc | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Possible PIC construction at 0x0207e168: Changing call to branch */
/* WARNING: Removing unreachable block (ram,0x0207e16c) */
/* WARNING: Removing unreachable block (ram,0x0207e174) */

void _ZN4Aska13StringUtility26ConvertFullPathToDirectoryEPciPKc
               (undefined1 *param_1,int param_2,long param_3)

{
  ulong uVar1;
  ulong uVar2;
  ulong uVar3;
  ulong uVar4;
  long lVar5;
  
  uVar2 = strrchr(param_3,0x5c);
  uVar3 = strrchr(param_3,0x2f);
  if (uVar2 != 0 || uVar3 != 0) {
    if (uVar2 < uVar3) {
      lVar5 = uVar3 - param_3;
    }
    else {
      lVar5 = uVar2 - param_3;
    }
    uVar3 = (ulong)param_2;
    uVar2 = uVar3;
    if (lVar5 + 1 < (long)uVar3) {
      uVar2 = lVar5 + 1;
    }
    uVar4 = strlen(param_3);
    uVar1 = uVar4 + 1;
    if (uVar2 == 0xffffffffffffffff) {
      uVar2 = uVar3;
      if (uVar1 <= uVar3) {
        uVar2 = uVar1;
      }
    }
    else {
      if (uVar1 != uVar2) {
        uVar4 = uVar1;
      }
      if (uVar1 <= uVar2) {
        uVar2 = uVar4;
      }
      if (uVar3 <= uVar2) goto code_r0x011b27a0;
    }
    (*(code *)PTR_strncpy_02ca6608)(param_1,param_3,uVar2);
    return;
  }
  if (param_2 != 0) {
    *param_1 = 0;
    return;
  }
code_r0x011b27a0:
  (*(code *)PTR_raise_02c913c0)(5);
  return;
}

// ==== Aska::StringUtility::ConvertBinaryToHexBaseAscii(signed char const*, unsigned long, char*, unsigned int)
// vaddr 0x1f7eb9c | ghidra 0x207eb9c | size 120 | symbol _ZN4Aska13StringUtility27ConvertBinaryToHexBaseAsciiEPKamPcj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13StringUtility27ConvertBinaryToHexBaseAsciiEPKamPcj
               (undefined1 *param_1,long param_2,long param_3,ulong param_4)

{
  long lVar1;
  long lVar2;
  
  if (param_2 != 0) {
    param_4 = param_4 & 0xffffffff;
    lVar1 = param_3;
    lVar2 = param_2;
    do {
      __aska_snprintf_s(char*, unsigned long, unsigned long, char const*, ...)(lVar1,param_4,0xffffffffffffffff,&UNK_02a3d098/*"%02x"*/,*param_1);
      lVar2 = lVar2 + -1;
      lVar1 = lVar1 + 2;
      param_4 = param_4 - 2;
      param_1 = param_1 + 1;
    } while (lVar2 != 0);
  }
  *(undefined1 *)(param_3 + param_2 * 2) = 0;
  return;
}

// ==== Aska::StringUtility::Utf8ToMultiByte(char const*, char*, unsigned int)
// vaddr 0x1f7f290 | ghidra 0x207f290 | size 116 | symbol _ZN4Aska13StringUtility15Utf8ToMultiByteEPKcPcj | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZN4Aska13StringUtility15Utf8ToMultiByteEPKcPcj(undefined8 param_1,long param_2,uint param_3)

{
  ulong uVar1;
  long lVar2;
  ulong uVar3;
  
  if (((param_2 == 0) && (param_3 != 0)) || ((param_2 != 0 && (param_3 == 0)))) {
    uVar3 = 0xfffffc43;
  }
  else {
    lVar2 = strlen(param_1);
    uVar1 = lVar2 + 1;
    if ((param_2 != 0) || (uVar3 = uVar1, param_3 != 0)) {
      uVar3 = (ulong)param_3;
      if (uVar1 <= param_3) {
        uVar3 = uVar1;
      }
      strncpy(param_2,param_1,uVar3);
    }
  }
  return uVar3 & 0xffffffff;
}
