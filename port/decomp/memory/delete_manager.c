// port/decomp/memory/delete_manager.c: Ghidra decompiles for the memory subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-04 05:04 UTC: tools/decomp.sh '--into' 'memory/delete_manager' 'Aska::DeleteManager::' 'Aska::TSharedPointerCode::'

// ==== Aska::DeleteManager::~DeleteManager()
// vaddr 0x1f1e24c | ghidra 0x201e24c | size 132 | symbol _ZN4Aska13DeleteManagerD2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13DeleteManagerD2Ev(long *param_1)

{
  undefined *puVar1;
  
  *param_1 = (long)(PTR__ZTVN4Aska13DeleteManagerE_02cba7a0 + 0x10);
  if (param_1[0x13] != 0) {
    Aska::DeleteManager::Clear()(param_1);
    if (param_1[0x13] != 0) {
      operator delete[](void*)();
    }
    param_1[0x13] = 0;
  }
  puVar1 = PTR__ZTVN4Aska13TDynamicQueueIPNS_13DeleteManager18_DeletePointerInfoELb0EEE_02cbbbb0;
  *(undefined4 *)(param_1 + 0x23) = 0;
  param_1[0x24] = 0;
  puVar1 = puVar1 + 0x10;
  *(undefined4 *)(param_1 + 0x1f) = 0;
  *(undefined4 *)(param_1 + 0x1b) = 0;
  param_1[0x21] = (long)puVar1;
  param_1[0x22] = 1;
  param_1[0x1d] = (long)puVar1;
  param_1[0x1e] = 1;
  param_1[0x19] = (long)puVar1;
  param_1[0x1a] = 1;
  param_1[0x20] = 0;
  param_1[0x1c] = 0;
  param_1[0x18] = 0;
  param_1[0x15] = (long)puVar1;
  param_1[0x16] = 1;
  *(undefined4 *)(param_1 + 0x17) = 0;
  (*(code *)PTR__ZN4Aska19FastCriticalSectionD2Ev_02ca21e0)(param_1 + 1);
  return;
}

// ==== Aska::DeleteManager::Initialize()
// vaddr 0x1f1e2dc | ghidra 0x201e2dc | size 216 | symbol _ZN4Aska13DeleteManager10InitializeEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska13DeleteManager10InitializeEv(long param_1)

{
  uint uVar1;
  int iVar2;
  long lVar3;
  long lVar4;
  ulong uVar5;
  undefined8 uVar6;
  undefined1 auStack_28 [8];
  
  Aska::AppProjectDependentProxy::AppProjectDependentProxy()(auStack_28);
  iVar2 = Aska::AppProjectDependentProxy::GetDeleteManagerQueueSize() const(auStack_28);
  *(int *)(param_1 + 0x130) = iVar2;
  if (iVar2 - 2U < 0xfffe) {
    uVar1 = iVar2 + 1;
    lVar3 = operator new[](unsigned long, std::nothrow_t const&)((long)(int)(iVar2 * 0x18 + uVar1 * 0x20),PTR__ZSt7nothrow_02cb9a80);
    if (lVar3 != 0) {
      lVar4 = lVar3 + (long)iVar2 * 0x18;
      uVar5 = -(ulong)(uVar1 >> 0x1f) & 0xfffffff800000000 | (ulong)uVar1 << 3;
      *(long *)(param_1 + 0xc0) = lVar4;
      lVar4 = lVar4 + uVar5;
      *(long *)(param_1 + 0xe0) = lVar4;
      lVar4 = lVar4 + uVar5;
      *(long *)(param_1 + 0x98) = lVar3;
      *(long *)(param_1 + 0xa0) = lVar3;
      uVar6 = 1;
      *(long *)(param_1 + 0x100) = lVar4;
      *(uint *)(param_1 + 0xb8) = uVar1;
      *(uint *)(param_1 + 0xd8) = uVar1;
      *(uint *)(param_1 + 0xf8) = uVar1;
      *(uint *)(param_1 + 0x118) = uVar1;
      *(undefined8 *)(param_1 + 0xb0) = 1;
      *(undefined8 *)(param_1 + 0xd0) = 1;
      *(undefined8 *)(param_1 + 0xf0) = 1;
      *(undefined8 *)(param_1 + 0x110) = 1;
      *(ulong *)(param_1 + 0x120) = lVar4 + uVar5;
      *(long *)(param_1 + 0x128) = param_1 + 0xe8;
      Aska::DeleteManager::Clear()(param_1);
      goto code_r0x0201e398;
    }
  }
  uVar6 = 0;
code_r0x0201e398:
  Aska::AppProjectDependentProxy::~AppProjectDependentProxy()(auStack_28);
  return uVar6;
}

// ==== Aska::DeleteManager::Clear()
// vaddr 0x1f1e3e8 | ghidra 0x201e3e8 | size 456 | symbol _ZN4Aska13DeleteManager5ClearEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13DeleteManager5ClearEv(long param_1)

{
  int *piVar1;
  char cVar2;
  bool bVar3;
  ulong uVar4;
  int iVar5;
  ulong uVar6;
  int *piVar7;
  uint uVar8;
  ulong uVar9;
  
  piVar7 = (int *)(param_1 + 0x40);
  iVar5 = 0;
  do {
    while (*piVar7 == -1) {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar7,0x10);
      if (bVar3) {
        *piVar7 = 0;
        cVar2 = ExclusiveMonitorsStatus();
      }
      if (cVar2 == '\0') goto code_r0x0201e4c8;
    }
    ClearExclusiveLocal();
    bVar3 = iVar5 < 0x1ff;
    iVar5 = iVar5 + 1;
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
        uVar4 = Aska::Semaphore::IsReady() const(param_1 + 0x80);
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
          if (cVar2 == '\0') goto code_r0x0201e4b8;
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
code_r0x0201e4b8:
  do {
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar3) {
      *piVar1 = *piVar1 + -1;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
code_r0x0201e4c8:
  DataMemoryBarrier(2,3);
  *(undefined8 *)(param_1 + 0xb0) = 1;
  *(undefined8 *)(param_1 + 0xd0) = 1;
  *(undefined8 *)(param_1 + 0xf0) = 1;
  *(undefined8 *)(param_1 + 0x110) = 1;
  if (0 < *(int *)(param_1 + 0x130)) {
    uVar9 = *(ulong *)(param_1 + 0xa0);
    uVar8 = 1;
    uVar6 = uVar9 + (long)*(int *)(param_1 + 0x130) * 0x18;
    uVar4 = uVar9 + 0x18;
    do {
      *(ulong *)(*(long *)(param_1 + 0xc0) + (ulong)uVar8 * 8) = uVar9;
      uVar8 = 0;
      if (*(int *)(param_1 + 0xb0) + 1U < *(uint *)(param_1 + 0xb8)) {
        uVar8 = *(int *)(param_1 + 0xb0) + 1;
      }
      *(uint *)(param_1 + 0xb0) = uVar8;
      do {
        uVar9 = uVar4;
        if (uVar6 <= uVar9) goto code_r0x0201e54c;
        uVar4 = uVar9 + 0x18;
      } while (*(uint *)(param_1 + 0xb4) == uVar8);
    } while( true );
  }
code_r0x0201e54c:
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
    uVar4 = Aska::Semaphore::IsReady() const(param_1 + 0x80);
    if ((uVar4 & 1) != 0) {
      (*(code *)PTR__ZNK4Aska9Semaphore6SignalEv_02c96cd0)(param_1 + 0x80);
      return;
    }
  }
  return;
}

// ==== Aska::DeleteManager::IsEmpty()
// vaddr 0x1f1e5b0 | ghidra 0x201e5b0 | size 92 | symbol _ZN4Aska13DeleteManager7IsEmptyEv | lib libSOA-3.7.0.so | 2026-10-04
bool _ZN4Aska13DeleteManager7IsEmptyEv(long param_1)

{
  uint uVar1;
  long lVar2;
  
  uVar1 = *(uint *)(param_1 + 0xd0);
  if (uVar1 <= *(uint *)(param_1 + 0xd4)) {
    uVar1 = *(int *)(param_1 + 0xd8) + uVar1;
  }
  if (uVar1 - 1 == *(uint *)(param_1 + 0xd4)) {
    lVar2 = *(long *)(param_1 + 0x128);
    if (lVar2 != 0) {
      uVar1 = *(uint *)(lVar2 + 8);
      if (uVar1 <= *(uint *)(lVar2 + 0xc)) {
        uVar1 = *(int *)(lVar2 + 0x10) + uVar1;
      }
      return uVar1 - 1 == *(uint *)(lVar2 + 0xc);
    }
    return true;
  }
  return false;
}

// ==== Aska::DeleteManager::AddMain(void*, unsigned char, unsigned char, Aska::IDeleteHandler*)
// vaddr 0x1f1e60c | ghidra 0x201e60c | size 588 | symbol _ZN4Aska13DeleteManager7AddMainEPvhhPNS_14IDeleteHandlerE | lib libSOA-3.7.0.so | 2026-10-04
undefined4
_ZN4Aska13DeleteManager7AddMainEPvhhPNS_14IDeleteHandlerE
          (long param_1,long param_2,undefined1 param_3,char param_4,long param_5)

{
  undefined8 *puVar1;
  int *piVar2;
  uint uVar3;
  char cVar4;
  bool bVar5;
  ulong uVar6;
  int iVar7;
  long *plVar8;
  int *piVar9;
  long lVar10;
  undefined4 uVar11;
  long lStack_68;
  long lStack_60;
  char cStack_58;
  undefined1 uStack_57;
  
  if (param_2 != 0) {
    if (*(long *)(param_1 + 0x98) != 0) {
      piVar9 = (int *)(param_1 + 0x40);
      iVar7 = 0;
code_r0x0201e64c:
      do {
        if (*piVar9 != -1) {
          ClearExclusiveLocal();
          bVar5 = iVar7 < 0x1ff;
          iVar7 = iVar7 + 1;
          if (bVar5) goto code_r0x0201e64c;
          piVar2 = (int *)(param_1 + 0x44);
          do {
            cVar4 = '\x01';
            bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
            if (bVar5) {
              *piVar2 = *piVar2 + 1;
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
                    bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
                    if (bVar5) {
                      *piVar2 = *piVar2 + -1;
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
                  bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
                  if (bVar5) {
                    *piVar2 = *piVar2 + 1;
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
                  if (cVar4 == '\0') goto code_r0x0201e728;
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
code_r0x0201e728:
          do {
            cVar4 = '\x01';
            bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
            if (bVar5) {
              *piVar2 = *piVar2 + -1;
              cVar4 = ExclusiveMonitorsStatus();
            }
          } while (cVar4 != '\0');
code_r0x0201e738:
          DataMemoryBarrier(2,3);
          uVar11 = 0;
          uVar3 = 0;
          if (*(int *)(param_1 + 0xb4) + 1U < *(uint *)(param_1 + 0xb8)) {
            uVar3 = *(int *)(param_1 + 0xb4) + 1;
          }
          if (uVar3 == *(uint *)(param_1 + 0xb0)) goto code_r0x0201e7f0;
          *(uint *)(param_1 + 0xb4) = uVar3;
          puVar1 = (undefined8 *)(*(long *)(param_1 + 0xc0) + (ulong)uVar3 * 8);
          if (puVar1 == (undefined8 *)0x0) {
code_r0x0201e7c4:
            uVar11 = 0;
          }
          else {
            plVar8 = (long *)*puVar1;
            *(char *)(plVar8 + 2) = param_4;
            *(undefined1 *)((long)plVar8 + 0x11) = param_3;
            *plVar8 = param_2;
            plVar8[1] = param_5;
            if (param_4 == '\0') {
              if (*(uint *)(param_1 + 0xd4) == *(uint *)(param_1 + 0xd0)) goto code_r0x0201e7c4;
              *(long **)(*(long *)(param_1 + 0xe0) + (ulong)*(uint *)(param_1 + 0xd0) * 8) = plVar8;
              iVar7 = 0;
              if (*(int *)(param_1 + 0xd0) + 1U < *(uint *)(param_1 + 0xd8)) {
                iVar7 = *(int *)(param_1 + 0xd0) + 1;
              }
              *(int *)(param_1 + 0xd0) = iVar7;
            }
            else {
              lVar10 = *(long *)(param_1 + 0x128);
              if (*(uint *)(lVar10 + 0xc) == *(uint *)(lVar10 + 8)) goto code_r0x0201e7c4;
              *(long **)(*(long *)(lVar10 + 0x18) + (ulong)*(uint *)(lVar10 + 8) * 8) = plVar8;
              iVar7 = 0;
              if (*(int *)(lVar10 + 8) + 1U < *(uint *)(lVar10 + 0x10)) {
                iVar7 = *(int *)(lVar10 + 8) + 1;
              }
              *(int *)(lVar10 + 8) = iVar7;
            }
            uVar11 = 1;
          }
code_r0x0201e7f0:
          DataMemoryBarrier(2,3);
          *(undefined4 *)(param_1 + 0x40) = 0xffffffff;
          DataMemoryBarrier(2,3);
          piVar9 = (int *)(param_1 + 0x44);
          if (*piVar9 < 0x15) {
            return uVar11;
          }
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
            return uVar11;
          }
          return uVar11;
        }
        cVar4 = '\x01';
        bVar5 = (bool)ExclusiveMonitorPass(piVar9,0x10);
        if (bVar5) {
          *piVar9 = 0;
          cVar4 = ExclusiveMonitorsStatus();
        }
        if (cVar4 == '\0') goto code_r0x0201e738;
      } while( true );
    }
    lStack_68 = param_2;
    lStack_60 = param_5;
    cStack_58 = param_4;
    uStack_57 = param_3;
    Aska::DeleteManager::_DeletePointerInfo::DeletePointer()(&lStack_68);
  }
  return 1;
}

// ==== Aska::DeleteManager::_DeletePointerInfo::DeletePointer()
// vaddr 0x1f1e858 | ghidra 0x201e858 | size 192 | symbol _ZN4Aska13DeleteManager18_DeletePointerInfo13DeletePointerEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13DeleteManager18_DeletePointerInfo13DeletePointerEv(long *param_1)

{
  char cVar1;
  int iVar2;
  undefined8 *puVar3;
  
  puVar3 = (undefined8 *)param_1[1];
  cVar1 = *(char *)((long)param_1 + 0x11);
  if (puVar3 != (undefined8 *)0x0) {
    if (cVar1 != '\t') {
                    /* WARNING: Could not recover jumptable at 0x0201e8b4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (**(code **)*puVar3)(puVar3,cVar1,*param_1);
      return;
    }
                    /* WARNING: Could not recover jumptable at 0x0201e87c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)*puVar3)(puVar3,*param_1);
    return;
  }
  switch(cVar1) {
  case '\0':
  case '\x01':
    (*(code *)PTR__ZN4Aska14IMemoryManager4FreeEPKv_02c91818)(*param_1);
    return;
  case '\x02':
                    /* WARNING: Could not recover jumptable at 0x0201e8f0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(*(long *)*param_1 + 0x50))();
    return;
  case '\x03':
  case '\x04':
    param_1 = (long *)*param_1;
    if (param_1 != (long *)0x0) {
code_r0x0201e8d8:
                    /* WARNING: Could not recover jumptable at 0x0201e8e0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (**(code **)(*param_1 + 8))();
      return;
    }
    break;
  case '\x05':
  case '\a':
    param_1 = (long *)*param_1;
    iVar2 = (int)param_1[1] + -1;
    *(int *)(param_1 + 1) = iVar2;
    if (iVar2 == 0) goto code_r0x0201e8d8;
    break;
  case '\x06':
    puVar3 = (undefined8 *)*param_1;
    iVar2 = *(int *)(puVar3 + 1);
    *(int *)(puVar3 + 1) = iVar2 + -1;
    if (iVar2 + -1 == 0) {
                    /* WARNING: Could not recover jumptable at 0x0201e914. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (**(code **)*puVar3)();
      return;
    }
  }
  return;
}

// ==== Aska::DeleteManager::Cancel(void*)
// vaddr 0x1f1e918 | ghidra 0x201e918 | size 548 | symbol _ZN4Aska13DeleteManager6CancelEPv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13DeleteManager6CancelEPv(long param_1,long param_2)

{
  int *piVar1;
  int iVar2;
  char cVar3;
  bool bVar4;
  ulong uVar5;
  int iVar6;
  long lVar7;
  long *plVar8;
  int *piVar9;
  long *plVar10;
  
  piVar9 = (int *)(param_1 + 0x40);
  iVar6 = 0;
code_r0x0201e934:
  do {
    if (*piVar9 != -1) {
      ClearExclusiveLocal();
      bVar4 = iVar6 < 0x1ff;
      iVar6 = iVar6 + 1;
      if (bVar4) goto code_r0x0201e934;
      piVar1 = (int *)(param_1 + 0x44);
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
        if (bVar4) {
          *piVar1 = *piVar1 + 1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      do {
        if (*piVar9 != -1) {
          ClearExclusiveLocal();
          do {
            uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0x80);
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
              Aska::Semaphore::Wait() const(param_1 + 0x80);
            }
            do {
              cVar3 = '\x01';
              bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
              if (bVar4) {
                *piVar1 = *piVar1 + 1;
                cVar3 = ExclusiveMonitorsStatus();
              }
            } while (cVar3 != '\0');
            while (*piVar9 == -1) {
              cVar3 = '\x01';
              bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
              if (bVar4) {
                *piVar9 = 0;
                cVar3 = ExclusiveMonitorsStatus();
              }
              if (cVar3 == '\0') goto code_r0x0201e9ec;
            }
            ClearExclusiveLocal();
          } while( true );
        }
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
        if (bVar4) {
          *piVar9 = 0;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
code_r0x0201e9ec:
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
        if (bVar4) {
          *piVar1 = *piVar1 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
code_r0x0201e9fc:
      DataMemoryBarrier(2,3);
      iVar6 = 0;
      if (*(int *)(param_1 + 0xd4) + 1U < *(uint *)(param_1 + 0xd8)) {
        iVar6 = *(int *)(param_1 + 0xd4) + 1;
      }
      if (iVar6 == *(int *)(param_1 + 0xd0)) {
code_r0x0201ea50:
        lVar7 = *(long *)(param_1 + 0x128);
        iVar6 = 0;
        if (*(int *)(lVar7 + 0xc) + 1U < *(uint *)(lVar7 + 0x10)) {
          iVar6 = *(int *)(lVar7 + 0xc) + 1;
        }
        if (iVar6 == *(int *)(lVar7 + 8)) goto code_r0x0201ead8;
        while( true ) {
          plVar8 = (long *)(*(long *)(lVar7 + 0x18) + (long)iVar6 * 8);
          if (plVar8 == (long *)0x0) goto code_r0x0201ead8;
          plVar10 = (long *)*plVar8;
          if ((plVar10 != (long *)0x0) && (*plVar10 == param_2)) break;
          iVar2 = 0;
          if (iVar6 + 1U < *(uint *)(lVar7 + 0x10)) {
            iVar2 = iVar6 + 1;
          }
          iVar6 = iVar2;
          if (iVar2 == *(int *)(lVar7 + 8)) goto code_r0x0201ead8;
        }
      }
      else {
        while( true ) {
          plVar8 = (long *)(*(long *)(param_1 + 0xe0) + (long)iVar6 * 8);
          if (plVar8 == (long *)0x0) goto code_r0x0201ea50;
          plVar10 = (long *)*plVar8;
          if ((plVar10 != (long *)0x0) && (*plVar10 == param_2)) break;
          iVar2 = 0;
          if (iVar6 + 1U < *(uint *)(param_1 + 0xd8)) {
            iVar2 = iVar6 + 1;
          }
          iVar6 = iVar2;
          if (iVar2 == *(int *)(param_1 + 0xd0)) goto code_r0x0201ea50;
        }
      }
      if (*(uint *)(param_1 + 0xb4) != *(uint *)(param_1 + 0xb0)) {
        *(long **)(*(long *)(param_1 + 0xc0) + (ulong)*(uint *)(param_1 + 0xb0) * 8) = plVar10;
        iVar6 = 0;
        if (*(int *)(param_1 + 0xb0) + 1U < *(uint *)(param_1 + 0xb8)) {
          iVar6 = *(int *)(param_1 + 0xb0) + 1;
        }
        *(int *)(param_1 + 0xb0) = iVar6;
      }
      *plVar8 = 0;
code_r0x0201ead8:
      DataMemoryBarrier(2,3);
      *(undefined4 *)(param_1 + 0x40) = 0xffffffff;
      DataMemoryBarrier(2,3);
      piVar9 = (int *)(param_1 + 0x44);
      if (0x14 < *piVar9) {
        do {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
          if (bVar4) {
            *piVar9 = *piVar9 + -1;
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
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
    if (bVar4) {
      *piVar9 = 0;
      cVar3 = ExclusiveMonitorsStatus();
    }
    if (cVar3 == '\0') goto code_r0x0201e9fc;
  } while( true );
}

// ==== Aska::DeleteManager::PreFlushMain()
// vaddr 0x1f1eb3c | ghidra 0x201eb3c | size 568 | symbol _ZN4Aska13DeleteManager12PreFlushMainEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13DeleteManager12PreFlushMainEv(long param_1)

{
  long *plVar1;
  int *piVar2;
  int *piVar3;
  long lVar4;
  int iVar5;
  char cVar6;
  bool bVar7;
  ulong uVar8;
  uint uVar9;
  int iVar10;
  uint uVar11;
  long lVar12;
  uint uVar13;
  uint uVar14;
  
  iVar10 = *(int *)(param_1 + 0xf4);
  uVar9 = *(uint *)(param_1 + 0xf8);
  uVar11 = *(uint *)(param_1 + 0xf0);
  *(long *)(param_1 + 0x128) = param_1 + 0x108;
  uVar14 = 0;
  if (iVar10 + 1U < uVar9) {
    uVar14 = iVar10 + 1;
  }
  if (uVar14 != uVar11) {
    piVar2 = (int *)(param_1 + 0x40);
    piVar3 = (int *)(param_1 + 0x44);
    lVar4 = param_1 + 0x80;
    uVar13 = uVar14;
    do {
      plVar1 = (long *)(*(long *)(param_1 + 0x100) + (long)(int)uVar13 * 8);
      uVar14 = uVar11;
      if (plVar1 == (long *)0x0) break;
      lVar12 = *plVar1;
      if (lVar12 != 0) {
        if (*(char *)(lVar12 + 0x10) == '\0') {
          Aska::DeleteManager::_DeletePointerInfo::DeletePointer()(lVar12);
          iVar10 = 0;
          do {
            while (*piVar2 == -1) {
              cVar6 = '\x01';
              bVar7 = (bool)ExclusiveMonitorPass(piVar2,0x10);
              if (bVar7) {
                *piVar2 = 0;
                cVar6 = ExclusiveMonitorsStatus();
              }
              if (cVar6 == '\0') goto code_r0x0201ec78;
            }
            ClearExclusiveLocal();
            bVar7 = iVar10 < 0x1ff;
            iVar10 = iVar10 + 1;
          } while (bVar7);
          do {
            cVar6 = '\x01';
            bVar7 = (bool)ExclusiveMonitorPass(piVar3,0x10);
            if (bVar7) {
              *piVar3 = *piVar3 + 1;
              cVar6 = ExclusiveMonitorsStatus();
            }
          } while (cVar6 != '\0');
          do {
            if (*piVar2 != -1) {
              do {
                ClearExclusiveLocal();
                uVar8 = Aska::Semaphore::IsReady() const(lVar4);
                if ((uVar8 & 1) == 0) {
                  do {
                    cVar6 = '\x01';
                    bVar7 = (bool)ExclusiveMonitorPass(piVar3,0x10);
                    if (bVar7) {
                      *piVar3 = *piVar3 + -1;
                      cVar6 = ExclusiveMonitorsStatus();
                    }
                  } while (cVar6 != '\0');
                  Aska::Thread::Sleep(unsigned int)(1);
                }
                else {
                  Aska::Semaphore::Wait() const(lVar4);
                }
                do {
                  cVar6 = '\x01';
                  bVar7 = (bool)ExclusiveMonitorPass(piVar3,0x10);
                  if (bVar7) {
                    *piVar3 = *piVar3 + 1;
                    cVar6 = ExclusiveMonitorsStatus();
                  }
                } while (cVar6 != '\0');
                while (*piVar2 == -1) {
                  cVar6 = '\x01';
                  bVar7 = (bool)ExclusiveMonitorPass(piVar2,0x10);
                  if (bVar7) {
                    *piVar2 = 0;
                    cVar6 = ExclusiveMonitorsStatus();
                  }
                  if (cVar6 == '\0') goto code_r0x0201ec68;
                }
              } while( true );
            }
            cVar6 = '\x01';
            bVar7 = (bool)ExclusiveMonitorPass(piVar2,0x10);
            if (bVar7) {
              *piVar2 = 0;
              cVar6 = ExclusiveMonitorsStatus();
            }
          } while (cVar6 != '\0');
code_r0x0201ec68:
          do {
            cVar6 = '\x01';
            bVar7 = (bool)ExclusiveMonitorPass(piVar3,0x10);
            if (bVar7) {
              *piVar3 = *piVar3 + -1;
              cVar6 = ExclusiveMonitorsStatus();
            }
          } while (cVar6 != '\0');
code_r0x0201ec78:
          DataMemoryBarrier(2,3);
          if (*(uint *)(param_1 + 0xb4) != *(uint *)(param_1 + 0xb0)) {
            *(long *)(*(long *)(param_1 + 0xc0) + (ulong)*(uint *)(param_1 + 0xb0) * 8) = lVar12;
            iVar10 = 0;
            if (*(int *)(param_1 + 0xb0) + 1U < *(uint *)(param_1 + 0xb8)) {
              iVar10 = *(int *)(param_1 + 0xb0) + 1;
            }
            *(int *)(param_1 + 0xb0) = iVar10;
          }
          DataMemoryBarrier(2,3);
          *piVar2 = -1;
          DataMemoryBarrier(2,3);
          if (0x14 < *piVar3) {
            do {
              cVar6 = '\x01';
              bVar7 = (bool)ExclusiveMonitorPass(piVar3,0x10);
              if (bVar7) {
                *piVar3 = *piVar3 + -1;
                cVar6 = ExclusiveMonitorsStatus();
              }
            } while (cVar6 != '\0');
            uVar8 = Aska::Semaphore::IsReady() const(lVar4);
            if ((uVar8 & 1) != 0) {
              Aska::Semaphore::Signal() const(lVar4);
            }
          }
          *plVar1 = 0;
        }
        else {
          *(char *)(lVar12 + 0x10) = *(char *)(lVar12 + 0x10) + -1;
        }
      }
      uVar9 = *(uint *)(param_1 + 0xf8);
      uVar11 = *(uint *)(param_1 + 0xf0);
      uVar14 = 0;
      if (uVar13 + 1 < uVar9) {
        uVar14 = uVar13 + 1;
      }
      uVar13 = uVar14;
    } while (uVar14 != uVar11);
    iVar10 = *(int *)(param_1 + 0xf4);
  }
  uVar11 = 0;
  if (iVar10 + 1U < uVar9) {
    uVar11 = iVar10 + 1;
  }
  if (uVar11 != uVar14) {
    do {
      plVar1 = (long *)(*(long *)(param_1 + 0x100) + (ulong)uVar11 * 8);
      if (plVar1 == (long *)0x0) {
        return;
      }
      if (*plVar1 != 0) {
        return;
      }
      iVar5 = 0;
      if (iVar10 + 1U < uVar9) {
        iVar5 = iVar10 + 1;
      }
      uVar11 = 0;
      if (iVar5 + 1U < uVar9) {
        uVar11 = iVar5 + 1;
      }
      *(int *)(param_1 + 0xf4) = iVar5;
      iVar10 = iVar5;
    } while (uVar11 != uVar14);
  }
  return;
}

// ==== Aska::DeleteManager::FlushMain()
// vaddr 0x1f1ed74 | ghidra 0x201ed74 | size 740 | symbol _ZN4Aska13DeleteManager9FlushMainEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska13DeleteManager9FlushMainEv(long param_1)

{
  long *plVar1;
  int *piVar2;
  char cVar3;
  bool bVar4;
  ulong uVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  long lVar9;
  long lVar10;
  int *piVar11;
  
  piVar2 = (int *)(param_1 + 0x40);
  iVar6 = 0;
code_r0x0201ed90:
  do {
    if (*piVar2 == -1) goto code_r0x0201ed9c;
    ClearExclusiveLocal();
    bVar4 = iVar6 < 0x1ff;
    iVar6 = iVar6 + 1;
  } while (bVar4);
  piVar11 = (int *)(param_1 + 0x44);
  do {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar11,0x10);
    if (bVar4) {
      *piVar11 = *piVar11 + 1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
  do {
    if (*piVar2 != -1) {
      ClearExclusiveLocal();
      do {
        uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0x80);
        if ((uVar5 & 1) == 0) {
          do {
            cVar3 = '\x01';
            bVar4 = (bool)ExclusiveMonitorPass(piVar11,0x10);
            if (bVar4) {
              *piVar11 = *piVar11 + -1;
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
          bVar4 = (bool)ExclusiveMonitorPass(piVar11,0x10);
          if (bVar4) {
            *piVar11 = *piVar11 + 1;
            cVar3 = ExclusiveMonitorsStatus();
          }
        } while (cVar3 != '\0');
        while (*piVar2 == -1) {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
          if (bVar4) {
            *piVar2 = 0;
            cVar3 = ExclusiveMonitorsStatus();
          }
          if (cVar3 == '\0') goto code_r0x0201ee48;
        }
        ClearExclusiveLocal();
      } while( true );
    }
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar4) {
      *piVar2 = 0;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
code_r0x0201ee48:
  do {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar11,0x10);
    if (bVar4) {
      *piVar11 = *piVar11 + -1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
code_r0x0201ee58:
  DataMemoryBarrier(2,3);
  uVar7 = *(uint *)(param_1 + 0xd0);
  if (uVar7 <= *(uint *)(param_1 + 0xd4)) {
    uVar7 = *(int *)(param_1 + 0xd8) + uVar7;
  }
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_1 + 0x40) = 0xffffffff;
  DataMemoryBarrier(2,3);
  piVar11 = (int *)(param_1 + 0x44);
  iVar6 = uVar7 + ~*(uint *)(param_1 + 0xd4);
  if (0x14 < *piVar11) {
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar11,0x10);
      if (bVar4) {
        *piVar11 = *piVar11 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
    uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0x80);
    if ((uVar5 & 1) != 0) {
      Aska::Semaphore::Signal() const(param_1 + 0x80);
    }
  }
  lVar9 = param_1 + 0x80;
code_r0x0201eecc:
  uVar7 = 0;
  if (*(int *)(param_1 + 0xd4) + 1U < *(uint *)(param_1 + 0xd8)) {
    uVar7 = *(int *)(param_1 + 0xd4) + 1;
  }
  if (uVar7 == *(uint *)(param_1 + 0xd0)) {
    return 1;
  }
  *(uint *)(param_1 + 0xd4) = uVar7;
  plVar1 = (long *)(*(long *)(param_1 + 0xe0) + (ulong)uVar7 * 8);
  if (plVar1 == (long *)0x0) {
    return 1;
  }
  lVar10 = *plVar1;
  if (lVar10 != 0) {
    Aska::DeleteManager::_DeletePointerInfo::DeletePointer()(lVar10);
    iVar8 = 0;
    do {
      while (*piVar2 != -1) {
        ClearExclusiveLocal();
        bVar4 = 0x1fe < iVar8;
        iVar8 = iVar8 + 1;
        if (bVar4) goto code_r0x0201ef34;
      }
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
      if (bVar4) {
        *piVar2 = 0;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
    goto code_r0x0201efc4;
  }
  goto code_r0x0201f030;
code_r0x0201ed9c:
  cVar3 = '\x01';
  bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
  if (bVar4) {
    *piVar2 = 0;
    cVar3 = ExclusiveMonitorsStatus();
  }
  if (cVar3 == '\0') goto code_r0x0201ee58;
  goto code_r0x0201ed90;
code_r0x0201ef34:
  do {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar11,0x10);
    if (bVar4) {
      *piVar11 = *piVar11 + 1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
  do {
    if (*piVar2 != -1) {
      do {
        ClearExclusiveLocal();
        uVar5 = Aska::Semaphore::IsReady() const(lVar9);
        if ((uVar5 & 1) == 0) {
          do {
            cVar3 = '\x01';
            bVar4 = (bool)ExclusiveMonitorPass(piVar11,0x10);
            if (bVar4) {
              *piVar11 = *piVar11 + -1;
              cVar3 = ExclusiveMonitorsStatus();
            }
          } while (cVar3 != '\0');
          Aska::Thread::Sleep(unsigned int)(1);
        }
        else {
          Aska::Semaphore::Wait() const(lVar9);
        }
        do {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar11,0x10);
          if (bVar4) {
            *piVar11 = *piVar11 + 1;
            cVar3 = ExclusiveMonitorsStatus();
          }
        } while (cVar3 != '\0');
        while (*piVar2 == -1) {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
          if (bVar4) {
            *piVar2 = 0;
            cVar3 = ExclusiveMonitorsStatus();
          }
          if (cVar3 == '\0') goto code_r0x0201efb4;
        }
      } while( true );
    }
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar4) {
      *piVar2 = 0;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
code_r0x0201efb4:
  do {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar11,0x10);
    if (bVar4) {
      *piVar11 = *piVar11 + -1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
code_r0x0201efc4:
  DataMemoryBarrier(2,3);
  if (*(uint *)(param_1 + 0xb4) != *(uint *)(param_1 + 0xb0)) {
    *(long *)(*(long *)(param_1 + 0xc0) + (ulong)*(uint *)(param_1 + 0xb0) * 8) = lVar10;
    iVar8 = 0;
    if (*(int *)(param_1 + 0xb0) + 1U < *(uint *)(param_1 + 0xb8)) {
      iVar8 = *(int *)(param_1 + 0xb0) + 1;
    }
    *(int *)(param_1 + 0xb0) = iVar8;
  }
  DataMemoryBarrier(2,3);
  *piVar2 = -1;
  DataMemoryBarrier(2,3);
  if (0x14 < *piVar11) {
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar11,0x10);
      if (bVar4) {
        *piVar11 = *piVar11 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
    uVar5 = Aska::Semaphore::IsReady() const(lVar9);
    if ((uVar5 & 1) != 0) {
      Aska::Semaphore::Signal() const(lVar9);
    }
  }
code_r0x0201f030:
  iVar6 = iVar6 + -1;
  if (iVar6 == 0) {
    return 0;
  }
  goto code_r0x0201eecc;
}

// ==== Aska::DeleteManager::PostFlushMain()
// vaddr 0x1f1f058 | ghidra 0x201f058 | size 484 | symbol _ZN4Aska13DeleteManager13PostFlushMainEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13DeleteManager13PostFlushMainEv(long param_1)

{
  long *plVar1;
  int *piVar2;
  char cVar3;
  bool bVar4;
  ulong uVar5;
  int iVar6;
  uint uVar7;
  long lVar8;
  int *piVar9;
  
  piVar9 = (int *)(param_1 + 0x40);
  iVar6 = 0;
code_r0x0201f070:
  if (*piVar9 == -1) {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
    if (bVar4) {
      *piVar9 = 0;
      cVar3 = ExclusiveMonitorsStatus();
    }
    if (cVar3 == '\0') goto code_r0x0201f138;
    goto code_r0x0201f070;
  }
  ClearExclusiveLocal();
  bVar4 = iVar6 < 0x1ff;
  iVar6 = iVar6 + 1;
  if (bVar4) goto code_r0x0201f070;
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
    if (*piVar9 != -1) {
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
        while (*piVar9 == -1) {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
          if (bVar4) {
            *piVar9 = 0;
            cVar3 = ExclusiveMonitorsStatus();
          }
          if (cVar3 == '\0') goto code_r0x0201f128;
        }
        ClearExclusiveLocal();
      } while( true );
    }
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
    if (bVar4) {
      *piVar9 = 0;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
code_r0x0201f128:
  do {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar4) {
      *piVar2 = *piVar2 + -1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
code_r0x0201f138:
  DataMemoryBarrier(2,3);
  uVar7 = 0;
  if (*(int *)(param_1 + 0x114) + 1U < *(uint *)(param_1 + 0x118)) {
    uVar7 = *(int *)(param_1 + 0x114) + 1;
  }
  *(long *)(param_1 + 0x128) = param_1 + 0xe8;
  if (uVar7 != *(uint *)(param_1 + 0x110)) {
    do {
      *(uint *)(param_1 + 0x114) = uVar7;
      plVar1 = (long *)(*(long *)(param_1 + 0x120) + (ulong)uVar7 * 8);
      if (plVar1 == (long *)0x0) break;
      lVar8 = *plVar1;
      if (lVar8 != 0) {
        if (*(char *)(lVar8 + 0x10) != '\0') {
          *(char *)(lVar8 + 0x10) = *(char *)(lVar8 + 0x10) + -1;
        }
        if (*(uint *)(param_1 + 0xf4) != *(uint *)(param_1 + 0xf0)) {
          *(long *)(*(long *)(param_1 + 0x100) + (ulong)*(uint *)(param_1 + 0xf0) * 8) = lVar8;
          iVar6 = 0;
          if (*(int *)(param_1 + 0xf0) + 1U < *(uint *)(param_1 + 0xf8)) {
            iVar6 = *(int *)(param_1 + 0xf0) + 1;
          }
          *(int *)(param_1 + 0xf0) = iVar6;
        }
      }
      uVar7 = 0;
      if (*(int *)(param_1 + 0x114) + 1U < *(uint *)(param_1 + 0x118)) {
        uVar7 = *(int *)(param_1 + 0x114) + 1;
      }
    } while (uVar7 != *(uint *)(param_1 + 0x110));
  }
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_1 + 0x40) = 0xffffffff;
  DataMemoryBarrier(2,3);
  piVar9 = (int *)(param_1 + 0x44);
  if (0x14 < *piVar9) {
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
      if (bVar4) {
        *piVar9 = *piVar9 + -1;
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

// ==== Aska::DeleteManager::~DeleteManager()
// vaddr 0x1f1f23c | ghidra 0x201f23c | size 140 | symbol _ZN4Aska13DeleteManagerD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13DeleteManagerD0Ev(long *param_1)

{
  undefined *puVar1;
  
  *param_1 = (long)(PTR__ZTVN4Aska13DeleteManagerE_02cba7a0 + 0x10);
  if (param_1[0x13] != 0) {
    Aska::DeleteManager::Clear()(param_1);
    if (param_1[0x13] != 0) {
      operator delete[](void*)();
    }
    param_1[0x13] = 0;
  }
  puVar1 = PTR__ZTVN4Aska13TDynamicQueueIPNS_13DeleteManager18_DeletePointerInfoELb0EEE_02cbbbb0;
  *(undefined4 *)(param_1 + 0x23) = 0;
  puVar1 = puVar1 + 0x10;
  param_1[0x24] = 0;
  *(undefined4 *)(param_1 + 0x1f) = 0;
  *(undefined4 *)(param_1 + 0x1b) = 0;
  *(undefined4 *)(param_1 + 0x17) = 0;
  param_1[0x21] = (long)puVar1;
  param_1[0x22] = 1;
  param_1[0x1d] = (long)puVar1;
  param_1[0x1e] = 1;
  param_1[0x19] = (long)puVar1;
  param_1[0x1a] = 1;
  param_1[0x20] = 0;
  param_1[0x1c] = 0;
  param_1[0x18] = 0;
  param_1[0x15] = (long)puVar1;
  param_1[0x16] = 1;
  Aska::FastCriticalSection::~FastCriticalSection()(param_1 + 1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::TDynamicQueue<Aska::DeleteManager::_DeletePointerInfo*, false>::~TDynamicQueue()
// vaddr 0x1f1f2c8 | ghidra 0x201f2c8 | size 32 | symbol _ZN4Aska13TDynamicQueueIPNS_13DeleteManager18_DeletePointerInfoELb0EED2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13TDynamicQueueIPNS_13DeleteManager18_DeletePointerInfoELb0EED2Ev(long *param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZTVN4Aska13TDynamicQueueIPNS_13DeleteManager18_DeletePointerInfoELb0EEE_02cbbbb0;
  *(undefined4 *)(param_1 + 2) = 0;
  param_1[3] = 0;
  *param_1 = (long)(puVar1 + 0x10);
  param_1[1] = 1;
  return;
}

// ==== Aska::TDynamicQueue<Aska::DeleteManager::_DeletePointerInfo*, false>::~TDynamicQueue()
// vaddr 0x1f1f2e8 | ghidra 0x201f2e8 | size 4 | symbol _ZN4Aska13TDynamicQueueIPNS_13DeleteManager18_DeletePointerInfoELb0EED0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13TDynamicQueueIPNS_13DeleteManager18_DeletePointerInfoELb0EED0Ev(void)

{
  (*(code *)PTR__ZdlPv_02ca4758)();
  return;
}

// ==== Aska::TSharedPointerCode::CreateCounter(int)
// vaddr 0x1f63054 | ghidra 0x2063054 | size 344 | symbol _ZN4Aska18TSharedPointerCode13CreateCounterEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18TSharedPointerCode13CreateCounterEi(undefined4 param_1)

{
  long lVar1;
  uint uVar2;
  char cVar3;
  bool bVar4;
  int iVar5;
  undefined4 *puVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  
  do {
    if (iRam0000000002dcd4a0 != 0) {
      ClearExclusiveLocal();
      uVar9 = 0;
      do {
        uVar9 = uVar9 + 1;
        if ((uVar9 & 0x1ff) == 0) {
          Aska::Thread::SleepU(unsigned int)(0);
        }
        while (iRam0000000002dcd4a0 == 0) {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(0x2dcd4a0,0x10);
          if (bVar4) {
            iRam0000000002dcd4a0 = 1;
            cVar3 = ExclusiveMonitorsStatus();
          }
          if (cVar3 == '\0') goto code_r0x020630c4;
        }
        ClearExclusiveLocal();
      } while( true );
    }
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(0x2dcd4a0,0x10);
    if (bVar4) {
      iRam0000000002dcd4a0 = 1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
code_r0x020630c4:
  iVar5 = iRam0000000002dcd4a4;
  uVar9 = uRam0000000002dcd8c8;
  if (0xff < iRam0000000002dcd4a4) goto code_r0x02063180;
  uVar9 = uRam0000000002dcd8c8 - 1;
  do {
    if (uVar9 == 0xff) {
      uVar9 = 0;
      goto code_r0x02063120;
    }
    uVar7 = uVar9 + 1;
    lVar1 = (long)((int)uVar7 >> 5) * 4;
    uVar2 = uVar9 + 2;
    uVar8 = 1 << (ulong)(uVar7 & 0x1f);
    uVar9 = uVar7;
  } while ((*(uint *)(lVar1 + 0x2dcd8a8) & uVar8) != 0);
  goto code_r0x02063158;
  while( true ) {
    lVar1 = (long)((int)uVar7 >> 5) * 4;
    uVar8 = 1 << (ulong)(uVar7 & 0x1f);
    uVar9 = uVar7 + 1;
    uVar2 = uVar7 + 1;
    if ((*(uint *)(lVar1 + 0x2dcd8a8) & uVar8) == 0) break;
code_r0x02063120:
    uVar7 = uVar9;
    uVar9 = uVar7;
    if (uRam0000000002dcd8c8 == uVar7) goto code_r0x02063180;
  }
code_r0x02063158:
  uRam0000000002dcd8c8 = uVar2;
  *(uint *)(lVar1 + 0x2dcd8a8) = *(uint *)(lVar1 + 0x2dcd8a8) | uVar8;
  uVar9 = uRam0000000002dcd8c8;
  if (-1 < (int)uVar7) {
    iRam0000000002dcd4a4 = iVar5 + 1;
    *(undefined4 *)((long)(int)uVar7 * 4 + 0x2dcd4a8) = param_1;
    iRam0000000002dcd4a0 = 0;
    return;
  }
code_r0x02063180:
  uRam0000000002dcd8c8 = uVar9;
  iRam0000000002dcd4a0 = 0;
  puVar6 = (undefined4 *)operator new(unsigned long, std::nothrow_t const&)(4,PTR__ZSt7nothrow_02cb9a80);
  if (puVar6 != (undefined4 *)0x0) {
    *puVar6 = param_1;
  }
  return;
}

// ==== Aska::TSharedPointerCode::DeleteCounter(int*)
// vaddr 0x1f631ac | ghidra 0x20631ac | size 244 | symbol _ZN4Aska18TSharedPointerCode13DeleteCounterEPi | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska18TSharedPointerCode13DeleteCounterEPi(ulong param_1)

{
  long lVar1;
  char cVar2;
  bool bVar3;
  uint uVar4;
  uint uVar5;
  
  uVar4 = (uint)(param_1 - 0x2dcd4a8 >> 2);
  if (0x2dcd8a4 < param_1 || param_1 < 0x2dcd4a8) {
    uVar4 = 0xffffffff;
  }
  if ((int)uVar4 < 0) {
    if (param_1 == 0) {
      return 0;
    }
    operator delete(void*)();
  }
  else {
    do {
      if (iRam0000000002dcd4a0 != 0) {
        ClearExclusiveLocal();
        uVar5 = 0;
        do {
          uVar5 = uVar5 + 1;
          if ((uVar5 & 0x1ff) == 0) {
            Aska::Thread::SleepU(unsigned int)(0);
          }
          while (iRam0000000002dcd4a0 == 0) {
            cVar2 = '\x01';
            bVar3 = (bool)ExclusiveMonitorPass(0x2dcd4a0,0x10);
            if (bVar3) {
              iRam0000000002dcd4a0 = 1;
              cVar2 = ExclusiveMonitorsStatus();
            }
            if (cVar2 == '\0') goto code_r0x02063244;
          }
          ClearExclusiveLocal();
        } while( true );
      }
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(0x2dcd4a0,0x10);
      if (bVar3) {
        iRam0000000002dcd4a0 = 1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
code_r0x02063244:
    lVar1 = (long)((int)uVar4 >> 5) * 4;
    uVar5 = *(uint *)(lVar1 + 0x2dcd8a8);
    uVar4 = 1 << (ulong)(uVar4 & 0x1f);
    if ((uVar5 & uVar4) == 0) {
      iRam0000000002dcd4a0 = 0;
      return 0;
    }
    *(uint *)(lVar1 + 0x2dcd8a8) = uVar5 & (uVar4 ^ 0xffffffff);
    iRam0000000002dcd4a4 = iRam0000000002dcd4a4 + -1;
    iRam0000000002dcd4a0 = 0;
  }
  return 1;
}


// FAILED to create function at 0296e910 typeinfo name for Aska::TDynamicQueue<Aska::DeleteManager::_DeletePointerInfo*, false>
// FAILED to create function at 02bb0418 Aska::DeleteManager::vtable
// FAILED to create function at 02bb0438 Aska::DeleteManager::typeinfo
// FAILED to create function at 02bb0448 Aska::TDynamicQueue<Aska::DeleteManager::_DeletePointerInfo*,false>::vtable
// FAILED to create function at 02bb0468 Aska::TDynamicQueue<Aska::DeleteManager::_DeletePointerInfo*,false>::typeinfo
