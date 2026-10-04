// port/decomp/resource/downloader.c: Ghidra decompiles for the resource subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-04 06:19 UTC: tools/decomp.sh '--into' 'resource/downloader' 'CGameResourceDownloader::' 'CGameResourceDownloader\('

// ==== CGameResourceDownloader::CGameResourceDownloader()
// vaddr 0x17d0034 | ghidra 0x18d0034 | size 420 | symbol _ZN23CGameResourceDownloaderC1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN23CGameResourceDownloaderC2Ev(long *param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  
  Framework::CFiberUnit::CFiberUnit(unsigned int)(param_1,0x600);
  puVar2 = PTR__ZTV23CGameResourceDownloader_02cbe610;
  puVar1 = PTR__ZTVN4Aska6TArrayIPN23CGameResourceDownloader13CDownloadNodeELb0EEE_02cb9088;
  *(undefined4 *)(param_1 + 0xe) = 0;
  *param_1 = (long)(puVar2 + 0x10);
  *(undefined4 *)(param_1 + 0x15) = 0;
  param_1[8] = (long)(puVar1 + 0x10);
  param_1[0xf] = (long)(puVar1 + 0x10);
  puVar1 = PTR__ZTVN4Aska6TArrayIN23CGameResourceDownloader24tDownloadNodeInitializerELb0EEE_02cc2cf8
           + 0x10;
  *(undefined4 *)(param_1 + 0x1c) = 0;
  param_1[10] = 0;
  param_1[9] = 0;
  param_1[0xc] = 0;
  param_1[0xb] = 0;
  param_1[0xd] = 8;
  param_1[0x11] = 0;
  param_1[0x10] = 0;
  param_1[0x13] = 0;
  param_1[0x12] = 0;
  param_1[0x14] = 8;
  param_1[0x1a] = 0;
  param_1[0x19] = 0;
  param_1[0x18] = 0;
  param_1[0x17] = 0;
  param_1[0x1b] = 8;
  param_1[0x16] = (long)puVar1;
  memset(param_1 + 0x1d,0,0x50);
  *(undefined4 *)(param_1 + 0x27) = 0x3f800000;
  *(undefined8 *)((long)param_1 + 0x14f) = 0;
  param_1[0x29] = 0;
  param_1[0x28] = 0;
  *(undefined4 *)((long)param_1 + 0x157) = 0x101;
  *(undefined2 *)((long)param_1 + 0x15b) = 0x100;
  *(undefined8 *)((long)param_1 + 0x15d) = 0;
  *(undefined1 *)((long)param_1 + 0x167) = 0;
  *(undefined2 *)((long)param_1 + 0x165) = 0;
  Framework::CMutex::CMutex()(param_1 + 0x2e);
  param_1[0x45] = 0;
  param_1[0x44] = 0;
  param_1[0x46] = 0;
  *(undefined1 *)((long)param_1 + 0x221) = 0;
  memset(param_1 + 0x47,0,0x44);
  Aska::ASON::ASON()(param_1 + 0x50);
  Aska::ASON::ASON()(param_1 + 0x62);
  Aska::ASON::ASON()(param_1 + 0x74);
  param_1[0x88] = 0;
  param_1[0x87] = 0;
  param_1[0x86] = 0;
  puVar1 = PTR__ZTVN4Aska6TArrayIN9Framework13TStaticStringILm256EEELb0EEE_02cc2958;
  param_1[0x8d] = 0;
  param_1[0x8c] = 0;
  param_1[0x8b] = 0;
  param_1[0x8a] = 0;
  param_1[0x95] = 0;
  param_1[0x94] = 0;
  param_1[0x93] = 0;
  param_1[0x92] = 0;
  param_1[0x91] = 0;
  param_1[0x90] = 0;
  param_1[0xb7] = 0;
  param_1[0xb6] = 0;
  param_1[0x8e] = 8;
  *(undefined4 *)(param_1 + 0x8f) = 0;
  param_1[0x9c] = 0;
  param_1[0x9e] = 0;
  param_1[0xa4] = 0;
  param_1[0xaa] = 0;
  param_1[0xb0] = 0;
  param_1[0xb2] = 0;
  *(undefined1 *)(param_1 + 0xb3) = 0;
  param_1[0xb4] = 0;
  param_1[0x96] = 0;
  param_1[0xb8] = 0;
  *(undefined4 *)(param_1 + 0xb9) = 0;
  param_1[0xbb] = 0;
  param_1[0xba] = 0;
  param_1[0xbc] = 0;
  *(undefined1 *)(param_1 + 0xb5) = 1;
  *(undefined1 *)((long)param_1 + 0x154) = 1;
  param_1[0x89] = (long)(puVar1 + 0x10);
  param_1[0xb7] = 0;
  return;
}

// ==== CGameResourceDownloader::~CGameResourceDownloader()
// vaddr 0x17d01d8 | ghidra 0x18d01d8 | size 912 | symbol _ZN23CGameResourceDownloaderD2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN23CGameResourceDownloaderD1Ev(long *param_1)

{
  undefined *puVar1;
  byte bVar2;
  long lVar3;
  long *plVar4;
  code *pcVar5;
  long lVar6;
  long lVar7;
  long *plVar8;
  
  *param_1 = (long)(PTR__ZTV23CGameResourceDownloader_02cbe610 + 0x10);
  if (param_1[0xb6] != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)();
  }
  lVar7 = param_1[0xb4];
  param_1[0xb4] = 0;
  if (lVar7 != 0) {
    if (*(long *)(lVar7 + 0x28) != 0) {
      lVar6 = *(long *)(lVar7 + 0x18);
      plVar4 = *(long **)(lVar7 + 0x20);
      *(undefined8 *)(*plVar4 + 8) = *(undefined8 *)(lVar6 + 8);
      **(long **)(lVar6 + 8) = *plVar4;
      *(undefined8 *)(lVar7 + 0x28) = 0;
      while (plVar4 != (long *)(lVar7 + 0x18)) {
        plVar8 = (long *)plVar4[1];
        if ((*(byte *)(plVar4 + 2) & 1) != 0) {
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar4[4]);
        }
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar4);
        plVar4 = plVar8;
      }
    }
    operator delete(void*)(lVar7);
  }
  plVar4 = (long *)param_1[0xb0];
  if (param_1 + 0xac == plVar4) {
    pcVar5 = *(code **)(*plVar4 + 0x20);
code_r0x018d029c:
    (*pcVar5)();
  }
  else if (plVar4 != (long *)0x0) {
    pcVar5 = *(code **)(*plVar4 + 0x28);
    goto code_r0x018d029c;
  }
  plVar4 = (long *)param_1[0xaa];
  if (param_1 + 0xa6 == plVar4) {
    pcVar5 = *(code **)(*plVar4 + 0x20);
code_r0x018d02c8:
    (*pcVar5)();
  }
  else if (plVar4 != (long *)0x0) {
    pcVar5 = *(code **)(*plVar4 + 0x28);
    goto code_r0x018d02c8;
  }
  plVar4 = (long *)param_1[0xa4];
  if (param_1 + 0xa0 == plVar4) {
    pcVar5 = *(code **)(*plVar4 + 0x20);
code_r0x018d02f4:
    (*pcVar5)();
  }
  else if (plVar4 != (long *)0x0) {
    pcVar5 = *(code **)(*plVar4 + 0x28);
    goto code_r0x018d02f4;
  }
  plVar4 = (long *)param_1[0x9c];
  if (param_1 + 0x98 == plVar4) {
    pcVar5 = *(code **)(*plVar4 + 0x20);
  }
  else {
    if (plVar4 == (long *)0x0) goto code_r0x018d0324;
    pcVar5 = *(code **)(*plVar4 + 0x28);
  }
  (*pcVar5)();
code_r0x018d0324:
  lVar7 = param_1[0x94];
  if (lVar7 != 0) {
    lVar6 = param_1[0x95];
    if (lVar6 != lVar7) {
      param_1[0x95] = lVar6 + (~((lVar6 + -8) - lVar7) & 0xfffffffffffffff8U);
    }
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)();
  }
  param_1[0x89] =
       (long)(PTR__ZTVN4Aska6TArrayIN9Framework13TStaticStringILm256EEELb0EEE_02cc2958 + 0x10);
  *(ushort *)((long)param_1 + 0x47a) = *(ushort *)((long)param_1 + 0x47a) | 1;
  if (param_1[0x8a] != 0) {
    operator delete[](void*)();
    param_1[0x8a] = 0;
  }
  lVar7 = param_1[0x86];
  param_1[0x8d] = 0;
  param_1[0x8c] = 0;
  param_1[0x8b] = 0;
  if (lVar7 != 0) {
    lVar6 = param_1[0x87];
    if (lVar6 != lVar7) {
      do {
        param_1[0x87] = lVar6 + -0x90;
        (*(code *)**(undefined8 **)(lVar6 + -0x90))();
        lVar6 = param_1[0x87];
      } while (lVar6 != lVar7);
      lVar7 = param_1[0x86];
    }
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(lVar7);
  }
  Aska::ASON::~ASON()(param_1 + 0x74);
  Aska::ASON::~ASON()(param_1 + 0x62);
  Aska::ASON::~ASON()(param_1 + 0x50);
  if ((*(byte *)(param_1 + 0x4a) & 1) == 0) {
    bVar2 = *(byte *)(param_1 + 0x47);
  }
  else {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(param_1[0x4c]);
    bVar2 = *(byte *)(param_1 + 0x47);
  }
  if ((bVar2 & 1) == 0) {
    bVar2 = *(byte *)(param_1 + 0x44);
  }
  else {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(param_1[0x49]);
    bVar2 = *(byte *)(param_1 + 0x44);
  }
  if ((bVar2 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(param_1[0x46]);
  }
  Framework::CMutex::~CMutex()(param_1 + 0x2e);
  plVar4 = (long *)param_1[0x25];
  while (plVar4 != (long *)0x0) {
    plVar4 = (long *)*plVar4;
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)();
  }
  lVar7 = param_1[0x23];
  param_1[0x23] = 0;
  if (lVar7 != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)();
  }
  lVar7 = param_1[0x20];
  if (lVar7 != 0) {
    lVar6 = param_1[0x21];
    if (lVar6 != lVar7) {
      do {
        param_1[0x21] = lVar6 + -0x18;
        lVar3 = lVar6 + -0x18;
        if ((*(byte *)(lVar6 + -0x18) & 1) != 0) {
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(*(undefined8 *)(lVar6 + -8));
          lVar3 = param_1[0x21];
        }
        lVar6 = lVar3;
      } while (lVar6 != lVar7);
      lVar7 = param_1[0x20];
    }
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(lVar7);
  }
  lVar7 = param_1[0x1d];
  if (lVar7 != 0) {
    lVar6 = param_1[0x1e];
    if (lVar6 != lVar7) {
      param_1[0x1e] = lVar6 + (~((lVar6 + -8) - lVar7) & 0xfffffffffffffff8U);
    }
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)();
  }
  param_1[0x16] =
       (long)(
             PTR__ZTVN4Aska6TArrayIN23CGameResourceDownloader24tDownloadNodeInitializerELb0EEE_02cc2cf8
             + 0x10);
  *(ushort *)((long)param_1 + 0xe2) = *(ushort *)((long)param_1 + 0xe2) | 1;
  Aska::TArray<CGameResourceDownloader::tDownloadNodeInitializer, false>::Clear()(param_1 + 0x16);
  puVar1 = PTR__ZTVN4Aska6TArrayIPN23CGameResourceDownloader13CDownloadNodeELb0EEE_02cb9088 + 0x10;
  param_1[0xf] = (long)puVar1;
  *(ushort *)((long)param_1 + 0xaa) = *(ushort *)((long)param_1 + 0xaa) | 1;
  if (param_1[0x10] != 0) {
    operator delete[](void*)();
    param_1[0x10] = 0;
  }
  param_1[0x12] = 0;
  param_1[0x13] = 0;
  param_1[0x11] = 0;
  param_1[8] = (long)puVar1;
  *(ushort *)((long)param_1 + 0x72) = *(ushort *)((long)param_1 + 0x72) | 1;
  if (param_1[9] != 0) {
    operator delete[](void*)();
    param_1[9] = 0;
  }
  param_1[0xb] = 0;
  param_1[0xc] = 0;
  param_1[10] = 0;
  (*(code *)PTR__ZN9Framework10CFiberUnitD1Ev_02c90ac0)(param_1);
  return;
}

// ==== Aska::TArray<CGameResourceDownloader::tDownloadNodeInitializer, false>::~TArray()
// vaddr 0x17d0568 | ghidra 0x18d0568 | size 32 | symbol _ZN4Aska6TArrayIN23CGameResourceDownloader24tDownloadNodeInitializerELb0EED2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6TArrayIN23CGameResourceDownloader24tDownloadNodeInitializerELb0EED2Ev(long *param_1)

{
  *param_1 = (long)(
                   PTR__ZTVN4Aska6TArrayIN23CGameResourceDownloader24tDownloadNodeInitializerELb0EEE_02cc2cf8
                   + 0x10);
  *(ushort *)((long)param_1 + 0x32) = *(ushort *)((long)param_1 + 0x32) | 1;
  (*(code *)
    PTR__ZN4Aska6TArrayIN23CGameResourceDownloader24tDownloadNodeInitializerELb0EE5ClearEv_02c96308)
            ();
  return;
}

// ==== Aska::TArray<CGameResourceDownloader::CDownloadNode*, false>::~TArray()
// vaddr 0x17d0588 | ghidra 0x18d0588 | size 68 | symbol _ZN4Aska6TArrayIPN23CGameResourceDownloader13CDownloadNodeELb0EED2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6TArrayIPN23CGameResourceDownloader13CDownloadNodeELb0EED2Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska6TArrayIPN23CGameResourceDownloader13CDownloadNodeELb0EEE_02cb9088
                   + 0x10);
  *(ushort *)((long)param_1 + 0x32) = *(ushort *)((long)param_1 + 0x32) | 1;
  if (param_1[1] != 0) {
    operator delete[](void*)();
    param_1[1] = 0;
  }
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[2] = 0;
  return;
}

// ==== CGameResourceDownloader::~CGameResourceDownloader()
// vaddr 0x17d05cc | ghidra 0x18d05cc | size 24 | symbol _ZN23CGameResourceDownloaderD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN23CGameResourceDownloaderD0Ev(undefined8 param_1)

{
  CGameResourceDownloader::~CGameResourceDownloader()();
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== CGameResourceDownloader::Initialize()
// vaddr 0x17d05e4 | ghidra 0x18d05e4 | size 304 | symbol _ZN23CGameResourceDownloader10InitializeEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN23CGameResourceDownloader10InitializeEv(long param_1)

{
  undefined8 uVar1;
  long lVar2;
  long lVar3;
  long lVar4;
  long lVar5;
  
  lVar2 = *(long *)(param_1 + 0x50);
  if (lVar2 < 0x100) {
    lVar3 = *(long *)(param_1 + 0x68);
    lVar5 = *(long *)(param_1 + 0x58);
    uVar1 = *(undefined8 *)(param_1 + 0x48);
    if (lVar3 < 0x101) {
      lVar3 = 0x100;
    }
code_r0x018d0614:
    lVar2 = operator new[](unsigned long, void*, unsigned long)(lVar3 << 3,uVar1,4);
    if (lVar2 == 0) {
      *(ushort *)(param_1 + 0x70) = *(ushort *)(param_1 + 0x70) | 1;
    }
    else {
      *(long *)(param_1 + 0x48) = lVar2;
      *(long *)(param_1 + 0x50) = lVar3;
      *(long *)(param_1 + 0x58) = lVar5;
    }
  }
  else if (((lVar2 != 0x100) && (lVar5 = *(long *)(param_1 + 0x58), lVar5 < lVar2)) &&
          ((lVar4 = *(long *)(param_1 + 0x68), lVar3 = lVar5, lVar4 <= lVar5 ||
           (lVar3 = lVar4, lVar4 < lVar2)))) {
    uVar1 = *(undefined8 *)(param_1 + 0x48);
    goto code_r0x018d0614;
  }
  lVar2 = *(long *)(param_1 + 0x88);
  if (lVar2 < 0x20) {
    lVar3 = *(long *)(param_1 + 0xa0);
    lVar5 = *(long *)(param_1 + 0x90);
    uVar1 = *(undefined8 *)(param_1 + 0x80);
    if (lVar3 < 0x21) {
      lVar3 = 0x20;
    }
  }
  else {
    if (((lVar2 == 0x20) || (lVar5 = *(long *)(param_1 + 0x90), lVar2 <= lVar5)) ||
       ((lVar4 = *(long *)(param_1 + 0xa0), lVar3 = lVar5, lVar5 < lVar4 &&
        (lVar3 = lVar4, lVar2 <= lVar4)))) goto code_r0x018d06f8;
    uVar1 = *(undefined8 *)(param_1 + 0x80);
  }
  lVar2 = operator new[](unsigned long, void*, unsigned long)(lVar3 << 3,uVar1,4);
  if (lVar2 == 0) {
    *(ushort *)(param_1 + 0xa8) = *(ushort *)(param_1 + 0xa8) | 1;
  }
  else {
    *(long *)(param_1 + 0x80) = lVar2;
    *(long *)(param_1 + 0x88) = lVar3;
    *(long *)(param_1 + 0x90) = lVar5;
  }
code_r0x018d06f8:
  Framework::CMutex::Initialize()(param_1 + 0x170);
  *(undefined8 *)(param_1 + 0x14c) = 0;
  return;
}

// ==== CGameResourceDownloader::Release()
// vaddr 0x17d0714 | ghidra 0x18d0714 | size 264 | symbol _ZN23CGameResourceDownloader7ReleaseEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN23CGameResourceDownloader7ReleaseEv(long param_1)

{
  undefined8 *puVar1;
  long *plVar2;
  long lVar3;
  long lVar4;
  long lVar5;
  
  lVar3 = *(long *)(param_1 + 0x58);
  *(undefined8 *)(param_1 + 0x60) = 0;
  if (0 < lVar3) {
    lVar4 = 0;
    do {
      plVar2 = *(long **)(*(long *)(param_1 + 0x48) + lVar4 * 8);
      lVar5 = lVar4;
      if (plVar2 != (long *)0x0) {
        (**(code **)(*plVar2 + 0x10))();
        lVar3 = *(long *)(param_1 + 0x58);
        lVar5 = *(long *)(param_1 + 0x60);
      }
      lVar4 = lVar5;
      if ((-1 < lVar5) && (lVar5 < lVar3)) {
        lVar3 = lVar3 + -1;
        if (lVar5 < lVar3) {
          do {
            puVar1 = (undefined8 *)(*(long *)(param_1 + 0x48) + lVar4 * 8);
            lVar4 = lVar4 + 1;
            *puVar1 = puVar1[1];
            lVar3 = *(long *)(param_1 + 0x58) + -1;
          } while (lVar4 < lVar3);
        }
        Aska::TArray<CGameResourceDownloader::CDownloadNode*, false>::Resize(long, bool)(param_1 + 0x40,lVar3,0);
        lVar4 = *(long *)(param_1 + 0x60);
        if (lVar5 <= lVar4) {
          lVar3 = lVar4 + -1;
          if (lVar4 < 1) {
            lVar4 = 0;
          }
          else {
            lVar4 = lVar3;
            if (*(long *)(param_1 + 0x58) <= lVar3) {
              lVar4 = *(long *)(param_1 + 0x58);
            }
          }
          *(long *)(param_1 + 0x60) = lVar4;
        }
      }
      lVar3 = *(long *)(param_1 + 0x58);
    } while (lVar4 < lVar3);
  }
  if (*(long **)(param_1 + 0x5d8) != (long *)0x0) {
    (**(code **)(**(long **)(param_1 + 0x5d8) + 0x18))();
    *(undefined8 *)(param_1 + 0x5d8) = 0;
  }
  if (*(long **)(param_1 + 0x5e0) != (long *)0x0) {
    (**(code **)(**(long **)(param_1 + 0x5e0) + 0x18))();
    *(undefined8 *)(param_1 + 0x5e0) = 0;
  }
  (*(code *)PTR__ZN9Framework6CMutex7ReleaseEv_02c955a8)(param_1 + 0x170);
  return;
}

// ==== CGameResourceDownloader::Reset(bool)
// vaddr 0x17d081c | ghidra 0x18d081c | size 196 | symbol _ZN23CGameResourceDownloader5ResetEb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN23CGameResourceDownloader5ResetEb(long param_1,ulong param_2)

{
  undefined *puVar1;
  long lVar2;
  
  if (*(char *)(param_1 + 0x154) == '\0') {
    *(undefined8 *)(param_1 + 0x160) = 0;
    *(undefined1 *)(param_1 + 0x15c) = 1;
    *(undefined2 *)(param_1 + 0x155) = 1;
    puVar1 = PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
    if (*(long *)(param_1 + 0x5d0) == 0) {
      lVar2 = *(long *)PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
      if (lVar2 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
        lVar2 = *(long *)puVar1;
      }
      lVar2 = CParameterManager::pParameterUI() const(lVar2);
      *(long *)(param_1 + 0x5d0) = lVar2 + 0xc3f8;
    }
    CParameterUI::tEpisodeData::Initialize()();
    CGameResourceDownloader::LoadLocalKVSEpisodeUpdateFlag(bool)(param_1,1);
    if (((param_2 & 1) != 0) && (lVar2 = *(long *)(param_1 + 0x5d8), lVar2 != 0)) {
      if ((*(byte *)(lVar2 + 0x40) & 1) == 0) {
        *(undefined2 *)(lVar2 + 0x40) = 0;
      }
      else {
        **(undefined1 **)(lVar2 + 0x50) = 0;
        *(undefined8 *)(lVar2 + 0x48) = 0;
      }
    }
    *(undefined4 *)(param_1 + 0x140) = 0;
    *(undefined4 *)(param_1 + 0x14c) = 6;
    *(undefined4 *)(param_1 + 0x150) = 0;
  }
  return;
}

// ==== CGameResourceDownloader::LoadLocalKVSEpisodeUpdateFlag(bool)
// vaddr 0x17d08e0 | ghidra 0x18d08e0 | size 408 | symbol _ZN23CGameResourceDownloader29LoadLocalKVSEpisodeUpdateFlagEb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN23CGameResourceDownloader29LoadLocalKVSEpisodeUpdateFlagEb(long param_1,ulong param_2)

{
  bool bVar1;
  long lVar2;
  ulong uVar3;
  ulong uVar4;
  ulong uVar5;
  uint uVar6;
  
  lVar2 = *(long *)(param_1 + 0x5d0);
  *(undefined1 *)(param_1 + 0x15d) = 0;
  *(undefined8 *)(param_1 + 0x5b8) = 0;
  if ((lVar2 == 0) || (*(int *)(param_1 + 0x278) == 0)) {
    return;
  }
  uVar6 = 0;
  if ((param_2 & 1) != 0) goto code_r0x018d0984;
code_r0x018d0924:
  uVar3 = CParameterUI::tEpisodeData::IsReservedDeleteEpisodeState(unsigned int, bool)(lVar2,uVar6,1);
  lVar2 = *(long *)(param_1 + 0x5c0);
  uVar4 = *(ulong *)(param_1 + 0x5b8);
  bVar1 = uVar4 != lVar2 * 0x40;
  if ((uVar3 & 1) == 0) {
    if (bVar1) goto code_r0x018d0a2c;
    if (0x3ffffffffffffffe < uVar4) goto code_r0x018d0a1c;
    goto code_r0x018d0964;
  }
  if (bVar1) goto code_r0x018d09dc;
  if (uVar4 < 0x3fffffffffffffff) goto code_r0x018d09bc;
  do {
    uVar3 = 0x7fffffffffffffff;
    while( true ) {
      std::__ndk1::vector<bool, Framework::CSTLAllocator<bool, Framework::CSTLVectorAllocatorInf> >::reserve(unsigned long)(param_1 + 0x5b0,uVar3);
      uVar4 = *(ulong *)(param_1 + 0x5b8);
code_r0x018d09dc:
      do {
        lVar2 = *(long *)(param_1 + 0x5b0);
        *(ulong *)(param_1 + 0x5b8) = uVar4 + 1;
        uVar5 = uVar4 >> 3 & 0x1ffffffffffffff8;
        uVar3 = *(ulong *)(lVar2 + uVar5) | 1L << (uVar4 & 0x3f);
        while( true ) {
          *(ulong *)(lVar2 + uVar5) = uVar3;
          uVar6 = uVar6 + 1;
          if (*(uint *)(param_1 + 0x278) <= uVar6) {
            return;
          }
          lVar2 = *(long *)(param_1 + 0x5d0);
          if ((param_2 & 1) == 0) goto code_r0x018d0924;
code_r0x018d0984:
          uVar3 = CParameterUI::tEpisodeData::IsDownloadedEpisodeState(unsigned int)(lVar2,uVar6);
          if (((uVar3 & 1) != 0) ||
             (uVar3 = CParameterUI::tEpisodeData::IsReservedDownloadEpisodeState(unsigned int, bool)(*(undefined8 *)(param_1 + 0x5d0),uVar6,1), (uVar3 & 1) != 0))
          break;
          uVar4 = *(ulong *)(param_1 + 0x5b8);
          lVar2 = *(long *)(param_1 + 0x5c0);
          if (uVar4 == lVar2 * 0x40) {
            if (uVar4 < 0x3fffffffffffffff) {
code_r0x018d0964:
              uVar3 = uVar4 + 0x40 & 0xffffffffffffffc0;
              if (uVar3 <= (ulong)(lVar2 << 7)) {
                uVar3 = lVar2 << 7;
              }
            }
            else {
code_r0x018d0a1c:
              uVar3 = 0x7fffffffffffffff;
            }
            std::__ndk1::vector<bool, Framework::CSTLAllocator<bool, Framework::CSTLVectorAllocatorInf> >::reserve(unsigned long)(param_1 + 0x5b0,uVar3);
            uVar4 = *(ulong *)(param_1 + 0x5b8);
          }
code_r0x018d0a2c:
          lVar2 = *(long *)(param_1 + 0x5b0);
          *(ulong *)(param_1 + 0x5b8) = uVar4 + 1;
          uVar5 = uVar4 >> 3 & 0x1ffffffffffffff8;
          uVar3 = *(ulong *)(lVar2 + uVar5) & (1L << (uVar4 & 0x3f) ^ 0xffffffffffffffffU);
        }
        uVar4 = *(ulong *)(param_1 + 0x5b8);
        lVar2 = *(long *)(param_1 + 0x5c0);
      } while (uVar4 != lVar2 * 0x40);
      if (0x3ffffffffffffffe < uVar4) break;
code_r0x018d09bc:
      uVar3 = uVar4 + 0x40 & 0xffffffffffffffc0;
      if (uVar3 <= (ulong)(lVar2 << 7)) {
        uVar3 = lVar2 << 7;
      }
    }
  } while( true );
}

// ==== CGameResourceDownloader::SetErrorCallback(std::__ndk1::function<void (unsigned int, Aska::Status)>)
// vaddr 0x17d0a78 | ghidra 0x18d0a78 | size 164 | symbol _ZN23CGameResourceDownloader16SetErrorCallbackENSt6__ndk18functionIFvjN4Aska6StatusEEEE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN23CGameResourceDownloader16SetErrorCallbackENSt6__ndk18functionIFvjN4Aska6StatusEEEE
               (long param_1,long *param_2)

{
  long *plVar1;
  code *pcVar2;
  long alStack_50 [4];
  long *plStack_30;
  
  plStack_30 = alStack_50;
  plVar1 = (long *)param_2[4];
  if (plVar1 == (long *)0x0) {
    plStack_30 = (long *)0x0;
  }
  else if (param_2 == plVar1) {
    (**(code **)(*plVar1 + 0x18))(plVar1,alStack_50);
  }
  else {
    plStack_30 = (long *)(**(code **)(*plVar1 + 0x10))(plVar1);
  }
  std::__ndk1::function<void (unsigned int, Aska::Status)>::swap(std::__ndk1::function<void (unsigned int, Aska::Status)>&)(alStack_50,param_1 + 0x4c0);
  if (alStack_50 == plStack_30) {
    pcVar2 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) {
      return;
    }
    pcVar2 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar2)();
  return;
}

// ==== CGameResourceDownloader::RequestDownload(char const*, std::__ndk1::function<void (char const*, CGameResourceDownloader::iErrorCode)>)
// vaddr 0x17d0b1c | ghidra 0x18d0b1c | size 1920 | symbol _ZN23CGameResourceDownloader15RequestDownloadEPKcNSt6__ndk18functionIFvS1_NS_10iErrorCodeEEEE | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8
_ZN23CGameResourceDownloader15RequestDownloadEPKcNSt6__ndk18functionIFvS1_NS_10iErrorCodeEEEE
          (long param_1,undefined8 param_2,long *param_3)

{
  ulong uVar1;
  undefined *puVar2;
  undefined8 *puVar3;
  long lVar4;
  byte bVar5;
  undefined8 uVar6;
  bool bVar7;
  int iVar8;
  long lVar9;
  long *plVar10;
  ulong uVar11;
  undefined8 uVar12;
  ulong uVar13;
  code *pcVar14;
  long lVar15;
  long alStack_130 [4];
  long *plStack_110;
  long alStack_100 [4];
  long *plStack_e0;
  undefined8 uStack_d0;
  ulong uStack_c8;
  ulong uStack_c0;
  long *aplStack_b0 [4];
  long **pplStack_90;
  ulong uStack_80;
  ulong uStack_78;
  ulong uStack_70;
  ulong *puStack_60;
  
  if (*(char *)(param_1 + 0x154) != '\0') {
    return 0;
  }
  if (*(char *)(param_1 + 0x156) != '\0') {
    lVar9 = CGameResourceDownloader::SearchDownloadNode(char const*) const(param_1,param_2);
    if ((((lVar9 != 0) && (*(int *)(lVar9 + 8) - 1U < 4)) ||
        (lVar9 = CGameResourceDownloader::SearchDownloadNode(char const*) const(param_1,param_2), lVar9 == 0)) || (*(int *)(lVar9 + 8) == 5)) {
      lVar9 = CGameResourceDownloader::SearchDownloadNode(char const*) const(param_1,param_2);
      if (lVar9 == 0) {
        return 0;
      }
      plVar10 = (long *)param_3[4];
      if (plVar10 == (long *)0x0) {
        plStack_110 = (long *)0x0;
      }
      else if (param_3 == plVar10) {
        plStack_110 = alStack_130;
        (**(code **)(*plVar10 + 0x18))(plVar10,alStack_130);
      }
      else {
        plStack_110 = (long *)(**(code **)(*plVar10 + 0x10))();
      }
      CGameResourceDownloader::CDownloadNode::RegistryCallback(char const*, std::__ndk1::function<void (char const*, CGameResourceDownloader::iErrorCode)>)(lVar9,param_2,alStack_130);
      if (alStack_130 == plStack_110) {
        pcVar14 = *(code **)(*plStack_110 + 0x20);
      }
      else {
        if (plStack_110 == (long *)0x0) {
          return 0;
        }
        pcVar14 = *(code **)(*plStack_110 + 0x28);
      }
      (*pcVar14)();
      return 0;
    }
    if (*(int *)(param_1 + 0x14c) == 0) {
      *(undefined8 *)(param_1 + 0x14c) = 4;
      *(undefined8 *)(param_1 + 0x160) = 0;
    }
    if (*(long *)(param_1 + 0x480) == 0) {
      BAS::GetDownloadPath()(&uStack_d0);
      if ((uStack_d0 & 1) == 0) {
        uVar13 = 0x16;
        uVar11 = uStack_d0 & 0xff;
      }
      else {
        uVar13 = (uStack_d0 & 0xfffffffffffffffe) - 1;
        uVar11 = uStack_d0;
      }
      uVar1 = (ulong)(((uint)uVar11 & 0xfe) >> 1);
      if ((uVar11 & 1) != 0) {
        uVar1 = uStack_c8;
      }
      if (uVar13 == uVar1) {
        string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&uStack_d0,uVar13,1,uVar13,uVar13,0,1,&UNK_029c5d3e/*"/"*/);
      }
      else {
        uVar13 = (ulong)&uStack_d0 | 1;
        if ((uVar11 & 1) != 0) {
          uVar13 = uStack_c0;
        }
        *(undefined1 *)(uVar13 + uVar1) = 0x2f;
        uVar1 = uVar1 + 1;
        uVar11 = uVar1;
        if ((uStack_d0 & 1) == 0) {
          uStack_d0 = CONCAT71(uStack_d0._1_7_,(char)uVar1 * '\x02');
          uVar11 = uStack_c8;
        }
        uStack_c8 = uVar11;
        *(undefined1 *)(uVar13 + uVar1) = 0;
      }
      uVar6 = _UNK_02866d67;
      uVar12 = _UNK_02866d5f;
      uStack_78 = uStack_c8;
      uStack_80 = uStack_d0;
      uStack_70 = uStack_c0;
      if ((uStack_d0 & 1) == 0) {
        lVar9 = 0x16;
        uVar11 = uStack_d0 & 0xff;
      }
      else {
        lVar9 = (uStack_d0 & 0xfffffffffffffffe) - 1;
        uVar11 = uStack_d0;
      }
      uVar13 = (ulong)(((uint)uVar11 & 0xfe) >> 1);
      if ((uVar11 & 1) != 0) {
        uVar13 = uStack_c8;
      }
      if (lVar9 - uVar13 < 0x14) {
        string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&uStack_80,lVar9,(0x14 - lVar9) + uVar13,uVar13,uVar13,0,0x14,&UNK_02866d5f/*"downloadfilelist.tmp"*/)
        ;
      }
      else {
        uVar1 = (ulong)&uStack_80 | 1;
        if ((uVar11 & 1) != 0) {
          uVar1 = uStack_c0;
        }
        puVar3 = (undefined8 *)(uVar1 + uVar13);
        *(undefined4 *)(puVar3 + 2) = 0x706d742e;
        puVar3[1] = uVar6;
        *puVar3 = uVar12;
        uVar13 = uVar13 + 0x14;
        uVar11 = uVar13;
        if ((uStack_d0 & 1) == 0) {
          uStack_80 = CONCAT71((int7)(uStack_d0 >> 8),(char)uVar13 * '\x02');
          uVar11 = uStack_78;
        }
        uStack_78 = uVar11;
        *(undefined1 *)(uVar1 + uVar13) = 0;
      }
      uStack_c0 = uStack_70;
      uStack_c8 = uStack_78;
      uStack_d0 = uStack_80;
      plVar10 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x220,PTR__ZSt7nothrow_02cb9a80);
      if (plVar10 != (long *)0x0) {
        *plVar10 = (long)(PTR__ZTVN23CGameResourceDownloader18CJournalFileWriterE_02cb86c0 + 0x10);
        Framework::CMutex::CMutex()(plVar10 + 2);
        Framework::CMutex::CMutex()(plVar10 + 0x18);
        *(undefined4 *)(plVar10 + 0x2e) = 0;
        puVar2 = PTR__ZTVN4Aska10FileStreamE_02cbc9f8 + 0x10;
        plVar10[0x30] = (long)(PTR__ZTVN4Aska4FileE_02cb6e28 + 0x10);
        plVar10[0x2f] = (long)puVar2;
        puVar2 = PTR__ZTVN4Aska6TArrayIN23CGameResourceDownloader18CJournalFileWriter10tWriteInfoELb0EEE_02cbd0a0
                 + 0x10;
        plVar10[0x35] = (long)puVar2;
        plVar10[0x3c] = (long)puVar2;
        *(undefined1 *)(plVar10 + 0x31) = 0;
        plVar10[0x33] = 0;
        plVar10[0x32] = 0;
        *(undefined1 *)(plVar10 + 0x34) = 0;
        plVar10[0x37] = 0;
        plVar10[0x36] = 0;
        plVar10[0x39] = 0;
        plVar10[0x38] = 0;
        plVar10[0x3a] = 8;
        *(undefined4 *)(plVar10 + 0x3b) = 0;
        plVar10[0x40] = 0;
        plVar10[0x3f] = 0;
        plVar10[0x3e] = 0;
        plVar10[0x3d] = 0;
        plVar10[0x41] = 8;
        *(undefined4 *)(plVar10 + 0x42) = 0;
      }
      *(long **)(param_1 + 0x480) = plVar10;
      if ((uStack_d0 & 1) == 0) {
        uVar11 = (ulong)&uStack_d0 | 1;
code_r0x018d109c:
        iVar8 = access(uVar11,0);
        plVar10 = *(long **)(param_1 + 0x480);
        bVar7 = iVar8 == 0;
        uVar11 = uStack_c0;
      }
      else {
        uVar11 = uStack_c0;
        if (uStack_c0 != 0) goto code_r0x018d109c;
        uVar11 = 0;
        bVar7 = false;
      }
      uVar13 = (ulong)&uStack_d0 | 1;
      if ((uStack_d0 & 1) != 0) {
        uVar13 = uVar11;
      }
      Framework::CMutex::Initialize()(plVar10 + 2);
      Framework::CMutex::Initialize()(plVar10 + 0x18);
      plVar10 = plVar10 + 0x2f;
      if (bVar7) {
        uVar11 = Aska::FileStream::Open(char const*, bool, bool, Aska::Machine::Endian)(plVar10,uVar13,0,0,3);
        if ((uVar11 & 1) != 0) {
          uVar12 = Aska::FileStream::GetTotalSize() const(plVar10);
          Aska::FileStream::Seek(long, int)(plVar10,uVar12,0);
        }
      }
      else {
        Aska::FileStream::Open(char const*, bool, bool, Aska::Machine::Endian)(plVar10,uVar13,0,1,3);
      }
      if ((uStack_d0 & 1) != 0) {
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_c0);
      }
    }
    lVar9 = CGameResourceDownloader::SearchDownloadNode(char const*) const(param_1,param_2);
    lVar15 = *(long *)(param_1 + 0x90);
    if (-1 < lVar15) {
      Aska::TArray<CGameResourceDownloader::CDownloadNode*, false>::Resize(long, bool)(param_1 + 0x78,lVar15 + 1,0);
      *(long *)(*(long *)(param_1 + 0x80) + lVar15 * 8) = lVar9;
    }
    if (*(int *)(lVar9 + 8) == 5) {
      return 0;
    }
    plVar10 = (long *)param_3[4];
    if (plVar10 == (long *)0x0) {
      plStack_e0 = (long *)0x0;
    }
    else if (param_3 == plVar10) {
      plStack_e0 = alStack_100;
      (**(code **)(*plVar10 + 0x18))(plVar10,alStack_100);
    }
    else {
      plStack_e0 = (long *)(**(code **)(*plVar10 + 0x10))();
    }
    if (*(int *)(lVar9 + 8) == 5) goto code_r0x018d1268;
    if (plStack_e0 != (long *)0x0) {
      if (alStack_100 == plStack_e0) {
        aplStack_b0[0] = &uStack_d0;
        (**(code **)(*plStack_e0 + 0x18))(plStack_e0,&uStack_d0);
      }
      else {
        aplStack_b0[0] = (long *)(**(code **)(*plStack_e0 + 0x10))();
      }
      CGameResourceDownloader::CDownloadNode::RegistryCallback(char const*, std::__ndk1::function<void (char const*, CGameResourceDownloader::iErrorCode)>)(lVar9,param_2,&uStack_d0);
      if (&uStack_d0 == aplStack_b0[0]) {
        pcVar14 = *(code **)(*aplStack_b0[0] + 0x20);
      }
      else {
        if (aplStack_b0[0] == (long *)0x0) goto code_r0x018d125c;
        pcVar14 = *(code **)(*aplStack_b0[0] + 0x28);
      }
      (*pcVar14)();
    }
code_r0x018d125c:
    *(undefined1 *)(lVar9 + 0x150) = 0;
    *(undefined8 *)(lVar9 + 8) = 1;
code_r0x018d1268:
    if (alStack_100 == plStack_e0) {
      pcVar14 = *(code **)(*plStack_e0 + 0x20);
    }
    else {
      if (plStack_e0 == (long *)0x0) {
        return 1;
      }
      pcVar14 = *(code **)(*plStack_e0 + 0x28);
    }
    (*pcVar14)();
    return 1;
  }
  lVar9 = *(long *)(param_1 + 200);
  *(undefined8 *)(param_1 + 0xd0) = 0;
  if (0 < lVar9) {
    plVar10 = (long *)(*(long *)(param_1 + 0xb8) + 0x10);
    lVar15 = 1;
    do {
      uVar13 = strlen(param_2);
      bVar5 = *(byte *)(plVar10 + -2);
      uVar11 = (ulong)(bVar5 >> 1);
      if ((bVar5 & 1) != 0) {
        uVar11 = plVar10[-1];
      }
      if (uVar13 == uVar11) {
        if (uVar13 == 0) {
          return 0;
        }
        lVar4 = (long)plVar10 + -0xf;
        if ((bVar5 & 1) != 0) {
          lVar4 = *plVar10;
        }
        uVar12 = memcmp(lVar4,param_2,uVar13);
        if ((int)uVar12 == 0) {
          return uVar12;
        }
      }
      *(long *)(param_1 + 0xd0) = lVar15;
      plVar10 = plVar10 + 10;
      bVar7 = lVar15 < lVar9;
      lVar15 = lVar15 + 1;
    } while (bVar7);
  }
  uStack_c8 = 0;
  uStack_c0 = 0;
  uStack_d0 = 0;
  pplStack_90 = (long **)0x0;
  uVar11 = strlen(param_2);
  if (uVar11 < 0x16 || uVar11 - 0x16 == 0) {
    if (uVar11 != 0) {
      memcpy((ulong)&uStack_d0 | 1,param_2,uVar11);
    }
    *(undefined1 *)((long)&uStack_d0 + uVar11 + 1) = 0;
    uStack_d0 = CONCAT71(uStack_d0._1_7_,(char)(uVar11 << 1));
  }
  else {
    string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&uStack_d0,0x16,uVar11 - 0x16,0,0,0,uVar11,param_2);
  }
  plVar10 = (long *)param_3[4];
  if (plVar10 == (long *)0x0) {
    puStack_60 = (ulong *)0x0;
  }
  else if (param_3 == plVar10) {
    puStack_60 = &uStack_80;
    (**(code **)(*plVar10 + 0x18))(plVar10,&uStack_80);
  }
  else {
    puStack_60 = (ulong *)(**(code **)(*plVar10 + 0x10))();
  }
  std::__ndk1::function<void (char const*, CGameResourceDownloader::iErrorCode)>::swap(std::__ndk1::function<void (char const*, CGameResourceDownloader::iErrorCode)>&)(&uStack_80,aplStack_b0);
  if (&uStack_80 == puStack_60) {
    pcVar14 = *(code **)(*puStack_60 + 0x20);
code_r0x018d0dec:
    (*pcVar14)();
  }
  else if (puStack_60 != (ulong *)0x0) {
    pcVar14 = *(code **)(*puStack_60 + 0x28);
    goto code_r0x018d0dec;
  }
  Aska::TArray<CGameResourceDownloader::tDownloadNodeInitializer, false>::SetAt(long, CGameResourceDownloader::tDownloadNodeInitializer const&)(param_1 + 0xb0,*(undefined8 *)(param_1 + 200),&uStack_d0);
  if (*(int *)(param_1 + 0x14c) == 0) {
    *(undefined8 *)(param_1 + 0x14c) = 3;
  }
  if (aplStack_b0 == pplStack_90) {
    pcVar14 = (code *)(*pplStack_90)[4];
  }
  else {
    if (pplStack_90 == (long **)0x0) goto code_r0x018d0e44;
    pcVar14 = (code *)(*pplStack_90)[5];
  }
  (*pcVar14)();
code_r0x018d0e44:
  if ((uStack_d0 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_c0);
  }
  return 0;
}

// ==== CGameResourceDownloader::IsReadyDownload() const
// vaddr 0x17d129c | ghidra 0x18d129c | size 32 | symbol _ZNK23CGameResourceDownloader15IsReadyDownloadEv | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK23CGameResourceDownloader15IsReadyDownloadEv(long param_1)

{
  if (*(char *)(param_1 + 0x156) != '\0') {
    return true;
  }
  return *(char *)(param_1 + 0x154) != '\0';
}

// ==== CGameResourceDownloader::IsIdele() const
// vaddr 0x17d12bc | ghidra 0x18d12bc | size 16 | symbol _ZNK23CGameResourceDownloader7IsIdeleEv | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK23CGameResourceDownloader7IsIdeleEv(long param_1)

{
  return *(int *)(param_1 + 0x14c) == 0;
}

// ==== CGameResourceDownloader::IsNeedDownload(char const*) const
// vaddr 0x17d12cc | ghidra 0x18d12cc | size 88 | symbol _ZNK23CGameResourceDownloader14IsNeedDownloadEPKc | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK23CGameResourceDownloader14IsNeedDownloadEPKc(undefined8 param_1,undefined8 param_2)

{
  bool bVar1;
  long lVar2;
  
  lVar2 = CGameResourceDownloader::SearchDownloadNode(char const*) const();
  if ((lVar2 == 0) || (3 < *(int *)(lVar2 + 8) - 1U)) {
    lVar2 = CGameResourceDownloader::SearchDownloadNode(char const*) const(param_1,param_2);
    bVar1 = false;
    if (lVar2 != 0) {
      bVar1 = *(int *)(lVar2 + 8) != 5;
    }
  }
  else {
    bVar1 = false;
  }
  return bVar1;
}

// ==== CGameResourceDownloader::RestartDownload()
// vaddr 0x17d1324 | ghidra 0x18d1324 | size 32 | symbol _ZN23CGameResourceDownloader15RestartDownloadEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN23CGameResourceDownloader15RestartDownloadEv(long param_1)

{
  if (*(int *)(param_1 + 0x14c) != 0) {
    return;
  }
  *(undefined8 *)(param_1 + 0x14c) = 4;
  *(undefined8 *)(param_1 + 0x160) = 0;
  return;
}

// ==== CGameResourceDownloader::CJournalFileWriter::Open(char const*, bool)
// vaddr 0x17d1344 | ghidra 0x18d1344 | size 116 | symbol _ZN23CGameResourceDownloader18CJournalFileWriter4OpenEPKcb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN23CGameResourceDownloader18CJournalFileWriter4OpenEPKcb
               (long param_1,undefined8 param_2,uint param_3)

{
  ulong uVar1;
  undefined8 uVar2;
  
  Framework::CMutex::Initialize()(param_1 + 0x10);
  Framework::CMutex::Initialize()(param_1 + 0xc0);
  param_1 = param_1 + 0x178;
  uVar1 = Aska::FileStream::Open(char const*, bool, bool, Aska::Machine::Endian)(param_1,param_2,0,param_3 & 1,3);
  if (((uVar1 & 1) != 0) && ((param_3 & 1) == 0)) {
    uVar2 = Aska::FileStream::GetTotalSize() const(param_1);
    (*(code *)PTR__ZN4Aska10FileStream4SeekEli_02ca4d68)(param_1,uVar2,0);
    return;
  }
  return;
}

// ==== CGameResourceDownloader::SearchDownloadNode(char const*) const
// vaddr 0x17d13b8 | ghidra 0x18d13b8 | size 468 | symbol _ZNK23CGameResourceDownloader18SearchDownloadNodeEPKc | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK23CGameResourceDownloader18SearchDownloadNodeEPKc(long param_1,undefined8 param_2)

{
  ulong uVar1;
  ulong uVar2;
  uint uVar3;
  long lVar4;
  ulong uVar5;
  long *plVar6;
  ulong uVar7;
  ulong uStack_70;
  ulong uStack_68;
  ulong uStack_60;
  long alStack_58 [3];
  
  lVar4 = *(long *)(param_1 + 0x5d8);
  if (lVar4 == 0) {
    return 0;
  }
  uStack_68 = 0;
  uStack_60 = 0;
  uStack_70 = 0;
  uVar2 = strlen(param_2);
  if (uVar2 < 0x17) {
    uVar7 = (ulong)&uStack_70 | 1;
    uStack_70 = CONCAT71(uStack_70._1_7_,(char)(uVar2 << 1));
    if (uVar2 == 0) goto code_r0x018d1488;
  }
  else {
    uVar5 = uVar2 + 0x10 & 0xfffffffffffffff0;
    if (uVar5 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
    }
    uVar7 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar5,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
    if (uVar7 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    }
    uStack_70 = uVar5 | 1;
    uStack_68 = uVar2;
    uStack_60 = uVar7;
  }
  memcpy(uVar7,param_2,uVar2);
code_r0x018d1488:
  *(undefined1 *)(uVar7 + uVar2) = 0;
  Aska::THashMap<string, CAssetInfo, Hasher_CSTLString, Aska::TEqualTo<string >, Aska::TAllocator<Aska::TPair<string const, CAssetInfo> > >::Find_(string const&) const(alStack_58,lVar4 + 0x58,&uStack_70);
  if ((uStack_70 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_60);
  }
  if (alStack_58[0] ==
      *(long *)(*(long *)(param_1 + 0x5d8) + 0x78) +
      *(long *)(*(long *)(param_1 + 0x5d8) + 0x80) * 0xc0) {
    uVar3 = 0;
    uVar2 = *(ulong *)(param_1 + 0x120);
  }
  else {
    uVar3 = *(uint *)(alStack_58[0] + 0x50);
    uVar2 = *(ulong *)(param_1 + 0x120);
  }
  if (uVar2 != 0) {
    uVar7 = uVar2 - 1;
    uVar5 = (ulong)uVar3;
    if ((uVar7 & uVar2) == 0) {
      uVar5 = uVar7 & uVar5;
    }
    else {
      uVar1 = 0;
      if (uVar2 != 0) {
        uVar1 = uVar5 / uVar2;
      }
      uVar5 = uVar5 - uVar1 * uVar2;
    }
    plVar6 = *(long **)(*(long *)(param_1 + 0x118) + uVar5 * 8);
    if (plVar6 != (long *)0x0) {
      if ((uVar7 & uVar2) == 0) {
        do {
          plVar6 = (long *)*plVar6;
          if (plVar6 == (long *)0x0) {
            return 0;
          }
          if ((plVar6[1] & uVar7) != uVar5) {
            return 0;
          }
        } while (*(uint *)(plVar6 + 2) != uVar3);
      }
      else {
        do {
          plVar6 = (long *)*plVar6;
          if (plVar6 == (long *)0x0) {
            return 0;
          }
          uVar7 = 0;
          if (uVar2 != 0) {
            uVar7 = (ulong)plVar6[1] / uVar2;
          }
          if (plVar6[1] - uVar7 * uVar2 != uVar5) {
            return 0;
          }
        } while (*(uint *)(plVar6 + 2) != uVar3);
      }
      return plVar6[3];
    }
  }
  return 0;
}

// ==== CGameResourceDownloader::CDownloadNode::IsDownloaded() const
// vaddr 0x17d158c | ghidra 0x18d158c | size 16 | symbol _ZNK23CGameResourceDownloader13CDownloadNode12IsDownloadedEv | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK23CGameResourceDownloader13CDownloadNode12IsDownloadedEv(long param_1)

{
  return *(int *)(param_1 + 8) == 5;
}

// ==== CGameResourceDownloader::CDownloadNode::Download(char const*, std::__ndk1::function<void (char const*, CGameResourceDownloader::iErrorCode)>, bool)
// vaddr 0x17d159c | ghidra 0x18d159c | size 192 | symbol _ZN23CGameResourceDownloader13CDownloadNode8DownloadEPKcNSt6__ndk18functionIFvS2_NS_10iErrorCodeEEEEb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN23CGameResourceDownloader13CDownloadNode8DownloadEPKcNSt6__ndk18functionIFvS2_NS_10iErrorCodeEEEEb
               (long param_1,undefined8 param_2,long *param_3,byte param_4)

{
  long *plVar1;
  code *pcVar2;
  long alStack_60 [4];
  long *plStack_40;
  
  plStack_40 = alStack_60;
  if (*(int *)(param_1 + 8) == 5) {
    return;
  }
  plVar1 = (long *)param_3[4];
  if (plVar1 != (long *)0x0) {
    if (param_3 == plVar1) {
      (**(code **)(*plVar1 + 0x18))(plVar1,alStack_60);
    }
    else {
      plStack_40 = (long *)(**(code **)(*plVar1 + 0x10))();
    }
    CGameResourceDownloader::CDownloadNode::RegistryCallback(char const*, std::__ndk1::function<void (char const*, CGameResourceDownloader::iErrorCode)>)(param_1,param_2,alStack_60);
    if (alStack_60 == plStack_40) {
      pcVar2 = *(code **)(*plStack_40 + 0x20);
    }
    else {
      if (plStack_40 == (long *)0x0) goto code_r0x018d163c;
      pcVar2 = *(code **)(*plStack_40 + 0x28);
    }
    (*pcVar2)();
  }
code_r0x018d163c:
  *(byte *)(param_1 + 0x150) = param_4 & 1;
  *(undefined8 *)(param_1 + 8) = 1;
  return;
}

// ==== CGameResourceDownloader::CDownloadNode::RegistryCallback(char const*, std::__ndk1::function<void (char const*, CGameResourceDownloader::iErrorCode)>)
// vaddr 0x17d165c | ghidra 0x18d165c | size 748 | symbol _ZN23CGameResourceDownloader13CDownloadNode16RegistryCallbackEPKcNSt6__ndk18functionIFvS2_NS_10iErrorCodeEEEE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN23CGameResourceDownloader13CDownloadNode16RegistryCallbackEPKcNSt6__ndk18functionIFvS2_NS_10iErrorCodeEEEE
               (long param_1,undefined8 param_2,long *param_3)

{
  long lVar1;
  ulong uVar2;
  uint uVar3;
  ulong uVar4;
  long lVar5;
  ulong uVar6;
  code *pcVar7;
  long *plVar8;
  ulong uVar9;
  undefined1 auStack_1d0 [16];
  undefined1 auStack_1c0 [256];
  long alStack_c0 [4];
  long *plStack_a0;
  long lStack_90;
  undefined1 auStack_80 [16];
  long alStack_70 [4];
  long *plStack_50;
  undefined4 uStack_34;
  
  lVar1 = param_1 + 0x3a0;
  uVar4 = Framework::CMutex::IsInitialized() const(lVar1);
  if ((uVar4 & 1) == 0) {
    Framework::CMutex::Initialize()(lVar1);
  }
  Framework::CMutex::Lock()(lVar1);
  Framework::CHash32::CHash32(char const*)(auStack_80,param_2);
  uVar3 = Framework::CHash32::operator unsigned int() const(auStack_80);
  uVar4 = *(ulong *)(param_1 + 0x380);
  if (uVar4 != 0) {
    uVar9 = uVar4 - 1;
    uVar6 = (ulong)uVar3;
    if ((uVar9 & uVar4) == 0) {
      uVar6 = uVar9 & uVar6;
    }
    else {
      uVar2 = 0;
      if (uVar4 != 0) {
        uVar2 = uVar6 / uVar4;
      }
      uVar6 = uVar6 - uVar2 * uVar4;
    }
    plVar8 = *(long **)(*(long *)(param_1 + 0x378) + uVar6 * 8);
    if (plVar8 != (long *)0x0) {
      if ((uVar9 & uVar4) == 0) {
        do {
          plVar8 = (long *)*plVar8;
          if ((plVar8 == (long *)0x0) || ((plVar8[1] & uVar9) != uVar6)) goto code_r0x018d174c;
        } while (*(uint *)(plVar8 + 2) != uVar3);
      }
      else {
        do {
          plVar8 = (long *)*plVar8;
          if (plVar8 == (long *)0x0) goto code_r0x018d174c;
          uVar9 = 0;
          if (uVar4 != 0) {
            uVar9 = (ulong)plVar8[1] / uVar4;
          }
          if (plVar8[1] - uVar9 * uVar4 != uVar6) goto code_r0x018d174c;
        } while (*(uint *)(plVar8 + 2) != uVar3);
      }
      plVar8[0x2a] = plVar8[0x2a] + 1;
      goto code_r0x018d1920;
    }
  }
code_r0x018d174c:
  plStack_a0 = (long *)0x0;
  lStack_90 = 0;
  uVar4 = strlen(param_2);
  if (0xff < uVar4) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dc32f/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/Utility.h"*/,0x77,&UNK_027dc380/*"gStrcpy() : destination buffer is small. ( %d < %d )"*/,uVar4,0x100);
  }
  strcpy(auStack_1c0,param_2);
  plVar8 = (long *)param_3[4];
  if (plVar8 == (long *)0x0) {
    plStack_50 = (long *)0x0;
  }
  else if (param_3 == plVar8) {
    plStack_50 = alStack_70;
    (**(code **)(*plVar8 + 0x18))(plVar8,alStack_70);
  }
  else {
    plStack_50 = (long *)(**(code **)(*plVar8 + 0x10))();
  }
  std::__ndk1::function<void (char const*, CGameResourceDownloader::iErrorCode)>::swap(std::__ndk1::function<void (char const*, CGameResourceDownloader::iErrorCode)>&)(alStack_70,alStack_c0);
  if (alStack_70 == plStack_50) {
    pcVar7 = *(code **)(*plStack_50 + 0x20);
code_r0x018d1814:
    (*pcVar7)();
  }
  else if (plStack_50 != (long *)0x0) {
    pcVar7 = *(code **)(*plStack_50 + 0x28);
    goto code_r0x018d1814;
  }
  lStack_90 = lStack_90 + 1;
  Framework::CHash32::CHash32(char const*)(auStack_1d0,param_2);
  uStack_34 = Framework::CHash32::operator unsigned int() const(auStack_1d0);
  lVar5 = std::__ndk1::unordered_map<unsigned int, CGameResourceDownloader::CDownloadNode::tCallbackInfo, std::__ndk1::hash<unsigned int>, std::__ndk1::equal_to<unsigned int>, Framework::CSTLAllocator<std::__ndk1::pair<unsigned int const, CGameResourceDownloader::CDownloadNode::tCallbackInfo>, Framework::CSTLUnorderedMapAllocatorInf> >::operator[](unsigned int&&)((long *)(param_1 + 0x378),&uStack_34);
  memcpy(lVar5,auStack_1c0,0x100);
  if (plStack_a0 == (long *)0x0) {
    plStack_50 = (long *)0x0;
  }
  else if (alStack_c0 == plStack_a0) {
    plStack_50 = alStack_70;
    (**(code **)(*plStack_a0 + 0x18))(plStack_a0,alStack_70);
  }
  else {
    plStack_50 = (long *)(**(code **)(*plStack_a0 + 0x10))();
  }
  std::__ndk1::function<void (char const*, CGameResourceDownloader::iErrorCode)>::swap(std::__ndk1::function<void (char const*, CGameResourceDownloader::iErrorCode)>&)(alStack_70,lVar5 + 0x100);
  if (alStack_70 == plStack_50) {
    pcVar7 = *(code **)(*plStack_50 + 0x20);
code_r0x018d18dc:
    (*pcVar7)();
  }
  else if (plStack_50 != (long *)0x0) {
    pcVar7 = *(code **)(*plStack_50 + 0x28);
    goto code_r0x018d18dc;
  }
  *(long *)(lVar5 + 0x130) = lStack_90;
  Framework::CHash32::~CHash32()(auStack_1d0);
  if (alStack_c0 == plStack_a0) {
    pcVar7 = *(code **)(*plStack_a0 + 0x20);
  }
  else {
    if (plStack_a0 == (long *)0x0) goto code_r0x018d1920;
    pcVar7 = *(code **)(*plStack_a0 + 0x28);
  }
  (*pcVar7)();
code_r0x018d1920:
  Framework::CHash32::~CHash32()(auStack_80);
  Framework::CMutex::Unlock()(lVar1);
  return;
}

// ==== CGameResourceDownloader::RequestDownloadAll(std::__ndk1::function<void (char const*, CGameResourceDownloader::iErrorCode)>)
// vaddr 0x17d1948 | ghidra 0x18d1948 | size 416 | symbol _ZN23CGameResourceDownloader18RequestDownloadAllENSt6__ndk18functionIFvPKcNS_10iErrorCodeEEEE | lib libSOA-3.7.0.so | 2026-10-04
int _ZN23CGameResourceDownloader18RequestDownloadAllENSt6__ndk18functionIFvPKcNS_10iErrorCodeEEEE
              (long param_1,long *param_2)

{
  undefined8 *puVar1;
  uint uVar2;
  ulong uVar3;
  long *plVar4;
  long lVar5;
  code *pcVar6;
  int iVar7;
  undefined8 uVar8;
  long *plVar9;
  undefined8 *puVar10;
  long alStack_a0 [4];
  long *plStack_80;
  long alStack_70 [4];
  long *plStack_50;
  
  uVar3 = CUIUtility::IsRequestSelectAllDownload()();
  if ((uVar3 & 1) == 0) {
    puVar10 = *(undefined8 **)(param_1 + 0xe8);
    puVar1 = *(undefined8 **)(param_1 + 0xf0);
    if (puVar10 != puVar1) {
      iVar7 = 0;
      do {
        plVar9 = (long *)param_2[4];
        uVar8 = *puVar10;
        if (plVar9 == (long *)0x0) {
          plStack_50 = (long *)0x0;
        }
        else if (param_2 == plVar9) {
          plStack_50 = alStack_70;
          (**(code **)(*plVar9 + 0x18))(plVar9,alStack_70);
        }
        else {
          plStack_50 = (long *)(**(code **)(*plVar9 + 0x10))();
        }
        uVar2 = CGameResourceDownloader::RequestDownload(char const*, std::__ndk1::function<void (char const*, CGameResourceDownloader::iErrorCode)>)(param_1,uVar8,alStack_70);
        if (alStack_70 == plStack_50) {
          pcVar6 = *(code **)(*plStack_50 + 0x20);
code_r0x018d1aa8:
          (*pcVar6)(plStack_50);
        }
        else if (plStack_50 != (long *)0x0) {
          pcVar6 = *(code **)(*plStack_50 + 0x28);
          goto code_r0x018d1aa8;
        }
        puVar10 = puVar10 + 1;
        iVar7 = iVar7 + (uVar2 & 1);
        if (puVar1 == puVar10) {
          return iVar7;
        }
      } while( true );
    }
  }
  else {
    plVar9 = *(long **)(param_1 + 0x128);
    if (plVar9 != (long *)0x0) {
      iVar7 = 0;
      do {
        lVar5 = plVar9[3];
        plVar4 = (long *)param_2[4];
        if (plVar4 == (long *)0x0) {
          plStack_80 = (long *)0x0;
        }
        else if (param_2 == plVar4) {
          plStack_80 = alStack_a0;
          (**(code **)(*plVar4 + 0x18))(plVar4,alStack_a0);
        }
        else {
          plStack_80 = (long *)(**(code **)(*plVar4 + 0x10))();
        }
        uVar2 = CGameResourceDownloader::RequestDownload(char const*, std::__ndk1::function<void (char const*, CGameResourceDownloader::iErrorCode)>)(param_1,lVar5 + 0x10,alStack_a0);
        if (alStack_a0 == plStack_80) {
          pcVar6 = *(code **)(*plStack_80 + 0x20);
code_r0x018d19fc:
          (*pcVar6)(plStack_80);
        }
        else if (plStack_80 != (long *)0x0) {
          pcVar6 = *(code **)(*plStack_80 + 0x28);
          goto code_r0x018d19fc;
        }
        plVar9 = (long *)*plVar9;
        iVar7 = iVar7 + (uVar2 & 1);
        if (plVar9 == (long *)0x0) {
          return iVar7;
        }
      } while( true );
    }
  }
  return 0;
}

// ==== CGameResourceDownloader::CDownloadNode::pFileName() const
// vaddr 0x17d1ae8 | ghidra 0x18d1ae8 | size 8 | symbol _ZNK23CGameResourceDownloader13CDownloadNode9pFileNameEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK23CGameResourceDownloader13CDownloadNode9pFileNameEv(long param_1)

{
  return param_1 + 0x10;
}

// ==== CGameResourceDownloader::RequestRemoveDownloadData(std::__ndk1::function<void (Aska::Status)>)
// vaddr 0x17d1af0 | ghidra 0x18d1af0 | size 188 | symbol _ZN23CGameResourceDownloader25RequestRemoveDownloadDataENSt6__ndk18functionIFvN4Aska6StatusEEEE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN23CGameResourceDownloader25RequestRemoveDownloadDataENSt6__ndk18functionIFvN4Aska6StatusEEEE
               (long param_1,long *param_2)

{
  long *plVar1;
  code *pcVar2;
  long alStack_50 [4];
  long *plStack_30;
  
  plStack_30 = alStack_50;
  plVar1 = (long *)param_2[4];
  if (plVar1 == (long *)0x0) {
    plStack_30 = (long *)0x0;
  }
  else if (param_2 == plVar1) {
    (**(code **)(*plVar1 + 0x18))(plVar1,alStack_50);
  }
  else {
    plStack_30 = (long *)(**(code **)(*plVar1 + 0x10))(plVar1);
  }
  std::__ndk1::function<void (Aska::Status)>::swap(std::__ndk1::function<void (Aska::Status)>&)(alStack_50,param_1 + 0x500);
  if (alStack_50 == plStack_30) {
    pcVar2 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x018d1b88;
    pcVar2 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar2)();
code_r0x018d1b88:
  *(undefined8 *)(param_1 + 0x4f0) = 0x100000000;
  *(undefined8 *)(param_1 + 0x14c) = 7;
  return;
}

// ==== CGameResourceDownloader::IsFinishRemoveDownloadData() const
// vaddr 0x17d1bac | ghidra 0x18d1bac | size 20 | symbol _ZNK23CGameResourceDownloader26IsFinishRemoveDownloadDataEv | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK23CGameResourceDownloader26IsFinishRemoveDownloadDataEv(long param_1)

{
  return *(uint *)(param_1 + 0x4f4) <= *(uint *)(param_1 + 0x4f0);
}

// ==== CGameResourceDownloader::NumRemoveDownloadData() const
// vaddr 0x17d1bc0 | ghidra 0x18d1bc0 | size 8 | symbol _ZNK23CGameResourceDownloader21NumRemoveDownloadDataEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK23CGameResourceDownloader21NumRemoveDownloadDataEv(long param_1)

{
  return *(undefined4 *)(param_1 + 0x4f0);
}

// ==== CGameResourceDownloader::NumMaxRemoveDownloadData() const
// vaddr 0x17d1bc8 | ghidra 0x18d1bc8 | size 8 | symbol _ZNK23CGameResourceDownloader24NumMaxRemoveDownloadDataEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK23CGameResourceDownloader24NumMaxRemoveDownloadDataEv(long param_1)

{
  return *(undefined4 *)(param_1 + 0x4f4);
}

// ==== CGameResourceDownloader::CheckLocalResourceFileToolVersionOld()
// vaddr 0x17d1bd0 | ghidra 0x18d1bd0 | size 852 | symbol _ZN23CGameResourceDownloader36CheckLocalResourceFileToolVersionOldEv | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 _ZN23CGameResourceDownloader36CheckLocalResourceFileToolVersionOldEv(long param_1)

{
  undefined8 *puVar1;
  ulong uVar2;
  ulong uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  bool bVar6;
  int iVar7;
  ulong uVar8;
  ulong uVar9;
  long lVar10;
  ulong uVar11;
  undefined4 uVar12;
  ulong uStack_88;
  ulong uStack_80;
  ulong uStack_78;
  ulong uStack_70;
  ulong uStack_68;
  ulong uStack_60;
  ulong uStack_50;
  ulong uStack_48;
  ulong uStack_40;
  
  BAS::GetDownloadPath()(&uStack_50);
  if ((uStack_50 & 1) == 0) {
    uVar9 = 0x16;
    uVar8 = uStack_50 & 0xff;
  }
  else {
    uVar9 = (uStack_50 & 0xfffffffffffffffe) - 1;
    uVar8 = uStack_50;
  }
  uVar11 = (ulong)(((uint)uVar8 & 0xfe) >> 1);
  if ((uVar8 & 1) != 0) {
    uVar11 = uStack_48;
  }
  if (uVar9 == uVar11) {
    string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&uStack_50,uVar9,1,uVar9,uVar9,0,1,&UNK_029c5d3e/*"/"*/);
  }
  else {
    uVar9 = (ulong)&uStack_50 | 1;
    if ((uVar8 & 1) != 0) {
      uVar9 = uStack_40;
    }
    *(undefined1 *)(uVar9 + uVar11) = 0x2f;
    uVar11 = uVar11 + 1;
    uVar8 = uVar11;
    if ((uStack_50 & 1) == 0) {
      uStack_50 = CONCAT71(uStack_50._1_7_,(char)uVar11 * '\x02');
      uVar8 = uStack_48;
    }
    uStack_48 = uVar8;
    *(undefined1 *)(uVar9 + uVar11) = 0;
  }
  uStack_60 = uStack_40;
  uStack_68 = uStack_48;
  uStack_70 = uStack_50;
  CGameResourceDownloader::CheckLocalResourceFileToolVersionOld()+0x354(&uStack_88);
  uVar5 = _UNK_02866d7e;
  if ((uStack_88 & 1) == 0) {
    lVar10 = 0x16;
    uVar8 = uStack_88 & 0xff;
  }
  else {
    lVar10 = (uStack_88 & 0xfffffffffffffffe) - 1;
    uVar8 = uStack_88;
  }
  uVar9 = (ulong)(((uint)uVar8 & 0xfe) >> 1);
  if ((uVar8 & 1) != 0) {
    uVar9 = uStack_80;
  }
  if (lVar10 - uVar9 < 0x17) {
    string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&uStack_88,lVar10,(0x17 - lVar10) + uVar9,uVar9,uVar9,0,0x17,&UNK_02866d7e/*"version_latest_Bulk.bin"*/);
  }
  else {
    uVar4 = CONCAT17(UNK_02866d8d,_UNK_02866d86);
    uVar11 = (ulong)&uStack_88 | 1;
    if ((uVar8 & 1) != 0) {
      uVar11 = uStack_78;
    }
    puVar1 = (undefined8 *)(uVar11 + uVar9);
    *(ulong *)((long)puVar1 + 0xf) = CONCAT71(_UNK_02866d8e,UNK_02866d8d);
    puVar1[1] = uVar4;
    *puVar1 = uVar5;
    uVar9 = uVar9 + 0x17;
    uVar8 = uVar9;
    if ((uStack_88 & 1) == 0) {
      uStack_88 = CONCAT71(uStack_88._1_7_,(char)uVar9 * '\x02');
      uVar8 = uStack_80;
    }
    uStack_80 = uVar8;
    *(undefined1 *)(uVar11 + uVar9) = 0;
  }
  uStack_40 = uStack_78;
  uStack_48 = uStack_80;
  uStack_50 = uStack_88;
  uStack_80 = 0;
  uStack_78 = 0;
  bVar6 = (uStack_88 & 1) != 0;
  uVar8 = (ulong)&uStack_50 | 1;
  if (bVar6) {
    uVar8 = uStack_40;
  }
  uVar9 = uStack_88 >> 1 & 0x7f;
  if (bVar6) {
    uVar9 = uStack_48;
  }
  uStack_88 = 0;
  if ((uStack_70 & 1) == 0) {
    lVar10 = 0x16;
    uVar11 = uStack_70 & 0xff;
  }
  else {
    lVar10 = (uStack_70 & 0xfffffffffffffffe) - 1;
    uVar11 = uStack_70;
  }
  uVar2 = (ulong)(((uint)uVar11 & 0xfe) >> 1);
  if ((uVar11 & 1) != 0) {
    uVar2 = uStack_68;
  }
  if (lVar10 - uVar2 < uVar9) {
    string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&uStack_70,lVar10,(uVar9 - lVar10) + uVar2,uVar2,uVar2,0,uVar9);
  }
  else if (uVar9 != 0) {
    uVar3 = (ulong)&uStack_70 | 1;
    if ((uVar11 & 1) != 0) {
      uVar3 = uStack_60;
    }
    memcpy(uVar3 + uVar2,uVar8,uVar9);
    uVar2 = uVar2 + uVar9;
    if ((uStack_70 & 1) == 0) {
      uStack_70 = CONCAT71(uStack_70._1_7_,(char)uVar2 * '\x02');
      *(undefined1 *)(uVar3 + uVar2) = 0;
    }
    else {
      *(undefined1 *)(uVar3 + uVar2) = 0;
      uStack_68 = uVar2;
    }
  }
  if ((uStack_50 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_40);
  }
  if ((uStack_88 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_78);
  }
  Aska::ASON::Term()(param_1 + 0x310);
  if ((uStack_70 & 1) == 0) {
    uVar8 = (ulong)&uStack_70 | 1;
code_r0x018d1e7c:
    iVar7 = access(uVar8,0);
    if (iVar7 == 0) {
      uStack_48 = 0;
      uStack_40 = 0;
      uStack_50 = 0;
      CGameResourceDownloader::LoadVersionFileToAson(string const&, string const&)(param_1,&uStack_70,&uStack_50);
      if ((uStack_50 & 1) != 0) {
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_40);
      }
      lVar10 = Aska::ASON::AValue::AMap::Get_(char const*)(param_1 + 0x378,&UNK_02866d96/*"toolversion"*/);
      iVar7 = strcmp(*(undefined8 *)(lVar10 + 0x10),&UNK_02866a9c/*"1.2.0"*/);
      if (iVar7 != 0) {
        uVar12 = 1;
        goto joined_r0x018d1e90;
      }
    }
  }
  else {
    uVar8 = uStack_60;
    if (uStack_60 != 0) goto code_r0x018d1e7c;
  }
  uVar12 = 0;
joined_r0x018d1e90:
  if ((uStack_70 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_60);
  }
  return uVar12;
}

// ==== CGameResourceDownloader::LoadVersionFileToAson(std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > const&, std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > const&)
// vaddr 0x17d2000 | ghidra 0x18d2000 | size 784 | symbol _ZN23CGameResourceDownloader21LoadVersionFileToAsonERKNSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEESA_ | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN23CGameResourceDownloader21LoadVersionFileToAsonERKNSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEESA_
          (long param_1,byte *param_2,byte *param_3)

{
  undefined *puVar1;
  undefined *puVar2;
  byte bVar3;
  int iVar4;
  long lVar5;
  long *plVar6;
  undefined8 uVar7;
  ulong uVar8;
  byte *pbVar9;
  undefined *puStack_90;
  undefined *puStack_88;
  undefined1 uStack_80;
  long lStack_78;
  undefined8 uStack_70;
  undefined1 uStack_68;
  undefined4 uStack_54;
  
  bVar3 = *param_2;
  uVar8 = (ulong)(bVar3 >> 1);
  if ((bVar3 & 1) != 0) {
    uVar8 = *(ulong *)(param_2 + 8);
  }
  if (uVar8 != 0) {
    if ((bVar3 & 1) == 0) {
      pbVar9 = param_2 + 1;
    }
    else {
      pbVar9 = *(byte **)(param_2 + 0x10);
      if (pbVar9 == (byte *)0x0) {
        return 0;
      }
    }
    iVar4 = access(pbVar9,0);
    if (iVar4 != 0) {
      return 0;
    }
    lVar5 = Aska::ASON::Init(unsigned int, bool)(param_1 + 0x310,"meterEPv",1);
    if (lVar5 == 0) {
      pbVar9 = *(byte **)(param_2 + 0x10);
      if ((*param_2 & 1) == 0) {
        pbVar9 = param_2 + 1;
      }
      lVar5 = Aska::FileReadManager::CalcFileLength(char const*, bool)(pbVar9,0);
      if (lVar5 != 0) {
        if (*(long *)(param_1 + 0x490) != 0) {
          operator delete[](void*)();
          *(undefined8 *)(param_1 + 0x490) = 0;
        }
        uVar7 = operator new[](unsigned long, std::nothrow_t const&)(lVar5,PTR__ZSt7nothrow_02cb9a80);
        *(undefined8 *)(param_1 + 0x490) = uVar7;
        uStack_80 = 0;
        puVar1 = PTR__ZTVN4Aska10FileStreamE_02cbc9f8 + 0x10;
        puVar2 = PTR__ZTVN4Aska4FileE_02cb6e28 + 0x10;
        uStack_68 = 0;
        lStack_78 = 0;
        uStack_70 = 0;
        pbVar9 = param_2 + 1;
        if ((*param_2 & 1) != 0) {
          pbVar9 = *(byte **)(param_2 + 0x10);
        }
        puStack_90 = puVar1;
        puStack_88 = puVar2;
        uVar8 = Aska::FileStream::Open(char const*, bool, bool, Aska::Machine::Endian)(&puStack_90,pbVar9,0,0,3);
        if ((uVar8 & 1) != 0) {
          Aska::FileStream::Read(void*, unsigned long, unsigned long)(&puStack_90,*(undefined8 *)(param_1 + 0x490),lVar5,1);
          Aska::FileStream::Close()(&puStack_90);
          Aska::ASON::DeserializeBinary(void const*, unsigned long)(param_1 + 0x310,*(undefined8 *)(param_1 + 0x490),lVar5);
        }
        puStack_90 = puVar1;
        Aska::FileStream::Close()(&puStack_90);
        puStack_88 = puVar2;
        if (lStack_78 != 0) {
          Aska::File::Close()((ulong)&puStack_90 | 8);
        }
      }
      if (*(char *)(param_1 + 0x155) == '\0') {
        return 1;
      }
      if ((*param_3 & 1) == 0) {
        pbVar9 = param_3 + 1;
      }
      else {
        pbVar9 = *(byte **)(param_3 + 0x10);
        if (pbVar9 == (byte *)0x0) {
          return 1;
        }
      }
      iVar4 = access(pbVar9,0);
      if (iVar4 != 0) {
        return 1;
      }
      lVar5 = Aska::ASON::Init(unsigned int, bool)(param_1 + 0x3a0,"meterEPv",1);
      if (lVar5 == 0) {
        pbVar9 = *(byte **)(param_3 + 0x10);
        if ((*param_3 & 1) == 0) {
          pbVar9 = param_3 + 1;
        }
        lVar5 = Aska::FileReadManager::CalcFileLength(char const*, bool)(pbVar9,0);
        if (lVar5 == 0) {
          return 1;
        }
        if (*(long *)(param_1 + 0x498) != 0) {
          operator delete[](void*)();
          *(undefined8 *)(param_1 + 0x498) = 0;
        }
        uVar7 = operator new[](unsigned long, std::nothrow_t const&)(lVar5,PTR__ZSt7nothrow_02cb9a80);
        *(undefined8 *)(param_1 + 0x498) = uVar7;
        uStack_80 = 0;
        puVar1 = PTR__ZTVN4Aska10FileStreamE_02cbc9f8 + 0x10;
        puVar2 = PTR__ZTVN4Aska4FileE_02cb6e28 + 0x10;
        uStack_68 = 0;
        lStack_78 = 0;
        uStack_70 = 0;
        pbVar9 = param_3 + 1;
        if ((*param_3 & 1) != 0) {
          pbVar9 = *(byte **)(param_3 + 0x10);
        }
        puStack_90 = puVar1;
        puStack_88 = puVar2;
        uVar8 = Aska::FileStream::Open(char const*, bool, bool, Aska::Machine::Endian)(&puStack_90,pbVar9,0,0,3);
        if ((uVar8 & 1) != 0) {
          Aska::FileStream::Read(void*, unsigned long, unsigned long)(&puStack_90,*(undefined8 *)(param_1 + 0x498),lVar5,1);
          Aska::FileStream::Close()(&puStack_90);
          Aska::ASON::DeserializeBinary(void const*, unsigned long)(param_1 + 0x3a0,*(undefined8 *)(param_1 + 0x498),lVar5);
        }
        puStack_90 = puVar1;
        Aska::FileStream::Close()(&puStack_90);
        if (lStack_78 == 0) {
          return 1;
        }
        puStack_88 = puVar2;
        Aska::File::Close()((ulong)&puStack_90 | 8);
        return 1;
      }
    }
    *(undefined8 *)(param_1 + 0x14c) = 5;
    if ((*(char *)(param_1 + 0x157) != '\0') &&
       (plVar6 = *(long **)(param_1 + 0x4e0), plVar6 != (long *)0x0)) {
      puStack_90 = (undefined *)0xfffffffffffffc15;
      uStack_54 = 1000000;
      (**(code **)(*plVar6 + 0x30))(plVar6,&uStack_54,&puStack_90);
    }
  }
  return 0;
}

// ==== CGameResourceDownloader::RequestDeleteEpisodeData(std::__ndk1::function<void (Aska::Status)>)
// vaddr 0x17d2310 | ghidra 0x18d2310 | size 332 | symbol _ZN23CGameResourceDownloader24RequestDeleteEpisodeDataENSt6__ndk18functionIFvN4Aska6StatusEEEE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN23CGameResourceDownloader24RequestDeleteEpisodeDataENSt6__ndk18functionIFvN4Aska6StatusEEEE
               (long param_1,long *param_2)

{
  undefined *puVar1;
  long lVar2;
  long *plVar3;
  code *pcVar4;
  long alStack_50 [4];
  long *plStack_30;
  
  *(undefined8 *)(param_1 + 0x160) = 0;
  *(undefined1 *)(param_1 + 0x15c) = 0;
  *(undefined4 *)(param_1 + 0x5c8) = *(undefined4 *)(param_1 + 0x14c);
  *(undefined2 *)(param_1 + 0x155) = 0;
  puVar1 = PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
  if (*(long *)(param_1 + 0x5d0) == 0) {
    lVar2 = *(long *)PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
    if (lVar2 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
      lVar2 = *(long *)puVar1;
    }
    lVar2 = CParameterManager::pParameterUI() const(lVar2);
    *(long *)(param_1 + 0x5d0) = lVar2 + 0xc3f8;
  }
  CParameterUI::tEpisodeData::Initialize()();
  CGameResourceDownloader::LoadLocalKVSEpisodeUpdateFlag(bool)(param_1,0);
  *(undefined4 *)(param_1 + 0x140) = 0;
  plVar3 = (long *)param_2[4];
  if (plVar3 != (long *)0x0) {
    if (param_2 == plVar3) {
      plStack_30 = alStack_50;
      (**(code **)(*plVar3 + 0x18))(plVar3,alStack_50);
    }
    else {
      plStack_30 = (long *)(**(code **)(*plVar3 + 0x10))();
    }
    std::__ndk1::function<void (Aska::Status)>::swap(std::__ndk1::function<void (Aska::Status)>&)(alStack_50,(long *)(param_1 + 0x530));
    if (alStack_50 == plStack_30) {
      (**(code **)(*plStack_30 + 0x20))();
    }
    else if (plStack_30 != (long *)0x0) {
      (**(code **)(*plStack_30 + 0x28))();
    }
    goto code_r0x018d2440;
  }
  plVar3 = *(long **)(param_1 + 0x550);
  if ((long *)(param_1 + 0x530) == plVar3) {
    pcVar4 = *(code **)(*plVar3 + 0x20);
code_r0x018d2438:
    (*pcVar4)();
  }
  else if (plVar3 != (long *)0x0) {
    pcVar4 = *(code **)(*plVar3 + 0x28);
    goto code_r0x018d2438;
  }
  *(undefined8 *)(param_1 + 0x550) = 0;
code_r0x018d2440:
  *(undefined8 *)(param_1 + 0x14c) = 1;
  return;
}

// ==== CGameResourceDownloader::ScriptDownload()
// vaddr 0x17d245c | ghidra 0x18d245c | size 2076 | symbol _ZN23CGameResourceDownloader14ScriptDownloadEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN23CGameResourceDownloader14ScriptDownloadEv(long param_1)

{
  long *plVar1;
  long *plVar2;
  long *plVar3;
  ulong *puVar4;
  long lVar5;
  undefined4 *puVar6;
  undefined8 uVar7;
  long lVar8;
  long *plVar9;
  ulong uVar10;
  long *plVar11;
  long *plVar12;
  long *plVar13;
  undefined4 *puVar14;
  long lVar15;
  ulong uVar16;
  ulong uVar17;
  ulong uVar18;
  byte bStack_108;
  undefined7 uStack_107;
  ulong uStack_100;
  ulong uStack_f8;
  ulong uStack_f0;
  ulong uStack_e8;
  ulong uStack_e0;
  long *plStack_d8;
  long *plStack_d0;
  ulong uStack_c8;
  long *plStack_c0;
  long *plStack_b8;
  ulong uStack_b0;
  long *plStack_a8;
  long *plStack_a0;
  undefined8 uStack_98;
  long *plStack_90;
  long *plStack_88;
  undefined4 *puStack_78;
  undefined4 *puStack_70;
  undefined8 uStack_68;
  
  lVar15 = *(long *)(param_1 + 0x100);
  lVar8 = *(long *)(param_1 + 0x108);
  plVar2 = (long *)PTR__ZN9Framework10TSingletonI20CGameResourceManagerE11m_pInstanceE_02cc2018;
  while (lVar5 = lVar8,
        PTR__ZN9Framework10TSingletonI20CGameResourceManagerE11m_pInstanceE_02cc2018 =
             (undefined *)plVar2, lVar5 != lVar15) {
    *(long *)(param_1 + 0x108) = lVar5 + -0x18;
    lVar8 = lVar5 + -0x18;
    plVar2 = (long *)PTR__ZN9Framework10TSingletonI20CGameResourceManagerE11m_pInstanceE_02cc2018;
    if ((*(byte *)(lVar5 + -0x18) & 1) != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(*(undefined8 *)(lVar5 + -8));
      lVar8 = *(long *)(param_1 + 0x108);
      plVar2 = (long *)PTR__ZN9Framework10TSingletonI20CGameResourceManagerE11m_pInstanceE_02cc2018;
    }
  }
  lVar15 = *plVar2;
  if (lVar15 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar15 = *plVar2;
  }
  uVar7 = CTimeUtility::NowTime()();
  puStack_70 = (undefined4 *)0x0;
  uStack_68 = 0;
  puStack_78 = (undefined4 *)0x0;
  MissionUtility::GetEventAreaList(long, Common::MissionType, Framework::CSTLVector<MissionUtility::tAreaInfo>*, unsigned int*, bool)(uVar7,1,&puStack_78,0,0);
  puVar6 = puStack_70;
  if (puStack_78 != puStack_70) {
    puVar14 = puStack_78;
    do {
      CParameterUtility::CollectAreaMissionMaster(unsigned int, int)(&plStack_90,*puVar14,1);
      plVar11 = plStack_88;
      plVar9 = plStack_90;
      for (plVar2 = plStack_90; plStack_90 = plVar9, plVar2 != plVar11; plVar2 = plVar2 + 2) {
        plStack_a0 = (long *)0x0;
        uStack_98 = 0;
        plStack_a8 = (long *)0x0;
        void CParameterPropertyBase<145u>::CryptString<string >(string&, string const&)(&plStack_a8,*plVar2 + 0x738);
        plVar9 = (long *)(ulong)((byte)plStack_a8 >> 1);
        if (((ulong)plStack_a8 & 1) != 0) {
          plVar9 = plStack_a0;
        }
        if (plVar9 != (long *)0x0) {
          string std::__ndk1::operator+<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> >(char const*, string const&)(&plStack_d8,&UNK_02866aa2/*"Script/"*/,&plStack_a8);
          if (((ulong)plStack_d8 & 1) == 0) {
            lVar8 = 0x16;
            plVar9 = (long *)((ulong)plStack_d8 & 0xff);
          }
          else {
            lVar8 = ((ulong)plStack_d8 & 0xfffffffffffffffe) - 1;
            plVar9 = plStack_d8;
          }
          plVar1 = (long *)(ulong)(((uint)plVar9 & 0xfe) >> 1);
          if (((ulong)plVar9 & 1) != 0) {
            plVar1 = plStack_d0;
          }
          if ((ulong)(lVar8 - (long)plVar1) < 5) {
            string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&plStack_d8,lVar8,(5 - lVar8) + (long)plVar1,plVar1,plVar1,0,5,
                            &UNK_02815902/*".msgp"*/);
          }
          else {
            uVar10 = (ulong)&plStack_d8 | 1;
            if (((ulong)plVar9 & 1) != 0) {
              uVar10 = uStack_c8;
            }
            *(undefined1 *)((undefined4 *)(uVar10 + (long)plVar1) + 1) = 0x70;
            *(undefined4 *)(uVar10 + (long)plVar1) = 0x67736d2e;
            plVar1 = (long *)((long)plVar1 + 5);
            plVar9 = plVar1;
            if (((ulong)plStack_d8 & 1) == 0) {
              plStack_d8 = (long *)CONCAT71(plStack_d8._1_7_,(char)plVar1 * '\x02');
              plVar9 = plStack_d0;
            }
            plStack_d0 = plVar9;
            *(undefined1 *)(uVar10 + (long)plVar1) = 0;
          }
          plStack_b8 = plStack_d0;
          plStack_c0 = plStack_d8;
          uVar10 = (ulong)&plStack_c0 | 1;
          if (((ulong)plStack_d8 & 1) != 0) {
            uVar10 = uStack_c8;
          }
          uStack_b0 = uStack_c8;
          CGameResourceManager::AddDirectFile(unsigned int, char const*, unsigned int, bool, CGameResourceManager::iPriorityMode)(lVar15,1,uVar10,0,0,0);
          puVar4 = *(ulong **)(param_1 + 0x108);
          if (puVar4 == *(ulong **)(param_1 + 0x110)) {
            void std::__ndk1::vector<string, Framework::CSTLAllocator<string, Framework::CSTLVectorAllocatorInf> >::__push_back_slow_path<string const&>(string const&)(param_1 + 0x100,&plStack_c0);
          }
          else {
            if (puVar4 == (ulong *)0x0) {
              Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
            }
            uVar10 = uStack_b0;
            plVar9 = plStack_b8;
            puVar4[1] = 0;
            puVar4[2] = 0;
            *puVar4 = 0;
            if (((ulong)plStack_c0 & 1) == 0) {
              puVar4[2] = uStack_b0;
              puVar4[1] = (ulong)plStack_b8;
              *puVar4 = (ulong)plStack_c0;
            }
            else {
              if (plStack_b8 < (long *)0x17) {
                uVar17 = (long)puVar4 + 1;
                *(char *)puVar4 = (char)((long)plStack_b8 << 1);
                if (plStack_b8 != (long *)0x0) goto code_r0x018d2770;
              }
              else {
                uVar18 = (ulong)(plStack_b8 + 2) & 0xfffffffffffffff0;
                if (uVar18 == 0) {
                  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
                }
                uVar17 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar18,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
                if (uVar17 == 0) {
                  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
                }
                puVar4[1] = (ulong)plVar9;
                puVar4[2] = uVar17;
                *puVar4 = uVar18 | 1;
code_r0x018d2770:
                memcpy(uVar17,uVar10,plVar9);
              }
              *(undefined1 *)(uVar17 + (long)plVar9) = 0;
            }
            *(long *)(param_1 + 0x108) = *(long *)(param_1 + 0x108) + 0x18;
          }
          if (((ulong)plStack_c0 & 1) != 0) {
            Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_b0);
          }
        }
        if (((byte)plStack_a8 & 1) != 0) {
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_98);
        }
        plVar9 = plStack_90;
      }
      if (plVar9 != (long *)0x0) {
        while (plStack_88 != plVar9) {
          while (plVar11 = plStack_88 + -2, plVar2 = plStack_88 + -1, plStack_88 = plVar11,
                *plVar2 != 0) {
            std::__ndk1::__shared_weak_count::__release_shared()();
            if (plStack_88 == plVar9) goto code_r0x018d2808;
          }
        }
code_r0x018d2808:
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plStack_90);
      }
      puVar14 = puVar14 + 0x40;
    } while (puVar14 != puVar6);
  }
  CParameterUtility::CollectEffectivePlanet()(&plStack_90);
  plVar2 = plStack_88;
  if (plStack_90 != plStack_88) {
    plVar9 = plStack_90;
    do {
      CParameterUtility::CollectAreaMasterWithPlanetId(unsigned int)(&plStack_a8,*(undefined4 *)(*plVar9 + 0x38));
      plVar13 = plStack_a0;
      plVar1 = plStack_a8;
      for (plVar11 = plStack_a8; plStack_a8 = plVar1, plVar11 != plVar13; plVar11 = plVar11 + 2) {
        CParameterUtility::CollectAreaMissionMaster(unsigned int, int)(&plStack_c0,*(undefined4 *)(*plVar11 + 0x38),0);
        plVar12 = plStack_b8;
        plVar3 = plStack_c0;
        for (plVar1 = plStack_c0; plStack_c0 = plVar3, plVar1 != plVar12; plVar1 = plVar1 + 2) {
          plStack_d0 = (long *)0x0;
          uStack_c8 = 0;
          plStack_d8 = (long *)0x0;
          void CParameterPropertyBase<145u>::CryptString<string >(string&, string const&)(&plStack_d8,*plVar1 + 0x738);
          plVar3 = (long *)(ulong)((byte)plStack_d8 >> 1);
          if (((ulong)plStack_d8 & 1) != 0) {
            plVar3 = plStack_d0;
          }
          if (plVar3 != (long *)0x0) {
            string std::__ndk1::operator+<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> >(char const*, string const&)(&bStack_108,&UNK_02866aa2/*"Script/"*/,&plStack_d8);
            uVar10 = (ulong)bStack_108;
            if ((bStack_108 & 1) == 0) {
              lVar8 = 0x16;
            }
            else {
              uVar10 = CONCAT71(uStack_107,bStack_108);
              lVar8 = (uVar10 & 0xfffffffffffffffe) - 1;
            }
            uVar18 = (ulong)(((uint)uVar10 & 0xfe) >> 1);
            if ((uVar10 & 1) != 0) {
              uVar18 = uStack_100;
            }
            if (lVar8 - uVar18 < 5) {
              string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&bStack_108,lVar8,(5 - lVar8) + uVar18,uVar18,uVar18,0,5,&UNK_02815902/*".msgp"*/
                             );
            }
            else {
              uVar17 = (ulong)&bStack_108 | 1;
              if ((uVar10 & 1) != 0) {
                uVar17 = uStack_f8;
              }
              *(undefined1 *)((undefined4 *)(uVar17 + uVar18) + 1) = 0x70;
              *(undefined4 *)(uVar17 + uVar18) = 0x67736d2e;
              uVar18 = uVar18 + 5;
              uVar10 = uVar18;
              if ((bStack_108 & 1) == 0) {
                bStack_108 = (char)uVar18 * '\x02';
                uVar10 = uStack_100;
              }
              uStack_100 = uVar10;
              *(undefined1 *)(uVar17 + uVar18) = 0;
            }
            uStack_f0 = CONCAT71(uStack_107,bStack_108);
            uStack_e8 = uStack_100;
            uVar10 = (ulong)&uStack_f0 | 1;
            if ((bStack_108 & 1) != 0) {
              uVar10 = uStack_f8;
            }
            uStack_e0 = uStack_f8;
            CGameResourceManager::AddDirectFile(unsigned int, char const*, unsigned int, bool, CGameResourceManager::iPriorityMode)(lVar15,1,uVar10,0,0,0);
            puVar4 = *(ulong **)(param_1 + 0x108);
            if (puVar4 == *(ulong **)(param_1 + 0x110)) {
              void std::__ndk1::vector<string, Framework::CSTLAllocator<string, Framework::CSTLVectorAllocatorInf> >::__push_back_slow_path<string const&>(string const&)(param_1 + 0x100,&uStack_f0);
            }
            else {
              if (puVar4 == (ulong *)0x0) {
                Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
              }
              uVar18 = uStack_e0;
              uVar10 = uStack_e8;
              puVar4[1] = 0;
              puVar4[2] = 0;
              *puVar4 = 0;
              if ((uStack_f0 & 1) == 0) {
                puVar4[2] = uStack_e0;
                puVar4[1] = uStack_e8;
                *puVar4 = uStack_f0;
              }
              else {
                if (uStack_e8 < 0x17) {
                  uVar16 = (long)puVar4 + 1;
                  *(char *)puVar4 = (char)(uStack_e8 << 1);
                  if (uStack_e8 != 0) goto code_r0x018d2ab8;
                }
                else {
                  uVar17 = uStack_e8 + 0x10 & 0xfffffffffffffff0;
                  if (uVar17 == 0) {
                    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
                  }
                  uVar16 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar17,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
                  if (uVar16 == 0) {
                    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
                  }
                  puVar4[1] = uVar10;
                  puVar4[2] = uVar16;
                  *puVar4 = uVar17 | 1;
code_r0x018d2ab8:
                  memcpy(uVar16,uVar18,uVar10);
                }
                *(undefined1 *)(uVar16 + uVar10) = 0;
              }
              *(long *)(param_1 + 0x108) = *(long *)(param_1 + 0x108) + 0x18;
            }
            if ((uStack_f0 & 1) != 0) {
              Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_e0);
            }
          }
          if (((byte)plStack_d8 & 1) != 0) {
            Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_c8);
          }
          plVar3 = plStack_c0;
        }
        if (plVar3 != (long *)0x0) {
          while (plStack_b8 != plVar3) {
            while (plVar12 = plStack_b8 + -2, plVar1 = plStack_b8 + -1, plStack_b8 = plVar12,
                  *plVar1 != 0) {
              std::__ndk1::__shared_weak_count::__release_shared()();
              if (plStack_b8 == plVar3) goto code_r0x018d2b58;
            }
          }
code_r0x018d2b58:
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plStack_c0);
        }
        plVar1 = plStack_a8;
      }
      if (plVar1 != (long *)0x0) {
        while (plStack_a0 != plVar1) {
          while (plVar13 = plStack_a0 + -2, plVar11 = plStack_a0 + -1, plStack_a0 = plVar13,
                *plVar11 != 0) {
            std::__ndk1::__shared_weak_count::__release_shared()();
            if (plStack_a0 == plVar1) goto code_r0x018d2bb8;
          }
        }
code_r0x018d2bb8:
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plStack_a8);
      }
      plVar9 = plVar9 + 3;
    } while (plVar9 != plVar2);
  }
  plVar2 = plStack_90;
  if (plStack_90 != (long *)0x0) {
    while (plStack_88 != plVar2) {
      while (plVar11 = plStack_88 + -3, plVar9 = plStack_88 + -2, plStack_88 = plVar11, *plVar9 != 0
            ) {
        std::__ndk1::__shared_weak_count::__release_shared()();
        if (plStack_88 == plVar2) goto code_r0x018d2c18;
      }
    }
code_r0x018d2c18:
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plStack_90);
  }
  puVar6 = puStack_78;
  if (puStack_78 != (undefined4 *)0x0) {
    while (puStack_70 != puVar6) {
      puStack_70 = puStack_70 + -0x40;
      MissionUtility::tAreaInfo::~tAreaInfo()();
    }
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puStack_78);
  }
  return;
}

// ==== CGameResourceDownloader::InitAllDownloadList()
// vaddr 0x17d2c78 | ghidra 0x18d2c78 | size 272 | symbol _ZN23CGameResourceDownloader19InitAllDownloadListEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN23CGameResourceDownloader19InitAllDownloadListEv(long param_1)

{
  long *plVar1;
  long lVar2;
  long lVar3;
  long *plVar4;
  long lStack_48;
  
  lVar3 = *(long *)(param_1 + 0xe8);
  lVar2 = *(long *)(param_1 + 0xf0);
  if (lVar2 != lVar3) {
    *(ulong *)(param_1 + 0xf0) = lVar2 + (~((lVar2 + -8) - lVar3) & 0xfffffffffffffff8U);
  }
  plVar4 = *(long **)(param_1 + 0x128);
  do {
    while( true ) {
      if (plVar4 == (long *)0x0) {
        return;
      }
      lVar2 = plVar4[3] + 0x10;
      lVar3 = CGameResourceDownloader::SearchDownloadNode(char const*) const(param_1,lVar2);
      if ((((lVar3 == 0) || (3 < *(int *)(lVar3 + 8) - 1U)) &&
          (lVar3 = CGameResourceDownloader::SearchDownloadNode(char const*) const(param_1,lVar2), lVar3 != 0)) && (*(int *)(lVar3 + 8) != 5))
      break;
code_r0x018d2d50:
      plVar4 = (long *)*plVar4;
    }
    plVar1 = *(long **)(param_1 + 0xf0);
    lStack_48 = lVar2;
    if (plVar1 < *(long **)(param_1 + 0xf8)) {
      if (plVar1 == (long *)0x0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
      }
      *plVar1 = lStack_48;
      *(long *)(param_1 + 0xf0) = *(long *)(param_1 + 0xf0) + 8;
      goto code_r0x018d2d50;
    }
    void std::__ndk1::vector<char const*, Framework::CSTLAllocator<char const*, Framework::CSTLVectorAllocatorInf> >::__push_back_slow_path<char const*>(char const*&&)((long *)(param_1 + 0xe8),&lStack_48);
    plVar4 = (long *)*plVar4;
  } while( true );
}

// ==== CGameResourceDownloader::NeedNumDownload() const
// vaddr 0x17d2d88 | ghidra 0x18d2d88 | size 236 | symbol _ZNK23CGameResourceDownloader15NeedNumDownloadEv | lib libSOA-3.7.0.so | 2026-10-04
int _ZNK23CGameResourceDownloader15NeedNumDownloadEv(long param_1)

{
  undefined8 *puVar1;
  ulong uVar2;
  long lVar3;
  long lVar4;
  int iVar5;
  undefined8 uVar6;
  long *plVar7;
  undefined8 *puVar8;
  
  uVar2 = CUIUtility::IsRequestSelectAllDownload()();
  if ((uVar2 & 1) == 0) {
    puVar8 = *(undefined8 **)(param_1 + 0xe8);
    puVar1 = *(undefined8 **)(param_1 + 0xf0);
    if (puVar8 != puVar1) {
      iVar5 = 0;
      do {
        uVar6 = *puVar8;
        lVar3 = CGameResourceDownloader::SearchDownloadNode(char const*) const(param_1,uVar6);
        if ((((lVar3 == 0) || (3 < *(int *)(lVar3 + 8) - 1U)) &&
            (lVar3 = CGameResourceDownloader::SearchDownloadNode(char const*) const(param_1,uVar6), lVar3 != 0)) && (*(int *)(lVar3 + 8) != 5)) {
          iVar5 = iVar5 + 1;
        }
        puVar8 = puVar8 + 1;
      } while (puVar1 != puVar8);
      return iVar5;
    }
  }
  else {
    plVar7 = *(long **)(param_1 + 0x128);
    if (plVar7 != (long *)0x0) {
      iVar5 = 0;
      do {
        lVar4 = plVar7[3];
        lVar3 = CGameResourceDownloader::SearchDownloadNode(char const*) const(param_1,lVar4 + 0x10);
        if (((lVar3 == 0) || (3 < *(int *)(lVar3 + 8) - 1U)) &&
           ((lVar3 = CGameResourceDownloader::SearchDownloadNode(char const*) const(param_1,lVar4 + 0x10), lVar3 != 0 && (*(int *)(lVar3 + 8) != 5)
            ))) {
          iVar5 = iVar5 + 1;
        }
        plVar7 = (long *)*plVar7;
      } while (plVar7 != (long *)0x0);
      return iVar5;
    }
  }
  return 0;
}

// ==== CGameResourceDownloader::GetRequireDownloadSize() const
// vaddr 0x17d2e74 | ghidra 0x18d2e74 | size 204 | symbol _ZNK23CGameResourceDownloader22GetRequireDownloadSizeEv | lib libSOA-3.7.0.so | 2026-10-04
int _ZNK23CGameResourceDownloader22GetRequireDownloadSizeEv(long param_1)

{
  int iVar1;
  ulong uVar2;
  long *plVar3;
  long lVar4;
  long lVar5;
  long *plVar6;
  
  uVar2 = CUIUtility::IsRequestSelectAllDownload()();
  if ((uVar2 & 1) == 0) {
    plVar3 = *(long **)(param_1 + 0xe8);
    if (plVar3 == *(long **)(param_1 + 0xf0)) {
      return 0;
    }
    if (*(long **)(param_1 + 0x128) == (long *)0x0) {
      return 0;
    }
    iVar1 = 0;
    do {
      plVar6 = *(long **)(param_1 + 0x128);
      do {
        if (plVar6[3] + 0x10 == *plVar3) {
          iVar1 = iVar1 + *(int *)(plVar6[3] + 0x370);
          break;
        }
        plVar6 = (long *)*plVar6;
      } while (plVar6 != (long *)0x0);
      plVar3 = plVar3 + 1;
    } while (plVar3 != *(long **)(param_1 + 0xf0));
  }
  else {
    if (*(long *)(param_1 + 0x58) < 1) {
      return 0;
    }
    iVar1 = 0;
    lVar4 = 0;
    do {
      lVar5 = *(long *)(*(long *)(param_1 + 0x48) + lVar4 * 8);
      if (*(int *)(lVar5 + 8) != 5) {
        iVar1 = iVar1 + *(int *)(lVar5 + 0x370);
      }
      lVar4 = lVar4 + 1;
    } while (lVar4 < *(long *)(param_1 + 0x58));
  }
  return iVar1;
}

// ==== CGameResourceDownloader::CDownloadNode::GetContentsSize() const
// vaddr 0x17d2f40 | ghidra 0x18d2f40 | size 8 | symbol _ZNK23CGameResourceDownloader13CDownloadNode15GetContentsSizeEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK23CGameResourceDownloader13CDownloadNode15GetContentsSizeEv(long param_1)

{
  return *(undefined8 *)(param_1 + 0x370);
}

// ==== CGameResourceDownloader::GetRequireDownloadSize_withWorkSpace()
// vaddr 0x17d2f48 | ghidra 0x18d2f48 | size 180 | symbol _ZN23CGameResourceDownloader36GetRequireDownloadSize_withWorkSpaceEv | lib libSOA-3.7.0.so | 2026-10-04
int _ZN23CGameResourceDownloader36GetRequireDownloadSize_withWorkSpaceEv(long param_1)

{
  ulong uVar1;
  int iVar2;
  long lVar3;
  long *plVar4;
  long *plVar5;
  
  uVar1 = CUIUtility::IsRequestSelectAllDownload()();
  if ((uVar1 & 1) == 0) {
    plVar4 = *(long **)(param_1 + 0xe8);
    if ((plVar4 != *(long **)(param_1 + 0xf0)) && (*(long **)(param_1 + 0x128) != (long *)0x0)) {
      iVar2 = 0;
      do {
        plVar5 = *(long **)(param_1 + 0x128);
        do {
          if (plVar5[3] + 0x10 == *plVar4) {
            iVar2 = iVar2 + *(int *)(plVar5[3] + 0x370);
            break;
          }
          plVar5 = (long *)*plVar5;
        } while (plVar5 != (long *)0x0);
        plVar4 = plVar4 + 1;
      } while (plVar4 != *(long **)(param_1 + 0xf0));
      goto code_r0x018d2fec;
    }
  }
  else {
    lVar3 = *(long *)(param_1 + 0x58);
    if (0 < lVar3) {
      plVar4 = *(long **)(param_1 + 0x48);
      iVar2 = 0;
      do {
        if (*(int *)(*plVar4 + 8) != 5) {
          iVar2 = iVar2 + *(int *)(*plVar4 + 0x370);
        }
        lVar3 = lVar3 + -1;
        plVar4 = plVar4 + 1;
      } while (lVar3 != 0);
      goto code_r0x018d2fec;
    }
  }
  iVar2 = 0;
code_r0x018d2fec:
  return iVar2 + 0x6400000;
}

// ==== CGameResourceDownloader::GetRequireHiDownloadSize() const
// vaddr 0x17d2ffc | ghidra 0x18d2ffc | size 8 | symbol _ZNK23CGameResourceDownloader24GetRequireHiDownloadSizeEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK23CGameResourceDownloader24GetRequireHiDownloadSizeEv(long param_1)

{
  return *(undefined4 *)(param_1 + 0x26c);
}

// ==== CGameResourceDownloader::CalcNumDownload(unsigned int&, unsigned int&) const
// vaddr 0x17d3004 | ghidra 0x18d3004 | size 204 | symbol _ZNK23CGameResourceDownloader15CalcNumDownloadERjS0_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK23CGameResourceDownloader15CalcNumDownloadERjS0_
               (long param_1,int *param_2,undefined4 *param_3)

{
  uint uVar1;
  undefined4 uVar2;
  long *plVar3;
  long *plVar4;
  long *plVar5;
  
  *param_2 = 0;
  *param_3 = 0;
  uVar1 = CUIUtility::IsRequestSelectAllDownload()();
  if ((uVar1 & 1) == 0) {
    plVar3 = *(long **)(param_1 + 0xe8);
    plVar4 = *(long **)(param_1 + 0xf0);
    if (plVar3 != plVar4) {
      do {
        plVar5 = *(long **)(param_1 + 0x128);
        if (plVar5 != (long *)0x0) {
          do {
            if ((plVar5[3] + 0x10 == *plVar3) && (*(int *)(plVar5[3] + 8) == 5)) {
              *param_2 = *param_2 + 1;
              break;
            }
            plVar5 = (long *)*plVar5;
          } while (plVar5 != (long *)0x0);
        }
        plVar3 = plVar3 + 1;
      } while (plVar3 != plVar4);
      plVar3 = *(long **)(param_1 + 0xe8);
      plVar4 = *(long **)(param_1 + 0xf0);
    }
    uVar2 = (undefined4)((long)plVar4 - (long)plVar3 >> 3);
  }
  else {
    for (plVar3 = *(long **)(param_1 + 0x128); plVar3 != (long *)0x0; plVar3 = (long *)*plVar3) {
      if (*(int *)(plVar3[3] + 8) == 5) {
        *param_2 = *param_2 + 1;
      }
    }
    uVar2 = (undefined4)*(undefined8 *)(param_1 + 0x130);
  }
  *param_3 = uVar2;
  return;
}

// ==== CGameResourceDownloader::GetSetupProgressRate() const
// vaddr 0x17d30d0 | ghidra 0x18d30d0 | size 8 | symbol _ZNK23CGameResourceDownloader20GetSetupProgressRateEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK23CGameResourceDownloader20GetSetupProgressRateEv(long param_1)

{
  return *(undefined4 *)(param_1 + 0x140);
}

// ==== CGameResourceDownloader::RequestDownloadCancel()
// vaddr 0x17d30d8 | ghidra 0x18d30d8 | size 16 | symbol _ZN23CGameResourceDownloader21RequestDownloadCancelEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN23CGameResourceDownloader21RequestDownloadCancelEv(long param_1)

{
  *(undefined8 *)(param_1 + 0x14c) = 5;
  return;
}

// ==== CGameResourceDownloader::IsExistDownloadList(char const*) const
// vaddr 0x17d30e8 | ghidra 0x18d30e8 | size 48 | symbol _ZNK23CGameResourceDownloader19IsExistDownloadListEPKc | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK23CGameResourceDownloader19IsExistDownloadListEPKc(void)

{
  bool bVar1;
  long lVar2;
  
  lVar2 = CGameResourceDownloader::SearchDownloadNode(char const*) const();
  bVar1 = false;
  if (lVar2 != 0) {
    bVar1 = *(int *)(lVar2 + 8) == 1 || *(int *)(lVar2 + 8) - 2U < 3;
  }
  return bVar1;
}

// ==== CGameResourceDownloader::IsExistDownloadDB(char const*) const
// vaddr 0x17d3118 | ghidra 0x18d3118 | size 32 | symbol _ZNK23CGameResourceDownloader17IsExistDownloadDBEPKc | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK23CGameResourceDownloader17IsExistDownloadDBEPKc(void)

{
  bool bVar1;
  long lVar2;
  
  lVar2 = CGameResourceDownloader::SearchDownloadNode(char const*) const();
  bVar1 = false;
  if (lVar2 != 0) {
    bVar1 = *(int *)(lVar2 + 8) != 5;
  }
  return bVar1;
}

// ==== CGameResourceDownloader::CDownloadNode::IsDownloading() const
// vaddr 0x17d3138 | ghidra 0x18d3138 | size 20 | symbol _ZNK23CGameResourceDownloader13CDownloadNode13IsDownloadingEv | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK23CGameResourceDownloader13CDownloadNode13IsDownloadingEv(long param_1)

{
  return *(int *)(param_1 + 8) - 2U < 3;
}

// ==== CGameResourceDownloader::CDownloadNode::IsWaitingDownload() const
// vaddr 0x17d314c | ghidra 0x18d314c | size 16 | symbol _ZNK23CGameResourceDownloader13CDownloadNode17IsWaitingDownloadEv | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK23CGameResourceDownloader13CDownloadNode17IsWaitingDownloadEv(long param_1)

{
  return *(int *)(param_1 + 8) == 1;
}

// ==== CGameResourceDownloader::IsBuildInData(char const*) const
// vaddr 0x17d315c | ghidra 0x18d315c | size 1072 | symbol _ZNK23CGameResourceDownloader13IsBuildInDataEPKc | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK23CGameResourceDownloader13IsBuildInDataEPKc(long param_1,undefined8 param_2)

{
  char *pcVar1;
  ulong uVar2;
  byte bVar3;
  bool bVar4;
  int iVar5;
  ulong uVar6;
  long lVar7;
  long lVar8;
  ulong uVar9;
  ulong uVar10;
  char *pcVar11;
  ulong uStack_a0;
  ulong uStack_98;
  ulong uStack_90;
  ulong uStack_88;
  ulong uStack_80;
  ulong uStack_78;
  ulong uStack_70;
  ulong uStack_68;
  ulong uStack_60;
  ulong uStack_58;
  ulong uStack_50;
  char *pcStack_48;
  
  lVar8 = *(long *)(param_1 + 0x5d8);
  if ((lVar8 == 0) || (*(long *)(param_1 + 0x5e0) == 0)) {
    return false;
  }
  uStack_50 = 0;
  pcStack_48 = (char *)0x0;
  uStack_58 = 0;
  uStack_80 = 0;
  uStack_78 = 0;
  uStack_88 = 0;
  uVar6 = strlen(param_2);
  if (uVar6 < 0x17) {
    uVar9 = (ulong)&uStack_88 | 1;
    uStack_88 = CONCAT71(uStack_88._1_7_,(char)(uVar6 << 1));
    if (uVar6 != 0) goto code_r0x018d3234;
  }
  else {
    uVar10 = uVar6 + 0x10 & 0xfffffffffffffff0;
    if (uVar10 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
    }
    uVar9 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar10,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
    if (uVar9 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    }
    uStack_88 = uVar10 | 1;
    uStack_80 = uVar6;
    uStack_78 = uVar9;
code_r0x018d3234:
    memcpy(uVar9,param_2,uVar6);
  }
  *(undefined1 *)(uVar9 + uVar6) = 0;
  Aska::THashMap<string, CAssetInfo, Hasher_CSTLString, Aska::TEqualTo<string >, Aska::TAllocator<Aska::TPair<string const, CAssetInfo> > >::Find_(string const&) const(&uStack_70,lVar8 + 0x58,&uStack_88);
  if ((uStack_88 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_78);
  }
  pcVar11 = (char *)((ulong)&uStack_58 | 1);
  uVar6 = uStack_50;
  if ((uStack_70 !=
       *(long *)(*(long *)(param_1 + 0x5d8) + 0x78) +
       *(long *)(*(long *)(param_1 + 0x5d8) + 0x80) * 0xc0) &&
     (&uStack_58 != (ulong *)(uStack_70 + 0x30))) {
    uVar6 = *(ulong *)(uStack_70 + 0x38);
    lVar8 = *(long *)(uStack_70 + 0x40);
    if ((*(byte *)(uStack_70 + 0x30) & 1) == 0) {
      lVar8 = uStack_70 + 0x31;
      uVar6 = (ulong)(*(byte *)(uStack_70 + 0x30) >> 1);
    }
    if ((uStack_58 & 1) == 0) {
      uVar9 = 0x16;
      lVar7 = uVar6 - 0x16;
      uVar10 = uStack_58 & 0xff;
      if (0x15 < uVar6 && lVar7 != 0) {
code_r0x018d3318:
        uVar2 = (ulong)(((uint)uVar10 & 0xfe) >> 1);
        if ((uVar10 & 1) != 0) {
          uVar2 = uStack_50;
        }
        string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&uStack_58,uVar9,lVar7,uVar2,0,uVar2,uVar6);
        uVar6 = uStack_50;
        goto code_r0x018d3348;
      }
    }
    else {
      uVar9 = (uStack_58 & 0xfffffffffffffffe) - 1;
      lVar7 = uVar6 - uVar9;
      uVar10 = uStack_58;
      if (uVar9 <= uVar6 && lVar7 != 0) goto code_r0x018d3318;
    }
    pcVar1 = pcVar11;
    if ((uVar10 & 1) != 0) {
      pcVar1 = pcStack_48;
    }
    if (uVar6 != 0) {
      memmove(pcVar1,lVar8,uVar6);
    }
    pcVar1[uVar6] = '\0';
    if ((uStack_58 & 1) == 0) {
      uStack_58 = CONCAT71(uStack_58._1_7_,(char)(uVar6 << 1));
      uVar6 = uStack_50;
    }
  }
code_r0x018d3348:
  uStack_50 = uVar6;
  pcVar1 = pcVar11;
  if ((uStack_58 & 1) != 0) {
    pcVar1 = pcStack_48;
  }
  if (*pcVar1 == '\0') {
    bVar4 = false;
    if ((uStack_58 & 1) == 0) {
      return false;
    }
    goto code_r0x018d3568;
  }
  uStack_68 = 0;
  uStack_60 = 0;
  uStack_70 = 0;
  lVar8 = *(long *)(param_1 + 0x5e0);
  uStack_98 = 0;
  uStack_90 = 0;
  uStack_a0 = 0;
  uVar6 = strlen(param_2);
  if (uVar6 < 0x17) {
    uVar9 = (ulong)&uStack_a0 | 1;
    uStack_a0 = CONCAT71(uStack_a0._1_7_,(char)(uVar6 << 1));
    if (uVar6 != 0) goto code_r0x018d3414;
  }
  else {
    uVar10 = uVar6 + 0x10 & 0xfffffffffffffff0;
    if (uVar10 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
    }
    uVar9 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar10,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
    if (uVar9 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    }
    uStack_a0 = uVar10 | 1;
    uStack_98 = uVar6;
    uStack_90 = uVar9;
code_r0x018d3414:
    memcpy(uVar9,param_2,uVar6);
  }
  *(undefined1 *)(uVar9 + uVar6) = 0;
  Aska::THashMap<string, CAssetInfo, Hasher_CSTLString, Aska::TEqualTo<string >, Aska::TAllocator<Aska::TPair<string const, CAssetInfo> > >::Find_(string const&) const(&uStack_88,lVar8 + 0x58,&uStack_a0);
  if ((uStack_a0 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_90);
  }
  uVar6 = uStack_68;
  if ((uStack_88 !=
       *(long *)(*(long *)(param_1 + 0x5e0) + 0x78) +
       *(long *)(*(long *)(param_1 + 0x5e0) + 0x80) * 0xc0) &&
     (&uStack_70 != (ulong *)(uStack_88 + 0x30))) {
    uVar6 = *(ulong *)(uStack_88 + 0x38);
    lVar8 = *(long *)(uStack_88 + 0x40);
    if ((*(byte *)(uStack_88 + 0x30) & 1) == 0) {
      lVar8 = uStack_88 + 0x31;
      uVar6 = (ulong)(*(byte *)(uStack_88 + 0x30) >> 1);
    }
    if ((uStack_70 & 1) == 0) {
      uVar9 = 0x16;
      lVar7 = uVar6 - 0x16;
      uVar10 = uStack_70 & 0xff;
      if (0x15 < uVar6 && lVar7 != 0) {
code_r0x018d34f8:
        uVar2 = (ulong)(((uint)uVar10 & 0xfe) >> 1);
        if ((uVar10 & 1) != 0) {
          uVar2 = uStack_68;
        }
        string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&uStack_70,uVar9,lVar7,uVar2,0,uVar2,uVar6);
        uVar6 = uStack_68;
        goto code_r0x018d3528;
      }
    }
    else {
      uVar9 = (uStack_70 & 0xfffffffffffffffe) - 1;
      lVar7 = uVar6 - uVar9;
      uVar10 = uStack_70;
      if (uVar9 <= uVar6 && lVar7 != 0) goto code_r0x018d34f8;
    }
    uVar9 = (ulong)&uStack_70 | 1;
    if ((uVar10 & 1) != 0) {
      uVar9 = uStack_60;
    }
    if (uVar6 != 0) {
      memmove(uVar9,lVar8,uVar6);
    }
    *(undefined1 *)(uVar9 + uVar6) = 0;
    if ((uStack_70 & 1) == 0) {
      uStack_70 = CONCAT71(uStack_70._1_7_,(char)(uVar6 << 1));
      uVar6 = uStack_68;
    }
  }
code_r0x018d3528:
  uStack_68 = uVar6;
  uVar10 = uStack_60;
  uVar6 = uStack_70;
  bVar3 = (byte)uStack_58;
  if ((uStack_58 & 1) != 0) {
    pcVar11 = pcStack_48;
  }
  uVar9 = (ulong)&uStack_70 | 1;
  if ((uStack_70 & 1) != 0) {
    uVar9 = uStack_60;
  }
  iVar5 = strcmp(pcVar11,uVar9);
  bVar4 = iVar5 == 0;
  if ((uVar6 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uVar10);
    bVar3 = (byte)uStack_58;
  }
  if ((bVar3 & 1) == 0) {
    return bVar4;
  }
code_r0x018d3568:
  Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(pcStack_48);
  return bVar4;
}

// ==== CGameResourceDownloader::IsDownloading() const
// vaddr 0x17d358c | ghidra 0x18d358c | size 32 | symbol _ZNK23CGameResourceDownloader13IsDownloadingEv | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK23CGameResourceDownloader13IsDownloadingEv(long param_1)

{
  if (*(char *)(param_1 + 0x154) != '\0') {
    return false;
  }
  return *(int *)(param_1 + 0x90) != 0;
}

// ==== CGameResourceDownloader::NumDownloading() const
// vaddr 0x17d35ac | ghidra 0x18d35ac | size 24 | symbol _ZNK23CGameResourceDownloader14NumDownloadingEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK23CGameResourceDownloader14NumDownloadingEv(long param_1)

{
  if (*(char *)(param_1 + 0x154) != '\0') {
    return 0;
  }
  return *(undefined4 *)(param_1 + 0x90);
}

// ==== CGameResourceDownloader::EndNodeDownloading() const
// vaddr 0x17d35c4 | ghidra 0x18d35c4 | size 212 | symbol _ZNK23CGameResourceDownloader18EndNodeDownloadingEv | lib libSOA-3.7.0.so | 2026-10-04
int _ZNK23CGameResourceDownloader18EndNodeDownloadingEv(long param_1)

{
  int *piVar1;
  ulong uVar2;
  uint uVar3;
  ulong uVar4;
  ulong uVar5;
  int *piVar6;
  long lVar7;
  int iVar8;
  long lVar9;
  int iVar10;
  ulong uVar11;
  
  if (*(long *)(param_1 + 0x90) < 1) {
    return 0;
  }
  lVar7 = 0;
  while( true ) {
    lVar9 = *(long *)(*(long *)(param_1 + 0x80) + lVar7 * 8);
    uVar3 = *(uint *)(lVar9 + 400);
    uVar4 = (ulong)uVar3;
    if (uVar3 != 0) break;
    lVar7 = lVar7 + 1;
    if (*(long *)(param_1 + 0x90) <= lVar7) {
      return 0;
    }
  }
  lVar7 = *(long *)(lVar9 + 0x198);
  uVar2 = uVar4;
  if (uVar4 < 2) {
    uVar2 = 1;
  }
  if (uVar2 < 2) {
    uVar5 = 0;
  }
  else {
    uVar5 = uVar2 & 0xfffffffe;
    if (uVar5 != 0) {
      iVar8 = 0;
      iVar10 = 0;
      uVar11 = uVar5;
      lVar9 = lVar7;
      do {
        piVar6 = (int *)(lVar9 + 0x118);
        piVar1 = (int *)(lVar9 + 600);
        uVar11 = uVar11 - 2;
        lVar9 = lVar9 + 0x280;
        if (*piVar6 == 2) {
          iVar8 = iVar8 + 1;
        }
        if (*piVar1 == 2) {
          iVar10 = iVar10 + 1;
        }
      } while (uVar11 != 0);
      iVar10 = iVar10 + iVar8;
      if (uVar2 == uVar5) {
        return iVar10;
      }
      goto code_r0x018d366c;
    }
  }
  iVar10 = 0;
code_r0x018d366c:
  piVar6 = (int *)(lVar7 + uVar5 * 0x140 + 0x118);
  do {
    iVar8 = *piVar6;
    uVar5 = uVar5 + 1;
    piVar6 = piVar6 + 0x50;
    if (iVar8 == 2) {
      iVar10 = iVar10 + 1;
    }
  } while (uVar5 < uVar4);
  return iVar10;
}

// ==== CGameResourceDownloader::CDownloadNode::GetUnpackSize() const
// vaddr 0x17d3698 | ghidra 0x18d3698 | size 8 | symbol _ZNK23CGameResourceDownloader13CDownloadNode13GetUnpackSizeEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK23CGameResourceDownloader13CDownloadNode13GetUnpackSizeEv(long param_1)

{
  return *(undefined4 *)(param_1 + 400);
}

// ==== CGameResourceDownloader::CDownloadNode::GetUnpackNum() const
// vaddr 0x17d36a0 | ghidra 0x18d36a0 | size 160 | symbol _ZNK23CGameResourceDownloader13CDownloadNode12GetUnpackNumEv | lib libSOA-3.7.0.so | 2026-10-04
int _ZNK23CGameResourceDownloader13CDownloadNode12GetUnpackNumEv(long param_1)

{
  int *piVar1;
  uint uVar2;
  ulong uVar3;
  int *piVar4;
  int iVar5;
  int iVar6;
  ulong uVar7;
  long lVar8;
  
  uVar2 = *(uint *)(param_1 + 400);
  if (uVar2 == 0) {
    return 0;
  }
  if (uVar2 == 1) {
    uVar3 = 0;
  }
  else {
    uVar3 = (ulong)uVar2 - (ulong)(uVar2 & 1);
    if (uVar3 != 0) {
      iVar5 = 0;
      iVar6 = 0;
      uVar7 = uVar3;
      lVar8 = *(long *)(param_1 + 0x198);
      do {
        piVar4 = (int *)(lVar8 + 0x118);
        piVar1 = (int *)(lVar8 + 600);
        uVar7 = uVar7 - 2;
        lVar8 = lVar8 + 0x280;
        if (*piVar4 == 2) {
          iVar5 = iVar5 + 1;
        }
        if (*piVar1 == 2) {
          iVar6 = iVar6 + 1;
        }
      } while (uVar7 != 0);
      iVar6 = iVar6 + iVar5;
      if ((uVar2 & 1) == 0) {
        return iVar6;
      }
      goto code_r0x018d3714;
    }
  }
  iVar6 = 0;
code_r0x018d3714:
  piVar4 = (int *)(*(long *)(param_1 + 0x198) + uVar3 * 0x140 + 0x118);
  do {
    iVar5 = *piVar4;
    uVar3 = uVar3 + 1;
    piVar4 = piVar4 + 0x50;
    if (iVar5 == 2) {
      iVar6 = iVar6 + 1;
    }
  } while (uVar3 < uVar2);
  return iVar6;
}

// ==== CGameResourceDownloader::NumNodeDownloading() const
// vaddr 0x17d3740 | ghidra 0x18d3740 | size 72 | symbol _ZNK23CGameResourceDownloader18NumNodeDownloadingEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK23CGameResourceDownloader18NumNodeDownloadingEv(long param_1)

{
  long lVar1;
  
  if (*(long *)(param_1 + 0x90) < 1) {
    return 0;
  }
  lVar1 = 0;
  do {
    if (*(int *)((*(long **)(param_1 + 0x80))[lVar1] + 400) != 0) {
      return *(undefined4 *)(**(long **)(param_1 + 0x80) + 400);
    }
    lVar1 = lVar1 + 1;
  } while (lVar1 < *(long *)(param_1 + 0x90));
  return 0;
}

// ==== CGameResourceDownloader::NumDownloadingExactWaiting(int) const
// vaddr 0x17d3788 | ghidra 0x18d3788 | size 344 | symbol _ZNK23CGameResourceDownloader26NumDownloadingExactWaitingEi | lib libSOA-3.7.0.so | 2026-10-04
int _ZNK23CGameResourceDownloader26NumDownloadingExactWaitingEi(long param_1,int param_2)

{
  long *plVar1;
  long lVar2;
  ulong uVar3;
  long lVar4;
  ulong uVar5;
  ulong uVar6;
  uint uVar7;
  ulong uVar8;
  int iVar9;
  int iVar10;
  long *plVar11;
  
  uVar3 = *(ulong *)(param_1 + 0x90);
  if ((long)uVar3 < 1) {
    return 0;
  }
  lVar4 = *(long *)(param_1 + 0x80);
  if (param_2 < 0) {
    if ((uVar3 < 2) || (uVar8 = uVar3 & 0xfffffffffffffffe, uVar8 == 0)) {
      uVar6 = 0;
      uVar7 = 0;
      iVar10 = 0;
    }
    else {
      uVar7 = 0;
      uVar6 = 0;
      if ((int)(uVar3 - 1) == -1) {
        iVar10 = 0;
      }
      else {
        iVar10 = 0;
        if (uVar3 - 1 >> 0x20 == 0) {
          iVar10 = 0;
          uVar7 = (uint)uVar8;
          plVar11 = (long *)(lVar4 + 8);
          iVar9 = 0;
          uVar6 = uVar8;
          do {
            plVar1 = plVar11 + -1;
            lVar2 = *plVar11;
            uVar6 = uVar6 - 2;
            plVar11 = plVar11 + 2;
            iVar9 = iVar9 + (uint)(*(int *)(*plVar1 + 8) - 2U < 3 && *(int *)(*plVar1 + 8) != 4);
            iVar10 = iVar10 + (uint)(*(int *)(lVar2 + 8) - 2U < 3 && *(int *)(lVar2 + 8) != 4);
          } while (uVar6 != 0);
          iVar10 = iVar10 + iVar9;
          uVar6 = uVar8;
          if (uVar3 == uVar8) {
            return iVar10;
          }
        }
      }
    }
    do {
      uVar7 = uVar7 + 1;
      iVar9 = *(int *)(*(long *)(lVar4 + uVar6 * 8) + 8);
      iVar10 = iVar10 + (uint)(iVar9 - 2U < 3 && iVar9 != 4);
      uVar6 = (ulong)uVar7;
    } while ((long)(ulong)uVar7 < (long)uVar3);
  }
  else {
    iVar10 = 0;
    uVar8 = 1;
    uVar6 = 0;
    do {
      uVar5 = uVar8;
      iVar9 = *(int *)(*(long *)(lVar4 + uVar6 * 8) + 8);
      iVar10 = iVar10 + (uint)(iVar9 - 2U < 3 && iVar9 != 4);
      if (param_2 <= iVar10) {
        return iVar10;
      }
      uVar8 = (ulong)((int)uVar5 + 1);
      uVar6 = uVar5;
    } while ((long)uVar5 < (long)uVar3);
  }
  return iVar10;
}

// ==== CGameResourceDownloader::CDownloadNode::IsUnpacking() const
// vaddr 0x17d38e0 | ghidra 0x18d38e0 | size 16 | symbol _ZNK23CGameResourceDownloader13CDownloadNode11IsUnpackingEv | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK23CGameResourceDownloader13CDownloadNode11IsUnpackingEv(long param_1)

{
  return *(int *)(param_1 + 8) == 4;
}

// ==== CGameResourceDownloader::NumUnpakingExactWaiting(int) const
// vaddr 0x17d38f0 | ghidra 0x18d38f0 | size 264 | symbol _ZNK23CGameResourceDownloader23NumUnpakingExactWaitingEi | lib libSOA-3.7.0.so | 2026-10-04
int _ZNK23CGameResourceDownloader23NumUnpakingExactWaitingEi(long param_1,int param_2)

{
  long *plVar1;
  long lVar2;
  ulong uVar3;
  long lVar4;
  ulong uVar5;
  ulong uVar6;
  uint uVar7;
  ulong uVar8;
  int iVar9;
  int iVar10;
  long *plVar11;
  
  uVar3 = *(ulong *)(param_1 + 0x90);
  if ((long)uVar3 < 1) {
    return 0;
  }
  lVar4 = *(long *)(param_1 + 0x80);
  if (param_2 < 0) {
    if ((uVar3 < 2) || (uVar8 = uVar3 & 0xfffffffffffffffe, uVar8 == 0)) {
      uVar6 = 0;
      uVar7 = 0;
      iVar10 = 0;
    }
    else {
      uVar7 = 0;
      uVar6 = 0;
      if ((int)(uVar3 - 1) == -1) {
        iVar10 = 0;
      }
      else {
        iVar10 = 0;
        if (uVar3 - 1 >> 0x20 == 0) {
          iVar10 = 0;
          uVar7 = (uint)uVar8;
          plVar11 = (long *)(lVar4 + 8);
          iVar9 = 0;
          uVar6 = uVar8;
          do {
            plVar1 = plVar11 + -1;
            lVar2 = *plVar11;
            uVar6 = uVar6 - 2;
            plVar11 = plVar11 + 2;
            if (*(int *)(*plVar1 + 8) == 4) {
              iVar9 = iVar9 + 1;
            }
            if (*(int *)(lVar2 + 8) == 4) {
              iVar10 = iVar10 + 1;
            }
          } while (uVar6 != 0);
          iVar10 = iVar10 + iVar9;
          uVar6 = uVar8;
          if (uVar3 == uVar8) {
            return iVar10;
          }
        }
      }
    }
    do {
      uVar7 = uVar7 + 1;
      if (*(int *)(*(long *)(lVar4 + uVar6 * 8) + 8) == 4) {
        iVar10 = iVar10 + 1;
      }
      uVar6 = (ulong)uVar7;
    } while ((long)(ulong)uVar7 < (long)uVar3);
  }
  else {
    iVar10 = 0;
    uVar8 = 1;
    uVar6 = 0;
    do {
      uVar5 = uVar8;
      if (*(int *)(*(long *)(lVar4 + uVar6 * 8) + 8) == 4) {
        iVar10 = iVar10 + 1;
      }
    } while ((iVar10 < param_2) &&
            (uVar8 = (ulong)((int)uVar5 + 1), uVar6 = uVar5, (long)uVar5 < (long)uVar3));
  }
  return iVar10;
}

// ==== CGameResourceDownloader::IsReadyDownloadFlag() const
// vaddr 0x17d39f8 | ghidra 0x18d39f8 | size 8 | symbol _ZNK23CGameResourceDownloader19IsReadyDownloadFlagEv | lib libSOA-3.7.0.so | 2026-10-04
undefined1 _ZNK23CGameResourceDownloader19IsReadyDownloadFlagEv(long param_1)

{
  return *(undefined1 *)(param_1 + 0x156);
}

// ==== CGameResourceDownloader::IsExistOldVersion()
// vaddr 0x17d3a00 | ghidra 0x18d3a00 | size 760 | symbol _ZN23CGameResourceDownloader17IsExistOldVersionEv | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

bool _ZN23CGameResourceDownloader17IsExistOldVersionEv(void)

{
  undefined8 *puVar1;
  ulong uVar2;
  ulong uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  bool bVar6;
  int iVar7;
  ulong uVar8;
  ulong uVar9;
  long lVar10;
  ulong uVar11;
  ulong uStack_78;
  ulong uStack_70;
  ulong uStack_68;
  ulong uStack_60;
  ulong uStack_58;
  ulong uStack_50;
  ulong uStack_40;
  ulong uStack_38;
  ulong uStack_30;
  
  BAS::GetDownloadPath()(&uStack_40);
  if ((uStack_40 & 1) == 0) {
    uVar9 = 0x16;
    uVar8 = uStack_40 & 0xff;
  }
  else {
    uVar9 = (uStack_40 & 0xfffffffffffffffe) - 1;
    uVar8 = uStack_40;
  }
  uVar11 = (ulong)(((uint)uVar8 & 0xfe) >> 1);
  if ((uVar8 & 1) != 0) {
    uVar11 = uStack_38;
  }
  if (uVar9 == uVar11) {
    string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&uStack_40,uVar9,1,uVar9,uVar9,0,1,&UNK_029c5d3e/*"/"*/);
  }
  else {
    uVar9 = (ulong)&uStack_40 | 1;
    if ((uVar8 & 1) != 0) {
      uVar9 = uStack_30;
    }
    *(undefined1 *)(uVar9 + uVar11) = 0x2f;
    uVar11 = uVar11 + 1;
    uVar8 = uVar11;
    if ((uStack_40 & 1) == 0) {
      uStack_40 = CONCAT71(uStack_40._1_7_,(char)uVar11 * '\x02');
      uVar8 = uStack_38;
    }
    uStack_38 = uVar8;
    *(undefined1 *)(uVar9 + uVar11) = 0;
  }
  uStack_50 = uStack_30;
  uStack_58 = uStack_38;
  uStack_60 = uStack_40;
  CGameResourceDownloader::CheckLocalResourceFileToolVersionOld()+0x354(&uStack_78);
  uVar5 = _UNK_02866da2;
  if ((uStack_78 & 1) == 0) {
    lVar10 = 0x16;
    uVar8 = uStack_78 & 0xff;
  }
  else {
    lVar10 = (uStack_78 & 0xfffffffffffffffe) - 1;
    uVar8 = uStack_78;
  }
  uVar9 = (ulong)(((uint)uVar8 & 0xfe) >> 1);
  if ((uVar8 & 1) != 0) {
    uVar9 = uStack_70;
  }
  if (lVar10 - uVar9 < 0x16) {
    string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&uStack_78,lVar10,(0x16 - lVar10) + uVar9,uVar9,uVar9,0,0x16,&UNK_02866da2/*"version_latest.version"*/);
  }
  else {
    uVar4 = CONCAT26(_UNK_02866db0,_UNK_02866daa);
    uVar11 = (ulong)&uStack_78 | 1;
    if ((uVar8 & 1) != 0) {
      uVar11 = uStack_68;
    }
    puVar1 = (undefined8 *)(uVar11 + uVar9);
    *(ulong *)((long)puVar1 + 0xe) = CONCAT62(_UNK_02866db2,_UNK_02866db0);
    puVar1[1] = uVar4;
    *puVar1 = uVar5;
    uVar9 = uVar9 + 0x16;
    uVar8 = uVar9;
    if ((uStack_78 & 1) == 0) {
      uStack_78 = CONCAT71(uStack_78._1_7_,(char)uVar9 * '\x02');
      uVar8 = uStack_70;
    }
    uStack_70 = uVar8;
    *(undefined1 *)(uVar11 + uVar9) = 0;
  }
  uStack_30 = uStack_68;
  uStack_38 = uStack_70;
  uStack_40 = uStack_78;
  uStack_70 = 0;
  uStack_68 = 0;
  bVar6 = (uStack_78 & 1) != 0;
  uVar8 = (ulong)&uStack_40 | 1;
  if (bVar6) {
    uVar8 = uStack_30;
  }
  uVar9 = uStack_78 >> 1 & 0x7f;
  if (bVar6) {
    uVar9 = uStack_38;
  }
  uStack_78 = 0;
  if ((uStack_60 & 1) == 0) {
    lVar10 = 0x16;
    uVar11 = uStack_60 & 0xff;
  }
  else {
    lVar10 = (uStack_60 & 0xfffffffffffffffe) - 1;
    uVar11 = uStack_60;
  }
  uVar2 = (ulong)(((uint)uVar11 & 0xfe) >> 1);
  if ((uVar11 & 1) != 0) {
    uVar2 = uStack_58;
  }
  if (lVar10 - uVar2 < uVar9) {
    string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&uStack_60,lVar10,(uVar9 - lVar10) + uVar2,uVar2,uVar2,0,uVar9);
    if ((uStack_40 & 1) != 0) goto code_r0x018d3c1c;
code_r0x018d3c98:
    if ((uStack_78 & 1) == 0) goto code_r0x018d3ca0;
code_r0x018d3c2c:
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_68);
    if ((uStack_60 & 1) != 0) goto code_r0x018d3c3c;
code_r0x018d3ca8:
    uVar8 = (ulong)&uStack_60 | 1;
  }
  else {
    if (uVar9 != 0) {
      uVar3 = (ulong)&uStack_60 | 1;
      if ((uVar11 & 1) != 0) {
        uVar3 = uStack_50;
      }
      memcpy(uVar3 + uVar2,uVar8,uVar9);
      uVar2 = uVar2 + uVar9;
      if ((uStack_60 & 1) == 0) {
        uStack_60 = CONCAT71(uStack_60._1_7_,(char)uVar2 * '\x02');
        *(undefined1 *)(uVar3 + uVar2) = 0;
      }
      else {
        *(undefined1 *)(uVar3 + uVar2) = 0;
        uStack_58 = uVar2;
      }
    }
    if ((uStack_40 & 1) == 0) goto code_r0x018d3c98;
code_r0x018d3c1c:
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_30);
    if ((uStack_78 & 1) != 0) goto code_r0x018d3c2c;
code_r0x018d3ca0:
    if ((uStack_60 & 1) == 0) goto code_r0x018d3ca8;
code_r0x018d3c3c:
    uVar8 = uStack_50;
    if (uStack_50 == 0) {
      bVar6 = false;
      if (((byte)uStack_60 & 1) == 0) {
        return false;
      }
      goto code_r0x018d3cc8;
    }
  }
  iVar7 = access(uVar8,0);
  bVar6 = iVar7 == 0;
  if ((uStack_60 & 1) == 0) {
    return bVar6;
  }
code_r0x018d3cc8:
  Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_50);
  return bVar6;
}

// ==== CGameResourceDownloader::IsExistLocalVersion()
// vaddr 0x17d3cf8 | ghidra 0x18d3cf8 | size 760 | symbol _ZN23CGameResourceDownloader19IsExistLocalVersionEv | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

bool _ZN23CGameResourceDownloader19IsExistLocalVersionEv(void)

{
  ulong uVar1;
  ulong uVar2;
  undefined8 uVar3;
  bool bVar4;
  int iVar5;
  ulong uVar6;
  ulong uVar7;
  long lVar8;
  ulong uVar9;
  ulong uStack_78;
  ulong uStack_70;
  ulong uStack_68;
  ulong uStack_60;
  ulong uStack_58;
  ulong uStack_50;
  ulong uStack_40;
  ulong uStack_38;
  ulong uStack_30;
  
  BAS::GetDownloadPath()(&uStack_40);
  if ((uStack_40 & 1) == 0) {
    uVar7 = 0x16;
    uVar6 = uStack_40 & 0xff;
  }
  else {
    uVar7 = (uStack_40 & 0xfffffffffffffffe) - 1;
    uVar6 = uStack_40;
  }
  uVar9 = (ulong)(((uint)uVar6 & 0xfe) >> 1);
  if ((uVar6 & 1) != 0) {
    uVar9 = uStack_38;
  }
  if (uVar7 == uVar9) {
    string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&uStack_40,uVar7,1,uVar7,uVar7,0,1,&UNK_029c5d3e/*"/"*/);
  }
  else {
    uVar7 = (ulong)&uStack_40 | 1;
    if ((uVar6 & 1) != 0) {
      uVar7 = uStack_30;
    }
    *(undefined1 *)(uVar7 + uVar9) = 0x2f;
    uVar9 = uVar9 + 1;
    uVar6 = uVar9;
    if ((uStack_40 & 1) == 0) {
      uStack_40 = CONCAT71(uStack_40._1_7_,(char)uVar9 * '\x02');
      uVar6 = uStack_38;
    }
    uStack_38 = uVar6;
    *(undefined1 *)(uVar7 + uVar9) = 0;
  }
  uStack_50 = uStack_30;
  uStack_58 = uStack_38;
  uStack_60 = uStack_40;
  CGameResourceDownloader::CheckLocalResourceFileToolVersionOld()+0x354(&uStack_78);
  if ((uStack_78 & 1) == 0) {
    lVar8 = 0x16;
    uVar6 = uStack_78 & 0xff;
  }
  else {
    lVar8 = (uStack_78 & 0xfffffffffffffffe) - 1;
    uVar6 = uStack_78;
  }
  uVar7 = (ulong)(((uint)uVar6 & 0xfe) >> 1);
  if ((uVar6 & 1) != 0) {
    uVar7 = uStack_70;
  }
  if (lVar8 - uVar7 < 0xf) {
    string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&uStack_78,lVar8,(0xf - lVar8) + uVar7,uVar7,uVar7,0,0xf,&UNK_02866db9/*"version.version"*/);
  }
  else {
    uVar3 = CONCAT17(UNK_02866dc0,_UNK_02866db9);
    uVar9 = (ulong)&uStack_78 | 1;
    if ((uVar6 & 1) != 0) {
      uVar9 = uStack_68;
    }
    *(ulong *)((long)(uVar9 + uVar7) + 7) = CONCAT71(_UNK_02866dc1,UNK_02866dc0);
    *(undefined8 *)(uVar9 + uVar7) = uVar3;
    uVar7 = uVar7 + 0xf;
    uVar6 = uVar7;
    if ((uStack_78 & 1) == 0) {
      uStack_78 = CONCAT71(uStack_78._1_7_,(char)uVar7 * '\x02');
      uVar6 = uStack_70;
    }
    uStack_70 = uVar6;
    *(undefined1 *)(uVar9 + uVar7) = 0;
  }
  uStack_30 = uStack_68;
  uStack_38 = uStack_70;
  uStack_40 = uStack_78;
  uStack_70 = 0;
  uStack_68 = 0;
  bVar4 = (uStack_78 & 1) != 0;
  uVar6 = (ulong)&uStack_40 | 1;
  if (bVar4) {
    uVar6 = uStack_30;
  }
  uVar7 = uStack_78 >> 1 & 0x7f;
  if (bVar4) {
    uVar7 = uStack_38;
  }
  uStack_78 = 0;
  if ((uStack_60 & 1) == 0) {
    lVar8 = 0x16;
    uVar9 = uStack_60 & 0xff;
  }
  else {
    lVar8 = (uStack_60 & 0xfffffffffffffffe) - 1;
    uVar9 = uStack_60;
  }
  uVar1 = (ulong)(((uint)uVar9 & 0xfe) >> 1);
  if ((uVar9 & 1) != 0) {
    uVar1 = uStack_58;
  }
  if (lVar8 - uVar1 < uVar7) {
    string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&uStack_60,lVar8,(uVar7 - lVar8) + uVar1,uVar1,uVar1,0,uVar7);
    if ((uStack_40 & 1) != 0) goto code_r0x018d3f14;
code_r0x018d3f90:
    if ((uStack_78 & 1) == 0) goto code_r0x018d3f98;
code_r0x018d3f24:
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_68);
    if ((uStack_60 & 1) != 0) goto code_r0x018d3f34;
code_r0x018d3fa0:
    uVar6 = (ulong)&uStack_60 | 1;
  }
  else {
    if (uVar7 != 0) {
      uVar2 = (ulong)&uStack_60 | 1;
      if ((uVar9 & 1) != 0) {
        uVar2 = uStack_50;
      }
      memcpy(uVar2 + uVar1,uVar6,uVar7);
      uVar1 = uVar1 + uVar7;
      if ((uStack_60 & 1) == 0) {
        uStack_60 = CONCAT71(uStack_60._1_7_,(char)uVar1 * '\x02');
        *(undefined1 *)(uVar2 + uVar1) = 0;
      }
      else {
        *(undefined1 *)(uVar2 + uVar1) = 0;
        uStack_58 = uVar1;
      }
    }
    if ((uStack_40 & 1) == 0) goto code_r0x018d3f90;
code_r0x018d3f14:
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_30);
    if ((uStack_78 & 1) != 0) goto code_r0x018d3f24;
code_r0x018d3f98:
    if ((uStack_60 & 1) == 0) goto code_r0x018d3fa0;
code_r0x018d3f34:
    uVar6 = uStack_50;
    if (uStack_50 == 0) {
      bVar4 = false;
      if (((byte)uStack_60 & 1) == 0) {
        return false;
      }
      goto code_r0x018d3fc0;
    }
  }
  iVar5 = access(uVar6,0);
  bVar4 = iVar5 == 0;
  if ((uStack_60 & 1) == 0) {
    return bVar4;
  }
code_r0x018d3fc0:
  Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_50);
  return bVar4;
}

// ==== CGameResourceDownloader::SetOldVersionFileChecked()
// vaddr 0x17d3ff0 | ghidra 0x18d3ff0 | size 12 | symbol _ZN23CGameResourceDownloader24SetOldVersionFileCheckedEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN23CGameResourceDownloader24SetOldVersionFileCheckedEv(long param_1)

{
  *(undefined1 *)(param_1 + 0x15f) = 1;
  return;
}

// ==== CGameResourceDownloader::IsCheckedOldVersionFile()
// vaddr 0x17d3ffc | ghidra 0x18d3ffc | size 8 | symbol _ZN23CGameResourceDownloader23IsCheckedOldVersionFileEv | lib libSOA-3.7.0.so | 2026-10-04
undefined1 _ZN23CGameResourceDownloader23IsCheckedOldVersionFileEv(long param_1)

{
  return *(undefined1 *)(param_1 + 0x15f);
}

// ==== CGameResourceDownloader::IsModeDownload() const
// vaddr 0x17d4004 | ghidra 0x18d4004 | size 16 | symbol _ZNK23CGameResourceDownloader14IsModeDownloadEv | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK23CGameResourceDownloader14IsModeDownloadEv(long param_1)

{
  return *(int *)(param_1 + 0x14c) == 4;
}

// ==== CGameResourceDownloader::IsExistCache() const
// vaddr 0x17d4014 | ghidra 0x18d4014 | size 104 | symbol _ZNK23CGameResourceDownloader12IsExistCacheEv | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK23CGameResourceDownloader12IsExistCacheEv(void)

{
  bool bVar1;
  int iVar2;
  ulong uVar3;
  byte abStack_28 [16];
  ulong uStack_18;
  
  BAS::GetDownloadPath()(abStack_28);
  if ((abStack_28[0] & 1) == 0) {
    uVar3 = (ulong)abStack_28 | 1;
  }
  else {
    uVar3 = uStack_18;
    if (uStack_18 == 0) {
      bVar1 = false;
      goto joined_r0x018d4074;
    }
  }
  iVar2 = access(uVar3,0);
  bVar1 = iVar2 == 0;
joined_r0x018d4074:
  if ((abStack_28[0] & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_18);
  }
  return bVar1;
}

// ==== CGameResourceDownloader::ForEach(char const*, std::__ndk1::function<bool (char const*)> const&)
// vaddr 0x17d407c | ghidra 0x18d407c | size 644 | symbol _ZN23CGameResourceDownloader7ForEachEPKcRKNSt6__ndk18functionIFbS1_EEE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN23CGameResourceDownloader7ForEachEPKcRKNSt6__ndk18functionIFbS1_EEE
               (long param_1,long param_2,long param_3)

{
  bool bVar1;
  long lVar2;
  ulong uVar3;
  long lVar4;
  char *pcVar5;
  char *pcVar6;
  char *pcVar7;
  undefined1 auStack_110 [8];
  undefined8 uStack_108;
  undefined8 uStack_100;
  undefined8 uStack_f8;
  undefined8 uStack_f0;
  undefined8 uStack_e8;
  long lStack_e0;
  undefined8 uStack_d8;
  char *pcStack_d0;
  char *pcStack_c8;
  undefined8 uStack_c0;
  undefined8 uStack_b8;
  undefined8 uStack_b0;
  undefined1 uStack_a8;
  undefined8 uStack_a0;
  undefined8 uStack_98;
  undefined1 uStack_90;
  undefined8 uStack_88;
  undefined8 uStack_80;
  char cStack_78;
  undefined1 uStack_70;
  undefined8 uStack_68;
  
  if (*(long *)(param_1 + 0x5d8) != 0) {
    std::__ndk1::locale::locale()(auStack_110);
    uStack_108 = std::__ndk1::locale::use_facet(std::__ndk1::locale::id&) const(auStack_110,PTR__ZNSt6__ndk15ctypeIcE2idE_02cc4c88);
    uStack_100 = std::__ndk1::locale::use_facet(std::__ndk1::locale::id&) const(auStack_110,PTR__ZNSt6__ndk17collateIcE2idE_02cc0d10);
    lStack_e0 = 0;
    uStack_e8 = 0;
    uStack_d8 = 0;
    uStack_f0 = 0;
    uStack_f8 = 0;
    lVar2 = strlen(param_2);
    char const* std::__ndk1::basic_regex<char, std::__ndk1::regex_traits<char> >::__parse<char const*>(char const*, char const*)(auStack_110,param_2,param_2 + lVar2);
    lVar2 = *(long *)(param_1 + 0x5d8);
    if (*(int *)(lVar2 + 0x68) != 0) {
      pcVar7 = *(char **)(lVar2 + 0x78);
      lVar2 = *(long *)(lVar2 + 0x80);
      pcVar6 = pcVar7;
      if (lVar2 == 0) {
code_r0x018d4144:
        pcVar7 = pcVar7 + lVar2 * 0xc0;
        if (pcVar6 != pcVar7) {
          do {
            if ((pcVar6[8] & 1U) == 0) {
              pcVar5 = pcVar6 + 9;
            }
            else {
              pcVar5 = *(char **)(pcVar6 + 0x18);
            }
            lVar2 = strlen(pcVar5);
            uStack_90 = 0;
            uStack_a0 = 0;
            uStack_98 = 0;
            cStack_78 = '\0';
            uStack_88 = 0;
            uStack_80 = 0;
            uStack_70 = 0;
            uStack_68 = 0;
            uStack_a8 = 0;
            pcStack_d0 = (char *)0x0;
            pcStack_c8 = (char *)0x0;
            uStack_b8 = 0;
            uStack_b0 = 0;
            uStack_c0 = 0;
            uVar3 = bool std::__ndk1::basic_regex<char, std::__ndk1::regex_traits<char> >::__search<std::__ndk1::allocator<std::__ndk1::sub_match<char const*> > >(char const*, char const*, std::__ndk1::match_results<char const*, std::__ndk1::allocator<std::__ndk1::sub_match<char const*> > >&, std::__ndk1::regex_constants::match_flag_type) const(auStack_110,pcVar5,pcVar5 + lVar2,&pcStack_d0,0x40);
            bVar1 = false;
            if ((uVar3 & 1) != 0) {
              if (cStack_78 == '\0') {
                bVar1 = true;
              }
              else if (pcStack_c8 == pcStack_d0) {
                bVar1 = false;
              }
              else {
                bVar1 = false;
                pcStack_c8 = pcStack_c8 +
                             ((ulong)(pcStack_c8 + (-0x18 - (long)pcStack_d0)) / 0x18 ^
                             0xffffffffffffffff) * 0x18;
              }
            }
            if (pcStack_d0 != (char *)0x0) {
              if (pcStack_c8 != pcStack_d0) {
                pcStack_c8 = pcStack_c8 +
                             ((ulong)(pcStack_c8 + (-0x18 - (long)pcStack_d0)) / 0x18 ^
                             0xffffffffffffffff) * 0x18;
              }
              operator delete(void*)();
            }
            pcVar5 = pcVar6;
            if (bVar1) {
              if ((pcVar6[8] & 1U) == 0) {
                pcStack_d0 = pcVar6 + 9;
              }
              else {
                pcStack_d0 = *(char **)(pcVar6 + 0x18);
              }
              uVar3 = (**(code **)(**(long **)(param_3 + 0x20) + 0x30))
                                (*(long **)(param_3 + 0x20),&pcStack_d0);
              if ((uVar3 & 1) != 0) break;
            }
            do {
              pcVar6 = pcVar7;
              if (pcVar7 == pcVar5) break;
              pcVar6 = pcVar5 + 0xc0;
              pcVar5 = pcVar6;
            } while (*pcVar6 != '\x01');
          } while (pcVar6 != (char *)(*(long *)(*(long *)(param_1 + 0x5d8) + 0x78) +
                                     *(long *)(*(long *)(param_1 + 0x5d8) + 0x80) * 0xc0));
        }
      }
      else {
        lVar4 = lVar2 * 0xc0;
        do {
          if (*pcVar6 == '\x01') goto code_r0x018d4144;
          lVar4 = lVar4 + -0xc0;
          pcVar6 = pcVar6 + 0xc0;
        } while (lVar4 != 0);
      }
    }
    if (lStack_e0 != 0) {
      std::__ndk1::__shared_weak_count::__release_shared()();
    }
    std::__ndk1::locale::~locale()(auStack_110);
  }
  return;
}

// ==== CGameResourceDownloader::NotifyRequireDownLoad(Aska::ASON::AValue const*, char const*, char const*, unsigned int, CMetaList)
// vaddr 0x17d4300 | ghidra 0x18d4300 | size 1112 | symbol _ZN23CGameResourceDownloader21NotifyRequireDownLoadEPKN4Aska4ASON6AValueEPKcS6_j9CMetaList | lib libSOA-3.7.0.so | 2026-10-04
void _ZN23CGameResourceDownloader21NotifyRequireDownLoadEPKN4Aska4ASON6AValueEPKcS6_j9CMetaList
               (long param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               undefined4 param_5,undefined8 param_6)

{
  long *plVar1;
  ulong uVar2;
  uint uVar3;
  long lVar4;
  code *pcVar5;
  long *plVar6;
  long *plVar7;
  ulong uVar8;
  long *unaff_x19;
  long lVar9;
  ulong uVar10;
  ulong uVar11;
  float fVar12;
  undefined *puStack_108;
  long *plStack_100;
  long lStack_f0;
  ushort uStack_d6;
  ulong uStack_c0;
  ulong uStack_b8;
  ulong uStack_b0;
  long alStack_a8 [3];
  long alStack_90 [4];
  long *plStack_70;
  
  Framework::CHash32::CHash32(char const*)(alStack_a8,param_3);
  uVar3 = Framework::CHash32::Get() const(alStack_a8);
  uVar10 = (ulong)uVar3;
  Framework::CHash32::~CHash32()(alStack_a8);
  lVar4 = operator new(unsigned long, std::nothrow_t const&)(0x450,PTR__ZSt7nothrow_02cb9a80);
  if (lVar4 != 0) {
    plStack_70 = (long *)0x0;
    unaff_x19 = alStack_90;
    CGameResourceDownloader::CDownloadNode::CDownloadNode(char const*, std::__ndk1::function<void (char const*, CGameResourceDownloader::iErrorCode)>)(lVar4,param_3,alStack_90);
    if (unaff_x19 == plStack_70) {
      pcVar5 = *(code **)(*plStack_70 + 0x20);
    }
    else {
      if (plStack_70 == (long *)0x0) goto code_r0x018d43a8;
      pcVar5 = *(code **)(*plStack_70 + 0x28);
    }
    (*pcVar5)();
  }
code_r0x018d43a8:
  uVar11 = *(ulong *)(param_1 + 0x120);
  plVar1 = (long *)(param_1 + 0x118);
  if (uVar11 == 0) {
code_r0x018d443c:
    plVar6 = (long *)Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(0x20,&UNK_027dc2d5/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_UnorderedMap.h"*/,0x1c);
    if (plVar6 == (long *)0x0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    }
    *(uint *)(plVar6 + 2) = uVar3;
    plVar6[3] = lVar4;
    *plVar6 = 0;
    plVar6[1] = uVar10;
    fVar12 = (float)(*(long *)(param_1 + 0x130) + 1);
    if ((uVar11 == 0) || (*(float *)(param_1 + 0x138) * (float)uVar11 < fVar12)) {
      if (uVar11 < 3) {
        uVar8 = 1;
      }
      else {
        uVar8 = (ulong)((uVar11 - 1 & uVar11) != 0);
      }
      uVar8 = uVar8 | uVar11 << 1;
      uVar11 = (ulong)(fVar12 / *(float *)(param_1 + 0x138));
      if (uVar11 <= uVar8) {
        uVar11 = uVar8;
      }
      std::__ndk1::__hash_table<std::__ndk1::__hash_value_type<unsigned int, CGameResourceDownloader::CDownloadNode*>, std::__ndk1::__unordered_map_hasher<unsigned int, std::__ndk1::__hash_value_type<unsigned int, CGameResourceDownloader::CDownloadNode*>, std::__ndk1::hash<unsigned int>, true>, std::__ndk1::__unordered_map_equal<unsigned int, std::__ndk1::__hash_value_type<unsigned int, CGameResourceDownloader::CDownloadNode*>, std::__ndk1::equal_to<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__hash_value_type<unsigned int, CGameResourceDownloader::CDownloadNode*>, Framework::CSTLUnorderedMapAllocatorInf> >::rehash(unsigned long)(plVar1,uVar11);
      uVar11 = *(ulong *)(param_1 + 0x120);
      if ((uVar11 - 1 & uVar11) == 0) {
        unaff_x19 = (long *)(uVar11 - 1 & uVar10);
      }
      else {
        uVar8 = 0;
        if (uVar11 != 0) {
          uVar8 = uVar10 / uVar11;
        }
        unaff_x19 = (long *)(uVar10 - uVar8 * uVar11);
      }
    }
    plVar7 = *(long **)(*plVar1 + (long)unaff_x19 * 8);
    if (plVar7 == (long *)0x0) {
      *plVar6 = *(long *)(param_1 + 0x128);
      *(long **)(param_1 + 0x128) = plVar6;
      *(long *)(*(long *)(param_1 + 0x118) + (long)unaff_x19 * 8) = param_1 + 0x128;
      if (*plVar6 != 0) {
        uVar10 = *(ulong *)(*plVar6 + 8);
        if ((uVar11 - 1 & uVar11) == 0) {
          uVar10 = uVar10 & uVar11 - 1;
        }
        else {
          uVar8 = 0;
          if (uVar11 != 0) {
            uVar8 = uVar10 / uVar11;
          }
          uVar10 = uVar10 - uVar8 * uVar11;
        }
        plVar7 = (long *)(*plVar1 + uVar10 * 8);
        goto code_r0x018d455c;
      }
    }
    else {
      *plVar6 = *plVar7;
code_r0x018d455c:
      *plVar7 = (long)plVar6;
    }
    *(long *)(param_1 + 0x130) = *(long *)(param_1 + 0x130) + 1;
  }
  else {
    uVar8 = uVar11 - 1;
    if ((uVar8 & uVar11) == 0) {
      unaff_x19 = (long *)(uVar8 & uVar10);
    }
    else {
      uVar2 = 0;
      if (uVar11 != 0) {
        uVar2 = uVar10 / uVar11;
      }
      unaff_x19 = (long *)(uVar10 - uVar2 * uVar11);
    }
    plVar6 = *(long **)(*plVar1 + (long)unaff_x19 * 8);
    if (plVar6 == (long *)0x0) goto code_r0x018d443c;
    if ((uVar8 & uVar11) == 0) {
      do {
        plVar6 = (long *)*plVar6;
        if ((plVar6 == (long *)0x0) || ((long *)(plVar6[1] & uVar8) != unaff_x19))
        goto code_r0x018d443c;
      } while (*(uint *)(plVar6 + 2) != uVar3);
    }
    else {
      do {
        plVar6 = (long *)*plVar6;
        if (plVar6 == (long *)0x0) goto code_r0x018d443c;
        uVar8 = 0;
        if (uVar11 != 0) {
          uVar8 = (ulong)plVar6[1] / uVar11;
        }
        if ((long *)(plVar6[1] - uVar8 * uVar11) != unaff_x19) goto code_r0x018d443c;
      } while (*(uint *)(plVar6 + 2) != uVar3);
    }
  }
  lVar9 = *(long *)(param_1 + 0x58);
  if (-1 < lVar9) {
    Aska::TArray<CGameResourceDownloader::CDownloadNode*, false>::Resize(long, bool)(param_1 + 0x40,lVar9 + 1,0);
    *(long *)(*(long *)(param_1 + 0x48) + lVar9 * 8) = lVar4;
  }
  lVar9 = *(long *)(param_1 + 0x5d8);
  uStack_b8 = 0;
  uStack_b0 = 0;
  uStack_c0 = 0;
  uVar10 = strlen(param_3);
  if (uVar10 < 0x17) {
    uVar8 = (ulong)&uStack_c0 | 1;
    uStack_c0 = CONCAT71(uStack_c0._1_7_,(char)(uVar10 << 1));
    if (uVar10 == 0) goto code_r0x018d4654;
  }
  else {
    uVar11 = uVar10 + 0x10 & 0xfffffffffffffff0;
    if (uVar11 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
    }
    uVar8 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar11,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
    if (uVar8 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    }
    uStack_c0 = uVar11 | 1;
    uStack_b8 = uVar10;
    uStack_b0 = uVar8;
  }
  memcpy(uVar8,param_3,uVar10);
code_r0x018d4654:
  *(undefined1 *)(uVar8 + uVar10) = 0;
  Aska::THashMap<string, CAssetInfo, Hasher_CSTLString, Aska::TEqualTo<string >, Aska::TAllocator<Aska::TPair<string const, CAssetInfo> > >::Find_(string const&) const(alStack_a8,lVar9 + 0x58,&uStack_c0);
  if ((uStack_c0 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_b0);
  }
  CMetaList::CMetaList(CMetaList const&)(&puStack_108,param_6);
  CGameResourceDownloader::CDownloadNode::SetJsonData(CAssetInfo*, unsigned int, char const*, CMetaList)(lVar4,alStack_a8[0] + 0x20,param_5,param_4,&puStack_108);
  puStack_108 = PTR__ZTVN4Aska6TArrayI9CMetaInfoLb0EEE_02cba9a0 + 0x10;
  uStack_d6 = uStack_d6 | 1;
  if (((plStack_100 != (long *)0x0) && (0 < lStack_f0)) &&
     ((**(code **)(*plStack_100 + 0x10))(), 1 < lStack_f0)) {
    lVar4 = 1;
    lVar9 = 0x28;
    do {
      (**(code **)(*(long *)((long)plStack_100 + lVar9) + 0x10))();
      lVar4 = lVar4 + 1;
      lVar9 = lVar9 + 0x28;
    } while (lVar4 < lStack_f0);
  }
  if (((uStack_d6 & 1) != 0) && (plStack_100 != (long *)0x0)) {
    operator delete[](void*)();
  }
  return;
}

// ==== CGameResourceDownloader::RegisterDownloadNode(CGameResourceDownloader::CDownloadNode*)
// vaddr 0x17d4758 | ghidra 0x18d4758 | size 60 | symbol _ZN23CGameResourceDownloader20RegisterDownloadNodeEPNS_13CDownloadNodeE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN23CGameResourceDownloader20RegisterDownloadNodeEPNS_13CDownloadNodeE
               (long param_1,undefined8 param_2)

{
  long lVar1;
  
  lVar1 = *(long *)(param_1 + 0x58);
  if (-1 < lVar1) {
    Aska::TArray<CGameResourceDownloader::CDownloadNode*, false>::Resize(long, bool)(param_1 + 0x40,lVar1 + 1,0);
    *(undefined8 *)(*(long *)(param_1 + 0x48) + lVar1 * 8) = param_2;
  }
  return;
}

// ==== CGameResourceDownloader::CDownloadNode::SetJsonData(CAssetInfo*, unsigned int, char const*, CMetaList)
// vaddr 0x17d4794 | ghidra 0x18d4794 | size 416 | symbol _ZN23CGameResourceDownloader13CDownloadNode11SetJsonDataEP10CAssetInfojPKc9CMetaList | lib libSOA-3.7.0.so | 2026-10-04
void _ZN23CGameResourceDownloader13CDownloadNode11SetJsonDataEP10CAssetInfojPKc9CMetaList
               (long param_1,undefined8 param_2,ulong param_3,undefined8 param_4,long param_5)

{
  ulong *puVar1;
  undefined *puVar2;
  ulong uVar3;
  long *plVar4;
  ulong uVar5;
  ulong uVar6;
  long lVar7;
  long lVar8;
  
  *(undefined8 *)(param_1 + 0x158) = param_2;
  puVar1 = (ulong *)(param_1 + 0x160);
  uVar3 = strlen(param_4);
  uVar6 = (ulong)*(byte *)(param_1 + 0x160);
  if ((*(byte *)(param_1 + 0x160) & 1) == 0) {
    uVar5 = 0x16;
    lVar7 = uVar3 - 0x16;
    if (0x15 < uVar3 && lVar7 != 0) {
code_r0x018d4800:
      if ((uVar6 & 1) == 0) {
        uVar6 = (ulong)(((uint)uVar6 & 0xfe) >> 1);
      }
      else {
        uVar6 = *(ulong *)(param_1 + 0x168);
      }
      string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(puVar1,uVar5,lVar7,uVar6,0,uVar6,uVar3,param_4);
      goto code_r0x018d4864;
    }
  }
  else {
    uVar6 = *puVar1;
    uVar5 = (uVar6 & 0xfffffffffffffffe) - 1;
    lVar7 = uVar3 - uVar5;
    if (uVar5 <= uVar3 && lVar7 != 0) goto code_r0x018d4800;
  }
  if ((uVar6 & 1) == 0) {
    lVar7 = param_1 + 0x161;
  }
  else {
    lVar7 = *(long *)(param_1 + 0x170);
  }
  if (uVar3 != 0) {
    memmove(lVar7,param_4,uVar3);
  }
  *(undefined1 *)(lVar7 + uVar3) = 0;
  if ((*(byte *)puVar1 & 1) == 0) {
    *(byte *)puVar1 = (byte)(uVar3 << 1);
  }
  else {
    *(ulong *)(param_1 + 0x168) = uVar3;
  }
code_r0x018d4864:
  *(ulong *)(param_1 + 0x370) = param_3 & 0xffffffff;
  plVar4 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x48,PTR__ZSt7nothrow_02cb9a80);
  if (plVar4 != (long *)0x0) {
    memset(plVar4,0,0x48);
    *(undefined4 *)(plVar4 + 6) = 0;
    puVar2 = PTR__ZTV9CMetaList_02cbed68;
    plVar4[5] = 8;
    *(undefined1 *)(plVar4 + 8) = 1;
    *plVar4 = (long)(puVar2 + 0x10);
    plVar4[7] = (long)(puVar2 + 0x40);
  }
  *(long **)(param_1 + 0x178) = plVar4;
  if ((0 < *(long *)(param_5 + 0x18)) &&
     (Aska::TArray<CMetaInfo, false>::SetAt(long, CMetaInfo const&)(plVar4,plVar4[3],*(undefined8 *)(param_5 + 8)), 1 < *(long *)(param_5 + 0x18))
     ) {
    lVar7 = 1;
    lVar8 = 0x28;
    do {
      Aska::TArray<CMetaInfo, false>::SetAt(long, CMetaInfo const&)(*(long *)(param_1 + 0x178),*(undefined8 *)(*(long *)(param_1 + 0x178) + 0x18),
                      *(long *)(param_5 + 8) + lVar8);
      lVar7 = lVar7 + 1;
      lVar8 = lVar8 + 0x28;
    } while (lVar7 < *(long *)(param_5 + 0x18));
  }
  *(ulong *)(param_1 + 800) = param_3 & 0xffffffff;
  return;
}

// ==== CGameResourceDownloader::Progress()
// vaddr 0x17d4bc0 | ghidra 0x18d4bc0 | size 332 | symbol _ZN23CGameResourceDownloader8ProgressEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN23CGameResourceDownloader8ProgressEv(long param_1)

{
  long lVar1;
  ulong uVar2;
  long *plVar3;
  undefined8 uVar4;
  undefined8 uStack_28;
  undefined4 uStack_14;
  
  if ((*(int *)PTR__ZN23CGameResourceDownloader15m_ErrorOverSizeE_02cbb7b8 != 0) &&
     (*(int *)(param_1 + 0x14c) != 10)) {
    *(undefined4 *)PTR__ZN23CGameResourceDownloader15m_ErrorOverSizeE_02cbb7b8 = 0;
    *(undefined8 *)(param_1 + 0x160) = 0xfffffffffffffc33;
    *(undefined8 *)(param_1 + 0x14c) = 5;
    if ((*(char *)(param_1 + 0x157) != '\0') &&
       (plVar3 = *(long **)(param_1 + 0x4e0), plVar3 != (long *)0x0)) {
      uStack_28 = 0xfffffffffffffc33;
      uStack_14 = 0xf4241;
      (**(code **)(*plVar3 + 0x30))(plVar3,&uStack_14,&uStack_28);
    }
    return;
  }
  lVar1 = param_1 + 0x170;
  uVar2 = Framework::CMutex::IsInitialized() const(lVar1);
  if ((uVar2 & 1) == 0) {
    Framework::CMutex::Initialize()(lVar1);
  }
  Framework::CMutex::Lock()(lVar1);
  switch(*(undefined4 *)(param_1 + 0x14c)) {
  case 1:
    uVar4 = 2;
    break;
  case 2:
    CGameResourceDownloader::Progress_DeleteEpisodeData()(param_1);
    goto code_r0x011f7f50;
  case 3:
    CGameResourceDownloader::Progress_Setup()(param_1);
    goto code_r0x011f7f50;
  case 4:
    if (*(char *)(param_1 + 0x15c) != '\0') {
      CGameResourceDownloader::Progress_Download()(param_1);
    }
    goto code_r0x011f7f50;
  case 5:
    uVar4 = 0;
    break;
  case 6:
    uVar4 = 3;
    break;
  case 7:
    uVar4 = 8;
    break;
  case 8:
    CGameResourceDownloader::Progress_RemoveDownloadData()(param_1);
    goto code_r0x011f7f50;
  case 9:
    uVar4 = 4;
    break;
  default:
    goto code_r0x011f7f50;
  }
  CGameResourceDownloader::Progress_StopDownload(int)(param_1,uVar4);
code_r0x011f7f50:
  (*(code *)PTR__ZN9Framework6CMutex6UnlockEv_02cb3f98)(lVar1);
  return;
}

// ==== CGameResourceDownloader::PostError(int, Aska::Status)
// vaddr 0x17d4d0c | ghidra 0x18d4d0c | size 100 | symbol _ZN23CGameResourceDownloader9PostErrorEiN4Aska6StatusE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN23CGameResourceDownloader9PostErrorEiN4Aska6StatusE
               (long param_1,undefined4 param_2,long *param_3)

{
  long *plVar1;
  long lVar2;
  long lStack_18;
  undefined4 uStack_4;
  
  lVar2 = *param_3;
  *(undefined8 *)(param_1 + 0x14c) = 5;
  uStack_4 = 0xf4241;
  if (lVar2 != -0x3cd) {
    uStack_4 = param_2;
  }
  if ((*(char *)(param_1 + 0x157) != '\0') &&
     (plVar1 = *(long **)(param_1 + 0x4e0), plVar1 != (long *)0x0)) {
    lStack_18 = *param_3;
    (**(code **)(*plVar1 + 0x30))(plVar1,&uStack_4,&lStack_18);
  }
  return;
}

// ==== CGameResourceDownloader::Progress_StopDownload(int)
// vaddr 0x17d4d70 | ghidra 0x18d4d70 | size 240 | symbol _ZN23CGameResourceDownloader21Progress_StopDownloadEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN23CGameResourceDownloader21Progress_StopDownloadEi(long param_1,undefined4 param_2)

{
  int iVar1;
  long lVar2;
  long lVar3;
  long lVar4;
  undefined1 auStack_18 [8];
  
  iVar1 = *(int *)(param_1 + 0x150);
  if (iVar1 == 2) {
    *(undefined4 *)(param_1 + 0x14c) = param_2;
    *(undefined4 *)(param_1 + 0x150) = 0;
  }
  else {
    if (iVar1 == 1) {
      if (*(int *)(*(long *)(*(long *)PTR__ZN4Aska6Global17m_pNetworkManagerE_02cb9e90 + 0x1a8) +
                  0x670) != 0) {
        return;
      }
      lVar2 = *(long *)(param_1 + 0x58);
      *(undefined8 *)(param_1 + 0x60) = 0;
      if (0 < lVar2) {
        lVar3 = 0;
        do {
          lVar4 = *(long *)(*(long *)(param_1 + 0x48) + lVar3 * 8);
          if (*(int *)(lVar4 + 8) != 5) {
            *(undefined4 *)(lVar4 + 0x180) = 0;
            *(undefined8 *)(lVar4 + 0x188) = 0;
            *(undefined8 *)(lVar4 + 8) = 0;
            lVar2 = *(long *)(param_1 + 0x58);
            lVar3 = *(long *)(param_1 + 0x60);
          }
          lVar3 = lVar3 + 1;
          *(long *)(param_1 + 0x60) = lVar3;
        } while (lVar3 < lVar2);
      }
      *(undefined4 *)(param_1 + 0x268) = 0;
      if ((*(byte *)(param_1 + 0xaa) & 1) != 0) {
        if (*(long *)(param_1 + 0x80) != 0) {
          operator delete[](void*)();
          *(undefined8 *)(param_1 + 0x80) = 0;
        }
        *(undefined8 *)(param_1 + 0x88) = 0;
      }
      iVar1 = *(int *)(param_1 + 0x150);
      *(undefined8 *)(param_1 + 0x90) = 0;
      *(undefined8 *)(param_1 + 0x98) = 0;
    }
    else {
      if (iVar1 != 0) {
        return;
      }
      Aska::Yayoi::Downloader::Stop(unsigned int)(auStack_18,
                      *(undefined8 *)
                       (*(long *)PTR__ZN4Aska6Global17m_pNetworkManagerE_02cb9e90 + 0x1a8),
                      0xffffffff);
      iVar1 = *(int *)(param_1 + 0x150);
    }
    *(int *)(param_1 + 0x150) = iVar1 + 1;
  }
  return;
}

// ==== CGameResourceDownloader::Progress_DeleteEpisodeData()
// vaddr 0x17d4e60 | ghidra 0x18d4e60 | size 5108 | symbol _ZN23CGameResourceDownloader26Progress_DeleteEpisodeDataEv | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Type propagation algorithm not settling */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN23CGameResourceDownloader26Progress_DeleteEpisodeDataEv(long *param_1)

{
  uint uVar1;
  ulong *puVar2;
  undefined *puVar3;
  ulong uVar4;
  ulong uVar5;
  bool bVar6;
  int iVar7;
  long lVar8;
  undefined1 *puVar9;
  undefined *puVar10;
  ulong uVar11;
  ulong uVar12;
  code *pcVar13;
  undefined1 *puVar14;
  uint uVar16;
  long lVar17;
  long *plVar18;
  long lVar19;
  long *plVar20;
  ulong uVar21;
  undefined *puVar22;
  float fVar23;
  float fVar24;
  undefined8 uStack_188;
  undefined *puStack_180;
  undefined *puStack_178;
  ulong uStack_170;
  long lStack_168;
  undefined8 uStack_160;
  undefined1 uStack_158;
  long alStack_f0 [3];
  uint auStack_d8 [2];
  ulong uStack_d0;
  ulong uStack_c8;
  undefined *puStack_c0;
  undefined *puStack_b8;
  ulong uStack_b0;
  undefined *puStack_a0;
  undefined *puStack_98;
  ulong uStack_90;
  undefined8 uStack_80;
  undefined *puStack_78;
  ulong uStack_70;
  undefined1 *puVar15;
  
  switch((int)param_1[0x2a]) {
  case 0:
    *(undefined4 *)(param_1 + 0x28) = 0;
    Aska::ASON::Term()(param_1 + 0x62);
    lVar17 = param_1[0xbb];
    if (lVar17 != 0) {
      puVar2 = (ulong *)(param_1 + 0x47);
      if (puVar2 == (ulong *)(lVar17 + 0x40)) {
code_r0x018d5c84:
        plVar20 = (long *)param_1[0xbb];
      }
      else {
        uVar21 = *(ulong *)(lVar17 + 0x48);
        lVar19 = *(long *)(lVar17 + 0x50);
        uVar12 = (ulong)(byte)*puVar2;
        if ((*(byte *)(lVar17 + 0x40) & 1) == 0) {
          lVar19 = lVar17 + 0x41;
          uVar21 = (ulong)(*(byte *)(lVar17 + 0x40) >> 1);
        }
        if (((byte)*puVar2 & 1) == 0) {
          uVar11 = 0x16;
          lVar17 = uVar21 - 0x16;
          if (uVar21 < 0x16 || lVar17 == 0) goto code_r0x018d4ef4;
        }
        else {
          uVar12 = *puVar2;
          uVar11 = (uVar12 & 0xfffffffffffffffe) - 1;
          lVar17 = uVar21 - uVar11;
          if (uVar21 < uVar11 || lVar17 == 0) {
code_r0x018d4ef4:
            if ((uVar12 & 1) == 0) {
              lVar17 = (long)param_1 + 0x239;
            }
            else {
              lVar17 = param_1[0x49];
            }
            if (uVar21 != 0) {
              memmove(lVar17,lVar19,uVar21);
            }
            *(undefined1 *)(lVar17 + uVar21) = 0;
            if ((*puVar2 & 1) != 0) {
              param_1[0x48] = uVar21;
              goto code_r0x018d5c84;
            }
            *(byte *)puVar2 = (byte)(uVar21 << 1);
            plVar20 = (long *)param_1[0xbb];
            goto joined_r0x018d4f28;
          }
        }
        if ((uVar12 & 1) == 0) {
          uVar12 = (ulong)(((uint)uVar12 & 0xfe) >> 1);
        }
        else {
          uVar12 = param_1[0x48];
        }
        string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(puVar2,uVar11,lVar17,uVar12,0,uVar12,uVar21);
        plVar20 = (long *)param_1[0xbb];
      }
joined_r0x018d4f28:
      if (plVar20 != (long *)0x0) {
        (**(code **)(*plVar20 + 0x18))();
        param_1[0xbb] = 0;
      }
    }
    plVar20 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x98,PTR__ZSt7nothrow_02cb9a80);
    if (plVar20 != (long *)0x0) {
      puVar22 = PTR__ZTV12CVersionInfo_02cbda90 + 0x10;
      *(undefined1 *)(plVar20 + 1) = 1;
      *(undefined4 *)((long)plVar20 + 0xc) = 0x312e31;
      *plVar20 = (long)puVar22;
      memset(plVar20 + 2,0,0x48);
      puVar22 = PTR__ZTVN4Aska8THashMapINSt6__ndk112basic_stringIcNS1_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS5_22CSTLStringAllocatorInfEEEEE10CAssetInfo17Hasher_CSTLStringNS_8TEqualToIS9_EENS_10TAllocatorINS_5TPairIKS9_SA_EEEEEE_02cc2290
                + 0x10;
      *(undefined8 *)((long)plVar20 + 100) = 0x3f400000;
      plVar20[0xb] = (long)puVar22;
      *(undefined4 *)((long)plVar20 + 0x6c) = 0;
      puVar9 = (undefined1 *)Aska::MemoryManagerAdapter::AlignedMalloc(unsigned long, unsigned long)(0xcc0,8);
      lVar17 = 0x11;
      if (puVar9 == (undefined1 *)0x0) {
        lVar17 = 0;
      }
      plVar20[0xf] = (long)puVar9;
      plVar20[0x10] = lVar17;
      if (puVar9 != (undefined1 *)0x0) {
        uVar21 = (lVar17 * 0xc0 - 0xc0U) / 0xc0 + 1;
        puVar15 = puVar9;
        if ((1 < uVar21) && (uVar12 = uVar21 & 0x3fffffffffffffe, uVar12 != 0)) {
          uVar11 = uVar12;
          do {
            *puVar15 = 0;
            puVar15[0xc0] = 0;
            uVar11 = uVar11 - 2;
            puVar15 = puVar15 + 0x180;
          } while (uVar11 != 0);
          puVar15 = puVar9 + uVar12 * 0xc0;
          if (uVar21 == uVar12) goto code_r0x018d5dc4;
        }
        do {
          puVar14 = puVar15 + 0xc0;
          *puVar15 = 0;
          puVar15 = puVar14;
        } while (puVar9 + lVar17 * 0xc0 != puVar14);
      }
code_r0x018d5dc4:
      *(undefined1 *)(plVar20 + 0x12) = 1;
      puVar22 = PTR__ZTV10CAssetList_02cba9a8 + 0x38;
      plVar20[0xb] = (long)(PTR__ZTV10CAssetList_02cba9a8 + 0x10);
      plVar20[0x11] = (long)puVar22;
    }
    param_1[0xbb] = (long)plVar20;
    lVar17 = Aska::ASON::Init(unsigned int, bool)(param_1 + 0x50,"meterEPv",1);
    if (lVar17 != 0) {
      *(undefined8 *)((long)param_1 + 0x14c) = 5;
      if (*(char *)((long)param_1 + 0x157) == '\0') {
        return;
      }
      plVar20 = (long *)param_1[0x9c];
      if (plVar20 == (long *)0x0) {
        return;
      }
      puStack_180 = (undefined *)0xfffffffffffffc15;
      uStack_80 = (undefined *)CONCAT44(uStack_80._4_4_,1000000);
      (**(code **)(*plVar20 + 0x30))(plVar20,&uStack_80,&puStack_180);
      return;
    }
    BAS::GetDownloadPath()(&puStack_180);
    if (((ulong)puStack_180 & 1) == 0) {
      puVar10 = (undefined *)0x16;
      puVar22 = (undefined *)((ulong)puStack_180 & 0xff);
    }
    else {
      puVar10 = (undefined *)(((ulong)puStack_180 & 0xfffffffffffffffe) - 1);
      puVar22 = puStack_180;
    }
    puVar3 = (undefined *)(ulong)(((uint)puVar22 & 0xfe) >> 1);
    if (((ulong)puVar22 & 1) != 0) {
      puVar3 = puStack_178;
    }
    if (puVar10 == puVar3) {
      string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&puStack_180,puVar10,1,puVar10,puVar10,0,1,&UNK_029c5d3e/*"/"*/);
    }
    else {
      uVar21 = (ulong)&puStack_180 | 1;
      if (((ulong)puVar22 & 1) != 0) {
        uVar21 = uStack_170;
      }
      puVar3[uVar21] = 0x2f;
      puVar3 = puVar3 + 1;
      puVar22 = puVar3;
      if (((ulong)puStack_180 & 1) == 0) {
        puStack_180 = (undefined *)CONCAT71(puStack_180._1_7_,(char)puVar3 * '\x02');
        puVar22 = puStack_178;
      }
      puStack_178 = puVar22;
      puVar3[uVar21] = 0;
    }
    uStack_70 = uStack_170;
    puStack_78 = puStack_178;
    uStack_80 = puStack_180;
    string std::__ndk1::operator+<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> >(string const&, char const*)(&puStack_a0,&uStack_80,&UNK_02866dd0/*"version.bin"*/);
    if (((ulong)puStack_a0 & 1) == 0) {
      uVar21 = (ulong)&puStack_a0 | 1;
code_r0x018d5f28:
      iVar7 = access(uVar21,0);
      if (iVar7 == 0) {
        uVar21 = (ulong)&puStack_a0 | 1;
        if (((ulong)puStack_a0 & 1) != 0) {
          uVar21 = uStack_90;
        }
        lVar19 = Aska::FileReadManager::CalcFileLength(char const*, bool)(uVar21,0);
        lVar17 = 0;
        if (lVar19 != 0) {
          lVar17 = operator new[](unsigned long, std::nothrow_t const&)(lVar19,PTR__ZSt7nothrow_02cb9a80);
          param_1[0x91] = lVar17;
          puVar22 = PTR__ZTVN4Aska10FileStreamE_02cbc9f8 + 0x10;
          puVar10 = PTR__ZTVN4Aska4FileE_02cb6e28 + 0x10;
          uVar21 = (ulong)&puStack_a0 | 1;
          if (((ulong)puStack_a0 & 1) != 0) {
            uVar21 = uStack_90;
          }
          uStack_170 = uStack_170 & 0xffffffffffffff00;
          uStack_158 = 0;
          lStack_168 = 0;
          uStack_160 = 0;
          puStack_180 = puVar22;
          puStack_178 = puVar10;
          uVar21 = Aska::FileStream::Open(char const*, bool, bool, Aska::Machine::Endian)(&puStack_180,uVar21,0,0,3);
          if ((uVar21 & 1) != 0) {
            Aska::FileStream::Read(void*, unsigned long, unsigned long)(&puStack_180,param_1[0x91],lVar19,1);
            Aska::FileStream::Close()(&puStack_180);
            Aska::ASON::DeserializeBinary(void const*, unsigned long)(param_1 + 0x50,param_1[0x91],lVar19);
            if (param_1[0x60] < 0) {
              param_1[0x2c] = -0x3a7;
              *(undefined8 *)((long)param_1 + 0x14c) = 5;
              if ((*(char *)((long)param_1 + 0x157) != '\0') &&
                 (plVar20 = (long *)param_1[0x9c], plVar20 != (long *)0x0)) {
                puStack_c0 = (undefined *)0xfffffffffffffc59;
                auStack_d8[0] = 1000000;
                (**(code **)(*plVar20 + 0x30))(plVar20,auStack_d8,&puStack_c0);
              }
            }
          }
          lVar17 = Aska::ASON::AValue::AMap::Get_(char const*)(param_1 + 0x5d,&UNK_02866dc9/*"assets"*/);
          lVar17 = lVar17 + 8;
          puStack_180 = puVar22;
          Aska::FileStream::Close()(&puStack_180);
          puStack_178 = puVar10;
          if (lStack_168 != 0) {
            Aska::File::Close()((ulong)&puStack_180 | 8);
          }
        }
        goto joined_r0x018d60a8;
      }
      lVar17 = 0;
      if (((ulong)puStack_a0 & 1) != 0) goto code_r0x018d5f40;
    }
    else {
      uVar21 = uStack_90;
      if (uStack_90 != 0) goto code_r0x018d5f28;
      lVar17 = 0;
joined_r0x018d60a8:
      if (((byte)puStack_a0 & 1) != 0) {
code_r0x018d5f40:
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_90);
      }
    }
    if (((ulong)uStack_80 & 1) != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_70);
    }
    if ((lVar17 == 0) || (uVar16 = *(uint *)(lVar17 + 8), uVar16 == 0)) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02866a48/*"C:\BAS_Submission\Client\Project\..\Source\Game\Resource\GameResourceDownloader.cpp"*/,0x844,&UNK_02866aaa);
      return;
    }
    lVar19 = param_1[0xbb];
    fVar23 = (float)NEON_ucvtf(*(undefined4 *)(lVar19 + 0x68));
    uVar21 = (ulong)(fVar23 / *(float *)(lVar19 + 100));
    if (uVar21 <= uVar16) {
      uVar21 = (ulong)uVar16;
    }
    Aska::THashMap<string, CAssetInfo, Hasher_CSTLString, Aska::TEqualTo<string >, Aska::TAllocator<Aska::TPair<string const, CAssetInfo> > >::Rehash_(unsigned long)(lVar19 + 0x58,uVar21);
    if ((long *)param_1[0xb2] != (long *)0x0) {
      (**(code **)(*(long *)param_1[0xb2] + 0x10))();
      param_1[0xb2] = 0;
    }
    plVar20 = (long *)operator new(unsigned long, std::nothrow_t const&)(200,PTR__ZSt7nothrow_02cb9a80);
    if (plVar20 != (long *)0x0) {
      *plVar20 = (long)(PTR__ZTVN23CGameResourceDownloader11CVerifyTaskE_02cbe2d8 + 0x10);
      plVar20[1] = 0;
      memset(plVar20 + 2,0,99);
      *(undefined4 *)((long)plVar20 + 0x8c) = 0;
      *(undefined8 *)((long)plVar20 + 0x74) = 0;
      plVar20[0x17] = 0;
      *(undefined8 *)((long)plVar20 + 0x84) = 0;
      *(undefined8 *)((long)plVar20 + 0x7c) = 0;
      plVar20[0x16] = 0;
      plVar20[0x15] = 0;
      plVar20[0x14] = 0;
      plVar20[0x13] = 0;
      *(undefined4 *)(plVar20 + 0x18) = 0x3f800000;
    }
    param_1[0xb2] = (long)plVar20;
    lVar19 = plVar20[8];
    lVar8 = param_1[0xbb];
    plVar20[4] = 0;
    plVar20[5] = lVar17;
    plVar20[6] = 0;
    *(undefined1 *)((long)plVar20 + 0x72) = 0;
    *(undefined4 *)((long)plVar20 + 0x74) = 0;
    plVar20[2] = (long)param_1;
    plVar20[3] = lVar8;
    plVar20[10] = 0;
    *(undefined2 *)(plVar20 + 0xe) = 0;
    if (lVar19 != plVar20[7]) {
      plVar20[8] = lVar19 + (~((lVar19 + -8) - plVar20[7]) & 0xfffffffffffffff8U);
    }
    std::__ndk1::__hash_table<std::__ndk1::__hash_value_type<unsigned int, bool>, std::__ndk1::__unordered_map_hasher<unsigned int, std::__ndk1::__hash_value_type<unsigned int, bool>, std::__ndk1::hash<unsigned int>, true>, std::__ndk1::__unordered_map_equal<unsigned int, std::__ndk1::__hash_value_type<unsigned int, bool>, std::__ndk1::equal_to<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__hash_value_type<unsigned int, bool>, Framework::CSTLUnorderedMapAllocatorInf> >::rehash(unsigned long)(plVar20 + 0x14,*(undefined4 *)(lVar17 + 8));
    iVar7 = 1;
    plVar20[1] = 0;
    goto code_r0x018d6230;
  case 1:
    lVar17 = param_1[0xb2];
    if (lVar17 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02866a48/*"C:\BAS_Submission\Client\Project\..\Source\Game\Resource\GameResourceDownloader.cpp"*/,0x84b,&UNK_02866aee/*"m_pVerifyTask is null."*/);
      lVar17 = param_1[0xb2];
    }
    switch(*(undefined4 *)(lVar17 + 8)) {
    case 0:
      CGameResourceDownloader::CVerifyTask::ProgressLocalFileCheck()();
      break;
    case 1:
      CGameResourceDownloader::CVerifyTask::ProgressServerManifestCheck()();
      break;
    case 2:
      CGameResourceDownloader::CVerifyTask::ProgressEraseCheck()();
      break;
    case 3:
      CGameResourceDownloader::CVerifyTask::ProgressEraseEpisodeDataCheck()();
      break;
    case 4:
      CGameResourceDownloader::CVerifyTask::ProgressSetupManifest()();
    }
    lVar17 = param_1[0xb2];
    iVar7 = *(int *)(lVar17 + 8);
    if (iVar7 == 1) {
      fVar24 = 6.0;
      fVar23 = (float)NEON_ucvtf(*(undefined4 *)(lVar17 + 0xc));
code_r0x018d61fc:
      fVar23 = fVar23 / fVar24;
    }
    else {
      fVar23 = 0.0;
      if (iVar7 == 2) {
        plVar20 = *(long **)(lVar17 + 0x98);
        if (plVar20 != (long *)0x0) {
          uVar21 = (ulong)(plVar20[1] - *plVar20) >> 8;
          uVar16 = (uint)((ulong)(plVar20[1] - *plVar20) >> 8);
joined_r0x018d5c6c:
          if (uVar16 != 0) {
            fVar23 = (float)*(uint *)(lVar17 + 0x74);
            fVar24 = (float)(uVar21 & 0xffffffff);
            goto code_r0x018d61fc;
          }
        }
      }
      else if (iVar7 == 0) {
        if (*(char *)(lVar17 + 0x70) == '\0') {
          lVar19 = *(long *)(lVar17 + 0x28);
        }
        else {
          lVar19 = *(long *)(lVar17 + 0x30);
        }
        if (lVar19 != 0) {
          uVar16 = *(uint *)(lVar19 + 8);
          uVar21 = (ulong)uVar16;
          goto joined_r0x018d5c6c;
        }
      }
    }
    *(float *)(param_1 + 0x28) = fVar23 * _UNK_027e5198 + 0.0;
    if (*(char *)(lVar17 + 0x71) == '\0') {
      return;
    }
    goto code_r0x018d6220;
  case 2:
    if (param_1[0xb7] != 0) {
      uVar21 = 0;
      uVar12 = 1;
      do {
        BAS::GetDownloadPath()(&puStack_180);
        if (((ulong)puStack_180 & 1) == 0) {
          puVar10 = (undefined *)0x16;
          puVar22 = (undefined *)((ulong)puStack_180 & 0xff);
        }
        else {
          puVar10 = (undefined *)(((ulong)puStack_180 & 0xfffffffffffffffe) - 1);
          puVar22 = puStack_180;
        }
        puVar3 = (undefined *)(ulong)(((uint)puVar22 & 0xfe) >> 1);
        if (((ulong)puVar22 & 1) != 0) {
          puVar3 = puStack_178;
        }
        if (puVar10 == puVar3) {
          string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&puStack_180,puVar10,1,puVar10,puVar10,0,1,&UNK_029c5d3e/*"/"*/);
        }
        else {
          uVar11 = (ulong)&puStack_180 | 1;
          if (((ulong)puVar22 & 1) != 0) {
            uVar11 = uStack_170;
          }
          puVar3[uVar11] = 0x2f;
          puVar3 = puVar3 + 1;
          puVar22 = puVar3;
          if (((ulong)puStack_180 & 1) == 0) {
            puStack_180 = (undefined *)CONCAT71(puStack_180._1_7_,(char)puVar3 * '\x02');
            puVar22 = puStack_178;
          }
          puStack_178 = puVar22;
          puVar3[uVar11] = 0;
        }
        uStack_90 = uStack_170;
        puStack_98 = puStack_178;
        puStack_a0 = puStack_180;
        CGameResourceDownloader::CheckLocalResourceFileToolVersionOld()+0x354(&puStack_c0);
        puVar22 = (undefined *)((ulong)puStack_c0 >> 1 & 0x7f);
        uVar11 = (ulong)&puStack_c0 | 1;
        if (((ulong)puStack_c0 & 1) != 0) {
          puVar22 = puStack_b8;
          uVar11 = uStack_b0;
        }
        if (((ulong)puStack_a0 & 1) == 0) {
          lVar17 = 0x16;
          puVar10 = (undefined *)((ulong)puStack_a0 & 0xff);
        }
        else {
          lVar17 = ((ulong)puStack_a0 & 0xfffffffffffffffe) - 1;
          puVar10 = puStack_a0;
        }
        puVar3 = (undefined *)(ulong)(((uint)puVar10 & 0xfe) >> 1);
        if (((ulong)puVar10 & 1) != 0) {
          puVar3 = puStack_98;
        }
        if ((ulong)(lVar17 - (long)puVar3) < puVar22) {
          string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&puStack_a0,lVar17,puVar3 + ((long)puVar22 - lVar17),puVar3,puVar3,0,
                          puVar22);
        }
        else if (puVar22 != (undefined *)0x0) {
          uVar4 = (ulong)&puStack_a0 | 1;
          if (((ulong)puVar10 & 1) != 0) {
            uVar4 = uStack_90;
          }
          memcpy(puVar3 + uVar4,uVar11,puVar22);
          puVar3 = puVar3 + (long)puVar22;
          puVar22 = puVar3;
          if (((ulong)puStack_a0 & 1) == 0) {
            puStack_a0 = (undefined *)CONCAT71(puStack_a0._1_7_,(char)puVar3 * '\x02');
            puVar22 = puStack_98;
          }
          puStack_98 = puVar22;
          puVar3[uVar4] = 0;
        }
        puStack_78 = puStack_98;
        uStack_70 = uStack_90;
        puStack_98 = (undefined *)0x0;
        uStack_90 = 0;
        uStack_80 = puStack_a0;
        puStack_a0 = (undefined *)0x0;
        Framework::CSTLStringUtility_Base<string >::Format(char const*, ...)(auStack_d8,&UNK_02866b05/*"version_latest_ep%d.bin"*/,uVar12);
        uVar11 = (ulong)((byte)auStack_d8[0] >> 1);
        uVar4 = (ulong)auStack_d8 | 1;
        if ((auStack_d8[0] & 1) != 0) {
          uVar11 = uStack_d0;
          uVar4 = uStack_c8;
        }
        if (((ulong)uStack_80 & 1) == 0) {
          lVar17 = 0x16;
          puVar22 = (undefined *)((ulong)uStack_80 & 0xff);
        }
        else {
          lVar17 = ((ulong)uStack_80 & 0xfffffffffffffffe) - 1;
          puVar22 = uStack_80;
        }
        puVar10 = (undefined *)(ulong)(((uint)puVar22 & 0xfe) >> 1);
        if (((ulong)puVar22 & 1) != 0) {
          puVar10 = puStack_78;
        }
        if ((ulong)(lVar17 - (long)puVar10) < uVar11) {
          string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&uStack_80,lVar17,puVar10 + (uVar11 - lVar17),puVar10,puVar10,0,uVar11);
        }
        else if (uVar11 != 0) {
          uVar5 = (ulong)&uStack_80 | 1;
          if (((ulong)puVar22 & 1) != 0) {
            uVar5 = uStack_70;
          }
          memcpy(puVar10 + uVar5,uVar4,uVar11);
          puVar10 = puVar10 + uVar11;
          puVar22 = puVar10;
          if (((ulong)uStack_80 & 1) == 0) {
            uStack_80 = (undefined *)CONCAT71(uStack_80._1_7_,(char)puVar10 * '\x02');
            puVar22 = puStack_78;
          }
          puStack_78 = puVar22;
          puVar10[uVar5] = 0;
        }
        uStack_170 = uStack_70;
        puStack_178 = puStack_78;
        puStack_180 = uStack_80;
        uStack_80 = (undefined *)0x0;
        puStack_78 = (undefined *)0x0;
        uStack_70 = 0;
        if (((auStack_d8[0] & 1) != 0) && (Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_c8), ((ulong)uStack_80 & 1) != 0))
        {
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_70);
        }
        if (((ulong)puStack_c0 & 1) != 0) {
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_b0);
        }
        if (((ulong)puStack_a0 & 1) != 0) {
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_90);
        }
        if ((ulong)param_1[0xb7] <= uVar21) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dc536/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Vector.h"*/,0x58,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,uVar21);
        }
        if ((*(ulong *)(param_1[0xb6] + (uVar21 >> 3 & 0x1ffffffffffffff8)) & 1L << (uVar21 & 0x3f))
            != 0) {
          CGameResourceDownloader::LoadVersionFileToAsonEpisodeData(string const&)(param_1,&puStack_180);
        }
        if (((ulong)puStack_180 & 1) != 0) {
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_170);
        }
        bVar6 = uVar12 < (ulong)param_1[0xb7];
        uVar21 = uVar12;
        uVar12 = (ulong)((int)uVar12 + 1);
      } while (bVar6);
    }
    if ((long *)param_1[0xb2] != (long *)0x0) {
      (**(code **)(*(long *)param_1[0xb2] + 0x10))();
      param_1[0xb2] = 0;
    }
    plVar20 = (long *)operator new(unsigned long, std::nothrow_t const&)(200,PTR__ZSt7nothrow_02cb9a80);
    if (plVar20 != (long *)0x0) {
      *plVar20 = (long)(PTR__ZTVN23CGameResourceDownloader11CVerifyTaskE_02cbe2d8 + 0x10);
      plVar20[1] = 0;
      memset(plVar20 + 2,0,99);
      *(undefined4 *)((long)plVar20 + 0x8c) = 0;
      *(undefined8 *)((long)plVar20 + 0x74) = 0;
      plVar20[0x17] = 0;
      *(undefined8 *)((long)plVar20 + 0x84) = 0;
      *(undefined8 *)((long)plVar20 + 0x7c) = 0;
      plVar20[0x16] = 0;
      plVar20[0x15] = 0;
      plVar20[0x14] = 0;
      plVar20[0x13] = 0;
      *(undefined4 *)(plVar20 + 0x18) = 0x3f800000;
    }
    param_1[0xb2] = (long)plVar20;
    lVar17 = plVar20[8];
    lVar19 = param_1[0xbb];
    *(undefined1 *)((long)plVar20 + 0x72) = 0;
    *(undefined4 *)((long)plVar20 + 0x74) = 0;
    plVar20[10] = 0;
    *(undefined2 *)(plVar20 + 0xe) = 0;
    plVar20[5] = 0;
    plVar20[6] = 0;
    plVar20[2] = (long)param_1;
    plVar20[3] = lVar19;
    plVar20[4] = 0;
    if (lVar17 != plVar20[7]) {
      plVar20[8] = lVar17 + (~((lVar17 + -8) - plVar20[7]) & 0xfffffffffffffff8U);
    }
    plVar20[1] = 3;
    lVar19 = param_1[0x87];
    lVar17 = param_1[0x86];
    if (lVar19 != lVar17) {
      puVar22 = (undefined *)0x0;
      uVar21 = 0;
      uVar12 = 1;
      do {
        uVar11 = (lVar19 - lVar17 >> 4) * -0x71c71c71c71c71c7;
        if (uVar11 < uVar21 || uVar11 - uVar21 == 0) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dc536/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Vector.h"*/,0x58,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,uVar21);
          lVar17 = param_1[0x86];
        }
        lVar17 = Aska::ASON::AValue::AMap::Get_(char const*)(lVar17 + uVar21 * 0x90 + 0x68,&UNK_02866dc9/*"assets"*/);
        lVar19 = param_1[0xb2];
        if (lVar17 != 0) {
          puVar22 = (undefined *)(lVar17 + 8);
        }
        puStack_180 = puVar22;
        if ((*(uint *)(lVar19 + 8) | 2) == 3) {
          plVar20 = *(long **)(lVar19 + 0x40);
          if (plVar20 == *(long **)(lVar19 + 0x48)) {
            void std::__ndk1::vector<Aska::ASON::AValue::AMap const*, Framework::CSTLAllocator<Aska::ASON::AValue::AMap const*, Framework::CSTLVectorAllocatorInf> >::__push_back_slow_path<Aska::ASON::AValue::AMap const* const&>(Aska::ASON::AValue::AMap const* const&)(lVar19 + 0x38,&puStack_180);
          }
          else {
            if (plVar20 == (long *)0x0) {
              Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
            }
            *plVar20 = (long)puVar22;
            *(long *)(lVar19 + 0x40) = *(long *)(lVar19 + 0x40) + 8;
          }
        }
        lVar19 = param_1[0x87];
        lVar17 = param_1[0x86];
        uVar21 = (lVar19 - lVar17 >> 4) * -0x71c71c71c71c71c7;
        bVar6 = uVar12 <= uVar21;
        lVar8 = uVar21 - uVar12;
        uVar21 = uVar12;
        uVar12 = (ulong)((int)uVar12 + 1);
      } while (bVar6 && lVar8 != 0);
    }
code_r0x018d6220:
    iVar7 = (int)param_1[0x2a];
    *(undefined4 *)(param_1 + 0x28) = 0x42c80000;
code_r0x018d622c:
    iVar7 = iVar7 + 1;
code_r0x018d6230:
    *(int *)(param_1 + 0x2a) = iVar7;
    break;
  case 3:
    lVar17 = param_1[0xb2];
    if (lVar17 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02866a48/*"C:\BAS_Submission\Client\Project\..\Source\Game\Resource\GameResourceDownloader.cpp"*/,0x886,&UNK_02866aee/*"m_pVerifyTask is null."*/);
      lVar17 = param_1[0xb2];
    }
    switch(*(undefined4 *)(lVar17 + 8)) {
    case 0:
      CGameResourceDownloader::CVerifyTask::ProgressLocalFileCheck()();
      break;
    case 1:
      CGameResourceDownloader::CVerifyTask::ProgressServerManifestCheck()();
      break;
    case 2:
      CGameResourceDownloader::CVerifyTask::ProgressEraseCheck()();
      break;
    case 3:
      CGameResourceDownloader::CVerifyTask::ProgressEraseEpisodeDataCheck()();
      break;
    case 4:
      CGameResourceDownloader::CVerifyTask::ProgressSetupManifest()();
    }
    *(undefined4 *)(param_1 + 0x28) = 0x42c80000;
    if (*(char *)(param_1[0xb2] + 0x71) == '\0') {
      return;
    }
    goto code_r0x018d5c50;
  case 4:
    *(undefined1 *)(param_1 + 0x2b) = 0;
    plVar20 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x50,PTR__ZSt7nothrow_02cb9a80);
    if (plVar20 != (long *)0x0) {
      lVar17 = param_1[0xbb];
      Framework::CFiberUnit::CFiberUnit(unsigned int)(plVar20,0x600);
      puVar22 = PTR__ZTVN23CGameResourceDownloader16CEraseCheckFiberE_02cb6f20;
      plVar20[7] = (long)param_1;
      plVar20[8] = lVar17;
      plVar20[9] = 0;
      *plVar20 = (long)(puVar22 + 0x10);
    }
    (**(code **)(*param_1 + 0x48))(param_1,plVar20);
    BAS::GetDownloadPath()(&puStack_180);
    uVar21 = (ulong)&puStack_180 | 1;
    if (((ulong)puStack_180 & 1) != 0) {
      uVar21 = uStack_170;
    }
    BAS::SetNoBackupFolder(char const*)(uVar21);
    *(int *)(param_1 + 0x2a) = (int)param_1[0x2a] + 1;
    if (((byte)puStack_180 & 1) != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_170);
    }
    break;
  case 5:
    if ((char)param_1[0x2b] == '\0') {
      return;
    }
    if (param_1[0xbb] != 0) {
      CGameResourceDownloader::SerializeLocalVersionJson(bool)(param_1,0);
    }
    if ((int)param_1[0x4f] != 0) {
      uVar16 = 0;
      do {
        BAS::GetDownloadPath()(&puStack_180);
        if (((ulong)puStack_180 & 1) == 0) {
          puVar10 = (undefined *)0x16;
          puVar22 = (undefined *)((ulong)puStack_180 & 0xff);
        }
        else {
          puVar10 = (undefined *)(((ulong)puStack_180 & 0xfffffffffffffffe) - 1);
          puVar22 = puStack_180;
        }
        puVar3 = (undefined *)(ulong)(((uint)puVar22 & 0xfe) >> 1);
        if (((ulong)puVar22 & 1) != 0) {
          puVar3 = puStack_178;
        }
        if (puVar10 == puVar3) {
          string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&puStack_180,puVar10,1,puVar10,puVar10,0,1,&UNK_029c5d3e/*"/"*/);
        }
        else {
          uVar21 = (ulong)&puStack_180 | 1;
          if (((ulong)puVar22 & 1) != 0) {
            uVar21 = uStack_170;
          }
          puVar3[uVar21] = 0x2f;
          puVar3 = puVar3 + 1;
          puVar22 = puVar3;
          if (((ulong)puStack_180 & 1) == 0) {
            puStack_180 = (undefined *)CONCAT71(puStack_180._1_7_,(char)puVar3 * '\x02');
            puVar22 = puStack_178;
          }
          puStack_178 = puVar22;
          puVar3[uVar21] = 0;
        }
        uStack_b0 = uStack_170;
        puStack_b8 = puStack_178;
        puStack_c0 = puStack_180;
        CGameResourceDownloader::CheckLocalResourceFileToolVersionOld()+0x354(&puStack_180);
        puVar22 = (undefined *)((ulong)puStack_180 >> 1 & 0x7f);
        uVar21 = (ulong)&puStack_180 | 1;
        if (((ulong)puStack_180 & 1) != 0) {
          puVar22 = puStack_178;
          uVar21 = uStack_170;
        }
        if (((ulong)puStack_c0 & 1) == 0) {
          lVar17 = 0x16;
          puVar10 = (undefined *)((ulong)puStack_c0 & 0xff);
        }
        else {
          lVar17 = ((ulong)puStack_c0 & 0xfffffffffffffffe) - 1;
          puVar10 = puStack_c0;
        }
        puVar3 = (undefined *)(ulong)(((uint)puVar10 & 0xfe) >> 1);
        if (((ulong)puVar10 & 1) != 0) {
          puVar3 = puStack_b8;
        }
        if ((undefined *)(lVar17 - (long)puVar3) < puVar22) {
          string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&puStack_c0,lVar17,puVar3 + ((long)puVar22 - lVar17),puVar3,puVar3,0,
                          puVar22);
        }
        else if (puVar22 != (undefined *)0x0) {
          uVar12 = (ulong)&puStack_c0 | 1;
          if (((ulong)puVar10 & 1) != 0) {
            uVar12 = uStack_b0;
          }
          memcpy(puVar3 + uVar12,uVar21,puVar22);
          puVar3 = puVar3 + (long)puVar22;
          puVar22 = puVar3;
          if (((ulong)puStack_c0 & 1) == 0) {
            puStack_c0 = (undefined *)CONCAT71(puStack_c0._1_7_,(char)puVar3 * '\x02');
            puVar22 = puStack_b8;
          }
          puStack_b8 = puVar22;
          puVar3[uVar12] = 0;
        }
        puStack_98 = puStack_b8;
        puStack_a0 = puStack_c0;
        uVar1 = uVar16 + 1;
        uStack_90 = uStack_b0;
        puStack_b8 = (undefined *)0x0;
        uStack_b0 = 0;
        puStack_c0 = (undefined *)0x0;
        Framework::CSTLStringUtility_Base<string >::Format(char const*, ...)(auStack_d8,&UNK_02866b05/*"version_latest_ep%d.bin"*/,uVar1);
        uVar21 = (ulong)((byte)auStack_d8[0] >> 1);
        uVar12 = (ulong)auStack_d8 | 1;
        if ((auStack_d8[0] & 1) != 0) {
          uVar21 = uStack_d0;
          uVar12 = uStack_c8;
        }
        if (((ulong)puStack_a0 & 1) == 0) {
          lVar17 = 0x16;
          puVar22 = (undefined *)((ulong)puStack_a0 & 0xff);
        }
        else {
          lVar17 = ((ulong)puStack_a0 & 0xfffffffffffffffe) - 1;
          puVar22 = puStack_a0;
        }
        puVar10 = (undefined *)(ulong)(((uint)puVar22 & 0xfe) >> 1);
        if (((ulong)puVar22 & 1) != 0) {
          puVar10 = puStack_98;
        }
        if ((ulong)(lVar17 - (long)puVar10) < uVar21) {
          string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&puStack_a0,lVar17,puVar10 + (uVar21 - lVar17),puVar10,puVar10,0,uVar21);
        }
        else if (uVar21 != 0) {
          uVar11 = (ulong)&puStack_a0 | 1;
          if (((ulong)puVar22 & 1) != 0) {
            uVar11 = uStack_90;
          }
          memcpy(puVar10 + uVar11,uVar12,uVar21);
          puVar10 = puVar10 + uVar21;
          puVar22 = puVar10;
          if (((ulong)puStack_a0 & 1) == 0) {
            puStack_a0 = (undefined *)CONCAT71(puStack_a0._1_7_,(char)puVar10 * '\x02');
            puVar22 = puStack_98;
          }
          puStack_98 = puVar22;
          puVar10[uVar11] = 0;
        }
        uStack_70 = uStack_90;
        puStack_78 = puStack_98;
        uStack_80 = puStack_a0;
        puStack_a0 = (undefined *)0x0;
        puStack_98 = (undefined *)0x0;
        uStack_90 = 0;
        if (((auStack_d8[0] & 1) != 0) && (Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_c8), ((ulong)puStack_a0 & 1) != 0)
           ) {
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_90);
        }
        if (((ulong)puStack_180 & 1) != 0) {
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_170);
        }
        if (((ulong)puStack_c0 & 1) != 0) {
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_b0);
        }
        uVar21 = (ulong)&uStack_80 | 1;
        if (((((ulong)uStack_80 & 1) == 0) || (uVar21 = uStack_70, uStack_70 != 0)) &&
           (iVar7 = access(uVar21,0), iVar7 == 0)) {
          uVar21 = (ulong)uVar16;
          if ((ulong)param_1[0xb7] <= uVar21) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dc536/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Vector.h"*/,0x58,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,uVar21);
          }
          if ((*(ulong *)(param_1[0xb6] + ((ulong)(uVar16 >> 3) & 0x1ffffff8)) &
              1L << (uVar21 & 0x3f)) != 0) {
            uVar21 = (ulong)&uStack_80 | 1;
            if (((ulong)uStack_80 & 1) != 0) {
              uVar21 = uStack_70;
            }
            Aska::File::DeleteFile(char const*)(uVar21);
          }
        }
        if (((ulong)uStack_80 & 1) != 0) {
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_70);
        }
        uVar16 = uVar1;
      } while (uVar1 < *(uint *)(param_1 + 0x4f));
    }
    lVar17 = param_1[0xba];
    alStack_f0[1] = 0;
    alStack_f0[2] = 0;
    alStack_f0[0] = 0;
    if (param_1[0xb7] != 0) {
      lVar19 = (param_1[0xb7] - 1U >> 6) + 1;
      lVar8 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(lVar19 * 8,&UNK_027dc536/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Vector.h"*/,0x20);
      if (lVar8 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
      }
      alStack_f0[1] = 0;
      alStack_f0[0] = lVar8;
      alStack_f0[2] = lVar19;
      std::__ndk1::enable_if<__is_forward_iterator<std::__ndk1::__bit_iterator<std::__ndk1::vector<bool, Framework::CSTLAllocator<bool, Framework::CSTLVectorAllocatorInf> >, true, 0ul> >::value, void>::type std::__ndk1::vector<bool, Framework::CSTLAllocator<bool, Framework::CSTLVectorAllocatorInf> >::__construct_at_end<std::__ndk1::__bit_iterator<std::__ndk1::vector<bool, Framework::CSTLAllocator<bool, Framework::CSTLVectorAllocatorInf> >, true, 0ul> >(std::__ndk1::__bit_iterator<std::__ndk1::vector<bool, Framework::CSTLAllocator<bool, Framework::CSTLVectorAllocatorInf> >, true, 0ul>, std::__ndk1::__bit_iterator<std::__ndk1::vector<bool, Framework::CSTLAllocator<bool, Framework::CSTLVectorAllocatorInf> >, true, 0ul>)(alStack_f0,param_1[0xb6],0,
                      param_1[0xb6] + ((ulong)param_1[0xb7] >> 3 & 0x1ffffffffffffff8),
                      param_1[0xb7] & 0x3f);
    }
    CParameterUI::tEpisodeData::UpdateEpisodeDataState(Framework::CSTLVector<bool>, bool)(lVar17,alStack_f0,0);
    if (alStack_f0[0] != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)();
    }
code_r0x018d5c50:
    iVar7 = (int)param_1[0x2a];
    goto code_r0x018d622c;
  case 6:
    *(undefined4 *)(param_1 + 0x28) = 0x42c80000;
    Aska::ASON::Term()(param_1 + 0x50);
    Aska::ASON::Term()(param_1 + 0x62);
    Aska::ASON::Term()(param_1 + 0x74);
    lVar19 = param_1[0x87];
    lVar17 = param_1[0x86];
    if ((lVar19 != lVar17) && (lVar17 != lVar19)) {
      do {
        Aska::ASON::ASON(Aska::ASON const&)(&puStack_180,lVar17);
        Aska::ASON::Term()(&puStack_180);
        Aska::ASON::~ASON()(&puStack_180);
        lVar17 = lVar17 + 0x90;
      } while (lVar19 != lVar17);
      lVar17 = param_1[0x86];
      while (lVar19 = param_1[0x87], lVar19 != lVar17) {
        param_1[0x87] = lVar19 + -0x90;
        (*(code *)**(undefined8 **)(lVar19 + -0x90))();
      }
    }
    if (param_1[0x91] != 0) {
      operator delete[](void*)();
      param_1[0x91] = 0;
    }
    if (param_1[0x92] != 0) {
      operator delete[](void*)();
      param_1[0x92] = 0;
    }
    if (param_1[0x93] != 0) {
      operator delete[](void*)();
      param_1[0x93] = 0;
    }
    plVar18 = (long *)param_1[0x95];
    plVar20 = (long *)param_1[0x94];
    if ((plVar18 != plVar20) && (plVar20 != plVar18)) {
      do {
        if (*plVar20 != 0) {
          operator delete[](void*)();
        }
        plVar20 = plVar20 + 1;
      } while (plVar18 != plVar20);
      lVar17 = param_1[0x95];
      if (lVar17 != param_1[0x94]) {
        param_1[0x95] = lVar17 + (~((lVar17 + -8) - param_1[0x94]) & 0xfffffffffffffff8U);
      }
    }
    if ((long *)param_1[0xb2] != (long *)0x0) {
      (**(code **)(*(long *)param_1[0xb2] + 0x10))();
      param_1[0xb2] = 0;
    }
    plVar20 = (long *)param_1[0xaa];
    *(undefined4 *)(param_1 + 0x28) = 0x3f800000;
    if (plVar20 != (long *)0x0) {
      uStack_188 = 0;
      (**(code **)(*plVar20 + 0x30))(plVar20,&uStack_188);
      plVar20 = (long *)param_1[0xaa];
      if (param_1 + 0xa6 == plVar20) {
        pcVar13 = *(code **)(*plVar20 + 0x20);
code_r0x018d5b80:
        (*pcVar13)();
      }
      else if (plVar20 != (long *)0x0) {
        pcVar13 = *(code **)(*plVar20 + 0x28);
        goto code_r0x018d5b80;
      }
      param_1[0xaa] = 0;
    }
    *(undefined4 *)(param_1 + 0x2a) = 0;
    *(int *)((long)param_1 + 0x14c) = (int)param_1[0xb9];
  }
  return;
}

// ==== CGameResourceDownloader::Progress_Setup()
// vaddr 0x17d6254 | ghidra 0x18d6254 | size 21872 | symbol _ZN23CGameResourceDownloader14Progress_SetupEv | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Type propagation algorithm not settling */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN23CGameResourceDownloader14Progress_SetupEv(long *param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  ulong *puVar3;
  ulong uVar4;
  undefined7 *puVar5;
  undefined *puVar6;
  undefined8 *puVar7;
  byte bVar8;
  byte bVar9;
  uint uVar10;
  undefined8 uVar11;
  undefined8 uVar12;
  bool bVar13;
  bool bVar14;
  int iVar15;
  uint uVar16;
  undefined1 *puVar17;
  ulong *puVar18;
  ulong *puVar19;
  long *plVar20;
  long lVar21;
  ulong uVar22;
  undefined8 uVar23;
  undefined1 auVar24 [8];
  ulong *puVar25;
  ulong uVar26;
  undefined *puVar27;
  undefined *puVar28;
  ulong uVar29;
  undefined4 uVar30;
  undefined1 auVar31 [8];
  ulong *puVar32;
  code *pcVar33;
  undefined1 *puVar34;
  undefined1 *puVar35;
  char cVar36;
  long lVar37;
  long lVar38;
  long lVar39;
  long *plVar40;
  undefined8 uVar41;
  long lVar42;
  long *plVar43;
  byte *pbVar44;
  char *pcVar45;
  char *pcVar46;
  char *pcVar47;
  ulong uVar48;
  byte *pbVar49;
  undefined *puVar50;
  float fVar51;
  double dVar52;
  float fVar53;
  long alStack_360 [4];
  long *plStack_340;
  undefined8 uStack_330;
  ulong *puStack_328;
  undefined1 auStack_320 [8];
  undefined *puStack_318;
  long *plStack_310;
  byte bStack_308;
  undefined8 uStack_2f8;
  byte bStack_2d8;
  undefined8 uStack_2c8;
  undefined *puStack_2c0;
  long *plStack_2b8;
  undefined8 uStack_2b0;
  long lStack_2a8;
  undefined8 uStack_2a0;
  ushort uStack_28e;
  ulong *puStack_230;
  ulong *puStack_228;
  ulong *puStack_220;
  undefined1 auStack_210 [16];
  undefined1 auStack_200 [16];
  ulong *puStack_1f0;
  ulong *puStack_1e8;
  undefined8 uStack_1e0;
  ulong uStack_1d8;
  long lStack_1d0;
  int iStack_1c8;
  int iStack_1c4;
  int iStack_1c0;
  int iStack_1bc;
  int iStack_1b8;
  byte bStack_1b0;
  undefined7 uStack_1af;
  ulong uStack_1a8;
  undefined7 *puStack_1a0;
  undefined *puStack_198;
  long *plStack_190;
  undefined8 uStack_188;
  long lStack_180;
  undefined8 uStack_178;
  undefined8 uStack_170;
  uint uStack_168;
  undefined *puStack_160;
  undefined1 uStack_158;
  ulong *puStack_150;
  ulong *puStack_148;
  ulong *puStack_140;
  ulong *puStack_110;
  ulong *puStack_108;
  ulong *puStack_100;
  long lStack_f8;
  undefined8 uStack_f0;
  undefined1 uStack_e8;
  ulong *puStack_e0;
  ulong *puStack_d8;
  ulong *puStack_d0;
  ulong *puStack_c0;
  ulong *puStack_b8;
  ulong *puStack_b0;
  ulong *puStack_a0;
  ulong *puStack_98;
  ulong *puStack_90;
  ulong *puStack_80;
  ulong *puStack_78;
  ulong *puStack_70;
  
  if ((*(char *)((long)param_1 + 0x154) == '\0') && ((int)param_1[0x12] != 0)) {
    (*(code *)PTR__ZN23CGameResourceDownloader17Progress_DownloadEv_02ca6d60)(param_1);
    return;
  }
  switch((int)param_1[0x2a]) {
  case 0:
    if (param_1[0xbc] == 0) {
      plVar43 = param_1 + 0x50;
      lVar39 = Aska::ASON::Init(unsigned int, bool)(plVar43,"meterEPv",1);
      if (lVar39 != 0) goto code_r0x018d901c;
      uVar41 = Framework::CFileLoader::pDefaultDirectLoadFolder()();
      puStack_1f0 = (ulong *)0x0;
      puStack_1e8 = (ulong *)0x0;
      uStack_1e0 = (ulong *)0x0;
      uVar22 = strlen();
      if (uVar22 < 0x17) {
        uVar29 = (ulong)&puStack_1f0 | 1;
        puStack_1f0 = (ulong *)CONCAT71(puStack_1f0._1_7_,(char)(uVar22 << 1));
        if (uVar22 != 0) goto code_r0x018d934c;
      }
      else {
        uVar48 = uVar22 + 0x10 & 0xfffffffffffffff0;
        if (uVar48 == 0) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
        }
        uVar29 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar48,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
        if (uVar29 == 0) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
        }
        puStack_1f0 = (ulong *)(uVar48 | 1);
        puStack_1e8 = (ulong *)uVar22;
        uStack_1e0 = (ulong *)uVar29;
code_r0x018d934c:
        memcpy(uVar29,uVar41,uVar22);
      }
      *(undefined1 *)(uVar29 + uVar22) = 0;
      string std::__ndk1::operator+<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> >(string const&, char const*)(&puStack_150,&puStack_1f0,&UNK_02866b1d/*"buildin_varsion.bin"*/);
      uVar22 = Framework::CFileLoader::gIsFileExist(char const*, char const*)(&UNK_02866b1d/*"buildin_varsion.bin"*/,0);
      lVar39 = 0;
      if ((uVar22 & 1) == 0) {
code_r0x018d98b8:
        if (((ulong)puStack_150 & 1) == 0) {
          puVar18 = (ulong *)((ulong)&puStack_150 | 1);
code_r0x018d98d4:
          iVar15 = access(puVar18,0);
          bVar14 = false;
          if (iVar15 != 0) {
            bVar13 = bVar14;
            if (((ulong)puStack_150 & 1) == 0) goto code_r0x018d98ec;
            goto code_r0x018d9a28;
          }
          puVar18 = (ulong *)((ulong)&puStack_150 | 1);
          if (((ulong)puStack_150 & 1) != 0) {
            puVar18 = puStack_140;
          }
          lVar42 = Aska::FileReadManager::CalcFileLength(char const*, bool)(puVar18,0);
          if (lVar42 == 0) goto code_r0x018d9a1c;
          lVar21 = operator new[](unsigned long, std::nothrow_t const&)(lVar42,PTR__ZSt7nothrow_02cb9a80);
          param_1[0x91] = lVar21;
          puVar2 = PTR__ZTVN4Aska10FileStreamE_02cbc9f8;
          puVar1 = PTR__ZTVN4Aska4FileE_02cb6e28;
          uStack_330 = (ulong *)(PTR__ZTVN4Aska10FileStreamE_02cbc9f8 + 0x10);
          puStack_328 = (ulong *)(PTR__ZTVN4Aska4FileE_02cb6e28 + 0x10);
          puVar18 = (ulong *)((ulong)&puStack_150 | 1);
          if (((ulong)puStack_150 & 1) != 0) {
            puVar18 = puStack_140;
          }
          auStack_320 = (undefined1  [8])((ulong)auStack_320 & 0xffffffffffffff00);
          bStack_308 = 0;
          puStack_318 = (undefined *)0x0;
          plStack_310 = (long *)0x0;
          uVar22 = Aska::FileStream::Open(char const*, bool, bool, Aska::Machine::Endian)(&uStack_330,puVar18,1,0,3);
          if ((uVar22 & 1) == 0) {
code_r0x018d99c4:
            lVar39 = Aska::ASON::AValue::AMap::Get_(char const*)(param_1 + 0x5d,&UNK_02866dc9/*"assets"*/);
            bVar14 = false;
            lVar39 = lVar39 + 8;
          }
          else {
            Aska::FileStream::Read(void*, unsigned long, unsigned long)(&uStack_330,param_1[0x91],lVar42,1);
            Aska::FileStream::Close()(&uStack_330);
            Aska::ASON::DeserializeBinary(void const*, unsigned long)(plVar43,param_1[0x91],lVar42);
            if (-1 < param_1[0x60]) goto code_r0x018d99c4;
            param_1[0x2c] = -0x3a7;
            *(undefined8 *)((long)param_1 + 0x14c) = 5;
            if ((*(char *)((long)param_1 + 0x157) != '\0') &&
               (plVar43 = (long *)param_1[0x9c], plVar43 != (long *)0x0)) {
              puStack_110 = (ulong *)0xfffffffffffffc59;
              puStack_230 = (ulong *)CONCAT44(puStack_230._4_4_,1000000);
              (**(code **)(*plVar43 + 0x30))(plVar43,&puStack_230,&puStack_110);
            }
            bVar14 = true;
          }
          uStack_330 = (ulong *)(puVar2 + 0x10);
          Aska::FileStream::Close()(&uStack_330);
          puStack_328 = (ulong *)(puVar1 + 0x10);
          if (puStack_318 != (undefined *)0x0) {
            Aska::File::Close()((ulong)&uStack_330 | 8);
          }
          if (bVar14) goto code_r0x018d9a0c;
        }
        else {
          puVar18 = puStack_140;
          if (puStack_140 != (ulong *)0x0) goto code_r0x018d98d4;
        }
code_r0x018d9a1c:
        bVar14 = false;
        bVar13 = false;
        if (((byte)puStack_150 & 1) == 0) goto code_r0x018d98ec;
code_r0x018d9a28:
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puStack_140);
        if (((ulong)puStack_1f0 & 1) == 0) goto code_r0x018d98f4;
code_r0x018d9a38:
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_1e0);
        if (bVar14) {
          return;
        }
      }
      else {
        puVar19 = (ulong *)((ulong)&puStack_150 | 1);
        puVar18 = puVar19;
        if (((ulong)puStack_150 & 1) != 0) {
          puVar18 = puStack_140;
        }
        lVar39 = Aska::FileReadManager::CalcFileLength(char const*, bool)(puVar18,1);
        if (lVar39 == 0) {
code_r0x018d98b4:
          lVar39 = 0;
          goto code_r0x018d98b8;
        }
        lVar42 = operator new[](unsigned long, std::nothrow_t const&)(lVar39,PTR__ZSt7nothrow_02cb9a80);
        param_1[0x91] = lVar42;
        puVar18 = puVar19;
        if (((ulong)puStack_150 & 1) != 0) {
          puVar18 = puStack_140;
        }
        uVar22 = Framework::CFileLoader::IsAssetManagerPath(char const*)(puVar18);
        puVar1 = PTR__ZTVN4Aska4FileE_02cb6e28;
        if ((uVar22 & 1) == 0) goto code_r0x018d98b4;
        uStack_330 = (ulong *)(PTR__ZTVN4Aska4FileE_02cb6e28 + 0x10);
        if (((ulong)puStack_150 & 1) != 0) {
          puVar19 = puStack_140;
        }
        auStack_320 = (undefined1  [8])0x0;
        puStack_328 = (ulong *)CONCAT71(puStack_328._1_7_,1);
        uVar22 = Aska::File::Open(char const*, bool, bool, bool)(&uStack_330,puVar19,1,0,0);
        if ((uVar22 & 1) == 0) {
code_r0x018d9458:
          lVar39 = Aska::ASON::AValue::AMap::Get_(char const*)(param_1 + 0x5d,&UNK_02866dc9/*"assets"*/);
          bVar14 = false;
          lVar39 = lVar39 + 8;
        }
        else {
          Aska::File::Read(void*, unsigned long, unsigned int*)(&uStack_330,param_1[0x91],lVar39,0);
          Aska::File::Close()(&uStack_330);
          Aska::ASON::DeserializeBinary(void const*, unsigned long)(plVar43,param_1[0x91],lVar39);
          if (-1 < param_1[0x60]) goto code_r0x018d9458;
          param_1[0x2c] = -0x3a7;
          *(undefined8 *)((long)param_1 + 0x14c) = 5;
          if ((*(char *)((long)param_1 + 0x157) != '\0') &&
             (plVar40 = (long *)param_1[0x9c], plVar40 != (long *)0x0)) {
            puStack_110 = (ulong *)0xfffffffffffffc59;
            puStack_230 = (ulong *)CONCAT44(puStack_230._4_4_,1000000);
            (**(code **)(*plVar40 + 0x30))(plVar40,&puStack_230,&puStack_110);
          }
          lVar39 = 0;
          bVar14 = true;
        }
        uStack_330 = (ulong *)(puVar1 + 0x10);
        if (auStack_320 != (undefined1  [8])0x0) {
          Aska::File::Close()(&uStack_330);
        }
        if (!bVar14) goto code_r0x018d98b8;
code_r0x018d9a0c:
        bVar14 = true;
        bVar13 = bVar14;
        if (((byte)puStack_150 & 1) != 0) goto code_r0x018d9a28;
code_r0x018d98ec:
        bVar14 = bVar13;
        if (((ulong)puStack_1f0 & 1) != 0) goto code_r0x018d9a38;
code_r0x018d98f4:
        if (bVar14) {
          return;
        }
      }
      *(undefined4 *)(param_1 + 0x28) = 0;
      if ((lVar39 != 0) && (*(int *)(lVar39 + 8) != 0)) {
        plVar43 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x98,PTR__ZSt7nothrow_02cb9a80);
        if (plVar43 != (long *)0x0) {
          puVar1 = PTR__ZTV12CVersionInfo_02cbda90 + 0x10;
          *(undefined4 *)((long)plVar43 + 0xc) = 0x312e31;
          *(undefined1 *)(plVar43 + 1) = 1;
          *plVar43 = (long)puVar1;
          memset(plVar43 + 2,0,0x48);
          puVar1 = PTR__ZTVN4Aska8THashMapINSt6__ndk112basic_stringIcNS1_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS5_22CSTLStringAllocatorInfEEEEE10CAssetInfo17Hasher_CSTLStringNS_8TEqualToIS9_EENS_10TAllocatorINS_5TPairIKS9_SA_EEEEEE_02cc2290
                   + 0x10;
          *(undefined8 *)((long)plVar43 + 100) = 0x3f400000;
          plVar43[0xb] = (long)puVar1;
          *(undefined4 *)((long)plVar43 + 0x6c) = 0;
          puVar17 = (undefined1 *)Aska::MemoryManagerAdapter::AlignedMalloc(unsigned long, unsigned long)(0xcc0,8);
          lVar42 = 0x11;
          if (puVar17 == (undefined1 *)0x0) {
            lVar42 = 0;
          }
          plVar43[0xf] = (long)puVar17;
          plVar43[0x10] = lVar42;
          if (puVar17 != (undefined1 *)0x0) {
            uVar22 = (lVar42 * 0xc0 - 0xc0U) / 0xc0 + 1;
            puVar35 = puVar17;
            if ((1 < uVar22) && (uVar48 = uVar22 & 0x3fffffffffffffe, uVar48 != 0)) {
              uVar29 = uVar48;
              do {
                *puVar35 = 0;
                puVar35[0xc0] = 0;
                uVar29 = uVar29 - 2;
                puVar35 = puVar35 + 0x180;
              } while (uVar29 != 0);
              puVar35 = puVar17 + uVar48 * 0xc0;
              if (uVar22 == uVar48) goto code_r0x018db5dc;
            }
            do {
              puVar34 = puVar35 + 0xc0;
              *puVar35 = 0;
              puVar35 = puVar34;
            } while (puVar17 + lVar42 * 0xc0 != puVar34);
          }
code_r0x018db5dc:
          *(undefined1 *)(plVar43 + 0x12) = 1;
          puVar1 = PTR__ZTV10CAssetList_02cba9a8 + 0x38;
          plVar43[0xb] = (long)(PTR__ZTV10CAssetList_02cba9a8 + 0x10);
          plVar43[0x11] = (long)puVar1;
        }
        puVar18 = (ulong *)(plVar43 + 8);
        param_1[0xbc] = (long)plVar43;
        if (puVar18 == (ulong *)(param_1 + 0x47)) goto code_r0x018db6c0;
        lVar42 = param_1[0x49];
        uVar22 = param_1[0x48];
        uVar48 = (ulong)(byte)*puVar18;
        if ((*(byte *)(param_1 + 0x47) & 1) == 0) {
          lVar42 = (long)param_1 + 0x239;
          uVar22 = (ulong)(*(byte *)(param_1 + 0x47) >> 1);
        }
        if (((byte)*puVar18 & 1) == 0) {
          uVar29 = 0x16;
          lVar21 = uVar22 - 0x16;
          if (uVar22 < 0x16 || lVar21 == 0) {
code_r0x018db660:
            if ((uVar48 & 1) == 0) {
              lVar21 = (long)plVar43 + 0x41;
            }
            else {
              lVar21 = plVar43[10];
            }
            if (uVar22 != 0) {
              memmove(lVar21,lVar42,uVar22);
            }
            *(undefined1 *)(lVar21 + uVar22) = 0;
            if ((*puVar18 & 1) == 0) {
              *(byte *)puVar18 = (byte)(uVar22 << 1);
            }
            else {
              plVar43[9] = uVar22;
            }
            goto code_r0x018db6c0;
          }
        }
        else {
          uVar48 = *puVar18;
          uVar29 = (uVar48 & 0xfffffffffffffffe) - 1;
          lVar21 = uVar22 - uVar29;
          if (uVar22 < uVar29 || lVar21 == 0) goto code_r0x018db660;
        }
        if ((uVar48 & 1) == 0) {
          uVar48 = (ulong)(((uint)uVar48 & 0xfe) >> 1);
        }
        else {
          uVar48 = plVar43[9];
        }
        string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(puVar18,uVar29,lVar21,uVar48,0,uVar48,uVar22);
code_r0x018db6c0:
        lVar42 = param_1[0xbc];
        fVar51 = (float)NEON_ucvtf(*(undefined4 *)(lVar42 + 0x68));
        uVar22 = (ulong)(fVar51 / *(float *)(lVar42 + 100));
        if (uVar22 <= *(uint *)(lVar39 + 8)) {
          uVar22 = (ulong)*(uint *)(lVar39 + 8);
        }
        Aska::THashMap<string, CAssetInfo, Hasher_CSTLString, Aska::TEqualTo<string >, Aska::TAllocator<Aska::TPair<string const, CAssetInfo> > >::Rehash_(unsigned long)(lVar42 + 0x58,uVar22);
        if ((long *)param_1[0xb2] != (long *)0x0) {
          (**(code **)(*(long *)param_1[0xb2] + 0x10))();
          param_1[0xb2] = 0;
        }
        plVar43 = (long *)operator new(unsigned long, std::nothrow_t const&)(200,PTR__ZSt7nothrow_02cb9a80);
        if (plVar43 != (long *)0x0) {
          *plVar43 = (long)(PTR__ZTVN23CGameResourceDownloader11CVerifyTaskE_02cbe2d8 + 0x10);
          plVar43[1] = 0;
          memset(plVar43 + 2,0,99);
          *(undefined4 *)((long)plVar43 + 0x8c) = 0;
          *(undefined8 *)((long)plVar43 + 0x74) = 0;
          plVar43[0x17] = 0;
          *(undefined8 *)((long)plVar43 + 0x84) = 0;
          *(undefined8 *)((long)plVar43 + 0x7c) = 0;
          plVar43[0x16] = 0;
          plVar43[0x15] = 0;
          plVar43[0x14] = 0;
          plVar43[0x13] = 0;
          *(undefined4 *)(plVar43 + 0x18) = 0x3f800000;
        }
        param_1[0xb2] = (long)plVar43;
        lVar42 = plVar43[8];
        lVar21 = param_1[0xbc];
        plVar43[4] = 0;
        plVar43[5] = lVar39;
        plVar43[6] = 0;
        *(undefined1 *)((long)plVar43 + 0x72) = 0;
        *(undefined4 *)((long)plVar43 + 0x74) = 0;
        plVar43[2] = (long)param_1;
        plVar43[3] = lVar21;
        plVar43[10] = 0;
        *(undefined2 *)(plVar43 + 0xe) = 0;
        if (lVar42 != plVar43[7]) {
          plVar43[8] = lVar42 + (~((lVar42 + -8) - plVar43[7]) & 0xfffffffffffffff8U);
        }
        std::__ndk1::__hash_table<std::__ndk1::__hash_value_type<unsigned int, bool>, std::__ndk1::__unordered_map_hasher<unsigned int, std::__ndk1::__hash_value_type<unsigned int, bool>, std::__ndk1::hash<unsigned int>, true>, std::__ndk1::__unordered_map_equal<unsigned int, std::__ndk1::__hash_value_type<unsigned int, bool>, std::__ndk1::equal_to<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__hash_value_type<unsigned int, bool>, Framework::CSTLUnorderedMapAllocatorInf> >::rehash(unsigned long)(plVar43 + 0x14,*(undefined4 *)(lVar39 + 8));
        plVar43[1] = 4;
        *(undefined4 *)(param_1 + 0x2a) = 1;
        return;
      }
    }
    uVar30 = 2;
    break;
  case 1:
    lVar39 = param_1[0xb2];
    if (lVar39 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02866a48/*"C:\BAS_Submission\Client\Project\..\Source\Game\Resource\GameResourceDownloader.cpp"*/,0x989,&UNK_02866aee/*"m_pVerifyTask is null."*/);
      lVar39 = param_1[0xb2];
    }
    switch(*(undefined4 *)(lVar39 + 8)) {
    case 0:
      CGameResourceDownloader::CVerifyTask::ProgressLocalFileCheck()();
      break;
    case 1:
      CGameResourceDownloader::CVerifyTask::ProgressServerManifestCheck()();
      break;
    case 2:
      CGameResourceDownloader::CVerifyTask::ProgressEraseCheck()();
      break;
    case 3:
      CGameResourceDownloader::CVerifyTask::ProgressEraseEpisodeDataCheck()();
      break;
    case 4:
      CGameResourceDownloader::CVerifyTask::ProgressSetupManifest()();
    }
    lVar39 = param_1[0xb2];
    if (*(char *)(lVar39 + 0x71) != '\0') {
      *(undefined4 *)(param_1 + 0x2a) = 2;
    }
    iVar15 = *(int *)(lVar39 + 8);
    if (iVar15 == 1) {
      fVar53 = 6.0;
      fVar51 = (float)NEON_ucvtf(*(undefined4 *)(lVar39 + 0xc));
code_r0x018d952c:
      fVar51 = fVar51 / fVar53;
    }
    else {
      fVar51 = 0.0;
      if (iVar15 == 2) {
        plVar43 = *(long **)(lVar39 + 0x98);
        if (plVar43 != (long *)0x0) {
          uVar22 = (ulong)(plVar43[1] - *plVar43) >> 8;
          uVar16 = (uint)((ulong)(plVar43[1] - *plVar43) >> 8);
joined_r0x018d7188:
          if (uVar16 != 0) {
            fVar51 = (float)*(uint *)(lVar39 + 0x74);
            fVar53 = (float)(uVar22 & 0xffffffff);
            goto code_r0x018d952c;
          }
        }
      }
      else if (iVar15 == 0) {
        if (*(char *)(lVar39 + 0x70) == '\0') {
          lVar42 = *(long *)(lVar39 + 0x28);
        }
        else {
          lVar42 = *(long *)(lVar39 + 0x30);
        }
        if (lVar42 != 0) {
          uVar16 = *(uint *)(lVar42 + 8);
          uVar22 = (ulong)uVar16;
          goto joined_r0x018d7188;
        }
      }
    }
    fVar51 = fVar51 * _UNK_027e6a14;
    fVar53 = 0.0;
code_r0x018da988:
    *(float *)(param_1 + 0x28) = fVar51 + fVar53;
    return;
  case 2:
    lVar39 = param_1[0xbb];
    if ((lVar39 == 0) || (*(int *)(lVar39 + 0x68) == 0)) {
code_r0x018d8008:
      if ((*(byte *)((long)param_1 + 0xaa) & 1) != 0) {
        if (param_1[0x10] != 0) {
          operator delete[](void*)();
          param_1[0x10] = 0;
        }
        param_1[0x11] = 0;
      }
      plVar43 = param_1 + 0x12;
      *plVar43 = 0;
      param_1[0x13] = 0;
      if (param_1[0x26] != 0) {
        plVar40 = (long *)param_1[0x25];
        while (plVar40 != (long *)0x0) {
          plVar40 = (long *)*plVar40;
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)();
        }
        lVar39 = param_1[0x24];
        param_1[0x25] = 0;
        if (lVar39 != 0) {
          lVar42 = 0;
          do {
            *(undefined8 *)(param_1[0x23] + lVar42 * 8) = 0;
            lVar42 = lVar42 + 1;
          } while (lVar39 != lVar42);
        }
        param_1[0x26] = 0;
      }
      lVar39 = param_1[0xb];
      plVar40 = param_1 + 8;
      param_1[0xc] = 0;
      if (0 < lVar39) {
        lVar42 = 0;
        do {
          plVar20 = *(long **)(param_1[9] + lVar42 * 8);
          lVar21 = lVar42;
          if (plVar20 != (long *)0x0) {
            (**(code **)(*plVar20 + 0x10))();
            lVar39 = param_1[0xb];
            lVar21 = param_1[0xc];
          }
          lVar42 = lVar21;
          if ((-1 < lVar21) && (lVar21 < lVar39)) {
            lVar39 = lVar39 + -1;
            if (lVar21 < lVar39) {
              do {
                puVar7 = (undefined8 *)(param_1[9] + lVar42 * 8);
                lVar42 = lVar42 + 1;
                *puVar7 = puVar7[1];
                lVar39 = param_1[0xb] + -1;
              } while (lVar42 < lVar39);
            }
            Aska::TArray<CGameResourceDownloader::CDownloadNode*, false>::Resize(long, bool)(plVar40,lVar39,0);
            lVar42 = param_1[0xc];
            if (lVar21 <= lVar42) {
              lVar39 = lVar42 + -1;
              if (lVar42 < 1) {
                lVar42 = 0;
              }
              else {
                lVar42 = lVar39;
                if (param_1[0xb] <= lVar39) {
                  lVar42 = param_1[0xb];
                }
              }
              param_1[0xc] = lVar42;
            }
          }
          lVar39 = param_1[0xb];
        } while (lVar42 < lVar39);
      }
      if ((long *)param_1[0xb2] != (long *)0x0) {
        (**(code **)(*(long *)param_1[0xb2] + 0x10))();
        param_1[0xb2] = 0;
      }
      puVar1 = 
      PTR__ZN23CGameResourceDownloader13CDownloadNode12UnpackNotify15m_DispatchCountE_02cbe960;
      *(undefined4 *)(param_1 + 0x28) = 0x3dcccccd;
      *(undefined4 *)puVar1 = 0;
      CGameResourceDownloader::CDownloadNode::UnpackNotify::ResetDispatchCount()+0x10(&uStack_330);
      uVar41 = _UNK_02866ddc;
      if (((ulong)uStack_330 & 1) == 0) {
        lVar39 = 0x16;
        puVar18 = (ulong *)((ulong)uStack_330 & 0xff);
      }
      else {
        lVar39 = ((ulong)uStack_330 & 0xfffffffffffffffe) - 1;
        puVar18 = uStack_330;
      }
      puVar19 = (ulong *)(ulong)(((uint)puVar18 & 0xfe) >> 1);
      if (((ulong)puVar18 & 1) != 0) {
        puVar19 = puStack_328;
      }
      if ((ulong)(lVar39 - (long)puVar19) < 0x1b) {
        string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&uStack_330,lVar39,(byte *)((0x1b - lVar39) + (long)puVar19),puVar19,puVar19
                        ,0,0x1b,&UNK_02866ddc/*"version_latest_Bulk.version"*/);
      }
      else {
        uVar11 = CONCAT35(_UNK_02866dec,_UNK_02866de7);
        uVar23 = CONCAT53(_UNK_02866de7,_UNK_02866de4);
        auVar24 = (undefined1  [8])((ulong)&uStack_330 | 1);
        if (((ulong)puVar18 & 1) != 0) {
          auVar24 = auStack_320;
        }
        pbVar49 = (byte *)((long)auVar24 + (long)puVar19);
        *(undefined8 *)(pbVar49 + 0x13) = _UNK_02866def;
        *(undefined8 *)(pbVar49 + 0xb) = uVar11;
        *(undefined8 *)(pbVar49 + 8) = uVar23;
        *(undefined8 *)pbVar49 = uVar41;
        puVar19 = (ulong *)((long)puVar19 + 0x1b);
        puVar25 = puVar19;
        if (((ulong)puVar18 & 1) == 0) {
          uStack_330 = (ulong *)CONCAT71(uStack_330._1_7_,(char)puVar19 * '\x02');
          puVar25 = puStack_328;
        }
        puStack_328 = puVar25;
        *(byte *)((long)auVar24 + (long)puVar19) = 0;
      }
      uStack_1e0 = (ulong *)auStack_320;
      puStack_1e8 = puStack_328;
      puStack_1f0 = uStack_330;
      CGameResourceDownloader::CDownloadNode::UnpackNotify::ResetDispatchCount()+0x10(&uStack_330);
      uVar12 = _UNK_02866e10;
      uVar11 = _UNK_02866e08;
      uVar23 = _UNK_02866e00;
      uVar41 = _UNK_02866df8;
      if (((ulong)uStack_330 & 1) == 0) {
        lVar39 = 0x16;
        puVar18 = (ulong *)((ulong)uStack_330 & 0xff);
      }
      else {
        lVar39 = ((ulong)uStack_330 & 0xfffffffffffffffe) - 1;
        puVar18 = uStack_330;
      }
      puVar19 = (ulong *)(ulong)(((uint)puVar18 & 0xfe) >> 1);
      if (((ulong)puVar18 & 1) != 0) {
        puVar19 = puStack_328;
      }
      if ((ulong)(lVar39 - (long)puVar19) < 0x21) {
        string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&uStack_330,lVar39,(byte *)((0x21 - lVar39) + (long)puVar19),puVar19,puVar19
                        ,0,0x21,&UNK_02866df8/*"version_latest_Individual.version"*/);
      }
      else {
        auVar24 = (undefined1  [8])((ulong)&uStack_330 | 1);
        if (((ulong)puVar18 & 1) != 0) {
          auVar24 = auStack_320;
        }
        pbVar49 = (byte *)((long)auVar24 + (long)puVar19);
        pbVar49[0x20] = 0x6e;
        *(undefined8 *)(pbVar49 + 8) = uVar23;
        *(undefined8 *)pbVar49 = uVar41;
        *(undefined8 *)(pbVar49 + 0x18) = uVar12;
        *(undefined8 *)(pbVar49 + 0x10) = uVar11;
        puVar19 = (ulong *)((long)puVar19 + 0x21);
        puVar25 = puVar19;
        if (((ulong)puVar18 & 1) == 0) {
          uStack_330 = (ulong *)CONCAT71(uStack_330._1_7_,(char)puVar19 * '\x02');
          puVar25 = puStack_328;
        }
        puStack_328 = puVar25;
        *(byte *)((long)auVar24 + (long)puVar19) = 0;
      }
      puStack_100 = (ulong *)0x0;
      puStack_108 = (ulong *)0x0;
      puStack_140 = (ulong *)auStack_320;
      puStack_148 = puStack_328;
      puStack_150 = uStack_330;
      puStack_110 = (ulong *)0x0;
      if ((int)param_1[0x4f] != 0) {
        uVar16 = 0;
        do {
          CGameResourceDownloader::CDownloadNode::UnpackNotify::ResetDispatchCount()+0x10(&puStack_230);
          uVar16 = uVar16 + 1;
          Framework::CSTLStringUtility_Base<string >::Format(char const*, ...)(&puStack_80,&UNK_02866b31/*"version_latest_ep%d.version"*/,uVar16);
          puVar18 = (ulong *)((ulong)puStack_80 >> 1 & 0x7f);
          puVar19 = (ulong *)((ulong)&puStack_80 | 1);
          if (((ulong)puStack_80 & 1) != 0) {
            puVar18 = puStack_78;
            puVar19 = puStack_70;
          }
          if (((ulong)puStack_230 & 1) == 0) {
            lVar39 = 0x16;
            puVar25 = (ulong *)((ulong)puStack_230 & 0xff);
          }
          else {
            lVar39 = ((ulong)puStack_230 & 0xfffffffffffffffe) - 1;
            puVar25 = puStack_230;
          }
          puVar32 = (ulong *)(ulong)(((uint)puVar25 & 0xfe) >> 1);
          if (((ulong)puVar25 & 1) != 0) {
            puVar32 = puStack_228;
          }
          if ((ulong *)(lVar39 - (long)puVar32) < puVar18) {
            string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&puStack_230,lVar39,(byte *)(((long)puVar18 - lVar39) + (long)puVar32),
                            puVar32,puVar32,0,puVar18);
          }
          else if (puVar18 != (ulong *)0x0) {
            puVar3 = (ulong *)((ulong)&puStack_230 | 1);
            if (((ulong)puVar25 & 1) != 0) {
              puVar3 = puStack_220;
            }
            memcpy((byte *)((long)puVar3 + (long)puVar32),puVar19,puVar18);
            puVar32 = (ulong *)((long)puVar32 + (long)puVar18);
            puVar18 = puVar32;
            if (((ulong)puStack_230 & 1) == 0) {
              puStack_230 = (ulong *)CONCAT71(puStack_230._1_7_,(char)puVar32 * '\x02');
              puVar18 = puStack_228;
            }
            puStack_228 = puVar18;
            *(byte *)((long)puVar3 + (long)puVar32) = 0;
          }
          auStack_320 = (undefined1  [8])puStack_220;
          puStack_328 = puStack_228;
          uStack_330 = puStack_230;
          puStack_228 = (ulong *)0x0;
          puStack_220 = (ulong *)0x0;
          puStack_230 = (ulong *)0x0;
          if ((((ulong)puStack_80 & 1) != 0) &&
             (Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puStack_70), ((ulong)puStack_230 & 1) != 0)) {
            Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puStack_220);
          }
          puVar18 = puStack_108;
          if (puStack_108 == puStack_100) {
            void std::__ndk1::vector<string, Framework::CSTLAllocator<string, Framework::CSTLVectorAllocatorInf> >::__push_back_slow_path<string const&>(string const&)(&puStack_110,&uStack_330);
          }
          else {
            if (puStack_108 == (ulong *)0x0) {
              Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
            }
            auVar24 = auStack_320;
            puVar19 = puStack_328;
            puVar18[1] = 0;
            puVar18[2] = 0;
            *puVar18 = 0;
            if (((ulong)uStack_330 & 1) == 0) {
              puVar18[2] = (ulong)auStack_320;
              puVar18[1] = (ulong)puStack_328;
              *puVar18 = (ulong)uStack_330;
            }
            else {
              if (puStack_328 < (ulong *)0x17) {
                pbVar49 = (byte *)((long)puVar18 + 1);
                *(byte *)puVar18 = (byte)((long)puStack_328 << 1);
                if (puStack_328 != (ulong *)0x0) goto code_r0x018d8530;
              }
              else {
                uVar22 = (ulong)(puStack_328 + 2) & 0xfffffffffffffff0;
                if (uVar22 == 0) {
                  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
                }
                pbVar49 = (byte *)Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar22,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
                if (pbVar49 == (byte *)0x0) {
                  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
                }
                puVar18[1] = (ulong)puVar19;
                puVar18[2] = (ulong)pbVar49;
                *puVar18 = uVar22 | 1;
code_r0x018d8530:
                memcpy(pbVar49,auVar24,puVar19);
              }
              pbVar49[(long)puVar19] = 0;
            }
            puStack_108 = puStack_108 + 3;
          }
          if (((ulong)uStack_330 & 1) != 0) {
            Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(auStack_320);
          }
        } while (uVar16 < *(uint *)(param_1 + 0x4f));
      }
      puVar19 = uStack_1e0;
      puVar18 = puStack_1f0;
      if (*(char *)((long)param_1 + 0x155) != '\0') {
        lVar39 = operator new(unsigned long, std::nothrow_t const&)(0x450,PTR__ZSt7nothrow_02cb9a80);
        if (lVar39 != 0) {
          puVar25 = (ulong *)((ulong)&puStack_1f0 | 1);
          if (((ulong)puVar18 & 1) != 0) {
            puVar25 = puVar19;
          }
          plStack_310 = (long *)0x0;
          CGameResourceDownloader::CDownloadNode::CDownloadNode(char const*, std::__ndk1::function<void (char const*, CGameResourceDownloader::iErrorCode)>)(lVar39,puVar25,&uStack_330);
          if (&uStack_330 == plStack_310) {
            pcVar33 = *(code **)(*plStack_310 + 0x20);
          }
          else {
            if (plStack_310 == (long *)0x0) goto code_r0x018d89bc;
            pcVar33 = *(code **)(*plStack_310 + 0x28);
          }
          (*pcVar33)();
        }
code_r0x018d89bc:
        lVar42 = param_1[0xb];
        if (-1 < lVar42) {
          Aska::TArray<CGameResourceDownloader::CDownloadNode*, false>::Resize(long, bool)(plVar40,lVar42 + 1,0);
          *(long *)(param_1[9] + lVar42 * 8) = lVar39;
        }
        plVar20 = param_1 + 0xf;
        *(undefined1 *)(lVar39 + 0x110) = 0;
        if (*(int *)(lVar39 + 8) != 5) {
          *(undefined1 *)(lVar39 + 0x150) = 1;
          *(undefined8 *)(lVar39 + 8) = 1;
        }
        *(undefined1 *)(lVar39 + 0x150) = 1;
        lVar42 = *plVar43;
        if (-1 < lVar42) {
          Aska::TArray<CGameResourceDownloader::CDownloadNode*, false>::Resize(long, bool)(plVar20,lVar42 + 1,0);
          *(long *)(param_1[0x10] + lVar42 * 8) = lVar39;
        }
        puVar19 = puStack_140;
        puVar18 = puStack_150;
        lVar39 = operator new(unsigned long, std::nothrow_t const&)(0x450,PTR__ZSt7nothrow_02cb9a80);
        if (lVar39 != 0) {
          puVar25 = (ulong *)((ulong)&puStack_150 | 1);
          if (((ulong)puVar18 & 1) != 0) {
            puVar25 = puVar19;
          }
          plStack_310 = (long *)0x0;
          CGameResourceDownloader::CDownloadNode::CDownloadNode(char const*, std::__ndk1::function<void (char const*, CGameResourceDownloader::iErrorCode)>)(lVar39,puVar25,&uStack_330);
          if (&uStack_330 == plStack_310) {
            pcVar33 = *(code **)(*plStack_310 + 0x20);
          }
          else {
            if (plStack_310 == (long *)0x0) goto code_r0x018d8a94;
            pcVar33 = *(code **)(*plStack_310 + 0x28);
          }
          (*pcVar33)();
        }
code_r0x018d8a94:
        lVar42 = param_1[0xb];
        if (-1 < lVar42) {
          Aska::TArray<CGameResourceDownloader::CDownloadNode*, false>::Resize(long, bool)(plVar40,lVar42 + 1,0);
          *(long *)(param_1[9] + lVar42 * 8) = lVar39;
        }
        *(undefined1 *)(lVar39 + 0x110) = 0;
        if (*(int *)(lVar39 + 8) != 5) {
          *(undefined1 *)(lVar39 + 0x150) = 1;
          *(undefined8 *)(lVar39 + 8) = 1;
        }
        *(undefined1 *)(lVar39 + 0x150) = 1;
        lVar42 = *plVar43;
        if (-1 < lVar42) {
          Aska::TArray<CGameResourceDownloader::CDownloadNode*, false>::Resize(long, bool)(plVar20,lVar42 + 1,0);
          *(long *)(param_1[0x10] + lVar42 * 8) = lVar39;
        }
        puVar1 = PTR__ZSt7nothrow_02cb9a80;
        if ((int)param_1[0x4f] != 0) {
          uVar16 = 0;
          do {
            uVar48 = (ulong)uVar16;
            uVar22 = ((long)puStack_108 - (long)puStack_110 >> 3) * -0x5555555555555555;
            if (uVar22 < uVar48 || uVar22 - uVar48 == 0) {
              Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dc536/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Vector.h"*/,0x58,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,uVar48);
            }
            if ((puStack_110[uVar48 * 3] & 1) == 0) {
              pbVar49 = (byte *)((long)(puStack_110 + uVar48 * 3) + 1);
            }
            else {
              pbVar49 = (byte *)puStack_110[uVar48 * 3 + 2];
            }
            lVar39 = operator new(unsigned long, std::nothrow_t const&)(0x450,puVar1);
            if (lVar39 != 0) {
              plStack_310 = (long *)0x0;
              CGameResourceDownloader::CDownloadNode::CDownloadNode(char const*, std::__ndk1::function<void (char const*, CGameResourceDownloader::iErrorCode)>)(lVar39,pbVar49,&uStack_330);
              if (&uStack_330 == plStack_310) {
                pcVar33 = *(code **)(*plStack_310 + 0x20);
              }
              else {
                if (plStack_310 == (long *)0x0) goto code_r0x018d8bd4;
                pcVar33 = *(code **)(*plStack_310 + 0x28);
              }
              (*pcVar33)();
            }
code_r0x018d8bd4:
            lVar42 = param_1[0xb];
            if (-1 < lVar42) {
              Aska::TArray<CGameResourceDownloader::CDownloadNode*, false>::Resize(long, bool)(plVar40,lVar42 + 1,0);
              *(long *)(param_1[9] + lVar42 * 8) = lVar39;
            }
            *(undefined1 *)(lVar39 + 0x110) = 0;
            if (*(int *)(lVar39 + 8) != 5) {
              *(undefined1 *)(lVar39 + 0x150) = 1;
              *(undefined8 *)(lVar39 + 8) = 1;
            }
            *(undefined1 *)(lVar39 + 0x150) = 1;
            lVar42 = *plVar43;
            if (-1 < lVar42) {
              Aska::TArray<CGameResourceDownloader::CDownloadNode*, false>::Resize(long, bool)(plVar20,lVar42 + 1,0);
              *(long *)(param_1[0x10] + lVar42 * 8) = lVar39;
            }
            uVar16 = uVar16 + 1;
          } while (uVar16 < *(uint *)(param_1 + 0x4f));
        }
      }
      puVar18 = puStack_110;
      *(undefined4 *)(param_1 + 0x2a) = 3;
      if (puStack_110 != (ulong *)0x0) {
        while (puVar19 = puStack_108, puVar19 != puVar18) {
          puStack_108 = puVar19 + -3;
          if ((puVar19[-3] & 1) != 0) {
            Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puVar19[-1]);
          }
        }
        puStack_108 = puVar19;
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puStack_110);
      }
      auVar24 = (undefined1  [8])uStack_1e0;
      puVar18 = puStack_1f0;
      if (((ulong)puStack_150 & 1) != 0) {
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puStack_140);
        auVar24 = (undefined1  [8])uStack_1e0;
        puVar18 = puStack_1f0;
      }
      goto joined_r0x018db454;
    }
    bVar9 = *(byte *)(lVar39 + 0x40);
    if ((bVar9 & 1) == 0) {
      uVar22 = (ulong)(bVar9 >> 1);
    }
    else {
      uVar22 = *(ulong *)(lVar39 + 0x48);
    }
    bVar8 = *(byte *)(param_1 + 0x47);
    uVar48 = (ulong)(bVar8 >> 1);
    if ((bVar8 & 1) != 0) {
      uVar48 = param_1[0x48];
    }
    if ((bVar9 & 1) == 0) {
      lVar39 = lVar39 + 0x41;
    }
    else {
      lVar39 = *(long *)(lVar39 + 0x50);
    }
    uVar29 = uVar48;
    if (uVar22 <= uVar48) {
      uVar29 = uVar22;
    }
    if (uVar29 == 0) {
      if (uVar48 != uVar22) goto code_r0x018d8008;
    }
    else {
      lVar42 = param_1[0x49];
      if ((bVar8 & 1) == 0) {
        lVar42 = (long)param_1 + 0x239;
      }
      iVar15 = memcmp(lVar39,lVar42);
      if ((uVar48 != uVar22) || (iVar15 != 0)) goto code_r0x018d8008;
    }
code_r0x018d7010:
    uVar30 = 0xf;
    break;
  case 3:
    *(undefined4 *)(param_1 + 0x28) = 0x3e4ccccd;
    Aska::THashMap<string, CAssetInfo, Hasher_CSTLString, Aska::TEqualTo<string >, Aska::TAllocator<Aska::TPair<string const, CAssetInfo> > >::~THashMap()+0x70(&uStack_330);
    if (((ulong)uStack_330 & 1) == 0) {
      lVar39 = 0x16;
      puVar18 = (ulong *)((ulong)uStack_330 & 0xff);
    }
    else {
      lVar39 = ((ulong)uStack_330 & 0xfffffffffffffffe) - 1;
      puVar18 = uStack_330;
    }
    puVar19 = (ulong *)(ulong)(((uint)puVar18 & 0xfe) >> 1);
    if (((ulong)puVar18 & 1) != 0) {
      puVar19 = puStack_328;
    }
    if ((ulong)(lVar39 - (long)puVar19) < 0xf) {
      string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&uStack_330,lVar39,(byte *)((0xf - lVar39) + (long)puVar19),puVar19,puVar19,0,
                      0xf,&UNK_02866db9/*"version.version"*/);
      auVar31 = (undefined1  [8])((ulong)&uStack_330 | 1);
    }
    else {
      auVar31 = (undefined1  [8])((ulong)&uStack_330 | 1);
      uVar41 = CONCAT17(UNK_02866dc0,_UNK_02866db9);
      auVar24 = auVar31;
      if (((ulong)puVar18 & 1) != 0) {
        auVar24 = auStack_320;
      }
      *(ulong *)((byte *)((long)auVar24 + (long)puVar19) + 7) = CONCAT71(_UNK_02866dc1,UNK_02866dc0)
      ;
      *(undefined8 *)((long)auVar24 + (long)puVar19) = uVar41;
      puVar19 = (ulong *)((long)puVar19 + 0xf);
      puVar18 = puVar19;
      if (((ulong)uStack_330 & 1) == 0) {
        uStack_330 = (ulong *)CONCAT71(uStack_330._1_7_,(char)puVar19 * '\x02');
        puVar18 = puStack_328;
      }
      puStack_328 = puVar18;
      *(byte *)((long)auVar24 + (long)puVar19) = 0;
    }
    if (((ulong)uStack_330 & 1) != 0) {
      auVar31 = auStack_320;
    }
    CGameResourceDownloader::EnableDefaultErrorHandle(bool)+0xc(&puStack_110,auVar31,&UNK_02a354cc/*"version"*/);
    if (((ulong)uStack_330 & 1) != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(auStack_320);
    }
    puStack_140 = (ulong *)0x0;
    puStack_148 = (ulong *)0x0;
    puStack_150 = (ulong *)0x0;
    Aska::THashMap<string, CAssetInfo, Hasher_CSTLString, Aska::TEqualTo<string >, Aska::TAllocator<Aska::TPair<string const, CAssetInfo> > >::~THashMap()+0x70(&puStack_1f0);
    uVar41 = _UNK_02866ddc;
    if (((ulong)puStack_1f0 & 1) == 0) {
      lVar39 = 0x16;
      puVar18 = (ulong *)((ulong)puStack_1f0 & 0xff);
    }
    else {
      lVar39 = ((ulong)puStack_1f0 & 0xfffffffffffffffe) - 1;
      puVar18 = puStack_1f0;
    }
    puVar19 = (ulong *)(ulong)(((uint)puVar18 & 0xfe) >> 1);
    if (((ulong)puVar18 & 1) != 0) {
      puVar19 = puStack_1e8;
    }
    if ((ulong)(lVar39 - (long)puVar19) < 0x1b) {
      string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&puStack_1f0,lVar39,(byte *)((0x1b - lVar39) + (long)puVar19),puVar19,puVar19,
                      0,0x1b,&UNK_02866ddc/*"version_latest_Bulk.version"*/);
    }
    else {
      uVar11 = CONCAT35(_UNK_02866dec,_UNK_02866de7);
      uVar23 = CONCAT53(_UNK_02866de7,_UNK_02866de4);
      puVar25 = (ulong *)((ulong)&puStack_1f0 | 1);
      if (((ulong)puVar18 & 1) != 0) {
        puVar25 = uStack_1e0;
      }
      pbVar49 = (byte *)((long)puVar25 + (long)puVar19);
      *(undefined8 *)(pbVar49 + 0x13) = _UNK_02866def;
      *(undefined8 *)(pbVar49 + 0xb) = uVar11;
      *(undefined8 *)(pbVar49 + 8) = uVar23;
      *(undefined8 *)pbVar49 = uVar41;
      puVar19 = (ulong *)((long)puVar19 + 0x1b);
      puVar32 = puVar19;
      if (((ulong)puVar18 & 1) == 0) {
        puStack_1f0 = (ulong *)CONCAT71(puStack_1f0._1_7_,(char)puVar19 * '\x02');
        puVar32 = puStack_1e8;
      }
      puStack_1e8 = puVar32;
      *(byte *)((long)puVar25 + (long)puVar19) = 0;
    }
    puVar19 = puStack_150;
    puStack_328 = puStack_1e8;
    uStack_330 = puStack_1f0;
    puVar18 = (ulong *)((ulong)&uStack_330 | 1);
    if (((ulong)puStack_1f0 & 1) != 0) {
      puVar18 = uStack_1e0;
    }
    auStack_320 = (undefined1  [8])uStack_1e0;
    CGameResourceDownloader::EnableDefaultErrorHandle(bool)+0xc(&puStack_1f0,puVar18,&UNK_02a354cc/*"version"*/);
    if (((ulong)puVar19 & 1) == 0) {
      puStack_150 = (ulong *)((ulong)puStack_150 & 0xffffffffffff0000);
    }
    else {
      *(undefined1 *)puStack_140 = 0;
      puStack_148 = (ulong *)0x0;
    }
    string::reserve(unsigned long)(&puStack_150,0);
    puStack_148 = puStack_1e8;
    puStack_150 = puStack_1f0;
    puStack_140 = uStack_1e0;
    if (((ulong)uStack_330 & 1) != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(auStack_320);
    }
    pbVar49 = (byte *)(param_1 + 0x4a);
    if ((*(byte *)(param_1 + 0x4a) & 1) == 0) {
      pbVar49[0] = 0;
      pbVar49[1] = 0;
    }
    else {
      *(undefined1 *)param_1[0x4c] = 0;
      param_1[0x4b] = 0;
    }
    string::reserve(unsigned long)(pbVar49,0);
    param_1[0x4c] = (long)puStack_140;
    param_1[0x4b] = (long)puStack_148;
    *(ulong **)pbVar49 = puStack_150;
    BAS::GetDownloadPath()(&uStack_330);
    if (((ulong)uStack_330 & 1) == 0) {
      puVar19 = (ulong *)0x16;
      puVar18 = (ulong *)((ulong)uStack_330 & 0xff);
    }
    else {
      puVar19 = (ulong *)(((ulong)uStack_330 & 0xfffffffffffffffe) - 1);
      puVar18 = uStack_330;
    }
    puVar25 = (ulong *)(ulong)(((uint)puVar18 & 0xfe) >> 1);
    if (((ulong)puVar18 & 1) != 0) {
      puVar25 = puStack_328;
    }
    if (puVar19 == puVar25) {
      string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&uStack_330,puVar19,1,puVar19,puVar19,0,1,&UNK_029c5d3e/*"/"*/);
    }
    else {
      auVar24 = (undefined1  [8])((ulong)&uStack_330 | 1);
      if (((ulong)puVar18 & 1) != 0) {
        auVar24 = auStack_320;
      }
      *(byte *)((long)auVar24 + (long)puVar25) = 0x2f;
      puVar25 = (ulong *)((long)puVar25 + 1);
      puVar18 = puVar25;
      if (((ulong)uStack_330 & 1) == 0) {
        uStack_330 = (ulong *)CONCAT71(uStack_330._1_7_,(char)puVar25 * '\x02');
        puVar18 = puStack_328;
      }
      puStack_328 = puVar18;
      *(byte *)((long)auVar24 + (long)puVar25) = 0;
    }
    CGameResourceDownloader::CDownloadNode::UnpackNotify::ResetDispatchCount()+0x10(&puStack_150);
    uVar41 = _UNK_02866ddc;
    if (((ulong)puStack_150 & 1) == 0) {
      lVar39 = 0x16;
      puVar18 = (ulong *)((ulong)puStack_150 & 0xff);
    }
    else {
      lVar39 = ((ulong)puStack_150 & 0xfffffffffffffffe) - 1;
      puVar18 = puStack_150;
    }
    puVar19 = (ulong *)(ulong)(((uint)puVar18 & 0xfe) >> 1);
    if (((ulong)puVar18 & 1) != 0) {
      puVar19 = puStack_148;
    }
    if ((ulong)(lVar39 - (long)puVar19) < 0x1b) {
      string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&puStack_150,lVar39,(byte *)((0x1b - lVar39) + (long)puVar19),puVar19,puVar19,
                      0,0x1b,&UNK_02866ddc/*"version_latest_Bulk.version"*/);
    }
    else {
      uVar11 = CONCAT35(_UNK_02866dec,_UNK_02866de7);
      uVar23 = CONCAT53(_UNK_02866de7,_UNK_02866de4);
      puVar25 = (ulong *)((ulong)&puStack_150 | 1);
      if (((ulong)puVar18 & 1) != 0) {
        puVar25 = puStack_140;
      }
      pbVar44 = (byte *)((long)puVar25 + (long)puVar19);
      *(undefined8 *)(pbVar44 + 0x13) = _UNK_02866def;
      *(undefined8 *)(pbVar44 + 0xb) = uVar11;
      *(undefined8 *)(pbVar44 + 8) = uVar23;
      *(undefined8 *)pbVar44 = uVar41;
      puVar19 = (ulong *)((long)puVar19 + 0x1b);
      puVar32 = puVar19;
      if (((ulong)puVar18 & 1) == 0) {
        puStack_150 = (ulong *)CONCAT71(puStack_150._1_7_,(char)puVar19 * '\x02');
        puVar32 = puStack_148;
      }
      puStack_148 = puVar32;
      *(byte *)((long)puVar25 + (long)puVar19) = 0;
    }
    uStack_1e0 = puStack_140;
    puStack_1e8 = puStack_148;
    puStack_1f0 = puStack_150;
    puStack_140 = (ulong *)0x0;
    bVar14 = ((ulong)puStack_150 & 1) != 0;
    puVar18 = (ulong *)((ulong)&puStack_1f0 | 1);
    if (bVar14) {
      puVar18 = uStack_1e0;
    }
    puVar19 = (ulong *)((ulong)puStack_150 >> 1 & 0x7f);
    if (bVar14) {
      puVar19 = puStack_148;
    }
    puStack_150 = (ulong *)0x0;
    puStack_148 = (ulong *)0x0;
    if (((ulong)uStack_330 & 1) == 0) {
      lVar39 = 0x16;
      puVar25 = (ulong *)((ulong)uStack_330 & 0xff);
    }
    else {
      lVar39 = ((ulong)uStack_330 & 0xfffffffffffffffe) - 1;
      puVar25 = uStack_330;
    }
    puVar32 = (ulong *)(ulong)(((uint)puVar25 & 0xfe) >> 1);
    if (((ulong)puVar25 & 1) != 0) {
      puVar32 = puStack_328;
    }
    if ((ulong *)(lVar39 - (long)puVar32) < puVar19) {
      string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&uStack_330,lVar39,(byte *)(((long)puVar19 - lVar39) + (long)puVar32),puVar32,
                      puVar32,0,puVar19);
    }
    else if (puVar19 != (ulong *)0x0) {
      auVar24 = (undefined1  [8])((ulong)&uStack_330 | 1);
      if (((ulong)puVar25 & 1) != 0) {
        auVar24 = auStack_320;
      }
      memcpy((byte *)((long)auVar24 + (long)puVar32),puVar18,puVar19);
      puVar32 = (ulong *)((long)puVar32 + (long)puVar19);
      if (((ulong)uStack_330 & 1) == 0) {
        uStack_330 = (ulong *)CONCAT71(uStack_330._1_7_,(char)puVar32 * '\x02');
        *(byte *)((long)auVar24 + (long)puVar32) = 0;
      }
      else {
        *(byte *)((long)auVar24 + (long)puVar32) = 0;
        puStack_328 = puVar32;
      }
    }
    if (((ulong)puStack_1f0 & 1) != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_1e0);
    }
    if (((ulong)puStack_150 & 1) != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puStack_140);
    }
    auVar24 = (undefined1  [8])((ulong)&uStack_330 | 1);
    if (((ulong)uStack_330 & 1) != 0) {
      auVar24 = auStack_320;
    }
    CGameResourceDownloader::EnableDefaultErrorHandle(bool)+0xc(&puStack_1f0,auVar24,&UNK_02866e1a/*"totalSize"*/);
    uVar22 = Framework::CSTLStringUtility_Base<string >::IsDigits(string const&, bool, float*, double*)(&puStack_1f0,0,0,0);
    iVar15 = 0;
    if ((uVar22 & 1) != 0) {
      dVar52 = (double)Framework::CSTLStringUtility_Base<string >::AToDoubleWithTrimming(string const&)(&puStack_1f0);
      iVar15 = (int)dVar52;
    }
    if (((ulong)puStack_1f0 & 1) != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_1e0);
    }
    if (((ulong)uStack_330 & 1) != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(auStack_320);
    }
    bVar9 = *(byte *)(param_1 + 0x4a);
    *(int *)((long)param_1 + 0x26c) = iVar15;
    if ((bVar9 & 1) == 0) {
      puVar18 = (ulong *)(ulong)(bVar9 >> 1);
    }
    else {
      puVar18 = (ulong *)param_1[0x4b];
    }
    puVar19 = (ulong *)((ulong)puStack_110 >> 1 & 0x7f);
    if (((ulong)puStack_110 & 1) != 0) {
      puVar19 = puStack_108;
    }
    if ((bVar9 & 1) == 0) {
      lVar39 = (long)param_1 + 0x251;
    }
    else {
      lVar39 = param_1[0x4c];
    }
    puVar25 = puVar19;
    if (puVar18 <= puVar19) {
      puVar25 = puVar18;
    }
    if (puVar25 == (ulong *)0x0) {
code_r0x018d7474:
      uVar16 = (uint)(puVar19 < puVar18);
      if (puVar18 < puVar19) {
        uVar16 = 0xffffffff;
      }
    }
    else {
      puVar25 = (ulong *)((ulong)&puStack_110 | 1);
      if (((ulong)puStack_110 & 1) != 0) {
        puVar25 = puStack_100;
      }
      uVar16 = memcmp(lVar39,puVar25);
      if (uVar16 == 0) goto code_r0x018d7474;
    }
    *(bool *)(param_1 + 0xb3) = uVar16 == 0;
    CGameResourceDownloader::CheckLocalResourceFileToolVersionOld()+0x354(&uStack_330);
    uVar41 = _UNK_02866d7e;
    if (((ulong)uStack_330 & 1) == 0) {
      lVar39 = 0x16;
      puVar18 = (ulong *)((ulong)uStack_330 & 0xff);
    }
    else {
      lVar39 = ((ulong)uStack_330 & 0xfffffffffffffffe) - 1;
      puVar18 = uStack_330;
    }
    puVar19 = (ulong *)(ulong)(((uint)puVar18 & 0xfe) >> 1);
    if (((ulong)puVar18 & 1) != 0) {
      puVar19 = puStack_328;
    }
    if ((ulong)(lVar39 - (long)puVar19) < 0x17) {
      string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&uStack_330,lVar39,(byte *)((0x17 - lVar39) + (long)puVar19),puVar19,puVar19,0
                      ,0x17,&UNK_02866d7e/*"version_latest_Bulk.bin"*/);
    }
    else {
      uVar23 = CONCAT17(UNK_02866d8d,_UNK_02866d86);
      auVar24 = (undefined1  [8])((ulong)&uStack_330 | 1);
      if (((ulong)puVar18 & 1) != 0) {
        auVar24 = auStack_320;
      }
      pbVar44 = (byte *)((long)auVar24 + (long)puVar19);
      *(ulong *)(pbVar44 + 0xf) = CONCAT71(_UNK_02866d8e,UNK_02866d8d);
      *(undefined8 *)(pbVar44 + 8) = uVar23;
      *(undefined8 *)pbVar44 = uVar41;
      puVar19 = (ulong *)((long)puVar19 + 0x17);
      puVar18 = puVar19;
      if (((ulong)uStack_330 & 1) == 0) {
        uStack_330 = (ulong *)CONCAT71(uStack_330._1_7_,(char)puVar19 * '\x02');
        puVar18 = puStack_328;
      }
      puStack_328 = puVar18;
      *(byte *)((long)auVar24 + (long)puVar19) = 0;
    }
    uStack_1e0 = (ulong *)auStack_320;
    puStack_1e8 = puStack_328;
    puStack_1f0 = uStack_330;
    CGameResourceDownloader::CheckLocalResourceFileToolVersionOld()+0x354(&uStack_330);
    uVar41 = _UNK_02866e24;
    if (((ulong)uStack_330 & 1) == 0) {
      lVar39 = 0x16;
      puVar18 = (ulong *)((ulong)uStack_330 & 0xff);
    }
    else {
      lVar39 = ((ulong)uStack_330 & 0xfffffffffffffffe) - 1;
      puVar18 = uStack_330;
    }
    puVar19 = (ulong *)(ulong)(((uint)puVar18 & 0xfe) >> 1);
    if (((ulong)puVar18 & 1) != 0) {
      puVar19 = puStack_328;
    }
    if ((ulong)(lVar39 - (long)puVar19) < 0x1d) {
      string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&uStack_330,lVar39,(byte *)((0x1d - lVar39) + (long)puVar19),puVar19,puVar19,0
                      ,0x1d,&UNK_02866e24/*"version_latest_Individual.bin"*/);
    }
    else {
      uVar11 = CONCAT53(_UNK_02866e34,_UNK_02866e31);
      uVar23 = CONCAT35(_UNK_02866e31,_UNK_02866e2c);
      auVar24 = (undefined1  [8])((ulong)&uStack_330 | 1);
      if (((ulong)puVar18 & 1) != 0) {
        auVar24 = auStack_320;
      }
      pbVar44 = (byte *)((long)auVar24 + (long)puVar19);
      *(undefined8 *)(pbVar44 + 0x15) = _UNK_02866e39;
      *(undefined8 *)(pbVar44 + 0xd) = uVar11;
      *(undefined8 *)(pbVar44 + 8) = uVar23;
      *(undefined8 *)pbVar44 = uVar41;
      puVar19 = (ulong *)((long)puVar19 + 0x1d);
      puVar25 = puVar19;
      if (((ulong)puVar18 & 1) == 0) {
        uStack_330 = (ulong *)CONCAT71(uStack_330._1_7_,(char)puVar19 * '\x02');
        puVar25 = puStack_328;
      }
      puStack_328 = puVar25;
      *(byte *)((long)auVar24 + (long)puVar19) = 0;
    }
    puStack_228 = (ulong *)0x0;
    puStack_220 = (ulong *)0x0;
    puStack_230 = (ulong *)0x0;
    puStack_70 = (ulong *)0x0;
    puStack_78 = (ulong *)0x0;
    puStack_140 = (ulong *)auStack_320;
    puStack_148 = puStack_328;
    puStack_150 = uStack_330;
    puStack_80 = (ulong *)0x0;
    if ((int)param_1[0x4f] != 0) {
      uVar16 = 0;
      do {
        CGameResourceDownloader::CheckLocalResourceFileToolVersionOld()+0x354(&puStack_a0);
        uVar16 = uVar16 + 1;
        Framework::CSTLStringUtility_Base<string >::Format(char const*, ...)(&puStack_c0,&UNK_02866b05/*"version_latest_ep%d.bin"*/,uVar16);
        puVar18 = (ulong *)((ulong)puStack_c0 >> 1 & 0x7f);
        puVar19 = (ulong *)((ulong)&puStack_c0 | 1);
        if (((ulong)puStack_c0 & 1) != 0) {
          puVar18 = puStack_b8;
          puVar19 = puStack_b0;
        }
        if (((ulong)puStack_a0 & 1) == 0) {
          lVar39 = 0x16;
          puVar25 = (ulong *)((ulong)puStack_a0 & 0xff);
        }
        else {
          lVar39 = ((ulong)puStack_a0 & 0xfffffffffffffffe) - 1;
          puVar25 = puStack_a0;
        }
        puVar32 = (ulong *)(ulong)(((uint)puVar25 & 0xfe) >> 1);
        if (((ulong)puVar25 & 1) != 0) {
          puVar32 = puStack_98;
        }
        if ((ulong *)(lVar39 - (long)puVar32) < puVar18) {
          string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&puStack_a0,lVar39,(byte *)(((long)puVar18 - lVar39) + (long)puVar32),
                          puVar32,puVar32,0,puVar18);
        }
        else if (puVar18 != (ulong *)0x0) {
          puVar3 = (ulong *)((ulong)&puStack_a0 | 1);
          if (((ulong)puVar25 & 1) != 0) {
            puVar3 = puStack_90;
          }
          memcpy((byte *)((long)puVar3 + (long)puVar32),puVar19,puVar18);
          puVar32 = (ulong *)((long)puVar32 + (long)puVar18);
          puVar18 = puVar32;
          if (((ulong)puStack_a0 & 1) == 0) {
            puStack_a0 = (ulong *)CONCAT71(puStack_a0._1_7_,(char)puVar32 * '\x02');
            puVar18 = puStack_98;
          }
          puStack_98 = puVar18;
          *(byte *)((long)puVar3 + (long)puVar32) = 0;
        }
        auStack_320 = (undefined1  [8])puStack_90;
        uStack_330 = puStack_a0;
        puStack_90 = (ulong *)0x0;
        puStack_a0 = (ulong *)0x0;
        puStack_328 = puStack_98;
        puStack_98 = (ulong *)0x0;
        if ((((ulong)puStack_c0 & 1) != 0) &&
           (Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puStack_b0), ((ulong)puStack_a0 & 1) != 0)) {
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puStack_90);
        }
        puVar18 = puStack_228;
        if (puStack_228 == puStack_220) {
          void std::__ndk1::vector<string, Framework::CSTLAllocator<string, Framework::CSTLVectorAllocatorInf> >::__push_back_slow_path<string const&>(string const&)(&puStack_230,&uStack_330);
        }
        else {
          if (puStack_228 == (ulong *)0x0) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
          }
          auVar24 = auStack_320;
          puVar19 = puStack_328;
          puVar18[1] = 0;
          puVar18[2] = 0;
          *puVar18 = 0;
          if (((ulong)uStack_330 & 1) == 0) {
            puVar18[2] = (ulong)auStack_320;
            puVar18[1] = (ulong)puStack_328;
            *puVar18 = (ulong)uStack_330;
          }
          else {
            if (puStack_328 < (ulong *)0x17) {
              pbVar44 = (byte *)((long)puVar18 + 1);
              *(byte *)puVar18 = (byte)((long)puStack_328 << 1);
              if (puStack_328 != (ulong *)0x0) goto code_r0x018d7878;
            }
            else {
              uVar22 = (ulong)(puStack_328 + 2) & 0xfffffffffffffff0;
              if (uVar22 == 0) {
                Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
              }
              pbVar44 = (byte *)Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar22,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
              if (pbVar44 == (byte *)0x0) {
                Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
              }
              puVar18[1] = (ulong)puVar19;
              puVar18[2] = (ulong)pbVar44;
              *puVar18 = uVar22 | 1;
code_r0x018d7878:
              memcpy(pbVar44,auVar24,puVar19);
            }
            pbVar44[(long)puVar19] = 0;
          }
          puStack_228 = puStack_228 + 3;
        }
        CGameResourceDownloader::CheckLocalResourceFileToolVersionOld()+0x354(&puStack_c0);
        Framework::CSTLStringUtility_Base<string >::Format(char const*, ...)(&puStack_e0,&UNK_02866b31/*"version_latest_ep%d.version"*/,uVar16);
        puVar18 = (ulong *)((ulong)puStack_e0 >> 1 & 0x7f);
        puVar19 = (ulong *)((ulong)&puStack_e0 | 1);
        if (((ulong)puStack_e0 & 1) != 0) {
          puVar18 = puStack_d8;
          puVar19 = puStack_d0;
        }
        if (((ulong)puStack_c0 & 1) == 0) {
          lVar39 = 0x16;
          puVar25 = (ulong *)((ulong)puStack_c0 & 0xff);
        }
        else {
          lVar39 = ((ulong)puStack_c0 & 0xfffffffffffffffe) - 1;
          puVar25 = puStack_c0;
        }
        puVar32 = (ulong *)(ulong)(((uint)puVar25 & 0xfe) >> 1);
        if (((ulong)puVar25 & 1) != 0) {
          puVar32 = puStack_b8;
        }
        if ((ulong)(lVar39 - (long)puVar32) < puVar18) {
          string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&puStack_c0,lVar39,(byte *)(((long)puVar18 - lVar39) + (long)puVar32),
                          puVar32,puVar32,0,puVar18);
        }
        else if (puVar18 != (ulong *)0x0) {
          puVar3 = (ulong *)((ulong)&puStack_c0 | 1);
          if (((ulong)puVar25 & 1) != 0) {
            puVar3 = puStack_b0;
          }
          memcpy((byte *)((long)puVar3 + (long)puVar32),puVar19,puVar18);
          puVar32 = (ulong *)((long)puVar32 + (long)puVar18);
          puVar18 = puVar32;
          if (((ulong)puStack_c0 & 1) == 0) {
            puStack_c0 = (ulong *)CONCAT71(puStack_c0._1_7_,(char)puVar32 * '\x02');
            puVar18 = puStack_b8;
          }
          puStack_b8 = puVar18;
          *(byte *)((long)puVar3 + (long)puVar32) = 0;
        }
        puStack_90 = puStack_b0;
        puStack_a0 = puStack_c0;
        puStack_b0 = (ulong *)0x0;
        puStack_c0 = (ulong *)0x0;
        puStack_98 = puStack_b8;
        puStack_b8 = (ulong *)0x0;
        if ((((ulong)puStack_e0 & 1) != 0) &&
           (Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puStack_d0), ((ulong)puStack_c0 & 1) != 0)) {
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puStack_b0);
        }
        puVar18 = puStack_78;
        if (puStack_78 == puStack_70) {
          void std::__ndk1::vector<string, Framework::CSTLAllocator<string, Framework::CSTLVectorAllocatorInf> >::__push_back_slow_path<string const&>(string const&)(&puStack_80,&puStack_a0);
        }
        else {
          if (puStack_78 == (ulong *)0x0) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
          }
          puVar25 = puStack_90;
          puVar19 = puStack_98;
          puVar18[1] = 0;
          puVar18[2] = 0;
          *puVar18 = 0;
          if (((ulong)puStack_a0 & 1) == 0) {
            puVar18[2] = (ulong)puStack_90;
            puVar18[1] = (ulong)puStack_98;
            *puVar18 = (ulong)puStack_a0;
          }
          else {
            if (puStack_98 < (ulong *)0x17) {
              pbVar44 = (byte *)((long)puVar18 + 1);
              *(byte *)puVar18 = (byte)((long)puStack_98 << 1);
              if (puStack_98 != (ulong *)0x0) goto code_r0x018d7a9c;
            }
            else {
              uVar22 = (ulong)(puStack_98 + 2) & 0xfffffffffffffff0;
              if (uVar22 == 0) {
                Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
              }
              pbVar44 = (byte *)Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar22,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
              if (pbVar44 == (byte *)0x0) {
                Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
              }
              puVar18[1] = (ulong)puVar19;
              puVar18[2] = (ulong)pbVar44;
              *puVar18 = uVar22 | 1;
code_r0x018d7a9c:
              memcpy(pbVar44,puVar25,puVar19);
            }
            pbVar44[(long)puVar19] = 0;
          }
          puStack_78 = puStack_78 + 3;
        }
        if (((ulong)puStack_a0 & 1) != 0) {
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puStack_90);
        }
        if (((ulong)uStack_330 & 1) != 0) {
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(auStack_320);
        }
      } while (uVar16 < *(uint *)(param_1 + 0x4f));
    }
    if (*(char *)((long)param_1 + 0x155) != '\0') {
      if ((char)param_1[0xb3] == '\0') {
code_r0x018daa18:
        puVar19 = uStack_1e0;
        puVar18 = puStack_1f0;
        lVar39 = operator new(unsigned long, std::nothrow_t const&)(0x450,PTR__ZSt7nothrow_02cb9a80);
        if (lVar39 != 0) {
          puVar25 = (ulong *)((ulong)&puStack_1f0 | 1);
          if (((ulong)puVar18 & 1) != 0) {
            puVar25 = puVar19;
          }
          plStack_310 = (long *)0x0;
          CGameResourceDownloader::CDownloadNode::CDownloadNode(char const*, std::__ndk1::function<void (char const*, CGameResourceDownloader::iErrorCode)>)(lVar39,puVar25,&uStack_330);
          if (&uStack_330 == plStack_310) {
            pcVar33 = *(code **)(*plStack_310 + 0x20);
          }
          else {
            if (plStack_310 == (long *)0x0) goto code_r0x018daa84;
            pcVar33 = *(code **)(*plStack_310 + 0x28);
          }
          (*pcVar33)();
        }
code_r0x018daa84:
        lVar42 = param_1[0xb];
        if (-1 < lVar42) {
          Aska::TArray<CGameResourceDownloader::CDownloadNode*, false>::Resize(long, bool)(param_1 + 8,lVar42 + 1,0);
          *(long *)(param_1[9] + lVar42 * 8) = lVar39;
        }
        if (*(int *)(lVar39 + 8) != 5) {
          *(undefined1 *)(lVar39 + 0x150) = 1;
          *(undefined8 *)(lVar39 + 8) = 1;
        }
        lVar42 = param_1[0x12];
        if (-1 < lVar42) {
          Aska::TArray<CGameResourceDownloader::CDownloadNode*, false>::Resize(long, bool)(param_1 + 0xf,lVar42 + 1,0);
          *(long *)(param_1[0x10] + lVar42 * 8) = lVar39;
        }
        puVar19 = puStack_140;
        puVar18 = puStack_150;
        lVar39 = operator new(unsigned long, std::nothrow_t const&)(0x450,PTR__ZSt7nothrow_02cb9a80);
        if (lVar39 != 0) {
          puVar25 = (ulong *)((ulong)&puStack_150 | 1);
          if (((ulong)puVar18 & 1) != 0) {
            puVar25 = puVar19;
          }
          plStack_310 = (long *)0x0;
          CGameResourceDownloader::CDownloadNode::CDownloadNode(char const*, std::__ndk1::function<void (char const*, CGameResourceDownloader::iErrorCode)>)(lVar39,puVar25,&uStack_330);
          if (&uStack_330 == plStack_310) {
            pcVar33 = *(code **)(*plStack_310 + 0x20);
          }
          else {
            if (plStack_310 == (long *)0x0) goto code_r0x018dab48;
            pcVar33 = *(code **)(*plStack_310 + 0x28);
          }
          (*pcVar33)();
        }
code_r0x018dab48:
        lVar42 = param_1[0xb];
        if (-1 < lVar42) {
          Aska::TArray<CGameResourceDownloader::CDownloadNode*, false>::Resize(long, bool)(param_1 + 8,lVar42 + 1,0);
          *(long *)(param_1[9] + lVar42 * 8) = lVar39;
        }
        if (*(int *)(lVar39 + 8) != 5) {
          *(undefined1 *)(lVar39 + 0x150) = 1;
          *(undefined8 *)(lVar39 + 8) = 1;
        }
        lVar42 = param_1[0x12];
        if (-1 < lVar42) {
          Aska::TArray<CGameResourceDownloader::CDownloadNode*, false>::Resize(long, bool)(param_1 + 0xf,lVar42 + 1,0);
          *(long *)(param_1[0x10] + lVar42 * 8) = lVar39;
        }
      }
      else {
        BAS::GetDownloadPath()(&uStack_330);
        if (((ulong)uStack_330 & 1) == 0) {
          puVar19 = (ulong *)0x16;
          puVar18 = (ulong *)((ulong)uStack_330 & 0xff);
        }
        else {
          puVar19 = (ulong *)(((ulong)uStack_330 & 0xfffffffffffffffe) - 1);
          puVar18 = uStack_330;
        }
        puVar25 = (ulong *)(ulong)(((uint)puVar18 & 0xfe) >> 1);
        if (((ulong)puVar18 & 1) != 0) {
          puVar25 = puStack_328;
        }
        if (puVar19 == puVar25) {
          string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&uStack_330,puVar19,1,puVar19,puVar19,0,1,&UNK_029c5d3e/*"/"*/);
        }
        else {
          auVar24 = (undefined1  [8])((ulong)&uStack_330 | 1);
          if (((ulong)puVar18 & 1) != 0) {
            auVar24 = auStack_320;
          }
          *(byte *)((long)auVar24 + (long)puVar25) = 0x2f;
          puVar25 = (ulong *)((long)puVar25 + 1);
          puVar18 = puVar25;
          if (((ulong)uStack_330 & 1) == 0) {
            uStack_330 = (ulong *)CONCAT71(uStack_330._1_7_,(char)puVar25 * '\x02');
            puVar18 = puStack_328;
          }
          puStack_328 = puVar18;
          *(byte *)((long)auVar24 + (long)puVar25) = 0;
        }
        puStack_b8 = puStack_328;
        puStack_c0 = uStack_330;
        puStack_b0 = (ulong *)auStack_320;
        puVar18 = (ulong *)((ulong)puStack_1f0 >> 1 & 0x7f);
        puVar19 = (ulong *)((ulong)&puStack_1f0 | 1);
        if (((ulong)puStack_1f0 & 1) != 0) {
          puVar18 = puStack_1e8;
          puVar19 = uStack_1e0;
        }
        if (((ulong)uStack_330 & 1) == 0) {
          lVar39 = 0x16;
          puVar25 = (ulong *)((ulong)uStack_330 & 0xff);
        }
        else {
          lVar39 = ((ulong)uStack_330 & 0xfffffffffffffffe) - 1;
          puVar25 = uStack_330;
        }
        puVar32 = (ulong *)(ulong)(((uint)puVar25 & 0xfe) >> 1);
        if (((ulong)puVar25 & 1) != 0) {
          puVar32 = puStack_328;
        }
        if ((ulong *)(lVar39 - (long)puVar32) < puVar18) {
          string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&puStack_c0,lVar39,(byte *)(((long)puVar18 - lVar39) + (long)puVar32),
                          puVar32,puVar32,0,puVar18);
        }
        else if (puVar18 != (ulong *)0x0) {
          auVar24 = (undefined1  [8])((ulong)&puStack_c0 | 1);
          if (((ulong)puVar25 & 1) != 0) {
            auVar24 = auStack_320;
          }
          memcpy((byte *)((long)auVar24 + (long)puVar32),puVar19,puVar18);
          puVar32 = (ulong *)((long)puVar32 + (long)puVar18);
          puVar18 = puVar32;
          if (((ulong)puStack_c0 & 1) == 0) {
            puStack_c0 = (ulong *)CONCAT71(puStack_c0._1_7_,(char)puVar32 * '\x02');
            puVar18 = puStack_b8;
          }
          puStack_b8 = puVar18;
          *(byte *)((long)auVar24 + (long)puVar32) = 0;
        }
        puVar19 = puStack_b0;
        puVar18 = puStack_c0;
        puStack_c0 = (ulong *)0x0;
        puStack_b0 = (ulong *)0x0;
        puStack_98 = puStack_b8;
        puStack_a0 = puVar18;
        puStack_90 = puVar19;
        puStack_b8 = (ulong *)0x0;
        if (((ulong)puVar18 & 1) == 0) {
          puVar19 = (ulong *)((ulong)&puStack_a0 | 1);
code_r0x018d95bc:
          iVar15 = access(puVar19,0);
          if (iVar15 == 0) {
            BAS::GetDownloadPath()(&uStack_330);
            if (((ulong)uStack_330 & 1) == 0) {
              puVar25 = (ulong *)0x16;
              puVar19 = (ulong *)((ulong)uStack_330 & 0xff);
            }
            else {
              puVar25 = (ulong *)(((ulong)uStack_330 & 0xfffffffffffffffe) - 1);
              puVar19 = uStack_330;
            }
            puVar32 = (ulong *)(ulong)(((uint)puVar19 & 0xfe) >> 1);
            if (((ulong)puVar19 & 1) != 0) {
              puVar32 = puStack_328;
            }
            if (puVar25 == puVar32) {
              string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&uStack_330,puVar25,1,puVar25,puVar25,0,1,&UNK_029c5d3e/*"/"*/);
            }
            else {
              auVar24 = (undefined1  [8])((ulong)&uStack_330 | 1);
              if (((ulong)puVar19 & 1) != 0) {
                auVar24 = auStack_320;
              }
              *(byte *)((long)auVar24 + (long)puVar32) = 0x2f;
              puVar32 = (ulong *)((long)puVar32 + 1);
              puVar19 = puVar32;
              if (((ulong)uStack_330 & 1) == 0) {
                uStack_330 = (ulong *)CONCAT71(uStack_330._1_7_,(char)puVar32 * '\x02');
                puVar19 = puStack_328;
              }
              puStack_328 = puVar19;
              *(byte *)((long)auVar24 + (long)puVar32) = 0;
            }
            puStack_d8 = puStack_328;
            puStack_e0 = uStack_330;
            puStack_d0 = (ulong *)auStack_320;
            puVar19 = (ulong *)((ulong)puStack_150 >> 1 & 0x7f);
            puVar25 = (ulong *)((ulong)&puStack_150 | 1);
            if (((ulong)puStack_150 & 1) != 0) {
              puVar19 = puStack_148;
              puVar25 = puStack_140;
            }
            if (((ulong)uStack_330 & 1) == 0) {
              lVar39 = 0x16;
              puVar32 = (ulong *)((ulong)uStack_330 & 0xff);
            }
            else {
              lVar39 = ((ulong)uStack_330 & 0xfffffffffffffffe) - 1;
              puVar32 = uStack_330;
            }
            puVar3 = (ulong *)(ulong)(((uint)puVar32 & 0xfe) >> 1);
            if (((ulong)puVar32 & 1) != 0) {
              puVar3 = puStack_328;
            }
            if ((ulong *)(lVar39 - (long)puVar3) < puVar19) {
              string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&puStack_e0,lVar39,(byte *)(((long)puVar19 - lVar39) + (long)puVar3),
                              puVar3,puVar3,0,puVar19);
            }
            else if (puVar19 != (ulong *)0x0) {
              auVar24 = (undefined1  [8])((ulong)&puStack_e0 | 1);
              if (((ulong)puVar32 & 1) != 0) {
                auVar24 = auStack_320;
              }
              memcpy((byte *)((long)auVar24 + (long)puVar3),puVar25,puVar19);
              puVar3 = (ulong *)((long)puVar3 + (long)puVar19);
              puVar19 = puVar3;
              if (((ulong)puStack_e0 & 1) == 0) {
                puStack_e0 = (ulong *)CONCAT71(puStack_e0._1_7_,(char)puVar3 * '\x02');
                puVar19 = puStack_d8;
              }
              puStack_d8 = puVar19;
              *(byte *)((long)auVar24 + (long)puVar3) = 0;
            }
            auStack_320 = (undefined1  [8])puStack_d0;
            uStack_330 = puStack_e0;
            puStack_e0 = (ulong *)0x0;
            puStack_d0 = (ulong *)0x0;
            puStack_328 = puStack_d8;
            puStack_d8 = (ulong *)0x0;
            if (((ulong)uStack_330 & 1) == 0) {
              iVar15 = access((ulong)&uStack_330 | 1,0);
              bVar14 = iVar15 != 0;
            }
            else {
              if (auStack_320 == (undefined1  [8])0x0) {
                bVar14 = true;
              }
              else {
                iVar15 = access(auStack_320,0);
                bVar14 = iVar15 != 0;
              }
              Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(auStack_320);
            }
            if (((ulong)puStack_e0 & 1) != 0) {
              Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puStack_d0);
            }
          }
          else {
            bVar14 = true;
          }
          if (((ulong)puVar18 & 1) != 0) goto code_r0x018da9fc;
          if (((ulong)puStack_c0 & 1) != 0) goto code_r0x018daa0c;
code_r0x018da9f4:
          if (bVar14) goto code_r0x018daa18;
        }
        else {
          if (puVar19 != (ulong *)0x0) goto code_r0x018d95bc;
          bVar14 = true;
code_r0x018da9fc:
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puStack_90);
          if (((ulong)puStack_c0 & 1) == 0) goto code_r0x018da9f4;
code_r0x018daa0c:
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puStack_b0);
          if (bVar14) goto code_r0x018daa18;
        }
      }
      puVar1 = PTR__ZSt7nothrow_02cb9a80;
      if ((int)param_1[0x4f] != 0) {
        uVar22 = 0;
        do {
          if ((ulong)param_1[0xb7] <= uVar22) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dc536/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Vector.h"*/,0x58,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,uVar22);
          }
          if ((*(ulong *)(param_1[0xb6] + (uVar22 >> 3 & 0x1ffffff8)) & 1L << (uVar22 & 0x3f)) != 0)
          {
            BAS::GetDownloadPath()(&uStack_330);
            if (((ulong)uStack_330 & 1) == 0) {
              puVar19 = (ulong *)0x16;
              puVar18 = (ulong *)((ulong)uStack_330 & 0xff);
            }
            else {
              puVar19 = (ulong *)(((ulong)uStack_330 & 0xfffffffffffffffe) - 1);
              puVar18 = uStack_330;
            }
            puVar25 = (ulong *)(ulong)(((uint)puVar18 & 0xfe) >> 1);
            if (((ulong)puVar18 & 1) != 0) {
              puVar25 = puStack_328;
            }
            if (puVar19 == puVar25) {
              string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&uStack_330,puVar19,1,puVar19,puVar19,0,1,&UNK_029c5d3e/*"/"*/);
            }
            else {
              auVar24 = (undefined1  [8])((ulong)&uStack_330 | 1);
              if (((ulong)puVar18 & 1) != 0) {
                auVar24 = auStack_320;
              }
              *(byte *)((long)auVar24 + (long)puVar25) = 0x2f;
              puVar25 = (ulong *)((long)puVar25 + 1);
              puVar18 = puVar25;
              if (((ulong)uStack_330 & 1) == 0) {
                uStack_330 = (ulong *)CONCAT71(uStack_330._1_7_,(char)puVar25 * '\x02');
                puVar18 = puStack_328;
              }
              puStack_328 = puVar18;
              *(byte *)((long)auVar24 + (long)puVar25) = 0;
            }
            puStack_b0 = (ulong *)auStack_320;
            uVar48 = ((long)puStack_228 - (long)puStack_230 >> 3) * -0x5555555555555555;
            puStack_b8 = puStack_328;
            puStack_c0 = uStack_330;
            if (uVar48 < uVar22 || uVar48 - uVar22 == 0) {
              Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dc536/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Vector.h"*/,0x58,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,uVar22);
            }
            puVar18 = puStack_230 + uVar22 * 3;
            uVar48 = puVar18[1];
            pbVar44 = (byte *)puVar18[2];
            if (((byte)*puVar18 & 1) == 0) {
              pbVar44 = (byte *)((long)puVar18 + 1);
              uVar48 = (ulong)(byte)((byte)*puVar18 >> 1);
            }
            if (((ulong)puStack_c0 & 1) == 0) {
              lVar39 = 0x16;
              puVar18 = (ulong *)((ulong)puStack_c0 & 0xff);
            }
            else {
              lVar39 = ((ulong)puStack_c0 & 0xfffffffffffffffe) - 1;
              puVar18 = puStack_c0;
            }
            puVar19 = (ulong *)(ulong)(((uint)puVar18 & 0xfe) >> 1);
            if (((ulong)puVar18 & 1) != 0) {
              puVar19 = puStack_b8;
            }
            if ((ulong)(lVar39 - (long)puVar19) < uVar48) {
              string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&puStack_c0,lVar39,(byte *)((uVar48 - lVar39) + (long)puVar19),puVar19
                              ,puVar19,0,uVar48);
            }
            else if (uVar48 != 0) {
              puVar25 = (ulong *)((ulong)&puStack_c0 | 1);
              if (((ulong)puVar18 & 1) != 0) {
                puVar25 = puStack_b0;
              }
              memcpy((byte *)((long)puVar25 + (long)puVar19),pbVar44,uVar48);
              puVar19 = (ulong *)((long)puVar19 + uVar48);
              puVar18 = puVar19;
              if (((ulong)puStack_c0 & 1) == 0) {
                puStack_c0 = (ulong *)CONCAT71(puStack_c0._1_7_,(char)puVar19 * '\x02');
                puVar18 = puStack_b8;
              }
              puStack_b8 = puVar18;
              *(byte *)((long)puVar25 + (long)puVar19) = 0;
            }
            puVar19 = puStack_b0;
            puVar18 = puStack_c0;
            puStack_c0 = (ulong *)0x0;
            puStack_98 = puStack_b8;
            puStack_a0 = puVar18;
            puStack_90 = puStack_b0;
            puStack_b0 = (ulong *)0x0;
            puStack_b8 = (ulong *)0x0;
            puVar25 = (ulong *)((ulong)&puStack_a0 | 1);
            if ((((ulong)puVar18 & 1) == 0) || (puVar25 = puVar19, puVar19 != (ulong *)0x0)) {
              iVar15 = access(puVar25,0);
              if (iVar15 != 0) {
                if (((ulong)puVar18 & 1) != 0) goto code_r0x018dae50;
                goto code_r0x018dae58;
              }
              uVar48 = ((long)puStack_78 - (long)puStack_80 >> 3) * -0x5555555555555555;
              if (uVar48 < uVar22 || uVar48 - uVar22 == 0) {
                Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dc536/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Vector.h"*/,0x58,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,uVar22);
              }
              puVar19 = puStack_80 + uVar22 * 3;
              uVar48 = ((long)puStack_228 - (long)puStack_230 >> 3) * -0x5555555555555555;
              if (uVar48 < uVar22 || uVar48 - uVar22 == 0) {
                Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dc536/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Vector.h"*/,0x58,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,uVar22);
              }
              uVar48 = CGameResourceDownloader::episodeResourceFileListUpdateCheck(string const&, string const&)(param_1,puVar19,puStack_230 + uVar22 * 3);
              if (((ulong)puVar18 & 1) != 0) {
                Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puStack_90);
              }
              if (((ulong)puStack_c0 & 1) != 0) {
                Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puStack_b0);
              }
              if ((uVar48 & 1) != 0) goto code_r0x018db018;
            }
            else {
code_r0x018dae50:
              Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puStack_90);
code_r0x018dae58:
              if (((ulong)puStack_c0 & 1) != 0) {
                Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puStack_b0);
              }
            }
            uVar48 = ((long)puStack_228 - (long)puStack_230 >> 3) * -0x5555555555555555;
            if (uVar48 < uVar22 || uVar48 - uVar22 == 0) {
              Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dc536/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Vector.h"*/,0x58,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,uVar22);
            }
            if ((puStack_230[uVar22 * 3] & 1) == 0) {
              pbVar44 = (byte *)((long)(puStack_230 + uVar22 * 3) + 1);
            }
            else {
              pbVar44 = (byte *)puStack_230[uVar22 * 3 + 2];
            }
            lVar39 = operator new(unsigned long, std::nothrow_t const&)(0x450,puVar1);
            if (lVar39 != 0) {
              plStack_310 = (long *)0x0;
              CGameResourceDownloader::CDownloadNode::CDownloadNode(char const*, std::__ndk1::function<void (char const*, CGameResourceDownloader::iErrorCode)>)(lVar39,pbVar44,&uStack_330);
              if (&uStack_330 == plStack_310) {
                pcVar33 = *(code **)(*plStack_310 + 0x20);
              }
              else {
                if (plStack_310 == (long *)0x0) goto code_r0x018dafc4;
                pcVar33 = *(code **)(*plStack_310 + 0x28);
              }
              (*pcVar33)();
            }
code_r0x018dafc4:
            lVar42 = param_1[0xb];
            if (-1 < lVar42) {
              Aska::TArray<CGameResourceDownloader::CDownloadNode*, false>::Resize(long, bool)(param_1 + 8,lVar42 + 1,0);
              *(long *)(param_1[9] + lVar42 * 8) = lVar39;
            }
            if (*(int *)(lVar39 + 8) != 5) {
              *(undefined1 *)(lVar39 + 0x150) = 1;
              *(undefined8 *)(lVar39 + 8) = 1;
            }
            lVar42 = param_1[0x12];
            if (-1 < lVar42) {
              Aska::TArray<CGameResourceDownloader::CDownloadNode*, false>::Resize(long, bool)(param_1 + 0xf,lVar42 + 1,0);
              *(long *)(param_1[0x10] + lVar42 * 8) = lVar39;
            }
          }
code_r0x018db018:
          uVar16 = (int)uVar22 + 1;
          uVar22 = (ulong)uVar16;
        } while (uVar16 < *(uint *)(param_1 + 0x4f));
      }
    }
    BAS::GetDownloadPath()(&uStack_330);
    if (((ulong)uStack_330 & 1) == 0) {
      puVar19 = (ulong *)0x16;
      puVar18 = (ulong *)((ulong)uStack_330 & 0xff);
    }
    else {
      puVar19 = (ulong *)(((ulong)uStack_330 & 0xfffffffffffffffe) - 1);
      puVar18 = uStack_330;
    }
    puVar25 = (ulong *)(ulong)(((uint)puVar18 & 0xfe) >> 1);
    if (((ulong)puVar18 & 1) != 0) {
      puVar25 = puStack_328;
    }
    if (puVar19 == puVar25) {
      string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&uStack_330,puVar19,1,puVar19,puVar19,0,1,&UNK_029c5d3e/*"/"*/);
    }
    else {
      auVar24 = (undefined1  [8])((ulong)&uStack_330 | 1);
      if (((ulong)puVar18 & 1) != 0) {
        auVar24 = auStack_320;
      }
      *(byte *)((long)auVar24 + (long)puVar25) = 0x2f;
      puVar25 = (ulong *)((long)puVar25 + 1);
      puVar18 = puVar25;
      if (((ulong)uStack_330 & 1) == 0) {
        uStack_330 = (ulong *)CONCAT71(uStack_330._1_7_,(char)puVar25 * '\x02');
        puVar18 = puStack_328;
      }
      puStack_328 = puVar18;
      *(byte *)((long)auVar24 + (long)puVar25) = 0;
    }
    puStack_90 = (ulong *)auStack_320;
    puStack_98 = puStack_328;
    puStack_a0 = uStack_330;
    CGameResourceDownloader::CheckLocalResourceFileToolVersionOld()+0x354(&puStack_c0);
    if (((ulong)puStack_c0 & 1) == 0) {
      lVar39 = 0x16;
      puVar18 = (ulong *)((ulong)puStack_c0 & 0xff);
    }
    else {
      lVar39 = ((ulong)puStack_c0 & 0xfffffffffffffffe) - 1;
      puVar18 = puStack_c0;
    }
    puVar19 = (ulong *)(ulong)(((uint)puVar18 & 0xfe) >> 1);
    if (((ulong)puVar18 & 1) != 0) {
      puVar19 = puStack_b8;
    }
    if ((ulong)(lVar39 - (long)puVar19) < 0xf) {
      string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&puStack_c0,lVar39,(byte *)((0xf - lVar39) + (long)puVar19),puVar19,puVar19,0,
                      0xf,&UNK_02866db9/*"version.version"*/);
    }
    else {
      uVar41 = CONCAT17(UNK_02866dc0,_UNK_02866db9);
      puVar25 = (ulong *)((ulong)&puStack_c0 | 1);
      if (((ulong)puVar18 & 1) != 0) {
        puVar25 = puStack_b0;
      }
      *(ulong *)((byte *)((long)puVar25 + (long)puVar19) + 7) = CONCAT71(_UNK_02866dc1,UNK_02866dc0)
      ;
      *(undefined8 *)((long)puVar25 + (long)puVar19) = uVar41;
      puVar19 = (ulong *)((long)puVar19 + 0xf);
      puVar18 = puVar19;
      if (((ulong)puStack_c0 & 1) == 0) {
        puStack_c0 = (ulong *)CONCAT71(puStack_c0._1_7_,(char)puVar19 * '\x02');
        puVar18 = puStack_b8;
      }
      puStack_b8 = puVar18;
      *(byte *)((long)puVar25 + (long)puVar19) = 0;
    }
    auStack_320 = (undefined1  [8])puStack_b0;
    puStack_328 = puStack_b8;
    uStack_330 = puStack_c0;
    puStack_b0 = (ulong *)0x0;
    bVar14 = ((ulong)puStack_c0 & 1) != 0;
    puVar18 = (ulong *)((ulong)&uStack_330 | 1);
    if (bVar14) {
      puVar18 = (ulong *)auStack_320;
    }
    puVar19 = (ulong *)((ulong)puStack_c0 >> 1 & 0x7f);
    if (bVar14) {
      puVar19 = puStack_b8;
    }
    puStack_c0 = (ulong *)0x0;
    puStack_b8 = (ulong *)0x0;
    if (((ulong)puStack_a0 & 1) == 0) {
      lVar39 = 0x16;
      puVar25 = (ulong *)((ulong)puStack_a0 & 0xff);
    }
    else {
      lVar39 = ((ulong)puStack_a0 & 0xfffffffffffffffe) - 1;
      puVar25 = puStack_a0;
    }
    puVar32 = (ulong *)(ulong)(((uint)puVar25 & 0xfe) >> 1);
    if (((ulong)puVar25 & 1) != 0) {
      puVar32 = puStack_98;
    }
    if ((ulong *)(lVar39 - (long)puVar32) < puVar19) {
      string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&puStack_a0,lVar39,(byte *)(((long)puVar19 - lVar39) + (long)puVar32),puVar32,
                      puVar32,0,puVar19);
    }
    else if (puVar19 != (ulong *)0x0) {
      puVar3 = (ulong *)((ulong)&puStack_a0 | 1);
      if (((ulong)puVar25 & 1) != 0) {
        puVar3 = puStack_90;
      }
      memcpy((byte *)((long)puVar3 + (long)puVar32),puVar18,puVar19);
      puVar32 = (ulong *)((long)puVar32 + (long)puVar19);
      if (((ulong)puStack_a0 & 1) == 0) {
        puStack_a0 = (ulong *)CONCAT71(puStack_a0._1_7_,(char)puVar32 * '\x02');
        *(byte *)((long)puVar3 + (long)puVar32) = 0;
      }
      else {
        *(byte *)((long)puVar3 + (long)puVar32) = 0;
        puStack_98 = puVar32;
      }
    }
    if (((ulong)uStack_330 & 1) != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(auStack_320);
    }
    if (((ulong)puStack_c0 & 1) != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puStack_b0);
    }
    puVar18 = (ulong *)(PTR__ZTVN4Aska10FileStreamE_02cbc9f8 + 0x10);
    puVar19 = (ulong *)(PTR__ZTVN4Aska4FileE_02cb6e28 + 0x10);
    puVar25 = (ulong *)((ulong)&puStack_a0 | 1);
    if (((ulong)puStack_a0 & 1) != 0) {
      puVar25 = puStack_90;
    }
    auStack_320 = (undefined1  [8])((ulong)auStack_320 & 0xffffffffffffff00);
    bStack_308 = 0;
    puStack_318 = (undefined *)0x0;
    plStack_310 = (long *)0x0;
    uStack_330 = puVar18;
    puStack_328 = puVar19;
    uVar22 = Aska::FileStream::Open(char const*, bool, bool, Aska::Machine::Endian)(&uStack_330,puVar25,0,1,3);
    if ((uVar22 & 1) != 0) {
      if ((*pbVar49 & 1) == 0) {
        lVar39 = (long)param_1 + 0x251;
        uVar22 = (ulong)(*pbVar49 >> 1);
      }
      else {
        lVar39 = param_1[0x4c];
        uVar22 = param_1[0x4b];
      }
      lVar39 = Aska::FileStream::Write(void const*, unsigned long, unsigned long)(&uStack_330,lVar39,uVar22,1);
      if (lVar39 == 0) {
        if ((*pbVar49 & 1) == 0) {
          uVar16 = (uint)(*pbVar49 >> 1);
        }
        else {
          uVar16 = (uint)param_1[0x4b];
        }
        *(uint *)PTR__ZN23CGameResourceDownloader15m_ErrorOverSizeE_02cbb7b8 =
             *(int *)PTR__ZN23CGameResourceDownloader15m_ErrorOverSizeE_02cbb7b8 + uVar16;
      }
      Aska::FileStream::Close()(&uStack_330);
    }
    uStack_330 = puVar18;
    Aska::FileStream::Close()(&uStack_330);
    puStack_328 = puVar19;
    if (puStack_318 != (undefined *)0x0) {
      Aska::File::Close()((ulong)&uStack_330 | 8);
    }
    if (((ulong)puStack_a0 & 1) != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puStack_90);
    }
    puVar18 = puStack_80;
    *(undefined4 *)(param_1 + 0x2a) = 4;
    if (puStack_80 != (ulong *)0x0) {
      while (puVar19 = puStack_78, puVar19 != puVar18) {
        puStack_78 = puVar19 + -3;
        if ((puVar19[-3] & 1) != 0) {
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puVar19[-1]);
        }
      }
      puStack_78 = puVar19;
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puStack_80);
    }
    puVar18 = puStack_230;
    if (puStack_230 != (ulong *)0x0) {
      while (puVar19 = puStack_228, puVar19 != puVar18) {
        puStack_228 = puVar19 + -3;
        if ((puVar19[-3] & 1) != 0) {
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puVar19[-1]);
        }
      }
      puStack_228 = puVar19;
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puStack_230);
    }
    if (((ulong)puStack_150 & 1) != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puStack_140);
    }
    auVar24 = (undefined1  [8])puStack_100;
    puVar18 = puStack_110;
    if (((ulong)puStack_1f0 & 1) != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_1e0);
      auVar24 = (undefined1  [8])puStack_100;
      puVar18 = puStack_110;
    }
joined_r0x018db454:
    if (((ulong)puVar18 & 1) == 0) {
      return;
    }
    goto code_r0x018db480;
  case 4:
    *(undefined4 *)(param_1 + 0x28) = 0x3e99999a;
    if ((long *)param_1[0xbb] != (long *)0x0) {
      (**(code **)(*(long *)param_1[0xbb] + 0x18))();
      param_1[0xbb] = 0;
    }
    plVar43 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x98,PTR__ZSt7nothrow_02cb9a80);
    if (plVar43 != (long *)0x0) {
      puVar1 = PTR__ZTV12CVersionInfo_02cbda90 + 0x10;
      *(undefined4 *)((long)plVar43 + 0xc) = 0x312e31;
      *(undefined1 *)(plVar43 + 1) = 1;
      *plVar43 = (long)puVar1;
      memset(plVar43 + 2,0,0x48);
      puVar1 = PTR__ZTVN4Aska8THashMapINSt6__ndk112basic_stringIcNS1_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS5_22CSTLStringAllocatorInfEEEEE10CAssetInfo17Hasher_CSTLStringNS_8TEqualToIS9_EENS_10TAllocatorINS_5TPairIKS9_SA_EEEEEE_02cc2290
               + 0x10;
      *(undefined8 *)((long)plVar43 + 100) = 0x3f400000;
      plVar43[0xb] = (long)puVar1;
      *(undefined4 *)((long)plVar43 + 0x6c) = 0;
      puVar17 = (undefined1 *)Aska::MemoryManagerAdapter::AlignedMalloc(unsigned long, unsigned long)(0xcc0,8);
      lVar39 = 0x11;
      if (puVar17 == (undefined1 *)0x0) {
        lVar39 = 0;
      }
      plVar43[0xf] = (long)puVar17;
      plVar43[0x10] = lVar39;
      if (puVar17 != (undefined1 *)0x0) {
        uVar22 = (lVar39 * 0xc0 - 0xc0U) / 0xc0 + 1;
        puVar35 = puVar17;
        if ((1 < uVar22) && (uVar48 = uVar22 & 0x3fffffffffffffe, uVar48 != 0)) {
          uVar29 = uVar48;
          do {
            *puVar35 = 0;
            puVar35[0xc0] = 0;
            uVar29 = uVar29 - 2;
            puVar35 = puVar35 + 0x180;
          } while (uVar29 != 0);
          puVar35 = puVar17 + uVar48 * 0xc0;
          if (uVar22 == uVar48) goto code_r0x018d8f20;
        }
        do {
          puVar34 = puVar35 + 0xc0;
          *puVar35 = 0;
          puVar35 = puVar34;
        } while (puVar17 + lVar39 * 0xc0 != puVar34);
      }
code_r0x018d8f20:
      *(undefined1 *)(plVar43 + 0x12) = 1;
      puVar1 = PTR__ZTV10CAssetList_02cba9a8 + 0x38;
      plVar43[0xb] = (long)(PTR__ZTV10CAssetList_02cba9a8 + 0x10);
      plVar43[0x11] = (long)puVar1;
    }
    puVar18 = (ulong *)(plVar43 + 8);
    param_1[0xbb] = (long)plVar43;
    if (puVar18 != (ulong *)(param_1 + 0x47)) {
      lVar39 = param_1[0x49];
      uVar22 = param_1[0x48];
      uVar48 = (ulong)(byte)*puVar18;
      if ((*(byte *)(param_1 + 0x47) & 1) == 0) {
        lVar39 = (long)param_1 + 0x239;
        uVar22 = (ulong)(*(byte *)(param_1 + 0x47) >> 1);
      }
      if (((byte)*puVar18 & 1) == 0) {
        uVar29 = 0x16;
        lVar42 = uVar22 - 0x16;
        if (uVar22 < 0x16 || lVar42 == 0) {
code_r0x018d8fa4:
          if ((uVar48 & 1) == 0) {
            lVar42 = (long)plVar43 + 0x41;
          }
          else {
            lVar42 = plVar43[10];
          }
          if (uVar22 != 0) {
            memmove(lVar42,lVar39,uVar22);
          }
          *(undefined1 *)(lVar42 + uVar22) = 0;
          if ((*puVar18 & 1) == 0) {
            *(byte *)puVar18 = (byte)(uVar22 << 1);
          }
          else {
            plVar43[9] = uVar22;
          }
          goto code_r0x018d9004;
        }
      }
      else {
        uVar48 = *puVar18;
        uVar29 = (uVar48 & 0xfffffffffffffffe) - 1;
        lVar42 = uVar22 - uVar29;
        if (uVar22 < uVar29 || lVar42 == 0) goto code_r0x018d8fa4;
      }
      if ((uVar48 & 1) == 0) {
        uVar48 = (ulong)(((uint)uVar48 & 0xfe) >> 1);
      }
      else {
        uVar48 = plVar43[9];
      }
      string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(puVar18,uVar29,lVar42,uVar48,0,uVar48,uVar22);
    }
code_r0x018d9004:
    lVar39 = Aska::ASON::Init(unsigned int, bool)(param_1 + 0x50,"meterEPv",1);
    if (lVar39 != 0) {
code_r0x018d901c:
      *(undefined8 *)((long)param_1 + 0x14c) = 5;
      if (*(char *)((long)param_1 + 0x157) == '\0') {
        return;
      }
      plVar43 = (long *)param_1[0x9c];
      if (plVar43 == (long *)0x0) {
        return;
      }
      uStack_330 = (ulong *)0xfffffffffffffc15;
      puStack_1f0 = (ulong *)CONCAT44(puStack_1f0._4_4_,1000000);
      (**(code **)(*plVar43 + 0x30))(plVar43,&puStack_1f0,&uStack_330);
      return;
    }
    BAS::GetDownloadPath()(&uStack_330);
    if (((ulong)uStack_330 & 1) == 0) {
      puVar19 = (ulong *)0x16;
      puVar18 = (ulong *)((ulong)uStack_330 & 0xff);
    }
    else {
      puVar19 = (ulong *)(((ulong)uStack_330 & 0xfffffffffffffffe) - 1);
      puVar18 = uStack_330;
    }
    puVar25 = (ulong *)(ulong)(((uint)puVar18 & 0xfe) >> 1);
    if (((ulong)puVar18 & 1) != 0) {
      puVar25 = puStack_328;
    }
    if (puVar19 == puVar25) {
      string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&uStack_330,puVar19,1,puVar19,puVar19,0,1,&UNK_029c5d3e/*"/"*/);
    }
    else {
      auVar24 = (undefined1  [8])((ulong)&uStack_330 | 1);
      if (((ulong)puVar18 & 1) != 0) {
        auVar24 = auStack_320;
      }
      *(byte *)((long)auVar24 + (long)puVar25) = 0x2f;
      puVar25 = (ulong *)((long)puVar25 + 1);
      puVar18 = puVar25;
      if (((ulong)uStack_330 & 1) == 0) {
        uStack_330 = (ulong *)CONCAT71(uStack_330._1_7_,(char)puVar25 * '\x02');
        puVar18 = puStack_328;
      }
      puStack_328 = puVar18;
      *(byte *)((long)auVar24 + (long)puVar25) = 0;
    }
    uStack_1e0 = (ulong *)auStack_320;
    puStack_1e8 = puStack_328;
    puStack_1f0 = uStack_330;
    string std::__ndk1::operator+<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> >(string const&, char const*)(&puStack_150,&puStack_1f0,&UNK_02866dd0/*"version.bin"*/);
    if (((ulong)puStack_150 & 1) == 0) {
      puVar18 = (ulong *)((ulong)&puStack_150 | 1);
code_r0x018d9140:
      iVar15 = access(puVar18,0);
      if (iVar15 != 0) goto code_r0x018d914c;
      puVar18 = (ulong *)((ulong)&puStack_150 | 1);
      if (((ulong)puStack_150 & 1) != 0) {
        puVar18 = puStack_140;
      }
      lVar39 = Aska::FileReadManager::CalcFileLength(char const*, bool)(puVar18,0);
      if (lVar39 == 0) goto code_r0x018d914c;
      lVar42 = operator new[](unsigned long, std::nothrow_t const&)(lVar39,PTR__ZSt7nothrow_02cb9a80);
      param_1[0x91] = lVar42;
      puVar2 = PTR__ZTVN4Aska10FileStreamE_02cbc9f8;
      puVar1 = PTR__ZTVN4Aska4FileE_02cb6e28;
      uStack_330 = (ulong *)(PTR__ZTVN4Aska10FileStreamE_02cbc9f8 + 0x10);
      puStack_328 = (ulong *)(PTR__ZTVN4Aska4FileE_02cb6e28 + 0x10);
      puVar18 = (ulong *)((ulong)&puStack_150 | 1);
      if (((ulong)puStack_150 & 1) != 0) {
        puVar18 = puStack_140;
      }
      auStack_320 = (undefined1  [8])((ulong)auStack_320 & 0xffffffffffffff00);
      bStack_308 = 0;
      puStack_318 = (undefined *)0x0;
      plStack_310 = (long *)0x0;
      uVar22 = Aska::FileStream::Open(char const*, bool, bool, Aska::Machine::Endian)(&uStack_330,puVar18,0,0,3);
      if ((uVar22 & 1) == 0) {
code_r0x018d9290:
        lVar39 = Aska::ASON::AValue::AMap::Get_(char const*)(param_1 + 0x5d,&UNK_02866dc9/*"assets"*/);
        bVar14 = false;
        lVar39 = lVar39 + 8;
      }
      else {
        Aska::FileStream::Read(void*, unsigned long, unsigned long)(&uStack_330,param_1[0x91],lVar39,1);
        Aska::FileStream::Close()(&uStack_330);
        Aska::ASON::DeserializeBinary(void const*, unsigned long)(param_1 + 0x50,param_1[0x91],lVar39);
        if (-1 < param_1[0x60]) goto code_r0x018d9290;
        param_1[0x2c] = -0x3a7;
        *(undefined8 *)((long)param_1 + 0x14c) = 5;
        if ((*(char *)((long)param_1 + 0x157) != '\0') &&
           (plVar43 = (long *)param_1[0x9c], plVar43 != (long *)0x0)) {
          puStack_110 = (ulong *)0xfffffffffffffc59;
          puStack_230 = (ulong *)CONCAT44(puStack_230._4_4_,1000000);
          (**(code **)(*plVar43 + 0x30))(plVar43,&puStack_230,&puStack_110);
        }
        lVar39 = 0;
        bVar14 = true;
      }
      uStack_330 = (ulong *)(puVar2 + 0x10);
      Aska::FileStream::Close()(&uStack_330);
      puStack_328 = (ulong *)(puVar1 + 0x10);
      if (puStack_318 != (undefined *)0x0) {
        Aska::File::Close()((ulong)&uStack_330 | 8);
      }
      if (!bVar14) goto code_r0x018d9150;
      bVar14 = true;
    }
    else {
      puVar18 = puStack_140;
      if (puStack_140 != (ulong *)0x0) goto code_r0x018d9140;
code_r0x018d914c:
      lVar39 = 0;
code_r0x018d9150:
      bVar14 = false;
    }
    if (((ulong)puStack_150 & 1) != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puStack_140);
    }
    if (((ulong)puStack_1f0 & 1) != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_1e0);
    }
    if (bVar14) {
      return;
    }
    if ((lVar39 != 0) && (uVar16 = *(uint *)(lVar39 + 8), uVar16 != 0)) {
      lVar42 = param_1[0xbb];
      fVar51 = (float)NEON_ucvtf(*(undefined4 *)(lVar42 + 0x68));
      uVar22 = (ulong)(fVar51 / *(float *)(lVar42 + 100));
      if (uVar22 <= uVar16) {
        uVar22 = (ulong)uVar16;
      }
      Aska::THashMap<string, CAssetInfo, Hasher_CSTLString, Aska::TEqualTo<string >, Aska::TAllocator<Aska::TPair<string const, CAssetInfo> > >::Rehash_(unsigned long)(lVar42 + 0x58,uVar22);
    }
    BAS::GetDownloadPath()(&uStack_330);
    if (((ulong)uStack_330 & 1) == 0) {
      puVar19 = (ulong *)0x16;
      puVar18 = (ulong *)((ulong)uStack_330 & 0xff);
    }
    else {
      puVar19 = (ulong *)(((ulong)uStack_330 & 0xfffffffffffffffe) - 1);
      puVar18 = uStack_330;
    }
    puVar25 = (ulong *)(ulong)(((uint)puVar18 & 0xfe) >> 1);
    if (((ulong)puVar18 & 1) != 0) {
      puVar25 = puStack_328;
    }
    if (puVar19 == puVar25) {
      string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&uStack_330,puVar19,1,puVar19,puVar19,0,1,&UNK_029c5d3e/*"/"*/);
    }
    else {
      auVar24 = (undefined1  [8])((ulong)&uStack_330 | 1);
      if (((ulong)puVar18 & 1) != 0) {
        auVar24 = auStack_320;
      }
      *(byte *)((long)auVar24 + (long)puVar25) = 0x2f;
      puVar25 = (ulong *)((long)puVar25 + 1);
      puVar18 = puVar25;
      if (((ulong)uStack_330 & 1) == 0) {
        uStack_330 = (ulong *)CONCAT71(uStack_330._1_7_,(char)puVar25 * '\x02');
        puVar18 = puStack_328;
      }
      puStack_328 = puVar18;
      *(byte *)((long)auVar24 + (long)puVar25) = 0;
    }
    uVar23 = _UNK_02866d67;
    uVar41 = _UNK_02866d5f;
    puStack_1e8 = puStack_328;
    puStack_1f0 = uStack_330;
    uStack_1e0 = (ulong *)auStack_320;
    if (((ulong)uStack_330 & 1) == 0) {
      lVar42 = 0x16;
      puVar18 = (ulong *)((ulong)uStack_330 & 0xff);
    }
    else {
      lVar42 = ((ulong)uStack_330 & 0xfffffffffffffffe) - 1;
      puVar18 = uStack_330;
    }
    puVar19 = (ulong *)(ulong)(((uint)puVar18 & 0xfe) >> 1);
    if (((ulong)puVar18 & 1) != 0) {
      puVar19 = puStack_328;
    }
    if ((ulong)(lVar42 - (long)puVar19) < 0x14) {
      string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&puStack_1f0,lVar42,(byte *)((0x14 - lVar42) + (long)puVar19),puVar19,puVar19,
                      0,0x14,&UNK_02866d5f/*"downloadfilelist.tmp"*/);
    }
    else {
      auVar24 = (undefined1  [8])((ulong)&puStack_1f0 | 1);
      if (((ulong)puVar18 & 1) != 0) {
        auVar24 = auStack_320;
      }
      pbVar49 = (byte *)((long)auVar24 + (long)puVar19);
      pbVar49[0x10] = 0x2e;
      pbVar49[0x11] = 0x74;
      pbVar49[0x12] = 0x6d;
      pbVar49[0x13] = 0x70;
      *(undefined8 *)(pbVar49 + 8) = uVar23;
      *(undefined8 *)pbVar49 = uVar41;
      puVar19 = (ulong *)((long)puVar19 + 0x14);
      puVar18 = puVar19;
      if (((ulong)uStack_330 & 1) == 0) {
        puStack_1f0._1_7_ = (undefined7)((ulong)uStack_330 >> 8);
        puStack_1f0 = (ulong *)CONCAT71(puStack_1f0._1_7_,(char)puVar19 * '\x02');
        puVar18 = puStack_1e8;
      }
      puStack_1e8 = puVar18;
      *(byte *)((long)auVar24 + (long)puVar19) = 0;
    }
    puStack_78 = puStack_1e8;
    puStack_80 = puStack_1f0;
    puStack_70 = uStack_1e0;
    if (((ulong)puStack_1f0 & 1) == 0) {
      puVar18 = (ulong *)((ulong)&puStack_80 | 1);
code_r0x018d9c38:
      iVar15 = access(puVar18,0);
      if (iVar15 != 0) goto code_r0x018d9c44;
      puVar18 = (ulong *)((ulong)&puStack_80 | 1);
      if (((ulong)puStack_80 & 1) != 0) {
        puVar18 = puStack_70;
      }
      lVar42 = Aska::FileReadManager::CalcFileLength(char const*, bool)(puVar18,0);
      if (lVar42 == 0) goto code_r0x018d9c44;
      lVar21 = operator new[](unsigned long, std::nothrow_t const&)(lVar42 + 1,PTR__ZSt7nothrow_02cb9a80);
      puStack_110 = (ulong *)(PTR__ZTVN4Aska10FileStreamE_02cbc9f8 + 0x10);
      puStack_108 = (ulong *)(PTR__ZTVN4Aska4FileE_02cb6e28 + 0x10);
      puVar18 = (ulong *)((ulong)&puStack_80 | 1);
      if (((ulong)puStack_80 & 1) != 0) {
        puVar18 = puStack_70;
      }
      puStack_100 = (ulong *)((ulong)puStack_100 & 0xffffffffffffff00);
      uStack_e8 = 0;
      uStack_f0 = 0;
      lStack_f8 = 0;
      uVar22 = Aska::FileStream::Open(char const*, bool, bool, Aska::Machine::Endian)(&puStack_110,puVar18,0,0,3);
      if ((uVar22 & 1) != 0) {
        Aska::FileStream::Read(void*, unsigned long, unsigned long)(&puStack_110,lVar21,lVar42,1);
        Aska::FileStream::Close()(&puStack_110);
        *(undefined1 *)(lVar21 + lVar42) = 0;
      }
      Framework::CCSV::CCSV()(&puStack_150);
      Framework::CCSV::Initialize()(&puStack_150);
      Framework::CCSV::Parse(char const*, bool)(&puStack_150,lVar21,0);
      lVar42 = Framework::CCSV::NumRows() const(&puStack_150);
      if (lVar42 != 0) {
        puVar18 = (ulong *)(PTR__ZTV10CAssetInfo_02cb7ad0 + 0x10);
        puVar1 = PTR__ZTVN4Aska6TArrayI9CMetaInfoLb0EEE_02cba9a0 + 0x10;
        uVar22 = 0;
        puVar2 = PTR__ZTV9CMetaInfo_02cc00d0 + 0x10;
        puVar50 = PTR__ZTV10CAssetInfo_02cb7ad0;
        do {
          uVar48 = Framework::CCSV::NumElements(unsigned long) const(&puStack_150,uVar22);
          if (uVar48 < 8) {
            *(undefined1 *)((long)param_1 + 0x15e) = 1;
            break;
          }
          uVar41 = Framework::CCSV::Element(unsigned long, unsigned long) const(&puStack_150,uVar22,0);
          Framework::CCSV::tElement::tElement(Framework::CCSV::tElement const&)(&puStack_c0,uVar41);
          uVar41 = Framework::CCSV::Element(unsigned long, unsigned long) const(&puStack_150,uVar22,1);
          Framework::CCSV::tElement::tElement(Framework::CCSV::tElement const&)(&puStack_e0,uVar41);
          uVar48 = Framework::CCSV::tElement::IsString() const(&puStack_c0);
          if (((uVar48 & 1) != 0) && (uVar48 = Framework::CCSV::tElement::IsString() const(&puStack_e0), (uVar48 & 1) != 0)) {
            uVar41 = Framework::CCSV::tElement::String() const(&puStack_c0);
            puStack_1e8 = (ulong *)CONCAT71(puStack_1e8._1_7_,1);
            lStack_1d0 = 0;
            uStack_1d8 = 0;
            uStack_1e0 = (ulong *)0x0;
            puStack_1a0 = (undefined7 *)0x0;
            uStack_1a8 = 0;
            uStack_1af = 0;
            bStack_1b0 = 0;
            uStack_188 = 0;
            plStack_190 = (long *)0x0;
            uStack_178 = 0;
            lStack_180 = 0;
            uStack_170 = 8;
            uStack_168 = 0;
            uStack_158 = 1;
            puStack_198 = PTR__ZTV9CMetaList_02cbed68 + 0x10;
            puStack_160 = PTR__ZTV9CMetaList_02cbed68 + 0x40;
            puStack_1f0 = puVar18;
            Framework::CCSV::Element(unsigned long, unsigned long) const(&puStack_150,uVar22,2);
            dVar52 = (double)Framework::CCSV::tElement::ValueSafe(double) const(0);
            iStack_1c8 = (int)dVar52;
            Framework::CCSV::Element(unsigned long, unsigned long) const(&puStack_150,uVar22,3);
            dVar52 = (double)Framework::CCSV::tElement::ValueSafe(double) const(0);
            iStack_1c4 = (int)dVar52;
            pbVar49 = (byte *)Framework::CCSV::tElement::String() const(&puStack_e0);
            uVar48 = uStack_1d8;
            if ((byte *)&uStack_1e0 != pbVar49) {
              uVar48 = *(ulong *)(pbVar49 + 8);
              pbVar44 = *(byte **)(pbVar49 + 0x10);
              if ((*pbVar49 & 1) == 0) {
                pbVar44 = pbVar49 + 1;
                uVar48 = (ulong)(*pbVar49 >> 1);
              }
              if (((ulong)uStack_1e0 & 1) == 0) {
                uVar29 = 0x16;
                lVar42 = uVar48 - 0x16;
                puVar19 = (ulong *)((ulong)uStack_1e0 & 0xff);
                if (uVar48 < 0x16 || lVar42 == 0) {
code_r0x018da030:
                  lVar42 = (long)&uStack_1e0 + 1;
                  if (((ulong)puVar19 & 1) != 0) {
                    lVar42 = lStack_1d0;
                  }
                  if (uVar48 != 0) {
                    memmove(lVar42,pbVar44,uVar48);
                  }
                  *(undefined1 *)(lVar42 + uVar48) = 0;
                  if (((ulong)uStack_1e0 & 1) == 0) {
                    uStack_1e0 = (ulong *)CONCAT71(uStack_1e0._1_7_,(char)(uVar48 << 1));
                    uVar48 = uStack_1d8;
                  }
                  goto code_r0x018da07c;
                }
              }
              else {
                uVar29 = ((ulong)uStack_1e0 & 0xfffffffffffffffe) - 1;
                lVar42 = uVar48 - uVar29;
                puVar19 = uStack_1e0;
                if (uVar48 < uVar29 || lVar42 == 0) goto code_r0x018da030;
              }
              uVar26 = (ulong)(((uint)puVar19 & 0xfe) >> 1);
              if (((ulong)puVar19 & 1) != 0) {
                uVar26 = uStack_1d8;
              }
              string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&uStack_1e0,uVar29,lVar42,uVar26,0,uVar26,uVar48);
              uVar48 = uStack_1d8;
            }
code_r0x018da07c:
            uStack_1d8 = uVar48;
            Framework::CCSV::Element(unsigned long, unsigned long) const(&puStack_150,uVar22,5);
            dVar52 = (double)Framework::CCSV::tElement::ValueSafe(double) const(0);
            iStack_1bc = (int)dVar52;
            Framework::CCSV::Element(unsigned long, unsigned long) const(&puStack_150,uVar22,4);
            dVar52 = (double)Framework::CCSV::tElement::ValueSafe(double) const(0);
            iStack_1c0 = (int)dVar52;
            Framework::CCSV::Element(unsigned long, unsigned long) const(&puStack_150,uVar22,6);
            dVar52 = (double)Framework::CCSV::tElement::ValueSafe(double) const(0);
            iStack_1b8 = (int)dVar52;
            uVar23 = Framework::CCSV::Element(unsigned long, unsigned long) const(&puStack_150,uVar22,8);
            Framework::CCSV::tElement::tElement(Framework::CCSV::tElement const&)(auStack_200,uVar23);
            uVar48 = Framework::CCSV::tElement::IsString() const(auStack_200);
            if ((uVar48 & 1) == 0) {
              puVar5 = &uStack_1af;
              if ((bStack_1b0 & 1) != 0) {
                puVar5 = puStack_1a0;
              }
              *(undefined1 *)puVar5 = 0;
              if ((bStack_1b0 & 1) == 0) {
                bStack_1b0 = 0;
                uVar48 = uStack_1a8;
              }
              else {
                uStack_1a8 = 0;
                uVar48 = uStack_1a8;
              }
            }
            else {
              pbVar49 = (byte *)Framework::CCSV::tElement::String() const(auStack_200);
              uVar48 = uStack_1a8;
              if (&bStack_1b0 != pbVar49) {
                uVar48 = *(ulong *)(pbVar49 + 8);
                pbVar44 = *(byte **)(pbVar49 + 0x10);
                uVar29 = (ulong)bStack_1b0;
                if ((*pbVar49 & 1) == 0) {
                  pbVar44 = pbVar49 + 1;
                  uVar48 = (ulong)(*pbVar49 >> 1);
                }
                if ((bStack_1b0 & 1) == 0) {
                  uVar26 = 0x16;
                  lVar42 = uVar48 - 0x16;
                  if (uVar48 < 0x16 || lVar42 == 0) {
code_r0x018da1b4:
                    puVar5 = &uStack_1af;
                    if ((uVar29 & 1) != 0) {
                      puVar5 = puStack_1a0;
                    }
                    if (uVar48 != 0) {
                      memmove(puVar5,pbVar44,uVar48);
                    }
                    *(undefined1 *)((long)puVar5 + uVar48) = 0;
                    if ((bStack_1b0 & 1) == 0) {
                      bStack_1b0 = (byte)(uVar48 << 1);
                      uVar48 = uStack_1a8;
                    }
                    goto code_r0x018da200;
                  }
                }
                else {
                  uVar29 = CONCAT71(uStack_1af,bStack_1b0);
                  uVar26 = (uVar29 & 0xfffffffffffffffe) - 1;
                  lVar42 = uVar48 - uVar26;
                  if (uVar48 < uVar26 || lVar42 == 0) goto code_r0x018da1b4;
                }
                uVar4 = (ulong)(((uint)uVar29 & 0xfe) >> 1);
                if ((uVar29 & 1) != 0) {
                  uVar4 = uStack_1a8;
                }
                string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&bStack_1b0,uVar26,lVar42,uVar4,0,uVar4,uVar48);
                uVar48 = uStack_1a8;
              }
            }
code_r0x018da200:
            uStack_1a8 = uVar48;
            uVar23 = Framework::CCSV::Element(unsigned long, unsigned long) const(&puStack_150,uVar22,7);
            Framework::CCSV::tElement::tElement(Framework::CCSV::tElement const&)(auStack_210,uVar23);
            pbVar49 = (byte *)Framework::CCSV::tElement::String() const(auStack_210);
            puStack_a0 = (ulong *)0x0;
            puStack_90 = (ulong *)0x0;
            puStack_98 = (ulong *)0x0;
            if ((*pbVar49 & 1) == 0) {
              puStack_90 = *(ulong **)(pbVar49 + 0x10);
              puStack_98 = *(ulong **)(pbVar49 + 8);
              puStack_a0 = *(ulong **)pbVar49;
            }
            else {
              puVar19 = *(ulong **)(pbVar49 + 8);
              uVar23 = *(undefined8 *)(pbVar49 + 0x10);
              if (puVar19 < (ulong *)0x17) {
                puStack_a0 = (ulong *)(((ulong)puVar19 & 0x7f) << 1);
                puVar25 = (ulong *)((ulong)&puStack_a0 | 1);
                if (puVar19 != (ulong *)0x0) goto code_r0x018da2e0;
              }
              else {
                uVar48 = (ulong)(puVar19 + 2) & 0xfffffffffffffff0;
                if (uVar48 == 0) {
                  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
                }
                puVar25 = (ulong *)Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar48,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
                if (puVar25 == (ulong *)0x0) {
                  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
                }
                puStack_a0 = (ulong *)(uVar48 | 1);
                puStack_98 = puVar19;
                puStack_90 = puVar25;
code_r0x018da2e0:
                memcpy(puVar25,uVar23,puVar19);
              }
              *(byte *)((long)puVar25 + (long)puVar19) = 0;
            }
            puVar19 = (ulong *)((ulong)puStack_a0 >> 1 & 0x7f);
            if (((ulong)puStack_a0 & 1) != 0) {
              puVar19 = puStack_98;
            }
            if (puVar19 != (ulong *)0x0) {
              puStack_328 = (ulong *)0x0;
              auStack_320 = (undefined1  [8])0x0;
              uStack_330 = (ulong *)0x7c02;
              Framework::CSTLStringUtility_Base<string >::Split(string const&, string const&)(&puStack_230,&puStack_a0,&uStack_330);
              if (((ulong)uStack_330 & 1) != 0) {
                Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(auStack_320);
              }
              puVar19 = puStack_230;
              if (puStack_228 != puStack_230) {
                lVar42 = 0;
                uVar48 = 0;
                do {
                  uVar29 = ((long)puStack_228 - (long)puVar19 >> 3) * -0x5555555555555555;
                  if (uVar29 < uVar48 || uVar29 - uVar48 == 0) {
                    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dc536/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Vector.h"*/,0x58,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,uVar48);
                    puVar19 = puStack_230;
                  }
                  if ((*(byte *)((long)puVar19 + lVar42) & 1) == 0) {
                    if (*(byte *)((long)puVar19 + lVar42) >> 1 != 0) {
code_r0x018da3ac:
                      puStack_328 = (ulong *)CONCAT71(puStack_328._1_7_,1);
                      uVar29 = ((long)puStack_228 - (long)puVar19 >> 3) * -0x5555555555555555;
                      puStack_318 = (undefined *)0x0;
                      plStack_310 = (long *)0x0;
                      auStack_320 = (undefined1  [8])0x0;
                      uStack_330 = (ulong *)puVar2;
                      if (uVar29 < uVar48 || uVar29 - uVar48 == 0) {
                        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dc536/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Vector.h"*/,0x58,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,uVar48);
                        puVar19 = puStack_230;
                      }
                      puVar50 = puStack_318;
                      if ((byte *)((long)puVar19 + lVar42 + (-0x10 - (long)&uStack_330)) !=
                          (byte *)0x0) {
                        pbVar49 = (byte *)((long)puVar19 + lVar42);
                        puVar50 = *(undefined **)(pbVar49 + 8);
                        pbVar44 = *(byte **)(pbVar49 + 0x10);
                        if ((*pbVar49 & 1) == 0) {
                          pbVar44 = pbVar49 + 1;
                          puVar50 = (undefined *)(ulong)(*pbVar49 >> 1);
                        }
                        if (((ulong)auStack_320 & 1) == 0) {
                          puVar27 = (undefined *)0x16;
                          puVar28 = puVar50 + -0x16;
                          auVar24 = (undefined1  [8])((ulong)auStack_320 & 0xff);
                          if (puVar50 < (undefined *)0x16 || puVar28 == (undefined *)0x0) {
code_r0x018da478:
                            plVar43 = (long *)(auStack_320 + 1);
                            if (((ulong)auVar24 & 1) != 0) {
                              plVar43 = plStack_310;
                            }
                            if (puVar50 != (undefined *)0x0) {
                              memmove(plVar43,pbVar44,puVar50);
                            }
                            *(undefined1 *)((long)plVar43 + (long)puVar50) = 0;
                            if (((ulong)auStack_320 & 1) == 0) {
                              auStack_320[0] = (char)((long)puVar50 << 1);
                              puVar50 = puStack_318;
                            }
                            goto code_r0x018da4c4;
                          }
                        }
                        else {
                          puVar27 = (undefined *)(((ulong)auStack_320 & 0xfffffffffffffffe) - 1);
                          puVar28 = puVar50 + -(long)puVar27;
                          auVar24 = auStack_320;
                          if (puVar50 < puVar27 || puVar28 == (undefined *)0x0)
                          goto code_r0x018da478;
                        }
                        puVar6 = (undefined *)(ulong)((SUB84(auVar24,0) & 0xfe) >> 1);
                        if (((ulong)auVar24 & 1) != 0) {
                          puVar6 = puStack_318;
                        }
                        string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(auStack_320,puVar27,puVar28,puVar6,0,puVar6,puVar50);
                        puVar50 = puStack_318;
                      }
code_r0x018da4c4:
                      puStack_318 = puVar50;
                      Aska::TArray<CMetaInfo, false>::SetAt(long, CMetaInfo const&)(&puStack_198,lStack_180,&uStack_330);
                      uStack_330 = (ulong *)(PTR__ZTV9CMetaInfo_02cc00d0 + 0x10);
                      puVar19 = puStack_230;
                      if (((ulong)auStack_320 & 1) != 0) {
                        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plStack_310);
                        puVar19 = puStack_230;
                      }
                    }
                  }
                  else if (*(long *)((long)puVar19 + lVar42 + 8) != 0) goto code_r0x018da3ac;
                  uVar48 = uVar48 + 1;
                  lVar42 = lVar42 + 0x18;
                  uVar29 = ((long)puStack_228 - (long)puVar19 >> 3) * -0x5555555555555555;
                } while (uVar48 <= uVar29 && uVar29 - uVar48 != 0);
              }
              puVar50 = PTR__ZTV10CAssetInfo_02cb7ad0;
              puVar25 = puVar19;
              if (puVar19 != (ulong *)0x0) {
                while (puVar32 = puStack_228, puVar19 != puVar32) {
                  puStack_228 = puVar32 + -3;
                  puVar25 = puStack_230;
                  if ((puVar32[-3] & 1) != 0) {
                    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puVar32[-1]);
                    puVar25 = puStack_230;
                  }
                }
                puStack_228 = puVar32;
                Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puVar25);
              }
            }
            lVar42 = param_1[0xbb];
            Aska::TPair<string const, CAssetInfo>::TPair(string const&, CAssetInfo const&)(&uStack_330,uVar41,&puStack_1f0);
            uVar48 = (ulong)((float)((ulong)*(uint *)(lVar42 + 0x68) +
                                     (ulong)*(uint *)(lVar42 + 0x6c) + 1) / *(float *)(lVar42 + 100)
                            );
            if (*(ulong *)(lVar42 + 0x80) < uVar48) {
              Aska::THashMap<string, CAssetInfo, Hasher_CSTLString, Aska::TEqualTo<string >, Aska::TAllocator<Aska::TPair<string const, CAssetInfo> > >::Rehash_(unsigned long)(lVar42 + 0x58,uVar48 << 1 | 1);
            }
            Aska::THashMap<string, CAssetInfo, Hasher_CSTLString, Aska::TEqualTo<string >, Aska::TAllocator<Aska::TPair<string const, CAssetInfo> > >::Insert_(Aska::TPair<string const, CAssetInfo> const&)(&puStack_230,lVar42 + 0x58,&uStack_330);
            puStack_318 = puVar50 + 0x10;
            uStack_28e = uStack_28e | 1;
            puStack_2c0 = puVar1;
            if (((plStack_2b8 != (long *)0x0) && (0 < lStack_2a8)) &&
               ((**(code **)(*plStack_2b8 + 0x10))(), 1 < lStack_2a8)) {
              lVar37 = 0x28;
              lVar42 = 1;
              do {
                (**(code **)(*(long *)((long)plStack_2b8 + lVar37) + 0x10))();
                lVar42 = lVar42 + 1;
                lVar37 = lVar37 + 0x28;
              } while (lVar42 < lStack_2a8);
            }
            if ((uStack_28e & 1) != 0) {
              if (plStack_2b8 != (long *)0x0) {
                operator delete[](void*)();
                plStack_2b8 = (long *)0x0;
              }
              uStack_2b0 = 0;
            }
            lStack_2a8 = 0;
            uStack_2a0 = 0;
            if ((bStack_2d8 & 1) != 0) {
              Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_2c8);
            }
            if ((bStack_308 & 1) != 0) {
              Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_2f8);
            }
            if (((ulong)uStack_330 & 1) != 0) {
              Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(auStack_320);
            }
            if (((ulong)puStack_a0 & 1) != 0) {
              Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puStack_90);
            }
            Framework::CCSV::tElement::~tElement()(auStack_210);
            Framework::CCSV::tElement::~tElement()(auStack_200);
            puStack_1f0 = (ulong *)(puVar50 + 0x10);
            puStack_198 = PTR__ZTVN4Aska6TArrayI9CMetaInfoLb0EEE_02cba9a0 + 0x10;
            uStack_168 = uStack_168 | 0x10000;
            if (((plStack_190 != (long *)0x0) && (0 < lStack_180)) &&
               ((**(code **)(*plStack_190 + 0x10))(), 1 < lStack_180)) {
              lVar37 = 0x28;
              lVar42 = 1;
              do {
                (**(code **)(*(long *)((long)plStack_190 + lVar37) + 0x10))();
                lVar42 = lVar42 + 1;
                lVar37 = lVar37 + 0x28;
              } while (lVar42 < lStack_180);
            }
            if ((uStack_168 & 0x10000) != 0) {
              if (plStack_190 != (long *)0x0) {
                operator delete[](void*)();
                plStack_190 = (long *)0x0;
              }
              uStack_188 = 0;
            }
            uStack_178 = 0;
            if ((bStack_1b0 & 1) != 0) {
              Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puStack_1a0);
            }
            if (((ulong)uStack_1e0 & 1) != 0) {
              Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(lStack_1d0);
            }
          }
          Framework::CCSV::tElement::~tElement()(&puStack_e0);
          Framework::CCSV::tElement::~tElement()(&puStack_c0);
          uVar22 = uVar22 + 1;
          uVar48 = Framework::CCSV::NumRows() const(&puStack_150);
        } while (uVar22 < uVar48);
      }
      if (lVar21 != 0) {
        operator delete[](void*)();
      }
      Framework::CCSV::~CCSV()(&puStack_150);
      puStack_110 = (ulong *)(PTR__ZTVN4Aska10FileStreamE_02cbc9f8 + 0x10);
      Aska::FileStream::Close()(&puStack_110);
      puStack_108 = (ulong *)(PTR__ZTVN4Aska4FileE_02cb6e28 + 0x10);
      if (lStack_f8 == 0) goto code_r0x018d9c44;
      Aska::File::Close()((ulong)&puStack_110 | 8);
      if (lVar39 != 0) goto code_r0x018d9c48;
code_r0x018da82c:
      uVar30 = 6;
    }
    else {
      puVar18 = uStack_1e0;
      if (uStack_1e0 != (ulong *)0x0) goto code_r0x018d9c38;
code_r0x018d9c44:
      if (lVar39 == 0) goto code_r0x018da82c;
code_r0x018d9c48:
      if (*(int *)(lVar39 + 8) == 0) goto code_r0x018da82c;
      if ((long *)param_1[0xb2] != (long *)0x0) {
        (**(code **)(*(long *)param_1[0xb2] + 0x10))();
        param_1[0xb2] = 0;
      }
      plVar43 = (long *)operator new(unsigned long, std::nothrow_t const&)(200,PTR__ZSt7nothrow_02cb9a80);
      if (plVar43 != (long *)0x0) {
        *plVar43 = (long)(PTR__ZTVN23CGameResourceDownloader11CVerifyTaskE_02cbe2d8 + 0x10);
        plVar43[1] = 0;
        memset(plVar43 + 2,0,99);
        *(undefined4 *)((long)plVar43 + 0x8c) = 0;
        *(undefined8 *)((long)plVar43 + 0x74) = 0;
        plVar43[0x17] = 0;
        *(undefined8 *)((long)plVar43 + 0x84) = 0;
        *(undefined8 *)((long)plVar43 + 0x7c) = 0;
        plVar43[0x16] = 0;
        plVar43[0x15] = 0;
        plVar43[0x14] = 0;
        plVar43[0x13] = 0;
        *(undefined4 *)(plVar43 + 0x18) = 0x3f800000;
      }
      param_1[0xb2] = (long)plVar43;
      lVar42 = plVar43[8];
      lVar21 = param_1[0xbb];
      lVar37 = param_1[0xbc];
      plVar43[5] = lVar39;
      plVar43[6] = 0;
      *(undefined1 *)((long)plVar43 + 0x72) = 0;
      *(undefined4 *)((long)plVar43 + 0x74) = 0;
      plVar43[2] = (long)param_1;
      plVar43[3] = lVar21;
      plVar43[4] = lVar37;
      plVar43[10] = 0;
      *(undefined2 *)(plVar43 + 0xe) = 0;
      if (lVar42 != plVar43[7]) {
        plVar43[8] = lVar42 + (~((lVar42 + -8) - plVar43[7]) & 0xfffffffffffffff8U);
      }
      std::__ndk1::__hash_table<std::__ndk1::__hash_value_type<unsigned int, bool>, std::__ndk1::__unordered_map_hasher<unsigned int, std::__ndk1::__hash_value_type<unsigned int, bool>, std::__ndk1::hash<unsigned int>, true>, std::__ndk1::__unordered_map_equal<unsigned int, std::__ndk1::__hash_value_type<unsigned int, bool>, std::__ndk1::equal_to<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__hash_value_type<unsigned int, bool>, Framework::CSTLUnorderedMapAllocatorInf> >::rehash(unsigned long)(plVar43 + 0x14,*(undefined4 *)(lVar39 + 8));
      uVar30 = 5;
      plVar43[1] = 0;
    }
    *(undefined4 *)(param_1 + 0x2a) = uVar30;
    auVar24 = (undefined1  [8])puStack_70;
    puVar18 = puStack_80;
    goto joined_r0x018d674c;
  case 5:
    lVar39 = param_1[0xb2];
    if (lVar39 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02866a48/*"C:\BAS_Submission\Client\Project\..\Source\Game\Resource\GameResourceDownloader.cpp"*/,0xb14,&UNK_02866aee/*"m_pVerifyTask is null."*/);
      lVar39 = param_1[0xb2];
    }
    switch(*(undefined4 *)(lVar39 + 8)) {
    case 0:
      CGameResourceDownloader::CVerifyTask::ProgressLocalFileCheck()();
      break;
    case 1:
      CGameResourceDownloader::CVerifyTask::ProgressServerManifestCheck()();
      break;
    case 2:
      CGameResourceDownloader::CVerifyTask::ProgressEraseCheck()();
      break;
    case 3:
      CGameResourceDownloader::CVerifyTask::ProgressEraseEpisodeDataCheck()();
      break;
    case 4:
      CGameResourceDownloader::CVerifyTask::ProgressSetupManifest()();
    }
    lVar39 = param_1[0xb2];
    if (*(char *)(lVar39 + 0x71) == '\0') {
      iVar15 = *(int *)(lVar39 + 8);
      if (iVar15 == 1) {
        fVar53 = 6.0;
        fVar51 = (float)NEON_ucvtf(*(undefined4 *)(lVar39 + 0xc));
      }
      else {
        fVar51 = 0.0;
        if (iVar15 == 2) {
          plVar43 = *(long **)(lVar39 + 0x98);
          if (plVar43 == (long *)0x0) goto code_r0x018da93c;
          uVar22 = (ulong)(plVar43[1] - *plVar43) >> 8;
          uVar16 = (uint)((ulong)(plVar43[1] - *plVar43) >> 8);
        }
        else {
          if (iVar15 != 0) goto code_r0x018da93c;
          if (*(char *)(lVar39 + 0x70) == '\0') {
            lVar42 = *(long *)(lVar39 + 0x28);
          }
          else {
            lVar42 = *(long *)(lVar39 + 0x30);
          }
          if (lVar42 == 0) goto code_r0x018da93c;
          uVar16 = *(uint *)(lVar42 + 8);
          uVar22 = (ulong)uVar16;
        }
        if (uVar16 == 0) goto code_r0x018da93c;
        fVar51 = (float)*(uint *)(lVar39 + 0x74);
        fVar53 = (float)(uVar22 & 0xffffffff);
      }
      fVar51 = fVar51 / fVar53;
code_r0x018da93c:
      *(float *)(param_1 + 0x28) = fVar51 * _UNK_028014f4 + _UNK_02866098;
      return;
    }
    uVar30 = 6;
    break;
  case 6:
    *(undefined4 *)(param_1 + 0x28) = 0x3f000000;
    BAS::GetDownloadPath()(&uStack_330);
    if (((ulong)uStack_330 & 1) == 0) {
      puVar19 = (ulong *)0x16;
      puVar18 = (ulong *)((ulong)uStack_330 & 0xff);
    }
    else {
      puVar19 = (ulong *)(((ulong)uStack_330 & 0xfffffffffffffffe) - 1);
      puVar18 = uStack_330;
    }
    puVar25 = (ulong *)(ulong)(((uint)puVar18 & 0xfe) >> 1);
    if (((ulong)puVar18 & 1) != 0) {
      puVar25 = puStack_328;
    }
    if (puVar19 == puVar25) {
      string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&uStack_330,puVar19,1,puVar19,puVar19,0,1,&UNK_029c5d3e/*"/"*/);
    }
    else {
      auVar24 = (undefined1  [8])((ulong)&uStack_330 | 1);
      if (((ulong)puVar18 & 1) != 0) {
        auVar24 = auStack_320;
      }
      *(byte *)((long)auVar24 + (long)puVar25) = 0x2f;
      puVar25 = (ulong *)((long)puVar25 + 1);
      puVar18 = puVar25;
      if (((ulong)uStack_330 & 1) == 0) {
        uStack_330 = (ulong *)CONCAT71(uStack_330._1_7_,(char)puVar25 * '\x02');
        puVar18 = puStack_328;
      }
      puStack_328 = puVar18;
      *(byte *)((long)auVar24 + (long)puVar25) = 0;
    }
    uStack_1e0 = (ulong *)auStack_320;
    puStack_1e8 = puStack_328;
    puStack_1f0 = uStack_330;
    BAS::GetDownloadPath()(&uStack_330);
    if (((ulong)uStack_330 & 1) == 0) {
      puVar19 = (ulong *)0x16;
      puVar18 = (ulong *)((ulong)uStack_330 & 0xff);
    }
    else {
      puVar19 = (ulong *)(((ulong)uStack_330 & 0xfffffffffffffffe) - 1);
      puVar18 = uStack_330;
    }
    puVar25 = (ulong *)(ulong)(((uint)puVar18 & 0xfe) >> 1);
    if (((ulong)puVar18 & 1) != 0) {
      puVar25 = puStack_328;
    }
    if (puVar19 == puVar25) {
      string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&uStack_330,puVar19,1,puVar19,puVar19,0,1,&UNK_029c5d3e/*"/"*/);
    }
    else {
      auVar24 = (undefined1  [8])((ulong)&uStack_330 | 1);
      if (((ulong)puVar18 & 1) != 0) {
        auVar24 = auStack_320;
      }
      *(byte *)((long)auVar24 + (long)puVar25) = 0x2f;
      puVar25 = (ulong *)((long)puVar25 + 1);
      puVar18 = puVar25;
      if (((ulong)uStack_330 & 1) == 0) {
        uStack_330 = (ulong *)CONCAT71(uStack_330._1_7_,(char)puVar25 * '\x02');
        puVar18 = puStack_328;
      }
      puStack_328 = puVar18;
      *(byte *)((long)auVar24 + (long)puVar25) = 0;
    }
    puStack_140 = (ulong *)auStack_320;
    puStack_148 = puStack_328;
    puStack_150 = uStack_330;
    CGameResourceDownloader::CheckLocalResourceFileToolVersionOld()+0x354(&puStack_110);
    uVar41 = _UNK_02866d7e;
    if (((ulong)puStack_110 & 1) == 0) {
      lVar39 = 0x16;
      puVar18 = (ulong *)((ulong)puStack_110 & 0xff);
    }
    else {
      lVar39 = ((ulong)puStack_110 & 0xfffffffffffffffe) - 1;
      puVar18 = puStack_110;
    }
    puVar19 = (ulong *)(ulong)(((uint)puVar18 & 0xfe) >> 1);
    if (((ulong)puVar18 & 1) != 0) {
      puVar19 = puStack_108;
    }
    if ((ulong)(lVar39 - (long)puVar19) < 0x17) {
      string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&puStack_110,lVar39,(byte *)((0x17 - lVar39) + (long)puVar19),puVar19,puVar19,
                      0,0x17,&UNK_02866d7e/*"version_latest_Bulk.bin"*/);
    }
    else {
      uVar23 = CONCAT17(UNK_02866d8d,_UNK_02866d86);
      puVar25 = (ulong *)((ulong)&puStack_110 | 1);
      if (((ulong)puVar18 & 1) != 0) {
        puVar25 = puStack_100;
      }
      pbVar49 = (byte *)((long)puVar25 + (long)puVar19);
      *(ulong *)(pbVar49 + 0xf) = CONCAT71(_UNK_02866d8e,UNK_02866d8d);
      *(undefined8 *)(pbVar49 + 8) = uVar23;
      *(undefined8 *)pbVar49 = uVar41;
      puVar19 = (ulong *)((long)puVar19 + 0x17);
      puVar18 = puVar19;
      if (((ulong)puStack_110 & 1) == 0) {
        puStack_110 = (ulong *)CONCAT71(puStack_110._1_7_,(char)puVar19 * '\x02');
        puVar18 = puStack_108;
      }
      puStack_108 = puVar18;
      *(byte *)((long)puVar25 + (long)puVar19) = 0;
    }
    auStack_320 = (undefined1  [8])puStack_100;
    puStack_328 = puStack_108;
    uStack_330 = puStack_110;
    puStack_100 = (ulong *)0x0;
    bVar14 = ((ulong)puStack_110 & 1) != 0;
    puVar18 = (ulong *)((ulong)&uStack_330 | 1);
    if (bVar14) {
      puVar18 = (ulong *)auStack_320;
    }
    puVar19 = (ulong *)((ulong)puStack_110 >> 1 & 0x7f);
    if (bVar14) {
      puVar19 = puStack_108;
    }
    puStack_110 = (ulong *)0x0;
    puStack_108 = (ulong *)0x0;
    if (((ulong)puStack_1f0 & 1) == 0) {
      lVar39 = 0x16;
      puVar25 = (ulong *)((ulong)puStack_1f0 & 0xff);
    }
    else {
      lVar39 = ((ulong)puStack_1f0 & 0xfffffffffffffffe) - 1;
      puVar25 = puStack_1f0;
    }
    puVar32 = (ulong *)(ulong)(((uint)puVar25 & 0xfe) >> 1);
    if (((ulong)puVar25 & 1) != 0) {
      puVar32 = puStack_1e8;
    }
    if ((ulong *)(lVar39 - (long)puVar32) < puVar19) {
      string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&puStack_1f0,lVar39,(byte *)(((long)puVar19 - lVar39) + (long)puVar32),puVar32
                      ,puVar32,0,puVar19);
    }
    else if (puVar19 != (ulong *)0x0) {
      puVar3 = (ulong *)((ulong)&puStack_1f0 | 1);
      if (((ulong)puVar25 & 1) != 0) {
        puVar3 = uStack_1e0;
      }
      memcpy((byte *)((long)puVar3 + (long)puVar32),puVar18,puVar19);
      puVar32 = (ulong *)((long)puVar32 + (long)puVar19);
      if (((ulong)puStack_1f0 & 1) == 0) {
        puStack_1f0 = (ulong *)CONCAT71(puStack_1f0._1_7_,(char)puVar32 * '\x02');
        *(byte *)((long)puVar3 + (long)puVar32) = 0;
      }
      else {
        *(byte *)((long)puVar3 + (long)puVar32) = 0;
        puStack_1e8 = puVar32;
      }
    }
    if (((ulong)uStack_330 & 1) != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(auStack_320);
    }
    if (((ulong)puStack_110 & 1) != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puStack_100);
    }
    CGameResourceDownloader::CheckLocalResourceFileToolVersionOld()+0x354(&puStack_110);
    uVar41 = _UNK_02866e24;
    if (((ulong)puStack_110 & 1) == 0) {
      lVar39 = 0x16;
      puVar18 = (ulong *)((ulong)puStack_110 & 0xff);
    }
    else {
      lVar39 = ((ulong)puStack_110 & 0xfffffffffffffffe) - 1;
      puVar18 = puStack_110;
    }
    puVar19 = (ulong *)(ulong)(((uint)puVar18 & 0xfe) >> 1);
    if (((ulong)puVar18 & 1) != 0) {
      puVar19 = puStack_108;
    }
    if ((ulong)(lVar39 - (long)puVar19) < 0x1d) {
      string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&puStack_110,lVar39,(byte *)((0x1d - lVar39) + (long)puVar19),puVar19,puVar19,
                      0,0x1d,&UNK_02866e24/*"version_latest_Individual.bin"*/);
    }
    else {
      uVar11 = CONCAT53(_UNK_02866e34,_UNK_02866e31);
      uVar23 = CONCAT35(_UNK_02866e31,_UNK_02866e2c);
      puVar25 = (ulong *)((ulong)&puStack_110 | 1);
      if (((ulong)puVar18 & 1) != 0) {
        puVar25 = puStack_100;
      }
      pbVar49 = (byte *)((long)puVar25 + (long)puVar19);
      *(undefined8 *)(pbVar49 + 0x15) = _UNK_02866e39;
      *(undefined8 *)(pbVar49 + 0xd) = uVar11;
      *(undefined8 *)(pbVar49 + 8) = uVar23;
      *(undefined8 *)pbVar49 = uVar41;
      puVar19 = (ulong *)((long)puVar19 + 0x1d);
      puVar32 = puVar19;
      if (((ulong)puVar18 & 1) == 0) {
        puStack_110 = (ulong *)CONCAT71(puStack_110._1_7_,(char)puVar19 * '\x02');
        puVar32 = puStack_108;
      }
      puStack_108 = puVar32;
      *(byte *)((long)puVar25 + (long)puVar19) = 0;
    }
    auStack_320 = (undefined1  [8])puStack_100;
    puStack_328 = puStack_108;
    uStack_330 = puStack_110;
    puStack_100 = (ulong *)0x0;
    bVar14 = ((ulong)puStack_110 & 1) != 0;
    puVar18 = (ulong *)((ulong)&uStack_330 | 1);
    if (bVar14) {
      puVar18 = (ulong *)auStack_320;
    }
    puVar19 = (ulong *)((ulong)puStack_110 >> 1 & 0x7f);
    if (bVar14) {
      puVar19 = puStack_108;
    }
    puStack_110 = (ulong *)0x0;
    puStack_108 = (ulong *)0x0;
    if (((ulong)puStack_150 & 1) == 0) {
      lVar39 = 0x16;
      puVar25 = (ulong *)((ulong)puStack_150 & 0xff);
    }
    else {
      lVar39 = ((ulong)puStack_150 & 0xfffffffffffffffe) - 1;
      puVar25 = puStack_150;
    }
    puVar32 = (ulong *)(ulong)(((uint)puVar25 & 0xfe) >> 1);
    if (((ulong)puVar25 & 1) != 0) {
      puVar32 = puStack_148;
    }
    if ((ulong *)(lVar39 - (long)puVar32) < puVar19) {
      string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&puStack_150,lVar39,(byte *)(((long)puVar19 - lVar39) + (long)puVar32),puVar32
                      ,puVar32,0,puVar19);
    }
    else if (puVar19 != (ulong *)0x0) {
      puVar3 = (ulong *)((ulong)&puStack_150 | 1);
      if (((ulong)puVar25 & 1) != 0) {
        puVar3 = puStack_140;
      }
      memcpy((byte *)((long)puVar3 + (long)puVar32),puVar18,puVar19);
      puVar32 = (ulong *)((long)puVar32 + (long)puVar19);
      if (((ulong)puStack_150 & 1) == 0) {
        puStack_150 = (ulong *)CONCAT71(puStack_150._1_7_,(char)puVar32 * '\x02');
        *(byte *)((long)puVar3 + (long)puVar32) = 0;
      }
      else {
        *(byte *)((long)puVar3 + (long)puVar32) = 0;
        puStack_148 = puVar32;
      }
    }
    if (((ulong)uStack_330 & 1) != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(auStack_320);
    }
    if (((ulong)puStack_110 & 1) != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puStack_100);
    }
    uVar22 = CGameResourceDownloader::LoadVersionFileToAson(string const&, string const&)(param_1,&puStack_1f0,&puStack_150);
    uVar22 = uVar22 & 0xffffffff;
    if ((int)param_1[0x4f] != 0) {
      uVar16 = 0;
      do {
        uVar48 = (ulong)uVar16;
        if ((ulong)param_1[0xb7] <= uVar48) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dc536/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Vector.h"*/,0x58,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,uVar48);
        }
        if ((*(ulong *)(param_1[0xb6] + ((ulong)(uVar16 >> 3) & 0x1ffffff8)) & 1L << (uVar48 & 0x3f)
            ) != 0) {
          BAS::GetDownloadPath()(&uStack_330);
          if (((ulong)uStack_330 & 1) == 0) {
            puVar19 = (ulong *)0x16;
            puVar18 = (ulong *)((ulong)uStack_330 & 0xff);
          }
          else {
            puVar19 = (ulong *)(((ulong)uStack_330 & 0xfffffffffffffffe) - 1);
            puVar18 = uStack_330;
          }
          puVar25 = (ulong *)(ulong)(((uint)puVar18 & 0xfe) >> 1);
          if (((ulong)puVar18 & 1) != 0) {
            puVar25 = puStack_328;
          }
          if (puVar19 == puVar25) {
            string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&uStack_330,puVar19,1,puVar19,puVar19,0,1,&UNK_029c5d3e/*"/"*/);
          }
          else {
            auVar24 = (undefined1  [8])((ulong)&uStack_330 | 1);
            if (((ulong)puVar18 & 1) != 0) {
              auVar24 = auStack_320;
            }
            *(byte *)((long)auVar24 + (long)puVar25) = 0x2f;
            puVar25 = (ulong *)((long)puVar25 + 1);
            puVar18 = puVar25;
            if (((ulong)uStack_330 & 1) == 0) {
              uStack_330 = (ulong *)CONCAT71(uStack_330._1_7_,(char)puVar25 * '\x02');
              puVar18 = puStack_328;
            }
            puStack_328 = puVar18;
            *(byte *)((long)auVar24 + (long)puVar25) = 0;
          }
          puStack_220 = (ulong *)auStack_320;
          puStack_228 = puStack_328;
          puStack_230 = uStack_330;
          CGameResourceDownloader::CheckLocalResourceFileToolVersionOld()+0x354(&puStack_80);
          puVar18 = (ulong *)((ulong)puStack_80 >> 1 & 0x7f);
          puVar19 = (ulong *)((ulong)&puStack_80 | 1);
          if (((ulong)puStack_80 & 1) != 0) {
            puVar18 = puStack_78;
            puVar19 = puStack_70;
          }
          if (((ulong)puStack_230 & 1) == 0) {
            lVar39 = 0x16;
            puVar25 = (ulong *)((ulong)puStack_230 & 0xff);
          }
          else {
            lVar39 = ((ulong)puStack_230 & 0xfffffffffffffffe) - 1;
            puVar25 = puStack_230;
          }
          puVar32 = (ulong *)(ulong)(((uint)puVar25 & 0xfe) >> 1);
          if (((ulong)puVar25 & 1) != 0) {
            puVar32 = puStack_228;
          }
          if ((ulong *)(lVar39 - (long)puVar32) < puVar18) {
            string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&puStack_230,lVar39,(byte *)(((long)puVar18 - lVar39) + (long)puVar32),
                            puVar32,puVar32,0,puVar18);
          }
          else if (puVar18 != (ulong *)0x0) {
            puVar3 = (ulong *)((ulong)&puStack_230 | 1);
            if (((ulong)puVar25 & 1) != 0) {
              puVar3 = puStack_220;
            }
            memcpy((byte *)((long)puVar3 + (long)puVar32),puVar19,puVar18);
            puVar32 = (ulong *)((long)puVar32 + (long)puVar18);
            puVar18 = puVar32;
            if (((ulong)puStack_230 & 1) == 0) {
              puStack_230 = (ulong *)CONCAT71(puStack_230._1_7_,(char)puVar32 * '\x02');
              puVar18 = puStack_228;
            }
            puStack_228 = puVar18;
            *(byte *)((long)puVar3 + (long)puVar32) = 0;
          }
          puStack_108 = puStack_228;
          puStack_110 = puStack_230;
          puStack_100 = puStack_220;
          puStack_228 = (ulong *)0x0;
          puStack_220 = (ulong *)0x0;
          puStack_230 = (ulong *)0x0;
          Framework::CSTLStringUtility_Base<string >::Format(char const*, ...)(&puStack_a0,&UNK_02866b05/*"version_latest_ep%d.bin"*/,uVar16 + 1);
          puVar18 = (ulong *)((ulong)puStack_a0 >> 1 & 0x7f);
          puVar19 = (ulong *)((ulong)&puStack_a0 | 1);
          if (((ulong)puStack_a0 & 1) != 0) {
            puVar18 = puStack_98;
            puVar19 = puStack_90;
          }
          if (((ulong)puStack_110 & 1) == 0) {
            lVar39 = 0x16;
            puVar25 = (ulong *)((ulong)puStack_110 & 0xff);
          }
          else {
            lVar39 = ((ulong)puStack_110 & 0xfffffffffffffffe) - 1;
            puVar25 = puStack_110;
          }
          puVar32 = (ulong *)(ulong)(((uint)puVar25 & 0xfe) >> 1);
          if (((ulong)puVar25 & 1) != 0) {
            puVar32 = puStack_108;
          }
          if ((ulong *)(lVar39 - (long)puVar32) < puVar18) {
            string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&puStack_110,lVar39,(byte *)(((long)puVar18 - lVar39) + (long)puVar32),
                            puVar32,puVar32,0,puVar18);
          }
          else if (puVar18 != (ulong *)0x0) {
            puVar3 = (ulong *)((ulong)&puStack_110 | 1);
            if (((ulong)puVar25 & 1) != 0) {
              puVar3 = puStack_100;
            }
            memcpy((byte *)((long)puVar3 + (long)puVar32),puVar19,puVar18);
            puVar32 = (ulong *)((long)puVar32 + (long)puVar18);
            puVar18 = puVar32;
            if (((ulong)puStack_110 & 1) == 0) {
              puStack_110 = (ulong *)CONCAT71(puStack_110._1_7_,(char)puVar32 * '\x02');
              puVar18 = puStack_108;
            }
            puStack_108 = puVar18;
            *(byte *)((long)puVar3 + (long)puVar32) = 0;
          }
          auStack_320 = (undefined1  [8])puStack_100;
          uStack_330 = puStack_110;
          puStack_110 = (ulong *)0x0;
          puStack_100 = (ulong *)0x0;
          puStack_328 = puStack_108;
          puStack_108 = (ulong *)0x0;
          if ((((ulong)puStack_a0 & 1) != 0) &&
             (Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puStack_90), ((ulong)puStack_110 & 1) != 0)) {
            Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puStack_100);
          }
          if (((ulong)puStack_80 & 1) != 0) {
            Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puStack_70);
          }
          if (((ulong)puStack_230 & 1) != 0) {
            Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puStack_220);
          }
          uVar22 = CGameResourceDownloader::LoadVersionFileToAsonEpisodeData(string const&)(param_1,&uStack_330);
          if (((ulong)uStack_330 & 1) != 0) {
            Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(auStack_320);
          }
          if ((uVar22 & 1) == 0) goto code_r0x018d7f74;
          uVar22 = 1;
        }
        uVar16 = uVar16 + 1;
      } while (uVar16 < *(uint *)(param_1 + 0x4f));
    }
    if ((uVar22 & 1) == 0) {
code_r0x018d7f74:
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02866a48/*"C:\BAS_Submission\Client\Project\..\Source\Game\Resource\GameResourceDownloader.cpp"*/,0xb47,&UNK_02866b4d/*"isLocalDataLoad FALSE"*/);
      iVar15 = 0x1a;
      *(undefined1 *)((long)param_1 + 0x154) = 1;
      *(undefined4 *)(param_1 + 0x2a) = 0xf;
    }
    else {
      iVar15 = 0;
    }
    if (((ulong)puStack_150 & 1) != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puStack_140);
    }
    if (((ulong)puStack_1f0 & 1) != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_1e0);
    }
    if (iVar15 == 0) {
      lVar39 = Aska::ASON::AValue::AMap::Get_(char const*)(param_1 + 0x6f,&UNK_02866dc9/*"assets"*/);
      if (*(char *)((long)param_1 + 0x155) == '\0') {
        lVar42 = 0;
      }
      else {
        lVar42 = Aska::ASON::AValue::AMap::Get_(char const*)(param_1 + 0x81,&UNK_02866dc9/*"assets"*/);
        lVar42 = lVar42 + 8;
      }
      lVar21 = Aska::ASON::AValue::AMap::Get_(char const*)(param_1 + 0x6f,&UNK_02866d96/*"toolversion"*/);
      if (lVar21 != 0) {
        uVar41 = *(undefined8 *)(lVar21 + 0x10);
        iVar15 = strcmp(uVar41,&UNK_02866a9c/*"1.2.0"*/);
        if (iVar15 != 0) {
          iVar15 = strcmp(uVar41,&UNK_02866b63/*"1.0.1"*/);
          if (iVar15 != 0) goto code_r0x018d8618;
          *(undefined1 *)((long)param_1 + 0x15e) = 1;
        }
        if ((lVar42 == 0) && (*(char *)((long)param_1 + 0x155) != '\0')) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02866a48/*"C:\BAS_Submission\Client\Project\..\Source\Game\Resource\GameResourceDownloader.cpp"*/,0xb86,&UNK_02866b69/*"rootMapSub is null."*/);
        }
        if ((long *)param_1[0xb2] != (long *)0x0) {
          (**(code **)(*(long *)param_1[0xb2] + 0x10))();
          param_1[0xb2] = 0;
        }
        plVar43 = (long *)operator new(unsigned long, std::nothrow_t const&)(200,PTR__ZSt7nothrow_02cb9a80);
        if (plVar43 != (long *)0x0) {
          *plVar43 = (long)(PTR__ZTVN23CGameResourceDownloader11CVerifyTaskE_02cbe2d8 + 0x10);
          plVar43[1] = 0;
          memset(plVar43 + 2,0,99);
          *(undefined4 *)((long)plVar43 + 0x8c) = 0;
          *(undefined8 *)((long)plVar43 + 0x74) = 0;
          plVar43[0x17] = 0;
          *(undefined8 *)((long)plVar43 + 0x84) = 0;
          *(undefined8 *)((long)plVar43 + 0x7c) = 0;
          plVar43[0x16] = 0;
          plVar43[0x15] = 0;
          plVar43[0x14] = 0;
          plVar43[0x13] = 0;
          *(undefined4 *)(plVar43 + 0x18) = 0x3f800000;
        }
        param_1[0xb2] = (long)plVar43;
        lVar21 = plVar43[8];
        lVar37 = param_1[0xbb];
        lVar38 = param_1[0xbc];
        plVar43[5] = lVar39 + 8;
        plVar43[6] = lVar42;
        *(undefined1 *)((long)plVar43 + 0x72) = 0;
        *(undefined4 *)((long)plVar43 + 0x74) = 0;
        plVar43[2] = (long)param_1;
        plVar43[3] = lVar37;
        plVar43[4] = lVar38;
        plVar43[10] = 0;
        *(undefined2 *)(plVar43 + 0xe) = 0;
        if (lVar21 != plVar43[7]) {
          plVar43[8] = lVar21 + (~((lVar21 + -8) - plVar43[7]) & 0xfffffffffffffff8U);
        }
        uVar16 = *(uint *)(lVar39 + 0x10);
        uVar10 = uVar16;
        if ((lVar42 != 0) && (uVar10 = *(uint *)(lVar42 + 8), *(uint *)(lVar42 + 8) <= uVar16)) {
          uVar10 = uVar16;
        }
        std::__ndk1::__hash_table<std::__ndk1::__hash_value_type<unsigned int, bool>, std::__ndk1::__unordered_map_hasher<unsigned int, std::__ndk1::__hash_value_type<unsigned int, bool>, std::__ndk1::hash<unsigned int>, true>, std::__ndk1::__unordered_map_equal<unsigned int, std::__ndk1::__hash_value_type<unsigned int, bool>, std::__ndk1::equal_to<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__hash_value_type<unsigned int, bool>, Framework::CSTLUnorderedMapAllocatorInf> >::rehash(unsigned long)(plVar43 + 0x14,uVar10);
        plVar43[1] = 1;
        lVar42 = param_1[0x87];
        lVar39 = param_1[0x86];
        if (lVar42 != lVar39) {
          puVar18 = (ulong *)0x0;
          uVar22 = 0;
          uVar48 = 1;
          do {
            uVar29 = (lVar42 - lVar39 >> 4) * -0x71c71c71c71c71c7;
            if (uVar29 < uVar22 || uVar29 - uVar22 == 0) {
              Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dc536/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Vector.h"*/,0x58,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,uVar22);
              lVar39 = param_1[0x86];
            }
            lVar39 = Aska::ASON::AValue::AMap::Get_(char const*)(lVar39 + uVar22 * 0x90 + 0x68,&UNK_02866dc9/*"assets"*/);
            lVar42 = param_1[0xb2];
            if (lVar39 != 0) {
              puVar18 = (ulong *)(lVar39 + 8);
            }
            uStack_330 = puVar18;
            if ((*(uint *)(lVar42 + 8) | 2) == 3) {
              puVar7 = *(undefined8 **)(lVar42 + 0x40);
              if (puVar7 == *(undefined8 **)(lVar42 + 0x48)) {
                void std::__ndk1::vector<Aska::ASON::AValue::AMap const*, Framework::CSTLAllocator<Aska::ASON::AValue::AMap const*, Framework::CSTLVectorAllocatorInf> >::__push_back_slow_path<Aska::ASON::AValue::AMap const* const&>(Aska::ASON::AValue::AMap const* const&)(lVar42 + 0x38,&uStack_330);
              }
              else {
                if (puVar7 == (undefined8 *)0x0) {
                  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
                }
                *puVar7 = puVar18;
                *(long *)(lVar42 + 0x40) = *(long *)(lVar42 + 0x40) + 8;
              }
            }
            lVar42 = param_1[0x87];
            lVar39 = param_1[0x86];
            uVar22 = (lVar42 - lVar39 >> 4) * -0x71c71c71c71c71c7;
            bVar14 = uVar48 <= uVar22;
            lVar21 = uVar22 - uVar48;
            uVar22 = uVar48;
            uVar48 = (ulong)((int)uVar48 + 1);
          } while (bVar14 && lVar21 != 0);
        }
        uVar30 = 7;
        break;
      }
code_r0x018d8618:
      *(undefined1 *)((long)param_1 + 0x154) = 1;
      *(undefined4 *)(param_1 + 0x2a) = 0xf;
    }
  case 0xf:
    Aska::ASON::Term()(param_1 + 0x50);
    Aska::ASON::Term()(param_1 + 0x62);
    Aska::ASON::Term()(param_1 + 0x74);
    lVar42 = param_1[0x87];
    lVar39 = param_1[0x86];
    if ((lVar42 != lVar39) && (lVar39 != lVar42)) {
      do {
        Aska::ASON::ASON(Aska::ASON const&)(&uStack_330,lVar39);
        Aska::ASON::Term()(&uStack_330);
        Aska::ASON::~ASON()(&uStack_330);
        lVar39 = lVar39 + 0x90;
      } while (lVar42 != lVar39);
      lVar39 = param_1[0x86];
      while (lVar42 = param_1[0x87], lVar42 != lVar39) {
        param_1[0x87] = lVar42 + -0x90;
        (*(code *)**(undefined8 **)(lVar42 + -0x90))();
      }
    }
    if (param_1[0x91] != 0) {
      operator delete[](void*)();
      param_1[0x91] = 0;
    }
    if (param_1[0x92] != 0) {
      operator delete[](void*)();
      param_1[0x92] = 0;
    }
    if (param_1[0x93] != 0) {
      operator delete[](void*)();
      param_1[0x93] = 0;
    }
    plVar40 = (long *)param_1[0x95];
    plVar43 = (long *)param_1[0x94];
    if ((plVar40 != plVar43) && (plVar43 != plVar40)) {
      do {
        if (*plVar43 != 0) {
          operator delete[](void*)();
        }
        plVar43 = plVar43 + 1;
      } while (plVar40 != plVar43);
      lVar39 = param_1[0x95];
      if (lVar39 != param_1[0x94]) {
        param_1[0x95] = lVar39 + (~((lVar39 + -8) - param_1[0x94]) & 0xfffffffffffffff8U);
      }
    }
    if ((long *)param_1[0xb2] != (long *)0x0) {
      (**(code **)(*(long *)param_1[0xb2] + 0x10))();
      param_1[0xb2] = 0;
    }
    *(undefined4 *)(param_1 + 0x4d) = 0;
    *(undefined4 *)(param_1 + 0x28) = 0x3f800000;
    *(undefined1 *)((long)param_1 + 0x156) = 1;
    *(undefined4 *)((long)param_1 + 0x14c) = 4;
    *(undefined4 *)(param_1 + 0x2a) = 0;
    param_1[0x1a] = 0;
    if (0 < param_1[0x19]) {
      lVar39 = 0;
      do {
        lVar42 = param_1[0x17];
        pbVar49 = (byte *)(lVar42 + lVar39 * 0x50);
        if ((*pbVar49 & 1) == 0) {
          pbVar44 = pbVar49 + 1;
        }
        else {
          pbVar44 = *(byte **)(lVar42 + lVar39 * 0x50 + 0x10);
        }
        plVar40 = (long *)(lVar42 + lVar39 * 0x50 + 0x40);
        plVar43 = (long *)*plVar40;
        if (plVar43 == (long *)0x0) {
          plStack_340 = (long *)0x0;
        }
        else if ((long *)(lVar42 + lVar39 * 0x50 + 0x20) == plVar43) {
          plStack_340 = alStack_360;
          (**(code **)(*plVar43 + 0x18))(plVar43,alStack_360);
        }
        else {
          plStack_340 = (long *)(**(code **)(*plVar43 + 0x10))();
        }
        uVar22 = CGameResourceDownloader::RequestDownload(char const*, std::__ndk1::function<void (char const*, CGameResourceDownloader::iErrorCode)>)(param_1,pbVar44,alStack_360);
        if (alStack_360 == plStack_340) {
          pcVar33 = *(code **)(*plStack_340 + 0x20);
code_r0x018d8834:
          (*pcVar33)(plStack_340);
        }
        else if (plStack_340 != (long *)0x0) {
          pcVar33 = *(code **)(*plStack_340 + 0x28);
          goto code_r0x018d8834;
        }
        if ((uVar22 & 1) == 0) {
          if ((*pbVar49 & 1) == 0) {
            uStack_330 = (ulong *)(pbVar49 + 1);
          }
          else {
            uStack_330 = *(ulong **)(lVar42 + lVar39 * 0x50 + 0x10);
          }
          puStack_1f0 = (ulong *)((ulong)puStack_1f0 & 0xffffffff00000000);
          plVar40 = (long *)*plVar40;
          (**(code **)(*plVar40 + 0x30))(plVar40,&uStack_330,&puStack_1f0);
        }
        lVar39 = param_1[0x1a] + 1;
        param_1[0x1a] = lVar39;
      } while (lVar39 < param_1[0x19]);
    }
    Aska::TArray<CGameResourceDownloader::tDownloadNodeInitializer, false>::Clear()(param_1 + 0x16);
    goto code_r0x018db484;
  case 7:
    lVar39 = param_1[0xb2];
    if (lVar39 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02866a48/*"C:\BAS_Submission\Client\Project\..\Source\Game\Resource\GameResourceDownloader.cpp"*/,0xbb3,&UNK_02866aee/*"m_pVerifyTask is null."*/);
      lVar39 = param_1[0xb2];
    }
    switch(*(undefined4 *)(lVar39 + 8)) {
    case 0:
      CGameResourceDownloader::CVerifyTask::ProgressLocalFileCheck()();
      break;
    case 1:
      CGameResourceDownloader::CVerifyTask::ProgressServerManifestCheck()();
      break;
    case 2:
      CGameResourceDownloader::CVerifyTask::ProgressEraseCheck()();
      break;
    case 3:
      CGameResourceDownloader::CVerifyTask::ProgressEraseEpisodeDataCheck()();
      break;
    case 4:
      CGameResourceDownloader::CVerifyTask::ProgressSetupManifest()();
    }
    lVar39 = param_1[0xb2];
    if (*(char *)(lVar39 + 0x71) == '\0') {
      iVar15 = *(int *)(lVar39 + 8);
      if (iVar15 == 1) {
        fVar53 = 6.0;
        fVar51 = (float)NEON_ucvtf(*(undefined4 *)(lVar39 + 0xc));
code_r0x018da974:
        fVar51 = fVar51 / fVar53;
      }
      else {
        fVar51 = 0.0;
        if (iVar15 == 2) {
          plVar43 = *(long **)(lVar39 + 0x98);
          if (plVar43 != (long *)0x0) {
            uVar22 = (ulong)(plVar43[1] - *plVar43) >> 8;
            uVar16 = (uint)((ulong)(plVar43[1] - *plVar43) >> 8);
joined_r0x018d9574:
            if (uVar16 != 0) {
              fVar51 = (float)*(uint *)(lVar39 + 0x74);
              fVar53 = (float)(uVar22 & 0xffffffff);
              goto code_r0x018da974;
            }
          }
        }
        else if (iVar15 == 0) {
          if (*(char *)(lVar39 + 0x70) == '\0') {
            lVar42 = *(long *)(lVar39 + 0x28);
          }
          else {
            lVar42 = *(long *)(lVar39 + 0x30);
          }
          if (lVar42 != 0) {
            uVar16 = *(uint *)(lVar42 + 8);
            uVar22 = (ulong)uVar16;
            goto joined_r0x018d9574;
          }
        }
      }
      fVar51 = fVar51 * _UNK_028014f4;
      fVar53 = 0.5;
      goto code_r0x018da988;
    }
    uVar30 = 10;
    break;
  default:
    goto code_r0x018db484;
  case 10:
    lVar39 = param_1[0xbb];
    if ((int)param_1[0x6e] == 7) {
      puStack_328 = (ulong *)0x0;
      auStack_320 = (undefined1  [8])0x0;
      uStack_330 = (ulong *)0x0;
      lVar42 = Aska::ASON::AValue::AMap::Get_(char const*)(param_1 + 0x6f,&UNK_02a354cc/*"version"*/);
      uVar41 = *(undefined8 *)(lVar42 + 0x10);
      puVar18 = (ulong *)strlen(uVar41);
      if (puVar18 < (ulong *)0x17) {
        if (puVar18 != (ulong *)0x0) {
          memmove((ulong)&uStack_330 | 1,uVar41,puVar18);
        }
        *(byte *)((long)&uStack_330 + 1 + (long)puVar18) = 0;
        uStack_330 = (ulong *)CONCAT71(uStack_330._1_7_,(char)((long)puVar18 << 1));
      }
      else {
        puVar19 = puVar18;
        if (puVar18 < (ulong *)0x2d) {
          puVar19 = (ulong *)0x2c;
        }
        if (puVar19 < (ulong *)0x17) {
          uVar22 = 0x17;
        }
        else {
          uVar22 = (ulong)(puVar19 + 2) & 0xfffffffffffffff0;
          if (uVar22 == 0) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
          }
        }
        puVar19 = (ulong *)Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar22,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
        if (puVar19 == (ulong *)0x0) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
        }
        memcpy(puVar19,uVar41,puVar18);
        uStack_330 = (ulong *)(uVar22 | 1);
        *(byte *)((long)puVar19 + (long)puVar18) = 0;
        puStack_328 = puVar18;
        auStack_320 = (undefined1  [8])puVar19;
      }
      puVar18 = (ulong *)(lVar39 + 0x10);
      if (puVar18 != &uStack_330) {
        uVar22 = (ulong)*(byte *)puVar18;
        puVar19 = (ulong *)((ulong)uStack_330 >> 1 & 0x7f);
        auVar24 = (undefined1  [8])((ulong)&uStack_330 | 1);
        if (((ulong)uStack_330 & 1) != 0) {
          puVar19 = puStack_328;
          auVar24 = auStack_320;
        }
        if ((*(byte *)puVar18 & 1) == 0) {
          puVar25 = (ulong *)0x16;
          pbVar49 = (byte *)((long)puVar19 + -0x16);
          if ((ulong *)0x15 < puVar19 && pbVar49 != (byte *)0x0) goto code_r0x018d8950;
        }
        else {
          uVar22 = *puVar18;
          puVar25 = (ulong *)((uVar22 & 0xfffffffffffffffe) - 1);
          pbVar49 = (byte *)((long)puVar19 - (long)puVar25);
          if (puVar25 <= puVar19 && pbVar49 != (byte *)0x0) {
code_r0x018d8950:
            if ((uVar22 & 1) == 0) {
              uVar22 = (ulong)(((uint)uVar22 & 0xfe) >> 1);
            }
            else {
              uVar22 = *(ulong *)(lVar39 + 0x18);
            }
            string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(puVar18,puVar25,pbVar49,uVar22,0,uVar22,puVar19);
            goto joined_r0x018d89a8;
          }
        }
        if ((uVar22 & 1) == 0) {
          lVar42 = lVar39 + 0x11;
        }
        else {
          lVar42 = *(long *)(lVar39 + 0x20);
        }
        if (puVar19 != (ulong *)0x0) {
          memmove(lVar42,auVar24,puVar19);
        }
        *(byte *)(lVar42 + (long)puVar19) = 0;
        if ((*(byte *)puVar18 & 1) == 0) {
          *(byte *)puVar18 = (byte)((long)puVar19 << 1);
        }
        else {
          *(ulong **)(lVar39 + 0x18) = puVar19;
        }
      }
joined_r0x018d89a8:
      if (((ulong)uStack_330 & 1) != 0) {
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(auStack_320);
      }
      lVar39 = param_1[0xbb];
    }
    if (*(int *)(lVar39 + 0x68) != 0) {
      pcVar47 = *(char **)(lVar39 + 0x78);
      lVar39 = *(long *)(lVar39 + 0x80);
      pcVar46 = pcVar47;
      if (lVar39 == 0) {
code_r0x018d8e10:
        pcVar47 = pcVar47 + lVar39 * 0xc0;
        if (pcVar46 != pcVar47) {
          do {
            if ((pcVar46[8] & 1U) == 0) {
              uVar22 = CGameResourceDownloader::CVerifyTask::IsLatestAsset(char const*) const(param_1[0xb2],pcVar46 + 9);
            }
            else {
              uVar22 = CGameResourceDownloader::CVerifyTask::IsLatestAsset(char const*) const(param_1[0xb2],*(undefined8 *)(pcVar46 + 0x18));
            }
            pcVar45 = pcVar46;
            if ((uVar22 & 1) == 0) {
              if ((pcVar46[8] & 1U) == 0) {
                pcVar46 = pcVar46 + 9;
              }
              else {
                pcVar46 = *(char **)(pcVar46 + 0x18);
              }
              cVar36 = *pcVar46;
              uStack_330._1_7_ = (undefined7)((ulong)uStack_330 >> 8);
              uStack_330 = (ulong *)CONCAT71(uStack_330._1_7_,cVar36);
              lVar39 = 0;
              do {
                lVar42 = lVar39;
                if (cVar36 == '\0') goto code_r0x018d8e9c;
                cVar36 = pcVar46[lVar42 + 1];
                *(char *)((long)&uStack_330 + lVar42 + 1) = cVar36;
                lVar39 = lVar42 + 1;
              } while ((int)(lVar42 + 1) < 0xff);
              *(undefined1 *)((long)&uStack_330 + lVar42 + 1) = 0;
code_r0x018d8e9c:
              lVar39 = param_1[0x8c];
              if (-1 < lVar39) {
                Aska::TArray<Framework::TStaticString<256ul>, false>::Resize(long, bool)(param_1 + 0x89,lVar39 + 1,0);
                memcpy(param_1[0x8a] + lVar39 * 0x100,&uStack_330,0x100);
              }
            }
            do {
              pcVar46 = pcVar47;
              if (pcVar47 == pcVar45) break;
              pcVar46 = pcVar45 + 0xc0;
              pcVar45 = pcVar46;
            } while (*pcVar46 != '\x01');
          } while (pcVar46 !=
                   (char *)(*(long *)(param_1[0xbb] + 0x78) + *(long *)(param_1[0xbb] + 0x80) * 0xc0
                           ));
        }
      }
      else {
        lVar42 = lVar39 * 0xc0;
        do {
          if (*pcVar46 == '\x01') goto code_r0x018d8e10;
          lVar42 = lVar42 + -0xc0;
          pcVar46 = pcVar46 + 0xc0;
        } while (lVar42 != 0);
      }
    }
    uVar30 = 0xb;
    break;
  case 0xb:
    param_1[0x8d] = 0;
    if (0 < param_1[0x8c]) {
      lVar39 = 0;
      do {
        lVar39 = param_1[0x8a] + lVar39 * 0x100;
        uVar22 = CGameResourceDownloader::CVerifyTask::IsLatestAsset(char const*) const(param_1[0xb2],lVar39);
        if ((uVar22 & 1) == 0) {
          lVar42 = param_1[0xbb];
          puStack_328 = (ulong *)0x0;
          auStack_320 = (undefined1  [8])0x0;
          uStack_330 = (ulong *)0x0;
          puVar18 = (ulong *)strlen(lVar39);
          if (puVar18 < (ulong *)0x17) {
            uStack_330 = (ulong *)CONCAT71(uStack_330._1_7_,(char)((long)puVar18 << 1));
            puVar19 = (ulong *)((ulong)&uStack_330 | 1);
            if (puVar18 != (ulong *)0x0) goto code_r0x018d6674;
          }
          else {
            uVar22 = (ulong)(puVar18 + 2) & 0xfffffffffffffff0;
            if (uVar22 == 0) {
              Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
            }
            puVar19 = (ulong *)Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar22,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
            if (puVar19 == (ulong *)0x0) {
              Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
            }
            uStack_330 = (ulong *)(uVar22 | 1);
            puStack_328 = puVar18;
            auStack_320 = (undefined1  [8])puVar19;
code_r0x018d6674:
            memcpy(puVar19,lVar39,puVar18);
          }
          *(byte *)((long)puVar19 + (long)puVar18) = 0;
          Aska::THashMap<string, CAssetInfo, Hasher_CSTLString, Aska::TEqualTo<string >, Aska::TAllocator<Aska::TPair<string const, CAssetInfo> > >::Erase(string const&)(lVar42 + 0x58,&uStack_330);
          if (((ulong)uStack_330 & 1) != 0) {
            Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(auStack_320);
          }
        }
        lVar39 = param_1[0x8d] + 1;
        param_1[0x8d] = lVar39;
      } while (lVar39 < param_1[0x8c]);
    }
    uVar30 = 0xc;
    break;
  case 0xc:
    *(undefined1 *)(param_1 + 0x2b) = 0;
    plVar43 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x50,PTR__ZSt7nothrow_02cb9a80);
    if (plVar43 != (long *)0x0) {
      lVar39 = param_1[0xbb];
      Framework::CFiberUnit::CFiberUnit(unsigned int)(plVar43,0x600);
      puVar1 = PTR__ZTVN23CGameResourceDownloader16CEraseCheckFiberE_02cb6f20;
      plVar43[7] = (long)param_1;
      plVar43[8] = lVar39;
      plVar43[9] = 0;
      *plVar43 = (long)(puVar1 + 0x10);
    }
    (**(code **)(*param_1 + 0x48))(param_1,plVar43);
    BAS::GetDownloadPath()(&uStack_330);
    auVar24 = (undefined1  [8])((ulong)&uStack_330 | 1);
    if (((ulong)uStack_330 & 1) != 0) {
      auVar24 = auStack_320;
    }
    BAS::SetNoBackupFolder(char const*)(auVar24);
    *(undefined4 *)(param_1 + 0x2a) = 0xe;
    auVar24 = auStack_320;
    puVar18 = uStack_330;
joined_r0x018d674c:
    if (((ulong)puVar18 & 1) == 0) {
      return;
    }
code_r0x018db480:
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(auVar24);
    return;
  case 0xe:
    if ((char)param_1[0x2b] == '\0') {
      return;
    }
    iVar15 = CGameResourceDownloader::NeedNumDownload() const(param_1);
    if ((iVar15 != 0) || (*(char *)((long)param_1 + 0x15d) == '\0')) goto code_r0x018d7010;
    CGameResourceDownloader::SerializeLocalVersionJson(bool)(param_1,0);
    *(undefined1 *)((long)param_1 + 0x15d) = 0;
    uVar30 = 0xf;
  }
  *(undefined4 *)(param_1 + 0x2a) = uVar30;
code_r0x018db484:
  return;
}

// ==== CGameResourceDownloader::Progress_Download()
// vaddr 0x17db7c4 | ghidra 0x18db7c4 | size 1492 | symbol _ZN23CGameResourceDownloader17Progress_DownloadEv | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN23CGameResourceDownloader17Progress_DownloadEv(long param_1)

{
  ulong uVar1;
  undefined8 *puVar2;
  int iVar3;
  undefined8 uVar4;
  undefined *puVar5;
  long *plVar6;
  ulong uVar7;
  long lVar8;
  ulong uVar9;
  undefined4 uVar10;
  undefined8 uVar11;
  long lVar12;
  long lVar13;
  uint uVar14;
  long alStack_88 [3];
  ulong uStack_70;
  ulong uStack_68;
  ulong uStack_60;
  ulong uStack_50;
  ulong uStack_48;
  ulong uStack_40;
  
  *(undefined8 *)(param_1 + 0x160) = 0;
  if (0 < *(long *)(param_1 + 0x90)) {
    lVar12 = 0;
    uVar14 = 0;
    *(undefined8 *)(param_1 + 0x98) = 0;
    do {
      while( true ) {
        lVar12 = *(long *)(*(long *)(param_1 + 0x80) + lVar12 * 8);
        CGameResourceDownloader::CDownloadNode::Run()(lVar12);
        iVar3 = *(int *)(lVar12 + 8);
        if (iVar3 - 1U < 4) break;
        if (iVar3 == 6) {
          uVar7 = *(ulong *)(lVar12 + 0x188);
          *(ulong *)(param_1 + 0x160) = uVar7;
          *(undefined8 *)(param_1 + 0x14c) = 5;
          uVar10 = 1000000;
          if (uVar7 == 0xfffffffffffffc33) {
            uVar10 = 0xf4241;
          }
          if ((*(char *)(param_1 + 0x157) != '\0') &&
             (plVar6 = *(long **)(param_1 + 0x4e0), plVar6 != (long *)0x0)) {
            uStack_70 = CONCAT44(uStack_70._4_4_,uVar10);
            uStack_50 = uVar7;
            (**(code **)(*plVar6 + 0x30))(plVar6,&uStack_70,&uStack_50);
          }
          puVar5 = PTR__ZN9Framework10TSingletonI10CUIManagerE11m_pInstanceE_02cc3ca0;
          if (*(char *)(param_1 + 0x15c) == '\0') {
            if (*(long *)(param_1 + 0x160) == -0x3cd) {
              lVar13 = *(long *)PTR__ZN9Framework10TSingletonI10CUIManagerE11m_pInstanceE_02cc3ca0;
              if (lVar13 == 0) {
                Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
                lVar13 = *(long *)puVar5;
              }
              lVar8 = *(long *)(lVar13 + 0x38);
              uVar10 = *(undefined4 *)(param_1 + 0x38);
              if (lVar8 == 0) {
                Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027ec285/*"C:\BAS_Submission\Client\Project\Android\BASAndroid.NativeActivity\..\..\..\Source\Game/UI/UIManager.h"*/,0x50,&UNK_027e6bb9/*"m_pSceneObjectContainer is null."*/);
                lVar8 = *(long *)(lVar13 + 0x38);
              }
              lVar13 = CSceneObjectContainer::pSearch(unsigned int)(lVar8,uVar10);
              uVar11 = BAS::GetDeviceFreeSize()();
              *(undefined8 *)(lVar13 + 0x158) = uVar11;
              *(undefined8 *)(lVar13 + 0x160) = *(undefined8 *)(lVar12 + 0x370);
              CSuccessivelyDownload::OpenSelectAllDownload()(lVar13);
              uVar10 = 9;
            }
            else {
              *(undefined8 *)(lVar12 + 8) = 1;
              uVar10 = 4;
            }
            *(undefined4 *)(param_1 + 0x14c) = uVar10;
            *(undefined4 *)(param_1 + 0x150) = 0;
            puVar5 = PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
            lVar12 = *(long *)
                      PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
            if (lVar12 == 0) {
              Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
              lVar12 = *(long *)puVar5;
            }
            lVar12 = CParameterManager::pParameterUI() const(lVar12);
            *(undefined1 *)(lVar12 + 0xc038) = 1;
          }
code_r0x018dba34:
          lVar13 = *(long *)(param_1 + 0x90);
          goto code_r0x018dba38;
        }
        lVar13 = *(long *)(param_1 + 0x98);
        lVar12 = lVar13;
        if ((-1 < lVar13) && (lVar13 < *(long *)(param_1 + 0x90))) {
          lVar8 = *(long *)(param_1 + 0x90) + -1;
          if (lVar13 < lVar8) {
            do {
              puVar2 = (undefined8 *)(*(long *)(param_1 + 0x80) + lVar12 * 8);
              lVar12 = lVar12 + 1;
              *puVar2 = puVar2[1];
              lVar8 = *(long *)(param_1 + 0x90) + -1;
            } while (lVar12 < lVar8);
          }
          Aska::TArray<CGameResourceDownloader::CDownloadNode*, false>::Resize(long, bool)(param_1 + 0x78,lVar8,0);
          lVar12 = *(long *)(param_1 + 0x98);
          if (lVar13 <= lVar12) {
            lVar13 = lVar12 + -1;
            if (lVar12 < 1) {
              lVar12 = 0;
            }
            else {
              lVar12 = lVar13;
              if (*(long *)(param_1 + 0x90) <= lVar13) {
                lVar12 = *(long *)(param_1 + 0x90);
              }
            }
            *(long *)(param_1 + 0x98) = lVar12;
          }
        }
        lVar13 = *(long *)(param_1 + 0x90);
        *(int *)(param_1 + 0x268) = *(int *)(param_1 + 0x268) + 1;
        if (lVar13 <= lVar12) goto code_r0x018dba38;
      }
      if (iVar3 == 4) {
        uVar14 = uVar14 + 1;
      }
      if ((iVar3 - 2U < 3 && iVar3 != 4) || (3 < uVar14)) goto code_r0x018dba34;
      lVar13 = *(long *)(param_1 + 0x90);
      lVar12 = *(long *)(param_1 + 0x98) + 1;
      *(long *)(param_1 + 0x98) = lVar12;
    } while (lVar12 < lVar13);
code_r0x018dba38:
    if (lVar13 < 1) {
      if (*(long *)(param_1 + 0x5d8) != 0) {
        *(undefined4 *)(param_1 + 0x268) = 0;
      }
      if (*(long *)(param_1 + 0x480) != 0) {
        if (*(long *)(param_1 + 0x5d8) != 0) {
          CGameResourceDownloader::SerializeLocalVersionJson(bool)(param_1,0);
        }
        BAS::GetDownloadPath()(&uStack_50);
        if ((uStack_50 & 1) == 0) {
          uVar9 = 0x16;
          uVar7 = uStack_50 & 0xff;
        }
        else {
          uVar9 = (uStack_50 & 0xfffffffffffffffe) - 1;
          uVar7 = uStack_50;
        }
        uVar1 = (ulong)(((uint)uVar7 & 0xfe) >> 1);
        if ((uVar7 & 1) != 0) {
          uVar1 = uStack_48;
        }
        if (uVar9 == uVar1) {
          string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&uStack_50,uVar9,1,uVar9,uVar9,0,1,&UNK_029c5d3e/*"/"*/);
        }
        else {
          uVar9 = (ulong)&uStack_50 | 1;
          if ((uVar7 & 1) != 0) {
            uVar9 = uStack_40;
          }
          *(undefined1 *)(uVar9 + uVar1) = 0x2f;
          uVar1 = uVar1 + 1;
          uVar7 = uVar1;
          if ((uStack_50 & 1) == 0) {
            uStack_50 = CONCAT71(uStack_50._1_7_,(char)uVar1 * '\x02');
            uVar7 = uStack_48;
          }
          uStack_48 = uVar7;
          *(undefined1 *)(uVar9 + uVar1) = 0;
        }
        uVar4 = _UNK_02866d67;
        uVar11 = _UNK_02866d5f;
        uStack_68 = uStack_48;
        uStack_70 = uStack_50;
        uStack_60 = uStack_40;
        if ((uStack_50 & 1) == 0) {
          lVar12 = 0x16;
          uVar7 = uStack_50 & 0xff;
        }
        else {
          lVar12 = (uStack_50 & 0xfffffffffffffffe) - 1;
          uVar7 = uStack_50;
        }
        uVar9 = (ulong)(((uint)uVar7 & 0xfe) >> 1);
        if ((uVar7 & 1) != 0) {
          uVar9 = uStack_48;
        }
        if (lVar12 - uVar9 < 0x14) {
          string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&uStack_70,lVar12,(0x14 - lVar12) + uVar9,uVar9,uVar9,0,0x14,&UNK_02866d5f/*"downloadfilelist.tmp"*/
                         );
        }
        else {
          uVar1 = (ulong)&uStack_70 | 1;
          if ((uVar7 & 1) != 0) {
            uVar1 = uStack_40;
          }
          puVar2 = (undefined8 *)(uVar1 + uVar9);
          *(undefined4 *)(puVar2 + 2) = 0x706d742e;
          puVar2[1] = uVar4;
          *puVar2 = uVar11;
          uVar9 = uVar9 + 0x14;
          uVar7 = uVar9;
          if ((uStack_50 & 1) == 0) {
            uStack_70 = CONCAT71((int7)(uStack_50 >> 8),(char)uVar9 * '\x02');
            uVar7 = uStack_68;
          }
          uStack_68 = uVar7;
          *(undefined1 *)(uVar1 + uVar9) = 0;
        }
        uStack_40 = uStack_60;
        uStack_48 = uStack_68;
        uStack_50 = uStack_70;
        lVar13 = *(long *)(param_1 + 0x480);
        lVar12 = lVar13 + 0xc0;
        uVar7 = Framework::CMutex::IsInitialized() const(lVar12);
        if ((uVar7 & 1) == 0) {
          Framework::CMutex::Initialize()(lVar12);
        }
        Framework::CMutex::Lock()(lVar12);
        Aska::FileStream::Close()(lVar13 + 0x178);
        Framework::CMutex::Unlock()(lVar12);
        Framework::CMutex::Release()(lVar13 + 0x10);
        Framework::CMutex::Release()(lVar12);
        if (*(long **)(param_1 + 0x480) != (long *)0x0) {
          (**(code **)(**(long **)(param_1 + 0x480) + 0x10))();
          *(undefined8 *)(param_1 + 0x480) = 0;
        }
        uVar7 = (ulong)&uStack_50 | 1;
        if ((uStack_50 & 1) != 0) {
          uVar7 = uStack_40;
        }
        Aska::File::DeleteFile(char const*)(uVar7);
        uVar11 = *(undefined8 *)(param_1 + 0x5d0);
        alStack_88[1] = 0;
        alStack_88[2] = 0;
        alStack_88[0] = 0;
        if (*(long *)(param_1 + 0x5b8) != 0) {
          lVar12 = (*(long *)(param_1 + 0x5b8) - 1U >> 6) + 1;
          lVar13 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(lVar12 * 8,&UNK_027dc536/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Vector.h"*/,0x20);
          if (lVar13 == 0) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
          }
          alStack_88[1] = 0;
          alStack_88[0] = lVar13;
          alStack_88[2] = lVar12;
          std::__ndk1::enable_if<__is_forward_iterator<std::__ndk1::__bit_iterator<std::__ndk1::vector<bool, Framework::CSTLAllocator<bool, Framework::CSTLVectorAllocatorInf> >, true, 0ul> >::value, void>::type std::__ndk1::vector<bool, Framework::CSTLAllocator<bool, Framework::CSTLVectorAllocatorInf> >::__construct_at_end<std::__ndk1::__bit_iterator<std::__ndk1::vector<bool, Framework::CSTLAllocator<bool, Framework::CSTLVectorAllocatorInf> >, true, 0ul> >(std::__ndk1::__bit_iterator<std::__ndk1::vector<bool, Framework::CSTLAllocator<bool, Framework::CSTLVectorAllocatorInf> >, true, 0ul>, std::__ndk1::__bit_iterator<std::__ndk1::vector<bool, Framework::CSTLAllocator<bool, Framework::CSTLVectorAllocatorInf> >, true, 0ul>)(alStack_88,*(long *)(param_1 + 0x5b0),0,
                          *(long *)(param_1 + 0x5b0) +
                          (*(ulong *)(param_1 + 0x5b8) >> 3 & 0x1ffffffffffffff8),
                          *(ulong *)(param_1 + 0x5b8) & 0x3f);
        }
        CParameterUI::tEpisodeData::UpdateEpisodeDataState(Framework::CSTLVector<bool>, bool)(uVar11,alStack_88,1);
        if (alStack_88[0] != 0) {
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)();
        }
        if ((uStack_50 & 1) != 0) {
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_40);
        }
      }
    }
    else {
      lVar12 = *(long *)(param_1 + 0x480);
      if (lVar12 != 0) {
        lVar13 = lVar12 + 0xc0;
        uVar7 = Framework::CMutex::IsInitialized() const(lVar13);
        if ((uVar7 & 1) == 0) {
          Framework::CMutex::Initialize()(lVar13);
        }
        Framework::CMutex::Lock()(lVar13);
        lVar8 = *(long *)PTR__ZN4Aska6Global20m_pMessageDispatcherE_02cb77c8;
        if (lVar8 == 0) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02866a48/*"C:\BAS_Submission\Client\Project\..\Source\Game\Resource\GameResourceDownloader.cpp"*/,0x1724,&UNK_02866c07/*"dispatcher is null."*/);
        }
        Aska::SimpleMessageDispatcher::PostMessage(unsigned short, Aska::INotify*, void*, void*, unsigned int*, signed char)(lVar8,0x4c9,lVar12,0,0,0,0);
        Framework::CMutex::Unlock()(lVar13);
      }
    }
  }
  return;
}

// ==== CGameResourceDownloader::Progress_RemoveDownloadData()
// vaddr 0x17dbd98 | ghidra 0x18dbd98 | size 528 | symbol _ZN23CGameResourceDownloader27Progress_RemoveDownloadDataEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN23CGameResourceDownloader27Progress_RemoveDownloadDataEv(long param_1)

{
  long lVar1;
  int iVar2;
  int *piVar3;
  long *plVar4;
  long lVar5;
  long *plVar6;
  undefined8 uStack_38;
  
  if (*(int *)(param_1 + 0x150) == 1) {
    CGameResourceDownloader::CDeleteTask::Progress()(*(undefined8 *)(param_1 + 0x5a0));
    piVar3 = *(int **)(param_1 + 0x5a0);
    *(uint *)(param_1 + 0x4f0) =
         piVar3[4] - piVar3[10] & (piVar3[4] - piVar3[10] >> 0x1f ^ 0xffffffffU);
    iVar2 = piVar3[4];
    if (iVar2 == 0) {
      iVar2 = 1;
    }
    *(int *)(param_1 + 0x4f4) = iVar2;
    if (*piVar3 == 4) {
      plVar4 = *(long **)(param_1 + 0x520);
      *(undefined1 *)(param_1 + 0x15f) = 1;
      if (plVar4 != (long *)0x0) {
        uStack_38 = *(undefined8 *)(piVar3 + 2);
        (**(code **)(*plVar4 + 0x30))(plVar4,&uStack_38);
        piVar3 = *(int **)(param_1 + 0x5a0);
      }
      *(undefined8 *)(param_1 + 0x5a0) = 0;
      if (piVar3 != (int *)0x0) {
        if (*(long *)(piVar3 + 10) != 0) {
          lVar5 = *(long *)(piVar3 + 6);
          plVar4 = *(long **)(piVar3 + 8);
          *(undefined8 *)(*plVar4 + 8) = *(undefined8 *)(lVar5 + 8);
          **(long **)(lVar5 + 8) = *plVar4;
          piVar3[10] = 0;
          piVar3[0xb] = 0;
          while (plVar4 != (long *)(piVar3 + 6)) {
            plVar6 = (long *)plVar4[1];
            if ((*(byte *)(plVar4 + 2) & 1) != 0) {
              Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar4[4]);
            }
            Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar4);
            plVar4 = plVar6;
          }
        }
        operator delete(void*)(piVar3);
      }
      *(undefined1 *)(param_1 + 0x156) = 0;
      *(undefined1 *)(param_1 + 0x154) = 1;
      if ((*(byte *)(param_1 + 0x238) & 1) == 0) {
        *(undefined2 *)(param_1 + 0x238) = 0;
      }
      else {
        **(undefined1 **)(param_1 + 0x248) = 0;
        *(undefined8 *)(param_1 + 0x240) = 0;
      }
      *(undefined8 *)(param_1 + 0x14c) = 5;
      *(int *)(param_1 + 0x4f0) = *(int *)(param_1 + 0x4f0) + 1;
    }
  }
  else if (*(int *)(param_1 + 0x150) == 0) {
    *(undefined4 *)(param_1 + 0x4f0) = 0;
    piVar3 = (int *)operator new(unsigned long, std::nothrow_t const&)(0x30,PTR__ZSt7nothrow_02cb9a80);
    if (piVar3 != (int *)0x0) {
      piVar3[0] = 0;
      piVar3[1] = 0;
      piVar3[2] = 0;
      piVar3[3] = 0;
      piVar3[4] = 1;
      *(int **)(piVar3 + 6) = piVar3 + 6;
      *(int **)(piVar3 + 8) = piVar3 + 6;
      piVar3[10] = 0;
      piVar3[0xb] = 0;
    }
    lVar5 = *(long *)(param_1 + 0x5a0);
    *(int **)(param_1 + 0x5a0) = piVar3;
    if (lVar5 != 0) {
      if (*(long *)(lVar5 + 0x28) != 0) {
        lVar1 = *(long *)(lVar5 + 0x18);
        plVar4 = *(long **)(lVar5 + 0x20);
        *(undefined8 *)(*plVar4 + 8) = *(undefined8 *)(lVar1 + 8);
        **(long **)(lVar1 + 8) = *plVar4;
        *(undefined8 *)(lVar5 + 0x28) = 0;
        while (plVar4 != (long *)(lVar5 + 0x18)) {
          plVar6 = (long *)plVar4[1];
          if ((*(byte *)(plVar4 + 2) & 1) != 0) {
            Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar4[4]);
          }
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar4);
          plVar4 = plVar6;
        }
      }
      operator delete(void*)(lVar5);
      piVar3 = *(int **)(param_1 + 0x5a0);
    }
    if (*piVar3 == 0) {
      piVar3[0] = 1;
      piVar3[1] = 0;
    }
    *(int *)(param_1 + 0x150) = *(int *)(param_1 + 0x150) + 1;
  }
  return;
}

// ==== CGameResourceDownloader::CVerifyTask::Initialize(int, CGameResourceDownloader*, CVersionInfo*, CVersionInfo*, Aska::ASON::AValue::AMap const*, Aska::ASON::AValue::AMap const*)
// vaddr 0x17dbfa8 | ghidra 0x18dbfa8 | size 132 | symbol _ZN23CGameResourceDownloader11CVerifyTask10InitializeEiPS_P12CVersionInfoS3_PKN4Aska4ASON6AValue4AMapES9_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN23CGameResourceDownloader11CVerifyTask10InitializeEiPS_P12CVersionInfoS3_PKN4Aska4ASON6AValue4AMapES9_
               (long param_1,undefined4 param_2,undefined8 param_3,undefined8 param_4,
               undefined8 param_5,long param_6,long param_7)

{
  long lVar1;
  uint uVar2;
  uint uVar3;
  
  lVar1 = *(long *)(param_1 + 0x40);
  *(undefined8 *)(param_1 + 0x10) = param_3;
  *(undefined8 *)(param_1 + 0x18) = param_4;
  *(undefined8 *)(param_1 + 0x20) = param_5;
  *(long *)(param_1 + 0x28) = param_6;
  *(long *)(param_1 + 0x30) = param_7;
  *(undefined1 *)(param_1 + 0x72) = 0;
  *(undefined4 *)(param_1 + 0x74) = 0;
  *(undefined8 *)(param_1 + 0x50) = 0;
  *(undefined2 *)(param_1 + 0x70) = 0;
  if (lVar1 != *(long *)(param_1 + 0x38)) {
    *(ulong *)(param_1 + 0x40) =
         lVar1 + (~((lVar1 + -8) - *(long *)(param_1 + 0x38)) & 0xfffffffffffffff8U);
  }
  if (param_6 != 0) {
    uVar2 = *(uint *)(param_6 + 8);
    uVar3 = uVar2;
    if ((param_7 != 0) && (uVar3 = *(uint *)(param_7 + 8), *(uint *)(param_7 + 8) <= uVar2)) {
      uVar3 = uVar2;
    }
    std::__ndk1::__hash_table<std::__ndk1::__hash_value_type<unsigned int, bool>, std::__ndk1::__unordered_map_hasher<unsigned int, std::__ndk1::__hash_value_type<unsigned int, bool>, std::__ndk1::hash<unsigned int>, true>, std::__ndk1::__unordered_map_equal<unsigned int, std::__ndk1::__hash_value_type<unsigned int, bool>, std::__ndk1::equal_to<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__hash_value_type<unsigned int, bool>, Framework::CSTLUnorderedMapAllocatorInf> >::rehash(unsigned long)(param_1 + 0xa0,uVar3);
  }
  *(undefined4 *)(param_1 + 8) = param_2;
  *(undefined4 *)(param_1 + 0xc) = 0;
  return;
}

// ==== CGameResourceDownloader::CVerifyTask::Progress()
// vaddr 0x17dc02c | ghidra 0x18dc02c | size 56 | symbol _ZN23CGameResourceDownloader11CVerifyTask8ProgressEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN23CGameResourceDownloader11CVerifyTask8ProgressEv(long param_1)

{
  switch(*(undefined4 *)(param_1 + 8)) {
  case 0:
    (*(code *)PTR__ZN23CGameResourceDownloader11CVerifyTask22ProgressLocalFileCheckEv_02ca8a78)();
    return;
  case 1:
    (*(code *)PTR__ZN23CGameResourceDownloader11CVerifyTask27ProgressServerManifestCheckEv_02c92f48)
              ();
    return;
  case 2:
    (*(code *)PTR__ZN23CGameResourceDownloader11CVerifyTask18ProgressEraseCheckEv_02c919b8)();
    return;
  case 3:
    (*(code *)
      PTR__ZN23CGameResourceDownloader11CVerifyTask29ProgressEraseEpisodeDataCheckEv_02c91c98)();
    return;
  case 4:
    (*(code *)PTR__ZN23CGameResourceDownloader11CVerifyTask21ProgressSetupManifestEv_02cb2c70)();
    return;
  default:
    return;
  }
}

// ==== CGameResourceDownloader::CVerifyTask::GetCheckRate() const
// vaddr 0x17dc064 | ghidra 0x18dc064 | size 128 | symbol _ZNK23CGameResourceDownloader11CVerifyTask12GetCheckRateEv | lib libSOA-3.7.0.so | 2026-10-04
float _ZNK23CGameResourceDownloader11CVerifyTask12GetCheckRateEv(long param_1)

{
  int iVar1;
  uint uVar2;
  long lVar3;
  ulong uVar4;
  long *plVar5;
  float fVar6;
  float fVar7;
  
  iVar1 = *(int *)(param_1 + 8);
  if (iVar1 == 1) {
    fVar7 = 6.0;
    fVar6 = (float)NEON_ucvtf(*(undefined4 *)(param_1 + 0xc));
  }
  else {
    if (iVar1 == 2) {
      plVar5 = *(long **)(param_1 + 0x98);
      if (plVar5 == (long *)0x0) {
        return 0.0;
      }
      uVar4 = (ulong)(plVar5[1] - *plVar5) >> 8;
      uVar2 = (uint)((ulong)(plVar5[1] - *plVar5) >> 8);
    }
    else {
      if (iVar1 != 0) {
        return 0.0;
      }
      if (*(char *)(param_1 + 0x70) == '\0') {
        lVar3 = *(long *)(param_1 + 0x28);
      }
      else {
        lVar3 = *(long *)(param_1 + 0x30);
      }
      if (lVar3 == 0) {
        return 0.0;
      }
      uVar2 = *(uint *)(lVar3 + 8);
      uVar4 = (ulong)uVar2;
    }
    if (uVar2 == 0) {
      return 0.0;
    }
    fVar6 = (float)*(uint *)(param_1 + 0x74);
    fVar7 = (float)(uVar4 & 0xffffffff);
  }
  return fVar6 / fVar7;
}

// ==== CGameResourceDownloader::CVerifyTask::IsEnd() const
// vaddr 0x17dc0e4 | ghidra 0x18dc0e4 | size 8 | symbol _ZNK23CGameResourceDownloader11CVerifyTask5IsEndEv | lib libSOA-3.7.0.so | 2026-10-04
undefined1 _ZNK23CGameResourceDownloader11CVerifyTask5IsEndEv(long param_1)

{
  return *(undefined1 *)(param_1 + 0x71);
}

// ==== CGameResourceDownloader::LoadVersionFileToAsonEpisodeData(std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > const&)
// vaddr 0x17dc0ec | ghidra 0x18dc0ec | size 612 | symbol _ZN23CGameResourceDownloader32LoadVersionFileToAsonEpisodeDataERKNSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEE | lib libSOA-3.7.0.so | 2026-10-04
undefined4
_ZN23CGameResourceDownloader32LoadVersionFileToAsonEpisodeDataERKNSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEE
          (long param_1,byte *param_2)

{
  undefined *puVar1;
  undefined *puVar2;
  long lVar3;
  long *plVar4;
  undefined8 uVar5;
  ulong uVar6;
  byte *pbVar7;
  undefined4 uVar8;
  undefined8 *puVar9;
  undefined *puStack_110;
  undefined *puStack_108;
  undefined1 uStack_100;
  long lStack_f8;
  undefined8 uStack_f0;
  undefined1 uStack_e8;
  undefined1 auStack_e0 [144];
  undefined8 uStack_48;
  
  uVar6 = (ulong)(*param_2 >> 1);
  if ((*param_2 & 1) != 0) {
    uVar6 = *(ulong *)(param_2 + 8);
  }
  if (uVar6 == 0) {
    uVar8 = 0;
  }
  else {
    Aska::ASON::ASON()(auStack_e0);
    lVar3 = Aska::ASON::Init(unsigned int, bool)(auStack_e0,"meterEPv",1);
    if (lVar3 == 0) {
      pbVar7 = *(byte **)(param_2 + 0x10);
      if ((*param_2 & 1) == 0) {
        pbVar7 = param_2 + 1;
      }
      lVar3 = Aska::FileReadManager::CalcFileLength(char const*, bool)(pbVar7,0);
      if (lVar3 != 0) {
        uVar5 = operator new[](unsigned long, std::nothrow_t const&)(lVar3,PTR__ZSt7nothrow_02cb9a80);
        puVar2 = PTR__ZTVN4Aska10FileStreamE_02cbc9f8;
        puVar1 = PTR__ZTVN4Aska4FileE_02cb6e28;
        uStack_100 = 0;
        puStack_110 = PTR__ZTVN4Aska10FileStreamE_02cbc9f8 + 0x10;
        puStack_108 = PTR__ZTVN4Aska4FileE_02cb6e28 + 0x10;
        uStack_e8 = 0;
        lStack_f8 = 0;
        uStack_f0 = 0;
        pbVar7 = param_2 + 1;
        if ((*param_2 & 1) != 0) {
          pbVar7 = *(byte **)(param_2 + 0x10);
        }
        uStack_48 = uVar5;
        uVar6 = Aska::FileStream::Open(char const*, bool, bool, Aska::Machine::Endian)(&puStack_110,pbVar7,0,0,3);
        if ((uVar6 & 1) != 0) {
          Aska::FileStream::Read(void*, unsigned long, unsigned long)(&puStack_110,uVar5,lVar3,1);
          Aska::FileStream::Close()(&puStack_110);
          Aska::ASON::DeserializeBinary(void const*, unsigned long)(auStack_e0,uStack_48,lVar3);
        }
        lVar3 = *(long *)(param_1 + 0x438);
        if (lVar3 == *(long *)(param_1 + 0x440)) {
          void std::__ndk1::vector<Aska::ASON, Framework::CSTLAllocator<Aska::ASON, Framework::CSTLVectorAllocatorInf> >::__push_back_slow_path<Aska::ASON const&>(Aska::ASON const&)(param_1 + 0x430,auStack_e0);
        }
        else {
          if (lVar3 == 0) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
          }
          Aska::ASON::ASON(Aska::ASON const&)(lVar3,auStack_e0);
          *(long *)(param_1 + 0x438) = *(long *)(param_1 + 0x438) + 0x90;
        }
        puVar9 = *(undefined8 **)(param_1 + 0x4a8);
        if (puVar9 == *(undefined8 **)(param_1 + 0x4b0)) {
          void std::__ndk1::vector<unsigned char*, Framework::CSTLAllocator<unsigned char*, Framework::CSTLVectorAllocatorInf> >::__push_back_slow_path<unsigned char* const&>(unsigned char* const&)(param_1 + 0x4a0,&uStack_48);
        }
        else {
          if (puVar9 == (undefined8 *)0x0) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
          }
          *puVar9 = uStack_48;
          *(long *)(param_1 + 0x4a8) = *(long *)(param_1 + 0x4a8) + 8;
        }
        puStack_110 = puVar2 + 0x10;
        Aska::FileStream::Close()(&puStack_110);
        puStack_108 = puVar1 + 0x10;
        if (lStack_f8 != 0) {
          Aska::File::Close()((ulong)&puStack_110 | 8);
        }
      }
      uVar8 = 1;
    }
    else {
      *(undefined8 *)(param_1 + 0x14c) = 5;
      if ((*(char *)(param_1 + 0x157) != '\0') &&
         (plVar4 = *(long **)(param_1 + 0x4e0), plVar4 != (long *)0x0)) {
        puStack_110 = (undefined *)0xfffffffffffffc15;
        uStack_48 = CONCAT44(uStack_48._4_4_,1000000);
        (**(code **)(*plVar4 + 0x30))(plVar4,&uStack_48,&puStack_110);
      }
      uVar8 = 0;
    }
    Aska::ASON::~ASON()(auStack_e0);
  }
  return uVar8;
}

// ==== CGameResourceDownloader::CVerifyTask::AddManifestMapData(Aska::ASON::AValue::AMap const*)
// vaddr 0x17dc350 | ghidra 0x18dc350 | size 128 | symbol _ZN23CGameResourceDownloader11CVerifyTask18AddManifestMapDataEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN23CGameResourceDownloader11CVerifyTask18AddManifestMapDataEPKN4Aska4ASON6AValue4AMapE
               (long param_1,undefined8 param_2)

{
  undefined8 *puVar1;
  undefined8 uStack_28;
  
  if ((*(uint *)(param_1 + 8) | 2) == 3) {
    puVar1 = *(undefined8 **)(param_1 + 0x40);
    uStack_28 = param_2;
    if (puVar1 == *(undefined8 **)(param_1 + 0x48)) {
      void std::__ndk1::vector<Aska::ASON::AValue::AMap const*, Framework::CSTLAllocator<Aska::ASON::AValue::AMap const*, Framework::CSTLVectorAllocatorInf> >::__push_back_slow_path<Aska::ASON::AValue::AMap const* const&>(Aska::ASON::AValue::AMap const* const&)(param_1 + 0x38,&uStack_28);
    }
    else {
      if (puVar1 == (undefined8 *)0x0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
      }
      *puVar1 = param_2;
      *(long *)(param_1 + 0x40) = *(long *)(param_1 + 0x40) + 8;
    }
  }
  return;
}

// ==== CGameResourceDownloader::SerializeLocalVersionJson(bool)
// vaddr 0x17dc3d0 | ghidra 0x18dc3d0 | size 836 | symbol _ZN23CGameResourceDownloader25SerializeLocalVersionJsonEb | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN23CGameResourceDownloader25SerializeLocalVersionJsonEb(long param_1,ulong param_2)

{
  ulong uVar1;
  undefined8 *puVar2;
  undefined *puVar3;
  undefined8 uVar4;
  ulong uVar5;
  ulong uVar6;
  long lVar7;
  ulong uVar8;
  long lVar9;
  undefined *puVar10;
  ulong uVar11;
  undefined *puStack_120;
  undefined *puStack_118;
  undefined1 uStack_110;
  undefined7 uStack_10f;
  long lStack_108;
  undefined8 uStack_100;
  undefined1 uStack_f8;
  undefined *puStack_f0;
  ulong uStack_e8;
  ulong uStack_e0;
  undefined1 auStack_d0 [144];
  
  if ((param_2 & 1) != 0) {
    Framework::CMutex::Lock()(param_1 + 0x170);
  }
  Aska::ASON::ASON()(auStack_d0);
  void AsonSerializer::Serialize<CVersionInfo>(CVersionInfo&, unsigned int, unsigned long, bool)(auStack_d0,*(undefined8 *)(param_1 + 0x5d8),0,"meterEPv",0);
  uVar6 = Aska::ASON::CalcSerializedSize() const(auStack_d0);
  lVar7 = operator new[](unsigned long, std::nothrow_t const&)(uVar6,PTR__ZSt7nothrow_02cb9a80);
  uVar8 = Aska::ASON::CalcSerializedSize() const(auStack_d0);
  if ((uVar6 < uVar8) || (lVar9 = Aska::ASON::Serialize(void*, unsigned long) const(auStack_d0,lVar7,uVar8), lVar9 == -0x3eb)) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02866a48/*"C:\BAS_Submission\Client\Project\..\Source\Game\Resource\GameResourceDownloader.cpp"*/,0xd41,&UNK_02866b7d/*"AsonSerializer::CreateMessagePack in CGameResourceDownloader::SerializeLocalVersionJson NoBuffer."*/);
  }
  BAS::GetDownloadPath()(&puStack_120);
  if (((ulong)puStack_120 & 1) == 0) {
    uVar8 = 0x16;
    puVar10 = (undefined *)((ulong)puStack_120 & 0xff);
  }
  else {
    uVar8 = ((ulong)puStack_120 & 0xfffffffffffffffe) - 1;
    puVar10 = puStack_120;
  }
  puVar3 = (undefined *)(ulong)(((uint)puVar10 & 0xfe) >> 1);
  if (((ulong)puVar10 & 1) != 0) {
    puVar3 = puStack_118;
  }
  if ((undefined *)uVar8 == puVar3) {
    string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&puStack_120,uVar8,1,uVar8,uVar8,0,1,&UNK_029c5d3e/*"/"*/);
  }
  else {
    uVar8 = (ulong)&puStack_120 | 1;
    if (((ulong)puVar10 & 1) != 0) {
      uVar8 = CONCAT71(uStack_10f,uStack_110);
    }
    *(undefined1 *)(uVar8 + (long)puVar3) = 0x2f;
    uVar11 = (long)puVar3 + 1;
    puVar10 = (undefined *)uVar11;
    if (((ulong)puStack_120 & 1) == 0) {
      puStack_120 = (undefined *)CONCAT71(puStack_120._1_7_,(char)uVar11 * '\x02');
      puVar10 = puStack_118;
    }
    puStack_118 = puVar10;
    *(undefined1 *)(uVar8 + uVar11) = 0;
  }
  uVar4 = _UNK_02866dd0;
  uStack_e0 = CONCAT71(uStack_10f,uStack_110);
  uStack_e8 = (ulong)puStack_118;
  puStack_f0 = puStack_120;
  if (((ulong)puStack_120 & 1) == 0) {
    lVar9 = 0x16;
    puVar10 = (undefined *)((ulong)puStack_120 & 0xff);
  }
  else {
    lVar9 = ((ulong)puStack_120 & 0xfffffffffffffffe) - 1;
    puVar10 = puStack_120;
  }
  puVar3 = (undefined *)(ulong)(((uint)puVar10 & 0xfe) >> 1);
  if (((ulong)puVar10 & 1) != 0) {
    puVar3 = puStack_118;
  }
  if ((ulong)(lVar9 - (long)puVar3) < 0xb) {
    string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&puStack_f0,lVar9,(0xb - lVar9) + (long)puVar3,puVar3,puVar3,0,0xb,&UNK_02866dd0/*"version.bin"*/
                   );
    uVar11 = (ulong)&puStack_f0 | 1;
  }
  else {
    uVar11 = (ulong)&puStack_f0 | 1;
    uVar8 = uVar11;
    if (((ulong)puVar10 & 1) != 0) {
      uVar8 = uStack_e0;
    }
    puVar2 = (undefined8 *)(uVar8 + (long)puVar3);
    *(undefined1 *)((long)puVar2 + 10) = 0x6e;
    *(undefined2 *)(puVar2 + 1) = 0x6962;
    *puVar2 = uVar4;
    uVar1 = (long)puVar3 + 0xb;
    uVar5 = uVar1;
    if (((ulong)puStack_120 & 1) == 0) {
      puStack_f0 = (undefined *)CONCAT71((int7)((ulong)puStack_120 >> 8),(char)uVar1 * '\x02');
      uVar5 = uStack_e8;
    }
    uStack_e8 = uVar5;
    *(undefined1 *)(uVar8 + uVar1) = 0;
  }
  puVar3 = PTR__ZTVN4Aska10FileStreamE_02cbc9f8;
  puVar10 = PTR__ZTVN4Aska4FileE_02cb6e28;
  puStack_120 = PTR__ZTVN4Aska10FileStreamE_02cbc9f8 + 0x10;
  puStack_118 = PTR__ZTVN4Aska4FileE_02cb6e28 + 0x10;
  if (((ulong)puStack_f0 & 1) != 0) {
    uVar11 = uStack_e0;
  }
  uStack_110 = 0;
  uStack_f8 = 0;
  lStack_108 = 0;
  uStack_100 = 0;
  uVar8 = Aska::FileStream::Open(char const*, bool, bool, Aska::Machine::Endian)(&puStack_120,uVar11,0,1,3);
  if ((uVar8 & 1) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02866a48/*"C:\BAS_Submission\Client\Project\..\Source\Game\Resource\GameResourceDownloader.cpp"*/,0xd51,&UNK_028db317/*"0 is null."*/);
  }
  else {
    lVar9 = Aska::FileStream::Write(void const*, unsigned long, unsigned long)(&puStack_120,lVar7,uVar6,1);
    if (lVar9 == 0) {
      *(int *)PTR__ZN23CGameResourceDownloader15m_ErrorOverSizeE_02cbb7b8 =
           *(int *)PTR__ZN23CGameResourceDownloader15m_ErrorOverSizeE_02cbb7b8 + (int)uVar6;
    }
    Aska::FileStream::Close()(&puStack_120);
  }
  if (lVar7 != 0) {
    operator delete[](void*)(lVar7);
  }
  if ((param_2 & 1) != 0) {
    Framework::CMutex::Unlock()(param_1 + 0x170);
  }
  puStack_120 = puVar3 + 0x10;
  Aska::FileStream::Close()(&puStack_120);
  puStack_118 = puVar10 + 0x10;
  if (lStack_108 != 0) {
    Aska::File::Close()((ulong)&puStack_120 | 8);
  }
  if (((ulong)puStack_f0 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_e0);
  }
  Aska::ASON::~ASON()(auStack_d0);
  return;
}

// ==== CGameResourceDownloader::CDownloadNode::UnpackNotify::ResetDispatchCount()
// vaddr 0x17dc714 | ghidra 0x18dc714 | size 16 | symbol _ZN23CGameResourceDownloader13CDownloadNode12UnpackNotify18ResetDispatchCountEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN23CGameResourceDownloader13CDownloadNode12UnpackNotify18ResetDispatchCountEv(void)

{
  *(undefined4 *)
   PTR__ZN23CGameResourceDownloader13CDownloadNode12UnpackNotify15m_DispatchCountE_02cbe960 = 0;
  return;
}

// ==== CGameResourceDownloader::episodeResourceFileListUpdateCheck(std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > const&, std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > const&)
// vaddr 0x17dc808 | ghidra 0x18dc808 | size 1312 | symbol _ZN23CGameResourceDownloader34episodeResourceFileListUpdateCheckERKNSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEESA_ | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Type propagation algorithm not settling */

bool _ZN23CGameResourceDownloader34episodeResourceFileListUpdateCheckERKNSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEESA_
               (undefined8 param_1,byte *param_2,byte *param_3)

{
  ulong uVar1;
  byte *pbVar2;
  uint uVar3;
  ulong uVar4;
  long lVar5;
  ulong uVar6;
  ulong uVar7;
  ulong uVar8;
  ulong uStack_d0;
  ulong uStack_c8;
  ulong uStack_c0;
  byte abStack_b8 [16];
  ulong uStack_a8;
  ulong uStack_a0;
  ulong uStack_98;
  ulong uStack_90;
  ulong uStack_80;
  ulong uStack_78;
  ulong uStack_70;
  ulong uStack_60;
  ulong uStack_58;
  ulong uStack_50;
  
  BAS::GetDownloadPath()(&uStack_60);
  if ((uStack_60 & 1) == 0) {
    uVar4 = 0x16;
    uVar6 = uStack_60 & 0xff;
  }
  else {
    uVar4 = (uStack_60 & 0xfffffffffffffffe) - 1;
    uVar6 = uStack_60;
  }
  uVar8 = (ulong)(((uint)uVar6 & 0xfe) >> 1);
  if ((uVar6 & 1) != 0) {
    uVar8 = uStack_58;
  }
  if (uVar4 == uVar8) {
    string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&uStack_60,uVar4,1,uVar4,uVar4,0,1,&UNK_029c5d3e/*"/"*/);
  }
  else {
    uVar4 = (ulong)&uStack_60 | 1;
    if ((uVar6 & 1) != 0) {
      uVar4 = uStack_50;
    }
    *(undefined1 *)(uVar4 + uVar8) = 0x2f;
    uVar8 = uVar8 + 1;
    uVar6 = uVar8;
    if ((uStack_60 & 1) == 0) {
      uStack_60 = CONCAT71(uStack_60._1_7_,(char)uVar8 * '\x02');
      uVar6 = uStack_58;
    }
    uStack_58 = uVar6;
    *(undefined1 *)(uVar4 + uVar8) = 0;
  }
  uStack_90 = uStack_50;
  uStack_98 = uStack_58;
  uStack_a0 = uStack_60;
  uVar6 = *(ulong *)(param_2 + 8);
  pbVar2 = *(byte **)(param_2 + 0x10);
  if ((*param_2 & 1) == 0) {
    pbVar2 = param_2 + 1;
    uVar6 = (ulong)(*param_2 >> 1);
  }
  if ((uStack_60 & 1) == 0) {
    lVar5 = 0x16;
    uVar4 = uStack_60 & 0xff;
  }
  else {
    lVar5 = (uStack_60 & 0xfffffffffffffffe) - 1;
    uVar4 = uStack_60;
  }
  uVar8 = (ulong)(((uint)uVar4 & 0xfe) >> 1);
  if ((uVar4 & 1) != 0) {
    uVar8 = uStack_58;
  }
  if (lVar5 - uVar8 < uVar6) {
    string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&uStack_a0,lVar5,(uVar6 - lVar5) + uVar8,uVar8,uVar8,0,uVar6);
  }
  else if (uVar6 != 0) {
    uVar7 = (ulong)&uStack_a0 | 1;
    if ((uVar4 & 1) != 0) {
      uVar7 = uStack_50;
    }
    memcpy(uVar7 + uVar8,pbVar2,uVar6);
    uVar8 = uVar8 + uVar6;
    uVar6 = uVar8;
    if ((uStack_a0 & 1) == 0) {
      uStack_a0 = CONCAT71(uStack_a0._1_7_,(char)uVar8 * '\x02');
      uVar6 = uStack_98;
    }
    uStack_98 = uVar6;
    *(undefined1 *)(uVar7 + uVar8) = 0;
  }
  uStack_70 = uStack_90;
  uStack_78 = uStack_98;
  uStack_80 = uStack_a0;
  BAS::GetDownloadPath()(&uStack_60);
  if ((uStack_60 & 1) == 0) {
    uVar4 = 0x16;
    uVar6 = uStack_60 & 0xff;
  }
  else {
    uVar4 = (uStack_60 & 0xfffffffffffffffe) - 1;
    uVar6 = uStack_60;
  }
  uVar8 = (ulong)(((uint)uVar6 & 0xfe) >> 1);
  if ((uVar6 & 1) != 0) {
    uVar8 = uStack_58;
  }
  if (uVar4 == uVar8) {
    string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&uStack_60,uVar4,1,uVar4,uVar4,0,1,&UNK_029c5d3e/*"/"*/);
  }
  else {
    uVar4 = (ulong)&uStack_60 | 1;
    if ((uVar6 & 1) != 0) {
      uVar4 = uStack_50;
    }
    *(undefined1 *)(uVar4 + uVar8) = 0x2f;
    uVar8 = uVar8 + 1;
    uVar6 = uVar8;
    if ((uStack_60 & 1) == 0) {
      uStack_60 = CONCAT71(uStack_60._1_7_,(char)uVar8 * '\x02');
      uVar6 = uStack_58;
    }
    uStack_58 = uVar6;
    *(undefined1 *)(uVar4 + uVar8) = 0;
  }
  uStack_90 = uStack_50;
  uStack_98 = uStack_58;
  uStack_a0 = uStack_60;
  uVar6 = *(ulong *)(param_3 + 8);
  pbVar2 = *(byte **)(param_3 + 0x10);
  if ((*param_3 & 1) == 0) {
    pbVar2 = param_3 + 1;
    uVar6 = (ulong)(*param_3 >> 1);
  }
  if ((uStack_60 & 1) == 0) {
    lVar5 = 0x16;
    uVar4 = uStack_60 & 0xff;
  }
  else {
    lVar5 = (uStack_60 & 0xfffffffffffffffe) - 1;
    uVar4 = uStack_60;
  }
  uVar8 = (ulong)(((uint)uVar4 & 0xfe) >> 1);
  if ((uVar4 & 1) != 0) {
    uVar8 = uStack_58;
  }
  if (lVar5 - uVar8 < uVar6) {
    string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&uStack_a0,lVar5,(uVar6 - lVar5) + uVar8,uVar8,uVar8,0,uVar6);
  }
  else if (uVar6 != 0) {
    uVar7 = (ulong)&uStack_a0 | 1;
    if ((uVar4 & 1) != 0) {
      uVar7 = uStack_50;
    }
    memcpy(uVar7 + uVar8,pbVar2,uVar6);
    uVar8 = uVar8 + uVar6;
    uVar6 = uVar8;
    if ((uStack_a0 & 1) == 0) {
      uStack_a0 = CONCAT71(uStack_a0._1_7_,(char)uVar8 * '\x02');
      uVar6 = uStack_98;
    }
    uStack_98 = uVar6;
    *(undefined1 *)(uVar7 + uVar8) = 0;
  }
  uVar6 = (ulong)&uStack_80 | 1;
  if ((uStack_80 & 1) != 0) {
    uVar6 = uStack_70;
  }
  uStack_58 = uStack_98;
  uStack_60 = uStack_a0;
  uStack_50 = uStack_90;
  CGameResourceDownloader::EnableDefaultErrorHandle(bool)+0xc(&uStack_a0,uVar6,&UNK_02a354cc/*"version"*/);
  uVar6 = (ulong)&uStack_60 | 1;
  if ((uStack_60 & 1) != 0) {
    uVar6 = uStack_50;
  }
  uStack_c8 = 0;
  uStack_c0 = 0;
  uStack_d0 = 0;
  uVar4 = strlen(uVar6);
  if (uVar4 < 0x17) {
    uVar7 = (ulong)&uStack_d0 | 1;
    uStack_d0 = CONCAT71(uStack_d0._1_7_,(char)(uVar4 << 1));
    if (uVar4 != 0) goto code_r0x018dcc08;
  }
  else {
    uVar8 = uVar4 + 0x10 & 0xfffffffffffffff0;
    if (uVar8 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
    }
    uVar7 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar8,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
    if (uVar7 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    }
    uStack_d0 = uVar8 | 1;
    uStack_c8 = uVar4;
    uStack_c0 = uVar7;
code_r0x018dcc08:
    memcpy(uVar7,uVar6,uVar4);
  }
  *(undefined1 *)(uVar7 + uVar4) = 0;
  CGameResourceDownloader::checkLocalEpisodeFilelistVersion(string const&)(abStack_b8,param_1,&uStack_d0);
  if ((uStack_d0 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_c0);
  }
  uVar6 = (ulong)abStack_b8 | 1;
  if ((abStack_b8[0] & 1) != 0) {
    uVar6 = uStack_a8;
  }
  uVar7 = strlen(uVar6);
  uVar8 = uStack_a0;
  uVar4 = uStack_a0 >> 1 & 0x7f;
  if ((uStack_a0 & 1) != 0) {
    uVar4 = uStack_98;
  }
  uVar1 = uVar7;
  if (uVar4 <= uVar7) {
    uVar1 = uVar4;
  }
  if (uVar1 != 0) {
    uVar1 = (ulong)&uStack_a0 | 1;
    if ((uStack_a0 & 1) != 0) {
      uVar1 = uStack_90;
    }
    uVar3 = memcmp(uVar1,uVar6);
    if (uVar3 != 0) goto joined_r0x018dccf0;
  }
  uVar3 = (uint)(uVar7 < uVar4);
  if (uVar4 < uVar7) {
    uVar3 = 0xffffffff;
  }
joined_r0x018dccf0:
  if ((abStack_b8[0] & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_a8);
    uVar8 = uStack_a0;
  }
  if ((uVar8 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_90);
  }
  if ((uStack_60 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_50);
  }
  if ((uStack_80 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_70);
  }
  return uVar3 == 0;
}

// ==== CGameResourceDownloader::CVerifyTask::IsLatestAsset(char const*) const
// vaddr 0x17dd02c | ghidra 0x18dd02c | size 212 | symbol _ZNK23CGameResourceDownloader11CVerifyTask13IsLatestAssetEPKc | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK23CGameResourceDownloader11CVerifyTask13IsLatestAssetEPKc(long param_1)

{
  ulong uVar1;
  uint uVar2;
  ulong uVar3;
  ulong uVar4;
  ulong uVar5;
  long *plVar6;
  undefined1 auStack_20 [16];
  
  Framework::CHash32::CHash32(char const*)(auStack_20);
  uVar2 = Framework::CHash32::operator unsigned int() const(auStack_20);
  uVar4 = *(ulong *)(param_1 + 0xa8);
  if (uVar4 != 0) {
    uVar5 = uVar4 - 1;
    uVar3 = (ulong)uVar2;
    if ((uVar5 & uVar4) == 0) {
      uVar3 = uVar5 & uVar3;
    }
    else {
      uVar1 = 0;
      if (uVar4 != 0) {
        uVar1 = uVar3 / uVar4;
      }
      uVar3 = uVar3 - uVar1 * uVar4;
    }
    plVar6 = *(long **)(*(long *)(param_1 + 0xa0) + uVar3 * 8);
    if (plVar6 != (long *)0x0) {
      if ((uVar5 & uVar4) == 0) {
        do {
          plVar6 = (long *)*plVar6;
          if ((plVar6 == (long *)0x0) || ((plVar6[1] & uVar5) != uVar3)) goto code_r0x018dd0e8;
        } while (*(uint *)(plVar6 + 2) != uVar2);
      }
      else {
        do {
          plVar6 = (long *)*plVar6;
          if (plVar6 == (long *)0x0) goto code_r0x018dd0e8;
          uVar5 = 0;
          if (uVar4 != 0) {
            uVar5 = (ulong)plVar6[1] / uVar4;
          }
          if (plVar6[1] - uVar5 * uVar4 != uVar3) goto code_r0x018dd0e8;
        } while (*(uint *)(plVar6 + 2) != uVar2);
      }
      Framework::CHash32::~CHash32()(auStack_20);
      return *(char *)((long)plVar6 + 0x14) != '\0';
    }
  }
code_r0x018dd0e8:
  Framework::CHash32::~CHash32()(auStack_20);
  return false;
}

// ==== Aska::TArray<CGameResourceDownloader::tDownloadNodeInitializer, false>::Clear()
// vaddr 0x17dd284 | ghidra 0x18dd284 | size 188 | symbol _ZN4Aska6TArrayIN23CGameResourceDownloader24tDownloadNodeInitializerELb0EE5ClearEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6TArrayIN23CGameResourceDownloader24tDownloadNodeInitializerELb0EE5ClearEv
               (long param_1)

{
  long *plVar1;
  code *pcVar2;
  long lVar3;
  long lVar4;
  long lVar5;
  
  lVar5 = *(long *)(param_1 + 8);
  if ((lVar5 != 0) && (0 < *(long *)(param_1 + 0x18))) {
    lVar3 = 0;
    lVar4 = 1;
    do {
      plVar1 = *(long **)(lVar5 + lVar3 + 0x40);
      if ((long *)(lVar5 + lVar3 + 0x20) == plVar1) {
        pcVar2 = *(code **)(*plVar1 + 0x20);
code_r0x018dd2ec:
        (*pcVar2)();
      }
      else if (plVar1 != (long *)0x0) {
        pcVar2 = *(code **)(*plVar1 + 0x28);
        goto code_r0x018dd2ec;
      }
      if ((*(byte *)(lVar5 + lVar3) & 1) != 0) {
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(*(undefined8 *)(lVar5 + lVar3 + 0x10));
      }
      if (*(long *)(param_1 + 0x18) <= lVar4) break;
      lVar5 = *(long *)(param_1 + 8);
      lVar3 = lVar3 + 0x50;
      lVar4 = lVar4 + 1;
    } while( true );
  }
  if ((*(byte *)(param_1 + 0x32) & 1) != 0) {
    if (*(long *)(param_1 + 8) != 0) {
      operator delete[](void*)();
      *(undefined8 *)(param_1 + 8) = 0;
    }
    *(undefined8 *)(param_1 + 0x10) = 0;
  }
  *(undefined8 *)(param_1 + 0x18) = 0;
  *(undefined8 *)(param_1 + 0x20) = 0;
  return;
}

// ==== CGameResourceDownloader::CDownloadNode::Run()
// vaddr 0x17dd340 | ghidra 0x18dd340 | size 236 | symbol _ZN23CGameResourceDownloader13CDownloadNode3RunEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN23CGameResourceDownloader13CDownloadNode3RunEv(long param_1)

{
  int iVar1;
  undefined *puVar2;
  ulong uVar3;
  long lVar4;
  long lVar5;
  int iVar6;
  ulong uVar7;
  ulong uVar8;
  
  puVar2 = PTR__ZN9Framework10TSingletonI20CGameResourceManagerE11m_pInstanceE_02cc2018;
  iVar6 = *(int *)(param_1 + 8);
  if (iVar6 == 4) {
    CGameResourceDownloader::CDownloadNode::UnpackChildData()(param_1);
  }
  else if (iVar6 == 3) {
    CGameResourceDownloader::CDownloadNode::DownloadCompleteCalc()(param_1);
    *(undefined8 *)(param_1 + 8) = 4;
  }
  else if (iVar6 == 1) {
    lVar4 = *(long *)PTR__ZN9Framework10TSingletonI20CGameResourceManagerE11m_pInstanceE_02cc2018;
    if (lVar4 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
      lVar4 = *(long *)puVar2;
    }
    lVar5 = *(long *)(*(long *)(lVar4 + 0x20) + 0x90);
    if (0 < lVar5) {
      iVar6 = 0;
      uVar3 = 1;
      uVar8 = 0;
      do {
        uVar7 = uVar3;
        iVar1 = *(int *)(*(long *)(*(long *)(*(long *)(lVar4 + 0x20) + 0x80) + uVar8 * 8) + 8);
        iVar6 = iVar6 + (uint)(iVar1 != 4 && iVar1 - 2U < 3);
        if (0 < iVar6) {
          return 1;
        }
        uVar3 = (ulong)((int)uVar7 + 1);
        uVar8 = uVar7;
      } while ((long)uVar7 < lVar5);
      if (iVar6 != 0) {
        return 1;
      }
    }
    CGameResourceDownloader::CDownloadNode::StartDownload()(param_1);
  }
  return 1;
}

// ==== CGameResourceDownloader::CDownloadNode::IsError() const
// vaddr 0x17dd42c | ghidra 0x18dd42c | size 16 | symbol _ZNK23CGameResourceDownloader13CDownloadNode7IsErrorEv | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK23CGameResourceDownloader13CDownloadNode7IsErrorEv(long param_1)

{
  return *(int *)(param_1 + 8) == 6;
}

// ==== CGameResourceDownloader::CJournalFileWriter::Close()
// vaddr 0x17dd43c | ghidra 0x18dd43c | size 84 | symbol _ZN23CGameResourceDownloader18CJournalFileWriter5CloseEv | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Possible PIC construction at 0x018dd47c: Changing call to branch */
/* WARNING: Removing unreachable block (ram,0x018dd480) */

void _ZN23CGameResourceDownloader18CJournalFileWriter5CloseEv(long param_1)

{
  long lVar1;
  ulong uVar2;
  
  lVar1 = param_1 + 0xc0;
  uVar2 = Framework::CMutex::IsInitialized() const(lVar1);
  if ((uVar2 & 1) == 0) {
    Framework::CMutex::Initialize()(lVar1);
  }
  Framework::CMutex::Lock()(lVar1);
  Aska::FileStream::Close()(param_1 + 0x178);
  Framework::CMutex::Unlock()(lVar1);
  (*(code *)PTR__ZN9Framework6CMutex7ReleaseEv_02c955a8)(param_1 + 0x10);
  return;
}

// ==== CGameResourceDownloader::CJournalFileWriter::Start()
// vaddr 0x17dd490 | ghidra 0x18dd490 | size 132 | symbol _ZN23CGameResourceDownloader18CJournalFileWriter5StartEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN23CGameResourceDownloader18CJournalFileWriter5StartEv(long param_1)

{
  long lVar1;
  ulong uVar2;
  long lVar3;
  
  lVar1 = param_1 + 0xc0;
  uVar2 = Framework::CMutex::IsInitialized() const(lVar1);
  if ((uVar2 & 1) == 0) {
    Framework::CMutex::Initialize()(lVar1);
  }
  Framework::CMutex::Lock()(lVar1);
  lVar3 = *(long *)PTR__ZN4Aska6Global20m_pMessageDispatcherE_02cb77c8;
  if (lVar3 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02866a48/*"C:\BAS_Submission\Client\Project\..\Source\Game\Resource\GameResourceDownloader.cpp"*/,0x1724,&UNK_02866c07/*"dispatcher is null."*/);
  }
  Aska::SimpleMessageDispatcher::PostMessage(unsigned short, Aska::INotify*, void*, void*, unsigned int*, signed char)(lVar3,0x4c9,param_1,0,0,0,0);
  (*(code *)PTR__ZN9Framework6CMutex6UnlockEv_02cb3f98)(lVar1);
  return;
}

// ==== CGameResourceDownloader::CDownloadNode::Calncel()
// vaddr 0x17dd514 | ghidra 0x18dd514 | size 28 | symbol _ZN23CGameResourceDownloader13CDownloadNode7CalncelEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN23CGameResourceDownloader13CDownloadNode7CalncelEv(long param_1)

{
  if (*(int *)(param_1 + 8) != 5) {
    *(undefined4 *)(param_1 + 0x180) = 0;
    *(undefined8 *)(param_1 + 0x188) = 0;
    *(undefined8 *)(param_1 + 8) = 0;
  }
  return;
}

// ==== CGameResourceDownloader::CDeleteTask::Start()
// vaddr 0x17dd530 | ghidra 0x18dd530 | size 32 | symbol _ZN23CGameResourceDownloader11CDeleteTask5StartEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN23CGameResourceDownloader11CDeleteTask5StartEv(int *param_1)

{
  if (*param_1 != 0) {
    return 0;
  }
  param_1[0] = 1;
  param_1[1] = 0;
  return 1;
}

// ==== CGameResourceDownloader::CDeleteTask::Progress()
// vaddr 0x17dd550 | ghidra 0x18dd550 | size 396 | symbol _ZN23CGameResourceDownloader11CDeleteTask8ProgressEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN23CGameResourceDownloader11CDeleteTask8ProgressEv(int *param_1)

{
  int iVar1;
  ulong uVar2;
  long lVar3;
  undefined8 uVar4;
  long *plVar5;
  uint uVar6;
  byte abStack_48 [16];
  ulong uStack_38;
  undefined8 uStack_28;
  
  iVar1 = *param_1;
  if (iVar1 == 1) {
    BAS::GetDownloadPath()(abStack_48);
    uVar2 = (ulong)abStack_48 | 1;
    if ((abStack_48[0] & 1) != 0) {
      uVar2 = uStack_38;
    }
    CGameResourceDownloader::CDeleteTask::FindFiles(char const*, Framework::CSTLList<string >&)(param_1,uVar2,param_1 + 6);
    if ((abStack_48[0] & 1) != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_38);
    }
    param_1[0] = 2;
    param_1[1] = 0;
    param_1[4] = (int)*(undefined8 *)(param_1 + 10);
    return;
  }
  if (iVar1 == 3) {
    BAS::GetDownloadPath()(abStack_48);
    uVar2 = (ulong)abStack_48 | 1;
    if ((abStack_48[0] & 1) != 0) {
      uVar2 = uStack_38;
    }
    CGameResourceDownloader::CDeleteTask::FindFiles(char const*, Framework::CSTLList<string >&)+0x270(&uStack_28,uVar2);
    *(undefined8 *)(param_1 + 2) = uStack_28;
    if ((abStack_48[0] & 1) != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_38);
    }
    uVar4 = 4;
  }
  else {
    if (iVar1 != 2) {
      return;
    }
    uVar6 = 0;
    do {
      if (*(long *)(param_1 + 10) == 0) goto code_r0x018dd628;
      Framework::CPerformanceCounter::Mark(unsigned int)(0x2e);
      lVar3 = *(long *)(param_1 + 6);
      if ((*(byte *)(lVar3 + 0x10) & 1) == 0) {
        uVar2 = Aska::File::DeleteFile(char const*)(lVar3 + 0x11);
      }
      else {
        uVar2 = Aska::File::DeleteFile(char const*)(*(undefined8 *)(lVar3 + 0x20));
      }
      if ((uVar2 & 1) == 0) {
        param_1[2] = -1;
        param_1[3] = -1;
      }
      plVar5 = *(long **)(param_1 + 6);
      *(long *)(*plVar5 + 8) = plVar5[1];
      *(long *)plVar5[1] = *plVar5;
      *(long *)(param_1 + 10) = *(long *)(param_1 + 10) + -1;
      if ((*(byte *)(plVar5 + 2) & 1) != 0) {
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar5[4]);
      }
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar5);
      Framework::CPerformanceCounter::Set(unsigned int)(0x2e);
      iVar1 = Framework::CPerformanceCounter::Get(unsigned int)(0x2e);
      uVar6 = iVar1 + uVar6;
    } while (uVar6 >> 4 < 0x271);
    if (*(long *)(param_1 + 10) != 0) {
      return;
    }
code_r0x018dd628:
    uVar4 = 3;
  }
  *(undefined8 *)param_1 = uVar4;
  return;
}

// ==== CGameResourceDownloader::CDeleteTask::ProgressFiles() const
// vaddr 0x17dd6dc | ghidra 0x18dd6dc | size 20 | symbol _ZNK23CGameResourceDownloader11CDeleteTask13ProgressFilesEv | lib libSOA-3.7.0.so | 2026-10-04
uint _ZNK23CGameResourceDownloader11CDeleteTask13ProgressFilesEv(long param_1)

{
  uint uVar1;
  
  uVar1 = *(int *)(param_1 + 0x10) - *(int *)(param_1 + 0x28);
  return uVar1 & ((int)uVar1 >> 0x1f ^ 0xffffffffU);
}

// ==== CGameResourceDownloader::CDeleteTask::NumFiles() const
// vaddr 0x17dd6f0 | ghidra 0x18dd6f0 | size 16 | symbol _ZNK23CGameResourceDownloader11CDeleteTask8NumFilesEv | lib libSOA-3.7.0.so | 2026-10-04
int _ZNK23CGameResourceDownloader11CDeleteTask8NumFilesEv(long param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x10);
  if (iVar1 == 0) {
    iVar1 = 1;
  }
  return iVar1;
}

// ==== CGameResourceDownloader::CDeleteTask::IsFinish() const
// vaddr 0x17dd700 | ghidra 0x18dd700 | size 16 | symbol _ZNK23CGameResourceDownloader11CDeleteTask8IsFinishEv | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK23CGameResourceDownloader11CDeleteTask8IsFinishEv(int *param_1)

{
  return *param_1 == 4;
}

// ==== CGameResourceDownloader::CDeleteTask::GetLastResult() const
// vaddr 0x17dd710 | ghidra 0x18dd710 | size 12 | symbol _ZNK23CGameResourceDownloader11CDeleteTask13GetLastResultEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK23CGameResourceDownloader11CDeleteTask13GetLastResultEv(undefined8 *param_1,long param_2)

{
  *param_1 = *(undefined8 *)(param_2 + 8);
  return;
}

// ==== CGameResourceDownloader::IsErrorStatus() const
// vaddr 0x17ddc9c | ghidra 0x18ddc9c | size 16 | symbol _ZNK23CGameResourceDownloader13IsErrorStatusEv | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK23CGameResourceDownloader13IsErrorStatusEv(long param_1)

{
  return *(long *)(param_1 + 0x160) != 0;
}

// ==== CGameResourceDownloader::IsVersionFile(char const*)
// vaddr 0x17ddcac | ghidra 0x18ddcac | size 404 | symbol _ZN23CGameResourceDownloader13IsVersionFileEPKc | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN23CGameResourceDownloader13IsVersionFileEPKc(long param_1,undefined8 param_2)

{
  ulong uVar1;
  byte bVar2;
  bool bVar3;
  long lVar4;
  int iVar5;
  byte bVar6;
  byte abStack_90 [16];
  ulong uStack_80;
  byte abStack_78 [16];
  ulong uStack_68;
  
  lVar4 = strstr(param_2,&UNK_02866dd0/*"version.bin"*/);
  if ((((lVar4 == 0) && (lVar4 = strstr(param_2,&UNK_02866db9/*"version.version"*/), lVar4 == 0)) &&
      (lVar4 = strstr(param_2,&UNK_02866d7e/*"version_latest_Bulk.bin"*/), lVar4 == 0)) &&
     (((lVar4 = strstr(param_2,&UNK_02866ddc/*"version_latest_Bulk.version"*/), lVar4 == 0 &&
       (lVar4 = strstr(param_2,&UNK_02866e24/*"version_latest_Individual.bin"*/), lVar4 == 0)) &&
      (lVar4 = strstr(param_2,&UNK_02866df8/*"version_latest_Individual.version"*/), lVar4 == 0)))) {
    iVar5 = 1;
    do {
      if (*(uint *)(param_1 + 0x278) <= iVar5 - 1U) {
        return 0;
      }
      Framework::CSTLStringUtility_Base<string >::Format(char const*, ...)(abStack_78,&UNK_02866b05/*"version_latest_ep%d.bin"*/,iVar5);
      Framework::CSTLStringUtility_Base<string >::Format(char const*, ...)(abStack_90,&UNK_02866b31/*"version_latest_ep%d.version"*/,iVar5);
      bVar6 = abStack_78[0];
      uVar1 = (ulong)abStack_78 | 1;
      if ((abStack_78[0] & 1) != 0) {
        uVar1 = uStack_68;
      }
      lVar4 = strstr(param_2,uVar1);
      bVar2 = abStack_90[0];
      if (lVar4 == 0) {
        uVar1 = (ulong)abStack_90 | 1;
        if ((abStack_90[0] & 1) != 0) {
          uVar1 = uStack_80;
        }
        lVar4 = strstr(param_2,uVar1);
        bVar3 = lVar4 != 0;
      }
      else {
        bVar3 = true;
      }
      if ((bVar2 & 1) != 0) {
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_80);
        bVar6 = abStack_78[0];
      }
      if ((bVar6 & 1) != 0) {
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_68);
      }
      iVar5 = iVar5 + 1;
    } while (!bVar3);
  }
  return 1;
}

// ==== CGameResourceDownloader::SetDownloadDataServer(char const*)
// vaddr 0x17dde40 | ghidra 0x18dde40 | size 420 | symbol _ZN23CGameResourceDownloader21SetDownloadDataServerEPKc | lib libSOA-3.7.0.so | 2026-10-04
void _ZN23CGameResourceDownloader21SetDownloadDataServerEPKc(long param_1,long param_2)

{
  ulong *puVar1;
  byte bVar2;
  int iVar3;
  ulong uVar4;
  ulong uVar5;
  long lVar6;
  byte *pbVar7;
  undefined1 *puVar8;
  ulong uVar9;
  
  if (param_2 == 0) {
    return;
  }
  puVar1 = (ulong *)(param_1 + 0x220);
  uVar4 = strlen(param_2);
  if ((*(byte *)(param_1 + 0x220) & 1) == 0) {
    uVar9 = (ulong)(*(byte *)(param_1 + 0x220) >> 1);
    lVar6 = param_1 + 0x221;
  }
  else {
    uVar9 = *(ulong *)(param_1 + 0x228);
    lVar6 = *(long *)(param_1 + 0x230);
  }
  uVar5 = uVar4;
  if (uVar9 < uVar4 || uVar9 == uVar4) {
    uVar5 = uVar9;
  }
  if (uVar5 == 0) {
    if (uVar9 != uVar4) goto code_r0x018ddeac;
  }
  else {
    iVar3 = memcmp(lVar6,param_2);
    if ((uVar9 != uVar4) || (iVar3 != 0)) {
code_r0x018ddeac:
      lVar6 = *(long *)(param_1 + 0x5d8);
      if (lVar6 != 0) {
        pbVar7 = (byte *)(lVar6 + 0x40);
        bVar2 = *pbVar7;
        if ((bVar2 & 1) != 0) {
          bVar2 = *pbVar7;
        }
        if ((bVar2 & 1) == 0) {
          puVar8 = (undefined1 *)(lVar6 + 0x41);
        }
        else {
          puVar8 = *(undefined1 **)(lVar6 + 0x50);
        }
        *puVar8 = 0;
        if ((*pbVar7 & 1) == 0) {
          *pbVar7 = 0;
        }
        else {
          *(undefined8 *)(lVar6 + 0x48) = 0;
        }
        bVar2 = *(byte *)(param_1 + 0x238);
        pbVar7 = (byte *)(param_1 + 0x238);
        if ((bVar2 & 1) != 0) {
          bVar2 = *pbVar7;
        }
        if ((bVar2 & 1) == 0) {
          puVar8 = (undefined1 *)(param_1 + 0x239);
        }
        else {
          puVar8 = *(undefined1 **)(param_1 + 0x248);
        }
        *puVar8 = 0;
        if ((*pbVar7 & 1) == 0) {
          *pbVar7 = 0;
        }
        else {
          *(undefined8 *)(param_1 + 0x240) = 0;
        }
      }
    }
  }
  uVar4 = strlen(param_2);
  uVar9 = (ulong)*(byte *)puVar1;
  if ((*(byte *)puVar1 & 1) == 0) {
    uVar5 = 0x16;
    lVar6 = uVar4 - 0x16;
    if (0x15 < uVar4 && lVar6 != 0) {
code_r0x018ddf68:
      if ((uVar9 & 1) == 0) {
        uVar9 = (ulong)(((uint)uVar9 & 0xfe) >> 1);
      }
      else {
        uVar9 = *(ulong *)(param_1 + 0x228);
      }
      (*(code *)
        PTR__ZNSt6__ndk112basic_stringIcNS_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS3_22CSTLStringAllocatorInfEEEE21__grow_by_and_replaceEmmmmmmPKc_02ca6d40
      )(puVar1,uVar5,lVar6,uVar9,0,uVar9,uVar4,param_2);
      return;
    }
  }
  else {
    uVar9 = *puVar1;
    uVar5 = (uVar9 & 0xfffffffffffffffe) - 1;
    lVar6 = uVar4 - uVar5;
    if (uVar5 <= uVar4 && lVar6 != 0) goto code_r0x018ddf68;
  }
  if ((uVar9 & 1) == 0) {
    lVar6 = param_1 + 0x221;
  }
  else {
    lVar6 = *(long *)(param_1 + 0x230);
  }
  if (uVar4 != 0) {
    memmove(lVar6,param_2,uVar4);
  }
  *(undefined1 *)(lVar6 + uVar4) = 0;
  if ((*(byte *)puVar1 & 1) == 0) {
    *(byte *)puVar1 = (byte)(uVar4 << 1);
  }
  else {
    *(ulong *)(param_1 + 0x228) = uVar4;
  }
  return;
}

// ==== CGameResourceDownloader::SetServerAssetRevision(char const*)
// vaddr 0x17ddfe4 | ghidra 0x18ddfe4 | size 324 | symbol _ZN23CGameResourceDownloader22SetServerAssetRevisionEPKc | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZN23CGameResourceDownloader22SetServerAssetRevisionEPKc(long param_1,long param_2)

{
  ulong *puVar1;
  ulong uVar2;
  byte bVar3;
  int iVar4;
  ulong uVar5;
  undefined4 uVar6;
  ulong uVar7;
  ulong uVar8;
  long lVar9;
  
  if (param_2 == 0) {
    return 0;
  }
  puVar1 = (ulong *)(param_1 + 0x238);
  uVar5 = strlen(param_2);
  bVar3 = *(byte *)(param_1 + 0x238);
  uVar8 = (ulong)bVar3;
  if ((bVar3 & 1) == 0) {
    uVar7 = (ulong)(bVar3 >> 1);
    lVar9 = param_1 + 0x239;
  }
  else {
    uVar7 = *(ulong *)(param_1 + 0x240);
    lVar9 = *(long *)(param_1 + 0x248);
  }
  uVar2 = uVar5;
  if (uVar7 <= uVar5) {
    uVar2 = uVar7;
  }
  if (uVar2 == 0) {
    if (uVar7 == uVar5) goto code_r0x018de054;
code_r0x018de064:
    uVar6 = 1;
    *(undefined1 *)(param_1 + 0x155) = 1;
  }
  else {
    iVar4 = memcmp(lVar9,param_2);
    if ((uVar7 != uVar5) || (iVar4 != 0)) goto code_r0x018de064;
code_r0x018de054:
    uVar6 = 0;
  }
  uVar5 = strlen(param_2);
  if ((bVar3 & 1) == 0) {
    uVar7 = 0x16;
    lVar9 = uVar5 - 0x16;
    if (0x15 < uVar5 && lVar9 != 0) {
code_r0x018de0ac:
      if ((uVar8 & 1) == 0) {
        uVar8 = (ulong)(((uint)uVar8 & 0xfe) >> 1);
      }
      else {
        uVar8 = *(ulong *)(param_1 + 0x240);
      }
      string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(puVar1,uVar7,lVar9,uVar8,0,uVar8,uVar5,param_2);
      return uVar6;
    }
  }
  else {
    uVar8 = *puVar1;
    uVar7 = (uVar8 & 0xfffffffffffffffe) - 1;
    lVar9 = uVar5 - uVar7;
    if (uVar7 <= uVar5 && lVar9 != 0) goto code_r0x018de0ac;
  }
  if ((uVar8 & 1) == 0) {
    lVar9 = param_1 + 0x239;
  }
  else {
    lVar9 = *(long *)(param_1 + 0x248);
  }
  if (uVar5 != 0) {
    memmove(lVar9,param_2,uVar5);
  }
  *(undefined1 *)(lVar9 + uVar5) = 0;
  if ((*(byte *)puVar1 & 1) == 0) {
    *(byte *)puVar1 = (byte)(uVar5 << 1);
  }
  else {
    *(ulong *)(param_1 + 0x240) = uVar5;
  }
  return uVar6;
}

// ==== CGameResourceDownloader::GetLocalAssetevision() const
// vaddr 0x17de128 | ghidra 0x18de128 | size 332 | symbol _ZNK23CGameResourceDownloader20GetLocalAssetevisionEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK23CGameResourceDownloader20GetLocalAssetevisionEv(ulong *param_1,long param_2)

{
  long lVar1;
  ulong uVar2;
  ulong uVar3;
  undefined8 uVar4;
  ulong uVar5;
  
  if (*(char *)(param_2 + 0x156) == '\0') {
    param_1[1] = 0;
    param_1[2] = 0;
    *param_1 = 0;
    if ((*(byte *)(param_2 + 0x238) & 1) == 0) {
      param_1[2] = *(ulong *)(param_2 + 0x248);
      uVar3 = *(ulong *)(param_2 + 0x238);
      param_1[1] = *(ulong *)(param_2 + 0x240);
      *param_1 = uVar3;
      return;
    }
    uVar3 = *(ulong *)(param_2 + 0x240);
    uVar4 = *(undefined8 *)(param_2 + 0x248);
    if (0x16 < uVar3) goto code_r0x018de1e8;
code_r0x018de1c4:
    uVar2 = (long)param_1 + 1;
    *(char *)param_1 = (char)(uVar3 << 1);
    if (uVar3 == 0) goto code_r0x018de260;
  }
  else {
    lVar1 = *(long *)(param_2 + 0x5d8);
    if (lVar1 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02866a48/*"C:\BAS_Submission\Client\Project\..\Source\Game\Resource\GameResourceDownloader.cpp"*/,0xdc5,&UNK_02866bdf/*"m_VersionInfo is null."*/);
      lVar1 = *(long *)(param_2 + 0x5d8);
    }
    param_1[1] = 0;
    param_1[2] = 0;
    *param_1 = 0;
    if ((*(byte *)(lVar1 + 0x40) & 1) == 0) {
      param_1[2] = *(ulong *)(lVar1 + 0x50);
      uVar3 = *(ulong *)(lVar1 + 0x40);
      param_1[1] = *(ulong *)(lVar1 + 0x48);
      *param_1 = uVar3;
      return;
    }
    uVar3 = *(ulong *)(lVar1 + 0x48);
    uVar4 = *(undefined8 *)(lVar1 + 0x50);
    if (uVar3 < 0x17) goto code_r0x018de1c4;
code_r0x018de1e8:
    uVar5 = uVar3 + 0x10 & 0xfffffffffffffff0;
    if (uVar5 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
    }
    uVar2 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar5,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
    if (uVar2 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    }
    param_1[1] = uVar3;
    param_1[2] = uVar2;
    *param_1 = uVar5 | 1;
  }
  memcpy(uVar2,uVar4,uVar3);
code_r0x018de260:
  *(undefined1 *)(uVar2 + uVar3) = 0;
  return;
}

// ==== CGameResourceDownloader::UpdateEpisodeDataMaxSize()
// vaddr 0x17de274 | ghidra 0x18de274 | size 28 | symbol _ZN23CGameResourceDownloader24UpdateEpisodeDataMaxSizeEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN23CGameResourceDownloader24UpdateEpisodeDataMaxSizeEv(long param_1)

{
  *(undefined4 *)(param_1 + 0x278) =
       *(undefined4 *)
        (*(long *)PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0 + 0xb6f0
        );
  return;
}

// ==== CGameResourceDownloader::PermissionDownload()
// vaddr 0x17de290 | ghidra 0x18de290 | size 260 | symbol _ZN23CGameResourceDownloader18PermissionDownloadEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN23CGameResourceDownloader18PermissionDownloadEv(long param_1)

{
  ulong *puVar1;
  ulong uVar2;
  ulong uVar3;
  long lVar4;
  ulong uVar5;
  long lVar6;
  long lVar7;
  
  *(undefined1 *)(param_1 + 0x15c) = 1;
  *(undefined2 *)(param_1 + 0x155) = 0x101;
  lVar7 = *(long *)(param_1 + 0x5d8);
  if ((lVar7 != 0) && (puVar1 = (ulong *)(lVar7 + 0x40), puVar1 != (ulong *)(param_1 + 0x238))) {
    lVar4 = *(long *)(param_1 + 0x248);
    uVar5 = *(ulong *)(param_1 + 0x240);
    uVar3 = (ulong)*(byte *)puVar1;
    if ((*(byte *)(param_1 + 0x238) & 1) == 0) {
      lVar4 = param_1 + 0x239;
      uVar5 = (ulong)(*(byte *)(param_1 + 0x238) >> 1);
    }
    if ((*(byte *)puVar1 & 1) == 0) {
      uVar2 = 0x16;
      lVar6 = uVar5 - 0x16;
      if (0x15 < uVar5 && lVar6 != 0) {
code_r0x018de31c:
        if ((uVar3 & 1) == 0) {
          uVar3 = (ulong)(((uint)uVar3 & 0xfe) >> 1);
        }
        else {
          uVar3 = *(ulong *)(lVar7 + 0x48);
        }
        (*(code *)
          PTR__ZNSt6__ndk112basic_stringIcNS_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS3_22CSTLStringAllocatorInfEEEE21__grow_by_and_replaceEmmmmmmPKc_02ca6d40
        )(puVar1,uVar2,lVar6,uVar3,0,uVar3,uVar5);
        return;
      }
    }
    else {
      uVar3 = *puVar1;
      uVar2 = (uVar3 & 0xfffffffffffffffe) - 1;
      lVar6 = uVar5 - uVar2;
      if (uVar2 <= uVar5 && lVar6 != 0) goto code_r0x018de31c;
    }
    if ((uVar3 & 1) == 0) {
      lVar6 = lVar7 + 0x41;
    }
    else {
      lVar6 = *(long *)(lVar7 + 0x50);
    }
    if (uVar5 != 0) {
      memmove(lVar6,lVar4,uVar5);
    }
    *(undefined1 *)(lVar6 + uVar5) = 0;
    if ((*(byte *)puVar1 & 1) == 0) {
      *(byte *)puVar1 = (byte)(uVar5 << 1);
    }
    else {
      *(ulong *)(lVar7 + 0x48) = uVar5;
    }
  }
  return;
}

// ==== CGameResourceDownloader::GetMutex()
// vaddr 0x17de394 | ghidra 0x18de394 | size 8 | symbol _ZN23CGameResourceDownloader8GetMutexEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZN23CGameResourceDownloader8GetMutexEv(long param_1)

{
  return param_1 + 0x170;
}

// ==== CGameResourceDownloader::WriteToTempDownloadList(char const*, char const*, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, CMetaList*, char const*)
// vaddr 0x17de39c | ghidra 0x18de39c | size 24 | symbol _ZN23CGameResourceDownloader23WriteToTempDownloadListEPKcS1_jjjjjP9CMetaListS1_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN23CGameResourceDownloader23WriteToTempDownloadListEPKcS1_jjjjjP9CMetaListS1_(long param_1)

{
  if (*(long *)(param_1 + 0x480) != 0) {
    (*(code *)
      PTR__ZN23CGameResourceDownloader18CJournalFileWriter12AddWriteInfoEPKcS2_jjjjjP9CMetaListS2__02c97480
    )();
    return;
  }
  return;
}

// ==== CGameResourceDownloader::CJournalFileWriter::AddWriteInfo(char const*, char const*, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, CMetaList*, char const*)
// vaddr 0x17de3b4 | ghidra 0x18de3b4 | size 428 | symbol _ZN23CGameResourceDownloader18CJournalFileWriter12AddWriteInfoEPKcS2_jjjjjP9CMetaListS2_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN23CGameResourceDownloader18CJournalFileWriter12AddWriteInfoEPKcS2_jjjjjP9CMetaListS2_
               (long param_1,undefined8 param_2,undefined8 param_3,undefined4 param_4,
               undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8,
               undefined8 param_9,undefined8 param_10)

{
  long lVar1;
  ulong uVar2;
  long lVar3;
  long lVar4;
  
  lVar1 = param_1 + 0x10;
  uVar2 = Framework::CMutex::IsInitialized() const(lVar1);
  if ((uVar2 & 1) == 0) {
    Framework::CMutex::Initialize()(lVar1);
  }
  Framework::CMutex::Lock()(lVar1);
  param_1 = param_1 + (ulong)*(uint *)(param_1 + 0x170) * 0x38;
  Aska::TArray<CGameResourceDownloader::CJournalFileWriter::tWriteInfo, false>::Resize(long, bool)(param_1 + 0x1a8,*(long *)(param_1 + 0x1c0) + 1,0);
  lVar3 = *(long *)(param_1 + 0x1b0);
  lVar4 = *(long *)(param_1 + 0x1c0) + -1;
  uVar2 = strlen(param_2);
  if (0xff < uVar2) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dc32f/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/Utility.h"*/,0x77,&UNK_027dc380/*"gStrcpy() : destination buffer is small. ( %d < %d )"*/,uVar2,0x100);
  }
  strcpy(lVar3 + lVar4 * 0x168,param_2);
  uVar2 = strlen(param_3);
  if (0x3f < uVar2) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dc32f/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/Utility.h"*/,0x77,&UNK_027dc380/*"gStrcpy() : destination buffer is small. ( %d < %d )"*/,uVar2,0x40);
  }
  strcpy(lVar3 + lVar4 * 0x168 + 0x100,param_3);
  lVar3 = lVar3 + lVar4 * 0x168;
  *(undefined4 *)(lVar3 + 0x140) = param_4;
  *(undefined4 *)(lVar3 + 0x144) = param_5;
  *(undefined4 *)(lVar3 + 0x148) = param_6;
  *(undefined4 *)(lVar3 + 0x14c) = param_7;
  *(undefined8 *)(lVar3 + 0x158) = param_9;
  *(undefined4 *)(lVar3 + 0x150) = param_8;
  uVar2 = strlen(param_10);
  if (4 < uVar2) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dc32f/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/Utility.h"*/,0x77,&UNK_027dc380/*"gStrcpy() : destination buffer is small. ( %d < %d )"*/,uVar2,5);
  }
  strcpy(lVar3 + 0x160,param_10);
  (*(code *)PTR__ZN9Framework6CMutex6UnlockEv_02cb3f98)(lVar1);
  return;
}

// ==== CGameResourceDownloader::EnableDefaultErrorHandle(bool)
// vaddr 0x17de560 | ghidra 0x18de560 | size 12 | symbol _ZN23CGameResourceDownloader24EnableDefaultErrorHandleEb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN23CGameResourceDownloader24EnableDefaultErrorHandleEb(long param_1,byte param_2)

{
  *(byte *)(param_1 + 0x157) = param_2 & 1;
  return;
}

// ==== CGameResourceDownloader::checkLocalEpisodeFilelistVersion(std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > const&)
// vaddr 0x17de920 | ghidra 0x18de920 | size 760 | symbol _ZN23CGameResourceDownloader32checkLocalEpisodeFilelistVersionERKNSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN23CGameResourceDownloader32checkLocalEpisodeFilelistVersionERKNSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEE
               (ulong *param_1,long param_2,byte *param_3)

{
  int iVar1;
  ulong uVar2;
  long lVar3;
  ulong uVar4;
  byte *pbVar5;
  undefined *puVar6;
  long lVar7;
  ulong uVar8;
  ulong uStack_58;
  ulong uStack_50;
  ulong uStack_48;
  
  param_1[1] = 0;
  param_1[2] = 0;
  *param_1 = 0;
  lVar7 = *(long *)(param_2 + 0x430);
  lVar3 = *(long *)(param_2 + 0x438);
  while (lVar3 != lVar7) {
    *(long *)(param_2 + 0x438) = lVar3 + -0x90;
    (*(code *)**(undefined8 **)(lVar3 + -0x90))();
    lVar3 = *(long *)(param_2 + 0x438);
  }
  lVar3 = *(long *)(param_2 + 0x4a8);
  if (lVar3 != *(long *)(param_2 + 0x4a0)) {
    *(ulong *)(param_2 + 0x4a8) =
         lVar3 + (~((lVar3 + -8) - *(long *)(param_2 + 0x4a0)) & 0xfffffffffffffff8U);
  }
  if ((*param_3 & 1) == 0) {
    pbVar5 = param_3 + 1;
  }
  else {
    pbVar5 = *(byte **)(param_3 + 0x10);
    if (pbVar5 == (byte *)0x0) {
      return;
    }
  }
  iVar1 = access(pbVar5,0);
  if (iVar1 != 0) {
    return;
  }
  pbVar5 = *(byte **)(param_3 + 0x10);
  uStack_50 = 0;
  uStack_48 = 0;
  uStack_58 = 0;
  if ((*param_3 & 1) == 0) {
    pbVar5 = param_3 + 1;
  }
  uVar2 = strlen(pbVar5);
  if (uVar2 < 0x17) {
    uVar8 = (ulong)&uStack_58 | 1;
    uStack_58 = CONCAT71(uStack_58._1_7_,(char)(uVar2 << 1));
    if (uVar2 != 0) goto code_r0x018dea6c;
  }
  else {
    uVar4 = uVar2 + 0x10 & 0xfffffffffffffff0;
    if (uVar4 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
    }
    uVar8 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar4,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
    if (uVar8 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    }
    uStack_58 = uVar4 | 1;
    uStack_50 = uVar2;
    uStack_48 = uVar8;
code_r0x018dea6c:
    memcpy(uVar8,pbVar5,uVar2);
  }
  *(undefined1 *)(uVar8 + uVar2) = 0;
  CGameResourceDownloader::LoadVersionFileToAsonEpisodeData(string const&)(param_2,&uStack_58);
  if ((uStack_58 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_48);
  }
  lVar3 = *(long *)(param_2 + 0x430);
  if (*(long *)(param_2 + 0x438) == lVar3) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dc536/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Vector.h"*/,0x58,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,0,0);
    lVar3 = *(long *)(param_2 + 0x430);
  }
  if ((*(int *)(lVar3 + 0x60) == 7) &&
     (lVar3 = Aska::ASON::AValue::AMap::Get_(char const*)(lVar3 + 0x68,&UNK_02a354cc/*"version"*/), lVar3 != 0)) {
    puVar6 = *(undefined **)(lVar3 + 0x10);
  }
  else {
    puVar6 = &UNK_029d2011;
  }
  uVar2 = strlen(puVar6);
  uVar4 = (ulong)(byte)*param_1;
  if (((byte)*param_1 & 1) == 0) {
    uVar8 = 0x16;
    lVar3 = uVar2 - 0x16;
    if (0x15 < uVar2 && lVar3 != 0) {
code_r0x018deb44:
      if ((uVar4 & 1) == 0) {
        uVar4 = (ulong)(((uint)uVar4 & 0xfe) >> 1);
      }
      else {
        uVar4 = param_1[1];
      }
      string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(param_1,uVar8,lVar3,uVar4,0,uVar4,uVar2,puVar6);
      lVar3 = *(long *)(param_2 + 0x430);
      goto code_r0x018debcc;
    }
  }
  else {
    uVar4 = *param_1;
    uVar8 = (uVar4 & 0xfffffffffffffffe) - 1;
    lVar3 = uVar2 - uVar8;
    if (uVar8 <= uVar2 && lVar3 != 0) goto code_r0x018deb44;
  }
  if ((uVar4 & 1) == 0) {
    pbVar5 = (byte *)((long)param_1 + 1);
  }
  else {
    pbVar5 = (byte *)param_1[2];
  }
  if (uVar2 != 0) {
    memmove(pbVar5,puVar6,uVar2);
  }
  pbVar5[uVar2] = 0;
  if ((*param_1 & 1) == 0) {
    *(byte *)param_1 = (byte)(uVar2 << 1);
    lVar3 = *(long *)(param_2 + 0x430);
  }
  else {
    param_1[1] = uVar2;
    lVar3 = *(long *)(param_2 + 0x430);
  }
code_r0x018debcc:
  while (lVar7 = *(long *)(param_2 + 0x438), lVar7 != lVar3) {
    *(long *)(param_2 + 0x438) = lVar7 + -0x90;
    (*(code *)**(undefined8 **)(lVar7 + -0x90))();
  }
  lVar3 = *(long *)(param_2 + 0x4a8);
  if (lVar3 != *(long *)(param_2 + 0x4a0)) {
    *(ulong *)(param_2 + 0x4a8) =
         lVar3 + (~((lVar3 + -8) - *(long *)(param_2 + 0x4a0)) & 0xfffffffffffffff8U);
  }
  return;
}

// ==== CGameResourceDownloader::ClearLocalAssetRevision()
// vaddr 0x17dec18 | ghidra 0x18dec18 | size 72 | symbol _ZN23CGameResourceDownloader23ClearLocalAssetRevisionEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN23CGameResourceDownloader23ClearLocalAssetRevisionEv(long param_1)

{
  byte bVar1;
  long lVar2;
  
  lVar2 = *(long *)(param_1 + 0x5d8);
  if (lVar2 != 0) {
    if ((*(byte *)(lVar2 + 0x40) & 1) != 0) {
      **(undefined1 **)(lVar2 + 0x50) = 0;
      *(undefined8 *)(lVar2 + 0x48) = 0;
      bVar1 = *(byte *)(param_1 + 0x238);
      goto joined_r0x018dec4c;
    }
    *(undefined2 *)(lVar2 + 0x40) = 0;
  }
  bVar1 = *(byte *)(param_1 + 0x238);
joined_r0x018dec4c:
  if ((bVar1 & 1) == 0) {
    *(undefined2 *)(param_1 + 0x238) = 0;
    return;
  }
  **(undefined1 **)(param_1 + 0x248) = 0;
  *(undefined8 *)(param_1 + 0x240) = 0;
  return;
}

// ==== CGameResourceDownloader::CDownloadNode::CDownloadNode(char const*, std::__ndk1::function<void (char const*, CGameResourceDownloader::iErrorCode)>)
// vaddr 0x17dec60 | ghidra 0x18dec60 | size 440 | symbol _ZN23CGameResourceDownloader13CDownloadNodeC2EPKcNSt6__ndk18functionIFvS2_NS_10iErrorCodeEEEE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN23CGameResourceDownloader13CDownloadNodeC1EPKcNSt6__ndk18functionIFvS2_NS_10iErrorCodeEEEE
               (long *param_1,undefined8 param_2,long *param_3)

{
  undefined *puVar1;
  undefined *puVar2;
  ulong uVar3;
  long *plVar4;
  code *pcVar5;
  long alStack_60 [4];
  long *plStack_40;
  
  puVar1 = PTR__ZTVN23CGameResourceDownloader13CDownloadNodeE_02cb9b98 + 0x10;
  *(undefined1 *)(param_1 + 0x22) = 0;
  param_1[0x28] = 0;
  *(undefined1 *)(param_1 + 0x2a) = 0;
  param_1[0x31] = 0;
  *(undefined4 *)(param_1 + 0x32) = 0;
  param_1[0x33] = 0;
  param_1[0x2f] = 0;
  *(undefined4 *)(param_1 + 0x30) = 0;
  *param_1 = (long)puVar1;
  param_1[1] = 0;
  param_1[0x2e] = 0;
  param_1[0x2d] = 0;
  puVar1 = PTR__ZTVN4Aska10FileStreamE_02cbc9f8;
  param_1[0x2c] = 0;
  param_1[0x2b] = 0;
  puVar2 = PTR__ZTVN23CGameResourceDownloader13CDownloadNode15CDownloadStreamE_02cbd948;
  param_1[0x36] = (long)(PTR__ZTVN4Aska4FileE_02cb6e28 + 0x10);
  param_1[0x35] = (long)(puVar1 + 0x10);
  *(undefined1 *)(param_1 + 0x37) = 0;
  *(undefined1 *)(param_1 + 0x3a) = 0;
  param_1[0x38] = 0;
  param_1[0x39] = 0;
  param_1[0x34] = (long)(puVar2 + 0x10);
  param_1[0x6c] = 0;
  param_1[100] = 0;
  param_1[0x65] = 0;
  *(undefined4 *)(param_1 + 0x6d) = 0;
  param_1[0x6e] = 0x100000;
  param_1[0x72] = 0;
  param_1[0x6f] = 0;
  param_1[0x71] = 0;
  param_1[0x70] = 0;
  *(undefined4 *)(param_1 + 0x73) = 0x3f800000;
  Framework::CMutex::CMutex()(param_1 + 0x74);
  uVar3 = strlen(param_2);
  if (0xff < uVar3) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dc32f/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/Utility.h"*/,0x77,&UNK_027dc380/*"gStrcpy() : destination buffer is small. ( %d < %d )"*/,uVar3,0x100);
  }
  strcpy(param_1 + 2,param_2);
  Framework::CMutex::Initialize()(param_1 + 0x74);
  plVar4 = (long *)param_3[4];
  if (plVar4 != (long *)0x0) {
    if (param_3 == plVar4) {
      plStack_40 = alStack_60;
      (**(code **)(*plVar4 + 0x18))(plVar4,alStack_60);
    }
    else {
      plStack_40 = (long *)(**(code **)(*plVar4 + 0x10))();
    }
    CGameResourceDownloader::CDownloadNode::RegistryCallback(char const*, std::__ndk1::function<void (char const*, CGameResourceDownloader::iErrorCode)>)(param_1,param_1 + 2,alStack_60);
    if (alStack_60 == plStack_40) {
      pcVar5 = *(code **)(*plStack_40 + 0x20);
    }
    else {
      if (plStack_40 == (long *)0x0) {
        return;
      }
      pcVar5 = *(code **)(*plStack_40 + 0x28);
    }
    (*pcVar5)();
  }
  return;
}

// ==== CGameResourceDownloader::CDownloadNode::~CDownloadNode()
// vaddr 0x17dee18 | ghidra 0x18dee18 | size 516 | symbol _ZN23CGameResourceDownloader13CDownloadNodeD1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN23CGameResourceDownloader13CDownloadNodeD2Ev(long *param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  undefined *puVar3;
  long lVar4;
  long *plVar5;
  long *plVar6;
  long lVar7;
  code *UNRECOVERED_JUMPTABLE;
  long lVar8;
  
  lVar8 = param_1[0x33];
  *param_1 = (long)(PTR__ZTVN23CGameResourceDownloader13CDownloadNodeE_02cb9b98 + 0x10);
  puVar3 = PTR__ZTVN4Aska4FileE_02cb6e28;
  if (lVar8 != 0) {
    lVar7 = *(long *)(lVar8 + -8);
    if (lVar7 != 0) {
      lVar7 = lVar7 * 0x140;
      puVar1 = PTR__ZTVN23CGameResourceDownloader13CDownloadNode12UnpackNotifyE_02cc1100 + 0x10;
      puVar2 = PTR__ZTVN4Aska4FileE_02cb6e28 + 0x10;
      do {
        while( true ) {
          lVar4 = lVar8 + lVar7;
          *(undefined **)(lVar4 + -0x140) = puVar1;
          if (*(long *)(lVar4 + -0x10) == 0) break;
          Aska::File::Close()(lVar4 + -0x20);
          *(undefined **)(lVar4 + -0x20) = puVar3 + 0x10;
          if (*(long *)(lVar4 + -0x10) != 0) {
            Aska::File::Close()(lVar4 + -0x20);
          }
          lVar7 = lVar7 + -0x140;
          if (lVar7 == 0) goto code_r0x018deec4;
        }
        *(undefined **)(lVar4 + -0x20) = puVar2;
        lVar7 = lVar7 + -0x140;
      } while (lVar7 != 0);
    }
code_r0x018deec4:
    operator delete[](void*)((long *)(lVar8 + -8));
    param_1[0x33] = 0;
  }
  if ((long *)param_1[0x2f] != (long *)0x0) {
    (**(code **)(*(long *)param_1[0x2f] + 8))();
    param_1[0x2f] = 0;
  }
  Framework::CMutex::~CMutex()(param_1 + 0x74);
  plVar6 = (long *)param_1[0x71];
  do {
    if (plVar6 == (long *)0x0) {
      lVar8 = param_1[0x6f];
      param_1[0x6f] = 0;
      if (lVar8 != 0) {
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)();
      }
      param_1[0x34] =
           (long)(PTR__ZTVN23CGameResourceDownloader13CDownloadNode15CDownloadStreamE_02cbd948 +
                 0x10);
      if (param_1[0x6c] != 0) {
        operator delete[](void*)();
        param_1[0x6c] = 0;
      }
      puVar3 = PTR__ZTVN4Aska5Yayoi10Downloader14DownloadStreamE_02cc1c28 + 0x10;
      param_1[0x35] = (long)(PTR__ZTVN4Aska10FileStreamE_02cbc9f8 + 0x10);
      param_1[0x34] = (long)puVar3;
      Aska::FileStream::Close()(param_1 + 0x35);
      param_1[0x36] = (long)(PTR__ZTVN4Aska4FileE_02cb6e28 + 0x10);
      if (param_1[0x38] != 0) {
        Aska::File::Close()(param_1 + 0x36);
      }
      if ((*(byte *)(param_1 + 0x2c) & 1) != 0) {
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(param_1[0x2e]);
      }
      plVar6 = (long *)param_1[0x28];
      if (param_1 + 0x24 == plVar6) {
        UNRECOVERED_JUMPTABLE = *(code **)(*plVar6 + 0x20);
      }
      else {
        if (plVar6 == (long *)0x0) {
          return;
        }
        UNRECOVERED_JUMPTABLE = *(code **)(*plVar6 + 0x28);
      }
                    /* WARNING: Could not recover jumptable at 0x018df000. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (*UNRECOVERED_JUMPTABLE)();
      return;
    }
    plVar5 = (long *)plVar6[0x28];
    lVar8 = *plVar6;
    if (plVar6 + 0x24 == plVar5) {
      UNRECOVERED_JUMPTABLE = *(code **)(*plVar5 + 0x20);
code_r0x018def28:
      (*UNRECOVERED_JUMPTABLE)();
    }
    else if (plVar5 != (long *)0x0) {
      UNRECOVERED_JUMPTABLE = *(code **)(*plVar5 + 0x28);
      goto code_r0x018def28;
    }
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar6);
    plVar6 = (long *)lVar8;
  } while( true );
}

// ==== CGameResourceDownloader::CDownloadNode::CDownloadStream::~CDownloadStream()
// vaddr 0x17df01c | ghidra 0x18df01c | size 128 | symbol _ZN23CGameResourceDownloader13CDownloadNode15CDownloadStreamD2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN23CGameResourceDownloader13CDownloadNode15CDownloadStreamD2Ev(long *param_1)

{
  undefined *puVar1;
  
  *param_1 = (long)(PTR__ZTVN23CGameResourceDownloader13CDownloadNode15CDownloadStreamE_02cbd948 +
                   0x10);
  if (param_1[0x38] != 0) {
    operator delete[](void*)();
    param_1[0x38] = 0;
  }
  puVar1 = PTR__ZTVN4Aska5Yayoi10Downloader14DownloadStreamE_02cc1c28 + 0x10;
  param_1[1] = (long)(PTR__ZTVN4Aska10FileStreamE_02cbc9f8 + 0x10);
  *param_1 = (long)puVar1;
  Aska::FileStream::Close()(param_1 + 1);
  param_1[2] = (long)(PTR__ZTVN4Aska4FileE_02cb6e28 + 0x10);
  if (param_1[4] != 0) {
    (*(code *)PTR__ZN4Aska4File5CloseEv_02c8e880)(param_1 + 2);
    return;
  }
  return;
}

// ==== CGameResourceDownloader::CDownloadNode::~CDownloadNode()
// vaddr 0x17df09c | ghidra 0x18df09c | size 24 | symbol _ZN23CGameResourceDownloader13CDownloadNodeD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN23CGameResourceDownloader13CDownloadNodeD0Ev(undefined8 param_1)

{
  CGameResourceDownloader::CDownloadNode::~CDownloadNode()();
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== CGameResourceDownloader::CDownloadNode::StartDownload()
// vaddr 0x17df0b4 | ghidra 0x18df0b4 | size 2404 | symbol _ZN23CGameResourceDownloader13CDownloadNode13StartDownloadEv | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Type propagation algorithm not settling */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN23CGameResourceDownloader13CDownloadNode13StartDownloadEv(long param_1)

{
  long lVar1;
  ulong uVar2;
  char cVar3;
  undefined *puVar4;
  undefined *puVar5;
  char cVar6;
  undefined2 uVar7;
  undefined2 uVar8;
  undefined5 uVar9;
  undefined5 uVar10;
  int iVar11;
  ulong uVar12;
  ulong uVar13;
  long lVar14;
  ulong uVar15;
  undefined1 *puVar16;
  ulong uVar17;
  ulong uVar18;
  ulong uStack_c8;
  ulong uStack_c0;
  ulong uStack_b8;
  byte bStack_b0;
  undefined7 uStack_af;
  char cStack_a8;
  undefined2 uStack_a7;
  undefined5 uStack_a5;
  ulong uStack_a0;
  ulong uStack_90;
  ulong uStack_88;
  ulong uStack_80;
  ulong uStack_70;
  ulong uStack_68;
  ulong uStack_60;
  ulong uStack_58;
  ulong uStack_50;
  undefined1 *puStack_48;
  
  if (*(int *)(param_1 + 8) == 5) {
    return;
  }
  uStack_68 = 0;
  uStack_60 = 0;
  uStack_70 = 0;
  uVar12 = strlen(param_1 + 0x10);
  if (uVar12 < 0x17) {
    uVar15 = (ulong)&uStack_70 | 1;
    uStack_70 = CONCAT71(uStack_70._1_7_,(char)(uVar12 << 1));
    if (uVar12 != 0) goto code_r0x018df174;
  }
  else {
    uVar13 = uVar12 + 0x10 & 0xfffffffffffffff0;
    if (uVar13 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
    }
    uVar15 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar13,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
    if (uVar15 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    }
    uStack_70 = uVar13 | 1;
    uStack_68 = uVar12;
    uStack_60 = uVar15;
code_r0x018df174:
    memcpy(uVar15,param_1 + 0x10,uVar12);
  }
  *(undefined1 *)(uVar15 + uVar12) = 0;
  cVar3 = *(char *)(param_1 + 0x110);
  BAS::GetDownloadPath()(&uStack_58);
  if ((uStack_58 & 1) == 0) {
    uVar13 = 0x16;
    uVar12 = uStack_58 & 0xff;
  }
  else {
    uVar13 = (uStack_58 & 0xfffffffffffffffe) - 1;
    uVar12 = uStack_58;
  }
  uVar15 = (ulong)(((uint)uVar12 & 0xfe) >> 1);
  if ((uVar12 & 1) != 0) {
    uVar15 = uStack_50;
  }
  if (uVar13 == uVar15) {
    string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&uStack_58,uVar13,1,uVar13,uVar13,0,1,&UNK_029c5d3e/*"/"*/);
  }
  else {
    puVar16 = (undefined1 *)((ulong)&uStack_58 | 1);
    if ((uVar12 & 1) != 0) {
      puVar16 = puStack_48;
    }
    *(undefined1 *)((long)puVar16 + uVar15) = 0x2f;
    uVar15 = uVar15 + 1;
    uVar12 = uVar15;
    if ((uStack_58 & 1) == 0) {
      uStack_58 = CONCAT71(uStack_58._1_7_,(char)uVar15 * '\x02');
      uVar12 = uStack_50;
    }
    uStack_50 = uVar12;
    *(undefined1 *)((long)puVar16 + uVar15) = 0;
  }
  puVar5 = PTR__ZN9Framework10TSingletonI20CGameResourceManagerE11m_pInstanceE_02cc2018;
  uStack_80 = (ulong)puStack_48;
  uStack_88 = uStack_50;
  uStack_90 = uStack_58;
  lVar14 = *(long *)PTR__ZN9Framework10TSingletonI20CGameResourceManagerE11m_pInstanceE_02cc2018;
  if (lVar14 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar14 = *(long *)puVar5;
  }
  lVar14 = *(long *)(lVar14 + 0x20);
  if ((*(byte *)(lVar14 + 0x220) & 1) == 0) {
    lVar14 = lVar14 + 0x221;
  }
  else {
    lVar14 = *(long *)(lVar14 + 0x230);
  }
  uStack_50 = 0;
  puStack_48 = (undefined1 *)0x0;
  uStack_58 = 0;
  uVar12 = strlen(lVar14);
  if (uVar12 < 0x17) {
    puVar16 = (undefined1 *)((ulong)&uStack_58 | 1);
    uStack_58 = CONCAT71(uStack_58._1_7_,(char)(uVar12 << 1));
    if (uVar12 != 0) goto code_r0x018df3ac;
    *puVar16 = 0;
    if (cVar3 == '\0') goto code_r0x018df3c4;
code_r0x018df2c0:
    uStack_b8 = 0;
    bStack_b0 = 0x12;
    uStack_a5 = 0;
    uStack_a0 = 0;
    uStack_c8 = 0x2f72657473616d0e;
    uStack_af = (undefined7)_UNK_027db25d;
    cStack_a8 = (char)((ulong)_UNK_027db25d >> 0x38);
    uStack_a7 = 0x2f;
    uStack_c0 = 0;
    Framework::CSTLStringUtility_Base<string >::ReplaceSelf(string&, string const&, string const&, bool*)(&uStack_58,&bStack_b0,&uStack_c8,0);
    if ((uStack_c8 & 1) != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_b8);
    }
    if ((bStack_b0 & 1) != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_a0);
    }
  }
  else {
    uVar13 = uVar12 + 0x10 & 0xfffffffffffffff0;
    if (uVar13 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
    }
    puVar16 = (undefined1 *)Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar13,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
    if (puVar16 == (undefined1 *)0x0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    }
    uStack_58 = uVar13 | 1;
    uStack_50 = uVar12;
    puStack_48 = puVar16;
code_r0x018df3ac:
    memcpy(puVar16,lVar14,uVar12);
    puVar16[uVar12] = 0;
    if (cVar3 != '\0') goto code_r0x018df2c0;
code_r0x018df3c4:
    if ((uStack_58 & 1) == 0) {
      lVar14 = 0x16;
      uVar12 = uStack_58 & 0xff;
    }
    else {
      lVar14 = (uStack_58 & 0xfffffffffffffffe) - 1;
      uVar12 = uStack_58;
    }
    uVar13 = (ulong)(((uint)uVar12 & 0xfe) >> 1);
    if ((uVar12 & 1) != 0) {
      uVar13 = uStack_50;
    }
    if (lVar14 - uVar13 < 8) {
      string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&uStack_58,lVar14,(8 - lVar14) + uVar13,uVar13,uVar13,0,8,&UNK_02866bf6/*"Android/"*/);
    }
    else {
      puVar16 = (undefined1 *)((ulong)&uStack_58 | 1);
      if ((uVar12 & 1) != 0) {
        puVar16 = puStack_48;
      }
      *(undefined8 *)(puVar16 + uVar13) = 0x2f64696f72646e41;
      uVar13 = uVar13 + 8;
      uVar12 = uVar13;
      if ((uStack_58 & 1) == 0) {
        uStack_58 = CONCAT71(uStack_58._1_7_,(char)uVar13 * '\x02');
        uVar12 = uStack_50;
      }
      uStack_50 = uVar12;
      puVar16[uVar13] = 0;
    }
  }
  uVar13 = (ulong)&uStack_70 | 1;
  uVar12 = uStack_70 >> 1 & 0x7f;
  uVar15 = uVar13;
  if ((uStack_70 & 1) != 0) {
    uVar12 = uStack_68;
    uVar15 = uStack_60;
  }
  if ((uStack_58 & 1) == 0) {
    lVar14 = 0x16;
    uVar18 = uStack_58 & 0xff;
  }
  else {
    lVar14 = (uStack_58 & 0xfffffffffffffffe) - 1;
    uVar18 = uStack_58;
  }
  uVar17 = (ulong)(((uint)uVar18 & 0xfe) >> 1);
  if ((uVar18 & 1) != 0) {
    uVar17 = uStack_50;
  }
  if (lVar14 - uVar17 < uVar12) {
    string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&uStack_58,lVar14,(uVar12 - lVar14) + uVar17,uVar17,uVar17,0,uVar12);
  }
  else if (uVar12 != 0) {
    puVar16 = (undefined1 *)((ulong)&uStack_58 | 1);
    if ((uVar18 & 1) != 0) {
      puVar16 = puStack_48;
    }
    memcpy(puVar16 + uVar17,uVar15,uVar12);
    uVar17 = uVar17 + uVar12;
    uVar12 = uVar17;
    if ((uStack_58 & 1) == 0) {
      uStack_58 = CONCAT71(uStack_58._1_7_,(char)uVar17 * '\x02');
      uVar12 = uStack_50;
    }
    uStack_50 = uVar12;
    puVar16[uVar17] = 0;
  }
  uVar15 = uStack_80;
  uVar12 = uStack_88;
  cStack_a8 = '\0';
  cVar3 = cStack_a8;
  uStack_a7 = 0;
  uVar7 = uStack_a7;
  uStack_a5 = 0;
  uVar9 = uStack_a5;
  uStack_a0 = 0;
  bStack_b0 = 0;
  uStack_af = 0;
  cStack_a8 = (char)uStack_88;
  cVar6 = cStack_a8;
  uStack_a7 = (undefined2)(uStack_88 >> 8);
  uVar8 = uStack_a7;
  uStack_a5 = (undefined5)(uStack_88 >> 0x18);
  uVar10 = uStack_a5;
  if ((uStack_90 & 1) == 0) {
    uStack_a0 = uStack_80;
    uStack_af = (undefined7)(uStack_90 >> 8);
    bStack_b0 = (byte)uStack_90;
  }
  else {
    cStack_a8 = cVar3;
    uStack_a7 = uVar7;
    uStack_a5 = uVar9;
    if (uStack_88 < 0x17) {
      uVar17 = (ulong)&bStack_b0 | 1;
      bStack_b0 = (byte)(uStack_88 << 1);
      if (uStack_88 != 0) goto code_r0x018df5e8;
    }
    else {
      uVar18 = uStack_88 + 0x10 & 0xfffffffffffffff0;
      if (uVar18 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
      }
      uVar17 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar18,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
      if (uVar17 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
      }
      bStack_b0 = (byte)uVar18 | 1;
      uStack_af = (undefined7)(uVar18 >> 8);
      cStack_a8 = cVar6;
      uStack_a7 = uVar8;
      uStack_a5 = uVar10;
      uStack_a0 = uVar17;
code_r0x018df5e8:
      memcpy(uVar17,uVar15,uVar12);
    }
    *(undefined1 *)(uVar17 + uVar12) = 0;
  }
  uVar12 = uVar13;
  uVar15 = uStack_70 >> 1 & 0x7f;
  if ((uStack_70 & 1) != 0) {
    uVar12 = uStack_60;
    uVar15 = uStack_68;
  }
  if (0 < (long)uVar15) {
    lVar14 = 0;
    do {
      if (uVar15 + lVar14 == 0) goto code_r0x018df848;
      lVar1 = uVar12 + uVar15 + lVar14;
      lVar14 = lVar14 + -1;
    } while (*(char *)(lVar1 + -1) != '/');
    if ((lVar14 != 0) && (uVar18 = uVar15 + lVar14, uVar18 != 0xffffffffffffffff)) {
      if (uVar18 <= uVar15) {
        uVar15 = uVar18;
      }
      uStack_c0 = 0;
      uStack_b8 = 0;
      uStack_c8 = 0;
      if (uVar15 < 0x17) {
        uVar17 = (ulong)&uStack_c8 | 1;
        uStack_c8 = (uVar15 & 0x7f) << 1;
        uVar18 = uVar17;
        if (uVar15 != 0) goto code_r0x018df6f8;
      }
      else {
        uVar18 = uVar15 + 0x10 & 0xfffffffffffffff0;
        if (uVar18 == 0) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
        }
        uVar17 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar18,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
        if (uVar17 == 0) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
        }
        uStack_c8 = uVar18 | 1;
        uVar18 = (ulong)&uStack_c8 | 1;
        uStack_c0 = uVar15;
        uStack_b8 = uVar17;
code_r0x018df6f8:
        memcpy(uVar17,uVar12,uVar15);
      }
      *(undefined1 *)(uVar17 + uVar15) = 0;
      uVar15 = (ulong)bStack_b0;
      uVar12 = uStack_c8 >> 1 & 0x7f;
      if ((uStack_c8 & 1) != 0) {
        uVar12 = uStack_c0;
        uVar18 = uStack_b8;
      }
      if ((bStack_b0 & 1) == 0) {
        lVar14 = 0x16;
      }
      else {
        uVar15 = CONCAT71(uStack_af,bStack_b0);
        lVar14 = (uVar15 & 0xfffffffffffffffe) - 1;
      }
      uVar17 = (ulong)(((uint)uVar15 & 0xfe) >> 1);
      if ((uVar15 & 1) != 0) {
        uVar17 = CONCAT53(uStack_a5,CONCAT21(uStack_a7,cStack_a8));
      }
      if (lVar14 - uVar17 < uVar12) {
        string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&bStack_b0,lVar14,(uVar12 - lVar14) + uVar17,uVar17,uVar17,0,uVar12);
        uVar12 = (ulong)bStack_b0;
        if ((bStack_b0 & 1) != 0) goto code_r0x018df788;
code_r0x018df7f4:
        uVar15 = 0x16;
      }
      else {
        if (uVar12 != 0) {
          uVar2 = (ulong)&bStack_b0 | 1;
          if ((uVar15 & 1) != 0) {
            uVar2 = uStack_a0;
          }
          memcpy(uVar2 + uVar17,uVar18,uVar12);
          lVar14 = uVar17 + uVar12;
          if ((bStack_b0 & 1) == 0) {
            bStack_b0 = (char)lVar14 * '\x02';
            *(undefined1 *)(uVar2 + lVar14) = 0;
            uVar12 = (ulong)bStack_b0;
            goto code_r0x018df7f4;
          }
          uStack_a7 = (undefined2)((ulong)lVar14 >> 8);
          uStack_a5 = (undefined5)((ulong)lVar14 >> 0x18);
          *(undefined1 *)(uVar2 + lVar14) = 0;
          cStack_a8 = (char)lVar14;
        }
        uVar12 = (ulong)bStack_b0;
        if ((bStack_b0 & 1) == 0) goto code_r0x018df7f4;
code_r0x018df788:
        uVar12 = CONCAT71(uStack_af,bStack_b0);
        uVar15 = (uVar12 & 0xfffffffffffffffe) - 1;
      }
      uVar18 = (ulong)(((uint)uVar12 & 0xfe) >> 1);
      if ((uVar12 & 1) != 0) {
        uVar18 = CONCAT53(uStack_a5,CONCAT21(uStack_a7,cStack_a8));
      }
      if (uVar15 == uVar18) {
        string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&bStack_b0,uVar15,1,uVar15,uVar15,0,1,&UNK_029c5d3e/*"/"*/);
      }
      else {
        uVar15 = (ulong)&bStack_b0 | 1;
        if ((uVar12 & 1) != 0) {
          uVar15 = uStack_a0;
        }
        *(undefined1 *)(uVar15 + uVar18) = 0x2f;
        lVar14 = uVar18 + 1;
        if ((bStack_b0 & 1) == 0) {
          bStack_b0 = (char)lVar14 * '\x02';
        }
        else {
          uStack_a7 = (undefined2)((ulong)lVar14 >> 8);
          uStack_a5 = (undefined5)((ulong)lVar14 >> 0x18);
          cStack_a8 = (char)lVar14;
        }
        *(undefined1 *)(uVar15 + lVar14) = 0;
      }
      if ((uStack_c8 & 1) != 0) {
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_b8);
      }
    }
  }
code_r0x018df848:
  if ((bStack_b0 & 1) == 0) {
    uVar12 = (ulong)&bStack_b0 | 1;
code_r0x018df864:
    iVar11 = access(uVar12,0);
    uVar12 = uStack_a0;
    if (iVar11 == 0) goto code_r0x018df8a8;
  }
  else {
    uVar12 = uStack_a0;
    if (uStack_a0 != 0) goto code_r0x018df864;
    uVar12 = 0;
  }
  uVar15 = (ulong)&bStack_b0 | 1;
  if ((bStack_b0 & 1) != 0) {
    uVar15 = uVar12;
  }
  Aska::File::CreateDirectory(char const*)(uVar15);
  uVar12 = (ulong)&bStack_b0 | 1;
  if ((bStack_b0 & 1) != 0) {
    uVar12 = uStack_a0;
  }
  BAS::SetNoBackupFolder(char const*)(uVar12);
code_r0x018df8a8:
  puVar5 = PTR__ZN23CGameResourceDownloader13CDownloadNode23m_GlobalDownloadCounterE_02cc0968;
  iVar11 = *(int *)
            PTR__ZN23CGameResourceDownloader13CDownloadNode23m_GlobalDownloadCounterE_02cc0968;
  if (iVar11 == 0) {
    iVar11 = 1;
    *(undefined4 *)
     PTR__ZN23CGameResourceDownloader13CDownloadNode23m_GlobalDownloadCounterE_02cc0968 = 1;
  }
  puVar4 = PTR__ZN4Aska6Global17m_pNetworkManagerE_02cb9e90;
  *(int *)puVar5 = iVar11 + 1;
  *(int *)(param_1 + 0x368) = iVar11;
  *(undefined8 *)(param_1 + 8) = 2;
  puVar16 = (undefined1 *)((ulong)&uStack_58 | 1);
  if ((uStack_58 & 1) != 0) {
    puVar16 = puStack_48;
  }
  if ((uStack_70 & 1) != 0) {
    uVar13 = uStack_60;
  }
  uVar12 = (ulong)&uStack_90 | 1;
  if ((uStack_90 & 1) != 0) {
    uVar12 = uStack_80;
  }
  Aska::Yayoi::Downloader::Download(unsigned int, char const*, Aska::INotify*, char const*, char const*, Aska::Yayoi::Downloader::UriParam const*, unsigned long, Aska::Yayoi::Downloader::IDownloadStream*)(&uStack_c8,*(undefined8 *)(*(long *)puVar4 + 0x1a8),iVar11,puVar16,param_1,uVar13,
                  uVar12,0,0,param_1 + 0x1a0);
  if ((long)uStack_c8 < 0) {
    *(ulong *)(param_1 + 0x188) = uStack_c8;
    *(undefined8 *)(param_1 + 8) = 6;
  }
  if ((bStack_b0 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_a0);
  }
  if ((uStack_58 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puStack_48);
  }
  if ((uStack_90 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_80);
  }
  if ((uStack_70 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_60);
  }
  return;
}

// ==== CGameResourceDownloader::CDownloadNode::DownloadCompleteCalc()
// vaddr 0x17dfa18 | ghidra 0x18dfa18 | size 932 | symbol _ZN23CGameResourceDownloader13CDownloadNode20DownloadCompleteCalcEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN23CGameResourceDownloader13CDownloadNode20DownloadCompleteCalcEv(long param_1)

{
  ulong *puVar1;
  undefined *puVar2;
  int iVar3;
  ulong uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  long lVar7;
  long lVar8;
  ulong uVar9;
  long lVar10;
  ulong uVar11;
  long lVar12;
  byte abStack_118 [16];
  ulong uStack_108;
  ulong uStack_100;
  ulong uStack_f8;
  ulong uStack_f0;
  long alStack_e8 [3];
  ulong uStack_d0;
  ulong uStack_c8;
  ulong uStack_c0;
  undefined4 uStack_a0;
  undefined4 uStack_78;
  
  puVar2 = PTR__ZN9Framework10TSingletonI20CGameResourceManagerE11m_pInstanceE_02cc2018;
  lVar7 = *(long *)PTR__ZN9Framework10TSingletonI20CGameResourceManagerE11m_pInstanceE_02cc2018;
  if (lVar7 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar7 = *(long *)puVar2;
  }
  lVar12 = *(long *)(lVar7 + 0x20);
  lVar7 = param_1 + 0x10;
  lVar8 = *(long *)(lVar12 + 0x5d8);
  uStack_c8 = 0;
  uStack_c0 = 0;
  uStack_d0 = 0;
  uVar4 = strlen(lVar7);
  if (uVar4 < 0x17) {
    uVar11 = (ulong)&uStack_d0 | 1;
    uStack_d0 = CONCAT71(uStack_d0._1_7_,(char)(uVar4 << 1));
    if (uVar4 != 0) goto code_r0x018dfb08;
  }
  else {
    uVar9 = uVar4 + 0x10 & 0xfffffffffffffff0;
    if (uVar9 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
    }
    uVar11 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar9,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
    if (uVar11 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    }
    uStack_d0 = uVar9 | 1;
    uStack_c8 = uVar4;
    uStack_c0 = uVar11;
code_r0x018dfb08:
    memcpy(uVar11,lVar7,uVar4);
  }
  *(undefined1 *)(uVar11 + uVar4) = 0;
  Aska::THashMap<string, CAssetInfo, Hasher_CSTLString, Aska::TEqualTo<string >, Aska::TAllocator<Aska::TPair<string const, CAssetInfo> > >::Find_(string const&) const(alStack_e8,lVar8 + 0x58,&uStack_d0);
  if ((uStack_d0 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_c0);
  }
  puVar1 = (ulong *)(alStack_e8[0] + 0x30);
  if (puVar1 != (ulong *)(param_1 + 0x160)) {
    uVar4 = *(ulong *)(param_1 + 0x168);
    lVar8 = *(long *)(param_1 + 0x170);
    uVar9 = (ulong)*(byte *)puVar1;
    if ((*(byte *)(param_1 + 0x160) & 1) == 0) {
      lVar8 = param_1 + 0x161;
      uVar4 = (ulong)(*(byte *)(param_1 + 0x160) >> 1);
    }
    if ((*(byte *)puVar1 & 1) == 0) {
      uVar11 = 0x16;
      lVar10 = uVar4 - 0x16;
      if (0x15 < uVar4 && lVar10 != 0) {
code_r0x018dfba0:
        if ((uVar9 & 1) == 0) {
          uVar9 = (ulong)(((uint)uVar9 & 0xfe) >> 1);
        }
        else {
          uVar9 = *(ulong *)(alStack_e8[0] + 0x38);
        }
        string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(puVar1,uVar11,lVar10,uVar9,0,uVar9,uVar4);
        goto code_r0x018dfc00;
      }
    }
    else {
      uVar9 = *puVar1;
      uVar11 = (uVar9 & 0xfffffffffffffffe) - 1;
      lVar10 = uVar4 - uVar11;
      if (uVar11 <= uVar4 && lVar10 != 0) goto code_r0x018dfba0;
    }
    if ((uVar9 & 1) == 0) {
      lVar10 = alStack_e8[0] + 0x31;
    }
    else {
      lVar10 = *(long *)(alStack_e8[0] + 0x40);
    }
    if (uVar4 != 0) {
      memmove(lVar10,lVar8,uVar4);
    }
    *(undefined1 *)(lVar10 + uVar4) = 0;
    if ((*(byte *)puVar1 & 1) == 0) {
      *(byte *)puVar1 = (byte)(uVar4 << 1);
    }
    else {
      *(ulong *)(alStack_e8[0] + 0x38) = uVar4;
    }
  }
code_r0x018dfc00:
  BAS::GetDownloadPath()(&uStack_d0);
  if ((uStack_d0 & 1) == 0) {
    uVar9 = 0x16;
    uVar4 = uStack_d0 & 0xff;
  }
  else {
    uVar9 = (uStack_d0 & 0xfffffffffffffffe) - 1;
    uVar4 = uStack_d0;
  }
  uVar11 = (ulong)(((uint)uVar4 & 0xfe) >> 1);
  if ((uVar4 & 1) != 0) {
    uVar11 = uStack_c8;
  }
  if (uVar9 == uVar11) {
    string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&uStack_d0,uVar9,1,uVar9,uVar9,0,1,&UNK_029c5d3e/*"/"*/);
  }
  else {
    uVar9 = (ulong)&uStack_d0 | 1;
    if ((uVar4 & 1) != 0) {
      uVar9 = uStack_c0;
    }
    *(undefined1 *)(uVar9 + uVar11) = 0x2f;
    uVar11 = uVar11 + 1;
    uVar4 = uVar11;
    if ((uStack_d0 & 1) == 0) {
      uStack_d0 = CONCAT71(uStack_d0._1_7_,(char)uVar11 * '\x02');
      uVar4 = uStack_c8;
    }
    uStack_c8 = uVar4;
    *(undefined1 *)(uVar9 + uVar11) = 0;
  }
  uStack_f0 = uStack_c0;
  uStack_f8 = uStack_c8;
  uStack_100 = uStack_d0;
  string std::__ndk1::operator+<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> >(string const&, char const*)(abStack_118,&uStack_100,lVar7);
  if ((abStack_118[0] & 1) == 0) {
    uVar4 = (ulong)abStack_118 | 1;
  }
  else {
    uVar4 = uStack_108;
    if (uStack_108 == 0) {
      uVar6 = 0;
      uVar5 = 0;
      goto code_r0x018dfd18;
    }
  }
  iVar3 = access(uVar4,0);
  uVar6 = 0;
  uVar5 = 0;
  if (iVar3 == 0) {
    stat(uVar4,&uStack_d0);
    uVar6 = uStack_78;
    uVar5 = uStack_a0;
  }
code_r0x018dfd18:
  *(undefined4 *)(alStack_e8[0] + 0x48) = uVar5;
  *(undefined4 *)(alStack_e8[0] + 0x4c) = uVar6;
  if ((*(byte *)(param_1 + 0x160) & 1) == 0) {
    lVar8 = param_1 + 0x161;
  }
  else {
    lVar8 = *(long *)(param_1 + 0x170);
  }
  if ((*(byte *)(alStack_e8[0] + 0x60) & 1) == 0) {
    lVar10 = alStack_e8[0] + 0x61;
    lVar12 = *(long *)(lVar12 + 0x480);
  }
  else {
    lVar10 = *(long *)(alStack_e8[0] + 0x70);
    lVar12 = *(long *)(lVar12 + 0x480);
  }
  if (lVar12 != 0) {
    CGameResourceDownloader::CJournalFileWriter::AddWriteInfo(char const*, char const*, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, CMetaList*, char const*)(lVar12,lVar7,lVar8,uVar5,uVar6,*(undefined4 *)(alStack_e8[0] + 0x50),
                    *(undefined4 *)(alStack_e8[0] + 0x54),*(undefined4 *)(alStack_e8[0] + 0x58),
                    alStack_e8[0] + 0x78,lVar10);
  }
  CGameResourceDownloader::CDownloadNode::Callback(char const*, CGameResourceDownloader::iErrorCode)(param_1,lVar7,0);
  if ((abStack_118[0] & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_108);
  }
  if ((uStack_100 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_f0);
  }
  return;
}

// ==== CGameResourceDownloader::CDownloadNode::UnpackChildData()
// vaddr 0x17dfdbc | ghidra 0x18dfdbc | size 4436 | symbol _ZN23CGameResourceDownloader13CDownloadNode15UnpackChildDataEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN23CGameResourceDownloader13CDownloadNode15UnpackChildDataEv(long param_1)

{
  uint uVar1;
  undefined4 *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined *puVar5;
  uint uVar6;
  char cVar7;
  bool bVar8;
  long *plVar9;
  undefined *puVar10;
  int iVar11;
  int iVar12;
  ulong uVar13;
  ulong uVar14;
  long *plVar15;
  ulong *puVar16;
  undefined4 *puVar17;
  undefined4 *puVar18;
  ulong uVar19;
  ulong uVar20;
  undefined4 uVar21;
  ulong uVar22;
  code *pcVar23;
  undefined4 *puVar24;
  undefined4 *puVar25;
  ulong uVar26;
  ulong uVar27;
  long lVar28;
  long lVar29;
  int *piVar30;
  long lVar31;
  undefined4 *puVar32;
  undefined4 *puVar33;
  ulong *puVar34;
  long lVar35;
  ulong uVar36;
  uint uVar37;
  undefined4 *puVar38;
  ulong uStack_c8;
  ulong uStack_c0;
  undefined4 *puStack_b8;
  ulong uStack_b0;
  ulong uStack_a8;
  undefined4 *puStack_a0;
  ulong uStack_98;
  ulong uStack_90;
  undefined4 *puStack_88;
  undefined8 uStack_80;
  ulong uStack_78;
  undefined4 *puStack_70;
  undefined4 uStack_68;
  undefined2 uStack_64;
  undefined1 uStack_62;
  
  puVar10 = PTR__ZN9Framework10TSingletonI20CGameResourceManagerE11m_pInstanceE_02cc2018;
  puVar4 = PTR__ZN23CGameResourceDownloader13CDownloadNode12UnpackNotify15m_DispatchCountE_02cbe960;
  puVar3 = PTR__ZN4Aska6Global20m_pMessageDispatcherE_02cb77c8;
  puVar5 = PTR__ZTVN4Aska4FileE_02cb6e28;
  iVar11 = *(int *)(param_1 + 0xc);
  if (iVar11 != 0) {
    if (iVar11 != 2) {
      if (iVar11 != 1) {
        return;
      }
      if (*(int *)(param_1 + 400) == 0) {
        piVar30 = *(int **)(param_1 + 0x360);
      }
      else {
        uVar37 = 0;
        uVar22 = 0;
        do {
          lVar31 = *(long *)(param_1 + 0x198);
          lVar28 = lVar31 + uVar22 * 0x140;
          iVar11 = *(int *)(lVar28 + 0x118);
          if (iVar11 == 2) {
            uVar37 = uVar37 + 1;
          }
          else if ((iVar11 == 0) && (DataMemoryBarrier(2,3), *(int *)puVar4 < 5)) {
            lVar35 = *(long *)puVar3;
            puVar2 = (undefined4 *)(lVar28 + 0x118);
            if (lVar35 == 0) {
              Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02866a48/*"C:\BAS_Submission\Client\Project\..\Source\Game\Resource\GameResourceDownloader.cpp"*/,0x1074,&UNK_02866c07/*"dispatcher is null."*/);
            }
            *puVar2 = 1;
            do {
              cVar7 = '\x01';
              bVar8 = (bool)ExclusiveMonitorPass(puVar4,0x10);
              if (bVar8) {
                *(int *)puVar4 = *(int *)puVar4 + 1;
                cVar7 = ExclusiveMonitorsStatus();
              }
            } while (cVar7 != '\0');
            if (5 < *(int *)puVar4) {
              Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02866a48/*"C:\BAS_Submission\Client\Project\..\Source\Game\Resource\GameResourceDownloader.cpp"*/,0x1222,&UNK_02866c4f/*"IncDispatchCount too many call?"*/);
            }
            uVar13 = Aska::SimpleMessageDispatcher::PostMessage(unsigned short, Aska::INotify*, void*, void*, unsigned int*, signed char)(lVar35,0x4c9,lVar31 + uVar22 * 0x140,0,0,0,0);
            if ((uVar13 & 1) == 0) {
              *puVar2 = 0;
              do {
                cVar7 = '\x01';
                bVar8 = (bool)ExclusiveMonitorPass(puVar4,0x10);
                if (bVar8) {
                  *(int *)puVar4 = *(int *)puVar4 + -1;
                  cVar7 = ExclusiveMonitorsStatus();
                }
              } while (cVar7 != '\0');
              if (*(int *)puVar4 < 0) {
                Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02866a48/*"C:\BAS_Submission\Client\Project\..\Source\Game\Resource\GameResourceDownloader.cpp"*/,0x1228,&UNK_02866c6f/*"SubDispatchCount too many call?"*/);
              }
            }
          }
          puVar5 = PTR__ZN9Framework10TSingletonI20CGameResourceManagerE11m_pInstanceE_02cc2018;
          uVar6 = *(uint *)(param_1 + 400);
          uVar1 = (int)uVar22 + 1;
          uVar22 = (ulong)uVar1;
        } while (uVar1 < uVar6);
        if (uVar37 != uVar6) {
          return;
        }
        piVar30 = *(int **)(param_1 + 0x360);
        if (uVar6 != 0) {
          uVar22 = 0;
          do {
            lVar28 = *(long *)(*(long *)(param_1 + 0x198) + uVar22 * 0x140 + 0x138);
            if (lVar28 != 0) {
              lVar31 = *(long *)puVar5;
              if (lVar31 == 0) {
                Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
                lVar31 = *(long *)puVar5;
              }
              lVar31 = *(long *)(lVar31 + 0x20);
              if ((*piVar30 != 0x46534900) || (0x20130304 < (uint)piVar30[1])) {
                Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02866e51/*"C:\BAS_Submission\Client\Project\../Library/Framework/Tools\MakeFileStream/FileStream_Image.h"*/,0xdc,&UNK_02866eaf/*"Illegal instance."*/);
              }
              if ((uint)piVar30[2] <= (uint)uVar22) {
                Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02866e51/*"C:\BAS_Submission\Client\Project\../Library/Framework/Tools\MakeFileStream/FileStream_Image.h"*/,0xdd,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,uVar22);
              }
              if ((*(byte *)(lVar28 + 0x10) & 1) == 0) {
                lVar35 = lVar28 + 0x11;
              }
              else {
                lVar35 = *(long *)(lVar28 + 0x20);
              }
              if ((*(byte *)(lVar28 + 0x40) & 1) == 0) {
                lVar29 = lVar28 + 0x41;
                lVar31 = *(long *)(lVar31 + 0x480);
              }
              else {
                lVar29 = *(long *)(lVar28 + 0x50);
                lVar31 = *(long *)(lVar31 + 0x480);
              }
              if (lVar31 != 0) {
                CGameResourceDownloader::CJournalFileWriter::AddWriteInfo(char const*, char const*, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, CMetaList*, char const*)(lVar31,(ulong)(uint)piVar30[uVar22 * 4 + 4] + (long)piVar30,lVar35,
                                *(undefined4 *)(lVar28 + 0x28),*(undefined4 *)(lVar28 + 0x2c),
                                *(undefined4 *)(lVar28 + 0x30),*(undefined4 *)(lVar28 + 0x34),
                                *(undefined4 *)(lVar28 + 0x38),lVar28 + 0x58,lVar29);
              }
            }
            uVar37 = (uint)uVar22 + 1;
            uVar22 = (ulong)uVar37;
          } while (uVar37 < *(uint *)(param_1 + 400));
          piVar30 = *(int **)(param_1 + 0x360);
        }
      }
      if (piVar30 != (int *)0x0) {
        operator delete[](void*)(piVar30);
        *(undefined8 *)(param_1 + 0x360) = 0;
      }
      *(int *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) + 1;
      return;
    }
    lVar28 = *(long *)(param_1 + 0x198);
    if (lVar28 != 0) {
      lVar31 = *(long *)(lVar28 + -8);
      if (lVar31 != 0) {
        lVar31 = lVar31 * 0x140;
        puVar3 = PTR__ZTVN23CGameResourceDownloader13CDownloadNode12UnpackNotifyE_02cc1100 + 0x10;
        puVar4 = PTR__ZTVN4Aska4FileE_02cb6e28 + 0x10;
        do {
          while( true ) {
            lVar35 = lVar28 + lVar31;
            *(undefined **)(lVar35 + -0x140) = puVar3;
            if (*(long *)(lVar35 + -0x10) == 0) break;
            Aska::File::Close()(lVar35 + -0x20);
            *(undefined **)(lVar35 + -0x20) = puVar5 + 0x10;
            if (*(long *)(lVar35 + -0x10) != 0) {
              Aska::File::Close()(lVar35 + -0x20);
            }
            lVar31 = lVar31 + -0x140;
            if (lVar31 == 0) goto code_r0x018e014c;
          }
          *(undefined **)(lVar35 + -0x20) = puVar4;
          lVar31 = lVar31 + -0x140;
        } while (lVar31 != 0);
      }
code_r0x018e014c:
      operator delete[](void*)((long *)(lVar28 + -8));
      *(undefined8 *)(param_1 + 0x198) = 0;
    }
    BAS::GetDownloadPath()(&uStack_98);
    if ((uStack_98 & 1) == 0) {
      uVar13 = 0x16;
      uVar22 = uStack_98 & 0xff;
    }
    else {
      uVar13 = (uStack_98 & 0xfffffffffffffffe) - 1;
      uVar22 = uStack_98;
    }
    uVar14 = (ulong)(((uint)uVar22 & 0xfe) >> 1);
    if ((uVar22 & 1) != 0) {
      uVar14 = uStack_90;
    }
    if (uVar13 == uVar14) {
      string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&uStack_98,uVar13,1,uVar13,uVar13,0,1,&UNK_029c5d3e/*"/"*/);
    }
    else {
      puVar2 = (undefined4 *)((ulong)&uStack_98 | 1);
      if ((uVar22 & 1) != 0) {
        puVar2 = puStack_88;
      }
      *(undefined1 *)((long)puVar2 + uVar14) = 0x2f;
      uVar14 = uVar14 + 1;
      uVar22 = uVar14;
      if ((uStack_98 & 1) == 0) {
        uStack_98 = CONCAT71(uStack_98._1_7_,(char)uVar14 * '\x02');
        uVar22 = uStack_90;
      }
      uStack_90 = uVar22;
      *(undefined1 *)((long)puVar2 + uVar14) = 0;
    }
    uVar22 = uStack_98;
    lVar28 = param_1 + 0x10;
    uStack_78 = uStack_90;
    uStack_80 = uStack_98;
    uVar13 = uStack_98 & 0xff;
    puStack_70 = puStack_88;
    uVar14 = strlen(lVar28);
    if ((uVar22 & 1) == 0) {
      lVar31 = 0x16;
    }
    else {
      lVar31 = (uStack_80 & 0xfffffffffffffffe) - 1;
      uVar13 = uStack_80;
    }
    uVar22 = (ulong)(((uint)uVar13 & 0xfe) >> 1);
    if ((uVar13 & 1) != 0) {
      uVar22 = uStack_78;
    }
    if (lVar31 - uVar22 < uVar14) {
      string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&uStack_80,lVar31,(uVar14 - lVar31) + uVar22,uVar22,uVar22,0,uVar14,lVar28);
    }
    else if (uVar14 != 0) {
      puVar2 = (undefined4 *)((ulong)&uStack_80 | 1);
      if ((uVar13 & 1) != 0) {
        puVar2 = puStack_70;
      }
      memcpy((long)puVar2 + uVar22,lVar28,uVar14);
      uVar22 = uVar22 + uVar14;
      uVar13 = uVar22;
      if ((uStack_80 & 1) == 0) {
        uStack_80 = CONCAT71(uStack_80._1_7_,(char)uVar22 * '\x02');
        uVar13 = uStack_78;
      }
      uStack_78 = uVar13;
      *(undefined1 *)((long)puVar2 + uVar22) = 0;
    }
    puVar2 = (undefined4 *)((ulong)&uStack_80 | 1);
    if ((uStack_80 & 1) != 0) {
      puVar2 = puStack_70;
    }
    Aska::File::DeleteFile(char const*)(puVar2);
    CGameResourceDownloader::CDownloadNode::AllCallback()(param_1);
    if (*(long *)(param_1 + 0x390) != 0) {
      plVar9 = (long *)*(long *)(param_1 + 0x388);
      while (plVar9 != (long *)0x0) {
        plVar15 = (long *)plVar9[0x28];
        lVar28 = *plVar9;
        if (plVar9 + 0x24 == plVar15) {
          pcVar23 = *(code **)(*plVar15 + 0x20);
code_r0x018e03fc:
          (*pcVar23)();
        }
        else if (plVar15 != (long *)0x0) {
          pcVar23 = *(code **)(*plVar15 + 0x28);
          goto code_r0x018e03fc;
        }
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar9);
        plVar9 = (long *)lVar28;
      }
      lVar28 = *(long *)(param_1 + 0x380);
      *(undefined8 *)(param_1 + 0x388) = 0;
      if (lVar28 != 0) {
        lVar31 = 0;
        do {
          *(undefined8 *)(*(long *)(param_1 + 0x378) + lVar31 * 8) = 0;
          lVar31 = lVar31 + 1;
        } while (lVar28 != lVar31);
      }
      *(undefined8 *)(param_1 + 0x390) = 0;
    }
    *(undefined8 *)(param_1 + 8) = 5;
    puVar2 = puStack_70;
    uVar22 = uStack_80;
    goto joined_r0x018e0ee4;
  }
  lVar28 = *(long *)PTR__ZN9Framework10TSingletonI20CGameResourceManagerE11m_pInstanceE_02cc2018;
  if (lVar28 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar28 = *(long *)puVar10;
  }
  piVar30 = *(int **)(param_1 + 0x360);
  if (*piVar30 != 0x46534900) {
    if (piVar30 != (int *)0x0) {
      operator delete[](void*)(piVar30);
      *(undefined8 *)(param_1 + 0x360) = 0;
    }
    CGameResourceDownloader::CDownloadNode::AllCallback()(param_1);
    *(undefined8 *)(param_1 + 8) = 5;
    return;
  }
  lVar28 = *(long *)(*(long *)(lVar28 + 0x20) + 0x5d8);
  BAS::GetDownloadPath()(&uStack_80);
  if ((uStack_80 & 1) == 0) {
    uVar13 = 0x16;
    uVar22 = uStack_80 & 0xff;
  }
  else {
    uVar13 = (uStack_80 & 0xfffffffffffffffe) - 1;
    uVar22 = uStack_80;
  }
  uVar14 = (ulong)(((uint)uVar22 & 0xfe) >> 1);
  if ((uVar22 & 1) != 0) {
    uVar14 = uStack_78;
  }
  if (uVar13 == uVar14) {
    string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&uStack_80,uVar13,1,uVar13,uVar13,0,1,&UNK_029c5d3e/*"/"*/);
  }
  else {
    puVar2 = (undefined4 *)((ulong)&uStack_80 | 1);
    if ((uVar22 & 1) != 0) {
      puVar2 = puStack_70;
    }
    *(undefined1 *)((long)puVar2 + uVar14) = 0x2f;
    uVar14 = uVar14 + 1;
    uVar22 = uVar14;
    if ((uStack_80 & 1) == 0) {
      uStack_80 = CONCAT71(uStack_80._1_7_,(char)uVar14 * '\x02');
      uVar22 = uStack_78;
    }
    uStack_78 = uVar22;
    *(undefined1 *)((long)puVar2 + uVar14) = 0;
  }
  puVar2 = puStack_70;
  uVar13 = uStack_78;
  uVar22 = uStack_80;
  puVar5 = PTR__ZTVN4Aska4FileE_02cb6e28;
  uStack_64 = uStack_80._5_2_;
  uStack_68 = uStack_80._1_4_;
  uStack_62 = uStack_80._7_1_;
  lVar31 = *(long *)(param_1 + 0x198);
  uVar37 = piVar30[2];
  uVar14 = (ulong)uVar37;
  if (lVar31 != 0) {
    lVar35 = *(long *)(lVar31 + -8);
    if (lVar35 != 0) {
      lVar35 = lVar35 * 0x140;
      puVar3 = PTR__ZTVN23CGameResourceDownloader13CDownloadNode12UnpackNotifyE_02cc1100 + 0x10;
      puVar4 = PTR__ZTVN4Aska4FileE_02cb6e28 + 0x10;
      do {
        while( true ) {
          lVar29 = lVar31 + lVar35;
          *(undefined **)(lVar29 + -0x140) = puVar3;
          if (*(long *)(lVar29 + -0x10) == 0) break;
          Aska::File::Close()(lVar29 + -0x20);
          *(undefined **)(lVar29 + -0x20) = puVar5 + 0x10;
          if (*(long *)(lVar29 + -0x10) != 0) {
            Aska::File::Close()(lVar29 + -0x20);
          }
          lVar35 = lVar35 + -0x140;
          if (lVar35 == 0) goto code_r0x018e050c;
        }
        *(undefined **)(lVar29 + -0x20) = puVar4;
        lVar35 = lVar35 + -0x140;
      } while (lVar35 != 0);
    }
code_r0x018e050c:
    operator delete[](void*)((long *)(lVar31 + -8));
    *(undefined8 *)(param_1 + 0x198) = 0;
  }
  puVar16 = (ulong *)operator new[](unsigned long, std::nothrow_t const&)(uVar14 * 0x140 | 8,PTR__ZSt7nothrow_02cb9a80);
  puVar34 = puVar16;
  if (puVar16 == (ulong *)0x0) {
code_r0x018e058c:
    *(ulong **)(param_1 + 0x198) = puVar34;
    if (uVar37 != 0) {
      puVar38 = (undefined4 *)((ulong)&uStack_80 | 1);
      puVar24 = (undefined4 *)((ulong)&uStack_c8 | 1);
      puVar25 = (undefined4 *)((ulong)&uStack_b0 | 1);
      uVar26 = uVar13 + 0x10 & 0xfffffffffffffff0;
      uVar36 = 0;
      puVar33 = (undefined4 *)((ulong)&uStack_98 | 1);
      do {
        if ((*piVar30 != 0x46534900) || (0x20130304 < (uint)piVar30[1])) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02866e51/*"C:\BAS_Submission\Client\Project\../Library/Framework/Tools\MakeFileStream/FileStream_Image.h"*/,0xdc,&UNK_02866eaf/*"Illegal instance."*/);
        }
        if ((uint)piVar30[2] <= uVar36) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02866e51/*"C:\BAS_Submission\Client\Project\../Library/Framework/Tools\MakeFileStream/FileStream_Image.h"*/,0xdd,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,uVar36 & 0xffffffff);
        }
        uStack_78 = 0;
        puStack_70 = (undefined4 *)0x0;
        uStack_80 = 0;
        lVar31 = (ulong)(uint)piVar30[uVar36 * 4 + 4] + (long)piVar30;
        uVar19 = strlen(lVar31);
        if (uVar19 < 0x17) {
          uStack_80 = CONCAT71(uStack_80._1_7_,(char)(uVar19 << 1));
          puVar18 = puVar38;
          if (uVar19 != 0) goto code_r0x018e0d98;
        }
        else {
          uVar20 = uVar19 + 0x10 & 0xfffffffffffffff0;
          if (uVar20 == 0) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
          }
          puVar18 = (undefined4 *)Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar20,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
          if (puVar18 == (undefined4 *)0x0) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
          }
          uStack_80 = uVar20 | 1;
          uStack_78 = uVar19;
          puStack_70 = puVar18;
code_r0x018e0d98:
          memcpy(puVar18,lVar31,uVar19);
        }
        *(undefined1 *)((long)puVar18 + uVar19) = 0;
        uStack_90 = 0;
        puStack_88 = (undefined4 *)0x0;
        uStack_98 = 0;
        if ((uVar22 & 1) == 0) {
          uStack_98 = uVar22 & 0xff;
          *(undefined1 *)((long)puVar33 + 6) = uStack_62;
          *(undefined2 *)(puVar33 + 1) = uStack_64;
          *puVar33 = uStack_68;
          puStack_88 = puVar2;
          uStack_90 = uVar13;
        }
        else {
          if (uVar13 < 0x17) {
            uStack_98 = (ulong)(byte)((int)uVar13 << 1);
            puVar18 = puVar33;
            uVar19 = uStack_98;
            uVar20 = uStack_90;
            puVar17 = puStack_88;
            if (uVar13 != 0) goto code_r0x018e0e64;
          }
          else {
            if (uVar26 == 0) {
              Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
            }
            puVar18 = (undefined4 *)Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar26,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
            uVar19 = uVar26 | 1;
            uVar20 = uVar13;
            puVar17 = puVar18;
            if (puVar18 == (undefined4 *)0x0) {
              Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
            }
code_r0x018e0e64:
            puStack_88 = puVar17;
            uStack_90 = uVar20;
            uStack_98 = uVar19;
            memcpy(puVar18,puVar2,uVar13);
          }
          *(undefined1 *)((long)puVar18 + uVar13) = 0;
        }
        puVar18 = puVar38;
        uVar19 = uStack_80 >> 1 & 0x7f;
        if ((uStack_80 & 1) != 0) {
          puVar18 = puStack_70;
          uVar19 = uStack_78;
        }
        if (0 < (long)uVar19) {
          lVar35 = 0;
          do {
            if (uVar19 + lVar35 == 0) goto code_r0x018e0898;
            lVar29 = lVar35 + uVar19;
            lVar35 = lVar35 + -1;
          } while (*(char *)((long)puVar18 + lVar29 + -1) != '/');
          if ((lVar35 != 0) && (uVar20 = uVar19 + lVar35, uVar20 != 0xffffffffffffffff)) {
            if (uVar20 <= uVar19) {
              uVar19 = uVar20;
            }
            uStack_c0 = 0;
            puStack_b8 = (undefined4 *)0x0;
            uStack_c8 = 0;
            if (uVar19 < 0x17) {
              uStack_c8 = (uVar19 & 0x7f) << 1;
              puVar17 = puVar24;
              if (uVar19 != 0) goto code_r0x018e06a4;
            }
            else {
              uVar20 = uVar19 + 0x10 & 0xfffffffffffffff0;
              if (uVar20 == 0) {
                Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
              }
              puVar17 = (undefined4 *)Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar20,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
              if (puVar17 == (undefined4 *)0x0) {
                Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
              }
              uStack_c8 = uVar20 | 1;
              uStack_c0 = uVar19;
              puStack_b8 = puVar17;
code_r0x018e06a4:
              memcpy(puVar17,puVar18,uVar19);
            }
            *(undefined1 *)((long)puVar17 + uVar19) = 0;
            uVar19 = uStack_98 >> 1 & 0x7f;
            puVar18 = puVar33;
            if ((uStack_98 & 1) != 0) {
              uVar19 = uStack_90;
              puVar18 = puStack_88;
            }
            if ((uStack_c8 & 1) == 0) {
              lVar35 = 0x16;
              uVar27 = uStack_c8 & 0xff;
              uVar20 = uStack_c8 >> 1 & 0x7f;
            }
            else {
              lVar35 = (uStack_c8 & 0xfffffffffffffffe) - 1;
              uVar27 = uStack_c8;
              uVar20 = uStack_c0;
            }
            if (lVar35 - uVar20 < uVar19) {
              string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&uStack_c8,lVar35,(uVar20 + uVar19) - lVar35,uVar20,0,0,uVar19,puVar18
                             );
            }
            else if (uVar19 != 0) {
              puVar17 = puVar24;
              if ((uVar27 & 1) != 0) {
                puVar17 = puStack_b8;
              }
              puVar32 = puVar18;
              if (uVar20 != 0) {
                puVar32 = (undefined4 *)((long)puVar18 + uVar19);
                if ((undefined4 *)((long)puVar17 + uVar20) <= puVar18 || puVar18 < puVar17) {
                  puVar32 = puVar18;
                }
                memmove((long)puVar17 + uVar19,puVar17,uVar20);
              }
              memmove(puVar17,puVar32,uVar19);
              uVar20 = uVar20 + uVar19;
              uVar19 = uVar20;
              if ((uStack_c8 & 1) == 0) {
                uStack_c8 = CONCAT71(uStack_c8._1_7_,(char)uVar20 * '\x02');
                uVar19 = uStack_c0;
              }
              uStack_c0 = uVar19;
              *(undefined1 *)((long)puVar17 + uVar20) = 0;
            }
            uStack_a8 = uStack_c0;
            uStack_b0 = uStack_c8;
            puStack_a0 = puStack_b8;
            if ((uStack_c8 & 1) == 0) {
              uVar20 = 0x16;
              uVar19 = uStack_c8 & 0xff;
            }
            else {
              uVar20 = (uStack_c8 & 0xfffffffffffffffe) - 1;
              uVar19 = uStack_c8;
            }
            uVar27 = (ulong)(((uint)uVar19 & 0xfe) >> 1);
            if ((uVar19 & 1) != 0) {
              uVar27 = uStack_c0;
            }
            if (uVar20 == uVar27) {
              string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&uStack_b0,uVar20,1,uVar20,uVar20,0,1,&UNK_029c5d3e/*"/"*/);
            }
            else {
              puVar18 = puVar25;
              if ((uVar19 & 1) != 0) {
                puVar18 = puStack_b8;
              }
              *(undefined1 *)((long)puVar18 + uVar27) = 0x2f;
              uVar27 = uVar27 + 1;
              uVar19 = uVar27;
              if ((uStack_c8 & 1) == 0) {
                uStack_b0 = CONCAT71((int7)(uStack_c8 >> 8),(char)uVar27 * '\x02');
                uVar19 = uStack_a8;
              }
              uStack_a8 = uVar19;
              *(undefined1 *)((long)puVar18 + uVar27) = 0;
            }
            puVar18 = puVar25;
            if (((uStack_b0 & 1) == 0) || (puVar18 = puStack_a0, puStack_a0 != (undefined4 *)0x0)) {
              iVar11 = access(puVar18,0);
              puVar18 = puStack_a0;
              if (iVar11 != 0) goto code_r0x018e0868;
            }
            else {
              puVar18 = (undefined4 *)0x0;
code_r0x018e0868:
              puVar17 = puVar25;
              if ((uStack_b0 & 1) != 0) {
                puVar17 = puVar18;
              }
              Aska::File::CreateDirectory(char const*)(puVar17);
            }
            puVar18 = puVar25;
            if ((uStack_b0 & 1) != 0) {
              puVar18 = puStack_a0;
            }
            BAS::SetNoBackupFolder(char const*)(puVar18);
            if ((uStack_b0 & 1) != 0) {
              Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puStack_a0);
            }
          }
        }
code_r0x018e0898:
        uStack_c0 = 0;
        puStack_b8 = (undefined4 *)0x0;
        uStack_c8 = 0;
        uVar19 = strlen(lVar31);
        if (uVar19 < 0x17) {
          uStack_c8 = CONCAT71(uStack_c8._1_7_,(char)(uVar19 << 1));
          puVar18 = puVar24;
          if (uVar19 != 0) goto code_r0x018e0934;
        }
        else {
          uVar20 = uVar19 + 0x10 & 0xfffffffffffffff0;
          if (uVar20 == 0) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
          }
          puVar18 = (undefined4 *)Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar20,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
          if (puVar18 == (undefined4 *)0x0) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
          }
          uStack_c8 = uVar20 | 1;
          uStack_c0 = uVar19;
          puStack_b8 = puVar18;
code_r0x018e0934:
          memcpy(puVar18,lVar31,uVar19);
        }
        *(undefined1 *)((long)puVar18 + uVar19) = 0;
        Aska::THashMap<string, CAssetInfo, Hasher_CSTLString, Aska::TEqualTo<string >, Aska::TAllocator<Aska::TPair<string const, CAssetInfo> > >::Find_(string const&) const(&uStack_b0,lVar28 + 0x58,&uStack_c8);
        if ((uStack_c8 & 1) != 0) {
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puStack_b8);
        }
        if (uStack_b0 == *(long *)(lVar28 + 0x78) + *(long *)(lVar28 + 0x80) * 0xc0) {
code_r0x018e0ae4:
          uVar21 = 2;
        }
        else {
          uVar19 = uStack_80 >> 1 & 0x7f;
          puVar18 = puVar38;
          if ((uStack_80 & 1) != 0) {
            uVar19 = uStack_78;
            puVar18 = puStack_70;
          }
          if ((uStack_98 & 1) == 0) {
            lVar31 = 0x16;
            uVar20 = uStack_98 & 0xff;
          }
          else {
            lVar31 = (uStack_98 & 0xfffffffffffffffe) - 1;
            uVar20 = uStack_98;
          }
          uVar27 = (ulong)(((uint)uVar20 & 0xfe) >> 1);
          if ((uVar20 & 1) != 0) {
            uVar27 = uStack_90;
          }
          if (lVar31 - uVar27 < uVar19) {
            string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&uStack_98,lVar31,(uVar19 - lVar31) + uVar27,uVar27,uVar27,0,uVar19);
          }
          else if (uVar19 != 0) {
            puVar17 = puVar33;
            if ((uVar20 & 1) != 0) {
              puVar17 = puStack_88;
            }
            memcpy((long)puVar17 + uVar27,puVar18,uVar19);
            uVar27 = uVar27 + uVar19;
            uVar19 = uVar27;
            if ((uStack_98 & 1) == 0) {
              uStack_98 = CONCAT71(uStack_98._1_7_,(char)uVar27 * '\x02');
              uVar19 = uStack_90;
            }
            uStack_90 = uVar19;
            *(undefined1 *)((long)puVar17 + uVar27) = 0;
          }
          if ((*piVar30 != 0x46534900) || (0x20130304 < (uint)piVar30[1])) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02866e51/*"C:\BAS_Submission\Client\Project\../Library/Framework/Tools\MakeFileStream/FileStream_Image.h"*/,0xea,&UNK_02866eaf/*"Illegal instance."*/);
          }
          if ((uint)piVar30[2] <= uVar36) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02866e51/*"C:\BAS_Submission\Client\Project\../Library/Framework/Tools\MakeFileStream/FileStream_Image.h"*/,0xeb,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,uVar36 & 0xffffffff);
          }
          iVar11 = piVar30[uVar36 * 4 + 6];
          puVar18 = puVar33;
          if (((((uStack_98 & 1) == 0) || (puVar18 = puStack_88, puStack_88 != (undefined4 *)0x0))
              && (iVar12 = access(puVar18,0), iVar12 == 0)) &&
             (*(int *)(uStack_b0 + 0x48) == iVar11 + 0x10)) goto code_r0x018e0ae4;
          puVar18 = puVar33;
          if ((uStack_98 & 1) != 0) {
            puVar18 = puStack_88;
          }
          if ((*piVar30 != 0x46534900) || (0x20130304 < (uint)piVar30[1])) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02866e51/*"C:\BAS_Submission\Client\Project\../Library/Framework/Tools\MakeFileStream/FileStream_Image.h"*/,0xe3,&UNK_02866eaf/*"Illegal instance."*/);
          }
          if ((uint)piVar30[2] <= uVar36) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02866e51/*"C:\BAS_Submission\Client\Project\../Library/Framework/Tools\MakeFileStream/FileStream_Image.h"*/,0xe4,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,uVar36 & 0xffffffff);
          }
          uVar1 = piVar30[uVar36 * 4 + 5];
          if ((*piVar30 != 0x46534900) || (0x20130304 < (uint)piVar30[1])) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02866e51/*"C:\BAS_Submission\Client\Project\../Library/Framework/Tools\MakeFileStream/FileStream_Image.h"*/,0xea,&UNK_02866eaf/*"Illegal instance."*/);
          }
          if ((uint)piVar30[2] <= uVar36) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02866e51/*"C:\BAS_Submission\Client\Project\../Library/Framework/Tools\MakeFileStream/FileStream_Image.h"*/,0xeb,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,uVar36 & 0xffffffff);
          }
          iVar11 = piVar30[uVar36 * 4 + 6];
          uVar19 = uStack_b0 + 0x20;
          uVar20 = strlen(puVar18);
          if (0xff < uVar20) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dc32f/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/Utility.h"*/,0x77,&UNK_027dc380/*"gStrcpy() : destination buffer is small. ( %d < %d )"*/,uVar20,0x100);
          }
          strcpy(puVar34 + uVar36 * 0x28 + 1,puVar18);
          puVar34[uVar36 * 0x28 + 0x21] = (ulong)uVar1 + (long)piVar30;
          *(int *)(puVar34 + uVar36 * 0x28 + 0x22) = iVar11;
          puVar34[uVar36 * 0x28 + 0x27] = uVar19;
          *(undefined4 *)((long)puVar34 + uVar36 * 0x140 + 0x114) = 0;
          uVar21 = 0;
        }
        *(undefined4 *)(puVar34 + uVar36 * 0x28 + 0x23) = uVar21;
        if ((uStack_98 & 1) != 0) {
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puStack_88);
        }
        if ((uStack_80 & 1) != 0) {
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puStack_70);
        }
        uVar36 = uVar36 + 1;
        if (uVar36 == uVar14) break;
        puVar34 = *(ulong **)(param_1 + 0x198);
      } while( true );
    }
  }
  else {
    puVar34 = puVar16 + 1;
    *puVar16 = uVar14;
    if (uVar37 != 0) {
      puVar5 = PTR__ZTVN23CGameResourceDownloader13CDownloadNode12UnpackNotifyE_02cc1100 + 0x10;
      puVar3 = PTR__ZTVN4Aska4FileE_02cb6e28 + 0x10;
      puVar16 = puVar34;
      do {
        *puVar16 = (ulong)puVar5;
        *(undefined4 *)(puVar16 + 0x23) = 0;
        puVar16[0x21] = 0;
        puVar16[0x22] = 0;
        puVar16[0x24] = (ulong)puVar3;
        *(undefined1 *)(puVar16 + 0x25) = 0;
        puVar16[0x26] = 0;
        puVar16[0x27] = 0;
        puVar16 = puVar16 + 0x28;
      } while (puVar16 != puVar34 + uVar14 * 0x28);
      goto code_r0x018e058c;
    }
    *(ulong **)(param_1 + 0x198) = puVar34;
  }
  *(uint *)(param_1 + 400) = uVar37;
  *(int *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) + 1;
joined_r0x018e0ee4:
  if ((uVar22 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puVar2);
  }
  return;
}

// ==== CGameResourceDownloader::CDownloadNode::Callback(char const*, CGameResourceDownloader::iErrorCode)
// vaddr 0x17e0f10 | ghidra 0x18e0f10 | size 632 | symbol _ZN23CGameResourceDownloader13CDownloadNode8CallbackEPKcNS_10iErrorCodeE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN23CGameResourceDownloader13CDownloadNode8CallbackEPKcNS_10iErrorCodeE
               (long param_1,undefined8 param_2,undefined4 param_3)

{
  long lVar1;
  ulong uVar2;
  uint uVar3;
  ulong uVar4;
  long *plVar5;
  ulong uVar6;
  code *pcVar7;
  ulong uVar8;
  ulong uVar9;
  long *plVar10;
  ulong uVar11;
  long *plVar12;
  undefined1 auStack_58 [20];
  undefined4 uStack_44;
  undefined8 uStack_38;
  
  lVar1 = param_1 + 0x3a0;
  uVar4 = Framework::CMutex::IsInitialized() const(lVar1);
  if ((uVar4 & 1) == 0) {
    Framework::CMutex::Initialize()(lVar1);
  }
  Framework::CMutex::Lock()(lVar1);
  Framework::CHash32::CHash32(char const*)(auStack_58,param_2);
  uVar3 = Framework::CHash32::operator unsigned int() const(auStack_58);
  uVar4 = *(ulong *)(param_1 + 0x380);
  if (uVar4 != 0) {
    uVar8 = uVar4 - 1;
    uVar6 = (ulong)uVar3;
    if ((uVar8 & uVar4) == 0) {
      uVar6 = uVar8 & uVar6;
    }
    else {
      uVar9 = 0;
      if (uVar4 != 0) {
        uVar9 = uVar6 / uVar4;
      }
      uVar6 = uVar6 - uVar9 * uVar4;
    }
    plVar12 = *(long **)(*(long *)(param_1 + 0x378) + uVar6 * 8);
    if (plVar12 != (long *)0x0) {
      if ((uVar8 & uVar4) == 0) {
        do {
          plVar12 = (long *)*plVar12;
          if ((plVar12 == (long *)0x0) || ((plVar12[1] & uVar8) != uVar6)) goto code_r0x018e1054;
        } while (*(uint *)(plVar12 + 2) != uVar3);
      }
      else {
        do {
          plVar12 = (long *)*plVar12;
          if (plVar12 == (long *)0x0) goto code_r0x018e1054;
          uVar8 = 0;
          if (uVar4 != 0) {
            uVar8 = (ulong)plVar12[1] / uVar4;
          }
          if (plVar12[1] - uVar8 * uVar4 != uVar6) goto code_r0x018e1054;
        } while (*(uint *)(plVar12 + 2) != uVar3);
      }
      Framework::CHash32::~CHash32()(auStack_58);
      if (plVar12 == (long *)0x0) goto code_r0x018e105c;
      if (plVar12[0x2a] != 0) {
        uVar4 = 0;
        do {
          uStack_44 = param_3;
          uStack_38 = param_2;
          (**(code **)(*(long *)plVar12[0x28] + 0x30))((long *)plVar12[0x28],&uStack_38,&uStack_44);
          uVar4 = uVar4 + 1;
        } while (uVar4 < (ulong)plVar12[0x2a]);
      }
      uVar6 = *(ulong *)(param_1 + 0x380);
      uVar4 = plVar12[1];
      uVar8 = uVar6 - 1;
      uVar9 = uVar8 & uVar6;
      if (uVar9 == 0) {
        uVar4 = uVar8 & uVar4;
      }
      else {
        uVar11 = 0;
        if (uVar6 != 0) {
          uVar11 = uVar4 / uVar6;
        }
        uVar4 = uVar4 - uVar11 * uVar6;
      }
      plVar5 = *(long **)(*(long *)(param_1 + 0x378) + uVar4 * 8);
      do {
        plVar10 = plVar5;
        plVar5 = (long *)*plVar10;
      } while ((long *)*plVar10 != plVar12);
      if (plVar10 == (long *)(param_1 + 0x388)) {
code_r0x018e10cc:
        if (*plVar12 != 0) {
          uVar11 = *(ulong *)(*plVar12 + 8);
          if (uVar9 == 0) {
            uVar11 = uVar11 & uVar8;
          }
          else {
            uVar2 = 0;
            if (uVar6 != 0) {
              uVar2 = uVar11 / uVar6;
            }
            uVar11 = uVar11 - uVar2 * uVar6;
          }
          if (uVar11 == uVar4) goto code_r0x018e1100;
        }
        *(undefined8 *)(*(long *)(param_1 + 0x378) + uVar4 * 8) = 0;
      }
      else {
        uVar11 = plVar10[1];
        if (uVar9 == 0) {
          uVar11 = uVar11 & uVar8;
        }
        else {
          uVar2 = 0;
          if (uVar6 != 0) {
            uVar2 = uVar11 / uVar6;
          }
          uVar11 = uVar11 - uVar2 * uVar6;
        }
        if (uVar11 != uVar4) goto code_r0x018e10cc;
      }
code_r0x018e1100:
      if (*plVar12 != 0) {
        uVar11 = *(ulong *)(*plVar12 + 8);
        if (uVar9 == 0) {
          uVar11 = uVar11 & uVar8;
        }
        else {
          uVar8 = 0;
          if (uVar6 != 0) {
            uVar8 = uVar11 / uVar6;
          }
          uVar11 = uVar11 - uVar8 * uVar6;
        }
        if (uVar11 != uVar4) {
          *(long **)(*(long *)(param_1 + 0x378) + uVar11 * 8) = plVar10;
        }
      }
      *plVar10 = *plVar12;
      *plVar12 = 0;
      *(long *)(param_1 + 0x390) = *(long *)(param_1 + 0x390) + -1;
      plVar5 = (long *)plVar12[0x28];
      if (plVar12 + 0x24 == plVar5) {
        pcVar7 = *(code **)(*plVar5 + 0x20);
code_r0x018e1168:
        (*pcVar7)();
      }
      else if (plVar5 != (long *)0x0) {
        pcVar7 = *(code **)(*plVar5 + 0x28);
        goto code_r0x018e1168;
      }
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar12);
      goto code_r0x018e105c;
    }
  }
code_r0x018e1054:
  Framework::CHash32::~CHash32()(auStack_58);
code_r0x018e105c:
  Framework::CMutex::Unlock()(lVar1);
  return;
}

// ==== CGameResourceDownloader::CDownloadNode::CDownloadStream::GetBuffer() const
// vaddr 0x17e1188 | ghidra 0x18e1188 | size 8 | symbol _ZNK23CGameResourceDownloader13CDownloadNode15CDownloadStream9GetBufferEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK23CGameResourceDownloader13CDownloadNode15CDownloadStream9GetBufferEv(long param_1)

{
  return *(undefined8 *)(param_1 + 0x1c0);
}

// ==== CGameResourceDownloader::CDownloadNode::CDownloadStream::DeleteBuffer()
// vaddr 0x17e1190 | ghidra 0x18e1190 | size 32 | symbol _ZN23CGameResourceDownloader13CDownloadNode15CDownloadStream12DeleteBufferEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN23CGameResourceDownloader13CDownloadNode15CDownloadStream12DeleteBufferEv(long param_1)

{
  if (*(long *)(param_1 + 0x1c0) != 0) {
    operator delete[](void*)();
    *(undefined8 *)(param_1 + 0x1c0) = 0;
  }
  return;
}

// ==== CGameResourceDownloader::CDownloadNode::AllCallback()
// vaddr 0x17e11b0 | ghidra 0x18e11b0 | size 468 | symbol _ZN23CGameResourceDownloader13CDownloadNode11AllCallbackEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN23CGameResourceDownloader13CDownloadNode11AllCallbackEv(long param_1)

{
  long lVar1;
  long *plVar2;
  ulong uVar3;
  ulong uVar4;
  ulong uVar5;
  long *plVar6;
  code *pcVar7;
  ulong uVar8;
  ulong uVar9;
  ulong uVar10;
  long *plVar11;
  long *plVar12;
  undefined4 uStack_44;
  long *plStack_38;
  
  lVar1 = param_1 + 0x3a0;
  uVar5 = Framework::CMutex::IsInitialized() const(lVar1);
  if ((uVar5 & 1) == 0) {
    Framework::CMutex::Initialize()(lVar1);
  }
  Framework::CMutex::Lock()(lVar1);
  if (*(long **)(param_1 + 0x388) != (long *)0x0) {
    plVar12 = *(long **)(param_1 + 0x388);
    do {
      if (plVar12[0x2a] != 0) {
        uVar5 = 0;
        do {
          uStack_44 = 0;
          plStack_38 = plVar12 + 4;
          (**(code **)(*(long *)plVar12[0x28] + 0x30))((long *)plVar12[0x28],&plStack_38,&uStack_44)
          ;
          uVar5 = uVar5 + 1;
        } while (uVar5 < (ulong)plVar12[0x2a]);
      }
      uVar8 = *(ulong *)(param_1 + 0x380);
      plVar2 = (long *)*plVar12;
      uVar5 = plVar12[1];
      uVar9 = uVar8 - 1;
      uVar3 = 0;
      if (uVar8 != 0) {
        uVar3 = uVar5 / uVar8;
      }
      uVar10 = uVar9 & uVar8;
      uVar3 = uVar5 - uVar3 * uVar8;
      if (uVar10 == 0) {
        uVar3 = uVar9 & uVar5;
      }
      plVar6 = *(long **)(*(long *)(param_1 + 0x378) + uVar3 * 8);
      do {
        plVar11 = plVar6;
        plVar6 = (long *)*plVar11;
      } while ((long *)*plVar11 != plVar12);
      if (plVar11 == (long *)(param_1 + 0x388)) {
code_r0x018e1290:
        if (*plVar12 != 0) {
          uVar5 = *(ulong *)(*plVar12 + 8);
          if (uVar10 == 0) {
            uVar5 = uVar5 & uVar9;
          }
          else {
            uVar4 = 0;
            if (uVar8 != 0) {
              uVar4 = uVar5 / uVar8;
            }
            uVar5 = uVar5 - uVar4 * uVar8;
          }
          if (uVar5 == uVar3) goto code_r0x018e12d4;
        }
        *(undefined8 *)(*(long *)(param_1 + 0x378) + uVar3 * 8) = 0;
      }
      else {
        uVar5 = plVar11[1];
        if (uVar10 == 0) {
          uVar5 = uVar5 & uVar9;
        }
        else {
          uVar4 = 0;
          if (uVar8 != 0) {
            uVar4 = uVar5 / uVar8;
          }
          uVar5 = uVar5 - uVar4 * uVar8;
        }
        if (uVar5 != uVar3) goto code_r0x018e1290;
      }
code_r0x018e12d4:
      if (*plVar12 != 0) {
        uVar5 = *(ulong *)(*plVar12 + 8);
        if (uVar10 == 0) {
          uVar5 = uVar5 & uVar9;
        }
        else {
          uVar9 = 0;
          if (uVar8 != 0) {
            uVar9 = uVar5 / uVar8;
          }
          uVar5 = uVar5 - uVar9 * uVar8;
        }
        if (uVar5 != uVar3) {
          *(long **)(*(long *)(param_1 + 0x378) + uVar5 * 8) = plVar11;
        }
      }
      *plVar11 = *plVar12;
      *plVar12 = 0;
      *(long *)(param_1 + 0x390) = *(long *)(param_1 + 0x390) + -1;
      if (plVar12 != (long *)0x0) {
        plVar6 = (long *)plVar12[0x28];
        if (plVar12 + 0x24 == plVar6) {
          pcVar7 = *(code **)(*plVar6 + 0x20);
code_r0x018e1350:
          (*pcVar7)();
        }
        else if (plVar6 != (long *)0x0) {
          pcVar7 = *(code **)(*plVar6 + 0x28);
          goto code_r0x018e1350;
        }
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar12);
      }
      plVar12 = plVar2;
    } while (plVar2 != (long *)0x0);
  }
  Framework::CMutex::Unlock()(lVar1);
  return;
}

// ==== CGameResourceDownloader::CDownloadNode::UnpackNotify::SetBinary(char const*, void const*, unsigned int, CAssetInfo*)
// vaddr 0x17e1384 | ghidra 0x18e1384 | size 144 | symbol _ZN23CGameResourceDownloader13CDownloadNode12UnpackNotify9SetBinaryEPKcPKvjP10CAssetInfo | lib libSOA-3.7.0.so | 2026-10-04
void _ZN23CGameResourceDownloader13CDownloadNode12UnpackNotify9SetBinaryEPKcPKvjP10CAssetInfo
               (long param_1,undefined8 param_2,undefined8 param_3,undefined4 param_4,
               undefined8 param_5)

{
  ulong uVar1;
  
  uVar1 = strlen(param_2);
  if (0xff < uVar1) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dc32f/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/Utility.h"*/,0x77,&UNK_027dc380/*"gStrcpy() : destination buffer is small. ( %d < %d )"*/,uVar1,0x100);
  }
  strcpy(param_1 + 8,param_2);
  *(undefined8 *)(param_1 + 0x108) = param_3;
  *(undefined4 *)(param_1 + 0x110) = param_4;
  *(undefined8 *)(param_1 + 0x138) = param_5;
  *(undefined8 *)(param_1 + 0x114) = 0;
  return;
}

// ==== CGameResourceDownloader::CDownloadNode::UnpackNotify::GetDispatchCount()
// vaddr 0x17e1414 | ghidra 0x18e1414 | size 20 | symbol _ZN23CGameResourceDownloader13CDownloadNode12UnpackNotify16GetDispatchCountEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZN23CGameResourceDownloader13CDownloadNode12UnpackNotify16GetDispatchCountEv(void)

{
  DataMemoryBarrier(2,3);
  return *(undefined4 *)
          PTR__ZN23CGameResourceDownloader13CDownloadNode12UnpackNotify15m_DispatchCountE_02cbe960;
}

// ==== CGameResourceDownloader::CDownloadNode::UnpackNotify::GetMaxDispatchCount()
// vaddr 0x17e1428 | ghidra 0x18e1428 | size 8 | symbol _ZN23CGameResourceDownloader13CDownloadNode12UnpackNotify19GetMaxDispatchCountEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN23CGameResourceDownloader13CDownloadNode12UnpackNotify19GetMaxDispatchCountEv(void)

{
  return 5;
}

// ==== CGameResourceDownloader::CDownloadNode::UnpackNotify::IncDispatchCount()
// vaddr 0x17e1430 | ghidra 0x18e1430 | size 64 | symbol _ZN23CGameResourceDownloader13CDownloadNode12UnpackNotify16IncDispatchCountEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN23CGameResourceDownloader13CDownloadNode12UnpackNotify16IncDispatchCountEv(void)

{
  char cVar1;
  bool bVar2;
  undefined *puVar3;
  
  puVar3 = PTR__ZN23CGameResourceDownloader13CDownloadNode12UnpackNotify15m_DispatchCountE_02cbe960;
  do {
    cVar1 = '\x01';
    bVar2 = (bool)ExclusiveMonitorPass(puVar3,0x10);
    if (bVar2) {
      *(int *)puVar3 = *(int *)puVar3 + 1;
      cVar1 = ExclusiveMonitorsStatus();
    }
  } while (cVar1 != '\0');
  if (*(int *)puVar3 < 6) {
    return;
  }
  (*(code *)PTR__ZN9Framework9gDoAssertEPKciS1_z_02ca3240)(&UNK_02866a48/*"C:\BAS_Submission\Client\Project\..\Source\Game\Resource\GameResourceDownloader.cpp"*/,0x1222,&UNK_02866c4f/*"IncDispatchCount too many call?"*/);
  return;
}

// ==== CGameResourceDownloader::CDownloadNode::UnpackNotify::SubDispatchCount()
// vaddr 0x17e1470 | ghidra 0x18e1470 | size 60 | symbol _ZN23CGameResourceDownloader13CDownloadNode12UnpackNotify16SubDispatchCountEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN23CGameResourceDownloader13CDownloadNode12UnpackNotify16SubDispatchCountEv(void)

{
  char cVar1;
  bool bVar2;
  undefined *puVar3;
  
  puVar3 = PTR__ZN23CGameResourceDownloader13CDownloadNode12UnpackNotify15m_DispatchCountE_02cbe960;
  do {
    cVar1 = '\x01';
    bVar2 = (bool)ExclusiveMonitorPass(puVar3,0x10);
    if (bVar2) {
      *(int *)puVar3 = *(int *)puVar3 + -1;
      cVar1 = ExclusiveMonitorsStatus();
    }
  } while (cVar1 != '\0');
  if (-1 < *(int *)puVar3) {
    return;
  }
  (*(code *)PTR__ZN9Framework9gDoAssertEPKciS1_z_02ca3240)(&UNK_02866a48/*"C:\BAS_Submission\Client\Project\..\Source\Game\Resource\GameResourceDownloader.cpp"*/,0x1228,&UNK_02866c6f/*"SubDispatchCount too many call?"*/);
  return;
}

// ==== std::__ndk1::unordered_map<unsigned int, CGameResourceDownloader::CDownloadNode::tCallbackInfo, std::__ndk1::hash<unsigned int>, std::__ndk1::equal_to<unsigned int>, Framework::CSTLAllocator<std::__ndk1::pair<unsigned int const, CGameResourceDownloader::CDownloadNode::tCallbackInfo>, Framework::CSTLUnorderedMapAllocatorInf> >::operator[](unsigned int&&)
// vaddr 0x17e14ac | ghidra 0x18e14ac | size 504 | symbol _ZNSt6__ndk113unordered_mapIjN23CGameResourceDownloader13CDownloadNode13tCallbackInfoENS_4hashIjEENS_8equal_toIjEEN9Framework13CSTLAllocatorINS_4pairIKjS3_EENS8_28CSTLUnorderedMapAllocatorInfEEEEixEOj | lib libSOA-3.7.0.so | 2026-10-04
long * _ZNSt6__ndk113unordered_mapIjN23CGameResourceDownloader13CDownloadNode13tCallbackInfoENS_4hashIjEENS_8equal_toIjEEN9Framework13CSTLAllocatorINS_4pairIKjS3_EENS8_28CSTLUnorderedMapAllocatorInfEEEEixEOj
                 (long *param_1,uint *param_2)

{
  uint uVar1;
  ulong uVar2;
  ulong uVar3;
  long *plVar4;
  long *plVar5;
  ulong uVar6;
  ulong uVar7;
  ulong unaff_x24;
  
  uVar6 = param_1[1];
  uVar1 = *param_2;
  uVar7 = (ulong)uVar1;
  if (uVar6 != 0) {
    uVar3 = uVar6 - 1;
    if ((uVar3 & uVar6) == 0) {
      unaff_x24 = uVar3 & uVar7;
    }
    else {
      uVar2 = 0;
      if (uVar6 != 0) {
        uVar2 = uVar7 / uVar6;
      }
      unaff_x24 = uVar7 - uVar2 * uVar6;
    }
    plVar5 = *(long **)(*param_1 + unaff_x24 * 8);
    if (plVar5 != (long *)0x0) {
      if ((uVar3 & uVar6) == 0) {
        do {
          plVar5 = (long *)*plVar5;
          if ((plVar5 == (long *)0x0) || ((plVar5[1] & uVar3) != unaff_x24)) goto code_r0x018e1554;
        } while (*(uint *)(plVar5 + 2) != uVar1);
      }
      else {
        do {
          plVar5 = (long *)*plVar5;
          if (plVar5 == (long *)0x0) goto code_r0x018e1554;
          uVar3 = 0;
          if (uVar6 != 0) {
            uVar3 = (ulong)plVar5[1] / uVar6;
          }
          if (plVar5[1] - uVar3 * uVar6 != unaff_x24) goto code_r0x018e1554;
        } while (*(uint *)(plVar5 + 2) != uVar1);
      }
      goto code_r0x018e168c;
    }
  }
code_r0x018e1554:
  plVar5 = (long *)Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(0x160,&UNK_027dc2d5/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_UnorderedMap.h"*/,0x1c);
  if (plVar5 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
  }
  uVar1 = *param_2;
  plVar5[0x28] = 0;
  plVar5[0x2a] = 0;
  *plVar5 = 0;
  plVar5[1] = uVar7;
  *(uint *)(plVar5 + 2) = uVar1;
  if ((uVar6 == 0) || (*(float *)(param_1 + 4) * (float)uVar6 < (float)(param_1[3] + 1))) {
    if (uVar6 < 3) {
      uVar3 = 1;
    }
    else {
      uVar3 = (ulong)((uVar6 - 1 & uVar6) != 0);
    }
    uVar3 = uVar3 | uVar6 << 1;
    uVar6 = (ulong)((float)(param_1[3] + 1) / *(float *)(param_1 + 4));
    if (uVar6 <= uVar3) {
      uVar6 = uVar3;
    }
    std::__ndk1::__hash_table<std::__ndk1::__hash_value_type<unsigned int, CGameResourceDownloader::CDownloadNode::tCallbackInfo>, std::__ndk1::__unordered_map_hasher<unsigned int, std::__ndk1::__hash_value_type<unsigned int, CGameResourceDownloader::CDownloadNode::tCallbackInfo>, std::__ndk1::hash<unsigned int>, true>, std::__ndk1::__unordered_map_equal<unsigned int, std::__ndk1::__hash_value_type<unsigned int, CGameResourceDownloader::CDownloadNode::tCallbackInfo>, std::__ndk1::equal_to<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__hash_value_type<unsigned int, CGameResourceDownloader::CDownloadNode::tCallbackInfo>, Framework::CSTLUnorderedMapAllocatorInf> >::rehash(unsigned long)(param_1,uVar6);
    uVar6 = param_1[1];
    if ((uVar6 - 1 & uVar6) == 0) {
      unaff_x24 = uVar6 - 1 & uVar7;
    }
    else {
      uVar3 = 0;
      if (uVar6 != 0) {
        uVar3 = uVar7 / uVar6;
      }
      unaff_x24 = uVar7 - uVar3 * uVar6;
    }
  }
  plVar4 = *(long **)(*param_1 + unaff_x24 * 8);
  if (plVar4 == (long *)0x0) {
    plVar4 = param_1 + 2;
    *plVar5 = *plVar4;
    *plVar4 = (long)plVar5;
    *(long **)(*param_1 + unaff_x24 * 8) = plVar4;
    if (*plVar5 != 0) {
      uVar7 = *(ulong *)(*plVar5 + 8);
      if ((uVar6 - 1 & uVar6) == 0) {
        uVar7 = uVar7 & uVar6 - 1;
      }
      else {
        uVar3 = 0;
        if (uVar6 != 0) {
          uVar3 = uVar7 / uVar6;
        }
        uVar7 = uVar7 - uVar3 * uVar6;
      }
      *(long **)(*param_1 + uVar7 * 8) = plVar5;
    }
  }
  else {
    *plVar5 = *plVar4;
    *plVar4 = (long)plVar5;
  }
  param_1[3] = param_1[3] + 1;
code_r0x018e168c:
  return plVar5 + 4;
}

// ==== CGameResourceDownloader::CDownloadNode::CDownloadStream::SetContentsSize(unsigned long)
// vaddr 0x17e16a4 | ghidra 0x18e16a4 | size 8 | symbol _ZN23CGameResourceDownloader13CDownloadNode15CDownloadStream15SetContentsSizeEm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN23CGameResourceDownloader13CDownloadNode15CDownloadStream15SetContentsSizeEm
               (long param_1,undefined8 param_2)

{
  *(undefined8 *)(param_1 + 0x180) = param_2;
  return;
}

// ==== CGameResourceDownloader::CDownloadNode::IsMetaInfo(char const*) const
// vaddr 0x17e16ac | ghidra 0x18e16ac | size 436 | symbol _ZNK23CGameResourceDownloader13CDownloadNode10IsMetaInfoEPKc | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZNK23CGameResourceDownloader13CDownloadNode10IsMetaInfoEPKc(long param_1,undefined8 param_2)

{
  bool bVar1;
  long lVar2;
  undefined8 uVar3;
  int iVar4;
  ulong uVar5;
  long lVar6;
  long lVar7;
  ulong uVar8;
  ulong uVar9;
  undefined8 uStack_78;
  ulong uStack_70;
  long lStack_68;
  
  lVar6 = *(long *)(param_1 + 0x178);
  if (0 < *(long *)(lVar6 + 0x18)) {
    lVar2 = (long)&uStack_78 + 1;
    uVar5 = 0;
    uVar9 = 1;
    do {
      lVar7 = *(long *)(lVar6 + 8) + uVar5 * 0x28;
      uStack_70 = 0;
      lStack_68 = 0;
      uStack_78 = 0;
      if ((*(byte *)(lVar7 + 0x10) & 1) == 0) {
        lStack_68 = *(long *)(lVar7 + 0x20);
        uStack_70 = *(ulong *)(lVar7 + 0x18);
        uStack_78 = *(ulong *)(lVar7 + 0x10);
      }
      else {
        lVar6 = *(long *)(lVar6 + 8) + uVar5 * 0x28;
        uVar5 = *(ulong *)(lVar6 + 0x18);
        uVar3 = *(undefined8 *)(lVar6 + 0x20);
        if (uVar5 < 0x17) {
          uStack_78 = (uVar5 & 0x7f) << 1;
          lVar6 = lVar2;
          if (uVar5 != 0) goto code_r0x018e17d4;
        }
        else {
          uVar8 = uVar5 + 0x10 & 0xfffffffffffffff0;
          if (uVar8 == 0) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
          }
          lVar6 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar8,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
          if (lVar6 == 0) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
          }
          uStack_78 = uVar8 | 1;
          uStack_70 = uVar5;
          lStack_68 = lVar6;
code_r0x018e17d4:
          memcpy(lVar6,uVar3,uVar5);
        }
        *(undefined1 *)(lVar6 + uVar5) = 0;
      }
      lVar7 = lStack_68;
      uVar5 = uStack_78;
      lVar6 = lVar2;
      if ((uStack_78 & 1) != 0) {
        lVar6 = lStack_68;
      }
      iVar4 = strcmp(lVar6,param_2);
      if ((uVar5 & 1) != 0) {
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(lVar7);
      }
      if (iVar4 == 0) {
        return 1;
      }
      lVar6 = *(long *)(param_1 + 0x178);
      bVar1 = (long)uVar9 < *(long *)(lVar6 + 0x18);
      uVar5 = uVar9;
      uVar9 = (ulong)((int)uVar9 + 1);
    } while (bVar1);
  }
  return 0;
}

// ==== CGameResourceDownloader::CDownloadNode::Handler(unsigned long)
// vaddr 0x17e1860 | ghidra 0x18e1860 | size 308 | symbol _ZN23CGameResourceDownloader13CDownloadNode7HandlerEm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN23CGameResourceDownloader13CDownloadNode7HandlerEm(long param_1,long param_2)

{
  undefined *puVar1;
  int iVar2;
  ulong uVar3;
  undefined4 uVar4;
  long lVar5;
  ulong uVar6;
  
  if (*(int *)(param_1 + 8) == 5) {
    return;
  }
  lVar5 = *(long *)(param_2 + 0x148);
  if (lVar5 == 0) {
    uVar3 = BAS::GetDeviceFreeSize()();
    puVar1 = PTR__ZN9Framework10TSingletonI20CGameResourceManagerE11m_pInstanceE_02cc2018;
    uVar6 = *(ulong *)(param_2 + 0x158);
    if (((uVar3 < uVar6) && (*(char *)(param_1 + 0x150) == '\0')) ||
       ((uVar6 < uVar3 &&
        (((undefined *)(uVar3 - uVar6) < &UNK_01e00001 && (*(char *)(param_1 + 0x150) == '\0'))))))
    {
      *(undefined8 *)(param_1 + 0x188) = 0xfffffffffffffc33;
      *(undefined8 *)(param_1 + 0x370) = *(undefined8 *)(param_2 + 0x158);
code_r0x018e1978:
      uVar4 = 6;
      goto code_r0x018e197c;
    }
    if (*(long *)(param_1 + 0x158) != 0) {
      lVar5 = *(long *)PTR__ZN9Framework10TSingletonI20CGameResourceManagerE11m_pInstanceE_02cc2018;
      if (lVar5 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
        lVar5 = *(long *)puVar1;
        uVar6 = *(ulong *)(param_2 + 0x158);
      }
      *(ulong *)(*(long *)(lVar5 + 0x20) + 0x270) =
           *(long *)(*(long *)(lVar5 + 0x20) + 0x270) + uVar6;
      if ((*(byte *)(param_1 + 0x160) & 1) == 0) {
        lVar5 = param_1 + 0x161;
      }
      else {
        lVar5 = *(long *)(param_1 + 0x170);
      }
      iVar2 = strcmp(param_1 + 0x330,lVar5);
      if (iVar2 == 0) {
        uVar4 = 3;
        goto code_r0x018e197c;
      }
      CGameResourceDownloader::CDownloadNode::CDownloadStream::Close(bool)(param_1 + 0x1a0,1);
      lVar5 = -0x3a7;
      goto code_r0x018e1974;
    }
  }
  else {
    if (*(uint *)(param_1 + 0x180) < 3) {
      *(uint *)(param_1 + 0x180) = *(uint *)(param_1 + 0x180) + 1;
      uVar4 = 1;
      goto code_r0x018e197c;
    }
    if (*(char *)(param_1 + 0x110) == '\0') {
code_r0x018e1974:
      *(long *)(param_1 + 0x188) = lVar5;
      goto code_r0x018e1978;
    }
  }
  uVar4 = 5;
code_r0x018e197c:
  *(undefined4 *)(param_1 + 8) = uVar4;
  *(undefined4 *)(param_1 + 0xc) = 0;
  return;
}

// ==== CGameResourceDownloader::CDownloadNode::CDownloadStream::CheckMD5(char const*) const
// vaddr 0x17e1994 | ghidra 0x18e1994 | size 28 | symbol _ZNK23CGameResourceDownloader13CDownloadNode15CDownloadStream8CheckMD5EPKc | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK23CGameResourceDownloader13CDownloadNode15CDownloadStream8CheckMD5EPKc(long param_1)

{
  int iVar1;
  
  iVar1 = strcmp(param_1 + 400);
  return iVar1 == 0;
}

// ==== CGameResourceDownloader::CDownloadNode::CDownloadStream::Close(bool)
// vaddr 0x17e19b0 | ghidra 0x18e19b0 | size 196 | symbol _ZN23CGameResourceDownloader13CDownloadNode15CDownloadStream5CloseEb | lib libSOA-3.7.0.so | 2026-10-04
byte _ZN23CGameResourceDownloader13CDownloadNode15CDownloadStream5CloseEb(long param_1,uint param_2)

{
  long lVar1;
  byte bVar2;
  undefined8 uVar3;
  long lVar4;
  
  lVar4 = *(long *)(param_1 + 0x180);
  if (lVar4 == 0) {
    lVar1 = param_1 + 8;
    lVar4 = Aska::FileStream::Tell() const(lVar1);
    if (0 < lVar4) {
      Aska::FileStream::Seek(long, int)(lVar1,0,0);
      uVar3 = operator new[](unsigned long, std::nothrow_t const&)(lVar4,PTR__ZSt7nothrow_02cb9a80);
      *(undefined8 *)(param_1 + 0x1c0) = uVar3;
      Aska::FileStream::Read(void*, unsigned long, unsigned long)(lVar1,uVar3,lVar4,1);
    }
    bVar2 = Aska::Yayoi::Downloader::DownloadStream::Close(bool)(param_1,param_2 & 1);
    if ((bVar2 & 1) == 0) goto code_r0x018e19f4;
  }
  else {
    bVar2 = lVar4 == *(long *)(param_1 + 0x188);
    if (!(bool)bVar2) goto code_r0x018e19f4;
  }
  if (lVar4 != 0) {
    BAS::CryptBufferSHA1(char const*, unsigned long, char*, unsigned long)(*(undefined8 *)(param_1 + 0x1c0),lVar4,param_1 + 400,0x28);
  }
code_r0x018e19f4:
  return bVar2 & 1;
}

// ==== CGameResourceDownloader::CDownloadNode::UnpackNotify::UnpackNotify()
// vaddr 0x17e1a74 | ghidra 0x18e1a74 | size 52 | symbol _ZN23CGameResourceDownloader13CDownloadNode12UnpackNotifyC1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN23CGameResourceDownloader13CDownloadNode12UnpackNotifyC2Ev(long *param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  
  puVar2 = PTR__ZTVN23CGameResourceDownloader13CDownloadNode12UnpackNotifyE_02cc1100;
  *(undefined4 *)(param_1 + 0x23) = 0;
  param_1[0x21] = 0;
  param_1[0x22] = 0;
  puVar1 = PTR__ZTVN4Aska4FileE_02cb6e28;
  *(undefined1 *)(param_1 + 0x25) = 0;
  *param_1 = (long)(puVar2 + 0x10);
  param_1[0x24] = (long)(puVar1 + 0x10);
  param_1[0x26] = 0;
  param_1[0x27] = 0;
  return;
}

// ==== CGameResourceDownloader::CDownloadNode::UnpackNotify::~UnpackNotify()
// vaddr 0x17e1aa8 | ghidra 0x18e1aa8 | size 116 | symbol _ZN23CGameResourceDownloader13CDownloadNode12UnpackNotifyD1Ev | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Possible PIC construction at 0x018e1ad4: Changing call to branch */
/* WARNING: Removing unreachable block (ram,0x018e1ad8) */
/* WARNING: Removing unreachable block (ram,0x018e1af0) */

void _ZN23CGameResourceDownloader13CDownloadNode12UnpackNotifyD2Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN23CGameResourceDownloader13CDownloadNode12UnpackNotifyE_02cc1100 + 0x10
                   );
  if (param_1[0x26] != 0) {
    (*(code *)PTR__ZN4Aska4File5CloseEv_02c8e880)(param_1 + 0x24);
    return;
  }
  param_1[0x24] = (long)(PTR__ZTVN4Aska4FileE_02cb6e28 + 0x10);
  return;
}

// ==== CGameResourceDownloader::CDownloadNode::UnpackNotify::~UnpackNotify()
// vaddr 0x17e1b1c | ghidra 0x18e1b1c | size 96 | symbol _ZN23CGameResourceDownloader13CDownloadNode12UnpackNotifyD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN23CGameResourceDownloader13CDownloadNode12UnpackNotifyD0Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN23CGameResourceDownloader13CDownloadNode12UnpackNotifyE_02cc1100 + 0x10
                   );
  if (param_1[0x26] != 0) {
    Aska::File::Close()(param_1 + 0x24);
    param_1[0x24] = (long)(PTR__ZTVN4Aska4FileE_02cb6e28 + 0x10);
    if (param_1[0x26] != 0) {
      Aska::File::Close()(param_1 + 0x24);
    }
  }
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== CGameResourceDownloader::CDownloadNode::UnpackNotify::Handler(unsigned long)
// vaddr 0x17e1b7c | ghidra 0x18e1b7c | size 548 | symbol _ZN23CGameResourceDownloader13CDownloadNode12UnpackNotify7HandlerEm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN23CGameResourceDownloader13CDownloadNode12UnpackNotify7HandlerEm(long param_1)

{
  uint uVar1;
  char cVar2;
  bool bVar3;
  uint uVar4;
  int *piVar5;
  int iVar6;
  long lVar7;
  ulong uVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  long lVar11;
  undefined1 auStack_1b0 [256];
  undefined4 uStack_b0;
  int iStack_ac;
  undefined8 uStack_a8;
  undefined4 uStack_80;
  undefined4 uStack_58;
  
  uVar1 = *(uint *)(param_1 + 0x114);
  lVar11 = *(long *)(param_1 + 0x108);
  uVar4 = *(int *)(param_1 + 0x110) - uVar1;
  if (0x4a < uVar4 >> 0xb) {
    uVar4 = 0x25800;
  }
  if (uVar1 == 0) {
    snprintf(auStack_1b0,0x100,&UNK_02866c1b/*"%s.tmp"*/,param_1 + 8);
    uVar8 = Aska::File::Open(char const*, bool, bool, bool)(param_1 + 0x120,auStack_1b0,0,1,0);
    if ((uVar8 & 1) == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02866a48/*"C:\BAS_Submission\Client\Project\..\Source\Game\Resource\GameResourceDownloader.cpp"*/,0x11de,&UNK_02866c22/*"file open failed[ %s ]"*/,auStack_1b0);
    }
    uStack_a8 = 0;
    uStack_b0 = 0x444c4441;
    iStack_ac = *(int *)(*(long *)(param_1 + 0x138) + 0x38);
    if ((iStack_ac != 0) && (lVar7 = Aska::File::Write(void const*, unsigned long)(param_1 + 0x120,&uStack_b0,0x10), lVar7 == 0))
    {
      *(int *)PTR__ZN23CGameResourceDownloader15m_ErrorOverSizeE_02cbb7b8 =
           *(int *)PTR__ZN23CGameResourceDownloader15m_ErrorOverSizeE_02cbb7b8 + 0x10;
    }
    uVar1 = *(uint *)(param_1 + 0x114);
  }
  lVar11 = Aska::File::Write(void const*, unsigned long)(param_1 + 0x120,lVar11 + (ulong)uVar1,uVar4);
  if (lVar11 == 0) {
    *(uint *)PTR__ZN23CGameResourceDownloader15m_ErrorOverSizeE_02cbb7b8 =
         *(int *)PTR__ZN23CGameResourceDownloader15m_ErrorOverSizeE_02cbb7b8 + uVar4;
  }
  uVar1 = (int)lVar11 + *(int *)(param_1 + 0x114);
  *(uint *)(param_1 + 0x114) = uVar1;
  if (uVar1 < *(uint *)(param_1 + 0x110)) {
    *(undefined4 *)(param_1 + 0x118) = 0;
    piVar5 = (int *)
             PTR__ZN23CGameResourceDownloader13CDownloadNode12UnpackNotify15m_DispatchCountE_02cbe960
    ;
  }
  else {
    Aska::File::Close()(param_1 + 0x120);
    lVar11 = param_1 + 8;
    snprintf(auStack_1b0,0x100,&UNK_02866c1b/*"%s.tmp"*/,lVar11);
    uVar8 = Aska::File::MoveFile(char const*, char const*)(auStack_1b0,lVar11);
    if ((uVar8 & 1) == 0) {
      Aska::File::DeleteFile(char const*)(lVar11);
      Aska::File::MoveFile(char const*, char const*)(auStack_1b0,lVar11);
    }
    if (*(long *)(param_1 + 0x138) == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02866a48/*"C:\BAS_Submission\Client\Project\..\Source\Game\Resource\GameResourceDownloader.cpp"*/,0x1205,&UNK_02866c39/*"m_pAssetInfo is null."*/);
    }
    iVar6 = access(lVar11,0);
    uVar10 = 0;
    uVar9 = 0;
    if (iVar6 == 0) {
      stat(lVar11,&uStack_b0);
      uVar10 = uStack_80;
      uVar9 = uStack_58;
    }
    *(undefined4 *)(*(long *)(param_1 + 0x138) + 0x28) = uVar10;
    *(undefined4 *)(*(long *)(param_1 + 0x138) + 0x2c) = uVar9;
    *(undefined4 *)(param_1 + 0x118) = 2;
    piVar5 = (int *)
             PTR__ZN23CGameResourceDownloader13CDownloadNode12UnpackNotify15m_DispatchCountE_02cbe960
    ;
  }
  do {
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar5,0x10);
    if (bVar3) {
      *piVar5 = *piVar5 + -1;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
  if (*piVar5 < 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02866a48/*"C:\BAS_Submission\Client\Project\..\Source\Game\Resource\GameResourceDownloader.cpp"*/,0x1228,&UNK_02866c6f/*"SubDispatchCount too many call?"*/);
  }
  return;
}

// ==== CGameResourceDownloader::CDownloadNode::CDownloadStream::Open(char const*)
// vaddr 0x17e1da0 | ghidra 0x18e1da0 | size 84 | symbol _ZN23CGameResourceDownloader13CDownloadNode15CDownloadStream4OpenEPKc | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN23CGameResourceDownloader13CDownloadNode15CDownloadStream4OpenEPKc(long param_1)

{
  undefined8 uVar1;
  
  *(undefined1 *)(param_1 + 0x1b8) = 0;
  *(undefined8 *)(param_1 + 0x1b0) = 0;
  *(undefined8 *)(param_1 + 0x198) = 0;
  *(undefined8 *)(param_1 + 400) = 0;
  *(undefined8 *)(param_1 + 0x1a8) = 0;
  *(undefined8 *)(param_1 + 0x1a0) = 0;
  if (*(long *)(param_1 + 0x180) != 0) {
    if (*(long *)(param_1 + 0x1c0) == 0) {
      uVar1 = operator new[](unsigned long, std::nothrow_t const&)(*(long *)(param_1 + 0x180),PTR__ZSt7nothrow_02cb9a80);
      *(undefined8 *)(param_1 + 0x1c0) = uVar1;
    }
    *(undefined8 *)(param_1 + 0x188) = 0;
    return 1;
  }
  uVar1 = (*(code *)PTR__ZN4Aska5Yayoi10Downloader14DownloadStream4OpenEPKc_02ca4760)(param_1);
  return uVar1;
}

// ==== CGameResourceDownloader::CDownloadNode::CDownloadStream::IsReady() const
// vaddr 0x17e1df4 | ghidra 0x18e1df4 | size 32 | symbol _ZNK23CGameResourceDownloader13CDownloadNode15CDownloadStream7IsReadyEv | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK23CGameResourceDownloader13CDownloadNode15CDownloadStream7IsReadyEv(long param_1)

{
  if (*(long *)(param_1 + 0x180) != 0) {
    return true;
  }
  return *(long *)(param_1 + 0x20) != 0;
}

// ==== CGameResourceDownloader::CDownloadNode::CDownloadStream::Tell() const
// vaddr 0x17e1e14 | ghidra 0x18e1e14 | size 24 | symbol _ZNK23CGameResourceDownloader13CDownloadNode15CDownloadStream4TellEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK23CGameResourceDownloader13CDownloadNode15CDownloadStream4TellEv(long param_1)

{
  undefined8 uVar1;
  
  if (*(long *)(param_1 + 0x180) != 0) {
    return *(undefined8 *)(param_1 + 0x188);
  }
  uVar1 = (*(code *)PTR__ZNK4Aska10FileStream4TellEv_02cb2738)(param_1 + 8);
  return uVar1;
}

// ==== CGameResourceDownloader::CDownloadNode::CDownloadStream::Seek(long, int)
// vaddr 0x17e1e2c | ghidra 0x18e1e2c | size 24 | symbol _ZN23CGameResourceDownloader13CDownloadNode15CDownloadStream4SeekEli | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN23CGameResourceDownloader13CDownloadNode15CDownloadStream4SeekEli(long param_1)

{
  undefined8 uVar1;
  
  if (*(long *)(param_1 + 0x180) != 0) {
    return 0;
  }
  uVar1 = (*(code *)PTR__ZN4Aska10FileStream4SeekEli_02ca4d68)(param_1 + 8);
  return uVar1;
}

// ==== CGameResourceDownloader::CDownloadNode::CDownloadStream::Read(void*, unsigned long, unsigned long)
// vaddr 0x17e1e44 | ghidra 0x18e1e44 | size 24 | symbol _ZN23CGameResourceDownloader13CDownloadNode15CDownloadStream4ReadEPvmm | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN23CGameResourceDownloader13CDownloadNode15CDownloadStream4ReadEPvmm(long param_1)

{
  undefined8 uVar1;
  
  if (*(long *)(param_1 + 0x180) != 0) {
    return 0;
  }
  uVar1 = (*(code *)PTR__ZN4Aska10FileStream4ReadEPvmm_02c9e0d0)(param_1 + 8);
  return uVar1;
}

// ==== CGameResourceDownloader::CDownloadNode::CDownloadStream::Write(void const*, unsigned long, unsigned long)
// vaddr 0x17e1e5c | ghidra 0x18e1e5c | size 116 | symbol _ZN23CGameResourceDownloader13CDownloadNode15CDownloadStream5WriteEPKvmm | lib libSOA-3.7.0.so | 2026-10-04
long _ZN23CGameResourceDownloader13CDownloadNode15CDownloadStream5WriteEPKvmm
               (long param_1,undefined8 param_2,long param_3,long param_4)

{
  ulong uVar1;
  long lVar2;
  long lVar3;
  
  uVar1 = *(ulong *)(param_1 + 0x180);
  if (uVar1 != 0) {
    param_4 = param_4 * param_3;
    if (param_4 == 0) {
      lVar3 = 0;
    }
    else {
      lVar2 = *(long *)(param_1 + 0x188);
      lVar3 = uVar1 - lVar2;
      if ((ulong)(lVar2 + param_4) <= uVar1) {
        lVar3 = param_4;
      }
      memcpy(*(long *)(param_1 + 0x1c0) + lVar2,param_2,lVar3);
      *(long *)(param_1 + 0x188) = *(long *)(param_1 + 0x188) + lVar3;
    }
    return lVar3;
  }
  lVar3 = (*(code *)PTR__ZN4Aska10FileStream5WriteEPKvmm_02c93088)(param_1 + 8);
  return lVar3;
}

// ==== CGameResourceDownloader::CDownloadNode::CDownloadStream::Flush()
// vaddr 0x17e1ed0 | ghidra 0x18e1ed0 | size 24 | symbol _ZN23CGameResourceDownloader13CDownloadNode15CDownloadStream5FlushEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN23CGameResourceDownloader13CDownloadNode15CDownloadStream5FlushEv(long param_1)

{
  undefined8 uVar1;
  
  if (*(long *)(param_1 + 0x180) != 0) {
    return 0;
  }
  uVar1 = (*(code *)PTR__ZN4Aska10FileStream5FlushEv_02cadfe0)(param_1 + 8);
  return uVar1;
}

// ==== CGameResourceDownloader::CDownloadNode::CDownloadStream::IsEnd(long*) const
// vaddr 0x17e1ee8 | ghidra 0x18e1ee8 | size 32 | symbol _ZNK23CGameResourceDownloader13CDownloadNode15CDownloadStream5IsEndEPl | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZNK23CGameResourceDownloader13CDownloadNode15CDownloadStream5IsEndEPl(long param_1)

{
  ulong uVar1;
  
  if (*(ulong *)(param_1 + 0x180) != 0) {
    return (ulong)(*(ulong *)(param_1 + 0x188) <= *(ulong *)(param_1 + 0x180));
  }
  uVar1 = (*(code *)PTR__ZNK4Aska10FileStream5IsEndEPl_02c9e928)(param_1 + 8);
  return uVar1;
}

// ==== CGameResourceDownloader::CDownloadNode::CDownloadStream::SetLastError(long) const
// vaddr 0x17e1f08 | ghidra 0x18e1f08 | size 32 | symbol _ZNK23CGameResourceDownloader13CDownloadNode15CDownloadStream12SetLastErrorEl | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZNK23CGameResourceDownloader13CDownloadNode15CDownloadStream12SetLastErrorEl
          (long param_1,undefined8 param_2)

{
  if (*(long *)(param_1 + 0x180) != 0) {
    return 0;
  }
  *(undefined8 *)(param_1 + 0x28) = param_2;
  return param_2;
}

// ==== CGameResourceDownloader::CDownloadNode::CDownloadStream::GetLastError() const
// vaddr 0x17e1f28 | ghidra 0x18e1f28 | size 24 | symbol _ZNK23CGameResourceDownloader13CDownloadNode15CDownloadStream12GetLastErrorEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZNK23CGameResourceDownloader13CDownloadNode15CDownloadStream12GetLastErrorEv(long param_1)

{
  if (*(long *)(param_1 + 0x180) != 0) {
    return 0;
  }
  return *(undefined8 *)(param_1 + 0x28);
}

// ==== CGameResourceDownloader::CDownloadNode::CDownloadStream::GetMD5() const
// vaddr 0x17e1f40 | ghidra 0x18e1f40 | size 8 | symbol _ZNK23CGameResourceDownloader13CDownloadNode15CDownloadStream6GetMD5Ev | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK23CGameResourceDownloader13CDownloadNode15CDownloadStream6GetMD5Ev(long param_1)

{
  return param_1 + 400;
}

// ==== CGameResourceDownloader::CVerifyTask::CVerifyTask()
// vaddr 0x17e1f48 | ghidra 0x18e1f48 | size 84 | symbol _ZN23CGameResourceDownloader11CVerifyTaskC1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN23CGameResourceDownloader11CVerifyTaskC2Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN23CGameResourceDownloader11CVerifyTaskE_02cbe2d8 + 0x10);
  param_1[1] = 0;
  memset(param_1 + 2,0,99);
  *(undefined4 *)((long)param_1 + 0x8c) = 0;
  *(undefined8 *)((long)param_1 + 0x74) = 0;
  param_1[0x17] = 0;
  *(undefined8 *)((long)param_1 + 0x84) = 0;
  *(undefined8 *)((long)param_1 + 0x7c) = 0;
  param_1[0x16] = 0;
  param_1[0x15] = 0;
  param_1[0x14] = 0;
  param_1[0x13] = 0;
  *(undefined4 *)(param_1 + 0x18) = 0x3f800000;
  return;
}

// ==== CGameResourceDownloader::CVerifyTask::ProgressLocalFileCheck()
// vaddr 0x17e1f9c | ghidra 0x18e1f9c | size 3020 | symbol _ZN23CGameResourceDownloader11CVerifyTask22ProgressLocalFileCheckEv | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Type propagation algorithm not settling */

void _ZN23CGameResourceDownloader11CVerifyTask22ProgressLocalFileCheckEv(long param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined7 *puVar5;
  ulong uVar6;
  undefined *puVar7;
  bool bVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  undefined4 uVar12;
  ulong uVar13;
  long lVar14;
  long lVar15;
  long lVar16;
  long lVar17;
  long lVar18;
  long lVar19;
  long lVar20;
  ulong uVar21;
  undefined *puVar22;
  undefined *puVar23;
  undefined4 uVar24;
  uint uVar25;
  long lVar26;
  ulong uVar27;
  uint uVar28;
  undefined8 uVar29;
  undefined *puVar30;
  uint uVar31;
  uint uVar32;
  uint uStack_348;
  int iStack_344;
  int iStack_328;
  byte bStack_324;
  undefined *puStack_308;
  ulong uStack_300;
  undefined8 uStack_2f8;
  undefined *puStack_2f0;
  long lStack_2e8;
  byte bStack_2e0;
  int iStack_2d8;
  undefined8 uStack_2d0;
  uint uStack_2b0;
  undefined8 uStack_2a0;
  undefined *puStack_298;
  long *plStack_290;
  undefined8 uStack_288;
  long lStack_280;
  undefined8 uStack_278;
  ushort uStack_266;
  undefined1 auStack_250 [16];
  undefined *puStack_240;
  undefined1 uStack_238;
  byte bStack_230;
  undefined7 uStack_22f;
  ulong uStack_228;
  undefined7 *puStack_220;
  int iStack_218;
  uint uStack_214;
  undefined4 uStack_210;
  uint uStack_20c;
  undefined4 uStack_208;
  byte bStack_200;
  undefined7 uStack_1ff;
  ulong uStack_1f8;
  undefined7 *puStack_1f0;
  undefined *puStack_1e8;
  long *plStack_1e0;
  undefined8 uStack_1d8;
  long lStack_1d0;
  undefined8 uStack_1c8;
  undefined8 uStack_1c0;
  uint uStack_1b8;
  undefined *puStack_1b0;
  undefined1 uStack_1a8;
  long alStack_1a0 [3];
  undefined8 uStack_188;
  byte abStack_180 [16];
  ulong uStack_170;
  undefined1 auStack_164 [260];
  
  if (*(int *)(param_1 + 0xc) == 0) {
    if (*(long *)(param_1 + 0x28) == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02866a48/*"C:\BAS_Submission\Client\Project\..\Source\Game\Resource\GameResourceDownloader.cpp"*/,0x132c,&UNK_02866c8f/*"m_pSearchMap is null."*/);
    }
    BAS::GetDownloadPath()(abStack_180);
    if (*(int *)(*(long *)(param_1 + 0x28) + 8) != 0) {
      puVar1 = PTR__ZTV10CAssetInfo_02cb7ad0 + 0x10;
      puVar2 = PTR__ZTVN4Aska6TArrayI9CMetaInfoLb0EEE_02cba9a0 + 0x10;
      puVar3 = PTR__ZTVN4Aska4FileE_02cb6e28 + 0x10;
      puVar4 = PTR__ZTV9CMetaInfo_02cc00d0 + 0x10;
      uVar28 = 0;
      uVar31 = 0;
      do {
        Framework::CPerformanceCounter::Mark(unsigned int)(0x2b);
        if (*(uint *)(param_1 + 0x74) < *(uint *)(*(long **)(param_1 + 0x28) + 1)) {
          lVar26 = **(long **)(param_1 + 0x28) + (ulong)*(uint *)(param_1 + 0x74) * 0x40;
          lVar20 = lVar26 + 0x28;
        }
        else {
          lVar26 = 0;
          lVar20 = 8;
        }
        uVar29 = *(undefined8 *)(lVar26 + 0x10);
        lVar26 = *(long *)(param_1 + 0x18);
        uStack_300 = 0;
        uStack_2f8 = 0;
        puStack_308 = (undefined *)0x0;
        uStack_188 = uVar29;
        uVar13 = strlen(uVar29);
        if (uVar13 < 0x17) {
          puStack_308 = (undefined *)CONCAT71(puStack_308._1_7_,(char)(uVar13 << 1));
          uVar21 = (ulong)&puStack_308 | 1;
          if (uVar13 != 0) goto code_r0x018e21e0;
        }
        else {
          uVar27 = uVar13 + 0x10 & 0xfffffffffffffff0;
          if (uVar27 == 0) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
          }
          uVar21 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar27,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
          if (uVar21 == 0) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
          }
          puStack_308 = (undefined *)(uVar27 | 1);
          uStack_300 = uVar13;
          uStack_2f8 = uVar21;
code_r0x018e21e0:
          memcpy(uVar21,uVar29,uVar13);
        }
        *(undefined1 *)(uVar21 + uVar13) = 0;
        Aska::THashMap<string, CAssetInfo, Hasher_CSTLString, Aska::TEqualTo<string >, Aska::TAllocator<Aska::TPair<string const, CAssetInfo> > >::Find_(string const&) const(alStack_1a0,lVar26 + 0x58,&puStack_308);
        lVar15 = alStack_1a0[0];
        lVar26 = *(long *)(*(long *)(param_1 + 0x18) + 0x78);
        lVar14 = *(long *)(*(long *)(param_1 + 0x18) + 0x80);
        if (((ulong)puStack_308 & 1) != 0) {
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_2f8);
        }
        if (lVar15 == lVar26 + lVar14 * 0xc0) {
          uStack_238 = 1;
          puStack_220 = (undefined7 *)0x0;
          uStack_228 = 0;
          uStack_22f = 0;
          bStack_230 = 0;
          puStack_1f0 = (undefined7 *)0x0;
          uStack_1f8 = 0;
          uStack_1ff = 0;
          bStack_200 = 0;
          uStack_1d8 = 0;
          plStack_1e0 = (long *)0x0;
          uStack_1c8 = 0;
          lStack_1d0 = 0;
          uStack_1c0 = 8;
          uStack_1b8 = 0;
          uStack_1a8 = 1;
          puStack_1e8 = PTR__ZTV9CMetaList_02cbed68 + 0x10;
          puStack_1b0 = PTR__ZTV9CMetaList_02cbed68 + 0x40;
          puStack_240 = puVar1;
          lVar26 = Aska::ASON::AValue::AMap::Get_(char const*)(lVar20,&UNK_02866ca5/*"md5"*/);
          lVar14 = Aska::ASON::AValue::AMap::Get_(char const*)(lVar20,&UNK_02a3cbab/*"time"*/);
          lVar15 = Aska::ASON::AValue::AMap::Get_(char const*)(lVar20,&UNK_02866f00/*"size"*/);
          lVar16 = Aska::ASON::AValue::AMap::Get_(char const*)(lVar20,&UNK_02866ca9/*"parentHash"*/);
          lVar17 = Aska::ASON::AValue::AMap::Get_(char const*)(lVar20,&UNK_02866cb4/*"flags"*/);
          lVar18 = Aska::ASON::AValue::AMap::Get_(char const*)(lVar20,&UNK_02866cba/*"encType"*/);
          lVar19 = Aska::ASON::AValue::AMap::Get_(char const*)(lVar20,&UNK_02866cc2/*"meta"*/);
          lVar20 = Aska::ASON::AValue::AMap::Get_(char const*)(lVar20,&UNK_02866cc7/*"ep_data"*/);
          if (lVar26 == 0) {
            puVar30 = (undefined *)0x0;
            if (lVar15 != 0) goto code_r0x018e2338;
code_r0x018e2370:
            iStack_344 = 0;
            if (lVar14 != 0) goto code_r0x018e2344;
code_r0x018e2378:
            uStack_348 = 0;
            if (lVar16 != 0) goto code_r0x018e2350;
code_r0x018e2380:
            uVar12 = 0;
            if (lVar17 != 0) goto code_r0x018e2358;
code_r0x018e2388:
            uVar32 = 0;
            if (lVar18 != 0) goto code_r0x018e2360;
code_r0x018e2390:
            uVar24 = 1;
          }
          else {
            puVar30 = *(undefined **)(lVar26 + 0x10);
            if (lVar15 == 0) goto code_r0x018e2370;
code_r0x018e2338:
            iStack_344 = *(int *)(lVar15 + 8);
            if (lVar14 == 0) goto code_r0x018e2378;
code_r0x018e2344:
            uStack_348 = *(uint *)(lVar14 + 8);
            if (lVar16 == 0) goto code_r0x018e2380;
code_r0x018e2350:
            uVar12 = *(undefined4 *)(lVar16 + 8);
            if (lVar17 == 0) goto code_r0x018e2388;
code_r0x018e2358:
            uVar32 = *(uint *)(lVar17 + 8);
            if (lVar18 == 0) goto code_r0x018e2390;
code_r0x018e2360:
            uVar24 = *(undefined4 *)(lVar18 + 8);
          }
          if ((uVar32 & 1) == 0) {
            uVar13 = (ulong)abStack_180 | 1;
            if ((abStack_180[0] & 1) != 0) {
              uVar13 = uStack_170;
            }
            snprintf(auStack_164,0x104,&UNK_02866ccf/*"%s/%s"*/,uVar13,uStack_188);
            iVar10 = access(auStack_164,0);
            iVar11 = access(auStack_164,0);
            iVar9 = 0;
            uVar25 = 0;
            if (iVar11 == 0) {
              stat(auStack_164,&puStack_308);
              iVar9 = iStack_2d8;
              uVar25 = uStack_2b0;
            }
            lVar26 = strstr(uStack_188,&UNK_02862e51/*".sqlite3"*/);
            if ((lVar26 == 0) ||
               (iVar9 == 0 || (uVar25 != uStack_348 || (iVar10 != 0 || iVar9 != iStack_344)))) {
              if (iVar9 == 0 || (uVar25 != uStack_348 || (iVar10 != 0 || iVar9 != iStack_344)))
              goto code_r0x018e2528;
code_r0x018e26b8:
              if (puVar30 == (undefined *)0x0) {
                puVar30 = &UNK_029d2011;
              }
              uVar13 = strlen(puVar30);
              uVar27 = (ulong)bStack_230;
              if ((bStack_230 & 1) == 0) {
                uVar21 = 0x16;
                lVar26 = uVar13 - 0x16;
                if (uVar13 < 0x16 || lVar26 == 0) {
code_r0x018e26e8:
                  puVar5 = &uStack_22f;
                  if ((uVar27 & 1) != 0) {
                    puVar5 = puStack_220;
                  }
                  if (uVar13 != 0) {
                    memmove(puVar5,puVar30,uVar13);
                  }
                  *(undefined1 *)((long)puVar5 + uVar13) = 0;
                  if ((bStack_230 & 1) != 0) goto joined_r0x018e25c8;
                  bStack_230 = (byte)(uVar13 << 1);
                  goto joined_r0x018e2554;
                }
              }
              else {
                uVar27 = CONCAT71(uStack_22f,bStack_230);
                uVar21 = (uVar27 & 0xfffffffffffffffe) - 1;
                lVar26 = uVar13 - uVar21;
                if (uVar13 < uVar21 || lVar26 == 0) goto code_r0x018e26e8;
              }
              uVar6 = (ulong)(((uint)uVar27 & 0xfe) >> 1);
              if ((uVar27 & 1) != 0) {
                uVar6 = uStack_228;
              }
              string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&bStack_230,uVar21,lVar26,uVar6,0,uVar6,uVar13,puVar30);
            }
            else {
              uStack_300 = uStack_300 & 0xffffffffffffff00;
              uStack_2f8 = 0;
              puStack_308 = puVar3;
              uVar13 = Aska::File::Open(char const*, bool, bool, bool)(&puStack_308,auStack_164,1,0,0);
              bVar8 = false;
              if ((uVar13 & 1) != 0) {
                Aska::File::Read(void*, unsigned long, unsigned int*)(&puStack_308,&iStack_328,0x10,0);
                if ((iStack_328 == 0x444c4441) && ((bStack_324 >> 1 & 1) != 0)) {
                  bVar8 = false;
                }
                else {
                  bVar8 = true;
                }
                Aska::File::Close()(&puStack_308);
              }
              puStack_308 = PTR__ZTVN4Aska4FileE_02cb6e28 + 0x10;
              if (uStack_2f8 != 0) {
                Aska::File::Close()(&puStack_308);
              }
              if (!bVar8) goto code_r0x018e26b8;
code_r0x018e2528:
              *(undefined1 *)(param_1 + 0x72) = 1;
              puVar5 = &uStack_22f;
              if ((bStack_230 & 1) != 0) {
                puVar5 = puStack_220;
              }
              *(undefined1 *)puVar5 = 0;
              if ((bStack_230 & 1) != 0) {
                uStack_228 = 0;
                uVar13 = uStack_228;
                goto joined_r0x018e25c8;
              }
              bStack_230 = 0;
            }
joined_r0x018e2554:
            if (lVar20 == 0) goto code_r0x018e2778;
code_r0x018e25cc:
            lVar20 = *(long *)(lVar20 + 0x10);
            if (lVar20 == 0) goto code_r0x018e2778;
            uVar13 = strlen(lVar20);
            uVar27 = (ulong)bStack_200;
            if ((bStack_200 & 1) == 0) {
              uVar21 = 0x16;
              lVar26 = uVar13 - 0x16;
              if (0x15 < uVar13 && lVar26 != 0) goto code_r0x018e2644;
code_r0x018e25f4:
              puVar5 = &uStack_1ff;
              if ((uVar27 & 1) != 0) {
                puVar5 = puStack_1f0;
              }
              if (uVar13 != 0) {
                memmove(puVar5,lVar20,uVar13);
              }
              *(undefined1 *)((long)puVar5 + uVar13) = 0;
              if ((bStack_200 & 1) == 0) {
                bStack_200 = (byte)(uVar13 << 1);
                uVar13 = uStack_1f8;
              }
            }
            else {
              uVar27 = CONCAT71(uStack_1ff,bStack_200);
              uVar21 = (uVar27 & 0xfffffffffffffffe) - 1;
              lVar26 = uVar13 - uVar21;
              if (uVar13 < uVar21 || lVar26 == 0) goto code_r0x018e25f4;
code_r0x018e2644:
              uVar6 = (ulong)(((uint)uVar27 & 0xfe) >> 1);
              if ((uVar27 & 1) != 0) {
                uVar6 = uStack_1f8;
              }
              string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&bStack_200,uVar21,lVar26,uVar6,0,uVar6,uVar13,lVar20);
              uVar13 = uStack_1f8;
            }
          }
          else {
            if (puVar30 == (undefined *)0x0) {
              puVar30 = &UNK_029d2011;
            }
            uVar27 = strlen(puVar30);
            uVar13 = (ulong)bStack_230;
            if ((bStack_230 & 1) == 0) {
              uVar21 = 0x16;
              lVar26 = uVar27 - 0x16;
              if (0x15 < uVar27 && lVar26 != 0) goto code_r0x018e2570;
code_r0x018e24e8:
              puVar5 = &uStack_22f;
              if ((uVar13 & 1) != 0) {
                puVar5 = puStack_220;
              }
              if (uVar27 != 0) {
                memmove(puVar5,puVar30,uVar27);
              }
              *(undefined1 *)((long)puVar5 + uVar27) = 0;
              if ((bStack_230 & 1) == 0) {
                bStack_230 = (byte)(uVar27 << 1);
                uVar27 = uStack_228;
              }
            }
            else {
              uVar13 = CONCAT71(uStack_22f,bStack_230);
              uVar21 = (uVar13 & 0xfffffffffffffffe) - 1;
              lVar26 = uVar27 - uVar21;
              if (uVar27 < uVar21 || lVar26 == 0) goto code_r0x018e24e8;
code_r0x018e2570:
              uVar6 = (ulong)(((uint)uVar13 & 0xfe) >> 1);
              if ((uVar13 & 1) != 0) {
                uVar6 = uStack_228;
              }
              string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&bStack_230,uVar21,lVar26,uVar6,0,uVar6,uVar27,puVar30);
              uVar27 = uStack_228;
            }
            uStack_228 = uVar27;
            Framework::CHash32::CHash32(char const*)(auStack_250,uStack_188);
            uVar12 = Framework::CHash32::operator unsigned int() const(auStack_250);
            Framework::CHash32::~CHash32()(auStack_250);
            uVar32 = 1;
            uVar13 = uStack_228;
joined_r0x018e25c8:
            uStack_228 = uVar13;
            if (lVar20 != 0) goto code_r0x018e25cc;
code_r0x018e2778:
            puVar5 = &uStack_1ff;
            if ((bStack_200 & 1) != 0) {
              puVar5 = puStack_1f0;
            }
            *(undefined1 *)puVar5 = 0;
            if ((bStack_200 & 1) == 0) {
              bStack_200 = 0;
              uVar13 = uStack_1f8;
            }
            else {
              uStack_1f8 = 0;
              uVar13 = uStack_1f8;
            }
          }
          uStack_1f8 = uVar13;
          iStack_218 = iStack_344;
          uStack_214 = uStack_348;
          uStack_210 = uVar12;
          uStack_20c = uVar32;
          uStack_208 = uVar24;
          if ((lVar19 != 0) && (*(int *)(lVar19 + 0x10) != 0)) {
            uVar32 = 0;
            do {
              uStack_300 = CONCAT71(uStack_300._1_7_,1);
              puStack_2f0 = (undefined *)0x0;
              lStack_2e8 = 0;
              uStack_2f8 = 0;
              lVar20 = 0;
              if (uVar32 < *(uint *)(lVar19 + 0x10)) {
                lVar20 = *(long *)(lVar19 + 8) + (ulong)uVar32 * 0x20;
              }
              puStack_308 = puVar4;
              lVar20 = Aska::ASON::AValue::AMap::Get_(char const*)(lVar20 + 8,&UNK_029d62d5/*"param"*/);
              if (lVar20 == 0) {
                uVar29 = 0;
              }
              else {
                uVar29 = *(undefined8 *)(lVar20 + 0x10);
              }
              puVar30 = (undefined *)strlen(uVar29);
              if ((uStack_2f8 & 1) == 0) {
                puVar22 = (undefined *)0x16;
                puVar23 = puVar30 + -0x16;
                uVar13 = uStack_2f8 & 0xff;
                if ((undefined *)0x15 < puVar30 && puVar23 != (undefined *)0x0)
                goto code_r0x018e289c;
code_r0x018e284c:
                lVar20 = (long)&uStack_2f8 + 1;
                if ((uVar13 & 1) != 0) {
                  lVar20 = lStack_2e8;
                }
                if (puVar30 != (undefined *)0x0) {
                  memmove(lVar20,uVar29,puVar30);
                }
                puVar30[lVar20] = 0;
                if ((uStack_2f8 & 1) == 0) {
                  uStack_2f8 = CONCAT71(uStack_2f8._1_7_,(char)((long)puVar30 << 1));
                  puVar30 = puStack_2f0;
                }
              }
              else {
                puVar22 = (undefined *)((uStack_2f8 & 0xfffffffffffffffe) - 1);
                puVar23 = puVar30 + -(long)puVar22;
                uVar13 = uStack_2f8;
                if (puVar30 < puVar22 || puVar23 == (undefined *)0x0) goto code_r0x018e284c;
code_r0x018e289c:
                puVar7 = (undefined *)(ulong)(((uint)uVar13 & 0xfe) >> 1);
                if ((uVar13 & 1) != 0) {
                  puVar7 = puStack_2f0;
                }
                string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&uStack_2f8,puVar22,puVar23,puVar7,0,puVar7,puVar30,uVar29);
                puVar30 = puStack_2f0;
              }
              puStack_2f0 = puVar30;
              Aska::TArray<CMetaInfo, false>::SetAt(long, CMetaInfo const&)(&puStack_1e8,lStack_1d0,&puStack_308);
              puStack_308 = PTR__ZTV9CMetaInfo_02cc00d0 + 0x10;
              if ((uStack_2f8 & 1) != 0) {
                Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(lStack_2e8);
              }
              uVar32 = uVar32 + 1;
            } while (uVar32 < *(uint *)(lVar19 + 0x10));
          }
          lVar20 = *(long *)(param_1 + 0x18);
          Aska::TPair<string const, CAssetInfo>::TPair<char const*, CAssetInfo>(char const* const&, CAssetInfo const&)(&puStack_308,&uStack_188,&puStack_240);
          uVar13 = (ulong)((float)((ulong)*(uint *)(lVar20 + 0x68) + (ulong)*(uint *)(lVar20 + 0x6c)
                                  + 1) / *(float *)(lVar20 + 100));
          if (*(ulong *)(lVar20 + 0x80) < uVar13) {
            Aska::THashMap<string, CAssetInfo, Hasher_CSTLString, Aska::TEqualTo<string >, Aska::TAllocator<Aska::TPair<string const, CAssetInfo> > >::Rehash_(unsigned long)(lVar20 + 0x58,uVar13 << 1 | 1);
          }
          Aska::THashMap<string, CAssetInfo, Hasher_CSTLString, Aska::TEqualTo<string >, Aska::TAllocator<Aska::TPair<string const, CAssetInfo> > >::Insert_(Aska::TPair<string const, CAssetInfo> const&)(&iStack_328,lVar20 + 0x58,&puStack_308);
          puStack_2f0 = PTR__ZTV10CAssetInfo_02cb7ad0 + 0x10;
          uStack_266 = uStack_266 | 1;
          puStack_298 = puVar2;
          if (((plStack_290 != (long *)0x0) && (0 < lStack_280)) &&
             ((**(code **)(*plStack_290 + 0x10))(), 1 < lStack_280)) {
            lVar26 = 0x28;
            lVar20 = 1;
            do {
              (**(code **)(*(long *)((long)plStack_290 + lVar26) + 0x10))();
              lVar20 = lVar20 + 1;
              lVar26 = lVar26 + 0x28;
            } while (lVar20 < lStack_280);
          }
          if ((uStack_266 & 1) != 0) {
            if (plStack_290 != (long *)0x0) {
              operator delete[](void*)();
              plStack_290 = (long *)0x0;
            }
            uStack_288 = 0;
          }
          lStack_280 = 0;
          uStack_278 = 0;
          if ((uStack_2b0 & 1) != 0) {
            Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_2a0);
          }
          if ((bStack_2e0 & 1) != 0) {
            Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_2d0);
          }
          if (((ulong)puStack_308 & 1) != 0) {
            Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_2f8);
          }
          puStack_240 = PTR__ZTV10CAssetInfo_02cb7ad0 + 0x10;
          puStack_1e8 = PTR__ZTVN4Aska6TArrayI9CMetaInfoLb0EEE_02cba9a0 + 0x10;
          uStack_1b8 = uStack_1b8 | 0x10000;
          if (((plStack_1e0 != (long *)0x0) && (0 < lStack_1d0)) &&
             ((**(code **)(*plStack_1e0 + 0x10))(), 1 < lStack_1d0)) {
            lVar26 = 0x28;
            lVar20 = 1;
            do {
              (**(code **)(*(long *)((long)plStack_1e0 + lVar26) + 0x10))();
              lVar20 = lVar20 + 1;
              lVar26 = lVar26 + 0x28;
            } while (lVar20 < lStack_1d0);
          }
          if ((uStack_1b8 & 0x10000) != 0) {
            if (plStack_1e0 != (long *)0x0) {
              operator delete[](void*)();
              plStack_1e0 = (long *)0x0;
            }
            uStack_1d8 = 0;
          }
          uStack_1c8 = 0;
          if ((bStack_200 & 1) != 0) {
            Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puStack_1f0);
          }
          if ((bStack_230 & 1) != 0) {
            Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puStack_220);
          }
        }
        Framework::CPerformanceCounter::Set(unsigned int)(0x2b);
        uVar32 = *(int *)(param_1 + 0x74) + 1;
        *(uint *)(param_1 + 0x74) = uVar32;
        if (*(uint *)(*(long *)(param_1 + 0x28) + 8) <= uVar32) {
          *(undefined1 *)(param_1 + 0x71) = 1;
          *(int *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) + 1;
          break;
        }
        iVar9 = Framework::CPerformanceCounter::Get(unsigned int)(0x2b);
        uVar28 = iVar9 + uVar28;
        if ((0x270 < uVar28 >> 4) ||
           (uVar31 = uVar31 + 1, *(uint *)(*(long *)(param_1 + 0x28) + 8) <= uVar31)) break;
      } while( true );
    }
    if ((abStack_180[0] & 1) != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_170);
    }
  }
  return;
}

// ==== CGameResourceDownloader::CVerifyTask::ProgressServerManifestCheck()
// vaddr 0x17e2b68 | ghidra 0x18e2b68 | size 1136 | symbol _ZN23CGameResourceDownloader11CVerifyTask27ProgressServerManifestCheckEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN23CGameResourceDownloader11CVerifyTask27ProgressServerManifestCheckEv(long param_1)

{
  bool bVar1;
  long *plVar2;
  int iVar3;
  char cVar4;
  undefined *puVar5;
  ulong uVar6;
  undefined4 uVar7;
  undefined4 *puVar8;
  long lVar9;
  long lVar10;
  ulong uVar11;
  undefined8 uVar12;
  uint uVar13;
  undefined4 *puVar14;
  undefined4 uStack_38;
  undefined4 uStack_34;
  
  puVar5 = PTR__ZN9Framework10TSingletonI20CGameResourceManagerE11m_pInstanceE_02cc2018;
  iVar3 = *(int *)(param_1 + 0xc);
  switch(iVar3) {
  case 0:
    lVar9 = *(long *)PTR__ZN9Framework10TSingletonI20CGameResourceManagerE11m_pInstanceE_02cc2018;
    if (lVar9 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
      lVar9 = *(long *)puVar5;
    }
    cVar4 = *(char *)(*(long *)(lVar9 + 0x20) + 0x155);
    *(undefined4 *)(param_1 + 0x74) = 0;
    if (cVar4 == '\0') {
      uVar7 = 4;
    }
    else {
      puVar14 = *(undefined4 **)(param_1 + 0x78);
      puVar8 = *(undefined4 **)(param_1 + 0x80);
      if (puVar8 != puVar14) {
        puVar14 = (undefined4 *)
                  ((long)puVar8 + (~((long)puVar8 + (-4 - (long)puVar14)) & 0xfffffffffffffffcU));
        *(undefined4 **)(param_1 + 0x80) = puVar14;
      }
      lVar9 = *(long *)(param_1 + 0x40) - *(long *)(param_1 + 0x38);
      if ((lVar9 != 0) && (*(long *)(param_1 + 0x38) != *(long *)(param_1 + 0x40))) {
        while( true ) {
          lVar9 = lVar9 + -8;
          uStack_34 = 0;
          if (puVar14 < *(undefined4 **)(param_1 + 0x88)) {
            if (puVar14 == (undefined4 *)0x0) {
              Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
            }
            else {
              uStack_34 = 0;
            }
            *puVar14 = uStack_34;
            *(long *)(param_1 + 0x80) = *(long *)(param_1 + 0x80) + 4;
          }
          else {
            void std::__ndk1::vector<unsigned int, Framework::CSTLAllocator<unsigned int, Framework::CSTLVectorAllocatorInf> >::__push_back_slow_path<unsigned int>(unsigned int&&)((undefined8 *)(param_1 + 0x78),&uStack_34);
          }
          if (lVar9 == 0) break;
          puVar14 = *(undefined4 **)(param_1 + 0x80);
        }
      }
      lVar9 = *(long *)(param_1 + 0x60);
      *(undefined4 *)(param_1 + 0x90) = 0;
      *(undefined8 *)(param_1 + 0x50) = 0;
      if (lVar9 != *(long *)(param_1 + 0x58)) {
        *(ulong *)(param_1 + 0x60) =
             lVar9 + (~((lVar9 + -4) - *(long *)(param_1 + 0x58)) & 0xfffffffffffffffcU);
      }
      uVar7 = 1;
    }
    break;
  case 1:
  case 5:
    lVar9 = *(long *)(param_1 + 0x38);
    lVar10 = *(long *)(param_1 + 0x40) - lVar9;
    if (lVar10 != 0) {
      uVar11 = (ulong)*(uint *)(param_1 + 0x90);
      uVar6 = uVar11;
      if ((ulong)(lVar10 >> 3) <= uVar11) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dc536/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Vector.h"*/,0x58,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,uVar11);
        lVar9 = *(long *)(param_1 + 0x38);
        uVar6 = (ulong)*(uint *)(param_1 + 0x90);
      }
      lVar10 = *(long *)(param_1 + 0x78);
      uVar12 = *(undefined8 *)(lVar9 + uVar11 * 8);
      if ((ulong)(*(long *)(param_1 + 0x80) - lVar10 >> 2) <= uVar6) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dc536/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Vector.h"*/,0x58,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,uVar6);
        lVar10 = *(long *)(param_1 + 0x78);
      }
      uVar6 = CGameResourceDownloader::CVerifyTask::ProgressManifestCheck(bool, Aska::ASON::AValue::AMap const*, unsigned int*)(param_1,iVar3 == 1,uVar12,lVar10 + uVar6 * 4);
      if ((uVar6 & 1) == 0) {
        return;
      }
      uVar13 = *(int *)(param_1 + 0x90) + 1;
      *(uint *)(param_1 + 0x90) = uVar13;
      if ((ulong)uVar13 < (ulong)(*(long *)(param_1 + 0x40) - *(long *)(param_1 + 0x38) >> 3)) {
        *(undefined4 *)(param_1 + 0x74) = 0;
        return;
      }
    }
    if (iVar3 != 1) {
      *(undefined1 *)(param_1 + 0x71) = 1;
      *(undefined4 *)(param_1 + 0xc) = 6;
      return;
    }
    *(undefined4 *)(param_1 + 0x74) = 0;
    uVar7 = 2;
    break;
  case 2:
    uVar6 = CGameResourceDownloader::CVerifyTask::ProgressManifestCheck(bool, Aska::ASON::AValue::AMap const*, unsigned int*)(param_1,1,*(undefined8 *)(param_1 + 0x28),param_1 + 0x50);
    if ((uVar6 & 1) == 0) {
      return;
    }
    *(undefined4 *)(param_1 + 0x74) = 0;
    uVar7 = 3;
    break;
  case 3:
    uVar6 = CGameResourceDownloader::CVerifyTask::ProgressManifestCheck(bool, Aska::ASON::AValue::AMap const*, unsigned int*)(param_1,1,*(undefined8 *)(param_1 + 0x30),param_1 + 0x54);
    if ((uVar6 & 1) == 0) {
      return;
    }
    lVar9 = *(long *)(param_1 + 0x78);
    lVar10 = *(long *)(param_1 + 0x80);
    uVar13 = *(uint *)(param_1 + 0x54);
    *(undefined4 *)(param_1 + 0x74) = 0;
    *(undefined4 *)(param_1 + 0xc) = 4;
    if (lVar10 != lVar9) {
      uVar6 = 0;
      uVar11 = 1;
      do {
        if ((ulong)(lVar10 - lVar9 >> 2) <= uVar6) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dc536/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Vector.h"*/,0x58,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,uVar6);
          lVar9 = *(long *)(param_1 + 0x78);
          lVar10 = *(long *)(param_1 + 0x80);
        }
        uVar13 = *(int *)(lVar9 + uVar6 * 4) + uVar13;
        if ((ulong)(lVar10 - lVar9 >> 2) <= uVar6) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dc536/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Vector.h"*/,0x58,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,uVar6);
          lVar9 = *(long *)(param_1 + 0x78);
          lVar10 = *(long *)(param_1 + 0x80);
        }
        bVar1 = uVar11 < (ulong)(lVar10 - lVar9 >> 2);
        uVar6 = uVar11;
        uVar11 = (ulong)((int)uVar11 + 1);
      } while (bVar1);
    }
    if (799 < uVar13) {
      return;
    }
    *(undefined1 *)(param_1 + 0x70) = 1;
    return;
  case 4:
    plVar2 = (long *)(param_1 + 0x30);
    if (*(char *)(param_1 + 0x70) == '\0') {
      plVar2 = (long *)(param_1 + 0x28);
    }
    lVar9 = *plVar2;
    if (lVar9 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02866a48/*"C:\BAS_Submission\Client\Project\..\Source\Game\Resource\GameResourceDownloader.cpp"*/,0x1442,&UNK_02866c91/*"pSearchMap is null."*/);
    }
    uVar6 = CGameResourceDownloader::CVerifyTask::ProgressManifestCheck(bool, Aska::ASON::AValue::AMap const*, unsigned int*)(param_1,0,lVar9,0);
    if ((uVar6 & 1) == 0) {
      return;
    }
    puVar14 = *(undefined4 **)(param_1 + 0x78);
    puVar8 = *(undefined4 **)(param_1 + 0x80);
    *(undefined4 *)(param_1 + 0x74) = 0;
    if (puVar8 != puVar14) {
      puVar14 = (undefined4 *)
                ((long)puVar8 + (~((long)puVar8 + (-4 - (long)puVar14)) & 0xfffffffffffffffcU));
      *(undefined4 **)(param_1 + 0x80) = puVar14;
    }
    lVar9 = *(long *)(param_1 + 0x40) - *(long *)(param_1 + 0x38);
    if ((lVar9 != 0) && (*(long *)(param_1 + 0x38) != *(long *)(param_1 + 0x40))) {
      while( true ) {
        lVar9 = lVar9 + -8;
        uStack_38 = 0;
        if (puVar14 < *(undefined4 **)(param_1 + 0x88)) {
          if (puVar14 == (undefined4 *)0x0) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
          }
          else {
            uStack_38 = 0;
          }
          *puVar14 = uStack_38;
          *(long *)(param_1 + 0x80) = *(long *)(param_1 + 0x80) + 4;
        }
        else {
          void std::__ndk1::vector<unsigned int, Framework::CSTLAllocator<unsigned int, Framework::CSTLVectorAllocatorInf> >::__push_back_slow_path<unsigned int>(unsigned int&&)((undefined8 *)(param_1 + 0x78),&uStack_38);
        }
        if (lVar9 == 0) break;
        puVar14 = *(undefined4 **)(param_1 + 0x80);
      }
    }
    uVar7 = 5;
    *(undefined4 *)(param_1 + 0x90) = 0;
    break;
  default:
    goto code_r0x018e2fc4;
  }
  *(undefined4 *)(param_1 + 0xc) = uVar7;
code_r0x018e2fc4:
  return;
}

// ==== CGameResourceDownloader::CVerifyTask::ProgressEraseCheck()
// vaddr 0x17e2fd8 | ghidra 0x18e2fd8 | size 1960 | symbol _ZN23CGameResourceDownloader11CVerifyTask18ProgressEraseCheckEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN23CGameResourceDownloader11CVerifyTask18ProgressEraseCheckEv(long param_1)

{
  long lVar1;
  uint uVar2;
  bool bVar3;
  long *plVar4;
  long lVar5;
  ulong uVar6;
  ulong uVar7;
  ulong uVar8;
  int iVar9;
  long lVar10;
  long lVar11;
  long lVar12;
  undefined1 *puVar13;
  ulong uVar14;
  ulong uVar15;
  ulong uStack_2e0;
  ulong uStack_2d8;
  ulong uStack_2d0;
  ulong uStack_1e0;
  undefined8 uStack_1d8;
  undefined8 uStack_1d0;
  ulong uStack_1c8;
  ulong uStack_1c0;
  ulong uStack_1b8;
  ulong uStack_1b0;
  ulong uStack_1a8;
  undefined1 *puStack_1a0;
  byte abStack_190 [8];
  ulong uStack_188;
  ulong uStack_180;
  ulong uStack_178;
  undefined8 uStack_170;
  ulong uStack_168;
  ulong uStack_78;
  ulong uStack_70;
  long lStack_68;
  
  if (*(int *)(param_1 + 0xc) != 1) {
    if (*(int *)(param_1 + 0xc) != 0) {
      return;
    }
    BAS::GetDownloadPath()(&uStack_2e0);
    uVar7 = (ulong)&uStack_2e0 | 1;
    if ((uStack_2e0 & 1) != 0) {
      uVar7 = uStack_2d0;
    }
    lStack_68 = 0;
    uStack_78 = 0;
    uStack_70 = 0;
    std::__ndk1::unordered_map<unsigned int, bool, std::__ndk1::hash<unsigned int>, std::__ndk1::equal_to<unsigned int>, Framework::CSTLAllocator<std::__ndk1::pair<unsigned int const, bool>, Framework::CSTLUnorderedMapAllocatorInf> >::operator[](unsigned int&&)+0x1f4(uVar7,&uStack_78,1);
    if (*(long *)(param_1 + 0x98) != 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02866a48/*"C:\BAS_Submission\Client\Project\..\Source\Game\Resource\GameResourceDownloader.cpp"*/,0x1586,&UNK_02866d01/*"m_pFindDataList isn't null.(%08x)"*/);
    }
    plVar4 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x18,PTR__ZSt7nothrow_02cb9a80);
    if (plVar4 != (long *)0x0) {
      plVar4[1] = 0;
      plVar4[2] = 0;
      *plVar4 = 0;
    }
    *(long **)(param_1 + 0x98) = plVar4;
    lVar10 = *plVar4;
    uVar14 = (long)(uStack_70 - uStack_78) >> 8;
    uVar7 = uStack_78;
    uVar6 = uStack_70;
    if ((ulong)(plVar4[2] - lVar10 >> 8) < uVar14) {
      lVar11 = plVar4[1];
      lVar5 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uStack_70 - uStack_78,&UNK_027dc536/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Vector.h"*/,0x20);
      if (lVar5 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
      }
      lVar1 = *plVar4;
      lVar12 = plVar4[1];
      lVar10 = lVar5 + (lVar11 - lVar10 >> 8) * 0x100;
      lVar11 = lVar10;
      while (lVar12 != lVar1) {
        lVar12 = lVar12 + -0x100;
        memcpy(lVar11 + -0x100,lVar12,0x100);
        lVar11 = lVar11 + -0x100;
      }
      *plVar4 = lVar11;
      plVar4[1] = lVar10;
      plVar4[2] = lVar5 + uVar14 * 0x100;
      uVar7 = uStack_78;
      uVar6 = uStack_70;
      if (lVar1 != 0) {
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(lVar1);
        uVar7 = uStack_78;
        uVar6 = uStack_70;
      }
    }
    for (; uVar14 = uStack_70, uVar7 != uStack_70; uVar7 = uVar7 + 0x100) {
      uStack_70 = uVar6;
      uVar6 = strlen(uVar7);
      if (0xff < uVar6) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dc32f/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/Utility.h"*/,0x77,&UNK_027dc380/*"gStrcpy() : destination buffer is small. ( %d < %d )"*/,uVar6,0x100);
      }
      strcpy(&uStack_178,uVar7);
      lVar5 = *(long *)(param_1 + 0x98);
      lVar10 = *(long *)(lVar5 + 8);
      if (lVar10 == *(long *)(lVar5 + 0x10)) {
        void std::__ndk1::vector<CGameResourceDownloader::CVerifyTask::tFolderInfo, Framework::CSTLAllocator<CGameResourceDownloader::CVerifyTask::tFolderInfo, Framework::CSTLVectorAllocatorInf> >::__push_back_slow_path<CGameResourceDownloader::CVerifyTask::tFolderInfo const&>(CGameResourceDownloader::CVerifyTask::tFolderInfo const&)(lVar5,&uStack_178);
      }
      else {
        if (lVar10 == 0) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
        }
        memcpy(lVar10,&uStack_178,0x100);
        *(long *)(lVar5 + 8) = *(long *)(lVar5 + 8) + 0x100;
      }
      uVar6 = uStack_70;
      uStack_70 = uVar14;
    }
    *(undefined4 *)(param_1 + 0x74) = 0;
    *(int *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) + 1;
    uStack_70 = uVar6;
    if (uStack_78 != 0) {
      if (uVar6 - uStack_78 != 0) {
        uStack_70 = uVar6 + (~((uVar6 - uStack_78) - 0x100) & 0xffffffffffffff00);
      }
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_78);
    }
    uVar7 = uStack_2d0;
    if ((uStack_2e0 & 1) == 0) {
      return;
    }
    goto code_r0x018e3738;
  }
  plVar4 = *(long **)(param_1 + 0x98);
  uVar2 = *(uint *)(param_1 + 0x74);
  lVar10 = *plVar4;
  if ((ulong)(plVar4[1] - lVar10 >> 8) <= (ulong)uVar2) {
    if (plVar4 == (long *)0x0) {
      iVar9 = 2;
    }
    else {
      if (*plVar4 != 0) {
        lVar10 = plVar4[1] - *plVar4;
        if (lVar10 != 0) {
          plVar4[1] = plVar4[1] + (~(lVar10 - 0x100U) & 0xffffffffffffff00);
        }
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)();
      }
      operator delete(void*)(plVar4);
      *(undefined8 *)(param_1 + 0x98) = 0;
      iVar9 = *(int *)(param_1 + 0xc) + 1;
    }
    *(int *)(param_1 + 0xc) = iVar9;
    *(undefined1 *)(param_1 + 0x71) = 1;
    return;
  }
  lStack_68 = 0;
  uStack_70 = 0;
  uStack_78 = 0;
  uVar7 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(0x10000,&UNK_027dc536/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Vector.h"*/,0x20);
  if (uVar7 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
  }
  lStack_68 = uVar7 + 0x10000;
  lVar10 = lVar10 + (ulong)uVar2 * 0x100;
  uStack_78 = uVar7;
  uStack_70 = uVar7;
  std::__ndk1::unordered_map<unsigned int, bool, std::__ndk1::hash<unsigned int>, std::__ndk1::equal_to<unsigned int>, Framework::CSTLAllocator<std::__ndk1::pair<unsigned int const, bool>, Framework::CSTLUnorderedMapAllocatorInf> >::operator[](unsigned int&&)+0x1f4(lVar10,&uStack_78,0);
  if (uStack_78 != uStack_70) {
    BAS::GetDownloadPath()(abStack_190);
    uStack_1a8 = 0;
    puStack_1a0 = (undefined1 *)0x0;
    uStack_1b0 = 0;
    uVar7 = strlen(lVar10);
    if (uVar7 < 0x17) {
      puVar13 = (undefined1 *)((ulong)&uStack_1b0 | 1);
      uStack_1b0 = CONCAT71(uStack_1b0._1_7_,(char)(uVar7 << 1));
      if (uVar7 != 0) goto code_r0x018e33d4;
    }
    else {
      uVar6 = uVar7 + 0x10 & 0xfffffffffffffff0;
      if (uVar6 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
      }
      puVar13 = (undefined1 *)Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar6,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
      if (puVar13 == (undefined1 *)0x0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
      }
      uStack_1b0 = uVar6 | 1;
      uStack_1a8 = uVar7;
      puStack_1a0 = puVar13;
code_r0x018e33d4:
      memcpy(puVar13,lVar10,uVar7);
    }
    puVar13[uVar7] = 0;
    uVar7 = (ulong)abStack_190 | 1;
    uVar6 = (ulong)(abStack_190[0] >> 1);
    if ((abStack_190[0] & 1) != 0) {
      uVar7 = uStack_180;
      uVar6 = uStack_188;
    }
    uStack_1c0 = 0;
    uStack_1b8 = 0;
    uStack_1c8 = 0x2f02;
    if (uVar6 < 0x15 || uVar6 - 0x15 == 0) {
      if (uVar6 != 0) {
        uVar15 = (ulong)&uStack_1c8 | 1;
        uVar14 = uVar7 + uVar6;
        if (((ulong)&uStack_1c8 | 2) <= uVar7 || uVar7 < ((ulong)&uStack_1c8 | 1)) {
          uVar14 = uVar7;
        }
        *(undefined1 *)(uVar15 + uVar6) = 0x2f;
        memmove((ulong)&uStack_1c8 | 1,uVar14,uVar6);
        uStack_1c8 = CONCAT71(uStack_1c8._1_7_,(char)(uVar6 + 1) * '\x02');
        *(undefined1 *)(uVar15 + uVar6 + 1) = 0;
      }
    }
    else {
      string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&uStack_1c8,0x16,uVar6 - 0x15,1,0,0,uVar6);
    }
    uStack_2d8 = uStack_1c0;
    uStack_2e0 = uStack_1c8;
    uStack_2d0 = uStack_1b8;
    uStack_1c0 = 0;
    uStack_1b8 = 0;
    uStack_1d0 = 0;
    uStack_1c8 = 0;
    uStack_1e0 = 0;
    uStack_1d8 = 0;
    Framework::CSTLStringUtility_Base<string >::Replace(string const&, string const&, string const&, bool*)(&uStack_178,&uStack_1b0,&uStack_2e0,&uStack_1e0,0);
    if ((uStack_1b0 & 1) == 0) {
      uStack_1b0 = uStack_1b0 & 0xffffffffffff0000;
    }
    else {
      *puStack_1a0 = 0;
      uStack_1a8 = 0;
    }
    string::reserve(unsigned long)(&uStack_1b0,0);
    puStack_1a0 = (undefined1 *)uStack_168;
    uStack_1a8 = uStack_170;
    uStack_1b0 = uStack_178;
    uStack_170 = 0;
    uStack_168 = 0;
    uStack_178 = 0;
    if ((uStack_1e0 & 1) != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_1d0);
    }
    if ((uStack_2e0 & 1) != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_2d0);
    }
    if ((uStack_1c8 & 1) != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_1b8);
    }
    uVar7 = uStack_70;
    bVar3 = (uStack_1b0 & 1) == 0;
    if (uStack_78 != uStack_70) {
      uVar6 = uStack_78;
      do {
        puVar13 = (undefined1 *)((ulong)&uStack_1b0 | 1);
        if (!bVar3) {
          puVar13 = puStack_1a0;
        }
        snprintf(&uStack_178,0x100,&UNK_02866ccf/*"%s/%s"*/,puVar13,uVar6);
        lVar10 = *(long *)(param_1 + 0x18);
        uStack_2d8 = 0;
        uStack_2d0 = 0;
        uStack_2e0 = 0;
        uVar14 = strlen(&uStack_178);
        if (uVar14 < 0x17) {
          uStack_2e0 = CONCAT71(uStack_2e0._1_7_,(char)(uVar14 << 1));
          uVar8 = (ulong)&uStack_2e0 | 1;
          if (uVar14 != 0) goto code_r0x018e361c;
        }
        else {
          uVar15 = uVar14 + 0x10 & 0xfffffffffffffff0;
          if (uVar15 == 0) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
          }
          uVar8 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar15,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
          if (uVar8 == 0) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
          }
          uStack_2e0 = uVar15 | 1;
          uStack_2d8 = uVar14;
          uStack_2d0 = uVar8;
code_r0x018e361c:
          memcpy(uVar8,&uStack_178,uVar14);
        }
        *(undefined1 *)(uVar8 + uVar14) = 0;
        Aska::THashMap<string, CAssetInfo, Hasher_CSTLString, Aska::TEqualTo<string >, Aska::TAllocator<Aska::TPair<string const, CAssetInfo> > >::Find_(string const&) const(&uStack_1c8,lVar10 + 0x58,&uStack_2e0);
        if ((uStack_2e0 & 1) != 0) {
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_2d0);
        }
        lVar10 = *(long *)(*(long *)(param_1 + 0x18) + 0x78);
        lVar5 = *(long *)(*(long *)(param_1 + 0x18) + 0x80);
        if (uStack_1c8 == lVar10 + lVar5 * 0xc0) {
          uVar14 = CGameResourceDownloader::IsVersionFile(char const*)(*(undefined8 *)(param_1 + 0x10),uVar6);
          if ((uVar14 & 1) != 0) {
            lVar10 = *(long *)(*(long *)(param_1 + 0x18) + 0x78);
            lVar5 = *(long *)(*(long *)(param_1 + 0x18) + 0x80);
            goto code_r0x018e368c;
          }
code_r0x018e36a0:
          uVar14 = (ulong)abStack_190 | 1;
          if ((abStack_190[0] & 1) != 0) {
            uVar14 = uStack_180;
          }
          snprintf(&uStack_2e0,0x100,&UNK_02866ccf/*"%s/%s"*/,uVar14,&uStack_178);
          Aska::File::DeleteFile(char const*)(&uStack_2e0);
        }
        else {
code_r0x018e368c:
          if ((uStack_1c8 != lVar10 + lVar5 * 0xc0) && ((*(byte *)(uStack_1c8 + 0x54) & 1) != 0))
          goto code_r0x018e36a0;
        }
        uVar6 = uVar6 + 0x100;
        bVar3 = (uStack_1b0 & 1) == 0;
      } while (uVar7 != uVar6);
    }
    if (!bVar3) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puStack_1a0);
    }
    if ((abStack_190[0] & 1) != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_180);
    }
  }
  *(int *)(param_1 + 0x74) = *(int *)(param_1 + 0x74) + 1;
  if (uStack_78 == 0) {
    return;
  }
  uVar7 = uStack_78;
  if (uStack_70 - uStack_78 != 0) {
    uStack_70 = uStack_70 + (~((uStack_70 - uStack_78) - 0x100) & 0xffffffffffffff00);
  }
code_r0x018e3738:
  Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uVar7);
  return;
}

// ==== CGameResourceDownloader::CVerifyTask::ProgressEraseEpisodeDataCheck()
// vaddr 0x17e3780 | ghidra 0x18e3780 | size 404 | symbol _ZN23CGameResourceDownloader11CVerifyTask29ProgressEraseEpisodeDataCheckEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN23CGameResourceDownloader11CVerifyTask29ProgressEraseEpisodeDataCheckEv(long param_1)

{
  uint uVar1;
  long lVar2;
  int iVar3;
  undefined4 *puVar4;
  ulong uVar5;
  undefined4 *puVar6;
  long lVar7;
  undefined4 uStack_34;
  
  if (*(int *)(param_1 + 0xc) != 1) {
    if (*(int *)(param_1 + 0xc) != 0) {
      return;
    }
    puVar6 = *(undefined4 **)(param_1 + 0x78);
    puVar4 = *(undefined4 **)(param_1 + 0x80);
    if (puVar4 != puVar6) {
      puVar6 = (undefined4 *)
               ((long)puVar4 + (~((long)puVar4 + (-4 - (long)puVar6)) & 0xfffffffffffffffcU));
      *(undefined4 **)(param_1 + 0x80) = puVar6;
    }
    lVar7 = *(long *)(param_1 + 0x40) - *(long *)(param_1 + 0x38);
    if ((lVar7 == 0) || (*(long *)(param_1 + 0x38) == *(long *)(param_1 + 0x40))) {
      iVar3 = 1;
    }
    else {
      while( true ) {
        lVar7 = lVar7 + -8;
        uStack_34 = 0;
        if (puVar6 < *(undefined4 **)(param_1 + 0x88)) {
          if (puVar6 == (undefined4 *)0x0) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
          }
          else {
            uStack_34 = 0;
          }
          *puVar6 = uStack_34;
          *(long *)(param_1 + 0x80) = *(long *)(param_1 + 0x80) + 4;
        }
        else {
          void std::__ndk1::vector<unsigned int, Framework::CSTLAllocator<unsigned int, Framework::CSTLVectorAllocatorInf> >::__push_back_slow_path<unsigned int>(unsigned int&&)((undefined8 *)(param_1 + 0x78),&uStack_34);
        }
        if (lVar7 == 0) break;
        puVar6 = *(undefined4 **)(param_1 + 0x80);
      }
      iVar3 = *(int *)(param_1 + 0xc) + 1;
    }
    *(undefined4 *)(param_1 + 0x90) = 0;
    *(undefined4 *)(param_1 + 0x74) = 0;
    *(int *)(param_1 + 0xc) = iVar3;
    return;
  }
  lVar7 = *(long *)(param_1 + 0x38);
  lVar2 = *(long *)(param_1 + 0x40) - lVar7;
  if (lVar2 != 0) {
    uVar5 = (ulong)*(uint *)(param_1 + 0x90);
    if ((ulong)(lVar2 >> 3) <= uVar5) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dc536/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Vector.h"*/,0x58,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,uVar5);
      lVar7 = *(long *)(param_1 + 0x38);
    }
    uVar5 = CGameResourceDownloader::CVerifyTask::ProgressEraseEpisodeData(Aska::ASON::AValue::AMap const*)(param_1,*(undefined8 *)(lVar7 + uVar5 * 8));
    if ((uVar5 & 1) == 0) {
      return;
    }
    uVar1 = *(int *)(param_1 + 0x90) + 1;
    *(uint *)(param_1 + 0x90) = uVar1;
    if ((ulong)uVar1 < (ulong)(*(long *)(param_1 + 0x40) - *(long *)(param_1 + 0x38) >> 3)) {
      *(undefined4 *)(param_1 + 0x74) = 0;
      return;
    }
  }
  *(undefined1 *)(param_1 + 0x71) = 1;
  *(undefined4 *)(param_1 + 0xc) = 3;
  return;
}

// ==== CGameResourceDownloader::CVerifyTask::ProgressSetupManifest()
// vaddr 0x17e3914 | ghidra 0x18e3914 | size 2324 | symbol _ZN23CGameResourceDownloader11CVerifyTask21ProgressSetupManifestEv | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Type propagation algorithm not settling */

void _ZN23CGameResourceDownloader11CVerifyTask21ProgressSetupManifestEv(long param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  undefined *puVar3;
  ulong uVar4;
  undefined7 *puVar5;
  undefined *puVar6;
  int iVar7;
  undefined4 uVar8;
  ulong uVar9;
  long lVar10;
  long lVar11;
  long lVar12;
  long lVar13;
  long lVar14;
  long lVar15;
  ulong uVar16;
  undefined *puVar17;
  ulong uVar18;
  undefined *puVar19;
  undefined *puVar20;
  long lVar21;
  undefined *puVar22;
  undefined4 uVar23;
  uint uVar24;
  uint uVar25;
  undefined4 uVar26;
  undefined8 uVar27;
  uint uVar28;
  undefined *puVar29;
  undefined4 uStack_240;
  undefined4 uStack_23c;
  undefined1 auStack_220 [32];
  undefined *puStack_200;
  ulong uStack_1f8;
  undefined8 uStack_1f0;
  undefined *puStack_1e8;
  long lStack_1e0;
  byte bStack_1d8;
  undefined8 uStack_1c8;
  byte bStack_1a8;
  undefined8 uStack_198;
  undefined *puStack_190;
  long *plStack_188;
  undefined8 uStack_180;
  long lStack_178;
  undefined8 uStack_170;
  ushort uStack_15e;
  undefined1 auStack_148 [16];
  undefined *puStack_138;
  undefined1 uStack_130;
  byte bStack_128;
  undefined7 uStack_127;
  ulong uStack_120;
  undefined7 *puStack_118;
  undefined4 uStack_110;
  undefined4 uStack_10c;
  undefined4 uStack_108;
  undefined4 uStack_104;
  undefined4 uStack_100;
  byte bStack_f8;
  undefined7 uStack_f7;
  ulong uStack_f0;
  undefined7 *puStack_e8;
  undefined *puStack_e0;
  long *plStack_d8;
  undefined8 uStack_d0;
  long lStack_c8;
  undefined8 uStack_c0;
  undefined8 uStack_b8;
  uint uStack_b0;
  undefined *puStack_a8;
  undefined1 uStack_a0;
  long alStack_98 [3];
  undefined8 uStack_80;
  byte abStack_78 [16];
  undefined8 uStack_68;
  
  if (*(int *)(param_1 + 0xc) == 0) {
    if (*(long *)(param_1 + 0x28) == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02866a48/*"C:\BAS_Submission\Client\Project\..\Source\Game\Resource\GameResourceDownloader.cpp"*/,0x1661,&UNK_02866c8f/*"m_pSearchMap is null."*/);
    }
    BAS::GetDownloadPath()(abStack_78);
    if (*(int *)(*(long *)(param_1 + 0x28) + 8) != 0) {
      puVar1 = PTR__ZTV10CAssetInfo_02cb7ad0 + 0x10;
      puVar2 = PTR__ZTVN4Aska6TArrayI9CMetaInfoLb0EEE_02cba9a0 + 0x10;
      puVar3 = PTR__ZTV9CMetaInfo_02cc00d0 + 0x10;
      uVar28 = 0;
      uVar25 = 0;
      do {
        Framework::CPerformanceCounter::Mark(unsigned int)(0x2b);
        if (*(uint *)(param_1 + 0x74) < *(uint *)(*(long **)(param_1 + 0x28) + 1)) {
          lVar21 = **(long **)(param_1 + 0x28) + (ulong)*(uint *)(param_1 + 0x74) * 0x40;
          lVar15 = lVar21 + 0x28;
        }
        else {
          lVar21 = 0;
          lVar15 = 8;
        }
        uVar27 = *(undefined8 *)(lVar21 + 0x10);
        lVar21 = *(long *)(param_1 + 0x18);
        uStack_1f8 = 0;
        uStack_1f0 = 0;
        puStack_200 = (undefined *)0x0;
        uStack_80 = uVar27;
        uVar9 = strlen(uVar27);
        if (uVar9 < 0x17) {
          puStack_200 = (undefined *)CONCAT71(puStack_200._1_7_,(char)(uVar9 << 1));
          uVar18 = (ulong)&puStack_200 | 1;
          if (uVar9 != 0) goto code_r0x018e3b30;
        }
        else {
          uVar16 = uVar9 + 0x10 & 0xfffffffffffffff0;
          if (uVar16 == 0) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
          }
          uVar18 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar16,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
          if (uVar18 == 0) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
          }
          puStack_200 = (undefined *)(uVar16 | 1);
          uStack_1f8 = uVar9;
          uStack_1f0 = uVar18;
code_r0x018e3b30:
          memcpy(uVar18,uVar27,uVar9);
        }
        *(undefined1 *)(uVar18 + uVar9) = 0;
        Aska::THashMap<string, CAssetInfo, Hasher_CSTLString, Aska::TEqualTo<string >, Aska::TAllocator<Aska::TPair<string const, CAssetInfo> > >::Find_(string const&) const(alStack_98,lVar21 + 0x58,&puStack_200);
        lVar11 = alStack_98[0];
        lVar21 = *(long *)(*(long *)(param_1 + 0x18) + 0x78);
        lVar10 = *(long *)(*(long *)(param_1 + 0x18) + 0x80);
        if (((ulong)puStack_200 & 1) != 0) {
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_1f0);
        }
        if (lVar11 == lVar21 + lVar10 * 0xc0) {
          uStack_130 = 1;
          puStack_118 = (undefined7 *)0x0;
          uStack_120 = 0;
          uStack_127 = 0;
          bStack_128 = 0;
          puStack_e8 = (undefined7 *)0x0;
          uStack_f0 = 0;
          uStack_f7 = 0;
          bStack_f8 = 0;
          uStack_d0 = 0;
          plStack_d8 = (long *)0x0;
          uStack_c0 = 0;
          lStack_c8 = 0;
          uStack_b8 = 8;
          uStack_b0 = 0;
          uStack_a0 = 1;
          puStack_e0 = PTR__ZTV9CMetaList_02cbed68 + 0x10;
          puStack_a8 = PTR__ZTV9CMetaList_02cbed68 + 0x40;
          puStack_138 = puVar1;
          lVar21 = Aska::ASON::AValue::AMap::Get_(char const*)(lVar15,&UNK_02866ca5/*"md5"*/);
          lVar10 = Aska::ASON::AValue::AMap::Get_(char const*)(lVar15,&UNK_02a3cbab/*"time"*/);
          lVar11 = Aska::ASON::AValue::AMap::Get_(char const*)(lVar15,&UNK_02866f00/*"size"*/);
          Aska::ASON::AValue::AMap::Get_(char const*)(lVar15,&UNK_02866ca9/*"parentHash"*/);
          lVar12 = Aska::ASON::AValue::AMap::Get_(char const*)(lVar15,&UNK_02866cb4/*"flags"*/);
          lVar13 = Aska::ASON::AValue::AMap::Get_(char const*)(lVar15,&UNK_028c6cb9/*"e"*/);
          lVar14 = Aska::ASON::AValue::AMap::Get_(char const*)(lVar15,&UNK_02866cc2/*"meta"*/);
          lVar15 = Aska::ASON::AValue::AMap::Get_(char const*)(lVar15,&UNK_02866cc7/*"ep_data"*/);
          if (lVar21 == 0) {
            puVar22 = (undefined *)0x0;
            if (lVar11 != 0) goto code_r0x018e3c88;
code_r0x018e3cc0:
            uStack_23c = 0;
            if (lVar10 != 0) goto code_r0x018e3c94;
code_r0x018e3cc8:
            uStack_240 = 0;
            if (lVar12 != 0) goto code_r0x018e3ca0;
code_r0x018e3cd0:
            uVar23 = 0;
            if (lVar13 != 0) goto code_r0x018e3ca8;
code_r0x018e3cd8:
            uVar26 = 1;
            if (lVar15 != 0) goto code_r0x018e3cb0;
code_r0x018e3ce0:
            puVar29 = (undefined *)0x0;
          }
          else {
            puVar22 = *(undefined **)(lVar21 + 0x10);
            if (lVar11 == 0) goto code_r0x018e3cc0;
code_r0x018e3c88:
            uStack_23c = *(undefined4 *)(lVar11 + 8);
            if (lVar10 == 0) goto code_r0x018e3cc8;
code_r0x018e3c94:
            uStack_240 = *(undefined4 *)(lVar10 + 8);
            if (lVar12 == 0) goto code_r0x018e3cd0;
code_r0x018e3ca0:
            uVar23 = *(undefined4 *)(lVar12 + 8);
            if (lVar13 == 0) goto code_r0x018e3cd8;
code_r0x018e3ca8:
            uVar26 = *(undefined4 *)(lVar13 + 8);
            if (lVar15 == 0) goto code_r0x018e3ce0;
code_r0x018e3cb0:
            puVar29 = *(undefined **)(lVar15 + 0x10);
          }
          if (puVar22 == (undefined *)0x0) {
            puVar22 = &UNK_029d2011;
          }
          uVar16 = strlen(puVar22);
          uVar9 = (ulong)bStack_128;
          if ((bStack_128 & 1) == 0) {
            uVar18 = 0x16;
            lVar15 = uVar16 - 0x16;
            if (0x15 < uVar16 && lVar15 != 0) goto code_r0x018e3d64;
code_r0x018e3d14:
            puVar5 = &uStack_127;
            if ((uVar9 & 1) != 0) {
              puVar5 = puStack_118;
            }
            if (uVar16 != 0) {
              memmove(puVar5,puVar22,uVar16);
            }
            *(undefined1 *)((long)puVar5 + uVar16) = 0;
            if ((bStack_128 & 1) == 0) {
              bStack_128 = (byte)(uVar16 << 1);
              uVar16 = uStack_120;
            }
          }
          else {
            uVar9 = CONCAT71(uStack_127,bStack_128);
            uVar18 = (uVar9 & 0xfffffffffffffffe) - 1;
            lVar15 = uVar16 - uVar18;
            if (uVar16 < uVar18 || lVar15 == 0) goto code_r0x018e3d14;
code_r0x018e3d64:
            uVar4 = (ulong)(((uint)uVar9 & 0xfe) >> 1);
            if ((uVar9 & 1) != 0) {
              uVar4 = uStack_120;
            }
            string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&bStack_128,uVar18,lVar15,uVar4,0,uVar4,uVar16,puVar22);
            uVar16 = uStack_120;
          }
          uStack_120 = uVar16;
          if (puVar29 == (undefined *)0x0) {
            puVar29 = &UNK_029d2011;
          }
          uVar16 = strlen(puVar29);
          puVar22 = PTR__ZTV9CMetaInfo_02cc00d0;
          uVar9 = (ulong)bStack_f8;
          if ((bStack_f8 & 1) == 0) {
            uVar18 = 0x16;
          }
          else {
            uVar9 = CONCAT71(uStack_f7,bStack_f8);
            uVar18 = (uVar9 & 0xfffffffffffffffe) - 1;
          }
          if (uVar16 < uVar18 || uVar16 - uVar18 == 0) {
            puVar5 = &uStack_f7;
            if ((uVar9 & 1) != 0) {
              puVar5 = puStack_e8;
            }
            if (uVar16 != 0) {
              memmove(puVar5,puVar29,uVar16);
            }
            *(undefined1 *)((long)puVar5 + uVar16) = 0;
            if ((bStack_f8 & 1) == 0) {
              bStack_f8 = (byte)(uVar16 << 1);
              uVar16 = uStack_f0;
            }
          }
          else {
            uVar4 = (ulong)(((uint)uVar9 & 0xfe) >> 1);
            if ((uVar9 & 1) != 0) {
              uVar4 = uStack_f0;
            }
            string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&bStack_f8,uVar18,uVar16 - uVar18,uVar4,0,uVar4,uVar16,puVar29);
            uVar16 = uStack_f0;
          }
          uStack_f0 = uVar16;
          Framework::CHash32::CHash32(char const*)(auStack_148,uStack_80);
          uVar8 = Framework::CHash32::operator unsigned int() const(auStack_148);
          Framework::CHash32::~CHash32()(auStack_148);
          uStack_110 = uStack_23c;
          uStack_10c = uStack_240;
          uStack_108 = uVar8;
          uStack_104 = uVar23;
          uStack_100 = uVar26;
          if ((lVar14 != 0) && (*(int *)(lVar14 + 0x10) != 0)) {
            uVar24 = 0;
            do {
              uStack_1f8 = CONCAT71(uStack_1f8._1_7_,1);
              puStack_1e8 = (undefined *)0x0;
              lStack_1e0 = 0;
              uStack_1f0 = 0;
              lVar15 = 0;
              if (uVar24 < *(uint *)(lVar14 + 0x10)) {
                lVar15 = *(long *)(lVar14 + 8) + (ulong)uVar24 * 0x20;
              }
              puStack_200 = puVar3;
              lVar15 = Aska::ASON::AValue::AMap::Get_(char const*)(lVar15 + 8,&UNK_029d62d5/*"param"*/);
              if (lVar15 == 0) {
                puVar29 = &UNK_029d2011;
              }
              else {
                puVar29 = *(undefined **)(lVar15 + 0x10);
              }
              puVar17 = (undefined *)strlen(puVar29);
              if ((uStack_1f0 & 1) == 0) {
                puVar19 = (undefined *)0x16;
                puVar20 = puVar17 + -0x16;
                uVar9 = uStack_1f0 & 0xff;
                if ((undefined *)0x15 < puVar17 && puVar20 != (undefined *)0x0)
                goto code_r0x018e3f64;
code_r0x018e3f14:
                lVar15 = (long)&uStack_1f0 + 1;
                if ((uVar9 & 1) != 0) {
                  lVar15 = lStack_1e0;
                }
                if (puVar17 != (undefined *)0x0) {
                  memmove(lVar15,puVar29,puVar17);
                }
                puVar17[lVar15] = 0;
                if ((uStack_1f0 & 1) == 0) {
                  uStack_1f0 = CONCAT71(uStack_1f0._1_7_,(char)((long)puVar17 << 1));
                  puVar17 = puStack_1e8;
                }
              }
              else {
                puVar19 = (undefined *)((uStack_1f0 & 0xfffffffffffffffe) - 1);
                puVar20 = puVar17 + -(long)puVar19;
                uVar9 = uStack_1f0;
                if (puVar17 < puVar19 || puVar20 == (undefined *)0x0) goto code_r0x018e3f14;
code_r0x018e3f64:
                puVar6 = (undefined *)(ulong)(((uint)uVar9 & 0xfe) >> 1);
                if ((uVar9 & 1) != 0) {
                  puVar6 = puStack_1e8;
                }
                string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&uStack_1f0,puVar19,puVar20,puVar6,0,puVar6,puVar17,puVar29);
                puVar17 = puStack_1e8;
              }
              puStack_1e8 = puVar17;
              Aska::TArray<CMetaInfo, false>::SetAt(long, CMetaInfo const&)(&puStack_e0,lStack_c8,&puStack_200);
              puStack_200 = puVar22 + 0x10;
              if ((uStack_1f0 & 1) != 0) {
                Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(lStack_1e0);
              }
              uVar24 = uVar24 + 1;
            } while (uVar24 < *(uint *)(lVar14 + 0x10));
          }
          lVar15 = *(long *)(param_1 + 0x18);
          Aska::TPair<string const, CAssetInfo>::TPair<char const*, CAssetInfo>(char const* const&, CAssetInfo const&)(&puStack_200,&uStack_80,&puStack_138);
          uVar9 = (ulong)((float)((ulong)*(uint *)(lVar15 + 0x68) + (ulong)*(uint *)(lVar15 + 0x6c)
                                 + 1) / *(float *)(lVar15 + 100));
          if (*(ulong *)(lVar15 + 0x80) < uVar9) {
            Aska::THashMap<string, CAssetInfo, Hasher_CSTLString, Aska::TEqualTo<string >, Aska::TAllocator<Aska::TPair<string const, CAssetInfo> > >::Rehash_(unsigned long)(lVar15 + 0x58,uVar9 << 1 | 1);
          }
          Aska::THashMap<string, CAssetInfo, Hasher_CSTLString, Aska::TEqualTo<string >, Aska::TAllocator<Aska::TPair<string const, CAssetInfo> > >::Insert_(Aska::TPair<string const, CAssetInfo> const&)(auStack_220,lVar15 + 0x58,&puStack_200);
          puStack_1e8 = PTR__ZTV10CAssetInfo_02cb7ad0 + 0x10;
          uStack_15e = uStack_15e | 1;
          puStack_190 = puVar2;
          if (((plStack_188 != (long *)0x0) && (0 < lStack_178)) &&
             ((**(code **)(*plStack_188 + 0x10))(), 1 < lStack_178)) {
            lVar21 = 0x28;
            lVar15 = 1;
            do {
              (**(code **)(*(long *)((long)plStack_188 + lVar21) + 0x10))();
              lVar15 = lVar15 + 1;
              lVar21 = lVar21 + 0x28;
            } while (lVar15 < lStack_178);
          }
          if ((uStack_15e & 1) != 0) {
            if (plStack_188 != (long *)0x0) {
              operator delete[](void*)();
              plStack_188 = (long *)0x0;
            }
            uStack_180 = 0;
          }
          lStack_178 = 0;
          uStack_170 = 0;
          if ((bStack_1a8 & 1) != 0) {
            Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_198);
          }
          if ((bStack_1d8 & 1) != 0) {
            Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_1c8);
          }
          if (((ulong)puStack_200 & 1) != 0) {
            Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_1f0);
          }
          puStack_138 = PTR__ZTV10CAssetInfo_02cb7ad0 + 0x10;
          puStack_e0 = PTR__ZTVN4Aska6TArrayI9CMetaInfoLb0EEE_02cba9a0 + 0x10;
          uStack_b0 = uStack_b0 | 0x10000;
          if (((plStack_d8 != (long *)0x0) && (0 < lStack_c8)) &&
             ((**(code **)(*plStack_d8 + 0x10))(), 1 < lStack_c8)) {
            lVar21 = 0x28;
            lVar15 = 1;
            do {
              (**(code **)(*(long *)((long)plStack_d8 + lVar21) + 0x10))();
              lVar15 = lVar15 + 1;
              lVar21 = lVar21 + 0x28;
            } while (lVar15 < lStack_c8);
          }
          if ((uStack_b0 & 0x10000) != 0) {
            if (plStack_d8 != (long *)0x0) {
              operator delete[](void*)();
              plStack_d8 = (long *)0x0;
            }
            uStack_d0 = 0;
          }
          uStack_c0 = 0;
          if ((bStack_f8 & 1) != 0) {
            Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puStack_e8);
          }
          if ((bStack_128 & 1) != 0) {
            Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puStack_118);
          }
        }
        Framework::CPerformanceCounter::Set(unsigned int)(0x2b);
        uVar24 = *(int *)(param_1 + 0x74) + 1;
        *(uint *)(param_1 + 0x74) = uVar24;
        if (*(uint *)(*(long *)(param_1 + 0x28) + 8) <= uVar24) {
          *(undefined1 *)(param_1 + 0x71) = 1;
          *(int *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) + 1;
          break;
        }
        iVar7 = Framework::CPerformanceCounter::Get(unsigned int)(0x2b);
        uVar28 = iVar7 + uVar28;
        if ((0x270 < uVar28 >> 4) ||
           (uVar25 = uVar25 + 1, *(uint *)(*(long *)(param_1 + 0x28) + 8) <= uVar25)) break;
      } while( true );
    }
    if ((abStack_78[0] & 1) != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_68);
    }
  }
  return;
}

// ==== CGameResourceDownloader::CVerifyTask::IsNeedUpdate() const
// vaddr 0x17e4228 | ghidra 0x18e4228 | size 8 | symbol _ZNK23CGameResourceDownloader11CVerifyTask12IsNeedUpdateEv | lib libSOA-3.7.0.so | 2026-10-04
undefined1 _ZNK23CGameResourceDownloader11CVerifyTask12IsNeedUpdateEv(long param_1)

{
  return *(undefined1 *)(param_1 + 0x72);
}

// ==== CGameResourceDownloader::CVerifyTask::GetMap()
// vaddr 0x17e4230 | ghidra 0x18e4230 | size 28 | symbol _ZN23CGameResourceDownloader11CVerifyTask6GetMapEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN23CGameResourceDownloader11CVerifyTask6GetMapEv(long param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)(param_1 + 0x30);
  if (*(char *)(param_1 + 0x70) == '\0') {
    puVar1 = (undefined8 *)(param_1 + 0x28);
  }
  return *puVar1;
}

// ==== CGameResourceDownloader::CVerifyTask::InitializeManifestCheck()
// vaddr 0x17e432c | ghidra 0x18e432c | size 8 | symbol _ZN23CGameResourceDownloader11CVerifyTask23InitializeManifestCheckEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN23CGameResourceDownloader11CVerifyTask23InitializeManifestCheckEv(long param_1)

{
  *(undefined4 *)(param_1 + 0x74) = 0;
  return;
}

// ==== CGameResourceDownloader::CVerifyTask::InitializeEpisodeManifestCheck()
// vaddr 0x17e4334 | ghidra 0x18e4334 | size 228 | symbol _ZN23CGameResourceDownloader11CVerifyTask30InitializeEpisodeManifestCheckEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN23CGameResourceDownloader11CVerifyTask30InitializeEpisodeManifestCheckEv(long param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  long lVar3;
  undefined4 uStack_34;
  
  puVar2 = *(undefined4 **)(param_1 + 0x78);
  puVar1 = *(undefined4 **)(param_1 + 0x80);
  if (puVar1 != puVar2) {
    puVar2 = (undefined4 *)
             ((long)puVar1 + (~((long)puVar1 + (-4 - (long)puVar2)) & 0xfffffffffffffffcU));
    *(undefined4 **)(param_1 + 0x80) = puVar2;
  }
  lVar3 = *(long *)(param_1 + 0x40) - *(long *)(param_1 + 0x38);
  if ((lVar3 != 0) && (*(long *)(param_1 + 0x38) != *(long *)(param_1 + 0x40))) {
    while( true ) {
      lVar3 = lVar3 + -8;
      uStack_34 = 0;
      if (puVar2 < *(undefined4 **)(param_1 + 0x88)) {
        if (puVar2 == (undefined4 *)0x0) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
        }
        else {
          uStack_34 = 0;
        }
        *puVar2 = uStack_34;
        *(long *)(param_1 + 0x80) = *(long *)(param_1 + 0x80) + 4;
      }
      else {
        void std::__ndk1::vector<unsigned int, Framework::CSTLAllocator<unsigned int, Framework::CSTLVectorAllocatorInf> >::__push_back_slow_path<unsigned int>(unsigned int&&)((undefined8 *)(param_1 + 0x78),&uStack_34);
      }
      if (lVar3 == 0) break;
      puVar2 = *(undefined4 **)(param_1 + 0x80);
    }
  }
  *(undefined4 *)(param_1 + 0x90) = 0;
  return;
}

// ==== CGameResourceDownloader::CVerifyTask::ProgressManifestCheck(bool, Aska::ASON::AValue::AMap const*, unsigned int*)
// vaddr 0x17e4418 | ghidra 0x18e4418 | size 5516 | symbol _ZN23CGameResourceDownloader11CVerifyTask21ProgressManifestCheckEbPKN4Aska4ASON6AValue4AMapEPj | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Type propagation algorithm not settling */

bool _ZN23CGameResourceDownloader11CVerifyTask21ProgressManifestCheckEbPKN4Aska4ASON6AValue4AMapEPj
               (long param_1,byte param_2,long *param_3,int *param_4)

{
  long lVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  long *plVar5;
  ulong uVar6;
  int iVar7;
  undefined4 uVar8;
  int iVar9;
  undefined4 uVar10;
  long lVar11;
  long lVar12;
  ulong uVar13;
  long lVar14;
  long lVar15;
  long lVar16;
  long lVar17;
  long *plVar18;
  undefined1 *puVar19;
  ulong uVar20;
  undefined8 extraout_x1;
  uint uVar21;
  long lVar22;
  long lVar23;
  ulong uVar24;
  uint uVar25;
  uint uVar26;
  uint uVar27;
  ulong uVar28;
  int iVar29;
  undefined8 uVar30;
  undefined8 uVar31;
  undefined *puVar32;
  uint uVar33;
  undefined8 uVar34;
  uint uVar35;
  uint uVar36;
  undefined *puVar37;
  ulong uVar38;
  undefined8 uStack_3e8;
  undefined *puStack_3a0;
  long *plStack_398;
  undefined8 uStack_390;
  long lStack_388;
  undefined8 uStack_380;
  ushort uStack_36e;
  undefined1 auStack_358 [16];
  long alStack_348 [3];
  ulong uStack_330;
  ulong uStack_328;
  ulong uStack_320;
  undefined *puStack_310;
  long *plStack_308;
  undefined8 uStack_300;
  undefined *puStack_2f8;
  undefined8 uStack_2f0;
  ulong uStack_2e8;
  uint uStack_2e0;
  undefined *puStack_2d8;
  undefined1 uStack_2d0;
  byte bStack_2b8;
  undefined8 uStack_2a8;
  undefined *puStack_2a0;
  long *plStack_298;
  undefined8 uStack_290;
  long lStack_288;
  undefined8 uStack_280;
  ushort uStack_26e;
  undefined *puStack_258;
  ulong uStack_250;
  undefined8 uStack_248;
  undefined8 uStack_240;
  undefined8 uStack_238;
  undefined8 uStack_230;
  undefined4 uStack_228;
  long lStack_224;
  byte bStack_218;
  undefined1 uStack_217;
  undefined6 uStack_216;
  ulong uStack_210;
  undefined1 *puStack_208;
  undefined *puStack_200;
  long *plStack_1f8;
  undefined8 uStack_1f0;
  long lStack_1e8;
  undefined8 uStack_1e0;
  undefined8 uStack_1d8;
  uint uStack_1d0;
  undefined *puStack_1c8;
  undefined1 uStack_1c0;
  undefined1 auStack_1b8 [16];
  undefined1 auStack_1a8 [16];
  undefined1 auStack_198 [16];
  undefined8 uStack_188;
  undefined1 auStack_17c [260];
  byte abStack_78 [16];
  ulong uStack_68;
  
  if (param_3 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02866a48/*"C:\BAS_Submission\Client\Project\..\Source\Game\Resource\GameResourceDownloader.cpp"*/,0x146b,&UNK_02866cd5/*"apSearchMap is null."*/);
  }
  BAS::GetDownloadPath()(abStack_78);
  if ((int)param_3[1] != 0) {
    lVar1 = param_1 + 0xa0;
    uVar28 = (ulong)&puStack_310 | 1;
    puVar2 = PTR__ZTV10CAssetInfo_02cb7ad0 + 0x10;
    puVar3 = PTR__ZTVN4Aska6TArrayI9CMetaInfoLb0EEE_02cba9a0 + 0x10;
    uVar26 = 0;
    uVar27 = 0;
    puVar4 = PTR__ZTV9CMetaInfo_02cc00d0 + 0x10;
    do {
      Framework::CPerformanceCounter::Mark(unsigned int)(0x2b);
      if (*(uint *)(param_1 + 0x74) < *(uint *)(param_3 + 1)) {
        lVar22 = (ulong)*(uint *)(param_1 + 0x74) * 0x40;
        uStack_188 = *(undefined8 *)(*param_3 + lVar22 + 0x10);
        lVar22 = *param_3 + lVar22 + 0x20;
      }
      else {
        lVar22 = 0;
        uStack_188 = uRam0000000000000010;
      }
      plVar5 = (long *)(lVar22 + 8);
      lVar11 = Aska::ASON::AValue::AMap::Get_(char const*)(plVar5,&UNK_02866cc2/*"meta"*/);
      lVar12 = Aska::ASON::AValue::AMap::Get_(char const*)(plVar5,&UNK_02866ca5/*"md5"*/);
      uVar30 = *(undefined8 *)(lVar12 + 0x10);
      Framework::CHash32::CHash32(char const*)(auStack_198,uStack_188);
      uVar8 = Framework::CHash32::operator unsigned int() const(auStack_198);
      Framework::CHash32::~CHash32()(auStack_198);
      uVar35 = *(uint *)(lVar22 + 0x10);
      if (uVar35 == 0) {
        uStack_3e8._4_4_ = 0;
        uStack_3e8._0_4_ = 0;
        iVar7 = 0;
code_r0x018e51b8:
        if (((uVar35 != 0) && (((int)uStack_3e8 == 0 & (param_2 ^ 1)) != 0)) &&
           (uStack_3e8._4_4_ == iVar7)) {
          uVar38 = 0;
          do {
            uVar30 = *(undefined8 *)(*plVar5 + (uVar38 & 0xffffffff) * 0x40 + 0x10);
            lVar11 = strrchr(uVar30,0x2f);
            if (lVar11 != 0) {
              Framework::CHash32::CHash32(char const*)(auStack_1b8,uVar30);
              uVar8 = Framework::CHash32::operator unsigned int() const(auStack_1b8);
              puStack_310 = (undefined *)CONCAT44(puStack_310._4_4_,uVar8);
              puVar19 = (undefined1 *)std::__ndk1::unordered_map<unsigned int, bool, std::__ndk1::hash<unsigned int>, std::__ndk1::equal_to<unsigned int>, Framework::CSTLAllocator<std::__ndk1::pair<unsigned int const, bool>, Framework::CSTLUnorderedMapAllocatorInf> >::operator[](unsigned int&&)(lVar1,&puStack_310);
              *puVar19 = 0;
              Framework::CHash32::~CHash32()(auStack_1b8);
              uVar35 = *(uint *)(lVar22 + 0x10);
            }
            uVar38 = uVar38 + 1;
          } while (uVar38 < uVar35);
        }
      }
      else {
        uVar33 = 0;
        uVar38 = 0;
        uStack_3e8 = 0;
        iVar7 = 0;
        do {
          uVar31 = *(undefined8 *)(*plVar5 + (uVar38 & 0xffffffff) * 0x40 + 0x10);
          lVar12 = strrchr(uVar31,0x2f);
          if (lVar12 != 0) {
            lVar12 = *(long *)(param_1 + 0x18);
            uStack_248 = 0;
            uStack_250 = 0;
            puStack_258 = (undefined *)0x0;
            uVar13 = strlen(uVar31);
            if (uVar13 < 0x17) {
              puStack_258 = (undefined *)CONCAT71(puStack_258._1_7_,(char)(uVar13 << 1));
              uVar20 = (ulong)&puStack_258 | 1;
              if (uVar13 != 0) goto code_r0x018e4748;
            }
            else {
              uVar24 = uVar13 + 0x10 & 0xfffffffffffffff0;
              if (uVar24 == 0) {
                Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
              }
              uVar20 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar24,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
              if (uVar20 == 0) {
                Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
              }
              puStack_258 = (undefined *)(uVar24 | 1);
              uStack_250 = uVar13;
              uStack_248 = uVar20;
code_r0x018e4748:
              memcpy(uVar20,uVar31,uVar13);
            }
            *(undefined1 *)(uVar20 + uVar13) = 0;
            Aska::THashMap<string, CAssetInfo, Hasher_CSTLString, Aska::TEqualTo<string >, Aska::TAllocator<Aska::TPair<string const, CAssetInfo> > >::Find_(string const&) const(&puStack_310,lVar12 + 0x58,&puStack_258);
            if (((ulong)puStack_258 & 1) != 0) {
              Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_248);
            }
            if ((uint)uVar38 < *(uint *)(lVar22 + 0x10)) {
              lVar12 = *plVar5 + (uVar38 & 0xffffffff) * 0x40 + 0x20;
            }
            else {
              lVar12 = 0;
            }
            lVar12 = lVar12 + 8;
            uVar13 = (ulong)abStack_78 | 1;
            if ((abStack_78[0] & 1) != 0) {
              uVar13 = uStack_68;
            }
            snprintf(auStack_17c,0x104,&UNK_02866ccf/*"%s/%s"*/,uVar13,uVar31);
            lVar14 = Aska::ASON::AValue::AMap::Get_(char const*)(lVar12,&UNK_02866ca5/*"md5"*/);
            uVar34 = *(undefined8 *)(lVar14 + 0x10);
            lVar14 = Aska::ASON::AValue::AMap::Get_(char const*)(lVar12,&UNK_028c6cb9/*"e"*/);
            iVar29 = *(int *)(lVar14 + 8);
            Aska::ASON::AValue::AMap::Get_(char const*)(lVar12,&UNK_02866cc7/*"ep_data"*/);
            if ((puStack_310 ==
                 (undefined *)
                 (*(long *)(*(long *)(param_1 + 0x18) + 0x78) +
                 *(long *)(*(long *)(param_1 + 0x18) + 0x80) * 0xc0)) ||
               (iVar9 = access(auStack_17c,0), puVar37 = puStack_310, iVar9 != 0)) {
              uVar35 = 0;
              uVar36 = 1;
              lVar12 = *(long *)(param_1 + 0x20);
joined_r0x018e4844:
              if (lVar12 == 0) goto code_r0x018e49e0;
code_r0x018e4848:
              uStack_328 = 0;
              uStack_320 = 0;
              uStack_330 = 0;
              uVar13 = strlen(uVar31);
              if (uVar13 < 0x17) {
                uStack_330 = CONCAT71(uStack_330._1_7_,(char)(uVar13 << 1));
                uVar20 = (ulong)&uStack_330 | 1;
                if (uVar13 != 0) goto code_r0x018e48e4;
              }
              else {
                uVar24 = uVar13 + 0x10 & 0xfffffffffffffff0;
                if (uVar24 == 0) {
                  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
                }
                uVar20 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar24,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
                if (uVar20 == 0) {
                  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
                }
                uStack_330 = uVar24 | 1;
                uStack_328 = uVar13;
                uStack_320 = uVar20;
code_r0x018e48e4:
                memcpy(uVar20,uVar31,uVar13);
              }
              *(undefined1 *)(uVar20 + uVar13) = 0;
              Aska::THashMap<string, CAssetInfo, Hasher_CSTLString, Aska::TEqualTo<string >, Aska::TAllocator<Aska::TPair<string const, CAssetInfo> > >::Find_(string const&) const(&puStack_258,lVar12 + 0x58,&uStack_330);
              if ((uStack_330 & 1) != 0) {
                Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_320);
              }
              puVar37 = puStack_258;
              if (puStack_258 ==
                  (undefined *)
                  (*(long *)(*(long *)(param_1 + 0x20) + 0x78) +
                  *(long *)(*(long *)(param_1 + 0x20) + 0x80) * 0xc0)) {
                uVar25 = 0;
                uVar21 = 0;
              }
              else {
                if ((puStack_258[0x30] & 1) == 0) {
                  puVar32 = puStack_258 + 0x31;
                }
                else {
                  puVar32 = *(undefined **)(puStack_258 + 0x40);
                }
                iVar9 = strcmp(uVar34,puVar32);
                if (iVar9 == 0) {
                  uVar21 = (uint)(iVar29 != *(int *)(puVar37 + 0x58));
                }
                else {
                  uVar21 = 1;
                }
                uStack_3e8 = CONCAT44(uStack_3e8._4_4_ + 1,(int)uStack_3e8 + uVar21);
                uVar25 = 1;
              }
            }
            else {
              *(undefined4 *)(puStack_310 + 0x50) = uVar8;
              if ((puStack_310[0x30] & 1) == 0) {
                puVar32 = puStack_310 + 0x31;
              }
              else {
                puVar32 = *(undefined **)(puStack_310 + 0x40);
              }
              iVar9 = strcmp(uVar34,puVar32);
              uVar36 = 0;
              if (iVar9 == 0) {
                uVar35 = (uint)(*(int *)(puVar37 + 0x58) != iVar29);
                lVar12 = *(long *)(param_1 + 0x20);
                goto joined_r0x018e4844;
              }
              uVar35 = 1;
              lVar12 = *(long *)(param_1 + 0x20);
              if (lVar12 != 0) goto code_r0x018e4848;
code_r0x018e49e0:
              uVar21 = 0;
              uVar25 = 0;
            }
            uVar33 = uVar33 | (uVar36 | uVar35) & (uVar21 | uVar25 ^ 1);
            if ((param_2 & 1) == 0) {
              Framework::CHash32::CHash32(char const*)(auStack_1a8,uVar31);
              uVar10 = Framework::CHash32::operator unsigned int() const(auStack_1a8);
              puStack_258 = (undefined *)CONCAT44(puStack_258._4_4_,uVar10);
              puVar19 = (undefined1 *)std::__ndk1::unordered_map<unsigned int, bool, std::__ndk1::hash<unsigned int>, std::__ndk1::equal_to<unsigned int>, Framework::CSTLAllocator<std::__ndk1::pair<unsigned int const, bool>, Framework::CSTLUnorderedMapAllocatorInf> >::operator[](unsigned int&&)(lVar1,&puStack_258);
              *puVar19 = 1;
              Framework::CHash32::~CHash32()(auStack_1a8);
            }
            else if (uVar33 != 0) goto code_r0x018e5248;
            uVar35 = *(uint *)(lVar22 + 0x10);
            iVar7 = iVar7 + 1;
          }
          uVar38 = uVar38 + 1;
        } while (uVar38 < uVar35);
        if (uVar33 == 0) {
          goto code_r0x018e51b8;
        }
        if ((param_2 & 1) == 0) {
          puVar37 = PTR__ZTV9CMetaInfo_02cc00d0;
          if (uVar35 != 0) {
            uVar38 = 0;
            do {
              if ((uint)uVar38 < uVar35) {
                lVar12 = *plVar5 + (uVar38 & 0xffffffff) * 0x40;
              }
              else {
                lVar12 = 0;
              }
              alStack_348[0] = *(long *)(lVar12 + 0x10);
              lVar12 = strrchr(alStack_348[0],0x2f);
              if (lVar12 != 0) {
                if ((uint)uVar38 < uVar35) {
                  lVar12 = *plVar5 + (uVar38 & 0xffffffff) * 0x40 + 0x20;
                }
                else {
                  lVar12 = 0;
                }
                lVar12 = lVar12 + 8;
                lVar14 = Aska::ASON::AValue::AMap::Get_(char const*)(lVar12,&UNK_02866ca5/*"md5"*/);
                lVar15 = Aska::ASON::AValue::AMap::Get_(char const*)(lVar12,&UNK_028c6cb9/*"e"*/);
                lVar16 = Aska::ASON::AValue::AMap::Get_(char const*)(lVar12,&UNK_02866cc2/*"meta"*/);
                lVar17 = Aska::ASON::AValue::AMap::Get_(char const*)(lVar12,&UNK_02866cc7/*"ep_data"*/);
                lVar12 = alStack_348[0];
                lVar23 = *(long *)(param_1 + 0x18);
                puStack_310 = (undefined *)0x0;
                plStack_308 = (long *)0x0;
                uStack_300 = 0;
                plVar18 = (long *)strlen(alStack_348[0]);
                if (plVar18 < (long *)0x17) {
                  puStack_310 = (undefined *)CONCAT71(puStack_310._1_7_,(char)((long)plVar18 << 1));
                  uVar24 = uVar28;
                  if (plVar18 != (long *)0x0) goto code_r0x018e4c98;
                }
                else {
                  uVar13 = (ulong)(plVar18 + 2) & 0xfffffffffffffff0;
                  if (uVar13 == 0) {
                    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
                  }
                  uVar24 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar13,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
                  if (uVar24 == 0) {
                    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
                  }
                  puStack_310 = (undefined *)(uVar13 | 1);
                  plStack_308 = plVar18;
                  uStack_300 = uVar24;
code_r0x018e4c98:
                  memcpy(uVar24,lVar12,plVar18);
                }
                *(undefined1 *)(uVar24 + (long)plVar18) = 0;
                Aska::THashMap<string, CAssetInfo, Hasher_CSTLString, Aska::TEqualTo<string >, Aska::TAllocator<Aska::TPair<string const, CAssetInfo> > >::Erase(string const&)(lVar23 + 0x58,&puStack_310);
                if (((ulong)puStack_310 & 1) != 0) {
                  Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_300);
                }
                puVar37 = PTR__ZTV9CMetaInfo_02cc00d0;
                uStack_250 = CONCAT71(uStack_250._1_7_,1);
                puStack_258 = PTR__ZTV10CAssetInfo_02cb7ad0 + 0x10;
                uStack_238 = 0;
                uStack_240 = 0;
                uStack_248 = 0;
                puStack_200 = PTR__ZTV9CMetaList_02cbed68 + 0x10;
                puStack_208 = (undefined1 *)0x0;
                uStack_210 = 0;
                uStack_216 = 0;
                uStack_217 = 0;
                bStack_218 = 0;
                uStack_1f0 = 0;
                plStack_1f8 = (long *)0x0;
                uStack_1e0 = 0;
                lStack_1e8 = 0;
                puStack_1c8 = PTR__ZTV9CMetaList_02cbed68 + 0x40;
                uStack_1d8 = 8;
                uStack_1d0 = 0;
                uStack_1c0 = 1;
                if (lVar14 == 0) {
                  puVar32 = &UNK_029d2011;
                }
                else {
                  puVar32 = *(undefined **)(lVar14 + 0x10);
                }
                uVar13 = strlen(puVar32);
                if (uVar13 < 0x16 || uVar13 - 0x16 == 0) {
                  if (uVar13 != 0) {
                    memmove((long)&uStack_248 + 1,puVar32,uVar13);
                  }
                  *(undefined1 *)((long)&uStack_248 + uVar13 + 1) = 0;
                  uStack_248 = CONCAT71(uStack_248._1_7_,(char)(uVar13 << 1));
                }
                else {
                  string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&uStack_248,0x16,uVar13 - 0x16,0,0,0,uVar13,puVar32);
                }
                uStack_230 = 0;
                uVar13 = uStack_210;
                if (lVar15 == 0) {
                  lStack_224 = 0x100000000;
                  if (lVar17 != 0) goto code_r0x018e4de0;
code_r0x018e4e58:
                  puVar19 = &uStack_217;
                  if ((bStack_218 & 1) != 0) {
                    puVar19 = puStack_208;
                  }
                  *puVar19 = 0;
                  if ((bStack_218 & 1) == 0) {
                    bStack_218 = 0;
                    uStack_228 = uVar8;
                  }
                  else {
                    uStack_210 = 0;
                    uStack_228 = uVar8;
                    uVar13 = uStack_210;
                  }
                }
                else {
                  lStack_224 = (ulong)*(uint *)(lVar15 + 8) << 0x20;
                  if (lVar17 == 0) goto code_r0x018e4e58;
code_r0x018e4de0:
                  lVar12 = *(long *)(lVar17 + 0x10);
                  if (lVar12 == 0) {
                    puVar19 = &uStack_217;
                    if ((bStack_218 & 1) != 0) {
                      puVar19 = puStack_208;
                    }
                    *puVar19 = 0;
                    if ((bStack_218 & 1) == 0) {
                      bStack_218 = 0;
                      uStack_228 = uVar8;
                    }
                    else {
                      uStack_210 = 0;
                      uStack_228 = uVar8;
                      uVar13 = uStack_210;
                    }
                  }
                  else {
                    uStack_228 = uVar8;
                    uVar13 = strlen(lVar12);
                    uVar24 = (ulong)bStack_218;
                    if ((bStack_218 & 1) == 0) {
                      uVar20 = 0x16;
                      lVar14 = uVar13 - 0x16;
                      if (uVar13 < 0x16 || lVar14 == 0) {
code_r0x018e4e08:
                        puVar19 = &uStack_217;
                        if ((uVar24 & 1) != 0) {
                          puVar19 = puStack_208;
                        }
                        if (uVar13 != 0) {
                          memmove(puVar19,lVar12,uVar13);
                        }
                        puVar19[uVar13] = 0;
                        if ((bStack_218 & 1) == 0) {
                          bStack_218 = (byte)(uVar13 << 1);
                          uVar13 = uStack_210;
                        }
                        goto joined_r0x018e4ad0;
                      }
                    }
                    else {
                      uVar24 = CONCAT62(uStack_216,CONCAT11(uStack_217,bStack_218));
                      uVar20 = (uVar24 & 0xfffffffffffffffe) - 1;
                      lVar14 = uVar13 - uVar20;
                      if (uVar13 < uVar20 || lVar14 == 0) goto code_r0x018e4e08;
                    }
                    uVar6 = (ulong)(((uint)uVar24 & 0xfe) >> 1);
                    if ((uVar24 & 1) != 0) {
                      uVar6 = uStack_210;
                    }
                    string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&bStack_218,uVar20,lVar14,uVar6,0,uVar6,uVar13,lVar12);
                    uVar13 = uStack_210;
                  }
                }
joined_r0x018e4ad0:
                uStack_210 = uVar13;
                if ((lVar16 != 0) && (*(int *)(lVar16 + 0x10) != 0)) {
                  uVar35 = 0;
                  do {
                    puStack_310 = puVar37 + 0x10;
                    plStack_308 = (long *)CONCAT71(plStack_308._1_7_,1);
                    uVar31 = *(undefined8 *)(*(long *)(lVar16 + 8) + (ulong)uVar35 * 0x20 + 0x10);
                    uVar13 = strlen(uVar31);
                    if (uVar13 < 0x16 || uVar13 - 0x16 == 0) {
                      if (uVar13 != 0) {
                        memmove((long)&uStack_300 + 1,uVar31,uVar13);
                      }
                      *(undefined1 *)((long)&uStack_300 + uVar13 + 1) = 0;
                      uStack_300 = CONCAT71(uStack_300._1_7_,(char)(uVar13 << 1));
                    }
                    else {
                      string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&uStack_300,0x16,uVar13 - 0x16,0,0,0,uVar13,uVar31);
                    }
                    Aska::TArray<CMetaInfo, false>::SetAt(long, CMetaInfo const&)(&puStack_200,lStack_1e8,&puStack_310);
                    puStack_310 = puVar37 + 0x10;
                    if ((uStack_300 & 1) != 0) {
                      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_2f0);
                    }
                    uVar35 = uVar35 + 1;
                  } while (uVar35 < *(uint *)(lVar16 + 0x10));
                }
                lVar12 = *(long *)(param_1 + 0x18);
                Aska::TPair<string const, CAssetInfo>::TPair<char const*, CAssetInfo>(char const* const&, CAssetInfo const&)(&puStack_310,alStack_348,&puStack_258);
                uVar13 = (ulong)((float)((ulong)*(uint *)(lVar12 + 0x68) +
                                         (ulong)*(uint *)(lVar12 + 0x6c) + 1) /
                                *(float *)(lVar12 + 100));
                if (*(ulong *)(lVar12 + 0x80) < uVar13) {
                  Aska::THashMap<string, CAssetInfo, Hasher_CSTLString, Aska::TEqualTo<string >, Aska::TAllocator<Aska::TPair<string const, CAssetInfo> > >::Rehash_(unsigned long)(lVar12 + 0x58,uVar13 << 1 | 1);
                }
                Aska::THashMap<string, CAssetInfo, Hasher_CSTLString, Aska::TEqualTo<string >, Aska::TAllocator<Aska::TPair<string const, CAssetInfo> > >::Insert_(Aska::TPair<string const, CAssetInfo> const&)(&uStack_330,lVar12 + 0x58,&puStack_310);
                puStack_2f8 = PTR__ZTV10CAssetInfo_02cb7ad0 + 0x10;
                puStack_2a0 = PTR__ZTVN4Aska6TArrayI9CMetaInfoLb0EEE_02cba9a0 + 0x10;
                uStack_26e = uStack_26e | 1;
                if (((plStack_298 != (long *)0x0) && (0 < lStack_288)) &&
                   ((**(code **)(*plStack_298 + 0x10))(), 1 < lStack_288)) {
                  lVar14 = 0x28;
                  lVar12 = 1;
                  do {
                    (**(code **)(*(long *)((long)plStack_298 + lVar14) + 0x10))();
                    lVar12 = lVar12 + 1;
                    lVar14 = lVar14 + 0x28;
                  } while (lVar12 < lStack_288);
                }
                if ((uStack_26e & 1) != 0) {
                  if (plStack_298 != (long *)0x0) {
                    operator delete[](void*)();
                    plStack_298 = (long *)0x0;
                  }
                  uStack_290 = 0;
                }
                lStack_288 = 0;
                uStack_280 = 0;
                if ((bStack_2b8 & 1) != 0) {
                  Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_2a8);
                }
                if ((uStack_2e8 & 1) != 0) {
                  Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puStack_2d8);
                }
                if (((ulong)puStack_310 & 1) != 0) {
                  Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_300);
                }
                puStack_258 = PTR__ZTV10CAssetInfo_02cb7ad0 + 0x10;
                puStack_200 = PTR__ZTVN4Aska6TArrayI9CMetaInfoLb0EEE_02cba9a0 + 0x10;
                uStack_1d0 = uStack_1d0 | 0x10000;
                if (((plStack_1f8 != (long *)0x0) && (0 < lStack_1e8)) &&
                   ((**(code **)(*plStack_1f8 + 0x10))(), 1 < lStack_1e8)) {
                  lVar14 = 0x28;
                  lVar12 = 1;
                  do {
                    (**(code **)(*(long *)((long)plStack_1f8 + lVar14) + 0x10))();
                    lVar12 = lVar12 + 1;
                    lVar14 = lVar14 + 0x28;
                  } while (lVar12 < lStack_1e8);
                }
                if ((uStack_1d0 & 0x10000) != 0) {
                  if (plStack_1f8 != (long *)0x0) {
                    operator delete[](void*)();
                    plStack_1f8 = (long *)0x0;
                  }
                  uStack_1f0 = 0;
                }
                uStack_1e0 = 0;
                if ((bStack_218 & 1) != 0) {
                  Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puStack_208);
                }
                if ((uStack_248 & 1) != 0) {
                  Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_238);
                }
                uVar35 = *(uint *)(lVar22 + 0x10);
              }
              uVar38 = uVar38 + 1;
            } while (uVar38 < uVar35);
          }
          uVar31 = uStack_188;
          lVar22 = *(long *)(param_1 + 0x18);
          puStack_310 = (undefined *)0x0;
          plStack_308 = (long *)0x0;
          uStack_300 = 0;
          uVar38 = strlen(uStack_188);
          if (uVar38 < 0x17) {
            puStack_310 = (undefined *)CONCAT71(puStack_310._1_7_,(char)(uVar38 << 1));
            uVar24 = uVar28;
            if (uVar38 != 0) goto code_r0x018e52c8;
          }
          else {
            uVar13 = uVar38 + 0x10 & 0xfffffffffffffff0;
            if (uVar13 == 0) {
              Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
            }
            uVar24 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar13,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
            if (uVar24 == 0) {
              Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
            }
            puStack_310 = (undefined *)(uVar13 | 1);
            plStack_308 = (long *)uVar38;
            uStack_300 = uVar24;
code_r0x018e52c8:
            memcpy(uVar24,uVar31,uVar38);
          }
          *(undefined1 *)(uVar24 + uVar38) = 0;
          Aska::THashMap<string, CAssetInfo, Hasher_CSTLString, Aska::TEqualTo<string >, Aska::TAllocator<Aska::TPair<string const, CAssetInfo> > >::Find_(string const&) const(alStack_348,lVar22 + 0x58,&puStack_310);
          if (((ulong)puStack_310 & 1) != 0) {
            Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_300);
          }
          lVar22 = *(long *)(param_1 + 0x18);
          if (alStack_348[0] == *(long *)(lVar22 + 0x78) + *(long *)(lVar22 + 0x80) * 0xc0) {
            uStack_250 = CONCAT71(uStack_250._1_7_,1);
            uStack_240 = 0;
            puStack_208 = (undefined1 *)0x0;
            uStack_210 = 0;
            uStack_1f0 = 0;
            plStack_1f8 = (long *)0x0;
            uStack_1e0 = 0;
            lStack_1e8 = 0;
            uStack_1d8 = 8;
            uStack_1d0 = 0;
            uStack_1c0 = 1;
            uStack_248 = uStack_248 & 0xffffffffffff0000;
            puStack_200 = PTR__ZTV9CMetaList_02cbed68 + 0x10;
            puStack_1c8 = PTR__ZTV9CMetaList_02cbed68 + 0x40;
            lStack_224 = 1;
            bStack_218 = 0;
            uStack_217 = 0;
            puStack_258 = puVar2;
            uStack_228 = uVar8;
            if ((lVar11 != 0) && (*(int *)(lVar11 + 0x10) != 0)) {
              uVar35 = 0;
              do {
                plStack_308 = (long *)CONCAT71(plStack_308._1_7_,1);
                puStack_2f8 = (undefined *)0x0;
                uStack_2f0 = 0;
                uStack_300 = 0;
                uVar31 = *(undefined8 *)(*(long *)(lVar11 + 8) + (ulong)uVar35 * 0x20 + 0x10);
                puStack_310 = puVar4;
                uVar38 = strlen(uVar31);
                if (uVar38 < 0x16 || uVar38 - 0x16 == 0) {
                  if (uVar38 != 0) {
                    memmove((long)&uStack_300 + 1,uVar31,uVar38);
                  }
                  *(undefined1 *)((long)&uStack_300 + uVar38 + 1) = 0;
                  uStack_300 = CONCAT71(uStack_300._1_7_,(char)(uVar38 << 1));
                }
                else {
                  string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&uStack_300,0x16,uVar38 - 0x16,0,0,0,uVar38,uVar31);
                }
                Aska::TArray<CMetaInfo, false>::SetAt(long, CMetaInfo const&)(&puStack_200,lStack_1e8,&puStack_310);
                puStack_310 = puVar37 + 0x10;
                if ((uStack_300 & 1) != 0) {
                  Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_2f0);
                }
                uVar35 = uVar35 + 1;
              } while (uVar35 < *(uint *)(lVar11 + 0x10));
              lVar22 = *(long *)(param_1 + 0x18);
            }
            Aska::TPair<string const, CAssetInfo>::TPair<char const*, CAssetInfo>(char const* const&, CAssetInfo const&)(&puStack_310,&uStack_188,&puStack_258);
            uVar38 = (ulong)((float)((ulong)*(uint *)(lVar22 + 0x68) +
                                     (ulong)*(uint *)(lVar22 + 0x6c) + 1) / *(float *)(lVar22 + 100)
                            );
            if (*(ulong *)(lVar22 + 0x80) < uVar38) {
              Aska::THashMap<string, CAssetInfo, Hasher_CSTLString, Aska::TEqualTo<string >, Aska::TAllocator<Aska::TPair<string const, CAssetInfo> > >::Rehash_(unsigned long)(lVar22 + 0x58,uVar38 << 1 | 1);
            }
            Aska::THashMap<string, CAssetInfo, Hasher_CSTLString, Aska::TEqualTo<string >, Aska::TAllocator<Aska::TPair<string const, CAssetInfo> > >::Insert_(Aska::TPair<string const, CAssetInfo> const&)(&uStack_330,lVar22 + 0x58,&puStack_310);
            puStack_2f8 = PTR__ZTV10CAssetInfo_02cb7ad0 + 0x10;
            uStack_26e = uStack_26e | 1;
            puStack_2a0 = puVar3;
            if (((plStack_298 != (long *)0x0) && (0 < lStack_288)) &&
               ((**(code **)(*plStack_298 + 0x10))(), 1 < lStack_288)) {
              lVar12 = 0x28;
              lVar22 = 1;
              do {
                (**(code **)(*(long *)((long)plStack_298 + lVar12) + 0x10))();
                lVar22 = lVar22 + 1;
                lVar12 = lVar12 + 0x28;
              } while (lVar22 < lStack_288);
            }
            if ((uStack_26e & 1) != 0) {
              if (plStack_298 != (long *)0x0) {
                operator delete[](void*)();
                plStack_298 = (long *)0x0;
              }
              uStack_290 = 0;
            }
            lStack_288 = 0;
            uStack_280 = 0;
            if ((bStack_2b8 & 1) != 0) {
              Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_2a8);
            }
            if ((uStack_2e8 & 1) != 0) {
              Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puStack_2d8);
            }
            if (((ulong)puStack_310 & 1) != 0) {
              Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_300);
            }
            puStack_258 = PTR__ZTV10CAssetInfo_02cb7ad0 + 0x10;
            puStack_200 = PTR__ZTVN4Aska6TArrayI9CMetaInfoLb0EEE_02cba9a0 + 0x10;
            uStack_1d0 = uStack_1d0 | 0x10000;
            if (((plStack_1f8 != (long *)0x0) && (0 < lStack_1e8)) &&
               ((**(code **)(*plStack_1f8 + 0x10))(), 1 < lStack_1e8)) {
              lVar12 = 0x28;
              lVar22 = 1;
              do {
                (**(code **)(*(long *)((long)plStack_1f8 + lVar12) + 0x10))();
                lVar22 = lVar22 + 1;
                lVar12 = lVar12 + 0x28;
              } while (lVar22 < lStack_1e8);
            }
            if ((uStack_1d0 & 0x10000) != 0) {
              if (plStack_1f8 != (long *)0x0) {
                operator delete[](void*)();
                plStack_1f8 = (long *)0x0;
              }
              uStack_1f0 = 0;
            }
            uStack_1e0 = 0;
            if ((bStack_218 & 1) != 0) {
              Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puStack_208);
            }
            if ((uStack_248 & 1) != 0) {
              Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_238);
            }
          }
          Framework::CHash32::CHash32(char const*)(auStack_358,uStack_188);
          uVar8 = Framework::CHash32::operator unsigned int() const(auStack_358);
          puStack_310 = (undefined *)CONCAT44(puStack_310._4_4_,uVar8);
          puVar19 = (undefined1 *)std::__ndk1::unordered_map<unsigned int, bool, std::__ndk1::hash<unsigned int>, std::__ndk1::equal_to<unsigned int>, Framework::CSTLAllocator<std::__ndk1::pair<unsigned int const, bool>, Framework::CSTLUnorderedMapAllocatorInf> >::operator[](unsigned int&&)(lVar1,&puStack_310);
          *puVar19 = 1;
          Framework::CHash32::~CHash32()(auStack_358);
          lVar22 = Aska::ASON::AValue::AMap::Get_(char const*)(plVar5,&UNK_02866f00/*"size"*/);
          if (lVar22 == 0) {
            uVar8 = 0;
          }
          else {
            uVar8 = *(undefined4 *)(lVar22 + 8);
          }
          plVar5 = (long *)0x0;
          if (lVar11 != 0) {
            plVar5 = (long *)(lVar11 + 8);
          }
          uStack_300 = 0;
          plStack_308 = (long *)0x0;
          uStack_2f0 = 0;
          puStack_2f8 = (undefined *)0x0;
          uStack_2e8 = 8;
          uStack_2e0 = 0;
          uStack_2d0 = 1;
          puStack_310 = PTR__ZTV9CMetaList_02cbed68 + 0x10;
          puStack_2d8 = PTR__ZTV9CMetaList_02cbed68 + 0x40;
          if ((int)plVar5[1] != 0) {
            uVar35 = 0;
            do {
              puStack_258 = puVar37 + 0x10;
              uStack_250 = CONCAT71(uStack_250._1_7_,1);
              uStack_240 = 0;
              uVar31 = *(undefined8 *)(*plVar5 + (ulong)uVar35 * 0x20 + 0x10);
              uVar38 = strlen(uVar31);
              if (uVar38 < 0x16 || uVar38 - 0x16 == 0) {
                if (uVar38 != 0) {
                  memmove((long)&uStack_248 + 1,uVar31,uVar38);
                }
                *(undefined1 *)((long)&uStack_248 + uVar38 + 1) = 0;
                uStack_248 = CONCAT71(uStack_248._1_7_,(char)(uVar38 << 1));
              }
              else {
                string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&uStack_248,0x16,uVar38 - 0x16,0,0,0,uVar38,uVar31);
              }
              Aska::TArray<CMetaInfo, false>::SetAt(long, CMetaInfo const&)(&puStack_310,puStack_2f8,&puStack_258);
              puStack_258 = puVar37 + 0x10;
              if ((uStack_248 & 1) != 0) {
                Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_238);
              }
              uVar35 = uVar35 + 1;
            } while (uVar35 < *(uint *)(plVar5 + 1));
          }
          lVar22 = *(long *)(param_1 + 0x10);
          if (lVar22 == 0) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02866a48/*"C:\BAS_Submission\Client\Project\..\Source\Game\Resource\GameResourceDownloader.cpp"*/,0x1563,&UNK_02866cea/*"m_pDownLoader is null."*/);
            lVar22 = *(long *)(param_1 + 0x10);
          }
          uVar31 = uStack_188;
          CMetaList::CMetaList(CMetaList const&)(&puStack_3a0,&puStack_310);
          CGameResourceDownloader::NotifyRequireDownLoad(Aska::ASON::AValue const*, char const*, char const*, unsigned int, CMetaList)(lVar22,extraout_x1,uVar31,uVar30,uVar8,&puStack_3a0);
          puStack_3a0 = PTR__ZTVN4Aska6TArrayI9CMetaInfoLb0EEE_02cba9a0 + 0x10;
          uStack_36e = uStack_36e | 1;
          if (((plStack_398 != (long *)0x0) && (0 < lStack_388)) &&
             ((**(code **)(*plStack_398 + 0x10))(), 1 < lStack_388)) {
            lVar11 = 0x28;
            lVar22 = 1;
            do {
              (**(code **)(*(long *)((long)plStack_398 + lVar11) + 0x10))();
              lVar22 = lVar22 + 1;
              lVar11 = lVar11 + 0x28;
            } while (lVar22 < lStack_388);
          }
          if ((uStack_36e & 1) != 0) {
            if (plStack_398 != (long *)0x0) {
              operator delete[](void*)();
              plStack_398 = (long *)0x0;
            }
            uStack_390 = 0;
          }
          puStack_310 = PTR__ZTVN4Aska6TArrayI9CMetaInfoLb0EEE_02cba9a0 + 0x10;
          uStack_2e0 = uStack_2e0 | 0x10000;
          lStack_388 = 0;
          uStack_380 = 0;
          if (((plStack_308 != (long *)0x0) && (0 < (long)puStack_2f8)) &&
             ((**(code **)(*plStack_308 + 0x10))(), 1 < (long)puStack_2f8)) {
            lVar11 = 0x28;
            lVar22 = 1;
            do {
              (**(code **)(*(long *)((long)plStack_308 + lVar11) + 0x10))();
              lVar22 = lVar22 + 1;
              lVar11 = lVar11 + 0x28;
            } while (lVar22 < (long)puStack_2f8);
          }
          if ((uStack_2e0 & 0x10000) != 0) {
            if (plStack_308 != (long *)0x0) {
              operator delete[](void*)();
              plStack_308 = (long *)0x0;
            }
            uStack_300 = 0;
          }
        }
        else {
code_r0x018e5248:
          if (param_4 != (int *)0x0) {
            *param_4 = *param_4 + 1;
          }
        }
      }
      Framework::CPerformanceCounter::Set(unsigned int)(0x2b);
      uVar35 = *(int *)(param_1 + 0x74) + 1;
      *(uint *)(param_1 + 0x74) = uVar35;
      if (*(uint *)(param_3 + 1) <= uVar35) {
        iVar29 = 1;
        iVar7 = 1;
        goto joined_r0x018e5960;
      }
      iVar7 = Framework::CPerformanceCounter::Get(unsigned int)(0x2b);
      uVar26 = iVar7 + uVar26;
    } while ((uVar26 >> 4 < 0x271) && (uVar27 = uVar27 + 1, uVar27 < *(uint *)(param_3 + 1)));
  }
  iVar29 = 2;
  iVar7 = 2;
joined_r0x018e5960:
  if ((abStack_78[0] & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_68);
    iVar7 = iVar29;
  }
  return iVar7 != 2;
}

// ==== CGameResourceDownloader::CVerifyTask::ProgressEraseEpisodeData(Aska::ASON::AValue::AMap const*)
// vaddr 0x17e5d34 | ghidra 0x18e5d34 | size 888 | symbol _ZN23CGameResourceDownloader11CVerifyTask24ProgressEraseEpisodeDataEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-04
undefined4
_ZN23CGameResourceDownloader11CVerifyTask24ProgressEraseEpisodeDataEPKN4Aska4ASON6AValue4AMapE
          (long param_1,long *param_2)

{
  long lVar1;
  int iVar2;
  long lVar3;
  ulong uVar4;
  ulong uVar5;
  uint uVar6;
  undefined4 uVar7;
  ulong uVar8;
  uint uVar9;
  uint uVar10;
  ulong uVar11;
  uint uVar12;
  undefined8 uVar13;
  ulong uStack_1c0;
  ulong uStack_1b8;
  ulong uStack_1b0;
  long alStack_1a8 [3];
  undefined1 auStack_190 [16];
  byte abStack_180 [16];
  ulong uStack_170;
  undefined1 auStack_164 [260];
  
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02866a48/*"C:\BAS_Submission\Client\Project\..\Source\Game\Resource\GameResourceDownloader.cpp"*/,0x160b,&UNK_02866cd5/*"apSearchMap is null."*/);
  }
  BAS::GetDownloadPath()(abStack_180);
  if ((int)param_2[1] != 0) {
    uVar12 = 0;
    uVar6 = 0;
    uVar8 = (ulong)&uStack_1c0 | 1;
    do {
      Framework::CPerformanceCounter::Mark(unsigned int)(0x2d);
      lVar3 = *param_2 + (ulong)*(uint *)(param_1 + 0x74) * 0x40;
      lVar1 = lVar3 + 0x20;
      if (*(uint *)(param_2 + 1) <= *(uint *)(param_1 + 0x74)) {
        lVar1 = 0;
      }
      Framework::CHash32::CHash32(char const*)(auStack_190,*(undefined8 *)(lVar3 + 0x10));
      Framework::CHash32::operator unsigned int() const(auStack_190);
      Framework::CHash32::~CHash32()(auStack_190);
      uVar10 = *(uint *)(lVar1 + 0x10);
      if (uVar10 != 0) {
        uVar9 = 0;
        do {
          uVar13 = *(undefined8 *)(*(long *)(lVar1 + 8) + (ulong)uVar9 * 0x40 + 0x10);
          lVar3 = strrchr(uVar13,0x2f);
          if (lVar3 != 0) {
            lVar3 = *(long *)(param_1 + 0x18);
            uStack_1b8 = 0;
            uStack_1b0 = 0;
            uStack_1c0 = 0;
            uVar4 = strlen(uVar13);
            if (uVar4 < 0x17) {
              uStack_1c0 = CONCAT71(uStack_1c0._1_7_,(char)(uVar4 << 1));
              uVar5 = uVar8;
              if (uVar4 != 0) goto code_r0x018e5eac;
            }
            else {
              uVar11 = uVar4 + 0x10 & 0xfffffffffffffff0;
              if (uVar11 == 0) {
                Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
              }
              uVar5 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar11,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
              if (uVar5 == 0) {
                Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
              }
              uStack_1c0 = uVar11 | 1;
              uStack_1b8 = uVar4;
              uStack_1b0 = uVar5;
code_r0x018e5eac:
              memcpy(uVar5,uVar13,uVar4);
            }
            *(undefined1 *)(uVar5 + uVar4) = 0;
            Aska::THashMap<string, CAssetInfo, Hasher_CSTLString, Aska::TEqualTo<string >, Aska::TAllocator<Aska::TPair<string const, CAssetInfo> > >::Find_(string const&) const(alStack_1a8,lVar3 + 0x58,&uStack_1c0);
            if ((uStack_1c0 & 1) != 0) {
              Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_1b0);
            }
            uVar4 = (ulong)abStack_180 | 1;
            if ((abStack_180[0] & 1) != 0) {
              uVar4 = uStack_170;
            }
            snprintf(auStack_164,0x104,&UNK_02866ccf/*"%s/%s"*/,uVar4,uVar13);
            if ((alStack_1a8[0] !=
                 *(long *)(*(long *)(param_1 + 0x18) + 0x78) +
                 *(long *)(*(long *)(param_1 + 0x18) + 0x80) * 0xc0) &&
               (iVar2 = access(auStack_164,0), iVar2 == 0)) {
              lVar3 = *(long *)(param_1 + 0x18);
              uStack_1b8 = 0;
              uStack_1b0 = 0;
              uStack_1c0 = 0;
              uVar4 = strlen(uVar13);
              if (uVar4 < 0x17) {
                uStack_1c0 = CONCAT71(uStack_1c0._1_7_,(char)(uVar4 << 1));
                uVar5 = uVar8;
                if (uVar4 != 0) goto code_r0x018e5fd4;
              }
              else {
                uVar11 = uVar4 + 0x10 & 0xfffffffffffffff0;
                if (uVar11 == 0) {
                  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
                }
                uVar5 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar11,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
                if (uVar5 == 0) {
                  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
                }
                uStack_1c0 = uVar11 | 1;
                uStack_1b8 = uVar4;
                uStack_1b0 = uVar5;
code_r0x018e5fd4:
                memcpy(uVar5,uVar13,uVar4);
              }
              *(undefined1 *)(uVar5 + uVar4) = 0;
              Aska::THashMap<string, CAssetInfo, Hasher_CSTLString, Aska::TEqualTo<string >, Aska::TAllocator<Aska::TPair<string const, CAssetInfo> > >::Erase(string const&)(lVar3 + 0x58,&uStack_1c0);
              if ((uStack_1c0 & 1) != 0) {
                Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_1b0);
              }
            }
            uVar10 = *(uint *)(lVar1 + 0x10);
          }
          uVar9 = uVar9 + 1;
        } while (uVar9 < uVar10);
      }
      Framework::CPerformanceCounter::Set(unsigned int)(0x2d);
      uVar10 = *(int *)(param_1 + 0x74) + 1;
      *(uint *)(param_1 + 0x74) = uVar10;
      if (*(uint *)(param_2 + 1) <= uVar10) {
        uVar7 = 1;
        if ((abStack_180[0] & 1) == 0) {
          return 1;
        }
        goto code_r0x018e6070;
      }
      iVar2 = Framework::CPerformanceCounter::Get(unsigned int)(0x2d);
      uVar12 = iVar2 + uVar12;
    } while ((uVar12 >> 4 < 0x271) && (uVar6 = uVar6 + 1, uVar6 < *(uint *)(param_2 + 1)));
  }
  uVar7 = 0;
  if ((abStack_180[0] & 1) != 0) {
code_r0x018e6070:
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_170);
  }
  return uVar7;
}

// ==== CGameResourceDownloader::CVerifyTask::GetCheckCount() const
// vaddr 0x17e60ac | ghidra 0x18e60ac | size 8 | symbol _ZNK23CGameResourceDownloader11CVerifyTask13GetCheckCountEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK23CGameResourceDownloader11CVerifyTask13GetCheckCountEv(long param_1)

{
  return *(undefined4 *)(param_1 + 0x74);
}

// ==== CGameResourceDownloader::CVerifyTask::GetCheckSize() const
// vaddr 0x17e60b4 | ghidra 0x18e60b4 | size 112 | symbol _ZNK23CGameResourceDownloader11CVerifyTask12GetCheckSizeEv | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZNK23CGameResourceDownloader11CVerifyTask12GetCheckSizeEv(long param_1)

{
  long *plVar1;
  
  if (1 < *(uint *)(param_1 + 8)) {
    if (*(uint *)(param_1 + 8) != 2) {
      return 0;
    }
    plVar1 = *(long **)(param_1 + 0x98);
    if (plVar1 != (long *)0x0) {
      return (ulong)(plVar1[1] - *plVar1) >> 8;
    }
    return 0;
  }
  if (*(char *)(param_1 + 0x70) == '\0') {
    if (*(long *)(param_1 + 0x28) != 0) {
      return (ulong)*(uint *)(*(long *)(param_1 + 0x28) + 8);
    }
    return 0;
  }
  if (*(long *)(param_1 + 0x30) != 0) {
    return (ulong)*(uint *)(*(long *)(param_1 + 0x30) + 8);
  }
  return 0;
}

// ==== CGameResourceDownloader::CVerifyTask::Handler(unsigned long)
// vaddr 0x17e6124 | ghidra 0x18e6124 | size 4 | symbol _ZN23CGameResourceDownloader11CVerifyTask7HandlerEm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN23CGameResourceDownloader11CVerifyTask7HandlerEm(void)

{
  return;
}

// ==== CGameResourceDownloader::CJournalFileWriter::Handler(unsigned long)
// vaddr 0x17e6128 | ghidra 0x18e6128 | size 904 | symbol _ZN23CGameResourceDownloader18CJournalFileWriter7HandlerEm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN23CGameResourceDownloader18CJournalFileWriter7HandlerEm(long param_1)

{
  long lVar1;
  long *plVar2;
  ulong uVar3;
  ulong uVar4;
  ulong uVar5;
  int iVar6;
  ulong uVar7;
  ulong uVar8;
  undefined8 uVar9;
  long lVar10;
  long lVar11;
  ulong uVar12;
  long lVar13;
  long lVar14;
  long lVar15;
  long lVar16;
  long *plVar17;
  long lVar18;
  byte abStack_178 [8];
  ulong uStack_170;
  ulong uStack_168;
  ulong uStack_78;
  ulong uStack_70;
  ulong uStack_68;
  
  lVar10 = param_1 + 0x10;
  uVar7 = Framework::CMutex::IsInitialized() const(lVar10);
  if ((uVar7 & 1) == 0) {
    Framework::CMutex::Initialize()(lVar10);
  }
  Framework::CMutex::Lock()(lVar10);
  uVar7 = (ulong)*(uint *)(param_1 + 0x170);
  *(uint *)(param_1 + 0x170) = ~*(uint *)(param_1 + 0x170) & 1;
  Framework::CMutex::Unlock()(lVar10);
  lVar10 = param_1 + uVar7 * 0x38;
  if (0 < *(long *)(lVar10 + 0x1c0)) {
    lVar1 = param_1 + 0xc0;
    plVar2 = (long *)(lVar10 + 0x1c0);
    uVar8 = Framework::CMutex::IsInitialized() const(lVar1);
    if ((uVar8 & 1) == 0) {
      Framework::CMutex::Initialize()(lVar1);
    }
    Framework::CMutex::Lock()(lVar1);
    if (*plVar2 < 1) {
      plVar17 = (long *)(param_1 + uVar7 * 0x38 + 0x1b0);
    }
    else {
      lVar18 = 0;
      plVar17 = (long *)(param_1 + uVar7 * 0x38 + 0x1b0);
      do {
        lVar14 = *plVar17;
        uStack_70 = 0;
        uStack_68 = 0;
        uStack_78 = 0x7c02;
        lVar13 = lVar14 + lVar18 * 0x168;
        lVar11 = *(long *)(lVar13 + 0x158);
        if (*(long *)(lVar11 + 0x18) < 1) {
          uVar8 = 0;
        }
        else {
          lVar16 = 0;
          lVar15 = 0x10;
          do {
            string std::__ndk1::operator+<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> >(string const&, char const*)(abStack_178,*(long *)(lVar11 + 8) + lVar15,&UNK_02a52b78/*"|"*/);
            uVar8 = (ulong)(abStack_178[0] >> 1);
            uVar5 = (ulong)abStack_178 | 1;
            if ((abStack_178[0] & 1) != 0) {
              uVar8 = uStack_170;
              uVar5 = uStack_168;
            }
            if ((uStack_78 & 1) == 0) {
              lVar11 = 0x16;
              uVar12 = uStack_78 & 0xff;
            }
            else {
              lVar11 = (uStack_78 & 0xfffffffffffffffe) - 1;
              uVar12 = uStack_78;
            }
            uVar3 = (ulong)(((uint)uVar12 & 0xfe) >> 1);
            if ((uVar12 & 1) != 0) {
              uVar3 = uStack_70;
            }
            if (lVar11 - uVar3 < uVar8) {
              string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&uStack_78,lVar11,(uVar8 - lVar11) + uVar3,uVar3,uVar3,0,uVar8);
            }
            else if (uVar8 != 0) {
              uVar4 = (ulong)&uStack_78 | 1;
              if ((uVar12 & 1) != 0) {
                uVar4 = uStack_68;
              }
              memcpy(uVar4 + uVar3,uVar5,uVar8);
              uVar3 = uVar3 + uVar8;
              if ((uStack_78 & 1) == 0) {
                uStack_78 = CONCAT71(uStack_78._1_7_,(char)uVar3 * '\x02');
                *(undefined1 *)(uVar4 + uVar3) = 0;
              }
              else {
                *(undefined1 *)(uVar4 + uVar3) = 0;
                uStack_70 = uVar3;
              }
            }
            if ((abStack_178[0] & 1) != 0) {
              Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_168);
            }
            lVar11 = *(long *)(lVar13 + 0x158);
            lVar16 = lVar16 + 1;
            lVar15 = lVar15 + 0x28;
          } while (lVar16 < *(long *)(lVar11 + 0x18));
          uVar8 = uStack_78 & 0xff;
        }
        uVar12 = uStack_68;
        memset(abStack_178,0,0x100);
        lVar14 = lVar14 + lVar18 * 0x168;
        uVar5 = (ulong)&uStack_78 | 1;
        if ((uVar8 & 1) != 0) {
          uVar5 = uVar12;
        }
        snprintf(abStack_178,0x100,&UNK_02866d23,lVar14,lVar14 + 0x100,
                        *(undefined4 *)(lVar14 + 0x140),*(undefined4 *)(lVar14 + 0x144),
                        *(undefined4 *)(lVar14 + 0x148),*(undefined4 *)(lVar14 + 0x14c),
                        *(undefined4 *)(lVar14 + 0x150),uVar5,lVar14 + 0x160);
        uVar9 = strlen(abStack_178);
        lVar14 = Aska::FileStream::Write(void const*, unsigned long, unsigned long)(param_1 + 0x178,abStack_178,uVar9,1);
        if (lVar14 == 0) {
          iVar6 = strlen(abStack_178);
          *(int *)PTR__ZN23CGameResourceDownloader15m_ErrorOverSizeE_02cbb7b8 =
               *(int *)PTR__ZN23CGameResourceDownloader15m_ErrorOverSizeE_02cbb7b8 + iVar6;
        }
        if ((uStack_78 & 1) != 0) {
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_68);
        }
        lVar18 = lVar18 + 1;
      } while (lVar18 < *plVar2);
    }
    Aska::FileStream::Flush()(param_1 + 0x178);
    if ((*(byte *)(param_1 + uVar7 * 0x38 + 0x1da) & 1) != 0) {
      if (*plVar17 != 0) {
        operator delete[](void*)();
        *plVar17 = 0;
      }
      *(undefined8 *)(param_1 + uVar7 * 0x38 + 0x1b8) = 0;
    }
    *plVar2 = 0;
    *(undefined8 *)(lVar10 + 0x1c8) = 0;
    Framework::CMutex::Unlock()(lVar1);
  }
  return;
}

// ==== CGameResourceDownloader::CDeleteTask::CDeleteTask()
// vaddr 0x17e64b0 | ghidra 0x18e64b0 | size 28 | symbol _ZN23CGameResourceDownloader11CDeleteTaskC1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN23CGameResourceDownloader11CDeleteTaskC2Ev(undefined8 *param_1)

{
  *param_1 = 0;
  param_1[1] = 0;
  *(undefined4 *)(param_1 + 2) = 1;
  param_1[3] = param_1 + 3;
  param_1[4] = param_1 + 3;
  param_1[5] = 0;
  return;
}

// ==== CGameResourceDownloader::CDeleteTask::FindFiles(char const*, Framework::CSTLList<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > >&)
// vaddr 0x17e64cc | ghidra 0x18e64cc | size 624 | symbol _ZN23CGameResourceDownloader11CDeleteTask9FindFilesEPKcRN9Framework8CSTLListINSt6__ndk112basic_stringIcNS5_11char_traitsIcEENS3_13CSTLAllocatorIcNS3_22CSTLStringAllocatorInfEEEEEEE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN23CGameResourceDownloader11CDeleteTask9FindFilesEPKcRN9Framework8CSTLListINSt6__ndk112basic_stringIcNS5_11char_traitsIcEENS3_13CSTLAllocatorIcNS3_22CSTLStringAllocatorInfEEEEEEE
               (undefined8 param_1,long param_2,long *param_3)

{
  int iVar1;
  ulong uVar2;
  ulong uVar3;
  long *plVar4;
  long lVar5;
  long lVar6;
  long lVar7;
  ulong uVar8;
  ulong uStack_298;
  ulong uStack_290;
  ulong uStack_288;
  undefined1 auStack_280 [256];
  long lStack_180;
  long lStack_178;
  undefined8 uStack_170;
  undefined1 auStack_164 [260];
  
  if ((param_2 != 0) && (iVar1 = access(param_2,0), iVar1 == 0)) {
    lStack_178 = 0;
    uStack_170 = 0;
    lStack_180 = 0;
    std::__ndk1::unordered_map<unsigned int, bool, std::__ndk1::hash<unsigned int>, std::__ndk1::equal_to<unsigned int>, Framework::CSTLAllocator<std::__ndk1::pair<unsigned int const, bool>, Framework::CSTLUnorderedMapAllocatorInf> >::operator[](unsigned int&&)+0x1f4(param_2,&lStack_180,1);
    lVar6 = lStack_178;
    lVar7 = lStack_180;
    if (lStack_180 != lStack_178) {
      do {
        memcpy(auStack_280,lVar7,0x100);
        Aska::PathUtil::CatenatePathName(char const*, char const*, char*, unsigned long)(param_2,auStack_280,auStack_164,0x104);
        _ZN23CGameResourceDownloader11CDeleteTask9FindFilesEPKcRN9Framework8CSTLListINSt6__ndk112basic_stringIcNS5_11char_traitsIcEENS3_13CSTLAllocatorIcNS3_22CSTLStringAllocatorInfEEEEEEE
                  (param_1,auStack_164,param_3);
        lVar7 = lVar7 + 0x100;
      } while (lVar6 != lVar7);
      if (lStack_178 - lStack_180 != 0) {
        lStack_178 = lStack_178 + (~((lStack_178 - lStack_180) - 0x100U) & 0xffffffffffffff00);
      }
    }
    std::__ndk1::unordered_map<unsigned int, bool, std::__ndk1::hash<unsigned int>, std::__ndk1::equal_to<unsigned int>, Framework::CSTLAllocator<std::__ndk1::pair<unsigned int const, bool>, Framework::CSTLUnorderedMapAllocatorInf> >::operator[](unsigned int&&)+0x1f4(param_2,&lStack_180,0);
    lVar7 = lStack_178;
    if (lStack_180 != lStack_178) {
      lVar6 = lStack_180;
      do {
        memcpy(auStack_280,lVar6,0x100);
        Aska::PathUtil::CatenatePathName(char const*, char const*, char*, unsigned long)(param_2,auStack_280,auStack_164,0x104);
        uStack_290 = 0;
        uStack_288 = 0;
        uStack_298 = 0;
        uVar2 = strlen(auStack_164);
        if (uVar2 < 0x17) {
          uStack_298 = CONCAT71(uStack_298._1_7_,(char)(uVar2 << 1));
          uVar3 = (ulong)&uStack_298 | 1;
          if (uVar2 != 0) goto code_r0x018e6674;
        }
        else {
          uVar8 = uVar2 + 0x10 & 0xfffffffffffffff0;
          if (uVar8 == 0) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
          }
          uVar3 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar8,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
          if (uVar3 == 0) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
          }
          uStack_298 = uVar8 | 1;
          uStack_290 = uVar2;
          uStack_288 = uVar3;
code_r0x018e6674:
          memcpy(uVar3,auStack_164,uVar2);
        }
        *(undefined1 *)(uVar3 + uVar2) = 0;
        plVar4 = (long *)Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(0x28,&UNK_027e7774/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_List.h"*/,0x20);
        if (plVar4 == (long *)0x0) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
        }
        lVar6 = lVar6 + 0x100;
        plVar4[4] = uStack_288;
        plVar4[1] = (long)param_3;
        plVar4[3] = uStack_290;
        plVar4[2] = uStack_298;
        lVar5 = *param_3;
        *plVar4 = lVar5;
        *(long **)(lVar5 + 8) = plVar4;
        *param_3 = (long)plVar4;
        param_3[2] = param_3[2] + 1;
      } while (lVar7 != lVar6);
    }
    if (lStack_180 != 0) {
      if (lStack_178 - lStack_180 != 0) {
        lStack_178 = lStack_178 + (~((lStack_178 - lStack_180) - 0x100U) & 0xffffffffffffff00);
      }
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(lStack_180);
    }
  }
  return;
}

// ==== CGameResourceDownloader::CDeleteTask::Finish()
// vaddr 0x17e68a4 | ghidra 0x18e68a4 | size 12 | symbol _ZN23CGameResourceDownloader11CDeleteTask6FinishEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN23CGameResourceDownloader11CDeleteTask6FinishEv(undefined8 *param_1)

{
  *param_1 = 4;
  return;
}

// ==== CGameResourceDownloader::CDeleteTask::ProgressRate() const
// vaddr 0x17e68b0 | ghidra 0x18e68b0 | size 32 | symbol _ZNK23CGameResourceDownloader11CDeleteTask12ProgressRateEv | lib libSOA-3.7.0.so | 2026-10-04
float _ZNK23CGameResourceDownloader11CDeleteTask12ProgressRateEv(long param_1)

{
  uint uVar1;
  ulong uVar2;
  
  uVar1 = *(uint *)(param_1 + 0x10);
  if (uVar1 != 0) {
    uVar2 = 0;
    if ((ulong)uVar1 != 0) {
      uVar2 = *(ulong *)(param_1 + 0x28) / (ulong)uVar1;
    }
    return (float)uVar2;
  }
  return 0.0;
}

// ==== CGameResourceDownloader::CEraseCheckFiber::Progress()
// vaddr 0x17e68d0 | ghidra 0x18e68d0 | size 400 | symbol _ZN23CGameResourceDownloader16CEraseCheckFiber8ProgressEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN23CGameResourceDownloader16CEraseCheckFiber8ProgressEv(long param_1)

{
  long lVar1;
  long lVar2;
  long lVar3;
  long *plVar4;
  
  if (*(int *)(param_1 + 0x18) == 1) {
    switch(*(undefined4 *)(*(long *)(param_1 + 0x48) + 8)) {
    case 0:
      CGameResourceDownloader::CVerifyTask::ProgressLocalFileCheck()();
      break;
    case 1:
      CGameResourceDownloader::CVerifyTask::ProgressServerManifestCheck()();
      break;
    case 2:
      CGameResourceDownloader::CVerifyTask::ProgressEraseCheck()();
      break;
    case 3:
      CGameResourceDownloader::CVerifyTask::ProgressEraseEpisodeDataCheck()();
      break;
    case 4:
      CGameResourceDownloader::CVerifyTask::ProgressSetupManifest()();
    }
    if (*(char *)(*(long *)(param_1 + 0x48) + 0x71) != '\0') {
      *(undefined1 *)(*(long *)(param_1 + 0x38) + 0x158) = 1;
      if (*(long **)(param_1 + 0x48) != (long *)0x0) {
        (**(code **)(**(long **)(param_1 + 0x48) + 0x10))();
        *(undefined8 *)(param_1 + 0x48) = 0;
      }
      (*(code *)PTR__ZN9Framework10CFiberUnit7DestroyEb_02c924e0)(param_1,1);
      return;
    }
  }
  else if (*(int *)(param_1 + 0x18) == 0) {
    if (*(long *)(param_1 + 0x48) != 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02866a48/*"C:\BAS_Submission\Client\Project\..\Source\Game\Resource\GameResourceDownloader.cpp"*/,0x17e0,&UNK_02866d3f/*"m_pVerifyTask isn't null.(%08x)"*/);
    }
    plVar4 = (long *)operator new(unsigned long, std::nothrow_t const&)(200,PTR__ZSt7nothrow_02cb9a80);
    if (plVar4 != (long *)0x0) {
      *plVar4 = (long)(PTR__ZTVN23CGameResourceDownloader11CVerifyTaskE_02cbe2d8 + 0x10);
      plVar4[1] = 0;
      memset(plVar4 + 2,0,99);
      *(undefined4 *)((long)plVar4 + 0x8c) = 0;
      *(undefined8 *)((long)plVar4 + 0x74) = 0;
      plVar4[0x17] = 0;
      *(undefined8 *)((long)plVar4 + 0x84) = 0;
      *(undefined8 *)((long)plVar4 + 0x7c) = 0;
      plVar4[0x16] = 0;
      plVar4[0x15] = 0;
      plVar4[0x14] = 0;
      plVar4[0x13] = 0;
      *(undefined4 *)(plVar4 + 0x18) = 0x3f800000;
    }
    *(long **)(param_1 + 0x48) = plVar4;
    lVar2 = plVar4[8];
    lVar1 = *(long *)(param_1 + 0x38);
    lVar3 = *(long *)(param_1 + 0x40);
    *(undefined1 *)((long)plVar4 + 0x72) = 0;
    *(undefined4 *)((long)plVar4 + 0x74) = 0;
    plVar4[10] = 0;
    *(undefined2 *)(plVar4 + 0xe) = 0;
    plVar4[5] = 0;
    plVar4[6] = 0;
    plVar4[2] = lVar1;
    plVar4[3] = lVar3;
    plVar4[4] = 0;
    if (lVar2 != plVar4[7]) {
      plVar4[8] = lVar2 + (~((lVar2 + -8) - plVar4[7]) & 0xfffffffffffffff8U);
    }
    plVar4[1] = 2;
    *(int *)(param_1 + 0x18) = *(int *)(param_1 + 0x18) + 1;
    *(undefined4 *)(param_1 + 0x1c) = 0;
  }
  return;
}

// ==== CGameResourceDownloader::CDownloadNode::CDownloadStream::~CDownloadStream()
// vaddr 0x17e6cc0 | ghidra 0x18e6cc0 | size 128 | symbol _ZN23CGameResourceDownloader13CDownloadNode15CDownloadStreamD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN23CGameResourceDownloader13CDownloadNode15CDownloadStreamD0Ev(long *param_1)

{
  undefined *puVar1;
  
  *param_1 = (long)(PTR__ZTVN23CGameResourceDownloader13CDownloadNode15CDownloadStreamE_02cbd948 +
                   0x10);
  if (param_1[0x38] != 0) {
    operator delete[](void*)();
    param_1[0x38] = 0;
  }
  puVar1 = PTR__ZTVN4Aska5Yayoi10Downloader14DownloadStreamE_02cc1c28 + 0x10;
  param_1[1] = (long)(PTR__ZTVN4Aska10FileStreamE_02cbc9f8 + 0x10);
  *param_1 = (long)puVar1;
  Aska::FileStream::Close()(param_1 + 1);
  param_1[2] = (long)(PTR__ZTVN4Aska4FileE_02cb6e28 + 0x10);
  if (param_1[4] != 0) {
    Aska::File::Close()();
  }
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== CGameResourceDownloader::CJournalFileWriter::~CJournalFileWriter()
// vaddr 0x17e6d40 | ghidra 0x18e6d40 | size 200 | symbol _ZN23CGameResourceDownloader18CJournalFileWriterD2Ev | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Possible PIC construction at 0x018e6df4: Changing call to branch */
/* WARNING: Removing unreachable block (ram,0x018e6df8) */

void _ZN23CGameResourceDownloader18CJournalFileWriterD2Ev(long *param_1)

{
  undefined *puVar1;
  
  puVar1 = 
  PTR__ZTVN4Aska6TArrayIN23CGameResourceDownloader18CJournalFileWriter10tWriteInfoELb0EEE_02cbd0a0;
  *param_1 = (long)(PTR__ZTVN23CGameResourceDownloader18CJournalFileWriterE_02cb86c0 + 0x10);
  param_1[0x3c] = (long)(puVar1 + 0x10);
  *(ushort *)((long)param_1 + 0x212) = *(ushort *)((long)param_1 + 0x212) | 1;
  if (param_1[0x3d] != 0) {
    operator delete[](void*)();
    param_1[0x3d] = 0;
  }
  param_1[0x3f] = 0;
  param_1[0x40] = 0;
  param_1[0x3e] = 0;
  param_1[0x35] = (long)(puVar1 + 0x10);
  *(ushort *)((long)param_1 + 0x1da) = *(ushort *)((long)param_1 + 0x1da) | 1;
  if (param_1[0x36] != 0) {
    operator delete[](void*)();
    param_1[0x36] = 0;
  }
  param_1[0x38] = 0;
  param_1[0x39] = 0;
  param_1[0x37] = 0;
  param_1[0x2f] = (long)(PTR__ZTVN4Aska10FileStreamE_02cbc9f8 + 0x10);
  Aska::FileStream::Close()(param_1 + 0x2f);
  param_1[0x30] = (long)(PTR__ZTVN4Aska4FileE_02cb6e28 + 0x10);
  if (param_1[0x32] != 0) {
    Aska::File::Close()(param_1 + 0x30);
  }
  (*(code *)PTR__ZN9Framework6CMutexD1Ev_02cb2040)(param_1 + 0x18);
  return;
}

// ==== CGameResourceDownloader::CJournalFileWriter::~CJournalFileWriter()
// vaddr 0x17e6e08 | ghidra 0x18e6e08 | size 24 | symbol _ZN23CGameResourceDownloader18CJournalFileWriterD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN23CGameResourceDownloader18CJournalFileWriterD0Ev(undefined8 param_1)

{
  CGameResourceDownloader::CJournalFileWriter::~CJournalFileWriter()();
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== CGameResourceDownloader::CEraseCheckFiber::~CEraseCheckFiber()
// vaddr 0x17e6e20 | ghidra 0x18e6e20 | size 60 | symbol _ZN23CGameResourceDownloader16CEraseCheckFiberD2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN23CGameResourceDownloader16CEraseCheckFiberD2Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN23CGameResourceDownloader16CEraseCheckFiberE_02cb6f20 + 0x10);
  if ((long *)param_1[9] != (long *)0x0) {
    (**(code **)(*(long *)param_1[9] + 0x10))();
    param_1[9] = 0;
  }
  (*(code *)PTR__ZN9Framework10CFiberUnitD1Ev_02c90ac0)(param_1);
  return;
}

// ==== CGameResourceDownloader::CEraseCheckFiber::~CEraseCheckFiber()
// vaddr 0x17e6e5c | ghidra 0x18e6e5c | size 68 | symbol _ZN23CGameResourceDownloader16CEraseCheckFiberD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN23CGameResourceDownloader16CEraseCheckFiberD0Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN23CGameResourceDownloader16CEraseCheckFiberE_02cb6f20 + 0x10);
  if ((long *)param_1[9] != (long *)0x0) {
    (**(code **)(*(long *)param_1[9] + 0x10))();
    param_1[9] = 0;
  }
  Framework::CFiberUnit::~CFiberUnit()(param_1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== CGameResourceDownloader::CVerifyTask::~CVerifyTask()
// vaddr 0x17e6ea0 | ghidra 0x18e6ea0 | size 232 | symbol _ZN23CGameResourceDownloader11CVerifyTaskD2Ev | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Possible PIC construction at 0x018e6ec8: Changing call to branch */
/* WARNING: Possible PIC construction at 0x018e6f10: Changing call to branch */
/* WARNING: Removing unreachable block (ram,0x018e6ecc) */

void _ZN23CGameResourceDownloader11CVerifyTaskD2Ev(long *param_1)

{
  long lVar1;
  long lVar2;
  
  *param_1 = (long)(PTR__ZTVN23CGameResourceDownloader11CVerifyTaskE_02cbe2d8 + 0x10);
  if (param_1[0x16] == 0) {
    lVar1 = param_1[0x14];
    param_1[0x14] = 0;
    if (lVar1 != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)();
    }
    lVar1 = param_1[0xf];
    if (lVar1 == 0) {
      lVar1 = param_1[0xb];
      if (lVar1 != 0) {
        lVar2 = param_1[0xc];
        if (lVar2 != lVar1) {
          param_1[0xc] = lVar2 + (~((lVar2 + -4) - lVar1) & 0xfffffffffffffffcU);
        }
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)();
      }
      lVar1 = param_1[7];
      if (lVar1 == 0) {
        return;
      }
      lVar2 = param_1[8];
      if (lVar2 != lVar1) {
        param_1[8] = lVar2 + (~((lVar2 + -8) - lVar1) & 0xfffffffffffffff8U);
      }
    }
    else {
      lVar2 = param_1[0x10];
      if (lVar2 != lVar1) {
        param_1[0x10] = lVar2 + (~((lVar2 + -4) - lVar1) & 0xfffffffffffffffcU);
      }
    }
  }
  (*(code *)PTR__ZN9Framework37CAssignedMemoryManagerForSTLAllocator4FreeEPv_02ca11c0)();
  return;
}

// ==== CGameResourceDownloader::CVerifyTask::~CVerifyTask()
// vaddr 0x17e6f88 | ghidra 0x18e6f88 | size 24 | symbol _ZN23CGameResourceDownloader11CVerifyTaskD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN23CGameResourceDownloader11CVerifyTaskD0Ev(undefined8 param_1)

{
  CGameResourceDownloader::CVerifyTask::~CVerifyTask()();
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::TArray<CGameResourceDownloader::CJournalFileWriter::tWriteInfo, false>::~TArray()
// vaddr 0x17e6fa0 | ghidra 0x18e6fa0 | size 68 | symbol _ZN4Aska6TArrayIN23CGameResourceDownloader18CJournalFileWriter10tWriteInfoELb0EED2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6TArrayIN23CGameResourceDownloader18CJournalFileWriter10tWriteInfoELb0EED2Ev
               (long *param_1)

{
  *param_1 = (long)(
                   PTR__ZTVN4Aska6TArrayIN23CGameResourceDownloader18CJournalFileWriter10tWriteInfoELb0EEE_02cbd0a0
                   + 0x10);
  *(ushort *)((long)param_1 + 0x32) = *(ushort *)((long)param_1 + 0x32) | 1;
  if (param_1[1] != 0) {
    operator delete[](void*)();
    param_1[1] = 0;
  }
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[2] = 0;
  return;
}

// ==== Aska::TArray<CGameResourceDownloader::CJournalFileWriter::tWriteInfo, false>::~TArray()
// vaddr 0x17e6fe4 | ghidra 0x18e6fe4 | size 60 | symbol _ZN4Aska6TArrayIN23CGameResourceDownloader18CJournalFileWriter10tWriteInfoELb0EED0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6TArrayIN23CGameResourceDownloader18CJournalFileWriter10tWriteInfoELb0EED0Ev
               (long *param_1)

{
  *param_1 = (long)(
                   PTR__ZTVN4Aska6TArrayIN23CGameResourceDownloader18CJournalFileWriter10tWriteInfoELb0EEE_02cbd0a0
                   + 0x10);
  *(ushort *)((long)param_1 + 0x32) = *(ushort *)((long)param_1 + 0x32) | 1;
  if (param_1[1] != 0) {
    operator delete[](void*)();
  }
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::TArray<CGameResourceDownloader::CDownloadNode*, false>::~TArray()
// vaddr 0x17e93dc | ghidra 0x18e93dc | size 60 | symbol _ZN4Aska6TArrayIPN23CGameResourceDownloader13CDownloadNodeELb0EED0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6TArrayIPN23CGameResourceDownloader13CDownloadNodeELb0EED0Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska6TArrayIPN23CGameResourceDownloader13CDownloadNodeELb0EEE_02cb9088
                   + 0x10);
  *(ushort *)((long)param_1 + 0x32) = *(ushort *)((long)param_1 + 0x32) | 1;
  if (param_1[1] != 0) {
    operator delete[](void*)();
  }
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::TArray<CGameResourceDownloader::tDownloadNodeInitializer, false>::~TArray()
// vaddr 0x17e9418 | ghidra 0x18e9418 | size 52 | symbol _ZN4Aska6TArrayIN23CGameResourceDownloader24tDownloadNodeInitializerELb0EED0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6TArrayIN23CGameResourceDownloader24tDownloadNodeInitializerELb0EED0Ev(long *param_1)

{
  *param_1 = (long)(
                   PTR__ZTVN4Aska6TArrayIN23CGameResourceDownloader24tDownloadNodeInitializerELb0EEE_02cc2cf8
                   + 0x10);
  *(ushort *)((long)param_1 + 0x32) = *(ushort *)((long)param_1 + 0x32) | 1;
  Aska::TArray<CGameResourceDownloader::tDownloadNodeInitializer, false>::Clear()();
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::TArray<CGameResourceDownloader::CDownloadNode*, false>::Resize(long, bool)
// vaddr 0x17e944c | ghidra 0x18e944c | size 252 | symbol _ZN4Aska6TArrayIPN23CGameResourceDownloader13CDownloadNodeELb0EE6ResizeElb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6TArrayIPN23CGameResourceDownloader13CDownloadNodeELb0EE6ResizeElb
               (long param_1,long param_2)

{
  long lVar1;
  ushort uVar2;
  long lVar3;
  
  if (param_2 == 0) {
    if ((*(byte *)(param_1 + 0x32) & 1) != 0) {
      if (*(long *)(param_1 + 8) != 0) {
        operator delete[](void*)();
        *(undefined8 *)(param_1 + 8) = 0;
      }
      *(undefined8 *)(param_1 + 0x10) = 0;
    }
    *(undefined8 *)(param_1 + 0x18) = 0;
    *(undefined8 *)(param_1 + 0x20) = 0;
    return;
  }
  lVar3 = *(long *)(param_1 + 0x10);
  if (lVar3 < param_2) {
    lVar3 = param_2 << 1;
  }
  else {
    lVar1 = lVar3 + 3;
    if (-1 < lVar3) {
      lVar1 = lVar3;
    }
    if (((lVar1 >> 2 < param_2) || ((*(ushort *)(param_1 + 0x32) & 1) == 0)) ||
       (lVar3 = param_2 * 2,
       lVar3 - *(long *)(param_1 + 0x28) == 0 || lVar3 < *(long *)(param_1 + 0x28)))
    goto code_r0x018e952c;
  }
  if (*(long *)(param_1 + 8) == 0) {
    lVar3 = *(long *)(param_1 + 0x28);
    if (*(long *)(param_1 + 0x28) <= param_2) {
      lVar3 = param_2;
    }
    lVar1 = operator new[](unsigned long, std::nothrow_t const&)(lVar3 << 3,PTR__ZSt7nothrow_02cb9a80);
    *(long *)(param_1 + 8) = lVar1;
    if (lVar1 == 0) {
      *(ushort *)(param_1 + 0x30) = *(ushort *)(param_1 + 0x30) | 1;
      return;
    }
    uVar2 = *(ushort *)(param_1 + 0x30) & 0xfffe;
code_r0x018e9524:
    *(ushort *)(param_1 + 0x30) = uVar2;
  }
  else {
    lVar1 = operator new[](unsigned long, void*, unsigned long)(param_2 << 4,*(long *)(param_1 + 8),4);
    if (lVar1 == 0) {
      uVar2 = *(ushort *)(param_1 + 0x30) | 1;
      goto code_r0x018e9524;
    }
    *(long *)(param_1 + 8) = lVar1;
    *(long *)(param_1 + 0x10) = lVar3;
    *(long *)(param_1 + 0x18) = param_2;
  }
  *(long *)(param_1 + 0x10) = lVar3;
code_r0x018e952c:
  *(long *)(param_1 + 0x18) = param_2;
  return;
}

// ==== std::__ndk1::function<void (char const*, CGameResourceDownloader::iErrorCode)>::swap(std::__ndk1::function<void (char const*, CGameResourceDownloader::iErrorCode)>&)
// vaddr 0x17e967c | ghidra 0x18e967c | size 308 | symbol _ZNSt6__ndk18functionIFvPKcN23CGameResourceDownloader10iErrorCodeEEE4swapERS6_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZNSt6__ndk18functionIFvPKcN23CGameResourceDownloader10iErrorCodeEEE4swapERS6_
               (long *param_1,long *param_2)

{
  long *plVar1;
  long *plVar2;
  long alStack_40 [4];
  
  plVar1 = (long *)param_1[4];
  if ((plVar1 == param_1) && ((long *)param_2[4] == param_2)) {
    (**(code **)(*plVar1 + 0x18))(plVar1,alStack_40);
    (**(code **)(*(long *)param_1[4] + 0x20))();
    param_1[4] = 0;
    (**(code **)(*(long *)param_2[4] + 0x18))((long *)param_2[4],param_1);
    (**(code **)(*(long *)param_2[4] + 0x20))();
    param_2[4] = 0;
    param_1[4] = (long)param_1;
    (**(code **)(alStack_40[0] + 0x18))(alStack_40,param_2);
    (**(code **)(alStack_40[0] + 0x20))(alStack_40);
  }
  else {
    if (param_1 != plVar1) {
      plVar2 = (long *)param_2[4];
      if (param_2 != plVar2) {
        param_1[4] = (long)plVar2;
        param_2[4] = (long)plVar1;
        return;
      }
      (**(code **)(*plVar2 + 0x18))(plVar2,param_1);
      (**(code **)(*(long *)param_2[4] + 0x20))();
      param_2[4] = param_1[4];
      param_1[4] = (long)param_1;
      return;
    }
    (**(code **)(*plVar1 + 0x18))(plVar1,param_2);
    (**(code **)(*(long *)param_1[4] + 0x20))();
    param_1[4] = param_2[4];
  }
  param_2[4] = (long)param_2;
  return;
}

// ==== Aska::TArray<CGameResourceDownloader::tDownloadNodeInitializer, false>::SetAt(long, CGameResourceDownloader::tDownloadNodeInitializer const&)
// vaddr 0x17e97b0 | ghidra 0x18e97b0 | size 464 | symbol _ZN4Aska6TArrayIN23CGameResourceDownloader24tDownloadNodeInitializerELb0EE5SetAtElRKS2_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6TArrayIN23CGameResourceDownloader24tDownloadNodeInitializerELb0EE5SetAtElRKS2_
               (long param_1,long param_2,ulong *param_3)

{
  ulong uVar1;
  ulong uVar2;
  ulong *puVar3;
  code *pcVar4;
  ulong uVar5;
  ulong uVar6;
  ulong uStack_90;
  ulong uStack_88;
  ulong uStack_80;
  long alStack_70 [4];
  long *plStack_50;
  
  if (param_2 < 0) {
    return;
  }
  if (param_2 < *(long *)(param_1 + 0x18)) {
    CGameResourceDownloader::tDownloadNodeInitializer::operator=(CGameResourceDownloader::tDownloadNodeInitializer const&)(*(long *)(param_1 + 8) + param_2 * 0x50,param_3);
    return;
  }
  uStack_88 = 0;
  uStack_80 = 0;
  uStack_90 = 0;
  if ((*param_3 & 1) == 0) {
    uStack_80 = param_3[2];
    uStack_88 = param_3[1];
    uStack_90 = *param_3;
    puVar3 = (ulong *)param_3[8];
    if (puVar3 != (ulong *)0x0) goto code_r0x018e9820;
code_r0x018e98e4:
    plStack_50 = (long *)0x0;
  }
  else {
    uVar1 = param_3[1];
    uVar2 = param_3[2];
    if (uVar1 < 0x17) {
      uVar5 = (ulong)&uStack_90 | 1;
      uStack_90 = (uVar1 & 0x7f) << 1;
      if (uVar1 != 0) goto code_r0x018e98c8;
    }
    else {
      uVar6 = uVar1 + 0x10 & 0xfffffffffffffff0;
      if (uVar6 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
      }
      uVar5 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar6,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
      if (uVar5 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
      }
      uStack_90 = uVar6 | 1;
      uStack_88 = uVar1;
      uStack_80 = uVar5;
code_r0x018e98c8:
      memcpy(uVar5,uVar2,uVar1);
    }
    *(undefined1 *)(uVar5 + uVar1) = 0;
    puVar3 = (ulong *)param_3[8];
    if (puVar3 == (ulong *)0x0) goto code_r0x018e98e4;
code_r0x018e9820:
    if (param_3 + 4 == puVar3) {
      plStack_50 = alStack_70;
      (**(code **)(*puVar3 + 0x18))();
    }
    else {
      plStack_50 = (long *)(**(code **)(*puVar3 + 0x10))();
    }
  }
  Aska::TArray<CGameResourceDownloader::tDownloadNodeInitializer, false>::Resize(long, bool)(param_1,param_2 + 1,0);
  CGameResourceDownloader::tDownloadNodeInitializer::operator=(CGameResourceDownloader::tDownloadNodeInitializer const&)(*(long *)(param_1 + 8) + param_2 * 0x50,&uStack_90);
  if (alStack_70 == plStack_50) {
    pcVar4 = *(code **)(*plStack_50 + 0x20);
  }
  else {
    if (plStack_50 == (long *)0x0) goto code_r0x018e9958;
    pcVar4 = *(code **)(*plStack_50 + 0x28);
  }
  (*pcVar4)();
code_r0x018e9958:
  if ((uStack_90 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_80);
  }
  return;
}

// ==== Aska::TArray<CGameResourceDownloader::tDownloadNodeInitializer, false>::Resize(long, bool)
// vaddr 0x17e9980 | ghidra 0x18e9980 | size 516 | symbol _ZN4Aska6TArrayIN23CGameResourceDownloader24tDownloadNodeInitializerELb0EE6ResizeElb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6TArrayIN23CGameResourceDownloader24tDownloadNodeInitializerELb0EE6ResizeElb
               (long param_1,long param_2,ulong param_3)

{
  long *plVar1;
  long *plVar2;
  undefined8 *puVar3;
  long lVar4;
  long lVar5;
  code *pcVar6;
  long lVar7;
  
  if (param_2 == 0) {
    (*(code *)
      PTR__ZN4Aska6TArrayIN23CGameResourceDownloader24tDownloadNodeInitializerELb0EE5ClearEv_02c96308
    )(param_1);
    return;
  }
  lVar4 = *(long *)(param_1 + 0x10);
  if (lVar4 < param_2) {
    lVar4 = param_2 << 1;
    lVar5 = *(long *)(param_1 + 8);
  }
  else {
    lVar5 = lVar4 + 3;
    if (-1 < lVar4) {
      lVar5 = lVar4;
    }
    if (((lVar5 >> 2 < param_2) || ((*(ushort *)(param_1 + 0x32) & 1) == 0)) ||
       (lVar4 = param_2 * 2,
       lVar4 - *(long *)(param_1 + 0x28) == 0 || lVar4 < *(long *)(param_1 + 0x28))) {
      plVar1 = (long *)(param_1 + 0x18);
      if (((param_3 & 1) == 0) && (lVar4 = *plVar1, lVar4 < param_2)) {
        lVar5 = lVar4 * 0x50;
        lVar4 = param_2 - lVar4;
        do {
          lVar4 = lVar4 + -1;
          puVar3 = (undefined8 *)(*(long *)(param_1 + 8) + lVar5);
          lVar5 = lVar5 + 0x50;
          puVar3[1] = 0;
          puVar3[2] = 0;
          *puVar3 = 0;
          puVar3[8] = 0;
        } while (lVar4 != 0);
      }
      if (param_2 < *plVar1) {
        lVar5 = param_2 * 0x50;
        lVar4 = param_2;
        do {
          lVar7 = *(long *)(param_1 + 8);
          plVar2 = *(long **)(lVar7 + lVar5 + 0x40);
          if ((long *)(lVar7 + lVar5 + 0x20) == plVar2) {
            pcVar6 = *(code **)(*plVar2 + 0x20);
code_r0x018e9aac:
            (*pcVar6)();
          }
          else if (plVar2 != (long *)0x0) {
            pcVar6 = *(code **)(*plVar2 + 0x28);
            goto code_r0x018e9aac;
          }
          if ((*(byte *)(lVar7 + lVar5) & 1) != 0) {
            Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(*(undefined8 *)(lVar7 + lVar5 + 0x10));
          }
          lVar4 = lVar4 + 1;
          lVar5 = lVar5 + 0x50;
        } while (lVar4 < *plVar1);
      }
      goto code_r0x018e9b5c;
    }
    lVar5 = *(long *)(param_1 + 8);
  }
  if (lVar5 == 0) {
    lVar4 = *(long *)(param_1 + 0x28);
    if (*(long *)(param_1 + 0x28) <= param_2) {
      lVar4 = param_2;
    }
    puVar3 = (undefined8 *)operator new[](unsigned long, std::nothrow_t const&)(lVar4 * 0x50,PTR__ZSt7nothrow_02cb9a80);
    *(undefined8 **)(param_1 + 8) = puVar3;
    if (puVar3 == (undefined8 *)0x0) {
      *(ushort *)(param_1 + 0x30) = *(ushort *)(param_1 + 0x30) | 1;
      return;
    }
    if ((0 < param_2) && ((param_3 & 1) == 0)) {
      lVar5 = param_2 + -1;
      puVar3[1] = 0;
      puVar3[2] = 0;
      *puVar3 = 0;
      puVar3[8] = 0;
      if (lVar5 != 0) {
        lVar7 = 0x90;
        do {
          lVar5 = lVar5 + -1;
          puVar3 = (undefined8 *)(*(long *)(param_1 + 8) + lVar7);
          lVar7 = lVar7 + 0x50;
          puVar3[-7] = 0;
          puVar3[-6] = 0;
          puVar3[-8] = 0;
          *puVar3 = 0;
        } while (lVar5 != 0);
      }
    }
    *(ushort *)(param_1 + 0x30) = *(ushort *)(param_1 + 0x30) & 0xfffe;
  }
  else {
    Aska::TArray<CGameResourceDownloader::tDownloadNodeInitializer, false>::ForceRealloc(long, long, CGameResourceDownloader::tDownloadNodeInitializer const*, StBoolean<false>)(param_1,param_2,lVar4,0);
  }
  *(long *)(param_1 + 0x10) = lVar4;
code_r0x018e9b5c:
  *(long *)(param_1 + 0x18) = param_2;
  return;
}

// ==== Aska::TArray<CGameResourceDownloader::tDownloadNodeInitializer, false>::ForceRealloc(long, long, CGameResourceDownloader::tDownloadNodeInitializer const*, StBoolean<false>)
// vaddr 0x17e9b84 | ghidra 0x18e9b84 | size 384 | symbol _ZN4Aska6TArrayIN23CGameResourceDownloader24tDownloadNodeInitializerELb0EE12ForceReallocEllPKS2_9StBooleanILb0EE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6TArrayIN23CGameResourceDownloader24tDownloadNodeInitializerELb0EE12ForceReallocEllPKS2_9StBooleanILb0EE
               (long param_1,long param_2,long param_3,long param_4)

{
  undefined8 *puVar1;
  long lVar2;
  long *plVar3;
  code *pcVar4;
  long lVar5;
  long lVar6;
  long lVar7;
  long *plVar8;
  long lVar9;
  
  lVar6 = *(long *)(param_1 + 8);
  lVar2 = operator new[](unsigned long, std::nothrow_t const&)(param_3 * 0x50,PTR__ZSt7nothrow_02cb9a80);
  *(long *)(param_1 + 8) = lVar2;
  if (lVar2 == 0) {
    *(ushort *)(param_1 + 0x30) = *(ushort *)(param_1 + 0x30) | 1;
    return;
  }
  if (param_4 == 0) {
    lVar5 = *(long *)(param_1 + 0x18);
    lVar9 = param_2;
    if (lVar5 <= param_2) {
      lVar9 = lVar5;
    }
    lVar7 = lVar6;
    if (0 < lVar9) {
      do {
        Aska::TArray<CGameResourceDownloader::tDownloadNodeInitializer, false>::CallCopyConstructor(CGameResourceDownloader::tDownloadNodeInitializer*, CGameResourceDownloader::tDownloadNodeInitializer const&, StBoolean<false>)(param_1,lVar2,lVar7);
        lVar9 = lVar9 + -1;
        lVar2 = lVar2 + 0x50;
        lVar7 = lVar7 + 0x50;
      } while (lVar9 != 0);
      lVar5 = *(long *)(param_1 + 0x18);
    }
    if (lVar5 < param_2) {
      lVar2 = lVar5 * 0x50;
      lVar5 = param_2 - lVar5;
      do {
        lVar5 = lVar5 + -1;
        puVar1 = (undefined8 *)(*(long *)(param_1 + 8) + lVar2);
        lVar2 = lVar2 + 0x50;
        puVar1[1] = 0;
        puVar1[2] = 0;
        *puVar1 = 0;
        puVar1[8] = 0;
      } while (lVar5 != 0);
    }
  }
  else {
    lVar9 = param_2;
    if (0 < param_2) {
      do {
        Aska::TArray<CGameResourceDownloader::tDownloadNodeInitializer, false>::CallCopyConstructor(CGameResourceDownloader::tDownloadNodeInitializer*, CGameResourceDownloader::tDownloadNodeInitializer const&, StBoolean<false>)(param_1,lVar2,param_4);
        lVar9 = lVar9 + -1;
        param_4 = param_4 + 0x50;
        lVar2 = lVar2 + 0x50;
      } while (lVar9 != 0);
    }
  }
  if (*(long *)(param_1 + 0x18) < 1) {
    if (lVar6 == 0) goto code_r0x018e9cec;
  }
  else {
    lVar2 = 0;
    plVar8 = (long *)(lVar6 + 0x20);
    do {
      plVar3 = (long *)plVar8[4];
      if (plVar8 == plVar3) {
        pcVar4 = *(code **)(*plVar3 + 0x20);
code_r0x018e9cb4:
        (*pcVar4)();
      }
      else if (plVar3 != (long *)0x0) {
        pcVar4 = *(code **)(*plVar3 + 0x28);
        goto code_r0x018e9cb4;
      }
      if ((*(byte *)(plVar8 + -4) & 1) != 0) {
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar8[-2]);
      }
      lVar2 = lVar2 + 1;
      plVar8 = plVar8 + 10;
    } while (lVar2 < *(long *)(param_1 + 0x18));
  }
  operator delete[](void*)(lVar6);
code_r0x018e9cec:
  *(long *)(param_1 + 0x10) = param_3;
  *(long *)(param_1 + 0x18) = param_2;
  return;
}

// ==== Aska::TArray<CGameResourceDownloader::tDownloadNodeInitializer, false>::CallCopyConstructor(CGameResourceDownloader::tDownloadNodeInitializer*, CGameResourceDownloader::tDownloadNodeInitializer const&, StBoolean<false>)
// vaddr 0x17e9d04 | ghidra 0x18e9d04 | size 320 | symbol _ZN4Aska6TArrayIN23CGameResourceDownloader24tDownloadNodeInitializerELb0EE19CallCopyConstructorEPS2_RKS2_9StBooleanILb0EE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6TArrayIN23CGameResourceDownloader24tDownloadNodeInitializerELb0EE19CallCopyConstructorEPS2_RKS2_9StBooleanILb0EE
               (undefined8 param_1,ulong *param_2,ulong *param_3)

{
  ulong uVar1;
  ulong *puVar2;
  ulong uVar3;
  ulong uVar4;
  ulong uVar5;
  
  param_2[1] = 0;
  param_2[2] = 0;
  *param_2 = 0;
  if ((*param_3 & 1) == 0) {
    param_2[2] = param_3[2];
    uVar3 = *param_3;
    param_2[1] = param_3[1];
    *param_2 = uVar3;
    puVar2 = (ulong *)param_3[8];
    goto joined_r0x018e9e00;
  }
  uVar3 = param_3[1];
  uVar1 = param_3[2];
  if (uVar3 < 0x17) {
    uVar4 = (long)param_2 + 1;
    *(char *)param_2 = (char)(uVar3 << 1);
    if (uVar3 != 0) goto code_r0x018e9de8;
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
    param_2[1] = uVar3;
    param_2[2] = uVar4;
    *param_2 = uVar5 | 1;
code_r0x018e9de8:
    memcpy(uVar4,uVar1,uVar3);
  }
  *(undefined1 *)(uVar4 + uVar3) = 0;
  puVar2 = (ulong *)param_3[8];
joined_r0x018e9e00:
  if (puVar2 == (ulong *)0x0) {
    param_2[8] = 0;
  }
  else {
    if (param_3 + 4 == puVar2) {
      param_2[8] = (ulong)(param_2 + 4);
                    /* WARNING: Could not recover jumptable at 0x018e9e40. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (**(code **)(*(long *)param_3[8] + 0x18))();
      return;
    }
    uVar3 = (**(code **)(*puVar2 + 0x10))();
    param_2[8] = uVar3;
  }
  return;
}

// ==== CGameResourceDownloader::tDownloadNodeInitializer::operator=(CGameResourceDownloader::tDownloadNodeInitializer const&)
// vaddr 0x17e9e44 | ghidra 0x18e9e44 | size 364 | symbol _ZN23CGameResourceDownloader24tDownloadNodeInitializeraSERKS0_ | lib libSOA-3.7.0.so | 2026-10-04
ulong * _ZN23CGameResourceDownloader24tDownloadNodeInitializeraSERKS0_
                  (ulong *param_1,ulong *param_2)

{
  ulong uVar1;
  byte *pbVar2;
  ulong *puVar3;
  ulong uVar4;
  long lVar5;
  ulong uVar6;
  code *pcVar7;
  byte *pbVar8;
  long alStack_60 [4];
  long *plStack_40;
  
  if (param_1 == param_2) goto code_r0x018e9f14;
  uVar1 = param_2[1];
  pbVar2 = (byte *)param_2[2];
  uVar6 = (ulong)(byte)*param_1;
  if (((byte)*param_2 & 1) == 0) {
    pbVar2 = (byte *)((long)param_2 + 1);
    uVar1 = (ulong)(byte)((byte)*param_2 >> 1);
  }
  if (((byte)*param_1 & 1) == 0) {
    uVar4 = 0x16;
    lVar5 = uVar1 - 0x16;
    if (0x15 < uVar1 && lVar5 != 0) {
code_r0x018e9eb4:
      if ((uVar6 & 1) == 0) {
        uVar6 = (ulong)(((uint)uVar6 & 0xfe) >> 1);
      }
      else {
        uVar6 = param_1[1];
      }
      string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(param_1,uVar4,lVar5,uVar6,0,uVar6,uVar1);
      goto code_r0x018e9f14;
    }
  }
  else {
    uVar6 = *param_1;
    uVar4 = (uVar6 & 0xfffffffffffffffe) - 1;
    lVar5 = uVar1 - uVar4;
    if (uVar4 <= uVar1 && lVar5 != 0) goto code_r0x018e9eb4;
  }
  if ((uVar6 & 1) == 0) {
    pbVar8 = (byte *)((long)param_1 + 1);
  }
  else {
    pbVar8 = (byte *)param_1[2];
  }
  if (uVar1 != 0) {
    memmove(pbVar8,pbVar2,uVar1);
  }
  pbVar8[uVar1] = 0;
  if ((*param_1 & 1) == 0) {
    *(byte *)param_1 = (byte)(uVar1 << 1);
  }
  else {
    param_1[1] = uVar1;
  }
code_r0x018e9f14:
  puVar3 = (ulong *)param_2[8];
  if (puVar3 == (ulong *)0x0) {
    plStack_40 = (long *)0x0;
  }
  else if (param_2 + 4 == puVar3) {
    plStack_40 = alStack_60;
    (**(code **)(*puVar3 + 0x18))(puVar3,alStack_60);
  }
  else {
    plStack_40 = (long *)(**(code **)(*puVar3 + 0x10))();
  }
  std::__ndk1::function<void (char const*, CGameResourceDownloader::iErrorCode)>::swap(std::__ndk1::function<void (char const*, CGameResourceDownloader::iErrorCode)>&)(alStack_60,param_1 + 4);
  if (alStack_60 == plStack_40) {
    pcVar7 = *(code **)(*plStack_40 + 0x20);
  }
  else {
    if (plStack_40 == (long *)0x0) {
      return param_1;
    }
    pcVar7 = *(code **)(*plStack_40 + 0x28);
  }
  (*pcVar7)();
  return param_1;
}

// ==== std::__ndk1::__hash_table<std::__ndk1::__hash_value_type<unsigned int, CGameResourceDownloader::CDownloadNode*>, std::__ndk1::__unordered_map_hasher<unsigned int, std::__ndk1::__hash_value_type<unsigned int, CGameResourceDownloader::CDownloadNode*>, std::__ndk1::hash<unsigned int>, true>, std::__ndk1::__unordered_map_equal<unsigned int, std::__ndk1::__hash_value_type<unsigned int, CGameResourceDownloader::CDownloadNode*>, std::__ndk1::equal_to<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__hash_value_type<unsigned int, CGameResourceDownloader::CDownloadNode*>, Framework::CSTLUnorderedMapAllocatorInf> >::rehash(unsigned long)
// vaddr 0x17f4fec | ghidra 0x18f4fec | size 208 | symbol _ZNSt6__ndk112__hash_tableINS_17__hash_value_typeIjPN23CGameResourceDownloader13CDownloadNodeEEENS_22__unordered_map_hasherIjS5_NS_4hashIjEELb1EEENS_21__unordered_map_equalIjS5_NS_8equal_toIjEELb1EEEN9Framework13CSTLAllocatorIS5_NSE_28CSTLUnorderedMapAllocatorInfEEEE6rehashEm | lib libSOA-3.7.0.so | 2026-10-04
void _ZNSt6__ndk112__hash_tableINS_17__hash_value_typeIjPN23CGameResourceDownloader13CDownloadNodeEEENS_22__unordered_map_hasherIjS5_NS_4hashIjEELb1EEENS_21__unordered_map_equalIjS5_NS_8equal_toIjEELb1EEEN9Framework13CSTLAllocatorIS5_NSE_28CSTLUnorderedMapAllocatorInfEEEE6rehashEm
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
code_r0x011bfdd0:
    (*(code *)
      PTR__ZNSt6__ndk112__hash_tableINS_17__hash_value_typeIjPN23CGameResourceDownloader13CDownloadNodeEEENS_22__unordered_map_hasherIjS5_NS_4hashIjEELb1EEENS_21__unordered_map_equalIjS5_NS_8equal_toIjEELb1EEEN9Framework13CSTLAllocatorIS5_NSE_28CSTLUnorderedMapAllocatorInfEEEE8__rehashEm_02c97ed8
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
    if (uVar1 < uVar2) goto code_r0x011bfdd0;
  }
  return;
}

// ==== std::__ndk1::__hash_table<std::__ndk1::__hash_value_type<unsigned int, CGameResourceDownloader::CDownloadNode*>, std::__ndk1::__unordered_map_hasher<unsigned int, std::__ndk1::__hash_value_type<unsigned int, CGameResourceDownloader::CDownloadNode*>, std::__ndk1::hash<unsigned int>, true>, std::__ndk1::__unordered_map_equal<unsigned int, std::__ndk1::__hash_value_type<unsigned int, CGameResourceDownloader::CDownloadNode*>, std::__ndk1::equal_to<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__hash_value_type<unsigned int, CGameResourceDownloader::CDownloadNode*>, Framework::CSTLUnorderedMapAllocatorInf> >::__rehash(unsigned long)
// vaddr 0x17f50bc | ghidra 0x18f50bc | size 524 | symbol _ZNSt6__ndk112__hash_tableINS_17__hash_value_typeIjPN23CGameResourceDownloader13CDownloadNodeEEENS_22__unordered_map_hasherIjS5_NS_4hashIjEELb1EEENS_21__unordered_map_equalIjS5_NS_8equal_toIjEELb1EEEN9Framework13CSTLAllocatorIS5_NSE_28CSTLUnorderedMapAllocatorInfEEEE8__rehashEm | lib libSOA-3.7.0.so | 2026-10-04
void _ZNSt6__ndk112__hash_tableINS_17__hash_value_typeIjPN23CGameResourceDownloader13CDownloadNodeEEENS_22__unordered_map_hasherIjS5_NS_4hashIjEELb1EEENS_21__unordered_map_equalIjS5_NS_8equal_toIjEELb1EEEN9Framework13CSTLAllocatorIS5_NSE_28CSTLUnorderedMapAllocatorInfEEEE8__rehashEm
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
joined_r0x018f5180:
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
              if (*plVar8 == 0) goto code_r0x018f52a4;
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
            if (*plVar8 == 0) goto code_r0x018f52a4;
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
code_r0x018f52a4:
  *plVar8 = (long)plVar5;
  plVar5 = plVar6;
  plVar6 = (long *)*plVar6;
  uVar3 = uVar7;
  goto joined_r0x018f5180;
}

// ==== std::__ndk1::__hash_table<std::__ndk1::__hash_value_type<unsigned int, CGameResourceDownloader::CDownloadNode::tCallbackInfo>, std::__ndk1::__unordered_map_hasher<unsigned int, std::__ndk1::__hash_value_type<unsigned int, CGameResourceDownloader::CDownloadNode::tCallbackInfo>, std::__ndk1::hash<unsigned int>, true>, std::__ndk1::__unordered_map_equal<unsigned int, std::__ndk1::__hash_value_type<unsigned int, CGameResourceDownloader::CDownloadNode::tCallbackInfo>, std::__ndk1::equal_to<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__hash_value_type<unsigned int, CGameResourceDownloader::CDownloadNode::tCallbackInfo>, Framework::CSTLUnorderedMapAllocatorInf> >::rehash(unsigned long)
// vaddr 0x17f646c | ghidra 0x18f646c | size 208 | symbol _ZNSt6__ndk112__hash_tableINS_17__hash_value_typeIjN23CGameResourceDownloader13CDownloadNode13tCallbackInfoEEENS_22__unordered_map_hasherIjS5_NS_4hashIjEELb1EEENS_21__unordered_map_equalIjS5_NS_8equal_toIjEELb1EEEN9Framework13CSTLAllocatorIS5_NSE_28CSTLUnorderedMapAllocatorInfEEEE6rehashEm | lib libSOA-3.7.0.so | 2026-10-04
void _ZNSt6__ndk112__hash_tableINS_17__hash_value_typeIjN23CGameResourceDownloader13CDownloadNode13tCallbackInfoEEENS_22__unordered_map_hasherIjS5_NS_4hashIjEELb1EEENS_21__unordered_map_equalIjS5_NS_8equal_toIjEELb1EEEN9Framework13CSTLAllocatorIS5_NSE_28CSTLUnorderedMapAllocatorInfEEEE6rehashEm
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
code_r0x011bdb40:
    (*(code *)
      PTR__ZNSt6__ndk112__hash_tableINS_17__hash_value_typeIjN23CGameResourceDownloader13CDownloadNode13tCallbackInfoEEENS_22__unordered_map_hasherIjS5_NS_4hashIjEELb1EEENS_21__unordered_map_equalIjS5_NS_8equal_toIjEELb1EEEN9Framework13CSTLAllocatorIS5_NSE_28CSTLUnorderedMapAllocatorInfEEEE8__rehashEm_02c96d90
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
    if (uVar1 < uVar2) goto code_r0x011bdb40;
  }
  return;
}

// ==== std::__ndk1::__hash_table<std::__ndk1::__hash_value_type<unsigned int, CGameResourceDownloader::CDownloadNode::tCallbackInfo>, std::__ndk1::__unordered_map_hasher<unsigned int, std::__ndk1::__hash_value_type<unsigned int, CGameResourceDownloader::CDownloadNode::tCallbackInfo>, std::__ndk1::hash<unsigned int>, true>, std::__ndk1::__unordered_map_equal<unsigned int, std::__ndk1::__hash_value_type<unsigned int, CGameResourceDownloader::CDownloadNode::tCallbackInfo>, std::__ndk1::equal_to<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__hash_value_type<unsigned int, CGameResourceDownloader::CDownloadNode::tCallbackInfo>, Framework::CSTLUnorderedMapAllocatorInf> >::__rehash(unsigned long)
// vaddr 0x17f653c | ghidra 0x18f653c | size 524 | symbol _ZNSt6__ndk112__hash_tableINS_17__hash_value_typeIjN23CGameResourceDownloader13CDownloadNode13tCallbackInfoEEENS_22__unordered_map_hasherIjS5_NS_4hashIjEELb1EEENS_21__unordered_map_equalIjS5_NS_8equal_toIjEELb1EEEN9Framework13CSTLAllocatorIS5_NSE_28CSTLUnorderedMapAllocatorInfEEEE8__rehashEm | lib libSOA-3.7.0.so | 2026-10-04
void _ZNSt6__ndk112__hash_tableINS_17__hash_value_typeIjN23CGameResourceDownloader13CDownloadNode13tCallbackInfoEEENS_22__unordered_map_hasherIjS5_NS_4hashIjEELb1EEENS_21__unordered_map_equalIjS5_NS_8equal_toIjEELb1EEEN9Framework13CSTLAllocatorIS5_NSE_28CSTLUnorderedMapAllocatorInfEEEE8__rehashEm
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
joined_r0x018f6600:
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
              if (*plVar8 == 0) goto code_r0x018f6724;
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
            if (*plVar8 == 0) goto code_r0x018f6724;
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
code_r0x018f6724:
  *plVar8 = (long)plVar5;
  plVar5 = plVar6;
  plVar6 = (long *)*plVar6;
  uVar3 = uVar7;
  goto joined_r0x018f6600;
}

// ==== void std::__ndk1::vector<CGameResourceDownloader::CVerifyTask::tFolderInfo, Framework::CSTLAllocator<CGameResourceDownloader::CVerifyTask::tFolderInfo, Framework::CSTLVectorAllocatorInf> >::__push_back_slow_path<CGameResourceDownloader::CVerifyTask::tFolderInfo const&>(CGameResourceDownloader::CVerifyTask::tFolderInfo const&)
// vaddr 0x17f6b44 | ghidra 0x18f6b44 | size 324 | symbol _ZNSt6__ndk16vectorIN23CGameResourceDownloader11CVerifyTask11tFolderInfoEN9Framework13CSTLAllocatorIS3_NS4_22CSTLVectorAllocatorInfEEEE21__push_back_slow_pathIRKS3_EEvOT_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZNSt6__ndk16vectorIN23CGameResourceDownloader11CVerifyTask11tFolderInfoEN9Framework13CSTLAllocatorIS3_NS4_22CSTLVectorAllocatorInfEEEE21__push_back_slow_pathIRKS3_EEvOT_
               (long *param_1,undefined8 param_2)

{
  long lVar1;
  long lVar2;
  ulong uVar3;
  long lVar4;
  long lVar5;
  long lVar6;
  ulong uVar7;
  
  lVar2 = param_1[2] - *param_1;
  lVar5 = param_1[1] - *param_1 >> 8;
  if ((ulong)(lVar2 >> 8) < 0x7fffffffffffff) {
    uVar3 = lVar2 >> 7;
    uVar7 = lVar5 + 1U;
    if (lVar5 + 1U <= uVar3) {
      uVar7 = uVar3;
    }
    if (uVar7 == 0) {
      lVar2 = 0;
      lVar5 = lVar5 << 8;
      goto joined_r0x018f6c80;
    }
  }
  else {
    uVar7 = 0xffffffffffffff;
  }
  lVar2 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar7 << 8,&UNK_027dc536/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Vector.h"*/,0x20);
  if (lVar2 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    lVar5 = lVar5 * 0x100;
  }
  else {
    lVar5 = lVar2 + lVar5 * 0x100;
  }
joined_r0x018f6c80:
  if (lVar5 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
  }
  memcpy(lVar5,param_2,0x100);
  lVar4 = *param_1;
  lVar6 = param_1[1];
  lVar1 = lVar5 + 0x100;
  if (lVar6 != lVar4) {
    do {
      lVar6 = lVar6 + -0x100;
      memcpy(lVar5 + -0x100,lVar6,0x100);
      lVar5 = lVar5 + -0x100;
    } while (lVar4 != lVar6);
    lVar4 = *param_1;
  }
  *param_1 = lVar5;
  param_1[1] = lVar1;
  param_1[2] = lVar2 + uVar7 * 0x100;
  if (lVar4 != 0) {
    (*(code *)PTR__ZN9Framework37CAssignedMemoryManagerForSTLAllocator4FreeEPv_02ca11c0)(lVar4);
    return;
  }
  return;
}

// ==== Aska::TArray<CGameResourceDownloader::CJournalFileWriter::tWriteInfo, false>::Resize(long, bool)
// vaddr 0x17f6c88 | ghidra 0x18f6c88 | size 348 | symbol _ZN4Aska6TArrayIN23CGameResourceDownloader18CJournalFileWriter10tWriteInfoELb0EE6ResizeElb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6TArrayIN23CGameResourceDownloader18CJournalFileWriter10tWriteInfoELb0EE6ResizeElb
               (long param_1,long param_2)

{
  long lVar1;
  ushort uVar2;
  long lVar3;
  long lVar4;
  long lVar5;
  long lVar6;
  
  if (param_2 == 0) {
    if ((*(byte *)(param_1 + 0x32) & 1) != 0) {
      if (*(long *)(param_1 + 8) != 0) {
        operator delete[](void*)();
        *(undefined8 *)(param_1 + 8) = 0;
      }
      *(undefined8 *)(param_1 + 0x10) = 0;
    }
    *(undefined8 *)(param_1 + 0x18) = 0;
    *(undefined8 *)(param_1 + 0x20) = 0;
    return;
  }
  lVar3 = *(long *)(param_1 + 0x10);
  if (lVar3 < param_2) {
    lVar3 = param_2 << 1;
  }
  else {
    lVar4 = lVar3 + 3;
    if (-1 < lVar3) {
      lVar4 = lVar3;
    }
    if (((lVar4 >> 2 < param_2) || ((*(ushort *)(param_1 + 0x32) & 1) == 0)) ||
       (lVar3 = param_2 * 2,
       lVar3 - *(long *)(param_1 + 0x28) == 0 || lVar3 < *(long *)(param_1 + 0x28)))
    goto code_r0x018f6dc0;
  }
  lVar4 = *(long *)(param_1 + 8);
  if (lVar4 == 0) {
    lVar3 = *(long *)(param_1 + 0x28);
    if (*(long *)(param_1 + 0x28) <= param_2) {
      lVar3 = param_2;
    }
    lVar4 = operator new[](unsigned long, std::nothrow_t const&)(lVar3 * 0x168,PTR__ZSt7nothrow_02cb9a80);
    *(long *)(param_1 + 8) = lVar4;
    if (lVar4 == 0) {
      *(ushort *)(param_1 + 0x30) = *(ushort *)(param_1 + 0x30) | 1;
      return;
    }
    uVar2 = *(ushort *)(param_1 + 0x30) & 0xfffe;
code_r0x018f6db8:
    *(ushort *)(param_1 + 0x30) = uVar2;
  }
  else {
    lVar1 = operator new[](unsigned long, std::nothrow_t const&)(param_2 * 0x2d0,PTR__ZSt7nothrow_02cb9a80);
    *(long *)(param_1 + 8) = lVar1;
    if (lVar1 == 0) {
      uVar2 = *(ushort *)(param_1 + 0x30) | 1;
      goto code_r0x018f6db8;
    }
    lVar6 = param_2;
    if (*(long *)(param_1 + 0x18) <= param_2) {
      lVar6 = *(long *)(param_1 + 0x18);
    }
    lVar5 = lVar4;
    if (0 < lVar6) {
      do {
        memcpy(lVar1,lVar5,0x168);
        lVar6 = lVar6 + -1;
        lVar1 = lVar1 + 0x168;
        lVar5 = lVar5 + 0x168;
      } while (lVar6 != 0);
    }
    operator delete[](void*)(lVar4);
    *(long *)(param_1 + 0x10) = lVar3;
    *(long *)(param_1 + 0x18) = param_2;
  }
  *(long *)(param_1 + 0x10) = lVar3;
code_r0x018f6dc0:
  *(long *)(param_1 + 0x18) = param_2;
  return;
}


// FAILED to create function at 02866f20 typeinfo name for CGameResourceDownloader::CDownloadNode::CDownloadStream
// FAILED to create function at 02866f60 typeinfo name for CGameResourceDownloader::CJournalFileWriter
// FAILED to create function at 02866f90 typeinfo name for CGameResourceDownloader::CEraseCheckFiber
// FAILED to create function at 02866fc0 typeinfo name for CGameResourceDownloader::CVerifyTask
// FAILED to create function at 02867010 typeinfo name for CGameResourceDownloader::CDownloadNode
// FAILED to create function at 02867040 typeinfo name for CGameResourceDownloader::CDownloadNode::UnpackNotify
// FAILED to create function at 02867080 typeinfo name for Aska::TArray<CGameResourceDownloader::CJournalFileWriter::tWriteInfo, false>
// FAILED to create function at 02867420 typeinfo name for Aska::TArray<CGameResourceDownloader::CDownloadNode*, false>
// FAILED to create function at 02867460 typeinfo name for Aska::TArray<CGameResourceDownloader::tDownloadNodeInitializer, false>
// FAILED to create function at 028684b0 typeinfo name for std::__ndk1::__function::__base<void (char const*, CGameResourceDownloader::iErrorCode)>
// FAILED to create function at 02b0ff38 CGameResourceDownloader::vtable
// FAILED to create function at 02b0ff98 CGameResourceDownloader::CDownloadNode::vtable
// FAILED to create function at 02b0ffc0 CGameResourceDownloader::CDownloadNode::UnpackNotify::vtable
// FAILED to create function at 02b0ffe8 CGameResourceDownloader::CVerifyTask::vtable
// FAILED to create function at 02b10010 CGameResourceDownloader::CDownloadNode::CDownloadStream::vtable
// FAILED to create function at 02b100d0 CGameResourceDownloader::CDownloadNode::CDownloadStream::typeinfo
// FAILED to create function at 02b100e8 CGameResourceDownloader::CJournalFileWriter::vtable
// FAILED to create function at 02b10110 CGameResourceDownloader::CJournalFileWriter::typeinfo
// FAILED to create function at 02b10128 CGameResourceDownloader::CEraseCheckFiber::vtable
// FAILED to create function at 02b10190 CGameResourceDownloader::CEraseCheckFiber::typeinfo
// FAILED to create function at 02b101b0 CGameResourceDownloader::CVerifyTask::typeinfo
// FAILED to create function at 02b101f0 CGameResourceDownloader::typeinfo
// FAILED to create function at 02b10210 CGameResourceDownloader::CDownloadNode::typeinfo
// FAILED to create function at 02b10250 CGameResourceDownloader::CDownloadNode::UnpackNotify::typeinfo
// FAILED to create function at 02b10268 Aska::TArray<CGameResourceDownloader::CJournalFileWriter::tWriteInfo,false>::vtable
// FAILED to create function at 02b10288 Aska::TArray<CGameResourceDownloader::CJournalFileWriter::tWriteInfo,false>::typeinfo
// FAILED to create function at 02b10668 Aska::TArray<CGameResourceDownloader::CDownloadNode*,false>::vtable
// FAILED to create function at 02b10688 Aska::TArray<CGameResourceDownloader::CDownloadNode*,false>::typeinfo
// FAILED to create function at 02b10698 Aska::TArray<CGameResourceDownloader::tDownloadNodeInitializer,false>::vtable
// FAILED to create function at 02b106b8 Aska::TArray<CGameResourceDownloader::tDownloadNodeInitializer,false>::typeinfo
// FAILED to create function at 02b10fe0 std::__ndk1::__function::__base<void(char_const*,CGameResourceDownloader::iErrorCode)>::typeinfo
// FAILED to create function at 02cfab18 CGameResourceDownloader::CDownloadNode::m_GlobalDownloadCounter
// FAILED to create function at 02cfab1c CGameResourceDownloader::CDownloadNode::UnpackNotify::m_DispatchCount
// FAILED to create function at 02cfab20 CGameResourceDownloader::m_ErrorOverSize
