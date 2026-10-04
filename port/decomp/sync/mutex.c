// port/decomp/sync/mutex.c: Ghidra decompiles for the sync subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-04 05:03 UTC: tools/decomp.sh '--into' 'sync/mutex' 'Framework::CMutex::'
// run      2026-10-04 05:04 UTC: tools/decomp.sh '--into' 'sync/mutex' 'Aska::FastCriticalSection::'

// ==== Framework::CMutex::CMutex()
// vaddr 0x1e8bab4 | ghidra 0x1f8bab4 | size 24 | symbol _ZN9Framework6CMutexC1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework6CMutexC2Ev(long *param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZTVN9Framework6CMutexE_02cc28b8;
  *(undefined2 *)(param_1 + 0x14) = 0;
  *param_1 = (long)(puVar1 + 0x10);
  return;
}

// ==== Framework::CMutex::~CMutex()
// vaddr 0x1e8bacc | ghidra 0x1f8bacc | size 152 | symbol _ZN9Framework6CMutexD2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework6CMutexD1Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN9Framework6CMutexE_02cc28b8 + 0x10);
  if (*(char *)((long)param_1 + 0xa1) != '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964c10/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Mutex.cpp"*/,0x36,&UNK_02964c61/*"Unlock doesn't called, yet."*/);
  }
  if ((char)param_1[0x14] != '\0') {
    DataMemoryBarrier(2,3);
    if (*(int *)((long)param_1 + 0xa4) != 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964c10/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Mutex.cpp"*/,0x3a,&UNK_02964c61/*"Unlock doesn't called, yet."*/);
    }
    if ((char)param_1[0x14] == '\0') {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964c10/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Mutex.cpp"*/,0x44,&UNK_02961b3b/*"Uninitialized object."*/);
    }
    Aska::FastCriticalSection::~FastCriticalSection()(param_1 + 2);
  }
  *(undefined2 *)(param_1 + 0x14) = 0;
  return;
}

// ==== Framework::CMutex::Release()
// vaddr 0x1e8bb64 | ghidra 0x1f8bb64 | size 136 | symbol _ZN9Framework6CMutex7ReleaseEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework6CMutex7ReleaseEv(long param_1)

{
  if (*(char *)(param_1 + 0xa1) != '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964c10/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Mutex.cpp"*/,0x36,&UNK_02964c61/*"Unlock doesn't called, yet."*/);
  }
  if (*(char *)(param_1 + 0xa0) != '\0') {
    DataMemoryBarrier(2,3);
    if (*(int *)(param_1 + 0xa4) != 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964c10/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Mutex.cpp"*/,0x3a,&UNK_02964c61/*"Unlock doesn't called, yet."*/);
    }
    if (*(char *)(param_1 + 0xa0) == '\0') {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964c10/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Mutex.cpp"*/,0x44,&UNK_02961b3b/*"Uninitialized object."*/);
    }
    Aska::FastCriticalSection::~FastCriticalSection()(param_1 + 0x10);
  }
  *(undefined2 *)(param_1 + 0xa0) = 0;
  return;
}

// ==== Framework::CMutex::~CMutex()
// vaddr 0x1e8bbec | ghidra 0x1f8bbec | size 152 | symbol _ZN9Framework6CMutexD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework6CMutexD0Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN9Framework6CMutexE_02cc28b8 + 0x10);
  if (*(char *)((long)param_1 + 0xa1) != '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964c10/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Mutex.cpp"*/,0x36,&UNK_02964c61/*"Unlock doesn't called, yet."*/);
  }
  if ((char)param_1[0x14] != '\0') {
    DataMemoryBarrier(2,3);
    if (*(int *)((long)param_1 + 0xa4) != 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964c10/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Mutex.cpp"*/,0x3a,&UNK_02964c61/*"Unlock doesn't called, yet."*/);
    }
    if ((char)param_1[0x14] == '\0') {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964c10/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Mutex.cpp"*/,0x44,&UNK_02961b3b/*"Uninitialized object."*/);
    }
    Aska::FastCriticalSection::~FastCriticalSection()(param_1 + 2);
  }
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Framework::CMutex::Initialize()
// vaddr 0x1e8bc84 | ghidra 0x1f8bc84 | size 72 | symbol _ZN9Framework6CMutex10InitializeEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework6CMutex10InitializeEv(long param_1)

{
  if (*(char *)(param_1 + 0xa0) != '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964c10/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Mutex.cpp"*/,0x1a,&UNK_02961b26/*"Already initialized."*/);
  }
  Aska::FastCriticalSection::FastCriticalSection()(param_1 + 0x10);
  *(undefined2 *)(param_1 + 0xa0) = 1;
  *(undefined4 *)(param_1 + 0xa4) = 0;
  *(undefined8 *)(param_1 + 0xa8) = 0;
  return;
}

// ==== Framework::CMutex::IsInitialized() const
// vaddr 0x1e8bccc | ghidra 0x1f8bccc | size 8 | symbol _ZNK9Framework6CMutex13IsInitializedEv | lib libSOA-3.7.0.so | 2026-10-04
undefined1 _ZNK9Framework6CMutex13IsInitializedEv(long param_1)

{
  return *(undefined1 *)(param_1 + 0xa0);
}

// ==== Framework::CMutex::LockCounter() const
// vaddr 0x1e8bcd4 | ghidra 0x1f8bcd4 | size 56 | symbol _ZNK9Framework6CMutex11LockCounterEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK9Framework6CMutex11LockCounterEv(long param_1)

{
  if (*(char *)(param_1 + 0xa0) == '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964c10/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Mutex.cpp"*/,0xa6,&UNK_02961b3b/*"Uninitialized object."*/);
  }
  DataMemoryBarrier(2,3);
  return *(undefined4 *)(param_1 + 0xa4);
}

// ==== Framework::CMutex::rSubstance()
// vaddr 0x1e8bd0c | ghidra 0x1f8bd0c | size 52 | symbol _ZN9Framework6CMutex10rSubstanceEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZN9Framework6CMutex10rSubstanceEv(long param_1)

{
  if (*(char *)(param_1 + 0xa0) == '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964c10/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Mutex.cpp"*/,0x44,&UNK_02961b3b/*"Uninitialized object."*/);
  }
  return param_1 + 0x10;
}

// ==== Framework::CMutex::crSubstance() const
// vaddr 0x1e8bd40 | ghidra 0x1f8bd40 | size 52 | symbol _ZNK9Framework6CMutex11crSubstanceEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK9Framework6CMutex11crSubstanceEv(long param_1)

{
  if (*(char *)(param_1 + 0xa0) == '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964c10/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Mutex.cpp"*/,0x4a,&UNK_02961b3b/*"Uninitialized object."*/);
  }
  return param_1 + 0x10;
}

// ==== Framework::CMutex::Lock()
// vaddr 0x1e8bd74 | ghidra 0x1f8bd74 | size 360 | symbol _ZN9Framework6CMutex4LockEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework6CMutex4LockEv(long param_1)

{
  int *piVar1;
  int *piVar2;
  char cVar3;
  bool bVar4;
  long lVar5;
  ulong uVar6;
  undefined8 uVar7;
  int iVar8;
  long lVar9;
  
  if (*(char *)(param_1 + 0xa0) == '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964c10/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Mutex.cpp"*/,0x61,&UNK_02961b3b/*"Uninitialized object."*/);
  }
  lVar9 = *(long *)(param_1 + 0xa8);
  lVar5 = Aska::Thread::GetCurrentID()();
  if (lVar9 == lVar5) {
code_r0x01f8bea8:
    uVar7 = Aska::Thread::GetCurrentID()();
    *(undefined8 *)(param_1 + 0xa8) = uVar7;
    *(undefined1 *)(param_1 + 0xa1) = 1;
    piVar1 = (int *)(param_1 + 0xa4);
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + 1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
    return;
  }
  if (*(char *)(param_1 + 0xa0) == '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964c10/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Mutex.cpp"*/,0x44,&UNK_02961b3b/*"Uninitialized object."*/);
  }
  piVar1 = (int *)(param_1 + 0x48);
  iVar8 = 0;
code_r0x01f8bddc:
  do {
    if (*piVar1 != -1) {
      ClearExclusiveLocal();
      bVar4 = iVar8 < 0x1ff;
      iVar8 = iVar8 + 1;
      if (bVar4) goto code_r0x01f8bddc;
      piVar2 = (int *)(param_1 + 0x4c);
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
        if (bVar4) {
          *piVar2 = *piVar2 + 1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      do {
        if (*piVar1 != -1) {
          ClearExclusiveLocal();
          do {
            uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x88);
            if ((uVar6 & 1) == 0) {
              do {
                cVar3 = '\x01';
                bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
                if (bVar4) {
                  *piVar2 = *piVar2 + -1;
                  cVar3 = ExclusiveMonitorsStatus();
                }
              } while (cVar3 != '\0');
              Aska::Thread::Sleep(unsigned int)(1);
            }
            else {
              Aska::Semaphore::Wait() const(param_1 + 0x88);
            }
            do {
              cVar3 = '\x01';
              bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
              if (bVar4) {
                *piVar2 = *piVar2 + 1;
                cVar3 = ExclusiveMonitorsStatus();
              }
            } while (cVar3 != '\0');
            while (*piVar1 == -1) {
              cVar3 = '\x01';
              bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
              if (bVar4) {
                *piVar1 = 0;
                cVar3 = ExclusiveMonitorsStatus();
              }
              if (cVar3 == '\0') goto code_r0x01f8be94;
            }
            ClearExclusiveLocal();
          } while( true );
        }
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
        if (bVar4) {
          *piVar1 = 0;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
code_r0x01f8be94:
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
        if (bVar4) {
          *piVar2 = *piVar2 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
code_r0x01f8bea4:
      DataMemoryBarrier(2,3);
      goto code_r0x01f8bea8;
    }
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar4) {
      *piVar1 = 0;
      cVar3 = ExclusiveMonitorsStatus();
    }
    if (cVar3 == '\0') goto code_r0x01f8bea4;
  } while( true );
}

// ==== Framework::CMutex::Unlock()
// vaddr 0x1e8bedc | ghidra 0x1f8bedc | size 212 | symbol _ZN9Framework6CMutex6UnlockEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework6CMutex6UnlockEv(long param_1)

{
  char cVar1;
  bool bVar2;
  ulong uVar3;
  int *piVar4;
  
  if (*(char *)(param_1 + 0xa0) == '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964c10/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Mutex.cpp"*/,0x7d,&UNK_02961b3b/*"Uninitialized object."*/);
  }
  piVar4 = (int *)(param_1 + 0xa4);
  if (*piVar4 == 1) {
    *(undefined1 *)(param_1 + 0xa1) = 0;
    *(undefined8 *)(param_1 + 0xa8) = 0;
    do {
      cVar1 = '\x01';
      bVar2 = (bool)ExclusiveMonitorPass(piVar4,0x10);
      if (bVar2) {
        *piVar4 = *piVar4 + -1;
        cVar1 = ExclusiveMonitorsStatus();
      }
    } while (cVar1 != '\0');
    if (*(char *)(param_1 + 0xa0) == '\0') {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964c10/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Mutex.cpp"*/,0x44,&UNK_02961b3b/*"Uninitialized object."*/);
    }
    DataMemoryBarrier(2,3);
    *(undefined4 *)(param_1 + 0x48) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar4 = (int *)(param_1 + 0x4c);
    if (0x14 < *piVar4) {
      do {
        cVar1 = '\x01';
        bVar2 = (bool)ExclusiveMonitorPass(piVar4,0x10);
        if (bVar2) {
          *piVar4 = *piVar4 + -1;
          cVar1 = ExclusiveMonitorsStatus();
        }
      } while (cVar1 != '\0');
      uVar3 = Aska::Semaphore::IsReady() const(param_1 + 0x88);
      if ((uVar3 & 1) != 0) {
        (*(code *)PTR__ZNK4Aska9Semaphore6SignalEv_02c96cd0)(param_1 + 0x88);
        return;
      }
    }
  }
  else {
    do {
      cVar1 = '\x01';
      bVar2 = (bool)ExclusiveMonitorPass(piVar4,0x10);
      if (bVar2) {
        *piVar4 = *piVar4 + -1;
        cVar1 = ExclusiveMonitorsStatus();
      }
    } while (cVar1 != '\0');
  }
  return;
}

// ==== Framework::CMutex::IsLocked() const
// vaddr 0x1e8bfb0 | ghidra 0x1f8bfb0 | size 8 | symbol _ZNK9Framework6CMutex8IsLockedEv | lib libSOA-3.7.0.so | 2026-10-04
undefined1 _ZNK9Framework6CMutex8IsLockedEv(long param_1)

{
  return *(undefined1 *)(param_1 + 0xa1);
}


// FAILED to create function at 02ba91d8 Framework::CMutex::vtable
// FAILED to create function at 02ba9210 Framework::CMutex::typeinfo

// ==== Aska::FastCriticalSection::FastCriticalSection()
// vaddr 0x1f85580 | ghidra 0x2085580 | size 52 | symbol _ZN4Aska19FastCriticalSectionC2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska19FastCriticalSectionC1Ev(long param_1)

{
  *(undefined4 *)(param_1 + 0x38) = 0xffffffff;
  *(undefined4 *)(param_1 + 0x3c) = 0x14;
  Aska::Semaphore::Semaphore()(param_1 + 0x78);
  (*(code *)PTR__ZN4Aska9Semaphore6CreateEii_02ca0a70)(param_1 + 0x78,0,0x7fffffff);
  return;
}

// ==== Aska::FastCriticalSection::~FastCriticalSection()
// vaddr 0x1f855b4 | ghidra 0x20855b4 | size 28 | symbol _ZN4Aska19FastCriticalSectionD1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska19FastCriticalSectionD2Ev(long param_1)

{
  Aska::Semaphore::Exit()(param_1 + 0x78);
  (*(code *)PTR__ZN4Aska9SemaphoreD2Ev_02c9edf8)(param_1 + 0x78);
  return;
}
