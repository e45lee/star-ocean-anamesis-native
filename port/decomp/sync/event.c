// port/decomp/sync/event.c: Ghidra decompiles for the sync subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-04 05:03 UTC: tools/decomp.sh '--into' 'sync/event' 'Aska::Event::' 'Aska::Semaphore::' 'Aska::CriticalSection::' 'Aska::Mutex::'

// ==== Aska::CriticalSection::CriticalSection()
// vaddr 0x1f17f14 | ghidra 0x2017f14 | size 64 | symbol _ZN4Aska15CriticalSectionC2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska15CriticalSectionC1Ev(undefined8 param_1)

{
  undefined1 auStack_18 [8];
  
  pthread_mutexattr_init(auStack_18);
  pthread_mutexattr_settype(auStack_18,1);
  pthread_mutex_init(param_1,auStack_18);
  pthread_mutexattr_destroy(auStack_18);
  return;
}

// ==== Aska::CriticalSection::~CriticalSection()
// vaddr 0x1f17f54 | ghidra 0x2017f54 | size 4 | symbol _ZN4Aska15CriticalSectionD1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska15CriticalSectionD2Ev(void)

{
  (*(code *)PTR_pthread_mutex_destroy_02ca2f88)();
  return;
}

// ==== Aska::CriticalSection::Delete()
// vaddr 0x1f17f58 | ghidra 0x2017f58 | size 4 | symbol _ZN4Aska15CriticalSection6DeleteEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska15CriticalSection6DeleteEv(void)

{
  (*(code *)PTR_pthread_mutex_destroy_02ca2f88)();
  return;
}

// ==== Aska::CriticalSection::Enter() const
// vaddr 0x1f17f5c | ghidra 0x2017f5c | size 4 | symbol _ZNK4Aska15CriticalSection5EnterEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK4Aska15CriticalSection5EnterEv(void)

{
  (*(code *)PTR_pthread_mutex_lock_02c9dfb8)();
  return;
}

// ==== Aska::CriticalSection::TryEnter() const
// vaddr 0x1f17f60 | ghidra 0x2017f60 | size 24 | symbol _ZNK4Aska15CriticalSection8TryEnterEv | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK4Aska15CriticalSection8TryEnterEv(void)

{
  int iVar1;
  
  iVar1 = pthread_mutex_trylock();
  return iVar1 == 0;
}

// ==== Aska::CriticalSection::Leave() const
// vaddr 0x1f17f78 | ghidra 0x2017f78 | size 4 | symbol _ZNK4Aska15CriticalSection5LeaveEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK4Aska15CriticalSection5LeaveEv(void)

{
  (*(code *)PTR_pthread_mutex_unlock_02cb2c98)();
  return;
}

// ==== Aska::Event::Event()
// vaddr 0x1f1f2ec | ghidra 0x201f2ec | size 8 | symbol _ZN4Aska5EventC1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5EventC2Ev(undefined8 *param_1)

{
  *param_1 = 0;
  return;
}

// ==== Aska::Event::Create(bool, bool)
// vaddr 0x1f1f2f4 | ghidra 0x201f2f4 | size 92 | symbol _ZN4Aska5Event6CreateEbb | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska5Event6CreateEbb(long *param_1,byte param_2,byte param_3)

{
  if (*param_1 == 0) {
    pthread_mutex_init(param_1 + 1,0);
    pthread_cond_init(param_1 + 6,0);
    *param_1 = (long)(param_1 + 1);
    *(byte *)(param_1 + 0xc) = param_3 & 1;
    *(byte *)((long)param_1 + 0x61) = param_2 & 1;
  }
  return 1;
}

// ==== Aska::Event::Wait(unsigned int) const
// vaddr 0x1f1f350 | ghidra 0x201f350 | size 200 | symbol _ZNK4Aska5Event4WaitEj | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK4Aska5Event4WaitEj(long *param_1,int param_2)

{
  char cVar1;
  bool bVar2;
  int iVar3;
  undefined8 uStack_40;
  long lStack_38;
  undefined8 uStack_30;
  long lStack_28;
  
  bVar2 = false;
  if (*param_1 != 0) {
    pthread_mutex_lock();
    if ((char)param_1[0xc] == '\0') {
      if (param_2 == 0) {
        pthread_cond_wait(param_1 + 6,*param_1);
        cVar1 = *(char *)((long)param_1 + 0x61);
      }
      else {
        iVar3 = gettimeofday(&uStack_30,0);
        if (iVar3 < 0) {
          return false;
        }
        uStack_40 = uStack_30;
        lStack_38 = (ulong)(uint)(param_2 * 1000000) + lStack_28 * 1000;
        pthread_cond_timedwait(param_1 + 6,*param_1,&uStack_40);
        cVar1 = *(char *)((long)param_1 + 0x61);
      }
    }
    else {
      cVar1 = *(char *)((long)param_1 + 0x61);
    }
    if (cVar1 == '\0') {
      *(undefined1 *)(param_1 + 0xc) = 0;
    }
    iVar3 = pthread_mutex_unlock(*param_1);
    bVar2 = iVar3 != 0;
  }
  return bVar2;
}

// ==== Aska::Event::Set() const
// vaddr 0x1f1f418 | ghidra 0x201f418 | size 80 | symbol _ZNK4Aska5Event3SetEv | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK4Aska5Event3SetEv(long *param_1)

{
  bool bVar1;
  int iVar2;
  
  bVar1 = false;
  if (*param_1 != 0) {
    iVar2 = pthread_mutex_lock();
    if (iVar2 != 0) {
      return false;
    }
    *(undefined1 *)(param_1 + 0xc) = 1;
    pthread_cond_signal(param_1 + 6);
    iVar2 = pthread_mutex_unlock(*param_1);
    bVar1 = iVar2 == 0;
  }
  return bVar1;
}

// ==== Aska::Event::Reset() const
// vaddr 0x1f1f468 | ghidra 0x201f468 | size 64 | symbol _ZNK4Aska5Event5ResetEv | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK4Aska5Event5ResetEv(long *param_1)

{
  bool bVar1;
  int iVar2;
  
  bVar1 = false;
  if (*param_1 != 0) {
    iVar2 = pthread_mutex_lock();
    if (iVar2 != 0) {
      return false;
    }
    *(undefined1 *)(param_1 + 0xc) = 0;
    iVar2 = pthread_mutex_unlock(*param_1);
    bVar1 = iVar2 == 0;
  }
  return bVar1;
}

// ==== Aska::Event::IsSignal() const
// vaddr 0x1f1f4a8 | ghidra 0x201f4a8 | size 32 | symbol _ZNK4Aska5Event8IsSignalEv | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK4Aska5Event8IsSignalEv(long *param_1)

{
  if (*param_1 != 0) {
    return (char)param_1[0xc] != '\0';
  }
  return false;
}

// ==== Aska::Event::Exit()
// vaddr 0x1f1f4c8 | ghidra 0x201f4c8 | size 72 | symbol _ZN4Aska5Event4ExitEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Event4ExitEv(long *param_1)

{
  int iVar1;
  
  if (*param_1 != 0) {
    pthread_mutex_lock();
    pthread_cond_destroy(param_1 + 6);
    pthread_mutex_unlock(*param_1);
    while (iVar1 = pthread_mutex_destroy(*param_1), iVar1 != 0) {
      Aska::Thread::SleepU(unsigned int)(100);
    }
    *param_1 = 0;
  }
  return;
}

// ==== Aska::Mutex::Mutex()
// vaddr 0x1f50274 | ghidra 0x2050274 | size 36 | symbol _ZN4Aska5MutexC2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5MutexC1Ev(long param_1)

{
  Aska::Semaphore::Semaphore()(param_1 + 8);
  (*(code *)PTR__ZN4Aska9Semaphore6CreateEii_02ca0a70)(param_1 + 8,1,1);
  return;
}

// ==== Aska::Mutex::~Mutex()
// vaddr 0x1f50298 | ghidra 0x2050298 | size 28 | symbol _ZN4Aska5MutexD2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5MutexD1Ev(long param_1)

{
  Aska::Semaphore::Exit()(param_1 + 8);
  (*(code *)PTR__ZN4Aska9SemaphoreD2Ev_02c9edf8)(param_1 + 8);
  return;
}

// ==== Aska::Mutex::Lock()
// vaddr 0x1f502b4 | ghidra 0x20502b4 | size 8 | symbol _ZN4Aska5Mutex4LockEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Mutex4LockEv(long param_1)

{
  (*(code *)PTR__ZNK4Aska9Semaphore4WaitEv_02ca6750)(param_1 + 8);
  return;
}

// ==== Aska::Mutex::TryLock()
// vaddr 0x1f502bc | ghidra 0x20502bc | size 8 | symbol _ZN4Aska5Mutex7TryLockEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Mutex7TryLockEv(long param_1)

{
  (*(code *)PTR__ZNK4Aska9Semaphore15WaitNonBlockingEv_02c9d6b8)(param_1 + 8);
  return;
}

// ==== Aska::Mutex::Unlock()
// vaddr 0x1f502c4 | ghidra 0x20502c4 | size 8 | symbol _ZN4Aska5Mutex6UnlockEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Mutex6UnlockEv(long param_1)

{
  (*(code *)PTR__ZNK4Aska9Semaphore6SignalEv_02c96cd0)(param_1 + 8);
  return;
}

// ==== Aska::Semaphore::Semaphore()
// vaddr 0x1f5cbf0 | ghidra 0x205cbf0 | size 8 | symbol _ZN4Aska9SemaphoreC2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska9SemaphoreC1Ev(undefined8 *param_1)

{
  *param_1 = 0;
  return;
}

// ==== Aska::Semaphore::~Semaphore()
// vaddr 0x1f5cbf8 | ghidra 0x205cbf8 | size 32 | symbol _ZN4Aska9SemaphoreD1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska9SemaphoreD2Ev(long *param_1)

{
  if (*param_1 != 0) {
    sem_destroy();
    *param_1 = 0;
  }
  return;
}

// ==== Aska::Semaphore::Exit()
// vaddr 0x1f5cc18 | ghidra 0x205cc18 | size 32 | symbol _ZN4Aska9Semaphore4ExitEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska9Semaphore4ExitEv(long *param_1)

{
  if (*param_1 != 0) {
    sem_destroy();
    *param_1 = 0;
  }
  return;
}

// ==== Aska::Semaphore::Create(int, int)
// vaddr 0x1f5cc38 | ghidra 0x205cc38 | size 68 | symbol _ZN4Aska9Semaphore6CreateEii | lib libSOA-3.7.0.so | 2026-10-04
bool _ZN4Aska9Semaphore6CreateEii(long *param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = sem_init(param_1 + 1,0,param_2);
  if (iVar1 == 0) {
    *param_1 = (long)(param_1 + 1);
  }
  return iVar1 == 0;
}

// ==== Aska::Semaphore::Wait() const
// vaddr 0x1f5cc7c | ghidra 0x205cc7c | size 16 | symbol _ZNK4Aska9Semaphore4WaitEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK4Aska9Semaphore4WaitEv(long *param_1)

{
  if (*param_1 != 0) {
    (*(code *)PTR_sem_wait_02caa2c8)();
    return;
  }
  return;
}

// ==== Aska::Semaphore::WaitNonBlocking() const
// vaddr 0x1f5cc8c | ghidra 0x205cc8c | size 32 | symbol _ZNK4Aska9Semaphore15WaitNonBlockingEv | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK4Aska9Semaphore15WaitNonBlockingEv(long *param_1)

{
  bool bVar1;
  int iVar2;
  
  bVar1 = false;
  if (*param_1 != 0) {
    iVar2 = sem_trywait();
    bVar1 = iVar2 == 0;
  }
  return bVar1;
}

// ==== Aska::Semaphore::IsReady() const
// vaddr 0x1f5ccac | ghidra 0x205ccac | size 16 | symbol _ZNK4Aska9Semaphore7IsReadyEv | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK4Aska9Semaphore7IsReadyEv(long *param_1)

{
  return *param_1 != 0;
}

// ==== Aska::Semaphore::Polling() const
// vaddr 0x1f5ccbc | ghidra 0x205ccbc | size 52 | symbol _ZNK4Aska9Semaphore7PollingEv | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK4Aska9Semaphore7PollingEv(long *param_1)

{
  bool bVar1;
  int iVar2;
  int iStack_4;
  
  bVar1 = false;
  if (*param_1 != 0) {
    iVar2 = sem_getvalue(*param_1,&iStack_4);
    bVar1 = iVar2 == 0 && 0 < iStack_4;
  }
  return bVar1;
}

// ==== Aska::Semaphore::Signal() const
// vaddr 0x1f5ccf0 | ghidra 0x205ccf0 | size 16 | symbol _ZNK4Aska9Semaphore6SignalEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK4Aska9Semaphore6SignalEv(long *param_1)

{
  if (*param_1 != 0) {
    (*(code *)PTR_sem_post_02ca3660)();
    return;
  }
  return;
}

// ==== Aska::Semaphore::Signal_Legacy() const
// vaddr 0x1f5cd00 | ghidra 0x205cd00 | size 40 | symbol _ZNK4Aska9Semaphore13Signal_LegacyEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK4Aska9Semaphore13Signal_LegacyEv(undefined8 *param_1)

{
  undefined4 uVar1;
  
  if ((undefined4 *)*param_1 == (undefined4 *)0x0) {
    uVar1 = 0;
  }
  else {
    uVar1 = *(undefined4 *)*param_1;
    sem_post();
  }
  return uVar1;
}

// ==== Aska::Event::~Event()
// vaddr 0x1f8d218 | ghidra 0x208d218 | size 4 | symbol _ZN4Aska5EventD2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5EventD2Ev(void)

{
  (*(code *)PTR__ZN4Aska5Event4ExitEv_02ca1548)();
  return;
}
