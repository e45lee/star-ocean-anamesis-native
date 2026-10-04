// port/decomp/kernel/application.c: Ghidra decompiles for the kernel subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-04 06:16 UTC: tools/decomp.sh '--into' 'kernel/application' 'Framework::CApplication::' 'Aska::AskaMainThread::' 'Aska::LifeCycleManager::'

// ==== Framework::CApplication::CAskaAppWithoutAPE::~CAskaAppWithoutAPE()
// vaddr 0x1e622e4 | ghidra 0x1f622e4 | size 56 | symbol _ZN9Framework12CApplication18CAskaAppWithoutAPED2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework12CApplication18CAskaAppWithoutAPED2Ev(void)

{
  undefined *puVar1;
  
  puVar1 = 
  PTR__ZN9Framework10TSingletonINS_12CApplication18CAskaAppWithoutAPEEE11m_pInstanceE_02cc2f60;
  if (*(long *)
       PTR__ZN9Framework10TSingletonINS_12CApplication18CAskaAppWithoutAPEEE11m_pInstanceE_02cc2f60
      == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029612b1/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TSingleton.h"*/,0x1d,&UNK_027daf21/*"m_pInstance is null."*/);
  }
  *(undefined8 *)puVar1 = 0;
  return;
}

// ==== Framework::CApplication::Integrated_Preinit()
// vaddr 0x1e6231c | ghidra 0x1f6231c | size 88 | symbol _ZN9Framework12CApplication18Integrated_PreinitEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework12CApplication18Integrated_PreinitEv(void)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)(*(long *)PTR__ZN4Aska6Global6m_pAppE_02cc2078 + 0x30);
  if (*(char *)(*(long *)PTR__ZN4Aska6Global6m_pAppE_02cc2078 + 0x140) != '\0') {
    puVar1 = (undefined8 *)0x0;
  }
  *puVar1 = 0x17700000;
  *(undefined4 *)((long)puVar1 + 0x5c) = 0x80;
  *(undefined4 *)(puVar1 + 4) = 0x180;
  *(undefined4 *)(puVar1 + 5) = 0x1800;
  *(undefined4 *)(puVar1 + 6) = 0x600;
  *(undefined4 *)((long)puVar1 + 0xc) = 0x400;
  *(undefined4 *)(puVar1 + 8) = 0x1000;
  return;
}

// ==== Framework::CApplication::Integrated_Init(Aska::App::InitParams&)
// vaddr 0x1e62374 | ghidra 0x1f62374 | size 4 | symbol _ZN9Framework12CApplication15Integrated_InitERN4Aska3App10InitParamsE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework12CApplication15Integrated_InitERN4Aska3App10InitParamsE(void)

{
  return;
}

// ==== Framework::CApplication::InitializeMainTask()
// vaddr 0x1e62378 | ghidra 0x1f62378 | size 72 | symbol _ZN9Framework12CApplication18InitializeMainTaskEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework12CApplication18InitializeMainTaskEv(void)

{
  long lVar1;
  undefined8 uVar2;
  
  uVar2 = *(undefined8 *)PTR__ZN4Aska6Global20m_pSystemTaskManagerE_02cbf620;
  lVar1 = operator new(unsigned long, std::nothrow_t const&)(0xf8,PTR__ZSt7nothrow_02cb9a80);
  if (lVar1 != 0) {
    Framework::CApplication::CMainTask::CMainTask()(lVar1);
  }
  (*(code *)PTR__ZN4Aska11TaskManager3AddEPNS_4TaskE_02c95ab0)(uVar2,lVar1);
  return;
}

// ==== Framework::CApplication::ReleaseMainTask()
// vaddr 0x1e623c0 | ghidra 0x1f623c0 | size 4 | symbol _ZN9Framework12CApplication15ReleaseMainTaskEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework12CApplication15ReleaseMainTaskEv(void)

{
  return;
}

// ==== Framework::CApplication::CAskaAppWithoutAPE::Release()
// vaddr 0x1e623c4 | ghidra 0x1f623c4 | size 24 | symbol _ZN9Framework12CApplication18CAskaAppWithoutAPE7ReleaseEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework12CApplication18CAskaAppWithoutAPE7ReleaseEv(long param_1)

{
  (*(code *)PTR__ZN4Aska11TaskManager3AddEPNS_4TaskE_02c95ab0)
            (*(undefined8 *)PTR__ZN4Aska6Global20m_pSystemTaskManagerE_02cbf620,
             *(undefined8 *)(param_1 + 0x148));
  return;
}

// ==== Framework::CApplication::CAskaAppWithoutAPE::DeleteTasks()
// vaddr 0x1e623dc | ghidra 0x1f623dc | size 172 | symbol _ZN9Framework12CApplication18CAskaAppWithoutAPE11DeleteTasksEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework12CApplication18CAskaAppWithoutAPE11DeleteTasksEv(long param_1)

{
  long *plVar1;
  long lVar2;
  
  if (*(long *)(param_1 + 0x148) != 0) {
    Aska::Task::Remove()();
    (**(code **)(**(long **)(param_1 + 0x148) + 0x38))(*(long **)(param_1 + 0x148),0);
    *(undefined8 *)(param_1 + 0x148) = 0;
  }
  lVar2 = *(long *)PTR__ZN4Aska6Global20m_pPeripheralManagerE_02cc47d0;
  if (lVar2 != 0) {
    *(undefined1 *)(lVar2 + 0x30) = 1;
    Aska::Thread::WaitEnd()(lVar2 + 8);
    *(undefined1 *)(lVar2 + 0x31) = 0;
  }
  plVar1 = (long *)Aska::Global::GetPeripheral(int)(0);
  if (plVar1 != (long *)0x0) {
    Aska::Global::ReleasePeripheral(int)(0);
    (**(code **)(*plVar1 + 8))(plVar1);
  }
  plVar1 = (long *)Aska::Global::GetExPeripheral(int)(0);
  if (plVar1 != (long *)0x0) {
    Aska::Global::ReleaseExPeripheral(int)(0);
                    /* WARNING: Could not recover jumptable at 0x01f6247c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(*plVar1 + 8))(plVar1);
    return;
  }
  return;
}

// ==== Framework::CApplication::CAskaAppWithoutAPE::Preinit()
// vaddr 0x1e62488 | ghidra 0x1f62488 | size 88 | symbol _ZN9Framework12CApplication18CAskaAppWithoutAPE7PreinitEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework12CApplication18CAskaAppWithoutAPE7PreinitEv(void)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)(*(long *)PTR__ZN4Aska6Global6m_pAppE_02cc2078 + 0x30);
  if (*(char *)(*(long *)PTR__ZN4Aska6Global6m_pAppE_02cc2078 + 0x140) != '\0') {
    puVar1 = (undefined8 *)0x0;
  }
  *puVar1 = 0x17700000;
  *(undefined4 *)((long)puVar1 + 0x5c) = 0x80;
  *(undefined4 *)(puVar1 + 4) = 0x180;
  *(undefined4 *)(puVar1 + 5) = 0x1800;
  *(undefined4 *)(puVar1 + 6) = 0x600;
  *(undefined4 *)((long)puVar1 + 0xc) = 0x400;
  *(undefined4 *)(puVar1 + 8) = 0x1000;
  return;
}

// ==== Framework::CApplication::CAskaAppWithoutAPE::Init()
// vaddr 0x1e624e0 | ghidra 0x1f624e0 | size 4 | symbol _ZN9Framework12CApplication18CAskaAppWithoutAPE4InitEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework12CApplication18CAskaAppWithoutAPE4InitEv(void)

{
  return;
}

// ==== Framework::CApplication::CAskaAppWithoutAPE::Run()
// vaddr 0x1e624e4 | ghidra 0x1f624e4 | size 436 | symbol _ZN9Framework12CApplication18CAskaAppWithoutAPE3RunEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework12CApplication18CAskaAppWithoutAPE3RunEv(long param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined4 uVar4;
  long *plVar5;
  undefined8 *puVar6;
  long lVar7;
  code *pcVar8;
  undefined8 uVar9;
  undefined1 auStack_d0 [160];
  
  plVar5 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x28,PTR__ZSt7nothrow_02cb9a80);
  puVar1 = PTR__ZTVN4Aska4TaskE_02cbe020;
  if (plVar5 != (long *)0x0) {
    plVar5[2] = 0;
    plVar5[3] = 0;
    *(undefined2 *)((long)plVar5 + 0x24) = 0;
    pcVar8 = *(code **)(puVar1 + 0x68);
    *plVar5 = (long)(puVar1 + 0x10);
    plVar5[1] = 0;
    *(undefined1 *)((long)plVar5 + 0x26) = 0;
    uVar4 = (*pcVar8)(plVar5);
    *(undefined4 *)(plVar5 + 4) = uVar4;
    *plVar5 = (long)(PTR__ZTVN9Framework26CAskaAppWithoutAPEExitTaskE_02cbdbd0 + 0x10);
  }
  *(long **)(param_1 + 0x148) = plVar5;
  Framework::IGame::Instantiate()();
  puVar1 = PTR__ZN9Framework10TSingletonINS_5IGameEE11m_pInstanceE_02cc1a70;
  puVar6 = *(undefined8 **)PTR__ZN9Framework10TSingletonINS_5IGameEE11m_pInstanceE_02cc1a70;
  if (puVar6 == (undefined8 *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029612b1/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    puVar6 = *(undefined8 **)puVar1;
  }
  (**(code **)*puVar6)(auStack_d0);
  puVar1 = PTR__ZN9Framework12CApplication20m_FrameworkArgumentsE_02cbf880;
  memcpy(PTR__ZN9Framework12CApplication20m_FrameworkArgumentsE_02cbf880,auStack_d0,0xa0);
  if (puVar1[0x60] == '\0') {
    Framework::CAskaInitializer::Do(unsigned int, unsigned int)(0x280,0x470);
  }
  else {
    Framework::CAskaInitializer::Do(Framework::tFrameworkArguments::tAskaDescription&)(puVar1 + 0x60);
  }
  puVar1 = PTR__ZN4Aska6Global20m_pSystemTaskManagerE_02cbf620;
  uVar9 = *(undefined8 *)PTR__ZN4Aska6Global20m_pSystemTaskManagerE_02cbf620;
  lVar7 = operator new(unsigned long, std::nothrow_t const&)(0xf8,PTR__ZSt7nothrow_02cb9a80);
  if (lVar7 != 0) {
    Framework::CApplication::CMainTask::CMainTask()(lVar7);
  }
  Aska::TaskManager::Add(Aska::Task*)(uVar9,lVar7);
  puVar3 = PTR__ZN4Aska6Global16m_pObjectManagerE_02cc4688;
  puVar2 = PTR__ZN9Framework10TSingletonINS_12CApplication9CMainTaskEE11m_pInstanceE_02cc41c8;
  do {
    while( true ) {
      Aska::ObjectManager::OnPaint()(*(undefined8 *)puVar3);
      (**(code **)(**(long **)(*(long *)puVar1 + 0x108) + 0x70))();
      lVar7 = *(long *)puVar2;
      if (lVar7 != 0) break;
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029612b1/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
      if (*(char *)(*(long *)puVar2 + 0x6f) != '\0') goto code_r0x01f6266c;
    }
  } while (*(char *)(lVar7 + 0x6f) == '\0');
code_r0x01f6266c:
  (**(code **)(**(long **)PTR__ZN4Aska6Global6m_pAppE_02cc2078 + 0x28))();
  return;
}

// ==== Framework::CApplication::InitializeAska()
// vaddr 0x1e62698 | ghidra 0x1f62698 | size 140 | symbol _ZN9Framework12CApplication14InitializeAskaEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework12CApplication14InitializeAskaEv(void)

{
  undefined *puVar1;
  undefined8 *puVar2;
  undefined1 auStack_b0 [160];
  
  Framework::IGame::Instantiate()();
  puVar1 = PTR__ZN9Framework10TSingletonINS_5IGameEE11m_pInstanceE_02cc1a70;
  puVar2 = *(undefined8 **)PTR__ZN9Framework10TSingletonINS_5IGameEE11m_pInstanceE_02cc1a70;
  if (puVar2 == (undefined8 *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029612b1/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    puVar2 = *(undefined8 **)puVar1;
  }
  (**(code **)*puVar2)(auStack_b0);
  puVar1 = PTR__ZN9Framework12CApplication20m_FrameworkArgumentsE_02cbf880;
  memcpy(PTR__ZN9Framework12CApplication20m_FrameworkArgumentsE_02cbf880,auStack_b0,0xa0);
  if (puVar1[0x60] == '\0') {
    Framework::CAskaInitializer::Do(unsigned int, unsigned int)(0x280,0x470);
  }
  else {
    Framework::CAskaInitializer::Do(Framework::tFrameworkArguments::tAskaDescription&)(puVar1 + 0x60);
  }
  return;
}

// ==== Framework::CApplication::pProjectCode()
// vaddr 0x1e62724 | ghidra 0x1f62724 | size 12 | symbol _ZN9Framework12CApplication12pProjectCodeEv | lib libSOA-3.7.0.so | 2026-10-04
undefined * _ZN9Framework12CApplication12pProjectCodeEv(void)

{
  return &UNK_029610a0/*"Project-BAS"*/;
}

// ==== Framework::CApplication::pApeApp()
// vaddr 0x1e62730 | ghidra 0x1f62730 | size 8 | symbol _ZN9Framework12CApplication7pApeAppEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN9Framework12CApplication7pApeAppEv(void)

{
  return 0;
}

// ==== Framework::CApplication::gEnableExit()
// vaddr 0x1e62738 | ghidra 0x1f62738 | size 4 | symbol _ZN9Framework12CApplication11gEnableExitEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework12CApplication11gEnableExitEv(void)

{
  return;
}

// ==== Framework::CApplication::gAppBack()
// vaddr 0x1e6273c | ghidra 0x1f6273c | size 16 | symbol _ZN9Framework12CApplication8gAppBackEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework12CApplication8gAppBackEv(void)

{
  uRam0000000002d00240 = 1;
  return;
}

// ==== Framework::CApplication::IsAppBack()
// vaddr 0x1e6274c | ghidra 0x1f6274c | size 12 | symbol _ZN9Framework12CApplication9IsAppBackEv | lib libSOA-3.7.0.so | 2026-10-04
undefined1 _ZN9Framework12CApplication9IsAppBackEv(void)

{
  return uRam0000000002d00240;
}

// ==== Framework::CApplication::CMainTask::CMainTask()
// vaddr 0x1e62758 | ghidra 0x1f62758 | size 252 | symbol _ZN9Framework12CApplication9CMainTaskC2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework12CApplication9CMainTaskC1Ev(long *param_1)

{
  undefined *puVar1;
  undefined4 uVar2;
  long lVar3;
  code *pcVar4;
  
  pcVar4 = *(code **)(PTR__ZTVN4Aska4TaskE_02cbe020 + 0x68);
  *param_1 = (long)(PTR__ZTVN4Aska4TaskE_02cbe020 + 0x10);
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  *(undefined2 *)((long)param_1 + 0x24) = 0;
  *(undefined1 *)((long)param_1 + 0x26) = 0;
  uVar2 = (*pcVar4)();
  *(undefined4 *)(param_1 + 4) = uVar2;
  puVar1 = PTR__ZN9Framework10TSingletonINS_12CApplication9CMainTaskEE11m_pInstanceE_02cc41c8;
  if (*(long *)PTR__ZN9Framework10TSingletonINS_12CApplication9CMainTaskEE11m_pInstanceE_02cc41c8 !=
      0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029612b1/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TSingleton.h"*/,0x15,&UNK_027daee5/*"m_pInstance isn't null.(%08x)"*/);
  }
  *(long **)puVar1 = param_1;
  puVar1 = PTR__ZTVN9Framework12CApplication9CMainTaskE_02cc36c0;
  param_1[7] = 0;
  *param_1 = (long)(puVar1 + 0x10);
  param_1[6] = 0;
  param_1[5] = 0;
  Framework::CISO::CISO()(param_1 + 8);
  *(undefined1 *)((long)param_1 + 0x6f) = 0;
  *(undefined1 *)((long)param_1 + 0xec) = 0;
  param_1[0x1e] = 0;
  param_1[0xc] = 0;
  param_1[0xb] = 0;
  param_1[10] = 0;
  param_1[9] = 0;
  param_1[0x13] = 0;
  param_1[0x14] = 0;
  param_1[0x12] = 0;
  param_1[0x1b] = 0;
  param_1[0x1c] = 0;
  param_1[0x1a] = 0;
  lVar3 = operator new(unsigned long, std::nothrow_t const&)(0x28,PTR__ZSt7nothrow_02cb9a80);
  if (lVar3 != 0) {
    Framework::CApplicationMemory::CApplicationMemory()();
  }
  puVar1 = PTR__ZN9Framework10TSingletonINS_18CApplicationMemoryEE11m_pInstanceE_02cb8148;
  lVar3 = *(long *)PTR__ZN9Framework10TSingletonINS_18CApplicationMemoryEE11m_pInstanceE_02cb8148;
  if (lVar3 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029612b1/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar3 = *(long *)puVar1;
  }
  (*(code *)PTR__ZN9Framework18CApplicationMemory23SetPrimaryMemoryManagerEv_02c8fb28)(lVar3);
  return;
}

// ==== Framework::CApplication::CMainTask::~CMainTask()
// vaddr 0x1e62854 | ghidra 0x1f62854 | size 140 | symbol _ZN9Framework12CApplication9CMainTaskD1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework12CApplication9CMainTaskD2Ev(long *param_1)

{
  undefined *puVar1;
  long *plVar2;
  
  *param_1 = (long)(PTR__ZTVN9Framework12CApplication9CMainTaskE_02cc36c0 + 0x10);
  puVar1 = PTR__ZN9Framework10TSingletonINS_18CApplicationMemoryEE11m_pInstanceE_02cb8148;
  if (*(long *)PTR__ZN9Framework10TSingletonINS_18CApplicationMemoryEE11m_pInstanceE_02cb8148 != 0)
  {
    *(undefined8 *)PTR__ZN9Framework10TSingletonINS_18CApplicationMemoryEE11m_pInstanceE_02cb8148 =
         0;
    operator delete(void*)();
    *(undefined8 *)puVar1 = 0;
  }
  plVar2 = (long *)Framework::CAssignedMemoryManagerForSTLAllocator::pAttachedMemoryManager()();
  if (plVar2 != (long *)0x0) {
    (**(code **)(*plVar2 + 0xd0))();
  }
  *(undefined1 *)(param_1 + 0xe) = 0;
  puVar1 = PTR__ZN9Framework10TSingletonINS_12CApplication9CMainTaskEE11m_pInstanceE_02cc41c8;
  if (*(long *)PTR__ZN9Framework10TSingletonINS_12CApplication9CMainTaskEE11m_pInstanceE_02cc41c8 ==
      0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029612b1/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TSingleton.h"*/,0x1d,&UNK_027daf21/*"m_pInstance is null."*/);
  }
  *(undefined8 *)puVar1 = 0;
  (*(code *)PTR__ZN4Aska4TaskD1Ev_02c92d10)(param_1);
  return;
}

// ==== Framework::CApplication::CMainTask::~CMainTask()
// vaddr 0x1e628e0 | ghidra 0x1f628e0 | size 148 | symbol _ZN9Framework12CApplication9CMainTaskD0Ev | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Possible PIC construction at 0x01f62910: Changing call to branch */
/* WARNING: Removing unreachable block (ram,0x01f62914) */

void _ZN9Framework12CApplication9CMainTaskD0Ev(long *param_1)

{
  undefined *puVar1;
  long *plVar2;
  
  *param_1 = (long)(PTR__ZTVN9Framework12CApplication9CMainTaskE_02cc36c0 + 0x10);
  plVar2 = *(long **)PTR__ZN9Framework10TSingletonINS_18CApplicationMemoryEE11m_pInstanceE_02cb8148;
  if (plVar2 == (long *)0x0) {
    plVar2 = (long *)Framework::CAssignedMemoryManagerForSTLAllocator::pAttachedMemoryManager()();
    if (plVar2 != (long *)0x0) {
      (**(code **)(*plVar2 + 0xd0))();
    }
    *(undefined1 *)(param_1 + 0xe) = 0;
    puVar1 = PTR__ZN9Framework10TSingletonINS_12CApplication9CMainTaskEE11m_pInstanceE_02cc41c8;
    if (*(long *)PTR__ZN9Framework10TSingletonINS_12CApplication9CMainTaskEE11m_pInstanceE_02cc41c8
        == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029612b1/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TSingleton.h"*/,0x1d,&UNK_027daf21/*"m_pInstance is null."*/);
    }
    *(undefined8 *)puVar1 = 0;
    Aska::Task::~Task()(param_1);
  }
  else {
    *(undefined8 *)PTR__ZN9Framework10TSingletonINS_18CApplicationMemoryEE11m_pInstanceE_02cb8148 =
         0;
    param_1 = plVar2;
  }
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Framework::CApplication::CMainTask::FrameCounter() const
// vaddr 0x1e62974 | ghidra 0x1f62974 | size 8 | symbol _ZNK9Framework12CApplication9CMainTask12FrameCounterEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK9Framework12CApplication9CMainTask12FrameCounterEv(long param_1)

{
  return *(undefined4 *)(param_1 + 0x2c);
}

// ==== Framework::CApplication::CMainTask::rRootFiberKernel()
// vaddr 0x1e6297c | ghidra 0x1f6297c | size 60 | symbol _ZN9Framework12CApplication9CMainTask16rRootFiberKernelEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZN9Framework12CApplication9CMainTask16rRootFiberKernelEv(long param_1)

{
  if (*(long *)(param_1 + 0x90) != 0) {
    return *(long *)(param_1 + 0x90);
  }
  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029610ac/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Application.cpp"*/,0x24f,&UNK_02961103/*"m_pRootFiberKernel is null."*/);
  return *(long *)(param_1 + 0x90);
}

// ==== Framework::CApplication::CMainTask::rResourceManager() const
// vaddr 0x1e629b8 | ghidra 0x1f629b8 | size 60 | symbol _ZNK9Framework12CApplication9CMainTask16rResourceManagerEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK9Framework12CApplication9CMainTask16rResourceManagerEv(long param_1)

{
  if (*(long *)(param_1 + 0x60) != 0) {
    return *(long *)(param_1 + 0x60);
  }
  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029610ac/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Application.cpp"*/,0x255,&UNK_0296111f/*"m_pResourceManager is null."*/);
  return *(long *)(param_1 + 0x60);
}

// ==== Framework::CApplication::CMainTask::rFrameworkArguments() const
// vaddr 0x1e629f4 | ghidra 0x1f629f4 | size 12 | symbol _ZNK9Framework12CApplication9CMainTask19rFrameworkArgumentsEv | lib libSOA-3.7.0.so | 2026-10-04
undefined * _ZNK9Framework12CApplication9CMainTask19rFrameworkArgumentsEv(void)

{
  return PTR__ZN9Framework12CApplication20m_FrameworkArgumentsE_02cbf880;
}

// ==== Framework::CApplication::CMainTask::rSystemDefaultCamera() const
// vaddr 0x1e62a00 | ghidra 0x1f62a00 | size 60 | symbol _ZNK9Framework12CApplication9CMainTask20rSystemDefaultCameraEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK9Framework12CApplication9CMainTask20rSystemDefaultCameraEv(long param_1)

{
  if (*(long *)(param_1 + 0x38) != 0) {
    return *(long *)(param_1 + 0x38);
  }
  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029610ac/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Application.cpp"*/,0x262,&UNK_0296113b/*"m_pCameraStock_SystemDefault is null."*/);
  return *(long *)(param_1 + 0x38);
}

// ==== Framework::CApplication::CMainTask::rCamera() const
// vaddr 0x1e62a3c | ghidra 0x1f62a3c | size 60 | symbol _ZNK9Framework12CApplication9CMainTask7rCameraEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK9Framework12CApplication9CMainTask7rCameraEv(long param_1)

{
  if (*(long *)(param_1 + 0x30) != 0) {
    return *(long *)(param_1 + 0x30);
  }
  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029610ac/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Application.cpp"*/,0x268,&UNK_02961161/*"m_pCamera is null."*/);
  return *(long *)(param_1 + 0x30);
}

// ==== Framework::CApplication::CMainTask::crCamera() const
// vaddr 0x1e62a78 | ghidra 0x1f62a78 | size 60 | symbol _ZNK9Framework12CApplication9CMainTask8crCameraEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK9Framework12CApplication9CMainTask8crCameraEv(long param_1)

{
  if (*(long *)(param_1 + 0x30) != 0) {
    return *(long *)(param_1 + 0x30);
  }
  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029610ac/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Application.cpp"*/,0x26e,&UNK_02961161/*"m_pCamera is null."*/);
  return *(long *)(param_1 + 0x30);
}

// ==== Framework::CApplication::CMainTask::rFader() const
// vaddr 0x1e62ab4 | ghidra 0x1f62ab4 | size 60 | symbol _ZNK9Framework12CApplication9CMainTask6rFaderEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK9Framework12CApplication9CMainTask6rFaderEv(long param_1)

{
  if (*(long *)(param_1 + 0x48) != 0) {
    return *(long *)(param_1 + 0x48);
  }
  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029610ac/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Application.cpp"*/,0x274,&UNK_02961174/*"m_pFader is null."*/);
  return *(long *)(param_1 + 0x48);
}

// ==== Framework::CApplication::CMainTask::rFaderView_Color() const
// vaddr 0x1e62af0 | ghidra 0x1f62af0 | size 60 | symbol _ZNK9Framework12CApplication9CMainTask16rFaderView_ColorEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK9Framework12CApplication9CMainTask16rFaderView_ColorEv(long param_1)

{
  if (*(long *)(param_1 + 0x50) != 0) {
    return *(long *)(param_1 + 0x50);
  }
  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029610ac/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Application.cpp"*/,0x27a,&UNK_02961186/*"m_pFaderView_Color is null."*/);
  return *(long *)(param_1 + 0x50);
}

// ==== Framework::CApplication::CMainTask::rSoundManager() const
// vaddr 0x1e62b2c | ghidra 0x1f62b2c | size 60 | symbol _ZNK9Framework12CApplication9CMainTask13rSoundManagerEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK9Framework12CApplication9CMainTask13rSoundManagerEv(long param_1)

{
  if (*(long *)(param_1 + 0x58) != 0) {
    return *(long *)(param_1 + 0x58);
  }
  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029610ac/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Application.cpp"*/,0x280,&UNK_029611a2/*"m_pSoundManager is null."*/);
  return *(long *)(param_1 + 0x58);
}

// ==== Framework::CApplication::CMainTask::pScreenPrintPool(unsigned int)
// vaddr 0x1e62b68 | ghidra 0x1f62b68 | size 88 | symbol _ZN9Framework12CApplication9CMainTask16pScreenPrintPoolEj | lib libSOA-3.7.0.so | 2026-10-04
long _ZN9Framework12CApplication9CMainTask16pScreenPrintPoolEj(long param_1,uint param_2)

{
  long lVar1;
  
  if (1 < param_2) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029610ac/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Application.cpp"*/,0x286,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,param_2,2);
  }
  lVar1 = 0;
  if (*(long *)(param_1 + 0x98) != 0) {
    lVar1 = *(long *)(param_1 + 0x98) + (ulong)param_2 * 0x40;
  }
  return lVar1;
}

// ==== Framework::CApplication::CMainTask::rScreenPrintPool(unsigned int)
// vaddr 0x1e62bc0 | ghidra 0x1f62bc0 | size 124 | symbol _ZN9Framework12CApplication9CMainTask16rScreenPrintPoolEj | lib libSOA-3.7.0.so | 2026-10-04
long _ZN9Framework12CApplication9CMainTask16rScreenPrintPoolEj(long param_1,uint param_2)

{
  if (*(long *)(param_1 + 0x98) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029610ac/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Application.cpp"*/,0x28c,&UNK_029611bb/*"m_pScreenPrintPool is null."*/);
  }
  if (1 < param_2) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029610ac/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Application.cpp"*/,0x28d,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,param_2,2);
  }
  return *(long *)(param_1 + 0x98) + (ulong)param_2 * 0x40;
}

// ==== Framework::CApplication::CMainTask::rDebugPrimitiveManager()
// vaddr 0x1e62c3c | ghidra 0x1f62c3c | size 60 | symbol _ZN9Framework12CApplication9CMainTask22rDebugPrimitiveManagerEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZN9Framework12CApplication9CMainTask22rDebugPrimitiveManagerEv(long param_1)

{
  if (*(long *)(param_1 + 0xd8) != 0) {
    return *(long *)(param_1 + 0xd8);
  }
  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029610ac/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Application.cpp"*/,0x293,&UNK_029611d7/*"m_pDebugPrimitiveManager is null."*/);
  return *(long *)(param_1 + 0xd8);
}

// ==== Framework::CApplication::CMainTask::rResponderChainManager()
// vaddr 0x1e62c78 | ghidra 0x1f62c78 | size 60 | symbol _ZN9Framework12CApplication9CMainTask22rResponderChainManagerEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZN9Framework12CApplication9CMainTask22rResponderChainManagerEv(long param_1)

{
  if (*(long *)(param_1 + 0xe0) != 0) {
    return *(long *)(param_1 + 0xe0);
  }
  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029610ac/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Application.cpp"*/,0x299,&UNK_029611f9/*"m_pResponderChainManager is null."*/);
  return *(long *)(param_1 + 0xe0);
}

// ==== Framework::CApplication::CMainTask::TakeHighQualityScreenShot()
// vaddr 0x1e62cb4 | ghidra 0x1f62cb4 | size 12 | symbol _ZN9Framework12CApplication9CMainTask25TakeHighQualityScreenShotEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework12CApplication9CMainTask25TakeHighQualityScreenShotEv(long param_1)

{
  *(undefined1 *)(param_1 + 0xec) = 1;
  return;
}

// ==== Framework::CApplication::CMainTask::ResolutionWidth()
// vaddr 0x1e62cc0 | ghidra 0x1f62cc0 | size 20 | symbol _ZN9Framework12CApplication9CMainTask15ResolutionWidthEv | lib libSOA-3.7.0.so | 2026-10-04
undefined2 _ZN9Framework12CApplication9CMainTask15ResolutionWidthEv(void)

{
  return *(undefined2 *)(*(long *)PTR__ZN4Aska6Global14m_pFrameBufferE_02cb8198 + 0x18);
}

// ==== Framework::CApplication::CMainTask::ResolutionHeight()
// vaddr 0x1e62cd4 | ghidra 0x1f62cd4 | size 20 | symbol _ZN9Framework12CApplication9CMainTask16ResolutionHeightEv | lib libSOA-3.7.0.so | 2026-10-04
undefined2 _ZN9Framework12CApplication9CMainTask16ResolutionHeightEv(void)

{
  return *(undefined2 *)(*(long *)PTR__ZN4Aska6Global14m_pFrameBufferE_02cb8198 + 0x1a);
}

// ==== Framework::CApplication::CMainTask::ChangeScreenResolution(unsigned int, unsigned int, unsigned int, unsigned int)
// vaddr 0x1e62ce8 | ghidra 0x1f62ce8 | size 76 | symbol _ZN9Framework12CApplication9CMainTask22ChangeScreenResolutionEjjjj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework12CApplication9CMainTask22ChangeScreenResolutionEjjjj
               (undefined2 param_1,undefined2 param_2)

{
  long lVar1;
  undefined2 uStack_30;
  undefined2 uStack_2e;
  undefined4 uStack_2c;
  undefined8 uStack_28;
  undefined8 uStack_20;
  undefined8 uStack_18;
  
  lVar1 = *(long *)PTR__ZN4Aska6Global14m_pFrameBufferE_02cb8198;
  uStack_18 = *(undefined8 *)(lVar1 + 0x20);
  uStack_20 = *(undefined8 *)(lVar1 + 0x18);
  uStack_28 = *(undefined8 *)(lVar1 + 0x30);
  uStack_2c = (undefined4)((ulong)*(undefined8 *)(lVar1 + 0x28) >> 0x20);
  _uStack_30 = CONCAT22(param_2,param_1);
  Aska::FrameBuffer::SetFrameFormat(Aska::FrameBuffer::Screen::Num, Aska::FrontScreenFormat const*, Aska::BackScreenFormat const*)(lVar1,0,&uStack_20,&uStack_30);
  return;
}

// ==== Framework::CApplication::CMainTask::EnableApeDefaultLight(bool)
// vaddr 0x1e62d34 | ghidra 0x1f62d34 | size 4 | symbol _ZN9Framework12CApplication9CMainTask21EnableApeDefaultLightEb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework12CApplication9CMainTask21EnableApeDefaultLightEb(void)

{
  return;
}

// ==== Framework::CApplication::CMainTask::UpdateTitleBarText()
// vaddr 0x1e62d38 | ghidra 0x1f62d38 | size 4 | symbol _ZN9Framework12CApplication9CMainTask18UpdateTitleBarTextEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework12CApplication9CMainTask18UpdateTitleBarTextEv(void)

{
  return;
}

// ==== Framework::CApplication::CMainTask::rISO()
// vaddr 0x1e62d3c | ghidra 0x1f62d3c | size 8 | symbol _ZN9Framework12CApplication9CMainTask4rISOEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZN9Framework12CApplication9CMainTask4rISOEv(long param_1)

{
  return param_1 + 0x40;
}

// ==== Framework::CApplication::CMainTask::OnDevelopment()
// vaddr 0x1e62d44 | ghidra 0x1f62d44 | size 8 | symbol _ZN9Framework12CApplication9CMainTask13OnDevelopmentEv | lib libSOA-3.7.0.so | 2026-10-04
undefined1 _ZN9Framework12CApplication9CMainTask13OnDevelopmentEv(long param_1)

{
  return *(undefined1 *)(param_1 + 0x6d);
}

// ==== Framework::CApplication::CMainTask::pBuildInformation() const
// vaddr 0x1e62d4c | ghidra 0x1f62d4c | size 52 | symbol _ZNK9Framework12CApplication9CMainTask17pBuildInformationEv | lib libSOA-3.7.0.so | 2026-10-04
char * _ZNK9Framework12CApplication9CMainTask17pBuildInformationEv(long param_1)

{
  if (*(char *)(param_1 + 0x70) == '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029610ac/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Application.cpp"*/,0x322,&UNK_0296121b/*"pBuildInformation was not initialized, yet."*/);
  }
  return (char *)(param_1 + 0x70);
}

// ==== Framework::CApplication::CMainTask::UnlockGlobalPauseAndStep()
// vaddr 0x1e62d80 | ghidra 0x1f62d80 | size 4 | symbol _ZN9Framework12CApplication9CMainTask24UnlockGlobalPauseAndStepEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework12CApplication9CMainTask24UnlockGlobalPauseAndStepEv(void)

{
  return;
}

// ==== Framework::CApplication::CMainTask::OnRelease()
// vaddr 0x1e62d84 | ghidra 0x1f62d84 | size 156 | symbol _ZN9Framework12CApplication9CMainTask9OnReleaseEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework12CApplication9CMainTask9OnReleaseEv(long param_1)

{
  undefined *puVar1;
  long *plVar2;
  
  puVar1 = PTR__ZN9Framework10TSingletonINS_5IGameEE11m_pInstanceE_02cc1a70;
  plVar2 = *(long **)PTR__ZN9Framework10TSingletonINS_5IGameEE11m_pInstanceE_02cc1a70;
  if (plVar2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029612b1/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    plVar2 = *(long **)puVar1;
  }
  (**(code **)(*plVar2 + 0x18))(plVar2);
  plVar2 = *(long **)(param_1 + 0x60);
  if (plVar2 != (long *)0x0) {
    (**(code **)(*plVar2 + 0x38))(plVar2,0);
    *(undefined8 *)(param_1 + 0x60) = 0;
  }
  if (*(long **)(param_1 + 0x90) != (long *)0x0) {
    (**(code **)(**(long **)(param_1 + 0x90) + 8))();
    *(undefined8 *)(param_1 + 0x90) = 0;
  }
  Framework::CInteroperateParameter::ReleaseDefaultKey()();
  Framework::CFileLoader::ReleaseDefaultDirectLoadFolder()();
  *(undefined8 *)PTR__ZN4Aska6Global16m_pMemoryManagerE_02cbd3f0 = 0;
  return;
}

// ==== Framework::CApplication::CMainTask::DeleteTasks()
// vaddr 0x1e62e20 | ghidra 0x1f62e20 | size 24 | symbol _ZN9Framework12CApplication9CMainTask11DeleteTasksEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework12CApplication9CMainTask11DeleteTasksEv(long param_1)

{
  *(undefined1 *)(param_1 + 0x6f) = 1;
  *(int *)(param_1 + 0x28) = *(int *)(param_1 + 0x28) + 1;
  return;
}

// ==== Framework::CApplication::CMainTask::Run(int)
// vaddr 0x1e62e38 | ghidra 0x1f62e38 | size 3160 | symbol _ZN9Framework12CApplication9CMainTask3RunEi | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN9Framework12CApplication9CMainTask3RunEi(long param_1)

{
  undefined *puVar1;
  byte bVar2;
  undefined *puVar3;
  byte bVar4;
  undefined4 uVar5;
  long lVar6;
  long *plVar7;
  ulong uVar8;
  int iVar9;
  code *pcVar10;
  long *plVar11;
  long *plVar12;
  long lVar13;
  long *plVar14;
  undefined8 uVar15;
  
  uRam0000000002d00240 = 0;
  if (*(long *)(param_1 + 0xd8) != 0) {
    Framework::CDebugPrimitiveManager::Reset()();
  }
  puVar3 = PTR__ZN9Framework10TSingletonINS_5IGameEE11m_pInstanceE_02cc1a70;
  iVar9 = *(int *)(param_1 + 0x28);
  if (iVar9 == 10) {
    if (1 < *(int *)PTR__ZN4Aska6Global15m_ExitRequestedE_02cc3650 - 1U) {
      uVar5 = NEON_fminnm(*(float *)PTR__ZN4Aska6Global18m_fSystemDeltaTimeE_02cbfa70 *
                          _UNK_027ebde0,0x40400000);
      Framework::CTimeElementContainer::Progress(float)(uVar5);
      uVar15 = Framework::CTimeElementContainer::FrameworkDT()();
      if ((float)uVar15 < 0.0) {
        Framework::gDoAssert(char const*, int, char const*, ...)((double)(float)uVar15,&UNK_029610ac/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Application.cpp"*/,0x48d,&UNK_02961296/*"The dt less than zero.(%f)"*/);
      }
      puVar3 = PTR__ZN9Framework10TSingletonINS_5IGameEE11m_pInstanceE_02cc1a70;
      plVar7 = *(long **)PTR__ZN9Framework10TSingletonINS_5IGameEE11m_pInstanceE_02cc1a70;
      if (plVar7 == (long *)0x0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029612b1/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
        plVar7 = *(long **)puVar3;
      }
      (**(code **)(*plVar7 + 0x20))(uVar15);
      *(undefined4 *)(param_1 + 0x68) = 0;
      puVar1 = PTR__ZN9Framework10TSingletonINS_4CPadEE11m_pInstanceE_02cbef78;
      lVar6 = *(long *)PTR__ZN9Framework10TSingletonINS_4CPadEE11m_pInstanceE_02cbef78;
      if (lVar6 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029612b1/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
        lVar6 = *(long *)puVar1;
      }
      Framework::CPad::Mode(unsigned int)(lVar6,0);
      lVar6 = *(long *)puVar1;
      if (lVar6 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029612b1/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
        lVar6 = *(long *)puVar1;
      }
      Framework::CPad::Progress(float)(uVar15,lVar6);
      puVar1 = PTR__ZN9Framework10TSingletonINS_6CMouseEE11m_pInstanceE_02cc1de0;
      lVar6 = *(long *)PTR__ZN9Framework10TSingletonINS_6CMouseEE11m_pInstanceE_02cc1de0;
      if (lVar6 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029612b1/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
        lVar6 = *(long *)puVar1;
      }
      Framework::CMouse::Progress(float)(uVar15,lVar6);
      puVar1 = PTR__ZN9Framework10TSingletonINS_11CTouchPanelEE11m_pInstanceE_02cbd318;
      lVar6 = *(long *)PTR__ZN9Framework10TSingletonINS_11CTouchPanelEE11m_pInstanceE_02cbd318;
      if (lVar6 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029612b1/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
        lVar6 = *(long *)puVar1;
      }
      Framework::CTouchPanel::Progress(float)(uVar15,lVar6);
      lVar6 = *(long *)(param_1 + 0xe0);
      if (lVar6 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029610ac/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Application.cpp"*/,0x299,&UNK_029611f9/*"m_pResponderChainManager is null."*/);
        lVar6 = *(long *)(param_1 + 0xe0);
      }
      Framework::ResponderChain::CManager::Progress()(lVar6);
      puVar1 = PTR__ZN9Framework10TSingletonINS_5Cocos14CCocosDirectorEE11m_pInstanceE_02cc2fe8;
      lVar6 = *(long *)
               PTR__ZN9Framework10TSingletonINS_5Cocos14CCocosDirectorEE11m_pInstanceE_02cc2fe8;
      if (lVar6 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029612b1/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
        lVar6 = *(long *)puVar1;
      }
      Framework::Cocos::CCocosDirector::InputProgress(float)(uVar15,lVar6);
      Framework::CPerformanceCounter::Mark(unsigned int)(0x20);
      plVar7 = *(long **)puVar3;
      if (plVar7 == (long *)0x0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029612b1/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
        plVar7 = *(long **)puVar3;
      }
      (**(code **)(*plVar7 + 0x28))(uVar15);
      (**(code **)(**(long **)(param_1 + 0x90) + 0x28))();
      Framework::CPerformanceCounter::Set(unsigned int)(0x20);
      lVar6 = *(long *)puVar1;
      if (lVar6 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029612b1/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
        lVar6 = *(long *)puVar1;
      }
      Framework::Cocos::CCocosDirector::SceneProgress(float)(uVar15,lVar6);
      if (*(long *)(param_1 + 0x38) !=
          *(long *)(*(long *)PTR__ZN4Aska6Global16m_pCameraManagerE_02cb7d08 + 0xff0)) {
        *(long *)(param_1 + 0x38) =
             *(long *)(*(long *)PTR__ZN4Aska6Global16m_pCameraManagerE_02cb7d08 + 0xff0);
      }
      Framework::CCamera::Update()(*(undefined8 *)(param_1 + 0x30));
      lVar6 = param_1 + 0x40;
      uVar8 = Framework::CISO::IsModified() const(lVar6);
      if ((uVar8 & 1) != 0) {
        Framework::CISO::ResetModified()(lVar6);
        lVar13 = *(long *)(param_1 + 0x38);
        if (lVar13 == 0) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029610ac/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Application.cpp"*/,0x262,&UNK_0296113b/*"m_pCameraStock_SystemDefault is null."*/);
          lVar13 = *(long *)(param_1 + 0x38);
        }
        uVar5 = Framework::CISO::SettingValue() const(lVar6);
        Aska::CameraFilterManager::SetISO(int)(*(undefined8 *)(lVar13 + 0xe30),uVar5);
      }
      plVar7 = *(long **)puVar3;
      if (plVar7 == (long *)0x0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029612b1/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
        plVar7 = *(long **)puVar3;
      }
      (**(code **)(*plVar7 + 0x30))(uVar15);
      goto code_r0x01f63a34;
    }
    plVar7 = *(long **)PTR__ZN9Framework10TSingletonINS_5IGameEE11m_pInstanceE_02cc1a70;
    if (plVar7 == (long *)0x0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029612b1/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
      plVar7 = *(long **)puVar3;
    }
    (**(code **)(*plVar7 + 0x18))();
    plVar7 = *(long **)(param_1 + 0x60);
    if (plVar7 != (long *)0x0) {
      (**(code **)(*plVar7 + 0x38))(plVar7,0);
      *(undefined8 *)(param_1 + 0x60) = 0;
    }
    if (*(long **)(param_1 + 0x90) != (long *)0x0) {
      (**(code **)(**(long **)(param_1 + 0x90) + 8))();
      *(undefined8 *)(param_1 + 0x90) = 0;
    }
    Framework::CInteroperateParameter::ReleaseDefaultKey()();
    Framework::CFileLoader::ReleaseDefaultDirectLoadFolder()();
    *(undefined8 *)PTR__ZN4Aska6Global16m_pMemoryManagerE_02cbd3f0 = 0;
    iVar9 = *(int *)(param_1 + 0x28);
    *(undefined1 *)(param_1 + 0x6f) = 1;
code_r0x01f63a2c:
    iVar9 = iVar9 + 1;
  }
  else {
    if (iVar9 != 1) {
      if (iVar9 != 0) goto code_r0x01f63a34;
      Framework::CFileLoader::InitializeDefaultDirectLoadFolder()();
      bVar4 = Framework::gIsFileExist(char const*)(&UNK_02961247/*"AssetFullUpadteToIFBuild.cmd"*/);
      *(byte *)(param_1 + 0x6d) = ~bVar4 & 1;
      Framework::CInteroperateParameter::InitializeDefaultKey(char const*, unsigned long)(&UNK_02961264/*"^^"*/,100);
      puVar3 = PTR__ZN9Framework10TSingletonINS_18CApplicationMemoryEE11m_pInstanceE_02cb8148;
      lVar6 = *(long *)
               PTR__ZN9Framework10TSingletonINS_18CApplicationMemoryEE11m_pInstanceE_02cb8148;
      if (lVar6 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029612b1/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
        lVar6 = *(long *)puVar3;
      }
      Framework::CApplicationMemory::SetParticleMemoryManager()(lVar6);
      lVar6 = *(long *)puVar3;
      if (lVar6 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029612b1/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
        lVar6 = *(long *)puVar3;
      }
      Framework::CApplicationMemory::SetSoundMemoryManager()(lVar6);
      lVar6 = *(long *)puVar3;
      if (lVar6 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029612b1/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
        lVar6 = *(long *)puVar3;
      }
      Framework::CApplicationMemory::SetNetworkMemoryManager()(lVar6);
      Framework::CTimeElementContainer::Initialize()();
      puVar3 = PTR__ZN4Aska6Global16m_pCameraManagerE_02cb7d08;
      lVar6 = *(long *)(*(long *)PTR__ZN4Aska6Global16m_pCameraManagerE_02cb7d08 + 0xff0);
      *(long *)(param_1 + 0x38) = lVar6;
      if (lVar6 != 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029610ac/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Application.cpp"*/,0x39e,&UNK_02961267/*"m_pCameraStock_SystemDefault isn't null.(%08x)"*/);
      }
      lVar6 = operator new(unsigned long, std::nothrow_t const&)(0xf90,PTR__ZSt7nothrow_02cb9a80);
      if (lVar6 != 0) {
        Aska::Camera::Camera()(lVar6);
      }
      *(long *)(param_1 + 0x38) = lVar6;
      Aska::Camera::Default()(lVar6);
      plVar7 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x1a0,PTR__ZSt7nothrow_02cb9a80);
      puVar1 = PTR__ZTVN4Aska4TaskE_02cbe020;
      if (plVar7 != (long *)0x0) {
        plVar7[2] = 0;
        plVar7[3] = 0;
        *(undefined2 *)((long)plVar7 + 0x24) = 0;
        pcVar10 = *(code **)(puVar1 + 0x68);
        *plVar7 = (long)(puVar1 + 0x10);
        plVar7[1] = 0;
        *(undefined1 *)((long)plVar7 + 0x26) = 0;
        uVar5 = (*pcVar10)(plVar7);
        *(undefined4 *)(plVar7 + 4) = uVar5;
        puVar1 = PTR__ZTVN4Aska27HierarchicalObjectContainerE_02cb81a8 + 0x10;
        *plVar7 = (long)(PTR__ZTVN4Aska18HierarchicalObjectE_02cb6bb0 + 0x10);
        plVar11 = plVar7 + 6;
        *plVar11 = (long)puVar1;
        plVar7[0x14] = 0x3f8000003f800000;
        plVar7[0x15] = 0x3f8000003f800000;
        lVar13 = _UNK_027dbb38;
        lVar6 = _UNK_027dbb30;
        bVar4 = *(byte *)(plVar7 + 0x25);
        bVar2 = *(byte *)((long)plVar7 + 0x129);
        *(byte *)((long)plVar7 + 0x129) = bVar2 & 0xfc;
        plVar7[0x11] = lVar13;
        plVar7[0x10] = lVar6;
        plVar7[0x13] = lVar13;
        plVar7[0x12] = lVar6;
        *(byte *)(plVar7 + 0x25) = bVar4 & 0xde | 1;
        plVar12 = plVar7 + 0x18;
        do {
          plVar14 = (long *)((long)plVar12 + 0x7fU & 0xffffffffffffff81);
          Hint_Prefetch(plVar12,0,2,0);
          plVar12 = plVar14;
        } while (plVar14 < plVar7 + 0x1a);
        plVar7[0x20] = (long)plVar11;
        plVar7[0x21] = (long)plVar11;
        *(byte *)((long)plVar7 + 0x129) = bVar2 & 0xf8;
        plVar7[0x18] = 0;
        plVar7[0x19] = 0x3f80000000000000;
        plVar7[0x1b] = lVar13;
        plVar7[0x1a] = lVar6;
        plVar7[0x1d] = lVar13;
        plVar7[0x1c] = lVar6;
        plVar7[0x17] = lVar13;
        plVar7[0x16] = lVar6;
        plVar7[0x22] = 0;
        plVar7[0x23] = 0;
        plVar7[0x1e] = 0;
        plVar7[0x1f] = 0;
        plVar7[5] = 0;
        plVar7[0x23] = (long)plVar7;
        plVar7[0x24] = (long)(plVar7 + 8);
        plVar7[0x30] = 0;
        plVar7[0x31] = 0;
        *(undefined4 *)(plVar7 + 0x32) = 0;
        *(undefined1 *)((long)plVar7 + 0x195) = 0;
        *(undefined1 *)((long)plVar7 + 0x194) = 1;
        *(byte *)(plVar7 + 0x25) = bVar4 & 200 | 1;
        *(undefined1 *)((long)plVar7 + 0x197) = 0;
      }
      (**(code **)(*plVar7 + 200))(0,0,0,plVar7);
      lVar6 = *(long *)(param_1 + 0x38);
      if (*(long **)(lVar6 + 0x1b0) != plVar7) {
        if (*(long *)(lVar6 + 0x1c8) != 0) {
          *(undefined8 *)(*(long *)(lVar6 + 0x1c8) + 0x10) = *(undefined8 *)(lVar6 + 0x1d0);
        }
        if (*(undefined8 **)(lVar6 + 0x1d0) != (undefined8 *)0x0) {
          **(undefined8 **)(lVar6 + 0x1d0) = *(undefined8 *)(lVar6 + 0x1c8);
          *(undefined8 *)(lVar6 + 0x1d0) = 0;
        }
        *(undefined8 *)(lVar6 + 0x1c8) = 0;
        *(long **)(lVar6 + 0x1b0) = plVar7;
        if (plVar7 != (long *)0x0) {
          *(undefined8 *)(lVar6 + 0x1c8) = 0;
          plVar12 = plVar7 + 0x22;
          if (plVar7[0x22] == 0) {
            lVar13 = 0;
          }
          else {
            *(undefined8 **)(plVar7[0x22] + 0x10) = (undefined8 *)(lVar6 + 0x1c8);
            lVar13 = *plVar12;
          }
          *(long *)(lVar6 + 0x1c8) = lVar13;
          *(long **)(lVar6 + 0x1d0) = plVar12;
          *plVar12 = lVar6 + 0x1c0;
        }
        *(byte *)(lVar6 + 0x128) = *(byte *)(lVar6 + 0x128) & 0xe0 | 1;
        lVar6 = *(long *)(param_1 + 0x38);
      }
      Aska::TaskManager::Add(Aska::Task*)(*(undefined8 *)puVar3,lVar6);
      lVar6 = *(long *)(param_1 + 0x38);
      if ((lVar6 != 0) && (lVar13 = *(long *)puVar3, *(long *)(lVar13 + 0xff0) != lVar6)) {
        *(long *)(lVar13 + 0xff0) = lVar6;
        if ((*(byte *)(lVar6 + 0xeb4) >> 4 & 1) != 0) {
          Aska::Camera::MakeCameraMatrix()(lVar6);
        }
        *(undefined8 *)(lVar6 + 0xd68) = *(undefined8 *)(lVar6 + 0x138);
        *(undefined8 *)(lVar6 + 0xd60) = *(undefined8 *)(lVar6 + 0x130);
        *(undefined8 *)(lVar6 + 0xd78) = *(undefined8 *)(lVar6 + 0x148);
        *(undefined8 *)(lVar6 + 0xd70) = *(undefined8 *)(lVar6 + 0x140);
        *(undefined8 *)(lVar6 + 0xd88) = *(undefined8 *)(lVar6 + 0x158);
        *(undefined8 *)(lVar6 + 0xd80) = *(undefined8 *)(lVar6 + 0x150);
        *(undefined8 *)(lVar6 + 0xd98) = *(undefined8 *)(lVar6 + 0x168);
        *(undefined8 *)(lVar6 + 0xd90) = *(undefined8 *)(lVar6 + 0x160);
      }
      lVar6 = operator new(unsigned long, std::nothrow_t const&)(0x50,PTR__ZSt7nothrow_02cb9a80);
      if (lVar6 != 0) {
        Framework::CCamera::CCamera()(lVar6);
      }
      *(long *)(param_1 + 0x30) = lVar6;
      Framework::CCamera::Initialize(Aska::Camera&)(lVar6,*(undefined8 *)(param_1 + 0x38));
      lVar6 = operator new(unsigned long, std::nothrow_t const&)(0x10,PTR__ZSt7nothrow_02cb9a80);
      if (lVar6 != 0) {
        Framework::CCamera2D::CCamera2D()(lVar6);
      }
      Framework::CCamera2D::Initialize()(lVar6);
      uVar15 = *(undefined8 *)(*(long *)PTR__ZN4Aska6Global16m_pObjectManagerE_02cc4688 + 0x4478);
      Aska::RenderLayer::AddLayer(unsigned char, unsigned char)(uVar15,0xe5,1);
      Aska::RenderLayer::AddLayer(unsigned char, unsigned char)(uVar15,0xe6,0x12);
      Aska::RenderLayer::AddLayer(unsigned char, unsigned char)(uVar15,0xe7,0x11);
      Aska::RenderLayer::AddLayer(unsigned char, unsigned char)(uVar15,0xe8,0x11);
      Aska::RenderLayer::AddLayer(unsigned char, unsigned char)(uVar15,0xe9,1);
      Aska::RenderLayer::AddLayer(unsigned char, unsigned char)(uVar15,0xea,0x12);
      Aska::RenderLayer::AddLayer(unsigned char, unsigned char)(uVar15,0xeb,0x12);
      Aska::RenderLayer::AddLayer(unsigned char, unsigned char)(uVar15,0xec,1);
      Aska::Global::InitializePeripheralManager()();
      lVar6 = operator new(unsigned long, std::nothrow_t const&)(0x110,PTR__ZSt7nothrow_02cb9a80);
      if (lVar6 != 0) {
        Framework::CPad::CPad()();
      }
      puVar3 = PTR__ZN9Framework10TSingletonINS_4CPadEE11m_pInstanceE_02cbef78;
      lVar6 = *(long *)PTR__ZN9Framework10TSingletonINS_4CPadEE11m_pInstanceE_02cbef78;
      if (lVar6 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029612b1/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
        lVar6 = *(long *)puVar3;
      }
      Framework::CPad::Initialize()(lVar6);
      lVar6 = operator new(unsigned long, std::nothrow_t const&)(0x1c,PTR__ZSt7nothrow_02cb9a80);
      puVar3 = PTR__ZN9Framework10TSingletonINS_6CMouseEE11m_pInstanceE_02cc1de0;
      if (lVar6 == 0) {
        lVar6 = *(long *)PTR__ZN9Framework10TSingletonINS_6CMouseEE11m_pInstanceE_02cc1de0;
      }
      else {
        if (*(long *)PTR__ZN9Framework10TSingletonINS_6CMouseEE11m_pInstanceE_02cc1de0 != 0) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029612b1/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TSingleton.h"*/,0x15,&UNK_027daee5/*"m_pInstance isn't null.(%08x)"*/);
        }
        *(long *)puVar3 = lVar6;
      }
      if (lVar6 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029612b1/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
        lVar6 = *(long *)PTR__ZN9Framework10TSingletonINS_6CMouseEE11m_pInstanceE_02cc1de0;
      }
      Framework::CMouse::Initialize()(lVar6);
      lVar6 = operator new(unsigned long, std::nothrow_t const&)(0x900,PTR__ZSt7nothrow_02cb9a80);
      puVar3 = PTR__ZN9Framework10TSingletonINS_9CKeyboardEE11m_pInstanceE_02cbebc8;
      if (lVar6 == 0) {
        lVar6 = *(long *)PTR__ZN9Framework10TSingletonINS_9CKeyboardEE11m_pInstanceE_02cbebc8;
      }
      else {
        if (*(long *)PTR__ZN9Framework10TSingletonINS_9CKeyboardEE11m_pInstanceE_02cbebc8 != 0) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029612b1/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TSingleton.h"*/,0x15,&UNK_027daee5/*"m_pInstance isn't null.(%08x)"*/);
        }
        *(long *)puVar3 = lVar6;
      }
      if (lVar6 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029612b1/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
        lVar6 = *(long *)PTR__ZN9Framework10TSingletonINS_9CKeyboardEE11m_pInstanceE_02cbebc8;
      }
      Framework::CKeyboard::Initialize()(lVar6);
      lVar6 = operator new(unsigned long, std::nothrow_t const&)(0x26b0,PTR__ZSt7nothrow_02cb9a80);
      if (lVar6 != 0) {
        Framework::CTouchPanel::CTouchPanel()();
      }
      puVar3 = PTR__ZN9Framework10TSingletonINS_11CTouchPanelEE11m_pInstanceE_02cbd318;
      lVar6 = *(long *)PTR__ZN9Framework10TSingletonINS_11CTouchPanelEE11m_pInstanceE_02cbd318;
      if (lVar6 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029612b1/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
        lVar6 = *(long *)puVar3;
      }
      Framework::CTouchPanel::Initialize()(lVar6);
      lVar6 = operator new(unsigned long, std::nothrow_t const&)(1,PTR__ZSt7nothrow_02cb9a80);
      puVar3 = PTR__ZN9Framework10TSingletonINS_3CGPEE11m_pInstanceE_02cba880;
      if (lVar6 == 0) {
        lVar6 = *(long *)PTR__ZN9Framework10TSingletonINS_3CGPEE11m_pInstanceE_02cba880;
      }
      else {
        if (*(long *)PTR__ZN9Framework10TSingletonINS_3CGPEE11m_pInstanceE_02cba880 != 0) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029612b1/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TSingleton.h"*/,0x15,&UNK_027daee5/*"m_pInstance isn't null.(%08x)"*/);
        }
        *(long *)puVar3 = lVar6;
      }
      if (lVar6 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029612b1/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
        lVar6 = *(long *)PTR__ZN9Framework10TSingletonINS_3CGPEE11m_pInstanceE_02cba880;
      }
      Framework::CGP::Initialize()(lVar6);
      lVar6 = operator new(unsigned long, std::nothrow_t const&)(0x50,PTR__ZSt7nothrow_02cb9a80);
      if (lVar6 != 0) {
        Framework::CFiberKernel::CFiberKernel(unsigned int)(lVar6,0x600);
      }
      *(long *)(param_1 + 0x90) = lVar6;
      Framework::CFiberKernel::Initialize()(lVar6);
      *(undefined8 *)(*(long *)PTR__ZN4Aska6Global8m_pVSyncE_02cbd460 + 0x130) = 0x10000003c;
      lVar6 = operator new(unsigned long, std::nothrow_t const&)(0x58,PTR__ZSt7nothrow_02cb9a80);
      if (lVar6 != 0) {
        Framework::CFader::CFader()(lVar6);
      }
      *(long *)(param_1 + 0x48) = lVar6;
      Framework::CFader::Initialize(unsigned int, float)(0,lVar6,0xe7);
      (**(code **)(**(long **)(param_1 + 0x90) + 0x48))
                (*(long **)(param_1 + 0x90),*(undefined8 *)(param_1 + 0x48));
      lVar6 = operator new(unsigned long, std::nothrow_t const&)(0x20,PTR__ZSt7nothrow_02cb9a80);
      if (lVar6 != 0) {
        Framework::CFaderView_Color::CFaderView_Color()(lVar6);
      }
      *(long *)(param_1 + 0x50) = lVar6;
      Framework::CFaderView_Color::Initialize(unsigned int)(lVar6,0);
      Framework::CFader::Attach(Framework::CFader::CView_Base&)(*(undefined8 *)(param_1 + 0x48),*(undefined8 *)(param_1 + 0x50));
      lVar6 = operator new(unsigned long, std::nothrow_t const&)(0xf0,PTR__ZSt7nothrow_02cb9a80);
      if (lVar6 != 0) {
        Framework::CResourceManager::CResourceManager(char const*)(lVar6,&UNK_0295bf43/*"Application"*/);
      }
      *(long *)(param_1 + 0x60) = lVar6;
      Framework::CResourceManager::Initialize()(lVar6);
      lVar6 = operator new(unsigned long, std::nothrow_t const&)(0x88,PTR__ZSt7nothrow_02cb9a80);
      if (lVar6 != 0) {
        Framework::CSoundManager::CSoundManager()(lVar6);
      }
      *(long *)(param_1 + 0x58) = lVar6;
      Framework::CSoundManager::Initialize(unsigned int)(lVar6,0x20);
      lVar6 = operator new(unsigned long, std::nothrow_t const&)(0x58,PTR__ZSt7nothrow_02cb9a80);
      if (lVar6 != 0) {
        Framework::ResponderChain::CManager::CManager()(lVar6);
      }
      *(long *)(param_1 + 0xe0) = lVar6;
      Framework::ResponderChain::CManager::Initialize()(lVar6);
      Framework::CISO::Set(unsigned int)(param_1 + 0x40,0);
      *(undefined2 *)(param_1 + 0x6e) = 0;
      lVar6 = operator new(unsigned long, std::nothrow_t const&)(0xc10,PTR__ZSt7nothrow_02cb9a80);
      if (lVar6 != 0) {
        Framework::Cocos::CCocosDirector::CCocosDirector()();
      }
      puVar3 = PTR__ZN9Framework10TSingletonINS_5Cocos14CCocosDirectorEE11m_pInstanceE_02cc2fe8;
      lVar6 = *(long *)
               PTR__ZN9Framework10TSingletonINS_5Cocos14CCocosDirectorEE11m_pInstanceE_02cc2fe8;
      if (lVar6 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029612b1/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
        lVar6 = *(long *)puVar3;
      }
      Framework::Cocos::CCocosDirector::Initialize()(lVar6);
      Framework::gMakeBuildDateAndTime(char*, unsigned long)(param_1 + 0x70,0x1f);
      puVar3 = PTR__ZN9Framework10TSingletonINS_5IGameEE11m_pInstanceE_02cc1a70;
      plVar7 = *(long **)PTR__ZN9Framework10TSingletonINS_5IGameEE11m_pInstanceE_02cc1a70;
      if (plVar7 == (long *)0x0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029612b1/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
        plVar7 = *(long **)puVar3;
      }
      (**(code **)(*plVar7 + 8))();
      iVar9 = *(int *)(param_1 + 0x28);
      goto code_r0x01f63a2c;
    }
    plVar7 = *(long **)PTR__ZN9Framework10TSingletonINS_5IGameEE11m_pInstanceE_02cc1a70;
    if (plVar7 == (long *)0x0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029612b1/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
      plVar7 = *(long **)puVar3;
    }
    uVar8 = (**(code **)(*plVar7 + 0x10))();
    if ((uVar8 & 1) != 0) goto code_r0x01f63a34;
    iVar9 = 10;
    *(undefined4 *)(param_1 + 0x68) = 0;
    *(undefined1 *)(param_1 + 0x6c) = 0;
  }
  *(int *)(param_1 + 0x28) = iVar9;
code_r0x01f63a34:
  *(int *)(param_1 + 0x2c) = *(int *)(param_1 + 0x2c) + 1;
  return;
}

// ==== Framework::CApplication::CAskaAppWithoutAPE::~CAskaAppWithoutAPE()
// vaddr 0x1e63a90 | ghidra 0x1f63a90 | size 72 | symbol _ZN9Framework12CApplication18CAskaAppWithoutAPED0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework12CApplication18CAskaAppWithoutAPED0Ev(undefined8 param_1)

{
  undefined *puVar1;
  
  puVar1 = 
  PTR__ZN9Framework10TSingletonINS_12CApplication18CAskaAppWithoutAPEEE11m_pInstanceE_02cc2f60;
  if (*(long *)
       PTR__ZN9Framework10TSingletonINS_12CApplication18CAskaAppWithoutAPEEE11m_pInstanceE_02cc2f60
      == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029612b1/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TSingleton.h"*/,0x1d,&UNK_027daf21/*"m_pInstance is null."*/);
  }
  *(undefined8 *)puVar1 = 0;
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Framework::CApplication::CMainTask::GetClassID(int) const
// vaddr 0x1e63b08 | ghidra 0x1f63b08 | size 60 | symbol _ZNK9Framework12CApplication9CMainTask10GetClassIDEi | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK9Framework12CApplication9CMainTask10GetClassIDEi(undefined8 param_1,int param_2)

{
  undefined8 uVar1;
  undefined8 uVar2;
  
  uVar2 = 0xf000f001;
  if (param_2 != 0) {
    if (param_2 != 2) {
      uVar2 = 0xf000;
    }
    uVar1 = 0xf000f001f002;
    if (param_2 != 1) {
      uVar1 = uVar2;
    }
    return uVar1;
  }
  return 0xf0021001;
}

// ==== Framework::CApplication::CMainTask::GetDefaultLevel() const
// vaddr 0x1e63b44 | ghidra 0x1f63b44 | size 8 | symbol _ZNK9Framework12CApplication9CMainTask15GetDefaultLevelEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK9Framework12CApplication9CMainTask15GetDefaultLevelEv(void)

{
  return 0x40;
}

// ==== Aska::LifeCycleManager::LifeCycleManager()
// vaddr 0x1f0530c | ghidra 0x200530c | size 4 | symbol _ZN4Aska16LifeCycleManagerC2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16LifeCycleManagerC1Ev(void)

{
  return;
}

// ==== Aska::LifeCycleManager::~LifeCycleManager()
// vaddr 0x1f05310 | ghidra 0x2005310 | size 4 | symbol _ZN4Aska16LifeCycleManagerD1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16LifeCycleManagerD2Ev(void)

{
  return;
}

// ==== Aska::LifeCycleManager::SetAppLifeCycle(int)
// vaddr 0x1f05314 | ghidra 0x2005314 | size 372 | symbol _ZN4Aska16LifeCycleManager15SetAppLifeCycleEi | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Possible PIC construction at 0x020053cc: Changing call to branch */
/* WARNING: Possible PIC construction at 0x02005350: Changing call to branch */
/* WARNING: Removing unreachable block (ram,0x02005354) */
/* WARNING: Removing unreachable block (ram,0x02005358) */

void _ZN4Aska16LifeCycleManager15SetAppLifeCycleEi(int param_1)

{
  code *UNRECOVERED_JUMPTABLE;
  long *plVar1;
  
  if (0xe < param_1 - 1U) {
    return;
  }
  plVar1 = *(long **)PTR__ZN4Aska6Global6m_pAppE_02cc2078;
  switch(param_1) {
  case 1:
    Aska::LifeCycleManager::AppInitWindow()();
    goto code_r0x011cba00;
  case 2:
    Aska::LifeCycleManager::AppTermWindow()();
    if (plVar1 != (long *)0x0) {
      UNRECOVERED_JUMPTABLE = *(code **)(*plVar1 + 0x58);
code_r0x02005434:
                    /* WARNING: Could not recover jumptable at 0x0200543c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (*UNRECOVERED_JUMPTABLE)(plVar1);
      return;
    }
    break;
  case 6:
    Aska::LifeCycleManager::AppGainedFocusWindow()();
    if (plVar1 != (long *)0x0) {
      (**(code **)(*plVar1 + 0x68))(plVar1);
    }
    goto code_r0x011cba00;
  case 7:
    Aska::LifeCycleManager::AppLostFocusWindow()();
    if (plVar1 != (long *)0x0) {
      UNRECOVERED_JUMPTABLE = *(code **)(*plVar1 + 0x60);
      goto code_r0x02005434;
    }
    break;
  case 9:
    if (plVar1 != (long *)0x0) {
      UNRECOVERED_JUMPTABLE = *(code **)(*plVar1 + 0x70);
      goto code_r0x02005434;
    }
    break;
  case 10:
    Aska::LifeCycleManager::AppStartWindow()();
    if (*(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50 != 0) {
code_r0x011d7210:
      (*(code *)PTR__ZN4Aska12SoundManager15ResumeInterruptEv_02ca38f8)();
      return;
    }
    uRam0000000002d00a50 =
         *(undefined8 *)
          (**(long **)(*(long *)PTR__ZN4Aska6Global13m_pAndroidAppE_02cc2688 + 0x18) + 0x18);
    *(undefined **)
     (**(long **)(*(long *)PTR__ZN4Aska6Global13m_pAndroidAppE_02cc2688 + 0x18) + 0x18) =
         &UNK_02005d30;
    Aska::VSync::InitializeForAndroid()(*(undefined8 *)PTR__ZN4Aska6Global8m_pVSyncE_02cbd460);
    goto code_r0x011cba00;
  case 0xb:
    if (*(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50 != 0) goto code_r0x011d7210;
    break;
  case 0xc:
    if (plVar1 != (long *)0x0) {
      UNRECOVERED_JUMPTABLE = *(code **)(*plVar1 + 0x78);
      goto code_r0x02005434;
    }
    break;
  case 0xe:
    if (*(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50 != 0) {
      (*(code *)PTR__ZN4Aska12SoundManager14PauseInterruptEv_02c96568)();
      return;
    }
    break;
  case 0xf:
    if (plVar1 != (long *)0x0) {
      (**(code **)(*plVar1 + 0x80))(plVar1);
    }
    Aska::LifeCycleManager::AppDestroyWindow()();
code_r0x011cba00:
    (*(code *)PTR__ZNK4Aska5Event3SetEv_02c9dcf0)(PTR__ZN4Aska5VSync8m_evSyncE_02cbe9f8);
    return;
  }
  return;
}

// ==== Aska::LifeCycleManager::AppInitWindow()
// vaddr 0x1f05488 | ghidra 0x2005488 | size 464 | symbol _ZN4Aska16LifeCycleManager13AppInitWindowEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16LifeCycleManager13AppInitWindowEv(void)

{
  int *piVar1;
  uint uVar2;
  char cVar3;
  bool bVar4;
  undefined *puVar5;
  undefined *puVar6;
  ulong uVar7;
  int iVar8;
  
  puVar5 = PTR__ZN4Aska16LifeCycleManager5m_criE_02cbb920;
  if (cRam0000000002d00a58 != '\x01') {
    Aska::RenderDeviceGL::InitDisplay()(*(undefined8 *)PTR__ZN4Aska12g_pRenderDevE_02cbb1a0);
    cRam0000000002d00a58 = 1;
    return;
  }
  piVar1 = (int *)(PTR__ZN4Aska16LifeCycleManager5m_criE_02cbb920 + 0x38);
  iVar8 = 0;
  do {
    while (*piVar1 == -1) {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(puVar5 + 0x38,0x10);
      if (bVar4) {
        *(undefined4 *)(puVar5 + 0x38) = 0;
        cVar3 = ExclusiveMonitorsStatus();
      }
      if (cVar3 == '\0') goto code_r0x020055b0;
    }
    ClearExclusiveLocal();
    bVar4 = iVar8 < 0x1ff;
    iVar8 = iVar8 + 1;
  } while (bVar4);
  piVar1 = (int *)(puVar5 + 0x3c);
  do {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar4) {
      *piVar1 = *piVar1 + 1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
  do {
    if (*(int *)(puVar5 + 0x38) != -1) {
      ClearExclusiveLocal();
      do {
        uVar7 = Aska::Semaphore::IsReady() const(puVar5 + 0x78);
        if ((uVar7 & 1) == 0) {
          do {
            piVar1 = (int *)(puVar5 + 0x3c);
            cVar3 = '\x01';
            bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
            if (bVar4) {
              *piVar1 = *piVar1 + -1;
              cVar3 = ExclusiveMonitorsStatus();
            }
          } while (cVar3 != '\0');
          Aska::Thread::Sleep(unsigned int)(1);
        }
        else {
          Aska::Semaphore::Wait() const(puVar5 + 0x78);
        }
        do {
          piVar1 = (int *)(puVar5 + 0x3c);
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar4) {
            *piVar1 = *piVar1 + 1;
            cVar3 = ExclusiveMonitorsStatus();
          }
        } while (cVar3 != '\0');
        while (piVar1 = (int *)(puVar5 + 0x38), *piVar1 == -1) {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar4) {
            *piVar1 = 0;
            cVar3 = ExclusiveMonitorsStatus();
          }
          if (cVar3 == '\0') goto code_r0x0200559c;
        }
        ClearExclusiveLocal();
      } while( true );
    }
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(puVar5 + 0x38,0x10);
    if (bVar4) {
      *(undefined4 *)(puVar5 + 0x38) = 0;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
code_r0x0200559c:
  do {
    piVar1 = (int *)(puVar5 + 0x3c);
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar4) {
      *piVar1 = *piVar1 + -1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
code_r0x020055b0:
  puVar6 = PTR__ZN4Aska16LifeCycleManager16m_LifeCycleStateE_02cc00a0;
  DataMemoryBarrier(2,3);
  uVar2 = *(uint *)(PTR__ZN4Aska16LifeCycleManager16m_LifeCycleStateE_02cc00a0 + 8);
  if (*(uint *)(PTR__ZN4Aska16LifeCycleManager16m_LifeCycleStateE_02cc00a0 + 0xc) != uVar2) {
    iVar8 = 0;
    if (uVar2 + 1 < 0x25) {
      iVar8 = uVar2 + 1;
    }
    *(undefined4 *)
     (PTR__ZN4Aska16LifeCycleManager16m_LifeCycleStateE_02cc00a0 + (ulong)uVar2 * 4 + 0x10) = 1;
    *(int *)(puVar6 + 8) = iVar8;
  }
  DataMemoryBarrier(2,3);
  *(undefined4 *)(puVar5 + 0x38) = 0xffffffff;
  DataMemoryBarrier(2,3);
  if (0x14 < *(int *)(puVar5 + 0x3c)) {
    piVar1 = (int *)(puVar5 + 0x3c);
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
    uVar7 = Aska::Semaphore::IsReady() const(puVar5 + 0x78);
    if ((uVar7 & 1) != 0) {
      Aska::Semaphore::Signal() const(puVar5 + 0x78);
    }
  }
  if (*(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50 == 0) {
    return;
  }
  (*(code *)PTR__ZN4Aska12SoundManager15ResumeInterruptEv_02ca38f8)();
  return;
}

// ==== Aska::LifeCycleManager::AppGainedFocusWindow()
// vaddr 0x1f05658 | ghidra 0x2005658 | size 420 | symbol _ZN4Aska16LifeCycleManager20AppGainedFocusWindowEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16LifeCycleManager20AppGainedFocusWindowEv(void)

{
  int *piVar1;
  uint uVar2;
  char cVar3;
  bool bVar4;
  undefined *puVar5;
  undefined *puVar6;
  ulong uVar7;
  int iVar8;
  
  puVar5 = PTR__ZN4Aska16LifeCycleManager5m_criE_02cbb920;
  piVar1 = (int *)(PTR__ZN4Aska16LifeCycleManager5m_criE_02cbb920 + 0x38);
  iVar8 = 0;
  do {
    while (*piVar1 == -1) {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(puVar5 + 0x38,0x10);
      if (bVar4) {
        *(undefined4 *)(puVar5 + 0x38) = 0;
        cVar3 = ExclusiveMonitorsStatus();
      }
      if (cVar3 == '\0') goto code_r0x02005754;
    }
    ClearExclusiveLocal();
    bVar4 = iVar8 < 0x1ff;
    iVar8 = iVar8 + 1;
  } while (bVar4);
  piVar1 = (int *)(puVar5 + 0x3c);
  do {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar4) {
      *piVar1 = *piVar1 + 1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
  do {
    if (*(int *)(puVar5 + 0x38) != -1) {
      ClearExclusiveLocal();
      do {
        uVar7 = Aska::Semaphore::IsReady() const(puVar5 + 0x78);
        if ((uVar7 & 1) == 0) {
          do {
            piVar1 = (int *)(puVar5 + 0x3c);
            cVar3 = '\x01';
            bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
            if (bVar4) {
              *piVar1 = *piVar1 + -1;
              cVar3 = ExclusiveMonitorsStatus();
            }
          } while (cVar3 != '\0');
          Aska::Thread::Sleep(unsigned int)(1);
        }
        else {
          Aska::Semaphore::Wait() const(puVar5 + 0x78);
        }
        do {
          piVar1 = (int *)(puVar5 + 0x3c);
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar4) {
            *piVar1 = *piVar1 + 1;
            cVar3 = ExclusiveMonitorsStatus();
          }
        } while (cVar3 != '\0');
        while (piVar1 = (int *)(puVar5 + 0x38), *piVar1 == -1) {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar4) {
            *piVar1 = 0;
            cVar3 = ExclusiveMonitorsStatus();
          }
          if (cVar3 == '\0') goto code_r0x02005740;
        }
        ClearExclusiveLocal();
      } while( true );
    }
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(puVar5 + 0x38,0x10);
    if (bVar4) {
      *(undefined4 *)(puVar5 + 0x38) = 0;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
code_r0x02005740:
  do {
    piVar1 = (int *)(puVar5 + 0x3c);
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar4) {
      *piVar1 = *piVar1 + -1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
code_r0x02005754:
  puVar6 = PTR__ZN4Aska16LifeCycleManager16m_LifeCycleStateE_02cc00a0;
  DataMemoryBarrier(2,3);
  uVar2 = *(uint *)(PTR__ZN4Aska16LifeCycleManager16m_LifeCycleStateE_02cc00a0 + 8);
  if (*(uint *)(PTR__ZN4Aska16LifeCycleManager16m_LifeCycleStateE_02cc00a0 + 0xc) != uVar2) {
    iVar8 = 0;
    if (uVar2 + 1 < 0x25) {
      iVar8 = uVar2 + 1;
    }
    *(undefined4 *)
     (PTR__ZN4Aska16LifeCycleManager16m_LifeCycleStateE_02cc00a0 + (ulong)uVar2 * 4 + 0x10) = 2;
    *(int *)(puVar6 + 8) = iVar8;
  }
  DataMemoryBarrier(2,3);
  *(undefined4 *)(puVar5 + 0x38) = 0xffffffff;
  DataMemoryBarrier(2,3);
  if (0x14 < *(int *)(puVar5 + 0x3c)) {
    piVar1 = (int *)(puVar5 + 0x3c);
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
    uVar7 = Aska::Semaphore::IsReady() const(puVar5 + 0x78);
    if ((uVar7 & 1) != 0) {
      Aska::Semaphore::Signal() const(puVar5 + 0x78);
    }
  }
  if (*(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50 == 0) {
    return;
  }
  (*(code *)PTR__ZN4Aska12SoundManager15ResumeInterruptEv_02ca38f8)();
  return;
}

// ==== Aska::LifeCycleManager::AppLostFocusWindow()
// vaddr 0x1f057fc | ghidra 0x20057fc | size 456 | symbol _ZN4Aska16LifeCycleManager18AppLostFocusWindowEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16LifeCycleManager18AppLostFocusWindowEv(void)

{
  int *piVar1;
  uint uVar2;
  char cVar3;
  bool bVar4;
  undefined *puVar5;
  undefined *puVar6;
  long lVar7;
  ulong uVar8;
  int iVar9;
  
  lVar7 = Aska::Global::GetPeripheral(int)(0);
  puVar5 = PTR__ZN4Aska8PadDroid7m_bBackE_02cb9e10;
  if (lVar7 != 0) {
    *PTR__ZN4Aska8PadDroid7m_bMenuE_02cbc870 = 0;
    *puVar5 = 0;
  }
  puVar5 = PTR__ZN4Aska16LifeCycleManager5m_criE_02cbb920;
  piVar1 = (int *)(PTR__ZN4Aska16LifeCycleManager5m_criE_02cbb920 + 0x38);
  iVar9 = 0;
  do {
    while (*piVar1 == -1) {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(puVar5 + 0x38,0x10);
      if (bVar4) {
        *(undefined4 *)(puVar5 + 0x38) = 0;
        cVar3 = ExclusiveMonitorsStatus();
      }
      if (cVar3 == '\0') goto code_r0x0200591c;
    }
    ClearExclusiveLocal();
    bVar4 = iVar9 < 0x1ff;
    iVar9 = iVar9 + 1;
  } while (bVar4);
  piVar1 = (int *)(puVar5 + 0x3c);
  do {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar4) {
      *piVar1 = *piVar1 + 1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
  do {
    if (*(int *)(puVar5 + 0x38) != -1) {
      ClearExclusiveLocal();
      do {
        uVar8 = Aska::Semaphore::IsReady() const(puVar5 + 0x78);
        if ((uVar8 & 1) == 0) {
          do {
            piVar1 = (int *)(puVar5 + 0x3c);
            cVar3 = '\x01';
            bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
            if (bVar4) {
              *piVar1 = *piVar1 + -1;
              cVar3 = ExclusiveMonitorsStatus();
            }
          } while (cVar3 != '\0');
          Aska::Thread::Sleep(unsigned int)(1);
        }
        else {
          Aska::Semaphore::Wait() const(puVar5 + 0x78);
        }
        do {
          piVar1 = (int *)(puVar5 + 0x3c);
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar4) {
            *piVar1 = *piVar1 + 1;
            cVar3 = ExclusiveMonitorsStatus();
          }
        } while (cVar3 != '\0');
        while (piVar1 = (int *)(puVar5 + 0x38), *piVar1 == -1) {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar4) {
            *piVar1 = 0;
            cVar3 = ExclusiveMonitorsStatus();
          }
          if (cVar3 == '\0') goto code_r0x02005908;
        }
        ClearExclusiveLocal();
      } while( true );
    }
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(puVar5 + 0x38,0x10);
    if (bVar4) {
      *(undefined4 *)(puVar5 + 0x38) = 0;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
code_r0x02005908:
  do {
    piVar1 = (int *)(puVar5 + 0x3c);
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar4) {
      *piVar1 = *piVar1 + -1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
code_r0x0200591c:
  puVar6 = PTR__ZN4Aska16LifeCycleManager16m_LifeCycleStateE_02cc00a0;
  DataMemoryBarrier(2,3);
  uVar2 = *(uint *)(PTR__ZN4Aska16LifeCycleManager16m_LifeCycleStateE_02cc00a0 + 8);
  if (*(uint *)(PTR__ZN4Aska16LifeCycleManager16m_LifeCycleStateE_02cc00a0 + 0xc) != uVar2) {
    iVar9 = 0;
    if (uVar2 + 1 < 0x25) {
      iVar9 = uVar2 + 1;
    }
    *(undefined4 *)
     (PTR__ZN4Aska16LifeCycleManager16m_LifeCycleStateE_02cc00a0 + (ulong)uVar2 * 4 + 0x10) = 4;
    *(int *)(puVar6 + 8) = iVar9;
  }
  DataMemoryBarrier(2,3);
  *(undefined4 *)(puVar5 + 0x38) = 0xffffffff;
  DataMemoryBarrier(2,3);
  if (0x14 < *(int *)(puVar5 + 0x3c)) {
    piVar1 = (int *)(puVar5 + 0x3c);
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
    uVar8 = Aska::Semaphore::IsReady() const(puVar5 + 0x78);
    if ((uVar8 & 1) != 0) {
      Aska::Semaphore::Signal() const(puVar5 + 0x78);
    }
  }
  if (*(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50 == 0) {
    return;
  }
  (*(code *)PTR__ZN4Aska12SoundManager14PauseInterruptEv_02c96568)();
  return;
}

// ==== Aska::LifeCycleManager::AppTermWindow()
// vaddr 0x1f059c4 | ghidra 0x20059c4 | size 456 | symbol _ZN4Aska16LifeCycleManager13AppTermWindowEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16LifeCycleManager13AppTermWindowEv(void)

{
  int *piVar1;
  uint uVar2;
  char cVar3;
  bool bVar4;
  undefined *puVar5;
  undefined *puVar6;
  long lVar7;
  ulong uVar8;
  int iVar9;
  
  lVar7 = Aska::Global::GetPeripheral(int)(0);
  puVar5 = PTR__ZN4Aska8PadDroid7m_bBackE_02cb9e10;
  if (lVar7 != 0) {
    *PTR__ZN4Aska8PadDroid7m_bMenuE_02cbc870 = 0;
    *puVar5 = 0;
  }
  puVar5 = PTR__ZN4Aska16LifeCycleManager5m_criE_02cbb920;
  piVar1 = (int *)(PTR__ZN4Aska16LifeCycleManager5m_criE_02cbb920 + 0x38);
  iVar9 = 0;
  do {
    while (*piVar1 == -1) {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(puVar5 + 0x38,0x10);
      if (bVar4) {
        *(undefined4 *)(puVar5 + 0x38) = 0;
        cVar3 = ExclusiveMonitorsStatus();
      }
      if (cVar3 == '\0') goto code_r0x02005ae4;
    }
    ClearExclusiveLocal();
    bVar4 = iVar9 < 0x1ff;
    iVar9 = iVar9 + 1;
  } while (bVar4);
  piVar1 = (int *)(puVar5 + 0x3c);
  do {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar4) {
      *piVar1 = *piVar1 + 1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
  do {
    if (*(int *)(puVar5 + 0x38) != -1) {
      ClearExclusiveLocal();
      do {
        uVar8 = Aska::Semaphore::IsReady() const(puVar5 + 0x78);
        if ((uVar8 & 1) == 0) {
          do {
            piVar1 = (int *)(puVar5 + 0x3c);
            cVar3 = '\x01';
            bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
            if (bVar4) {
              *piVar1 = *piVar1 + -1;
              cVar3 = ExclusiveMonitorsStatus();
            }
          } while (cVar3 != '\0');
          Aska::Thread::Sleep(unsigned int)(1);
        }
        else {
          Aska::Semaphore::Wait() const(puVar5 + 0x78);
        }
        do {
          piVar1 = (int *)(puVar5 + 0x3c);
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar4) {
            *piVar1 = *piVar1 + 1;
            cVar3 = ExclusiveMonitorsStatus();
          }
        } while (cVar3 != '\0');
        while (piVar1 = (int *)(puVar5 + 0x38), *piVar1 == -1) {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar4) {
            *piVar1 = 0;
            cVar3 = ExclusiveMonitorsStatus();
          }
          if (cVar3 == '\0') goto code_r0x02005ad0;
        }
        ClearExclusiveLocal();
      } while( true );
    }
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(puVar5 + 0x38,0x10);
    if (bVar4) {
      *(undefined4 *)(puVar5 + 0x38) = 0;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
code_r0x02005ad0:
  do {
    piVar1 = (int *)(puVar5 + 0x3c);
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar4) {
      *piVar1 = *piVar1 + -1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
code_r0x02005ae4:
  puVar6 = PTR__ZN4Aska16LifeCycleManager16m_LifeCycleStateE_02cc00a0;
  DataMemoryBarrier(2,3);
  uVar2 = *(uint *)(PTR__ZN4Aska16LifeCycleManager16m_LifeCycleStateE_02cc00a0 + 8);
  if (*(uint *)(PTR__ZN4Aska16LifeCycleManager16m_LifeCycleStateE_02cc00a0 + 0xc) != uVar2) {
    iVar9 = 0;
    if (uVar2 + 1 < 0x25) {
      iVar9 = uVar2 + 1;
    }
    *(undefined4 *)
     (PTR__ZN4Aska16LifeCycleManager16m_LifeCycleStateE_02cc00a0 + (ulong)uVar2 * 4 + 0x10) = 3;
    *(int *)(puVar6 + 8) = iVar9;
  }
  DataMemoryBarrier(2,3);
  *(undefined4 *)(puVar5 + 0x38) = 0xffffffff;
  DataMemoryBarrier(2,3);
  if (0x14 < *(int *)(puVar5 + 0x3c)) {
    piVar1 = (int *)(puVar5 + 0x3c);
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
    uVar8 = Aska::Semaphore::IsReady() const(puVar5 + 0x78);
    if ((uVar8 & 1) != 0) {
      Aska::Semaphore::Signal() const(puVar5 + 0x78);
    }
  }
  if (*(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50 == 0) {
    return;
  }
  (*(code *)PTR__ZN4Aska12SoundManager14PauseInterruptEv_02c96568)();
  return;
}

// ==== Aska::LifeCycleManager::AppStartWindow()
// vaddr 0x1f05b8c | ghidra 0x2005b8c | size 396 | symbol _ZN4Aska16LifeCycleManager14AppStartWindowEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16LifeCycleManager14AppStartWindowEv(void)

{
  int *piVar1;
  uint uVar2;
  char cVar3;
  bool bVar4;
  undefined *puVar5;
  undefined *puVar6;
  ulong uVar7;
  int iVar8;
  
  puVar5 = PTR__ZN4Aska16LifeCycleManager5m_criE_02cbb920;
  piVar1 = (int *)(PTR__ZN4Aska16LifeCycleManager5m_criE_02cbb920 + 0x38);
  iVar8 = 0;
  do {
    while (*piVar1 == -1) {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(puVar5 + 0x38,0x10);
      if (bVar4) {
        *(undefined4 *)(puVar5 + 0x38) = 0;
        cVar3 = ExclusiveMonitorsStatus();
      }
      if (cVar3 == '\0') goto code_r0x02005c88;
    }
    ClearExclusiveLocal();
    bVar4 = iVar8 < 0x1ff;
    iVar8 = iVar8 + 1;
  } while (bVar4);
  piVar1 = (int *)(puVar5 + 0x3c);
  do {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar4) {
      *piVar1 = *piVar1 + 1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
  do {
    if (*(int *)(puVar5 + 0x38) != -1) {
      ClearExclusiveLocal();
      do {
        uVar7 = Aska::Semaphore::IsReady() const(puVar5 + 0x78);
        if ((uVar7 & 1) == 0) {
          do {
            piVar1 = (int *)(puVar5 + 0x3c);
            cVar3 = '\x01';
            bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
            if (bVar4) {
              *piVar1 = *piVar1 + -1;
              cVar3 = ExclusiveMonitorsStatus();
            }
          } while (cVar3 != '\0');
          Aska::Thread::Sleep(unsigned int)(1);
        }
        else {
          Aska::Semaphore::Wait() const(puVar5 + 0x78);
        }
        do {
          piVar1 = (int *)(puVar5 + 0x3c);
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar4) {
            *piVar1 = *piVar1 + 1;
            cVar3 = ExclusiveMonitorsStatus();
          }
        } while (cVar3 != '\0');
        while (piVar1 = (int *)(puVar5 + 0x38), *piVar1 == -1) {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar4) {
            *piVar1 = 0;
            cVar3 = ExclusiveMonitorsStatus();
          }
          if (cVar3 == '\0') goto code_r0x02005c74;
        }
        ClearExclusiveLocal();
      } while( true );
    }
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(puVar5 + 0x38,0x10);
    if (bVar4) {
      *(undefined4 *)(puVar5 + 0x38) = 0;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
code_r0x02005c74:
  do {
    piVar1 = (int *)(puVar5 + 0x3c);
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar4) {
      *piVar1 = *piVar1 + -1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
code_r0x02005c88:
  puVar6 = PTR__ZN4Aska16LifeCycleManager16m_LifeCycleStateE_02cc00a0;
  DataMemoryBarrier(2,3);
  uVar2 = *(uint *)(PTR__ZN4Aska16LifeCycleManager16m_LifeCycleStateE_02cc00a0 + 8);
  if (*(uint *)(PTR__ZN4Aska16LifeCycleManager16m_LifeCycleStateE_02cc00a0 + 0xc) != uVar2) {
    iVar8 = 0;
    if (uVar2 + 1 < 0x25) {
      iVar8 = uVar2 + 1;
    }
    *(undefined4 *)
     (PTR__ZN4Aska16LifeCycleManager16m_LifeCycleStateE_02cc00a0 + (ulong)uVar2 * 4 + 0x10) = 0;
    *(int *)(puVar6 + 8) = iVar8;
  }
  DataMemoryBarrier(2,3);
  *(undefined4 *)(puVar5 + 0x38) = 0xffffffff;
  DataMemoryBarrier(2,3);
  if (0x14 < *(int *)(puVar5 + 0x3c)) {
    piVar1 = (int *)(puVar5 + 0x3c);
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
    uVar7 = Aska::Semaphore::IsReady() const(puVar5 + 0x78);
    if ((uVar7 & 1) != 0) {
      (*(code *)PTR__ZNK4Aska9Semaphore6SignalEv_02c96cd0)(puVar5 + 0x78);
      return;
    }
  }
  return;
}

// ==== Aska::LifeCycleManager::ResumeSound()
// vaddr 0x1f05d18 | ghidra 0x2005d18 | size 24 | symbol _ZN4Aska16LifeCycleManager11ResumeSoundEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16LifeCycleManager11ResumeSoundEv(void)

{
  if (*(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50 != 0) {
    (*(code *)PTR__ZN4Aska12SoundManager15ResumeInterruptEv_02ca38f8)();
    return;
  }
  return;
}

// ==== Aska::LifeCycleManager::AppDestroyWindow()
// vaddr 0x1f05d7c | ghidra 0x2005d7c | size 408 | symbol _ZN4Aska16LifeCycleManager16AppDestroyWindowEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16LifeCycleManager16AppDestroyWindowEv(void)

{
  int *piVar1;
  uint uVar2;
  char cVar3;
  bool bVar4;
  undefined *puVar5;
  undefined *puVar6;
  ulong uVar7;
  int iVar8;
  
  Aska::Global::RequestExit(Aska::Global::ExitState::E)(1);
  puVar5 = PTR__ZN4Aska16LifeCycleManager5m_criE_02cbb920;
  piVar1 = (int *)(PTR__ZN4Aska16LifeCycleManager5m_criE_02cbb920 + 0x38);
  iVar8 = 0;
  do {
    while (*piVar1 == -1) {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(puVar5 + 0x38,0x10);
      if (bVar4) {
        *(undefined4 *)(puVar5 + 0x38) = 0;
        cVar3 = ExclusiveMonitorsStatus();
      }
      if (cVar3 == '\0') goto code_r0x02005e80;
    }
    ClearExclusiveLocal();
    bVar4 = iVar8 < 0x1ff;
    iVar8 = iVar8 + 1;
  } while (bVar4);
  piVar1 = (int *)(puVar5 + 0x3c);
  do {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar4) {
      *piVar1 = *piVar1 + 1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
  do {
    if (*(int *)(puVar5 + 0x38) != -1) {
      ClearExclusiveLocal();
      do {
        uVar7 = Aska::Semaphore::IsReady() const(puVar5 + 0x78);
        if ((uVar7 & 1) == 0) {
          do {
            piVar1 = (int *)(puVar5 + 0x3c);
            cVar3 = '\x01';
            bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
            if (bVar4) {
              *piVar1 = *piVar1 + -1;
              cVar3 = ExclusiveMonitorsStatus();
            }
          } while (cVar3 != '\0');
          Aska::Thread::Sleep(unsigned int)(1);
        }
        else {
          Aska::Semaphore::Wait() const(puVar5 + 0x78);
        }
        do {
          piVar1 = (int *)(puVar5 + 0x3c);
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar4) {
            *piVar1 = *piVar1 + 1;
            cVar3 = ExclusiveMonitorsStatus();
          }
        } while (cVar3 != '\0');
        while (piVar1 = (int *)(puVar5 + 0x38), *piVar1 == -1) {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar4) {
            *piVar1 = 0;
            cVar3 = ExclusiveMonitorsStatus();
          }
          if (cVar3 == '\0') goto code_r0x02005e6c;
        }
        ClearExclusiveLocal();
      } while( true );
    }
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(puVar5 + 0x38,0x10);
    if (bVar4) {
      *(undefined4 *)(puVar5 + 0x38) = 0;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
code_r0x02005e6c:
  do {
    piVar1 = (int *)(puVar5 + 0x3c);
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar4) {
      *piVar1 = *piVar1 + -1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
code_r0x02005e80:
  puVar6 = PTR__ZN4Aska16LifeCycleManager16m_LifeCycleStateE_02cc00a0;
  DataMemoryBarrier(2,3);
  uVar2 = *(uint *)(PTR__ZN4Aska16LifeCycleManager16m_LifeCycleStateE_02cc00a0 + 8);
  if (*(uint *)(PTR__ZN4Aska16LifeCycleManager16m_LifeCycleStateE_02cc00a0 + 0xc) != uVar2) {
    iVar8 = 0;
    if (uVar2 + 1 < 0x25) {
      iVar8 = uVar2 + 1;
    }
    *(undefined4 *)
     (PTR__ZN4Aska16LifeCycleManager16m_LifeCycleStateE_02cc00a0 + (ulong)uVar2 * 4 + 0x10) = 8;
    *(int *)(puVar6 + 8) = iVar8;
  }
  DataMemoryBarrier(2,3);
  *(undefined4 *)(puVar5 + 0x38) = 0xffffffff;
  DataMemoryBarrier(2,3);
  if (0x14 < *(int *)(puVar5 + 0x3c)) {
    piVar1 = (int *)(puVar5 + 0x3c);
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
    uVar7 = Aska::Semaphore::IsReady() const(puVar5 + 0x78);
    if ((uVar7 & 1) != 0) {
      (*(code *)PTR__ZNK4Aska9Semaphore6SignalEv_02c96cd0)(puVar5 + 0x78);
      return;
    }
  }
  return;
}

// ==== Aska::LifeCycleManager::PauseSound()
// vaddr 0x1f05f14 | ghidra 0x2005f14 | size 24 | symbol _ZN4Aska16LifeCycleManager10PauseSoundEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16LifeCycleManager10PauseSoundEv(void)

{
  if (*(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50 != 0) {
    (*(code *)PTR__ZN4Aska12SoundManager14PauseInterruptEv_02c96568)();
    return;
  }
  return;
}

// ==== Aska::LifeCycleManager::SurfaceControl()
// vaddr 0x1f05f2c | ghidra 0x2005f2c | size 504 | symbol _ZN4Aska16LifeCycleManager14SurfaceControlEv | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Removing unreachable block (ram,0x02005f9c) */

undefined8 _ZN4Aska16LifeCycleManager14SurfaceControlEv(void)

{
  char cVar1;
  char cVar2;
  bool bVar3;
  bool bVar4;
  bool bVar5;
  bool bVar6;
  undefined *puVar7;
  undefined *puVar8;
  undefined *puVar9;
  bool bVar10;
  bool bVar11;
  int iVar12;
  
  puVar9 = PTR__ZN4Aska16LifeCycleManager16m_LifeCycleStateE_02cc00a0;
  puVar8 = PTR__ZN4Aska16LifeCycleManager13m_bHasSurfaceE_02cbd440;
  puVar7 = PTR__ZN4Aska16LifeCycleManager14m_bNowFocusingE_02cbc468;
  cVar1 = *PTR__ZN4Aska16LifeCycleManager13m_bHasSurfaceE_02cbd440;
  cVar2 = *PTR__ZN4Aska16LifeCycleManager14m_bNowFocusingE_02cbc468;
  bVar10 = cVar1 != '\0';
  bVar11 = cVar2 != '\0';
  iVar12 = 0;
  if (*(int *)(PTR__ZN4Aska16LifeCycleManager16m_LifeCycleStateE_02cc00a0 + 0xc) + 1 < 0x25) {
    iVar12 = *(int *)(PTR__ZN4Aska16LifeCycleManager16m_LifeCycleStateE_02cc00a0 + 0xc) + 1;
  }
  if (iVar12 == *(int *)(PTR__ZN4Aska16LifeCycleManager16m_LifeCycleStateE_02cc00a0 + 8)) {
    bVar6 = false;
    bVar5 = false;
    bVar4 = false;
code_r0x0200605c:
    if ((bool)cVar1 == bVar10) goto code_r0x02006094;
  }
  else {
    bVar5 = false;
    bVar6 = false;
    bVar3 = false;
    do {
      switch(*(undefined4 *)(puVar9 + (long)iVar12 * 4 + 0x10)) {
      case 0:
        bVar4 = true;
        iVar12 = 0;
        if (*(int *)(puVar9 + 0xc) + 1 < 0x25) {
          iVar12 = *(int *)(puVar9 + 0xc) + 1;
        }
        *(int *)(puVar9 + 0xc) = iVar12;
        if (bVar3) goto code_r0x02006068;
        goto code_r0x0200605c;
      case 1:
        bVar10 = true;
        bVar3 = true;
        break;
      case 2:
        bVar10 = true;
        bVar11 = true;
        bVar6 = true;
        break;
      case 3:
        bVar10 = false;
        bVar3 = true;
        break;
      case 4:
        bVar11 = false;
        break;
      case 8:
        bVar5 = true;
      }
      iVar12 = 0;
      if (*(int *)(puVar9 + 0xc) + 1 < 0x25) {
        iVar12 = *(int *)(puVar9 + 0xc) + 1;
      }
      *(int *)(puVar9 + 0xc) = iVar12;
      iVar12 = 0;
      if (*(int *)(puVar9 + 0xc) + 1 < 0x25) {
        iVar12 = *(int *)(puVar9 + 0xc) + 1;
      }
    } while (iVar12 != *(int *)(puVar9 + 8));
    bVar4 = false;
    if (!bVar3) goto code_r0x0200605c;
  }
code_r0x02006068:
  if (bVar10 == false) {
    Aska::RenderDeviceGL::DeleteSurface(bool)(*(undefined8 *)PTR__ZN4Aska12g_pRenderDevE_02cbb1a0,1);
  }
  else {
    Aska::RenderDeviceGL::ReCreateSurface()();
  }
  cVar2 = *puVar7;
  *puVar8 = bVar10;
code_r0x02006094:
  if (bVar6 || (bool)cVar2 != bVar11) {
    if (bVar11 == false) {
      if (!bVar4) {
        Aska::RenderDeviceGL::SetActive(bool)(*(undefined8 *)PTR__ZN4Aska12g_pRenderDevE_02cbb1a0,0);
        Aska::Event::Reset() const(PTR__ZN4Aska5VSync8m_evSyncE_02cbe9f8);
      }
    }
    else {
      Aska::RenderDeviceGL::SetActive(bool)(*(undefined8 *)PTR__ZN4Aska12g_pRenderDevE_02cbb1a0,1);
      Aska::Event::Set() const(PTR__ZN4Aska5VSync8m_evSyncE_02cbe9f8);
    }
    *puVar7 = bVar11;
  }
  if (bVar5) {
    Aska::Event::Set() const(PTR__ZN4Aska5VSync8m_evSyncE_02cbe9f8);
  }
  return 0;
}

// ==== Aska::AskaMainThread::~AskaMainThread()
// vaddr 0x1f17c08 | ghidra 0x2017c08 | size 32 | symbol _ZN4Aska14AskaMainThreadD2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska14AskaMainThreadD2Ev(long *param_1)

{
  undefined4 uVar1;
  
  *param_1 = (long)(PTR__ZTVN4Aska14AskaMainThreadE_02cc20f8 + 0x10);
  uVar1 = *(undefined4 *)PTR__ZN4Aska6Global15m_ExitRequestedE_02cc3650;
  (*(code *)PTR__ZN4Aska6ThreadD1Ev_02c9be08)();
  return;
}

// ==== Aska::AskaMainThread::~AskaMainThread()
// vaddr 0x1f17c6c | ghidra 0x2017c6c | size 52 | symbol _ZN4Aska14AskaMainThreadD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska14AskaMainThreadD0Ev(long *param_1)

{
  undefined4 uVar1;
  
  *param_1 = (long)(PTR__ZTVN4Aska14AskaMainThreadE_02cc20f8 + 0x10);
  uVar1 = *(undefined4 *)PTR__ZN4Aska6Global15m_ExitRequestedE_02cc3650;
  Aska::Thread::~Thread()();
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::AskaMainThread::Handler()
// vaddr 0x1f17ca0 | ghidra 0x2017ca0 | size 132 | symbol _ZN4Aska14AskaMainThread7HandlerEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska14AskaMainThread7HandlerEv(void)

{
  undefined *puVar1;
  ulong uVar2;
  undefined8 uVar3;
  long lVar4;
  
  uVar2 = Aska::Global::InitAll()();
  if ((((uVar2 & 1) != 0) &&
      (uVar2 = Aska::Global::PostInit()(), puVar1 = PTR__ZN4Aska6Global6m_pAppE_02cc2078, (uVar2 & 1) != 0))
     && (3 < *(int *)(*(long *)PTR__ZN4Aska12g_pRenderDevE_02cbb1a0 + 0xec0b8))) {
    lVar4 = *(long *)PTR__ZN4Aska6Global6m_pAppE_02cc2078;
    if (lVar4 != 0) {
      uVar3 = Aska::Thread::GetCurrentID()();
      *(undefined8 *)(lVar4 + 0x108) = uVar3;
      (**(code **)(**(long **)puVar1 + 0x20))();
    }
    Aska::Global::PreDelete()();
    Aska::DeleteAska()();
    Aska::Global::DeleteAll()();
    *PTR__ZN4Aska4Boot7bIsLoopE_02cc2380 = 0;
  }
  return;
}


// FAILED to create function at 02961310 typeinfo name for Framework::CApplication::CAskaAppWithoutAPE
// FAILED to create function at 02961350 typeinfo name for Framework::TSingleton<Framework::CApplication::CAskaAppWithoutAPE>
// FAILED to create function at 029613a0 typeinfo name for Framework::CApplication::CMainTask
// FAILED to create function at 029613d0 typeinfo name for Framework::TSingleton<Framework::CApplication::CMainTask>
// FAILED to create function at 02ba6e38 Framework::CApplication::CMainTask::vtable
// FAILED to create function at 02ba6ee0 Framework::CApplication::CAskaAppWithoutAPE::vtable
// FAILED to create function at 02ba6f88 Framework::TSingleton<Framework::CApplication::CAskaAppWithoutAPE>::typeinfo
// FAILED to create function at 02ba6fa0 Framework::CApplication::CAskaAppWithoutAPE::typeinfo
// FAILED to create function at 02ba6fd8 Framework::TSingleton<Framework::CApplication::CMainTask>::typeinfo
// FAILED to create function at 02ba6ff0 Framework::CApplication::CMainTask::typeinfo
// FAILED to create function at 02bb02d8 Aska::AskaMainThread::vtable
// FAILED to create function at 02bb0300 Aska::AskaMainThread::typeinfo
// FAILED to create function at 02cc70e0 Aska::LifeCycleManager::m_bIsDroidLoop
// FAILED to create function at 02cc70e1 Aska::LifeCycleManager::m_bHasActivityLifeCycleControl
// FAILED to create function at 02ceb310 Framework::TSingleton<Framework::CApplication::CMainTask>::m_pInstance
// FAILED to create function at 02d00050 Framework::CApplication::m_FrameworkArguments
// FAILED to create function at 02d00248 Framework::TSingleton<Framework::CApplication::CAskaAppWithoutAPE>::m_pInstance
// FAILED to create function at 02d00910 Aska::LifeCycleManager::m_LifeCycleState
// FAILED to create function at 02d009b8 Aska::LifeCycleManager::m_bNowFocusing
// FAILED to create function at 02d009b9 Aska::LifeCycleManager::m_bHasSurface
// FAILED to create function at 02d009c0 Aska::LifeCycleManager::m_cri
