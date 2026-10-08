// port/decomp/master/stringdb.c: Ghidra decompiles for the master subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-08 13:02 UTC: tools/decomp.sh '--into' 'master/stringdb' 'StringDB'

// ==== CParameterManager::pStringDB() const
// vaddr 0x16ed064 | ghidra 0x17ed064 | size 8 | symbol _ZNK17CParameterManager9pStringDBEv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK17CParameterManager9pStringDBEv(long param_1)

{
  return *(undefined8 *)(param_1 + 0x48);
}

// ==== CMasterParameterBaseSqlite_Simple<StringDBEelement>::ClearCache()
// vaddr 0x16f5384 | ghidra 0x17f5384 | size 200 | symbol _ZN33CMasterParameterBaseSqlite_SimpleI16StringDBEelementE10ClearCacheEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN33CMasterParameterBaseSqlite_SimpleI16StringDBEelementE10ClearCacheEv(long param_1)

{
  long *plVar1;
  long lVar2;
  long lVar3;
  
  if (*(long *)(param_1 + 0x58) != 0) {
    plVar1 = (long *)*(long *)(param_1 + 0x50);
    while (plVar1 != (long *)0x0) {
      lVar3 = *plVar1;
      if (plVar1[4] != 0) {
        std::__ndk1::__shared_weak_count::__release_shared()();
      }
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar1);
      plVar1 = (long *)lVar3;
    }
    lVar3 = *(long *)(param_1 + 0x48);
    *(undefined8 *)(param_1 + 0x50) = 0;
    if (lVar3 != 0) {
      lVar2 = 0;
      do {
        *(undefined8 *)(*(long *)(param_1 + 0x40) + lVar2 * 8) = 0;
        lVar2 = lVar2 + 1;
      } while (lVar3 != lVar2);
    }
    *(undefined8 *)(param_1 + 0x58) = 0;
  }
  if (*(long *)(param_1 + 0x88) != 0) {
    plVar1 = (long *)*(long *)(param_1 + 0x80);
    while (plVar1 != (long *)0x0) {
      lVar3 = *plVar1;
      if (plVar1[4] != 0) {
        std::__ndk1::__shared_weak_count::__release_shared()();
      }
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar1);
      plVar1 = (long *)lVar3;
    }
    lVar3 = *(long *)(param_1 + 0x78);
    *(undefined8 *)(param_1 + 0x80) = 0;
    if (lVar3 != 0) {
      lVar2 = 0;
      do {
        *(undefined8 *)(*(long *)(param_1 + 0x70) + lVar2 * 8) = 0;
        lVar2 = lVar2 + 1;
      } while (lVar3 != lVar2);
    }
    *(undefined8 *)(param_1 + 0x88) = 0;
  }
  return;
}

// ==== StringDB::pParseName() const
// vaddr 0x16faa14 | ghidra 0x17faa14 | size 12 | symbol _ZNK8StringDB10pParseNameEv | lib libSOA-3.7.0.so | 2026-10-08
undefined * _ZNK8StringDB10pParseNameEv(void)

{
  return &UNK_0285ebc6/*"master_text"*/;
}

// ==== non-virtual thunk to StringDB::pParseName() const
// vaddr 0x16faa20 | ghidra 0x17faa20 | size 12 | symbol _ZThn16_NK8StringDB10pParseNameEv | lib libSOA-3.7.0.so | 2026-10-08
undefined * _ZThn16_NK8StringDB10pParseNameEv(void)

{
  return &UNK_0285ebc6/*"master_text"*/;
}

// ==== StringDB::Get(char const*, bool*)
// vaddr 0x16faa2c | ghidra 0x17faa2c | size 192 | symbol _ZN8StringDB3GetEPKcPb | lib libSOA-3.7.0.so | 2026-10-08
void _ZN8StringDB3GetEPKcPb(byte *param_1)

{
  undefined8 uVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  ulong auStack_58 [3];
  char *pcStack_40;
  undefined8 uStack_38;
  undefined8 uStack_30;
  undefined8 uStack_28;
  undefined8 uStack_20;
  undefined8 uStack_18;
  
  StringDB::GetNativeString(char const*, bool*)();
  auStack_58[2] = 0;
  uStack_38 = 0;
  uStack_30 = 0;
  auStack_58[1] = 0;
  pcStack_40 = "derEiPN9Framework5Cocos11CCocosSceneE";
  auStack_58[0] = 0xa02;
  Framework::CSTLStringUtility_Base<string >::Replace(string const&, string const&, string const&, bool*)(&uStack_28,param_1,auStack_58 + 3,auStack_58,0);
  if ((*param_1 & 1) == 0) {
    param_1[0] = 0;
    param_1[1] = 0;
  }
  else {
    **(undefined1 **)(param_1 + 0x10) = 0;
    param_1[8] = 0;
    param_1[9] = 0;
    param_1[10] = 0;
    param_1[0xb] = 0;
    param_1[0xc] = 0;
    param_1[0xd] = 0;
    param_1[0xe] = 0;
    param_1[0xf] = 0;
  }
  string::reserve(unsigned long)(param_1,0);
  uVar3 = uStack_18;
  uVar2 = uStack_20;
  uVar1 = uStack_28;
  uStack_20 = 0;
  uStack_18 = 0;
  uStack_28 = 0;
  *(undefined8 *)(param_1 + 0x10) = uVar3;
  *(undefined8 *)(param_1 + 8) = uVar2;
  *(undefined8 *)param_1 = uVar1;
  if ((auStack_58[0] & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(auStack_58[2]);
  }
  if (((ulong)pcStack_40 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_30);
  }
  return;
}

// ==== StringDB::GetNativeString(char const*, bool*)
// vaddr 0x16faaec | ghidra 0x17faaec | size 396 | symbol _ZN8StringDB15GetNativeStringEPKcPb | lib libSOA-3.7.0.so | 2026-10-08
void _ZN8StringDB15GetNativeStringEPKcPb
               (ulong *param_1,undefined8 param_2,undefined8 param_3,undefined1 *param_4)

{
  bool bVar1;
  undefined4 uVar2;
  ulong uVar3;
  ulong uVar4;
  ulong uVar5;
  long lStack_68;
  long lStack_60;
  undefined1 auStack_58 [16];
  byte abStack_48 [16];
  undefined8 uStack_38;
  
  Framework::CSTLStringUtility_Base<string >::Format(char const*, ...)(abStack_48,&UNK_0285ec00/*"%s_%s"*/,&UNK_0280bbba/*"ja"*/,param_3);
  Framework::CHash32::CHash32(string const&)(auStack_58,abStack_48);
  uVar2 = Framework::CHash32::operator unsigned int() const(auStack_58);
  CMasterParameterBaseSqlite_Simple<StringDBEelement>::pParameterFromHash(unsigned int) const(&lStack_68,param_2,uVar2);
  Framework::CHash32::~CHash32()(auStack_58);
  if ((abStack_48[0] & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_38);
  }
  if (lStack_68 == 0) {
    bVar1 = false;
  }
  else {
    if (param_4 != (undefined1 *)0x0) {
      *param_4 = 1;
    }
    param_1[1] = 0;
    param_1[2] = 0;
    *param_1 = 0;
    void CParameterPropertyBase<32u>::CryptString<string >(string&, string const&)(param_1,lStack_68 + 0xa8);
    bVar1 = true;
  }
  if (lStack_60 != 0) {
    std::__ndk1::__shared_weak_count::__release_shared()();
  }
  if (bVar1) {
    return;
  }
  if (param_4 != (undefined1 *)0x0) {
    *param_4 = 0;
  }
  param_1[1] = 0;
  param_1[2] = 0;
  *param_1 = 0;
  uVar3 = strlen(param_3);
  if (uVar3 < 0x17) {
    uVar4 = (long)param_1 + 1;
    *(char *)param_1 = (char)(uVar3 << 1);
    if (uVar3 == 0) goto code_r0x017fac60;
  }
  else {
    uVar5 = uVar3 + 0x10 & 0xfffffffffffffff0;
    if (uVar5 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
    }
    uVar4 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar5,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
    if (uVar4 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    }
    param_1[1] = uVar3;
    param_1[2] = uVar4;
    *param_1 = uVar5 | 1;
  }
  memcpy(uVar4,param_3,uVar3);
code_r0x017fac60:
  *(undefined1 *)(uVar4 + uVar3) = 0;
  return;
}

// ==== StringDB::GetList(Framework::CSTLUnorderedMap<unsigned int, StringDBEelement, std::__ndk1::hash<unsigned int>, std::__ndk1::equal_to<unsigned int> >&, Framework::CSTLVector<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > > const&)
// vaddr 0x16fac78 | ghidra 0x17fac78 | size 1260 | symbol _ZN8StringDB7GetListERN9Framework16CSTLUnorderedMapIj16StringDBEelementNSt6__ndk14hashIjEENS3_8equal_toIjEEEERKNS0_10CSTLVectorINS3_12basic_stringIcNS3_11char_traitsIcEENS0_13CSTLAllocatorIcNS0_22CSTLStringAllocatorInfEEEEEEE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN8StringDB7GetListERN9Framework16CSTLUnorderedMapIj16StringDBEelementNSt6__ndk14hashIjEENS3_8equal_toIjEEEERKNS0_10CSTLVectorINS3_12basic_stringIcNS3_11char_traitsIcEENS0_13CSTLAllocatorIcNS0_22CSTLStringAllocatorInfEEEEEEE
               (undefined8 param_1,undefined8 param_2,long *param_3)

{
  ulong uVar1;
  undefined8 uVar2;
  bool bVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  undefined4 uVar7;
  undefined8 *puVar8;
  undefined8 *puVar9;
  byte *pbVar10;
  long lVar11;
  ulong uVar12;
  ulong uVar13;
  undefined8 *puVar14;
  byte *pbVar15;
  ulong uVar16;
  byte abStack_c0 [8];
  ulong uStack_b8;
  ulong uStack_b0;
  undefined1 auStack_a8 [16];
  byte abStack_98 [16];
  undefined8 uStack_88;
  ulong uStack_80;
  ulong uStack_78;
  undefined8 *puStack_70;
  
  uStack_78 = 0;
  puStack_70 = (undefined8 *)0x0;
  uStack_80 = 0;
  puVar8 = (undefined8 *)Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(0x30,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
  if (puVar8 == (undefined8 *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
  }
  uVar6 = _UNK_0285ebe2;
  uVar5 = _UNK_0285ebda;
  uVar4 = _UNK_0285ebd2;
  uVar2 = CONCAT17(UNK_0285ebf1,_UNK_0285ebea);
  uStack_78 = _UNK_028015c8;
  uStack_80 = _UNK_028015c0;
  *(ulong *)((long)puVar8 + 0x1f) = CONCAT71(_UNK_0285ebf2,UNK_0285ebf1);
  puVar8[1] = uVar5;
  *puVar8 = uVar4;
  puVar8[3] = uVar2;
  puVar8[2] = uVar6;
  *(undefined1 *)((long)puVar8 + 0x27) = 0;
  puStack_70 = puVar8;
  if ((byte *)param_3[1] == (byte *)*param_3) {
code_r0x017faffc:
    uVar16 = (uStack_80 & 0xfffffffffffffffe) - 1;
    bVar3 = true;
    uVar12 = uStack_80;
    uVar13 = uStack_78;
    if (uStack_78 != uVar16) goto code_r0x017fafe8;
code_r0x017fb014:
    puVar14 = (undefined8 *)((ulong)&uStack_80 | 1);
    puVar8 = puVar14;
    if ((uVar12 & 1) != 0) {
      puVar8 = puStack_70;
    }
    if (uVar16 < 0x7fffffffffffffe7) {
      uVar12 = uVar16 << 1;
      if (uVar12 <= uVar16 + 1) {
        uVar12 = uVar16 + 1;
      }
      if (uVar12 < 0x17) {
        uVar12 = 0x17;
      }
      else {
        uVar12 = uVar12 + 0x10 & 0xfffffffffffffff0;
        if (uVar12 == 0) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
        }
      }
    }
    else {
      uVar12 = 0xffffffffffffffef;
    }
    puVar9 = (undefined8 *)Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar12,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
    if (puVar9 == (undefined8 *)0x0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    }
    memcpy(puVar9,puVar8,uVar16);
    if (uVar16 != 0x16) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puVar8);
    }
    uStack_80 = uVar12 | 1;
    puStack_70 = puVar9;
  }
  else {
    puVar8 = (undefined8 *)((ulong)&uStack_80 | 1);
    pbVar10 = (byte *)*param_3;
    do {
      pbVar15 = pbVar10 + 0x18;
      if ((*pbVar10 & 1) == 0) {
        pbVar10 = pbVar10 + 1;
      }
      else {
        pbVar10 = *(byte **)(pbVar10 + 0x10);
      }
      Framework::CSTLStringUtility_Base<string >::Format(char const*, ...)(abStack_98,&UNK_0285ebfa/*"ja_%s"*/,pbVar10);
      Framework::CHash32::CHash32(string const&)(auStack_a8,abStack_98);
      uVar7 = Framework::CHash32::operator unsigned int() const(auStack_a8);
      Framework::CHash32::~CHash32()(auStack_a8);
      Framework::CSTLStringUtility_Base<string >::Format(char const*, ...)(abStack_c0,&UNK_027e6d32/*"%u"*/,uVar7);
      uVar12 = (ulong)(abStack_c0[0] >> 1);
      uVar13 = (ulong)abStack_c0 | 1;
      if ((abStack_c0[0] & 1) != 0) {
        uVar12 = uStack_b8;
        uVar13 = uStack_b0;
      }
      if ((uStack_80 & 1) == 0) {
        lVar11 = 0x16;
        uVar16 = uStack_80 & 0xff;
      }
      else {
        lVar11 = (uStack_80 & 0xfffffffffffffffe) - 1;
        uVar16 = uStack_80;
      }
      uVar1 = (ulong)(((uint)uVar16 & 0xfe) >> 1);
      if ((uVar16 & 1) != 0) {
        uVar1 = uStack_78;
      }
      if (lVar11 - uVar1 < uVar12) {
        string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&uStack_80,lVar11,(uVar12 - lVar11) + uVar1,uVar1,uVar1,0,uVar12);
      }
      else if (uVar12 != 0) {
        puVar14 = puVar8;
        if ((uVar16 & 1) != 0) {
          puVar14 = puStack_70;
        }
        memcpy((long)puVar14 + uVar1,uVar13,uVar12);
        uVar1 = uVar1 + uVar12;
        if ((uStack_80 & 1) == 0) {
          uStack_80 = CONCAT71(uStack_80._1_7_,(char)uVar1 * '\x02');
          *(undefined1 *)((long)puVar14 + uVar1) = 0;
        }
        else {
          *(undefined1 *)((long)puVar14 + uVar1) = 0;
          uStack_78 = uVar1;
        }
      }
      if ((abStack_c0[0] & 1) != 0) {
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_b0);
      }
      if (pbVar15 != (byte *)param_3[1]) {
        if ((uStack_80 & 1) == 0) {
          uVar13 = uStack_80 >> 1 & 0x7f;
          uVar12 = uStack_80 & 0xff;
          uVar16 = 0x16;
          if (uVar13 != 0x16) goto code_r0x017fae80;
code_r0x017faea0:
          puVar14 = puVar8;
          if ((uVar12 & 1) != 0) {
            puVar14 = puStack_70;
          }
          if (uVar16 < 0x7fffffffffffffe7) {
            uVar12 = uVar16 << 1;
            if (uVar12 <= uVar16 + 1) {
              uVar12 = uVar16 + 1;
            }
            if (uVar12 < 0x17) {
              uVar12 = 0x17;
            }
            else {
              uVar12 = uVar12 + 0x10 & 0xfffffffffffffff0;
              if (uVar12 == 0) {
                Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
              }
            }
          }
          else {
            uVar12 = 0xffffffffffffffef;
          }
          puVar9 = (undefined8 *)Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar12,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
          if (puVar9 == (undefined8 *)0x0) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
          }
          memcpy(puVar9,puVar14,uVar16);
          if (uVar16 != 0x16) {
            Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puVar14);
          }
          uStack_80 = uVar12 | 1;
          puStack_70 = puVar9;
code_r0x017faf94:
          uStack_78 = uVar13 + 1;
          puVar14 = puStack_70;
        }
        else {
          uVar16 = (uStack_80 & 0xfffffffffffffffe) - 1;
          uVar12 = uStack_80;
          uVar13 = uStack_78;
          if (uStack_78 == uVar16) goto code_r0x017faea0;
code_r0x017fae80:
          if ((uStack_80 & 1) != 0) goto code_r0x017faf94;
          uStack_80 = CONCAT71(uStack_80._1_7_,(char)uVar13 * '\x02' + '\x02');
          puVar14 = puVar8;
        }
        *(undefined2 *)((long)puVar14 + uVar13) = 0x2c;
      }
      if ((abStack_98[0] & 1) != 0) {
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_88);
      }
      pbVar10 = pbVar15;
    } while (pbVar15 != (byte *)param_3[1]);
    if ((uStack_80 & 1) != 0) goto code_r0x017faffc;
    bVar3 = false;
    uVar13 = uStack_80 >> 1 & 0x7f;
    uVar16 = 0x16;
    uVar12 = uStack_80 & 0xff;
    if (uVar13 == 0x16) goto code_r0x017fb014;
code_r0x017fafe8:
    if (!bVar3) {
      puVar14 = (undefined8 *)((ulong)&uStack_80 | 1);
      uStack_80 = CONCAT71(uStack_80._1_7_,(char)uVar13 * '\x02' + '\x02');
      puVar8 = puVar14;
      goto code_r0x017fb108;
    }
    puVar14 = (undefined8 *)((ulong)&uStack_80 | 1);
  }
  uStack_78 = uVar13 + 1;
  puVar8 = puStack_70;
code_r0x017fb108:
  *(undefined2 *)((long)puVar8 + uVar13) = 0x29;
  if ((uStack_80 & 1) != 0) {
    puVar14 = puStack_70;
  }
  CMasterParameterBaseSqlite_Simple<StringDBEelement>::ParameterByQuery(char const*, Framework::CSTLUnorderedMap<unsigned int, StringDBEelement, std::__ndk1::hash<unsigned int>, std::__ndk1::equal_to<unsigned int> >&, Aska::Yayoi::QueryParam*, unsigned int) const(param_1,puVar14,param_2,0,0);
  if ((uStack_80 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puStack_70);
  }
  return;
}

// ==== CMasterParameterBaseSqlite_Simple<StringDBEelement>::ParameterByQuery(char const*, Framework::CSTLUnorderedMap<unsigned int, StringDBEelement, std::__ndk1::hash<unsigned int>, std::__ndk1::equal_to<unsigned int> >&, Aska::Yayoi::QueryParam*, unsigned int) const
// vaddr 0x16fb164 | ghidra 0x17fb164 | size 288 | symbol _ZNK33CMasterParameterBaseSqlite_SimpleI16StringDBEelementE16ParameterByQueryEPKcRN9Framework16CSTLUnorderedMapIjS0_NSt6__ndk14hashIjEENS6_8equal_toIjEEEEPN4Aska5Yayoi10QueryParamEj | lib libSOA-3.7.0.so | 2026-10-08
void _ZNK33CMasterParameterBaseSqlite_SimpleI16StringDBEelementE16ParameterByQueryEPKcRN9Framework16CSTLUnorderedMapIjS0_NSt6__ndk14hashIjEENS6_8equal_toIjEEEEPN4Aska5Yayoi10QueryParamEj
               (long *param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               undefined4 param_5)

{
  int iVar1;
  char cVar2;
  bool bVar3;
  ulong uVar4;
  long *plVar5;
  long lStack_50;
  int *piStack_48;
  long lStack_38;
  
  uVar4 = (**(code **)(*param_1 + 0x28))();
  if ((uVar4 & 1) == 0) {
    return;
  }
  plVar5 = (long *)param_1[1];
  if (plVar5 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dc023/*"C:\BAS_Submission\Client\Project\Android\BASAndroid.NativeActivity\..\..\..\Source\Game/Parameter/Master/MasterParameterBaseSqlite.h"*/,0x4d,&UNK_027dc0a8/*"m_pConnector is null."*/);
  }
  (**(code **)(*plVar5 + 0x10))(plVar5,&UNK_027dc00a/*"sqlite/basmaster.sqlite3"*/);
  lStack_50 = 0;
  piStack_48 = (int *)0x0;
  lStack_38 = 0;
  (**(code **)(*plVar5 + 0x30))(plVar5,param_2,&lStack_50,&lStack_38,param_4,param_5);
  if (0 < lStack_38) {
    void CMasterParameterBaseSqlite::DeserializeMsgPack<StringDBEelement>(Aska::TSharedArray<signed char> const&, long const&, StringDBEelement*, Framework::CSTLUnorderedMap<unsigned int, StringDBEelement, std::__ndk1::hash<unsigned int>, std::__ndk1::equal_to<unsigned int> >*) const(param_1,&lStack_50,&lStack_38,0,param_3);
  }
  if (piStack_48 != (int *)0x0) {
    do {
      iVar1 = *piStack_48;
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piStack_48,0x10);
      if (bVar3) {
        *piStack_48 = iVar1 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    if (iVar1 + -1 != 0) goto code_r0x017fb258;
  }
  if (lStack_50 != 0) {
    operator delete[](void*)();
  }
  if (piStack_48 != (int *)0x0) {
    Aska::TSharedPointerCode::DeleteCounter(int*)();
  }
code_r0x017fb258:
  lStack_50 = 0;
  (**(code **)(*plVar5 + 0x18))(plVar5);
  return;
}

// ==== StringDB::SetAddLoadFileName(std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> >)
// vaddr 0x16fb284 | ghidra 0x17fb284 | size 228 | symbol _ZN8StringDB18SetAddLoadFileNameENSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN8StringDB18SetAddLoadFileNameENSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEE
               (long param_1,ulong *param_2)

{
  ulong *puVar1;
  ulong uVar2;
  byte *pbVar3;
  ulong uVar4;
  ulong uVar5;
  long lVar6;
  
  puVar1 = (ulong *)(param_1 + 0xa0);
  if (puVar1 != param_2) {
    uVar2 = param_2[1];
    pbVar3 = (byte *)param_2[2];
    uVar5 = (ulong)*(byte *)puVar1;
    if (((byte)*param_2 & 1) == 0) {
      pbVar3 = (byte *)((long)param_2 + 1);
      uVar2 = (ulong)(byte)((byte)*param_2 >> 1);
    }
    if ((*(byte *)puVar1 & 1) == 0) {
      uVar4 = 0x16;
      lVar6 = uVar2 - 0x16;
      if (0x15 < uVar2 && lVar6 != 0) {
code_r0x017fb2f0:
        if ((uVar5 & 1) == 0) {
          uVar5 = (ulong)(((uint)uVar5 & 0xfe) >> 1);
        }
        else {
          uVar5 = *(ulong *)(param_1 + 0xa8);
        }
        (*(code *)
          PTR__ZNSt6__ndk112basic_stringIcNS_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS3_22CSTLStringAllocatorInfEEEE21__grow_by_and_replaceEmmmmmmPKc_02ca6d40
        )(puVar1,uVar4,lVar6,uVar5,0,uVar5,uVar2);
        return;
      }
    }
    else {
      uVar5 = *puVar1;
      uVar4 = (uVar5 & 0xfffffffffffffffe) - 1;
      lVar6 = uVar2 - uVar4;
      if (uVar4 <= uVar2 && lVar6 != 0) goto code_r0x017fb2f0;
    }
    if ((uVar5 & 1) == 0) {
      lVar6 = param_1 + 0xa1;
    }
    else {
      lVar6 = *(long *)(param_1 + 0xb0);
    }
    if (uVar2 != 0) {
      memmove(lVar6,pbVar3,uVar2);
    }
    *(undefined1 *)(lVar6 + uVar2) = 0;
    if ((*(byte *)puVar1 & 1) == 0) {
      *(byte *)puVar1 = (byte)(uVar2 << 1);
    }
    else {
      *(ulong *)(param_1 + 0xa8) = uVar2;
    }
  }
  return;
}

// ==== StringDB::ReleaseParameter(char const*)
// vaddr 0x16fb368 | ghidra 0x17fb368 | size 156 | symbol _ZN8StringDB16ReleaseParameterEPKc | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN8StringDB16ReleaseParameterEPKc(long param_1,undefined8 param_2)

{
  long *plVar1;
  int iVar2;
  long lVar3;
  long lVar4;
  
  if ((*(byte *)(param_1 + 0xa0) & 1) == 0) {
    lVar4 = param_1 + 0xa1;
  }
  else {
    lVar4 = *(long *)(param_1 + 0xb0);
  }
  iVar2 = strcmp(param_2,lVar4);
  if ((iVar2 == 0) && (*(long *)(param_1 + 0x30) != 0)) {
    plVar1 = (long *)*(long *)(param_1 + 0x28);
    while (plVar1 != (long *)0x0) {
      lVar4 = *plVar1;
      if (plVar1[4] != 0) {
        std::__ndk1::__shared_weak_count::__release_shared()();
      }
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar1);
      plVar1 = (long *)lVar4;
    }
    lVar4 = *(long *)(param_1 + 0x20);
    *(undefined8 *)(param_1 + 0x28) = 0;
    if (lVar4 != 0) {
      lVar3 = 0;
      do {
        *(undefined8 *)(*(long *)(param_1 + 0x18) + lVar3 * 8) = 0;
        lVar3 = lVar3 + 1;
      } while (lVar4 != lVar3);
    }
    *(undefined8 *)(param_1 + 0x30) = 0;
  }
  return 1;
}

// ==== non-virtual thunk to StringDB::ReleaseParameter(char const*)
// vaddr 0x16fb404 | ghidra 0x17fb404 | size 152 | symbol _ZThn16_N8StringDB16ReleaseParameterEPKc | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZThn16_N8StringDB16ReleaseParameterEPKc(long param_1,undefined8 param_2)

{
  long *plVar1;
  int iVar2;
  long lVar3;
  long lVar4;
  
  if ((*(byte *)(param_1 + 0x90) & 1) == 0) {
    lVar4 = param_1 + 0x91;
  }
  else {
    lVar4 = *(long *)(param_1 + 0xa0);
  }
  iVar2 = strcmp(param_2,lVar4);
  if ((iVar2 == 0) && (*(long *)(param_1 + 0x20) != 0)) {
    plVar1 = (long *)*(long *)(param_1 + 0x18);
    while (plVar1 != (long *)0x0) {
      lVar4 = *plVar1;
      if (plVar1[4] != 0) {
        std::__ndk1::__shared_weak_count::__release_shared()();
      }
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar1);
      plVar1 = (long *)lVar4;
    }
    lVar4 = *(long *)(param_1 + 0x10);
    *(undefined8 *)(param_1 + 0x18) = 0;
    if (lVar4 != 0) {
      lVar3 = 0;
      do {
        *(undefined8 *)(*(long *)(param_1 + 8) + lVar3 * 8) = 0;
        lVar3 = lVar3 + 1;
      } while (lVar4 != lVar3);
    }
    *(undefined8 *)(param_1 + 0x20) = 0;
  }
  return 1;
}

// ==== StringDB::~StringDB()
// vaddr 0x16fb49c | ghidra 0x17fb49c | size 60 | symbol _ZN8StringDBD2Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN8StringDBD2Ev(long *param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZTV8StringDB_02cb70a0 + 0x78;
  *param_1 = (long)(PTR__ZTV8StringDB_02cb70a0 + 0x10);
  param_1[2] = (long)puVar1;
  if ((*(byte *)(param_1 + 0x14) & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(param_1[0x16]);
  }
  (*(code *)PTR__ZN33CMasterParameterBaseSqlite_SimpleI16StringDBEelementED2Ev_02ca1de8)(param_1);
  return;
}

// ==== StringDB::~StringDB()
// vaddr 0x16fb4d8 | ghidra 0x17fb4d8 | size 68 | symbol _ZN8StringDBD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN8StringDBD0Ev(long *param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZTV8StringDB_02cb70a0 + 0x78;
  *param_1 = (long)(PTR__ZTV8StringDB_02cb70a0 + 0x10);
  param_1[2] = (long)puVar1;
  if ((*(byte *)(param_1 + 0x14) & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(param_1[0x16]);
  }
  CMasterParameterBaseSqlite_Simple<StringDBEelement>::~CMasterParameterBaseSqlite_Simple()(param_1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== CMasterParameterBaseSqlite_Simple<StringDBEelement>::Initialize()
// vaddr 0x16fb51c | ghidra 0x17fb51c | size 64 | symbol _ZN33CMasterParameterBaseSqlite_SimpleI16StringDBEelementE10InitializeEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN33CMasterParameterBaseSqlite_SimpleI16StringDBEelementE10InitializeEv(long *param_1)

{
  long lVar1;
  
  lVar1 = (**(code **)(*param_1 + 0x30))();
  param_1[1] = lVar1;
  if (lVar1 != 0) {
    return;
  }
  (*(code *)PTR__ZN9Framework9gDoAssertEPKciS1_z_02ca3240)(&UNK_027dc023/*"C:\BAS_Submission\Client\Project\Android\BASAndroid.NativeActivity\..\..\..\Source\Game/Parameter/Master/MasterParameterBaseSqlite.h"*/,0x165,&UNK_02845d79/*"m_pSqlConnector is null."*/);
  return;
}

// ==== StringDB::InstantiateSqlConnector()
// vaddr 0x16fb55c | ghidra 0x17fb55c | size 72 | symbol _ZN8StringDB23InstantiateSqlConnectorEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN8StringDB23InstantiateSqlConnectorEv(void)

{
  undefined *puVar1;
  undefined *puVar2;
  long *plVar3;
  
  plVar3 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x118,PTR__ZSt7nothrow_02cb9a80);
  if (plVar3 != (long *)0x0) {
    puVar1 = PTR__ZTV22CSimpleSqliteConnectorIN8MasterDB5CTextEN4Aska5Yayoi13TEntity_SlaveINS3_12SQLiteDriverES1_NS3_7NoCacheEEEE_02cb75f8
             + 0x10;
    puVar2 = PTR__ZTVN22CSimpleSqliteConnectorIN8MasterDB5CTextEN4Aska5Yayoi13TEntity_SlaveINS3_12SQLiteDriverES1_NS3_7NoCacheEEEE12CLocalEntityIS1_EE_02cc11b8
             + 0x10;
    plVar3[1] = (long)puVar2;
    *plVar3 = (long)puVar1;
    plVar3[2] = (long)puVar2;
  }
  return;
}

// ==== CMasterParameterBaseSqlite_Simple<StringDBEelement>::Deserialize(Aska::ASON::AValue::AMap const*)
// vaddr 0x16fb5a4 | ghidra 0x17fb5a4 | size 108 | symbol _ZN33CMasterParameterBaseSqlite_SimpleI16StringDBEelementE11DeserializeEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
bool _ZN33CMasterParameterBaseSqlite_SimpleI16StringDBEelementE11DeserializeEPKN4Aska4ASON6AValue4AMapE
               (long *param_1,long param_2)

{
  long lVar1;
  
  if (param_2 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dc023/*"C:\BAS_Submission\Client\Project\Android\BASAndroid.NativeActivity\..\..\..\Source\Game/Parameter/Master/MasterParameterBaseSqlite.h"*/,0x200,&UNK_027dc58a/*"apParser is null."*/);
  }
  lVar1 = (**(code **)(param_1[2] + 0x30))(param_1 + 2,param_2);
  if (lVar1 != 0) {
    (**(code **)(*param_1 + 0x48))(param_1,param_1 + 3,lVar1 + 8);
  }
  return lVar1 != 0;
}

// ==== CMasterParameterBaseSqlite_Simple<StringDBEelement>::DeserializeParameter(Framework::CSTLUnorderedMap<unsigned int, std::__ndk1::shared_ptr<StringDBEelement>, std::__ndk1::hash<unsigned int>, std::__ndk1::equal_to<unsigned int> >&, Aska::ASON::AValue::AArray const*)
// vaddr 0x16fb610 | ghidra 0x17fb610 | size 1388 | symbol _ZN33CMasterParameterBaseSqlite_SimpleI16StringDBEelementE20DeserializeParameterERN9Framework16CSTLUnorderedMapIjNSt6__ndk110shared_ptrIS0_EENS4_4hashIjEENS4_8equal_toIjEEEEPKN4Aska4ASON6AValue6AArrayE | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN33CMasterParameterBaseSqlite_SimpleI16StringDBEelementE20DeserializeParameterERN9Framework16CSTLUnorderedMapIjNSt6__ndk110shared_ptrIS0_EENS4_4hashIjEENS4_8equal_toIjEEEEPKN4Aska4ASON6AValue6AArrayE
          (long *param_1,long *param_2,long *param_3)

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
  long lVar13;
  uint uVar14;
  undefined8 uVar15;
  uint *puVar16;
  ulong uVar17;
  long *plVar18;
  ulong uVar19;
  ulong uVar20;
  long *plVar21;
  long *plVar22;
  long *plVar23;
  ulong uVar24;
  ulong uVar25;
  ulong uVar26;
  int iVar27;
  undefined1 auVar28 [16];
  undefined1 auStack_70 [16];
  
  if (param_3 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dc023/*"C:\BAS_Submission\Client\Project\Android\BASAndroid.NativeActivity\..\..\..\Source\Game/Parameter/Master/MasterParameterBaseSqlite.h"*/,0x221,&UNK_02845e17/*"apArray is null."*/);
    iVar27 = iRam0000000000000008;
  }
  else {
    iVar27 = (int)param_3[1];
  }
  if (iVar27 != 0) {
    puVar1 = PTR__ZTVNSt6__ndk120__shared_ptr_emplaceI16StringDBEelement18ParameterAllocatorIS1_EEE_02cc2d78
             + 0x10;
    puVar2 = PTR__ZTV16StringDBEelement_02cbb4f0 + 0x10;
    puVar3 = PTR__ZTV22CParameterPropertyBaseILj29EE_02cc1a28 + 0x10;
    puVar4 = PTR__ZTV23CParameterPropertyValueIjLj29E18CPropertyConverterE_02cb7988 + 0x10;
    puVar5 = PTR__ZTV22CParameterPropertyBaseILj31EE_02cc17e0 + 0x10;
    puVar6 = PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj31EE_02cba990
             + 0x10;
    puVar7 = PTR__ZTV22CParameterPropertyBaseILj32EE_02cc0fa8 + 0x10;
    puVar8 = PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj32EE_02cc31e8
             + 0x10;
    puVar9 = PTR__ZTV22CParameterPropertyBaseILj33EE_02cb96b8 + 0x10;
    puVar10 = PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj33EE_02cb7cb0
              + 0x10;
    puVar11 = PTR__ZTV22CParameterPropertyBaseILj34EE_02cc0de8 + 0x10;
    uVar19 = 0;
    puVar12 = PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj34EE_02cb8320
              + 0x10;
    do {
      lVar13 = *param_3 + uVar19 * 0x20;
      if (lVar13 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dc023/*"C:\BAS_Submission\Client\Project\Android\BASAndroid.NativeActivity\..\..\..\Source\Game/Parameter/Master/MasterParameterBaseSqlite.h"*/,0x224,&UNK_0285e8d7/*"pValue is null."*/);
      }
      lVar13 = lVar13 + 8;
      uVar15 = (**(code **)(*param_1 + 0x18))(param_1);
      puVar16 = (uint *)Aska::ASON::AValue::AMap::Get_(char const*)(lVar13,uVar15);
      if (puVar16 != (uint *)0x0) {
        uVar14 = *puVar16;
        uVar25 = (ulong)uVar14;
        uVar15 = (**(code **)(*param_1 + 0x18))(param_1);
        if (uVar14 == 5) {
          auVar28 = std::__ndk1::pair<char*, bool> CParameterParser::GetValue<char*>(Aska::ASON::AValue::AMap const*, char const*)();
          if ((auVar28._8_8_ & 1) != 0) {
            Framework::CHash32::CHash32(char const*)(auStack_70,auVar28._0_8_);
            uVar17 = Framework::CHash32::operator unsigned int() const(auStack_70);
            uVar17 = uVar17 & 0xffffffff;
            Framework::CHash32::~CHash32()(auStack_70);
code_r0x017fb7e0:
            uVar24 = param_2[1];
            uVar26 = uVar17 & 0xffffffff;
            iVar27 = (int)uVar17;
            if (uVar24 == 0) {
code_r0x017fb874:
              plVar18 = (long *)operator new(unsigned long)(0x158);
              plVar23 = plVar18 + 3;
              plVar18[2] = 0;
              *plVar18 = (long)puVar1;
              plVar18[1] = 0;
              CParameterElementBase::CParameterElementBase()(plVar23);
              *(undefined1 *)(plVar18 + 7) = 0;
              plVar18[3] = (long)puVar2;
              plVar18[5] = (long)puVar3;
              plVar18[6] = 0;
              Framework::CHash32::CHash32()(plVar18 + 8);
              *(undefined1 *)(plVar18 + 0xd) = 0;
              plVar18[5] = (long)puVar4;
              plVar18[0xb] = (long)puVar5;
              plVar18[0xc] = 0;
              Framework::CHash32::CHash32()(plVar18 + 0xe);
              plVar18[0x10] = 0;
              plVar18[0x11] = 0;
              plVar18[0x14] = 0;
              plVar18[0xb] = (long)puVar6;
              plVar18[0x12] = 0;
              *(undefined1 *)(plVar18 + 0x15) = 0;
              plVar18[0x13] = (long)puVar7;
              Framework::CHash32::CHash32()(plVar18 + 0x16);
              plVar18[0x18] = 0;
              plVar18[0x19] = 0;
              plVar18[0x1c] = 0;
              plVar18[0x13] = (long)puVar8;
              plVar18[0x1a] = 0;
              *(undefined1 *)(plVar18 + 0x1d) = 0;
              plVar18[0x1b] = (long)puVar9;
              Framework::CHash32::CHash32()(plVar18 + 0x1e);
              plVar18[0x20] = 0;
              plVar18[0x21] = 0;
              plVar18[0x24] = 0;
              plVar18[0x1b] = (long)puVar10;
              plVar18[0x22] = 0;
              *(undefined1 *)(plVar18 + 0x25) = 0;
              plVar18[0x23] = (long)puVar11;
              Framework::CHash32::CHash32()(plVar18 + 0x26);
              plVar18[0x29] = 0;
              plVar18[0x2a] = 0;
              plVar18[0x28] = 0;
              plVar18[0x23] = (long)puVar12;
              uVar17 = param_2[1];
              if (uVar17 == 0) {
code_r0x017fb9e0:
                plVar21 = (long *)Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(0x28,&UNK_027dc2d5/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_UnorderedMap.h"*/,0x1c);
                if (plVar21 == (long *)0x0) {
                  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
                }
                *(int *)(plVar21 + 2) = iVar27;
                plVar21[3] = (long)plVar23;
                plVar21[4] = (long)plVar18;
                std::__ndk1::__shared_weak_count::__add_shared()(plVar18);
                *plVar21 = 0;
                plVar21[1] = uVar26;
                if ((uVar17 == 0) ||
                   (*(float *)(param_2 + 4) * (float)uVar17 < (float)(param_2[3] + 1))) {
                  if (uVar17 < 3) {
                    uVar25 = 1;
                  }
                  else {
                    uVar25 = (ulong)((uVar17 - 1 & uVar17) != 0);
                  }
                  uVar25 = uVar25 | uVar17 << 1;
                  uVar17 = (ulong)((float)(param_2[3] + 1) / *(float *)(param_2 + 4));
                  if (uVar17 <= uVar25) {
                    uVar17 = uVar25;
                  }
                  std::__ndk1::__hash_table<std::__ndk1::__hash_value_type<unsigned int, std::__ndk1::shared_ptr<StringDBEelement> >, std::__ndk1::__unordered_map_hasher<unsigned int, std::__ndk1::__hash_value_type<unsigned int, std::__ndk1::shared_ptr<StringDBEelement> >, std::__ndk1::hash<unsigned int>, true>, std::__ndk1::__unordered_map_equal<unsigned int, std::__ndk1::__hash_value_type<unsigned int, std::__ndk1::shared_ptr<StringDBEelement> >, std::__ndk1::equal_to<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__hash_value_type<unsigned int, std::__ndk1::shared_ptr<StringDBEelement> >, Framework::CSTLUnorderedMapAllocatorInf> >::rehash(unsigned long)(param_2,uVar17);
                  uVar17 = param_2[1];
                  if ((uVar17 - 1 & uVar17) == 0) {
                    uVar25 = uVar17 - 1 & uVar26;
                  }
                  else {
                    uVar25 = 0;
                    if (uVar17 != 0) {
                      uVar25 = uVar26 / uVar17;
                    }
                    uVar25 = uVar26 - uVar25 * uVar17;
                  }
                }
                plVar22 = *(long **)(*param_2 + uVar25 * 8);
                if (plVar22 == (long *)0x0) {
                  *plVar21 = param_2[2];
                  param_2[2] = (long)plVar21;
                  *(long **)(*param_2 + uVar25 * 8) = param_2 + 2;
                  if (*plVar21 != 0) {
                    uVar25 = *(ulong *)(*plVar21 + 8);
                    if ((uVar17 - 1 & uVar17) == 0) {
                      uVar25 = uVar25 & uVar17 - 1;
                    }
                    else {
                      uVar24 = 0;
                      if (uVar17 != 0) {
                        uVar24 = uVar25 / uVar17;
                      }
                      uVar25 = uVar25 - uVar24 * uVar17;
                    }
                    plVar22 = (long *)(*param_2 + uVar25 * 8);
                    goto code_r0x017fbb08;
                  }
                }
                else {
                  *plVar21 = *plVar22;
code_r0x017fbb08:
                  *plVar22 = (long)plVar21;
                }
                param_2[3] = param_2[3] + 1;
              }
              else {
                uVar24 = uVar17 - 1;
                if ((uVar24 & uVar17) == 0) {
                  uVar25 = uVar24 & uVar26;
                }
                else {
                  uVar25 = 0;
                  if (uVar17 != 0) {
                    uVar25 = uVar26 / uVar17;
                  }
                  uVar25 = uVar26 - uVar25 * uVar17;
                }
                plVar21 = *(long **)(*param_2 + uVar25 * 8);
                if (plVar21 == (long *)0x0) goto code_r0x017fb9e0;
                if ((uVar24 & uVar17) == 0) {
                  do {
                    plVar21 = (long *)*plVar21;
                    if ((plVar21 == (long *)0x0) || ((plVar21[1] & uVar24) != uVar25))
                    goto code_r0x017fb9e0;
                  } while ((int)plVar21[2] != iVar27);
                }
                else {
                  do {
                    plVar21 = (long *)*plVar21;
                    if (plVar21 == (long *)0x0) goto code_r0x017fb9e0;
                    uVar24 = 0;
                    if (uVar17 != 0) {
                      uVar24 = (ulong)plVar21[1] / uVar17;
                    }
                    if (plVar21[1] - uVar24 * uVar17 != uVar25) goto code_r0x017fb9e0;
                  } while (*(int *)(plVar21 + 2) != iVar27);
                }
              }
              (**(code **)plVar18[3])(plVar23);
              std::__ndk1::__shared_weak_count::__release_shared()(plVar18);
            }
            else {
              uVar17 = uVar24 - 1;
              if ((uVar17 & uVar24) == 0) {
                uVar20 = uVar17 & uVar26;
              }
              else {
                uVar20 = 0;
                if (uVar24 != 0) {
                  uVar20 = uVar26 / uVar24;
                }
                uVar20 = uVar26 - uVar20 * uVar24;
              }
              plVar23 = *(long **)(*param_2 + uVar20 * 8);
              if (plVar23 == (long *)0x0) goto code_r0x017fb874;
              if ((uVar17 & uVar24) == 0) {
                do {
                  plVar23 = (long *)*plVar23;
                  if ((plVar23 == (long *)0x0) || ((plVar23[1] & uVar17) != uVar20))
                  goto code_r0x017fb874;
                } while ((int)plVar23[2] != iVar27);
              }
              else {
                do {
                  plVar23 = (long *)*plVar23;
                  if (plVar23 == (long *)0x0) goto code_r0x017fb874;
                  uVar17 = 0;
                  if (uVar24 != 0) {
                    uVar17 = (ulong)plVar23[1] / uVar24;
                  }
                  if (plVar23[1] - uVar17 * uVar24 != uVar20) goto code_r0x017fb874;
                } while (*(int *)(plVar23 + 2) != iVar27);
              }
              if (plVar23 == (long *)0x0) goto code_r0x017fb874;
              plVar23 = (long *)plVar23[3];
            }
            (**(code **)(*plVar23 + 8))(plVar23,lVar13);
          }
        }
        else {
          uVar17 = std::__ndk1::pair<unsigned int, bool> CParameterParser::GetValue<unsigned int>(Aska::ASON::AValue::AMap const*, char const*)(lVar13,uVar15);
          if ((uVar17 >> 0x20 & 1) != 0) goto code_r0x017fb7e0;
        }
      }
      uVar14 = (int)uVar19 + 1;
      uVar19 = (ulong)uVar14;
    } while (uVar14 < *(uint *)(param_3 + 1));
  }
  return 1;
}

// ==== non-virtual thunk to StringDB::~StringDB()
// vaddr 0x16fbb7c | ghidra 0x17fbb7c | size 60 | symbol _ZThn16_N8StringDBD1Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZThn16_N8StringDBD1Ev(long *param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZTV8StringDB_02cb70a0;
  param_1[-2] = (long)(PTR__ZTV8StringDB_02cb70a0 + 0x10);
  *param_1 = (long)(puVar1 + 0x78);
  if ((*(byte *)(param_1 + 0x12) & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(param_1[0x14]);
  }
  (*(code *)PTR__ZN33CMasterParameterBaseSqlite_SimpleI16StringDBEelementED2Ev_02ca1de8)
            (param_1 + -2);
  return;
}

// ==== non-virtual thunk to StringDB::~StringDB()
// vaddr 0x16fbbb8 | ghidra 0x17fbbb8 | size 68 | symbol _ZThn16_N8StringDBD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZThn16_N8StringDBD0Ev(long *param_1)

{
  undefined *puVar1;
  long *plVar2;
  
  puVar1 = PTR__ZTV8StringDB_02cb70a0;
  plVar2 = param_1 + -2;
  *plVar2 = (long)(PTR__ZTV8StringDB_02cb70a0 + 0x10);
  *param_1 = (long)(puVar1 + 0x78);
  if ((*(byte *)(param_1 + 0x12) & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(param_1[0x14]);
  }
  CMasterParameterBaseSqlite_Simple<StringDBEelement>::~CMasterParameterBaseSqlite_Simple()(plVar2);
  (*(code *)PTR__ZdlPv_02ca4758)(plVar2);
  return;
}

// ==== non-virtual thunk to CMasterParameterBaseSqlite_Simple<StringDBEelement>::Initialize()
// vaddr 0x16fbbfc | ghidra 0x17fbbfc | size 68 | symbol _ZThn16_N33CMasterParameterBaseSqlite_SimpleI16StringDBEelementE10InitializeEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZThn16_N33CMasterParameterBaseSqlite_SimpleI16StringDBEelementE10InitializeEv(long param_1)

{
  long lVar1;
  
  lVar1 = (**(code **)(*(long *)(param_1 + -0x10) + 0x30))((long *)(param_1 + -0x10));
  *(long *)(param_1 + -8) = lVar1;
  if (lVar1 != 0) {
    return;
  }
  (*(code *)PTR__ZN9Framework9gDoAssertEPKciS1_z_02ca3240)(&UNK_027dc023/*"C:\BAS_Submission\Client\Project\Android\BASAndroid.NativeActivity\..\..\..\Source\Game/Parameter/Master/MasterParameterBaseSqlite.h"*/,0x165,&UNK_02845d79/*"m_pSqlConnector is null."*/);
  return;
}

// ==== non-virtual thunk to CMasterParameterBaseSqlite_Simple<StringDBEelement>::Deserialize(Aska::ASON::AValue::AMap const*)
// vaddr 0x16fbc40 | ghidra 0x17fbc40 | size 108 | symbol _ZThn16_N33CMasterParameterBaseSqlite_SimpleI16StringDBEelementE11DeserializeEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
bool _ZThn16_N33CMasterParameterBaseSqlite_SimpleI16StringDBEelementE11DeserializeEPKN4Aska4ASON6AValue4AMapE
               (long *param_1,long param_2)

{
  long lVar1;
  
  if (param_2 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dc023/*"C:\BAS_Submission\Client\Project\Android\BASAndroid.NativeActivity\..\..\..\Source\Game/Parameter/Master/MasterParameterBaseSqlite.h"*/,0x200,&UNK_027dc58a/*"apParser is null."*/);
  }
  lVar1 = (**(code **)(*param_1 + 0x30))(param_1,param_2);
  if (lVar1 != 0) {
    (**(code **)(param_1[-2] + 0x48))(param_1 + -2,param_1 + 1,lVar1 + 8);
  }
  return lVar1 != 0;
}

// ==== CMasterParameterBaseSqlite_Simple<StringDBEelement>::pParameterFromHash(unsigned int) const
// vaddr 0x16fbcac | ghidra 0x17fbcac | size 1948 | symbol _ZNK33CMasterParameterBaseSqlite_SimpleI16StringDBEelementE18pParameterFromHashEj | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Possible PIC construction at 0x017fc378: Changing call to branch */
/* WARNING: Possible PIC construction at 0x017fc1b4: Changing call to branch */
/* WARNING: Removing unreachable block (ram,0x017fc37c) */
/* WARNING: Removing unreachable block (ram,0x017fc384) */
/* WARNING: Removing unreachable block (ram,0x017fc1b8) */
/* WARNING: Removing unreachable block (ram,0x017fc1d0) */
/* WARNING: Removing unreachable block (ram,0x017fc1d8) */
/* WARNING: Removing unreachable block (ram,0x017fc1dc) */
/* WARNING: Removing unreachable block (ram,0x017fc1e0) */
/* WARNING: Removing unreachable block (ram,0x017fc1fc) */
/* WARNING: Removing unreachable block (ram,0x017fc1ec) */
/* WARNING: Removing unreachable block (ram,0x017fc200) */
/* WARNING: Removing unreachable block (ram,0x017fc210) */
/* WARNING: Removing unreachable block (ram,0x017fc238) */
/* WARNING: Removing unreachable block (ram,0x017fc22c) */
/* WARNING: Removing unreachable block (ram,0x017fc23c) */
/* WARNING: Removing unreachable block (ram,0x017fc254) */
/* WARNING: Removing unreachable block (ram,0x017fc274) */
/* WARNING: Removing unreachable block (ram,0x017fc290) */
/* WARNING: Removing unreachable block (ram,0x017fc284) */
/* WARNING: Removing unreachable block (ram,0x017fc294) */
/* WARNING: Removing unreachable block (ram,0x017fc248) */
/* WARNING: Removing unreachable block (ram,0x017fc29c) */
/* WARNING: Removing unreachable block (ram,0x017fc2a0) */

void _ZNK33CMasterParameterBaseSqlite_SimpleI16StringDBEelementE18pParameterFromHashEj
               (long *param_1,long *param_2,uint param_3)

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
  long *plVar13;
  int iVar14;
  uint uVar15;
  char cVar16;
  bool bVar17;
  ulong uVar18;
  ulong uVar19;
  long *plVar20;
  long *plVar21;
  long lVar22;
  long *plVar23;
  ulong uVar24;
  ulong uVar25;
  long lVar26;
  ulong uVar27;
  long *plVar28;
  long *plVar29;
  long lStack_a0;
  undefined8 uStack_98;
  long *plStack_90;
  undefined8 uStack_88;
  undefined4 uStack_80;
  long lStack_78;
  long lStack_70;
  int *piStack_68;
  
  uVar24 = param_2[9];
  uVar27 = (ulong)param_3;
  plVar23 = param_2 + 8;
  if (uVar24 != 0) {
    uVar25 = uVar24 - 1;
    if ((uVar25 & uVar24) == 0) {
      uVar19 = uVar25 & uVar27;
    }
    else {
      uVar19 = 0;
      if (uVar24 != 0) {
        uVar19 = uVar27 / uVar24;
      }
      uVar19 = uVar27 - uVar19 * uVar24;
    }
    plVar21 = *(long **)(*plVar23 + uVar19 * 8);
    if (plVar21 == (long *)0x0) goto code_r0x017fbd64;
    if ((uVar25 & uVar24) == 0) {
      do {
        plVar21 = (long *)*plVar21;
        if ((plVar21 == (long *)0x0) || ((plVar21[1] & uVar25) != uVar19)) goto code_r0x017fbd64;
      } while (*(uint *)(plVar21 + 2) != param_3);
    }
    else {
      do {
        plVar21 = (long *)*plVar21;
        if (plVar21 == (long *)0x0) goto code_r0x017fbd64;
        uVar25 = 0;
        if (uVar24 != 0) {
          uVar25 = (ulong)plVar21[1] / uVar24;
        }
        if (plVar21[1] - uVar25 * uVar24 != uVar19) goto code_r0x017fbd64;
      } while (*(uint *)(plVar21 + 2) != param_3);
    }
    if (plVar21 == (long *)0x0) goto code_r0x017fbd64;
code_r0x017fbdec:
    *param_1 = plVar21[3];
    plVar21 = (long *)plVar21[4];
    param_1[1] = (long)plVar21;
    if (plVar21 == (long *)0x0) {
      return;
    }
code_r0x011d44c0:
    (*(code *)PTR__ZNSt6__ndk119__shared_weak_count12__add_sharedEv_02ca2250)(plVar21);
    return;
  }
code_r0x017fbd64:
  uVar24 = param_2[4];
  if (uVar24 != 0) {
    uVar25 = uVar24 - 1;
    if ((uVar25 & uVar24) == 0) {
      uVar19 = uVar25 & uVar27;
    }
    else {
      uVar19 = 0;
      if (uVar24 != 0) {
        uVar19 = uVar27 / uVar24;
      }
      uVar19 = uVar27 - uVar19 * uVar24;
    }
    plVar21 = *(long **)(param_2[3] + uVar19 * 8);
    if (plVar21 != (long *)0x0) {
      if ((uVar25 & uVar24) == 0) {
        do {
          plVar21 = (long *)*plVar21;
          if ((plVar21 == (long *)0x0) || ((plVar21[1] & uVar25) != uVar19)) goto code_r0x017fbe20;
        } while (*(uint *)(plVar21 + 2) != param_3);
      }
      else {
        do {
          plVar21 = (long *)*plVar21;
          if (plVar21 == (long *)0x0) goto code_r0x017fbe20;
          uVar25 = 0;
          if (uVar24 != 0) {
            uVar25 = (ulong)plVar21[1] / uVar24;
          }
          if (plVar21[1] - uVar25 * uVar24 != uVar19) goto code_r0x017fbe20;
        } while (*(uint *)(plVar21 + 2) != param_3);
      }
      if (plVar21 != (long *)0x0) goto code_r0x017fbdec;
    }
  }
code_r0x017fbe20:
  uVar24 = (**(code **)(*param_2 + 0x28))(param_2);
  if ((uVar24 & 1) == 0) {
    *param_1 = 0;
    param_1[1] = 0;
    return;
  }
  plVar28 = (long *)param_2[1];
  if (plVar28 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dc023/*"C:\BAS_Submission\Client\Project\Android\BASAndroid.NativeActivity\..\..\..\Source\Game/Parameter/Master/MasterParameterBaseSqlite.h"*/,0x4d,&UNK_027dc0a8/*"m_pConnector is null."*/);
  }
  (**(code **)(*plVar28 + 0x10))(plVar28,&UNK_027dc00a/*"sqlite/basmaster.sqlite3"*/);
  lStack_70 = 0;
  piStack_68 = (int *)0x0;
  lStack_78 = 0;
  (**(code **)(*plVar28 + 0x28))(plVar28,1,uVar27,&lStack_70,&lStack_78);
  if (lStack_78 < 1) {
    *param_1 = 0;
    param_1[1] = 0;
  }
  else {
    if ((ulong)param_2[0xd] < (ulong)param_2[0xb]) {
      plVar21 = (long *)param_2[10];
      while (plVar21 != (long *)0x0) {
        lVar26 = *plVar21;
        if (plVar21[4] != 0) {
          std::__ndk1::__shared_weak_count::__release_shared()();
        }
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar21);
        plVar21 = (long *)lVar26;
      }
      lVar26 = param_2[9];
      param_2[10] = 0;
      if (lVar26 != 0) {
        lVar22 = 0;
        do {
          *(undefined8 *)(*plVar23 + lVar22 * 8) = 0;
          lVar22 = lVar22 + 1;
        } while (lVar26 != lVar22);
      }
      param_2[0xb] = 0;
    }
    uStack_98 = 0;
    lStack_a0 = 0;
    uStack_88 = 0;
    plStack_90 = (long *)0x0;
    uStack_80 = 0x3f800000;
    void CMasterParameterBaseSqlite::DeserializeMsgPack<StringDBEelement>(Aska::TSharedArray<signed char> const&, long const&, StringDBEelement*, Framework::CSTLUnorderedMap<unsigned int, StringDBEelement, std::__ndk1::hash<unsigned int>, std::__ndk1::equal_to<unsigned int> >*) const(param_2,&lStack_70,&lStack_78,0,&lStack_a0);
    if (plStack_90 != (long *)0x0) {
      puVar1 = PTR__ZTVNSt6__ndk120__shared_ptr_emplaceI16StringDBEelement18ParameterAllocatorIS1_EEE_02cc2d78
               + 0x10;
      puVar2 = PTR__ZTV16StringDBEelement_02cbb4f0 + 0x10;
      puVar3 = PTR__ZTV22CParameterPropertyBaseILj29EE_02cc1a28 + 0x10;
      puVar4 = PTR__ZTV23CParameterPropertyValueIjLj29E18CPropertyConverterE_02cb7988 + 0x10;
      puVar5 = PTR__ZTV22CParameterPropertyBaseILj31EE_02cc17e0 + 0x10;
      puVar6 = PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj31EE_02cba990
               + 0x10;
      puVar7 = PTR__ZTV22CParameterPropertyBaseILj32EE_02cc0fa8 + 0x10;
      puVar8 = PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj32EE_02cc31e8
               + 0x10;
      puVar9 = PTR__ZTV22CParameterPropertyBaseILj33EE_02cb96b8 + 0x10;
      puVar10 = PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj33EE_02cb7cb0
                + 0x10;
      puVar11 = PTR__ZTV22CParameterPropertyBaseILj34EE_02cc0de8 + 0x10;
      puVar12 = PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj34EE_02cb8320
                + 0x10;
      plVar29 = plStack_90;
      do {
        plVar21 = (long *)operator new(unsigned long)(0x158);
        plVar21[2] = 0;
        plVar13 = plVar21 + 3;
        *plVar21 = (long)puVar1;
        plVar21[1] = 0;
        CParameterElementBase::CParameterElementBase()(plVar13);
        plVar21[3] = (long)puVar2;
        *(undefined1 *)(plVar21 + 7) = 0;
        plVar21[5] = (long)puVar3;
        plVar21[6] = 0;
        Framework::CHash32::CHash32()(plVar21 + 8);
        plVar21[5] = (long)puVar4;
        *(undefined1 *)(plVar21 + 0xd) = 0;
        plVar21[0xb] = (long)puVar5;
        plVar21[0xc] = 0;
        Framework::CHash32::CHash32()(plVar21 + 0xe);
        plVar21[0x10] = 0;
        plVar21[0x11] = 0;
        plVar21[0x14] = 0;
        plVar21[0x12] = 0;
        plVar21[0xb] = (long)puVar6;
        *(undefined1 *)(plVar21 + 0x15) = 0;
        plVar21[0x13] = (long)puVar7;
        Framework::CHash32::CHash32()(plVar21 + 0x16);
        plVar21[0x18] = 0;
        plVar21[0x19] = 0;
        plVar21[0x1c] = 0;
        plVar21[0x1a] = 0;
        plVar21[0x13] = (long)puVar8;
        *(undefined1 *)(plVar21 + 0x1d) = 0;
        plVar21[0x1b] = (long)puVar9;
        Framework::CHash32::CHash32()(plVar21 + 0x1e);
        plVar21[0x20] = 0;
        plVar21[0x21] = 0;
        plVar21[0x23] = (long)puVar11;
        plVar21[0x24] = 0;
        plVar21[0x1b] = (long)puVar10;
        plVar21[0x22] = 0;
        *(undefined1 *)(plVar21 + 0x25) = 0;
        Framework::CHash32::CHash32()(plVar21 + 0x26);
        plVar21[0x23] = (long)puVar12;
        plVar21[0x29] = 0;
        plVar21[0x2a] = 0;
        plVar21[0x28] = 0;
        StringDBEelement::operator=(StringDBEelement const&)(plVar13,plVar29 + 3);
        uVar25 = param_2[9];
        uVar15 = *(uint *)(plVar29 + 2);
        uVar24 = (ulong)uVar15;
        if (uVar25 == 0) {
code_r0x017fc170:
          lVar26 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(0x28,&UNK_027dc2d5/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_UnorderedMap.h"*/,0x1c);
          if (lVar26 == 0) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
          }
          lVar22 = plVar29[2];
          *(long **)(lVar26 + 0x18) = plVar13;
          *(long **)(lVar26 + 0x20) = plVar21;
          *(int *)(lVar26 + 0x10) = (int)lVar22;
          goto code_r0x011d44c0;
        }
        uVar19 = uVar25 - 1;
        if ((uVar19 & uVar25) == 0) {
          uVar24 = uVar19 & uVar24;
        }
        else {
          uVar18 = 0;
          if (uVar25 != 0) {
            uVar18 = uVar24 / uVar25;
          }
          uVar24 = uVar24 - uVar18 * uVar25;
        }
        plVar20 = *(long **)(*plVar23 + uVar24 * 8);
        if (plVar20 == (long *)0x0) goto code_r0x017fc170;
        if ((uVar19 & uVar25) == 0) {
          do {
            plVar20 = (long *)*plVar20;
            if ((plVar20 == (long *)0x0) || ((plVar20[1] & uVar19) != uVar24))
            goto code_r0x017fc170;
          } while (*(uint *)(plVar20 + 2) != uVar15);
        }
        else {
          do {
            plVar20 = (long *)*plVar20;
            if (plVar20 == (long *)0x0) goto code_r0x017fc170;
            uVar19 = 0;
            if (uVar25 != 0) {
              uVar19 = (ulong)plVar20[1] / uVar25;
            }
            if (plVar20[1] - uVar19 * uVar25 != uVar24) goto code_r0x017fc170;
          } while (*(uint *)(plVar20 + 2) != uVar15);
        }
        std::__ndk1::__shared_weak_count::__release_shared()(plVar21);
        plVar29 = (long *)*plVar29;
      } while (plVar29 != (long *)0x0);
    }
    uVar24 = param_2[9];
    lVar26 = lStack_a0;
    plVar29 = plStack_90;
    if (uVar24 == 0) {
code_r0x017fc388:
      *param_1 = 0;
      param_1[1] = 0;
    }
    else {
      uVar25 = uVar24 - 1;
      if ((uVar25 & uVar24) == 0) {
        uVar27 = uVar25 & uVar27;
      }
      else {
        uVar19 = 0;
        if (uVar24 != 0) {
          uVar19 = uVar27 / uVar24;
        }
        uVar27 = uVar27 - uVar19 * uVar24;
      }
      plVar23 = *(long **)(*plVar23 + uVar27 * 8);
      if (plVar23 == (long *)0x0) goto code_r0x017fc388;
      if ((uVar25 & uVar24) == 0) {
        do {
          plVar23 = (long *)*plVar23;
          if ((plVar23 == (long *)0x0) || ((plVar23[1] & uVar25) != uVar27)) goto code_r0x017fc388;
        } while (*(uint *)(plVar23 + 2) != param_3);
      }
      else {
        do {
          plVar23 = (long *)*plVar23;
          if (plVar23 == (long *)0x0) goto code_r0x017fc388;
          uVar25 = 0;
          if (uVar24 != 0) {
            uVar25 = (ulong)plVar23[1] / uVar24;
          }
          if (plVar23[1] - uVar25 * uVar24 != uVar27) goto code_r0x017fc388;
        } while (*(uint *)(plVar23 + 2) != param_3);
      }
      plVar21 = (long *)plVar23[4];
      *param_1 = plVar23[3];
      param_1[1] = (long)plVar21;
      if (plVar21 != (long *)0x0) goto code_r0x011d44c0;
    }
    while (plVar29 != (long *)0x0) {
      lVar22 = *plVar29;
      lStack_a0 = lVar26;
      StringDBEelement::~StringDBEelement()(plVar29 + 3);
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar29);
      lVar26 = lStack_a0;
      plVar29 = (long *)lVar22;
    }
    lStack_a0 = 0;
    if (lVar26 != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)();
    }
  }
  if (piStack_68 != (int *)0x0) {
    do {
      iVar14 = *piStack_68;
      cVar16 = '\x01';
      bVar17 = (bool)ExclusiveMonitorPass(piStack_68,0x10);
      if (bVar17) {
        *piStack_68 = iVar14 + -1;
        cVar16 = ExclusiveMonitorsStatus();
      }
    } while (cVar16 != '\0');
    if (iVar14 + -1 != 0) goto code_r0x017fc3f8;
  }
  if (lStack_70 != 0) {
    operator delete[](void*)();
  }
  if (piStack_68 != (int *)0x0) {
    Aska::TSharedPointerCode::DeleteCounter(int*)();
  }
code_r0x017fc3f8:
  lStack_70 = 0;
  if (plVar28 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dc023/*"C:\BAS_Submission\Client\Project\Android\BASAndroid.NativeActivity\..\..\..\Source\Game/Parameter/Master/MasterParameterBaseSqlite.h"*/,0x52,&UNK_027dc0a8/*"m_pConnector is null."*/);
  }
  (**(code **)(*plVar28 + 0x18))(plVar28);
  return;
}

// ==== void CMasterParameterBaseSqlite::DeserializeMsgPack<StringDBEelement>(Aska::TSharedArray<signed char> const&, long const&, StringDBEelement*, Framework::CSTLUnorderedMap<unsigned int, StringDBEelement, std::__ndk1::hash<unsigned int>, std::__ndk1::equal_to<unsigned int> >*) const
// vaddr 0x16fc448 | ghidra 0x17fc448 | size 2296 | symbol _ZNK26CMasterParameterBaseSqlite18DeserializeMsgPackI16StringDBEelementEEvRKN4Aska12TSharedArrayIaEERKlPT_PN9Framework16CSTLUnorderedMapIjS9_NSt6__ndk14hashIjEENSD_8equal_toIjEEEE | lib libSOA-3.7.0.so | 2026-10-08
void _ZNK26CMasterParameterBaseSqlite18DeserializeMsgPackI16StringDBEelementEEvRKN4Aska12TSharedArrayIaEERKlPT_PN9Framework16CSTLUnorderedMapIjS9_NSt6__ndk14hashIjEENSD_8equal_toIjEEEE
               (long *param_1,undefined8 *param_2,int *param_3,long *param_4,long *param_5)

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
  long lVar12;
  ulong uVar13;
  uint uVar14;
  undefined8 uVar15;
  int *piVar16;
  ulong uVar17;
  long *plVar18;
  long *plVar19;
  ulong uVar20;
  ulong uVar21;
  ulong uVar22;
  int iVar23;
  ulong unaff_x24;
  float fVar24;
  undefined1 auStack_250 [16];
  undefined1 auStack_240 [16];
  undefined *apuStack_230 [2];
  undefined *puStack_220;
  undefined8 uStack_218;
  undefined1 uStack_210;
  undefined1 auStack_208 [24];
  undefined *puStack_1f0;
  undefined8 uStack_1e8;
  undefined1 uStack_1e0;
  undefined1 auStack_1d8 [16];
  undefined8 uStack_1c8;
  undefined8 uStack_1c0;
  undefined8 uStack_1b8;
  undefined *puStack_1b0;
  undefined8 uStack_1a8;
  undefined1 uStack_1a0;
  undefined1 auStack_198 [16];
  undefined8 uStack_188;
  undefined8 uStack_180;
  undefined8 uStack_178;
  undefined *puStack_170;
  undefined8 uStack_168;
  undefined1 uStack_160;
  undefined1 auStack_158 [16];
  undefined8 uStack_148;
  undefined8 uStack_140;
  undefined8 uStack_138;
  undefined *puStack_130;
  undefined8 uStack_128;
  undefined1 uStack_120;
  undefined1 auStack_118 [16];
  undefined8 uStack_108;
  undefined8 uStack_100;
  undefined8 uStack_f8;
  undefined1 auStack_f0 [96];
  int iStack_90;
  long lStack_88;
  uint uStack_80;
  
  Aska::ASON::ASON()(auStack_f0);
  uVar14 = *param_3 << 2;
  if (uVar14 < 0x2001) {
    uVar14 = 0x2000;
  }
  Aska::ASON::Init(unsigned int, bool)(auStack_f0,uVar14,1);
  Aska::ASON::Deserialize(void const*, unsigned long)(auStack_f0,*param_2,*(undefined8 *)param_3);
  if (iStack_90 == 6) {
    if (param_5 != (long *)0x0) {
      fVar24 = (float)NEON_ucvtf(uStack_80);
      std::__ndk1::__hash_table<std::__ndk1::__hash_value_type<unsigned int, StringDBEelement>, std::__ndk1::__unordered_map_hasher<unsigned int, std::__ndk1::__hash_value_type<unsigned int, StringDBEelement>, std::__ndk1::hash<unsigned int>, true>, std::__ndk1::__unordered_map_equal<unsigned int, std::__ndk1::__hash_value_type<unsigned int, StringDBEelement>, std::__ndk1::equal_to<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__hash_value_type<unsigned int, StringDBEelement>, Framework::CSTLUnorderedMapAllocatorInf> >::rehash(unsigned long)(param_5,(long)(fVar24 / *(float *)(param_5 + 4)));
    }
    if (uStack_80 != 0) {
      puVar1 = PTR__ZTV16StringDBEelement_02cbb4f0 + 0x10;
      puVar2 = PTR__ZTV22CParameterPropertyBaseILj29EE_02cc1a28 + 0x10;
      puVar3 = PTR__ZTV23CParameterPropertyValueIjLj29E18CPropertyConverterE_02cb7988 + 0x10;
      puVar4 = PTR__ZTV22CParameterPropertyBaseILj31EE_02cc17e0 + 0x10;
      puVar5 = PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj31EE_02cba990
               + 0x10;
      puVar6 = PTR__ZTV22CParameterPropertyBaseILj32EE_02cc0fa8 + 0x10;
      puVar7 = PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj32EE_02cc31e8
               + 0x10;
      puVar8 = PTR__ZTV22CParameterPropertyBaseILj33EE_02cb96b8 + 0x10;
      puVar9 = PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj33EE_02cb7cb0
               + 0x10;
      puVar10 = PTR__ZTV22CParameterPropertyBaseILj34EE_02cc0de8 + 0x10;
      uVar17 = 0;
      puVar11 = PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj34EE_02cb8320
                + 0x10;
      do {
        lVar12 = lStack_88 + uVar17 * 0x20;
        if (lVar12 == 0) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dc023/*"C:\BAS_Submission\Client\Project\Android\BASAndroid.NativeActivity\..\..\..\Source\Game/Parameter/Master/MasterParameterBaseSqlite.h"*/,0x1b0,&UNK_0285e8d7/*"pValue is null."*/);
        }
        plVar18 = (long *)(lVar12 + 8);
        uVar15 = (**(code **)(*param_1 + 0x18))(param_1);
        piVar16 = (int *)Aska::ASON::AValue::AMap::Get_(char const*)(plVar18,uVar15);
        if (piVar16 == (int *)0x0) break;
        if (param_5 == (long *)0x0) {
          if (param_4 != (long *)0x0) goto code_r0x017fcaf8;
        }
        else {
          CParameterElementBase::CParameterElementBase()(apuStack_230);
          uStack_210 = 0;
          uStack_218 = 0;
          apuStack_230[0] = puVar1;
          puStack_220 = puVar2;
          Framework::CHash32::CHash32()(auStack_208);
          uStack_1e0 = 0;
          uStack_1e8 = 0;
          puStack_220 = puVar3;
          puStack_1f0 = puVar4;
          Framework::CHash32::CHash32()(auStack_1d8);
          uStack_1c0 = 0;
          uStack_1b8 = 0;
          uStack_1c8 = 0;
          uStack_1a0 = 0;
          uStack_1a8 = 0;
          puStack_1f0 = puVar5;
          puStack_1b0 = puVar6;
          Framework::CHash32::CHash32()(auStack_198);
          uStack_180 = 0;
          uStack_178 = 0;
          uStack_188 = 0;
          uStack_160 = 0;
          uStack_168 = 0;
          puStack_1b0 = puVar7;
          puStack_170 = puVar8;
          Framework::CHash32::CHash32()(auStack_158);
          uStack_140 = 0;
          uStack_138 = 0;
          uStack_148 = 0;
          uStack_120 = 0;
          uStack_128 = 0;
          puStack_170 = puVar9;
          puStack_130 = puVar10;
          Framework::CHash32::CHash32()(auStack_118);
          uStack_100 = 0;
          uStack_f8 = 0;
          uStack_108 = 0;
          puStack_130 = puVar11;
          StringDBEelement::Initialize()(apuStack_230);
          CParameterElementBase::Deserialize(Aska::ASON::AValue::AMap const*)(apuStack_230,plVar18);
          if (*piVar16 == 5) {
            Framework::CHash32::CHash32(char const*)(auStack_250,*(undefined8 *)(piVar16 + 4));
            uVar22 = Framework::CHash32::operator unsigned int() const(auStack_250);
            uVar22 = uVar22 & 0xffffffff;
            Framework::CHash32::~CHash32()(auStack_250);
          }
          else {
            uVar15 = (**(code **)(*param_1 + 0x18))(param_1);
            uVar22 = CParameterParser::GetValueUInt(Aska::ASON::AValue::AMap const*, char const*)(plVar18,uVar15);
            uVar14 = 0;
            if ((uVar22 & 0x100000000) != 0) {
              uVar14 = (uint)uVar22;
            }
            uVar22 = (ulong)uVar14;
          }
          uVar21 = param_5[1];
          iVar23 = (int)uVar22;
          if (uVar21 == 0) {
code_r0x017fc980:
            plVar18 = (long *)Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(0x158,&UNK_027dc2d5/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_UnorderedMap.h"*/,0x1c);
            if (plVar18 == (long *)0x0) {
              Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
            }
            *(int *)(plVar18 + 2) = iVar23;
            StringDBEelement::StringDBEelement(StringDBEelement const&)(plVar18 + 3,apuStack_230);
            *plVar18 = 0;
            plVar18[1] = uVar22;
            if ((uVar21 == 0) || (*(float *)(param_5 + 4) * (float)uVar21 < (float)(param_5[3] + 1))
               ) {
              if (uVar21 < 3) {
                uVar20 = 1;
              }
              else {
                uVar20 = (ulong)((uVar21 - 1 & uVar21) != 0);
              }
              uVar20 = uVar20 | uVar21 << 1;
              uVar21 = (ulong)((float)(param_5[3] + 1) / *(float *)(param_5 + 4));
              if (uVar21 <= uVar20) {
                uVar21 = uVar20;
              }
              std::__ndk1::__hash_table<std::__ndk1::__hash_value_type<unsigned int, StringDBEelement>, std::__ndk1::__unordered_map_hasher<unsigned int, std::__ndk1::__hash_value_type<unsigned int, StringDBEelement>, std::__ndk1::hash<unsigned int>, true>, std::__ndk1::__unordered_map_equal<unsigned int, std::__ndk1::__hash_value_type<unsigned int, StringDBEelement>, std::__ndk1::equal_to<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__hash_value_type<unsigned int, StringDBEelement>, Framework::CSTLUnorderedMapAllocatorInf> >::rehash(unsigned long)(param_5,uVar21);
              uVar21 = param_5[1];
              if ((uVar21 - 1 & uVar21) == 0) {
                unaff_x24 = uVar21 - 1 & uVar22;
              }
              else {
                uVar20 = 0;
                if (uVar21 != 0) {
                  uVar20 = uVar22 / uVar21;
                }
                unaff_x24 = uVar22 - uVar20 * uVar21;
              }
            }
            plVar19 = *(long **)(*param_5 + unaff_x24 * 8);
            if (plVar19 == (long *)0x0) {
              *plVar18 = param_5[2];
              param_5[2] = (long)plVar18;
              *(long **)(*param_5 + unaff_x24 * 8) = param_5 + 2;
              if (*plVar18 != 0) {
                uVar22 = *(ulong *)(*plVar18 + 8);
                if ((uVar21 - 1 & uVar21) == 0) {
                  uVar22 = uVar22 & uVar21 - 1;
                }
                else {
                  uVar20 = 0;
                  if (uVar21 != 0) {
                    uVar20 = uVar22 / uVar21;
                  }
                  uVar22 = uVar22 - uVar20 * uVar21;
                }
                plVar19 = (long *)(*param_5 + uVar22 * 8);
                goto code_r0x017fcaa8;
              }
            }
            else {
              *plVar18 = *plVar19;
code_r0x017fcaa8:
              *plVar19 = (long)plVar18;
            }
            param_5[3] = param_5[3] + 1;
          }
          else {
            uVar20 = uVar21 - 1;
            if ((uVar20 & uVar21) == 0) {
              unaff_x24 = uVar20 & uVar22;
            }
            else {
              uVar13 = 0;
              if (uVar21 != 0) {
                uVar13 = uVar22 / uVar21;
              }
              unaff_x24 = uVar22 - uVar13 * uVar21;
            }
            plVar18 = *(long **)(*param_5 + unaff_x24 * 8);
            if (plVar18 == (long *)0x0) goto code_r0x017fc980;
            if ((uVar20 & uVar21) == 0) {
              do {
                plVar18 = (long *)*plVar18;
                if ((plVar18 == (long *)0x0) || ((plVar18[1] & uVar20) != unaff_x24))
                goto code_r0x017fc980;
              } while ((int)plVar18[2] != iVar23);
            }
            else {
              do {
                plVar18 = (long *)*plVar18;
                if (plVar18 == (long *)0x0) goto code_r0x017fc980;
                uVar20 = 0;
                if (uVar21 != 0) {
                  uVar20 = (ulong)plVar18[1] / uVar21;
                }
                if (plVar18[1] - uVar20 * uVar21 != unaff_x24) goto code_r0x017fc980;
              } while (*(int *)(plVar18 + 2) != iVar23);
            }
          }
          StringDBEelement::~StringDBEelement()(apuStack_230);
        }
        uVar14 = (int)uVar17 + 1;
        uVar17 = (ulong)uVar14;
      } while (uVar14 < uStack_80);
    }
    goto code_r0x017fcd18;
  }
  if (iStack_90 != 7) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dc023/*"C:\BAS_Submission\Client\Project\Android\BASAndroid.NativeActivity\..\..\..\Source\Game/Parameter/Master/MasterParameterBaseSqlite.h"*/,0x1d7,&UNK_027dc0be/*"msgpack format invalid."*/);
    goto code_r0x017fcd18;
  }
  plVar18 = &lStack_88;
  if (param_5 == (long *)0x0) {
    if (param_4 != (long *)0x0) {
code_r0x017fcaf8:
      (**(code **)*param_4)(param_4);
      (**(code **)(*param_4 + 8))(param_4,plVar18);
    }
    goto code_r0x017fcd18;
  }
  CParameterElementBase::CParameterElementBase()(apuStack_230);
  uStack_210 = 0;
  apuStack_230[0] = PTR__ZTV16StringDBEelement_02cbb4f0 + 0x10;
  puStack_220 = PTR__ZTV22CParameterPropertyBaseILj29EE_02cc1a28 + 0x10;
  uStack_218 = 0;
  Framework::CHash32::CHash32()(auStack_208);
  uStack_1e0 = 0;
  puStack_220 = PTR__ZTV23CParameterPropertyValueIjLj29E18CPropertyConverterE_02cb7988 + 0x10;
  puStack_1f0 = PTR__ZTV22CParameterPropertyBaseILj31EE_02cc17e0 + 0x10;
  uStack_1e8 = 0;
  Framework::CHash32::CHash32()(auStack_1d8);
  uStack_1c0 = 0;
  uStack_1b8 = 0;
  puStack_1f0 = PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj31EE_02cba990
                + 0x10;
  puStack_1b0 = PTR__ZTV22CParameterPropertyBaseILj32EE_02cc0fa8 + 0x10;
  uStack_1c8 = 0;
  uStack_1a8 = 0;
  uStack_1a0 = 0;
  Framework::CHash32::CHash32()(auStack_198);
  uStack_180 = 0;
  uStack_178 = 0;
  puStack_1b0 = PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj32EE_02cc31e8
                + 0x10;
  puStack_170 = PTR__ZTV22CParameterPropertyBaseILj33EE_02cb96b8 + 0x10;
  uStack_188 = 0;
  uStack_168 = 0;
  uStack_160 = 0;
  Framework::CHash32::CHash32()(auStack_158);
  uStack_140 = 0;
  uStack_138 = 0;
  puStack_170 = PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj33EE_02cb7cb0
                + 0x10;
  puStack_130 = PTR__ZTV22CParameterPropertyBaseILj34EE_02cc0de8 + 0x10;
  uStack_148 = 0;
  uStack_128 = 0;
  uStack_120 = 0;
  Framework::CHash32::CHash32()(auStack_118);
  uStack_100 = 0;
  uStack_f8 = 0;
  uStack_108 = 0;
  puStack_130 = PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj34EE_02cb8320
                + 0x10;
  StringDBEelement::Initialize()(apuStack_230);
  CParameterElementBase::Deserialize(Aska::ASON::AValue::AMap const*)(apuStack_230,plVar18);
  uVar15 = (**(code **)(*param_1 + 0x18))(param_1);
  piVar16 = (int *)Aska::ASON::AValue::AMap::Get_(char const*)(plVar18,uVar15);
  if (piVar16 != (int *)0x0) {
    if (*piVar16 == 5) {
      Framework::CHash32::CHash32(char const*)(auStack_240,*(undefined8 *)(piVar16 + 4));
      uVar17 = Framework::CHash32::operator unsigned int() const(auStack_240);
      uVar17 = uVar17 & 0xffffffff;
      Framework::CHash32::~CHash32()(auStack_240);
    }
    else {
      uVar15 = (**(code **)(*param_1 + 0x18))(param_1);
      uVar17 = CParameterParser::GetValueUInt(Aska::ASON::AValue::AMap const*, char const*)(plVar18,uVar15);
      uVar14 = 0;
      if ((uVar17 & 0x100000000) != 0) {
        uVar14 = (uint)uVar17;
      }
      uVar17 = (ulong)uVar14;
    }
    uVar22 = param_5[1];
    iVar23 = (int)uVar17;
    if (uVar22 != 0) {
      uVar21 = uVar22 - 1;
      if ((uVar21 & uVar22) == 0) {
        unaff_x24 = uVar21 & uVar17;
      }
      else {
        uVar20 = 0;
        if (uVar22 != 0) {
          uVar20 = uVar17 / uVar22;
        }
        unaff_x24 = uVar17 - uVar20 * uVar22;
      }
      plVar18 = *(long **)(*param_5 + unaff_x24 * 8);
      if (plVar18 != (long *)0x0) {
        if ((uVar21 & uVar22) == 0) {
          do {
            plVar18 = (long *)*plVar18;
            if ((plVar18 == (long *)0x0) || ((plVar18[1] & uVar21) != unaff_x24))
            goto code_r0x017fcbd8;
          } while ((int)plVar18[2] != iVar23);
        }
        else {
          do {
            plVar18 = (long *)*plVar18;
            if (plVar18 == (long *)0x0) goto code_r0x017fcbd8;
            uVar21 = 0;
            if (uVar22 != 0) {
              uVar21 = (ulong)plVar18[1] / uVar22;
            }
            if (plVar18[1] - uVar21 * uVar22 != unaff_x24) goto code_r0x017fcbd8;
          } while (*(int *)(plVar18 + 2) != iVar23);
        }
        goto code_r0x017fcd10;
      }
    }
code_r0x017fcbd8:
    plVar18 = (long *)Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(0x158,&UNK_027dc2d5/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_UnorderedMap.h"*/,0x1c);
    if (plVar18 == (long *)0x0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    }
    *(int *)(plVar18 + 2) = iVar23;
    StringDBEelement::StringDBEelement(StringDBEelement const&)(plVar18 + 3,apuStack_230);
    *plVar18 = 0;
    plVar18[1] = uVar17;
    if ((uVar22 == 0) || (*(float *)(param_5 + 4) * (float)uVar22 < (float)(param_5[3] + 1))) {
      if (uVar22 < 3) {
        uVar21 = 1;
      }
      else {
        uVar21 = (ulong)((uVar22 - 1 & uVar22) != 0);
      }
      uVar21 = uVar21 | uVar22 << 1;
      uVar22 = (ulong)((float)(param_5[3] + 1) / *(float *)(param_5 + 4));
      if (uVar22 <= uVar21) {
        uVar22 = uVar21;
      }
      std::__ndk1::__hash_table<std::__ndk1::__hash_value_type<unsigned int, StringDBEelement>, std::__ndk1::__unordered_map_hasher<unsigned int, std::__ndk1::__hash_value_type<unsigned int, StringDBEelement>, std::__ndk1::hash<unsigned int>, true>, std::__ndk1::__unordered_map_equal<unsigned int, std::__ndk1::__hash_value_type<unsigned int, StringDBEelement>, std::__ndk1::equal_to<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__hash_value_type<unsigned int, StringDBEelement>, Framework::CSTLUnorderedMapAllocatorInf> >::rehash(unsigned long)(param_5,uVar22);
      uVar22 = param_5[1];
      if ((uVar22 - 1 & uVar22) == 0) {
        unaff_x24 = uVar22 - 1 & uVar17;
      }
      else {
        uVar21 = 0;
        if (uVar22 != 0) {
          uVar21 = uVar17 / uVar22;
        }
        unaff_x24 = uVar17 - uVar21 * uVar22;
      }
    }
    plVar19 = *(long **)(*param_5 + unaff_x24 * 8);
    if (plVar19 == (long *)0x0) {
      plVar19 = param_5 + 2;
      *plVar18 = *plVar19;
      *plVar19 = (long)plVar18;
      *(long **)(*param_5 + unaff_x24 * 8) = plVar19;
      if (*plVar18 != 0) {
        uVar17 = *(ulong *)(*plVar18 + 8);
        if ((uVar22 - 1 & uVar22) == 0) {
          uVar17 = uVar17 & uVar22 - 1;
        }
        else {
          uVar21 = 0;
          if (uVar22 != 0) {
            uVar21 = uVar17 / uVar22;
          }
          uVar17 = uVar17 - uVar21 * uVar22;
        }
        plVar19 = (long *)(*param_5 + uVar17 * 8);
        goto code_r0x017fcd00;
      }
    }
    else {
      *plVar18 = *plVar19;
code_r0x017fcd00:
      *plVar19 = (long)plVar18;
    }
    param_5[3] = param_5[3] + 1;
  }
code_r0x017fcd10:
  StringDBEelement::~StringDBEelement()(apuStack_230);
code_r0x017fcd18:
  Aska::ASON::~ASON()(auStack_f0);
  return;
}

// ==== StringDBEelement::operator=(StringDBEelement const&)
// vaddr 0x16fcd40 | ghidra 0x17fcd40 | size 944 | symbol _ZN16StringDBEelementaSERKS_ | lib libSOA-3.7.0.so | 2026-10-08
long _ZN16StringDBEelementaSERKS_(long param_1,long param_2)

{
  ulong *puVar1;
  ulong uVar2;
  long lVar3;
  ulong uVar4;
  ulong uVar5;
  long lVar6;
  
  *(undefined8 *)(param_1 + 8) = *(undefined8 *)(param_2 + 8);
  *(undefined8 *)(param_1 + 0x18) = *(undefined8 *)(param_2 + 0x18);
  *(undefined1 *)(param_1 + 0x20) = *(undefined1 *)(param_2 + 0x20);
  *(undefined4 *)(param_1 + 0x30) = *(undefined4 *)(param_2 + 0x30);
  *(undefined4 *)(param_1 + 0x38) = *(undefined4 *)(param_2 + 0x38);
  *(undefined8 *)(param_1 + 0x48) = *(undefined8 *)(param_2 + 0x48);
  *(undefined1 *)(param_1 + 0x50) = *(undefined1 *)(param_2 + 0x50);
  *(undefined4 *)(param_1 + 0x60) = *(undefined4 *)(param_2 + 0x60);
  if (param_1 != param_2) {
    puVar1 = (ulong *)(param_1 + 0x68);
    uVar2 = *(ulong *)(param_2 + 0x70);
    lVar3 = *(long *)(param_2 + 0x78);
    uVar5 = (ulong)*(byte *)puVar1;
    if ((*(byte *)(param_2 + 0x68) & 1) == 0) {
      lVar3 = param_2 + 0x69;
      uVar2 = (ulong)(*(byte *)(param_2 + 0x68) >> 1);
    }
    if ((*(byte *)puVar1 & 1) == 0) {
      uVar4 = 0x16;
      lVar6 = uVar2 - 0x16;
      if (0x15 < uVar2 && lVar6 != 0) {
code_r0x017fcdf4:
        if ((uVar5 & 1) == 0) {
          uVar5 = (ulong)(((uint)uVar5 & 0xfe) >> 1);
        }
        else {
          uVar5 = *(ulong *)(param_1 + 0x70);
        }
        string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(puVar1,uVar4,lVar6,uVar5,0,uVar5,uVar2);
        goto code_r0x017fce54;
      }
    }
    else {
      uVar5 = *puVar1;
      uVar4 = (uVar5 & 0xfffffffffffffffe) - 1;
      lVar6 = uVar2 - uVar4;
      if (uVar4 <= uVar2 && lVar6 != 0) goto code_r0x017fcdf4;
    }
    if ((uVar5 & 1) == 0) {
      lVar6 = param_1 + 0x69;
    }
    else {
      lVar6 = *(long *)(param_1 + 0x78);
    }
    if (uVar2 != 0) {
      memmove(lVar6,lVar3,uVar2);
    }
    *(undefined1 *)(lVar6 + uVar2) = 0;
    if ((*(byte *)puVar1 & 1) == 0) {
      *(byte *)puVar1 = (byte)(uVar2 << 1);
    }
    else {
      *(ulong *)(param_1 + 0x70) = uVar2;
    }
  }
code_r0x017fce54:
  *(undefined8 *)(param_1 + 0x88) = *(undefined8 *)(param_2 + 0x88);
  *(undefined1 *)(param_1 + 0x90) = *(undefined1 *)(param_2 + 0x90);
  *(undefined4 *)(param_1 + 0xa0) = *(undefined4 *)(param_2 + 0xa0);
  if (param_1 != param_2) {
    puVar1 = (ulong *)(param_1 + 0xa8);
    uVar2 = *(ulong *)(param_2 + 0xb0);
    lVar3 = *(long *)(param_2 + 0xb8);
    uVar5 = (ulong)*(byte *)puVar1;
    if ((*(byte *)(param_2 + 0xa8) & 1) == 0) {
      lVar3 = param_2 + 0xa9;
      uVar2 = (ulong)(*(byte *)(param_2 + 0xa8) >> 1);
    }
    if ((*(byte *)puVar1 & 1) == 0) {
      uVar4 = 0x16;
      lVar6 = uVar2 - 0x16;
      if (0x15 < uVar2 && lVar6 != 0) {
code_r0x017fcecc:
        if ((uVar5 & 1) == 0) {
          uVar5 = (ulong)(((uint)uVar5 & 0xfe) >> 1);
        }
        else {
          uVar5 = *(ulong *)(param_1 + 0xb0);
        }
        string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(puVar1,uVar4,lVar6,uVar5,0,uVar5,uVar2);
        goto code_r0x017fcf2c;
      }
    }
    else {
      uVar5 = *puVar1;
      uVar4 = (uVar5 & 0xfffffffffffffffe) - 1;
      lVar6 = uVar2 - uVar4;
      if (uVar4 <= uVar2 && lVar6 != 0) goto code_r0x017fcecc;
    }
    if ((uVar5 & 1) == 0) {
      lVar6 = param_1 + 0xa9;
    }
    else {
      lVar6 = *(long *)(param_1 + 0xb8);
    }
    if (uVar2 != 0) {
      memmove(lVar6,lVar3,uVar2);
    }
    *(undefined1 *)(lVar6 + uVar2) = 0;
    if ((*(byte *)puVar1 & 1) == 0) {
      *(byte *)puVar1 = (byte)(uVar2 << 1);
    }
    else {
      *(ulong *)(param_1 + 0xb0) = uVar2;
    }
  }
code_r0x017fcf2c:
  *(undefined8 *)(param_1 + 200) = *(undefined8 *)(param_2 + 200);
  *(undefined1 *)(param_1 + 0xd0) = *(undefined1 *)(param_2 + 0xd0);
  *(undefined4 *)(param_1 + 0xe0) = *(undefined4 *)(param_2 + 0xe0);
  if (param_1 != param_2) {
    puVar1 = (ulong *)(param_1 + 0xe8);
    uVar2 = *(ulong *)(param_2 + 0xf0);
    lVar3 = *(long *)(param_2 + 0xf8);
    uVar5 = (ulong)*(byte *)puVar1;
    if ((*(byte *)(param_2 + 0xe8) & 1) == 0) {
      lVar3 = param_2 + 0xe9;
      uVar2 = (ulong)(*(byte *)(param_2 + 0xe8) >> 1);
    }
    if ((*(byte *)puVar1 & 1) == 0) {
      uVar4 = 0x16;
      lVar6 = uVar2 - 0x16;
      if (0x15 < uVar2 && lVar6 != 0) {
code_r0x017fcfa4:
        if ((uVar5 & 1) == 0) {
          uVar5 = (ulong)(((uint)uVar5 & 0xfe) >> 1);
        }
        else {
          uVar5 = *(ulong *)(param_1 + 0xf0);
        }
        string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(puVar1,uVar4,lVar6,uVar5,0,uVar5,uVar2);
        goto code_r0x017fd004;
      }
    }
    else {
      uVar5 = *puVar1;
      uVar4 = (uVar5 & 0xfffffffffffffffe) - 1;
      lVar6 = uVar2 - uVar4;
      if (uVar4 <= uVar2 && lVar6 != 0) goto code_r0x017fcfa4;
    }
    if ((uVar5 & 1) == 0) {
      lVar6 = param_1 + 0xe9;
    }
    else {
      lVar6 = *(long *)(param_1 + 0xf8);
    }
    if (uVar2 != 0) {
      memmove(lVar6,lVar3,uVar2);
    }
    *(undefined1 *)(lVar6 + uVar2) = 0;
    if ((*(byte *)puVar1 & 1) == 0) {
      *(byte *)puVar1 = (byte)(uVar2 << 1);
    }
    else {
      *(ulong *)(param_1 + 0xf0) = uVar2;
    }
  }
code_r0x017fd004:
  *(undefined8 *)(param_1 + 0x108) = *(undefined8 *)(param_2 + 0x108);
  *(undefined1 *)(param_1 + 0x110) = *(undefined1 *)(param_2 + 0x110);
  *(undefined4 *)(param_1 + 0x120) = *(undefined4 *)(param_2 + 0x120);
  if (param_1 == param_2) {
    return param_1;
  }
  puVar1 = (ulong *)(param_1 + 0x128);
  uVar2 = *(ulong *)(param_2 + 0x130);
  lVar3 = *(long *)(param_2 + 0x138);
  uVar5 = (ulong)*(byte *)puVar1;
  if ((*(byte *)(param_2 + 0x128) & 1) == 0) {
    lVar3 = param_2 + 0x129;
    uVar2 = (ulong)(*(byte *)(param_2 + 0x128) >> 1);
  }
  if ((*(byte *)puVar1 & 1) == 0) {
    uVar4 = 0x16;
    lVar6 = uVar2 - 0x16;
    if (0x15 < uVar2 && lVar6 != 0) {
code_r0x017fd07c:
      if ((uVar5 & 1) == 0) {
        uVar5 = (ulong)(((uint)uVar5 & 0xfe) >> 1);
      }
      else {
        uVar5 = *(ulong *)(param_1 + 0x130);
      }
      string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(puVar1,uVar4,lVar6,uVar5,0,uVar5,uVar2);
      return param_1;
    }
  }
  else {
    uVar5 = *puVar1;
    uVar4 = (uVar5 & 0xfffffffffffffffe) - 1;
    lVar6 = uVar2 - uVar4;
    if (uVar4 <= uVar2 && lVar6 != 0) goto code_r0x017fd07c;
  }
  if ((uVar5 & 1) == 0) {
    lVar6 = param_1 + 0x129;
  }
  else {
    lVar6 = *(long *)(param_1 + 0x138);
  }
  if (uVar2 != 0) {
    memmove(lVar6,lVar3,uVar2);
  }
  *(undefined1 *)(lVar6 + uVar2) = 0;
  if ((*(byte *)puVar1 & 1) == 0) {
    *(byte *)puVar1 = (byte)(uVar2 << 1);
  }
  else {
    *(ulong *)(param_1 + 0x130) = uVar2;
  }
  return param_1;
}

// ==== StringDBEelement::Initialize()
// vaddr 0x16fd0f0 | ghidra 0x17fd0f0 | size 480 | symbol _ZN16StringDBEelement10InitializeEv | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN16StringDBEelement10InitializeEv(long param_1)

{
  byte bStack_48;
  undefined2 uStack_47;
  undefined1 uStack_45;
  undefined4 uStack_44;
  undefined1 uStack_40;
  undefined2 uStack_3f;
  undefined1 uStack_3d;
  undefined4 uStack_3c;
  undefined8 uStack_38;
  
  uStack_40 = 0;
  uStack_3f = 0;
  uStack_3d = 0;
  uStack_3c = 0;
  uStack_38 = 0;
  uStack_44 = 0;
  bStack_48 = 4;
  uStack_47 = 0x6469;
  uStack_45 = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x28,(ulong)&bStack_48 | 1);
  *(undefined1 *)(param_1 + 0x20) = 1;
  *(undefined4 *)(param_1 + 0x38) = 0;
  if ((bStack_48 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_38);
  }
  CParameterElementBase::AddProperty(IParameterProperty*)(param_1,param_1 + 0x10);
  uStack_3c = 0;
  uStack_38 = 0;
  bStack_48 = 0x14;
  uStack_47 = (undefined2)_UNK_028473e4;
  uStack_45 = (undefined1)((ulong)_UNK_028473e4 >> 0x10);
  uStack_44 = (undefined4)((ulong)_UNK_028473e4 >> 0x18);
  uStack_40 = (undefined1)((ulong)_UNK_028473e4 >> 0x38);
  uStack_3f = 0x6469;
  uStack_3d = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x58,(ulong)&bStack_48 | 1);
  *(undefined1 *)(param_1 + 0x50) = 1;
  if ((bStack_48 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_38);
  }
  CParameterElementBase::AddProperty(IParameterProperty*)(param_1,param_1 + 0x40);
  uStack_3c = 0;
  uStack_38 = 0;
  bStack_48 = 0x14;
  uStack_47 = (undefined2)_UNK_0285ec06;
  uStack_45 = (undefined1)((ulong)_UNK_0285ec06 >> 0x10);
  uStack_44 = (undefined4)((ulong)_UNK_0285ec06 >> 0x18);
  uStack_40 = (undefined1)((ulong)_UNK_0285ec06 >> 0x38);
  uStack_3f = 0x6575;
  uStack_3d = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x98,(ulong)&bStack_48 | 1);
  *(undefined1 *)(param_1 + 0x90) = 1;
  if ((bStack_48 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_38);
  }
  CParameterElementBase::AddProperty(IParameterProperty*)(param_1,param_1 + 0x80);
  uStack_3d = 0;
  uStack_3c = 0;
  uStack_38 = 0;
  bStack_48 = 0x12;
  uStack_47 = (undefined2)_UNK_0285ec11;
  uStack_45 = (undefined1)((ulong)_UNK_0285ec11 >> 0x10);
  uStack_44 = (undefined4)((ulong)_UNK_0285ec11 >> 0x18);
  uStack_40 = (undefined1)((ulong)_UNK_0285ec11 >> 0x38);
  uStack_3f = 0x61;
  Framework::CHash32::operator=(char const*)(param_1 + 0xd8,(ulong)&bStack_48 | 1);
  *(undefined1 *)(param_1 + 0xd0) = 1;
  if ((bStack_48 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_38);
  }
  CParameterElementBase::AddProperty(IParameterProperty*)(param_1,param_1 + 0xc0);
  uStack_3d = 0;
  uStack_3c = 0;
  uStack_38 = 0;
  bStack_48 = 0x12;
  uStack_47 = (undefined2)_UNK_027f805d;
  uStack_45 = (undefined1)((ulong)_UNK_027f805d >> 0x10);
  uStack_44 = (undefined4)((ulong)_UNK_027f805d >> 0x18);
  uStack_40 = (undefined1)((ulong)_UNK_027f805d >> 0x38);
  uStack_3f = 0x65;
  Framework::CHash32::operator=(char const*)(param_1 + 0x118,(ulong)&bStack_48 | 1);
  *(undefined1 *)(param_1 + 0x110) = 1;
  if ((bStack_48 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_38);
  }
  CParameterElementBase::AddProperty(IParameterProperty*)(param_1,param_1 + 0x100);
  return;
}

// ==== StringDBEelement::~StringDBEelement()
// vaddr 0x16fd2d0 | ghidra 0x17fd2d0 | size 276 | symbol _ZN16StringDBEelementD2Ev | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Possible PIC construction at 0x017fd31c: Changing call to branch */
/* WARNING: Possible PIC construction at 0x017fd354: Changing call to branch */
/* WARNING: Possible PIC construction at 0x017fd38c: Changing call to branch */
/* WARNING: Possible PIC construction at 0x017fd3c4: Changing call to branch */
/* WARNING: Removing unreachable block (ram,0x017fd390) */
/* WARNING: Removing unreachable block (ram,0x017fd3a8) */
/* WARNING: Removing unreachable block (ram,0x017fd3b0) */
/* WARNING: Removing unreachable block (ram,0x017fd358) */
/* WARNING: Removing unreachable block (ram,0x017fd370) */
/* WARNING: Removing unreachable block (ram,0x017fd378) */
/* WARNING: Removing unreachable block (ram,0x017fd320) */
/* WARNING: Removing unreachable block (ram,0x017fd338) */
/* WARNING: Removing unreachable block (ram,0x017fd340) */
/* WARNING: Removing unreachable block (ram,0x017fd3c8) */

void _ZN16StringDBEelementD2Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTV16StringDBEelement_02cbb4f0 + 0x10);
  param_1[0x20] =
       (long)(
             PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj34EE_02cb8320
             + 0x10);
  if ((*(byte *)(param_1 + 0x25) & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(param_1[0x27]);
  }
  param_1[0x20] = (long)(PTR__ZTV22CParameterPropertyBaseILj34EE_02cc0de8 + 0x10);
  (*(code *)PTR__ZN9Framework7CHash32D1Ev_02cb3740)(param_1 + 0x23);
  return;
}

// ==== StringDBEelement::~StringDBEelement()
// vaddr 0x16fd3e4 | ghidra 0x17fd3e4 | size 24 | symbol _ZN16StringDBEelementD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN16StringDBEelementD0Ev(undefined8 param_1)

{
  StringDBEelement::~StringDBEelement()();
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== std::__ndk1::__hash_table<std::__ndk1::__hash_value_type<unsigned int, StringDBEelement>, std::__ndk1::__unordered_map_hasher<unsigned int, std::__ndk1::__hash_value_type<unsigned int, StringDBEelement>, std::__ndk1::hash<unsigned int>, true>, std::__ndk1::__unordered_map_equal<unsigned int, std::__ndk1::__hash_value_type<unsigned int, StringDBEelement>, std::__ndk1::equal_to<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__hash_value_type<unsigned int, StringDBEelement>, Framework::CSTLUnorderedMapAllocatorInf> >::rehash(unsigned long)
// vaddr 0x16fd3fc | ghidra 0x17fd3fc | size 208 | symbol _ZNSt6__ndk112__hash_tableINS_17__hash_value_typeIj16StringDBEelementEENS_22__unordered_map_hasherIjS3_NS_4hashIjEELb1EEENS_21__unordered_map_equalIjS3_NS_8equal_toIjEELb1EEEN9Framework13CSTLAllocatorIS3_NSC_28CSTLUnorderedMapAllocatorInfEEEE6rehashEm | lib libSOA-3.7.0.so | 2026-10-08
void _ZNSt6__ndk112__hash_tableINS_17__hash_value_typeIj16StringDBEelementEENS_22__unordered_map_hasherIjS3_NS_4hashIjEELb1EEENS_21__unordered_map_equalIjS3_NS_8equal_toIjEELb1EEEN9Framework13CSTLAllocatorIS3_NSC_28CSTLUnorderedMapAllocatorInfEEEE6rehashEm
               (long param_1,ulong param_2)

{
  ulong uVar1;
  ulong uVar2;
  
  if (param_2 - 1 == 0) {
    param_2 = 2;
  }
  else if ((param_2 - 1 & param_2) != 0) {
    param_2 = std::__ndk1::__next_prime(unsigned long)(param_2);
  }
  uVar2 = *(ulong *)(param_1 + 8);
  uVar1 = param_2;
  if (uVar2 < param_2) {
code_r0x011d1d70:
    (*(code *)
      PTR__ZNSt6__ndk112__hash_tableINS_17__hash_value_typeIj16StringDBEelementEENS_22__unordered_map_hasherIjS3_NS_4hashIjEELb1EEENS_21__unordered_map_equalIjS3_NS_8equal_toIjEELb1EEEN9Framework13CSTLAllocatorIS3_NSC_28CSTLUnorderedMapAllocatorInfEEEE8__rehashEm_02ca0ea8
    )(param_1,uVar1);
    return;
  }
  if (param_2 < uVar2) {
    if (uVar2 < 3 || (uVar2 - 1 & uVar2) != 0) {
      uVar1 = std::__ndk1::__next_prime(unsigned long)();
    }
    else {
      uVar1 = 1L << (0x40U - LZCOUNT((long)((float)*(ulong *)(param_1 + 0x18) /
                                           *(float *)(param_1 + 0x20)) + -1) & 0x3f);
    }
    if (uVar1 <= param_2) {
      uVar1 = param_2;
    }
    if (uVar1 < uVar2) goto code_r0x011d1d70;
  }
  return;
}

// ==== StringDBEelement::StringDBEelement(StringDBEelement const&)
// vaddr 0x16fd4cc | ghidra 0x17fd4cc | size 1212 | symbol _ZN16StringDBEelementC2ERKS_ | lib libSOA-3.7.0.so | 2026-10-08
void _ZN16StringDBEelementC2ERKS_(long *param_1,long param_2)

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
  puVar5 = PTR__ZTV16StringDBEelement_02cbb4f0;
  *param_1 = (long)(PTR__ZTV21CParameterElementBase_02cbbc00 + 0x10);
  lVar8 = *(long *)(param_2 + 8);
  *param_1 = (long)(puVar5 + 0x10);
  param_1[1] = lVar8;
  param_1[2] = (long)(puVar7 + 0x10);
  lVar8 = *(long *)(param_2 + 0x18);
  param_1[2] = (long)(PTR__ZTV22CParameterPropertyBaseILj29EE_02cc1a28 + 0x10);
  param_1[3] = lVar8;
  puVar6 = PTR__ZTVN9Framework7CHash32E_02cba528;
  *(undefined1 *)(param_1 + 4) = *(undefined1 *)(param_2 + 0x20);
  param_1[5] = (long)(puVar6 + 0x10);
  puVar5 = PTR__ZTV23CParameterPropertyValueIjLj29E18CPropertyConverterE_02cb7988;
  *(undefined4 *)(param_1 + 6) = *(undefined4 *)(param_2 + 0x30);
  param_1[2] = (long)(puVar5 + 0x10);
  uVar3 = *(undefined4 *)(param_2 + 0x38);
  param_1[8] = (long)(puVar7 + 0x10);
  *(undefined4 *)(param_1 + 7) = uVar3;
  lVar8 = *(long *)(param_2 + 0x48);
  param_1[8] = (long)(PTR__ZTV22CParameterPropertyBaseILj31EE_02cc17e0 + 0x10);
  param_1[9] = lVar8;
  uVar4 = *(undefined1 *)(param_2 + 0x50);
  param_1[0xb] = (long)(puVar6 + 0x10);
  *(undefined1 *)(param_1 + 10) = uVar4;
  puVar5 = 
  PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj31EE_02cba990
  ;
  uVar3 = *(undefined4 *)(param_2 + 0x60);
  plVar9 = param_1 + 0xd;
  *plVar9 = 0;
  *(undefined4 *)(param_1 + 0xc) = uVar3;
  param_1[8] = (long)(puVar5 + 0x10);
  param_1[0xe] = 0;
  param_1[0xf] = 0;
  if ((*(byte *)(param_2 + 0x68) & 1) == 0) {
    param_1[0xf] = *(long *)(param_2 + 0x78);
    lVar8 = *(long *)(param_2 + 0x68);
    param_1[0xe] = *(long *)(param_2 + 0x70);
    *plVar9 = lVar8;
  }
  else {
    uVar1 = *(ulong *)(param_2 + 0x70);
    uVar2 = *(undefined8 *)(param_2 + 0x78);
    if (uVar1 < 0x17) {
      lVar8 = (long)param_1 + 0x69;
      *(char *)plVar9 = (char)(uVar1 << 1);
      if (uVar1 != 0) goto code_r0x017fd650;
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
      param_1[0xe] = uVar1;
      param_1[0xf] = lVar8;
      param_1[0xd] = uVar10 | 1;
code_r0x017fd650:
      memcpy(lVar8,uVar2,uVar1);
    }
    *(undefined1 *)(lVar8 + uVar1) = 0;
  }
  param_1[0x10] = (long)(puVar7 + 0x10);
  lVar8 = *(long *)(param_2 + 0x88);
  param_1[0x10] = (long)(PTR__ZTV22CParameterPropertyBaseILj32EE_02cc0fa8 + 0x10);
  param_1[0x11] = lVar8;
  uVar4 = *(undefined1 *)(param_2 + 0x90);
  param_1[0x13] = (long)(puVar6 + 0x10);
  *(undefined1 *)(param_1 + 0x12) = uVar4;
  puVar5 = 
  PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj32EE_02cc31e8
  ;
  uVar3 = *(undefined4 *)(param_2 + 0xa0);
  plVar9 = param_1 + 0x15;
  *plVar9 = 0;
  *(undefined4 *)(param_1 + 0x14) = uVar3;
  param_1[0x10] = (long)(puVar5 + 0x10);
  param_1[0x16] = 0;
  param_1[0x17] = 0;
  if ((*(byte *)(param_2 + 0xa8) & 1) == 0) {
    param_1[0x17] = *(long *)(param_2 + 0xb8);
    lVar8 = *(long *)(param_2 + 0xa8);
    param_1[0x16] = *(long *)(param_2 + 0xb0);
    *plVar9 = lVar8;
  }
  else {
    uVar1 = *(ulong *)(param_2 + 0xb0);
    uVar2 = *(undefined8 *)(param_2 + 0xb8);
    if (uVar1 < 0x17) {
      lVar8 = (long)param_1 + 0xa9;
      *(char *)plVar9 = (char)(uVar1 << 1);
      if (uVar1 != 0) goto code_r0x017fd754;
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
      param_1[0x16] = uVar1;
      param_1[0x17] = lVar8;
      param_1[0x15] = uVar10 | 1;
code_r0x017fd754:
      memcpy(lVar8,uVar2,uVar1);
    }
    *(undefined1 *)(lVar8 + uVar1) = 0;
  }
  param_1[0x18] = (long)(puVar7 + 0x10);
  lVar8 = *(long *)(param_2 + 200);
  param_1[0x18] = (long)(PTR__ZTV22CParameterPropertyBaseILj33EE_02cb96b8 + 0x10);
  param_1[0x19] = lVar8;
  uVar4 = *(undefined1 *)(param_2 + 0xd0);
  param_1[0x1b] = (long)(puVar6 + 0x10);
  *(undefined1 *)(param_1 + 0x1a) = uVar4;
  puVar5 = 
  PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj33EE_02cb7cb0
  ;
  uVar3 = *(undefined4 *)(param_2 + 0xe0);
  plVar9 = param_1 + 0x1d;
  *plVar9 = 0;
  *(undefined4 *)(param_1 + 0x1c) = uVar3;
  param_1[0x18] = (long)(puVar5 + 0x10);
  param_1[0x1e] = 0;
  param_1[0x1f] = 0;
  if ((*(byte *)(param_2 + 0xe8) & 1) == 0) {
    param_1[0x1f] = *(long *)(param_2 + 0xf8);
    lVar8 = *(long *)(param_2 + 0xe8);
    param_1[0x1e] = *(long *)(param_2 + 0xf0);
    *plVar9 = lVar8;
  }
  else {
    uVar1 = *(ulong *)(param_2 + 0xf0);
    uVar2 = *(undefined8 *)(param_2 + 0xf8);
    if (uVar1 < 0x17) {
      lVar8 = (long)param_1 + 0xe9;
      *(char *)plVar9 = (char)(uVar1 << 1);
      if (uVar1 != 0) goto code_r0x017fd858;
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
      param_1[0x1e] = uVar1;
      param_1[0x1f] = lVar8;
      param_1[0x1d] = uVar10 | 1;
code_r0x017fd858:
      memcpy(lVar8,uVar2,uVar1);
    }
    *(undefined1 *)(lVar8 + uVar1) = 0;
  }
  param_1[0x20] = (long)(puVar7 + 0x10);
  lVar8 = *(long *)(param_2 + 0x108);
  param_1[0x20] = (long)(PTR__ZTV22CParameterPropertyBaseILj34EE_02cc0de8 + 0x10);
  param_1[0x21] = lVar8;
  uVar4 = *(undefined1 *)(param_2 + 0x110);
  param_1[0x23] = (long)(puVar6 + 0x10);
  puVar5 = 
  PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj34EE_02cb8320
  ;
  *(undefined1 *)(param_1 + 0x22) = uVar4;
  uVar3 = *(undefined4 *)(param_2 + 0x120);
  param_1[0x26] = 0;
  param_1[0x27] = 0;
  param_1[0x20] = (long)(puVar5 + 0x10);
  *(undefined4 *)(param_1 + 0x24) = uVar3;
  param_1[0x25] = 0;
  if ((*(byte *)(param_2 + 0x128) & 1) == 0) {
    param_1[0x27] = *(long *)(param_2 + 0x138);
    lVar8 = *(long *)(param_2 + 0x128);
    param_1[0x26] = *(long *)(param_2 + 0x130);
    param_1[0x25] = lVar8;
    return;
  }
  uVar1 = *(ulong *)(param_2 + 0x130);
  uVar2 = *(undefined8 *)(param_2 + 0x138);
  if (uVar1 < 0x17) {
    lVar8 = (long)param_1 + 0x129;
    *(char *)(param_1 + 0x25) = (char)(uVar1 << 1);
    if (uVar1 == 0) goto code_r0x017fd96c;
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
    param_1[0x26] = uVar1;
    param_1[0x27] = lVar8;
    param_1[0x25] = uVar10 | 1;
  }
  memcpy(lVar8,uVar2,uVar1);
code_r0x017fd96c:
  *(undefined1 *)(lVar8 + uVar1) = 0;
  return;
}

// ==== std::__ndk1::__hash_table<std::__ndk1::__hash_value_type<unsigned int, StringDBEelement>, std::__ndk1::__unordered_map_hasher<unsigned int, std::__ndk1::__hash_value_type<unsigned int, StringDBEelement>, std::__ndk1::hash<unsigned int>, true>, std::__ndk1::__unordered_map_equal<unsigned int, std::__ndk1::__hash_value_type<unsigned int, StringDBEelement>, std::__ndk1::equal_to<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__hash_value_type<unsigned int, StringDBEelement>, Framework::CSTLUnorderedMapAllocatorInf> >::__rehash(unsigned long)
// vaddr 0x16fd988 | ghidra 0x17fd988 | size 524 | symbol _ZNSt6__ndk112__hash_tableINS_17__hash_value_typeIj16StringDBEelementEENS_22__unordered_map_hasherIjS3_NS_4hashIjEELb1EEENS_21__unordered_map_equalIjS3_NS_8equal_toIjEELb1EEEN9Framework13CSTLAllocatorIS3_NSC_28CSTLUnorderedMapAllocatorInfEEEE8__rehashEm | lib libSOA-3.7.0.so | 2026-10-08
void _ZNSt6__ndk112__hash_tableINS_17__hash_value_typeIj16StringDBEelementEENS_22__unordered_map_hasherIjS3_NS_4hashIjEELb1EEENS_21__unordered_map_equalIjS3_NS_8equal_toIjEELb1EEEN9Framework13CSTLAllocatorIS3_NSC_28CSTLUnorderedMapAllocatorInfEEEE8__rehashEm
               (long *param_1,ulong param_2)

{
  long lVar1;
  long lVar2;
  ulong uVar3;
  ulong uVar4;
  long *plVar5;
  long *plVar6;
  ulong uVar7;
  long *plVar8;
  long *plVar9;
  
  if (param_2 == 0) {
    lVar1 = *param_1;
    *param_1 = 0;
    if (lVar1 != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)();
    }
    param_1[1] = 0;
  }
  else {
    lVar1 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(param_2 << 3,&UNK_027dc2d5/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_UnorderedMap.h"*/,0x1c);
    if (lVar1 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    }
    lVar2 = *param_1;
    *param_1 = lVar1;
    if (lVar2 != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)();
    }
    uVar3 = 0;
    param_1[1] = param_2;
    do {
      *(undefined8 *)(*param_1 + uVar3 * 8) = 0;
      uVar3 = uVar3 + 1;
    } while (param_2 != uVar3);
    plVar5 = (long *)param_1[2];
    if (plVar5 != (long *)0x0) {
      uVar3 = plVar5[1];
      uVar4 = param_2 - 1;
      if ((uVar4 & param_2) == 0) {
        uVar3 = uVar3 & uVar4;
      }
      else {
        uVar7 = 0;
        if (param_2 != 0) {
          uVar7 = uVar3 / param_2;
        }
        uVar3 = uVar3 - uVar7 * param_2;
      }
      *(long **)(*param_1 + uVar3 * 8) = param_1 + 2;
      plVar6 = (long *)*plVar5;
joined_r0x017fda4c:
      if (plVar6 != (long *)0x0) {
        if ((uVar4 & param_2) == 0) {
          do {
            uVar7 = plVar6[1] & uVar4;
            if (uVar7 == uVar3) {
              plVar8 = (long *)*plVar6;
              plVar5 = plVar6;
            }
            else {
              plVar8 = (long *)(*param_1 + uVar7 * 8);
              plVar9 = plVar6;
              if (*plVar8 == 0) goto code_r0x017fdb70;
              do {
                plVar8 = plVar9;
                plVar9 = (long *)*plVar8;
                if (plVar9 == (long *)0x0) break;
              } while ((int)plVar6[2] == (int)plVar9[2]);
              *plVar5 = (long)plVar9;
              *plVar8 = **(long **)(*param_1 + uVar7 * 8);
              **(undefined8 **)(*param_1 + uVar7 * 8) = plVar6;
              plVar8 = (long *)*plVar5;
            }
            plVar6 = plVar8;
            if (plVar6 == (long *)0x0) {
              return;
            }
          } while( true );
        }
        do {
          uVar7 = 0;
          if (param_2 != 0) {
            uVar7 = (ulong)plVar6[1] / param_2;
          }
          uVar7 = plVar6[1] - uVar7 * param_2;
          if (uVar7 == uVar3) {
            plVar8 = (long *)*plVar6;
            plVar5 = plVar6;
          }
          else {
            plVar8 = (long *)(*param_1 + uVar7 * 8);
            plVar9 = plVar6;
            if (*plVar8 == 0) goto code_r0x017fdb70;
            do {
              plVar8 = plVar9;
              plVar9 = (long *)*plVar8;
              if (plVar9 == (long *)0x0) break;
            } while ((int)plVar6[2] == (int)plVar9[2]);
            *plVar5 = (long)plVar9;
            *plVar8 = **(long **)(*param_1 + uVar7 * 8);
            **(undefined8 **)(*param_1 + uVar7 * 8) = plVar6;
            plVar8 = (long *)*plVar5;
          }
          plVar6 = plVar8;
          if (plVar6 == (long *)0x0) {
            return;
          }
        } while( true );
      }
    }
  }
  return;
code_r0x017fdb70:
  *plVar8 = (long)plVar5;
  plVar5 = plVar6;
  plVar6 = (long *)*plVar6;
  uVar3 = uVar7;
  goto joined_r0x017fda4c;
}

// ==== std::__ndk1::__shared_ptr_emplace<StringDBEelement, ParameterAllocator<StringDBEelement> >::~__shared_ptr_emplace()
// vaddr 0x16fdb94 | ghidra 0x17fdb94 | size 40 | symbol _ZNSt6__ndk120__shared_ptr_emplaceI16StringDBEelement18ParameterAllocatorIS1_EED2Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZNSt6__ndk120__shared_ptr_emplaceI16StringDBEelement18ParameterAllocatorIS1_EED2Ev
               (long *param_1)

{
  *param_1 = (long)(
                   PTR__ZTVNSt6__ndk120__shared_ptr_emplaceI16StringDBEelement18ParameterAllocatorIS1_EEE_02cc2d78
                   + 0x10);
  StringDBEelement::~StringDBEelement()(param_1 + 3);
  (*(code *)PTR__ZNSt6__ndk119__shared_weak_countD2Ev_02cb1488)(param_1);
  return;
}

// ==== std::__ndk1::__shared_ptr_emplace<StringDBEelement, ParameterAllocator<StringDBEelement> >::~__shared_ptr_emplace()
// vaddr 0x16fdbbc | ghidra 0x17fdbbc | size 48 | symbol _ZNSt6__ndk120__shared_ptr_emplaceI16StringDBEelement18ParameterAllocatorIS1_EED0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZNSt6__ndk120__shared_ptr_emplaceI16StringDBEelement18ParameterAllocatorIS1_EED0Ev
               (long *param_1)

{
  *param_1 = (long)(
                   PTR__ZTVNSt6__ndk120__shared_ptr_emplaceI16StringDBEelement18ParameterAllocatorIS1_EEE_02cc2d78
                   + 0x10);
  StringDBEelement::~StringDBEelement()(param_1 + 3);
  std::__ndk1::__shared_weak_count::~__shared_weak_count()(param_1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== std::__ndk1::__shared_ptr_emplace<StringDBEelement, ParameterAllocator<StringDBEelement> >::__on_zero_shared()
// vaddr 0x16fdbec | ghidra 0x17fdbec | size 12 | symbol _ZNSt6__ndk120__shared_ptr_emplaceI16StringDBEelement18ParameterAllocatorIS1_EE16__on_zero_sharedEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZNSt6__ndk120__shared_ptr_emplaceI16StringDBEelement18ParameterAllocatorIS1_EE16__on_zero_sharedEv
               (long param_1)

{
                    /* WARNING: Could not recover jumptable at 0x017fdbf4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(long *)(param_1 + 0x18) + 0x10))();
  return;
}

// ==== std::__ndk1::__shared_ptr_emplace<StringDBEelement, ParameterAllocator<StringDBEelement> >::__on_zero_shared_weak()
// vaddr 0x16fdbf8 | ghidra 0x17fdbf8 | size 4 | symbol _ZNSt6__ndk120__shared_ptr_emplaceI16StringDBEelement18ParameterAllocatorIS1_EE21__on_zero_shared_weakEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZNSt6__ndk120__shared_ptr_emplaceI16StringDBEelement18ParameterAllocatorIS1_EE21__on_zero_shared_weakEv
               (void)

{
  (*(code *)PTR__ZdlPv_02ca4758)();
  return;
}

// ==== std::__ndk1::__hash_table<std::__ndk1::__hash_value_type<unsigned int, std::__ndk1::shared_ptr<StringDBEelement> >, std::__ndk1::__unordered_map_hasher<unsigned int, std::__ndk1::__hash_value_type<unsigned int, std::__ndk1::shared_ptr<StringDBEelement> >, std::__ndk1::hash<unsigned int>, true>, std::__ndk1::__unordered_map_equal<unsigned int, std::__ndk1::__hash_value_type<unsigned int, std::__ndk1::shared_ptr<StringDBEelement> >, std::__ndk1::equal_to<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__hash_value_type<unsigned int, std::__ndk1::shared_ptr<StringDBEelement> >, Framework::CSTLUnorderedMapAllocatorInf> >::rehash(unsigned long)
// vaddr 0x16fdbfc | ghidra 0x17fdbfc | size 208 | symbol _ZNSt6__ndk112__hash_tableINS_17__hash_value_typeIjNS_10shared_ptrI16StringDBEelementEEEENS_22__unordered_map_hasherIjS5_NS_4hashIjEELb1EEENS_21__unordered_map_equalIjS5_NS_8equal_toIjEELb1EEEN9Framework13CSTLAllocatorIS5_NSE_28CSTLUnorderedMapAllocatorInfEEEE6rehashEm | lib libSOA-3.7.0.so | 2026-10-08
void _ZNSt6__ndk112__hash_tableINS_17__hash_value_typeIjNS_10shared_ptrI16StringDBEelementEEEENS_22__unordered_map_hasherIjS5_NS_4hashIjEELb1EEENS_21__unordered_map_equalIjS5_NS_8equal_toIjEELb1EEEN9Framework13CSTLAllocatorIS5_NSE_28CSTLUnorderedMapAllocatorInfEEEE6rehashEm
               (long param_1,ulong param_2)

{
  ulong uVar1;
  ulong uVar2;
  
  if (param_2 - 1 == 0) {
    param_2 = 2;
  }
  else if ((param_2 - 1 & param_2) != 0) {
    param_2 = std::__ndk1::__next_prime(unsigned long)(param_2);
  }
  uVar2 = *(ulong *)(param_1 + 8);
  uVar1 = param_2;
  if (uVar2 < param_2) {
code_r0x011f7670:
    (*(code *)
      PTR__ZNSt6__ndk112__hash_tableINS_17__hash_value_typeIjNS_10shared_ptrI16StringDBEelementEEEENS_22__unordered_map_hasherIjS5_NS_4hashIjEELb1EEENS_21__unordered_map_equalIjS5_NS_8equal_toIjEELb1EEEN9Framework13CSTLAllocatorIS5_NSE_28CSTLUnorderedMapAllocatorInfEEEE8__rehashEm_02cb3b28
    )(param_1,uVar1);
    return;
  }
  if (param_2 < uVar2) {
    if (uVar2 < 3 || (uVar2 - 1 & uVar2) != 0) {
      uVar1 = std::__ndk1::__next_prime(unsigned long)();
    }
    else {
      uVar1 = 1L << (0x40U - LZCOUNT((long)((float)*(ulong *)(param_1 + 0x18) /
                                           *(float *)(param_1 + 0x20)) + -1) & 0x3f);
    }
    if (uVar1 <= param_2) {
      uVar1 = param_2;
    }
    if (uVar1 < uVar2) goto code_r0x011f7670;
  }
  return;
}

// ==== std::__ndk1::__hash_table<std::__ndk1::__hash_value_type<unsigned int, std::__ndk1::shared_ptr<StringDBEelement> >, std::__ndk1::__unordered_map_hasher<unsigned int, std::__ndk1::__hash_value_type<unsigned int, std::__ndk1::shared_ptr<StringDBEelement> >, std::__ndk1::hash<unsigned int>, true>, std::__ndk1::__unordered_map_equal<unsigned int, std::__ndk1::__hash_value_type<unsigned int, std::__ndk1::shared_ptr<StringDBEelement> >, std::__ndk1::equal_to<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__hash_value_type<unsigned int, std::__ndk1::shared_ptr<StringDBEelement> >, Framework::CSTLUnorderedMapAllocatorInf> >::__rehash(unsigned long)
// vaddr 0x16fdccc | ghidra 0x17fdccc | size 524 | symbol _ZNSt6__ndk112__hash_tableINS_17__hash_value_typeIjNS_10shared_ptrI16StringDBEelementEEEENS_22__unordered_map_hasherIjS5_NS_4hashIjEELb1EEENS_21__unordered_map_equalIjS5_NS_8equal_toIjEELb1EEEN9Framework13CSTLAllocatorIS5_NSE_28CSTLUnorderedMapAllocatorInfEEEE8__rehashEm | lib libSOA-3.7.0.so | 2026-10-08
void _ZNSt6__ndk112__hash_tableINS_17__hash_value_typeIjNS_10shared_ptrI16StringDBEelementEEEENS_22__unordered_map_hasherIjS5_NS_4hashIjEELb1EEENS_21__unordered_map_equalIjS5_NS_8equal_toIjEELb1EEEN9Framework13CSTLAllocatorIS5_NSE_28CSTLUnorderedMapAllocatorInfEEEE8__rehashEm
               (long *param_1,ulong param_2)

{
  long lVar1;
  long lVar2;
  ulong uVar3;
  ulong uVar4;
  long *plVar5;
  long *plVar6;
  ulong uVar7;
  long *plVar8;
  long *plVar9;
  
  if (param_2 == 0) {
    lVar1 = *param_1;
    *param_1 = 0;
    if (lVar1 != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)();
    }
    param_1[1] = 0;
  }
  else {
    lVar1 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(param_2 << 3,&UNK_027dc2d5/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_UnorderedMap.h"*/,0x1c);
    if (lVar1 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    }
    lVar2 = *param_1;
    *param_1 = lVar1;
    if (lVar2 != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)();
    }
    uVar3 = 0;
    param_1[1] = param_2;
    do {
      *(undefined8 *)(*param_1 + uVar3 * 8) = 0;
      uVar3 = uVar3 + 1;
    } while (param_2 != uVar3);
    plVar5 = (long *)param_1[2];
    if (plVar5 != (long *)0x0) {
      uVar3 = plVar5[1];
      uVar4 = param_2 - 1;
      if ((uVar4 & param_2) == 0) {
        uVar3 = uVar3 & uVar4;
      }
      else {
        uVar7 = 0;
        if (param_2 != 0) {
          uVar7 = uVar3 / param_2;
        }
        uVar3 = uVar3 - uVar7 * param_2;
      }
      *(long **)(*param_1 + uVar3 * 8) = param_1 + 2;
      plVar6 = (long *)*plVar5;
joined_r0x017fdd90:
      if (plVar6 != (long *)0x0) {
        if ((uVar4 & param_2) == 0) {
          do {
            uVar7 = plVar6[1] & uVar4;
            if (uVar7 == uVar3) {
              plVar8 = (long *)*plVar6;
              plVar5 = plVar6;
            }
            else {
              plVar8 = (long *)(*param_1 + uVar7 * 8);
              plVar9 = plVar6;
              if (*plVar8 == 0) goto code_r0x017fdeb4;
              do {
                plVar8 = plVar9;
                plVar9 = (long *)*plVar8;
                if (plVar9 == (long *)0x0) break;
              } while ((int)plVar6[2] == (int)plVar9[2]);
              *plVar5 = (long)plVar9;
              *plVar8 = **(long **)(*param_1 + uVar7 * 8);
              **(undefined8 **)(*param_1 + uVar7 * 8) = plVar6;
              plVar8 = (long *)*plVar5;
            }
            plVar6 = plVar8;
            if (plVar6 == (long *)0x0) {
              return;
            }
          } while( true );
        }
        do {
          uVar7 = 0;
          if (param_2 != 0) {
            uVar7 = (ulong)plVar6[1] / param_2;
          }
          uVar7 = plVar6[1] - uVar7 * param_2;
          if (uVar7 == uVar3) {
            plVar8 = (long *)*plVar6;
            plVar5 = plVar6;
          }
          else {
            plVar8 = (long *)(*param_1 + uVar7 * 8);
            plVar9 = plVar6;
            if (*plVar8 == 0) goto code_r0x017fdeb4;
            do {
              plVar8 = plVar9;
              plVar9 = (long *)*plVar8;
              if (plVar9 == (long *)0x0) break;
            } while ((int)plVar6[2] == (int)plVar9[2]);
            *plVar5 = (long)plVar9;
            *plVar8 = **(long **)(*param_1 + uVar7 * 8);
            **(undefined8 **)(*param_1 + uVar7 * 8) = plVar6;
            plVar8 = (long *)*plVar5;
          }
          plVar6 = plVar8;
          if (plVar6 == (long *)0x0) {
            return;
          }
        } while( true );
      }
    }
  }
  return;
code_r0x017fdeb4:
  *plVar8 = (long)plVar5;
  plVar5 = plVar6;
  plVar6 = (long *)*plVar6;
  uVar3 = uVar7;
  goto joined_r0x017fdd90;
}

// ==== CMasterParameterBaseSqlite_Simple<StringDBEelement>::~CMasterParameterBaseSqlite_Simple()
// vaddr 0x16fded8 | ghidra 0x17fded8 | size 256 | symbol _ZN33CMasterParameterBaseSqlite_SimpleI16StringDBEelementED2Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN33CMasterParameterBaseSqlite_SimpleI16StringDBEelementED2Ev(long *param_1)

{
  undefined *puVar1;
  long *plVar2;
  long lVar3;
  
  puVar1 = PTR__ZTV33CMasterParameterBaseSqlite_SimpleI16StringDBEelementE_02cc0880 + 0x70;
  *param_1 = (long)(PTR__ZTV33CMasterParameterBaseSqlite_SimpleI16StringDBEelementE_02cc0880 + 0x10)
  ;
  param_1[2] = (long)puVar1;
  plVar2 = (long *)param_1[0x10];
  while (plVar2 != (long *)0x0) {
    lVar3 = *plVar2;
    if (plVar2[4] != 0) {
      std::__ndk1::__shared_weak_count::__release_shared()();
    }
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar2);
    plVar2 = (long *)lVar3;
  }
  lVar3 = param_1[0xe];
  param_1[0xe] = 0;
  if (lVar3 != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)();
  }
  plVar2 = (long *)param_1[10];
  while (plVar2 != (long *)0x0) {
    lVar3 = *plVar2;
    if (plVar2[4] != 0) {
      std::__ndk1::__shared_weak_count::__release_shared()();
    }
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar2);
    plVar2 = (long *)lVar3;
  }
  lVar3 = param_1[8];
  param_1[8] = 0;
  if (lVar3 != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)();
  }
  plVar2 = (long *)param_1[5];
  while (plVar2 != (long *)0x0) {
    lVar3 = *plVar2;
    if (plVar2[4] != 0) {
      std::__ndk1::__shared_weak_count::__release_shared()();
    }
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar2);
    plVar2 = (long *)lVar3;
  }
  lVar3 = param_1[3];
  param_1[3] = 0;
  if (lVar3 != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)();
  }
  *param_1 = (long)(PTR__ZTV26CMasterParameterBaseSqlite_02cc48f0 + 0x10);
  if ((long *)param_1[1] != (long *)0x0) {
    (**(code **)(*(long *)param_1[1] + 8))();
    param_1[1] = 0;
  }
  return;
}

// ==== CMasterParameterBaseSqlite_Simple<StringDBEelement>::~CMasterParameterBaseSqlite_Simple()
// vaddr 0x16fdfd8 | ghidra 0x17fdfd8 | size 4 | symbol _ZN33CMasterParameterBaseSqlite_SimpleI16StringDBEelementED0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN33CMasterParameterBaseSqlite_SimpleI16StringDBEelementED0Ev(void)

{
  code *pcVar1;
  
                    /* WARNING: Does not return */
  pcVar1 = (code *)SoftwareBreakpoint(1,0x17fdfdc);
  (*pcVar1)();
}

// ==== CMasterParameterBaseSqlite_Simple<StringDBEelement>::ReleaseParameter(char const*)
// vaddr 0x16fdfdc | ghidra 0x17fdfdc | size 600 | symbol _ZN33CMasterParameterBaseSqlite_SimpleI16StringDBEelementE16ReleaseParameterEPKc | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN33CMasterParameterBaseSqlite_SimpleI16StringDBEelementE16ReleaseParameterEPKc
          (long param_1,undefined8 param_2)

{
  ulong uVar1;
  long *plVar2;
  uint uVar3;
  int iVar4;
  undefined8 uVar5;
  ulong uVar6;
  long lVar7;
  ulong uVar8;
  ulong uVar9;
  ulong uVar10;
  long *plVar11;
  ulong uVar12;
  long *plVar13;
  long lVar14;
  undefined1 auStack_30 [16];
  
  Framework::CHash32::CHash32(char const*)(auStack_30);
  uVar3 = Framework::CHash32::operator unsigned int() const(auStack_30);
  uVar8 = *(ulong *)(param_1 + 0x20);
  if (uVar8 != 0) {
    uVar9 = uVar8 - 1;
    uVar6 = (ulong)uVar3;
    if ((uVar9 & uVar8) == 0) {
      uVar6 = uVar9 & uVar6;
    }
    else {
      uVar10 = 0;
      if (uVar8 != 0) {
        uVar10 = uVar6 / uVar8;
      }
      uVar6 = uVar6 - uVar10 * uVar8;
    }
    plVar13 = *(long **)(*(long *)(param_1 + 0x18) + uVar6 * 8);
    if (plVar13 != (long *)0x0) {
      if ((uVar9 & uVar8) == 0) {
        do {
          plVar13 = (long *)*plVar13;
          if ((plVar13 == (long *)0x0) || ((plVar13[1] & uVar9) != uVar6)) goto code_r0x017fe0b4;
        } while (*(uint *)(plVar13 + 2) != uVar3);
      }
      else {
        do {
          plVar13 = (long *)*plVar13;
          if (plVar13 == (long *)0x0) goto code_r0x017fe0b4;
          uVar9 = 0;
          if (uVar8 != 0) {
            uVar9 = (ulong)plVar13[1] / uVar8;
          }
          if (plVar13[1] - uVar9 * uVar8 != uVar6) goto code_r0x017fe0b4;
        } while (*(uint *)(plVar13 + 2) != uVar3);
      }
      Framework::CHash32::~CHash32()(auStack_30);
      if (plVar13 != (long *)0x0) {
        uVar6 = *(ulong *)(param_1 + 0x20);
        uVar8 = plVar13[1];
        uVar9 = uVar6 - 1;
        uVar10 = uVar9 & uVar6;
        if (uVar10 == 0) {
          uVar8 = uVar9 & uVar8;
        }
        else {
          uVar12 = 0;
          if (uVar6 != 0) {
            uVar12 = uVar8 / uVar6;
          }
          uVar8 = uVar8 - uVar12 * uVar6;
        }
        plVar2 = *(long **)(*(long *)(param_1 + 0x18) + uVar8 * 8);
        do {
          plVar11 = plVar2;
          plVar2 = (long *)*plVar11;
        } while ((long *)*plVar11 != plVar13);
        if (plVar11 != (long *)(param_1 + 0x28)) {
          uVar12 = plVar11[1];
          if (uVar10 == 0) {
            uVar12 = uVar12 & uVar9;
          }
          else {
            uVar1 = 0;
            if (uVar6 != 0) {
              uVar1 = uVar12 / uVar6;
            }
            uVar12 = uVar12 - uVar1 * uVar6;
          }
          if (uVar12 == uVar8) goto code_r0x017fe1bc;
        }
        if (*plVar13 != 0) {
          uVar12 = *(ulong *)(*plVar13 + 8);
          if (uVar10 == 0) {
            uVar12 = uVar12 & uVar9;
          }
          else {
            uVar1 = 0;
            if (uVar6 != 0) {
              uVar1 = uVar12 / uVar6;
            }
            uVar12 = uVar12 - uVar1 * uVar6;
          }
          if (uVar12 == uVar8) goto code_r0x017fe1bc;
        }
        *(undefined8 *)(*(long *)(param_1 + 0x18) + uVar8 * 8) = 0;
code_r0x017fe1bc:
        if (*plVar13 != 0) {
          uVar12 = *(ulong *)(*plVar13 + 8);
          if (uVar10 == 0) {
            uVar12 = uVar12 & uVar9;
          }
          else {
            uVar9 = 0;
            if (uVar6 != 0) {
              uVar9 = uVar12 / uVar6;
            }
            uVar12 = uVar12 - uVar9 * uVar6;
          }
          if (uVar12 != uVar8) {
            *(long **)(*(long *)(param_1 + 0x18) + uVar12 * 8) = plVar11;
          }
        }
        *plVar11 = *plVar13;
        *plVar13 = 0;
        *(long *)(param_1 + 0x30) = *(long *)(param_1 + 0x30) + -1;
        if (plVar13[4] != 0) {
          std::__ndk1::__shared_weak_count::__release_shared()();
        }
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar13);
        return 1;
      }
      goto code_r0x017fe0bc;
    }
  }
code_r0x017fe0b4:
  Framework::CHash32::~CHash32()(auStack_30);
code_r0x017fe0bc:
  uVar5 = (**(code **)(*(long *)(param_1 + 0x10) + 0x18))();
  iVar4 = strcmp(param_2,uVar5);
  if ((iVar4 == 0) && (*(long *)(param_1 + 0x30) != 0)) {
    plVar13 = (long *)*(long *)(param_1 + 0x28);
    while (plVar13 != (long *)0x0) {
      lVar14 = *plVar13;
      if (plVar13[4] != 0) {
        std::__ndk1::__shared_weak_count::__release_shared()();
      }
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar13);
      plVar13 = (long *)lVar14;
    }
    lVar14 = *(long *)(param_1 + 0x20);
    *(undefined8 *)(param_1 + 0x28) = 0;
    if (lVar14 != 0) {
      lVar7 = 0;
      do {
        *(undefined8 *)(*(long *)(param_1 + 0x18) + lVar7 * 8) = 0;
        lVar7 = lVar7 + 1;
      } while (lVar14 != lVar7);
    }
    *(undefined8 *)(param_1 + 0x30) = 0;
  }
  return 1;
}

// ==== non-virtual thunk to CMasterParameterBaseSqlite_Simple<StringDBEelement>::~CMasterParameterBaseSqlite_Simple()
// vaddr 0x16fe234 | ghidra 0x17fe234 | size 8 | symbol _ZThn16_N33CMasterParameterBaseSqlite_SimpleI16StringDBEelementED1Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZThn16_N33CMasterParameterBaseSqlite_SimpleI16StringDBEelementED1Ev(long param_1)

{
  (*(code *)PTR__ZN33CMasterParameterBaseSqlite_SimpleI16StringDBEelementED2Ev_02ca1de8)
            (param_1 + -0x10);
  return;
}

// ==== non-virtual thunk to CMasterParameterBaseSqlite_Simple<StringDBEelement>::~CMasterParameterBaseSqlite_Simple()
// vaddr 0x16fe23c | ghidra 0x17fe23c | size 4 | symbol _ZThn16_N33CMasterParameterBaseSqlite_SimpleI16StringDBEelementED0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZThn16_N33CMasterParameterBaseSqlite_SimpleI16StringDBEelementED0Ev(void)

{
  code *pcVar1;
  
                    /* WARNING: Does not return */
  pcVar1 = (code *)SoftwareBreakpoint(1,0x17fe240);
  (*pcVar1)();
}

// ==== non-virtual thunk to CMasterParameterBaseSqlite_Simple<StringDBEelement>::ReleaseParameter(char const*)
// vaddr 0x16fe240 | ghidra 0x17fe240 | size 8 | symbol _ZThn16_N33CMasterParameterBaseSqlite_SimpleI16StringDBEelementE16ReleaseParameterEPKc | lib libSOA-3.7.0.so | 2026-10-08
void _ZThn16_N33CMasterParameterBaseSqlite_SimpleI16StringDBEelementE16ReleaseParameterEPKc
               (long param_1)

{
  (*(code *)
    PTR__ZN33CMasterParameterBaseSqlite_SimpleI16StringDBEelementE16ReleaseParameterEPKc_02c95298)
            (param_1 + -0x10);
  return;
}

// ==== std::__ndk1::shared_ptr<StringDBEelement> std::__ndk1::shared_ptr<StringDBEelement>::allocate_shared<BAS_STLAllocator<StringDBEelement>>(BAS_STLAllocator<StringDBEelement> const&)
// vaddr 0x177e3b4 | ghidra 0x187e3b4 | size 344 | symbol _ZNSt6__ndk110shared_ptrI16StringDBEelementE15allocate_sharedI16BAS_STLAllocatorIS1_EJEEES2_RKT_DpOT0_ | lib libSOA-3.7.0.so | 2026-10-08
void _ZNSt6__ndk110shared_ptrI16StringDBEelementE15allocate_sharedI16BAS_STLAllocatorIS1_EJEEES2_RKT_DpOT0_
               (long *param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  undefined8 uVar3;
  long *plVar4;
  
  uVar3 = Aska::Global::GetAvailableMemoryManager()();
  plVar4 = (long *)Aska::MemoryManager::Malloc(unsigned long)(uVar3,0x158);
  plVar4[2] = 0;
  *plVar4 = (long)(
                  PTR__ZTVNSt6__ndk120__shared_ptr_emplaceI16StringDBEelement16BAS_STLAllocatorIS1_EEE_02cba2f8
                  + 0x10);
  plVar4[1] = 0;
  CParameterElementBase::CParameterElementBase()(plVar4 + 3);
  puVar2 = PTR__ZTV22CParameterPropertyBaseILj29EE_02cc1a28;
  puVar1 = PTR__ZTV16StringDBEelement_02cbb4f0;
  *(undefined1 *)(plVar4 + 7) = 0;
  plVar4[3] = (long)(puVar1 + 0x10);
  plVar4[5] = (long)(puVar2 + 0x10);
  plVar4[6] = 0;
  Framework::CHash32::CHash32()(plVar4 + 8);
  puVar2 = PTR__ZTV22CParameterPropertyBaseILj31EE_02cc17e0;
  puVar1 = PTR__ZTV23CParameterPropertyValueIjLj29E18CPropertyConverterE_02cb7988;
  *(undefined1 *)(plVar4 + 0xd) = 0;
  plVar4[5] = (long)(puVar1 + 0x10);
  plVar4[0xb] = (long)(puVar2 + 0x10);
  plVar4[0xc] = 0;
  Framework::CHash32::CHash32()(plVar4 + 0xe);
  puVar1 = 
  PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj31EE_02cba990
  ;
  plVar4[0x10] = 0;
  plVar4[0x11] = 0;
  plVar4[0x14] = 0;
  puVar2 = PTR__ZTV22CParameterPropertyBaseILj32EE_02cc0fa8;
  *(undefined1 *)(plVar4 + 0x15) = 0;
  plVar4[0xb] = (long)(puVar1 + 0x10);
  plVar4[0x12] = 0;
  plVar4[0x13] = (long)(puVar2 + 0x10);
  Framework::CHash32::CHash32()(plVar4 + 0x16);
  puVar2 = 
  PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj32EE_02cc31e8
  ;
  plVar4[0x18] = 0;
  plVar4[0x19] = 0;
  plVar4[0x1c] = 0;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj33EE_02cb96b8;
  *(undefined1 *)(plVar4 + 0x1d) = 0;
  plVar4[0x13] = (long)(puVar2 + 0x10);
  plVar4[0x1a] = 0;
  plVar4[0x1b] = (long)(puVar1 + 0x10);
  Framework::CHash32::CHash32()(plVar4 + 0x1e);
  puVar1 = 
  PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj33EE_02cb7cb0
  ;
  plVar4[0x20] = 0;
  plVar4[0x21] = 0;
  plVar4[0x24] = 0;
  puVar2 = PTR__ZTV22CParameterPropertyBaseILj34EE_02cc0de8;
  *(undefined1 *)(plVar4 + 0x25) = 0;
  plVar4[0x1b] = (long)(puVar1 + 0x10);
  plVar4[0x22] = 0;
  plVar4[0x23] = (long)(puVar2 + 0x10);
  Framework::CHash32::CHash32()(plVar4 + 0x26);
  puVar1 = 
  PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj34EE_02cb8320
  ;
  plVar4[0x29] = 0;
  plVar4[0x2a] = 0;
  plVar4[0x28] = 0;
  plVar4[0x23] = (long)(puVar1 + 0x10);
  *param_1 = (long)(plVar4 + 3);
  param_1[1] = (long)plVar4;
  return;
}

// ==== std::__ndk1::__shared_ptr_emplace<StringDBEelement, BAS_STLAllocator<StringDBEelement> >::~__shared_ptr_emplace()
// vaddr 0x177e50c | ghidra 0x187e50c | size 40 | symbol _ZNSt6__ndk120__shared_ptr_emplaceI16StringDBEelement16BAS_STLAllocatorIS1_EED2Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZNSt6__ndk120__shared_ptr_emplaceI16StringDBEelement16BAS_STLAllocatorIS1_EED2Ev
               (long *param_1)

{
  *param_1 = (long)(
                   PTR__ZTVNSt6__ndk120__shared_ptr_emplaceI16StringDBEelement16BAS_STLAllocatorIS1_EEE_02cba2f8
                   + 0x10);
  StringDBEelement::~StringDBEelement()(param_1 + 3);
  (*(code *)PTR__ZNSt6__ndk119__shared_weak_countD2Ev_02cb1488)(param_1);
  return;
}

// ==== std::__ndk1::__shared_ptr_emplace<StringDBEelement, BAS_STLAllocator<StringDBEelement> >::~__shared_ptr_emplace()
// vaddr 0x177e534 | ghidra 0x187e534 | size 48 | symbol _ZNSt6__ndk120__shared_ptr_emplaceI16StringDBEelement16BAS_STLAllocatorIS1_EED0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZNSt6__ndk120__shared_ptr_emplaceI16StringDBEelement16BAS_STLAllocatorIS1_EED0Ev
               (long *param_1)

{
  *param_1 = (long)(
                   PTR__ZTVNSt6__ndk120__shared_ptr_emplaceI16StringDBEelement16BAS_STLAllocatorIS1_EEE_02cba2f8
                   + 0x10);
  StringDBEelement::~StringDBEelement()(param_1 + 3);
  std::__ndk1::__shared_weak_count::~__shared_weak_count()(param_1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== std::__ndk1::__shared_ptr_emplace<StringDBEelement, BAS_STLAllocator<StringDBEelement> >::__on_zero_shared()
// vaddr 0x177e564 | ghidra 0x187e564 | size 12 | symbol _ZNSt6__ndk120__shared_ptr_emplaceI16StringDBEelement16BAS_STLAllocatorIS1_EE16__on_zero_sharedEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZNSt6__ndk120__shared_ptr_emplaceI16StringDBEelement16BAS_STLAllocatorIS1_EE16__on_zero_sharedEv
               (long param_1)

{
                    /* WARNING: Could not recover jumptable at 0x0187e56c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(long *)(param_1 + 0x18) + 0x10))();
  return;
}

// ==== std::__ndk1::__shared_ptr_emplace<StringDBEelement, BAS_STLAllocator<StringDBEelement> >::__on_zero_shared_weak()
// vaddr 0x177e570 | ghidra 0x187e570 | size 36 | symbol _ZNSt6__ndk120__shared_ptr_emplaceI16StringDBEelement16BAS_STLAllocatorIS1_EE21__on_zero_shared_weakEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZNSt6__ndk120__shared_ptr_emplaceI16StringDBEelement16BAS_STLAllocatorIS1_EE21__on_zero_shared_weakEv
               (long param_1)

{
  undefined8 uVar1;
  
  uVar1 = Aska::Global::GetAvailableMemoryManager()();
  if (param_1 != 0) {
    (*(code *)PTR__ZN4Aska13MemoryManager9LocalFreeEPv_02cb5c60)(uVar1,param_1);
    return;
  }
  return;
}


// FAILED to create function at 0285ec1c typeinfo name for StringDB
// FAILED to create function at 0285ec30 typeinfo name for CMasterParameterBaseSqlite_Simple<StringDBEelement>
// FAILED to create function at 0285ec70 typeinfo name for StringDBEelement
// FAILED to create function at 0285ec90 typeinfo name for std::__ndk1::__shared_ptr_emplace<StringDBEelement, ParameterAllocator<StringDBEelement> >
// FAILED to create function at 02861f80 typeinfo name for std::__ndk1::__shared_ptr_emplace<StringDBEelement, BAS_STLAllocator<StringDBEelement> >
// FAILED to create function at 02b0bc68 StringDB::vtable
// FAILED to create function at 02b0bd20 CMasterParameterBaseSqlite_Simple<StringDBEelement>::typeinfo
// FAILED to create function at 02b0bd60 StringDB::typeinfo
// FAILED to create function at 02b0bd78 StringDBEelement::vtable
// FAILED to create function at 02b0bdb0 StringDBEelement::typeinfo
// FAILED to create function at 02b0bdc8 std::__ndk1::__shared_ptr_emplace<StringDBEelement,ParameterAllocator<StringDBEelement>>::vtable
// FAILED to create function at 02b0be00 std::__ndk1::__shared_ptr_emplace<StringDBEelement,ParameterAllocator<StringDBEelement>>::typeinfo
// FAILED to create function at 02b0be18 CMasterParameterBaseSqlite_Simple<StringDBEelement>::vtable
// FAILED to create function at 02b0c6f8 std::__ndk1::__shared_ptr_emplace<StringDBEelement,BAS_STLAllocator<StringDBEelement>>::vtable
// FAILED to create function at 02b0c730 std::__ndk1::__shared_ptr_emplace<StringDBEelement,BAS_STLAllocator<StringDBEelement>>::typeinfo
