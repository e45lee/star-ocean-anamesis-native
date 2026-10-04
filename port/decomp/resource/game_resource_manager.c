// port/decomp/resource/game_resource_manager.c: Ghidra decompiles for the resource subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-04 06:16 UTC: tools/decomp.sh '--into' 'resource/game_resource_manager' 'CGameResourceManager::'

// ==== CGameResourceManager::CGameResourceManager(char const*)
// vaddr 0x17f6de4 | ghidra 0x18f6de4 | size 356 | symbol _ZN20CGameResourceManagerC2EPKc | lib libSOA-3.7.0.so | 2026-10-04
void _ZN20CGameResourceManagerC1EPKc(long *param_1)

{
  undefined *puVar1;
  ulong uVar2;
  undefined1 *puVar3;
  long lVar4;
  undefined1 *puVar5;
  ulong uVar6;
  ulong uVar7;
  
  puVar1 = PTR__ZN9Framework10TSingletonI20CGameResourceManagerE11m_pInstanceE_02cc2018;
  if (*(long *)PTR__ZN9Framework10TSingletonI20CGameResourceManagerE11m_pInstanceE_02cc2018 != 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x15,&UNK_027daee5/*"m_pInstance isn't null.(%08x)"*/);
  }
  *(long **)puVar1 = param_1;
  puVar1 = PTR__ZTVN4Aska8THashMapIjN9Framework13TStaticStringILm256EEENS_7THasherIjEENS_8TEqualToIjEENS_10TAllocatorINS_5TPairIKjS3_EEEEEE_02cba4e8
           + 0x10;
  *param_1 = (long)(PTR__ZTV20CGameResourceManager_02cc3d08 + 0x10);
  param_1[2] = 0;
  param_1[1] = 0;
  param_1[4] = 0;
  param_1[3] = 0;
  param_1[5] = (long)puVar1;
  *(undefined8 *)((long)param_1 + 0x34) = 0x3f400000;
  *(undefined4 *)((long)param_1 + 0x3c) = 0;
  puVar3 = (undefined1 *)Aska::MemoryManagerAdapter::AlignedMalloc(unsigned long, unsigned long)(0x1188,4);
  lVar4 = 0x11;
  if (puVar3 == (undefined1 *)0x0) {
    lVar4 = 0;
  }
  param_1[9] = (long)puVar3;
  param_1[10] = lVar4;
  if (puVar3 != (undefined1 *)0x0) {
    uVar2 = (lVar4 * 0x108 - 0x108U) / 0x108 + 1;
    puVar5 = puVar3;
    if ((1 < uVar2) && (uVar6 = uVar2 & 0x1fffffffffffffe, uVar6 != 0)) {
      uVar7 = uVar6;
      do {
        *puVar5 = 0;
        puVar5[0x108] = 0;
        uVar7 = uVar7 - 2;
        puVar5 = puVar5 + 0x210;
      } while (uVar7 != 0);
      puVar5 = puVar3 + uVar6 * 0x108;
      if (uVar2 == uVar6) goto code_r0x018f6f00;
    }
    do {
      *puVar5 = 0;
      puVar5 = puVar5 + 0x108;
    } while (puVar3 + lVar4 * 0x108 != puVar5);
  }
code_r0x018f6f00:
  param_1[0xc] = 0;
  param_1[0xd] = 0;
  param_1[0xb] = 0;
  puVar1 = PTR__ZN9Framework10TSingletonINS_12CApplication9CMainTaskEE11m_pInstanceE_02cc41c8;
  lVar4 = *(long *)
           PTR__ZN9Framework10TSingletonINS_12CApplication9CMainTaskEE11m_pInstanceE_02cc41c8;
  if (lVar4 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar4 = *(long *)puVar1;
  }
  lVar4 = Framework::CApplication::CMainTask::rResourceManager() const(lVar4);
  param_1[1] = lVar4;
  return;
}

// ==== CGameResourceManager::Substance(Framework::CResourceManager*)
// vaddr 0x17f6f48 | ghidra 0x18f6f48 | size 60 | symbol _ZN20CGameResourceManager9SubstanceEPN9Framework16CResourceManagerE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN20CGameResourceManager9SubstanceEPN9Framework16CResourceManagerE(long param_1,long param_2)

{
  if (param_2 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_028679cc/*"C:\BAS_Submission\Client\Project\..\Source\Game\Resource\GameResourceManager.cpp"*/,0x31a,&UNK_028681ff/*"need framework resourcemanager."*/);
  }
  *(long *)(param_1 + 8) = param_2;
  return;
}

// ==== CGameResourceManager::~CGameResourceManager()
// vaddr 0x17f6f84 | ghidra 0x18f6f84 | size 144 | symbol _ZN20CGameResourceManagerD2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN20CGameResourceManagerD1Ev(long *param_1)

{
  undefined *puVar1;
  
  *param_1 = (long)(PTR__ZTV20CGameResourceManager_02cc3d08 + 0x10);
  CGameResourceManager::Release()();
  if ((*(byte *)(param_1 + 0xb) & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(param_1[0xd]);
  }
  param_1[5] = (long)(
                     PTR__ZTVN4Aska8THashMapIjN9Framework13TStaticStringILm256EEENS_7THasherIjEENS_8TEqualToIjEENS_10TAllocatorINS_5TPairIKjS3_EEEEEE_02cba4e8
                     + 0x10);
  if (param_1[9] != 0) {
    Aska::MemoryManagerAdapter::AlignedFree(void*)();
    param_1[9] = 0;
    param_1[10] = 0;
  }
  param_1[7] = 0;
  puVar1 = PTR__ZN9Framework10TSingletonI20CGameResourceManagerE11m_pInstanceE_02cc2018;
  if (*(long *)PTR__ZN9Framework10TSingletonI20CGameResourceManagerE11m_pInstanceE_02cc2018 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x1d,&UNK_027daf21/*"m_pInstance is null."*/);
  }
  *(undefined8 *)puVar1 = 0;
  return;
}

// ==== CGameResourceManager::Release()
// vaddr 0x17f7014 | ghidra 0x18f7014 | size 188 | symbol _ZN20CGameResourceManager7ReleaseEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN20CGameResourceManager7ReleaseEv(long param_1)

{
  long lVar1;
  
  if (*(long *)(param_1 + 8) != 0) {
    lVar1 = *(long *)(param_1 + 0x20);
    if (lVar1 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_028679cc/*"C:\BAS_Submission\Client\Project\..\Source\Game\Resource\GameResourceManager.cpp"*/,0xac,&UNK_02866cea/*"m_pDownLoader is null."*/);
      lVar1 = *(long *)(param_1 + 0x20);
    }
    Framework::CFiberUnit::Destroy(bool)(lVar1,0);
    if (*(long **)(param_1 + 0x20) != (long *)0x0) {
      (**(code **)(**(long **)(param_1 + 0x20) + 8))();
      *(undefined8 *)(param_1 + 0x20) = 0;
    }
    lVar1 = *(long *)(param_1 + 0x10);
    if (lVar1 != 0) {
      Framework::CCSV::~CCSV()(lVar1);
      operator delete(void*)(lVar1);
      *(undefined8 *)(param_1 + 0x10) = 0;
    }
    if (*(long *)(param_1 + 0x18) != 0) {
      operator delete[](void*)();
      *(undefined8 *)(param_1 + 0x18) = 0;
    }
    lVar1 = *(long *)(param_1 + 8);
    if (lVar1 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_028679cc/*"C:\BAS_Submission\Client\Project\..\Source\Game\Resource\GameResourceManager.cpp"*/,0x324,&UNK_027e7586/*"m_pSubstance is null."*/);
      lVar1 = *(long *)(param_1 + 8);
    }
    Framework::CResourceManager::Release()(lVar1);
    *(undefined8 *)(param_1 + 8) = 0;
  }
  return;
}

// ==== CGameResourceManager::~CGameResourceManager()
// vaddr 0x17f7110 | ghidra 0x18f7110 | size 148 | symbol _ZN20CGameResourceManagerD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN20CGameResourceManagerD0Ev(long *param_1)

{
  undefined *puVar1;
  
  *param_1 = (long)(PTR__ZTV20CGameResourceManager_02cc3d08 + 0x10);
  CGameResourceManager::Release()();
  if ((*(byte *)(param_1 + 0xb) & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(param_1[0xd]);
  }
  param_1[5] = (long)(
                     PTR__ZTVN4Aska8THashMapIjN9Framework13TStaticStringILm256EEENS_7THasherIjEENS_8TEqualToIjEENS_10TAllocatorINS_5TPairIKjS3_EEEEEE_02cba4e8
                     + 0x10);
  if (param_1[9] != 0) {
    Aska::MemoryManagerAdapter::AlignedFree(void*)();
    param_1[9] = 0;
    param_1[10] = 0;
  }
  param_1[7] = 0;
  puVar1 = PTR__ZN9Framework10TSingletonI20CGameResourceManagerE11m_pInstanceE_02cc2018;
  if (*(long *)PTR__ZN9Framework10TSingletonI20CGameResourceManagerE11m_pInstanceE_02cc2018 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x1d,&UNK_027daf21/*"m_pInstance is null."*/);
  }
  *(undefined8 *)puVar1 = 0;
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== CGameResourceManager::Initialize()
// vaddr 0x17f71a4 | ghidra 0x18f71a4 | size 3256 | symbol _ZN20CGameResourceManager10InitializeEv | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Type propagation algorithm not settling */

void _ZN20CGameResourceManager10InitializeEv(long param_1)

{
  undefined1 *puVar1;
  char cVar2;
  undefined8 uVar3;
  undefined *puVar4;
  undefined7 uVar5;
  undefined7 uVar6;
  byte bVar7;
  long lVar8;
  long *plVar9;
  undefined8 uVar10;
  ulong uVar11;
  ulong uVar12;
  code *pcVar13;
  ulong uVar14;
  float fVar15;
  ulong uStack_c8;
  undefined8 uStack_c0;
  undefined8 uStack_b8;
  ulong uStack_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined7 uStack_98;
  char cStack_91;
  undefined7 uStack_90;
  undefined1 uStack_89;
  ulong uStack_88;
  byte bStack_80;
  undefined1 uStack_7f;
  undefined6 uStack_7e;
  char cStack_78;
  undefined7 uStack_77;
  undefined1 *puStack_70;
  undefined *apuStack_60 [4];
  undefined **ppuStack_40;
  
  if (*(long *)(param_1 + 0x20) != 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_028679cc/*"C:\BAS_Submission\Client\Project\..\Source\Game\Resource\GameResourceManager.cpp"*/,0x39,&UNK_02867a1d/*"m_pDownLoader isn't null.(%08x)"*/);
  }
  lVar8 = operator new(unsigned long, std::nothrow_t const&)(0x5f0,PTR__ZSt7nothrow_02cb9a80);
  if (lVar8 != 0) {
    CGameResourceDownloader::CGameResourceDownloader()(lVar8);
  }
  *(long *)(param_1 + 0x20) = lVar8;
  CGameResourceDownloader::Initialize()(lVar8);
  apuStack_60[0] = &UNK_02b10f08;
  ppuStack_40 = apuStack_60;
  CGameResourceDownloader::SetErrorCallback(std::__ndk1::function<void (unsigned int, Aska::Status)>)(*(undefined8 *)(param_1 + 0x20),apuStack_60);
  if (apuStack_60 == ppuStack_40) {
    pcVar13 = *(code **)(*ppuStack_40 + 0x20);
  }
  else {
    if (ppuStack_40 == (undefined **)0x0) goto code_r0x018f7250;
    pcVar13 = *(code **)(*ppuStack_40 + 0x28);
  }
  (*pcVar13)();
code_r0x018f7250:
  puVar4 = PTR__ZN9Framework10TSingletonINS_12CApplication9CMainTaskEE11m_pInstanceE_02cc41c8;
  lVar8 = *(long *)
           PTR__ZN9Framework10TSingletonINS_12CApplication9CMainTaskEE11m_pInstanceE_02cc41c8;
  if (lVar8 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar8 = *(long *)puVar4;
  }
  plVar9 = (long *)Framework::CApplication::CMainTask::rRootFiberKernel()(lVar8);
  (**(code **)(*plVar9 + 0x48))(plVar9,*(undefined8 *)(param_1 + 0x20));
  cStack_78 = '\0';
  uStack_77 = 0;
  puStack_70 = (undefined1 *)0x0;
  bStack_80 = 0;
  uStack_7f = 0;
  uStack_7e = 0;
  lVar8 = 0x16;
  string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&bStack_80,0x16,0x65,0,0,0,0x7b,&UNK_02867a3d);
  uVar14 = (ulong)bStack_80;
  if ((bStack_80 & 1) != 0) {
    uVar14 = CONCAT62(uStack_7e,CONCAT11(uStack_7f,bStack_80));
    lVar8 = (uVar14 & 0xfffffffffffffffe) - 1;
  }
  uVar12 = (ulong)(((uint)uVar14 & 0xfe) >> 1);
  if ((uVar14 & 1) != 0) {
    uVar12 = CONCAT71(uStack_77,cStack_78);
  }
  if (lVar8 - uVar12 < 0xa3) {
    string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&bStack_80,lVar8,(0xa3 - lVar8) + uVar12,uVar12,uVar12,0,0xa3,&UNK_02867ab9);
  }
  else {
    puVar1 = (undefined1 *)((ulong)&bStack_80 | 1);
    if ((uVar14 & 1) != 0) {
      puVar1 = puStack_70;
    }
    memcpy(puVar1 + uVar12,&UNK_02867ab9,0xa3);
    lVar8 = uVar12 + 0xa3;
    if ((uVar14 & 1) == 0) {
      bStack_80 = (char)lVar8 * '\x02';
    }
    else {
      uStack_77 = (undefined7)((ulong)lVar8 >> 8);
      cStack_78 = (char)lVar8;
    }
    puVar1[lVar8] = 0;
  }
  if ((bStack_80 & 1) == 0) {
    uVar14 = (ulong)bStack_80;
    lVar8 = 0x16;
  }
  else {
    uVar14 = CONCAT62(uStack_7e,CONCAT11(uStack_7f,bStack_80));
    lVar8 = (uVar14 & 0xfffffffffffffffe) - 1;
  }
  uVar12 = (ulong)(((uint)uVar14 & 0xfe) >> 1);
  if ((uVar14 & 1) != 0) {
    uVar12 = CONCAT71(uStack_77,cStack_78);
  }
  if (lVar8 - uVar12 < 0x9b) {
    string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&bStack_80,lVar8,(0x9b - lVar8) + uVar12,uVar12,uVar12,0,0x9b,&UNK_02867b5d);
  }
  else {
    puVar1 = (undefined1 *)((ulong)&bStack_80 | 1);
    if ((uVar14 & 1) != 0) {
      puVar1 = puStack_70;
    }
    memcpy(puVar1 + uVar12,&UNK_02867b5d,0x9b);
    lVar8 = uVar12 + 0x9b;
    if ((uVar14 & 1) == 0) {
      bStack_80 = (char)lVar8 * '\x02';
    }
    else {
      uStack_77 = (undefined7)((ulong)lVar8 >> 8);
      cStack_78 = (char)lVar8;
    }
    puVar1[lVar8] = 0;
  }
  if ((bStack_80 & 1) == 0) {
    uVar14 = (ulong)bStack_80;
    lVar8 = 0x16;
  }
  else {
    uVar14 = CONCAT62(uStack_7e,CONCAT11(uStack_7f,bStack_80));
    lVar8 = (uVar14 & 0xfffffffffffffffe) - 1;
  }
  uVar12 = (ulong)(((uint)uVar14 & 0xfe) >> 1);
  if ((uVar14 & 1) != 0) {
    uVar12 = CONCAT71(uStack_77,cStack_78);
  }
  if (lVar8 - uVar12 < 0xb3) {
    string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&bStack_80,lVar8,(0xb3 - lVar8) + uVar12,uVar12,uVar12,0,0xb3,&UNK_02867bf9);
  }
  else {
    puVar1 = (undefined1 *)((ulong)&bStack_80 | 1);
    if ((uVar14 & 1) != 0) {
      puVar1 = puStack_70;
    }
    memcpy(puVar1 + uVar12,&UNK_02867bf9,0xb3);
    lVar8 = uVar12 + 0xb3;
    if ((uVar14 & 1) == 0) {
      bStack_80 = (char)lVar8 * '\x02';
    }
    else {
      uStack_77 = (undefined7)((ulong)lVar8 >> 8);
      cStack_78 = (char)lVar8;
    }
    puVar1[lVar8] = 0;
  }
  if ((bStack_80 & 1) == 0) {
    uVar14 = (ulong)bStack_80;
    lVar8 = 0x16;
  }
  else {
    uVar14 = CONCAT62(uStack_7e,CONCAT11(uStack_7f,bStack_80));
    lVar8 = (uVar14 & 0xfffffffffffffffe) - 1;
  }
  uVar12 = (ulong)(((uint)uVar14 & 0xfe) >> 1);
  if ((uVar14 & 1) != 0) {
    uVar12 = CONCAT71(uStack_77,cStack_78);
  }
  if (lVar8 - uVar12 < 0x9b) {
    string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&bStack_80,lVar8,(0x9b - lVar8) + uVar12,uVar12,uVar12,0,0x9b,&UNK_02867cad);
  }
  else {
    puVar1 = (undefined1 *)((ulong)&bStack_80 | 1);
    if ((uVar14 & 1) != 0) {
      puVar1 = puStack_70;
    }
    memcpy(puVar1 + uVar12,&UNK_02867cad,0x9b);
    lVar8 = uVar12 + 0x9b;
    if ((uVar14 & 1) == 0) {
      bStack_80 = (char)lVar8 * '\x02';
    }
    else {
      uStack_77 = (undefined7)((ulong)lVar8 >> 8);
      cStack_78 = (char)lVar8;
    }
    puVar1[lVar8] = 0;
  }
  if ((bStack_80 & 1) == 0) {
    uVar14 = (ulong)bStack_80;
    lVar8 = 0x16;
  }
  else {
    uVar14 = CONCAT62(uStack_7e,CONCAT11(uStack_7f,bStack_80));
    lVar8 = (uVar14 & 0xfffffffffffffffe) - 1;
  }
  uVar12 = (ulong)(((uint)uVar14 & 0xfe) >> 1);
  if ((uVar14 & 1) != 0) {
    uVar12 = CONCAT71(uStack_77,cStack_78);
  }
  if (lVar8 - uVar12 < 0x86) {
    string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&bStack_80,lVar8,(0x86 - lVar8) + uVar12,uVar12,uVar12,0,0x86,&UNK_02867d49);
  }
  else {
    puVar1 = (undefined1 *)((ulong)&bStack_80 | 1);
    if ((uVar14 & 1) != 0) {
      puVar1 = puStack_70;
    }
    memcpy(puVar1 + uVar12,&UNK_02867d49,0x86);
    lVar8 = uVar12 + 0x86;
    if ((uVar14 & 1) == 0) {
      bStack_80 = (char)lVar8 * '\x02';
    }
    else {
      uStack_77 = (undefined7)((ulong)lVar8 >> 8);
      cStack_78 = (char)lVar8;
    }
    puVar1[lVar8] = 0;
  }
  if ((bStack_80 & 1) == 0) {
    uVar14 = (ulong)bStack_80;
    lVar8 = 0x16;
  }
  else {
    uVar14 = CONCAT62(uStack_7e,CONCAT11(uStack_7f,bStack_80));
    lVar8 = (uVar14 & 0xfffffffffffffffe) - 1;
  }
  uVar12 = (ulong)(((uint)uVar14 & 0xfe) >> 1);
  if ((uVar14 & 1) != 0) {
    uVar12 = CONCAT71(uStack_77,cStack_78);
  }
  if (lVar8 - uVar12 < 0x9b) {
    string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&bStack_80,lVar8,(0x9b - lVar8) + uVar12,uVar12,uVar12,0,0x9b,&UNK_02867dd0);
  }
  else {
    puVar1 = (undefined1 *)((ulong)&bStack_80 | 1);
    if ((uVar14 & 1) != 0) {
      puVar1 = puStack_70;
    }
    memcpy(puVar1 + uVar12,&UNK_02867dd0,0x9b);
    lVar8 = uVar12 + 0x9b;
    if ((uVar14 & 1) == 0) {
      bStack_80 = (char)lVar8 * '\x02';
    }
    else {
      uStack_77 = (undefined7)((ulong)lVar8 >> 8);
      cStack_78 = (char)lVar8;
    }
    puVar1[lVar8] = 0;
  }
  if ((bStack_80 & 1) == 0) {
    uVar14 = (ulong)bStack_80;
    lVar8 = 0x16;
  }
  else {
    uVar14 = CONCAT62(uStack_7e,CONCAT11(uStack_7f,bStack_80));
    lVar8 = (uVar14 & 0xfffffffffffffffe) - 1;
  }
  uVar12 = (ulong)(((uint)uVar14 & 0xfe) >> 1);
  if ((uVar14 & 1) != 0) {
    uVar12 = CONCAT71(uStack_77,cStack_78);
  }
  if (lVar8 - uVar12 < 0x9b) {
    string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&bStack_80,lVar8,(0x9b - lVar8) + uVar12,uVar12,uVar12,0,0x9b,&UNK_02867e6c);
  }
  else {
    puVar1 = (undefined1 *)((ulong)&bStack_80 | 1);
    if ((uVar14 & 1) != 0) {
      puVar1 = puStack_70;
    }
    memcpy(puVar1 + uVar12,&UNK_02867e6c,0x9b);
    lVar8 = uVar12 + 0x9b;
    if ((uVar14 & 1) == 0) {
      bStack_80 = (char)lVar8 * '\x02';
    }
    else {
      uStack_77 = (undefined7)((ulong)lVar8 >> 8);
      cStack_78 = (char)lVar8;
    }
    puVar1[lVar8] = 0;
  }
  if ((bStack_80 & 1) == 0) {
    uVar14 = (ulong)bStack_80;
    lVar8 = 0x16;
  }
  else {
    uVar14 = CONCAT62(uStack_7e,CONCAT11(uStack_7f,bStack_80));
    lVar8 = (uVar14 & 0xfffffffffffffffe) - 1;
  }
  uVar12 = (ulong)(((uint)uVar14 & 0xfe) >> 1);
  if ((uVar14 & 1) != 0) {
    uVar12 = CONCAT71(uStack_77,cStack_78);
  }
  if (lVar8 - uVar12 < 0x76) {
    string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&bStack_80,lVar8,(0x76 - lVar8) + uVar12,uVar12,uVar12,0,0x76,&UNK_02867f08);
  }
  else {
    puVar1 = (undefined1 *)((ulong)&bStack_80 | 1);
    if ((uVar14 & 1) != 0) {
      puVar1 = puStack_70;
    }
    memcpy(puVar1 + uVar12,&UNK_02867f08,0x76);
    lVar8 = uVar12 + 0x76;
    if ((uVar14 & 1) == 0) {
      bStack_80 = (char)lVar8 * '\x02';
    }
    else {
      uStack_77 = (undefined7)((ulong)lVar8 >> 8);
      cStack_78 = (char)lVar8;
    }
    puVar1[lVar8] = 0;
  }
  if ((bStack_80 & 1) == 0) {
    uVar14 = (ulong)bStack_80;
    lVar8 = 0x16;
  }
  else {
    uVar14 = CONCAT62(uStack_7e,CONCAT11(uStack_7f,bStack_80));
    lVar8 = (uVar14 & 0xfffffffffffffffe) - 1;
  }
  uVar12 = (ulong)(((uint)uVar14 & 0xfe) >> 1);
  if ((uVar14 & 1) != 0) {
    uVar12 = CONCAT71(uStack_77,cStack_78);
  }
  if (lVar8 - uVar12 < 0x7e) {
    string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&bStack_80,lVar8,(0x7e - lVar8) + uVar12,uVar12,uVar12,0,0x7e,&UNK_02867f7f);
  }
  else {
    puVar1 = (undefined1 *)((ulong)&bStack_80 | 1);
    if ((uVar14 & 1) != 0) {
      puVar1 = puStack_70;
    }
    memcpy(puVar1 + uVar12,&UNK_02867f7f,0x7e);
    lVar8 = uVar12 + 0x7e;
    if ((uVar14 & 1) == 0) {
      bStack_80 = (char)lVar8 * '\x02';
    }
    else {
      uStack_77 = (undefined7)((ulong)lVar8 >> 8);
      cStack_78 = (char)lVar8;
    }
    puVar1[lVar8] = 0;
  }
  if ((bStack_80 & 1) == 0) {
    uVar14 = (ulong)bStack_80;
    lVar8 = 0x16;
  }
  else {
    uVar14 = CONCAT62(uStack_7e,CONCAT11(uStack_7f,bStack_80));
    lVar8 = (uVar14 & 0xfffffffffffffffe) - 1;
  }
  uVar12 = (ulong)(((uint)uVar14 & 0xfe) >> 1);
  if ((uVar14 & 1) != 0) {
    uVar12 = CONCAT71(uStack_77,cStack_78);
  }
  if (lVar8 - uVar12 < 0x9e) {
    string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&bStack_80,lVar8,(0x9e - lVar8) + uVar12,uVar12,uVar12,0,0x9e,&UNK_02867ffe);
  }
  else {
    puVar1 = (undefined1 *)((ulong)&bStack_80 | 1);
    if ((uVar14 & 1) != 0) {
      puVar1 = puStack_70;
    }
    memcpy(puVar1 + uVar12,&UNK_02867ffe,0x9e);
    lVar8 = uVar12 + 0x9e;
    if ((uVar14 & 1) == 0) {
      bStack_80 = (char)lVar8 * '\x02';
    }
    else {
      uStack_77 = (undefined7)((ulong)lVar8 >> 8);
      cStack_78 = (char)lVar8;
    }
    puVar1[lVar8] = 0;
  }
  if ((bStack_80 & 1) == 0) {
    uVar14 = (ulong)bStack_80;
    lVar8 = 0x16;
  }
  else {
    uVar14 = CONCAT62(uStack_7e,CONCAT11(uStack_7f,bStack_80));
    lVar8 = (uVar14 & 0xfffffffffffffffe) - 1;
  }
  uVar12 = (ulong)(((uint)uVar14 & 0xfe) >> 1);
  if ((uVar14 & 1) != 0) {
    uVar12 = CONCAT71(uStack_77,cStack_78);
  }
  if (lVar8 - uVar12 < 0x66) {
    string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&bStack_80,lVar8,(0x66 - lVar8) + uVar12,uVar12,uVar12,0,0x66,&UNK_0286809d);
  }
  else {
    puVar1 = (undefined1 *)((ulong)&bStack_80 | 1);
    if ((uVar14 & 1) != 0) {
      puVar1 = puStack_70;
    }
    memcpy(puVar1 + uVar12,&UNK_0286809d,0x66);
    lVar8 = uVar12 + 0x66;
    if ((uVar14 & 1) == 0) {
      bStack_80 = (char)lVar8 * '\x02';
    }
    else {
      uStack_77 = (undefined7)((ulong)lVar8 >> 8);
      cStack_78 = (char)lVar8;
    }
    puVar1[lVar8] = 0;
  }
  if ((bStack_80 & 1) == 0) {
    uVar14 = (ulong)bStack_80;
    lVar8 = 0x16;
  }
  else {
    uVar14 = CONCAT62(uStack_7e,CONCAT11(uStack_7f,bStack_80));
    lVar8 = (uVar14 & 0xfffffffffffffffe) - 1;
  }
  uVar12 = (ulong)(((uint)uVar14 & 0xfe) >> 1);
  if ((uVar14 & 1) != 0) {
    uVar12 = CONCAT71(uStack_77,cStack_78);
  }
  if (lVar8 - uVar12 < 0x8b) {
    string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&bStack_80,lVar8,(0x8b - lVar8) + uVar12,uVar12,uVar12,0,0x8b,&UNK_02868104);
  }
  else {
    puVar1 = (undefined1 *)((ulong)&bStack_80 | 1);
    if ((uVar14 & 1) != 0) {
      puVar1 = puStack_70;
    }
    memcpy(puVar1 + uVar12,&UNK_02868104,0x8b);
    lVar8 = uVar12 + 0x8b;
    if ((uVar14 & 1) == 0) {
      bStack_80 = (char)lVar8 * '\x02';
    }
    else {
      uStack_77 = (undefined7)((ulong)lVar8 >> 8);
      cStack_78 = (char)lVar8;
    }
    puVar1[lVar8] = 0;
  }
  uStack_b8 = 0;
  uStack_a8 = 0;
  uStack_a0 = 0;
  uStack_c8 = 0;
  uStack_c0 = 0;
  uStack_b0 = 0x2002;
  Framework::CSTLStringUtility_Base<string >::Replace(string const&, string const&, string const&, bool*)(&uStack_98,&bStack_80,&uStack_b0,&uStack_c8,0);
  if ((bStack_80 & 1) == 0) {
    bStack_80 = 0;
    uStack_7f = 0;
  }
  else {
    *puStack_70 = 0;
    cStack_78 = '\0';
    uStack_77 = 0;
  }
  string::reserve(unsigned long)(&bStack_80,0);
  puStack_70 = (undefined1 *)uStack_88;
  uVar6 = uStack_90;
  uVar5 = uStack_98;
  uVar3 = CONCAT17(uStack_89,uStack_90);
  uVar10 = CONCAT17(cStack_91,uStack_98);
  uStack_90 = 0;
  uStack_89 = 0;
  uStack_88 = 0;
  uStack_98 = 0;
  cStack_91 = 0;
  cStack_78 = (char)uVar6;
  uStack_77 = (undefined7)((ulong)uVar3 >> 8);
  bStack_80 = (byte)uVar5;
  uStack_7f = (undefined1)((uint7)uVar5 >> 8);
  uStack_7e = (undefined6)((ulong)uVar10 >> 0x10);
  if ((uStack_c8 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_b8);
  }
  if ((uStack_b0 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_a0);
  }
  bVar7 = bStack_80;
  uVar14 = (ulong)(bStack_80 >> 1);
  if ((bStack_80 & 1) != 0) {
    uVar14 = CONCAT71(uStack_77,cStack_78);
  }
  uVar12 = uVar14 + 1;
  uVar10 = operator new[](unsigned long, std::nothrow_t const&)(uVar12,PTR__ZSt7nothrow_02cb9a80);
  *(undefined8 *)(param_1 + 0x18) = uVar10;
  puVar1 = (undefined1 *)((ulong)&bStack_80 | 1);
  if ((bVar7 & 1) != 0) {
    puVar1 = puStack_70;
  }
  uVar11 = strlen(puVar1);
  if (uVar12 <= uVar11) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dc32f/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/Utility.h"*/,0x77,&UNK_027dc380/*"gStrcpy() : destination buffer is small. ( %d < %d )"*/,uVar11,uVar12);
  }
  strcpy(uVar10,puVar1);
  *(undefined1 *)(*(long *)(param_1 + 0x18) + uVar14) = 0;
  if ((bStack_80 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puStack_70);
  }
  if (*(long *)(param_1 + 0x10) != 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_028679cc/*"C:\BAS_Submission\Client\Project\..\Source\Game\Resource\GameResourceManager.cpp"*/,0x8b,&UNK_02868190/*"m_pCSV isn't null.(%08x)"*/);
  }
  lVar8 = operator new(unsigned long, std::nothrow_t const&)(0x40,PTR__ZSt7nothrow_02cb9a80);
  if (lVar8 != 0) {
    Framework::CCSV::CCSV()(lVar8);
  }
  *(long *)(param_1 + 0x10) = lVar8;
  Framework::CCSV::Initialize()(lVar8);
  Framework::CCSV::Parse(char const*, bool)(*(undefined8 *)(param_1 + 0x10),*(undefined8 *)(param_1 + 0x18),0);
  fVar15 = (float)NEON_ucvtf(*(undefined4 *)(param_1 + 0x38));
  uVar14 = (ulong)(fVar15 / *(float *)(param_1 + 0x34));
  if (uVar14 < 0x101) {
    uVar14 = 0x100;
  }
  Aska::THashMap<unsigned int, Framework::TStaticString<256ul>, Aska::THasher<unsigned int>, Aska::TEqualTo<unsigned int>, Aska::TAllocator<Aska::TPair<unsigned int const, Framework::TStaticString<256ul> > > >::Rehash_(unsigned long)(param_1 + 0x28,uVar14);
  BAS::GetDownloadPath()(&bStack_80);
  uVar14 = (ulong)bStack_80;
  if ((bStack_80 & 1) == 0) {
    uVar12 = 0x16;
  }
  else {
    uVar14 = CONCAT62(uStack_7e,CONCAT11(uStack_7f,bStack_80));
    uVar12 = (uVar14 & 0xfffffffffffffffe) - 1;
  }
  uVar11 = (ulong)(((uint)uVar14 & 0xfe) >> 1);
  if ((uVar14 & 1) != 0) {
    uVar11 = CONCAT71(uStack_77,cStack_78);
  }
  if (uVar12 == uVar11) {
    string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&bStack_80,uVar12,1,uVar12,uVar12,0,1,&UNK_029c5d3e/*"/"*/);
  }
  else {
    puVar1 = (undefined1 *)((ulong)&bStack_80 | 1);
    if ((uVar14 & 1) != 0) {
      puVar1 = puStack_70;
    }
    *(undefined1 *)((long)puVar1 + uVar11) = 0x2f;
    lVar8 = uVar11 + 1;
    if ((bStack_80 & 1) == 0) {
      bStack_80 = (char)lVar8 * '\x02';
    }
    else {
      uStack_77 = (undefined7)((ulong)lVar8 >> 8);
      cStack_78 = (char)lVar8;
    }
    *(undefined1 *)((long)puVar1 + lVar8) = 0;
  }
  puVar1 = puStack_70;
  uStack_90 = uStack_77;
  cStack_91 = cStack_78;
  bVar7 = bStack_80;
  uStack_98 = CONCAT61(uStack_7e,uStack_7f);
  cStack_78 = 0;
  uStack_77 = 0;
  puStack_70 = (undefined1 *)0x0;
  bStack_80 = 0;
  uStack_7f = 0;
  uStack_7e = 0;
  if ((*(byte *)(param_1 + 0x58) & 1) == 0) {
    *(undefined2 *)(param_1 + 0x58) = 0;
  }
  else {
    **(undefined1 **)(param_1 + 0x68) = 0;
    *(undefined8 *)(param_1 + 0x60) = 0;
  }
  string::reserve(unsigned long)((byte *)(param_1 + 0x58),0);
  *(byte *)(param_1 + 0x58) = bVar7;
  *(ulong *)(param_1 + 0x59) = CONCAT17(cStack_91,uStack_98);
  *(ulong *)(param_1 + 0x60) = CONCAT71(uStack_90,cStack_91);
  *(undefined1 **)(param_1 + 0x68) = puVar1;
  uStack_98 = 0;
  cStack_91 = 0;
  uStack_90 = 0;
  if ((bStack_80 & 1) == 0) {
    lVar8 = *(long *)(param_1 + 8);
  }
  else {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puStack_70);
    lVar8 = *(long *)(param_1 + 8);
  }
  if (lVar8 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_028679cc/*"C:\BAS_Submission\Client\Project\..\Source\Game\Resource\GameResourceManager.cpp"*/,0x324,&UNK_027e7586/*"m_pSubstance is null."*/);
    cVar2 = *(char *)(*(long *)(param_1 + 8) + 0x27);
  }
  else {
    cVar2 = *(char *)(lVar8 + 0x27);
  }
  if (cVar2 == '\0') {
    Framework::CResourceManager::Initialize()();
  }
  return;
}

// ==== CGameResourceManager::pSubstance()
// vaddr 0x17f7e5c | ghidra 0x18f7e5c | size 60 | symbol _ZN20CGameResourceManager10pSubstanceEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZN20CGameResourceManager10pSubstanceEv(long param_1)

{
  if (*(long *)(param_1 + 8) != 0) {
    return *(long *)(param_1 + 8);
  }
  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_028679cc/*"C:\BAS_Submission\Client\Project\..\Source\Game\Resource\GameResourceManager.cpp"*/,0x324,&UNK_027e7586/*"m_pSubstance is null."*/);
  return *(long *)(param_1 + 8);
}

// ==== CGameResourceManager::IsInitialize() const
// vaddr 0x17f7e98 | ghidra 0x18f7e98 | size 56 | symbol _ZNK20CGameResourceManager12IsInitializeEv | lib libSOA-3.7.0.so | 2026-10-04
undefined1 _ZNK20CGameResourceManager12IsInitializeEv(long param_1)

{
  long lVar1;
  
  lVar1 = *(long *)(param_1 + 8);
  if (lVar1 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_028679cc/*"C:\BAS_Submission\Client\Project\..\Source\Game\Resource\GameResourceManager.cpp"*/,0x329,&UNK_027e7586/*"m_pSubstance is null."*/);
    lVar1 = *(long *)(param_1 + 8);
  }
  return *(undefined1 *)(lVar1 + 0x27);
}

// ==== CGameResourceManager::cpSubstance() const
// vaddr 0x17f7ed0 | ghidra 0x18f7ed0 | size 60 | symbol _ZNK20CGameResourceManager11cpSubstanceEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK20CGameResourceManager11cpSubstanceEv(long param_1)

{
  if (*(long *)(param_1 + 8) != 0) {
    return *(long *)(param_1 + 8);
  }
  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_028679cc/*"C:\BAS_Submission\Client\Project\..\Source\Game\Resource\GameResourceManager.cpp"*/,0x329,&UNK_027e7586/*"m_pSubstance is null."*/);
  return *(long *)(param_1 + 8);
}

// ==== CGameResourceManager::AddDirectFile(unsigned int, char const*, unsigned int, bool, CGameResourceManager::iPriorityMode)
// vaddr 0x17f7f0c | ghidra 0x18f7f0c | size 504 | symbol _ZN20CGameResourceManager13AddDirectFileEjPKcjbNS_13iPriorityModeE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN20CGameResourceManager13AddDirectFileEjPKcjbNS_13iPriorityModeE
               (long param_1,undefined4 param_2,undefined8 param_3,undefined4 param_4,byte param_5,
               undefined4 param_6)

{
  undefined *puVar1;
  int iVar2;
  undefined8 uVar3;
  ulong uVar4;
  code *pcVar5;
  long lVar6;
  long lVar7;
  long alStack_180 [4];
  long *plStack_160;
  undefined1 auStack_150 [256];
  undefined4 uStack_48;
  undefined2 uStack_44;
  undefined1 uStack_42;
  
  lVar6 = *(long *)(param_1 + 8);
  if (lVar6 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_028679cc/*"C:\BAS_Submission\Client\Project\..\Source\Game\Resource\GameResourceManager.cpp"*/,0x324,&UNK_027e7586/*"m_pSubstance is null."*/);
    lVar6 = *(long *)(param_1 + 8);
  }
  uVar3 = CGameResourceManager::ReplaceFileName(char const*) const(param_1,param_3);
  auStack_150[0] = 0;
  iVar2 = CGameResourceManager::FileExistLanguage(char const*, CGameResourceManager::iPriorityMode, Framework::TStaticString<256ul>*) const(param_1,uVar3,param_6,auStack_150);
  if (iVar2 - 3U < 3) {
    uVar4 = CGameResourceManager::IsFileExistDownloadFolder(char const*) const(param_1,auStack_150);
    if ((uVar4 & 1) == 0) {
      Framework::CResourceManager::AddDirectFile(unsigned int, char const*, unsigned int, bool)(lVar6,param_2,auStack_150,param_4,param_5 & 1);
    }
    else {
      if ((*(byte *)(param_1 + 0x58) & 1) == 0) {
        param_1 = param_1 + 0x59;
      }
      else {
        param_1 = *(long *)(param_1 + 0x68);
      }
      Framework::CResourceManager::AddDirectFileWithFolder(unsigned int, char const*, char const*, unsigned int, bool)(lVar6,param_2,param_1,auStack_150,param_4,param_5 & 1);
    }
  }
  else if (iVar2 - 1U < 2) {
    lVar7 = *(long *)(param_1 + 0x20);
    if (lVar7 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_028679cc/*"C:\BAS_Submission\Client\Project\..\Source\Game\Resource\GameResourceManager.cpp"*/,0xe4,&UNK_02866cea/*"m_pDownLoader is null."*/);
      lVar7 = *(long *)(param_1 + 0x20);
    }
    plStack_160 = (long *)operator new(unsigned long)(0x28);
    *(undefined4 *)(plStack_160 + 2) = param_2;
    *(undefined4 *)((long)plStack_160 + 0x14) = param_4;
    *(byte *)(plStack_160 + 3) = param_5 & 1;
    plStack_160[4] = param_1;
    *plStack_160 = (long)&UNK_02b10f98;
    plStack_160[1] = lVar6;
    *(undefined1 *)((long)plStack_160 + 0x1f) = uStack_42;
    *(undefined2 *)((long)plStack_160 + 0x1d) = uStack_44;
    *(undefined4 *)((long)plStack_160 + 0x19) = uStack_48;
    CGameResourceDownloader::RequestDownload(char const*, std::__ndk1::function<void (char const*, CGameResourceDownloader::iErrorCode)>)(lVar7,auStack_150,alStack_180);
    if (alStack_180 == plStack_160) {
      pcVar5 = *(code **)(*plStack_160 + 0x20);
    }
    else {
      if (plStack_160 == (long *)0x0) {
        return;
      }
      pcVar5 = *(code **)(*plStack_160 + 0x28);
    }
    (*pcVar5)();
  }
  else {
    puVar1 = &UNK_02805df9/*"yes"*/;
    if (*(char *)(*(long *)(param_1 + 0x20) + 0x5a8) == '\0') {
      puVar1 = &UNK_027f7e3a/*"no"*/;
    }
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_028679cc/*"C:\BAS_Submission\Client\Project\..\Source\Game\Resource\GameResourceManager.cpp"*/,0xed,&UNK_028681a9/*"unknown resource name = %s. priority = %d. localMode = %s."*/,uVar3,param_6,puVar1);
  }
  return;
}

// ==== CGameResourceManager::ReplaceFileName(char const*) const
// vaddr 0x17f8104 | ghidra 0x18f8104 | size 1328 | symbol _ZNK20CGameResourceManager15ReplaceFileNameEPKc | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Restarted to delay deadcode elimination for space: stack */

undefined8 _ZNK20CGameResourceManager15ReplaceFileNameEPKc(long param_1,undefined8 param_2)

{
  long lVar1;
  ulong uVar2;
  char *pcVar3;
  ulong uVar4;
  undefined *puVar5;
  undefined *puVar6;
  bool bVar7;
  uint uVar8;
  byte *pbVar9;
  undefined8 uVar10;
  ulong uVar11;
  undefined8 uVar12;
  long lVar13;
  byte *pbVar14;
  char cVar15;
  ulong uVar16;
  ulong uVar17;
  long lVar18;
  undefined8 uVar19;
  char *pcVar20;
  undefined8 uStack_1d0;
  ulong uStack_1c8;
  char *pcStack_1c0;
  undefined8 uStack_1b8;
  undefined8 uStack_1b0;
  undefined1 uStack_1a8;
  undefined8 uStack_1a0;
  undefined8 uStack_198;
  undefined1 uStack_190;
  undefined8 uStack_188;
  undefined8 uStack_180;
  char cStack_178;
  undefined1 uStack_170;
  undefined8 uStack_168;
  undefined1 auStack_d0 [8];
  undefined8 uStack_c8;
  undefined8 uStack_c0;
  undefined8 uStack_b8;
  undefined8 uStack_b0;
  undefined8 uStack_a8;
  long lStack_a0;
  undefined8 uStack_98;
  ulong uStack_90;
  ulong uStack_88;
  char *pcStack_80;
  undefined1 auStack_78 [20];
  uint uStack_64;
  
  Framework::CHash32::CHash32(char const*)(auStack_78);
  uVar8 = Framework::CHash32::operator unsigned int() const(auStack_78);
  Framework::CHash32::~CHash32()(auStack_78);
  uVar11 = *(ulong *)(param_1 + 0x50);
  lVar1 = param_1 + 0x28;
  uStack_64 = uVar8;
  if (uVar11 != 0) {
    uVar16 = ~(ulong)uVar8 + (ulong)uVar8 * 0x200000;
    uVar16 = (uVar16 ^ uVar16 >> 0x18) * 0x109;
    uVar17 = (uVar16 ^ uVar16 >> 0xe) * 0x15;
    uVar16 = 0;
    do {
      uVar2 = (uVar17 ^ uVar17 >> 0x1c) * 0x80000001 + uVar16;
      uVar4 = 0;
      if (uVar11 != 0) {
        uVar4 = uVar2 / uVar11;
      }
      lVar18 = uVar2 - uVar4 * uVar11;
      cVar15 = *(char *)(*(long *)(param_1 + 0x48) + lVar18 * 0x108);
      if (cVar15 == '\x01') {
        if (*(uint *)(*(long *)(param_1 + 0x48) + lVar18 * 0x108 + 4) == uVar8) {
          uVar19 = Aska::THashMap<unsigned int, Framework::TStaticString<256ul>, Aska::THasher<unsigned int>, Aska::TEqualTo<unsigned int>, Aska::TAllocator<Aska::TPair<unsigned int const, Framework::TStaticString<256ul> > > >::operator[](unsigned int const&)(lVar1,&uStack_64);
          return uVar19;
        }
      }
      else if (cVar15 == '\0') break;
      uVar16 = uVar16 + 1;
    } while (uVar16 < uVar11);
  }
  uStack_88 = 0;
  pcStack_80 = (char *)0x0;
  uStack_90 = 0;
  uVar11 = strlen(param_2);
  if (uVar11 < 0x17) {
    pcVar20 = (char *)((ulong)&uStack_90 | 1);
    uStack_90 = CONCAT71(uStack_90._1_7_,(char)(uVar11 << 1));
    if (uVar11 == 0) goto code_r0x018f8274;
  }
  else {
    uVar16 = uVar11 + 0x10 & 0xfffffffffffffff0;
    if (uVar16 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
    }
    pcVar20 = (char *)Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar16,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
    if (pcVar20 == (char *)0x0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    }
    uStack_90 = uVar16 | 1;
    uStack_88 = uVar11;
    pcStack_80 = pcVar20;
  }
  memcpy(pcVar20,param_2,uVar11);
code_r0x018f8274:
  pcVar20[uVar11] = '\0';
  uVar19 = *(undefined8 *)(param_1 + 0x10);
  lVar18 = Framework::CCSV::NumRows() const(uVar19);
  puVar6 = PTR__ZNSt6__ndk15ctypeIcE2idE_02cc4c88;
  puVar5 = PTR__ZNSt6__ndk17collateIcE2idE_02cc0d10;
  if (lVar18 == 0) {
    pcVar20 = (char *)((ulong)&uStack_90 | 1);
  }
  else {
    pcVar20 = (char *)((ulong)&uStack_90 | 1);
    uVar11 = 0;
    uVar16 = 1;
    do {
      Framework::CCSV::Element(unsigned long, unsigned long) const(uVar19,uVar11,0);
      pbVar9 = (byte *)Framework::CCSV::tElement::String() const();
      pbVar14 = *(byte **)(pbVar9 + 0x10);
      if ((*pbVar9 & 1) == 0) {
        pbVar14 = pbVar9 + 1;
      }
      std::__ndk1::locale::locale()(auStack_d0);
      uStack_c8 = std::__ndk1::locale::use_facet(std::__ndk1::locale::id&) const(auStack_d0,puVar6);
      uStack_c0 = std::__ndk1::locale::use_facet(std::__ndk1::locale::id&) const(auStack_d0,puVar5);
      uStack_98 = 0;
      uStack_b0 = 0;
      uStack_b8 = 0;
      lStack_a0 = 0;
      uStack_a8 = 0;
      lVar18 = strlen(pbVar14);
      char const* std::__ndk1::basic_regex<char, std::__ndk1::regex_traits<char> >::__parse<char const*>(char const*, char const*)(auStack_d0,pbVar14,pbVar14 + lVar18);
      pcVar3 = pcVar20;
      if ((uStack_90 & 1) != 0) {
        pcVar3 = pcStack_80;
      }
      lVar18 = strlen(pcVar3);
      uStack_190 = 0;
      uStack_1a0 = 0;
      uStack_198 = 0;
      cStack_178 = '\0';
      uStack_188 = 0;
      uStack_180 = 0;
      uStack_170 = 0;
      uStack_168 = 0;
      uStack_1a8 = 0;
      uStack_1d0 = 0;
      uStack_1c8 = 0;
      uStack_1b8 = 0;
      uStack_1b0 = 0;
      pcStack_1c0 = (char *)0x0;
      uVar17 = bool std::__ndk1::basic_regex<char, std::__ndk1::regex_traits<char> >::__search<std::__ndk1::allocator<std::__ndk1::sub_match<char const*> > >(char const*, char const*, std::__ndk1::match_results<char const*, std::__ndk1::allocator<std::__ndk1::sub_match<char const*> > >&, std::__ndk1::regex_constants::match_flag_type) const(auStack_d0,pcVar3,pcVar3 + lVar18,&uStack_1d0,0x40);
      bVar7 = false;
      if ((uVar17 & 1) != 0) {
        if (cStack_178 == '\0') {
          bVar7 = true;
        }
        else if (uStack_1c8 == uStack_1d0) {
          bVar7 = false;
        }
        else {
          bVar7 = false;
          uStack_1c8 = uStack_1c8 +
                       (((uStack_1c8 - 0x18) - uStack_1d0) / 0x18 ^ 0xffffffffffffffff) * 0x18;
        }
      }
      if (uStack_1d0 != 0) {
        if (uStack_1c8 != uStack_1d0) {
          uStack_1c8 = uStack_1c8 +
                       (((uStack_1c8 - 0x18) - uStack_1d0) / 0x18 ^ 0xffffffffffffffff) * 0x18;
        }
        operator delete(void*)();
      }
      if (bVar7) {
        uVar16 = CUIUtility::IsImageQualityNormal()();
        lVar18 = *(long *)PTR__ZN4Aska12g_pRenderDevE_02cbb1a0;
        if (lVar18 == 0) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_028679cc/*"C:\BAS_Submission\Client\Project\..\Source\Game\Resource\GameResourceManager.cpp"*/,0x255,&UNK_028681e4/*"pd3dd is null."*/);
        }
        uVar17 = Aska::RenderDeviceGL::GetImageFlags() const(lVar18);
        bVar7 = (uVar16 & 1) == 0;
        uVar12 = 6;
        if (bVar7) {
          uVar12 = 7;
        }
        uVar10 = 4;
        if (bVar7) {
          uVar10 = 5;
        }
        if ((uVar17 & 0x100) != 0) {
          uVar12 = uVar10;
        }
        uVar10 = Framework::CCSV::Element(unsigned long, unsigned long) const(uVar19,uVar11,1);
        uVar19 = Framework::CCSV::Element(unsigned long, unsigned long) const(uVar19,uVar11,uVar12);
        uVar12 = Framework::CCSV::tElement::String() const(uVar10);
        uVar19 = Framework::CCSV::tElement::String() const(uVar19);
        Framework::CSTLStringUtility_Base<string >::Replace(string const&, string const&, string const&, bool*)(&uStack_1d0,&uStack_90,uVar12,uVar19,0);
        if ((uStack_90 & 1) == 0) {
          uStack_90 = uStack_90 & 0xffffffffffff0000;
        }
        else {
          *pcStack_80 = '\0';
          uStack_88 = 0;
        }
        string::reserve(unsigned long)(&uStack_90,0);
        pcStack_80 = pcStack_1c0;
        uStack_88 = uStack_1c8;
        uStack_90 = uStack_1d0;
        if (lStack_a0 != 0) {
          std::__ndk1::__shared_weak_count::__release_shared()();
        }
        std::__ndk1::locale::~locale()(auStack_d0);
        break;
      }
      if (lStack_a0 != 0) {
        std::__ndk1::__shared_weak_count::__release_shared()();
      }
      std::__ndk1::locale::~locale()(auStack_d0);
      uVar11 = Framework::CCSV::NumRows() const(uVar19);
      bVar7 = uVar16 < uVar11;
      uVar11 = uVar16;
      uVar16 = (ulong)((int)uVar16 + 1);
    } while (bVar7);
  }
  if ((uStack_90 & 1) != 0) {
    pcVar20 = pcStack_80;
  }
  cVar15 = *pcVar20;
  uStack_1d0 = CONCAT71(uStack_1d0._1_7_,cVar15);
  lVar18 = 0;
  do {
    lVar13 = lVar18;
    if (cVar15 == '\0') goto code_r0x018f85c4;
    cVar15 = pcVar20[lVar13 + 1];
    *(char *)((long)&uStack_1d0 + lVar13 + 1) = cVar15;
    lVar18 = lVar13 + 1;
  } while ((int)(lVar13 + 1) < 0xff);
  *(undefined1 *)((long)&uStack_1d0 + lVar13 + 1) = 0;
code_r0x018f85c4:
  uVar19 = Aska::THashMap<unsigned int, Framework::TStaticString<256ul>, Aska::THasher<unsigned int>, Aska::TEqualTo<unsigned int>, Aska::TAllocator<Aska::TPair<unsigned int const, Framework::TStaticString<256ul> > > >::operator[](unsigned int const&)(lVar1,&uStack_64);
  memcpy(uVar19,&uStack_1d0,0x100);
  uVar19 = Aska::THashMap<unsigned int, Framework::TStaticString<256ul>, Aska::THasher<unsigned int>, Aska::TEqualTo<unsigned int>, Aska::TAllocator<Aska::TPair<unsigned int const, Framework::TStaticString<256ul> > > >::operator[](unsigned int const&)(lVar1,&uStack_64);
  if ((uStack_90 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(pcStack_80);
  }
  return uVar19;
}

// ==== CGameResourceManager::FileExistLanguage(char const*, CGameResourceManager::iPriorityMode, Framework::TStaticString<256ul>*) const
// vaddr 0x17f8634 | ghidra 0x18f8634 | size 808 | symbol _ZNK20CGameResourceManager17FileExistLanguageEPKcNS_13iPriorityModeEPN9Framework13TStaticStringILm256EEE | lib libSOA-3.7.0.so | 2026-10-04
int _ZNK20CGameResourceManager17FileExistLanguageEPKcNS_13iPriorityModeEPN9Framework13TStaticStringILm256EEE
              (undefined8 param_1,char *param_2,undefined4 param_3,long param_4)

{
  undefined *puVar1;
  undefined4 uVar2;
  int iVar3;
  long lVar4;
  long lVar5;
  ulong uVar6;
  char cVar7;
  char cStack_150;
  char acStack_14f [255];
  
  cStack_150 = *param_2;
  lVar4 = 0;
  cVar7 = cStack_150;
  do {
    lVar5 = lVar4;
    if (cVar7 == '\0') goto code_r0x018f8698;
    cVar7 = param_2[lVar5 + 1];
    acStack_14f[lVar5] = cVar7;
    lVar4 = lVar5 + 1;
  } while ((int)(lVar5 + 1) < 0xff);
  acStack_14f[lVar5] = '\0';
code_r0x018f8698:
  if (param_2 != (char *)0x0) {
    lVar4 = Aska::PathUtil::GetTailName(char const*, unsigned long*)(param_2,0);
    lVar5 = Aska::PathUtil::GetExtentionName(char const*, unsigned long*)(lVar4,0);
    if ((((lVar4 != 0) && (lVar5 != 0)) &&
        (lVar4 = strstr(lVar4,&UNK_028681f3/*"Voice_"*/), lVar4 != 0)) &&
       (lVar4 = strstr(lVar5,&UNK_028681fa/*".spk"*/),
       puVar1 = PTR__ZN9Framework10TSingletonI9CLanguageE11m_pInstanceE_02cc1760, lVar4 != 0)) {
      lVar4 = *(long *)PTR__ZN9Framework10TSingletonI9CLanguageE11m_pInstanceE_02cc1760;
      if (lVar4 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
        lVar4 = *(long *)puVar1;
      }
      uVar2 = CLanguage::Voice() const(lVar4);
      CLanguage::PostfixLanguageCodeFilepath(Framework::TStaticString<256ul>&, CLanguage::tLanguage, bool)(&cStack_150,uVar2,1);
      iVar3 = CGameResourceManager::CheckResourceStatusByFileName(char const*, CGameResourceManager::iPriorityMode) const(param_1,&cStack_150,param_3);
      if (iVar3 != 0) goto code_r0x018f87d4;
    }
  }
  puVar1 = PTR__ZN9Framework10TSingletonI9CLanguageE11m_pInstanceE_02cc1760;
  lVar4 = *(long *)PTR__ZN9Framework10TSingletonI9CLanguageE11m_pInstanceE_02cc1760;
  if (lVar4 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar4 = *(long *)puVar1;
  }
  iVar3 = CLanguage::Current() const(lVar4);
  if ((iVar3 == 0x100) || (uVar6 = CLanguage::IsPostfixLanguageCode(char const*, CLanguage::tLanguage)(param_2,0x100), (uVar6 & 1) != 0)) {
    cStack_150 = *param_2;
    lVar4 = 0;
    cVar7 = cStack_150;
    do {
      lVar5 = lVar4;
      if (cVar7 == '\0') goto code_r0x018f87c0;
      cVar7 = param_2[lVar5 + 1];
      acStack_14f[lVar5] = cVar7;
      lVar4 = lVar5 + 1;
    } while ((int)(lVar5 + 1) < 0xff);
    acStack_14f[lVar5] = '\0';
  }
  else {
    cStack_150 = *param_2;
    lVar4 = 0;
    cVar7 = cStack_150;
    do {
      lVar5 = lVar4;
      if (cVar7 == '\0') goto code_r0x018f8844;
      cVar7 = param_2[lVar5 + 1];
      acStack_14f[lVar5] = cVar7;
      lVar4 = lVar5 + 1;
    } while ((int)(lVar5 + 1) < 0xff);
    acStack_14f[lVar5] = '\0';
code_r0x018f8844:
    lVar4 = *(long *)puVar1;
    if (lVar4 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
      lVar4 = *(long *)puVar1;
    }
    uVar2 = CLanguage::Current() const(lVar4);
    CLanguage::PostfixLanguageCodeFilepath(Framework::TStaticString<256ul>&, CLanguage::tLanguage, bool)(&cStack_150,uVar2,1);
    iVar3 = CGameResourceManager::CheckResourceStatusByFileName(char const*, CGameResourceManager::iPriorityMode) const(param_1,&cStack_150,param_3);
    if (iVar3 != 0) goto code_r0x018f87d4;
    cStack_150 = *param_2;
    lVar4 = 0;
    cVar7 = cStack_150;
    do {
      lVar5 = lVar4;
      if (cVar7 == '\0') goto code_r0x018f88d0;
      cVar7 = param_2[lVar5 + 1];
      acStack_14f[lVar5] = cVar7;
      lVar4 = lVar5 + 1;
    } while ((int)(lVar5 + 1) < 0xff);
    acStack_14f[lVar5] = '\0';
code_r0x018f88d0:
    iVar3 = CGameResourceManager::CheckResourceStatusByFileName(char const*, CGameResourceManager::iPriorityMode) const(param_1,&cStack_150,param_3);
    if (iVar3 != 0) goto code_r0x018f87d4;
    cStack_150 = *param_2;
    lVar4 = 0;
    cVar7 = cStack_150;
    do {
      lVar5 = lVar4;
      if (cVar7 == '\0') goto code_r0x018f8920;
      cVar7 = param_2[lVar5 + 1];
      acStack_14f[lVar5] = cVar7;
      lVar4 = lVar5 + 1;
    } while ((int)(lVar5 + 1) < 0xff);
    acStack_14f[lVar5] = '\0';
code_r0x018f8920:
    lVar4 = *(long *)puVar1;
    if (lVar4 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
      lVar4 = *(long *)puVar1;
    }
    uVar2 = CLanguage::Default() const(lVar4);
    CLanguage::PostfixLanguageCodeFilepath(Framework::TStaticString<256ul>&, CLanguage::tLanguage, bool)(&cStack_150,uVar2,1);
  }
code_r0x018f87c0:
  iVar3 = CGameResourceManager::CheckResourceStatusByFileName(char const*, CGameResourceManager::iPriorityMode) const(param_1,&cStack_150,param_3);
code_r0x018f87d4:
  if (param_4 != 0) {
    memcpy(param_4,&cStack_150,0x100);
  }
  return iVar3;
}

// ==== CGameResourceManager::DownloadDirectFile(char const*)
// vaddr 0x17f895c | ghidra 0x18f895c | size 208 | symbol _ZN20CGameResourceManager18DownloadDirectFileEPKc | lib libSOA-3.7.0.so | 2026-10-04
void _ZN20CGameResourceManager18DownloadDirectFileEPKc(long param_1,undefined8 param_2)

{
  int iVar1;
  undefined8 uVar2;
  long lVar3;
  code *pcVar4;
  long alStack_150 [4];
  long *plStack_130;
  undefined1 auStack_120 [256];
  
  if (*(long *)(param_1 + 8) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_028679cc/*"C:\BAS_Submission\Client\Project\..\Source\Game\Resource\GameResourceManager.cpp"*/,0x324,&UNK_027e7586/*"m_pSubstance is null."*/);
  }
  uVar2 = CGameResourceManager::ReplaceFileName(char const*) const(param_1,param_2);
  auStack_120[0] = 0;
  iVar1 = CGameResourceManager::FileExistLanguage(char const*, CGameResourceManager::iPriorityMode, Framework::TStaticString<256ul>*) const(param_1,uVar2,2,auStack_120);
  if (iVar1 == 1) {
    lVar3 = *(long *)(param_1 + 0x20);
    if (lVar3 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_028679cc/*"C:\BAS_Submission\Client\Project\..\Source\Game\Resource\GameResourceManager.cpp"*/,0xff,&UNK_02866cea/*"m_pDownLoader is null."*/);
      lVar3 = *(long *)(param_1 + 0x20);
    }
    plStack_130 = (long *)0x0;
    CGameResourceDownloader::RequestDownload(char const*, std::__ndk1::function<void (char const*, CGameResourceDownloader::iErrorCode)>)(lVar3,auStack_120,alStack_150);
    if (alStack_150 == plStack_130) {
      pcVar4 = *(code **)(*plStack_130 + 0x20);
    }
    else {
      if (plStack_130 == (long *)0x0) {
        return;
      }
      pcVar4 = *(code **)(*plStack_130 + 0x28);
    }
    (*pcVar4)();
  }
  return;
}

// ==== CGameResourceManager::RemoveDirectFile(char const*)
// vaddr 0x17f8a2c | ghidra 0x18f8a2c | size 336 | symbol _ZN20CGameResourceManager16RemoveDirectFileEPKc | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN20CGameResourceManager16RemoveDirectFileEPKc(long param_1,undefined8 param_2)

{
  ulong uVar1;
  char cVar2;
  ulong uVar3;
  uint uVar4;
  undefined8 uVar5;
  ulong uVar6;
  ulong uVar7;
  ulong uVar8;
  char *pcVar9;
  long lVar10;
  undefined1 auStack_140 [16];
  undefined1 auStack_130 [256];
  
  lVar10 = *(long *)(param_1 + 8);
  if (lVar10 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_028679cc/*"C:\BAS_Submission\Client\Project\..\Source\Game\Resource\GameResourceManager.cpp"*/,0x324,&UNK_027e7586/*"m_pSubstance is null."*/);
    lVar10 = *(long *)(param_1 + 8);
  }
  uVar5 = CGameResourceManager::SearchFileMap(char const*) const(param_1,param_2);
  auStack_130[0] = 0;
  uVar6 = CGameResourceManager::RegisteredFileLanguage(char const*, Framework::TStaticString<256ul>&) const(param_1,uVar5,auStack_130);
  uVar5 = 0;
  if ((uVar6 & 1) != 0) {
    uVar6 = Framework::CResourceManager::RemoveDirectFile(char const*)(lVar10,auStack_130);
    if ((uVar6 & 1) == 0) {
      uVar5 = 0;
    }
    else {
      Framework::CHash32::CHash32(char const*)(auStack_140,param_2);
      uVar4 = Framework::CHash32::operator unsigned int() const(auStack_140);
      uVar6 = *(ulong *)(param_1 + 0x50);
      if (uVar6 != 0) {
        uVar7 = ~(ulong)uVar4 + (ulong)uVar4 * 0x200000;
        uVar7 = (uVar7 ^ uVar7 >> 0x18) * 0x109;
        uVar8 = (uVar7 ^ uVar7 >> 0xe) * 0x15;
        uVar7 = 0;
        do {
          uVar1 = (uVar8 ^ uVar8 >> 0x1c) * 0x80000001 + uVar7;
          uVar3 = 0;
          if (uVar6 != 0) {
            uVar3 = uVar1 / uVar6;
          }
          lVar10 = uVar1 - uVar3 * uVar6;
          pcVar9 = (char *)(*(long *)(param_1 + 0x48) + lVar10 * 0x108);
          cVar2 = *pcVar9;
          if (cVar2 == '\x01') {
            if (*(uint *)(*(long *)(param_1 + 0x48) + lVar10 * 0x108 + 4) == uVar4) {
              *(int *)(param_1 + 0x38) = *(int *)(param_1 + 0x38) + -1;
              *(int *)(param_1 + 0x3c) = *(int *)(param_1 + 0x3c) + 1;
              *pcVar9 = '\x02';
              break;
            }
          }
          else if (cVar2 == '\0') break;
          uVar7 = uVar7 + 1;
        } while (uVar7 < uVar6);
      }
      Framework::CHash32::~CHash32()(auStack_140);
      uVar5 = 1;
    }
  }
  return uVar5;
}

// ==== CGameResourceManager::SearchFileMap(char const*) const
// vaddr 0x17f8b7c | ghidra 0x18f8b7c | size 224 | symbol _ZNK20CGameResourceManager13SearchFileMapEPKc | lib libSOA-3.7.0.so | 2026-10-04
char * _ZNK20CGameResourceManager13SearchFileMapEPKc(long param_1,char *param_2)

{
  ulong uVar1;
  long lVar2;
  ulong uVar3;
  ulong uVar4;
  uint uVar5;
  char *pcVar6;
  ulong uVar7;
  ulong uVar8;
  char *pcVar9;
  long lVar10;
  undefined1 auStack_30 [16];
  
  Framework::CHash32::CHash32(char const*)(auStack_30);
  uVar5 = Framework::CHash32::operator unsigned int() const(auStack_30);
  Framework::CHash32::~CHash32()(auStack_30);
  lVar2 = *(long *)(param_1 + 0x48);
  uVar3 = *(ulong *)(param_1 + 0x50);
  if (uVar3 != 0) {
    uVar7 = ~(ulong)uVar5 + (ulong)uVar5 * 0x200000;
    uVar7 = (uVar7 ^ uVar7 >> 0x18) * 0x109;
    uVar8 = (uVar7 ^ uVar7 >> 0xe) * 0x15;
    uVar7 = 0;
    do {
      uVar1 = (uVar8 ^ uVar8 >> 0x1c) * 0x80000001 + uVar7;
      uVar4 = 0;
      if (uVar3 != 0) {
        uVar4 = uVar1 / uVar3;
      }
      lVar10 = uVar1 - uVar4 * uVar3;
      pcVar9 = (char *)(lVar2 + lVar10 * 0x108);
      if (*pcVar9 == '\x01') {
        if (*(uint *)(lVar2 + lVar10 * 0x108 + 4) == uVar5) {
          pcVar6 = (char *)(lVar2 + uVar3 * 0x108);
          goto code_r0x018f8c34;
        }
      }
      else if (*pcVar9 == '\0') break;
      uVar7 = uVar7 + 1;
    } while (uVar7 < uVar3);
  }
  pcVar6 = (char *)(lVar2 + uVar3 * 0x108);
  pcVar9 = pcVar6;
code_r0x018f8c34:
  if (pcVar9 != pcVar6) {
    param_2 = pcVar9 + 8;
  }
  return param_2;
}

// ==== CGameResourceManager::RegisteredFileLanguage(char const*, Framework::TStaticString<256ul>&) const
// vaddr 0x17f8c5c | ghidra 0x18f8c5c | size 660 | symbol _ZNK20CGameResourceManager22RegisteredFileLanguageEPKcRN9Framework13TStaticStringILm256EEE | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZNK20CGameResourceManager22RegisteredFileLanguageEPKcRN9Framework13TStaticStringILm256EEE
          (long param_1,char *param_2,undefined8 param_3)

{
  undefined *puVar1;
  undefined4 uVar2;
  long lVar3;
  long lVar4;
  char cVar5;
  long lVar6;
  char cStack_140;
  char acStack_13f [255];
  char acStack_34 [4];
  
  lVar6 = *(long *)(param_1 + 8);
  if (lVar6 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_028679cc/*"C:\BAS_Submission\Client\Project\..\Source\Game\Resource\GameResourceManager.cpp"*/,0x329,&UNK_027e7586/*"m_pSubstance is null."*/);
    lVar6 = *(long *)(param_1 + 8);
  }
  cStack_140 = *param_2;
  lVar3 = 0;
  cVar5 = cStack_140;
  do {
    lVar4 = lVar3;
    if (cVar5 == '\0') goto code_r0x018f8cdc;
    cVar5 = param_2[lVar4 + 1];
    acStack_13f[lVar4] = cVar5;
    lVar3 = lVar4 + 1;
  } while ((int)(lVar4 + 1) < 0xff);
  acStack_13f[lVar4] = '\0';
code_r0x018f8cdc:
  acStack_34[0] = '\0';
  Framework::CResourceManager::IsReadyDirectFile(char const*, bool*) const(lVar6,&cStack_140,acStack_34);
  if (acStack_34[0] == '\0') {
    if (param_2 != (char *)0x0) {
      lVar3 = Aska::PathUtil::GetTailName(char const*, unsigned long*)(param_2,0);
      lVar4 = Aska::PathUtil::GetExtentionName(char const*, unsigned long*)(lVar3,0);
      if ((((lVar3 != 0) && (lVar4 != 0)) &&
          (lVar3 = strstr(lVar3,&UNK_028681f3/*"Voice_"*/), lVar3 != 0)) &&
         (lVar3 = strstr(lVar4,&UNK_028681fa/*".spk"*/),
         puVar1 = PTR__ZN9Framework10TSingletonI9CLanguageE11m_pInstanceE_02cc1760, lVar3 != 0)) {
        lVar3 = *(long *)PTR__ZN9Framework10TSingletonI9CLanguageE11m_pInstanceE_02cc1760;
        if (lVar3 == 0) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
          lVar3 = *(long *)puVar1;
        }
        uVar2 = CLanguage::Voice() const(lVar3);
        CLanguage::PostfixLanguageCodeFilepath(Framework::TStaticString<256ul>&, CLanguage::tLanguage, bool)(&cStack_140,uVar2,1);
        Framework::CResourceManager::IsReadyDirectFile(char const*, bool*) const(lVar6,&cStack_140,acStack_34);
        if (acStack_34[0] != '\0') goto code_r0x018f8ebc;
      }
    }
    puVar1 = PTR__ZN9Framework10TSingletonI9CLanguageE11m_pInstanceE_02cc1760;
    cStack_140 = *param_2;
    lVar3 = 0;
    cVar5 = cStack_140;
    do {
      lVar4 = lVar3;
      if (cVar5 == '\0') goto code_r0x018f8ddc;
      cVar5 = param_2[lVar4 + 1];
      acStack_13f[lVar4] = cVar5;
      lVar3 = lVar4 + 1;
    } while ((int)(lVar4 + 1) < 0xff);
    acStack_13f[lVar4] = '\0';
code_r0x018f8ddc:
    lVar3 = *(long *)PTR__ZN9Framework10TSingletonI9CLanguageE11m_pInstanceE_02cc1760;
    if (lVar3 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
      lVar3 = *(long *)puVar1;
    }
    uVar2 = CLanguage::Current() const(lVar3);
    CLanguage::PostfixLanguageCodeFilepath(Framework::TStaticString<256ul>&, CLanguage::tLanguage, bool)(&cStack_140,uVar2,1);
    Framework::CResourceManager::IsReadyDirectFile(char const*, bool*) const(lVar6,&cStack_140,acStack_34);
    if (acStack_34[0] == '\0') {
      cStack_140 = *param_2;
      lVar3 = 0;
      cVar5 = cStack_140;
      do {
        lVar4 = lVar3;
        if (cVar5 == '\0') goto code_r0x018f8e6c;
        cVar5 = param_2[lVar4 + 1];
        acStack_13f[lVar4] = cVar5;
        lVar3 = lVar4 + 1;
      } while ((int)(lVar4 + 1) < 0xff);
      acStack_13f[lVar4] = '\0';
code_r0x018f8e6c:
      lVar3 = *(long *)puVar1;
      if (lVar3 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
        lVar3 = *(long *)puVar1;
      }
      uVar2 = CLanguage::Default() const(lVar3);
      CLanguage::PostfixLanguageCodeFilepath(Framework::TStaticString<256ul>&, CLanguage::tLanguage, bool)(&cStack_140,uVar2,1);
      Framework::CResourceManager::IsReadyDirectFile(char const*, bool*) const(lVar6,&cStack_140,acStack_34);
      if (acStack_34[0] == '\0') {
        return 0;
      }
    }
  }
code_r0x018f8ebc:
  memcpy(param_3,&cStack_140,0x100);
  return 1;
}

// ==== CGameResourceManager::RemoveForceDirectFile(char const*)
// vaddr 0x17f8ef0 | ghidra 0x18f8ef0 | size 336 | symbol _ZN20CGameResourceManager21RemoveForceDirectFileEPKc | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN20CGameResourceManager21RemoveForceDirectFileEPKc(long param_1,undefined8 param_2)

{
  ulong uVar1;
  char cVar2;
  ulong uVar3;
  uint uVar4;
  undefined8 uVar5;
  ulong uVar6;
  ulong uVar7;
  ulong uVar8;
  char *pcVar9;
  long lVar10;
  undefined1 auStack_140 [16];
  undefined1 auStack_130 [256];
  
  lVar10 = *(long *)(param_1 + 8);
  if (lVar10 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_028679cc/*"C:\BAS_Submission\Client\Project\..\Source\Game\Resource\GameResourceManager.cpp"*/,0x324,&UNK_027e7586/*"m_pSubstance is null."*/);
    lVar10 = *(long *)(param_1 + 8);
  }
  uVar5 = CGameResourceManager::SearchFileMap(char const*) const(param_1,param_2);
  auStack_130[0] = 0;
  uVar6 = CGameResourceManager::RegisteredFileLanguage(char const*, Framework::TStaticString<256ul>&) const(param_1,uVar5,auStack_130);
  uVar5 = 0;
  if ((uVar6 & 1) != 0) {
    uVar6 = Framework::CResourceManager::RemoveForceDirectFile(char const*)(lVar10,auStack_130);
    if ((uVar6 & 1) == 0) {
      uVar5 = 0;
    }
    else {
      Framework::CHash32::CHash32(char const*)(auStack_140,param_2);
      uVar4 = Framework::CHash32::operator unsigned int() const(auStack_140);
      uVar6 = *(ulong *)(param_1 + 0x50);
      if (uVar6 != 0) {
        uVar7 = ~(ulong)uVar4 + (ulong)uVar4 * 0x200000;
        uVar7 = (uVar7 ^ uVar7 >> 0x18) * 0x109;
        uVar8 = (uVar7 ^ uVar7 >> 0xe) * 0x15;
        uVar7 = 0;
        do {
          uVar1 = (uVar8 ^ uVar8 >> 0x1c) * 0x80000001 + uVar7;
          uVar3 = 0;
          if (uVar6 != 0) {
            uVar3 = uVar1 / uVar6;
          }
          lVar10 = uVar1 - uVar3 * uVar6;
          pcVar9 = (char *)(*(long *)(param_1 + 0x48) + lVar10 * 0x108);
          cVar2 = *pcVar9;
          if (cVar2 == '\x01') {
            if (*(uint *)(*(long *)(param_1 + 0x48) + lVar10 * 0x108 + 4) == uVar4) {
              *(int *)(param_1 + 0x38) = *(int *)(param_1 + 0x38) + -1;
              *(int *)(param_1 + 0x3c) = *(int *)(param_1 + 0x3c) + 1;
              *pcVar9 = '\x02';
              break;
            }
          }
          else if (cVar2 == '\0') break;
          uVar7 = uVar7 + 1;
        } while (uVar7 < uVar6);
      }
      Framework::CHash32::~CHash32()(auStack_140);
      uVar5 = 1;
    }
  }
  return uVar5;
}

// ==== CGameResourceManager::RemoveByUniqueBitFlag(unsigned int)
// vaddr 0x17f9040 | ghidra 0x18f9040 | size 68 | symbol _ZN20CGameResourceManager21RemoveByUniqueBitFlagEj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN20CGameResourceManager21RemoveByUniqueBitFlagEj(long param_1,undefined4 param_2)

{
  long lVar1;
  
  lVar1 = *(long *)(param_1 + 8);
  if (lVar1 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_028679cc/*"C:\BAS_Submission\Client\Project\..\Source\Game\Resource\GameResourceManager.cpp"*/,0x324,&UNK_027e7586/*"m_pSubstance is null."*/);
    lVar1 = *(long *)(param_1 + 8);
  }
  (*(code *)PTR__ZN9Framework16CResourceManager21RemoveByUniqueBitFlagEj_02c94470)(lVar1,param_2);
  return;
}

// ==== CGameResourceManager::IsReadyDirectFile(char const*) const
// vaddr 0x17f9084 | ghidra 0x18f9084 | size 144 | symbol _ZNK20CGameResourceManager17IsReadyDirectFileEPKc | lib libSOA-3.7.0.so | 2026-10-04
uint _ZNK20CGameResourceManager17IsReadyDirectFileEPKc(long param_1,undefined8 param_2)

{
  uint uVar1;
  undefined8 uVar2;
  ulong uVar3;
  long lVar4;
  undefined1 auStack_130 [256];
  
  lVar4 = *(long *)(param_1 + 8);
  if (lVar4 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_028679cc/*"C:\BAS_Submission\Client\Project\..\Source\Game\Resource\GameResourceManager.cpp"*/,0x329,&UNK_027e7586/*"m_pSubstance is null."*/);
    lVar4 = *(long *)(param_1 + 8);
  }
  uVar2 = CGameResourceManager::SearchFileMap(char const*) const(param_1,param_2);
  auStack_130[0] = 0;
  uVar3 = CGameResourceManager::RegisteredFileLanguage(char const*, Framework::TStaticString<256ul>&) const(param_1,uVar2,auStack_130);
  uVar1 = 0;
  if ((uVar3 & 1) != 0) {
    uVar1 = Framework::CResourceManager::IsReadyDirectFile(char const*, bool*) const(lVar4,auStack_130,0);
  }
  return uVar1 & 1;
}

// ==== CGameResourceManager::Lock()
// vaddr 0x17f9114 | ghidra 0x18f9114 | size 60 | symbol _ZN20CGameResourceManager4LockEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN20CGameResourceManager4LockEv(long param_1)

{
  long lVar1;
  
  lVar1 = *(long *)(param_1 + 8);
  if (lVar1 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_028679cc/*"C:\BAS_Submission\Client\Project\..\Source\Game\Resource\GameResourceManager.cpp"*/,0x324,&UNK_027e7586/*"m_pSubstance is null."*/);
    lVar1 = *(long *)(param_1 + 8);
  }
  (*(code *)PTR__ZN9Framework16CResourceManager4LockEv_02ca2d40)(lVar1);
  return;
}

// ==== CGameResourceManager::Unlock()
// vaddr 0x17f9150 | ghidra 0x18f9150 | size 60 | symbol _ZN20CGameResourceManager6UnlockEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN20CGameResourceManager6UnlockEv(long param_1)

{
  long lVar1;
  
  lVar1 = *(long *)(param_1 + 8);
  if (lVar1 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_028679cc/*"C:\BAS_Submission\Client\Project\..\Source\Game\Resource\GameResourceManager.cpp"*/,0x324,&UNK_027e7586/*"m_pSubstance is null."*/);
    lVar1 = *(long *)(param_1 + 8);
  }
  (*(code *)PTR__ZN9Framework16CResourceManager6UnlockEv_02c991c0)(lVar1);
  return;
}

// ==== CGameResourceManager::IsLocked() const
// vaddr 0x17f918c | ghidra 0x18f918c | size 60 | symbol _ZNK20CGameResourceManager8IsLockedEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK20CGameResourceManager8IsLockedEv(long param_1)

{
  long lVar1;
  
  lVar1 = *(long *)(param_1 + 8);
  if (lVar1 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_028679cc/*"C:\BAS_Submission\Client\Project\..\Source\Game\Resource\GameResourceManager.cpp"*/,0x329,&UNK_027e7586/*"m_pSubstance is null."*/);
    lVar1 = *(long *)(param_1 + 8);
  }
  (*(code *)PTR__ZNK9Framework16CResourceManager8IsLockedEv_02caf5b0)(lVar1);
  return;
}

// ==== CGameResourceManager::LockCounter() const
// vaddr 0x17f91c8 | ghidra 0x18f91c8 | size 60 | symbol _ZNK20CGameResourceManager11LockCounterEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK20CGameResourceManager11LockCounterEv(long param_1)

{
  long lVar1;
  
  lVar1 = *(long *)(param_1 + 8);
  if (lVar1 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_028679cc/*"C:\BAS_Submission\Client\Project\..\Source\Game\Resource\GameResourceManager.cpp"*/,0x329,&UNK_027e7586/*"m_pSubstance is null."*/);
    lVar1 = *(long *)(param_1 + 8);
  }
  (*(code *)PTR__ZNK9Framework16CResourceManager11LockCounterEv_02cae310)(lVar1);
  return;
}

// ==== CGameResourceManager::rResourceElementDirectFile(char const*)
// vaddr 0x17f9204 | ghidra 0x18f9204 | size 124 | symbol _ZN20CGameResourceManager26rResourceElementDirectFileEPKc | lib libSOA-3.7.0.so | 2026-10-04
void _ZN20CGameResourceManager26rResourceElementDirectFileEPKc(long param_1,undefined8 param_2)

{
  undefined8 uVar1;
  long lVar2;
  undefined1 auStack_130 [256];
  
  lVar2 = *(long *)(param_1 + 8);
  if (lVar2 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_028679cc/*"C:\BAS_Submission\Client\Project\..\Source\Game\Resource\GameResourceManager.cpp"*/,0x324,&UNK_027e7586/*"m_pSubstance is null."*/);
    lVar2 = *(long *)(param_1 + 8);
  }
  uVar1 = CGameResourceManager::SearchFileMap(char const*) const(param_1,param_2);
  auStack_130[0] = 0;
  CGameResourceManager::RegisteredFileLanguage(char const*, Framework::TStaticString<256ul>&) const(param_1,uVar1,auStack_130);
  Framework::CResourceManager::rResourceElementDirectFile(char const*)(lVar2,auStack_130);
  return;
}

// ==== CGameResourceManager::crResourceElementDirectFile(char const*) const
// vaddr 0x17f9280 | ghidra 0x18f9280 | size 124 | symbol _ZNK20CGameResourceManager27crResourceElementDirectFileEPKc | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK20CGameResourceManager27crResourceElementDirectFileEPKc(long param_1,undefined8 param_2)

{
  undefined8 uVar1;
  long lVar2;
  undefined1 auStack_130 [256];
  
  lVar2 = *(long *)(param_1 + 8);
  if (lVar2 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_028679cc/*"C:\BAS_Submission\Client\Project\..\Source\Game\Resource\GameResourceManager.cpp"*/,0x329,&UNK_027e7586/*"m_pSubstance is null."*/);
    lVar2 = *(long *)(param_1 + 8);
  }
  uVar1 = CGameResourceManager::SearchFileMap(char const*) const(param_1,param_2);
  auStack_130[0] = 0;
  CGameResourceManager::RegisteredFileLanguage(char const*, Framework::TStaticString<256ul>&) const(param_1,uVar1,auStack_130);
  Framework::CResourceManager::crResourceElementDirectFile(char const*) const(lVar2,auStack_130);
  return;
}

// ==== CGameResourceManager::crResourceElementByIndex(unsigned int) const
// vaddr 0x17f92fc | ghidra 0x18f92fc | size 72 | symbol _ZNK20CGameResourceManager24crResourceElementByIndexEj | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK20CGameResourceManager24crResourceElementByIndexEj(long param_1,undefined4 param_2)

{
  long lVar1;
  
  lVar1 = *(long *)(param_1 + 8);
  if (lVar1 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_028679cc/*"C:\BAS_Submission\Client\Project\..\Source\Game\Resource\GameResourceManager.cpp"*/,0x329,&UNK_027e7586/*"m_pSubstance is null."*/);
    lVar1 = *(long *)(param_1 + 8);
  }
  Framework::CResourceManager::crResourceElementByIndex(unsigned int) const(lVar1,param_2);
  return;
}

// ==== CGameResourceManager::NumLoading() const
// vaddr 0x17f9344 | ghidra 0x18f9344 | size 120 | symbol _ZNK20CGameResourceManager10NumLoadingEv | lib libSOA-3.7.0.so | 2026-10-04
int _ZNK20CGameResourceManager10NumLoadingEv(long param_1)

{
  int iVar1;
  int iVar2;
  long lVar3;
  
  if (*(long *)(param_1 + 0x20) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_028679cc/*"C:\BAS_Submission\Client\Project\..\Source\Game\Resource\GameResourceManager.cpp"*/,0x192,&UNK_02866cea/*"m_pDownLoader is null."*/);
    lVar3 = *(long *)(param_1 + 8);
  }
  else {
    lVar3 = *(long *)(param_1 + 8);
  }
  if (lVar3 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_028679cc/*"C:\BAS_Submission\Client\Project\..\Source\Game\Resource\GameResourceManager.cpp"*/,0x329,&UNK_027e7586/*"m_pSubstance is null."*/);
    lVar3 = *(long *)(param_1 + 8);
  }
  iVar1 = Framework::CResourceManager::NumLoading() const(lVar3);
  iVar2 = CGameResourceDownloader::NumDownloading() const(*(undefined8 *)(param_1 + 0x20));
  return iVar2 + iVar1;
}

// ==== CGameResourceManager::IsLoading() const
// vaddr 0x17f93bc | ghidra 0x18f93bc | size 192 | symbol _ZNK20CGameResourceManager9IsLoadingEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK20CGameResourceManager9IsLoadingEv(long param_1)

{
  int iVar1;
  undefined8 uVar2;
  long lVar3;
  ulong uVar4;
  
  lVar3 = *(long *)(param_1 + 0x20);
  if (lVar3 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_028679cc/*"C:\BAS_Submission\Client\Project\..\Source\Game\Resource\GameResourceManager.cpp"*/,0x19c,&UNK_02866cea/*"m_pDownLoader is null."*/);
    lVar3 = *(long *)(param_1 + 0x20);
  }
  iVar1 = Framework::CFiberUnit::Status() const(lVar3);
  if ((((iVar1 != 2) || (*(char *)(*(long *)(param_1 + 0x20) + 0x154) != '\0')) ||
      (*(char *)(*(long *)(param_1 + 0x20) + 0x5a8) != '\0')) ||
     (((uVar4 = CGameResourceDownloader::IsErrorStatus() const(), (uVar4 & 1) == 0 &&
       (uVar4 = CGameResourceDownloader::IsIdele() const(*(undefined8 *)(param_1 + 0x20)), (uVar4 & 1) == 0)) &&
      (uVar4 = CGameResourceDownloader::IsReadyDownload() const(*(undefined8 *)(param_1 + 0x20)), (uVar4 & 1) != 0)))) {
    if (*(long *)(param_1 + 8) == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_028679cc/*"C:\BAS_Submission\Client\Project\..\Source\Game\Resource\GameResourceManager.cpp"*/,0x329,&UNK_027e7586/*"m_pSubstance is null."*/);
      uVar4 = Framework::CResourceManager::IsLoading() const(*(undefined8 *)(param_1 + 8));
    }
    else {
      uVar4 = Framework::CResourceManager::IsLoading() const();
    }
    if ((uVar4 & 1) == 0) {
      uVar2 = (*(code *)PTR__ZNK23CGameResourceDownloader13IsDownloadingEv_02ca10e8)
                        (*(undefined8 *)(param_1 + 0x20));
      return uVar2;
    }
  }
  return 1;
}

// ==== CGameResourceManager::Num() const
// vaddr 0x17f947c | ghidra 0x18f947c | size 60 | symbol _ZNK20CGameResourceManager3NumEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK20CGameResourceManager3NumEv(long param_1)

{
  long lVar1;
  
  lVar1 = *(long *)(param_1 + 8);
  if (lVar1 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_028679cc/*"C:\BAS_Submission\Client\Project\..\Source\Game\Resource\GameResourceManager.cpp"*/,0x329,&UNK_027e7586/*"m_pSubstance is null."*/);
    lVar1 = *(long *)(param_1 + 8);
  }
  (*(code *)PTR__ZNK9Framework16CResourceManager3NumEv_02cb67c0)(lVar1);
  return;
}

// ==== CGameResourceManager::NumByUniqueBitFlag(unsigned int) const
// vaddr 0x17f94b8 | ghidra 0x18f94b8 | size 68 | symbol _ZNK20CGameResourceManager18NumByUniqueBitFlagEj | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK20CGameResourceManager18NumByUniqueBitFlagEj(long param_1,undefined4 param_2)

{
  long lVar1;
  
  lVar1 = *(long *)(param_1 + 8);
  if (lVar1 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_028679cc/*"C:\BAS_Submission\Client\Project\..\Source\Game\Resource\GameResourceManager.cpp"*/,0x329,&UNK_027e7586/*"m_pSubstance is null."*/);
    lVar1 = *(long *)(param_1 + 8);
  }
  (*(code *)PTR__ZNK9Framework16CResourceManager18NumByUniqueBitFlagEj_02cb17b0)(lVar1,param_2);
  return;
}

// ==== CGameResourceManager::PrintS(char const*)
// vaddr 0x17f94fc | ghidra 0x18f94fc | size 68 | symbol _ZN20CGameResourceManager6PrintSEPKc | lib libSOA-3.7.0.so | 2026-10-04
void _ZN20CGameResourceManager6PrintSEPKc(long param_1,undefined8 param_2)

{
  long lVar1;
  
  lVar1 = *(long *)(param_1 + 8);
  if (lVar1 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_028679cc/*"C:\BAS_Submission\Client\Project\..\Source\Game\Resource\GameResourceManager.cpp"*/,0x324,&UNK_027e7586/*"m_pSubstance is null."*/);
    lVar1 = *(long *)(param_1 + 8);
  }
  (*(code *)PTR__ZN9Framework16CResourceManager6PrintSEPKc_02ca0cb8)(lVar1,param_2);
  return;
}

// ==== CGameResourceManager::IsFileExist(char const*, bool) const
// vaddr 0x17f9540 | ghidra 0x18f9540 | size 80 | symbol _ZNK20CGameResourceManager11IsFileExistEPKcb | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK20CGameResourceManager11IsFileExistEPKcb
               (undefined8 param_1,undefined8 param_2,ulong param_3)

{
  bool bVar1;
  int iVar2;
  undefined8 uVar3;
  
  uVar3 = CGameResourceManager::ReplaceFileName(char const*) const();
  iVar2 = CGameResourceManager::FileExistLanguage(char const*, CGameResourceManager::iPriorityMode, Framework::TStaticString<256ul>*) const(param_1,uVar3,0,0);
  if ((param_3 & 1) == 0) {
    bVar1 = 2 < iVar2 - 3U;
  }
  else {
    bVar1 = iVar2 == 0;
  }
  return !bVar1;
}

// ==== CGameResourceManager::IsFileExistDownloadFolder(char const*) const
// vaddr 0x17f9590 | ghidra 0x18f9590 | size 864 | symbol _ZNK20CGameResourceManager25IsFileExistDownloadFolderEPKc | lib libSOA-3.7.0.so | 2026-10-04
uint _ZNK20CGameResourceManager25IsFileExistDownloadFolderEPKc(long param_1,char *param_2)

{
  undefined *puVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  long lVar5;
  ulong uVar6;
  long lVar7;
  char cVar8;
  byte *pbVar9;
  char cStack_130;
  char acStack_12f [255];
  
  lVar7 = *(long *)(param_1 + 0x20);
  if (lVar7 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_028679cc/*"C:\BAS_Submission\Client\Project\..\Source\Game\Resource\GameResourceManager.cpp"*/,0x1e8,&UNK_02866cea/*"m_pDownLoader is null."*/);
    lVar7 = *(long *)(param_1 + 0x20);
    cVar8 = *(char *)(lVar7 + 0x154);
  }
  else {
    cVar8 = *(char *)(lVar7 + 0x154);
  }
  if ((cVar8 != '\0') || (*(char *)(lVar7 + 0x5a8) != '\0')) {
    uVar4 = 0;
    goto code_r0x018f96c8;
  }
  cStack_130 = *param_2;
  lVar7 = 0;
  cVar8 = cStack_130;
  do {
    lVar5 = lVar7;
    if (cVar8 == '\0') goto code_r0x018f95fc;
    cVar8 = param_2[lVar5 + 1];
    acStack_12f[lVar5] = cVar8;
    lVar7 = lVar5 + 1;
  } while ((int)(lVar5 + 1) < 0xff);
  acStack_12f[lVar5] = '\0';
code_r0x018f95fc:
  if (param_2 == (char *)0x0) {
code_r0x018f96f0:
    puVar1 = PTR__ZN9Framework10TSingletonI9CLanguageE11m_pInstanceE_02cc1760;
    cStack_130 = *param_2;
    lVar7 = 0;
    cVar8 = cStack_130;
    do {
      lVar5 = lVar7;
      if (cVar8 == '\0') goto code_r0x018f972c;
      cVar8 = param_2[lVar5 + 1];
      acStack_12f[lVar5] = cVar8;
      lVar7 = lVar5 + 1;
    } while ((int)(lVar5 + 1) < 0xff);
    acStack_12f[lVar5] = '\0';
code_r0x018f972c:
    lVar7 = *(long *)PTR__ZN9Framework10TSingletonI9CLanguageE11m_pInstanceE_02cc1760;
    if (lVar7 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
      lVar7 = *(long *)puVar1;
    }
    iVar3 = CLanguage::Current() const(lVar7);
    if ((iVar3 == 0x100) || (uVar6 = CLanguage::IsPostfixLanguageCode(char const*, CLanguage::tLanguage)(param_2,0x100), (uVar6 & 1) != 0)) {
      uVar6 = CLanguage::IsPostfixLanguageCode(char const*, CLanguage::tLanguage)(&cStack_130,0x101);
      if ((uVar6 & 1) != 0) {
        CLanguage::RemoveLanguageCodeFilepath(Framework::TStaticString<256ul>&)(&cStack_130);
      }
      if ((*(byte *)(param_1 + 0x58) & 1) == 0) {
        param_1 = param_1 + 0x59;
      }
      else {
code_r0x018f98e0:
        param_1 = *(long *)(param_1 + 0x68);
      }
code_r0x018f98e4:
      uVar4 = Framework::CFileLoader::gIsFileExist(char const*, char const*)(&cStack_130,param_1);
      goto code_r0x018f96c8;
    }
    cStack_130 = *param_2;
    lVar7 = 0;
    cVar8 = cStack_130;
    do {
      lVar5 = lVar7;
      if (cVar8 == '\0') goto code_r0x018f97dc;
      cVar8 = param_2[lVar5 + 1];
      acStack_12f[lVar5] = cVar8;
      lVar7 = lVar5 + 1;
    } while ((int)(lVar5 + 1) < 0xff);
    acStack_12f[lVar5] = '\0';
code_r0x018f97dc:
    lVar7 = *(long *)puVar1;
    if (lVar7 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
      lVar7 = *(long *)puVar1;
    }
    uVar2 = CLanguage::Current() const(lVar7);
    CLanguage::PostfixLanguageCodeFilepath(Framework::TStaticString<256ul>&, CLanguage::tLanguage, bool)(&cStack_130,uVar2,1);
    pbVar9 = (byte *)(param_1 + 0x58);
    if ((*pbVar9 & 1) == 0) {
      lVar7 = param_1 + 0x59;
    }
    else {
      lVar7 = *(long *)(param_1 + 0x68);
    }
    uVar6 = Framework::CFileLoader::gIsFileExist(char const*, char const*)(&cStack_130,lVar7);
    if ((uVar6 & 1) == 0) {
      if ((*pbVar9 & 1) == 0) {
        lVar7 = param_1 + 0x59;
      }
      else {
        lVar7 = *(long *)(param_1 + 0x68);
      }
      uVar6 = Framework::CFileLoader::gIsFileExist(char const*, char const*)(param_2,lVar7);
      if ((uVar6 & 1) == 0) {
        cStack_130 = *param_2;
        lVar7 = 0;
        cVar8 = cStack_130;
        do {
          lVar5 = lVar7;
          if (cVar8 == '\0') goto code_r0x018f9898;
          cVar8 = param_2[lVar5 + 1];
          acStack_12f[lVar5] = cVar8;
          lVar7 = lVar5 + 1;
        } while ((int)(lVar5 + 1) < 0xff);
        acStack_12f[lVar5] = '\0';
code_r0x018f9898:
        lVar7 = *(long *)puVar1;
        if (lVar7 == 0) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
          lVar7 = *(long *)puVar1;
        }
        uVar2 = CLanguage::Default() const(lVar7);
        CLanguage::PostfixLanguageCodeFilepath(Framework::TStaticString<256ul>&, CLanguage::tLanguage, bool)(&cStack_130,uVar2,1);
        if ((*pbVar9 & 1) != 0) goto code_r0x018f98e0;
        param_1 = param_1 + 0x59;
        goto code_r0x018f98e4;
      }
    }
  }
  else {
    lVar7 = Aska::PathUtil::GetTailName(char const*, unsigned long*)(param_2,0);
    lVar5 = Aska::PathUtil::GetExtentionName(char const*, unsigned long*)(lVar7,0);
    if ((((lVar7 == 0) || (lVar5 == 0)) ||
        (lVar7 = strstr(lVar7,&UNK_028681f3/*"Voice_"*/), lVar7 == 0)) ||
       (lVar7 = strstr(lVar5,&UNK_028681fa/*".spk"*/),
       puVar1 = PTR__ZN9Framework10TSingletonI9CLanguageE11m_pInstanceE_02cc1760, lVar7 == 0))
    goto code_r0x018f96f0;
    lVar7 = *(long *)PTR__ZN9Framework10TSingletonI9CLanguageE11m_pInstanceE_02cc1760;
    if (lVar7 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
      lVar7 = *(long *)puVar1;
    }
    uVar2 = CLanguage::Voice() const(lVar7);
    CLanguage::PostfixLanguageCodeFilepath(Framework::TStaticString<256ul>&, CLanguage::tLanguage, bool)(&cStack_130,uVar2,1);
    if ((*(byte *)(param_1 + 0x58) & 1) == 0) {
      lVar7 = param_1 + 0x59;
    }
    else {
      lVar7 = *(long *)(param_1 + 0x68);
    }
    uVar6 = Framework::CFileLoader::gIsFileExist(char const*, char const*)(&cStack_130,lVar7);
    if ((uVar6 & 1) == 0) goto code_r0x018f96f0;
  }
  uVar4 = 1;
code_r0x018f96c8:
  return uVar4 & 1;
}

// ==== CGameResourceManager::IsVoiceFile(char const*) const
// vaddr 0x17f98f0 | ghidra 0x18f98f0 | size 116 | symbol _ZNK20CGameResourceManager11IsVoiceFileEPKc | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK20CGameResourceManager11IsVoiceFileEPKc(undefined8 param_1,long param_2)

{
  long lVar1;
  long lVar2;
  
  if (param_2 != 0) {
    lVar1 = Aska::PathUtil::GetTailName(char const*, unsigned long*)(param_2,0);
    lVar2 = Aska::PathUtil::GetExtentionName(char const*, unsigned long*)(lVar1,0);
    if (lVar1 == 0) {
      return 0;
    }
    if (lVar2 == 0) {
      return 0;
    }
    lVar1 = strstr(lVar1,&UNK_028681f3/*"Voice_"*/);
    if ((lVar1 != 0) && (lVar1 = strstr(lVar2,&UNK_028681fa/*".spk"*/), lVar1 != 0)) {
      return 1;
    }
  }
  return 0;
}

// ==== CGameResourceManager::CheckResourceStatus(unsigned int, CGameResourceManager::iPriorityMode) const
// vaddr 0x17f9aa8 | ghidra 0x18f9aa8 | size 48 | symbol _ZNK20CGameResourceManager19CheckResourceStatusEjNS_13iPriorityModeE | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK20CGameResourceManager19CheckResourceStatusEjNS_13iPriorityModeE
               (undefined8 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined8 uVar1;
  
  uVar1 = Framework::FileID::gpFileName(unsigned int)(param_2);
  (*(code *)
    PTR__ZNK20CGameResourceManager29CheckResourceStatusByFileNameEPKcNS_13iPriorityModeE_02c8fa18)
            (param_1,uVar1,param_3);
  return;
}

// ==== CGameResourceManager::CheckResourceStatusByFileName(char const*, CGameResourceManager::iPriorityMode) const
// vaddr 0x17f9ad8 | ghidra 0x18f9ad8 | size 460 | symbol _ZNK20CGameResourceManager29CheckResourceStatusByFileNameEPKcNS_13iPriorityModeE | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZNK20CGameResourceManager29CheckResourceStatusByFileNameEPKcNS_13iPriorityModeE
          (long param_1,undefined8 param_2,int param_3)

{
  long lVar1;
  ulong uVar2;
  undefined8 uVar3;
  undefined1 auStack_130 [256];
  
  lVar1 = *(long *)(param_1 + 0x20);
  if (lVar1 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_028679cc/*"C:\BAS_Submission\Client\Project\..\Source\Game\Resource\GameResourceManager.cpp"*/,0x2a5,&UNK_02866cea/*"m_pDownLoader is null."*/);
    lVar1 = *(long *)(param_1 + 0x20);
  }
  if (((param_3 == 1) || (param_3 != 2 && *(char *)(lVar1 + 0x5a8) != '\0')) ||
     (*(char *)(lVar1 + 0x154) != '\0')) {
    lVar1 = *(long *)(param_1 + 8);
    if (lVar1 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_028679cc/*"C:\BAS_Submission\Client\Project\..\Source\Game\Resource\GameResourceManager.cpp"*/,0x329,&UNK_027e7586/*"m_pSubstance is null."*/);
      lVar1 = *(long *)(param_1 + 8);
    }
    uVar3 = CGameResourceManager::SearchFileMap(char const*) const(param_1,param_2);
    auStack_130[0] = 0;
    uVar2 = CGameResourceManager::RegisteredFileLanguage(char const*, Framework::TStaticString<256ul>&) const(param_1,uVar3,auStack_130);
    if (((uVar2 & 1) != 0) && (uVar2 = Framework::CResourceManager::IsReadyDirectFile(char const*, bool*) const(lVar1,auStack_130,0), (uVar2 & 1) != 0)) {
      return 5;
    }
  }
  else {
    uVar2 = CGameResourceDownloader::IsBuildInData(char const*) const(lVar1,param_2);
    if (((uVar2 & 1) != 0) && (uVar2 = Framework::CFileLoader::gIsFileExist(char const*, char const*)(param_2,0), (uVar2 & 1) != 0)) {
      return 4;
    }
    lVar1 = *(long *)(param_1 + 8);
    if (lVar1 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_028679cc/*"C:\BAS_Submission\Client\Project\..\Source\Game\Resource\GameResourceManager.cpp"*/,0x329,&UNK_027e7586/*"m_pSubstance is null."*/);
      lVar1 = *(long *)(param_1 + 8);
    }
    uVar3 = CGameResourceManager::SearchFileMap(char const*) const(param_1,param_2);
    auStack_130[0] = 0;
    uVar2 = CGameResourceManager::RegisteredFileLanguage(char const*, Framework::TStaticString<256ul>&) const(param_1,uVar3,auStack_130);
    if (((uVar2 & 1) != 0) && (uVar2 = Framework::CResourceManager::IsReadyDirectFile(char const*, bool*) const(lVar1,auStack_130,0), (uVar2 & 1) != 0)) {
      return 5;
    }
    uVar2 = CGameResourceDownloader::IsReadyDownload() const(*(undefined8 *)(param_1 + 0x20));
    if ((uVar2 & 1) == 0) {
      return 1;
    }
    uVar2 = CGameResourceDownloader::IsExistDownloadList(char const*) const(*(undefined8 *)(param_1 + 0x20),param_2);
    if ((uVar2 & 1) != 0) {
      return 2;
    }
    uVar2 = CGameResourceDownloader::IsExistDownloadDB(char const*) const(*(undefined8 *)(param_1 + 0x20),param_2);
    if ((uVar2 & 1) != 0) {
      return 1;
    }
    uVar2 = CGameResourceManager::IsFileExistDownloadFolder(char const*) const(param_1,param_2);
    if ((uVar2 & 1) != 0) {
      return 3;
    }
  }
  uVar2 = Framework::CFileLoader::gIsFileExist(char const*, char const*)(param_2,0);
  if ((uVar2 & 1) != 0) {
    return 4;
  }
  return 0;
}

// ==== CGameResourceManager::MakeResolutionPath(char const*)
// vaddr 0x17f9ca4 | ghidra 0x18f9ca4 | size 736 | symbol _ZN20CGameResourceManager18MakeResolutionPathEPKc | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN20CGameResourceManager18MakeResolutionPathEPKc(ulong *param_1,undefined8 param_2)

{
  byte *pbVar1;
  ulong uVar2;
  byte bVar3;
  bool bVar4;
  uint uVar5;
  ulong *puVar6;
  long lVar7;
  ulong uVar8;
  undefined8 uVar9;
  undefined *puVar10;
  long lVar11;
  ulong uVar12;
  ulong uVar13;
  byte *pbVar14;
  ulong uStack_68;
  undefined8 uStack_60;
  undefined8 uStack_58;
  ulong uStack_50;
  ulong uStack_48;
  ulong uStack_40;
  
  puVar10 = PTR__ZN4Aska12g_pRenderDevE_02cbb1a0;
  param_1[1] = 0;
  param_1[2] = 0;
  *param_1 = 0;
  lVar11 = *(long *)puVar10;
  if (lVar11 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_028679cc/*"C:\BAS_Submission\Client\Project\..\Source\Game\Resource\GameResourceManager.cpp"*/,0x3b8,&UNK_028681e4/*"pd3dd is null."*/);
    uVar13 = (ulong)(byte)*param_1;
  }
  else {
    uVar13 = 0;
  }
  uVar5 = Aska::RenderDeviceGL::GetImageFlags() const(lVar11);
  uVar9 = _UNK_0286821f;
  if ((uVar5 >> 8 & 1) == 0) {
    if ((uVar13 & 1) == 0) {
      lVar11 = 0x16;
      if ((uVar13 & 1) != 0) goto code_r0x018f9d10;
code_r0x018f9d3c:
      uVar8 = (ulong)(((uint)uVar13 & 0xfe) >> 1);
    }
    else {
      uVar13 = *param_1;
      lVar11 = (uVar13 & 0xfffffffffffffffe) - 1;
      if ((uVar13 & 1) == 0) goto code_r0x018f9d3c;
code_r0x018f9d10:
      uVar8 = param_1[1];
    }
    if (lVar11 - uVar8 < 9) {
      lVar7 = (9 - lVar11) + uVar8;
      puVar10 = &UNK_0286821f/*"software/"*/;
      uVar9 = 9;
      goto code_r0x018f9da8;
    }
    if ((uVar13 & 1) == 0) {
      pbVar14 = (byte *)((long)param_1 + 1);
    }
    else {
      pbVar14 = (byte *)param_1[2];
    }
    (pbVar14 + uVar8)[8] = 0x2f;
    *(undefined8 *)(pbVar14 + uVar8) = uVar9;
    uVar8 = uVar8 + 9;
    if ((*param_1 & 1) == 0) goto code_r0x018f9e00;
code_r0x018f9e34:
    param_1[1] = uVar8;
code_r0x018f9e38:
    pbVar14[uVar8] = 0;
  }
  else {
    if ((uVar13 & 1) == 0) {
      lVar11 = 0x16;
      if ((uVar13 & 1) != 0) goto code_r0x018f9d24;
code_r0x018f9d7c:
      uVar8 = (ulong)(((uint)uVar13 & 0xfe) >> 1);
    }
    else {
      uVar13 = *param_1;
      lVar11 = (uVar13 & 0xfffffffffffffffe) - 1;
      if ((uVar13 & 1) == 0) goto code_r0x018f9d7c;
code_r0x018f9d24:
      uVar8 = param_1[1];
    }
    if (4 < lVar11 - uVar8) {
      if ((uVar13 & 1) == 0) {
        pbVar14 = (byte *)((long)param_1 + 1);
      }
      else {
        pbVar14 = (byte *)param_1[2];
      }
      pbVar1 = pbVar14 + uVar8;
      pbVar1[4] = 0x2f;
      pbVar1[0] = 0x65;
      pbVar1[1] = 0x74;
      pbVar1[2] = 99;
      pbVar1[3] = 0x32;
      uVar8 = uVar8 + 5;
      if ((*param_1 & 1) != 0) goto code_r0x018f9e34;
code_r0x018f9e00:
      *(byte *)param_1 = (byte)(uVar8 << 1);
      goto code_r0x018f9e38;
    }
    lVar7 = (5 - lVar11) + uVar8;
    puVar10 = &UNK_02868229/*"etc2/"*/;
    uVar9 = 5;
code_r0x018f9da8:
    string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(param_1,lVar11,lVar7,uVar8,uVar8,0,uVar9,puVar10);
  }
  uStack_60 = 0;
  uStack_58 = 0;
  uStack_68 = 0x2f02;
  puVar6 = (ulong *)string::insert(unsigned long, char const*)(&uStack_68,0,param_2);
  uStack_40 = puVar6[2];
  uStack_48 = puVar6[1];
  uStack_50 = *puVar6;
  puVar6[1] = 0;
  puVar6[2] = 0;
  *puVar6 = 0;
  bVar3 = (byte)*param_1;
  uVar8 = (ulong)bVar3;
  bVar4 = (uStack_50 & 1) != 0;
  uVar13 = (ulong)&uStack_50 | 1;
  if (bVar4) {
    uVar13 = uStack_40;
  }
  uVar2 = uStack_50 >> 1 & 0x7f;
  if (bVar4) {
    uVar2 = uStack_48;
  }
  if ((bVar3 & 1) == 0) {
    lVar11 = 0x16;
    if ((bVar3 & 1) == 0) {
code_r0x018f9ec0:
      uVar12 = (ulong)(((uint)uVar8 & 0xfe) >> 1);
      goto code_r0x018f9ec8;
    }
  }
  else {
    uVar8 = *param_1;
    lVar11 = (uVar8 & 0xfffffffffffffffe) - 1;
    if ((uVar8 & 1) == 0) goto code_r0x018f9ec0;
  }
  uVar12 = param_1[1];
code_r0x018f9ec8:
  if (lVar11 - uVar12 < uVar2) {
    string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(param_1,lVar11,(uVar2 - lVar11) + uVar12,uVar12,uVar12,0,uVar2);
  }
  else if (uVar2 != 0) {
    if ((uVar8 & 1) == 0) {
      pbVar14 = (byte *)((long)param_1 + 1);
    }
    else {
      pbVar14 = (byte *)param_1[2];
    }
    memcpy(pbVar14 + uVar12,uVar13,uVar2);
    uVar12 = uVar12 + uVar2;
    if ((*param_1 & 1) == 0) {
      *(char *)param_1 = (char)uVar12 * '\x02';
      pbVar14[uVar12] = 0;
    }
    else {
      param_1[1] = uVar12;
      pbVar14[uVar12] = 0;
    }
  }
  if ((uStack_50 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_40);
  }
  if ((uStack_68 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_58);
  }
  return;
}

// ==== CGameResourceManager::MakeCurrentResolutionPath()
// vaddr 0x17f9f84 | ghidra 0x18f9f84 | size 48 | symbol _ZN20CGameResourceManager25MakeCurrentResolutionPathEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN20CGameResourceManager25MakeCurrentResolutionPathEv(undefined8 param_1)

{
  undefined *puVar1;
  ulong uVar2;
  
  uVar2 = CUIUtility::IsImageQualityNormal()();
  puVar1 = &UNK_0293efa8/*"low"*/;
  if ((uVar2 & 1) == 0) {
    puVar1 = &UNK_029e4f32/*"hi"*/;
  }
  (*(code *)PTR__ZN20CGameResourceManager18MakeResolutionPathEPKc_02ca4bc8)(param_1,puVar1);
  return;
}


// FAILED to create function at 02b10e78 CGameResourceManager::vtable
// FAILED to create function at 02b10eb0 CGameResourceManager::typeinfo
