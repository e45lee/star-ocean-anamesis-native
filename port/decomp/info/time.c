// port/decomp/info/time.c: Ghidra decompiles for the info subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-08 15:19 UTC: tools/decomp.sh '--into' 'info/time' 'CTimeUtility::str2time_t'

// ==== CTimeUtility::str2time_t(char const*, long, bool, bool)
// vaddr 0x1dc6370 | ghidra 0x1ec6370 | size 1628 | symbol _ZN12CTimeUtility10str2time_tEPKclbb | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN12CTimeUtility10str2time_tEPKclbb(long param_1,undefined8 param_2,ulong param_3,byte param_4)

{
  char *pcVar1;
  char cVar2;
  long lVar3;
  long lVar4;
  undefined1 *puVar5;
  undefined1 *puVar6;
  ulong uVar7;
  undefined8 uVar8;
  undefined1 *puVar9;
  ulong uVar10;
  ulong uVar11;
  float fVar12;
  ulong uStack_100;
  ulong uStack_f8;
  ulong uStack_f0;
  undefined8 uStack_e8;
  int iStack_e0;
  int iStack_dc;
  int iStack_d8;
  int iStack_d4;
  undefined8 uStack_cc;
  undefined1 auStack_b0 [64];
  undefined1 *apuStack_70 [6];
  
  if (param_1 == 0) {
    return param_2;
  }
  lVar3 = strchr(param_1,0x2d);
  lVar4 = strchr(param_1,0x2f);
  pcVar1 = "// ::";
  if ((lVar3 == 0 & param_4) == 0 && lVar4 == 0) {
    pcVar1 = "-- ::";
  }
  strcpy(auStack_b0,param_1);
  puVar5 = (undefined1 *)strchr(auStack_b0,(long)*pcVar1);
  if (puVar5 == (undefined1 *)0x0) {
    return param_2;
  }
  cVar2 = pcVar1[1];
  *puVar5 = 0;
  apuStack_70[0] = auStack_b0;
  puVar6 = (undefined1 *)strchr(puVar5 + 1,(long)cVar2);
  if (puVar6 == (undefined1 *)0x0) {
    return param_2;
  }
  cVar2 = pcVar1[2];
  puVar9 = puVar6 + 1;
  *puVar6 = 0;
  apuStack_70[1] = puVar5 + 1;
  puVar5 = (undefined1 *)strchr(puVar9,(long)cVar2);
  if (puVar5 == (undefined1 *)0x0) {
    lVar3 = 2;
  }
  else {
    cVar2 = pcVar1[3];
    puVar6 = puVar5 + 1;
    *puVar5 = 0;
    apuStack_70[2] = puVar9;
    puVar5 = (undefined1 *)strchr(puVar6,(long)cVar2);
    if (puVar5 == (undefined1 *)0x0) {
      lVar3 = 3;
      puVar9 = puVar6;
    }
    else {
      cVar2 = pcVar1[4];
      puVar9 = puVar5 + 1;
      *puVar5 = 0;
      apuStack_70[3] = puVar6;
      puVar5 = (undefined1 *)strchr(puVar9,(long)cVar2);
      if (puVar5 == (undefined1 *)0x0) {
        lVar3 = 4;
      }
      else {
        cVar2 = pcVar1[5];
        *puVar5 = 0;
        apuStack_70[4] = puVar9;
        puVar6 = (undefined1 *)strchr(puVar5 + 1,(long)cVar2);
        if (puVar6 != (undefined1 *)0x0) {
          *puVar6 = 0;
        }
        lVar3 = 5;
        puVar9 = puVar5 + 1;
      }
    }
  }
  apuStack_70[lVar3] = puVar9;
  if ((param_3 & 1) == 0) {
    uStack_100 = 0;
    uStack_f8 = 0;
    uStack_f0 = 0;
    uVar7 = strlen(apuStack_70[5]);
    if (uVar7 < 0x17) {
      uVar10 = (ulong)&uStack_100 | 1;
      uStack_100 = CONCAT71(uStack_100._1_7_,(char)(uVar7 << 1));
      if (uVar7 != 0) goto code_r0x01ec6554;
    }
    else {
      uVar11 = uVar7 + 0x10 & 0xfffffffffffffff0;
      if (uVar11 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
      }
      uVar10 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar11,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
      if (uVar10 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
      }
      uStack_100 = uVar11 | 1;
      uStack_f8 = uVar7;
      uStack_f0 = uVar10;
code_r0x01ec6554:
      memcpy(uVar10,apuStack_70[5],uVar7);
    }
    *(undefined1 *)(uVar10 + uVar7) = 0;
    fVar12 = (float)Framework::CSTLStringUtility_Base<string >::AToF(string const&)(&uStack_100);
    uStack_e8 = CONCAT44(uStack_e8._4_4_,(int)fVar12);
    if ((uStack_100 & 1) != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_f0);
    }
    puVar5 = apuStack_70[4];
    uStack_100 = 0;
    uStack_f8 = 0;
    uStack_f0 = 0;
    uVar7 = strlen(apuStack_70[4]);
    if (uVar7 < 0x17) {
      uVar10 = (ulong)&uStack_100 | 1;
      uStack_100 = CONCAT71(uStack_100._1_7_,(char)(uVar7 << 1));
      if (uVar7 != 0) goto code_r0x01ec6624;
    }
    else {
      uVar11 = uVar7 + 0x10 & 0xfffffffffffffff0;
      if (uVar11 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
      }
      uVar10 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar11,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
      if (uVar10 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
      }
      uStack_100 = uVar11 | 1;
      uStack_f8 = uVar7;
      uStack_f0 = uVar10;
code_r0x01ec6624:
      memcpy(uVar10,puVar5,uVar7);
    }
    *(undefined1 *)(uVar10 + uVar7) = 0;
    fVar12 = (float)Framework::CSTLStringUtility_Base<string >::AToF(string const&)(&uStack_100);
    uStack_e8 = CONCAT44((int)fVar12,(undefined4)uStack_e8);
    if ((uStack_100 & 1) != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_f0);
    }
    puVar5 = apuStack_70[3];
    uStack_100 = 0;
    uStack_f8 = 0;
    uStack_f0 = 0;
    uVar7 = strlen(apuStack_70[3]);
    if (uVar7 < 0x17) {
      uVar10 = (ulong)&uStack_100 | 1;
      uStack_100 = CONCAT71(uStack_100._1_7_,(char)(uVar7 << 1));
      if (uVar7 != 0) goto code_r0x01ec66f4;
    }
    else {
      uVar11 = uVar7 + 0x10 & 0xfffffffffffffff0;
      if (uVar11 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
      }
      uVar10 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar11,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
      if (uVar10 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
      }
      uStack_100 = uVar11 | 1;
      uStack_f8 = uVar7;
      uStack_f0 = uVar10;
code_r0x01ec66f4:
      memcpy(uVar10,puVar5,uVar7);
    }
    *(undefined1 *)(uVar10 + uVar7) = 0;
    fVar12 = (float)Framework::CSTLStringUtility_Base<string >::AToF(string const&)(&uStack_100);
    iStack_e0 = (int)fVar12;
    if ((uStack_100 & 1) != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_f0);
    }
  }
  else {
    uStack_e8 = 0;
    iStack_e0 = 0;
  }
  puVar5 = apuStack_70[2];
  uStack_f8 = 0;
  uStack_f0 = 0;
  uStack_100 = 0;
  uVar7 = strlen(apuStack_70[2]);
  if (uVar7 < 0x17) {
    uVar10 = (ulong)&uStack_100 | 1;
    uStack_100 = CONCAT71(uStack_100._1_7_,(char)(uVar7 << 1));
    if (uVar7 != 0) goto code_r0x01ec67c4;
  }
  else {
    uVar11 = uVar7 + 0x10 & 0xfffffffffffffff0;
    if (uVar11 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
    }
    uVar10 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar11,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
    if (uVar10 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    }
    uStack_100 = uVar11 | 1;
    uStack_f8 = uVar7;
    uStack_f0 = uVar10;
code_r0x01ec67c4:
    memcpy(uVar10,puVar5,uVar7);
  }
  *(undefined1 *)(uVar10 + uVar7) = 0;
  fVar12 = (float)Framework::CSTLStringUtility_Base<string >::AToF(string const&)(&uStack_100);
  iStack_dc = (int)fVar12;
  if ((uStack_100 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_f0);
  }
  puVar5 = apuStack_70[1];
  uStack_f8 = 0;
  uStack_f0 = 0;
  uStack_100 = 0;
  uVar7 = strlen(apuStack_70[1]);
  if (uVar7 < 0x17) {
    uVar10 = (ulong)&uStack_100 | 1;
    uStack_100 = CONCAT71(uStack_100._1_7_,(char)(uVar7 << 1));
    if (uVar7 != 0) goto code_r0x01ec6894;
  }
  else {
    uVar11 = uVar7 + 0x10 & 0xfffffffffffffff0;
    if (uVar11 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
    }
    uVar10 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar11,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
    if (uVar10 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    }
    uStack_100 = uVar11 | 1;
    uStack_f8 = uVar7;
    uStack_f0 = uVar10;
code_r0x01ec6894:
    memcpy(uVar10,puVar5,uVar7);
  }
  *(undefined1 *)(uVar10 + uVar7) = 0;
  fVar12 = (float)Framework::CSTLStringUtility_Base<string >::AToF(string const&)(&uStack_100);
  iStack_d8 = (int)fVar12 + -1;
  if ((uStack_100 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_f0);
  }
  puVar5 = apuStack_70[0];
  uStack_100 = 0;
  uStack_f8 = 0;
  uStack_f0 = 0;
  uVar7 = strlen(apuStack_70[0]);
  if (uVar7 < 0x17) {
    uVar10 = (ulong)&uStack_100 | 1;
    uStack_100 = CONCAT71(uStack_100._1_7_,(char)(uVar7 << 1));
    if (uVar7 == 0) goto code_r0x01ec6978;
  }
  else {
    uVar11 = uVar7 + 0x10 & 0xfffffffffffffff0;
    if (uVar11 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
    }
    uVar10 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar11,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
    if (uVar10 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    }
    uStack_100 = uVar11 | 1;
    uStack_f8 = uVar7;
    uStack_f0 = uVar10;
  }
  memcpy(uVar10,puVar5,uVar7);
code_r0x01ec6978:
  *(undefined1 *)(uVar10 + uVar7) = 0;
  fVar12 = (float)Framework::CSTLStringUtility_Base<string >::AToF(string const&)(&uStack_100);
  iStack_d4 = (int)fVar12 + -0x76c;
  if ((uStack_100 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_f0);
  }
  uStack_cc = 0;
  uVar8 = mktime(&uStack_e8);
  return uVar8;
}
