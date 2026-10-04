// port/decomp/memory/memory_manager.c: Ghidra decompiles for the memory subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-04 05:04 UTC: tools/decomp.sh '--into' 'memory/memory_manager' 'Aska::MemoryManager::' 'Aska::MemoryManagerAdapter::' 'Aska::_MemoryBlock'

// ==== Aska::MemoryManager::InitHeap(unsigned char*, unsigned long)
// vaddr 0x1f49e3c | ghidra 0x2049e3c | size 324 | symbol _ZN4Aska13MemoryManager8InitHeapEPhm | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska13MemoryManager8InitHeapEPhm(long param_1,long param_2,long param_3)

{
  undefined1 *puVar1;
  uint uVar2;
  undefined1 auVar3 [16];
  undefined8 uVar4;
  long lVar5;
  long lVar6;
  ulong uVar7;
  int iVar8;
  undefined8 *puVar9;
  long *plVar10;
  ulong uVar11;
  
  lVar5 = *(long *)(param_1 + 0x20);
  if (lVar5 != 0) {
    if (*(char *)(param_1 + 0x38) != '\0') {
      Aska::MemoryManager::LocalFree(Aska::_MemoryBlock*)(*(undefined8 *)(lVar5 + -0x18),lVar5 + -0x40);
    }
    *(undefined8 *)(param_1 + 0x20) = 0;
    *(undefined8 *)(param_1 + 0x10) = 0;
    *(undefined1 *)(param_1 + 0x38) = 0;
  }
  if (param_2 == 0) {
    uVar4 = 0;
  }
  else {
    auVar3._8_8_ = 0;
    auVar3._0_8_ = param_3 + 0xffaeU;
    uVar11 = (param_3 + 0xffaeU) / 0x10028 & 0xffffffff;
    uVar7 = param_3 + uVar11 * -0x28 & 0xfffffffffffffff0;
    puVar1 = (undefined1 *)(param_2 + uVar7);
    *(long *)(param_1 + 0x20) = param_2;
    *(undefined1 *)(param_1 + 0x38) = 0;
    iVar8 = SUB164(auVar3 * ZEXT816(0xffd8063f062709e7),10);
    *(int *)(param_1 + 0x18) = iVar8;
    *(undefined1 **)(param_1 + 0x10) = puVar1;
    if (uVar7 + uVar11 * -0x10000 + 0x10000 < 0x80) {
      uVar2 = iVar8 - 1;
      *(uint *)(param_1 + 0x18) = uVar2;
      if (uVar2 == 0) {
        *(undefined8 *)(param_1 + 0x20) = 0;
        return 0;
      }
      uVar7 = (ulong)uVar2 << 0x10;
    }
    uVar4 = 1;
    *(ulong *)(param_1 + 0x28) = uVar7;
    *(undefined8 *)(puVar1 + 4) = 0;
    *puVar1 = 1;
    puVar9 = *(undefined8 **)(param_1 + 0x20);
    lVar5 = uVar7 - 0x40;
    *puVar9 = 0x40;
    *(undefined2 *)(puVar9 + 6) = 0x100;
    puVar9[7] = 0;
    plVar10 = puVar9 + 8;
    *plVar10 = lVar5;
    *(undefined2 *)(puVar9 + 0xe) = 0;
    puVar9[0xb] = puVar9;
    puVar9[0xc] = puVar9;
    puVar9[9] = puVar9;
    puVar9[10] = puVar9;
    puVar9[3] = plVar10;
    puVar9[4] = plVar10;
    puVar9[1] = plVar10;
    puVar9[2] = plVar10;
    *(undefined8 *)(puVar1 + 0x10) = 0;
    *(long *)(puVar1 + 0x18) = lVar5;
    *(long *)(puVar1 + 0x20) = lVar5;
    if (1 < *(uint *)(param_1 + 0x18)) {
      lVar6 = (ulong)*(uint *)(param_1 + 0x18) - 1;
      lVar5 = 0x28;
      do {
        lVar6 = lVar6 + -1;
        *(undefined1 *)(*(long *)(param_1 + 0x10) + lVar5) = 0;
        lVar5 = lVar5 + 0x28;
      } while (lVar6 != 0);
      uVar4 = 1;
    }
  }
  return uVar4;
}

// ==== Aska::MemoryManager::GetAllocatedManager(void const*, unsigned long*)
// vaddr 0x1f49fd0 | ghidra 0x2049fd0 | size 20 | symbol _ZN4Aska13MemoryManager19GetAllocatedManagerEPKvPm | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska13MemoryManager19GetAllocatedManagerEPKvPm(long param_1,undefined8 *param_2)

{
  if (param_2 != (undefined8 *)0x0) {
    *param_2 = *(undefined8 *)(param_1 + -0x40);
  }
  return *(undefined8 *)(param_1 + -0x18);
}

// ==== Aska::MemoryManager::GetAllocatedManager(void const*)
// vaddr 0x1f49fe4 | ghidra 0x2049fe4 | size 8 | symbol _ZN4Aska13MemoryManager19GetAllocatedManagerEPKv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska13MemoryManager19GetAllocatedManagerEPKv(long param_1)

{
  return *(undefined8 *)(param_1 + -0x18);
}

// ==== Aska::MemoryManager::LocalRegisterNotify(void*, Aska::IMemoryNotify*)
// vaddr 0x1f49fec | ghidra 0x2049fec | size 36 | symbol _ZN4Aska13MemoryManager19LocalRegisterNotifyEPvPNS_13IMemoryNotifyE | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska13MemoryManager19LocalRegisterNotifyEPvPNS_13IMemoryNotifyE(long param_1,long param_2)

{
  if ((*(long *)(param_1 + -8) != 0) && (*(long *)(param_1 + -8) != param_2)) {
    return 0;
  }
  *(long *)(param_1 + -8) = param_2;
  return 1;
}

// ==== Aska::MemoryManager::LocalRemoveNotify(void*, Aska::IMemoryNotify*)
// vaddr 0x1f4a010 | ghidra 0x204a010 | size 36 | symbol _ZN4Aska13MemoryManager17LocalRemoveNotifyEPvPNS_13IMemoryNotifyE | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska13MemoryManager17LocalRemoveNotifyEPvPNS_13IMemoryNotifyE(long param_1,long param_2)

{
  if ((param_2 != 0) && (*(long *)(param_1 + -8) != param_2)) {
    return 0;
  }
  *(undefined8 *)(param_1 + -8) = 0;
  return 1;
}

// ==== Aska::MemoryManager::LocalIsRegisteredNotify(void*, Aska::IMemoryNotify*)
// vaddr 0x1f4a034 | ghidra 0x204a034 | size 44 | symbol _ZN4Aska13MemoryManager23LocalIsRegisteredNotifyEPvPNS_13IMemoryNotifyE | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska13MemoryManager23LocalIsRegisteredNotifyEPvPNS_13IMemoryNotifyE(long param_1,long param_2)

{
  if (param_2 == 0) {
    if (*(long *)(param_1 + -8) != 0) {
      return 1;
    }
  }
  else if (*(long *)(param_1 + -8) == param_2) {
    return 1;
  }
  return 0;
}

// ==== Aska::MemoryManager::LocalGetRegisteredNotify(void*)
// vaddr 0x1f4a060 | ghidra 0x204a060 | size 8 | symbol _ZN4Aska13MemoryManager24LocalGetRegisteredNotifyEPv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska13MemoryManager24LocalGetRegisteredNotifyEPv(long param_1)

{
  return *(undefined8 *)(param_1 + -8);
}

// ==== Aska::MemoryManager::RegisterNotify(void*, Aska::IMemoryNotify*)
// vaddr 0x1f4a068 | ghidra 0x204a068 | size 380 | symbol _ZN4Aska13MemoryManager14RegisterNotifyEPvPNS_13IMemoryNotifyE | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZN4Aska13MemoryManager14RegisterNotifyEPvPNS_13IMemoryNotifyE(long param_1,long param_2)

{
  int *piVar1;
  char cVar2;
  bool bVar3;
  ulong uVar4;
  int iVar5;
  undefined4 uVar6;
  long lVar7;
  int *piVar8;
  
  lVar7 = *(long *)(param_1 + -0x18);
  if (lVar7 == 0) {
    return 0;
  }
  piVar8 = (int *)(lVar7 + 0x98);
  iVar5 = 0;
  do {
    while (*piVar8 == -1) {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar8,0x10);
      if (bVar3) {
        *piVar8 = 0;
        cVar2 = ExclusiveMonitorsStatus();
      }
      if (cVar2 == '\0') goto code_r0x0204a164;
    }
    ClearExclusiveLocal();
    bVar3 = iVar5 < 0x1ff;
    iVar5 = iVar5 + 1;
  } while (bVar3);
  piVar1 = (int *)(lVar7 + 0x9c);
  do {
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar3) {
      *piVar1 = *piVar1 + 1;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
  do {
    if (*piVar8 != -1) {
      ClearExclusiveLocal();
      do {
        uVar4 = Aska::Semaphore::IsReady() const(lVar7 + 0xd8);
        if ((uVar4 & 1) == 0) {
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
          Aska::Semaphore::Wait() const(lVar7 + 0xd8);
        }
        do {
          cVar2 = '\x01';
          bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar3) {
            *piVar1 = *piVar1 + 1;
            cVar2 = ExclusiveMonitorsStatus();
          }
        } while (cVar2 != '\0');
        while (*piVar8 == -1) {
          cVar2 = '\x01';
          bVar3 = (bool)ExclusiveMonitorPass(piVar8,0x10);
          if (bVar3) {
            *piVar8 = 0;
            cVar2 = ExclusiveMonitorsStatus();
          }
          if (cVar2 == '\0') goto code_r0x0204a154;
        }
        ClearExclusiveLocal();
      } while( true );
    }
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar8,0x10);
    if (bVar3) {
      *piVar8 = 0;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
code_r0x0204a154:
  do {
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar3) {
      *piVar1 = *piVar1 + -1;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
code_r0x0204a164:
  DataMemoryBarrier(2,3);
  if ((*(long *)(param_1 + -8) == 0) || (*(long *)(param_1 + -8) == param_2)) {
    *(long *)(param_1 + -8) = param_2;
    uVar6 = 1;
  }
  else {
    uVar6 = 0;
  }
  DataMemoryBarrier(2,3);
  *(undefined4 *)(lVar7 + 0x98) = 0xffffffff;
  DataMemoryBarrier(2,3);
  piVar8 = (int *)(lVar7 + 0x9c);
  if (*piVar8 < 0x15) {
    return uVar6;
  }
  do {
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar8,0x10);
    if (bVar3) {
      *piVar8 = *piVar8 + -1;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
  uVar4 = Aska::Semaphore::IsReady() const(lVar7 + 0xd8);
  if ((uVar4 & 1) == 0) {
    return uVar6;
  }
  Aska::Semaphore::Signal() const(lVar7 + 0xd8);
  return uVar6;
}

// ==== Aska::MemoryManager::RemoveNotify(void*, Aska::IMemoryNotify*)
// vaddr 0x1f4a1e4 | ghidra 0x204a1e4 | size 380 | symbol _ZN4Aska13MemoryManager12RemoveNotifyEPvPNS_13IMemoryNotifyE | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZN4Aska13MemoryManager12RemoveNotifyEPvPNS_13IMemoryNotifyE(long param_1,long param_2)

{
  int *piVar1;
  char cVar2;
  bool bVar3;
  ulong uVar4;
  int iVar5;
  undefined4 uVar6;
  long lVar7;
  int *piVar8;
  
  lVar7 = *(long *)(param_1 + -0x18);
  if (lVar7 == 0) {
    return 0;
  }
  piVar8 = (int *)(lVar7 + 0x98);
  iVar5 = 0;
  do {
    while (*piVar8 == -1) {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar8,0x10);
      if (bVar3) {
        *piVar8 = 0;
        cVar2 = ExclusiveMonitorsStatus();
      }
      if (cVar2 == '\0') goto code_r0x0204a2e0;
    }
    ClearExclusiveLocal();
    bVar3 = iVar5 < 0x1ff;
    iVar5 = iVar5 + 1;
  } while (bVar3);
  piVar1 = (int *)(lVar7 + 0x9c);
  do {
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar3) {
      *piVar1 = *piVar1 + 1;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
  do {
    if (*piVar8 != -1) {
      ClearExclusiveLocal();
      do {
        uVar4 = Aska::Semaphore::IsReady() const(lVar7 + 0xd8);
        if ((uVar4 & 1) == 0) {
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
          Aska::Semaphore::Wait() const(lVar7 + 0xd8);
        }
        do {
          cVar2 = '\x01';
          bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar3) {
            *piVar1 = *piVar1 + 1;
            cVar2 = ExclusiveMonitorsStatus();
          }
        } while (cVar2 != '\0');
        while (*piVar8 == -1) {
          cVar2 = '\x01';
          bVar3 = (bool)ExclusiveMonitorPass(piVar8,0x10);
          if (bVar3) {
            *piVar8 = 0;
            cVar2 = ExclusiveMonitorsStatus();
          }
          if (cVar2 == '\0') goto code_r0x0204a2d0;
        }
        ClearExclusiveLocal();
      } while( true );
    }
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar8,0x10);
    if (bVar3) {
      *piVar8 = 0;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
code_r0x0204a2d0:
  do {
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar3) {
      *piVar1 = *piVar1 + -1;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
code_r0x0204a2e0:
  DataMemoryBarrier(2,3);
  if ((param_2 == 0) || (*(long *)(param_1 + -8) == param_2)) {
    *(undefined8 *)(param_1 + -8) = 0;
    uVar6 = 1;
  }
  else {
    uVar6 = 0;
  }
  DataMemoryBarrier(2,3);
  *(undefined4 *)(lVar7 + 0x98) = 0xffffffff;
  DataMemoryBarrier(2,3);
  piVar8 = (int *)(lVar7 + 0x9c);
  if (*piVar8 < 0x15) {
    return uVar6;
  }
  do {
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar8,0x10);
    if (bVar3) {
      *piVar8 = *piVar8 + -1;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
  uVar4 = Aska::Semaphore::IsReady() const(lVar7 + 0xd8);
  if ((uVar4 & 1) == 0) {
    return uVar6;
  }
  Aska::Semaphore::Signal() const(lVar7 + 0xd8);
  return uVar6;
}

// ==== Aska::MemoryManager::IsRegisteredNotify(void*, Aska::IMemoryNotify*)
// vaddr 0x1f4a360 | ghidra 0x204a360 | size 380 | symbol _ZN4Aska13MemoryManager18IsRegisteredNotifyEPvPNS_13IMemoryNotifyE | lib libSOA-3.7.0.so | 2026-10-04
undefined4
_ZN4Aska13MemoryManager18IsRegisteredNotifyEPvPNS_13IMemoryNotifyE(long param_1,long param_2)

{
  int *piVar1;
  char cVar2;
  bool bVar3;
  ulong uVar4;
  int iVar5;
  undefined4 uVar6;
  long lVar7;
  int *piVar8;
  
  lVar7 = *(long *)(param_1 + -0x18);
  if (lVar7 == 0) {
    return 0;
  }
  piVar8 = (int *)(lVar7 + 0x98);
  iVar5 = 0;
  do {
    while (*piVar8 == -1) {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar8,0x10);
      if (bVar3) {
        *piVar8 = 0;
        cVar2 = ExclusiveMonitorsStatus();
      }
      if (cVar2 == '\0') goto code_r0x0204a45c;
    }
    ClearExclusiveLocal();
    bVar3 = iVar5 < 0x1ff;
    iVar5 = iVar5 + 1;
  } while (bVar3);
  piVar1 = (int *)(lVar7 + 0x9c);
  do {
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar3) {
      *piVar1 = *piVar1 + 1;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
  do {
    if (*piVar8 != -1) {
      ClearExclusiveLocal();
      do {
        uVar4 = Aska::Semaphore::IsReady() const(lVar7 + 0xd8);
        if ((uVar4 & 1) == 0) {
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
          Aska::Semaphore::Wait() const(lVar7 + 0xd8);
        }
        do {
          cVar2 = '\x01';
          bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar3) {
            *piVar1 = *piVar1 + 1;
            cVar2 = ExclusiveMonitorsStatus();
          }
        } while (cVar2 != '\0');
        while (*piVar8 == -1) {
          cVar2 = '\x01';
          bVar3 = (bool)ExclusiveMonitorPass(piVar8,0x10);
          if (bVar3) {
            *piVar8 = 0;
            cVar2 = ExclusiveMonitorsStatus();
          }
          if (cVar2 == '\0') goto code_r0x0204a44c;
        }
        ClearExclusiveLocal();
      } while( true );
    }
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar8,0x10);
    if (bVar3) {
      *piVar8 = 0;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
code_r0x0204a44c:
  do {
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar3) {
      *piVar1 = *piVar1 + -1;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
code_r0x0204a45c:
  DataMemoryBarrier(2,3);
  if (param_2 == 0) {
    if (*(long *)(param_1 + -8) != 0) goto code_r0x0204a47c;
  }
  else if (*(long *)(param_1 + -8) == param_2) {
code_r0x0204a47c:
    uVar6 = 1;
    goto code_r0x0204a480;
  }
  uVar6 = 0;
code_r0x0204a480:
  DataMemoryBarrier(2,3);
  *(undefined4 *)(lVar7 + 0x98) = 0xffffffff;
  DataMemoryBarrier(2,3);
  piVar8 = (int *)(lVar7 + 0x9c);
  if (*piVar8 < 0x15) {
    return uVar6;
  }
  do {
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar8,0x10);
    if (bVar3) {
      *piVar8 = *piVar8 + -1;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
  uVar4 = Aska::Semaphore::IsReady() const(lVar7 + 0xd8);
  if ((uVar4 & 1) == 0) {
    return uVar6;
  }
  Aska::Semaphore::Signal() const(lVar7 + 0xd8);
  return uVar6;
}

// ==== Aska::MemoryManager::GetRegisteredNotify(void*)
// vaddr 0x1f4a4dc | ghidra 0x204a4dc | size 348 | symbol _ZN4Aska13MemoryManager19GetRegisteredNotifyEPv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska13MemoryManager19GetRegisteredNotifyEPv(long param_1)

{
  int *piVar1;
  char cVar2;
  bool bVar3;
  ulong uVar4;
  int iVar5;
  undefined8 uVar6;
  long lVar7;
  int *piVar8;
  
  lVar7 = *(long *)(param_1 + -0x18);
  if (lVar7 == 0) {
    return 0;
  }
  piVar1 = (int *)(lVar7 + 0x98);
  iVar5 = 0;
  do {
    while (*piVar1 != -1) {
      ClearExclusiveLocal();
      bVar3 = 0x1fe < iVar5;
      iVar5 = iVar5 + 1;
      if (bVar3) {
        piVar8 = (int *)(lVar7 + 0x9c);
        do {
          cVar2 = '\x01';
          bVar3 = (bool)ExclusiveMonitorPass(piVar8,0x10);
          if (bVar3) {
            *piVar8 = *piVar8 + 1;
            cVar2 = ExclusiveMonitorsStatus();
          }
        } while (cVar2 != '\0');
        do {
          if (*piVar1 != -1) {
            ClearExclusiveLocal();
            do {
              uVar4 = Aska::Semaphore::IsReady() const(lVar7 + 0xd8);
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
                Aska::Semaphore::Wait() const(lVar7 + 0xd8);
              }
              do {
                cVar2 = '\x01';
                bVar3 = (bool)ExclusiveMonitorPass(piVar8,0x10);
                if (bVar3) {
                  *piVar8 = *piVar8 + 1;
                  cVar2 = ExclusiveMonitorsStatus();
                }
              } while (cVar2 != '\0');
              while (*piVar1 == -1) {
                cVar2 = '\x01';
                bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
                if (bVar3) {
                  *piVar1 = 0;
                  cVar2 = ExclusiveMonitorsStatus();
                }
                if (cVar2 == '\0') goto code_r0x0204a620;
              }
              ClearExclusiveLocal();
            } while( true );
          }
          cVar2 = '\x01';
          bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar3) {
            *piVar1 = 0;
            cVar2 = ExclusiveMonitorsStatus();
          }
        } while (cVar2 != '\0');
code_r0x0204a620:
        do {
          cVar2 = '\x01';
          bVar3 = (bool)ExclusiveMonitorPass(piVar8,0x10);
          if (bVar3) {
            *piVar8 = *piVar8 + -1;
            cVar2 = ExclusiveMonitorsStatus();
          }
        } while (cVar2 != '\0');
        DataMemoryBarrier(2,3);
        goto code_r0x0204a558;
      }
    }
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar3) {
      *piVar1 = 0;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
  DataMemoryBarrier(2,3);
code_r0x0204a558:
  piVar8 = (int *)(lVar7 + 0x9c);
  uVar6 = *(undefined8 *)(param_1 + -8);
  DataMemoryBarrier(2,3);
  *piVar1 = -1;
  DataMemoryBarrier(2,3);
  if (*piVar8 < 0x15) {
    return uVar6;
  }
  do {
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar8,0x10);
    if (bVar3) {
      *piVar8 = *piVar8 + -1;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
  uVar4 = Aska::Semaphore::IsReady() const(lVar7 + 0xd8);
  if ((uVar4 & 1) == 0) {
    return uVar6;
  }
  Aska::Semaphore::Signal() const(lVar7 + 0xd8);
  return uVar6;
}

// ==== Aska::MemoryManager::CalcSrbkSize(unsigned long)
// vaddr 0x1f4a638 | ghidra 0x204a638 | size 24 | symbol _ZN4Aska13MemoryManager12CalcSrbkSizeEm | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska13MemoryManager12CalcSrbkSizeEm(long param_1)

{
  return (param_1 + 0xffffU >> 0x10) * 0x28;
}

// ==== Aska::MemoryManager::CalcFullHeapSize(unsigned long)
// vaddr 0x1f4a650 | ghidra 0x204a650 | size 32 | symbol _ZN4Aska13MemoryManager16CalcFullHeapSizeEm | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZN4Aska13MemoryManager16CalcFullHeapSizeEm(long param_1)

{
  return param_1 + (param_1 + 0xffffU >> 0x10) * 0x28 + 0xf & 0xfffffffffffffff0;
}

// ==== Aska::MemoryManager::CalcFullHeapSizeForOneBlock(unsigned long, long, bool)
// vaddr 0x1f4a670 | ghidra 0x204a670 | size 44 | symbol _ZN4Aska13MemoryManager27CalcFullHeapSizeForOneBlockEmlb | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZN4Aska13MemoryManager27CalcFullHeapSizeForOneBlockEmlb(long param_1,long param_2)

{
  ulong uVar1;
  
  uVar1 = param_1 + param_2 + 0x8f;
  return (uVar1 | 0xf) + ((uVar1 & 0xfffffffffffffff0) + 0xffff >> 0x10) * 0x28 & 0xfffffffffffffff0
  ;
}

// ==== Aska::MemoryManager::LocalFree(Aska::_MemoryBlock*)
// vaddr 0x1f4a6b4 | ghidra 0x204a6b4 | size 1492 | symbol _ZN4Aska13MemoryManager9LocalFreeEPNS_12_MemoryBlockE | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Possible PIC construction at 0x0204a7f4: Changing call to branch */

void _ZN4Aska13MemoryManager9LocalFreeEPNS_12_MemoryBlockE(long param_1,ulong *param_2)

{
  long lVar1;
  uint uVar2;
  char cVar3;
  bool bVar4;
  ulong uVar5;
  int iVar6;
  char *pcVar7;
  int *piVar8;
  ulong uVar9;
  undefined1 *puVar10;
  long *plVar11;
  ulong *puVar12;
  ulong *puVar13;
  char *pcVar14;
  char *pcVar15;
  ulong *puVar16;
  long lVar17;
  int *piVar18;
  ulong uVar19;
  ulong uVar20;
  ulong uVar21;
  ulong uVar22;
  ulong uVar23;
  ulong uVar24;
  ulong uVar25;
  ulong uVar26;
  
  piVar8 = (int *)(param_1 + 0x98);
  iVar6 = 0;
code_r0x0204a6d0:
  if (*piVar8 == -1) {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar8,0x10);
    if (bVar4) {
      *piVar8 = 0;
      cVar3 = ExclusiveMonitorsStatus();
    }
    if (cVar3 == '\0') goto code_r0x0204a798;
    goto code_r0x0204a6d0;
  }
  ClearExclusiveLocal();
  bVar4 = iVar6 < 0x1ff;
  iVar6 = iVar6 + 1;
  if (bVar4) goto code_r0x0204a6d0;
  piVar18 = (int *)(param_1 + 0x9c);
  do {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar18,0x10);
    if (bVar4) {
      *piVar18 = *piVar18 + 1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
  do {
    if (*piVar8 != -1) {
      ClearExclusiveLocal();
      do {
        uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0xd8);
        if ((uVar5 & 1) == 0) {
          do {
            cVar3 = '\x01';
            bVar4 = (bool)ExclusiveMonitorPass(piVar18,0x10);
            if (bVar4) {
              *piVar18 = *piVar18 + -1;
              cVar3 = ExclusiveMonitorsStatus();
            }
          } while (cVar3 != '\0');
          Aska::Thread::Sleep(unsigned int)(1);
        }
        else {
          Aska::Semaphore::Wait() const(param_1 + 0xd8);
        }
        do {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar18,0x10);
          if (bVar4) {
            *piVar18 = *piVar18 + 1;
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
          if (cVar3 == '\0') goto code_r0x0204a788;
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
code_r0x0204a788:
  do {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar18,0x10);
    if (bVar4) {
      *piVar18 = *piVar18 + -1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
code_r0x0204a798:
  DataMemoryBarrier(2,3);
  if (*(char *)((long)param_2 + 0x31) == '\x01') {
    if (param_2[7] != 0) {
      DataMemoryBarrier(2,3);
      *(undefined4 *)(param_1 + 0x98) = 0xffffffff;
      DataMemoryBarrier(2,3);
      piVar18 = (int *)(param_1 + 0x9c);
      if (0x14 < *piVar18) {
        do {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar18,0x10);
          if (bVar4) {
            *piVar18 = *piVar18 + -1;
            cVar3 = ExclusiveMonitorsStatus();
          }
        } while (cVar3 != '\0');
        uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0xd8);
        if ((uVar5 & 1) != 0) goto code_r0x011bd9c0;
      }
      (**(code **)(*(long *)param_2[7] + 8))((long *)param_2[7],param_2 + 8);
      iVar6 = 0;
      do {
        while (*piVar8 == -1) {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar8,0x10);
          if (bVar4) {
            *piVar8 = 0;
            cVar3 = ExclusiveMonitorsStatus();
          }
          if (cVar3 == '\0') goto code_r0x0204a908;
        }
        ClearExclusiveLocal();
        bVar4 = iVar6 < 0x1ff;
        iVar6 = iVar6 + 1;
      } while (bVar4);
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar18,0x10);
        if (bVar4) {
          *piVar18 = *piVar18 + 1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      do {
        if (*piVar8 != -1) {
          ClearExclusiveLocal();
          do {
            uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0xd8);
            if ((uVar5 & 1) == 0) {
              do {
                cVar3 = '\x01';
                bVar4 = (bool)ExclusiveMonitorPass(piVar18,0x10);
                if (bVar4) {
                  *piVar18 = *piVar18 + -1;
                  cVar3 = ExclusiveMonitorsStatus();
                }
              } while (cVar3 != '\0');
              Aska::Thread::Sleep(unsigned int)(1);
            }
            else {
              Aska::Semaphore::Wait() const(param_1 + 0xd8);
            }
            do {
              cVar3 = '\x01';
              bVar4 = (bool)ExclusiveMonitorPass(piVar18,0x10);
              if (bVar4) {
                *piVar18 = *piVar18 + 1;
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
              if (cVar3 == '\0') goto code_r0x0204a8f8;
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
code_r0x0204a8f8:
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar18,0x10);
        if (bVar4) {
          *piVar18 = *piVar18 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
code_r0x0204a908:
      DataMemoryBarrier(2,3);
      param_2[7] = 0;
      if (*(char *)((long)param_2 + 0x31) == '\0') {
        DataMemoryBarrier(2,3);
        *piVar8 = -1;
        DataMemoryBarrier(2,3);
        if (*piVar18 < 0x15) {
          return;
        }
        do {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar18,0x10);
          if (bVar4) {
            *piVar18 = *piVar18 + -1;
            cVar3 = ExclusiveMonitorsStatus();
          }
        } while (cVar3 != '\0');
        goto code_r0x0204ab74;
      }
    }
    uVar9 = *param_2;
    pcVar7 = (char *)0x0;
    uVar5 = (ulong)((long)param_2 - *(long *)(param_1 + 0x20)) >> 0x10;
    lVar17 = uVar5 * 0x28;
    uVar19 = uVar5 + 1;
    do {
      uVar20 = uVar19 - 1;
      if ((long)uVar19 < 1) goto code_r0x0204a964;
      pcVar7 = (char *)(*(long *)(param_1 + 0x10) + lVar17);
      lVar17 = lVar17 + -0x28;
      uVar19 = uVar20;
    } while (*pcVar7 == '\0');
    pcVar7 = (char *)(*(long *)(param_1 + 0x10) + lVar17 + 0x28);
    uVar5 = uVar20;
code_r0x0204a964:
    puVar16 = (ulong *)param_2[2];
    if (*(char *)((long)puVar16 + 0x31) == '\x01') {
      puVar12 = (ulong *)(*(long *)(param_1 + 0x20) + uVar5 * 0x10000);
      if ((puVar16 == puVar12) && (uVar5 = *puVar12, 0x40 < uVar5)) {
        *puVar12 = 0x40;
        *(undefined1 *)((long)param_2 + 0x31) = 0;
        uVar20 = param_2[5];
        uVar19 = param_2[4];
        uVar22 = param_2[7];
        uVar21 = param_2[6];
        uVar24 = param_2[1];
        uVar23 = *param_2;
        uVar26 = param_2[3];
        uVar25 = param_2[2];
        uVar9 = (uVar9 + uVar5) - 0x40;
        puVar16 = puVar12 + 8;
        puVar12[1] = (ulong)puVar16;
        puVar12[9] = uVar24;
        puVar12[8] = uVar23;
        puVar12[0xb] = uVar26;
        puVar12[10] = uVar25;
        puVar12[0xd] = uVar20;
        puVar12[0xc] = uVar19;
        puVar12[0xf] = uVar22;
        puVar12[0xe] = uVar21;
        puVar12[8] = uVar9;
        puVar12[0xb] = puVar12[3];
        *(ulong **)(puVar12[3] + 0x20) = puVar16;
        puVar12[0xc] = (ulong)puVar12;
        puVar12[3] = (ulong)puVar16;
        *(ulong **)(puVar12[9] + 0x10) = puVar16;
      }
      else {
        puVar13 = (ulong *)param_2[1];
        puVar16 = puVar12;
        if (*(char *)((long)puVar13 + 0x31) == '\x01') {
          do {
            puVar13 = (ulong *)puVar16[3];
            if (param_2 <= puVar13) break;
            puVar16 = puVar13;
          } while (puVar13 != puVar12);
          uVar5 = puVar13[4];
          param_2[3] = (ulong)puVar13;
        }
        else {
          param_2[3] = (ulong)puVar13;
          uVar5 = puVar13[4];
        }
        param_2[4] = uVar5;
        puVar13[4] = (ulong)param_2;
        *(ulong **)(param_2[4] + 0x18) = param_2;
        puVar16 = param_2;
      }
    }
    else {
      puVar16[1] = param_2[1];
      *(ulong **)(param_2[1] + 0x10) = puVar16;
      *puVar16 = *puVar16 + uVar9;
      *(undefined1 *)((long)param_2 + 0x31) = 0;
    }
    plVar11 = (long *)puVar16[1];
    if (*(char *)((long)plVar11 + 0x31) != '\x01') {
      *puVar16 = *puVar16 + *plVar11;
      puVar16[1] = plVar11[1];
      puVar16[3] = plVar11[3];
      *(ulong **)(puVar16[4] + 0x18) = puVar16;
      *(ulong **)(plVar11[3] + 0x20) = puVar16;
      *(ulong **)(plVar11[1] + 0x10) = puVar16;
    }
    *(undefined1 *)((long)puVar16 + 0x31) = 0;
    lVar17 = *(long *)(pcVar7 + 0x10);
    lVar1 = *(long *)(pcVar7 + 0x18);
    *(ulong *)(pcVar7 + 0x10) = lVar17 - uVar9;
    *(ulong *)(pcVar7 + 0x18) = lVar1 + uVar9;
    pcVar15 = pcVar7;
    if (lVar17 - uVar9 == 0) {
      pcVar14 = *(char **)(param_1 + 0x10);
      if (pcVar7 != pcVar14) {
        uVar2 = *(uint *)(pcVar7 + 8);
        uVar5 = (ulong)uVar2;
        if (*(long *)(pcVar14 + uVar5 * 0x28 + 0x10) == 0) {
          *pcVar7 = '\0';
          pcVar15 = pcVar14 + uVar5 * 0x28;
          lVar17 = lVar1 + uVar9 + *(long *)(pcVar15 + 0x18) + 0x40;
          *(long *)(pcVar15 + 0x18) = lVar17;
          **(long **)(*(long *)(param_1 + 0x20) + uVar5 * 0x10000 + 0x18) = lVar17;
          *(undefined4 *)(pcVar15 + 4) = *(undefined4 *)(pcVar7 + 4);
          *(uint *)(*(long *)(param_1 + 0x10) + (ulong)*(uint *)(pcVar7 + 4) * 0x28 + 8) = uVar2;
        }
      }
      uVar2 = *(uint *)(pcVar15 + 4);
      if ((uVar2 != 0) && (*(long *)(*(long *)(param_1 + 0x10) + (ulong)uVar2 * 0x28 + 0x10) == 0))
      {
        puVar10 = (undefined1 *)(*(long *)(param_1 + 0x10) + (ulong)uVar2 * 0x28);
        *puVar10 = 0;
        *(undefined4 *)(pcVar15 + 4) = *(undefined4 *)(puVar10 + 4);
        *(undefined4 *)(*(long *)(param_1 + 0x10) + (ulong)*(uint *)(puVar10 + 4) * 0x28 + 8) =
             *(undefined4 *)(puVar10 + 8);
        lVar17 = *(long *)(puVar10 + 0x18) + *(long *)(pcVar15 + 0x18) + 0x40;
        *(long *)(pcVar15 + 0x18) = lVar17;
        **(long **)(*(long *)(param_1 + 0x20) + (ulong)*(uint *)(puVar10 + 8) * 0x10000 + 0x18) =
             lVar17;
      }
    }
    puVar16 = (ulong *)(*(long *)(param_1 + 0x20) +
                       ((ulong)((long)pcVar15 - *(long *)(param_1 + 0x10)) >> 3) *
                       -0x3333333333330000);
    puVar12 = (ulong *)puVar16[3];
    if (puVar16 < puVar12) {
      uVar19 = 0;
      do {
        uVar5 = uVar19;
        if ((*(char *)((long)puVar12 + 0x31) != '\x01') && (uVar5 = *puVar12, *puVar12 <= uVar19)) {
          uVar5 = uVar19;
        }
        puVar12 = (ulong *)puVar12[3];
        uVar19 = uVar5;
      } while (puVar16 < puVar12);
    }
    else {
      uVar5 = 0;
    }
    *(ulong *)(pcVar15 + 0x20) = uVar5;
    DataMemoryBarrier(2,3);
    *(undefined4 *)(param_1 + 0x98) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar8 = (int *)(param_1 + 0x9c);
    if (*piVar8 < 0x15) {
      return;
    }
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar8,0x10);
      if (bVar4) {
        *piVar8 = *piVar8 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
  }
  else {
    DataMemoryBarrier(2,3);
    *(undefined4 *)(param_1 + 0x98) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar8 = (int *)(param_1 + 0x9c);
    if (*piVar8 < 0x15) {
      return;
    }
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar8,0x10);
      if (bVar4) {
        *piVar8 = *piVar8 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
  }
code_r0x0204ab74:
  uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0xd8);
  if ((uVar5 & 1) == 0) {
    return;
  }
code_r0x011bd9c0:
  (*(code *)PTR__ZNK4Aska9Semaphore6SignalEv_02c96cd0)(param_1 + 0xd8);
  return;
}

// ==== Aska::MemoryManager::MemoryManager()
// vaddr 0x1f4acb8 | ghidra 0x204acb8 | size 60 | symbol _ZN4Aska13MemoryManagerC2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13MemoryManagerC1Ev(long *param_1)

{
  *(undefined1 *)(param_1 + 1) = 0;
  *param_1 = (long)(PTR__ZTVN4Aska13MemoryManagerE_02cb9280 + 0x10);
  Aska::FastCriticalSection::FastCriticalSection()(param_1 + 0xc);
  param_1[5] = 0;
  param_1[6] = 0;
  param_1[4] = 0;
  param_1[8] = (long)param_1;
  param_1[9] = (long)param_1;
  param_1[10] = (long)param_1;
  param_1[0xb] = 0;
  return;
}

// ==== Aska::MemoryManager::Initialize()
// vaddr 0x1f4acf4 | ghidra 0x204acf4 | size 20 | symbol _ZN4Aska13MemoryManager10InitializeEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13MemoryManager10InitializeEv(long param_1)

{
  *(undefined8 *)(param_1 + 0x28) = 0;
  *(undefined8 *)(param_1 + 0x30) = 0;
  *(undefined8 *)(param_1 + 0x20) = 0;
  *(long *)(param_1 + 0x40) = param_1;
  *(long *)(param_1 + 0x48) = param_1;
  *(long *)(param_1 + 0x50) = param_1;
  *(undefined8 *)(param_1 + 0x58) = 0;
  return;
}

// ==== Aska::MemoryManager::MemoryManager(unsigned long)
// vaddr 0x1f4ad08 | ghidra 0x204ad08 | size 80 | symbol _ZN4Aska13MemoryManagerC1Em | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13MemoryManagerC2Em(long *param_1,undefined8 param_2)

{
  *(undefined1 *)(param_1 + 1) = 0;
  *param_1 = (long)(PTR__ZTVN4Aska13MemoryManagerE_02cb9280 + 0x10);
  Aska::FastCriticalSection::FastCriticalSection()(param_1 + 0xc);
  param_1[5] = 0;
  param_1[6] = 0;
  param_1[4] = 0;
  param_1[8] = (long)param_1;
  param_1[9] = (long)param_1;
  param_1[10] = (long)param_1;
  param_1[0xb] = 0;
  (*(code *)PTR__ZN4Aska13MemoryManager8InitHeapEm_02c9cc58)(param_1,param_2);
  return;
}

// ==== Aska::MemoryManager::InitHeap(unsigned long)
// vaddr 0x1f4ad58 | ghidra 0x204ad58 | size 348 | symbol _ZN4Aska13MemoryManager8InitHeapEm | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska13MemoryManager8InitHeapEm(long param_1,long param_2)

{
  uint uVar1;
  undefined1 auVar2 [16];
  undefined8 *puVar3;
  undefined8 uVar4;
  long lVar5;
  ulong uVar6;
  long lVar7;
  ulong uVar8;
  long *plVar9;
  int iVar10;
  ulong uVar11;
  
  lVar5 = *(long *)(param_1 + 0x20);
  if (lVar5 != 0) {
    if (*(char *)(param_1 + 0x38) != '\0') {
      Aska::MemoryManager::LocalFree(Aska::_MemoryBlock*)(*(undefined8 *)(lVar5 + -0x18),lVar5 + -0x40);
    }
    *(undefined8 *)(param_1 + 0x20) = 0;
    *(undefined8 *)(param_1 + 0x10) = 0;
    *(undefined1 *)(param_1 + 0x38) = 0;
  }
  puVar3 = (undefined8 *)operator new[](unsigned long, std::nothrow_t const&)(param_2 + 0x10,PTR__ZSt7nothrow_02cb9a80);
  *(undefined8 **)(param_1 + 0x20) = puVar3;
  uVar4 = 0;
  if (puVar3 != (undefined8 *)0x0) {
    auVar2._8_8_ = 0;
    auVar2._0_8_ = param_2 + 0xffbeU;
    uVar11 = (param_2 + 0xffbeU) / 0x10028 & 0xffffffff;
    uVar6 = param_2 + 0x10 + uVar11 * -0x28 & 0xfffffffffffffff0;
    uVar4 = 1;
    lVar5 = (long)puVar3 + uVar6;
    *(undefined1 *)(param_1 + 0x38) = 1;
    iVar10 = SUB164(auVar2 * ZEXT816(0xffd8063f062709e7),10);
    *(int *)(param_1 + 0x18) = iVar10;
    *(long *)(param_1 + 0x10) = lVar5;
    uVar8 = uVar6;
    if (uVar6 + uVar11 * -0x10000 + 0x10000 < 0x80) {
      uVar1 = iVar10 - 1;
      *(uint *)(param_1 + 0x18) = uVar1;
      if (uVar1 == 0) {
        Aska::MemoryManager::LocalFree(Aska::_MemoryBlock*)(1,puVar3 + -8);
        *(undefined8 *)(param_1 + 0x20) = 0;
        *(undefined1 *)(param_1 + 0x38) = 0;
        return 0;
      }
      uVar8 = (ulong)uVar1 << 0x10;
    }
    *(ulong *)(param_1 + 0x28) = uVar8;
    *(undefined1 *)((long)puVar3 + uVar6) = 1;
    lVar7 = uVar8 - 0x40;
    *(undefined8 *)(lVar5 + 4) = 0;
    *puVar3 = 0x40;
    *(undefined2 *)(puVar3 + 6) = 0x100;
    puVar3[7] = 0;
    plVar9 = puVar3 + 8;
    *plVar9 = lVar7;
    *(undefined2 *)(puVar3 + 0xe) = 0;
    puVar3[0xb] = puVar3;
    puVar3[0xc] = puVar3;
    puVar3[9] = puVar3;
    puVar3[10] = puVar3;
    puVar3[3] = plVar9;
    puVar3[4] = plVar9;
    puVar3[1] = plVar9;
    puVar3[2] = plVar9;
    *(undefined8 *)(lVar5 + 0x10) = 0;
    *(long *)(lVar5 + 0x18) = lVar7;
    *(long *)(lVar5 + 0x20) = lVar7;
    if (1 < *(uint *)(param_1 + 0x18)) {
      lVar7 = (ulong)*(uint *)(param_1 + 0x18) - 1;
      lVar5 = 0x28;
      do {
        lVar7 = lVar7 + -1;
        *(undefined1 *)(*(long *)(param_1 + 0x10) + lVar5) = 0;
        lVar5 = lVar5 + 0x28;
      } while (lVar7 != 0);
      uVar4 = 1;
    }
  }
  return uVar4;
}

// ==== Aska::MemoryManager::~MemoryManager()
// vaddr 0x1f4aeb4 | ghidra 0x204aeb4 | size 264 | symbol _ZN4Aska13MemoryManagerD2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13MemoryManagerD1Ev(long *param_1)

{
  long lVar1;
  long *plVar2;
  long *plVar3;
  
  *param_1 = (long)(PTR__ZTVN4Aska13MemoryManagerE_02cb9280 + 0x10);
  if (*(long **)PTR__ZN4Aska6Global16m_pMemoryManagerE_02cbd3f0 == param_1) {
    *(undefined8 *)PTR__ZN4Aska6Global16m_pMemoryManagerE_02cbd3f0 = 0;
  }
  plVar2 = (long *)param_1[9];
  do {
    plVar3 = (long *)plVar2[9];
    if ((plVar2 != (long *)0x0) && ((long *)plVar2[0xb] == param_1)) {
      (**(code **)(*plVar2 + 0xd0))();
    }
    plVar2 = plVar3;
  } while (plVar3 != param_1);
  if (param_1 == (long *)0x0) goto code_r0x0204af84;
  if ((long *)param_1[8] == param_1) {
    plVar3 = (long *)param_1[9];
    plVar2 = plVar3;
    do {
      if ((long *)plVar2[0xb] != param_1) goto code_r0x0204af4c;
      plVar2 = (long *)plVar2[9];
    } while (plVar2 != param_1);
    goto code_r0x0204af84;
  }
code_r0x0204af6c:
  param_1[8] = (long)param_1;
  *(long *)(param_1[9] + 0x50) = param_1[10];
  *(long *)(param_1[10] + 0x48) = param_1[9];
  param_1[9] = (long)param_1;
  param_1[10] = (long)param_1;
code_r0x0204af84:
  lVar1 = param_1[4];
  if (lVar1 != 0) {
    if ((char)param_1[7] != '\0') {
      Aska::MemoryManager::LocalFree(Aska::_MemoryBlock*)(*(undefined8 *)(lVar1 + -0x18),lVar1 + -0x40);
    }
    param_1[4] = 0;
    param_1[2] = 0;
    *(undefined1 *)(param_1 + 7) = 0;
  }
  (*(code *)PTR__ZN4Aska19FastCriticalSectionD2Ev_02ca21e0)(param_1 + 0xc);
  return;
code_r0x0204af4c:
  do {
    plVar3[8] = (long)plVar2;
    if ((long *)plVar3[0xb] == param_1) {
      plVar3[0xb] = (long)plVar2;
    }
    plVar3 = (long *)plVar3[9];
  } while (plVar3 != param_1);
  goto code_r0x0204af6c;
}

// ==== Aska::MemoryManager::ClearHeap()
// vaddr 0x1f4afbc | ghidra 0x204afbc | size 4 | symbol _ZN4Aska13MemoryManager9ClearHeapEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13MemoryManager9ClearHeapEv(void)

{
  return;
}

// ==== Aska::MemoryManager::Remove(Aska::MemoryManager*)
// vaddr 0x1f4afc0 | ghidra 0x204afc0 | size 148 | symbol _ZN4Aska13MemoryManager6RemoveEPS0_ | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska13MemoryManager6RemoveEPS0_(long param_1,long param_2)

{
  long lVar1;
  long lVar2;
  
  if (param_2 == 0) {
    return 0;
  }
  if (*(long *)(param_2 + 0x40) != *(long *)(param_1 + 0x40)) {
    return 0;
  }
  if (*(long *)(param_2 + 0x40) == param_2) {
    lVar1 = *(long *)(param_2 + 0x48);
    lVar2 = lVar1;
    while (*(long *)(lVar2 + 0x58) == param_2) {
      lVar2 = *(long *)(lVar2 + 0x48);
      if (lVar2 == param_2) {
        return 0;
      }
    }
    do {
      *(long *)(lVar1 + 0x40) = lVar2;
      if (*(long *)(lVar1 + 0x58) == param_2) {
        *(long *)(lVar1 + 0x58) = lVar2;
      }
      lVar1 = *(long *)(lVar1 + 0x48);
    } while (lVar1 != param_2);
  }
  *(long *)(param_2 + 0x40) = param_2;
  *(undefined8 *)(*(long *)(param_2 + 0x48) + 0x50) = *(undefined8 *)(param_2 + 0x50);
  *(undefined8 *)(*(long *)(param_2 + 0x50) + 0x48) = *(undefined8 *)(param_2 + 0x48);
  *(long *)(param_2 + 0x48) = param_2;
  *(long *)(param_2 + 0x50) = param_2;
  return 1;
}

// ==== Aska::MemoryManager::DeleteHeap()
// vaddr 0x1f4b054 | ghidra 0x204b054 | size 56 | symbol _ZN4Aska13MemoryManager10DeleteHeapEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13MemoryManager10DeleteHeapEv(long param_1)

{
  long lVar1;
  
  lVar1 = *(long *)(param_1 + 0x20);
  if (lVar1 != 0) {
    if (*(char *)(param_1 + 0x38) != '\0') {
      Aska::MemoryManager::LocalFree(Aska::_MemoryBlock*)(*(undefined8 *)(lVar1 + -0x18),lVar1 + -0x40);
    }
    *(undefined8 *)(param_1 + 0x20) = 0;
    *(undefined8 *)(param_1 + 0x10) = 0;
    *(undefined1 *)(param_1 + 0x38) = 0;
  }
  return;
}

// ==== Aska::MemoryManager::~MemoryManager()
// vaddr 0x1f4b08c | ghidra 0x204b08c | size 40 | symbol _ZN4Aska13MemoryManagerD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13MemoryManagerD0Ev(long param_1)

{
  Aska::MemoryManager::~MemoryManager()();
  if (param_1 != 0) {
    (*(code *)PTR__ZN4Aska13MemoryManager9LocalFreeEPNS_12_MemoryBlockE_02c924f8)
              (*(undefined8 *)(param_1 + -0x18),param_1 + -0x40);
    return;
  }
  return;
}

// ==== Aska::MemoryManager::InitSrbk(unsigned long)
// vaddr 0x1f4b0b4 | ghidra 0x204b0b4 | size 232 | symbol _ZN4Aska13MemoryManager8InitSrbkEm | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZN4Aska13MemoryManager8InitSrbkEm(long param_1,long param_2)

{
  undefined1 *puVar1;
  uint uVar2;
  undefined1 auVar3 [16];
  int iVar4;
  long lVar5;
  ulong uVar6;
  long lVar7;
  ulong uVar8;
  undefined8 *puVar9;
  long *plVar10;
  
  auVar3._8_8_ = 0;
  auVar3._0_8_ = param_2 + 0xffaeU;
  uVar8 = (param_2 + 0xffaeU) / 0x10028 & 0xffffffff;
  uVar6 = param_2 + uVar8 * -0x28 & 0xfffffffffffffff0;
  puVar1 = (undefined1 *)(*(long *)(param_1 + 0x20) + uVar6);
  iVar4 = SUB164(auVar3 * ZEXT816(0xffd8063f062709e7),10);
  *(int *)(param_1 + 0x18) = iVar4;
  *(undefined1 **)(param_1 + 0x10) = puVar1;
  if (uVar6 + uVar8 * -0x10000 + 0x10000 < 0x80) {
    uVar2 = iVar4 - 1;
    *(uint *)(param_1 + 0x18) = uVar2;
    if (uVar2 == 0) {
      return 0;
    }
    uVar6 = (ulong)uVar2 << 0x10;
  }
  *(ulong *)(param_1 + 0x28) = uVar6;
  *(undefined8 *)(puVar1 + 4) = 0;
  *puVar1 = 1;
  puVar9 = *(undefined8 **)(param_1 + 0x20);
  lVar7 = uVar6 - 0x40;
  *puVar9 = 0x40;
  *(undefined2 *)(puVar9 + 6) = 0x100;
  puVar9[7] = 0;
  plVar10 = puVar9 + 8;
  *plVar10 = lVar7;
  *(undefined2 *)(puVar9 + 0xe) = 0;
  puVar9[0xb] = puVar9;
  puVar9[0xc] = puVar9;
  puVar9[9] = puVar9;
  puVar9[10] = puVar9;
  puVar9[3] = plVar10;
  puVar9[4] = plVar10;
  puVar9[1] = plVar10;
  puVar9[2] = plVar10;
  *(undefined8 *)(puVar1 + 0x10) = 0;
  *(long *)(puVar1 + 0x18) = lVar7;
  *(long *)(puVar1 + 0x20) = lVar7;
  if (1 < *(uint *)(param_1 + 0x18)) {
    lVar5 = (ulong)*(uint *)(param_1 + 0x18) - 1;
    lVar7 = 0x28;
    do {
      lVar5 = lVar5 + -1;
      *(undefined1 *)(*(long *)(param_1 + 0x10) + lVar7) = 0;
      lVar7 = lVar7 + 0x28;
    } while (lVar5 != 0);
  }
  return 1;
}

// ==== Aska::MemoryManager::InitHeap(unsigned char*, unsigned long, unsigned char*, unsigned long)
// vaddr 0x1f4b19c | ghidra 0x204b19c | size 332 | symbol _ZN4Aska13MemoryManager8InitHeapEPhmS1_m | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska13MemoryManager8InitHeapEPhmS1_m
          (long param_1,long param_2,long param_3,undefined1 *param_4,ulong param_5)

{
  undefined8 uVar1;
  int iVar2;
  long lVar3;
  ulong uVar4;
  undefined8 *puVar5;
  long lVar6;
  long *plVar7;
  
  lVar3 = *(long *)(param_1 + 0x20);
  if (lVar3 != 0) {
    if (*(char *)(param_1 + 0x38) != '\0') {
      Aska::MemoryManager::LocalFree(Aska::_MemoryBlock*)(*(undefined8 *)(lVar3 + -0x18),lVar3 + -0x40);
    }
    *(undefined8 *)(param_1 + 0x20) = 0;
    *(undefined8 *)(param_1 + 0x10) = 0;
    *(undefined1 *)(param_1 + 0x38) = 0;
  }
  uVar1 = 0;
  if ((param_2 != 0) && (param_4 != (undefined1 *)0x0)) {
    uVar4 = (param_3 + 0xffffU >> 0x10) * 0x28;
    if (uVar4 < param_5 || uVar4 - param_5 == 0) {
      *(long *)(param_1 + 0x20) = param_2;
      *(undefined1 *)(param_1 + 0x38) = 0;
      iVar2 = (int)(param_3 + 0xffaeU >> 0x10);
      *(int *)(param_1 + 0x18) = iVar2;
      *(undefined1 **)(param_1 + 0x10) = param_4;
      if (((param_3 + 0x10000) - (param_3 + 0xffaeU & 0xffffffff0000) < 0x80) &&
         (iVar2 = iVar2 + -1, *(int *)(param_1 + 0x18) = iVar2, iVar2 == 0)) {
        uVar1 = 0;
        *(undefined8 *)(param_1 + 0x20) = 0;
      }
      else {
        uVar1 = 1;
        *(long *)(param_1 + 0x28) = param_3;
        *(undefined8 *)(param_4 + 4) = 0;
        *param_4 = 1;
        puVar5 = *(undefined8 **)(param_1 + 0x20);
        param_3 = param_3 + -0x40;
        *puVar5 = 0x40;
        *(undefined2 *)(puVar5 + 6) = 0x100;
        puVar5[7] = 0;
        plVar7 = puVar5 + 8;
        *plVar7 = param_3;
        *(undefined2 *)(puVar5 + 0xe) = 0;
        puVar5[0xb] = puVar5;
        puVar5[0xc] = puVar5;
        puVar5[9] = puVar5;
        puVar5[10] = puVar5;
        puVar5[3] = plVar7;
        puVar5[4] = plVar7;
        puVar5[1] = plVar7;
        puVar5[2] = plVar7;
        *(undefined8 *)(param_4 + 0x10) = 0;
        *(long *)(param_4 + 0x18) = param_3;
        *(long *)(param_4 + 0x20) = param_3;
        if (1 < *(uint *)(param_1 + 0x18)) {
          lVar6 = (ulong)*(uint *)(param_1 + 0x18) - 1;
          lVar3 = 0x28;
          do {
            lVar6 = lVar6 + -1;
            *(undefined1 *)(*(long *)(param_1 + 0x10) + lVar3) = 0;
            lVar3 = lVar3 + 0x28;
          } while (lVar6 != 0);
          uVar1 = 1;
        }
      }
    }
    else {
      uVar1 = 0;
    }
  }
  return uVar1;
}

// ==== Aska::MemoryManager::InitSrbk(unsigned long, unsigned char*)
// vaddr 0x1f4b2e8 | ghidra 0x204b2e8 | size 184 | symbol _ZN4Aska13MemoryManager8InitSrbkEmPh | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZN4Aska13MemoryManager8InitSrbkEmPh(long param_1,long param_2,undefined1 *param_3)

{
  int iVar1;
  long lVar2;
  undefined8 *puVar3;
  long lVar4;
  long *plVar5;
  
  iVar1 = (int)(param_2 + 0xffaeU >> 0x10);
  *(int *)(param_1 + 0x18) = iVar1;
  *(undefined1 **)(param_1 + 0x10) = param_3;
  if (((param_2 + 0x10000) - (param_2 + 0xffaeU & 0xffffffff0000) < 0x80) &&
     (iVar1 = iVar1 + -1, *(int *)(param_1 + 0x18) = iVar1, iVar1 == 0)) {
    return 0;
  }
  *(long *)(param_1 + 0x28) = param_2;
  *(undefined8 *)(param_3 + 4) = 0;
  *param_3 = 1;
  puVar3 = *(undefined8 **)(param_1 + 0x20);
  param_2 = param_2 + -0x40;
  *puVar3 = 0x40;
  *(undefined2 *)(puVar3 + 6) = 0x100;
  puVar3[7] = 0;
  plVar5 = puVar3 + 8;
  *plVar5 = param_2;
  *(undefined2 *)(puVar3 + 0xe) = 0;
  puVar3[0xb] = puVar3;
  puVar3[0xc] = puVar3;
  puVar3[9] = puVar3;
  puVar3[10] = puVar3;
  puVar3[3] = plVar5;
  puVar3[4] = plVar5;
  puVar3[1] = plVar5;
  puVar3[2] = plVar5;
  *(undefined8 *)(param_3 + 0x10) = 0;
  *(long *)(param_3 + 0x18) = param_2;
  *(long *)(param_3 + 0x20) = param_2;
  if (1 < *(uint *)(param_1 + 0x18)) {
    lVar2 = (ulong)*(uint *)(param_1 + 0x18) - 1;
    lVar4 = 0x28;
    do {
      lVar2 = lVar2 + -1;
      *(undefined1 *)(*(long *)(param_1 + 0x10) + lVar4) = 0;
      lVar4 = lVar4 + 0x28;
    } while (lVar2 != 0);
  }
  return 1;
}

// ==== Aska::MemoryManager::Malloc(unsigned long)
// vaddr 0x1f4b3a0 | ghidra 0x204b3a0 | size 1248 | symbol _ZN4Aska13MemoryManager6MallocEm | lib libSOA-3.7.0.so | 2026-10-04
ulong * _ZN4Aska13MemoryManager6MallocEm(ulong param_1,long param_2)

{
  int *piVar1;
  uint uVar2;
  char cVar3;
  bool bVar4;
  ulong *puVar5;
  undefined8 *puVar6;
  int iVar7;
  int *piVar8;
  ulong *puVar9;
  long lVar10;
  ulong *puVar11;
  long lVar12;
  ulong uVar13;
  long *plVar14;
  long lVar15;
  long *plVar16;
  long lVar17;
  ulong uVar18;
  char *pcVar19;
  ulong *puVar20;
  ulong uVar21;
  ulong uVar22;
  ulong uStack_98;
  long lStack_90;
  undefined8 uStack_88;
  undefined4 uStack_80;
  int *piStack_78;
  ulong *puStack_70;
  int iStack_64;
  
  if (param_2 == 0) {
    return (ulong *)0x0;
  }
  if (*(char *)(param_1 + 8) == '\x01') {
    puVar5 = (ulong *)(*(code *)PTR__ZN4Aska13MemoryManager10MallocHighEm_02c990a8)(param_1,param_2)
    ;
    return puVar5;
  }
  uVar22 = param_2 + 0x4fU & 0xfffffffffffffff0;
  iStack_64 = 0;
  uVar21 = param_1;
  do {
    piVar8 = (int *)(uVar21 + 0x98);
    iVar7 = 0;
code_r0x0204b424:
    if (*piVar8 == -1) {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar8,0x10);
      if (bVar4) {
        *piVar8 = 0;
        cVar3 = ExclusiveMonitorsStatus();
      }
      if (cVar3 == '\0') goto code_r0x0204b4ec;
      goto code_r0x0204b424;
    }
    ClearExclusiveLocal();
    bVar4 = iVar7 < 0x1ff;
    iVar7 = iVar7 + 1;
    if (bVar4) goto code_r0x0204b424;
    piVar1 = (int *)(uVar21 + 0x9c);
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
          uVar13 = Aska::Semaphore::IsReady() const(uVar21 + 0xd8);
          if ((uVar13 & 1) == 0) {
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
            Aska::Semaphore::Wait() const(uVar21 + 0xd8);
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
            if (cVar3 == '\0') goto code_r0x0204b4dc;
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
code_r0x0204b4dc:
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
code_r0x0204b4ec:
    DataMemoryBarrier(2,3);
    lVar10 = *(long *)(uVar21 + 0x10);
    lVar12 = *(long *)(uVar21 + 0x20);
    uVar13 = 0;
    do {
      puVar5 = (ulong *)(lVar10 + uVar13 * 0x28 + 0x20);
      if (uVar22 <= *puVar5) {
        puVar9 = (ulong *)(lVar12 + uVar13 * 0x10000);
        for (puVar20 = (ulong *)puVar9[3]; puVar20 != puVar9; puVar20 = (ulong *)puVar20[3]) {
          uVar18 = *puVar20 - uVar22;
          if (uVar22 <= *puVar20) {
            if (uVar18 < 0x50) {
              *(ulong *)(puVar20[4] + 0x18) = puVar20[3];
              *(ulong *)(puVar20[3] + 0x20) = puVar20[4];
              uVar22 = *puVar20;
            }
            else {
              puVar11 = (ulong *)((long)puVar20 + uVar22);
              *puVar11 = uVar18;
              *(undefined1 *)((long)puVar11 + 0x31) = 0;
              puVar11[4] = puVar20[4];
              puVar11[3] = puVar20[3];
              *(ulong **)(puVar20[4] + 0x18) = puVar11;
              *(ulong **)(puVar20[3] + 0x20) = puVar11;
              *(ulong **)(puVar20[1] + 0x10) = puVar11;
              puVar11[1] = puVar20[1];
              puVar20[1] = (ulong)puVar11;
              puVar11[2] = (ulong)puVar20;
              *puVar20 = uVar22;
            }
            puVar20[5] = uVar21;
            puVar20[7] = 0;
            *(undefined2 *)(puVar20 + 6) = 0x100;
            lVar15 = lVar10 + uVar13 * 0x28;
            plVar16 = (long *)(lVar15 + 0x10);
            lVar17 = *plVar16;
            *plVar16 = lVar17 + uVar22;
            plVar14 = (long *)(lVar15 + 0x18);
            *plVar14 = *plVar14 - uVar22;
            if (lVar17 != 0) goto code_r0x0204b7b4;
            uVar22 = (long)puVar20 + (*puVar20 - (long)puVar9);
            if (*(char *)(puVar9[2] + 0x31) != '\x01') {
              uVar22 = uVar22 + 0x40;
            }
            uVar18 = uVar22 + 0xffff >> 0x10;
            if (uVar22 < 0xffc1) {
              uVar18 = 1;
            }
            uVar22 = uVar18 + uVar13;
            if ((*(uint *)(uVar21 + 0x18) <= uVar22) ||
               (pcVar19 = (char *)(lVar10 + uVar22 * 0x28), *pcVar19 != '\0'))
            goto code_r0x0204b7b4;
            *pcVar19 = '\x01';
            lVar17 = lVar10 + uVar13 * 0x28;
            lVar15 = lVar10 + uVar22 * 0x28;
            puVar6 = (undefined8 *)(lVar12 + uVar22 * 0x10000);
            *(undefined4 *)(lVar15 + 4) = *(undefined4 *)(lVar17 + 4);
            *(int *)(lVar10 + (ulong)*(uint *)(lVar17 + 4) * 0x28 + 8) = (int)uVar22;
            *(int *)(lVar17 + 4) = (int)uVar22;
            *(int *)(lVar15 + 8) = (int)uVar13;
            lVar12 = *plVar16;
            *(undefined8 *)(lVar15 + 0x10) = 0;
            lVar12 = (uVar18 * 0x10000 - lVar12) + -0x40;
            lVar17 = (*plVar14 - lVar12) + -0x40;
            *(long *)(lVar15 + 0x18) = lVar17;
            *(long *)(lVar15 + 0x20) = lVar17;
            *(undefined2 *)(puVar6 + 6) = 0x100;
            puVar6[7] = 0;
            plVar16 = puVar6 + 8;
            *plVar16 = lVar17;
            *(undefined2 *)(puVar6 + 0xe) = 0;
            puVar6[0xb] = puVar6;
            puVar6[0xc] = puVar6;
            puVar6[9] = puVar6;
            puVar6[10] = puVar6;
            puVar6[3] = plVar16;
            puVar6[4] = plVar16;
            *puVar6 = 0x40;
            puVar6[1] = plVar16;
            puVar6[2] = plVar16;
            *plVar14 = lVar12;
            puVar11 = (ulong *)puVar9[3];
            if (puVar11 == puVar9) goto code_r0x0204b7b4;
            goto code_r0x0204b78c;
          }
        }
      }
      uVar2 = *(uint *)(lVar10 + uVar13 * 0x28 + 4);
      uVar13 = (ulong)uVar2;
    } while (uVar2 != 0);
    DataMemoryBarrier(2,3);
    *(undefined4 *)(uVar21 + 0x98) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar8 = (int *)(uVar21 + 0x9c);
    if (0x14 < *piVar8) {
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar8,0x10);
        if (bVar4) {
          *piVar8 = *piVar8 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      uVar13 = Aska::Semaphore::IsReady() const(uVar21 + 0xd8);
      if ((uVar13 & 1) != 0) {
        Aska::Semaphore::Signal() const(uVar21 + 0xd8);
      }
    }
    puVar5 = (ulong *)(uVar21 + 0x48);
    uVar21 = *puVar5;
    if (*puVar5 == param_1) {
      if (0 < iStack_64) {
        return (ulong *)0x0;
      }
      puVar6 = *(undefined8 **)(param_1 + 0x30);
      if (puVar6 == (undefined8 *)0x0) {
        return (ulong *)0x0;
      }
      iStack_64 = iStack_64 + 1;
      uStack_88 = 4;
      uStack_80 = 0;
      puStack_70 = (ulong *)0x0;
      uStack_98 = param_1;
      lStack_90 = param_2;
      piStack_78 = &iStack_64;
      (**(code **)*puVar6)(puVar6,&uStack_98);
      uVar21 = param_1;
      if (puStack_70 != (ulong *)0x0) {
        return puStack_70;
      }
    }
  } while( true );
  while (puVar11 = (ulong *)puVar11[3], puVar11 != puVar9) {
code_r0x0204b78c:
    if (puVar6 < (undefined8 *)(*puVar11 + (long)puVar11)) {
      *puVar11 = (long)puVar6 - (long)puVar11;
      break;
    }
  }
code_r0x0204b7b4:
  puVar9 = (ulong *)(*(long *)(uVar21 + 0x20) +
                    ((lVar10 + uVar13 * 0x28) - *(long *)(uVar21 + 0x10) >> 3) * -0x3333333333330000
                    );
  puVar11 = (ulong *)puVar9[3];
  if (puVar9 < puVar11) {
    uVar13 = 0;
    do {
      uVar22 = uVar13;
      if ((*(char *)((long)puVar11 + 0x31) != '\x01') && (uVar22 = *puVar11, *puVar11 <= uVar13)) {
        uVar22 = uVar13;
      }
      puVar11 = (ulong *)puVar11[3];
      uVar13 = uVar22;
    } while (puVar9 < puVar11);
  }
  else {
    uVar22 = 0;
  }
  *puVar5 = uVar22;
  DataMemoryBarrier(2,3);
  *(undefined4 *)(uVar21 + 0x98) = 0xffffffff;
  DataMemoryBarrier(2,3);
  piVar8 = (int *)(uVar21 + 0x9c);
  if (0x14 < *piVar8) {
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar8,0x10);
      if (bVar4) {
        *piVar8 = *piVar8 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
    uVar22 = Aska::Semaphore::IsReady() const(uVar21 + 0xd8);
    if ((uVar22 & 1) != 0) {
      Aska::Semaphore::Signal() const(uVar21 + 0xd8);
    }
  }
  return puVar20 + 8;
}

// ==== Aska::MemoryManager::MallocHigh(unsigned long)
// vaddr 0x1f4b880 | ghidra 0x204b880 | size 1184 | symbol _ZN4Aska13MemoryManager10MallocHighEm | lib libSOA-3.7.0.so | 2026-10-04
ulong * _ZN4Aska13MemoryManager10MallocHighEm(ulong param_1,long param_2)

{
  int *piVar1;
  long lVar2;
  uint uVar3;
  uint uVar4;
  char cVar5;
  bool bVar6;
  undefined8 *puVar7;
  int iVar8;
  undefined1 *puVar9;
  int *piVar10;
  long lVar11;
  ulong uVar12;
  ulong uVar13;
  ulong *puVar14;
  long lVar15;
  ulong uVar16;
  ulong *puVar17;
  long *plVar18;
  long lVar19;
  ulong *puVar20;
  ulong uVar21;
  ulong uVar22;
  ulong uStack_98;
  long lStack_90;
  undefined8 uStack_88;
  undefined4 uStack_80;
  int *piStack_78;
  ulong *puStack_70;
  int iStack_64;
  
  if (param_2 == 0) {
    return (ulong *)0x0;
  }
  uVar22 = param_2 + 0x4fU & 0xfffffffffffffff0;
  iStack_64 = 0;
  uVar21 = param_1;
code_r0x0204b978:
  piVar10 = (int *)(uVar21 + 0x98);
  iVar8 = 0;
code_r0x0204b980:
  do {
    if (*piVar10 == -1) goto code_r0x0204b98c;
    ClearExclusiveLocal();
    bVar6 = iVar8 < 0x1ff;
    iVar8 = iVar8 + 1;
  } while (bVar6);
  piVar1 = (int *)(uVar21 + 0x9c);
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
      uVar16 = Aska::Semaphore::IsReady() const();
      if ((uVar16 & 1) != 0) goto code_r0x0204b924;
      do {
        do {
          cVar5 = '\x01';
          bVar6 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar6) {
            *piVar1 = *piVar1 + -1;
            cVar5 = ExclusiveMonitorsStatus();
          }
        } while (cVar5 != '\0');
        Aska::Thread::Sleep(unsigned int)(1);
        while( true ) {
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
            if (cVar5 == '\0') goto code_r0x0204b95c;
          }
          ClearExclusiveLocal();
          uVar16 = Aska::Semaphore::IsReady() const(uVar21 + 0xd8);
          if ((uVar16 & 1) == 0) break;
code_r0x0204b924:
          Aska::Semaphore::Wait() const(uVar21 + 0xd8);
        }
      } while( true );
    }
    cVar5 = '\x01';
    bVar6 = (bool)ExclusiveMonitorPass(piVar10,0x10);
    if (bVar6) {
      *piVar10 = 0;
      cVar5 = ExclusiveMonitorsStatus();
    }
  } while (cVar5 != '\0');
code_r0x0204b95c:
  do {
    cVar5 = '\x01';
    bVar6 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar6) {
      *piVar1 = *piVar1 + -1;
      cVar5 = ExclusiveMonitorsStatus();
    }
  } while (cVar5 != '\0');
  DataMemoryBarrier(2,3);
  goto code_r0x0204b9d8;
code_r0x0204b98c:
  cVar5 = '\x01';
  bVar6 = (bool)ExclusiveMonitorPass(piVar10,0x10);
  if (bVar6) {
    *piVar10 = 0;
    cVar5 = ExclusiveMonitorsStatus();
  }
  if (cVar5 == '\0') goto code_r0x0204b9d4;
  goto code_r0x0204b980;
code_r0x0204b9d4:
  DataMemoryBarrier(2,3);
code_r0x0204b9d8:
  lVar11 = *(long *)(uVar21 + 0x10);
  lVar15 = *(long *)(uVar21 + 0x20);
  uVar3 = *(uint *)(lVar11 + 8);
  uVar4 = uVar3;
  do {
    uVar16 = (ulong)uVar4;
    puVar9 = (undefined1 *)(lVar11 + uVar16 * 0x28);
    puVar17 = (ulong *)(puVar9 + 0x20);
    if (uVar22 <= *puVar17) {
      uVar12 = uVar16;
      if (*(long *)(lVar11 + uVar16 * 0x28 + 0x10) == 0) {
        puVar20 = (ulong *)(lVar11 + uVar16 * 0x28 + 0x18);
        lVar19 = (-0x40 - uVar22) + *puVar20;
        lVar2 = lVar19 + 0xffff;
        if (-1 < lVar19) {
          lVar2 = lVar19;
        }
        uVar12 = (lVar2 >> 0x10) + uVar16;
        if (0xffff < lVar19) {
          lVar19 = lVar11 + uVar16 * 0x28;
          puVar9 = (undefined1 *)(lVar11 + uVar12 * 0x28);
          puVar7 = (undefined8 *)(lVar15 + uVar16 * 0x10000);
          *(undefined4 *)(puVar9 + 4) = *(undefined4 *)(lVar19 + 4);
          uVar13 = (lVar2 >> 0x10) * 0x10000 - 0x40;
          *(int *)(lVar11 + (ulong)*(uint *)(lVar19 + 4) * 0x28 + 8) = (int)uVar12;
          *(int *)(lVar19 + 4) = (int)uVar12;
          *(uint *)(puVar9 + 8) = uVar4;
          uVar16 = *puVar20;
          *puVar20 = uVar13;
          *puVar17 = uVar13;
          *(undefined2 *)(puVar7 + 6) = 0x100;
          puVar7[7] = 0;
          puVar17 = puVar7 + 8;
          *puVar17 = uVar13;
          *(undefined2 *)(puVar7 + 0xe) = 0;
          puVar7[0xb] = puVar7;
          puVar7[0xc] = puVar7;
          puVar7[9] = puVar7;
          puVar7[10] = puVar7;
          puVar7[3] = puVar17;
          puVar7[4] = puVar17;
          *puVar7 = 0x40;
          puVar7[1] = puVar17;
          puVar7[2] = puVar17;
          *puVar9 = 1;
          *(undefined8 *)(puVar9 + 0x10) = 0;
          puVar7 = (undefined8 *)(lVar15 + uVar12 * 0x10000);
          lVar19 = (uVar16 - *puVar20) + -0x40;
          *(long *)(puVar9 + 0x18) = lVar19;
          *(long *)(puVar9 + 0x20) = lVar19;
          *(undefined2 *)(puVar7 + 6) = 0x100;
          puVar7[7] = 0;
          plVar18 = puVar7 + 8;
          *plVar18 = lVar19;
          *(undefined2 *)(puVar7 + 0xe) = 0;
          puVar7[0xb] = puVar7;
          puVar7[0xc] = puVar7;
          puVar7[3] = plVar18;
          puVar7[4] = plVar18;
          *puVar7 = 0x40;
          puVar7[1] = plVar18;
          puVar7[2] = plVar18;
          puVar7[9] = puVar7;
          puVar7[10] = puVar7;
        }
      }
      puVar17 = (ulong *)(lVar15 + uVar12 * 0x10000);
      for (puVar20 = (ulong *)puVar17[4]; puVar20 != puVar17; puVar20 = (ulong *)puVar20[4]) {
        uVar16 = *puVar20;
        if (uVar22 <= uVar16) {
          if (uVar16 - uVar22 < 0x50) {
            *(ulong *)(puVar20[4] + 0x18) = puVar20[3];
            *(ulong *)(puVar20[3] + 0x20) = puVar20[4];
            puVar17 = puVar20;
            uVar22 = uVar16;
          }
          else {
            uVar12 = puVar20[1];
            uVar13 = puVar20[3];
            puVar17 = (ulong *)((long)puVar20 + (uVar16 - uVar22));
            *(undefined1 *)((long)puVar17 + 0x31) = 0;
            puVar17[1] = uVar12;
            puVar17[3] = uVar13;
            *(ulong **)(uVar12 + 0x10) = puVar17;
            *puVar20 = (long)puVar17 - (long)puVar20;
            puVar20[1] = (ulong)puVar17;
            puVar17[2] = (ulong)puVar20;
            puVar17[4] = (ulong)puVar20;
          }
          *puVar17 = uVar22;
          puVar17[5] = uVar21;
          puVar17[7] = 0;
          *(undefined2 *)(puVar17 + 6) = 0x101;
          *(ulong *)(puVar9 + 0x10) = *(long *)(puVar9 + 0x10) + uVar22;
          *(ulong *)(puVar9 + 0x18) = *(long *)(puVar9 + 0x18) - uVar22;
          puVar20 = (ulong *)(*(long *)(uVar21 + 0x20) +
                             ((ulong)((long)puVar9 - *(long *)(uVar21 + 0x10)) >> 3) *
                             -0x3333333333330000);
          puVar14 = (ulong *)puVar20[3];
          uVar22 = 0;
          if (puVar20 < puVar14) {
            uVar16 = 0;
            do {
              uVar22 = uVar16;
              if ((*(char *)((long)puVar14 + 0x31) != '\x01') &&
                 (uVar22 = *puVar14, *puVar14 <= uVar16)) {
                uVar22 = uVar16;
              }
              puVar14 = (ulong *)puVar14[3];
              uVar16 = uVar22;
            } while (puVar20 < puVar14);
          }
          *(ulong *)(puVar9 + 0x20) = uVar22;
          DataMemoryBarrier(2,3);
          *(undefined4 *)(uVar21 + 0x98) = 0xffffffff;
          DataMemoryBarrier(2,3);
          piVar10 = (int *)(uVar21 + 0x9c);
          if (0x14 < *piVar10) {
            do {
              cVar5 = '\x01';
              bVar6 = (bool)ExclusiveMonitorPass(piVar10,0x10);
              if (bVar6) {
                *piVar10 = *piVar10 + -1;
                cVar5 = ExclusiveMonitorsStatus();
              }
            } while (cVar5 != '\0');
            uVar22 = Aska::Semaphore::IsReady() const(uVar21 + 0xd8);
            if ((uVar22 & 1) != 0) {
              Aska::Semaphore::Signal() const(uVar21 + 0xd8);
            }
          }
          return puVar17 + 8;
        }
      }
    }
    uVar4 = *(uint *)(puVar9 + 8);
  } while (uVar3 != uVar4);
  DataMemoryBarrier(2,3);
  *(undefined4 *)(uVar21 + 0x98) = 0xffffffff;
  DataMemoryBarrier(2,3);
  piVar10 = (int *)(uVar21 + 0x9c);
  if (0x14 < *piVar10) {
    do {
      cVar5 = '\x01';
      bVar6 = (bool)ExclusiveMonitorPass(piVar10,0x10);
      if (bVar6) {
        *piVar10 = *piVar10 + -1;
        cVar5 = ExclusiveMonitorsStatus();
      }
    } while (cVar5 != '\0');
    uVar16 = Aska::Semaphore::IsReady() const(uVar21 + 0xd8);
    if ((uVar16 & 1) != 0) {
      Aska::Semaphore::Signal() const(uVar21 + 0xd8);
    }
  }
  puVar17 = (ulong *)(uVar21 + 0x48);
  uVar21 = *puVar17;
  if (*puVar17 == param_1) {
    if (0 < iStack_64) {
      return (ulong *)0x0;
    }
    puVar7 = *(undefined8 **)(param_1 + 0x30);
    if (puVar7 == (undefined8 *)0x0) {
      return (ulong *)0x0;
    }
    iStack_64 = iStack_64 + 1;
    uStack_88 = 4;
    uStack_80 = 0;
    puStack_70 = (ulong *)0x0;
    uStack_98 = param_1;
    lStack_90 = param_2;
    piStack_78 = &iStack_64;
    (**(code **)*puVar7)(puVar7,&uStack_98);
    uVar21 = param_1;
    if (puStack_70 != (ulong *)0x0) {
      return puStack_70;
    }
  }
  goto code_r0x0204b978;
}

// ==== Aska::MemoryManager::AlignedMalloc(unsigned long, long)
// vaddr 0x1f4bd20 | ghidra 0x204bd20 | size 1460 | symbol _ZN4Aska13MemoryManager13AlignedMallocEml | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZN4Aska13MemoryManager13AlignedMallocEml(long param_1,long param_2,long param_3)

{
  int *piVar1;
  ulong uVar2;
  ulong uVar3;
  ulong uVar4;
  uint uVar5;
  char cVar6;
  bool bVar7;
  ulong uVar8;
  undefined8 *puVar9;
  int iVar10;
  ulong *puVar11;
  int *piVar12;
  ulong *puVar13;
  long lVar14;
  long lVar15;
  ulong uVar16;
  ulong uVar17;
  long *plVar18;
  ulong *puVar19;
  long lVar20;
  long *plVar21;
  ulong uVar22;
  ulong uVar23;
  long lVar24;
  char *pcVar25;
  ulong *puVar26;
  long lVar27;
  long lStack_98;
  long lStack_90;
  long lStack_88;
  undefined4 uStack_80;
  int *piStack_78;
  ulong uStack_70;
  int iStack_64;
  
  if (param_2 == 0) {
    return 0;
  }
  if (*(char *)(param_1 + 8) == '\x01') {
    uVar8 = (*(code *)PTR__ZN4Aska13MemoryManager17AlignedMallocHighEml_02cab2b8)(param_1,param_2);
    return uVar8;
  }
  if (param_3 < 5) {
    param_3 = 4;
  }
  uVar8 = param_2 + 0x4fU & 0xfffffffffffffff0;
  iStack_64 = 0;
  lVar27 = param_1;
code_r0x0204be40:
  piVar12 = (int *)(lVar27 + 0x98);
  iVar10 = 0;
code_r0x0204be48:
  do {
    if (*piVar12 == -1) goto code_r0x0204be54;
    ClearExclusiveLocal();
    bVar7 = iVar10 < 0x1ff;
    iVar10 = iVar10 + 1;
  } while (bVar7);
  piVar1 = (int *)(lVar27 + 0x9c);
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
      uVar16 = Aska::Semaphore::IsReady() const();
      if ((uVar16 & 1) != 0) goto code_r0x0204bdf4;
      do {
        do {
          cVar6 = '\x01';
          bVar7 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar7) {
            *piVar1 = *piVar1 + -1;
            cVar6 = ExclusiveMonitorsStatus();
          }
        } while (cVar6 != '\0');
        Aska::Thread::Sleep(unsigned int)(1);
        while( true ) {
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
            if (cVar6 == '\0') goto code_r0x0204be24;
          }
          ClearExclusiveLocal();
          uVar16 = Aska::Semaphore::IsReady() const(lVar27 + 0xd8);
          if ((uVar16 & 1) == 0) break;
code_r0x0204bdf4:
          Aska::Semaphore::Wait() const(lVar27 + 0xd8);
        }
      } while( true );
    }
    cVar6 = '\x01';
    bVar7 = (bool)ExclusiveMonitorPass(piVar12,0x10);
    if (bVar7) {
      *piVar12 = 0;
      cVar6 = ExclusiveMonitorsStatus();
    }
  } while (cVar6 != '\0');
code_r0x0204be24:
  do {
    cVar6 = '\x01';
    bVar7 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar7) {
      *piVar1 = *piVar1 + -1;
      cVar6 = ExclusiveMonitorsStatus();
    }
  } while (cVar6 != '\0');
  DataMemoryBarrier(2,3);
  goto code_r0x0204bea0;
code_r0x0204be54:
  cVar6 = '\x01';
  bVar7 = (bool)ExclusiveMonitorPass(piVar12,0x10);
  if (bVar7) {
    *piVar12 = 0;
    cVar6 = ExclusiveMonitorsStatus();
  }
  if (cVar6 == '\0') goto code_r0x0204be9c;
  goto code_r0x0204be48;
code_r0x0204be9c:
  DataMemoryBarrier(2,3);
code_r0x0204bea0:
  lVar14 = *(long *)(lVar27 + 0x20);
  lVar15 = *(long *)(lVar27 + 0x10);
  uVar16 = 0;
  do {
    puVar11 = (ulong *)(lVar15 + uVar16 * 0x28 + 0x20);
    if (uVar8 <= *puVar11) {
      puVar13 = (ulong *)(lVar14 + uVar16 * 0x10000);
      for (puVar19 = (ulong *)puVar13[3]; puVar19 != puVar13; puVar19 = (ulong *)puVar19[3]) {
        if (uVar8 <= *puVar19) {
          uVar22 = param_3 + 0x3f + (long)puVar19 & -param_3;
          uVar17 = *puVar19 + (long)puVar19;
          if ((param_2 + 0xf + uVar22 & 0xfffffffffffffff0) <= uVar17) {
            puVar26 = (ulong *)(uVar22 - 0x40);
            uVar23 = (long)puVar26 - (long)puVar19;
            if (uVar23 == 0) {
              uVar17 = 0;
            }
            else {
              uVar2 = puVar19[1];
              plVar18 = (long *)puVar19[2];
              uVar3 = puVar19[3];
              uVar4 = puVar19[4];
              *(undefined1 *)(uVar22 - 0xf) = 0;
              *puVar26 = uVar17 - (long)puVar26;
              *(ulong *)(uVar22 - 0x38) = uVar2;
              *(ulong *)(uVar22 - 0x28) = uVar3;
              *(ulong **)(uVar2 + 0x10) = puVar26;
              if (uVar23 < 0x50) {
                uVar17 = 0;
                if (*(char *)((long)plVar18 + 0x31) != '\0') {
                  uVar17 = uVar23;
                }
                *plVar18 = *plVar18 + uVar23;
                *(long **)(uVar22 - 0x30) = plVar18;
                *(ulong *)(uVar22 - 0x20) = uVar4;
                plVar18[1] = (long)puVar26;
              }
              else {
                uVar17 = 0;
                *puVar19 = uVar23;
                puVar19[1] = (ulong)puVar26;
                puVar19[3] = (ulong)puVar26;
                *(ulong **)(uVar22 - 0x30) = puVar19;
                *(ulong **)(uVar22 - 0x20) = puVar19;
              }
            }
            if (*puVar26 - uVar8 < 0x50) {
              *(undefined8 *)(*(long *)(uVar22 - 0x20) + 0x18) = *(undefined8 *)(uVar22 - 0x28);
              *(undefined8 *)(*(long *)(uVar22 - 0x28) + 0x20) = *(undefined8 *)(uVar22 - 0x20);
              uVar8 = *puVar26;
            }
            else {
              puVar19 = (ulong *)((long)puVar26 + uVar8);
              *puVar19 = *puVar26 - uVar8;
              *(undefined1 *)((long)puVar19 + 0x31) = 0;
              puVar19[4] = *(ulong *)(uVar22 - 0x20);
              puVar19[3] = *(ulong *)(uVar22 - 0x28);
              *(ulong **)(*(long *)(uVar22 - 0x20) + 0x18) = puVar19;
              *(ulong **)(*(long *)(uVar22 - 0x28) + 0x20) = puVar19;
              *(ulong **)(*(long *)(uVar22 - 0x38) + 0x10) = puVar19;
              puVar19[1] = *(ulong *)(uVar22 - 0x38);
              *(ulong **)(uVar22 - 0x38) = puVar19;
              puVar19[2] = (ulong)puVar26;
              *puVar26 = uVar8;
            }
            *(long *)(uVar22 - 0x18) = lVar27;
            *(undefined8 *)(uVar22 - 8) = 0;
            *(undefined2 *)(uVar22 - 0x10) = 0x100;
            lVar20 = lVar15 + uVar16 * 0x28;
            plVar21 = (long *)(lVar20 + 0x10);
            lVar24 = *plVar21;
            *plVar21 = lVar24 + uVar8 + uVar17;
            plVar18 = (long *)(lVar20 + 0x18);
            *plVar18 = *plVar18 - (uVar8 + uVar17);
            if (lVar24 != 0) goto code_r0x0204c208;
            uVar8 = (long)puVar26 + (*puVar26 - (long)puVar13);
            if (*(char *)(puVar13[2] + 0x31) != '\x01') {
              uVar8 = uVar8 + 0x40;
            }
            uVar17 = uVar8 + 0xffff >> 0x10;
            if (uVar8 >> 6 < 0x3ff) {
              uVar17 = 1;
            }
            uVar8 = uVar17 + uVar16;
            if ((*(uint *)(lVar27 + 0x18) <= uVar8) ||
               (pcVar25 = (char *)(lVar15 + uVar8 * 0x28), *pcVar25 != '\0')) goto code_r0x0204c208;
            *pcVar25 = '\x01';
            lVar24 = lVar15 + uVar16 * 0x28;
            lVar20 = lVar15 + uVar8 * 0x28;
            puVar9 = (undefined8 *)(lVar14 + uVar8 * 0x10000);
            *(undefined4 *)(lVar20 + 4) = *(undefined4 *)(lVar24 + 4);
            *(int *)(lVar15 + (ulong)*(uint *)(lVar24 + 4) * 0x28 + 8) = (int)uVar8;
            *(int *)(lVar24 + 4) = (int)uVar8;
            *(int *)(lVar20 + 8) = (int)uVar16;
            lVar14 = *plVar21;
            *(undefined8 *)(lVar20 + 0x10) = 0;
            lVar14 = (uVar17 * 0x10000 - lVar14) + -0x40;
            lVar24 = (*plVar18 - lVar14) + -0x40;
            *(long *)(lVar20 + 0x18) = lVar24;
            *(long *)(lVar20 + 0x20) = lVar24;
            *(undefined2 *)(puVar9 + 6) = 0x100;
            puVar9[7] = 0;
            plVar21 = puVar9 + 8;
            *plVar21 = lVar24;
            *(undefined2 *)(puVar9 + 0xe) = 0;
            puVar9[0xb] = puVar9;
            puVar9[0xc] = puVar9;
            puVar9[9] = puVar9;
            puVar9[10] = puVar9;
            puVar9[3] = plVar21;
            puVar9[4] = plVar21;
            *puVar9 = 0x40;
            puVar9[1] = plVar21;
            puVar9[2] = plVar21;
            *plVar18 = lVar14;
            puVar19 = (ulong *)puVar13[3];
            if (puVar19 == puVar13) goto code_r0x0204c208;
            goto code_r0x0204c1e0;
          }
        }
      }
    }
    uVar5 = *(uint *)(lVar15 + uVar16 * 0x28 + 4);
    uVar16 = (ulong)uVar5;
  } while (uVar5 != 0);
  DataMemoryBarrier(2,3);
  *(undefined4 *)(lVar27 + 0x98) = 0xffffffff;
  DataMemoryBarrier(2,3);
  piVar12 = (int *)(lVar27 + 0x9c);
  if (0x14 < *piVar12) {
    do {
      cVar6 = '\x01';
      bVar7 = (bool)ExclusiveMonitorPass(piVar12,0x10);
      if (bVar7) {
        *piVar12 = *piVar12 + -1;
        cVar6 = ExclusiveMonitorsStatus();
      }
    } while (cVar6 != '\0');
    uVar16 = Aska::Semaphore::IsReady() const(lVar27 + 0xd8);
    if ((uVar16 & 1) != 0) {
      Aska::Semaphore::Signal() const(lVar27 + 0xd8);
    }
  }
  plVar18 = (long *)(lVar27 + 0x48);
  lVar27 = *plVar18;
  if (*plVar18 == param_1) {
    if (0 < iStack_64) {
      return 0;
    }
    puVar9 = *(undefined8 **)(param_1 + 0x30);
    if (puVar9 == (undefined8 *)0x0) {
      return 0;
    }
    iStack_64 = iStack_64 + 1;
    uStack_80 = 0;
    uStack_70 = 0;
    lStack_98 = param_1;
    lStack_90 = param_2;
    lStack_88 = param_3;
    piStack_78 = &iStack_64;
    (**(code **)*puVar9)(puVar9,&lStack_98);
    lVar27 = param_1;
    if (uStack_70 != 0) {
      return uStack_70;
    }
  }
  goto code_r0x0204be40;
  while (puVar19 = (ulong *)puVar19[3], puVar19 != puVar13) {
code_r0x0204c1e0:
    if (puVar9 < (undefined8 *)(*puVar19 + (long)puVar19)) {
      *puVar19 = (long)puVar9 - (long)puVar19;
      break;
    }
  }
code_r0x0204c208:
  puVar13 = (ulong *)(*(long *)(lVar27 + 0x20) +
                     ((lVar15 + uVar16 * 0x28) - *(long *)(lVar27 + 0x10) >> 3) *
                     -0x3333333333330000);
  puVar19 = (ulong *)puVar13[3];
  if (puVar13 < puVar19) {
    uVar16 = 0;
    do {
      uVar8 = uVar16;
      if ((*(char *)((long)puVar19 + 0x31) != '\x01') && (uVar8 = *puVar19, *puVar19 <= uVar16)) {
        uVar8 = uVar16;
      }
      puVar19 = (ulong *)puVar19[3];
      uVar16 = uVar8;
    } while (puVar13 < puVar19);
  }
  else {
    uVar8 = 0;
  }
  *puVar11 = uVar8;
  DataMemoryBarrier(2,3);
  *(undefined4 *)(lVar27 + 0x98) = 0xffffffff;
  DataMemoryBarrier(2,3);
  piVar12 = (int *)(lVar27 + 0x9c);
  if (0x14 < *piVar12) {
    do {
      cVar6 = '\x01';
      bVar7 = (bool)ExclusiveMonitorPass(piVar12,0x10);
      if (bVar7) {
        *piVar12 = *piVar12 + -1;
        cVar6 = ExclusiveMonitorsStatus();
      }
    } while (cVar6 != '\0');
    uVar8 = Aska::Semaphore::IsReady() const(lVar27 + 0xd8);
    if ((uVar8 & 1) != 0) {
      Aska::Semaphore::Signal() const(lVar27 + 0xd8);
    }
  }
  return uVar22;
}

// ==== Aska::MemoryManager::AlignedMallocHigh(unsigned long, long)
// vaddr 0x1f4c2d4 | ghidra 0x204c2d4 | size 1460 | symbol _ZN4Aska13MemoryManager17AlignedMallocHighEml | lib libSOA-3.7.0.so | 2026-10-04
ulong * _ZN4Aska13MemoryManager17AlignedMallocHighEml(ulong param_1,long param_2,long param_3)

{
  int *piVar1;
  long lVar2;
  uint uVar3;
  char cVar4;
  bool bVar5;
  undefined8 *puVar6;
  long lVar7;
  int iVar8;
  int *piVar9;
  undefined1 *puVar10;
  long lVar11;
  ulong uVar12;
  long *plVar13;
  ulong *puVar14;
  ulong *puVar15;
  long *plVar16;
  long lVar17;
  long *plVar18;
  ulong *puVar19;
  ulong uVar20;
  ulong *puVar21;
  ulong uVar22;
  ulong uVar23;
  ulong *puVar24;
  long lVar25;
  long *plVar26;
  ulong *puVar27;
  ulong uVar28;
  ulong uVar29;
  ulong uStack_98;
  long lStack_90;
  long lStack_88;
  undefined4 uStack_80;
  int *piStack_78;
  ulong *puStack_70;
  int iStack_64;
  
  if (param_2 == 0) {
    return (ulong *)0x0;
  }
  if (param_3 < 5) {
    param_3 = 4;
  }
  uVar29 = param_2 + 0x4fU & 0xfffffffffffffff0;
  iStack_64 = 0;
  uVar28 = param_1;
  do {
    piVar9 = (int *)(uVar28 + 0x98);
    iVar8 = 0;
code_r0x0204c330:
    if (*piVar9 == -1) {
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar9,0x10);
      if (bVar5) {
        *piVar9 = 0;
        cVar4 = ExclusiveMonitorsStatus();
      }
      if (cVar4 == '\0') goto code_r0x0204c400;
      goto code_r0x0204c330;
    }
    ClearExclusiveLocal();
    bVar5 = iVar8 < 0x1ff;
    iVar8 = iVar8 + 1;
    if (bVar5) goto code_r0x0204c330;
    piVar1 = (int *)(uVar28 + 0x9c);
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
        uVar12 = Aska::Semaphore::IsReady() const();
        if ((uVar12 & 1) != 0) goto code_r0x0204c3c4;
        do {
          do {
            cVar4 = '\x01';
            bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
            if (bVar5) {
              *piVar1 = *piVar1 + -1;
              cVar4 = ExclusiveMonitorsStatus();
            }
          } while (cVar4 != '\0');
          Aska::Thread::Sleep(unsigned int)(1);
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
              if (cVar4 == '\0') goto code_r0x0204c3f0;
            }
            ClearExclusiveLocal();
            uVar12 = Aska::Semaphore::IsReady() const(uVar28 + 0xd8);
            if ((uVar12 & 1) == 0) break;
code_r0x0204c3c4:
            Aska::Semaphore::Wait() const(uVar28 + 0xd8);
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
code_r0x0204c3f0:
    do {
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar5) {
        *piVar1 = *piVar1 + -1;
        cVar4 = ExclusiveMonitorsStatus();
      }
    } while (cVar4 != '\0');
code_r0x0204c400:
    DataMemoryBarrier(2,3);
    lVar17 = *(long *)(uVar28 + 0x10);
    lVar11 = *(long *)(uVar28 + 0x20);
    uVar3 = *(uint *)(lVar17 + 8);
    do {
      uVar12 = (ulong)uVar3;
      puVar15 = (ulong *)(lVar17 + uVar12 * 0x28 + 0x20);
      if (uVar29 <= *puVar15) {
        puVar14 = (ulong *)(lVar11 + uVar12 * 0x10000);
        for (puVar19 = (ulong *)puVar14[4]; puVar19 != puVar14; puVar19 = (ulong *)puVar19[4]) {
          uVar20 = *puVar19;
          if ((uVar29 <= uVar20) &&
             (puVar21 = (ulong *)((long)puVar19 + (uVar20 - uVar29) & -param_3),
             puVar19 + 8 <= puVar21)) {
            puVar27 = puVar21 + -8;
            puVar24 = (ulong *)((long)puVar27 + uVar29);
            uVar20 = (long)puVar19 + (uVar20 - (long)puVar24);
            if (uVar20 < 0x50) {
              uVar29 = uVar20 + uVar29;
            }
            else {
              *puVar24 = uVar20;
              *(undefined1 *)((long)puVar24 + 0x31) = 0;
              puVar24[4] = (ulong)puVar19;
              puVar24[3] = puVar19[3];
              *(ulong **)(puVar19[3] + 0x20) = puVar24;
              puVar19[3] = (ulong)puVar24;
              *(ulong **)(puVar19[1] + 0x10) = puVar24;
              puVar24[1] = puVar19[1];
              puVar19[1] = (ulong)puVar24;
              puVar24[2] = (ulong)puVar19;
              *puVar19 = (long)puVar24 - (long)puVar19;
            }
            uVar20 = puVar19[1];
            puVar24 = (ulong *)puVar19[3];
            uVar22 = (long)puVar27 - (long)puVar19;
            puVar10 = (undefined1 *)(lVar17 + uVar12 * 0x28);
            if (uVar22 < 0x50) {
              plVar26 = (long *)puVar19[2];
              puVar19 = (ulong *)puVar19[4];
              uVar23 = 0;
              if (*(char *)((long)plVar26 + 0x31) != '\0') {
                uVar23 = uVar22;
              }
              *plVar26 = *plVar26 + uVar22;
              puVar21[-7] = uVar20;
              puVar21[-6] = (ulong)plVar26;
              puVar21[-5] = (ulong)puVar24;
              puVar21[-4] = (ulong)puVar19;
              plVar26[1] = (long)puVar27;
              *(ulong **)(uVar20 + 0x10) = puVar27;
              puVar19[3] = (ulong)puVar24;
            }
            else {
              uVar23 = 0;
              *(undefined1 *)((long)puVar21 + -0xf) = 0;
              puVar21[-7] = uVar20;
              puVar21[-5] = (ulong)puVar24;
              *(ulong **)(uVar20 + 0x10) = puVar27;
              *puVar19 = uVar22;
              puVar19[1] = (ulong)puVar27;
              puVar21[-6] = (ulong)puVar19;
              puVar24 = puVar27;
            }
            puVar24[4] = (ulong)puVar19;
            *puVar27 = uVar29;
            puVar21[-3] = uVar28;
            puVar21[-1] = 0;
            *(undefined2 *)(puVar21 + -2) = 0x101;
            lVar25 = lVar17 + uVar12 * 0x28;
            plVar26 = (long *)(lVar25 + 0x10);
            lVar7 = *plVar26;
            lVar2 = uVar23 + uVar29;
            *plVar26 = lVar7 + lVar2;
            puVar19 = (ulong *)(lVar25 + 0x18);
            *puVar19 = *puVar19 - lVar2;
            if ((lVar7 == 0) && (uVar22 >> 0x10 != 0)) {
              lVar25 = lVar17 + uVar12 * 0x28;
              lVar7 = (uVar22 >> 0x10) + uVar12;
              puVar10 = (undefined1 *)(lVar17 + lVar7 * 0x28);
              *(undefined4 *)(puVar10 + 4) = *(undefined4 *)(lVar25 + 4);
              uVar12 = (uVar22 & 0xffffffffffff0000) - 0x40;
              plVar13 = (long *)(lVar11 + lVar7 * 0x10000);
              *(int *)(lVar17 + (ulong)*(uint *)(lVar25 + 4) * 0x28 + 8) = (int)lVar7;
              *(int *)(lVar25 + 4) = (int)lVar7;
              *(uint *)(puVar10 + 8) = uVar3;
              uVar29 = *puVar19;
              *plVar26 = 0;
              *puVar19 = uVar12;
              *puVar15 = uVar12;
              *(undefined2 *)(puVar14 + 6) = 0x100;
              puVar14[7] = 0;
              puVar15 = puVar14 + 8;
              *puVar15 = uVar12;
              *(undefined2 *)(puVar14 + 0xe) = 0;
              puVar14[0xb] = (ulong)puVar14;
              puVar14[0xc] = (ulong)puVar14;
              puVar14[9] = (ulong)puVar14;
              puVar14[10] = (ulong)puVar14;
              puVar14[3] = (ulong)puVar15;
              puVar14[4] = (ulong)puVar15;
              *puVar14 = 0x40;
              puVar14[1] = (ulong)puVar15;
              puVar14[2] = (ulong)puVar15;
              *puVar10 = 1;
              plVar18 = (long *)(puVar10 + 0x10);
              *plVar18 = lVar2;
              *(ulong *)(puVar10 + 0x18) = (uVar29 - 0x40) - *puVar19;
              plVar16 = (long *)puVar21[-7];
              plVar26 = plVar13 + 8;
              uVar29 = (long)puVar27 - (long)plVar26;
              if (uVar29 < 0x40) {
                *(undefined2 *)(plVar13 + 6) = 0x100;
                plVar13[7] = 0;
                *plVar13 = uVar29 + 0x40;
                *plVar18 = *plVar18 + uVar29;
                *(ulong *)(puVar10 + 0x18) = *(long *)(puVar10 + 0x18) - uVar29;
                plVar13[1] = (long)puVar27;
                if (plVar13 < plVar16) {
                  plVar13[2] = (long)plVar16;
                  plVar13[3] = (long)plVar16;
                  plVar13[4] = (long)plVar16;
                  puVar21[-6] = (ulong)plVar13;
                  plVar16[1] = (long)plVar13;
                  plVar16[3] = (long)plVar13;
                  puVar15 = (ulong *)(plVar16 + 4);
                }
                else {
                  puVar15 = puVar21 + -6;
                  plVar13[2] = (long)puVar27;
                  plVar13[3] = (long)plVar13;
                  plVar13[4] = (long)plVar13;
                  puVar21[-7] = (ulong)plVar13;
                }
              }
              else {
                *(undefined2 *)(plVar13 + 6) = 0x100;
                plVar13[3] = (long)plVar26;
                plVar13[4] = (long)plVar26;
                plVar13[1] = (long)plVar26;
                plVar13[2] = (long)plVar26;
                plVar13[7] = 0;
                plVar13[8] = uVar29;
                *(undefined2 *)(plVar13 + 0xe) = 0;
                plVar13[0xb] = (long)plVar13;
                plVar13[0xc] = (long)plVar13;
                plVar13[9] = (long)plVar13;
                plVar13[10] = (long)plVar13;
                *plVar13 = 0x40;
                if (plVar26 < plVar16) {
                  plVar13[2] = (long)plVar16;
                  plVar13[3] = (long)plVar26;
                  plVar13[4] = (long)plVar16;
                  plVar13[9] = (long)puVar27;
                  plVar13[10] = (long)plVar13;
                  plVar13[0xb] = (long)plVar16;
                  plVar13[0xc] = (long)plVar13;
                  puVar21[-6] = (ulong)plVar26;
                  plVar16[1] = (long)plVar13;
                  plVar16[3] = (long)plVar13;
                  puVar15 = (ulong *)(plVar16 + 4);
                  plVar13 = plVar26;
                }
                else {
                  plVar13[2] = (long)puVar27;
                  plVar13[3] = (long)plVar26;
                  plVar13[4] = (long)plVar26;
                  plVar13[9] = (long)puVar27;
                  plVar13[10] = (long)plVar13;
                  plVar13[0xb] = (long)plVar13;
                  plVar13[0xc] = (long)plVar13;
                  puVar21[-7] = (ulong)plVar13;
                  puVar15 = puVar21 + -6;
                  plVar13 = plVar26;
                }
              }
              *puVar15 = (ulong)plVar13;
            }
            puVar15 = (ulong *)(*(long *)(uVar28 + 0x20) +
                               ((ulong)((long)puVar10 - *(long *)(uVar28 + 0x10)) >> 3) *
                               -0x3333333333330000);
            puVar14 = (ulong *)puVar15[3];
            if (puVar15 < puVar14) {
              uVar12 = 0;
              do {
                uVar29 = uVar12;
                if ((*(char *)((long)puVar14 + 0x31) != '\x01') &&
                   (uVar29 = *puVar14, *puVar14 <= uVar12)) {
                  uVar29 = uVar12;
                }
                puVar14 = (ulong *)puVar14[3];
                uVar12 = uVar29;
              } while (puVar15 < puVar14);
            }
            else {
              uVar29 = 0;
            }
            *(ulong *)(puVar10 + 0x20) = uVar29;
            DataMemoryBarrier(2,3);
            *(undefined4 *)(uVar28 + 0x98) = 0xffffffff;
            DataMemoryBarrier(2,3);
            piVar9 = (int *)(uVar28 + 0x9c);
            if (0x14 < *piVar9) {
              do {
                cVar4 = '\x01';
                bVar5 = (bool)ExclusiveMonitorPass(piVar9,0x10);
                if (bVar5) {
                  *piVar9 = *piVar9 + -1;
                  cVar4 = ExclusiveMonitorsStatus();
                }
              } while (cVar4 != '\0');
              uVar29 = Aska::Semaphore::IsReady() const(uVar28 + 0xd8);
              if ((uVar29 & 1) != 0) {
                Aska::Semaphore::Signal() const(uVar28 + 0xd8);
                return puVar21;
              }
              return puVar21;
            }
            return puVar21;
          }
        }
      }
      uVar3 = *(uint *)(lVar17 + uVar12 * 0x28 + 8);
    } while (*(uint *)(lVar17 + 8) != uVar3);
    DataMemoryBarrier(2,3);
    *(undefined4 *)(uVar28 + 0x98) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar9 = (int *)(uVar28 + 0x9c);
    if (0x14 < *piVar9) {
      do {
        cVar4 = '\x01';
        bVar5 = (bool)ExclusiveMonitorPass(piVar9,0x10);
        if (bVar5) {
          *piVar9 = *piVar9 + -1;
          cVar4 = ExclusiveMonitorsStatus();
        }
      } while (cVar4 != '\0');
      uVar12 = Aska::Semaphore::IsReady() const(uVar28 + 0xd8);
      if ((uVar12 & 1) != 0) {
        Aska::Semaphore::Signal() const(uVar28 + 0xd8);
      }
    }
    puVar15 = (ulong *)(uVar28 + 0x48);
    uVar28 = *puVar15;
    if (*puVar15 == param_1) {
      if (0 < iStack_64) {
        return (ulong *)0x0;
      }
      puVar6 = *(undefined8 **)(param_1 + 0x30);
      if (puVar6 == (undefined8 *)0x0) {
        return (ulong *)0x0;
      }
      iStack_64 = iStack_64 + 1;
      uStack_80 = 0;
      puStack_70 = (ulong *)0x0;
      uStack_98 = param_1;
      lStack_90 = param_2;
      lStack_88 = param_3;
      piStack_78 = &iStack_64;
      (**(code **)*puVar6)(puVar6,&uStack_98);
      uVar28 = param_1;
      if (puStack_70 != (ulong *)0x0) {
        return puStack_70;
      }
    }
  } while( true );
}

// ==== Aska::MemoryManager::Realloc(unsigned long, void*, long)
// vaddr 0x1f4c888 | ghidra 0x204c888 | size 2124 | symbol _ZN4Aska13MemoryManager7ReallocEmPvl | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Possible PIC construction at 0x0204c8d4: Changing call to branch */
/* WARNING: Removing unreachable block (ram,0x0204c8d8) */
/* WARNING: Removing unreachable block (ram,0x0204c8e0) */
/* WARNING: Removing unreachable block (ram,0x0204c8e8) */
/* WARNING: Removing unreachable block (ram,0x0204c908) */
/* WARNING: Removing unreachable block (ram,0x0204c9c0) */
/* WARNING: Removing unreachable block (ram,0x0204c920) */

ulong _ZN4Aska13MemoryManager7ReallocEmPvl(long param_1,long param_2,ulong param_3,ulong param_4)

{
  int *piVar1;
  ulong *puVar2;
  ulong uVar3;
  uint uVar4;
  char cVar5;
  bool bVar6;
  bool bVar7;
  ulong uVar8;
  int iVar9;
  ulong uVar10;
  char *pcVar11;
  int *piVar12;
  undefined4 uVar13;
  ulong uVar14;
  long *plVar15;
  char *pcVar16;
  char *pcVar17;
  long lVar18;
  long lVar19;
  ulong *puVar20;
  ulong uVar21;
  long lVar22;
  undefined1 *puVar23;
  long lVar24;
  ulong *puVar25;
  undefined1 *puVar26;
  long lVar27;
  ulong uVar28;
  long lVar29;
  uint *puVar30;
  ulong *puVar31;
  
  if (param_3 == 0) {
code_r0x011ec6e0:
    uVar8 = (*(code *)PTR__ZN4Aska13MemoryManager13AlignedMallocEml_02cae360)
                      (param_1,param_2,param_4);
    return uVar8;
  }
  puVar31 = (ulong *)(param_3 - 0x40);
  if (param_2 == 0) {
    Aska::MemoryManager::LocalFree(Aska::_MemoryBlock*)(*(long *)(param_3 - 0x18),puVar31);
    return 0;
  }
  if (*(long *)(param_3 - 0x18) != param_1) goto code_r0x011ec6e0;
  piVar12 = (int *)(param_1 + 0x98);
  iVar9 = 0;
code_r0x0204c96c:
  if (*piVar12 == -1) {
    cVar5 = '\x01';
    bVar6 = (bool)ExclusiveMonitorPass(piVar12,0x10);
    if (bVar6) {
      *piVar12 = 0;
      cVar5 = ExclusiveMonitorsStatus();
    }
    if (cVar5 == '\0') goto code_r0x0204ca40;
    goto code_r0x0204c96c;
  }
  ClearExclusiveLocal();
  bVar6 = iVar9 < 0x1ff;
  iVar9 = iVar9 + 1;
  if (bVar6) goto code_r0x0204c96c;
  piVar1 = (int *)(param_1 + 0x9c);
  do {
    cVar5 = '\x01';
    bVar6 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar6) {
      *piVar1 = *piVar1 + 1;
      cVar5 = ExclusiveMonitorsStatus();
    }
  } while (cVar5 != '\0');
  do {
    if (*piVar12 != -1) {
      ClearExclusiveLocal();
      do {
        uVar8 = Aska::Semaphore::IsReady() const(param_1 + 0xd8);
        if ((uVar8 & 1) == 0) {
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
          Aska::Semaphore::Wait() const(param_1 + 0xd8);
        }
        do {
          cVar5 = '\x01';
          bVar6 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar6) {
            *piVar1 = *piVar1 + 1;
            cVar5 = ExclusiveMonitorsStatus();
          }
        } while (cVar5 != '\0');
        while (*piVar12 == -1) {
          cVar5 = '\x01';
          bVar6 = (bool)ExclusiveMonitorPass(piVar12,0x10);
          if (bVar6) {
            *piVar12 = 0;
            cVar5 = ExclusiveMonitorsStatus();
          }
          if (cVar5 == '\0') goto code_r0x0204ca30;
        }
        ClearExclusiveLocal();
      } while( true );
    }
    cVar5 = '\x01';
    bVar6 = (bool)ExclusiveMonitorPass(piVar12,0x10);
    if (bVar6) {
      *piVar12 = 0;
      cVar5 = ExclusiveMonitorsStatus();
    }
  } while (cVar5 != '\0');
code_r0x0204ca30:
  do {
    cVar5 = '\x01';
    bVar6 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar6) {
      *piVar1 = *piVar1 + -1;
      cVar5 = ExclusiveMonitorsStatus();
    }
  } while (cVar5 != '\0');
code_r0x0204ca40:
  DataMemoryBarrier(2,3);
  uVar10 = *puVar31;
  uVar14 = param_2 + 0x4fU & 0xfffffffffffffff0;
  uVar8 = uVar10 - uVar14;
  if ((uVar10 < uVar14 || uVar8 == 0) || (uVar8 < 0x50)) {
    if (uVar14 <= uVar10) {
code_r0x0204d064:
      bVar6 = true;
      goto code_r0x0204d068;
    }
    plVar15 = *(long **)(param_3 - 0x38);
    if (*(char *)((long)plVar15 + 0x31) != '\x01') {
      uVar8 = 0;
      if (param_4 != 0) {
        uVar8 = param_3 / param_4;
      }
      if (param_3 != uVar8 * param_4) goto code_r0x0204cae0;
      uVar8 = *plVar15 + uVar10;
      if (uVar14 <= uVar8) {
        uVar21 = plVar15[1];
        if (uVar8 - uVar14 < 0x50) {
          *(ulong *)(param_3 - 0x40) = uVar8;
          *(ulong *)(param_3 - 0x38) = uVar21;
          *(ulong **)(uVar21 + 0x10) = puVar31;
          *(long *)(plVar15[4] + 0x18) = plVar15[3];
          *(long *)(plVar15[3] + 0x20) = plVar15[4];
        }
        else {
          uVar28 = plVar15[3];
          uVar3 = plVar15[4];
          puVar20 = (ulong *)(uVar14 + (long)puVar31);
          *(undefined1 *)((long)puVar20 + 0x31) = 0;
          *puVar20 = uVar8 - uVar14;
          puVar20[1] = uVar21;
          puVar20[2] = (ulong)puVar31;
          puVar20[3] = uVar28;
          puVar20[4] = uVar3;
          *(ulong **)(uVar3 + 0x18) = puVar20;
          *(ulong **)(puVar20[3] + 0x20) = puVar20;
          *(ulong *)(param_3 - 0x40) = uVar14;
          *(ulong **)(param_3 - 0x38) = puVar20;
          *(ulong **)(uVar21 + 0x10) = puVar20;
          uVar8 = uVar14;
        }
        lVar18 = 0;
        uVar14 = (ulong)((long)puVar31 - *(long *)(param_1 + 0x20)) >> 0x10;
        lVar24 = uVar14 + 1;
        lVar19 = uVar14 + 2;
        lVar22 = uVar14 * 0x28;
        do {
          lVar19 = lVar19 + -1;
          if (lVar19 < 1) goto code_r0x0204cd98;
          lVar27 = *(long *)(param_1 + 0x10);
          lVar24 = lVar24 + -1;
          lVar29 = lVar22 + -0x28;
          pcVar11 = (char *)(lVar27 + lVar22);
          lVar18 = lVar27 + lVar24 * 0x28;
          lVar22 = lVar29;
        } while (*pcVar11 == '\0');
        lVar18 = lVar27 + lVar29 + 0x28;
code_r0x0204cd98:
        *(ulong *)(lVar18 + 0x10) = *(long *)(lVar18 + 0x10) + (uVar8 - uVar10);
        *(ulong *)(lVar18 + 0x18) = *(long *)(lVar18 + 0x18) - (uVar8 - uVar10);
        puVar31 = (ulong *)(*(long *)(param_1 + 0x20) +
                           ((ulong)(lVar18 - *(long *)(param_1 + 0x10)) >> 3) * -0x3333333333330000)
        ;
        puVar20 = (ulong *)puVar31[3];
        if (puVar31 < puVar20) {
          uVar10 = 0;
          do {
            uVar8 = uVar10;
            if ((*(char *)((long)puVar20 + 0x31) != '\x01') &&
               (uVar8 = *puVar20, *puVar20 <= uVar10)) {
              uVar8 = uVar10;
            }
            puVar20 = (ulong *)puVar20[3];
            uVar10 = uVar8;
          } while (puVar31 < puVar20);
        }
        else {
          uVar8 = 0;
        }
        *(ulong *)(lVar18 + 0x20) = uVar8;
        goto code_r0x0204d064;
      }
    }
  }
  else {
    uVar10 = 0;
    if (param_4 != 0) {
      uVar10 = param_3 / param_4;
    }
    if (param_3 == uVar10 * param_4) {
      uVar10 = (ulong)((long)puVar31 - *(long *)(param_1 + 0x20)) >> 0x10;
      lVar24 = uVar10 * 0x28;
      pcVar11 = (char *)0x0;
      uVar21 = uVar10 + 1;
      do {
        uVar28 = uVar21 - 1;
        if ((long)uVar21 < 1) goto code_r0x0204caec;
        pcVar11 = (char *)(*(long *)(param_1 + 0x10) + lVar24);
        lVar24 = lVar24 + -0x28;
        uVar21 = uVar28;
      } while (*pcVar11 == '\0');
      pcVar11 = (char *)(*(long *)(param_1 + 0x10) + lVar24 + 0x28);
      uVar10 = uVar28;
code_r0x0204caec:
      puVar20 = (ulong *)(*(long *)(param_1 + 0x20) + uVar10 * 0x10000);
      puVar2 = (ulong *)(uVar14 + (long)puVar31);
      *puVar2 = uVar8;
      puVar25 = puVar20;
      do {
        puVar25 = (ulong *)puVar25[3];
        if (puVar25 == puVar20) break;
      } while (puVar25 < puVar2);
      uVar21 = puVar25[4];
      puVar2[3] = (ulong)puVar25;
      puVar2[4] = uVar21;
      *(ulong **)(uVar21 + 0x18) = puVar2;
      *(ulong **)(puVar2[3] + 0x20) = puVar2;
      uVar21 = *(ulong *)(param_3 - 0x38);
      puVar2[1] = uVar21;
      puVar2[2] = (ulong)puVar31;
      *(ulong **)(uVar21 + 0x10) = puVar2;
      *(ulong **)(puVar2[2] + 8) = puVar2;
      *(ulong *)(param_3 - 0x40) = uVar14;
      plVar15 = (long *)puVar2[1];
      if (*(char *)((long)plVar15 + 0x31) != '\x01') {
        *puVar2 = *puVar2 + *plVar15;
        puVar2[1] = plVar15[1];
        puVar2[3] = plVar15[3];
        *(ulong **)(plVar15[1] + 0x10) = puVar2;
        *(ulong **)(plVar15[3] + 0x20) = puVar2;
      }
      *(undefined1 *)((long)puVar2 + 0x31) = 0;
      lVar24 = *(long *)(pcVar11 + 0x10);
      lVar19 = *(long *)(pcVar11 + 0x18);
      *(ulong *)(pcVar11 + 0x10) = lVar24 - uVar8;
      *(ulong *)(pcVar11 + 0x18) = lVar19 + uVar8;
      pcVar17 = pcVar11;
      if (lVar24 - uVar8 == 0) {
        pcVar16 = *(char **)(param_1 + 0x10);
        if (pcVar11 != pcVar16) {
          uVar4 = *(uint *)(pcVar11 + 8);
          uVar10 = (ulong)uVar4;
          if (*(long *)(pcVar16 + uVar10 * 0x28 + 0x10) == 0) {
            *pcVar11 = '\0';
            pcVar17 = pcVar16 + uVar10 * 0x28;
            lVar24 = lVar19 + uVar8 + *(long *)(pcVar17 + 0x18) + 0x40;
            *(long *)(pcVar17 + 0x18) = lVar24;
            **(long **)(*(long *)(param_1 + 0x20) + uVar10 * 0x10000 + 0x18) = lVar24;
            *(undefined4 *)(pcVar17 + 4) = *(undefined4 *)(pcVar11 + 4);
            *(uint *)(*(long *)(param_1 + 0x10) + (ulong)*(uint *)(pcVar11 + 4) * 0x28 + 8) = uVar4;
          }
        }
        uVar4 = *(uint *)(pcVar17 + 4);
        if ((uVar4 != 0) && (*(long *)(*(long *)(param_1 + 0x10) + (ulong)uVar4 * 0x28 + 0x10) == 0)
           ) {
          puVar26 = (undefined1 *)(*(long *)(param_1 + 0x10) + (ulong)uVar4 * 0x28);
          *puVar26 = 0;
          *(undefined4 *)(pcVar17 + 4) = *(undefined4 *)(puVar26 + 4);
          *(undefined4 *)(*(long *)(param_1 + 0x10) + (ulong)*(uint *)(puVar26 + 4) * 0x28 + 8) =
               *(undefined4 *)(puVar26 + 8);
          lVar24 = *(long *)(puVar26 + 0x18) + *(long *)(pcVar17 + 0x18) + 0x40;
          *(long *)(pcVar17 + 0x18) = lVar24;
          **(long **)(*(long *)(param_1 + 0x20) + (ulong)*(uint *)(puVar26 + 8) * 0x10000 + 0x18) =
               lVar24;
        }
      }
      else {
        puVar31 = (ulong *)puVar2[1];
        if (puVar31 < puVar2) {
          uVar8 = (long)puVar2 + (0xffff - *(long *)(param_1 + 0x20));
          uVar14 = uVar8 >> 0x10;
          if ((long)uVar10 < (long)uVar14) {
            uVar21 = *puVar2;
            puVar20 = (ulong *)(*(long *)(param_1 + 0x20) + (uVar8 & 0xffffffffffff0000));
            uVar28 = (long)puVar20 - (long)puVar2;
            if (uVar28 + 0x80 < uVar21) {
              if (puVar2 == puVar20) {
                uVar28 = puVar2[2];
                *(ulong **)(uVar28 + 8) = puVar31;
                *(ulong *)(puVar2[1] + 0x10) = uVar28;
                *(ulong *)(puVar2[4] + 0x18) = puVar2[3];
                *(ulong *)(puVar2[3] + 0x20) = puVar2[4];
              }
              else {
                uVar21 = uVar21 - uVar28;
                if (uVar28 < 0x40) {
                  plVar15 = (long *)puVar2[2];
                  plVar15[1] = (long)puVar31;
                  *(long **)(puVar2[1] + 0x10) = plVar15;
                  *(ulong *)(puVar2[4] + 0x18) = puVar2[3];
                  *(ulong *)(puVar2[3] + 0x20) = puVar2[4];
                  *plVar15 = *plVar15 + uVar28;
                  *(ulong *)(pcVar11 + 0x10) = *(long *)(pcVar11 + 0x10) + uVar28;
                  *(ulong *)(pcVar11 + 0x18) = *(long *)(pcVar11 + 0x18) - uVar28;
                }
                else {
                  *puVar2 = uVar28;
                }
              }
              puVar31 = puVar20 + 8;
              *puVar31 = uVar21 - 0x40;
              *(undefined2 *)(puVar20 + 6) = 0x100;
              puVar20[7] = 0;
              *(undefined2 *)(puVar20 + 0xe) = 0;
              puVar20[0xb] = (ulong)puVar20;
              puVar20[0xc] = (ulong)puVar20;
              puVar20[9] = (ulong)puVar20;
              puVar20[10] = (ulong)puVar20;
              puVar20[3] = (ulong)puVar31;
              puVar20[4] = (ulong)puVar31;
              puVar20[1] = (ulong)puVar31;
              puVar20[2] = (ulong)puVar31;
              *puVar20 = 0x40;
              *(ulong *)(pcVar11 + 0x18) = *(long *)(pcVar11 + 0x18) - uVar21;
              lVar24 = *(long *)(param_1 + 0x10);
              puVar26 = (undefined1 *)(lVar24 + uVar14 * 0x28);
              puVar30 = (uint *)(puVar26 + 4);
              *puVar30 = *(uint *)(pcVar11 + 4);
              uVar13 = (undefined4)(uVar8 >> 0x10);
              *(undefined4 *)(*(long *)(param_1 + 0x10) + (ulong)*(uint *)(pcVar11 + 4) * 0x28 + 8)
                   = uVar13;
              *(undefined4 *)(pcVar11 + 4) = uVar13;
              *(int *)(puVar26 + 8) = (int)uVar10;
              *puVar26 = 1;
              *(undefined8 *)(puVar26 + 0x10) = 0;
              uVar10 = (ulong)*puVar30;
              if (*puVar30 == 0) {
                lVar19 = (-0x40 - (uVar8 & 0xffffffffffff0000)) + *(long *)(param_1 + 0x28);
code_r0x0204cf30:
                *(long *)(lVar24 + uVar14 * 0x28 + 0x18) = lVar19;
              }
              else {
                if (*(long *)(*(long *)(param_1 + 0x10) + uVar10 * 0x28 + 0x10) != 0) {
                  lVar19 = (uVar10 - uVar14) * 0x10000 + -0x40;
                  goto code_r0x0204cf30;
                }
                puVar23 = (undefined1 *)(*(long *)(param_1 + 0x10) + uVar10 * 0x28);
                *puVar30 = *(uint *)(puVar23 + 4);
                *(undefined4 *)
                 (*(long *)(param_1 + 0x10) + (ulong)*(uint *)(puVar23 + 4) * 0x28 + 8) = uVar13;
                *puVar23 = 0;
                uVar8 = *(long *)(puVar23 + 0x18) + (uVar10 - uVar14) * 0x10000;
                *(ulong *)(lVar24 + uVar14 * 0x28 + 0x18) = uVar8;
                *(undefined2 *)(puVar20 + 6) = 0x100;
                puVar20[3] = (ulong)puVar31;
                puVar20[4] = (ulong)puVar31;
                puVar20[1] = (ulong)puVar31;
                puVar20[2] = (ulong)puVar31;
                *puVar20 = 0x40;
                puVar20[7] = 0;
                puVar20[8] = uVar8;
                *(undefined2 *)(puVar20 + 0xe) = 0;
                puVar20[0xb] = (ulong)puVar20;
                puVar20[0xc] = (ulong)puVar20;
                puVar20[9] = (ulong)puVar20;
                puVar20[10] = (ulong)puVar20;
              }
              puVar31 = (ulong *)(*(long *)(param_1 + 0x20) +
                                 ((ulong)((long)puVar26 - *(long *)(param_1 + 0x10)) >> 3) *
                                 -0x3333333333330000);
              puVar20 = (ulong *)puVar31[3];
              if (puVar31 < puVar20) {
                uVar10 = 0;
                do {
                  uVar8 = uVar10;
                  if ((*(char *)((long)puVar20 + 0x31) != '\x01') &&
                     (uVar8 = *puVar20, *puVar20 <= uVar10)) {
                    uVar8 = uVar10;
                  }
                  puVar20 = (ulong *)puVar20[3];
                  uVar10 = uVar8;
                } while (puVar31 < puVar20);
              }
              else {
                uVar8 = 0;
              }
              *(ulong *)(lVar24 + uVar14 * 0x28 + 0x20) = uVar8;
            }
          }
        }
      }
      puVar31 = (ulong *)(*(long *)(param_1 + 0x20) +
                         ((ulong)((long)pcVar17 - *(long *)(param_1 + 0x10)) >> 3) *
                         -0x3333333333330000);
      puVar20 = (ulong *)puVar31[3];
      if (puVar31 < puVar20) {
        uVar10 = 0;
        do {
          uVar8 = uVar10;
          if ((*(char *)((long)puVar20 + 0x31) != '\x01') && (uVar8 = *puVar20, *puVar20 <= uVar10))
          {
            uVar8 = uVar10;
          }
          puVar20 = (ulong *)puVar20[3];
          uVar10 = uVar8;
        } while (puVar31 < puVar20);
      }
      else {
        uVar8 = 0;
      }
      *(ulong *)(pcVar17 + 0x20) = uVar8;
      goto code_r0x0204d064;
    }
  }
code_r0x0204cae0:
  bVar6 = false;
code_r0x0204d068:
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_1 + 0x98) = 0xffffffff;
  DataMemoryBarrier(2,3);
  piVar12 = (int *)(param_1 + 0x9c);
  if (0x14 < *piVar12) {
    do {
      cVar5 = '\x01';
      bVar7 = (bool)ExclusiveMonitorPass(piVar12,0x10);
      if (bVar7) {
        *piVar12 = *piVar12 + -1;
        cVar5 = ExclusiveMonitorsStatus();
      }
    } while (cVar5 != '\0');
    uVar8 = Aska::Semaphore::IsReady() const(param_1 + 0xd8);
    if ((uVar8 & 1) != 0) {
      Aska::Semaphore::Signal() const(param_1 + 0xd8);
    }
  }
  if (bVar6) {
    return param_3;
  }
  goto code_r0x011ec6e0;
}

// ==== Aska::MemoryManager::Split(void*, void*)
// vaddr 0x1f4d0d4 | ghidra 0x204d0d4 | size 536 | symbol _ZN4Aska13MemoryManager5SplitEPvS1_ | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZN4Aska13MemoryManager5SplitEPvS1_(long param_1,ulong *param_2,ulong param_3)

{
  int *piVar1;
  char cVar2;
  bool bVar3;
  ulong uVar4;
  int iVar5;
  ulong *puVar6;
  int *piVar7;
  ulong *puVar8;
  ulong uVar9;
  
  piVar7 = (int *)(param_1 + 0x98);
  iVar5 = 0;
  do {
    while (*piVar7 == -1) {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar7,0x10);
      if (bVar3) {
        *piVar7 = 0;
        cVar2 = ExclusiveMonitorsStatus();
      }
      if (cVar2 == '\0') goto code_r0x0204d1c0;
    }
    ClearExclusiveLocal();
    bVar3 = iVar5 < 0x1ff;
    iVar5 = iVar5 + 1;
  } while (bVar3);
  piVar1 = (int *)(param_1 + 0x9c);
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
        uVar4 = Aska::Semaphore::IsReady() const(param_1 + 0xd8);
        if ((uVar4 & 1) == 0) {
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
          Aska::Semaphore::Wait() const(param_1 + 0xd8);
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
          if (cVar2 == '\0') goto code_r0x0204d1b0;
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
code_r0x0204d1b0:
  do {
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar3) {
      *piVar1 = *piVar1 + -1;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
code_r0x0204d1c0:
  DataMemoryBarrier(2,3);
  puVar8 = param_2 + -8;
  puVar6 = (ulong *)(param_3 - 0x40);
  if ((param_2 < puVar6) && (param_3 < (long)param_2 + (*puVar8 - 0x40))) {
    uVar4 = *puVar8 + ((long)param_2 - param_3);
    if (uVar4 == (uVar4 + 0xf & 0xfffffffffffffff0)) {
      uVar9 = param_2[-2];
      *(ulong *)(param_3 - 8) = param_2[-1];
      *(ulong *)(param_3 - 0x10) = uVar9;
      uVar9 = param_2[-4];
      *(ulong *)(param_3 - 0x18) = param_2[-3];
      *(ulong *)(param_3 - 0x20) = uVar9;
      uVar9 = param_2[-6];
      *(ulong *)(param_3 - 0x28) = param_2[-5];
      *(ulong *)(param_3 - 0x30) = uVar9;
      uVar9 = *puVar8;
      *(ulong *)(param_3 - 0x38) = param_2[-7];
      *puVar6 = uVar9;
      param_2[-8] = -((long)param_2 - param_3);
      *puVar6 = uVar4;
      uVar9 = param_2[-7];
      *(ulong *)(param_3 - 0x38) = uVar9;
      *(ulong **)(param_3 - 0x30) = puVar8;
      *(ulong **)(uVar9 + 0x10) = puVar6;
      param_2[-7] = (ulong)puVar6;
      DataMemoryBarrier(2,3);
      *(undefined4 *)(param_1 + 0x98) = 0xffffffff;
      DataMemoryBarrier(2,3);
      piVar7 = (int *)(param_1 + 0x9c);
      if (*piVar7 < 0x15) {
        return uVar4;
      }
      do {
        cVar2 = '\x01';
        bVar3 = (bool)ExclusiveMonitorPass(piVar7,0x10);
        if (bVar3) {
          *piVar7 = *piVar7 + -1;
          cVar2 = ExclusiveMonitorsStatus();
        }
      } while (cVar2 != '\0');
      uVar9 = Aska::Semaphore::IsReady() const(param_1 + 0xd8);
      if ((uVar9 & 1) == 0) {
        return uVar4;
      }
      Aska::Semaphore::Signal() const(param_1 + 0xd8);
      return uVar4;
    }
  }
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_1 + 0x98) = 0xffffffff;
  DataMemoryBarrier(2,3);
  piVar7 = (int *)(param_1 + 0x9c);
  if (0x14 < *piVar7) {
    do {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar7,0x10);
      if (bVar3) {
        *piVar7 = *piVar7 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    uVar4 = Aska::Semaphore::IsReady() const(param_1 + 0xd8);
    if ((uVar4 & 1) != 0) {
      Aska::Semaphore::Signal() const(param_1 + 0xd8);
    }
  }
  return 0;
}

// ==== Aska::MemoryManager::Move(void*, long, bool)
// vaddr 0x1f4d2ec | ghidra 0x204d2ec | size 364 | symbol _ZN4Aska13MemoryManager4MoveEPvlb | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska13MemoryManager4MoveEPvlb
               (undefined8 param_1,undefined8 param_2,long param_3,uint param_4)

{
  long *plVar1;
  long lVar2;
  undefined8 *puVar3;
  ulong uVar4;
  ulong uStack_38;
  
  plVar1 = (long *)Aska::IMemoryManager::GetAllocatedManager(void*, unsigned long*)(param_2,&uStack_38);
  if (plVar1 != (long *)0x0) {
    if (param_3 < 2) {
      if ((param_4 & 1) == 0) {
        lVar2 = Aska::MemoryManager::Malloc(unsigned long)(param_1,uStack_38);
      }
      else {
        lVar2 = Aska::MemoryManager::MallocHigh(unsigned long)(param_1);
      }
    }
    else if ((param_4 & 1) == 0) {
      lVar2 = Aska::MemoryManager::AlignedMalloc(unsigned long, long)(param_1,uStack_38,param_3);
    }
    else {
      lVar2 = Aska::MemoryManager::AlignedMallocHigh(unsigned long, long)(param_1,uStack_38,param_3);
    }
    if (lVar2 == 0) {
      return 0;
    }
    memcpy(lVar2,param_2,uStack_38);
    puVar3 = (undefined8 *)(**(code **)(*plVar1 + 0xc0))(plVar1,param_2);
    if ((puVar3 == (undefined8 *)0x0) ||
       (uVar4 = (**(code **)*puVar3)(puVar3,param_2,lVar2), (uVar4 & 1) != 0)) {
      Aska::IMemoryManager::Free(void const*)(param_2);
      return lVar2;
    }
    Aska::MemoryManager::LocalFree(Aska::_MemoryBlock*)(*(undefined8 *)(lVar2 + -0x18),lVar2 + -0x40);
  }
  return 0;
}

// ==== Aska::MemoryManager::LocalFree(void*)
// vaddr 0x1f4d458 | ghidra 0x204d458 | size 12 | symbol _ZN4Aska13MemoryManager9LocalFreeEPv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13MemoryManager9LocalFreeEPv(undefined8 param_1,long param_2)

{
  (*(code *)PTR__ZN4Aska13MemoryManager9LocalFreeEPNS_12_MemoryBlockE_02c924f8)
            (*(undefined8 *)(param_2 + -0x18),param_2 + -0x40);
  return;
}

// ==== Aska::MemoryManager::IsCreated() const
// vaddr 0x1f4d464 | ghidra 0x204d464 | size 356 | symbol _ZNK4Aska13MemoryManager9IsCreatedEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK4Aska13MemoryManager9IsCreatedEv(long param_1)

{
  int *piVar1;
  char cVar2;
  bool bVar3;
  ulong uVar4;
  int iVar5;
  long lVar6;
  int *piVar7;
  undefined4 uVar8;
  
  piVar7 = (int *)(param_1 + 0x98);
  iVar5 = 0;
code_r0x0204d47c:
  if (*piVar7 == -1) {
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar7,0x10);
    if (bVar3) {
      *piVar7 = 0;
      cVar2 = ExclusiveMonitorsStatus();
    }
    if (cVar2 == '\0') goto code_r0x0204d544;
    goto code_r0x0204d47c;
  }
  ClearExclusiveLocal();
  bVar3 = iVar5 < 0x1ff;
  iVar5 = iVar5 + 1;
  if (bVar3) goto code_r0x0204d47c;
  piVar1 = (int *)(param_1 + 0x9c);
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
        uVar4 = Aska::Semaphore::IsReady() const(param_1 + 0xd8);
        if ((uVar4 & 1) == 0) {
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
          Aska::Semaphore::Wait() const(param_1 + 0xd8);
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
          if (cVar2 == '\0') goto code_r0x0204d534;
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
code_r0x0204d534:
  do {
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar3) {
      *piVar1 = *piVar1 + -1;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
code_r0x0204d544:
  DataMemoryBarrier(2,3);
  lVar6 = param_1;
  do {
    if (*(long *)(lVar6 + 0x20) != 0) {
      uVar8 = 1;
      goto code_r0x0204d56c;
    }
    lVar6 = *(long *)(lVar6 + 0x48);
  } while (lVar6 != param_1);
  uVar8 = 0;
code_r0x0204d56c:
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_1 + 0x98) = 0xffffffff;
  DataMemoryBarrier(2,3);
  piVar7 = (int *)(param_1 + 0x9c);
  if (0x14 < *piVar7) {
    do {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar7,0x10);
      if (bVar3) {
        *piVar7 = *piVar7 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    uVar4 = Aska::Semaphore::IsReady() const(param_1 + 0xd8);
    if ((uVar4 & 1) != 0) {
      Aska::Semaphore::Signal() const(param_1 + 0xd8);
    }
  }
  return uVar8;
}

// ==== Aska::MemoryManager::IsPhysical() const
// vaddr 0x1f4d5c8 | ghidra 0x204d5c8 | size 8 | symbol _ZNK4Aska13MemoryManager10IsPhysicalEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska13MemoryManager10IsPhysicalEv(void)

{
  return 0;
}

// ==== Aska::MemoryManager::GetMemorySize(void const*)
// vaddr 0x1f4d5d0 | ghidra 0x204d5d0 | size 8 | symbol _ZN4Aska13MemoryManager13GetMemorySizeEPKv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska13MemoryManager13GetMemorySizeEPKv(undefined8 param_1,long param_2)

{
  return *(undefined8 *)(param_2 + -0x40);
}

// ==== Aska::MemoryManager::CalcFreeSize(long*, long*) const
// vaddr 0x1f4d5d8 | ghidra 0x204d5d8 | size 524 | symbol _ZNK4Aska13MemoryManager12CalcFreeSizeEPlS1_ | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZNK4Aska13MemoryManager12CalcFreeSizeEPlS1_(long param_1,long *param_2,long *param_3)

{
  int *piVar1;
  char cVar2;
  bool bVar3;
  ulong uVar4;
  int iVar5;
  long lVar6;
  int *piVar7;
  long lVar8;
  long lVar9;
  long lVar10;
  long lVar11;
  long lVar12;
  
  uVar4 = Aska::MemoryManager::IsCreated() const();
  if ((uVar4 & 1) == 0) {
    *param_2 = 0;
    *param_3 = 0;
    return 0;
  }
  lVar10 = 0;
  lVar11 = 0;
  lVar8 = 0;
  lVar12 = param_1;
code_r0x0204d6a8:
  piVar7 = (int *)(lVar12 + 0x98);
  iVar5 = 0;
code_r0x0204d6b0:
  do {
    if (*piVar7 == -1) goto code_r0x0204d6bc;
    ClearExclusiveLocal();
    bVar3 = iVar5 < 0x1ff;
    iVar5 = iVar5 + 1;
  } while (bVar3);
  piVar1 = (int *)(lVar12 + 0x9c);
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
        uVar4 = Aska::Semaphore::IsReady() const(lVar12 + 0xd8);
        if ((uVar4 & 1) == 0) {
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
          Aska::Semaphore::Wait() const(lVar12 + 0xd8);
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
          if (cVar2 == '\0') goto code_r0x0204d688;
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
code_r0x0204d688:
  do {
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar3) {
      *piVar1 = *piVar1 + -1;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
  DataMemoryBarrier(2,3);
  goto code_r0x0204d710;
code_r0x0204d6bc:
  cVar2 = '\x01';
  bVar3 = (bool)ExclusiveMonitorPass(piVar7,0x10);
  if (bVar3) {
    *piVar7 = 0;
    cVar2 = ExclusiveMonitorsStatus();
  }
  if (cVar2 == '\0') goto code_r0x0204d70c;
  goto code_r0x0204d6b0;
code_r0x0204d70c:
  DataMemoryBarrier(2,3);
code_r0x0204d710:
  uVar4 = 0;
  lVar9 = lVar8;
  do {
    lVar6 = *(long *)(lVar12 + 0x10) + uVar4 * 0x28;
    uVar4 = (ulong)*(uint *)(lVar6 + 4);
    lVar8 = *(long *)(lVar6 + 0x20);
    if (*(long *)(lVar6 + 0x20) <= lVar9) {
      lVar8 = lVar9;
    }
    lVar11 = lVar11 + *(long *)(lVar6 + 0x18) + 0x40;
    lVar9 = lVar8;
  } while (*(uint *)(lVar6 + 4) != 0);
  DataMemoryBarrier(2,3);
  *(undefined4 *)(lVar12 + 0x98) = 0xffffffff;
  DataMemoryBarrier(2,3);
  piVar7 = (int *)(lVar12 + 0x9c);
  lVar10 = (*(long *)(lVar12 + 0x10) - *(long *)(lVar12 + 0x20)) + lVar10;
  if (0x14 < *piVar7) {
    do {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar7,0x10);
      if (bVar3) {
        *piVar7 = *piVar7 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    uVar4 = Aska::Semaphore::IsReady() const(lVar12 + 0xd8);
    if ((uVar4 & 1) != 0) {
      Aska::Semaphore::Signal() const(lVar12 + 0xd8);
    }
  }
  lVar12 = *(long *)(lVar12 + 0x48);
  if (lVar12 == param_1) {
    if (param_2 != (long *)0x0) {
      *param_2 = lVar10;
    }
    if (param_3 != (long *)0x0) {
      *param_3 = lVar10 - lVar11;
    }
    return lVar8 - 0x40U & 0xfffffffffffffff0 &
           ((long)(lVar8 - 0x40U) >> 0x3f ^ 0xffffffffffffffffU);
  }
  goto code_r0x0204d6a8;
}

// ==== Aska::MemoryManager::CountFreeBlocks()
// vaddr 0x1f4d7e4 | ghidra 0x204d7e4 | size 424 | symbol _ZN4Aska13MemoryManager15CountFreeBlocksEv | lib libSOA-3.7.0.so | 2026-10-04
int _ZN4Aska13MemoryManager15CountFreeBlocksEv(long param_1)

{
  char *pcVar1;
  int *piVar2;
  ulong uVar3;
  uint uVar4;
  char cVar5;
  bool bVar6;
  int iVar7;
  int *piVar8;
  ulong uVar9;
  ulong uVar10;
  int iVar11;
  long lVar12;
  
  iVar11 = 0;
  lVar12 = param_1;
  do {
    piVar8 = (int *)(lVar12 + 0x98);
    iVar7 = 0;
code_r0x0204d814:
    if (*piVar8 == -1) {
      cVar5 = '\x01';
      bVar6 = (bool)ExclusiveMonitorPass(piVar8,0x10);
      if (bVar6) {
        *piVar8 = 0;
        cVar5 = ExclusiveMonitorsStatus();
      }
      if (cVar5 == '\0') goto code_r0x0204d8dc;
      goto code_r0x0204d814;
    }
    ClearExclusiveLocal();
    bVar6 = iVar7 < 0x1ff;
    iVar7 = iVar7 + 1;
    if (bVar6) goto code_r0x0204d814;
    piVar2 = (int *)(lVar12 + 0x9c);
    do {
      cVar5 = '\x01';
      bVar6 = (bool)ExclusiveMonitorPass(piVar2,0x10);
      if (bVar6) {
        *piVar2 = *piVar2 + 1;
        cVar5 = ExclusiveMonitorsStatus();
      }
    } while (cVar5 != '\0');
    do {
      if (*piVar8 != -1) {
        ClearExclusiveLocal();
        do {
          uVar9 = Aska::Semaphore::IsReady() const(lVar12 + 0xd8);
          if ((uVar9 & 1) == 0) {
            do {
              cVar5 = '\x01';
              bVar6 = (bool)ExclusiveMonitorPass(piVar2,0x10);
              if (bVar6) {
                *piVar2 = *piVar2 + -1;
                cVar5 = ExclusiveMonitorsStatus();
              }
            } while (cVar5 != '\0');
            Aska::Thread::Sleep(unsigned int)(1);
          }
          else {
            Aska::Semaphore::Wait() const(lVar12 + 0xd8);
          }
          do {
            cVar5 = '\x01';
            bVar6 = (bool)ExclusiveMonitorPass(piVar2,0x10);
            if (bVar6) {
              *piVar2 = *piVar2 + 1;
              cVar5 = ExclusiveMonitorsStatus();
            }
          } while (cVar5 != '\0');
          while (*piVar8 == -1) {
            cVar5 = '\x01';
            bVar6 = (bool)ExclusiveMonitorPass(piVar8,0x10);
            if (bVar6) {
              *piVar8 = 0;
              cVar5 = ExclusiveMonitorsStatus();
            }
            if (cVar5 == '\0') goto code_r0x0204d8cc;
          }
          ClearExclusiveLocal();
        } while( true );
      }
      cVar5 = '\x01';
      bVar6 = (bool)ExclusiveMonitorPass(piVar8,0x10);
      if (bVar6) {
        *piVar8 = 0;
        cVar5 = ExclusiveMonitorsStatus();
      }
    } while (cVar5 != '\0');
code_r0x0204d8cc:
    do {
      cVar5 = '\x01';
      bVar6 = (bool)ExclusiveMonitorPass(piVar2,0x10);
      if (bVar6) {
        *piVar2 = *piVar2 + -1;
        cVar5 = ExclusiveMonitorsStatus();
      }
    } while (cVar5 != '\0');
code_r0x0204d8dc:
    DataMemoryBarrier(2,3);
    uVar9 = 0;
    do {
      uVar3 = *(long *)(lVar12 + 0x20) + uVar9 * 0x10000;
      uVar10 = *(ulong *)(uVar3 + 8);
      while (uVar3 < uVar10) {
        pcVar1 = (char *)(uVar10 + 0x31);
        uVar10 = *(ulong *)(uVar10 + 8);
        if (*pcVar1 != '\x01') {
          iVar11 = iVar11 + 1;
        }
      }
      uVar4 = *(uint *)(*(long *)(lVar12 + 0x10) + uVar9 * 0x28 + 4);
      uVar9 = (ulong)uVar4;
    } while (uVar4 != 0);
    DataMemoryBarrier(2,3);
    *(undefined4 *)(lVar12 + 0x98) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar8 = (int *)(lVar12 + 0x9c);
    if (0x14 < *piVar8) {
      do {
        cVar5 = '\x01';
        bVar6 = (bool)ExclusiveMonitorPass(piVar8,0x10);
        if (bVar6) {
          *piVar8 = *piVar8 + -1;
          cVar5 = ExclusiveMonitorsStatus();
        }
      } while (cVar5 != '\0');
      uVar9 = Aska::Semaphore::IsReady() const(lVar12 + 0xd8);
      if ((uVar9 & 1) != 0) {
        Aska::Semaphore::Signal() const(lVar12 + 0xd8);
      }
    }
    lVar12 = *(long *)(lVar12 + 0x48);
    if (lVar12 == param_1) {
      return iVar11;
    }
  } while( true );
}

// ==== Aska::MemoryManager::IsEmpty(bool) const
// vaddr 0x1f4d98c | ghidra 0x204d98c | size 816 | symbol _ZNK4Aska13MemoryManager7IsEmptyEb | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska13MemoryManager7IsEmptyEb(long param_1,uint param_2)

{
  long *plVar1;
  int *piVar2;
  uint uVar3;
  char cVar4;
  bool bVar5;
  ulong uVar6;
  int iVar7;
  int *piVar8;
  long lVar9;
  
  uVar6 = Aska::MemoryManager::IsCreated() const();
  if ((uVar6 & 1) == 0) {
    return 1;
  }
  lVar9 = param_1;
  if ((param_2 & 1) == 0) {
    do {
      piVar8 = (int *)(lVar9 + 0x98);
      iVar7 = 0;
code_r0x0204da20:
      if (*piVar8 == -1) {
        cVar4 = '\x01';
        bVar5 = (bool)ExclusiveMonitorPass(piVar8,0x10);
        if (bVar5) {
          *piVar8 = 0;
          cVar4 = ExclusiveMonitorsStatus();
        }
        if (cVar4 == '\0') goto code_r0x0204dae8;
        goto code_r0x0204da20;
      }
      ClearExclusiveLocal();
      bVar5 = iVar7 < 0x1ff;
      iVar7 = iVar7 + 1;
      if (bVar5) goto code_r0x0204da20;
      piVar2 = (int *)(lVar9 + 0x9c);
      do {
        cVar4 = '\x01';
        bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
        if (bVar5) {
          *piVar2 = *piVar2 + 1;
          cVar4 = ExclusiveMonitorsStatus();
        }
      } while (cVar4 != '\0');
      do {
        if (*piVar8 != -1) {
          ClearExclusiveLocal();
          do {
            uVar6 = Aska::Semaphore::IsReady() const(lVar9 + 0xd8);
            if ((uVar6 & 1) == 0) {
              do {
                cVar4 = '\x01';
                bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
                if (bVar5) {
                  *piVar2 = *piVar2 + -1;
                  cVar4 = ExclusiveMonitorsStatus();
                }
              } while (cVar4 != '\0');
              Aska::Thread::Sleep(unsigned int)(1);
            }
            else {
              Aska::Semaphore::Wait() const(lVar9 + 0xd8);
            }
            do {
              cVar4 = '\x01';
              bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
              if (bVar5) {
                *piVar2 = *piVar2 + 1;
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
              if (cVar4 == '\0') goto code_r0x0204dad8;
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
code_r0x0204dad8:
      do {
        cVar4 = '\x01';
        bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
        if (bVar5) {
          *piVar2 = *piVar2 + -1;
          cVar4 = ExclusiveMonitorsStatus();
        }
      } while (cVar4 != '\0');
code_r0x0204dae8:
      DataMemoryBarrier(2,3);
      uVar6 = 0;
      do {
        if (*(long *)(*(long *)(lVar9 + 0x10) + uVar6 * 0x28 + 0x10) != 0) goto code_r0x0204dc54;
        uVar3 = *(uint *)(*(long *)(lVar9 + 0x10) + uVar6 * 0x28 + 4);
        uVar6 = (ulong)uVar3;
      } while (uVar3 != 0);
      DataMemoryBarrier(2,3);
      *(undefined4 *)(lVar9 + 0x98) = 0xffffffff;
      DataMemoryBarrier(2,3);
      piVar8 = (int *)(lVar9 + 0x9c);
      if (0x14 < *piVar8) {
        do {
          cVar4 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(piVar8,0x10);
          if (bVar5) {
            *piVar8 = *piVar8 + -1;
            cVar4 = ExclusiveMonitorsStatus();
          }
        } while (cVar4 != '\0');
        uVar6 = Aska::Semaphore::IsReady() const(lVar9 + 0xd8);
        if ((uVar6 & 1) != 0) {
          Aska::Semaphore::Signal() const(lVar9 + 0xd8);
        }
      }
      plVar1 = (long *)(lVar9 + 0x48);
      lVar9 = *plVar1;
      if (*plVar1 == param_1) {
        return 1;
      }
    } while( true );
  }
  piVar8 = (int *)(param_1 + 0x98);
  iVar7 = 0;
  do {
    while (*piVar8 == -1) {
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar8,0x10);
      if (bVar5) {
        *piVar8 = 0;
        cVar4 = ExclusiveMonitorsStatus();
      }
      if (cVar4 == '\0') goto code_r0x0204dbd8;
    }
    ClearExclusiveLocal();
    bVar5 = iVar7 < 0x1ff;
    iVar7 = iVar7 + 1;
  } while (bVar5);
  piVar2 = (int *)(param_1 + 0x9c);
  do {
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar5) {
      *piVar2 = *piVar2 + 1;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
  do {
    if (*piVar8 != -1) {
      ClearExclusiveLocal();
      do {
        uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0xd8);
        if ((uVar6 & 1) == 0) {
          do {
            cVar4 = '\x01';
            bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
            if (bVar5) {
              *piVar2 = *piVar2 + -1;
              cVar4 = ExclusiveMonitorsStatus();
            }
          } while (cVar4 != '\0');
          Aska::Thread::Sleep(unsigned int)(1);
        }
        else {
          Aska::Semaphore::Wait() const(param_1 + 0xd8);
        }
        do {
          cVar4 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
          if (bVar5) {
            *piVar2 = *piVar2 + 1;
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
          if (cVar4 == '\0') goto code_r0x0204dbc8;
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
code_r0x0204dbc8:
  do {
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar5) {
      *piVar2 = *piVar2 + -1;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
code_r0x0204dbd8:
  DataMemoryBarrier(2,3);
  uVar6 = 0;
  while (*(long *)(*(long *)(param_1 + 0x10) + uVar6 * 0x28 + 0x10) == 0) {
    uVar3 = *(uint *)(*(long *)(param_1 + 0x10) + uVar6 * 0x28 + 4);
    uVar6 = (ulong)uVar3;
    if (uVar3 == 0) {
      DataMemoryBarrier(2,3);
      *(undefined4 *)(param_1 + 0x98) = 0xffffffff;
      DataMemoryBarrier(2,3);
      piVar8 = (int *)(param_1 + 0x9c);
      if (*piVar8 < 0x15) {
        return 1;
      }
      do {
        cVar4 = '\x01';
        bVar5 = (bool)ExclusiveMonitorPass(piVar8,0x10);
        if (bVar5) {
          *piVar8 = *piVar8 + -1;
          cVar4 = ExclusiveMonitorsStatus();
        }
      } while (cVar4 != '\0');
      uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0xd8);
      if ((uVar6 & 1) == 0) {
        return 1;
      }
      Aska::Semaphore::Signal() const(param_1 + 0xd8);
      return 1;
    }
  }
code_r0x0204dc54:
  DataMemoryBarrier(2,3);
  *piVar8 = -1;
  DataMemoryBarrier(2,3);
  piVar8 = (int *)(lVar9 + 0x9c);
  if (0x14 < *piVar8) {
    do {
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar8,0x10);
      if (bVar5) {
        *piVar8 = *piVar8 + -1;
        cVar4 = ExclusiveMonitorsStatus();
      }
    } while (cVar4 != '\0');
    uVar6 = Aska::Semaphore::IsReady() const(lVar9 + 0xd8);
    if ((uVar6 & 1) != 0) {
      Aska::Semaphore::Signal() const(lVar9 + 0xd8);
    }
  }
  return 0;
}

// ==== Aska::MemoryManager::CalcFreeSize(bool)
// vaddr 0x1f4dcbc | ghidra 0x204dcbc | size 764 | symbol _ZN4Aska13MemoryManager12CalcFreeSizeEb | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska13MemoryManager12CalcFreeSizeEb(long param_1,uint param_2)

{
  int *piVar1;
  uint uVar2;
  char cVar3;
  bool bVar4;
  ulong uVar5;
  int iVar6;
  int *piVar7;
  long lVar8;
  long lVar9;
  long lVar10;
  
  uVar5 = Aska::MemoryManager::IsCreated() const();
  if ((uVar5 & 1) == 0) {
    return 0;
  }
  if ((param_2 & 1) == 0) {
    lVar10 = 0;
    lVar9 = param_1;
    do {
      piVar7 = (int *)(lVar9 + 0x98);
      iVar6 = 0;
code_r0x0204dd58:
      if (*piVar7 == -1) {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar7,0x10);
        if (bVar4) {
          *piVar7 = 0;
          cVar3 = ExclusiveMonitorsStatus();
        }
        if (cVar3 == '\0') goto code_r0x0204de20;
        goto code_r0x0204dd58;
      }
      ClearExclusiveLocal();
      bVar4 = iVar6 < 0x1ff;
      iVar6 = iVar6 + 1;
      if (bVar4) goto code_r0x0204dd58;
      piVar1 = (int *)(lVar9 + 0x9c);
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
        if (bVar4) {
          *piVar1 = *piVar1 + 1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      do {
        if (*piVar7 != -1) {
          ClearExclusiveLocal();
          do {
            uVar5 = Aska::Semaphore::IsReady() const(lVar9 + 0xd8);
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
              Aska::Semaphore::Wait() const(lVar9 + 0xd8);
            }
            do {
              cVar3 = '\x01';
              bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
              if (bVar4) {
                *piVar1 = *piVar1 + 1;
                cVar3 = ExclusiveMonitorsStatus();
              }
            } while (cVar3 != '\0');
            while (*piVar7 == -1) {
              cVar3 = '\x01';
              bVar4 = (bool)ExclusiveMonitorPass(piVar7,0x10);
              if (bVar4) {
                *piVar7 = 0;
                cVar3 = ExclusiveMonitorsStatus();
              }
              if (cVar3 == '\0') goto code_r0x0204de10;
            }
            ClearExclusiveLocal();
          } while( true );
        }
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar7,0x10);
        if (bVar4) {
          *piVar7 = 0;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
code_r0x0204de10:
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
        if (bVar4) {
          *piVar1 = *piVar1 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
code_r0x0204de20:
      DataMemoryBarrier(2,3);
      uVar5 = 0;
      Hint_Prefetch(*(undefined8 *)(lVar9 + 0x48),0,2,0);
      do {
        lVar8 = *(long *)(lVar9 + 0x10) + uVar5 * 0x28;
        uVar2 = *(uint *)(lVar8 + 4);
        uVar5 = (ulong)uVar2;
        lVar10 = lVar10 + *(long *)(lVar8 + 0x18) + 0x40;
      } while (uVar2 != 0);
      DataMemoryBarrier(2,3);
      *(undefined4 *)(lVar9 + 0x98) = 0xffffffff;
      DataMemoryBarrier(2,3);
      piVar7 = (int *)(lVar9 + 0x9c);
      if (0x14 < *piVar7) {
        do {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar7,0x10);
          if (bVar4) {
            *piVar7 = *piVar7 + -1;
            cVar3 = ExclusiveMonitorsStatus();
          }
        } while (cVar3 != '\0');
        uVar5 = Aska::Semaphore::IsReady() const(lVar9 + 0xd8);
        if ((uVar5 & 1) != 0) {
          Aska::Semaphore::Signal() const(lVar9 + 0xd8);
        }
      }
      lVar9 = *(long *)(lVar9 + 0x48);
      if (lVar9 == param_1) {
        return lVar10;
      }
    } while( true );
  }
  piVar7 = (int *)(param_1 + 0x98);
  iVar6 = 0;
  do {
    while (*piVar7 == -1) {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar7,0x10);
      if (bVar4) {
        *piVar7 = 0;
        cVar3 = ExclusiveMonitorsStatus();
      }
      if (cVar3 == '\0') goto code_r0x0204df18;
    }
    ClearExclusiveLocal();
    bVar4 = iVar6 < 0x1ff;
    iVar6 = iVar6 + 1;
  } while (bVar4);
  piVar1 = (int *)(param_1 + 0x9c);
  do {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar4) {
      *piVar1 = *piVar1 + 1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
  do {
    if (*piVar7 != -1) {
      ClearExclusiveLocal();
      do {
        uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0xd8);
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
          Aska::Semaphore::Wait() const(param_1 + 0xd8);
        }
        do {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar4) {
            *piVar1 = *piVar1 + 1;
            cVar3 = ExclusiveMonitorsStatus();
          }
        } while (cVar3 != '\0');
        while (*piVar7 == -1) {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar7,0x10);
          if (bVar4) {
            *piVar7 = 0;
            cVar3 = ExclusiveMonitorsStatus();
          }
          if (cVar3 == '\0') goto code_r0x0204df08;
        }
        ClearExclusiveLocal();
      } while( true );
    }
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar7,0x10);
    if (bVar4) {
      *piVar7 = 0;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
code_r0x0204df08:
  do {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar4) {
      *piVar1 = *piVar1 + -1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
code_r0x0204df18:
  DataMemoryBarrier(2,3);
  lVar10 = 0;
  uVar5 = 0;
  Hint_Prefetch(*(undefined8 *)(param_1 + 0x48),0,2,0);
  do {
    lVar9 = *(long *)(param_1 + 0x10) + uVar5 * 0x28;
    uVar2 = *(uint *)(lVar9 + 4);
    uVar5 = (ulong)uVar2;
    lVar10 = lVar10 + *(long *)(lVar9 + 0x18) + 0x40;
  } while (uVar2 != 0);
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_1 + 0x98) = 0xffffffff;
  DataMemoryBarrier(2,3);
  piVar7 = (int *)(param_1 + 0x9c);
  if (*piVar7 < 0x15) {
    return lVar10;
  }
  do {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar7,0x10);
    if (bVar4) {
      *piVar7 = *piVar7 + -1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
  uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0xd8);
  if ((uVar5 & 1) == 0) {
    return lVar10;
  }
  Aska::Semaphore::Signal() const(param_1 + 0xd8);
  return lVar10;
}

// ==== Aska::MemoryManager::PrintMemoryChain()
// vaddr 0x1f4dfb8 | ghidra 0x204dfb8 | size 4 | symbol _ZN4Aska13MemoryManager16PrintMemoryChainEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13MemoryManager16PrintMemoryChainEv(void)

{
  return;
}

// ==== Aska::MemoryManager::PrintMemoryChain(char const*)
// vaddr 0x1f4dfbc | ghidra 0x204dfbc | size 4 | symbol _ZN4Aska13MemoryManager16PrintMemoryChainEPKc | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13MemoryManager16PrintMemoryChainEPKc(void)

{
  return;
}

// ==== Aska::MemoryManager::SearchNextBlock(Aska::MemoryManager::_Srbk**, Aska::_MemoryBlock**, bool)
// vaddr 0x1f4dfc0 | ghidra 0x204dfc0 | size 600 | symbol _ZN4Aska13MemoryManager15SearchNextBlockEPPNS0_5_SrbkEPPNS_12_MemoryBlockEb | lib libSOA-3.7.0.so | 2026-10-04
bool _ZN4Aska13MemoryManager15SearchNextBlockEPPNS0_5_SrbkEPPNS_12_MemoryBlockEb
               (long param_1,long *param_2,long *param_3,uint param_4)

{
  int *piVar1;
  long lVar2;
  long lVar3;
  uint uVar4;
  char cVar5;
  bool bVar6;
  bool bVar7;
  long lVar8;
  ulong uVar9;
  int iVar10;
  long lVar11;
  int *piVar12;
  long lVar13;
  long lVar14;
  uint uVar15;
  
  piVar12 = (int *)(param_1 + 0x98);
  iVar10 = 0;
  do {
    while (*piVar12 == -1) {
      cVar5 = '\x01';
      bVar6 = (bool)ExclusiveMonitorPass(piVar12,0x10);
      if (bVar6) {
        *piVar12 = 0;
        cVar5 = ExclusiveMonitorsStatus();
      }
      if (cVar5 == '\0') goto code_r0x0204e0b0;
    }
    ClearExclusiveLocal();
    bVar6 = iVar10 < 0x1ff;
    iVar10 = iVar10 + 1;
  } while (bVar6);
  piVar1 = (int *)(param_1 + 0x9c);
  do {
    cVar5 = '\x01';
    bVar6 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar6) {
      *piVar1 = *piVar1 + 1;
      cVar5 = ExclusiveMonitorsStatus();
    }
  } while (cVar5 != '\0');
  do {
    if (*piVar12 != -1) {
      ClearExclusiveLocal();
      do {
        uVar9 = Aska::Semaphore::IsReady() const(param_1 + 0xd8);
        if ((uVar9 & 1) == 0) {
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
          Aska::Semaphore::Wait() const(param_1 + 0xd8);
        }
        do {
          cVar5 = '\x01';
          bVar6 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar6) {
            *piVar1 = *piVar1 + 1;
            cVar5 = ExclusiveMonitorsStatus();
          }
        } while (cVar5 != '\0');
        while (*piVar12 == -1) {
          cVar5 = '\x01';
          bVar6 = (bool)ExclusiveMonitorPass(piVar12,0x10);
          if (bVar6) {
            *piVar12 = 0;
            cVar5 = ExclusiveMonitorsStatus();
          }
          if (cVar5 == '\0') goto code_r0x0204e0a0;
        }
        ClearExclusiveLocal();
      } while( true );
    }
    cVar5 = '\x01';
    bVar6 = (bool)ExclusiveMonitorPass(piVar12,0x10);
    if (bVar6) {
      *piVar12 = 0;
      cVar5 = ExclusiveMonitorsStatus();
    }
  } while (cVar5 != '\0');
code_r0x0204e0a0:
  do {
    cVar5 = '\x01';
    bVar6 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar6) {
      *piVar1 = *piVar1 + -1;
      cVar5 = ExclusiveMonitorsStatus();
    }
  } while (cVar5 != '\0');
code_r0x0204e0b0:
  DataMemoryBarrier(2,3);
  lVar13 = *param_2;
  lVar11 = *param_3;
  lVar3 = *(long *)(param_1 + 0x10);
  if (lVar13 != 0) {
    lVar3 = lVar13;
  }
  uVar4 = *(uint *)(lVar3 + 4);
  uVar15 = *(uint *)(*(long *)(param_1 + 0x10) + (ulong)uVar4 * 0x28 + 8);
  lVar14 = 0;
  if (lVar13 != 0) {
    lVar14 = lVar11;
  }
  if ((param_4 & 1) == 0) {
    do {
      lVar2 = *(long *)(param_1 + 0x20) + (ulong)uVar15 * 0x10000;
      if (lVar14 == 0) {
        lVar14 = *(long *)(lVar2 + 8);
      }
      if (lVar14 != lVar2) {
code_r0x0204e19c:
        *param_2 = lVar3;
        *param_3 = lVar14;
        DataMemoryBarrier(2,3);
        *(undefined4 *)(param_1 + 0x98) = 0xffffffff;
        DataMemoryBarrier(2,3);
        piVar12 = (int *)(param_1 + 0x9c);
        bVar6 = lVar11 != lVar14 || lVar13 != lVar3;
        if (*piVar12 < 0x15) {
          return bVar6;
        }
        do {
          cVar5 = '\x01';
          bVar7 = (bool)ExclusiveMonitorPass(piVar12,0x10);
          if (bVar7) {
            *piVar12 = *piVar12 + -1;
            cVar5 = ExclusiveMonitorsStatus();
          }
        } while (cVar5 != '\0');
        uVar9 = Aska::Semaphore::IsReady() const(param_1 + 0xd8);
        if ((uVar9 & 1) == 0) {
          return bVar6;
        }
        Aska::Semaphore::Signal() const(param_1 + 0xd8);
        return bVar6;
      }
      lVar14 = 0;
      uVar15 = uVar4;
    } while (uVar4 != 0);
  }
  else {
    do {
      lVar2 = *(long *)(param_1 + 0x20) + (ulong)uVar15 * 0x10000;
      lVar8 = lVar2;
      if (lVar14 != 0) goto code_r0x0204e0fc;
      while( true ) {
        lVar14 = *(long *)(lVar8 + 8);
code_r0x0204e0fc:
        if (lVar14 == lVar2) break;
        lVar8 = lVar14;
        if (*(char *)(lVar14 + 0x31) != '\x01') goto code_r0x0204e19c;
      }
      lVar14 = 0;
      uVar15 = uVar4;
    } while (uVar4 != 0);
  }
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_1 + 0x98) = 0xffffffff;
  DataMemoryBarrier(2,3);
  piVar12 = (int *)(param_1 + 0x9c);
  if (0x14 < *piVar12) {
    do {
      cVar5 = '\x01';
      bVar6 = (bool)ExclusiveMonitorPass(piVar12,0x10);
      if (bVar6) {
        *piVar12 = *piVar12 + -1;
        cVar5 = ExclusiveMonitorsStatus();
      }
    } while (cVar5 != '\0');
    uVar9 = Aska::Semaphore::IsReady() const(param_1 + 0xd8);
    if ((uVar9 & 1) != 0) {
      Aska::Semaphore::Signal() const(param_1 + 0xd8);
    }
  }
  return false;
}

// ==== Aska::MemoryManager::Add(int)
// vaddr 0x1f4e218 | ghidra 0x204e218 | size 176 | symbol _ZN4Aska13MemoryManager3AddEi | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska13MemoryManager3AddEi(long param_1,int param_2)

{
  long *plVar1;
  ulong uVar2;
  undefined8 uVar3;
  long lVar4;
  
  plVar1 = (long *)operator new(unsigned long, std::nothrow_t const&)(0xf0,PTR__ZSt7nothrow_02cb9a80);
  uVar3 = 0;
  if (plVar1 != (long *)0x0) {
    *(undefined1 *)(plVar1 + 1) = 0;
    *plVar1 = (long)(PTR__ZTVN4Aska13MemoryManagerE_02cb9280 + 0x10);
    Aska::FastCriticalSection::FastCriticalSection()(plVar1 + 0xc);
    plVar1[5] = 0;
    plVar1[6] = 0;
    plVar1[4] = 0;
    plVar1[8] = (long)plVar1;
    plVar1[9] = (long)plVar1;
    plVar1[10] = (long)plVar1;
    plVar1[0xb] = 0;
    uVar2 = Aska::MemoryManager::InitHeap(unsigned long)(plVar1,(long)param_2);
    if ((uVar2 & 1) == 0) {
      (**(code **)(*plVar1 + 0xd0))(plVar1);
      uVar3 = 0;
    }
    else {
      lVar4 = *(long *)(param_1 + 0x40);
      uVar3 = 1;
      plVar1[8] = lVar4;
      plVar1[9] = lVar4;
      plVar1[10] = *(long *)(lVar4 + 0x50);
      *(long **)(*(long *)(lVar4 + 0x50) + 0x48) = plVar1;
      *(long **)(*(long *)(param_1 + 0x40) + 0x50) = plVar1;
      plVar1[0xb] = param_1;
    }
  }
  return uVar3;
}

// ==== Aska::MemoryManager::Add(void*, int)
// vaddr 0x1f4e2c8 | ghidra 0x204e2c8 | size 188 | symbol _ZN4Aska13MemoryManager3AddEPvi | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska13MemoryManager3AddEPvi(long param_1,undefined8 param_2,int param_3)

{
  long *plVar1;
  ulong uVar2;
  undefined8 uVar3;
  long lVar4;
  
  plVar1 = (long *)operator new(unsigned long, std::nothrow_t const&)(0xf0,PTR__ZSt7nothrow_02cb9a80);
  uVar3 = 0;
  if (plVar1 != (long *)0x0) {
    *(undefined1 *)(plVar1 + 1) = 0;
    *plVar1 = (long)(PTR__ZTVN4Aska13MemoryManagerE_02cb9280 + 0x10);
    Aska::FastCriticalSection::FastCriticalSection()(plVar1 + 0xc);
    plVar1[5] = 0;
    plVar1[6] = 0;
    plVar1[4] = 0;
    plVar1[8] = (long)plVar1;
    plVar1[9] = (long)plVar1;
    plVar1[10] = (long)plVar1;
    plVar1[0xb] = 0;
    uVar2 = Aska::MemoryManager::InitHeap(unsigned char*, unsigned long)(plVar1,param_2,(long)param_3);
    if ((uVar2 & 1) == 0) {
      (**(code **)(*plVar1 + 0xd0))(plVar1);
      uVar3 = 0;
    }
    else {
      lVar4 = *(long *)(param_1 + 0x40);
      uVar3 = 1;
      plVar1[8] = lVar4;
      plVar1[9] = lVar4;
      plVar1[10] = *(long *)(lVar4 + 0x50);
      *(long **)(*(long *)(lVar4 + 0x50) + 0x48) = plVar1;
      *(long **)(*(long *)(param_1 + 0x40) + 0x50) = plVar1;
    }
  }
  return uVar3;
}

// ==== Aska::MemoryManager::Add(Aska::MemoryManager*)
// vaddr 0x1f4e384 | ghidra 0x204e384 | size 92 | symbol _ZN4Aska13MemoryManager3AddEPS0_ | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska13MemoryManager3AddEPS0_(long param_1,long param_2)

{
  long lVar1;
  long lVar2;
  
  if (param_2 != 0) {
    lVar1 = *(long *)(param_2 + 0x40);
    lVar2 = param_2;
    do {
      *(undefined8 *)(lVar2 + 0x40) = *(undefined8 *)(param_1 + 0x40);
      lVar2 = *(long *)(lVar2 + 0x48);
    } while (lVar2 != param_2);
    *(undefined8 *)(*(long *)(lVar1 + 0x50) + 0x48) = *(undefined8 *)(param_1 + 0x40);
    *(undefined8 *)(lVar1 + 0x50) = *(undefined8 *)(*(long *)(param_1 + 0x40) + 0x50);
    *(long *)(*(long *)(*(long *)(param_1 + 0x40) + 0x50) + 0x48) = lVar1;
    *(long *)(*(long *)(param_1 + 0x40) + 0x50) = lVar1;
    return 1;
  }
  return 0;
}

// ==== Aska::MemoryManager::CreateDebugMemoryMap(int, int, bool)
// vaddr 0x1f4e3e0 | ghidra 0x204e3e0 | size 4 | symbol _ZN4Aska13MemoryManager20CreateDebugMemoryMapEiib | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13MemoryManager20CreateDebugMemoryMapEiib(void)

{
  return;
}

// ==== Aska::MemoryManager::UpdateDebugMemoryMap()
// vaddr 0x1f4e3e4 | ghidra 0x204e3e4 | size 4 | symbol _ZN4Aska13MemoryManager20UpdateDebugMemoryMapEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13MemoryManager20UpdateDebugMemoryMapEv(void)

{
  return;
}

// ==== Aska::MemoryManager::GetDebugMemoryMap(Aska::Text*, float, float, unsigned int, float, float)
// vaddr 0x1f4e3e8 | ghidra 0x204e3e8 | size 4 | symbol _ZN4Aska13MemoryManager17GetDebugMemoryMapEPNS_4TextEffjff | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13MemoryManager17GetDebugMemoryMapEPNS_4TextEffjff(void)

{
  return;
}

// ==== Aska::MemoryManager::SetSwapDebugMemoryMap(bool)
// vaddr 0x1f4e3ec | ghidra 0x204e3ec | size 4 | symbol _ZN4Aska13MemoryManager21SetSwapDebugMemoryMapEb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13MemoryManager21SetSwapDebugMemoryMapEb(void)

{
  return;
}

// ==== Aska::MemoryManager::VirtualRegisterNotify(void*, Aska::IMemoryNotify*)
// vaddr 0x1f4e3f0 | ghidra 0x204e3f0 | size 368 | symbol _ZN4Aska13MemoryManager21VirtualRegisterNotifyEPvPNS_13IMemoryNotifyE | lib libSOA-3.7.0.so | 2026-10-04
undefined4
_ZN4Aska13MemoryManager21VirtualRegisterNotifyEPvPNS_13IMemoryNotifyE
          (long param_1,long param_2,long param_3)

{
  int *piVar1;
  char cVar2;
  bool bVar3;
  ulong uVar4;
  int iVar5;
  int *piVar6;
  undefined4 uVar7;
  
  piVar6 = (int *)(param_1 + 0x98);
  iVar5 = 0;
  do {
    while (*piVar6 == -1) {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar6,0x10);
      if (bVar3) {
        *piVar6 = 0;
        cVar2 = ExclusiveMonitorsStatus();
      }
      if (cVar2 == '\0') goto code_r0x0204e4dc;
    }
    ClearExclusiveLocal();
    bVar3 = iVar5 < 0x1ff;
    iVar5 = iVar5 + 1;
  } while (bVar3);
  piVar1 = (int *)(param_1 + 0x9c);
  do {
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar3) {
      *piVar1 = *piVar1 + 1;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
  do {
    if (*piVar6 != -1) {
      ClearExclusiveLocal();
      do {
        uVar4 = Aska::Semaphore::IsReady() const(param_1 + 0xd8);
        if ((uVar4 & 1) == 0) {
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
          Aska::Semaphore::Wait() const(param_1 + 0xd8);
        }
        do {
          cVar2 = '\x01';
          bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar3) {
            *piVar1 = *piVar1 + 1;
            cVar2 = ExclusiveMonitorsStatus();
          }
        } while (cVar2 != '\0');
        while (*piVar6 == -1) {
          cVar2 = '\x01';
          bVar3 = (bool)ExclusiveMonitorPass(piVar6,0x10);
          if (bVar3) {
            *piVar6 = 0;
            cVar2 = ExclusiveMonitorsStatus();
          }
          if (cVar2 == '\0') goto code_r0x0204e4cc;
        }
        ClearExclusiveLocal();
      } while( true );
    }
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar6,0x10);
    if (bVar3) {
      *piVar6 = 0;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
code_r0x0204e4cc:
  do {
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar3) {
      *piVar1 = *piVar1 + -1;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
code_r0x0204e4dc:
  DataMemoryBarrier(2,3);
  if ((*(long *)(param_2 + -8) == 0) || (*(long *)(param_2 + -8) == param_3)) {
    *(long *)(param_2 + -8) = param_3;
    uVar7 = 1;
  }
  else {
    uVar7 = 0;
  }
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_1 + 0x98) = 0xffffffff;
  DataMemoryBarrier(2,3);
  piVar6 = (int *)(param_1 + 0x9c);
  if (0x14 < *piVar6) {
    do {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar6,0x10);
      if (bVar3) {
        *piVar6 = *piVar6 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    uVar4 = Aska::Semaphore::IsReady() const(param_1 + 0xd8);
    if ((uVar4 & 1) != 0) {
      Aska::Semaphore::Signal() const(param_1 + 0xd8);
    }
  }
  return uVar7;
}

// ==== Aska::MemoryManager::VirtualRemoveNotify(void*, Aska::IMemoryNotify*)
// vaddr 0x1f4e560 | ghidra 0x204e560 | size 368 | symbol _ZN4Aska13MemoryManager19VirtualRemoveNotifyEPvPNS_13IMemoryNotifyE | lib libSOA-3.7.0.so | 2026-10-04
undefined4
_ZN4Aska13MemoryManager19VirtualRemoveNotifyEPvPNS_13IMemoryNotifyE
          (long param_1,long param_2,long param_3)

{
  int *piVar1;
  char cVar2;
  bool bVar3;
  ulong uVar4;
  int iVar5;
  int *piVar6;
  undefined4 uVar7;
  
  piVar6 = (int *)(param_1 + 0x98);
  iVar5 = 0;
  do {
    while (*piVar6 == -1) {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar6,0x10);
      if (bVar3) {
        *piVar6 = 0;
        cVar2 = ExclusiveMonitorsStatus();
      }
      if (cVar2 == '\0') goto code_r0x0204e64c;
    }
    ClearExclusiveLocal();
    bVar3 = iVar5 < 0x1ff;
    iVar5 = iVar5 + 1;
  } while (bVar3);
  piVar1 = (int *)(param_1 + 0x9c);
  do {
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar3) {
      *piVar1 = *piVar1 + 1;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
  do {
    if (*piVar6 != -1) {
      ClearExclusiveLocal();
      do {
        uVar4 = Aska::Semaphore::IsReady() const(param_1 + 0xd8);
        if ((uVar4 & 1) == 0) {
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
          Aska::Semaphore::Wait() const(param_1 + 0xd8);
        }
        do {
          cVar2 = '\x01';
          bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar3) {
            *piVar1 = *piVar1 + 1;
            cVar2 = ExclusiveMonitorsStatus();
          }
        } while (cVar2 != '\0');
        while (*piVar6 == -1) {
          cVar2 = '\x01';
          bVar3 = (bool)ExclusiveMonitorPass(piVar6,0x10);
          if (bVar3) {
            *piVar6 = 0;
            cVar2 = ExclusiveMonitorsStatus();
          }
          if (cVar2 == '\0') goto code_r0x0204e63c;
        }
        ClearExclusiveLocal();
      } while( true );
    }
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar6,0x10);
    if (bVar3) {
      *piVar6 = 0;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
code_r0x0204e63c:
  do {
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar3) {
      *piVar1 = *piVar1 + -1;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
code_r0x0204e64c:
  DataMemoryBarrier(2,3);
  if ((param_3 == 0) || (*(long *)(param_2 + -8) == param_3)) {
    *(undefined8 *)(param_2 + -8) = 0;
    uVar7 = 1;
  }
  else {
    uVar7 = 0;
  }
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_1 + 0x98) = 0xffffffff;
  DataMemoryBarrier(2,3);
  piVar6 = (int *)(param_1 + 0x9c);
  if (0x14 < *piVar6) {
    do {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar6,0x10);
      if (bVar3) {
        *piVar6 = *piVar6 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    uVar4 = Aska::Semaphore::IsReady() const(param_1 + 0xd8);
    if ((uVar4 & 1) != 0) {
      Aska::Semaphore::Signal() const(param_1 + 0xd8);
    }
  }
  return uVar7;
}

// ==== Aska::MemoryManager::VirtualIsRegisteredNotify(void*, Aska::IMemoryNotify*)
// vaddr 0x1f4e6d0 | ghidra 0x204e6d0 | size 368 | symbol _ZN4Aska13MemoryManager25VirtualIsRegisteredNotifyEPvPNS_13IMemoryNotifyE | lib libSOA-3.7.0.so | 2026-10-04
undefined4
_ZN4Aska13MemoryManager25VirtualIsRegisteredNotifyEPvPNS_13IMemoryNotifyE
          (long param_1,long param_2,long param_3)

{
  int *piVar1;
  char cVar2;
  bool bVar3;
  ulong uVar4;
  int iVar5;
  int *piVar6;
  undefined4 uVar7;
  
  piVar6 = (int *)(param_1 + 0x98);
  iVar5 = 0;
code_r0x0204e6f4:
  do {
    if (*piVar6 != -1) {
      ClearExclusiveLocal();
      bVar3 = iVar5 < 0x1ff;
      iVar5 = iVar5 + 1;
      if (bVar3) goto code_r0x0204e6f4;
      piVar1 = (int *)(param_1 + 0x9c);
      do {
        cVar2 = '\x01';
        bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
        if (bVar3) {
          *piVar1 = *piVar1 + 1;
          cVar2 = ExclusiveMonitorsStatus();
        }
      } while (cVar2 != '\0');
      do {
        if (*piVar6 != -1) {
          ClearExclusiveLocal();
          do {
            uVar4 = Aska::Semaphore::IsReady() const(param_1 + 0xd8);
            if ((uVar4 & 1) == 0) {
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
              Aska::Semaphore::Wait() const(param_1 + 0xd8);
            }
            do {
              cVar2 = '\x01';
              bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
              if (bVar3) {
                *piVar1 = *piVar1 + 1;
                cVar2 = ExclusiveMonitorsStatus();
              }
            } while (cVar2 != '\0');
            while (*piVar6 == -1) {
              cVar2 = '\x01';
              bVar3 = (bool)ExclusiveMonitorPass(piVar6,0x10);
              if (bVar3) {
                *piVar6 = 0;
                cVar2 = ExclusiveMonitorsStatus();
              }
              if (cVar2 == '\0') goto code_r0x0204e7ac;
            }
            ClearExclusiveLocal();
          } while( true );
        }
        cVar2 = '\x01';
        bVar3 = (bool)ExclusiveMonitorPass(piVar6,0x10);
        if (bVar3) {
          *piVar6 = 0;
          cVar2 = ExclusiveMonitorsStatus();
        }
      } while (cVar2 != '\0');
code_r0x0204e7ac:
      do {
        cVar2 = '\x01';
        bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
        if (bVar3) {
          *piVar1 = *piVar1 + -1;
          cVar2 = ExclusiveMonitorsStatus();
        }
      } while (cVar2 != '\0');
code_r0x0204e7bc:
      DataMemoryBarrier(2,3);
      if (param_3 == 0) {
        if (*(long *)(param_2 + -8) != 0) goto code_r0x0204e7dc;
      }
      else if (*(long *)(param_2 + -8) == param_3) {
code_r0x0204e7dc:
        uVar7 = 1;
        goto code_r0x0204e7e0;
      }
      uVar7 = 0;
code_r0x0204e7e0:
      DataMemoryBarrier(2,3);
      *(undefined4 *)(param_1 + 0x98) = 0xffffffff;
      DataMemoryBarrier(2,3);
      piVar6 = (int *)(param_1 + 0x9c);
      if (0x14 < *piVar6) {
        do {
          cVar2 = '\x01';
          bVar3 = (bool)ExclusiveMonitorPass(piVar6,0x10);
          if (bVar3) {
            *piVar6 = *piVar6 + -1;
            cVar2 = ExclusiveMonitorsStatus();
          }
        } while (cVar2 != '\0');
        uVar4 = Aska::Semaphore::IsReady() const(param_1 + 0xd8);
        if ((uVar4 & 1) != 0) {
          Aska::Semaphore::Signal() const(param_1 + 0xd8);
        }
      }
      return uVar7;
    }
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar6,0x10);
    if (bVar3) {
      *piVar6 = 0;
      cVar2 = ExclusiveMonitorsStatus();
    }
    if (cVar2 == '\0') goto code_r0x0204e7bc;
  } while( true );
}

// ==== Aska::MemoryManager::VirtualGetRegisteredNotify(void*)
// vaddr 0x1f4e840 | ghidra 0x204e840 | size 336 | symbol _ZN4Aska13MemoryManager26VirtualGetRegisteredNotifyEPv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska13MemoryManager26VirtualGetRegisteredNotifyEPv(long param_1,long param_2)

{
  int *piVar1;
  char cVar2;
  bool bVar3;
  ulong uVar4;
  int iVar5;
  undefined8 uVar6;
  int *piVar7;
  
  piVar1 = (int *)(param_1 + 0x98);
  iVar5 = 0;
  do {
    while (*piVar1 != -1) {
      ClearExclusiveLocal();
      bVar3 = 0x1fe < iVar5;
      iVar5 = iVar5 + 1;
      if (bVar3) {
        piVar7 = (int *)(param_1 + 0x9c);
        do {
          cVar2 = '\x01';
          bVar3 = (bool)ExclusiveMonitorPass(piVar7,0x10);
          if (bVar3) {
            *piVar7 = *piVar7 + 1;
            cVar2 = ExclusiveMonitorsStatus();
          }
        } while (cVar2 != '\0');
        do {
          if (*piVar1 != -1) {
            ClearExclusiveLocal();
            do {
              uVar4 = Aska::Semaphore::IsReady() const(param_1 + 0xd8);
              if ((uVar4 & 1) == 0) {
                do {
                  cVar2 = '\x01';
                  bVar3 = (bool)ExclusiveMonitorPass(piVar7,0x10);
                  if (bVar3) {
                    *piVar7 = *piVar7 + -1;
                    cVar2 = ExclusiveMonitorsStatus();
                  }
                } while (cVar2 != '\0');
                Aska::Thread::Sleep(unsigned int)(1);
              }
              else {
                Aska::Semaphore::Wait() const(param_1 + 0xd8);
              }
              do {
                cVar2 = '\x01';
                bVar3 = (bool)ExclusiveMonitorPass(piVar7,0x10);
                if (bVar3) {
                  *piVar7 = *piVar7 + 1;
                  cVar2 = ExclusiveMonitorsStatus();
                }
              } while (cVar2 != '\0');
              while (*piVar1 == -1) {
                cVar2 = '\x01';
                bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
                if (bVar3) {
                  *piVar1 = 0;
                  cVar2 = ExclusiveMonitorsStatus();
                }
                if (cVar2 == '\0') goto code_r0x0204e978;
              }
              ClearExclusiveLocal();
            } while( true );
          }
          cVar2 = '\x01';
          bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar3) {
            *piVar1 = 0;
            cVar2 = ExclusiveMonitorsStatus();
          }
        } while (cVar2 != '\0');
code_r0x0204e978:
        do {
          cVar2 = '\x01';
          bVar3 = (bool)ExclusiveMonitorPass(piVar7,0x10);
          if (bVar3) {
            *piVar7 = *piVar7 + -1;
            cVar2 = ExclusiveMonitorsStatus();
          }
        } while (cVar2 != '\0');
        DataMemoryBarrier(2,3);
code_r0x0204e8b8:
        piVar7 = (int *)(param_1 + 0x9c);
        uVar6 = *(undefined8 *)(param_2 + -8);
        DataMemoryBarrier(2,3);
        *piVar1 = -1;
        DataMemoryBarrier(2,3);
        if (0x14 < *piVar7) {
          do {
            cVar2 = '\x01';
            bVar3 = (bool)ExclusiveMonitorPass(piVar7,0x10);
            if (bVar3) {
              *piVar7 = *piVar7 + -1;
              cVar2 = ExclusiveMonitorsStatus();
            }
          } while (cVar2 != '\0');
          uVar4 = Aska::Semaphore::IsReady() const(param_1 + 0xd8);
          if ((uVar4 & 1) != 0) {
            Aska::Semaphore::Signal() const(param_1 + 0xd8);
          }
        }
        return uVar6;
      }
    }
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar3) {
      *piVar1 = 0;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
  DataMemoryBarrier(2,3);
  goto code_r0x0204e8b8;
}

// ==== Aska::MemoryManager::VirtualMalloc(unsigned long)
// vaddr 0x1f4e990 | ghidra 0x204e990 | size 4 | symbol _ZN4Aska13MemoryManager13VirtualMallocEm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13MemoryManager13VirtualMallocEm(void)

{
  (*(code *)PTR__ZN4Aska13MemoryManager6MallocEm_02ca1310)();
  return;
}

// ==== Aska::MemoryManager::VirtualMallocHigh(unsigned long)
// vaddr 0x1f4e994 | ghidra 0x204e994 | size 4 | symbol _ZN4Aska13MemoryManager17VirtualMallocHighEm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13MemoryManager17VirtualMallocHighEm(void)

{
  (*(code *)PTR__ZN4Aska13MemoryManager10MallocHighEm_02c990a8)();
  return;
}

// ==== Aska::MemoryManager::VirtualAlignedMalloc(unsigned long, long)
// vaddr 0x1f4e998 | ghidra 0x204e998 | size 4 | symbol _ZN4Aska13MemoryManager20VirtualAlignedMallocEml | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13MemoryManager20VirtualAlignedMallocEml(void)

{
  (*(code *)PTR__ZN4Aska13MemoryManager13AlignedMallocEml_02cae360)();
  return;
}

// ==== Aska::MemoryManager::VirtualAlignedMallocHigh(unsigned long, long)
// vaddr 0x1f4e99c | ghidra 0x204e99c | size 4 | symbol _ZN4Aska13MemoryManager24VirtualAlignedMallocHighEml | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13MemoryManager24VirtualAlignedMallocHighEml(void)

{
  (*(code *)PTR__ZN4Aska13MemoryManager17AlignedMallocHighEml_02cab2b8)();
  return;
}

// ==== Aska::MemoryManager::VirtualRealloc(unsigned long, void*, long)
// vaddr 0x1f4e9a0 | ghidra 0x204e9a0 | size 4 | symbol _ZN4Aska13MemoryManager14VirtualReallocEmPvl | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13MemoryManager14VirtualReallocEmPvl(void)

{
  (*(code *)PTR__ZN4Aska13MemoryManager7ReallocEmPvl_02cb5770)();
  return;
}

// ==== Aska::MemoryManager::VirtualSplit(void*, void*)
// vaddr 0x1f4e9a4 | ghidra 0x204e9a4 | size 4 | symbol _ZN4Aska13MemoryManager12VirtualSplitEPvS1_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13MemoryManager12VirtualSplitEPvS1_(void)

{
  (*(code *)PTR__ZN4Aska13MemoryManager5SplitEPvS1__02ca7480)();
  return;
}

// ==== Aska::MemoryManager::VirtualMove(void*, long, bool)
// vaddr 0x1f4e9a8 | ghidra 0x204e9a8 | size 8 | symbol _ZN4Aska13MemoryManager11VirtualMoveEPvlb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13MemoryManager11VirtualMoveEPvlb(void)

{
  (*(code *)PTR__ZN4Aska13MemoryManager4MoveEPvlb_02c9c978)();
  return;
}

// ==== Aska::MemoryManager::VirtualMoveHigh(void*, long)
// vaddr 0x1f4e9b0 | ghidra 0x204e9b0 | size 8 | symbol _ZN4Aska13MemoryManager15VirtualMoveHighEPvl | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13MemoryManager15VirtualMoveHighEPvl(void)

{
  (*(code *)PTR__ZN4Aska13MemoryManager4MoveEPvlb_02c9c978)();
  return;
}

// ==== Aska::MemoryManager::VirtualFree(void*)
// vaddr 0x1f4e9b8 | ghidra 0x204e9b8 | size 20 | symbol _ZN4Aska13MemoryManager11VirtualFreeEPv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13MemoryManager11VirtualFreeEPv(undefined8 param_1,long param_2)

{
  if (param_2 != 0) {
    (*(code *)PTR__ZN4Aska13MemoryManager9LocalFreeEPNS_12_MemoryBlockE_02c924f8)
              (*(undefined8 *)(param_2 + -0x18),param_2 + -0x40);
    return;
  }
  return;
}

// ==== Aska::MemoryManager::VirtualGetHeapAddress() const
// vaddr 0x1f4e9cc | ghidra 0x204e9cc | size 8 | symbol _ZNK4Aska13MemoryManager21VirtualGetHeapAddressEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska13MemoryManager21VirtualGetHeapAddressEv(long param_1)

{
  return *(undefined8 *)(param_1 + 0x20);
}

// ==== Aska::MemoryManager::VirtualIsPhysical() const
// vaddr 0x1f4e9d4 | ghidra 0x204e9d4 | size 8 | symbol _ZNK4Aska13MemoryManager17VirtualIsPhysicalEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska13MemoryManager17VirtualIsPhysicalEv(void)

{
  return 0;
}

// ==== Aska::MemoryManager::VirtualCalcFreeSize(long*, long*) const
// vaddr 0x1f4e9e4 | ghidra 0x204e9e4 | size 4 | symbol _ZNK4Aska13MemoryManager19VirtualCalcFreeSizeEPlS1_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK4Aska13MemoryManager19VirtualCalcFreeSizeEPlS1_(void)

{
  (*(code *)PTR__ZNK4Aska13MemoryManager12CalcFreeSizeEPlS1__02caec58)();
  return;
}

// ==== Aska::MemoryManager::VirtualIsEmpty(bool) const
// vaddr 0x1f4e9e8 | ghidra 0x204e9e8 | size 8 | symbol _ZNK4Aska13MemoryManager14VirtualIsEmptyEb | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK4Aska13MemoryManager14VirtualIsEmptyEb(undefined8 param_1,uint param_2)

{
  (*(code *)PTR__ZNK4Aska13MemoryManager7IsEmptyEb_02cac970)(param_1,param_2 & 1);
  return;
}

// ==== Aska::MemoryManager::VirtualGetFastCriticalSection()
// vaddr 0x1f4e9f0 | ghidra 0x204e9f0 | size 8 | symbol _ZN4Aska13MemoryManager29VirtualGetFastCriticalSectionEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska13MemoryManager29VirtualGetFastCriticalSectionEv(long param_1)

{
  return param_1 + 0x60;
}

// ==== Aska::MemoryManager::VirtualGetSrbk(int) const
// vaddr 0x1f4e9f8 | ghidra 0x204e9f8 | size 16 | symbol _ZNK4Aska13MemoryManager14VirtualGetSrbkEi | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK4Aska13MemoryManager14VirtualGetSrbkEi(long param_1,int param_2)

{
  return *(long *)(param_1 + 0x10) + (long)param_2 * 0x28;
}

// ==== Aska::MemoryManager::VirtualGetTopSrbkAddress() const
// vaddr 0x1f4ea08 | ghidra 0x204ea08 | size 8 | symbol _ZNK4Aska13MemoryManager24VirtualGetTopSrbkAddressEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska13MemoryManager24VirtualGetTopSrbkAddressEv(long param_1)

{
  return *(undefined8 *)(param_1 + 0x10);
}

// ==== Aska::MemoryManager::VirtualPrintMemoryChain()
// vaddr 0x1f4ea10 | ghidra 0x204ea10 | size 4 | symbol _ZN4Aska13MemoryManager23VirtualPrintMemoryChainEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13MemoryManager23VirtualPrintMemoryChainEv(void)

{
  return;
}

// ==== Aska::MemoryManager::VirtualGetHeapSize() const
// vaddr 0x1f4ea14 | ghidra 0x204ea14 | size 8 | symbol _ZNK4Aska13MemoryManager18VirtualGetHeapSizeEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska13MemoryManager18VirtualGetHeapSizeEv(long param_1)

{
  return *(undefined8 *)(param_1 + 0x28);
}

// ==== Aska::MemoryManager::VirtualGetAllocatedManager(void const*, unsigned long*)
// vaddr 0x1f4ea1c | ghidra 0x204ea1c | size 20 | symbol _ZN4Aska13MemoryManager26VirtualGetAllocatedManagerEPKvPm | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska13MemoryManager26VirtualGetAllocatedManagerEPKvPm
          (undefined8 param_1,long param_2,undefined8 *param_3)

{
  if (param_3 != (undefined8 *)0x0) {
    *param_3 = *(undefined8 *)(param_2 + -0x40);
  }
  return *(undefined8 *)(param_2 + -0x18);
}

// ==== Aska::MemoryManagerAdapter::Malloc(unsigned long)
// vaddr 0x1f4ea30 | ghidra 0x204ea30 | size 24 | symbol _ZN4Aska20MemoryManagerAdapter6MallocEm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska20MemoryManagerAdapter6MallocEm(undefined8 param_1)

{
  undefined8 uVar1;
  
  uVar1 = Aska::Global::GetAvailableMemoryManager()();
  (*(code *)PTR__ZN4Aska13MemoryManager6MallocEm_02ca1310)(uVar1,param_1);
  return;
}

// ==== Aska::MemoryManagerAdapter::Free(void*)
// vaddr 0x1f4ea48 | ghidra 0x204ea48 | size 36 | symbol _ZN4Aska20MemoryManagerAdapter4FreeEPv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska20MemoryManagerAdapter4FreeEPv(long param_1)

{
  undefined8 uVar1;
  
  uVar1 = Aska::Global::GetAvailableMemoryManager()();
  if (param_1 != 0) {
    (*(code *)PTR__ZN4Aska13MemoryManager9LocalFreeEPv_02cb5c60)(uVar1,param_1);
    return;
  }
  return;
}

// ==== Aska::MemoryManagerAdapter::AlignedMalloc(unsigned long, unsigned long)
// vaddr 0x1f4ea6c | ghidra 0x204ea6c | size 40 | symbol _ZN4Aska20MemoryManagerAdapter13AlignedMallocEmm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska20MemoryManagerAdapter13AlignedMallocEmm(undefined8 param_1,undefined8 param_2)

{
  undefined8 uVar1;
  
  uVar1 = Aska::Global::GetAvailableMemoryManager()();
  (*(code *)PTR__ZN4Aska13MemoryManager13AlignedMallocEml_02cae360)(uVar1,param_1,param_2);
  return;
}

// ==== Aska::MemoryManagerAdapter::AlignedFree(void*)
// vaddr 0x1f4ea94 | ghidra 0x204ea94 | size 36 | symbol _ZN4Aska20MemoryManagerAdapter11AlignedFreeEPv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska20MemoryManagerAdapter11AlignedFreeEPv(long param_1)

{
  undefined8 uVar1;
  
  uVar1 = Aska::Global::GetAvailableMemoryManager()();
  if (param_1 != 0) {
    (*(code *)PTR__ZN4Aska13MemoryManager9LocalFreeEPv_02cb5c60)(uVar1,param_1);
    return;
  }
  return;
}


// FAILED to create function at 02bb1e98 Aska::MemoryManager::vtable
// FAILED to create function at 02bb1f80 Aska::MemoryManager::typeinfo
