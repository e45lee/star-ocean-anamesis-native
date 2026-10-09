// port/decomp/api/fakeapi.c: Ghidra decompiles for the api subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-09 01:43 UTC: tools/decomp.sh '--into' 'api/fakeapi' 'FakeApiCaller::'

// ==== FakeApiCaller::FakeApiCaller()
// vaddr 0x148ac38 | ghidra 0x158ac38 | size 220 | symbol _ZN13FakeApiCallerC1Ev | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCallerC2Ev(long *param_1)

{
  undefined *puVar1;
  long lVar2;
  long *plVar3;
  
  *param_1 = (long)(PTR__ZTV10IApiCaller_02cc1fd8 + 0x10);
  Framework::CFiberUnit::CFiberUnit(unsigned int)(param_1 + 1,0x600);
  puVar1 = PTR__ZTV13FakeApiCaller_02cbd4b8;
  param_1[10] = 0;
  param_1[1] = (long)(puVar1 + 0x700);
  *param_1 = (long)(puVar1 + 0x10);
  param_1[9] = 0;
  param_1[8] = (long)(param_1 + 9);
  CApiNotify::CApiNotify(IApiCaller*)(param_1 + 0xc,param_1);
  puVar1 = PTR__ZN9Framework10TSingletonINS_12CApplication9CMainTaskEE11m_pInstanceE_02cc41c8;
  lVar2 = *(long *)
           PTR__ZN9Framework10TSingletonINS_12CApplication9CMainTaskEE11m_pInstanceE_02cc41c8;
  if (lVar2 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar2 = *(long *)puVar1;
  }
  plVar3 = (long *)Framework::CApplication::CMainTask::rRootFiberKernel()(lVar2);
  (**(code **)(*plVar3 + 0x48))(plVar3,param_1 + 1);
  puVar1 = PTR__ZN9Framework10TSingletonI17CErrorHandlerWrapE11m_pInstanceE_02cbc0d8;
  lVar2 = *(long *)PTR__ZN9Framework10TSingletonI17CErrorHandlerWrapE11m_pInstanceE_02cbc0d8;
  if (lVar2 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar2 = *(long *)puVar1;
  }
  (*(code *)PTR__ZN17CErrorHandlerWrap16SetFakeAppCallerEv_02c95890)(lVar2);
  return;
}

// ==== FakeApiCaller::~FakeApiCaller()
// vaddr 0x148ad14 | ghidra 0x158ad14 | size 120 | symbol _ZN13FakeApiCallerD2Ev | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCallerD1Ev(long *param_1)

{
  undefined *puVar1;
  long *plVar2;
  
  puVar1 = PTR__ZTV13FakeApiCaller_02cbd4b8 + 0x10;
  param_1[1] = (long)(PTR__ZTV13FakeApiCaller_02cbd4b8 + 0x700);
  *param_1 = (long)puVar1;
  plVar2 = param_1 + 9;
  std::__ndk1::__tree<std::__ndk1::__value_type<Aska::Yayoi::GameRPC::GameProtocol::FunctionID, FakeApiCaller::Info>, std::__ndk1::__map_value_compare<Aska::Yayoi::GameRPC::GameProtocol::FunctionID, std::__ndk1::__value_type<Aska::Yayoi::GameRPC::GameProtocol::FunctionID, FakeApiCaller::Info>, std::__ndk1::less<Aska::Yayoi::GameRPC::GameProtocol::FunctionID>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<Aska::Yayoi::GameRPC::GameProtocol::FunctionID, FakeApiCaller::Info>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<Aska::Yayoi::GameRPC::GameProtocol::FunctionID, FakeApiCaller::Info>, void*>*)(param_1 + 8,*plVar2);
  param_1[8] = (long)plVar2;
  param_1[10] = 0;
  *plVar2 = 0;
  CApiNotify::~CApiNotify()(param_1 + 0xc);
  std::__ndk1::__tree<std::__ndk1::__value_type<Aska::Yayoi::GameRPC::GameProtocol::FunctionID, FakeApiCaller::Info>, std::__ndk1::__map_value_compare<Aska::Yayoi::GameRPC::GameProtocol::FunctionID, std::__ndk1::__value_type<Aska::Yayoi::GameRPC::GameProtocol::FunctionID, FakeApiCaller::Info>, std::__ndk1::less<Aska::Yayoi::GameRPC::GameProtocol::FunctionID>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<Aska::Yayoi::GameRPC::GameProtocol::FunctionID, FakeApiCaller::Info>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<Aska::Yayoi::GameRPC::GameProtocol::FunctionID, FakeApiCaller::Info>, void*>*)(param_1 + 8,*plVar2);
  (*(code *)PTR__ZN9Framework10CFiberUnitD1Ev_02c90ac0)(param_1 + 1);
  return;
}

// ==== non-virtual thunk to FakeApiCaller::~FakeApiCaller()
// vaddr 0x148ad8c | ghidra 0x158ad8c | size 108 | symbol _ZThn8_N13FakeApiCallerD1Ev | lib libSOA-3.7.0.so | 2026-10-09
void _ZThn8_N13FakeApiCallerD1Ev(long *param_1)

{
  undefined *puVar1;
  long *plVar2;
  
  puVar1 = PTR__ZTV13FakeApiCaller_02cbd4b8 + 0x10;
  *param_1 = (long)(PTR__ZTV13FakeApiCaller_02cbd4b8 + 0x700);
  param_1[-1] = (long)puVar1;
  plVar2 = param_1 + 8;
  std::__ndk1::__tree<std::__ndk1::__value_type<Aska::Yayoi::GameRPC::GameProtocol::FunctionID, FakeApiCaller::Info>, std::__ndk1::__map_value_compare<Aska::Yayoi::GameRPC::GameProtocol::FunctionID, std::__ndk1::__value_type<Aska::Yayoi::GameRPC::GameProtocol::FunctionID, FakeApiCaller::Info>, std::__ndk1::less<Aska::Yayoi::GameRPC::GameProtocol::FunctionID>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<Aska::Yayoi::GameRPC::GameProtocol::FunctionID, FakeApiCaller::Info>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<Aska::Yayoi::GameRPC::GameProtocol::FunctionID, FakeApiCaller::Info>, void*>*)(param_1 + 7,*plVar2);
  param_1[7] = (long)plVar2;
  param_1[9] = 0;
  *plVar2 = 0;
  CApiNotify::~CApiNotify()(param_1 + 0xb);
  std::__ndk1::__tree<std::__ndk1::__value_type<Aska::Yayoi::GameRPC::GameProtocol::FunctionID, FakeApiCaller::Info>, std::__ndk1::__map_value_compare<Aska::Yayoi::GameRPC::GameProtocol::FunctionID, std::__ndk1::__value_type<Aska::Yayoi::GameRPC::GameProtocol::FunctionID, FakeApiCaller::Info>, std::__ndk1::less<Aska::Yayoi::GameRPC::GameProtocol::FunctionID>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<Aska::Yayoi::GameRPC::GameProtocol::FunctionID, FakeApiCaller::Info>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<Aska::Yayoi::GameRPC::GameProtocol::FunctionID, FakeApiCaller::Info>, void*>*)(param_1 + 7,*plVar2);
  (*(code *)PTR__ZN9Framework10CFiberUnitD1Ev_02c90ac0)(param_1);
  return;
}

// ==== FakeApiCaller::~FakeApiCaller()
// vaddr 0x148adf8 | ghidra 0x158adf8 | size 128 | symbol _ZN13FakeApiCallerD0Ev | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCallerD0Ev(long *param_1)

{
  undefined *puVar1;
  long *plVar2;
  
  puVar1 = PTR__ZTV13FakeApiCaller_02cbd4b8 + 0x10;
  param_1[1] = (long)(PTR__ZTV13FakeApiCaller_02cbd4b8 + 0x700);
  *param_1 = (long)puVar1;
  plVar2 = param_1 + 9;
  std::__ndk1::__tree<std::__ndk1::__value_type<Aska::Yayoi::GameRPC::GameProtocol::FunctionID, FakeApiCaller::Info>, std::__ndk1::__map_value_compare<Aska::Yayoi::GameRPC::GameProtocol::FunctionID, std::__ndk1::__value_type<Aska::Yayoi::GameRPC::GameProtocol::FunctionID, FakeApiCaller::Info>, std::__ndk1::less<Aska::Yayoi::GameRPC::GameProtocol::FunctionID>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<Aska::Yayoi::GameRPC::GameProtocol::FunctionID, FakeApiCaller::Info>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<Aska::Yayoi::GameRPC::GameProtocol::FunctionID, FakeApiCaller::Info>, void*>*)(param_1 + 8,*plVar2);
  param_1[8] = (long)plVar2;
  param_1[10] = 0;
  *plVar2 = 0;
  CApiNotify::~CApiNotify()(param_1 + 0xc);
  std::__ndk1::__tree<std::__ndk1::__value_type<Aska::Yayoi::GameRPC::GameProtocol::FunctionID, FakeApiCaller::Info>, std::__ndk1::__map_value_compare<Aska::Yayoi::GameRPC::GameProtocol::FunctionID, std::__ndk1::__value_type<Aska::Yayoi::GameRPC::GameProtocol::FunctionID, FakeApiCaller::Info>, std::__ndk1::less<Aska::Yayoi::GameRPC::GameProtocol::FunctionID>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<Aska::Yayoi::GameRPC::GameProtocol::FunctionID, FakeApiCaller::Info>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<Aska::Yayoi::GameRPC::GameProtocol::FunctionID, FakeApiCaller::Info>, void*>*)(param_1 + 8,*plVar2);
  Framework::CFiberUnit::~CFiberUnit()(param_1 + 1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== non-virtual thunk to FakeApiCaller::~FakeApiCaller()
// vaddr 0x148ae78 | ghidra 0x158ae78 | size 128 | symbol _ZThn8_N13FakeApiCallerD0Ev | lib libSOA-3.7.0.so | 2026-10-09
void _ZThn8_N13FakeApiCallerD0Ev(long *param_1)

{
  undefined *puVar1;
  long *plVar2;
  
  puVar1 = PTR__ZTV13FakeApiCaller_02cbd4b8 + 0x10;
  *param_1 = (long)(PTR__ZTV13FakeApiCaller_02cbd4b8 + 0x700);
  param_1[-1] = (long)puVar1;
  plVar2 = param_1 + 8;
  std::__ndk1::__tree<std::__ndk1::__value_type<Aska::Yayoi::GameRPC::GameProtocol::FunctionID, FakeApiCaller::Info>, std::__ndk1::__map_value_compare<Aska::Yayoi::GameRPC::GameProtocol::FunctionID, std::__ndk1::__value_type<Aska::Yayoi::GameRPC::GameProtocol::FunctionID, FakeApiCaller::Info>, std::__ndk1::less<Aska::Yayoi::GameRPC::GameProtocol::FunctionID>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<Aska::Yayoi::GameRPC::GameProtocol::FunctionID, FakeApiCaller::Info>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<Aska::Yayoi::GameRPC::GameProtocol::FunctionID, FakeApiCaller::Info>, void*>*)(param_1 + 7,*plVar2);
  param_1[7] = (long)plVar2;
  param_1[9] = 0;
  *plVar2 = 0;
  CApiNotify::~CApiNotify()(param_1 + 0xb);
  std::__ndk1::__tree<std::__ndk1::__value_type<Aska::Yayoi::GameRPC::GameProtocol::FunctionID, FakeApiCaller::Info>, std::__ndk1::__map_value_compare<Aska::Yayoi::GameRPC::GameProtocol::FunctionID, std::__ndk1::__value_type<Aska::Yayoi::GameRPC::GameProtocol::FunctionID, FakeApiCaller::Info>, std::__ndk1::less<Aska::Yayoi::GameRPC::GameProtocol::FunctionID>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<Aska::Yayoi::GameRPC::GameProtocol::FunctionID, FakeApiCaller::Info>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<Aska::Yayoi::GameRPC::GameProtocol::FunctionID, FakeApiCaller::Info>, void*>*)(param_1 + 7,*plVar2);
  Framework::CFiberUnit::~CFiberUnit()(param_1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1 + -1);
  return;
}

// ==== FakeApiCaller::Initialize()
// vaddr 0x148aef8 | ghidra 0x158aef8 | size 12 | symbol _ZN13FakeApiCaller10InitializeEv | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller10InitializeEv(undefined8 *param_1)

{
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::Release()
// vaddr 0x148af04 | ghidra 0x158af04 | size 36 | symbol _ZN13FakeApiCaller7ReleaseEv | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller7ReleaseEv(long param_1)

{
  std::__ndk1::__tree<std::__ndk1::__value_type<Aska::Yayoi::GameRPC::GameProtocol::FunctionID, FakeApiCaller::Info>, std::__ndk1::__map_value_compare<Aska::Yayoi::GameRPC::GameProtocol::FunctionID, std::__ndk1::__value_type<Aska::Yayoi::GameRPC::GameProtocol::FunctionID, FakeApiCaller::Info>, std::__ndk1::less<Aska::Yayoi::GameRPC::GameProtocol::FunctionID>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<Aska::Yayoi::GameRPC::GameProtocol::FunctionID, FakeApiCaller::Info>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<Aska::Yayoi::GameRPC::GameProtocol::FunctionID, FakeApiCaller::Info>, void*>*)(param_1 + 0x40,*(undefined8 *)(param_1 + 0x48));
  *(undefined8 **)(param_1 + 0x40) = (undefined8 *)(param_1 + 0x48);
  *(undefined8 *)(param_1 + 0x48) = 0;
  *(undefined8 *)(param_1 + 0x50) = 0;
  return;
}

// ==== FakeApiCaller::Progress()
// vaddr 0x148af28 | ghidra 0x158af28 | size 448 | symbol _ZN13FakeApiCaller8ProgressEv | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller8ProgressEv(long param_1)

{
  undefined *puVar1;
  bool bVar2;
  long lVar3;
  ulong uVar4;
  long lVar5;
  long *plVar6;
  long *plVar7;
  undefined1 auStack_78 [12];
  undefined4 uStack_6c;
  undefined8 uStack_68;
  
  puVar1 = PTR__ZN9Framework10TSingletonI20CGameResourceManagerE11m_pInstanceE_02cc2018;
  plVar7 = *(long **)(param_1 + 0x40);
  do {
    while( true ) {
      if (plVar7 == (long *)(param_1 + 0x48)) {
        return;
      }
      if (*(int *)((long)plVar7 + 0x34) != 1) break;
      lVar3 = *(long *)puVar1;
      if (lVar3 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
        lVar3 = *(long *)puVar1;
      }
      uVar4 = CGameResourceManager::IsLoading() const(lVar3);
      if ((uVar4 & 1) != 0) goto code_r0x0158b018;
      CGameResourceManager::Lock()(lVar3);
      if ((*(byte *)(plVar7 + 7) & 1) == 0) {
        lVar5 = (long)plVar7 + 0x39;
      }
      else {
        lVar5 = plVar7[9];
      }
      plVar6 = (long *)CGameResourceManager::crResourceElementDirectFile(char const*) const(lVar3,lVar5);
      uStack_6c = Framework::CFileLoader::Size() const();
      uStack_68 = (**(code **)(*plVar6 + 0x50))(plVar6);
      (**(code **)(*(long *)plVar7[0xe] + 0x30))
                (auStack_78,(long *)plVar7[0xe],&uStack_68,&uStack_6c);
      CGameResourceManager::Unlock()(lVar3);
      if ((*(byte *)(plVar7 + 7) & 1) == 0) {
        lVar5 = (long)plVar7 + 0x39;
      }
      else {
        lVar5 = plVar7[9];
      }
      CGameResourceManager::RemoveDirectFile(char const*)(lVar3,lVar5);
      *(undefined4 *)((long)plVar7 + 0x34) = 2;
      plVar6 = (long *)plVar7[1];
      if ((long *)plVar7[1] != (long *)0x0) goto code_r0x0158b020;
code_r0x0158b0a8:
      do {
        plVar6 = (long *)plVar7[2];
        bVar2 = (long *)*plVar6 != plVar7;
        plVar7 = plVar6;
      } while (bVar2);
    }
    if (*(int *)((long)plVar7 + 0x34) == 0) {
      lVar3 = *(long *)puVar1;
      if (lVar3 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
        lVar3 = *(long *)puVar1;
      }
      if ((*(byte *)(plVar7 + 7) & 1) == 0) {
        lVar5 = (long)plVar7 + 0x39;
      }
      else {
        lVar5 = plVar7[9];
      }
      CGameResourceManager::AddDirectFile(unsigned int, char const*, unsigned int, bool, CGameResourceManager::iPriorityMode)(lVar3,1,lVar5,0,0,0);
      *(undefined4 *)((long)plVar7 + 0x34) = 1;
    }
code_r0x0158b018:
    plVar6 = (long *)plVar7[1];
    if ((long *)plVar7[1] == (long *)0x0) goto code_r0x0158b0a8;
code_r0x0158b020:
    do {
      plVar7 = plVar6;
      plVar6 = (long *)*plVar7;
    } while ((long *)*plVar7 != (long *)0x0);
  } while( true );
}

// ==== non-virtual thunk to FakeApiCaller::Progress()
// vaddr 0x148b0e8 | ghidra 0x158b0e8 | size 8 | symbol _ZThn8_N13FakeApiCaller8ProgressEv | lib libSOA-3.7.0.so | 2026-10-09
void _ZThn8_N13FakeApiCaller8ProgressEv(long param_1)

{
  (*(code *)PTR__ZN13FakeApiCaller8ProgressEv_02cb4358)(param_1 + -8);
  return;
}

// ==== FakeApiCaller::IsRequesting(Aska::Yayoi::GameRPC::GameProtocol::FunctionID) const
// vaddr 0x148b0f0 | ghidra 0x158b0f0 | size 136 | symbol _ZNK13FakeApiCaller12IsRequestingEN4Aska5Yayoi7GameRPC12GameProtocol10FunctionIDE | lib libSOA-3.7.0.so | 2026-10-09
bool _ZNK13FakeApiCaller12IsRequestingEN4Aska5Yayoi7GameRPC12GameProtocol10FunctionIDE
               (long param_1,uint param_2)

{
  long *plVar1;
  long *plVar2;
  bool bVar3;
  long *plVar4;
  long *plVar5;
  long *plVar6;
  
  plVar4 = (long *)(param_1 + 0x48);
  plVar2 = (long *)*plVar4;
  plVar5 = plVar4;
  if ((long *)*plVar4 == (long *)0x0) {
    return true;
  }
  do {
    while (plVar6 = plVar2, param_2 <= *(uint *)(plVar6 + 4)) {
      plVar2 = (long *)*plVar6;
      plVar5 = plVar6;
      if ((long *)*plVar6 == (long *)0x0) goto code_r0x0158b12c;
    }
    plVar1 = plVar6 + 1;
    plVar6 = plVar5;
    plVar2 = (long *)*plVar1;
  } while ((long *)*plVar1 != (long *)0x0);
code_r0x0158b12c:
  if (plVar6 == plVar4) {
    return true;
  }
  bVar3 = true;
  if ((*(uint *)(plVar6 + 4) <= param_2) && (plVar6 != plVar4)) {
    bVar3 = *(int *)((long)plVar6 + 0x34) != 2;
  }
  return bVar3;
}

// ==== FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)
// vaddr 0x148b178 | ghidra 0x158b178 | size 568 | symbol _ZN13FakeApiCaller12AddLocalFileEN4Aska5Yayoi7GameRPC12GameProtocol10FunctionIDEPKcNSt6__ndk18functionIFNS0_6StatusEPaRjEEE | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller12AddLocalFileEN4Aska5Yayoi7GameRPC12GameProtocol10FunctionIDEPKcNSt6__ndk18functionIFNS0_6StatusEPaRjEEE
               (long param_1,uint param_2,undefined8 param_3,long *param_4)

{
  long *plVar1;
  long *plVar2;
  ulong uVar3;
  long *plVar4;
  long *plVar5;
  code *pcVar6;
  long *plVar7;
  ulong uVar8;
  ulong uVar9;
  long alStack_f0 [4];
  long *plStack_d0;
  ulong uStack_b8;
  ulong uStack_b0;
  ulong uStack_a8;
  undefined1 auStack_a0 [8];
  byte bStack_98;
  undefined8 uStack_88;
  long alStack_80 [4];
  long *plStack_60;
  uint uStack_44;
  
  plVar5 = (long *)(param_1 + 0x48);
  plVar4 = (long *)*plVar5;
  plVar2 = plVar5;
  if ((long *)*plVar5 != (long *)0x0) {
    do {
      while (plVar7 = plVar4, *(uint *)(plVar7 + 4) < param_2) {
        plVar1 = plVar7 + 1;
        plVar7 = plVar2;
        plVar4 = (long *)*plVar1;
        if ((long *)*plVar1 == (long *)0x0) goto code_r0x0158b1e0;
      }
      plVar4 = (long *)*plVar7;
      plVar2 = plVar7;
    } while ((long *)*plVar7 != (long *)0x0);
code_r0x0158b1e0:
    if (((plVar7 != plVar5) && (*(uint *)(plVar7 + 4) <= param_2)) && (plVar7 != plVar5)) {
      *(undefined4 *)((long)plVar7 + 0x34) = 0;
      return;
    }
  }
  uStack_b0 = 0;
  uStack_a8 = 0;
  uStack_b8 = 0;
  uStack_44 = param_2;
  uVar3 = strlen(param_3);
  if (uVar3 < 0x17) {
    uVar9 = (ulong)&uStack_b8 | 1;
    uStack_b8 = CONCAT71(uStack_b8._1_7_,(char)(uVar3 << 1));
    if (uVar3 != 0) goto code_r0x0158b29c;
  }
  else {
    uVar8 = uVar3 + 0x10 & 0xfffffffffffffff0;
    if (uVar8 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
    }
    uVar9 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar8,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
    if (uVar9 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    }
    uStack_b8 = uVar8 | 1;
    uStack_b0 = uVar3;
    uStack_a8 = uVar9;
code_r0x0158b29c:
    memcpy(uVar9,param_3,uVar3);
  }
  *(undefined1 *)(uVar9 + uVar3) = 0;
  plVar4 = (long *)param_4[4];
  if (plVar4 == (long *)0x0) {
    plStack_d0 = (long *)0x0;
  }
  else if (param_4 == plVar4) {
    plStack_d0 = alStack_f0;
    (**(code **)(*plVar4 + 0x18))(plVar4,alStack_f0);
  }
  else {
    plStack_d0 = (long *)(**(code **)(*plVar4 + 0x10))();
  }
  FakeApiCaller::Info::Info(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, string const&, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(auStack_a0,param_2,&uStack_b8,alStack_f0);
  std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<Aska::Yayoi::GameRPC::GameProtocol::FunctionID, FakeApiCaller::Info>, std::__ndk1::__tree_node<std::__ndk1::__value_type<Aska::Yayoi::GameRPC::GameProtocol::FunctionID, FakeApiCaller::Info>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<Aska::Yayoi::GameRPC::GameProtocol::FunctionID, FakeApiCaller::Info>, std::__ndk1::__map_value_compare<Aska::Yayoi::GameRPC::GameProtocol::FunctionID, std::__ndk1::__value_type<Aska::Yayoi::GameRPC::GameProtocol::FunctionID, FakeApiCaller::Info>, std::__ndk1::less<Aska::Yayoi::GameRPC::GameProtocol::FunctionID>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<Aska::Yayoi::GameRPC::GameProtocol::FunctionID, FakeApiCaller::Info>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<Aska::Yayoi::GameRPC::GameProtocol::FunctionID, Aska::Yayoi::GameRPC::GameProtocol::FunctionID&, FakeApiCaller::Info>(Aska::Yayoi::GameRPC::GameProtocol::FunctionID const&, Aska::Yayoi::GameRPC::GameProtocol::FunctionID&, FakeApiCaller::Info&&)(param_1 + 0x40,&uStack_44,&uStack_44,auStack_a0);
  if (alStack_80 == plStack_60) {
    pcVar6 = *(code **)(*plStack_60 + 0x20);
code_r0x0158b348:
    (*pcVar6)();
  }
  else if (plStack_60 != (long *)0x0) {
    pcVar6 = *(code **)(*plStack_60 + 0x28);
    goto code_r0x0158b348;
  }
  if ((bStack_98 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_88);
  }
  if (alStack_f0 == plStack_d0) {
    pcVar6 = *(code **)(*plStack_d0 + 0x20);
  }
  else {
    if (plStack_d0 == (long *)0x0) goto code_r0x0158b388;
    pcVar6 = *(code **)(*plStack_d0 + 0x28);
  }
  (*pcVar6)();
code_r0x0158b388:
  if ((uStack_b8 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_a8);
  }
  return;
}

// ==== FakeApiCaller::Info::Info(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > const&, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)
// vaddr 0x148b3b0 | ghidra 0x158b3b0 | size 328 | symbol _ZN13FakeApiCaller4InfoC2EN4Aska5Yayoi7GameRPC12GameProtocol10FunctionIDERKNSt6__ndk112basic_stringIcNS6_11char_traitsIcEEN9Framework13CSTLAllocatorIcNSA_22CSTLStringAllocatorInfEEEEENS6_8functionIFNS1_6StatusEPaRjEEE | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller4InfoC2EN4Aska5Yayoi7GameRPC12GameProtocol10FunctionIDERKNSt6__ndk112basic_stringIcNS6_11char_traitsIcEEN9Framework13CSTLAllocatorIcNSA_22CSTLStringAllocatorInfEEEEENS6_8functionIFNS1_6StatusEPaRjEEE
               (undefined4 *param_1,undefined4 param_2,byte *param_3,long *param_4)

{
  ulong uVar1;
  long *plVar2;
  undefined8 uVar3;
  long lVar4;
  ulong uVar5;
  
  *param_1 = param_2;
  param_1[7] = 0;
  *(undefined8 *)(param_1 + 5) = 0;
  *(undefined8 *)(param_1 + 3) = 0;
  *(undefined8 *)(param_1 + 1) = 0;
  if ((*param_3 & 1) == 0) {
    *(undefined8 *)(param_1 + 6) = *(undefined8 *)(param_3 + 0x10);
    uVar3 = *(undefined8 *)param_3;
    *(undefined8 *)(param_1 + 4) = *(undefined8 *)(param_3 + 8);
    *(undefined8 *)(param_1 + 2) = uVar3;
    plVar2 = (long *)param_4[4];
    goto joined_r0x0158b4b4;
  }
  uVar1 = *(ulong *)(param_3 + 8);
  uVar3 = *(undefined8 *)(param_3 + 0x10);
  if (uVar1 < 0x17) {
    lVar4 = (long)param_1 + 9;
    *(char *)(param_1 + 2) = (char)(uVar1 << 1);
    if (uVar1 != 0) goto code_r0x0158b49c;
  }
  else {
    uVar5 = uVar1 + 0x10 & 0xfffffffffffffff0;
    if (uVar5 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
    }
    lVar4 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar5,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
    if (lVar4 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    }
    *(ulong *)(param_1 + 4) = uVar1;
    *(long *)(param_1 + 6) = lVar4;
    *(ulong *)(param_1 + 2) = uVar5 | 1;
code_r0x0158b49c:
    memcpy(lVar4,uVar3,uVar1);
  }
  *(undefined1 *)(lVar4 + uVar1) = 0;
  plVar2 = (long *)param_4[4];
joined_r0x0158b4b4:
  if (plVar2 == (long *)0x0) {
    *(undefined8 *)(param_1 + 0x10) = 0;
  }
  else {
    if (param_4 == plVar2) {
      *(undefined4 **)(param_1 + 0x10) = param_1 + 8;
                    /* WARNING: Could not recover jumptable at 0x0158b4f4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (**(code **)(*(long *)param_4[4] + 0x18))();
      return;
    }
    uVar3 = (**(code **)(*plVar2 + 0x10))();
    *(undefined8 *)(param_1 + 0x10) = uVar3;
  }
  return;
}

// ==== FakeApiCaller::Login()
// vaddr 0x148b4f8 | ghidra 0x158b4f8 | size 128 | symbol _ZN13FakeApiCaller5LoginEv | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller5LoginEv(undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02ac35f0;
  uStack_48 = param_2;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0xa01c67ef,&UNK_028155e0/*"FakeApi/player_get.msgp"*/,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar1 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x0158b560;
    pcVar1 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158b560:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::SimpleLogin()
// vaddr 0x148b578 | ghidra 0x158b578 | size 128 | symbol _ZN13FakeApiCaller11SimpleLoginEv | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller11SimpleLoginEv(undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02ac3688;
  uStack_48 = param_2;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0xa01c67ef,&UNK_028155e0/*"FakeApi/player_get.msgp"*/,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar1 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x0158b5e0;
    pcVar1 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158b5e0:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::CreatePlayer(signed char const*, signed char const*)
// vaddr 0x148b5f8 | ghidra 0x158b5f8 | size 128 | symbol _ZN13FakeApiCaller12CreatePlayerEPKaS1_ | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller12CreatePlayerEPKaS1_(undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02ac3708;
  uStack_48 = param_2;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0xe3e463ad,&UNK_028155e0/*"FakeApi/player_get.msgp"*/,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar1 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x0158b660;
    pcVar1 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158b660:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::GetPlayer()
// vaddr 0x148b678 | ghidra 0x158b678 | size 128 | symbol _ZN13FakeApiCaller9GetPlayerEv | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller9GetPlayerEv(undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02ac3788;
  uStack_48 = param_2;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0x9a056905,&UNK_028155e0/*"FakeApi/player_get.msgp"*/,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar1 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x0158b6e0;
    pcVar1 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158b6e0:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::GetPlayMission()
// vaddr 0x148b6f8 | ghidra 0x158b6f8 | size 128 | symbol _ZN13FakeApiCaller14GetPlayMissionEv | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller14GetPlayMissionEv(undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02ac3808;
  uStack_48 = param_2;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0x7c1b7a1b,&UNK_028155e0/*"FakeApi/player_get.msgp"*/,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar1 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x0158b760;
    pcVar1 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158b760:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::SearchPlayer(signed char const*)
// vaddr 0x148b778 | ghidra 0x158b778 | size 128 | symbol _ZN13FakeApiCaller12SearchPlayerEPKa | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller12SearchPlayerEPKa(undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02ac3888;
  uStack_48 = param_2;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0x5e598152,&UNK_028155f8/*"FakeApi/update_name.msgp"*/,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar1 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x0158b7e0;
    pcVar1 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158b7e0:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::UpdatePlayerName(signed char const*)
// vaddr 0x148b7f8 | ghidra 0x158b7f8 | size 128 | symbol _ZN13FakeApiCaller16UpdatePlayerNameEPKa | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller16UpdatePlayerNameEPKa(undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02ac3908;
  uStack_48 = param_2;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0xe8e5c4da,&UNK_028155f8/*"FakeApi/update_name.msgp"*/,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar1 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x0158b860;
    pcVar1 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158b860:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::UpdateKiyakuVersion(signed char const*)
// vaddr 0x148b878 | ghidra 0x158b878 | size 128 | symbol _ZN13FakeApiCaller19UpdateKiyakuVersionEPKa | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller19UpdateKiyakuVersionEPKa(undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02ac3988;
  uStack_48 = param_2;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0xe5af488c,&UNK_02815611/*"FakeApi/update_kiyaku_version.msgp"*/,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar1 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x0158b8e0;
    pcVar1 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158b8e0:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::MissionStart(unsigned int, unsigned int, unsigned int, unsigned long, unsigned int, unsigned long, unsigned int)
// vaddr 0x148b8f8 | ghidra 0x158b8f8 | size 128 | symbol _ZN13FakeApiCaller12MissionStartEjjjmjmj | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller12MissionStartEjjjmjmj(undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02ac3a08;
  uStack_48 = param_2;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0xb7c62bc2,&UNK_02815634/*"FakeApi/mission_start.msgp"*/,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar1 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x0158b960;
    pcVar1 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158b960:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::MissionRestart()
// vaddr 0x148b978 | ghidra 0x158b978 | size 128 | symbol _ZN13FakeApiCaller14MissionRestartEv | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller14MissionRestartEv(undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02ac3a88;
  uStack_48 = param_2;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0x1f96f310,&UNK_02815634/*"FakeApi/mission_start.msgp"*/,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar1 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x0158b9e0;
    pcVar1 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158b9e0:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::MultiMissionRestart()
// vaddr 0x148b9f8 | ghidra 0x158b9f8 | size 128 | symbol _ZN13FakeApiCaller19MultiMissionRestartEv | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller19MultiMissionRestartEv(undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02ac3b08;
  uStack_48 = param_2;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0x8c788f39,&UNK_02815634/*"FakeApi/mission_start.msgp"*/,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar1 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x0158ba60;
    pcVar1 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158ba60:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::TrainingMissionStart(unsigned int, unsigned int, unsigned long)
// vaddr 0x148ba78 | ghidra 0x158ba78 | size 128 | symbol _ZN13FakeApiCaller20TrainingMissionStartEjjm | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller20TrainingMissionStartEjjm(undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02ac3b88;
  uStack_48 = param_2;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0xa16fd90,&UNK_02815634/*"FakeApi/mission_start.msgp"*/,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar1 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x0158bae0;
    pcVar1 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158bae0:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::MissionEnd(unsigned int, unsigned int)
// vaddr 0x148baf8 | ghidra 0x158baf8 | size 128 | symbol _ZN13FakeApiCaller10MissionEndEjj | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller10MissionEndEjj(undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02ac3c08;
  uStack_48 = param_2;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0x8312a64c,&UNK_0281564f/*"FakeApi/mission_end.msgp"*/,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar1 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x0158bb60;
    pcVar1 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158bb60:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::MissionTalk(unsigned int, unsigned int, unsigned int, unsigned char)
// vaddr 0x148bb78 | ghidra 0x158bb78 | size 128 | symbol _ZN13FakeApiCaller11MissionTalkEjjjh | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller11MissionTalkEjjjh(undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02ac3c88;
  uStack_48 = param_2;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0x816dc8b4,&UNK_028155e0/*"FakeApi/player_get.msgp"*/,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar1 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x0158bbe0;
    pcVar1 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158bbe0:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::MissionFailed(unsigned int, unsigned int)
// vaddr 0x148bbf8 | ghidra 0x158bbf8 | size 128 | symbol _ZN13FakeApiCaller13MissionFailedEjj | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller13MissionFailedEjj(undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02ac3d08;
  uStack_48 = param_2;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0x479604f6,&UNK_028155e0/*"FakeApi/player_get.msgp"*/,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar1 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x0158bc60;
    pcVar1 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158bc60:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::BoostCharacter(unsigned long, unsigned int, unsigned int)
// vaddr 0x148bc78 | ghidra 0x158bc78 | size 128 | symbol _ZN13FakeApiCaller14BoostCharacterEmjj | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller14BoostCharacterEmjj(undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02ac3d88;
  uStack_48 = param_2;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0xe5a04db6,&UNK_02815668/*"FakeApi/boost_character.msgp"*/,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar1 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x0158bce0;
    pcVar1 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158bce0:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::EvolutionCharacter(unsigned long)
// vaddr 0x148bcf8 | ghidra 0x158bcf8 | size 128 | symbol _ZN13FakeApiCaller18EvolutionCharacterEm | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller18EvolutionCharacterEm(undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02ac3e08;
  uStack_48 = param_2;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0x990921b6,&UNK_02815685/*"FakeApi/evolution.msgp"*/,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar1 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x0158bd60;
    pcVar1 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158bd60:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::LimitBreakCharacter(unsigned long, unsigned int)
// vaddr 0x148bd78 | ghidra 0x158bd78 | size 128 | symbol _ZN13FakeApiCaller19LimitBreakCharacterEmj | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller19LimitBreakCharacterEmj(undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02ac3e88;
  uStack_48 = param_2;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0x78972d03,&UNK_0281569c/*"FakeApi/limit_break.msgp"*/,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar1 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x0158bde0;
    pcVar1 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158bde0:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::LimitBreakCharacter_Legacy(unsigned long, unsigned int)
// vaddr 0x148bdf8 | ghidra 0x158bdf8 | size 128 | symbol _ZN13FakeApiCaller26LimitBreakCharacter_LegacyEmj | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller26LimitBreakCharacter_LegacyEmj(undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02ac3f08;
  uStack_48 = param_2;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0x78972d03,&UNK_0281569c/*"FakeApi/limit_break.msgp"*/,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar1 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x0158be60;
    pcVar1 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158be60:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::AddStatusCharacter(unsigned long, unsigned int, unsigned int)
// vaddr 0x148be78 | ghidra 0x158be78 | size 128 | symbol _ZN13FakeApiCaller18AddStatusCharacterEmjj | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller18AddStatusCharacterEmjj(undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02ac3f88;
  uStack_48 = param_2;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0x74e09417,&UNK_02815668/*"FakeApi/boost_character.msgp"*/,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar1 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x0158bee0;
    pcVar1 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158bee0:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::ItemCompose(unsigned long, unsigned int, ...)
// vaddr 0x148bef8 | ghidra 0x158bef8 | size 156 | symbol _ZN13FakeApiCaller11ItemComposeEmjz | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller11ItemComposeEmjz(undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  undefined **ppuStack_30;
  
  puStack_50 = &UNK_02ac4008;
  uStack_48 = param_2;
  ppuStack_30 = &puStack_50;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,&UNK_02a5cd1d,&UNK_028156b5/*"FakeApi/compose.msgp"*/,&puStack_50);
  if (&puStack_50 == ppuStack_30) {
    pcVar1 = *(code **)(*ppuStack_30 + 0x20);
  }
  else {
    if (ppuStack_30 == (undefined **)0x0) goto code_r0x0158bf7c;
    pcVar1 = *(code **)(*ppuStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158bf7c:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::ItemComposeArray(unsigned long, Framework::CSTLVector<unsigned long> const&)
// vaddr 0x148bf94 | ghidra 0x158bf94 | size 128 | symbol _ZN13FakeApiCaller16ItemComposeArrayEmRKN9Framework10CSTLVectorImEE | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller16ItemComposeArrayEmRKN9Framework10CSTLVectorImEE
               (undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02ac4088;
  uStack_48 = param_2;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,&UNK_02a5cd1d,&UNK_028156b5/*"FakeApi/compose.msgp"*/,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar1 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x0158bffc;
    pcVar1 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158bffc:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::ItemGradeUp(unsigned long, unsigned int, ...)
// vaddr 0x148c014 | ghidra 0x158c014 | size 156 | symbol _ZN13FakeApiCaller11ItemGradeUpEmjz | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller11ItemGradeUpEmjz(undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  undefined **ppuStack_30;
  
  puStack_50 = &UNK_02ac4108;
  uStack_48 = param_2;
  ppuStack_30 = &puStack_50;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0x8952aa02,&UNK_028156ca/*"FakeApi/grade_up.msgp"*/,&puStack_50);
  if (&puStack_50 == ppuStack_30) {
    pcVar1 = *(code **)(*ppuStack_30 + 0x20);
  }
  else {
    if (ppuStack_30 == (undefined **)0x0) goto code_r0x0158c098;
    pcVar1 = *(code **)(*ppuStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158c098:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::ItemGradeUpArray(unsigned long, Framework::CSTLVector<unsigned long> const&)
// vaddr 0x148c0b0 | ghidra 0x158c0b0 | size 128 | symbol _ZN13FakeApiCaller16ItemGradeUpArrayEmRKN9Framework10CSTLVectorImEE | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller16ItemGradeUpArrayEmRKN9Framework10CSTLVectorImEE
               (undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02ac4188;
  uStack_48 = param_2;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0x8952aa02,&UNK_028156ca/*"FakeApi/grade_up.msgp"*/,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar1 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x0158c118;
    pcVar1 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158c118:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::UpdateParty(unsigned int, unsigned long, unsigned long, unsigned long)
// vaddr 0x148c130 | ghidra 0x158c130 | size 128 | symbol _ZN13FakeApiCaller11UpdatePartyEjmmm | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller11UpdatePartyEjmmm(undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02ac4208;
  uStack_48 = param_2;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0xef02dd83,&UNK_028156e0/*"FakeApi/party_update.msgp"*/,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar1 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x0158c198;
    pcVar1 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158c198:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::UpdateSupport(unsigned long)
// vaddr 0x148c1b0 | ghidra 0x158c1b0 | size 128 | symbol _ZN13FakeApiCaller13UpdateSupportEm | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller13UpdateSupportEm(undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02ac4288;
  uStack_48 = param_2;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0x3e77af96,&UNK_028156fa/*"FakeApi/update_support.msgp"*/,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar1 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x0158c218;
    pcVar1 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158c218:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::EquipWeapon(unsigned long, unsigned long)
// vaddr 0x148c230 | ghidra 0x158c230 | size 128 | symbol _ZN13FakeApiCaller11EquipWeaponEmm | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller11EquipWeaponEmm(undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02ac4308;
  uStack_48 = param_2;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0x1f3c9eca,&UNK_02815716/*"FakeApi/equip_weapon.msgp"*/,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar1 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x0158c298;
    pcVar1 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158c298:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::EquipAccessory(unsigned long, unsigned long)
// vaddr 0x148c2b0 | ghidra 0x158c2b0 | size 128 | symbol _ZN13FakeApiCaller14EquipAccessoryEmm | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller14EquipAccessoryEmm(undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02ac4388;
  uStack_48 = param_2;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0x1f3c9eca,&UNK_02815730/*"FakeApi/equip_accessory.msgp"*/,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar1 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x0158c318;
    pcVar1 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158c318:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::EquipSkill(unsigned long, unsigned int, unsigned int, unsigned int)
// vaddr 0x148c330 | ghidra 0x158c330 | size 128 | symbol _ZN13FakeApiCaller10EquipSkillEmjjj | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller10EquipSkillEmjjj(undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02ac4408;
  uStack_48 = param_2;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0x4656d729,&UNK_0281574d/*"FakeApi/equip_skill.msgp"*/,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar1 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x0158c398;
    pcVar1 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158c398:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::EquipAuto(unsigned long)
// vaddr 0x148c3b0 | ghidra 0x158c3b0 | size 128 | symbol _ZN13FakeApiCaller9EquipAutoEm | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller9EquipAutoEm(undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02ac4488;
  uStack_48 = param_2;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0x7827ff6a,&UNK_02815766/*"FakeApi/equip_auto.msgp"*/,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar1 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x0158c418;
    pcVar1 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158c418:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::GetPresent(unsigned long, ...)
// vaddr 0x148c430 | ghidra 0x158c430 | size 156 | symbol _ZN13FakeApiCaller10GetPresentEmz | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller10GetPresentEmz(undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  undefined **ppuStack_30;
  
  puStack_50 = &UNK_02ac4508;
  uStack_48 = param_2;
  ppuStack_30 = &puStack_50;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0x4072d7e1,&UNK_0281577e/*"FakeApi/present_get_item.msgp"*/,&puStack_50);
  if (&puStack_50 == ppuStack_30) {
    pcVar1 = *(code **)(*ppuStack_30 + 0x20);
  }
  else {
    if (ppuStack_30 == (undefined **)0x0) goto code_r0x0158c4b4;
    pcVar1 = *(code **)(*ppuStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158c4b4:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::GetPresentArray(Framework::CSTLVector<unsigned long> const&)
// vaddr 0x148c4cc | ghidra 0x158c4cc | size 128 | symbol _ZN13FakeApiCaller15GetPresentArrayERKN9Framework10CSTLVectorImEE | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller15GetPresentArrayERKN9Framework10CSTLVectorImEE
               (undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02ac4588;
  uStack_48 = param_2;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0x4072d7e1,&UNK_0281577e/*"FakeApi/present_get_item.msgp"*/,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar1 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x0158c534;
    pcVar1 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158c534:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::PresentList()
// vaddr 0x148c54c | ghidra 0x158c54c | size 128 | symbol _ZN13FakeApiCaller11PresentListEv | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller11PresentListEv(undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02ac4608;
  uStack_48 = param_2;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0xfa782a45,&UNK_0281579c/*"FakeApi/present_get_all.msgp"*/,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar1 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x0158c5b4;
    pcVar1 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158c5b4:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::LockItem(unsigned int, ...)
// vaddr 0x148c5cc | ghidra 0x158c5cc | size 156 | symbol _ZN13FakeApiCaller8LockItemEjz | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller8LockItemEjz(undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  undefined **ppuStack_30;
  
  puStack_50 = &UNK_02ac4688;
  uStack_48 = param_2;
  ppuStack_30 = &puStack_50;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0x88f29383,&UNK_028157b9/*"FakeApi/item_lock.msgp"*/,&puStack_50);
  if (&puStack_50 == ppuStack_30) {
    pcVar1 = *(code **)(*ppuStack_30 + 0x20);
  }
  else {
    if (ppuStack_30 == (undefined **)0x0) goto code_r0x0158c650;
    pcVar1 = *(code **)(*ppuStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158c650:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::LockItemArray(Framework::CSTLVector<unsigned long> const&)
// vaddr 0x148c668 | ghidra 0x158c668 | size 128 | symbol _ZN13FakeApiCaller13LockItemArrayERKN9Framework10CSTLVectorImEE | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller13LockItemArrayERKN9Framework10CSTLVectorImEE
               (undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02ac4708;
  uStack_48 = param_2;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0x88f29383,&UNK_028157b9/*"FakeApi/item_lock.msgp"*/,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar1 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x0158c6d0;
    pcVar1 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158c6d0:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::UnlockItem(unsigned int, ...)
// vaddr 0x148c6e8 | ghidra 0x158c6e8 | size 156 | symbol _ZN13FakeApiCaller10UnlockItemEjz | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller10UnlockItemEjz(undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  undefined **ppuStack_30;
  
  puStack_50 = &UNK_02ac4788;
  uStack_48 = param_2;
  ppuStack_30 = &puStack_50;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0x2f9569e5,&UNK_028157d0/*"FakeApi/item_unlock.msgp"*/,&puStack_50);
  if (&puStack_50 == ppuStack_30) {
    pcVar1 = *(code **)(*ppuStack_30 + 0x20);
  }
  else {
    if (ppuStack_30 == (undefined **)0x0) goto code_r0x0158c76c;
    pcVar1 = *(code **)(*ppuStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158c76c:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::UnlockItemArray(Framework::CSTLVector<unsigned long> const&)
// vaddr 0x148c784 | ghidra 0x158c784 | size 128 | symbol _ZN13FakeApiCaller15UnlockItemArrayERKN9Framework10CSTLVectorImEE | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller15UnlockItemArrayERKN9Framework10CSTLVectorImEE
               (undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02ac4808;
  uStack_48 = param_2;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0x2f9569e5,&UNK_028157d0/*"FakeApi/item_unlock.msgp"*/,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar1 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x0158c7ec;
    pcVar1 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158c7ec:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::ClearNewItem(Framework::CSTLVector<unsigned long> const&)
// vaddr 0x148c804 | ghidra 0x158c804 | size 128 | symbol _ZN13FakeApiCaller12ClearNewItemERKN9Framework10CSTLVectorImEE | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller12ClearNewItemERKN9Framework10CSTLVectorImEE
               (undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02ac4888;
  uStack_48 = param_2;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0xee45f7,&UNK_028157e9/*"FakeApi/sale.msgp"*/,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar1 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x0158c86c;
    pcVar1 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158c86c:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::ClearNewStackItem(Framework::CSTLVector<unsigned int> const&)
// vaddr 0x148c884 | ghidra 0x158c884 | size 128 | symbol _ZN13FakeApiCaller17ClearNewStackItemERKN9Framework10CSTLVectorIjEE | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller17ClearNewStackItemERKN9Framework10CSTLVectorIjEE
               (undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02ac4908;
  uStack_48 = param_2;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0xee45f7,&UNK_028157e9/*"FakeApi/sale.msgp"*/,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar1 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x0158c8ec;
    pcVar1 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158c8ec:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::ClearNewCharacter(Framework::CSTLVector<unsigned long> const&)
// vaddr 0x148c904 | ghidra 0x158c904 | size 128 | symbol _ZN13FakeApiCaller17ClearNewCharacterERKN9Framework10CSTLVectorImEE | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller17ClearNewCharacterERKN9Framework10CSTLVectorImEE
               (undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02ac4988;
  uStack_48 = param_2;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0xee45f7,&UNK_028157e9/*"FakeApi/sale.msgp"*/,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar1 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x0158c96c;
    pcVar1 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158c96c:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::SellItem(unsigned int, ...)
// vaddr 0x148c984 | ghidra 0x158c984 | size 156 | symbol _ZN13FakeApiCaller8SellItemEjz | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller8SellItemEjz(undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  undefined **ppuStack_30;
  
  puStack_50 = &UNK_02ac4a08;
  uStack_48 = param_2;
  ppuStack_30 = &puStack_50;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0xee45f7,&UNK_028157e9/*"FakeApi/sale.msgp"*/,&puStack_50);
  if (&puStack_50 == ppuStack_30) {
    pcVar1 = *(code **)(*ppuStack_30 + 0x20);
  }
  else {
    if (ppuStack_30 == (undefined **)0x0) goto code_r0x0158ca08;
    pcVar1 = *(code **)(*ppuStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158ca08:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::SellItemArray(Framework::CSTLVector<unsigned long> const&)
// vaddr 0x148ca20 | ghidra 0x158ca20 | size 128 | symbol _ZN13FakeApiCaller13SellItemArrayERKN9Framework10CSTLVectorImEE | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller13SellItemArrayERKN9Framework10CSTLVectorImEE
               (undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02ac4a88;
  uStack_48 = param_2;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0xee45f7,&UNK_028157e9/*"FakeApi/sale.msgp"*/,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar1 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x0158ca88;
    pcVar1 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158ca88:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::SellStackItem(unsigned int, unsigned int)
// vaddr 0x148caa0 | ghidra 0x158caa0 | size 128 | symbol _ZN13FakeApiCaller13SellStackItemEjj | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller13SellStackItemEjj(undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02ac4b08;
  uStack_48 = param_2;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0x445ab956,&UNK_028157fb/*"FakeApi/sale_stock.msgp"*/,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar1 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x0158cb08;
    pcVar1 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158cb08:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::UseHealItem(unsigned int, unsigned int)
// vaddr 0x148cb20 | ghidra 0x158cb20 | size 128 | symbol _ZN13FakeApiCaller11UseHealItemEjj | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller11UseHealItemEjj(undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02ac4b88;
  uStack_48 = param_2;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0xbaeea1ba,&UNK_02815813/*"FakeApi/use_heal.msgp"*/,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar1 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x0158cb88;
    pcVar1 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158cb88:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::UpdateItemStock()
// vaddr 0x148cba0 | ghidra 0x158cba0 | size 128 | symbol _ZN13FakeApiCaller15UpdateItemStockEv | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller15UpdateItemStockEv(undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02ac4c08;
  uStack_48 = param_2;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0xcf39cc5c,&UNK_02815829/*"FakeApi/update_item_stock.msgp"*/,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar1 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x0158cc08;
    pcVar1 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158cc08:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::ExshopExchange(unsigned int, unsigned int)
// vaddr 0x148cc20 | ghidra 0x158cc20 | size 128 | symbol _ZN13FakeApiCaller14ExshopExchangeEjj | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller14ExshopExchangeEjj(undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02ac4c88;
  uStack_48 = param_2;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0x70d0f3ce,&UNK_02815848/*"FakeApi/exshop_exchange.msgp"*/,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar1 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x0158cc88;
    pcVar1 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158cc88:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::ExshopExchangeList()
// vaddr 0x148cca0 | ghidra 0x158cca0 | size 128 | symbol _ZN13FakeApiCaller18ExshopExchangeListEv | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller18ExshopExchangeListEv(undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02ac4d08;
  uStack_48 = param_2;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0x7329eff2,&UNK_02815848/*"FakeApi/exshop_exchange.msgp"*/,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar1 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x0158cd08;
    pcVar1 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158cd08:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::ExItemShop(unsigned int)
// vaddr 0x148cd20 | ghidra 0x158cd20 | size 128 | symbol _ZN13FakeApiCaller10ExItemShopEj | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller10ExItemShopEj(undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02ac4d88;
  uStack_48 = param_2;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0x33d09fb7,&UNK_02815865/*"FakeApi/exitem_shop.msgp"*/,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar1 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x0158cd88;
    pcVar1 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158cd88:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::MaterialCompose(unsigned int, unsigned int)
// vaddr 0x148cda0 | ghidra 0x158cda0 | size 128 | symbol _ZN13FakeApiCaller15MaterialComposeEjj | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller15MaterialComposeEjj(undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02ac4e08;
  uStack_48 = param_2;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0xf9a4ba8c,&UNK_0281587e/*"FakeApi/material_compose.msgp"*/,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar1 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x0158ce08;
    pcVar1 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158ce08:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::StaminaHeal()
// vaddr 0x148ce20 | ghidra 0x158ce20 | size 128 | symbol _ZN13FakeApiCaller11StaminaHealEv | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller11StaminaHealEv(undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02ac4e88;
  uStack_48 = param_2;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0x737fac92,&UNK_0281589c/*"FakeApi/stamina_heal.msgp"*/,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar1 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x0158ce88;
    pcVar1 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158ce88:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::UpdateFollowMax()
// vaddr 0x148cea0 | ghidra 0x158cea0 | size 128 | symbol _ZN13FakeApiCaller15UpdateFollowMaxEv | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller15UpdateFollowMaxEv(undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02ac4f08;
  uStack_48 = param_2;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0x7c2b82bf,&UNK_028158b6/*"FakeApi/update_follow_max.msgp"*/,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar1 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x0158cf08;
    pcVar1 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158cf08:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::GachaOnce(unsigned int, signed char const*)
// vaddr 0x148cf20 | ghidra 0x158cf20 | size 128 | symbol _ZN13FakeApiCaller9GachaOnceEjPKa | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller9GachaOnceEjPKa(undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02ac4f88;
  uStack_48 = param_2;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0x992ccbe5,&UNK_028158d5/*"FakeApi/gacha_once_item.msgp"*/,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar1 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x0158cf88;
    pcVar1 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158cf88:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::Gacha(unsigned int, signed char const*, unsigned int)
// vaddr 0x148cfa0 | ghidra 0x158cfa0 | size 128 | symbol _ZN13FakeApiCaller5GachaEjPKaj | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller5GachaEjPKaj(undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02ac5008;
  uStack_48 = param_2;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0xa0a1940b,&UNK_028158f2/*"FakeApi/gacha_pc.msgp"*/,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar1 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x0158d008;
    pcVar1 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158d008:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::GachaTicket(unsigned int, unsigned int, signed char const*)
// vaddr 0x148d020 | ghidra 0x158d020 | size 128 | symbol _ZN13FakeApiCaller11GachaTicketEjjPKa | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller11GachaTicketEjjPKa(undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02ac5088;
  uStack_48 = param_2;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0xee11c3d3,&UNK_02815908/*"FakeApi/gacha_ticket.msgp"*/,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar1 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x0158d088;
    pcVar1 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158d088:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::BoxGacha(unsigned int, unsigned int)
// vaddr 0x148d0a0 | ghidra 0x158d0a0 | size 128 | symbol _ZN13FakeApiCaller8BoxGachaEjj | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller8BoxGachaEjj(undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02ac5108;
  uStack_48 = param_2;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0x5be25d4b,&UNK_028158f2/*"FakeApi/gacha_pc.msgp"*/,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar1 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x0158d108;
    pcVar1 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158d108:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::ResetBoxGacha(unsigned int)
// vaddr 0x148d120 | ghidra 0x158d120 | size 128 | symbol _ZN13FakeApiCaller13ResetBoxGachaEj | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller13ResetBoxGachaEj(undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02ac5188;
  uStack_48 = param_2;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0xc292cf48,&UNK_028158f2/*"FakeApi/gacha_pc.msgp"*/,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar1 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x0158d188;
    pcVar1 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158d188:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::GetBoxGacha()
// vaddr 0x148d1a0 | ghidra 0x158d1a0 | size 128 | symbol _ZN13FakeApiCaller11GetBoxGachaEv | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller11GetBoxGachaEv(undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02ac5208;
  uStack_48 = param_2;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0xaf250236,&UNK_028158f2/*"FakeApi/gacha_pc.msgp"*/,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar1 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x0158d208;
    pcVar1 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158d208:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::SaleGachaOnce(unsigned int, signed char const*)
// vaddr 0x148d220 | ghidra 0x158d220 | size 128 | symbol _ZN13FakeApiCaller13SaleGachaOnceEjPKa | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller13SaleGachaOnceEjPKa(undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02ac5288;
  uStack_48 = param_2;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0x2d230806,&UNK_028158d5/*"FakeApi/gacha_once_item.msgp"*/,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar1 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x0158d288;
    pcVar1 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158d288:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::SaleGacha(unsigned int, signed char const*)
// vaddr 0x148d2a0 | ghidra 0x158d2a0 | size 128 | symbol _ZN13FakeApiCaller9SaleGachaEjPKa | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller9SaleGachaEjPKa(undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02ac5308;
  uStack_48 = param_2;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0xb164b4c5,&UNK_028158f2/*"FakeApi/gacha_pc.msgp"*/,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar1 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x0158d308;
    pcVar1 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158d308:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::GetGachaRate(unsigned int, signed char const*)
// vaddr 0x148d320 | ghidra 0x158d320 | size 128 | symbol _ZN13FakeApiCaller12GetGachaRateEjPKa | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller12GetGachaRateEjPKa(undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02ac5388;
  uStack_48 = param_2;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0xd6bcb49d,&UNK_028158f2/*"FakeApi/gacha_pc.msgp"*/,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar1 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x0158d388;
    pcVar1 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158d388:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::FollowList()
// vaddr 0x148d3a0 | ghidra 0x158d3a0 | size 128 | symbol _ZN13FakeApiCaller10FollowListEv | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller10FollowListEv(undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02ac5408;
  uStack_48 = param_2;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0x9bddc9d7,&UNK_02815922/*"FakeApi/follow_list.msgp"*/,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar1 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x0158d408;
    pcVar1 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158d408:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::FollowAdd(unsigned int)
// vaddr 0x148d420 | ghidra 0x158d420 | size 128 | symbol _ZN13FakeApiCaller9FollowAddEj | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller9FollowAddEj(undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02ac5488;
  uStack_48 = param_2;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0x2559b5a1,&UNK_0281593b/*"FakeApi/follow_add.msgp"*/,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar1 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x0158d488;
    pcVar1 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158d488:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::FollowRemove(unsigned int)
// vaddr 0x148d4a0 | ghidra 0x158d4a0 | size 128 | symbol _ZN13FakeApiCaller12FollowRemoveEj | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller12FollowRemoveEj(undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02ac5508;
  uStack_48 = param_2;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0x408f02f6,&UNK_02815953/*"FakeApi/follow_remove.msgp"*/,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar1 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x0158d508;
    pcVar1 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158d508:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::Blacklist()
// vaddr 0x148d520 | ghidra 0x158d520 | size 128 | symbol _ZN13FakeApiCaller9BlacklistEv | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller9BlacklistEv(undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02ac5588;
  uStack_48 = param_2;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0x9bddc9d7,&UNK_0281596e/*"FakeApi/blacklist.msgp"*/,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar1 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x0158d588;
    pcVar1 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158d588:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::BlacklistAdd(unsigned int)
// vaddr 0x148d5a0 | ghidra 0x158d5a0 | size 128 | symbol _ZN13FakeApiCaller12BlacklistAddEj | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller12BlacklistAddEj(undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02ac5608;
  uStack_48 = param_2;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0x2559b5a1,&UNK_02815985/*"FakeApi/blacklist_add.msgp"*/,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar1 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x0158d608;
    pcVar1 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158d608:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::BlacklistRemove(unsigned int)
// vaddr 0x148d620 | ghidra 0x158d620 | size 128 | symbol _ZN13FakeApiCaller15BlacklistRemoveEj | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller15BlacklistRemoveEj(undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02ac5688;
  uStack_48 = param_2;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0x408f02f6,&UNK_028159a0/*"FakeApi/blacklist_remove.msgp"*/,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar1 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x0158d688;
    pcVar1 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158d688:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::NeighborRegist(float, float)
// vaddr 0x148d6a0 | ghidra 0x158d6a0 | size 128 | symbol _ZN13FakeApiCaller14NeighborRegistEff | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller14NeighborRegistEff(undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02ac5708;
  uStack_48 = param_2;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0x9a57cfc9,&UNK_028159be/*"FakeApi/__dummy.msgp"*/,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar1 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x0158d708;
    pcVar1 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158d708:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::NeighborList(float, float)
// vaddr 0x148d720 | ghidra 0x158d720 | size 128 | symbol _ZN13FakeApiCaller12NeighborListEff | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller12NeighborListEff(undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02ac5788;
  uStack_48 = param_2;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0x451d30bf,&UNK_028159be/*"FakeApi/__dummy.msgp"*/,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar1 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x0158d788;
    pcVar1 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158d788:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::LocationRegist(float, float)
// vaddr 0x148d7a0 | ghidra 0x158d7a0 | size 128 | symbol _ZN13FakeApiCaller14LocationRegistEff | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller14LocationRegistEff(undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02ac5808;
  uStack_48 = param_2;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0x49898ba4,&UNK_028159be/*"FakeApi/__dummy.msgp"*/,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar1 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x0158d808;
    pcVar1 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158d808:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::AchievementActiveList(unsigned int)
// vaddr 0x148d820 | ghidra 0x158d820 | size 128 | symbol _ZN13FakeApiCaller21AchievementActiveListEj | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller21AchievementActiveListEj(undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02ac5888;
  uStack_48 = param_2;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0xd0b25cb6,&UNK_028159d3/*"FakeApi/achievement_active_list.msgp"*/,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar1 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x0158d888;
    pcVar1 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158d888:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::AchievementReceive(unsigned long)
// vaddr 0x148d8a0 | ghidra 0x158d8a0 | size 128 | symbol _ZN13FakeApiCaller18AchievementReceiveEm | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller18AchievementReceiveEm(undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02ac5908;
  uStack_48 = param_2;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0x47e9dee6,&UNK_028159f8/*"FakeApi/achievement_receive.msgp"*/,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar1 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x0158d908;
    pcVar1 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158d908:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::AchievementListReceive(Framework::CSTLVector<unsigned long> const&)
// vaddr 0x148d920 | ghidra 0x158d920 | size 12 | symbol _ZN13FakeApiCaller22AchievementListReceiveERKN9Framework10CSTLVectorImEE | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller22AchievementListReceiveERKN9Framework10CSTLVectorImEE(undefined8 *param_1)

{
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::AchievementReceiveList()
// vaddr 0x148d92c | ghidra 0x158d92c | size 128 | symbol _ZN13FakeApiCaller22AchievementReceiveListEv | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller22AchievementReceiveListEv(undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02ac5988;
  uStack_48 = param_2;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0xd0b25cb6,&UNK_02815a19/*"FakeApi/achievement_receive_list.msgp"*/,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar1 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x0158d994;
    pcVar1 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158d994:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::UpdateHome(unsigned long)
// vaddr 0x148d9ac | ghidra 0x158d9ac | size 128 | symbol _ZN13FakeApiCaller10UpdateHomeEm | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller10UpdateHomeEm(undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02ac5a08;
  uStack_48 = param_2;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0x46e0807c,&UNK_02815a3f/*"FakeApi/update_home.msgp"*/,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar1 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x0158da14;
    pcVar1 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158da14:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::UpdateTutorial(unsigned long)
// vaddr 0x148da2c | ghidra 0x158da2c | size 128 | symbol _ZN13FakeApiCaller14UpdateTutorialEm | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller14UpdateTutorialEm(undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02ac5a88;
  uStack_48 = param_2;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0x1cf2b3d7,&UNK_02815a3f/*"FakeApi/update_home.msgp"*/,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar1 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x0158da94;
    pcVar1 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158da94:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::NoLoginStart(signed char const*)
// vaddr 0x148daac | ghidra 0x158daac | size 128 | symbol _ZN13FakeApiCaller12NoLoginStartEPKa | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller12NoLoginStartEPKa(undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02ac5b08;
  uStack_48 = param_2;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0x95804837,&UNK_02815a3f/*"FakeApi/update_home.msgp"*/,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar1 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x0158db14;
    pcVar1 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158db14:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::GetServerTime()
// vaddr 0x148db2c | ghidra 0x158db2c | size 128 | symbol _ZN13FakeApiCaller13GetServerTimeEv | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller13GetServerTimeEv(undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02ac5b88;
  uStack_48 = param_2;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0x98b03930,&UNK_02815a3f/*"FakeApi/update_home.msgp"*/,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar1 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x0158db94;
    pcVar1 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158db94:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::CbtCertification(signed char const*)
// vaddr 0x148dbac | ghidra 0x158dbac | size 128 | symbol _ZN13FakeApiCaller16CbtCertificationEPKa | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller16CbtCertificationEPKa(undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02ac5c08;
  uStack_48 = param_2;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0x5f583f50,&UNK_02815a3f/*"FakeApi/update_home.msgp"*/,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar1 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x0158dc14;
    pcVar1 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158dc14:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::SetStampSlot(Framework::CSTLVector<unsigned int> const&)
// vaddr 0x148dc2c | ghidra 0x158dc2c | size 128 | symbol _ZN13FakeApiCaller12SetStampSlotERKN9Framework10CSTLVectorIjEE | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller12SetStampSlotERKN9Framework10CSTLVectorIjEE
               (undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02ac5c88;
  uStack_48 = param_2;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0x58123949,&UNK_028156b5/*"FakeApi/compose.msgp"*/,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar1 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x0158dc94;
    pcVar1 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158dc94:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::SetTitle(unsigned int)
// vaddr 0x148dcac | ghidra 0x158dcac | size 128 | symbol _ZN13FakeApiCaller8SetTitleEj | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller8SetTitleEj(undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02ac5d08;
  uStack_48 = param_2;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0x4332363c,&UNK_028156b5/*"FakeApi/compose.msgp"*/,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar1 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x0158dd14;
    pcVar1 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158dd14:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::UpdateAwakenLevel(unsigned long, unsigned int)
// vaddr 0x148dd2c | ghidra 0x158dd2c | size 128 | symbol _ZN13FakeApiCaller17UpdateAwakenLevelEmj | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller17UpdateAwakenLevelEmj(undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02ac5d88;
  uStack_48 = param_2;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0x2d714808,&UNK_028156b5/*"FakeApi/compose.msgp"*/,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar1 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x0158dd94;
    pcVar1 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158dd94:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::DeepSpaceMissionStart(unsigned int, unsigned int, Framework::CSTLVector<unsigned long> const&)
// vaddr 0x148ddac | ghidra 0x158ddac | size 128 | symbol _ZN13FakeApiCaller21DeepSpaceMissionStartEjjRKN9Framework10CSTLVectorImEE | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller21DeepSpaceMissionStartEjjRKN9Framework10CSTLVectorImEE
               (undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02ac5e08;
  uStack_48 = param_2;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0x63c9927a,&UNK_028156b5/*"FakeApi/compose.msgp"*/,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar1 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x0158de14;
    pcVar1 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158de14:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::DeepSpaceMissionEnd(unsigned int)
// vaddr 0x148de2c | ghidra 0x158de2c | size 128 | symbol _ZN13FakeApiCaller19DeepSpaceMissionEndEj | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller19DeepSpaceMissionEndEj(undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02ac5e88;
  uStack_48 = param_2;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0x140e365b,&UNK_028156b5/*"FakeApi/compose.msgp"*/,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar1 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x0158de94;
    pcVar1 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158de94:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::DeepSpaceMissionEndNow(unsigned int)
// vaddr 0x148deac | ghidra 0x158deac | size 128 | symbol _ZN13FakeApiCaller22DeepSpaceMissionEndNowEj | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller22DeepSpaceMissionEndNowEj(undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02ac5f08;
  uStack_48 = param_2;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0x2df0328c,&UNK_028156b5/*"FakeApi/compose.msgp"*/,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar1 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x0158df14;
    pcVar1 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158df14:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::DeepSpaceAutoMemberSelect(unsigned int, unsigned int)
// vaddr 0x148df2c | ghidra 0x158df2c | size 128 | symbol _ZN13FakeApiCaller25DeepSpaceAutoMemberSelectEjj | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller25DeepSpaceAutoMemberSelectEjj(undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02ac5f88;
  uStack_48 = param_2;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0xed9aae28,&UNK_028156b5/*"FakeApi/compose.msgp"*/,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar1 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x0158df94;
    pcVar1 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158df94:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::SendErrorLog(signed char const*)
// vaddr 0x148dfac | ghidra 0x158dfac | size 128 | symbol _ZN13FakeApiCaller12SendErrorLogEPKa | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller12SendErrorLogEPKa(undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02ac6008;
  uStack_48 = param_2;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0xe5af488c,&UNK_02815a58/*"FakeApi/send_error_log.msgp"*/,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar1 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x0158e014;
    pcVar1 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158e014:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::UseFavorItem(unsigned int, unsigned int, unsigned int)
// vaddr 0x148e02c | ghidra 0x158e02c | size 128 | symbol _ZN13FakeApiCaller12UseFavorItemEjjj | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller12UseFavorItemEjjj(undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02ac6088;
  uStack_48 = param_2;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0x88af959e,&UNK_02815a74/*"FakeApi/use_item.msgp"*/,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar1 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x0158e094;
    pcVar1 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158e094:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::StaminaHealByFavor()
// vaddr 0x148e0ac | ghidra 0x158e0ac | size 128 | symbol _ZN13FakeApiCaller18StaminaHealByFavorEv | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller18StaminaHealByFavorEv(undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02ac6108;
  uStack_48 = param_2;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0x960546a3,&UNK_02815a8a/*"FakeApi/stamina_heal_by_favor.msgp"*/,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar1 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x0158e114;
    pcVar1 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158e114:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::UpdateFavorByTap(unsigned int)
// vaddr 0x148e12c | ghidra 0x158e12c | size 128 | symbol _ZN13FakeApiCaller16UpdateFavorByTapEj | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller16UpdateFavorByTapEj(undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02ac6188;
  uStack_48 = param_2;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0xe06ec7b3,&UNK_02815aad/*"FakeApi/update_favor_by_tap.msgp"*/,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar1 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x0158e194;
    pcVar1 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158e194:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::GetMasteryInfo()
// vaddr 0x148e1ac | ghidra 0x158e1ac | size 128 | symbol _ZN13FakeApiCaller14GetMasteryInfoEv | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller14GetMasteryInfoEv(undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02ac6208;
  uStack_48 = param_2;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0x45bea005,&UNK_02815ace/*"FakeApi/get_mastery_info.msgp"*/,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar1 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x0158e214;
    pcVar1 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158e214:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::TrainMastery(unsigned long, unsigned long, unsigned char, unsigned int, unsigned char, unsigned char)
// vaddr 0x148e22c | ghidra 0x158e22c | size 128 | symbol _ZN13FakeApiCaller12TrainMasteryEmmhjhh | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller12TrainMasteryEmmhjhh(undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02ac6288;
  uStack_48 = param_2;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0xbb0e7ef9,&UNK_02815aec/*"FakeApi/train_mastery.msgp"*/,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar1 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x0158e294;
    pcVar1 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158e294:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::ResetMastery(unsigned long, unsigned long)
// vaddr 0x148e2ac | ghidra 0x158e2ac | size 128 | symbol _ZN13FakeApiCaller12ResetMasteryEmm | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller12ResetMasteryEmm(undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02ac6308;
  uStack_48 = param_2;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0x614fa7ea,&UNK_02815b07/*"FakeApi/reset_mastery.msgp"*/,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar1 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x0158e314;
    pcVar1 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158e314:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::GetDecoInfo()
// vaddr 0x148e32c | ghidra 0x158e32c | size 128 | symbol _ZN13FakeApiCaller11GetDecoInfoEv | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller11GetDecoInfoEv(undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02ac6388;
  uStack_48 = param_2;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0x33015ed5,&UNK_02815b22/*"FakeApi/get_deco_info.msgp"*/,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar1 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x0158e394;
    pcVar1 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158e394:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::FavoriteDecoObject(Framework::CSTLVector<unsigned int> const&)
// vaddr 0x148e3ac | ghidra 0x158e3ac | size 128 | symbol _ZN13FakeApiCaller18FavoriteDecoObjectERKN9Framework10CSTLVectorIjEE | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller18FavoriteDecoObjectERKN9Framework10CSTLVectorIjEE
               (undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02ac6408;
  uStack_48 = param_2;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0x2b486f97,&UNK_02815b3d/*"FakeApi/favorite_deco_object.msgp"*/,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar1 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x0158e414;
    pcVar1 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158e414:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::UnFavoriteDecoObject(Framework::CSTLVector<unsigned int> const&)
// vaddr 0x148e42c | ghidra 0x158e42c | size 128 | symbol _ZN13FakeApiCaller20UnFavoriteDecoObjectERKN9Framework10CSTLVectorIjEE | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller20UnFavoriteDecoObjectERKN9Framework10CSTLVectorIjEE
               (undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02ac6488;
  uStack_48 = param_2;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0x6c67993d,&UNK_02815b5f/*"FakeApi/unfavorite_deco_object.msgp"*/,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar1 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x0158e494;
    pcVar1 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158e494:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::SetCharacterDeco()
// vaddr 0x148e4ac | ghidra 0x158e4ac | size 128 | symbol _ZN13FakeApiCaller16SetCharacterDecoEv | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller16SetCharacterDecoEv(undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02ac6508;
  uStack_48 = param_2;
  FakeApiCaller::AddLocalFile(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, char const*, std::__ndk1::function<Aska::Status (signed char*, unsigned int&)>)(param_2,0x747f39c,&UNK_02815b83/*"FakeApi/set_character_deco.msgp"*/,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar1 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x0158e514;
    pcVar1 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar1)();
code_r0x0158e514:
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::Reset()
// vaddr 0x148e52c | ghidra 0x158e52c | size 4 | symbol _ZN13FakeApiCaller5ResetEv | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller5ResetEv(void)

{
  return;
}

// ==== FakeApiCaller::ResetBRIDGE()
// vaddr 0x148e530 | ghidra 0x158e530 | size 4 | symbol _ZN13FakeApiCaller11ResetBRIDGEEv | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller11ResetBRIDGEEv(void)

{
  return;
}

// ==== FakeApiCaller::SetRetry(bool)
// vaddr 0x148e534 | ghidra 0x158e534 | size 4 | symbol _ZN13FakeApiCaller8SetRetryEb | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller8SetRetryEb(void)

{
  return;
}

// ==== FakeApiCaller::BeginBridge(std::__ndk1::function<void (Aska::Status&)>)
// vaddr 0x148e538 | ghidra 0x158e538 | size 12 | symbol _ZN13FakeApiCaller11BeginBridgeENSt6__ndk18functionIFvRN4Aska6StatusEEEE | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller11BeginBridgeENSt6__ndk18functionIFvRN4Aska6StatusEEEE(undefined8 *param_1)

{
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::EndBridge()
// vaddr 0x148e544 | ghidra 0x158e544 | size 12 | symbol _ZN13FakeApiCaller9EndBridgeEv | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller9EndBridgeEv(undefined8 *param_1)

{
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::GetBirthYearMonth()
// vaddr 0x148e550 | ghidra 0x158e550 | size 12 | symbol _ZN13FakeApiCaller17GetBirthYearMonthEv | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller17GetBirthYearMonthEv(undefined8 *param_1)

{
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::UpdateBirthYearMonth(unsigned short, unsigned char)
// vaddr 0x148e55c | ghidra 0x158e55c | size 12 | symbol _ZN13FakeApiCaller20UpdateBirthYearMonthEth | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller20UpdateBirthYearMonthEth(undefined8 *param_1)

{
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::GetStorageInfo()
// vaddr 0x148e590 | ghidra 0x158e590 | size 8 | symbol _ZN13FakeApiCaller14GetStorageInfoEv | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller14GetStorageInfoEv(undefined8 *param_1)

{
  *param_1 = 0;
  return;
}

// ==== FakeApiCaller::GetOneTimeStorageInfo()
// vaddr 0x148e598 | ghidra 0x158e598 | size 8 | symbol _ZN13FakeApiCaller21GetOneTimeStorageInfoEv | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller21GetOneTimeStorageInfoEv(undefined8 *param_1)

{
  *param_1 = 0;
  return;
}

// ==== FakeApiCaller::DepositItem(Framework::CSTLVector<unsigned long> const&)
// vaddr 0x148e5a0 | ghidra 0x158e5a0 | size 8 | symbol _ZN13FakeApiCaller11DepositItemERKN9Framework10CSTLVectorImEE | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller11DepositItemERKN9Framework10CSTLVectorImEE(undefined8 *param_1)

{
  *param_1 = 0;
  return;
}

// ==== FakeApiCaller::WithdrawItemFromStorage(Framework::CSTLVector<unsigned long> const&)
// vaddr 0x148e5a8 | ghidra 0x158e5a8 | size 8 | symbol _ZN13FakeApiCaller23WithdrawItemFromStorageERKN9Framework10CSTLVectorImEE | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller23WithdrawItemFromStorageERKN9Framework10CSTLVectorImEE(undefined8 *param_1)

{
  *param_1 = 0;
  return;
}

// ==== FakeApiCaller::WithdrawItemFromOneTimeStorage(unsigned int, unsigned int)
// vaddr 0x148e5b0 | ghidra 0x158e5b0 | size 8 | symbol _ZN13FakeApiCaller30WithdrawItemFromOneTimeStorageEjj | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller30WithdrawItemFromOneTimeStorageEjj(undefined8 *param_1)

{
  *param_1 = 0;
  return;
}

// ==== FakeApiCaller::BulkWithdrawItemFromOneTimeStorage(Framework::CSTLVector<unsigned int> const&, Framework::CSTLVector<unsigned int> const&)
// vaddr 0x148e5b8 | ghidra 0x158e5b8 | size 8 | symbol _ZN13FakeApiCaller34BulkWithdrawItemFromOneTimeStorageERKN9Framework10CSTLVectorIjEES4_ | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller34BulkWithdrawItemFromOneTimeStorageERKN9Framework10CSTLVectorIjEES4_
               (undefined8 *param_1)

{
  *param_1 = 0;
  return;
}

// ==== FakeApiCaller::SellItemsFromStorage(Framework::CSTLVector<unsigned long> const&)
// vaddr 0x148e5c0 | ghidra 0x158e5c0 | size 8 | symbol _ZN13FakeApiCaller20SellItemsFromStorageERKN9Framework10CSTLVectorImEE | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller20SellItemsFromStorageERKN9Framework10CSTLVectorImEE(undefined8 *param_1)

{
  *param_1 = 0;
  return;
}

// ==== FakeApiCaller::ClearNewOneTimeStorageItem(Framework::CSTLVector<unsigned int> const&)
// vaddr 0x148e5c8 | ghidra 0x158e5c8 | size 8 | symbol _ZN13FakeApiCaller26ClearNewOneTimeStorageItemERKN9Framework10CSTLVectorIjEE | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller26ClearNewOneTimeStorageItemERKN9Framework10CSTLVectorIjEE
               (undefined8 *param_1)

{
  *param_1 = 0;
  return;
}

// ==== FakeApiCaller::LockStorageItem(Framework::CSTLVector<unsigned long> const&)
// vaddr 0x148e5d0 | ghidra 0x158e5d0 | size 8 | symbol _ZN13FakeApiCaller15LockStorageItemERKN9Framework10CSTLVectorImEE | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller15LockStorageItemERKN9Framework10CSTLVectorImEE(undefined8 *param_1)

{
  *param_1 = 0;
  return;
}

// ==== FakeApiCaller::UnlockStorageItem(Framework::CSTLVector<unsigned long> const&)
// vaddr 0x148e5d8 | ghidra 0x158e5d8 | size 8 | symbol _ZN13FakeApiCaller17UnlockStorageItemERKN9Framework10CSTLVectorImEE | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller17UnlockStorageItemERKN9Framework10CSTLVectorImEE(undefined8 *param_1)

{
  *param_1 = 0;
  return;
}

// ==== FakeApiCaller::GetGearInfo()
// vaddr 0x148e5e0 | ghidra 0x158e5e0 | size 8 | symbol _ZN13FakeApiCaller11GetGearInfoEv | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller11GetGearInfoEv(undefined8 *param_1)

{
  *param_1 = 0;
  return;
}

// ==== FakeApiCaller::AttachGear(unsigned long, unsigned long, unsigned int)
// vaddr 0x148e5e8 | ghidra 0x158e5e8 | size 8 | symbol _ZN13FakeApiCaller10AttachGearEmmj | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller10AttachGearEmmj(undefined8 *param_1)

{
  *param_1 = 0;
  return;
}

// ==== FakeApiCaller::ClearNewGear(Framework::CSTLVector<unsigned long> const&)
// vaddr 0x148e5f0 | ghidra 0x158e5f0 | size 8 | symbol _ZN13FakeApiCaller12ClearNewGearERKN9Framework10CSTLVectorImEE | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller12ClearNewGearERKN9Framework10CSTLVectorImEE(undefined8 *param_1)

{
  *param_1 = 0;
  return;
}

// ==== FakeApiCaller::SellGear(Framework::CSTLVector<unsigned long> const&)
// vaddr 0x148e5f8 | ghidra 0x158e5f8 | size 8 | symbol _ZN13FakeApiCaller8SellGearERKN9Framework10CSTLVectorImEE | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller8SellGearERKN9Framework10CSTLVectorImEE(undefined8 *param_1)

{
  *param_1 = 0;
  return;
}

// ==== FakeApiCaller::RemoveGear(unsigned long)
// vaddr 0x148e600 | ghidra 0x158e600 | size 8 | symbol _ZN13FakeApiCaller10RemoveGearEm | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller10RemoveGearEm(undefined8 *param_1)

{
  *param_1 = 0;
  return;
}

// ==== FakeApiCaller::GenerateGear(unsigned long, unsigned int, Framework::CSTLVector<unsigned long> const&)
// vaddr 0x148e608 | ghidra 0x158e608 | size 8 | symbol _ZN13FakeApiCaller12GenerateGearEmjRKN9Framework10CSTLVectorImEE | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller12GenerateGearEmjRKN9Framework10CSTLVectorImEE(undefined8 *param_1)

{
  *param_1 = 0;
  return;
}

// ==== FakeApiCaller::UpdateGearStock()
// vaddr 0x148e610 | ghidra 0x158e610 | size 8 | symbol _ZN13FakeApiCaller15UpdateGearStockEv | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller15UpdateGearStockEv(undefined8 *param_1)

{
  *param_1 = 0;
  return;
}

// ==== FakeApiCaller::UpdateConfig(unsigned int, signed char const*, unsigned int)
// vaddr 0x148e618 | ghidra 0x158e618 | size 8 | symbol _ZN13FakeApiCaller12UpdateConfigEjPKaj | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller12UpdateConfigEjPKaj(undefined8 *param_1)

{
  *param_1 = 0;
  return;
}

// ==== FakeApiCaller::GetConfig()
// vaddr 0x148e620 | ghidra 0x158e620 | size 8 | symbol _ZN13FakeApiCaller9GetConfigEv | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller9GetConfigEv(undefined8 *param_1)

{
  *param_1 = 0;
  return;
}

// ==== FakeApiCaller::ResetConfig()
// vaddr 0x148e628 | ghidra 0x158e628 | size 8 | symbol _ZN13FakeApiCaller11ResetConfigEv | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller11ResetConfigEv(undefined8 *param_1)

{
  *param_1 = 0;
  return;
}

// ==== FakeApiCaller::GetGachaInData()
// vaddr 0x148e630 | ghidra 0x158e630 | size 8 | symbol _ZN13FakeApiCaller14GetGachaInDataEv | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller14GetGachaInDataEv(undefined8 *param_1)

{
  *param_1 = 0;
  return;
}

// ==== FakeApiCaller::MissionContinue(bool)
// vaddr 0x148e638 | ghidra 0x158e638 | size 8 | symbol _ZN13FakeApiCaller15MissionContinueEb | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller15MissionContinueEb(undefined8 *param_1)

{
  *param_1 = 0;
  return;
}

// ==== FakeApiCaller::MissionLose()
// vaddr 0x148e648 | ghidra 0x158e648 | size 8 | symbol _ZN13FakeApiCaller11MissionLoseEv | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller11MissionLoseEv(undefined8 *param_1)

{
  *param_1 = 0;
  return;
}

// ==== FakeApiCaller::GetWorldBossInfo(unsigned int)
// vaddr 0x148e658 | ghidra 0x158e658 | size 8 | symbol _ZN13FakeApiCaller16GetWorldBossInfoEj | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller16GetWorldBossInfoEj(undefined8 *param_1)

{
  *param_1 = 0;
  return;
}

// ==== FakeApiCaller::GetWorldMapInfoList(unsigned int)
// vaddr 0x148e660 | ghidra 0x158e660 | size 8 | symbol _ZN13FakeApiCaller19GetWorldMapInfoListEj | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller19GetWorldMapInfoListEj(undefined8 *param_1)

{
  *param_1 = 0;
  return;
}

// ==== FakeApiCaller::GetScenarioLibraryInfoList(unsigned int)
// vaddr 0x148e668 | ghidra 0x158e668 | size 8 | symbol _ZN13FakeApiCaller26GetScenarioLibraryInfoListEj | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller26GetScenarioLibraryInfoListEj(undefined8 *param_1)

{
  *param_1 = 0;
  return;
}

// ==== FakeApiCaller::DeepSpaceActiveList()
// vaddr 0x148e670 | ghidra 0x158e670 | size 8 | symbol _ZN13FakeApiCaller19DeepSpaceActiveListEv | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller19DeepSpaceActiveListEv(undefined8 *param_1)

{
  *param_1 = 0;
  return;
}

// ==== FakeApiCaller::ChangeRole(unsigned long, unsigned int)
// vaddr 0x148e678 | ghidra 0x158e678 | size 8 | symbol _ZN13FakeApiCaller10ChangeRoleEmj | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller10ChangeRoleEmj(undefined8 *param_1)

{
  *param_1 = 0;
  return;
}

// ==== FakeApiCaller::InheritAccessory(unsigned long, unsigned long)
// vaddr 0x148e680 | ghidra 0x158e680 | size 12 | symbol _ZN13FakeApiCaller16InheritAccessoryEmm | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller16InheritAccessoryEmm(undefined8 *param_1)

{
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::CoinList()
// vaddr 0x148e68c | ghidra 0x158e68c | size 8 | symbol _ZN13FakeApiCaller8CoinListEv | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller8CoinListEv(undefined8 *param_1)

{
  *param_1 = 0;
  return;
}

// ==== FakeApiCaller::CoinDepositCreate(unsigned char, int, char const*)
// vaddr 0x148e694 | ghidra 0x158e694 | size 8 | symbol _ZN13FakeApiCaller17CoinDepositCreateEhiPKc | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller17CoinDepositCreateEhiPKc(undefined8 *param_1)

{
  *param_1 = 0;
  return;
}

// ==== FakeApiCaller::CoinDepositIOSUpdate(unsigned int, char const*, char const*)
// vaddr 0x148e69c | ghidra 0x158e69c | size 12 | symbol _ZN13FakeApiCaller20CoinDepositIOSUpdateEjPKcS1_ | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller20CoinDepositIOSUpdateEjPKcS1_(undefined8 *param_1)

{
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::CoinDepositAndroidUpdate(unsigned int, char const*, char const*)
// vaddr 0x148e6a8 | ghidra 0x158e6a8 | size 12 | symbol _ZN13FakeApiCaller24CoinDepositAndroidUpdateEjPKcS1_ | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller24CoinDepositAndroidUpdateEjPKcS1_(undefined8 *param_1)

{
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::CoinDepositAmazonUpdate(unsigned int, char const*, char const*)
// vaddr 0x148e6b4 | ghidra 0x158e6b4 | size 12 | symbol _ZN13FakeApiCaller23CoinDepositAmazonUpdateEjPKcS1_ | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller23CoinDepositAmazonUpdateEjPKcS1_(undefined8 *param_1)

{
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::ItemShopList()
// vaddr 0x148e6c0 | ghidra 0x158e6c0 | size 12 | symbol _ZN13FakeApiCaller12ItemShopListEv | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller12ItemShopListEv(undefined8 *param_1)

{
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::DirectItemShopList()
// vaddr 0x148e6cc | ghidra 0x158e6cc | size 12 | symbol _ZN13FakeApiCaller18DirectItemShopListEv | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller18DirectItemShopListEv(undefined8 *param_1)

{
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::Home3DAnd2DSwitching(unsigned char)
// vaddr 0x148e6e0 | ghidra 0x158e6e0 | size 12 | symbol _ZN13FakeApiCaller20Home3DAnd2DSwitchingEh | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller20Home3DAnd2DSwitchingEh(undefined8 *param_1)

{
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::ChangeMascot(unsigned int)
// vaddr 0x148e6ec | ghidra 0x158e6ec | size 12 | symbol _ZN13FakeApiCaller12ChangeMascotEj | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller12ChangeMascotEj(undefined8 *param_1)

{
  *param_1 = 1;
  return;
}

// ==== FakeApiCaller::SendGuideInformation(unsigned int)
// vaddr 0x148e700 | ghidra 0x158e700 | size 8 | symbol _ZN13FakeApiCaller20SendGuideInformationEj | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller20SendGuideInformationEj(undefined8 *param_1)

{
  *param_1 = 0;
  return;
}

// ==== FakeApiCaller::ReadExpirationInfo(Framework::CSTLVector<unsigned int> const&)
// vaddr 0x148e708 | ghidra 0x158e708 | size 8 | symbol _ZN13FakeApiCaller18ReadExpirationInfoERKN9Framework10CSTLVectorIjEE | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller18ReadExpirationInfoERKN9Framework10CSTLVectorIjEE(undefined8 *param_1)

{
  *param_1 = 0;
  return;
}

// ==== FakeApiCaller::ReturnSphere211()
// vaddr 0x148e72c | ghidra 0x158e72c | size 8 | symbol _ZN13FakeApiCaller15ReturnSphere211Ev | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller15ReturnSphere211Ev(undefined8 *param_1)

{
  *param_1 = 0;
  return;
}

// ==== FakeApiCaller::Sphere211StaminaHeal()
// vaddr 0x148e734 | ghidra 0x158e734 | size 8 | symbol _ZN13FakeApiCaller20Sphere211StaminaHealEv | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller20Sphere211StaminaHealEv(undefined8 *param_1)

{
  *param_1 = 0;
  return;
}

// ==== FakeApiCaller::Sphere211UseRerollItem()
// vaddr 0x148e73c | ghidra 0x158e73c | size 8 | symbol _ZN13FakeApiCaller22Sphere211UseRerollItemEv | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller22Sphere211UseRerollItemEv(undefined8 *param_1)

{
  *param_1 = 0;
  return;
}

// ==== FakeApiCaller::Sphere211FloorClear(unsigned int)
// vaddr 0x148e744 | ghidra 0x158e744 | size 8 | symbol _ZN13FakeApiCaller19Sphere211FloorClearEj | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller19Sphere211FloorClearEj(undefined8 *param_1)

{
  *param_1 = 0;
  return;
}

// ==== FakeApiCaller::Sphere211SelectedFloor(unsigned int)
// vaddr 0x148e74c | ghidra 0x158e74c | size 8 | symbol _ZN13FakeApiCaller22Sphere211SelectedFloorEj | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller22Sphere211SelectedFloorEj(undefined8 *param_1)

{
  *param_1 = 0;
  return;
}

// ==== FakeApiCaller::Debug_GradeUpCharacter()
// vaddr 0x148e804 | ghidra 0x158e804 | size 8 | symbol _ZN13FakeApiCaller22Debug_GradeUpCharacterEv | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller22Debug_GradeUpCharacterEv(undefined8 *param_1)

{
  *param_1 = 0;
  return;
}

// ==== FakeApiCaller::Debug_GetCoin(unsigned int)
// vaddr 0x148e80c | ghidra 0x158e80c | size 8 | symbol _ZN13FakeApiCaller13Debug_GetCoinEj | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller13Debug_GetCoinEj(undefined8 *param_1)

{
  *param_1 = 0;
  return;
}

// ==== FakeApiCaller::Debug_GetFol(unsigned int)
// vaddr 0x148e814 | ghidra 0x158e814 | size 8 | symbol _ZN13FakeApiCaller12Debug_GetFolEj | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller12Debug_GetFolEj(undefined8 *param_1)

{
  *param_1 = 0;
  return;
}

// ==== FakeApiCaller::Debug_GetCharacter()
// vaddr 0x148e81c | ghidra 0x158e81c | size 8 | symbol _ZN13FakeApiCaller18Debug_GetCharacterEv | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller18Debug_GetCharacterEv(undefined8 *param_1)

{
  *param_1 = 0;
  return;
}

// ==== FakeApiCaller::Debug_GetItem()
// vaddr 0x148e824 | ghidra 0x158e824 | size 8 | symbol _ZN13FakeApiCaller13Debug_GetItemEv | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller13Debug_GetItemEv(undefined8 *param_1)

{
  *param_1 = 0;
  return;
}

// ==== FakeApiCaller::Debug_OpenMission()
// vaddr 0x148e82c | ghidra 0x158e82c | size 8 | symbol _ZN13FakeApiCaller17Debug_OpenMissionEv | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller17Debug_OpenMissionEv(undefined8 *param_1)

{
  *param_1 = 0;
  return;
}

// ==== FakeApiCaller::Debug_DeletePlayer()
// vaddr 0x148e834 | ghidra 0x158e834 | size 8 | symbol _ZN13FakeApiCaller18Debug_DeletePlayerEv | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller18Debug_DeletePlayerEv(undefined8 *param_1)

{
  *param_1 = 0;
  return;
}

// ==== FakeApiCaller::Debug_TowerMax()
// vaddr 0x148e83c | ghidra 0x158e83c | size 8 | symbol _ZN13FakeApiCaller14Debug_TowerMaxEv | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller14Debug_TowerMaxEv(undefined8 *param_1)

{
  *param_1 = 0;
  return;
}

// ==== FakeApiCaller::Debug_DeepMissionDrop(unsigned int, unsigned int, unsigned int, Framework::CSTLVector<unsigned long> const&)
// vaddr 0x148e844 | ghidra 0x158e844 | size 8 | symbol _ZN13FakeApiCaller21Debug_DeepMissionDropEjjjRKN9Framework10CSTLVectorImEE | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller21Debug_DeepMissionDropEjjjRKN9Framework10CSTLVectorImEE(undefined8 *param_1)

{
  *param_1 = 0;
  return;
}

// ==== FakeApiCaller::Debug_DeepBonus(unsigned int, unsigned int)
// vaddr 0x148e84c | ghidra 0x158e84c | size 8 | symbol _ZN13FakeApiCaller15Debug_DeepBonusEjj | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller15Debug_DeepBonusEjj(undefined8 *param_1)

{
  *param_1 = 0;
  return;
}

// ==== FakeApiCaller::Debug_DeepBonusRareMission(unsigned int, unsigned int, unsigned int, Framework::CSTLVector<unsigned long> const&)
// vaddr 0x148e854 | ghidra 0x158e854 | size 8 | symbol _ZN13FakeApiCaller26Debug_DeepBonusRareMissionEjjjRKN9Framework10CSTLVectorImEE | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller26Debug_DeepBonusRareMissionEjjjRKN9Framework10CSTLVectorImEE
               (undefined8 *param_1)

{
  *param_1 = 0;
  return;
}

// ==== FakeApiCaller::Debug_Gear(unsigned long, unsigned int, Framework::CSTLVector<unsigned long> const&, unsigned int, unsigned int)
// vaddr 0x148e85c | ghidra 0x158e85c | size 8 | symbol _ZN13FakeApiCaller10Debug_GearEmjRKN9Framework10CSTLVectorImEEjj | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller10Debug_GearEmjRKN9Framework10CSTLVectorImEEjj(undefined8 *param_1)

{
  *param_1 = 0;
  return;
}

// ==== FakeApiCaller::Debug_GearDrop(unsigned int, unsigned int)
// vaddr 0x148e864 | ghidra 0x158e864 | size 8 | symbol _ZN13FakeApiCaller14Debug_GearDropEjj | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller14Debug_GearDropEjj(undefined8 *param_1)

{
  *param_1 = 0;
  return;
}

// ==== FakeApiCaller::Debug_BarneyChance(unsigned int)
// vaddr 0x148e86c | ghidra 0x158e86c | size 8 | symbol _ZN13FakeApiCaller18Debug_BarneyChanceEj | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller18Debug_BarneyChanceEj(undefined8 *param_1)

{
  *param_1 = 0;
  return;
}

// ==== FakeApiCaller::Debug_FavorLoginBonus(unsigned int)
// vaddr 0x148e874 | ghidra 0x158e874 | size 8 | symbol _ZN13FakeApiCaller21Debug_FavorLoginBonusEj | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller21Debug_FavorLoginBonusEj(undefined8 *param_1)

{
  *param_1 = 0;
  return;
}

// ==== FakeApiCaller::Debug_Sphere211TreasureBox(unsigned int, unsigned int, unsigned int)
// vaddr 0x148e87c | ghidra 0x158e87c | size 8 | symbol _ZN13FakeApiCaller26Debug_Sphere211TreasureBoxEjjj | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller26Debug_Sphere211TreasureBoxEjjj(undefined8 *param_1)

{
  *param_1 = 0;
  return;
}

// ==== FakeApiCaller::Debug_Sphere211LotFloorNum(unsigned int, unsigned int)
// vaddr 0x148e884 | ghidra 0x158e884 | size 8 | symbol _ZN13FakeApiCaller26Debug_Sphere211LotFloorNumEjj | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller26Debug_Sphere211LotFloorNumEjj(undefined8 *param_1)

{
  *param_1 = 0;
  return;
}

// ==== FakeApiCaller::GetApiWatcher()
// vaddr 0x148e8b4 | ghidra 0x158e8b4 | size 8 | symbol _ZN13FakeApiCaller13GetApiWatcherEv | lib libSOA-3.7.0.so | 2026-10-09
undefined8 _ZN13FakeApiCaller13GetApiWatcherEv(void)

{
  return 0;
}

// ==== FakeApiCaller::DeleteWatcher()
// vaddr 0x148e8bc | ghidra 0x158e8bc | size 4 | symbol _ZN13FakeApiCaller13DeleteWatcherEv | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller13DeleteWatcherEv(void)

{
  return;
}

// ==== FakeApiCaller::GetApiNotify()
// vaddr 0x148e8c0 | ghidra 0x158e8c0 | size 8 | symbol _ZN13FakeApiCaller12GetApiNotifyEv | lib libSOA-3.7.0.so | 2026-10-09
undefined8 _ZN13FakeApiCaller12GetApiNotifyEv(void)

{
  return 0;
}

// ==== FakeApiCaller::LoggedIn() const
// vaddr 0x148e8c8 | ghidra 0x158e8c8 | size 8 | symbol _ZNK13FakeApiCaller8LoggedInEv | lib libSOA-3.7.0.so | 2026-10-09
undefined8 _ZNK13FakeApiCaller8LoggedInEv(void)

{
  return 1;
}

// ==== FakeApiCaller::IsSuccess(Aska::Yayoi::GameRPC::GameProtocol::FunctionID) const
// vaddr 0x148e8d0 | ghidra 0x158e8d0 | size 8 | symbol _ZNK13FakeApiCaller9IsSuccessEN4Aska5Yayoi7GameRPC12GameProtocol10FunctionIDE | lib libSOA-3.7.0.so | 2026-10-09
undefined8 _ZNK13FakeApiCaller9IsSuccessEN4Aska5Yayoi7GameRPC12GameProtocol10FunctionIDE(void)

{
  return 1;
}

// ==== FakeApiCaller::IsFailure(Aska::Yayoi::GameRPC::GameProtocol::FunctionID) const
// vaddr 0x148e8d8 | ghidra 0x158e8d8 | size 8 | symbol _ZNK13FakeApiCaller9IsFailureEN4Aska5Yayoi7GameRPC12GameProtocol10FunctionIDE | lib libSOA-3.7.0.so | 2026-10-09
undefined8 _ZNK13FakeApiCaller9IsFailureEN4Aska5Yayoi7GameRPC12GameProtocol10FunctionIDE(void)

{
  return 0;
}

// ==== FakeApiCaller::ErrorCode(Aska::Yayoi::GameRPC::GameProtocol::FunctionID) const
// vaddr 0x148e8e0 | ghidra 0x158e8e0 | size 8 | symbol _ZNK13FakeApiCaller9ErrorCodeEN4Aska5Yayoi7GameRPC12GameProtocol10FunctionIDE | lib libSOA-3.7.0.so | 2026-10-09
undefined8 _ZNK13FakeApiCaller9ErrorCodeEN4Aska5Yayoi7GameRPC12GameProtocol10FunctionIDE(void)

{
  return 0;
}

// ==== FakeApiCaller::SetSharedSecurityKey(signed char const*)
// vaddr 0x148e8e8 | ghidra 0x158e8e8 | size 4 | symbol _ZN13FakeApiCaller20SetSharedSecurityKeyEPKa | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller20SetSharedSecurityKeyEPKa(void)

{
  return;
}

// ==== FakeApiCaller::UpdateSession(signed char const*)
// vaddr 0x148e8ec | ghidra 0x158e8ec | size 8 | symbol _ZN13FakeApiCaller13UpdateSessionEPKa | lib libSOA-3.7.0.so | 2026-10-09
void _ZN13FakeApiCaller13UpdateSessionEPKa(undefined8 *param_1)

{
  *param_1 = 0;
  return;
}

// ==== std::__ndk1::__tree<std::__ndk1::__value_type<Aska::Yayoi::GameRPC::GameProtocol::FunctionID, FakeApiCaller::Info>, std::__ndk1::__map_value_compare<Aska::Yayoi::GameRPC::GameProtocol::FunctionID, std::__ndk1::__value_type<Aska::Yayoi::GameRPC::GameProtocol::FunctionID, FakeApiCaller::Info>, std::__ndk1::less<Aska::Yayoi::GameRPC::GameProtocol::FunctionID>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<Aska::Yayoi::GameRPC::GameProtocol::FunctionID, FakeApiCaller::Info>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<Aska::Yayoi::GameRPC::GameProtocol::FunctionID, FakeApiCaller::Info>, void*>*)
// vaddr 0x148e92c | ghidra 0x158e92c | size 132 | symbol _ZNSt6__ndk16__treeINS_12__value_typeIN4Aska5Yayoi7GameRPC12GameProtocol10FunctionIDEN13FakeApiCaller4InfoEEENS_19__map_value_compareIS6_S9_NS_4lessIS6_EELb1EEEN9Framework13CSTLAllocatorIS9_NSE_19CSTLMapAllocatorInfEEEE7destroyEPNS_11__tree_nodeIS9_PvEE | lib libSOA-3.7.0.so | 2026-10-09
/* WARNING: Possible PIC construction at 0x0158e99c: Changing call to branch */

void _ZNSt6__ndk16__treeINS_12__value_typeIN4Aska5Yayoi7GameRPC12GameProtocol10FunctionIDEN13FakeApiCaller4InfoEEENS_19__map_value_compareIS6_S9_NS_4lessIS6_EELb1EEEN9Framework13CSTLAllocatorIS9_NSE_19CSTLMapAllocatorInfEEEE7destroyEPNS_11__tree_nodeIS9_PvEE
               (undefined8 param_1,undefined8 *param_2)

{
  long *plVar1;
  code *pcVar2;
  
  if (param_2 == (undefined8 *)0x0) {
    return;
  }
  std::__ndk1::__tree<std::__ndk1::__value_type<Aska::Yayoi::GameRPC::GameProtocol::FunctionID, FakeApiCaller::Info>, std::__ndk1::__map_value_compare<Aska::Yayoi::GameRPC::GameProtocol::FunctionID, std::__ndk1::__value_type<Aska::Yayoi::GameRPC::GameProtocol::FunctionID, FakeApiCaller::Info>, std::__ndk1::less<Aska::Yayoi::GameRPC::GameProtocol::FunctionID>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<Aska::Yayoi::GameRPC::GameProtocol::FunctionID, FakeApiCaller::Info>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<Aska::Yayoi::GameRPC::GameProtocol::FunctionID, FakeApiCaller::Info>, void*>*)(param_1,*param_2);
  std::__ndk1::__tree<std::__ndk1::__value_type<Aska::Yayoi::GameRPC::GameProtocol::FunctionID, FakeApiCaller::Info>, std::__ndk1::__map_value_compare<Aska::Yayoi::GameRPC::GameProtocol::FunctionID, std::__ndk1::__value_type<Aska::Yayoi::GameRPC::GameProtocol::FunctionID, FakeApiCaller::Info>, std::__ndk1::less<Aska::Yayoi::GameRPC::GameProtocol::FunctionID>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<Aska::Yayoi::GameRPC::GameProtocol::FunctionID, FakeApiCaller::Info>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<Aska::Yayoi::GameRPC::GameProtocol::FunctionID, FakeApiCaller::Info>, void*>*)(param_1,param_2[1]);
  plVar1 = (long *)param_2[0xe];
  if (param_2 + 10 == plVar1) {
    pcVar2 = *(code **)(*plVar1 + 0x20);
  }
  else {
    if (plVar1 == (long *)0x0) goto code_r0x0158e990;
    pcVar2 = *(code **)(*plVar1 + 0x28);
  }
  (*pcVar2)();
code_r0x0158e990:
  if ((*(byte *)(param_2 + 7) & 1) != 0) {
    param_2 = (undefined8 *)param_2[9];
  }
  (*(code *)PTR__ZN9Framework37CAssignedMemoryManagerForSTLAllocator4FreeEPv_02ca11c0)(param_2);
  return;
}

// ==== std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<Aska::Yayoi::GameRPC::GameProtocol::FunctionID, FakeApiCaller::Info>, std::__ndk1::__tree_node<std::__ndk1::__value_type<Aska::Yayoi::GameRPC::GameProtocol::FunctionID, FakeApiCaller::Info>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<Aska::Yayoi::GameRPC::GameProtocol::FunctionID, FakeApiCaller::Info>, std::__ndk1::__map_value_compare<Aska::Yayoi::GameRPC::GameProtocol::FunctionID, std::__ndk1::__value_type<Aska::Yayoi::GameRPC::GameProtocol::FunctionID, FakeApiCaller::Info>, std::__ndk1::less<Aska::Yayoi::GameRPC::GameProtocol::FunctionID>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<Aska::Yayoi::GameRPC::GameProtocol::FunctionID, FakeApiCaller::Info>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<Aska::Yayoi::GameRPC::GameProtocol::FunctionID, Aska::Yayoi::GameRPC::GameProtocol::FunctionID&, FakeApiCaller::Info>(Aska::Yayoi::GameRPC::GameProtocol::FunctionID const&, Aska::Yayoi::GameRPC::GameProtocol::FunctionID&, FakeApiCaller::Info&&)
// vaddr 0x148e9b0 | ghidra 0x158e9b0 | size 416 | symbol _ZNSt6__ndk16__treeINS_12__value_typeIN4Aska5Yayoi7GameRPC12GameProtocol10FunctionIDEN13FakeApiCaller4InfoEEENS_19__map_value_compareIS6_S9_NS_4lessIS6_EELb1EEEN9Framework13CSTLAllocatorIS9_NSE_19CSTLMapAllocatorInfEEEE25__emplace_unique_key_argsIS6_JRS6_S8_EEENS_4pairINS_15__tree_iteratorIS9_PNS_11__tree_nodeIS9_PvEElEEbEERKT_DpOT0_ | lib libSOA-3.7.0.so | 2026-10-09
/* WARNING: Type propagation algorithm not settling */

undefined1  [16]
_ZNSt6__ndk16__treeINS_12__value_typeIN4Aska5Yayoi7GameRPC12GameProtocol10FunctionIDEN13FakeApiCaller4InfoEEENS_19__map_value_compareIS6_S9_NS_4lessIS6_EELb1EEEN9Framework13CSTLAllocatorIS9_NSE_19CSTLMapAllocatorInfEEEE25__emplace_unique_key_argsIS6_JRS6_S8_EEENS_4pairINS_15__tree_iteratorIS9_PNS_11__tree_nodeIS9_PvEElEEbEERKT_DpOT0_
          (long *param_1,uint *param_2,undefined4 *param_3,undefined8 *param_4)

{
  long *******ppppppplVar1;
  undefined8 uVar2;
  long ******pppppplVar3;
  long *******ppppppplVar4;
  long *******ppppppplVar5;
  undefined1 auVar6 [16];
  long *******ppppppplStack_38;
  
  ppppppplVar5 = (long *******)(param_1 + 1);
  if ((long *******)*ppppppplVar5 == (long *******)0x0) {
    ppppppplVar4 = (long *******)*ppppppplVar5;
    ppppppplVar1 = ppppppplVar5;
  }
  else {
    ppppppplVar4 = (long *******)*ppppppplVar5;
    do {
      while (ppppppplVar1 = ppppppplVar4, *param_2 < *(uint *)(ppppppplVar1 + 4)) {
        ppppppplVar4 = (long *******)*ppppppplVar1;
        if ((long *******)*ppppppplVar1 == (long *******)0x0) {
          ppppppplVar4 = (long *******)*ppppppplVar1;
          ppppppplVar5 = ppppppplVar1;
          goto joined_r0x0158ea58;
        }
      }
      if (*param_2 <= *(uint *)(ppppppplVar1 + 4)) {
        ppppppplVar5 = (long *******)&ppppppplStack_38;
        ppppppplVar4 = ppppppplVar1;
        goto joined_r0x0158ea58;
      }
      ppppppplVar5 = ppppppplVar1 + 1;
      ppppppplVar4 = (long *******)*ppppppplVar5;
    } while ((long *******)*ppppppplVar5 != (long *******)0x0);
    ppppppplVar4 = (long *******)*ppppppplVar5;
  }
joined_r0x0158ea58:
  if (ppppppplVar4 == (long *******)0x0) {
    ppppppplStack_38 = ppppppplVar1;
    ppppppplVar4 = (long *******)Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(0x80,&UNK_027dc4e5/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Map.h"*/,0x21);
    if (ppppppplVar4 == (long *******)0x0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    }
    *(undefined4 *)(ppppppplVar4 + 4) = *param_3;
    ppppppplVar4[6] = (long ******)*param_4;
    ppppppplVar4[9] = (long ******)param_4[3];
    pppppplVar3 = (long ******)param_4[1];
    ppppppplVar4[8] = (long ******)param_4[2];
    ppppppplVar4[7] = pppppplVar3;
    pppppplVar3 = (long ******)param_4[8];
    param_4[2] = 0;
    param_4[3] = 0;
    param_4[1] = 0;
    if (pppppplVar3 == (long ******)0x0) {
      ppppppplVar4[0xe] = (long ******)0x0;
    }
    else if ((long ******)(param_4 + 4) == pppppplVar3) {
      ppppppplVar4[0xe] = (long ******)(ppppppplVar4 + 10);
      (**(code **)(*(long *)param_4[8] + 0x18))();
    }
    else {
      ppppppplVar4[0xe] = pppppplVar3;
      param_4[8] = 0;
    }
    *ppppppplVar4 = (long ******)0x0;
    ppppppplVar4[1] = (long ******)0x0;
    ppppppplVar4[2] = (long ******)ppppppplVar1;
    *ppppppplVar5 = (long ******)ppppppplVar4;
    ppppppplVar1 = ppppppplVar4;
    if (*(long *)*param_1 != 0) {
      *param_1 = *(long *)*param_1;
      ppppppplVar1 = (long *******)*ppppppplVar5;
    }
    void std::__ndk1::__tree_balance_after_insert<std::__ndk1::__tree_node_base<void*>*>(std::__ndk1::__tree_node_base<void*>*, std::__ndk1::__tree_node_base<void*>*)(param_1[1],ppppppplVar1);
    uVar2 = 1;
    param_1[2] = param_1[2] + 1;
  }
  else {
    uVar2 = 0;
  }
  auVar6._8_8_ = uVar2;
  auVar6._0_8_ = ppppppplVar4;
  return auVar6;
}


// FAILED to create function at 02ac2758 FakeApiCaller::vtable
// FAILED to create function at 02ac2ec0 FakeApiCaller::typeinfo
