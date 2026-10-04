// port/decomp/kernel/message_dispatcher.c: Ghidra decompiles for the kernel subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-04 06:11 UTC: tools/decomp.sh '--into' 'kernel/message_dispatcher' 'SimpleMessageDispatcher::' 'MessageDispatcherBlock::' 'Global::InstantiateMessageDispatcher'

// ==== Aska::SimpleMessageDispatcher::PostMessage(unsigned short, Aska::INotify*, void*, void*, unsigned int*, signed char)
// vaddr 0x1f5cd28 | ghidra 0x205cd28 | size 752 | symbol _ZN4Aska23SimpleMessageDispatcher11PostMessageEtPNS_7INotifyEPvS3_Pja | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska23SimpleMessageDispatcher11PostMessageEtPNS_7INotifyEPvS3_Pja
          (long param_1,ushort param_2,undefined8 param_3,undefined8 param_4,undefined8 param_5,
          uint *param_6,char param_7)

{
  int *piVar1;
  uint uVar2;
  ushort uVar3;
  char cVar4;
  bool bVar5;
  ulong uVar6;
  int iVar7;
  int *piVar8;
  long lVar9;
  long lVar10;
  long lVar11;
  
  piVar8 = (int *)(param_1 + 0x40);
  iVar7 = 0;
code_r0x0205cd64:
  if (*piVar8 == -1) {
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar8,0x10);
    if (bVar5) {
      *piVar8 = 0;
      cVar4 = ExclusiveMonitorsStatus();
    }
    if (cVar4 == '\0') goto code_r0x0205ce2c;
    goto code_r0x0205cd64;
  }
  ClearExclusiveLocal();
  bVar5 = iVar7 < 0x1ff;
  iVar7 = iVar7 + 1;
  if (bVar5) goto code_r0x0205cd64;
  piVar1 = (int *)(param_1 + 0x44);
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
        uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x80);
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
          Aska::Semaphore::Wait() const(param_1 + 0x80);
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
          if (cVar4 == '\0') goto code_r0x0205ce1c;
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
code_r0x0205ce1c:
  do {
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar5) {
      *piVar1 = *piVar1 + -1;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
code_r0x0205ce2c:
  DataMemoryBarrier(2,3);
  uVar2 = 0;
  if (*(int *)(param_1 + 0x124) + 1U < *(uint *)(param_1 + 0x128)) {
    uVar2 = *(int *)(param_1 + 0x124) + 1;
  }
  if (uVar2 == *(uint *)(param_1 + 0x120)) {
    *(undefined1 *)(param_1 + 0x1b0) = 1;
    Aska::Event::Reset() const(param_1 + 0x148);
    DataMemoryBarrier(2,3);
    *(undefined4 *)(param_1 + 0x40) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar8 = (int *)(param_1 + 0x44);
    if (0x14 < *piVar8) {
      do {
        cVar4 = '\x01';
        bVar5 = (bool)ExclusiveMonitorPass(piVar8,0x10);
        if (bVar5) {
          *piVar8 = *piVar8 + -1;
          cVar4 = ExclusiveMonitorsStatus();
        }
      } while (cVar4 != '\0');
      uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x80);
      if ((uVar6 & 1) != 0) {
        Aska::Semaphore::Signal() const(param_1 + 0x80);
      }
    }
    return 0;
  }
  *(uint *)(param_1 + 0x124) = uVar2;
  lVar9 = *(long *)(param_1 + 0xa8);
  lVar11 = *(long *)(*(long *)(param_1 + 0x130) + (ulong)uVar2 * 8);
  do {
    if (param_1 + 0xa0 == lVar9) {
      lVar9 = *(long *)(param_1 + 0xb0);
      *(long *)(lVar11 + 8) = param_1 + 0xa0;
      *(long *)(lVar11 + 0x10) = lVar9;
      *(long *)(lVar9 + 8) = lVar11;
      *(long *)(param_1 + 0xb0) = lVar11;
code_r0x0205cf0c:
      *(int *)(param_1 + 0x110) = *(int *)(param_1 + 0x110) + 1;
      *(char *)(lVar11 + 0x68) = param_7;
      memset(lVar11 + 0x18,0,0x50);
      uVar3 = *(ushort *)(param_1 + 0x1ca);
      *(ushort *)(param_1 + 0x1ca) = uVar3 + 1;
      *(ushort *)(lVar11 + 0x18) = uVar3;
      *(ushort *)(lVar11 + 0x1a) = param_2 & 0x3fff;
      *(undefined8 *)(lVar11 + 0x20) = param_3;
      *(undefined8 *)(lVar11 + 0x48) = param_4;
      *(undefined8 *)(lVar11 + 0x50) = param_5;
      if (param_6 != (uint *)0x0) {
        *param_6 = (uint)uVar3;
      }
      DataMemoryBarrier(2,3);
      *(undefined4 *)(param_1 + 0x40) = 0xffffffff;
      DataMemoryBarrier(2,3);
      piVar8 = (int *)(param_1 + 0x44);
      if (0x14 < *piVar8) {
        do {
          cVar4 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(piVar8,0x10);
          if (bVar5) {
            *piVar8 = *piVar8 + -1;
            cVar4 = ExclusiveMonitorsStatus();
          }
        } while (cVar4 != '\0');
        uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x80);
        if ((uVar6 & 1) != 0) {
          Aska::Semaphore::Signal() const(param_1 + 0x80);
        }
      }
      iVar7 = *(int *)(param_1 + 0x1b8);
      if (0 < iVar7) {
        lVar11 = 0;
        lVar9 = 0;
        do {
          lVar10 = *(long *)(param_1 + 0x1c0) + lVar11;
          if ((*(char *)(lVar10 + 0x84) != '\0') && (*(char *)(lVar10 + 0x83) == '\0')) {
            lVar10 = *(long *)(param_1 + 0x1c0) + lVar11 + 0x18;
            uVar6 = Aska::Event::IsSignal() const(lVar10);
            if ((uVar6 & 1) == 0) {
              Aska::Event::Set() const(lVar10);
              return 1;
            }
          }
          lVar9 = lVar9 + 1;
          lVar11 = lVar11 + 0xe0;
        } while (lVar9 < iVar7);
      }
      return 1;
    }
    if (param_7 <= *(char *)(lVar9 + 0x68)) {
      lVar10 = *(long *)(lVar9 + 0x10);
      *(long *)(lVar11 + 8) = lVar9;
      *(long *)(lVar11 + 0x10) = lVar10;
      *(long *)(lVar10 + 8) = lVar11;
      *(long *)(lVar9 + 0x10) = lVar11;
      goto code_r0x0205cf0c;
    }
    lVar9 = *(long *)(lVar9 + 8);
  } while( true );
}

// ==== Aska::SimpleMessageDispatcher::AddMessage(signed char)
// vaddr 0x1f5d018 | ghidra 0x205d018 | size 200 | symbol _ZN4Aska23SimpleMessageDispatcher10AddMessageEa | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska23SimpleMessageDispatcher10AddMessageEa(long param_1,char param_2)

{
  uint uVar1;
  long lVar2;
  long lVar3;
  long lVar4;
  
  uVar1 = 0;
  if (*(int *)(param_1 + 0x124) + 1U < *(uint *)(param_1 + 0x128)) {
    uVar1 = *(int *)(param_1 + 0x124) + 1;
  }
  if (uVar1 == *(uint *)(param_1 + 0x120)) {
    *(undefined1 *)(param_1 + 0x1b0) = 1;
    Aska::Event::Reset() const(param_1 + 0x148);
    lVar4 = 0;
  }
  else {
    *(uint *)(param_1 + 0x124) = uVar1;
    lVar2 = *(long *)(*(long *)(param_1 + 0x130) + (ulong)uVar1 * 8);
    for (lVar4 = *(long *)(param_1 + 0xa8); param_1 + 0xa0 != lVar4; lVar4 = *(long *)(lVar4 + 8)) {
      if (param_2 <= *(char *)(lVar4 + 0x68)) {
        lVar3 = *(long *)(lVar4 + 0x10);
        *(long *)(lVar2 + 8) = lVar4;
        *(long *)(lVar2 + 0x10) = lVar3;
        *(long *)(lVar3 + 8) = lVar2;
        *(long *)(lVar4 + 0x10) = lVar2;
        goto code_r0x0205d0b0;
      }
    }
    lVar4 = *(long *)(param_1 + 0xb0);
    *(long *)(lVar2 + 8) = param_1 + 0xa0;
    *(long *)(lVar2 + 0x10) = lVar4;
    *(long *)(lVar4 + 8) = lVar2;
    *(long *)(param_1 + 0xb0) = lVar2;
code_r0x0205d0b0:
    lVar4 = lVar2 + 0x18;
    *(int *)(param_1 + 0x110) = *(int *)(param_1 + 0x110) + 1;
    *(char *)(lVar2 + 0x68) = param_2;
    memset(lVar4,0,0x50);
  }
  return lVar4;
}

// ==== Aska::SimpleMessageDispatcher::WakeupWorkerThread()
// vaddr 0x1f5d0e0 | ghidra 0x205d0e0 | size 132 | symbol _ZN4Aska23SimpleMessageDispatcher18WakeupWorkerThreadEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska23SimpleMessageDispatcher18WakeupWorkerThreadEv(long param_1)

{
  long lVar1;
  int iVar2;
  ulong uVar3;
  long lVar4;
  long lVar5;
  
  iVar2 = *(int *)(param_1 + 0x1b8);
  if (0 < iVar2) {
    lVar4 = 0;
    lVar5 = 0;
    do {
      lVar1 = *(long *)(param_1 + 0x1c0) + lVar4;
      if ((*(char *)(lVar1 + 0x84) != '\0') && (*(char *)(lVar1 + 0x83) == '\0')) {
        lVar1 = *(long *)(param_1 + 0x1c0) + lVar4 + 0x18;
        uVar3 = Aska::Event::IsSignal() const(lVar1);
        if ((uVar3 & 1) == 0) {
          Aska::Event::Set() const(lVar1);
          return 1;
        }
      }
      lVar5 = lVar5 + 1;
      lVar4 = lVar4 + 0xe0;
    } while (lVar5 < iVar2);
  }
  return 0;
}

// ==== Aska::SimpleMessageDispatcher::PostMessage(unsigned short, Aska::INotify*, void*, void*, unsigned long, unsigned long, unsigned int*, signed char)
// vaddr 0x1f5d164 | ghidra 0x205d164 | size 784 | symbol _ZN4Aska23SimpleMessageDispatcher11PostMessageEtPNS_7INotifyEPvS3_mmPja | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska23SimpleMessageDispatcher11PostMessageEtPNS_7INotifyEPvS3_mmPja
          (long param_1,ushort param_2,undefined8 param_3,undefined8 param_4,undefined8 param_5,
          undefined8 param_6,undefined8 param_7,uint *param_8,char param_9)

{
  int *piVar1;
  uint uVar2;
  ushort uVar3;
  char cVar4;
  bool bVar5;
  ulong uVar6;
  int iVar7;
  int *piVar8;
  long lVar9;
  long lVar10;
  long lVar11;
  
  piVar8 = (int *)(param_1 + 0x40);
  iVar7 = 0;
code_r0x0205d1ac:
  if (*piVar8 == -1) {
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar8,0x10);
    if (bVar5) {
      *piVar8 = 0;
      cVar4 = ExclusiveMonitorsStatus();
    }
    if (cVar4 == '\0') goto code_r0x0205d280;
    goto code_r0x0205d1ac;
  }
  ClearExclusiveLocal();
  bVar5 = iVar7 < 0x1ff;
  iVar7 = iVar7 + 1;
  if (bVar5) goto code_r0x0205d1ac;
  piVar1 = (int *)(param_1 + 0x44);
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
      uVar6 = Aska::Semaphore::IsReady() const();
      if ((uVar6 & 1) == 0) goto code_r0x0205d234;
      do {
        Aska::Semaphore::Wait() const(param_1 + 0x80);
        while( true ) {
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
            if (cVar4 == '\0') goto code_r0x0205d270;
          }
          ClearExclusiveLocal();
          uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x80);
          if ((uVar6 & 1) != 0) break;
code_r0x0205d234:
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
      } while( true );
    }
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar8,0x10);
    if (bVar5) {
      *piVar8 = 0;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
code_r0x0205d270:
  do {
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar5) {
      *piVar1 = *piVar1 + -1;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
code_r0x0205d280:
  DataMemoryBarrier(2,3);
  uVar2 = 0;
  if (*(int *)(param_1 + 0x124) + 1U < *(uint *)(param_1 + 0x128)) {
    uVar2 = *(int *)(param_1 + 0x124) + 1;
  }
  if (uVar2 == *(uint *)(param_1 + 0x120)) {
    *(undefined1 *)(param_1 + 0x1b0) = 1;
    Aska::Event::Reset() const(param_1 + 0x148);
    DataMemoryBarrier(2,3);
    *(undefined4 *)(param_1 + 0x40) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar8 = (int *)(param_1 + 0x44);
    if (0x14 < *piVar8) {
      do {
        cVar4 = '\x01';
        bVar5 = (bool)ExclusiveMonitorPass(piVar8,0x10);
        if (bVar5) {
          *piVar8 = *piVar8 + -1;
          cVar4 = ExclusiveMonitorsStatus();
        }
      } while (cVar4 != '\0');
      uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x80);
      if ((uVar6 & 1) != 0) {
        Aska::Semaphore::Signal() const(param_1 + 0x80);
      }
    }
    return 0;
  }
  *(uint *)(param_1 + 0x124) = uVar2;
  lVar9 = *(long *)(param_1 + 0xa8);
  lVar11 = *(long *)(*(long *)(param_1 + 0x130) + (ulong)uVar2 * 8);
  do {
    if (param_1 + 0xa0 == lVar9) {
      lVar9 = *(long *)(param_1 + 0xb0);
      *(long *)(lVar11 + 8) = param_1 + 0xa0;
      *(long *)(lVar11 + 0x10) = lVar9;
      *(long *)(lVar9 + 8) = lVar11;
      *(long *)(param_1 + 0xb0) = lVar11;
code_r0x0205d360:
      *(int *)(param_1 + 0x110) = *(int *)(param_1 + 0x110) + 1;
      *(char *)(lVar11 + 0x68) = param_9;
      memset(lVar11 + 0x18,0,0x50);
      uVar3 = *(ushort *)(param_1 + 0x1ca);
      *(ushort *)(param_1 + 0x1ca) = uVar3 + 1;
      *(ushort *)(lVar11 + 0x18) = uVar3;
      *(ushort *)(lVar11 + 0x1a) = param_2 & 0x3fff;
      *(undefined8 *)(lVar11 + 0x20) = param_3;
      *(undefined8 *)(lVar11 + 0x48) = param_4;
      *(undefined8 *)(lVar11 + 0x50) = param_5;
      *(undefined8 *)(lVar11 + 0x58) = param_6;
      *(undefined8 *)(lVar11 + 0x60) = param_7;
      if (param_8 != (uint *)0x0) {
        *param_8 = (uint)uVar3;
      }
      DataMemoryBarrier(2,3);
      *(undefined4 *)(param_1 + 0x40) = 0xffffffff;
      DataMemoryBarrier(2,3);
      piVar8 = (int *)(param_1 + 0x44);
      if (0x14 < *piVar8) {
        do {
          cVar4 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(piVar8,0x10);
          if (bVar5) {
            *piVar8 = *piVar8 + -1;
            cVar4 = ExclusiveMonitorsStatus();
          }
        } while (cVar4 != '\0');
        uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x80);
        if ((uVar6 & 1) != 0) {
          Aska::Semaphore::Signal() const(param_1 + 0x80);
        }
      }
      iVar7 = *(int *)(param_1 + 0x1b8);
      if (0 < iVar7) {
        lVar11 = 0;
        lVar9 = 0;
        do {
          lVar10 = *(long *)(param_1 + 0x1c0) + lVar11;
          if ((*(char *)(lVar10 + 0x84) != '\0') && (*(char *)(lVar10 + 0x83) == '\0')) {
            lVar10 = *(long *)(param_1 + 0x1c0) + lVar11 + 0x18;
            uVar6 = Aska::Event::IsSignal() const(lVar10);
            if ((uVar6 & 1) == 0) {
              Aska::Event::Set() const(lVar10);
              return 1;
            }
          }
          lVar9 = lVar9 + 1;
          lVar11 = lVar11 + 0xe0;
        } while (lVar9 < iVar7);
      }
      return 1;
    }
    if (param_9 <= *(char *)(lVar9 + 0x68)) {
      lVar10 = *(long *)(lVar9 + 0x10);
      *(long *)(lVar11 + 8) = lVar9;
      *(long *)(lVar11 + 0x10) = lVar10;
      *(long *)(lVar10 + 8) = lVar11;
      *(long *)(lVar9 + 0x10) = lVar11;
      goto code_r0x0205d360;
    }
    lVar9 = *(long *)(lVar9 + 8);
  } while( true );
}

// ==== Aska::SimpleMessageDispatcher::PostMultiMessages(Aska::SimpleMessageDispatcher::Argument*, int, signed char)
// vaddr 0x1f5d474 | ghidra 0x205d474 | size 876 | symbol _ZN4Aska23SimpleMessageDispatcher17PostMultiMessagesEPNS0_8ArgumentEia | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska23SimpleMessageDispatcher17PostMultiMessagesEPNS0_8ArgumentEia
          (long param_1,ushort *param_2,int param_3,char param_4)

{
  int *piVar1;
  uint uVar2;
  ushort uVar3;
  char cVar4;
  bool bVar5;
  ulong uVar6;
  int iVar7;
  long lVar8;
  int *piVar9;
  long lVar10;
  long lVar11;
  ushort *puVar12;
  long lVar13;
  
  piVar9 = (int *)(param_1 + 0x40);
  iVar7 = 0;
code_r0x0205d49c:
  do {
    if (*piVar9 != -1) {
      ClearExclusiveLocal();
      bVar5 = iVar7 < 0x1ff;
      iVar7 = iVar7 + 1;
      if (bVar5) goto code_r0x0205d49c;
      piVar1 = (int *)(param_1 + 0x44);
      do {
        cVar4 = '\x01';
        bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
        if (bVar5) {
          *piVar1 = *piVar1 + 1;
          cVar4 = ExclusiveMonitorsStatus();
        }
      } while (cVar4 != '\0');
      do {
        if (*piVar9 != -1) {
          ClearExclusiveLocal();
          do {
            uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x80);
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
              Aska::Semaphore::Wait() const(param_1 + 0x80);
            }
            do {
              cVar4 = '\x01';
              bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
              if (bVar5) {
                *piVar1 = *piVar1 + 1;
                cVar4 = ExclusiveMonitorsStatus();
              }
            } while (cVar4 != '\0');
            while (*piVar9 == -1) {
              cVar4 = '\x01';
              bVar5 = (bool)ExclusiveMonitorPass(piVar9,0x10);
              if (bVar5) {
                *piVar9 = 0;
                cVar4 = ExclusiveMonitorsStatus();
              }
              if (cVar4 == '\0') goto code_r0x0205d554;
            }
            ClearExclusiveLocal();
          } while( true );
        }
        cVar4 = '\x01';
        bVar5 = (bool)ExclusiveMonitorPass(piVar9,0x10);
        if (bVar5) {
          *piVar9 = 0;
          cVar4 = ExclusiveMonitorsStatus();
        }
      } while (cVar4 != '\0');
code_r0x0205d554:
      do {
        cVar4 = '\x01';
        bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
        if (bVar5) {
          *piVar1 = *piVar1 + -1;
          cVar4 = ExclusiveMonitorsStatus();
        }
      } while (cVar4 != '\0');
code_r0x0205d564:
      DataMemoryBarrier(2,3);
      if (0 < param_3) {
        lVar11 = param_1 + 0xa0;
        puVar12 = param_2;
        do {
          *puVar12 = *puVar12 & 0x3fff;
          uVar3 = *(ushort *)(param_1 + 0x1ca);
          *(ushort *)(param_1 + 0x1ca) = uVar3 + 1;
          puVar12[1] = uVar3;
          uVar2 = 0;
          if (*(int *)(param_1 + 0x124) + 1U < *(uint *)(param_1 + 0x128)) {
            uVar2 = *(int *)(param_1 + 0x124) + 1;
          }
          if (uVar2 == *(uint *)(param_1 + 0x120)) {
            *(undefined1 *)(param_1 + 0x1b0) = 1;
            Aska::Event::Reset() const(param_1 + 0x148);
            do {
              if (puVar12 <= param_2) {
                DataMemoryBarrier(2,3);
                *(undefined4 *)(param_1 + 0x40) = 0xffffffff;
                DataMemoryBarrier(2,3);
                piVar9 = (int *)(param_1 + 0x44);
                if (0x14 < *piVar9) {
                  do {
                    cVar4 = '\x01';
                    bVar5 = (bool)ExclusiveMonitorPass(piVar9,0x10);
                    if (bVar5) {
                      *piVar9 = *piVar9 + -1;
                      cVar4 = ExclusiveMonitorsStatus();
                    }
                  } while (cVar4 != '\0');
                  uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x80);
                  if ((uVar6 & 1) != 0) {
                    Aska::Semaphore::Signal() const(param_1 + 0x80);
                  }
                }
                return 0;
              }
              lVar8 = *(long *)(param_1 + 0xa8);
              if (lVar11 != lVar8) {
                do {
                  if (*(ushort *)(lVar8 + 0x18) == param_2[1]) {
                    lVar13 = *(long *)(lVar8 + 8);
                    lVar10 = *(long *)(lVar8 + 0x10);
                    if (lVar13 != 0) {
                      *(long *)(lVar13 + 0x10) = lVar10;
                    }
                    if (lVar10 != 0) {
                      *(long *)(lVar10 + 8) = lVar13;
                    }
                    if (0 < *(int *)(param_1 + 0x110)) {
                      *(int *)(param_1 + 0x110) = *(int *)(param_1 + 0x110) + -1;
                    }
                    *(long *)(lVar8 + 8) = 0;
                    *(undefined8 *)(lVar8 + 0x10) = 0;
                    break;
                  }
                  lVar8 = *(long *)(lVar8 + 8);
                } while (lVar11 != lVar8);
              }
              param_2 = param_2 + 0x14;
            } while( true );
          }
          *(uint *)(param_1 + 0x124) = uVar2;
          lVar13 = *(long *)(*(long *)(param_1 + 0x130) + (ulong)uVar2 * 8);
          for (lVar8 = *(long *)(param_1 + 0xa8); lVar11 != lVar8; lVar8 = *(long *)(lVar8 + 8)) {
            if (param_4 <= *(char *)(lVar8 + 0x68)) {
              lVar10 = *(long *)(lVar8 + 0x10);
              *(long *)(lVar13 + 8) = lVar8;
              *(long *)(lVar13 + 0x10) = lVar10;
              *(long *)(lVar10 + 8) = lVar13;
              *(long *)(lVar8 + 0x10) = lVar13;
              goto code_r0x0205d614;
            }
          }
          lVar8 = *(long *)(param_1 + 0xb0);
          *(long *)(lVar13 + 8) = lVar11;
          *(long *)(lVar13 + 0x10) = lVar8;
          *(long *)(lVar8 + 8) = lVar13;
          *(long *)(param_1 + 0xb0) = lVar13;
code_r0x0205d614:
          *(int *)(param_1 + 0x110) = *(int *)(param_1 + 0x110) + 1;
          *(char *)(lVar13 + 0x68) = param_4;
          memset(lVar13 + 0x18,0,0x50);
          uVar3 = *(ushort *)(param_1 + 0x1ca);
          *(ushort *)(param_1 + 0x1ca) = uVar3 + 1;
          puVar12[1] = uVar3;
          *(ushort *)(lVar13 + 0x18) = uVar3;
          *(ushort *)(lVar13 + 0x1a) = *puVar12;
          *(undefined8 *)(lVar13 + 0x20) = *(undefined8 *)(puVar12 + 4);
          *(undefined8 *)(lVar13 + 0x48) = *(undefined8 *)(puVar12 + 8);
          *(undefined8 *)(lVar13 + 0x50) = *(undefined8 *)(puVar12 + 0xc);
          if (*(uint **)(puVar12 + 0x10) != (uint *)0x0) {
            **(uint **)(puVar12 + 0x10) = (uint)uVar3;
          }
          puVar12 = puVar12 + 0x14;
        } while (puVar12 < param_2 + (long)param_3 * 0x14);
      }
      DataMemoryBarrier(2,3);
      *(undefined4 *)(param_1 + 0x40) = 0xffffffff;
      DataMemoryBarrier(2,3);
      piVar9 = (int *)(param_1 + 0x44);
      if (0x14 < *piVar9) {
        do {
          cVar4 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(piVar9,0x10);
          if (bVar5) {
            *piVar9 = *piVar9 + -1;
            cVar4 = ExclusiveMonitorsStatus();
          }
        } while (cVar4 != '\0');
        uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x80);
        if ((uVar6 & 1) != 0) {
          Aska::Semaphore::Signal() const(param_1 + 0x80);
        }
      }
      uVar6 = (ulong)*(uint *)(param_1 + 0x1b8);
      if (0 < (int)*(uint *)(param_1 + 0x1b8)) {
        lVar11 = 0x84;
        do {
          if (*(char *)(*(long *)(param_1 + 0x1c0) + lVar11) != '\0') {
            Aska::Event::Set() const(*(long *)(param_1 + 0x1c0) + lVar11 + -0x6c);
          }
          uVar6 = uVar6 - 1;
          lVar11 = lVar11 + 0xe0;
        } while (uVar6 != 0);
      }
      return 1;
    }
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar9,0x10);
    if (bVar5) {
      *piVar9 = 0;
      cVar4 = ExclusiveMonitorsStatus();
    }
    if (cVar4 == '\0') goto code_r0x0205d564;
  } while( true );
}

// ==== Aska::SimpleMessageDispatcher::DeleteMessage(int)
// vaddr 0x1f5d7e0 | ghidra 0x205d7e0 | size 120 | symbol _ZN4Aska23SimpleMessageDispatcher13DeleteMessageEi | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska23SimpleMessageDispatcher13DeleteMessageEi(long param_1,uint param_2)

{
  long lVar1;
  long lVar2;
  long lVar3;
  
  if ((int)param_2 < 0) {
    *(long *)(param_1 + 0xa8) = param_1 + 0xa0;
    *(long *)(param_1 + 0xb0) = param_1 + 0xa0;
    return 1;
  }
  lVar1 = *(long *)(param_1 + 0xa8);
  while( true ) {
    if (param_1 + 0xa0 == lVar1) {
      return 0;
    }
    if (*(ushort *)(lVar1 + 0x18) == param_2) break;
    lVar1 = *(long *)(lVar1 + 8);
  }
  lVar2 = *(long *)(lVar1 + 8);
  lVar3 = *(long *)(lVar1 + 0x10);
  if (lVar2 != 0) {
    *(long *)(lVar2 + 0x10) = lVar3;
  }
  if (lVar3 != 0) {
    *(long *)(lVar3 + 8) = lVar2;
  }
  if (0 < *(int *)(param_1 + 0x110)) {
    *(int *)(param_1 + 0x110) = *(int *)(param_1 + 0x110) + -1;
  }
  *(long *)(lVar1 + 8) = 0;
  *(undefined8 *)(lVar1 + 0x10) = 0;
  return 1;
}

// ==== Aska::SimpleMessageDispatcher::WakeupAllWorkerThreads()
// vaddr 0x1f5d858 | ghidra 0x205d858 | size 76 | symbol _ZN4Aska23SimpleMessageDispatcher22WakeupAllWorkerThreadsEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska23SimpleMessageDispatcher22WakeupAllWorkerThreadsEv(long param_1)

{
  ulong uVar1;
  long lVar2;
  
  uVar1 = (ulong)*(uint *)(param_1 + 0x1b8);
  if (0 < (int)*(uint *)(param_1 + 0x1b8)) {
    lVar2 = 0x84;
    do {
      if (*(char *)(*(long *)(param_1 + 0x1c0) + lVar2) != '\0') {
        Aska::Event::Set() const(*(long *)(param_1 + 0x1c0) + lVar2 + -0x6c);
      }
      uVar1 = uVar1 - 1;
      lVar2 = lVar2 + 0xe0;
    } while (uVar1 != 0);
  }
  return;
}

// ==== Aska::SimpleMessageDispatcher::PostMultiMessages(Aska::SimpleMessageDispatcher::ArgumentEx*, int, signed char)
// vaddr 0x1f5d8a4 | ghidra 0x205d8a4 | size 876 | symbol _ZN4Aska23SimpleMessageDispatcher17PostMultiMessagesEPNS0_10ArgumentExEia | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska23SimpleMessageDispatcher17PostMultiMessagesEPNS0_10ArgumentExEia
          (long param_1,ushort *param_2,int param_3,char param_4)

{
  int *piVar1;
  uint uVar2;
  ushort uVar3;
  char cVar4;
  bool bVar5;
  ulong uVar6;
  int iVar7;
  long lVar8;
  int *piVar9;
  long lVar10;
  long lVar11;
  ushort *puVar12;
  long lVar13;
  
  piVar9 = (int *)(param_1 + 0x40);
  iVar7 = 0;
code_r0x0205d8cc:
  do {
    if (*piVar9 != -1) {
      ClearExclusiveLocal();
      bVar5 = iVar7 < 0x1ff;
      iVar7 = iVar7 + 1;
      if (bVar5) goto code_r0x0205d8cc;
      piVar1 = (int *)(param_1 + 0x44);
      do {
        cVar4 = '\x01';
        bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
        if (bVar5) {
          *piVar1 = *piVar1 + 1;
          cVar4 = ExclusiveMonitorsStatus();
        }
      } while (cVar4 != '\0');
      do {
        if (*piVar9 != -1) {
          ClearExclusiveLocal();
          do {
            uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x80);
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
              Aska::Semaphore::Wait() const(param_1 + 0x80);
            }
            do {
              cVar4 = '\x01';
              bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
              if (bVar5) {
                *piVar1 = *piVar1 + 1;
                cVar4 = ExclusiveMonitorsStatus();
              }
            } while (cVar4 != '\0');
            while (*piVar9 == -1) {
              cVar4 = '\x01';
              bVar5 = (bool)ExclusiveMonitorPass(piVar9,0x10);
              if (bVar5) {
                *piVar9 = 0;
                cVar4 = ExclusiveMonitorsStatus();
              }
              if (cVar4 == '\0') goto code_r0x0205d984;
            }
            ClearExclusiveLocal();
          } while( true );
        }
        cVar4 = '\x01';
        bVar5 = (bool)ExclusiveMonitorPass(piVar9,0x10);
        if (bVar5) {
          *piVar9 = 0;
          cVar4 = ExclusiveMonitorsStatus();
        }
      } while (cVar4 != '\0');
code_r0x0205d984:
      do {
        cVar4 = '\x01';
        bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
        if (bVar5) {
          *piVar1 = *piVar1 + -1;
          cVar4 = ExclusiveMonitorsStatus();
        }
      } while (cVar4 != '\0');
code_r0x0205d994:
      DataMemoryBarrier(2,3);
      if (0 < param_3) {
        lVar11 = param_1 + 0xa0;
        puVar12 = param_2;
        do {
          *puVar12 = *puVar12 & 0x3fff;
          uVar2 = 0;
          if (*(int *)(param_1 + 0x124) + 1U < *(uint *)(param_1 + 0x128)) {
            uVar2 = *(int *)(param_1 + 0x124) + 1;
          }
          if (uVar2 == *(uint *)(param_1 + 0x120)) {
            *(undefined1 *)(param_1 + 0x1b0) = 1;
            Aska::Event::Reset() const(param_1 + 0x148);
            do {
              if (puVar12 <= param_2) {
                DataMemoryBarrier(2,3);
                *(undefined4 *)(param_1 + 0x40) = 0xffffffff;
                DataMemoryBarrier(2,3);
                piVar9 = (int *)(param_1 + 0x44);
                if (0x14 < *piVar9) {
                  do {
                    cVar4 = '\x01';
                    bVar5 = (bool)ExclusiveMonitorPass(piVar9,0x10);
                    if (bVar5) {
                      *piVar9 = *piVar9 + -1;
                      cVar4 = ExclusiveMonitorsStatus();
                    }
                  } while (cVar4 != '\0');
                  uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x80);
                  if ((uVar6 & 1) != 0) {
                    Aska::Semaphore::Signal() const(param_1 + 0x80);
                  }
                }
                return 0;
              }
              lVar8 = *(long *)(param_1 + 0xa8);
              if (lVar11 != lVar8) {
                do {
                  if (*(ushort *)(lVar8 + 0x18) == param_2[1]) {
                    lVar13 = *(long *)(lVar8 + 8);
                    lVar10 = *(long *)(lVar8 + 0x10);
                    if (lVar13 != 0) {
                      *(long *)(lVar13 + 0x10) = lVar10;
                    }
                    if (lVar10 != 0) {
                      *(long *)(lVar10 + 8) = lVar13;
                    }
                    if (0 < *(int *)(param_1 + 0x110)) {
                      *(int *)(param_1 + 0x110) = *(int *)(param_1 + 0x110) + -1;
                    }
                    *(long *)(lVar8 + 8) = 0;
                    *(undefined8 *)(lVar8 + 0x10) = 0;
                    break;
                  }
                  lVar8 = *(long *)(lVar8 + 8);
                } while (lVar11 != lVar8);
              }
              param_2 = param_2 + 0x1c;
            } while( true );
          }
          *(uint *)(param_1 + 0x124) = uVar2;
          lVar13 = *(long *)(*(long *)(param_1 + 0x130) + (ulong)uVar2 * 8);
          for (lVar8 = *(long *)(param_1 + 0xa8); lVar11 != lVar8; lVar8 = *(long *)(lVar8 + 8)) {
            if (param_4 <= *(char *)(lVar8 + 0x68)) {
              lVar10 = *(long *)(lVar8 + 0x10);
              *(long *)(lVar13 + 8) = lVar8;
              *(long *)(lVar13 + 0x10) = lVar10;
              *(long *)(lVar10 + 8) = lVar13;
              *(long *)(lVar8 + 0x10) = lVar13;
              goto code_r0x0205da34;
            }
          }
          lVar8 = *(long *)(param_1 + 0xb0);
          *(long *)(lVar13 + 8) = lVar11;
          *(long *)(lVar13 + 0x10) = lVar8;
          *(long *)(lVar8 + 8) = lVar13;
          *(long *)(param_1 + 0xb0) = lVar13;
code_r0x0205da34:
          *(int *)(param_1 + 0x110) = *(int *)(param_1 + 0x110) + 1;
          *(char *)(lVar13 + 0x68) = param_4;
          memset(lVar13 + 0x18,0,0x50);
          uVar3 = *(ushort *)(param_1 + 0x1ca);
          *(ushort *)(param_1 + 0x1ca) = uVar3 + 1;
          puVar12[1] = uVar3;
          *(ushort *)(lVar13 + 0x18) = uVar3;
          *(ushort *)(lVar13 + 0x1a) = *puVar12;
          *(undefined8 *)(lVar13 + 0x20) = *(undefined8 *)(puVar12 + 4);
          *(undefined8 *)(lVar13 + 0x48) = *(undefined8 *)(puVar12 + 8);
          *(undefined8 *)(lVar13 + 0x50) = *(undefined8 *)(puVar12 + 0xc);
          *(undefined8 *)(lVar13 + 0x58) = *(undefined8 *)(puVar12 + 0x14);
          *(undefined8 *)(lVar13 + 0x60) = *(undefined8 *)(puVar12 + 0x18);
          if (*(uint **)(puVar12 + 0x10) != (uint *)0x0) {
            **(uint **)(puVar12 + 0x10) = (uint)uVar3;
          }
          puVar12 = puVar12 + 0x1c;
        } while (puVar12 < param_2 + (long)param_3 * 0x1c);
      }
      DataMemoryBarrier(2,3);
      *(undefined4 *)(param_1 + 0x40) = 0xffffffff;
      DataMemoryBarrier(2,3);
      piVar9 = (int *)(param_1 + 0x44);
      if (0x14 < *piVar9) {
        do {
          cVar4 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(piVar9,0x10);
          if (bVar5) {
            *piVar9 = *piVar9 + -1;
            cVar4 = ExclusiveMonitorsStatus();
          }
        } while (cVar4 != '\0');
        uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x80);
        if ((uVar6 & 1) != 0) {
          Aska::Semaphore::Signal() const(param_1 + 0x80);
        }
      }
      uVar6 = (ulong)*(uint *)(param_1 + 0x1b8);
      if (0 < (int)*(uint *)(param_1 + 0x1b8)) {
        lVar11 = 0x84;
        do {
          if (*(char *)(*(long *)(param_1 + 0x1c0) + lVar11) != '\0') {
            Aska::Event::Set() const(*(long *)(param_1 + 0x1c0) + lVar11 + -0x6c);
          }
          uVar6 = uVar6 - 1;
          lVar11 = lVar11 + 0xe0;
        } while (uVar6 != 0);
      }
      return 1;
    }
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar9,0x10);
    if (bVar5) {
      *piVar9 = 0;
      cVar4 = ExclusiveMonitorsStatus();
    }
    if (cVar4 == '\0') goto code_r0x0205d994;
  } while( true );
}

// ==== Aska::SimpleMessageDispatcher::PostSyncMessages(Aska::SimpleMessageDispatcher::Argument*, int, int*, signed char)
// vaddr 0x1f5dc10 | ghidra 0x205dc10 | size 1132 | symbol _ZN4Aska23SimpleMessageDispatcher16PostSyncMessagesEPNS0_8ArgumentEiPia | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska23SimpleMessageDispatcher16PostSyncMessagesEPNS0_8ArgumentEiPia
          (long param_1,ushort *param_2,int param_3,int *param_4,char param_5)

{
  int *piVar1;
  uint uVar2;
  ushort uVar3;
  short sVar4;
  char cVar5;
  bool bVar6;
  ulong uVar7;
  int iVar8;
  long lVar9;
  int *piVar10;
  undefined8 uVar11;
  long lVar12;
  ushort *puVar13;
  long lVar14;
  
  piVar10 = (int *)(param_1 + 0x40);
  iVar8 = 0;
code_r0x0205dc40:
  if (*piVar10 == -1) {
    cVar5 = '\x01';
    bVar6 = (bool)ExclusiveMonitorPass(piVar10,0x10);
    if (bVar6) {
      *piVar10 = 0;
      cVar5 = ExclusiveMonitorsStatus();
    }
    if (cVar5 == '\0') goto code_r0x0205dd08;
    goto code_r0x0205dc40;
  }
  ClearExclusiveLocal();
  bVar6 = iVar8 < 0x1ff;
  iVar8 = iVar8 + 1;
  if (bVar6) goto code_r0x0205dc40;
  piVar1 = (int *)(param_1 + 0x44);
  do {
    cVar5 = '\x01';
    bVar6 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar6) {
      *piVar1 = *piVar1 + 1;
      cVar5 = ExclusiveMonitorsStatus();
    }
  } while (cVar5 != '\0');
  do {
    if (*piVar10 != -1) {
      ClearExclusiveLocal();
      do {
        uVar7 = Aska::Semaphore::IsReady() const(param_1 + 0x80);
        if ((uVar7 & 1) == 0) {
          do {
            cVar5 = '\x01';
            bVar6 = (bool)ExclusiveMonitorPass(piVar1,0x10);
            if (bVar6) {
              *piVar1 = *piVar1 + -1;
              cVar5 = ExclusiveMonitorsStatus();
            }
          } while (cVar5 != '\0');
          Aska::Thread::Sleep(unsigned int)(1);
        }
        else {
          Aska::Semaphore::Wait() const(param_1 + 0x80);
        }
        do {
          cVar5 = '\x01';
          bVar6 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar6) {
            *piVar1 = *piVar1 + 1;
            cVar5 = ExclusiveMonitorsStatus();
          }
        } while (cVar5 != '\0');
        while (*piVar10 == -1) {
          cVar5 = '\x01';
          bVar6 = (bool)ExclusiveMonitorPass(piVar10,0x10);
          if (bVar6) {
            *piVar10 = 0;
            cVar5 = ExclusiveMonitorsStatus();
          }
          if (cVar5 == '\0') goto code_r0x0205dcf8;
        }
        ClearExclusiveLocal();
      } while( true );
    }
    cVar5 = '\x01';
    bVar6 = (bool)ExclusiveMonitorPass(piVar10,0x10);
    if (bVar6) {
      *piVar10 = 0;
      cVar5 = ExclusiveMonitorsStatus();
    }
  } while (cVar5 != '\0');
code_r0x0205dcf8:
  do {
    cVar5 = '\x01';
    bVar6 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar6) {
      *piVar1 = *piVar1 + -1;
      cVar5 = ExclusiveMonitorsStatus();
    }
  } while (cVar5 != '\0');
code_r0x0205dd08:
  DataMemoryBarrier(2,3);
  puVar13 = param_2;
  if (param_3 + -1 != 0 && 0 < param_3) {
    do {
      *puVar13 = *puVar13 & 0x3fff;
      uVar3 = *(ushort *)(param_1 + 0x1ca);
      *(ushort *)(param_1 + 0x1ca) = uVar3 + 1;
      puVar13[1] = uVar3;
      uVar2 = 0;
      if (*(int *)(param_1 + 0x124) + 1U < *(uint *)(param_1 + 0x128)) {
        uVar2 = *(int *)(param_1 + 0x124) + 1;
      }
      if (uVar2 == *(uint *)(param_1 + 0x120)) goto code_r0x0205de4c;
      *(uint *)(param_1 + 0x124) = uVar2;
      lVar14 = *(long *)(*(long *)(param_1 + 0x130) + (ulong)uVar2 * 8);
      for (lVar9 = *(long *)(param_1 + 0xa8); param_1 + 0xa0 != lVar9; lVar9 = *(long *)(lVar9 + 8))
      {
        if (param_5 <= *(char *)(lVar9 + 0x68)) {
          lVar12 = *(long *)(lVar9 + 0x10);
          *(long *)(lVar14 + 8) = lVar9;
          *(long *)(lVar14 + 0x10) = lVar12;
          *(long *)(lVar12 + 8) = lVar14;
          *(long *)(lVar9 + 0x10) = lVar14;
          goto code_r0x0205ddbc;
        }
      }
      lVar9 = *(long *)(param_1 + 0xb0);
      *(long *)(lVar14 + 8) = param_1 + 0xa0;
      *(long *)(lVar14 + 0x10) = lVar9;
      *(long *)(lVar9 + 8) = lVar14;
      *(long *)(param_1 + 0xb0) = lVar14;
code_r0x0205ddbc:
      *(int *)(param_1 + 0x110) = *(int *)(param_1 + 0x110) + 1;
      *(char *)(lVar14 + 0x68) = param_5;
      memset(lVar14 + 0x18,0,0x50);
      uVar3 = *(ushort *)(param_1 + 0x1ca);
      *(ushort *)(param_1 + 0x1ca) = uVar3 + 1;
      puVar13[1] = uVar3;
      *(ushort *)(lVar14 + 0x18) = uVar3;
      *(ushort *)(lVar14 + 0x1a) = *puVar13;
      uVar11 = *(undefined8 *)(puVar13 + 4);
      *(int **)(lVar14 + 0x40) = param_4;
      *(undefined8 *)(lVar14 + 0x20) = uVar11;
      *(undefined8 *)(lVar14 + 0x48) = *(undefined8 *)(puVar13 + 8);
      *(undefined8 *)(lVar14 + 0x50) = *(undefined8 *)(puVar13 + 0xc);
      if (*(uint **)(puVar13 + 0x10) != (uint *)0x0) {
        **(uint **)(puVar13 + 0x10) = (uint)uVar3;
      }
      puVar13 = puVar13 + 0x14;
    } while (puVar13 < param_2 + (long)(param_3 + -1) * 0x14);
  }
  uVar2 = 0;
  if (*(int *)(param_1 + 0x124) + 1U < *(uint *)(param_1 + 0x128)) {
    uVar2 = *(int *)(param_1 + 0x124) + 1;
  }
  if (uVar2 == *(uint *)(param_1 + 0x120)) {
code_r0x0205de4c:
    *(undefined1 *)(param_1 + 0x1b0) = 1;
    Aska::Event::Reset() const(param_1 + 0x148);
    if (param_2 < puVar13) {
      do {
        lVar9 = *(long *)(param_1 + 0xa8);
        if (param_1 + 0xa0 != lVar9) {
          do {
            if (*(ushort *)(lVar9 + 0x18) == param_2[1]) {
              lVar14 = *(long *)(lVar9 + 8);
              lVar12 = *(long *)(lVar9 + 0x10);
              if (lVar14 != 0) {
                *(long *)(lVar14 + 0x10) = lVar12;
              }
              if (lVar12 != 0) {
                *(long *)(lVar12 + 8) = lVar14;
              }
              if (0 < *(int *)(param_1 + 0x110)) {
                *(int *)(param_1 + 0x110) = *(int *)(param_1 + 0x110) + -1;
              }
              *(long *)(lVar9 + 8) = 0;
              *(undefined8 *)(lVar9 + 0x10) = 0;
              break;
            }
            lVar9 = *(long *)(lVar9 + 8);
          } while (param_1 + 0xa0 != lVar9);
        }
        param_2 = param_2 + 0x14;
      } while (param_2 < puVar13);
    }
    DataMemoryBarrier(2,3);
    *(undefined4 *)(param_1 + 0x40) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar10 = (int *)(param_1 + 0x44);
    if (0x14 < *piVar10) {
      do {
        cVar5 = '\x01';
        bVar6 = (bool)ExclusiveMonitorPass(piVar10,0x10);
        if (bVar6) {
          *piVar10 = *piVar10 + -1;
          cVar5 = ExclusiveMonitorsStatus();
        }
      } while (cVar5 != '\0');
      uVar7 = Aska::Semaphore::IsReady() const(param_1 + 0x80);
      if ((uVar7 & 1) != 0) {
        Aska::Semaphore::Signal() const(param_1 + 0x80);
      }
    }
    return 0;
  }
  *(uint *)(param_1 + 0x124) = uVar2;
  lVar9 = *(long *)(param_1 + 0xa8);
  lVar14 = *(long *)(*(long *)(param_1 + 0x130) + (ulong)uVar2 * 8);
  do {
    if (param_1 + 0xa0 == lVar9) {
      lVar9 = *(long *)(param_1 + 0xb0);
      *(long *)(lVar14 + 8) = param_1 + 0xa0;
      *(long *)(lVar14 + 0x10) = lVar9;
      *(long *)(lVar9 + 8) = lVar14;
      *(long *)(param_1 + 0xb0) = lVar14;
code_r0x0205df78:
      *(int *)(param_1 + 0x110) = *(int *)(param_1 + 0x110) + 1;
      *(char *)(lVar14 + 0x68) = param_5;
      memset(lVar14 + 0x18,0,0x50);
      *puVar13 = *puVar13 & 0x3fff;
      sVar4 = *(short *)(param_1 + 0x1ca);
      *(short *)(param_1 + 0x1ca) = sVar4 + 1;
      *(short *)(lVar14 + 0x18) = sVar4;
      *(ushort *)(lVar14 + 0x1a) = *puVar13 | 0x4000;
      uVar11 = *(undefined8 *)(puVar13 + 4);
      *(int **)(lVar14 + 0x40) = param_4;
      *(undefined8 *)(lVar14 + 0x20) = uVar11;
      *(undefined8 *)(lVar14 + 0x48) = *(undefined8 *)(puVar13 + 8);
      *(undefined8 *)(lVar14 + 0x50) = *(undefined8 *)(puVar13 + 0xc);
      if (param_4 != (int *)0x0) {
        *param_4 = param_3;
      }
      DataMemoryBarrier(2,3);
      *(undefined4 *)(param_1 + 0x40) = 0xffffffff;
      DataMemoryBarrier(2,3);
      piVar10 = (int *)(param_1 + 0x44);
      if (0x14 < *piVar10) {
        do {
          cVar5 = '\x01';
          bVar6 = (bool)ExclusiveMonitorPass(piVar10,0x10);
          if (bVar6) {
            *piVar10 = *piVar10 + -1;
            cVar5 = ExclusiveMonitorsStatus();
          }
        } while (cVar5 != '\0');
        uVar7 = Aska::Semaphore::IsReady() const(param_1 + 0x80);
        if ((uVar7 & 1) != 0) {
          Aska::Semaphore::Signal() const(param_1 + 0x80);
        }
      }
      uVar7 = (ulong)*(uint *)(param_1 + 0x1b8);
      if (0 < (int)*(uint *)(param_1 + 0x1b8)) {
        lVar9 = 0x84;
        do {
          if (*(char *)(*(long *)(param_1 + 0x1c0) + lVar9) != '\0') {
            Aska::Event::Set() const(*(long *)(param_1 + 0x1c0) + lVar9 + -0x6c);
          }
          uVar7 = uVar7 - 1;
          lVar9 = lVar9 + 0xe0;
        } while (uVar7 != 0);
      }
      return 1;
    }
    if (param_5 <= *(char *)(lVar9 + 0x68)) {
      lVar12 = *(long *)(lVar9 + 0x10);
      *(long *)(lVar14 + 8) = lVar9;
      *(long *)(lVar14 + 0x10) = lVar12;
      *(long *)(lVar12 + 8) = lVar14;
      *(long *)(lVar9 + 0x10) = lVar14;
      goto code_r0x0205df78;
    }
    lVar9 = *(long *)(lVar9 + 8);
  } while( true );
}

// ==== Aska::SimpleMessageDispatcher::PostSyncMessages(Aska::SimpleMessageDispatcher::ArgumentEx*, int, int*, signed char)
// vaddr 0x1f5e07c | ghidra 0x205e07c | size 1148 | symbol _ZN4Aska23SimpleMessageDispatcher16PostSyncMessagesEPNS0_10ArgumentExEiPia | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska23SimpleMessageDispatcher16PostSyncMessagesEPNS0_10ArgumentExEiPia
          (long param_1,ushort *param_2,int param_3,int *param_4,char param_5)

{
  int *piVar1;
  uint uVar2;
  ushort uVar3;
  short sVar4;
  char cVar5;
  bool bVar6;
  ulong uVar7;
  int iVar8;
  long lVar9;
  int *piVar10;
  undefined8 uVar11;
  long lVar12;
  ushort *puVar13;
  long lVar14;
  
  piVar10 = (int *)(param_1 + 0x40);
  iVar8 = 0;
code_r0x0205e0ac:
  if (*piVar10 == -1) {
    cVar5 = '\x01';
    bVar6 = (bool)ExclusiveMonitorPass(piVar10,0x10);
    if (bVar6) {
      *piVar10 = 0;
      cVar5 = ExclusiveMonitorsStatus();
    }
    if (cVar5 == '\0') goto code_r0x0205e174;
    goto code_r0x0205e0ac;
  }
  ClearExclusiveLocal();
  bVar6 = iVar8 < 0x1ff;
  iVar8 = iVar8 + 1;
  if (bVar6) goto code_r0x0205e0ac;
  piVar1 = (int *)(param_1 + 0x44);
  do {
    cVar5 = '\x01';
    bVar6 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar6) {
      *piVar1 = *piVar1 + 1;
      cVar5 = ExclusiveMonitorsStatus();
    }
  } while (cVar5 != '\0');
  do {
    if (*piVar10 != -1) {
      ClearExclusiveLocal();
      do {
        uVar7 = Aska::Semaphore::IsReady() const(param_1 + 0x80);
        if ((uVar7 & 1) == 0) {
          do {
            cVar5 = '\x01';
            bVar6 = (bool)ExclusiveMonitorPass(piVar1,0x10);
            if (bVar6) {
              *piVar1 = *piVar1 + -1;
              cVar5 = ExclusiveMonitorsStatus();
            }
          } while (cVar5 != '\0');
          Aska::Thread::Sleep(unsigned int)(1);
        }
        else {
          Aska::Semaphore::Wait() const(param_1 + 0x80);
        }
        do {
          cVar5 = '\x01';
          bVar6 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar6) {
            *piVar1 = *piVar1 + 1;
            cVar5 = ExclusiveMonitorsStatus();
          }
        } while (cVar5 != '\0');
        while (*piVar10 == -1) {
          cVar5 = '\x01';
          bVar6 = (bool)ExclusiveMonitorPass(piVar10,0x10);
          if (bVar6) {
            *piVar10 = 0;
            cVar5 = ExclusiveMonitorsStatus();
          }
          if (cVar5 == '\0') goto code_r0x0205e164;
        }
        ClearExclusiveLocal();
      } while( true );
    }
    cVar5 = '\x01';
    bVar6 = (bool)ExclusiveMonitorPass(piVar10,0x10);
    if (bVar6) {
      *piVar10 = 0;
      cVar5 = ExclusiveMonitorsStatus();
    }
  } while (cVar5 != '\0');
code_r0x0205e164:
  do {
    cVar5 = '\x01';
    bVar6 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar6) {
      *piVar1 = *piVar1 + -1;
      cVar5 = ExclusiveMonitorsStatus();
    }
  } while (cVar5 != '\0');
code_r0x0205e174:
  DataMemoryBarrier(2,3);
  puVar13 = param_2;
  if (0 < param_3) {
    do {
      *puVar13 = *puVar13 & 0x3fff;
      uVar2 = 0;
      if (*(int *)(param_1 + 0x124) + 1U < *(uint *)(param_1 + 0x128)) {
        uVar2 = *(int *)(param_1 + 0x124) + 1;
      }
      if (uVar2 == *(uint *)(param_1 + 0x120)) goto code_r0x0205e2b8;
      *(uint *)(param_1 + 0x124) = uVar2;
      lVar14 = *(long *)(*(long *)(param_1 + 0x130) + (ulong)uVar2 * 8);
      for (lVar9 = *(long *)(param_1 + 0xa8); param_1 + 0xa0 != lVar9; lVar9 = *(long *)(lVar9 + 8))
      {
        if (param_5 <= *(char *)(lVar9 + 0x68)) {
          lVar12 = *(long *)(lVar9 + 0x10);
          *(long *)(lVar14 + 8) = lVar9;
          *(long *)(lVar14 + 0x10) = lVar12;
          *(long *)(lVar12 + 8) = lVar14;
          *(long *)(lVar9 + 0x10) = lVar14;
          goto code_r0x0205e218;
        }
      }
      lVar9 = *(long *)(param_1 + 0xb0);
      *(long *)(lVar14 + 8) = param_1 + 0xa0;
      *(long *)(lVar14 + 0x10) = lVar9;
      *(long *)(lVar9 + 8) = lVar14;
      *(long *)(param_1 + 0xb0) = lVar14;
code_r0x0205e218:
      *(int *)(param_1 + 0x110) = *(int *)(param_1 + 0x110) + 1;
      *(char *)(lVar14 + 0x68) = param_5;
      memset(lVar14 + 0x18,0,0x50);
      uVar3 = *(ushort *)(param_1 + 0x1ca);
      *(ushort *)(param_1 + 0x1ca) = uVar3 + 1;
      puVar13[1] = uVar3;
      *(ushort *)(lVar14 + 0x18) = uVar3;
      *(ushort *)(lVar14 + 0x1a) = *puVar13;
      uVar11 = *(undefined8 *)(puVar13 + 4);
      *(int **)(lVar14 + 0x40) = param_4;
      *(undefined8 *)(lVar14 + 0x20) = uVar11;
      *(undefined8 *)(lVar14 + 0x48) = *(undefined8 *)(puVar13 + 8);
      *(undefined8 *)(lVar14 + 0x50) = *(undefined8 *)(puVar13 + 0xc);
      *(undefined8 *)(lVar14 + 0x58) = *(undefined8 *)(puVar13 + 0x14);
      *(undefined8 *)(lVar14 + 0x60) = *(undefined8 *)(puVar13 + 0x18);
      if (*(uint **)(puVar13 + 0x10) != (uint *)0x0) {
        **(uint **)(puVar13 + 0x10) = (uint)uVar3;
      }
      puVar13 = puVar13 + 0x1c;
    } while (puVar13 < param_2 + (long)param_3 * 0x1c);
  }
  uVar2 = 0;
  if (*(int *)(param_1 + 0x124) + 1U < *(uint *)(param_1 + 0x128)) {
    uVar2 = *(int *)(param_1 + 0x124) + 1;
  }
  if (uVar2 == *(uint *)(param_1 + 0x120)) {
code_r0x0205e2b8:
    *(undefined1 *)(param_1 + 0x1b0) = 1;
    Aska::Event::Reset() const(param_1 + 0x148);
    if (param_2 < puVar13) {
      do {
        lVar9 = *(long *)(param_1 + 0xa8);
        if (param_1 + 0xa0 != lVar9) {
          do {
            if (*(ushort *)(lVar9 + 0x18) == param_2[1]) {
              lVar14 = *(long *)(lVar9 + 8);
              lVar12 = *(long *)(lVar9 + 0x10);
              if (lVar14 != 0) {
                *(long *)(lVar14 + 0x10) = lVar12;
              }
              if (lVar12 != 0) {
                *(long *)(lVar12 + 8) = lVar14;
              }
              if (0 < *(int *)(param_1 + 0x110)) {
                *(int *)(param_1 + 0x110) = *(int *)(param_1 + 0x110) + -1;
              }
              *(long *)(lVar9 + 8) = 0;
              *(undefined8 *)(lVar9 + 0x10) = 0;
              break;
            }
            lVar9 = *(long *)(lVar9 + 8);
          } while (param_1 + 0xa0 != lVar9);
        }
        param_2 = param_2 + 0x1c;
      } while (param_2 < puVar13);
    }
    DataMemoryBarrier(2,3);
    *(undefined4 *)(param_1 + 0x40) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar10 = (int *)(param_1 + 0x44);
    if (0x14 < *piVar10) {
      do {
        cVar5 = '\x01';
        bVar6 = (bool)ExclusiveMonitorPass(piVar10,0x10);
        if (bVar6) {
          *piVar10 = *piVar10 + -1;
          cVar5 = ExclusiveMonitorsStatus();
        }
      } while (cVar5 != '\0');
      uVar7 = Aska::Semaphore::IsReady() const(param_1 + 0x80);
      if ((uVar7 & 1) != 0) {
        Aska::Semaphore::Signal() const(param_1 + 0x80);
      }
    }
    return 0;
  }
  *(uint *)(param_1 + 0x124) = uVar2;
  lVar9 = *(long *)(param_1 + 0xa8);
  lVar14 = *(long *)(*(long *)(param_1 + 0x130) + (ulong)uVar2 * 8);
  do {
    if (param_1 + 0xa0 == lVar9) {
      lVar9 = *(long *)(param_1 + 0xb0);
      *(long *)(lVar14 + 8) = param_1 + 0xa0;
      *(long *)(lVar14 + 0x10) = lVar9;
      *(long *)(lVar9 + 8) = lVar14;
      *(long *)(param_1 + 0xb0) = lVar14;
code_r0x0205e3e4:
      *(int *)(param_1 + 0x110) = *(int *)(param_1 + 0x110) + 1;
      *(char *)(lVar14 + 0x68) = param_5;
      memset(lVar14 + 0x18,0,0x50);
      *puVar13 = *puVar13 & 0x3fff;
      sVar4 = *(short *)(param_1 + 0x1ca);
      *(short *)(param_1 + 0x1ca) = sVar4 + 1;
      *(short *)(lVar14 + 0x18) = sVar4;
      *(ushort *)(lVar14 + 0x1a) = *puVar13 | 0x4000;
      uVar11 = *(undefined8 *)(puVar13 + 4);
      *(int **)(lVar14 + 0x40) = param_4;
      *(undefined8 *)(lVar14 + 0x20) = uVar11;
      *(undefined8 *)(lVar14 + 0x48) = *(undefined8 *)(puVar13 + 8);
      *(undefined8 *)(lVar14 + 0x50) = *(undefined8 *)(puVar13 + 0xc);
      *(undefined8 *)(lVar14 + 0x58) = *(undefined8 *)(puVar13 + 0x14);
      *(undefined8 *)(lVar14 + 0x60) = *(undefined8 *)(puVar13 + 0x18);
      if (param_4 != (int *)0x0) {
        *param_4 = param_3;
      }
      DataMemoryBarrier(2,3);
      *(undefined4 *)(param_1 + 0x40) = 0xffffffff;
      DataMemoryBarrier(2,3);
      piVar10 = (int *)(param_1 + 0x44);
      if (0x14 < *piVar10) {
        do {
          cVar5 = '\x01';
          bVar6 = (bool)ExclusiveMonitorPass(piVar10,0x10);
          if (bVar6) {
            *piVar10 = *piVar10 + -1;
            cVar5 = ExclusiveMonitorsStatus();
          }
        } while (cVar5 != '\0');
        uVar7 = Aska::Semaphore::IsReady() const(param_1 + 0x80);
        if ((uVar7 & 1) != 0) {
          Aska::Semaphore::Signal() const(param_1 + 0x80);
        }
      }
      uVar7 = (ulong)*(uint *)(param_1 + 0x1b8);
      if (0 < (int)*(uint *)(param_1 + 0x1b8)) {
        lVar9 = 0x84;
        do {
          if (*(char *)(*(long *)(param_1 + 0x1c0) + lVar9) != '\0') {
            Aska::Event::Set() const(*(long *)(param_1 + 0x1c0) + lVar9 + -0x6c);
          }
          uVar7 = uVar7 - 1;
          lVar9 = lVar9 + 0xe0;
        } while (uVar7 != 0);
      }
      return 1;
    }
    if (param_5 <= *(char *)(lVar9 + 0x68)) {
      lVar12 = *(long *)(lVar9 + 0x10);
      *(long *)(lVar14 + 8) = lVar9;
      *(long *)(lVar14 + 0x10) = lVar12;
      *(long *)(lVar12 + 8) = lVar14;
      *(long *)(lVar9 + 0x10) = lVar14;
      goto code_r0x0205e3e4;
    }
    lVar9 = *(long *)(lVar9 + 8);
  } while( true );
}

// ==== Aska::SimpleMessageDispatcher::PostSyncMessageSingle(unsigned short, int*, Aska::INotify*, void*, void*, unsigned int*, signed char)
// vaddr 0x1f5e4f8 | ghidra 0x205e4f8 | size 760 | symbol _ZN4Aska23SimpleMessageDispatcher21PostSyncMessageSingleEtPiPNS_7INotifyEPvS4_Pja | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska23SimpleMessageDispatcher21PostSyncMessageSingleEtPiPNS_7INotifyEPvS4_Pja
          (long param_1,ushort param_2,undefined8 param_3,undefined8 param_4,undefined8 param_5,
          undefined8 param_6,uint *param_7,char param_8)

{
  int *piVar1;
  uint uVar2;
  ushort uVar3;
  char cVar4;
  bool bVar5;
  ulong uVar6;
  int iVar7;
  int *piVar8;
  long lVar9;
  long lVar10;
  long lVar11;
  
  piVar8 = (int *)(param_1 + 0x40);
  iVar7 = 0;
code_r0x0205e538:
  if (*piVar8 == -1) {
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar8,0x10);
    if (bVar5) {
      *piVar8 = 0;
      cVar4 = ExclusiveMonitorsStatus();
    }
    if (cVar4 == '\0') goto code_r0x0205e600;
    goto code_r0x0205e538;
  }
  ClearExclusiveLocal();
  bVar5 = iVar7 < 0x1ff;
  iVar7 = iVar7 + 1;
  if (bVar5) goto code_r0x0205e538;
  piVar1 = (int *)(param_1 + 0x44);
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
        uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x80);
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
          Aska::Semaphore::Wait() const(param_1 + 0x80);
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
          if (cVar4 == '\0') goto code_r0x0205e5f0;
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
code_r0x0205e5f0:
  do {
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar5) {
      *piVar1 = *piVar1 + -1;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
code_r0x0205e600:
  DataMemoryBarrier(2,3);
  uVar2 = 0;
  if (*(int *)(param_1 + 0x124) + 1U < *(uint *)(param_1 + 0x128)) {
    uVar2 = *(int *)(param_1 + 0x124) + 1;
  }
  if (uVar2 == *(uint *)(param_1 + 0x120)) {
    *(undefined1 *)(param_1 + 0x1b0) = 1;
    Aska::Event::Reset() const(param_1 + 0x148);
    DataMemoryBarrier(2,3);
    *(undefined4 *)(param_1 + 0x40) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar8 = (int *)(param_1 + 0x44);
    if (0x14 < *piVar8) {
      do {
        cVar4 = '\x01';
        bVar5 = (bool)ExclusiveMonitorPass(piVar8,0x10);
        if (bVar5) {
          *piVar8 = *piVar8 + -1;
          cVar4 = ExclusiveMonitorsStatus();
        }
      } while (cVar4 != '\0');
      uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x80);
      if ((uVar6 & 1) != 0) {
        Aska::Semaphore::Signal() const(param_1 + 0x80);
      }
    }
    return 0;
  }
  *(uint *)(param_1 + 0x124) = uVar2;
  lVar9 = *(long *)(param_1 + 0xa8);
  lVar11 = *(long *)(*(long *)(param_1 + 0x130) + (ulong)uVar2 * 8);
  do {
    if (param_1 + 0xa0 == lVar9) {
      lVar9 = *(long *)(param_1 + 0xb0);
      *(long *)(lVar11 + 8) = param_1 + 0xa0;
      *(long *)(lVar11 + 0x10) = lVar9;
      *(long *)(lVar9 + 8) = lVar11;
      *(long *)(param_1 + 0xb0) = lVar11;
code_r0x0205e6e0:
      *(int *)(param_1 + 0x110) = *(int *)(param_1 + 0x110) + 1;
      *(char *)(lVar11 + 0x68) = param_8;
      memset(lVar11 + 0x18,0,0x50);
      uVar3 = *(ushort *)(param_1 + 0x1ca);
      *(ushort *)(param_1 + 0x1ca) = uVar3 + 1;
      *(ushort *)(lVar11 + 0x18) = uVar3;
      *(ushort *)(lVar11 + 0x1a) = param_2 & 0x3fff;
      *(undefined8 *)(lVar11 + 0x20) = param_4;
      *(undefined8 *)(lVar11 + 0x40) = param_3;
      *(undefined8 *)(lVar11 + 0x48) = param_5;
      *(undefined8 *)(lVar11 + 0x50) = param_6;
      if (param_7 != (uint *)0x0) {
        *param_7 = (uint)uVar3;
      }
      DataMemoryBarrier(2,3);
      *(undefined4 *)(param_1 + 0x40) = 0xffffffff;
      DataMemoryBarrier(2,3);
      piVar8 = (int *)(param_1 + 0x44);
      if (0x14 < *piVar8) {
        do {
          cVar4 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(piVar8,0x10);
          if (bVar5) {
            *piVar8 = *piVar8 + -1;
            cVar4 = ExclusiveMonitorsStatus();
          }
        } while (cVar4 != '\0');
        uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x80);
        if ((uVar6 & 1) != 0) {
          Aska::Semaphore::Signal() const(param_1 + 0x80);
        }
      }
      iVar7 = *(int *)(param_1 + 0x1b8);
      if (0 < iVar7) {
        lVar11 = 0;
        lVar9 = 0;
        do {
          lVar10 = *(long *)(param_1 + 0x1c0) + lVar11;
          if ((*(char *)(lVar10 + 0x84) != '\0') && (*(char *)(lVar10 + 0x83) == '\0')) {
            lVar10 = *(long *)(param_1 + 0x1c0) + lVar11 + 0x18;
            uVar6 = Aska::Event::IsSignal() const(lVar10);
            if ((uVar6 & 1) == 0) {
              Aska::Event::Set() const(lVar10);
              return 1;
            }
          }
          lVar9 = lVar9 + 1;
          lVar11 = lVar11 + 0xe0;
        } while (lVar9 < iVar7);
      }
      return 1;
    }
    if (param_8 <= *(char *)(lVar9 + 0x68)) {
      lVar10 = *(long *)(lVar9 + 0x10);
      *(long *)(lVar11 + 8) = lVar9;
      *(long *)(lVar11 + 0x10) = lVar10;
      *(long *)(lVar10 + 8) = lVar11;
      *(long *)(lVar9 + 0x10) = lVar11;
      goto code_r0x0205e6e0;
    }
    lVar9 = *(long *)(lVar9 + 8);
  } while( true );
}

// ==== Aska::SimpleMessageDispatcher::PostSyncMessageSingle(unsigned short, int*, Aska::INotify*, void*, void*, unsigned long, unsigned long, unsigned int*, signed char)
// vaddr 0x1f5e7f0 | ghidra 0x205e7f0 | size 808 | symbol _ZN4Aska23SimpleMessageDispatcher21PostSyncMessageSingleEtPiPNS_7INotifyEPvS4_mmPja | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska23SimpleMessageDispatcher21PostSyncMessageSingleEtPiPNS_7INotifyEPvS4_mmPja
          (long param_1,ushort param_2,undefined8 param_3,undefined8 param_4,undefined8 param_5,
          undefined8 param_6,undefined8 param_7,undefined8 param_8,uint *param_9,char param_10)

{
  int *piVar1;
  uint uVar2;
  ushort uVar3;
  char cVar4;
  bool bVar5;
  ulong uVar6;
  undefined8 uVar7;
  int iVar8;
  int *piVar9;
  long lVar10;
  long lVar11;
  long lVar12;
  
  piVar9 = (int *)(param_1 + 0x40);
  iVar8 = 0;
code_r0x0205e838:
  do {
    if (*piVar9 == -1) goto code_r0x0205e844;
    ClearExclusiveLocal();
    bVar5 = iVar8 < 0x1ff;
    iVar8 = iVar8 + 1;
  } while (bVar5);
  piVar1 = (int *)(param_1 + 0x44);
  do {
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar5) {
      *piVar1 = *piVar1 + 1;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
  do {
    if (*piVar9 != -1) {
      ClearExclusiveLocal();
      uVar6 = Aska::Semaphore::IsReady() const();
      if ((uVar6 & 1) == 0) goto code_r0x0205eac0;
      do {
        Aska::Semaphore::Wait() const(param_1 + 0x80);
        while( true ) {
          do {
            cVar4 = '\x01';
            bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
            if (bVar5) {
              *piVar1 = *piVar1 + 1;
              cVar4 = ExclusiveMonitorsStatus();
            }
          } while (cVar4 != '\0');
          while (*piVar9 == -1) {
            cVar4 = '\x01';
            bVar5 = (bool)ExclusiveMonitorPass(piVar9,0x10);
            if (bVar5) {
              *piVar9 = 0;
              cVar4 = ExclusiveMonitorsStatus();
            }
            if (cVar4 == '\0') goto code_r0x0205eafc;
          }
          ClearExclusiveLocal();
          uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x80);
          if ((uVar6 & 1) != 0) break;
code_r0x0205eac0:
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
      } while( true );
    }
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar9,0x10);
    if (bVar5) {
      *piVar9 = 0;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
code_r0x0205eafc:
  do {
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar5) {
      *piVar1 = *piVar1 + -1;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
  DataMemoryBarrier(2,3);
  goto code_r0x0205e894;
code_r0x0205e844:
  cVar4 = '\x01';
  bVar5 = (bool)ExclusiveMonitorPass(piVar9,0x10);
  if (bVar5) {
    *piVar9 = 0;
    cVar4 = ExclusiveMonitorsStatus();
  }
  if (cVar4 == '\0') goto code_r0x0205e890;
  goto code_r0x0205e838;
code_r0x0205e890:
  DataMemoryBarrier(2,3);
code_r0x0205e894:
  uVar2 = 0;
  if (*(int *)(param_1 + 0x124) + 1U < *(uint *)(param_1 + 0x128)) {
    uVar2 = *(int *)(param_1 + 0x124) + 1;
  }
  if (uVar2 == *(uint *)(param_1 + 0x120)) {
    *(undefined1 *)(param_1 + 0x1b0) = 1;
    Aska::Event::Reset() const(param_1 + 0x148);
    DataMemoryBarrier(2,3);
    *(undefined4 *)(param_1 + 0x40) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar9 = (int *)(param_1 + 0x44);
    if (0x14 < *piVar9) {
      do {
        cVar4 = '\x01';
        bVar5 = (bool)ExclusiveMonitorPass(piVar9,0x10);
        if (bVar5) {
          *piVar9 = *piVar9 + -1;
          cVar4 = ExclusiveMonitorsStatus();
        }
      } while (cVar4 != '\0');
      uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x80);
      if ((uVar6 & 1) != 0) {
        Aska::Semaphore::Signal() const(param_1 + 0x80);
      }
    }
    uVar7 = 0;
  }
  else {
    *(uint *)(param_1 + 0x124) = uVar2;
    lVar12 = *(long *)(*(long *)(param_1 + 0x130) + (ulong)uVar2 * 8);
    for (lVar10 = *(long *)(param_1 + 0xa8); param_1 + 0xa0 != lVar10;
        lVar10 = *(long *)(lVar10 + 8)) {
      if (param_10 <= *(char *)(lVar10 + 0x68)) {
        lVar11 = *(long *)(lVar10 + 0x10);
        *(long *)(lVar12 + 8) = lVar10;
        *(long *)(lVar12 + 0x10) = lVar11;
        *(long *)(lVar11 + 8) = lVar12;
        *(long *)(lVar10 + 0x10) = lVar12;
        goto code_r0x0205e974;
      }
    }
    lVar10 = *(long *)(param_1 + 0xb0);
    *(long *)(lVar12 + 8) = param_1 + 0xa0;
    *(long *)(lVar12 + 0x10) = lVar10;
    *(long *)(lVar10 + 8) = lVar12;
    *(long *)(param_1 + 0xb0) = lVar12;
code_r0x0205e974:
    *(int *)(param_1 + 0x110) = *(int *)(param_1 + 0x110) + 1;
    *(char *)(lVar12 + 0x68) = param_10;
    memset(lVar12 + 0x18,0,0x50);
    uVar3 = *(ushort *)(param_1 + 0x1ca);
    *(ushort *)(param_1 + 0x1ca) = uVar3 + 1;
    *(ushort *)(lVar12 + 0x18) = uVar3;
    *(ushort *)(lVar12 + 0x1a) = param_2 & 0x3fff;
    *(undefined8 *)(lVar12 + 0x20) = param_4;
    *(undefined8 *)(lVar12 + 0x40) = param_3;
    *(undefined8 *)(lVar12 + 0x48) = param_5;
    *(undefined8 *)(lVar12 + 0x50) = param_6;
    *(undefined8 *)(lVar12 + 0x58) = param_7;
    *(undefined8 *)(lVar12 + 0x60) = param_8;
    if (param_9 != (uint *)0x0) {
      *param_9 = (uint)uVar3;
    }
    DataMemoryBarrier(2,3);
    *(undefined4 *)(param_1 + 0x40) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar9 = (int *)(param_1 + 0x44);
    if (0x14 < *piVar9) {
      do {
        cVar4 = '\x01';
        bVar5 = (bool)ExclusiveMonitorPass(piVar9,0x10);
        if (bVar5) {
          *piVar9 = *piVar9 + -1;
          cVar4 = ExclusiveMonitorsStatus();
        }
      } while (cVar4 != '\0');
      uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x80);
      if ((uVar6 & 1) != 0) {
        Aska::Semaphore::Signal() const(param_1 + 0x80);
      }
    }
    iVar8 = *(int *)(param_1 + 0x1b8);
    if (0 < iVar8) {
      lVar12 = 0;
      lVar10 = 0;
      do {
        lVar11 = *(long *)(param_1 + 0x1c0) + lVar12;
        if ((*(char *)(lVar11 + 0x84) != '\0') && (*(char *)(lVar11 + 0x83) == '\0')) {
          lVar11 = *(long *)(param_1 + 0x1c0) + lVar12 + 0x18;
          uVar6 = Aska::Event::IsSignal() const(lVar11);
          if ((uVar6 & 1) == 0) {
            Aska::Event::Set() const(lVar11);
            break;
          }
        }
        lVar10 = lVar10 + 1;
        lVar12 = lVar12 + 0xe0;
      } while (lVar10 < iVar8);
    }
    uVar7 = 1;
  }
  return uVar7;
}

// ==== Aska::SimpleMessageDispatcher::PostSyncMessageEnd(unsigned short, int*, Aska::INotify*, void*, void*, unsigned int*, signed char)
// vaddr 0x1f5eb18 | ghidra 0x205eb18 | size 764 | symbol _ZN4Aska23SimpleMessageDispatcher18PostSyncMessageEndEtPiPNS_7INotifyEPvS4_Pja | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska23SimpleMessageDispatcher18PostSyncMessageEndEtPiPNS_7INotifyEPvS4_Pja
          (long param_1,ushort param_2,undefined8 param_3,undefined8 param_4,undefined8 param_5,
          undefined8 param_6,uint *param_7,char param_8)

{
  int *piVar1;
  uint uVar2;
  ushort uVar3;
  char cVar4;
  bool bVar5;
  ulong uVar6;
  int iVar7;
  int *piVar8;
  long lVar9;
  long lVar10;
  long lVar11;
  
  piVar8 = (int *)(param_1 + 0x40);
  iVar7 = 0;
code_r0x0205eb58:
  if (*piVar8 == -1) {
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar8,0x10);
    if (bVar5) {
      *piVar8 = 0;
      cVar4 = ExclusiveMonitorsStatus();
    }
    if (cVar4 == '\0') goto code_r0x0205ec20;
    goto code_r0x0205eb58;
  }
  ClearExclusiveLocal();
  bVar5 = iVar7 < 0x1ff;
  iVar7 = iVar7 + 1;
  if (bVar5) goto code_r0x0205eb58;
  piVar1 = (int *)(param_1 + 0x44);
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
        uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x80);
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
          Aska::Semaphore::Wait() const(param_1 + 0x80);
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
          if (cVar4 == '\0') goto code_r0x0205ec10;
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
code_r0x0205ec10:
  do {
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar5) {
      *piVar1 = *piVar1 + -1;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
code_r0x0205ec20:
  DataMemoryBarrier(2,3);
  uVar2 = 0;
  if (*(int *)(param_1 + 0x124) + 1U < *(uint *)(param_1 + 0x128)) {
    uVar2 = *(int *)(param_1 + 0x124) + 1;
  }
  if (uVar2 == *(uint *)(param_1 + 0x120)) {
    *(undefined1 *)(param_1 + 0x1b0) = 1;
    Aska::Event::Reset() const(param_1 + 0x148);
    DataMemoryBarrier(2,3);
    *(undefined4 *)(param_1 + 0x40) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar8 = (int *)(param_1 + 0x44);
    if (0x14 < *piVar8) {
      do {
        cVar4 = '\x01';
        bVar5 = (bool)ExclusiveMonitorPass(piVar8,0x10);
        if (bVar5) {
          *piVar8 = *piVar8 + -1;
          cVar4 = ExclusiveMonitorsStatus();
        }
      } while (cVar4 != '\0');
      uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x80);
      if ((uVar6 & 1) != 0) {
        Aska::Semaphore::Signal() const(param_1 + 0x80);
      }
    }
    return 0;
  }
  *(uint *)(param_1 + 0x124) = uVar2;
  lVar9 = *(long *)(param_1 + 0xa8);
  lVar11 = *(long *)(*(long *)(param_1 + 0x130) + (ulong)uVar2 * 8);
  do {
    if (param_1 + 0xa0 == lVar9) {
      lVar9 = *(long *)(param_1 + 0xb0);
      *(long *)(lVar11 + 8) = param_1 + 0xa0;
      *(long *)(lVar11 + 0x10) = lVar9;
      *(long *)(lVar9 + 8) = lVar11;
      *(long *)(param_1 + 0xb0) = lVar11;
code_r0x0205ed00:
      *(int *)(param_1 + 0x110) = *(int *)(param_1 + 0x110) + 1;
      *(char *)(lVar11 + 0x68) = param_8;
      memset(lVar11 + 0x18,0,0x50);
      uVar3 = *(ushort *)(param_1 + 0x1ca);
      *(ushort *)(param_1 + 0x1ca) = uVar3 + 1;
      *(ushort *)(lVar11 + 0x18) = uVar3;
      *(ushort *)(lVar11 + 0x1a) = param_2 & 0x3fff | 0x4000;
      *(undefined8 *)(lVar11 + 0x20) = param_4;
      *(undefined8 *)(lVar11 + 0x40) = param_3;
      *(undefined8 *)(lVar11 + 0x48) = param_5;
      *(undefined8 *)(lVar11 + 0x50) = param_6;
      if (param_7 != (uint *)0x0) {
        *param_7 = (uint)uVar3;
      }
      DataMemoryBarrier(2,3);
      *(undefined4 *)(param_1 + 0x40) = 0xffffffff;
      DataMemoryBarrier(2,3);
      piVar8 = (int *)(param_1 + 0x44);
      if (0x14 < *piVar8) {
        do {
          cVar4 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(piVar8,0x10);
          if (bVar5) {
            *piVar8 = *piVar8 + -1;
            cVar4 = ExclusiveMonitorsStatus();
          }
        } while (cVar4 != '\0');
        uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x80);
        if ((uVar6 & 1) != 0) {
          Aska::Semaphore::Signal() const(param_1 + 0x80);
        }
      }
      iVar7 = *(int *)(param_1 + 0x1b8);
      if (0 < iVar7) {
        lVar11 = 0;
        lVar9 = 0;
        do {
          lVar10 = *(long *)(param_1 + 0x1c0) + lVar11;
          if ((*(char *)(lVar10 + 0x84) != '\0') && (*(char *)(lVar10 + 0x83) == '\0')) {
            lVar10 = *(long *)(param_1 + 0x1c0) + lVar11 + 0x18;
            uVar6 = Aska::Event::IsSignal() const(lVar10);
            if ((uVar6 & 1) == 0) {
              Aska::Event::Set() const(lVar10);
              return 1;
            }
          }
          lVar9 = lVar9 + 1;
          lVar11 = lVar11 + 0xe0;
        } while (lVar9 < iVar7);
      }
      return 1;
    }
    if (param_8 <= *(char *)(lVar9 + 0x68)) {
      lVar10 = *(long *)(lVar9 + 0x10);
      *(long *)(lVar11 + 8) = lVar9;
      *(long *)(lVar11 + 0x10) = lVar10;
      *(long *)(lVar10 + 8) = lVar11;
      *(long *)(lVar9 + 0x10) = lVar11;
      goto code_r0x0205ed00;
    }
    lVar9 = *(long *)(lVar9 + 8);
  } while( true );
}

// ==== Aska::SimpleMessageDispatcher::PostSyncMessageEnd(unsigned short, int*, Aska::INotify*, void*, void*, unsigned long, unsigned long, unsigned int*, signed char)
// vaddr 0x1f5ee14 | ghidra 0x205ee14 | size 812 | symbol _ZN4Aska23SimpleMessageDispatcher18PostSyncMessageEndEtPiPNS_7INotifyEPvS4_mmPja | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska23SimpleMessageDispatcher18PostSyncMessageEndEtPiPNS_7INotifyEPvS4_mmPja
          (long param_1,ushort param_2,undefined8 param_3,undefined8 param_4,undefined8 param_5,
          undefined8 param_6,undefined8 param_7,undefined8 param_8,uint *param_9,char param_10)

{
  int *piVar1;
  uint uVar2;
  ushort uVar3;
  char cVar4;
  bool bVar5;
  ulong uVar6;
  undefined8 uVar7;
  int iVar8;
  int *piVar9;
  long lVar10;
  long lVar11;
  long lVar12;
  
  piVar9 = (int *)(param_1 + 0x40);
  iVar8 = 0;
code_r0x0205ee5c:
  do {
    if (*piVar9 == -1) goto code_r0x0205ee68;
    ClearExclusiveLocal();
    bVar5 = iVar8 < 0x1ff;
    iVar8 = iVar8 + 1;
  } while (bVar5);
  piVar1 = (int *)(param_1 + 0x44);
  do {
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar5) {
      *piVar1 = *piVar1 + 1;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
  do {
    if (*piVar9 != -1) {
      ClearExclusiveLocal();
      uVar6 = Aska::Semaphore::IsReady() const();
      if ((uVar6 & 1) == 0) goto code_r0x0205f0e8;
      do {
        Aska::Semaphore::Wait() const(param_1 + 0x80);
        while( true ) {
          do {
            cVar4 = '\x01';
            bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
            if (bVar5) {
              *piVar1 = *piVar1 + 1;
              cVar4 = ExclusiveMonitorsStatus();
            }
          } while (cVar4 != '\0');
          while (*piVar9 == -1) {
            cVar4 = '\x01';
            bVar5 = (bool)ExclusiveMonitorPass(piVar9,0x10);
            if (bVar5) {
              *piVar9 = 0;
              cVar4 = ExclusiveMonitorsStatus();
            }
            if (cVar4 == '\0') goto code_r0x0205f124;
          }
          ClearExclusiveLocal();
          uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x80);
          if ((uVar6 & 1) != 0) break;
code_r0x0205f0e8:
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
      } while( true );
    }
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar9,0x10);
    if (bVar5) {
      *piVar9 = 0;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
code_r0x0205f124:
  do {
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar5) {
      *piVar1 = *piVar1 + -1;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
  DataMemoryBarrier(2,3);
  goto code_r0x0205eeb8;
code_r0x0205ee68:
  cVar4 = '\x01';
  bVar5 = (bool)ExclusiveMonitorPass(piVar9,0x10);
  if (bVar5) {
    *piVar9 = 0;
    cVar4 = ExclusiveMonitorsStatus();
  }
  if (cVar4 == '\0') goto code_r0x0205eeb4;
  goto code_r0x0205ee5c;
code_r0x0205eeb4:
  DataMemoryBarrier(2,3);
code_r0x0205eeb8:
  uVar2 = 0;
  if (*(int *)(param_1 + 0x124) + 1U < *(uint *)(param_1 + 0x128)) {
    uVar2 = *(int *)(param_1 + 0x124) + 1;
  }
  if (uVar2 == *(uint *)(param_1 + 0x120)) {
    *(undefined1 *)(param_1 + 0x1b0) = 1;
    Aska::Event::Reset() const(param_1 + 0x148);
    DataMemoryBarrier(2,3);
    *(undefined4 *)(param_1 + 0x40) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar9 = (int *)(param_1 + 0x44);
    if (0x14 < *piVar9) {
      do {
        cVar4 = '\x01';
        bVar5 = (bool)ExclusiveMonitorPass(piVar9,0x10);
        if (bVar5) {
          *piVar9 = *piVar9 + -1;
          cVar4 = ExclusiveMonitorsStatus();
        }
      } while (cVar4 != '\0');
      uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x80);
      if ((uVar6 & 1) != 0) {
        Aska::Semaphore::Signal() const(param_1 + 0x80);
      }
    }
    uVar7 = 0;
  }
  else {
    *(uint *)(param_1 + 0x124) = uVar2;
    lVar12 = *(long *)(*(long *)(param_1 + 0x130) + (ulong)uVar2 * 8);
    for (lVar10 = *(long *)(param_1 + 0xa8); param_1 + 0xa0 != lVar10;
        lVar10 = *(long *)(lVar10 + 8)) {
      if (param_10 <= *(char *)(lVar10 + 0x68)) {
        lVar11 = *(long *)(lVar10 + 0x10);
        *(long *)(lVar12 + 8) = lVar10;
        *(long *)(lVar12 + 0x10) = lVar11;
        *(long *)(lVar11 + 8) = lVar12;
        *(long *)(lVar10 + 0x10) = lVar12;
        goto code_r0x0205ef98;
      }
    }
    lVar10 = *(long *)(param_1 + 0xb0);
    *(long *)(lVar12 + 8) = param_1 + 0xa0;
    *(long *)(lVar12 + 0x10) = lVar10;
    *(long *)(lVar10 + 8) = lVar12;
    *(long *)(param_1 + 0xb0) = lVar12;
code_r0x0205ef98:
    *(int *)(param_1 + 0x110) = *(int *)(param_1 + 0x110) + 1;
    *(char *)(lVar12 + 0x68) = param_10;
    memset(lVar12 + 0x18,0,0x50);
    uVar3 = *(ushort *)(param_1 + 0x1ca);
    *(ushort *)(param_1 + 0x1ca) = uVar3 + 1;
    *(ushort *)(lVar12 + 0x18) = uVar3;
    *(ushort *)(lVar12 + 0x1a) = param_2 & 0x3fff | 0x4000;
    *(undefined8 *)(lVar12 + 0x20) = param_4;
    *(undefined8 *)(lVar12 + 0x40) = param_3;
    *(undefined8 *)(lVar12 + 0x48) = param_5;
    *(undefined8 *)(lVar12 + 0x50) = param_6;
    *(undefined8 *)(lVar12 + 0x58) = param_7;
    *(undefined8 *)(lVar12 + 0x60) = param_8;
    if (param_9 != (uint *)0x0) {
      *param_9 = (uint)uVar3;
    }
    DataMemoryBarrier(2,3);
    *(undefined4 *)(param_1 + 0x40) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar9 = (int *)(param_1 + 0x44);
    if (0x14 < *piVar9) {
      do {
        cVar4 = '\x01';
        bVar5 = (bool)ExclusiveMonitorPass(piVar9,0x10);
        if (bVar5) {
          *piVar9 = *piVar9 + -1;
          cVar4 = ExclusiveMonitorsStatus();
        }
      } while (cVar4 != '\0');
      uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x80);
      if ((uVar6 & 1) != 0) {
        Aska::Semaphore::Signal() const(param_1 + 0x80);
      }
    }
    iVar8 = *(int *)(param_1 + 0x1b8);
    if (0 < iVar8) {
      lVar12 = 0;
      lVar10 = 0;
      do {
        lVar11 = *(long *)(param_1 + 0x1c0) + lVar12;
        if ((*(char *)(lVar11 + 0x84) != '\0') && (*(char *)(lVar11 + 0x83) == '\0')) {
          lVar11 = *(long *)(param_1 + 0x1c0) + lVar12 + 0x18;
          uVar6 = Aska::Event::IsSignal() const(lVar11);
          if ((uVar6 & 1) == 0) {
            Aska::Event::Set() const(lVar11);
            break;
          }
        }
        lVar10 = lVar10 + 1;
        lVar12 = lVar12 + 0xe0;
      } while (lVar10 < iVar8);
    }
    uVar7 = 1;
  }
  return uVar7;
}

// ==== Aska::SimpleMessageDispatcher::SendMessage(unsigned short, Aska::INotify*, void*, void*, signed char)
// vaddr 0x1f5f140 | ghidra 0x205f140 | size 896 | symbol _ZN4Aska23SimpleMessageDispatcher11SendMessageEtPNS_7INotifyEPvS3_a | lib libSOA-3.7.0.so | 2026-10-04
undefined4
_ZN4Aska23SimpleMessageDispatcher11SendMessageEtPNS_7INotifyEPvS3_a
          (long param_1,ushort param_2,undefined8 param_3,undefined8 param_4,undefined8 param_5,
          char param_6)

{
  int *piVar1;
  uint uVar2;
  short sVar3;
  char cVar4;
  bool bVar5;
  bool bVar6;
  undefined1 *puVar7;
  ulong uVar8;
  int iVar9;
  long lVar10;
  int *piVar11;
  long lVar12;
  undefined4 uVar13;
  long lVar14;
  long lVar15;
  undefined1 auStack_c8 [104];
  
  lVar14 = param_1 + 8;
  piVar11 = (int *)(param_1 + 0x40);
  iVar9 = 0;
code_r0x0205f180:
  if (*piVar11 == -1) {
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar11,0x10);
    if (bVar5) {
      *piVar11 = 0;
      cVar4 = ExclusiveMonitorsStatus();
    }
    if (cVar4 == '\0') goto code_r0x0205f248;
    goto code_r0x0205f180;
  }
  ClearExclusiveLocal();
  bVar5 = iVar9 < 0x1ff;
  iVar9 = iVar9 + 1;
  if (bVar5) goto code_r0x0205f180;
  piVar1 = (int *)(param_1 + 0x44);
  do {
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar5) {
      *piVar1 = *piVar1 + 1;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
  do {
    if (*piVar11 != -1) {
      ClearExclusiveLocal();
      do {
        uVar8 = Aska::Semaphore::IsReady() const(param_1 + 0x80);
        if ((uVar8 & 1) == 0) {
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
          Aska::Semaphore::Wait() const(param_1 + 0x80);
        }
        do {
          cVar4 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar5) {
            *piVar1 = *piVar1 + 1;
            cVar4 = ExclusiveMonitorsStatus();
          }
        } while (cVar4 != '\0');
        while (*piVar11 == -1) {
          cVar4 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(piVar11,0x10);
          if (bVar5) {
            *piVar11 = 0;
            cVar4 = ExclusiveMonitorsStatus();
          }
          if (cVar4 == '\0') goto code_r0x0205f238;
        }
        ClearExclusiveLocal();
      } while( true );
    }
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar11,0x10);
    if (bVar5) {
      *piVar11 = 0;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
code_r0x0205f238:
  do {
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar5) {
      *piVar1 = *piVar1 + -1;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
code_r0x0205f248:
  DataMemoryBarrier(2,3);
  uVar2 = 0;
  if (*(int *)(param_1 + 0x124) + 1U < *(uint *)(param_1 + 0x128)) {
    uVar2 = *(int *)(param_1 + 0x124) + 1;
  }
  if (uVar2 == *(uint *)(param_1 + 0x120)) {
    *(undefined1 *)(param_1 + 0x1b0) = 1;
    Aska::Event::Reset() const(param_1 + 0x148);
    uVar13 = 0;
    goto code_r0x0205f43c;
  }
  *(uint *)(param_1 + 0x124) = uVar2;
  lVar10 = *(long *)(param_1 + 0xa8);
  lVar15 = *(long *)(*(long *)(param_1 + 0x130) + (ulong)uVar2 * 8);
  do {
    if (param_1 + 0xa0 == lVar10) {
      lVar10 = *(long *)(param_1 + 0xb0);
      *(long *)(lVar15 + 8) = param_1 + 0xa0;
      *(long *)(lVar15 + 0x10) = lVar10;
      *(long *)(lVar10 + 8) = lVar15;
      *(long *)(param_1 + 0xb0) = lVar15;
code_r0x0205f2e0:
      *(int *)(param_1 + 0x110) = *(int *)(param_1 + 0x110) + 1;
      *(char *)(lVar15 + 0x68) = param_6;
      memset(lVar15 + 0x18,0,0x50);
      puVar7 = auStack_c8;
      Aska::Event::Event()(auStack_c8);
      uVar8 = Aska::Event::Create(bool, bool)(auStack_c8,1,0);
      if ((uVar8 & 1) == 0) {
        puVar7 = (undefined1 *)
                 Aska::EventPool::Scoop()(*(undefined8 *)PTR__ZN4Aska6Global12m_pEventPoolE_02cbc1a8);
        if (puVar7 != (undefined1 *)0x0) {
          bVar5 = true;
          goto code_r0x0205f344;
        }
        uVar13 = 0;
      }
      else {
        bVar5 = false;
code_r0x0205f344:
        sVar3 = *(short *)(param_1 + 0x1ca);
        *(short *)(param_1 + 0x1ca) = sVar3 + 1;
        *(short *)(lVar15 + 0x18) = sVar3;
        *(ushort *)(lVar15 + 0x1a) = param_2 & 0x3fff | 0x8000;
        *(undefined8 *)(lVar15 + 0x20) = param_3;
        *(undefined1 **)(lVar15 + 0x28) = puVar7;
        *(undefined8 *)(lVar15 + 0x48) = param_4;
        *(undefined8 *)(lVar15 + 0x50) = param_5;
        *(undefined8 *)(lVar15 + 0x58) = 0;
        *(undefined8 *)(lVar15 + 0x60) = 0;
        DataMemoryBarrier(2,3);
        *(undefined4 *)(param_1 + 0x40) = 0xffffffff;
        DataMemoryBarrier(2,3);
        piVar11 = (int *)(param_1 + 0x44);
        if (0x14 < *piVar11) {
          do {
            cVar4 = '\x01';
            bVar6 = (bool)ExclusiveMonitorPass(piVar11,0x10);
            if (bVar6) {
              *piVar11 = *piVar11 + -1;
              cVar4 = ExclusiveMonitorsStatus();
            }
          } while (cVar4 != '\0');
          uVar8 = Aska::Semaphore::IsReady() const(param_1 + 0x80);
          if ((uVar8 & 1) != 0) {
            Aska::Semaphore::Signal() const(param_1 + 0x80);
          }
        }
        iVar9 = *(int *)(param_1 + 0x1b8);
        if (0 < iVar9) {
          lVar10 = 0;
          lVar14 = 0;
          do {
            lVar15 = *(long *)(param_1 + 0x1c0) + lVar10;
            if ((*(char *)(lVar15 + 0x84) != '\0') && (*(char *)(lVar15 + 0x83) == '\0')) {
              lVar15 = *(long *)(param_1 + 0x1c0) + lVar10 + 0x18;
              uVar8 = Aska::Event::IsSignal() const(lVar15);
              if ((uVar8 & 1) == 0) {
                Aska::Event::Set() const(lVar15);
                break;
              }
            }
            lVar14 = lVar14 + 1;
            lVar10 = lVar10 + 0xe0;
          } while (lVar14 < iVar9);
        }
        if ((puVar7 != (undefined1 *)0x0) && (Aska::Event::Wait(unsigned int) const(puVar7,0), bVar5)) {
          Aska::EventPool::Sink(Aska::Event*)(*(undefined8 *)PTR__ZN4Aska6Global12m_pEventPoolE_02cbc1a8,puVar7);
        }
        lVar14 = 0;
        uVar13 = 1;
      }
      Aska::Event::Exit()(auStack_c8);
      if (lVar14 == 0) {
        return uVar13;
      }
code_r0x0205f43c:
      DataMemoryBarrier(2,3);
      *(undefined4 *)(lVar14 + 0x38) = 0xffffffff;
      DataMemoryBarrier(2,3);
      piVar11 = (int *)(lVar14 + 0x3c);
      if (0x14 < *piVar11) {
        do {
          cVar4 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(piVar11,0x10);
          if (bVar5) {
            *piVar11 = *piVar11 + -1;
            cVar4 = ExclusiveMonitorsStatus();
          }
        } while (cVar4 != '\0');
        uVar8 = Aska::Semaphore::IsReady() const(lVar14 + 0x78);
        if ((uVar8 & 1) != 0) {
          Aska::Semaphore::Signal() const(lVar14 + 0x78);
        }
      }
      return uVar13;
    }
    if (param_6 <= *(char *)(lVar10 + 0x68)) {
      lVar12 = *(long *)(lVar10 + 0x10);
      *(long *)(lVar15 + 8) = lVar10;
      *(long *)(lVar15 + 0x10) = lVar12;
      *(long *)(lVar12 + 8) = lVar15;
      *(long *)(lVar10 + 0x10) = lVar15;
      goto code_r0x0205f2e0;
    }
    lVar10 = *(long *)(lVar10 + 8);
  } while( true );
}

// ==== Aska::SimpleMessageDispatcher::SendMessage(unsigned short, Aska::INotify*, void*, void*, unsigned long, unsigned long, signed char)
// vaddr 0x1f5f4c0 | ghidra 0x205f4c0 | size 920 | symbol _ZN4Aska23SimpleMessageDispatcher11SendMessageEtPNS_7INotifyEPvS3_mma | lib libSOA-3.7.0.so | 2026-10-04
undefined4
_ZN4Aska23SimpleMessageDispatcher11SendMessageEtPNS_7INotifyEPvS3_mma
          (long param_1,ushort param_2,undefined8 param_3,undefined8 param_4,undefined8 param_5,
          undefined8 param_6,undefined8 param_7,char param_8)

{
  int *piVar1;
  uint uVar2;
  short sVar3;
  char cVar4;
  bool bVar5;
  bool bVar6;
  undefined1 *puVar7;
  ulong uVar8;
  int iVar9;
  long lVar10;
  int *piVar11;
  long lVar12;
  undefined4 uVar13;
  long lVar14;
  long lVar15;
  undefined1 auStack_c8 [104];
  
  lVar14 = param_1 + 8;
  piVar11 = (int *)(param_1 + 0x40);
  iVar9 = 0;
code_r0x0205f508:
  if (*piVar11 == -1) {
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar11,0x10);
    if (bVar5) {
      *piVar11 = 0;
      cVar4 = ExclusiveMonitorsStatus();
    }
    if (cVar4 == '\0') goto code_r0x0205f5dc;
    goto code_r0x0205f508;
  }
  ClearExclusiveLocal();
  bVar5 = iVar9 < 0x1ff;
  iVar9 = iVar9 + 1;
  if (bVar5) goto code_r0x0205f508;
  piVar1 = (int *)(param_1 + 0x44);
  do {
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar5) {
      *piVar1 = *piVar1 + 1;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
  do {
    if (*piVar11 != -1) {
      ClearExclusiveLocal();
      uVar8 = Aska::Semaphore::IsReady() const();
      if ((uVar8 & 1) == 0) goto code_r0x0205f590;
      do {
        Aska::Semaphore::Wait() const(param_1 + 0x80);
        while( true ) {
          do {
            cVar4 = '\x01';
            bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
            if (bVar5) {
              *piVar1 = *piVar1 + 1;
              cVar4 = ExclusiveMonitorsStatus();
            }
          } while (cVar4 != '\0');
          while (*piVar11 == -1) {
            cVar4 = '\x01';
            bVar5 = (bool)ExclusiveMonitorPass(piVar11,0x10);
            if (bVar5) {
              *piVar11 = 0;
              cVar4 = ExclusiveMonitorsStatus();
            }
            if (cVar4 == '\0') goto code_r0x0205f5cc;
          }
          ClearExclusiveLocal();
          uVar8 = Aska::Semaphore::IsReady() const(param_1 + 0x80);
          if ((uVar8 & 1) != 0) break;
code_r0x0205f590:
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
      } while( true );
    }
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar11,0x10);
    if (bVar5) {
      *piVar11 = 0;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
code_r0x0205f5cc:
  do {
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar5) {
      *piVar1 = *piVar1 + -1;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
code_r0x0205f5dc:
  DataMemoryBarrier(2,3);
  uVar2 = 0;
  if (*(int *)(param_1 + 0x124) + 1U < *(uint *)(param_1 + 0x128)) {
    uVar2 = *(int *)(param_1 + 0x124) + 1;
  }
  if (uVar2 == *(uint *)(param_1 + 0x120)) {
    *(undefined1 *)(param_1 + 0x1b0) = 1;
    Aska::Event::Reset() const(param_1 + 0x148);
    uVar13 = 0;
    goto code_r0x0205f7d4;
  }
  *(uint *)(param_1 + 0x124) = uVar2;
  lVar10 = *(long *)(param_1 + 0xa8);
  lVar15 = *(long *)(*(long *)(param_1 + 0x130) + (ulong)uVar2 * 8);
  do {
    if (param_1 + 0xa0 == lVar10) {
      lVar10 = *(long *)(param_1 + 0xb0);
      *(long *)(lVar15 + 8) = param_1 + 0xa0;
      *(long *)(lVar15 + 0x10) = lVar10;
      *(long *)(lVar10 + 8) = lVar15;
      *(long *)(param_1 + 0xb0) = lVar15;
code_r0x0205f674:
      *(int *)(param_1 + 0x110) = *(int *)(param_1 + 0x110) + 1;
      *(char *)(lVar15 + 0x68) = param_8;
      memset(lVar15 + 0x18,0,0x50);
      puVar7 = auStack_c8;
      Aska::Event::Event()(auStack_c8);
      uVar8 = Aska::Event::Create(bool, bool)(auStack_c8,1,0);
      if ((uVar8 & 1) == 0) {
        puVar7 = (undefined1 *)
                 Aska::EventPool::Scoop()(*(undefined8 *)PTR__ZN4Aska6Global12m_pEventPoolE_02cbc1a8);
        if (puVar7 != (undefined1 *)0x0) {
          bVar5 = true;
          goto code_r0x0205f6d8;
        }
        uVar13 = 0;
      }
      else {
        bVar5 = false;
code_r0x0205f6d8:
        sVar3 = *(short *)(param_1 + 0x1ca);
        *(short *)(param_1 + 0x1ca) = sVar3 + 1;
        *(short *)(lVar15 + 0x18) = sVar3;
        *(ushort *)(lVar15 + 0x1a) = param_2 & 0x3fff | 0x8000;
        *(undefined8 *)(lVar15 + 0x20) = param_3;
        *(undefined1 **)(lVar15 + 0x28) = puVar7;
        *(undefined8 *)(lVar15 + 0x30) = 0;
        *(undefined8 *)(lVar15 + 0x48) = param_4;
        *(undefined8 *)(lVar15 + 0x50) = param_5;
        *(undefined8 *)(lVar15 + 0x58) = param_6;
        *(undefined8 *)(lVar15 + 0x60) = param_7;
        DataMemoryBarrier(2,3);
        *(undefined4 *)(param_1 + 0x40) = 0xffffffff;
        DataMemoryBarrier(2,3);
        piVar11 = (int *)(param_1 + 0x44);
        if (0x14 < *piVar11) {
          do {
            cVar4 = '\x01';
            bVar6 = (bool)ExclusiveMonitorPass(piVar11,0x10);
            if (bVar6) {
              *piVar11 = *piVar11 + -1;
              cVar4 = ExclusiveMonitorsStatus();
            }
          } while (cVar4 != '\0');
          uVar8 = Aska::Semaphore::IsReady() const(param_1 + 0x80);
          if ((uVar8 & 1) != 0) {
            Aska::Semaphore::Signal() const(param_1 + 0x80);
          }
        }
        iVar9 = *(int *)(param_1 + 0x1b8);
        if (0 < iVar9) {
          lVar10 = 0;
          lVar14 = 0;
          do {
            lVar15 = *(long *)(param_1 + 0x1c0) + lVar10;
            if ((*(char *)(lVar15 + 0x84) != '\0') && (*(char *)(lVar15 + 0x83) == '\0')) {
              lVar15 = *(long *)(param_1 + 0x1c0) + lVar10 + 0x18;
              uVar8 = Aska::Event::IsSignal() const(lVar15);
              if ((uVar8 & 1) == 0) {
                Aska::Event::Set() const(lVar15);
                break;
              }
            }
            lVar14 = lVar14 + 1;
            lVar10 = lVar10 + 0xe0;
          } while (lVar14 < iVar9);
        }
        if ((puVar7 != (undefined1 *)0x0) && (Aska::Event::Wait(unsigned int) const(puVar7,0), bVar5)) {
          Aska::EventPool::Sink(Aska::Event*)(*(undefined8 *)PTR__ZN4Aska6Global12m_pEventPoolE_02cbc1a8,puVar7);
        }
        lVar14 = 0;
        uVar13 = 1;
      }
      Aska::Event::Exit()(auStack_c8);
      if (lVar14 == 0) {
        return uVar13;
      }
code_r0x0205f7d4:
      DataMemoryBarrier(2,3);
      *(undefined4 *)(lVar14 + 0x38) = 0xffffffff;
      DataMemoryBarrier(2,3);
      piVar11 = (int *)(lVar14 + 0x3c);
      if (0x14 < *piVar11) {
        do {
          cVar4 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(piVar11,0x10);
          if (bVar5) {
            *piVar11 = *piVar11 + -1;
            cVar4 = ExclusiveMonitorsStatus();
          }
        } while (cVar4 != '\0');
        uVar8 = Aska::Semaphore::IsReady() const(lVar14 + 0x78);
        if ((uVar8 & 1) != 0) {
          Aska::Semaphore::Signal() const(lVar14 + 0x78);
        }
      }
      return uVar13;
    }
    if (param_8 <= *(char *)(lVar10 + 0x68)) {
      lVar12 = *(long *)(lVar10 + 0x10);
      *(long *)(lVar15 + 8) = lVar10;
      *(long *)(lVar15 + 0x10) = lVar12;
      *(long *)(lVar12 + 8) = lVar15;
      *(long *)(lVar10 + 0x10) = lVar15;
      goto code_r0x0205f674;
    }
    lVar10 = *(long *)(lVar10 + 8);
  } while( true );
}

// ==== Aska::SimpleMessageDispatcher::SendMessageHigh(unsigned short, Aska::INotify*, void*, void*)
// vaddr 0x1f5f858 | ghidra 0x205f858 | size 832 | symbol _ZN4Aska23SimpleMessageDispatcher15SendMessageHighEtPNS_7INotifyEPvS3_ | lib libSOA-3.7.0.so | 2026-10-04
undefined4
_ZN4Aska23SimpleMessageDispatcher15SendMessageHighEtPNS_7INotifyEPvS3_
          (long param_1,ushort param_2,undefined8 param_3,undefined8 param_4,undefined8 param_5)

{
  int *piVar1;
  uint uVar2;
  short sVar3;
  char cVar4;
  bool bVar5;
  bool bVar6;
  undefined1 *puVar7;
  ulong uVar8;
  int iVar9;
  long lVar10;
  int *piVar11;
  undefined4 uVar12;
  long lVar13;
  long lVar14;
  undefined1 auStack_b8 [104];
  
  lVar13 = param_1 + 8;
  piVar11 = (int *)(param_1 + 0x40);
  iVar9 = 0;
  do {
    while (*piVar11 == -1) {
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar11,0x10);
      if (bVar5) {
        *piVar11 = 0;
        cVar4 = ExclusiveMonitorsStatus();
      }
      if (cVar4 == '\0') goto code_r0x0205f958;
    }
    ClearExclusiveLocal();
    bVar5 = iVar9 < 0x1ff;
    iVar9 = iVar9 + 1;
  } while (bVar5);
  piVar1 = (int *)(param_1 + 0x44);
  do {
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar5) {
      *piVar1 = *piVar1 + 1;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
  do {
    if (*piVar11 != -1) {
      ClearExclusiveLocal();
      do {
        uVar8 = Aska::Semaphore::IsReady() const(param_1 + 0x80);
        if ((uVar8 & 1) == 0) {
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
          Aska::Semaphore::Wait() const(param_1 + 0x80);
        }
        do {
          cVar4 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar5) {
            *piVar1 = *piVar1 + 1;
            cVar4 = ExclusiveMonitorsStatus();
          }
        } while (cVar4 != '\0');
        while (*piVar11 == -1) {
          cVar4 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(piVar11,0x10);
          if (bVar5) {
            *piVar11 = 0;
            cVar4 = ExclusiveMonitorsStatus();
          }
          if (cVar4 == '\0') goto code_r0x0205f948;
        }
        ClearExclusiveLocal();
      } while( true );
    }
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar11,0x10);
    if (bVar5) {
      *piVar11 = 0;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
code_r0x0205f948:
  do {
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar5) {
      *piVar1 = *piVar1 + -1;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
code_r0x0205f958:
  DataMemoryBarrier(2,3);
  uVar2 = 0;
  if (*(int *)(param_1 + 0x124) + 1U < *(uint *)(param_1 + 0x128)) {
    uVar2 = *(int *)(param_1 + 0x124) + 1;
  }
  if (uVar2 == *(uint *)(param_1 + 0x120)) {
    *(undefined1 *)(param_1 + 0x1b0) = 1;
    Aska::Event::Reset() const(param_1 + 0x148);
    uVar12 = 0;
    goto code_r0x0205fb18;
  }
  *(uint *)(param_1 + 0x124) = uVar2;
  lVar14 = *(long *)(*(long *)(param_1 + 0x130) + (ulong)uVar2 * 8);
  lVar10 = *(long *)(param_1 + 0xb0);
  *(long *)(lVar14 + 8) = param_1 + 0xa0;
  *(long *)(lVar14 + 0x10) = lVar10;
  *(long *)(lVar10 + 8) = lVar14;
  *(long *)(param_1 + 0xb0) = lVar14;
  *(int *)(param_1 + 0x110) = *(int *)(param_1 + 0x110) + 1;
  *(undefined1 *)(lVar14 + 0x68) = 0x7f;
  memset(lVar14 + 0x18,0,0x50);
  puVar7 = auStack_b8;
  Aska::Event::Event()(auStack_b8);
  uVar8 = Aska::Event::Create(bool, bool)(auStack_b8,1,0);
  if ((uVar8 & 1) == 0) {
    puVar7 = (undefined1 *)
             Aska::EventPool::Scoop()(*(undefined8 *)PTR__ZN4Aska6Global12m_pEventPoolE_02cbc1a8);
    if (puVar7 != (undefined1 *)0x0) {
      bVar5 = true;
      goto code_r0x0205fa1c;
    }
    uVar12 = 0;
  }
  else {
    bVar5 = false;
code_r0x0205fa1c:
    sVar3 = *(short *)(param_1 + 0x1ca);
    *(short *)(param_1 + 0x1ca) = sVar3 + 1;
    *(short *)(lVar14 + 0x18) = sVar3;
    *(ushort *)(lVar14 + 0x1a) = param_2 & 0x3fff | 0x8000;
    *(undefined8 *)(lVar14 + 0x20) = param_3;
    *(undefined1 **)(lVar14 + 0x28) = puVar7;
    *(undefined8 *)(lVar14 + 0x30) = 0;
    *(undefined8 *)(lVar14 + 0x48) = param_4;
    *(undefined8 *)(lVar14 + 0x50) = param_5;
    *(undefined8 *)(lVar14 + 0x58) = 0;
    *(undefined8 *)(lVar14 + 0x60) = 0;
    DataMemoryBarrier(2,3);
    *(undefined4 *)(param_1 + 0x40) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar11 = (int *)(param_1 + 0x44);
    if (0x14 < *piVar11) {
      do {
        cVar4 = '\x01';
        bVar6 = (bool)ExclusiveMonitorPass(piVar11,0x10);
        if (bVar6) {
          *piVar11 = *piVar11 + -1;
          cVar4 = ExclusiveMonitorsStatus();
        }
      } while (cVar4 != '\0');
      uVar8 = Aska::Semaphore::IsReady() const(param_1 + 0x80);
      if ((uVar8 & 1) != 0) {
        Aska::Semaphore::Signal() const(param_1 + 0x80);
      }
    }
    iVar9 = *(int *)(param_1 + 0x1b8);
    if (0 < iVar9) {
      lVar10 = 0;
      lVar13 = 0;
      do {
        lVar14 = *(long *)(param_1 + 0x1c0) + lVar10;
        if ((*(char *)(lVar14 + 0x84) != '\0') && (*(char *)(lVar14 + 0x83) == '\0')) {
          lVar14 = *(long *)(param_1 + 0x1c0) + lVar10 + 0x18;
          uVar8 = Aska::Event::IsSignal() const(lVar14);
          if ((uVar8 & 1) == 0) {
            Aska::Event::Set() const(lVar14);
            break;
          }
        }
        lVar13 = lVar13 + 1;
        lVar10 = lVar10 + 0xe0;
      } while (lVar13 < iVar9);
    }
    if ((puVar7 != (undefined1 *)0x0) && (Aska::Event::Wait(unsigned int) const(puVar7,0), bVar5)) {
      Aska::EventPool::Sink(Aska::Event*)(*(undefined8 *)PTR__ZN4Aska6Global12m_pEventPoolE_02cbc1a8,puVar7);
    }
    lVar13 = 0;
    uVar12 = 1;
  }
  Aska::Event::Exit()(auStack_b8);
  if (lVar13 == 0) {
    return uVar12;
  }
code_r0x0205fb18:
  DataMemoryBarrier(2,3);
  *(undefined4 *)(lVar13 + 0x38) = 0xffffffff;
  DataMemoryBarrier(2,3);
  piVar11 = (int *)(lVar13 + 0x3c);
  if (0x14 < *piVar11) {
    do {
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar11,0x10);
      if (bVar5) {
        *piVar11 = *piVar11 + -1;
        cVar4 = ExclusiveMonitorsStatus();
      }
    } while (cVar4 != '\0');
    uVar8 = Aska::Semaphore::IsReady() const(lVar13 + 0x78);
    if ((uVar8 & 1) != 0) {
      Aska::Semaphore::Signal() const(lVar13 + 0x78);
    }
  }
  return uVar12;
}

// ==== Aska::SimpleMessageDispatcher::AddMessageToFront()
// vaddr 0x1f5fb98 | ghidra 0x205fb98 | size 144 | symbol _ZN4Aska23SimpleMessageDispatcher17AddMessageToFrontEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska23SimpleMessageDispatcher17AddMessageToFrontEv(long param_1)

{
  uint uVar1;
  long lVar2;
  long lVar3;
  long lVar4;
  
  uVar1 = 0;
  if (*(int *)(param_1 + 0x124) + 1U < *(uint *)(param_1 + 0x128)) {
    uVar1 = *(int *)(param_1 + 0x124) + 1;
  }
  if (uVar1 == *(uint *)(param_1 + 0x120)) {
    *(undefined1 *)(param_1 + 0x1b0) = 1;
    Aska::Event::Reset() const(param_1 + 0x148);
    lVar4 = 0;
  }
  else {
    *(uint *)(param_1 + 0x124) = uVar1;
    lVar2 = *(long *)(*(long *)(param_1 + 0x130) + (ulong)uVar1 * 8);
    lVar3 = *(long *)(param_1 + 0xb0);
    lVar4 = lVar2 + 0x18;
    *(long *)(lVar2 + 8) = param_1 + 0xa0;
    *(long *)(lVar2 + 0x10) = lVar3;
    *(long *)(lVar3 + 8) = lVar2;
    *(long *)(param_1 + 0xb0) = lVar2;
    *(int *)(param_1 + 0x110) = *(int *)(param_1 + 0x110) + 1;
    *(undefined1 *)(lVar2 + 0x68) = 0x7f;
    memset(lVar4,0,0x50);
  }
  return lVar4;
}

// ==== Aska::SimpleMessageDispatcher::SendMessageHigh(unsigned short, Aska::INotify*, void*, void*, unsigned long, unsigned long)
// vaddr 0x1f5fc28 | ghidra 0x205fc28 | size 848 | symbol _ZN4Aska23SimpleMessageDispatcher15SendMessageHighEtPNS_7INotifyEPvS3_mm | lib libSOA-3.7.0.so | 2026-10-04
undefined4
_ZN4Aska23SimpleMessageDispatcher15SendMessageHighEtPNS_7INotifyEPvS3_mm
          (long param_1,ushort param_2,undefined8 param_3,undefined8 param_4,undefined8 param_5,
          undefined8 param_6,undefined8 param_7)

{
  int *piVar1;
  uint uVar2;
  short sVar3;
  char cVar4;
  bool bVar5;
  bool bVar6;
  undefined1 *puVar7;
  ulong uVar8;
  int iVar9;
  long lVar10;
  int *piVar11;
  undefined4 uVar12;
  long lVar13;
  long lVar14;
  undefined1 auStack_c8 [104];
  
  lVar13 = param_1 + 8;
  piVar11 = (int *)(param_1 + 0x40);
  iVar9 = 0;
  do {
    while (*piVar11 == -1) {
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar11,0x10);
      if (bVar5) {
        *piVar11 = 0;
        cVar4 = ExclusiveMonitorsStatus();
      }
      if (cVar4 == '\0') goto code_r0x0205fd34;
    }
    ClearExclusiveLocal();
    bVar5 = iVar9 < 0x1ff;
    iVar9 = iVar9 + 1;
  } while (bVar5);
  piVar1 = (int *)(param_1 + 0x44);
  do {
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar5) {
      *piVar1 = *piVar1 + 1;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
  do {
    if (*piVar11 != -1) {
      ClearExclusiveLocal();
      do {
        uVar8 = Aska::Semaphore::IsReady() const(param_1 + 0x80);
        if ((uVar8 & 1) == 0) {
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
          Aska::Semaphore::Wait() const(param_1 + 0x80);
        }
        do {
          cVar4 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar5) {
            *piVar1 = *piVar1 + 1;
            cVar4 = ExclusiveMonitorsStatus();
          }
        } while (cVar4 != '\0');
        while (*piVar11 == -1) {
          cVar4 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(piVar11,0x10);
          if (bVar5) {
            *piVar11 = 0;
            cVar4 = ExclusiveMonitorsStatus();
          }
          if (cVar4 == '\0') goto code_r0x0205fd24;
        }
        ClearExclusiveLocal();
      } while( true );
    }
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar11,0x10);
    if (bVar5) {
      *piVar11 = 0;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
code_r0x0205fd24:
  do {
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar5) {
      *piVar1 = *piVar1 + -1;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
code_r0x0205fd34:
  DataMemoryBarrier(2,3);
  uVar2 = 0;
  if (*(int *)(param_1 + 0x124) + 1U < *(uint *)(param_1 + 0x128)) {
    uVar2 = *(int *)(param_1 + 0x124) + 1;
  }
  if (uVar2 == *(uint *)(param_1 + 0x120)) {
    *(undefined1 *)(param_1 + 0x1b0) = 1;
    Aska::Event::Reset() const(param_1 + 0x148);
    uVar12 = 0;
    goto code_r0x0205fef4;
  }
  *(uint *)(param_1 + 0x124) = uVar2;
  lVar14 = *(long *)(*(long *)(param_1 + 0x130) + (ulong)uVar2 * 8);
  lVar10 = *(long *)(param_1 + 0xb0);
  *(long *)(lVar14 + 8) = param_1 + 0xa0;
  *(long *)(lVar14 + 0x10) = lVar10;
  *(long *)(lVar10 + 8) = lVar14;
  *(long *)(param_1 + 0xb0) = lVar14;
  *(int *)(param_1 + 0x110) = *(int *)(param_1 + 0x110) + 1;
  *(undefined1 *)(lVar14 + 0x68) = 0x7f;
  memset(lVar14 + 0x18,0,0x50);
  puVar7 = auStack_c8;
  Aska::Event::Event()(auStack_c8);
  uVar8 = Aska::Event::Create(bool, bool)(auStack_c8,1,0);
  if ((uVar8 & 1) == 0) {
    puVar7 = (undefined1 *)
             Aska::EventPool::Scoop()(*(undefined8 *)PTR__ZN4Aska6Global12m_pEventPoolE_02cbc1a8);
    if (puVar7 != (undefined1 *)0x0) {
      bVar5 = true;
      goto code_r0x0205fdf8;
    }
    uVar12 = 0;
  }
  else {
    bVar5 = false;
code_r0x0205fdf8:
    sVar3 = *(short *)(param_1 + 0x1ca);
    *(short *)(param_1 + 0x1ca) = sVar3 + 1;
    *(short *)(lVar14 + 0x18) = sVar3;
    *(ushort *)(lVar14 + 0x1a) = param_2 & 0x3fff | 0x8000;
    *(undefined8 *)(lVar14 + 0x20) = param_3;
    *(undefined1 **)(lVar14 + 0x28) = puVar7;
    *(undefined8 *)(lVar14 + 0x30) = 0;
    *(undefined8 *)(lVar14 + 0x48) = param_4;
    *(undefined8 *)(lVar14 + 0x50) = param_5;
    *(undefined8 *)(lVar14 + 0x58) = param_6;
    *(undefined8 *)(lVar14 + 0x60) = param_7;
    DataMemoryBarrier(2,3);
    *(undefined4 *)(param_1 + 0x40) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar11 = (int *)(param_1 + 0x44);
    if (0x14 < *piVar11) {
      do {
        cVar4 = '\x01';
        bVar6 = (bool)ExclusiveMonitorPass(piVar11,0x10);
        if (bVar6) {
          *piVar11 = *piVar11 + -1;
          cVar4 = ExclusiveMonitorsStatus();
        }
      } while (cVar4 != '\0');
      uVar8 = Aska::Semaphore::IsReady() const(param_1 + 0x80);
      if ((uVar8 & 1) != 0) {
        Aska::Semaphore::Signal() const(param_1 + 0x80);
      }
    }
    iVar9 = *(int *)(param_1 + 0x1b8);
    if (0 < iVar9) {
      lVar10 = 0;
      lVar13 = 0;
      do {
        lVar14 = *(long *)(param_1 + 0x1c0) + lVar10;
        if ((*(char *)(lVar14 + 0x84) != '\0') && (*(char *)(lVar14 + 0x83) == '\0')) {
          lVar14 = *(long *)(param_1 + 0x1c0) + lVar10 + 0x18;
          uVar8 = Aska::Event::IsSignal() const(lVar14);
          if ((uVar8 & 1) == 0) {
            Aska::Event::Set() const(lVar14);
            break;
          }
        }
        lVar13 = lVar13 + 1;
        lVar10 = lVar10 + 0xe0;
      } while (lVar13 < iVar9);
    }
    if ((puVar7 != (undefined1 *)0x0) && (Aska::Event::Wait(unsigned int) const(puVar7,0), bVar5)) {
      Aska::EventPool::Sink(Aska::Event*)(*(undefined8 *)PTR__ZN4Aska6Global12m_pEventPoolE_02cbc1a8,puVar7);
    }
    lVar13 = 0;
    uVar12 = 1;
  }
  Aska::Event::Exit()(auStack_c8);
  if (lVar13 == 0) {
    return uVar12;
  }
code_r0x0205fef4:
  DataMemoryBarrier(2,3);
  *(undefined4 *)(lVar13 + 0x38) = 0xffffffff;
  DataMemoryBarrier(2,3);
  piVar11 = (int *)(lVar13 + 0x3c);
  if (0x14 < *piVar11) {
    do {
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar11,0x10);
      if (bVar5) {
        *piVar11 = *piVar11 + -1;
        cVar4 = ExclusiveMonitorsStatus();
      }
    } while (cVar4 != '\0');
    uVar8 = Aska::Semaphore::IsReady() const(lVar13 + 0x78);
    if ((uVar8 & 1) != 0) {
      Aska::Semaphore::Signal() const(lVar13 + 0x78);
    }
  }
  return uVar12;
}

// ==== Aska::SimpleMessageDispatcher::PostMessage(Aska::Task*, int, unsigned short, Aska::INotify*, void*, void*, unsigned int*, signed char)
// vaddr 0x1f5ff78 | ghidra 0x205ff78 | size 840 | symbol _ZN4Aska23SimpleMessageDispatcher11PostMessageEPNS_4TaskEitPNS_7INotifyEPvS5_Pja | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska23SimpleMessageDispatcher11PostMessageEPNS_4TaskEitPNS_7INotifyEPvS5_Pja
          (long param_1,long param_2,uint param_3,ushort param_4,undefined8 param_5,
          undefined8 param_6,undefined8 param_7,uint *param_8,char param_9)

{
  int *piVar1;
  uint uVar2;
  short sVar3;
  char cVar4;
  bool bVar5;
  ulong uVar6;
  int iVar7;
  int *piVar8;
  long lVar9;
  long lVar10;
  long lVar11;
  
  piVar8 = (int *)(param_1 + 0x40);
  iVar7 = 0;
code_r0x0205ffc0:
  if (*piVar8 == -1) {
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar8,0x10);
    if (bVar5) {
      *piVar8 = 0;
      cVar4 = ExclusiveMonitorsStatus();
    }
    if (cVar4 == '\0') goto code_r0x02060094;
    goto code_r0x0205ffc0;
  }
  ClearExclusiveLocal();
  bVar5 = iVar7 < 0x1ff;
  iVar7 = iVar7 + 1;
  if (bVar5) goto code_r0x0205ffc0;
  piVar1 = (int *)(param_1 + 0x44);
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
      uVar6 = Aska::Semaphore::IsReady() const();
      if ((uVar6 & 1) == 0) goto code_r0x02060048;
      do {
        Aska::Semaphore::Wait() const(param_1 + 0x80);
        while( true ) {
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
            if (cVar4 == '\0') goto code_r0x02060084;
          }
          ClearExclusiveLocal();
          uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x80);
          if ((uVar6 & 1) != 0) break;
code_r0x02060048:
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
      } while( true );
    }
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar8,0x10);
    if (bVar5) {
      *piVar8 = 0;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
code_r0x02060084:
  do {
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar5) {
      *piVar1 = *piVar1 + -1;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
code_r0x02060094:
  DataMemoryBarrier(2,3);
  uVar2 = 0;
  if (*(int *)(param_1 + 0x124) + 1U < *(uint *)(param_1 + 0x128)) {
    uVar2 = *(int *)(param_1 + 0x124) + 1;
  }
  if (uVar2 == *(uint *)(param_1 + 0x120)) {
    *(undefined1 *)(param_1 + 0x1b0) = 1;
    Aska::Event::Reset() const(param_1 + 0x148);
    DataMemoryBarrier(2,3);
    *(undefined4 *)(param_1 + 0x40) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar8 = (int *)(param_1 + 0x44);
    if (0x14 < *piVar8) {
      do {
        cVar4 = '\x01';
        bVar5 = (bool)ExclusiveMonitorPass(piVar8,0x10);
        if (bVar5) {
          *piVar8 = *piVar8 + -1;
          cVar4 = ExclusiveMonitorsStatus();
        }
      } while (cVar4 != '\0');
      uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x80);
      if ((uVar6 & 1) != 0) {
        Aska::Semaphore::Signal() const(param_1 + 0x80);
      }
    }
    return 0;
  }
  *(uint *)(param_1 + 0x124) = uVar2;
  lVar9 = *(long *)(param_1 + 0xa8);
  lVar11 = *(long *)(*(long *)(param_1 + 0x130) + (ulong)uVar2 * 8);
  do {
    if (param_1 + 0xa0 == lVar9) {
      lVar9 = *(long *)(param_1 + 0xb0);
      *(long *)(lVar11 + 8) = param_1 + 0xa0;
      *(long *)(lVar11 + 0x10) = lVar9;
      *(long *)(lVar9 + 8) = lVar11;
      *(long *)(param_1 + 0xb0) = lVar11;
code_r0x02060174:
      *(int *)(param_1 + 0x110) = *(int *)(param_1 + 0x110) + 1;
      *(char *)(lVar11 + 0x68) = param_9;
      memset((ushort *)(lVar11 + 0x18),0,0x50);
      lVar9 = 0;
      if (param_2 != 0) {
        lVar9 = *(long *)(param_2 + 0x18);
      }
      sVar3 = *(short *)(param_1 + 0x1ca);
      *(short *)(param_1 + 0x1ca) = sVar3 + 1;
      *(short *)(lVar11 + 0x18) = sVar3;
      *(ushort *)(lVar11 + 0x1a) = param_4 & 0x3fff;
      *(undefined8 *)(lVar11 + 0x20) = param_5;
      *(long *)(lVar11 + 0x30) = lVar9;
      *(uint *)(lVar11 + 0x38) = param_3;
      *(undefined8 *)(lVar11 + 0x48) = param_6;
      *(undefined8 *)(lVar11 + 0x50) = param_7;
      *(undefined8 *)(lVar11 + 0x58) = 0;
      *(undefined8 *)(lVar11 + 0x60) = 0;
      if ((param_3 < 0x20) && (lVar9 != 0)) {
        Aska::TaskManager::AddThreadBarrier(int)(lVar9,param_3);
        Aska::TaskManager::IncrementThreadBarrierCount(int)(lVar9,param_3);
      }
      if (param_8 != (uint *)0x0) {
        *param_8 = (uint)*(ushort *)(lVar11 + 0x18);
      }
      DataMemoryBarrier(2,3);
      *(undefined4 *)(param_1 + 0x40) = 0xffffffff;
      DataMemoryBarrier(2,3);
      piVar8 = (int *)(param_1 + 0x44);
      if (0x14 < *piVar8) {
        do {
          cVar4 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(piVar8,0x10);
          if (bVar5) {
            *piVar8 = *piVar8 + -1;
            cVar4 = ExclusiveMonitorsStatus();
          }
        } while (cVar4 != '\0');
        uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x80);
        if ((uVar6 & 1) != 0) {
          Aska::Semaphore::Signal() const(param_1 + 0x80);
        }
      }
      iVar7 = *(int *)(param_1 + 0x1b8);
      if (0 < iVar7) {
        lVar11 = 0;
        lVar9 = 0;
        do {
          lVar10 = *(long *)(param_1 + 0x1c0) + lVar11;
          if ((*(char *)(lVar10 + 0x84) != '\0') && (*(char *)(lVar10 + 0x83) == '\0')) {
            lVar10 = *(long *)(param_1 + 0x1c0) + lVar11 + 0x18;
            uVar6 = Aska::Event::IsSignal() const(lVar10);
            if ((uVar6 & 1) == 0) {
              Aska::Event::Set() const(lVar10);
              return 1;
            }
          }
          lVar9 = lVar9 + 1;
          lVar11 = lVar11 + 0xe0;
        } while (lVar9 < iVar7);
      }
      return 1;
    }
    if (param_9 <= *(char *)(lVar9 + 0x68)) {
      lVar10 = *(long *)(lVar9 + 0x10);
      *(long *)(lVar11 + 8) = lVar9;
      *(long *)(lVar11 + 0x10) = lVar10;
      *(long *)(lVar10 + 8) = lVar11;
      *(long *)(lVar9 + 0x10) = lVar11;
      goto code_r0x02060174;
    }
    lVar9 = *(long *)(lVar9 + 8);
  } while( true );
}

// ==== Aska::SimpleMessageDispatcher::PostMessage(Aska::Task*, int, unsigned short, Aska::INotify*, void*, void*, unsigned long, unsigned long, unsigned int*, signed char)
// vaddr 0x1f602c0 | ghidra 0x20602c0 | size 900 | symbol _ZN4Aska23SimpleMessageDispatcher11PostMessageEPNS_4TaskEitPNS_7INotifyEPvS5_mmPja | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska23SimpleMessageDispatcher11PostMessageEPNS_4TaskEitPNS_7INotifyEPvS5_mmPja
          (long param_1,long param_2,uint param_3,ushort param_4,undefined8 param_5,
          undefined8 param_6,undefined8 param_7,undefined8 param_8,undefined8 param_9,uint *param_10
          ,char param_11)

{
  int *piVar1;
  uint uVar2;
  short sVar3;
  char cVar4;
  bool bVar5;
  ulong uVar6;
  undefined8 uVar7;
  int iVar8;
  int *piVar9;
  long lVar10;
  long lVar11;
  long lVar12;
  
  piVar9 = (int *)(param_1 + 0x40);
  iVar8 = 0;
code_r0x02060300:
  do {
    if (*piVar9 == -1) goto code_r0x0206030c;
    ClearExclusiveLocal();
    bVar5 = iVar8 < 0x1ff;
    iVar8 = iVar8 + 1;
  } while (bVar5);
  piVar1 = (int *)(param_1 + 0x44);
  do {
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar5) {
      *piVar1 = *piVar1 + 1;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
  do {
    if (*piVar9 != -1) {
      ClearExclusiveLocal();
      do {
        uVar6 = Aska::Semaphore::IsReady() const();
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
          Aska::Semaphore::Wait() const(param_1 + 0x80);
        }
        do {
          cVar4 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar5) {
            *piVar1 = *piVar1 + 1;
            cVar4 = ExclusiveMonitorsStatus();
          }
        } while (cVar4 != '\0');
        while (*piVar9 == -1) {
          cVar4 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(piVar9,0x10);
          if (bVar5) {
            *piVar9 = 0;
            cVar4 = ExclusiveMonitorsStatus();
          }
          if (cVar4 == '\0') goto code_r0x02060628;
        }
        ClearExclusiveLocal();
      } while( true );
    }
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar9,0x10);
    if (bVar5) {
      *piVar9 = 0;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
code_r0x02060628:
  do {
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar5) {
      *piVar1 = *piVar1 + -1;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
  DataMemoryBarrier(2,3);
  goto code_r0x0206035c;
code_r0x0206030c:
  cVar4 = '\x01';
  bVar5 = (bool)ExclusiveMonitorPass(piVar9,0x10);
  if (bVar5) {
    *piVar9 = 0;
    cVar4 = ExclusiveMonitorsStatus();
  }
  if (cVar4 == '\0') goto code_r0x02060358;
  goto code_r0x02060300;
code_r0x02060358:
  DataMemoryBarrier(2,3);
code_r0x0206035c:
  uVar2 = 0;
  if (*(int *)(param_1 + 0x124) + 1U < *(uint *)(param_1 + 0x128)) {
    uVar2 = *(int *)(param_1 + 0x124) + 1;
  }
  if (uVar2 == *(uint *)(param_1 + 0x120)) {
    *(undefined1 *)(param_1 + 0x1b0) = 1;
    Aska::Event::Reset() const(param_1 + 0x148);
    DataMemoryBarrier(2,3);
    *(undefined4 *)(param_1 + 0x40) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar9 = (int *)(param_1 + 0x44);
    if (0x14 < *piVar9) {
      do {
        cVar4 = '\x01';
        bVar5 = (bool)ExclusiveMonitorPass(piVar9,0x10);
        if (bVar5) {
          *piVar9 = *piVar9 + -1;
          cVar4 = ExclusiveMonitorsStatus();
        }
      } while (cVar4 != '\0');
      uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x80);
      if ((uVar6 & 1) != 0) {
        Aska::Semaphore::Signal() const(param_1 + 0x80);
      }
    }
    uVar7 = 0;
  }
  else {
    lVar10 = *(long *)(param_1 + 0xa8);
    *(uint *)(param_1 + 0x124) = uVar2;
    lVar12 = *(long *)(*(long *)(param_1 + 0x130) + (ulong)uVar2 * 8);
    for (; param_1 + 0xa0 != lVar10; lVar10 = *(long *)(lVar10 + 8)) {
      if (param_11 <= *(char *)(lVar10 + 0x68)) {
        lVar11 = *(long *)(lVar10 + 0x10);
        *(long *)(lVar12 + 8) = lVar10;
        *(long *)(lVar12 + 0x10) = lVar11;
        *(long *)(lVar11 + 8) = lVar12;
        *(long *)(lVar10 + 0x10) = lVar12;
        goto code_r0x02060460;
      }
    }
    lVar10 = *(long *)(param_1 + 0xb0);
    *(long *)(lVar12 + 8) = param_1 + 0xa0;
    *(long *)(lVar12 + 0x10) = lVar10;
    *(long *)(lVar10 + 8) = lVar12;
    *(long *)(param_1 + 0xb0) = lVar12;
code_r0x02060460:
    *(int *)(param_1 + 0x110) = *(int *)(param_1 + 0x110) + 1;
    *(char *)(lVar12 + 0x68) = param_11;
    memset((ushort *)(lVar12 + 0x18),0,0x50);
    lVar10 = 0;
    if (param_2 != 0) {
      lVar10 = *(long *)(param_2 + 0x18);
    }
    sVar3 = *(short *)(param_1 + 0x1ca);
    *(short *)(param_1 + 0x1ca) = sVar3 + 1;
    *(short *)(lVar12 + 0x18) = sVar3;
    *(ushort *)(lVar12 + 0x1a) = param_4 & 0x3fff;
    *(undefined8 *)(lVar12 + 0x20) = param_5;
    *(long *)(lVar12 + 0x30) = lVar10;
    *(uint *)(lVar12 + 0x38) = param_3;
    *(undefined8 *)(lVar12 + 0x48) = param_6;
    *(undefined8 *)(lVar12 + 0x50) = param_7;
    *(undefined8 *)(lVar12 + 0x58) = param_8;
    *(undefined8 *)(lVar12 + 0x60) = param_9;
    if ((param_3 < 0x20) && (lVar10 != 0)) {
      Aska::TaskManager::AddThreadBarrier(int)(lVar10,param_3);
      Aska::TaskManager::IncrementThreadBarrierCount(int)(lVar10,param_3);
    }
    if (param_10 != (uint *)0x0) {
      *param_10 = (uint)*(ushort *)(lVar12 + 0x18);
    }
    DataMemoryBarrier(2,3);
    *(undefined4 *)(param_1 + 0x40) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar9 = (int *)(param_1 + 0x44);
    if (0x14 < *piVar9) {
      do {
        cVar4 = '\x01';
        bVar5 = (bool)ExclusiveMonitorPass(piVar9,0x10);
        if (bVar5) {
          *piVar9 = *piVar9 + -1;
          cVar4 = ExclusiveMonitorsStatus();
        }
      } while (cVar4 != '\0');
      uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x80);
      if ((uVar6 & 1) != 0) {
        Aska::Semaphore::Signal() const(param_1 + 0x80);
      }
    }
    iVar8 = *(int *)(param_1 + 0x1b8);
    if (0 < iVar8) {
      lVar12 = 0;
      lVar10 = 0;
      do {
        lVar11 = *(long *)(param_1 + 0x1c0) + lVar12;
        if ((*(char *)(lVar11 + 0x84) != '\0') && (*(char *)(lVar11 + 0x83) == '\0')) {
          lVar11 = *(long *)(param_1 + 0x1c0) + lVar12 + 0x18;
          uVar6 = Aska::Event::IsSignal() const(lVar11);
          if ((uVar6 & 1) == 0) {
            Aska::Event::Set() const(lVar11);
            break;
          }
        }
        lVar10 = lVar10 + 1;
        lVar12 = lVar12 + 0xe0;
      } while (lVar10 < iVar8);
    }
    uVar7 = 1;
  }
  return uVar7;
}

// ==== Aska::SimpleMessageDispatcher::PostMultiMessages(Aska::Task*, Aska::SimpleMessageDispatcher::ArgumentWithBarrier*, int, signed char)
// vaddr 0x1f60644 | ghidra 0x2060644 | size 1072 | symbol _ZN4Aska23SimpleMessageDispatcher17PostMultiMessagesEPNS_4TaskEPNS0_19ArgumentWithBarrierEia | lib libSOA-3.7.0.so | 2026-10-04
undefined4
_ZN4Aska23SimpleMessageDispatcher17PostMultiMessagesEPNS_4TaskEPNS0_19ArgumentWithBarrierEia
          (long param_1,long param_2,ushort *param_3,int param_4,char param_5)

{
  int *piVar1;
  uint uVar2;
  uint uVar3;
  short sVar4;
  ushort uVar5;
  char cVar6;
  bool bVar7;
  ulong uVar8;
  int iVar9;
  long lVar10;
  undefined8 uVar11;
  int *piVar12;
  long lVar13;
  long lVar14;
  long lVar15;
  undefined4 uVar16;
  ushort *puVar17;
  
  uVar3 = *(uint *)(param_3 + 0x14);
  piVar12 = (int *)(param_1 + 0x40);
  iVar9 = 0;
code_r0x02060680:
  do {
    if (*piVar12 != -1) {
      ClearExclusiveLocal();
      bVar7 = iVar9 < 0x1ff;
      iVar9 = iVar9 + 1;
      if (bVar7) goto code_r0x02060680;
      piVar1 = (int *)(param_1 + 0x44);
      do {
        cVar6 = '\x01';
        bVar7 = (bool)ExclusiveMonitorPass(piVar1,0x10);
        if (bVar7) {
          *piVar1 = *piVar1 + 1;
          cVar6 = ExclusiveMonitorsStatus();
        }
      } while (cVar6 != '\0');
      do {
        if (*piVar12 != -1) {
          ClearExclusiveLocal();
          do {
            uVar8 = Aska::Semaphore::IsReady() const(param_1 + 0x80);
            if ((uVar8 & 1) == 0) {
              do {
                cVar6 = '\x01';
                bVar7 = (bool)ExclusiveMonitorPass(piVar1,0x10);
                if (bVar7) {
                  *piVar1 = *piVar1 + -1;
                  cVar6 = ExclusiveMonitorsStatus();
                }
              } while (cVar6 != '\0');
              Aska::Thread::Sleep(unsigned int)(1);
            }
            else {
              Aska::Semaphore::Wait() const(param_1 + 0x80);
            }
            do {
              cVar6 = '\x01';
              bVar7 = (bool)ExclusiveMonitorPass(piVar1,0x10);
              if (bVar7) {
                *piVar1 = *piVar1 + 1;
                cVar6 = ExclusiveMonitorsStatus();
              }
            } while (cVar6 != '\0');
            while (*piVar12 == -1) {
              cVar6 = '\x01';
              bVar7 = (bool)ExclusiveMonitorPass(piVar12,0x10);
              if (bVar7) {
                *piVar12 = 0;
                cVar6 = ExclusiveMonitorsStatus();
              }
              if (cVar6 == '\0') goto code_r0x02060738;
            }
            ClearExclusiveLocal();
          } while( true );
        }
        cVar6 = '\x01';
        bVar7 = (bool)ExclusiveMonitorPass(piVar12,0x10);
        if (bVar7) {
          *piVar12 = 0;
          cVar6 = ExclusiveMonitorsStatus();
        }
      } while (cVar6 != '\0');
code_r0x02060738:
      do {
        cVar6 = '\x01';
        bVar7 = (bool)ExclusiveMonitorPass(piVar1,0x10);
        if (bVar7) {
          *piVar1 = *piVar1 + -1;
          cVar6 = ExclusiveMonitorsStatus();
        }
      } while (cVar6 != '\0');
code_r0x02060748:
      DataMemoryBarrier(2,3);
      if (param_4 < 1) {
        uVar16 = 1;
      }
      else {
        puVar17 = param_3 + (long)param_4 * 0x18;
        lVar14 = param_1 + 0xa0;
        if (param_2 == 0) {
          uVar16 = 1;
          do {
            *param_3 = *param_3 & 0x3fff;
            uVar2 = 0;
            if (*(int *)(param_1 + 0x124) + 1U < *(uint *)(param_1 + 0x128)) {
              uVar2 = *(int *)(param_1 + 0x124) + 1;
            }
            if (uVar2 == *(uint *)(param_1 + 0x120)) {
              *(undefined1 *)(param_1 + 0x1b0) = 1;
              Aska::Event::Reset() const(param_1 + 0x148);
              uVar16 = 0;
            }
            else {
              *(uint *)(param_1 + 0x124) = uVar2;
              lVar15 = *(long *)(*(long *)(param_1 + 0x130) + (ulong)uVar2 * 8);
              for (lVar10 = *(long *)(param_1 + 0xa8); lVar14 != lVar10;
                  lVar10 = *(long *)(lVar10 + 8)) {
                if (param_5 <= *(char *)(lVar10 + 0x68)) {
                  lVar13 = *(long *)(lVar10 + 0x10);
                  *(long *)(lVar15 + 8) = lVar10;
                  *(long *)(lVar15 + 0x10) = lVar13;
                  *(long *)(lVar13 + 8) = lVar15;
                  *(long *)(lVar10 + 0x10) = lVar15;
                  goto code_r0x02060960;
                }
              }
              lVar10 = *(long *)(param_1 + 0xb0);
              *(long *)(lVar15 + 8) = lVar14;
              *(long *)(lVar15 + 0x10) = lVar10;
              *(long *)(lVar10 + 8) = lVar15;
              *(long *)(param_1 + 0xb0) = lVar15;
code_r0x02060960:
              *(int *)(param_1 + 0x110) = *(int *)(param_1 + 0x110) + 1;
              *(char *)(lVar15 + 0x68) = param_5;
              memset(lVar15 + 0x18,0,0x50);
              uVar5 = *(ushort *)(param_1 + 0x1ca);
              *(ushort *)(param_1 + 0x1ca) = uVar5 + 1;
              *(ushort *)(lVar15 + 0x18) = uVar5;
              *(ushort *)(lVar15 + 0x1a) = *param_3;
              uVar11 = *(undefined8 *)(param_3 + 4);
              *(undefined8 *)(lVar15 + 0x30) = 0;
              *(uint *)(lVar15 + 0x38) = uVar3;
              *(undefined8 *)(lVar15 + 0x20) = uVar11;
              *(undefined8 *)(lVar15 + 0x48) = *(undefined8 *)(param_3 + 8);
              uVar11 = *(undefined8 *)(param_3 + 0xc);
              *(undefined8 *)(lVar15 + 0x58) = 0;
              *(undefined8 *)(lVar15 + 0x60) = 0;
              *(undefined8 *)(lVar15 + 0x50) = uVar11;
              if (*(uint **)(param_3 + 0x10) != (uint *)0x0) {
                **(uint **)(param_3 + 0x10) = (uint)uVar5;
              }
            }
            param_3 = param_3 + 0x18;
          } while (param_3 < puVar17);
        }
        else {
          uVar16 = 1;
          do {
            *param_3 = *param_3 & 0x3fff;
            uVar2 = 0;
            if (*(int *)(param_1 + 0x124) + 1U < *(uint *)(param_1 + 0x128)) {
              uVar2 = *(int *)(param_1 + 0x124) + 1;
            }
            if (uVar2 == *(uint *)(param_1 + 0x120)) {
              *(undefined1 *)(param_1 + 0x1b0) = 1;
              Aska::Event::Reset() const(param_1 + 0x148);
              uVar16 = 0;
            }
            else {
              *(uint *)(param_1 + 0x124) = uVar2;
              lVar15 = *(long *)(*(long *)(param_1 + 0x130) + (ulong)uVar2 * 8);
              for (lVar10 = *(long *)(param_1 + 0xa8); lVar14 != lVar10;
                  lVar10 = *(long *)(lVar10 + 8)) {
                if (param_5 <= *(char *)(lVar10 + 0x68)) {
                  lVar13 = *(long *)(lVar10 + 0x10);
                  *(long *)(lVar15 + 8) = lVar10;
                  *(long *)(lVar15 + 0x10) = lVar13;
                  *(long *)(lVar13 + 8) = lVar15;
                  *(long *)(lVar10 + 0x10) = lVar15;
                  goto code_r0x0206080c;
                }
              }
              lVar10 = *(long *)(param_1 + 0xb0);
              *(long *)(lVar15 + 8) = lVar14;
              *(long *)(lVar15 + 0x10) = lVar10;
              *(long *)(lVar10 + 8) = lVar15;
              *(long *)(param_1 + 0xb0) = lVar15;
code_r0x0206080c:
              *(int *)(param_1 + 0x110) = *(int *)(param_1 + 0x110) + 1;
              *(char *)(lVar15 + 0x68) = param_5;
              memset((ushort *)(lVar15 + 0x18),0,0x50);
              sVar4 = *(short *)(param_1 + 0x1ca);
              lVar10 = *(long *)(param_2 + 0x18);
              *(short *)(param_1 + 0x1ca) = sVar4 + 1;
              *(short *)(lVar15 + 0x18) = sVar4;
              *(ushort *)(lVar15 + 0x1a) = *param_3;
              uVar11 = *(undefined8 *)(param_3 + 4);
              *(long *)(lVar15 + 0x30) = lVar10;
              *(uint *)(lVar15 + 0x38) = uVar3;
              *(undefined8 *)(lVar15 + 0x20) = uVar11;
              *(undefined8 *)(lVar15 + 0x48) = *(undefined8 *)(param_3 + 8);
              uVar11 = *(undefined8 *)(param_3 + 0xc);
              *(undefined8 *)(lVar15 + 0x58) = 0;
              *(undefined8 *)(lVar15 + 0x60) = 0;
              *(undefined8 *)(lVar15 + 0x50) = uVar11;
              if ((uVar3 < 0x20) && (lVar10 != 0)) {
                Aska::TaskManager::AddThreadBarrier(int)(lVar10,uVar3);
                Aska::TaskManager::IncrementThreadBarrierCount(int)(lVar10,uVar3);
              }
              if (*(uint **)(param_3 + 0x10) != (uint *)0x0) {
                **(uint **)(param_3 + 0x10) = (uint)*(ushort *)(lVar15 + 0x18);
              }
            }
            param_3 = param_3 + 0x18;
          } while (param_3 < puVar17);
        }
      }
      DataMemoryBarrier(2,3);
      *(undefined4 *)(param_1 + 0x40) = 0xffffffff;
      DataMemoryBarrier(2,3);
      piVar12 = (int *)(param_1 + 0x44);
      if (0x14 < *piVar12) {
        do {
          cVar6 = '\x01';
          bVar7 = (bool)ExclusiveMonitorPass(piVar12,0x10);
          if (bVar7) {
            *piVar12 = *piVar12 + -1;
            cVar6 = ExclusiveMonitorsStatus();
          }
        } while (cVar6 != '\0');
        uVar8 = Aska::Semaphore::IsReady() const(param_1 + 0x80);
        if ((uVar8 & 1) != 0) {
          Aska::Semaphore::Signal() const(param_1 + 0x80);
        }
      }
      uVar8 = (ulong)*(uint *)(param_1 + 0x1b8);
      if (0 < (int)*(uint *)(param_1 + 0x1b8)) {
        lVar14 = 0x84;
        do {
          if (*(char *)(*(long *)(param_1 + 0x1c0) + lVar14) != '\0') {
            Aska::Event::Set() const(*(long *)(param_1 + 0x1c0) + lVar14 + -0x6c);
          }
          uVar8 = uVar8 - 1;
          lVar14 = lVar14 + 0xe0;
        } while (uVar8 != 0);
      }
      return uVar16;
    }
    cVar6 = '\x01';
    bVar7 = (bool)ExclusiveMonitorPass(piVar12,0x10);
    if (bVar7) {
      *piVar12 = 0;
      cVar6 = ExclusiveMonitorsStatus();
    }
    if (cVar6 == '\0') goto code_r0x02060748;
  } while( true );
}

// ==== Aska::SimpleMessageDispatcher::PostMultiMessages(Aska::Task*, Aska::SimpleMessageDispatcher::ArgumentWithBarrierEx*, int, signed char)
// vaddr 0x1f60a74 | ghidra 0x2060a74 | size 1096 | symbol _ZN4Aska23SimpleMessageDispatcher17PostMultiMessagesEPNS_4TaskEPNS0_21ArgumentWithBarrierExEia | lib libSOA-3.7.0.so | 2026-10-04
undefined4
_ZN4Aska23SimpleMessageDispatcher17PostMultiMessagesEPNS_4TaskEPNS0_21ArgumentWithBarrierExEia
          (long param_1,long param_2,ushort *param_3,int param_4,char param_5)

{
  int *piVar1;
  ushort *puVar2;
  uint uVar3;
  uint uVar4;
  short sVar5;
  ushort uVar6;
  char cVar7;
  bool bVar8;
  ulong uVar9;
  int iVar10;
  long lVar11;
  int *piVar12;
  long lVar13;
  undefined8 uVar14;
  long lVar15;
  long lVar16;
  undefined4 uVar17;
  
  uVar4 = *(uint *)(param_3 + 0x14);
  piVar12 = (int *)(param_1 + 0x40);
  iVar10 = 0;
code_r0x02060ab0:
  do {
    if (*piVar12 != -1) {
      ClearExclusiveLocal();
      bVar8 = iVar10 < 0x1ff;
      iVar10 = iVar10 + 1;
      if (bVar8) goto code_r0x02060ab0;
      piVar1 = (int *)(param_1 + 0x44);
      do {
        cVar7 = '\x01';
        bVar8 = (bool)ExclusiveMonitorPass(piVar1,0x10);
        if (bVar8) {
          *piVar1 = *piVar1 + 1;
          cVar7 = ExclusiveMonitorsStatus();
        }
      } while (cVar7 != '\0');
      do {
        if (*piVar12 != -1) {
          ClearExclusiveLocal();
          do {
            uVar9 = Aska::Semaphore::IsReady() const(param_1 + 0x80);
            if ((uVar9 & 1) == 0) {
              do {
                cVar7 = '\x01';
                bVar8 = (bool)ExclusiveMonitorPass(piVar1,0x10);
                if (bVar8) {
                  *piVar1 = *piVar1 + -1;
                  cVar7 = ExclusiveMonitorsStatus();
                }
              } while (cVar7 != '\0');
              Aska::Thread::Sleep(unsigned int)(1);
            }
            else {
              Aska::Semaphore::Wait() const(param_1 + 0x80);
            }
            do {
              cVar7 = '\x01';
              bVar8 = (bool)ExclusiveMonitorPass(piVar1,0x10);
              if (bVar8) {
                *piVar1 = *piVar1 + 1;
                cVar7 = ExclusiveMonitorsStatus();
              }
            } while (cVar7 != '\0');
            while (*piVar12 == -1) {
              cVar7 = '\x01';
              bVar8 = (bool)ExclusiveMonitorPass(piVar12,0x10);
              if (bVar8) {
                *piVar12 = 0;
                cVar7 = ExclusiveMonitorsStatus();
              }
              if (cVar7 == '\0') goto code_r0x02060b68;
            }
            ClearExclusiveLocal();
          } while( true );
        }
        cVar7 = '\x01';
        bVar8 = (bool)ExclusiveMonitorPass(piVar12,0x10);
        if (bVar8) {
          *piVar12 = 0;
          cVar7 = ExclusiveMonitorsStatus();
        }
      } while (cVar7 != '\0');
code_r0x02060b68:
      do {
        cVar7 = '\x01';
        bVar8 = (bool)ExclusiveMonitorPass(piVar1,0x10);
        if (bVar8) {
          *piVar1 = *piVar1 + -1;
          cVar7 = ExclusiveMonitorsStatus();
        }
      } while (cVar7 != '\0');
code_r0x02060b78:
      DataMemoryBarrier(2,3);
      if (param_4 < 1) {
        uVar17 = 1;
      }
      else {
        puVar2 = param_3 + (long)param_4 * 0x20;
        lVar15 = param_1 + 0xa0;
        if (param_2 == 0) {
          uVar17 = 1;
          do {
            *param_3 = *param_3 & 0x3fff;
            uVar3 = 0;
            if (*(int *)(param_1 + 0x124) + 1U < *(uint *)(param_1 + 0x128)) {
              uVar3 = *(int *)(param_1 + 0x124) + 1;
            }
            if (uVar3 == *(uint *)(param_1 + 0x120)) {
              *(undefined1 *)(param_1 + 0x1b0) = 1;
              Aska::Event::Reset() const(param_1 + 0x148);
              uVar17 = 0;
            }
            else {
              *(uint *)(param_1 + 0x124) = uVar3;
              lVar16 = *(long *)(*(long *)(param_1 + 0x130) + (ulong)uVar3 * 8);
              for (lVar11 = *(long *)(param_1 + 0xa8); lVar15 != lVar11;
                  lVar11 = *(long *)(lVar11 + 8)) {
                if (param_5 <= *(char *)(lVar11 + 0x68)) {
                  lVar13 = *(long *)(lVar11 + 0x10);
                  *(long *)(lVar16 + 8) = lVar11;
                  *(long *)(lVar16 + 0x10) = lVar13;
                  *(long *)(lVar13 + 8) = lVar16;
                  *(long *)(lVar11 + 0x10) = lVar16;
                  goto code_r0x02060d9c;
                }
              }
              lVar11 = *(long *)(param_1 + 0xb0);
              *(long *)(lVar16 + 8) = lVar15;
              *(long *)(lVar16 + 0x10) = lVar11;
              *(long *)(lVar11 + 8) = lVar16;
              *(long *)(param_1 + 0xb0) = lVar16;
code_r0x02060d9c:
              *(int *)(param_1 + 0x110) = *(int *)(param_1 + 0x110) + 1;
              *(char *)(lVar16 + 0x68) = param_5;
              memset(lVar16 + 0x18,0,0x50);
              uVar6 = *(ushort *)(param_1 + 0x1ca);
              *(ushort *)(param_1 + 0x1ca) = uVar6 + 1;
              *(ushort *)(lVar16 + 0x18) = uVar6;
              *(ushort *)(lVar16 + 0x1a) = *param_3;
              uVar14 = *(undefined8 *)(param_3 + 4);
              *(undefined8 *)(lVar16 + 0x30) = 0;
              *(uint *)(lVar16 + 0x38) = uVar4;
              *(undefined8 *)(lVar16 + 0x20) = uVar14;
              *(undefined8 *)(lVar16 + 0x48) = *(undefined8 *)(param_3 + 8);
              *(undefined8 *)(lVar16 + 0x50) = *(undefined8 *)(param_3 + 0xc);
              *(undefined8 *)(lVar16 + 0x58) = *(undefined8 *)(param_3 + 0x18);
              *(undefined8 *)(lVar16 + 0x60) = *(undefined8 *)(param_3 + 0x1c);
              if (*(uint **)(param_3 + 0x10) != (uint *)0x0) {
                **(uint **)(param_3 + 0x10) = (uint)uVar6;
              }
            }
            param_3 = param_3 + 0x20;
          } while (param_3 < puVar2);
        }
        else {
          uVar17 = 1;
          do {
            *param_3 = *param_3 & 0x3fff;
            uVar3 = 0;
            if (*(int *)(param_1 + 0x124) + 1U < *(uint *)(param_1 + 0x128)) {
              uVar3 = *(int *)(param_1 + 0x124) + 1;
            }
            if (uVar3 == *(uint *)(param_1 + 0x120)) {
              *(undefined1 *)(param_1 + 0x1b0) = 1;
              Aska::Event::Reset() const(param_1 + 0x148);
              uVar17 = 0;
            }
            else {
              *(uint *)(param_1 + 0x124) = uVar3;
              lVar16 = *(long *)(*(long *)(param_1 + 0x130) + (ulong)uVar3 * 8);
              for (lVar11 = *(long *)(param_1 + 0xa8); lVar15 != lVar11;
                  lVar11 = *(long *)(lVar11 + 8)) {
                if (param_5 <= *(char *)(lVar11 + 0x68)) {
                  lVar13 = *(long *)(lVar11 + 0x10);
                  *(long *)(lVar16 + 8) = lVar11;
                  *(long *)(lVar16 + 0x10) = lVar13;
                  *(long *)(lVar13 + 8) = lVar16;
                  *(long *)(lVar11 + 0x10) = lVar16;
                  goto code_r0x02060c3c;
                }
              }
              lVar11 = *(long *)(param_1 + 0xb0);
              *(long *)(lVar16 + 8) = lVar15;
              *(long *)(lVar16 + 0x10) = lVar11;
              *(long *)(lVar11 + 8) = lVar16;
              *(long *)(param_1 + 0xb0) = lVar16;
code_r0x02060c3c:
              *(int *)(param_1 + 0x110) = *(int *)(param_1 + 0x110) + 1;
              *(char *)(lVar16 + 0x68) = param_5;
              memset((ushort *)(lVar16 + 0x18),0,0x50);
              sVar5 = *(short *)(param_1 + 0x1ca);
              *(short *)(param_1 + 0x1ca) = sVar5 + 1;
              *(short *)(lVar16 + 0x18) = sVar5;
              *(ushort *)(lVar16 + 0x1a) = *param_3;
              *(undefined8 *)(lVar16 + 0x20) = *(undefined8 *)(param_3 + 4);
              lVar11 = *(long *)(param_2 + 0x18);
              *(uint *)(lVar16 + 0x38) = uVar4;
              *(long *)(lVar16 + 0x30) = lVar11;
              *(undefined8 *)(lVar16 + 0x48) = *(undefined8 *)(param_3 + 8);
              *(undefined8 *)(lVar16 + 0x50) = *(undefined8 *)(param_3 + 0xc);
              *(undefined8 *)(lVar16 + 0x58) = *(undefined8 *)(param_3 + 0x18);
              *(undefined8 *)(lVar16 + 0x60) = *(undefined8 *)(param_3 + 0x1c);
              if ((uVar4 < 0x20) && (lVar11 != 0)) {
                Aska::TaskManager::AddThreadBarrier(int)(lVar11,uVar4);
                Aska::TaskManager::IncrementThreadBarrierCount(int)(lVar11,uVar4);
              }
              if (*(uint **)(param_3 + 0x10) != (uint *)0x0) {
                **(uint **)(param_3 + 0x10) = (uint)*(ushort *)(lVar16 + 0x18);
              }
            }
            param_3 = param_3 + 0x20;
          } while (param_3 < puVar2);
        }
      }
      DataMemoryBarrier(2,3);
      *(undefined4 *)(param_1 + 0x40) = 0xffffffff;
      DataMemoryBarrier(2,3);
      piVar12 = (int *)(param_1 + 0x44);
      if (0x14 < *piVar12) {
        do {
          cVar7 = '\x01';
          bVar8 = (bool)ExclusiveMonitorPass(piVar12,0x10);
          if (bVar8) {
            *piVar12 = *piVar12 + -1;
            cVar7 = ExclusiveMonitorsStatus();
          }
        } while (cVar7 != '\0');
        uVar9 = Aska::Semaphore::IsReady() const(param_1 + 0x80);
        if ((uVar9 & 1) != 0) {
          Aska::Semaphore::Signal() const(param_1 + 0x80);
        }
      }
      uVar9 = (ulong)*(uint *)(param_1 + 0x1b8);
      if (0 < (int)*(uint *)(param_1 + 0x1b8)) {
        lVar15 = 0x84;
        do {
          if (*(char *)(*(long *)(param_1 + 0x1c0) + lVar15) != '\0') {
            Aska::Event::Set() const(*(long *)(param_1 + 0x1c0) + lVar15 + -0x6c);
          }
          uVar9 = uVar9 - 1;
          lVar15 = lVar15 + 0xe0;
        } while (uVar9 != 0);
      }
      return uVar17;
    }
    cVar7 = '\x01';
    bVar8 = (bool)ExclusiveMonitorPass(piVar12,0x10);
    if (bVar8) {
      *piVar12 = 0;
      cVar7 = ExclusiveMonitorsStatus();
    }
    if (cVar7 == '\0') goto code_r0x02060b78;
  } while( true );
}

// ==== Aska::SimpleMessageDispatcher::SendMessage(Aska::Task*, int, unsigned short, Aska::INotify*, void*, void*, signed char)
// vaddr 0x1f60ebc | ghidra 0x2060ebc | size 976 | symbol _ZN4Aska23SimpleMessageDispatcher11SendMessageEPNS_4TaskEitPNS_7INotifyEPvS5_a | lib libSOA-3.7.0.so | 2026-10-04
undefined4
_ZN4Aska23SimpleMessageDispatcher11SendMessageEPNS_4TaskEitPNS_7INotifyEPvS5_a
          (long param_1,long param_2,uint param_3,ushort param_4,undefined8 param_5,
          undefined8 param_6,undefined8 param_7,char param_8)

{
  int *piVar1;
  uint uVar2;
  short sVar3;
  char cVar4;
  bool bVar5;
  bool bVar6;
  undefined1 *puVar7;
  ulong uVar8;
  int iVar9;
  long lVar10;
  int *piVar11;
  long lVar12;
  undefined4 uVar13;
  long lVar14;
  long lVar15;
  undefined1 auStack_c8 [104];
  
  lVar14 = param_1 + 8;
  piVar11 = (int *)(param_1 + 0x40);
  iVar9 = 0;
code_r0x02060f04:
  if (*piVar11 == -1) {
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar11,0x10);
    if (bVar5) {
      *piVar11 = 0;
      cVar4 = ExclusiveMonitorsStatus();
    }
    if (cVar4 == '\0') goto code_r0x02060fd8;
    goto code_r0x02060f04;
  }
  ClearExclusiveLocal();
  bVar5 = iVar9 < 0x1ff;
  iVar9 = iVar9 + 1;
  if (bVar5) goto code_r0x02060f04;
  piVar1 = (int *)(param_1 + 0x44);
  do {
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar5) {
      *piVar1 = *piVar1 + 1;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
  do {
    if (*piVar11 != -1) {
      ClearExclusiveLocal();
      uVar8 = Aska::Semaphore::IsReady() const();
      if ((uVar8 & 1) == 0) goto code_r0x02060f8c;
      do {
        Aska::Semaphore::Wait() const(param_1 + 0x80);
        while( true ) {
          do {
            cVar4 = '\x01';
            bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
            if (bVar5) {
              *piVar1 = *piVar1 + 1;
              cVar4 = ExclusiveMonitorsStatus();
            }
          } while (cVar4 != '\0');
          while (*piVar11 == -1) {
            cVar4 = '\x01';
            bVar5 = (bool)ExclusiveMonitorPass(piVar11,0x10);
            if (bVar5) {
              *piVar11 = 0;
              cVar4 = ExclusiveMonitorsStatus();
            }
            if (cVar4 == '\0') goto code_r0x02060fc8;
          }
          ClearExclusiveLocal();
          uVar8 = Aska::Semaphore::IsReady() const(param_1 + 0x80);
          if ((uVar8 & 1) != 0) break;
code_r0x02060f8c:
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
      } while( true );
    }
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar11,0x10);
    if (bVar5) {
      *piVar11 = 0;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
code_r0x02060fc8:
  do {
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar5) {
      *piVar1 = *piVar1 + -1;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
code_r0x02060fd8:
  DataMemoryBarrier(2,3);
  uVar2 = 0;
  if (*(int *)(param_1 + 0x124) + 1U < *(uint *)(param_1 + 0x128)) {
    uVar2 = *(int *)(param_1 + 0x124) + 1;
  }
  if (uVar2 == *(uint *)(param_1 + 0x120)) {
    *(undefined1 *)(param_1 + 0x1b0) = 1;
    Aska::Event::Reset() const(param_1 + 0x148);
    uVar13 = 0;
    goto code_r0x02061208;
  }
  *(uint *)(param_1 + 0x124) = uVar2;
  lVar10 = *(long *)(param_1 + 0xa8);
  lVar15 = *(long *)(*(long *)(param_1 + 0x130) + (ulong)uVar2 * 8);
  do {
    if (param_1 + 0xa0 == lVar10) {
      lVar10 = *(long *)(param_1 + 0xb0);
      *(long *)(lVar15 + 8) = param_1 + 0xa0;
      *(long *)(lVar15 + 0x10) = lVar10;
      *(long *)(lVar10 + 8) = lVar15;
      *(long *)(param_1 + 0xb0) = lVar15;
code_r0x02061070:
      *(int *)(param_1 + 0x110) = *(int *)(param_1 + 0x110) + 1;
      *(char *)(lVar15 + 0x68) = param_8;
      memset(lVar15 + 0x18,0,0x50);
      if (param_2 == 0) {
        lVar10 = 0;
      }
      else {
        lVar10 = *(long *)(param_2 + 0x18);
      }
      puVar7 = auStack_c8;
      Aska::Event::Event()(auStack_c8);
      uVar8 = Aska::Event::Create(bool, bool)(auStack_c8,1,0);
      if ((uVar8 & 1) == 0) {
        puVar7 = (undefined1 *)
                 Aska::EventPool::Scoop()(*(undefined8 *)PTR__ZN4Aska6Global12m_pEventPoolE_02cbc1a8);
        if (puVar7 != (undefined1 *)0x0) {
          bVar5 = true;
          goto code_r0x020610e4;
        }
        uVar13 = 0;
      }
      else {
        bVar5 = false;
code_r0x020610e4:
        sVar3 = *(short *)(param_1 + 0x1ca);
        *(short *)(param_1 + 0x1ca) = sVar3 + 1;
        *(short *)(lVar15 + 0x18) = sVar3;
        *(ushort *)(lVar15 + 0x1a) = param_4 & 0x3fff | 0x8000;
        *(undefined8 *)(lVar15 + 0x20) = param_5;
        *(undefined1 **)(lVar15 + 0x28) = puVar7;
        *(long *)(lVar15 + 0x30) = lVar10;
        *(uint *)(lVar15 + 0x38) = param_3;
        *(undefined8 *)(lVar15 + 0x48) = param_6;
        *(undefined8 *)(lVar15 + 0x50) = param_7;
        *(undefined8 *)(lVar15 + 0x58) = 0;
        *(undefined8 *)(lVar15 + 0x60) = 0;
        if ((param_3 < 0x20) && (lVar10 != 0)) {
          Aska::TaskManager::AddThreadBarrier(int)(lVar10,param_3);
          Aska::TaskManager::IncrementThreadBarrierCount(int)(lVar10,param_3);
        }
        DataMemoryBarrier(2,3);
        *(undefined4 *)(param_1 + 0x40) = 0xffffffff;
        DataMemoryBarrier(2,3);
        piVar11 = (int *)(param_1 + 0x44);
        if (0x14 < *piVar11) {
          do {
            cVar4 = '\x01';
            bVar6 = (bool)ExclusiveMonitorPass(piVar11,0x10);
            if (bVar6) {
              *piVar11 = *piVar11 + -1;
              cVar4 = ExclusiveMonitorsStatus();
            }
          } while (cVar4 != '\0');
          uVar8 = Aska::Semaphore::IsReady() const(param_1 + 0x80);
          if ((uVar8 & 1) != 0) {
            Aska::Semaphore::Signal() const(param_1 + 0x80);
          }
        }
        iVar9 = *(int *)(param_1 + 0x1b8);
        if (0 < iVar9) {
          lVar10 = 0;
          lVar14 = 0;
          do {
            lVar15 = *(long *)(param_1 + 0x1c0) + lVar10;
            if ((*(char *)(lVar15 + 0x84) != '\0') && (*(char *)(lVar15 + 0x83) == '\0')) {
              lVar15 = *(long *)(param_1 + 0x1c0) + lVar10 + 0x18;
              uVar8 = Aska::Event::IsSignal() const(lVar15);
              if ((uVar8 & 1) == 0) {
                Aska::Event::Set() const(lVar15);
                break;
              }
            }
            lVar14 = lVar14 + 1;
            lVar10 = lVar10 + 0xe0;
          } while (lVar14 < iVar9);
        }
        if ((puVar7 != (undefined1 *)0x0) && (Aska::Event::Wait(unsigned int) const(puVar7,0), bVar5)) {
          Aska::EventPool::Sink(Aska::Event*)(*(undefined8 *)PTR__ZN4Aska6Global12m_pEventPoolE_02cbc1a8,puVar7);
        }
        lVar14 = 0;
        uVar13 = 1;
      }
      Aska::Event::Exit()(auStack_c8);
      if (lVar14 == 0) {
        return uVar13;
      }
code_r0x02061208:
      DataMemoryBarrier(2,3);
      *(undefined4 *)(lVar14 + 0x38) = 0xffffffff;
      DataMemoryBarrier(2,3);
      piVar11 = (int *)(lVar14 + 0x3c);
      if (0x14 < *piVar11) {
        do {
          cVar4 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(piVar11,0x10);
          if (bVar5) {
            *piVar11 = *piVar11 + -1;
            cVar4 = ExclusiveMonitorsStatus();
          }
        } while (cVar4 != '\0');
        uVar8 = Aska::Semaphore::IsReady() const(lVar14 + 0x78);
        if ((uVar8 & 1) != 0) {
          Aska::Semaphore::Signal() const(lVar14 + 0x78);
        }
      }
      return uVar13;
    }
    if (param_8 <= *(char *)(lVar10 + 0x68)) {
      lVar12 = *(long *)(lVar10 + 0x10);
      *(long *)(lVar15 + 8) = lVar10;
      *(long *)(lVar15 + 0x10) = lVar12;
      *(long *)(lVar12 + 8) = lVar15;
      *(long *)(lVar10 + 0x10) = lVar15;
      goto code_r0x02061070;
    }
    lVar10 = *(long *)(lVar10 + 8);
  } while( true );
}

// ==== Aska::SimpleMessageDispatcher::SendMessage(Aska::Task*, int, unsigned short, Aska::INotify*, void*, void*, unsigned long, unsigned long, signed char)
// vaddr 0x1f6128c | ghidra 0x206128c | size 1048 | symbol _ZN4Aska23SimpleMessageDispatcher11SendMessageEPNS_4TaskEitPNS_7INotifyEPvS5_mma | lib libSOA-3.7.0.so | 2026-10-04
undefined4
_ZN4Aska23SimpleMessageDispatcher11SendMessageEPNS_4TaskEitPNS_7INotifyEPvS5_mma
          (long param_1,long param_2,uint param_3,ushort param_4,undefined8 param_5,
          undefined8 param_6,undefined8 param_7,undefined8 param_8,undefined8 param_9,char param_10)

{
  int *piVar1;
  uint uVar2;
  short sVar3;
  char cVar4;
  bool bVar5;
  bool bVar6;
  undefined1 *puVar7;
  ulong uVar8;
  int iVar9;
  long lVar10;
  int *piVar11;
  long lVar12;
  undefined4 uVar13;
  long lVar14;
  long lVar15;
  undefined1 auStack_c8 [104];
  
  lVar15 = param_1 + 8;
  piVar11 = (int *)(param_1 + 0x40);
  iVar9 = 0;
code_r0x020612c8:
  do {
    if (*piVar11 == -1) goto code_r0x020612d4;
    ClearExclusiveLocal();
    bVar5 = iVar9 < 0x1ff;
    iVar9 = iVar9 + 1;
  } while (bVar5);
  piVar1 = (int *)(param_1 + 0x44);
  do {
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar5) {
      *piVar1 = *piVar1 + 1;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
  do {
    if (*piVar11 != -1) {
      ClearExclusiveLocal();
      do {
        uVar8 = Aska::Semaphore::IsReady() const();
        if ((uVar8 & 1) == 0) {
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
          Aska::Semaphore::Wait() const(param_1 + 0x80);
        }
        do {
          cVar4 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar5) {
            *piVar1 = *piVar1 + 1;
            cVar4 = ExclusiveMonitorsStatus();
          }
        } while (cVar4 != '\0');
        while (*piVar11 == -1) {
          cVar4 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(piVar11,0x10);
          if (bVar5) {
            *piVar11 = 0;
            cVar4 = ExclusiveMonitorsStatus();
          }
          if (cVar4 == '\0') goto code_r0x0206167c;
        }
        ClearExclusiveLocal();
      } while( true );
    }
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar11,0x10);
    if (bVar5) {
      *piVar11 = 0;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
code_r0x0206167c:
  do {
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar5) {
      *piVar1 = *piVar1 + -1;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
  DataMemoryBarrier(2,3);
  goto code_r0x02061330;
code_r0x020612d4:
  cVar4 = '\x01';
  bVar5 = (bool)ExclusiveMonitorPass(piVar11,0x10);
  if (bVar5) {
    *piVar11 = 0;
    cVar4 = ExclusiveMonitorsStatus();
  }
  if (cVar4 == '\0') goto code_r0x0206132c;
  goto code_r0x020612c8;
code_r0x0206132c:
  DataMemoryBarrier(2,3);
code_r0x02061330:
  uVar2 = 0;
  if (*(int *)(param_1 + 0x124) + 1U < *(uint *)(param_1 + 0x128)) {
    uVar2 = *(int *)(param_1 + 0x124) + 1;
  }
  if (uVar2 == *(uint *)(param_1 + 0x120)) {
    *(undefined1 *)(param_1 + 0x1b0) = 1;
    Aska::Event::Reset() const(param_1 + 0x148);
    uVar13 = 0;
    goto code_r0x02061580;
  }
  lVar10 = *(long *)(param_1 + 0xa8);
  *(uint *)(param_1 + 0x124) = uVar2;
  lVar14 = *(long *)(*(long *)(param_1 + 0x130) + (ulong)uVar2 * 8);
  for (; param_1 + 0xa0 != lVar10; lVar10 = *(long *)(lVar10 + 8)) {
    if (param_10 <= *(char *)(lVar10 + 0x68)) {
      lVar12 = *(long *)(lVar10 + 0x10);
      *(long *)(lVar14 + 8) = lVar10;
      *(long *)(lVar14 + 0x10) = lVar12;
      *(long *)(lVar12 + 8) = lVar14;
      *(long *)(lVar10 + 0x10) = lVar14;
      goto code_r0x020613e4;
    }
  }
  lVar10 = *(long *)(param_1 + 0xb0);
  *(long *)(lVar14 + 8) = param_1 + 0xa0;
  *(long *)(lVar14 + 0x10) = lVar10;
  *(long *)(lVar10 + 8) = lVar14;
  *(long *)(param_1 + 0xb0) = lVar14;
code_r0x020613e4:
  *(int *)(param_1 + 0x110) = *(int *)(param_1 + 0x110) + 1;
  *(char *)(lVar14 + 0x68) = param_10;
  memset(lVar14 + 0x18,0,0x50);
  if (param_2 == 0) {
    lVar10 = 0;
  }
  else {
    lVar10 = *(long *)(param_2 + 0x18);
  }
  puVar7 = auStack_c8;
  Aska::Event::Event()(auStack_c8);
  uVar8 = Aska::Event::Create(bool, bool)(auStack_c8,1,0);
  if ((uVar8 & 1) == 0) {
    puVar7 = (undefined1 *)
             Aska::EventPool::Scoop()(*(undefined8 *)PTR__ZN4Aska6Global12m_pEventPoolE_02cbc1a8);
    if (puVar7 != (undefined1 *)0x0) {
      bVar5 = true;
      goto code_r0x02061458;
    }
    uVar13 = 0;
  }
  else {
    bVar5 = false;
code_r0x02061458:
    sVar3 = *(short *)(param_1 + 0x1ca);
    *(short *)(param_1 + 0x1ca) = sVar3 + 1;
    *(short *)(lVar14 + 0x18) = sVar3;
    *(ushort *)(lVar14 + 0x1a) = param_4 & 0x3fff | 0x8000;
    *(undefined8 *)(lVar14 + 0x20) = param_5;
    *(undefined1 **)(lVar14 + 0x28) = puVar7;
    *(long *)(lVar14 + 0x30) = lVar10;
    *(uint *)(lVar14 + 0x38) = param_3;
    *(undefined8 *)(lVar14 + 0x48) = param_6;
    *(undefined8 *)(lVar14 + 0x50) = param_7;
    *(undefined8 *)(lVar14 + 0x58) = param_8;
    *(undefined8 *)(lVar14 + 0x60) = param_9;
    if ((param_3 < 0x20) && (lVar10 != 0)) {
      Aska::TaskManager::AddThreadBarrier(int)(lVar10,param_3);
      Aska::TaskManager::IncrementThreadBarrierCount(int)(lVar10,param_3);
    }
    DataMemoryBarrier(2,3);
    *(undefined4 *)(param_1 + 0x40) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar11 = (int *)(param_1 + 0x44);
    if (0x14 < *piVar11) {
      do {
        cVar4 = '\x01';
        bVar6 = (bool)ExclusiveMonitorPass(piVar11,0x10);
        if (bVar6) {
          *piVar11 = *piVar11 + -1;
          cVar4 = ExclusiveMonitorsStatus();
        }
      } while (cVar4 != '\0');
      uVar8 = Aska::Semaphore::IsReady() const(param_1 + 0x80);
      if ((uVar8 & 1) != 0) {
        Aska::Semaphore::Signal() const(param_1 + 0x80);
      }
    }
    iVar9 = *(int *)(param_1 + 0x1b8);
    if (0 < iVar9) {
      lVar10 = 0;
      lVar15 = 0;
      do {
        lVar14 = *(long *)(param_1 + 0x1c0) + lVar10;
        if ((*(char *)(lVar14 + 0x84) != '\0') && (*(char *)(lVar14 + 0x83) == '\0')) {
          lVar14 = *(long *)(param_1 + 0x1c0) + lVar10 + 0x18;
          uVar8 = Aska::Event::IsSignal() const(lVar14);
          if ((uVar8 & 1) == 0) {
            Aska::Event::Set() const(lVar14);
            break;
          }
        }
        lVar15 = lVar15 + 1;
        lVar10 = lVar10 + 0xe0;
      } while (lVar15 < iVar9);
    }
    if ((puVar7 != (undefined1 *)0x0) && (Aska::Event::Wait(unsigned int) const(puVar7,0), bVar5)) {
      Aska::EventPool::Sink(Aska::Event*)(*(undefined8 *)PTR__ZN4Aska6Global12m_pEventPoolE_02cbc1a8,puVar7);
    }
    lVar15 = 0;
    uVar13 = 1;
  }
  Aska::Event::Exit()(auStack_c8);
  if (lVar15 == 0) {
    return uVar13;
  }
code_r0x02061580:
  DataMemoryBarrier(2,3);
  *(undefined4 *)(lVar15 + 0x38) = 0xffffffff;
  DataMemoryBarrier(2,3);
  piVar11 = (int *)(lVar15 + 0x3c);
  if (0x14 < *piVar11) {
    do {
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar11,0x10);
      if (bVar5) {
        *piVar11 = *piVar11 + -1;
        cVar4 = ExclusiveMonitorsStatus();
      }
    } while (cVar4 != '\0');
    uVar8 = Aska::Semaphore::IsReady() const(lVar15 + 0x78);
    if ((uVar8 & 1) != 0) {
      Aska::Semaphore::Signal() const(lVar15 + 0x78);
    }
  }
  return uVar13;
}

// ==== Aska::SimpleMessageDispatcher::SendMessageHigh(Aska::Task*, int, unsigned short, Aska::INotify*, void*, void*)
// vaddr 0x1f616a4 | ghidra 0x20616a4 | size 904 | symbol _ZN4Aska23SimpleMessageDispatcher15SendMessageHighEPNS_4TaskEitPNS_7INotifyEPvS5_ | lib libSOA-3.7.0.so | 2026-10-04
undefined4
_ZN4Aska23SimpleMessageDispatcher15SendMessageHighEPNS_4TaskEitPNS_7INotifyEPvS5_
          (long param_1,long param_2,uint param_3,ushort param_4,undefined8 param_5,
          undefined8 param_6,undefined8 param_7)

{
  int *piVar1;
  uint uVar2;
  short sVar3;
  char cVar4;
  bool bVar5;
  bool bVar6;
  undefined1 *puVar7;
  ulong uVar8;
  int iVar9;
  long lVar10;
  int *piVar11;
  undefined4 uVar12;
  long lVar13;
  long lVar14;
  undefined1 auStack_c8 [104];
  
  lVar13 = param_1 + 8;
  piVar11 = (int *)(param_1 + 0x40);
  iVar9 = 0;
  do {
    while (*piVar11 == -1) {
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar11,0x10);
      if (bVar5) {
        *piVar11 = 0;
        cVar4 = ExclusiveMonitorsStatus();
      }
      if (cVar4 == '\0') goto code_r0x020617b0;
    }
    ClearExclusiveLocal();
    bVar5 = iVar9 < 0x1ff;
    iVar9 = iVar9 + 1;
  } while (bVar5);
  piVar1 = (int *)(param_1 + 0x44);
  do {
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar5) {
      *piVar1 = *piVar1 + 1;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
  do {
    if (*piVar11 != -1) {
      ClearExclusiveLocal();
      do {
        uVar8 = Aska::Semaphore::IsReady() const(param_1 + 0x80);
        if ((uVar8 & 1) == 0) {
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
          Aska::Semaphore::Wait() const(param_1 + 0x80);
        }
        do {
          cVar4 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar5) {
            *piVar1 = *piVar1 + 1;
            cVar4 = ExclusiveMonitorsStatus();
          }
        } while (cVar4 != '\0');
        while (*piVar11 == -1) {
          cVar4 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(piVar11,0x10);
          if (bVar5) {
            *piVar11 = 0;
            cVar4 = ExclusiveMonitorsStatus();
          }
          if (cVar4 == '\0') goto code_r0x020617a0;
        }
        ClearExclusiveLocal();
      } while( true );
    }
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar11,0x10);
    if (bVar5) {
      *piVar11 = 0;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
code_r0x020617a0:
  do {
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar5) {
      *piVar1 = *piVar1 + -1;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
code_r0x020617b0:
  DataMemoryBarrier(2,3);
  uVar2 = 0;
  if (*(int *)(param_1 + 0x124) + 1U < *(uint *)(param_1 + 0x128)) {
    uVar2 = *(int *)(param_1 + 0x124) + 1;
  }
  if (uVar2 == *(uint *)(param_1 + 0x120)) {
    *(undefined1 *)(param_1 + 0x1b0) = 1;
    Aska::Event::Reset() const(param_1 + 0x148);
    uVar12 = 0;
    goto code_r0x020619a8;
  }
  *(uint *)(param_1 + 0x124) = uVar2;
  lVar14 = *(long *)(*(long *)(param_1 + 0x130) + (ulong)uVar2 * 8);
  lVar10 = *(long *)(param_1 + 0xb0);
  *(long *)(lVar14 + 8) = param_1 + 0xa0;
  *(long *)(lVar14 + 0x10) = lVar10;
  *(long *)(lVar10 + 8) = lVar14;
  *(long *)(param_1 + 0xb0) = lVar14;
  *(int *)(param_1 + 0x110) = *(int *)(param_1 + 0x110) + 1;
  *(undefined1 *)(lVar14 + 0x68) = 0x7f;
  memset(lVar14 + 0x18,0,0x50);
  if (param_2 == 0) {
    lVar10 = 0;
  }
  else {
    lVar10 = *(long *)(param_2 + 0x18);
  }
  puVar7 = auStack_c8;
  Aska::Event::Event()(auStack_c8);
  uVar8 = Aska::Event::Create(bool, bool)(auStack_c8,1,0);
  if ((uVar8 & 1) == 0) {
    puVar7 = (undefined1 *)
             Aska::EventPool::Scoop()(*(undefined8 *)PTR__ZN4Aska6Global12m_pEventPoolE_02cbc1a8);
    if (puVar7 != (undefined1 *)0x0) {
      bVar5 = true;
      goto code_r0x02061884;
    }
    uVar12 = 0;
  }
  else {
    bVar5 = false;
code_r0x02061884:
    sVar3 = *(short *)(param_1 + 0x1ca);
    *(short *)(param_1 + 0x1ca) = sVar3 + 1;
    *(short *)(lVar14 + 0x18) = sVar3;
    *(ushort *)(lVar14 + 0x1a) = param_4 & 0x3fff | 0x8000;
    *(undefined8 *)(lVar14 + 0x20) = param_5;
    *(undefined1 **)(lVar14 + 0x28) = puVar7;
    *(long *)(lVar14 + 0x30) = lVar10;
    *(uint *)(lVar14 + 0x38) = param_3;
    *(undefined8 *)(lVar14 + 0x48) = param_6;
    *(undefined8 *)(lVar14 + 0x50) = param_7;
    *(undefined8 *)(lVar14 + 0x58) = 0;
    *(undefined8 *)(lVar14 + 0x60) = 0;
    if ((param_3 < 0x20) && (lVar10 != 0)) {
      Aska::TaskManager::AddThreadBarrier(int)(lVar10,param_3);
      Aska::TaskManager::IncrementThreadBarrierCount(int)(lVar10,param_3);
    }
    DataMemoryBarrier(2,3);
    *(undefined4 *)(param_1 + 0x40) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar11 = (int *)(param_1 + 0x44);
    if (0x14 < *piVar11) {
      do {
        cVar4 = '\x01';
        bVar6 = (bool)ExclusiveMonitorPass(piVar11,0x10);
        if (bVar6) {
          *piVar11 = *piVar11 + -1;
          cVar4 = ExclusiveMonitorsStatus();
        }
      } while (cVar4 != '\0');
      uVar8 = Aska::Semaphore::IsReady() const(param_1 + 0x80);
      if ((uVar8 & 1) != 0) {
        Aska::Semaphore::Signal() const(param_1 + 0x80);
      }
    }
    iVar9 = *(int *)(param_1 + 0x1b8);
    if (0 < iVar9) {
      lVar10 = 0;
      lVar13 = 0;
      do {
        lVar14 = *(long *)(param_1 + 0x1c0) + lVar10;
        if ((*(char *)(lVar14 + 0x84) != '\0') && (*(char *)(lVar14 + 0x83) == '\0')) {
          lVar14 = *(long *)(param_1 + 0x1c0) + lVar10 + 0x18;
          uVar8 = Aska::Event::IsSignal() const(lVar14);
          if ((uVar8 & 1) == 0) {
            Aska::Event::Set() const(lVar14);
            break;
          }
        }
        lVar13 = lVar13 + 1;
        lVar10 = lVar10 + 0xe0;
      } while (lVar13 < iVar9);
    }
    if ((puVar7 != (undefined1 *)0x0) && (Aska::Event::Wait(unsigned int) const(puVar7,0), bVar5)) {
      Aska::EventPool::Sink(Aska::Event*)(*(undefined8 *)PTR__ZN4Aska6Global12m_pEventPoolE_02cbc1a8,puVar7);
    }
    lVar13 = 0;
    uVar12 = 1;
  }
  Aska::Event::Exit()(auStack_c8);
  if (lVar13 == 0) {
    return uVar12;
  }
code_r0x020619a8:
  DataMemoryBarrier(2,3);
  *(undefined4 *)(lVar13 + 0x38) = 0xffffffff;
  DataMemoryBarrier(2,3);
  piVar11 = (int *)(lVar13 + 0x3c);
  if (0x14 < *piVar11) {
    do {
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar11,0x10);
      if (bVar5) {
        *piVar11 = *piVar11 + -1;
        cVar4 = ExclusiveMonitorsStatus();
      }
    } while (cVar4 != '\0');
    uVar8 = Aska::Semaphore::IsReady() const(lVar13 + 0x78);
    if ((uVar8 & 1) != 0) {
      Aska::Semaphore::Signal() const(lVar13 + 0x78);
    }
  }
  return uVar12;
}

// ==== Aska::SimpleMessageDispatcher::SendMessageHigh(Aska::Task*, int, unsigned short, Aska::INotify*, void*, void*, unsigned long, unsigned long)
// vaddr 0x1f61a2c | ghidra 0x2061a2c | size 984 | symbol _ZN4Aska23SimpleMessageDispatcher15SendMessageHighEPNS_4TaskEitPNS_7INotifyEPvS5_mm | lib libSOA-3.7.0.so | 2026-10-04
undefined4
_ZN4Aska23SimpleMessageDispatcher15SendMessageHighEPNS_4TaskEitPNS_7INotifyEPvS5_mm
          (long param_1,long param_2,uint param_3,ushort param_4,undefined8 param_5,
          undefined8 param_6,undefined8 param_7,undefined8 param_8,undefined8 param_9)

{
  int *piVar1;
  uint uVar2;
  short sVar3;
  char cVar4;
  bool bVar5;
  bool bVar6;
  undefined1 *puVar7;
  ulong uVar8;
  int iVar9;
  long lVar10;
  int *piVar11;
  undefined4 uVar12;
  long lVar13;
  long lVar14;
  undefined1 auStack_c8 [104];
  
  lVar14 = param_1 + 8;
  piVar11 = (int *)(param_1 + 0x40);
  iVar9 = 0;
code_r0x02061a68:
  do {
    if (*piVar11 == -1) goto code_r0x02061a74;
    ClearExclusiveLocal();
    bVar5 = iVar9 < 0x1ff;
    iVar9 = iVar9 + 1;
  } while (bVar5);
  piVar1 = (int *)(param_1 + 0x44);
  do {
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar5) {
      *piVar1 = *piVar1 + 1;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
  do {
    if (*piVar11 != -1) {
      ClearExclusiveLocal();
      do {
        uVar8 = Aska::Semaphore::IsReady() const();
        if ((uVar8 & 1) == 0) {
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
          Aska::Semaphore::Wait() const(param_1 + 0x80);
        }
        do {
          cVar4 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar5) {
            *piVar1 = *piVar1 + 1;
            cVar4 = ExclusiveMonitorsStatus();
          }
        } while (cVar4 != '\0');
        while (*piVar11 == -1) {
          cVar4 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(piVar11,0x10);
          if (bVar5) {
            *piVar11 = 0;
            cVar4 = ExclusiveMonitorsStatus();
          }
          if (cVar4 == '\0') goto code_r0x02061dd4;
        }
        ClearExclusiveLocal();
      } while( true );
    }
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar11,0x10);
    if (bVar5) {
      *piVar11 = 0;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
code_r0x02061dd4:
  do {
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar5) {
      *piVar1 = *piVar1 + -1;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
  DataMemoryBarrier(2,3);
  goto code_r0x02061ad8;
code_r0x02061a74:
  cVar4 = '\x01';
  bVar5 = (bool)ExclusiveMonitorPass(piVar11,0x10);
  if (bVar5) {
    *piVar11 = 0;
    cVar4 = ExclusiveMonitorsStatus();
  }
  if (cVar4 == '\0') goto code_r0x02061ad4;
  goto code_r0x02061a68;
code_r0x02061ad4:
  DataMemoryBarrier(2,3);
code_r0x02061ad8:
  uVar2 = 0;
  if (*(int *)(param_1 + 0x124) + 1U < *(uint *)(param_1 + 0x128)) {
    uVar2 = *(int *)(param_1 + 0x124) + 1;
  }
  if (uVar2 == *(uint *)(param_1 + 0x120)) {
    *(undefined1 *)(param_1 + 0x1b0) = 1;
    Aska::Event::Reset() const(param_1 + 0x148);
    uVar12 = 0;
    goto code_r0x02061ce8;
  }
  *(uint *)(param_1 + 0x124) = uVar2;
  lVar13 = *(long *)(*(long *)(param_1 + 0x130) + (ulong)uVar2 * 8);
  lVar10 = *(long *)(param_1 + 0xb0);
  *(long *)(lVar13 + 8) = param_1 + 0xa0;
  *(long *)(lVar13 + 0x10) = lVar10;
  *(long *)(lVar10 + 8) = lVar13;
  *(long *)(param_1 + 0xb0) = lVar13;
  *(int *)(param_1 + 0x110) = *(int *)(param_1 + 0x110) + 1;
  *(undefined1 *)(lVar13 + 0x68) = 0x7f;
  memset(lVar13 + 0x18,0,0x50);
  if (param_2 == 0) {
    lVar10 = 0;
  }
  else {
    lVar10 = *(long *)(param_2 + 0x18);
  }
  puVar7 = auStack_c8;
  Aska::Event::Event()(auStack_c8);
  uVar8 = Aska::Event::Create(bool, bool)(auStack_c8,1,0);
  if ((uVar8 & 1) == 0) {
    puVar7 = (undefined1 *)
             Aska::EventPool::Scoop()(*(undefined8 *)PTR__ZN4Aska6Global12m_pEventPoolE_02cbc1a8);
    if (puVar7 != (undefined1 *)0x0) {
      bVar5 = true;
      goto code_r0x02061bbc;
    }
    uVar12 = 0;
  }
  else {
    bVar5 = false;
code_r0x02061bbc:
    sVar3 = *(short *)(param_1 + 0x1ca);
    *(short *)(param_1 + 0x1ca) = sVar3 + 1;
    *(short *)(lVar13 + 0x18) = sVar3;
    *(ushort *)(lVar13 + 0x1a) = param_4 & 0x3fff | 0x8000;
    *(undefined8 *)(lVar13 + 0x20) = param_5;
    *(undefined1 **)(lVar13 + 0x28) = puVar7;
    *(long *)(lVar13 + 0x30) = lVar10;
    *(uint *)(lVar13 + 0x38) = param_3;
    *(undefined8 *)(lVar13 + 0x48) = param_6;
    *(undefined8 *)(lVar13 + 0x50) = param_7;
    *(undefined8 *)(lVar13 + 0x58) = param_8;
    *(undefined8 *)(lVar13 + 0x60) = param_9;
    if ((param_3 < 0x20) && (lVar10 != 0)) {
      Aska::TaskManager::AddThreadBarrier(int)(lVar10,param_3);
      Aska::TaskManager::IncrementThreadBarrierCount(int)(lVar10,param_3);
    }
    DataMemoryBarrier(2,3);
    *(undefined4 *)(param_1 + 0x40) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar11 = (int *)(param_1 + 0x44);
    if (0x14 < *piVar11) {
      do {
        cVar4 = '\x01';
        bVar6 = (bool)ExclusiveMonitorPass(piVar11,0x10);
        if (bVar6) {
          *piVar11 = *piVar11 + -1;
          cVar4 = ExclusiveMonitorsStatus();
        }
      } while (cVar4 != '\0');
      uVar8 = Aska::Semaphore::IsReady() const(param_1 + 0x80);
      if ((uVar8 & 1) != 0) {
        Aska::Semaphore::Signal() const(param_1 + 0x80);
      }
    }
    iVar9 = *(int *)(param_1 + 0x1b8);
    if (0 < iVar9) {
      lVar10 = 0;
      lVar14 = 0;
      do {
        lVar13 = *(long *)(param_1 + 0x1c0) + lVar10;
        if ((*(char *)(lVar13 + 0x84) != '\0') && (*(char *)(lVar13 + 0x83) == '\0')) {
          lVar13 = *(long *)(param_1 + 0x1c0) + lVar10 + 0x18;
          uVar8 = Aska::Event::IsSignal() const(lVar13);
          if ((uVar8 & 1) == 0) {
            Aska::Event::Set() const(lVar13);
            break;
          }
        }
        lVar14 = lVar14 + 1;
        lVar10 = lVar10 + 0xe0;
      } while (lVar14 < iVar9);
    }
    if ((puVar7 != (undefined1 *)0x0) && (Aska::Event::Wait(unsigned int) const(puVar7,0), bVar5)) {
      Aska::EventPool::Sink(Aska::Event*)(*(undefined8 *)PTR__ZN4Aska6Global12m_pEventPoolE_02cbc1a8,puVar7);
    }
    lVar14 = 0;
    uVar12 = 1;
  }
  Aska::Event::Exit()(auStack_c8);
  if (lVar14 == 0) {
    return uVar12;
  }
code_r0x02061ce8:
  DataMemoryBarrier(2,3);
  *(undefined4 *)(lVar14 + 0x38) = 0xffffffff;
  DataMemoryBarrier(2,3);
  piVar11 = (int *)(lVar14 + 0x3c);
  if (0x14 < *piVar11) {
    do {
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar11,0x10);
      if (bVar5) {
        *piVar11 = *piVar11 + -1;
        cVar4 = ExclusiveMonitorsStatus();
      }
    } while (cVar4 != '\0');
    uVar8 = Aska::Semaphore::IsReady() const(lVar14 + 0x78);
    if ((uVar8 & 1) != 0) {
      Aska::Semaphore::Signal() const(lVar14 + 0x78);
    }
  }
  return uVar12;
}

// ==== Aska::SimpleMessageDispatcher::Setup(int, int)
// vaddr 0x1f61e04 | ghidra 0x2061e04 | size 256 | symbol _ZN4Aska23SimpleMessageDispatcher5SetupEii | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska23SimpleMessageDispatcher5SetupEii(long param_1,int param_2,undefined4 param_3)

{
  long lVar1;
  undefined *puVar2;
  int iVar3;
  ulong uVar4;
  undefined8 uVar5;
  long *plVar6;
  long *plVar7;
  
  uVar4 = Aska::Event::Create(bool, bool)(param_1 + 0x148,1,0);
  uVar5 = 0;
  if ((uVar4 & 1) != 0) {
    plVar6 = (long *)operator new[](unsigned long, std::nothrow_t const&)((long)(param_2 * 0x70 + (param_2 + 1) * 8),
                                     PTR__ZSt7nothrow_02cb9a80);
    uVar5 = 0;
    if (plVar6 != (long *)0x0) {
      lVar1 = (long)plVar6 + (long)(param_2 * 0x70);
      *(long **)(param_1 + 0x138) = plVar6;
      *(long **)(param_1 + 0x140) = plVar6;
      if (param_2 < 0) {
        operator delete[](void*)(lVar1);
        uVar5 = 0;
      }
      else {
        *(long *)(param_1 + 0x130) = lVar1;
        *(int *)(param_1 + 0x128) = param_2 + 1;
        *(undefined8 *)(param_1 + 0x120) = 1;
        if (param_2 != 0) {
          plVar7 = plVar6 + (long)param_2 * 0xe;
          puVar2 = PTR__ZTVN4Aska29MessageDispatcherBlockForListE_02cc2790 + 0x10;
          do {
            plVar6[1] = 0;
            plVar6[2] = 0;
            *plVar6 = (long)puVar2;
            if (*(uint *)(param_1 + 0x124) != *(uint *)(param_1 + 0x120)) {
              *(long **)(*(long *)(param_1 + 0x130) + (ulong)*(uint *)(param_1 + 0x120) * 8) =
                   plVar6;
              iVar3 = 0;
              if (*(int *)(param_1 + 0x120) + 1U < *(uint *)(param_1 + 0x128)) {
                iVar3 = *(int *)(param_1 + 0x120) + 1;
              }
              *(int *)(param_1 + 0x120) = iVar3;
            }
            plVar6 = plVar6 + 0xe;
          } while (plVar6 < plVar7);
        }
        uVar5 = 1;
        *(undefined1 *)(param_1 + 0x1b0) = 0;
        *(undefined4 *)(param_1 + 0x1b4) = param_3;
      }
    }
  }
  return uVar5;
}

// ==== Aska::SimpleMessageDispatcher::AllocateWorkerThreadList(Aska::MessageDispatherWorkerThreadInfo*, int)
// vaddr 0x1f61f04 | ghidra 0x2061f04 | size 616 | symbol _ZN4Aska23SimpleMessageDispatcher24AllocateWorkerThreadListEPNS_32MessageDispatherWorkerThreadInfoEi | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska23SimpleMessageDispatcher24AllocateWorkerThreadListEPNS_32MessageDispatherWorkerThreadInfoEi
          (long param_1,long param_2,uint param_3)

{
  bool bVar1;
  undefined *puVar2;
  undefined1 auVar3 [16];
  ulong *puVar4;
  long lVar5;
  ulong *puVar6;
  long *plVar7;
  ulong uVar8;
  long lVar9;
  
  Aska::SimpleMessageDispatcher::Clear()();
  uVar8 = (ulong)(int)param_3;
  auVar3._8_8_ = 0;
  auVar3._0_8_ = uVar8;
  lVar5 = (long)(int)param_3 * 0xe0 + 8;
  if (SUB168(auVar3 * ZEXT816(0xe0),8) != 0 ||
      0xfffffffffffffff7 < (ulong)((long)(int)param_3 * 0xe0)) {
    lVar5 = -1;
  }
  puVar4 = (ulong *)operator new[](unsigned long, std::nothrow_t const&)(lVar5,PTR__ZSt7nothrow_02cb9a80);
  puVar6 = puVar4;
  if (puVar4 != (ulong *)0x0) {
    puVar6 = puVar4 + 1;
    *puVar4 = uVar8;
    if (param_3 == 0) {
      *(ulong **)(param_1 + 0x1c0) = puVar6;
      *(undefined4 *)(param_1 + 0x1b8) = 0;
      return 1;
    }
    puVar2 = PTR__ZTVN4Aska23SimpleMessageDispatcher13_WorkerThreadE_02cb95f8 + 0x10;
    puVar4 = puVar6;
    do {
      Aska::Thread::Thread()(puVar4);
      *puVar4 = (ulong)puVar2;
      Aska::Event::Event()(puVar4 + 3);
      *(undefined1 *)(puVar4 + 0x10) = 0;
      *(undefined1 *)((long)puVar4 + 0x81) = 0;
      *(undefined1 *)((long)puVar4 + 0x83) = 0;
      *(undefined1 *)((long)puVar4 + 0x84) = 1;
      *(undefined1 *)((long)puVar4 + 0x85) = 0;
      puVar4[0x11] = 0;
      Aska::Event::Create(bool, bool)(puVar4 + 3,0,0);
      puVar4 = puVar4 + 0x1c;
    } while (puVar4 != puVar6 + uVar8 * 0x1c);
  }
  bVar1 = 0 < (int)param_3;
  *(ulong **)(param_1 + 0x1c0) = puVar6;
  if ((int)param_3 < 1) {
    bVar1 = false;
  }
  else {
    lVar5 = 0;
    puVar4 = puVar6 + 3;
    do {
      if (*puVar4 == 0) goto code_r0x02062144;
      lVar5 = lVar5 + 1;
      puVar4 = puVar4 + 0x1c;
    } while (lVar5 < (long)uVar8);
  }
  if (puVar6 == (ulong *)0x0) {
code_r0x02062144:
    Aska::SimpleMessageDispatcher::Clear()(param_1);
    return 0;
  }
  *(uint *)(param_1 + 0x1b8) = param_3;
  if (bVar1) {
    plVar7 = (long *)(param_1 + 0x1c0);
    lVar5 = 0;
    if (param_2 == 0) {
      bVar1 = true;
      lVar9 = 0;
      while( true ) {
        *(long *)((long)puVar6 + lVar9 + 0x88) = param_1;
        *(char *)(*(long *)(param_1 + 0x1c0) + lVar9 + 0x86) = (char)lVar5;
        uVar8 = Aska::Thread::Create(bool, int, int, bool)(*(long *)(param_1 + 0x1c0) + lVar9,1,
                                *(undefined4 *)(param_1 + 0x1b4),0x3000,1);
        if ((uVar8 & 1) == 0) {
          bVar1 = false;
        }
        else {
          Aska::SimpleMessageDispatcher::_WorkerThread::MessageReady()(*plVar7 + lVar9);
        }
        if ((ulong)param_3 - 1 == lVar5) break;
        puVar6 = (ulong *)*plVar7;
        lVar5 = lVar5 + 1;
        lVar9 = lVar9 + 0xe0;
      }
    }
    else {
      lVar9 = 0;
      bVar1 = true;
      while( true ) {
        *(long *)((long)puVar6 + lVar5 + 0x88) = param_1;
        *(char *)(*(long *)(param_1 + 0x1c0) + lVar5 + 0x86) = (char)lVar9;
        uVar8 = Aska::Thread::Create(bool, int, int, bool)(*(long *)(param_1 + 0x1c0) + lVar5,1,
                                *(undefined4 *)(param_1 + 0x1b4),
                                *(undefined4 *)(param_2 + lVar9 * 4),1);
        if ((uVar8 & 1) == 0) {
          bVar1 = false;
        }
        else {
          Aska::SimpleMessageDispatcher::_WorkerThread::MessageReady()(*plVar7 + lVar5);
        }
        if ((ulong)param_3 - 1 == lVar9) break;
        puVar6 = (ulong *)*plVar7;
        lVar9 = lVar9 + 1;
        lVar5 = lVar5 + 0xe0;
      }
    }
    if (!bVar1) goto code_r0x02062144;
  }
  return 1;
}

// ==== Aska::SimpleMessageDispatcher::Clear()
// vaddr 0x1f6216c | ghidra 0x206216c | size 216 | symbol _ZN4Aska23SimpleMessageDispatcher5ClearEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska23SimpleMessageDispatcher5ClearEv(long param_1)

{
  undefined *puVar1;
  uint uVar2;
  ulong uVar3;
  long lVar4;
  long *plVar5;
  long lVar6;
  ulong uVar7;
  
  lVar6 = *(long *)(param_1 + 0x1c0);
  if (lVar6 == 0) {
    return;
  }
  uVar2 = *(uint *)(param_1 + 0x1b8);
  uVar3 = (ulong)uVar2;
  if (0 < (int)uVar2) {
    lVar4 = 0x81;
    uVar7 = uVar3;
    do {
      *(undefined1 *)(lVar6 + lVar4) = 1;
      Aska::Event::Set() const((undefined1 *)(lVar6 + lVar4) + -0x69);
      lVar6 = *(long *)(param_1 + 0x1c0);
      uVar7 = uVar7 - 1;
      lVar4 = lVar4 + 0xe0;
    } while (uVar7 != 0);
    if (0 < (int)uVar2) {
      lVar4 = 0;
      do {
        Aska::Thread::WaitEnd()(lVar6 + lVar4);
        lVar6 = *(long *)(param_1 + 0x1c0);
        uVar3 = uVar3 - 1;
        lVar4 = lVar4 + 0xe0;
      } while (uVar3 != 0);
    }
    if (lVar6 == 0) goto code_r0x0206222c;
  }
  lVar4 = *(long *)(lVar6 + -8);
  if (lVar4 != 0) {
    lVar4 = lVar4 * 0xe0;
    puVar1 = PTR__ZTVN4Aska23SimpleMessageDispatcher13_WorkerThreadE_02cb95f8 + 0x10;
    do {
      plVar5 = (long *)(lVar6 + lVar4 + -0xe0);
      *plVar5 = (long)puVar1;
      Aska::Event::Exit()(lVar6 + lVar4 + -200);
      Aska::Thread::~Thread()(plVar5);
      lVar4 = lVar4 + -0xe0;
    } while (lVar4 != 0);
  }
  operator delete[](void*)((long *)(lVar6 + -8));
code_r0x0206222c:
  *(undefined8 *)(param_1 + 0x1c0) = 0;
  return;
}

// ==== Aska::SimpleMessageDispatcher::_WorkerThread::MessageReady()
// vaddr 0x1f62244 | ghidra 0x2062244 | size 448 | symbol _ZN4Aska23SimpleMessageDispatcher13_WorkerThread12MessageReadyEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska23SimpleMessageDispatcher13_WorkerThread12MessageReadyEv(long param_1)

{
  int *piVar1;
  uint uVar2;
  char cVar3;
  bool bVar4;
  int iVar5;
  long lVar6;
  long lVar7;
  ulong uVar8;
  long lVar9;
  int *piVar10;
  
  *(undefined1 *)(param_1 + 0x83) = 0;
  if ((*(long *)(param_1 + 0xd0) == 0xffffffff) || (*(long *)(param_1 + 0xd8) == 0xffffffff)) {
    lVar7 = *(long *)(param_1 + 0x88);
    uVar2 = *(uint *)(lVar7 + 0x1b8);
    uVar8 = (ulong)uVar2;
    if (0 < (int)uVar2) {
      lVar9 = 0x84;
      do {
        lVar6 = *(long *)(lVar7 + 0x1c0);
        if (*(char *)(lVar6 + lVar9) != '\0') {
          Aska::Event::Set() const(lVar6 + lVar9 + -0x6c);
        }
        uVar8 = uVar8 - 1;
        lVar9 = lVar9 + 0xe0;
      } while (uVar8 != 0);
    }
  }
  lVar7 = *(long *)(param_1 + 0x88);
  piVar1 = (int *)(lVar7 + 0x40);
  iVar5 = 0;
  do {
    while (*piVar1 != -1) {
      ClearExclusiveLocal();
      bVar4 = 0x1fe < iVar5;
      iVar5 = iVar5 + 1;
      if (bVar4) {
        piVar10 = (int *)(lVar7 + 0x44);
        do {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar10,0x10);
          if (bVar4) {
            *piVar10 = *piVar10 + 1;
            cVar3 = ExclusiveMonitorsStatus();
          }
        } while (cVar3 != '\0');
        do {
          if (*piVar1 != -1) {
            ClearExclusiveLocal();
            do {
              uVar8 = Aska::Semaphore::IsReady() const(lVar7 + 0x80);
              if ((uVar8 & 1) == 0) {
                do {
                  cVar3 = '\x01';
                  bVar4 = (bool)ExclusiveMonitorPass(piVar10,0x10);
                  if (bVar4) {
                    *piVar10 = *piVar10 + -1;
                    cVar3 = ExclusiveMonitorsStatus();
                  }
                } while (cVar3 != '\0');
                Aska::Thread::Sleep(unsigned int)(1);
              }
              else {
                Aska::Semaphore::Wait() const(lVar7 + 0x80);
              }
              do {
                cVar3 = '\x01';
                bVar4 = (bool)ExclusiveMonitorPass(piVar10,0x10);
                if (bVar4) {
                  *piVar10 = *piVar10 + 1;
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
                if (cVar3 == '\0') goto code_r0x020623ec;
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
code_r0x020623ec:
        do {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar10,0x10);
          if (bVar4) {
            *piVar10 = *piVar10 + -1;
            cVar3 = ExclusiveMonitorsStatus();
          }
        } while (cVar3 != '\0');
        DataMemoryBarrier(2,3);
code_r0x02062324:
        piVar10 = (int *)(lVar7 + 0x44);
        *(long *)(param_1 + 0xd0) = 0;
        *(undefined8 *)(param_1 + 0xd8) = 0;
        DataMemoryBarrier(2,3);
        *piVar1 = -1;
        DataMemoryBarrier(2,3);
        if (0x14 < *piVar10) {
          do {
            cVar3 = '\x01';
            bVar4 = (bool)ExclusiveMonitorPass(piVar10,0x10);
            if (bVar4) {
              *piVar10 = *piVar10 + -1;
              cVar3 = ExclusiveMonitorsStatus();
            }
          } while (cVar3 != '\0');
          uVar8 = Aska::Semaphore::IsReady() const(lVar7 + 0x80);
          if ((uVar8 & 1) != 0) {
            (*(code *)PTR__ZNK4Aska9Semaphore6SignalEv_02c96cd0)(lVar7 + 0x80);
            return;
          }
        }
        return;
      }
    }
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar4) {
      *piVar1 = 0;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
  DataMemoryBarrier(2,3);
  goto code_r0x02062324;
}

// ==== Aska::SimpleMessageDispatcher::AllocateWorkerThreadList(int, char const*, int, int, int)
// vaddr 0x1f62404 | ghidra 0x2062404 | size 500 | symbol _ZN4Aska23SimpleMessageDispatcher24AllocateWorkerThreadListEiPKciii | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska23SimpleMessageDispatcher24AllocateWorkerThreadListEiPKciii(long param_1,uint param_2)

{
  bool bVar1;
  undefined *puVar2;
  int iVar3;
  undefined1 auVar4 [16];
  ulong *puVar5;
  undefined8 uVar6;
  int in_w5;
  long lVar7;
  ulong *puVar8;
  long lVar9;
  ulong uVar10;
  
  Aska::SimpleMessageDispatcher::Clear()();
  uVar10 = (ulong)(int)param_2;
  auVar4._8_8_ = 0;
  auVar4._0_8_ = uVar10;
  lVar7 = (long)(int)param_2 * 0xe0 + 8;
  if (SUB168(auVar4 * ZEXT816(0xe0),8) != 0 ||
      0xfffffffffffffff7 < (ulong)((long)(int)param_2 * 0xe0)) {
    lVar7 = -1;
  }
  puVar5 = (ulong *)operator new[](unsigned long, std::nothrow_t const&)(lVar7,PTR__ZSt7nothrow_02cb9a80);
  puVar8 = puVar5;
  if (puVar5 == (ulong *)0x0) {
code_r0x020624dc:
    bVar1 = 0 < (int)param_2;
    *(ulong **)(param_1 + 0x1c0) = puVar8;
    if ((int)param_2 < 1) {
      bVar1 = false;
    }
    else {
      lVar7 = 0;
      puVar5 = puVar8 + 3;
      do {
        if (*puVar5 == 0) goto code_r0x020625d0;
        lVar7 = lVar7 + 1;
        puVar5 = puVar5 + 0x1c;
      } while (lVar7 < (long)uVar10);
    }
    if (puVar8 != (ulong *)0x0) goto code_r0x02062534;
code_r0x020625d0:
    Aska::SimpleMessageDispatcher::Clear()(param_1);
    uVar6 = 0;
  }
  else {
    puVar8 = puVar5 + 1;
    *puVar5 = uVar10;
    if (param_2 != 0) {
      puVar2 = PTR__ZTVN4Aska23SimpleMessageDispatcher13_WorkerThreadE_02cb95f8 + 0x10;
      puVar5 = puVar8;
      do {
        Aska::Thread::Thread()(puVar5);
        *puVar5 = (ulong)puVar2;
        Aska::Event::Event()(puVar5 + 3);
        *(undefined1 *)(puVar5 + 0x10) = 0;
        *(undefined1 *)((long)puVar5 + 0x81) = 0;
        *(undefined1 *)((long)puVar5 + 0x83) = 0;
        *(undefined1 *)((long)puVar5 + 0x84) = 1;
        *(undefined1 *)((long)puVar5 + 0x85) = 0;
        puVar5[0x11] = 0;
        Aska::Event::Create(bool, bool)(puVar5 + 3,0,0);
        puVar5 = puVar5 + 0x1c;
      } while (puVar5 != puVar8 + uVar10 * 0x1c);
      goto code_r0x020624dc;
    }
    bVar1 = false;
    *(ulong **)(param_1 + 0x1c0) = puVar8;
code_r0x02062534:
    iVar3 = 0x3000;
    if (0 < in_w5) {
      iVar3 = in_w5;
    }
    *(uint *)(param_1 + 0x1b8) = param_2;
    if (bVar1) {
      lVar9 = 0;
      lVar7 = 0;
      bVar1 = true;
      while( true ) {
        *(long *)((long)puVar8 + lVar9 + 0x88) = param_1;
        *(char *)(*(long *)(param_1 + 0x1c0) + lVar9 + 0x86) = (char)lVar7;
        uVar10 = Aska::Thread::Create(bool, int, int, bool)(*(long *)(param_1 + 0x1c0) + lVar9,1,
                                 *(undefined4 *)(param_1 + 0x1b4),iVar3,1);
        if ((uVar10 & 1) == 0) {
          bVar1 = false;
        }
        else {
          Aska::SimpleMessageDispatcher::_WorkerThread::MessageReady()(*(long *)(param_1 + 0x1c0) + lVar9);
        }
        if ((ulong)param_2 - 1 == lVar7) break;
        puVar8 = *(ulong **)(param_1 + 0x1c0);
        lVar7 = lVar7 + 1;
        lVar9 = lVar9 + 0xe0;
      }
      if (!bVar1) goto code_r0x020625d0;
    }
    uVar6 = 1;
  }
  return uVar6;
}

// ==== Aska::SimpleMessageDispatcher::SuspendWorkerThread()
// vaddr 0x1f625f8 | ghidra 0x20625f8 | size 344 | symbol _ZN4Aska23SimpleMessageDispatcher19SuspendWorkerThreadEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska23SimpleMessageDispatcher19SuspendWorkerThreadEv(long param_1)

{
  int *piVar1;
  int *piVar2;
  char cVar3;
  bool bVar4;
  ulong uVar5;
  int iVar6;
  
  piVar1 = (int *)(param_1 + 0x40);
  iVar6 = 0;
  do {
    while (*piVar1 != -1) {
      ClearExclusiveLocal();
      bVar4 = 0x1fe < iVar6;
      iVar6 = iVar6 + 1;
      if (bVar4) {
        piVar2 = (int *)(param_1 + 0x44);
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
              uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0x80);
              if ((uVar5 & 1) == 0) {
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
                Aska::Semaphore::Wait() const(param_1 + 0x80);
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
                if (cVar3 == '\0') goto code_r0x02062738;
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
code_r0x02062738:
        do {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
          if (bVar4) {
            *piVar2 = *piVar2 + -1;
            cVar3 = ExclusiveMonitorsStatus();
          }
        } while (cVar3 != '\0');
        DataMemoryBarrier(2,3);
code_r0x0206266c:
        *(undefined1 *)(param_1 + 0x1c8) = 1;
        DataMemoryBarrier(2,3);
        *(undefined4 *)(param_1 + 0x40) = 0xffffffff;
        DataMemoryBarrier(2,3);
        piVar1 = (int *)(param_1 + 0x44);
        if (0x14 < *piVar1) {
          do {
            cVar3 = '\x01';
            bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
            if (bVar4) {
              *piVar1 = *piVar1 + -1;
              cVar3 = ExclusiveMonitorsStatus();
            }
          } while (cVar3 != '\0');
          uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0x80);
          if ((uVar5 & 1) != 0) {
            (*(code *)PTR__ZNK4Aska9Semaphore6SignalEv_02c96cd0)(param_1 + 0x80);
            return;
          }
        }
        return;
      }
    }
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar4) {
      *piVar1 = 0;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
  DataMemoryBarrier(2,3);
  goto code_r0x0206266c;
}

// ==== Aska::SimpleMessageDispatcher::ResumeWorkerThread()
// vaddr 0x1f62750 | ghidra 0x2062750 | size 400 | symbol _ZN4Aska23SimpleMessageDispatcher18ResumeWorkerThreadEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska23SimpleMessageDispatcher18ResumeWorkerThreadEv(long param_1)

{
  int *piVar1;
  char cVar2;
  bool bVar3;
  int iVar4;
  int *piVar5;
  ulong uVar6;
  long lVar7;
  
  piVar5 = (int *)(param_1 + 0x40);
  iVar4 = 0;
  do {
    while (*piVar5 == -1) {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar5,0x10);
      if (bVar3) {
        *piVar5 = 0;
        cVar2 = ExclusiveMonitorsStatus();
      }
      if (cVar2 == '\0') goto code_r0x02062830;
    }
    ClearExclusiveLocal();
    bVar3 = iVar4 < 0x1ff;
    iVar4 = iVar4 + 1;
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
    if (*piVar5 != -1) {
      ClearExclusiveLocal();
      do {
        uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x80);
        if ((uVar6 & 1) == 0) {
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
        while (*piVar5 == -1) {
          cVar2 = '\x01';
          bVar3 = (bool)ExclusiveMonitorPass(piVar5,0x10);
          if (bVar3) {
            *piVar5 = 0;
            cVar2 = ExclusiveMonitorsStatus();
          }
          if (cVar2 == '\0') goto code_r0x02062820;
        }
        ClearExclusiveLocal();
      } while( true );
    }
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar5,0x10);
    if (bVar3) {
      *piVar5 = 0;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
code_r0x02062820:
  do {
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar3) {
      *piVar1 = *piVar1 + -1;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
code_r0x02062830:
  DataMemoryBarrier(2,3);
  *(undefined1 *)(param_1 + 0x1c8) = 0;
  if ((param_1 + 0xa0 != *(long *)(param_1 + 0xb0)) &&
     (uVar6 = (ulong)*(uint *)(param_1 + 0x1b8), 0 < (int)*(uint *)(param_1 + 0x1b8))) {
    lVar7 = 0x84;
    do {
      if (*(char *)(*(long *)(param_1 + 0x1c0) + lVar7) != '\0') {
        Aska::Event::Set() const(*(long *)(param_1 + 0x1c0) + lVar7 + -0x6c);
      }
      uVar6 = uVar6 - 1;
      lVar7 = lVar7 + 0xe0;
    } while (uVar6 != 0);
  }
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_1 + 0x40) = 0xffffffff;
  DataMemoryBarrier(2,3);
  piVar5 = (int *)(param_1 + 0x44);
  if (0x14 < *piVar5) {
    do {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar5,0x10);
      if (bVar3) {
        *piVar5 = *piVar5 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x80);
    if ((uVar6 & 1) != 0) {
      (*(code *)PTR__ZNK4Aska9Semaphore6SignalEv_02c96cd0)(param_1 + 0x80);
      return;
    }
  }
  return;
}

// ==== Aska::SimpleMessageDispatcher::IsWorkerThreadSuspended() const
// vaddr 0x1f628e0 | ghidra 0x20628e0 | size 8 | symbol _ZNK4Aska23SimpleMessageDispatcher23IsWorkerThreadSuspendedEv | lib libSOA-3.7.0.so | 2026-10-04
undefined1 _ZNK4Aska23SimpleMessageDispatcher23IsWorkerThreadSuspendedEv(long param_1)

{
  return *(undefined1 *)(param_1 + 0x1c8);
}

// ==== Aska::SimpleMessageDispatcher::Initialize()
// vaddr 0x1f628e8 | ghidra 0x20628e8 | size 40 | symbol _ZN4Aska23SimpleMessageDispatcher10InitializeEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska23SimpleMessageDispatcher10InitializeEv(long param_1)

{
  *(undefined2 *)(param_1 + 0x1ca) = 0;
  *(undefined8 *)(param_1 + 0x1c0) = 0;
  *(undefined8 *)(param_1 + 0x138) = 0;
  *(undefined8 *)(param_1 + 0x140) = 0;
  *(undefined8 *)(param_1 + 0x1b4) = 0x80;
  *(undefined1 *)(param_1 + 0x1c8) = 0;
  return 1;
}

// ==== Aska::SimpleMessageDispatcher::Release()
// vaddr 0x1f62910 | ghidra 0x2062910 | size 4 | symbol _ZN4Aska23SimpleMessageDispatcher7ReleaseEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska23SimpleMessageDispatcher7ReleaseEv(void)

{
  (*(code *)PTR__ZN4Aska23SimpleMessageDispatcher5ClearEv_02cb0c08)();
  return;
}

// ==== Aska::SimpleMessageDispatcher::_WorkerThread::Exit()
// vaddr 0x1f62914 | ghidra 0x2062914 | size 20 | symbol _ZN4Aska23SimpleMessageDispatcher13_WorkerThread4ExitEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska23SimpleMessageDispatcher13_WorkerThread4ExitEv(long param_1)

{
  *(undefined1 *)(param_1 + 0x81) = 1;
  (*(code *)PTR__ZNK4Aska5Event3SetEv_02c9dcf0)(param_1 + 0x18);
  return;
}

// ==== Aska::SimpleMessageDispatcher::_WorkerThread::~_WorkerThread()
// vaddr 0x1f62928 | ghidra 0x2062928 | size 40 | symbol _ZN4Aska23SimpleMessageDispatcher13_WorkerThreadD2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska23SimpleMessageDispatcher13_WorkerThreadD2Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska23SimpleMessageDispatcher13_WorkerThreadE_02cb95f8 + 0x10);
  Aska::Event::Exit()(param_1 + 3);
  (*(code *)PTR__ZN4Aska6ThreadD1Ev_02c9be08)(param_1);
  return;
}

// ==== Aska::SimpleMessageDispatcher::GetMessage(Aska::MessageDispatcherBlock*, int)
// vaddr 0x1f62950 | ghidra 0x2062950 | size 756 | symbol _ZN4Aska23SimpleMessageDispatcher10GetMessageEPNS_22MessageDispatcherBlockEi | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska23SimpleMessageDispatcher10GetMessageEPNS_22MessageDispatcherBlockEi
          (long *param_1,undefined8 param_2,ulong param_3)

{
  long *plVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  ulong uVar5;
  long lVar6;
  long lVar7;
  long lVar8;
  long lVar9;
  long lVar10;
  long *plVar11;
  uint uVar12;
  
  plVar11 = (long *)param_1[0x16];
  plVar1 = param_1 + 0x14;
  if (plVar1 == plVar11) {
    return 0;
  }
  if ((char)param_1[0x39] != '\0') {
    return 0;
  }
  uVar4 = *(uint *)(param_1 + 0x37);
  if (0 < (int)uVar4) {
    uVar5 = 0;
    uVar12 = 0;
    lVar6 = 0x83;
    do {
      if ((param_3 & 0xffffffff) != uVar5) {
        uVar2 = 0;
        if (*(char *)(param_1[0x38] + lVar6) != '\0') {
          uVar2 = 1 << (ulong)((uint)uVar5 & 0x1f);
        }
        uVar12 = uVar2 | uVar12;
      }
      uVar5 = uVar5 + 1;
      lVar6 = lVar6 + 0xe0;
    } while (uVar4 != uVar5);
    if (uVar12 != 0) {
      if ((int)uVar4 < 1) {
        do {
          if (plVar11[0xb] == 0xffffffff) {
            return 0;
          }
          if (plVar11[0xc] == 0xffffffff) {
            return 0;
          }
          if ((*(byte *)((long)plVar11 + 0x1b) >> 6 & 1) == 0) {
            if ((uVar4 == 0) &&
               (uVar5 = (**(code **)(*param_1 + 0x18))(param_1,plVar11), (uVar5 & 1) != 0)) break;
          }
          else if (((int *)plVar11[8] == (int *)0x0) || (*(int *)plVar11[8] == 0)) break;
          plVar11 = (long *)plVar11[2];
        } while (plVar1 != plVar11);
      }
      else {
        do {
          lVar6 = plVar11[0xb];
          if (lVar6 == 0xffffffff) {
            return 0;
          }
          lVar7 = plVar11[0xc];
          if (lVar7 == 0xffffffff) {
            return 0;
          }
          if ((*(byte *)((long)plVar11 + 0x1b) >> 6 & 1) == 0) {
            lVar8 = 0;
            uVar5 = 0;
            do {
              if ((((param_3 & 0xffffffff) != uVar5) &&
                  ((1 << (ulong)((uint)uVar5 & 0x1f) & uVar12) != 0)) &&
                 ((((lVar9 = param_1[0x38], lVar6 != 0 &&
                    ((*(long *)(lVar9 + lVar8 + 0xd0) == lVar6 ||
                     (*(long *)(lVar9 + lVar8 + 0xd8) == lVar6)))) ||
                   ((lVar10 = *(long *)(lVar9 + lVar8 + 0xd0), lVar7 != 0 &&
                    ((lVar10 == lVar7 || (*(long *)(lVar9 + lVar8 + 0xd8) == lVar7)))))) ||
                  ((lVar10 == 0xffffffff || (*(long *)(lVar9 + lVar8 + 0xd8) == 0xffffffff))))))
              break;
              uVar5 = uVar5 + 1;
              lVar8 = lVar8 + 0xe0;
            } while ((long)uVar5 < (long)(int)uVar4);
            if (((uint)uVar5 == uVar4) &&
               (uVar5 = (**(code **)(*param_1 + 0x18))(param_1,plVar11), (uVar5 & 1) != 0)) break;
          }
          else if (((int *)plVar11[8] == (int *)0x0) || (*(int *)plVar11[8] == 0)) break;
          plVar11 = (long *)plVar11[2];
        } while (plVar1 != plVar11);
      }
      goto code_r0x02062b40;
    }
  }
  do {
    if ((*(byte *)((long)plVar11 + 0x1b) >> 6 & 1) == 0) {
      uVar5 = (**(code **)(*param_1 + 0x18))(param_1,plVar11);
      if ((uVar5 & 1) != 0) break;
    }
    else if (((int *)plVar11[8] == (int *)0x0) || (*(int *)plVar11[8] == 0)) break;
    plVar11 = (long *)plVar11[2];
  } while (plVar1 != plVar11);
code_r0x02062b40:
  if (plVar1 == plVar11) {
    return 0;
  }
  if ((*(byte *)((long)plVar11 + 0x1b) >> 6 & 1) != 0) {
    plVar11[8] = 0;
  }
  memcpy(param_2,plVar11 + 3,0x50);
  lVar6 = plVar11[1];
  lVar7 = plVar11[2];
  if (lVar6 != 0) {
    *(long *)(lVar6 + 0x10) = lVar7;
  }
  if (lVar7 != 0) {
    *(long *)(lVar7 + 8) = lVar6;
  }
  if (0 < (int)param_1[0x22]) {
    *(int *)(param_1 + 0x22) = (int)param_1[0x22] + -1;
  }
  plVar11[1] = 0;
  plVar11[2] = 0;
  if (*(uint *)((long)param_1 + 0x124) != *(uint *)(param_1 + 0x24)) {
    *(long **)(param_1[0x26] + (ulong)*(uint *)(param_1 + 0x24) * 8) = plVar11;
    iVar3 = 0;
    if ((int)param_1[0x24] + 1U < *(uint *)(param_1 + 0x25)) {
      iVar3 = (int)param_1[0x24] + 1;
    }
    *(int *)(param_1 + 0x24) = iVar3;
  }
  if ((char)param_1[0x36] != '\0') {
    Aska::Event::Set() const(param_1 + 0x29);
    *(undefined1 *)(param_1 + 0x36) = 0;
  }
  return 1;
}

// ==== Aska::SimpleMessageDispatcher::_WorkerThread::Handler()
// vaddr 0x1f62c44 | ghidra 0x2062c44 | size 200 | symbol _ZN4Aska23SimpleMessageDispatcher13_WorkerThread7HandlerEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska23SimpleMessageDispatcher13_WorkerThread7HandlerEv(long param_1)

{
  uint uVar1;
  char cVar2;
  bool bVar3;
  ulong uVar4;
  undefined8 *puVar5;
  int *piVar6;
  long lVar7;
  
  *(undefined1 *)(param_1 + 0x80) = 1;
  do {
    Aska::Event::Wait(unsigned int) const(param_1 + 0x18,0);
    if (*(char *)(param_1 + 0x81) != '\0') {
      Aska::Thread::Exit()();
    }
    while (uVar4 = Aska::SimpleMessageDispatcher::_WorkerThread::GetMessage(Aska::MessageDispatcherBlock*)(param_1,param_1 + 0x90), (uVar4 & 1) != 0) {
      puVar5 = *(undefined8 **)(param_1 + 0x98);
      if (puVar5 != (undefined8 *)0x0) {
        (**(code **)*puVar5)(puVar5,param_1 + 0x90);
      }
      piVar6 = *(int **)(param_1 + 0xb8);
      if (piVar6 != (int *)0x0) {
        do {
          cVar2 = '\x01';
          bVar3 = (bool)ExclusiveMonitorPass(piVar6,0x10);
          if (bVar3) {
            *piVar6 = *piVar6 + -1;
            cVar2 = ExclusiveMonitorsStatus();
          }
        } while (cVar2 != '\0');
      }
      if ((*(char *)(param_1 + 0x82) != '\0') && (*(long *)(param_1 + 0xa0) != 0)) {
        Aska::Event::Set() const();
      }
      lVar7 = *(long *)(param_1 + 0xa8);
      uVar1 = *(uint *)(param_1 + 0xb0);
      if ((lVar7 != 0) && (uVar1 < 0x20)) {
        Aska::TaskManager::DecrementThreadBarrierCount(int)(lVar7,uVar1);
        Aska::TaskManager::DeleteThreadBarrier(int)(lVar7,uVar1);
      }
      Aska::SimpleMessageDispatcher::_WorkerThread::MessageReady()(param_1);
    }
  } while( true );
}

// ==== Aska::SimpleMessageDispatcher::_WorkerThread::GetMessage(Aska::MessageDispatcherBlock*)
// vaddr 0x1f62d0c | ghidra 0x2062d0c | size 520 | symbol _ZN4Aska23SimpleMessageDispatcher13_WorkerThread10GetMessageEPNS_22MessageDispatcherBlockE | lib libSOA-3.7.0.so | 2026-10-04
uint _ZN4Aska23SimpleMessageDispatcher13_WorkerThread10GetMessageEPNS_22MessageDispatcherBlockE
               (long param_1,undefined8 param_2)

{
  int *piVar1;
  long lVar2;
  char cVar3;
  bool bVar4;
  uint uVar5;
  ulong uVar6;
  int iVar7;
  long lVar8;
  long lVar9;
  int *piVar10;
  long lVar11;
  long lVar12;
  
  if (*(char *)(param_1 + 0x84) == '\0') {
    lVar9 = *(long *)(param_1 + 0x88);
    iVar7 = *(int *)(lVar9 + 0x1b8);
    if (0 < iVar7) {
      lVar11 = 0;
      lVar12 = 0;
      do {
        lVar8 = *(long *)(lVar9 + 0x1c0);
        lVar2 = lVar8 + lVar11;
        if ((*(char *)(lVar2 + 0x84) != '\0') && (*(char *)(lVar2 + 0x83) == '\0')) {
          lVar2 = lVar8 + lVar11 + 0x18;
          uVar6 = Aska::Event::IsSignal() const(lVar2);
          if ((uVar6 & 1) == 0) {
            Aska::Event::Set() const(lVar2);
            uVar5 = 0;
            goto code_r0x02062efc;
          }
        }
        lVar12 = lVar12 + 1;
        lVar11 = lVar11 + 0xe0;
      } while (lVar12 < iVar7);
    }
    *(undefined1 *)(param_1 + 0x84) = 1;
    Aska::Event::Set() const(param_1 + 0x18);
  }
  lVar9 = *(long *)(param_1 + 0x88);
  piVar10 = (int *)(lVar9 + 0x40);
  iVar7 = 0;
  do {
    while (*piVar10 == -1) {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar10,0x10);
      if (bVar4) {
        *piVar10 = 0;
        cVar3 = ExclusiveMonitorsStatus();
      }
      if (cVar3 == '\0') goto code_r0x02062e78;
    }
    ClearExclusiveLocal();
    bVar4 = iVar7 < 0x1ff;
    iVar7 = iVar7 + 1;
  } while (bVar4);
  piVar1 = (int *)(lVar9 + 0x44);
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
        uVar6 = Aska::Semaphore::IsReady() const(lVar9 + 0x80);
        if ((uVar6 & 1) == 0) {
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
          Aska::Semaphore::Wait() const(lVar9 + 0x80);
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
          if (cVar3 == '\0') goto code_r0x02062e68;
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
code_r0x02062e68:
  do {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar4) {
      *piVar1 = *piVar1 + -1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
code_r0x02062e78:
  DataMemoryBarrier(2,3);
  uVar5 = (**(code **)(**(long **)(param_1 + 0x88) + 0x10))
                    (*(long **)(param_1 + 0x88),param_2,*(undefined1 *)(param_1 + 0x86));
  if ((uVar5 & 1) != 0) {
    *(undefined1 *)(param_1 + 0x83) = 1;
    *(byte *)(param_1 + 0x82) = (byte)(*(ushort *)(param_1 + 0x92) >> 0xf);
    *(ushort *)(param_1 + 0x92) = *(ushort *)(param_1 + 0x92) & 0x3fff;
  }
  DataMemoryBarrier(2,3);
  *(undefined4 *)(lVar9 + 0x40) = 0xffffffff;
  DataMemoryBarrier(2,3);
  piVar10 = (int *)(lVar9 + 0x44);
  if (0x14 < *piVar10) {
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar10,0x10);
      if (bVar4) {
        *piVar10 = *piVar10 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
    uVar6 = Aska::Semaphore::IsReady() const(lVar9 + 0x80);
    if ((uVar6 & 1) != 0) {
      Aska::Semaphore::Signal() const(lVar9 + 0x80);
    }
  }
code_r0x02062efc:
  return uVar5 & 1;
}

// ==== Aska::SimpleMessageDispatcher::_WorkerThread::~_WorkerThread()
// vaddr 0x1f62f14 | ghidra 0x2062f14 | size 48 | symbol _ZN4Aska23SimpleMessageDispatcher13_WorkerThreadD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska23SimpleMessageDispatcher13_WorkerThreadD0Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska23SimpleMessageDispatcher13_WorkerThreadE_02cb95f8 + 0x10);
  Aska::Event::Exit()(param_1 + 3);
  Aska::Thread::~Thread()(param_1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::SimpleMessageDispatcher::~SimpleMessageDispatcher()
// vaddr 0x1f62f44 | ghidra 0x2062f44 | size 108 | symbol _ZN4Aska23SimpleMessageDispatcherD2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska23SimpleMessageDispatcherD2Ev(long *param_1)

{
  undefined *puVar1;
  
  *param_1 = (long)(PTR__ZTVN4Aska23SimpleMessageDispatcherE_02cba3a8 + 0x10);
  Aska::SimpleMessageDispatcher::Clear()();
  if (param_1[0x28] != 0) {
    operator delete[](void*)();
  }
  Aska::Event::Exit()(param_1 + 0x29);
  Aska::Event::Exit()(param_1 + 0x29);
  puVar1 = PTR__ZTVN4Aska13TDynamicQueueIPNS_29MessageDispatcherBlockForListELb0EEE_02cc17a8;
  *(undefined4 *)(param_1 + 0x25) = 0;
  param_1[0x26] = 0;
  param_1[0x23] = (long)(puVar1 + 0x10);
  param_1[0x24] = 1;
  (*(code *)PTR__ZN4Aska19FastCriticalSectionD2Ev_02ca21e0)(param_1 + 1);
  return;
}

// ==== Aska::SimpleMessageDispatcher::~SimpleMessageDispatcher()
// vaddr 0x1f62fb0 | ghidra 0x2062fb0 | size 116 | symbol _ZN4Aska23SimpleMessageDispatcherD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska23SimpleMessageDispatcherD0Ev(long *param_1)

{
  undefined *puVar1;
  
  *param_1 = (long)(PTR__ZTVN4Aska23SimpleMessageDispatcherE_02cba3a8 + 0x10);
  Aska::SimpleMessageDispatcher::Clear()();
  if (param_1[0x28] != 0) {
    operator delete[](void*)();
  }
  Aska::Event::Exit()(param_1 + 0x29);
  Aska::Event::Exit()(param_1 + 0x29);
  puVar1 = PTR__ZTVN4Aska13TDynamicQueueIPNS_29MessageDispatcherBlockForListELb0EEE_02cc17a8;
  *(undefined4 *)(param_1 + 0x25) = 0;
  param_1[0x26] = 0;
  param_1[0x23] = (long)(puVar1 + 0x10);
  param_1[0x24] = 1;
  Aska::FastCriticalSection::~FastCriticalSection()(param_1 + 1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::SimpleMessageDispatcher::CheckToDispatch(Aska::MessageDispatcherBlockForList*)
// vaddr 0x1f63024 | ghidra 0x2063024 | size 8 | symbol _ZN4Aska23SimpleMessageDispatcher15CheckToDispatchEPNS_29MessageDispatcherBlockForListE | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska23SimpleMessageDispatcher15CheckToDispatchEPNS_29MessageDispatcherBlockForListE(void)

{
  return 1;
}

// ==== Aska::Global::InstantiateMessageDispatcher()
// vaddr 0x220ff8c | ghidra 0x230ff8c | size 340 | symbol _ZN4Aska6Global28InstantiateMessageDispatcherEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZN4Aska6Global28InstantiateMessageDispatcherEv(void)

{
  undefined4 uVar1;
  int iVar2;
  undefined *puVar3;
  undefined *puVar4;
  int iVar5;
  long *plVar6;
  ulong uVar7;
  
  uVar1 = *(undefined4 *)(*(long *)PTR__ZN4Aska6Global6m_pAppE_02cc2078 + 0x88);
  plVar6 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x1d0,PTR__ZSt7nothrow_02cb9a80);
  if (plVar6 != (long *)0x0) {
    *plVar6 = (long)(PTR__ZTVN4Aska23SimpleMessageDispatcherE_02cba3a8 + 0x10);
    Aska::FastCriticalSection::FastCriticalSection()(plVar6 + 1);
    puVar3 = PTR__ZTVN4Aska5TListINS_29MessageDispatcherBlockForListEEE_02cb8088;
    plVar6[0x15] = (long)(plVar6 + 0x14);
    plVar6[0x16] = (long)(plVar6 + 0x14);
    puVar4 = PTR__ZTVN4Aska29MessageDispatcherBlockForListE_02cc2790;
    *(undefined4 *)(plVar6 + 0x22) = 0;
    plVar6[0x23] = (long)(
                         PTR__ZTVN4Aska13TDynamicQueueIPNS_29MessageDispatcherBlockForListELb0EEE_02cc17a8
                         + 0x10);
    *(undefined4 *)((long)plVar6 + 0x124) = 0;
    *(undefined4 *)(plVar6 + 0x25) = 0;
    plVar6[0x26] = 0;
    *(undefined4 *)(plVar6 + 0x24) = 1;
    plVar6[0x14] = (long)(puVar4 + 0x10);
    plVar6[0x13] = (long)(puVar3 + 0x10);
    Aska::Event::Event()(plVar6 + 0x29);
    Aska::SimpleMessageDispatcher::Initialize()(plVar6);
    Aska::SimpleMessageDispatcher::Setup(int, int)(plVar6,uVar1,0x80);
    *plVar6 = (long)(PTR__ZTVN4Aska17MessageDispatcherE_02cbe770 + 0x10);
    Aska::MessageDispatcher::Initialize()(plVar6);
    puVar3 = PTR__ZN4Aska6Global20m_pMessageDispatcherE_02cb77c8;
    *(long **)PTR__ZN4Aska6Global20m_pMessageDispatcherE_02cb77c8 = plVar6;
    iVar5 = Aska::RenderDeviceGL::GetNumberOfProcessors()();
    iVar2 = iVar5 + -2;
    if (0xff < iVar2) {
      iVar2 = 0x100;
    }
    if (iVar5 < 3) {
      iVar2 = 1;
    }
    uVar7 = Aska::SimpleMessageDispatcher::AllocateWorkerThreadList(int, char const*, int, int, int)(*(undefined8 *)puVar3,iVar2,&UNK_029d4c7b/*"Aska::DynamicsWorker"*/,0xb,6,0x20000);
    if ((uVar7 & 1) != 0) {
      return 1;
    }
    plVar6 = *(long **)puVar3;
    if (plVar6 != (long *)0x0) {
      (**(code **)(*plVar6 + 8))();
    }
  }
  *(undefined8 *)PTR__ZN4Aska6Global20m_pMessageDispatcherE_02cb77c8 = 0;
  return 0;
}

// ==== Aska::SimpleMessageDispatcher::CancelMessage(unsigned int)
// vaddr 0x2236fc8 | ghidra 0x2336fc8 | size 348 | symbol _ZN4Aska23SimpleMessageDispatcher13CancelMessageEj | lib libSOA-3.7.0.so | 2026-10-04
uint _ZN4Aska23SimpleMessageDispatcher13CancelMessageEj(long param_1,undefined4 param_2)

{
  int *piVar1;
  int *piVar2;
  char cVar3;
  bool bVar4;
  uint uVar5;
  ulong uVar6;
  int iVar7;
  
  piVar1 = (int *)(param_1 + 0x40);
  iVar7 = 0;
  do {
    while (*piVar1 != -1) {
      ClearExclusiveLocal();
      bVar4 = 0x1fe < iVar7;
      iVar7 = iVar7 + 1;
      if (bVar4) {
        piVar2 = (int *)(param_1 + 0x44);
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
              uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x80);
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
                Aska::Semaphore::Wait() const(param_1 + 0x80);
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
                if (cVar3 == '\0') goto code_r0x0233710c;
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
code_r0x0233710c:
        do {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
          if (bVar4) {
            *piVar2 = *piVar2 + -1;
            cVar3 = ExclusiveMonitorsStatus();
          }
        } while (cVar3 != '\0');
        DataMemoryBarrier(2,3);
code_r0x02337040:
        uVar5 = Aska::SimpleMessageDispatcher::DeleteMessage(int)(param_1,param_2);
        DataMemoryBarrier(2,3);
        *(undefined4 *)(param_1 + 0x40) = 0xffffffff;
        DataMemoryBarrier(2,3);
        piVar1 = (int *)(param_1 + 0x44);
        if (0x14 < *piVar1) {
          do {
            cVar3 = '\x01';
            bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
            if (bVar4) {
              *piVar1 = *piVar1 + -1;
              cVar3 = ExclusiveMonitorsStatus();
            }
          } while (cVar3 != '\0');
          uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x80);
          if ((uVar6 & 1) != 0) {
            Aska::Semaphore::Signal() const(param_1 + 0x80);
          }
        }
        return uVar5 & 1;
      }
    }
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar4) {
      *piVar1 = 0;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
  DataMemoryBarrier(2,3);
  goto code_r0x02337040;
}


// FAILED to create function at 02971690 typeinfo name for Aska::SimpleMessageDispatcher::_WorkerThread
// FAILED to create function at 02bb2b58 Aska::SimpleMessageDispatcher::_WorkerThread::vtable
// FAILED to create function at 02bb2b80 Aska::SimpleMessageDispatcher::_WorkerThread::typeinfo
// FAILED to create function at 02bb2b98 Aska::SimpleMessageDispatcher::vtable
// FAILED to create function at 02bb2bc8 Aska::SimpleMessageDispatcher::typeinfo
