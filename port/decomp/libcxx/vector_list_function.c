// port/decomp/libcxx/vector_list_function.c: Ghidra decompiles for the libcxx subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-04 05:18 UTC: tools/decomp.sh '--into' 'libcxx/vector_list_function' 'vector<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,Framework::CSTLAllocator<char,Framework::CSTLStringAllocatorInf>>,Framework::CSTLAllocator<.*__push_back_slow_path<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,Framework::CSTLAllocator<char,Framework::CSTLStringAllocatorInf>>>\(' 'list<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,Framework::CSTLAllocator<char,Framework::CSTLStringAllocatorInf>>,Framework::CSTLAllocator<.*::(emplace_back<char_const\*&>|remove)\(' '__func<std::__ndk1::function<void\(bool,long\)>,std::__ndk1::allocator<std::__ndk1::function<void\(bool,long\)>>,void\(bool,unsigned_long\)>::__clone'

// ==== void std::__ndk1::vector<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> >, Framework::CSTLAllocator<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> >, Framework::CSTLVectorAllocatorInf> >::__push_back_slow_path<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > >(std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> >&&)
// vaddr 0x11a929c | ghidra 0x12a929c | size 556 | symbol _ZNSt6__ndk16vectorINS_12basic_stringIcNS_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEENS5_IS8_NS4_22CSTLVectorAllocatorInfEEEE21__push_back_slow_pathIS8_EEvOT_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZNSt6__ndk16vectorINS_12basic_stringIcNS_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEENS5_IS8_NS4_22CSTLVectorAllocatorInfEEEE21__push_back_slow_pathIS8_EEvOT_
               (long *param_1,ulong *param_2)

{
  ulong *puVar1;
  long lVar2;
  ulong uVar3;
  long lVar4;
  ulong uVar5;
  ulong uVar6;
  ulong *puVar7;
  long lVar8;
  long lStack_78;
  ulong *puStack_70;
  ulong *puStack_68;
  long lStack_60;
  long *plStack_58;
  
  plStack_58 = param_1 + 2;
  lVar4 = param_1[1] - *param_1 >> 3;
  lVar2 = *plStack_58 - *param_1 >> 3;
  if ((ulong)(lVar2 * -0x5555555555555555) < 0x555555555555555) {
    uVar5 = lVar4 * -0x5555555555555555 + 1;
    uVar3 = lVar2 * 0x5555555555555556;
    if (uVar5 <= uVar3) {
      uVar5 = uVar3;
    }
    if (uVar5 != 0) goto code_r0x012a9324;
    lVar2 = 0;
  }
  else {
    uVar5 = 0xaaaaaaaaaaaaaaa;
code_r0x012a9324:
    lStack_60 = 0;
    lVar2 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar5 * 0x18,&UNK_027dc536/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Vector.h"*/,0x20);
    if (lVar2 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    }
  }
  puVar7 = (ulong *)(lVar2 + lVar4 * 8);
  lStack_60 = lVar2 + uVar5 * 0x18;
  lStack_78 = lVar2;
  puStack_70 = puVar7;
  puStack_68 = puVar7;
  if (puVar7 == (ulong *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
  }
  puVar7[1] = 0;
  puVar7[2] = 0;
  *puVar7 = 0;
  if ((*param_2 & 1) == 0) {
    puVar7[2] = param_2[2];
    uVar5 = *param_2;
    puVar7[1] = param_2[1];
    *puVar7 = uVar5;
    puStack_68 = puVar7;
    goto code_r0x012a9458;
  }
  uVar5 = param_2[1];
  uVar3 = param_2[2];
  if (uVar5 < 0x17) {
    lVar8 = (long)puVar7 + 1;
    *(char *)puVar7 = (char)(uVar5 << 1);
    if (uVar5 != 0) goto code_r0x012a9440;
  }
  else {
    uVar6 = uVar5 + 0x10 & 0xfffffffffffffff0;
    if (uVar6 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
    }
    lVar8 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar6,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
    if (lVar8 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    }
    lVar2 = lVar2 + lVar4 * 8;
    *(ulong *)(lVar2 + 8) = uVar5;
    *(long *)(lVar2 + 0x10) = lVar8;
    *puVar7 = uVar6 | 1;
code_r0x012a9440:
    memcpy(lVar8,uVar3,uVar5);
  }
  *(undefined1 *)(lVar8 + uVar5) = 0;
code_r0x012a9458:
  puStack_68 = puStack_68 + 3;
  std::__ndk1::vector<string, Framework::CSTLAllocator<string, Framework::CSTLVectorAllocatorInf> >::__swap_out_circular_buffer(std::__ndk1::__split_buffer<string, Framework::CSTLAllocator<string, Framework::CSTLVectorAllocatorInf>&>&)(param_1,&lStack_78);
  puVar7 = puStack_70;
  while (puVar1 = puStack_68, puVar1 != puVar7) {
    puStack_68 = puVar1 + -3;
    if ((puVar1[-3] & 1) != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puVar1[-1]);
    }
  }
  if (lStack_78 != 0) {
    puStack_68 = puVar1;
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)();
  }
  return;
}

// ==== void std::__ndk1::list<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> >, Framework::CSTLAllocator<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> >, Framework::CSTLListAllocatorInf> >::emplace_back<char const*&>(char const*&)
// vaddr 0x17ff528 | ghidra 0x18ff528 | size 300 | symbol _ZNSt6__ndk14listINS_12basic_stringIcNS_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEENS5_IS8_NS4_20CSTLListAllocatorInfEEEE12emplace_backIJRPKcEEEvDpOT_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZNSt6__ndk14listINS_12basic_stringIcNS_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEENS5_IS8_NS4_20CSTLListAllocatorInfEEEE12emplace_backIJRPKcEEEvDpOT_
               (long *param_1,undefined8 *param_2)

{
  long *plVar1;
  ulong uVar2;
  long lVar3;
  undefined8 uVar4;
  ulong uVar5;
  
  plVar1 = (long *)Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(0x28,&UNK_027e7774/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_List.h"*/,0x20);
  if (plVar1 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
  }
  uVar4 = *param_2;
  plVar1[3] = 0;
  plVar1[4] = 0;
  plVar1[2] = 0;
  uVar2 = strlen(uVar4);
  if (uVar2 < 0x17) {
    lVar3 = (long)plVar1 + 0x11;
    *(char *)(plVar1 + 2) = (char)(uVar2 << 1);
    if (uVar2 == 0) goto code_r0x018ff61c;
  }
  else {
    uVar5 = uVar2 + 0x10 & 0xfffffffffffffff0;
    if (uVar5 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
    }
    lVar3 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar5,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
    if (lVar3 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    }
    plVar1[3] = uVar2;
    plVar1[4] = lVar3;
    plVar1[2] = uVar5 | 1;
  }
  memcpy(lVar3,uVar4,uVar2);
code_r0x018ff61c:
  *(undefined1 *)(lVar3 + uVar2) = 0;
  plVar1[1] = (long)param_1;
  lVar3 = *param_1;
  *plVar1 = lVar3;
  *(long **)(lVar3 + 8) = plVar1;
  *param_1 = (long)plVar1;
  param_1[2] = param_1[2] + 1;
  return;
}

// ==== std::__ndk1::list<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> >, Framework::CSTLAllocator<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> >, Framework::CSTLListAllocatorInf> >::remove(std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > const&)
// vaddr 0x17ffa8c | ghidra 0x18ffa8c | size 656 | symbol _ZNSt6__ndk14listINS_12basic_stringIcNS_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEENS5_IS8_NS4_20CSTLListAllocatorInfEEEE6removeERKS8_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZNSt6__ndk14listINS_12basic_stringIcNS_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEENS5_IS8_NS4_20CSTLListAllocatorInfEEEE6removeERKS8_
               (long ******param_1,byte *param_2)

{
  long *****ppppplVar1;
  byte *pbVar2;
  byte bVar3;
  byte bVar4;
  bool bVar5;
  long ******pppppplVar6;
  int iVar7;
  byte *pbVar8;
  long lVar9;
  byte *pbVar10;
  long *****ppppplVar11;
  long ******pppppplVar12;
  long ******pppppplVar13;
  long ******pppppplVar14;
  long *****ppppplStack_68;
  long *****ppppplStack_60;
  long lStack_58;
  
  ppppplStack_68 = (long *****)&ppppplStack_68;
  ppppplStack_60 = (long *****)&ppppplStack_68;
  lStack_58 = 0;
  pppppplVar13 = (long ******)param_1[1];
  if (param_1 != pppppplVar13) {
    pppppplVar12 = &ppppplStack_68;
    do {
      bVar3 = *(byte *)(pppppplVar13 + 2);
      bVar4 = *param_2;
      ppppplVar1 = (long *****)(ulong)(bVar3 >> 1);
      if ((bVar3 & 1) != 0) {
        ppppplVar1 = pppppplVar13[3];
      }
      ppppplVar11 = (long *****)(ulong)(bVar4 >> 1);
      if ((bVar4 & 1) != 0) {
        ppppplVar11 = *(long ******)(param_2 + 8);
      }
      if (ppppplVar1 == ppppplVar11) {
        ppppplVar11 = pppppplVar13[4];
        if ((bVar3 & 1) == 0) {
          ppppplVar11 = (long *****)((long)pppppplVar13 + 0x11);
        }
        pbVar2 = param_2 + 1;
        if ((bVar4 & 1) != 0) {
          pbVar2 = *(byte **)(param_2 + 0x10);
        }
        if ((bVar3 & 1) == 0) {
          if (ppppplVar1 != (long *****)0x0) {
            pbVar8 = (byte *)((long)pppppplVar13 + 0x11);
            lVar9 = -(long)(ulong)(bVar3 >> 1);
            pbVar10 = pbVar2;
            do {
              if (*pbVar8 != *pbVar10) goto code_r0x018ffc94;
              pbVar8 = pbVar8 + 1;
              lVar9 = lVar9 + 1;
              pbVar10 = pbVar10 + 1;
            } while (lVar9 != 0);
          }
        }
        else if ((ppppplVar1 != (long *****)0x0) &&
                (iVar7 = memcmp(ppppplVar11,pbVar2,ppppplVar1), iVar7 != 0))
        goto code_r0x018ffc94;
        for (pppppplVar14 = (long ******)pppppplVar13[1]; param_1 != pppppplVar14;
            pppppplVar14 = (long ******)pppppplVar14[1]) {
          bVar3 = *(byte *)(pppppplVar14 + 2);
          ppppplVar11 = (long *****)(ulong)(bVar3 >> 1);
          if ((bVar3 & 1) != 0) {
            ppppplVar11 = pppppplVar14[3];
          }
          if (ppppplVar11 != ppppplVar1) {
code_r0x018ffb78:
            bVar5 = true;
            pppppplVar6 = pppppplVar14;
            goto joined_r0x018ffb84;
          }
          ppppplVar11 = pppppplVar14[4];
          if ((bVar3 & 1) == 0) {
            ppppplVar11 = (long *****)((long)pppppplVar14 + 0x11);
          }
          if ((bVar3 & 1) == 0) {
            if (ppppplVar1 != (long *****)0x0) {
              pbVar8 = (byte *)((long)pppppplVar14 + 0x11);
              lVar9 = -(long)(ulong)(bVar3 >> 1);
              pbVar10 = pbVar2;
              do {
                if (*pbVar8 != *pbVar10) goto code_r0x018ffb78;
                pbVar8 = pbVar8 + 1;
                lVar9 = lVar9 + 1;
                pbVar10 = pbVar10 + 1;
              } while (lVar9 != 0);
            }
          }
          else if ((ppppplVar1 != (long *****)0x0) &&
                  (iVar7 = memcmp(ppppplVar11,pbVar2,ppppplVar1), iVar7 != 0))
          goto code_r0x018ffb78;
        }
        bVar5 = false;
        pppppplVar6 = param_1;
joined_r0x018ffb84:
        if (pppppplVar13 != pppppplVar6) {
          if (&ppppplStack_68 != param_1) {
            lVar9 = 0;
            pppppplVar12 = pppppplVar13;
            do {
              pppppplVar12 = (long ******)pppppplVar12[1];
              lVar9 = lVar9 + 1;
            } while (pppppplVar12 != pppppplVar6);
            param_1[2] = (long *****)((long)param_1[2] - lVar9);
            lStack_58 = lStack_58 + lVar9;
          }
          pppppplVar12 = (long ******)*pppppplVar14;
          (*pppppplVar13)[1] = (long ****)pppppplVar12[1];
          *pppppplVar12[1] = (long ****)*pppppplVar13;
          ppppplStack_68[1] = (long ****)pppppplVar13;
          *pppppplVar13 = ppppplStack_68;
          ppppplStack_68 = (long *****)pppppplVar12;
          pppppplVar12[1] = (long *****)&ppppplStack_68;
        }
        pppppplVar13 = pppppplVar6;
        if (bVar5) goto code_r0x018ffc94;
      }
      else {
code_r0x018ffc94:
        pppppplVar14 = (long ******)pppppplVar13[1];
      }
      pppppplVar13 = pppppplVar14;
    } while (param_1 != pppppplVar13);
    if (lStack_58 != 0) {
      (*ppppplStack_60)[1] = (long ***)pppppplVar12[1];
      *pppppplVar12[1] = *ppppplStack_60;
      lStack_58 = 0;
      pppppplVar13 = (long ******)ppppplStack_60;
      while (pppppplVar13 != &ppppplStack_68) {
        pppppplVar12 = (long ******)pppppplVar13[1];
        if (((ulong)pppppplVar13[2] & 1) != 0) {
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(pppppplVar13[4]);
        }
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(pppppplVar13);
        pppppplVar13 = pppppplVar12;
      }
    }
  }
  return;
}

// ==== std::__ndk1::__function::__func<std::__ndk1::function<void (bool, long)>, std::__ndk1::allocator<std::__ndk1::function<void (bool, long)> >, void (bool, unsigned long)>::__clone() const
// vaddr 0x1816130 | ghidra 0x1916130 | size 124 | symbol _ZNKSt6__ndk110__function6__funcINS_8functionIFvblEEENS_9allocatorIS4_EEFvbmEE7__cloneEv | lib libSOA-3.7.0.so | 2026-10-04
long * _ZNKSt6__ndk110__function6__funcINS_8functionIFvblEEENS_9allocatorIS4_EEFvbmEE7__cloneEv
                 (long param_1)

{
  long *plVar1;
  long *plVar2;
  long lVar3;
  
  plVar1 = (long *)operator new(unsigned long)(0x40);
  *plVar1 = (long)(
                  PTR__ZTVNSt6__ndk110__function6__funcINS_8functionIFvblEEENS_9allocatorIS4_EEFvbmEEE_02cbd988
                  + 0x10);
  plVar2 = *(long **)(param_1 + 0x30);
  if (plVar2 == (long *)0x0) {
    plVar1[6] = 0;
  }
  else if ((long *)(param_1 + 0x10) == plVar2) {
    plVar1[6] = (long)(plVar1 + 2);
    (**(code **)(*plVar2 + 0x18))();
  }
  else {
    lVar3 = (**(code **)(*plVar2 + 0x10))();
    plVar1[6] = lVar3;
  }
  return plVar1;
}

// ==== std::__ndk1::__function::__func<std::__ndk1::function<void (bool, long)>, std::__ndk1::allocator<std::__ndk1::function<void (bool, long)> >, void (bool, unsigned long)>::__clone(std::__ndk1::__function::__base<void (bool, unsigned long)>*) const
// vaddr 0x18161ac | ghidra 0x19161ac | size 108 | symbol _ZNKSt6__ndk110__function6__funcINS_8functionIFvblEEENS_9allocatorIS4_EEFvbmEE7__cloneEPNS0_6__baseIS7_EE | lib libSOA-3.7.0.so | 2026-10-04
void _ZNKSt6__ndk110__function6__funcINS_8functionIFvblEEENS_9allocatorIS4_EEFvbmEE7__cloneEPNS0_6__baseIS7_EE
               (long param_1,long *param_2)

{
  long lVar1;
  long *plVar2;
  
  *param_2 = (long)(
                   PTR__ZTVNSt6__ndk110__function6__funcINS_8functionIFvblEEENS_9allocatorIS4_EEFvbmEEE_02cbd988
                   + 0x10);
  plVar2 = *(long **)(param_1 + 0x30);
  if (plVar2 == (long *)0x0) {
    param_2[6] = 0;
    return;
  }
  if ((long *)(param_1 + 0x10) != plVar2) {
    lVar1 = (**(code **)(*plVar2 + 0x10))(plVar2);
    param_2[6] = lVar1;
    return;
  }
  param_2[6] = (long)(param_2 + 2);
                    /* WARNING: Could not recover jumptable at 0x01916214. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(**(long **)(param_1 + 0x30) + 0x18))();
  return;
}
