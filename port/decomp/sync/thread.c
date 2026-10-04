// port/decomp/sync/thread.c: Ghidra decompiles for the sync subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-04 05:03 UTC: tools/decomp.sh '--into' 'sync/thread' 'Aska::Thread::' 'Framework::CThread::' 'Aska::GPUSync::'

// ==== Framework::CThread::CSubstance::CSubstance()
// vaddr 0x1e9e468 | ghidra 0x1f9e468 | size 40 | symbol _ZN9Framework7CThread10CSubstanceC2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework7CThread10CSubstanceC1Ev(long *param_1)

{
  undefined *puVar1;
  
  Aska::Thread::Thread()();
  puVar1 = PTR__ZTVN9Framework7CThread10CSubstanceE_02cba628;
  param_1[3] = 0;
  *param_1 = (long)(puVar1 + 0x10);
  return;
}

// ==== Framework::CThread::CSubstance::~CSubstance()
// vaddr 0x1e9e490 | ghidra 0x1f9e490 | size 56 | symbol _ZN9Framework7CThread10CSubstanceD2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework7CThread10CSubstanceD1Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN9Framework7CThread10CSubstanceE_02cba628 + 0x10);
  if (param_1[3] != 0) {
    param_1[3] = 0;
    Aska::Thread::Delete()(param_1);
  }
  (*(code *)PTR__ZN4Aska6ThreadD1Ev_02c9be08)(param_1);
  return;
}

// ==== Framework::CThread::CSubstance::~CSubstance()
// vaddr 0x1e9e4c8 | ghidra 0x1f9e4c8 | size 64 | symbol _ZN9Framework7CThread10CSubstanceD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework7CThread10CSubstanceD0Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN9Framework7CThread10CSubstanceE_02cba628 + 0x10);
  if (param_1[3] != 0) {
    param_1[3] = 0;
    Aska::Thread::Delete()(param_1);
  }
  Aska::Thread::~Thread()(param_1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Framework::CThread::CSubstance::CreateAskaThread(Framework::CThread&, char const*, int, unsigned int, unsigned long)
// vaddr 0x1e9e508 | ghidra 0x1f9e508 | size 112 | symbol _ZN9Framework7CThread10CSubstance16CreateAskaThreadERS0_PKcijm | lib libSOA-3.7.0.so | 2026-10-04
uint _ZN9Framework7CThread10CSubstance16CreateAskaThreadERS0_PKcijm
               (long param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               undefined4 param_5,undefined4 param_6)

{
  uint uVar1;
  
  if (*(long *)(param_1 + 0x18) != 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029664cd/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Thread.cpp"*/,0x47,&UNK_027daee5/*"m_pInstance isn't null.(%08x)"*/);
  }
  uVar1 = Aska::Thread::Create(bool, int, int, bool)(param_1,1,param_5,param_6,1);
  if ((uVar1 & 1) != 0) {
    *(undefined8 *)(param_1 + 0x18) = param_2;
  }
  return uVar1 & 1;
}

// ==== Framework::CThread::CSubstance::IsCreated() const
// vaddr 0x1e9e578 | ghidra 0x1f9e578 | size 16 | symbol _ZNK9Framework7CThread10CSubstance9IsCreatedEv | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK9Framework7CThread10CSubstance9IsCreatedEv(long param_1)

{
  return *(long *)(param_1 + 0x18) != 0;
}

// ==== Framework::CThread::CSubstance::Handler()
// vaddr 0x1e9e588 | ghidra 0x1f9e588 | size 148 | symbol _ZN9Framework7CThread10CSubstance7HandlerEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework7CThread10CSubstance7HandlerEv(long param_1)

{
  long *plVar1;
  undefined8 *puVar2;
  long lVar3;
  
  plVar1 = *(long **)(param_1 + 0x18);
  if (plVar1 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029664cd/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Thread.cpp"*/,0x5d,&UNK_027daf21/*"m_pInstance is null."*/);
    plVar1 = *(long **)(param_1 + 0x18);
  }
  (**(code **)(*plVar1 + 0x10))();
  lVar3 = *(long *)(param_1 + 0x18);
  if (*(char *)(lVar3 + 0x28) == '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029664cd/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Thread.cpp"*/,0x94,&UNK_02966564/*"m_IsExecuting is null."*/);
  }
  puVar2 = *(undefined8 **)(lVar3 + 0x30);
  *(undefined1 *)(lVar3 + 0x28) = 0;
  if (puVar2 != (undefined8 *)0x0) {
    (**(code **)*puVar2)(puVar2,*(undefined4 *)(lVar3 + 0x38),lVar3);
  }
  *(undefined8 *)(param_1 + 0x18) = 0;
  (*(code *)PTR__ZN4Aska6Thread6DeleteEv_02cb0b58)(param_1);
  return;
}

// ==== Framework::CThread::ToTerminate()
// vaddr 0x1e9e61c | ghidra 0x1f9e61c | size 84 | symbol _ZN9Framework7CThread11ToTerminateEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework7CThread11ToTerminateEv(long param_1)

{
  undefined8 *puVar1;
  
  if (*(char *)(param_1 + 0x28) == '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029664cd/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Thread.cpp"*/,0x94,&UNK_02966564/*"m_IsExecuting is null."*/);
  }
  puVar1 = *(undefined8 **)(param_1 + 0x30);
  *(undefined1 *)(param_1 + 0x28) = 0;
  if (puVar1 != (undefined8 *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x01f9e664. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)*puVar1)(puVar1,*(undefined4 *)(param_1 + 0x38),param_1);
    return;
  }
  return;
}

// ==== Framework::CThread::CThread()
// vaddr 0x1e9e670 | ghidra 0x1f9e670 | size 64 | symbol _ZN9Framework7CThreadC2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework7CThreadC2Ev(long *param_1)

{
  undefined *puVar1;
  
  *param_1 = (long)(PTR__ZTVN9Framework7CThreadE_02cc48a0 + 0x10);
  Aska::Thread::Thread()(param_1 + 1);
  puVar1 = PTR__ZTVN9Framework7CThread10CSubstanceE_02cba628;
  param_1[4] = 0;
  *(undefined1 *)(param_1 + 5) = 0;
  param_1[1] = (long)(puVar1 + 0x10);
  return;
}

// ==== Framework::CThread::~CThread()
// vaddr 0x1e9e6b0 | ghidra 0x1f9e6b0 | size 76 | symbol _ZN9Framework7CThreadD1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework7CThreadD2Ev(long *param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZTVN9Framework7CThreadE_02cc48a0 + 0x10;
  param_1[1] = (long)(PTR__ZTVN9Framework7CThread10CSubstanceE_02cba628 + 0x10);
  *param_1 = (long)puVar1;
  if (param_1[4] != 0) {
    param_1[4] = 0;
    Aska::Thread::Delete()(param_1 + 1);
  }
  (*(code *)PTR__ZN4Aska6ThreadD1Ev_02c9be08)(param_1 + 1);
  return;
}

// ==== Framework::CThread::~CThread()
// vaddr 0x1e9e6fc | ghidra 0x1f9e6fc | size 4 | symbol _ZN9Framework7CThreadD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework7CThreadD0Ev(void)

{
  code *pcVar1;
  
                    /* WARNING: Does not return */
  pcVar1 = (code *)SoftwareBreakpoint(1,0x1f9e700);
  (*pcVar1)();
}

// ==== Framework::CThread::Create(char const*, int, unsigned int, unsigned long)
// vaddr 0x1e9e700 | ghidra 0x1f9e700 | size 180 | symbol _ZN9Framework7CThread6CreateEPKcijm | lib libSOA-3.7.0.so | 2026-10-04
uint _ZN9Framework7CThread6CreateEPKcijm
               (long param_1,undefined8 param_2,undefined8 param_3,undefined4 param_4,
               undefined4 param_5)

{
  uint uVar1;
  
  if (*(char *)(param_1 + 0x28) != '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029664cd/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Thread.cpp"*/,0x7f,&UNK_0296651f/*"Already executing."*/);
  }
  if (*(long *)(param_1 + 0x20) != 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029664cd/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Thread.cpp"*/,0x80,&UNK_02966532/*"Already created."*/);
    if (*(long *)(param_1 + 0x20) != 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029664cd/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Thread.cpp"*/,0x47,&UNK_027daee5/*"m_pInstance isn't null.(%08x)"*/);
    }
  }
  uVar1 = Aska::Thread::Create(bool, int, int, bool)(param_1 + 8,1,param_4,param_5,1);
  if ((uVar1 & 1) != 0) {
    *(long *)(param_1 + 0x20) = param_1;
    *(undefined8 *)(param_1 + 0x30) = 0;
  }
  return uVar1 & 1;
}

// ==== Framework::CThread::Resume()
// vaddr 0x1e9e7b4 | ghidra 0x1f9e7b4 | size 88 | symbol _ZN9Framework7CThread6ResumeEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework7CThread6ResumeEv(long param_1)

{
  if (*(char *)(param_1 + 0x28) != '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029664cd/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Thread.cpp"*/,0x8b,&UNK_0296651f/*"Already executing."*/);
  }
  if (*(long *)(param_1 + 0x20) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029664cd/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Thread.cpp"*/,0x8c,&UNK_02966543/*"m_Substance.IsCreated() is null."*/);
  }
  *(undefined1 *)(param_1 + 0x28) = 1;
  return;
}

// ==== Framework::CThread::IsTerminated() const
// vaddr 0x1e9e80c | ghidra 0x1f9e80c | size 16 | symbol _ZNK9Framework7CThread12IsTerminatedEv | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK9Framework7CThread12IsTerminatedEv(long param_1)

{
  return *(char *)(param_1 + 0x28) == '\0';
}

// ==== Framework::CThread::TerminateCallback(Framework::ICallback&, unsigned int)
// vaddr 0x1e9e81c | ghidra 0x1f9e81c | size 12 | symbol _ZN9Framework7CThread17TerminateCallbackERNS_9ICallbackEj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework7CThread17TerminateCallbackERNS_9ICallbackEj
               (long param_1,undefined8 param_2,undefined4 param_3)

{
  *(undefined8 *)(param_1 + 0x30) = param_2;
  *(undefined4 *)(param_1 + 0x38) = param_3;
  return;
}

// ==== Framework::CThread::rAskaThread()
// vaddr 0x1e9e828 | ghidra 0x1f9e828 | size 52 | symbol _ZN9Framework7CThread11rAskaThreadEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZN9Framework7CThread11rAskaThreadEv(long param_1)

{
  if (*(long *)(param_1 + 0x20) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029664cd/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Thread.cpp"*/,0xb0,&UNK_0296657b/*"Not created, yet."*/);
  }
  return param_1 + 8;
}

// ==== Aska::Thread::Thread()
// vaddr 0x1f83f04 | ghidra 0x2083f04 | size 20 | symbol _ZN4Aska6ThreadC1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6ThreadC2Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska6ThreadE_02cbcf78 + 0x10);
  param_1[1] = 0;
  return;
}

// ==== Aska::Thread::~Thread()
// vaddr 0x1f83f18 | ghidra 0x2083f18 | size 52 | symbol _ZN4Aska6ThreadD2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6ThreadD1Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska6ThreadE_02cbcf78 + 0x10);
  if (param_1[1] != 0) {
    pthread_join(param_1[1],0);
  }
  param_1[1] = 0;
  return;
}

// ==== Aska::Thread::WaitEnd()
// vaddr 0x1f83f4c | ghidra 0x2083f4c | size 20 | symbol _ZN4Aska6Thread7WaitEndEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6Thread7WaitEndEv(long param_1)

{
  if (*(long *)(param_1 + 8) != 0) {
    (*(code *)PTR_pthread_join_02cac498)(*(long *)(param_1 + 8),0);
    return;
  }
  return;
}

// ==== Aska::Thread::Delete()
// vaddr 0x1f83f60 | ghidra 0x2083f60 | size 8 | symbol _ZN4Aska6Thread6DeleteEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6Thread6DeleteEv(long param_1)

{
  *(undefined8 *)(param_1 + 8) = 0;
  return;
}

// ==== Aska::Thread::~Thread()
// vaddr 0x1f83f68 | ghidra 0x2083f68 | size 52 | symbol _ZN4Aska6ThreadD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6ThreadD0Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska6ThreadE_02cbcf78 + 0x10);
  if (param_1[1] != 0) {
    pthread_join(param_1[1],0);
  }
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::Thread::Create(bool, int, int, bool)
// vaddr 0x1f83f9c | ghidra 0x2083f9c | size 328 | symbol _ZN4Aska6Thread6CreateEbiib | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 _ZN4Aska6Thread6CreateEbiib(long param_1,undefined8 param_2,uint param_3,int param_4)

{
  int iVar1;
  undefined *puVar2;
  undefined *puVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  undefined1 auStack_78 [36];
  int iStack_54;
  undefined8 uStack_40;
  ulong uStack_38;
  
  if (*(long *)(param_1 + 8) == 0) {
    pthread_attr_init(auStack_78);
    if (param_4 < 0x4001) {
      param_4 = 0x4000;
    }
    pthread_attr_setstacksize(auStack_78,param_4);
    iVar4 = pthread_attr_setschedpolicy(auStack_78,
                            *(undefined4 *)PTR__ZN4Aska6Thread20sThreadPrioritySchedE_02cc2b80);
    puVar3 = PTR__ZN4Aska6Thread19MIN_THREAD_PRIORITYE_02cbefc8;
    puVar2 = PTR__ZN4Aska6Thread19MAX_THREAD_PRIORITYE_02cba738;
    if (iVar4 == 0) {
      iVar4 = *(int *)PTR__ZN4Aska6Thread19MIN_THREAD_PRIORITYE_02cbefc8;
      iVar6 = *(int *)PTR__ZN4Aska6Thread19MAX_THREAD_PRIORITYE_02cba738;
      if (iVar6 == 0 && iVar4 == 0) {
        iVar4 = getrlimit(0xd,&uStack_40);
        if (iVar4 == 0) {
          iVar4 = (int)(uStack_38 >> 1);
          iVar6 = -iVar4;
          *(int *)puVar3 = iVar4;
          *(int *)puVar2 = iVar6;
        }
        else {
          iVar4 = *(int *)puVar3;
          iVar6 = *(int *)puVar2;
        }
        iVar1 = iVar6 - iVar4;
        if (iVar1 < 0) {
          iVar1 = iVar1 + 1;
        }
        *(int *)PTR__ZN4Aska6Thread23DEFAULT_THREAD_PRIORITYE_02cc1aa8 = iVar4 + (iVar1 >> 1);
      }
      iStack_54 = (int)(((float)param_3 / _UNK_028014f8) * (float)(iVar6 - iVar4) + (float)iVar4);
      iVar4 = pthread_create(&uStack_40,auStack_78,PTR__ZN4Aska6Thread4MainEPv_02cc4ea0,param_1);
      if (iVar4 == 0) {
        *(undefined8 *)(param_1 + 8) = uStack_40;
        uVar5 = pthread_gettid_np();
        setpriority(0,uVar5,iStack_54);
        return 1;
      }
    }
  }
  return 0;
}

// ==== Aska::Thread::ConvertToDependentPriority(unsigned int)
// vaddr 0x1f850e4 | ghidra 0x20850e4 | size 180 | symbol _ZN4Aska6Thread26ConvertToDependentPriorityEj | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int _ZN4Aska6Thread26ConvertToDependentPriorityEj(uint param_1)

{
  int iVar1;
  undefined *puVar2;
  undefined *puVar3;
  int iVar4;
  int iVar5;
  undefined1 auStack_30 [8];
  ulong uStack_28;
  
  puVar3 = PTR__ZN4Aska6Thread19MIN_THREAD_PRIORITYE_02cbefc8;
  puVar2 = PTR__ZN4Aska6Thread19MAX_THREAD_PRIORITYE_02cba738;
  iVar4 = *(int *)PTR__ZN4Aska6Thread19MIN_THREAD_PRIORITYE_02cbefc8;
  iVar5 = *(int *)PTR__ZN4Aska6Thread19MAX_THREAD_PRIORITYE_02cba738;
  if (iVar5 == 0 && iVar4 == 0) {
    iVar4 = getrlimit(0xd,auStack_30);
    if (iVar4 == 0) {
      iVar4 = (int)(uStack_28 >> 1);
      iVar5 = -iVar4;
      *(int *)puVar3 = iVar4;
      *(int *)puVar2 = iVar5;
    }
    else {
      iVar4 = *(int *)puVar3;
      iVar5 = *(int *)puVar2;
    }
    iVar1 = iVar5 - iVar4;
    if (iVar1 < 0) {
      iVar1 = iVar1 + 1;
    }
    *(int *)PTR__ZN4Aska6Thread23DEFAULT_THREAD_PRIORITYE_02cc1aa8 = iVar4 + (iVar1 >> 1);
  }
  return (int)(((float)param_1 / _UNK_028014f8) * (float)(iVar5 - iVar4) + (float)iVar4);
}

// ==== Aska::Thread::Main(void*)
// vaddr 0x1f85198 | ghidra 0x2085198 | size 28 | symbol _ZN4Aska6Thread4MainEPv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska6Thread4MainEPv(long *param_1)

{
  (**(code **)(*param_1 + 0x10))();
  return 0;
}

// ==== Aska::Thread::GetPriority() const
// vaddr 0x1f851b4 | ghidra 0x20851b4 | size 216 | symbol _ZNK4Aska6Thread11GetPriorityEv | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int _ZNK4Aska6Thread11GetPriorityEv(long param_1)

{
  int iVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined1 auStack_30 [8];
  ulong uStack_28;
  
  if (*(long *)(param_1 + 8) != 0) {
    uVar4 = pthread_gettid_np();
    iVar5 = getpriority(0,uVar4);
    puVar3 = PTR__ZN4Aska6Thread19MIN_THREAD_PRIORITYE_02cbefc8;
    puVar2 = PTR__ZN4Aska6Thread19MAX_THREAD_PRIORITYE_02cba738;
    iVar6 = *(int *)PTR__ZN4Aska6Thread19MIN_THREAD_PRIORITYE_02cbefc8;
    iVar7 = *(int *)PTR__ZN4Aska6Thread19MAX_THREAD_PRIORITYE_02cba738;
    if (iVar7 == 0 && iVar6 == 0) {
      iVar6 = getrlimit(0xd,auStack_30);
      if (iVar6 == 0) {
        iVar6 = (int)(uStack_28 >> 1);
        iVar7 = -iVar6;
        *(int *)puVar3 = iVar6;
        *(int *)puVar2 = iVar7;
      }
      else {
        iVar6 = *(int *)puVar3;
        iVar7 = *(int *)puVar2;
      }
      iVar1 = iVar7 - iVar6;
      if (iVar1 < 0) {
        iVar1 = iVar1 + 1;
      }
      *(int *)PTR__ZN4Aska6Thread23DEFAULT_THREAD_PRIORITYE_02cc1aa8 = iVar6 + (iVar1 >> 1);
    }
    return (int)(((float)(iVar5 - iVar6) / (float)(iVar7 - iVar6)) * _UNK_028014f8 + 0.0);
  }
  return -1;
}

// ==== Aska::Thread::ConvertToIndependentPriority(int)
// vaddr 0x1f8528c | ghidra 0x208528c | size 184 | symbol _ZN4Aska6Thread28ConvertToIndependentPriorityEi | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int _ZN4Aska6Thread28ConvertToIndependentPriorityEi(int param_1)

{
  int iVar1;
  undefined *puVar2;
  undefined *puVar3;
  int iVar4;
  int iVar5;
  undefined1 auStack_30 [8];
  ulong uStack_28;
  
  puVar3 = PTR__ZN4Aska6Thread19MIN_THREAD_PRIORITYE_02cbefc8;
  puVar2 = PTR__ZN4Aska6Thread19MAX_THREAD_PRIORITYE_02cba738;
  iVar4 = *(int *)PTR__ZN4Aska6Thread19MIN_THREAD_PRIORITYE_02cbefc8;
  iVar5 = *(int *)PTR__ZN4Aska6Thread19MAX_THREAD_PRIORITYE_02cba738;
  if (iVar5 == 0 && iVar4 == 0) {
    iVar4 = getrlimit(0xd,auStack_30);
    if (iVar4 == 0) {
      iVar4 = (int)(uStack_28 >> 1);
      iVar5 = -iVar4;
      *(int *)puVar3 = iVar4;
      *(int *)puVar2 = iVar5;
    }
    else {
      iVar4 = *(int *)puVar3;
      iVar5 = *(int *)puVar2;
    }
    iVar1 = iVar5 - iVar4;
    if (iVar1 < 0) {
      iVar1 = iVar1 + 1;
    }
    *(int *)PTR__ZN4Aska6Thread23DEFAULT_THREAD_PRIORITYE_02cc1aa8 = iVar4 + (iVar1 >> 1);
  }
  return (int)(((float)(param_1 - iVar4) / (float)(iVar5 - iVar4)) * _UNK_028014f8 + 0.0);
}

// ==== Aska::Thread::PosixPriorityToString(int)
// vaddr 0x1f85344 | ghidra 0x2085344 | size 8 | symbol _ZN4Aska6Thread21PosixPriorityToStringEi | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska6Thread21PosixPriorityToStringEi(void)

{
  return 0;
}

// ==== Aska::Thread::PosixInitThreadPriority()
// vaddr 0x1f8534c | ghidra 0x208534c | size 128 | symbol _ZN4Aska6Thread23PosixInitThreadPriorityEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6Thread23PosixInitThreadPriorityEv(void)

{
  int iVar1;
  int iVar2;
  undefined1 auStack_20 [8];
  ulong uStack_18;
  
  iVar1 = getrlimit(0xd,auStack_20);
  if (iVar1 == 0) {
    iVar2 = (int)(uStack_18 >> 1);
    *(int *)PTR__ZN4Aska6Thread19MIN_THREAD_PRIORITYE_02cbefc8 = iVar2;
    iVar1 = -iVar2;
    *(int *)PTR__ZN4Aska6Thread19MAX_THREAD_PRIORITYE_02cba738 = iVar1;
  }
  else {
    iVar2 = *(int *)PTR__ZN4Aska6Thread19MIN_THREAD_PRIORITYE_02cbefc8;
    iVar1 = *(int *)PTR__ZN4Aska6Thread19MAX_THREAD_PRIORITYE_02cba738;
  }
  iVar1 = iVar1 - iVar2;
  if (iVar1 < 0) {
    iVar1 = iVar1 + 1;
  }
  *(int *)PTR__ZN4Aska6Thread23DEFAULT_THREAD_PRIORITYE_02cc1aa8 = iVar2 + (iVar1 >> 1);
  return;
}

// ==== Aska::Thread::SetPriority(int)
// vaddr 0x1f853cc | ghidra 0x20853cc | size 224 | symbol _ZN4Aska6Thread11SetPriorityEi | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

bool _ZN4Aska6Thread11SetPriorityEi(long param_1,uint param_2)

{
  int iVar1;
  undefined *puVar2;
  undefined *puVar3;
  bool bVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  undefined1 auStack_40 [8];
  ulong uStack_38;
  
  bVar4 = false;
  if (*(long *)(param_1 + 8) != 0) {
    uVar5 = pthread_gettid_np();
    puVar3 = PTR__ZN4Aska6Thread19MIN_THREAD_PRIORITYE_02cbefc8;
    puVar2 = PTR__ZN4Aska6Thread19MAX_THREAD_PRIORITYE_02cba738;
    iVar6 = *(int *)PTR__ZN4Aska6Thread19MIN_THREAD_PRIORITYE_02cbefc8;
    iVar7 = *(int *)PTR__ZN4Aska6Thread19MAX_THREAD_PRIORITYE_02cba738;
    if (iVar7 == 0 && iVar6 == 0) {
      iVar6 = getrlimit(0xd,auStack_40);
      if (iVar6 == 0) {
        iVar6 = (int)(uStack_38 >> 1);
        iVar7 = -iVar6;
        *(int *)puVar3 = iVar6;
        *(int *)puVar2 = iVar7;
      }
      else {
        iVar6 = *(int *)puVar3;
        iVar7 = *(int *)puVar2;
      }
      iVar1 = iVar7 - iVar6;
      if (iVar1 < 0) {
        iVar1 = iVar1 + 1;
      }
      *(int *)PTR__ZN4Aska6Thread23DEFAULT_THREAD_PRIORITYE_02cc1aa8 = iVar6 + (iVar1 >> 1);
    }
    iVar6 = setpriority(0,uVar5,(int)(((float)param_2 / _UNK_028014f8) * (float)(iVar7 - iVar6)
                                         + (float)iVar6));
    bVar4 = iVar6 == 0;
  }
  return bVar4;
}

// ==== Aska::Thread::DeleteSignalHandler()
// vaddr 0x1f854ac | ghidra 0x20854ac | size 4 | symbol _ZN4Aska6Thread19DeleteSignalHandlerEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6Thread19DeleteSignalHandlerEv(void)

{
  return;
}

// ==== Aska::Thread::Exit()
// vaddr 0x1f854b0 | ghidra 0x20854b0 | size 12 | symbol _ZN4Aska6Thread4ExitEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6Thread4ExitEv(void)

{
  pthread_exit(0);
  (*(code *)PTR_pthread_self_02c95740)();
  return;
}

// ==== Aska::Thread::GetCurrentID()
// vaddr 0x1f854bc | ghidra 0x20854bc | size 4 | symbol _ZN4Aska6Thread12GetCurrentIDEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6Thread12GetCurrentIDEv(void)

{
  (*(code *)PTR_pthread_self_02c95740)();
  return;
}

// ==== Aska::Thread::Switch()
// vaddr 0x1f854c0 | ghidra 0x20854c0 | size 4 | symbol _ZN4Aska6Thread6SwitchEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6Thread6SwitchEv(void)

{
  return;
}

// ==== Aska::Thread::Sleep(unsigned int)
// vaddr 0x1f854c4 | ghidra 0x20854c4 | size 76 | symbol _ZN4Aska6Thread5SleepEj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6Thread5SleepEj(int param_1)

{
  ulong uStack_20;
  long lStack_18;
  
  uStack_20 = (ulong)(uint)(param_1 * 1000) / 1000000;
  lStack_18 = ((ulong)(uint)(param_1 * 1000) % 1000000) * 1000;
  nanosleep(&uStack_20,&uStack_20);
  return;
}

// ==== Aska::Thread::SleepU(unsigned int)
// vaddr 0x1f85510 | ghidra 0x2085510 | size 76 | symbol _ZN4Aska6Thread6SleepUEj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6Thread6SleepUEj(ulong param_1)

{
  ulong uStack_20;
  long lStack_18;
  
  uStack_20 = (param_1 & 0xffffffff) / 1000000;
  lStack_18 = ((param_1 & 0xffffffff) + uStack_20 * -1000000) * 1000;
  nanosleep(&uStack_20,&uStack_20);
  return;
}

// ==== Aska::Thread::CreateThreadKey()
// vaddr 0x1f8555c | ghidra 0x208555c | size 4 | symbol _ZN4Aska6Thread15CreateThreadKeyEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6Thread15CreateThreadKeyEv(void)

{
  return;
}

// ==== Aska::Thread::InitializeThreadSystem()
// vaddr 0x1f85560 | ghidra 0x2085560 | size 28 | symbol _ZN4Aska6Thread22InitializeThreadSystemEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6Thread22InitializeThreadSystemEv(void)

{
  undefined8 uVar1;
  
  uVar1 = pthread_self();
  *(undefined8 *)(PTR__ZN4Aska6Thread12m_mainThreadE_02cc3038 + 8) = uVar1;
  return;
}

// ==== Aska::Thread::Handler()
// vaddr 0x1f8557c | ghidra 0x208557c | size 4 | symbol _ZN4Aska6Thread7HandlerEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6Thread7HandlerEv(void)

{
  return;
}

// ==== Aska::GPUSync::WaitGPUSync()
// vaddr 0x21c4e30 | ghidra 0x22c4e30 | size 220 | symbol _ZN4Aska7GPUSync11WaitGPUSyncEv | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Possible PIC construction at 0x022c4e98: Changing call to branch */
/* WARNING: Possible PIC construction at 0x022c4ed8: Changing call to branch */
/* WARNING: Removing unreachable block (ram,0x022c4e9c) */
/* WARNING: Removing unreachable block (ram,0x022c4edc) */
/* WARNING: Removing unreachable block (ram,0x022c4ee4) */
/* WARNING: Removing unreachable block (ram,0x022c4ef4) */

void _ZN4Aska7GPUSync11WaitGPUSyncEv(long param_1)

{
  ulong uVar1;
  undefined *puStack_98;
  undefined1 *puStack_90;
  undefined1 auStack_88 [104];
  
  Aska::Semaphore::Wait() const(param_1 + 0xc0);
  if (*(char *)(param_1 + 0xb8) != '\0') {
    Aska::Event::Event()(auStack_88);
    uVar1 = Aska::Event::Create(bool, bool)(auStack_88,1,0);
    if ((uVar1 & 1) != 0) {
      puStack_98 = PTR__ZTVN4Aska11EventNotifyE_02cb7e68 + 0x10;
      puStack_90 = auStack_88;
      Aska::NotifierThread::AddNotify(Aska::INotify*, unsigned int)(param_1,&puStack_98,0);
    }
  }
  (*(code *)PTR__ZNK4Aska9Semaphore6SignalEv_02c96cd0)(param_1 + 0xc0);
  return;
}

// ==== Aska::GPUSync::Notify()
// vaddr 0x21c4f0c | ghidra 0x22c4f0c | size 72 | symbol _ZN4Aska7GPUSync6NotifyEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska7GPUSync6NotifyEv(long param_1)

{
  Aska::Semaphore::Wait() const(param_1 + 0xc0);
  *(undefined1 *)(param_1 + 0xb8) = 0;
  Aska::PerformanceCounter::Set(int)(*(undefined8 *)PTR__ZN4Aska6Global21m_pPerformanceCounterE_02cc3ad8,2);
  Aska::NotifierThread::Notify()(param_1);
  (*(code *)PTR__ZNK4Aska9Semaphore6SignalEv_02c96cd0)(param_1 + 0xc0);
  return;
}

// ==== Aska::GPUSync::~GPUSync()
// vaddr 0x21c53e0 | ghidra 0x22c53e0 | size 64 | symbol _ZN4Aska7GPUSyncD2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska7GPUSyncD2Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska7GPUSyncE_02cc05c8 + 0x10);
  Aska::Semaphore::Exit()(param_1 + 0x18);
  Aska::Semaphore::~Semaphore()(param_1 + 0x18);
  (*(code *)PTR__ZN4Aska14NotifierThreadD2Ev_02ca2268)(param_1);
  return;
}

// ==== Aska::GPUSync::~GPUSync()
// vaddr 0x21c5420 | ghidra 0x22c5420 | size 72 | symbol _ZN4Aska7GPUSyncD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska7GPUSyncD0Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska7GPUSyncE_02cc05c8 + 0x10);
  Aska::Semaphore::Exit()(param_1 + 0x18);
  Aska::Semaphore::~Semaphore()(param_1 + 0x18);
  Aska::NotifierThread::~NotifierThread()(param_1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}


// FAILED to create function at 029665b0 typeinfo name for Framework::CThread::CSubstance
// FAILED to create function at 02bab420 Framework::CThread::CSubstance::vtable
// FAILED to create function at 02bab448 Framework::CThread::vtable
// FAILED to create function at 02bab470 Framework::CThread::typeinfo
// FAILED to create function at 02bab480 Framework::CThread::CSubstance::typeinfo
// FAILED to create function at 02bb49c8 Aska::Thread::vtable
// FAILED to create function at 02bb49f0 Aska::Thread::typeinfo
// FAILED to create function at 02c54420 Aska::GPUSync::vtable
// FAILED to create function at 02c54460 Aska::GPUSync::typeinfo
// FAILED to create function at 02dcd918 Aska::Thread::MIN_THREAD_PRIORITY
// FAILED to create function at 02dcd91c Aska::Thread::MAX_THREAD_PRIORITY
// FAILED to create function at 02dcd920 Aska::Thread::DEFAULT_THREAD_PRIORITY
// FAILED to create function at 02dcd924 Aska::Thread::sThreadPrioritySched
// FAILED to create function at 02dcd928 Aska::Thread::m_mainThread
