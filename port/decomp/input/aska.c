// port/decomp/input/aska.c: Ghidra decompiles for the input subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-04 06:12 UTC: tools/decomp.sh '--into' 'input/aska' 'Aska::(Pad|TouchPanel|PeripheralManager|BasePeripheral|Mouse|Keyboard|PadCapture\w*|TouchData|TouchReport)::'

// ==== Aska::Pad::SetAnalogAsDigital(bool)
// vaddr 0x1e8d450 | ghidra 0x1f8d450 | size 344 | symbol _ZN4Aska3Pad18SetAnalogAsDigitalEb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska3Pad18SetAnalogAsDigitalEb(long param_1,byte param_2)

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
                if (cVar3 == '\0') goto code_r0x01f8d590;
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
code_r0x01f8d590:
        do {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
          if (bVar4) {
            *piVar2 = *piVar2 + -1;
            cVar3 = ExclusiveMonitorsStatus();
          }
        } while (cVar3 != '\0');
        DataMemoryBarrier(2,3);
code_r0x01f8d4c8:
        *(byte *)(param_1 + 0x16e) = param_2 & 1;
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
  goto code_r0x01f8d4c8;
}

// ==== Aska::Pad::SetRepeatThreshold(unsigned char)
// vaddr 0x1e8d5a8 | ghidra 0x1f8d5a8 | size 344 | symbol _ZN4Aska3Pad18SetRepeatThresholdEh | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska3Pad18SetRepeatThresholdEh(long param_1,undefined1 param_2)

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
                if (cVar3 == '\0') goto code_r0x01f8d6e8;
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
code_r0x01f8d6e8:
        do {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
          if (bVar4) {
            *piVar2 = *piVar2 + -1;
            cVar3 = ExclusiveMonitorsStatus();
          }
        } while (cVar3 != '\0');
        DataMemoryBarrier(2,3);
code_r0x01f8d620:
        *(undefined1 *)(param_1 + 0x10e) = param_2;
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
  goto code_r0x01f8d620;
}

// ==== Aska::Pad::SetRepeatInterval(unsigned char)
// vaddr 0x1e8d700 | ghidra 0x1f8d700 | size 344 | symbol _ZN4Aska3Pad17SetRepeatIntervalEh | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska3Pad17SetRepeatIntervalEh(long param_1,undefined1 param_2)

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
                if (cVar3 == '\0') goto code_r0x01f8d840;
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
code_r0x01f8d840:
        do {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
          if (bVar4) {
            *piVar2 = *piVar2 + -1;
            cVar3 = ExclusiveMonitorsStatus();
          }
        } while (cVar3 != '\0');
        DataMemoryBarrier(2,3);
code_r0x01f8d778:
        *(undefined1 *)(param_1 + 0x10f) = param_2;
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
  goto code_r0x01f8d778;
}

// ==== Aska::TouchPanel::CopyMessages(Aska::TouchData*)
// vaddr 0x1e9f92c | ghidra 0x1f9f92c | size 672 | symbol _ZN4Aska10TouchPanel12CopyMessagesEPNS_9TouchDataE | lib libSOA-3.7.0.so | 2026-10-04
int _ZN4Aska10TouchPanel12CopyMessagesEPNS_9TouchDataE(long param_1,undefined8 param_2)

{
  int *piVar1;
  char cVar2;
  bool bVar3;
  undefined *puVar4;
  ulong uVar5;
  int iVar6;
  int *piVar7;
  
  puVar4 = PTR__ZN4Aska10TouchPanel11m_criGlobalE_02cb9650;
  piVar7 = (int *)(PTR__ZN4Aska10TouchPanel11m_criGlobalE_02cb9650 + 0x38);
  iVar6 = 0;
code_r0x01f9f954:
  if (*piVar7 == -1) {
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(puVar4 + 0x38,0x10);
    if (bVar3) {
      *(undefined4 *)(puVar4 + 0x38) = 0;
      cVar2 = ExclusiveMonitorsStatus();
    }
    if (cVar2 == '\0') goto code_r0x01f9fa38;
    goto code_r0x01f9f954;
  }
  ClearExclusiveLocal();
  bVar3 = iVar6 < 0x1ff;
  iVar6 = iVar6 + 1;
  if (bVar3) goto code_r0x01f9f954;
  piVar7 = (int *)(puVar4 + 0x3c);
  do {
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar7,0x10);
    if (bVar3) {
      *piVar7 = *piVar7 + 1;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
  do {
    if (*(int *)(puVar4 + 0x38) != -1) {
      ClearExclusiveLocal();
      do {
        uVar5 = Aska::Semaphore::IsReady() const(puVar4 + 0x78);
        if ((uVar5 & 1) == 0) {
          do {
            piVar7 = (int *)(puVar4 + 0x3c);
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
          Aska::Semaphore::Wait() const(puVar4 + 0x78);
        }
        do {
          piVar7 = (int *)(puVar4 + 0x3c);
          cVar2 = '\x01';
          bVar3 = (bool)ExclusiveMonitorPass(piVar7,0x10);
          if (bVar3) {
            *piVar7 = *piVar7 + 1;
            cVar2 = ExclusiveMonitorsStatus();
          }
        } while (cVar2 != '\0');
        while (piVar7 = (int *)(puVar4 + 0x38), *piVar7 == -1) {
          cVar2 = '\x01';
          bVar3 = (bool)ExclusiveMonitorPass(piVar7,0x10);
          if (bVar3) {
            *piVar7 = 0;
            cVar2 = ExclusiveMonitorsStatus();
          }
          if (cVar2 == '\0') goto code_r0x01f9fa24;
        }
        ClearExclusiveLocal();
      } while( true );
    }
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(puVar4 + 0x38,0x10);
    if (bVar3) {
      *(undefined4 *)(puVar4 + 0x38) = 0;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
code_r0x01f9fa24:
  do {
    piVar7 = (int *)(puVar4 + 0x3c);
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar7,0x10);
    if (bVar3) {
      *piVar7 = *piVar7 + -1;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
code_r0x01f9fa38:
  DataMemoryBarrier(2,3);
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
      if (cVar2 == '\0') goto code_r0x01f9fb0c;
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
          if (cVar2 == '\0') goto code_r0x01f9fafc;
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
code_r0x01f9fafc:
  do {
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar3) {
      *piVar1 = *piVar1 + -1;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
code_r0x01f9fb0c:
  DataMemoryBarrier(2,3);
  iVar6 = *(int *)(param_1 + 0x26a8);
  memcpy(param_2,param_1 + 0xa8,(long)iVar6 * 0x98);
  DataMemoryBarrier(2,3);
  *(undefined4 *)(puVar4 + 0x38) = 0xffffffff;
  DataMemoryBarrier(2,3);
  if (0x14 < *(int *)(puVar4 + 0x3c)) {
    piVar7 = (int *)(puVar4 + 0x3c);
    do {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar7,0x10);
      if (bVar3) {
        *piVar7 = *piVar7 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    uVar5 = Aska::Semaphore::IsReady() const(puVar4 + 0x78);
    if ((uVar5 & 1) != 0) {
      Aska::Semaphore::Signal() const(puVar4 + 0x78);
    }
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
      Aska::Semaphore::Signal() const(param_1 + 0x80);
    }
  }
  return iVar6;
}

// ==== Framework::Cocos::CCocosTouch::SetPinchInfo(bool, Aska::TouchPanel::PinchOutInParam const&)
// vaddr 0x1ece670 | ghidra 0x1fce670 | size 28 | symbol _ZN9Framework5Cocos11CCocosTouch12SetPinchInfoEbRKN4Aska10TouchPanel15PinchOutInParamE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework5Cocos11CCocosTouch12SetPinchInfoEbRKN4Aska10TouchPanel15PinchOutInParamE
               (long param_1,byte param_2,undefined8 *param_3)

{
  undefined8 uVar1;
  
  *(byte *)(param_1 + 0xa0) = param_2 & 1;
  uVar1 = param_3[2];
  *(undefined8 *)(param_1 + 0xbc) = param_3[3];
  *(undefined8 *)(param_1 + 0xb4) = uVar1;
  uVar1 = *param_3;
  *(undefined8 *)(param_1 + 0xac) = param_3[1];
  *(undefined8 *)(param_1 + 0xa4) = uVar1;
  return;
}

// ==== Aska::BasePeripheral::~BasePeripheral()
// vaddr 0x1f06150 | ghidra 0x2006150 | size 40 | symbol _ZN4Aska14BasePeripheralD2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska14BasePeripheralD2Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska14BasePeripheralE_02cbc550 + 0x10);
  Aska::FastCriticalSection::~FastCriticalSection()(param_1 + 1);
  (*(code *)PTR__ZN4Aska11IAnimatableD2Ev_02cb13b8)(param_1);
  return;
}

// ==== Aska::PadDroid::SetTriggerThreshold(Aska::Pad::TriggerThreshold, int)
// vaddr 0x1f06250 | ghidra 0x2006250 | size 4 | symbol _ZN4Aska8PadDroid19SetTriggerThresholdENS_3Pad16TriggerThresholdEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska8PadDroid19SetTriggerThresholdENS_3Pad16TriggerThresholdEi(void)

{
  return;
}

// ==== Aska::PadDroid::GetTriggerThreshold(Aska::Pad::TriggerThreshold) const
// vaddr 0x1f06254 | ghidra 0x2006254 | size 8 | symbol _ZNK4Aska8PadDroid19GetTriggerThresholdENS_3Pad16TriggerThresholdE | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska8PadDroid19GetTriggerThresholdENS_3Pad16TriggerThresholdE(void)

{
  return 0x7f;
}

// ==== Aska::TouchPanel::Initialize(unsigned char)
// vaddr 0x1f0625c | ghidra 0x200625c | size 192 | symbol _ZN4Aska10TouchPanel10InitializeEh | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska10TouchPanel10InitializeEh(long param_1,undefined1 param_2)

{
  ushort uVar1;
  ushort uVar2;
  float fVar3;
  undefined *puVar4;
  
  *(undefined1 *)(param_1 + 0x99) = param_2;
  puVar4 = PTR__ZN4Aska6Global14m_pFrameBufferE_02cb8198;
  *(undefined1 *)(param_1 + 0x26c5) = 1;
  *(undefined4 *)(param_1 + 0x28fc) = 0xfa;
  fVar3 = _UNK_027dab9c;
  uVar1 = *(ushort *)(*(long *)puVar4 + 0x18);
  uVar2 = *(ushort *)(*(long *)puVar4 + 0x1a);
  *(undefined8 *)(param_1 + 0x2888) = 0;
  *(undefined8 *)(param_1 + 0x2880) = 0;
  if (uVar1 <= uVar2) {
    uVar1 = uVar2;
  }
  *(undefined4 *)(param_1 + 0x290c) = 3;
  *(undefined4 *)(param_1 + 0x2924) = 3;
  *(undefined4 *)(param_1 + 0x293c) = 3;
  *(undefined4 *)(param_1 + 0x2954) = 3;
  *(undefined4 *)(param_1 + 0x296c) = 3;
  *(undefined4 *)(param_1 + 0x2984) = 3;
  *(undefined4 *)(param_1 + 0x299c) = 3;
  *(undefined4 *)(param_1 + 0x29b4) = 3;
  *(undefined4 *)(param_1 + 0x28d8) = 3;
  *(undefined4 *)(param_1 + 0x26bc) = 0;
  *(undefined4 *)(param_1 + 0x2904) = 0;
  *(undefined4 *)(param_1 + 0x2708) = 0;
  *(int *)(param_1 + 0x26b8) = (int)((float)((uint)uVar1 * 0x50) / fVar3);
  memset(param_1 + 10000,0,0x130);
  *(undefined1 *)(param_1 + 0x9a) = 1;
  return;
}

// ==== Aska::TouchPanel::Enable(bool)
// vaddr 0x1f0631c | ghidra 0x200631c | size 16 | symbol _ZN4Aska10TouchPanel6EnableEb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10TouchPanel6EnableEb(long param_1,byte param_2)

{
  *(byte *)(param_1 + 0x26c5) = param_2 & 1;
  return;
}

// ==== Aska::TouchPanel::ClearGestureParam()
// vaddr 0x1f0632c | ghidra 0x200632c | size 160 | symbol _ZN4Aska10TouchPanel17ClearGestureParamEv | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska10TouchPanel17ClearGestureParamEv(long param_1)

{
  ushort uVar1;
  ushort uVar2;
  float fVar3;
  undefined *puVar4;
  
  puVar4 = PTR__ZN4Aska6Global14m_pFrameBufferE_02cb8198;
  *(undefined4 *)(param_1 + 0x28fc) = 0xfa;
  fVar3 = _UNK_027dab9c;
  uVar1 = *(ushort *)(*(long *)puVar4 + 0x18);
  uVar2 = *(ushort *)(*(long *)puVar4 + 0x1a);
  *(undefined8 *)(param_1 + 0x2888) = 0;
  *(undefined8 *)(param_1 + 0x2880) = 0;
  *(undefined4 *)(param_1 + 0x290c) = 3;
  *(undefined4 *)(param_1 + 0x2924) = 3;
  if (uVar1 <= uVar2) {
    uVar1 = uVar2;
  }
  *(undefined4 *)(param_1 + 0x293c) = 3;
  *(undefined4 *)(param_1 + 0x2954) = 3;
  *(undefined4 *)(param_1 + 0x296c) = 3;
  *(undefined4 *)(param_1 + 0x2984) = 3;
  *(undefined4 *)(param_1 + 0x299c) = 3;
  *(undefined4 *)(param_1 + 0x29b4) = 3;
  *(undefined4 *)(param_1 + 0x28d8) = 3;
  *(undefined4 *)(param_1 + 0x26bc) = 0;
  *(undefined4 *)(param_1 + 0x2904) = 0;
  *(undefined4 *)(param_1 + 0x2708) = 0;
  *(int *)(param_1 + 0x26b8) = (int)((float)((uint)uVar1 * 0x50) / fVar3);
  memset(param_1 + 10000,0,0x130);
  return;
}

// ==== Aska::TouchPanel::CalcDoublTapRange(int)
// vaddr 0x1f063cc | ghidra 0x20063cc | size 56 | symbol _ZN4Aska10TouchPanel17CalcDoublTapRangeEi | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int _ZN4Aska10TouchPanel17CalcDoublTapRangeEi(undefined8 param_1,int param_2)

{
  ushort uVar1;
  ushort uVar2;
  
  uVar1 = *(ushort *)(*(long *)PTR__ZN4Aska6Global14m_pFrameBufferE_02cb8198 + 0x18);
  uVar2 = *(ushort *)(*(long *)PTR__ZN4Aska6Global14m_pFrameBufferE_02cb8198 + 0x1a);
  if (uVar1 <= uVar2) {
    uVar1 = uVar2;
  }
  return (int)((float)(int)((uint)uVar1 * param_2) / _UNK_027dab9c);
}

// ==== Aska::TouchPanel::ResetGestureParam()
// vaddr 0x1f06404 | ghidra 0x2006404 | size 324 | symbol _ZN4Aska10TouchPanel17ResetGestureParamEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10TouchPanel17ResetGestureParamEv(long param_1)

{
  if (0 < *(int *)(param_1 + 0x2880)) {
    *(int *)(param_1 + 0x2884) = *(int *)(param_1 + 0x2880);
  }
  if (0 < *(int *)(param_1 + 0x2888)) {
    *(int *)(param_1 + 0x288c) = *(int *)(param_1 + 0x2888);
  }
  *(undefined4 *)(param_1 + 0x2880) = 0;
  *(undefined4 *)(param_1 + 0x2888) = 0;
  *(undefined4 *)(param_1 + 0x28d4) = 0;
  if (*(int *)(param_1 + 0x290c) == 2) {
    *(undefined4 *)(param_1 + 0x290c) = 3;
    *(undefined4 *)(param_1 + 0x2920) = 0xffffffff;
  }
  *(undefined4 *)(param_1 + 0x2914) = 0;
  if (*(int *)(param_1 + 0x2924) == 2) {
    *(undefined4 *)(param_1 + 0x2924) = 3;
    *(undefined4 *)(param_1 + 0x2938) = 0xffffffff;
  }
  *(undefined4 *)(param_1 + 0x292c) = 0;
  if (*(int *)(param_1 + 0x293c) == 2) {
    *(undefined4 *)(param_1 + 0x293c) = 3;
    *(undefined4 *)(param_1 + 0x2950) = 0xffffffff;
  }
  *(undefined4 *)(param_1 + 0x2944) = 0;
  if (*(int *)(param_1 + 0x2954) == 2) {
    *(undefined4 *)(param_1 + 0x2954) = 3;
    *(undefined4 *)(param_1 + 0x2968) = 0xffffffff;
  }
  *(undefined4 *)(param_1 + 0x295c) = 0;
  if (*(int *)(param_1 + 0x296c) == 2) {
    *(undefined4 *)(param_1 + 0x296c) = 3;
    *(undefined4 *)(param_1 + 0x2980) = 0xffffffff;
  }
  *(undefined4 *)(param_1 + 0x2974) = 0;
  if (*(int *)(param_1 + 0x2984) == 2) {
    *(undefined4 *)(param_1 + 0x2984) = 3;
    *(undefined4 *)(param_1 + 0x2998) = 0xffffffff;
  }
  *(undefined4 *)(param_1 + 0x298c) = 0;
  if (*(int *)(param_1 + 0x299c) == 2) {
    *(undefined4 *)(param_1 + 0x299c) = 3;
    *(undefined4 *)(param_1 + 0x29b0) = 0xffffffff;
  }
  *(undefined4 *)(param_1 + 0x29a4) = 0;
  if (*(int *)(param_1 + 0x29b4) == 2) {
    *(undefined4 *)(param_1 + 0x29b4) = 3;
    *(undefined4 *)(param_1 + 0x29c8) = 0xffffffff;
  }
  *(undefined4 *)(param_1 + 0x29bc) = 0;
  if (*(int *)(param_1 + 0x28d8) == 2) {
    *(undefined4 *)(param_1 + 0x28d8) = 3;
  }
  return;
}

// ==== Aska::TouchPanel::UpdateGesture(Aska::TouchData*, int)
// vaddr 0x1f06548 | ghidra 0x2006548 | size 2428 | symbol _ZN4Aska10TouchPanel13UpdateGestureEPNS_9TouchDataEi | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Removing unreachable block (ram,0x02006820) */

void _ZN4Aska10TouchPanel13UpdateGestureEPNS_9TouchDataEi(long param_1,long param_2,uint param_3)

{
  int *piVar1;
  int *piVar2;
  ulong uVar3;
  ulong uVar4;
  short *psVar5;
  short *psVar6;
  long lVar7;
  int iVar8;
  uint uVar9;
  int iVar10;
  bool bVar11;
  int iVar12;
  undefined8 uVar13;
  ulong uVar14;
  long lVar15;
  long lVar16;
  int *piVar17;
  int *piVar18;
  long lVar19;
  long lVar20;
  long lVar21;
  uint uVar22;
  int iVar23;
  ulong uVar24;
  byte bVar25;
  int *piVar26;
  
  *(undefined4 *)(param_1 + 0x2910) = *(undefined4 *)(param_1 + 0x290c);
  *(undefined4 *)(param_1 + 0x2928) = *(undefined4 *)(param_1 + 0x2924);
  *(undefined4 *)(param_1 + 0x2940) = *(undefined4 *)(param_1 + 0x293c);
  *(undefined4 *)(param_1 + 0x2958) = *(undefined4 *)(param_1 + 0x2954);
  *(undefined4 *)(param_1 + 0x2970) = *(undefined4 *)(param_1 + 0x296c);
  *(undefined4 *)(param_1 + 0x29a0) = *(undefined4 *)(param_1 + 0x299c);
  *(undefined4 *)(param_1 + 0x2988) = *(undefined4 *)(param_1 + 0x2984);
  *(undefined4 *)(param_1 + 0x29b8) = *(undefined4 *)(param_1 + 0x29b4);
  piVar1 = (int *)(param_1 + 0x290c);
  piVar2 = (int *)(param_1 + 0x29cc);
  *(undefined4 *)(param_1 + 0x29d0) = *(undefined4 *)(param_1 + 0x28d8);
  iVar12 = Aska::Global::GetCPUTime()();
  *(int *)(param_1 + 0x2904) = (iVar12 - *(int *)(param_1 + 0x26bc)) + *(int *)(param_1 + 0x2904);
  uVar3 = param_1 + 0x2720;
  lVar15 = 0;
  *(int *)(param_1 + 0x26bc) = iVar12;
  uVar4 = param_1 + 0x2840;
  lVar16 = param_1 + 0x2734;
  lVar20 = param_1 + 0x2894;
  do {
    lVar19 = lVar16 + lVar15;
    if (*(char *)(lVar19 + 8) != '\0') {
      bVar25 = *(byte *)(lVar19 + 10);
      iVar10 = iVar12 - *(int *)(param_1 + lVar15 + 0x2720);
      if (((bVar25 & 1) != 0) && (*(int *)(param_1 + 0x28fc) < iVar10)) {
        bVar25 = bVar25 & 0xfe;
        *(byte *)(lVar19 + 10) = bVar25;
      }
      if ((((~bVar25 & 0xc) == 0) && (*(int *)(param_1 + lVar15 + 0x2734) < iVar10)) &&
         (*(int *)(param_1 + 0x28d4) < 8)) {
        *(undefined2 *)(lVar20 + (long)*(int *)(param_1 + 0x28d4) * 8) =
             *(undefined2 *)(lVar16 + lVar15 + -0xc);
        *(undefined2 *)(lVar20 + (long)*(int *)(param_1 + 0x28d4) * 8 + 2) =
             *(undefined2 *)(lVar16 + lVar15 + -10);
        iVar10 = *(int *)(param_1 + 0x28d4);
        *(undefined4 *)(lVar20 + (long)iVar10 * 8 + 4) = *(undefined4 *)(param_1 + lVar15 + 0x2738);
        *(int *)(param_1 + 0x28d4) = iVar10 + 1;
      }
    }
    lVar15 = lVar15 + 0x24;
  } while ((lVar16 + lVar15) - 0x14U < uVar4);
  if ((*(int *)(param_1 + 0x28fc) < *(int *)(param_1 + 0x2904)) &&
     ((0 < *(int *)(param_1 + 0x2880) || (0 < *(int *)(param_1 + 0x2884))))) {
    *(undefined8 *)(param_1 + 0x2880) = 0;
    *(undefined8 *)(param_1 + 0x2888) = 0;
    *(undefined8 *)(param_1 + 0x26de) = 0xffffffffffffffff;
    *(undefined8 *)(param_1 + 0x26d6) = 0xffffffffffffffff;
    *(undefined8 *)(param_1 + 0x26ce) = 0xffffffffffffffff;
    *(undefined8 *)(param_1 + 0x26c6) = 0xffffffffffffffff;
  }
  if (0 < (int)param_3) {
    psVar5 = (short *)(param_1 + 0x2918);
    psVar6 = (short *)(param_1 + 0x291a);
    uVar14 = 0;
    lVar15 = param_1 + 0x2730;
    do {
      lVar16 = param_2 + uVar14 * 0x98;
      iVar10 = *(int *)(lVar16 + 0xc);
      if (0 < iVar10) {
        lVar20 = param_2 + uVar14 * 0x98;
        piVar26 = (int *)(lVar20 + 0x18);
code_r0x02006824:
        switch(*(undefined2 *)((long)piVar26 + 10)) {
        case 1:
          uVar13 = Aska::TouchPanel::SetOrRegisterOriginInfo(Aska::TouchReport&, unsigned int)(param_1,piVar26,*(undefined4 *)(lVar20 + 8));
          Aska::TouchPanel::StartGestureCheck(Aska::TouchOrigin*)(param_1,uVar13);
          piVar17 = (int *)0x0;
          piVar18 = piVar1;
          do {
            if ((piVar18[5] == *piVar26) && (*piVar18 != 3)) goto code_r0x02006ad4;
            if ((piVar17 == (int *)0x0) && (piVar17 = piVar18, *piVar18 != 3)) {
              piVar17 = (int *)0x0;
            }
            piVar18 = piVar18 + 6;
          } while (piVar18 < piVar2);
          piVar18 = piVar17;
          if (piVar17 != (int *)0x0) {
code_r0x02006ad4:
            *piVar18 = 0;
            piVar18[2] = 0;
            *(undefined2 *)(piVar18 + 3) = *(undefined2 *)((long)piVar26 + 6);
            *(short *)((long)piVar18 + 0xe) = (short)piVar26[2];
            *(undefined2 *)(piVar18 + 4) = *(undefined2 *)((long)piVar26 + 6);
            *(short *)((long)piVar18 + 0x12) = (short)piVar26[2];
            piVar18[5] = *piVar26;
          }
          break;
        case 2:
          iVar23 = *piVar26;
          lVar19 = 0;
          do {
            if ((*(char *)(lVar15 + lVar19 + 0xc) != '\0') &&
               (*(int *)(param_1 + lVar19 + 0x2738) == iVar23)) {
              iVar8 = *(int *)(param_1 + lVar19 + 0x2724);
              lVar21 = lVar15 + lVar19 + -0x10;
              if ((iVar8 != 0) && (399 < (uint)(iVar12 - iVar8))) {
                Aska::TouchPanel::ClearGlobalFlags(Aska::TouchOrigin*, unsigned char)(param_1,lVar21,3);
                goto code_r0x02006de0;
              }
              bVar25 = *(byte *)(lVar15 + lVar19 + 0xe);
              if ((bVar25 & 1) != 0) {
                uVar22 = 0;
                uVar24 = uVar3;
                goto code_r0x02006cac;
              }
              if ((bVar25 >> 1 & 1) == 0) goto code_r0x02006de0;
              uVar22 = 0;
              uVar24 = uVar3;
              goto code_r0x02006b78;
            }
            lVar19 = lVar19 + 0x24;
          } while ((lVar15 + lVar19) - 0x10U < uVar4);
          goto code_r0x02006dfc;
        case 3:
          uVar24 = uVar3;
          do {
            if ((*(char *)(uVar24 + 0x1c) != '\0') && (*(int *)(uVar24 + 0x18) == *piVar26)) {
              *(undefined2 *)(uVar24 + 8) = *(undefined2 *)((long)piVar26 + 6);
              *(short *)(uVar24 + 10) = (short)piVar26[2];
              Aska::TouchPanel::CheckRange(Aska::TouchReport&)(param_1,piVar26);
              piVar17 = (int *)0x0;
              piVar18 = piVar1;
              goto code_r0x02006a7c;
            }
            uVar24 = uVar24 + 0x24;
          } while (uVar24 < uVar4);
          Aska::TouchPanel::CheckRange(Aska::TouchReport&)(param_1,piVar26);
          piVar17 = (int *)0x0;
          piVar18 = piVar1;
          do {
            if ((piVar18[5] == *piVar26) && (iVar23 = *piVar18, iVar23 != 3)) goto code_r0x02006b0c;
            if ((piVar17 == (int *)0x0) && (piVar17 = piVar18, *piVar18 != 3)) {
              piVar17 = (int *)0x0;
            }
            piVar18 = piVar18 + 6;
          } while (piVar18 < piVar2);
          if (((piVar17 != (int *)0x0) && (piVar17[5] == *piVar26)) &&
             (iVar23 = *piVar17, piVar18 = piVar17, iVar23 != 3)) {
code_r0x02006b0c:
            *(short *)(piVar18 + 2) = *(short *)((long)piVar26 + 6) - *psVar5;
            *(short *)((long)piVar18 + 10) = (short)piVar26[2] - *psVar6;
            *(undefined2 *)(piVar18 + 3) = *(undefined2 *)((long)piVar26 + 6);
            *(short *)((long)piVar18 + 0xe) = (short)piVar26[2];
            if (piVar18[1] == iVar23) {
              *piVar18 = 1;
            }
          }
          break;
        case 4:
          uVar24 = uVar3;
          do {
            if (*(char *)(uVar24 + 0x1c) != '\0') {
              Aska::TouchPanel::OffAndDeregisterOriginInfo(Aska::TouchOrigin*, unsigned int)(param_1,uVar24,iVar12);
            }
            uVar24 = uVar24 + 0x24;
          } while (uVar24 < uVar4);
          if (*piVar1 != 3) {
            *piVar1 = 2;
          }
          if (*(int *)(param_1 + 0x2924) != 3) {
            *(undefined4 *)(param_1 + 0x2924) = 2;
          }
          if (*(int *)(param_1 + 0x293c) != 3) {
            *(undefined4 *)(param_1 + 0x293c) = 2;
          }
          if (*(int *)(param_1 + 0x2954) != 3) {
            *(undefined4 *)(param_1 + 0x2954) = 2;
          }
          if (*(int *)(param_1 + 0x296c) != 3) {
            *(undefined4 *)(param_1 + 0x296c) = 2;
          }
          if (*(int *)(param_1 + 0x2984) != 3) {
            *(undefined4 *)(param_1 + 0x2984) = 2;
          }
          if (*(int *)(param_1 + 0x299c) != 3) {
            *(undefined4 *)(param_1 + 0x299c) = 2;
          }
          if (*(int *)(param_1 + 0x29b4) != 3) {
            *(undefined4 *)(param_1 + 0x29b4) = 2;
          }
        }
        goto code_r0x02006e84;
      }
code_r0x02006e90:
      uVar14 = uVar14 + 1;
    } while (uVar14 != param_3);
  }
  return;
  while( true ) {
    if ((piVar17 == (int *)0x0) && (piVar17 = piVar18, *piVar18 != 3)) {
      piVar17 = (int *)0x0;
    }
    piVar18 = piVar18 + 6;
    if (piVar2 <= piVar18) break;
code_r0x02006a7c:
    if ((piVar18[5] == *piVar26) && (iVar23 = *piVar18, iVar23 != 3)) goto code_r0x02006bb8;
  }
  if (((piVar17 != (int *)0x0) && (piVar17[5] == *piVar26)) &&
     (iVar23 = *piVar17, piVar18 = piVar17, iVar23 != 3)) {
code_r0x02006bb8:
    *(short *)(piVar18 + 2) = *(short *)((long)piVar26 + 6) - *psVar5;
    *(short *)((long)piVar18 + 10) = (short)piVar26[2] - *psVar6;
    *(undefined2 *)(piVar18 + 3) = *(undefined2 *)((long)piVar26 + 6);
    *(short *)((long)piVar18 + 0xe) = (short)piVar26[2];
    if (piVar18[1] == iVar23) {
      *piVar18 = 1;
    }
  }
  if ((*(byte *)(uVar24 + 0x1e) & 3) == 0) {
    if (*(int *)(param_1 + 0x28d8) == 3) {
      lVar19 = *(long *)(param_1 + 10000);
      if ((lVar19 == 0) || (lVar21 = *(long *)(param_1 + 0x2718), lVar21 == 0)) {
        *(undefined4 *)(param_1 + 0x28d8) = 3;
      }
      else {
        *(undefined8 *)(param_1 + 0x28d8) = 0x3f80000000000000;
        *(undefined2 *)(param_1 + 0x28e0) = *(undefined2 *)(lVar19 + 8);
        *(undefined2 *)(param_1 + 0x28e2) = *(undefined2 *)(lVar19 + 10);
        *(undefined2 *)(param_1 + 0x28e4) = *(undefined2 *)(lVar21 + 8);
        *(undefined2 *)(param_1 + 0x28e6) = *(undefined2 *)(lVar21 + 10);
        *(undefined8 *)(param_1 + 0x28e8) = 0;
        *(undefined2 *)(param_1 + 0x28f0) = *(undefined2 *)(lVar19 + 8);
        *(undefined2 *)(param_1 + 0x28f2) = *(undefined2 *)(lVar19 + 10);
        *(undefined2 *)(param_1 + 0x28f4) = *(undefined2 *)(lVar21 + 8);
        *(undefined2 *)(param_1 + 0x28f6) = *(undefined2 *)(lVar21 + 10);
      }
    }
    else {
      Aska::TouchPanel::SetPinchOutInActive()(param_1);
    }
  }
  goto code_r0x02006e84;
code_r0x02006cac:
  do {
    if (*(char *)(uVar24 + 0x1c) != '\0') {
      if (iVar23 == *(int *)(uVar24 + 0x18)) {
        uVar22 = (uint)*(byte *)(uVar24 + 0x1d);
      }
      else if (*(int *)(param_1 + lVar19 + 0x2730) == *(int *)(uVar24 + 0x10)) {
        bVar11 = false;
        goto code_r0x02006d04;
      }
    }
    uVar24 = uVar24 + 0x24;
  } while (uVar24 < uVar4);
  bVar11 = true;
code_r0x02006d04:
  iVar23 = *(int *)(param_1 + 0x2708);
  if (iVar23 < 8) {
    *(int *)(param_1 + 0x2708) = iVar23 + 1;
    lVar7 = param_1 + (long)iVar23 * 4;
    *(undefined2 *)(lVar7 + 0x26e6) = *(undefined2 *)(lVar15 + lVar19 + -8);
    *(undefined2 *)(lVar7 + 0x26e8) = *(undefined2 *)(lVar15 + lVar19 + -6);
    if ((bVar11) && (uVar9 = *(uint *)(param_1 + 0x2708), uVar9 == uVar22)) {
      memcpy(param_1 + 0x26c6,param_1 + 0x26e6,(ulong)uVar22 << 2);
      *(undefined4 *)(param_1 + 0x2904) = 0;
      *(uint *)(param_1 + 0x2880) = uVar9;
      *(undefined4 *)(param_1 + 0x2888) = 1;
    }
  }
  goto code_r0x02006de0;
code_r0x02006b78:
  do {
    if (*(char *)(uVar24 + 0x1c) != '\0') {
      if (iVar23 == *(int *)(uVar24 + 0x18)) {
        uVar22 = (uint)*(byte *)(uVar24 + 0x1d);
      }
      else if (*(int *)(param_1 + lVar19 + 0x2730) == *(int *)(uVar24 + 0x10)) {
        bVar11 = false;
        goto code_r0x02006d78;
      }
    }
    uVar24 = uVar24 + 0x24;
  } while (uVar24 < uVar4);
  bVar11 = true;
code_r0x02006d78:
  iVar23 = *(int *)(param_1 + 0x2708);
  if (iVar23 < 8) {
    *(int *)(param_1 + 0x2708) = iVar23 + 1;
    lVar7 = param_1 + (long)iVar23 * 4;
    *(undefined2 *)(lVar7 + 0x26e6) = *(undefined2 *)(lVar15 + lVar19 + -8);
    *(undefined2 *)(lVar7 + 0x26e8) = *(undefined2 *)(lVar15 + lVar19 + -6);
    if ((bVar11) && (uVar9 = *(uint *)(param_1 + 0x2708), uVar9 == uVar22)) {
      memcpy(param_1 + 0x26c6,param_1 + 0x26e6,(ulong)uVar22 << 2);
      *(undefined4 *)(param_1 + 0x2888) = 2;
      *(undefined4 *)(param_1 + 0x2904) = 0;
      *(uint *)(param_1 + 0x2880) = uVar9;
    }
  }
code_r0x02006de0:
  Aska::TouchPanel::SetPinchOutInEnd()(param_1);
  Aska::TouchPanel::OffAndDeregisterOriginInfo(Aska::TouchOrigin*, unsigned int)(param_1,lVar21,iVar12);
  iVar23 = *piVar26;
code_r0x02006dfc:
  piVar17 = (int *)0x0;
  piVar18 = piVar1;
  do {
    if ((piVar18[5] == iVar23) && (*piVar18 != 3)) goto code_r0x02006e48;
    if ((piVar17 == (int *)0x0) && (piVar17 = piVar18, *piVar18 != 3)) {
      piVar17 = (int *)0x0;
    }
    piVar18 = piVar18 + 6;
  } while (piVar18 < piVar2);
  if ((piVar17 != (int *)0x0) && (piVar18 = piVar17, iVar23 == piVar17[5])) {
code_r0x02006e48:
    *piVar18 = 2;
    *(short *)(piVar18 + 2) = *(short *)((long)piVar26 + 6) - *psVar5;
    *(short *)((long)piVar18 + 10) = (short)piVar26[2] - *psVar6;
    *(undefined2 *)(piVar18 + 3) = *(undefined2 *)((long)piVar26 + 6);
    *(short *)((long)piVar18 + 0xe) = (short)piVar26[2];
  }
code_r0x02006e84:
  piVar26 = piVar26 + 4;
  if ((int *)(lVar16 + (long)iVar10 * 0x10 + 0x18U) <= piVar26) goto code_r0x02006e90;
  goto code_r0x02006824;
}

// ==== Aska::TouchPanel::UpdateGestureFlags(unsigned int)
// vaddr 0x1f06ec4 | ghidra 0x2006ec4 | size 256 | symbol _ZN4Aska10TouchPanel18UpdateGestureFlagsEj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10TouchPanel18UpdateGestureFlagsEj(long param_1,int param_2)

{
  long lVar1;
  int iVar2;
  int *piVar3;
  byte bVar4;
  
  piVar3 = (int *)(param_1 + 0x2720);
  lVar1 = param_1 + 0x2894;
  do {
    if ((char)piVar3[7] != '\0') {
      bVar4 = *(byte *)((long)piVar3 + 0x1e);
      if (((bVar4 & 1) != 0) && (*(int *)(param_1 + 0x28fc) < param_2 - *piVar3)) {
        bVar4 = bVar4 & 0xfe;
        *(byte *)((long)piVar3 + 0x1e) = bVar4;
      }
      if ((((~bVar4 & 0xc) == 0) && (piVar3[5] < param_2 - *piVar3)) &&
         (*(int *)(param_1 + 0x28d4) < 8)) {
        *(short *)(lVar1 + (long)*(int *)(param_1 + 0x28d4) * 8) = (short)piVar3[2];
        *(undefined2 *)(lVar1 + (long)*(int *)(param_1 + 0x28d4) * 8 + 2) =
             *(undefined2 *)((long)piVar3 + 10);
        iVar2 = *(int *)(param_1 + 0x28d4);
        *(int *)(lVar1 + (long)iVar2 * 8 + 4) = piVar3[6];
        *(int *)(param_1 + 0x28d4) = iVar2 + 1;
      }
    }
    piVar3 = piVar3 + 9;
  } while (piVar3 < (int *)(param_1 + 0x2840U));
  if ((*(int *)(param_1 + 0x28fc) < *(int *)(param_1 + 0x2904)) &&
     ((0 < *(int *)(param_1 + 0x2880) || (0 < *(int *)(param_1 + 0x2884))))) {
    *(undefined8 *)(param_1 + 0x2888) = 0;
    *(undefined8 *)(param_1 + 0x2880) = 0;
    *(undefined8 *)(param_1 + 0x26de) = 0xffffffffffffffff;
    *(undefined8 *)(param_1 + 0x26d6) = 0xffffffffffffffff;
    *(undefined8 *)(param_1 + 0x26ce) = 0xffffffffffffffff;
    *(undefined8 *)(param_1 + 0x26c6) = 0xffffffffffffffff;
  }
  return;
}

// ==== Aska::TouchPanel::SetOrRegisterOriginInfo(Aska::TouchReport&, unsigned int)
// vaddr 0x1f06fc4 | ghidra 0x2006fc4 | size 996 | symbol _ZN4Aska10TouchPanel23SetOrRegisterOriginInfoERNS_11TouchReportEj | lib libSOA-3.7.0.so | 2026-10-04
int * _ZN4Aska10TouchPanel23SetOrRegisterOriginInfoERNS_11TouchReportEj
                (long param_1,int *param_2,int param_3)

{
  int iVar1;
  uint uVar2;
  undefined2 uVar3;
  int iVar4;
  undefined *puVar5;
  uint uVar6;
  int *piVar7;
  ulong uVar8;
  ulong uVar9;
  uint uVar10;
  int *piVar11;
  int **ppiVar12;
  int **ppiVar13;
  int *piVar14;
  int *apiStack_40 [8];
  
  iVar1 = *param_2;
  apiStack_40[0] = (int *)(param_1 + 0x2720);
  piVar14 = apiStack_40[0];
  piVar11 = (int *)0x0;
  do {
    if ((char)piVar14[7] == '\0') {
      piVar7 = piVar14;
      if (piVar11 != (int *)0x0) {
        piVar7 = piVar11;
      }
    }
    else {
      piVar7 = piVar11;
      if (iVar1 == piVar14[6]) {
        uVar3 = *(undefined2 *)((long)param_2 + 6);
        iVar1 = param_2[2];
        *piVar14 = param_3;
        piVar14[1] = 0;
        piVar14[4] = 0;
        *(undefined2 *)((long)piVar14 + 0x1d) = 0xed00;
        *(undefined2 *)(piVar14 + 2) = uVar3;
        *(short *)((long)piVar14 + 10) = (short)iVar1;
        *(undefined2 *)(piVar14 + 3) = uVar3;
        *(short *)((long)piVar14 + 0xe) = (short)iVar1;
        *(undefined1 *)((long)piVar14 + 0x1f) = 0xff;
        piVar7 = piVar14;
        goto code_r0x020070a0;
      }
    }
    piVar14 = piVar14 + 9;
    piVar11 = piVar7;
  } while (piVar14 < (int *)(param_1 + 0x2840U));
  if (piVar7 == (int *)0x0) {
    return (int *)0x0;
  }
  uVar3 = *(undefined2 *)((long)param_2 + 6);
  iVar4 = param_2[2];
  *piVar7 = param_3;
  piVar7[1] = 0;
  piVar7[4] = 0;
  piVar7[5] = 500;
  *(undefined2 *)(piVar7 + 2) = uVar3;
  *(short *)((long)piVar7 + 10) = (short)iVar4;
  *(undefined2 *)(piVar7 + 3) = uVar3;
  *(short *)((long)piVar7 + 0xe) = (short)iVar4;
  piVar7[6] = iVar1;
  piVar7[7] = -0x12ffff;
  if (*(long *)(param_1 + 10000) == 0) {
    *(int **)(param_1 + 10000) = piVar7;
  }
  else if (*(long *)(param_1 + 0x2718) == 0) {
    *(int **)(param_1 + 0x2718) = piVar7;
  }
code_r0x020070a0:
  puVar5 = PTR__ZN4Aska11TouchOrigin14m_nGroupIDBaseE_02cbb438;
  ppiVar12 = apiStack_40;
  ppiVar13 = apiStack_40;
  uVar10 = (uint)*(byte *)(param_1 + 0x273c);
  if (*(byte *)(param_1 + 0x273c) == 0) {
code_r0x020070d4:
    uVar8 = 0;
  }
  else {
    if (399 < (uint)(param_3 - *apiStack_40[0])) {
      uVar10 = 0;
      goto code_r0x020070d4;
    }
    uVar10 = *(uint *)(param_1 + 0x2730);
    uVar8 = 1;
  }
  if (((*(char *)(param_1 + 0x2760) != '\0') && ((uint)(param_3 - *(int *)(param_1 + 0x2744)) < 400)
      ) && ((uVar2 = *(uint *)(param_1 + 0x2754), uVar6 = uVar2, uVar10 == 0 ||
            ((uVar6 = uVar10, uVar2 == 0 || (uVar10 == uVar2)))))) {
    uVar10 = uVar6;
    apiStack_40[uVar8] = (int *)(param_1 + 0x2744);
    uVar8 = (ulong)((int)uVar8 + 1);
  }
  uVar9 = uVar8;
  if (((*(char *)(param_1 + 0x2784) != '\0') && ((uint)(param_3 - *(int *)(param_1 + 0x2768)) < 400)
      ) && ((uVar2 = *(uint *)(param_1 + 0x2778), uVar6 = uVar2, uVar10 == 0 ||
            ((uVar6 = uVar10, uVar2 == 0 || (uVar10 == uVar2)))))) {
    uVar10 = uVar6;
    uVar9 = (ulong)((int)uVar8 + 1);
    apiStack_40[uVar8] = (int *)(param_1 + 0x2768);
  }
  uVar8 = uVar9;
  if (((*(char *)(param_1 + 0x27a8) != '\0') && ((uint)(param_3 - *(int *)(param_1 + 0x278c)) < 400)
      ) && ((uVar2 = *(uint *)(param_1 + 0x279c), uVar6 = uVar2, uVar10 == 0 ||
            ((uVar6 = uVar10, uVar2 == 0 || (uVar10 == uVar2)))))) {
    uVar10 = uVar6;
    uVar8 = (ulong)((int)uVar9 + 1);
    apiStack_40[uVar9] = (int *)(param_1 + 0x278c);
  }
  if ((*(char *)(param_1 + 0x27cc) != '\0') && ((uint)(param_3 - *(int *)(param_1 + 0x27b0)) < 400))
  {
    if (uVar10 == 0) {
      uVar10 = *(uint *)(param_1 + 0x27c0);
      uVar2 = *(uint *)(param_1 + 0x27c0);
    }
    else {
      uVar2 = *(uint *)(param_1 + 0x27c0);
    }
    if ((uVar2 == 0) || (uVar10 == uVar2)) {
      apiStack_40[uVar8] = (int *)(param_1 + 0x27b0);
      uVar8 = (ulong)((int)uVar8 + 1);
    }
  }
  if ((*(char *)(param_1 + 0x27f0) != '\0') && ((uint)(param_3 - *(int *)(param_1 + 0x27d4)) < 400))
  {
    if (uVar10 == 0) {
      uVar10 = *(uint *)(param_1 + 0x27e4);
      uVar2 = *(uint *)(param_1 + 0x27e4);
    }
    else {
      uVar2 = *(uint *)(param_1 + 0x27e4);
    }
    if ((uVar2 == 0) || (uVar10 == uVar2)) {
      apiStack_40[uVar8] = (int *)(param_1 + 0x27d4);
      uVar8 = (ulong)((int)uVar8 + 1);
    }
  }
  if ((*(char *)(param_1 + 0x2814) != '\0') && ((uint)(param_3 - *(int *)(param_1 + 0x27f8)) < 400))
  {
    if (uVar10 == 0) {
      uVar10 = *(uint *)(param_1 + 0x2808);
      uVar2 = *(uint *)(param_1 + 0x2808);
    }
    else {
      uVar2 = *(uint *)(param_1 + 0x2808);
    }
    if ((uVar2 == 0) || (uVar10 == uVar2)) {
      apiStack_40[uVar8] = (int *)(param_1 + 0x27f8);
      uVar8 = (ulong)((int)uVar8 + 1);
    }
  }
  if ((*(char *)(param_1 + 0x2838) != '\0') && ((uint)(param_3 - *(int *)(param_1 + 0x281c)) < 400))
  {
    if (uVar10 == 0) {
      uVar10 = *(uint *)(param_1 + 0x282c);
      uVar2 = *(uint *)(param_1 + 0x282c);
    }
    else {
      uVar2 = *(uint *)(param_1 + 0x282c);
    }
    if ((uVar2 == 0) || (uVar10 == uVar2)) {
      apiStack_40[uVar8] = (int *)(param_1 + 0x281c);
      uVar8 = (ulong)((int)uVar8 + 1);
      goto code_r0x02007334;
    }
  }
  if ((int)uVar8 == 0) {
    return piVar7;
  }
code_r0x02007334:
  if (uVar10 == 0) {
    do {
      piVar14 = *ppiVar13;
      *(char *)((long)piVar14 + 0x1d) = (char)uVar8;
      if (piVar14[4] == 0) {
        iVar1 = *(int *)puVar5 + 1;
        *(int *)puVar5 = iVar1;
        piVar14[4] = iVar1;
        *(undefined4 *)(param_1 + 0x2708) = 0;
      }
      ppiVar13 = ppiVar13 + 1;
    } while (ppiVar13 < apiStack_40 + uVar8);
  }
  else {
    do {
      piVar14 = *ppiVar12;
      *(char *)((long)piVar14 + 0x1d) = (char)uVar8;
      if (piVar14[4] == 0) {
        piVar14[4] = uVar10;
      }
      ppiVar12 = ppiVar12 + 1;
    } while (ppiVar12 < apiStack_40 + uVar8);
  }
  return piVar7;
}

// ==== Aska::TouchPanel::StartGestureCheck(Aska::TouchOrigin*)
// vaddr 0x1f073a8 | ghidra 0x20073a8 | size 516 | symbol _ZN4Aska10TouchPanel17StartGestureCheckEPNS_11TouchOriginE | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Possible PIC construction at 0x02007564: Changing call to branch */
/* WARNING: Removing unreachable block (ram,0x02007568) */

void _ZN4Aska10TouchPanel17StartGestureCheckEPNS_11TouchOriginE(long param_1,long param_2)

{
  long lVar1;
  uint uVar2;
  int iVar3;
  bool bVar4;
  ulong uVar5;
  long lVar6;
  ulong *puVar7;
  ulong uVar8;
  uint uVar9;
  int iVar10;
  int iVar11;
  ulong auStack_70 [8];
  
  if (param_2 != 0) {
    uVar2 = *(uint *)(param_1 + 0x2884);
    if (uVar2 == *(byte *)(param_2 + 0x1d)) {
      iVar3 = *(int *)(param_2 + 0x10);
      if (((int)uVar2 < 1) || (*(int *)(param_1 + 0x288c) != 1)) {
code_r0x011e5a30:
        (*(code *)PTR__ZN4Aska10TouchPanel19ClearDoubleTapFlagsEi_02caad08)(param_1,iVar3);
        return;
      }
      uVar9 = 0;
      uVar5 = param_1 + 0x2720;
      auStack_70[5] = 0;
      auStack_70[4] = 0;
      auStack_70[7] = 0;
      auStack_70[6] = 0;
      auStack_70[1] = 0;
      auStack_70[0] = 0;
      auStack_70[3] = 0;
      auStack_70[2] = 0;
      do {
        if (*(char *)(uVar5 + 0x1c) != '\0') {
          if (iVar3 != *(int *)(uVar5 + 0x10)) {
            Aska::TouchPanel::ClearDoubleTapFlags(int)(param_1,iVar3);
            bVar4 = false;
            if ((int)uVar9 < 1) goto code_r0x02007518;
            goto code_r0x0200747c;
          }
          auStack_70[(int)uVar9] = uVar5;
          uVar9 = uVar9 + 1;
        }
        uVar5 = uVar5 + 0x24;
      } while (uVar5 < param_1 + 0x2840U);
      bVar4 = true;
      if (0 < (int)uVar9) {
code_r0x0200747c:
        uVar5 = 0;
        do {
          lVar1 = param_1 + uVar5 * 4;
          lVar6 = 0;
          do {
            uVar8 = auStack_70[lVar6];
            if (*(char *)(uVar8 + 0x1f) < '\0') {
              iVar10 = MP_INT_ABS((int)*(short *)(uVar8 + 8) - (int)*(short *)(lVar1 + 0x26e6));
              iVar11 = MP_INT_ABS((int)*(short *)(uVar8 + 10) - (int)*(short *)(lVar1 + 0x26e8));
              if ((iVar11 + iVar10 <= *(int *)(param_1 + 0x26b8)) &&
                 (*(int *)(param_1 + 0x2904) <= *(int *)(param_1 + 0x28fc))) {
                *(char *)(uVar8 + 0x1f) = (char)uVar5;
                break;
              }
            }
            lVar6 = lVar6 + 1;
          } while (lVar6 < (int)uVar9);
          uVar5 = uVar5 + 1;
        } while (uVar5 != uVar2);
      }
code_r0x02007518:
      if ((bVar4) && (0 < (int)uVar9)) {
        lVar6 = 0;
        bVar4 = false;
        do {
          puVar7 = auStack_70 + lVar6;
          lVar6 = lVar6 + 1;
          bVar4 = (bool)(bVar4 | *(char *)(*puVar7 + 0x1f) < '\0');
          if ((int)uVar9 <= lVar6) break;
        } while (-1 < *(char *)(*puVar7 + 0x1f));
        if (bVar4) goto code_r0x011e5a30;
        if (0 < (int)uVar9) {
          uVar5 = (ulong)uVar9;
          puVar7 = auStack_70;
          do {
            uVar5 = uVar5 - 1;
            *(byte *)(*puVar7 + 0x1e) = *(byte *)(*puVar7 + 0x1e) & 0xfc | 2;
            puVar7 = puVar7 + 1;
          } while (uVar5 != 0);
        }
      }
    }
  }
  return;
}

// ==== Aska::TouchPanel::SetDragBegin(Aska::TouchReport&)
// vaddr 0x1f075ac | ghidra 0x20075ac | size 140 | symbol _ZN4Aska10TouchPanel12SetDragBeginERNS_11TouchReportE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10TouchPanel12SetDragBeginERNS_11TouchReportE(long param_1,int *param_2)

{
  int *piVar1;
  int *piVar2;
  
  piVar1 = (int *)0x0;
  piVar2 = (int *)(param_1 + 0x290c);
  do {
    if ((piVar2[5] == *param_2) && (*piVar2 != 3)) goto code_r0x02007604;
    if ((piVar1 == (int *)0x0) && (piVar1 = piVar2, *piVar2 != 3)) {
      piVar1 = (int *)0x0;
    }
    piVar2 = piVar2 + 6;
  } while (piVar2 < (int *)(param_1 + 0x29cc));
  piVar2 = piVar1;
  if (piVar1 == (int *)0x0) {
    return;
  }
code_r0x02007604:
  *piVar2 = 0;
  piVar2[2] = 0;
  *(undefined2 *)(piVar2 + 3) = *(undefined2 *)((long)param_2 + 6);
  *(short *)((long)piVar2 + 0xe) = (short)param_2[2];
  *(undefined2 *)(piVar2 + 4) = *(undefined2 *)((long)param_2 + 6);
  *(short *)((long)piVar2 + 0x12) = (short)param_2[2];
  piVar2[5] = *param_2;
  return;
}

// ==== Aska::TouchPanel::FindOrigin(unsigned int)
// vaddr 0x1f07638 | ghidra 0x2007638 | size 60 | symbol _ZN4Aska10TouchPanel10FindOriginEj | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZN4Aska10TouchPanel10FindOriginEj(long param_1,int param_2)

{
  ulong uVar1;
  
  uVar1 = param_1 + 0x2720;
  while ((*(char *)(uVar1 + 0x1c) == '\0' || (*(int *)(uVar1 + 0x18) != param_2))) {
    uVar1 = uVar1 + 0x24;
    if (param_1 + 0x2840U <= uVar1) {
      return 0;
    }
  }
  return uVar1;
}

// ==== Aska::TouchPanel::SetTap(Aska::TouchOrigin*, int)
// vaddr 0x1f07674 | ghidra 0x2007674 | size 224 | symbol _ZN4Aska10TouchPanel6SetTapEPNS_11TouchOriginEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10TouchPanel6SetTapEPNS_11TouchOriginEi(long param_1,long param_2,undefined4 param_3)

{
  long lVar1;
  uint uVar2;
  int iVar3;
  bool bVar4;
  uint uVar5;
  ulong uVar6;
  
  uVar5 = 0;
  uVar6 = param_1 + 0x2720;
  do {
    if (*(char *)(uVar6 + 0x1c) != '\0') {
      if (*(int *)(param_2 + 0x18) == *(int *)(uVar6 + 0x18)) {
        uVar5 = (uint)*(byte *)(uVar6 + 0x1d);
      }
      else if (*(int *)(param_2 + 0x10) == *(int *)(uVar6 + 0x10)) {
        bVar4 = false;
        goto code_r0x020076e0;
      }
    }
    uVar6 = uVar6 + 0x24;
  } while (uVar6 < param_1 + 0x2840U);
  bVar4 = true;
code_r0x020076e0:
  iVar3 = *(int *)(param_1 + 0x2708);
  if (iVar3 < 8) {
    *(int *)(param_1 + 0x2708) = iVar3 + 1;
    lVar1 = param_1 + (long)iVar3 * 4;
    *(undefined2 *)(lVar1 + 0x26e6) = *(undefined2 *)(param_2 + 8);
    *(undefined2 *)(lVar1 + 0x26e8) = *(undefined2 *)(param_2 + 10);
    if ((bVar4) && (uVar2 = *(uint *)(param_1 + 0x2708), uVar2 == uVar5)) {
      memcpy(param_1 + 0x26c6,param_1 + 0x26e6,(ulong)uVar5 << 2);
      *(uint *)(param_1 + 0x2880) = uVar2;
      *(undefined4 *)(param_1 + 0x2888) = param_3;
      *(undefined4 *)(param_1 + 0x2904) = 0;
    }
  }
  return;
}

// ==== Aska::TouchPanel::ClearGlobalFlags(Aska::TouchOrigin*, unsigned char)
// vaddr 0x1f07754 | ghidra 0x2007754 | size 332 | symbol _ZN4Aska10TouchPanel16ClearGlobalFlagsEPNS_11TouchOriginEh | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10TouchPanel16ClearGlobalFlagsEPNS_11TouchOriginEh
               (long param_1,long param_2,byte param_3)

{
  int iVar1;
  
  iVar1 = *(int *)(param_2 + 0x10);
  param_3 = ~param_3;
  if ((*(char *)(param_1 + 0x273c) != '\0') && (iVar1 == *(int *)(param_1 + 0x2730))) {
    *(byte *)(param_1 + 0x273e) = *(byte *)(param_1 + 0x273e) & param_3;
  }
  if ((*(char *)(param_1 + 0x2760) != '\0') && (iVar1 == *(int *)(param_1 + 0x2754))) {
    *(byte *)(param_1 + 0x2762) = *(byte *)(param_1 + 0x2762) & param_3;
  }
  if ((*(char *)(param_1 + 0x2784) != '\0') && (iVar1 == *(int *)(param_1 + 0x2778))) {
    *(byte *)(param_1 + 0x2786) = *(byte *)(param_1 + 0x2786) & param_3;
  }
  if ((*(char *)(param_1 + 0x27a8) != '\0') && (iVar1 == *(int *)(param_1 + 0x279c))) {
    *(byte *)(param_1 + 0x27aa) = *(byte *)(param_1 + 0x27aa) & param_3;
  }
  if ((*(char *)(param_1 + 0x27cc) != '\0') && (iVar1 == *(int *)(param_1 + 0x27c0))) {
    *(byte *)(param_1 + 0x27ce) = *(byte *)(param_1 + 0x27ce) & param_3;
  }
  if ((*(char *)(param_1 + 0x27f0) != '\0') && (iVar1 == *(int *)(param_1 + 0x27e4))) {
    *(byte *)(param_1 + 0x27f2) = *(byte *)(param_1 + 0x27f2) & param_3;
  }
  if ((*(char *)(param_1 + 0x2814) != '\0') && (iVar1 == *(int *)(param_1 + 0x2808))) {
    *(byte *)(param_1 + 0x2816) = *(byte *)(param_1 + 0x2816) & param_3;
  }
  if ((*(char *)(param_1 + 0x2838) != '\0') && (iVar1 == *(int *)(param_1 + 0x282c))) {
    *(byte *)(param_1 + 0x283a) = *(byte *)(param_1 + 0x283a) & param_3;
  }
  return;
}

// ==== Aska::TouchPanel::SetPinchOutInEnd()
// vaddr 0x1f078a0 | ghidra 0x20078a0 | size 324 | symbol _ZN4Aska10TouchPanel16SetPinchOutInEndEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10TouchPanel16SetPinchOutInEndEv(long param_1)

{
  int iVar1;
  short sVar2;
  short sVar3;
  short sVar4;
  int iVar5;
  int iVar6;
  long lVar7;
  long lVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  
  if (*(int *)(param_1 + 0x28d8) != 3) {
    lVar8 = *(long *)(param_1 + 10000);
    lVar7 = *(long *)(param_1 + 0x2718);
    *(undefined4 *)(param_1 + 0x28d8) = 2;
    if ((lVar8 != 0) && (lVar7 != 0)) {
      *(short *)(param_1 + 0x28e8) = *(short *)(lVar8 + 8) - *(short *)(param_1 + 0x28e0);
      *(short *)(param_1 + 0x28ea) = *(short *)(lVar8 + 10) - *(short *)(param_1 + 0x28e2);
      *(short *)(param_1 + 0x28ec) = *(short *)(lVar7 + 8) - *(short *)(param_1 + 0x28e4);
      *(short *)(param_1 + 0x28ee) = *(short *)(lVar7 + 10) - *(short *)(param_1 + 0x28e6);
      sVar2 = *(short *)(lVar8 + 8);
      *(short *)(param_1 + 0x28e0) = sVar2;
      sVar3 = *(short *)(lVar8 + 10);
      *(short *)(param_1 + 0x28e2) = sVar3;
      sVar4 = *(short *)(lVar7 + 8);
      *(short *)(param_1 + 0x28e4) = sVar4;
      iVar5 = (int)sVar2 - (int)sVar4;
      iVar1 = -iVar5;
      if (-1 < iVar5) {
        iVar1 = iVar5;
      }
      iVar6 = (int)sVar3 - (int)*(short *)(lVar7 + 10);
      iVar5 = -iVar6;
      if (-1 < iVar6) {
        iVar5 = iVar6;
      }
      fVar11 = SQRT((float)(iVar1 * iVar1 + iVar5 * iVar5));
      *(short *)(param_1 + 0x28e6) = *(short *)(lVar7 + 10);
      if (NAN(fVar11)) {
        fVar11 = (float)sqrtf();
      }
      iVar5 = (int)*(short *)(param_1 + 0x28f0) - (int)*(short *)(param_1 + 0x28f4);
      iVar1 = -iVar5;
      if (-1 < iVar5) {
        iVar1 = iVar5;
      }
      iVar6 = (int)*(short *)(param_1 + 0x28f2) - (int)*(short *)(param_1 + 0x28f6);
      iVar5 = -iVar6;
      if (-1 < iVar6) {
        iVar5 = iVar6;
      }
      fVar10 = (float)(iVar1 * iVar1 + iVar5 * iVar5);
      fVar9 = SQRT(fVar10);
      if (NAN(fVar9)) {
        fVar9 = (float)sqrtf(fVar10);
      }
      *(float *)(param_1 + 0x28dc) = fVar11 / fVar9;
    }
  }
  return;
}

// ==== Aska::TouchPanel::OffAndDeregisterOriginInfo(Aska::TouchOrigin*, unsigned int)
// vaddr 0x1f079e4 | ghidra 0x20079e4 | size 348 | symbol _ZN4Aska10TouchPanel26OffAndDeregisterOriginInfoEPNS_11TouchOriginEj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10TouchPanel26OffAndDeregisterOriginInfoEPNS_11TouchOriginEj
               (long param_1,long param_2,undefined4 param_3)

{
  int iVar1;
  long lVar2;
  
  *(undefined1 *)(param_2 + 0x1c) = 0;
  iVar1 = *(int *)(param_2 + 0x10);
  if (((*(char *)(param_1 + 0x273c) != '\0') && (iVar1 == *(int *)(param_1 + 0x2730))) &&
     (*(int *)(param_1 + 0x2724) == 0)) {
    *(undefined4 *)(param_1 + 0x2724) = param_3;
  }
  if (((*(char *)(param_1 + 0x2760) != '\0') && (iVar1 == *(int *)(param_1 + 0x2754))) &&
     (*(int *)(param_1 + 0x2748) == 0)) {
    *(undefined4 *)(param_1 + 0x2748) = param_3;
  }
  if (((*(char *)(param_1 + 0x2784) != '\0') && (iVar1 == *(int *)(param_1 + 0x2778))) &&
     (*(int *)(param_1 + 0x276c) == 0)) {
    *(undefined4 *)(param_1 + 0x276c) = param_3;
  }
  if (((*(char *)(param_1 + 0x27a8) != '\0') && (iVar1 == *(int *)(param_1 + 0x279c))) &&
     (*(int *)(param_1 + 0x2790) == 0)) {
    *(undefined4 *)(param_1 + 0x2790) = param_3;
  }
  if (((*(char *)(param_1 + 0x27cc) != '\0') && (iVar1 == *(int *)(param_1 + 0x27c0))) &&
     (*(int *)(param_1 + 0x27b4) == 0)) {
    *(undefined4 *)(param_1 + 0x27b4) = param_3;
  }
  if (((*(char *)(param_1 + 0x27f0) != '\0') && (iVar1 == *(int *)(param_1 + 0x27e4))) &&
     (*(int *)(param_1 + 0x27d8) == 0)) {
    *(undefined4 *)(param_1 + 0x27d8) = param_3;
  }
  if (((*(char *)(param_1 + 0x2814) != '\0') && (iVar1 == *(int *)(param_1 + 0x2808))) &&
     (*(int *)(param_1 + 0x27fc) == 0)) {
    *(undefined4 *)(param_1 + 0x27fc) = param_3;
  }
  if (((*(char *)(param_1 + 0x2838) != '\0') && (iVar1 == *(int *)(param_1 + 0x282c))) &&
     (*(int *)(param_1 + 0x2820) == 0)) {
    *(undefined4 *)(param_1 + 0x2820) = param_3;
  }
  if (*(long *)(param_1 + 10000) == param_2) {
    lVar2 = 0;
  }
  else {
    if (*(long *)(param_1 + 0x2718) != param_2) {
      return;
    }
    lVar2 = 1;
  }
  *(undefined8 *)(param_1 + lVar2 * 8 + 10000) = 0;
  return;
}

// ==== Aska::TouchPanel::SetDragEnd(Aska::TouchReport&)
// vaddr 0x1f07b40 | ghidra 0x2007b40 | size 180 | symbol _ZN4Aska10TouchPanel10SetDragEndERNS_11TouchReportE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10TouchPanel10SetDragEndERNS_11TouchReportE(long param_1,int *param_2)

{
  int *piVar1;
  int *piVar2;
  
  piVar1 = (int *)0x0;
  piVar2 = (int *)(param_1 + 0x290c);
  do {
    if ((piVar2[5] == *param_2) && (*piVar2 != 3)) goto code_r0x02007bb0;
    if ((piVar1 == (int *)0x0) && (piVar1 = piVar2, *piVar2 != 3)) {
      piVar1 = (int *)0x0;
    }
    piVar2 = piVar2 + 6;
  } while (piVar2 < (int *)(param_1 + 0x29cc));
  if ((piVar1 != (int *)0x0) && (piVar2 = piVar1, *param_2 == piVar1[5])) {
code_r0x02007bb0:
    *piVar2 = 2;
    *(short *)(piVar2 + 2) = *(short *)((long)param_2 + 6) - *(short *)(param_1 + 0x2918);
    *(short *)((long)piVar2 + 10) = (short)param_2[2] - *(short *)(param_1 + 0x291a);
    *(undefined2 *)(piVar2 + 3) = *(undefined2 *)((long)param_2 + 6);
    *(short *)((long)piVar2 + 0xe) = (short)param_2[2];
  }
  return;
}

// ==== Aska::TouchPanel::CheckRange(Aska::TouchReport&)
// vaddr 0x1f07bf4 | ghidra 0x2007bf4 | size 576 | symbol _ZN4Aska10TouchPanel10CheckRangeERNS_11TouchReportE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10TouchPanel10CheckRangeERNS_11TouchReportE(long param_1,int *param_2)

{
  int iVar1;
  ulong uVar2;
  int iVar3;
  int iVar4;
  
  iVar1 = *param_2;
  uVar2 = param_1 + 0x2720;
  while ((*(char *)(uVar2 + 0x1c) == '\0' || (iVar1 != *(int *)(uVar2 + 0x18)))) {
    uVar2 = uVar2 + 0x24;
    if (param_1 + 0x2840U <= uVar2) {
      return;
    }
  }
  if ((*(byte *)(uVar2 + 0x1e) & 7) == 0) {
    return;
  }
  iVar3 = MP_INT_ABS((int)*(short *)((long)param_2 + 6) - (int)*(short *)(uVar2 + 0xc));
  iVar4 = MP_INT_ABS((int)(short)param_2[2] - (int)*(short *)(uVar2 + 0xe));
  if (iVar4 + iVar3 <= *(int *)(param_1 + 0x26b8)) {
    return;
  }
  *(byte *)(uVar2 + 0x1e) = *(byte *)(uVar2 + 0x1e) & 0xf8;
  if (*(byte *)(uVar2 + 0x1d) < 2) {
    return;
  }
  iVar3 = *(int *)(uVar2 + 0x10);
  if (((*(char *)(param_1 + 0x273c) != '\0') && (iVar1 != *(int *)(param_1 + 0x2738))) &&
     (iVar3 == *(int *)(param_1 + 0x2730))) {
    *(byte *)(param_1 + 0x273e) = *(byte *)(param_1 + 0x273e) & 0xfc;
  }
  if (((*(char *)(param_1 + 0x2760) != '\0') && (iVar1 != *(int *)(param_1 + 0x275c))) &&
     (iVar3 == *(int *)(param_1 + 0x2754))) {
    *(byte *)(param_1 + 0x2762) = *(byte *)(param_1 + 0x2762) & 0xfc;
  }
  if (((*(char *)(param_1 + 0x2784) != '\0') && (iVar1 != *(int *)(param_1 + 0x2780))) &&
     (iVar3 == *(int *)(param_1 + 0x2778))) {
    *(byte *)(param_1 + 0x2786) = *(byte *)(param_1 + 0x2786) & 0xfc;
  }
  if (((*(char *)(param_1 + 0x27a8) != '\0') && (iVar1 != *(int *)(param_1 + 0x27a4))) &&
     (iVar3 == *(int *)(param_1 + 0x279c))) {
    *(byte *)(param_1 + 0x27aa) = *(byte *)(param_1 + 0x27aa) & 0xfc;
  }
  if (((*(char *)(param_1 + 0x27cc) != '\0') && (iVar1 != *(int *)(param_1 + 0x27c8))) &&
     (iVar3 == *(int *)(param_1 + 0x27c0))) {
    *(byte *)(param_1 + 0x27ce) = *(byte *)(param_1 + 0x27ce) & 0xfc;
  }
  if (((*(char *)(param_1 + 0x27f0) != '\0') && (iVar1 != *(int *)(param_1 + 0x27ec))) &&
     (iVar3 == *(int *)(param_1 + 0x27e4))) {
    *(byte *)(param_1 + 0x27f2) = *(byte *)(param_1 + 0x27f2) & 0xfc;
  }
  if (((*(char *)(param_1 + 0x2814) != '\0') && (iVar1 != *(int *)(param_1 + 0x2810))) &&
     (iVar3 == *(int *)(param_1 + 0x2808))) {
    *(byte *)(param_1 + 0x2816) = *(byte *)(param_1 + 0x2816) & 0xfc;
  }
  if (*(char *)(param_1 + 0x2838) == '\0') {
    return;
  }
  if (iVar1 == *(int *)(param_1 + 0x2834)) {
    return;
  }
  if (iVar3 != *(int *)(param_1 + 0x282c)) {
    return;
  }
  *(byte *)(param_1 + 0x283a) = *(byte *)(param_1 + 0x283a) & 0xfc;
  return;
}

// ==== Aska::TouchPanel::SetDragActive(Aska::TouchReport&)
// vaddr 0x1f07e34 | ghidra 0x2007e34 | size 192 | symbol _ZN4Aska10TouchPanel13SetDragActiveERNS_11TouchReportE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10TouchPanel13SetDragActiveERNS_11TouchReportE(long param_1,int *param_2)

{
  int *piVar1;
  int *piVar2;
  
  piVar1 = (int *)0x0;
  piVar2 = (int *)(param_1 + 0x290c);
  do {
    if ((piVar2[5] == *param_2) && (*piVar2 != 3)) goto code_r0x02007e98;
    if ((piVar1 == (int *)0x0) && (piVar1 = piVar2, *piVar2 != 3)) {
      piVar1 = (int *)0x0;
    }
    piVar2 = piVar2 + 6;
  } while (piVar2 < (int *)(param_1 + 0x29cc));
  if ((piVar1 != (int *)0x0) && (piVar2 = piVar1, piVar1[5] == *param_2)) {
code_r0x02007e98:
    if (*piVar2 != 3) {
      *(short *)(piVar2 + 2) = *(short *)((long)param_2 + 6) - *(short *)(param_1 + 0x2918);
      *(short *)((long)piVar2 + 10) = (short)param_2[2] - *(short *)(param_1 + 0x291a);
      *(undefined2 *)(piVar2 + 3) = *(undefined2 *)((long)param_2 + 6);
      *(short *)((long)piVar2 + 0xe) = (short)param_2[2];
      if (piVar2[1] == *piVar2) {
        *piVar2 = 1;
      }
    }
  }
  return;
}

// ==== Aska::TouchPanel::SetPinchOutInBegin()
// vaddr 0x1f07ef4 | ghidra 0x2007ef4 | size 152 | symbol _ZN4Aska10TouchPanel18SetPinchOutInBeginEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10TouchPanel18SetPinchOutInBeginEv(long param_1)

{
  long lVar1;
  long lVar2;
  
  lVar2 = *(long *)(param_1 + 10000);
  if (((lVar2 != 0) && (lVar1 = *(long *)(param_1 + 0x2718), lVar1 != 0)) &&
     (*(int *)(param_1 + 0x28d8) == 3)) {
    *(undefined8 *)(param_1 + 0x28d8) = 0x3f80000000000000;
    *(undefined2 *)(param_1 + 0x28e0) = *(undefined2 *)(lVar2 + 8);
    *(undefined2 *)(param_1 + 0x28e2) = *(undefined2 *)(lVar2 + 10);
    *(undefined2 *)(param_1 + 0x28e4) = *(undefined2 *)(lVar1 + 8);
    *(undefined2 *)(param_1 + 0x28e6) = *(undefined2 *)(lVar1 + 10);
    *(undefined8 *)(param_1 + 0x28e8) = 0;
    *(undefined2 *)(param_1 + 0x28f0) = *(undefined2 *)(lVar2 + 8);
    *(undefined2 *)(param_1 + 0x28f2) = *(undefined2 *)(lVar2 + 10);
    *(undefined2 *)(param_1 + 0x28f4) = *(undefined2 *)(lVar1 + 8);
    *(undefined2 *)(param_1 + 0x28f6) = *(undefined2 *)(lVar1 + 10);
    return;
  }
  *(undefined4 *)(param_1 + 0x28d8) = 3;
  return;
}

// ==== Aska::TouchPanel::SetPinchOutInActive()
// vaddr 0x1f07f8c | ghidra 0x2007f8c | size 348 | symbol _ZN4Aska10TouchPanel19SetPinchOutInActiveEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10TouchPanel19SetPinchOutInActiveEv(long param_1)

{
  int iVar1;
  short sVar2;
  short sVar3;
  short sVar4;
  int iVar5;
  int iVar6;
  long lVar7;
  long lVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  
  lVar7 = *(long *)(param_1 + 10000);
  if (((lVar7 == 0) || (lVar8 = *(long *)(param_1 + 0x2718), lVar8 == 0)) ||
     (1 < *(uint *)(param_1 + 0x28d8))) {
    *(undefined4 *)(param_1 + 0x28d8) = 3;
  }
  else {
    if (*(uint *)(param_1 + 0x29d0) == *(uint *)(param_1 + 0x28d8)) {
      *(undefined4 *)(param_1 + 0x28d8) = 1;
    }
    *(short *)(param_1 + 0x28e8) = *(short *)(lVar7 + 8) - *(short *)(param_1 + 0x28e0);
    *(short *)(param_1 + 0x28ea) = *(short *)(lVar7 + 10) - *(short *)(param_1 + 0x28e2);
    *(short *)(param_1 + 0x28ec) = *(short *)(lVar8 + 8) - *(short *)(param_1 + 0x28e4);
    *(short *)(param_1 + 0x28ee) = *(short *)(lVar8 + 10) - *(short *)(param_1 + 0x28e6);
    sVar2 = *(short *)(lVar7 + 8);
    *(short *)(param_1 + 0x28e0) = sVar2;
    sVar3 = *(short *)(lVar7 + 10);
    *(short *)(param_1 + 0x28e2) = sVar3;
    sVar4 = *(short *)(lVar8 + 8);
    *(short *)(param_1 + 0x28e4) = sVar4;
    iVar5 = (int)sVar2 - (int)sVar4;
    iVar1 = -iVar5;
    if (-1 < iVar5) {
      iVar1 = iVar5;
    }
    iVar6 = (int)sVar3 - (int)*(short *)(lVar8 + 10);
    iVar5 = -iVar6;
    if (-1 < iVar6) {
      iVar5 = iVar6;
    }
    fVar11 = SQRT((float)(iVar1 * iVar1 + iVar5 * iVar5));
    *(short *)(param_1 + 0x28e6) = *(short *)(lVar8 + 10);
    if (NAN(fVar11)) {
      fVar11 = (float)sqrtf();
    }
    iVar5 = (int)*(short *)(param_1 + 0x28f0) - (int)*(short *)(param_1 + 0x28f4);
    iVar1 = -iVar5;
    if (-1 < iVar5) {
      iVar1 = iVar5;
    }
    iVar6 = (int)*(short *)(param_1 + 0x28f2) - (int)*(short *)(param_1 + 0x28f6);
    iVar5 = -iVar6;
    if (-1 < iVar6) {
      iVar5 = iVar6;
    }
    fVar10 = (float)(iVar1 * iVar1 + iVar5 * iVar5);
    fVar9 = SQRT(fVar10);
    if (NAN(fVar9)) {
      fVar9 = (float)sqrtf(fVar10);
    }
    *(float *)(param_1 + 0x28dc) = fVar11 / fVar9;
  }
  return;
}

// ==== Aska::TouchPanel::ClearDoubleTapFlags(int)
// vaddr 0x1f080e8 | ghidra 0x20080e8 | size 452 | symbol _ZN4Aska10TouchPanel19ClearDoubleTapFlagsEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10TouchPanel19ClearDoubleTapFlagsEi(long param_1,int param_2)

{
  if ((*(char *)(param_1 + 0x273c) != '\0') && (*(int *)(param_1 + 0x2730) == param_2)) {
    *(undefined1 *)(param_1 + 0x273f) = 0xff;
    *(byte *)(param_1 + 0x273e) = *(byte *)(param_1 + 0x273e) & 0xfc | 1;
  }
  if ((*(char *)(param_1 + 0x2760) != '\0') && (*(int *)(param_1 + 0x2754) == param_2)) {
    *(undefined1 *)(param_1 + 0x2763) = 0xff;
    *(byte *)(param_1 + 0x2762) = *(byte *)(param_1 + 0x2762) & 0xfc | 1;
  }
  if ((*(char *)(param_1 + 0x2784) != '\0') && (*(int *)(param_1 + 0x2778) == param_2)) {
    *(undefined1 *)(param_1 + 0x2787) = 0xff;
    *(byte *)(param_1 + 0x2786) = *(byte *)(param_1 + 0x2786) & 0xfc | 1;
  }
  if ((*(char *)(param_1 + 0x27a8) != '\0') && (*(int *)(param_1 + 0x279c) == param_2)) {
    *(undefined1 *)(param_1 + 0x27ab) = 0xff;
    *(byte *)(param_1 + 0x27aa) = *(byte *)(param_1 + 0x27aa) & 0xfc | 1;
  }
  if ((*(char *)(param_1 + 0x27cc) != '\0') && (*(int *)(param_1 + 0x27c0) == param_2)) {
    *(undefined1 *)(param_1 + 0x27cf) = 0xff;
    *(byte *)(param_1 + 0x27ce) = *(byte *)(param_1 + 0x27ce) & 0xfc | 1;
  }
  if ((*(char *)(param_1 + 0x27f0) != '\0') && (*(int *)(param_1 + 0x27e4) == param_2)) {
    *(undefined1 *)(param_1 + 0x27f3) = 0xff;
    *(byte *)(param_1 + 0x27f2) = *(byte *)(param_1 + 0x27f2) & 0xfc | 1;
  }
  if ((*(char *)(param_1 + 0x2814) != '\0') && (*(int *)(param_1 + 0x2808) == param_2)) {
    *(undefined1 *)(param_1 + 0x2817) = 0xff;
    *(byte *)(param_1 + 0x2816) = *(byte *)(param_1 + 0x2816) & 0xfc | 1;
  }
  if ((*(char *)(param_1 + 0x2838) != '\0') && (*(int *)(param_1 + 0x282c) == param_2)) {
    *(undefined1 *)(param_1 + 0x283b) = 0xff;
    *(byte *)(param_1 + 0x283a) = *(byte *)(param_1 + 0x283a) & 0xfc | 1;
  }
  return;
}

// ==== Aska::TouchPanel::SetTouchAndHold(Aska::TouchOrigin*)
// vaddr 0x1f082ac | ghidra 0x20082ac | size 76 | symbol _ZN4Aska10TouchPanel15SetTouchAndHoldEPNS_11TouchOriginE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10TouchPanel15SetTouchAndHoldEPNS_11TouchOriginE(long param_1,long param_2)

{
  long lVar1;
  int iVar2;
  
  if (*(int *)(param_1 + 0x28d4) < 8) {
    lVar1 = param_1 + 0x2894;
    *(undefined2 *)(lVar1 + (long)*(int *)(param_1 + 0x28d4) * 8) = *(undefined2 *)(param_2 + 8);
    *(undefined2 *)(lVar1 + (long)*(int *)(param_1 + 0x28d4) * 8 + 2) =
         *(undefined2 *)(param_2 + 10);
    iVar2 = *(int *)(param_1 + 0x28d4);
    *(undefined4 *)(lVar1 + (long)iVar2 * 8 + 4) = *(undefined4 *)(param_2 + 0x18);
    *(int *)(param_1 + 0x28d4) = iVar2 + 1;
  }
  return;
}

// ==== Aska::TouchPanel::FindDragParam(unsigned int)
// vaddr 0x1f082f8 | ghidra 0x20082f8 | size 88 | symbol _ZN4Aska10TouchPanel13FindDragParamEj | lib libSOA-3.7.0.so | 2026-10-04
int * _ZN4Aska10TouchPanel13FindDragParamEj(long param_1,int param_2)

{
  int *piVar1;
  int *piVar2;
  
  piVar1 = (int *)0x0;
  piVar2 = (int *)(param_1 + 0x290c);
  do {
    if ((piVar2[5] == param_2) && (*piVar2 != 3)) {
      return piVar2;
    }
    if ((piVar1 == (int *)0x0) && (piVar1 = piVar2, *piVar2 != 3)) {
      piVar1 = (int *)0x0;
    }
    piVar2 = piVar2 + 6;
  } while (piVar2 < (int *)(param_1 + 0x29ccU));
  return piVar1;
}

// ==== Aska::TouchPanel::SetDragPos(Aska::TouchReport&, Aska::TouchPanel::DragParam*)
// vaddr 0x1f08350 | ghidra 0x2008350 | size 60 | symbol _ZN4Aska10TouchPanel10SetDragPosERNS_11TouchReportEPNS0_9DragParamE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10TouchPanel10SetDragPosERNS_11TouchReportEPNS0_9DragParamE
               (long param_1,long param_2,long param_3)

{
  *(short *)(param_3 + 8) = *(short *)(param_2 + 6) - *(short *)(param_1 + 0x2918);
  *(short *)(param_3 + 10) = *(short *)(param_2 + 8) - *(short *)(param_1 + 0x291a);
  *(undefined2 *)(param_3 + 0xc) = *(undefined2 *)(param_2 + 6);
  *(undefined2 *)(param_3 + 0xe) = *(undefined2 *)(param_2 + 8);
  return;
}

// ==== Aska::TouchPanel::GetTap(Aska::TouchPanel::Vector2*, int)
// vaddr 0x1f0838c | ghidra 0x200838c | size 300 | symbol _ZN4Aska10TouchPanel6GetTapEPNS0_7Vector2Ei | lib libSOA-3.7.0.so | 2026-10-04
int _ZN4Aska10TouchPanel6GetTapEPNS0_7Vector2Ei(long param_1,undefined4 *param_2,int param_3)

{
  ulong uVar1;
  undefined8 *puVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  ulong uVar6;
  ulong uVar7;
  undefined8 *puVar8;
  undefined8 *puVar9;
  undefined8 uVar10;
  undefined8 uVar11;
  undefined8 uVar12;
  
  iVar3 = 0;
  if ((param_2 != (undefined4 *)0x0) && (param_3 != 0)) {
    if (*(int *)(param_1 + 0x2888) != 1) {
      return 0;
    }
    iVar3 = *(int *)(param_1 + 0x2880);
    if (param_3 <= *(int *)(param_1 + 0x2880)) {
      iVar3 = param_3;
    }
    if (0 < iVar3) {
      uVar1 = param_1 + (long)iVar3 * 4 + 0x26c6;
      if (uVar1 <= param_1 + 0x26caU) {
        uVar1 = param_1 + 0x26caU;
      }
      uVar1 = (uVar1 + (-0x26c7 - param_1) >> 2) + 1;
      puVar4 = (undefined4 *)(param_1 + 0x26c6);
      if ((7 < uVar1) && (uVar6 = uVar1 & 0x7ffffffffffffff8, uVar6 != 0)) {
        uVar7 = param_1 + (long)iVar3 * 4 + 0x26c6;
        if (uVar7 <= param_1 + 0x26caU) {
          uVar7 = param_1 + 0x26caU;
        }
        uVar7 = uVar7 + (-0x26c7 - param_1) & 0xfffffffffffffffc;
        if (((undefined4 *)(param_1 + uVar7 + 0x26ca) <= param_2) ||
           ((long)param_2 + uVar7 + 4 <= param_1 + 0x26c6U)) {
          puVar8 = (undefined8 *)(param_2 + 4);
          puVar4 = (undefined4 *)(param_1 + 0x26c6U + uVar6 * 4);
          param_2 = param_2 + uVar6;
          puVar9 = (undefined8 *)(param_1 + 0x26d6);
          uVar7 = uVar6;
          do {
            puVar2 = puVar9 + -1;
            uVar10 = puVar9[-2];
            uVar12 = puVar9[1];
            uVar11 = *puVar9;
            uVar7 = uVar7 - 8;
            puVar9 = puVar9 + 4;
            puVar8[-1] = *puVar2;
            puVar8[-2] = uVar10;
            puVar8[1] = uVar12;
            *puVar8 = uVar11;
            puVar8 = puVar8 + 4;
          } while (uVar7 != 0);
          if (uVar1 == uVar6) {
            return iVar3;
          }
        }
      }
      do {
        puVar5 = puVar4 + 1;
        *param_2 = *puVar4;
        param_2 = param_2 + 1;
        puVar4 = puVar5;
      } while (puVar5 < (undefined4 *)(param_1 + (long)iVar3 * 4 + 0x26c6U));
    }
  }
  return iVar3;
}

// ==== Aska::TouchPanel::GetDoubleTap(Aska::TouchPanel::Vector2*, int)
// vaddr 0x1f084b8 | ghidra 0x20084b8 | size 300 | symbol _ZN4Aska10TouchPanel12GetDoubleTapEPNS0_7Vector2Ei | lib libSOA-3.7.0.so | 2026-10-04
int _ZN4Aska10TouchPanel12GetDoubleTapEPNS0_7Vector2Ei(long param_1,undefined4 *param_2,int param_3)

{
  ulong uVar1;
  undefined8 *puVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  ulong uVar6;
  ulong uVar7;
  undefined8 *puVar8;
  undefined8 *puVar9;
  undefined8 uVar10;
  undefined8 uVar11;
  undefined8 uVar12;
  
  iVar3 = 0;
  if ((param_2 != (undefined4 *)0x0) && (param_3 != 0)) {
    if (*(int *)(param_1 + 0x2888) != 2) {
      return 0;
    }
    iVar3 = *(int *)(param_1 + 0x2880);
    if (param_3 <= *(int *)(param_1 + 0x2880)) {
      iVar3 = param_3;
    }
    if (0 < iVar3) {
      uVar1 = param_1 + (long)iVar3 * 4 + 0x26c6;
      if (uVar1 <= param_1 + 0x26caU) {
        uVar1 = param_1 + 0x26caU;
      }
      uVar1 = (uVar1 + (-0x26c7 - param_1) >> 2) + 1;
      puVar4 = (undefined4 *)(param_1 + 0x26c6);
      if ((7 < uVar1) && (uVar6 = uVar1 & 0x7ffffffffffffff8, uVar6 != 0)) {
        uVar7 = param_1 + (long)iVar3 * 4 + 0x26c6;
        if (uVar7 <= param_1 + 0x26caU) {
          uVar7 = param_1 + 0x26caU;
        }
        uVar7 = uVar7 + (-0x26c7 - param_1) & 0xfffffffffffffffc;
        if (((undefined4 *)(param_1 + uVar7 + 0x26ca) <= param_2) ||
           ((long)param_2 + uVar7 + 4 <= param_1 + 0x26c6U)) {
          puVar8 = (undefined8 *)(param_2 + 4);
          puVar4 = (undefined4 *)(param_1 + 0x26c6U + uVar6 * 4);
          param_2 = param_2 + uVar6;
          puVar9 = (undefined8 *)(param_1 + 0x26d6);
          uVar7 = uVar6;
          do {
            puVar2 = puVar9 + -1;
            uVar10 = puVar9[-2];
            uVar12 = puVar9[1];
            uVar11 = *puVar9;
            uVar7 = uVar7 - 8;
            puVar9 = puVar9 + 4;
            puVar8[-1] = *puVar2;
            puVar8[-2] = uVar10;
            puVar8[1] = uVar12;
            *puVar8 = uVar11;
            puVar8 = puVar8 + 4;
          } while (uVar7 != 0);
          if (uVar1 == uVar6) {
            return iVar3;
          }
        }
      }
      do {
        puVar5 = puVar4 + 1;
        *param_2 = *puVar4;
        param_2 = param_2 + 1;
        puVar4 = puVar5;
      } while (puVar5 < (undefined4 *)(param_1 + (long)iVar3 * 4 + 0x26c6U));
    }
  }
  return iVar3;
}

// ==== Aska::TouchPanel::GetDrag(Aska::TouchPanel::DragParam*)
// vaddr 0x1f085e4 | ghidra 0x20085e4 | size 64 | symbol _ZN4Aska10TouchPanel7GetDragEPNS0_9DragParamE | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska10TouchPanel7GetDragEPNS0_9DragParamE(long param_1,undefined8 *param_2)

{
  undefined8 uVar1;
  
  if (param_2 == (undefined8 *)0x0) {
    return 0;
  }
  if (*(int *)(param_1 + 0x290c) == 3) {
    return 0;
  }
  param_2[2] = *(undefined8 *)(param_1 + 0x291c);
  uVar1 = *(undefined8 *)(param_1 + 0x290c);
  param_2[1] = *(undefined8 *)(param_1 + 0x2914);
  *param_2 = uVar1;
  return 1;
}

// ==== Aska::TouchPanel::GetDragMulti(Aska::TouchPanel::DragParam (&) [8])
// vaddr 0x1f08624 | ghidra 0x2008624 | size 392 | symbol _ZN4Aska10TouchPanel12GetDragMultiERA8_NS0_9DragParamE | lib libSOA-3.7.0.so | 2026-10-04
uint _ZN4Aska10TouchPanel12GetDragMultiERA8_NS0_9DragParamE(long param_1,undefined8 *param_2)

{
  bool bVar1;
  uint uVar2;
  undefined8 *puVar3;
  undefined8 uVar4;
  
  bVar1 = *(int *)(param_1 + 0x290c) != 3;
  if (bVar1) {
    param_2[2] = *(undefined8 *)(param_1 + 0x291c);
    uVar4 = *(undefined8 *)(param_1 + 0x290c);
    param_2[1] = *(undefined8 *)(param_1 + 0x2914);
    *param_2 = uVar4;
  }
  uVar2 = (uint)bVar1;
  if (*(int *)(param_1 + 0x2924) != 3) {
    puVar3 = param_2 + (ulong)uVar2 * 3;
    uVar2 = uVar2 + 1;
    puVar3[2] = *(undefined8 *)(param_1 + 0x2934);
    uVar4 = *(undefined8 *)(param_1 + 0x2924);
    puVar3[1] = *(undefined8 *)(param_1 + 0x292c);
    *puVar3 = uVar4;
  }
  if (*(int *)(param_1 + 0x293c) != 3) {
    puVar3 = param_2 + (long)(int)uVar2 * 3;
    uVar2 = uVar2 + 1;
    puVar3[2] = *(undefined8 *)(param_1 + 0x294c);
    uVar4 = *(undefined8 *)(param_1 + 0x293c);
    puVar3[1] = *(undefined8 *)(param_1 + 0x2944);
    *puVar3 = uVar4;
  }
  if (*(int *)(param_1 + 0x2954) != 3) {
    puVar3 = param_2 + (long)(int)uVar2 * 3;
    uVar2 = uVar2 + 1;
    puVar3[2] = *(undefined8 *)(param_1 + 0x2964);
    uVar4 = *(undefined8 *)(param_1 + 0x2954);
    puVar3[1] = *(undefined8 *)(param_1 + 0x295c);
    *puVar3 = uVar4;
  }
  if (*(int *)(param_1 + 0x296c) != 3) {
    puVar3 = param_2 + (long)(int)uVar2 * 3;
    uVar2 = uVar2 + 1;
    puVar3[2] = *(undefined8 *)(param_1 + 0x297c);
    uVar4 = *(undefined8 *)(param_1 + 0x296c);
    puVar3[1] = *(undefined8 *)(param_1 + 0x2974);
    *puVar3 = uVar4;
  }
  if (*(int *)(param_1 + 0x2984) != 3) {
    puVar3 = param_2 + (long)(int)uVar2 * 3;
    uVar2 = uVar2 + 1;
    puVar3[2] = *(undefined8 *)(param_1 + 0x2994);
    uVar4 = *(undefined8 *)(param_1 + 0x2984);
    puVar3[1] = *(undefined8 *)(param_1 + 0x298c);
    *puVar3 = uVar4;
  }
  if (*(int *)(param_1 + 0x299c) != 3) {
    puVar3 = param_2 + (long)(int)uVar2 * 3;
    uVar2 = uVar2 + 1;
    puVar3[2] = *(undefined8 *)(param_1 + 0x29ac);
    uVar4 = *(undefined8 *)(param_1 + 0x299c);
    puVar3[1] = *(undefined8 *)(param_1 + 0x29a4);
    *puVar3 = uVar4;
  }
  if (*(int *)(param_1 + 0x29b4) != 3) {
    param_2 = param_2 + (long)(int)uVar2 * 3;
    uVar2 = uVar2 + 1;
    param_2[2] = *(undefined8 *)(param_1 + 0x29c4);
    uVar4 = *(undefined8 *)(param_1 + 0x29b4);
    param_2[1] = *(undefined8 *)(param_1 + 0x29bc);
    *param_2 = uVar4;
  }
  return uVar2;
}

// ==== Aska::TouchPanel::GetTouchAndHold(Aska::TouchPanel::TouchAndHoldParam*)
// vaddr 0x1f087ac | ghidra 0x20087ac | size 48 | symbol _ZN4Aska10TouchPanel15GetTouchAndHoldEPNS0_17TouchAndHoldParamE | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska10TouchPanel15GetTouchAndHoldEPNS0_17TouchAndHoldParamE(long param_1,undefined8 *param_2)

{
  if (param_2 == (undefined8 *)0x0) {
    return 0;
  }
  if (*(int *)(param_1 + 0x28d4) != 0) {
    *param_2 = *(undefined8 *)(param_1 + 0x2894);
    return 1;
  }
  return 0;
}

// ==== Aska::TouchPanel::GetTouchAndHoldMulti(Aska::TouchPanel::TouchAndHoldParam (&) [8])
// vaddr 0x1f087dc | ghidra 0x20087dc | size 64 | symbol _ZN4Aska10TouchPanel20GetTouchAndHoldMultiERA8_NS0_17TouchAndHoldParamE | lib libSOA-3.7.0.so | 2026-10-04
undefined4
_ZN4Aska10TouchPanel20GetTouchAndHoldMultiERA8_NS0_17TouchAndHoldParamE
          (long param_1,undefined8 param_2)

{
  if (*(int *)(param_1 + 0x28d4) != 0) {
    memcpy(param_2,param_1 + 0x2894,(long)*(int *)(param_1 + 0x28d4) << 3);
    return *(undefined4 *)(param_1 + 0x28d4);
  }
  return 0;
}

// ==== Aska::TouchPanel::GetPinchOutIn(Aska::TouchPanel::PinchOutInParam*)
// vaddr 0x1f0881c | ghidra 0x200881c | size 64 | symbol _ZN4Aska10TouchPanel13GetPinchOutInEPNS0_15PinchOutInParamE | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska10TouchPanel13GetPinchOutInEPNS0_15PinchOutInParamE(long param_1,undefined8 *param_2)

{
  undefined8 uVar1;
  
  if (param_2 == (undefined8 *)0x0) {
    return 0;
  }
  if (*(int *)(param_1 + 0x28d8) == 3) {
    return 0;
  }
  uVar1 = *(undefined8 *)(param_1 + 0x28e8);
  param_2[3] = *(undefined8 *)(param_1 + 0x28f0);
  param_2[2] = uVar1;
  uVar1 = *(undefined8 *)(param_1 + 0x28d8);
  param_2[1] = *(undefined8 *)(param_1 + 0x28e0);
  *param_2 = uVar1;
  return 1;
}

// ==== Aska::TouchPanel::GetStatus()
// vaddr 0x1f08860 | ghidra 0x2008860 | size 20 | symbol _ZN4Aska10TouchPanel9GetStatusEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska10TouchPanel9GetStatusEv(void)

{
  Aska::TouchPanel::GetDeviceData()();
  return 1;
}

// ==== Aska::TouchPanel::GetDeviceData()
// vaddr 0x1f08874 | ghidra 0x2008874 | size 1208 | symbol _ZN4Aska10TouchPanel13GetDeviceDataEv | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 _ZN4Aska10TouchPanel13GetDeviceDataEv(long param_1)

{
  int *piVar1;
  int *piVar2;
  uint uVar3;
  int iVar4;
  char cVar5;
  int iVar6;
  uint uVar7;
  bool bVar8;
  undefined2 uVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  undefined *puVar14;
  undefined4 uVar15;
  int iVar16;
  int iVar17;
  ulong uVar18;
  long lVar19;
  char cVar20;
  uint *puVar21;
  ushort *puVar22;
  long lVar23;
  ushort *puVar24;
  int *piVar25;
  long lVar26;
  short sVar27;
  float fVar28;
  float fVar29;
  float fVar30;
  ushort uVar31;
  float fVar32;
  
  cVar20 = *(char *)(param_1 + 0x26c4);
  cVar5 = *(char *)(param_1 + 0x26c5);
  if (cVar20 != cVar5) {
    *(char *)(param_1 + 0x26c4) = cVar5;
    cVar20 = cVar5;
  }
  if (cVar20 != '\0') {
    lVar26 = *(long *)PTR__ZN4Aska6Global14m_pFrameBufferE_02cb8198;
    uVar15 = Aska::Global::GetCPUTime()();
    puVar14 = PTR__ZN4Aska12g_pRenderDevE_02cbb1a0;
    cVar20 = *(char *)(lVar26 + 300);
    uVar31 = *(ushort *)(lVar26 + 0x18);
    iVar16 = Aska::RenderDeviceGL::GetDefaultWindowWidth()(*(undefined8 *)PTR__ZN4Aska12g_pRenderDevE_02cbb1a0);
    if (cVar20 == '\0') {
      iVar16 = iVar16 + (int)*(float *)(lVar26 + 0x124) * -2;
      fVar29 = (float)NEON_ucvtf((uint)*(ushort *)(lVar26 + 0x1a));
      iVar17 = Aska::RenderDeviceGL::GetDefaultWindowHeight()(*(undefined8 *)puVar14);
      fVar30 = (float)(int)*(float *)(lVar26 + 0x124);
      fVar29 = fVar29 / (float)(iVar17 + (int)*(float *)(lVar26 + 0x128) * -2);
      fVar28 = (float)(int)*(float *)(lVar26 + 0x128);
    }
    else {
      fVar29 = (float)NEON_ucvtf((uint)*(ushort *)(lVar26 + 0x1a));
      iVar17 = Aska::RenderDeviceGL::GetDefaultWindowHeight()(*(undefined8 *)puVar14);
      fVar28 = 0.0;
      fVar29 = fVar29 / (float)iVar17;
      fVar30 = 0.0;
    }
    puVar14 = PTR__ZN4Aska10TouchPanel22m_queueSystemTouchDataE_02cbec00;
    fVar13 = _UNK_028014f8;
    iVar17 = 0;
    if (*(int *)(PTR__ZN4Aska10TouchPanel22m_queueSystemTouchDataE_02cbec00 + 0xc) + 1 < 0x41) {
      iVar17 = *(int *)(PTR__ZN4Aska10TouchPanel22m_queueSystemTouchDataE_02cbec00 + 0xc) + 1;
    }
    if (iVar17 != *(int *)(PTR__ZN4Aska10TouchPanel22m_queueSystemTouchDataE_02cbec00 + 8)) {
      fVar10 = (float)NEON_ucvtf((uint)uVar31);
      piVar1 = (int *)(param_1 + 0x40);
      piVar2 = (int *)(param_1 + 0x44);
      lVar26 = param_1 + 0x80;
      do {
        uVar3 = *(uint *)(puVar14 + (long)iVar17 * 0x14 + 0x10);
        if ((uVar3 & 0xff) < 7) {
          iVar4 = *(int *)(puVar14 + (long)iVar17 * 0x14 + 0x14);
          fVar11 = *(float *)(puVar14 + (long)iVar17 * 0x14 + 0x18);
          fVar12 = *(float *)(puVar14 + (long)iVar17 * 0x14 + 0x1c);
          fVar32 = *(float *)(puVar14 + (long)iVar17 * 0x14 + 0x20);
          uVar7 = 1 << (ulong)(uVar3 & 0x1f);
          if ((uVar7 & 0x5a) == 0) {
            if ((uVar7 & 0x21) == 0) {
              sVar27 = 3;
            }
            else {
              sVar27 = 1;
            }
          }
          else {
            sVar27 = 2;
          }
          iVar17 = 0;
          do {
            while (*piVar1 == -1) {
              cVar20 = '\x01';
              bVar8 = (bool)ExclusiveMonitorPass(piVar1,0x10);
              if (bVar8) {
                *piVar1 = 0;
                cVar20 = ExclusiveMonitorsStatus();
              }
              if (cVar20 == '\0') goto code_r0x02008b00;
            }
            ClearExclusiveLocal();
            bVar8 = iVar17 < 0x1ff;
            iVar17 = iVar17 + 1;
          } while (bVar8);
          do {
            cVar20 = '\x01';
            bVar8 = (bool)ExclusiveMonitorPass(piVar2,0x10);
            if (bVar8) {
              *piVar2 = *piVar2 + 1;
              cVar20 = ExclusiveMonitorsStatus();
            }
          } while (cVar20 != '\0');
          do {
            if (*piVar1 != -1) {
              do {
                ClearExclusiveLocal();
                uVar18 = Aska::Semaphore::IsReady() const(lVar26);
                if ((uVar18 & 1) == 0) {
                  do {
                    cVar20 = '\x01';
                    bVar8 = (bool)ExclusiveMonitorPass(piVar2,0x10);
                    if (bVar8) {
                      *piVar2 = *piVar2 + -1;
                      cVar20 = ExclusiveMonitorsStatus();
                    }
                  } while (cVar20 != '\0');
                  Aska::Thread::Sleep(unsigned int)(1);
                }
                else {
                  Aska::Semaphore::Wait() const(lVar26);
                }
                do {
                  cVar20 = '\x01';
                  bVar8 = (bool)ExclusiveMonitorPass(piVar2,0x10);
                  if (bVar8) {
                    *piVar2 = *piVar2 + 1;
                    cVar20 = ExclusiveMonitorsStatus();
                  }
                } while (cVar20 != '\0');
                while (*piVar1 == -1) {
                  cVar20 = '\x01';
                  bVar8 = (bool)ExclusiveMonitorPass(piVar1,0x10);
                  if (bVar8) {
                    *piVar1 = 0;
                    cVar20 = ExclusiveMonitorsStatus();
                  }
                  if (cVar20 == '\0') goto code_r0x02008af0;
                }
              } while( true );
            }
            cVar20 = '\x01';
            bVar8 = (bool)ExclusiveMonitorPass(piVar1,0x10);
            if (bVar8) {
              *piVar1 = 0;
              cVar20 = ExclusiveMonitorsStatus();
            }
          } while (cVar20 != '\0');
code_r0x02008af0:
          do {
            cVar20 = '\x01';
            bVar8 = (bool)ExclusiveMonitorPass(piVar2,0x10);
            if (bVar8) {
              *piVar2 = *piVar2 + -1;
              cVar20 = ExclusiveMonitorsStatus();
            }
          } while (cVar20 != '\0');
code_r0x02008b00:
          DataMemoryBarrier(2,3);
          iVar17 = *(int *)(param_1 + 0x26a8);
          if (iVar17 == 0) {
            iVar17 = 1;
            *(undefined4 *)(param_1 + 0x26a8) = 1;
            memset(param_1 + 0xa8,0,0x98);
            *(undefined4 *)(param_1 + 0xb0) = uVar15;
          }
          else if ((sVar27 == 3) && (0 < iVar17)) {
            lVar19 = 0;
            puVar22 = (ushort *)(param_1 + 0xca);
            do {
              iVar6 = *(int *)(param_1 + lVar19 * 0x98 + 0xb4);
              if (0 < iVar6) {
                lVar23 = 0;
                puVar24 = puVar22;
                do {
                  if ((iVar4 == *(int *)(puVar24 + -5)) && (*puVar24 - 1 < 2))
                  goto code_r0x02008c88;
                  lVar23 = lVar23 + 1;
                  puVar24 = puVar24 + 8;
                } while (lVar23 < iVar6);
              }
              lVar19 = lVar19 + 1;
              puVar22 = puVar22 + 0x4c;
            } while (lVar19 < iVar17);
          }
          lVar19 = (long)iVar17 + -1;
          lVar23 = param_1 + lVar19 * 0x98;
          puVar21 = (uint *)(lVar23 + 0xb4);
          uVar7 = *puVar21;
          *(undefined4 *)(lVar23 + 0xb8) = 1;
          if ((int)uVar7 < 1) {
code_r0x02008c30:
            lVar19 = param_1 + lVar19 * 0x98 + (ulong)uVar7 * 0x10;
            *puVar21 = uVar7 + 1;
code_r0x02008c44:
            *(int *)(lVar19 + 0xc0) = iVar4;
            *(short *)(lVar19 + 0xca) = sVar27;
            uVar9 = (undefined2)(int)((fVar10 / (float)iVar16) * (fVar11 - fVar30));
            *(undefined2 *)(lVar19 + 0xc6) = uVar9;
            *(short *)(lVar19 + 200) = (short)(int)(fVar29 * (fVar12 - fVar28));
            *(char *)(lVar19 + 0xc4) = (char)(int)(fVar32 * fVar13);
            if ((uVar3 & 0xff00) == 0) {
              *(undefined2 *)(param_1 + 0x26c0) = uVar9;
              *(undefined2 *)(param_1 + 0x26c2) = *(undefined2 *)(lVar19 + 200);
            }
          }
          else {
            lVar23 = 0;
            piVar25 = (int *)(param_1 + 0xc0 + lVar19 * 0x98);
            do {
              if (iVar4 == *piVar25) {
                if (iVar17 < 0x40) {
                  lVar19 = param_1 + (long)*(int *)(param_1 + 0x26a8) * 0x98;
                  *(int *)(param_1 + 0x26a8) = *(int *)(param_1 + 0x26a8) + 1;
                  memset(lVar19 + 0xa8,0,0x98);
                  *(undefined4 *)(lVar19 + 0xb4) = 1;
                  *(undefined4 *)(param_1 + 0xb0) = uVar15;
                  goto code_r0x02008c44;
                }
                break;
              }
              lVar23 = lVar23 + 1;
              piVar25 = piVar25 + 4;
            } while (lVar23 < (int)uVar7);
            if ((int)uVar7 < 8) goto code_r0x02008c30;
          }
code_r0x02008c88:
          DataMemoryBarrier(2,3);
          *piVar1 = -1;
          DataMemoryBarrier(2,3);
          if (0x14 < *piVar2) {
            do {
              cVar20 = '\x01';
              bVar8 = (bool)ExclusiveMonitorPass(piVar2,0x10);
              if (bVar8) {
                *piVar2 = *piVar2 + -1;
                cVar20 = ExclusiveMonitorsStatus();
              }
            } while (cVar20 != '\0');
            uVar18 = Aska::Semaphore::IsReady() const(lVar26);
            if ((uVar18 & 1) != 0) {
              Aska::Semaphore::Signal() const(lVar26);
            }
          }
        }
        iVar17 = 0;
        if (*(int *)(puVar14 + 0xc) + 1 < 0x41) {
          iVar17 = *(int *)(puVar14 + 0xc) + 1;
        }
        *(int *)(puVar14 + 0xc) = iVar17;
        iVar17 = 0;
        if (*(int *)(puVar14 + 0xc) + 1 < 0x41) {
          iVar17 = *(int *)(puVar14 + 0xc) + 1;
        }
        if (iVar17 == *(int *)(puVar14 + 8)) {
          return 1;
        }
      } while( true );
    }
  }
  return 1;
}

// ==== Aska::TouchPanel::ResetStatus()
// vaddr 0x1f08d2c | ghidra 0x2008d2c | size 340 | symbol _ZN4Aska10TouchPanel11ResetStatusEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10TouchPanel11ResetStatusEv(long param_1)

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
                if (cVar3 == '\0') goto code_r0x02008e68;
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
code_r0x02008e68:
        do {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
          if (bVar4) {
            *piVar2 = *piVar2 + -1;
            cVar3 = ExclusiveMonitorsStatus();
          }
        } while (cVar3 != '\0');
        DataMemoryBarrier(2,3);
code_r0x02008da0:
        *(undefined4 *)(param_1 + 0x26a8) = 0;
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
  goto code_r0x02008da0;
}

// ==== Aska::TouchPanel::InitializeGesture()
// vaddr 0x1f08e80 | ghidra 0x2008e80 | size 8 | symbol _ZN4Aska10TouchPanel17InitializeGestureEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska10TouchPanel17InitializeGestureEv(void)

{
  return 1;
}

// ==== Aska::TouchPanel::FinalizeGesture()
// vaddr 0x1f08e88 | ghidra 0x2008e88 | size 4 | symbol _ZN4Aska10TouchPanel15FinalizeGestureEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10TouchPanel15FinalizeGestureEv(void)

{
  return;
}

// ==== Aska::TouchPanel::~TouchPanel()
// vaddr 0x1f0a0b8 | ghidra 0x200a0b8 | size 48 | symbol _ZN4Aska10TouchPanelD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10TouchPanelD0Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska14BasePeripheralE_02cbc550 + 0x10);
  Aska::FastCriticalSection::~FastCriticalSection()(param_1 + 1);
  Aska::IAnimatable::~IAnimatable()(param_1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::BasePeripheral::GetClassID(int) const
// vaddr 0x1f0a0e8 | ghidra 0x200a0e8 | size 24 | symbol _ZNK4Aska14BasePeripheral10GetClassIDEi | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska14BasePeripheral10GetClassIDEi(undefined8 param_1,int param_2)

{
  undefined8 uVar1;
  
  uVar1 = 0xf000f035;
  if (param_2 != 0) {
    uVar1 = 0xf000;
  }
  return uVar1;
}

// ==== Aska::TouchPanel::GetDeviceDataNoPort()
// vaddr 0x1f0a100 | ghidra 0x200a100 | size 12 | symbol _ZN4Aska10TouchPanel19GetDeviceDataNoPortEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10TouchPanel19GetDeviceDataNoPortEv(long *param_1)

{
                    /* WARNING: Could not recover jumptable at 0x0200a108. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*param_1 + 0x60))();
  return;
}

// ==== Aska::BasePeripheral::GetStatus()
// vaddr 0x1f17664 | ghidra 0x2017664 | size 124 | symbol _ZN4Aska14BasePeripheral9GetStatusEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska14BasePeripheral9GetStatusEv(long *param_1)

{
  ulong uVar1;
  
  if (*(char *)((long)param_1 + 0xa1) != '\0') {
    (**(code **)(*param_1 + 0x58))(param_1);
    return 1;
  }
  if ((*(char *)((long)param_1 + 0x9a) != '\0') &&
     (uVar1 = (**(code **)(*param_1 + 0x60))(param_1), (uVar1 & 1) != 0)) {
    return 1;
  }
  if (*(char *)((long)param_1 + 0x99) != -1) {
    (**(code **)(*param_1 + 0x38))(param_1);
  }
  return 0;
}

// ==== Aska::BasePeripheral::CheckConnection()
// vaddr 0x1f176e0 | ghidra 0x20176e0 | size 28 | symbol _ZN4Aska14BasePeripheral15CheckConnectionEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska14BasePeripheral15CheckConnectionEv(long *param_1)

{
  if (*(char *)((long)param_1 + 0x99) != -1) {
                    /* WARNING: Could not recover jumptable at 0x020176f4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(*param_1 + 0x38))();
    return;
  }
  return;
}

// ==== Aska::BasePeripheral::Release()
// vaddr 0x1f176fc | ghidra 0x20176fc | size 364 | symbol _ZN4Aska14BasePeripheral7ReleaseEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska14BasePeripheral7ReleaseEv(long param_1)

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
                if (cVar3 == '\0') goto code_r0x02017850;
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
code_r0x02017850:
        do {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
          if (bVar4) {
            *piVar2 = *piVar2 + -1;
            cVar3 = ExclusiveMonitorsStatus();
          }
        } while (cVar3 != '\0');
        DataMemoryBarrier(2,3);
code_r0x02017770:
        *(undefined2 *)(param_1 + 0x9e) = 0;
        *(undefined1 *)(param_1 + 0xa1) = 0;
        *(undefined4 *)(param_1 + 0x99) = 0xff0000ff;
        *(undefined1 *)(param_1 + 0x9d) = 0xff;
        *(undefined1 *)(param_1 + 0xa0) = 0xff;
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
  goto code_r0x02017770;
}

// ==== Aska::BasePeripheral::Get(unsigned long, void*) const
// vaddr 0x1f17868 | ghidra 0x2017868 | size 108 | symbol _ZNK4Aska14BasePeripheral3GetEmPv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska14BasePeripheral3GetEmPv(long param_1,undefined8 param_2,undefined1 *param_3)

{
  undefined1 uVar1;
  
  if ((short)((ulong)param_2 >> 0x20) == 0) {
    switch((short)param_2) {
    case 0:
      uVar1 = *(undefined1 *)(param_1 + 0x98);
      break;
    case 1:
      uVar1 = *(undefined1 *)(param_1 + 0x99);
      break;
    case 2:
      uVar1 = *(undefined1 *)(param_1 + 0x9a);
      break;
    case 3:
      uVar1 = *(undefined1 *)(param_1 + 0x9c);
      break;
    case 4:
      uVar1 = *(undefined1 *)(param_1 + 0x9d);
      break;
    default:
      return 0;
    }
    *param_3 = uVar1;
    return 1;
  }
  return 0;
}

// ==== Aska::BasePeripheral::Set(unsigned long, void const*)
// vaddr 0x1f178d4 | ghidra 0x20178d4 | size 72 | symbol _ZN4Aska14BasePeripheral3SetEmPKv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska14BasePeripheral3SetEmPKv(long *param_1,short param_2,undefined1 *param_3)

{
  if (param_2 == 1) {
    (**(code **)(*param_1 + 0x38))(param_1,*param_3);
    return 1;
  }
  if (param_2 == 0) {
    *(undefined1 *)(param_1 + 0x13) = *param_3;
    return 1;
  }
  return 0;
}

// ==== Aska::BasePeripheral::~BasePeripheral()
// vaddr 0x1f1791c | ghidra 0x201791c | size 4 | symbol _ZN4Aska14BasePeripheralD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska14BasePeripheralD0Ev(void)

{
  code *pcVar1;
  
                    /* WARNING: Does not return */
  pcVar1 = (code *)SoftwareBreakpoint(1,0x2017920);
  (*pcVar1)();
}

// ==== Aska::Keyboard::Keyboard()
// vaddr 0x1f27680 | ghidra 0x2027680 | size 52 | symbol _ZN4Aska8KeyboardC2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska8KeyboardC1Ev(long *param_1)

{
  Aska::BaseInputPeripheral::BaseInputPeripheral()();
  *param_1 = (long)(PTR__ZTVN4Aska8KeyboardE_02cc09c0 + 0x10);
  memset((long)param_1 + 0x2ac,0,0x402);
  return;
}

// ==== Aska::Keyboard::~Keyboard()
// vaddr 0x1f276b4 | ghidra 0x20276b4 | size 4 | symbol _ZN4Aska8KeyboardD1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska8KeyboardD2Ev(void)

{
  (*(code *)PTR__ZN4Aska19BaseInputPeripheralD2Ev_02ca2020)();
  return;
}

// ==== Aska::Keyboard::~Keyboard()
// vaddr 0x1f276b8 | ghidra 0x20276b8 | size 24 | symbol _ZN4Aska8KeyboardD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska8KeyboardD0Ev(undefined8 param_1)

{
  Aska::BaseInputPeripheral::~BaseInputPeripheral()();
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::Keyboard::Initialize(unsigned char)
// vaddr 0x1f276d0 | ghidra 0x20276d0 | size 4 | symbol _ZN4Aska8Keyboard10InitializeEh | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska8Keyboard10InitializeEh(void)

{
  return;
}

// ==== Aska::Keyboard::Release()
// vaddr 0x1f276d4 | ghidra 0x20276d4 | size 4 | symbol _ZN4Aska8Keyboard7ReleaseEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska8Keyboard7ReleaseEv(void)

{
  return;
}

// ==== Aska::Keyboard::GetStatus()
// vaddr 0x1f276d8 | ghidra 0x20276d8 | size 8 | symbol _ZN4Aska8Keyboard9GetStatusEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska8Keyboard9GetStatusEv(void)

{
  return 0;
}

// ==== Aska::Keyboard::ResetStatus()
// vaddr 0x1f276e0 | ghidra 0x20276e0 | size 4 | symbol _ZN4Aska8Keyboard11ResetStatusEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska8Keyboard11ResetStatusEv(void)

{
  return;
}

// ==== Aska::Keyboard::GetDeviceDataNoPort()
// vaddr 0x1f276e4 | ghidra 0x20276e4 | size 4 | symbol _ZN4Aska8Keyboard19GetDeviceDataNoPortEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska8Keyboard19GetDeviceDataNoPortEv(void)

{
  return;
}

// ==== Aska::Keyboard::GetDeviceData()
// vaddr 0x1f276e8 | ghidra 0x20276e8 | size 8 | symbol _ZN4Aska8Keyboard13GetDeviceDataEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska8Keyboard13GetDeviceDataEv(void)

{
  return 0;
}

// ==== Aska::Keyboard::ClearKeyRepeatData()
// vaddr 0x1f276f0 | ghidra 0x20276f0 | size 16 | symbol _ZN4Aska8Keyboard18ClearKeyRepeatDataEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska8Keyboard18ClearKeyRepeatDataEv(long param_1)

{
  (*(code *)PTR_memset_02c9b870)(param_1 + 0x2ac,0,0x400);
  return;
}

// ==== Aska::Keyboard::GetIsControlledViaNetwork() const
// vaddr 0x1f27700 | ghidra 0x2027700 | size 8 | symbol _ZNK4Aska8Keyboard25GetIsControlledViaNetworkEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska8Keyboard25GetIsControlledViaNetworkEv(void)

{
  return 0;
}

// ==== Aska::Keyboard::StopNetworkControlRequest()
// vaddr 0x1f27708 | ghidra 0x2027708 | size 4 | symbol _ZN4Aska8Keyboard25StopNetworkControlRequestEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska8Keyboard25StopNetworkControlRequestEv(void)

{
  return;
}

// ==== Aska::Keyboard::CancelNetworkControlAutoStopTimer()
// vaddr 0x1f2770c | ghidra 0x202770c | size 4 | symbol _ZN4Aska8Keyboard33CancelNetworkControlAutoStopTimerEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska8Keyboard33CancelNetworkControlAutoStopTimerEv(void)

{
  return;
}

// ==== Aska::Keyboard::MapKeyEx(int, bool)
// vaddr 0x1f27710 | ghidra 0x2027710 | size 160 | symbol _ZN4Aska8Keyboard8MapKeyExEib | lib libSOA-3.7.0.so | 2026-10-04
uint _ZN4Aska8Keyboard8MapKeyExEib(undefined8 param_1,int param_2,uint param_3)

{
  byte bVar1;
  uint uVar2;
  uint uVar3;
  
  if (0x7f < param_2) {
    return 0;
  }
  bVar1 = (&UNK_0296f891)[param_2];
  uVar2 = (uint)bVar1;
  uVar3 = (uint)bVar1;
  if ((param_3 & 1) == 0) {
    uVar3 = uVar3 ^ 0xffffff80;
    if (((uVar3 & 0xff) < 0x19) && ((0x1f8000fU >> (ulong)(uVar3 & 0x1f) & 1) != 0)) {
      uVar2 = *(uint *)(&UNK_02970140 + (long)(char)uVar3 * 4);
    }
  }
  else if (bVar1 < 0xaf) {
    if (uVar3 == 0xd) {
      return 0xa9;
    }
    if (bVar1 == 0x2f) {
      return 0xac;
    }
  }
  else {
    if (bVar1 == 0xaf) {
      return 0xae;
    }
    if (uVar3 == 0xff) {
      return 0xfe;
    }
  }
  return uVar2;
}

// ==== Aska::Keyboard::KeyEventEx(int, bool)
// vaddr 0x1f277b0 | ghidra 0x20277b0 | size 248 | symbol _ZN4Aska8Keyboard10KeyEventExEib | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska8Keyboard10KeyEventExEib(long param_1,int param_2,byte param_3)

{
  int iVar1;
  long lVar2;
  int *piVar3;
  int iStack_8;
  undefined4 uStack_4;
  
  if (param_2 == 0xfe) {
    if ((param_3 & 1) != 0) {
      *(byte *)(param_1 + 0x6ac) = *(byte *)(param_1 + 0x6ac) ^ 1;
      iVar1 = *(int *)(param_1 + 0x6a4);
      *(int *)(param_1 + 0x6a4) = iVar1 + 1;
      lVar2 = 0xfe;
      goto joined_r0x02027848;
    }
    piVar3 = (int *)(param_1 + 0x6a4);
    lVar2 = 0xfe;
  }
  else {
    if (param_2 == 0x86) {
      *(byte *)(param_1 + 0x6ad) = param_3 & 1;
    }
    lVar2 = (long)param_2;
    piVar3 = (int *)(param_1 + (long)param_2 * 4 + 0x2ac);
    if ((param_3 & 1) != 0) {
      iVar1 = *piVar3;
      *piVar3 = iVar1 + 1;
      if (((param_2 - 0x7fU < 0x2a) &&
          ((1L << ((ulong)(param_2 - 0x7fU) & 0x3f) & 0x20800c00001U) != 0)) || (param_2 == 0xff))
      goto code_r0x0202785c;
joined_r0x02027848:
      if (0 < iVar1) {
        return;
      }
      goto code_r0x0202785c;
    }
  }
  *piVar3 = 0;
code_r0x0202785c:
  if (*(char *)(param_1 + 0x6ad) != '\0') {
    param_2 = *(int *)(&UNK_0296f914 + lVar2 * 4);
  }
  if (*(char *)(param_1 + 0x6ac) != '\0') {
    param_2 = *(int *)(&UNK_0296fd14 + (long)param_2 * 4);
  }
  uStack_4 = 1;
  if ((param_3 & 1) == 0) {
    uStack_4 = 2;
  }
  iStack_8 = param_2;
  Aska::BaseInputPeripheral::AddMessage(Aska::BaseInputPeripheral::Message const*)(param_1,&iStack_8);
  return;
}

// ==== Aska::Keyboard::GetInstance()
// vaddr 0x1f278a8 | ghidra 0x20278a8 | size 148 | symbol _ZN4Aska8Keyboard11GetInstanceEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska8Keyboard11GetInstanceEv(void)

{
  int iVar1;
  
  if (((bRam0000000002dcc5c8 & 1) == 0) && (iVar1 = __cxa_guard_acquire(0x2dcc5c8), iVar1 != 0)) {
    Aska::BaseInputPeripheral::BaseInputPeripheral()(0x2dcbf18);
    puRam0000000002dcbf18 = PTR__ZTVN4Aska8KeyboardE_02cc09c0 + 0x10;
    memset(0x2dcc1c4,0,0x402);
    __cxa_atexit(PTR__ZN4Aska8KeyboardD2Ev_02cbd870,0x2dcbf18,&DAT_02cc5000);
    __cxa_guard_release(0x2dcc5c8);
  }
  *(undefined8 *)PTR__ZN4Aska8Keyboard6Static9pKeyboardE_02cc24b8 = 0x2dcbf18;
  return;
}

// ==== Aska::Keyboard::GetInstanceNoCreate()
// vaddr 0x1f2793c | ghidra 0x202793c | size 16 | symbol _ZN4Aska8Keyboard19GetInstanceNoCreateEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska8Keyboard19GetInstanceNoCreateEv(void)

{
  return *(undefined8 *)PTR__ZN4Aska8Keyboard6Static9pKeyboardE_02cc24b8;
}

// ==== Aska::Mouse::Mouse()
// vaddr 0x1f4fd0c | ghidra 0x204fd0c | size 68 | symbol _ZN4Aska5MouseC2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5MouseC1Ev(long *param_1)

{
  Aska::BaseInputPeripheral::BaseInputPeripheral()();
  *param_1 = (long)(PTR__ZTVN4Aska5MouseE_02cbf4d8 + 0x10);
  *(undefined8 *)((long)param_1 + 0x2b2) = 0;
  *(undefined8 *)((long)param_1 + 0x2ac) = 0;
  memset((long)param_1 + 700,0,0x52);
  return;
}

// ==== Aska::Mouse::~Mouse()
// vaddr 0x1f4fd50 | ghidra 0x204fd50 | size 4 | symbol _ZN4Aska5MouseD1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5MouseD2Ev(void)

{
  (*(code *)PTR__ZN4Aska19BaseInputPeripheralD2Ev_02ca2020)();
  return;
}

// ==== Aska::Mouse::~Mouse()
// vaddr 0x1f4fd54 | ghidra 0x204fd54 | size 24 | symbol _ZN4Aska5MouseD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5MouseD0Ev(undefined8 param_1)

{
  Aska::BaseInputPeripheral::~BaseInputPeripheral()();
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::Mouse::Initialize(unsigned char)
// vaddr 0x1f4fd6c | ghidra 0x204fd6c | size 4 | symbol _ZN4Aska5Mouse10InitializeEh | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Mouse10InitializeEh(void)

{
  return;
}

// ==== Aska::Mouse::Release()
// vaddr 0x1f4fd70 | ghidra 0x204fd70 | size 4 | symbol _ZN4Aska5Mouse7ReleaseEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Mouse7ReleaseEv(void)

{
  (*(code *)PTR__ZN4Aska19BaseInputPeripheral7ReleaseEv_02cb2fa8)();
  return;
}

// ==== Aska::Mouse::GetStatus()
// vaddr 0x1f4fd74 | ghidra 0x204fd74 | size 8 | symbol _ZN4Aska5Mouse9GetStatusEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska5Mouse9GetStatusEv(void)

{
  return 0;
}

// ==== Aska::Mouse::ResetStatus()
// vaddr 0x1f4fd7c | ghidra 0x204fd7c | size 4 | symbol _ZN4Aska5Mouse11ResetStatusEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Mouse11ResetStatusEv(void)

{
  (*(code *)PTR__ZN4Aska19BaseInputPeripheral11ResetStatusEv_02ca6cf0)();
  return;
}

// ==== Aska::Mouse::SetCursorPosition(int, int, bool)
// vaddr 0x1f4fd80 | ghidra 0x204fd80 | size 160 | symbol _ZN4Aska5Mouse17SetCursorPositionEiib | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Mouse17SetCursorPositionEiib(long param_1,uint param_2,uint param_3,byte param_4)

{
  ushort uVar1;
  ushort uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  long lVar9;
  
  param_3 = param_3 & ((int)param_3 >> 0x1f ^ 0xffffffffU);
  lVar9 = *(long *)PTR__ZN4Aska6Global14m_pFrameBufferE_02cb8198;
  param_2 = param_2 & ((int)param_2 >> 0x1f ^ 0xffffffffU);
  uVar6 = param_3;
  uVar5 = param_2;
  if (lVar9 != 0) {
    uVar1 = *(ushort *)(lVar9 + 0x18);
    uVar2 = *(ushort *)(lVar9 + 0x1a);
    uVar5 = (uint)uVar1;
    if ((int)param_2 <= (int)(uint)uVar1) {
      uVar5 = param_2;
    }
    uVar6 = (uint)uVar2;
    if ((int)param_3 <= (int)(uint)uVar2) {
      uVar6 = param_3;
    }
    if (*(char *)(param_1 + 0x30c) != '\0') {
      uVar7 = (uint)(uVar1 >> 1);
      uVar8 = (uint)(uVar2 >> 1);
      uVar3 = uVar8;
      uVar4 = uVar7;
      goto joined_r0x0204fde0;
    }
  }
  uVar7 = *(uint *)(param_1 + 0x2fc);
  uVar8 = *(uint *)(param_1 + 0x300);
  uVar3 = uVar6;
  uVar4 = uVar5;
joined_r0x0204fde0:
  if ((param_4 & 1) == 0) {
    *(uint *)(param_1 + 0x304) = (uVar5 - uVar7) + *(int *)(param_1 + 0x304);
    *(uint *)(param_1 + 0x308) = (uVar6 - uVar8) + *(int *)(param_1 + 0x308);
  }
  *(uint *)(param_1 + 0x2fc) = uVar4;
  *(uint *)(param_1 + 0x300) = uVar3;
  *(byte *)(param_1 + 0x30d) = *(byte *)(param_1 + 0x30d) | param_4 & 1;
  return;
}

// ==== Aska::Mouse::MouseKey(Aska::Mouse::MsgCode, bool)
// vaddr 0x1f4fe20 | ghidra 0x204fe20 | size 76 | symbol _ZN4Aska5Mouse8MouseKeyENS0_7MsgCodeEb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Mouse8MouseKeyENS0_7MsgCodeEb(long param_1,uint param_2,uint param_3)

{
  int *piVar1;
  int iVar2;
  uint uStack_8;
  undefined4 uStack_4;
  
  if ((int)param_2 < 0x10) {
    piVar1 = (int *)(param_1 + (ulong)param_2 * 4 + 700);
    if ((param_3 & 1) == 0) {
      iVar2 = 0;
    }
    else {
      iVar2 = *piVar1 + 1;
    }
    *piVar1 = iVar2;
    uStack_4 = 1;
    if ((param_3 & 1) == 0) {
      uStack_4 = 2;
    }
    uStack_8 = param_2;
    Aska::BaseInputPeripheral::AddMessage(Aska::BaseInputPeripheral::Message const*)(param_1,&uStack_8);
  }
  return;
}

// ==== Aska::Mouse::GetDeviceDataNoPort()
// vaddr 0x1f4fe6c | ghidra 0x204fe6c | size 4 | symbol _ZN4Aska5Mouse19GetDeviceDataNoPortEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Mouse19GetDeviceDataNoPortEv(void)

{
  return;
}

// ==== Aska::Mouse::GetDeviceData()
// vaddr 0x1f4fe70 | ghidra 0x204fe70 | size 8 | symbol _ZN4Aska5Mouse13GetDeviceDataEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska5Mouse13GetDeviceDataEv(void)

{
  return 0;
}

// ==== Aska::Mouse::GetIsControlledViaNetwork() const
// vaddr 0x1f4fe78 | ghidra 0x204fe78 | size 8 | symbol _ZNK4Aska5Mouse25GetIsControlledViaNetworkEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska5Mouse25GetIsControlledViaNetworkEv(void)

{
  return 0;
}

// ==== Aska::Mouse::StopNetworkConrolRequest()
// vaddr 0x1f4fe80 | ghidra 0x204fe80 | size 4 | symbol _ZN4Aska5Mouse24StopNetworkConrolRequestEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Mouse24StopNetworkConrolRequestEv(void)

{
  return;
}

// ==== Aska::Mouse::GetIsControlledViaTouchPanel() const
// vaddr 0x1f4fe84 | ghidra 0x204fe84 | size 8 | symbol _ZNK4Aska5Mouse28GetIsControlledViaTouchPanelEv | lib libSOA-3.7.0.so | 2026-10-04
undefined1 _ZNK4Aska5Mouse28GetIsControlledViaTouchPanelEv(long param_1)

{
  return *(undefined1 *)(param_1 + 0x2b8);
}

// ==== Aska::Mouse::StopTouchPanelConrolRequest()
// vaddr 0x1f4fe8c | ghidra 0x204fe8c | size 8 | symbol _ZN4Aska5Mouse27StopTouchPanelConrolRequestEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Mouse27StopTouchPanelConrolRequestEv(long param_1)

{
  *(undefined1 *)(param_1 + 0x2b8) = 0;
  return;
}

// ==== Aska::Mouse::GetInstanceNoCreate()
// vaddr 0x1f4fe94 | ghidra 0x204fe94 | size 16 | symbol _ZN4Aska5Mouse19GetInstanceNoCreateEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska5Mouse19GetInstanceNoCreateEv(void)

{
  return *(undefined8 *)PTR__ZN4Aska5Mouse13StaticPrivate6pMouseE_02cbdaf8;
}

// ==== Aska::Mouse::GetInstance()
// vaddr 0x1f4fea4 | ghidra 0x204fea4 | size 164 | symbol _ZN4Aska5Mouse11GetInstanceEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Mouse11GetInstanceEv(void)

{
  int iVar1;
  
  if (((bRam0000000002dcc9c8 & 1) == 0) && (iVar1 = __cxa_guard_acquire(0x2dcc9c8), iVar1 != 0)) {
    Aska::BaseInputPeripheral::BaseInputPeripheral()(0x2dcc6b8);
    puRam0000000002dcc6b8 = PTR__ZTVN4Aska5MouseE_02cbf4d8 + 0x10;
    uRam0000000002dcc96c = 0;
    uRam0000000002dcc964 = 0;
    uRam0000000002dcc96a = 0;
    memset(0x2dcc974,0,0x52);
    __cxa_atexit(PTR__ZN4Aska5MouseD2Ev_02cc00e0,0x2dcc6b8,&DAT_02cc5000);
    __cxa_guard_release(0x2dcc9c8);
  }
  *(undefined8 *)PTR__ZN4Aska5Mouse13StaticPrivate6pMouseE_02cbdaf8 = 0x2dcc6b8;
  return;
}

// ==== Aska::Mouse::EmulateMouse(Aska::TouchPanel*)
// vaddr 0x1f4ff48 | ghidra 0x204ff48 | size 204 | symbol _ZN4Aska5Mouse12EmulateMouseEPNS_10TouchPanelE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Mouse12EmulateMouseEPNS_10TouchPanelE(long *param_1,long param_2)

{
  int iVar1;
  int iVar2;
  undefined1 *puVar3;
  ulong uVar4;
  undefined1 auStack_248 [512];
  uint uStack_48;
  undefined8 uStack_3c;
  undefined1 uStack_34;
  char cStack_33;
  char cStack_32;
  
  if (param_2 != 0) {
    Aska::Mouse::MakeMessageFromTouchPanel(Aska::TouchPanel*, Aska::Mouse::MouseCommonParam*, Aska::Mouse::TouchPanelStatus*)(param_2,auStack_248,(long)param_1 + 0x2ac);
    uVar4 = (ulong)uStack_48;
    if (0 < (int)uStack_48) {
      puVar3 = auStack_248;
      do {
        Aska::BaseInputPeripheral::AddMessage(Aska::BaseInputPeripheral::Message const*)(param_1,puVar3);
        uVar4 = uVar4 - 1;
        puVar3 = puVar3 + 8;
      } while (uVar4 != 0);
    }
    if (cStack_32 == '\0') {
      uStack_3c = 0;
    }
    if (cStack_33 != '\0') {
      uStack_3c._4_4_ = (int)((ulong)uStack_3c >> 0x20);
      iVar1 = (int)uStack_3c + *(int *)((long)param_1 + 0x2fc);
      iVar2 = uStack_3c._4_4_ + (int)param_1[0x60];
      (**(code **)(*param_1 + 0x70))(param_1,iVar1,iVar2,uStack_34);
    }
    *(int *)((long)param_1 + 0x304) = (int)uStack_3c;
    *(int *)(param_1 + 0x61) = uStack_3c._4_4_;
  }
  return;
}

// ==== Aska::Mouse::MakeMessageFromTouchPanel(Aska::TouchPanel*, Aska::Mouse::MouseCommonParam*, Aska::Mouse::TouchPanelStatus*)
// vaddr 0x1f50014 | ghidra 0x2050014 | size 604 | symbol _ZN4Aska5Mouse25MakeMessageFromTouchPanelEPNS_10TouchPanelEPNS0_16MouseCommonParamEPNS0_16TouchPanelStatusE | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska5Mouse25MakeMessageFromTouchPanelEPNS_10TouchPanelEPNS0_16MouseCommonParamEPNS0_16TouchPanelStatusE
               (long param_1,undefined8 *param_2,int *param_3)

{
  long lVar1;
  bool bVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  int iVar5;
  ulong uVar6;
  long lVar7;
  int iVar8;
  int iVar9;
  undefined1 auStack_2650 [8];
  int aiStack_2648 [2];
  short sStack_2640;
  short sStack_263e;
  short sStack_263c;
  short sStack_263a;
  undefined1 auStack_2630 [24];
  undefined4 uStack_2618;
  undefined1 auStack_2614 [2];
  undefined1 auStack_2612 [16];
  undefined1 auStack_2602 [16];
  undefined1 auStack_25f2 [16];
  undefined1 auStack_25e2 [16];
  undefined1 auStack_25d2 [16];
  undefined1 auStack_25c2 [16];
  undefined1 auStack_25b2 [16];
  undefined8 uStack_25a2;
  undefined2 auStack_259a [4789];
  short sStack_28;
  short sStack_26;
  
  lVar7 = 0;
  do {
    lVar1 = lVar7 + 0x98;
    *(undefined4 *)((long)&uStack_2618 + lVar7) = 0;
    auStack_2614[lVar7] = 0;
    *(undefined2 *)((long)auStack_259a + lVar7) = 0;
    *(undefined8 *)((long)&uStack_25a2 + lVar7) = 0;
    *(undefined8 *)(auStack_2614 + lVar7 + 2) = 0;
    *(undefined8 *)(auStack_2612 + lVar7 + 7) = 0;
    *(undefined8 *)(auStack_2602 + lVar7) = 0;
    *(undefined8 *)(auStack_2602 + lVar7 + 7) = 0;
    *(undefined8 *)(auStack_25f2 + lVar7 + 7) = 0;
    *(undefined8 *)(auStack_25f2 + lVar7) = 0;
    *(undefined8 *)(auStack_25e2 + lVar7 + 7) = 0;
    *(undefined8 *)(auStack_25e2 + lVar7) = 0;
    *(undefined8 *)(auStack_25d2 + lVar7 + 7) = 0;
    *(undefined8 *)(auStack_25d2 + lVar7) = 0;
    *(undefined8 *)(auStack_25c2 + lVar7 + 7) = 0;
    *(undefined8 *)(auStack_25c2 + lVar7) = 0;
    *(undefined8 *)(auStack_25b2 + lVar7 + 7) = 0;
    *(undefined8 *)(auStack_25b2 + lVar7) = 0;
    lVar7 = lVar1;
  } while (lVar1 != 0x2600);
  iVar5 = Aska::TouchPanel::CopyMessages(Aska::TouchData*)(param_1,auStack_2630);
  if (0 < iVar5) {
    iVar5 = Aska::TouchPanel::GetTap(Aska::TouchPanel::Vector2*, int)(param_1,&sStack_28,1);
    uVar3 = _UNK_02970ec0;
    if (0 < iVar5) {
      param_2[1] = _UNK_02970ec8;
      *param_2 = uVar3;
      iVar5 = Aska::Global::GetCPUTime()();
      bVar2 = false;
      iVar8 = 0;
      *param_3 = iVar5;
      param_3[1] = (int)sStack_28;
      iVar9 = 0;
      param_3[2] = (int)sStack_26;
      iVar5 = 2;
      goto code_r0x020501c8;
    }
    iVar5 = Aska::TouchPanel::GetDoubleTap(Aska::TouchPanel::Vector2*, int)(param_1,auStack_2650,1);
    uVar4 = _UNK_02970eb8;
    uVar3 = _UNK_02970eb0;
    if (0 < iVar5) {
      bVar2 = false;
      iVar8 = 0;
      iVar9 = 0;
      param_2[2] = 0x200000002;
      param_2[1] = uVar4;
      *param_2 = uVar3;
      iVar5 = 3;
      goto code_r0x020501c8;
    }
    uVar6 = Aska::TouchPanel::GetDrag(Aska::TouchPanel::DragParam*)(param_1,aiStack_2648);
    if ((uVar6 & 1) != 0) {
      if (aiStack_2648[0] == 2) {
        if (*(char *)((long)param_3 + 0xd) != '\0') {
          bVar2 = false;
          iVar8 = 0;
          iVar9 = 0;
          *param_2 = 0x200000001;
          iVar5 = 1;
          *(undefined1 *)((long)param_3 + 0xd) = 0;
          goto code_r0x020501c8;
        }
      }
      else {
        if (aiStack_2648[0] == 1) {
          iVar9 = (int)sStack_2640;
          iVar8 = (int)sStack_263e;
          iVar5 = 0;
          bVar2 = true;
          goto code_r0x020501c8;
        }
        if ((aiStack_2648[0] == 0) && (*(char *)((long)param_3 + 0xd) == '\0')) {
          iVar8 = param_3[1] - (int)sStack_263c;
          iVar5 = -iVar8;
          if (-1 < iVar8) {
            iVar5 = iVar8;
          }
          iVar9 = param_3[2] - (int)sStack_263a;
          iVar8 = -iVar9;
          if (-1 < iVar9) {
            iVar8 = iVar9;
          }
          if ((iVar8 + iVar5 <= *(int *)(param_1 + 0x26b8)) &&
             (iVar5 = Aska::Global::GetCPUTime()(), iVar5 - *param_3 <= *(int *)(param_1 + 0x28fc))) {
            iVar5 = 1;
            bVar2 = false;
            iVar8 = 0;
            iVar9 = 0;
            *param_2 = 0x100000001;
            *(undefined1 *)((long)param_3 + 0xd) = 1;
            goto code_r0x020501c8;
          }
        }
      }
    }
  }
  bVar2 = false;
  iVar5 = 0;
  iVar8 = 0;
  iVar9 = 0;
code_r0x020501c8:
  *(undefined8 *)((long)param_2 + 0x204) = 0;
  *(int *)((long)param_2 + 0x20c) = iVar9;
  *(int *)(param_2 + 0x42) = iVar8;
  *(int *)(param_2 + 0x40) = iVar5;
  *(undefined1 *)((long)param_2 + 0x214) = 0;
  *(bool *)((long)param_2 + 0x215) = bVar2;
  *(bool *)((long)param_2 + 0x216) = bVar2;
  if ((iVar5 != 0) || (bVar2)) {
    *(undefined1 *)(param_3 + 3) = 1;
  }
  return;
}

// ==== Aska::Mouse::ShowCursor(bool)
// vaddr 0x1f50270 | ghidra 0x2050270 | size 4 | symbol _ZN4Aska5Mouse10ShowCursorEb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5Mouse10ShowCursorEb(void)

{
  return;
}

// ==== Aska::Pad::Pad(short)
// vaddr 0x1f533b8 | ghidra 0x20533b8 | size 220 | symbol _ZN4Aska3PadC2Es | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska3PadC2Es(long *param_1,undefined2 param_2)

{
  undefined2 uVar1;
  int iVar2;
  undefined *puVar3;
  
  *param_1 = (long)(PTR__ZTVN4Aska14BasePeripheralE_02cbc550 + 0x10);
  Aska::FastCriticalSection::FastCriticalSection()(param_1 + 1);
  *(undefined2 *)((long)param_1 + 0x16c) = param_2;
  puVar3 = PTR__ZTVN4Aska3PadE_02cbf0d0;
  param_1[0x13] = 0xffff0000ffff;
  param_1[0x14] = 0xffff00ff;
  *(undefined2 *)((long)param_1 + 0xb2) = 0;
  *(undefined2 *)((long)param_1 + 0xb4) = 0;
  *(undefined4 *)(param_1 + 0x21) = 0;
  *(undefined2 *)((long)param_1 + 0x10c) = 0;
  *(undefined2 *)(param_1 + 0x15) = 0;
  *(undefined4 *)(param_1 + 0x2a) = 0;
  *(undefined1 *)((long)param_1 + 0x16e) = 0;
  *(undefined2 *)((long)param_1 + 0x10e) = 0x810;
  *param_1 = (long)(puVar3 + 0x10);
  memset(param_1 + 0x17,0,0x50);
  *(undefined8 *)((long)param_1 + 0xaa) = 0;
  param_1[0x22] = 0x810000008100000;
  param_1[0x23] = 0x810000008100000;
  param_1[0x24] = 0x810000008100000;
  param_1[0x25] = 0x810000008100000;
  param_1[0x26] = 0x810000008100000;
  param_1[0x27] = 0x810000008100000;
  param_1[0x28] = 0x810000008100000;
  param_1[0x29] = 0x810000008100000;
  *(undefined8 *)((long)param_1 + 0x15c) = 0;
  *(undefined8 *)((long)param_1 + 0x154) = 0x7fff7fff7fff7fff;
  iVar2 = 0x7fff - *(short *)((long)param_1 + 0x16c);
  if (0x7ffe < iVar2) {
    iVar2 = 0x7fff;
  }
  uVar1 = (undefined2)iVar2;
  *(undefined2 *)((long)param_1 + 0x164) = uVar1;
  *(undefined2 *)((long)param_1 + 0x166) = uVar1;
  *(undefined2 *)(param_1 + 0x2d) = uVar1;
  *(undefined2 *)((long)param_1 + 0x16a) = uVar1;
  return;
}

// ==== Aska::Pad::Release()
// vaddr 0x1f53494 | ghidra 0x2053494 | size 416 | symbol _ZN4Aska3Pad7ReleaseEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska3Pad7ReleaseEv(long param_1)

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
                if (cVar3 == '\0') goto code_r0x0205361c;
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
code_r0x0205361c:
        do {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
          if (bVar4) {
            *piVar2 = *piVar2 + -1;
            cVar3 = ExclusiveMonitorsStatus();
          }
        } while (cVar3 != '\0');
        DataMemoryBarrier(2,3);
code_r0x02053508:
        memset(param_1 + 0xb8,0,0x50);
        *(undefined2 *)(param_1 + 0x110) = 0;
        *(undefined2 *)(param_1 + 0x114) = 0;
        *(undefined2 *)(param_1 + 0x118) = 0;
        *(undefined2 *)(param_1 + 0x11c) = 0;
        *(undefined2 *)(param_1 + 0x120) = 0;
        *(undefined2 *)(param_1 + 0x124) = 0;
        *(undefined2 *)(param_1 + 0x128) = 0;
        *(undefined2 *)(param_1 + 300) = 0;
        *(undefined2 *)(param_1 + 0x130) = 0;
        *(undefined2 *)(param_1 + 0x134) = 0;
        *(undefined2 *)(param_1 + 0x138) = 0;
        *(undefined2 *)(param_1 + 0x13c) = 0;
        *(undefined2 *)(param_1 + 0x140) = 0;
        *(undefined2 *)(param_1 + 0x144) = 0;
        *(undefined2 *)(param_1 + 0x148) = 0;
        *(undefined2 *)(param_1 + 0x14c) = 0;
        *(undefined4 *)(param_1 + 0xae) = 0;
        *(undefined8 *)(param_1 + 0xa6) = 0;
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
            Aska::Semaphore::Signal() const(param_1 + 0x80);
          }
        }
        (*(code *)PTR__ZN4Aska14BasePeripheral7ReleaseEv_02cb1f90)(param_1);
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
  goto code_r0x02053508;
}

// ==== Aska::Pad::GetStatus()
// vaddr 0x1f53634 | ghidra 0x2053634 | size 352 | symbol _ZN4Aska3Pad9GetStatusEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska3Pad9GetStatusEv(long param_1)

{
  int *piVar1;
  int *piVar2;
  char cVar3;
  bool bVar4;
  ulong uVar5;
  int iVar6;
  
  uVar5 = Aska::BasePeripheral::GetStatus()();
  if ((uVar5 & 1) == 0) {
    return 0;
  }
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
                if (cVar3 == '\0') goto code_r0x0205377c;
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
code_r0x0205377c:
        do {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
          if (bVar4) {
            *piVar2 = *piVar2 + -1;
            cVar3 = ExclusiveMonitorsStatus();
          }
        } while (cVar3 != '\0');
        DataMemoryBarrier(2,3);
        goto code_r0x020536b8;
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
code_r0x020536b8:
  Aska::Pad::UpdateKeyStatus()(param_1);
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
      Aska::Semaphore::Signal() const(param_1 + 0x80);
    }
  }
  return 1;
}

// ==== Aska::Pad::UpdateKeyStatus()
// vaddr 0x1f53794 | ghidra 0x2053794 | size 400 | symbol _ZN4Aska3Pad15UpdateKeyStatusEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska3Pad15UpdateKeyStatusEv(long param_1)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  ushort uVar4;
  short sVar5;
  short sVar6;
  ushort uVar7;
  long lVar8;
  long lVar9;
  ushort *puVar10;
  
  uVar3 = *(uint *)(param_1 + 0x108) ^ 1;
  lVar9 = param_1 + (long)(int)uVar3 * 0x28;
  puVar10 = (ushort *)(lVar9 + 0xb8);
  *(ushort *)(lVar9 + 0xba) = *puVar10;
  *puVar10 = *(ushort *)(param_1 + 0xa6);
  Aska::Pad::CalcAnalogPosition(short*, short*, short*, short*)(param_1,lVar9 + 0xc6,lVar9 + 200,lVar9 + 0xca,lVar9 + 0xcc);
  sVar5 = *(short *)(lVar9 + 0xc6);
  *(float *)(lVar9 + 0xd0) = (float)(int)sVar5 / (float)(int)*(short *)(param_1 + 0x164);
  sVar6 = *(short *)(lVar9 + 200);
  *(float *)(lVar9 + 0xd4) = (float)(int)sVar6 / (float)(int)*(short *)(param_1 + 0x166);
  *(float *)(lVar9 + 0xd8) =
       (float)(int)*(short *)(lVar9 + 0xca) / (float)(int)*(short *)(param_1 + 0x168);
  *(float *)(lVar9 + 0xdc) =
       (float)(int)*(short *)(lVar9 + 0xcc) / (float)(int)*(short *)(param_1 + 0x16a);
  *(undefined1 *)(lVar9 + 0xce) = *(undefined1 *)(param_1 + 0xa8);
  *(undefined1 *)(lVar9 + 0xcf) = *(undefined1 *)(param_1 + 0xa9);
  if (*(char *)(param_1 + 0x16e) == '\0') {
    uVar7 = *puVar10;
  }
  else {
    iVar1 = (int)*(short *)(param_1 + 0x154) >> 1;
    iVar2 = (int)*(short *)(param_1 + 0x156) >> 1;
    uVar7 = *puVar10 | (ushort)(iVar1 < sVar5) << 3 | (ushort)((int)sVar5 < -iVar1) << 2 |
            (ushort)(iVar2 < sVar6) | (ushort)((int)sVar6 < -iVar2) << 1;
    *puVar10 = uVar7;
  }
  lVar8 = param_1 + (long)(int)uVar3 * 0x28;
  *(ushort *)(lVar8 + 0xbc) = *(ushort *)(lVar8 + 0xbc) | uVar7;
  uVar4 = *(ushort *)(lVar9 + 0xba);
  *(ushort *)(lVar8 + 0xbe) = uVar7 & (uVar4 ^ 0xffff) | *(ushort *)(lVar8 + 0xbe);
  *(ushort *)(lVar8 + 0xc0) = uVar4 & (uVar7 ^ 0xffff) | *(ushort *)(lVar8 + 0xc0);
  Aska::Pad::UpdateKeyRepeat(Aska::Pad::Keys*)(param_1,puVar10);
  *(undefined1 *)(param_1 + 0x9b) = 1;
  return;
}

// ==== Aska::Pad::UpdateKeyRepeat(Aska::Pad::Keys*)
// vaddr 0x1f53924 | ghidra 0x2053924 | size 448 | symbol _ZN4Aska3Pad15UpdateKeyRepeatEPNS0_4KeysE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska3Pad15UpdateKeyRepeatEPNS0_4KeysE(long param_1,ushort *param_2)

{
  uint uVar1;
  int iVar2;
  short sVar3;
  uint uVar4;
  int iVar5;
  ushort *puVar6;
  long lVar7;
  short *psVar8;
  undefined2 *puVar9;
  
  iVar5 = (**(code **)(**(long **)PTR__ZN4Aska6Global8m_pVSyncE_02cbd460 + 8))
                    (*(long **)PTR__ZN4Aska6Global8m_pVSyncE_02cbd460);
  iVar2 = *(int *)(param_1 + 0x150);
  if (iVar5 != iVar2) {
    *(int *)(param_1 + 0x150) = iVar5;
  }
  if ((*param_2 == 0) || (*param_2 != param_2[1])) {
    *(undefined2 *)(param_1 + 0x10c) = 0;
    param_2[5] = param_2[5] | param_2[3];
    if (iVar5 == iVar2) goto code_r0x02053a80;
  }
  else {
    if (iVar5 == iVar2) {
code_r0x02053a80:
      lVar7 = 0;
      puVar9 = (undefined2 *)(param_1 + 0x110);
      do {
        uVar1 = 1 << (ulong)((uint)lVar7 & 0x1f);
        if (((uVar1 & *param_2) == 0) || ((uVar1 & *param_2) != (uVar1 & param_2[1]))) {
          *puVar9 = 0;
          param_2[6] = (ushort)uVar1 & param_2[3] | param_2[6];
        }
        lVar7 = lVar7 + 1;
        puVar9 = puVar9 + 2;
      } while (lVar7 != 0x10);
      return;
    }
    sVar3 = *(short *)(param_1 + 0x10c) + 1;
    *(short *)(param_1 + 0x10c) = sVar3;
    if ((short)(ushort)*(byte *)(param_1 + 0x10e) <= sVar3) {
      param_2[5] = param_2[5] | *param_2;
      *(ushort *)(param_1 + 0x10c) =
           *(short *)(param_1 + 0x10c) - (ushort)*(byte *)(param_1 + 0x10f);
    }
  }
  puVar6 = param_2 + 6;
  lVar7 = 0;
  psVar8 = (short *)(param_1 + 0x110);
  do {
    uVar4 = 1 << (ulong)((uint)lVar7 & 0x1f);
    uVar1 = uVar4 & *param_2;
    if ((uVar1 == 0) || (uVar1 != (uVar4 & param_2[1]))) {
      *psVar8 = 0;
      *puVar6 = (ushort)uVar4 & param_2[3] | *puVar6;
    }
    else {
      sVar3 = *psVar8;
      *psVar8 = sVar3 + 1;
      if ((short)(ushort)*(byte *)(psVar8 + 1) <= (short)(sVar3 + 1)) {
        *puVar6 = (ushort)uVar1 | *puVar6;
        *psVar8 = *psVar8 - (ushort)*(byte *)((long)psVar8 + 3);
      }
    }
    lVar7 = lVar7 + 1;
    psVar8 = psVar8 + 2;
  } while (lVar7 != 0x10);
  return;
}

// ==== Aska::Pad::EmulateAnalogAsDigital(Aska::Pad::Keys*)
// vaddr 0x1f53ae4 | ghidra 0x2053ae4 | size 104 | symbol _ZN4Aska3Pad22EmulateAnalogAsDigitalEPNS0_4KeysE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska3Pad22EmulateAnalogAsDigitalEPNS0_4KeysE(long param_1,ushort *param_2)

{
  int iVar1;
  ushort uVar2;
  
  if (*(char *)(param_1 + 0x16e) != '\0') {
    iVar1 = (int)*(short *)(param_1 + 0x154) >> 1;
    uVar2 = *param_2 | (ushort)(iVar1 < (short)param_2[7]) << 3 |
            (ushort)((int)(short)param_2[7] < -iVar1) << 2;
    *param_2 = uVar2;
    iVar1 = (int)*(short *)(param_1 + 0x156) >> 1;
    *param_2 = uVar2 | iVar1 < (short)param_2[8] | (ushort)((int)(short)param_2[8] < -iVar1) << 1;
  }
  return;
}

// ==== Aska::Pad::CalcAnalogPosition(short*, short*, short*, short*)
// vaddr 0x1f53b4c | ghidra 0x2053b4c | size 408 | symbol _ZN4Aska3Pad18CalcAnalogPositionEPsS1_S1_S1_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska3Pad18CalcAnalogPositionEPsS1_S1_S1_
               (long param_1,short *param_2,short *param_3,short *param_4,short *param_5)

{
  short sVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  short sVar5;
  short sVar6;
  short sVar7;
  
  sVar6 = *(short *)(param_1 + 0x16c);
  iVar4 = (int)sVar6;
  if (param_2 != (short *)0x0) {
    iVar3 = (uint)*(ushort *)(param_1 + 0xaa) - (uint)*(ushort *)(param_1 + 0x15c);
    iVar2 = iVar3 * 0x10000;
    sVar5 = (short)iVar3;
    iVar3 = -(int)sVar5;
    if (-0x10000 < iVar2) {
      iVar3 = (int)sVar5;
    }
    if (sVar6 < iVar3) {
      if (iVar2 < 1) {
        sVar5 = sVar5 + sVar6;
      }
      else {
        sVar5 = sVar5 - sVar6;
      }
    }
    else {
      sVar5 = 0;
    }
    sVar1 = *(short *)(param_1 + 0x154);
    sVar7 = sVar1;
    if (((int)sVar5 <= (int)sVar1) && (sVar7 = sVar5, (int)sVar5 < -(int)sVar1)) {
      sVar7 = -sVar1;
    }
    *param_2 = sVar7;
  }
  if (param_3 != (short *)0x0) {
    iVar3 = (uint)*(ushort *)(param_1 + 0xac) - (uint)*(ushort *)(param_1 + 0x15e);
    iVar2 = iVar3 * 0x10000;
    sVar5 = (short)iVar3;
    iVar3 = -(int)sVar5;
    if (-0x10000 < iVar2) {
      iVar3 = (int)sVar5;
    }
    if (iVar4 < iVar3) {
      if (iVar2 < 1) {
        sVar5 = sVar5 + sVar6;
      }
      else {
        sVar5 = sVar5 - sVar6;
      }
    }
    else {
      sVar5 = 0;
    }
    sVar1 = *(short *)(param_1 + 0x156);
    sVar7 = sVar1;
    if (((int)sVar5 <= (int)sVar1) && (sVar7 = sVar5, (int)sVar5 < -(int)sVar1)) {
      sVar7 = -sVar1;
    }
    *param_3 = sVar7;
  }
  if (param_4 != (short *)0x0) {
    iVar3 = (uint)*(ushort *)(param_1 + 0xae) - (uint)*(ushort *)(param_1 + 0x160);
    iVar2 = iVar3 * 0x10000;
    sVar5 = (short)iVar3;
    iVar3 = -(int)sVar5;
    if (-0x10000 < iVar2) {
      iVar3 = (int)sVar5;
    }
    if (iVar4 < iVar3) {
      if (iVar2 < 1) {
        sVar5 = sVar5 + sVar6;
      }
      else {
        sVar5 = sVar5 - sVar6;
      }
    }
    else {
      sVar5 = 0;
    }
    sVar1 = *(short *)(param_1 + 0x158);
    sVar7 = sVar1;
    if (((int)sVar5 <= (int)sVar1) && (sVar7 = sVar5, (int)sVar5 < -(int)sVar1)) {
      sVar7 = -sVar1;
    }
    *param_4 = sVar7;
  }
  if (param_5 != (short *)0x0) {
    iVar3 = (uint)*(ushort *)(param_1 + 0xb0) - (uint)*(ushort *)(param_1 + 0x162);
    iVar2 = iVar3 * 0x10000;
    sVar5 = (short)iVar3;
    iVar3 = -(int)sVar5;
    if (-0x10000 < iVar2) {
      iVar3 = (int)sVar5;
    }
    if (iVar4 < iVar3) {
      if (iVar2 < 1) {
        sVar5 = sVar5 + sVar6;
      }
      else {
        sVar5 = sVar5 - sVar6;
      }
    }
    else {
      sVar5 = 0;
    }
    sVar7 = *(short *)(param_1 + 0x15a);
    sVar6 = sVar7;
    if (((int)sVar5 <= (int)sVar7) && (sVar6 = sVar5, (int)sVar5 < -(int)sVar7)) {
      sVar6 = -sVar7;
    }
    *param_5 = sVar6;
  }
  return;
}

// ==== Aska::Pad::CalcAnalogTrigger(unsigned char*, unsigned char*)
// vaddr 0x1f53ce4 | ghidra 0x2053ce4 | size 20 | symbol _ZN4Aska3Pad17CalcAnalogTriggerEPhS1_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska3Pad17CalcAnalogTriggerEPhS1_(long param_1,undefined1 *param_2,undefined1 *param_3)

{
  *param_2 = *(undefined1 *)(param_1 + 0xa8);
  *param_3 = *(undefined1 *)(param_1 + 0xa9);
  return;
}

// ==== Aska::Pad::ResetStatus()
// vaddr 0x1f53cf8 | ghidra 0x2053cf8 | size 36 | symbol _ZN4Aska3Pad11ResetStatusEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska3Pad11ResetStatusEv(long param_1)

{
  long lVar1;
  
  lVar1 = param_1 + (long)*(int *)(param_1 + 0x108) * 0x28;
  *(undefined8 *)(lVar1 + 0xd8) = 0;
  *(undefined8 *)(lVar1 + 0xd0) = 0;
  *(undefined8 *)(lVar1 + 200) = 0;
  *(undefined8 *)(lVar1 + 0xc0) = 0;
  *(undefined8 *)(lVar1 + 0xb8) = 0;
  *(undefined1 *)(param_1 + 0x9b) = 0;
  return;
}

// ==== Aska::Pad::Flip()
// vaddr 0x1f53d1c | ghidra 0x2053d1c | size 384 | symbol _ZN4Aska3Pad4FlipEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska3Pad4FlipEv(long *param_1)

{
  int *piVar1;
  uint uVar2;
  uint uVar3;
  char cVar4;
  bool bVar5;
  ulong uVar6;
  int iVar7;
  long *plVar8;
  
  plVar8 = param_1 + 8;
  (**(code **)(*param_1 + 0x50))();
  iVar7 = 0;
  do {
    while ((int)*plVar8 != -1) {
      ClearExclusiveLocal();
      bVar5 = 0x1fe < iVar7;
      iVar7 = iVar7 + 1;
      if (bVar5) {
        piVar1 = (int *)((long)param_1 + 0x44);
        do {
          cVar4 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar5) {
            *piVar1 = *piVar1 + 1;
            cVar4 = ExclusiveMonitorsStatus();
          }
        } while (cVar4 != '\0');
        do {
          if ((int)*plVar8 != -1) {
            ClearExclusiveLocal();
            do {
              uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x10);
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
                Aska::Semaphore::Wait() const(param_1 + 0x10);
              }
              do {
                cVar4 = '\x01';
                bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
                if (bVar5) {
                  *piVar1 = *piVar1 + 1;
                  cVar4 = ExclusiveMonitorsStatus();
                }
              } while (cVar4 != '\0');
              while ((int)*plVar8 == -1) {
                cVar4 = '\x01';
                bVar5 = (bool)ExclusiveMonitorPass(plVar8,0x10);
                if (bVar5) {
                  *(int *)plVar8 = 0;
                  cVar4 = ExclusiveMonitorsStatus();
                }
                if (cVar4 == '\0') goto code_r0x02053e84;
              }
              ClearExclusiveLocal();
            } while( true );
          }
          cVar4 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(plVar8,0x10);
          if (bVar5) {
            *(int *)plVar8 = 0;
            cVar4 = ExclusiveMonitorsStatus();
          }
        } while (cVar4 != '\0');
code_r0x02053e84:
        do {
          cVar4 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar5) {
            *piVar1 = *piVar1 + -1;
            cVar4 = ExclusiveMonitorsStatus();
          }
        } while (cVar4 != '\0');
        DataMemoryBarrier(2,3);
code_r0x02053d9c:
        uVar3 = *(uint *)(param_1 + 0x21);
        uVar2 = uVar3 ^ 1;
        *(uint *)(param_1 + 0x21) = uVar2;
        *(short *)(param_1 + (long)(int)uVar3 * 5 + 0x17) =
             (short)param_1[(long)(int)uVar2 * 5 + 0x17];
        DataMemoryBarrier(2,3);
        *(undefined4 *)(param_1 + 8) = 0xffffffff;
        DataMemoryBarrier(2,3);
        piVar1 = (int *)((long)param_1 + 0x44);
        if (0x14 < *piVar1) {
          do {
            cVar4 = '\x01';
            bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
            if (bVar5) {
              *piVar1 = *piVar1 + -1;
              cVar4 = ExclusiveMonitorsStatus();
            }
          } while (cVar4 != '\0');
          uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x10);
          if ((uVar6 & 1) != 0) {
            (*(code *)PTR__ZNK4Aska9Semaphore6SignalEv_02c96cd0)(param_1 + 0x10);
            return;
          }
        }
        return;
      }
    }
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(plVar8,0x10);
    if (bVar5) {
      *(int *)plVar8 = 0;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
  DataMemoryBarrier(2,3);
  goto code_r0x02053d9c;
}

// ==== Aska::Pad::EnableRumble(bool)
// vaddr 0x1f53e9c | ghidra 0x2053e9c | size 28 | symbol _ZN4Aska3Pad12EnableRumbleEb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska3Pad12EnableRumbleEb(long param_1,byte param_2)

{
  if (*(char *)(param_1 + 0xa4) != '\0') {
    if ((param_2 & 1) == 0) {
      *(undefined4 *)(param_1 + 0xb2) = 0;
    }
    *(byte *)(param_1 + 0xa5) = param_2 & 1;
  }
  return;
}

// ==== Aska::Pad::SetRumble(unsigned short, unsigned short)
// vaddr 0x1f53eb8 | ghidra 0x2053eb8 | size 28 | symbol _ZN4Aska3Pad9SetRumbleEtt | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska3Pad9SetRumbleEtt(long param_1,undefined2 param_2,undefined2 param_3)

{
  undefined2 uVar1;
  undefined2 uVar2;
  bool bVar3;
  
  bVar3 = *(char *)(param_1 + 0xa5) != '\0';
  uVar1 = 0;
  if (bVar3) {
    uVar1 = param_2;
  }
  uVar2 = 0;
  if (bVar3) {
    uVar2 = param_3;
  }
  *(undefined2 *)(param_1 + 0xb2) = uVar1;
  *(undefined2 *)(param_1 + 0xb4) = uVar2;
  return;
}

// ==== Aska::Pad::SetAnalogMax(short, short, short, short)
// vaddr 0x1f53ed4 | ghidra 0x2053ed4 | size 96 | symbol _ZN4Aska3Pad12SetAnalogMaxEssss | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska3Pad12SetAnalogMaxEssss
               (long param_1,short param_2,short param_3,short param_4,short param_5)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  *(short *)(param_1 + 0x154) = param_2;
  *(short *)(param_1 + 0x156) = param_3;
  *(short *)(param_1 + 0x158) = param_4;
  *(short *)(param_1 + 0x15a) = param_5;
  iVar3 = 0x7fff - *(short *)(param_1 + 0x16c);
  iVar1 = (int)param_2;
  if (iVar3 <= param_2) {
    iVar1 = iVar3;
  }
  *(short *)(param_1 + 0x164) = (short)iVar1;
  iVar1 = (int)param_3;
  if (iVar3 <= param_3) {
    iVar1 = iVar3;
  }
  *(short *)(param_1 + 0x166) = (short)iVar1;
  iVar1 = (int)param_4;
  if (iVar3 <= param_4) {
    iVar1 = iVar3;
  }
  iVar2 = (int)param_5;
  if (iVar3 <= param_5) {
    iVar2 = iVar3;
  }
  *(short *)(param_1 + 0x168) = (short)iVar1;
  *(short *)(param_1 + 0x16a) = (short)iVar2;
  return;
}

// ==== Aska::Pad::GetAnalogPosition(short*, short*, short*, short*) const
// vaddr 0x1f53f34 | ghidra 0x2053f34 | size 88 | symbol _ZNK4Aska3Pad17GetAnalogPositionEPsS1_S1_S1_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK4Aska3Pad17GetAnalogPositionEPsS1_S1_S1_
               (long param_1,undefined2 *param_2,undefined2 *param_3,undefined2 *param_4,
               undefined2 *param_5)

{
  long lVar1;
  
  lVar1 = (long)*(int *)(param_1 + 0x108);
  if (param_2 != (undefined2 *)0x0) {
    *param_2 = *(undefined2 *)(param_1 + lVar1 * 0x28 + 0xc6);
  }
  if (param_3 != (undefined2 *)0x0) {
    *param_3 = *(undefined2 *)(param_1 + lVar1 * 0x28 + 200);
  }
  if (param_4 != (undefined2 *)0x0) {
    *param_4 = *(undefined2 *)(param_1 + lVar1 * 0x28 + 0xca);
  }
  if (param_5 != (undefined2 *)0x0) {
    *param_5 = *(undefined2 *)(param_1 + lVar1 * 0x28 + 0xcc);
  }
  return;
}

// ==== Aska::Pad::GetAnalogPosition(float*, float*, float*, float*) const
// vaddr 0x1f53f8c | ghidra 0x2053f8c | size 88 | symbol _ZNK4Aska3Pad17GetAnalogPositionEPfS1_S1_S1_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK4Aska3Pad17GetAnalogPositionEPfS1_S1_S1_
               (long param_1,undefined4 *param_2,undefined4 *param_3,undefined4 *param_4,
               undefined4 *param_5)

{
  long lVar1;
  
  lVar1 = (long)*(int *)(param_1 + 0x108);
  if (param_2 != (undefined4 *)0x0) {
    *param_2 = *(undefined4 *)(param_1 + lVar1 * 0x28 + 0xd0);
  }
  if (param_3 != (undefined4 *)0x0) {
    *param_3 = *(undefined4 *)(param_1 + lVar1 * 0x28 + 0xd4);
  }
  if (param_4 != (undefined4 *)0x0) {
    *param_4 = *(undefined4 *)(param_1 + lVar1 * 0x28 + 0xd8);
  }
  if (param_5 != (undefined4 *)0x0) {
    *param_5 = *(undefined4 *)(param_1 + lVar1 * 0x28 + 0xdc);
  }
  return;
}

// ==== Aska::Pad::CalcAnalogPositionMax()
// vaddr 0x1f53fe4 | ghidra 0x2053fe4 | size 80 | symbol _ZN4Aska3Pad21CalcAnalogPositionMaxEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska3Pad21CalcAnalogPositionMaxEv(long param_1)

{
  int iVar1;
  int iVar2;
  
  iVar2 = 0x7fff - *(short *)(param_1 + 0x16c);
  iVar1 = (int)*(short *)(param_1 + 0x154);
  if (iVar2 <= *(short *)(param_1 + 0x154)) {
    iVar1 = iVar2;
  }
  *(short *)(param_1 + 0x164) = (short)iVar1;
  iVar1 = (int)*(short *)(param_1 + 0x156);
  if (iVar2 <= *(short *)(param_1 + 0x156)) {
    iVar1 = iVar2;
  }
  *(short *)(param_1 + 0x166) = (short)iVar1;
  iVar1 = (int)*(short *)(param_1 + 0x158);
  if (iVar2 <= *(short *)(param_1 + 0x158)) {
    iVar1 = iVar2;
  }
  *(short *)(param_1 + 0x168) = (short)iVar1;
  iVar1 = (int)*(short *)(param_1 + 0x15a);
  if (iVar2 <= *(short *)(param_1 + 0x15a)) {
    iVar1 = iVar2;
  }
  *(short *)(param_1 + 0x16a) = (short)iVar1;
  return;
}

// ==== Aska::Pad::GetAnalogTrigger(unsigned char*, unsigned char*) const
// vaddr 0x1f54034 | ghidra 0x2054034 | size 48 | symbol _ZNK4Aska3Pad16GetAnalogTriggerEPhS1_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK4Aska3Pad16GetAnalogTriggerEPhS1_(long param_1,undefined1 *param_2,undefined1 *param_3)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x108);
  if (param_2 != (undefined1 *)0x0) {
    *param_2 = *(undefined1 *)(param_1 + (long)iVar1 * 0x28 + 0xce);
  }
  if (param_3 != (undefined1 *)0x0) {
    *param_3 = *(undefined1 *)(param_1 + (long)iVar1 * 0x28 + 0xcf);
  }
  return;
}

// ==== Aska::Pad::SetCalibration(short, short, short, short, short)
// vaddr 0x1f54064 | ghidra 0x2054064 | size 96 | symbol _ZN4Aska3Pad14SetCalibrationEsssss | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska3Pad14SetCalibrationEsssss
               (long param_1,undefined2 param_2,undefined2 param_3,undefined2 param_4,
               undefined2 param_5,short param_6)

{
  int iVar1;
  int iVar2;
  
  *(undefined2 *)(param_1 + 0x15c) = param_2;
  *(undefined2 *)(param_1 + 0x15e) = param_3;
  *(undefined2 *)(param_1 + 0x160) = param_4;
  *(undefined2 *)(param_1 + 0x162) = param_5;
  *(short *)(param_1 + 0x16c) = param_6;
  iVar2 = 0x7fff - param_6;
  iVar1 = (int)*(short *)(param_1 + 0x154);
  if (iVar2 <= *(short *)(param_1 + 0x154)) {
    iVar1 = iVar2;
  }
  *(short *)(param_1 + 0x164) = (short)iVar1;
  iVar1 = (int)*(short *)(param_1 + 0x156);
  if (iVar2 <= *(short *)(param_1 + 0x156)) {
    iVar1 = iVar2;
  }
  *(short *)(param_1 + 0x166) = (short)iVar1;
  iVar1 = (int)*(short *)(param_1 + 0x158);
  if (iVar2 <= *(short *)(param_1 + 0x158)) {
    iVar1 = iVar2;
  }
  *(short *)(param_1 + 0x168) = (short)iVar1;
  iVar1 = (int)*(short *)(param_1 + 0x15a);
  if (iVar2 <= *(short *)(param_1 + 0x15a)) {
    iVar1 = iVar2;
  }
  *(short *)(param_1 + 0x16a) = (short)iVar1;
  return;
}

// ==== Aska::Pad::SetRepeatEachThreshold(unsigned short, unsigned char)
// vaddr 0x1f540c4 | ghidra 0x20540c4 | size 200 | symbol _ZN4Aska3Pad22SetRepeatEachThresholdEth | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska3Pad22SetRepeatEachThresholdEth(long param_1,uint param_2,undefined1 param_3)

{
  uint uVar1;
  
  uVar1 = param_2 & 0xffff;
  if ((param_2 & 1) != 0) {
    *(undefined1 *)(param_1 + 0x112) = param_3;
  }
  if ((uVar1 >> 1 & 1) != 0) {
    *(undefined1 *)(param_1 + 0x116) = param_3;
  }
  if ((uVar1 >> 2 & 1) != 0) {
    *(undefined1 *)(param_1 + 0x11a) = param_3;
  }
  if ((uVar1 >> 3 & 1) != 0) {
    *(undefined1 *)(param_1 + 0x11e) = param_3;
  }
  if ((uVar1 >> 4 & 1) != 0) {
    *(undefined1 *)(param_1 + 0x122) = param_3;
  }
  if ((uVar1 >> 5 & 1) != 0) {
    *(undefined1 *)(param_1 + 0x126) = param_3;
  }
  if ((uVar1 >> 6 & 1) != 0) {
    *(undefined1 *)(param_1 + 0x12a) = param_3;
  }
  if ((uVar1 >> 7 & 1) != 0) {
    *(undefined1 *)(param_1 + 0x12e) = param_3;
  }
  if ((uVar1 >> 8 & 1) != 0) {
    *(undefined1 *)(param_1 + 0x132) = param_3;
  }
  if ((uVar1 >> 9 & 1) != 0) {
    *(undefined1 *)(param_1 + 0x136) = param_3;
  }
  if ((uVar1 >> 10 & 1) != 0) {
    *(undefined1 *)(param_1 + 0x13a) = param_3;
  }
  if ((uVar1 >> 0xb & 1) != 0) {
    *(undefined1 *)(param_1 + 0x13e) = param_3;
  }
  if ((uVar1 >> 0xc & 1) != 0) {
    *(undefined1 *)(param_1 + 0x142) = param_3;
  }
  if ((uVar1 >> 0xd & 1) != 0) {
    *(undefined1 *)(param_1 + 0x146) = param_3;
  }
  if ((uVar1 >> 0xe & 1) != 0) {
    *(undefined1 *)(param_1 + 0x14a) = param_3;
  }
  if (uVar1 >> 0xf == 0) {
    return;
  }
  *(undefined1 *)(param_1 + 0x14e) = param_3;
  return;
}

// ==== Aska::Pad::SetRepeatEachInterval(unsigned short, unsigned char)
// vaddr 0x1f5418c | ghidra 0x205418c | size 200 | symbol _ZN4Aska3Pad21SetRepeatEachIntervalEth | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska3Pad21SetRepeatEachIntervalEth(long param_1,uint param_2,undefined1 param_3)

{
  uint uVar1;
  
  uVar1 = param_2 & 0xffff;
  if ((param_2 & 1) != 0) {
    *(undefined1 *)(param_1 + 0x113) = param_3;
  }
  if ((uVar1 >> 1 & 1) != 0) {
    *(undefined1 *)(param_1 + 0x117) = param_3;
  }
  if ((uVar1 >> 2 & 1) != 0) {
    *(undefined1 *)(param_1 + 0x11b) = param_3;
  }
  if ((uVar1 >> 3 & 1) != 0) {
    *(undefined1 *)(param_1 + 0x11f) = param_3;
  }
  if ((uVar1 >> 4 & 1) != 0) {
    *(undefined1 *)(param_1 + 0x123) = param_3;
  }
  if ((uVar1 >> 5 & 1) != 0) {
    *(undefined1 *)(param_1 + 0x127) = param_3;
  }
  if ((uVar1 >> 6 & 1) != 0) {
    *(undefined1 *)(param_1 + 299) = param_3;
  }
  if ((uVar1 >> 7 & 1) != 0) {
    *(undefined1 *)(param_1 + 0x12f) = param_3;
  }
  if ((uVar1 >> 8 & 1) != 0) {
    *(undefined1 *)(param_1 + 0x133) = param_3;
  }
  if ((uVar1 >> 9 & 1) != 0) {
    *(undefined1 *)(param_1 + 0x137) = param_3;
  }
  if ((uVar1 >> 10 & 1) != 0) {
    *(undefined1 *)(param_1 + 0x13b) = param_3;
  }
  if ((uVar1 >> 0xb & 1) != 0) {
    *(undefined1 *)(param_1 + 0x13f) = param_3;
  }
  if ((uVar1 >> 0xc & 1) != 0) {
    *(undefined1 *)(param_1 + 0x143) = param_3;
  }
  if ((uVar1 >> 0xd & 1) != 0) {
    *(undefined1 *)(param_1 + 0x147) = param_3;
  }
  if ((uVar1 >> 0xe & 1) != 0) {
    *(undefined1 *)(param_1 + 0x14b) = param_3;
  }
  if (uVar1 >> 0xf == 0) {
    return;
  }
  *(undefined1 *)(param_1 + 0x14f) = param_3;
  return;
}

// ==== Aska::Pad::Get(unsigned long, void*) const
// vaddr 0x1f54254 | ghidra 0x2054254 | size 508 | symbol _ZNK4Aska3Pad3GetEmPv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska3Pad3GetEmPv(long param_1,ulong param_2,byte *param_3)

{
  byte bVar1;
  undefined8 uVar2;
  
  if ((param_2 & 0xffff00000000) == 0) {
    switch((uint)param_2 & 0xffff) {
    case 5:
      bVar1 = *(byte *)(param_1 + 0xa4);
      break;
    case 6:
      bVar1 = *(byte *)(param_1 + 0xa5);
      break;
    case 7:
      *(undefined2 *)param_3 = *(undefined2 *)(param_1 + 0xb2);
      return 1;
    case 8:
      *(undefined2 *)param_3 = *(undefined2 *)(param_1 + 0xb4);
      return 1;
    default:
      goto code_r0x011af4f0;
    case 0x10:
      bVar1 = *(byte *)(param_1 + 0x10e);
      break;
    case 0x11:
      bVar1 = *(byte *)(param_1 + 0x10f);
      break;
    case 0x12:
      bVar1 = *(byte *)(param_1 + 0x112);
      break;
    case 0x13:
      bVar1 = *(byte *)(param_1 + 0x116);
      break;
    case 0x14:
      bVar1 = *(byte *)(param_1 + 0x11a);
      break;
    case 0x15:
      bVar1 = *(byte *)(param_1 + 0x11e);
      break;
    case 0x16:
      bVar1 = *(byte *)(param_1 + 0x122);
      break;
    case 0x17:
      bVar1 = *(byte *)(param_1 + 0x126);
      break;
    case 0x18:
      bVar1 = *(byte *)(param_1 + 0x12a);
      break;
    case 0x19:
      bVar1 = *(byte *)(param_1 + 0x12e);
      break;
    case 0x1a:
      bVar1 = *(byte *)(param_1 + 0x132);
      break;
    case 0x1b:
      bVar1 = *(byte *)(param_1 + 0x136);
      break;
    case 0x1c:
      bVar1 = *(byte *)(param_1 + 0x13a);
      break;
    case 0x1d:
      bVar1 = *(byte *)(param_1 + 0x13e);
      break;
    case 0x1e:
      bVar1 = *(byte *)(param_1 + 0x142);
      break;
    case 0x1f:
      bVar1 = *(byte *)(param_1 + 0x146);
      break;
    case 0x20:
      bVar1 = *(byte *)(param_1 + 0x14a);
      break;
    case 0x21:
      bVar1 = *(byte *)(param_1 + 0x14e);
      break;
    case 0x22:
      bVar1 = *(byte *)(param_1 + 0x113);
      break;
    case 0x23:
      bVar1 = *(byte *)(param_1 + 0x117);
      break;
    case 0x24:
      bVar1 = *(byte *)(param_1 + 0x11b);
      break;
    case 0x25:
      bVar1 = *(byte *)(param_1 + 0x11f);
      break;
    case 0x26:
      bVar1 = *(byte *)(param_1 + 0x123);
      break;
    case 0x27:
      bVar1 = *(byte *)(param_1 + 0x127);
      break;
    case 0x28:
      bVar1 = *(byte *)(param_1 + 299);
      break;
    case 0x29:
      bVar1 = *(byte *)(param_1 + 0x12f);
      break;
    case 0x2a:
      bVar1 = *(byte *)(param_1 + 0x133);
      break;
    case 0x2b:
      bVar1 = *(byte *)(param_1 + 0x137);
      break;
    case 0x2c:
      bVar1 = *(byte *)(param_1 + 0x13b);
      break;
    case 0x2d:
      bVar1 = *(byte *)(param_1 + 0x13f);
      break;
    case 0x2e:
      bVar1 = *(byte *)(param_1 + 0x143);
      break;
    case 0x2f:
      bVar1 = *(byte *)(param_1 + 0x147);
      break;
    case 0x30:
      bVar1 = *(byte *)(param_1 + 0x14b);
      break;
    case 0x31:
      bVar1 = *(byte *)(param_1 + 0x14f);
      break;
    case 0x48:
      *(undefined2 *)param_3 = *(undefined2 *)(param_1 + 0x154);
      return 1;
    case 0x49:
      *(undefined2 *)param_3 = *(undefined2 *)(param_1 + 0x156);
      return 1;
    case 0x4a:
      *(undefined2 *)param_3 = *(undefined2 *)(param_1 + 0x158);
      return 1;
    case 0x4b:
      *(undefined2 *)param_3 = *(undefined2 *)(param_1 + 0x15a);
      return 1;
    case 0x4c:
      *(undefined2 *)param_3 = *(undefined2 *)(param_1 + 0x15c);
      return 1;
    case 0x4d:
      *(undefined2 *)param_3 = *(undefined2 *)(param_1 + 0x15e);
      return 1;
    case 0x4e:
      *(undefined2 *)param_3 = *(undefined2 *)(param_1 + 0x160);
      return 1;
    case 0x4f:
      *(undefined2 *)param_3 = *(undefined2 *)(param_1 + 0x162);
      return 1;
    case 0x50:
      *(undefined2 *)param_3 = *(undefined2 *)(param_1 + 0x16c);
      return 1;
    case 0x51:
      bVar1 = Aska::Pad::IsAnalogAsDigital() const();
      bVar1 = bVar1 & 1;
    }
    *param_3 = bVar1;
    return 1;
  }
code_r0x011af4f0:
  uVar2 = (*(code *)PTR__ZNK4Aska14BasePeripheral3GetEmPv_02c8fa68)(param_1,(uint)param_2,param_3);
  return uVar2;
}

// ==== Aska::Pad::IsAnalogAsDigital() const
// vaddr 0x1f54450 | ghidra 0x2054450 | size 336 | symbol _ZNK4Aska3Pad17IsAnalogAsDigitalEv | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK4Aska3Pad17IsAnalogAsDigitalEv(long param_1)

{
  int *piVar1;
  int *piVar2;
  char cVar3;
  char cVar4;
  bool bVar5;
  ulong uVar6;
  int iVar7;
  
  piVar1 = (int *)(param_1 + 0x40);
  iVar7 = 0;
  do {
    while (*piVar1 != -1) {
      ClearExclusiveLocal();
      bVar5 = 0x1fe < iVar7;
      iVar7 = iVar7 + 1;
      if (bVar5) {
        piVar2 = (int *)(param_1 + 0x44);
        do {
          cVar3 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
          if (bVar5) {
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
                  bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
                  if (bVar5) {
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
                bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
                if (bVar5) {
                  *piVar2 = *piVar2 + 1;
                  cVar3 = ExclusiveMonitorsStatus();
                }
              } while (cVar3 != '\0');
              while (*piVar1 == -1) {
                cVar3 = '\x01';
                bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
                if (bVar5) {
                  *piVar1 = 0;
                  cVar3 = ExclusiveMonitorsStatus();
                }
                if (cVar3 == '\0') goto code_r0x02054588;
              }
              ClearExclusiveLocal();
            } while( true );
          }
          cVar3 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar5) {
            *piVar1 = 0;
            cVar3 = ExclusiveMonitorsStatus();
          }
        } while (cVar3 != '\0');
code_r0x02054588:
        do {
          cVar3 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
          if (bVar5) {
            *piVar2 = *piVar2 + -1;
            cVar3 = ExclusiveMonitorsStatus();
          }
        } while (cVar3 != '\0');
        DataMemoryBarrier(2,3);
code_r0x020544c4:
        cVar3 = *(char *)(param_1 + 0x16e);
        DataMemoryBarrier(2,3);
        *(undefined4 *)(param_1 + 0x40) = 0xffffffff;
        DataMemoryBarrier(2,3);
        piVar1 = (int *)(param_1 + 0x44);
        if (0x14 < *piVar1) {
          do {
            cVar4 = '\x01';
            bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
            if (bVar5) {
              *piVar1 = *piVar1 + -1;
              cVar4 = ExclusiveMonitorsStatus();
            }
          } while (cVar4 != '\0');
          uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x80);
          if ((uVar6 & 1) != 0) {
            Aska::Semaphore::Signal() const(param_1 + 0x80);
          }
        }
        return cVar3 != '\0';
      }
    }
    cVar3 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar5) {
      *piVar1 = 0;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
  DataMemoryBarrier(2,3);
  goto code_r0x020544c4;
}

// ==== Aska::Pad::Set(unsigned long, void const*)
// vaddr 0x1f545a0 | ghidra 0x20545a0 | size 3308 | symbol _ZN4Aska3Pad3SetEmPKv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska3Pad3SetEmPKv(long param_1,undefined8 param_2,ushort *param_3)

{
  int *piVar1;
  char cVar2;
  bool bVar3;
  int iVar4;
  undefined8 uVar5;
  ulong uVar6;
  ushort uVar7;
  int iVar8;
  int *piVar9;
  
  switch((uint)param_2 & 0xffff) {
  case 6:
    if (*(char *)(param_1 + 0xa4) == '\0') {
      return 1;
    }
    uVar7 = *param_3;
    if ((char)uVar7 == '\0') {
      *(undefined4 *)(param_1 + 0xb2) = 0;
    }
    *(char *)(param_1 + 0xa5) = (char)uVar7;
    return 1;
  case 7:
    uVar7 = (ushort)*(byte *)(param_1 + 0xa5);
    if (*(byte *)(param_1 + 0xa5) != 0) {
      uVar7 = *param_3;
    }
    *(ushort *)(param_1 + 0xb2) = uVar7;
    return 1;
  case 8:
    uVar7 = (ushort)*(byte *)(param_1 + 0xa5);
    if (*(byte *)(param_1 + 0xa5) != 0) {
      uVar7 = *param_3;
    }
    *(ushort *)(param_1 + 0xb4) = uVar7;
    return 1;
  default:
    uVar5 = (*(code *)PTR__ZN4Aska14BasePeripheral3SetEmPKv_02cb1428)(param_1,param_2,param_3);
    return uVar5;
  case 0x10:
    Aska::Pad::SetRepeatThreshold(unsigned char)(param_1,(char)*param_3);
    return 1;
  case 0x11:
    Aska::Pad::SetRepeatInterval(unsigned char)(param_1,(char)*param_3);
    return 1;
  case 0x12:
    *(char *)(param_1 + 0x112) = (char)*param_3;
    return 1;
  case 0x13:
    *(char *)(param_1 + 0x116) = (char)*param_3;
    return 1;
  case 0x14:
    *(char *)(param_1 + 0x11a) = (char)*param_3;
    return 1;
  case 0x15:
    *(char *)(param_1 + 0x11e) = (char)*param_3;
    return 1;
  case 0x16:
    *(char *)(param_1 + 0x122) = (char)*param_3;
    return 1;
  case 0x17:
    *(char *)(param_1 + 0x126) = (char)*param_3;
    return 1;
  case 0x18:
    *(char *)(param_1 + 0x12a) = (char)*param_3;
    return 1;
  case 0x19:
    *(char *)(param_1 + 0x12e) = (char)*param_3;
    return 1;
  case 0x1a:
    *(char *)(param_1 + 0x132) = (char)*param_3;
    return 1;
  case 0x1b:
    *(char *)(param_1 + 0x136) = (char)*param_3;
    return 1;
  case 0x1c:
    *(char *)(param_1 + 0x13a) = (char)*param_3;
    return 1;
  case 0x1d:
    *(char *)(param_1 + 0x13e) = (char)*param_3;
    return 1;
  case 0x1e:
    *(char *)(param_1 + 0x142) = (char)*param_3;
    return 1;
  case 0x1f:
    *(char *)(param_1 + 0x146) = (char)*param_3;
    return 1;
  case 0x20:
    *(char *)(param_1 + 0x14a) = (char)*param_3;
    return 1;
  case 0x21:
    *(char *)(param_1 + 0x14e) = (char)*param_3;
    return 1;
  case 0x22:
    *(char *)(param_1 + 0x113) = (char)*param_3;
    return 1;
  case 0x23:
    *(char *)(param_1 + 0x117) = (char)*param_3;
    return 1;
  case 0x24:
    *(char *)(param_1 + 0x11b) = (char)*param_3;
    return 1;
  case 0x25:
    *(char *)(param_1 + 0x11f) = (char)*param_3;
    return 1;
  case 0x26:
    *(char *)(param_1 + 0x123) = (char)*param_3;
    return 1;
  case 0x27:
    *(char *)(param_1 + 0x127) = (char)*param_3;
    return 1;
  case 0x28:
    *(char *)(param_1 + 299) = (char)*param_3;
    return 1;
  case 0x29:
    *(char *)(param_1 + 0x12f) = (char)*param_3;
    return 1;
  case 0x2a:
    *(char *)(param_1 + 0x133) = (char)*param_3;
    return 1;
  case 0x2b:
    *(char *)(param_1 + 0x137) = (char)*param_3;
    return 1;
  case 0x2c:
    *(char *)(param_1 + 0x13b) = (char)*param_3;
    return 1;
  case 0x2d:
    *(char *)(param_1 + 0x13f) = (char)*param_3;
    return 1;
  case 0x2e:
    *(char *)(param_1 + 0x143) = (char)*param_3;
    return 1;
  case 0x2f:
    *(char *)(param_1 + 0x147) = (char)*param_3;
    return 1;
  case 0x30:
    *(char *)(param_1 + 0x14b) = (char)*param_3;
    return 1;
  case 0x31:
    *(char *)(param_1 + 0x14f) = (char)*param_3;
    return 1;
  case 0x48:
    piVar9 = (int *)(param_1 + 0x40);
    iVar8 = 0;
    break;
  case 0x49:
    piVar9 = (int *)(param_1 + 0x40);
    iVar8 = 0;
code_r0x020547e4:
    do {
      if (*piVar9 == -1) goto code_r0x020547f0;
      ClearExclusiveLocal();
      bVar3 = iVar8 < 0x1ff;
      iVar8 = iVar8 + 1;
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
      if (*piVar9 != -1) {
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
          while (*piVar9 == -1) {
            cVar2 = '\x01';
            bVar3 = (bool)ExclusiveMonitorPass(piVar9,0x10);
            if (bVar3) {
              *piVar9 = 0;
              cVar2 = ExclusiveMonitorsStatus();
            }
            if (cVar2 == '\0') goto code_r0x02054f64;
          }
          ClearExclusiveLocal();
        } while( true );
      }
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar9,0x10);
      if (bVar3) {
        *piVar9 = 0;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
code_r0x02054f64:
    do {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar3) {
        *piVar1 = *piVar1 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    DataMemoryBarrier(2,3);
    goto code_r0x02054b80;
  case 0x4a:
    piVar9 = (int *)(param_1 + 0x40);
    iVar8 = 0;
code_r0x02054840:
    do {
      if (*piVar9 == -1) goto code_r0x0205484c;
      ClearExclusiveLocal();
      bVar3 = iVar8 < 0x1ff;
      iVar8 = iVar8 + 1;
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
      if (*piVar9 != -1) {
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
          while (*piVar9 == -1) {
            cVar2 = '\x01';
            bVar3 = (bool)ExclusiveMonitorPass(piVar9,0x10);
            if (bVar3) {
              *piVar9 = 0;
              cVar2 = ExclusiveMonitorsStatus();
            }
            if (cVar2 == '\0') goto code_r0x02054fd4;
          }
          ClearExclusiveLocal();
        } while( true );
      }
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar9,0x10);
      if (bVar3) {
        *piVar9 = 0;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
code_r0x02054fd4:
    do {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar3) {
        *piVar1 = *piVar1 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    DataMemoryBarrier(2,3);
    goto code_r0x02054bd8;
  case 0x4b:
    piVar9 = (int *)(param_1 + 0x40);
    iVar8 = 0;
code_r0x0205489c:
    do {
      if (*piVar9 == -1) goto code_r0x020548a8;
      ClearExclusiveLocal();
      bVar3 = iVar8 < 0x1ff;
      iVar8 = iVar8 + 1;
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
      if (*piVar9 != -1) {
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
          while (*piVar9 == -1) {
            cVar2 = '\x01';
            bVar3 = (bool)ExclusiveMonitorPass(piVar9,0x10);
            if (bVar3) {
              *piVar9 = 0;
              cVar2 = ExclusiveMonitorsStatus();
            }
            if (cVar2 == '\0') goto code_r0x02055044;
          }
          ClearExclusiveLocal();
        } while( true );
      }
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar9,0x10);
      if (bVar3) {
        *piVar9 = 0;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
code_r0x02055044:
    do {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar3) {
        *piVar1 = *piVar1 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    DataMemoryBarrier(2,3);
    goto code_r0x02054c30;
  case 0x4c:
    piVar9 = (int *)(param_1 + 0x40);
    iVar8 = 0;
code_r0x020548f8:
    do {
      if (*piVar9 == -1) goto code_r0x02054904;
      ClearExclusiveLocal();
      bVar3 = iVar8 < 0x1ff;
      iVar8 = iVar8 + 1;
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
      if (*piVar9 != -1) {
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
          while (*piVar9 == -1) {
            cVar2 = '\x01';
            bVar3 = (bool)ExclusiveMonitorPass(piVar9,0x10);
            if (bVar3) {
              *piVar9 = 0;
              cVar2 = ExclusiveMonitorsStatus();
            }
            if (cVar2 == '\0') goto code_r0x020550b4;
          }
          ClearExclusiveLocal();
        } while( true );
      }
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar9,0x10);
      if (bVar3) {
        *piVar9 = 0;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
code_r0x020550b4:
    do {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar3) {
        *piVar1 = *piVar1 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    DataMemoryBarrier(2,3);
    goto code_r0x02054c88;
  case 0x4d:
    piVar9 = (int *)(param_1 + 0x40);
    iVar8 = 0;
code_r0x02054954:
    do {
      if (*piVar9 == -1) goto code_r0x02054960;
      ClearExclusiveLocal();
      bVar3 = iVar8 < 0x1ff;
      iVar8 = iVar8 + 1;
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
      if (*piVar9 != -1) {
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
          while (*piVar9 == -1) {
            cVar2 = '\x01';
            bVar3 = (bool)ExclusiveMonitorPass(piVar9,0x10);
            if (bVar3) {
              *piVar9 = 0;
              cVar2 = ExclusiveMonitorsStatus();
            }
            if (cVar2 == '\0') goto code_r0x02055124;
          }
          ClearExclusiveLocal();
        } while( true );
      }
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar9,0x10);
      if (bVar3) {
        *piVar9 = 0;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
code_r0x02055124:
    do {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar3) {
        *piVar1 = *piVar1 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    DataMemoryBarrier(2,3);
    goto code_r0x02054cc8;
  case 0x4e:
    piVar9 = (int *)(param_1 + 0x40);
    iVar8 = 0;
code_r0x020549b0:
    do {
      if (*piVar9 == -1) goto code_r0x020549bc;
      ClearExclusiveLocal();
      bVar3 = iVar8 < 0x1ff;
      iVar8 = iVar8 + 1;
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
      if (*piVar9 != -1) {
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
          while (*piVar9 == -1) {
            cVar2 = '\x01';
            bVar3 = (bool)ExclusiveMonitorPass(piVar9,0x10);
            if (bVar3) {
              *piVar9 = 0;
              cVar2 = ExclusiveMonitorsStatus();
            }
            if (cVar2 == '\0') goto code_r0x02055194;
          }
          ClearExclusiveLocal();
        } while( true );
      }
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar9,0x10);
      if (bVar3) {
        *piVar9 = 0;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
code_r0x02055194:
    do {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar3) {
        *piVar1 = *piVar1 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    DataMemoryBarrier(2,3);
    goto code_r0x02054d08;
  case 0x4f:
    piVar9 = (int *)(param_1 + 0x40);
    iVar8 = 0;
code_r0x02054a0c:
    do {
      if (*piVar9 == -1) goto code_r0x02054a18;
      ClearExclusiveLocal();
      bVar3 = iVar8 < 0x1ff;
      iVar8 = iVar8 + 1;
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
      if (*piVar9 != -1) {
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
          while (*piVar9 == -1) {
            cVar2 = '\x01';
            bVar3 = (bool)ExclusiveMonitorPass(piVar9,0x10);
            if (bVar3) {
              *piVar9 = 0;
              cVar2 = ExclusiveMonitorsStatus();
            }
            if (cVar2 == '\0') goto code_r0x02055204;
          }
          ClearExclusiveLocal();
        } while( true );
      }
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar9,0x10);
      if (bVar3) {
        *piVar9 = 0;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
code_r0x02055204:
    do {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar3) {
        *piVar1 = *piVar1 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    DataMemoryBarrier(2,3);
    goto code_r0x02054d48;
  case 0x50:
    piVar9 = (int *)(param_1 + 0x40);
    iVar8 = 0;
code_r0x02054a68:
    do {
      if (*piVar9 == -1) goto code_r0x02054a74;
      ClearExclusiveLocal();
      bVar3 = iVar8 < 0x1ff;
      iVar8 = iVar8 + 1;
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
      if (*piVar9 != -1) {
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
          while (*piVar9 == -1) {
            cVar2 = '\x01';
            bVar3 = (bool)ExclusiveMonitorPass(piVar9,0x10);
            if (bVar3) {
              *piVar9 = 0;
              cVar2 = ExclusiveMonitorsStatus();
            }
            if (cVar2 == '\0') goto code_r0x02055274;
          }
          ClearExclusiveLocal();
        } while( true );
      }
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar9,0x10);
      if (bVar3) {
        *piVar9 = 0;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
code_r0x02055274:
    do {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar3) {
        *piVar1 = *piVar1 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    DataMemoryBarrier(2,3);
    goto code_r0x02054d88;
  case 0x51:
    Aska::Pad::SetAnalogAsDigital(bool)(param_1,(char)*param_3);
    return 1;
  }
code_r0x02054788:
  do {
    if (*piVar9 == -1) goto code_r0x02054794;
    ClearExclusiveLocal();
    bVar3 = iVar8 < 0x1ff;
    iVar8 = iVar8 + 1;
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
    if (*piVar9 != -1) {
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
        while (*piVar9 == -1) {
          cVar2 = '\x01';
          bVar3 = (bool)ExclusiveMonitorPass(piVar9,0x10);
          if (bVar3) {
            *piVar9 = 0;
            cVar2 = ExclusiveMonitorsStatus();
          }
          if (cVar2 == '\0') goto code_r0x02054ef4;
        }
        ClearExclusiveLocal();
      } while( true );
    }
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar9,0x10);
    if (bVar3) {
      *piVar9 = 0;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
code_r0x02054ef4:
  do {
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar3) {
      *piVar1 = *piVar1 + -1;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
  DataMemoryBarrier(2,3);
  goto code_r0x02054b28;
code_r0x02054a74:
  cVar2 = '\x01';
  bVar3 = (bool)ExclusiveMonitorPass(piVar9,0x10);
  if (bVar3) {
    *piVar9 = 0;
    cVar2 = ExclusiveMonitorsStatus();
  }
  if (cVar2 == '\0') goto code_r0x02054d80;
  goto code_r0x02054a68;
code_r0x02054d80:
  DataMemoryBarrier(2,3);
code_r0x02054d88:
  piVar9 = (int *)(param_1 + 0x44);
  uVar7 = *param_3;
  *(ushort *)(param_1 + 0x16c) = uVar7;
  iVar4 = 0x7fff - (short)uVar7;
  iVar8 = (int)*(short *)(param_1 + 0x154);
  if (iVar4 <= *(short *)(param_1 + 0x154)) {
    iVar8 = iVar4;
  }
  *(short *)(param_1 + 0x164) = (short)iVar8;
  iVar8 = (int)*(short *)(param_1 + 0x156);
  if (iVar4 <= *(short *)(param_1 + 0x156)) {
    iVar8 = iVar4;
  }
  *(short *)(param_1 + 0x166) = (short)iVar8;
  iVar8 = (int)*(short *)(param_1 + 0x158);
  if (iVar4 <= *(short *)(param_1 + 0x158)) {
    iVar8 = iVar4;
  }
  *(short *)(param_1 + 0x168) = (short)iVar8;
  iVar8 = (int)*(short *)(param_1 + 0x15a);
  if (iVar4 <= *(short *)(param_1 + 0x15a)) {
    iVar8 = iVar4;
  }
  *(short *)(param_1 + 0x16a) = (short)iVar8;
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_1 + 0x40) = 0xffffffff;
  DataMemoryBarrier(2,3);
  if (*(int *)(param_1 + 0x44) < 0x15) {
    return 1;
  }
  do {
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar9,0x10);
    if (bVar3) {
      *piVar9 = *piVar9 + -1;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
  goto code_r0x02054e04;
code_r0x02054a18:
  cVar2 = '\x01';
  bVar3 = (bool)ExclusiveMonitorPass(piVar9,0x10);
  if (bVar3) {
    *piVar9 = 0;
    cVar2 = ExclusiveMonitorsStatus();
  }
  if (cVar2 == '\0') goto code_r0x02054d40;
  goto code_r0x02054a0c;
code_r0x02054d40:
  DataMemoryBarrier(2,3);
code_r0x02054d48:
  *(ushort *)(param_1 + 0x162) = *param_3;
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_1 + 0x40) = 0xffffffff;
  DataMemoryBarrier(2,3);
  piVar9 = (int *)(param_1 + 0x44);
  if (*piVar9 < 0x15) {
    return 1;
  }
  do {
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar9,0x10);
    if (bVar3) {
      *piVar9 = *piVar9 + -1;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
  goto code_r0x02054e04;
code_r0x020549bc:
  cVar2 = '\x01';
  bVar3 = (bool)ExclusiveMonitorPass(piVar9,0x10);
  if (bVar3) {
    *piVar9 = 0;
    cVar2 = ExclusiveMonitorsStatus();
  }
  if (cVar2 == '\0') goto code_r0x02054d00;
  goto code_r0x020549b0;
code_r0x02054d00:
  DataMemoryBarrier(2,3);
code_r0x02054d08:
  *(ushort *)(param_1 + 0x160) = *param_3;
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_1 + 0x40) = 0xffffffff;
  DataMemoryBarrier(2,3);
  piVar9 = (int *)(param_1 + 0x44);
  if (*piVar9 < 0x15) {
    return 1;
  }
  do {
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar9,0x10);
    if (bVar3) {
      *piVar9 = *piVar9 + -1;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
  goto code_r0x02054e04;
code_r0x02054960:
  cVar2 = '\x01';
  bVar3 = (bool)ExclusiveMonitorPass(piVar9,0x10);
  if (bVar3) {
    *piVar9 = 0;
    cVar2 = ExclusiveMonitorsStatus();
  }
  if (cVar2 == '\0') goto code_r0x02054cc0;
  goto code_r0x02054954;
code_r0x02054cc0:
  DataMemoryBarrier(2,3);
code_r0x02054cc8:
  *(ushort *)(param_1 + 0x15e) = *param_3;
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_1 + 0x40) = 0xffffffff;
  DataMemoryBarrier(2,3);
  piVar9 = (int *)(param_1 + 0x44);
  if (*piVar9 < 0x15) {
    return 1;
  }
  do {
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar9,0x10);
    if (bVar3) {
      *piVar9 = *piVar9 + -1;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
  goto code_r0x02054e04;
code_r0x02054904:
  cVar2 = '\x01';
  bVar3 = (bool)ExclusiveMonitorPass(piVar9,0x10);
  if (bVar3) {
    *piVar9 = 0;
    cVar2 = ExclusiveMonitorsStatus();
  }
  if (cVar2 == '\0') goto code_r0x02054c80;
  goto code_r0x020548f8;
code_r0x02054c80:
  DataMemoryBarrier(2,3);
code_r0x02054c88:
  *(ushort *)(param_1 + 0x15c) = *param_3;
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_1 + 0x40) = 0xffffffff;
  DataMemoryBarrier(2,3);
  piVar9 = (int *)(param_1 + 0x44);
  if (*piVar9 < 0x15) {
    return 1;
  }
  do {
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar9,0x10);
    if (bVar3) {
      *piVar9 = *piVar9 + -1;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
  goto code_r0x02054e04;
code_r0x020548a8:
  cVar2 = '\x01';
  bVar3 = (bool)ExclusiveMonitorPass(piVar9,0x10);
  if (bVar3) {
    *piVar9 = 0;
    cVar2 = ExclusiveMonitorsStatus();
  }
  if (cVar2 == '\0') goto code_r0x02054c28;
  goto code_r0x0205489c;
code_r0x02054c28:
  DataMemoryBarrier(2,3);
code_r0x02054c30:
  piVar9 = (int *)(param_1 + 0x44);
  uVar7 = *param_3;
  *(ushort *)(param_1 + 0x15a) = uVar7;
  iVar4 = 0x7fff - *(short *)(param_1 + 0x16c);
  iVar8 = (int)(short)uVar7;
  if (iVar4 == (short)uVar7 || iVar4 < (short)uVar7) {
    iVar8 = iVar4;
  }
  *(short *)(param_1 + 0x16a) = (short)iVar8;
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_1 + 0x40) = 0xffffffff;
  DataMemoryBarrier(2,3);
  if (*(int *)(param_1 + 0x44) < 0x15) {
    return 1;
  }
  do {
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar9,0x10);
    if (bVar3) {
      *piVar9 = *piVar9 + -1;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
  goto code_r0x02054e04;
code_r0x0205484c:
  cVar2 = '\x01';
  bVar3 = (bool)ExclusiveMonitorPass(piVar9,0x10);
  if (bVar3) {
    *piVar9 = 0;
    cVar2 = ExclusiveMonitorsStatus();
  }
  if (cVar2 == '\0') goto code_r0x02054bd0;
  goto code_r0x02054840;
code_r0x02054bd0:
  DataMemoryBarrier(2,3);
code_r0x02054bd8:
  piVar9 = (int *)(param_1 + 0x44);
  uVar7 = *param_3;
  *(ushort *)(param_1 + 0x158) = uVar7;
  iVar4 = 0x7fff - *(short *)(param_1 + 0x16c);
  iVar8 = (int)(short)uVar7;
  if (iVar4 == (short)uVar7 || iVar4 < (short)uVar7) {
    iVar8 = iVar4;
  }
  *(short *)(param_1 + 0x168) = (short)iVar8;
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_1 + 0x40) = 0xffffffff;
  DataMemoryBarrier(2,3);
  if (*(int *)(param_1 + 0x44) < 0x15) {
    return 1;
  }
  do {
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar9,0x10);
    if (bVar3) {
      *piVar9 = *piVar9 + -1;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
  goto code_r0x02054e04;
code_r0x020547f0:
  cVar2 = '\x01';
  bVar3 = (bool)ExclusiveMonitorPass(piVar9,0x10);
  if (bVar3) {
    *piVar9 = 0;
    cVar2 = ExclusiveMonitorsStatus();
  }
  if (cVar2 == '\0') goto code_r0x02054b78;
  goto code_r0x020547e4;
code_r0x02054b78:
  DataMemoryBarrier(2,3);
code_r0x02054b80:
  piVar9 = (int *)(param_1 + 0x44);
  uVar7 = *param_3;
  *(ushort *)(param_1 + 0x156) = uVar7;
  iVar4 = 0x7fff - *(short *)(param_1 + 0x16c);
  iVar8 = (int)(short)uVar7;
  if (iVar4 == (short)uVar7 || iVar4 < (short)uVar7) {
    iVar8 = iVar4;
  }
  *(short *)(param_1 + 0x166) = (short)iVar8;
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_1 + 0x40) = 0xffffffff;
  DataMemoryBarrier(2,3);
  if (*(int *)(param_1 + 0x44) < 0x15) {
    return 1;
  }
  do {
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar9,0x10);
    if (bVar3) {
      *piVar9 = *piVar9 + -1;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
  goto code_r0x02054e04;
code_r0x02054794:
  cVar2 = '\x01';
  bVar3 = (bool)ExclusiveMonitorPass(piVar9,0x10);
  if (bVar3) {
    *piVar9 = 0;
    cVar2 = ExclusiveMonitorsStatus();
  }
  if (cVar2 == '\0') goto code_r0x02054b20;
  goto code_r0x02054788;
code_r0x02054b20:
  DataMemoryBarrier(2,3);
code_r0x02054b28:
  piVar9 = (int *)(param_1 + 0x44);
  uVar7 = *param_3;
  *(ushort *)(param_1 + 0x154) = uVar7;
  iVar4 = 0x7fff - *(short *)(param_1 + 0x16c);
  iVar8 = (int)(short)uVar7;
  if (iVar4 == (short)uVar7 || iVar4 < (short)uVar7) {
    iVar8 = iVar4;
  }
  *(short *)(param_1 + 0x164) = (short)iVar8;
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_1 + 0x40) = 0xffffffff;
  DataMemoryBarrier(2,3);
  if (*(int *)(param_1 + 0x44) < 0x15) {
    return 1;
  }
  do {
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar9,0x10);
    if (bVar3) {
      *piVar9 = *piVar9 + -1;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
code_r0x02054e04:
  uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x80);
  if ((uVar6 & 1) != 0) {
    Aska::Semaphore::Signal() const(param_1 + 0x80);
  }
  return 1;
}

// ==== Aska::Pad::InstantiateAppropriatePad()
// vaddr 0x1f5528c | ghidra 0x205528c | size 48 | symbol _ZN4Aska3Pad25InstantiateAppropriatePadEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska3Pad25InstantiateAppropriatePadEv(void)

{
  long lVar1;
  
  lVar1 = operator new(unsigned long, std::nothrow_t const&)(0x178,PTR__ZSt7nothrow_02cb9a80);
  if (lVar1 != 0) {
    Aska::PadDroid::PadDroid()(lVar1);
  }
  return lVar1;
}

// ==== Aska::Pad::InstantiateDebugPad()
// vaddr 0x1f552bc | ghidra 0x20552bc | size 8 | symbol _ZN4Aska3Pad19InstantiateDebugPadEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska3Pad19InstantiateDebugPadEv(void)

{
  return 0;
}

// ==== Aska::Pad::InstantiatePadCapture()
// vaddr 0x1f552c4 | ghidra 0x20552c4 | size 8 | symbol _ZN4Aska3Pad21InstantiatePadCaptureEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska3Pad21InstantiatePadCaptureEv(void)

{
  return 0;
}

// ==== Aska::Pad::~Pad()
// vaddr 0x1f552cc | ghidra 0x20552cc | size 4 | symbol _ZN4Aska3PadD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska3PadD0Ev(void)

{
  code *pcVar1;
  
                    /* WARNING: Does not return */
  pcVar1 = (code *)SoftwareBreakpoint(1,0x20552d0);
  (*pcVar1)();
}

// ==== Aska::Pad::GetClassID(int) const
// vaddr 0x1f552d0 | ghidra 0x20552d0 | size 72 | symbol _ZNK4Aska3Pad10GetClassIDEi | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska3Pad10GetClassIDEi(undefined8 param_1,int param_2)

{
  undefined8 uVar1;
  undefined8 uVar2;
  
  if (param_2 != 0) {
    uVar2 = 0xf000f035;
    if (param_2 != 2) {
      uVar2 = 0xf000;
    }
    uVar1 = 0xf000f035f036;
    if (param_2 != 1) {
      uVar1 = uVar2;
    }
    return uVar1;
  }
  return 0xf000f035f036f037;
}

// ==== Aska::Pad::SetTriggerThreshold(Aska::Pad::TriggerThreshold, int)
// vaddr 0x1f55318 | ghidra 0x2055318 | size 4 | symbol _ZN4Aska3Pad19SetTriggerThresholdENS0_16TriggerThresholdEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska3Pad19SetTriggerThresholdENS0_16TriggerThresholdEi(void)

{
  return;
}

// ==== Aska::Pad::GetTriggerThreshold(Aska::Pad::TriggerThreshold) const
// vaddr 0x1f5531c | ghidra 0x205531c | size 8 | symbol _ZNK4Aska3Pad19GetTriggerThresholdENS0_16TriggerThresholdE | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska3Pad19GetTriggerThresholdENS0_16TriggerThresholdE(void)

{
  return 0x7f;
}

// ==== Aska::PeripheralManager::PeripheralManager()
// vaddr 0x1f573f0 | ghidra 0x20573f0 | size 76 | symbol _ZN4Aska17PeripheralManagerC1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska17PeripheralManagerC2Ev(long *param_1)

{
  undefined *puVar1;
  
  *param_1 = (long)(PTR__ZTVN4Aska11IAnimatableE_02cc3b10 + 0x10);
  Aska::Thread::Thread()(param_1 + 1);
  puVar1 = PTR__ZTVN4Aska17PeripheralManagerE_02cc3a60;
  *(undefined2 *)(param_1 + 6) = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  param_1[1] = (long)(puVar1 + 0x60);
  *param_1 = (long)(puVar1 + 0x10);
  return;
}

// ==== Aska::PeripheralManager::~PeripheralManager()
// vaddr 0x1f5743c | ghidra 0x205743c | size 100 | symbol _ZN4Aska17PeripheralManagerD2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska17PeripheralManagerD1Ev(long *param_1)

{
  long *plVar1;
  undefined *puVar2;
  
  plVar1 = param_1 + 1;
  puVar2 = PTR__ZTVN4Aska17PeripheralManagerE_02cc3a60 + 0x10;
  param_1[1] = (long)(PTR__ZTVN4Aska17PeripheralManagerE_02cc3a60 + 0x60);
  *param_1 = (long)puVar2;
  *(undefined1 *)(param_1 + 6) = 1;
  Aska::Thread::WaitEnd()(plVar1);
  *(undefined1 *)((long)param_1 + 0x31) = 0;
  Aska::Thread::WaitEnd()(plVar1);
  Aska::TouchPanel::FinalizeGesture()();
  Aska::Thread::~Thread()(plVar1);
  (*(code *)PTR__ZN4Aska11IAnimatableD2Ev_02cb13b8)(param_1);
  return;
}

// ==== non-virtual thunk to Aska::PeripheralManager::~PeripheralManager()
// vaddr 0x1f574a0 | ghidra 0x20574a0 | size 96 | symbol _ZThn8_N4Aska17PeripheralManagerD1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZThn8_N4Aska17PeripheralManagerD1Ev(long *param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZTVN4Aska17PeripheralManagerE_02cc3a60 + 0x10;
  *param_1 = (long)(PTR__ZTVN4Aska17PeripheralManagerE_02cc3a60 + 0x60);
  param_1[-1] = (long)puVar1;
  *(undefined1 *)(param_1 + 5) = 1;
  Aska::Thread::WaitEnd()();
  *(undefined1 *)((long)param_1 + 0x29) = 0;
  Aska::Thread::WaitEnd()(param_1);
  Aska::TouchPanel::FinalizeGesture()();
  Aska::Thread::~Thread()(param_1);
  (*(code *)PTR__ZN4Aska11IAnimatableD2Ev_02cb13b8)(param_1 + -1);
  return;
}

// ==== Aska::PeripheralManager::~PeripheralManager()
// vaddr 0x1f57500 | ghidra 0x2057500 | size 108 | symbol _ZN4Aska17PeripheralManagerD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska17PeripheralManagerD0Ev(long *param_1)

{
  long *plVar1;
  undefined *puVar2;
  
  plVar1 = param_1 + 1;
  puVar2 = PTR__ZTVN4Aska17PeripheralManagerE_02cc3a60 + 0x10;
  param_1[1] = (long)(PTR__ZTVN4Aska17PeripheralManagerE_02cc3a60 + 0x60);
  *param_1 = (long)puVar2;
  *(undefined1 *)(param_1 + 6) = 1;
  Aska::Thread::WaitEnd()(plVar1);
  *(undefined1 *)((long)param_1 + 0x31) = 0;
  Aska::Thread::WaitEnd()(plVar1);
  Aska::TouchPanel::FinalizeGesture()();
  Aska::Thread::~Thread()(plVar1);
  Aska::IAnimatable::~IAnimatable()(param_1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== non-virtual thunk to Aska::PeripheralManager::~PeripheralManager()
// vaddr 0x1f5756c | ghidra 0x205756c | size 104 | symbol _ZThn8_N4Aska17PeripheralManagerD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZThn8_N4Aska17PeripheralManagerD0Ev(long *param_1)

{
  undefined *puVar1;
  long *plVar2;
  
  puVar1 = PTR__ZTVN4Aska17PeripheralManagerE_02cc3a60 + 0x10;
  plVar2 = param_1 + -1;
  *param_1 = (long)(PTR__ZTVN4Aska17PeripheralManagerE_02cc3a60 + 0x60);
  *plVar2 = (long)puVar1;
  *(undefined1 *)(param_1 + 5) = 1;
  Aska::Thread::WaitEnd()();
  *(undefined1 *)((long)param_1 + 0x29) = 0;
  Aska::Thread::WaitEnd()(param_1);
  Aska::TouchPanel::FinalizeGesture()();
  Aska::Thread::~Thread()(param_1);
  Aska::IAnimatable::~IAnimatable()(plVar2);
  (*(code *)PTR__ZdlPv_02ca4758)(plVar2);
  return;
}

// ==== Aska::PeripheralManager::ResetAllPeripheral()
// vaddr 0x1f575d4 | ghidra 0x20575d4 | size 60 | symbol _ZN4Aska17PeripheralManager18ResetAllPeripheralEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska17PeripheralManager18ResetAllPeripheralEv(long param_1)

{
  if (*(long **)(param_1 + 0x20) != (long *)0x0) {
    (**(code **)(**(long **)(param_1 + 0x20) + 0x50))();
  }
  if (*(long **)(param_1 + 0x28) != (long *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x02057604. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(**(long **)(param_1 + 0x28) + 0x50))();
    return;
  }
  return;
}

// ==== Aska::PeripheralManager::Handler()
// vaddr 0x1f57610 | ghidra 0x2057610 | size 88 | symbol _ZN4Aska17PeripheralManager7HandlerEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska17PeripheralManager7HandlerEv(long param_1)

{
  char cVar1;
  
  cVar1 = *(char *)(param_1 + 0x30);
  while (cVar1 == '\0') {
    if (*(long **)(param_1 + 0x20) != (long *)0x0) {
      (**(code **)(**(long **)(param_1 + 0x20) + 0x48))();
    }
    if (*(long **)(param_1 + 0x28) != (long *)0x0) {
      (**(code **)(**(long **)(param_1 + 0x28) + 0x48))();
    }
    Aska::Thread::Sleep(unsigned int)(8);
    cVar1 = *(char *)(param_1 + 0x30);
  }
  return;
}

// ==== non-virtual thunk to Aska::PeripheralManager::Handler()
// vaddr 0x1f57668 | ghidra 0x2057668 | size 88 | symbol _ZThn8_N4Aska17PeripheralManager7HandlerEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZThn8_N4Aska17PeripheralManager7HandlerEv(long param_1)

{
  char cVar1;
  
  cVar1 = *(char *)(param_1 + 0x28);
  while (cVar1 == '\0') {
    if (*(long **)(param_1 + 0x18) != (long *)0x0) {
      (**(code **)(**(long **)(param_1 + 0x18) + 0x48))();
    }
    if (*(long **)(param_1 + 0x20) != (long *)0x0) {
      (**(code **)(**(long **)(param_1 + 0x20) + 0x48))();
    }
    Aska::Thread::Sleep(unsigned int)(8);
    cVar1 = *(char *)(param_1 + 0x28);
  }
  return;
}

// ==== Aska::PeripheralManager::Get(unsigned long, void*) const
// vaddr 0x1f576c0 | ghidra 0x20576c0 | size 8 | symbol _ZNK4Aska17PeripheralManager3GetEmPv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska17PeripheralManager3GetEmPv(void)

{
  return 0;
}

// ==== Aska::PeripheralManager::Set(unsigned long, void const*)
// vaddr 0x1f576c8 | ghidra 0x20576c8 | size 8 | symbol _ZN4Aska17PeripheralManager3SetEmPKv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska17PeripheralManager3SetEmPKv(void)

{
  return 0;
}


// FAILED to create function at 02baf218 Aska::TouchPanel::vtable
// FAILED to create function at 02baf290 Aska::TouchPanel::typeinfo
// FAILED to create function at 02bb0248 Aska::BasePeripheral::vtable
// FAILED to create function at 02bb02c0 Aska::BasePeripheral::typeinfo
// FAILED to create function at 02bb0740 Aska::Keyboard::vtable
// FAILED to create function at 02bb07c0 Aska::Keyboard::typeinfo
// FAILED to create function at 02bb1fd8 Aska::Mouse::vtable
// FAILED to create function at 02bb2060 Aska::Mouse::typeinfo
// FAILED to create function at 02bb27d8 Aska::Pad::vtable
// FAILED to create function at 02bb28a0 Aska::Pad::typeinfo
// FAILED to create function at 02bb2a18 Aska::PeripheralManager::vtable
// FAILED to create function at 02bb2a90 Aska::PeripheralManager::typeinfo
// FAILED to create function at 02d00a60 Aska::TouchPanel::m_criGlobal
// FAILED to create function at 02d00af0 Aska::TouchPanel::m_queueSystemTouchData
// FAILED to create function at 02dcbf10 Aska::Keyboard::Static::pKeyboard
// FAILED to create function at 02dcc6b0 Aska::Mouse::StaticPrivate::pMouse
