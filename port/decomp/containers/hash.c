// port/decomp/containers/hash.c: Ghidra decompiles for the containers subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileAt.java, tools/resolve_decomp.py
// run      2026-10-04 05:12 UTC: tools/decomp_at.sh '--into' 'containers/hash' '12d84e4' '12d86e8' '12d890c' '18dce3c' '18dd100' '18e424c' '18e7ea4' '18e8440' '18e8644' '18e887c' '18e8884' '18e88bc' '18e929c' '18ea0d0' '18f52c8' '18f5504' '18f5604' '18f57f0' '18f9964' '18fa010' '18fa024' '18fa0bc' '18fa2d4' '1f84c08' '202a1e4' '202ec98' '202f08c' '202f360' '202f554' '202fa58' '202fa98' '202fb68' '202fc10' '202fd20' '202ff64' '2030220' '20303bc' '203053c' '2030624' '2030898' '2030b6c' '2030d08' '2030e88' '2030f70' '2051320' '20513f8' '20514f0' '2051544' '2051678' '2052530' '2052744' '2052798' '21e0178' '21e0330' '21f8944' '21f8bd8' '21f8c18' '21f8dfc' '21f8f7c' '21f9064' '21fa57c' '21fa780' '21fa828' '21fa938' '21fb664' '21fb990' '21fbbf0' '21fbd70' '21fd200' '21fd52c' '21fd7ec' '21fd96c' '227ffe0' '2280224' '2280838' '2280984' '2280bc8' '22d83a4' '22deca8' '22defd4' '22e132c' '22e28c4' '22e29f8' '22e4538' '22e47e0' '22e498c' '22e4b0c' '22e4bf4' '22e71e0' '22ed6fc' '22ed8b8' '22f52a0' '22f5410' '22f5614' '22f5714' '2304554' '232ebd0' '232f160' '2330744'

// ==== Aska::THashMap<unsigned long, bool, Aska::THasher<unsigned long>, Aska::TEqualTo<unsigned long>, Aska::TAllocator<Aska::TPair<unsigned long const, bool> > >::Rehash_(unsigned long)
// vaddr 0x11d84e4 | ghidra 0x12d84e4 | size 516 | symbol _ZN4Aska8THashMapImbNS_7THasherImEENS_8TEqualToImEENS_10TAllocatorINS_5TPairIKmbEEEEE7Rehash_Em | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska8THashMapImbNS_7THasherImEENS_8TEqualToImEENS_10TAllocatorINS_5TPairIKmbEEEEE7Rehash_Em
               (undefined1 *param_1,ulong param_2)

{
  ulong uVar1;
  undefined *puVar2;
  undefined1 *puVar3;
  undefined1 *puVar4;
  undefined8 uVar5;
  char *pcVar6;
  ulong uVar7;
  long lVar8;
  ulong uVar9;
  float fVar10;
  float fVar11;
  undefined *puStack_90;
  float fStack_84;
  undefined4 uStack_80;
  undefined4 uStack_7c;
  undefined1 *puStack_70;
  ulong uStack_68;
  char *pcStack_60;
  char *pcStack_58;
  char *pcStack_50;
  char *pcStack_48;
  char *pcStack_40;
  char *pcStack_38;
  
  puVar2 = 
  PTR__ZTVN4Aska8THashMapImbNS_7THasherImEENS_8TEqualToImEENS_10TAllocatorINS_5TPairIKmbEEEEEE_02cb8478
  ;
  puStack_90 = PTR__ZTVN4Aska8THashMapImbNS_7THasherImEENS_8TEqualToImEENS_10TAllocatorINS_5TPairIKmbEEEEEE_02cb8478
               + 0x10;
  fStack_84 = 0.75;
  uStack_80 = 0;
  uStack_7c = 0;
  if (param_2 < 0xaaaaaaaaaaaaaab) {
    puStack_70 = (undefined1 *)Aska::MemoryManagerAdapter::AlignedMalloc(unsigned long, unsigned long)(param_2 * 0x18,8);
  }
  else {
    puStack_70 = (undefined1 *)0x0;
  }
  if (puStack_70 == (undefined1 *)0x0) {
    param_2 = 0;
  }
  if (param_2 == 0) {
    fVar10 = *(float *)(param_1 + 0xc);
code_r0x012d85fc:
    if (fVar10 <= 0.0) goto code_r0x012d860c;
  }
  else {
    uVar1 = (param_2 * 0x18 - 0x18) / 0x18 + 1;
    puVar3 = puStack_70;
    if ((uVar1 < 2) || (uVar7 = uVar1 & 0x1ffffffffffffffe, uVar7 == 0)) {
code_r0x012d85b4:
      do {
        puVar4 = puVar3 + 0x18;
        *puVar3 = 0;
        puVar3 = puVar4;
      } while (puStack_70 + param_2 * 0x18 != puVar4);
    }
    else {
      puVar3 = puStack_70 + uVar7 * 0x18;
      uVar9 = uVar7;
      puVar4 = puStack_70;
      do {
        *puVar4 = 0;
        puVar4[0x18] = 0;
        uVar9 = uVar9 - 2;
        puVar4 = puVar4 + 0x30;
      } while (uVar9 != 0);
      if (uVar1 != uVar7) goto code_r0x012d85b4;
    }
    fVar10 = *(float *)(param_1 + 0xc);
    if (param_2 == 0) goto code_r0x012d85fc;
    fVar11 = (float)NEON_ucvtf(uStack_80);
    if (fVar10 <= fVar11 / (float)param_2) goto code_r0x012d860c;
  }
  fStack_84 = fVar10;
code_r0x012d860c:
  pcStack_58 = *(char **)(param_1 + 0x20);
  lVar8 = *(long *)(param_1 + 0x28);
  pcStack_60 = pcStack_58 + lVar8 * 0x18;
  pcStack_48 = pcStack_60;
  if ((*(int *)(param_1 + 0x10) != 0) && (pcStack_48 = pcStack_58, lVar8 != 0)) {
    lVar8 = lVar8 * 0x18;
    pcVar6 = pcStack_58;
    do {
      pcStack_48 = pcVar6;
      if (*pcVar6 == '\x01') break;
      lVar8 = lVar8 + -0x18;
      pcVar6 = pcVar6 + 0x18;
      pcStack_48 = pcStack_60;
    } while (lVar8 != 0);
  }
  uStack_68 = param_2;
  pcStack_50 = pcStack_60;
  pcStack_40 = pcStack_58;
  pcStack_38 = pcStack_60;
  void Aska::THashMap<unsigned long, bool, Aska::THasher<unsigned long>, Aska::TEqualTo<unsigned long>, Aska::TAllocator<Aska::TPair<unsigned long const, bool> > >::Insert<Aska::THashMapIterator<Aska::detail::THashMapBucketArray<Aska::detail::THashMapBucket<Aska::TPair<unsigned long const, bool> >, Aska::TAllocator<Aska::detail::THashMapBucket<Aska::TPair<unsigned long const, bool> > > > > >(Aska::THashMapIterator<Aska::detail::THashMapBucketArray<Aska::detail::THashMapBucket<Aska::TPair<unsigned long const, bool> >, Aska::TAllocator<Aska::detail::THashMapBucket<Aska::TPair<unsigned long const, bool> > > > >, Aska::THashMapIterator<Aska::detail::THashMapBucketArray<Aska::detail::THashMapBucket<Aska::TPair<unsigned long const, bool> >, Aska::TAllocator<Aska::detail::THashMapBucket<Aska::TPair<unsigned long const, bool> > > > >)(&puStack_90,&pcStack_48,&pcStack_60);
  if (&puStack_90 != (undefined **)param_1) {
    uVar5 = *(undefined8 *)(param_1 + 0x10);
    *(ulong *)(param_1 + 0x10) = CONCAT44(uStack_7c,uStack_80);
    uStack_80 = (undefined4)uVar5;
    uStack_7c = (undefined4)((ulong)uVar5 >> 0x20);
    puVar3 = *(undefined1 **)(param_1 + 0x20);
    uVar1 = *(ulong *)(param_1 + 0x28);
    *(ulong *)(param_1 + 0x28) = uStack_68;
    *(undefined1 **)(param_1 + 0x20) = puStack_70;
    fVar10 = *(float *)(param_1 + 0xc);
    *(float *)(param_1 + 0xc) = fStack_84;
    fStack_84 = fVar10;
    puStack_70 = puVar3;
    uStack_68 = uVar1;
  }
  puStack_90 = puVar2 + 0x10;
  if (puStack_70 != (undefined1 *)0x0) {
    Aska::MemoryManagerAdapter::AlignedFree(void*)();
  }
  return;
}

// ==== void Aska::THashMap<unsigned long, bool, Aska::THasher<unsigned long>, Aska::TEqualTo<unsigned long>, Aska::TAllocator<Aska::TPair<unsigned long const, bool> > >::Insert<Aska::THashMapIterator<Aska::detail::THashMapBucketArray<Aska::detail::THashMapBucket<Aska::TPair<unsigned long const, bool> >, Aska::TAllocator<Aska::detail::THashMapBucket<Aska::TPair<unsigned long const, bool> > > > > >(Aska::THashMapIterator<Aska::detail::THashMapBucketArray<Aska::detail::THashMapBucket<Aska::TPair<unsigned long const, bool> >, Aska::TAllocator<Aska::detail::THashMapBucket<Aska::TPair<unsigned long const, bool> > > > >, Aska::THashMapIterator<Aska::detail::THashMapBucketArray<Aska::detail::THashMapBucket<Aska::TPair<unsigned long const, bool> >, Aska::TAllocator<Aska::detail::THashMapBucket<Aska::TPair<unsigned long const, bool> > > > >)
// vaddr 0x11d86e8 | ghidra 0x12d86e8 | size 468 | symbol _ZN4Aska8THashMapImbNS_7THasherImEENS_8TEqualToImEENS_10TAllocatorINS_5TPairIKmbEEEEE6InsertINS_16THashMapIteratorINS_6detail19THashMapBucketArrayINSD_14THashMapBucketIS8_EENS5_ISG_EEEEEEEEvT_SK_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska8THashMapImbNS_7THasherImEENS_8TEqualToImEENS_10TAllocatorINS_5TPairIKmbEEEEE6InsertINS_16THashMapIteratorINS_6detail19THashMapBucketArrayINSD_14THashMapBucketIS8_EENS5_ISG_EEEEEEEEvT_SK_
               (long param_1,long *param_2,undefined8 *param_3)

{
  ulong uVar1;
  char cVar2;
  ulong uVar3;
  char *pcVar4;
  char *pcVar5;
  char *pcVar6;
  long lVar7;
  ulong uVar8;
  char *pcVar9;
  ulong uVar10;
  ulong uVar11;
  ulong uVar12;
  
  pcVar5 = (char *)*param_2;
  pcVar6 = (char *)*param_3;
  lVar7 = 0;
  if (pcVar5 != pcVar6) {
    pcVar9 = pcVar5;
    do {
      lVar7 = lVar7 + 1;
      do {
        pcVar4 = (char *)param_2[2];
        if ((char *)param_2[2] == pcVar9) break;
        pcVar9 = pcVar9 + 0x18;
        pcVar4 = pcVar9;
      } while (*pcVar9 != '\x01');
      pcVar9 = pcVar4;
    } while (pcVar9 != pcVar6);
  }
  uVar8 = (ulong)((float)(lVar7 + (ulong)*(uint *)(param_1 + 0x10) +
                         (ulong)*(uint *)(param_1 + 0x14)) / *(float *)(param_1 + 0xc));
  if (*(ulong *)(param_1 + 0x28) < uVar8) {
    Aska::THashMap<unsigned long, bool, Aska::THasher<unsigned long>, Aska::TEqualTo<unsigned long>, Aska::TAllocator<Aska::TPair<unsigned long const, bool> > >::Rehash_(unsigned long)(param_1,uVar8 << 1 | 1);
    pcVar5 = (char *)*param_2;
    pcVar6 = (char *)*param_3;
  }
  if (pcVar5 != pcVar6) {
    do {
      uVar8 = *(ulong *)(param_1 + 0x28);
      if (uVar8 != 0) {
        uVar10 = *(ulong *)(pcVar5 + 8);
        uVar11 = 0;
        uVar12 = ~uVar10 + uVar10 * 0x200000;
        uVar12 = (uVar12 ^ uVar12 >> 0x18) * 0x109;
        uVar12 = (uVar12 ^ uVar12 >> 0xe) * 0x15;
        pcVar6 = (char *)0x0;
        do {
          uVar1 = (uVar12 ^ uVar12 >> 0x1c) * 0x80000001 + uVar11;
          uVar3 = 0;
          if (uVar8 != 0) {
            uVar3 = uVar1 / uVar8;
          }
          lVar7 = uVar1 - uVar3 * uVar8;
          pcVar9 = (char *)(*(long *)(param_1 + 0x20) + lVar7 * 0x18);
          cVar2 = *pcVar9;
          if (cVar2 == '\x01') {
            if (*(ulong *)(*(long *)(param_1 + 0x20) + lVar7 * 0x18 + 8) == uVar10)
            goto code_r0x012d8874;
          }
          else if (cVar2 == '\0') {
            if (pcVar6 != (char *)0x0) {
              pcVar9 = pcVar6;
            }
            break;
          }
          uVar11 = uVar11 + 1;
          if (cVar2 != '\x02' || pcVar6 != (char *)0x0) {
            pcVar9 = pcVar6;
          }
          pcVar6 = pcVar9;
        } while (uVar11 < uVar8);
        if (pcVar9 != (char *)0x0) {
          *(ulong *)(pcVar9 + 8) = uVar10;
          pcVar9[0x10] = pcVar5[0x10];
          if (*pcVar9 == '\0') {
code_r0x012d8860:
            *(int *)(param_1 + 0x10) = *(int *)(param_1 + 0x10) + 1;
          }
          else if (*pcVar9 == '\x02') {
            *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + -1;
            goto code_r0x012d8860;
          }
          *pcVar9 = '\x01';
          pcVar5 = (char *)*param_2;
        }
      }
code_r0x012d8874:
      pcVar6 = pcVar5;
      do {
        pcVar5 = (char *)param_2[2];
        if ((char *)param_2[2] == pcVar6) break;
        pcVar5 = pcVar6 + 0x18;
        *param_2 = (long)pcVar5;
        pcVar9 = pcVar6 + 0x18;
        pcVar6 = pcVar5;
      } while (*pcVar9 != '\x01');
    } while (pcVar5 != (char *)*param_3);
  }
  return;
}

// ==== FUN_012d890c
// vaddr 0x11d890c | ghidra 0x12d890c | size 0 | symbol FUN_012d890c | lib libSOA-3.7.0.so | 2026-10-04
void FUN_012d890c(void)

{
  return;
}

// ==== Aska::TPair<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > const, CAssetInfo>::~TPair()
// vaddr 0x17dce3c | ghidra 0x18dce3c | size 264 | symbol _ZN4Aska5TPairIKNSt6__ndk112basic_stringIcNS1_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS5_22CSTLStringAllocatorInfEEEEE10CAssetInfoED2Ev | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Possible PIC construction at 0x018dcf28: Changing call to branch */
/* WARNING: Removing unreachable block (ram,0x018dcf2c) */

void _ZN4Aska5TPairIKNSt6__ndk112basic_stringIcNS1_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS5_22CSTLStringAllocatorInfEEEEE10CAssetInfoED2Ev
               (byte *param_1)

{
  byte bVar1;
  undefined *puVar2;
  undefined8 uVar3;
  long lVar4;
  long lVar5;
  
  puVar2 = PTR__ZTVN4Aska6TArrayI9CMetaInfoLb0EEE_02cba9a0;
  *(undefined **)(param_1 + 0x18) = PTR__ZTV10CAssetInfo_02cb7ad0 + 0x10;
  *(undefined **)(param_1 + 0x70) = puVar2 + 0x10;
  *(ushort *)(param_1 + 0xa2) = *(ushort *)(param_1 + 0xa2) | 1;
  if (((*(long **)(param_1 + 0x78) != (long *)0x0) && (0 < *(long *)(param_1 + 0x88))) &&
     ((**(code **)(**(long **)(param_1 + 0x78) + 0x10))(), 1 < *(long *)(param_1 + 0x88))) {
    lVar4 = 1;
    lVar5 = 0x28;
    do {
      (**(code **)(*(long *)(*(long *)(param_1 + 0x78) + lVar5) + 0x10))();
      lVar4 = lVar4 + 1;
      lVar5 = lVar5 + 0x28;
    } while (lVar4 < *(long *)(param_1 + 0x88));
  }
  if ((param_1[0xa2] & 1) != 0) {
    if (*(long *)(param_1 + 0x78) != 0) {
      operator delete[](void*)();
      param_1[0x78] = 0;
      param_1[0x79] = 0;
      param_1[0x7a] = 0;
      param_1[0x7b] = 0;
      param_1[0x7c] = 0;
      param_1[0x7d] = 0;
      param_1[0x7e] = 0;
      param_1[0x7f] = 0;
    }
    param_1[0x80] = 0;
    param_1[0x81] = 0;
    param_1[0x82] = 0;
    param_1[0x83] = 0;
    param_1[0x84] = 0;
    param_1[0x85] = 0;
    param_1[0x86] = 0;
    param_1[0x87] = 0;
  }
  param_1[0x88] = 0;
  param_1[0x89] = 0;
  param_1[0x8a] = 0;
  param_1[0x8b] = 0;
  param_1[0x8c] = 0;
  param_1[0x8d] = 0;
  param_1[0x8e] = 0;
  param_1[0x8f] = 0;
  param_1[0x90] = 0;
  param_1[0x91] = 0;
  param_1[0x92] = 0;
  param_1[0x93] = 0;
  param_1[0x94] = 0;
  param_1[0x95] = 0;
  param_1[0x96] = 0;
  param_1[0x97] = 0;
  if ((param_1[0x58] & 1) == 0) {
    bVar1 = param_1[0x28];
  }
  else {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(*(undefined8 *)(param_1 + 0x68));
    bVar1 = param_1[0x28];
  }
  if ((bVar1 & 1) == 0) {
    if ((*param_1 & 1) == 0) {
      return;
    }
    uVar3 = *(undefined8 *)(param_1 + 0x10);
  }
  else {
    uVar3 = *(undefined8 *)(param_1 + 0x38);
  }
  (*(code *)PTR__ZN9Framework37CAssignedMemoryManagerForSTLAllocator4FreeEPv_02ca11c0)(uVar3);
  return;
}

// ==== Aska::THashMap<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> >, CAssetInfo, Hasher_CSTLString, Aska::TEqualTo<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > >, Aska::TAllocator<Aska::TPair<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > const, CAssetInfo> > >::Erase(std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > const&)
// vaddr 0x17dd100 | ghidra 0x18dd100 | size 388 | symbol _ZN4Aska8THashMapINSt6__ndk112basic_stringIcNS1_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS5_22CSTLStringAllocatorInfEEEEE10CAssetInfo17Hasher_CSTLStringNS_8TEqualToIS9_EENS_10TAllocatorINS_5TPairIKS9_SA_EEEEE5EraseERSG_ | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska8THashMapINSt6__ndk112basic_stringIcNS1_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS5_22CSTLStringAllocatorInfEEEEE10CAssetInfo17Hasher_CSTLStringNS_8TEqualToIS9_EENS_10TAllocatorINS_5TPairIKS9_SA_EEEEE5EraseERSG_
          (long param_1,byte *param_2)

{
  ulong uVar1;
  long lVar2;
  ulong uVar3;
  ulong uVar4;
  byte *pbVar5;
  byte bVar6;
  ulong uVar7;
  int iVar8;
  ulong uVar9;
  long lVar10;
  byte *pbVar11;
  byte *pbVar12;
  long lVar13;
  ulong uVar14;
  char *pcVar15;
  long lVar16;
  undefined1 auStack_70 [16];
  
  lVar2 = *(long *)(param_1 + 0x20);
  uVar4 = *(ulong *)(param_1 + 0x28);
  Framework::CHash32::CHash32(string const&)(auStack_70);
  uVar9 = Framework::CHash32::operator unsigned int() const(auStack_70);
  Framework::CHash32::~CHash32()(auStack_70);
  if (uVar4 != 0) {
    uVar3 = *(ulong *)(param_2 + 8);
    pbVar5 = *(byte **)(param_2 + 0x10);
    uVar14 = 0;
    if ((*param_2 & 1) == 0) {
      pbVar5 = param_2 + 1;
      uVar3 = (ulong)(*param_2 >> 1);
    }
    do {
      uVar1 = uVar14 + (uVar9 & 0xffffffff);
      uVar7 = 0;
      if (uVar4 != 0) {
        uVar7 = uVar1 / uVar4;
      }
      lVar16 = uVar1 - uVar7 * uVar4;
      pcVar15 = (char *)(lVar2 + lVar16 * 0xc0);
      if (*pcVar15 == '\x01') {
        lVar10 = lVar2 + lVar16 * 0xc0;
        bVar6 = *(byte *)(lVar10 + 8);
        uVar1 = (ulong)(bVar6 >> 1);
        if ((bVar6 & 1) != 0) {
          uVar1 = *(ulong *)(lVar10 + 0x10);
        }
        if (uVar1 == uVar3) {
          lVar13 = *(long *)(lVar2 + lVar16 * 0xc0 + 0x18);
          if ((bVar6 & 1) == 0) {
            lVar13 = lVar10 + 9;
          }
          if ((bVar6 & 1) == 0) {
            if (uVar3 == 0) {
code_r0x018dd220:
              Aska::TPair<string const, CAssetInfo>::~TPair()(lVar2 + lVar16 * 0xc0 + 8);
              if (*pcVar15 != '\0') {
                if (*pcVar15 != '\x01') goto code_r0x018dd258;
                *(int *)(param_1 + 0x10) = *(int *)(param_1 + 0x10) + -1;
              }
              *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + 1;
code_r0x018dd258:
              *pcVar15 = '\x02';
              return 1;
            }
            pbVar11 = (byte *)(lVar10 + 9);
            lVar10 = -(ulong)(bVar6 >> 1);
            pbVar12 = pbVar5;
            while (*pbVar11 == *pbVar12) {
              pbVar11 = pbVar11 + 1;
              lVar10 = lVar10 + 1;
              pbVar12 = pbVar12 + 1;
              if (lVar10 == 0) goto code_r0x018dd220;
            }
          }
          else if ((uVar3 == 0) || (iVar8 = memcmp(lVar13,pbVar5,uVar3), iVar8 == 0))
          goto code_r0x018dd220;
        }
      }
      else if (*pcVar15 == '\0') {
        return 0;
      }
      uVar14 = uVar14 + 1;
    } while (uVar14 < uVar4);
  }
  return 0;
}

// ==== Aska::TPair<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > const, CAssetInfo>::TPair<char const*, CAssetInfo>(char const* const&, CAssetInfo const&)
// vaddr 0x17e424c | ghidra 0x18e424c | size 224 | symbol _ZN4Aska5TPairIKNSt6__ndk112basic_stringIcNS1_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS5_22CSTLStringAllocatorInfEEEEE10CAssetInfoEC2IPKcSB_EERKT_RKT0_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5TPairIKNSt6__ndk112basic_stringIcNS1_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS5_22CSTLStringAllocatorInfEEEEE10CAssetInfoEC2IPKcSB_EERKT_RKT0_
               (ulong *param_1,undefined8 *param_2,undefined8 param_3)

{
  ulong uVar1;
  undefined8 uVar2;
  ulong uVar3;
  ulong uVar4;
  
  uVar2 = *param_2;
  param_1[1] = 0;
  param_1[2] = 0;
  *param_1 = 0;
  uVar1 = strlen(uVar2);
  if (uVar1 < 0x17) {
    uVar3 = (long)param_1 + 1;
    *(char *)param_1 = (char)(uVar1 << 1);
    if (uVar1 == 0) goto code_r0x011e8b80;
  }
  else {
    uVar4 = uVar1 + 0x10 & 0xfffffffffffffff0;
    if (uVar4 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
    }
    uVar3 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar4,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
    if (uVar3 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    }
    param_1[1] = uVar1;
    param_1[2] = uVar3;
    *param_1 = uVar4 | 1;
  }
  memcpy(uVar3,uVar2,uVar1);
code_r0x011e8b80:
  *(undefined1 *)(uVar3 + uVar1) = 0;
  (*(code *)PTR__ZN10CAssetInfoC2ERKS__02cac5b0)(param_1 + 3,param_3);
  return;
}

// ==== FUN_018e7ea4
// vaddr 0x17e7ea4 | ghidra 0x18e7ea4 | size 0 | symbol FUN_018e7ea4 | lib libSOA-3.7.0.so | 2026-10-04
void FUN_018e7ea4(ulong *param_1)

{
  byte bVar1;
  ulong uVar2;
  long lVar3;
  ulong uVar4;
  ulong uVar5;
  ulong uVar6;
  byte *pbVar7;
  byte bStack_48;
  undefined7 uStack_47;
  ulong uStack_40;
  ulong uStack_38;
  
  BAS::GetDownloadPath()(&bStack_48);
  uVar4 = (ulong)bStack_48;
  if ((bStack_48 & 1) == 0) {
    uVar2 = 0x16;
  }
  else {
    uVar4 = CONCAT71(uStack_47,bStack_48);
    uVar2 = (uVar4 & 0xfffffffffffffffe) - 1;
  }
  uVar5 = (ulong)(((uint)uVar4 & 0xfe) >> 1);
  if ((uVar4 & 1) != 0) {
    uVar5 = uStack_40;
  }
  if (uVar2 == uVar5) {
    string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&bStack_48,uVar2,1,uVar2,uVar2,0,1,&UNK_029c5d3e/*"/"*/);
  }
  else {
    uVar2 = (ulong)&bStack_48 | 1;
    if ((uVar4 & 1) != 0) {
      uVar2 = uStack_38;
    }
    *(undefined1 *)(uVar2 + uVar5) = 0x2f;
    uVar5 = uVar5 + 1;
    uVar4 = uVar5;
    if ((bStack_48 & 1) == 0) {
      bStack_48 = (char)uVar5 * '\x02';
      uVar4 = uStack_40;
    }
    uStack_40 = uVar4;
    *(undefined1 *)(uVar2 + uVar5) = 0;
  }
  param_1[2] = uStack_38;
  param_1[1] = uStack_40;
  *param_1 = CONCAT71(uStack_47,bStack_48);
  CGameResourceDownloader::CheckLocalResourceFileToolVersionOld()+0x354(&bStack_48);
  bVar1 = (byte)*param_1;
  uVar5 = (ulong)bVar1;
  uVar4 = (ulong)(bStack_48 >> 1);
  uVar2 = (ulong)&bStack_48 | 1;
  if ((bStack_48 & 1) != 0) {
    uVar4 = uStack_40;
    uVar2 = uStack_38;
  }
  if ((bVar1 & 1) == 0) {
    lVar3 = 0x16;
    if ((bVar1 & 1) != 0) {
LAB_018e7fa4:
      uVar6 = param_1[1];
      goto LAB_018e7fc4;
    }
  }
  else {
    uVar5 = *param_1;
    lVar3 = (uVar5 & 0xfffffffffffffffe) - 1;
    if ((uVar5 & 1) != 0) goto LAB_018e7fa4;
  }
  uVar6 = (ulong)(((uint)uVar5 & 0xfe) >> 1);
LAB_018e7fc4:
  if (lVar3 - uVar6 < uVar4) {
    string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(param_1,lVar3,(uVar4 - lVar3) + uVar6,uVar6,uVar6,0,uVar4);
  }
  else if (uVar4 != 0) {
    if ((uVar5 & 1) == 0) {
      pbVar7 = (byte *)((long)param_1 + 1);
    }
    else {
      pbVar7 = (byte *)param_1[2];
    }
    memcpy(pbVar7 + uVar6,uVar2,uVar4);
    uVar6 = uVar6 + uVar4;
    if ((*param_1 & 1) == 0) {
      *(char *)param_1 = (char)uVar6 * '\x02';
      pbVar7[uVar6] = 0;
    }
    else {
      param_1[1] = uVar6;
      pbVar7[uVar6] = 0;
    }
  }
  if ((bStack_48 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_38);
  }
  return;
}

// ==== Aska::THashMap<unsigned int, bool, Aska::THasher<unsigned int>, Aska::TEqualTo<unsigned int>, Aska::TAllocator<Aska::TPair<unsigned int const, bool> > >::Rehash_(unsigned long)
// vaddr 0x17e8440 | ghidra 0x18e8440 | size 516 | symbol _ZN4Aska8THashMapIjbNS_7THasherIjEENS_8TEqualToIjEENS_10TAllocatorINS_5TPairIKjbEEEEE7Rehash_Em | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska8THashMapIjbNS_7THasherIjEENS_8TEqualToIjEENS_10TAllocatorINS_5TPairIKjbEEEEE7Rehash_Em
               (undefined1 *param_1,ulong param_2)

{
  ulong uVar1;
  undefined *puVar2;
  undefined1 *puVar3;
  undefined1 *puVar4;
  undefined8 uVar5;
  char *pcVar6;
  ulong uVar7;
  long lVar8;
  ulong uVar9;
  float fVar10;
  float fVar11;
  undefined *puStack_90;
  float fStack_84;
  undefined4 uStack_80;
  undefined4 uStack_7c;
  undefined1 *puStack_70;
  ulong uStack_68;
  char *pcStack_60;
  char *pcStack_58;
  char *pcStack_50;
  char *pcStack_48;
  char *pcStack_40;
  char *pcStack_38;
  
  puVar2 = 
  PTR__ZTVN4Aska8THashMapIjbNS_7THasherIjEENS_8TEqualToIjEENS_10TAllocatorINS_5TPairIKjbEEEEEE_02cbac18
  ;
  puStack_90 = PTR__ZTVN4Aska8THashMapIjbNS_7THasherIjEENS_8TEqualToIjEENS_10TAllocatorINS_5TPairIKjbEEEEEE_02cbac18
               + 0x10;
  fStack_84 = 0.75;
  uStack_80 = 0;
  uStack_7c = 0;
  if (param_2 < 0x1555555555555556) {
    puStack_70 = (undefined1 *)Aska::MemoryManagerAdapter::AlignedMalloc(unsigned long, unsigned long)(param_2 * 0xc,4);
  }
  else {
    puStack_70 = (undefined1 *)0x0;
  }
  if (puStack_70 == (undefined1 *)0x0) {
    param_2 = 0;
  }
  if (param_2 == 0) {
    fVar10 = *(float *)(param_1 + 0xc);
code_r0x018e8558:
    if (fVar10 <= 0.0) goto code_r0x018e8568;
  }
  else {
    uVar1 = (param_2 * 0xc - 0xc) / 0xc + 1;
    puVar3 = puStack_70;
    if ((uVar1 < 2) || (uVar7 = uVar1 & 0x3ffffffffffffffe, uVar7 == 0)) {
code_r0x018e8510:
      do {
        puVar4 = puVar3 + 0xc;
        *puVar3 = 0;
        puVar3 = puVar4;
      } while (puStack_70 + param_2 * 0xc != puVar4);
    }
    else {
      puVar3 = puStack_70 + uVar7 * 0xc;
      uVar9 = uVar7;
      puVar4 = puStack_70;
      do {
        *puVar4 = 0;
        puVar4[0xc] = 0;
        uVar9 = uVar9 - 2;
        puVar4 = puVar4 + 0x18;
      } while (uVar9 != 0);
      if (uVar1 != uVar7) goto code_r0x018e8510;
    }
    fVar10 = *(float *)(param_1 + 0xc);
    if (param_2 == 0) goto code_r0x018e8558;
    fVar11 = (float)NEON_ucvtf(uStack_80);
    if (fVar10 <= fVar11 / (float)param_2) goto code_r0x018e8568;
  }
  fStack_84 = fVar10;
code_r0x018e8568:
  pcStack_58 = *(char **)(param_1 + 0x20);
  lVar8 = *(long *)(param_1 + 0x28);
  pcStack_60 = pcStack_58 + lVar8 * 0xc;
  pcStack_48 = pcStack_60;
  if ((*(int *)(param_1 + 0x10) != 0) && (pcStack_48 = pcStack_58, lVar8 != 0)) {
    lVar8 = lVar8 * 0xc;
    pcVar6 = pcStack_58;
    do {
      pcStack_48 = pcVar6;
      if (*pcVar6 == '\x01') break;
      lVar8 = lVar8 + -0xc;
      pcVar6 = pcVar6 + 0xc;
      pcStack_48 = pcStack_60;
    } while (lVar8 != 0);
  }
  uStack_68 = param_2;
  pcStack_50 = pcStack_60;
  pcStack_40 = pcStack_58;
  pcStack_38 = pcStack_60;
  void Aska::THashMap<unsigned int, bool, Aska::THasher<unsigned int>, Aska::TEqualTo<unsigned int>, Aska::TAllocator<Aska::TPair<unsigned int const, bool> > >::Insert<Aska::THashMapIterator<Aska::detail::THashMapBucketArray<Aska::detail::THashMapBucket<Aska::TPair<unsigned int const, bool> >, Aska::TAllocator<Aska::detail::THashMapBucket<Aska::TPair<unsigned int const, bool> > > > > >(Aska::THashMapIterator<Aska::detail::THashMapBucketArray<Aska::detail::THashMapBucket<Aska::TPair<unsigned int const, bool> >, Aska::TAllocator<Aska::detail::THashMapBucket<Aska::TPair<unsigned int const, bool> > > > >, Aska::THashMapIterator<Aska::detail::THashMapBucketArray<Aska::detail::THashMapBucket<Aska::TPair<unsigned int const, bool> >, Aska::TAllocator<Aska::detail::THashMapBucket<Aska::TPair<unsigned int const, bool> > > > >)(&puStack_90,&pcStack_48,&pcStack_60);
  if (&puStack_90 != (undefined **)param_1) {
    uVar5 = *(undefined8 *)(param_1 + 0x10);
    *(ulong *)(param_1 + 0x10) = CONCAT44(uStack_7c,uStack_80);
    uStack_80 = (undefined4)uVar5;
    uStack_7c = (undefined4)((ulong)uVar5 >> 0x20);
    puVar3 = *(undefined1 **)(param_1 + 0x20);
    uVar1 = *(ulong *)(param_1 + 0x28);
    *(ulong *)(param_1 + 0x28) = uStack_68;
    *(undefined1 **)(param_1 + 0x20) = puStack_70;
    fVar10 = *(float *)(param_1 + 0xc);
    *(float *)(param_1 + 0xc) = fStack_84;
    fStack_84 = fVar10;
    puStack_70 = puVar3;
    uStack_68 = uVar1;
  }
  puStack_90 = puVar2 + 0x10;
  if (puStack_70 != (undefined1 *)0x0) {
    Aska::MemoryManagerAdapter::AlignedFree(void*)();
  }
  return;
}

// ==== void Aska::THashMap<unsigned int, bool, Aska::THasher<unsigned int>, Aska::TEqualTo<unsigned int>, Aska::TAllocator<Aska::TPair<unsigned int const, bool> > >::Insert<Aska::THashMapIterator<Aska::detail::THashMapBucketArray<Aska::detail::THashMapBucket<Aska::TPair<unsigned int const, bool> >, Aska::TAllocator<Aska::detail::THashMapBucket<Aska::TPair<unsigned int const, bool> > > > > >(Aska::THashMapIterator<Aska::detail::THashMapBucketArray<Aska::detail::THashMapBucket<Aska::TPair<unsigned int const, bool> >, Aska::TAllocator<Aska::detail::THashMapBucket<Aska::TPair<unsigned int const, bool> > > > >, Aska::THashMapIterator<Aska::detail::THashMapBucketArray<Aska::detail::THashMapBucket<Aska::TPair<unsigned int const, bool> >, Aska::TAllocator<Aska::detail::THashMapBucket<Aska::TPair<unsigned int const, bool> > > > >)
// vaddr 0x17e8644 | ghidra 0x18e8644 | size 468 | symbol _ZN4Aska8THashMapIjbNS_7THasherIjEENS_8TEqualToIjEENS_10TAllocatorINS_5TPairIKjbEEEEE6InsertINS_16THashMapIteratorINS_6detail19THashMapBucketArrayINSD_14THashMapBucketIS8_EENS5_ISG_EEEEEEEEvT_SK_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska8THashMapIjbNS_7THasherIjEENS_8TEqualToIjEENS_10TAllocatorINS_5TPairIKjbEEEEE6InsertINS_16THashMapIteratorINS_6detail19THashMapBucketArrayINSD_14THashMapBucketIS8_EENS5_ISG_EEEEEEEEvT_SK_
               (long param_1,long *param_2,undefined8 *param_3)

{
  ulong uVar1;
  uint uVar2;
  char cVar3;
  ulong uVar4;
  char *pcVar5;
  char *pcVar6;
  char *pcVar7;
  long lVar8;
  ulong uVar9;
  char *pcVar10;
  ulong uVar11;
  ulong uVar12;
  
  pcVar6 = (char *)*param_2;
  pcVar7 = (char *)*param_3;
  lVar8 = 0;
  if (pcVar6 != pcVar7) {
    pcVar10 = pcVar6;
    do {
      lVar8 = lVar8 + 1;
      do {
        pcVar5 = (char *)param_2[2];
        if ((char *)param_2[2] == pcVar10) break;
        pcVar10 = pcVar10 + 0xc;
        pcVar5 = pcVar10;
      } while (*pcVar10 != '\x01');
      pcVar10 = pcVar5;
    } while (pcVar10 != pcVar7);
  }
  uVar9 = (ulong)((float)(lVar8 + (ulong)*(uint *)(param_1 + 0x10) +
                         (ulong)*(uint *)(param_1 + 0x14)) / *(float *)(param_1 + 0xc));
  if (*(ulong *)(param_1 + 0x28) < uVar9) {
    Aska::THashMap<unsigned int, bool, Aska::THasher<unsigned int>, Aska::TEqualTo<unsigned int>, Aska::TAllocator<Aska::TPair<unsigned int const, bool> > >::Rehash_(unsigned long)(param_1,uVar9 << 1 | 1);
    pcVar6 = (char *)*param_2;
    pcVar7 = (char *)*param_3;
  }
  if (pcVar6 != pcVar7) {
    do {
      uVar9 = *(ulong *)(param_1 + 0x28);
      if (uVar9 != 0) {
        uVar2 = *(uint *)(pcVar6 + 4);
        uVar11 = 0;
        uVar12 = ~(ulong)uVar2 + (ulong)uVar2 * 0x200000;
        uVar12 = (uVar12 ^ uVar12 >> 0x18) * 0x109;
        uVar12 = (uVar12 ^ uVar12 >> 0xe) * 0x15;
        pcVar7 = (char *)0x0;
        do {
          uVar1 = (uVar12 ^ uVar12 >> 0x1c) * 0x80000001 + uVar11;
          uVar4 = 0;
          if (uVar9 != 0) {
            uVar4 = uVar1 / uVar9;
          }
          lVar8 = uVar1 - uVar4 * uVar9;
          pcVar10 = (char *)(*(long *)(param_1 + 0x20) + lVar8 * 0xc);
          cVar3 = *pcVar10;
          if (cVar3 == '\x01') {
            if (*(uint *)(*(long *)(param_1 + 0x20) + lVar8 * 0xc + 4) == uVar2)
            goto code_r0x018e87d0;
          }
          else if (cVar3 == '\0') {
            if (pcVar7 != (char *)0x0) {
              pcVar10 = pcVar7;
            }
            break;
          }
          uVar11 = uVar11 + 1;
          if (cVar3 != '\x02' || pcVar7 != (char *)0x0) {
            pcVar10 = pcVar7;
          }
          pcVar7 = pcVar10;
        } while (uVar11 < uVar9);
        if (pcVar10 != (char *)0x0) {
          *(uint *)(pcVar10 + 4) = uVar2;
          pcVar10[8] = pcVar6[8];
          if (*pcVar10 == '\0') {
code_r0x018e87bc:
            *(int *)(param_1 + 0x10) = *(int *)(param_1 + 0x10) + 1;
          }
          else if (*pcVar10 == '\x02') {
            *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + -1;
            goto code_r0x018e87bc;
          }
          *pcVar10 = '\x01';
          pcVar6 = (char *)*param_2;
        }
      }
code_r0x018e87d0:
      pcVar7 = pcVar6;
      do {
        pcVar6 = (char *)param_2[2];
        if ((char *)param_2[2] == pcVar7) break;
        pcVar6 = pcVar7 + 0xc;
        *param_2 = (long)pcVar6;
        pcVar10 = pcVar7 + 0xc;
        pcVar7 = pcVar6;
      } while (*pcVar10 != '\x01');
    } while (pcVar6 != (char *)*param_3);
  }
  return;
}

// ==== FUN_018e887c
// vaddr 0x17e887c | ghidra 0x18e887c | size 0 | symbol FUN_018e887c | lib libSOA-3.7.0.so | 2026-10-04
void FUN_018e887c(void)

{
  return;
}

// ==== FUN_018e8884
// vaddr 0x17e8884 | ghidra 0x18e8884 | size 0 | symbol FUN_018e8884 | lib libSOA-3.7.0.so | 2026-10-04
void FUN_018e8884(long param_1,undefined8 *param_2,undefined8 *param_3,long *param_4)

{
  char *pcVar1;
  ulong uVar2;
  ulong uVar3;
  int iVar4;
  uint uVar5;
  undefined4 uVar6;
  long lVar7;
  long lVar8;
  ulong uVar9;
  long *plVar10;
  undefined1 *puVar11;
  ulong *puVar12;
  undefined8 uVar13;
  ulong uVar14;
  undefined8 uVar15;
  long lVar16;
  char *pcVar17;
  char *pcVar18;
  ulong uVar19;
  char *pcVar20;
  long lVar21;
  long lVar22;
  long lVar23;
  ulong *puStack_4c0;
  undefined8 uStack_4b8;
  undefined8 uStack_4b0;
  ulong auStack_3c0 [2];
  ulong uStack_3b0;
  ulong uStack_3a8;
  ulong uStack_3a0;
  ulong uStack_2b0;
  ulong uStack_2a8;
  char *pcStack_2a0;
  ulong uStack_1b0;
  ulong uStack_1a8;
  char *pcStack_1a0;
  ulong uStack_190;
  ulong uStack_188;
  ulong uStack_180;
  undefined1 *puStack_178;
  undefined8 uStack_170;
  undefined1 auStack_168 [256];
  ulong *puStack_68;
  
  uVar13 = *param_2;
  uVar15 = *param_3;
  snprintf(auStack_168,0x100,&UNK_0282d96b/*"%s/"*/,uVar13);
  uStack_170 = 0;
  puStack_178 = auStack_168;
  lVar7 = fts_open(&puStack_178,2,0);
  if (lVar7 != 0) {
    uStack_180 = 0;
    uStack_188 = 0;
    uStack_190 = 0;
    pcStack_1a0 = (char *)0x0;
    uStack_1a8 = 0;
    uStack_1b0 = 0;
    string::reserve(unsigned long)(&uStack_190,0x40);
    string::reserve(unsigned long)(&uStack_1b0,0x80);
    lVar8 = fts_read(lVar7);
    if (lVar8 != 0) {
      do {
        if (*(long *)(lVar8 + 0x48) != 0) {
          lVar22 = *(long *)(lVar8 + 0x28);
          if (lVar22 != 0) {
            uVar9 = strlen(lVar22);
            if ((uStack_1b0 & 1) == 0) {
              uVar14 = 0x16;
              lVar16 = uVar9 - 0x16;
              uVar19 = uStack_1b0 & 0xff;
              if (0x15 < uVar9 && lVar16 != 0) goto LAB_018e8a08;
LAB_018e89bc:
              pcVar20 = (char *)((ulong)&uStack_1b0 | 1);
              if ((uVar19 & 1) != 0) {
                pcVar20 = pcStack_1a0;
              }
              if (uVar9 != 0) {
                memmove(pcVar20,lVar22,uVar9);
              }
              pcVar20[uVar9] = '\0';
              if ((uStack_1b0 & 1) == 0) {
                uStack_1b0 = CONCAT71(uStack_1b0._1_7_,(char)(uVar9 << 1));
                uVar9 = uStack_1a8;
              }
            }
            else {
              uVar14 = (uStack_1b0 & 0xfffffffffffffffe) - 1;
              lVar16 = uVar9 - uVar14;
              uVar19 = uStack_1b0;
              if (uVar9 < uVar14 || lVar16 == 0) goto LAB_018e89bc;
LAB_018e8a08:
              uVar2 = (ulong)(((uint)uVar19 & 0xfe) >> 1);
              if ((uVar19 & 1) != 0) {
                uVar2 = uStack_1a8;
              }
              string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&uStack_1b0,uVar14,lVar16,uVar2,0,uVar2,uVar9,lVar22);
              uVar9 = uStack_1a8;
            }
            uStack_1a8 = uVar9;
            uStack_3a8 = 0;
            uStack_3a0 = 0;
            uStack_3b0 = 0;
            uVar9 = strlen(auStack_168);
            if (uVar9 < 0x17) {
              uStack_3b0 = CONCAT71(uStack_3b0._1_7_,(char)(uVar9 << 1));
              uVar14 = (ulong)&uStack_3b0 | 1;
              if (uVar9 != 0) goto LAB_018e8ad0;
            }
            else {
              uVar19 = uVar9 + 0x10 & 0xfffffffffffffff0;
              if (uVar19 == 0) {
                Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
              }
              uVar14 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar19,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
              if (uVar14 == 0) {
                Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
              }
              uStack_3b0 = uVar19 | 1;
              uStack_3a8 = uVar9;
              uStack_3a0 = uVar14;
LAB_018e8ad0:
              memcpy(uVar14,auStack_168,uVar9);
            }
            *(undefined1 *)(uVar14 + uVar9) = 0;
            uStack_4b8 = 0;
            uStack_4b0 = 0;
            puStack_4c0 = (ulong *)0x0;
            Framework::CSTLStringUtility_Base<string >::Replace(string const&, string const&, string const&, bool*)(&uStack_2b0,&uStack_1b0,&uStack_3b0,&puStack_4c0,0);
            if ((uStack_1b0 & 1) == 0) {
              uStack_1b0 = uStack_1b0 & 0xffffffffffff0000;
            }
            else {
              *pcStack_1a0 = '\0';
              uStack_1a8 = 0;
            }
            string::reserve(unsigned long)(&uStack_1b0,0);
            pcStack_1a0 = pcStack_2a0;
            uStack_1b0 = uStack_2b0;
            pcStack_2a0 = (char *)0x0;
            uStack_2b0 = 0;
            uStack_1a8 = uStack_2a8;
            uStack_2a8 = 0;
            if (((ulong)puStack_4c0 & 1) != 0) {
              Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_4b0);
            }
            if ((uStack_3b0 & 1) != 0) {
              Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_3a0);
            }
            pcVar20 = (char *)((ulong)&uStack_1b0 | 1);
            uVar9 = uStack_1b0 >> 1 & 0x7f;
            if ((uStack_1b0 & 1) != 0) {
              pcVar20 = pcStack_1a0;
              uVar9 = uStack_1a8;
            }
            if (uVar9 != 0) {
              pcVar1 = pcVar20 + uVar9;
              pcVar17 = pcVar20;
              pcVar18 = pcVar1;
              if (0 < (long)uVar9) {
                do {
                  pcVar18 = pcVar17;
                  if (*pcVar17 == '/') break;
                  uVar9 = uVar9 - 1;
                  pcVar17 = pcVar17 + 1;
                  pcVar18 = pcVar1;
                } while (uVar9 != 0);
              }
              if ((pcVar1 != pcVar18) && ((long)pcVar18 - (long)pcVar20 != -1)) goto LAB_018e9244;
            }
          }
          lVar8 = lVar8 + 0x78;
          uVar9 = strlen(lVar8);
          if ((uStack_190 & 1) == 0) {
            uVar14 = 0x16;
            lVar22 = uVar9 - 0x16;
            uVar19 = uStack_190 & 0xff;
            if (0x15 < uVar9 && lVar22 != 0) goto LAB_018e8c44;
LAB_018e8bf4:
            uVar14 = (ulong)&uStack_190 | 1;
            if ((uVar19 & 1) != 0) {
              uVar14 = uStack_180;
            }
            if (uVar9 != 0) {
              memmove(uVar14,lVar8,uVar9);
            }
            *(undefined1 *)(uVar14 + uVar9) = 0;
            if ((uStack_190 & 1) == 0) {
              uStack_190 = CONCAT71(uStack_190._1_7_,(char)(uVar9 << 1));
              uVar9 = uStack_188;
            }
          }
          else {
            uVar14 = (uStack_190 & 0xfffffffffffffffe) - 1;
            lVar22 = uVar9 - uVar14;
            uVar19 = uStack_190;
            if (uVar9 < uVar14 || lVar22 == 0) goto LAB_018e8bf4;
LAB_018e8c44:
            uVar2 = (ulong)(((uint)uVar19 & 0xfe) >> 1);
            if ((uVar19 & 1) != 0) {
              uVar2 = uStack_188;
            }
            string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&uStack_190,uVar14,lVar22,uVar2,0,uVar2,uVar9,lVar8);
            uVar9 = uStack_188;
          }
          uStack_188 = uVar9;
          uStack_3a8 = 0;
          uStack_3a0 = 0;
          uStack_3b0 = 0x2e02;
          Framework::CSTLStringUtility_Base<string >::GetExtension(string const&, string const&)(&uStack_2b0,&uStack_190,&uStack_3b0);
          uVar9 = uStack_2b0 >> 1 & 0x7f;
          if ((uStack_2b0 & 1) != 0) {
            uVar9 = uStack_2a8;
          }
          if ((uStack_2b0 & 1) != 0) {
            Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(pcStack_2a0);
          }
          if ((uStack_3b0 & 1) != 0) {
            Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_3a0);
          }
          if (uVar9 == 0) {
            iVar4 = strcmp(uVar15,&UNK_02a50598/*"."*/);
            if (iVar4 == 0) {
              snprintf(&uStack_2b0,0x100,&UNK_027f6a37/*"%s"*/,lVar8);
            }
            else {
              snprintf(&uStack_2b0,0x100,&UNK_02866ccf/*"%s/%s"*/,uVar15,lVar8);
            }
            snprintf(&uStack_3b0,0x100,&UNK_02866ccf/*"%s/%s"*/,uVar13,lVar8);
            Framework::CHash32::CHash32(char const*)(auStack_3c0,&uStack_3b0);
            lVar22 = *(long *)(param_1 + 0x18);
            uVar5 = Framework::CHash32::operator unsigned int() const(auStack_3c0);
            lVar8 = *(long *)(lVar22 + 0x20);
            uVar9 = *(ulong *)(lVar22 + 0x28);
            if (uVar9 != 0) {
              uVar19 = ~(ulong)uVar5 + (ulong)uVar5 * 0x200000;
              uVar19 = (uVar19 ^ uVar19 >> 0x18) * 0x109;
              uVar14 = (uVar19 ^ uVar19 >> 0xe) * 0x15;
              uVar19 = 0;
              do {
                uVar2 = (uVar14 ^ uVar14 >> 0x1c) * 0x80000001 + uVar19;
                uVar3 = 0;
                if (uVar9 != 0) {
                  uVar3 = uVar2 / uVar9;
                }
                lVar22 = uVar2 - uVar3 * uVar9;
                pcVar20 = (char *)(lVar8 + lVar22 * 0xc);
                if (*pcVar20 == '\x01') {
                  if (*(uint *)(lVar8 + lVar22 * 0xc + 4) == uVar5) goto LAB_018e8e1c;
                }
                else if (*pcVar20 == '\0') break;
                uVar19 = uVar19 + 1;
              } while (uVar19 < uVar9);
            }
            pcVar20 = (char *)(lVar8 + uVar9 * 0xc);
LAB_018e8e1c:
            lVar8 = *(long *)(param_1 + 0x18);
            if (pcVar20 == (char *)(*(long *)(lVar8 + 0x20) + *(long *)(lVar8 + 0x28) * 0xc)) {
              uVar6 = Framework::CHash32::operator unsigned int() const(auStack_3c0);
              puStack_4c0 = (ulong *)CONCAT44(puStack_4c0._4_4_,uVar6);
              puVar11 = (undefined1 *)Aska::THashMap<unsigned int, bool, Aska::THasher<unsigned int>, Aska::TEqualTo<unsigned int>, Aska::TAllocator<Aska::TPair<unsigned int const, bool> > >::operator[](unsigned int const&)(lVar8,&puStack_4c0);
              *puVar11 = 1;
              if ((*(byte *)(param_1 + 0x10) & 1) == 0) {
                plVar10 = *(long **)(*(long *)(param_1 + 8) + 0x20);
                puStack_4c0 = &uStack_3b0;
                puStack_68 = &uStack_2b0;
                (**(code **)(*plVar10 + 0x30))(plVar10,&puStack_4c0,&puStack_68,param_4);
              }
              else {
                uVar9 = strlen(&uStack_3b0);
                if (0xff < uVar9) {
                  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dc32f/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/Utility.h"*/,0x77,&UNK_027dc380/*"gStrcpy() : destination buffer is small. ( %d < %d )"*/,uVar9,0x100);
                }
                strcpy(&puStack_4c0,&uStack_3b0);
                lVar8 = param_4[1];
                if (lVar8 == param_4[2]) {
                  uVar9 = lVar8 - *param_4 >> 8;
                  if (uVar9 < 0x7fffffffffffff) {
                    uVar14 = lVar8 - *param_4 >> 7;
                    uVar19 = uVar9 + 1;
                    if (uVar9 + 1 <= uVar14) {
                      uVar19 = uVar14;
                    }
                    if (uVar19 != 0) goto LAB_018e90c4;
                    lVar8 = 0;
                    lVar22 = uVar9 << 8;
                  }
                  else {
                    uVar19 = 0xffffffffffffff;
LAB_018e90c4:
                    lVar8 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar19 << 8,&UNK_027dc536/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Vector.h"*/,0x20);
                    if (lVar8 == 0) {
                      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
                      lVar22 = uVar9 * 0x100;
                    }
                    else {
                      lVar22 = lVar8 + uVar9 * 0x100;
                    }
                  }
                  if (lVar22 == 0) {
                    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
                  }
                  memcpy(lVar22,&puStack_4c0,0x100);
                  lVar21 = *param_4;
                  lVar23 = param_4[1];
                  lVar16 = lVar22 + 0x100;
                  if (lVar23 != lVar21) {
                    do {
                      lVar23 = lVar23 + -0x100;
                      memcpy(lVar22 + -0x100,lVar23,0x100);
                      lVar22 = lVar22 + -0x100;
                    } while (lVar21 != lVar23);
                    lVar21 = *param_4;
                  }
                  *param_4 = lVar22;
                  param_4[1] = lVar16;
                  param_4[2] = lVar8 + uVar19 * 0x100;
                  if (lVar21 != 0) {
                    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(lVar21);
                  }
                }
                else {
                  if (lVar8 == 0) {
                    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
                  }
                  memcpy(lVar8,&puStack_4c0,0x100);
                  param_4[1] = param_4[1] + 0x100;
                }
              }
            }
            puVar12 = auStack_3c0;
          }
          else {
            if ((*(byte *)(param_1 + 0x10) & 1) != 0) goto LAB_018e9244;
            iVar4 = strcmp(uVar15,&UNK_02a50598/*"."*/);
            if (iVar4 == 0) {
              snprintf(&uStack_2b0,0x100,&UNK_027f6a37/*"%s"*/,lVar8);
            }
            else {
              snprintf(&uStack_2b0,0x100,&UNK_02866ccf/*"%s/%s"*/,uVar15,lVar8);
            }
            Framework::CHash32::CHash32(char const*)(&uStack_3b0,&uStack_2b0);
            lVar22 = *(long *)(param_1 + 0x18);
            uVar5 = Framework::CHash32::operator unsigned int() const(&uStack_3b0);
            lVar8 = *(long *)(lVar22 + 0x20);
            uVar9 = *(ulong *)(lVar22 + 0x28);
            if (uVar9 != 0) {
              uVar19 = ~(ulong)uVar5 + (ulong)uVar5 * 0x200000;
              uVar19 = (uVar19 ^ uVar19 >> 0x18) * 0x109;
              uVar14 = (uVar19 ^ uVar19 >> 0xe) * 0x15;
              uVar19 = 0;
              do {
                uVar2 = (uVar14 ^ uVar14 >> 0x1c) * 0x80000001 + uVar19;
                uVar3 = 0;
                if (uVar9 != 0) {
                  uVar3 = uVar2 / uVar9;
                }
                lVar22 = uVar2 - uVar3 * uVar9;
                pcVar20 = (char *)(lVar8 + lVar22 * 0xc);
                if (*pcVar20 == '\x01') {
                  if (*(uint *)(lVar8 + lVar22 * 0xc + 4) == uVar5) goto LAB_018e8fc8;
                }
                else if (*pcVar20 == '\0') break;
                uVar19 = uVar19 + 1;
              } while (uVar19 < uVar9);
            }
            pcVar20 = (char *)(lVar8 + uVar9 * 0xc);
LAB_018e8fc8:
            lVar8 = *(long *)(param_1 + 0x18);
            if (pcVar20 == (char *)(*(long *)(lVar8 + 0x20) + *(long *)(lVar8 + 0x28) * 0xc)) {
              uVar6 = Framework::CHash32::operator unsigned int() const(&uStack_3b0);
              puStack_4c0 = (ulong *)CONCAT44(puStack_4c0._4_4_,uVar6);
              puVar11 = (undefined1 *)Aska::THashMap<unsigned int, bool, Aska::THasher<unsigned int>, Aska::TEqualTo<unsigned int>, Aska::TAllocator<Aska::TPair<unsigned int const, bool> > >::operator[](unsigned int const&)(lVar8,&puStack_4c0);
              *puVar11 = 1;
              lVar8 = param_4[1];
              if (lVar8 == param_4[2]) {
                uVar9 = lVar8 - *param_4 >> 8;
                if (uVar9 < 0x7fffffffffffff) {
                  uVar14 = lVar8 - *param_4 >> 7;
                  uVar19 = uVar9 + 1;
                  if (uVar9 + 1 <= uVar14) {
                    uVar19 = uVar14;
                  }
                  if (uVar19 != 0) goto LAB_018e918c;
                  lVar8 = 0;
                  lVar22 = uVar9 << 8;
                }
                else {
                  uVar19 = 0xffffffffffffff;
LAB_018e918c:
                  lVar8 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar19 << 8,&UNK_027dc536/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Vector.h"*/,0x20);
                  if (lVar8 == 0) {
                    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
                  }
                  lVar22 = lVar8 + uVar9 * 0x100;
                }
                if (lVar22 == 0) {
                  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
                }
                memcpy(lVar22,&uStack_2b0,0x100);
                lVar21 = *param_4;
                lVar23 = param_4[1];
                lVar16 = lVar22 + 0x100;
                if (lVar23 != lVar21) {
                  do {
                    lVar23 = lVar23 + -0x100;
                    memcpy(lVar22 + -0x100,lVar23,0x100);
                    lVar22 = lVar22 + -0x100;
                  } while (lVar21 != lVar23);
                  lVar21 = *param_4;
                }
                *param_4 = lVar22;
                param_4[1] = lVar16;
                param_4[2] = lVar8 + uVar19 * 0x100;
                if (lVar21 != 0) {
                  Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(lVar21);
                }
              }
              else {
                if (lVar8 == 0) {
                  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
                }
                memcpy(lVar8,&uStack_2b0,0x100);
                param_4[1] = param_4[1] + 0x100;
              }
            }
            puVar12 = &uStack_3b0;
          }
          Framework::CHash32::~CHash32()(puVar12);
        }
LAB_018e9244:
        lVar8 = fts_read(lVar7);
      } while (lVar8 != 0);
    }
    fts_close(lVar7);
    if ((uStack_1b0 & 1) != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(pcStack_1a0);
    }
    if ((uStack_190 & 1) != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_180);
    }
  }
  return;
}

// ==== FUN_018e88bc
// vaddr 0x17e88bc | ghidra 0x18e88bc | size 0 | symbol FUN_018e88bc | lib libSOA-3.7.0.so | 2026-10-04
void FUN_018e88bc(long *param_1,undefined8 param_2,undefined8 param_3,long *param_4)

{
  char *pcVar1;
  ulong uVar2;
  ulong uVar3;
  int iVar4;
  uint uVar5;
  undefined4 uVar6;
  long lVar7;
  long lVar8;
  ulong uVar9;
  undefined1 *puVar10;
  ulong *puVar11;
  ulong uVar12;
  long lVar13;
  char *pcVar14;
  char *pcVar15;
  ulong uVar16;
  char *pcVar17;
  long lVar18;
  long lVar19;
  long lVar20;
  ulong *puStack_4c0;
  undefined8 uStack_4b8;
  undefined8 uStack_4b0;
  ulong auStack_3c0 [2];
  ulong uStack_3b0;
  ulong uStack_3a8;
  ulong uStack_3a0;
  ulong uStack_2b0;
  ulong uStack_2a8;
  char *pcStack_2a0;
  ulong uStack_1b0;
  ulong uStack_1a8;
  char *pcStack_1a0;
  ulong uStack_190;
  ulong uStack_188;
  ulong uStack_180;
  undefined1 *puStack_178;
  undefined8 uStack_170;
  undefined1 auStack_168 [256];
  ulong *puStack_68;
  
  snprintf(auStack_168,0x100,&UNK_0282d96b/*"%s/"*/,param_2);
  uStack_170 = 0;
  puStack_178 = auStack_168;
  lVar7 = fts_open(&puStack_178,2,0);
  if (lVar7 != 0) {
    uStack_180 = 0;
    uStack_188 = 0;
    uStack_190 = 0;
    pcStack_1a0 = (char *)0x0;
    uStack_1a8 = 0;
    uStack_1b0 = 0;
    string::reserve(unsigned long)(&uStack_190,0x40);
    string::reserve(unsigned long)(&uStack_1b0,0x80);
    lVar8 = fts_read(lVar7);
    if (lVar8 != 0) {
      do {
        if (*(long *)(lVar8 + 0x48) != 0) {
          lVar19 = *(long *)(lVar8 + 0x28);
          if (lVar19 != 0) {
            uVar9 = strlen(lVar19);
            if ((uStack_1b0 & 1) == 0) {
              uVar12 = 0x16;
              lVar13 = uVar9 - 0x16;
              uVar16 = uStack_1b0 & 0xff;
              if (0x15 < uVar9 && lVar13 != 0) goto LAB_018e8a08;
LAB_018e89bc:
              pcVar17 = (char *)((ulong)&uStack_1b0 | 1);
              if ((uVar16 & 1) != 0) {
                pcVar17 = pcStack_1a0;
              }
              if (uVar9 != 0) {
                memmove(pcVar17,lVar19,uVar9);
              }
              pcVar17[uVar9] = '\0';
              if ((uStack_1b0 & 1) == 0) {
                uStack_1b0 = CONCAT71(uStack_1b0._1_7_,(char)(uVar9 << 1));
                uVar9 = uStack_1a8;
              }
            }
            else {
              uVar12 = (uStack_1b0 & 0xfffffffffffffffe) - 1;
              lVar13 = uVar9 - uVar12;
              uVar16 = uStack_1b0;
              if (uVar9 < uVar12 || lVar13 == 0) goto LAB_018e89bc;
LAB_018e8a08:
              uVar2 = (ulong)(((uint)uVar16 & 0xfe) >> 1);
              if ((uVar16 & 1) != 0) {
                uVar2 = uStack_1a8;
              }
              string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&uStack_1b0,uVar12,lVar13,uVar2,0,uVar2,uVar9,lVar19);
              uVar9 = uStack_1a8;
            }
            uStack_1a8 = uVar9;
            uStack_3a8 = 0;
            uStack_3a0 = 0;
            uStack_3b0 = 0;
            uVar9 = strlen(auStack_168);
            if (uVar9 < 0x17) {
              uStack_3b0 = CONCAT71(uStack_3b0._1_7_,(char)(uVar9 << 1));
              uVar12 = (ulong)&uStack_3b0 | 1;
              if (uVar9 != 0) goto LAB_018e8ad0;
            }
            else {
              uVar16 = uVar9 + 0x10 & 0xfffffffffffffff0;
              if (uVar16 == 0) {
                Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
              }
              uVar12 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar16,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
              if (uVar12 == 0) {
                Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
              }
              uStack_3b0 = uVar16 | 1;
              uStack_3a8 = uVar9;
              uStack_3a0 = uVar12;
LAB_018e8ad0:
              memcpy(uVar12,auStack_168,uVar9);
            }
            *(undefined1 *)(uVar12 + uVar9) = 0;
            uStack_4b8 = 0;
            uStack_4b0 = 0;
            puStack_4c0 = (ulong *)0x0;
            Framework::CSTLStringUtility_Base<string >::Replace(string const&, string const&, string const&, bool*)(&uStack_2b0,&uStack_1b0,&uStack_3b0,&puStack_4c0,0);
            if ((uStack_1b0 & 1) == 0) {
              uStack_1b0 = uStack_1b0 & 0xffffffffffff0000;
            }
            else {
              *pcStack_1a0 = '\0';
              uStack_1a8 = 0;
            }
            string::reserve(unsigned long)(&uStack_1b0,0);
            pcStack_1a0 = pcStack_2a0;
            uStack_1b0 = uStack_2b0;
            pcStack_2a0 = (char *)0x0;
            uStack_2b0 = 0;
            uStack_1a8 = uStack_2a8;
            uStack_2a8 = 0;
            if (((ulong)puStack_4c0 & 1) != 0) {
              Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_4b0);
            }
            if ((uStack_3b0 & 1) != 0) {
              Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_3a0);
            }
            pcVar17 = (char *)((ulong)&uStack_1b0 | 1);
            uVar9 = uStack_1b0 >> 1 & 0x7f;
            if ((uStack_1b0 & 1) != 0) {
              pcVar17 = pcStack_1a0;
              uVar9 = uStack_1a8;
            }
            if (uVar9 != 0) {
              pcVar1 = pcVar17 + uVar9;
              pcVar14 = pcVar17;
              pcVar15 = pcVar1;
              if (0 < (long)uVar9) {
                do {
                  pcVar15 = pcVar14;
                  if (*pcVar14 == '/') break;
                  uVar9 = uVar9 - 1;
                  pcVar14 = pcVar14 + 1;
                  pcVar15 = pcVar1;
                } while (uVar9 != 0);
              }
              if ((pcVar1 != pcVar15) && ((long)pcVar15 - (long)pcVar17 != -1)) goto LAB_018e9244;
            }
          }
          lVar8 = lVar8 + 0x78;
          uVar9 = strlen(lVar8);
          if ((uStack_190 & 1) == 0) {
            uVar12 = 0x16;
            lVar19 = uVar9 - 0x16;
            uVar16 = uStack_190 & 0xff;
            if (0x15 < uVar9 && lVar19 != 0) goto LAB_018e8c44;
LAB_018e8bf4:
            uVar12 = (ulong)&uStack_190 | 1;
            if ((uVar16 & 1) != 0) {
              uVar12 = uStack_180;
            }
            if (uVar9 != 0) {
              memmove(uVar12,lVar8,uVar9);
            }
            *(undefined1 *)(uVar12 + uVar9) = 0;
            if ((uStack_190 & 1) == 0) {
              uStack_190 = CONCAT71(uStack_190._1_7_,(char)(uVar9 << 1));
              uVar9 = uStack_188;
            }
          }
          else {
            uVar12 = (uStack_190 & 0xfffffffffffffffe) - 1;
            lVar19 = uVar9 - uVar12;
            uVar16 = uStack_190;
            if (uVar9 < uVar12 || lVar19 == 0) goto LAB_018e8bf4;
LAB_018e8c44:
            uVar2 = (ulong)(((uint)uVar16 & 0xfe) >> 1);
            if ((uVar16 & 1) != 0) {
              uVar2 = uStack_188;
            }
            string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&uStack_190,uVar12,lVar19,uVar2,0,uVar2,uVar9,lVar8);
            uVar9 = uStack_188;
          }
          uStack_188 = uVar9;
          uStack_3a8 = 0;
          uStack_3a0 = 0;
          uStack_3b0 = 0x2e02;
          Framework::CSTLStringUtility_Base<string >::GetExtension(string const&, string const&)(&uStack_2b0,&uStack_190,&uStack_3b0);
          uVar9 = uStack_2b0 >> 1 & 0x7f;
          if ((uStack_2b0 & 1) != 0) {
            uVar9 = uStack_2a8;
          }
          if ((uStack_2b0 & 1) != 0) {
            Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(pcStack_2a0);
          }
          if ((uStack_3b0 & 1) != 0) {
            Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_3a0);
          }
          if (uVar9 == 0) {
            iVar4 = strcmp(param_3,&UNK_02a50598/*"."*/);
            if (iVar4 == 0) {
              snprintf(&uStack_2b0,0x100,&UNK_027f6a37/*"%s"*/,lVar8);
            }
            else {
              snprintf(&uStack_2b0,0x100,&UNK_02866ccf/*"%s/%s"*/,param_3,lVar8);
            }
            snprintf(&uStack_3b0,0x100,&UNK_02866ccf/*"%s/%s"*/,param_2,lVar8);
            Framework::CHash32::CHash32(char const*)(auStack_3c0,&uStack_3b0);
            lVar19 = param_1[2];
            uVar5 = Framework::CHash32::operator unsigned int() const(auStack_3c0);
            lVar8 = *(long *)(lVar19 + 0x20);
            uVar9 = *(ulong *)(lVar19 + 0x28);
            if (uVar9 != 0) {
              uVar16 = ~(ulong)uVar5 + (ulong)uVar5 * 0x200000;
              uVar16 = (uVar16 ^ uVar16 >> 0x18) * 0x109;
              uVar12 = (uVar16 ^ uVar16 >> 0xe) * 0x15;
              uVar16 = 0;
              do {
                uVar2 = (uVar12 ^ uVar12 >> 0x1c) * 0x80000001 + uVar16;
                uVar3 = 0;
                if (uVar9 != 0) {
                  uVar3 = uVar2 / uVar9;
                }
                lVar19 = uVar2 - uVar3 * uVar9;
                pcVar17 = (char *)(lVar8 + lVar19 * 0xc);
                if (*pcVar17 == '\x01') {
                  if (*(uint *)(lVar8 + lVar19 * 0xc + 4) == uVar5) goto LAB_018e8e1c;
                }
                else if (*pcVar17 == '\0') break;
                uVar16 = uVar16 + 1;
              } while (uVar16 < uVar9);
            }
            pcVar17 = (char *)(lVar8 + uVar9 * 0xc);
LAB_018e8e1c:
            lVar8 = param_1[2];
            if (pcVar17 == (char *)(*(long *)(lVar8 + 0x20) + *(long *)(lVar8 + 0x28) * 0xc)) {
              uVar6 = Framework::CHash32::operator unsigned int() const(auStack_3c0);
              puStack_4c0 = (ulong *)CONCAT44(puStack_4c0._4_4_,uVar6);
              puVar10 = (undefined1 *)Aska::THashMap<unsigned int, bool, Aska::THasher<unsigned int>, Aska::TEqualTo<unsigned int>, Aska::TAllocator<Aska::TPair<unsigned int const, bool> > >::operator[](unsigned int const&)(lVar8,&puStack_4c0);
              *puVar10 = 1;
              if ((*(byte *)(param_1 + 1) & 1) == 0) {
                puStack_4c0 = &uStack_3b0;
                puStack_68 = &uStack_2b0;
                (**(code **)(**(long **)(*param_1 + 0x20) + 0x30))
                          (*(long **)(*param_1 + 0x20),&puStack_4c0,&puStack_68,param_4);
              }
              else {
                uVar9 = strlen(&uStack_3b0);
                if (0xff < uVar9) {
                  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dc32f/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/Utility.h"*/,0x77,&UNK_027dc380/*"gStrcpy() : destination buffer is small. ( %d < %d )"*/,uVar9,0x100);
                }
                strcpy(&puStack_4c0,&uStack_3b0);
                lVar8 = param_4[1];
                if (lVar8 == param_4[2]) {
                  uVar9 = lVar8 - *param_4 >> 8;
                  if (uVar9 < 0x7fffffffffffff) {
                    uVar12 = lVar8 - *param_4 >> 7;
                    uVar16 = uVar9 + 1;
                    if (uVar9 + 1 <= uVar12) {
                      uVar16 = uVar12;
                    }
                    if (uVar16 != 0) goto LAB_018e90c4;
                    lVar8 = 0;
                    lVar19 = uVar9 << 8;
                  }
                  else {
                    uVar16 = 0xffffffffffffff;
LAB_018e90c4:
                    lVar8 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar16 << 8,&UNK_027dc536/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Vector.h"*/,0x20);
                    if (lVar8 == 0) {
                      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
                      lVar19 = uVar9 * 0x100;
                    }
                    else {
                      lVar19 = lVar8 + uVar9 * 0x100;
                    }
                  }
                  if (lVar19 == 0) {
                    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
                  }
                  memcpy(lVar19,&puStack_4c0,0x100);
                  lVar18 = *param_4;
                  lVar20 = param_4[1];
                  lVar13 = lVar19 + 0x100;
                  if (lVar20 != lVar18) {
                    do {
                      lVar20 = lVar20 + -0x100;
                      memcpy(lVar19 + -0x100,lVar20,0x100);
                      lVar19 = lVar19 + -0x100;
                    } while (lVar18 != lVar20);
                    lVar18 = *param_4;
                  }
                  *param_4 = lVar19;
                  param_4[1] = lVar13;
                  param_4[2] = lVar8 + uVar16 * 0x100;
                  if (lVar18 != 0) {
                    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(lVar18);
                  }
                }
                else {
                  if (lVar8 == 0) {
                    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
                  }
                  memcpy(lVar8,&puStack_4c0,0x100);
                  param_4[1] = param_4[1] + 0x100;
                }
              }
            }
            puVar11 = auStack_3c0;
          }
          else {
            if ((*(byte *)(param_1 + 1) & 1) != 0) goto LAB_018e9244;
            iVar4 = strcmp(param_3,&UNK_02a50598/*"."*/);
            if (iVar4 == 0) {
              snprintf(&uStack_2b0,0x100,&UNK_027f6a37/*"%s"*/,lVar8);
            }
            else {
              snprintf(&uStack_2b0,0x100,&UNK_02866ccf/*"%s/%s"*/,param_3,lVar8);
            }
            Framework::CHash32::CHash32(char const*)(&uStack_3b0,&uStack_2b0);
            lVar19 = param_1[2];
            uVar5 = Framework::CHash32::operator unsigned int() const(&uStack_3b0);
            lVar8 = *(long *)(lVar19 + 0x20);
            uVar9 = *(ulong *)(lVar19 + 0x28);
            if (uVar9 != 0) {
              uVar16 = ~(ulong)uVar5 + (ulong)uVar5 * 0x200000;
              uVar16 = (uVar16 ^ uVar16 >> 0x18) * 0x109;
              uVar12 = (uVar16 ^ uVar16 >> 0xe) * 0x15;
              uVar16 = 0;
              do {
                uVar2 = (uVar12 ^ uVar12 >> 0x1c) * 0x80000001 + uVar16;
                uVar3 = 0;
                if (uVar9 != 0) {
                  uVar3 = uVar2 / uVar9;
                }
                lVar19 = uVar2 - uVar3 * uVar9;
                pcVar17 = (char *)(lVar8 + lVar19 * 0xc);
                if (*pcVar17 == '\x01') {
                  if (*(uint *)(lVar8 + lVar19 * 0xc + 4) == uVar5) goto LAB_018e8fc8;
                }
                else if (*pcVar17 == '\0') break;
                uVar16 = uVar16 + 1;
              } while (uVar16 < uVar9);
            }
            pcVar17 = (char *)(lVar8 + uVar9 * 0xc);
LAB_018e8fc8:
            lVar8 = param_1[2];
            if (pcVar17 == (char *)(*(long *)(lVar8 + 0x20) + *(long *)(lVar8 + 0x28) * 0xc)) {
              uVar6 = Framework::CHash32::operator unsigned int() const(&uStack_3b0);
              puStack_4c0 = (ulong *)CONCAT44(puStack_4c0._4_4_,uVar6);
              puVar10 = (undefined1 *)Aska::THashMap<unsigned int, bool, Aska::THasher<unsigned int>, Aska::TEqualTo<unsigned int>, Aska::TAllocator<Aska::TPair<unsigned int const, bool> > >::operator[](unsigned int const&)(lVar8,&puStack_4c0);
              *puVar10 = 1;
              lVar8 = param_4[1];
              if (lVar8 == param_4[2]) {
                uVar9 = lVar8 - *param_4 >> 8;
                if (uVar9 < 0x7fffffffffffff) {
                  uVar12 = lVar8 - *param_4 >> 7;
                  uVar16 = uVar9 + 1;
                  if (uVar9 + 1 <= uVar12) {
                    uVar16 = uVar12;
                  }
                  if (uVar16 != 0) goto LAB_018e918c;
                  lVar8 = 0;
                  lVar19 = uVar9 << 8;
                }
                else {
                  uVar16 = 0xffffffffffffff;
LAB_018e918c:
                  lVar8 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar16 << 8,&UNK_027dc536/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Vector.h"*/,0x20);
                  if (lVar8 == 0) {
                    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
                  }
                  lVar19 = lVar8 + uVar9 * 0x100;
                }
                if (lVar19 == 0) {
                  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
                }
                memcpy(lVar19,&uStack_2b0,0x100);
                lVar18 = *param_4;
                lVar20 = param_4[1];
                lVar13 = lVar19 + 0x100;
                if (lVar20 != lVar18) {
                  do {
                    lVar20 = lVar20 + -0x100;
                    memcpy(lVar19 + -0x100,lVar20,0x100);
                    lVar19 = lVar19 + -0x100;
                  } while (lVar18 != lVar20);
                  lVar18 = *param_4;
                }
                *param_4 = lVar19;
                param_4[1] = lVar13;
                param_4[2] = lVar8 + uVar16 * 0x100;
                if (lVar18 != 0) {
                  Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(lVar18);
                }
              }
              else {
                if (lVar8 == 0) {
                  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
                }
                memcpy(lVar8,&uStack_2b0,0x100);
                param_4[1] = param_4[1] + 0x100;
              }
            }
            puVar11 = &uStack_3b0;
          }
          Framework::CHash32::~CHash32()(puVar11);
        }
LAB_018e9244:
        lVar8 = fts_read(lVar7);
      } while (lVar8 != 0);
    }
    fts_close(lVar7);
    if ((uStack_1b0 & 1) != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(pcStack_1a0);
    }
    if ((uStack_190 & 1) != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_180);
    }
  }
  return;
}

// ==== Aska::THashMap<unsigned int, bool, Aska::THasher<unsigned int>, Aska::TEqualTo<unsigned int>, Aska::TAllocator<Aska::TPair<unsigned int const, bool> > >::operator[](unsigned int const&)
// vaddr 0x17e929c | ghidra 0x18e929c | size 320 | symbol _ZN4Aska8THashMapIjbNS_7THasherIjEENS_8TEqualToIjEENS_10TAllocatorINS_5TPairIKjbEEEEEixERS7_ | lib libSOA-3.7.0.so | 2026-10-04
char * _ZN4Aska8THashMapIjbNS_7THasherIjEENS_8TEqualToIjEENS_10TAllocatorINS_5TPairIKjbEEEEEixERS7_
                 (long param_1,uint *param_2)

{
  ulong uVar1;
  uint uVar2;
  char cVar3;
  ulong uVar4;
  ulong uVar5;
  char *pcVar6;
  ulong uVar7;
  long lVar8;
  ulong uVar9;
  char *pcVar10;
  long lVar11;
  
  uVar7 = *(ulong *)(param_1 + 0x28);
  uVar5 = (ulong)((float)((ulong)*(uint *)(param_1 + 0x10) + (ulong)*(uint *)(param_1 + 0x14) + 1) /
                 *(float *)(param_1 + 0xc));
  if (uVar7 < uVar5) {
    Aska::THashMap<unsigned int, bool, Aska::THasher<unsigned int>, Aska::TEqualTo<unsigned int>, Aska::TAllocator<Aska::TPair<unsigned int const, bool> > >::Rehash_(unsigned long)(param_1,uVar5 << 1 | 1);
    uVar7 = *(ulong *)(param_1 + 0x28);
  }
  lVar8 = *(long *)(param_1 + 0x20);
  if (uVar7 != 0) {
    uVar2 = *param_2;
    uVar5 = ~(ulong)uVar2 + (ulong)uVar2 * 0x200000;
    uVar5 = (uVar5 ^ uVar5 >> 0x18) * 0x109;
    uVar9 = (uVar5 ^ uVar5 >> 0xe) * 0x15;
    uVar5 = 0;
    pcVar6 = (char *)0x0;
    do {
      uVar1 = (uVar9 ^ uVar9 >> 0x1c) * 0x80000001 + uVar5;
      uVar4 = 0;
      if (uVar7 != 0) {
        uVar4 = uVar1 / uVar7;
      }
      lVar11 = uVar1 - uVar4 * uVar7;
      pcVar10 = (char *)(lVar8 + lVar11 * 0xc);
      cVar3 = *pcVar10;
      if (cVar3 == '\x01') {
        if (*(uint *)(lVar8 + lVar11 * 0xc + 4) == uVar2) goto code_r0x018e93c4;
      }
      else if (cVar3 == '\0') {
        if (pcVar6 != (char *)0x0) {
          pcVar10 = pcVar6;
        }
        if (pcVar10 == (char *)0x0) goto code_r0x018e93bc;
        goto code_r0x018e9378;
      }
      uVar5 = uVar5 + 1;
      if (cVar3 != '\x02' || pcVar6 != (char *)0x0) {
        pcVar10 = pcVar6;
      }
      pcVar6 = pcVar10;
    } while (uVar5 < uVar7);
    if (pcVar10 != (char *)0x0) {
code_r0x018e9378:
      *(uint *)(pcVar10 + 4) = uVar2;
      if (*pcVar10 == '\0') {
code_r0x018e9398:
        *(int *)(param_1 + 0x10) = *(int *)(param_1 + 0x10) + 1;
      }
      else if (*pcVar10 == '\x02') {
        *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + -1;
        goto code_r0x018e9398;
      }
      *pcVar10 = '\x01';
      goto code_r0x018e93c4;
    }
  }
code_r0x018e93bc:
  pcVar10 = (char *)(lVar8 + uVar7 * 0xc);
code_r0x018e93c4:
  return pcVar10 + 8;
}

// ==== Aska::THashMap<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> >, CAssetInfo, Hasher_CSTLString, Aska::TEqualTo<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > >, Aska::TAllocator<Aska::TPair<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > const, CAssetInfo> > >::Find_(std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > const&) const
// vaddr 0x17ea0d0 | ghidra 0x18ea0d0 | size 352 | symbol _ZNK4Aska8THashMapINSt6__ndk112basic_stringIcNS1_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS5_22CSTLStringAllocatorInfEEEEE10CAssetInfo17Hasher_CSTLStringNS_8TEqualToIS9_EENS_10TAllocatorINS_5TPairIKS9_SA_EEEEE5Find_ERSG_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK4Aska8THashMapINSt6__ndk112basic_stringIcNS1_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS5_22CSTLStringAllocatorInfEEEEE10CAssetInfo17Hasher_CSTLStringNS_8TEqualToIS9_EENS_10TAllocatorINS_5TPairIKS9_SA_EEEEE5Find_ERSG_
               (undefined8 *param_1,long param_2,byte *param_3)

{
  ulong uVar1;
  ulong uVar2;
  ulong uVar3;
  byte *pbVar4;
  byte bVar5;
  ulong uVar6;
  int iVar7;
  ulong uVar8;
  long lVar9;
  byte *pbVar10;
  long lVar11;
  byte *pbVar12;
  long lVar13;
  ulong uVar14;
  char *pcVar15;
  char *pcVar16;
  undefined1 auStack_70 [16];
  
  lVar13 = *(long *)(param_2 + 0x20);
  uVar3 = *(ulong *)(param_2 + 0x28);
  Framework::CHash32::CHash32(string const&)(auStack_70);
  uVar8 = Framework::CHash32::operator unsigned int() const(auStack_70);
  Framework::CHash32::~CHash32()(auStack_70);
  if (uVar3 != 0) {
    uVar2 = *(ulong *)(param_3 + 8);
    pbVar4 = *(byte **)(param_3 + 0x10);
    uVar14 = 0;
    if ((*param_3 & 1) == 0) {
      pbVar4 = param_3 + 1;
      uVar2 = (ulong)(*param_3 >> 1);
    }
    do {
      uVar1 = uVar14 + (uVar8 & 0xffffffff);
      uVar6 = 0;
      if (uVar3 != 0) {
        uVar6 = uVar1 / uVar3;
      }
      lVar11 = uVar1 - uVar6 * uVar3;
      pcVar15 = (char *)(lVar13 + lVar11 * 0xc0);
      if (*pcVar15 == '\x01') {
        lVar9 = lVar13 + lVar11 * 0xc0;
        bVar5 = *(byte *)(lVar9 + 8);
        uVar1 = (ulong)(bVar5 >> 1);
        if ((bVar5 & 1) != 0) {
          uVar1 = *(ulong *)(lVar9 + 0x10);
        }
        if (uVar1 == uVar2) {
          lVar11 = *(long *)(lVar13 + lVar11 * 0xc0 + 0x18);
          if ((bVar5 & 1) == 0) {
            lVar11 = lVar9 + 9;
          }
          if ((bVar5 & 1) == 0) {
            if (uVar2 == 0) {
code_r0x018ea200:
              pcVar16 = (char *)(lVar13 + uVar3 * 0xc0);
              goto code_r0x018ea208;
            }
            pbVar10 = (byte *)(lVar9 + 9);
            lVar11 = -(ulong)(bVar5 >> 1);
            pbVar12 = pbVar4;
            while (*pbVar10 == *pbVar12) {
              pbVar10 = pbVar10 + 1;
              lVar11 = lVar11 + 1;
              pbVar12 = pbVar12 + 1;
              if (lVar11 == 0) goto code_r0x018ea200;
            }
          }
          else if ((uVar2 == 0) || (iVar7 = memcmp(lVar11,pbVar4,uVar2), iVar7 == 0))
          goto code_r0x018ea200;
        }
      }
      else if (*pcVar15 == '\0') break;
      uVar14 = uVar14 + 1;
    } while (uVar14 < uVar3);
  }
  lVar13 = *(long *)(param_2 + 0x20);
  pcVar16 = (char *)(lVar13 + *(long *)(param_2 + 0x28) * 0xc0);
  pcVar15 = pcVar16;
code_r0x018ea208:
  *param_1 = pcVar15;
  param_1[1] = lVar13;
  param_1[2] = pcVar16;
  return;
}

// ==== Aska::THashMap<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> >, CAssetInfo, Hasher_CSTLString, Aska::TEqualTo<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > >, Aska::TAllocator<Aska::TPair<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > const, CAssetInfo> > >::Rehash_(unsigned long)
// vaddr 0x17f52c8 | ghidra 0x18f52c8 | size 572 | symbol _ZN4Aska8THashMapINSt6__ndk112basic_stringIcNS1_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS5_22CSTLStringAllocatorInfEEEEE10CAssetInfo17Hasher_CSTLStringNS_8TEqualToIS9_EENS_10TAllocatorINS_5TPairIKS9_SA_EEEEE7Rehash_Em | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska8THashMapINSt6__ndk112basic_stringIcNS1_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS5_22CSTLStringAllocatorInfEEEEE10CAssetInfo17Hasher_CSTLStringNS_8TEqualToIS9_EENS_10TAllocatorINS_5TPairIKS9_SA_EEEEE7Rehash_Em
               (undefined1 *param_1,ulong param_2)

{
  ulong uVar1;
  undefined *puVar2;
  undefined1 *puVar3;
  undefined1 *puVar4;
  undefined8 uVar5;
  char *pcVar6;
  ulong uVar7;
  long lVar8;
  ulong uVar9;
  float fVar10;
  float fVar11;
  undefined *puStack_90;
  float fStack_84;
  undefined4 uStack_80;
  undefined4 uStack_7c;
  undefined1 *puStack_70;
  ulong uStack_68;
  char *pcStack_60;
  char *pcStack_58;
  char *pcStack_50;
  char *pcStack_48;
  char *pcStack_40;
  char *pcStack_38;
  
  puVar2 = 
  PTR__ZTVN4Aska8THashMapINSt6__ndk112basic_stringIcNS1_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS5_22CSTLStringAllocatorInfEEEEE10CAssetInfo17Hasher_CSTLStringNS_8TEqualToIS9_EENS_10TAllocatorINS_5TPairIKS9_SA_EEEEEE_02cc2290
  ;
  puStack_90 = PTR__ZTVN4Aska8THashMapINSt6__ndk112basic_stringIcNS1_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS5_22CSTLStringAllocatorInfEEEEE10CAssetInfo17Hasher_CSTLStringNS_8TEqualToIS9_EENS_10TAllocatorINS_5TPairIKS9_SA_EEEEEE_02cc2290
               + 0x10;
  fStack_84 = 0.75;
  uStack_80 = 0;
  uStack_7c = 0;
  if (param_2 < 0x155555555555556) {
    puStack_70 = (undefined1 *)Aska::MemoryManagerAdapter::AlignedMalloc(unsigned long, unsigned long)(param_2 * 0xc0,8);
  }
  else {
    puStack_70 = (undefined1 *)0x0;
  }
  if (puStack_70 == (undefined1 *)0x0) {
    param_2 = 0;
  }
  if (param_2 == 0) {
    fVar10 = *(float *)(param_1 + 0xc);
code_r0x018f53e0:
    if (fVar10 <= 0.0) goto code_r0x018f53f0;
  }
  else {
    uVar1 = (param_2 * 0xc0 - 0xc0) / 0xc0 + 1;
    puVar3 = puStack_70;
    if ((uVar1 < 2) || (uVar7 = uVar1 & 0x3fffffffffffffe, uVar7 == 0)) {
code_r0x018f5398:
      do {
        puVar4 = puVar3 + 0xc0;
        *puVar3 = 0;
        puVar3 = puVar4;
      } while (puStack_70 + param_2 * 0xc0 != puVar4);
    }
    else {
      puVar3 = puStack_70 + uVar7 * 0xc0;
      uVar9 = uVar7;
      puVar4 = puStack_70;
      do {
        *puVar4 = 0;
        puVar4[0xc0] = 0;
        uVar9 = uVar9 - 2;
        puVar4 = puVar4 + 0x180;
      } while (uVar9 != 0);
      if (uVar1 != uVar7) goto code_r0x018f5398;
    }
    fVar10 = *(float *)(param_1 + 0xc);
    if (param_2 == 0) goto code_r0x018f53e0;
    fVar11 = (float)NEON_ucvtf(uStack_80);
    if (fVar10 <= fVar11 / (float)param_2) goto code_r0x018f53f0;
  }
  fStack_84 = fVar10;
code_r0x018f53f0:
  pcStack_58 = *(char **)(param_1 + 0x20);
  lVar8 = *(long *)(param_1 + 0x28);
  pcStack_60 = pcStack_58 + lVar8 * 0xc0;
  pcStack_48 = pcStack_60;
  if ((*(int *)(param_1 + 0x10) != 0) && (pcStack_48 = pcStack_58, lVar8 != 0)) {
    lVar8 = lVar8 * 0xc0;
    pcVar6 = pcStack_58;
    do {
      pcStack_48 = pcVar6;
      if (*pcVar6 == '\x01') break;
      lVar8 = lVar8 + -0xc0;
      pcVar6 = pcVar6 + 0xc0;
      pcStack_48 = pcStack_60;
    } while (lVar8 != 0);
  }
  uStack_68 = param_2;
  pcStack_50 = pcStack_60;
  pcStack_40 = pcStack_58;
  pcStack_38 = pcStack_60;
  void Aska::THashMap<string, CAssetInfo, Hasher_CSTLString, Aska::TEqualTo<string >, Aska::TAllocator<Aska::TPair<string const, CAssetInfo> > >::Insert<Aska::THashMapIterator<Aska::detail::THashMapBucketArray<Aska::detail::THashMapBucket<Aska::TPair<string const, CAssetInfo> >, Aska::TAllocator<Aska::detail::THashMapBucket<Aska::TPair<string const, CAssetInfo> > > > > >(Aska::THashMapIterator<Aska::detail::THashMapBucketArray<Aska::detail::THashMapBucket<Aska::TPair<string const, CAssetInfo> >, Aska::TAllocator<Aska::detail::THashMapBucket<Aska::TPair<string const, CAssetInfo> > > > >, Aska::THashMapIterator<Aska::detail::THashMapBucketArray<Aska::detail::THashMapBucket<Aska::TPair<string const, CAssetInfo> >, Aska::TAllocator<Aska::detail::THashMapBucket<Aska::TPair<string const, CAssetInfo> > > > >)(&puStack_90,&pcStack_48,&pcStack_60);
  if (&puStack_90 != (undefined **)param_1) {
    uVar5 = *(undefined8 *)(param_1 + 0x10);
    *(ulong *)(param_1 + 0x10) = CONCAT44(uStack_7c,uStack_80);
    uStack_80 = (undefined4)uVar5;
    uStack_7c = (undefined4)((ulong)uVar5 >> 0x20);
    puVar3 = *(undefined1 **)(param_1 + 0x20);
    uVar1 = *(ulong *)(param_1 + 0x28);
    *(ulong *)(param_1 + 0x28) = uStack_68;
    *(undefined1 **)(param_1 + 0x20) = puStack_70;
    fVar10 = *(float *)(param_1 + 0xc);
    *(float *)(param_1 + 0xc) = fStack_84;
    fStack_84 = fVar10;
    puStack_70 = puVar3;
    uStack_68 = uVar1;
  }
  puStack_90 = puVar2 + 0x10;
  if (puStack_70 != (undefined1 *)0x0) {
    if (uStack_68 != 0) {
      puVar3 = puStack_70 + 8;
      lVar8 = uStack_68 * 0xc0;
      do {
        if (puVar3[-8] == '\x01') {
          Aska::TPair<string const, CAssetInfo>::~TPair()(puVar3);
        }
        lVar8 = lVar8 + -0xc0;
        puVar3 = puVar3 + 0xc0;
      } while (lVar8 != 0);
    }
    Aska::MemoryManagerAdapter::AlignedFree(void*)(puStack_70);
  }
  return;
}

// ==== void Aska::THashMap<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> >, CAssetInfo, Hasher_CSTLString, Aska::TEqualTo<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > >, Aska::TAllocator<Aska::TPair<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > const, CAssetInfo> > >::Insert<Aska::THashMapIterator<Aska::detail::THashMapBucketArray<Aska::detail::THashMapBucket<Aska::TPair<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > const, CAssetInfo> >, Aska::TAllocator<Aska::detail::THashMapBucket<Aska::TPair<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > const, CAssetInfo> > > > > >(Aska::THashMapIterator<Aska::detail::THashMapBucketArray<Aska::detail::THashMapBucket<Aska::TPair<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > const, CAssetInfo> >, Aska::TAllocator<Aska::detail::THashMapBucket<Aska::TPair<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > const, CAssetInfo> > > > >, Aska::THashMapIterator<Aska::detail::THashMapBucketArray<Aska::detail::THashMapBucket<Aska::TPair<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > const, CAssetInfo> >, Aska::TAllocator<Aska::detail::THashMapBucket<Aska::TPair<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > const, CAssetInfo> > > > >)
// vaddr 0x17f5504 | ghidra 0x18f5504 | size 256 | symbol _ZN4Aska8THashMapINSt6__ndk112basic_stringIcNS1_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS5_22CSTLStringAllocatorInfEEEEE10CAssetInfo17Hasher_CSTLStringNS_8TEqualToIS9_EENS_10TAllocatorINS_5TPairIKS9_SA_EEEEE6InsertINS_16THashMapIteratorINS_6detail19THashMapBucketArrayINSM_14THashMapBucketISH_EENSE_ISP_EEEEEEEEvT_ST_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska8THashMapINSt6__ndk112basic_stringIcNS1_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS5_22CSTLStringAllocatorInfEEEEE10CAssetInfo17Hasher_CSTLStringNS_8TEqualToIS9_EENS_10TAllocatorINS_5TPairIKS9_SA_EEEEE6InsertINS_16THashMapIteratorINS_6detail19THashMapBucketArrayINSM_14THashMapBucketISH_EENSE_ISP_EEEEEEEEvT_ST_
               (long param_1,long *param_2,undefined8 *param_3)

{
  char *pcVar1;
  char *pcVar2;
  char *pcVar3;
  long lVar4;
  ulong uVar5;
  char *pcVar6;
  undefined1 auStack_40 [32];
  
  pcVar2 = (char *)*param_2;
  pcVar3 = (char *)*param_3;
  lVar4 = 0;
  if (pcVar2 != pcVar3) {
    pcVar6 = pcVar2;
    do {
      lVar4 = lVar4 + 1;
      do {
        pcVar1 = (char *)param_2[2];
        if ((char *)param_2[2] == pcVar6) break;
        pcVar6 = pcVar6 + 0xc0;
        pcVar1 = pcVar6;
      } while (*pcVar6 != '\x01');
      pcVar6 = pcVar1;
    } while (pcVar6 != pcVar3);
  }
  uVar5 = (ulong)((float)(lVar4 + (ulong)*(uint *)(param_1 + 0x10) +
                         (ulong)*(uint *)(param_1 + 0x14)) / *(float *)(param_1 + 0xc));
  if (uVar5 <= *(ulong *)(param_1 + 0x28)) goto code_r0x018f55a8;
  Aska::THashMap<string, CAssetInfo, Hasher_CSTLString, Aska::TEqualTo<string >, Aska::TAllocator<Aska::TPair<string const, CAssetInfo> > >::Rehash_(unsigned long)(param_1,uVar5 << 1 | 1);
  pcVar2 = (char *)*param_2;
  do {
    pcVar3 = (char *)*param_3;
code_r0x018f55a8:
    if (pcVar2 == pcVar3) {
      return;
    }
    Aska::THashMap<string, CAssetInfo, Hasher_CSTLString, Aska::TEqualTo<string >, Aska::TAllocator<Aska::TPair<string const, CAssetInfo> > >::Insert_(Aska::TPair<string const, CAssetInfo> const&)(auStack_40,param_1,pcVar2 + 8);
    pcVar3 = (char *)*param_2;
    do {
      pcVar2 = (char *)param_2[2];
      if ((char *)param_2[2] == pcVar3) break;
      pcVar2 = pcVar3 + 0xc0;
      *param_2 = (long)pcVar2;
      pcVar6 = pcVar3 + 0xc0;
      pcVar3 = pcVar2;
    } while (*pcVar6 != '\x01');
  } while( true );
}

// ==== Aska::THashMap<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> >, CAssetInfo, Hasher_CSTLString, Aska::TEqualTo<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > >, Aska::TAllocator<Aska::TPair<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > const, CAssetInfo> > >::Insert_(Aska::TPair<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > const, CAssetInfo> const&)
// vaddr 0x17f5604 | ghidra 0x18f5604 | size 492 | symbol _ZN4Aska8THashMapINSt6__ndk112basic_stringIcNS1_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS5_22CSTLStringAllocatorInfEEEEE10CAssetInfo17Hasher_CSTLStringNS_8TEqualToIS9_EENS_10TAllocatorINS_5TPairIKS9_SA_EEEEE7Insert_ERKSH_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska8THashMapINSt6__ndk112basic_stringIcNS1_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS5_22CSTLStringAllocatorInfEEEEE10CAssetInfo17Hasher_CSTLStringNS_8TEqualToIS9_EENS_10TAllocatorINS_5TPairIKS9_SA_EEEEE7Insert_ERKSH_
               (undefined8 *param_1,long param_2,byte *param_3)

{
  ulong uVar1;
  ulong uVar2;
  ulong uVar3;
  byte *pbVar4;
  byte bVar5;
  char cVar6;
  ulong uVar7;
  int iVar8;
  ulong uVar9;
  undefined1 uVar10;
  long lVar11;
  byte *pbVar12;
  long lVar13;
  byte *pbVar14;
  char *pcVar15;
  long lVar16;
  char *pcVar17;
  ulong uVar18;
  undefined1 auStack_70 [16];
  
  lVar16 = *(long *)(param_2 + 0x20);
  uVar3 = *(ulong *)(param_2 + 0x28);
  Framework::CHash32::CHash32(string const&)(auStack_70);
  uVar9 = Framework::CHash32::operator unsigned int() const(auStack_70);
  Framework::CHash32::~CHash32()(auStack_70);
  if (uVar3 != 0) {
    uVar2 = *(ulong *)(param_3 + 8);
    pbVar4 = *(byte **)(param_3 + 0x10);
    pcVar17 = (char *)0x0;
    uVar18 = 0;
    if ((*param_3 & 1) == 0) {
      pbVar4 = param_3 + 1;
      uVar2 = (ulong)(*param_3 >> 1);
    }
    do {
      uVar1 = uVar18 + (uVar9 & 0xffffffff);
      uVar7 = 0;
      if (uVar3 != 0) {
        uVar7 = uVar1 / uVar3;
      }
      lVar13 = uVar1 - uVar7 * uVar3;
      pcVar15 = (char *)(lVar16 + lVar13 * 0xc0);
      cVar6 = *pcVar15;
      if (cVar6 == '\x01') {
        lVar11 = lVar16 + lVar13 * 0xc0;
        bVar5 = *(byte *)(lVar11 + 8);
        uVar1 = (ulong)(bVar5 >> 1);
        if ((bVar5 & 1) != 0) {
          uVar1 = *(ulong *)(lVar11 + 0x10);
        }
        if (uVar1 == uVar2) {
          lVar13 = *(long *)(lVar16 + lVar13 * 0xc0 + 0x18);
          if ((bVar5 & 1) == 0) {
            lVar13 = lVar11 + 9;
          }
          if ((bVar5 & 1) == 0) {
            if (uVar2 == 0) {
code_r0x018f5788:
              uVar10 = 0;
              pcVar17 = (char *)(lVar16 + uVar3 * 0xc0);
              goto code_r0x018f57c4;
            }
            pbVar12 = (byte *)(lVar11 + 9);
            lVar13 = -(ulong)(bVar5 >> 1);
            pbVar14 = pbVar4;
            while (*pbVar12 == *pbVar14) {
              pbVar12 = pbVar12 + 1;
              lVar13 = lVar13 + 1;
              pbVar14 = pbVar14 + 1;
              if (lVar13 == 0) goto code_r0x018f5788;
            }
          }
          else if ((uVar2 == 0) || (iVar8 = memcmp(lVar13,pbVar4,uVar2), iVar8 == 0))
          goto code_r0x018f5788;
        }
      }
      else if (cVar6 == '\0') {
        if (pcVar17 != (char *)0x0) {
          pcVar15 = pcVar17;
        }
        break;
      }
      uVar18 = uVar18 + 1;
      if (cVar6 != '\x02' || pcVar17 != (char *)0x0) {
        pcVar15 = pcVar17;
      }
      pcVar17 = pcVar15;
    } while (uVar18 < uVar3);
    if (pcVar15 != (char *)0x0) {
      Aska::TPair<string const, CAssetInfo>::TPair(Aska::TPair<string const, CAssetInfo> const&)(pcVar15 + 8,param_3);
      if (*pcVar15 == '\0') {
code_r0x018f5764:
        *(int *)(param_2 + 0x10) = *(int *)(param_2 + 0x10) + 1;
      }
      else if (*pcVar15 == '\x02') {
        *(int *)(param_2 + 0x14) = *(int *)(param_2 + 0x14) + -1;
        goto code_r0x018f5764;
      }
      uVar10 = 1;
      *pcVar15 = '\x01';
      pcVar17 = (char *)(lVar16 + *(long *)(param_2 + 0x28) * 0xc0);
      goto code_r0x018f57c4;
    }
  }
  lVar16 = *(long *)(param_2 + 0x20);
  uVar10 = 0;
  pcVar17 = (char *)(lVar16 + *(long *)(param_2 + 0x28) * 0xc0);
  pcVar15 = pcVar17;
code_r0x018f57c4:
  *param_1 = pcVar15;
  param_1[1] = lVar16;
  param_1[2] = pcVar17;
  *(undefined1 *)(param_1 + 3) = uVar10;
  return;
}

// ==== Aska::TPair<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > const, CAssetInfo>::TPair(Aska::TPair<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > const, CAssetInfo> const&)
// vaddr 0x17f57f0 | ghidra 0x18f57f0 | size 240 | symbol _ZN4Aska5TPairIKNSt6__ndk112basic_stringIcNS1_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS5_22CSTLStringAllocatorInfEEEEE10CAssetInfoEC2ERKSC_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5TPairIKNSt6__ndk112basic_stringIcNS1_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS5_22CSTLStringAllocatorInfEEEEE10CAssetInfoEC2ERKSC_
               (ulong *param_1,ulong *param_2)

{
  ulong uVar1;
  ulong uVar2;
  ulong uVar3;
  ulong uVar4;
  
  param_1[1] = 0;
  param_1[2] = 0;
  *param_1 = 0;
  if ((*param_2 & 1) == 0) {
    param_1[2] = param_2[2];
    uVar4 = *param_2;
    param_1[1] = param_2[1];
    *param_1 = uVar4;
    goto code_r0x011e8b80;
  }
  uVar4 = param_2[1];
  uVar1 = param_2[2];
  if (uVar4 < 0x17) {
    uVar2 = (long)param_1 + 1;
    *(char *)param_1 = (char)(uVar4 << 1);
    if (uVar4 != 0) goto code_r0x018f58b0;
  }
  else {
    uVar3 = uVar4 + 0x10 & 0xfffffffffffffff0;
    if (uVar3 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
    }
    uVar2 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar3,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
    if (uVar2 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    }
    param_1[1] = uVar4;
    param_1[2] = uVar2;
    *param_1 = uVar3 | 1;
code_r0x018f58b0:
    memcpy(uVar2,uVar1,uVar4);
  }
  *(undefined1 *)(uVar2 + uVar4) = 0;
code_r0x011e8b80:
  (*(code *)PTR__ZN10CAssetInfoC2ERKS__02cac5b0)(param_1 + 3,param_2 + 3);
  return;
}

// ==== Aska::THashMap<unsigned int, Framework::TStaticString<256ul>, Aska::THasher<unsigned int>, Aska::TEqualTo<unsigned int>, Aska::TAllocator<Aska::TPair<unsigned int const, Framework::TStaticString<256ul> > > >::operator[](unsigned int const&)
// vaddr 0x17f9964 | ghidra 0x18f9964 | size 324 | symbol _ZN4Aska8THashMapIjN9Framework13TStaticStringILm256EEENS_7THasherIjEENS_8TEqualToIjEENS_10TAllocatorINS_5TPairIKjS3_EEEEEixERSA_ | lib libSOA-3.7.0.so | 2026-10-04
char * _ZN4Aska8THashMapIjN9Framework13TStaticStringILm256EEENS_7THasherIjEENS_8TEqualToIjEENS_10TAllocatorINS_5TPairIKjS3_EEEEEixERSA_
                 (long param_1,uint *param_2)

{
  ulong uVar1;
  uint uVar2;
  char cVar3;
  ulong uVar4;
  ulong uVar5;
  char *pcVar6;
  ulong uVar7;
  long lVar8;
  ulong uVar9;
  char *pcVar10;
  long lVar11;
  
  uVar7 = *(ulong *)(param_1 + 0x28);
  uVar5 = (ulong)((float)((ulong)*(uint *)(param_1 + 0x10) + (ulong)*(uint *)(param_1 + 0x14) + 1) /
                 *(float *)(param_1 + 0xc));
  if (uVar7 < uVar5) {
    Aska::THashMap<unsigned int, Framework::TStaticString<256ul>, Aska::THasher<unsigned int>, Aska::TEqualTo<unsigned int>, Aska::TAllocator<Aska::TPair<unsigned int const, Framework::TStaticString<256ul> > > >::Rehash_(unsigned long)(param_1,uVar5 << 1 | 1);
    uVar7 = *(ulong *)(param_1 + 0x28);
  }
  lVar8 = *(long *)(param_1 + 0x20);
  if (uVar7 != 0) {
    uVar2 = *param_2;
    uVar5 = ~(ulong)uVar2 + (ulong)uVar2 * 0x200000;
    uVar5 = (uVar5 ^ uVar5 >> 0x18) * 0x109;
    uVar9 = (uVar5 ^ uVar5 >> 0xe) * 0x15;
    uVar5 = 0;
    pcVar6 = (char *)0x0;
    do {
      uVar1 = (uVar9 ^ uVar9 >> 0x1c) * 0x80000001 + uVar5;
      uVar4 = 0;
      if (uVar7 != 0) {
        uVar4 = uVar1 / uVar7;
      }
      lVar11 = uVar1 - uVar4 * uVar7;
      pcVar10 = (char *)(lVar8 + lVar11 * 0x108);
      cVar3 = *pcVar10;
      if (cVar3 == '\x01') {
        if (*(uint *)(lVar8 + lVar11 * 0x108 + 4) == uVar2) goto code_r0x018f9a90;
      }
      else if (cVar3 == '\0') {
        if (pcVar6 != (char *)0x0) {
          pcVar10 = pcVar6;
        }
        if (pcVar10 == (char *)0x0) goto code_r0x018f9a88;
        goto code_r0x018f9a40;
      }
      uVar5 = uVar5 + 1;
      if (cVar3 != '\x02' || pcVar6 != (char *)0x0) {
        pcVar10 = pcVar6;
      }
      pcVar6 = pcVar10;
    } while (uVar5 < uVar7);
    if (pcVar10 != (char *)0x0) {
code_r0x018f9a40:
      *(uint *)(pcVar10 + 4) = uVar2;
      pcVar10[8] = '\0';
      if (*pcVar10 == '\0') {
code_r0x018f9a64:
        *(int *)(param_1 + 0x10) = *(int *)(param_1 + 0x10) + 1;
      }
      else if (*pcVar10 == '\x02') {
        *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + -1;
        goto code_r0x018f9a64;
      }
      *pcVar10 = '\x01';
      goto code_r0x018f9a90;
    }
  }
code_r0x018f9a88:
  pcVar10 = (char *)(lVar8 + uVar7 * 0x108);
code_r0x018f9a90:
  return pcVar10 + 8;
}

// ==== FUN_018fa010
// vaddr 0x17fa010 | ghidra 0x18fa010 | size 0 | symbol FUN_018fa010 | lib libSOA-3.7.0.so | 2026-10-04
void FUN_018fa010(undefined8 param_1,undefined8 *param_2)

{
  *param_2 = &UNK_02b10f08;
  return;
}

// ==== FUN_018fa024
// vaddr 0x17fa024 | ghidra 0x18fa024 | size 0 | symbol FUN_018fa024 | lib libSOA-3.7.0.so | 2026-10-04
void FUN_018fa024(void)

{
  return;
}

// ==== Aska::THashMap<unsigned int, Framework::TStaticString<256ul>, Aska::THasher<unsigned int>, Aska::TEqualTo<unsigned int>, Aska::TAllocator<Aska::TPair<unsigned int const, Framework::TStaticString<256ul> > > >::Rehash_(unsigned long)
// vaddr 0x17fa0bc | ghidra 0x18fa0bc | size 536 | symbol _ZN4Aska8THashMapIjN9Framework13TStaticStringILm256EEENS_7THasherIjEENS_8TEqualToIjEENS_10TAllocatorINS_5TPairIKjS3_EEEEE7Rehash_Em | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska8THashMapIjN9Framework13TStaticStringILm256EEENS_7THasherIjEENS_8TEqualToIjEENS_10TAllocatorINS_5TPairIKjS3_EEEEE7Rehash_Em
               (undefined1 *param_1,ulong param_2)

{
  ulong uVar1;
  undefined *puVar2;
  undefined1 *puVar3;
  undefined8 uVar4;
  char *pcVar5;
  ulong uVar6;
  long lVar7;
  ulong uVar8;
  undefined1 *puVar9;
  float fVar10;
  float fVar11;
  undefined *puStack_90;
  float fStack_84;
  undefined4 uStack_80;
  undefined4 uStack_7c;
  undefined1 *puStack_70;
  ulong uStack_68;
  char *pcStack_60;
  char *pcStack_58;
  char *pcStack_50;
  char *pcStack_48;
  char *pcStack_40;
  char *pcStack_38;
  
  puVar2 = 
  PTR__ZTVN4Aska8THashMapIjN9Framework13TStaticStringILm256EEENS_7THasherIjEENS_8TEqualToIjEENS_10TAllocatorINS_5TPairIKjS3_EEEEEE_02cba4e8
  ;
  puStack_90 = PTR__ZTVN4Aska8THashMapIjN9Framework13TStaticStringILm256EEENS_7THasherIjEENS_8TEqualToIjEENS_10TAllocatorINS_5TPairIKjS3_EEEEEE_02cba4e8
               + 0x10;
  fStack_84 = 0.75;
  uStack_80 = 0;
  uStack_7c = 0;
  if (param_2 < 0xf83e0f83e0f83f) {
    puStack_70 = (undefined1 *)Aska::MemoryManagerAdapter::AlignedMalloc(unsigned long, unsigned long)(param_2 * 0x108,4);
  }
  else {
    puStack_70 = (undefined1 *)0x0;
  }
  if (puStack_70 == (undefined1 *)0x0) {
    param_2 = 0;
  }
  if (param_2 == 0) {
    fVar10 = *(float *)(param_1 + 0xc);
code_r0x018fa1e8:
    if (fVar10 <= 0.0) goto code_r0x018fa1f8;
  }
  else {
    uVar1 = (param_2 * 0x108 - 0x108) / 0x108 + 1;
    puVar3 = puStack_70;
    if ((uVar1 < 2) || (uVar6 = uVar1 & 0x1fffffffffffffe, uVar6 == 0)) {
code_r0x018fa19c:
      do {
        *puVar3 = 0;
        puVar3 = puVar3 + 0x108;
      } while (puStack_70 + param_2 * 0x108 != puVar3);
    }
    else {
      puVar3 = puStack_70 + uVar6 * 0x108;
      uVar8 = uVar6;
      puVar9 = puStack_70;
      do {
        *puVar9 = 0;
        puVar9[0x108] = 0;
        uVar8 = uVar8 - 2;
        puVar9 = puVar9 + 0x210;
      } while (uVar8 != 0);
      if (uVar1 != uVar6) goto code_r0x018fa19c;
    }
    fVar10 = *(float *)(param_1 + 0xc);
    if (param_2 == 0) goto code_r0x018fa1e8;
    fVar11 = (float)NEON_ucvtf(uStack_80);
    if (fVar10 <= fVar11 / (float)param_2) goto code_r0x018fa1f8;
  }
  fStack_84 = fVar10;
code_r0x018fa1f8:
  pcStack_58 = *(char **)(param_1 + 0x20);
  lVar7 = *(long *)(param_1 + 0x28);
  pcStack_60 = pcStack_58 + lVar7 * 0x108;
  pcStack_48 = pcStack_60;
  if ((*(int *)(param_1 + 0x10) != 0) && (pcStack_48 = pcStack_58, lVar7 != 0)) {
    lVar7 = lVar7 * 0x108;
    pcVar5 = pcStack_58;
    do {
      pcStack_48 = pcVar5;
      if (*pcVar5 == '\x01') break;
      lVar7 = lVar7 + -0x108;
      pcVar5 = pcVar5 + 0x108;
      pcStack_48 = pcStack_60;
    } while (lVar7 != 0);
  }
  uStack_68 = param_2;
  pcStack_50 = pcStack_60;
  pcStack_40 = pcStack_58;
  pcStack_38 = pcStack_60;
  void Aska::THashMap<unsigned int, Framework::TStaticString<256ul>, Aska::THasher<unsigned int>, Aska::TEqualTo<unsigned int>, Aska::TAllocator<Aska::TPair<unsigned int const, Framework::TStaticString<256ul> > > >::Insert<Aska::THashMapIterator<Aska::detail::THashMapBucketArray<Aska::detail::THashMapBucket<Aska::TPair<unsigned int const, Framework::TStaticString<256ul> > >, Aska::TAllocator<Aska::detail::THashMapBucket<Aska::TPair<unsigned int const, Framework::TStaticString<256ul> > > > > > >(Aska::THashMapIterator<Aska::detail::THashMapBucketArray<Aska::detail::THashMapBucket<Aska::TPair<unsigned int const, Framework::TStaticString<256ul> > >, Aska::TAllocator<Aska::detail::THashMapBucket<Aska::TPair<unsigned int const, Framework::TStaticString<256ul> > > > > >, Aska::THashMapIterator<Aska::detail::THashMapBucketArray<Aska::detail::THashMapBucket<Aska::TPair<unsigned int const, Framework::TStaticString<256ul> > >, Aska::TAllocator<Aska::detail::THashMapBucket<Aska::TPair<unsigned int const, Framework::TStaticString<256ul> > > > > >)(&puStack_90,&pcStack_48,&pcStack_60);
  if (&puStack_90 != (undefined **)param_1) {
    uVar4 = *(undefined8 *)(param_1 + 0x10);
    *(ulong *)(param_1 + 0x10) = CONCAT44(uStack_7c,uStack_80);
    uStack_80 = (undefined4)uVar4;
    uStack_7c = (undefined4)((ulong)uVar4 >> 0x20);
    puVar3 = *(undefined1 **)(param_1 + 0x20);
    uVar1 = *(ulong *)(param_1 + 0x28);
    *(ulong *)(param_1 + 0x28) = uStack_68;
    *(undefined1 **)(param_1 + 0x20) = puStack_70;
    fVar10 = *(float *)(param_1 + 0xc);
    *(float *)(param_1 + 0xc) = fStack_84;
    fStack_84 = fVar10;
    puStack_70 = puVar3;
    uStack_68 = uVar1;
  }
  puStack_90 = puVar2 + 0x10;
  if (puStack_70 != (undefined1 *)0x0) {
    Aska::MemoryManagerAdapter::AlignedFree(void*)();
  }
  return;
}

// ==== void Aska::THashMap<unsigned int, Framework::TStaticString<256ul>, Aska::THasher<unsigned int>, Aska::TEqualTo<unsigned int>, Aska::TAllocator<Aska::TPair<unsigned int const, Framework::TStaticString<256ul> > > >::Insert<Aska::THashMapIterator<Aska::detail::THashMapBucketArray<Aska::detail::THashMapBucket<Aska::TPair<unsigned int const, Framework::TStaticString<256ul> > >, Aska::TAllocator<Aska::detail::THashMapBucket<Aska::TPair<unsigned int const, Framework::TStaticString<256ul> > > > > > >(Aska::THashMapIterator<Aska::detail::THashMapBucketArray<Aska::detail::THashMapBucket<Aska::TPair<unsigned int const, Framework::TStaticString<256ul> > >, Aska::TAllocator<Aska::detail::THashMapBucket<Aska::TPair<unsigned int const, Framework::TStaticString<256ul> > > > > >, Aska::THashMapIterator<Aska::detail::THashMapBucketArray<Aska::detail::THashMapBucket<Aska::TPair<unsigned int const, Framework::TStaticString<256ul> > >, Aska::TAllocator<Aska::detail::THashMapBucket<Aska::TPair<unsigned int const, Framework::TStaticString<256ul> > > > > >)
// vaddr 0x17fa2d4 | ghidra 0x18fa2d4 | size 512 | symbol _ZN4Aska8THashMapIjN9Framework13TStaticStringILm256EEENS_7THasherIjEENS_8TEqualToIjEENS_10TAllocatorINS_5TPairIKjS3_EEEEE6InsertINS_16THashMapIteratorINS_6detail19THashMapBucketArrayINSG_14THashMapBucketISB_EENS8_ISJ_EEEEEEEEvT_SN_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska8THashMapIjN9Framework13TStaticStringILm256EEENS_7THasherIjEENS_8TEqualToIjEENS_10TAllocatorINS_5TPairIKjS3_EEEEE6InsertINS_16THashMapIteratorINS_6detail19THashMapBucketArrayINSG_14THashMapBucketISB_EENS8_ISJ_EEEEEEEEvT_SN_
               (long param_1,long *param_2,long *param_3)

{
  ulong uVar1;
  uint uVar2;
  char cVar3;
  ulong uVar4;
  long lVar5;
  long lVar6;
  long lVar7;
  long lVar8;
  ulong uVar9;
  ulong uVar10;
  long lVar11;
  ulong uVar12;
  char *pcVar13;
  char *pcVar14;
  
  lVar6 = *param_2;
  lVar7 = *param_3;
  lVar8 = 0;
  if (lVar6 != lVar7) {
    lVar11 = lVar6;
    do {
      lVar8 = lVar8 + 1;
      do {
        lVar5 = param_2[2];
        if (param_2[2] == lVar11) break;
        pcVar14 = (char *)(lVar11 + 0x108);
        lVar11 = lVar11 + 0x108;
        lVar5 = lVar11;
      } while (*pcVar14 != '\x01');
      lVar11 = lVar5;
    } while (lVar11 != lVar7);
  }
  uVar9 = (ulong)((float)(lVar8 + (ulong)*(uint *)(param_1 + 0x10) +
                         (ulong)*(uint *)(param_1 + 0x14)) / *(float *)(param_1 + 0xc));
  if (*(ulong *)(param_1 + 0x28) < uVar9) {
    Aska::THashMap<unsigned int, Framework::TStaticString<256ul>, Aska::THasher<unsigned int>, Aska::TEqualTo<unsigned int>, Aska::TAllocator<Aska::TPair<unsigned int const, Framework::TStaticString<256ul> > > >::Rehash_(unsigned long)(param_1,uVar9 << 1 | 1);
    lVar6 = *param_2;
    lVar7 = *param_3;
  }
  if (lVar6 != lVar7) {
    do {
      uVar9 = *(ulong *)(param_1 + 0x28);
      if (uVar9 != 0) {
        uVar2 = *(uint *)(lVar6 + 4);
        uVar10 = 0;
        uVar12 = ~(ulong)uVar2 + (ulong)uVar2 * 0x200000;
        uVar12 = (uVar12 ^ uVar12 >> 0x18) * 0x109;
        uVar12 = (uVar12 ^ uVar12 >> 0xe) * 0x15;
        pcVar14 = (char *)0x0;
        do {
          uVar1 = (uVar12 ^ uVar12 >> 0x1c) * 0x80000001 + uVar10;
          uVar4 = 0;
          if (uVar9 != 0) {
            uVar4 = uVar1 / uVar9;
          }
          lVar8 = uVar1 - uVar4 * uVar9;
          pcVar13 = (char *)(*(long *)(param_1 + 0x20) + lVar8 * 0x108);
          cVar3 = *pcVar13;
          if (cVar3 == '\x01') {
            if (*(uint *)(*(long *)(param_1 + 0x20) + lVar8 * 0x108 + 4) == uVar2)
            goto code_r0x018fa480;
          }
          else if (cVar3 == '\0') {
            if (pcVar14 != (char *)0x0) {
              pcVar13 = pcVar14;
            }
            break;
          }
          uVar10 = uVar10 + 1;
          if (cVar3 != '\x02' || pcVar14 != (char *)0x0) {
            pcVar13 = pcVar14;
          }
          pcVar14 = pcVar13;
        } while (uVar10 < uVar9);
        if (pcVar13 != (char *)0x0) {
          *(uint *)(pcVar13 + 4) = uVar2;
          memcpy(pcVar13 + 8,lVar6 + 8,0x100);
          if (*pcVar13 == '\0') {
code_r0x018fa46c:
            *(int *)(param_1 + 0x10) = *(int *)(param_1 + 0x10) + 1;
          }
          else if (*pcVar13 == '\x02') {
            *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + -1;
            goto code_r0x018fa46c;
          }
          *pcVar13 = '\x01';
          lVar6 = *param_2;
        }
      }
code_r0x018fa480:
      lVar8 = lVar6;
      do {
        lVar6 = param_2[2];
        if (param_2[2] == lVar8) break;
        lVar6 = lVar8 + 0x108;
        *param_2 = lVar6;
        pcVar14 = (char *)(lVar8 + 0x108);
        lVar8 = lVar6;
      } while (*pcVar14 != '\x01');
    } while (lVar6 != *param_3);
  }
  return;
}

// ==== Aska::THashMap<unsigned int, unsigned long, Aska::THasher<unsigned int>, Aska::TEqualTo<unsigned int>, Aska::TAllocator<Aska::TPair<unsigned int const, unsigned long> > >::operator[](unsigned int const&)
// vaddr 0x1e84c08 | ghidra 0x1f84c08 | size 320 | symbol _ZN4Aska8THashMapIjmNS_7THasherIjEENS_8TEqualToIjEENS_10TAllocatorINS_5TPairIKjmEEEEEixERS7_ | lib libSOA-3.7.0.so | 2026-10-04
char * _ZN4Aska8THashMapIjmNS_7THasherIjEENS_8TEqualToIjEENS_10TAllocatorINS_5TPairIKjmEEEEEixERS7_
                 (long param_1,uint *param_2)

{
  ulong uVar1;
  uint uVar2;
  char cVar3;
  ulong uVar4;
  ulong uVar5;
  char *pcVar6;
  ulong uVar7;
  long lVar8;
  ulong uVar9;
  char *pcVar10;
  long lVar11;
  
  uVar7 = *(ulong *)(param_1 + 0x28);
  uVar5 = (ulong)((float)((ulong)*(uint *)(param_1 + 0x10) + (ulong)*(uint *)(param_1 + 0x14) + 1) /
                 *(float *)(param_1 + 0xc));
  if (uVar7 < uVar5) {
    Aska::THashMap<unsigned int, unsigned long, Aska::THasher<unsigned int>, Aska::TEqualTo<unsigned int>, Aska::TAllocator<Aska::TPair<unsigned int const, unsigned long> > >::Rehash_(unsigned long)(param_1,uVar5 << 1 | 1);
    uVar7 = *(ulong *)(param_1 + 0x28);
  }
  lVar8 = *(long *)(param_1 + 0x20);
  if (uVar7 != 0) {
    uVar2 = *param_2;
    uVar5 = ~(ulong)uVar2 + (ulong)uVar2 * 0x200000;
    uVar5 = (uVar5 ^ uVar5 >> 0x18) * 0x109;
    uVar9 = (uVar5 ^ uVar5 >> 0xe) * 0x15;
    uVar5 = 0;
    pcVar6 = (char *)0x0;
    do {
      uVar1 = (uVar9 ^ uVar9 >> 0x1c) * 0x80000001 + uVar5;
      uVar4 = 0;
      if (uVar7 != 0) {
        uVar4 = uVar1 / uVar7;
      }
      lVar11 = uVar1 - uVar4 * uVar7;
      pcVar10 = (char *)(lVar8 + lVar11 * 0x18);
      cVar3 = *pcVar10;
      if (cVar3 == '\x01') {
        if (*(uint *)(lVar8 + lVar11 * 0x18 + 8) == uVar2) goto code_r0x01f84d30;
      }
      else if (cVar3 == '\0') {
        if (pcVar6 != (char *)0x0) {
          pcVar10 = pcVar6;
        }
        if (pcVar10 == (char *)0x0) goto code_r0x01f84d28;
        goto code_r0x01f84ce4;
      }
      uVar5 = uVar5 + 1;
      if (cVar3 != '\x02' || pcVar6 != (char *)0x0) {
        pcVar10 = pcVar6;
      }
      pcVar6 = pcVar10;
    } while (uVar5 < uVar7);
    if (pcVar10 != (char *)0x0) {
code_r0x01f84ce4:
      *(uint *)(pcVar10 + 8) = uVar2;
      if (*pcVar10 == '\0') {
code_r0x01f84d04:
        *(int *)(param_1 + 0x10) = *(int *)(param_1 + 0x10) + 1;
      }
      else if (*pcVar10 == '\x02') {
        *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + -1;
        goto code_r0x01f84d04;
      }
      *pcVar10 = '\x01';
      goto code_r0x01f84d30;
    }
  }
code_r0x01f84d28:
  pcVar10 = (char *)(lVar8 + uVar7 * 0x18);
code_r0x01f84d30:
  return pcVar10 + 0x10;
}

// ==== Aska::TCategorizeHash<Aska::MappedMemoryPointer>::Regist(void const*, unsigned int)
// vaddr 0x1f2a1e4 | ghidra 0x202a1e4 | size 384 | symbol _ZN4Aska15TCategorizeHashINS_19MappedMemoryPointerEE6RegistEPKvj | lib libSOA-3.7.0.so | 2026-10-04
long * _ZN4Aska15TCategorizeHashINS_19MappedMemoryPointerEE6RegistEPKvj
                 (long *param_1,undefined8 param_2,uint param_3)

{
  int iVar1;
  long *plVar2;
  long lVar3;
  long *plVar4;
  long *plVar5;
  ulong uVar6;
  long *plVar7;
  
  uVar6 = (ulong)param_3;
  if (*(uint *)(param_1 + 0xb) <= param_3) {
    uVar6 = 0;
  }
  plVar4 = (long *)(param_1[10] + uVar6 * 8);
  param_1[0xc] = (long)plVar4;
  plVar2 = (long *)*plVar4;
  while (plVar2 != (long *)0x0) {
    while (iVar1 = (**(code **)(*plVar2 + 0x20))(plVar2,param_2), -1 < iVar1) {
      if (iVar1 == 0) goto code_r0x0202a274;
      plVar4 = (long *)(*plVar4 + 0x20);
      plVar2 = (long *)*plVar4;
      if (plVar2 == (long *)0x0) goto code_r0x0202a258;
    }
    plVar4 = (long *)(*plVar4 + 0x18);
    plVar2 = (long *)*plVar4;
  }
code_r0x0202a258:
  lVar3 = (**(code **)(*param_1 + 0x10))(param_1,param_2);
  *plVar4 = lVar3;
  plVar2 = (long *)0x0;
  if (lVar3 != 0) {
code_r0x0202a274:
    if ((plVar4 == (long *)0x0) || (plVar7 = (long *)*plVar4, plVar7 == (long *)0x0)) {
      plVar2 = (long *)0x0;
    }
    else {
      iVar1 = (**(code **)(*plVar7 + 0x38))(plVar7,param_2);
      while (0 < iVar1) {
        plVar2 = (long *)plVar7[9];
        if (plVar2 == (long *)0x0) {
          plVar4 = (long *)(**(code **)(*param_1 + 0x10))(param_1,param_2);
          if (plVar4 == (long *)0x0) {
            return (long *)0x0;
          }
          plVar4[8] = (long)plVar7;
          plVar7[9] = (long)plVar4;
          return plVar4;
        }
        iVar1 = (**(code **)(*plVar2 + 0x38))(plVar2,param_2);
        plVar7 = plVar2;
      }
      plVar2 = plVar7;
      if ((iVar1 < 0) &&
         (plVar2 = (long *)(**(code **)(*param_1 + 0x10))(param_1,param_2), plVar2 != (long *)0x0))
      {
        plVar2[3] = plVar7[3];
        plVar2[4] = plVar7[4];
        lVar3 = plVar7[8];
        plVar7[3] = 0;
        plVar7[4] = 0;
        plVar2[8] = lVar3;
        plVar2[9] = (long)plVar7;
        plVar5 = plVar7;
        if (lVar3 != 0) {
          *(long **)(lVar3 + 0x48) = plVar2;
          plVar5 = (long *)plVar2[9];
        }
        plVar5[8] = (long)plVar2;
        if ((long *)*plVar4 == plVar7) {
          *plVar4 = (long)plVar2;
        }
      }
    }
  }
  return plVar2;
}

// ==== Aska::THash<Aska::AUIDNode>::Regist(void const*, unsigned int)
// vaddr 0x1f2ec98 | ghidra 0x202ec98 | size 168 | symbol _ZN4Aska5THashINS_8AUIDNodeEE6RegistEPKvj | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska5THashINS_8AUIDNodeEE6RegistEPKvj(long *param_1,undefined8 param_2,uint param_3)

{
  int iVar1;
  long *plVar2;
  long lVar3;
  long lVar4;
  ulong uVar5;
  long *plVar6;
  
  uVar5 = (ulong)param_3;
  if (*(uint *)(param_1 + 0xb) <= param_3) {
    uVar5 = 0;
  }
  plVar6 = (long *)(param_1[10] + uVar5 * 8);
  param_1[0xc] = (long)plVar6;
  plVar2 = (long *)*plVar6;
  while (plVar2 != (long *)0x0) {
    while (iVar1 = (**(code **)(*plVar2 + 0x20))(plVar2,param_2), -1 < iVar1) {
      if (iVar1 == 0) goto code_r0x0202ed24;
      plVar6 = (long *)(*plVar6 + 0x20);
      plVar2 = (long *)*plVar6;
      if (plVar2 == (long *)0x0) goto code_r0x0202ed08;
    }
    plVar6 = (long *)(*plVar6 + 0x18);
    plVar2 = (long *)*plVar6;
  }
code_r0x0202ed08:
  lVar3 = (**(code **)(*param_1 + 0x10))(param_1,param_2);
  *plVar6 = lVar3;
  lVar4 = 0;
  if (lVar3 != 0) {
code_r0x0202ed24:
    if (plVar6 == (long *)0x0) {
      lVar4 = 0;
    }
    else {
      lVar4 = *plVar6;
    }
  }
  return lVar4;
}

// ==== Aska::TCategorizeHash<Aska::MappedMemoryPointer>::FreeNode(Aska::MappedMemoryPointer**)
// vaddr 0x1f2f08c | ghidra 0x202f08c | size 484 | symbol _ZN4Aska15TCategorizeHashINS_19MappedMemoryPointerEE8FreeNodeEPPS1_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska15TCategorizeHashINS_19MappedMemoryPointerEE8FreeNodeEPPS1_
               (long *param_1,ulong *param_2)

{
  long lVar1;
  char cVar2;
  long *plVar3;
  ulong uVar4;
  long *plVar5;
  long lVar6;
  
  uVar4 = *param_2;
  if (uVar4 != 0) {
    if (param_1[0xe] == uVar4) {
      param_1[0xe] = *(long *)(uVar4 + 0x10);
      uVar4 = *param_2;
    }
    if (param_1[0xf] == uVar4) {
      param_1[0xf] = *(long *)(uVar4 + 8);
      uVar4 = *param_2;
    }
    if (param_1[0x10] == uVar4) {
      param_1[0x10] = *(long *)(uVar4 + 8);
      cVar2 = (char)param_1[0x11];
    }
    else {
      cVar2 = (char)param_1[0x11];
    }
    if ((cVar2 == '\0') && (param_1[0x12] == *param_2)) {
      *(undefined4 *)(param_1 + 0x13) = 0;
      param_1[0x12] = 0;
      param_1[0x10] = 0;
      *(undefined1 *)(param_1 + 0x11) = 0;
    }
    lVar6 = *(long *)(*param_2 + 8);
    lVar1 = *(long *)(*param_2 + 0x10);
    if (lVar6 != 0) {
      *(long *)(lVar6 + 0x10) = lVar1;
    }
    if (lVar1 != 0) {
      *(undefined8 *)(lVar1 + 8) = *(undefined8 *)(*param_2 + 8);
    }
    *(undefined8 *)(*param_2 + 0x10) = 0;
    *(undefined8 *)(*param_2 + 8) = 0;
    plVar3 = (long *)*param_2;
    if (plVar3[9] != 0) {
      (**(code **)(*param_1 + 0x18))(param_1);
      plVar3 = (long *)*param_2;
    }
    if (plVar3[4] != 0) {
      (**(code **)(*param_1 + 0x18))(param_1);
      plVar3 = (long *)*param_2;
    }
    if (plVar3[3] != 0) {
      (**(code **)(*param_1 + 0x18))(param_1);
      plVar3 = (long *)*param_2;
    }
    (**(code **)(*plVar3 + 0x18))();
    *(int *)((long)param_1 + 0x8c) = *(int *)((long)param_1 + 0x8c) + -1;
    plVar5 = (long *)param_1[8];
    plVar3 = (long *)*param_2;
    if (((plVar5 == (long *)0x0) || (plVar3 < plVar5)) ||
       (plVar5 + (ulong)*(uint *)((long)param_1 + 0x2c) * 10 <= plVar3)) {
      if (plVar3 != (long *)0x0) {
        (**(code **)(*plVar3 + 8))();
      }
    }
    else {
      uVar4 = ((long)plVar3 - (long)plVar5 >> 4) * -0x3333333333333333;
      (**(code **)plVar5[(uVar4 & 0xffffffff) * 10])();
      lVar6 = (uVar4 >> 5 & 0x7ffffff) * 4;
      *(uint *)(param_1[4] + lVar6) =
           *(uint *)(param_1[4] + lVar6) & (1 << (ulong)((uint)uVar4 & 0x1f) ^ 0xffffffffU);
      *(int *)((long)param_1 + 0x3c) = *(int *)((long)param_1 + 0x3c) + -1;
    }
    *param_2 = 0;
  }
  return;
}

// ==== Aska::TCategorizeHash<Aska::MappedMemoryPointer>::Remove(Aska::MappedMemoryPointer**)
// vaddr 0x1f2f360 | ghidra 0x202f360 | size 232 | symbol _ZN4Aska15TCategorizeHashINS_19MappedMemoryPointerEE6RemoveEPPS1_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska15TCategorizeHashINS_19MappedMemoryPointerEE6RemoveEPPS1_(long *param_1,long *param_2)

{
  long *plVar1;
  long *plVar2;
  long lVar3;
  long lStack_8;
  
  lStack_8 = *param_2;
  if (lStack_8 == 0) {
    return;
  }
  if (*(long *)(lStack_8 + 0x48) == 0) {
    if (*(long *)(lStack_8 + 0x40) != 0) {
      *param_2 = *(long *)(lStack_8 + 0x40);
      *(undefined8 *)(*(long *)(lStack_8 + 0x40) + 0x48) = 0;
      *(undefined8 *)(lStack_8 + 0x40) = 0;
      goto code_r0x0202f3d4;
    }
    lVar3 = *(long *)(lStack_8 + 0x18);
    if (*(long *)(lStack_8 + 0x20) == 0) {
      *param_2 = lVar3;
      *(undefined8 *)(lStack_8 + 0x18) = 0;
      goto code_r0x0202f3d4;
    }
    plVar1 = (long *)(lStack_8 + 0x18);
    if (lVar3 != 0) {
      do {
        plVar2 = plVar1;
        lVar3 = *plVar2;
        plVar1 = (long *)(lVar3 + 0x20);
      } while (*(long *)(lVar3 + 0x20) != 0);
      *plVar2 = *(long *)(lVar3 + 0x18);
      *(undefined8 *)(lVar3 + 0x18) = *(undefined8 *)(lStack_8 + 0x18);
      *(undefined8 *)(lVar3 + 0x20) = *(undefined8 *)(lStack_8 + 0x20);
      *param_2 = lVar3;
      goto code_r0x0202f3b0;
    }
    *param_2 = *(long *)(lStack_8 + 0x20);
  }
  else {
    *param_2 = *(long *)(lStack_8 + 0x48);
    *(undefined8 *)(*(long *)(lStack_8 + 0x48) + 0x40) = *(undefined8 *)(lStack_8 + 0x40);
    if (*(long *)(lStack_8 + 0x40) != 0) {
      *(undefined8 *)(*(long *)(lStack_8 + 0x40) + 0x48) = *(undefined8 *)(lStack_8 + 0x48);
    }
    *(undefined8 *)(*(long *)(lStack_8 + 0x48) + 0x18) = *(undefined8 *)(lStack_8 + 0x18);
    *(undefined8 *)(*(long *)(lStack_8 + 0x48) + 0x20) = *(undefined8 *)(lStack_8 + 0x20);
    *(undefined8 *)(lStack_8 + 0x40) = 0;
    *(undefined8 *)(lStack_8 + 0x48) = 0;
code_r0x0202f3b0:
    *(undefined8 *)(lStack_8 + 0x18) = 0;
  }
  *(undefined8 *)(lStack_8 + 0x20) = 0;
code_r0x0202f3d4:
  (**(code **)(*param_1 + 0x18))(param_1,&lStack_8);
  return;
}

// ==== Aska::TCategorizeHash<Aska::MappedMemoryPointer>::Search(void const*, unsigned int)
// vaddr 0x1f2f554 | ghidra 0x202f554 | size 180 | symbol _ZN4Aska15TCategorizeHashINS_19MappedMemoryPointerEE6SearchEPKvj | lib libSOA-3.7.0.so | 2026-10-04
long * _ZN4Aska15TCategorizeHashINS_19MappedMemoryPointerEE6SearchEPKvj
                 (long param_1,undefined8 param_2,uint param_3)

{
  int iVar1;
  long *plVar2;
  ulong uVar3;
  long *plVar4;
  
  uVar3 = (ulong)param_3;
  if (*(uint *)(param_1 + 0x58) <= param_3) {
    uVar3 = 0;
  }
  plVar4 = (long *)(*(long *)(param_1 + 0x50) + uVar3 * 8);
  plVar2 = (long *)*plVar4;
  while( true ) {
    while( true ) {
      if (plVar2 == (long *)0x0) {
        return (long *)0x0;
      }
      iVar1 = (**(code **)(*plVar2 + 0x20))(plVar2,param_2);
      if (-1 < iVar1) break;
      plVar4 = (long *)(*plVar4 + 0x18);
      plVar2 = (long *)*plVar4;
    }
    if (iVar1 == 0) break;
    plVar4 = (long *)(*plVar4 + 0x20);
    plVar2 = (long *)*plVar4;
  }
  plVar4 = (long *)*plVar4;
  while( true ) {
    if (plVar4 == (long *)0x0) {
      return (long *)0x0;
    }
    iVar1 = (**(code **)(*plVar4 + 0x38))(plVar4,param_2);
    if (iVar1 == 0) break;
    if (iVar1 < 1) {
      return (long *)0x0;
    }
    plVar4 = (long *)plVar4[9];
  }
  return plVar4;
}

// ==== Aska::THash<Aska::MappedMemoryRelation>::Regist(void const*)
// vaddr 0x1f2fa58 | ghidra 0x202fa58 | size 64 | symbol _ZN4Aska5THashINS_20MappedMemoryRelationEE6RegistEPKv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5THashINS_20MappedMemoryRelationEE6RegistEPKv(long *param_1,undefined8 param_2)

{
  code *UNRECOVERED_JUMPTABLE;
  undefined4 uVar1;
  
  UNRECOVERED_JUMPTABLE = *(code **)(*param_1 + 0x68);
  uVar1 = (**(code **)(*param_1 + 0x60))(param_1);
                    /* WARNING: Could not recover jumptable at 0x0202fa94. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*UNRECOVERED_JUMPTABLE)(param_1,param_2,uVar1);
  return;
}

// ==== Aska::THash<Aska::MappedMemoryRelation>::Remove(Aska::MappedMemoryRelation**)
// vaddr 0x1f2fa98 | ghidra 0x202fa98 | size 140 | symbol _ZN4Aska5THashINS_20MappedMemoryRelationEE6RemoveEPPS1_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5THashINS_20MappedMemoryRelationEE6RemoveEPPS1_(long *param_1,long *param_2)

{
  long *plVar1;
  long *plVar2;
  long *plVar3;
  long lVar4;
  long *plVar5;
  long lStack_8;
  
  lStack_8 = *param_2;
  if (lStack_8 != 0) {
    plVar2 = (long *)(lStack_8 + 0x20);
    plVar3 = (long *)(lStack_8 + 0x18);
    if (*plVar2 == 0) {
      *param_2 = *plVar3;
      plVar2 = plVar3;
    }
    else {
      plVar1 = plVar3;
      if (*plVar3 == 0) {
        *param_2 = *plVar2;
      }
      else {
        do {
          plVar5 = plVar1;
          lVar4 = *plVar5;
          plVar1 = (long *)(lVar4 + 0x20);
        } while (*(long *)(lVar4 + 0x20) != 0);
        *plVar5 = *(long *)(lVar4 + 0x18);
        *(long *)(lVar4 + 0x18) = *plVar3;
        *(long *)(lVar4 + 0x20) = *plVar2;
        *param_2 = lVar4;
        *plVar3 = 0;
      }
    }
    *plVar2 = 0;
    (**(code **)(*param_1 + 0x18))(param_1,&lStack_8);
  }
  return;
}

// ==== Aska::THash<Aska::MappedMemoryRelation>::Regist(void const*, unsigned int)
// vaddr 0x1f2fb68 | ghidra 0x202fb68 | size 168 | symbol _ZN4Aska5THashINS_20MappedMemoryRelationEE6RegistEPKvj | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska5THashINS_20MappedMemoryRelationEE6RegistEPKvj
               (long *param_1,undefined8 param_2,uint param_3)

{
  int iVar1;
  long *plVar2;
  long lVar3;
  long lVar4;
  ulong uVar5;
  long *plVar6;
  
  uVar5 = (ulong)param_3;
  if (*(uint *)(param_1 + 0xb) <= param_3) {
    uVar5 = 0;
  }
  plVar6 = (long *)(param_1[10] + uVar5 * 8);
  param_1[0xc] = (long)plVar6;
  plVar2 = (long *)*plVar6;
  while (plVar2 != (long *)0x0) {
    while (iVar1 = (**(code **)(*plVar2 + 0x20))(plVar2,param_2), -1 < iVar1) {
      if (iVar1 == 0) goto code_r0x0202fbf4;
      plVar6 = (long *)(*plVar6 + 0x20);
      plVar2 = (long *)*plVar6;
      if (plVar2 == (long *)0x0) goto code_r0x0202fbd8;
    }
    plVar6 = (long *)(*plVar6 + 0x18);
    plVar2 = (long *)*plVar6;
  }
code_r0x0202fbd8:
  lVar3 = (**(code **)(*param_1 + 0x10))(param_1,param_2);
  *plVar6 = lVar3;
  lVar4 = 0;
  if (lVar3 != 0) {
code_r0x0202fbf4:
    if (plVar6 == (long *)0x0) {
      lVar4 = 0;
    }
    else {
      lVar4 = *plVar6;
    }
  }
  return lVar4;
}

// ==== Aska::THash<Aska::MappedMemoryRelation>::Remove(void const*, unsigned int)
// vaddr 0x1f2fc10 | ghidra 0x202fc10 | size 140 | symbol _ZN4Aska5THashINS_20MappedMemoryRelationEE6RemoveEPKvj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5THashINS_20MappedMemoryRelationEE6RemoveEPKvj
               (long *param_1,undefined8 param_2,uint param_3)

{
  int iVar1;
  long *plVar2;
  ulong uVar3;
  long *plVar4;
  
  uVar3 = (ulong)param_3;
  if (*(uint *)(param_1 + 0xb) <= param_3) {
    uVar3 = 0;
  }
  plVar4 = (long *)(param_1[10] + uVar3 * 8);
  param_1[0xc] = (long)plVar4;
  plVar2 = (long *)*plVar4;
  while (plVar2 != (long *)0x0) {
    while (iVar1 = (**(code **)(*plVar2 + 0x20))(plVar2,param_2), -1 < iVar1) {
      if (iVar1 == 0) goto code_r0x0202fc80;
      plVar4 = (long *)(*plVar4 + 0x20);
      plVar2 = (long *)*plVar4;
      if (plVar2 == (long *)0x0) goto code_r0x0202fc80;
    }
    plVar4 = (long *)(*plVar4 + 0x18);
    plVar2 = (long *)*plVar4;
  }
code_r0x0202fc80:
                    /* WARNING: Could not recover jumptable at 0x0202fc98. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*param_1 + 0x40))(param_1,plVar4);
  return;
}

// ==== Aska::THash<Aska::MappedMemoryRelation>::Search(void const*, unsigned int)
// vaddr 0x1f2fd20 | ghidra 0x202fd20 | size 124 | symbol _ZN4Aska5THashINS_20MappedMemoryRelationEE6SearchEPKvj | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska5THashINS_20MappedMemoryRelationEE6SearchEPKvj
               (long param_1,undefined8 param_2,uint param_3)

{
  int iVar1;
  long *plVar2;
  ulong uVar3;
  long *plVar4;
  
  uVar3 = (ulong)param_3;
  if (*(uint *)(param_1 + 0x58) <= param_3) {
    uVar3 = 0;
  }
  plVar4 = (long *)(*(long *)(param_1 + 0x50) + uVar3 * 8);
  plVar2 = (long *)*plVar4;
  do {
    if (plVar2 == (long *)0x0) {
      return 0;
    }
    while (iVar1 = (**(code **)(*plVar2 + 0x20))(plVar2,param_2), -1 < iVar1) {
      if (iVar1 == 0) {
        return *plVar4;
      }
      plVar4 = (long *)(*plVar4 + 0x20);
      plVar2 = (long *)*plVar4;
      if (plVar2 == (long *)0x0) {
        return 0;
      }
    }
    plVar4 = (long *)(*plVar4 + 0x18);
    plVar2 = (long *)*plVar4;
  } while( true );
}

// ==== Aska::TCategorizeHash<Aska::MappedMemoryLocation>::FreeNode(Aska::MappedMemoryLocation**)
// vaddr 0x1f2ff64 | ghidra 0x202ff64 | size 460 | symbol _ZN4Aska15TCategorizeHashINS_20MappedMemoryLocationEE8FreeNodeEPPS1_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska15TCategorizeHashINS_20MappedMemoryLocationEE8FreeNodeEPPS1_
               (long *param_1,ulong *param_2)

{
  long lVar1;
  char cVar2;
  long *plVar3;
  ulong uVar4;
  long *plVar5;
  long lVar6;
  
  uVar4 = *param_2;
  if (uVar4 != 0) {
    if (param_1[0xe] == uVar4) {
      param_1[0xe] = *(long *)(uVar4 + 0x10);
      uVar4 = *param_2;
    }
    if (param_1[0xf] == uVar4) {
      param_1[0xf] = *(long *)(uVar4 + 8);
      uVar4 = *param_2;
    }
    if (param_1[0x10] == uVar4) {
      param_1[0x10] = *(long *)(uVar4 + 8);
      cVar2 = (char)param_1[0x11];
    }
    else {
      cVar2 = (char)param_1[0x11];
    }
    if ((cVar2 == '\0') && (param_1[0x12] == *param_2)) {
      *(undefined4 *)(param_1 + 0x13) = 0;
      param_1[0x12] = 0;
      param_1[0x10] = 0;
      *(undefined1 *)(param_1 + 0x11) = 0;
    }
    lVar6 = *(long *)(*param_2 + 8);
    lVar1 = *(long *)(*param_2 + 0x10);
    if (lVar6 != 0) {
      *(long *)(lVar6 + 0x10) = lVar1;
    }
    if (lVar1 != 0) {
      *(undefined8 *)(lVar1 + 8) = *(undefined8 *)(*param_2 + 8);
    }
    *(undefined8 *)(*param_2 + 0x10) = 0;
    *(undefined8 *)(*param_2 + 8) = 0;
    plVar3 = (long *)*param_2;
    if (plVar3[10] != 0) {
      (**(code **)(*param_1 + 0x18))(param_1);
      plVar3 = (long *)*param_2;
    }
    if (plVar3[4] != 0) {
      (**(code **)(*param_1 + 0x18))(param_1);
      plVar3 = (long *)*param_2;
    }
    if (plVar3[3] != 0) {
      (**(code **)(*param_1 + 0x18))(param_1);
      plVar3 = (long *)*param_2;
    }
    (**(code **)(*plVar3 + 0x18))();
    *(int *)((long)param_1 + 0x8c) = *(int *)((long)param_1 + 0x8c) + -1;
    plVar5 = (long *)param_1[8];
    plVar3 = (long *)*param_2;
    if (((plVar5 == (long *)0x0) || (plVar3 < plVar5)) ||
       (plVar5 + (ulong)*(uint *)((long)param_1 + 0x2c) * 0x10 <= plVar3)) {
      if (plVar3 != (long *)0x0) {
        (**(code **)(*plVar3 + 8))();
      }
    }
    else {
      uVar4 = (long)plVar3 - (long)plVar5;
      (**(code **)plVar5[(uVar4 >> 7 & 0xffffffff) * 0x10])();
      lVar6 = (uVar4 >> 0xc & 0x7ffffff) * 4;
      *(uint *)(param_1[4] + lVar6) =
           *(uint *)(param_1[4] + lVar6) & (1 << (uVar4 >> 7 & 0x1f) ^ 0xffffffffU);
      *(int *)((long)param_1 + 0x3c) = *(int *)((long)param_1 + 0x3c) + -1;
    }
    *param_2 = 0;
  }
  return;
}

// ==== Aska::TCategorizeHash<Aska::MappedMemoryLocation>::Remove(Aska::MappedMemoryLocation**)
// vaddr 0x1f30220 | ghidra 0x2030220 | size 232 | symbol _ZN4Aska15TCategorizeHashINS_20MappedMemoryLocationEE6RemoveEPPS1_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska15TCategorizeHashINS_20MappedMemoryLocationEE6RemoveEPPS1_(long *param_1,long *param_2)

{
  long *plVar1;
  long *plVar2;
  long lVar3;
  long lStack_8;
  
  lStack_8 = *param_2;
  if (lStack_8 == 0) {
    return;
  }
  if (*(long *)(lStack_8 + 0x50) == 0) {
    if (*(long *)(lStack_8 + 0x48) != 0) {
      *param_2 = *(long *)(lStack_8 + 0x48);
      *(undefined8 *)(*(long *)(lStack_8 + 0x48) + 0x50) = 0;
      *(undefined8 *)(lStack_8 + 0x48) = 0;
      goto code_r0x02030294;
    }
    lVar3 = *(long *)(lStack_8 + 0x18);
    if (*(long *)(lStack_8 + 0x20) == 0) {
      *param_2 = lVar3;
      *(undefined8 *)(lStack_8 + 0x18) = 0;
      goto code_r0x02030294;
    }
    plVar1 = (long *)(lStack_8 + 0x18);
    if (lVar3 != 0) {
      do {
        plVar2 = plVar1;
        lVar3 = *plVar2;
        plVar1 = (long *)(lVar3 + 0x20);
      } while (*(long *)(lVar3 + 0x20) != 0);
      *plVar2 = *(long *)(lVar3 + 0x18);
      *(undefined8 *)(lVar3 + 0x18) = *(undefined8 *)(lStack_8 + 0x18);
      *(undefined8 *)(lVar3 + 0x20) = *(undefined8 *)(lStack_8 + 0x20);
      *param_2 = lVar3;
      goto code_r0x02030270;
    }
    *param_2 = *(long *)(lStack_8 + 0x20);
  }
  else {
    *param_2 = *(long *)(lStack_8 + 0x50);
    *(undefined8 *)(*(long *)(lStack_8 + 0x50) + 0x48) = *(undefined8 *)(lStack_8 + 0x48);
    if (*(long *)(lStack_8 + 0x48) != 0) {
      *(undefined8 *)(*(long *)(lStack_8 + 0x48) + 0x50) = *(undefined8 *)(lStack_8 + 0x50);
    }
    *(undefined8 *)(*(long *)(lStack_8 + 0x50) + 0x18) = *(undefined8 *)(lStack_8 + 0x18);
    *(undefined8 *)(*(long *)(lStack_8 + 0x50) + 0x20) = *(undefined8 *)(lStack_8 + 0x20);
    *(undefined8 *)(lStack_8 + 0x48) = 0;
    *(undefined8 *)(lStack_8 + 0x50) = 0;
code_r0x02030270:
    *(undefined8 *)(lStack_8 + 0x18) = 0;
  }
  *(undefined8 *)(lStack_8 + 0x20) = 0;
code_r0x02030294:
  (**(code **)(*param_1 + 0x18))(param_1,&lStack_8);
  return;
}

// ==== Aska::TCategorizeHash<Aska::MappedMemoryLocation>::Regist(void const*, unsigned int)
// vaddr 0x1f303bc | ghidra 0x20303bc | size 384 | symbol _ZN4Aska15TCategorizeHashINS_20MappedMemoryLocationEE6RegistEPKvj | lib libSOA-3.7.0.so | 2026-10-04
long * _ZN4Aska15TCategorizeHashINS_20MappedMemoryLocationEE6RegistEPKvj
                 (long *param_1,undefined8 param_2,uint param_3)

{
  int iVar1;
  long *plVar2;
  long lVar3;
  long *plVar4;
  long *plVar5;
  ulong uVar6;
  long *plVar7;
  
  uVar6 = (ulong)param_3;
  if (*(uint *)(param_1 + 0xb) <= param_3) {
    uVar6 = 0;
  }
  plVar4 = (long *)(param_1[10] + uVar6 * 8);
  param_1[0xc] = (long)plVar4;
  plVar2 = (long *)*plVar4;
  while (plVar2 != (long *)0x0) {
    while (iVar1 = (**(code **)(*plVar2 + 0x20))(plVar2,param_2), -1 < iVar1) {
      if (iVar1 == 0) goto code_r0x0203044c;
      plVar4 = (long *)(*plVar4 + 0x20);
      plVar2 = (long *)*plVar4;
      if (plVar2 == (long *)0x0) goto code_r0x02030430;
    }
    plVar4 = (long *)(*plVar4 + 0x18);
    plVar2 = (long *)*plVar4;
  }
code_r0x02030430:
  lVar3 = (**(code **)(*param_1 + 0x10))(param_1,param_2);
  *plVar4 = lVar3;
  plVar2 = (long *)0x0;
  if (lVar3 != 0) {
code_r0x0203044c:
    if ((plVar4 == (long *)0x0) || (plVar7 = (long *)*plVar4, plVar7 == (long *)0x0)) {
      plVar2 = (long *)0x0;
    }
    else {
      iVar1 = (**(code **)(*plVar7 + 0x38))(plVar7,param_2);
      while (0 < iVar1) {
        plVar2 = (long *)plVar7[10];
        if (plVar2 == (long *)0x0) {
          plVar4 = (long *)(**(code **)(*param_1 + 0x10))(param_1,param_2);
          if (plVar4 == (long *)0x0) {
            return (long *)0x0;
          }
          plVar4[9] = (long)plVar7;
          plVar7[10] = (long)plVar4;
          return plVar4;
        }
        iVar1 = (**(code **)(*plVar2 + 0x38))(plVar2,param_2);
        plVar7 = plVar2;
      }
      plVar2 = plVar7;
      if ((iVar1 < 0) &&
         (plVar2 = (long *)(**(code **)(*param_1 + 0x10))(param_1,param_2), plVar2 != (long *)0x0))
      {
        plVar2[3] = plVar7[3];
        plVar2[4] = plVar7[4];
        lVar3 = plVar7[9];
        plVar7[3] = 0;
        plVar7[4] = 0;
        plVar2[9] = lVar3;
        plVar2[10] = (long)plVar7;
        plVar5 = plVar7;
        if (lVar3 != 0) {
          *(long **)(lVar3 + 0x50) = plVar2;
          plVar5 = (long *)plVar2[10];
        }
        plVar5[9] = (long)plVar2;
        if ((long *)*plVar4 == plVar7) {
          *plVar4 = (long)plVar2;
        }
      }
    }
  }
  return plVar2;
}

// ==== Aska::TCategorizeHash<Aska::MappedMemoryLocation>::Remove(void const*, unsigned int)
// vaddr 0x1f3053c | ghidra 0x203053c | size 200 | symbol _ZN4Aska15TCategorizeHashINS_20MappedMemoryLocationEE6RemoveEPKvj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska15TCategorizeHashINS_20MappedMemoryLocationEE6RemoveEPKvj
               (long *param_1,undefined8 param_2,uint param_3)

{
  int iVar1;
  long *plVar2;
  ulong uVar3;
  long *plVar4;
  
  uVar3 = (ulong)param_3;
  if (*(uint *)(param_1 + 0xb) <= param_3) {
    uVar3 = 0;
  }
  plVar4 = (long *)(param_1[10] + uVar3 * 8);
  param_1[0xc] = (long)plVar4;
  plVar2 = (long *)*plVar4;
  while (plVar2 != (long *)0x0) {
    iVar1 = (**(code **)(*plVar2 + 0x20))(plVar2,param_2);
    if (iVar1 < 0) {
      plVar4 = (long *)(*plVar4 + 0x18);
    }
    else {
      if (iVar1 == 0) goto code_r0x020305ac;
      plVar4 = (long *)(*plVar4 + 0x20);
    }
    plVar2 = (long *)*plVar4;
  }
code_r0x020305dc:
                    /* WARNING: Could not recover jumptable at 0x020305f4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*param_1 + 0x40))(param_1,plVar4);
  return;
code_r0x020305ac:
  plVar2 = (long *)*plVar4;
  if (plVar2 == (long *)0x0) goto code_r0x020305dc;
  iVar1 = (**(code **)(*plVar2 + 0x38))(plVar2,param_2);
  if (iVar1 < 1) {
    if (iVar1 < 0) {
      return;
    }
    goto code_r0x020305dc;
  }
  plVar4 = (long *)(*plVar4 + 0x50);
  goto code_r0x020305ac;
}

// ==== Aska::TCategorizeHash<Aska::MappedMemoryLocation>::Search(void const*, unsigned int)
// vaddr 0x1f30624 | ghidra 0x2030624 | size 180 | symbol _ZN4Aska15TCategorizeHashINS_20MappedMemoryLocationEE6SearchEPKvj | lib libSOA-3.7.0.so | 2026-10-04
long * _ZN4Aska15TCategorizeHashINS_20MappedMemoryLocationEE6SearchEPKvj
                 (long param_1,undefined8 param_2,uint param_3)

{
  int iVar1;
  long *plVar2;
  ulong uVar3;
  long *plVar4;
  
  uVar3 = (ulong)param_3;
  if (*(uint *)(param_1 + 0x58) <= param_3) {
    uVar3 = 0;
  }
  plVar4 = (long *)(*(long *)(param_1 + 0x50) + uVar3 * 8);
  plVar2 = (long *)*plVar4;
  while( true ) {
    while( true ) {
      if (plVar2 == (long *)0x0) {
        return (long *)0x0;
      }
      iVar1 = (**(code **)(*plVar2 + 0x20))(plVar2,param_2);
      if (-1 < iVar1) break;
      plVar4 = (long *)(*plVar4 + 0x18);
      plVar2 = (long *)*plVar4;
    }
    if (iVar1 == 0) break;
    plVar4 = (long *)(*plVar4 + 0x20);
    plVar2 = (long *)*plVar4;
  }
  plVar4 = (long *)*plVar4;
  while( true ) {
    if (plVar4 == (long *)0x0) {
      return (long *)0x0;
    }
    iVar1 = (**(code **)(*plVar4 + 0x38))(plVar4,param_2);
    if (iVar1 == 0) break;
    if (iVar1 < 1) {
      return (long *)0x0;
    }
    plVar4 = (long *)plVar4[10];
  }
  return plVar4;
}

// ==== Aska::TCategorizeHash<Aska::MappedMemoryIdentifier>::FreeNode(Aska::MappedMemoryIdentifier**)
// vaddr 0x1f30898 | ghidra 0x2030898 | size 484 | symbol _ZN4Aska15TCategorizeHashINS_22MappedMemoryIdentifierEE8FreeNodeEPPS1_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska15TCategorizeHashINS_22MappedMemoryIdentifierEE8FreeNodeEPPS1_
               (long *param_1,ulong *param_2)

{
  long lVar1;
  char cVar2;
  long *plVar3;
  ulong uVar4;
  long *plVar5;
  long lVar6;
  
  uVar4 = *param_2;
  if (uVar4 != 0) {
    if (param_1[0xe] == uVar4) {
      param_1[0xe] = *(long *)(uVar4 + 0x10);
      uVar4 = *param_2;
    }
    if (param_1[0xf] == uVar4) {
      param_1[0xf] = *(long *)(uVar4 + 8);
      uVar4 = *param_2;
    }
    if (param_1[0x10] == uVar4) {
      param_1[0x10] = *(long *)(uVar4 + 8);
      cVar2 = (char)param_1[0x11];
    }
    else {
      cVar2 = (char)param_1[0x11];
    }
    if ((cVar2 == '\0') && (param_1[0x12] == *param_2)) {
      *(undefined4 *)(param_1 + 0x13) = 0;
      param_1[0x12] = 0;
      param_1[0x10] = 0;
      *(undefined1 *)(param_1 + 0x11) = 0;
    }
    lVar6 = *(long *)(*param_2 + 8);
    lVar1 = *(long *)(*param_2 + 0x10);
    if (lVar6 != 0) {
      *(long *)(lVar6 + 0x10) = lVar1;
    }
    if (lVar1 != 0) {
      *(undefined8 *)(lVar1 + 8) = *(undefined8 *)(*param_2 + 8);
    }
    *(undefined8 *)(*param_2 + 0x10) = 0;
    *(undefined8 *)(*param_2 + 8) = 0;
    plVar3 = (long *)*param_2;
    if (plVar3[9] != 0) {
      (**(code **)(*param_1 + 0x18))(param_1);
      plVar3 = (long *)*param_2;
    }
    if (plVar3[4] != 0) {
      (**(code **)(*param_1 + 0x18))(param_1);
      plVar3 = (long *)*param_2;
    }
    if (plVar3[3] != 0) {
      (**(code **)(*param_1 + 0x18))(param_1);
      plVar3 = (long *)*param_2;
    }
    (**(code **)(*plVar3 + 0x18))();
    *(int *)((long)param_1 + 0x8c) = *(int *)((long)param_1 + 0x8c) + -1;
    plVar5 = (long *)param_1[8];
    plVar3 = (long *)*param_2;
    if (((plVar5 == (long *)0x0) || (plVar3 < plVar5)) ||
       (plVar5 + (ulong)*(uint *)((long)param_1 + 0x2c) * 10 <= plVar3)) {
      if (plVar3 != (long *)0x0) {
        (**(code **)(*plVar3 + 8))();
      }
    }
    else {
      uVar4 = ((long)plVar3 - (long)plVar5 >> 4) * -0x3333333333333333;
      (**(code **)plVar5[(uVar4 & 0xffffffff) * 10])();
      lVar6 = (uVar4 >> 5 & 0x7ffffff) * 4;
      *(uint *)(param_1[4] + lVar6) =
           *(uint *)(param_1[4] + lVar6) & (1 << (ulong)((uint)uVar4 & 0x1f) ^ 0xffffffffU);
      *(int *)((long)param_1 + 0x3c) = *(int *)((long)param_1 + 0x3c) + -1;
    }
    *param_2 = 0;
  }
  return;
}

// ==== Aska::TCategorizeHash<Aska::MappedMemoryIdentifier>::Remove(Aska::MappedMemoryIdentifier**)
// vaddr 0x1f30b6c | ghidra 0x2030b6c | size 232 | symbol _ZN4Aska15TCategorizeHashINS_22MappedMemoryIdentifierEE6RemoveEPPS1_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska15TCategorizeHashINS_22MappedMemoryIdentifierEE6RemoveEPPS1_
               (long *param_1,long *param_2)

{
  long *plVar1;
  long *plVar2;
  long lVar3;
  long lStack_8;
  
  lStack_8 = *param_2;
  if (lStack_8 == 0) {
    return;
  }
  if (*(long *)(lStack_8 + 0x48) == 0) {
    if (*(long *)(lStack_8 + 0x40) != 0) {
      *param_2 = *(long *)(lStack_8 + 0x40);
      *(undefined8 *)(*(long *)(lStack_8 + 0x40) + 0x48) = 0;
      *(undefined8 *)(lStack_8 + 0x40) = 0;
      goto code_r0x02030be0;
    }
    lVar3 = *(long *)(lStack_8 + 0x18);
    if (*(long *)(lStack_8 + 0x20) == 0) {
      *param_2 = lVar3;
      *(undefined8 *)(lStack_8 + 0x18) = 0;
      goto code_r0x02030be0;
    }
    plVar1 = (long *)(lStack_8 + 0x18);
    if (lVar3 != 0) {
      do {
        plVar2 = plVar1;
        lVar3 = *plVar2;
        plVar1 = (long *)(lVar3 + 0x20);
      } while (*(long *)(lVar3 + 0x20) != 0);
      *plVar2 = *(long *)(lVar3 + 0x18);
      *(undefined8 *)(lVar3 + 0x18) = *(undefined8 *)(lStack_8 + 0x18);
      *(undefined8 *)(lVar3 + 0x20) = *(undefined8 *)(lStack_8 + 0x20);
      *param_2 = lVar3;
      goto code_r0x02030bbc;
    }
    *param_2 = *(long *)(lStack_8 + 0x20);
  }
  else {
    *param_2 = *(long *)(lStack_8 + 0x48);
    *(undefined8 *)(*(long *)(lStack_8 + 0x48) + 0x40) = *(undefined8 *)(lStack_8 + 0x40);
    if (*(long *)(lStack_8 + 0x40) != 0) {
      *(undefined8 *)(*(long *)(lStack_8 + 0x40) + 0x48) = *(undefined8 *)(lStack_8 + 0x48);
    }
    *(undefined8 *)(*(long *)(lStack_8 + 0x48) + 0x18) = *(undefined8 *)(lStack_8 + 0x18);
    *(undefined8 *)(*(long *)(lStack_8 + 0x48) + 0x20) = *(undefined8 *)(lStack_8 + 0x20);
    *(undefined8 *)(lStack_8 + 0x40) = 0;
    *(undefined8 *)(lStack_8 + 0x48) = 0;
code_r0x02030bbc:
    *(undefined8 *)(lStack_8 + 0x18) = 0;
  }
  *(undefined8 *)(lStack_8 + 0x20) = 0;
code_r0x02030be0:
  (**(code **)(*param_1 + 0x18))(param_1,&lStack_8);
  return;
}

// ==== Aska::TCategorizeHash<Aska::MappedMemoryIdentifier>::Regist(void const*, unsigned int)
// vaddr 0x1f30d08 | ghidra 0x2030d08 | size 384 | symbol _ZN4Aska15TCategorizeHashINS_22MappedMemoryIdentifierEE6RegistEPKvj | lib libSOA-3.7.0.so | 2026-10-04
long * _ZN4Aska15TCategorizeHashINS_22MappedMemoryIdentifierEE6RegistEPKvj
                 (long *param_1,undefined8 param_2,uint param_3)

{
  int iVar1;
  long *plVar2;
  long lVar3;
  long *plVar4;
  long *plVar5;
  ulong uVar6;
  long *plVar7;
  
  uVar6 = (ulong)param_3;
  if (*(uint *)(param_1 + 0xb) <= param_3) {
    uVar6 = 0;
  }
  plVar4 = (long *)(param_1[10] + uVar6 * 8);
  param_1[0xc] = (long)plVar4;
  plVar2 = (long *)*plVar4;
  while (plVar2 != (long *)0x0) {
    while (iVar1 = (**(code **)(*plVar2 + 0x20))(plVar2,param_2), -1 < iVar1) {
      if (iVar1 == 0) goto code_r0x02030d98;
      plVar4 = (long *)(*plVar4 + 0x20);
      plVar2 = (long *)*plVar4;
      if (plVar2 == (long *)0x0) goto code_r0x02030d7c;
    }
    plVar4 = (long *)(*plVar4 + 0x18);
    plVar2 = (long *)*plVar4;
  }
code_r0x02030d7c:
  lVar3 = (**(code **)(*param_1 + 0x10))(param_1,param_2);
  *plVar4 = lVar3;
  plVar2 = (long *)0x0;
  if (lVar3 != 0) {
code_r0x02030d98:
    if ((plVar4 == (long *)0x0) || (plVar7 = (long *)*plVar4, plVar7 == (long *)0x0)) {
      plVar2 = (long *)0x0;
    }
    else {
      iVar1 = (**(code **)(*plVar7 + 0x38))(plVar7,param_2);
      while (0 < iVar1) {
        plVar2 = (long *)plVar7[9];
        if (plVar2 == (long *)0x0) {
          plVar4 = (long *)(**(code **)(*param_1 + 0x10))(param_1,param_2);
          if (plVar4 == (long *)0x0) {
            return (long *)0x0;
          }
          plVar4[8] = (long)plVar7;
          plVar7[9] = (long)plVar4;
          return plVar4;
        }
        iVar1 = (**(code **)(*plVar2 + 0x38))(plVar2,param_2);
        plVar7 = plVar2;
      }
      plVar2 = plVar7;
      if ((iVar1 < 0) &&
         (plVar2 = (long *)(**(code **)(*param_1 + 0x10))(param_1,param_2), plVar2 != (long *)0x0))
      {
        plVar2[3] = plVar7[3];
        plVar2[4] = plVar7[4];
        lVar3 = plVar7[8];
        plVar7[3] = 0;
        plVar7[4] = 0;
        plVar2[8] = lVar3;
        plVar2[9] = (long)plVar7;
        plVar5 = plVar7;
        if (lVar3 != 0) {
          *(long **)(lVar3 + 0x48) = plVar2;
          plVar5 = (long *)plVar2[9];
        }
        plVar5[8] = (long)plVar2;
        if ((long *)*plVar4 == plVar7) {
          *plVar4 = (long)plVar2;
        }
      }
    }
  }
  return plVar2;
}

// ==== Aska::TCategorizeHash<Aska::MappedMemoryIdentifier>::Remove(void const*, unsigned int)
// vaddr 0x1f30e88 | ghidra 0x2030e88 | size 200 | symbol _ZN4Aska15TCategorizeHashINS_22MappedMemoryIdentifierEE6RemoveEPKvj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska15TCategorizeHashINS_22MappedMemoryIdentifierEE6RemoveEPKvj
               (long *param_1,undefined8 param_2,uint param_3)

{
  int iVar1;
  long *plVar2;
  ulong uVar3;
  long *plVar4;
  
  uVar3 = (ulong)param_3;
  if (*(uint *)(param_1 + 0xb) <= param_3) {
    uVar3 = 0;
  }
  plVar4 = (long *)(param_1[10] + uVar3 * 8);
  param_1[0xc] = (long)plVar4;
  plVar2 = (long *)*plVar4;
  while (plVar2 != (long *)0x0) {
    iVar1 = (**(code **)(*plVar2 + 0x20))(plVar2,param_2);
    if (iVar1 < 0) {
      plVar4 = (long *)(*plVar4 + 0x18);
    }
    else {
      if (iVar1 == 0) goto code_r0x02030ef8;
      plVar4 = (long *)(*plVar4 + 0x20);
    }
    plVar2 = (long *)*plVar4;
  }
code_r0x02030f28:
                    /* WARNING: Could not recover jumptable at 0x02030f40. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*param_1 + 0x40))(param_1,plVar4);
  return;
code_r0x02030ef8:
  plVar2 = (long *)*plVar4;
  if (plVar2 == (long *)0x0) goto code_r0x02030f28;
  iVar1 = (**(code **)(*plVar2 + 0x38))(plVar2,param_2);
  if (iVar1 < 1) {
    if (iVar1 < 0) {
      return;
    }
    goto code_r0x02030f28;
  }
  plVar4 = (long *)(*plVar4 + 0x48);
  goto code_r0x02030ef8;
}

// ==== Aska::TCategorizeHash<Aska::MappedMemoryIdentifier>::Search(void const*, unsigned int)
// vaddr 0x1f30f70 | ghidra 0x2030f70 | size 180 | symbol _ZN4Aska15TCategorizeHashINS_22MappedMemoryIdentifierEE6SearchEPKvj | lib libSOA-3.7.0.so | 2026-10-04
long * _ZN4Aska15TCategorizeHashINS_22MappedMemoryIdentifierEE6SearchEPKvj
                 (long param_1,undefined8 param_2,uint param_3)

{
  int iVar1;
  long *plVar2;
  ulong uVar3;
  long *plVar4;
  
  uVar3 = (ulong)param_3;
  if (*(uint *)(param_1 + 0x58) <= param_3) {
    uVar3 = 0;
  }
  plVar4 = (long *)(*(long *)(param_1 + 0x50) + uVar3 * 8);
  plVar2 = (long *)*plVar4;
  while( true ) {
    while( true ) {
      if (plVar2 == (long *)0x0) {
        return (long *)0x0;
      }
      iVar1 = (**(code **)(*plVar2 + 0x20))(plVar2,param_2);
      if (-1 < iVar1) break;
      plVar4 = (long *)(*plVar4 + 0x18);
      plVar2 = (long *)*plVar4;
    }
    if (iVar1 == 0) break;
    plVar4 = (long *)(*plVar4 + 0x20);
    plVar2 = (long *)*plVar4;
  }
  plVar4 = (long *)*plVar4;
  while( true ) {
    if (plVar4 == (long *)0x0) {
      return (long *)0x0;
    }
    iVar1 = (**(code **)(*plVar4 + 0x38))(plVar4,param_2);
    if (iVar1 == 0) break;
    if (iVar1 < 1) {
      return (long *)0x0;
    }
    plVar4 = (long *)plVar4[9];
  }
  return plVar4;
}

// ==== Aska::THash<Aska::ClassNameSet>::Regist(void const*)
// vaddr 0x1f51320 | ghidra 0x2051320 | size 64 | symbol _ZN4Aska5THashINS_12ClassNameSetEE6RegistEPKv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5THashINS_12ClassNameSetEE6RegistEPKv(long *param_1,undefined8 param_2)

{
  code *UNRECOVERED_JUMPTABLE;
  undefined4 uVar1;
  
  UNRECOVERED_JUMPTABLE = *(code **)(*param_1 + 0x68);
  uVar1 = (**(code **)(*param_1 + 0x60))(param_1);
                    /* WARNING: Could not recover jumptable at 0x0205135c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*UNRECOVERED_JUMPTABLE)(param_1,param_2,uVar1);
  return;
}

// ==== Aska::THash<Aska::ClassNameSet>::IsRegisted(void const*)
// vaddr 0x1f513f8 | ghidra 0x20513f8 | size 68 | symbol _ZN4Aska5THashINS_12ClassNameSetEE10IsRegistedEPKv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5THashINS_12ClassNameSetEE10IsRegistedEPKv(long *param_1,undefined8 param_2)

{
  undefined4 uVar1;
  code *UNRECOVERED_JUMPTABLE;
  
  UNRECOVERED_JUMPTABLE = *(code **)(*param_1 + 0x78);
  uVar1 = (**(code **)(*param_1 + 0x60))(param_1);
                    /* WARNING: Could not recover jumptable at 0x02051438. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*UNRECOVERED_JUMPTABLE)(param_1,param_2,uVar1);
  return;
}

// ==== Aska::THash<Aska::ClassNameSet>::CalcHashValue(void const*) const
// vaddr 0x1f514f0 | ghidra 0x20514f0 | size 84 | symbol _ZNK4Aska5THashINS_12ClassNameSetEE13CalcHashValueEPKv | lib libSOA-3.7.0.so | 2026-10-04
int _ZNK4Aska5THashINS_12ClassNameSetEE13CalcHashValueEPKv(long param_1,byte *param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  long lVar4;
  
  uVar1 = *(uint *)(param_1 + 0x58);
  uVar2 = 0x811c9dc5;
  lVar4 = strlen(param_2);
  for (; lVar4 != 0; lVar4 = lVar4 + -1) {
    uVar2 = uVar2 * 0x1000193 ^ (uint)*param_2;
    param_2 = param_2 + 1;
  }
  uVar3 = 0;
  if (uVar1 != 0) {
    uVar3 = uVar2 / uVar1;
  }
  return uVar2 - uVar3 * uVar1;
}

// ==== Aska::THash<Aska::ClassNameSet>::Regist(void const*, unsigned int)
// vaddr 0x1f51544 | ghidra 0x2051544 | size 168 | symbol _ZN4Aska5THashINS_12ClassNameSetEE6RegistEPKvj | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska5THashINS_12ClassNameSetEE6RegistEPKvj(long *param_1,undefined8 param_2,uint param_3)

{
  int iVar1;
  long *plVar2;
  long lVar3;
  long lVar4;
  ulong uVar5;
  long *plVar6;
  
  uVar5 = (ulong)param_3;
  if (*(uint *)(param_1 + 0xb) <= param_3) {
    uVar5 = 0;
  }
  plVar6 = (long *)(param_1[10] + uVar5 * 8);
  param_1[0xc] = (long)plVar6;
  plVar2 = (long *)*plVar6;
  while (plVar2 != (long *)0x0) {
    while (iVar1 = (**(code **)(*plVar2 + 0x20))(plVar2,param_2), -1 < iVar1) {
      if (iVar1 == 0) goto code_r0x020515d0;
      plVar6 = (long *)(*plVar6 + 0x20);
      plVar2 = (long *)*plVar6;
      if (plVar2 == (long *)0x0) goto code_r0x020515b4;
    }
    plVar6 = (long *)(*plVar6 + 0x18);
    plVar2 = (long *)*plVar6;
  }
code_r0x020515b4:
  lVar3 = (**(code **)(*param_1 + 0x10))(param_1,param_2);
  *plVar6 = lVar3;
  lVar4 = 0;
  if (lVar3 != 0) {
code_r0x020515d0:
    if (plVar6 == (long *)0x0) {
      lVar4 = 0;
    }
    else {
      lVar4 = *plVar6;
    }
  }
  return lVar4;
}

// ==== Aska::THash<Aska::ClassNameSet>::IsRegisted(void const*, unsigned int)
// vaddr 0x1f51678 | ghidra 0x2051678 | size 132 | symbol _ZN4Aska5THashINS_12ClassNameSetEE10IsRegistedEPKvj | lib libSOA-3.7.0.so | 2026-10-04
bool _ZN4Aska5THashINS_12ClassNameSetEE10IsRegistedEPKvj
               (long param_1,undefined8 param_2,uint param_3)

{
  int iVar1;
  long *plVar2;
  ulong uVar3;
  long *plVar4;
  
  uVar3 = (ulong)param_3;
  if (*(uint *)(param_1 + 0x58) <= param_3) {
    uVar3 = 0;
  }
  plVar4 = (long *)(*(long *)(param_1 + 0x50) + uVar3 * 8);
  plVar2 = (long *)*plVar4;
  do {
    if (plVar2 == (long *)0x0) {
      return false;
    }
    while (iVar1 = (**(code **)(*plVar2 + 0x20))(plVar2,param_2), -1 < iVar1) {
      if (iVar1 == 0) {
        return *plVar4 != 0;
      }
      plVar4 = (long *)(*plVar4 + 0x20);
      plVar2 = (long *)*plVar4;
      if (plVar2 == (long *)0x0) {
        return false;
      }
    }
    plVar4 = (long *)(*plVar4 + 0x18);
    plVar2 = (long *)*plVar4;
  } while( true );
}

// ==== Aska::THash<Aska::ParamNameSet>::Regist(void const*)
// vaddr 0x1f52530 | ghidra 0x2052530 | size 64 | symbol _ZN4Aska5THashINS_12ParamNameSetEE6RegistEPKv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5THashINS_12ParamNameSetEE6RegistEPKv(long *param_1,undefined8 param_2)

{
  code *UNRECOVERED_JUMPTABLE;
  undefined4 uVar1;
  
  UNRECOVERED_JUMPTABLE = *(code **)(*param_1 + 0x68);
  uVar1 = (**(code **)(*param_1 + 0x60))(param_1);
                    /* WARNING: Could not recover jumptable at 0x0205256c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*UNRECOVERED_JUMPTABLE)(param_1,param_2,uVar1);
  return;
}

// ==== Aska::THash<Aska::ParamNameSet>::CalcHashValue(void const*) const
// vaddr 0x1f52744 | ghidra 0x2052744 | size 84 | symbol _ZNK4Aska5THashINS_12ParamNameSetEE13CalcHashValueEPKv | lib libSOA-3.7.0.so | 2026-10-04
int _ZNK4Aska5THashINS_12ParamNameSetEE13CalcHashValueEPKv(long param_1,byte *param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  long lVar4;
  
  uVar1 = *(uint *)(param_1 + 0x58);
  uVar2 = 0x811c9dc5;
  lVar4 = strlen(param_2);
  for (; lVar4 != 0; lVar4 = lVar4 + -1) {
    uVar2 = uVar2 * 0x1000193 ^ (uint)*param_2;
    param_2 = param_2 + 1;
  }
  uVar3 = 0;
  if (uVar1 != 0) {
    uVar3 = uVar2 / uVar1;
  }
  return uVar2 - uVar3 * uVar1;
}

// ==== Aska::THash<Aska::ParamNameSet>::Regist(void const*, unsigned int)
// vaddr 0x1f52798 | ghidra 0x2052798 | size 168 | symbol _ZN4Aska5THashINS_12ParamNameSetEE6RegistEPKvj | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska5THashINS_12ParamNameSetEE6RegistEPKvj(long *param_1,undefined8 param_2,uint param_3)

{
  int iVar1;
  long *plVar2;
  long lVar3;
  long lVar4;
  ulong uVar5;
  long *plVar6;
  
  uVar5 = (ulong)param_3;
  if (*(uint *)(param_1 + 0xb) <= param_3) {
    uVar5 = 0;
  }
  plVar6 = (long *)(param_1[10] + uVar5 * 8);
  param_1[0xc] = (long)plVar6;
  plVar2 = (long *)*plVar6;
  while (plVar2 != (long *)0x0) {
    while (iVar1 = (**(code **)(*plVar2 + 0x20))(plVar2,param_2), -1 < iVar1) {
      if (iVar1 == 0) goto code_r0x02052824;
      plVar6 = (long *)(*plVar6 + 0x20);
      plVar2 = (long *)*plVar6;
      if (plVar2 == (long *)0x0) goto code_r0x02052808;
    }
    plVar6 = (long *)(*plVar6 + 0x18);
    plVar2 = (long *)*plVar6;
  }
code_r0x02052808:
  lVar3 = (**(code **)(*param_1 + 0x10))(param_1,param_2);
  *plVar6 = lVar3;
  lVar4 = 0;
  if (lVar3 != 0) {
code_r0x02052824:
    if (plVar6 == (long *)0x0) {
      lVar4 = 0;
    }
    else {
      lVar4 = *plVar6;
    }
  }
  return lVar4;
}

// ==== Aska::THash<Aska::AsfNode>::Regist(void const*, unsigned int)
// vaddr 0x20e0178 | ghidra 0x21e0178 | size 168 | symbol _ZN4Aska5THashINS_7AsfNodeEE6RegistEPKvj | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska5THashINS_7AsfNodeEE6RegistEPKvj(long *param_1,undefined8 param_2,uint param_3)

{
  int iVar1;
  long *plVar2;
  long lVar3;
  long lVar4;
  ulong uVar5;
  long *plVar6;
  
  uVar5 = (ulong)param_3;
  if (*(uint *)(param_1 + 0xb) <= param_3) {
    uVar5 = 0;
  }
  plVar6 = (long *)(param_1[10] + uVar5 * 8);
  param_1[0xc] = (long)plVar6;
  plVar2 = (long *)*plVar6;
  while (plVar2 != (long *)0x0) {
    while (iVar1 = (**(code **)(*plVar2 + 0x20))(plVar2,param_2), -1 < iVar1) {
      if (iVar1 == 0) goto code_r0x021e0204;
      plVar6 = (long *)(*plVar6 + 0x20);
      plVar2 = (long *)*plVar6;
      if (plVar2 == (long *)0x0) goto code_r0x021e01e8;
    }
    plVar6 = (long *)(*plVar6 + 0x18);
    plVar2 = (long *)*plVar6;
  }
code_r0x021e01e8:
  lVar3 = (**(code **)(*param_1 + 0x10))(param_1,param_2);
  *plVar6 = lVar3;
  lVar4 = 0;
  if (lVar3 != 0) {
code_r0x021e0204:
    if (plVar6 == (long *)0x0) {
      lVar4 = 0;
    }
    else {
      lVar4 = *plVar6;
    }
  }
  return lVar4;
}

// ==== Aska::THash<Aska::AsfNode>::Search(void const*, unsigned int)
// vaddr 0x20e0330 | ghidra 0x21e0330 | size 124 | symbol _ZN4Aska5THashINS_7AsfNodeEE6SearchEPKvj | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska5THashINS_7AsfNodeEE6SearchEPKvj(long param_1,undefined8 param_2,uint param_3)

{
  int iVar1;
  long *plVar2;
  ulong uVar3;
  long *plVar4;
  
  uVar3 = (ulong)param_3;
  if (*(uint *)(param_1 + 0x58) <= param_3) {
    uVar3 = 0;
  }
  plVar4 = (long *)(*(long *)(param_1 + 0x50) + uVar3 * 8);
  plVar2 = (long *)*plVar4;
  do {
    if (plVar2 == (long *)0x0) {
      return 0;
    }
    while (iVar1 = (**(code **)(*plVar2 + 0x20))(plVar2,param_2), -1 < iVar1) {
      if (iVar1 == 0) {
        return *plVar4;
      }
      plVar4 = (long *)(*plVar4 + 0x20);
      plVar2 = (long *)*plVar4;
      if (plVar2 == (long *)0x0) {
        return 0;
      }
    }
    plVar4 = (long *)(*plVar4 + 0x18);
    plVar2 = (long *)*plVar4;
  } while( true );
}

// ==== Aska::TCategorizeHash<Aska::DecodeTextureQueue::TextureMemoryEx>::FreeNode(Aska::DecodeTextureQueue::TextureMemoryEx**)
// vaddr 0x20f8944 | ghidra 0x21f8944 | size 484 | symbol _ZN4Aska15TCategorizeHashINS_18DecodeTextureQueue15TextureMemoryExEE8FreeNodeEPPS2_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska15TCategorizeHashINS_18DecodeTextureQueue15TextureMemoryExEE8FreeNodeEPPS2_
               (long *param_1,ulong *param_2)

{
  long lVar1;
  char cVar2;
  long *plVar3;
  ulong uVar4;
  long *plVar5;
  long lVar6;
  
  uVar4 = *param_2;
  if (uVar4 != 0) {
    if (param_1[0xe] == uVar4) {
      param_1[0xe] = *(long *)(uVar4 + 0x10);
      uVar4 = *param_2;
    }
    if (param_1[0xf] == uVar4) {
      param_1[0xf] = *(long *)(uVar4 + 8);
      uVar4 = *param_2;
    }
    if (param_1[0x10] == uVar4) {
      param_1[0x10] = *(long *)(uVar4 + 8);
      cVar2 = (char)param_1[0x11];
    }
    else {
      cVar2 = (char)param_1[0x11];
    }
    if ((cVar2 == '\0') && (param_1[0x12] == *param_2)) {
      *(undefined4 *)(param_1 + 0x13) = 0;
      param_1[0x12] = 0;
      param_1[0x10] = 0;
      *(undefined1 *)(param_1 + 0x11) = 0;
    }
    lVar6 = *(long *)(*param_2 + 8);
    lVar1 = *(long *)(*param_2 + 0x10);
    if (lVar6 != 0) {
      *(long *)(lVar6 + 0x10) = lVar1;
    }
    if (lVar1 != 0) {
      *(undefined8 *)(lVar1 + 8) = *(undefined8 *)(*param_2 + 8);
    }
    *(undefined8 *)(*param_2 + 0x10) = 0;
    *(undefined8 *)(*param_2 + 8) = 0;
    plVar3 = (long *)*param_2;
    if (plVar3[8] != 0) {
      (**(code **)(*param_1 + 0x18))(param_1);
      plVar3 = (long *)*param_2;
    }
    if (plVar3[4] != 0) {
      (**(code **)(*param_1 + 0x18))(param_1);
      plVar3 = (long *)*param_2;
    }
    if (plVar3[3] != 0) {
      (**(code **)(*param_1 + 0x18))(param_1);
      plVar3 = (long *)*param_2;
    }
    (**(code **)(*plVar3 + 0x18))();
    *(int *)((long)param_1 + 0x8c) = *(int *)((long)param_1 + 0x8c) + -1;
    plVar5 = (long *)param_1[8];
    plVar3 = (long *)*param_2;
    if (((plVar5 == (long *)0x0) || (plVar3 < plVar5)) ||
       (plVar5 + (ulong)*(uint *)((long)param_1 + 0x2c) * 10 <= plVar3)) {
      if (plVar3 != (long *)0x0) {
        (**(code **)(*plVar3 + 8))();
      }
    }
    else {
      uVar4 = ((long)plVar3 - (long)plVar5 >> 4) * -0x3333333333333333;
      (**(code **)plVar5[(uVar4 & 0xffffffff) * 10])();
      lVar6 = (uVar4 >> 5 & 0x7ffffff) * 4;
      *(uint *)(param_1[4] + lVar6) =
           *(uint *)(param_1[4] + lVar6) & (1 << (ulong)((uint)uVar4 & 0x1f) ^ 0xffffffffU);
      *(int *)((long)param_1 + 0x3c) = *(int *)((long)param_1 + 0x3c) + -1;
    }
    *param_2 = 0;
  }
  return;
}

// ==== Aska::TCategorizeHash<Aska::DecodeTextureQueue::TextureMemoryEx>::Regist(void const*)
// vaddr 0x20f8bd8 | ghidra 0x21f8bd8 | size 64 | symbol _ZN4Aska15TCategorizeHashINS_18DecodeTextureQueue15TextureMemoryExEE6RegistEPKv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska15TCategorizeHashINS_18DecodeTextureQueue15TextureMemoryExEE6RegistEPKv
               (long *param_1,undefined8 param_2)

{
  code *UNRECOVERED_JUMPTABLE;
  undefined4 uVar1;
  
  UNRECOVERED_JUMPTABLE = *(code **)(*param_1 + 0x68);
  uVar1 = (**(code **)(*param_1 + 0x60))(param_1);
                    /* WARNING: Could not recover jumptable at 0x021f8c14. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*UNRECOVERED_JUMPTABLE)(param_1,param_2,uVar1);
  return;
}

// ==== Aska::TCategorizeHash<Aska::DecodeTextureQueue::TextureMemoryEx>::Remove(Aska::DecodeTextureQueue::TextureMemoryEx**)
// vaddr 0x20f8c18 | ghidra 0x21f8c18 | size 232 | symbol _ZN4Aska15TCategorizeHashINS_18DecodeTextureQueue15TextureMemoryExEE6RemoveEPPS2_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska15TCategorizeHashINS_18DecodeTextureQueue15TextureMemoryExEE6RemoveEPPS2_
               (long *param_1,long *param_2)

{
  long *plVar1;
  long *plVar2;
  long lVar3;
  long lStack_8;
  
  lStack_8 = *param_2;
  if (lStack_8 == 0) {
    return;
  }
  if (*(long *)(lStack_8 + 0x40) == 0) {
    if (*(long *)(lStack_8 + 0x38) != 0) {
      *param_2 = *(long *)(lStack_8 + 0x38);
      *(undefined8 *)(*(long *)(lStack_8 + 0x38) + 0x40) = 0;
      *(undefined8 *)(lStack_8 + 0x38) = 0;
      goto code_r0x021f8c8c;
    }
    lVar3 = *(long *)(lStack_8 + 0x18);
    if (*(long *)(lStack_8 + 0x20) == 0) {
      *param_2 = lVar3;
      *(undefined8 *)(lStack_8 + 0x18) = 0;
      goto code_r0x021f8c8c;
    }
    plVar1 = (long *)(lStack_8 + 0x18);
    if (lVar3 != 0) {
      do {
        plVar2 = plVar1;
        lVar3 = *plVar2;
        plVar1 = (long *)(lVar3 + 0x20);
      } while (*(long *)(lVar3 + 0x20) != 0);
      *plVar2 = *(long *)(lVar3 + 0x18);
      *(undefined8 *)(lVar3 + 0x18) = *(undefined8 *)(lStack_8 + 0x18);
      *(undefined8 *)(lVar3 + 0x20) = *(undefined8 *)(lStack_8 + 0x20);
      *param_2 = lVar3;
      goto code_r0x021f8c68;
    }
    *param_2 = *(long *)(lStack_8 + 0x20);
  }
  else {
    *param_2 = *(long *)(lStack_8 + 0x40);
    *(undefined8 *)(*(long *)(lStack_8 + 0x40) + 0x38) = *(undefined8 *)(lStack_8 + 0x38);
    if (*(long *)(lStack_8 + 0x38) != 0) {
      *(undefined8 *)(*(long *)(lStack_8 + 0x38) + 0x40) = *(undefined8 *)(lStack_8 + 0x40);
    }
    *(undefined8 *)(*(long *)(lStack_8 + 0x40) + 0x18) = *(undefined8 *)(lStack_8 + 0x18);
    *(undefined8 *)(*(long *)(lStack_8 + 0x40) + 0x20) = *(undefined8 *)(lStack_8 + 0x20);
    *(undefined8 *)(lStack_8 + 0x38) = 0;
    *(undefined8 *)(lStack_8 + 0x40) = 0;
code_r0x021f8c68:
    *(undefined8 *)(lStack_8 + 0x18) = 0;
  }
  *(undefined8 *)(lStack_8 + 0x20) = 0;
code_r0x021f8c8c:
  (**(code **)(*param_1 + 0x18))(param_1,&lStack_8);
  return;
}

// ==== Aska::TCategorizeHash<Aska::DecodeTextureQueue::TextureMemoryEx>::Regist(void const*, unsigned int)
// vaddr 0x20f8dfc | ghidra 0x21f8dfc | size 384 | symbol _ZN4Aska15TCategorizeHashINS_18DecodeTextureQueue15TextureMemoryExEE6RegistEPKvj | lib libSOA-3.7.0.so | 2026-10-04
long * _ZN4Aska15TCategorizeHashINS_18DecodeTextureQueue15TextureMemoryExEE6RegistEPKvj
                 (long *param_1,undefined8 param_2,uint param_3)

{
  int iVar1;
  long *plVar2;
  long lVar3;
  long *plVar4;
  long *plVar5;
  ulong uVar6;
  long *plVar7;
  
  uVar6 = (ulong)param_3;
  if (*(uint *)(param_1 + 0xb) <= param_3) {
    uVar6 = 0;
  }
  plVar4 = (long *)(param_1[10] + uVar6 * 8);
  param_1[0xc] = (long)plVar4;
  plVar2 = (long *)*plVar4;
  while (plVar2 != (long *)0x0) {
    while (iVar1 = (**(code **)(*plVar2 + 0x20))(plVar2,param_2), -1 < iVar1) {
      if (iVar1 == 0) goto code_r0x021f8e8c;
      plVar4 = (long *)(*plVar4 + 0x20);
      plVar2 = (long *)*plVar4;
      if (plVar2 == (long *)0x0) goto code_r0x021f8e70;
    }
    plVar4 = (long *)(*plVar4 + 0x18);
    plVar2 = (long *)*plVar4;
  }
code_r0x021f8e70:
  lVar3 = (**(code **)(*param_1 + 0x10))(param_1,param_2);
  *plVar4 = lVar3;
  plVar2 = (long *)0x0;
  if (lVar3 != 0) {
code_r0x021f8e8c:
    if ((plVar4 == (long *)0x0) || (plVar7 = (long *)*plVar4, plVar7 == (long *)0x0)) {
      plVar2 = (long *)0x0;
    }
    else {
      iVar1 = (**(code **)(*plVar7 + 0x38))(plVar7,param_2);
      while (0 < iVar1) {
        plVar2 = (long *)plVar7[8];
        if (plVar2 == (long *)0x0) {
          plVar4 = (long *)(**(code **)(*param_1 + 0x10))(param_1,param_2);
          if (plVar4 == (long *)0x0) {
            return (long *)0x0;
          }
          plVar4[7] = (long)plVar7;
          plVar7[8] = (long)plVar4;
          return plVar4;
        }
        iVar1 = (**(code **)(*plVar2 + 0x38))(plVar2,param_2);
        plVar7 = plVar2;
      }
      plVar2 = plVar7;
      if ((iVar1 < 0) &&
         (plVar2 = (long *)(**(code **)(*param_1 + 0x10))(param_1,param_2), plVar2 != (long *)0x0))
      {
        plVar2[3] = plVar7[3];
        plVar2[4] = plVar7[4];
        lVar3 = plVar7[7];
        plVar7[3] = 0;
        plVar7[4] = 0;
        plVar2[7] = lVar3;
        plVar2[8] = (long)plVar7;
        plVar5 = plVar7;
        if (lVar3 != 0) {
          *(long **)(lVar3 + 0x40) = plVar2;
          plVar5 = (long *)plVar2[8];
        }
        plVar5[7] = (long)plVar2;
        if ((long *)*plVar4 == plVar7) {
          *plVar4 = (long)plVar2;
        }
      }
    }
  }
  return plVar2;
}

// ==== Aska::TCategorizeHash<Aska::DecodeTextureQueue::TextureMemoryEx>::Remove(void const*, unsigned int)
// vaddr 0x20f8f7c | ghidra 0x21f8f7c | size 200 | symbol _ZN4Aska15TCategorizeHashINS_18DecodeTextureQueue15TextureMemoryExEE6RemoveEPKvj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska15TCategorizeHashINS_18DecodeTextureQueue15TextureMemoryExEE6RemoveEPKvj
               (long *param_1,undefined8 param_2,uint param_3)

{
  int iVar1;
  long *plVar2;
  ulong uVar3;
  long *plVar4;
  
  uVar3 = (ulong)param_3;
  if (*(uint *)(param_1 + 0xb) <= param_3) {
    uVar3 = 0;
  }
  plVar4 = (long *)(param_1[10] + uVar3 * 8);
  param_1[0xc] = (long)plVar4;
  plVar2 = (long *)*plVar4;
  while (plVar2 != (long *)0x0) {
    iVar1 = (**(code **)(*plVar2 + 0x20))(plVar2,param_2);
    if (iVar1 < 0) {
      plVar4 = (long *)(*plVar4 + 0x18);
    }
    else {
      if (iVar1 == 0) goto code_r0x021f8fec;
      plVar4 = (long *)(*plVar4 + 0x20);
    }
    plVar2 = (long *)*plVar4;
  }
code_r0x021f901c:
                    /* WARNING: Could not recover jumptable at 0x021f9034. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*param_1 + 0x40))(param_1,plVar4);
  return;
code_r0x021f8fec:
  plVar2 = (long *)*plVar4;
  if (plVar2 == (long *)0x0) goto code_r0x021f901c;
  iVar1 = (**(code **)(*plVar2 + 0x38))(plVar2,param_2);
  if (iVar1 < 1) {
    if (iVar1 < 0) {
      return;
    }
    goto code_r0x021f901c;
  }
  plVar4 = (long *)(*plVar4 + 0x40);
  goto code_r0x021f8fec;
}

// ==== Aska::TCategorizeHash<Aska::DecodeTextureQueue::TextureMemoryEx>::Search(void const*, unsigned int)
// vaddr 0x20f9064 | ghidra 0x21f9064 | size 180 | symbol _ZN4Aska15TCategorizeHashINS_18DecodeTextureQueue15TextureMemoryExEE6SearchEPKvj | lib libSOA-3.7.0.so | 2026-10-04
long * _ZN4Aska15TCategorizeHashINS_18DecodeTextureQueue15TextureMemoryExEE6SearchEPKvj
                 (long param_1,undefined8 param_2,uint param_3)

{
  int iVar1;
  long *plVar2;
  ulong uVar3;
  long *plVar4;
  
  uVar3 = (ulong)param_3;
  if (*(uint *)(param_1 + 0x58) <= param_3) {
    uVar3 = 0;
  }
  plVar4 = (long *)(*(long *)(param_1 + 0x50) + uVar3 * 8);
  plVar2 = (long *)*plVar4;
  while( true ) {
    while( true ) {
      if (plVar2 == (long *)0x0) {
        return (long *)0x0;
      }
      iVar1 = (**(code **)(*plVar2 + 0x20))(plVar2,param_2);
      if (-1 < iVar1) break;
      plVar4 = (long *)(*plVar4 + 0x18);
      plVar2 = (long *)*plVar4;
    }
    if (iVar1 == 0) break;
    plVar4 = (long *)(*plVar4 + 0x20);
    plVar2 = (long *)*plVar4;
  }
  plVar4 = (long *)*plVar4;
  while( true ) {
    if (plVar4 == (long *)0x0) {
      return (long *)0x0;
    }
    iVar1 = (**(code **)(*plVar4 + 0x38))(plVar4,param_2);
    if (iVar1 == 0) break;
    if (iVar1 < 1) {
      return (long *)0x0;
    }
    plVar4 = (long *)plVar4[8];
  }
  return plVar4;
}

// ==== Aska::THash<Aska::DecodeTextureQueue::DecodeTextureIdIterator>::Remove(Aska::DecodeTextureQueue::DecodeTextureIdIterator**)
// vaddr 0x20fa57c | ghidra 0x21fa57c | size 140 | symbol _ZN4Aska5THashINS_18DecodeTextureQueue23DecodeTextureIdIteratorEE6RemoveEPPS2_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5THashINS_18DecodeTextureQueue23DecodeTextureIdIteratorEE6RemoveEPPS2_
               (long *param_1,long *param_2)

{
  long *plVar1;
  long *plVar2;
  long *plVar3;
  long lVar4;
  long *plVar5;
  long lStack_8;
  
  lStack_8 = *param_2;
  if (lStack_8 != 0) {
    plVar2 = (long *)(lStack_8 + 0x20);
    plVar3 = (long *)(lStack_8 + 0x18);
    if (*plVar2 == 0) {
      *param_2 = *plVar3;
      plVar2 = plVar3;
    }
    else {
      plVar1 = plVar3;
      if (*plVar3 == 0) {
        *param_2 = *plVar2;
      }
      else {
        do {
          plVar5 = plVar1;
          lVar4 = *plVar5;
          plVar1 = (long *)(lVar4 + 0x20);
        } while (*(long *)(lVar4 + 0x20) != 0);
        *plVar5 = *(long *)(lVar4 + 0x18);
        *(long *)(lVar4 + 0x18) = *plVar3;
        *(long *)(lVar4 + 0x20) = *plVar2;
        *param_2 = lVar4;
        *plVar3 = 0;
      }
    }
    *plVar2 = 0;
    (**(code **)(*param_1 + 0x18))(param_1,&lStack_8);
  }
  return;
}

// ==== Aska::THash<Aska::DecodeTextureQueue::DecodeTextureIdIterator>::Regist(void const*, unsigned int)
// vaddr 0x20fa780 | ghidra 0x21fa780 | size 168 | symbol _ZN4Aska5THashINS_18DecodeTextureQueue23DecodeTextureIdIteratorEE6RegistEPKvj | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska5THashINS_18DecodeTextureQueue23DecodeTextureIdIteratorEE6RegistEPKvj
               (long *param_1,undefined8 param_2,uint param_3)

{
  int iVar1;
  long *plVar2;
  long lVar3;
  long lVar4;
  ulong uVar5;
  long *plVar6;
  
  uVar5 = (ulong)param_3;
  if (*(uint *)(param_1 + 0xb) <= param_3) {
    uVar5 = 0;
  }
  plVar6 = (long *)(param_1[10] + uVar5 * 8);
  param_1[0xc] = (long)plVar6;
  plVar2 = (long *)*plVar6;
  while (plVar2 != (long *)0x0) {
    while (iVar1 = (**(code **)(*plVar2 + 0x20))(plVar2,param_2), -1 < iVar1) {
      if (iVar1 == 0) goto code_r0x021fa80c;
      plVar6 = (long *)(*plVar6 + 0x20);
      plVar2 = (long *)*plVar6;
      if (plVar2 == (long *)0x0) goto code_r0x021fa7f0;
    }
    plVar6 = (long *)(*plVar6 + 0x18);
    plVar2 = (long *)*plVar6;
  }
code_r0x021fa7f0:
  lVar3 = (**(code **)(*param_1 + 0x10))(param_1,param_2);
  *plVar6 = lVar3;
  lVar4 = 0;
  if (lVar3 != 0) {
code_r0x021fa80c:
    if (plVar6 == (long *)0x0) {
      lVar4 = 0;
    }
    else {
      lVar4 = *plVar6;
    }
  }
  return lVar4;
}

// ==== Aska::THash<Aska::DecodeTextureQueue::DecodeTextureIdIterator>::Remove(void const*, unsigned int)
// vaddr 0x20fa828 | ghidra 0x21fa828 | size 140 | symbol _ZN4Aska5THashINS_18DecodeTextureQueue23DecodeTextureIdIteratorEE6RemoveEPKvj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5THashINS_18DecodeTextureQueue23DecodeTextureIdIteratorEE6RemoveEPKvj
               (long *param_1,undefined8 param_2,uint param_3)

{
  int iVar1;
  long *plVar2;
  ulong uVar3;
  long *plVar4;
  
  uVar3 = (ulong)param_3;
  if (*(uint *)(param_1 + 0xb) <= param_3) {
    uVar3 = 0;
  }
  plVar4 = (long *)(param_1[10] + uVar3 * 8);
  param_1[0xc] = (long)plVar4;
  plVar2 = (long *)*plVar4;
  while (plVar2 != (long *)0x0) {
    while (iVar1 = (**(code **)(*plVar2 + 0x20))(plVar2,param_2), -1 < iVar1) {
      if (iVar1 == 0) goto code_r0x021fa898;
      plVar4 = (long *)(*plVar4 + 0x20);
      plVar2 = (long *)*plVar4;
      if (plVar2 == (long *)0x0) goto code_r0x021fa898;
    }
    plVar4 = (long *)(*plVar4 + 0x18);
    plVar2 = (long *)*plVar4;
  }
code_r0x021fa898:
                    /* WARNING: Could not recover jumptable at 0x021fa8b0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*param_1 + 0x40))(param_1,plVar4);
  return;
}

// ==== Aska::THash<Aska::DecodeTextureQueue::DecodeTextureIdIterator>::Search(void const*, unsigned int)
// vaddr 0x20fa938 | ghidra 0x21fa938 | size 124 | symbol _ZN4Aska5THashINS_18DecodeTextureQueue23DecodeTextureIdIteratorEE6SearchEPKvj | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska5THashINS_18DecodeTextureQueue23DecodeTextureIdIteratorEE6SearchEPKvj
               (long param_1,undefined8 param_2,uint param_3)

{
  int iVar1;
  long *plVar2;
  ulong uVar3;
  long *plVar4;
  
  uVar3 = (ulong)param_3;
  if (*(uint *)(param_1 + 0x58) <= param_3) {
    uVar3 = 0;
  }
  plVar4 = (long *)(*(long *)(param_1 + 0x50) + uVar3 * 8);
  plVar2 = (long *)*plVar4;
  do {
    if (plVar2 == (long *)0x0) {
      return 0;
    }
    while (iVar1 = (**(code **)(*plVar2 + 0x20))(plVar2,param_2), -1 < iVar1) {
      if (iVar1 == 0) {
        return *plVar4;
      }
      plVar4 = (long *)(*plVar4 + 0x20);
      plVar2 = (long *)*plVar4;
      if (plVar2 == (long *)0x0) {
        return 0;
      }
    }
    plVar4 = (long *)(*plVar4 + 0x18);
    plVar2 = (long *)*plVar4;
  } while( true );
}

// ==== Aska::TCategorizeHash<Aska::DecodeTextureQueue::TextureDecoderIterator>::FreeNode(Aska::DecodeTextureQueue::TextureDecoderIterator**)
// vaddr 0x20fb664 | ghidra 0x21fb664 | size 492 | symbol _ZN4Aska15TCategorizeHashINS_18DecodeTextureQueue22TextureDecoderIteratorEE8FreeNodeEPPS2_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska15TCategorizeHashINS_18DecodeTextureQueue22TextureDecoderIteratorEE8FreeNodeEPPS2_
               (long *param_1,ulong *param_2)

{
  long lVar1;
  char cVar2;
  long *plVar3;
  ulong uVar4;
  long *plVar5;
  long lVar6;
  
  uVar4 = *param_2;
  if (uVar4 != 0) {
    if (param_1[0xe] == uVar4) {
      param_1[0xe] = *(long *)(uVar4 + 0x10);
      uVar4 = *param_2;
    }
    if (param_1[0xf] == uVar4) {
      param_1[0xf] = *(long *)(uVar4 + 8);
      uVar4 = *param_2;
    }
    if (param_1[0x10] == uVar4) {
      param_1[0x10] = *(long *)(uVar4 + 8);
      cVar2 = (char)param_1[0x11];
    }
    else {
      cVar2 = (char)param_1[0x11];
    }
    if ((cVar2 == '\0') && (param_1[0x12] == *param_2)) {
      *(undefined4 *)(param_1 + 0x13) = 0;
      param_1[0x12] = 0;
      param_1[0x10] = 0;
      *(undefined1 *)(param_1 + 0x11) = 0;
    }
    lVar6 = *(long *)(*param_2 + 8);
    lVar1 = *(long *)(*param_2 + 0x10);
    if (lVar6 != 0) {
      *(long *)(lVar6 + 0x10) = lVar1;
    }
    if (lVar1 != 0) {
      *(undefined8 *)(lVar1 + 8) = *(undefined8 *)(*param_2 + 8);
    }
    *(undefined8 *)(*param_2 + 0x10) = 0;
    *(undefined8 *)(*param_2 + 8) = 0;
    plVar3 = (long *)*param_2;
    if (plVar3[9] != 0) {
      (**(code **)(*param_1 + 0x18))(param_1);
      plVar3 = (long *)*param_2;
    }
    if (plVar3[4] != 0) {
      (**(code **)(*param_1 + 0x18))(param_1);
      plVar3 = (long *)*param_2;
    }
    if (plVar3[3] != 0) {
      (**(code **)(*param_1 + 0x18))(param_1);
      plVar3 = (long *)*param_2;
    }
    (**(code **)(*plVar3 + 0x18))();
    *(int *)((long)param_1 + 0x8c) = *(int *)((long)param_1 + 0x8c) + -1;
    plVar5 = (long *)param_1[8];
    plVar3 = (long *)*param_2;
    if (((plVar5 == (long *)0x0) || (plVar3 < plVar5)) ||
       (plVar5 + (ulong)*(uint *)((long)param_1 + 0x2c) * 0xb <= plVar3)) {
      if (plVar3 != (long *)0x0) {
        (**(code **)(*plVar3 + 8))();
      }
    }
    else {
      uVar4 = ((long)plVar3 - (long)plVar5 >> 3) * 0x2e8ba2e8ba2e8ba3;
      (**(code **)plVar5[(uVar4 & 0xffffffff) * 0xb])();
      lVar6 = (uVar4 >> 5 & 0x7ffffff) * 4;
      *(uint *)(param_1[4] + lVar6) =
           *(uint *)(param_1[4] + lVar6) & (1 << (ulong)((uint)uVar4 & 0x1f) ^ 0xffffffffU);
      *(int *)((long)param_1 + 0x3c) = *(int *)((long)param_1 + 0x3c) + -1;
    }
    *param_2 = 0;
  }
  return;
}

// ==== Aska::TCategorizeHash<Aska::DecodeTextureQueue::TextureDecoderIterator>::Remove(Aska::DecodeTextureQueue::TextureDecoderIterator**)
// vaddr 0x20fb990 | ghidra 0x21fb990 | size 232 | symbol _ZN4Aska15TCategorizeHashINS_18DecodeTextureQueue22TextureDecoderIteratorEE6RemoveEPPS2_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska15TCategorizeHashINS_18DecodeTextureQueue22TextureDecoderIteratorEE6RemoveEPPS2_
               (long *param_1,long *param_2)

{
  long *plVar1;
  long *plVar2;
  long lVar3;
  long lStack_8;
  
  lStack_8 = *param_2;
  if (lStack_8 == 0) {
    return;
  }
  if (*(long *)(lStack_8 + 0x48) == 0) {
    if (*(long *)(lStack_8 + 0x40) != 0) {
      *param_2 = *(long *)(lStack_8 + 0x40);
      *(undefined8 *)(*(long *)(lStack_8 + 0x40) + 0x48) = 0;
      *(undefined8 *)(lStack_8 + 0x40) = 0;
      goto code_r0x021fba04;
    }
    lVar3 = *(long *)(lStack_8 + 0x18);
    if (*(long *)(lStack_8 + 0x20) == 0) {
      *param_2 = lVar3;
      *(undefined8 *)(lStack_8 + 0x18) = 0;
      goto code_r0x021fba04;
    }
    plVar1 = (long *)(lStack_8 + 0x18);
    if (lVar3 != 0) {
      do {
        plVar2 = plVar1;
        lVar3 = *plVar2;
        plVar1 = (long *)(lVar3 + 0x20);
      } while (*(long *)(lVar3 + 0x20) != 0);
      *plVar2 = *(long *)(lVar3 + 0x18);
      *(undefined8 *)(lVar3 + 0x18) = *(undefined8 *)(lStack_8 + 0x18);
      *(undefined8 *)(lVar3 + 0x20) = *(undefined8 *)(lStack_8 + 0x20);
      *param_2 = lVar3;
      goto code_r0x021fb9e0;
    }
    *param_2 = *(long *)(lStack_8 + 0x20);
  }
  else {
    *param_2 = *(long *)(lStack_8 + 0x48);
    *(undefined8 *)(*(long *)(lStack_8 + 0x48) + 0x40) = *(undefined8 *)(lStack_8 + 0x40);
    if (*(long *)(lStack_8 + 0x40) != 0) {
      *(undefined8 *)(*(long *)(lStack_8 + 0x40) + 0x48) = *(undefined8 *)(lStack_8 + 0x48);
    }
    *(undefined8 *)(*(long *)(lStack_8 + 0x48) + 0x18) = *(undefined8 *)(lStack_8 + 0x18);
    *(undefined8 *)(*(long *)(lStack_8 + 0x48) + 0x20) = *(undefined8 *)(lStack_8 + 0x20);
    *(undefined8 *)(lStack_8 + 0x40) = 0;
    *(undefined8 *)(lStack_8 + 0x48) = 0;
code_r0x021fb9e0:
    *(undefined8 *)(lStack_8 + 0x18) = 0;
  }
  *(undefined8 *)(lStack_8 + 0x20) = 0;
code_r0x021fba04:
  (**(code **)(*param_1 + 0x18))(param_1,&lStack_8);
  return;
}

// ==== Aska::TCategorizeHash<Aska::DecodeTextureQueue::TextureDecoderIterator>::Regist(void const*, unsigned int)
// vaddr 0x20fbbf0 | ghidra 0x21fbbf0 | size 384 | symbol _ZN4Aska15TCategorizeHashINS_18DecodeTextureQueue22TextureDecoderIteratorEE6RegistEPKvj | lib libSOA-3.7.0.so | 2026-10-04
long * _ZN4Aska15TCategorizeHashINS_18DecodeTextureQueue22TextureDecoderIteratorEE6RegistEPKvj
                 (long *param_1,undefined8 param_2,uint param_3)

{
  int iVar1;
  long *plVar2;
  long lVar3;
  long *plVar4;
  long *plVar5;
  ulong uVar6;
  long *plVar7;
  
  uVar6 = (ulong)param_3;
  if (*(uint *)(param_1 + 0xb) <= param_3) {
    uVar6 = 0;
  }
  plVar4 = (long *)(param_1[10] + uVar6 * 8);
  param_1[0xc] = (long)plVar4;
  plVar2 = (long *)*plVar4;
  while (plVar2 != (long *)0x0) {
    while (iVar1 = (**(code **)(*plVar2 + 0x20))(plVar2,param_2), -1 < iVar1) {
      if (iVar1 == 0) goto code_r0x021fbc80;
      plVar4 = (long *)(*plVar4 + 0x20);
      plVar2 = (long *)*plVar4;
      if (plVar2 == (long *)0x0) goto code_r0x021fbc64;
    }
    plVar4 = (long *)(*plVar4 + 0x18);
    plVar2 = (long *)*plVar4;
  }
code_r0x021fbc64:
  lVar3 = (**(code **)(*param_1 + 0x10))(param_1,param_2);
  *plVar4 = lVar3;
  plVar2 = (long *)0x0;
  if (lVar3 != 0) {
code_r0x021fbc80:
    if ((plVar4 == (long *)0x0) || (plVar7 = (long *)*plVar4, plVar7 == (long *)0x0)) {
      plVar2 = (long *)0x0;
    }
    else {
      iVar1 = (**(code **)(*plVar7 + 0x38))(plVar7,param_2);
      while (0 < iVar1) {
        plVar2 = (long *)plVar7[9];
        if (plVar2 == (long *)0x0) {
          plVar4 = (long *)(**(code **)(*param_1 + 0x10))(param_1,param_2);
          if (plVar4 == (long *)0x0) {
            return (long *)0x0;
          }
          plVar4[8] = (long)plVar7;
          plVar7[9] = (long)plVar4;
          return plVar4;
        }
        iVar1 = (**(code **)(*plVar2 + 0x38))(plVar2,param_2);
        plVar7 = plVar2;
      }
      plVar2 = plVar7;
      if ((iVar1 < 0) &&
         (plVar2 = (long *)(**(code **)(*param_1 + 0x10))(param_1,param_2), plVar2 != (long *)0x0))
      {
        plVar2[3] = plVar7[3];
        plVar2[4] = plVar7[4];
        lVar3 = plVar7[8];
        plVar7[3] = 0;
        plVar7[4] = 0;
        plVar2[8] = lVar3;
        plVar2[9] = (long)plVar7;
        plVar5 = plVar7;
        if (lVar3 != 0) {
          *(long **)(lVar3 + 0x48) = plVar2;
          plVar5 = (long *)plVar2[9];
        }
        plVar5[8] = (long)plVar2;
        if ((long *)*plVar4 == plVar7) {
          *plVar4 = (long)plVar2;
        }
      }
    }
  }
  return plVar2;
}

// ==== Aska::TCategorizeHash<Aska::DecodeTextureQueue::TextureDecoderIterator>::Remove(void const*, unsigned int)
// vaddr 0x20fbd70 | ghidra 0x21fbd70 | size 200 | symbol _ZN4Aska15TCategorizeHashINS_18DecodeTextureQueue22TextureDecoderIteratorEE6RemoveEPKvj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska15TCategorizeHashINS_18DecodeTextureQueue22TextureDecoderIteratorEE6RemoveEPKvj
               (long *param_1,undefined8 param_2,uint param_3)

{
  int iVar1;
  long *plVar2;
  ulong uVar3;
  long *plVar4;
  
  uVar3 = (ulong)param_3;
  if (*(uint *)(param_1 + 0xb) <= param_3) {
    uVar3 = 0;
  }
  plVar4 = (long *)(param_1[10] + uVar3 * 8);
  param_1[0xc] = (long)plVar4;
  plVar2 = (long *)*plVar4;
  while (plVar2 != (long *)0x0) {
    iVar1 = (**(code **)(*plVar2 + 0x20))(plVar2,param_2);
    if (iVar1 < 0) {
      plVar4 = (long *)(*plVar4 + 0x18);
    }
    else {
      if (iVar1 == 0) goto code_r0x021fbde0;
      plVar4 = (long *)(*plVar4 + 0x20);
    }
    plVar2 = (long *)*plVar4;
  }
code_r0x021fbe10:
                    /* WARNING: Could not recover jumptable at 0x021fbe28. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*param_1 + 0x40))(param_1,plVar4);
  return;
code_r0x021fbde0:
  plVar2 = (long *)*plVar4;
  if (plVar2 == (long *)0x0) goto code_r0x021fbe10;
  iVar1 = (**(code **)(*plVar2 + 0x38))(plVar2,param_2);
  if (iVar1 < 1) {
    if (iVar1 < 0) {
      return;
    }
    goto code_r0x021fbe10;
  }
  plVar4 = (long *)(*plVar4 + 0x48);
  goto code_r0x021fbde0;
}

// ==== Aska::TCategorizeHash<Aska::DecodeTextureQueue::TextureMemoryIterator>::FreeNode(Aska::DecodeTextureQueue::TextureMemoryIterator**)
// vaddr 0x20fd200 | ghidra 0x21fd200 | size 492 | symbol _ZN4Aska15TCategorizeHashINS_18DecodeTextureQueue21TextureMemoryIteratorEE8FreeNodeEPPS2_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska15TCategorizeHashINS_18DecodeTextureQueue21TextureMemoryIteratorEE8FreeNodeEPPS2_
               (long *param_1,ulong *param_2)

{
  long lVar1;
  char cVar2;
  long *plVar3;
  ulong uVar4;
  long *plVar5;
  long lVar6;
  
  uVar4 = *param_2;
  if (uVar4 != 0) {
    if (param_1[0xe] == uVar4) {
      param_1[0xe] = *(long *)(uVar4 + 0x10);
      uVar4 = *param_2;
    }
    if (param_1[0xf] == uVar4) {
      param_1[0xf] = *(long *)(uVar4 + 8);
      uVar4 = *param_2;
    }
    if (param_1[0x10] == uVar4) {
      param_1[0x10] = *(long *)(uVar4 + 8);
      cVar2 = (char)param_1[0x11];
    }
    else {
      cVar2 = (char)param_1[0x11];
    }
    if ((cVar2 == '\0') && (param_1[0x12] == *param_2)) {
      *(undefined4 *)(param_1 + 0x13) = 0;
      param_1[0x12] = 0;
      param_1[0x10] = 0;
      *(undefined1 *)(param_1 + 0x11) = 0;
    }
    lVar6 = *(long *)(*param_2 + 8);
    lVar1 = *(long *)(*param_2 + 0x10);
    if (lVar6 != 0) {
      *(long *)(lVar6 + 0x10) = lVar1;
    }
    if (lVar1 != 0) {
      *(undefined8 *)(lVar1 + 8) = *(undefined8 *)(*param_2 + 8);
    }
    *(undefined8 *)(*param_2 + 0x10) = 0;
    *(undefined8 *)(*param_2 + 8) = 0;
    plVar3 = (long *)*param_2;
    if (plVar3[9] != 0) {
      (**(code **)(*param_1 + 0x18))(param_1);
      plVar3 = (long *)*param_2;
    }
    if (plVar3[4] != 0) {
      (**(code **)(*param_1 + 0x18))(param_1);
      plVar3 = (long *)*param_2;
    }
    if (plVar3[3] != 0) {
      (**(code **)(*param_1 + 0x18))(param_1);
      plVar3 = (long *)*param_2;
    }
    (**(code **)(*plVar3 + 0x18))();
    *(int *)((long)param_1 + 0x8c) = *(int *)((long)param_1 + 0x8c) + -1;
    plVar5 = (long *)param_1[8];
    plVar3 = (long *)*param_2;
    if (((plVar5 == (long *)0x0) || (plVar3 < plVar5)) ||
       (plVar5 + (ulong)*(uint *)((long)param_1 + 0x2c) * 0xb <= plVar3)) {
      if (plVar3 != (long *)0x0) {
        (**(code **)(*plVar3 + 8))();
      }
    }
    else {
      uVar4 = ((long)plVar3 - (long)plVar5 >> 3) * 0x2e8ba2e8ba2e8ba3;
      (**(code **)plVar5[(uVar4 & 0xffffffff) * 0xb])();
      lVar6 = (uVar4 >> 5 & 0x7ffffff) * 4;
      *(uint *)(param_1[4] + lVar6) =
           *(uint *)(param_1[4] + lVar6) & (1 << (ulong)((uint)uVar4 & 0x1f) ^ 0xffffffffU);
      *(int *)((long)param_1 + 0x3c) = *(int *)((long)param_1 + 0x3c) + -1;
    }
    *param_2 = 0;
  }
  return;
}

// ==== Aska::TCategorizeHash<Aska::DecodeTextureQueue::TextureMemoryIterator>::Remove(Aska::DecodeTextureQueue::TextureMemoryIterator**)
// vaddr 0x20fd52c | ghidra 0x21fd52c | size 232 | symbol _ZN4Aska15TCategorizeHashINS_18DecodeTextureQueue21TextureMemoryIteratorEE6RemoveEPPS2_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska15TCategorizeHashINS_18DecodeTextureQueue21TextureMemoryIteratorEE6RemoveEPPS2_
               (long *param_1,long *param_2)

{
  long *plVar1;
  long *plVar2;
  long lVar3;
  long lStack_8;
  
  lStack_8 = *param_2;
  if (lStack_8 == 0) {
    return;
  }
  if (*(long *)(lStack_8 + 0x48) == 0) {
    if (*(long *)(lStack_8 + 0x40) != 0) {
      *param_2 = *(long *)(lStack_8 + 0x40);
      *(undefined8 *)(*(long *)(lStack_8 + 0x40) + 0x48) = 0;
      *(undefined8 *)(lStack_8 + 0x40) = 0;
      goto code_r0x021fd5a0;
    }
    lVar3 = *(long *)(lStack_8 + 0x18);
    if (*(long *)(lStack_8 + 0x20) == 0) {
      *param_2 = lVar3;
      *(undefined8 *)(lStack_8 + 0x18) = 0;
      goto code_r0x021fd5a0;
    }
    plVar1 = (long *)(lStack_8 + 0x18);
    if (lVar3 != 0) {
      do {
        plVar2 = plVar1;
        lVar3 = *plVar2;
        plVar1 = (long *)(lVar3 + 0x20);
      } while (*(long *)(lVar3 + 0x20) != 0);
      *plVar2 = *(long *)(lVar3 + 0x18);
      *(undefined8 *)(lVar3 + 0x18) = *(undefined8 *)(lStack_8 + 0x18);
      *(undefined8 *)(lVar3 + 0x20) = *(undefined8 *)(lStack_8 + 0x20);
      *param_2 = lVar3;
      goto code_r0x021fd57c;
    }
    *param_2 = *(long *)(lStack_8 + 0x20);
  }
  else {
    *param_2 = *(long *)(lStack_8 + 0x48);
    *(undefined8 *)(*(long *)(lStack_8 + 0x48) + 0x40) = *(undefined8 *)(lStack_8 + 0x40);
    if (*(long *)(lStack_8 + 0x40) != 0) {
      *(undefined8 *)(*(long *)(lStack_8 + 0x40) + 0x48) = *(undefined8 *)(lStack_8 + 0x48);
    }
    *(undefined8 *)(*(long *)(lStack_8 + 0x48) + 0x18) = *(undefined8 *)(lStack_8 + 0x18);
    *(undefined8 *)(*(long *)(lStack_8 + 0x48) + 0x20) = *(undefined8 *)(lStack_8 + 0x20);
    *(undefined8 *)(lStack_8 + 0x40) = 0;
    *(undefined8 *)(lStack_8 + 0x48) = 0;
code_r0x021fd57c:
    *(undefined8 *)(lStack_8 + 0x18) = 0;
  }
  *(undefined8 *)(lStack_8 + 0x20) = 0;
code_r0x021fd5a0:
  (**(code **)(*param_1 + 0x18))(param_1,&lStack_8);
  return;
}

// ==== Aska::TCategorizeHash<Aska::DecodeTextureQueue::TextureMemoryIterator>::Regist(void const*, unsigned int)
// vaddr 0x20fd7ec | ghidra 0x21fd7ec | size 384 | symbol _ZN4Aska15TCategorizeHashINS_18DecodeTextureQueue21TextureMemoryIteratorEE6RegistEPKvj | lib libSOA-3.7.0.so | 2026-10-04
long * _ZN4Aska15TCategorizeHashINS_18DecodeTextureQueue21TextureMemoryIteratorEE6RegistEPKvj
                 (long *param_1,undefined8 param_2,uint param_3)

{
  int iVar1;
  long *plVar2;
  long lVar3;
  long *plVar4;
  long *plVar5;
  ulong uVar6;
  long *plVar7;
  
  uVar6 = (ulong)param_3;
  if (*(uint *)(param_1 + 0xb) <= param_3) {
    uVar6 = 0;
  }
  plVar4 = (long *)(param_1[10] + uVar6 * 8);
  param_1[0xc] = (long)plVar4;
  plVar2 = (long *)*plVar4;
  while (plVar2 != (long *)0x0) {
    while (iVar1 = (**(code **)(*plVar2 + 0x20))(plVar2,param_2), -1 < iVar1) {
      if (iVar1 == 0) goto code_r0x021fd87c;
      plVar4 = (long *)(*plVar4 + 0x20);
      plVar2 = (long *)*plVar4;
      if (plVar2 == (long *)0x0) goto code_r0x021fd860;
    }
    plVar4 = (long *)(*plVar4 + 0x18);
    plVar2 = (long *)*plVar4;
  }
code_r0x021fd860:
  lVar3 = (**(code **)(*param_1 + 0x10))(param_1,param_2);
  *plVar4 = lVar3;
  plVar2 = (long *)0x0;
  if (lVar3 != 0) {
code_r0x021fd87c:
    if ((plVar4 == (long *)0x0) || (plVar7 = (long *)*plVar4, plVar7 == (long *)0x0)) {
      plVar2 = (long *)0x0;
    }
    else {
      iVar1 = (**(code **)(*plVar7 + 0x38))(plVar7,param_2);
      while (0 < iVar1) {
        plVar2 = (long *)plVar7[9];
        if (plVar2 == (long *)0x0) {
          plVar4 = (long *)(**(code **)(*param_1 + 0x10))(param_1,param_2);
          if (plVar4 == (long *)0x0) {
            return (long *)0x0;
          }
          plVar4[8] = (long)plVar7;
          plVar7[9] = (long)plVar4;
          return plVar4;
        }
        iVar1 = (**(code **)(*plVar2 + 0x38))(plVar2,param_2);
        plVar7 = plVar2;
      }
      plVar2 = plVar7;
      if ((iVar1 < 0) &&
         (plVar2 = (long *)(**(code **)(*param_1 + 0x10))(param_1,param_2), plVar2 != (long *)0x0))
      {
        plVar2[3] = plVar7[3];
        plVar2[4] = plVar7[4];
        lVar3 = plVar7[8];
        plVar7[3] = 0;
        plVar7[4] = 0;
        plVar2[8] = lVar3;
        plVar2[9] = (long)plVar7;
        plVar5 = plVar7;
        if (lVar3 != 0) {
          *(long **)(lVar3 + 0x48) = plVar2;
          plVar5 = (long *)plVar2[9];
        }
        plVar5[8] = (long)plVar2;
        if ((long *)*plVar4 == plVar7) {
          *plVar4 = (long)plVar2;
        }
      }
    }
  }
  return plVar2;
}

// ==== Aska::TCategorizeHash<Aska::DecodeTextureQueue::TextureMemoryIterator>::Remove(void const*, unsigned int)
// vaddr 0x20fd96c | ghidra 0x21fd96c | size 200 | symbol _ZN4Aska15TCategorizeHashINS_18DecodeTextureQueue21TextureMemoryIteratorEE6RemoveEPKvj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska15TCategorizeHashINS_18DecodeTextureQueue21TextureMemoryIteratorEE6RemoveEPKvj
               (long *param_1,undefined8 param_2,uint param_3)

{
  int iVar1;
  long *plVar2;
  ulong uVar3;
  long *plVar4;
  
  uVar3 = (ulong)param_3;
  if (*(uint *)(param_1 + 0xb) <= param_3) {
    uVar3 = 0;
  }
  plVar4 = (long *)(param_1[10] + uVar3 * 8);
  param_1[0xc] = (long)plVar4;
  plVar2 = (long *)*plVar4;
  while (plVar2 != (long *)0x0) {
    iVar1 = (**(code **)(*plVar2 + 0x20))(plVar2,param_2);
    if (iVar1 < 0) {
      plVar4 = (long *)(*plVar4 + 0x18);
    }
    else {
      if (iVar1 == 0) goto code_r0x021fd9dc;
      plVar4 = (long *)(*plVar4 + 0x20);
    }
    plVar2 = (long *)*plVar4;
  }
code_r0x021fda0c:
                    /* WARNING: Could not recover jumptable at 0x021fda24. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*param_1 + 0x40))(param_1,plVar4);
  return;
code_r0x021fd9dc:
  plVar2 = (long *)*plVar4;
  if (plVar2 == (long *)0x0) goto code_r0x021fda0c;
  iVar1 = (**(code **)(*plVar2 + 0x38))(plVar2,param_2);
  if (iVar1 < 1) {
    if (iVar1 < 0) {
      return;
    }
    goto code_r0x021fda0c;
  }
  plVar4 = (long *)(*plVar4 + 0x48);
  goto code_r0x021fd9dc;
}

// ==== Aska::THashSet<Aska::ShaderKeyValue*, Aska::THasher_StateKey<Aska::ShaderKeyValue*>, Aska::TEqualTo_StateKey<Aska::ShaderKeyValue*>, Aska::TAllocator<Aska::ShaderKeyValue*> >::Rehash_(unsigned long)
// vaddr 0x217ffe0 | ghidra 0x227ffe0 | size 468 | symbol _ZN4Aska8THashSetIPNS_14ShaderKeyValueENS_16THasher_StateKeyIS2_EENS_17TEqualTo_StateKeyIS2_EENS_10TAllocatorIS2_EEE7Rehash_Em | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska8THashSetIPNS_14ShaderKeyValueENS_16THasher_StateKeyIS2_EENS_17TEqualTo_StateKeyIS2_EENS_10TAllocatorIS2_EEE7Rehash_Em
               (undefined1 *param_1,ulong param_2)

{
  ulong uVar1;
  undefined *puVar2;
  undefined1 *puVar3;
  undefined8 uVar5;
  char *pcVar6;
  ulong uVar7;
  long lVar8;
  ulong uVar9;
  float fVar10;
  float fVar11;
  undefined *puStack_90;
  float fStack_84;
  undefined4 uStack_80;
  undefined4 uStack_7c;
  undefined1 *puStack_70;
  ulong uStack_68;
  char *pcStack_60;
  char *pcStack_58;
  char *pcStack_50;
  char *pcStack_48;
  char *pcStack_40;
  char *pcStack_38;
  undefined1 *puVar4;
  
  puVar2 = 
  PTR__ZTVN4Aska8THashSetIPNS_14ShaderKeyValueENS_16THasher_StateKeyIS2_EENS_17TEqualTo_StateKeyIS2_EENS_10TAllocatorIS2_EEEE_02cba260
  ;
  puStack_90 = PTR__ZTVN4Aska8THashSetIPNS_14ShaderKeyValueENS_16THasher_StateKeyIS2_EENS_17TEqualTo_StateKeyIS2_EENS_10TAllocatorIS2_EEEE_02cba260
               + 0x10;
  fStack_84 = 0.75;
  uStack_80 = 0;
  uStack_7c = 0;
  if (param_2 >> 0x3c == 0) {
    puStack_70 = (undefined1 *)Aska::MemoryManagerAdapter::AlignedMalloc(unsigned long, unsigned long)(param_2 << 4,8);
  }
  else {
    puStack_70 = (undefined1 *)0x0;
  }
  if (puStack_70 == (undefined1 *)0x0) {
    param_2 = 0;
  }
  if (param_2 == 0) {
    fVar10 = *(float *)(param_1 + 0xc);
code_r0x022800d0:
    if (fVar10 <= 0.0) goto code_r0x022800e0;
  }
  else {
    uVar1 = (param_2 * 0x10 - 0x10 >> 4) + 1;
    puVar4 = puStack_70;
    if ((uVar1 < 2) || (uVar7 = uVar1 & 0x1ffffffffffffffe, uVar7 == 0)) {
code_r0x0228008c:
      do {
        puVar3 = puVar4 + 0x10;
        *puVar4 = 0;
        puVar4 = puVar3;
      } while (puStack_70 + param_2 * 0x10 != puVar3);
    }
    else {
      puVar4 = puStack_70 + uVar7 * 0x10;
      puVar3 = puStack_70 + 0x10;
      uVar9 = uVar7;
      do {
        puVar3[-0x10] = 0;
        *puVar3 = 0;
        uVar9 = uVar9 - 2;
        puVar3 = puVar3 + 0x20;
      } while (uVar9 != 0);
      if (uVar1 != uVar7) goto code_r0x0228008c;
    }
    fVar10 = *(float *)(param_1 + 0xc);
    if (param_2 == 0) goto code_r0x022800d0;
    fVar11 = (float)NEON_ucvtf(uStack_80);
    if (fVar10 <= fVar11 / (float)param_2) goto code_r0x022800e0;
  }
  fStack_84 = fVar10;
code_r0x022800e0:
  pcStack_58 = *(char **)(param_1 + 0x20);
  lVar8 = *(long *)(param_1 + 0x28);
  pcStack_60 = pcStack_58 + lVar8 * 0x10;
  pcStack_48 = pcStack_60;
  if ((*(int *)(param_1 + 0x10) != 0) && (pcStack_48 = pcStack_58, lVar8 != 0)) {
    lVar8 = lVar8 << 4;
    pcVar6 = pcStack_58;
    do {
      pcStack_48 = pcVar6;
      if (*pcVar6 == '\x01') break;
      lVar8 = lVar8 + -0x10;
      pcVar6 = pcVar6 + 0x10;
      pcStack_48 = pcStack_60;
    } while (lVar8 != 0);
  }
  uStack_68 = param_2;
  pcStack_50 = pcStack_60;
  pcStack_40 = pcStack_58;
  pcStack_38 = pcStack_60;
  void Aska::THashSet<Aska::ShaderKeyValue*, Aska::THasher_StateKey<Aska::ShaderKeyValue*>, Aska::TEqualTo_StateKey<Aska::ShaderKeyValue*>, Aska::TAllocator<Aska::ShaderKeyValue*> >::Insert<Aska::THashMapIterator<Aska::detail::THashMapBucketArray<Aska::detail::THashMapBucket<Aska::ShaderKeyValue*>, Aska::TAllocator<Aska::detail::THashMapBucket<Aska::ShaderKeyValue*> > > > >(Aska::THashMapIterator<Aska::detail::THashMapBucketArray<Aska::detail::THashMapBucket<Aska::ShaderKeyValue*>, Aska::TAllocator<Aska::detail::THashMapBucket<Aska::ShaderKeyValue*> > > >, Aska::THashMapIterator<Aska::detail::THashMapBucketArray<Aska::detail::THashMapBucket<Aska::ShaderKeyValue*>, Aska::TAllocator<Aska::detail::THashMapBucket<Aska::ShaderKeyValue*> > > >)(&puStack_90,&pcStack_48,&pcStack_60);
  if (&puStack_90 != (undefined **)param_1) {
    uVar5 = *(undefined8 *)(param_1 + 0x10);
    *(ulong *)(param_1 + 0x10) = CONCAT44(uStack_7c,uStack_80);
    uStack_80 = (undefined4)uVar5;
    uStack_7c = (undefined4)((ulong)uVar5 >> 0x20);
    puVar4 = *(undefined1 **)(param_1 + 0x20);
    uVar1 = *(ulong *)(param_1 + 0x28);
    *(ulong *)(param_1 + 0x28) = uStack_68;
    *(undefined1 **)(param_1 + 0x20) = puStack_70;
    fVar10 = *(float *)(param_1 + 0xc);
    *(float *)(param_1 + 0xc) = fStack_84;
    fStack_84 = fVar10;
    puStack_70 = puVar4;
    uStack_68 = uVar1;
  }
  puStack_90 = puVar2 + 0x10;
  if (puStack_70 != (undefined1 *)0x0) {
    Aska::MemoryManagerAdapter::AlignedFree(void*)();
  }
  return;
}

// ==== void Aska::THashSet<Aska::ShaderKeyValue*, Aska::THasher_StateKey<Aska::ShaderKeyValue*>, Aska::TEqualTo_StateKey<Aska::ShaderKeyValue*>, Aska::TAllocator<Aska::ShaderKeyValue*> >::Insert<Aska::THashMapIterator<Aska::detail::THashMapBucketArray<Aska::detail::THashMapBucket<Aska::ShaderKeyValue*>, Aska::TAllocator<Aska::detail::THashMapBucket<Aska::ShaderKeyValue*> > > > >(Aska::THashMapIterator<Aska::detail::THashMapBucketArray<Aska::detail::THashMapBucket<Aska::ShaderKeyValue*>, Aska::TAllocator<Aska::detail::THashMapBucket<Aska::ShaderKeyValue*> > > >, Aska::THashMapIterator<Aska::detail::THashMapBucketArray<Aska::detail::THashMapBucket<Aska::ShaderKeyValue*>, Aska::TAllocator<Aska::detail::THashMapBucket<Aska::ShaderKeyValue*> > > >)
// vaddr 0x2180224 | ghidra 0x2280224 | size 488 | symbol _ZN4Aska8THashSetIPNS_14ShaderKeyValueENS_16THasher_StateKeyIS2_EENS_17TEqualTo_StateKeyIS2_EENS_10TAllocatorIS2_EEE6InsertINS_16THashMapIteratorINS_6detail19THashMapBucketArrayINSC_14THashMapBucketIS2_EENS7_ISF_EEEEEEEEvT_SJ_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska8THashSetIPNS_14ShaderKeyValueENS_16THasher_StateKeyIS2_EENS_17TEqualTo_StateKeyIS2_EENS_10TAllocatorIS2_EEE6InsertINS_16THashMapIteratorINS_6detail19THashMapBucketArrayINSC_14THashMapBucketIS2_EENS7_ISF_EEEEEEEEvT_SJ_
               (long param_1,long *param_2,undefined8 *param_3)

{
  char cVar1;
  ulong uVar2;
  char *pcVar3;
  int iVar4;
  char *pcVar5;
  long lVar6;
  ulong uVar7;
  char *pcVar8;
  char *pcVar9;
  long *plVar10;
  long lVar11;
  ulong uVar12;
  
  pcVar9 = (char *)*param_2;
  pcVar5 = (char *)*param_3;
  lVar6 = 0;
  if (pcVar9 != pcVar5) {
    pcVar8 = pcVar9;
    do {
      lVar6 = lVar6 + 1;
      do {
        pcVar3 = (char *)param_2[2];
        if ((char *)param_2[2] == pcVar8) break;
        pcVar8 = pcVar8 + 0x10;
        pcVar3 = pcVar8;
      } while (*pcVar8 != '\x01');
      pcVar8 = pcVar3;
    } while (pcVar8 != pcVar5);
  }
  uVar7 = (ulong)((float)(lVar6 + (ulong)*(uint *)(param_1 + 0x10) +
                         (ulong)*(uint *)(param_1 + 0x14)) / *(float *)(param_1 + 0xc));
  if (*(ulong *)(param_1 + 0x28) < uVar7) {
    Aska::THashSet<Aska::ShaderKeyValue*, Aska::THasher_StateKey<Aska::ShaderKeyValue*>, Aska::TEqualTo_StateKey<Aska::ShaderKeyValue*>, Aska::TAllocator<Aska::ShaderKeyValue*> >::Rehash_(unsigned long)(param_1,uVar7 << 1 | 1);
    pcVar9 = (char *)*param_2;
    pcVar5 = (char *)*param_3;
  }
  if (pcVar9 != pcVar5) {
    do {
      uVar7 = *(ulong *)(param_1 + 0x28);
      if (uVar7 != 0) {
        plVar10 = *(long **)(pcVar9 + 8);
        lVar6 = *(long *)(param_1 + 0x20);
        uVar12 = 0;
        lVar11 = *plVar10;
        pcVar5 = (char *)0x0;
        do {
          uVar2 = 0;
          if (uVar7 != 0) {
            uVar2 = (lVar11 + uVar12) / uVar7;
          }
          pcVar8 = (char *)(lVar6 + ((lVar11 + uVar12) - uVar2 * uVar7) * 0x10);
          cVar1 = *pcVar8;
          if (cVar1 == '\x01') {
            if ((*(int *)(*(long *)(pcVar8 + 8) + 0x18) == (int)plVar10[3]) &&
               (iVar4 = memcmp(*(undefined8 *)(*(long *)(pcVar8 + 8) + 0x10),plVar10[2]),
               iVar4 == 0)) goto code_r0x022803ac;
          }
          else if (cVar1 == '\0') {
            if (pcVar5 != (char *)0x0) {
              pcVar8 = pcVar5;
            }
            break;
          }
          uVar12 = uVar12 + 1;
          if (cVar1 != '\x02' || pcVar5 != (char *)0x0) {
            pcVar8 = pcVar5;
          }
          pcVar5 = pcVar8;
        } while (uVar12 < uVar7);
        if (pcVar8 != (char *)0x0) {
          *(long **)(pcVar8 + 8) = plVar10;
          if (*pcVar8 == '\0') {
code_r0x02280394:
            *(int *)(param_1 + 0x10) = *(int *)(param_1 + 0x10) + 1;
          }
          else if (*pcVar8 == '\x02') {
            *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + -1;
            goto code_r0x02280394;
          }
          *pcVar8 = '\x01';
          pcVar9 = (char *)*param_2;
        }
      }
code_r0x022803ac:
      pcVar5 = pcVar9;
      do {
        pcVar9 = (char *)param_2[2];
        if ((char *)param_2[2] == pcVar5) break;
        pcVar9 = pcVar5 + 0x10;
        *param_2 = (long)pcVar9;
        pcVar8 = pcVar5 + 0x10;
        pcVar5 = pcVar9;
      } while (*pcVar8 != '\x01');
    } while (pcVar9 != (char *)*param_3);
  }
  return;
}

// ==== Aska::THashSet<Aska::ShaderProgramValue*, Aska::THasher_StateKey<Aska::ShaderProgramValue*>, Aska::TEqualTo_StateKey<Aska::ShaderProgramValue*>, Aska::TAllocator<Aska::ShaderProgramValue*> >::Insert(Aska::ShaderProgramValue* const&)
// vaddr 0x2180838 | ghidra 0x2280838 | size 332 | symbol _ZN4Aska8THashSetIPNS_18ShaderProgramValueENS_16THasher_StateKeyIS2_EENS_17TEqualTo_StateKeyIS2_EENS_10TAllocatorIS2_EEE6InsertERKS2_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska8THashSetIPNS_18ShaderProgramValueENS_16THasher_StateKeyIS2_EENS_17TEqualTo_StateKeyIS2_EENS_10TAllocatorIS2_EEE6InsertERKS2_
               (undefined8 *param_1,long param_2,long *param_3)

{
  char cVar1;
  ulong uVar2;
  long lVar3;
  ulong uVar4;
  char *pcVar5;
  char *pcVar6;
  ulong uVar7;
  undefined1 uVar8;
  
  uVar7 = *(ulong *)(param_2 + 0x28);
  uVar4 = (ulong)((float)((ulong)*(uint *)(param_2 + 0x10) + (ulong)*(uint *)(param_2 + 0x14) + 1) /
                 *(float *)(param_2 + 0xc));
  if (uVar7 < uVar4) {
    Aska::THashSet<Aska::ShaderProgramValue*, Aska::THasher_StateKey<Aska::ShaderProgramValue*>, Aska::TEqualTo_StateKey<Aska::ShaderProgramValue*>, Aska::TAllocator<Aska::ShaderProgramValue*> >::Rehash_(unsigned long)(param_2,uVar4 << 1 | 1);
    uVar7 = *(ulong *)(param_2 + 0x28);
  }
  lVar3 = *(long *)(param_2 + 0x20);
  if (uVar7 != 0) {
    param_3 = (long *)*param_3;
    uVar4 = 0;
    pcVar5 = (char *)0x0;
    do {
      uVar2 = 0;
      if (uVar7 != 0) {
        uVar2 = (*param_3 + uVar4) / uVar7;
      }
      pcVar6 = (char *)(lVar3 + ((*param_3 + uVar4) - uVar2 * uVar7) * 0x10);
      cVar1 = *pcVar6;
      if (cVar1 == '\x01') {
        if ((*(long *)(*(long *)(pcVar6 + 8) + 8) == param_3[1]) &&
           (*(long *)(*(long *)(pcVar6 + 8) + 0x10) == param_3[2])) {
          uVar8 = 0;
          pcVar5 = (char *)(lVar3 + uVar7 * 0x10);
          goto code_r0x0228095c;
        }
      }
      else if (cVar1 == '\0') {
        if (pcVar5 != (char *)0x0) {
          pcVar6 = pcVar5;
        }
        if (pcVar6 == (char *)0x0) goto code_r0x02280950;
        goto code_r0x02280904;
      }
      uVar4 = uVar4 + 1;
      if (cVar1 != '\x02' || pcVar5 != (char *)0x0) {
        pcVar6 = pcVar5;
      }
      pcVar5 = pcVar6;
    } while (uVar4 < uVar7);
    if (pcVar6 != (char *)0x0) {
code_r0x02280904:
      *(long **)(pcVar6 + 8) = param_3;
      if (*pcVar6 == '\0') {
code_r0x02280924:
        *(int *)(param_2 + 0x10) = *(int *)(param_2 + 0x10) + 1;
      }
      else if (*pcVar6 == '\x02') {
        *(int *)(param_2 + 0x14) = *(int *)(param_2 + 0x14) + -1;
        goto code_r0x02280924;
      }
      uVar8 = 1;
      *pcVar6 = '\x01';
      pcVar5 = (char *)(lVar3 + *(long *)(param_2 + 0x28) * 0x10);
      goto code_r0x0228095c;
    }
  }
code_r0x02280950:
  pcVar6 = (char *)(lVar3 + uVar7 * 0x10);
  uVar8 = 0;
  pcVar5 = pcVar6;
code_r0x0228095c:
  *param_1 = pcVar6;
  param_1[1] = lVar3;
  param_1[2] = pcVar5;
  *(undefined1 *)(param_1 + 3) = uVar8;
  return;
}

// ==== Aska::THashSet<Aska::ShaderProgramValue*, Aska::THasher_StateKey<Aska::ShaderProgramValue*>, Aska::TEqualTo_StateKey<Aska::ShaderProgramValue*>, Aska::TAllocator<Aska::ShaderProgramValue*> >::Rehash_(unsigned long)
// vaddr 0x2180984 | ghidra 0x2280984 | size 468 | symbol _ZN4Aska8THashSetIPNS_18ShaderProgramValueENS_16THasher_StateKeyIS2_EENS_17TEqualTo_StateKeyIS2_EENS_10TAllocatorIS2_EEE7Rehash_Em | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska8THashSetIPNS_18ShaderProgramValueENS_16THasher_StateKeyIS2_EENS_17TEqualTo_StateKeyIS2_EENS_10TAllocatorIS2_EEE7Rehash_Em
               (undefined1 *param_1,ulong param_2)

{
  ulong uVar1;
  undefined *puVar2;
  undefined1 *puVar3;
  undefined8 uVar5;
  char *pcVar6;
  ulong uVar7;
  long lVar8;
  ulong uVar9;
  float fVar10;
  float fVar11;
  undefined *puStack_90;
  float fStack_84;
  undefined4 uStack_80;
  undefined4 uStack_7c;
  undefined1 *puStack_70;
  ulong uStack_68;
  char *pcStack_60;
  char *pcStack_58;
  char *pcStack_50;
  char *pcStack_48;
  char *pcStack_40;
  char *pcStack_38;
  undefined1 *puVar4;
  
  puVar2 = 
  PTR__ZTVN4Aska8THashSetIPNS_18ShaderProgramValueENS_16THasher_StateKeyIS2_EENS_17TEqualTo_StateKeyIS2_EENS_10TAllocatorIS2_EEEE_02cc0ab0
  ;
  puStack_90 = PTR__ZTVN4Aska8THashSetIPNS_18ShaderProgramValueENS_16THasher_StateKeyIS2_EENS_17TEqualTo_StateKeyIS2_EENS_10TAllocatorIS2_EEEE_02cc0ab0
               + 0x10;
  fStack_84 = 0.75;
  uStack_80 = 0;
  uStack_7c = 0;
  if (param_2 >> 0x3c == 0) {
    puStack_70 = (undefined1 *)Aska::MemoryManagerAdapter::AlignedMalloc(unsigned long, unsigned long)(param_2 << 4,8);
  }
  else {
    puStack_70 = (undefined1 *)0x0;
  }
  if (puStack_70 == (undefined1 *)0x0) {
    param_2 = 0;
  }
  if (param_2 == 0) {
    fVar10 = *(float *)(param_1 + 0xc);
code_r0x02280a74:
    if (fVar10 <= 0.0) goto code_r0x02280a84;
  }
  else {
    uVar1 = (param_2 * 0x10 - 0x10 >> 4) + 1;
    puVar4 = puStack_70;
    if ((uVar1 < 2) || (uVar7 = uVar1 & 0x1ffffffffffffffe, uVar7 == 0)) {
code_r0x02280a30:
      do {
        puVar3 = puVar4 + 0x10;
        *puVar4 = 0;
        puVar4 = puVar3;
      } while (puStack_70 + param_2 * 0x10 != puVar3);
    }
    else {
      puVar4 = puStack_70 + uVar7 * 0x10;
      puVar3 = puStack_70 + 0x10;
      uVar9 = uVar7;
      do {
        puVar3[-0x10] = 0;
        *puVar3 = 0;
        uVar9 = uVar9 - 2;
        puVar3 = puVar3 + 0x20;
      } while (uVar9 != 0);
      if (uVar1 != uVar7) goto code_r0x02280a30;
    }
    fVar10 = *(float *)(param_1 + 0xc);
    if (param_2 == 0) goto code_r0x02280a74;
    fVar11 = (float)NEON_ucvtf(uStack_80);
    if (fVar10 <= fVar11 / (float)param_2) goto code_r0x02280a84;
  }
  fStack_84 = fVar10;
code_r0x02280a84:
  pcStack_58 = *(char **)(param_1 + 0x20);
  lVar8 = *(long *)(param_1 + 0x28);
  pcStack_60 = pcStack_58 + lVar8 * 0x10;
  pcStack_48 = pcStack_60;
  if ((*(int *)(param_1 + 0x10) != 0) && (pcStack_48 = pcStack_58, lVar8 != 0)) {
    lVar8 = lVar8 << 4;
    pcVar6 = pcStack_58;
    do {
      pcStack_48 = pcVar6;
      if (*pcVar6 == '\x01') break;
      lVar8 = lVar8 + -0x10;
      pcVar6 = pcVar6 + 0x10;
      pcStack_48 = pcStack_60;
    } while (lVar8 != 0);
  }
  uStack_68 = param_2;
  pcStack_50 = pcStack_60;
  pcStack_40 = pcStack_58;
  pcStack_38 = pcStack_60;
  void Aska::THashSet<Aska::ShaderProgramValue*, Aska::THasher_StateKey<Aska::ShaderProgramValue*>, Aska::TEqualTo_StateKey<Aska::ShaderProgramValue*>, Aska::TAllocator<Aska::ShaderProgramValue*> >::Insert<Aska::THashMapIterator<Aska::detail::THashMapBucketArray<Aska::detail::THashMapBucket<Aska::ShaderProgramValue*>, Aska::TAllocator<Aska::detail::THashMapBucket<Aska::ShaderProgramValue*> > > > >(Aska::THashMapIterator<Aska::detail::THashMapBucketArray<Aska::detail::THashMapBucket<Aska::ShaderProgramValue*>, Aska::TAllocator<Aska::detail::THashMapBucket<Aska::ShaderProgramValue*> > > >, Aska::THashMapIterator<Aska::detail::THashMapBucketArray<Aska::detail::THashMapBucket<Aska::ShaderProgramValue*>, Aska::TAllocator<Aska::detail::THashMapBucket<Aska::ShaderProgramValue*> > > >)(&puStack_90,&pcStack_48,&pcStack_60);
  if (&puStack_90 != (undefined **)param_1) {
    uVar5 = *(undefined8 *)(param_1 + 0x10);
    *(ulong *)(param_1 + 0x10) = CONCAT44(uStack_7c,uStack_80);
    uStack_80 = (undefined4)uVar5;
    uStack_7c = (undefined4)((ulong)uVar5 >> 0x20);
    puVar4 = *(undefined1 **)(param_1 + 0x20);
    uVar1 = *(ulong *)(param_1 + 0x28);
    *(ulong *)(param_1 + 0x28) = uStack_68;
    *(undefined1 **)(param_1 + 0x20) = puStack_70;
    fVar10 = *(float *)(param_1 + 0xc);
    *(float *)(param_1 + 0xc) = fStack_84;
    fStack_84 = fVar10;
    puStack_70 = puVar4;
    uStack_68 = uVar1;
  }
  puStack_90 = puVar2 + 0x10;
  if (puStack_70 != (undefined1 *)0x0) {
    Aska::MemoryManagerAdapter::AlignedFree(void*)();
  }
  return;
}

// ==== void Aska::THashSet<Aska::ShaderProgramValue*, Aska::THasher_StateKey<Aska::ShaderProgramValue*>, Aska::TEqualTo_StateKey<Aska::ShaderProgramValue*>, Aska::TAllocator<Aska::ShaderProgramValue*> >::Insert<Aska::THashMapIterator<Aska::detail::THashMapBucketArray<Aska::detail::THashMapBucket<Aska::ShaderProgramValue*>, Aska::TAllocator<Aska::detail::THashMapBucket<Aska::ShaderProgramValue*> > > > >(Aska::THashMapIterator<Aska::detail::THashMapBucketArray<Aska::detail::THashMapBucket<Aska::ShaderProgramValue*>, Aska::TAllocator<Aska::detail::THashMapBucket<Aska::ShaderProgramValue*> > > >, Aska::THashMapIterator<Aska::detail::THashMapBucketArray<Aska::detail::THashMapBucket<Aska::ShaderProgramValue*>, Aska::TAllocator<Aska::detail::THashMapBucket<Aska::ShaderProgramValue*> > > >)
// vaddr 0x2180bc8 | ghidra 0x2280bc8 | size 440 | symbol _ZN4Aska8THashSetIPNS_18ShaderProgramValueENS_16THasher_StateKeyIS2_EENS_17TEqualTo_StateKeyIS2_EENS_10TAllocatorIS2_EEE6InsertINS_16THashMapIteratorINS_6detail19THashMapBucketArrayINSC_14THashMapBucketIS2_EENS7_ISF_EEEEEEEEvT_SJ_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska8THashSetIPNS_18ShaderProgramValueENS_16THasher_StateKeyIS2_EENS_17TEqualTo_StateKeyIS2_EENS_10TAllocatorIS2_EEE6InsertINS_16THashMapIteratorINS_6detail19THashMapBucketArrayINSC_14THashMapBucketIS2_EENS7_ISF_EEEEEEEEvT_SJ_
               (long param_1,long *param_2,undefined8 *param_3)

{
  char cVar1;
  ulong uVar2;
  char *pcVar3;
  char *pcVar4;
  char *pcVar5;
  long lVar6;
  ulong uVar7;
  long *plVar8;
  char *pcVar9;
  ulong uVar10;
  
  pcVar4 = (char *)*param_2;
  pcVar5 = (char *)*param_3;
  lVar6 = 0;
  if (pcVar4 != pcVar5) {
    pcVar9 = pcVar4;
    do {
      lVar6 = lVar6 + 1;
      do {
        pcVar3 = (char *)param_2[2];
        if ((char *)param_2[2] == pcVar9) break;
        pcVar9 = pcVar9 + 0x10;
        pcVar3 = pcVar9;
      } while (*pcVar9 != '\x01');
      pcVar9 = pcVar3;
    } while (pcVar9 != pcVar5);
  }
  uVar7 = (ulong)((float)(lVar6 + (ulong)*(uint *)(param_1 + 0x10) +
                         (ulong)*(uint *)(param_1 + 0x14)) / *(float *)(param_1 + 0xc));
  if (*(ulong *)(param_1 + 0x28) < uVar7) {
    Aska::THashSet<Aska::ShaderProgramValue*, Aska::THasher_StateKey<Aska::ShaderProgramValue*>, Aska::TEqualTo_StateKey<Aska::ShaderProgramValue*>, Aska::TAllocator<Aska::ShaderProgramValue*> >::Rehash_(unsigned long)(param_1,uVar7 << 1 | 1);
    pcVar4 = (char *)*param_2;
    pcVar5 = (char *)*param_3;
  }
  if (pcVar4 != pcVar5) {
    do {
      uVar7 = *(ulong *)(param_1 + 0x28);
      if (uVar7 != 0) {
        plVar8 = *(long **)(pcVar4 + 8);
        uVar10 = 0;
        pcVar5 = (char *)0x0;
        do {
          uVar2 = 0;
          if (uVar7 != 0) {
            uVar2 = (*plVar8 + uVar10) / uVar7;
          }
          pcVar9 = (char *)(*(long *)(param_1 + 0x20) + ((*plVar8 + uVar10) - uVar2 * uVar7) * 0x10)
          ;
          cVar1 = *pcVar9;
          if (cVar1 == '\x01') {
            if ((*(long *)(*(long *)(pcVar9 + 8) + 8) == plVar8[1]) &&
               (*(long *)(*(long *)(pcVar9 + 8) + 0x10) == plVar8[2])) goto code_r0x02280d38;
          }
          else if (cVar1 == '\0') {
            if (pcVar5 != (char *)0x0) {
              pcVar9 = pcVar5;
            }
            break;
          }
          uVar10 = uVar10 + 1;
          if (cVar1 != '\x02' || pcVar5 != (char *)0x0) {
            pcVar9 = pcVar5;
          }
          pcVar5 = pcVar9;
        } while (uVar10 < uVar7);
        if (pcVar9 != (char *)0x0) {
          *(long **)(pcVar9 + 8) = plVar8;
          if (*pcVar9 == '\0') {
code_r0x02280d24:
            *(int *)(param_1 + 0x10) = *(int *)(param_1 + 0x10) + 1;
          }
          else if (*pcVar9 == '\x02') {
            *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + -1;
            goto code_r0x02280d24;
          }
          *pcVar9 = '\x01';
          pcVar4 = (char *)*param_2;
        }
      }
code_r0x02280d38:
      pcVar5 = pcVar4;
      do {
        pcVar4 = (char *)param_2[2];
        if ((char *)param_2[2] == pcVar5) break;
        pcVar4 = pcVar5 + 0x10;
        *param_2 = (long)pcVar4;
        pcVar9 = pcVar5 + 0x10;
        pcVar5 = pcVar4;
      } while (*pcVar9 != '\x01');
    } while (pcVar4 != (char *)*param_3);
  }
  return;
}

// ==== Aska::TCategorizeHash<Aska::TextureNode>::Regist(void const*, unsigned int)
// vaddr 0x21d83a4 | ghidra 0x22d83a4 | size 384 | symbol _ZN4Aska15TCategorizeHashINS_11TextureNodeEE6RegistEPKvj | lib libSOA-3.7.0.so | 2026-10-04
long * _ZN4Aska15TCategorizeHashINS_11TextureNodeEE6RegistEPKvj
                 (long *param_1,undefined8 param_2,uint param_3)

{
  int iVar1;
  long *plVar2;
  long lVar3;
  long *plVar4;
  long *plVar5;
  ulong uVar6;
  long *plVar7;
  
  uVar6 = (ulong)param_3;
  if (*(uint *)(param_1 + 0xb) <= param_3) {
    uVar6 = 0;
  }
  plVar4 = (long *)(param_1[10] + uVar6 * 8);
  param_1[0xc] = (long)plVar4;
  plVar2 = (long *)*plVar4;
  while (plVar2 != (long *)0x0) {
    while (iVar1 = (**(code **)(*plVar2 + 0x20))(plVar2,param_2), -1 < iVar1) {
      if (iVar1 == 0) goto code_r0x022d8434;
      plVar4 = (long *)(*plVar4 + 0x20);
      plVar2 = (long *)*plVar4;
      if (plVar2 == (long *)0x0) goto code_r0x022d8418;
    }
    plVar4 = (long *)(*plVar4 + 0x18);
    plVar2 = (long *)*plVar4;
  }
code_r0x022d8418:
  lVar3 = (**(code **)(*param_1 + 0x10))(param_1,param_2);
  *plVar4 = lVar3;
  plVar2 = (long *)0x0;
  if (lVar3 != 0) {
code_r0x022d8434:
    if ((plVar4 == (long *)0x0) || (plVar7 = (long *)*plVar4, plVar7 == (long *)0x0)) {
      plVar2 = (long *)0x0;
    }
    else {
      iVar1 = (**(code **)(*plVar7 + 0x38))(plVar7,param_2);
      while (0 < iVar1) {
        plVar2 = (long *)plVar7[8];
        if (plVar2 == (long *)0x0) {
          plVar4 = (long *)(**(code **)(*param_1 + 0x10))(param_1,param_2);
          if (plVar4 == (long *)0x0) {
            return (long *)0x0;
          }
          plVar4[7] = (long)plVar7;
          plVar7[8] = (long)plVar4;
          return plVar4;
        }
        iVar1 = (**(code **)(*plVar2 + 0x38))(plVar2,param_2);
        plVar7 = plVar2;
      }
      plVar2 = plVar7;
      if ((iVar1 < 0) &&
         (plVar2 = (long *)(**(code **)(*param_1 + 0x10))(param_1,param_2), plVar2 != (long *)0x0))
      {
        plVar2[3] = plVar7[3];
        plVar2[4] = plVar7[4];
        lVar3 = plVar7[7];
        plVar7[3] = 0;
        plVar7[4] = 0;
        plVar2[7] = lVar3;
        plVar2[8] = (long)plVar7;
        plVar5 = plVar7;
        if (lVar3 != 0) {
          *(long **)(lVar3 + 0x40) = plVar2;
          plVar5 = (long *)plVar2[8];
        }
        plVar5[7] = (long)plVar2;
        if ((long *)*plVar4 == plVar7) {
          *plVar4 = (long)plVar2;
        }
      }
    }
  }
  return plVar2;
}

// ==== Aska::TCategorizeHash<Aska::TextureNode>::FreeNode(Aska::TextureNode**)
// vaddr 0x21deca8 | ghidra 0x22deca8 | size 492 | symbol _ZN4Aska15TCategorizeHashINS_11TextureNodeEE8FreeNodeEPPS1_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska15TCategorizeHashINS_11TextureNodeEE8FreeNodeEPPS1_(long *param_1,ulong *param_2)

{
  long lVar1;
  char cVar2;
  long *plVar3;
  ulong uVar4;
  long *plVar5;
  long lVar6;
  
  uVar4 = *param_2;
  if (uVar4 != 0) {
    if (param_1[0xe] == uVar4) {
      param_1[0xe] = *(long *)(uVar4 + 0x10);
      uVar4 = *param_2;
    }
    if (param_1[0xf] == uVar4) {
      param_1[0xf] = *(long *)(uVar4 + 8);
      uVar4 = *param_2;
    }
    if (param_1[0x10] == uVar4) {
      param_1[0x10] = *(long *)(uVar4 + 8);
      cVar2 = (char)param_1[0x11];
    }
    else {
      cVar2 = (char)param_1[0x11];
    }
    if ((cVar2 == '\0') && (param_1[0x12] == *param_2)) {
      *(undefined4 *)(param_1 + 0x13) = 0;
      param_1[0x12] = 0;
      param_1[0x10] = 0;
      *(undefined1 *)(param_1 + 0x11) = 0;
    }
    lVar6 = *(long *)(*param_2 + 8);
    lVar1 = *(long *)(*param_2 + 0x10);
    if (lVar6 != 0) {
      *(long *)(lVar6 + 0x10) = lVar1;
    }
    if (lVar1 != 0) {
      *(undefined8 *)(lVar1 + 8) = *(undefined8 *)(*param_2 + 8);
    }
    *(undefined8 *)(*param_2 + 0x10) = 0;
    *(undefined8 *)(*param_2 + 8) = 0;
    plVar3 = (long *)*param_2;
    if (plVar3[8] != 0) {
      (**(code **)(*param_1 + 0x18))(param_1);
      plVar3 = (long *)*param_2;
    }
    if (plVar3[4] != 0) {
      (**(code **)(*param_1 + 0x18))(param_1);
      plVar3 = (long *)*param_2;
    }
    if (plVar3[3] != 0) {
      (**(code **)(*param_1 + 0x18))(param_1);
      plVar3 = (long *)*param_2;
    }
    (**(code **)(*plVar3 + 0x18))();
    *(int *)((long)param_1 + 0x8c) = *(int *)((long)param_1 + 0x8c) + -1;
    plVar5 = (long *)param_1[8];
    plVar3 = (long *)*param_2;
    if (((plVar5 == (long *)0x0) || (plVar3 < plVar5)) ||
       (plVar5 + (ulong)*(uint *)((long)param_1 + 0x2c) * 0x21 <= plVar3)) {
      if (plVar3 != (long *)0x0) {
        (**(code **)(*plVar3 + 8))();
      }
    }
    else {
      uVar4 = ((long)plVar3 - (long)plVar5 >> 3) * 0xf83e0f83e0f83e1;
      (**(code **)plVar5[(uVar4 & 0xffffffff) * 0x21])();
      lVar6 = (uVar4 >> 5 & 0x7ffffff) * 4;
      *(uint *)(param_1[4] + lVar6) =
           *(uint *)(param_1[4] + lVar6) & (1 << (ulong)((uint)uVar4 & 0x1f) ^ 0xffffffffU);
      *(int *)((long)param_1 + 0x3c) = *(int *)((long)param_1 + 0x3c) + -1;
    }
    *param_2 = 0;
  }
  return;
}

// ==== Aska::TCategorizeHash<Aska::TextureNode>::Remove(Aska::TextureNode**)
// vaddr 0x21defd4 | ghidra 0x22defd4 | size 232 | symbol _ZN4Aska15TCategorizeHashINS_11TextureNodeEE6RemoveEPPS1_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska15TCategorizeHashINS_11TextureNodeEE6RemoveEPPS1_(long *param_1,long *param_2)

{
  long *plVar1;
  long *plVar2;
  long lVar3;
  long lStack_8;
  
  lStack_8 = *param_2;
  if (lStack_8 == 0) {
    return;
  }
  if (*(long *)(lStack_8 + 0x40) == 0) {
    if (*(long *)(lStack_8 + 0x38) != 0) {
      *param_2 = *(long *)(lStack_8 + 0x38);
      *(undefined8 *)(*(long *)(lStack_8 + 0x38) + 0x40) = 0;
      *(undefined8 *)(lStack_8 + 0x38) = 0;
      goto code_r0x022df048;
    }
    lVar3 = *(long *)(lStack_8 + 0x18);
    if (*(long *)(lStack_8 + 0x20) == 0) {
      *param_2 = lVar3;
      *(undefined8 *)(lStack_8 + 0x18) = 0;
      goto code_r0x022df048;
    }
    plVar1 = (long *)(lStack_8 + 0x18);
    if (lVar3 != 0) {
      do {
        plVar2 = plVar1;
        lVar3 = *plVar2;
        plVar1 = (long *)(lVar3 + 0x20);
      } while (*(long *)(lVar3 + 0x20) != 0);
      *plVar2 = *(long *)(lVar3 + 0x18);
      *(undefined8 *)(lVar3 + 0x18) = *(undefined8 *)(lStack_8 + 0x18);
      *(undefined8 *)(lVar3 + 0x20) = *(undefined8 *)(lStack_8 + 0x20);
      *param_2 = lVar3;
      goto code_r0x022df024;
    }
    *param_2 = *(long *)(lStack_8 + 0x20);
  }
  else {
    *param_2 = *(long *)(lStack_8 + 0x40);
    *(undefined8 *)(*(long *)(lStack_8 + 0x40) + 0x38) = *(undefined8 *)(lStack_8 + 0x38);
    if (*(long *)(lStack_8 + 0x38) != 0) {
      *(undefined8 *)(*(long *)(lStack_8 + 0x38) + 0x40) = *(undefined8 *)(lStack_8 + 0x40);
    }
    *(undefined8 *)(*(long *)(lStack_8 + 0x40) + 0x18) = *(undefined8 *)(lStack_8 + 0x18);
    *(undefined8 *)(*(long *)(lStack_8 + 0x40) + 0x20) = *(undefined8 *)(lStack_8 + 0x20);
    *(undefined8 *)(lStack_8 + 0x38) = 0;
    *(undefined8 *)(lStack_8 + 0x40) = 0;
code_r0x022df024:
    *(undefined8 *)(lStack_8 + 0x18) = 0;
  }
  *(undefined8 *)(lStack_8 + 0x20) = 0;
code_r0x022df048:
  (**(code **)(*param_1 + 0x18))(param_1,&lStack_8);
  return;
}

// ==== Aska::THash<Aska::RelatedTextureIDSet>::Regist(void const*, unsigned int)
// vaddr 0x21e132c | ghidra 0x22e132c | size 168 | symbol _ZN4Aska5THashINS_19RelatedTextureIDSetEE6RegistEPKvj | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska5THashINS_19RelatedTextureIDSetEE6RegistEPKvj
               (long *param_1,undefined8 param_2,uint param_3)

{
  int iVar1;
  long *plVar2;
  long lVar3;
  long lVar4;
  ulong uVar5;
  long *plVar6;
  
  uVar5 = (ulong)param_3;
  if (*(uint *)(param_1 + 0xb) <= param_3) {
    uVar5 = 0;
  }
  plVar6 = (long *)(param_1[10] + uVar5 * 8);
  param_1[0xc] = (long)plVar6;
  plVar2 = (long *)*plVar6;
  while (plVar2 != (long *)0x0) {
    while (iVar1 = (**(code **)(*plVar2 + 0x20))(plVar2,param_2), -1 < iVar1) {
      if (iVar1 == 0) goto code_r0x022e13b8;
      plVar6 = (long *)(*plVar6 + 0x20);
      plVar2 = (long *)*plVar6;
      if (plVar2 == (long *)0x0) goto code_r0x022e139c;
    }
    plVar6 = (long *)(*plVar6 + 0x18);
    plVar2 = (long *)*plVar6;
  }
code_r0x022e139c:
  lVar3 = (**(code **)(*param_1 + 0x10))(param_1,param_2);
  *plVar6 = lVar3;
  lVar4 = 0;
  if (lVar3 != 0) {
code_r0x022e13b8:
    if (plVar6 == (long *)0x0) {
      lVar4 = 0;
    }
    else {
      lVar4 = *plVar6;
    }
  }
  return lVar4;
}

// ==== Aska::THash<Aska::TextureID>::Regist(void const*, unsigned int)
// vaddr 0x21e28c4 | ghidra 0x22e28c4 | size 168 | symbol _ZN4Aska5THashINS_9TextureIDEE6RegistEPKvj | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska5THashINS_9TextureIDEE6RegistEPKvj(long *param_1,undefined8 param_2,uint param_3)

{
  int iVar1;
  long *plVar2;
  long lVar3;
  long lVar4;
  ulong uVar5;
  long *plVar6;
  
  uVar5 = (ulong)param_3;
  if (*(uint *)(param_1 + 0xb) <= param_3) {
    uVar5 = 0;
  }
  plVar6 = (long *)(param_1[10] + uVar5 * 8);
  param_1[0xc] = (long)plVar6;
  plVar2 = (long *)*plVar6;
  while (plVar2 != (long *)0x0) {
    while (iVar1 = (**(code **)(*plVar2 + 0x20))(plVar2,param_2), -1 < iVar1) {
      if (iVar1 == 0) goto code_r0x022e2950;
      plVar6 = (long *)(*plVar6 + 0x20);
      plVar2 = (long *)*plVar6;
      if (plVar2 == (long *)0x0) goto code_r0x022e2934;
    }
    plVar6 = (long *)(*plVar6 + 0x18);
    plVar2 = (long *)*plVar6;
  }
code_r0x022e2934:
  lVar3 = (**(code **)(*param_1 + 0x10))(param_1,param_2);
  *plVar6 = lVar3;
  lVar4 = 0;
  if (lVar3 != 0) {
code_r0x022e2950:
    if (plVar6 == (long *)0x0) {
      lVar4 = 0;
    }
    else {
      lVar4 = *plVar6;
    }
  }
  return lVar4;
}

// ==== Aska::THash<Aska::TextureID>::IsRegisted(void const*, unsigned int)
// vaddr 0x21e29f8 | ghidra 0x22e29f8 | size 132 | symbol _ZN4Aska5THashINS_9TextureIDEE10IsRegistedEPKvj | lib libSOA-3.7.0.so | 2026-10-04
bool _ZN4Aska5THashINS_9TextureIDEE10IsRegistedEPKvj(long param_1,undefined8 param_2,uint param_3)

{
  int iVar1;
  long *plVar2;
  ulong uVar3;
  long *plVar4;
  
  uVar3 = (ulong)param_3;
  if (*(uint *)(param_1 + 0x58) <= param_3) {
    uVar3 = 0;
  }
  plVar4 = (long *)(*(long *)(param_1 + 0x50) + uVar3 * 8);
  plVar2 = (long *)*plVar4;
  do {
    if (plVar2 == (long *)0x0) {
      return false;
    }
    while (iVar1 = (**(code **)(*plVar2 + 0x20))(plVar2,param_2), -1 < iVar1) {
      if (iVar1 == 0) {
        return *plVar4 != 0;
      }
      plVar4 = (long *)(*plVar4 + 0x20);
      plVar2 = (long *)*plVar4;
      if (plVar2 == (long *)0x0) {
        return false;
      }
    }
    plVar4 = (long *)(*plVar4 + 0x18);
    plVar2 = (long *)*plVar4;
  } while( true );
}

// ==== Aska::TCategorizeHash<Aska::TextureMemory>::FreeNode(Aska::TextureMemory**)
// vaddr 0x21e4538 | ghidra 0x22e4538 | size 492 | symbol _ZN4Aska15TCategorizeHashINS_13TextureMemoryEE8FreeNodeEPPS1_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska15TCategorizeHashINS_13TextureMemoryEE8FreeNodeEPPS1_(long *param_1,ulong *param_2)

{
  long lVar1;
  char cVar2;
  long *plVar3;
  ulong uVar4;
  long *plVar5;
  long lVar6;
  
  uVar4 = *param_2;
  if (uVar4 != 0) {
    if (param_1[0xe] == uVar4) {
      param_1[0xe] = *(long *)(uVar4 + 0x10);
      uVar4 = *param_2;
    }
    if (param_1[0xf] == uVar4) {
      param_1[0xf] = *(long *)(uVar4 + 8);
      uVar4 = *param_2;
    }
    if (param_1[0x10] == uVar4) {
      param_1[0x10] = *(long *)(uVar4 + 8);
      cVar2 = (char)param_1[0x11];
    }
    else {
      cVar2 = (char)param_1[0x11];
    }
    if ((cVar2 == '\0') && (param_1[0x12] == *param_2)) {
      *(undefined4 *)(param_1 + 0x13) = 0;
      param_1[0x12] = 0;
      param_1[0x10] = 0;
      *(undefined1 *)(param_1 + 0x11) = 0;
    }
    lVar6 = *(long *)(*param_2 + 8);
    lVar1 = *(long *)(*param_2 + 0x10);
    if (lVar6 != 0) {
      *(long *)(lVar6 + 0x10) = lVar1;
    }
    if (lVar1 != 0) {
      *(undefined8 *)(lVar1 + 8) = *(undefined8 *)(*param_2 + 8);
    }
    *(undefined8 *)(*param_2 + 0x10) = 0;
    *(undefined8 *)(*param_2 + 8) = 0;
    plVar3 = (long *)*param_2;
    if (plVar3[8] != 0) {
      (**(code **)(*param_1 + 0x18))(param_1);
      plVar3 = (long *)*param_2;
    }
    if (plVar3[4] != 0) {
      (**(code **)(*param_1 + 0x18))(param_1);
      plVar3 = (long *)*param_2;
    }
    if (plVar3[3] != 0) {
      (**(code **)(*param_1 + 0x18))(param_1);
      plVar3 = (long *)*param_2;
    }
    (**(code **)(*plVar3 + 0x18))();
    *(int *)((long)param_1 + 0x8c) = *(int *)((long)param_1 + 0x8c) + -1;
    plVar5 = (long *)param_1[8];
    plVar3 = (long *)*param_2;
    if (((plVar5 == (long *)0x0) || (plVar3 < plVar5)) ||
       (plVar5 + (ulong)*(uint *)((long)param_1 + 0x2c) * 9 <= plVar3)) {
      if (plVar3 != (long *)0x0) {
        (**(code **)(*plVar3 + 8))();
      }
    }
    else {
      uVar4 = ((long)plVar3 - (long)plVar5 >> 3) * -0x71c71c71c71c71c7;
      (**(code **)plVar5[(uVar4 & 0xffffffff) * 9])();
      lVar6 = (uVar4 >> 5 & 0x7ffffff) * 4;
      *(uint *)(param_1[4] + lVar6) =
           *(uint *)(param_1[4] + lVar6) & (1 << (ulong)((uint)uVar4 & 0x1f) ^ 0xffffffffU);
      *(int *)((long)param_1 + 0x3c) = *(int *)((long)param_1 + 0x3c) + -1;
    }
    *param_2 = 0;
  }
  return;
}

// ==== Aska::TCategorizeHash<Aska::TextureMemory>::Remove(Aska::TextureMemory**)
// vaddr 0x21e47e0 | ghidra 0x22e47e0 | size 232 | symbol _ZN4Aska15TCategorizeHashINS_13TextureMemoryEE6RemoveEPPS1_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska15TCategorizeHashINS_13TextureMemoryEE6RemoveEPPS1_(long *param_1,long *param_2)

{
  long *plVar1;
  long *plVar2;
  long lVar3;
  long lStack_8;
  
  lStack_8 = *param_2;
  if (lStack_8 == 0) {
    return;
  }
  if (*(long *)(lStack_8 + 0x40) == 0) {
    if (*(long *)(lStack_8 + 0x38) != 0) {
      *param_2 = *(long *)(lStack_8 + 0x38);
      *(undefined8 *)(*(long *)(lStack_8 + 0x38) + 0x40) = 0;
      *(undefined8 *)(lStack_8 + 0x38) = 0;
      goto code_r0x022e4854;
    }
    lVar3 = *(long *)(lStack_8 + 0x18);
    if (*(long *)(lStack_8 + 0x20) == 0) {
      *param_2 = lVar3;
      *(undefined8 *)(lStack_8 + 0x18) = 0;
      goto code_r0x022e4854;
    }
    plVar1 = (long *)(lStack_8 + 0x18);
    if (lVar3 != 0) {
      do {
        plVar2 = plVar1;
        lVar3 = *plVar2;
        plVar1 = (long *)(lVar3 + 0x20);
      } while (*(long *)(lVar3 + 0x20) != 0);
      *plVar2 = *(long *)(lVar3 + 0x18);
      *(undefined8 *)(lVar3 + 0x18) = *(undefined8 *)(lStack_8 + 0x18);
      *(undefined8 *)(lVar3 + 0x20) = *(undefined8 *)(lStack_8 + 0x20);
      *param_2 = lVar3;
      goto code_r0x022e4830;
    }
    *param_2 = *(long *)(lStack_8 + 0x20);
  }
  else {
    *param_2 = *(long *)(lStack_8 + 0x40);
    *(undefined8 *)(*(long *)(lStack_8 + 0x40) + 0x38) = *(undefined8 *)(lStack_8 + 0x38);
    if (*(long *)(lStack_8 + 0x38) != 0) {
      *(undefined8 *)(*(long *)(lStack_8 + 0x38) + 0x40) = *(undefined8 *)(lStack_8 + 0x40);
    }
    *(undefined8 *)(*(long *)(lStack_8 + 0x40) + 0x18) = *(undefined8 *)(lStack_8 + 0x18);
    *(undefined8 *)(*(long *)(lStack_8 + 0x40) + 0x20) = *(undefined8 *)(lStack_8 + 0x20);
    *(undefined8 *)(lStack_8 + 0x38) = 0;
    *(undefined8 *)(lStack_8 + 0x40) = 0;
code_r0x022e4830:
    *(undefined8 *)(lStack_8 + 0x18) = 0;
  }
  *(undefined8 *)(lStack_8 + 0x20) = 0;
code_r0x022e4854:
  (**(code **)(*param_1 + 0x18))(param_1,&lStack_8);
  return;
}

// ==== Aska::TCategorizeHash<Aska::TextureMemory>::Regist(void const*, unsigned int)
// vaddr 0x21e498c | ghidra 0x22e498c | size 384 | symbol _ZN4Aska15TCategorizeHashINS_13TextureMemoryEE6RegistEPKvj | lib libSOA-3.7.0.so | 2026-10-04
long * _ZN4Aska15TCategorizeHashINS_13TextureMemoryEE6RegistEPKvj
                 (long *param_1,undefined8 param_2,uint param_3)

{
  int iVar1;
  long *plVar2;
  long lVar3;
  long *plVar4;
  long *plVar5;
  ulong uVar6;
  long *plVar7;
  
  uVar6 = (ulong)param_3;
  if (*(uint *)(param_1 + 0xb) <= param_3) {
    uVar6 = 0;
  }
  plVar4 = (long *)(param_1[10] + uVar6 * 8);
  param_1[0xc] = (long)plVar4;
  plVar2 = (long *)*plVar4;
  while (plVar2 != (long *)0x0) {
    while (iVar1 = (**(code **)(*plVar2 + 0x20))(plVar2,param_2), -1 < iVar1) {
      if (iVar1 == 0) goto code_r0x022e4a1c;
      plVar4 = (long *)(*plVar4 + 0x20);
      plVar2 = (long *)*plVar4;
      if (plVar2 == (long *)0x0) goto code_r0x022e4a00;
    }
    plVar4 = (long *)(*plVar4 + 0x18);
    plVar2 = (long *)*plVar4;
  }
code_r0x022e4a00:
  lVar3 = (**(code **)(*param_1 + 0x10))(param_1,param_2);
  *plVar4 = lVar3;
  plVar2 = (long *)0x0;
  if (lVar3 != 0) {
code_r0x022e4a1c:
    if ((plVar4 == (long *)0x0) || (plVar7 = (long *)*plVar4, plVar7 == (long *)0x0)) {
      plVar2 = (long *)0x0;
    }
    else {
      iVar1 = (**(code **)(*plVar7 + 0x38))(plVar7,param_2);
      while (0 < iVar1) {
        plVar2 = (long *)plVar7[8];
        if (plVar2 == (long *)0x0) {
          plVar4 = (long *)(**(code **)(*param_1 + 0x10))(param_1,param_2);
          if (plVar4 == (long *)0x0) {
            return (long *)0x0;
          }
          plVar4[7] = (long)plVar7;
          plVar7[8] = (long)plVar4;
          return plVar4;
        }
        iVar1 = (**(code **)(*plVar2 + 0x38))(plVar2,param_2);
        plVar7 = plVar2;
      }
      plVar2 = plVar7;
      if ((iVar1 < 0) &&
         (plVar2 = (long *)(**(code **)(*param_1 + 0x10))(param_1,param_2), plVar2 != (long *)0x0))
      {
        plVar2[3] = plVar7[3];
        plVar2[4] = plVar7[4];
        lVar3 = plVar7[7];
        plVar7[3] = 0;
        plVar7[4] = 0;
        plVar2[7] = lVar3;
        plVar2[8] = (long)plVar7;
        plVar5 = plVar7;
        if (lVar3 != 0) {
          *(long **)(lVar3 + 0x40) = plVar2;
          plVar5 = (long *)plVar2[8];
        }
        plVar5[7] = (long)plVar2;
        if ((long *)*plVar4 == plVar7) {
          *plVar4 = (long)plVar2;
        }
      }
    }
  }
  return plVar2;
}

// ==== Aska::TCategorizeHash<Aska::TextureMemory>::Remove(void const*, unsigned int)
// vaddr 0x21e4b0c | ghidra 0x22e4b0c | size 200 | symbol _ZN4Aska15TCategorizeHashINS_13TextureMemoryEE6RemoveEPKvj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska15TCategorizeHashINS_13TextureMemoryEE6RemoveEPKvj
               (long *param_1,undefined8 param_2,uint param_3)

{
  int iVar1;
  long *plVar2;
  ulong uVar3;
  long *plVar4;
  
  uVar3 = (ulong)param_3;
  if (*(uint *)(param_1 + 0xb) <= param_3) {
    uVar3 = 0;
  }
  plVar4 = (long *)(param_1[10] + uVar3 * 8);
  param_1[0xc] = (long)plVar4;
  plVar2 = (long *)*plVar4;
  while (plVar2 != (long *)0x0) {
    iVar1 = (**(code **)(*plVar2 + 0x20))(plVar2,param_2);
    if (iVar1 < 0) {
      plVar4 = (long *)(*plVar4 + 0x18);
    }
    else {
      if (iVar1 == 0) goto code_r0x022e4b7c;
      plVar4 = (long *)(*plVar4 + 0x20);
    }
    plVar2 = (long *)*plVar4;
  }
code_r0x022e4bac:
                    /* WARNING: Could not recover jumptable at 0x022e4bc4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*param_1 + 0x40))(param_1,plVar4);
  return;
code_r0x022e4b7c:
  plVar2 = (long *)*plVar4;
  if (plVar2 == (long *)0x0) goto code_r0x022e4bac;
  iVar1 = (**(code **)(*plVar2 + 0x38))(plVar2,param_2);
  if (iVar1 < 1) {
    if (iVar1 < 0) {
      return;
    }
    goto code_r0x022e4bac;
  }
  plVar4 = (long *)(*plVar4 + 0x40);
  goto code_r0x022e4b7c;
}

// ==== Aska::TCategorizeHash<Aska::TextureMemory>::Search(void const*, unsigned int)
// vaddr 0x21e4bf4 | ghidra 0x22e4bf4 | size 180 | symbol _ZN4Aska15TCategorizeHashINS_13TextureMemoryEE6SearchEPKvj | lib libSOA-3.7.0.so | 2026-10-04
long * _ZN4Aska15TCategorizeHashINS_13TextureMemoryEE6SearchEPKvj
                 (long param_1,undefined8 param_2,uint param_3)

{
  int iVar1;
  long *plVar2;
  ulong uVar3;
  long *plVar4;
  
  uVar3 = (ulong)param_3;
  if (*(uint *)(param_1 + 0x58) <= param_3) {
    uVar3 = 0;
  }
  plVar4 = (long *)(*(long *)(param_1 + 0x50) + uVar3 * 8);
  plVar2 = (long *)*plVar4;
  while( true ) {
    while( true ) {
      if (plVar2 == (long *)0x0) {
        return (long *)0x0;
      }
      iVar1 = (**(code **)(*plVar2 + 0x20))(plVar2,param_2);
      if (-1 < iVar1) break;
      plVar4 = (long *)(*plVar4 + 0x18);
      plVar2 = (long *)*plVar4;
    }
    if (iVar1 == 0) break;
    plVar4 = (long *)(*plVar4 + 0x20);
    plVar2 = (long *)*plVar4;
  }
  plVar4 = (long *)*plVar4;
  while( true ) {
    if (plVar4 == (long *)0x0) {
      return (long *)0x0;
    }
    iVar1 = (**(code **)(*plVar4 + 0x38))(plVar4,param_2);
    if (iVar1 == 0) break;
    if (iVar1 < 1) {
      return (long *)0x0;
    }
    plVar4 = (long *)plVar4[8];
  }
  return plVar4;
}

// ==== Aska::TCategorizeHash<Aska::TextureMemory>::GetNext() const
// vaddr 0x21e71e0 | ghidra 0x22e71e0 | size 404 | symbol _ZNK4Aska15TCategorizeHashINS_13TextureMemoryEE7GetNextEv | lib libSOA-3.7.0.so | 2026-10-04
long * _ZNK4Aska15TCategorizeHashINS_13TextureMemoryEE7GetNextEv(long *param_1)

{
  bool bVar1;
  uint uVar2;
  int iVar3;
  long *plVar4;
  undefined8 uVar5;
  long *plVar6;
  uint uVar7;
  long *plVar8;
  ulong uVar9;
  long *plVar10;
  long *plVar11;
  
  if ((char)param_1[0x11] != '\0') {
    return (long *)0x0;
  }
  plVar4 = (long *)param_1[0x12];
  if ((long *)param_1[0x12] == (long *)0x0) {
    if (*(uint *)(param_1 + 0xb) != 0) {
      uVar7 = 0;
      do {
        plVar4 = *(long **)(param_1[10] + (ulong)uVar7 * 8);
        if (plVar4 != (long *)0x0) {
          param_1[0x12] = (long)plVar4;
          *(uint *)(param_1 + 0x13) = uVar7;
          goto code_r0x022e720c;
        }
        uVar7 = uVar7 + 1;
      } while (uVar7 < *(uint *)(param_1 + 0xb));
    }
    *(undefined1 *)(param_1 + 0x11) = 1;
    return (long *)0x0;
  }
code_r0x022e720c:
  do {
    plVar6 = plVar4;
    plVar4 = (long *)plVar6[7];
  } while ((long *)plVar6[7] != (long *)0x0);
  plVar4 = (long *)plVar6[3];
  if (plVar4 == (long *)0x0) {
    plVar4 = (long *)plVar6[4];
    while (plVar10 = plVar6, plVar4 == (long *)0x0) {
      do {
        uVar5 = (**(code **)(*plVar10 + 0x30))(plVar10);
        uVar2 = (**(code **)(*param_1 + 0x60))(param_1,uVar5);
        uVar7 = *(uint *)(param_1 + 0xb);
        uVar9 = (ulong)uVar2;
        if (uVar7 <= uVar2) {
          uVar9 = 0;
        }
        plVar4 = (long *)(param_1[10] + uVar9 * 8);
        plVar6 = (long *)*plVar4;
        if (plVar6 == (long *)0x0) {
code_r0x022e7340:
          uVar2 = *(uint *)(param_1 + 0x13);
          goto code_r0x022e7344;
        }
        bVar1 = true;
        plVar11 = plVar6;
        do {
          iVar3 = (**(code **)(*plVar6 + 0x20))(plVar6,uVar5);
          plVar8 = (long *)*plVar4;
          if (iVar3 == 0) {
            plVar6 = (long *)0x0;
            if (plVar8 != (long *)0x0) {
              plVar6 = plVar11;
            }
            if (!bVar1) goto code_r0x022e72d0;
            uVar7 = *(uint *)(param_1 + 0xb);
            goto code_r0x022e7340;
          }
          plVar4 = plVar8 + 3;
          if (-1 < iVar3) {
            plVar4 = plVar8 + 4;
          }
          plVar6 = (long *)*plVar4;
          bVar1 = false;
          plVar11 = plVar8;
        } while (plVar6 != (long *)0x0);
        plVar6 = (long *)0x0;
code_r0x022e72d0:
        plVar4 = (long *)plVar6[4];
        bVar1 = plVar10 == plVar4;
        plVar10 = plVar6;
      } while (bVar1);
    }
  }
  goto code_r0x022e7228;
  while (plVar4 = *(long **)(param_1[10] + (ulong)uVar2 * 8), plVar4 == (long *)0x0) {
code_r0x022e7344:
    uVar2 = uVar2 + 1;
    if (uVar7 <= uVar2) {
      plVar4 = (long *)0x0;
      *(undefined1 *)(param_1 + 0x11) = 1;
      goto code_r0x022e7228;
    }
  }
  *(uint *)(param_1 + 0x13) = uVar2;
code_r0x022e7228:
  param_1[0x12] = (long)plVar4;
  return plVar4;
}

// ==== Aska::THashMap<Aska::Yayoi::DNSCache::DNSKey const, Aska::Yayoi::IPAddress, Aska::Yayoi::DNSCache::DNSHasher, Aska::Yayoi::DNSCache::DNSEqual, Aska::TAllocator<Aska::TPair<Aska::Yayoi::DNSCache::DNSKey const, Aska::Yayoi::IPAddress> > >::Find_(Aska::Yayoi::DNSCache::DNSKey const&) const
// vaddr 0x21ed6fc | ghidra 0x22ed6fc | size 444 | symbol _ZNK4Aska8THashMapIKNS_5Yayoi8DNSCache6DNSKeyENS1_9IPAddressENS2_9DNSHasherENS2_8DNSEqualENS_10TAllocatorINS_5TPairIS4_S5_EEEEE5Find_ERS4_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK4Aska8THashMapIKNS_5Yayoi8DNSCache6DNSKeyENS1_9IPAddressENS2_9DNSHasherENS2_8DNSEqualENS_10TAllocatorINS_5TPairIS4_S5_EEEEE5Find_ERS4_
               (undefined8 *param_1,long param_2,undefined8 *param_3)

{
  ulong uVar1;
  ulong uVar2;
  ulong uVar3;
  int iVar4;
  long lVar5;
  long lVar6;
  ulong uVar7;
  ulong uVar8;
  char *pcVar9;
  char *pcVar10;
  undefined1 auStack_170 [64];
  long lStack_130;
  int iStack_128;
  short sStack_124;
  undefined1 *puStack_120;
  undefined1 auStack_118 [64];
  long lStack_d8;
  int iStack_d0;
  short sStack_cc;
  undefined1 *puStack_c8;
  undefined1 auStack_c0 [64];
  long lStack_80;
  undefined4 uStack_78;
  undefined2 uStack_74;
  undefined8 uStack_70;
  ulong uStack_68;
  
  puStack_c8 = auStack_c0;
  lVar6 = *(long *)(param_2 + 0x20);
  uVar2 = *(ulong *)(param_2 + 0x28);
  uStack_78 = *(undefined4 *)(param_3 + 10);
  uStack_74 = *(undefined2 *)((long)param_3 + 0x54);
  iVar4 = __aska_snprintf_s(char*, unsigned long, unsigned long, char const*, ...)(puStack_c8,0x40,0xffffffffffffffff,&UNK_027f6a37/*"%s"*/,*param_3);
  lStack_80 = (long)iVar4;
  uStack_70 = 0;
  uStack_68 = 0;
  Aska::detail::SpookyHashV2::Hash128(void const*, unsigned long, unsigned long*, unsigned long*)(puStack_c8,lStack_80,&uStack_68,&uStack_70);
  if (uVar2 != 0) {
    uVar8 = uStack_68 & 0xffffffff;
    uVar7 = 0;
    do {
      uVar1 = uVar8 + uVar7;
      uVar3 = 0;
      if (uVar2 != 0) {
        uVar3 = uVar1 / uVar2;
      }
      lVar5 = uVar1 - uVar3 * uVar2;
      pcVar9 = (char *)(lVar6 + lVar5 * 0xe8);
      if (*pcVar9 == '\x01') {
        lVar5 = lVar6 + lVar5 * 0xe8;
        iStack_d0 = *(int *)(lVar5 + 0x58);
        sStack_cc = *(short *)(lVar5 + 0x5c);
        puStack_120 = auStack_118;
        iVar4 = __aska_snprintf_s(char*, unsigned long, unsigned long, char const*, ...)(auStack_118,0x40,0xffffffffffffffff,&UNK_027f6a37/*"%s"*/,
                                *(undefined8 *)(lVar5 + 8));
        lStack_d8 = (long)iVar4;
        iStack_128 = *(int *)(param_3 + 10);
        sStack_124 = *(short *)((long)param_3 + 0x54);
        iVar4 = __aska_snprintf_s(char*, unsigned long, unsigned long, char const*, ...)(auStack_170,0x40,0xffffffffffffffff,&UNK_027f6a37/*"%s"*/,*param_3);
        lStack_130 = (long)iVar4;
        iVar4 = strcmp(puStack_120,auStack_170);
        if (((iVar4 == 0) && (iStack_d0 == iStack_128)) && (sStack_cc == sStack_124)) {
          pcVar10 = (char *)(lVar6 + uVar2 * 0xe8);
          goto code_r0x022ed880;
        }
      }
      else if (*pcVar9 == '\0') break;
      uVar7 = uVar7 + 1;
    } while (uVar7 < uVar2);
  }
  lVar6 = *(long *)(param_2 + 0x20);
  pcVar10 = (char *)(lVar6 + *(long *)(param_2 + 0x28) * 0xe8);
  pcVar9 = pcVar10;
code_r0x022ed880:
  *param_1 = pcVar9;
  param_1[1] = lVar6;
  param_1[2] = pcVar10;
  return;
}

// ==== Aska::THashMap<Aska::Yayoi::DNSCache::DNSKey const, Aska::Yayoi::IPAddress, Aska::Yayoi::DNSCache::DNSHasher, Aska::Yayoi::DNSCache::DNSEqual, Aska::TAllocator<Aska::TPair<Aska::Yayoi::DNSCache::DNSKey const, Aska::Yayoi::IPAddress> > >::Emplace_(Aska::Yayoi::DNSCache::DNSKey const&)
// vaddr 0x21ed8b8 | ghidra 0x22ed8b8 | size 636 | symbol _ZN4Aska8THashMapIKNS_5Yayoi8DNSCache6DNSKeyENS1_9IPAddressENS2_9DNSHasherENS2_8DNSEqualENS_10TAllocatorINS_5TPairIS4_S5_EEEEE8Emplace_ERS4_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska8THashMapIKNS_5Yayoi8DNSCache6DNSKeyENS1_9IPAddressENS2_9DNSHasherENS2_8DNSEqualENS_10TAllocatorINS_5TPairIS4_S5_EEEEE8Emplace_ERS4_
               (undefined8 *param_1,long param_2,undefined8 *param_3)

{
  ulong uVar1;
  ulong uVar2;
  ulong uVar3;
  int iVar4;
  undefined1 uVar5;
  long lVar6;
  char *pcVar7;
  long lVar8;
  char *pcVar9;
  ulong uVar10;
  ulong uVar11;
  undefined1 auStack_170 [64];
  long lStack_130;
  int iStack_128;
  short sStack_124;
  undefined1 *puStack_120;
  undefined1 auStack_118 [64];
  long lStack_d8;
  int iStack_d0;
  short sStack_cc;
  undefined1 *puStack_c8;
  undefined1 auStack_c0 [64];
  long lStack_80;
  undefined4 uStack_78;
  undefined2 uStack_74;
  undefined8 uStack_70;
  ulong uStack_68;
  
  puStack_c8 = auStack_c0;
  lVar8 = *(long *)(param_2 + 0x20);
  uVar2 = *(ulong *)(param_2 + 0x28);
  uStack_78 = *(undefined4 *)(param_3 + 10);
  uStack_74 = *(undefined2 *)((long)param_3 + 0x54);
  iVar4 = __aska_snprintf_s(char*, unsigned long, unsigned long, char const*, ...)(puStack_c8,0x40,0xffffffffffffffff,&UNK_027f6a37/*"%s"*/,*param_3);
  lStack_80 = (long)iVar4;
  uStack_70 = 0;
  uStack_68 = 0;
  Aska::detail::SpookyHashV2::Hash128(void const*, unsigned long, unsigned long*, unsigned long*)(puStack_c8,lStack_80,&uStack_68,&uStack_70);
  if (uVar2 != 0) {
    uVar11 = uStack_68 & 0xffffffff;
    uVar10 = 0;
    pcVar7 = (char *)0x0;
    do {
      uVar1 = uVar11 + uVar10;
      uVar3 = 0;
      if (uVar2 != 0) {
        uVar3 = uVar1 / uVar2;
      }
      lVar6 = uVar1 - uVar3 * uVar2;
      pcVar9 = (char *)(lVar8 + lVar6 * 0xe8);
      if (*pcVar9 == '\x01') {
        lVar6 = lVar8 + lVar6 * 0xe8;
        iStack_d0 = *(int *)(lVar6 + 0x58);
        sStack_cc = *(short *)(lVar6 + 0x5c);
        puStack_120 = auStack_118;
        iVar4 = __aska_snprintf_s(char*, unsigned long, unsigned long, char const*, ...)(auStack_118,0x40,0xffffffffffffffff,&UNK_027f6a37/*"%s"*/,
                                *(undefined8 *)(lVar6 + 8));
        lStack_d8 = (long)iVar4;
        iStack_128 = *(int *)(param_3 + 10);
        sStack_124 = *(short *)((long)param_3 + 0x54);
        iVar4 = __aska_snprintf_s(char*, unsigned long, unsigned long, char const*, ...)(auStack_170,0x40,0xffffffffffffffff,&UNK_027f6a37/*"%s"*/,*param_3);
        lStack_130 = (long)iVar4;
        iVar4 = strcmp(puStack_120,auStack_170);
        if (((iVar4 == 0) && (iStack_d0 == iStack_128)) && (sStack_cc == sStack_124)) {
          uVar5 = 0;
          pcVar7 = (char *)(lVar8 + uVar2 * 0xe8);
          goto code_r0x022edaf0;
        }
      }
      else if (*pcVar9 == '\0') {
        if (pcVar7 != (char *)0x0) {
          pcVar9 = pcVar7;
        }
        if (pcVar9 == (char *)0x0) goto code_r0x022edadc;
        goto code_r0x022eda4c;
      }
      uVar10 = uVar10 + 1;
      if (*pcVar9 != '\x02' || pcVar7 != (char *)0x0) {
        pcVar9 = pcVar7;
      }
      pcVar7 = pcVar9;
    } while (uVar10 < uVar2);
    if (pcVar9 != (char *)0x0) {
code_r0x022eda4c:
      *(char **)(pcVar9 + 8) = pcVar9 + 0x10;
      *(undefined4 *)(pcVar9 + 0x58) = *(undefined4 *)(param_3 + 10);
      *(undefined2 *)(pcVar9 + 0x5c) = *(undefined2 *)((long)param_3 + 0x54);
      iVar4 = __aska_snprintf_s(char*, unsigned long, unsigned long, char const*, ...)(pcVar9 + 0x10,0x40,0xffffffffffffffff,&UNK_027f6a37/*"%s"*/,*param_3);
      *(long *)(pcVar9 + 0x50) = (long)iVar4;
      Aska::Yayoi::IPAddress::IPAddress()(pcVar9 + 0x60);
      if (*pcVar9 == '\0') {
code_r0x022edaa8:
        *(int *)(param_2 + 0x10) = *(int *)(param_2 + 0x10) + 1;
      }
      else if (*pcVar9 == '\x02') {
        *(int *)(param_2 + 0x14) = *(int *)(param_2 + 0x14) + -1;
        goto code_r0x022edaa8;
      }
      uVar5 = 1;
      *pcVar9 = '\x01';
      pcVar7 = (char *)(lVar8 + *(long *)(param_2 + 0x28) * 0xe8);
      goto code_r0x022edaf0;
    }
  }
code_r0x022edadc:
  lVar8 = *(long *)(param_2 + 0x20);
  uVar5 = 0;
  pcVar7 = (char *)(lVar8 + *(long *)(param_2 + 0x28) * 0xe8);
  pcVar9 = pcVar7;
code_r0x022edaf0:
  *param_1 = pcVar9;
  param_1[1] = lVar8;
  param_1[2] = pcVar7;
  *(undefined1 *)(param_1 + 3) = uVar5;
  return;
}

// ==== Aska::THashMap<char const*, int, Aska::Yayoi::SQLiteDriver::EntityObject::StringHasher, Aska::Yayoi::SQLiteDriver::EntityObject::StringEqualTo, Aska::TAllocator<Aska::TPair<char const* const, int> > >::Emplace_(char const* const&)
// vaddr 0x21f52a0 | ghidra 0x22f52a0 | size 368 | symbol _ZN4Aska8THashMapIPKciNS_5Yayoi12SQLiteDriver12EntityObject12StringHasherENS5_13StringEqualToENS_10TAllocatorINS_5TPairIKS2_iEEEEE8Emplace_ERSA_ | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Type propagation algorithm not settling */

void _ZN4Aska8THashMapIPKciNS_5Yayoi12SQLiteDriver12EntityObject12StringHasherENS5_13StringEqualToENS_10TAllocatorINS_5TPairIKS2_iEEEEE8Emplace_ERSA_
               (undefined8 *param_1,long param_2,undefined8 *param_3)

{
  ulong uVar1;
  char cVar2;
  ulong uVar3;
  long lVar4;
  int iVar5;
  undefined8 uVar6;
  undefined1 uVar7;
  long lVar8;
  undefined8 uVar9;
  long lVar10;
  char *pcVar11;
  ulong uVar12;
  char *pcVar13;
  long alStack_70 [2];
  
  uVar9 = *param_3;
  lVar10 = *(long *)(param_2 + 0x20);
  uVar1 = *(ulong *)(param_2 + 0x28);
  uVar6 = strlen(uVar9);
  alStack_70[0] = 0;
  alStack_70[1] = 0;
  Aska::detail::SpookyHashV2::Hash128(void const*, unsigned long, unsigned long*, unsigned long*)(uVar9,uVar6,alStack_70,alStack_70 + 1);
  lVar4 = alStack_70[0];
  if (uVar1 != 0) {
    uVar6 = *param_3;
    uVar12 = 0;
    pcVar11 = (char *)0x0;
    do {
      uVar3 = 0;
      if (uVar1 != 0) {
        uVar3 = (lVar4 + uVar12) / uVar1;
      }
      lVar8 = (lVar4 + uVar12) - uVar3 * uVar1;
      pcVar13 = (char *)(lVar10 + lVar8 * 0x18);
      cVar2 = *pcVar13;
      if (cVar2 == '\x01') {
        iVar5 = strcmp(*(undefined8 *)(lVar10 + lVar8 * 0x18 + 8),uVar6);
        if (iVar5 == 0) {
          uVar7 = 0;
          pcVar11 = (char *)(lVar10 + uVar1 * 0x18);
          goto code_r0x022f53d0;
        }
      }
      else if (cVar2 == '\0') {
        if (pcVar11 != (char *)0x0) {
          pcVar13 = pcVar11;
        }
        if (pcVar13 == (char *)0x0) goto code_r0x022f53bc;
        goto code_r0x022f5364;
      }
      uVar12 = uVar12 + 1;
      if (cVar2 != '\x02' || pcVar11 != (char *)0x0) {
        pcVar13 = pcVar11;
      }
      pcVar11 = pcVar13;
    } while (uVar12 < uVar1);
    if (pcVar13 != (char *)0x0) {
code_r0x022f5364:
      *(undefined8 *)(pcVar13 + 8) = *param_3;
      if (*pcVar13 == '\0') {
code_r0x022f5388:
        *(int *)(param_2 + 0x10) = *(int *)(param_2 + 0x10) + 1;
      }
      else if (*pcVar13 == '\x02') {
        *(int *)(param_2 + 0x14) = *(int *)(param_2 + 0x14) + -1;
        goto code_r0x022f5388;
      }
      uVar7 = 1;
      *pcVar13 = '\x01';
      pcVar11 = (char *)(lVar10 + *(long *)(param_2 + 0x28) * 0x18);
      goto code_r0x022f53d0;
    }
  }
code_r0x022f53bc:
  lVar10 = *(long *)(param_2 + 0x20);
  uVar7 = 0;
  pcVar11 = (char *)(lVar10 + *(long *)(param_2 + 0x28) * 0x18);
  pcVar13 = pcVar11;
code_r0x022f53d0:
  *param_1 = pcVar13;
  param_1[1] = lVar10;
  param_1[2] = pcVar11;
  *(undefined1 *)(param_1 + 3) = uVar7;
  return;
}

// ==== Aska::THashMap<char const*, int, Aska::Yayoi::SQLiteDriver::EntityObject::StringHasher, Aska::Yayoi::SQLiteDriver::EntityObject::StringEqualTo, Aska::TAllocator<Aska::TPair<char const* const, int> > >::Rehash_(unsigned long)
// vaddr 0x21f5410 | ghidra 0x22f5410 | size 516 | symbol _ZN4Aska8THashMapIPKciNS_5Yayoi12SQLiteDriver12EntityObject12StringHasherENS5_13StringEqualToENS_10TAllocatorINS_5TPairIKS2_iEEEEE7Rehash_Em | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska8THashMapIPKciNS_5Yayoi12SQLiteDriver12EntityObject12StringHasherENS5_13StringEqualToENS_10TAllocatorINS_5TPairIKS2_iEEEEE7Rehash_Em
               (undefined1 *param_1,ulong param_2)

{
  ulong uVar1;
  undefined *puVar2;
  undefined1 *puVar3;
  undefined1 *puVar4;
  undefined8 uVar5;
  char *pcVar6;
  ulong uVar7;
  long lVar8;
  ulong uVar9;
  float fVar10;
  float fVar11;
  undefined *puStack_90;
  float fStack_84;
  undefined4 uStack_80;
  undefined4 uStack_7c;
  undefined1 *puStack_70;
  ulong uStack_68;
  char *pcStack_60;
  char *pcStack_58;
  char *pcStack_50;
  char *pcStack_48;
  char *pcStack_40;
  char *pcStack_38;
  
  puVar2 = 
  PTR__ZTVN4Aska8THashMapIPKciNS_5Yayoi12SQLiteDriver12EntityObject12StringHasherENS5_13StringEqualToENS_10TAllocatorINS_5TPairIKS2_iEEEEEE_02cc1328
  ;
  puStack_90 = PTR__ZTVN4Aska8THashMapIPKciNS_5Yayoi12SQLiteDriver12EntityObject12StringHasherENS5_13StringEqualToENS_10TAllocatorINS_5TPairIKS2_iEEEEEE_02cc1328
               + 0x10;
  fStack_84 = 0.75;
  uStack_80 = 0;
  uStack_7c = 0;
  if (param_2 < 0xaaaaaaaaaaaaaab) {
    puStack_70 = (undefined1 *)Aska::MemoryManagerAdapter::AlignedMalloc(unsigned long, unsigned long)(param_2 * 0x18,8);
  }
  else {
    puStack_70 = (undefined1 *)0x0;
  }
  if (puStack_70 == (undefined1 *)0x0) {
    param_2 = 0;
  }
  if (param_2 == 0) {
    fVar10 = *(float *)(param_1 + 0xc);
code_r0x022f5528:
    if (fVar10 <= 0.0) goto code_r0x022f5538;
  }
  else {
    uVar1 = (param_2 * 0x18 - 0x18) / 0x18 + 1;
    puVar3 = puStack_70;
    if ((uVar1 < 2) || (uVar7 = uVar1 & 0x1ffffffffffffffe, uVar7 == 0)) {
code_r0x022f54e0:
      do {
        puVar4 = puVar3 + 0x18;
        *puVar3 = 0;
        puVar3 = puVar4;
      } while (puStack_70 + param_2 * 0x18 != puVar4);
    }
    else {
      puVar3 = puStack_70 + uVar7 * 0x18;
      uVar9 = uVar7;
      puVar4 = puStack_70;
      do {
        *puVar4 = 0;
        puVar4[0x18] = 0;
        uVar9 = uVar9 - 2;
        puVar4 = puVar4 + 0x30;
      } while (uVar9 != 0);
      if (uVar1 != uVar7) goto code_r0x022f54e0;
    }
    fVar10 = *(float *)(param_1 + 0xc);
    if (param_2 == 0) goto code_r0x022f5528;
    fVar11 = (float)NEON_ucvtf(uStack_80);
    if (fVar10 <= fVar11 / (float)param_2) goto code_r0x022f5538;
  }
  fStack_84 = fVar10;
code_r0x022f5538:
  pcStack_58 = *(char **)(param_1 + 0x20);
  lVar8 = *(long *)(param_1 + 0x28);
  pcStack_60 = pcStack_58 + lVar8 * 0x18;
  pcStack_48 = pcStack_60;
  if ((*(int *)(param_1 + 0x10) != 0) && (pcStack_48 = pcStack_58, lVar8 != 0)) {
    lVar8 = lVar8 * 0x18;
    pcVar6 = pcStack_58;
    do {
      pcStack_48 = pcVar6;
      if (*pcVar6 == '\x01') break;
      lVar8 = lVar8 + -0x18;
      pcVar6 = pcVar6 + 0x18;
      pcStack_48 = pcStack_60;
    } while (lVar8 != 0);
  }
  uStack_68 = param_2;
  pcStack_50 = pcStack_60;
  pcStack_40 = pcStack_58;
  pcStack_38 = pcStack_60;
  void Aska::THashMap<char const*, int, Aska::Yayoi::SQLiteDriver::EntityObject::StringHasher, Aska::Yayoi::SQLiteDriver::EntityObject::StringEqualTo, Aska::TAllocator<Aska::TPair<char const* const, int> > >::Insert<Aska::THashMapIterator<Aska::detail::THashMapBucketArray<Aska::detail::THashMapBucket<Aska::TPair<char const* const, int> >, Aska::TAllocator<Aska::detail::THashMapBucket<Aska::TPair<char const* const, int> > > > > >(Aska::THashMapIterator<Aska::detail::THashMapBucketArray<Aska::detail::THashMapBucket<Aska::TPair<char const* const, int> >, Aska::TAllocator<Aska::detail::THashMapBucket<Aska::TPair<char const* const, int> > > > >, Aska::THashMapIterator<Aska::detail::THashMapBucketArray<Aska::detail::THashMapBucket<Aska::TPair<char const* const, int> >, Aska::TAllocator<Aska::detail::THashMapBucket<Aska::TPair<char const* const, int> > > > >)(&puStack_90,&pcStack_48,&pcStack_60);
  if (&puStack_90 != (undefined **)param_1) {
    uVar5 = *(undefined8 *)(param_1 + 0x10);
    *(ulong *)(param_1 + 0x10) = CONCAT44(uStack_7c,uStack_80);
    uStack_80 = (undefined4)uVar5;
    uStack_7c = (undefined4)((ulong)uVar5 >> 0x20);
    puVar3 = *(undefined1 **)(param_1 + 0x20);
    uVar1 = *(ulong *)(param_1 + 0x28);
    *(ulong *)(param_1 + 0x28) = uStack_68;
    *(undefined1 **)(param_1 + 0x20) = puStack_70;
    fVar10 = *(float *)(param_1 + 0xc);
    *(float *)(param_1 + 0xc) = fStack_84;
    fStack_84 = fVar10;
    puStack_70 = puVar3;
    uStack_68 = uVar1;
  }
  puStack_90 = puVar2 + 0x10;
  if (puStack_70 != (undefined1 *)0x0) {
    Aska::MemoryManagerAdapter::AlignedFree(void*)();
  }
  return;
}

// ==== void Aska::THashMap<char const*, int, Aska::Yayoi::SQLiteDriver::EntityObject::StringHasher, Aska::Yayoi::SQLiteDriver::EntityObject::StringEqualTo, Aska::TAllocator<Aska::TPair<char const* const, int> > >::Insert<Aska::THashMapIterator<Aska::detail::THashMapBucketArray<Aska::detail::THashMapBucket<Aska::TPair<char const* const, int> >, Aska::TAllocator<Aska::detail::THashMapBucket<Aska::TPair<char const* const, int> > > > > >(Aska::THashMapIterator<Aska::detail::THashMapBucketArray<Aska::detail::THashMapBucket<Aska::TPair<char const* const, int> >, Aska::TAllocator<Aska::detail::THashMapBucket<Aska::TPair<char const* const, int> > > > >, Aska::THashMapIterator<Aska::detail::THashMapBucketArray<Aska::detail::THashMapBucket<Aska::TPair<char const* const, int> >, Aska::TAllocator<Aska::detail::THashMapBucket<Aska::TPair<char const* const, int> > > > >)
// vaddr 0x21f5614 | ghidra 0x22f5614 | size 256 | symbol _ZN4Aska8THashMapIPKciNS_5Yayoi12SQLiteDriver12EntityObject12StringHasherENS5_13StringEqualToENS_10TAllocatorINS_5TPairIKS2_iEEEEE6InsertINS_16THashMapIteratorINS_6detail19THashMapBucketArrayINSG_14THashMapBucketISB_EENS8_ISJ_EEEEEEEEvT_SN_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska8THashMapIPKciNS_5Yayoi12SQLiteDriver12EntityObject12StringHasherENS5_13StringEqualToENS_10TAllocatorINS_5TPairIKS2_iEEEEE6InsertINS_16THashMapIteratorINS_6detail19THashMapBucketArrayINSG_14THashMapBucketISB_EENS8_ISJ_EEEEEEEEvT_SN_
               (long param_1,long *param_2,undefined8 *param_3)

{
  char *pcVar1;
  char *pcVar2;
  char *pcVar3;
  long lVar4;
  ulong uVar5;
  char *pcVar6;
  undefined1 auStack_40 [32];
  
  pcVar2 = (char *)*param_2;
  pcVar3 = (char *)*param_3;
  lVar4 = 0;
  if (pcVar2 != pcVar3) {
    pcVar6 = pcVar2;
    do {
      lVar4 = lVar4 + 1;
      do {
        pcVar1 = (char *)param_2[2];
        if ((char *)param_2[2] == pcVar6) break;
        pcVar6 = pcVar6 + 0x18;
        pcVar1 = pcVar6;
      } while (*pcVar6 != '\x01');
      pcVar6 = pcVar1;
    } while (pcVar6 != pcVar3);
  }
  uVar5 = (ulong)((float)(lVar4 + (ulong)*(uint *)(param_1 + 0x10) +
                         (ulong)*(uint *)(param_1 + 0x14)) / *(float *)(param_1 + 0xc));
  if (uVar5 <= *(ulong *)(param_1 + 0x28)) goto code_r0x022f56b8;
  Aska::THashMap<char const*, int, Aska::Yayoi::SQLiteDriver::EntityObject::StringHasher, Aska::Yayoi::SQLiteDriver::EntityObject::StringEqualTo, Aska::TAllocator<Aska::TPair<char const* const, int> > >::Rehash_(unsigned long)(param_1,uVar5 << 1 | 1);
  pcVar2 = (char *)*param_2;
  do {
    pcVar3 = (char *)*param_3;
code_r0x022f56b8:
    if (pcVar2 == pcVar3) {
      return;
    }
    Aska::THashMap<char const*, int, Aska::Yayoi::SQLiteDriver::EntityObject::StringHasher, Aska::Yayoi::SQLiteDriver::EntityObject::StringEqualTo, Aska::TAllocator<Aska::TPair<char const* const, int> > >::Insert_(Aska::TPair<char const* const, int> const&)(auStack_40,param_1,pcVar2 + 8);
    pcVar3 = (char *)*param_2;
    do {
      pcVar2 = (char *)param_2[2];
      if ((char *)param_2[2] == pcVar3) break;
      pcVar2 = pcVar3 + 0x18;
      *param_2 = (long)pcVar2;
      pcVar6 = pcVar3 + 0x18;
      pcVar3 = pcVar2;
    } while (*pcVar6 != '\x01');
  } while( true );
}

// ==== Aska::THashMap<char const*, int, Aska::Yayoi::SQLiteDriver::EntityObject::StringHasher, Aska::Yayoi::SQLiteDriver::EntityObject::StringEqualTo, Aska::TAllocator<Aska::TPair<char const* const, int> > >::Insert_(Aska::TPair<char const* const, int> const&)
// vaddr 0x21f5714 | ghidra 0x22f5714 | size 360 | symbol _ZN4Aska8THashMapIPKciNS_5Yayoi12SQLiteDriver12EntityObject12StringHasherENS5_13StringEqualToENS_10TAllocatorINS_5TPairIKS2_iEEEEE7Insert_ERKSB_ | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Type propagation algorithm not settling */

void _ZN4Aska8THashMapIPKciNS_5Yayoi12SQLiteDriver12EntityObject12StringHasherENS5_13StringEqualToENS_10TAllocatorINS_5TPairIKS2_iEEEEE7Insert_ERKSB_
               (undefined8 *param_1,long param_2,undefined8 *param_3)

{
  ulong uVar1;
  char cVar2;
  ulong uVar3;
  long lVar4;
  int iVar5;
  undefined8 uVar6;
  undefined1 uVar7;
  long lVar8;
  undefined8 uVar9;
  char *pcVar10;
  long lVar11;
  ulong uVar12;
  char *pcVar13;
  long alStack_70 [2];
  
  uVar9 = *param_3;
  lVar11 = *(long *)(param_2 + 0x20);
  uVar1 = *(ulong *)(param_2 + 0x28);
  uVar6 = strlen(uVar9);
  alStack_70[0] = 0;
  alStack_70[1] = 0;
  Aska::detail::SpookyHashV2::Hash128(void const*, unsigned long, unsigned long*, unsigned long*)(uVar9,uVar6,alStack_70,alStack_70 + 1);
  lVar4 = alStack_70[0];
  if (uVar1 != 0) {
    uVar12 = 0;
    pcVar10 = (char *)0x0;
    do {
      uVar3 = 0;
      if (uVar1 != 0) {
        uVar3 = (lVar4 + uVar12) / uVar1;
      }
      lVar8 = (lVar4 + uVar12) - uVar3 * uVar1;
      pcVar13 = (char *)(lVar11 + lVar8 * 0x18);
      cVar2 = *pcVar13;
      if (cVar2 == '\x01') {
        iVar5 = strcmp(*(undefined8 *)(lVar11 + lVar8 * 0x18 + 8),*param_3);
        if (iVar5 == 0) {
          uVar7 = 0;
          pcVar10 = (char *)(lVar11 + uVar1 * 0x18);
          goto code_r0x022f583c;
        }
      }
      else if (cVar2 == '\0') {
        if (pcVar10 != (char *)0x0) {
          pcVar13 = pcVar10;
        }
        if (pcVar13 == (char *)0x0) goto code_r0x022f5828;
        goto code_r0x022f57cc;
      }
      uVar12 = uVar12 + 1;
      if (cVar2 != '\x02' || pcVar10 != (char *)0x0) {
        pcVar13 = pcVar10;
      }
      pcVar10 = pcVar13;
    } while (uVar12 < uVar1);
    if (pcVar13 != (char *)0x0) {
code_r0x022f57cc:
      *(undefined8 *)(pcVar13 + 8) = *param_3;
      *(undefined4 *)(pcVar13 + 0x10) = *(undefined4 *)(param_3 + 1);
      if (*pcVar13 == '\0') {
code_r0x022f57f8:
        *(int *)(param_2 + 0x10) = *(int *)(param_2 + 0x10) + 1;
      }
      else if (*pcVar13 == '\x02') {
        *(int *)(param_2 + 0x14) = *(int *)(param_2 + 0x14) + -1;
        goto code_r0x022f57f8;
      }
      uVar7 = 1;
      *pcVar13 = '\x01';
      pcVar10 = (char *)(lVar11 + *(long *)(param_2 + 0x28) * 0x18);
      goto code_r0x022f583c;
    }
  }
code_r0x022f5828:
  lVar11 = *(long *)(param_2 + 0x20);
  uVar7 = 0;
  pcVar10 = (char *)(lVar11 + *(long *)(param_2 + 0x28) * 0x18);
  pcVar13 = pcVar10;
code_r0x022f583c:
  *param_1 = pcVar13;
  param_1[1] = lVar11;
  param_1[2] = pcVar10;
  *(undefined1 *)(param_1 + 3) = uVar7;
  return;
}

// ==== Aska::THashMap<long, Aska::Yayoi::NetworkEvent*, Aska::THasher<long>, Aska::TEqualTo<long>, Aska::TAllocator<Aska::TPair<long const, Aska::Yayoi::NetworkEvent*> > >::operator[](long const&)
// vaddr 0x2204554 | ghidra 0x2304554 | size 320 | symbol _ZN4Aska8THashMapIlPNS_5Yayoi12NetworkEventENS_7THasherIlEENS_8TEqualToIlEENS_10TAllocatorINS_5TPairIKlS3_EEEEEixERSA_ | lib libSOA-3.7.0.so | 2026-10-04
char * _ZN4Aska8THashMapIlPNS_5Yayoi12NetworkEventENS_7THasherIlEENS_8TEqualToIlEENS_10TAllocatorINS_5TPairIKlS3_EEEEEixERSA_
                 (long param_1,ulong *param_2)

{
  ulong uVar1;
  char cVar2;
  ulong uVar3;
  ulong uVar4;
  char *pcVar5;
  ulong uVar6;
  long lVar7;
  ulong uVar8;
  ulong uVar9;
  char *pcVar10;
  long lVar11;
  
  uVar6 = *(ulong *)(param_1 + 0x28);
  uVar4 = (ulong)((float)((ulong)*(uint *)(param_1 + 0x10) + (ulong)*(uint *)(param_1 + 0x14) + 1) /
                 *(float *)(param_1 + 0xc));
  if (uVar6 < uVar4) {
    Aska::THashMap<long, Aska::Yayoi::NetworkEvent*, Aska::THasher<long>, Aska::TEqualTo<long>, Aska::TAllocator<Aska::TPair<long const, Aska::Yayoi::NetworkEvent*> > >::Rehash_(unsigned long)(param_1,uVar4 << 1 | 1);
    uVar6 = *(ulong *)(param_1 + 0x28);
  }
  lVar7 = *(long *)(param_1 + 0x20);
  if (uVar6 != 0) {
    uVar8 = *param_2;
    uVar4 = ~uVar8 + uVar8 * 0x200000;
    uVar4 = (uVar4 ^ uVar4 >> 0x18) * 0x109;
    uVar9 = (uVar4 ^ uVar4 >> 0xe) * 0x15;
    uVar4 = 0;
    pcVar5 = (char *)0x0;
    do {
      uVar1 = (uVar9 ^ uVar9 >> 0x1c) * 0x80000001 + uVar4;
      uVar3 = 0;
      if (uVar6 != 0) {
        uVar3 = uVar1 / uVar6;
      }
      lVar11 = uVar1 - uVar3 * uVar6;
      pcVar10 = (char *)(lVar7 + lVar11 * 0x18);
      cVar2 = *pcVar10;
      if (cVar2 == '\x01') {
        if (*(ulong *)(lVar7 + lVar11 * 0x18 + 8) == uVar8) goto code_r0x0230467c;
      }
      else if (cVar2 == '\0') {
        if (pcVar5 != (char *)0x0) {
          pcVar10 = pcVar5;
        }
        if (pcVar10 == (char *)0x0) goto code_r0x02304674;
        goto code_r0x02304630;
      }
      uVar4 = uVar4 + 1;
      if (cVar2 != '\x02' || pcVar5 != (char *)0x0) {
        pcVar10 = pcVar5;
      }
      pcVar5 = pcVar10;
    } while (uVar4 < uVar6);
    if (pcVar10 != (char *)0x0) {
code_r0x02304630:
      *(ulong *)(pcVar10 + 8) = uVar8;
      if (*pcVar10 == '\0') {
code_r0x02304650:
        *(int *)(param_1 + 0x10) = *(int *)(param_1 + 0x10) + 1;
      }
      else if (*pcVar10 == '\x02') {
        *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + -1;
        goto code_r0x02304650;
      }
      *pcVar10 = '\x01';
      goto code_r0x0230467c;
    }
  }
code_r0x02304674:
  pcVar10 = (char *)(lVar7 + uVar6 * 0x18);
code_r0x0230467c:
  return pcVar10 + 0x10;
}

// ==== Aska::TCategorizeHash<Aska::MappedAddressSet>::FreeNode(Aska::MappedAddressSet**)
// vaddr 0x222ebd0 | ghidra 0x232ebd0 | size 492 | symbol _ZN4Aska15TCategorizeHashINS_16MappedAddressSetEE8FreeNodeEPPS1_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska15TCategorizeHashINS_16MappedAddressSetEE8FreeNodeEPPS1_(long *param_1,ulong *param_2)

{
  long lVar1;
  char cVar2;
  long *plVar3;
  ulong uVar4;
  long *plVar5;
  long lVar6;
  
  uVar4 = *param_2;
  if (uVar4 != 0) {
    if (param_1[0xe] == uVar4) {
      param_1[0xe] = *(long *)(uVar4 + 0x10);
      uVar4 = *param_2;
    }
    if (param_1[0xf] == uVar4) {
      param_1[0xf] = *(long *)(uVar4 + 8);
      uVar4 = *param_2;
    }
    if (param_1[0x10] == uVar4) {
      param_1[0x10] = *(long *)(uVar4 + 8);
      cVar2 = (char)param_1[0x11];
    }
    else {
      cVar2 = (char)param_1[0x11];
    }
    if ((cVar2 == '\0') && (param_1[0x12] == *param_2)) {
      *(undefined4 *)(param_1 + 0x13) = 0;
      param_1[0x12] = 0;
      param_1[0x10] = 0;
      *(undefined1 *)(param_1 + 0x11) = 0;
    }
    lVar6 = *(long *)(*param_2 + 8);
    lVar1 = *(long *)(*param_2 + 0x10);
    if (lVar6 != 0) {
      *(long *)(lVar6 + 0x10) = lVar1;
    }
    if (lVar1 != 0) {
      *(undefined8 *)(lVar1 + 8) = *(undefined8 *)(*param_2 + 8);
    }
    *(undefined8 *)(*param_2 + 0x10) = 0;
    *(undefined8 *)(*param_2 + 8) = 0;
    plVar3 = (long *)*param_2;
    if (plVar3[9] != 0) {
      (**(code **)(*param_1 + 0x18))(param_1);
      plVar3 = (long *)*param_2;
    }
    if (plVar3[4] != 0) {
      (**(code **)(*param_1 + 0x18))(param_1);
      plVar3 = (long *)*param_2;
    }
    if (plVar3[3] != 0) {
      (**(code **)(*param_1 + 0x18))(param_1);
      plVar3 = (long *)*param_2;
    }
    (**(code **)(*plVar3 + 0x18))();
    *(int *)((long)param_1 + 0x8c) = *(int *)((long)param_1 + 0x8c) + -1;
    plVar5 = (long *)param_1[8];
    plVar3 = (long *)*param_2;
    if (((plVar5 == (long *)0x0) || (plVar3 < plVar5)) ||
       (plVar5 + (ulong)*(uint *)((long)param_1 + 0x2c) * 0x16 <= plVar3)) {
      if (plVar3 != (long *)0x0) {
        (**(code **)(*plVar3 + 8))();
      }
    }
    else {
      uVar4 = ((long)plVar3 - (long)plVar5 >> 4) * 0x2e8ba2e8ba2e8ba3;
      (**(code **)plVar5[(uVar4 & 0xffffffff) * 0x16])();
      lVar6 = (uVar4 >> 5 & 0x7ffffff) * 4;
      *(uint *)(param_1[4] + lVar6) =
           *(uint *)(param_1[4] + lVar6) & (1 << (ulong)((uint)uVar4 & 0x1f) ^ 0xffffffffU);
      *(int *)((long)param_1 + 0x3c) = *(int *)((long)param_1 + 0x3c) + -1;
    }
    *param_2 = 0;
  }
  return;
}

// ==== Aska::TCategorizeHash<Aska::MappedAddressSet>::Regist(void const*, unsigned int)
// vaddr 0x222f160 | ghidra 0x232f160 | size 384 | symbol _ZN4Aska15TCategorizeHashINS_16MappedAddressSetEE6RegistEPKvj | lib libSOA-3.7.0.so | 2026-10-04
long * _ZN4Aska15TCategorizeHashINS_16MappedAddressSetEE6RegistEPKvj
                 (long *param_1,undefined8 param_2,uint param_3)

{
  int iVar1;
  long *plVar2;
  long lVar3;
  long *plVar4;
  long *plVar5;
  ulong uVar6;
  long *plVar7;
  
  uVar6 = (ulong)param_3;
  if (*(uint *)(param_1 + 0xb) <= param_3) {
    uVar6 = 0;
  }
  plVar4 = (long *)(param_1[10] + uVar6 * 8);
  param_1[0xc] = (long)plVar4;
  plVar2 = (long *)*plVar4;
  while (plVar2 != (long *)0x0) {
    while (iVar1 = (**(code **)(*plVar2 + 0x20))(plVar2,param_2), -1 < iVar1) {
      if (iVar1 == 0) goto code_r0x0232f1f0;
      plVar4 = (long *)(*plVar4 + 0x20);
      plVar2 = (long *)*plVar4;
      if (plVar2 == (long *)0x0) goto code_r0x0232f1d4;
    }
    plVar4 = (long *)(*plVar4 + 0x18);
    plVar2 = (long *)*plVar4;
  }
code_r0x0232f1d4:
  lVar3 = (**(code **)(*param_1 + 0x10))(param_1,param_2);
  *plVar4 = lVar3;
  plVar2 = (long *)0x0;
  if (lVar3 != 0) {
code_r0x0232f1f0:
    if ((plVar4 == (long *)0x0) || (plVar7 = (long *)*plVar4, plVar7 == (long *)0x0)) {
      plVar2 = (long *)0x0;
    }
    else {
      iVar1 = (**(code **)(*plVar7 + 0x38))(plVar7,param_2);
      while (0 < iVar1) {
        plVar2 = (long *)plVar7[9];
        if (plVar2 == (long *)0x0) {
          plVar4 = (long *)(**(code **)(*param_1 + 0x10))(param_1,param_2);
          if (plVar4 == (long *)0x0) {
            return (long *)0x0;
          }
          plVar4[8] = (long)plVar7;
          plVar7[9] = (long)plVar4;
          return plVar4;
        }
        iVar1 = (**(code **)(*plVar2 + 0x38))(plVar2,param_2);
        plVar7 = plVar2;
      }
      plVar2 = plVar7;
      if ((iVar1 < 0) &&
         (plVar2 = (long *)(**(code **)(*param_1 + 0x10))(param_1,param_2), plVar2 != (long *)0x0))
      {
        plVar2[3] = plVar7[3];
        plVar2[4] = plVar7[4];
        lVar3 = plVar7[8];
        plVar7[3] = 0;
        plVar7[4] = 0;
        plVar2[8] = lVar3;
        plVar2[9] = (long)plVar7;
        plVar5 = plVar7;
        if (lVar3 != 0) {
          *(long **)(lVar3 + 0x48) = plVar2;
          plVar5 = (long *)plVar2[9];
        }
        plVar5[8] = (long)plVar2;
        if ((long *)*plVar4 == plVar7) {
          *plVar4 = (long)plVar2;
        }
      }
    }
  }
  return plVar2;
}

// ==== Aska::TCategorizeHash<Aska::MappedAddressSet>::GetNext() const
// vaddr 0x2230744 | ghidra 0x2330744 | size 404 | symbol _ZNK4Aska15TCategorizeHashINS_16MappedAddressSetEE7GetNextEv | lib libSOA-3.7.0.so | 2026-10-04
long * _ZNK4Aska15TCategorizeHashINS_16MappedAddressSetEE7GetNextEv(long *param_1)

{
  bool bVar1;
  uint uVar2;
  int iVar3;
  long *plVar4;
  undefined8 uVar5;
  long *plVar6;
  uint uVar7;
  long *plVar8;
  ulong uVar9;
  long *plVar10;
  long *plVar11;
  
  if ((char)param_1[0x11] != '\0') {
    return (long *)0x0;
  }
  plVar4 = (long *)param_1[0x12];
  if ((long *)param_1[0x12] == (long *)0x0) {
    if (*(uint *)(param_1 + 0xb) != 0) {
      uVar7 = 0;
      do {
        plVar4 = *(long **)(param_1[10] + (ulong)uVar7 * 8);
        if (plVar4 != (long *)0x0) {
          param_1[0x12] = (long)plVar4;
          *(uint *)(param_1 + 0x13) = uVar7;
          goto code_r0x02330770;
        }
        uVar7 = uVar7 + 1;
      } while (uVar7 < *(uint *)(param_1 + 0xb));
    }
    *(undefined1 *)(param_1 + 0x11) = 1;
    return (long *)0x0;
  }
code_r0x02330770:
  do {
    plVar6 = plVar4;
    plVar4 = (long *)plVar6[8];
  } while ((long *)plVar6[8] != (long *)0x0);
  plVar4 = (long *)plVar6[3];
  if (plVar4 == (long *)0x0) {
    plVar4 = (long *)plVar6[4];
    while (plVar10 = plVar6, plVar4 == (long *)0x0) {
      do {
        uVar5 = (**(code **)(*plVar10 + 0x30))(plVar10);
        uVar2 = (**(code **)(*param_1 + 0x60))(param_1,uVar5);
        uVar7 = *(uint *)(param_1 + 0xb);
        uVar9 = (ulong)uVar2;
        if (uVar7 <= uVar2) {
          uVar9 = 0;
        }
        plVar4 = (long *)(param_1[10] + uVar9 * 8);
        plVar6 = (long *)*plVar4;
        if (plVar6 == (long *)0x0) {
code_r0x023308a4:
          uVar2 = *(uint *)(param_1 + 0x13);
          goto code_r0x023308a8;
        }
        bVar1 = true;
        plVar11 = plVar6;
        do {
          iVar3 = (**(code **)(*plVar6 + 0x20))(plVar6,uVar5);
          plVar8 = (long *)*plVar4;
          if (iVar3 == 0) {
            plVar6 = (long *)0x0;
            if (plVar8 != (long *)0x0) {
              plVar6 = plVar11;
            }
            if (!bVar1) goto code_r0x02330834;
            uVar7 = *(uint *)(param_1 + 0xb);
            goto code_r0x023308a4;
          }
          plVar4 = plVar8 + 3;
          if (-1 < iVar3) {
            plVar4 = plVar8 + 4;
          }
          plVar6 = (long *)*plVar4;
          bVar1 = false;
          plVar11 = plVar8;
        } while (plVar6 != (long *)0x0);
        plVar6 = (long *)0x0;
code_r0x02330834:
        plVar4 = (long *)plVar6[4];
        bVar1 = plVar10 == plVar4;
        plVar10 = plVar6;
      } while (bVar1);
    }
  }
  goto code_r0x0233078c;
  while (plVar4 = *(long **)(param_1[10] + (ulong)uVar2 * 8), plVar4 == (long *)0x0) {
code_r0x023308a8:
    uVar2 = uVar2 + 1;
    if (uVar7 <= uVar2) {
      plVar4 = (long *)0x0;
      *(undefined1 *)(param_1 + 0x11) = 1;
      goto code_r0x0233078c;
    }
  }
  *(uint *)(param_1 + 0x13) = uVar2;
code_r0x0233078c:
  param_1[0x12] = (long)plVar4;
  return plVar4;
}
