// port/decomp/containers/hash_map.c: Ghidra decompiles for the containers subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileAt.java, tools/resolve_decomp.py
// run      2026-10-04 05:16 UTC: tools/decomp_at.sh '--into' 'containers/hash_map' '246936c' '2469168' '2468e10' '2468dd0' '1f856f8' '1f854f4' '1f854c4' '1f85484' '1f84c08' '18061e0' '180600c' '1804d6c' '17feef0'

// ==== Aska::THashSet<unsigned int, Aska::THasher<unsigned int>, Aska::TEqualTo<unsigned int>, Aska::TAllocator<unsigned int> >::~THashSet()
// vaddr 0x16feef0 | ghidra 0x17feef0 | size 64 | symbol _ZN4Aska8THashSetIjNS_7THasherIjEENS_8TEqualToIjEENS_10TAllocatorIjEEED2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska8THashSetIjNS_7THasherIjEENS_8TEqualToIjEENS_10TAllocatorIjEEED2Ev(long *param_1)

{
  *param_1 = (long)(
                   PTR__ZTVN4Aska8THashSetIjNS_7THasherIjEENS_8TEqualToIjEENS_10TAllocatorIjEEEE_02cc11f0
                   + 0x10);
  if (param_1[4] != 0) {
    Aska::MemoryManagerAdapter::AlignedFree(void*)();
    param_1[4] = 0;
    param_1[5] = 0;
  }
  param_1[2] = 0;
  return;
}

// ==== Aska::THashSet<unsigned int, Aska::THasher<unsigned int>, Aska::TEqualTo<unsigned int>, Aska::TAllocator<unsigned int> >::~THashSet()
// vaddr 0x1704d6c | ghidra 0x1804d6c | size 48 | symbol _ZN4Aska8THashSetIjNS_7THasherIjEENS_8TEqualToIjEENS_10TAllocatorIjEEED0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska8THashSetIjNS_7THasherIjEENS_8TEqualToIjEENS_10TAllocatorIjEEED0Ev(long *param_1)

{
  *param_1 = (long)(
                   PTR__ZTVN4Aska8THashSetIjNS_7THasherIjEENS_8TEqualToIjEENS_10TAllocatorIjEEEE_02cc11f0
                   + 0x10);
  if (param_1[4] != 0) {
    Aska::MemoryManagerAdapter::AlignedFree(void*)();
  }
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::THashSet<unsigned int, Aska::THasher<unsigned int>, Aska::TEqualTo<unsigned int>, Aska::TAllocator<unsigned int> >::Rehash_(unsigned long)
// vaddr 0x170600c | ghidra 0x180600c | size 468 | symbol _ZN4Aska8THashSetIjNS_7THasherIjEENS_8TEqualToIjEENS_10TAllocatorIjEEE7Rehash_Em | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska8THashSetIjNS_7THasherIjEENS_8TEqualToIjEENS_10TAllocatorIjEEE7Rehash_Em
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
  
  puVar2 = PTR__ZTVN4Aska8THashSetIjNS_7THasherIjEENS_8TEqualToIjEENS_10TAllocatorIjEEEE_02cc11f0;
  puStack_90 = PTR__ZTVN4Aska8THashSetIjNS_7THasherIjEENS_8TEqualToIjEENS_10TAllocatorIjEEEE_02cc11f0
               + 0x10;
  fStack_84 = 0.75;
  uStack_80 = 0;
  uStack_7c = 0;
  if (param_2 >> 0x3d == 0) {
    puStack_70 = (undefined1 *)Aska::MemoryManagerAdapter::AlignedMalloc(unsigned long, unsigned long)(param_2 << 3,4);
  }
  else {
    puStack_70 = (undefined1 *)0x0;
  }
  if (puStack_70 == (undefined1 *)0x0) {
    param_2 = 0;
  }
  if (param_2 == 0) {
    fVar10 = *(float *)(param_1 + 0xc);
code_r0x018060fc:
    if (fVar10 <= 0.0) goto code_r0x0180610c;
  }
  else {
    uVar1 = (param_2 * 8 - 8 >> 3) + 1;
    puVar4 = puStack_70;
    if ((uVar1 < 2) || (uVar7 = uVar1 & 0x3ffffffffffffffe, uVar7 == 0)) {
code_r0x018060b8:
      do {
        puVar3 = puVar4 + 8;
        *puVar4 = 0;
        puVar4 = puVar3;
      } while (puStack_70 + param_2 * 8 != puVar3);
    }
    else {
      puVar4 = puStack_70 + uVar7 * 8;
      puVar3 = puStack_70 + 8;
      uVar9 = uVar7;
      do {
        puVar3[-8] = 0;
        *puVar3 = 0;
        uVar9 = uVar9 - 2;
        puVar3 = puVar3 + 0x10;
      } while (uVar9 != 0);
      if (uVar1 != uVar7) goto code_r0x018060b8;
    }
    fVar10 = *(float *)(param_1 + 0xc);
    if (param_2 == 0) goto code_r0x018060fc;
    fVar11 = (float)NEON_ucvtf(uStack_80);
    if (fVar10 <= fVar11 / (float)param_2) goto code_r0x0180610c;
  }
  fStack_84 = fVar10;
code_r0x0180610c:
  pcStack_58 = *(char **)(param_1 + 0x20);
  lVar8 = *(long *)(param_1 + 0x28);
  pcStack_60 = pcStack_58 + lVar8 * 8;
  pcStack_48 = pcStack_60;
  if ((*(int *)(param_1 + 0x10) != 0) && (pcStack_48 = pcStack_58, lVar8 != 0)) {
    lVar8 = lVar8 << 3;
    pcVar6 = pcStack_58;
    do {
      pcStack_48 = pcVar6;
      if (*pcVar6 == '\x01') break;
      lVar8 = lVar8 + -8;
      pcVar6 = pcVar6 + 8;
      pcStack_48 = pcStack_60;
    } while (lVar8 != 0);
  }
  uStack_68 = param_2;
  pcStack_50 = pcStack_60;
  pcStack_40 = pcStack_58;
  pcStack_38 = pcStack_60;
  void Aska::THashSet<unsigned int, Aska::THasher<unsigned int>, Aska::TEqualTo<unsigned int>, Aska::TAllocator<unsigned int> >::Insert<Aska::THashMapIterator<Aska::detail::THashMapBucketArray<Aska::detail::THashMapBucket<unsigned int>, Aska::TAllocator<Aska::detail::THashMapBucket<unsigned int> > > > >(Aska::THashMapIterator<Aska::detail::THashMapBucketArray<Aska::detail::THashMapBucket<unsigned int>, Aska::TAllocator<Aska::detail::THashMapBucket<unsigned int> > > >, Aska::THashMapIterator<Aska::detail::THashMapBucketArray<Aska::detail::THashMapBucket<unsigned int>, Aska::TAllocator<Aska::detail::THashMapBucket<unsigned int> > > >)(&puStack_90,&pcStack_48,&pcStack_60);
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

// ==== void Aska::THashSet<unsigned int, Aska::THasher<unsigned int>, Aska::TEqualTo<unsigned int>, Aska::TAllocator<unsigned int> >::Insert<Aska::THashMapIterator<Aska::detail::THashMapBucketArray<Aska::detail::THashMapBucket<unsigned int>, Aska::TAllocator<Aska::detail::THashMapBucket<unsigned int> > > > >(Aska::THashMapIterator<Aska::detail::THashMapBucketArray<Aska::detail::THashMapBucket<unsigned int>, Aska::TAllocator<Aska::detail::THashMapBucket<unsigned int> > > >, Aska::THashMapIterator<Aska::detail::THashMapBucketArray<Aska::detail::THashMapBucket<unsigned int>, Aska::TAllocator<Aska::detail::THashMapBucket<unsigned int> > > >)
// vaddr 0x17061e0 | ghidra 0x18061e0 | size 452 | symbol _ZN4Aska8THashSetIjNS_7THasherIjEENS_8TEqualToIjEENS_10TAllocatorIjEEE6InsertINS_16THashMapIteratorINS_6detail19THashMapBucketArrayINSA_14THashMapBucketIjEENS5_ISD_EEEEEEEEvT_SH_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska8THashSetIjNS_7THasherIjEENS_8TEqualToIjEENS_10TAllocatorIjEEE6InsertINS_16THashMapIteratorINS_6detail19THashMapBucketArrayINSA_14THashMapBucketIjEENS5_ISD_EEEEEEEEvT_SH_
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
        pcVar10 = pcVar10 + 8;
        pcVar5 = pcVar10;
      } while (*pcVar10 != '\x01');
      pcVar10 = pcVar5;
    } while (pcVar10 != pcVar7);
  }
  uVar9 = (ulong)((float)(lVar8 + (ulong)*(uint *)(param_1 + 0x10) +
                         (ulong)*(uint *)(param_1 + 0x14)) / *(float *)(param_1 + 0xc));
  if (*(ulong *)(param_1 + 0x28) < uVar9) {
    Aska::THashSet<unsigned int, Aska::THasher<unsigned int>, Aska::TEqualTo<unsigned int>, Aska::TAllocator<unsigned int> >::Rehash_(unsigned long)(param_1,uVar9 << 1 | 1);
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
          pcVar10 = (char *)(*(long *)(param_1 + 0x20) + (uVar1 - uVar4 * uVar9) * 8);
          cVar3 = *pcVar10;
          if (cVar3 == '\x01') {
            if (*(uint *)(pcVar10 + 4) == uVar2) goto code_r0x0180635c;
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
          if (*pcVar10 == '\0') {
code_r0x01806348:
            *(int *)(param_1 + 0x10) = *(int *)(param_1 + 0x10) + 1;
          }
          else if (*pcVar10 == '\x02') {
            *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + -1;
            goto code_r0x01806348;
          }
          *pcVar10 = '\x01';
          pcVar6 = (char *)*param_2;
        }
      }
code_r0x0180635c:
      pcVar7 = pcVar6;
      do {
        pcVar6 = (char *)param_2[2];
        if ((char *)param_2[2] == pcVar7) break;
        pcVar6 = pcVar7 + 8;
        *param_2 = (long)pcVar6;
        pcVar10 = pcVar7 + 8;
        pcVar7 = pcVar6;
      } while (*pcVar10 != '\x01');
    } while (pcVar6 != (char *)*param_3);
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

// ==== Aska::THashMap<unsigned int, unsigned long, Aska::THasher<unsigned int>, Aska::TEqualTo<unsigned int>, Aska::TAllocator<Aska::TPair<unsigned int const, unsigned long> > >::~THashMap()
// vaddr 0x1e85484 | ghidra 0x1f85484 | size 64 | symbol _ZN4Aska8THashMapIjmNS_7THasherIjEENS_8TEqualToIjEENS_10TAllocatorINS_5TPairIKjmEEEEED2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska8THashMapIjmNS_7THasherIjEENS_8TEqualToIjEENS_10TAllocatorINS_5TPairIKjmEEEEED2Ev
               (long *param_1)

{
  *param_1 = (long)(
                   PTR__ZTVN4Aska8THashMapIjmNS_7THasherIjEENS_8TEqualToIjEENS_10TAllocatorINS_5TPairIKjmEEEEEE_02cbcdd8
                   + 0x10);
  if (param_1[4] != 0) {
    Aska::MemoryManagerAdapter::AlignedFree(void*)();
    param_1[4] = 0;
    param_1[5] = 0;
  }
  param_1[2] = 0;
  return;
}

// ==== Aska::THashMap<unsigned int, unsigned long, Aska::THasher<unsigned int>, Aska::TEqualTo<unsigned int>, Aska::TAllocator<Aska::TPair<unsigned int const, unsigned long> > >::~THashMap()
// vaddr 0x1e854c4 | ghidra 0x1f854c4 | size 48 | symbol _ZN4Aska8THashMapIjmNS_7THasherIjEENS_8TEqualToIjEENS_10TAllocatorINS_5TPairIKjmEEEEED0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska8THashMapIjmNS_7THasherIjEENS_8TEqualToIjEENS_10TAllocatorINS_5TPairIKjmEEEEED0Ev
               (long *param_1)

{
  *param_1 = (long)(
                   PTR__ZTVN4Aska8THashMapIjmNS_7THasherIjEENS_8TEqualToIjEENS_10TAllocatorINS_5TPairIKjmEEEEEE_02cbcdd8
                   + 0x10);
  if (param_1[4] != 0) {
    Aska::MemoryManagerAdapter::AlignedFree(void*)();
  }
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::THashMap<unsigned int, unsigned long, Aska::THasher<unsigned int>, Aska::TEqualTo<unsigned int>, Aska::TAllocator<Aska::TPair<unsigned int const, unsigned long> > >::Rehash_(unsigned long)
// vaddr 0x1e854f4 | ghidra 0x1f854f4 | size 516 | symbol _ZN4Aska8THashMapIjmNS_7THasherIjEENS_8TEqualToIjEENS_10TAllocatorINS_5TPairIKjmEEEEE7Rehash_Em | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska8THashMapIjmNS_7THasherIjEENS_8TEqualToIjEENS_10TAllocatorINS_5TPairIKjmEEEEE7Rehash_Em
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
  PTR__ZTVN4Aska8THashMapIjmNS_7THasherIjEENS_8TEqualToIjEENS_10TAllocatorINS_5TPairIKjmEEEEEE_02cbcdd8
  ;
  puStack_90 = PTR__ZTVN4Aska8THashMapIjmNS_7THasherIjEENS_8TEqualToIjEENS_10TAllocatorINS_5TPairIKjmEEEEEE_02cbcdd8
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
code_r0x01f8560c:
    if (fVar10 <= 0.0) goto code_r0x01f8561c;
  }
  else {
    uVar1 = (param_2 * 0x18 - 0x18) / 0x18 + 1;
    puVar3 = puStack_70;
    if ((uVar1 < 2) || (uVar7 = uVar1 & 0x1ffffffffffffffe, uVar7 == 0)) {
code_r0x01f855c4:
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
      if (uVar1 != uVar7) goto code_r0x01f855c4;
    }
    fVar10 = *(float *)(param_1 + 0xc);
    if (param_2 == 0) goto code_r0x01f8560c;
    fVar11 = (float)NEON_ucvtf(uStack_80);
    if (fVar10 <= fVar11 / (float)param_2) goto code_r0x01f8561c;
  }
  fStack_84 = fVar10;
code_r0x01f8561c:
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
  void Aska::THashMap<unsigned int, unsigned long, Aska::THasher<unsigned int>, Aska::TEqualTo<unsigned int>, Aska::TAllocator<Aska::TPair<unsigned int const, unsigned long> > >::Insert<Aska::THashMapIterator<Aska::detail::THashMapBucketArray<Aska::detail::THashMapBucket<Aska::TPair<unsigned int const, unsigned long> >, Aska::TAllocator<Aska::detail::THashMapBucket<Aska::TPair<unsigned int const, unsigned long> > > > > >(Aska::THashMapIterator<Aska::detail::THashMapBucketArray<Aska::detail::THashMapBucket<Aska::TPair<unsigned int const, unsigned long> >, Aska::TAllocator<Aska::detail::THashMapBucket<Aska::TPair<unsigned int const, unsigned long> > > > >, Aska::THashMapIterator<Aska::detail::THashMapBucketArray<Aska::detail::THashMapBucket<Aska::TPair<unsigned int const, unsigned long> >, Aska::TAllocator<Aska::detail::THashMapBucket<Aska::TPair<unsigned int const, unsigned long> > > > >)(&puStack_90,&pcStack_48,&pcStack_60);
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

// ==== void Aska::THashMap<unsigned int, unsigned long, Aska::THasher<unsigned int>, Aska::TEqualTo<unsigned int>, Aska::TAllocator<Aska::TPair<unsigned int const, unsigned long> > >::Insert<Aska::THashMapIterator<Aska::detail::THashMapBucketArray<Aska::detail::THashMapBucket<Aska::TPair<unsigned int const, unsigned long> >, Aska::TAllocator<Aska::detail::THashMapBucket<Aska::TPair<unsigned int const, unsigned long> > > > > >(Aska::THashMapIterator<Aska::detail::THashMapBucketArray<Aska::detail::THashMapBucket<Aska::TPair<unsigned int const, unsigned long> >, Aska::TAllocator<Aska::detail::THashMapBucket<Aska::TPair<unsigned int const, unsigned long> > > > >, Aska::THashMapIterator<Aska::detail::THashMapBucketArray<Aska::detail::THashMapBucket<Aska::TPair<unsigned int const, unsigned long> >, Aska::TAllocator<Aska::detail::THashMapBucket<Aska::TPair<unsigned int const, unsigned long> > > > >)
// vaddr 0x1e856f8 | ghidra 0x1f856f8 | size 468 | symbol _ZN4Aska8THashMapIjmNS_7THasherIjEENS_8TEqualToIjEENS_10TAllocatorINS_5TPairIKjmEEEEE6InsertINS_16THashMapIteratorINS_6detail19THashMapBucketArrayINSD_14THashMapBucketIS8_EENS5_ISG_EEEEEEEEvT_SK_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska8THashMapIjmNS_7THasherIjEENS_8TEqualToIjEENS_10TAllocatorINS_5TPairIKjmEEEEE6InsertINS_16THashMapIteratorINS_6detail19THashMapBucketArrayINSD_14THashMapBucketIS8_EENS5_ISG_EEEEEEEEvT_SK_
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
        pcVar10 = pcVar10 + 0x18;
        pcVar5 = pcVar10;
      } while (*pcVar10 != '\x01');
      pcVar10 = pcVar5;
    } while (pcVar10 != pcVar7);
  }
  uVar9 = (ulong)((float)(lVar8 + (ulong)*(uint *)(param_1 + 0x10) +
                         (ulong)*(uint *)(param_1 + 0x14)) / *(float *)(param_1 + 0xc));
  if (*(ulong *)(param_1 + 0x28) < uVar9) {
    Aska::THashMap<unsigned int, unsigned long, Aska::THasher<unsigned int>, Aska::TEqualTo<unsigned int>, Aska::TAllocator<Aska::TPair<unsigned int const, unsigned long> > >::Rehash_(unsigned long)(param_1,uVar9 << 1 | 1);
    pcVar6 = (char *)*param_2;
    pcVar7 = (char *)*param_3;
  }
  if (pcVar6 != pcVar7) {
    do {
      uVar9 = *(ulong *)(param_1 + 0x28);
      if (uVar9 != 0) {
        uVar2 = *(uint *)(pcVar6 + 8);
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
          pcVar10 = (char *)(*(long *)(param_1 + 0x20) + lVar8 * 0x18);
          cVar3 = *pcVar10;
          if (cVar3 == '\x01') {
            if (*(uint *)(*(long *)(param_1 + 0x20) + lVar8 * 0x18 + 8) == uVar2)
            goto code_r0x01f85884;
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
          *(uint *)(pcVar10 + 8) = uVar2;
          *(undefined8 *)(pcVar10 + 0x10) = *(undefined8 *)(pcVar6 + 0x10);
          if (*pcVar10 == '\0') {
code_r0x01f85870:
            *(int *)(param_1 + 0x10) = *(int *)(param_1 + 0x10) + 1;
          }
          else if (*pcVar10 == '\x02') {
            *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + -1;
            goto code_r0x01f85870;
          }
          *pcVar10 = '\x01';
          pcVar6 = (char *)*param_2;
        }
      }
code_r0x01f85884:
      pcVar7 = pcVar6;
      do {
        pcVar6 = (char *)param_2[2];
        if ((char *)param_2[2] == pcVar7) break;
        pcVar6 = pcVar7 + 0x18;
        *param_2 = (long)pcVar6;
        pcVar10 = pcVar7 + 0x18;
        pcVar7 = pcVar6;
      } while (*pcVar10 != '\x01');
    } while (pcVar6 != (char *)*param_3);
  }
  return;
}

// ==== Aska::THashMap<unsigned int, unsigned int, Aska::THasher<unsigned int>, Aska::TEqualTo<unsigned int>, Aska::TAllocator<Aska::TPair<unsigned int const, unsigned int> > >::~THashMap()
// vaddr 0x2368dd0 | ghidra 0x2468dd0 | size 64 | symbol _ZN4Aska8THashMapIjjNS_7THasherIjEENS_8TEqualToIjEENS_10TAllocatorINS_5TPairIKjjEEEEED2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska8THashMapIjjNS_7THasherIjEENS_8TEqualToIjEENS_10TAllocatorINS_5TPairIKjjEEEEED2Ev
               (long *param_1)

{
  *param_1 = (long)(
                   PTR__ZTVN4Aska8THashMapIjjNS_7THasherIjEENS_8TEqualToIjEENS_10TAllocatorINS_5TPairIKjjEEEEEE_02cc1a90
                   + 0x10);
  if (param_1[4] != 0) {
    Aska::MemoryManagerAdapter::AlignedFree(void*)();
    param_1[4] = 0;
    param_1[5] = 0;
  }
  param_1[2] = 0;
  return;
}

// ==== Aska::THashMap<unsigned int, unsigned int, Aska::THasher<unsigned int>, Aska::TEqualTo<unsigned int>, Aska::TAllocator<Aska::TPair<unsigned int const, unsigned int> > >::~THashMap()
// vaddr 0x2368e10 | ghidra 0x2468e10 | size 48 | symbol _ZN4Aska8THashMapIjjNS_7THasherIjEENS_8TEqualToIjEENS_10TAllocatorINS_5TPairIKjjEEEEED0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska8THashMapIjjNS_7THasherIjEENS_8TEqualToIjEENS_10TAllocatorINS_5TPairIKjjEEEEED0Ev
               (long *param_1)

{
  *param_1 = (long)(
                   PTR__ZTVN4Aska8THashMapIjjNS_7THasherIjEENS_8TEqualToIjEENS_10TAllocatorINS_5TPairIKjjEEEEEE_02cc1a90
                   + 0x10);
  if (param_1[4] != 0) {
    Aska::MemoryManagerAdapter::AlignedFree(void*)();
  }
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::THashMap<unsigned int, unsigned int, Aska::THasher<unsigned int>, Aska::TEqualTo<unsigned int>, Aska::TAllocator<Aska::TPair<unsigned int const, unsigned int> > >::Rehash_(unsigned long)
// vaddr 0x2369168 | ghidra 0x2469168 | size 516 | symbol _ZN4Aska8THashMapIjjNS_7THasherIjEENS_8TEqualToIjEENS_10TAllocatorINS_5TPairIKjjEEEEE7Rehash_Em | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska8THashMapIjjNS_7THasherIjEENS_8TEqualToIjEENS_10TAllocatorINS_5TPairIKjjEEEEE7Rehash_Em
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
  PTR__ZTVN4Aska8THashMapIjjNS_7THasherIjEENS_8TEqualToIjEENS_10TAllocatorINS_5TPairIKjjEEEEEE_02cc1a90
  ;
  puStack_90 = PTR__ZTVN4Aska8THashMapIjjNS_7THasherIjEENS_8TEqualToIjEENS_10TAllocatorINS_5TPairIKjjEEEEEE_02cc1a90
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
code_r0x02469280:
    if (fVar10 <= 0.0) goto code_r0x02469290;
  }
  else {
    uVar1 = (param_2 * 0xc - 0xc) / 0xc + 1;
    puVar3 = puStack_70;
    if ((uVar1 < 2) || (uVar7 = uVar1 & 0x3ffffffffffffffe, uVar7 == 0)) {
code_r0x02469238:
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
      if (uVar1 != uVar7) goto code_r0x02469238;
    }
    fVar10 = *(float *)(param_1 + 0xc);
    if (param_2 == 0) goto code_r0x02469280;
    fVar11 = (float)NEON_ucvtf(uStack_80);
    if (fVar10 <= fVar11 / (float)param_2) goto code_r0x02469290;
  }
  fStack_84 = fVar10;
code_r0x02469290:
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
  void Aska::THashMap<unsigned int, unsigned int, Aska::THasher<unsigned int>, Aska::TEqualTo<unsigned int>, Aska::TAllocator<Aska::TPair<unsigned int const, unsigned int> > >::Insert<Aska::THashMapIterator<Aska::detail::THashMapBucketArray<Aska::detail::THashMapBucket<Aska::TPair<unsigned int const, unsigned int> >, Aska::TAllocator<Aska::detail::THashMapBucket<Aska::TPair<unsigned int const, unsigned int> > > > > >(Aska::THashMapIterator<Aska::detail::THashMapBucketArray<Aska::detail::THashMapBucket<Aska::TPair<unsigned int const, unsigned int> >, Aska::TAllocator<Aska::detail::THashMapBucket<Aska::TPair<unsigned int const, unsigned int> > > > >, Aska::THashMapIterator<Aska::detail::THashMapBucketArray<Aska::detail::THashMapBucket<Aska::TPair<unsigned int const, unsigned int> >, Aska::TAllocator<Aska::detail::THashMapBucket<Aska::TPair<unsigned int const, unsigned int> > > > >)(&puStack_90,&pcStack_48,&pcStack_60);
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

// ==== void Aska::THashMap<unsigned int, unsigned int, Aska::THasher<unsigned int>, Aska::TEqualTo<unsigned int>, Aska::TAllocator<Aska::TPair<unsigned int const, unsigned int> > >::Insert<Aska::THashMapIterator<Aska::detail::THashMapBucketArray<Aska::detail::THashMapBucket<Aska::TPair<unsigned int const, unsigned int> >, Aska::TAllocator<Aska::detail::THashMapBucket<Aska::TPair<unsigned int const, unsigned int> > > > > >(Aska::THashMapIterator<Aska::detail::THashMapBucketArray<Aska::detail::THashMapBucket<Aska::TPair<unsigned int const, unsigned int> >, Aska::TAllocator<Aska::detail::THashMapBucket<Aska::TPair<unsigned int const, unsigned int> > > > >, Aska::THashMapIterator<Aska::detail::THashMapBucketArray<Aska::detail::THashMapBucket<Aska::TPair<unsigned int const, unsigned int> >, Aska::TAllocator<Aska::detail::THashMapBucket<Aska::TPair<unsigned int const, unsigned int> > > > >)
// vaddr 0x236936c | ghidra 0x246936c | size 468 | symbol _ZN4Aska8THashMapIjjNS_7THasherIjEENS_8TEqualToIjEENS_10TAllocatorINS_5TPairIKjjEEEEE6InsertINS_16THashMapIteratorINS_6detail19THashMapBucketArrayINSD_14THashMapBucketIS8_EENS5_ISG_EEEEEEEEvT_SK_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska8THashMapIjjNS_7THasherIjEENS_8TEqualToIjEENS_10TAllocatorINS_5TPairIKjjEEEEE6InsertINS_16THashMapIteratorINS_6detail19THashMapBucketArrayINSD_14THashMapBucketIS8_EENS5_ISG_EEEEEEEEvT_SK_
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
    Aska::THashMap<unsigned int, unsigned int, Aska::THasher<unsigned int>, Aska::TEqualTo<unsigned int>, Aska::TAllocator<Aska::TPair<unsigned int const, unsigned int> > >::Rehash_(unsigned long)(param_1,uVar9 << 1 | 1);
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
            goto code_r0x024694f8;
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
          *(undefined4 *)(pcVar10 + 8) = *(undefined4 *)(pcVar6 + 8);
          if (*pcVar10 == '\0') {
code_r0x024694e4:
            *(int *)(param_1 + 0x10) = *(int *)(param_1 + 0x10) + 1;
          }
          else if (*pcVar10 == '\x02') {
            *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + -1;
            goto code_r0x024694e4;
          }
          *pcVar10 = '\x01';
          pcVar6 = (char *)*param_2;
        }
      }
code_r0x024694f8:
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
