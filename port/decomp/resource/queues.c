// port/decomp/resource/queues.c: Ghidra decompiles for the resource subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-04 06:17 UTC: tools/decomp.sh '--into' 'resource/queues' 'Aska::ResourceReadyQueue::' 'Aska::DecompressQueue::' 'Aska::DecompressThread::'

// ==== Aska::DecompressQueue::DecompressQueue(int)
// vaddr 0x1f1cc58 | ghidra 0x201cc58 | size 172 | symbol _ZN4Aska15DecompressQueueC1Ei | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska15DecompressQueueC2Ei(long *param_1)

{
  long *plVar1;
  ulong uVar2;
  long lVar3;
  
  Aska::FastCriticalSection::FastCriticalSection()(param_1 + 1);
  *(undefined4 *)(param_1 + 0x13) = 0;
  *(undefined1 *)((long)param_1 + 0x9c) = 0;
  plVar1 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x140,PTR__ZSt7nothrow_02cb9a80);
  if (plVar1 != (long *)0x0) {
    Aska::DecompressThread::DecompressThread(Aska::DecompressQueue*)(plVar1,param_1);
    *param_1 = (long)plVar1;
    if ((char)plVar1[0x11] == '\0') {
      lVar3 = *plVar1;
    }
    else {
      Aska::DecompressThread::CleanQueue()(plVar1);
      uVar2 = Aska::Thread::Create(bool, int, int, bool)(*param_1,1,0x80,0x4000,1);
      if ((uVar2 & 1) != 0) {
        *(undefined1 *)((long)param_1 + 0x9c) = 1;
        return;
      }
      plVar1 = (long *)*param_1;
      if (plVar1 == (long *)0x0) {
        return;
      }
      lVar3 = *plVar1;
    }
    (**(code **)(lVar3 + 8))(plVar1);
  }
  *param_1 = 0;
  return;
}

// ==== Aska::DecompressQueue::Clear()
// vaddr 0x1f1cd04 | ghidra 0x201cd04 | size 8 | symbol _ZN4Aska15DecompressQueue5ClearEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska15DecompressQueue5ClearEv(undefined8 *param_1)

{
  (*(code *)PTR__ZN4Aska16DecompressThread10CleanQueueEv_02c932a8)(*param_1);
  return;
}

// ==== Aska::DecompressQueue::~DecompressQueue()
// vaddr 0x1f1cd0c | ghidra 0x201cd0c | size 44 | symbol _ZN4Aska15DecompressQueueD1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska15DecompressQueueD2Ev(long *param_1)

{
  if ((long *)*param_1 != (long *)0x0) {
    (**(code **)(*(long *)*param_1 + 8))();
  }
  *(undefined1 *)((long)param_1 + 0x9c) = 0;
  (*(code *)PTR__ZN4Aska19FastCriticalSectionD2Ev_02ca21e0)(param_1 + 1);
  return;
}

// ==== Aska::DecompressQueue::Add(void const*, Aska::DecompressInfo*, int, Aska::INotify*, Aska::IMemoryManager*, Aska::IMemoryManager*, Aska::IMemoryManager*, Aska::IMemoryManager*)
// vaddr 0x1f1cd38 | ghidra 0x201cd38 | size 652 | symbol _ZN4Aska15DecompressQueue3AddEPKvPNS_14DecompressInfoEiPNS_7INotifyEPNS_14IMemoryManagerES8_S8_S8_ | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska15DecompressQueue3AddEPKvPNS_14DecompressInfoEiPNS_7INotifyEPNS_14IMemoryManagerES8_S8_S8_
          (long *param_1,long param_2,undefined4 *param_3,undefined4 param_4,undefined8 *param_5,
          undefined8 param_6,undefined8 param_7,undefined8 param_8,undefined8 param_9)

{
  long *plVar1;
  char cVar2;
  bool bVar3;
  ulong uVar4;
  long lVar5;
  undefined8 uVar6;
  int iVar7;
  int *piVar8;
  undefined8 *puVar9;
  long lStack_b0;
  undefined4 *puStack_a8;
  undefined8 uStack_a0;
  undefined4 uStack_98;
  undefined8 *puStack_90;
  undefined8 uStack_88;
  undefined8 uStack_80;
  undefined8 uStack_78;
  undefined8 uStack_70;
  undefined4 uStack_68;
  
  if (((param_2 == 0) || (param_3 == (undefined4 *)0x0)) ||
     (uVar4 = Aska::Decompress::CheckMemoryManager(Aska::IMemoryManager*, Aska::IMemoryManager*, Aska::IMemoryManager*, Aska::IMemoryManager*)(param_6,param_7,param_8,param_9), (uVar4 & 1) == 0)) {
    return 0;
  }
  plVar1 = param_1 + 8;
  iVar7 = 0;
  do {
    while ((int)*plVar1 == -1) {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(plVar1,0x10);
      if (bVar3) {
        *(int *)plVar1 = 0;
        cVar2 = ExclusiveMonitorsStatus();
      }
      if (cVar2 == '\0') goto code_r0x0201ce74;
    }
    ClearExclusiveLocal();
    bVar3 = iVar7 < 0x1ff;
    iVar7 = iVar7 + 1;
  } while (bVar3);
  piVar8 = (int *)((long)param_1 + 0x44);
  do {
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar8,0x10);
    if (bVar3) {
      *piVar8 = *piVar8 + 1;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
  do {
    if ((int)*plVar1 != -1) {
      ClearExclusiveLocal();
      uVar4 = Aska::Semaphore::IsReady() const();
      if ((uVar4 & 1) != 0) goto code_r0x0201ce38;
      do {
        do {
          cVar2 = '\x01';
          bVar3 = (bool)ExclusiveMonitorPass(piVar8,0x10);
          if (bVar3) {
            *piVar8 = *piVar8 + -1;
            cVar2 = ExclusiveMonitorsStatus();
          }
        } while (cVar2 != '\0');
        Aska::Thread::Sleep(unsigned int)(1);
        while( true ) {
          do {
            cVar2 = '\x01';
            bVar3 = (bool)ExclusiveMonitorPass(piVar8,0x10);
            if (bVar3) {
              *piVar8 = *piVar8 + 1;
              cVar2 = ExclusiveMonitorsStatus();
            }
          } while (cVar2 != '\0');
          while ((int)*plVar1 == -1) {
            cVar2 = '\x01';
            bVar3 = (bool)ExclusiveMonitorPass(plVar1,0x10);
            if (bVar3) {
              *(int *)plVar1 = 0;
              cVar2 = ExclusiveMonitorsStatus();
            }
            if (cVar2 == '\0') goto code_r0x0201ce64;
          }
          ClearExclusiveLocal();
          uVar4 = Aska::Semaphore::IsReady() const(param_1 + 0x10);
          if ((uVar4 & 1) == 0) break;
code_r0x0201ce38:
          Aska::Semaphore::Wait() const(param_1 + 0x10);
        }
      } while( true );
    }
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(plVar1,0x10);
    if (bVar3) {
      *(int *)plVar1 = 0;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
code_r0x0201ce64:
  do {
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar8,0x10);
    if (bVar3) {
      *piVar8 = *piVar8 + -1;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
code_r0x0201ce74:
  DataMemoryBarrier(2,3);
  uStack_68 = (undefined4)param_1[0x13];
  uStack_a0 = 0;
  uStack_70 = param_9;
  lStack_b0 = param_2;
  puStack_a8 = param_3;
  uStack_98 = param_4;
  puStack_90 = param_5;
  uStack_88 = param_6;
  uStack_80 = param_7;
  uStack_78 = param_8;
  uVar4 = Aska::DecompressBase::IsCompressed(void const*)(param_2);
  if ((uVar4 & 1) == 0) {
    *param_3 = 3;
    if (param_5 == (undefined8 *)0x0) goto code_r0x0201cf58;
    puVar9 = (undefined8 *)*param_5;
    uVar6 = 2;
  }
  else {
    lVar5 = Aska::DecompressThread::Add(Aska::DecompressQueue::_DecompressArg*)(*param_1,&lStack_b0);
    if (lVar5 != 0) {
      *(uint *)(param_1 + 0x13) = (int)param_1[0x13] + 1U & 0x7fffffff;
      DataMemoryBarrier(2,3);
      *(undefined4 *)(param_1 + 8) = 0xffffffff;
      DataMemoryBarrier(2,3);
      piVar8 = (int *)((long)param_1 + 0x44);
      if (0x14 < *piVar8) {
        do {
          cVar2 = '\x01';
          bVar3 = (bool)ExclusiveMonitorPass(piVar8,0x10);
          if (bVar3) {
            *piVar8 = *piVar8 + -1;
            cVar2 = ExclusiveMonitorsStatus();
          }
        } while (cVar2 != '\0');
        uVar4 = Aska::Semaphore::IsReady() const(param_1 + 0x10);
        if ((uVar4 & 1) != 0) {
          Aska::Semaphore::Signal() const(param_1 + 0x10);
        }
      }
      Aska::Event::Set() const(*param_1 + 0x18);
      return 1;
    }
    *param_3 = 3;
    if (param_5 == (undefined8 *)0x0) goto code_r0x0201cf58;
    puVar9 = (undefined8 *)*param_5;
    uVar6 = 3;
  }
  (*(code *)*puVar9)(param_5,uVar6);
code_r0x0201cf58:
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_1 + 8) = 0xffffffff;
  DataMemoryBarrier(2,3);
  piVar8 = (int *)((long)param_1 + 0x44);
  if (*piVar8 < 0x15) {
    return 0;
  }
  do {
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar8,0x10);
    if (bVar3) {
      *piVar8 = *piVar8 + -1;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
  uVar4 = Aska::Semaphore::IsReady() const(param_1 + 0x10);
  if ((uVar4 & 1) == 0) {
    return 0;
  }
  Aska::Semaphore::Signal() const(param_1 + 0x10);
  return 0;
}

// ==== Aska::DecompressQueue::Add(void const*, unsigned char*, int, Aska::INotify*)
// vaddr 0x1f1cfc4 | ghidra 0x201cfc4 | size 584 | symbol _ZN4Aska15DecompressQueue3AddEPKvPhiPNS_7INotifyE | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska15DecompressQueue3AddEPKvPhiPNS_7INotifyE
          (long *param_1,long param_2,long param_3,undefined4 param_4,undefined8 *param_5)

{
  long *plVar1;
  char cVar2;
  bool bVar3;
  ulong uVar4;
  long lVar5;
  undefined8 uVar6;
  int iVar7;
  int *piVar8;
  undefined8 *puVar9;
  long alStack_a0 [3];
  undefined4 uStack_88;
  undefined8 *puStack_80;
  undefined8 uStack_78;
  undefined8 uStack_70;
  undefined8 uStack_68;
  undefined8 uStack_60;
  undefined4 uStack_58;
  
  if ((param_2 == 0) || (param_3 == 0)) {
    return 0;
  }
  plVar1 = param_1 + 8;
  iVar7 = 0;
  do {
    while ((int)*plVar1 == -1) {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(plVar1,0x10);
      if (bVar3) {
        *(int *)plVar1 = 0;
        cVar2 = ExclusiveMonitorsStatus();
      }
      if (cVar2 == '\0') goto code_r0x0201d0cc;
    }
    ClearExclusiveLocal();
    bVar3 = iVar7 < 0x1ff;
    iVar7 = iVar7 + 1;
  } while (bVar3);
  piVar8 = (int *)((long)param_1 + 0x44);
  do {
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar8,0x10);
    if (bVar3) {
      *piVar8 = *piVar8 + 1;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
  do {
    if ((int)*plVar1 != -1) {
      ClearExclusiveLocal();
      do {
        uVar4 = Aska::Semaphore::IsReady() const(param_1 + 0x10);
        if ((uVar4 & 1) == 0) {
          do {
            cVar2 = '\x01';
            bVar3 = (bool)ExclusiveMonitorPass(piVar8,0x10);
            if (bVar3) {
              *piVar8 = *piVar8 + -1;
              cVar2 = ExclusiveMonitorsStatus();
            }
          } while (cVar2 != '\0');
          Aska::Thread::Sleep(unsigned int)(1);
        }
        else {
          Aska::Semaphore::Wait() const(param_1 + 0x10);
        }
        do {
          cVar2 = '\x01';
          bVar3 = (bool)ExclusiveMonitorPass(piVar8,0x10);
          if (bVar3) {
            *piVar8 = *piVar8 + 1;
            cVar2 = ExclusiveMonitorsStatus();
          }
        } while (cVar2 != '\0');
        while ((int)*plVar1 == -1) {
          cVar2 = '\x01';
          bVar3 = (bool)ExclusiveMonitorPass(plVar1,0x10);
          if (bVar3) {
            *(int *)plVar1 = 0;
            cVar2 = ExclusiveMonitorsStatus();
          }
          if (cVar2 == '\0') goto code_r0x0201d0bc;
        }
        ClearExclusiveLocal();
      } while( true );
    }
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(plVar1,0x10);
    if (bVar3) {
      *(int *)plVar1 = 0;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
code_r0x0201d0bc:
  do {
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar8,0x10);
    if (bVar3) {
      *piVar8 = *piVar8 + -1;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
code_r0x0201d0cc:
  DataMemoryBarrier(2,3);
  uStack_58 = (undefined4)param_1[0x13];
  alStack_a0[1] = 0;
  uStack_60 = 0;
  uStack_68 = 0;
  uStack_70 = 0;
  uStack_78 = 0;
  alStack_a0[0] = param_2;
  alStack_a0[2] = param_3;
  uStack_88 = param_4;
  puStack_80 = param_5;
  uVar4 = Aska::DecompressBase::IsCompressed(void const*)(param_2);
  if ((uVar4 & 1) == 0) {
    if (param_5 == (undefined8 *)0x0) goto code_r0x0201d1a4;
    puVar9 = (undefined8 *)*param_5;
    uVar6 = 2;
  }
  else {
    lVar5 = Aska::DecompressThread::Add(Aska::DecompressQueue::_DecompressArg*)(*param_1,alStack_a0);
    if (lVar5 != 0) {
      *(uint *)(param_1 + 0x13) = (int)param_1[0x13] + 1U & 0x7fffffff;
      DataMemoryBarrier(2,3);
      *(undefined4 *)(param_1 + 8) = 0xffffffff;
      DataMemoryBarrier(2,3);
      piVar8 = (int *)((long)param_1 + 0x44);
      if (0x14 < *piVar8) {
        do {
          cVar2 = '\x01';
          bVar3 = (bool)ExclusiveMonitorPass(piVar8,0x10);
          if (bVar3) {
            *piVar8 = *piVar8 + -1;
            cVar2 = ExclusiveMonitorsStatus();
          }
        } while (cVar2 != '\0');
        uVar4 = Aska::Semaphore::IsReady() const(param_1 + 0x10);
        if ((uVar4 & 1) != 0) {
          Aska::Semaphore::Signal() const(param_1 + 0x10);
        }
      }
      Aska::Event::Set() const(*param_1 + 0x18);
      return 1;
    }
    if (param_5 == (undefined8 *)0x0) goto code_r0x0201d1a4;
    puVar9 = (undefined8 *)*param_5;
    uVar6 = 3;
  }
  (*(code *)*puVar9)(param_5,uVar6);
code_r0x0201d1a4:
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_1 + 8) = 0xffffffff;
  DataMemoryBarrier(2,3);
  piVar8 = (int *)((long)param_1 + 0x44);
  if (0x14 < *piVar8) {
    do {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar8,0x10);
      if (bVar3) {
        *piVar8 = *piVar8 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    uVar4 = Aska::Semaphore::IsReady() const(param_1 + 0x10);
    if ((uVar4 & 1) != 0) {
      Aska::Semaphore::Signal() const(param_1 + 0x10);
    }
  }
  return 0;
}

// ==== Aska::DecompressQueue::GetElement(unsigned int)
// vaddr 0x1f1d20c | ghidra 0x201d20c | size 412 | symbol _ZN4Aska15DecompressQueue10GetElementEj | lib libSOA-3.7.0.so | 2026-10-04
long * _ZN4Aska15DecompressQueue10GetElementEj(long *param_1,int param_2)

{
  int *piVar1;
  int iVar2;
  char cVar3;
  bool bVar4;
  ulong uVar5;
  int iVar6;
  long lVar7;
  long *plVar8;
  long lVar9;
  int *piVar10;
  
  lVar9 = *param_1;
  piVar10 = (int *)(lVar9 + 0xe8);
  iVar6 = 0;
code_r0x0201d234:
  if (*piVar10 == -1) {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar10,0x10);
    if (bVar4) {
      *piVar10 = 0;
      cVar3 = ExclusiveMonitorsStatus();
    }
    if (cVar3 == '\0') goto code_r0x0201d2fc;
    goto code_r0x0201d234;
  }
  ClearExclusiveLocal();
  bVar4 = iVar6 < 0x1ff;
  iVar6 = iVar6 + 1;
  if (bVar4) goto code_r0x0201d234;
  piVar1 = (int *)(lVar9 + 0xec);
  do {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar4) {
      *piVar1 = *piVar1 + 1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
  do {
    if (*piVar10 != -1) {
      ClearExclusiveLocal();
      do {
        uVar5 = Aska::Semaphore::IsReady() const(lVar9 + 0x128);
        if ((uVar5 & 1) == 0) {
          do {
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
          Aska::Semaphore::Wait() const(lVar9 + 0x128);
        }
        do {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar4) {
            *piVar1 = *piVar1 + 1;
            cVar3 = ExclusiveMonitorsStatus();
          }
        } while (cVar3 != '\0');
        while (*piVar10 == -1) {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar10,0x10);
          if (bVar4) {
            *piVar10 = 0;
            cVar3 = ExclusiveMonitorsStatus();
          }
          if (cVar3 == '\0') goto code_r0x0201d2ec;
        }
        ClearExclusiveLocal();
      } while( true );
    }
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar10,0x10);
    if (bVar4) {
      *piVar10 = 0;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
code_r0x0201d2ec:
  do {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar4) {
      *piVar1 = *piVar1 + -1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
code_r0x0201d2fc:
  DataMemoryBarrier(2,3);
  lVar7 = *param_1;
  iVar6 = *(int *)(lVar7 + 0x9c);
  while( true ) {
    iVar2 = 0;
    if (iVar6 + 1U < *(uint *)(lVar7 + 0xa0)) {
      iVar2 = iVar6 + 1;
    }
    if (iVar2 == *(int *)(lVar7 + 0x98)) break;
    plVar8 = (long *)(*(long *)(lVar7 + 0xa8) + (long)iVar2 * 0x50);
    if ((plVar8 == (long *)0x0) || (iVar6 = iVar2, *(int *)(*plVar8 + 4) == param_2))
    goto code_r0x0201d34c;
  }
  plVar8 = (long *)0x0;
code_r0x0201d34c:
  DataMemoryBarrier(2,3);
  *(undefined4 *)(lVar9 + 0xe8) = 0xffffffff;
  DataMemoryBarrier(2,3);
  piVar10 = (int *)(lVar9 + 0xec);
  if (0x14 < *piVar10) {
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar10,0x10);
      if (bVar4) {
        *piVar10 = *piVar10 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
    uVar5 = Aska::Semaphore::IsReady() const(lVar9 + 0x128);
    if ((uVar5 & 1) != 0) {
      Aska::Semaphore::Signal() const(lVar9 + 0x128);
    }
  }
  return plVar8;
}

// ==== Aska::DecompressQueue::GetElement(void*)
// vaddr 0x1f1d3a8 | ghidra 0x201d3a8 | size 412 | symbol _ZN4Aska15DecompressQueue10GetElementEPv | lib libSOA-3.7.0.so | 2026-10-04
long * _ZN4Aska15DecompressQueue10GetElementEPv(long *param_1,long param_2)

{
  int *piVar1;
  int iVar2;
  char cVar3;
  bool bVar4;
  ulong uVar5;
  int iVar6;
  long lVar7;
  long *plVar8;
  long lVar9;
  int *piVar10;
  
  lVar9 = *param_1;
  piVar10 = (int *)(lVar9 + 0xe8);
  iVar6 = 0;
code_r0x0201d3d0:
  if (*piVar10 == -1) {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar10,0x10);
    if (bVar4) {
      *piVar10 = 0;
      cVar3 = ExclusiveMonitorsStatus();
    }
    if (cVar3 == '\0') goto code_r0x0201d498;
    goto code_r0x0201d3d0;
  }
  ClearExclusiveLocal();
  bVar4 = iVar6 < 0x1ff;
  iVar6 = iVar6 + 1;
  if (bVar4) goto code_r0x0201d3d0;
  piVar1 = (int *)(lVar9 + 0xec);
  do {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar4) {
      *piVar1 = *piVar1 + 1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
  do {
    if (*piVar10 != -1) {
      ClearExclusiveLocal();
      do {
        uVar5 = Aska::Semaphore::IsReady() const(lVar9 + 0x128);
        if ((uVar5 & 1) == 0) {
          do {
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
          Aska::Semaphore::Wait() const(lVar9 + 0x128);
        }
        do {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar4) {
            *piVar1 = *piVar1 + 1;
            cVar3 = ExclusiveMonitorsStatus();
          }
        } while (cVar3 != '\0');
        while (*piVar10 == -1) {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar10,0x10);
          if (bVar4) {
            *piVar10 = 0;
            cVar3 = ExclusiveMonitorsStatus();
          }
          if (cVar3 == '\0') goto code_r0x0201d488;
        }
        ClearExclusiveLocal();
      } while( true );
    }
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar10,0x10);
    if (bVar4) {
      *piVar10 = 0;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
code_r0x0201d488:
  do {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar4) {
      *piVar1 = *piVar1 + -1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
code_r0x0201d498:
  DataMemoryBarrier(2,3);
  lVar7 = *param_1;
  iVar6 = *(int *)(lVar7 + 0x9c);
  while( true ) {
    iVar2 = 0;
    if (iVar6 + 1U < *(uint *)(lVar7 + 0xa0)) {
      iVar2 = iVar6 + 1;
    }
    if (iVar2 == *(int *)(lVar7 + 0x98)) break;
    plVar8 = (long *)(*(long *)(lVar7 + 0xa8) + (long)iVar2 * 0x50);
    if ((plVar8 == (long *)0x0) || (iVar6 = iVar2, *(long *)(*plVar8 + 0x10) == param_2))
    goto code_r0x0201d4e8;
  }
  plVar8 = (long *)0x0;
code_r0x0201d4e8:
  DataMemoryBarrier(2,3);
  *(undefined4 *)(lVar9 + 0xe8) = 0xffffffff;
  DataMemoryBarrier(2,3);
  piVar10 = (int *)(lVar9 + 0xec);
  if (0x14 < *piVar10) {
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar10,0x10);
      if (bVar4) {
        *piVar10 = *piVar10 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
    uVar5 = Aska::Semaphore::IsReady() const(lVar9 + 0x128);
    if ((uVar5 & 1) != 0) {
      Aska::Semaphore::Signal() const(lVar9 + 0x128);
    }
  }
  return plVar8;
}

// ==== Aska::DecompressQueue::IsFull(void*) const
// vaddr 0x1f1d544 | ghidra 0x201d544 | size 92 | symbol _ZNK4Aska15DecompressQueue6IsFullEPv | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK4Aska15DecompressQueue6IsFullEPv(long *param_1)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  long lVar4;
  undefined1 auStack_18 [8];
  
  Aska::AppProjectDependentProxy::AppProjectDependentProxy()(auStack_18);
  iVar2 = Aska::AppProjectDependentProxy::GetDecompressQueueSize() const(auStack_18);
  lVar4 = *param_1;
  uVar3 = *(uint *)(lVar4 + 0x98);
  uVar1 = *(uint *)(lVar4 + 0x9c);
  if (uVar3 <= uVar1) {
    uVar3 = *(int *)(lVar4 + 0xa0) + uVar3;
  }
  Aska::AppProjectDependentProxy::~AppProjectDependentProxy()(auStack_18);
  return iVar2 <= (int)(uVar3 + ~uVar1);
}

// ==== Aska::DecompressQueue::IsEmpty() const
// vaddr 0x1f1d5a0 | ghidra 0x201d5a0 | size 40 | symbol _ZNK4Aska15DecompressQueue7IsEmptyEv | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK4Aska15DecompressQueue7IsEmptyEv(long *param_1)

{
  uint uVar1;
  long lVar2;
  
  lVar2 = *param_1;
  uVar1 = *(uint *)(lVar2 + 0x98);
  if (uVar1 <= *(uint *)(lVar2 + 0x9c)) {
    uVar1 = *(int *)(lVar2 + 0xa0) + uVar1;
  }
  return uVar1 - 1 == *(uint *)(lVar2 + 0x9c);
}

// ==== Aska::DecompressQueue::GetSize() const
// vaddr 0x1f1d5c8 | ghidra 0x201d5c8 | size 36 | symbol _ZNK4Aska15DecompressQueue7GetSizeEv | lib libSOA-3.7.0.so | 2026-10-04
int _ZNK4Aska15DecompressQueue7GetSizeEv(long *param_1)

{
  uint uVar1;
  long lVar2;
  
  lVar2 = *param_1;
  uVar1 = *(uint *)(lVar2 + 0x98);
  if (uVar1 <= *(uint *)(lVar2 + 0x9c)) {
    uVar1 = *(int *)(lVar2 + 0xa0) + uVar1;
  }
  return uVar1 + ~*(uint *)(lVar2 + 0x9c);
}

// ==== Aska::DecompressQueue::Stop(unsigned int)
// vaddr 0x1f1d5ec | ghidra 0x201d5ec | size 356 | symbol _ZN4Aska15DecompressQueue4StopEj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska15DecompressQueue4StopEj(long param_1,undefined4 param_2)

{
  int *piVar1;
  char cVar2;
  bool bVar3;
  long lVar4;
  ulong uVar5;
  int iVar6;
  int *piVar7;
  
  piVar7 = (int *)(param_1 + 0x40);
  iVar6 = 0;
  do {
    while (*piVar7 == -1) {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar7,0x10);
      if (bVar3) {
        *piVar7 = 0;
        cVar2 = ExclusiveMonitorsStatus();
      }
      if (cVar2 == '\0') goto code_r0x0201d6d0;
    }
    ClearExclusiveLocal();
    bVar3 = iVar6 < 0x1ff;
    iVar6 = iVar6 + 1;
  } while (bVar3);
  piVar1 = (int *)(param_1 + 0x44);
  do {
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar3) {
      *piVar1 = *piVar1 + 1;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
  do {
    if (*piVar7 != -1) {
      ClearExclusiveLocal();
      do {
        uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0x80);
        if ((uVar5 & 1) == 0) {
          do {
            cVar2 = '\x01';
            bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
            if (bVar3) {
              *piVar1 = *piVar1 + -1;
              cVar2 = ExclusiveMonitorsStatus();
            }
          } while (cVar2 != '\0');
          Aska::Thread::Sleep(unsigned int)(1);
        }
        else {
          Aska::Semaphore::Wait() const(param_1 + 0x80);
        }
        do {
          cVar2 = '\x01';
          bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar3) {
            *piVar1 = *piVar1 + 1;
            cVar2 = ExclusiveMonitorsStatus();
          }
        } while (cVar2 != '\0');
        while (*piVar7 == -1) {
          cVar2 = '\x01';
          bVar3 = (bool)ExclusiveMonitorPass(piVar7,0x10);
          if (bVar3) {
            *piVar7 = 0;
            cVar2 = ExclusiveMonitorsStatus();
          }
          if (cVar2 == '\0') goto code_r0x0201d6c0;
        }
        ClearExclusiveLocal();
      } while( true );
    }
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar7,0x10);
    if (bVar3) {
      *piVar7 = 0;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
code_r0x0201d6c0:
  do {
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar3) {
      *piVar1 = *piVar1 + -1;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
code_r0x0201d6d0:
  DataMemoryBarrier(2,3);
  lVar4 = Aska::DecompressQueue::GetElement(unsigned int)(param_1,param_2);
  if (lVar4 != 0) {
    *(undefined1 *)(lVar4 + 0x29) = 1;
  }
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_1 + 0x40) = 0xffffffff;
  DataMemoryBarrier(2,3);
  piVar7 = (int *)(param_1 + 0x44);
  if (0x14 < *piVar7) {
    do {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar7,0x10);
      if (bVar3) {
        *piVar7 = *piVar7 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0x80);
    if ((uVar5 & 1) != 0) {
      (*(code *)PTR__ZNK4Aska9Semaphore6SignalEv_02c96cd0)(param_1 + 0x80);
      return;
    }
  }
  return;
}

// ==== Aska::DecompressQueue::IsSafe(unsigned int)
// vaddr 0x1f1d750 | ghidra 0x201d750 | size 52 | symbol _ZN4Aska15DecompressQueue6IsSafeEj | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska15DecompressQueue6IsSafeEj(void)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)Aska::DecompressQueue::GetElement(unsigned int)();
  if ((puVar1 != (undefined8 *)0x0) && (*(uint *)*puVar1 < 2)) {
    return 0;
  }
  return 1;
}

// ==== Aska::DecompressQueue::IsSafe(void*)
// vaddr 0x1f1d784 | ghidra 0x201d784 | size 52 | symbol _ZN4Aska15DecompressQueue6IsSafeEPv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska15DecompressQueue6IsSafeEPv(void)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)Aska::DecompressQueue::GetElement(void*)();
  if ((puVar1 != (undefined8 *)0x0) && (*(uint *)*puVar1 < 2)) {
    return 0;
  }
  return 1;
}

// ==== Aska::DecompressThread::DecompressThread(Aska::DecompressQueue*)
// vaddr 0x1f1d7b8 | ghidra 0x201d7b8 | size 272 | symbol _ZN4Aska16DecompressThreadC2EPNS_15DecompressQueueE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16DecompressThreadC1EPNS_15DecompressQueueE(long *param_1,long param_2)

{
  undefined1 auVar1 [16];
  int iVar2;
  ulong uVar3;
  long lVar4;
  undefined1 auStack_28 [8];
  
  Aska::Thread::Thread()();
  *param_1 = (long)(PTR__ZTVN4Aska16DecompressThreadE_02cbcaf8 + 0x10);
  Aska::Event::Event()(param_1 + 3);
  *(undefined2 *)(param_1 + 0x11) = 0;
  memset(param_1 + 0x12,0,0xb0);
  *(undefined4 *)(param_1 + 0x14) = 0;
  param_1[0x12] =
       (long)(
             PTR__ZTVN4Aska16DecompressThread13TElementQueueINS_15DecompressQueue7ElementELb1EEE_02cc4be8
             + 0x10);
  param_1[0x13] = 1;
  Aska::FastCriticalSection::FastCriticalSection()(param_1 + 0x16);
  Aska::AppProjectDependentProxy::AppProjectDependentProxy()(auStack_28);
  iVar2 = Aska::AppProjectDependentProxy::GetDecompressQueueSize() const(auStack_28);
  iVar2 = iVar2 + 1;
  if ((int)param_1[0x14] != iVar2) {
    if (param_1[0x15] != 0) {
      operator delete[](void*)();
    }
    auVar1._8_8_ = 0;
    auVar1._0_8_ = (long)iVar2;
    lVar4 = ((long)iVar2 + (long)iVar2 * 4) * 0x10;
    if (SUB168(auVar1 * ZEXT816(0x50),8) != 0) {
      lVar4 = -1;
    }
    lVar4 = operator new[](unsigned long, std::nothrow_t const&)(lVar4,PTR__ZSt7nothrow_02cb9a80);
    param_1[0x15] = lVar4;
    if (lVar4 == 0) {
      *(undefined4 *)(param_1 + 0x14) = 0;
      goto code_r0x0201d8b0;
    }
    *(int *)(param_1 + 0x14) = iVar2;
    param_1[0x13] = 1;
  }
  uVar3 = Aska::Event::Create(bool, bool)(param_1 + 3,0,0);
  if ((uVar3 & 1) != 0) {
    param_1[0x10] = param_2;
    *(undefined1 *)(param_1 + 0x11) = 1;
  }
code_r0x0201d8b0:
  Aska::AppProjectDependentProxy::~AppProjectDependentProxy()(auStack_28);
  return;
}

// ==== Aska::DecompressThread::~DecompressThread()
// vaddr 0x1f1d8c8 | ghidra 0x201d8c8 | size 160 | symbol _ZN4Aska16DecompressThreadD1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16DecompressThreadD2Ev(long *param_1)

{
  long *plVar1;
  undefined *puVar2;
  
  plVar1 = param_1 + 3;
  puVar2 = PTR__ZTVN4Aska16DecompressThreadE_02cbcaf8 + 0x10;
  *(undefined1 *)((long)param_1 + 0x89) = 1;
  *param_1 = (long)puVar2;
  Aska::Event::Set() const(plVar1);
  Aska::Thread::WaitEnd()(param_1);
  if ((char)param_1[0x11] != '\0') {
    Aska::Event::Exit()(plVar1);
  }
  param_1[0x12] =
       (long)(
             PTR__ZTVN4Aska16DecompressThread13TElementQueueINS_15DecompressQueue7ElementELb1EEE_02cc4be8
             + 0x10);
  Aska::FastCriticalSection::~FastCriticalSection()(param_1 + 0x16);
  puVar2 = PTR__ZTVN4Aska13TDynamicQueueINS_15DecompressQueue7ElementELb1EEE_02cb8c30;
  *(undefined4 *)(param_1 + 0x14) = 0;
  param_1[0x12] = (long)(puVar2 + 0x10);
  param_1[0x13] = 1;
  if (param_1[0x15] != 0) {
    operator delete[](void*)();
    param_1[0x15] = 0;
  }
  Aska::Event::Exit()(plVar1);
  (*(code *)PTR__ZN4Aska6ThreadD1Ev_02c9be08)(param_1);
  return;
}

// ==== Aska::DecompressThread::TElementQueue<Aska::DecompressQueue::Element, true>::~TElementQueue()
// vaddr 0x1f1d968 | ghidra 0x201d968 | size 80 | symbol _ZN4Aska16DecompressThread13TElementQueueINS_15DecompressQueue7ElementELb1EED2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16DecompressThread13TElementQueueINS_15DecompressQueue7ElementELb1EED2Ev(long *param_1)

{
  undefined *puVar1;
  
  *param_1 = (long)(
                   PTR__ZTVN4Aska16DecompressThread13TElementQueueINS_15DecompressQueue7ElementELb1EEE_02cc4be8
                   + 0x10);
  Aska::FastCriticalSection::~FastCriticalSection()(param_1 + 4);
  puVar1 = PTR__ZTVN4Aska13TDynamicQueueINS_15DecompressQueue7ElementELb1EEE_02cb8c30;
  *(undefined4 *)(param_1 + 2) = 0;
  *param_1 = (long)(puVar1 + 0x10);
  param_1[1] = 1;
  if (param_1[3] != 0) {
    operator delete[](void*)();
    param_1[3] = 0;
  }
  return;
}

// ==== Aska::DecompressThread::~DecompressThread()
// vaddr 0x1f1d9b8 | ghidra 0x201d9b8 | size 24 | symbol _ZN4Aska16DecompressThreadD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16DecompressThreadD0Ev(undefined8 param_1)

{
  Aska::DecompressThread::~DecompressThread()();
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::DecompressThread::Handler()
// vaddr 0x1f1d9d0 | ghidra 0x201d9d0 | size 984 | symbol _ZN4Aska16DecompressThread7HandlerEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16DecompressThread7HandlerEv(long param_1)

{
  int *piVar1;
  int *piVar2;
  long lVar3;
  uint uVar4;
  undefined2 uVar5;
  char cVar6;
  bool bVar7;
  uint uVar8;
  long *plVar9;
  long *plVar10;
  int iVar11;
  undefined8 *puVar12;
  long lVar13;
  code *pcVar14;
  uint uVar15;
  long lVar16;
  long lVar17;
  char *pcVar18;
  long lVar19;
  undefined8 uVar20;
  ulong uVar21;
  undefined4 *puVar22;
  
  if (*(char *)(param_1 + 0x89) == '\0') {
    piVar1 = (int *)(param_1 + 0xe8);
    piVar2 = (int *)(param_1 + 0xec);
    lVar3 = param_1 + 0x128;
    do {
      Aska::Event::Wait(unsigned int) const(param_1 + 0x18,0);
      uVar8 = *(uint *)(param_1 + 0x98);
      uVar4 = *(uint *)(param_1 + 0x9c);
      uVar15 = uVar8;
      if (uVar8 <= uVar4) {
        uVar15 = *(int *)(param_1 + 0xa0) + uVar8;
      }
      if (0 < (int)(uVar15 + ~uVar4)) {
        uVar15 = 0;
        if (uVar4 + 1 < *(uint *)(param_1 + 0xa0)) {
          uVar15 = uVar4 + 1;
        }
        if (uVar15 != uVar8) {
          do {
            lVar16 = *(long *)(param_1 + 0xa8);
            puVar12 = (undefined8 *)(lVar16 + (ulong)uVar15 * 0x50);
            if (puVar12 == (undefined8 *)0x0) break;
            puVar22 = (undefined4 *)*puVar12;
            uVar21 = (ulong)uVar15;
            if (puVar22 == (undefined4 *)0x0) {
              uVar20 = 0;
              plVar10 = (long *)(lVar16 + uVar21 * 0x50 + 8);
            }
            else {
              *puVar22 = 1;
              uVar20 = *(undefined8 *)(puVar22 + 2);
              plVar10 = (long *)(puVar22 + 4);
            }
            lVar17 = lVar16 + uVar21 * 0x50;
            lVar19 = *plVar10;
            pcVar18 = (char *)(lVar17 + 0x29);
            if (*pcVar18 == '\0') {
              lVar17 = *(long *)(lVar17 + 0x10);
              if (lVar19 == 0) {
                plVar10 = (long *)(lVar16 + uVar21 * 0x50 + 0x30);
                plVar9 = (long *)*plVar10;
                iVar11 = *(int *)(lVar17 + 0xc);
                uVar5 = *(undefined2 *)(lVar17 + 0x1a);
                uVar15 = puVar22[7];
                if (plVar9 == (long *)0x0) {
                  plVar9 = (long *)Aska::Global::GetAvailableMemoryManager()();
                  if ((uVar15 >> 1 & 1) == 0) {
                    pcVar14 = *(code **)(*plVar9 + 0x10);
                  }
                  else {
                    pcVar14 = *(code **)(*plVar9 + 0x18);
                  }
                }
                else if ((uVar15 >> 1 & 1) == 0) {
                  pcVar14 = *(code **)(*plVar9 + 0x10);
                }
                else {
                  pcVar14 = *(code **)(*plVar9 + 0x18);
                }
                lVar19 = (*pcVar14)(plVar9,(long)iVar11,uVar5);
                if (lVar19 != 0) {
                  uVar15 = 1;
                  goto joined_r0x0201db88;
                }
code_r0x0201dbcc:
                plVar10 = (long *)*plVar10;
                if (plVar10 == (long *)0x0) {
                  if (lVar19 != 0) {
                    operator delete[](void*)(lVar19);
                  }
                }
                else {
                  (**(code **)(*plVar10 + 0x40))(plVar10,lVar19);
                }
                uVar8 = 0;
              }
              else {
                uVar15 = 0;
joined_r0x0201db88:
                if ((puVar22 == (undefined4 *)0x0) || ((*(byte *)(puVar22 + 7) & 1) == 0)) {
                  lVar13 = lVar16 + uVar21 * 0x50;
                  uVar8 = Aska::Decompress::Decode(Aska::COMPRESSHEADER*, unsigned char*, int, Aska::IMemoryManager*, Aska::IMemoryManager*, Aska::IMemoryManager*)(lVar17,lVar19,0,*(undefined8 *)(lVar13 + 0x38),
                                          *(undefined8 *)(lVar13 + 0x40),
                                          *(undefined8 *)(lVar13 + 0x48));
                }
                else {
                  lVar13 = lVar16 + uVar21 * 0x50;
                  uVar8 = Aska::Decompress::DecodeAndStoreCache(Aska::COMPRESSHEADER*, unsigned char*, int, Aska::IMemoryManager*, Aska::IMemoryManager*, Aska::IMemoryManager*)(lVar17,lVar19,0,*(undefined8 *)(lVar13 + 0x38),
                                          *(undefined8 *)(lVar13 + 0x40),
                                          *(undefined8 *)(lVar13 + 0x48));
                }
                if ((puVar22 == (undefined4 *)0x0) || ((uVar8 & 1) == 0)) {
                  if ((uVar15 & (uVar8 ^ 1)) == 1) {
                    plVar10 = (long *)(lVar16 + uVar21 * 0x50 + 0x30);
                    goto code_r0x0201dbcc;
                  }
                  uVar8 = uVar8 & 1;
                }
                else {
                  *puVar22 = 2;
                  uVar8 = 1;
                  *(undefined1 *)(puVar22 + 8) = 1;
                  if (*(long *)(puVar22 + 4) == 0) {
                    *(undefined8 *)(puVar22 + 2) = uVar20;
                    *(long *)(puVar22 + 4) = lVar19;
                    uVar8 = 1;
                  }
                }
              }
            }
            else {
              uVar8 = 0;
            }
            if (puVar22 != (undefined4 *)0x0) {
              *puVar22 = 3;
            }
            puVar12 = *(undefined8 **)(lVar16 + uVar21 * 0x50 + 0x20);
            if (puVar12 != (undefined8 *)0x0) {
              uVar20 = 0;
              if (uVar8 == 0) {
                uVar20 = 2;
              }
              if (*pcVar18 != '\0') {
                uVar20 = 1;
              }
              (**(code **)*puVar12)(puVar12,uVar20);
            }
            *(undefined1 *)(lVar16 + uVar21 * 0x50 + 0x28) = 0;
            iVar11 = 0;
            do {
              while (*piVar1 == -1) {
                cVar6 = '\x01';
                bVar7 = (bool)ExclusiveMonitorPass(piVar1,0x10);
                if (bVar7) {
                  *piVar1 = 0;
                  cVar6 = ExclusiveMonitorsStatus();
                }
                if (cVar6 == '\0') goto code_r0x0201dd0c;
              }
              ClearExclusiveLocal();
              bVar7 = iVar11 < 0x1ff;
              iVar11 = iVar11 + 1;
            } while (bVar7);
            do {
              cVar6 = '\x01';
              bVar7 = (bool)ExclusiveMonitorPass(piVar2,0x10);
              if (bVar7) {
                *piVar2 = *piVar2 + 1;
                cVar6 = ExclusiveMonitorsStatus();
              }
            } while (cVar6 != '\0');
            do {
              if (*piVar1 != -1) {
                do {
                  ClearExclusiveLocal();
                  uVar21 = Aska::Semaphore::IsReady() const(lVar3);
                  if ((uVar21 & 1) == 0) {
                    do {
                      cVar6 = '\x01';
                      bVar7 = (bool)ExclusiveMonitorPass(piVar2,0x10);
                      if (bVar7) {
                        *piVar2 = *piVar2 + -1;
                        cVar6 = ExclusiveMonitorsStatus();
                      }
                    } while (cVar6 != '\0');
                    Aska::Thread::Sleep(unsigned int)(1);
                  }
                  else {
                    Aska::Semaphore::Wait() const(lVar3);
                  }
                  do {
                    cVar6 = '\x01';
                    bVar7 = (bool)ExclusiveMonitorPass(piVar2,0x10);
                    if (bVar7) {
                      *piVar2 = *piVar2 + 1;
                      cVar6 = ExclusiveMonitorsStatus();
                    }
                  } while (cVar6 != '\0');
                  while (*piVar1 == -1) {
                    cVar6 = '\x01';
                    bVar7 = (bool)ExclusiveMonitorPass(piVar1,0x10);
                    if (bVar7) {
                      *piVar1 = 0;
                      cVar6 = ExclusiveMonitorsStatus();
                    }
                    if (cVar6 == '\0') goto code_r0x0201dcfc;
                  }
                } while( true );
              }
              cVar6 = '\x01';
              bVar7 = (bool)ExclusiveMonitorPass(piVar1,0x10);
              if (bVar7) {
                *piVar1 = 0;
                cVar6 = ExclusiveMonitorsStatus();
              }
            } while (cVar6 != '\0');
code_r0x0201dcfc:
            do {
              cVar6 = '\x01';
              bVar7 = (bool)ExclusiveMonitorPass(piVar2,0x10);
              if (bVar7) {
                *piVar2 = *piVar2 + -1;
                cVar6 = ExclusiveMonitorsStatus();
              }
            } while (cVar6 != '\0');
code_r0x0201dd0c:
            DataMemoryBarrier(2,3);
            iVar11 = 0;
            if (*(int *)(param_1 + 0x9c) + 1U < *(uint *)(param_1 + 0xa0)) {
              iVar11 = *(int *)(param_1 + 0x9c) + 1;
            }
            *(int *)(param_1 + 0x9c) = iVar11;
            DataMemoryBarrier(2,3);
            *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
            DataMemoryBarrier(2,3);
            if (0x14 < *(int *)(param_1 + 0xec)) {
              do {
                cVar6 = '\x01';
                bVar7 = (bool)ExclusiveMonitorPass(piVar2,0x10);
                if (bVar7) {
                  *piVar2 = *piVar2 + -1;
                  cVar6 = ExclusiveMonitorsStatus();
                }
              } while (cVar6 != '\0');
              uVar21 = Aska::Semaphore::IsReady() const(lVar3);
              if ((uVar21 & 1) != 0) {
                Aska::Semaphore::Signal() const(lVar3);
              }
            }
            uVar15 = 0;
            if (*(int *)(param_1 + 0x9c) + 1U < *(uint *)(param_1 + 0xa0)) {
              uVar15 = *(int *)(param_1 + 0x9c) + 1;
            }
          } while (uVar15 != *(uint *)(param_1 + 0x98));
        }
      }
    } while (*(char *)(param_1 + 0x89) == '\0');
  }
  return;
}

// ==== Aska::DecompressThread::Add(Aska::DecompressQueue::_DecompressArg*)
// vaddr 0x1f1dda8 | ghidra 0x201dda8 | size 572 | symbol _ZN4Aska16DecompressThread3AddEPNS_15DecompressQueue14_DecompressArgE | lib libSOA-3.7.0.so | 2026-10-04
long * _ZN4Aska16DecompressThread3AddEPNS_15DecompressQueue14_DecompressArgE
                 (long param_1,long *param_2)

{
  int *piVar1;
  int iVar2;
  char cVar3;
  bool bVar4;
  ulong uVar5;
  int iVar6;
  long lVar7;
  int *piVar8;
  long lVar9;
  long lVar10;
  long *plVar11;
  
  piVar8 = (int *)(param_1 + 0xe8);
  iVar6 = 0;
code_r0x0201ddc4:
  do {
    if (*piVar8 != -1) {
      ClearExclusiveLocal();
      bVar4 = iVar6 < 0x1ff;
      iVar6 = iVar6 + 1;
      if (bVar4) goto code_r0x0201ddc4;
      piVar1 = (int *)(param_1 + 0xec);
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
        if (bVar4) {
          *piVar1 = *piVar1 + 1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      do {
        if (*piVar8 != -1) {
          ClearExclusiveLocal();
          do {
            uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0x128);
            if ((uVar5 & 1) == 0) {
              do {
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
              Aska::Semaphore::Wait() const(param_1 + 0x128);
            }
            do {
              cVar3 = '\x01';
              bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
              if (bVar4) {
                *piVar1 = *piVar1 + 1;
                cVar3 = ExclusiveMonitorsStatus();
              }
            } while (cVar3 != '\0');
            while (*piVar8 == -1) {
              cVar3 = '\x01';
              bVar4 = (bool)ExclusiveMonitorPass(piVar8,0x10);
              if (bVar4) {
                *piVar8 = 0;
                cVar3 = ExclusiveMonitorsStatus();
              }
              if (cVar3 == '\0') goto code_r0x0201de7c;
            }
            ClearExclusiveLocal();
          } while( true );
        }
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar8,0x10);
        if (bVar4) {
          *piVar8 = 0;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
code_r0x0201de7c:
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
        if (bVar4) {
          *piVar1 = *piVar1 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
code_r0x0201de8c:
      DataMemoryBarrier(2,3);
      lVar7 = (long)*(int *)(param_1 + 0x98);
      if (*(int *)(param_1 + 0x9c) != *(int *)(param_1 + 0x98)) {
        lVar9 = *(long *)(param_1 + 0xa8);
        plVar11 = (long *)(lVar9 + lVar7 * 0x50);
        if (plVar11 == (long *)0x0) goto code_r0x0201df88;
        lVar10 = 0;
        if ((undefined4 *)param_2[1] != (undefined4 *)0x0) {
          *(undefined4 *)param_2[1] = 0;
          *(int *)(param_2[1] + 4) = (int)param_2[9];
          *(undefined1 *)(param_2[1] + 0x20) = 0;
          lVar10 = param_2[1];
        }
        *plVar11 = lVar10;
        lVar10 = lVar9 + lVar7 * 0x50;
        *(long *)(lVar10 + 8) = param_2[2];
        *(long *)(lVar10 + 0x10) = *param_2;
        *(long *)(lVar10 + 0x20) = param_2[4];
        *(long *)(lVar10 + 0x30) = param_2[5];
        *(long *)(lVar10 + 0x38) = param_2[6];
        *(long *)(lVar10 + 0x40) = param_2[7];
        *(long *)(lVar10 + 0x48) = param_2[8];
        *(undefined2 *)(lVar10 + 0x28) = 1;
        lVar10 = *param_2;
        if (0 < (int)param_2[3]) {
          iVar6 = 0;
          do {
            if (*(uint *)(lVar10 + 0x1c) == 0) goto code_r0x0201dea0;
            iVar6 = iVar6 + 1;
            lVar10 = lVar10 + (ulong)*(uint *)(lVar10 + 0x1c);
          } while (iVar6 < (int)param_2[3]);
        }
        if (lVar10 != 0) {
          *(undefined4 *)(lVar9 + lVar7 * 0x50 + 0x18) = *(undefined4 *)(lVar10 + 8);
          iVar6 = *(int *)(param_1 + 0x98);
          if (*(int *)(param_1 + 0x9c) != iVar6) {
            iVar2 = 0;
            if (iVar6 + 1U < *(uint *)(param_1 + 0xa0)) {
              iVar2 = iVar6 + 1;
            }
            *(int *)(param_1 + 0x98) = iVar2;
          }
          goto code_r0x0201df88;
        }
      }
code_r0x0201dea0:
      plVar11 = (long *)0x0;
code_r0x0201df88:
      DataMemoryBarrier(2,3);
      *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
      DataMemoryBarrier(2,3);
      piVar8 = (int *)(param_1 + 0xec);
      if (0x14 < *piVar8) {
        do {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar8,0x10);
          if (bVar4) {
            *piVar8 = *piVar8 + -1;
            cVar3 = ExclusiveMonitorsStatus();
          }
        } while (cVar3 != '\0');
        uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0x128);
        if ((uVar5 & 1) != 0) {
          Aska::Semaphore::Signal() const(param_1 + 0x128);
        }
      }
      return plVar11;
    }
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar8,0x10);
    if (bVar4) {
      *piVar8 = 0;
      cVar3 = ExclusiveMonitorsStatus();
    }
    if (cVar3 == '\0') goto code_r0x0201de8c;
  } while( true );
}

// ==== Aska::DecompressThread::CleanQueue()
// vaddr 0x1f1dfe4 | ghidra 0x201dfe4 | size 424 | symbol _ZN4Aska16DecompressThread10CleanQueueEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16DecompressThread10CleanQueueEv(long param_1)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  char cVar4;
  bool bVar5;
  ulong uVar6;
  int iVar7;
  int *piVar8;
  uint uVar9;
  
  piVar8 = (int *)(param_1 + 0xe8);
  iVar7 = 0;
code_r0x0201dffc:
  if (*piVar8 == -1) {
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar8,0x10);
    if (bVar5) {
      *piVar8 = 0;
      cVar4 = ExclusiveMonitorsStatus();
    }
    if (cVar4 == '\0') goto code_r0x0201e0c4;
    goto code_r0x0201dffc;
  }
  ClearExclusiveLocal();
  bVar5 = iVar7 < 0x1ff;
  iVar7 = iVar7 + 1;
  if (bVar5) goto code_r0x0201dffc;
  piVar1 = (int *)(param_1 + 0xec);
  do {
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar5) {
      *piVar1 = *piVar1 + 1;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
  do {
    if (*piVar8 != -1) {
      ClearExclusiveLocal();
      do {
        uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x128);
        if ((uVar6 & 1) == 0) {
          do {
            cVar4 = '\x01';
            bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
            if (bVar5) {
              *piVar1 = *piVar1 + -1;
              cVar4 = ExclusiveMonitorsStatus();
            }
          } while (cVar4 != '\0');
          Aska::Thread::Sleep(unsigned int)(1);
        }
        else {
          Aska::Semaphore::Wait() const(param_1 + 0x128);
        }
        do {
          cVar4 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar5) {
            *piVar1 = *piVar1 + 1;
            cVar4 = ExclusiveMonitorsStatus();
          }
        } while (cVar4 != '\0');
        while (*piVar8 == -1) {
          cVar4 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(piVar8,0x10);
          if (bVar5) {
            *piVar8 = 0;
            cVar4 = ExclusiveMonitorsStatus();
          }
          if (cVar4 == '\0') goto code_r0x0201e0b4;
        }
        ClearExclusiveLocal();
      } while( true );
    }
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar8,0x10);
    if (bVar5) {
      *piVar8 = 0;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
code_r0x0201e0b4:
  do {
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar5) {
      *piVar1 = *piVar1 + -1;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
code_r0x0201e0c4:
  DataMemoryBarrier(2,3);
  iVar7 = *(int *)(param_1 + 0x9c);
  uVar3 = *(uint *)(param_1 + 0xa0);
  uVar9 = 0;
  if (iVar7 + 1U < uVar3) {
    uVar9 = iVar7 + 1;
  }
  if (uVar9 != *(uint *)(param_1 + 0x98)) {
    do {
      if ((*(long *)(param_1 + 0xa8) + (ulong)uVar9 * 0x50 == 0) ||
         (*(char *)(*(long *)(param_1 + 0xa8) + (ulong)uVar9 * 0x50 + 0x28) != '\0')) break;
      iVar2 = 0;
      if (iVar7 + 1U < uVar3) {
        iVar2 = iVar7 + 1;
      }
      uVar9 = 0;
      if (iVar2 + 1U < uVar3) {
        uVar9 = iVar2 + 1;
      }
      *(int *)(param_1 + 0x9c) = iVar2;
      iVar7 = iVar2;
    } while (uVar9 != *(uint *)(param_1 + 0x98));
  }
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
  DataMemoryBarrier(2,3);
  piVar8 = (int *)(param_1 + 0xec);
  if (0x14 < *piVar8) {
    do {
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar8,0x10);
      if (bVar5) {
        *piVar8 = *piVar8 + -1;
        cVar4 = ExclusiveMonitorsStatus();
      }
    } while (cVar4 != '\0');
    uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x128);
    if ((uVar6 & 1) != 0) {
      (*(code *)PTR__ZNK4Aska9Semaphore6SignalEv_02c96cd0)(param_1 + 0x128);
      return;
    }
  }
  return;
}

// ==== Aska::DecompressThread::TElementQueue<Aska::DecompressQueue::Element, true>::~TElementQueue()
// vaddr 0x1f1e18c | ghidra 0x201e18c | size 80 | symbol _ZN4Aska16DecompressThread13TElementQueueINS_15DecompressQueue7ElementELb1EED0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16DecompressThread13TElementQueueINS_15DecompressQueue7ElementELb1EED0Ev(long *param_1)

{
  undefined *puVar1;
  
  *param_1 = (long)(
                   PTR__ZTVN4Aska16DecompressThread13TElementQueueINS_15DecompressQueue7ElementELb1EEE_02cc4be8
                   + 0x10);
  Aska::FastCriticalSection::~FastCriticalSection()(param_1 + 4);
  puVar1 = PTR__ZTVN4Aska13TDynamicQueueINS_15DecompressQueue7ElementELb1EEE_02cb8c30;
  *(undefined4 *)(param_1 + 2) = 0;
  *param_1 = (long)(puVar1 + 0x10);
  param_1[1] = 1;
  if (param_1[3] != 0) {
    operator delete[](void*)();
  }
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::TDynamicQueue<Aska::DecompressQueue::Element, true>::~TDynamicQueue()
// vaddr 0x1f1e1dc | ghidra 0x201e1dc | size 56 | symbol _ZN4Aska13TDynamicQueueINS_15DecompressQueue7ElementELb1EED2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13TDynamicQueueINS_15DecompressQueue7ElementELb1EED2Ev(long *param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZTVN4Aska13TDynamicQueueINS_15DecompressQueue7ElementELb1EEE_02cb8c30;
  *(undefined4 *)(param_1 + 2) = 0;
  *param_1 = (long)(puVar1 + 0x10);
  param_1[1] = 1;
  if (param_1[3] != 0) {
    operator delete[](void*)();
    param_1[3] = 0;
  }
  return;
}

// ==== Aska::TDynamicQueue<Aska::DecompressQueue::Element, true>::~TDynamicQueue()
// vaddr 0x1f1e214 | ghidra 0x201e214 | size 56 | symbol _ZN4Aska13TDynamicQueueINS_15DecompressQueue7ElementELb1EED0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13TDynamicQueueINS_15DecompressQueue7ElementELb1EED0Ev(long *param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZTVN4Aska13TDynamicQueueINS_15DecompressQueue7ElementELb1EEE_02cb8c30;
  *(undefined4 *)(param_1 + 2) = 0;
  *param_1 = (long)(puVar1 + 0x10);
  param_1[1] = 1;
  if (param_1[3] != 0) {
    operator delete[](void*)();
  }
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::ResourceReadyQueue::ResourceReadyQueue(unsigned int)
// vaddr 0x2238384 | ghidra 0x2338384 | size 456 | symbol _ZN4Aska18ResourceReadyQueueC2Ej | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18ResourceReadyQueueC1Ej(long *param_1,undefined4 param_2)

{
  int iVar1;
  char cVar2;
  undefined *puVar3;
  bool bVar4;
  long lVar5;
  int *piVar6;
  long lStack_38;
  
  Aska::Thread::Thread()();
  *param_1 = (long)(PTR__ZTVN4Aska18ResourceReadyQueueE_02cc45b8 + 0x10);
  *(undefined1 *)((long)param_1 + 0x11) = 0;
  *(undefined1 *)((long)param_1 + 0x12) = 0;
  Aska::Event::Event()(param_1 + 3);
  Aska::CriticalSection::CriticalSection()(param_1 + 0x10);
  *(undefined4 *)(param_1 + 0x15) = 0;
  bVar4 = true;
  Aska::Event::Create(bool, bool)(param_1 + 3,1,1);
  param_1[0x16] =
       (long)(PTR__ZTVN4Aska10TEventPortINS_18ResourceReadyQueue6EvItemEEE_02cbacd0 + 0x10);
  memset(param_1 + 0x17,0,0x44);
  lVar5 = operator new[](unsigned long, std::nothrow_t const&)(0x1000,PTR__ZSt7nothrow_02cb9a80);
  lStack_38 = 0;
  if (lVar5 == 0) {
    piVar6 = (int *)0x0;
  }
  else {
    lStack_38 = 0;
    piVar6 = (int *)Aska::TSharedPointerCode::CreateCounter(int)(0);
    if (piVar6 == (int *)0x0) {
      bVar4 = true;
    }
    else {
      do {
        cVar2 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar6,0x10);
        if (bVar4) {
          *piVar6 = *piVar6 + 1;
          cVar2 = ExclusiveMonitorsStatus();
        }
      } while (cVar2 != '\0');
      bVar4 = lVar5 == 0;
      lStack_38 = lVar5;
    }
  }
  param_1[0x24] = 0;
  param_1[0x23] = 0;
  puVar3 = PTR__ZTVN4Aska10FakeStreamE_02cb8d80;
  param_1[0x22] = 0;
  param_1[0x21] = 0;
  param_1[0x29] = 0;
  param_1[0x28] = 0;
  param_1[0x2b] = 0;
  param_1[0x2a] = 0;
  param_1[0x20] = (long)(puVar3 + 0x10);
  param_1[0x26] = 0;
  param_1[0x25] = 0;
  param_1[0x27] = (long)(puVar3 + 0x10);
  param_1[0x32] = 0;
  param_1[0x2f] = 0;
  param_1[0x2e] = 0;
  param_1[0x31] = 0;
  param_1[0x30] = 0;
  param_1[0x2d] = 0;
  param_1[0x2c] = 0;
  *(undefined4 *)(param_1 + 0x33) = 0;
  *(undefined4 *)((long)param_1 + 0x21c) = 0x10;
  if (!bVar4) {
    param_1[0x30] = lStack_38;
    param_1[0x31] = (long)piVar6;
    lVar5 = lStack_38;
    if (piVar6 != (int *)0x0) {
      do {
        cVar2 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar6,0x10);
        if (bVar4) {
          *piVar6 = *piVar6 + 1;
          cVar2 = ExclusiveMonitorsStatus();
        }
      } while (cVar2 != '\0');
      lVar5 = param_1[0x30];
    }
    if (lVar5 != 0) {
      *(undefined4 *)(param_1 + 0x33) = 0x1000;
      param_1[0x32] = lStack_38;
    }
  }
  if (piVar6 != (int *)0x0) {
    do {
      iVar1 = *piVar6;
      cVar2 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar6,0x10);
      if (bVar4) {
        *piVar6 = iVar1 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    if (iVar1 + -1 != 0) goto code_r0x0233851c;
  }
  if (lStack_38 != 0) {
    operator delete[](void*)();
  }
  if (piVar6 != (int *)0x0) {
    Aska::TSharedPointerCode::DeleteCounter(int*)(piVar6);
  }
code_r0x0233851c:
  Aska::CriticalSection::CriticalSection()(param_1 + 0x44);
                    /* WARNING: Could not recover jumptable at 0x02338548. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*param_1 + 0x18))(param_1,0xd4,param_2);
  return;
}

// ==== Aska::ResourceReadyQueue::ResourceReadyQueue(unsigned int, unsigned int)
// vaddr 0x223854c | ghidra 0x233854c | size 460 | symbol _ZN4Aska18ResourceReadyQueueC2Ejj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18ResourceReadyQueueC1Ejj(long *param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  char cVar2;
  undefined *puVar3;
  bool bVar4;
  long lVar5;
  int *piVar6;
  long lStack_38;
  
  Aska::Thread::Thread()();
  *param_1 = (long)(PTR__ZTVN4Aska18ResourceReadyQueueE_02cc45b8 + 0x10);
  *(undefined1 *)((long)param_1 + 0x11) = 0;
  *(undefined1 *)((long)param_1 + 0x12) = 0;
  Aska::Event::Event()(param_1 + 3);
  Aska::CriticalSection::CriticalSection()(param_1 + 0x10);
  *(undefined4 *)(param_1 + 0x15) = 0;
  bVar4 = true;
  Aska::Event::Create(bool, bool)(param_1 + 3,1,1);
  param_1[0x16] =
       (long)(PTR__ZTVN4Aska10TEventPortINS_18ResourceReadyQueue6EvItemEEE_02cbacd0 + 0x10);
  memset(param_1 + 0x17,0,0x44);
  lVar5 = operator new[](unsigned long, std::nothrow_t const&)(0x1000,PTR__ZSt7nothrow_02cb9a80);
  lStack_38 = 0;
  if (lVar5 == 0) {
    piVar6 = (int *)0x0;
  }
  else {
    lStack_38 = 0;
    piVar6 = (int *)Aska::TSharedPointerCode::CreateCounter(int)(0);
    if (piVar6 == (int *)0x0) {
      bVar4 = true;
    }
    else {
      do {
        cVar2 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar6,0x10);
        if (bVar4) {
          *piVar6 = *piVar6 + 1;
          cVar2 = ExclusiveMonitorsStatus();
        }
      } while (cVar2 != '\0');
      bVar4 = lVar5 == 0;
      lStack_38 = lVar5;
    }
  }
  param_1[0x24] = 0;
  param_1[0x23] = 0;
  puVar3 = PTR__ZTVN4Aska10FakeStreamE_02cb8d80;
  param_1[0x22] = 0;
  param_1[0x21] = 0;
  param_1[0x29] = 0;
  param_1[0x28] = 0;
  param_1[0x2b] = 0;
  param_1[0x2a] = 0;
  param_1[0x20] = (long)(puVar3 + 0x10);
  param_1[0x26] = 0;
  param_1[0x25] = 0;
  param_1[0x27] = (long)(puVar3 + 0x10);
  param_1[0x32] = 0;
  param_1[0x2f] = 0;
  param_1[0x2e] = 0;
  param_1[0x31] = 0;
  param_1[0x30] = 0;
  param_1[0x2d] = 0;
  param_1[0x2c] = 0;
  *(undefined4 *)(param_1 + 0x33) = 0;
  *(undefined4 *)((long)param_1 + 0x21c) = 0x10;
  if (!bVar4) {
    param_1[0x30] = lStack_38;
    param_1[0x31] = (long)piVar6;
    lVar5 = lStack_38;
    if (piVar6 != (int *)0x0) {
      do {
        cVar2 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar6,0x10);
        if (bVar4) {
          *piVar6 = *piVar6 + 1;
          cVar2 = ExclusiveMonitorsStatus();
        }
      } while (cVar2 != '\0');
      lVar5 = param_1[0x30];
    }
    if (lVar5 != 0) {
      *(undefined4 *)(param_1 + 0x33) = 0x1000;
      param_1[0x32] = lStack_38;
    }
  }
  if (piVar6 != (int *)0x0) {
    do {
      iVar1 = *piVar6;
      cVar2 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar6,0x10);
      if (bVar4) {
        *piVar6 = iVar1 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    if (iVar1 + -1 != 0) goto code_r0x023386e8;
  }
  if (lStack_38 != 0) {
    operator delete[](void*)();
  }
  if (piVar6 != (int *)0x0) {
    Aska::TSharedPointerCode::DeleteCounter(int*)(piVar6);
  }
code_r0x023386e8:
  Aska::CriticalSection::CriticalSection()(param_1 + 0x44);
                    /* WARNING: Could not recover jumptable at 0x02338714. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*param_1 + 0x18))(param_1,param_2,param_3);
  return;
}

// ==== Aska::ResourceReadyQueue::~ResourceReadyQueue()
// vaddr 0x2238718 | ghidra 0x2338718 | size 392 | symbol _ZN4Aska18ResourceReadyQueueD2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18ResourceReadyQueueD1Ev(long *param_1)

{
  int iVar1;
  char cVar2;
  bool bVar3;
  long *plVar4;
  long lVar5;
  int *piVar6;
  long *plVar7;
  
  *param_1 = (long)(PTR__ZTVN4Aska18ResourceReadyQueueE_02cc45b8 + 0x10);
  Aska::ResourceReadyQueue::Term()();
  Aska::CriticalSection::~CriticalSection()(param_1 + 0x44);
  Aska::MappedResourceFilter::~MappedResourceFilter()(param_1 + 0x20);
  piVar6 = (int *)param_1[0x1d];
  if (piVar6 == (int *)0x0) {
code_r0x02338764:
    if ((long *)param_1[0x1c] != (long *)0x0) {
      (**(code **)(*(long *)param_1[0x1c] + 0xd0))();
    }
    if (param_1[0x1d] != 0) {
      Aska::TSharedPointerCode::DeleteCounter(int*)();
    }
  }
  else {
    do {
      iVar1 = *piVar6;
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar6,0x10);
      if (bVar3) {
        *piVar6 = iVar1 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    if (iVar1 + -1 == 0) goto code_r0x02338764;
  }
  piVar6 = (int *)param_1[0x1b];
  param_1[0x1c] = 0;
  param_1[0x1d] = 0;
  if (piVar6 == (int *)0x0) {
code_r0x023387a4:
    if ((long *)param_1[0x1a] != (long *)0x0) {
      (**(code **)(*(long *)param_1[0x1a] + 8))();
    }
    if (param_1[0x1b] != 0) {
      Aska::TSharedPointerCode::DeleteCounter(int*)();
    }
  }
  else {
    do {
      iVar1 = *piVar6;
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar6,0x10);
      if (bVar3) {
        *piVar6 = iVar1 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    if (iVar1 + -1 == 0) goto code_r0x023387a4;
  }
  plVar7 = param_1 + 0x17;
  plVar4 = (long *)*plVar7;
  param_1[0x1a] = 0;
  param_1[0x1b] = 0;
  piVar6 = (int *)param_1[0x18];
  param_1[0x16] =
       (long)(PTR__ZTVN4Aska10TEventPortINS_18ResourceReadyQueue6EvItemEEE_02cbacd0 + 0x10);
  if (plVar4 == (long *)0x0) {
    param_1[0x19] = 0;
    if (piVar6 == (int *)0x0) goto code_r0x011c7c30;
    do {
      iVar1 = *piVar6;
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar6,0x10);
      if (bVar3) {
        *piVar6 = iVar1 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    if (iVar1 + -1 != 0) goto code_r0x011c7c30;
    if ((long *)*plVar7 == (long *)0x0) goto code_r0x02338828;
    (**(code **)(*(long *)*plVar7 + 8))();
    lVar5 = param_1[0x18];
  }
  else {
    if (piVar6 == (int *)0x0) {
code_r0x02338808:
      (**(code **)(*plVar4 + 8))();
code_r0x02338814:
      if (param_1[0x18] != 0) {
        Aska::TSharedPointerCode::DeleteCounter(int*)();
      }
    }
    else {
      do {
        iVar1 = *piVar6;
        cVar2 = '\x01';
        bVar3 = (bool)ExclusiveMonitorPass(piVar6,0x10);
        if (bVar3) {
          *piVar6 = iVar1 + -1;
          cVar2 = ExclusiveMonitorsStatus();
        }
      } while (cVar2 != '\0');
      if (iVar1 + -1 == 0) {
        plVar4 = (long *)*plVar7;
        if (plVar4 != (long *)0x0) goto code_r0x02338808;
        goto code_r0x02338814;
      }
    }
    param_1[0x18] = 0;
    param_1[0x19] = 0;
    *plVar7 = 0;
code_r0x02338828:
    lVar5 = param_1[0x18];
  }
  if (lVar5 != 0) {
    Aska::TSharedPointerCode::DeleteCounter(int*)();
  }
code_r0x011c7c30:
  *plVar7 = 0;
  param_1[0x18] = 0;
  Aska::Event::Exit()(param_1 + 3);
  Aska::CriticalSection::~CriticalSection()(param_1 + 0x10);
  Aska::Event::Exit()(param_1 + 3);
  (*(code *)PTR__ZN4Aska6ThreadD1Ev_02c9be08)(param_1);
  return;
}

// ==== Aska::TEventPort<Aska::ResourceReadyQueue::EvItem>::~TEventPort()
// vaddr 0x22389c8 | ghidra 0x23389c8 | size 196 | symbol _ZN4Aska10TEventPortINS_18ResourceReadyQueue6EvItemEED2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10TEventPortINS_18ResourceReadyQueue6EvItemEED2Ev(long *param_1)

{
  int iVar1;
  char cVar2;
  bool bVar3;
  long *plVar4;
  long lVar5;
  int *piVar6;
  long *plVar7;
  
  *param_1 = (long)(PTR__ZTVN4Aska10TEventPortINS_18ResourceReadyQueue6EvItemEEE_02cbacd0 + 0x10);
  plVar7 = param_1 + 1;
  plVar4 = (long *)*plVar7;
  piVar6 = (int *)param_1[2];
  if (plVar4 == (long *)0x0) {
    param_1[3] = 0;
    if (piVar6 == (int *)0x0) goto code_r0x02338a7c;
    do {
      iVar1 = *piVar6;
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar6,0x10);
      if (bVar3) {
        *piVar6 = iVar1 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    if (iVar1 + -1 != 0) goto code_r0x02338a7c;
    if ((long *)*plVar7 == (long *)0x0) goto code_r0x02338a34;
    (**(code **)(*(long *)*plVar7 + 8))();
    lVar5 = param_1[2];
  }
  else {
    if (piVar6 == (int *)0x0) {
code_r0x02338a14:
      (**(code **)(*plVar4 + 8))();
code_r0x02338a20:
      if (param_1[2] != 0) {
        Aska::TSharedPointerCode::DeleteCounter(int*)();
      }
    }
    else {
      do {
        iVar1 = *piVar6;
        cVar2 = '\x01';
        bVar3 = (bool)ExclusiveMonitorPass(piVar6,0x10);
        if (bVar3) {
          *piVar6 = iVar1 + -1;
          cVar2 = ExclusiveMonitorsStatus();
        }
      } while (cVar2 != '\0');
      if (iVar1 + -1 == 0) {
        plVar4 = (long *)*plVar7;
        if (plVar4 != (long *)0x0) goto code_r0x02338a14;
        goto code_r0x02338a20;
      }
    }
    *plVar7 = 0;
    param_1[2] = 0;
    param_1[3] = 0;
code_r0x02338a34:
    lVar5 = param_1[2];
  }
  if (lVar5 != 0) {
    Aska::TSharedPointerCode::DeleteCounter(int*)();
  }
code_r0x02338a7c:
  param_1[1] = 0;
  param_1[2] = 0;
  return;
}

// ==== Aska::ResourceReadyQueue::~ResourceReadyQueue()
// vaddr 0x2238a8c | ghidra 0x2338a8c | size 24 | symbol _ZN4Aska18ResourceReadyQueueD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18ResourceReadyQueueD0Ev(undefined8 param_1)

{
  Aska::ResourceReadyQueue::~ResourceReadyQueue()();
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::ResourceReadyQueue::Init(unsigned int, unsigned int)
// vaddr 0x2238aa4 | ghidra 0x2338aa4 | size 564 | symbol _ZN4Aska18ResourceReadyQueue4InitEjj | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska18ResourceReadyQueue4InitEjj(long param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  char cVar2;
  bool bVar3;
  bool bVar4;
  long *plVar5;
  long *plVar6;
  ulong uVar7;
  int *piVar8;
  long *plVar9;
  
  if (*(long *)(param_1 + 0x18) == 0) {
    return 0;
  }
  if (*(char *)(param_1 + 0x11) != '\0') {
    return 1;
  }
  *(undefined1 *)(param_1 + 0x12) = 0;
  plVar5 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x78,PTR__ZSt7nothrow_02cb9a80);
  if (plVar5 != (long *)0x0) {
    *plVar5 = (long)(PTR__ZTVN4Aska11TEventQueueINS_18ResourceReadyQueue6EvItemEEE_02cbe178 + 0x10);
    plVar5[1] = 0;
    Aska::Event::Event()(plVar5 + 2);
  }
  plVar9 = (long *)(param_1 + 0xd0);
  plVar6 = (long *)*plVar9;
  if (plVar6 != plVar5) {
    piVar8 = *(int **)(param_1 + 0xd8);
    if (piVar8 == (int *)0x0) {
code_r0x02338b40:
      if (plVar6 != (long *)0x0) {
        (**(code **)(*plVar6 + 8))();
      }
      if (*(long *)(param_1 + 0xd8) != 0) {
        Aska::TSharedPointerCode::DeleteCounter(int*)();
      }
    }
    else {
      do {
        iVar1 = *piVar8;
        cVar2 = '\x01';
        bVar3 = (bool)ExclusiveMonitorPass(piVar8,0x10);
        if (bVar3) {
          *piVar8 = iVar1 + -1;
          cVar2 = ExclusiveMonitorsStatus();
        }
      } while (cVar2 != '\0');
      if (iVar1 + -1 == 0) {
        plVar6 = (long *)*plVar9;
        goto code_r0x02338b40;
      }
    }
    *plVar9 = 0;
    *(undefined8 *)(param_1 + 0xd8) = 0;
    if (plVar5 != (long *)0x0) {
      piVar8 = (int *)Aska::TSharedPointerCode::CreateCounter(int)(0);
      *(int **)(param_1 + 0xd8) = piVar8;
      if (piVar8 != (int *)0x0) {
        *plVar9 = (long)plVar5;
        do {
          cVar2 = '\x01';
          bVar3 = (bool)ExclusiveMonitorPass(piVar8,0x10);
          if (bVar3) {
            *piVar8 = *piVar8 + 1;
            cVar2 = ExclusiveMonitorsStatus();
          }
        } while (cVar2 != '\0');
      }
    }
  }
  plVar5 = (long *)0x0;
  if (*plVar9 == 0) {
code_r0x02338be4:
    if (plVar5 == (long *)0x0) {
      return 0;
    }
    piVar8 = *(int **)(param_1 + 0xd8);
    if (piVar8 == (int *)0x0) goto code_r0x02338ca8;
    do {
      bVar4 = *piVar8 + -1 == 0;
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar8,0x10);
      if (bVar3) {
        *piVar8 = *piVar8 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
code_r0x02338c00:
    if (!bVar4) goto code_r0x02338cc0;
    plVar5 = (long *)*plVar9;
    if (plVar5 != (long *)0x0) goto code_r0x02338ca8;
  }
  else {
    uVar7 = Aska::TEventQueue<Aska::ResourceReadyQueue::EvItem>::Create(unsigned int, bool, bool)(*plVar9,param_3,1,0);
    if ((uVar7 & 1) == 0) {
      plVar5 = (long *)*plVar9;
      goto code_r0x02338be4;
    }
    uVar7 = Aska::TEventPort<Aska::ResourceReadyQueue::EvItem>::Create(Aska::TSharedPointer<Aska::TEventQueue<Aska::ResourceReadyQueue::EvItem> >&)(param_1 + 0xb0,plVar9);
    if ((uVar7 & 1) == 0) {
      plVar5 = (long *)*plVar9;
      if (plVar5 == (long *)0x0) {
        return 0;
      }
      piVar8 = *(int **)(param_1 + 0xd8);
      if (piVar8 == (int *)0x0) goto code_r0x02338ca8;
      do {
        bVar4 = *piVar8 + -1 == 0;
        cVar2 = '\x01';
        bVar3 = (bool)ExclusiveMonitorPass(piVar8,0x10);
        if (bVar3) {
          *piVar8 = *piVar8 + -1;
          cVar2 = ExclusiveMonitorsStatus();
        }
      } while (cVar2 != '\0');
      goto code_r0x02338c00;
    }
    uVar7 = Aska::Thread::Create(bool, int, int, bool)(param_1,0,param_2,0x9800,0);
    if ((uVar7 & 1) != 0) {
      *(undefined8 *)(param_1 + 0x248) = 0;
      *(undefined1 *)(param_1 + 0x11) = 1;
      return 1;
    }
    plVar6 = (long *)(param_1 + 0xb8);
    plVar5 = (long *)*plVar6;
    if (plVar5 != (long *)0x0) {
      piVar8 = *(int **)(param_1 + 0xc0);
      if (piVar8 == (int *)0x0) {
code_r0x02338c64:
        (**(code **)(*plVar5 + 8))();
code_r0x02338c70:
        if (*(long *)(param_1 + 0xc0) != 0) {
          Aska::TSharedPointerCode::DeleteCounter(int*)();
        }
      }
      else {
        do {
          iVar1 = *piVar8;
          cVar2 = '\x01';
          bVar3 = (bool)ExclusiveMonitorPass(piVar8,0x10);
          if (bVar3) {
            *piVar8 = iVar1 + -1;
            cVar2 = ExclusiveMonitorsStatus();
          }
        } while (cVar2 != '\0');
        if (iVar1 + -1 == 0) {
          plVar5 = (long *)*plVar6;
          if (plVar5 != (long *)0x0) goto code_r0x02338c64;
          goto code_r0x02338c70;
        }
      }
      *plVar6 = 0;
      *(undefined8 *)(param_1 + 0xc0) = 0;
    }
    plVar5 = *(long **)(param_1 + 0xd0);
    *(undefined8 *)(param_1 + 200) = 0;
    if (plVar5 == (long *)0x0) {
      return 0;
    }
    piVar8 = *(int **)(param_1 + 0xd8);
    if (piVar8 != (int *)0x0) {
      do {
        bVar4 = *piVar8 + -1 == 0;
        cVar2 = '\x01';
        bVar3 = (bool)ExclusiveMonitorPass(piVar8,0x10);
        if (bVar3) {
          *piVar8 = *piVar8 + -1;
          cVar2 = ExclusiveMonitorsStatus();
        }
      } while (cVar2 != '\0');
      goto code_r0x02338c00;
    }
code_r0x02338ca8:
    (**(code **)(*plVar5 + 8))();
  }
  if (*(long *)(param_1 + 0xd8) != 0) {
    Aska::TSharedPointerCode::DeleteCounter(int*)();
  }
code_r0x02338cc0:
  *plVar9 = 0;
  *(undefined8 *)(param_1 + 0xd8) = 0;
  return 0;
}

// ==== Aska::TEventQueue<Aska::ResourceReadyQueue::EvItem>::Create(unsigned int, bool, bool)
// vaddr 0x2238cd8 | ghidra 0x2338cd8 | size 420 | symbol _ZN4Aska11TEventQueueINS_18ResourceReadyQueue6EvItemEE6CreateEjbb | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska11TEventQueueINS_18ResourceReadyQueue6EvItemEE6CreateEjbb
          (long param_1,undefined4 param_2,byte param_3,byte param_4)

{
  long *plVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined8 uVar5;
  long *plVar6;
  ulong uVar7;
  
  if (*(long *)(param_1 + 8) == 0) {
    plVar6 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x120,PTR__ZSt7nothrow_02cb9a80);
    if (plVar6 == (long *)0x0) {
      *(undefined8 *)(param_1 + 8) = 0;
    }
    else {
      plVar1 = plVar6 + 1;
      *plVar6 = (long)(PTR__ZTVN4Aska14TPriorityQueueINS_18ResourceReadyQueue6EvItemELb1EEE_02cc15c0
                      + 0x10);
      Aska::CriticalSection::CriticalSection()(plVar1);
      puVar4 = PTR__ZTVN4Aska5TListINS_13TEventElementINS_18ResourceReadyQueue6EvItemEEEEE_02cc1958;
      *(undefined1 *)(plVar6 + 0xb) = 1;
      puVar2 = PTR__ZTVN4Aska13TEventElementINS_18ResourceReadyQueue6EvItemEEE_02cb97c0;
      plVar6[9] = (long)(plVar6 + 7);
      plVar6[10] = 0;
      plVar6[8] = (long)(plVar6 + 7);
      plVar6[0x17] = 0;
      plVar6[0x14] = 0;
      plVar6[0x15] = 0;
      *(undefined4 *)(plVar6 + 0x16) = 0;
      *(undefined4 *)(plVar6 + 0x18) = 0;
      *(undefined4 *)(plVar6 + 0x1a) = 0;
      *(undefined4 *)(plVar6 + 0x1c) = 0;
      plVar6[0xf] = 0;
      plVar6[0xe] = 0;
      plVar6[0x11] = 0;
      plVar6[0x10] = 0;
      plVar6[0xd] = 0;
      plVar6[0xc] = 0;
      puVar3 = PTR__ZTVN4Aska9TBitArrayIjLb0EEE_02cba038;
      plVar6[0x20] = 0;
      plVar6[0x21] = 0;
      *(undefined1 *)(plVar6 + 0x1f) = 0;
      plVar6[0x1d] = 0;
      plVar6[0x1e] = 0;
      plVar6[0x1b] = (long)(puVar3 + 0x10);
      puVar3 = PTR__ZTVN4Aska14TPriorityQueueINS_18ResourceReadyQueue6EvItemELb1EE6MyPoolE_02cbd678;
      plVar6[0x12] = -1;
      plVar6[0x13] = 0;
      plVar6[7] = (long)(puVar2 + 0x10);
      plVar6[6] = (long)(puVar4 + 0x10);
      plVar6[0x19] = (long)(puVar3 + 0x10);
      *(byte *)(plVar6 + 0x23) = param_3 & 1;
      *(byte *)((long)plVar6 + 0x119) = param_4 & 1;
      Aska::CriticalSection::Enter() const(plVar1);
      Aska::TPoolLegacy<Aska::TEventElement<Aska::ResourceReadyQueue::EvItem>, false>::SecurePool(unsigned int, bool, void const*, unsigned int const*)(plVar6 + 0x19,param_2,1,0,0);
      Aska::CriticalSection::Leave() const(plVar1);
      *(long **)(param_1 + 8) = plVar6;
      if (((*(char *)((long)plVar6 + 0x119) != '\0') ||
          ((*(uint *)(plVar6 + 0x1e) & 0x3fffffff) != 0)) &&
         (uVar7 = Aska::Event::Create(bool, bool)(param_1 + 0x10,0,0), (uVar7 & 1) != 0)) goto code_r0x02338d00;
    }
    Aska::Event::Exit()(param_1 + 0x10);
    uVar5 = 0;
    if (*(long **)(param_1 + 8) != (long *)0x0) {
      (**(code **)(**(long **)(param_1 + 8) + 8))();
      uVar5 = 0;
      *(undefined8 *)(param_1 + 8) = 0;
    }
  }
  else {
code_r0x02338d00:
    uVar5 = 1;
  }
  return uVar5;
}

// ==== Aska::TEventPort<Aska::ResourceReadyQueue::EvItem>::Create(Aska::TSharedPointer<Aska::TEventQueue<Aska::ResourceReadyQueue::EvItem> >&)
// vaddr 0x2238e7c | ghidra 0x2338e7c | size 284 | symbol _ZN4Aska10TEventPortINS_18ResourceReadyQueue6EvItemEE6CreateERNS_14TSharedPointerINS_11TEventQueueIS2_EEEE | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska10TEventPortINS_18ResourceReadyQueue6EvItemEE6CreateERNS_14TSharedPointerINS_11TEventQueueIS2_EEEE
          (long param_1,long *param_2)

{
  int iVar1;
  char cVar2;
  bool bVar3;
  long *plVar4;
  int *piVar5;
  long lVar6;
  long *plVar7;
  
  if (*(long *)(param_1 + 0x18) == *param_2) {
    return 1;
  }
  plVar7 = (long *)(param_1 + 8);
  plVar4 = (long *)*plVar7;
  if (plVar4 == (long *)0x0) goto code_r0x02338ee8;
  piVar5 = *(int **)(param_1 + 0x10);
  if (piVar5 == (int *)0x0) {
code_r0x02338ecc:
    (**(code **)(*plVar4 + 8))();
code_r0x02338ed8:
    if (*(long *)(param_1 + 0x10) != 0) {
      Aska::TSharedPointerCode::DeleteCounter(int*)();
    }
  }
  else {
    do {
      iVar1 = *piVar5;
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar5,0x10);
      if (bVar3) {
        *piVar5 = iVar1 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    if (iVar1 + -1 == 0) {
      plVar4 = (long *)*plVar7;
      if (plVar4 != (long *)0x0) goto code_r0x02338ecc;
      goto code_r0x02338ed8;
    }
  }
  *plVar7 = 0;
  *(undefined8 *)(param_1 + 0x10) = 0;
code_r0x02338ee8:
  *(undefined8 *)(param_1 + 0x18) = 0;
  lVar6 = *(long *)(*param_2 + 8);
  if ((lVar6 != 0) &&
     (((*(char *)(lVar6 + 0x119) != '\0' || ((*(uint *)(lVar6 + 0xf0) & 0x3fffffff) != 0)) &&
      (*(long *)(*param_2 + 0x10) != 0)))) {
    piVar5 = *(int **)(param_1 + 0x10);
    if (piVar5 != (int *)0x0) {
      do {
        iVar1 = *piVar5;
        cVar2 = '\x01';
        bVar3 = (bool)ExclusiveMonitorPass(piVar5,0x10);
        if (bVar3) {
          *piVar5 = iVar1 + -1;
          cVar2 = ExclusiveMonitorsStatus();
        }
      } while (cVar2 != '\0');
      if (iVar1 + -1 == 0) {
        if ((long *)*plVar7 != (long *)0x0) {
          (**(code **)(*(long *)*plVar7 + 8))();
        }
        if (*(long *)(param_1 + 0x10) != 0) {
          Aska::TSharedPointerCode::DeleteCounter(int*)();
        }
      }
    }
    *plVar7 = 0;
    *(undefined8 *)(param_1 + 0x10) = 0;
    piVar5 = (int *)param_2[1];
    *(int **)(param_1 + 0x10) = piVar5;
    *(long *)(param_1 + 8) = *param_2;
    if (piVar5 != (int *)0x0) {
      do {
        cVar2 = '\x01';
        bVar3 = (bool)ExclusiveMonitorPass(piVar5,0x10);
        if (bVar3) {
          *piVar5 = *piVar5 + 1;
          cVar2 = ExclusiveMonitorsStatus();
        }
      } while (cVar2 != '\0');
    }
    *(long *)(param_1 + 0x18) = *param_2;
    return 1;
  }
  return 0;
}

// ==== Aska::ResourceReadyQueue::Term()
// vaddr 0x2238f98 | ghidra 0x2338f98 | size 284 | symbol _ZN4Aska18ResourceReadyQueue4TermEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18ResourceReadyQueue4TermEv(long param_1)

{
  int iVar1;
  char cVar2;
  bool bVar3;
  undefined4 uVar4;
  long *plVar5;
  int *piVar6;
  long lVar7;
  long *plVar8;
  
  if (*(char *)(param_1 + 0x11) == '\0') goto code_r0x023390a4;
  if (*(char *)(param_1 + 0x12) == '\0') {
    *(undefined1 *)(param_1 + 0x12) = 1;
    lVar7 = *(long *)(param_1 + 200);
    if (lVar7 != 0) {
      Aska::Thread::GetCurrentID()();
      uVar4 = gettid();
      getpriority(0,uVar4);
      uVar4 = Aska::Thread::ConvertToIndependentPriority(int)();
      Aska::TEventQueue<Aska::ResourceReadyQueue::EvItem>::Set(Aska::ResourceReadyQueue::EvItem const*, unsigned long, unsigned long*, int)(lVar7,0,0xffffffffffffffff,0,uVar4);
    }
    Aska::Thread::WaitEnd()(param_1);
    plVar8 = (long *)(param_1 + 0xb8);
    plVar5 = (long *)*plVar8;
    if (plVar5 != (long *)0x0) {
      piVar6 = *(int **)(param_1 + 0xc0);
      if (piVar6 == (int *)0x0) {
code_r0x0233902c:
        (**(code **)(*plVar5 + 8))();
code_r0x02339038:
        if (*(long *)(param_1 + 0xc0) != 0) {
          Aska::TSharedPointerCode::DeleteCounter(int*)();
        }
      }
      else {
        do {
          iVar1 = *piVar6;
          cVar2 = '\x01';
          bVar3 = (bool)ExclusiveMonitorPass(piVar6,0x10);
          if (bVar3) {
            *piVar6 = iVar1 + -1;
            cVar2 = ExclusiveMonitorsStatus();
          }
        } while (cVar2 != '\0');
        if (iVar1 + -1 == 0) {
          plVar5 = (long *)*plVar8;
          if (plVar5 != (long *)0x0) goto code_r0x0233902c;
          goto code_r0x02339038;
        }
      }
      *plVar8 = 0;
      *(undefined8 *)(param_1 + 0xc0) = 0;
    }
    plVar8 = (long *)(param_1 + 0xd0);
    plVar5 = (long *)*plVar8;
    *(undefined8 *)(param_1 + 200) = 0;
    if (plVar5 != (long *)0x0) {
      piVar6 = *(int **)(param_1 + 0xd8);
      if (piVar6 == (int *)0x0) {
code_r0x0233907c:
        (**(code **)(*plVar5 + 8))();
code_r0x02339088:
        if (*(long *)(param_1 + 0xd8) != 0) {
          Aska::TSharedPointerCode::DeleteCounter(int*)();
        }
      }
      else {
        do {
          iVar1 = *piVar6;
          cVar2 = '\x01';
          bVar3 = (bool)ExclusiveMonitorPass(piVar6,0x10);
          if (bVar3) {
            *piVar6 = iVar1 + -1;
            cVar2 = ExclusiveMonitorsStatus();
          }
        } while (cVar2 != '\0');
        if (iVar1 + -1 == 0) {
          plVar5 = (long *)*plVar8;
          if (plVar5 != (long *)0x0) goto code_r0x0233907c;
          goto code_r0x02339088;
        }
      }
      *plVar8 = 0;
      *(undefined8 *)(param_1 + 0xd8) = 0;
    }
    Aska::Thread::Delete()(param_1);
  }
  *(undefined1 *)(param_1 + 0x11) = 0;
code_r0x023390a4:
  *(undefined1 *)(param_1 + 0x12) = 0;
  return;
}

// ==== Aska::ResourceReadyQueue::IsBusy() const
// vaddr 0x22390b4 | ghidra 0x23390b4 | size 56 | symbol _ZNK4Aska18ResourceReadyQueue6IsBusyEv | lib libSOA-3.7.0.so | 2026-10-04
uint _ZNK4Aska18ResourceReadyQueue6IsBusyEv(long *param_1)

{
  uint uVar1;
  ulong uVar2;
  
  uVar2 = (**(code **)(*param_1 + 0x28))();
  if ((uVar2 & 1) == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = Aska::Event::IsSignal() const(param_1 + 3);
    uVar1 = uVar1 ^ 1;
  }
  return uVar1 & 1;
}

// ==== Aska::ResourceReadyQueue::Wait() const
// vaddr 0x22390ec | ghidra 0x23390ec | size 112 | symbol _ZNK4Aska18ResourceReadyQueue4WaitEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK4Aska18ResourceReadyQueue4WaitEv(long *param_1)

{
  ulong uVar1;
  undefined4 uVar2;
  
  uVar1 = (**(code **)(*param_1 + 0x28))();
  if ((uVar1 & 1) == 0) {
    uVar2 = 0xfffffc44;
  }
  else {
    Aska::Event::Wait(unsigned int) const(param_1 + 3,0);
    uVar1 = (**(code **)(*param_1 + 0x28))(param_1);
    uVar2 = 0;
    if ((uVar1 & 1) != 0) {
      uVar1 = Aska::Event::IsSignal() const(param_1 + 3);
      uVar2 = 0;
      if ((uVar1 & 1) == 0) {
        uVar2 = 0xfffffc3a;
      }
    }
  }
  return uVar2;
}

// ==== Aska::ResourceReadyQueue::CalcTargetSize(Aska::IStream*, unsigned int*, unsigned long)
// vaddr 0x223915c | ghidra 0x233915c | size 204 | symbol _ZN4Aska18ResourceReadyQueue14CalcTargetSizeEPNS_7IStreamEPjm | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Possible PIC construction at 0x023391b8: Changing call to branch */
/* WARNING: Removing unreachable block (ram,0x023391bc) */
/* WARNING: Removing unreachable block (ram,0x023391c4) */
/* WARNING: Removing unreachable block (ram,0x023391d8) */
/* WARNING: Removing unreachable block (ram,0x023391f0) */

void _ZN4Aska18ResourceReadyQueue14CalcTargetSizeEPNS_7IStreamEPjm
               (long param_1,long *param_2,undefined8 param_3,undefined8 param_4)

{
  ulong uVar1;
  
  if ((param_2 != (long *)0x0) &&
     (uVar1 = (**(code **)(*param_2 + 0x10))(param_2), (uVar1 & 1) != 0)) {
    (**(code **)(*param_2 + 0x18))(param_2);
  }
  (*(code *)PTR__ZN4Aska20MappedResourceFilter6FilterEPNS_7IStreamES2_Pjm_02c94b40)
            (param_1 + 0x100,param_2,0,param_3,param_4);
  return;
}

// ==== Aska::ResourceReadyQueue::Invoke(Aska::IStream*, void**, long*, Aska::INotify*, Aska::IMemoryManager*, Aska::ResourceReadyQueue::AllocationType, bool)
// vaddr 0x2239228 | ghidra 0x2339228 | size 256 | symbol _ZN4Aska18ResourceReadyQueue6InvokeEPNS_7IStreamEPPvPlPNS_7INotifyEPNS_14IMemoryManagerENS0_14AllocationTypeEb | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska18ResourceReadyQueue6InvokeEPNS_7IStreamEPPvPlPNS_7INotifyEPNS_14IMemoryManagerENS0_14AllocationTypeEb
               (long *param_1,undefined8 param_2,undefined8 param_3,long *param_4,
               undefined8 *param_5,undefined8 param_6,undefined4 param_7,byte param_8)

{
  int iVar1;
  ulong uVar2;
  long lVar3;
  undefined8 *puVar4;
  undefined8 uStack_90;
  undefined8 uStack_88;
  undefined8 uStack_80;
  undefined8 uStack_78;
  long *plStack_70;
  undefined8 *puStack_68;
  undefined8 uStack_60;
  undefined8 uStack_58;
  undefined8 uStack_50;
  undefined8 uStack_48;
  uint uStack_40;
  undefined8 uStack_38;
  
  uStack_90 = 0;
  uStack_88 = 0;
  uStack_60 = 0xffffffffffffffff;
  uStack_58 = 0;
  uStack_50 = 0;
  uStack_48 = 0;
  uStack_38 = 0;
  uStack_40 = (uint)(byte)((param_8 & 1) << 2);
  uStack_80 = param_2;
  uStack_78 = param_3;
  plStack_70 = param_4;
  puStack_68 = param_5;
  uVar2 = (**(code **)(*param_1 + 0x28))();
  if ((uVar2 & 1) == 0) {
    if (param_4 != (long *)0x0) {
      *param_4 = -0x3bc;
    }
    if (param_5 == (undefined8 *)0x0) {
      lVar3 = -0x3bc;
      goto code_r0x02339308;
    }
    puVar4 = (undefined8 *)*param_5;
    lVar3 = -0x3bc;
  }
  else {
    iVar1 = Aska::ResourceReadyQueue::PrepareForEvItem(Aska::ResourceReadyQueue::EvItem&, Aska::IMemoryManager*, Aska::ResourceReadyQueue::AllocationType)(param_1,&uStack_90,param_6,param_7);
    if (-1 < iVar1) {
      lVar3 = Aska::ResourceReadyQueue::Sequencer(Aska::ResourceReadyQueue::EvItem*)(param_1,&uStack_90);
      goto code_r0x02339308;
    }
    lVar3 = (long)iVar1;
    if (plStack_70 != (long *)0x0) {
      *plStack_70 = lVar3;
    }
    if (puStack_68 == (undefined8 *)0x0) goto code_r0x02339308;
    puVar4 = (undefined8 *)*puStack_68;
    param_5 = puStack_68;
  }
  (*(code *)*puVar4)(param_5,lVar3);
code_r0x02339308:
  Aska::ResourceReadyQueue::EvItem::~EvItem()(&uStack_90);
  return lVar3;
}

// ==== Aska::ResourceReadyQueue::PrepareForEvItem(Aska::ResourceReadyQueue::EvItem&, Aska::IMemoryManager*, Aska::ResourceReadyQueue::AllocationType)
// vaddr 0x2239328 | ghidra 0x2339328 | size 624 | symbol _ZN4Aska18ResourceReadyQueue16PrepareForEvItemERNS0_6EvItemEPNS_14IMemoryManagerENS0_14AllocationTypeE | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska18ResourceReadyQueue16PrepareForEvItemERNS0_6EvItemEPNS_14IMemoryManagerENS0_14AllocationTypeE
          (long param_1,long param_2,long param_3,int param_4)

{
  int *piVar1;
  char cVar2;
  bool bVar3;
  int iVar4;
  ulong uVar5;
  long *plVar6;
  long *plVar7;
  long *plVar8;
  int *piVar9;
  undefined8 uVar10;
  long *plVar11;
  
  plVar8 = *(long **)(param_2 + 0x10);
  if (((plVar8 == (long *)0x0) || (uVar5 = (**(code **)(*plVar8 + 0x10))(plVar8), (uVar5 & 1) == 0))
     || (*(long *)(param_2 + 0x18) == 0)) {
    return 0xfffffc44;
  }
  plVar8 = *(long **)(param_1 + 0xe0);
  piVar1 = *(int **)(param_1 + 0xe8);
  if (piVar1 != (int *)0x0) {
    do {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar3) {
        *piVar1 = *piVar1 + 1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
  }
  if (param_3 == 0) {
    if (plVar8 == (long *)0x0) {
      param_3 = *(long *)(param_1 + 0xf0);
      if (param_3 != 0) {
        plVar6 = *(long **)(param_2 + 0x38);
        if (plVar6 != (long *)0x0) {
          piVar9 = *(int **)(param_2 + 0x40);
          if (piVar9 != (int *)0x0) {
            do {
              iVar4 = *piVar9 + -1;
              cVar2 = '\x01';
              bVar3 = (bool)ExclusiveMonitorPass(piVar9,0x10);
              if (bVar3) {
                *piVar9 = iVar4;
                cVar2 = ExclusiveMonitorsStatus();
              }
            } while (cVar2 != '\0');
            goto code_r0x023393b0;
          }
          goto code_r0x023393bc;
        }
        goto code_r0x023393d8;
      }
      plVar6 = (long *)Aska::Global::GetAvailableMemoryManager()();
      plVar11 = (long *)(param_2 + 0x38);
      plVar7 = (long *)*plVar11;
      if (plVar7 == (long *)0x0) goto code_r0x02339508;
      piVar9 = *(int **)(param_2 + 0x40);
      if (piVar9 == (int *)0x0) {
code_r0x023394e8:
        (**(code **)(*plVar7 + 0xd0))(plVar7);
code_r0x023394f8:
        if (*(long *)(param_2 + 0x40) != 0) {
          Aska::TSharedPointerCode::DeleteCounter(int*)();
        }
      }
      else {
        do {
          iVar4 = *piVar9;
          cVar2 = '\x01';
          bVar3 = (bool)ExclusiveMonitorPass(piVar9,0x10);
          if (bVar3) {
            *piVar9 = iVar4 + -1;
            cVar2 = ExclusiveMonitorsStatus();
          }
        } while (cVar2 != '\0');
        if (iVar4 + -1 == 0) {
          plVar7 = (long *)*plVar11;
          if (plVar7 != (long *)0x0) goto code_r0x023394e8;
          goto code_r0x023394f8;
        }
      }
      *plVar11 = 0;
      *(undefined8 *)(param_2 + 0x40) = 0;
code_r0x02339508:
      *(long **)(param_2 + 0x48) = plVar6;
    }
    else {
      plVar7 = *(long **)(param_2 + 0x38);
      plVar6 = plVar8;
      if (plVar7 == plVar8) goto code_r0x02339508;
      piVar9 = *(int **)(param_2 + 0x40);
      if (piVar9 == (int *)0x0) {
code_r0x02339430:
        if (plVar7 != (long *)0x0) {
          (**(code **)(*plVar7 + 0xd0))();
        }
        if (*(long *)(param_2 + 0x40) != 0) {
          Aska::TSharedPointerCode::DeleteCounter(int*)();
        }
      }
      else {
        do {
          iVar4 = *piVar9;
          cVar2 = '\x01';
          bVar3 = (bool)ExclusiveMonitorPass(piVar9,0x10);
          if (bVar3) {
            *piVar9 = iVar4 + -1;
            cVar2 = ExclusiveMonitorsStatus();
          }
        } while (cVar2 != '\0');
        if (iVar4 + -1 == 0) {
          plVar7 = *(long **)(param_2 + 0x38);
          goto code_r0x02339430;
        }
      }
      *(long **)(param_2 + 0x38) = plVar8;
      *(int **)(param_2 + 0x40) = piVar1;
      if (piVar1 == (int *)0x0) goto code_r0x02339508;
      do {
        cVar2 = '\x01';
        bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
        if (bVar3) {
          *piVar1 = *piVar1 + 1;
          cVar2 = ExclusiveMonitorsStatus();
        }
      } while (cVar2 != '\0');
      *(long **)(param_2 + 0x48) = plVar8;
    }
    if (plVar6 == (long *)0x0) {
      uVar10 = 0xffffffff;
      goto joined_r0x0233954c;
    }
  }
  else {
    plVar6 = *(long **)(param_2 + 0x38);
    if (plVar6 != (long *)0x0) {
      piVar9 = *(int **)(param_2 + 0x40);
      if (piVar9 == (int *)0x0) {
code_r0x023393bc:
        (**(code **)(*plVar6 + 0xd0))();
code_r0x023393c8:
        if (*(long *)(param_2 + 0x40) != 0) {
          Aska::TSharedPointerCode::DeleteCounter(int*)();
        }
      }
      else {
        do {
          iVar4 = *piVar9 + -1;
          cVar2 = '\x01';
          bVar3 = (bool)ExclusiveMonitorPass(piVar9,0x10);
          if (bVar3) {
            *piVar9 = iVar4;
            cVar2 = ExclusiveMonitorsStatus();
          }
        } while (cVar2 != '\0');
code_r0x023393b0:
        if (iVar4 == 0) {
          plVar6 = *(long **)(param_2 + 0x38);
          if (plVar6 != (long *)0x0) goto code_r0x023393bc;
          goto code_r0x023393c8;
        }
      }
      *(undefined8 *)(param_2 + 0x38) = 0;
      *(undefined8 *)(param_2 + 0x40) = 0;
    }
code_r0x023393d8:
    *(long *)(param_2 + 0x48) = param_3;
  }
  if (param_4 - 1U < 2) {
    uVar10 = 0;
    *(byte *)(param_2 + 0x50) = *(byte *)(param_2 + 0x50) & 0xfc | (byte)param_4 & 3;
  }
  else if (param_4 == 0) {
    uVar10 = 0;
    *(byte *)(param_2 + 0x50) = *(byte *)(param_2 + 0x50) & 0xfc | *(byte *)(param_1 + 0xf8) & 3;
  }
  else {
    uVar10 = 0xfffffc42;
  }
joined_r0x0233954c:
  if (piVar1 != (int *)0x0) {
    do {
      iVar4 = *piVar1;
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar3) {
        *piVar1 = iVar4 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    if (iVar4 + -1 != 0) {
      return uVar10;
    }
  }
  if (plVar8 != (long *)0x0) {
    (**(code **)(*plVar8 + 0xd0))();
  }
  if (piVar1 != (int *)0x0) {
    Aska::TSharedPointerCode::DeleteCounter(int*)(piVar1);
  }
  return uVar10;
}

// ==== Aska::ResourceReadyQueue::Sequencer(Aska::ResourceReadyQueue::EvItem*)
// vaddr 0x2239598 | ghidra 0x2339598 | size 1740 | symbol _ZN4Aska18ResourceReadyQueue9SequencerEPNS0_6EvItemE | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska18ResourceReadyQueue9SequencerEPNS0_6EvItemE(long param_1,long param_2)

{
  long lVar1;
  int iVar2;
  long *plVar3;
  char cVar4;
  bool bVar5;
  ulong uVar6;
  long lVar7;
  long lVar8;
  undefined8 *puVar9;
  long *plVar10;
  ulong uVar11;
  long lVar12;
  long lVar13;
  ulong uVar14;
  ulong uVar15;
  undefined8 *puVar16;
  code *pcVar17;
  long lVar18;
  long lVar19;
  undefined8 uVar20;
  undefined *puVar21;
  undefined4 uVar22;
  long unaff_x28;
  undefined *puStack_158;
  long lStack_150;
  int *piStack_148;
  long lStack_140;
  int *piStack_138;
  undefined8 uStack_130;
  long lStack_108;
  uint uStack_fc;
  undefined1 auStack_f8 [152];
  
  lVar1 = param_1 + 0x220;
  Aska::CriticalSection::Enter() const(lVar1);
  lVar19 = *(long *)(param_1 + 400);
  if (lVar19 == 0) {
    lVar19 = param_1 + 0x19c;
    uVar22 = 0x80;
  }
  else {
    uVar22 = *(undefined4 *)(param_1 + 0x198);
  }
  plVar3 = *(long **)(param_2 + 0x10);
  uVar20 = *(undefined8 *)(param_2 + 0x30);
  lVar18 = param_1 + 0x100;
  uVar14 = **(ulong **)(param_2 + 0x18);
  if ((plVar3 == (long *)0x0) || (uVar6 = (**(code **)(*plVar3 + 0x10))(plVar3), (uVar6 & 1) == 0))
  {
    lVar7 = -0x3bc;
  }
  else {
    lVar7 = (**(code **)(*plVar3 + 0x18))(plVar3);
  }
  lVar8 = (**(code **)(*plVar3 + 0x18))(plVar3);
  lStack_108 = lVar8;
  if (lVar8 < 0) {
    if (*(long **)(param_2 + 0x20) != (long *)0x0) {
      **(long **)(param_2 + 0x20) = lVar8;
    }
    puVar9 = *(undefined8 **)(param_2 + 0x28);
    if (puVar9 != (undefined8 *)0x0) {
      puVar16 = (undefined8 *)*puVar9;
code_r0x02339778:
      (*(code *)*puVar16)(puVar9,lStack_108);
    }
code_r0x02339780:
    bVar5 = true;
    lVar8 = lStack_108;
  }
  else {
    uVar6 = (**(code **)(*plVar3 + 0x10))(plVar3);
    if ((uVar6 & 1) == 0) {
      param_1 = Aska::MappedResourceFilter::Filter(Aska::IStream*, Aska::IStream*, unsigned int*, unsigned long)(lVar18,plVar3,0,&uStack_fc,uVar20);
    }
    else {
      unaff_x28 = (**(code **)(*plVar3 + 0x18))(plVar3);
      param_1 = Aska::MappedResourceFilter::Filter(Aska::IStream*, Aska::IStream*, unsigned int*, unsigned long)(lVar18,plVar3,0,&uStack_fc,uVar20);
      if ((-1 < unaff_x28) && (uVar6 = (**(code **)(*plVar3 + 0x10))(plVar3), (uVar6 & 1) != 0)) {
        (**(code **)(*plVar3 + 0x20))(plVar3,unaff_x28,0);
      }
    }
    if (param_1 < 0) {
      if (*(long **)(param_2 + 0x20) != (long *)0x0) {
        **(long **)(param_2 + 0x20) = param_1;
      }
      puVar9 = *(undefined8 **)(param_2 + 0x28);
      lStack_108 = param_1;
      if (puVar9 != (undefined8 *)0x0) {
        puVar16 = (undefined8 *)*puVar9;
        lStack_108 = param_1;
        goto code_r0x02339778;
      }
      goto code_r0x02339780;
    }
    if (param_1 == 0) {
      lStack_108 = 0;
      if (*(undefined8 **)(param_2 + 0x20) != (undefined8 *)0x0) {
        **(undefined8 **)(param_2 + 0x20) = 0;
      }
      puVar9 = *(undefined8 **)(param_2 + 0x28);
      if (puVar9 != (undefined8 *)0x0) {
        (**(code **)*puVar9)(puVar9,0);
      }
      param_1 = 0;
code_r0x023397e4:
      bVar5 = true;
      lVar8 = lStack_108;
    }
    else {
      lStack_108 = param_1;
      lStack_108 = (**(code **)(*plVar3 + 0x20))(plVar3,0,2);
      if ((lStack_108 < 0) || (lStack_108 = (**(code **)(*plVar3 + 0x18))(plVar3), lStack_108 < 0))
      {
        if (*(long **)(param_2 + 0x20) != (long *)0x0) {
          **(long **)(param_2 + 0x20) = lStack_108;
        }
        puVar9 = *(undefined8 **)(param_2 + 0x28);
        if (puVar9 != (undefined8 *)0x0) {
          (**(code **)*puVar9)(puVar9,lStack_108);
        }
        goto code_r0x023397e4;
      }
      bVar5 = false;
      unaff_x28 = lStack_108 - lVar8;
    }
  }
  if ((-1 < lVar7) && (uVar6 = (**(code **)(*plVar3 + 0x10))(plVar3), (uVar6 & 1) != 0)) {
    (**(code **)(*plVar3 + 0x20))(plVar3,lVar7,0);
  }
  lVar7 = lVar8;
  if (bVar5) goto code_r0x02339c38;
  lVar7 = (**(code **)(*plVar3 + 0x18))(plVar3);
  lStack_108 = lVar7;
  if (lVar7 < 0) {
    if (*(long **)(param_2 + 0x20) != (long *)0x0) {
      **(long **)(param_2 + 0x20) = lVar7;
    }
    puVar9 = *(undefined8 **)(param_2 + 0x28);
    if (puVar9 == (undefined8 *)0x0) goto code_r0x02339c38;
    puVar16 = (undefined8 *)*puVar9;
  }
  else {
    if (uVar14 != 0) {
      uVar15 = (ulong)uStack_fc;
      uVar6 = 0;
      if (uVar15 != 0) {
        uVar6 = uVar14 / uVar15;
      }
      uVar11 = uVar14;
      if (uVar14 != uVar6 * uVar15) {
        lStack_108 = -0x3bd;
        if (*(undefined8 **)(param_2 + 0x20) != (undefined8 *)0x0) {
          **(undefined8 **)(param_2 + 0x20) = 0xfffffffffffffc43;
        }
        puVar9 = *(undefined8 **)(param_2 + 0x28);
        lVar7 = lStack_108;
        if (puVar9 == (undefined8 *)0x0) goto code_r0x02339c38;
        puVar16 = (undefined8 *)*puVar9;
        goto code_r0x02339a4c;
      }
code_r0x023398e0:
      puStack_158 = PTR__ZTVN4Aska12StaticStreamE_02cba478 + 0x10;
      uStack_130 = 0;
      piStack_148 = (int *)0x0;
      lStack_150 = 0;
      piStack_138 = (int *)0x0;
      lStack_140 = 0;
      Aska::StaticStream::Open(signed char const*, unsigned long)(&puStack_158,uVar11,param_1);
      uVar6 = (**(code **)(*plVar3 + 0x10))(plVar3);
      if ((uVar6 & 1) == 0) {
        lVar12 = -0x3bc;
      }
      else {
        lVar12 = (**(code **)(*plVar3 + 0x18))(plVar3);
      }
      uVar6 = (**(code **)(puStack_158 + 0x10))(&puStack_158);
      if ((uVar6 & 1) == 0) {
        lVar13 = -0x3bc;
        if (param_1 != unaff_x28 - lVar7) goto code_r0x02339974;
code_r0x023399b8:
        bVar5 = true;
        lVar19 = Aska::IStream::Transfer(Aska::IStream*, Aska::IStream*, unsigned long, unsigned long, void*, unsigned long, long*)(plVar3,&puStack_158,1,param_1,lVar19,uVar22,&lStack_108);
        puVar21 = PTR__ZTVN4Aska12StaticStreamE_02cba478;
        if (lVar19 != param_1) {
          if (uVar14 == 0) {
            Aska::IMemoryManager::Free(void const*)(uVar11);
          }
          if (*(long **)(param_2 + 0x20) != (long *)0x0) {
            **(long **)(param_2 + 0x20) = lStack_108;
          }
          if (*(undefined8 **)(param_2 + 0x28) != (undefined8 *)0x0) {
            (**(code **)**(undefined8 **)(param_2 + 0x28))();
          }
code_r0x02339a9c:
          bVar5 = false;
          lVar8 = lStack_108;
        }
      }
      else {
        lVar13 = (**(code **)(puStack_158 + 0x18))(&puStack_158);
        if (param_1 == unaff_x28 - lVar7) goto code_r0x023399b8;
code_r0x02339974:
        lStack_108 = Aska::MappedResourceFilter::Filter(Aska::IStream*, Aska::IStream*, unsigned int*, unsigned long)(lVar18,plVar3,&puStack_158,0,uVar20);
        puVar21 = PTR__ZTVN4Aska12StaticStreamE_02cba478;
        if (lStack_108 < 0) {
          if (uVar14 == 0) {
            Aska::IMemoryManager::Free(void const*)(uVar11);
          }
          if (*(long **)(param_2 + 0x20) != (long *)0x0) {
            **(long **)(param_2 + 0x20) = lStack_108;
          }
          puVar9 = *(undefined8 **)(param_2 + 0x28);
          if (puVar9 != (undefined8 *)0x0) {
            (**(code **)*puVar9)(puVar9,lStack_108);
          }
          goto code_r0x02339a9c;
        }
        bVar5 = true;
      }
      if ((-1 < lVar13) &&
         (uVar6 = (**(code **)(puStack_158 + 0x10))(&puStack_158), (uVar6 & 1) != 0)) {
        (**(code **)(puStack_158 + 0x20))(&puStack_158,lVar13,0);
      }
      if ((-1 < lVar12) && (uVar6 = (**(code **)(*plVar3 + 0x10))(plVar3), (uVar6 & 1) != 0)) {
        (**(code **)(*plVar3 + 0x20))(plVar3,lVar12,0);
      }
      if (bVar5) {
        lVar18 = *(long *)PTR__ZN4Aska6Global22m_pMappedMemoryManagerE_02cc0368;
        memset(auStack_f8,0,0x98);
        lVar19 = lVar18 + 8;
        Aska::CriticalSection::Enter() const(lVar19);
        uVar6 = Aska::MappedMemoryManager::RegisterMappingEx(void*, Aska::AFF::AskaFile*, void const**)(lVar18,uVar11,uVar11,auStack_f8);
        Aska::CriticalSection::Leave() const(lVar19);
        if ((uVar6 & 1) == 0) {
          lStack_108 = -1;
          if (uVar14 == 0) {
            Aska::IMemoryManager::Free(void const*)(uVar11);
          }
          if (*(long **)(param_2 + 0x20) != (long *)0x0) {
            **(long **)(param_2 + 0x20) = lStack_108;
          }
          puVar9 = *(undefined8 **)(param_2 + 0x28);
          lVar8 = lStack_108;
          if (puVar9 != (undefined8 *)0x0) {
            puVar16 = (undefined8 *)*puVar9;
            param_1 = lStack_108;
            goto code_r0x02339bb4;
          }
        }
        else {
          **(ulong **)(param_2 + 0x18) = uVar11;
          if (*(long **)(param_2 + 0x20) != (long *)0x0) {
            **(long **)(param_2 + 0x20) = param_1;
          }
          puVar9 = *(undefined8 **)(param_2 + 0x28);
          lVar8 = lStack_108;
          if (puVar9 != (undefined8 *)0x0) {
            puVar16 = (undefined8 *)*puVar9;
code_r0x02339bb4:
            (*(code *)*puVar16)(puVar9,param_1);
            lVar8 = lStack_108;
          }
        }
      }
      puStack_158 = puVar21 + 0x10;
      if (piStack_138 == (int *)0x0) {
code_r0x02339be4:
        if (lStack_140 != 0) {
          operator delete[](void*)();
        }
        if (piStack_138 != (int *)0x0) {
          Aska::TSharedPointerCode::DeleteCounter(int*)();
        }
      }
      else {
        do {
          iVar2 = *piStack_138;
          cVar4 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(piStack_138,0x10);
          if (bVar5) {
            *piStack_138 = iVar2 + -1;
            cVar4 = ExclusiveMonitorsStatus();
          }
        } while (cVar4 != '\0');
        if (iVar2 + -1 == 0) goto code_r0x02339be4;
      }
      lStack_140 = 0;
      piStack_138 = (int *)0x0;
      if (piStack_148 == (int *)0x0) {
code_r0x02339c1c:
        if (lStack_150 != 0) {
          operator delete[](void*)();
        }
        if (piStack_148 != (int *)0x0) {
          Aska::TSharedPointerCode::DeleteCounter(int*)();
        }
      }
      else {
        do {
          iVar2 = *piStack_148;
          cVar4 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(piStack_148,0x10);
          if (bVar5) {
            *piStack_148 = iVar2 + -1;
            cVar4 = ExclusiveMonitorsStatus();
          }
        } while (cVar4 != '\0');
        if (iVar2 + -1 == 0) goto code_r0x02339c1c;
      }
      lStack_150 = 0;
      lVar7 = lVar8;
      goto code_r0x02339c38;
    }
    plVar10 = *(long **)(param_2 + 0x48);
    if ((*(byte *)(param_2 + 0x50) >> 1 & 1) == 0) {
      pcVar17 = *(code **)(*plVar10 + 0x10);
code_r0x023398d0:
      uVar11 = (*pcVar17)(plVar10,param_1,uStack_fc);
      if (uVar11 != 0) goto code_r0x023398e0;
    }
    else if ((*(byte *)(param_2 + 0x50) & 3) == 2) {
      pcVar17 = *(code **)(*plVar10 + 0x18);
      goto code_r0x023398d0;
    }
    lStack_108 = -0x3bf;
    if (*(undefined8 **)(param_2 + 0x20) != (undefined8 *)0x0) {
      **(undefined8 **)(param_2 + 0x20) = 0xfffffffffffffc41;
    }
    puVar9 = *(undefined8 **)(param_2 + 0x28);
    lVar7 = lStack_108;
    if (puVar9 == (undefined8 *)0x0) goto code_r0x02339c38;
    puVar16 = (undefined8 *)*puVar9;
  }
code_r0x02339a4c:
  (*(code *)*puVar16)(puVar9,lStack_108);
  lVar7 = lStack_108;
code_r0x02339c38:
  Aska::CriticalSection::Leave() const(lVar1);
  return lVar7;
}

// ==== Aska::ResourceReadyQueue::EvItem::~EvItem()
// vaddr 0x2239c64 | ghidra 0x2339c64 | size 224 | symbol _ZN4Aska18ResourceReadyQueue6EvItemD2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18ResourceReadyQueue6EvItemD2Ev(long *param_1)

{
  int iVar1;
  char cVar2;
  bool bVar3;
  int iVar4;
  int *piVar5;
  long lVar6;
  
  lVar6 = param_1[0xb];
  if (lVar6 != 0) {
    Aska::CriticalSection::Enter() const(lVar6 + 0x68);
    iVar1 = *(int *)(lVar6 + 0x90);
    iVar4 = iVar1 + -1;
    *(int *)(lVar6 + 0x90) = iVar4;
    if (iVar4 == 0) {
      Aska::Event::Set() const(lVar6);
    }
    else if (iVar1 == 0) {
      Aska::Event::Reset() const(lVar6);
    }
    Aska::CriticalSection::Leave() const(lVar6 + 0x68);
    param_1[0xb] = 0;
  }
  piVar5 = (int *)param_1[8];
  if (piVar5 == (int *)0x0) {
code_r0x02339cd4:
    if ((long *)param_1[7] != (long *)0x0) {
      (**(code **)(*(long *)param_1[7] + 0xd0))();
    }
    if (param_1[8] != 0) {
      Aska::TSharedPointerCode::DeleteCounter(int*)();
    }
  }
  else {
    do {
      iVar1 = *piVar5;
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar5,0x10);
      if (bVar3) {
        *piVar5 = iVar1 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    if (iVar1 + -1 == 0) goto code_r0x02339cd4;
  }
  piVar5 = (int *)param_1[1];
  param_1[7] = 0;
  param_1[8] = 0;
  if (piVar5 != (int *)0x0) {
    do {
      iVar1 = *piVar5;
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar5,0x10);
      if (bVar3) {
        *piVar5 = iVar1 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    if (iVar1 + -1 != 0) goto code_r0x02339d34;
  }
  if ((long *)*param_1 != (long *)0x0) {
    (**(code **)(*(long *)*param_1 + 8))();
  }
  if (param_1[1] != 0) {
    Aska::TSharedPointerCode::DeleteCounter(int*)();
  }
code_r0x02339d34:
  *param_1 = 0;
  param_1[1] = 0;
  return;
}

// ==== Aska::ResourceReadyQueue::Add(Aska::IStream*, void**, long*, Aska::INotify*, int, Aska::IMemoryManager*, Aska::ResourceReadyQueue::AllocationType, bool)
// vaddr 0x2239d44 | ghidra 0x2339d44 | size 428 | symbol _ZN4Aska18ResourceReadyQueue3AddEPNS_7IStreamEPPvPlPNS_7INotifyEiPNS_14IMemoryManagerENS0_14AllocationTypeEb | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska18ResourceReadyQueue3AddEPNS_7IStreamEPPvPlPNS_7INotifyEiPNS_14IMemoryManagerENS0_14AllocationTypeEb
          (long *param_1,undefined8 param_2,undefined8 param_3,long *param_4,undefined8 *param_5,
          int param_6,undefined8 param_7,undefined4 param_8,byte param_9)

{
  long *plVar1;
  int iVar2;
  undefined4 uVar3;
  ulong uVar4;
  undefined8 *puVar5;
  undefined8 uVar6;
  long lVar7;
  undefined8 uStack_b8;
  undefined8 uStack_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined8 uStack_98;
  long *plStack_90;
  undefined8 *puStack_88;
  undefined8 uStack_80;
  undefined8 uStack_78;
  undefined8 uStack_70;
  undefined8 uStack_68;
  undefined4 uStack_60;
  long *plStack_58;
  
  plVar1 = param_1 + 3;
  uStack_b0 = 0;
  uStack_a8 = 0;
  uStack_80 = 0xffffffffffffffff;
  uStack_78 = 0;
  uStack_70 = 0;
  uStack_68 = 0;
  uStack_60 = 0;
  uStack_a0 = param_2;
  uStack_98 = param_3;
  plStack_90 = param_4;
  puStack_88 = param_5;
  plStack_58 = plVar1;
  Aska::CriticalSection::Enter() const(param_1 + 0x10);
  lVar7 = param_1[0x15];
  iVar2 = (int)lVar7 + 1;
  *(int *)(param_1 + 0x15) = iVar2;
  if (iVar2 == 0) {
    Aska::Event::Set() const(plVar1);
  }
  else if ((int)lVar7 == 0) {
    Aska::Event::Reset() const(plVar1);
  }
  Aska::CriticalSection::Leave() const(param_1 + 0x10);
  uStack_60 = CONCAT31(uStack_60._1_3_,(param_9 & 1) << 2);
  uVar4 = (**(code **)(*param_1 + 0x28))(param_1);
  if ((uVar4 & 1) == 0) {
    if (param_4 != (long *)0x0) {
      *param_4 = -0x3bc;
    }
    if (param_5 != (undefined8 *)0x0) {
      puVar5 = (undefined8 *)*param_5;
      lVar7 = -0x3bc;
      goto code_r0x02339ebc;
    }
  }
  else {
    iVar2 = Aska::ResourceReadyQueue::PrepareForEvItem(Aska::ResourceReadyQueue::EvItem&, Aska::IMemoryManager*, Aska::ResourceReadyQueue::AllocationType)(param_1,&uStack_b0,param_7,param_8);
    if (iVar2 < 0) {
      lVar7 = (long)iVar2;
      if (plStack_90 != (long *)0x0) {
        *plStack_90 = lVar7;
      }
      if (puStack_88 != (undefined8 *)0x0) {
        puVar5 = (undefined8 *)*puStack_88;
        param_5 = puStack_88;
        goto code_r0x02339ebc;
      }
    }
    else {
      lVar7 = param_1[0x19];
      if (lVar7 != 0) {
        if (param_6 < 0) {
          Aska::Thread::GetCurrentID()();
          uVar3 = gettid();
          getpriority(0,uVar3);
          param_6 = Aska::Thread::ConvertToIndependentPriority(int)();
        }
        uVar4 = Aska::TEventQueue<Aska::ResourceReadyQueue::EvItem>::Set(Aska::ResourceReadyQueue::EvItem const*, unsigned long, unsigned long*, int)(lVar7,&uStack_b0,0xffffffffffffffff,&uStack_b8,param_6);
        uVar6 = uStack_b8;
        if ((uVar4 & 1) != 0) goto code_r0x02339ec8;
      }
      if (plStack_90 != (long *)0x0) {
        *plStack_90 = -1;
      }
      if (puStack_88 != (undefined8 *)0x0) {
        puVar5 = (undefined8 *)*puStack_88;
        lVar7 = -1;
        param_5 = puStack_88;
code_r0x02339ebc:
        (*(code *)*puVar5)(param_5,lVar7);
      }
    }
  }
  uVar6 = 0;
code_r0x02339ec8:
  Aska::ResourceReadyQueue::EvItem::~EvItem()(&uStack_b0);
  return uVar6;
}

// ==== Aska::ResourceReadyQueue::Add(Aska::TSharedPointer<Aska::IStream>&, void**, long*, Aska::INotify*, int, Aska::IMemoryManager*, Aska::ResourceReadyQueue::AllocationType, bool)
// vaddr 0x2239ef0 | ghidra 0x2339ef0 | size 456 | symbol _ZN4Aska18ResourceReadyQueue3AddERNS_14TSharedPointerINS_7IStreamEEEPPvPlPNS_7INotifyEiPNS_14IMemoryManagerENS0_14AllocationTypeEb | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska18ResourceReadyQueue3AddERNS_14TSharedPointerINS_7IStreamEEEPPvPlPNS_7INotifyEiPNS_14IMemoryManagerENS0_14AllocationTypeEb
          (long *param_1,undefined8 *param_2,undefined8 param_3,long *param_4,undefined8 *param_5,
          int param_6,undefined8 param_7,undefined4 param_8,byte param_9)

{
  long *plVar1;
  char cVar2;
  bool bVar3;
  int iVar4;
  undefined4 uVar5;
  ulong uVar6;
  undefined8 *puVar7;
  undefined8 uVar8;
  long lVar9;
  undefined8 uStack_b8;
  undefined8 uStack_b0;
  int *piStack_a8;
  undefined8 uStack_a0;
  undefined8 uStack_98;
  long *plStack_90;
  undefined8 *puStack_88;
  undefined8 uStack_80;
  undefined8 uStack_78;
  undefined8 uStack_70;
  undefined8 uStack_68;
  undefined4 uStack_60;
  long *plStack_58;
  
  uStack_b0 = *param_2;
  piStack_a8 = (int *)param_2[1];
  plVar1 = param_1 + 3;
  uStack_a0 = uStack_b0;
  if (piStack_a8 != (int *)0x0) {
    do {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piStack_a8,0x10);
      if (bVar3) {
        *piStack_a8 = *piStack_a8 + 1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    uStack_a0 = *param_2;
  }
  uStack_80 = 0xffffffffffffffff;
  uStack_78 = 0;
  uStack_70 = 0;
  uStack_68 = 0;
  uStack_60 = 0;
  uStack_98 = param_3;
  plStack_90 = param_4;
  puStack_88 = param_5;
  plStack_58 = plVar1;
  Aska::CriticalSection::Enter() const(param_1 + 0x10);
  lVar9 = param_1[0x15];
  iVar4 = (int)lVar9 + 1;
  *(int *)(param_1 + 0x15) = iVar4;
  if (iVar4 == 0) {
    Aska::Event::Set() const(plVar1);
  }
  else if ((int)lVar9 == 0) {
    Aska::Event::Reset() const(plVar1);
  }
  Aska::CriticalSection::Leave() const(param_1 + 0x10);
  uStack_60 = CONCAT31(uStack_60._1_3_,(param_9 & 1) << 2);
  uVar6 = (**(code **)(*param_1 + 0x28))(param_1);
  if ((uVar6 & 1) == 0) {
    if (param_4 != (long *)0x0) {
      *param_4 = -0x3bc;
    }
    if (param_5 != (undefined8 *)0x0) {
      puVar7 = (undefined8 *)*param_5;
      lVar9 = -0x3bc;
      goto code_r0x0233a084;
    }
  }
  else {
    iVar4 = Aska::ResourceReadyQueue::PrepareForEvItem(Aska::ResourceReadyQueue::EvItem&, Aska::IMemoryManager*, Aska::ResourceReadyQueue::AllocationType)(param_1,&uStack_b0,param_7,param_8);
    if (iVar4 < 0) {
      lVar9 = (long)iVar4;
      if (plStack_90 != (long *)0x0) {
        *plStack_90 = lVar9;
      }
      if (puStack_88 != (undefined8 *)0x0) {
        puVar7 = (undefined8 *)*puStack_88;
        param_5 = puStack_88;
        goto code_r0x0233a084;
      }
    }
    else {
      lVar9 = param_1[0x19];
      if (lVar9 != 0) {
        if (param_6 < 0) {
          Aska::Thread::GetCurrentID()();
          uVar5 = gettid();
          getpriority(0,uVar5);
          param_6 = Aska::Thread::ConvertToIndependentPriority(int)();
        }
        uVar6 = Aska::TEventQueue<Aska::ResourceReadyQueue::EvItem>::Set(Aska::ResourceReadyQueue::EvItem const*, unsigned long, unsigned long*, int)(lVar9,&uStack_b0,0xffffffffffffffff,&uStack_b8,param_6);
        uVar8 = uStack_b8;
        if ((uVar6 & 1) != 0) goto code_r0x0233a090;
      }
      if (plStack_90 != (long *)0x0) {
        *plStack_90 = -1;
      }
      if (puStack_88 != (undefined8 *)0x0) {
        puVar7 = (undefined8 *)*puStack_88;
        lVar9 = -1;
        param_5 = puStack_88;
code_r0x0233a084:
        (*(code *)*puVar7)(param_5,lVar9);
      }
    }
  }
  uVar8 = 0;
code_r0x0233a090:
  Aska::ResourceReadyQueue::EvItem::~EvItem()(&uStack_b0);
  return uVar8;
}

// ==== Aska::ResourceReadyQueue::Cancel(unsigned long)
// vaddr 0x223a0b8 | ghidra 0x233a0b8 | size 236 | symbol _ZN4Aska18ResourceReadyQueue6CancelEm | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska18ResourceReadyQueue6CancelEm(long *param_1,long param_2)

{
  ulong uVar1;
  long lVar2;
  undefined8 uVar3;
  long lVar4;
  undefined8 uStack_80;
  undefined8 uStack_78;
  undefined8 uStack_70;
  undefined8 uStack_68;
  undefined8 *puStack_60;
  undefined8 *puStack_58;
  undefined8 uStack_50;
  undefined8 uStack_48;
  undefined8 uStack_40;
  undefined8 uStack_38;
  undefined4 uStack_30;
  undefined8 uStack_28;
  
  uVar1 = (**(code **)(*param_1 + 0x28))();
  if ((uVar1 & 1) == 0) {
code_r0x0233a188:
    uVar3 = 0;
  }
  else {
    if (param_2 != 0) {
      uStack_68 = 0;
      uStack_70 = 0;
      puStack_58 = (undefined8 *)0x0;
      puStack_60 = (undefined8 *)0x0;
      uStack_78 = 0;
      uStack_80 = 0;
      uStack_50 = 0xffffffffffffffff;
      uStack_28 = 0;
      uStack_30 = 0;
      uStack_38 = 0;
      uStack_40 = 0;
      uStack_48 = 0;
      lVar4 = param_1[0x19];
      if ((((lVar4 == 0) || (lVar2 = *(long *)(lVar4 + 8), lVar2 == 0)) ||
          ((*(char *)(lVar2 + 0x119) == '\0' && ((*(uint *)(lVar2 + 0xf0) & 0x3fffffff) == 0)))) ||
         ((*(long *)(lVar4 + 0x10) == 0 ||
          (uVar1 = Aska::TPriorityQueue<Aska::ResourceReadyQueue::EvItem, true>::Remove(unsigned long, Aska::ResourceReadyQueue::EvItem*)(lVar2,param_2,&uStack_80), (uVar1 & 1) == 0)))) {
        lVar4 = param_1[0x49];
        Aska::ResourceReadyQueue::EvItem::~EvItem()(&uStack_80);
        if (lVar4 == param_2) goto code_r0x0233a188;
      }
      else {
        if (puStack_60 != (undefined8 *)0x0) {
          *puStack_60 = 0xfffffffffffffc0f;
        }
        if (puStack_58 != (undefined8 *)0x0) {
          (**(code **)*puStack_58)(puStack_58,0xfffffffffffffc0f);
        }
        Aska::ResourceReadyQueue::EvItem::~EvItem()(&uStack_80);
      }
    }
    uVar3 = 1;
  }
  return uVar3;
}

// ==== Aska::ResourceReadyQueue::Flush()
// vaddr 0x223a1a4 | ghidra 0x233a1a4 | size 112 | symbol _ZN4Aska18ResourceReadyQueue5FlushEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZN4Aska18ResourceReadyQueue5FlushEv(long *param_1)

{
  ulong uVar1;
  undefined4 uVar2;
  
  uVar1 = (**(code **)(*param_1 + 0x28))();
  if ((uVar1 & 1) == 0) {
    uVar2 = 0xfffffc44;
  }
  else {
    Aska::Event::Wait(unsigned int) const(param_1 + 3,0);
    uVar1 = (**(code **)(*param_1 + 0x28))(param_1);
    uVar2 = 0;
    if ((uVar1 & 1) != 0) {
      uVar1 = Aska::Event::IsSignal() const(param_1 + 3);
      uVar2 = 0;
      if ((uVar1 & 1) == 0) {
        uVar2 = 0xfffffc3a;
      }
    }
  }
  return uVar2;
}

// ==== Aska::ResourceReadyQueue::Handler()
// vaddr 0x223a214 | ghidra 0x233a214 | size 248 | symbol _ZN4Aska18ResourceReadyQueue7HandlerEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18ResourceReadyQueue7HandlerEv(long param_1)

{
  long lVar1;
  ulong uVar2;
  undefined8 uVar3;
  long lVar4;
  undefined8 uStack_98;
  undefined8 uStack_90;
  undefined8 uStack_88;
  undefined8 uStack_80;
  undefined8 uStack_78;
  undefined8 uStack_70;
  undefined8 uStack_68;
  undefined8 uStack_60;
  undefined8 uStack_58;
  undefined8 uStack_50;
  undefined4 uStack_48;
  undefined8 uStack_40;
  undefined8 uStack_38;
  
  while( true ) {
    uStack_70 = 0;
    uStack_78 = 0;
    uStack_80 = 0;
    uStack_88 = 0;
    uStack_90 = 0;
    uStack_98 = 0;
    uStack_68 = 0xffffffffffffffff;
    uStack_40 = 0;
    uStack_48 = 0;
    uStack_50 = 0;
    uStack_58 = 0;
    uStack_60 = 0;
    *(undefined8 *)(param_1 + 0x248) = 0;
    lVar4 = *(long *)(param_1 + 0xd0);
    lVar1 = *(long *)(lVar4 + 8);
    if ((lVar1 == 0) ||
       ((*(char *)(lVar1 + 0x119) == '\0' && ((*(uint *)(lVar1 + 0xf0) & 0x3fffffff) == 0)))) {
      uVar3 = 0;
    }
    else {
      uVar3 = 0;
      if ((*(long *)(lVar4 + 0x10) != 0) &&
         (uVar2 = Aska::TPriorityQueue<Aska::ResourceReadyQueue::EvItem, true>::Acquire(Aska::ResourceReadyQueue::EvItem*, unsigned long, unsigned long*)(lVar1,&uStack_98,0xffffffffffffffff,&uStack_38), uVar3 = uStack_38
         , (uVar2 & 1) == 0)) {
        do {
          Aska::Event::Wait(unsigned int) const(lVar4 + 0x10,0);
          uVar2 = Aska::TPriorityQueue<Aska::ResourceReadyQueue::EvItem, true>::Acquire(Aska::ResourceReadyQueue::EvItem*, unsigned long, unsigned long*)(*(undefined8 *)(lVar4 + 8),&uStack_98,0xffffffffffffffff,
                                  &uStack_38);
          uVar3 = uStack_38;
        } while ((uVar2 & 1) == 0);
      }
    }
    *(undefined8 *)(param_1 + 0x248) = uVar3;
    if (*(char *)(param_1 + 0x12) != '\0') break;
    Aska::ResourceReadyQueue::Sequencer(Aska::ResourceReadyQueue::EvItem*)(param_1,&uStack_98);
    Aska::ResourceReadyQueue::EvItem::~EvItem()(&uStack_98);
  }
  Aska::ResourceReadyQueue::EvItem::~EvItem()(&uStack_98);
  return;
}

// ==== Aska::ResourceReadyQueue::IsReady() const
// vaddr 0x223a30c | ghidra 0x233a30c | size 32 | symbol _ZNK4Aska18ResourceReadyQueue7IsReadyEv | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK4Aska18ResourceReadyQueue7IsReadyEv(long param_1)

{
  if (*(char *)(param_1 + 0x11) != '\0') {
    return *(char *)(param_1 + 0x12) == '\0';
  }
  return false;
}

// ==== Aska::TEventPort<Aska::ResourceReadyQueue::EvItem>::~TEventPort()
// vaddr 0x223a32c | ghidra 0x233a32c | size 196 | symbol _ZN4Aska10TEventPortINS_18ResourceReadyQueue6EvItemEED0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10TEventPortINS_18ResourceReadyQueue6EvItemEED0Ev(long *param_1)

{
  int iVar1;
  char cVar2;
  bool bVar3;
  long *plVar4;
  long lVar5;
  int *piVar6;
  long *plVar7;
  
  *param_1 = (long)(PTR__ZTVN4Aska10TEventPortINS_18ResourceReadyQueue6EvItemEEE_02cbacd0 + 0x10);
  plVar7 = param_1 + 1;
  plVar4 = (long *)*plVar7;
  piVar6 = (int *)param_1[2];
  if (plVar4 == (long *)0x0) {
    param_1[3] = 0;
    if (piVar6 == (int *)0x0) goto code_r0x011d8ed0;
    do {
      iVar1 = *piVar6;
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar6,0x10);
      if (bVar3) {
        *piVar6 = iVar1 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    if (iVar1 + -1 != 0) goto code_r0x011d8ed0;
    if ((long *)*plVar7 == (long *)0x0) goto code_r0x0233a398;
    (**(code **)(*(long *)*plVar7 + 8))();
    lVar5 = param_1[2];
  }
  else {
    if (piVar6 == (int *)0x0) {
code_r0x0233a378:
      (**(code **)(*plVar4 + 8))();
code_r0x0233a384:
      if (param_1[2] != 0) {
        Aska::TSharedPointerCode::DeleteCounter(int*)();
      }
    }
    else {
      do {
        iVar1 = *piVar6;
        cVar2 = '\x01';
        bVar3 = (bool)ExclusiveMonitorPass(piVar6,0x10);
        if (bVar3) {
          *piVar6 = iVar1 + -1;
          cVar2 = ExclusiveMonitorsStatus();
        }
      } while (cVar2 != '\0');
      if (iVar1 + -1 == 0) {
        plVar4 = (long *)*plVar7;
        if (plVar4 != (long *)0x0) goto code_r0x0233a378;
        goto code_r0x0233a384;
      }
    }
    param_1[2] = 0;
    param_1[3] = 0;
    *plVar7 = 0;
code_r0x0233a398:
    lVar5 = param_1[2];
  }
  if (lVar5 != 0) {
    Aska::TSharedPointerCode::DeleteCounter(int*)();
  }
code_r0x011d8ed0:
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::TEventQueue<Aska::ResourceReadyQueue::EvItem>::~TEventQueue()
// vaddr 0x223a3f0 | ghidra 0x233a3f0 | size 80 | symbol _ZN4Aska11TEventQueueINS_18ResourceReadyQueue6EvItemEED2Ev | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Possible PIC construction at 0x0233a414: Changing call to branch */
/* WARNING: Removing unreachable block (ram,0x0233a418) */
/* WARNING: Removing unreachable block (ram,0x0233a420) */
/* WARNING: Removing unreachable block (ram,0x0233a430) */

void _ZN4Aska11TEventQueueINS_18ResourceReadyQueue6EvItemEED2Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska11TEventQueueINS_18ResourceReadyQueue6EvItemEEE_02cbe178 + 0x10);
  (*(code *)PTR__ZN4Aska5Event4ExitEv_02ca1548)(param_1 + 2);
  return;
}

// ==== Aska::TEventQueue<Aska::ResourceReadyQueue::EvItem>::~TEventQueue()
// vaddr 0x223a440 | ghidra 0x233a440 | size 88 | symbol _ZN4Aska11TEventQueueINS_18ResourceReadyQueue6EvItemEED0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11TEventQueueINS_18ResourceReadyQueue6EvItemEED0Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska11TEventQueueINS_18ResourceReadyQueue6EvItemEEE_02cbe178 + 0x10);
  Aska::Event::Exit()(param_1 + 2);
  if ((long *)param_1[1] != (long *)0x0) {
    (**(code **)(*(long *)param_1[1] + 8))();
    param_1[1] = 0;
  }
  Aska::Event::Exit()(param_1 + 2);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::TPoolLegacy<Aska::TEventElement<Aska::ResourceReadyQueue::EvItem>, false>::SecurePool(unsigned int, bool, void const*, unsigned int const*)
// vaddr 0x223a498 | ghidra 0x233a498 | size 328 | symbol _ZN4Aska11TPoolLegacyINS_13TEventElementINS_18ResourceReadyQueue6EvItemEEELb0EE10SecurePoolEjbPKvPKj | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska11TPoolLegacyINS_13TEventElementINS_18ResourceReadyQueue6EvItemEEELb0EE10SecurePoolEjbPKvPKj
          (long param_1,uint param_2,ulong param_3,long param_4,undefined8 param_5)

{
  long lVar1;
  ulong uVar2;
  undefined8 uVar3;
  long lVar4;
  long *plVar5;
  
  plVar5 = (long *)(param_1 + 0x20);
  if ((*plVar5 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 0x30) = 0;
  }
  *plVar5 = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  *(undefined8 *)(param_1 + 0x38) = 0;
  if (*(long *)(param_1 + 0x40) != 0) {
    if (*(char *)(param_1 + 0x48) != '\0') {
      operator delete[](void*)();
    }
    *(undefined8 *)(param_1 + 0x40) = 0;
  }
  if (param_2 == 0) {
code_r0x0233a584:
    uVar3 = 1;
  }
  else {
    if (param_4 == 0) {
      lVar1 = operator new[](unsigned long, unsigned long, bool)(param_2 * 0x88,8,1);
      *(undefined1 *)(param_1 + 0x48) = 1;
      *(long *)(param_1 + 0x40) = lVar1;
      lVar4 = 0;
      if (lVar1 != 0) goto code_r0x0233a53c;
    }
    else {
      *(undefined1 *)(param_1 + 0x48) = 0;
      *(long *)(param_1 + 0x40) = param_4;
code_r0x0233a53c:
      uVar2 = Aska::TBitArray<unsigned int, false>::Alloc(unsigned int, unsigned int const*)(param_1 + 0x10,param_2,param_5);
      if ((uVar2 & 1) != 0) {
        if ((param_3 & 1) != 0) {
          memset(*(undefined8 *)(param_1 + 0x40),0,(ulong)param_2 * 0x88);
        }
        *(undefined8 *)(param_1 + 0x38) = 0;
        if (*(int *)(param_1 + 0x28) != 0) {
          memset(*plVar5,0,*(int *)(param_1 + 0x28) << 2);
        }
        goto code_r0x0233a584;
      }
      lVar4 = *(long *)(param_1 + 0x40);
    }
    if (lVar4 != 0) {
      if (*(char *)(param_1 + 0x48) != '\0') {
        operator delete[](void*)();
      }
      *(undefined8 *)(param_1 + 0x40) = 0;
    }
    *(char *)(param_1 + 0x48) = '\0';
    if ((*plVar5 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
      operator delete[](void*)();
      *(undefined1 *)(param_1 + 0x30) = 0;
    }
    uVar3 = 0;
    *plVar5 = 0;
    *(undefined8 *)(param_1 + 0x28) = 0;
  }
  return uVar3;
}

// ==== Aska::TPriorityQueue<Aska::ResourceReadyQueue::EvItem, true>::~TPriorityQueue()
// vaddr 0x223a5e0 | ghidra 0x233a5e0 | size 292 | symbol _ZN4Aska14TPriorityQueueINS_18ResourceReadyQueue6EvItemELb1EED2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska14TPriorityQueueINS_18ResourceReadyQueue6EvItemELb1EED2Ev(long *param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  undefined *puVar3;
  long *plVar4;
  
  *param_1 = (long)(PTR__ZTVN4Aska14TPriorityQueueINS_18ResourceReadyQueue6EvItemELb1EEE_02cc15c0 +
                   0x10);
  Aska::TPriorityQueue<Aska::ResourceReadyQueue::EvItem, true>::ClearQueue()();
  plVar4 = param_1 + 0x1d;
  param_1[0x19] =
       (long)(
             PTR__ZTVN4Aska11TPoolLegacyINS_13TEventElementINS_18ResourceReadyQueue6EvItemEEELb0EEE_02cc0c38
             + 0x10);
  if ((*plVar4 != 0) && ((char)param_1[0x1f] != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 0x1f) = 0;
  }
  *plVar4 = 0;
  param_1[0x1e] = 0;
  param_1[0x20] = 0;
  if (param_1[0x21] == 0) {
    param_1[0x1b] = (long)(PTR__ZTVN4Aska9TBitArrayIjLb0EEE_02cba038 + 0x10);
  }
  else if ((char)param_1[0x22] == '\0') {
    param_1[0x1b] = (long)(PTR__ZTVN4Aska9TBitArrayIjLb0EEE_02cba038 + 0x10);
    param_1[0x21] = 0;
  }
  else {
    operator delete[](void*)();
    param_1[0x1b] = (long)(PTR__ZTVN4Aska9TBitArrayIjLb0EEE_02cba038 + 0x10);
    param_1[0x21] = 0;
    if ((param_1[0x1d] != 0) && ((char)param_1[0x1f] != '\0')) {
      operator delete[](void*)();
      *(undefined1 *)(param_1 + 0x1f) = 0;
    }
  }
  *plVar4 = 0;
  param_1[0x1e] = 0;
  puVar1 = PTR__ZTVN4Aska13TSmartPointerILb0EEE_02cc2320 + 0x10;
  puVar2 = PTR__ZTVN4Aska5TListINS_13TEventElementINS_18ResourceReadyQueue6EvItemEEEEE_02cc1958 +
           0x10;
  puVar3 = PTR__ZTVN4Aska13TEventElementINS_18ResourceReadyQueue6EvItemEEE_02cb97c0 + 0x10;
  param_1[0x1b] = (long)puVar1;
  param_1[0x19] = (long)puVar1;
  *(undefined1 *)(param_1 + 0xb) = 0;
  param_1[7] = (long)puVar3;
  param_1[6] = (long)puVar2;
  Aska::ResourceReadyQueue::EvItem::~EvItem()(param_1 + 0xc);
  (*(code *)PTR__ZN4Aska15CriticalSectionD2Ev_02caae08)(param_1 + 1);
  return;
}

// ==== Aska::TPriorityQueue<Aska::ResourceReadyQueue::EvItem, true>::~TPriorityQueue()
// vaddr 0x223a704 | ghidra 0x233a704 | size 24 | symbol _ZN4Aska14TPriorityQueueINS_18ResourceReadyQueue6EvItemELb1EED0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska14TPriorityQueueINS_18ResourceReadyQueue6EvItemELb1EED0Ev(undefined8 param_1)

{
  Aska::TPriorityQueue<Aska::ResourceReadyQueue::EvItem, true>::~TPriorityQueue()();
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::TList<Aska::TEventElement<Aska::ResourceReadyQueue::EvItem> >::~TList()
// vaddr 0x223a71c | ghidra 0x233a71c | size 52 | symbol _ZN4Aska5TListINS_13TEventElementINS_18ResourceReadyQueue6EvItemEEEED2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5TListINS_13TEventElementINS_18ResourceReadyQueue6EvItemEEEED2Ev(long *param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZTVN4Aska5TListINS_13TEventElementINS_18ResourceReadyQueue6EvItemEEEEE_02cc1958 +
           0x10;
  param_1[1] = (long)(PTR__ZTVN4Aska13TEventElementINS_18ResourceReadyQueue6EvItemEEE_02cb97c0 +
                     0x10);
  *param_1 = (long)puVar1;
  *(undefined1 *)(param_1 + 5) = 0;
  (*(code *)PTR__ZN4Aska18ResourceReadyQueue6EvItemD2Ev_02cb55b8)(param_1 + 6);
  return;
}

// ==== Aska::TList<Aska::TEventElement<Aska::ResourceReadyQueue::EvItem> >::~TList()
// vaddr 0x223a750 | ghidra 0x233a750 | size 68 | symbol _ZN4Aska5TListINS_13TEventElementINS_18ResourceReadyQueue6EvItemEEEED0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5TListINS_13TEventElementINS_18ResourceReadyQueue6EvItemEEEED0Ev(long *param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  
  puVar1 = PTR__ZTVN4Aska5TListINS_13TEventElementINS_18ResourceReadyQueue6EvItemEEEEE_02cc1958 +
           0x10;
  puVar2 = PTR__ZTVN4Aska13TEventElementINS_18ResourceReadyQueue6EvItemEEE_02cb97c0 + 0x10;
  *(undefined1 *)(param_1 + 5) = 0;
  param_1[1] = (long)puVar2;
  *param_1 = (long)puVar1;
  Aska::ResourceReadyQueue::EvItem::~EvItem()(param_1 + 6);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::TList<Aska::TEventElement<Aska::ResourceReadyQueue::EvItem> >::Add(Aska::TEventElement<Aska::ResourceReadyQueue::EvItem>*)
// vaddr 0x223a794 | ghidra 0x233a794 | size 36 | symbol _ZN4Aska5TListINS_13TEventElementINS_18ResourceReadyQueue6EvItemEEEE3AddEPS4_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5TListINS_13TEventElementINS_18ResourceReadyQueue6EvItemEEEE3AddEPS4_
               (long param_1,long param_2)

{
  long lVar1;
  
  lVar1 = *(long *)(param_1 + 0x10);
  *(long *)(param_2 + 8) = lVar1;
  *(long *)(param_2 + 0x10) = param_1 + 8;
  *(long *)(param_1 + 0x10) = param_2;
  *(long *)(lVar1 + 0x10) = param_2;
  *(int *)(param_1 + 0x90) = *(int *)(param_1 + 0x90) + 1;
  return;
}

// ==== Aska::TList<Aska::TEventElement<Aska::ResourceReadyQueue::EvItem> >::AddTop(Aska::TEventElement<Aska::ResourceReadyQueue::EvItem>*)
// vaddr 0x223a7b8 | ghidra 0x233a7b8 | size 36 | symbol _ZN4Aska5TListINS_13TEventElementINS_18ResourceReadyQueue6EvItemEEEE6AddTopEPS4_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5TListINS_13TEventElementINS_18ResourceReadyQueue6EvItemEEEE6AddTopEPS4_
               (long param_1,long param_2)

{
  long lVar1;
  
  lVar1 = *(long *)(param_1 + 0x18);
  *(long *)(param_2 + 8) = param_1 + 8;
  *(long *)(param_2 + 0x10) = lVar1;
  *(long *)(lVar1 + 8) = param_2;
  *(long *)(param_1 + 0x18) = param_2;
  *(int *)(param_1 + 0x90) = *(int *)(param_1 + 0x90) + 1;
  return;
}

// ==== Aska::TList<Aska::TEventElement<Aska::ResourceReadyQueue::EvItem> >::Insert(Aska::TEventElement<Aska::ResourceReadyQueue::EvItem>*, Aska::TEventElement<Aska::ResourceReadyQueue::EvItem>*)
// vaddr 0x223a7dc | ghidra 0x233a7dc | size 32 | symbol _ZN4Aska5TListINS_13TEventElementINS_18ResourceReadyQueue6EvItemEEEE6InsertEPS4_S6_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5TListINS_13TEventElementINS_18ResourceReadyQueue6EvItemEEEE6InsertEPS4_S6_
               (long param_1,long param_2,long param_3)

{
  long lVar1;
  
  lVar1 = *(long *)(param_2 + 0x10);
  *(long *)(param_3 + 8) = param_2;
  *(long *)(param_3 + 0x10) = lVar1;
  *(long *)(lVar1 + 8) = param_3;
  *(long *)(param_2 + 0x10) = param_3;
  *(int *)(param_1 + 0x90) = *(int *)(param_1 + 0x90) + 1;
  return;
}

// ==== Aska::TList<Aska::TEventElement<Aska::ResourceReadyQueue::EvItem> >::Delete(Aska::TEventElement<Aska::ResourceReadyQueue::EvItem>*)
// vaddr 0x223a7fc | ghidra 0x233a7fc | size 64 | symbol _ZN4Aska5TListINS_13TEventElementINS_18ResourceReadyQueue6EvItemEEEE6DeleteEPS4_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5TListINS_13TEventElementINS_18ResourceReadyQueue6EvItemEEEE6DeleteEPS4_
               (long param_1,long param_2)

{
  long lVar1;
  long lVar2;
  
  if ((param_1 + 8 != param_2) && (param_2 != 0)) {
    lVar1 = *(long *)(param_2 + 8);
    lVar2 = *(long *)(param_2 + 0x10);
    if (lVar1 != 0) {
      *(long *)(lVar1 + 0x10) = lVar2;
    }
    if (lVar2 != 0) {
      *(long *)(lVar2 + 8) = lVar1;
    }
    if (0 < *(int *)(param_1 + 0x90)) {
      *(int *)(param_1 + 0x90) = *(int *)(param_1 + 0x90) + -1;
    }
    *(long *)(param_2 + 8) = 0;
    *(undefined8 *)(param_2 + 0x10) = 0;
  }
  return;
}

// ==== Aska::TEventElement<Aska::ResourceReadyQueue::EvItem>::~TEventElement()
// vaddr 0x223a83c | ghidra 0x233a83c | size 32 | symbol _ZN4Aska13TEventElementINS_18ResourceReadyQueue6EvItemEED2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13TEventElementINS_18ResourceReadyQueue6EvItemEED2Ev(long *param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZTVN4Aska13TEventElementINS_18ResourceReadyQueue6EvItemEEE_02cb97c0;
  *(undefined1 *)(param_1 + 4) = 0;
  *param_1 = (long)(puVar1 + 0x10);
  (*(code *)PTR__ZN4Aska18ResourceReadyQueue6EvItemD2Ev_02cb55b8)(param_1 + 5);
  return;
}

// ==== Aska::TEventElement<Aska::ResourceReadyQueue::EvItem>::~TEventElement()
// vaddr 0x223a85c | ghidra 0x233a85c | size 48 | symbol _ZN4Aska13TEventElementINS_18ResourceReadyQueue6EvItemEED0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13TEventElementINS_18ResourceReadyQueue6EvItemEED0Ev(long *param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZTVN4Aska13TEventElementINS_18ResourceReadyQueue6EvItemEEE_02cb97c0;
  *(undefined1 *)(param_1 + 4) = 0;
  *param_1 = (long)(puVar1 + 0x10);
  Aska::ResourceReadyQueue::EvItem::~EvItem()(param_1 + 5);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::TPoolLegacy<Aska::TEventElement<Aska::ResourceReadyQueue::EvItem>, false>::~TPoolLegacy()
// vaddr 0x223a88c | ghidra 0x233a88c | size 220 | symbol _ZN4Aska11TPoolLegacyINS_13TEventElementINS_18ResourceReadyQueue6EvItemEEELb0EED2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11TPoolLegacyINS_13TEventElementINS_18ResourceReadyQueue6EvItemEEELb0EED2Ev
               (long *param_1)

{
  undefined *puVar1;
  long *plVar2;
  
  *param_1 = (long)(
                   PTR__ZTVN4Aska11TPoolLegacyINS_13TEventElementINS_18ResourceReadyQueue6EvItemEEELb0EEE_02cc0c38
                   + 0x10);
  plVar2 = param_1 + 4;
  if ((*plVar2 != 0) && ((char)param_1[6] != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 6) = 0;
  }
  *plVar2 = 0;
  param_1[5] = 0;
  param_1[7] = 0;
  if (param_1[8] == 0) {
    param_1[2] = (long)(PTR__ZTVN4Aska9TBitArrayIjLb0EEE_02cba038 + 0x10);
  }
  else if ((char)param_1[9] == '\0') {
    param_1[2] = (long)(PTR__ZTVN4Aska9TBitArrayIjLb0EEE_02cba038 + 0x10);
    param_1[8] = 0;
  }
  else {
    operator delete[](void*)();
    param_1[2] = (long)(PTR__ZTVN4Aska9TBitArrayIjLb0EEE_02cba038 + 0x10);
    param_1[8] = 0;
    if ((param_1[4] != 0) && ((char)param_1[6] != '\0')) {
      operator delete[](void*)();
      *(undefined1 *)(param_1 + 6) = 0;
    }
  }
  *plVar2 = 0;
  param_1[5] = 0;
  puVar1 = PTR__ZTVN4Aska13TSmartPointerILb0EEE_02cc2320 + 0x10;
  param_1[2] = (long)puVar1;
  *param_1 = (long)puVar1;
  return;
}

// ==== Aska::TPriorityQueue<Aska::ResourceReadyQueue::EvItem, true>::MyPool::~MyPool()
// vaddr 0x223a968 | ghidra 0x233a968 | size 220 | symbol _ZN4Aska14TPriorityQueueINS_18ResourceReadyQueue6EvItemELb1EE6MyPoolD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska14TPriorityQueueINS_18ResourceReadyQueue6EvItemELb1EE6MyPoolD0Ev(long *param_1)

{
  long *plVar1;
  
  *param_1 = (long)(
                   PTR__ZTVN4Aska11TPoolLegacyINS_13TEventElementINS_18ResourceReadyQueue6EvItemEEELb0EEE_02cc0c38
                   + 0x10);
  plVar1 = param_1 + 4;
  if ((*plVar1 != 0) && ((char)param_1[6] != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 6) = 0;
  }
  *plVar1 = 0;
  param_1[5] = 0;
  param_1[7] = 0;
  if (param_1[8] == 0) {
    param_1[2] = (long)(PTR__ZTVN4Aska9TBitArrayIjLb0EEE_02cba038 + 0x10);
  }
  else if ((char)param_1[9] == '\0') {
    param_1[2] = (long)(PTR__ZTVN4Aska9TBitArrayIjLb0EEE_02cba038 + 0x10);
    param_1[8] = 0;
  }
  else {
    operator delete[](void*)();
    param_1[2] = (long)(PTR__ZTVN4Aska9TBitArrayIjLb0EEE_02cba038 + 0x10);
    param_1[8] = 0;
    if ((param_1[4] != 0) && ((char)param_1[6] != '\0')) {
      operator delete[](void*)();
      *(undefined1 *)(param_1 + 6) = 0;
    }
  }
  *plVar1 = 0;
  param_1[5] = 0;
  param_1[2] = (long)(PTR__ZTVN4Aska13TSmartPointerILb0EEE_02cc2320 + 0x10);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::TPriorityQueue<Aska::ResourceReadyQueue::EvItem, true>::MyPool::DirtyElement(Aska::TEventElement<Aska::ResourceReadyQueue::EvItem>*)
// vaddr 0x223aa44 | ghidra 0x233aa44 | size 48 | symbol _ZN4Aska14TPriorityQueueINS_18ResourceReadyQueue6EvItemELb1EE6MyPool12DirtyElementEPNS_13TEventElementIS2_EE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska14TPriorityQueueINS_18ResourceReadyQueue6EvItemELb1EE6MyPool12DirtyElementEPNS_13TEventElementIS2_EE
               (undefined8 param_1,long param_2)

{
  undefined1 uVar1;
  
  uVar1 = *(undefined1 *)(param_2 + 0x20);
  memset(param_2,0xcd,0x88);
  *(undefined1 *)(param_2 + 0x20) = uVar1;
  return;
}

// ==== Aska::TPoolLegacy<Aska::TEventElement<Aska::ResourceReadyQueue::EvItem>, false>::~TPoolLegacy()
// vaddr 0x223aa74 | ghidra 0x233aa74 | size 220 | symbol _ZN4Aska11TPoolLegacyINS_13TEventElementINS_18ResourceReadyQueue6EvItemEEELb0EED0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11TPoolLegacyINS_13TEventElementINS_18ResourceReadyQueue6EvItemEEELb0EED0Ev
               (long *param_1)

{
  long *plVar1;
  
  *param_1 = (long)(
                   PTR__ZTVN4Aska11TPoolLegacyINS_13TEventElementINS_18ResourceReadyQueue6EvItemEEELb0EEE_02cc0c38
                   + 0x10);
  plVar1 = param_1 + 4;
  if ((*plVar1 != 0) && ((char)param_1[6] != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 6) = 0;
  }
  *plVar1 = 0;
  param_1[5] = 0;
  param_1[7] = 0;
  if (param_1[8] == 0) {
    param_1[2] = (long)(PTR__ZTVN4Aska9TBitArrayIjLb0EEE_02cba038 + 0x10);
  }
  else if ((char)param_1[9] == '\0') {
    param_1[2] = (long)(PTR__ZTVN4Aska9TBitArrayIjLb0EEE_02cba038 + 0x10);
    param_1[8] = 0;
  }
  else {
    operator delete[](void*)();
    param_1[2] = (long)(PTR__ZTVN4Aska9TBitArrayIjLb0EEE_02cba038 + 0x10);
    param_1[8] = 0;
    if ((param_1[4] != 0) && ((char)param_1[6] != '\0')) {
      operator delete[](void*)();
      *(undefined1 *)(param_1 + 6) = 0;
    }
  }
  *plVar1 = 0;
  param_1[5] = 0;
  param_1[2] = (long)(PTR__ZTVN4Aska13TSmartPointerILb0EEE_02cc2320 + 0x10);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::TPriorityQueue<Aska::ResourceReadyQueue::EvItem, true>::ClearQueue()
// vaddr 0x223ab50 | ghidra 0x233ab50 | size 304 | symbol _ZN4Aska14TPriorityQueueINS_18ResourceReadyQueue6EvItemELb1EE10ClearQueueEv | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Possible PIC construction at 0x0233ac58: Changing call to branch */
/* WARNING: Removing unreachable block (ram,0x0233ac5c) */

void _ZN4Aska14TPriorityQueueINS_18ResourceReadyQueue6EvItemELb1EE10ClearQueueEv(long param_1)

{
  long lVar1;
  long *plVar2;
  long lVar3;
  long lVar4;
  long *plVar5;
  ulong uVar6;
  
  lVar1 = param_1 + 8;
  Aska::CriticalSection::Enter() const(lVar1);
  plVar5 = *(long **)(param_1 + 0x48);
  if ((long *)(param_1 + 0x38) != plVar5) {
    if (plVar5 != (long *)0x0) {
      lVar3 = plVar5[1];
      lVar4 = plVar5[2];
      if (lVar3 != 0) {
        *(long *)(lVar3 + 0x10) = lVar4;
      }
      if (lVar4 != 0) {
        *(long *)(lVar4 + 8) = lVar3;
      }
      if (0 < *(int *)(param_1 + 0xc0)) {
        *(int *)(param_1 + 0xc0) = *(int *)(param_1 + 0xc0) + -1;
      }
      plVar5[1] = 0;
      plVar5[2] = 0;
    }
    Aska::CriticalSection::Enter() const(lVar1);
    plVar2 = *(long **)(param_1 + 0x108);
    if (((plVar2 == (long *)0x0) || (plVar5 < plVar2)) ||
       (plVar2 + (ulong)*(uint *)(param_1 + 0xf4) * 0x11 <= plVar5)) {
      if (plVar5 != (long *)0x0) {
        (**(code **)(*plVar5 + 8))(plVar5);
      }
    }
    else {
      uVar6 = ((long)plVar5 - (long)plVar2 >> 3) * -0xf0f0f0f0f0f0f0f;
      (**(code **)plVar2[(uVar6 & 0xffffffff) * 0x11])();
      lVar3 = (uVar6 >> 5 & 0x7ffffff) * 4;
      *(uint *)(*(long *)(param_1 + 0xe8) + lVar3) =
           *(uint *)(*(long *)(param_1 + 0xe8) + lVar3) &
           (1 << (ulong)((uint)uVar6 & 0x1f) ^ 0xffffffffU);
      *(int *)(param_1 + 0x104) = *(int *)(param_1 + 0x104) + -1;
    }
  }
  (*(code *)PTR__ZNK4Aska15CriticalSection5LeaveEv_02ca8d00)(lVar1);
  return;
}

// ==== Aska::TEventQueue<Aska::ResourceReadyQueue::EvItem>::Set(Aska::ResourceReadyQueue::EvItem const*, unsigned long, unsigned long*, int)
// vaddr 0x223ac80 | ghidra 0x233ac80 | size 424 | symbol _ZN4Aska11TEventQueueINS_18ResourceReadyQueue6EvItemEE3SetEPKS2_mPmi | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska11TEventQueueINS_18ResourceReadyQueue6EvItemEE3SetEPKS2_mPmi
          (long param_1,long param_2,undefined8 param_3,long *param_4,int param_5)

{
  long lVar1;
  long *plVar2;
  undefined4 uVar3;
  long lVar4;
  long lVar5;
  code *pcVar6;
  long lVar7;
  
  lVar7 = *(long *)(param_1 + 8);
  if ((lVar7 != 0) &&
     (((*(char *)(lVar7 + 0x119) != '\0' || ((*(uint *)(lVar7 + 0xf0) & 0x3fffffff) != 0)) &&
      (*(long *)(param_1 + 0x10) != 0)))) {
    if (param_5 < 0) {
      Aska::Thread::GetCurrentID()();
      uVar3 = gettid();
      getpriority(0,uVar3);
      param_5 = Aska::Thread::ConvertToIndependentPriority(int)();
      if (param_5 < 0) {
        param_5 = -0x80;
      }
    }
    lVar1 = lVar7 + 8;
    Aska::CriticalSection::Enter() const(lVar1);
    lVar4 = Aska::TPriorityQueue<Aska::ResourceReadyQueue::EvItem, true>::CreateElement()(lVar7);
    if (lVar4 != 0) {
      if ((param_2 != 0) && (lVar4 + 0x28 != param_2)) {
        Aska::ResourceReadyQueue::EvItem::Copy(Aska::ResourceReadyQueue::EvItem const*)(lVar4 + 0x28,param_2);
      }
      *(undefined8 *)(lVar4 + 0x18) = param_3;
      *(ushort *)(lVar4 + 0x22) = (ushort)param_5 & 0xff;
      Aska::CriticalSection::Enter() const(lVar1);
      if (*(char *)(lVar7 + 0x118) == '\0') {
        lVar5 = *(long *)(lVar7 + 0x40);
        *(long *)(lVar4 + 8) = lVar5;
        *(long *)(lVar4 + 0x10) = lVar7 + 0x38;
        *(long *)(lVar7 + 0x40) = lVar4;
        *(long *)(lVar5 + 0x10) = lVar4;
        *(int *)(lVar7 + 0xc0) = *(int *)(lVar7 + 0xc0) + 1;
      }
      else {
        plVar2 = (long *)(lVar7 + 0x30);
        if (*(int *)(lVar7 + 0xc0) == 0) {
          pcVar6 = *(code **)(*plVar2 + 0x10);
        }
        else {
          if (*(ushort *)(lVar4 + 0x22) <= *(ushort *)(*(long *)(lVar7 + 0x48) + 0x22)) {
            lVar5 = *(long *)(lVar7 + 0x40);
            do {
              if (*(ushort *)(lVar4 + 0x22) <= *(ushort *)(lVar5 + 0x22)) {
                (**(code **)(*plVar2 + 0x20))(plVar2,lVar5,lVar4);
                break;
              }
              lVar5 = *(long *)(lVar5 + 8);
            } while (lVar7 + 0x38 != lVar5);
            goto code_r0x0233adec;
          }
          pcVar6 = *(code **)(*plVar2 + 0x18);
        }
        (*pcVar6)(plVar2,lVar4);
      }
code_r0x0233adec:
      Aska::CriticalSection::Leave() const(lVar1);
      Aska::CriticalSection::Leave() const(lVar1);
      if (param_4 != (long *)0x0) {
        *param_4 = lVar4;
      }
      Aska::Event::Set() const(param_1 + 0x10);
      return 1;
    }
    Aska::CriticalSection::Leave() const(lVar1);
  }
  return 0;
}

// ==== Aska::TPriorityQueue<Aska::ResourceReadyQueue::EvItem, true>::CreateElement()
// vaddr 0x223ae28 | ghidra 0x233ae28 | size 388 | symbol _ZN4Aska14TPriorityQueueINS_18ResourceReadyQueue6EvItemELb1EE13CreateElementEv | lib libSOA-3.7.0.so | 2026-10-04
long * _ZN4Aska14TPriorityQueueINS_18ResourceReadyQueue6EvItemELb1EE13CreateElementEv(long param_1)

{
  uint uVar1;
  undefined *puVar2;
  uint uVar3;
  long *plVar4;
  long lVar5;
  uint uVar6;
  long lVar7;
  ulong uVar8;
  ulong uVar9;
  ulong uVar10;
  
  Aska::CriticalSection::Enter() const(param_1 + 8);
  if (*(uint *)(param_1 + 0x104) < *(uint *)(param_1 + 0xf4)) {
    lVar5 = *(long *)(param_1 + 0xe8);
    uVar3 = *(uint *)(param_1 + 0x100);
    do {
      uVar6 = uVar3;
      if (*(uint *)(param_1 + 0xf4) <= uVar6) {
        uVar6 = 0;
      }
      uVar1 = 1 << (ulong)(uVar6 & 0x1f);
      uVar3 = uVar6 + 1;
    } while ((uVar1 & *(uint *)(lVar5 + (ulong)(uVar6 >> 5) * 4)) != 0);
    uVar8 = *(long *)(param_1 + 0x108) + (ulong)uVar6 * 0x88;
    uVar9 = uVar8;
    do {
      uVar10 = uVar9 + 0x7f & 0xffffffffffffff81;
      Hint_Prefetch(uVar9,0,2,0);
      uVar9 = uVar10;
    } while (uVar10 < uVar8 + 0x88);
    *(uint *)(param_1 + 0x100) = uVar6 + 1;
    lVar7 = (ulong)(uVar6 >> 5) * 4;
    *(uint *)(param_1 + 0x104) = *(uint *)(param_1 + 0x104) + 1;
    puVar2 = PTR__ZTVN4Aska13TEventElementINS_18ResourceReadyQueue6EvItemEEE_02cb97c0;
    *(uint *)(lVar5 + lVar7) = *(uint *)(lVar5 + lVar7) | uVar1;
    plVar4 = (long *)(*(long *)(param_1 + 0x108) + (ulong)uVar6 * 0x88);
    plVar4[2] = 0;
    plVar4[1] = 0;
    *plVar4 = (long)(puVar2 + 0x10);
    plVar4[3] = 0;
    *(undefined1 *)(plVar4 + 4) = 1;
    plVar4[7] = 0;
    plVar4[6] = 0;
    plVar4[9] = 0;
    plVar4[8] = 0;
    plVar4[5] = 0;
    plVar4[10] = 0;
    plVar4[0xb] = -1;
    plVar4[0x10] = 0;
    plVar4[0xd] = 0;
    plVar4[0xe] = 0;
    *(undefined4 *)(plVar4 + 0xf) = 0;
    plVar4[0xc] = 0;
    plVar4 = (long *)(*(long *)(param_1 + 0x108) + (ulong)uVar6 * 0x88);
    if (plVar4 != (long *)0x0) goto code_r0x0233af94;
  }
  if (*(char *)(param_1 + 0x119) == '\0') {
    plVar4 = (long *)0x0;
  }
  else {
    plVar4 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x88,PTR__ZSt7nothrow_02cb9a80);
    if (plVar4 != (long *)0x0) {
      *(undefined1 *)(plVar4 + 4) = 1;
      puVar2 = PTR__ZTVN4Aska13TEventElementINS_18ResourceReadyQueue6EvItemEEE_02cb97c0;
      plVar4[3] = 0;
      plVar4[0x10] = 0;
      *plVar4 = (long)(puVar2 + 0x10);
      plVar4[0xd] = 0;
      plVar4[0xe] = 0;
      *(undefined4 *)(plVar4 + 0xf) = 0;
      plVar4[2] = 0;
      plVar4[1] = 0;
      plVar4[8] = 0;
      plVar4[7] = 0;
      plVar4[10] = 0;
      plVar4[9] = 0;
      plVar4[6] = 0;
      plVar4[5] = 0;
      plVar4[0xb] = -1;
      plVar4[0xc] = 0;
    }
  }
code_r0x0233af94:
  Aska::CriticalSection::Leave() const(param_1 + 8);
  return plVar4;
}

// ==== Aska::ResourceReadyQueue::EvItem::Copy(Aska::ResourceReadyQueue::EvItem const*)
// vaddr 0x223afac | ghidra 0x233afac | size 476 | symbol _ZN4Aska18ResourceReadyQueue6EvItem4CopyEPKS1_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18ResourceReadyQueue6EvItem4CopyEPKS1_(long *param_1,long *param_2)

{
  int iVar1;
  int iVar2;
  char cVar3;
  bool bVar4;
  long *plVar5;
  int *piVar6;
  long *plVar7;
  long lVar8;
  long lVar9;
  
  plVar5 = (long *)*param_1;
  if ((long *)*param_2 != plVar5) {
    piVar6 = (int *)param_1[1];
    if (piVar6 == (int *)0x0) {
code_r0x0233aff0:
      if (plVar5 != (long *)0x0) {
        (**(code **)(*plVar5 + 8))();
      }
      if (param_1[1] != 0) {
        Aska::TSharedPointerCode::DeleteCounter(int*)();
      }
    }
    else {
      do {
        iVar1 = *piVar6;
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar6,0x10);
        if (bVar4) {
          *piVar6 = iVar1 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      if (iVar1 + -1 == 0) {
        plVar5 = (long *)*param_1;
        goto code_r0x0233aff0;
      }
    }
    *param_1 = 0;
    param_1[1] = 0;
    piVar6 = (int *)param_2[1];
    param_1[1] = (long)piVar6;
    *param_1 = *param_2;
    if (piVar6 != (int *)0x0) {
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar6,0x10);
        if (bVar4) {
          *piVar6 = *piVar6 + 1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
    }
  }
  plVar7 = param_1 + 7;
  plVar5 = (long *)*plVar7;
  param_1[2] = param_2[2];
  param_1[3] = param_2[3];
  param_1[4] = param_2[4];
  param_1[5] = param_2[5];
  param_1[6] = param_2[6];
  if ((long *)param_2[7] == plVar5) goto code_r0x0233b0d4;
  piVar6 = (int *)param_1[8];
  if (piVar6 == (int *)0x0) {
code_r0x0233b090:
    if (plVar5 != (long *)0x0) {
      (**(code **)(*plVar5 + 0xd0))();
    }
    if (param_1[8] != 0) {
      Aska::TSharedPointerCode::DeleteCounter(int*)();
    }
  }
  else {
    do {
      iVar1 = *piVar6;
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar6,0x10);
      if (bVar4) {
        *piVar6 = iVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
    if (iVar1 + -1 == 0) {
      plVar5 = (long *)*plVar7;
      goto code_r0x0233b090;
    }
  }
  *plVar7 = 0;
  param_1[8] = 0;
  piVar6 = (int *)param_2[8];
  param_1[8] = (long)piVar6;
  param_1[7] = param_2[7];
  if (piVar6 != (int *)0x0) {
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar6,0x10);
      if (bVar4) {
        *piVar6 = *piVar6 + 1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
  }
code_r0x0233b0d4:
  param_1[9] = param_2[9];
  *(int *)(param_1 + 10) = (int)param_2[10];
  lVar8 = param_2[0xb];
  lVar9 = 0;
  if (lVar8 != 0) {
    Aska::CriticalSection::Enter() const(lVar8 + 0x68);
    iVar2 = *(int *)(lVar8 + 0x90);
    iVar1 = iVar2 + 1;
    *(int *)(lVar8 + 0x90) = iVar1;
    if (iVar1 == 0) {
      Aska::Event::Set() const(lVar8);
    }
    else if (iVar2 == 0) {
      Aska::Event::Reset() const(lVar8);
    }
    Aska::CriticalSection::Leave() const(lVar8 + 0x68);
    lVar9 = param_2[0xb];
  }
  lVar8 = param_1[0xb];
  if (lVar8 != 0) {
    Aska::CriticalSection::Enter() const(lVar8 + 0x68);
    iVar1 = *(int *)(lVar8 + 0x90);
    iVar2 = iVar1 + -1;
    *(int *)(lVar8 + 0x90) = iVar2;
    if (iVar2 == 0) {
      Aska::Event::Set() const(lVar8);
    }
    else if (iVar1 == 0) {
      Aska::Event::Reset() const(lVar8);
    }
    Aska::CriticalSection::Leave() const(lVar8 + 0x68);
    param_1[0xb] = 0;
  }
  param_1[0xb] = lVar9;
  return;
}

// ==== Aska::TPriorityQueue<Aska::ResourceReadyQueue::EvItem, true>::Remove(unsigned long, Aska::ResourceReadyQueue::EvItem*)
// vaddr 0x223b188 | ghidra 0x233b188 | size 448 | symbol _ZN4Aska14TPriorityQueueINS_18ResourceReadyQueue6EvItemELb1EE6RemoveEmPS2_ | lib libSOA-3.7.0.so | 2026-10-04
undefined4
_ZN4Aska14TPriorityQueueINS_18ResourceReadyQueue6EvItemELb1EE6RemoveEmPS2_
          (long param_1,long *param_2,long *param_3)

{
  long lVar1;
  long *plVar2;
  long lVar3;
  long lVar4;
  undefined4 uVar5;
  ulong uVar6;
  
  lVar1 = param_1 + 8;
  Aska::CriticalSection::Enter() const(lVar1);
  if (param_2 != (long *)0x0) {
    Aska::CriticalSection::Enter() const(lVar1);
    plVar2 = *(long **)(param_1 + 0x108);
    if (((plVar2 == (long *)0x0) || (param_2 < plVar2)) ||
       (plVar2 + (ulong)*(uint *)(param_1 + 0xf4) * 0x11 <= param_2)) {
      for (plVar2 = *(long **)(param_1 + 0x48); (long *)(param_1 + 0x38U) != plVar2;
          plVar2 = (long *)plVar2[2]) {
        if (plVar2 == param_2) {
          Aska::CriticalSection::Leave() const(lVar1);
          goto code_r0x0233b230;
        }
      }
      Aska::CriticalSection::Leave() const(lVar1);
      uVar5 = 0;
      goto code_r0x0233b32c;
    }
    lVar3 = param_2[4];
    Aska::CriticalSection::Leave() const(lVar1);
    if ((char)lVar3 != '\0') {
code_r0x0233b230:
      if ((param_3 != (long *)0x0) && (param_2 + 5 != param_3)) {
        Aska::ResourceReadyQueue::EvItem::Copy(Aska::ResourceReadyQueue::EvItem const*)(param_3);
      }
      if ((long *)(param_1 + 0x38U) != param_2) {
        lVar3 = param_2[1];
        lVar4 = param_2[2];
        if (lVar3 != 0) {
          *(long *)(lVar3 + 0x10) = lVar4;
        }
        if (lVar4 != 0) {
          *(long *)(lVar4 + 8) = lVar3;
        }
        if (0 < *(int *)(param_1 + 0xc0)) {
          *(int *)(param_1 + 0xc0) = *(int *)(param_1 + 0xc0) + -1;
        }
        param_2[1] = 0;
        param_2[2] = 0;
      }
      Aska::CriticalSection::Enter() const(lVar1);
      plVar2 = *(long **)(param_1 + 0x108);
      if (((plVar2 == (long *)0x0) || (param_2 < plVar2)) ||
         (plVar2 + (ulong)*(uint *)(param_1 + 0xf4) * 0x11 <= param_2)) {
        (**(code **)(*param_2 + 8))(param_2);
      }
      else {
        uVar6 = ((long)param_2 - (long)plVar2 >> 3) * -0xf0f0f0f0f0f0f0f;
        (**(code **)plVar2[(uVar6 & 0xffffffff) * 0x11])();
        lVar3 = (uVar6 >> 5 & 0x7ffffff) * 4;
        *(uint *)(*(long *)(param_1 + 0xe8) + lVar3) =
             *(uint *)(*(long *)(param_1 + 0xe8) + lVar3) &
             (1 << (ulong)((uint)uVar6 & 0x1f) ^ 0xffffffffU);
        *(int *)(param_1 + 0x104) = *(int *)(param_1 + 0x104) + -1;
      }
      Aska::CriticalSection::Leave() const(lVar1);
      uVar5 = 1;
      goto code_r0x0233b32c;
    }
  }
  uVar5 = 0;
code_r0x0233b32c:
  Aska::CriticalSection::Leave() const(lVar1);
  return uVar5;
}

// ==== Aska::TPriorityQueue<Aska::ResourceReadyQueue::EvItem, true>::Acquire(Aska::ResourceReadyQueue::EvItem*, unsigned long, unsigned long*)
// vaddr 0x223b348 | ghidra 0x233b348 | size 460 | symbol _ZN4Aska14TPriorityQueueINS_18ResourceReadyQueue6EvItemELb1EE7AcquireEPS2_mPm | lib libSOA-3.7.0.so | 2026-10-04
undefined4
_ZN4Aska14TPriorityQueueINS_18ResourceReadyQueue6EvItemELb1EE7AcquireEPS2_mPm
          (long param_1,long *param_2,ulong param_3,undefined8 *param_4)

{
  long lVar1;
  long *plVar2;
  long lVar3;
  long lVar4;
  undefined4 uVar5;
  long *plVar6;
  ulong uVar7;
  
  lVar1 = param_1 + 8;
  Aska::CriticalSection::Enter() const(lVar1);
  Aska::CriticalSection::Enter() const(lVar1);
  if ((*(int *)(param_1 + 0xc0) < 1) || (plVar6 = *(long **)(param_1 + 0x48), plVar6 == (long *)0x0)
     ) {
code_r0x0233b3d0:
    Aska::CriticalSection::Leave() const(lVar1);
code_r0x0233b3d8:
    if (param_4 == (undefined8 *)0x0) {
      uVar5 = 0;
    }
    else {
      uVar5 = 0;
      *param_4 = 0;
    }
  }
  else {
    if ((plVar6[3] == 0) || ((plVar6[3] & param_3) != 0)) {
      Aska::CriticalSection::Leave() const(lVar1);
    }
    else {
      do {
        if ((long *)(param_1 + 0x38) == plVar6) goto code_r0x0233b3d0;
        plVar6 = (long *)plVar6[2];
      } while ((plVar6[3] != 0) && ((plVar6[3] & param_3) == 0));
      Aska::CriticalSection::Leave() const(lVar1);
      if (plVar6 == (long *)0x0) goto code_r0x0233b3d8;
    }
    if (plVar6 + 5 != param_2) {
      Aska::ResourceReadyQueue::EvItem::Copy(Aska::ResourceReadyQueue::EvItem const*)(param_2);
    }
    if (param_4 != (undefined8 *)0x0) {
      *param_4 = plVar6;
    }
    if ((long *)(param_1 + 0x38) != plVar6) {
      lVar3 = plVar6[1];
      lVar4 = plVar6[2];
      if (lVar3 != 0) {
        *(long *)(lVar3 + 0x10) = lVar4;
      }
      if (lVar4 != 0) {
        *(long *)(lVar4 + 8) = lVar3;
      }
      if (0 < *(int *)(param_1 + 0xc0)) {
        *(int *)(param_1 + 0xc0) = *(int *)(param_1 + 0xc0) + -1;
      }
      plVar6[1] = 0;
      plVar6[2] = 0;
    }
    Aska::CriticalSection::Enter() const(lVar1);
    plVar2 = *(long **)(param_1 + 0x108);
    if (((plVar2 == (long *)0x0) || (plVar6 < plVar2)) ||
       (plVar2 + (ulong)*(uint *)(param_1 + 0xf4) * 0x11 <= plVar6)) {
      (**(code **)(*plVar6 + 8))(plVar6);
    }
    else {
      uVar7 = ((long)plVar6 - (long)plVar2 >> 3) * -0xf0f0f0f0f0f0f0f;
      (**(code **)plVar2[(uVar7 & 0xffffffff) * 0x11])();
      lVar3 = (uVar7 >> 5 & 0x7ffffff) * 4;
      *(uint *)(*(long *)(param_1 + 0xe8) + lVar3) =
           *(uint *)(*(long *)(param_1 + 0xe8) + lVar3) &
           (1 << (ulong)((uint)uVar7 & 0x1f) ^ 0xffffffffU);
      *(int *)(param_1 + 0x104) = *(int *)(param_1 + 0x104) + -1;
    }
    Aska::CriticalSection::Leave() const(lVar1);
    uVar5 = 1;
  }
  Aska::CriticalSection::Leave() const(lVar1);
  return uVar5;
}


// FAILED to create function at 0296e840 typeinfo name for Aska::DecompressThread::TElementQueue<Aska::DecompressQueue::Element, true>
// FAILED to create function at 0296e890 typeinfo name for Aska::TDynamicQueue<Aska::DecompressQueue::Element, true>
// FAILED to create function at 029d9280 typeinfo name for Aska::TEventPort<Aska::ResourceReadyQueue::EvItem>
// FAILED to create function at 029d92c0 typeinfo name for Aska::TEventQueue<Aska::ResourceReadyQueue::EvItem>
// FAILED to create function at 029d9300 typeinfo name for Aska::TPriorityQueue<Aska::ResourceReadyQueue::EvItem, true>
// FAILED to create function at 029d9340 typeinfo name for Aska::TList<Aska::TEventElement<Aska::ResourceReadyQueue::EvItem> >
// FAILED to create function at 029d9390 typeinfo name for Aska::TEventElement<Aska::ResourceReadyQueue::EvItem>
// FAILED to create function at 029d93d0 typeinfo name for Aska::TPriorityQueue<Aska::ResourceReadyQueue::EvItem, true>::MyPool
// FAILED to create function at 029d9420 typeinfo name for Aska::TPoolLegacy<Aska::TEventElement<Aska::ResourceReadyQueue::EvItem>, false>
// FAILED to create function at 02bb0360 Aska::DecompressThread::vtable
// FAILED to create function at 02bb0390 Aska::DecompressThread::typeinfo
// FAILED to create function at 02bb03a8 Aska::DecompressThread::TElementQueue<Aska::DecompressQueue::Element,true>::vtable
// FAILED to create function at 02bb03c8 Aska::TDynamicQueue<Aska::DecompressQueue::Element,true>::typeinfo
// FAILED to create function at 02bb03e0 Aska::DecompressThread::TElementQueue<Aska::DecompressQueue::Element,true>::typeinfo
// FAILED to create function at 02bb03f8 Aska::TDynamicQueue<Aska::DecompressQueue::Element,true>::vtable
// FAILED to create function at 02c5eeb8 Aska::ResourceReadyQueue::vtable
// FAILED to create function at 02c5ef00 Aska::ResourceReadyQueue::typeinfo
// FAILED to create function at 02c5ef18 Aska::TEventPort<Aska::ResourceReadyQueue::EvItem>::vtable
// FAILED to create function at 02c5ef38 Aska::TEventPort<Aska::ResourceReadyQueue::EvItem>::typeinfo
// FAILED to create function at 02c5ef48 Aska::TEventQueue<Aska::ResourceReadyQueue::EvItem>::vtable
// FAILED to create function at 02c5ef68 Aska::TEventQueue<Aska::ResourceReadyQueue::EvItem>::typeinfo
// FAILED to create function at 02c5ef78 Aska::TPriorityQueue<Aska::ResourceReadyQueue::EvItem,true>::vtable
// FAILED to create function at 02c5ef98 Aska::TPriorityQueue<Aska::ResourceReadyQueue::EvItem,true>::typeinfo
// FAILED to create function at 02c5efa8 Aska::TList<Aska::TEventElement<Aska::ResourceReadyQueue::EvItem>>::vtable
// FAILED to create function at 02c5efe8 Aska::TList<Aska::TEventElement<Aska::ResourceReadyQueue::EvItem>>::typeinfo
// FAILED to create function at 02c5eff8 Aska::TEventElement<Aska::ResourceReadyQueue::EvItem>::vtable
// FAILED to create function at 02c5f020 Aska::TEventElement<Aska::ResourceReadyQueue::EvItem>::typeinfo
// FAILED to create function at 02c5f038 Aska::TPriorityQueue<Aska::ResourceReadyQueue::EvItem,true>::MyPool::vtable
// FAILED to create function at 02c5f060 Aska::TPoolLegacy<Aska::TEventElement<Aska::ResourceReadyQueue::EvItem>,false>::typeinfo
// FAILED to create function at 02c5f080 Aska::TPriorityQueue<Aska::ResourceReadyQueue::EvItem,true>::MyPool::typeinfo
// FAILED to create function at 02c5f098 Aska::TPoolLegacy<Aska::TEventElement<Aska::ResourceReadyQueue::EvItem>,false>::vtable
