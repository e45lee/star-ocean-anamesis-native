// port/decomp/audio/sound_manager.c: Ghidra decompiles for the audio subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-08 13:04 UTC: tools/decomp.sh '--into' 'audio/sound_manager' 'Aska::Sound[A-Za-z0-9]*::' 'Aska::SEControlObject::' 'Aska::Sequencer2::'

// ==== Aska::Sequencer2::Sequencer2()
// vaddr 0x1f6a53c | ghidra 0x206a53c | size 124 | symbol _ZN4Aska10Sequencer2C2Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska10Sequencer2C1Ev(long *param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  undefined *puVar3;
  
  puVar3 = PTR__ZTVN4Aska5TListINS_16AudioMessageNoteEEE_02cbc6f0;
  puVar2 = PTR__ZTVN4Aska10Sequencer2E_02cbad30;
  param_1[4] = (long)(param_1 + 3);
  param_1[5] = (long)(param_1 + 3);
  puVar1 = PTR__ZTVN4Aska16AudioMessageNoteE_02cc20c8 + 0x10;
  param_1[6] = 0;
  *(undefined4 *)(param_1 + 0xb) = 0;
  *param_1 = (long)(puVar2 + 0x10);
  param_1[1] = 0;
  param_1[3] = (long)puVar1;
  param_1[2] = (long)(puVar3 + 0x10);
  Aska::FastCriticalSection::FastCriticalSection()(param_1 + 0xc);
  puVar1 = PTR__ZTVN4Aska10Sequencer217WaitingNoteNotifyE_02cba7c8;
  param_1[0x1e] = 0x4185555600000000;
  param_1[0x1f] = (long)(puVar1 + 0x10);
  param_1[0x20] = 0;
  *(undefined1 *)(param_1 + 0x21) = 0;
  return;
}

// ==== Aska::Sequencer2::~Sequencer2()
// vaddr 0x1f6a5b8 | ghidra 0x206a5b8 | size 40 | symbol _ZN4Aska10Sequencer2D2Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska10Sequencer2D1Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska10Sequencer2E_02cbad30 + 0x10);
  Aska::Sequencer2::DeleteAllMessageNote()();
  (*(code *)PTR__ZN4Aska19FastCriticalSectionD2Ev_02ca21e0)(param_1 + 0xc);
  return;
}

// ==== Aska::Sequencer2::DeleteAllMessageNote()
// vaddr 0x1f6a5e0 | ghidra 0x206a5e0 | size 428 | symbol _ZN4Aska10Sequencer220DeleteAllMessageNoteEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska10Sequencer220DeleteAllMessageNoteEv(long param_1)

{
  int *piVar1;
  char cVar2;
  bool bVar3;
  long lVar4;
  undefined *puVar5;
  ulong uVar6;
  int iVar7;
  int *piVar8;
  long lVar9;
  long lVar10;
  
  piVar8 = (int *)(param_1 + 0x98);
  iVar7 = 0;
code_r0x0206a5f8:
  do {
    if (*piVar8 != -1) {
      ClearExclusiveLocal();
      bVar3 = iVar7 < 0x1ff;
      iVar7 = iVar7 + 1;
      if (bVar3) goto code_r0x0206a5f8;
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
        if (*piVar8 != -1) {
          ClearExclusiveLocal();
          do {
            uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0xd8);
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
            while (*piVar8 == -1) {
              cVar2 = '\x01';
              bVar3 = (bool)ExclusiveMonitorPass(piVar8,0x10);
              if (bVar3) {
                *piVar8 = 0;
                cVar2 = ExclusiveMonitorsStatus();
              }
              if (cVar2 == '\0') goto code_r0x0206a6b0;
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
code_r0x0206a6b0:
      do {
        cVar2 = '\x01';
        bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
        if (bVar3) {
          *piVar1 = *piVar1 + -1;
          cVar2 = ExclusiveMonitorsStatus();
        }
      } while (cVar2 != '\0');
code_r0x0206a6c0:
      puVar5 = PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50;
      DataMemoryBarrier(2,3);
      lVar4 = *(long *)(param_1 + 0x28);
      while (param_1 + 0x18 != lVar4) {
        lVar10 = *(long *)(lVar4 + 0x10);
        if (lVar4 != 0) {
          lVar9 = *(long *)(lVar4 + 8);
          if (lVar9 != 0) {
            *(long *)(lVar9 + 0x10) = lVar10;
          }
          if (lVar10 != 0) {
            *(long *)(lVar10 + 8) = lVar9;
          }
          if (0 < *(int *)(param_1 + 0x58)) {
            *(int *)(param_1 + 0x58) = *(int *)(param_1 + 0x58) + -1;
          }
          *(long *)(lVar4 + 8) = 0;
          *(undefined8 *)(lVar4 + 0x10) = 0;
        }
        Aska::SoundServer::ReleaseMessageNote(Aska::AudioMessageNote*)(*(undefined8 *)(*(long *)puVar5 + 0xe8));
        lVar4 = lVar10;
      }
      DataMemoryBarrier(2,3);
      *(undefined4 *)(param_1 + 0x98) = 0xffffffff;
      DataMemoryBarrier(2,3);
      piVar8 = (int *)(param_1 + 0x9c);
      if (0x14 < *piVar8) {
        do {
          cVar2 = '\x01';
          bVar3 = (bool)ExclusiveMonitorPass(piVar8,0x10);
          if (bVar3) {
            *piVar8 = *piVar8 + -1;
            cVar2 = ExclusiveMonitorsStatus();
          }
        } while (cVar2 != '\0');
        uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0xd8);
        if ((uVar6 & 1) != 0) {
          (*(code *)PTR__ZNK4Aska9Semaphore6SignalEv_02c96cd0)(param_1 + 0xd8);
          return;
        }
      }
      return;
    }
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar8,0x10);
    if (bVar3) {
      *piVar8 = 0;
      cVar2 = ExclusiveMonitorsStatus();
    }
    if (cVar2 == '\0') goto code_r0x0206a6c0;
  } while( true );
}

// ==== Aska::Sequencer2::~Sequencer2()
// vaddr 0x1f6a790 | ghidra 0x206a790 | size 60 | symbol _ZN4Aska10Sequencer2D0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska10Sequencer2D0Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska10Sequencer2E_02cbad30 + 0x10);
  Aska::Sequencer2::DeleteAllMessageNote()();
  Aska::FastCriticalSection::~FastCriticalSection()(param_1 + 0xc);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::Sequencer2::AudioRun()
// vaddr 0x1f6a7cc | ghidra 0x206a7cc | size 80 | symbol _ZN4Aska10Sequencer28AudioRunEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska10Sequencer28AudioRunEv(long param_1)

{
  long lVar1;
  
  lVar1 = *(long *)(param_1 + 8);
  if (lVar1 != 0) {
    if ((*(int *)(lVar1 + 0x18) == 2) || (*(int *)(lVar1 + 0x18) == 4)) {
      *(float *)(param_1 + 0xf0) = *(float *)(param_1 + 0xf4) + *(float *)(param_1 + 0xf0);
    }
    Aska::Sequencer2::ArrangeMessageNote()(param_1);
    (*(code *)PTR__ZN4Aska10Sequencer218ProcessMessageNoteEv_02ca0d60)(param_1);
    return;
  }
  return;
}

// ==== Aska::Sequencer2::ArrangeMessageNote()
// vaddr 0x1f6a81c | ghidra 0x206a81c | size 1024 | symbol _ZN4Aska10Sequencer218ArrangeMessageNoteEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska10Sequencer218ArrangeMessageNoteEv(long param_1)

{
  int *piVar1;
  long lVar2;
  char cVar3;
  long *plVar4;
  undefined *puVar5;
  bool bVar6;
  ulong uVar7;
  int iVar8;
  uint uVar9;
  int *piVar10;
  long lVar11;
  long lVar12;
  long lVar13;
  uint uVar14;
  
  piVar10 = (int *)(param_1 + 0x98);
  iVar8 = 0;
code_r0x0206a838:
  do {
    if (*piVar10 != -1) {
      ClearExclusiveLocal();
      bVar6 = iVar8 < 0x1ff;
      iVar8 = iVar8 + 1;
      if (bVar6) goto code_r0x0206a838;
      piVar1 = (int *)(param_1 + 0x9c);
      do {
        cVar3 = '\x01';
        bVar6 = (bool)ExclusiveMonitorPass(piVar1,0x10);
        if (bVar6) {
          *piVar1 = *piVar1 + 1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      do {
        if (*piVar10 != -1) {
          ClearExclusiveLocal();
          do {
            uVar7 = Aska::Semaphore::IsReady() const(param_1 + 0xd8);
            if ((uVar7 & 1) == 0) {
              do {
                cVar3 = '\x01';
                bVar6 = (bool)ExclusiveMonitorPass(piVar1,0x10);
                if (bVar6) {
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
              bVar6 = (bool)ExclusiveMonitorPass(piVar1,0x10);
              if (bVar6) {
                *piVar1 = *piVar1 + 1;
                cVar3 = ExclusiveMonitorsStatus();
              }
            } while (cVar3 != '\0');
            while (*piVar10 == -1) {
              cVar3 = '\x01';
              bVar6 = (bool)ExclusiveMonitorPass(piVar10,0x10);
              if (bVar6) {
                *piVar10 = 0;
                cVar3 = ExclusiveMonitorsStatus();
              }
              if (cVar3 == '\0') goto code_r0x0206a8f0;
            }
            ClearExclusiveLocal();
          } while( true );
        }
        cVar3 = '\x01';
        bVar6 = (bool)ExclusiveMonitorPass(piVar10,0x10);
        if (bVar6) {
          *piVar10 = 0;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
code_r0x0206a8f0:
      do {
        cVar3 = '\x01';
        bVar6 = (bool)ExclusiveMonitorPass(piVar1,0x10);
        if (bVar6) {
          *piVar1 = *piVar1 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
code_r0x0206a900:
      puVar5 = PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50;
      DataMemoryBarrier(2,3);
      lVar12 = *(long *)(param_1 + 0x28);
      lVar2 = param_1 + 0x18;
      if (lVar2 != lVar12) {
        do {
          iVar8 = *(int *)(lVar12 + 0x20);
          lVar13 = *(long *)(lVar12 + 0x10);
          if ((iVar8 == 4) || (iVar8 == 1)) {
            for (lVar11 = *(long *)(param_1 + 0x28); lVar2 != lVar11;
                lVar11 = *(long *)(lVar11 + 0x10)) {
              if ((iVar8 == *(int *)(lVar11 + 0x20)) &&
                 (*(float *)(lVar11 + 0x38) < *(float *)(lVar12 + 0x38))) {
                lVar11 = *(long *)(lVar12 + 8);
                if (lVar11 != 0) {
                  *(long *)(lVar11 + 0x10) = lVar13;
                }
                if (lVar13 != 0) {
                  *(long *)(lVar13 + 8) = lVar11;
                }
                if (0 < *(int *)(param_1 + 0x58)) {
                  *(int *)(param_1 + 0x58) = *(int *)(param_1 + 0x58) + -1;
                }
                *(long *)(lVar12 + 8) = 0;
                *(undefined8 *)(lVar12 + 0x10) = 0;
                Aska::SoundServer::ReleaseMessageNote(Aska::AudioMessageNote*)(*(undefined8 *)(*(long *)puVar5 + 0xe8));
                break;
              }
            }
          }
          lVar12 = lVar13;
        } while (lVar2 != lVar13);
        lVar12 = *(long *)(param_1 + 0x28);
      }
      puVar5 = PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50;
      if (lVar2 == lVar12) goto code_r0x0206abb0;
      do {
        lVar13 = *(long *)(lVar12 + 0x10);
        plVar4 = (long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50;
        if (*(float *)(lVar12 + 0x38) <= *(float *)(param_1 + 0xf0)) {
          for (lVar11 = *(long *)(param_1 + 0x28); lVar2 != lVar11;
              lVar11 = *(long *)(lVar11 + 0x10)) {
            if ((((lVar12 != lVar11) && (*(float *)(lVar11 + 0x38) <= *(float *)(param_1 + 0xf0)))
                && (*(int *)(lVar11 + 0x20) == *(int *)(lVar12 + 0x20))) &&
               (*(float *)(lVar12 + 0x38) <= *(float *)(lVar11 + 0x38))) {
              lVar11 = *(long *)(lVar12 + 8);
              if (lVar11 != 0) {
                *(long *)(lVar11 + 0x10) = lVar13;
              }
              if (lVar13 != 0) {
                *(long *)(lVar13 + 8) = lVar11;
              }
              if (0 < *(int *)(param_1 + 0x58)) {
                *(int *)(param_1 + 0x58) = *(int *)(param_1 + 0x58) + -1;
              }
              *(long *)(lVar12 + 8) = 0;
              *(undefined8 *)(lVar12 + 0x10) = 0;
              Aska::SoundServer::ReleaseMessageNote(Aska::AudioMessageNote*)(*(undefined8 *)(*(long *)puVar5 + 0xe8));
              plVar4 = (long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50;
              break;
            }
          }
        }
        lVar12 = lVar13;
        PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50 = (undefined *)plVar4;
      } while (lVar2 != lVar13);
      if (lVar2 == *(long *)(param_1 + 0x28)) goto code_r0x0206abb0;
      lVar12 = *(long *)(param_1 + 0x28);
      uVar14 = *(uint *)(*(long *)(param_1 + 8) + 0x18);
      do {
        lVar13 = *(long *)(lVar12 + 0x10);
        lVar11 = *(long *)(lVar12 + 0x18);
        uVar9 = uVar14;
        if ((((lVar11 == 0) || (*(long *)(lVar11 + 8) == lVar12)) ||
            (*(char *)(lVar11 + 0x10) == '\0')) &&
           (*(float *)(lVar12 + 0x38) <= *(float *)(param_1 + 0xf0))) {
          switch(*(undefined4 *)(lVar12 + 0x20)) {
          case 0:
            if (uVar14 == 1) {
              uVar9 = 2;
            }
            else {
code_r0x0206ab68:
              lVar11 = *(long *)(lVar12 + 8);
              if (lVar11 != 0) {
                *(long *)(lVar11 + 0x10) = lVar13;
              }
              if (lVar13 != 0) {
                *(long *)(lVar13 + 8) = lVar11;
              }
              if (0 < *(int *)(param_1 + 0x58)) {
                *(int *)(param_1 + 0x58) = *(int *)(param_1 + 0x58) + -1;
              }
              *(long *)(lVar12 + 8) = 0;
              *(undefined8 *)(lVar12 + 0x10) = 0;
              Aska::SoundServer::ReleaseMessageNote(Aska::AudioMessageNote*)(*(undefined8 *)(*plVar4 + 0xe8));
              uVar9 = uVar14;
            }
            break;
          case 1:
            if (2 < uVar14 - 2) goto code_r0x0206ab68;
            uVar9 = 5;
            break;
          case 2:
            uVar9 = 3;
            if ((uVar14 != 2) && (uVar14 != 4)) goto code_r0x0206ab68;
            break;
          case 3:
            bVar6 = uVar14 != 3;
            uVar14 = 2;
            uVar9 = 2;
            if (bVar6) goto code_r0x0206ab68;
            break;
          case 4:
            if ((uVar14 & 0xfffffffe) != 2) goto code_r0x0206ab68;
            uVar9 = 4;
            break;
          case 5:
          case 6:
          case 7:
          case 8:
          case 9:
            if ((uVar14 & 0xfffffffe) != 2) goto code_r0x0206ab68;
          }
        }
        lVar12 = lVar13;
        uVar14 = uVar9;
        if (lVar2 == lVar13) {
code_r0x0206abb0:
          DataMemoryBarrier(2,3);
          *(undefined4 *)(param_1 + 0x98) = 0xffffffff;
          DataMemoryBarrier(2,3);
          piVar10 = (int *)(param_1 + 0x9c);
          if (0x14 < *piVar10) {
            do {
              cVar3 = '\x01';
              bVar6 = (bool)ExclusiveMonitorPass(piVar10,0x10);
              if (bVar6) {
                *piVar10 = *piVar10 + -1;
                cVar3 = ExclusiveMonitorsStatus();
              }
            } while (cVar3 != '\0');
            uVar7 = Aska::Semaphore::IsReady() const(param_1 + 0xd8);
            if ((uVar7 & 1) != 0) {
              (*(code *)PTR__ZNK4Aska9Semaphore6SignalEv_02c96cd0)(param_1 + 0xd8);
              return;
            }
          }
          return;
        }
      } while( true );
    }
    cVar3 = '\x01';
    bVar6 = (bool)ExclusiveMonitorPass(piVar10,0x10);
    if (bVar6) {
      *piVar10 = 0;
      cVar3 = ExclusiveMonitorsStatus();
    }
    if (cVar3 == '\0') goto code_r0x0206a900;
  } while( true );
}

// ==== Aska::Sequencer2::ProcessMessageNote()
// vaddr 0x1f6ac1c | ghidra 0x206ac1c | size 728 | symbol _ZN4Aska10Sequencer218ProcessMessageNoteEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska10Sequencer218ProcessMessageNoteEv(long param_1)

{
  int *piVar1;
  int *piVar2;
  long lVar3;
  char cVar4;
  bool bVar5;
  ulong uVar6;
  undefined8 *puVar7;
  int iVar8;
  long lVar9;
  long lVar10;
  long lVar11;
  
  piVar2 = (int *)(param_1 + 0x98);
  iVar8 = 0;
  do {
    while (*piVar2 != -1) {
      ClearExclusiveLocal();
      bVar5 = 0x1fe < iVar8;
      iVar8 = iVar8 + 1;
      if (bVar5) {
        piVar1 = (int *)(param_1 + 0x9c);
        do {
          cVar4 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar5) {
            *piVar1 = *piVar1 + 1;
            cVar4 = ExclusiveMonitorsStatus();
          }
        } while (cVar4 != '\0');
        do {
          if (*piVar2 != -1) {
            ClearExclusiveLocal();
            do {
              uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0xd8);
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
                Aska::Semaphore::Wait() const(param_1 + 0xd8);
              }
              do {
                cVar4 = '\x01';
                bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
                if (bVar5) {
                  *piVar1 = *piVar1 + 1;
                  cVar4 = ExclusiveMonitorsStatus();
                }
              } while (cVar4 != '\0');
              while (*piVar2 == -1) {
                cVar4 = '\x01';
                bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
                if (bVar5) {
                  *piVar2 = 0;
                  cVar4 = ExclusiveMonitorsStatus();
                }
                if (cVar4 == '\0') goto code_r0x0206aedc;
              }
              ClearExclusiveLocal();
            } while( true );
          }
          cVar4 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
          if (bVar5) {
            *piVar2 = 0;
            cVar4 = ExclusiveMonitorsStatus();
          }
        } while (cVar4 != '\0');
code_r0x0206aedc:
        do {
          cVar4 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar5) {
            *piVar1 = *piVar1 + -1;
            cVar4 = ExclusiveMonitorsStatus();
          }
        } while (cVar4 != '\0');
        DataMemoryBarrier(2,3);
        goto code_r0x0206ac98;
      }
    }
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar5) {
      *piVar2 = 0;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
  DataMemoryBarrier(2,3);
code_r0x0206ac98:
  lVar10 = *(long *)(param_1 + 0x28);
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_1 + 0x98) = 0xffffffff;
  DataMemoryBarrier(2,3);
  piVar1 = (int *)(param_1 + 0x9c);
  if (0x14 < *piVar1) {
    do {
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar5) {
        *piVar1 = *piVar1 + -1;
        cVar4 = ExclusiveMonitorsStatus();
      }
    } while (cVar4 != '\0');
    uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0xd8);
    if ((uVar6 & 1) != 0) {
      Aska::Semaphore::Signal() const(param_1 + 0xd8);
    }
  }
  if (param_1 + 0x18 != lVar10) {
    lVar3 = param_1 + 0xd8;
    do {
      iVar8 = 0;
      do {
        while (*piVar2 == -1) {
          cVar4 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
          if (bVar5) {
            *piVar2 = 0;
            cVar4 = ExclusiveMonitorsStatus();
          }
          if (cVar4 == '\0') goto code_r0x0206adb0;
        }
        ClearExclusiveLocal();
        bVar5 = iVar8 < 0x1ff;
        iVar8 = iVar8 + 1;
      } while (bVar5);
      do {
        cVar4 = '\x01';
        bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
        if (bVar5) {
          *piVar1 = *piVar1 + 1;
          cVar4 = ExclusiveMonitorsStatus();
        }
      } while (cVar4 != '\0');
      do {
        if (*piVar2 != -1) {
          do {
            ClearExclusiveLocal();
            uVar6 = Aska::Semaphore::IsReady() const(lVar3);
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
              Aska::Semaphore::Wait() const(lVar3);
            }
            do {
              cVar4 = '\x01';
              bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
              if (bVar5) {
                *piVar1 = *piVar1 + 1;
                cVar4 = ExclusiveMonitorsStatus();
              }
            } while (cVar4 != '\0');
            while (*piVar2 == -1) {
              cVar4 = '\x01';
              bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
              if (bVar5) {
                *piVar2 = 0;
                cVar4 = ExclusiveMonitorsStatus();
              }
              if (cVar4 == '\0') goto code_r0x0206ada0;
            }
          } while( true );
        }
        cVar4 = '\x01';
        bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
        if (bVar5) {
          *piVar2 = 0;
          cVar4 = ExclusiveMonitorsStatus();
        }
      } while (cVar4 != '\0');
code_r0x0206ada0:
      do {
        cVar4 = '\x01';
        bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
        if (bVar5) {
          *piVar1 = *piVar1 + -1;
          cVar4 = ExclusiveMonitorsStatus();
        }
      } while (cVar4 != '\0');
code_r0x0206adb0:
      DataMemoryBarrier(2,3);
      lVar11 = *(long *)(lVar10 + 0x10);
      DataMemoryBarrier(2,3);
      *piVar2 = -1;
      DataMemoryBarrier(2,3);
      if (0x14 < *piVar1) {
        do {
          cVar4 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar5) {
            *piVar1 = *piVar1 + -1;
            cVar4 = ExclusiveMonitorsStatus();
          }
        } while (cVar4 != '\0');
        uVar6 = Aska::Semaphore::IsReady() const(lVar3);
        if ((uVar6 & 1) != 0) {
          Aska::Semaphore::Signal() const(lVar3);
        }
      }
      lVar9 = *(long *)(lVar10 + 0x18);
      if ((((lVar9 == 0) || (*(long *)(lVar9 + 8) == lVar10)) || (*(char *)(lVar9 + 0x10) == '\0'))
         && (*(float *)(lVar10 + 0x38) <= *(float *)(param_1 + 0xf0))) {
        Aska::AudioPlayer::SendMessage(unsigned int, void*, void*)(*(undefined8 *)(param_1 + 8),*(undefined4 *)(lVar10 + 0x20),
                        *(undefined8 *)(lVar10 + 0x28),*(undefined8 *)(lVar10 + 0x30));
        puVar7 = *(undefined8 **)(lVar10 + 0x18);
        if (puVar7 != (undefined8 *)0x0) {
          (**(code **)*puVar7)(puVar7,0);
        }
        Aska::Sequencer2::DeleteMessageNote(Aska::AudioMessageNote*)(param_1,lVar10);
      }
      lVar10 = lVar11;
    } while (param_1 + 0x18 != lVar11);
  }
  return;
}

// ==== Aska::Sequencer2::IsWaitingNote(Aska::AudioMessageNote*) const
// vaddr 0x1f6af34 | ghidra 0x206af34 | size 44 | symbol _ZNK4Aska10Sequencer213IsWaitingNoteEPNS_16AudioMessageNoteE | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZNK4Aska10Sequencer213IsWaitingNoteEPNS_16AudioMessageNoteE(undefined8 param_1,long param_2)

{
  long lVar1;
  
  lVar1 = *(long *)(param_2 + 0x18);
  if (((lVar1 != 0) && (*(long *)(lVar1 + 8) != param_2)) && (*(char *)(lVar1 + 0x10) != '\0')) {
    return 1;
  }
  return 0;
}

// ==== Aska::Sequencer2::DeleteMessageNote(Aska::AudioMessageNote*)
// vaddr 0x1f6af60 | ghidra 0x206af60 | size 420 | symbol _ZN4Aska10Sequencer217DeleteMessageNoteEPNS_16AudioMessageNoteE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska10Sequencer217DeleteMessageNoteEPNS_16AudioMessageNoteE(long param_1,long param_2)

{
  int *piVar1;
  char cVar2;
  bool bVar3;
  ulong uVar4;
  int iVar5;
  int *piVar6;
  long lVar7;
  long lVar8;
  
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
      if (cVar2 == '\0') goto code_r0x0206b044;
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
          if (cVar2 == '\0') goto code_r0x0206b034;
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
code_r0x0206b034:
  do {
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar3) {
      *piVar1 = *piVar1 + -1;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
code_r0x0206b044:
  DataMemoryBarrier(2,3);
  if ((param_1 + 0x18 != param_2) && (param_2 != 0)) {
    lVar7 = *(long *)(param_2 + 8);
    lVar8 = *(long *)(param_2 + 0x10);
    if (lVar7 != 0) {
      *(long *)(lVar7 + 0x10) = lVar8;
    }
    if (lVar8 != 0) {
      *(long *)(lVar8 + 8) = lVar7;
    }
    if (0 < *(int *)(param_1 + 0x58)) {
      *(int *)(param_1 + 0x58) = *(int *)(param_1 + 0x58) + -1;
    }
    *(long *)(param_2 + 8) = 0;
    *(undefined8 *)(param_2 + 0x10) = 0;
  }
  Aska::SoundServer::ReleaseMessageNote(Aska::AudioMessageNote*)(*(undefined8 *)(*(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50 + 0xe8),
                  param_2);
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
      (*(code *)PTR__ZNK4Aska9Semaphore6SignalEv_02c96cd0)(param_1 + 0xd8);
      return;
    }
  }
  return;
}

// ==== Aska::Sequencer2::AddMessageNote(unsigned int, float, void const*, void const*)
// vaddr 0x1f6b104 | ghidra 0x206b104 | size 496 | symbol _ZN4Aska10Sequencer214AddMessageNoteEjfPKvS2_ | lib libSOA-3.7.0.so | 2026-10-08
undefined4
_ZN4Aska10Sequencer214AddMessageNoteEjfPKvS2_
          (undefined4 param_1,long param_2,int param_3,undefined8 param_4,undefined8 param_5)

{
  int *piVar1;
  char cVar2;
  bool bVar3;
  long lVar4;
  ulong uVar5;
  int iVar6;
  long lVar7;
  int *piVar8;
  undefined4 uVar9;
  
  piVar8 = (int *)(param_2 + 0x98);
  iVar6 = 0;
  do {
    while (*piVar8 == -1) {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar8,0x10);
      if (bVar3) {
        *piVar8 = 0;
        cVar2 = ExclusiveMonitorsStatus();
      }
      if (cVar2 == '\0') goto code_r0x0206b1fc;
    }
    ClearExclusiveLocal();
    bVar3 = iVar6 < 0x1ff;
    iVar6 = iVar6 + 1;
  } while (bVar3);
  piVar1 = (int *)(param_2 + 0x9c);
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
        uVar5 = Aska::Semaphore::IsReady() const(param_2 + 0xd8);
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
          Aska::Semaphore::Wait() const(param_2 + 0xd8);
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
          if (cVar2 == '\0') goto code_r0x0206b1ec;
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
code_r0x0206b1ec:
  do {
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar3) {
      *piVar1 = *piVar1 + -1;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
code_r0x0206b1fc:
  DataMemoryBarrier(2,3);
  lVar4 = Aska::SoundServer::AcquireMessageNote()(*(undefined8 *)
                           (*(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50 + 0xe8));
  if (lVar4 == 0) {
    uVar9 = 0;
  }
  else {
    if (param_3 - 1U < 9) {
      lVar7 = 0;
      if (*(char *)(param_2 + 0x108) != '\0') {
        lVar7 = param_2 + 0xf8;
      }
    }
    else if (param_3 == 0) {
      *(undefined1 *)(param_2 + 0x108) = 1;
      *(long *)(param_2 + 0x100) = lVar4;
      lVar7 = param_2 + 0xf8;
    }
    else {
      lVar7 = 0;
    }
    *(long *)(lVar4 + 0x18) = lVar7;
    *(undefined4 *)(lVar4 + 0x38) = param_1;
    *(int *)(lVar4 + 0x20) = param_3;
    *(undefined8 *)(lVar4 + 0x28) = param_4;
    *(undefined8 *)(lVar4 + 0x30) = param_5;
    lVar7 = *(long *)(param_2 + 0x20);
    uVar9 = 1;
    *(long *)(lVar4 + 8) = lVar7;
    *(long *)(lVar4 + 0x10) = param_2 + 0x18;
    *(long *)(param_2 + 0x20) = lVar4;
    *(long *)(lVar7 + 0x10) = lVar4;
    *(int *)(param_2 + 0x58) = *(int *)(param_2 + 0x58) + 1;
  }
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_2 + 0x98) = 0xffffffff;
  DataMemoryBarrier(2,3);
  piVar8 = (int *)(param_2 + 0x9c);
  if (0x14 < *piVar8) {
    do {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar8,0x10);
      if (bVar3) {
        *piVar8 = *piVar8 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    uVar5 = Aska::Semaphore::IsReady() const(param_2 + 0xd8);
    if ((uVar5 & 1) != 0) {
      Aska::Semaphore::Signal() const(param_2 + 0xd8);
    }
  }
  return uVar9;
}

// ==== Aska::Sequencer2::WaitingNoteNotify::Handler(unsigned long)
// vaddr 0x1f6b318 | ghidra 0x206b318 | size 8 | symbol _ZN4Aska10Sequencer217WaitingNoteNotify7HandlerEm | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska10Sequencer217WaitingNoteNotify7HandlerEm(long param_1)

{
  *(undefined1 *)(param_1 + 0x10) = 0;
  return;
}

// ==== Aska::Sequencer2::WaitingNoteNotify::~WaitingNoteNotify()
// vaddr 0x1f6b320 | ghidra 0x206b320 | size 4 | symbol _ZN4Aska10Sequencer217WaitingNoteNotifyD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska10Sequencer217WaitingNoteNotifyD0Ev(void)

{
  (*(code *)PTR__ZdlPv_02ca4758)();
  return;
}

// ==== Aska::SoundManager::Instantiate()
// vaddr 0x1f6b410 | ghidra 0x206b410 | size 104 | symbol _ZN4Aska12SoundManager11InstantiateEv | lib libSOA-3.7.0.so | 2026-10-08
long _ZN4Aska12SoundManager11InstantiateEv(void)

{
  undefined *puVar1;
  undefined *puVar2;
  long lVar3;
  
  puVar2 = PTR__ZN4Aska12SoundManager11m_pInstanceE_02cc2868;
  lVar3 = *(long *)PTR__ZN4Aska12SoundManager11m_pInstanceE_02cc2868;
  if (lVar3 == 0) {
    lVar3 = operator new(unsigned long, std::nothrow_t const&)(0x1240,PTR__ZSt7nothrow_02cb9a80);
    if (lVar3 == 0) {
      *(undefined8 *)puVar2 = 0;
      lVar3 = 0;
    }
    else {
      Aska::SoundManager::SoundManager()(lVar3);
      puVar1 = PTR__ZN4Aska6Global20m_pSystemTaskManagerE_02cbf620;
      *(long *)puVar2 = lVar3;
      Aska::TaskManager::Add(Aska::Task*)(*(undefined8 *)puVar1,lVar3);
      lVar3 = *(long *)puVar2;
    }
  }
  return lVar3;
}

// ==== Aska::SoundManager::Initialize()
// vaddr 0x1f6b478 | ghidra 0x206b478 | size 1172 | symbol _ZN4Aska12SoundManager10InitializeEv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska12SoundManager10InitializeEv(long param_1)

{
  undefined *puVar1;
  byte *pbVar2;
  ulong uVar3;
  char cVar4;
  ulong uVar5;
  int iVar6;
  undefined4 uVar7;
  undefined8 *puVar8;
  long lVar9;
  long lVar10;
  ulong uVar11;
  long *plVar12;
  byte bVar13;
  uint uVar14;
  ulong uVar15;
  code *pcVar16;
  ulong uVar17;
  ulong uVar18;
  char *pcVar19;
  long *plVar20;
  undefined *puStack_48;
  undefined8 uStack_40;
  long lStack_38;
  undefined4 auStack_28 [2];
  
  pbVar2 = (byte *)(param_1 + 0x1234);
  if ((*pbVar2 >> 2 & 1) != 0) {
    return 1;
  }
  iVar6 = slCreateEngine((undefined8 *)(param_1 + 0x28),0,0,0,0,0);
  if ((iVar6 == 0) &&
     (puVar8 = *(undefined8 **)(param_1 + 0x28), iVar6 = (**(code **)*puVar8)(puVar8,0), iVar6 == 0)
     ) {
    iVar6 = (**(code **)(**(long **)(param_1 + 0x28) + 0x18))
                      (*(long **)(param_1 + 0x28),*(undefined8 *)PTR_SL_IID_ENGINE_02cb9428,
                       param_1 + 0x30);
    bVar13 = *pbVar2;
    if (iVar6 != 0) goto code_r0x0206b4dc;
    *pbVar2 = bVar13 | 2;
    puVar1 = PTR__ZN4Aska6Global13m_pAndroidAppE_02cc2688;
    plVar20 = *(long **)(*(long *)(*(long *)PTR__ZN4Aska6Global13m_pAndroidAppE_02cc2688 + 0x18) + 8
                        );
    puStack_48 = (undefined *)0x0;
    Aska::AndroidUtil::AttachCurrentThread(_JavaVM*, _JNIEnv**, void*)(plVar20,&puStack_48,0);
    *(undefined4 *)(param_1 + 0x38) = 0x42c80000;
    *(undefined4 *)(param_1 + 0x3c) = 0;
    Aska::AndroidUtil::CallMethod(_JNIEnv*, jvalue*, _jobject*, char const*, char const*, ...)(&lStack_38,puStack_48,auStack_28,
                    *(undefined8 *)(*(long *)(*(long *)puVar1 + 0x18) + 0x18),&UNK_02971aaa/*"GetAudioLatency"*/,
                    &UNK_0295bd4f/*"()F"*/);
    if (-1 < lStack_38) {
      *(undefined4 *)(param_1 + 0x38) = auStack_28[0];
    }
    lVar10 = *(long *)PTR__ZN4Aska11AndroidUtil19m_pAttachThreadListE_02cbb5c8;
    if (lVar10 != 0) {
      uVar11 = Aska::Thread::GetCurrentID()();
      uVar15 = *(ulong *)(lVar10 + 0x28);
      if (uVar15 != 0) {
        uVar17 = ~uVar11 + uVar11 * 0x200000;
        uVar17 = (uVar17 ^ uVar17 >> 0x18) * 0x109;
        uVar18 = (uVar17 ^ uVar17 >> 0xe) * 0x15;
        uVar17 = 0;
        do {
          uVar3 = (uVar18 ^ uVar18 >> 0x1c) * 0x80000001 + uVar17;
          uVar5 = 0;
          if (uVar15 != 0) {
            uVar5 = uVar3 / uVar15;
          }
          lVar9 = uVar3 - uVar5 * uVar15;
          pcVar19 = (char *)(*(long *)(lVar10 + 0x20) + lVar9 * 0x18);
          cVar4 = *pcVar19;
          if (cVar4 == '\x01') {
            if (*(ulong *)(*(long *)(lVar10 + 0x20) + lVar9 * 0x18 + 8) == uVar11) {
              *(int *)(lVar10 + 0x10) = *(int *)(lVar10 + 0x10) + -1;
              *(int *)(lVar10 + 0x14) = *(int *)(lVar10 + 0x14) + 1;
              *pcVar19 = '\x02';
              break;
            }
          }
          else if (cVar4 == '\0') break;
          uVar17 = uVar17 + 1;
        } while (uVar17 < uVar15);
      }
    }
    (**(code **)(*plVar20 + 0x28))(plVar20);
    uVar14 = (uint)*pbVar2;
    if ((*pbVar2 >> 1 & 1) != 0) {
      lVar9 = Aska::SoundMemory::Malloc(unsigned long)(0x610);
      *(long *)(param_1 + 0xe8) = lVar9;
      lVar10 = 0;
      if (lVar9 != 0) {
        Aska::SoundServer::SoundServer()();
        lVar10 = *(long *)(param_1 + 0xe8);
      }
      if (lVar10 == 0) {
        return 0;
      }
      uVar11 = Aska::SoundServer::Initialize()();
      if ((uVar11 & 1) == 0) {
        return 0;
      }
      uVar14 = (uint)*pbVar2;
    }
  }
  else {
    bVar13 = *pbVar2;
code_r0x0206b4dc:
    uVar14 = bVar13 & 0xfd;
    *pbVar2 = (byte)uVar14;
  }
  if ((uVar14 >> 1 & 1) != 0) {
    plVar12 = (long *)Aska::SoundMemory::Malloc(unsigned long)(0x1020);
    *(long **)(param_1 + 0x6c8) = plVar12;
    plVar20 = (long *)0x0;
    if (plVar12 != (long *)0x0) {
      Aska::AudioMixer::AudioMixer()(plVar12);
      *plVar12 = (long)(PTR__ZTVN4Aska7MixerSLE_02cc0838 + 0x10);
      plVar20 = *(long **)(param_1 + 0x6c8);
    }
    if (plVar20 == (long *)0x0) {
      return 0;
    }
    uVar11 = (**(code **)(*plVar20 + 0x58))(plVar20);
    if ((uVar11 & 1) == 0) {
      if (*(long **)(param_1 + 0x6c8) != (long *)0x0) {
        (**(code **)(**(long **)(param_1 + 0x6c8) + 8))();
        *(undefined8 *)(param_1 + 0x6c8) = 0;
      }
      bVar13 = *pbVar2 & 0xfd;
      *pbVar2 = bVar13;
      goto code_r0x0206b568;
    }
    uVar14 = (uint)*pbVar2;
  }
  bVar13 = (byte)uVar14;
  if ((uVar14 >> 1 & 1) != 0) {
    *(undefined8 *)(param_1 + 0x6c0) = 0;
    plVar20 = (long *)Aska::SoundMemory::Malloc(unsigned long)(0x28);
    *(long **)(param_1 + 0xe0) = plVar20;
    lVar10 = 0;
    if (plVar20 != (long *)0x0) {
      Aska::Thread::Thread()(plVar20);
      *plVar20 = (long)(PTR__ZTVN4Aska18SoundManagerThreadE_02cbc8d0 + 0x10);
      *(byte *)(plVar20 + 4) = *(byte *)(plVar20 + 4) & 0xfe;
      *(byte *)(plVar20 + 4) = *(byte *)(plVar20 + 4) & 0xfd;
      plVar20[3] = param_1;
      lVar10 = *(long *)(param_1 + 0xe0);
    }
    if ((lVar10 == 0) || (uVar11 = Aska::Thread::Create(bool, int, int, bool)(lVar10,1,0x7f,0x8000,1), (uVar11 & 1) == 0)) {
      return 0;
    }
    *(byte *)(lVar10 + 0x20) = *(byte *)(lVar10 + 0x20) | 1;
    plVar20 = (long *)Aska::SoundMemory::Malloc(unsigned long)(0x2a0);
    *(long **)(param_1 + 0x40) = plVar20;
    lVar10 = 0;
    if (plVar20 != (long *)0x0) {
      pcVar16 = *(code **)(PTR__ZTVN4Aska4TaskE_02cbe020 + 0x68);
      *plVar20 = (long)(PTR__ZTVN4Aska4TaskE_02cbe020 + 0x10);
      plVar20[1] = 0;
      plVar20[2] = 0;
      plVar20[3] = 0;
      *(undefined2 *)((long)plVar20 + 0x24) = 0;
      *(undefined1 *)((long)plVar20 + 0x26) = 0;
      uVar7 = (*pcVar16)(plVar20);
      *(undefined4 *)(plVar20 + 4) = uVar7;
      puVar1 = PTR__ZTVN4Aska17AudioSignalNotifyE_02cb9718 + 0x10;
      *plVar20 = (long)(PTR__ZTVN4Aska11AudioSignalE_02cb93d0 + 0x10);
      plVar20[5] = (long)puVar1;
      Aska::FastCriticalSection::FastCriticalSection()(plVar20 + 0x1a);
      memset(plVar20 + 6,0,0xa0);
      plVar20[0x2c] = (long)puVar1;
      Aska::FastCriticalSection::FastCriticalSection()(plVar20 + 0x41);
      memset(plVar20 + 0x2d,0,0xa0);
      *(undefined4 *)(plVar20 + 0x53) = 0;
      lVar10 = *(long *)(param_1 + 0x40);
    }
    if (lVar10 == 0) {
      return 0;
    }
    Aska::TaskManager::Add(Aska::Task*)(*(undefined8 *)PTR__ZN4Aska6Global20m_pSystemTaskManagerE_02cbf620,lVar10);
    uVar11 = Aska::AudioSafetySignalThread::Initialize()(param_1 + 0x58);
    if ((uVar11 & 1) == 0) {
      return 0;
    }
    uVar11 = Aska::AudioSafetySignalNotify::Initialize(Aska::Event*)(param_1 + 0x48,param_1 + 0x70);
    if ((uVar11 & 1) == 0) {
      return 0;
    }
    *(undefined8 *)(param_1 + 0x10e0) = 0;
    *(undefined8 *)(param_1 + 0x1148) = 0;
    *(undefined2 *)(param_1 + 0x1158) = 0;
    *(undefined8 *)(param_1 + 0x1150) = 0xffffffffffffffff;
    *(undefined1 *)(param_1 + 0x115a) = 0;
    *(undefined4 *)(param_1 + 0x1230) = 0x4000;
    lVar10 = Aska::SoundMemory::ResourceAlloc(unsigned long, unsigned long)(0x4000,0x80);
    *(long *)(param_1 + 0x1228) = lVar10;
    if (lVar10 == 0) {
      return 0;
    }
    memset(lVar10,0,*(undefined4 *)(param_1 + 0x1230));
    puStack_48 = &UNK_02971ac0;
    uStack_40 = 5;
    uVar11 = Aska::AudioSmallHeap::Initialize(Aska::AudioSmallHeap::InitParam const&)(param_1 + 0x1168,&puStack_48);
    if ((uVar11 & 1) == 0) {
      return 0;
    }
    Aska::AskaOGG::InitializeMemory()();
    uVar11 = Aska::Audio3DEngine::Initialize()(param_1 + 0x390);
    if ((uVar11 & 1) == 0) {
      return 0;
    }
    bVar13 = *pbVar2 & 0xfe;
    *pbVar2 = bVar13;
    *(undefined4 *)(param_1 + 0x10d8) = 0;
    *(undefined4 *)(param_1 + 0x115c) = 1;
    *(undefined1 *)(param_1 + 0x1160) = 0;
  }
code_r0x0206b568:
  *pbVar2 = bVar13 | 4;
  return 1;
}

// ==== Aska::SoundManager::GetInstance()
// vaddr 0x1f6b944 | ghidra 0x206b944 | size 16 | symbol _ZN4Aska12SoundManager11GetInstanceEv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska12SoundManager11GetInstanceEv(void)

{
  return *(undefined8 *)PTR__ZN4Aska12SoundManager11m_pInstanceE_02cc2868;
}

// ==== Aska::SoundManager::DeleteThis(Aska::DeleteManager*)
// vaddr 0x1f6b954 | ghidra 0x206b954 | size 40 | symbol _ZN4Aska12SoundManager10DeleteThisEPNS_13DeleteManagerE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12SoundManager10DeleteThisEPNS_13DeleteManagerE(undefined8 param_1,undefined8 param_2)

{
  Aska::SoundManager::Deinitialize()();
  (*(code *)PTR__ZN4Aska4Task10DeleteThisEPNS_13DeleteManagerE_02cac0f0)(param_1,param_2);
  return;
}

// ==== Aska::SoundManager::Deinitialize()
// vaddr 0x1f6b97c | ghidra 0x206b97c | size 424 | symbol _ZN4Aska12SoundManager12DeinitializeEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12SoundManager12DeinitializeEv(long param_1)

{
  byte *pbVar1;
  byte bVar2;
  long lVar3;
  long lVar4;
  
  pbVar1 = (byte *)(param_1 + 0x1234);
  if ((*pbVar1 >> 2 & 1) != 0) {
    if ((~*pbVar1 & 6) == 0) {
      lVar3 = *(long *)(param_1 + 0x108);
      while (param_1 + 0xf8 != lVar3) {
        lVar4 = *(long *)(lVar3 + 0x10);
        Aska::SoundManager::DeleteSoundObject(Aska::SoundObject*, bool)(param_1,lVar3,1);
        lVar3 = lVar4;
      }
      lVar3 = *(long *)(param_1 + 0x130);
      while (param_1 + 0x120 != lVar3) {
        lVar4 = *(long *)(lVar3 + 0x10);
        Aska::SoundManager::DeleteSoundObject(Aska::SoundObject*, bool)(param_1,lVar3,1);
        lVar3 = lVar4;
      }
    }
    Aska::SoundManager::FlushDeletingSoundObject()(param_1);
    Aska::Audio3DEngine::Finalize()(param_1 + 0x390);
    lVar3 = *(long *)(param_1 + 0xe0);
    if (lVar3 != 0) {
      *(byte *)(lVar3 + 0x20) = *(byte *)(lVar3 + 0x20) | 2;
      Aska::Thread::WaitEnd()(*(undefined8 *)(param_1 + 0xe0));
      if (*(long **)(param_1 + 0xe0) != (long *)0x0) {
        (**(code **)(**(long **)(param_1 + 0xe0) + 8))();
        *(undefined8 *)(param_1 + 0xe0) = 0;
      }
      *(undefined1 *)(param_1 + 0xd8) = 1;
      Aska::Event::Set() const(param_1 + 0x70);
      Aska::Thread::WaitEnd()(param_1 + 0x58);
      Aska::AudioSafetySignalNotify::Finalize()(param_1 + 0x48);
      if (*(long *)(param_1 + 0x40) != 0) {
        Aska::Task::Remove()();
        (**(code **)(**(long **)(param_1 + 0x40) + 0x38))(*(long **)(param_1 + 0x40),0);
        *(undefined8 *)(param_1 + 0x40) = 0;
      }
    }
    *(byte *)(param_1 + 0xdfa) = *(byte *)(param_1 + 0xdfa) | 1;
    Aska::PushPopBGMList::Clear()(param_1 + 0x140);
    if (*(long **)(param_1 + 0x6c8) != (long *)0x0) {
      (**(code **)(**(long **)(param_1 + 0x6c8) + 8))();
      *(undefined8 *)(param_1 + 0x6c8) = 0;
    }
    if (*(long **)(param_1 + 0xe8) != (long *)0x0) {
      (**(code **)(**(long **)(param_1 + 0xe8) + 8))();
      *(undefined8 *)(param_1 + 0xe8) = 0;
    }
    Aska::AudioSmallHeap::Finalize()(param_1 + 0x1168);
    bVar2 = *pbVar1;
    if ((bVar2 >> 1 & 1) != 0) {
      if (*(long *)(param_1 + 0x1228) != 0) {
        Aska::SoundMemory::ResourceFree(void*)();
        *(undefined8 *)(param_1 + 0x1228) = 0;
        bVar2 = *pbVar1;
      }
      bVar2 = bVar2 & 0xfd;
      *(undefined4 *)(param_1 + 0x1230) = 0;
      *pbVar1 = bVar2;
    }
    *pbVar1 = bVar2 & 0xfb;
  }
  return;
}

// ==== Aska::SoundManager::ProcessSoundObject()
// vaddr 0x1f6bb24 | ghidra 0x206bb24 | size 112 | symbol _ZN4Aska12SoundManager18ProcessSoundObjectEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12SoundManager18ProcessSoundObjectEv(long param_1)

{
  long *plVar1;
  
  for (plVar1 = *(long **)(param_1 + 0x108); (long *)(param_1 + 0xf8) != plVar1;
      plVar1 = (long *)plVar1[2]) {
    (**(code **)(*plVar1 + 0x40))(plVar1);
  }
  for (plVar1 = *(long **)(param_1 + 0x130); (long *)(param_1 + 0x120) != plVar1;
      plVar1 = (long *)plVar1[2]) {
    (**(code **)(*plVar1 + 0x40))(plVar1);
  }
  return;
}

// ==== Aska::SoundManager::Process3DEngine()
// vaddr 0x1f6bb94 | ghidra 0x206bb94 | size 92 | symbol _ZN4Aska12SoundManager15Process3DEngineEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12SoundManager15Process3DEngineEv(long param_1)

{
  long lVar1;
  
  if (*(long *)(param_1 + 0x3b8) != 0) {
    Aska::AudioListener::Compute()(param_1 + 0x3a0);
    for (lVar1 = *(long *)(param_1 + 0x108); param_1 + 0xf8 != lVar1;
        lVar1 = *(long *)(lVar1 + 0x10)) {
      if (*(long *)(lVar1 + 0x218) != 0) {
        Aska::AudioEmitter::Compute()(lVar1 + 0x200);
      }
    }
  }
  return;
}

// ==== Aska::SoundManager::CheckDeleteSoundObject()
// vaddr 0x1f6bbf0 | ghidra 0x206bbf0 | size 152 | symbol _ZN4Aska12SoundManager22CheckDeleteSoundObjectEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12SoundManager22CheckDeleteSoundObjectEv(long param_1)

{
  long lVar1;
  long lVar2;
  
  lVar2 = *(long *)(param_1 + 0x108);
  while (lVar1 = lVar2, param_1 + 0xf8 != lVar1) {
    lVar2 = *(long *)(lVar1 + 0x10);
    if ((*(long *)(lVar1 + 0x128) != 0) && (*(int *)(*(long *)(lVar1 + 0x128) + 0x18) == 5)) {
      Aska::SoundManager::DeleteSoundObject(Aska::SoundObject*, bool)(param_1,lVar1,0);
    }
  }
  lVar2 = *(long *)(param_1 + 0x130);
  while (lVar1 = lVar2, param_1 + 0x120 != lVar1) {
    lVar2 = *(long *)(lVar1 + 0x10);
    if ((*(long *)(lVar1 + 0x128) != 0) && (*(int *)(*(long *)(lVar1 + 0x128) + 0x18) == 5)) {
      Aska::SoundManager::DeleteSoundObject(Aska::SoundObject*, bool)(param_1,lVar1,0);
    }
  }
  return;
}

// ==== Aska::SoundManager::DeleteSoundObject(Aska::SoundObject*, bool)
// vaddr 0x1f6bc88 | ghidra 0x206bc88 | size 264 | symbol _ZN4Aska12SoundManager17DeleteSoundObjectEPNS_11SoundObjectEb | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12SoundManager17DeleteSoundObjectEPNS_11SoundObjectEb
               (long param_1,long *param_2,ulong param_3)

{
  long lVar1;
  long *plVar2;
  long lVar3;
  
  for (plVar2 = *(long **)(param_1 + 0x108); (long *)(param_1 + 0xf8) != plVar2;
      plVar2 = (long *)plVar2[2]) {
    if (plVar2 == param_2) goto code_r0x0206bce0;
  }
  for (plVar2 = *(long **)(param_1 + 0x130); (long *)(param_1 + 0x120) != plVar2;
      plVar2 = (long *)plVar2[2]) {
    if (plVar2 == param_2) goto code_r0x0206bce0;
  }
code_r0x0206bd64:
  *(byte *)((long)param_2 + 0x1f2) = *(byte *)((long)param_2 + 0x1f2) | 1;
  if (((param_3 & 1) == 0) && ((*(byte *)((long)param_2 + 0x1ec) & 1) == 0)) {
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x0206bd8c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*param_2 + 0x38))(param_2);
  return;
code_r0x0206bce0:
  if ((*(uint *)(param_2 + 0x3d) & 1) == 0) {
    if ((((*(uint *)(param_2 + 0x3d) >> 1 & 1) == 0) || (param_2 == (long *)0x0)) ||
       ((long *)(param_1 + 0x120) == param_2)) goto code_r0x0206bd64;
    lVar1 = param_2[1];
    lVar3 = param_2[2];
    if (lVar1 != 0) {
      *(long *)(lVar1 + 0x10) = lVar3;
    }
    if (lVar3 != 0) {
      *(long *)(lVar3 + 8) = lVar1;
    }
    if (0 < *(int *)(param_1 + 0x138)) {
      *(int *)(param_1 + 0x138) = *(int *)(param_1 + 0x138) + -1;
    }
  }
  else {
    if ((param_2 == (long *)0x0) || ((long *)(param_1 + 0xf8) == param_2)) goto code_r0x0206bd64;
    lVar1 = param_2[1];
    lVar3 = param_2[2];
    if (lVar1 != 0) {
      *(long *)(lVar1 + 0x10) = lVar3;
    }
    if (lVar3 != 0) {
      *(long *)(lVar3 + 8) = lVar1;
    }
    if (0 < *(int *)(param_1 + 0x110)) {
      *(int *)(param_1 + 0x110) = *(int *)(param_1 + 0x110) + -1;
    }
  }
  param_2[1] = 0;
  param_2[2] = 0;
  goto code_r0x0206bd64;
}

// ==== Aska::SoundManager::IsAvailable(Aska::SoundObject*) const
// vaddr 0x1f6bd90 | ghidra 0x206bd90 | size 36 | symbol _ZNK4Aska12SoundManager11IsAvailableEPNS_11SoundObjectE | lib libSOA-3.7.0.so | 2026-10-08
bool _ZNK4Aska12SoundManager11IsAvailableEPNS_11SoundObjectE(undefined8 param_1,long param_2)

{
  long lVar1;
  
  if (param_2 != 0) {
    lVar1 = Aska::SoundManager::QuerySoundHandle(Aska::SoundObject*) const();
    return lVar1 != 0;
  }
  return false;
}

// ==== Aska::SoundManager::QuerySoundHandle(Aska::SoundObject*) const
// vaddr 0x1f6bdb4 | ghidra 0x206bdb4 | size 376 | symbol _ZNK4Aska12SoundManager16QuerySoundHandleEPNS_11SoundObjectE | lib libSOA-3.7.0.so | 2026-10-08
long _ZNK4Aska12SoundManager16QuerySoundHandleEPNS_11SoundObjectE(long param_1,long param_2)

{
  int *piVar1;
  int *piVar2;
  char cVar3;
  bool bVar4;
  ulong uVar5;
  int iVar6;
  long lVar7;
  
  piVar1 = (int *)(param_1 + 0x330);
  iVar6 = 0;
  do {
    while (*piVar1 == -1) {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = 0;
        cVar3 = ExclusiveMonitorsStatus();
      }
      if (cVar3 == '\0') goto code_r0x0206be98;
    }
    ClearExclusiveLocal();
    bVar4 = iVar6 < 0x1ff;
    iVar6 = iVar6 + 1;
  } while (bVar4);
  piVar2 = (int *)(param_1 + 0x334);
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
        uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0x370);
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
          Aska::Semaphore::Wait() const(param_1 + 0x370);
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
          if (cVar3 == '\0') goto code_r0x0206be88;
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
code_r0x0206be88:
  do {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar4) {
      *piVar2 = *piVar2 + -1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
code_r0x0206be98:
  DataMemoryBarrier(2,3);
  for (lVar7 = *(long *)(param_1 + 0x2e0); param_1 + 0x2d0 != lVar7; lVar7 = *(long *)(lVar7 + 0x10)
      ) {
    if (*(long *)(lVar7 + 0x18) == param_2) goto code_r0x0206bed0;
  }
  lVar7 = 0;
code_r0x0206bed0:
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_1 + 0x330) = 0xffffffff;
  DataMemoryBarrier(2,3);
  if (0x14 < *(int *)(param_1 + 0x334)) {
    piVar1 = (int *)(param_1 + 0x334);
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
    uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0x370);
    if ((uVar5 & 1) != 0) {
      Aska::Semaphore::Signal() const(param_1 + 0x370);
    }
  }
  return lVar7;
}

// ==== Aska::SoundManager::AcquireSoundObject(unsigned int)
// vaddr 0x1f6bf2c | ghidra 0x206bf2c | size 96 | symbol _ZN4Aska12SoundManager18AcquireSoundObjectEj | lib libSOA-3.7.0.so | 2026-10-08
long _ZN4Aska12SoundManager18AcquireSoundObjectEj(long param_1)

{
  long lVar1;
  long lVar2;
  
  lVar1 = Aska::SoundServer::AcquireSoundObject(unsigned int)(*(undefined8 *)(param_1 + 0xe8));
  if (lVar1 != 0) {
    lVar2 = Aska::SoundServer::AcquireSoundHandle()(*(undefined8 *)(param_1 + 0xe8));
    if (lVar2 == 0) {
      Aska::SoundServer::ReleaseSoundObject(Aska::SoundObject*)(*(undefined8 *)(param_1 + 0xe8),lVar1);
      lVar1 = 0;
    }
    else {
      *(long *)(lVar2 + 0x18) = lVar1;
      Aska::SoundManager::AddSoundHandle(Aska::SoundHandle*)(param_1,lVar2);
    }
  }
  return lVar1;
}

// ==== Aska::SoundManager::AddSoundHandle(Aska::SoundHandle*)
// vaddr 0x1f6bf8c | ghidra 0x206bf8c | size 372 | symbol _ZN4Aska12SoundManager14AddSoundHandleEPNS_11SoundHandleE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12SoundManager14AddSoundHandleEPNS_11SoundHandleE(long param_1,long param_2)

{
  int *piVar1;
  int *piVar2;
  char cVar3;
  bool bVar4;
  ulong uVar5;
  int iVar6;
  long lVar7;
  
  piVar1 = (int *)(param_1 + 0x330);
  iVar6 = 0;
  do {
    while (*piVar1 != -1) {
      ClearExclusiveLocal();
      bVar4 = 0x1fe < iVar6;
      iVar6 = iVar6 + 1;
      if (bVar4) {
        piVar2 = (int *)(param_1 + 0x334);
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
              uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0x370);
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
                Aska::Semaphore::Wait() const(param_1 + 0x370);
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
                if (cVar3 == '\0') goto code_r0x0206c0e8;
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
code_r0x0206c0e8:
        do {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
          if (bVar4) {
            *piVar2 = *piVar2 + -1;
            cVar3 = ExclusiveMonitorsStatus();
          }
        } while (cVar3 != '\0');
        DataMemoryBarrier(2,3);
code_r0x0206c004:
        lVar7 = *(long *)(param_1 + 0x2d8);
        *(long *)(param_2 + 8) = lVar7;
        *(long *)(param_2 + 0x10) = param_1 + 0x2d0;
        *(long *)(param_1 + 0x2d8) = param_2;
        *(long *)(lVar7 + 0x10) = param_2;
        *(int *)(param_1 + 0x2f0) = *(int *)(param_1 + 0x2f0) + 1;
        DataMemoryBarrier(2,3);
        *(undefined4 *)(param_1 + 0x330) = 0xffffffff;
        DataMemoryBarrier(2,3);
        piVar1 = (int *)(param_1 + 0x334);
        if (0x14 < *piVar1) {
          do {
            cVar3 = '\x01';
            bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
            if (bVar4) {
              *piVar1 = *piVar1 + -1;
              cVar3 = ExclusiveMonitorsStatus();
            }
          } while (cVar3 != '\0');
          uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0x370);
          if ((uVar5 & 1) != 0) {
            (*(code *)PTR__ZNK4Aska9Semaphore6SignalEv_02c96cd0)(param_1 + 0x370);
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
  goto code_r0x0206c004;
}

// ==== Aska::SoundManager::ReleaseSoundObject(Aska::SoundObject*)
// vaddr 0x1f6c100 | ghidra 0x206c100 | size 96 | symbol _ZN4Aska12SoundManager18ReleaseSoundObjectEPNS_11SoundObjectE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12SoundManager18ReleaseSoundObjectEPNS_11SoundObjectE(long param_1,long param_2)

{
  long lVar1;
  
  if ((param_2 != 0) && (lVar1 = Aska::SoundManager::QuerySoundHandle(Aska::SoundObject*) const(param_1,param_2), lVar1 != 0)) {
    Aska::SoundManager::RemoveSoundHandle(Aska::SoundHandle*)(param_1,lVar1);
    Aska::SoundServer::ReleaseSoundHandle(Aska::SoundHandle*)(*(undefined8 *)(param_1 + 0xe8),lVar1);
    (*(code *)PTR__ZN4Aska11SoundServer18ReleaseSoundObjectEPNS_11SoundObjectE_02ca4168)
              (*(undefined8 *)(param_1 + 0xe8),param_2);
    return;
  }
  return;
}

// ==== Aska::SoundManager::RemoveSoundHandle(Aska::SoundHandle*)
// vaddr 0x1f6c160 | ghidra 0x206c160 | size 392 | symbol _ZN4Aska12SoundManager17RemoveSoundHandleEPNS_11SoundHandleE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12SoundManager17RemoveSoundHandleEPNS_11SoundHandleE(long param_1,long param_2)

{
  int *piVar1;
  int *piVar2;
  char cVar3;
  bool bVar4;
  ulong uVar5;
  int iVar6;
  long lVar7;
  long lVar8;
  
  piVar1 = (int *)(param_1 + 0x330);
  iVar6 = 0;
  do {
    while (*piVar1 == -1) {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = 0;
        cVar3 = ExclusiveMonitorsStatus();
      }
      if (cVar3 == '\0') goto code_r0x0206c244;
    }
    ClearExclusiveLocal();
    bVar4 = iVar6 < 0x1ff;
    iVar6 = iVar6 + 1;
  } while (bVar4);
  piVar2 = (int *)(param_1 + 0x334);
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
        uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0x370);
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
          Aska::Semaphore::Wait() const(param_1 + 0x370);
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
          if (cVar3 == '\0') goto code_r0x0206c234;
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
code_r0x0206c234:
  do {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar4) {
      *piVar2 = *piVar2 + -1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
code_r0x0206c244:
  DataMemoryBarrier(2,3);
  if ((param_1 + 0x2d0 != param_2) && (param_2 != 0)) {
    lVar7 = *(long *)(param_2 + 8);
    lVar8 = *(long *)(param_2 + 0x10);
    if (lVar7 != 0) {
      *(long *)(lVar7 + 0x10) = lVar8;
    }
    if (lVar8 != 0) {
      *(long *)(lVar8 + 8) = lVar7;
    }
    if (0 < *(int *)(param_1 + 0x2f0)) {
      *(int *)(param_1 + 0x2f0) = *(int *)(param_1 + 0x2f0) + -1;
    }
    *(long *)(param_2 + 8) = 0;
    *(undefined8 *)(param_2 + 0x10) = 0;
  }
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_1 + 0x330) = 0xffffffff;
  DataMemoryBarrier(2,3);
  if (0x14 < *(int *)(param_1 + 0x334)) {
    piVar1 = (int *)(param_1 + 0x334);
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
    uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0x370);
    if ((uVar5 & 1) != 0) {
      (*(code *)PTR__ZNK4Aska9Semaphore6SignalEv_02c96cd0)(param_1 + 0x370);
      return;
    }
  }
  return;
}

// ==== Aska::SoundManager::QuerySoundObject(Aska::SoundObject*) const
// vaddr 0x1f6c2e8 | ghidra 0x206c2e8 | size 104 | symbol _ZNK4Aska12SoundManager16QuerySoundObjectEPNS_11SoundObjectE | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK4Aska12SoundManager16QuerySoundObjectEPNS_11SoundObjectE(long param_1,long param_2)

{
  long lVar1;
  
  for (lVar1 = *(long *)(param_1 + 0x108); param_1 + 0xf8 != lVar1; lVar1 = *(long *)(lVar1 + 0x10))
  {
    if (lVar1 == param_2) {
      return 1;
    }
  }
  lVar1 = *(long *)(param_1 + 0x130);
  if (param_1 + 0x120 != lVar1) {
    do {
      if (lVar1 == param_2) {
        return 1;
      }
      lVar1 = *(long *)(lVar1 + 0x10);
    } while (param_1 + 0x120 != lVar1);
    return 0;
  }
  return 0;
}

// ==== Aska::SoundManager::AddSoundObject(Aska::SoundObject*)
// vaddr 0x1f6c350 | ghidra 0x206c350 | size 80 | symbol _ZN4Aska12SoundManager14AddSoundObjectEPNS_11SoundObjectE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12SoundManager14AddSoundObjectEPNS_11SoundObjectE(long param_1,long param_2)

{
  long lVar1;
  int *piVar2;
  
  if ((*(uint *)(param_2 + 0x1e8) & 1) == 0) {
    if ((*(uint *)(param_2 + 0x1e8) >> 1 & 1) == 0) {
      return;
    }
    lVar1 = *(long *)(param_1 + 0x128);
    *(long *)(param_2 + 8) = lVar1;
    *(long *)(param_2 + 0x10) = param_1 + 0x120;
    *(long *)(param_1 + 0x128) = param_2;
    *(long *)(lVar1 + 0x10) = param_2;
    piVar2 = (int *)(param_1 + 0x138);
  }
  else {
    lVar1 = *(long *)(param_1 + 0x100);
    *(long *)(param_2 + 8) = lVar1;
    *(long *)(param_2 + 0x10) = param_1 + 0xf8;
    *(long *)(param_1 + 0x100) = param_2;
    *(long *)(lVar1 + 0x10) = param_2;
    piVar2 = (int *)(param_1 + 0x110);
  }
  *piVar2 = *piVar2 + 1;
  return;
}

// ==== Aska::SoundManager::SetDefaultDirectPlaybackSettingsBase(Aska::DirectPlaybackSettingsBase*)
// vaddr 0x1f6c3a0 | ghidra 0x206c3a0 | size 24 | symbol _ZN4Aska12SoundManager36SetDefaultDirectPlaybackSettingsBaseEPNS_26DirectPlaybackSettingsBaseE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12SoundManager36SetDefaultDirectPlaybackSettingsBaseEPNS_26DirectPlaybackSettingsBaseE
               (undefined8 *param_1)

{
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0x3f800000;
  param_1[3] = 0x100ffff00000000;
  return;
}

// ==== Aska::SoundManager::PauseInterrupt()
// vaddr 0x1f6c3b8 | ghidra 0x206c3b8 | size 72 | symbol _ZN4Aska12SoundManager14PauseInterruptEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12SoundManager14PauseInterruptEv(long param_1)

{
  ulong uVar1;
  
  if ((*(char *)(param_1 + 0x1158) == '\0') && (uVar1 = Aska::SoundManager::IncrementPauseAll()(param_1), (uVar1 & 1) != 0))
  {
    *(undefined8 *)(param_1 + 0x1148) = 0;
    *(undefined4 *)(param_1 + 0x1150) = 500;
    *(char *)(param_1 + 0x1158) = '\x01';
  }
  return;
}

// ==== Aska::SoundManager::RequestPauseInterrupt(unsigned int)
// vaddr 0x1f6c400 | ghidra 0x206c400 | size 72 | symbol _ZN4Aska12SoundManager21RequestPauseInterruptEj | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12SoundManager21RequestPauseInterruptEj(long param_1,undefined4 param_2)

{
  ulong uVar1;
  
  if ((*(char *)(param_1 + 0x1158) == '\0') && (uVar1 = Aska::SoundManager::IncrementPauseAll()(param_1), (uVar1 & 1) != 0))
  {
    *(undefined8 *)(param_1 + 0x1148) = 0;
    *(undefined4 *)(param_1 + 0x1150) = param_2;
    *(char *)(param_1 + 0x1158) = '\x01';
  }
  return;
}

// ==== Aska::SoundManager::ResumeInterrupt()
// vaddr 0x1f6c448 | ghidra 0x206c448 | size 72 | symbol _ZN4Aska12SoundManager15ResumeInterruptEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12SoundManager15ResumeInterruptEv(long param_1)

{
  ulong uVar1;
  
  if ((*(char *)(param_1 + 0x1159) == '\0') &&
     (uVar1 = Aska::SoundManager::DecrementPauseAll(bool)(param_1,0), (uVar1 & 1) != 0)) {
    *(undefined4 *)(param_1 + 0x1154) = 1000;
    *(char *)(param_1 + 0x1159) = '\x01';
  }
  return;
}

// ==== Aska::SoundManager::RequestResumeInterrupt(unsigned int)
// vaddr 0x1f6c490 | ghidra 0x206c490 | size 72 | symbol _ZN4Aska12SoundManager22RequestResumeInterruptEj | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12SoundManager22RequestResumeInterruptEj(long param_1,undefined4 param_2)

{
  ulong uVar1;
  
  if ((*(char *)(param_1 + 0x1159) == '\0') &&
     (uVar1 = Aska::SoundManager::DecrementPauseAll(bool)(param_1,0), (uVar1 & 1) != 0)) {
    *(undefined4 *)(param_1 + 0x1154) = param_2;
    *(char *)(param_1 + 0x1159) = '\x01';
  }
  return;
}

// ==== Aska::SoundManager::InitCaptureFrameBuffer()
// vaddr 0x1f6c4d8 | ghidra 0x206c4d8 | size 96 | symbol _ZN4Aska12SoundManager22InitCaptureFrameBufferEv | lib libSOA-3.7.0.so | 2026-10-08
bool _ZN4Aska12SoundManager22InitCaptureFrameBufferEv(long param_1)

{
  undefined8 *puVar1;
  long lVar2;
  
  if ((~*(byte *)(param_1 + 0x1234) & 6) == 0) {
    if (*(long *)(param_1 + 0x6c0) != 0) {
      operator delete(void*)();
      *(undefined8 *)(param_1 + 0x6c0) = 0;
    }
    puVar1 = (undefined8 *)Aska::SoundMemory::Malloc(unsigned long)(8);
    *(undefined8 **)(param_1 + 0x6c0) = puVar1;
    lVar2 = 0;
    if (puVar1 != (undefined8 *)0x0) {
      *puVar1 = 0;
      lVar2 = *(long *)(param_1 + 0x6c0);
    }
    return lVar2 != 0;
  }
  return false;
}

// ==== Aska::SoundManager::DeleteCaptureFrameBuffer()
// vaddr 0x1f6c538 | ghidra 0x206c538 | size 52 | symbol _ZN4Aska12SoundManager24DeleteCaptureFrameBufferEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12SoundManager24DeleteCaptureFrameBufferEv(long param_1)

{
  if (((~*(byte *)(param_1 + 0x1234) & 6) == 0) && (*(long *)(param_1 + 0x6c0) != 0)) {
    operator delete(void*)();
    *(undefined8 *)(param_1 + 0x6c0) = 0;
  }
  return;
}

// ==== Aska::SoundManager::IsAllocatedCaptureFrameBuffer() const
// vaddr 0x1f6c56c | ghidra 0x206c56c | size 44 | symbol _ZNK4Aska12SoundManager29IsAllocatedCaptureFrameBufferEv | lib libSOA-3.7.0.so | 2026-10-08
bool _ZNK4Aska12SoundManager29IsAllocatedCaptureFrameBufferEv(long param_1)

{
  if ((~*(byte *)(param_1 + 0x1234) & 6) == 0) {
    return *(long *)(param_1 + 0x6c0) != 0;
  }
  return false;
}

// ==== Aska::SoundManager::SetFrameBufferCaptureOverride(Aska::IFrameBufferCaptureOverride*)
// vaddr 0x1f6c598 | ghidra 0x206c598 | size 4 | symbol _ZN4Aska12SoundManager29SetFrameBufferCaptureOverrideEPNS_27IFrameBufferCaptureOverrideE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12SoundManager29SetFrameBufferCaptureOverrideEPNS_27IFrameBufferCaptureOverrideE(void)

{
  return;
}

// ==== Aska::SoundManager::Get(unsigned long, void*) const
// vaddr 0x1f6c59c | ghidra 0x206c59c | size 8 | symbol _ZNK4Aska12SoundManager3GetEmPv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK4Aska12SoundManager3GetEmPv(void)

{
  return 0;
}

// ==== Aska::SoundManager::Set(unsigned long, void const*)
// vaddr 0x1f6c5a4 | ghidra 0x206c5a4 | size 8 | symbol _ZN4Aska12SoundManager3SetEmPKv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska12SoundManager3SetEmPKv(void)

{
  return 0;
}

// ==== Aska::SoundManagerThread::SoundManagerThread(Aska::SoundManager*)
// vaddr 0x1f6c5ac | ghidra 0x206c5ac | size 80 | symbol _ZN4Aska18SoundManagerThreadC1EPNS_12SoundManagerE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska18SoundManagerThreadC2EPNS_12SoundManagerE(long *param_1,long param_2)

{
  Aska::Thread::Thread()();
  *param_1 = (long)(PTR__ZTVN4Aska18SoundManagerThreadE_02cbc8d0 + 0x10);
  *(byte *)(param_1 + 4) = *(byte *)(param_1 + 4) & 0xfe;
  *(byte *)(param_1 + 4) = *(byte *)(param_1 + 4) & 0xfd;
  param_1[3] = param_2;
  return;
}

// ==== Aska::SoundManagerThread::Initialize()
// vaddr 0x1f6c5fc | ghidra 0x206c5fc | size 68 | symbol _ZN4Aska18SoundManagerThread10InitializeEv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska18SoundManagerThread10InitializeEv(long param_1)

{
  ulong uVar1;
  
  uVar1 = Aska::Thread::Create(bool, int, int, bool)(param_1,1,0x7f,0x8000,1);
  if ((uVar1 & 1) != 0) {
    *(byte *)(param_1 + 0x20) = *(byte *)(param_1 + 0x20) | 1;
    return 1;
  }
  return 0;
}

// ==== Aska::SoundManagerThread::Handler()
// vaddr 0x1f6c640 | ghidra 0x206c640 | size 60 | symbol _ZN4Aska18SoundManagerThread7HandlerEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska18SoundManagerThread7HandlerEv(long param_1)

{
  do {
    Aska::Thread::Sleep(unsigned int)(0x10);
    if ((*(byte *)(param_1 + 0x20) >> 1 & 1) != 0) {
      Aska::Thread::Exit()();
    }
    Aska::SoundManager::SoundProcessSync()(*(undefined8 *)(param_1 + 0x18));
    Aska::AudioSafetySignalNotify::Handler(unsigned long)(*(long *)(param_1 + 0x18) + 0x48,0);
  } while( true );
}

// ==== Aska::SoundManager::SoundProcessSync()
// vaddr 0x1f6c67c | ghidra 0x206c67c | size 540 | symbol _ZN4Aska12SoundManager16SoundProcessSyncEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12SoundManager16SoundProcessSyncEv(long param_1)

{
  long *plVar1;
  long lVar2;
  long lVar3;
  long *plVar4;
  long *plVar5;
  
  Aska::SoundManager::PauseInterruptProcess()();
  Aska::SoundManager::ResumeInterruptProcess()(param_1);
  Aska::SoundManager::ArrangeCommandList()(param_1);
  Aska::SoundManager::ProcessCommandList()(param_1);
  Aska::SoundManager::ProcessSoundPass()(param_1);
  if (*(long *)(param_1 + 0x3b8) == 0) {
    plVar4 = *(long **)(param_1 + 0x108);
    if ((long *)(param_1 + 0xf8) == plVar4) goto code_r0x0206c718;
  }
  else {
    Aska::AudioListener::Compute()(param_1 + 0x3a0);
    for (plVar4 = *(long **)(param_1 + 0x108); (long *)(param_1 + 0xf8) != plVar4;
        plVar4 = (long *)plVar4[2]) {
      if (plVar4[0x43] != 0) {
        Aska::AudioEmitter::Compute()(plVar4 + 0x40);
      }
    }
    plVar4 = *(long **)(param_1 + 0x108);
    if ((long *)(param_1 + 0xf8) == plVar4) goto code_r0x0206c718;
  }
  do {
    (**(code **)(*plVar4 + 0x40))(plVar4);
    plVar4 = (long *)plVar4[2];
  } while ((long *)(param_1 + 0xf8) != plVar4);
code_r0x0206c718:
  plVar4 = (long *)(param_1 + 0x120);
  for (plVar5 = *(long **)(param_1 + 0x130); plVar4 != plVar5; plVar5 = (long *)plVar5[2]) {
    (**(code **)(*plVar5 + 0x40))(plVar5);
  }
  Aska::AudioMixer::AudioRun()(*(undefined8 *)(param_1 + 0x6c8));
  if (*(int *)(param_1 + 0x6e8) != 0) {
    Aska::AudioEffector::AudioRun()(param_1 + 0x720);
  }
  if (*(int *)(param_1 + 0x800) != 0) {
    Aska::AudioEffector::AudioRun()(param_1 + 0x838);
  }
  if (*(int *)(param_1 + 0x918) != 0) {
    Aska::AudioEffector::AudioRun()(param_1 + 0x950);
  }
  Aska::SoundManager::UpdateReadDeviceAccessStatus()(param_1);
  if (*(char *)(param_1 + 0x1160) != '\0') {
    *(char *)(param_1 + 0x1160) = '\0';
    for (lVar2 = *(long *)(param_1 + 0x108); param_1 + 0xf8 != lVar2;
        lVar2 = *(long *)(lVar2 + 0x10)) {
      if ((*(long *)(lVar2 + 0x128) != 0) &&
         (lVar3 = *(long *)(*(long *)(lVar2 + 0x128) + 0x118), lVar3 != 0)) {
        *(undefined1 *)(lVar3 + 0x28) = 1;
      }
    }
    for (plVar5 = *(long **)(param_1 + 0x130); plVar4 != plVar5; plVar5 = (long *)plVar5[2]) {
      if ((plVar5[0x25] != 0) && (lVar2 = *(long *)(plVar5[0x25] + 0x118), lVar2 != 0)) {
        *(undefined1 *)(lVar2 + 0x28) = 1;
      }
    }
  }
  lVar2 = *(long *)(param_1 + 0x108);
  while (lVar3 = lVar2, param_1 + 0xf8 != lVar3) {
    lVar2 = *(long *)(lVar3 + 0x10);
    if ((*(long *)(lVar3 + 0x128) != 0) && (*(int *)(*(long *)(lVar3 + 0x128) + 0x18) == 5)) {
      Aska::SoundManager::DeleteSoundObject(Aska::SoundObject*, bool)(param_1,lVar3,0);
    }
  }
  plVar5 = *(long **)(param_1 + 0x130);
  while (plVar1 = plVar5, plVar4 != plVar1) {
    plVar5 = (long *)plVar1[2];
    if ((plVar1[0x25] != 0) && (*(int *)(plVar1[0x25] + 0x18) == 5)) {
      Aska::SoundManager::DeleteSoundObject(Aska::SoundObject*, bool)(param_1,plVar1,0);
    }
  }
  return;
}

// ==== Aska::SoundManager::SoundManager()
// vaddr 0x1f6c958 | ghidra 0x206c958 | size 1228 | symbol _ZN4Aska12SoundManagerC1Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12SoundManagerC2Ev(long *param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  long *plVar3;
  ulong uVar4;
  long lVar5;
  undefined *puVar6;
  undefined4 uVar7;
  undefined1 *puVar8;
  code *pcVar9;
  undefined1 *puVar10;
  ulong uVar12;
  ulong uVar13;
  undefined1 *puVar11;
  
  pcVar9 = *(code **)(PTR__ZTVN4Aska4TaskE_02cbe020 + 0x68);
  *param_1 = (long)(PTR__ZTVN4Aska4TaskE_02cbe020 + 0x10);
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  *(undefined2 *)((long)param_1 + 0x24) = 0;
  *(undefined1 *)((long)param_1 + 0x26) = 0;
  uVar7 = (*pcVar9)();
  *(undefined4 *)(param_1 + 4) = uVar7;
  puVar1 = PTR__ZTVN4Aska23AudioSafetySignalNotifyE_02cb7478 + 0x10;
  *param_1 = (long)(PTR__ZTVN4Aska12SoundManagerE_02cb89a0 + 0x10);
  param_1[9] = (long)puVar1;
  param_1[10] = 0;
  Aska::Thread::Thread()(param_1 + 0xb);
  param_1[0xb] = (long)(PTR__ZTVN4Aska23AudioSafetySignalThreadE_02cbf2a0 + 0x10);
  Aska::Event::Event()(param_1 + 0xe);
  *(undefined1 *)(param_1 + 0x1b) = 0;
  *(undefined4 *)(param_1 + 0x22) = 0;
  puVar6 = PTR__ZTVN4Aska21AnimatableLinkElementE_02cc02b8;
  puVar1 = PTR__ZTVN4Aska14AnimatableListE_02cb9290 + 0x10;
  param_1[0x20] = (long)(param_1 + 0x1f);
  param_1[0x21] = (long)(param_1 + 0x1f);
  *(undefined4 *)(param_1 + 0x27) = 0;
  param_1[0x28] = 0;
  param_1[0x2e] = 0;
  param_1[0x34] = 0;
  param_1[0x3a] = 0;
  param_1[0x40] = 0;
  param_1[0x46] = 0;
  param_1[0x4c] = 0;
  param_1[0x52] = 0;
  *(undefined4 *)(param_1 + 0x58) = 0;
  param_1[0x25] = (long)(param_1 + 0x24);
  param_1[0x26] = (long)(param_1 + 0x24);
  param_1[0x23] = (long)puVar1;
  param_1[0x24] = (long)(puVar6 + 0x10);
  puVar2 = PTR__ZTVN4Aska5TListINS_11SoundHandleEEE_02cba448;
  param_1[0x1f] = (long)(puVar6 + 0x10);
  param_1[0x1e] = (long)puVar1;
  param_1[0x5a] = (long)(PTR__ZTVN4Aska11SoundHandleE_02cbf3a8 + 0x10);
  param_1[0x59] = (long)(puVar2 + 0x10);
  param_1[0x5d] = 0;
  *(undefined4 *)(param_1 + 0x5e) = 0;
  param_1[0x5b] = (long)(param_1 + 0x5a);
  param_1[0x5c] = (long)(param_1 + 0x5a);
  Aska::FastCriticalSection::FastCriticalSection()(param_1 + 0x5f);
  Aska::Audio3DEngine::Audio3DEngine()(param_1 + 0x72);
  Aska::IAudioDevice::IAudioDevice()(param_1 + 0xda);
  puVar1 = PTR__ZTVN4Aska15AuxiliaryDeviceE_02cb88f0;
  *(undefined4 *)(param_1 + 0xde) = 0;
  param_1[0xe3] = 0;
  puVar1 = puVar1 + 0x10;
  param_1[0xe2] = 0;
  *(undefined4 *)(param_1 + 0xe1) = 0;
  param_1[0xe0] = 0;
  param_1[0xda] = (long)puVar1;
  param_1[0xdf] = 0;
  Aska::AudioEffector::AudioEffector()(param_1 + 0xe4);
  puVar2 = PTR__ZTVN4Aska17AuxiliaryEffectorE_02cc14d8;
  *(undefined4 *)(param_1 + 0xfc) = 0;
  puVar2 = puVar2 + 0x10;
  param_1[0xe4] = (long)puVar2;
  Aska::IAudioDevice::IAudioDevice()(param_1 + 0xfd);
  param_1[0xfd] = (long)puVar1;
  *(undefined4 *)(param_1 + 0x101) = 0;
  param_1[0x106] = 0;
  param_1[0x105] = 0;
  *(undefined4 *)(param_1 + 0x104) = 0;
  param_1[0x103] = 0;
  param_1[0x102] = 0;
  Aska::AudioEffector::AudioEffector()(param_1 + 0x107);
  param_1[0x107] = (long)puVar2;
  *(undefined4 *)(param_1 + 0x11f) = 0;
  Aska::IAudioDevice::IAudioDevice()(param_1 + 0x120);
  param_1[0x120] = (long)puVar1;
  *(undefined4 *)(param_1 + 0x124) = 0;
  param_1[0x129] = 0;
  param_1[0x128] = 0;
  *(undefined4 *)(param_1 + 0x127) = 0;
  param_1[0x126] = 0;
  param_1[0x125] = 0;
  Aska::AudioEffector::AudioEffector()(param_1 + 0x12a);
  param_1[0x12a] = (long)puVar2;
  *(undefined4 *)(param_1 + 0x142) = 0;
  puVar2 = PTR__ZTVN4Aska5TListINS_9SoundPassEEE_02cbeff8;
  plVar3 = param_1 + 0x15b;
  puVar1 = PTR__ZTVN4Aska5TListINS_12SoundCommandEEE_02cba8e8 + 0x10;
  param_1[0x144] = (long)(PTR__ZTVN4Aska12SoundCommandE_02cc0710 + 0x10);
  param_1[0x143] = (long)puVar1;
  *(undefined4 *)(param_1 + 0x147) = 0;
  param_1[0x148] = 0;
  *(undefined4 *)(param_1 + 0x159) = 0;
  param_1[0x145] = (long)(param_1 + 0x144);
  param_1[0x146] = (long)(param_1 + 0x144);
  param_1[0x15a] = (long)(puVar2 + 0x10);
  Aska::SoundPass::SoundPass()(plVar3);
  *(undefined4 *)(param_1 + 0x178) = 0;
  param_1[0x15c] = (long)plVar3;
  param_1[0x15d] = (long)plVar3;
  plVar3 = param_1 + 0x17a;
  param_1[0x179] = (long)(PTR__ZTVN4Aska5TListINS_14AudioInterfaceEEE_02cc3f18 + 0x10);
  Aska::AudioInterface::AudioInterface()(plVar3);
  *(undefined4 *)(param_1 + 0x17f) = 0;
  param_1[0x17b] = (long)plVar3;
  param_1[0x17c] = (long)plVar3;
  plVar3 = param_1 + 0x181;
  param_1[0x180] = (long)(PTR__ZTVN4Aska5TListINS_11SoundObjectEEE_02cb70c0 + 0x10);
  Aska::SoundObject::SoundObject()(plVar3);
  *(undefined4 *)(param_1 + 0x1c0) = 0;
  param_1[0x182] = (long)plVar3;
  param_1[0x183] = (long)plVar3;
  Aska::FastCriticalSection::FastCriticalSection()(param_1 + 0x1c1);
  Aska::FastCriticalSection::FastCriticalSection()(param_1 + 0x1d3);
  Aska::FastCriticalSection::FastCriticalSection()(param_1 + 0x1e5);
  Aska::FastCriticalSection::FastCriticalSection()(param_1 + 0x1f7);
  Aska::FastCriticalSection::FastCriticalSection()(param_1 + 0x209);
  puVar1 = PTR__ZTVN4Aska8THashMapImfNS_7THasherImEENS_8TEqualToImEENS_10TAllocatorINS_5TPairIKmfEEEEEE_02cbb700
           + 0x10;
  param_1[0x21d] = (long)puVar1;
  *(undefined8 *)((long)param_1 + 0x10f4) = 0x3f400000;
  *(undefined4 *)((long)param_1 + 0x10fc) = 0;
  puVar8 = (undefined1 *)Aska::MemoryManagerAdapter::AlignedMalloc(unsigned long, unsigned long)(0x198,8);
  lVar5 = 0x11;
  if (puVar8 == (undefined1 *)0x0) {
    lVar5 = 0;
  }
  param_1[0x221] = (long)puVar8;
  param_1[0x222] = lVar5;
  if (puVar8 != (undefined1 *)0x0) {
    uVar4 = (lVar5 * 0x18 - 0x18U) / 0x18 + 1;
    puVar11 = puVar8;
    if ((1 < uVar4) && (uVar12 = uVar4 & 0x1ffffffffffffffe, uVar12 != 0)) {
      uVar13 = uVar12;
      do {
        *puVar11 = 0;
        puVar11[0x18] = 0;
        uVar13 = uVar13 - 2;
        puVar11 = puVar11 + 0x30;
      } while (uVar13 != 0);
      puVar11 = puVar8 + uVar12 * 0x18;
      if (uVar4 == uVar12) goto code_r0x0206ccd8;
    }
    do {
      puVar10 = puVar11 + 0x18;
      *puVar11 = 0;
      puVar11 = puVar10;
    } while (puVar8 + lVar5 * 0x18 != puVar10);
  }
code_r0x0206ccd8:
  param_1[0x223] = (long)puVar1;
  *(undefined8 *)((long)param_1 + 0x1124) = 0x3f400000;
  *(undefined4 *)((long)param_1 + 0x112c) = 0;
  puVar8 = (undefined1 *)Aska::MemoryManagerAdapter::AlignedMalloc(unsigned long, unsigned long)(0x198,8);
  lVar5 = 0x11;
  if (puVar8 == (undefined1 *)0x0) {
    lVar5 = 0;
  }
  param_1[0x227] = (long)puVar8;
  param_1[0x228] = lVar5;
  if (puVar8 != (undefined1 *)0x0) {
    uVar4 = (lVar5 * 0x18 - 0x18U) / 0x18 + 1;
    puVar11 = puVar8;
    if ((1 < uVar4) && (uVar12 = uVar4 & 0x1ffffffffffffffe, uVar12 != 0)) {
      uVar13 = uVar12;
      do {
        *puVar11 = 0;
        puVar11[0x18] = 0;
        uVar13 = uVar13 - 2;
        puVar11 = puVar11 + 0x30;
      } while (uVar13 != 0);
      puVar11 = puVar8 + uVar12 * 0x18;
      if (uVar4 == uVar12) goto code_r0x0206cd8c;
    }
    do {
      puVar10 = puVar11 + 0x18;
      *puVar11 = 0;
      puVar11 = puVar10;
    } while (puVar8 + lVar5 * 0x18 != puVar10);
  }
code_r0x0206cd8c:
  Aska::FastCriticalSection::FastCriticalSection()(param_1 + 0x22d);
  puVar1 = 
  PTR__ZTVN4Aska13TDynamicArrayINS_14AudioSmallHeap8HeapInfoENS_14AudioAllocatorIS2_EEEE_02cbaab0;
  param_1[0x242] = 0;
  param_1[0x23f] = (long)(puVar1 + 0x10);
  param_1[0x244] = 0;
  *(undefined4 *)(param_1 + 7) = 0;
  param_1[0x1c] = 0;
  param_1[0x1d] = 0;
  param_1[0x241] = 0;
  param_1[0x240] = 0;
  param_1[6] = 0;
  param_1[5] = 0;
  *(undefined4 *)((long)param_1 + 0x3c) = 0;
  param_1[8] = 0;
  param_1[0xd9] = 0;
  param_1[0xd8] = 0;
  *(undefined4 *)(param_1 + 0x21b) = 0;
  param_1[0x22a] = -1;
  param_1[0x21c] = 0;
  param_1[0x229] = 0;
  *(undefined2 *)(param_1 + 0x22b) = 0;
  *(undefined1 *)((long)param_1 + 0x115a) = 0;
  *(undefined4 *)((long)param_1 + 0x115c) = 1;
  *(undefined1 *)(param_1 + 0x22c) = 0;
  param_1[0x245] = 0;
  *(undefined4 *)(param_1 + 0x246) = 0;
  *(byte *)((long)param_1 + 0x1234) = *(byte *)((long)param_1 + 0x1234) & 0xf8;
  return;
}

// ==== Aska::SoundManager::~SoundManager()
// vaddr 0x1f6ce24 | ghidra 0x206ce24 | size 836 | symbol _ZN4Aska12SoundManagerD2Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12SoundManagerD1Ev(long *param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  undefined *puVar3;
  long lVar4;
  code *pcVar5;
  long lVar6;
  
  puVar1 = PTR__ZN4Aska12SoundManager11m_pInstanceE_02cc2868;
  *param_1 = (long)(PTR__ZTVN4Aska12SoundManagerE_02cb89a0 + 0x10);
  *(undefined8 *)puVar1 = 0;
  Aska::AudioSmallHeap::Finalize()(param_1 + 0x22d);
  lVar4 = param_1[0x240];
  param_1[0x23f] =
       (long)(
             PTR__ZTVN4Aska13TDynamicArrayINS_14AudioSmallHeap8HeapInfoENS_14AudioAllocatorIS2_EEEE_02cbaab0
             + 0x10);
  if (param_1[0x242] != lVar4) {
    lVar6 = param_1[0x241];
    if (lVar6 != lVar4) {
      do {
        Aska::detail::FixedSizeHeap::~FixedSizeHeap()(lVar4 + 8);
        lVar4 = lVar4 + 0x30;
      } while (lVar6 != lVar4);
      lVar4 = param_1[0x240];
    }
    if (lVar4 != 0) {
      operator delete[](void*)(lVar4);
    }
    param_1[0x241] = 0;
    param_1[0x242] = 0;
    param_1[0x240] = 0;
  }
  Aska::FastCriticalSection::~FastCriticalSection()(param_1 + 0x22d);
  puVar1 = PTR__ZTVN4Aska8THashMapImfNS_7THasherImEENS_8TEqualToImEENS_10TAllocatorINS_5TPairIKmfEEEEEE_02cbb700
           + 0x10;
  param_1[0x223] = (long)puVar1;
  if (param_1[0x227] != 0) {
    Aska::MemoryManagerAdapter::AlignedFree(void*)();
    param_1[0x227] = 0;
    param_1[0x228] = 0;
  }
  param_1[0x225] = 0;
  param_1[0x21d] = (long)puVar1;
  if (param_1[0x221] != 0) {
    Aska::MemoryManagerAdapter::AlignedFree(void*)();
    param_1[0x221] = 0;
    param_1[0x222] = 0;
  }
  param_1[0x21f] = 0;
  Aska::FastCriticalSection::~FastCriticalSection()(param_1 + 0x209);
  Aska::FastCriticalSection::~FastCriticalSection()(param_1 + 0x1f7);
  Aska::FastCriticalSection::~FastCriticalSection()(param_1 + 0x1e5);
  Aska::FastCriticalSection::~FastCriticalSection()(param_1 + 0x1d3);
  Aska::FastCriticalSection::~FastCriticalSection()(param_1 + 0x1c1);
  param_1[0x180] = (long)(PTR__ZTVN4Aska5TListINS_11SoundObjectEEE_02cb70c0 + 0x10);
  Aska::SoundObject::~SoundObject()(param_1 + 0x181);
  param_1[0x15a] = (long)(PTR__ZTVN4Aska5TListINS_9SoundPassEEE_02cbeff8 + 0x10);
  Aska::SoundPass::~SoundPass()(param_1 + 0x15b);
  puVar1 = PTR__ZTVN4Aska15AuxiliaryDeviceE_02cb88f0;
  pcVar5 = *(code **)(PTR__ZTVN4Aska15AuxiliaryDeviceE_02cb88f0 + 0x70);
  param_1[0x120] = (long)(PTR__ZTVN4Aska15AuxiliaryDeviceE_02cb88f0 + 0x10);
  (*pcVar5)(param_1 + 0x120);
  puVar3 = PTR__ZTVN4Aska13AudioEffectorE_02cc4a78;
  *(undefined4 *)(param_1 + 0x12e) = 0;
  param_1[0x12a] = (long)(puVar3 + 0x10);
  param_1[0x12d] = 1;
  if (param_1[0x12f] != 0) {
    operator delete[](void*)();
    param_1[0x12f] = 0;
  }
  Aska::FastCriticalSection::~FastCriticalSection()(param_1 + 0x130);
  puVar2 = PTR__ZTVN4Aska13TDynamicQueueINS_15EffectorRequest16RequestContainerELb1EEE_02cb7d20;
  *(undefined4 *)(param_1 + 0x12e) = 0;
  param_1[300] = (long)(puVar2 + 0x10);
  param_1[0x12d] = 1;
  if (param_1[0x12f] != 0) {
    operator delete[](void*)();
    param_1[0x12f] = 0;
  }
  Aska::IAnimatable::~IAnimatable()(param_1 + 0x12a);
  Aska::IAudioDevice::~IAudioDevice()(param_1 + 0x120);
  param_1[0xfd] = (long)(puVar1 + 0x10);
  (*pcVar5)(param_1 + 0xfd);
  param_1[0x107] = (long)(puVar3 + 0x10);
  param_1[0x10a] = 1;
  *(undefined4 *)(param_1 + 0x10b) = 0;
  if (param_1[0x10c] != 0) {
    operator delete[](void*)();
    param_1[0x10c] = 0;
  }
  Aska::FastCriticalSection::~FastCriticalSection()(param_1 + 0x10d);
  param_1[0x109] = (long)(puVar2 + 0x10);
  param_1[0x10a] = 1;
  *(undefined4 *)(param_1 + 0x10b) = 0;
  if (param_1[0x10c] != 0) {
    operator delete[](void*)();
    param_1[0x10c] = 0;
  }
  Aska::IAnimatable::~IAnimatable()(param_1 + 0x107);
  Aska::IAudioDevice::~IAudioDevice()(param_1 + 0xfd);
  param_1[0xda] = (long)(puVar1 + 0x10);
  (*pcVar5)(param_1 + 0xda);
  param_1[0xe4] = (long)(puVar3 + 0x10);
  param_1[0xe7] = 1;
  *(undefined4 *)(param_1 + 0xe8) = 0;
  if (param_1[0xe9] != 0) {
    operator delete[](void*)();
    param_1[0xe9] = 0;
  }
  Aska::FastCriticalSection::~FastCriticalSection()(param_1 + 0xea);
  param_1[0xe6] = (long)(puVar2 + 0x10);
  param_1[0xe7] = 1;
  *(undefined4 *)(param_1 + 0xe8) = 0;
  if (param_1[0xe9] != 0) {
    operator delete[](void*)();
    param_1[0xe9] = 0;
  }
  Aska::IAnimatable::~IAnimatable()(param_1 + 0xe4);
  Aska::IAudioDevice::~IAudioDevice()(param_1 + 0xda);
  Aska::Audio3DEngine::~Audio3DEngine()(param_1 + 0x72);
  Aska::FastCriticalSection::~FastCriticalSection()(param_1 + 0x5f);
  puVar1 = PTR__ZTVN4Aska5TListINS_21AnimatableLinkElementEEE_02cc13d8 + 0x10;
  param_1[0x23] = (long)puVar1;
  Aska::IAnimatable::~IAnimatable()(param_1 + 0x24);
  param_1[0x1e] = (long)puVar1;
  Aska::IAnimatable::~IAnimatable()(param_1 + 0x1f);
  param_1[0xb] = (long)(PTR__ZTVN4Aska23AudioSafetySignalThreadE_02cbf2a0 + 0x10);
  Aska::Event::Exit()(param_1 + 0xe);
  Aska::Thread::~Thread()(param_1 + 0xb);
  (*(code *)PTR__ZN4Aska4TaskD1Ev_02c92d10)(param_1);
  return;
}

// ==== Aska::SoundManager::~SoundManager()
// vaddr 0x1f6d1f0 | ghidra 0x206d1f0 | size 24 | symbol _ZN4Aska12SoundManagerD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12SoundManagerD0Ev(undefined8 param_1)

{
  Aska::SoundManager::~SoundManager()();
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::SoundManager::DeleteAllSoundObject()
// vaddr 0x1f6d208 | ghidra 0x206d208 | size 132 | symbol _ZN4Aska12SoundManager20DeleteAllSoundObjectEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12SoundManager20DeleteAllSoundObjectEv(long param_1)

{
  long lVar1;
  long lVar2;
  
  if ((~*(byte *)(param_1 + 0x1234) & 6) == 0) {
    lVar1 = *(long *)(param_1 + 0x108);
    while (param_1 + 0xf8 != lVar1) {
      lVar2 = *(long *)(lVar1 + 0x10);
      Aska::SoundManager::DeleteSoundObject(Aska::SoundObject*, bool)(param_1,lVar1,1);
      lVar1 = lVar2;
    }
    lVar1 = *(long *)(param_1 + 0x130);
    while (param_1 + 0x120 != lVar1) {
      lVar2 = *(long *)(lVar1 + 0x10);
      Aska::SoundManager::DeleteSoundObject(Aska::SoundObject*, bool)(param_1,lVar1,1);
      lVar1 = lVar2;
    }
  }
  return;
}

// ==== Aska::SoundManager::FlushDeletingSoundObject()
// vaddr 0x1f6d28c | ghidra 0x206d28c | size 528 | symbol _ZN4Aska12SoundManager24FlushDeletingSoundObjectEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12SoundManager24FlushDeletingSoundObjectEv(long param_1)

{
  int *piVar1;
  int *piVar2;
  char cVar3;
  bool bVar4;
  ulong uVar5;
  int iVar6;
  long lVar7;
  long lVar8;
  long lVar9;
  
  if ((~*(byte *)(param_1 + 0x1234) & 6) != 0) {
    return;
  }
  piVar1 = (int *)(param_1 + 0xff0);
  iVar6 = 0;
  do {
    while (*piVar1 == -1) {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = 0;
        cVar3 = ExclusiveMonitorsStatus();
      }
      if (cVar3 == '\0') goto code_r0x0206d380;
    }
    ClearExclusiveLocal();
    bVar4 = iVar6 < 0x1ff;
    iVar6 = iVar6 + 1;
  } while (bVar4);
  piVar2 = (int *)(param_1 + 0xff4);
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
        uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0x1030);
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
          Aska::Semaphore::Wait() const(param_1 + 0x1030);
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
          if (cVar3 == '\0') goto code_r0x0206d370;
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
code_r0x0206d370:
  do {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar4) {
      *piVar2 = *piVar2 + -1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
code_r0x0206d380:
  DataMemoryBarrier(2,3);
  lVar9 = *(long *)(param_1 + 0xc18);
  while (lVar8 = lVar9, param_1 + 0xc08 != lVar8) {
    lVar9 = *(long *)(lVar8 + 0x10);
    if (((((*(byte *)(lVar8 + 0x1e8) >> 3 & 1) == 0) || (*(long *)(lVar8 + 0x128) == 0)) ||
        (lVar7 = *(long *)(*(long *)(lVar8 + 0x128) + 0x118), lVar7 == 0)) ||
       ((lVar7 = *(long *)(*(long *)(lVar7 + 0x30) + 8), lVar7 == 0 ||
        (*(int *)(lVar7 + 0x3fc) == 0)))) {
      lVar7 = *(long *)(lVar8 + 8);
      if (lVar7 != 0) {
        *(long *)(lVar7 + 0x10) = lVar9;
      }
      if (lVar9 != 0) {
        *(long *)(lVar9 + 8) = lVar7;
      }
      if (0 < *(int *)(param_1 + 0xe00)) {
        *(int *)(param_1 + 0xe00) = *(int *)(param_1 + 0xe00) + -1;
      }
      *(long *)(lVar8 + 8) = 0;
      *(undefined8 *)(lVar8 + 0x10) = 0;
      lVar7 = Aska::SoundManager::QuerySoundHandle(Aska::SoundObject*) const(param_1,lVar8);
      if (lVar7 != 0) {
        Aska::SoundManager::RemoveSoundHandle(Aska::SoundHandle*)(param_1,lVar7);
        Aska::SoundServer::ReleaseSoundHandle(Aska::SoundHandle*)(*(undefined8 *)(param_1 + 0xe8),lVar7);
        Aska::SoundServer::ReleaseSoundObject(Aska::SoundObject*)(*(undefined8 *)(param_1 + 0xe8),lVar8);
      }
    }
  }
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_1 + 0xff0) = 0xffffffff;
  DataMemoryBarrier(2,3);
  if (*(int *)(param_1 + 0xff4) < 0x15) {
    return;
  }
  piVar1 = (int *)(param_1 + 0xff4);
  do {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar4) {
      *piVar1 = *piVar1 + -1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
  uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0x1030);
  if ((uVar5 & 1) == 0) {
    return;
  }
  (*(code *)PTR__ZNK4Aska9Semaphore6SignalEv_02c96cd0)(param_1 + 0x1030);
  return;
}

// ==== Aska::SoundManager::StopAllSignal()
// vaddr 0x1f6d49c | ghidra 0x206d49c | size 96 | symbol _ZN4Aska12SoundManager13StopAllSignalEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12SoundManager13StopAllSignalEv(long param_1)

{
  *(undefined1 *)(param_1 + 0xd8) = 1;
  Aska::Event::Set() const(param_1 + 0x70);
  Aska::Thread::WaitEnd()(param_1 + 0x58);
  Aska::AudioSafetySignalNotify::Finalize()(param_1 + 0x48);
  if (*(long *)(param_1 + 0x40) != 0) {
    Aska::Task::Remove()();
    (**(code **)(**(long **)(param_1 + 0x40) + 0x38))(*(long **)(param_1 + 0x40),0);
    *(undefined8 *)(param_1 + 0x40) = 0;
  }
  return;
}

// ==== Aska::SoundManager::Run(int)
// vaddr 0x1f6d4fc | ghidra 0x206d4fc | size 32 | symbol _ZN4Aska12SoundManager3RunEi | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12SoundManager3RunEi(long param_1)

{
  Aska::SoundManager::UpdateAllSoundStatus()();
  Aska::Audio3DEngine::UpdateAll3DObjectMatrix()(param_1 + 0x390);
  (*(code *)PTR__ZN4Aska12SoundManager24FlushDeletingSoundObjectEv_02cb0128)(param_1);
  return;
}

// ==== Aska::SoundManager::UpdateAllSoundStatus()
// vaddr 0x1f6d51c | ghidra 0x206d51c | size 636 | symbol _ZN4Aska12SoundManager20UpdateAllSoundStatusEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12SoundManager20UpdateAllSoundStatusEv(long param_1)

{
  int *piVar1;
  int *piVar2;
  long lVar3;
  char cVar4;
  bool bVar5;
  ulong uVar6;
  int iVar7;
  long lVar8;
  long lVar9;
  
  piVar2 = (int *)(param_1 + 0x330);
  iVar7 = 0;
  do {
    while (*piVar2 != -1) {
      ClearExclusiveLocal();
      bVar5 = 0x1fe < iVar7;
      iVar7 = iVar7 + 1;
      if (bVar5) {
        piVar1 = (int *)(param_1 + 0x334);
        do {
          cVar4 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar5) {
            *piVar1 = *piVar1 + 1;
            cVar4 = ExclusiveMonitorsStatus();
          }
        } while (cVar4 != '\0');
        do {
          if (*piVar2 != -1) {
            ClearExclusiveLocal();
            do {
              uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x370);
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
                Aska::Semaphore::Wait() const(param_1 + 0x370);
              }
              do {
                cVar4 = '\x01';
                bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
                if (bVar5) {
                  *piVar1 = *piVar1 + 1;
                  cVar4 = ExclusiveMonitorsStatus();
                }
              } while (cVar4 != '\0');
              while (*piVar2 == -1) {
                cVar4 = '\x01';
                bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
                if (bVar5) {
                  *piVar2 = 0;
                  cVar4 = ExclusiveMonitorsStatus();
                }
                if (cVar4 == '\0') goto code_r0x0206d780;
              }
              ClearExclusiveLocal();
            } while( true );
          }
          cVar4 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
          if (bVar5) {
            *piVar2 = 0;
            cVar4 = ExclusiveMonitorsStatus();
          }
        } while (cVar4 != '\0');
code_r0x0206d780:
        do {
          cVar4 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar5) {
            *piVar1 = *piVar1 + -1;
            cVar4 = ExclusiveMonitorsStatus();
          }
        } while (cVar4 != '\0');
        DataMemoryBarrier(2,3);
        goto code_r0x0206d594;
      }
    }
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar5) {
      *piVar2 = 0;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
  DataMemoryBarrier(2,3);
code_r0x0206d594:
  lVar8 = *(long *)(param_1 + 0x2e0);
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_1 + 0x330) = 0xffffffff;
  DataMemoryBarrier(2,3);
  piVar1 = (int *)(param_1 + 0x334);
  if (0x14 < *piVar1) {
    do {
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar5) {
        *piVar1 = *piVar1 + -1;
        cVar4 = ExclusiveMonitorsStatus();
      }
    } while (cVar4 != '\0');
    uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x370);
    if ((uVar6 & 1) != 0) {
      Aska::Semaphore::Signal() const(param_1 + 0x370);
    }
  }
  if (param_1 + 0x2d0 == lVar8) {
    return;
  }
  lVar3 = param_1 + 0x370;
  do {
    iVar7 = 0;
    do {
      while (*piVar2 == -1) {
        cVar4 = '\x01';
        bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
        if (bVar5) {
          *piVar2 = 0;
          cVar4 = ExclusiveMonitorsStatus();
        }
        if (cVar4 == '\0') goto code_r0x0206d6ac;
      }
      ClearExclusiveLocal();
      bVar5 = iVar7 < 0x1ff;
      iVar7 = iVar7 + 1;
    } while (bVar5);
    do {
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar5) {
        *piVar1 = *piVar1 + 1;
        cVar4 = ExclusiveMonitorsStatus();
      }
    } while (cVar4 != '\0');
    do {
      if (*piVar2 != -1) {
        do {
          ClearExclusiveLocal();
          uVar6 = Aska::Semaphore::IsReady() const(lVar3);
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
            Aska::Semaphore::Wait() const(lVar3);
          }
          do {
            cVar4 = '\x01';
            bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
            if (bVar5) {
              *piVar1 = *piVar1 + 1;
              cVar4 = ExclusiveMonitorsStatus();
            }
          } while (cVar4 != '\0');
          while (*piVar2 == -1) {
            cVar4 = '\x01';
            bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
            if (bVar5) {
              *piVar2 = 0;
              cVar4 = ExclusiveMonitorsStatus();
            }
            if (cVar4 == '\0') goto code_r0x0206d69c;
          }
        } while( true );
      }
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
      if (bVar5) {
        *piVar2 = 0;
        cVar4 = ExclusiveMonitorsStatus();
      }
    } while (cVar4 != '\0');
code_r0x0206d69c:
    do {
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar5) {
        *piVar1 = *piVar1 + -1;
        cVar4 = ExclusiveMonitorsStatus();
      }
    } while (cVar4 != '\0');
code_r0x0206d6ac:
    DataMemoryBarrier(2,3);
    lVar9 = *(long *)(lVar8 + 0x10);
    DataMemoryBarrier(2,3);
    *piVar2 = -1;
    DataMemoryBarrier(2,3);
    if (0x14 < *piVar1) {
      do {
        cVar4 = '\x01';
        bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
        if (bVar5) {
          *piVar1 = *piVar1 + -1;
          cVar4 = ExclusiveMonitorsStatus();
        }
      } while (cVar4 != '\0');
      uVar6 = Aska::Semaphore::IsReady() const(lVar3);
      if ((uVar6 & 1) != 0) {
        Aska::Semaphore::Signal() const(lVar3);
      }
    }
    if (*(long *)(lVar8 + 0x18) != 0) {
      Aska::SoundObject::UpdateSoundStatus()();
    }
    lVar8 = lVar9;
    if (param_1 + 0x2d0 == lVar9) {
      return;
    }
  } while( true );
}

// ==== Aska::SoundManager::PauseInterruptProcess()
// vaddr 0x1f6d798 | ghidra 0x206d798 | size 920 | symbol _ZN4Aska12SoundManager21PauseInterruptProcessEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12SoundManager21PauseInterruptProcessEv(long param_1)

{
  ulong uVar1;
  char cVar2;
  ulong uVar3;
  undefined4 *puVar4;
  undefined8 *puVar5;
  undefined8 uVar6;
  long *plVar7;
  int iVar8;
  ulong uVar9;
  char *pcVar10;
  ulong uVar11;
  ulong uVar12;
  int *piVar13;
  long lVar14;
  ulong uVar15;
  undefined4 uVar16;
  float fVar17;
  ulong uStack_68;
  
  if (*(char *)(param_1 + 0x1158) != '\0') {
    if (*(char *)(param_1 + 0x115a) == '\0') {
      if (*(long *)(param_1 + 0x1148) == 0) {
        uVar15 = *(ulong *)(param_1 + 0x130);
        if (param_1 + 0x120U != uVar15) {
          do {
            if (*(int *)(uVar15 + 0x1e4) - 1U < 4) {
              uVar9 = *(ulong *)(param_1 + 0x1140);
              if (uVar9 != 0) {
                uVar11 = ~uVar15 + uVar15 * 0x200000;
                uVar11 = (uVar11 ^ uVar11 >> 0x18) * 0x109;
                uVar12 = (uVar11 ^ uVar11 >> 0xe) * 0x15;
                uVar11 = 0;
                do {
                  uVar1 = (uVar12 ^ uVar12 >> 0x1c) * 0x80000001 + uVar11;
                  uVar3 = 0;
                  if (uVar9 != 0) {
                    uVar3 = uVar1 / uVar9;
                  }
                  lVar14 = uVar1 - uVar3 * uVar9;
                  cVar2 = *(char *)(*(long *)(param_1 + 0x1138) + lVar14 * 0x18);
                  if (cVar2 == '\x01') {
                    if (*(ulong *)(*(long *)(param_1 + 0x1138) + lVar14 * 0x18 + 8) == uVar15)
                    goto code_r0x0206d8f0;
                  }
                  else if (cVar2 == '\0') break;
                  uVar11 = uVar11 + 1;
                } while (uVar11 < uVar9);
              }
              if (*(long *)(uVar15 + 0x128) == 0) {
                uVar16 = 0;
              }
              else {
                uVar16 = Aska::AudioPlayer::GetDeviceParam(unsigned int)(*(long *)(uVar15 + 0x128),0);
              }
              uStack_68 = uVar15;
              puVar4 = (undefined4 *)Aska::THashMap<unsigned long, float, Aska::THasher<unsigned long>, Aska::TEqualTo<unsigned long>, Aska::TAllocator<Aska::TPair<unsigned long const, float> > >::operator[](unsigned long const&)(param_1 + 0x1118,&uStack_68);
              *puVar4 = uVar16;
              uStack_68 = uStack_68 & 0xffffffff00000000;
              Aska::Sequencer2::AddMessageNote(unsigned int, float, void const*, void const*)(*(float *)(uVar15 + 0x108) + 0.0,uVar15 + 0x18,5,uStack_68,
                              (long)*(int *)(param_1 + 0x1150));
            }
code_r0x0206d8f0:
            uVar15 = *(ulong *)(uVar15 + 0x10);
          } while (param_1 + 0x120U != uVar15);
        }
        pcVar10 = *(char **)(param_1 + 0x1108);
        if ((pcVar10 != (char *)0x0) && (*(long *)(param_1 + 0x1110) != 0)) {
          lVar14 = *(long *)(param_1 + 0x1110) * 0x18;
          do {
            piVar13 = (int *)(param_1 + 0x10f8);
            if ((*pcVar10 == '\x01') || (piVar13 = (int *)(param_1 + 0x10fc), *pcVar10 == '\x02')) {
              *piVar13 = *piVar13 + -1;
              *pcVar10 = '\0';
            }
            lVar14 = lVar14 + -0x18;
            pcVar10 = pcVar10 + 0x18;
          } while (lVar14 != 0);
        }
        uVar15 = *(ulong *)(param_1 + 0x108);
        *(undefined8 *)(param_1 + 0x10f8) = 0;
        if (param_1 + 0xf8U != uVar15) {
          do {
            if (*(int *)(uVar15 + 0x1e4) - 1U < 4) {
              if (*(long *)(uVar15 + 0x128) == 0) {
                uVar16 = 0;
              }
              else {
                uVar16 = Aska::AudioPlayer::GetDeviceParam(unsigned int)(*(long *)(uVar15 + 0x128),0);
              }
              uStack_68 = uVar15;
              puVar4 = (undefined4 *)Aska::THashMap<unsigned long, float, Aska::THasher<unsigned long>, Aska::TEqualTo<unsigned long>, Aska::TAllocator<Aska::TPair<unsigned long const, float> > >::operator[](unsigned long const&)(param_1 + 0x10e8,&uStack_68);
              *puVar4 = uVar16;
              uStack_68 = uStack_68 & 0xffffffff00000000;
              Aska::Sequencer2::AddMessageNote(unsigned int, float, void const*, void const*)(*(float *)(uVar15 + 0x108) + 0.0,uVar15 + 0x18,5,uStack_68,
                              (long)*(int *)(param_1 + 0x1150));
            }
            uVar15 = *(ulong *)(uVar15 + 0x10);
          } while (param_1 + 0xf8U != uVar15);
        }
        puVar5 = *(undefined8 **)(param_1 + 0x10e0);
        if (puVar5 != (undefined8 *)0x0) {
          (**(code **)*puVar5)(puVar5,0);
        }
        uVar6 = Aska::Global::GetCPUTime()();
        *(undefined8 *)(param_1 + 0x1148) = uVar6;
      }
      for (lVar14 = *(long *)(param_1 + 0x130); param_1 + 0x120 != lVar14;
          lVar14 = *(long *)(lVar14 + 0x10)) {
        iVar8 = *(int *)(lVar14 + 0x1e4);
        if (iVar8 - 1U < 4) {
          plVar7 = *(long **)(lVar14 + 0x128);
          if (plVar7 != (long *)0x0) {
            fVar17 = (float)(**(code **)(*plVar7 + 0x88))(plVar7,0);
            if (0.0 < fVar17) goto code_r0x0206da1c;
            iVar8 = *(int *)(lVar14 + 0x1e4);
          }
          if (1 < iVar8 - 3U) {
            Aska::SoundObject::Pause()(lVar14);
          }
        }
code_r0x0206da1c:
      }
      for (lVar14 = *(long *)(param_1 + 0x108); param_1 + 0xf8 != lVar14;
          lVar14 = *(long *)(lVar14 + 0x10)) {
        iVar8 = *(int *)(lVar14 + 0x1e4);
        if (iVar8 - 1U < 4) {
          plVar7 = *(long **)(lVar14 + 0x128);
          if (plVar7 != (long *)0x0) {
            fVar17 = (float)(**(code **)(*plVar7 + 0x88))(plVar7,0);
            if (0.0 < fVar17) goto code_r0x0206da88;
            iVar8 = *(int *)(lVar14 + 0x1e4);
          }
          if (1 < iVar8 - 3U) {
            Aska::SoundObject::Pause()(lVar14);
          }
        }
code_r0x0206da88:
      }
      lVar14 = Aska::Global::GetCPUTime()();
      if ((ulong)(lVar14 - *(long *)(param_1 + 0x1148)) < (ulong)(long)*(int *)(param_1 + 0x1150)) {
        return;
      }
      *(undefined8 *)(param_1 + 0x1148) = 0;
      *(undefined4 *)(param_1 + 0x1150) = 0xffffffff;
      *(char *)(param_1 + 0x115a) = '\x01';
    }
    else {
      *(undefined8 *)(param_1 + 0x1148) = 0;
      *(undefined4 *)(param_1 + 0x1150) = 0xffffffff;
    }
    *(char *)(param_1 + 0x1158) = '\0';
  }
  return;
}

// ==== Aska::SoundManager::ResumeInterruptProcess()
// vaddr 0x1f6db30 | ghidra 0x206db30 | size 904 | symbol _ZN4Aska12SoundManager22ResumeInterruptProcessEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12SoundManager22ResumeInterruptProcessEv(long param_1)

{
  char *pcVar1;
  ulong uVar2;
  char cVar3;
  ulong uVar4;
  ulong uVar5;
  undefined4 *puVar6;
  undefined8 *puVar7;
  char *pcVar8;
  ulong uVar9;
  ulong uVar10;
  long lVar11;
  int *piVar12;
  ulong uVar13;
  undefined4 uVar14;
  undefined4 uVar15;
  ulong uStack_58;
  
  pcVar1 = (char *)(param_1 + 0x1159);
  if ((*pcVar1 != '\0') && (*(char *)(param_1 + 0x1158) == '\0')) {
    if (*(char *)(param_1 + 0x115a) == '\0') {
      *pcVar1 = '\0';
      *(undefined4 *)(param_1 + 0x1154) = 0xffffffff;
    }
    else {
      uVar13 = *(ulong *)(param_1 + 0x130);
      if (param_1 + 0x120U != uVar13) {
        uVar15 = 0x3f800000;
        do {
          if ((*(int *)(uVar13 + 0x1e4) - 1U < 4) &&
             (uVar5 = Aska::SoundObject::Resume()(uVar13), (uVar5 & 1) != 0)) {
            uVar5 = *(ulong *)(param_1 + 0x1140);
            uVar14 = uVar15;
            if (uVar5 != 0) {
              uVar9 = ~uVar13 + uVar13 * 0x200000;
              uVar9 = (uVar9 ^ uVar9 >> 0x18) * 0x109;
              uVar10 = (uVar9 ^ uVar9 >> 0xe) * 0x15;
              uVar9 = 0;
              do {
                uVar2 = (uVar10 ^ uVar10 >> 0x1c) * 0x80000001 + uVar9;
                uVar4 = 0;
                if (uVar5 != 0) {
                  uVar4 = uVar2 / uVar5;
                }
                lVar11 = uVar2 - uVar4 * uVar5;
                cVar3 = *(char *)(*(long *)(param_1 + 0x1138) + lVar11 * 0x18);
                if (cVar3 == '\x01') {
                  if (*(ulong *)(*(long *)(param_1 + 0x1138) + lVar11 * 0x18 + 8) == uVar13) {
                    uStack_58 = uVar13;
                    puVar6 = (undefined4 *)Aska::THashMap<unsigned long, float, Aska::THasher<unsigned long>, Aska::TEqualTo<unsigned long>, Aska::TAllocator<Aska::TPair<unsigned long const, float> > >::operator[](unsigned long const&)(param_1 + 0x1118,&uStack_58);
                    uVar14 = *puVar6;
                    break;
                  }
                }
                else if (cVar3 == '\0') break;
                uVar9 = uVar9 + 1;
              } while (uVar9 < uVar5);
            }
            uStack_58 = CONCAT44(uStack_58._4_4_,uVar14);
            Aska::Sequencer2::AddMessageNote(unsigned int, float, void const*, void const*)(*(float *)(uVar13 + 0x108) + 0.0,uVar13 + 0x18,5,uStack_58,
                            (long)*(int *)(param_1 + 0x1154));
          }
          uVar13 = *(ulong *)(uVar13 + 0x10);
        } while (param_1 + 0x120U != uVar13);
      }
      uVar13 = *(ulong *)(param_1 + 0x108);
      if (param_1 + 0xf8U != uVar13) {
        uVar15 = 0x3f800000;
        do {
          if ((*(int *)(uVar13 + 0x1e4) - 1U < 4) &&
             (uVar5 = Aska::SoundObject::Resume()(uVar13), (uVar5 & 1) != 0)) {
            uVar5 = *(ulong *)(param_1 + 0x1110);
            uVar14 = uVar15;
            if (uVar5 != 0) {
              uVar9 = ~uVar13 + uVar13 * 0x200000;
              uVar9 = (uVar9 ^ uVar9 >> 0x18) * 0x109;
              uVar10 = (uVar9 ^ uVar9 >> 0xe) * 0x15;
              uVar9 = 0;
              do {
                uVar2 = (uVar10 ^ uVar10 >> 0x1c) * 0x80000001 + uVar9;
                uVar4 = 0;
                if (uVar5 != 0) {
                  uVar4 = uVar2 / uVar5;
                }
                lVar11 = uVar2 - uVar4 * uVar5;
                cVar3 = *(char *)(*(long *)(param_1 + 0x1108) + lVar11 * 0x18);
                if (cVar3 == '\x01') {
                  if (*(ulong *)(*(long *)(param_1 + 0x1108) + lVar11 * 0x18 + 8) == uVar13) {
                    uStack_58 = uVar13;
                    puVar6 = (undefined4 *)Aska::THashMap<unsigned long, float, Aska::THasher<unsigned long>, Aska::TEqualTo<unsigned long>, Aska::TAllocator<Aska::TPair<unsigned long const, float> > >::operator[](unsigned long const&)(param_1 + 0x10e8,&uStack_58);
                    uVar14 = *puVar6;
                    break;
                  }
                }
                else if (cVar3 == '\0') break;
                uVar9 = uVar9 + 1;
              } while (uVar9 < uVar5);
            }
            uStack_58 = CONCAT44(uStack_58._4_4_,uVar14);
            Aska::Sequencer2::AddMessageNote(unsigned int, float, void const*, void const*)(*(float *)(uVar13 + 0x108) + 0.0,uVar13 + 0x18,5,uStack_58,
                            (long)*(int *)(param_1 + 0x1154));
          }
          uVar13 = *(ulong *)(uVar13 + 0x10);
        } while (param_1 + 0xf8U != uVar13);
      }
      puVar7 = *(undefined8 **)(param_1 + 0x10e0);
      if (puVar7 != (undefined8 *)0x0) {
        (**(code **)*puVar7)(puVar7,1);
      }
      pcVar8 = *(char **)(param_1 + 0x1138);
      if ((pcVar8 != (char *)0x0) && (*(long *)(param_1 + 0x1140) != 0)) {
        lVar11 = *(long *)(param_1 + 0x1140) * 0x18;
        do {
          piVar12 = (int *)(param_1 + 0x1128);
          if ((*pcVar8 == '\x01') || (piVar12 = (int *)(param_1 + 0x112c), *pcVar8 == '\x02')) {
            *piVar12 = *piVar12 + -1;
            *pcVar8 = '\0';
          }
          lVar11 = lVar11 + -0x18;
          pcVar8 = pcVar8 + 0x18;
        } while (lVar11 != 0);
      }
      pcVar8 = *(char **)(param_1 + 0x1108);
      *(undefined8 *)(param_1 + 0x1128) = 0;
      if ((pcVar8 != (char *)0x0) && (*(long *)(param_1 + 0x1110) != 0)) {
        lVar11 = *(long *)(param_1 + 0x1110) * 0x18;
        do {
          piVar12 = (int *)(param_1 + 0x10f8);
          if ((*pcVar8 == '\x01') || (piVar12 = (int *)(param_1 + 0x10fc), *pcVar8 == '\x02')) {
            *piVar12 = *piVar12 + -1;
            *pcVar8 = '\0';
          }
          lVar11 = lVar11 + -0x18;
          pcVar8 = pcVar8 + 0x18;
        } while (lVar11 != 0);
      }
      *(undefined8 *)(param_1 + 0x10f8) = 0;
      *(undefined4 *)(param_1 + 0x1154) = 0xffffffff;
      *(char *)(param_1 + 0x115a) = '\0';
      *pcVar1 = '\0';
    }
  }
  return;
}

// ==== Aska::SoundManager::ArrangeCommandList()
// vaddr 0x1f6deb8 | ghidra 0x206deb8 | size 676 | symbol _ZN4Aska12SoundManager18ArrangeCommandListEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12SoundManager18ArrangeCommandListEv(long param_1)

{
  int *piVar1;
  int *piVar2;
  long lVar3;
  char cVar4;
  bool bVar5;
  ulong uVar6;
  int iVar7;
  long lVar8;
  long lVar9;
  
  piVar2 = (int *)(param_1 + 0xe40);
  iVar7 = 0;
  do {
    while (*piVar2 != -1) {
      ClearExclusiveLocal();
      bVar5 = 0x1fe < iVar7;
      iVar7 = iVar7 + 1;
      if (bVar5) {
        piVar1 = (int *)(param_1 + 0xe44);
        do {
          cVar4 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar5) {
            *piVar1 = *piVar1 + 1;
            cVar4 = ExclusiveMonitorsStatus();
          }
        } while (cVar4 != '\0');
        do {
          if (*piVar2 != -1) {
            ClearExclusiveLocal();
            do {
              uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0xe80);
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
                Aska::Semaphore::Wait() const(param_1 + 0xe80);
              }
              do {
                cVar4 = '\x01';
                bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
                if (bVar5) {
                  *piVar1 = *piVar1 + 1;
                  cVar4 = ExclusiveMonitorsStatus();
                }
              } while (cVar4 != '\0');
              while (*piVar2 == -1) {
                cVar4 = '\x01';
                bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
                if (bVar5) {
                  *piVar2 = 0;
                  cVar4 = ExclusiveMonitorsStatus();
                }
                if (cVar4 == '\0') goto code_r0x0206e144;
              }
              ClearExclusiveLocal();
            } while( true );
          }
          cVar4 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
          if (bVar5) {
            *piVar2 = 0;
            cVar4 = ExclusiveMonitorsStatus();
          }
        } while (cVar4 != '\0');
code_r0x0206e144:
        do {
          cVar4 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar5) {
            *piVar1 = *piVar1 + -1;
            cVar4 = ExclusiveMonitorsStatus();
          }
        } while (cVar4 != '\0');
        DataMemoryBarrier(2,3);
        goto code_r0x0206df34;
      }
    }
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar5) {
      *piVar2 = 0;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
  DataMemoryBarrier(2,3);
code_r0x0206df34:
  lVar8 = *(long *)(param_1 + 0xa30);
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_1 + 0xe40) = 0xffffffff;
  DataMemoryBarrier(2,3);
  piVar1 = (int *)(param_1 + 0xe44);
  if (0x14 < *piVar1) {
    do {
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar5) {
        *piVar1 = *piVar1 + -1;
        cVar4 = ExclusiveMonitorsStatus();
      }
    } while (cVar4 != '\0');
    uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0xe80);
    if ((uVar6 & 1) != 0) {
      Aska::Semaphore::Signal() const(param_1 + 0xe80);
    }
  }
  if (param_1 + 0xa20 == lVar8) {
    return;
  }
  lVar3 = param_1 + 0xe80;
  do {
    iVar7 = 0;
    do {
      while (*piVar2 == -1) {
        cVar4 = '\x01';
        bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
        if (bVar5) {
          *piVar2 = 0;
          cVar4 = ExclusiveMonitorsStatus();
        }
        if (cVar4 == '\0') goto code_r0x0206e050;
      }
      ClearExclusiveLocal();
      bVar5 = iVar7 < 0x1ff;
      iVar7 = iVar7 + 1;
    } while (bVar5);
    do {
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar5) {
        *piVar1 = *piVar1 + 1;
        cVar4 = ExclusiveMonitorsStatus();
      }
    } while (cVar4 != '\0');
    do {
      if (*piVar2 != -1) {
        do {
          ClearExclusiveLocal();
          uVar6 = Aska::Semaphore::IsReady() const(lVar3);
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
            Aska::Semaphore::Wait() const(lVar3);
          }
          do {
            cVar4 = '\x01';
            bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
            if (bVar5) {
              *piVar1 = *piVar1 + 1;
              cVar4 = ExclusiveMonitorsStatus();
            }
          } while (cVar4 != '\0');
          while (*piVar2 == -1) {
            cVar4 = '\x01';
            bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
            if (bVar5) {
              *piVar2 = 0;
              cVar4 = ExclusiveMonitorsStatus();
            }
            if (cVar4 == '\0') goto code_r0x0206e040;
          }
        } while( true );
      }
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
      if (bVar5) {
        *piVar2 = 0;
        cVar4 = ExclusiveMonitorsStatus();
      }
    } while (cVar4 != '\0');
code_r0x0206e040:
    do {
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar5) {
        *piVar1 = *piVar1 + -1;
        cVar4 = ExclusiveMonitorsStatus();
      }
    } while (cVar4 != '\0');
code_r0x0206e050:
    DataMemoryBarrier(2,3);
    lVar9 = *(long *)(lVar8 + 0x10);
    DataMemoryBarrier(2,3);
    *piVar2 = -1;
    DataMemoryBarrier(2,3);
    if (0x14 < *piVar1) {
      do {
        cVar4 = '\x01';
        bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
        if (bVar5) {
          *piVar1 = *piVar1 + -1;
          cVar4 = ExclusiveMonitorsStatus();
        }
      } while (cVar4 != '\0');
      uVar6 = Aska::Semaphore::IsReady() const(lVar3);
      if ((uVar6 & 1) != 0) {
        Aska::Semaphore::Signal() const(lVar3);
      }
    }
    uVar6 = Aska::SoundCommand::ArrangeCommand(Aska::TList<Aska::SoundCommand>*)(lVar8,param_1 + 0xa18);
    if ((uVar6 & 1) != 0) {
      Aska::SoundManager::RemoveSoundCommand(Aska::SoundCommand*)(param_1,lVar8);
      Aska::SoundServer::ReleaseSoundCommand(Aska::SoundCommand*)(*(undefined8 *)(param_1 + 0xe8),lVar8);
    }
    lVar8 = lVar9;
    if (param_1 + 0xa20 == lVar9) {
      return;
    }
  } while( true );
}

// ==== Aska::SoundManager::ProcessCommandList()
// vaddr 0x1f6e15c | ghidra 0x206e15c | size 964 | symbol _ZN4Aska12SoundManager18ProcessCommandListEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12SoundManager18ProcessCommandListEv(long param_1)

{
  int *piVar1;
  int *piVar2;
  long lVar3;
  char cVar4;
  bool bVar5;
  ulong uVar6;
  int iVar7;
  long lVar8;
  long lVar9;
  long lStack_58;
  
  piVar2 = (int *)(param_1 + 0xe40);
  iVar7 = 0;
  do {
    while (*piVar2 != -1) {
      ClearExclusiveLocal();
      bVar5 = 0x1fe < iVar7;
      iVar7 = iVar7 + 1;
      if (bVar5) {
        piVar1 = (int *)(param_1 + 0xe44);
        do {
          cVar4 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar5) {
            *piVar1 = *piVar1 + 1;
            cVar4 = ExclusiveMonitorsStatus();
          }
        } while (cVar4 != '\0');
        do {
          if (*piVar2 != -1) {
            ClearExclusiveLocal();
            do {
              uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0xe80);
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
                Aska::Semaphore::Wait() const(param_1 + 0xe80);
              }
              do {
                cVar4 = '\x01';
                bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
                if (bVar5) {
                  *piVar1 = *piVar1 + 1;
                  cVar4 = ExclusiveMonitorsStatus();
                }
              } while (cVar4 != '\0');
              while (*piVar2 == -1) {
                cVar4 = '\x01';
                bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
                if (bVar5) {
                  *piVar2 = 0;
                  cVar4 = ExclusiveMonitorsStatus();
                }
                if (cVar4 == '\0') goto code_r0x0206e508;
              }
              ClearExclusiveLocal();
            } while( true );
          }
          cVar4 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
          if (bVar5) {
            *piVar2 = 0;
            cVar4 = ExclusiveMonitorsStatus();
          }
        } while (cVar4 != '\0');
code_r0x0206e508:
        do {
          cVar4 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar5) {
            *piVar1 = *piVar1 + -1;
            cVar4 = ExclusiveMonitorsStatus();
          }
        } while (cVar4 != '\0');
        DataMemoryBarrier(2,3);
        goto code_r0x0206e1dc;
      }
    }
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar5) {
      *piVar2 = 0;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
  DataMemoryBarrier(2,3);
code_r0x0206e1dc:
  lVar8 = *(long *)(param_1 + 0xa30);
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_1 + 0xe40) = 0xffffffff;
  DataMemoryBarrier(2,3);
  piVar1 = (int *)(param_1 + 0xe44);
  if (0x14 < *piVar1) {
    do {
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar5) {
        *piVar1 = *piVar1 + -1;
        cVar4 = ExclusiveMonitorsStatus();
      }
    } while (cVar4 != '\0');
    uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0xe80);
    if ((uVar6 & 1) != 0) {
      Aska::Semaphore::Signal() const(param_1 + 0xe80);
    }
  }
  if (param_1 + 0xa20 == lVar8) {
    return;
  }
  lVar3 = param_1 + 0xe80;
  do {
    iVar7 = 0;
    do {
      while (*piVar2 == -1) {
        cVar4 = '\x01';
        bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
        if (bVar5) {
          *piVar2 = 0;
          cVar4 = ExclusiveMonitorsStatus();
        }
        if (cVar4 == '\0') goto code_r0x0206e2f4;
      }
      ClearExclusiveLocal();
      bVar5 = iVar7 < 0x1ff;
      iVar7 = iVar7 + 1;
    } while (bVar5);
    do {
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar5) {
        *piVar1 = *piVar1 + 1;
        cVar4 = ExclusiveMonitorsStatus();
      }
    } while (cVar4 != '\0');
    do {
      if (*piVar2 != -1) {
        do {
          ClearExclusiveLocal();
          uVar6 = Aska::Semaphore::IsReady() const(lVar3);
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
            Aska::Semaphore::Wait() const(lVar3);
          }
          do {
            cVar4 = '\x01';
            bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
            if (bVar5) {
              *piVar1 = *piVar1 + 1;
              cVar4 = ExclusiveMonitorsStatus();
            }
          } while (cVar4 != '\0');
          while (*piVar2 == -1) {
            cVar4 = '\x01';
            bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
            if (bVar5) {
              *piVar2 = 0;
              cVar4 = ExclusiveMonitorsStatus();
            }
            if (cVar4 == '\0') goto code_r0x0206e2e4;
          }
        } while( true );
      }
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
      if (bVar5) {
        *piVar2 = 0;
        cVar4 = ExclusiveMonitorsStatus();
      }
    } while (cVar4 != '\0');
code_r0x0206e2e4:
    do {
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar5) {
        *piVar1 = *piVar1 + -1;
        cVar4 = ExclusiveMonitorsStatus();
      }
    } while (cVar4 != '\0');
code_r0x0206e2f4:
    DataMemoryBarrier(2,3);
    lVar9 = *(long *)(lVar8 + 0x10);
    DataMemoryBarrier(2,3);
    *piVar2 = -1;
    DataMemoryBarrier(2,3);
    if (0x14 < *piVar1) {
      do {
        cVar4 = '\x01';
        bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
        if (bVar5) {
          *piVar1 = *piVar1 + -1;
          cVar4 = ExclusiveMonitorsStatus();
        }
      } while (cVar4 != '\0');
      uVar6 = Aska::Semaphore::IsReady() const(lVar3);
      if ((uVar6 & 1) != 0) {
        Aska::Semaphore::Signal() const(lVar3);
      }
    }
    uVar6 = Aska::SoundCommand::ProcessCommand(Aska::SoundCommand**)(lVar8,&lStack_58);
    if (lStack_58 != 0) {
      Aska::SoundManager::InsertSoundCommand(Aska::SoundCommand*, Aska::SoundCommand*)(param_1,lVar8);
    }
    if ((uVar6 & 1) != 0) {
      Aska::SoundManager::RemoveSoundCommand(Aska::SoundCommand*)(param_1,lVar8);
      Aska::SoundServer::ReleaseSoundCommand(Aska::SoundCommand*)(*(undefined8 *)(param_1 + 0xe8),lVar8);
    }
    iVar7 = 0;
    lVar8 = lStack_58;
    if (lStack_58 == 0) {
      lVar8 = lVar9;
    }
    do {
      while (*piVar2 == -1) {
        cVar4 = '\x01';
        bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
        if (bVar5) {
          *piVar2 = 0;
          cVar4 = ExclusiveMonitorsStatus();
        }
        if (cVar4 == '\0') goto code_r0x0206e440;
      }
      ClearExclusiveLocal();
      bVar5 = iVar7 < 0x1ff;
      iVar7 = iVar7 + 1;
    } while (bVar5);
    do {
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar5) {
        *piVar1 = *piVar1 + 1;
        cVar4 = ExclusiveMonitorsStatus();
      }
    } while (cVar4 != '\0');
    do {
      if (*piVar2 != -1) {
        do {
          ClearExclusiveLocal();
          uVar6 = Aska::Semaphore::IsReady() const(lVar3);
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
            Aska::Semaphore::Wait() const(lVar3);
          }
          do {
            cVar4 = '\x01';
            bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
            if (bVar5) {
              *piVar1 = *piVar1 + 1;
              cVar4 = ExclusiveMonitorsStatus();
            }
          } while (cVar4 != '\0');
          while (*piVar2 == -1) {
            cVar4 = '\x01';
            bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
            if (bVar5) {
              *piVar2 = 0;
              cVar4 = ExclusiveMonitorsStatus();
            }
            if (cVar4 == '\0') goto code_r0x0206e430;
          }
        } while( true );
      }
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
      if (bVar5) {
        *piVar2 = 0;
        cVar4 = ExclusiveMonitorsStatus();
      }
    } while (cVar4 != '\0');
code_r0x0206e430:
    do {
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar5) {
        *piVar1 = *piVar1 + -1;
        cVar4 = ExclusiveMonitorsStatus();
      }
    } while (cVar4 != '\0');
code_r0x0206e440:
    DataMemoryBarrier(2,3);
    DataMemoryBarrier(2,3);
    *piVar2 = -1;
    DataMemoryBarrier(2,3);
    if (0x14 < *piVar1) {
      do {
        cVar4 = '\x01';
        bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
        if (bVar5) {
          *piVar1 = *piVar1 + -1;
          cVar4 = ExclusiveMonitorsStatus();
        }
      } while (cVar4 != '\0');
      uVar6 = Aska::Semaphore::IsReady() const(lVar3);
      if ((uVar6 & 1) != 0) {
        Aska::Semaphore::Signal() const(lVar3);
      }
    }
    if (param_1 + 0xa20 == lVar8) {
      return;
    }
  } while( true );
}

// ==== Aska::SoundManager::ProcessSoundPass()
// vaddr 0x1f6e520 | ghidra 0x206e520 | size 256 | symbol _ZN4Aska12SoundManager16ProcessSoundPassEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12SoundManager16ProcessSoundPassEv(long param_1)

{
  long lVar1;
  ulong uVar2;
  long lVar3;
  long lVar4;
  int *piVar5;
  long lVar6;
  long lVar7;
  
  lVar1 = param_1 + 0xad8;
  if (lVar1 != *(long *)(param_1 + 0xae8)) {
    lVar6 = *(long *)(param_1 + 0xae8);
    do {
      lVar7 = *(long *)(lVar6 + 0x10);
      uVar2 = Aska::SoundPass::AudioRun()(lVar6);
      if (*(int *)(lVar6 + 0x18) == 7) {
        lVar3 = *(long *)(lVar6 + 0x58);
        if ((*(uint *)(lVar3 + 0x1e8) & 1) == 0) {
          if ((*(uint *)(lVar3 + 0x1e8) >> 1 & 1) == 0) goto code_r0x0206e5b4;
          lVar4 = *(long *)(param_1 + 0x128);
          *(long *)(lVar3 + 8) = lVar4;
          *(long *)(lVar3 + 0x10) = param_1 + 0x120;
          *(long *)(param_1 + 0x128) = lVar3;
          piVar5 = (int *)(param_1 + 0x138);
        }
        else {
          lVar4 = *(long *)(param_1 + 0x100);
          *(long *)(lVar3 + 8) = lVar4;
          *(long *)(lVar3 + 0x10) = param_1 + 0xf8;
          *(long *)(param_1 + 0x100) = lVar3;
          piVar5 = (int *)(param_1 + 0x110);
        }
        *(long *)(lVar4 + 0x10) = lVar3;
        *piVar5 = *piVar5 + 1;
      }
code_r0x0206e5b4:
      if ((uVar2 & 1) != 0) {
        if (lVar1 != lVar6) {
          lVar3 = *(long *)(lVar6 + 8);
          lVar4 = *(long *)(lVar6 + 0x10);
          if (lVar3 != 0) {
            *(long *)(lVar3 + 0x10) = lVar4;
          }
          if (lVar4 != 0) {
            *(long *)(lVar4 + 8) = lVar3;
          }
          if (0 < *(int *)(param_1 + 0xbc0)) {
            *(int *)(param_1 + 0xbc0) = *(int *)(param_1 + 0xbc0) + -1;
          }
          *(long *)(lVar6 + 8) = 0;
          *(undefined8 *)(lVar6 + 0x10) = 0;
        }
        Aska::SoundServer::ReleaseSoundPass(Aska::SoundPass*)(*(undefined8 *)(param_1 + 0xe8),lVar6);
      }
      lVar6 = lVar7;
    } while (lVar1 != lVar7);
  }
  return;
}

// ==== Aska::SoundManager::ProcessAudioDevice()
// vaddr 0x1f6e620 | ghidra 0x206e620 | size 76 | symbol _ZN4Aska12SoundManager18ProcessAudioDeviceEv | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Possible PIC construction at 0x0206e63c: Changing call to branch */

void _ZN4Aska12SoundManager18ProcessAudioDeviceEv(long param_1)

{
  Aska::AudioMixer::AudioRun()(*(undefined8 *)(param_1 + 0x6c8));
  if (*(int *)(param_1 + 0x6e8) == 0) {
    if (*(int *)(param_1 + 0x800) != 0) {
      Aska::AudioEffector::AudioRun()(param_1 + 0x838);
    }
    if (*(int *)(param_1 + 0x918) == 0) {
      return;
    }
    param_1 = param_1 + 0x950;
  }
  else {
    param_1 = param_1 + 0x720;
  }
  (*(code *)PTR__ZN4Aska13AudioEffector8AudioRunEv_02c9bb40)(param_1);
  return;
}

// ==== Aska::SoundManager::UpdateReadDeviceAccessStatus()
// vaddr 0x1f6e66c | ghidra 0x206e66c | size 320 | symbol _ZN4Aska12SoundManager28UpdateReadDeviceAccessStatusEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12SoundManager28UpdateReadDeviceAccessStatusEv(long param_1)

{
  bool bVar1;
  byte bVar2;
  long lVar3;
  byte bVar4;
  uint uVar5;
  long lVar6;
  
  lVar3 = *(long *)(param_1 + 0xae8);
  if (param_1 + 0xad8 == lVar3) {
    uVar5 = 0;
  }
  else {
    bVar1 = false;
    uVar5 = 0;
    do {
      if (*(int *)(lVar3 + 0x1c) - 1U < 2) {
        if ((*(uint *)(lVar3 + 0x70) & 1) == 0) {
          uVar5 = uVar5 | (*(uint *)(lVar3 + 0x70) & 2) >> 1;
        }
        else {
          bVar1 = true;
        }
      }
      lVar3 = *(long *)(lVar3 + 0x10);
    } while (param_1 + 0xad8 != lVar3);
    if (bVar1) {
      bVar2 = 1;
      goto joined_r0x0206e730;
    }
  }
  lVar3 = *(long *)(param_1 + 0x108);
  if (param_1 + 0xf8 == lVar3) {
    bVar2 = 0;
  }
  else {
    bVar2 = 0;
    do {
      if (((((*(byte *)(lVar3 + 0x1e8) >> 3 & 1) != 0) && (*(long *)(lVar3 + 0x128) != 0)) &&
          (lVar6 = *(long *)(*(long *)(lVar3 + 0x128) + 0x118), lVar6 != 0)) &&
         (lVar6 = *(long *)(*(long *)(lVar6 + 0x30) + 8), lVar6 != 0)) {
        bVar2 = bVar2 | *(int *)(lVar6 + 0x3fc) != 0;
      }
      lVar3 = *(long *)(lVar3 + 0x10);
    } while (param_1 + 0xf8 != lVar3);
  }
joined_r0x0206e730:
  if (uVar5 == 0) {
    lVar3 = *(long *)(param_1 + 0x130);
    if (param_1 + 0x120 == lVar3) {
      bVar4 = 0;
    }
    else {
      bVar4 = 0;
      do {
        if ((((*(byte *)(lVar3 + 0x1e8) >> 3 & 1) != 0) && (*(long *)(lVar3 + 0x128) != 0)) &&
           ((lVar6 = *(long *)(*(long *)(lVar3 + 0x128) + 0x118), lVar6 != 0 &&
            (lVar6 = *(long *)(*(long *)(lVar6 + 0x30) + 8), lVar6 != 0)))) {
          bVar4 = bVar4 | *(int *)(lVar6 + 0x3fc) != 0;
        }
        lVar3 = *(long *)(lVar3 + 0x10);
      } while (param_1 + 0x120 != lVar3);
    }
  }
  else {
    bVar4 = 1;
  }
  *(byte *)(param_1 + 0x1234) = *(byte *)(param_1 + 0x1234) & 0xfe | bVar2 | bVar4;
  return;
}

// ==== Aska::SoundManager::UpdateOutputConfig()
// vaddr 0x1f6e7ac | ghidra 0x206e7ac | size 128 | symbol _ZN4Aska12SoundManager18UpdateOutputConfigEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12SoundManager18UpdateOutputConfigEv(long param_1)

{
  long lVar1;
  long lVar2;
  
  if (*(char *)(param_1 + 0x1160) != '\0') {
    *(char *)(param_1 + 0x1160) = '\0';
    for (lVar1 = *(long *)(param_1 + 0x108); param_1 + 0xf8 != lVar1;
        lVar1 = *(long *)(lVar1 + 0x10)) {
      if ((*(long *)(lVar1 + 0x128) != 0) &&
         (lVar2 = *(long *)(*(long *)(lVar1 + 0x128) + 0x118), lVar2 != 0)) {
        *(undefined1 *)(lVar2 + 0x28) = 1;
      }
    }
    for (lVar1 = *(long *)(param_1 + 0x130); param_1 + 0x120 != lVar1;
        lVar1 = *(long *)(lVar1 + 0x10)) {
      if ((*(long *)(lVar1 + 0x128) != 0) &&
         (lVar2 = *(long *)(*(long *)(lVar1 + 0x128) + 0x118), lVar2 != 0)) {
        *(undefined1 *)(lVar2 + 0x28) = 1;
      }
    }
  }
  return;
}

// ==== Aska::SoundManager::SetDefaultDirectPlaybackSettings(Aska::DirectPlaybackSettings*)
// vaddr 0x1f6e82c | ghidra 0x206e82c | size 32 | symbol _ZN4Aska12SoundManager32SetDefaultDirectPlaybackSettingsEPNS_22DirectPlaybackSettingsE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12SoundManager32SetDefaultDirectPlaybackSettingsEPNS_22DirectPlaybackSettingsE
               (undefined8 *param_1)

{
  *param_1 = 0;
  param_1[1] = 0;
  *(undefined2 *)(param_1 + 6) = 0;
  param_1[2] = 0x3f800000;
  param_1[3] = 0x100ffff00000000;
  param_1[4] = 0;
  param_1[5] = 0;
  return;
}

// ==== Aska::SoundManager::AdxSetDefaultDirectPlaybackSettings(Aska::AdxDirectPlaybackSettings*)
// vaddr 0x1f6e84c | ghidra 0x206e84c | size 4 | symbol _ZN4Aska12SoundManager35AdxSetDefaultDirectPlaybackSettingsEPNS_25AdxDirectPlaybackSettingsE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12SoundManager35AdxSetDefaultDirectPlaybackSettingsEPNS_25AdxDirectPlaybackSettingsE
               (void)

{
  return;
}

// ==== Aska::SoundManager::PlaySound(unsigned long, bool, unsigned int, unsigned int, Aska::DirectPlaybackSettings const*)
// vaddr 0x1f6e850 | ghidra 0x206e850 | size 408 | symbol _ZN4Aska12SoundManager9PlaySoundEmbjjPKNS_22DirectPlaybackSettingsE | lib libSOA-3.7.0.so | 2026-10-08
long _ZN4Aska12SoundManager9PlaySoundEmbjjPKNS_22DirectPlaybackSettingsE
               (long param_1,undefined8 param_2,uint param_3,undefined4 param_4,undefined4 param_5,
               long *param_6)

{
  uint uVar1;
  long lVar2;
  long lVar3;
  long lVar4;
  
  if ((~*(byte *)(param_1 + 0x1234) & 6) == 0) {
    lVar2 = Aska::SoundServer::AcquireSoundObject(unsigned int)(*(undefined8 *)(param_1 + 0xe8),param_5);
    if (lVar2 == 0) {
      return 0;
    }
    lVar3 = Aska::SoundServer::AcquireSoundHandle()(*(undefined8 *)(param_1 + 0xe8));
    if (lVar3 == 0) {
      Aska::SoundServer::ReleaseSoundObject(Aska::SoundObject*)(*(undefined8 *)(param_1 + 0xe8),lVar2);
    }
    else {
      *(long *)(lVar3 + 0x18) = lVar2;
      Aska::SoundManager::AddSoundHandle(Aska::SoundHandle*)(param_1,lVar3);
      lVar3 = Aska::SoundServer::AcquireSoundCommand()(*(undefined8 *)(param_1 + 0xe8));
      if ((((lVar3 != 0) && (*(undefined4 *)(lVar2 + 0x1e4) = 1, param_6 != (long *)0x0)) &&
          ((uVar1 = *(uint *)(lVar2 + 0x1e8), (uVar1 >> 1 & 1) == 0 ||
           (*(int *)((long)param_6 + 0xc) == 0)))) &&
         (((uVar1 >> 2 & 1) == 0 ||
          (((int)param_6[5] == 0 && (*(int *)((long)param_6 + 0x2c) == 0)))))) {
        if ((*param_6 != 0) && ((uVar1 & 1) != 0)) {
          Aska::SEControlObject::AttachEmitter(Aska::HierarchicalObject*)(lVar2);
        }
        *(undefined1 *)(lVar2 + 0x120) = 1;
        *(undefined4 *)(lVar3 + 0x18) = 1;
        *(long *)(lVar3 + 0x20) = lVar2;
        *(undefined8 *)(lVar3 + 0x28) = param_2;
        *(uint *)(lVar3 + 0x30) = param_3 & 1;
        *(undefined4 *)(lVar3 + 0x34) = param_4;
        *(undefined4 *)(lVar3 + 0x38) = param_5;
        *(long *)(lVar3 + 0x6c) = param_6[6];
        lVar4 = param_6[4];
        *(long *)(lVar3 + 100) = param_6[5];
        *(long *)(lVar3 + 0x5c) = lVar4;
        lVar4 = param_6[2];
        *(long *)(lVar3 + 0x54) = param_6[3];
        *(long *)(lVar3 + 0x4c) = lVar4;
        lVar4 = *param_6;
        *(long *)(lVar3 + 0x44) = param_6[1];
        *(long *)(lVar3 + 0x3c) = lVar4;
        Aska::SoundManager::AddSoundCommand(Aska::SoundCommand*)(param_1,lVar3);
        return lVar2;
      }
      *(byte *)(lVar2 + 0x1f2) = *(byte *)(lVar2 + 0x1f2) | 1;
      lVar4 = Aska::SoundManager::QuerySoundHandle(Aska::SoundObject*) const(param_1,lVar2);
      if (lVar4 != 0) {
        Aska::SoundManager::RemoveSoundHandle(Aska::SoundHandle*)(param_1,lVar4);
        Aska::SoundServer::ReleaseSoundHandle(Aska::SoundHandle*)(*(undefined8 *)(param_1 + 0xe8),lVar4);
        Aska::SoundServer::ReleaseSoundObject(Aska::SoundObject*)(*(undefined8 *)(param_1 + 0xe8),lVar2);
      }
      if (lVar3 != 0) {
        Aska::SoundServer::ReleaseSoundCommand(Aska::SoundCommand*)(*(undefined8 *)(param_1 + 0xe8),lVar3);
      }
    }
  }
  return 0;
}

// ==== Aska::SoundManager::AddSoundCommand(Aska::SoundCommand*)
// vaddr 0x1f6e9e8 | ghidra 0x206e9e8 | size 372 | symbol _ZN4Aska12SoundManager15AddSoundCommandEPNS_12SoundCommandE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12SoundManager15AddSoundCommandEPNS_12SoundCommandE(long param_1,long param_2)

{
  int *piVar1;
  int *piVar2;
  char cVar3;
  bool bVar4;
  ulong uVar5;
  int iVar6;
  long lVar7;
  
  piVar1 = (int *)(param_1 + 0xe40);
  iVar6 = 0;
  do {
    while (*piVar1 != -1) {
      ClearExclusiveLocal();
      bVar4 = 0x1fe < iVar6;
      iVar6 = iVar6 + 1;
      if (bVar4) {
        piVar2 = (int *)(param_1 + 0xe44);
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
              uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0xe80);
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
                Aska::Semaphore::Wait() const(param_1 + 0xe80);
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
                if (cVar3 == '\0') goto code_r0x0206eb44;
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
code_r0x0206eb44:
        do {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
          if (bVar4) {
            *piVar2 = *piVar2 + -1;
            cVar3 = ExclusiveMonitorsStatus();
          }
        } while (cVar3 != '\0');
        DataMemoryBarrier(2,3);
code_r0x0206ea60:
        lVar7 = *(long *)(param_1 + 0xa28);
        *(long *)(param_2 + 8) = lVar7;
        *(long *)(param_2 + 0x10) = param_1 + 0xa20;
        *(long *)(param_1 + 0xa28) = param_2;
        *(long *)(lVar7 + 0x10) = param_2;
        *(int *)(param_1 + 0xac8) = *(int *)(param_1 + 0xac8) + 1;
        DataMemoryBarrier(2,3);
        *(undefined4 *)(param_1 + 0xe40) = 0xffffffff;
        DataMemoryBarrier(2,3);
        piVar1 = (int *)(param_1 + 0xe44);
        if (0x14 < *piVar1) {
          do {
            cVar3 = '\x01';
            bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
            if (bVar4) {
              *piVar1 = *piVar1 + -1;
              cVar3 = ExclusiveMonitorsStatus();
            }
          } while (cVar3 != '\0');
          uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0xe80);
          if ((uVar5 & 1) != 0) {
            (*(code *)PTR__ZNK4Aska9Semaphore6SignalEv_02c96cd0)(param_1 + 0xe80);
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
  goto code_r0x0206ea60;
}

// ==== Aska::SoundManager::StopSound(Aska::SoundObject*, unsigned int)
// vaddr 0x1f6eb5c | ghidra 0x206eb5c | size 116 | symbol _ZN4Aska12SoundManager9StopSoundEPNS_11SoundObjectEj | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12SoundManager9StopSoundEPNS_11SoundObjectEj
               (long param_1,long param_2,undefined4 param_3)

{
  long lVar1;
  
  if (((param_2 != 0) && ((*(byte *)(param_1 + 0x1234) & 6) == 6)) &&
     (lVar1 = Aska::SoundServer::AcquireSoundCommand()(*(undefined8 *)(param_1 + 0xe8)), lVar1 != 0)) {
    *(undefined4 *)(param_2 + 0x1e4) = 4;
    *(undefined4 *)(lVar1 + 0x18) = 2;
    *(long *)(lVar1 + 0x20) = param_2;
    *(undefined4 *)(lVar1 + 0x28) = param_3;
    (*(code *)PTR__ZN4Aska12SoundManager15AddSoundCommandEPNS_12SoundCommandE_02cafe08)
              (param_1,lVar1);
    return;
  }
  return;
}

// ==== Aska::SoundManager::StopAllSound(unsigned int)
// vaddr 0x1f6ebd0 | ghidra 0x206ebd0 | size 100 | symbol _ZN4Aska12SoundManager12StopAllSoundEj | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12SoundManager12StopAllSoundEj(long param_1,undefined4 param_2)

{
  long lVar1;
  
  if (((~*(byte *)(param_1 + 0x1234) & 6) == 0) &&
     (lVar1 = Aska::SoundServer::AcquireSoundCommand()(*(undefined8 *)(param_1 + 0xe8)), lVar1 != 0)) {
    *(undefined8 *)(lVar1 + 0x20) = 0;
    *(undefined4 *)(lVar1 + 0x18) = 3;
    *(undefined4 *)(lVar1 + 0x28) = param_2;
    (*(code *)PTR__ZN4Aska12SoundManager15AddSoundCommandEPNS_12SoundCommandE_02cafe08)
              (param_1,lVar1);
    return;
  }
  return;
}

// ==== Aska::SoundManager::PauseSound(Aska::SoundObject*)
// vaddr 0x1f6ec34 | ghidra 0x206ec34 | size 108 | symbol _ZN4Aska12SoundManager10PauseSoundEPNS_11SoundObjectE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12SoundManager10PauseSoundEPNS_11SoundObjectE(long param_1,long param_2)

{
  long lVar1;
  
  if (((param_2 != 0) && ((*(byte *)(param_1 + 0x1234) & 6) == 6)) &&
     (lVar1 = Aska::SoundServer::AcquireSoundCommand()(*(undefined8 *)(param_1 + 0xe8)), lVar1 != 0)) {
    *(undefined4 *)(param_2 + 0x1e4) = 3;
    *(undefined4 *)(lVar1 + 0x18) = 4;
    *(long *)(lVar1 + 0x20) = param_2;
    (*(code *)PTR__ZN4Aska12SoundManager15AddSoundCommandEPNS_12SoundCommandE_02cafe08)
              (param_1,lVar1);
    return;
  }
  return;
}

// ==== Aska::SoundManager::ResumeSound(Aska::SoundObject*)
// vaddr 0x1f6eca0 | ghidra 0x206eca0 | size 108 | symbol _ZN4Aska12SoundManager11ResumeSoundEPNS_11SoundObjectE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12SoundManager11ResumeSoundEPNS_11SoundObjectE(long param_1,long param_2)

{
  long lVar1;
  
  if (((param_2 != 0) && ((*(byte *)(param_1 + 0x1234) & 6) == 6)) &&
     (lVar1 = Aska::SoundServer::AcquireSoundCommand()(*(undefined8 *)(param_1 + 0xe8)), lVar1 != 0)) {
    *(undefined4 *)(param_2 + 0x1e4) = 2;
    *(undefined4 *)(lVar1 + 0x18) = 5;
    *(long *)(lVar1 + 0x20) = param_2;
    (*(code *)PTR__ZN4Aska12SoundManager15AddSoundCommandEPNS_12SoundCommandE_02cafe08)
              (param_1,lVar1);
    return;
  }
  return;
}

// ==== Aska::SoundManager::PauseAllSound(unsigned int)
// vaddr 0x1f6ed0c | ghidra 0x206ed0c | size 112 | symbol _ZN4Aska12SoundManager13PauseAllSoundEj | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12SoundManager13PauseAllSoundEj(long param_1,undefined4 param_2)

{
  ulong uVar1;
  long lVar2;
  
  if ((((~*(byte *)(param_1 + 0x1234) & 6) == 0) &&
      (uVar1 = Aska::SoundManager::IncrementPauseAll()(param_1), (uVar1 & 1) != 0)) &&
     (lVar2 = Aska::SoundServer::AcquireSoundCommand()(*(undefined8 *)(param_1 + 0xe8)), lVar2 != 0)) {
    *(undefined8 *)(lVar2 + 0x20) = 0;
    *(undefined4 *)(lVar2 + 0x18) = 6;
    *(undefined4 *)(lVar2 + 0x28) = param_2;
    (*(code *)PTR__ZN4Aska12SoundManager15AddSoundCommandEPNS_12SoundCommandE_02cafe08)
              (param_1,lVar2);
    return;
  }
  return;
}

// ==== Aska::SoundManager::IncrementPauseAll()
// vaddr 0x1f6ed7c | ghidra 0x206ed7c | size 368 | symbol _ZN4Aska12SoundManager17IncrementPauseAllEv | lib libSOA-3.7.0.so | 2026-10-08
bool _ZN4Aska12SoundManager17IncrementPauseAllEv(long param_1)

{
  int *piVar1;
  int *piVar2;
  char cVar3;
  bool bVar4;
  ulong uVar5;
  int iVar6;
  
  piVar1 = (int *)(param_1 + 0x1080);
  iVar6 = 0;
  do {
    while (*piVar1 != -1) {
      ClearExclusiveLocal();
      bVar4 = 0x1fe < iVar6;
      iVar6 = iVar6 + 1;
      if (bVar4) {
        piVar2 = (int *)(param_1 + 0x1084);
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
              uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0x10c0);
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
                Aska::Semaphore::Wait() const(param_1 + 0x10c0);
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
                if (cVar3 == '\0') goto code_r0x0206eed4;
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
code_r0x0206eed4:
        do {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
          if (bVar4) {
            *piVar2 = *piVar2 + -1;
            cVar3 = ExclusiveMonitorsStatus();
          }
        } while (cVar3 != '\0');
        DataMemoryBarrier(2,3);
code_r0x0206edfc:
        *(int *)(param_1 + 0x10d8) = *(int *)(param_1 + 0x10d8) + 1;
        iVar6 = *(int *)(param_1 + 0x10d8);
        DataMemoryBarrier(2,3);
        *(undefined4 *)(param_1 + 0x1080) = 0xffffffff;
        DataMemoryBarrier(2,3);
        piVar1 = (int *)(param_1 + 0x1084);
        if (0x14 < *piVar1) {
          do {
            cVar3 = '\x01';
            bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
            if (bVar4) {
              *piVar1 = *piVar1 + -1;
              cVar3 = ExclusiveMonitorsStatus();
            }
          } while (cVar3 != '\0');
          uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0x10c0);
          if ((uVar5 & 1) != 0) {
            Aska::Semaphore::Signal() const(param_1 + 0x10c0);
          }
        }
        return iVar6 < 2;
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
  goto code_r0x0206edfc;
}

// ==== Aska::SoundManager::ResumeAll(bool)
// vaddr 0x1f6eeec | ghidra 0x206eeec | size 96 | symbol _ZN4Aska12SoundManager9ResumeAllEb | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12SoundManager9ResumeAllEb(long param_1,uint param_2)

{
  ulong uVar1;
  long lVar2;
  
  if ((((~*(byte *)(param_1 + 0x1234) & 6) == 0) &&
      (uVar1 = Aska::SoundManager::DecrementPauseAll(bool)(param_1,param_2 & 1), (uVar1 & 1) != 0)) &&
     (lVar2 = Aska::SoundServer::AcquireSoundCommand()(*(undefined8 *)(param_1 + 0xe8)), lVar2 != 0)) {
    *(undefined4 *)(lVar2 + 0x18) = 7;
    *(undefined8 *)(lVar2 + 0x20) = 0;
    (*(code *)PTR__ZN4Aska12SoundManager15AddSoundCommandEPNS_12SoundCommandE_02cafe08)
              (param_1,lVar2);
    return;
  }
  return;
}

// ==== Aska::SoundManager::DecrementPauseAll(bool)
// vaddr 0x1f6ef4c | ghidra 0x206ef4c | size 400 | symbol _ZN4Aska12SoundManager17DecrementPauseAllEb | lib libSOA-3.7.0.so | 2026-10-08
undefined4 _ZN4Aska12SoundManager17DecrementPauseAllEb(long param_1,uint param_2)

{
  int *piVar1;
  int *piVar2;
  char cVar3;
  bool bVar4;
  ulong uVar5;
  int iVar6;
  undefined4 uVar7;
  
  piVar1 = (int *)(param_1 + 0x1080);
  iVar6 = 0;
code_r0x0206ef6c:
  do {
    if (*piVar1 != -1) {
      ClearExclusiveLocal();
      bVar4 = iVar6 < 0x1ff;
      iVar6 = iVar6 + 1;
      if (bVar4) goto code_r0x0206ef6c;
      piVar2 = (int *)(param_1 + 0x1084);
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
            uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0x10c0);
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
              Aska::Semaphore::Wait() const(param_1 + 0x10c0);
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
              if (cVar3 == '\0') goto code_r0x0206f02c;
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
code_r0x0206f02c:
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
        if (bVar4) {
          *piVar2 = *piVar2 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
code_r0x0206f03c:
      DataMemoryBarrier(2,3);
      if ((param_2 & 1) == 0) {
        if ((*(int *)(param_1 + 0x10d8) < 1) ||
           (*(int *)(param_1 + 0x10d8) = *(int *)(param_1 + 0x10d8) + -1,
           0 < *(int *)(param_1 + 0x10d8))) {
          uVar7 = 0;
          goto code_r0x0206f078;
        }
      }
      else {
        *(undefined4 *)(param_1 + 0x10d8) = 0;
      }
      uVar7 = 1;
code_r0x0206f078:
      DataMemoryBarrier(2,3);
      *(undefined4 *)(param_1 + 0x1080) = 0xffffffff;
      DataMemoryBarrier(2,3);
      if (0x14 < *(int *)(param_1 + 0x1084)) {
        piVar1 = (int *)(param_1 + 0x1084);
        do {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar4) {
            *piVar1 = *piVar1 + -1;
            cVar3 = ExclusiveMonitorsStatus();
          }
        } while (cVar3 != '\0');
        uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0x10c0);
        if ((uVar5 & 1) != 0) {
          Aska::Semaphore::Signal() const(param_1 + 0x10c0);
        }
      }
      return uVar7;
    }
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar4) {
      *piVar1 = 0;
      cVar3 = ExclusiveMonitorsStatus();
    }
    if (cVar3 == '\0') goto code_r0x0206f03c;
  } while( true );
}

// ==== Aska::SoundManager::PushBGM(Aska::BGMControlObject*, unsigned int)
// vaddr 0x1f6f0dc | ghidra 0x206f0dc | size 116 | symbol _ZN4Aska12SoundManager7PushBGMEPNS_16BGMControlObjectEj | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska12SoundManager7PushBGMEPNS_16BGMControlObjectEj
          (long param_1,long param_2,undefined4 param_3)

{
  undefined8 uVar1;
  long lVar2;
  
  uVar1 = 0;
  if (((param_2 != 0) && ((*(byte *)(param_1 + 0x1234) & 6) == 6)) &&
     (lVar2 = Aska::SoundServer::AcquireSoundCommand()(*(undefined8 *)(param_1 + 0xe8)), uVar1 = 0, lVar2 != 0)) {
    *(undefined4 *)(param_2 + 0x1e4) = 4;
    *(undefined4 *)(lVar2 + 0x18) = 8;
    *(long *)(lVar2 + 0x20) = param_2;
    *(undefined4 *)(lVar2 + 0x28) = param_3;
    Aska::SoundManager::AddSoundCommand(Aska::SoundCommand*)(param_1,lVar2);
    uVar1 = 1;
  }
  return uVar1;
}

// ==== Aska::SoundManager::PopBGM(unsigned int, bool, float)
// vaddr 0x1f6f150 | ghidra 0x206f150 | size 260 | symbol _ZN4Aska12SoundManager6PopBGMEjbf | lib libSOA-3.7.0.so | 2026-10-08
long _ZN4Aska12SoundManager6PopBGMEjbf
               (undefined4 param_1,long param_2,undefined4 param_3,byte param_4)

{
  long lVar1;
  long lVar2;
  
  if ((~*(byte *)(param_2 + 0x1234) & 6) == 0) {
    lVar1 = Aska::SoundServer::AcquireSoundObject(unsigned int)(*(undefined8 *)(param_2 + 0xe8),2);
    if (lVar1 == 0) {
      return 0;
    }
    lVar2 = Aska::SoundServer::AcquireSoundHandle()(*(undefined8 *)(param_2 + 0xe8));
    if (lVar2 != 0) {
      *(long *)(lVar2 + 0x18) = lVar1;
      Aska::SoundManager::AddSoundHandle(Aska::SoundHandle*)(param_2,lVar2);
      lVar2 = Aska::SoundServer::AcquireSoundCommand()(*(undefined8 *)(param_2 + 0xe8));
      if (lVar2 != 0) {
        *(undefined4 *)(lVar1 + 0x228) = param_1;
        *(undefined4 *)(lVar1 + 0x1e4) = 1;
        *(byte *)(lVar1 + 0x22c) = param_4 & 1;
        *(undefined1 *)(lVar1 + 0x120) = 1;
        *(undefined4 *)(lVar2 + 0x18) = 9;
        *(long *)(lVar2 + 0x20) = lVar1;
        *(undefined4 *)(lVar2 + 0x28) = param_3;
        Aska::SoundManager::AddSoundCommand(Aska::SoundCommand*)(param_2,lVar2);
        return lVar1;
      }
      lVar2 = Aska::SoundManager::QuerySoundHandle(Aska::SoundObject*) const(param_2,lVar1);
      if (lVar2 == 0) {
        return 0;
      }
      Aska::SoundManager::RemoveSoundHandle(Aska::SoundHandle*)(param_2,lVar2);
      Aska::SoundServer::ReleaseSoundHandle(Aska::SoundHandle*)(*(undefined8 *)(param_2 + 0xe8),lVar2);
    }
    Aska::SoundServer::ReleaseSoundObject(Aska::SoundObject*)(*(undefined8 *)(param_2 + 0xe8),lVar1);
  }
  return 0;
}

// ==== Aska::SoundManager::DeleteAllPushPopBGMList()
// vaddr 0x1f6f254 | ghidra 0x206f254 | size 76 | symbol _ZN4Aska12SoundManager23DeleteAllPushPopBGMListEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12SoundManager23DeleteAllPushPopBGMListEv(long param_1)

{
  long lVar1;
  
  if (((~*(byte *)(param_1 + 0x1234) & 6) == 0) &&
     (lVar1 = Aska::SoundServer::AcquireSoundCommand()(*(undefined8 *)(param_1 + 0xe8)), lVar1 != 0)) {
    *(undefined4 *)(lVar1 + 0x18) = 10;
    (*(code *)PTR__ZN4Aska12SoundManager15AddSoundCommandEPNS_12SoundCommandE_02cafe08)
              (param_1,lVar1);
    return;
  }
  return;
}

// ==== Aska::SoundManager::CreateAuxiliaryEffector(unsigned int, unsigned int, Aska::ESound::EDspEffect, void const*)
// vaddr 0x1f6f2a0 | ghidra 0x206f2a0 | size 188 | symbol _ZN4Aska12SoundManager23CreateAuxiliaryEffectorEjjNS_6ESound10EDspEffectEPKv | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska12SoundManager23CreateAuxiliaryEffectorEjjNS_6ESound10EDspEffectEPKv
          (long param_1,undefined4 param_2,undefined4 param_3,int param_4,long param_5)

{
  int iVar1;
  long lVar2;
  undefined8 uVar3;
  
  if ((~*(byte *)(param_1 + 0x1234) & 6) == 0) {
    lVar2 = Aska::SoundServer::AcquireSoundCommand()(*(undefined8 *)(param_1 + 0xe8));
    uVar3 = 0;
    if (lVar2 != 0) {
      *(undefined8 *)(lVar2 + 0x20) = 0;
      *(undefined4 *)(lVar2 + 0x28) = param_2;
      *(undefined4 *)(lVar2 + 0x2c) = param_3;
      *(undefined4 *)(lVar2 + 0x18) = 0xb;
      *(int *)(lVar2 + 0x30) = param_4;
      if ((param_4 == 0) || (param_5 == 0)) {
        *(undefined4 *)(lVar2 + 0x34) = 0;
      }
      else {
        iVar1 = Aska::SoundUtility::GetDspEffectParamSize(Aska::ESound::EDspEffect)(param_4);
        *(int *)(lVar2 + 0x34) = iVar1;
        if (iVar1 != 0) {
          memcpy(lVar2 + 0x38,param_5,iVar1);
        }
      }
      Aska::SoundManager::AddSoundCommand(Aska::SoundCommand*)(param_1,lVar2);
      uVar3 = 1;
    }
  }
  else {
    uVar3 = 0;
  }
  return uVar3;
}

// ==== Aska::SoundManager::DeleteAuxiliaryEffector(unsigned int)
// vaddr 0x1f6f35c | ghidra 0x206f35c | size 104 | symbol _ZN4Aska12SoundManager23DeleteAuxiliaryEffectorEj | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska12SoundManager23DeleteAuxiliaryEffectorEj(long param_1,undefined4 param_2)

{
  long lVar1;
  undefined8 uVar2;
  
  if ((~*(byte *)(param_1 + 0x1234) & 6) == 0) {
    lVar1 = Aska::SoundServer::AcquireSoundCommand()(*(undefined8 *)(param_1 + 0xe8));
    uVar2 = 0;
    if (lVar1 != 0) {
      *(undefined8 *)(lVar1 + 0x20) = 0;
      *(undefined4 *)(lVar1 + 0x18) = 0xc;
      *(undefined4 *)(lVar1 + 0x28) = param_2;
      Aska::SoundManager::AddSoundCommand(Aska::SoundCommand*)(param_1,lVar1);
      uVar2 = 1;
    }
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

// ==== Aska::SoundManager::InstallDspEffect(unsigned int, unsigned int, Aska::ESound::EDspEffect, void const*)
// vaddr 0x1f6f3c4 | ghidra 0x206f3c4 | size 188 | symbol _ZN4Aska12SoundManager16InstallDspEffectEjjNS_6ESound10EDspEffectEPKv | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska12SoundManager16InstallDspEffectEjjNS_6ESound10EDspEffectEPKv
          (long param_1,undefined4 param_2,undefined4 param_3,int param_4,long param_5)

{
  int iVar1;
  long lVar2;
  undefined8 uVar3;
  
  if ((~*(byte *)(param_1 + 0x1234) & 6) == 0) {
    lVar2 = Aska::SoundServer::AcquireSoundCommand()(*(undefined8 *)(param_1 + 0xe8));
    uVar3 = 0;
    if (lVar2 != 0) {
      *(undefined8 *)(lVar2 + 0x20) = 0;
      *(undefined4 *)(lVar2 + 0x28) = param_2;
      *(undefined4 *)(lVar2 + 0x2c) = param_3;
      *(undefined4 *)(lVar2 + 0x18) = 0xd;
      *(int *)(lVar2 + 0x30) = param_4;
      if ((param_4 == 0) || (param_5 == 0)) {
        *(undefined4 *)(lVar2 + 0x34) = 0;
      }
      else {
        iVar1 = Aska::SoundUtility::GetDspEffectParamSize(Aska::ESound::EDspEffect)(param_4);
        *(int *)(lVar2 + 0x34) = iVar1;
        if (iVar1 != 0) {
          memcpy(lVar2 + 0x38,param_5,iVar1);
        }
      }
      Aska::SoundManager::AddSoundCommand(Aska::SoundCommand*)(param_1,lVar2);
      uVar3 = 1;
    }
  }
  else {
    uVar3 = 0;
  }
  return uVar3;
}

// ==== Aska::SoundManager::UninstallDspEffect(unsigned int, unsigned int)
// vaddr 0x1f6f480 | ghidra 0x206f480 | size 108 | symbol _ZN4Aska12SoundManager18UninstallDspEffectEjj | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska12SoundManager18UninstallDspEffectEjj(long param_1,undefined4 param_2,undefined4 param_3)

{
  long lVar1;
  undefined8 uVar2;
  
  if ((~*(byte *)(param_1 + 0x1234) & 6) == 0) {
    lVar1 = Aska::SoundServer::AcquireSoundCommand()(*(undefined8 *)(param_1 + 0xe8));
    uVar2 = 0;
    if (lVar1 != 0) {
      *(undefined8 *)(lVar1 + 0x20) = 0;
      *(undefined4 *)(lVar1 + 0x18) = 0xe;
      *(undefined4 *)(lVar1 + 0x28) = param_2;
      *(undefined4 *)(lVar1 + 0x2c) = param_3;
      Aska::SoundManager::AddSoundCommand(Aska::SoundCommand*)(param_1,lVar1);
      uVar2 = 1;
    }
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

// ==== Aska::SoundManager::ConnectAuxiliaryEffector(unsigned int, unsigned int)
// vaddr 0x1f6f4ec | ghidra 0x206f4ec | size 112 | symbol _ZN4Aska12SoundManager24ConnectAuxiliaryEffectorEjj | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska12SoundManager24ConnectAuxiliaryEffectorEjj
          (long param_1,undefined4 param_2,undefined4 param_3)

{
  long lVar1;
  undefined8 uVar2;
  
  if ((~*(byte *)(param_1 + 0x1234) & 6) == 0) {
    lVar1 = Aska::SoundServer::AcquireSoundCommand()(*(undefined8 *)(param_1 + 0xe8));
    uVar2 = 0;
    if (lVar1 != 0) {
      *(undefined8 *)(lVar1 + 0x20) = 0;
      *(undefined4 *)(lVar1 + 0x28) = param_2;
      *(undefined4 *)(lVar1 + 0x2c) = param_3;
      *(undefined4 *)(lVar1 + 0x18) = 0xf;
      *(undefined4 *)(lVar1 + 0x30) = 0;
      Aska::SoundManager::AddSoundCommand(Aska::SoundCommand*)(param_1,lVar1);
      uVar2 = 1;
    }
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

// ==== Aska::SoundManager::DisconnectAuxiliaryEffector(unsigned int)
// vaddr 0x1f6f55c | ghidra 0x206f55c | size 104 | symbol _ZN4Aska12SoundManager27DisconnectAuxiliaryEffectorEj | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska12SoundManager27DisconnectAuxiliaryEffectorEj(long param_1,undefined4 param_2)

{
  long lVar1;
  undefined8 uVar2;
  
  if ((~*(byte *)(param_1 + 0x1234) & 6) == 0) {
    lVar1 = Aska::SoundServer::AcquireSoundCommand()(*(undefined8 *)(param_1 + 0xe8));
    uVar2 = 0;
    if (lVar1 != 0) {
      *(undefined8 *)(lVar1 + 0x20) = 0;
      *(undefined4 *)(lVar1 + 0x18) = 0x10;
      *(undefined4 *)(lVar1 + 0x28) = param_2;
      Aska::SoundManager::AddSoundCommand(Aska::SoundCommand*)(param_1,lVar1);
      uVar2 = 1;
    }
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

// ==== Aska::SoundManager::IsInstalledDspEffect(unsigned int, unsigned int) const
// vaddr 0x1f6f5c4 | ghidra 0x206f5c4 | size 188 | symbol _ZNK4Aska12SoundManager20IsInstalledDspEffectEjj | lib libSOA-3.7.0.so | 2026-10-08
bool _ZNK4Aska12SoundManager20IsInstalledDspEffectEjj(long param_1,uint param_2,int param_3)

{
  long lVar1;
  
  if ((~*(byte *)(param_1 + 0x1234) & 6) != 0) {
    return false;
  }
  if (param_2 < 5) {
    lVar1 = Aska::AudioMixer::GetBusChannel(unsigned int)(*(undefined8 *)(param_1 + 0x6c8));
    if (lVar1 == 0) {
      return false;
    }
    lVar1 = *(long *)(lVar1 + 0x20);
    if (lVar1 == 0) {
      return false;
    }
  }
  else {
    param_2 = param_2 - 5;
    if (2 < param_2) {
      return false;
    }
    if (*(int *)(param_1 + (ulong)param_2 * 0x118 + 0x6e8) == 0) {
      return false;
    }
    lVar1 = *(long *)(param_1 + (ulong)param_2 * 0x118 + 0x728);
    if (lVar1 == 0) {
      return false;
    }
  }
  return *(long *)(lVar1 + (long)param_3 * 8 + 0x30) != 0;
}

// ==== Aska::SoundManager::QueryAuxiliaryDevice(unsigned int) const
// vaddr 0x1f6f680 | ghidra 0x206f680 | size 48 | symbol _ZNK4Aska12SoundManager20QueryAuxiliaryDeviceEj | lib libSOA-3.7.0.so | 2026-10-08
long _ZNK4Aska12SoundManager20QueryAuxiliaryDeviceEj(long param_1,int param_2)

{
  long lVar1;
  
  if (2 < param_2 - 5U) {
    return 0;
  }
  param_1 = param_1 + (ulong)(param_2 - 5U) * 0x118;
  lVar1 = 0;
  if (*(int *)(param_1 + 0x6e8) != 0) {
    lVar1 = param_1 + 0x6d0;
  }
  return lVar1;
}

// ==== Aska::SoundManager::IsConnectedAuxiliaryEffector(unsigned int, unsigned int*, unsigned int*)
// vaddr 0x1f6f6b0 | ghidra 0x206f6b0 | size 92 | symbol _ZN4Aska12SoundManager28IsConnectedAuxiliaryEffectorEjPjS1_ | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska12SoundManager28IsConnectedAuxiliaryEffectorEjPjS1_
          (long param_1,int param_2,undefined4 *param_3,undefined8 param_4)

{
  uint uVar1;
  undefined8 uVar2;
  
  if ((~*(byte *)(param_1 + 0x1234) & 6) == 0) {
    uVar1 = param_2 - 5;
    if ((uVar1 < 3) && (*(int *)(param_1 + (ulong)uVar1 * 0x118 + 0x6e8) != 0)) {
      uVar2 = (*(code *)PTR__ZN4Aska15AuxiliaryDevice17IsConnectedDeviceEPjS1__02c92840)
                        (param_1 + (ulong)uVar1 * 0x118 + 0x6d0,param_3,param_4);
      return uVar2;
    }
    *param_3 = 0xffffffff;
  }
  return 0;
}

// ==== Aska::SoundManager::GetInsertionEffector(unsigned int)
// vaddr 0x1f6f70c | ghidra 0x206f70c | size 60 | symbol _ZN4Aska12SoundManager20GetInsertionEffectorEj | lib libSOA-3.7.0.so | 2026-10-08
long _ZN4Aska12SoundManager20GetInsertionEffectorEj(long param_1)

{
  long lVar1;
  long lVar2;
  
  if ((~*(byte *)(param_1 + 0x1234) & 6) == 0) {
    lVar2 = Aska::AudioMixer::GetBusChannel(unsigned int)(*(undefined8 *)(param_1 + 0x6c8));
    lVar1 = 0;
    if (lVar2 != 0) {
      lVar1 = lVar2 + 0x18;
    }
    return lVar1;
  }
  return 0;
}

// ==== Aska::SoundManager::GetAuxiliaryEffector(unsigned int)
// vaddr 0x1f6f748 | ghidra 0x206f748 | size 68 | symbol _ZN4Aska12SoundManager20GetAuxiliaryEffectorEj | lib libSOA-3.7.0.so | 2026-10-08
long _ZN4Aska12SoundManager20GetAuxiliaryEffectorEj(long param_1,int param_2)

{
  long lVar1;
  
  if (((~*(byte *)(param_1 + 0x1234) & 6) == 0) && (param_2 - 5U < 3)) {
    param_1 = param_1 + (ulong)(param_2 - 5U) * 0x118;
    lVar1 = 0;
    if (*(int *)(param_1 + 0x6e8) != 0) {
      lVar1 = param_1 + 0x720;
    }
    return lVar1;
  }
  return 0;
}

// ==== Aska::SoundManager::RemoveSoundCommand(Aska::SoundCommand*)
// vaddr 0x1f6f78c | ghidra 0x206f78c | size 392 | symbol _ZN4Aska12SoundManager18RemoveSoundCommandEPNS_12SoundCommandE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12SoundManager18RemoveSoundCommandEPNS_12SoundCommandE(long param_1,long param_2)

{
  int *piVar1;
  int *piVar2;
  char cVar3;
  bool bVar4;
  ulong uVar5;
  int iVar6;
  long lVar7;
  long lVar8;
  
  piVar1 = (int *)(param_1 + 0xe40);
  iVar6 = 0;
  do {
    while (*piVar1 == -1) {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = 0;
        cVar3 = ExclusiveMonitorsStatus();
      }
      if (cVar3 == '\0') goto code_r0x0206f870;
    }
    ClearExclusiveLocal();
    bVar4 = iVar6 < 0x1ff;
    iVar6 = iVar6 + 1;
  } while (bVar4);
  piVar2 = (int *)(param_1 + 0xe44);
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
        uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0xe80);
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
          Aska::Semaphore::Wait() const(param_1 + 0xe80);
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
          if (cVar3 == '\0') goto code_r0x0206f860;
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
code_r0x0206f860:
  do {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar4) {
      *piVar2 = *piVar2 + -1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
code_r0x0206f870:
  DataMemoryBarrier(2,3);
  if ((param_1 + 0xa20 != param_2) && (param_2 != 0)) {
    lVar7 = *(long *)(param_2 + 8);
    lVar8 = *(long *)(param_2 + 0x10);
    if (lVar7 != 0) {
      *(long *)(lVar7 + 0x10) = lVar8;
    }
    if (lVar8 != 0) {
      *(long *)(lVar8 + 8) = lVar7;
    }
    if (0 < *(int *)(param_1 + 0xac8)) {
      *(int *)(param_1 + 0xac8) = *(int *)(param_1 + 0xac8) + -1;
    }
    *(long *)(param_2 + 8) = 0;
    *(undefined8 *)(param_2 + 0x10) = 0;
  }
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_1 + 0xe40) = 0xffffffff;
  DataMemoryBarrier(2,3);
  if (0x14 < *(int *)(param_1 + 0xe44)) {
    piVar1 = (int *)(param_1 + 0xe44);
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
    uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0xe80);
    if ((uVar5 & 1) != 0) {
      (*(code *)PTR__ZNK4Aska9Semaphore6SignalEv_02c96cd0)(param_1 + 0xe80);
      return;
    }
  }
  return;
}

// ==== Aska::SoundManager::InsertSoundCommand(Aska::SoundCommand*, Aska::SoundCommand*)
// vaddr 0x1f6f914 | ghidra 0x206f914 | size 384 | symbol _ZN4Aska12SoundManager18InsertSoundCommandEPNS_12SoundCommandES2_ | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12SoundManager18InsertSoundCommandEPNS_12SoundCommandES2_
               (long param_1,long param_2,long param_3)

{
  int *piVar1;
  int *piVar2;
  char cVar3;
  bool bVar4;
  ulong uVar5;
  int iVar6;
  long lVar7;
  
  piVar1 = (int *)(param_1 + 0xe40);
  iVar6 = 0;
  do {
    while (*piVar1 != -1) {
      ClearExclusiveLocal();
      bVar4 = 0x1fe < iVar6;
      iVar6 = iVar6 + 1;
      if (bVar4) {
        piVar2 = (int *)(param_1 + 0xe44);
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
              uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0xe80);
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
                Aska::Semaphore::Wait() const(param_1 + 0xe80);
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
                if (cVar3 == '\0') goto code_r0x0206fa7c;
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
code_r0x0206fa7c:
        do {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
          if (bVar4) {
            *piVar2 = *piVar2 + -1;
            cVar3 = ExclusiveMonitorsStatus();
          }
        } while (cVar3 != '\0');
        DataMemoryBarrier(2,3);
code_r0x0206f994:
        lVar7 = *(long *)(param_2 + 0x10);
        *(long *)(param_3 + 8) = param_2;
        *(long *)(param_3 + 0x10) = lVar7;
        *(long *)(lVar7 + 8) = param_3;
        *(long *)(param_2 + 0x10) = param_3;
        *(int *)(param_1 + 0xac8) = *(int *)(param_1 + 0xac8) + 1;
        DataMemoryBarrier(2,3);
        *(undefined4 *)(param_1 + 0xe40) = 0xffffffff;
        DataMemoryBarrier(2,3);
        piVar1 = (int *)(param_1 + 0xe44);
        if (0x14 < *piVar1) {
          do {
            cVar3 = '\x01';
            bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
            if (bVar4) {
              *piVar1 = *piVar1 + -1;
              cVar3 = ExclusiveMonitorsStatus();
            }
          } while (cVar3 != '\0');
          uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0xe80);
          if ((uVar5 & 1) != 0) {
            (*(code *)PTR__ZNK4Aska9Semaphore6SignalEv_02c96cd0)(param_1 + 0xe80);
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
  goto code_r0x0206f994;
}

// ==== Aska::SoundManager::AcquireAuxiliaryDevice(unsigned int)
// vaddr 0x1f6fad4 | ghidra 0x206fad4 | size 72 | symbol _ZN4Aska12SoundManager22AcquireAuxiliaryDeviceEj | lib libSOA-3.7.0.so | 2026-10-08
long _ZN4Aska12SoundManager22AcquireAuxiliaryDeviceEj(long param_1,int param_2)

{
  long lVar1;
  ulong uVar2;
  
  if (2 < param_2 - 5U) {
    return 0;
  }
  param_1 = param_1 + (ulong)(param_2 - 5U) * 0x118;
  *(int *)(param_1 + 0x7e0) = param_2;
  lVar1 = param_1 + 0x6d0;
  uVar2 = (**(code **)(*(long *)(param_1 + 0x6d0) + 0x58))(lVar1);
  if ((uVar2 & 1) == 0) {
    lVar1 = 0;
  }
  return lVar1;
}

// ==== Aska::SoundManager::ReleaseAuxiliaryDevice(unsigned int)
// vaddr 0x1f6fb1c | ghidra 0x206fb1c | size 72 | symbol _ZN4Aska12SoundManager22ReleaseAuxiliaryDeviceEj | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12SoundManager22ReleaseAuxiliaryDeviceEj(long param_1,int param_2)

{
  if (param_2 - 5U < 3) {
    param_1 = param_1 + (ulong)(param_2 - 5U) * 0x118;
    if (*(int *)(param_1 + 0x6e8) != 0) {
      (**(code **)(*(long *)(param_1 + 0x6d0) + 0x60))((long *)(param_1 + 0x6d0));
      *(undefined4 *)(param_1 + 0x7e0) = 0;
    }
  }
  return;
}

// ==== Aska::SoundManager::QueryAudioInterface(Aska::AudioConnector*) const
// vaddr 0x1f6fb64 | ghidra 0x206fb64 | size 388 | symbol _ZNK4Aska12SoundManager19QueryAudioInterfaceEPNS_14AudioConnectorE | lib libSOA-3.7.0.so | 2026-10-08
long _ZNK4Aska12SoundManager19QueryAudioInterfaceEPNS_14AudioConnectorE(long param_1,long param_2)

{
  int *piVar1;
  int *piVar2;
  char cVar3;
  bool bVar4;
  ulong uVar5;
  int iVar6;
  long lVar7;
  
  piVar1 = (int *)(param_1 + 0xed0);
  iVar6 = 0;
  do {
    while (*piVar1 == -1) {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = 0;
        cVar3 = ExclusiveMonitorsStatus();
      }
      if (cVar3 == '\0') goto code_r0x0206fc48;
    }
    ClearExclusiveLocal();
    bVar4 = iVar6 < 0x1ff;
    iVar6 = iVar6 + 1;
  } while (bVar4);
  piVar2 = (int *)(param_1 + 0xed4);
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
        uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0xf10);
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
          Aska::Semaphore::Wait() const(param_1 + 0xf10);
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
          if (cVar3 == '\0') goto code_r0x0206fc38;
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
code_r0x0206fc38:
  do {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar4) {
      *piVar2 = *piVar2 + -1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
code_r0x0206fc48:
  DataMemoryBarrier(2,3);
  for (lVar7 = *(long *)(param_1 + 0xbe0); param_1 + 0xbd0 != lVar7; lVar7 = *(long *)(lVar7 + 0x10)
      ) {
    if ((*(long *)(lVar7 + 0x18) == param_2) || (*(long *)(lVar7 + 0x20) == param_2))
    goto code_r0x0206fc8c;
  }
  lVar7 = 0;
code_r0x0206fc8c:
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_1 + 0xed0) = 0xffffffff;
  DataMemoryBarrier(2,3);
  if (0x14 < *(int *)(param_1 + 0xed4)) {
    piVar1 = (int *)(param_1 + 0xed4);
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
    uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0xf10);
    if ((uVar5 & 1) != 0) {
      Aska::Semaphore::Signal() const(param_1 + 0xf10);
    }
  }
  return lVar7;
}

// ==== Aska::SoundManager::NoneCommandList(Aska::SoundObject*)
// vaddr 0x1f6fce8 | ghidra 0x206fce8 | size 400 | symbol _ZN4Aska12SoundManager15NoneCommandListEPNS_11SoundObjectE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12SoundManager15NoneCommandListEPNS_11SoundObjectE(long param_1,long param_2)

{
  int *piVar1;
  int *piVar2;
  char cVar3;
  bool bVar4;
  ulong uVar5;
  int iVar6;
  long lVar7;
  
  if ((~*(byte *)(param_1 + 0x1234) & 6) == 0) {
    piVar1 = (int *)(param_1 + 0xe40);
    iVar6 = 0;
    do {
      while (*piVar1 == -1) {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
        if (bVar4) {
          *piVar1 = 0;
          cVar3 = ExclusiveMonitorsStatus();
        }
        if (cVar3 == '\0') goto code_r0x0206fddc;
      }
      ClearExclusiveLocal();
      bVar4 = iVar6 < 0x1ff;
      iVar6 = iVar6 + 1;
    } while (bVar4);
    piVar2 = (int *)(param_1 + 0xe44);
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
          uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0xe80);
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
            Aska::Semaphore::Wait() const(param_1 + 0xe80);
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
            if (cVar3 == '\0') goto code_r0x0206fdcc;
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
code_r0x0206fdcc:
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
      if (bVar4) {
        *piVar2 = *piVar2 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
code_r0x0206fddc:
    DataMemoryBarrier(2,3);
    for (lVar7 = *(long *)(param_1 + 0xa30); param_1 + 0xa20 != lVar7;
        lVar7 = *(long *)(lVar7 + 0x10)) {
      if (*(long *)(lVar7 + 0x20) == param_2) {
        *(undefined4 *)(lVar7 + 0x18) = 0;
      }
    }
    DataMemoryBarrier(2,3);
    *(undefined4 *)(param_1 + 0xe40) = 0xffffffff;
    DataMemoryBarrier(2,3);
    if (0x14 < *(int *)(param_1 + 0xe44)) {
      piVar1 = (int *)(param_1 + 0xe44);
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
        if (bVar4) {
          *piVar1 = *piVar1 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0xe80);
      if ((uVar5 & 1) != 0) {
        (*(code *)PTR__ZNK4Aska9Semaphore6SignalEv_02c96cd0)(param_1 + 0xe80);
        return;
      }
    }
  }
  return;
}

// ==== Aska::SoundManager::DeleteCommandList(Aska::SoundObject*)
// vaddr 0x1f6fe78 | ghidra 0x206fe78 | size 416 | symbol _ZN4Aska12SoundManager17DeleteCommandListEPNS_11SoundObjectE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12SoundManager17DeleteCommandListEPNS_11SoundObjectE(long param_1,long param_2)

{
  int *piVar1;
  int *piVar2;
  char cVar3;
  bool bVar4;
  long lVar5;
  ulong uVar6;
  int iVar7;
  long lVar8;
  
  if ((~*(byte *)(param_1 + 0x1234) & 6) != 0) {
    return;
  }
  piVar1 = (int *)(param_1 + 0xe40);
  iVar7 = 0;
  do {
    while (*piVar1 == -1) {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = 0;
        cVar3 = ExclusiveMonitorsStatus();
      }
      if (cVar3 == '\0') goto code_r0x0206ff6c;
    }
    ClearExclusiveLocal();
    bVar4 = iVar7 < 0x1ff;
    iVar7 = iVar7 + 1;
  } while (bVar4);
  piVar2 = (int *)(param_1 + 0xe44);
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
        uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0xe80);
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
          Aska::Semaphore::Wait() const(param_1 + 0xe80);
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
          if (cVar3 == '\0') goto code_r0x0206ff5c;
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
code_r0x0206ff5c:
  do {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar4) {
      *piVar2 = *piVar2 + -1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
code_r0x0206ff6c:
  DataMemoryBarrier(2,3);
  lVar8 = *(long *)(param_1 + 0xa30);
  while (lVar5 = lVar8, param_1 + 0xa20 != lVar5) {
    lVar8 = *(long *)(lVar5 + 0x10);
    if (*(long *)(lVar5 + 0x20) == param_2) {
      Aska::SoundManager::RemoveSoundCommand(Aska::SoundCommand*)(param_1,lVar5);
      Aska::SoundServer::ReleaseSoundCommand(Aska::SoundCommand*)(*(undefined8 *)(param_1 + 0xe8),lVar5);
    }
  }
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_1 + 0xe40) = 0xffffffff;
  DataMemoryBarrier(2,3);
  if (*(int *)(param_1 + 0xe44) < 0x15) {
    return;
  }
  piVar1 = (int *)(param_1 + 0xe44);
  do {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar4) {
      *piVar1 = *piVar1 + -1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
  uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0xe80);
  if ((uVar6 & 1) == 0) {
    return;
  }
  (*(code *)PTR__ZNK4Aska9Semaphore6SignalEv_02c96cd0)(param_1 + 0xe80);
  return;
}

// ==== Aska::SoundManager::WaitForCommandList()
// vaddr 0x1f70018 | ghidra 0x2070018 | size 364 | symbol _ZN4Aska12SoundManager18WaitForCommandListEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12SoundManager18WaitForCommandListEv(long param_1)

{
  int *piVar1;
  int *piVar2;
  long lVar3;
  char cVar4;
  bool bVar5;
  ulong uVar6;
  int iVar7;
  long lVar8;
  
  if ((~*(byte *)(param_1 + 0x1234) & 6) != 0) {
    return;
  }
  piVar1 = (int *)(param_1 + 0xe40);
  piVar2 = (int *)(param_1 + 0xe44);
  lVar3 = param_1 + 0xe80;
  iVar7 = 0;
code_r0x02070110:
  do {
    if (*piVar1 != -1) goto code_r0x02070100;
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar5) {
      *piVar1 = 0;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
  goto code_r0x02070124;
code_r0x02070100:
  ClearExclusiveLocal();
  bVar5 = 0x1fe < iVar7;
  iVar7 = iVar7 + 1;
  if (bVar5) {
    do {
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
      if (bVar5) {
        *piVar2 = *piVar2 + 1;
        cVar4 = ExclusiveMonitorsStatus();
      }
    } while (cVar4 != '\0');
    do {
      if (*piVar1 != -1) {
        do {
          ClearExclusiveLocal();
          uVar6 = Aska::Semaphore::IsReady() const(lVar3);
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
            Aska::Semaphore::Wait() const(lVar3);
          }
          do {
            cVar4 = '\x01';
            bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
            if (bVar5) {
              *piVar2 = *piVar2 + 1;
              cVar4 = ExclusiveMonitorsStatus();
            }
          } while (cVar4 != '\0');
          while (*piVar1 == -1) {
            cVar4 = '\x01';
            bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
            if (bVar5) {
              *piVar1 = 0;
              cVar4 = ExclusiveMonitorsStatus();
            }
            if (cVar4 == '\0') goto code_r0x020700ec;
          }
        } while( true );
      }
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar5) {
        *piVar1 = 0;
        cVar4 = ExclusiveMonitorsStatus();
      }
    } while (cVar4 != '\0');
code_r0x020700ec:
    do {
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
      if (bVar5) {
        *piVar2 = *piVar2 + -1;
        cVar4 = ExclusiveMonitorsStatus();
      }
    } while (cVar4 != '\0');
code_r0x02070124:
    DataMemoryBarrier(2,3);
    lVar8 = *(long *)(param_1 + 0xa30);
    DataMemoryBarrier(2,3);
    *(undefined4 *)(param_1 + 0xe40) = 0xffffffff;
    DataMemoryBarrier(2,3);
    if (0x14 < *(int *)(param_1 + 0xe44)) {
      do {
        cVar4 = '\x01';
        bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
        if (bVar5) {
          *piVar2 = *piVar2 + -1;
          cVar4 = ExclusiveMonitorsStatus();
        }
      } while (cVar4 != '\0');
      uVar6 = Aska::Semaphore::IsReady() const(lVar3);
      if ((uVar6 & 1) != 0) {
        Aska::Semaphore::Signal() const(lVar3);
      }
    }
    if (param_1 + 0xa20 == lVar8) {
      return;
    }
    Aska::Thread::Sleep(unsigned int)(2);
    iVar7 = 0;
  }
  goto code_r0x02070110;
}

// ==== Aska::SoundManager::IsOtherAudioPlaying() const
// vaddr 0x1f702c4 | ghidra 0x20702c4 | size 8 | symbol _ZNK4Aska12SoundManager19IsOtherAudioPlayingEv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK4Aska12SoundManager19IsOtherAudioPlayingEv(void)

{
  return 0;
}

// ==== Aska::SoundManager::SoundSignalHandler()
// vaddr 0x1f702cc | ghidra 0x20702cc | size 4 | symbol _ZN4Aska12SoundManager18SoundSignalHandlerEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12SoundManager18SoundSignalHandlerEv(void)

{
  return;
}

// ==== Aska::SoundManager::AdxRegisterAcf(void*, unsigned int)
// vaddr 0x1f702d0 | ghidra 0x20702d0 | size 4 | symbol _ZN4Aska12SoundManager14AdxRegisterAcfEPvj | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12SoundManager14AdxRegisterAcfEPvj(void)

{
  return;
}

// ==== Aska::SoundManager::AdxUnregisterAcf()
// vaddr 0x1f702d4 | ghidra 0x20702d4 | size 4 | symbol _ZN4Aska12SoundManager16AdxUnregisterAcfEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12SoundManager16AdxUnregisterAcfEv(void)

{
  return;
}

// ==== Aska::SoundManager::AdxIsRegisteredAcf() const
// vaddr 0x1f702d8 | ghidra 0x20702d8 | size 8 | symbol _ZNK4Aska12SoundManager18AdxIsRegisteredAcfEv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK4Aska12SoundManager18AdxIsRegisteredAcfEv(void)

{
  return 0;
}

// ==== Aska::SoundManager::AdxAttachDspBusSetting(char const*)
// vaddr 0x1f702e0 | ghidra 0x20702e0 | size 4 | symbol _ZN4Aska12SoundManager22AdxAttachDspBusSettingEPKc | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12SoundManager22AdxAttachDspBusSettingEPKc(void)

{
  return;
}

// ==== Aska::SoundManager::AdxDetachDspBusSetting()
// vaddr 0x1f702e4 | ghidra 0x20702e4 | size 4 | symbol _ZN4Aska12SoundManager22AdxDetachDspBusSettingEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12SoundManager22AdxDetachDspBusSettingEv(void)

{
  return;
}

// ==== Aska::SoundManager::AdxSetBusVolume(int, float)
// vaddr 0x1f702e8 | ghidra 0x20702e8 | size 4 | symbol _ZN4Aska12SoundManager15AdxSetBusVolumeEif | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12SoundManager15AdxSetBusVolumeEif(void)

{
  return;
}

// ==== Aska::SoundManager::AdxSetBusVolumeDB(int, float)
// vaddr 0x1f702ec | ghidra 0x20702ec | size 4 | symbol _ZN4Aska12SoundManager17AdxSetBusVolumeDBEif | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12SoundManager17AdxSetBusVolumeDBEif(void)

{
  return;
}

// ==== Aska::SoundManager::AdxSetBusMatrix(int, int, int, float const*)
// vaddr 0x1f702f0 | ghidra 0x20702f0 | size 4 | symbol _ZN4Aska12SoundManager15AdxSetBusMatrixEiiiPKf | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12SoundManager15AdxSetBusMatrixEiiiPKf(void)

{
  return;
}

// ==== Aska::SoundManager::AdxSetBusSendLevel(int, int, float)
// vaddr 0x1f702f4 | ghidra 0x20702f4 | size 4 | symbol _ZN4Aska12SoundManager18AdxSetBusSendLevelEiif | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12SoundManager18AdxSetBusSendLevelEiif(void)

{
  return;
}

// ==== Aska::SoundManager::AdxSetDspParameter(int, int, void const*)
// vaddr 0x1f702f8 | ghidra 0x20702f8 | size 4 | symbol _ZN4Aska12SoundManager18AdxSetDspParameterEiiPKv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12SoundManager18AdxSetDspParameterEiiPKv(void)

{
  return;
}

// ==== Aska::SoundManager::AdxSetDspBypass(int, int, bool)
// vaddr 0x1f702fc | ghidra 0x20702fc | size 4 | symbol _ZN4Aska12SoundManager15AdxSetDspBypassEiib | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12SoundManager15AdxSetDspBypassEiib(void)

{
  return;
}

// ==== Aska::SoundManagerThread::~SoundManagerThread()
// vaddr 0x1f70300 | ghidra 0x2070300 | size 24 | symbol _ZN4Aska18SoundManagerThreadD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska18SoundManagerThreadD0Ev(undefined8 param_1)

{
  Aska::Thread::~Thread()();
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::SoundManager::GetClassID(int) const
// vaddr 0x1f70318 | ghidra 0x2070318 | size 72 | symbol _ZNK4Aska12SoundManager10GetClassIDEi | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK4Aska12SoundManager10GetClassIDEi(undefined8 param_1,int param_2)

{
  undefined8 uVar1;
  undefined8 uVar2;
  
  if (param_2 != 0) {
    uVar2 = 0xf000f001;
    if (param_2 != 2) {
      uVar2 = 0xf000;
    }
    uVar1 = 0xf000f001f002;
    if (param_2 != 1) {
      uVar1 = uVar2;
    }
    return uVar1;
  }
  return 0xf000f001f002f211;
}

// ==== Aska::SoundManager::GetDefaultLevel() const
// vaddr 0x1f70360 | ghidra 0x2070360 | size 8 | symbol _ZNK4Aska12SoundManager15GetDefaultLevelEv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK4Aska12SoundManager15GetDefaultLevelEv(void)

{
  return 0x4000;
}

// ==== Aska::SoundHandle::~SoundHandle()
// vaddr 0x1f70918 | ghidra 0x2070918 | size 4 | symbol _ZN4Aska11SoundHandleD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska11SoundHandleD0Ev(void)

{
  (*(code *)PTR__ZdlPv_02ca4758)();
  return;
}

// ==== Aska::SoundCommand::~SoundCommand()
// vaddr 0x1f70944 | ghidra 0x2070944 | size 4 | symbol _ZN4Aska12SoundCommandD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12SoundCommandD0Ev(void)

{
  (*(code *)PTR__ZdlPv_02ca4758)();
  return;
}

// ==== Aska::SoundMemory::SetResourceMemoryMgr(Aska::MemoryManager*)
// vaddr 0x1f70f1c | ghidra 0x2070f1c | size 16 | symbol _ZN4Aska11SoundMemory20SetResourceMemoryMgrEPNS_13MemoryManagerE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska11SoundMemory20SetResourceMemoryMgrEPNS_13MemoryManagerE(undefined8 param_1)

{
  *(undefined8 *)PTR__ZN4Aska11SoundMemory14m_pMemResourceE_02cc4c90 = param_1;
  return;
}

// ==== Aska::SoundMemory::Malloc(unsigned long)
// vaddr 0x1f70f2c | ghidra 0x2070f2c | size 48 | symbol _ZN4Aska11SoundMemory6MallocEm | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska11SoundMemory6MallocEm(undefined8 param_1)

{
  long lVar1;
  
  lVar1 = *(long *)PTR__ZN4Aska11SoundMemory10m_pMemHeapE_02cbbc38;
  if (lVar1 == 0) {
    lVar1 = Aska::Global::GetAvailableMemoryManager()();
  }
  (*(code *)PTR__ZN4Aska13MemoryManager6MallocEm_02ca1310)(lVar1,param_1);
  return;
}

// ==== Aska::SoundMemory::AlignedMalloc(unsigned long, unsigned long)
// vaddr 0x1f70f5c | ghidra 0x2070f5c | size 68 | symbol _ZN4Aska11SoundMemory13AlignedMallocEmm | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska11SoundMemory13AlignedMallocEmm(undefined8 param_1,int param_2)

{
  long lVar1;
  
  lVar1 = *(long *)PTR__ZN4Aska11SoundMemory10m_pMemHeapE_02cbbc38;
  if (lVar1 == 0) {
    lVar1 = Aska::Global::GetAvailableMemoryManager()();
  }
  (*(code *)PTR__ZN4Aska13MemoryManager13AlignedMallocEml_02cae360)(lVar1,param_1,(long)param_2);
  return;
}

// ==== Aska::SoundMemory::ResourceAlloc(unsigned long, unsigned long)
// vaddr 0x1f70fa0 | ghidra 0x2070fa0 | size 68 | symbol _ZN4Aska11SoundMemory13ResourceAllocEmm | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska11SoundMemory13ResourceAllocEmm(undefined8 param_1,int param_2)

{
  long lVar1;
  
  lVar1 = *(long *)PTR__ZN4Aska11SoundMemory14m_pMemResourceE_02cc4c90;
  if (lVar1 == 0) {
    lVar1 = Aska::Global::GetAvailableMemoryManager()();
  }
  (*(code *)PTR__ZN4Aska13MemoryManager13AlignedMallocEml_02cae360)(lVar1,param_1,(long)param_2);
  return;
}

// ==== Aska::SoundMemory::ResourceFree(void*)
// vaddr 0x1f70fe4 | ghidra 0x2070fe4 | size 12 | symbol _ZN4Aska11SoundMemory12ResourceFreeEPv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska11SoundMemory12ResourceFreeEPv(long param_1)

{
  if (param_1 != 0) {
    (*(code *)PTR__ZdlPv_02ca4758)();
    return;
  }
  return;
}

// ==== Aska::SoundObject::Play(unsigned int, float)
// vaddr 0x1f72180 | ghidra 0x2072180 | size 192 | symbol _ZN4Aska11SoundObject4PlayEjf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 _ZN4Aska11SoundObject4PlayEjf(float param_1,long param_2,int param_3)

{
  ulong uVar1;
  undefined8 uVar2;
  undefined4 uVar3;
  undefined4 uStack_34;
  
  uVar1 = Aska::Sequencer2::AddMessageNote(unsigned int, float, void const*, void const*)(*(float *)(param_2 + 0x108) + 0.0,param_2 + 0x18,0,0,0);
  uVar2 = 0;
  if ((uVar1 & 1) != 0) {
    if (param_3 != 0) {
      uVar3 = 0;
      if (_UNK_02965bf8 < param_1) {
        uVar3 = powf(0x41200000,param_1 * _UNK_027edb4c,0);
      }
      uVar1 = Aska::Sequencer2::AddMessageNote(unsigned int, float, void const*, void const*)(*(float *)(param_2 + 0x108) + 0.0,param_2 + 0x18,5,
                              CONCAT44(uStack_34,uVar3),param_3);
      if ((uVar1 & 1) == 0) {
        return 0;
      }
    }
    uVar2 = 1;
  }
  return uVar2;
}

// ==== Aska::SoundObject::Stop(unsigned int)
// vaddr 0x1f72240 | ghidra 0x2072240 | size 128 | symbol _ZN4Aska11SoundObject4StopEj | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Possible PIC construction at 0x02072274: Changing call to branch */
/* WARNING: Removing unreachable block (ram,0x02072278) */
/* WARNING: Removing unreachable block (ram,0x020722ac) */

void _ZN4Aska11SoundObject4StopEj(long param_1,int param_2)

{
  undefined8 uVar1;
  long lVar2;
  float fVar3;
  undefined4 uStack_24;
  
  if (param_2 == 0) {
    fVar3 = *(float *)(param_1 + 0x108) + 0.0;
    uVar1 = 1;
    lVar2 = 0;
    param_2 = 0;
  }
  else {
    lVar2 = (ulong)uStack_24 << 0x20;
    fVar3 = *(float *)(param_1 + 0x108);
    uVar1 = 4;
  }
  (*(code *)PTR__ZN4Aska10Sequencer214AddMessageNoteEjfPKvS2__02c9f638)
            (fVar3,param_1 + 0x18,uVar1,lVar2,param_2);
  return;
}

// ==== Aska::SoundObject::Pause()
// vaddr 0x1f722c0 | ghidra 0x20722c0 | size 32 | symbol _ZN4Aska11SoundObject5PauseEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska11SoundObject5PauseEv(long param_1)

{
  (*(code *)PTR__ZN4Aska10Sequencer214AddMessageNoteEjfPKvS2__02c9f638)
            (*(float *)(param_1 + 0x108) + 0.0,param_1 + 0x18,2,0,0);
  return;
}

// ==== Aska::SoundObject::Resume()
// vaddr 0x1f722e0 | ghidra 0x20722e0 | size 32 | symbol _ZN4Aska11SoundObject6ResumeEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska11SoundObject6ResumeEv(long param_1)

{
  (*(code *)PTR__ZN4Aska10Sequencer214AddMessageNoteEjfPKvS2__02c9f638)
            (*(float *)(param_1 + 0x108) + 0.0,param_1 + 0x18,3,0,0);
  return;
}

// ==== Aska::SoundObject::Get(unsigned long, void*) const
// vaddr 0x1f72300 | ghidra 0x2072300 | size 316 | symbol _ZNK4Aska11SoundObject3GetEmPv | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 _ZNK4Aska11SoundObject3GetEmPv(long param_1,ulong param_2,float *param_3)

{
  undefined8 uVar1;
  long *plVar2;
  long lVar3;
  float fVar4;
  float fVar5;
  
  if ((param_2 & 0xffff00000000) != 0) {
    return 0;
  }
  uVar1 = 0;
  switch(param_2 & 0xffff) {
  case 0:
    fVar5 = 0.0;
    if (*(long *)(param_1 + 0x128) != 0) {
      lVar3 = *(long *)(*(long *)(param_1 + 0x128) + 0x118);
      fVar5 = 0.0;
      if (lVar3 != 0) {
        lVar3 = *(long *)(lVar3 + 0x10);
        fVar5 = 0.0;
        if (lVar3 != 0) {
          fVar5 = (float)(uint)*(byte *)(lVar3 + 0x14);
        }
      }
    }
    break;
  case 1:
    plVar2 = *(long **)(param_1 + 0x128);
    if (plVar2 == (long *)0x0) goto code_r0x020723d0;
    fVar4 = (float)(**(code **)(*plVar2 + 0x88))(plVar2,0);
    fVar5 = _UNK_02965bf8;
    if (_UNK_027fac84 <= ABS(fVar4)) {
      fVar5 = (float)log10f();
      fVar5 = fVar5 * 20.0;
    }
    goto code_r0x0207242c;
  case 2:
    plVar2 = *(long **)(param_1 + 0x128);
    if (plVar2 != (long *)0x0) {
      lVar3 = *plVar2;
      uVar1 = 1;
code_r0x020723c4:
      fVar5 = (float)(**(code **)(lVar3 + 0x88))(plVar2,uVar1);
      goto code_r0x0207242c;
    }
    goto code_r0x020723d0;
  case 3:
    plVar2 = *(long **)(param_1 + 0x128);
    if (plVar2 != (long *)0x0) {
      lVar3 = *plVar2;
      uVar1 = 2;
      goto code_r0x020723c4;
    }
code_r0x020723d0:
    fVar5 = 0.0;
code_r0x0207242c:
    *param_3 = fVar5;
    goto code_r0x02072430;
  default:
    goto code_r0x02072434;
  case 0xd:
    fVar5 = 0.0;
    if (*(long *)(param_1 + 0x128) == 0) break;
    lVar3 = *(long *)(*(long *)(param_1 + 0x128) + 0x118);
    fVar5 = 0.0;
    if (lVar3 == 0) break;
    *param_3 = *(float *)(*(long *)(*(long *)(lVar3 + 0x30) + 8) + 0x58);
    goto code_r0x02072430;
  case 0xe:
    fVar5 = 0.0;
    if (*(long *)(param_1 + 0x128) != 0) {
      lVar3 = *(long *)(*(long *)(param_1 + 0x128) + 0x118);
      fVar5 = 0.0;
      if (lVar3 != 0) {
        fVar5 = *(float *)(*(long *)(*(long *)(lVar3 + 0x30) + 8) + 0x80);
      }
    }
  }
  *param_3 = fVar5;
code_r0x02072430:
  uVar1 = 1;
code_r0x02072434:
  return uVar1;
}

// ==== Aska::SoundObject::Set(unsigned long, void const*)
// vaddr 0x1f7243c | ghidra 0x207243c | size 224 | symbol _ZN4Aska11SoundObject3SetEmPKv | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 _ZN4Aska11SoundObject3SetEmPKv(long param_1,ulong param_2,float *param_3)

{
  uint uVar1;
  undefined8 uVar2;
  ulong uVar3;
  undefined4 uVar4;
  float fVar5;
  undefined4 uStack_24;
  undefined4 uStack_14;
  
  if ((param_2 & 0xffff00000000) == 0) {
    uVar1 = (uint)param_2 & 0xffff;
    if (uVar1 == 3) {
      uVar3 = (ulong)(uint)*param_3;
      fVar5 = *(float *)(param_1 + 0x108) + 0.0;
      uVar2 = 7;
    }
    else if (uVar1 == 2) {
      uVar2 = 6;
      uVar3 = CONCAT44(uStack_14,*param_3);
      fVar5 = *(float *)(param_1 + 0x108) + 0.0;
    }
    else {
      if (uVar1 != 1) goto code_r0x02072454;
      uVar4 = 0;
      if (_UNK_02965bf8 < *param_3) {
        uVar4 = powf(0x41200000,*param_3 * _UNK_027edb4c);
      }
      uVar3 = CONCAT44(uStack_24,uVar4);
      uVar2 = 5;
      fVar5 = *(float *)(param_1 + 0x108) + 0.0;
    }
    Aska::Sequencer2::AddMessageNote(unsigned int, float, void const*, void const*)(fVar5,param_1 + 0x18,uVar2,uVar3,0);
    uVar2 = 1;
  }
  else {
code_r0x02072454:
    uVar2 = 0;
  }
  return uVar2;
}

// ==== Aska::SEControlObject::~SEControlObject()
// vaddr 0x1f7251c | ghidra 0x207251c | size 80 | symbol _ZN4Aska15SEControlObjectD2Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska15SEControlObjectD1Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska15SEControlObjectE_02cbe780 + 0x10);
  Aska::SEControlObject::DetachEmitter()();
  if ((*(byte *)((long)param_1 + 0x334) & 1) != 0) {
    if ((long *)param_1[99] != (long *)0x0) {
      (**(code **)(*(long *)param_1[99] + 8))();
    }
    param_1[99] = 0;
  }
  Aska::AudioEmitter::~AudioEmitter()(param_1 + 0x40);
  (*(code *)PTR__ZN4Aska11SoundObjectD1Ev_02ca5738)(param_1);
  return;
}

// ==== Aska::SEControlObject::DetachEmitter()
// vaddr 0x1f7256c | ghidra 0x207256c | size 384 | symbol _ZN4Aska15SEControlObject13DetachEmitterEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska15SEControlObject13DetachEmitterEv(long param_1)

{
  int *piVar1;
  int *piVar2;
  char cVar3;
  bool bVar4;
  ulong uVar5;
  int iVar6;
  
  if (*(long *)(param_1 + 0x218) == 0) {
    return;
  }
  Aska::Audio3DEngine::DeleteAudioEmitter(Aska::AudioEmitter*)(*(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50 + 0x390,param_1 + 0x200);
  piVar1 = (int *)(param_1 + 600);
  iVar6 = 0;
  do {
    while (*piVar1 != -1) {
      ClearExclusiveLocal();
      bVar4 = 0x1fe < iVar6;
      iVar6 = iVar6 + 1;
      if (bVar4) {
        piVar2 = (int *)(param_1 + 0x25c);
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
              uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0x298);
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
                Aska::Semaphore::Wait() const(param_1 + 0x298);
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
                if (cVar3 == '\0') goto code_r0x020726d4;
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
code_r0x020726d4:
        do {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
          if (bVar4) {
            *piVar2 = *piVar2 + -1;
            cVar3 = ExclusiveMonitorsStatus();
          }
        } while (cVar3 != '\0');
        DataMemoryBarrier(2,3);
code_r0x02072604:
        *(undefined8 *)(param_1 + 0x218) = 0;
        DataMemoryBarrier(2,3);
        *(undefined4 *)(param_1 + 600) = 0xffffffff;
        DataMemoryBarrier(2,3);
        piVar1 = (int *)(param_1 + 0x25c);
        if (0x14 < *piVar1) {
          do {
            cVar3 = '\x01';
            bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
            if (bVar4) {
              *piVar1 = *piVar1 + -1;
              cVar3 = ExclusiveMonitorsStatus();
            }
          } while (cVar3 != '\0');
          uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0x298);
          if ((uVar5 & 1) != 0) {
            Aska::Semaphore::Signal() const(param_1 + 0x298);
          }
        }
        (*(code *)PTR__ZN4Aska13Audio3DObject12UpdateMatrixEv_02cb19f8)(param_1 + 0x200);
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
  goto code_r0x02072604;
}

// ==== Aska::SEControlObject::FinishPlaybackEx()
// vaddr 0x1f726ec | ghidra 0x20726ec | size 48 | symbol _ZN4Aska15SEControlObject16FinishPlaybackExEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska15SEControlObject16FinishPlaybackExEv(long param_1)

{
  if ((*(byte *)(param_1 + 0x334) & 1) != 0) {
    if (*(long **)(param_1 + 0x318) != (long *)0x0) {
      (**(code **)(**(long **)(param_1 + 0x318) + 8))();
    }
    *(undefined8 *)(param_1 + 0x318) = 0;
  }
  return;
}

// ==== Aska::SoundObject::~SoundObject()
// vaddr 0x1f7271c | ghidra 0x207271c | size 148 | symbol _ZN4Aska11SoundObjectD2Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska11SoundObjectD1Ev(long *param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZTVN4Aska11SoundObjectE_02cbe158;
  param_1[4] = 0;
  *param_1 = (long)(puVar1 + 0x10);
  if ((long *)param_1[0x25] != (long *)0x0) {
    (**(code **)(*(long *)param_1[0x25] + 8))();
    param_1[0x25] = 0;
  }
  param_1[0x27] = 1;
  *(undefined4 *)(param_1 + 0x28) = 0;
  if (param_1[0x29] != 0) {
    operator delete[](void*)();
    param_1[0x29] = 0;
  }
  Aska::FastCriticalSection::~FastCriticalSection()(param_1 + 0x2a);
  puVar1 = PTR__ZTVN4Aska13TDynamicQueueINS_11SoundObject16RequestContainerELb1EEE_02cc4f38;
  *(undefined4 *)(param_1 + 0x28) = 0;
  param_1[0x26] = (long)(puVar1 + 0x10);
  param_1[0x27] = 1;
  if (param_1[0x29] != 0) {
    operator delete[](void*)();
    param_1[0x29] = 0;
  }
  Aska::Sequencer2::~Sequencer2()(param_1 + 3);
  (*(code *)PTR__ZN4Aska11IAnimatableD2Ev_02cb13b8)(param_1);
  return;
}

// ==== Aska::SEControlObject::~SEControlObject()
// vaddr 0x1f727b0 | ghidra 0x20727b0 | size 88 | symbol _ZN4Aska15SEControlObjectD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska15SEControlObjectD0Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska15SEControlObjectE_02cbe780 + 0x10);
  Aska::SEControlObject::DetachEmitter()();
  if ((*(byte *)((long)param_1 + 0x334) & 1) != 0) {
    if ((long *)param_1[99] != (long *)0x0) {
      (**(code **)(*(long *)param_1[99] + 8))();
    }
    param_1[99] = 0;
  }
  Aska::AudioEmitter::~AudioEmitter()(param_1 + 0x40);
  Aska::SoundObject::~SoundObject()(param_1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::SEControlObject::AttachEmitter(Aska::HierarchicalObject*)
// vaddr 0x1f72808 | ghidra 0x2072808 | size 404 | symbol _ZN4Aska15SEControlObject13AttachEmitterEPNS_18HierarchicalObjectE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska15SEControlObject13AttachEmitterEPNS_18HierarchicalObjectE(long param_1,long param_2)

{
  int *piVar1;
  int *piVar2;
  char cVar3;
  bool bVar4;
  ulong uVar5;
  int iVar6;
  
  if (param_2 == 0) {
    return;
  }
  Aska::SEControlObject::DetachEmitter()(param_1);
  piVar1 = (int *)(param_1 + 600);
  iVar6 = 0;
  do {
    while (*piVar1 != -1) {
      ClearExclusiveLocal();
      bVar4 = 0x1fe < iVar6;
      iVar6 = iVar6 + 1;
      if (bVar4) {
        piVar2 = (int *)(param_1 + 0x25c);
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
              uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0x298);
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
                Aska::Semaphore::Wait() const(param_1 + 0x298);
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
                if (cVar3 == '\0') goto code_r0x02072984;
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
code_r0x02072984:
        do {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
          if (bVar4) {
            *piVar2 = *piVar2 + -1;
            cVar3 = ExclusiveMonitorsStatus();
          }
        } while (cVar3 != '\0');
        DataMemoryBarrier(2,3);
code_r0x02072894:
        *(long *)(param_1 + 0x218) = param_2;
        DataMemoryBarrier(2,3);
        *(undefined4 *)(param_1 + 600) = 0xffffffff;
        DataMemoryBarrier(2,3);
        piVar1 = (int *)(param_1 + 0x25c);
        if (0x14 < *piVar1) {
          do {
            cVar3 = '\x01';
            bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
            if (bVar4) {
              *piVar1 = *piVar1 + -1;
              cVar3 = ExclusiveMonitorsStatus();
            }
          } while (cVar3 != '\0');
          uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0x298);
          if ((uVar5 & 1) != 0) {
            Aska::Semaphore::Signal() const(param_1 + 0x298);
          }
        }
        Aska::Audio3DObject::UpdateMatrix()(param_1 + 0x200);
        (*(code *)PTR__ZN4Aska13Audio3DEngine15AddAudioEmitterEPNS_12AudioEmitterE_02c9c0b0)
                  (*(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50 + 0x390,param_1 + 0x200);
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
  goto code_r0x02072894;
}

// ==== Aska::SEControlObject::Get(unsigned long, void*) const
// vaddr 0x1f7299c | ghidra 0x207299c | size 136 | symbol _ZNK4Aska15SEControlObject3GetEmPv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK4Aska15SEControlObject3GetEmPv(long param_1,ulong param_2,undefined8 *param_3)

{
  ulong uVar1;
  undefined4 uVar2;
  
  uVar1 = Aska::SoundObject::Get(unsigned long, void*) const();
  if ((uVar1 & 1) == 0) {
    if ((param_2 & 0xffff00000000) != 0) {
code_r0x020729cc:
      return 0;
    }
    switch((uint)param_2 & 0xffff) {
    case 0x11:
      *param_3 = *(undefined8 *)(param_1 + 0x218);
      return 1;
    case 0x12:
      uVar2 = *(undefined4 *)(param_1 + 0x2f0);
      break;
    case 0x13:
      uVar2 = *(undefined4 *)(param_1 + 0x2f4);
      break;
    case 0x14:
      uVar2 = *(undefined4 *)(param_1 + 0x310);
      break;
    default:
      goto code_r0x020729cc;
    }
    *(undefined4 *)param_3 = uVar2;
  }
  return 1;
}

// ==== Aska::SEControlObject::Set(unsigned long, void const*)
// vaddr 0x1f72a24 | ghidra 0x2072a24 | size 172 | symbol _ZN4Aska15SEControlObject3SetEmPKv | lib libSOA-3.7.0.so | 2026-10-08
undefined4 _ZN4Aska15SEControlObject3SetEmPKv(undefined8 param_1,ulong param_2,uint *param_3)

{
  uint uVar1;
  ulong uVar2;
  undefined8 uVar3;
  undefined4 uStack_2c;
  undefined4 uStack_24;
  
  uVar2 = Aska::SoundObject::Set(unsigned long, void const*)();
  if ((uVar2 & 1) == 0) {
    if ((param_2 & 0xffff00000000) != 0) {
      return 0;
    }
    uVar1 = (uint)param_2 & 0xffff;
    if (uVar1 == 0x14) {
      uVar2 = (ulong)*param_3;
      uVar3 = 3;
    }
    else {
      if (uVar1 != 0x13) {
        if (uVar1 != 0x12) {
          return 0;
        }
        Aska::SoundObject::RequestSet(unsigned int, void const*)(param_1,1,CONCAT44(uStack_2c,*param_3));
        return 1;
      }
      uVar3 = 2;
      uVar2 = CONCAT44(uStack_24,*param_3);
    }
    Aska::SoundObject::RequestSet(unsigned int, void const*)(param_1,uVar3,uVar2);
  }
  return 1;
}

// ==== Aska::SoundObject::SoundObject()
// vaddr 0x1f72ba4 | ghidra 0x2072ba4 | size 180 | symbol _ZN4Aska11SoundObjectC2Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska11SoundObjectC1Ev(long *param_1)

{
  undefined *puVar1;
  long lVar2;
  
  param_1[2] = 0;
  *param_1 = (long)(PTR__ZTVN4Aska11SoundObjectE_02cbe158 + 0x10);
  param_1[1] = 0;
  Aska::Sequencer2::Sequencer2()(param_1 + 3);
  param_1[0x29] = 0;
  *(undefined4 *)(param_1 + 0x28) = 0;
  puVar1 = PTR__ZTVN4Aska18TSoundDynamicQueueINS_11SoundObject16RequestContainerEEE_02cc02f8;
  param_1[0x27] = 1;
  param_1[0x25] = 0;
  param_1[0x26] = (long)(puVar1 + 0x10);
  Aska::FastCriticalSection::FastCriticalSection()(param_1 + 0x2a);
  param_1[0x3c] = 0;
  param_1[0x3d] = 0;
  *(undefined2 *)(param_1 + 0x3e) = 0xffff;
  *(byte *)((long)param_1 + 0x1f2) = *(byte *)((long)param_1 + 0x1f2) & 0xfe;
  if ((int)param_1[0x28] != 5) {
    if (param_1[0x29] != 0) {
      operator delete[](void*)();
      param_1[0x29] = 0;
    }
    lVar2 = Aska::SoundMemory::Malloc(unsigned long)(0x50);
    param_1[0x29] = lVar2;
    if (lVar2 == 0) {
      *(undefined4 *)(param_1 + 0x28) = 0;
      return;
    }
    *(undefined4 *)(param_1 + 0x28) = 5;
    param_1[0x27] = 1;
  }
  return;
}

// ==== Aska::SoundObject::FinishPlayback()
// vaddr 0x1f72c74 | ghidra 0x2072c74 | size 44 | symbol _ZN4Aska11SoundObject14FinishPlaybackEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska11SoundObject14FinishPlaybackEv(long param_1)

{
  *(undefined8 *)(param_1 + 0x20) = 0;
  if (*(long **)(param_1 + 0x128) != (long *)0x0) {
    (**(code **)(**(long **)(param_1 + 0x128) + 8))();
    *(undefined8 *)(param_1 + 0x128) = 0;
  }
  return;
}

// ==== Aska::TDynamicQueue<Aska::SoundObject::RequestContainer, true>::~TDynamicQueue()
// vaddr 0x1f72ca0 | ghidra 0x2072ca0 | size 56 | symbol _ZN4Aska13TDynamicQueueINS_11SoundObject16RequestContainerELb1EED2Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska13TDynamicQueueINS_11SoundObject16RequestContainerELb1EED2Ev(long *param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZTVN4Aska13TDynamicQueueINS_11SoundObject16RequestContainerELb1EEE_02cc4f38;
  *(undefined4 *)(param_1 + 2) = 0;
  *param_1 = (long)(puVar1 + 0x10);
  param_1[1] = 1;
  if (param_1[3] != 0) {
    operator delete[](void*)();
    param_1[3] = 0;
  }
  return;
}

// ==== Aska::SoundObject::~SoundObject()
// vaddr 0x1f72cd8 | ghidra 0x2072cd8 | size 24 | symbol _ZN4Aska11SoundObjectD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska11SoundObjectD0Ev(undefined8 param_1)

{
  Aska::SoundObject::~SoundObject()();
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::SoundObject::DeleteThis()
// vaddr 0x1f72cf0 | ghidra 0x2072cf0 | size 56 | symbol _ZN4Aska11SoundObject10DeleteThisEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska11SoundObject10DeleteThisEv(undefined8 param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50;
  Aska::SoundManager::NoneCommandList(Aska::SoundObject*)(*(undefined8 *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50,param_1);
  (*(code *)PTR__ZN4Aska12SoundManager22AddDeletingSoundObjectEPNS_11SoundObjectE_02caa480)
            (*(undefined8 *)puVar1,param_1);
  return;
}

// ==== Aska::SoundManager::AddDeletingSoundObject(Aska::SoundObject*)
// vaddr 0x1f72d28 | ghidra 0x2072d28 | size 456 | symbol _ZN4Aska12SoundManager22AddDeletingSoundObjectEPNS_11SoundObjectE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12SoundManager22AddDeletingSoundObjectEPNS_11SoundObjectE(long param_1,long param_2)

{
  int *piVar1;
  int *piVar2;
  char cVar3;
  bool bVar4;
  ulong uVar5;
  int iVar6;
  long lVar7;
  
  piVar1 = (int *)(param_1 + 0xff0);
  iVar6 = 0;
code_r0x02072d44:
  if (*piVar1 == -1) {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar4) {
      *piVar1 = 0;
      cVar3 = ExclusiveMonitorsStatus();
    }
    if (cVar3 == '\0') goto code_r0x02072e10;
    goto code_r0x02072d44;
  }
  ClearExclusiveLocal();
  bVar4 = iVar6 < 0x1ff;
  iVar6 = iVar6 + 1;
  if (bVar4) goto code_r0x02072d44;
  piVar2 = (int *)(param_1 + 0xff4);
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
        uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0x1030);
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
          Aska::Semaphore::Wait() const(param_1 + 0x1030);
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
          if (cVar3 == '\0') goto code_r0x02072e00;
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
code_r0x02072e00:
  do {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar4) {
      *piVar2 = *piVar2 + -1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
code_r0x02072e10:
  DataMemoryBarrier(2,3);
  for (lVar7 = *(long *)(param_1 + 0xc18); param_1 + 0xc08 != lVar7; lVar7 = *(long *)(lVar7 + 0x10)
      ) {
    if (lVar7 == param_2) goto code_r0x02072e88;
  }
  if (((((*(byte *)(param_2 + 0x1e8) >> 3 & 1) != 0) && (*(long *)(param_2 + 0x128) != 0)) &&
      (lVar7 = *(long *)(*(long *)(param_2 + 0x128) + 0x118), lVar7 != 0)) &&
     (lVar7 = *(long *)(*(long *)(lVar7 + 0x30) + 8), lVar7 != 0)) {
    *(undefined1 *)(lVar7 + 0x728) = 1;
  }
  lVar7 = *(long *)(param_1 + 0xc10);
  *(long *)(param_2 + 8) = lVar7;
  *(long *)(param_2 + 0x10) = param_1 + 0xc08;
  *(long *)(param_1 + 0xc10) = param_2;
  *(long *)(lVar7 + 0x10) = param_2;
  *(int *)(param_1 + 0xe00) = *(int *)(param_1 + 0xe00) + 1;
code_r0x02072e88:
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_1 + 0xff0) = 0xffffffff;
  DataMemoryBarrier(2,3);
  if (0x14 < *(int *)(param_1 + 0xff4)) {
    piVar1 = (int *)(param_1 + 0xff4);
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
    uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0x1030);
    if ((uVar5 & 1) != 0) {
      (*(code *)PTR__ZNK4Aska9Semaphore6SignalEv_02c96cd0)(param_1 + 0x1030);
      return;
    }
  }
  return;
}

// ==== Aska::SoundObject::Playback(unsigned int, Aska::AudioPlayer*, Aska::DirectPlaybackSettings const*)
// vaddr 0x1f72ef0 | ghidra 0x2072ef0 | size 336 | symbol _ZN4Aska11SoundObject8PlaybackEjPNS_11AudioPlayerEPKNS_22DirectPlaybackSettingsE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8
_ZN4Aska11SoundObject8PlaybackEjPNS_11AudioPlayerEPKNS_22DirectPlaybackSettingsE
          (long param_1,undefined4 param_2,long param_3,long param_4)

{
  int iVar1;
  undefined8 uVar2;
  ulong uVar3;
  float fVar4;
  undefined4 uVar5;
  undefined4 uStack_44;
  
  uVar2 = 0;
  if ((param_3 != 0) && (param_4 != 0)) {
    *(undefined8 *)(param_1 + 0x20) = 0;
    if (*(long **)(param_1 + 0x128) != (long *)0x0) {
      (**(code **)(**(long **)(param_1 + 0x128) + 8))();
      *(undefined8 *)(param_1 + 0x128) = 0;
    }
    *(long *)(param_1 + 0x128) = param_3;
    *(long *)(param_1 + 0x20) = param_3;
    *(undefined4 *)(param_1 + 0x1e8) = param_2;
    *(undefined4 *)(param_1 + 0x1ec) = 0;
    *(uint *)(param_1 + 0x1ec) = (uint)*(byte *)(param_4 + 0x1f);
    *(undefined2 *)(param_1 + 0x1f0) = *(undefined2 *)(param_4 + 0x1c);
    fVar4 = _UNK_02965bf8;
    if (_UNK_027fac84 <= ABS(*(float *)(param_4 + 0x10))) {
      fVar4 = (float)log10f();
      fVar4 = fVar4 * 20.0;
    }
    fVar4 = (float)Aska::WavePlayer::CalcMasterVolumeDB(float)(fVar4,param_3);
    iVar1 = *(int *)(param_4 + 8);
    uVar3 = Aska::Sequencer2::AddMessageNote(unsigned int, float, void const*, void const*)(*(float *)(param_1 + 0x108) + 0.0,param_1 + 0x18,0,0,0);
    uVar2 = 0;
    if ((uVar3 & 1) != 0) {
      if (iVar1 != 0) {
        uVar5 = 0;
        if (_UNK_02965bf8 < fVar4) {
          uVar5 = powf(0x41200000,fVar4 * _UNK_027edb4c,0);
        }
        uVar3 = Aska::Sequencer2::AddMessageNote(unsigned int, float, void const*, void const*)(*(float *)(param_1 + 0x108) + 0.0,param_1 + 0x18,5,
                                CONCAT44(uStack_44,uVar5),iVar1);
        if ((uVar3 & 1) == 0) {
          return 0;
        }
      }
      uVar2 = 1;
    }
  }
  return uVar2;
}

// ==== Aska::SoundObject::AudioRun()
// vaddr 0x1f73040 | ghidra 0x2073040 | size 288 | symbol _ZN4Aska11SoundObject8AudioRunEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska11SoundObject8AudioRunEv(long *param_1)

{
  char cVar1;
  ulong uVar2;
  long lVar3;
  long *plVar4;
  long *plVar5;
  undefined1 auStack_40 [16];
  
  if (param_1[0x25] == 0) {
    return;
  }
  while (uVar2 = Aska::SoundObject::RequestGet(Aska::SoundObject::RequestContainer*)(param_1,auStack_40), (uVar2 & 1) != 0) {
    (**(code **)(*param_1 + 0x58))(param_1,auStack_40);
  }
  Aska::Sequencer2::AudioRun()(param_1 + 3);
  plVar4 = (long *)param_1[0x25];
  (**(code **)(*plVar4 + 0x70))(plVar4);
  if ((*(uint *)(plVar4 + 3) | 1) != 3) goto code_r0x02073144;
  plVar5 = *(long **)(*(long *)(plVar4[0x23] + 0x30) + 8);
  cVar1 = *(char *)((long)plVar5 + 0x8d);
  *(undefined1 *)((long)plVar5 + 0x8d) = 0;
  if (cVar1 != '\0') {
    (**(code **)(*param_1 + 0x50))(param_1);
  }
  uVar2 = (**(code **)(*plVar5 + 0xb8))(plVar5,1,0);
  if ((uVar2 & 1) == 0) {
code_r0x02073114:
    if ((plVar4[0x23] == 0) || (*(char *)(plVar4[0x23] + 0x641) == '\0')) goto code_r0x02073144;
  }
  else {
    lVar3 = plVar4[0x23];
    if (lVar3 == 0) goto code_r0x02073144;
    if ((*(char *)(lVar3 + 0x640) == '\0') || (DataMemoryBarrier(2,3), -1 < *(int *)(lVar3 + 0x63c))
       ) goto code_r0x02073114;
  }
  Aska::Sequencer2::AddMessageNote(unsigned int, float, void const*, void const*)(*(float *)(param_1 + 0x21) + 0.0,param_1 + 3,1,0,0);
code_r0x02073144:
  *(int *)(param_1 + 0x3c) = (int)plVar4[3];
  return;
}

// ==== Aska::SoundObject::RequestGet(Aska::SoundObject::RequestContainer*)
// vaddr 0x1f73160 | ghidra 0x2073160 | size 380 | symbol _ZN4Aska11SoundObject10RequestGetEPNS0_16RequestContainerE | lib libSOA-3.7.0.so | 2026-10-08
bool _ZN4Aska11SoundObject10RequestGetEPNS0_16RequestContainerE(long param_1,undefined8 *param_2)

{
  int *piVar1;
  int *piVar2;
  uint uVar3;
  char cVar4;
  bool bVar5;
  undefined8 *puVar6;
  bool bVar7;
  ulong uVar8;
  int iVar9;
  undefined8 uVar10;
  
  piVar1 = (int *)(param_1 + 0x188);
  iVar9 = 0;
  do {
    while (*piVar1 == -1) {
      cVar4 = '\x01';
      bVar7 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar7) {
        *piVar1 = 0;
        cVar4 = ExclusiveMonitorsStatus();
      }
      if (cVar4 == '\0') goto code_r0x02073244;
    }
    ClearExclusiveLocal();
    bVar7 = iVar9 < 0x1ff;
    iVar9 = iVar9 + 1;
  } while (bVar7);
  piVar2 = (int *)(param_1 + 0x18c);
  do {
    cVar4 = '\x01';
    bVar7 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar7) {
      *piVar2 = *piVar2 + 1;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
  do {
    if (*piVar1 != -1) {
      ClearExclusiveLocal();
      do {
        uVar8 = Aska::Semaphore::IsReady() const(param_1 + 0x1c8);
        if ((uVar8 & 1) == 0) {
          do {
            cVar4 = '\x01';
            bVar7 = (bool)ExclusiveMonitorPass(piVar2,0x10);
            if (bVar7) {
              *piVar2 = *piVar2 + -1;
              cVar4 = ExclusiveMonitorsStatus();
            }
          } while (cVar4 != '\0');
          Aska::Thread::Sleep(unsigned int)(1);
        }
        else {
          Aska::Semaphore::Wait() const(param_1 + 0x1c8);
        }
        do {
          cVar4 = '\x01';
          bVar7 = (bool)ExclusiveMonitorPass(piVar2,0x10);
          if (bVar7) {
            *piVar2 = *piVar2 + 1;
            cVar4 = ExclusiveMonitorsStatus();
          }
        } while (cVar4 != '\0');
        while (*piVar1 == -1) {
          cVar4 = '\x01';
          bVar7 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar7) {
            *piVar1 = 0;
            cVar4 = ExclusiveMonitorsStatus();
          }
          if (cVar4 == '\0') goto code_r0x02073234;
        }
        ClearExclusiveLocal();
      } while( true );
    }
    cVar4 = '\x01';
    bVar7 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar7) {
      *piVar1 = 0;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
code_r0x02073234:
  do {
    cVar4 = '\x01';
    bVar7 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar7) {
      *piVar2 = *piVar2 + -1;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
code_r0x02073244:
  DataMemoryBarrier(2,3);
  uVar3 = 0;
  if (*(int *)(param_1 + 0x13c) + 1U < *(uint *)(param_1 + 0x140)) {
    uVar3 = *(int *)(param_1 + 0x13c) + 1;
  }
  bVar7 = uVar3 != *(uint *)(param_1 + 0x138);
  if (bVar7) {
    *(uint *)(param_1 + 0x13c) = uVar3;
    puVar6 = (undefined8 *)(*(long *)(param_1 + 0x148) + (ulong)uVar3 * 0x10);
    uVar10 = *puVar6;
    param_2[1] = puVar6[1];
    *param_2 = uVar10;
  }
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_1 + 0x188) = 0xffffffff;
  DataMemoryBarrier(2,3);
  if (0x14 < *(int *)(param_1 + 0x18c)) {
    piVar1 = (int *)(param_1 + 0x18c);
    do {
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar5) {
        *piVar1 = *piVar1 + -1;
        cVar4 = ExclusiveMonitorsStatus();
      }
    } while (cVar4 != '\0');
    uVar8 = Aska::Semaphore::IsReady() const(param_1 + 0x1c8);
    if ((uVar8 & 1) != 0) {
      Aska::Semaphore::Signal() const(param_1 + 0x1c8);
    }
  }
  return bVar7;
}

// ==== Aska::SoundObject::UpdateSoundStatus()
// vaddr 0x1f732dc | ghidra 0x20732dc | size 80 | symbol _ZN4Aska11SoundObject17UpdateSoundStatusEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska11SoundObject17UpdateSoundStatusEv(long param_1)

{
  int iVar1;
  
  if ((*(byte *)(param_1 + 0x1f2) & 1) == 0) {
    iVar1 = *(int *)(param_1 + 0x1e0);
    if (*(int *)(param_1 + 0x1e4) - 2U < 3) {
      if (iVar1 != 5) {
        return;
      }
    }
    else {
      if (*(int *)(param_1 + 0x1e4) != 1) {
        return;
      }
      if ((iVar1 != 5) && (iVar1 != 2)) {
        return;
      }
    }
  }
  else {
    iVar1 = 5;
  }
  *(int *)(param_1 + 0x1e4) = iVar1;
  return;
}

// ==== Aska::SoundObject::RequestSet(unsigned int, void const*)
// vaddr 0x1f7332c | ghidra 0x207332c | size 552 | symbol _ZN4Aska11SoundObject10RequestSetEjPKv | lib libSOA-3.7.0.so | 2026-10-08
undefined4
_ZN4Aska11SoundObject10RequestSetEjPKv(long param_1,undefined4 param_2,undefined8 param_3)

{
  int *piVar1;
  int *piVar2;
  undefined4 *puVar3;
  uint uVar4;
  char cVar5;
  bool bVar6;
  long lVar7;
  ulong uVar8;
  int iVar9;
  undefined4 uVar10;
  
  piVar1 = (int *)(param_1 + 0x188);
  iVar9 = 0;
code_r0x02073350:
  do {
    if (*piVar1 != -1) {
      ClearExclusiveLocal();
      bVar6 = iVar9 < 0x1ff;
      iVar9 = iVar9 + 1;
      if (bVar6) goto code_r0x02073350;
      piVar2 = (int *)(param_1 + 0x18c);
      do {
        cVar5 = '\x01';
        bVar6 = (bool)ExclusiveMonitorPass(piVar2,0x10);
        if (bVar6) {
          *piVar2 = *piVar2 + 1;
          cVar5 = ExclusiveMonitorsStatus();
        }
      } while (cVar5 != '\0');
      do {
        if (*piVar1 != -1) {
          ClearExclusiveLocal();
          do {
            uVar8 = Aska::Semaphore::IsReady() const(param_1 + 0x1c8);
            if ((uVar8 & 1) == 0) {
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
              Aska::Semaphore::Wait() const(param_1 + 0x1c8);
            }
            do {
              cVar5 = '\x01';
              bVar6 = (bool)ExclusiveMonitorPass(piVar2,0x10);
              if (bVar6) {
                *piVar2 = *piVar2 + 1;
                cVar5 = ExclusiveMonitorsStatus();
              }
            } while (cVar5 != '\0');
            while (*piVar1 == -1) {
              cVar5 = '\x01';
              bVar6 = (bool)ExclusiveMonitorPass(piVar1,0x10);
              if (bVar6) {
                *piVar1 = 0;
                cVar5 = ExclusiveMonitorsStatus();
              }
              if (cVar5 == '\0') goto code_r0x02073408;
            }
            ClearExclusiveLocal();
          } while( true );
        }
        cVar5 = '\x01';
        bVar6 = (bool)ExclusiveMonitorPass(piVar1,0x10);
        if (bVar6) {
          *piVar1 = 0;
          cVar5 = ExclusiveMonitorsStatus();
        }
      } while (cVar5 != '\0');
code_r0x02073408:
      do {
        cVar5 = '\x01';
        bVar6 = (bool)ExclusiveMonitorPass(piVar2,0x10);
        if (bVar6) {
          *piVar2 = *piVar2 + -1;
          cVar5 = ExclusiveMonitorsStatus();
        }
      } while (cVar5 != '\0');
code_r0x02073418:
      DataMemoryBarrier(2,3);
      uVar4 = *(uint *)(param_1 + 0x138);
      if (*(uint *)(param_1 + 0x13c) == uVar4) {
        lVar7 = Aska::SoundMemory::Malloc(unsigned long)((ulong)(*(int *)(param_1 + 0x140) + 1) << 4);
        if (lVar7 != 0) {
          memcpy(lVar7,*(long *)(param_1 + 0x148) +
                                (ulong)*(uint *)(param_1 + 0x138) * 0x10,
                          (ulong)(*(int *)(param_1 + 0x140) - *(uint *)(param_1 + 0x138)) << 4);
          if (*(uint *)(param_1 + 0x13c) != 0) {
            memcpy(lVar7 + (ulong)(uint)(*(int *)(param_1 + 0x140) -
                                                 *(int *)(param_1 + 0x138)) * 0x10,
                            *(undefined8 *)(param_1 + 0x148),(ulong)*(uint *)(param_1 + 0x13c) << 4)
            ;
          }
          if (*(long *)(param_1 + 0x148) != 0) {
            operator delete(void*)();
          }
          uVar4 = *(uint *)(param_1 + 0x140);
          *(long *)(param_1 + 0x148) = lVar7;
          *(undefined4 *)(param_1 + 0x13c) = 0;
          *(uint *)(param_1 + 0x138) = uVar4;
          *(uint *)(param_1 + 0x140) = uVar4 + 1;
          puVar3 = (undefined4 *)(lVar7 + (ulong)uVar4 * 0x10);
          *(undefined4 *)(param_1 + 0x138) = 0;
          goto joined_r0x020734e4;
        }
      }
      else {
        *(uint *)(param_1 + 0x138) = uVar4 + 1;
        puVar3 = (undefined4 *)(*(long *)(param_1 + 0x148) + (ulong)uVar4 * 0x10);
        iVar9 = 0;
        if (uVar4 + 1 < *(uint *)(param_1 + 0x140)) {
          iVar9 = uVar4 + 1;
        }
        *(int *)(param_1 + 0x138) = iVar9;
joined_r0x020734e4:
        if (puVar3 != (undefined4 *)0x0) {
          *(undefined8 *)(puVar3 + 2) = param_3;
          uVar10 = 1;
          *puVar3 = param_2;
          goto code_r0x020734f4;
        }
      }
      uVar10 = 0;
code_r0x020734f4:
      DataMemoryBarrier(2,3);
      *(undefined4 *)(param_1 + 0x188) = 0xffffffff;
      DataMemoryBarrier(2,3);
      if (0x14 < *(int *)(param_1 + 0x18c)) {
        piVar1 = (int *)(param_1 + 0x18c);
        do {
          cVar5 = '\x01';
          bVar6 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar6) {
            *piVar1 = *piVar1 + -1;
            cVar5 = ExclusiveMonitorsStatus();
          }
        } while (cVar5 != '\0');
        uVar8 = Aska::Semaphore::IsReady() const(param_1 + 0x1c8);
        if ((uVar8 & 1) != 0) {
          Aska::Semaphore::Signal() const(param_1 + 0x1c8);
        }
      }
      return uVar10;
    }
    cVar5 = '\x01';
    bVar6 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar6) {
      *piVar1 = 0;
      cVar5 = ExclusiveMonitorsStatus();
    }
    if (cVar5 == '\0') goto code_r0x02073418;
  } while( true );
}

// ==== Aska::SoundObject::ProcessRequest(Aska::SoundObject::RequestContainer const*)
// vaddr 0x1f73554 | ghidra 0x2073554 | size 4 | symbol _ZN4Aska11SoundObject14ProcessRequestEPKNS0_16RequestContainerE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska11SoundObject14ProcessRequestEPKNS0_16RequestContainerE(void)

{
  return;
}

// ==== Aska::SEControlObject::SEControlObject()
// vaddr 0x1f73558 | ghidra 0x2073558 | size 228 | symbol _ZN4Aska15SEControlObjectC1Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska15SEControlObjectC2Ev(long *param_1)

{
  undefined *puVar1;
  long lVar2;
  
  param_1[2] = 0;
  *param_1 = (long)(PTR__ZTVN4Aska11SoundObjectE_02cbe158 + 0x10);
  param_1[1] = 0;
  Aska::Sequencer2::Sequencer2()(param_1 + 3);
  param_1[0x29] = 0;
  *(undefined4 *)(param_1 + 0x28) = 0;
  puVar1 = PTR__ZTVN4Aska18TSoundDynamicQueueINS_11SoundObject16RequestContainerEEE_02cc02f8;
  param_1[0x25] = 0;
  param_1[0x26] = (long)(puVar1 + 0x10);
  param_1[0x27] = 1;
  Aska::FastCriticalSection::FastCriticalSection()(param_1 + 0x2a);
  param_1[0x3c] = 0;
  param_1[0x3d] = 0;
  *(undefined2 *)(param_1 + 0x3e) = 0xffff;
  *(byte *)((long)param_1 + 0x1f2) = *(byte *)((long)param_1 + 0x1f2) & 0xfe;
  if ((int)param_1[0x28] != 5) {
    if (param_1[0x29] != 0) {
      operator delete[](void*)();
      param_1[0x29] = 0;
    }
    lVar2 = Aska::SoundMemory::Malloc(unsigned long)(0x50);
    param_1[0x29] = lVar2;
    if (lVar2 == 0) {
      *(undefined4 *)(param_1 + 0x28) = 0;
    }
    else {
      *(undefined4 *)(param_1 + 0x28) = 5;
      param_1[0x27] = 1;
    }
  }
  *param_1 = (long)(PTR__ZTVN4Aska15SEControlObjectE_02cbe780 + 0x10);
  Aska::AudioEmitter::AudioEmitter()(param_1 + 0x40);
  *(undefined4 *)(param_1 + 0x66) = 0;
  *(undefined4 *)(param_1 + 0x3d) = 1;
  *(byte *)((long)param_1 + 0x334) = *(byte *)((long)param_1 + 0x334) & 0xfe;
  return;
}

// ==== Aska::SEControlObject::Playback(unsigned int, Aska::AudioPlayer*, Aska::DirectPlaybackSettings const*)
// vaddr 0x1f7363c | ghidra 0x207363c | size 452 | symbol _ZN4Aska15SEControlObject8PlaybackEjPNS_11AudioPlayerEPKNS_22DirectPlaybackSettingsE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8
_ZN4Aska15SEControlObject8PlaybackEjPNS_11AudioPlayerEPKNS_22DirectPlaybackSettingsE
          (long param_1,undefined4 param_2,long param_3,long param_4)

{
  int iVar1;
  undefined4 *puVar2;
  float fVar3;
  float fVar4;
  undefined *puVar5;
  undefined8 uVar6;
  long *plVar7;
  int iVar8;
  long lVar9;
  int iVar10;
  uint uVar11;
  undefined4 uVar12;
  float fVar13;
  byte bVar14;
  
  if ((param_3 != 0) && (param_4 != 0)) {
    lVar9 = *(long *)(*(long *)(param_3 + 0x120) + 0x80);
    uVar11 = *(uint *)(lVar9 + 0x30);
    puVar2 = (undefined4 *)((ulong)uVar11 + lVar9);
    if ((uVar11 == 0 || puVar2 == (undefined4 *)0x0) || (uVar11 = puVar2[2], uVar11 < 2)) {
      lVar9 = *(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50;
      *(undefined4 *)(param_1 + 0x2f4) = *(undefined4 *)(lVar9 + 0x618);
      *(undefined4 *)(param_1 + 0x310) = *(undefined4 *)(lVar9 + 0x6a8);
      uVar6 = *(undefined8 *)(lVar9 + 0x6b0);
      *(byte *)(param_1 + 0x334) = *(byte *)(param_1 + 0x334) & 0xfe;
      *(undefined8 *)(param_1 + 0x318) = uVar6;
    }
    else {
      *(undefined4 *)(param_1 + 0x310) = puVar2[1];
      uVar12 = NEON_ucvtf(*puVar2);
      *(undefined4 *)(param_1 + 0x2f4) = uVar12;
      plVar7 = (long *)Aska::SoundMemory::Malloc(unsigned long)(0xb8);
      if (plVar7 == (long *)0x0) {
        return 0;
      }
      *(undefined8 *)((long)plVar7 + 0x4c) = 0;
      puVar5 = PTR__ZTVN4Aska19TFastQuadraticCurveILi8EEE_02cba7e8;
      *(undefined4 *)(plVar7 + 9) = 0x3f800000;
      *(undefined1 *)((long)plVar7 + 0xb4) = 1;
      fVar4 = _UNK_02971e08;
      plVar7[8] = 0;
      plVar7[7] = 0;
      plVar7[6] = 0;
      plVar7[5] = 0;
      plVar7[4] = 0;
      plVar7[3] = 0;
      plVar7[2] = 0;
      plVar7[1] = 0;
      fVar3 = _UNK_028014f8;
      iVar8 = 0;
      *plVar7 = (long)(puVar5 + 0x10);
      iVar10 = 0x11;
      do {
        if (iVar8 < 8) {
          iVar1 = iVar10 + (8 - puVar2[2]) * 2;
          bVar14 = *(byte *)((long)puVar2 + (long)(iVar1 + -0x10) + 0xc);
          fVar13 = (float)NEON_ucvtf((uint)*(byte *)((long)puVar2 + (long)(iVar1 + -0x11) + 0xc));
          *(float *)((long)plVar7 + (long)iVar8 * 4 + 8) = fVar13 / fVar3;
          fVar13 = (float)NEON_ucvtf((uint)bVar14);
          *(float *)((long)plVar7 + (long)(int)plVar7[10] * 4 + 0x28) = fVar13 / fVar4 + 1.0;
          iVar8 = (int)plVar7[10] + 1;
          *(int *)(plVar7 + 10) = iVar8;
        }
        uVar11 = uVar11 - 1;
        iVar10 = iVar10 + 2;
      } while (uVar11 != 0);
      (**(code **)(*plVar7 + 0x90))(plVar7);
      *(long **)(param_1 + 0x318) = plVar7;
      *(byte *)(param_1 + 0x334) = *(byte *)(param_1 + 0x334) | 1;
    }
    uVar6 = (*(code *)
              PTR__ZN4Aska11SoundObject8PlaybackEjPNS_11AudioPlayerEPKNS_22DirectPlaybackSettingsE_02c950e8
            )(param_1,param_2,param_3,param_4);
    return uVar6;
  }
  return 0;
}

// ==== Aska::SEControlObject::AudioRun()
// vaddr 0x1f73800 | ghidra 0x2073800 | size 280 | symbol _ZN4Aska15SEControlObject8AudioRunEv | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska15SEControlObject8AudioRunEv(long param_1)

{
  float fVar1;
  undefined4 uVar2;
  float afStack_18 [2];
  
  if (*(char *)(param_1 + 800) == '\0') goto code_r0x020738e0;
  if (*(long *)(param_1 + 0x218) != 0) {
    Aska::SoundUtility::DownMixArray_51To2(float*, float const*, bool)(afStack_18,param_1 + 0x2f8,0);
    if (ABS(afStack_18[0] + afStack_18[1]) < _UNK_027fac84) {
code_r0x02073888:
      uVar2 = 0;
    }
    else {
      fVar1 = (float)log10f();
      fVar1 = fVar1 * 20.0 + -3.0;
      if (fVar1 <= _UNK_02965bf8) goto code_r0x02073888;
      uVar2 = powf(0x41200000,fVar1 * _UNK_027edb4c);
    }
    if ((0.0 < afStack_18[0]) || (0.0 < afStack_18[1])) {
      fVar1 = (afStack_18[1] - afStack_18[0]) / afStack_18[afStack_18[0] <= afStack_18[1]];
    }
    else {
      fVar1 = 0.0;
    }
    Aska::Sequencer2::AddMessageNote(unsigned int, float, void const*, void const*)(*(float *)(param_1 + 0x108) + 0.0,param_1 + 0x18,9,uVar2,fVar1);
  }
  *(undefined1 *)(param_1 + 800) = 0;
code_r0x020738e0:
  if ((*(int *)(param_1 + 0x1e0) == 4) || (*(int *)(param_1 + 0x1e0) == 2)) {
    *(float *)(param_1 + 0x330) = *(float *)(param_1 + 0x330) + 1.0;
  }
  Aska::SoundObject::AudioRun()(param_1);
  return;
}

// ==== Aska::SEControlObject::Update3DVolumeAndPanpot()
// vaddr 0x1f73918 | ghidra 0x2073918 | size 224 | symbol _ZN4Aska15SEControlObject23Update3DVolumeAndPanpotEv | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska15SEControlObject23Update3DVolumeAndPanpotEv(long param_1)

{
  float fVar1;
  undefined4 uVar2;
  float afStack_18 [2];
  
  if (*(long *)(param_1 + 0x218) == 0) {
    return;
  }
  Aska::SoundUtility::DownMixArray_51To2(float*, float const*, bool)(afStack_18,param_1 + 0x2f8,0);
  if (_UNK_027fac84 <= ABS(afStack_18[0] + afStack_18[1])) {
    fVar1 = (float)log10f();
    fVar1 = fVar1 * 20.0 + -3.0;
    if (_UNK_02965bf8 < fVar1) {
      uVar2 = powf(0x41200000,fVar1 * _UNK_027edb4c);
      goto code_r0x0207399c;
    }
  }
  uVar2 = 0;
code_r0x0207399c:
  if ((0.0 < afStack_18[0]) || (0.0 < afStack_18[1])) {
    fVar1 = (afStack_18[1] - afStack_18[0]) / afStack_18[afStack_18[0] <= afStack_18[1]];
  }
  else {
    fVar1 = 0.0;
  }
  Aska::Sequencer2::AddMessageNote(unsigned int, float, void const*, void const*)(*(float *)(param_1 + 0x108) + 0.0,param_1 + 0x18,9,uVar2,fVar1);
  return;
}

// ==== Aska::SEControlObject::ResetAtLoop()
// vaddr 0x1f739f8 | ghidra 0x20739f8 | size 8 | symbol _ZN4Aska15SEControlObject11ResetAtLoopEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska15SEControlObject11ResetAtLoopEv(long param_1)

{
  *(undefined4 *)(param_1 + 0x330) = 0;
  return;
}

// ==== Aska::SoundObject::ResetAtLoop()
// vaddr 0x1f73a00 | ghidra 0x2073a00 | size 4 | symbol _ZN4Aska11SoundObject11ResetAtLoopEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska11SoundObject11ResetAtLoopEv(void)

{
  return;
}

// ==== Aska::SEControlObject::ProcessRequest(Aska::SoundObject::RequestContainer const*)
// vaddr 0x1f73a04 | ghidra 0x2073a04 | size 64 | symbol _ZN4Aska15SEControlObject14ProcessRequestEPKNS_11SoundObject16RequestContainerE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska15SEControlObject14ProcessRequestEPKNS_11SoundObject16RequestContainerE
               (long param_1,int *param_2)

{
  int iVar1;
  
  iVar1 = *param_2;
  if (iVar1 == 3) {
    *(int *)(param_1 + 0x310) = (int)*(undefined8 *)(param_2 + 2);
  }
  else {
    if (iVar1 == 2) {
      *(int *)(param_1 + 0x2f4) = (int)*(undefined8 *)(param_2 + 2);
      return;
    }
    if (iVar1 == 1) {
      *(int *)(param_1 + 0x2f0) = (int)*(undefined8 *)(param_2 + 2);
      return;
    }
  }
  return;
}

// ==== Aska::SEControlObject::GetLipSync(float) const
// vaddr 0x1f73a44 | ghidra 0x2073a44 | size 184 | symbol _ZNK4Aska15SEControlObject10GetLipSyncEf | lib libSOA-3.7.0.so | 2026-10-08
undefined1 _ZNK4Aska15SEControlObject10GetLipSyncEf(float param_1,long param_2)

{
  ushort uVar1;
  long lVar2;
  long lVar3;
  long lVar4;
  
  lVar3 = *(long *)(param_2 + 0x128);
  if (lVar3 == 0) {
    return 0;
  }
  lVar2 = *(long *)(lVar3 + 0x120);
  if (lVar2 == 0) {
    return 0;
  }
  if (*(int *)(lVar2 + 0x44) == 0) {
    return 0;
  }
  if (lVar2 != -0x44) {
    if (*(uint *)(lVar2 + 0x48) < 2) {
      return 0;
    }
    lVar4 = *(long *)(*(long *)(lVar3 + 0x120) + 0x88);
    lVar3 = 0;
    do {
      uVar1 = *(ushort *)(lVar4 + (ulong)((int)lVar3 + 1) * 2);
      if ((uint)(int)(*(float *)(param_2 + 0x330) + param_1 + 3.0) <=
          ((uint)(uVar1 >> 8) | (uVar1 & 0xff00ff) << 8)) {
        return *(undefined1 *)
                ((lVar4 - (ulong)*(uint *)(lVar2 + 0x4c)) + (ulong)*(uint *)(lVar2 + 0x50) + lVar3);
      }
      lVar3 = lVar3 + 1;
    } while ((int)lVar3 + 1U < *(uint *)(lVar2 + 0x48));
    return 0;
  }
  return 0;
}

// ==== Aska::SEControlObject::GetVrcHeader() const
// vaddr 0x1f73afc | ghidra 0x2073afc | size 60 | symbol _ZNK4Aska15SEControlObject12GetVrcHeaderEv | lib libSOA-3.7.0.so | 2026-10-08
long _ZNK4Aska15SEControlObject12GetVrcHeaderEv(long param_1)

{
  long lVar1;
  
  lVar1 = *(long *)(param_1 + 0x128);
  if (lVar1 == 0) {
    return 0;
  }
  if (*(long *)(lVar1 + 0x120) != 0) {
    if (*(int *)(*(long *)(lVar1 + 0x120) + 0x44) != 0) {
      return *(long *)(lVar1 + 0x120) + 0x44;
    }
    return 0;
  }
  return 0;
}

// ==== Aska::SEControlObject::GetClassID(int) const
// vaddr 0x1f73b38 | ghidra 0x2073b38 | size 72 | symbol _ZNK4Aska15SEControlObject10GetClassIDEi | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK4Aska15SEControlObject10GetClassIDEi(undefined8 param_1,int param_2)

{
  undefined8 uVar1;
  undefined8 uVar2;
  
  if (param_2 != 0) {
    uVar2 = 0xf000f001;
    if (param_2 != 2) {
      uVar2 = 0xf000;
    }
    uVar1 = 0xf000f001f217;
    if (param_2 != 1) {
      uVar1 = uVar2;
    }
    return uVar1;
  }
  return 0xf000f001f217f218;
}

// ==== Aska::SoundObject::GetClassID(int) const
// vaddr 0x1f73bc8 | ghidra 0x2073bc8 | size 44 | symbol _ZNK4Aska11SoundObject10GetClassIDEi | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK4Aska11SoundObject10GetClassIDEi(undefined8 param_1,int param_2)

{
  undefined8 uVar1;
  undefined8 uVar2;
  
  uVar2 = 0xf000f001;
  if (param_2 != 1) {
    uVar2 = 0xf000;
  }
  uVar1 = 0xf000f001f217;
  if (param_2 != 0) {
    uVar1 = uVar2;
  }
  return uVar1;
}

// ==== Aska::TSoundDynamicQueue<Aska::SoundObject::RequestContainer>::~TSoundDynamicQueue()
// vaddr 0x1f73bf4 | ghidra 0x2073bf4 | size 56 | symbol _ZN4Aska18TSoundDynamicQueueINS_11SoundObject16RequestContainerEED0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska18TSoundDynamicQueueINS_11SoundObject16RequestContainerEED0Ev(long *param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZTVN4Aska13TDynamicQueueINS_11SoundObject16RequestContainerELb1EEE_02cc4f38;
  *(undefined4 *)(param_1 + 2) = 0;
  *param_1 = (long)(puVar1 + 0x10);
  param_1[1] = 1;
  if (param_1[3] != 0) {
    operator delete[](void*)();
  }
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::TDynamicQueue<Aska::SoundObject::RequestContainer, true>::~TDynamicQueue()
// vaddr 0x1f73c2c | ghidra 0x2073c2c | size 56 | symbol _ZN4Aska13TDynamicQueueINS_11SoundObject16RequestContainerELb1EED0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska13TDynamicQueueINS_11SoundObject16RequestContainerELb1EED0Ev(long *param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZTVN4Aska13TDynamicQueueINS_11SoundObject16RequestContainerELb1EEE_02cc4f38;
  *(undefined4 *)(param_1 + 2) = 0;
  *param_1 = (long)(puVar1 + 0x10);
  param_1[1] = 1;
  if (param_1[3] != 0) {
    operator delete[](void*)();
  }
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::SoundPass::SoundPass()
// vaddr 0x1f73c64 | ghidra 0x2073c64 | size 100 | symbol _ZN4Aska9SoundPassC1Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska9SoundPassC2Ev(long *param_1)

{
  undefined *puVar1;
  
  param_1[2] = 0;
  puVar1 = PTR__ZTVN4Aska9SoundPassE_02cc4328 + 0x10;
  param_1[0x16] = 0;
  *(undefined4 *)(param_1 + 0x17) = 0;
  param_1[0x18] = 0;
  *param_1 = (long)puVar1;
  param_1[1] = 0;
  param_1[0x1a] = 0;
  memset(param_1 + 3,0,0x58);
  param_1[0x19] = (long)(PTR__ZTVN4Aska9SoundPass13LoadEndNotifyE_02cc0ef8 + 0x10);
  *(undefined1 *)(param_1 + 0x1b) = 0;
  *(byte *)(param_1 + 0x1c) = *(byte *)(param_1 + 0x1c) & 0xfc;
  return;
}

// ==== Aska::SoundPass::~SoundPass()
// vaddr 0x1f73cc8 | ghidra 0x2073cc8 | size 20 | symbol _ZN4Aska9SoundPassD2Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska9SoundPassD1Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska9SoundPassE_02cc4328 + 0x10);
  return;
}

// ==== Aska::SoundPass::~SoundPass()
// vaddr 0x1f73cdc | ghidra 0x2073cdc | size 4 | symbol _ZN4Aska9SoundPassD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska9SoundPassD0Ev(void)

{
  (*(code *)PTR__ZdlPv_02ca4758)();
  return;
}

// ==== Aska::SoundPass::AudioRun()
// vaddr 0x1f73ce0 | ghidra 0x2073ce0 | size 3296 | symbol _ZN4Aska9SoundPass8AudioRunEv | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

bool _ZN4Aska9SoundPass8AudioRunEv(long param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  uint uVar5;
  ushort uVar6;
  short sVar7;
  uint uVar8;
  char cVar9;
  bool bVar10;
  short sVar11;
  int iVar12;
  ulong uVar13;
  long *plVar14;
  undefined8 uVar15;
  undefined4 uVar16;
  long lVar17;
  long lVar18;
  uint uVar19;
  long lVar20;
  short sVar21;
  undefined8 in_stack_ffffffffffffffa0;
  uint7 uVar22;
  undefined1 auStack_44 [4];
  undefined4 uStack_38;
  undefined4 uStack_34;
  
  iVar12 = *(int *)(param_1 + 0x1c);
  if (iVar12 != 0) {
    if (iVar12 == 2) {
      lVar17 = *(long *)(param_1 + 0xb0);
      uVar13 = (**(code **)(*(long *)(lVar17 + 0x288) + 0xa8))
                         (lVar17 + 0x288,0,*(undefined8 *)(lVar17 + 0x6d8),0);
      if ((uVar13 & 1) == 0) {
        if (*(int *)(param_1 + 0x1c) != 0) {
          return false;
        }
        goto code_r0x02073d44;
      }
    }
    else if ((iVar12 != 1) || (*(char *)(param_1 + 0xd8) == '\0')) {
      return false;
    }
    *(undefined4 *)(param_1 + 0x1c) = 0;
  }
code_r0x02073d44:
  iVar12 = *(int *)(param_1 + 0x18);
  if (iVar12 == 1) {
    if (*(long *)(param_1 + 0x20) != 0) {
      uVar19 = *(int *)(param_1 + 0x28) + 0x4fU & -*(int *)(param_1 + 0x28);
      lVar17 = Aska::SoundMemory::ResourceAlloc(unsigned long, unsigned long)(uVar19,0x200);
      *(long *)(param_1 + 0x30) = lVar17;
      if (lVar17 == 0) goto code_r0x0207499c;
      *(undefined1 *)(param_1 + 0xd8) = 0;
      uVar22 = (uint7)((ulong)in_stack_ffffffffffffffa0 >> 8);
      if ((*(byte *)(param_1 + 0xe0) & 1) == 0) {
        uVar13 = Aska::FileReadManager::Read(int, unsigned char*, Aska::INotify*, unsigned long, unsigned long, int, int, bool)(*(undefined8 *)PTR__ZN4Aska6Global18m_pFileReadManagerE_02cbf970,
                                 *(undefined8 *)(param_1 + 0x20),lVar17,param_1 + 200,uVar19,0,0,0,
                                 (ulong)uVar22 << 8);
      }
      else {
        uVar13 = Aska::FileReadManager::Read(char const*, unsigned char*, Aska::INotify*, unsigned long, unsigned long, int, int, bool, bool)(*(undefined8 *)PTR__ZN4Aska6Global18m_pFileReadManagerE_02cbf970,
                                 *(undefined8 *)(param_1 + 0x20),lVar17,param_1 + 200,uVar19,0,0,0,
                                 (ulong)uVar22 << 8,*(char *)(param_1 + 0xa8) != '\0');
      }
      if ((uVar13 & 1) == 0) {
        Aska::SoundMemory::ResourceFree(void*)(*(undefined8 *)(param_1 + 0x30));
        *(undefined8 *)(param_1 + 0x30) = 0;
        goto code_r0x0207499c;
      }
      uVar15 = 0x100000002;
      goto code_r0x02074030;
    }
    goto code_r0x0207499c;
  }
  if (iVar12 == 2) {
    lVar20 = Aska::SoundMemory::Malloc(unsigned long)(0x30);
    plVar14 = (long *)(param_1 + 0x60);
    *plVar14 = lVar20;
    lVar17 = 0;
    if (lVar20 != 0) {
      Aska::AacHandler::AacHandler()();
      lVar17 = *plVar14;
    }
    if (lVar17 == 0) goto code_r0x0207499c;
    uVar13 = Aska::AacHandler::CreateThis(void const*, bool, unsigned long, bool)(lVar17,*(undefined8 *)(param_1 + 0x30),
                             *(uint *)(param_1 + 0x70) >> 2 & 1,*(undefined8 *)(param_1 + 0x20),
                             *(byte *)(param_1 + 0xe0) & 1);
    if ((uVar13 & 1) == 0) {
      if ((long *)*plVar14 != (long *)0x0) {
        (**(code **)(*(long *)*plVar14 + 8))();
      }
      *plVar14 = 0;
      goto code_r0x0207499c;
    }
    *(undefined8 *)(param_1 + 0x20) = 0;
    *(undefined4 *)(param_1 + 0x18) = 3;
code_r0x02073e38:
    if ((*(byte *)(*(long *)(param_1 + 0x60) + 0x2c) >> 1 & 1) == 0) {
      lVar17 = *(long *)(*(long *)(param_1 + 0x60) + 8);
      uVar5 = *(uint *)(lVar17 + 0x20);
      uVar8 = -*(int *)(param_1 + 0x28);
      uVar19 = uVar5 & uVar8;
      uVar8 = ((uVar5 + *(int *)(param_1 + 0x28) + -1) - uVar19) + *(int *)(lVar17 + 0x28) & uVar8;
      lVar17 = Aska::SoundMemory::ResourceAlloc(unsigned long, unsigned long)(uVar8,0x200);
      *(long *)(param_1 + 0xc0) = lVar17;
      if (lVar17 != 0) {
        uVar15 = *(undefined8 *)(*(long *)(param_1 + 0x60) + 0x20);
        *(undefined1 *)(param_1 + 0xd8) = 0;
        uVar22 = (uint7)((ulong)in_stack_ffffffffffffffa0 >> 8);
        if ((*(byte *)(param_1 + 0xe0) & 1) == 0) {
          uVar13 = Aska::FileReadManager::Read(int, unsigned char*, Aska::INotify*, unsigned long, unsigned long, int, int, bool)(*(undefined8 *)PTR__ZN4Aska6Global18m_pFileReadManagerE_02cbf970,
                                   uVar15,lVar17,param_1 + 200,uVar8,uVar19,0,0,(ulong)uVar22 << 8);
        }
        else {
          uVar13 = Aska::FileReadManager::Read(char const*, unsigned char*, Aska::INotify*, unsigned long, unsigned long, int, int, bool, bool)(*(undefined8 *)PTR__ZN4Aska6Global18m_pFileReadManagerE_02cbf970,
                                   uVar15,lVar17,param_1 + 200,uVar8,uVar19,0,0,(ulong)uVar22 << 8,
                                   *(char *)(param_1 + 0xa8) != '\0');
        }
        if ((uVar13 & 1) == 0) {
          Aska::SoundMemory::ResourceFree(void*)(*(undefined8 *)(param_1 + 0xc0));
          *(undefined8 *)(param_1 + 0xc0) = 0;
          goto code_r0x0207499c;
        }
        uVar15 = 0x100000004;
        goto code_r0x02074030;
      }
      goto code_r0x0207499c;
    }
    *(byte *)(param_1 + 0xe0) = *(byte *)(param_1 + 0xe0) & 0xfd;
    lVar17 = (ulong)*(uint *)(*(long *)(param_1 + 0x30) + 0x20) + *(long *)(param_1 + 0x30);
    uVar13 = Aska::AFF::AacUtil::IsAvailableAao(void const*, unsigned int)(lVar17,*(undefined4 *)(param_1 + 0x2c));
    if ((uVar13 & 1) == 0) goto code_r0x0207499c;
    lVar17 = lVar17 + (ulong)*(uint *)(lVar17 + (ulong)*(uint *)(lVar17 + 0x18) +
                                       (long)*(int *)(param_1 + 0x2c) * 0x20 + 0x10);
    *(long *)(param_1 + 0x38) = lVar17;
    *(undefined8 *)(param_1 + 0x40) = 0;
    if ((*(byte *)(*(long *)(param_1 + 0x60) + 0x2c) >> 2 & 1) != 0) {
      iVar12 = *(int *)(param_1 + 0x18);
      goto code_r0x02074040;
    }
    lVar18 = *(long *)(param_1 + 0x30);
    uVar6 = *(ushort *)(lVar17 + 0x1e);
    lVar20 = (ulong)*(uint *)(lVar18 + 0x40) + lVar18;
    *(ulong *)(param_1 + 0x48) =
         lVar20 + (ulong)*(uint *)(lVar20 + (ulong)*(uint *)(lVar20 + 0x18) +
                                   (ulong)*(ushort *)(lVar17 + 0x1c) * 0x20 + 0x10);
    if ((ulong)uVar6 != 0xffff) {
      lVar18 = (ulong)*(uint *)(lVar18 + 0x30) + lVar18;
      *(ulong *)(param_1 + 0x50) =
           lVar18 + (ulong)*(uint *)(lVar18 + (ulong)*(uint *)(lVar18 + 0x18) + (ulong)uVar6 * 0x20
                                    + 0x10);
    }
    *(undefined4 *)(param_1 + 0x18) = 6;
code_r0x02074470:
    lVar17 = *(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50;
    if ((*(uint *)(param_1 + 0x70) & 1) == 0) {
      if (((*(uint *)(param_1 + 0x70) >> 1 & 1) != 0) && (1 < *(uint *)(lVar17 + 0x138))) {
        lVar20 = *(long *)(lVar17 + 0x130);
        lVar17 = lVar17 + 0x120;
        if (lVar17 != lVar20) {
          sVar7 = *(short *)(param_1 + 0x94);
          uVar19 = 0;
          sVar21 = 0xff;
          lVar18 = lVar20;
          do {
            sVar11 = sVar21;
            if ((*(uint *)(lVar18 + 0x1e4) & 0xfffffffe) != 4) {
              uVar19 = uVar19 + 1;
              sVar11 = *(short *)(lVar18 + 0x1f0);
              if (sVar21 <= *(short *)(lVar18 + 0x1f0)) {
                sVar11 = sVar21;
              }
            }
            sVar21 = sVar11;
            lVar18 = *(long *)(lVar18 + 0x10);
          } while (lVar17 != lVar18);
          if (1 < uVar19) {
            if ((sVar21 != sVar7 && sVar7 <= sVar21) ||
               (*(char *)(param_1 + 0x96) != '\0' && sVar21 == sVar7)) goto code_r0x0207499c;
            do {
              if (((*(uint *)(lVar20 + 0x1e4) & 0xfffffffe) != 4) &&
                 ((sVar21 == *(short *)(lVar20 + 0x1f0) &&
                  (uVar13 = Aska::SoundObject::Stop(unsigned int)(lVar20,200), (uVar13 & 1) != 0))))
              goto code_r0x020747b4;
              lVar20 = *(long *)(lVar20 + 0x10);
            } while (lVar17 != lVar20);
          }
        }
      }
    }
    else if (0x16 < *(uint *)(lVar17 + 0x110)) {
      lVar20 = *(long *)(lVar17 + 0x108);
      lVar17 = lVar17 + 0xf8;
      if (lVar17 != lVar20) {
        sVar7 = *(short *)(param_1 + 0x94);
        uVar19 = 0;
        sVar21 = 0xff;
        lVar18 = lVar20;
        do {
          sVar11 = sVar21;
          if ((*(uint *)(lVar18 + 0x1e4) & 0xfffffffe) != 4) {
            uVar19 = uVar19 + 1;
            sVar11 = *(short *)(lVar18 + 0x1f0);
            if (sVar21 <= *(short *)(lVar18 + 0x1f0)) {
              sVar11 = sVar21;
            }
          }
          sVar21 = sVar11;
          lVar18 = *(long *)(lVar18 + 0x10);
        } while (lVar17 != lVar18);
        if (0x16 < uVar19) {
          if ((sVar21 != sVar7 && sVar7 <= sVar21) ||
             (*(char *)(param_1 + 0x96) != '\0' && sVar21 == sVar7)) goto code_r0x0207499c;
          do {
            if (((*(uint *)(lVar20 + 0x1e4) & 0xfffffffe) != 4) &&
               ((sVar21 == *(short *)(lVar20 + 0x1f0) &&
                (uVar13 = Aska::SoundObject::Stop(unsigned int)(lVar20,200), (uVar13 & 1) != 0)))) goto code_r0x020747b4;
            lVar20 = *(long *)(lVar20 + 0x10);
          } while (lVar17 != lVar20);
        }
      }
    }
    goto code_r0x020747bc;
  }
  if (iVar12 == 3) goto code_r0x02073e38;
code_r0x02074040:
  if (iVar12 == 6) goto code_r0x02074470;
  if (iVar12 == 5) {
    lVar17 = (ulong)*(uint *)(*(long *)(param_1 + 0x38) + 0x10) + *(long *)(param_1 + 0x38);
    uVar19 = *(int *)(param_1 + 0x28) - 1;
    if ((uVar19 & *(uint *)(lVar17 + 0x30)) == 0) {
      uVar19 = uVar19 + *(int *)(lVar17 + 0x10) & -*(int *)(param_1 + 0x28);
      lVar20 = Aska::SoundMemory::ResourceAlloc(unsigned long, unsigned long)(uVar19,0x200);
      *(long *)(param_1 + 0x50) = lVar20;
      if (lVar20 != 0) {
        uVar16 = *(undefined4 *)(lVar17 + 0x30);
        uVar15 = *(undefined8 *)(*(long *)(param_1 + 0x60) + 0x20);
        *(undefined1 *)(param_1 + 0xd8) = 0;
        uVar22 = (uint7)((ulong)in_stack_ffffffffffffffa0 >> 8);
        if ((*(byte *)(param_1 + 0xe0) & 1) == 0) {
          uVar13 = Aska::FileReadManager::Read(int, unsigned char*, Aska::INotify*, unsigned long, unsigned long, int, int, bool)(*(undefined8 *)PTR__ZN4Aska6Global18m_pFileReadManagerE_02cbf970,
                                   uVar15,lVar20,param_1 + 200,uVar19,uVar16,0,0,(ulong)uVar22 << 8)
          ;
        }
        else {
          uVar13 = Aska::FileReadManager::Read(char const*, unsigned char*, Aska::INotify*, unsigned long, unsigned long, int, int, bool, bool)(*(undefined8 *)PTR__ZN4Aska6Global18m_pFileReadManagerE_02cbf970,
                                   uVar15,lVar20,param_1 + 200,uVar19,uVar16,0,0,(ulong)uVar22 << 8,
                                   *(char *)(param_1 + 0xa8) != '\0');
        }
        if ((uVar13 & 1) != 0) {
          uVar15 = 0x100000006;
code_r0x02074030:
          *(undefined8 *)(param_1 + 0x18) = uVar15;
          return false;
        }
        Aska::SoundMemory::ResourceFree(void*)(*(undefined8 *)(param_1 + 0x50));
        *(undefined8 *)(param_1 + 0x50) = 0;
      }
    }
    goto code_r0x0207499c;
  }
  if (iVar12 != 4) goto code_r0x02074854;
  lVar17 = *(long *)(param_1 + 0xc0) +
           (ulong)(*(int *)(param_1 + 0x28) - 1U &
                  *(uint *)(*(long *)(*(long *)(param_1 + 0x60) + 8) + 0x20));
  uVar13 = Aska::AFF::AacUtil::IsAvailableAao(void const*, unsigned int)(lVar17,*(undefined4 *)(param_1 + 0x2c));
  if ((uVar13 & 1) == 0) goto code_r0x0207499c;
  lVar17 = lVar17 + (ulong)*(uint *)(lVar17 + (ulong)*(uint *)(lVar17 + 0x18) +
                                     (long)*(int *)(param_1 + 0x2c) * 0x20 + 0x10);
  *(long *)(param_1 + 0x38) = lVar17;
  *(undefined8 *)(param_1 + 0x40) = *(undefined8 *)(param_1 + 0xc0);
  iVar12 = *(int *)(param_1 + 0x28);
  lVar17 = lVar17 + (ulong)*(uint *)(lVar17 + 0x18);
  if ((iVar12 - 1U & *(uint *)(lVar17 + 0x30)) != 0) goto code_r0x0207499c;
  uVar19 = 0xa0000;
  if (*(uint *)(param_1 + 0xa0) != 0) {
    uVar19 = *(uint *)(param_1 + 0xa0);
  }
  uVar8 = 5;
  if (*(uint *)(param_1 + 0xa4) != 0) {
    uVar8 = *(uint *)(param_1 + 0xa4);
  }
  if (*(uint *)(lVar17 + 0x1c) <= uVar19) {
    *(byte *)(param_1 + 0xe0) = *(byte *)(param_1 + 0xe0) & 0xfd;
    uVar19 = (*(int *)(lVar17 + 0x1c) + iVar12) - 1U & -iVar12;
    lVar20 = Aska::SoundMemory::ResourceAlloc(unsigned long, unsigned long)(uVar19,0x200);
    *(long *)(param_1 + 0x48) = lVar20;
    if (lVar20 != 0) {
      uVar16 = *(undefined4 *)(lVar17 + 0x30);
      uVar15 = *(undefined8 *)(*(long *)(param_1 + 0x60) + 0x20);
      *(undefined1 *)(param_1 + 0xd8) = 0;
      uVar22 = (uint7)((ulong)in_stack_ffffffffffffffa0 >> 8);
      if ((*(byte *)(param_1 + 0xe0) & 1) == 0) {
        uVar13 = Aska::FileReadManager::Read(int, unsigned char*, Aska::INotify*, unsigned long, unsigned long, int, int, bool)(*(undefined8 *)PTR__ZN4Aska6Global18m_pFileReadManagerE_02cbf970,
                                 uVar15,lVar20,param_1 + 200,uVar19,uVar16,0,0,(ulong)uVar22 << 8);
      }
      else {
        uVar13 = Aska::FileReadManager::Read(char const*, unsigned char*, Aska::INotify*, unsigned long, unsigned long, int, int, bool, bool)(*(undefined8 *)PTR__ZN4Aska6Global18m_pFileReadManagerE_02cbf970,
                                 uVar15,lVar20,param_1 + 200,uVar19,uVar16,0,0,(ulong)uVar22 << 8,
                                 *(char *)(param_1 + 0xa8) != '\0');
      }
      if ((uVar13 & 1) != 0) {
        *(undefined4 *)(param_1 + 0x1c) = 1;
        sVar7 = *(short *)(*(long *)(param_1 + 0x38) + 0x1e);
        goto code_r0x020747a0;
      }
      Aska::SoundMemory::ResourceFree(void*)(*(undefined8 *)(param_1 + 0x48));
      *(undefined8 *)(param_1 + 0x48) = 0;
    }
    goto code_r0x0207499c;
  }
  *(byte *)(param_1 + 0xe0) = *(byte *)(param_1 + 0xe0) | 2;
  *(uint *)(param_1 + 0x70) = *(uint *)(param_1 + 0x70) | 8;
  plVar14 = (long *)Aska::SoundMemory::Malloc(unsigned long)(0x780);
  *(long **)(param_1 + 0xb0) = plVar14;
  puVar4 = PTR__ZTVN4Aska14DiscReadStreamE_02cc4e70;
  lVar20 = 0;
  if (plVar14 != (long *)0x0) {
    puVar1 = PTR__ZTVN4Aska6TQueueIiLi8EEE_02cbf310 + 0x10;
    *plVar14 = (long)(PTR__ZTVN4Aska18AaoStreamingStreamE_02cb9ee0 + 0x10);
    plVar14[1] = (long)puVar1;
    *(undefined4 *)(plVar14 + 2) = 1;
    *(undefined4 *)((long)plVar14 + 0x14) = 0;
    plVar14[0xe] = 0;
    plVar14[0xb] = 0;
    plVar14[10] = 0;
    plVar14[0xd] = 0;
    plVar14[0xc] = 0;
    plVar14[9] = 0;
    plVar14[8] = 0;
    *(undefined4 *)(plVar14 + 0x11) = 0;
    puVar2 = PTR__ZTVN4Aska16MultiMediaStreamE_02cbd4c8 + 0x10;
    puVar3 = PTR__ZTVN4Aska18TPoolAtomicDynamicINS_14DiscReadStream15ReadAsyncNotifyEEE_02cc1350 +
             0x10;
    *(undefined1 *)((long)plVar14 + 0x8e) = 0;
    *(undefined2 *)((long)plVar14 + 0x8c) = 0;
    plVar14[0x10] = 0;
    plVar14[0xf] = 0;
    plVar14[0x13] = (long)puVar3;
    plVar14[0x12] = (long)(puVar4 + 0x10);
    plVar14[0x15] = 0;
    plVar14[0x14] = 0;
    *(undefined4 *)(plVar14 + 0x16) = 0;
    *(undefined4 *)((long)plVar14 + 0xb4) = 0;
    *(undefined2 *)(plVar14 + 0x17) = 0;
    *(undefined4 *)((long)plVar14 + 0xbc) = 0;
    *(undefined4 *)(plVar14 + 0x18) = 0;
    plVar14[0x3d] = 0;
    *(undefined2 *)(plVar14 + 0x3e) = 0;
    *(undefined1 *)(plVar14 + 0x1c) = 0;
    plVar14[0x1b] = 0;
    plVar14[0x1a] = 0;
    plVar14[0x19] = 0;
    plVar14[0x40] = (long)puVar1;
    plVar14[0x3f] = (long)puVar2;
    *(undefined4 *)(plVar14 + 0x41) = 1;
    *(undefined4 *)((long)plVar14 + 0x20c) = 0;
    plVar14[0x4d] = 0;
    plVar14[0x4c] = 0;
    plVar14[0x4b] = 0;
    puVar4 = PTR__ZTVN4Aska15StreamingStreamE_02cc1e40 + 0x10;
    plVar14[0x4a] = 0;
    plVar14[0x49] = 0;
    plVar14[0x48] = 0;
    plVar14[0x47] = 0;
    *(undefined4 *)(plVar14 + 0x50) = 0;
    *(undefined1 *)((long)plVar14 + 0x286) = 0;
    *(undefined2 *)((long)plVar14 + 0x284) = 0;
    plVar14[0x4f] = 0;
    plVar14[0x4e] = 0;
    plVar14[0x51] = (long)puVar4;
    plVar14[0x53] = 0;
    plVar14[0x52] = 0;
    plVar14[0x55] = 0;
    plVar14[0x54] = 0;
    Aska::RingBuffer::Reset()(plVar14 + 0x52);
    plVar14[0x59] =
         (long)(PTR__ZTVN4Aska11TPoolAtomicINS_15StreamingStream15BufferingNotifyELi9EEE_02cc33b0 +
               0x10);
    puVar4 = PTR__ZTVN4Aska15StreamingStream15BufferingNotifyE_02cbd080;
    plVar14[0x5d] = 0;
    plVar14[0x5c] = 0;
    plVar14[0x61] = 0;
    plVar14[0x60] = 0;
    plVar14[0x65] = 0;
    plVar14[100] = 0;
    plVar14[0x69] = 0;
    plVar14[0x68] = 0;
    plVar14[0x6d] = 0;
    plVar14[0x6c] = 0;
    plVar14[0x71] = 0;
    plVar14[0x70] = 0;
    plVar14[0x75] = 0;
    plVar14[0x74] = 0;
    plVar14[0x79] = 0;
    plVar14[0x78] = 0;
    puVar4 = puVar4 + 0x10;
    plVar14[0x5e] = 0;
    plVar14[0x62] = 0;
    plVar14[0x66] = 0;
    plVar14[0x6a] = 0;
    plVar14[0x6e] = 0;
    plVar14[0x72] = 0;
    plVar14[0x76] = 0;
    plVar14[0x7a] = 0;
    plVar14[0x7e] = 0;
    plVar14[0x7d] = 0;
    plVar14[0x7c] = 0;
    plVar14[0x5b] = (long)puVar4;
    plVar14[0x5f] = (long)puVar4;
    plVar14[99] = (long)puVar4;
    plVar14[0x67] = (long)puVar4;
    plVar14[0x6b] = (long)puVar4;
    plVar14[0x6f] = (long)puVar4;
    plVar14[0x73] = (long)puVar4;
    plVar14[0x77] = (long)puVar4;
    plVar14[0x7b] = (long)puVar4;
    *(undefined4 *)(plVar14 + 0x7f) = 0;
    *(undefined4 *)((long)plVar14 + 0x3fc) = 0;
    uStack_34 = 0;
    *(undefined4 *)(plVar14 + 0x5a) = 0;
    *(undefined1 *)(plVar14 + 0x80) = 1;
    Aska::Thread::Thread()(plVar14 + 0x81);
    plVar14[0x81] =
         (long)(PTR__ZTVN4Aska17TWorkerThreadBaseINS_15StreamingStream12WorkerThreadEEE_02cb8f08 +
               0x10);
    Aska::Event::Event()(plVar14 + 0x84);
    *(undefined1 *)(plVar14 + 0x91) = 0;
    *(undefined1 *)((long)plVar14 + 0x489) = 0;
    puVar4 = PTR__ZTVN4Aska6TQueueINS_15StreamingStream12WorkerThread7RequestELi9EEE_02cbcb80;
    plVar14[0x81] = (long)(PTR__ZTVN4Aska15StreamingStream12WorkerThreadE_02cc3220 + 0x10);
    plVar14[0x92] = (long)(puVar4 + 0x10);
    *(undefined4 *)(plVar14 + 0x93) = 1;
    *(undefined4 *)((long)plVar14 + 0x49c) = 0;
    do {
      cVar9 = '\x01';
      bVar10 = (bool)ExclusiveMonitorPass(plVar14 + 0xc6,0x10);
      if (bVar10) {
        *(undefined4 *)(plVar14 + 0xc6) = 0;
        cVar9 = ExclusiveMonitorsStatus();
      }
    } while (cVar9 != '\0');
    plVar14[199] = 0;
    Aska::FastCriticalSection::FastCriticalSection()(plVar14 + 200);
    lVar18 = _UNK_02971f58;
    lVar20 = _UNK_02971f50;
    *(undefined4 *)(plVar14 + 0xda) = 0;
    plVar14[0xdc] = lVar18;
    plVar14[0xdb] = lVar20;
    plVar14[0xe3] = 0;
    plVar14[0xe2] = 0;
    plVar14[0xe1] = 0;
    plVar14[0xe0] = 0;
    plVar14[0xdf] = 0;
    puVar1 = PTR__ZTVN4Aska9TDelegateINS_18AaoStreamingStreamEEE_02cbe878;
    plVar14[0xde] = 0;
    plVar14[0xdd] = 0;
    puVar2 = PTR__ZN4Aska18AaoStreamingStream16LoopBackDelegateEPv_02cc14f0;
    *(undefined1 *)(plVar14 + 0xe5) = 0;
    *(undefined1 *)((long)plVar14 + 0x729) = 0;
    *(undefined4 *)(plVar14 + 0xe4) = 0;
    *(undefined4 *)((long)plVar14 + 0x724) = 0;
    plVar14[0xef] = 0;
    plVar14[0xee] = 0;
    puVar4 = PTR__ZN4Aska18AaoStreamingStream17LoopFrontDelegateEPv_02cb6bf8;
    *(undefined2 *)((long)plVar14 + 0x72a) = 0;
    plVar14[0xe6] = (long)(puVar1 + 0x10);
    plVar14[0xea] = (long)(puVar1 + 0x10);
    plVar14[0xe7] = (long)plVar14;
    plVar14[0xe9] = 0;
    plVar14[0xe8] = (long)puVar4;
    plVar14[0xeb] = (long)plVar14;
    plVar14[0xed] = 0;
    plVar14[0xec] = (long)puVar2;
    lVar20 = *(long *)(param_1 + 0xb0);
  }
  if (lVar20 == 0) goto code_r0x0207499c;
  iVar12 = Aska::SoundUtility::CalcLoopCount(int, int)(*(undefined4 *)(param_1 + 0x9c),
                           *(undefined4 *)
                            ((ulong)*(uint *)(*(long *)(param_1 + 0x38) + 0x14) +
                             *(long *)(param_1 + 0x38) + 0x10));
  uVar13 = Aska::SoundUtility::CalcLoopAndOffset(unsigned int*, unsigned int*, unsigned int*, Aska::AFF::AaoWAVE const*, unsigned int)(&uStack_34,&uStack_38,auStack_44,lVar17,*(undefined4 *)(param_1 + 0x84));
  if (((((uVar13 & 1) != 0) && (*(char *)(lVar17 + 0x14) != '\v')) &&
      (*(char *)(lVar17 + 0x14) != '\x02')) &&
     (uVar13 = Aska::AaoStreamingStream::Open(unsigned long, bool, unsigned long, unsigned long, unsigned long, unsigned long, long, unsigned long, unsigned long, bool)(*(undefined8 *)(param_1 + 0xb0),
                               *(undefined8 *)(*(long *)(param_1 + 0x60) + 0x20),
                               *(byte *)(param_1 + 0xe0) & 1,uVar19,uVar8,*(int *)(lVar17 + 0x30),
                               *(int *)(lVar17 + 0x1c) + *(int *)(lVar17 + 0x30),(long)iVar12,
                               uStack_34,uStack_38,*(undefined1 *)(param_1 + 0xa8)),
     (uVar13 & 1) != 0)) {
    uVar5 = 0;
    if (uVar8 != 0) {
      uVar5 = uVar19 / uVar8;
    }
    *(uint *)(param_1 + 0xb8) = uVar5;
    *(undefined4 *)(param_1 + 0x1c) = 2;
    sVar7 = *(short *)(*(long *)(param_1 + 0x38) + 0x1e);
code_r0x020747a0:
    uVar16 = 5;
    if (sVar7 == -1) {
      uVar16 = 6;
    }
    *(undefined4 *)(param_1 + 0x18) = uVar16;
    return false;
  }
code_r0x02074984:
  if (*(long **)(param_1 + 0xb0) != (long *)0x0) {
    (**(code **)(**(long **)(param_1 + 0xb0) + 8))();
  }
code_r0x02074998:
  *(undefined8 *)(param_1 + 0xb0) = 0;
  goto code_r0x0207499c;
code_r0x020747b4:
  *(undefined4 *)(lVar20 + 0x1e4) = 4;
code_r0x020747bc:
  if (*(long *)(param_1 + 0xb0) == 0) {
    lVar17 = *(long *)(param_1 + 0x38);
    uVar19 = *(uint *)(lVar17 + 0x18);
    plVar14 = (long *)Aska::SoundMemory::Malloc(unsigned long)(0xe0);
    *(long **)(param_1 + 0xb0) = plVar14;
    lVar20 = 0;
    if (plVar14 != (long *)0x0) {
      plVar14[1] = (long)(PTR__ZTVN4Aska6TQueueIiLi8EEE_02cbf310 + 0x10);
      *(undefined4 *)(plVar14 + 2) = 1;
      puVar4 = PTR__ZTVN4Aska17AaoOnMemoryStreamE_02cb8908;
      *(undefined4 *)((long)plVar14 + 0x14) = 0;
      plVar14[0xe] = 0;
      plVar14[0xb] = 0;
      plVar14[10] = 0;
      plVar14[0xd] = 0;
      plVar14[0xc] = 0;
      plVar14[9] = 0;
      plVar14[8] = 0;
      *(undefined4 *)(plVar14 + 0x11) = 0;
      *plVar14 = (long)(puVar4 + 0x10);
      puVar4 = PTR__ZTVN4Aska12StaticStreamE_02cba478;
      *(undefined1 *)((long)plVar14 + 0x8e) = 0;
      *(undefined2 *)((long)plVar14 + 0x8c) = 0;
      plVar14[0x10] = 0;
      plVar14[0xf] = 0;
      plVar14[0x12] = (long)(puVar4 + 0x10);
      plVar14[0x19] = 0;
      plVar14[0x18] = 0;
      plVar14[0x17] = 0;
      plVar14[0x16] = 0;
      plVar14[0x15] = 0;
      plVar14[0x14] = 0;
      plVar14[0x13] = 0;
      *(undefined4 *)(plVar14 + 0x1a) = 0;
      plVar14[0x1b] = 0;
      lVar20 = *(long *)(param_1 + 0xb0);
    }
    if (lVar20 == 0) goto code_r0x0207499c;
    lVar17 = (ulong)uVar19 + lVar17;
    iVar12 = Aska::SoundUtility::CalcLoopCount(int, int)(*(undefined4 *)(param_1 + 0x9c),
                             *(undefined4 *)
                              ((ulong)*(uint *)(*(long *)(param_1 + 0x38) + 0x14) +
                               *(long *)(param_1 + 0x38) + 0x10));
    uVar13 = Aska::SoundUtility::CalcLoopAndOffset(unsigned int*, unsigned int*, unsigned int*, Aska::AFF::AaoWAVE const*, unsigned int)(&uStack_34,&uStack_38,auStack_44,lVar17,*(undefined4 *)(param_1 + 0x84)
                            );
    plVar14 = *(long **)(param_1 + 0xb0);
    if ((uVar13 & 1) == 0) {
      if (plVar14 != (long *)0x0) {
        (**(code **)(*plVar14 + 8))(plVar14);
      }
      goto code_r0x02074998;
    }
    uVar13 = Aska::AaoOnMemoryStream::Open(void const*, unsigned long, long, unsigned long, unsigned long)(plVar14,*(undefined8 *)(param_1 + 0x48),*(undefined4 *)(lVar17 + 0x1c),
                             (long)iVar12,uStack_34,uStack_38);
    if ((uVar13 & 1) == 0) goto code_r0x02074984;
    *(undefined4 *)(param_1 + 0xb8) = 0;
  }
  uVar15 = Aska::AacHandler::GetAaoHandler(unsigned int)(*(undefined8 *)(param_1 + 0x60),*(undefined4 *)(param_1 + 0x2c));
  uVar13 = Aska::AaoHandler::CreateThis(void const*, void const*, void const*, void const*, bool)(uVar15,*(undefined8 *)(param_1 + 0x38),*(undefined8 *)(param_1 + 0x40),
                           *(undefined8 *)(param_1 + 0x48),*(undefined8 *)(param_1 + 0x50),
                           *(byte *)(param_1 + 0xe0) >> 1 & 1);
  if (((uVar13 & 1) != 0) && (plVar14 = (long *)Aska::SoundMemory::Malloc(unsigned long)(0x128), plVar14 != (long *)0x0)) {
    Aska::WavePlayer::WavePlayer()(plVar14);
    uVar13 = Aska::WavePlayer::SetAaoHandler(Aska::AaoHandler*, Aska::DirectPlaybackSettings const*, Aska::MultiMediaStream const*, unsigned int)(plVar14,uVar15,param_1 + 0x78,*(undefined8 *)(param_1 + 0xb0),
                             *(undefined4 *)(param_1 + 0xb8));
    *(undefined8 *)(param_1 + 0xb0) = 0;
    if ((uVar13 & 1) == 0) {
      (**(code **)(*plVar14 + 8))(plVar14);
    }
    else {
      *(long **)(param_1 + 0x68) = plVar14;
      uVar13 = (**(code **)(**(long **)(param_1 + 0x58) + 0x48))
                         (*(long **)(param_1 + 0x58),*(undefined4 *)(param_1 + 0x70),plVar14,
                          param_1 + 0x78);
      if ((uVar13 & 1) != 0) {
        iVar12 = 7;
        *(undefined4 *)(param_1 + 0x18) = 7;
code_r0x02074854:
        return iVar12 == 7;
      }
    }
  }
code_r0x0207499c:
  Aska::SoundPass::ErrorHandler()(param_1);
  return true;
}

// ==== Aska::SoundPass::LoadAsync(unsigned long, bool, void*, unsigned int, unsigned int, bool)
// vaddr 0x1f749c0 | ghidra 0x20749c0 | size 120 | symbol _ZN4Aska9SoundPass9LoadAsyncEmbPvjjb | lib libSOA-3.7.0.so | 2026-10-08
uint _ZN4Aska9SoundPass9LoadAsyncEmbPvjjb
               (long param_1,undefined8 param_2,ulong param_3,undefined8 param_4,undefined4 param_5,
               undefined4 param_6,byte param_7)

{
  uint uVar1;
  
  *(undefined1 *)(param_1 + 0xd8) = 0;
  if ((param_3 & 1) == 0) {
    uVar1 = Aska::FileReadManager::Read(int, unsigned char*, Aska::INotify*, unsigned long, unsigned long, int, int, bool)(*(undefined8 *)PTR__ZN4Aska6Global18m_pFileReadManagerE_02cbf970,param_2
                            ,param_4,param_1 + 200,param_5,param_6,0,0,0);
  }
  else {
    uVar1 = Aska::FileReadManager::Read(char const*, unsigned char*, Aska::INotify*, unsigned long, unsigned long, int, int, bool, bool)(*(undefined8 *)PTR__ZN4Aska6Global18m_pFileReadManagerE_02cbf970,param_2
                            ,param_4,param_1 + 200,param_5,param_6,0,0,0,param_7 & 1);
  }
  return uVar1 & 1;
}

// ==== Aska::SoundPass::StopLowestPriority(Aska::AnimatableList*, unsigned int, short, bool)
// vaddr 0x1f74a38 | ghidra 0x2074a38 | size 244 | symbol _ZN4Aska9SoundPass18StopLowestPriorityEPNS_14AnimatableListEjsb | lib libSOA-3.7.0.so | 2026-10-08
byte _ZN4Aska9SoundPass18StopLowestPriorityEPNS_14AnimatableListEjsb
               (undefined8 param_1,long param_2,uint param_3,short param_4,byte param_5)

{
  byte bVar1;
  short sVar2;
  bool bVar3;
  ulong uVar4;
  uint uVar5;
  long lVar6;
  long lVar7;
  short sVar8;
  
  lVar7 = *(long *)(param_2 + 0x18);
  param_2 = param_2 + 8;
  if (param_2 == lVar7) {
    sVar8 = 0xff;
    if (param_3 != 0) {
      return 1;
    }
  }
  else {
    uVar5 = 0;
    sVar8 = 0xff;
    lVar6 = lVar7;
    do {
      sVar2 = sVar8;
      if ((*(uint *)(lVar6 + 0x1e4) & 0xfffffffe) != 4) {
        uVar5 = uVar5 + 1;
        sVar2 = *(short *)(lVar6 + 0x1f0);
        if (sVar8 <= *(short *)(lVar6 + 0x1f0)) {
          sVar2 = sVar8;
        }
      }
      sVar8 = sVar2;
      lVar6 = *(long *)(lVar6 + 0x10);
    } while (param_2 != lVar6);
    if (uVar5 < param_3) {
      return 1;
    }
  }
  bVar3 = sVar8 == param_4;
  bVar1 = sVar8 <= param_4 & (!bVar3 | param_5 ^ 1);
  if (!bVar3 && param_4 <= sVar8 || (bVar3 & param_5) != 0) {
    return bVar1;
  }
  if (param_2 != lVar7) {
    while ((((*(uint *)(lVar7 + 0x1e4) & 0xfffffffe) == 4 || (sVar8 != *(short *)(lVar7 + 0x1f0)))
           || (uVar4 = Aska::SoundObject::Stop(unsigned int)(lVar7,200), (uVar4 & 1) == 0))) {
      lVar7 = *(long *)(lVar7 + 0x10);
      if (param_2 == lVar7) {
        return 1;
      }
    }
    *(undefined4 *)(lVar7 + 0x1e4) = 4;
    return 1;
  }
  return bVar1;
}

// ==== Aska::SoundPass::ErrorHandler()
// vaddr 0x1f74b2c | ghidra 0x2074b2c | size 400 | symbol _ZN4Aska9SoundPass12ErrorHandlerEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska9SoundPass12ErrorHandlerEv(long param_1)

{
  long lVar1;
  long lVar2;
  
  if (*(long *)(*(long *)(param_1 + 0x58) + 0x128) != 0) goto code_r0x02074b44;
  if (*(long **)(param_1 + 0x68) != (long *)0x0) {
    (**(code **)(**(long **)(param_1 + 0x68) + 8))();
    *(undefined8 *)(param_1 + 0x68) = 0;
    if (*(long **)(param_1 + 0xb0) != (long *)0x0) {
      (**(code **)(**(long **)(param_1 + 0xb0) + 8))();
      *(undefined8 *)(param_1 + 0xb0) = 0;
    }
    goto code_r0x02074b44;
  }
  if (*(long *)(param_1 + 0x60) == 0) {
    if ((*(byte *)(param_1 + 0x70) >> 2 & 1) == 0) {
      Aska::SoundMemory::ResourceFree(void*)(*(undefined8 *)(param_1 + 0x30));
      *(undefined8 *)(param_1 + 0x30) = 0;
    }
    if (((*(byte *)(param_1 + 0xe0) & 1) != 0) && (*(long *)(param_1 + 0x20) != 0)) {
      Aska::SoundServer::ReleaseFilePathBuffer(char*)(*(undefined8 *)
                       (*(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50 + 0xe8));
      *(undefined8 *)(param_1 + 0x20) = 0;
    }
    goto code_r0x02074b44;
  }
  lVar1 = Aska::AacHandler::GetAaoHandler(unsigned int)(*(long *)(param_1 + 0x60),*(undefined4 *)(param_1 + 0x2c));
  if (lVar1 == 0) {
code_r0x02074c90:
    if (*(long *)(param_1 + 0xc0) != 0) {
      operator delete[](void*)();
      *(undefined8 *)(param_1 + 0xc0) = 0;
    }
  }
  else {
    if ((*(byte *)(*(long *)(param_1 + 0x60) + 0x2c) >> 1 & 1) == 0) {
      if (*(long *)(lVar1 + 0x88) == 0) {
        Aska::SoundMemory::ResourceFree(void*)(*(undefined8 *)(param_1 + 0x50));
        *(undefined8 *)(param_1 + 0x50) = 0;
      }
      if ((*(byte *)(param_1 + 0xe0) >> 1 & 1) != 0) {
        if ((*(long **)(param_1 + 0xb0) != (long *)0x0) &&
           (((((*(byte *)(*(long *)(param_1 + 0x58) + 0x1e8) >> 3 & 1) == 0 ||
              (lVar2 = *(long *)(*(long *)(param_1 + 0x58) + 0x128), lVar2 == 0)) ||
             (lVar2 = *(long *)(lVar2 + 0x118), lVar2 == 0)) ||
            (*(long *)(*(long *)(lVar2 + 0x30) + 8) == 0)))) {
          (**(code **)(**(long **)(param_1 + 0xb0) + 8))();
          *(undefined8 *)(param_1 + 0xb0) = 0;
        }
        goto code_r0x02074c88;
      }
      if (*(long *)(lVar1 + 0x90) != 0) goto code_r0x02074c88;
      Aska::SoundMemory::ResourceFree(void*)(*(undefined8 *)(param_1 + 0x48));
      *(undefined8 *)(param_1 + 0x48) = 0;
      lVar1 = *(long *)(lVar1 + 0xa0);
    }
    else {
code_r0x02074c88:
      lVar1 = *(long *)(lVar1 + 0xa0);
    }
    if (lVar1 == 0) goto code_r0x02074c90;
  }
  if (*(long **)(param_1 + 0x60) != (long *)0x0) {
    (**(code **)(**(long **)(param_1 + 0x60) + 8))();
  }
  *(undefined8 *)(param_1 + 0x60) = 0;
code_r0x02074b44:
  Aska::SoundManager::DeleteSoundObject(Aska::SoundObject*, bool)(*(undefined8 *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50,
                  *(undefined8 *)(param_1 + 0x58),*(undefined1 *)(param_1 + 0x97));
  *(undefined8 *)(param_1 + 0x58) = 0;
  *(undefined4 *)(param_1 + 0x18) = 8;
  return;
}

// ==== Aska::SoundPass::LoadEndNotify::Handler(unsigned long)
// vaddr 0x1f74cbc | ghidra 0x2074cbc | size 12 | symbol _ZN4Aska9SoundPass13LoadEndNotify7HandlerEm | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska9SoundPass13LoadEndNotify7HandlerEm(long param_1)

{
  *(undefined1 *)(param_1 + 0x10) = 1;
  return;
}

// ==== Aska::SoundPass::LoadEndNotify::~LoadEndNotify()
// vaddr 0x1f74cc8 | ghidra 0x2074cc8 | size 4 | symbol _ZN4Aska9SoundPass13LoadEndNotifyD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska9SoundPass13LoadEndNotifyD0Ev(void)

{
  (*(code *)PTR__ZdlPv_02ca4758)();
  return;
}

// ==== Aska::SoundServer::AcquireSoundObject(unsigned int)
// vaddr 0x1f75280 | ghidra 0x2075280 | size 48 | symbol _ZN4Aska11SoundServer18AcquireSoundObjectEj | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska11SoundServer18AcquireSoundObjectEj(undefined8 param_1,uint param_2)

{
  undefined8 uVar1;
  
  if ((param_2 & 1) != 0) {
    uVar1 = Aska::SoundServer::AcquireSEObject()();
    return uVar1;
  }
  if ((param_2 >> 1 & 1) == 0) {
    return 0;
  }
  uVar1 = Aska::SoundServer::AcquireBGMObject()();
  return uVar1;
}

// ==== Aska::SoundServer::AcquireSEObject()
// vaddr 0x1f752b0 | ghidra 0x20752b0 | size 216 | symbol _ZN4Aska11SoundServer15AcquireSEObjectEv | lib libSOA-3.7.0.so | 2026-10-08
long _ZN4Aska11SoundServer15AcquireSEObjectEv(long param_1)

{
  uint uVar1;
  uint uVar2;
  long lVar3;
  long lVar4;
  uint uVar5;
  ulong uVar6;
  ulong uVar7;
  ulong uVar8;
  
  if (*(uint *)(param_1 + 0x44) < *(uint *)(param_1 + 0x34)) {
    lVar4 = *(long *)(param_1 + 0x28);
    uVar2 = *(uint *)(param_1 + 0x40);
    do {
      uVar5 = uVar2;
      if (*(uint *)(param_1 + 0x34) <= uVar5) {
        uVar5 = 0;
      }
      uVar1 = 1 << (ulong)(uVar5 & 0x1f);
      uVar2 = uVar5 + 1;
    } while ((uVar1 & *(uint *)(lVar4 + (ulong)(uVar5 >> 5) * 4)) != 0);
    uVar6 = *(long *)(param_1 + 0x48) + (ulong)uVar5 * 0x340;
    uVar7 = uVar6;
    do {
      uVar8 = uVar7 + 0x7f & 0xffffffffffffff81;
      Hint_Prefetch(uVar7,0,2,0);
      uVar7 = uVar8;
    } while (uVar8 < uVar6 + 0x340);
    *(uint *)(param_1 + 0x40) = uVar5 + 1;
    *(uint *)(param_1 + 0x44) = *(uint *)(param_1 + 0x44) + 1;
    lVar3 = (ulong)(uVar5 >> 5) * 4;
    *(uint *)(lVar4 + lVar3) = *(uint *)(lVar4 + lVar3) | uVar1;
    Aska::SEControlObject::SEControlObject()(*(long *)(param_1 + 0x48) + (ulong)uVar5 * 0x340);
    lVar4 = *(long *)(param_1 + 0x48) + (ulong)uVar5 * 0x340;
    if (lVar4 != 0) {
      return lVar4;
    }
  }
  lVar4 = Aska::SoundMemory::Malloc(unsigned long)(0x340);
  if (lVar4 != 0) {
    Aska::SEControlObject::SEControlObject()(lVar4);
  }
  return lVar4;
}

// ==== Aska::SoundServer::AcquireBGMObject()
// vaddr 0x1f75388 | ghidra 0x2075388 | size 216 | symbol _ZN4Aska11SoundServer16AcquireBGMObjectEv | lib libSOA-3.7.0.so | 2026-10-08
long _ZN4Aska11SoundServer16AcquireBGMObjectEv(long param_1)

{
  uint uVar1;
  uint uVar2;
  long lVar3;
  long lVar4;
  uint uVar5;
  ulong uVar6;
  ulong uVar7;
  ulong uVar8;
  
  if (*(uint *)(param_1 + 0x94) < *(uint *)(param_1 + 0x84)) {
    lVar4 = *(long *)(param_1 + 0x78);
    uVar2 = *(uint *)(param_1 + 0x90);
    do {
      uVar5 = uVar2;
      if (*(uint *)(param_1 + 0x84) <= uVar5) {
        uVar5 = 0;
      }
      uVar1 = 1 << (ulong)(uVar5 & 0x1f);
      uVar2 = uVar5 + 1;
    } while ((uVar1 & *(uint *)(lVar4 + (ulong)(uVar5 >> 5) * 4)) != 0);
    uVar6 = *(long *)(param_1 + 0x98) + (ulong)uVar5 * 0x230;
    uVar7 = uVar6;
    do {
      uVar8 = uVar7 + 0x7f & 0xffffffffffffff81;
      Hint_Prefetch(uVar7,0,2,0);
      uVar7 = uVar8;
    } while (uVar8 < uVar6 + 0x230);
    *(uint *)(param_1 + 0x90) = uVar5 + 1;
    *(uint *)(param_1 + 0x94) = *(uint *)(param_1 + 0x94) + 1;
    lVar3 = (ulong)(uVar5 >> 5) * 4;
    *(uint *)(lVar4 + lVar3) = *(uint *)(lVar4 + lVar3) | uVar1;
    Aska::BGMControlObject::BGMControlObject()(*(long *)(param_1 + 0x98) + (ulong)uVar5 * 0x230);
    lVar4 = *(long *)(param_1 + 0x98) + (ulong)uVar5 * 0x230;
    if (lVar4 != 0) {
      return lVar4;
    }
  }
  lVar4 = Aska::SoundMemory::Malloc(unsigned long)(0x230);
  if (lVar4 != 0) {
    Aska::BGMControlObject::BGMControlObject()(lVar4);
  }
  return lVar4;
}

// ==== Aska::SoundServer::ReleaseSoundObject(Aska::SoundObject*)
// vaddr 0x1f75460 | ghidra 0x2075460 | size 336 | symbol _ZN4Aska11SoundServer18ReleaseSoundObjectEPNS_11SoundObjectE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska11SoundServer18ReleaseSoundObjectEPNS_11SoundObjectE(long param_1,long *param_2)

{
  long *plVar1;
  long lVar2;
  ulong uVar3;
  
  if ((*(uint *)(param_2 + 0x3d) & 1) == 0) {
    if ((*(uint *)(param_2 + 0x3d) >> 1 & 1) != 0) {
      plVar1 = *(long **)(param_1 + 0x98);
      if (((plVar1 == (long *)0x0) || (param_2 < plVar1)) ||
         (plVar1 + (ulong)*(uint *)(param_1 + 0x84) * 0x46 <= param_2)) goto code_r0x02075598;
      uVar3 = ((long)param_2 - (long)plVar1 >> 4) * -0x5075075075075075;
      (**(code **)plVar1[(uVar3 & 0xffffffff) * 0x46])();
      lVar2 = (uVar3 >> 5 & 0x7ffffff) * 4;
      *(uint *)(*(long *)(param_1 + 0x78) + lVar2) =
           *(uint *)(*(long *)(param_1 + 0x78) + lVar2) &
           (1 << (ulong)((uint)uVar3 & 0x1f) ^ 0xffffffffU);
      *(int *)(param_1 + 0x94) = *(int *)(param_1 + 0x94) + -1;
    }
  }
  else {
    plVar1 = *(long **)(param_1 + 0x48);
    if (((plVar1 == (long *)0x0) || (param_2 < plVar1)) ||
       (plVar1 + (ulong)*(uint *)(param_1 + 0x34) * 0x68 <= param_2)) {
code_r0x02075598:
                    /* WARNING: Could not recover jumptable at 0x020755ac. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (**(code **)(*param_2 + 8))(param_2);
      return;
    }
    uVar3 = ((long)param_2 - (long)plVar1 >> 6) * 0x4ec4ec4ec4ec4ec5;
    (**(code **)plVar1[(uVar3 & 0xffffffff) * 0x68])();
    lVar2 = (uVar3 >> 5 & 0x7ffffff) * 4;
    *(uint *)(*(long *)(param_1 + 0x28) + lVar2) =
         *(uint *)(*(long *)(param_1 + 0x28) + lVar2) &
         (1 << (ulong)((uint)uVar3 & 0x1f) ^ 0xffffffffU);
    *(int *)(param_1 + 0x44) = *(int *)(param_1 + 0x44) + -1;
  }
  return;
}

// ==== Aska::SoundServer::ReleaseSEObject(Aska::SEControlObject*)
// vaddr 0x1f755b0 | ghidra 0x20755b0 | size 192 | symbol _ZN4Aska11SoundServer15ReleaseSEObjectEPNS_15SEControlObjectE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska11SoundServer15ReleaseSEObjectEPNS_15SEControlObjectE(long param_1,long *param_2)

{
  long *plVar1;
  long lVar2;
  ulong uVar3;
  
  plVar1 = *(long **)(param_1 + 0x48);
  if (((plVar1 == (long *)0x0) || (param_2 < plVar1)) ||
     (plVar1 + (ulong)*(uint *)(param_1 + 0x34) * 0x68 <= param_2)) {
    if (param_2 != (long *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x02075660. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (**(code **)(*param_2 + 8))(param_2);
      return;
    }
  }
  else {
    uVar3 = ((long)param_2 - (long)plVar1 >> 6) * 0x4ec4ec4ec4ec4ec5;
    (**(code **)plVar1[(uVar3 & 0xffffffff) * 0x68])();
    lVar2 = (uVar3 >> 5 & 0x7ffffff) * 4;
    *(uint *)(*(long *)(param_1 + 0x28) + lVar2) =
         *(uint *)(*(long *)(param_1 + 0x28) + lVar2) &
         (1 << (ulong)((uint)uVar3 & 0x1f) ^ 0xffffffffU);
    *(int *)(param_1 + 0x44) = *(int *)(param_1 + 0x44) + -1;
  }
  return;
}

// ==== Aska::SoundServer::ReleaseBGMObject(Aska::BGMControlObject*)
// vaddr 0x1f75670 | ghidra 0x2075670 | size 192 | symbol _ZN4Aska11SoundServer16ReleaseBGMObjectEPNS_16BGMControlObjectE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska11SoundServer16ReleaseBGMObjectEPNS_16BGMControlObjectE(long param_1,long *param_2)

{
  long *plVar1;
  long lVar2;
  ulong uVar3;
  
  plVar1 = *(long **)(param_1 + 0x98);
  if (((plVar1 == (long *)0x0) || (param_2 < plVar1)) ||
     (plVar1 + (ulong)*(uint *)(param_1 + 0x84) * 0x46 <= param_2)) {
    if (param_2 != (long *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x02075720. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (**(code **)(*param_2 + 8))(param_2);
      return;
    }
  }
  else {
    uVar3 = ((long)param_2 - (long)plVar1 >> 4) * -0x5075075075075075;
    (**(code **)plVar1[(uVar3 & 0xffffffff) * 0x46])();
    lVar2 = (uVar3 >> 5 & 0x7ffffff) * 4;
    *(uint *)(*(long *)(param_1 + 0x78) + lVar2) =
         *(uint *)(*(long *)(param_1 + 0x78) + lVar2) &
         (1 << (ulong)((uint)uVar3 & 0x1f) ^ 0xffffffffU);
    *(int *)(param_1 + 0x94) = *(int *)(param_1 + 0x94) + -1;
  }
  return;
}

// ==== Aska::SoundServer::AcquireSoundHandle()
// vaddr 0x1f75730 | ghidra 0x2075730 | size 220 | symbol _ZN4Aska11SoundServer18AcquireSoundHandleEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska11SoundServer18AcquireSoundHandleEv(long param_1)

{
  ulong uVar1;
  uint uVar2;
  undefined *puVar3;
  uint uVar4;
  long *plVar5;
  long lVar6;
  uint uVar7;
  long lVar8;
  ulong uVar9;
  ulong uVar10;
  
  if (*(uint *)(param_1 + 0x134) < *(uint *)(param_1 + 0x124)) {
    lVar6 = *(long *)(param_1 + 0x118);
    uVar4 = *(uint *)(param_1 + 0x130);
    do {
      uVar7 = uVar4;
      if (*(uint *)(param_1 + 0x124) <= uVar7) {
        uVar7 = 0;
      }
      uVar2 = 1 << (ulong)(uVar7 & 0x1f);
      uVar4 = uVar7 + 1;
    } while ((uVar2 & *(uint *)(lVar6 + (ulong)(uVar7 >> 5) * 4)) != 0);
    uVar1 = *(long *)(param_1 + 0x138) + (ulong)uVar7 * 0x20;
    uVar9 = uVar1;
    do {
      uVar10 = uVar9 + 0x7f & 0xffffffffffffff81;
      Hint_Prefetch(uVar9,0,2,0);
      uVar9 = uVar10;
    } while (uVar10 < uVar1 + 0x20);
    *(uint *)(param_1 + 0x130) = uVar7 + 1;
    lVar8 = (ulong)(uVar7 >> 5) * 4;
    *(uint *)(param_1 + 0x134) = *(uint *)(param_1 + 0x134) + 1;
    *(uint *)(lVar6 + lVar8) = *(uint *)(lVar6 + lVar8) | uVar2;
    lVar6 = (ulong)uVar7 * 0x20;
    plVar5 = (long *)(*(long *)(param_1 + 0x138) + lVar6);
    *plVar5 = (long)(PTR__ZTVN4Aska11SoundHandleE_02cbf3a8 + 0x10);
    plVar5[1] = 0;
    plVar5[2] = 0;
    plVar5[3] = 0;
    if (*(long *)(param_1 + 0x138) + lVar6 != 0) {
      return;
    }
  }
  plVar5 = (long *)Aska::SoundMemory::Malloc(unsigned long)(0x20);
  puVar3 = PTR__ZTVN4Aska11SoundHandleE_02cbf3a8;
  if (plVar5 != (long *)0x0) {
    plVar5[2] = 0;
    plVar5[3] = 0;
    *plVar5 = (long)(puVar3 + 0x10);
    plVar5[1] = 0;
  }
  return;
}

// ==== Aska::SoundServer::ReleaseSoundHandle(Aska::SoundHandle*)
// vaddr 0x1f7580c | ghidra 0x207580c | size 160 | symbol _ZN4Aska11SoundServer18ReleaseSoundHandleEPNS_11SoundHandleE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska11SoundServer18ReleaseSoundHandleEPNS_11SoundHandleE(long param_1,long *param_2)

{
  long *plVar1;
  long lVar2;
  ulong uVar3;
  
  plVar1 = *(long **)(param_1 + 0x138);
  if (((plVar1 == (long *)0x0) || (param_2 < plVar1)) ||
     (plVar1 + (ulong)*(uint *)(param_1 + 0x124) * 4 <= param_2)) {
    if (param_2 != (long *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x0207589c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (**(code **)(*param_2 + 8))(param_2);
      return;
    }
  }
  else {
    uVar3 = (long)param_2 - (long)plVar1;
    (**(code **)plVar1[(uVar3 >> 5 & 0xffffffff) * 4])();
    lVar2 = (uVar3 >> 10 & 0x7ffffff) * 4;
    *(uint *)(*(long *)(param_1 + 0x118) + lVar2) =
         *(uint *)(*(long *)(param_1 + 0x118) + lVar2) & (1 << (uVar3 >> 5 & 0x1f) ^ 0xffffffffU);
    *(int *)(param_1 + 0x134) = *(int *)(param_1 + 0x134) + -1;
  }
  return;
}

// ==== Aska::SoundServer::AcquireMessageNote()
// vaddr 0x1f758ac | ghidra 0x20758ac | size 528 | symbol _ZN4Aska11SoundServer18AcquireMessageNoteEv | lib libSOA-3.7.0.so | 2026-10-08
long * _ZN4Aska11SoundServer18AcquireMessageNoteEv(long param_1)

{
  int *piVar1;
  int *piVar2;
  uint uVar3;
  char cVar4;
  bool bVar5;
  undefined *puVar6;
  uint uVar7;
  long *plVar8;
  ulong uVar9;
  int iVar10;
  long lVar11;
  uint uVar12;
  long lVar13;
  ulong uVar14;
  ulong uVar15;
  
  piVar1 = (int *)(param_1 + 0x3f0);
  iVar10 = 0;
code_r0x020758c4:
  do {
    if (*piVar1 != -1) {
      ClearExclusiveLocal();
      bVar5 = iVar10 < 0x1ff;
      iVar10 = iVar10 + 1;
      if (bVar5) goto code_r0x020758c4;
      piVar2 = (int *)(param_1 + 0x3f4);
      do {
        cVar4 = '\x01';
        bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
        if (bVar5) {
          *piVar2 = *piVar2 + 1;
          cVar4 = ExclusiveMonitorsStatus();
        }
      } while (cVar4 != '\0');
      do {
        if (*piVar1 != -1) {
          ClearExclusiveLocal();
          do {
            uVar9 = Aska::Semaphore::IsReady() const(param_1 + 0x430);
            if ((uVar9 & 1) == 0) {
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
              Aska::Semaphore::Wait() const(param_1 + 0x430);
            }
            do {
              cVar4 = '\x01';
              bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
              if (bVar5) {
                *piVar2 = *piVar2 + 1;
                cVar4 = ExclusiveMonitorsStatus();
              }
            } while (cVar4 != '\0');
            while (*piVar1 == -1) {
              cVar4 = '\x01';
              bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
              if (bVar5) {
                *piVar1 = 0;
                cVar4 = ExclusiveMonitorsStatus();
              }
              if (cVar4 == '\0') goto code_r0x0207597c;
            }
            ClearExclusiveLocal();
          } while( true );
        }
        cVar4 = '\x01';
        bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
        if (bVar5) {
          *piVar1 = 0;
          cVar4 = ExclusiveMonitorsStatus();
        }
      } while (cVar4 != '\0');
code_r0x0207597c:
      do {
        cVar4 = '\x01';
        bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
        if (bVar5) {
          *piVar2 = *piVar2 + -1;
          cVar4 = ExclusiveMonitorsStatus();
        }
      } while (cVar4 != '\0');
code_r0x0207598c:
      DataMemoryBarrier(2,3);
      if (*(uint *)(param_1 + 0xe4) < *(uint *)(param_1 + 0xd4)) {
        lVar11 = *(long *)(param_1 + 200);
        uVar7 = *(uint *)(param_1 + 0xe0);
        do {
          uVar12 = uVar7;
          if (*(uint *)(param_1 + 0xd4) <= uVar12) {
            uVar12 = 0;
          }
          uVar3 = 1 << (ulong)(uVar12 & 0x1f);
          uVar7 = uVar12 + 1;
        } while ((uVar3 & *(uint *)(lVar11 + (ulong)(uVar12 >> 5) * 4)) != 0);
        uVar9 = *(long *)(param_1 + 0xe8) + (ulong)uVar12 * 0x40;
        uVar14 = uVar9;
        do {
          uVar15 = uVar14 + 0x7f & 0xffffffffffffff81;
          Hint_Prefetch(uVar14,0,2,0);
          uVar14 = uVar15;
        } while (uVar15 < uVar9 + 0x40);
        lVar13 = (ulong)(uVar12 >> 5) * 4;
        *(uint *)(param_1 + 0xe0) = uVar12 + 1;
        *(uint *)(param_1 + 0xe4) = *(uint *)(param_1 + 0xe4) + 1;
        *(uint *)(lVar11 + lVar13) = *(uint *)(lVar11 + lVar13) | uVar3;
        lVar11 = (ulong)uVar12 * 0x40;
        plVar8 = (long *)(*(long *)(param_1 + 0xe8) + lVar11);
        *plVar8 = (long)(PTR__ZTVN4Aska16AudioMessageNoteE_02cc20c8 + 0x10);
        plVar8[1] = 0;
        plVar8[2] = 0;
        plVar8[3] = 0;
        plVar8 = (long *)(*(long *)(param_1 + 0xe8) + lVar11);
        if (plVar8 != (long *)0x0) goto code_r0x02075a60;
      }
      plVar8 = (long *)Aska::SoundMemory::Malloc(unsigned long)(0x40);
      puVar6 = PTR__ZTVN4Aska16AudioMessageNoteE_02cc20c8;
      if (plVar8 != (long *)0x0) {
        plVar8[2] = 0;
        plVar8[3] = 0;
        *plVar8 = (long)(puVar6 + 0x10);
        plVar8[1] = 0;
      }
code_r0x02075a60:
      DataMemoryBarrier(2,3);
      *(undefined4 *)(param_1 + 0x3f0) = 0xffffffff;
      DataMemoryBarrier(2,3);
      if (0x14 < *(int *)(param_1 + 0x3f4)) {
        piVar1 = (int *)(param_1 + 0x3f4);
        do {
          cVar4 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar5) {
            *piVar1 = *piVar1 + -1;
            cVar4 = ExclusiveMonitorsStatus();
          }
        } while (cVar4 != '\0');
        uVar9 = Aska::Semaphore::IsReady() const(param_1 + 0x430);
        if ((uVar9 & 1) != 0) {
          Aska::Semaphore::Signal() const(param_1 + 0x430);
        }
      }
      return plVar8;
    }
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar5) {
      *piVar1 = 0;
      cVar4 = ExclusiveMonitorsStatus();
    }
    if (cVar4 == '\0') goto code_r0x0207598c;
  } while( true );
}

// ==== Aska::SoundServer::ReleaseMessageNote(Aska::AudioMessageNote*)
// vaddr 0x1f75abc | ghidra 0x2075abc | size 460 | symbol _ZN4Aska11SoundServer18ReleaseMessageNoteEPNS_16AudioMessageNoteE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska11SoundServer18ReleaseMessageNoteEPNS_16AudioMessageNoteE(long param_1,long *param_2)

{
  int *piVar1;
  int *piVar2;
  char cVar3;
  bool bVar4;
  int iVar5;
  long *plVar6;
  long lVar7;
  ulong uVar8;
  
  piVar1 = (int *)(param_1 + 0x3f0);
  iVar5 = 0;
  do {
    while (*piVar1 == -1) {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = 0;
        cVar3 = ExclusiveMonitorsStatus();
      }
      if (cVar3 == '\0') goto code_r0x02075ba0;
    }
    ClearExclusiveLocal();
    bVar4 = iVar5 < 0x1ff;
    iVar5 = iVar5 + 1;
  } while (bVar4);
  piVar2 = (int *)(param_1 + 0x3f4);
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
        uVar8 = Aska::Semaphore::IsReady() const(param_1 + 0x430);
        if ((uVar8 & 1) == 0) {
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
          Aska::Semaphore::Wait() const(param_1 + 0x430);
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
          if (cVar3 == '\0') goto code_r0x02075b90;
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
code_r0x02075b90:
  do {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar4) {
      *piVar2 = *piVar2 + -1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
code_r0x02075ba0:
  DataMemoryBarrier(2,3);
  plVar6 = *(long **)(param_1 + 0xe8);
  if (((plVar6 == (long *)0x0) || (param_2 < plVar6)) ||
     (plVar6 + (ulong)*(uint *)(param_1 + 0xd4) * 8 <= param_2)) {
    if (param_2 != (long *)0x0) {
      (**(code **)(*param_2 + 8))(param_2);
    }
  }
  else {
    uVar8 = (long)param_2 - (long)plVar6;
    (**(code **)plVar6[(uVar8 >> 6 & 0xffffffff) * 8])();
    lVar7 = (uVar8 >> 0xb & 0x7ffffff) * 4;
    *(uint *)(*(long *)(param_1 + 200) + lVar7) =
         *(uint *)(*(long *)(param_1 + 200) + lVar7) & (1 << (uVar8 >> 6 & 0x1f) ^ 0xffffffffU);
    *(int *)(param_1 + 0xe4) = *(int *)(param_1 + 0xe4) + -1;
  }
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_1 + 0x3f0) = 0xffffffff;
  DataMemoryBarrier(2,3);
  if (0x14 < *(int *)(param_1 + 0x3f4)) {
    piVar1 = (int *)(param_1 + 0x3f4);
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
    uVar8 = Aska::Semaphore::IsReady() const(param_1 + 0x430);
    if ((uVar8 & 1) != 0) {
      (*(code *)PTR__ZNK4Aska9Semaphore6SignalEv_02c96cd0)(param_1 + 0x430);
      return;
    }
  }
  return;
}

// ==== Aska::SoundServer::SoundServer()
// vaddr 0x1f75c88 | ghidra 0x2075c88 | size 532 | symbol _ZN4Aska11SoundServerC1Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska11SoundServerC2Ev(long *param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  undefined *puVar3;
  
  *(undefined4 *)(param_1 + 2) = 0;
  puVar3 = PTR__ZTVN4Aska11SoundServerE_02cbfa60;
  puVar2 = PTR__ZTVN4Aska11TPoolLegacyINS_15SEControlObjectELb0EEE_02cbe858;
  *(undefined4 *)(param_1 + 4) = 0;
  puVar1 = PTR__ZTVN4Aska9TBitArrayIjLb0EEE_02cba038;
  *(undefined1 *)(param_1 + 7) = 0;
  param_1[1] = (long)(puVar2 + 0x10);
  *param_1 = (long)(puVar3 + 0x10);
  *(undefined4 *)(param_1 + 0xc) = 0;
  puVar2 = PTR__ZTVN4Aska11TPoolLegacyINS_16BGMControlObjectELb0EEE_02cba3c8;
  *(undefined4 *)(param_1 + 0xe) = 0;
  *(undefined1 *)(param_1 + 0x11) = 0;
  *(undefined4 *)(param_1 + 0x16) = 0;
  param_1[0xb] = (long)(puVar2 + 0x10);
  puVar2 = PTR__ZTVN4Aska11TPoolLegacyINS_16AudioMessageNoteELb0EEE_02cc2ea0;
  *(undefined4 *)(param_1 + 0x18) = 0;
  *(undefined1 *)(param_1 + 0x1b) = 0;
  *(undefined4 *)(param_1 + 0x20) = 0;
  param_1[0x15] = (long)(puVar2 + 0x10);
  puVar2 = PTR__ZTVN4Aska11TPoolLegacyINS_11SoundHandleELb0EEE_02cc1b30;
  puVar1 = puVar1 + 0x10;
  *(undefined4 *)(param_1 + 0x22) = 0;
  param_1[0x1f] = (long)(puVar2 + 0x10);
  *(undefined1 *)(param_1 + 0x25) = 0;
  param_1[6] = 0;
  param_1[5] = 0;
  param_1[9] = 0;
  param_1[8] = 0;
  param_1[0x10] = 0;
  param_1[0xf] = 0;
  param_1[0x13] = 0;
  param_1[0x12] = 0;
  param_1[0x1a] = 0;
  param_1[0x19] = 0;
  param_1[0x1d] = 0;
  param_1[0x1c] = 0;
  param_1[3] = (long)puVar1;
  param_1[0xd] = (long)puVar1;
  param_1[0x17] = (long)puVar1;
  param_1[0x21] = (long)puVar1;
  param_1[0x24] = 0;
  param_1[0x23] = 0;
  puVar2 = PTR__ZTVN4Aska11TPoolLegacyINS_7SLVoiceELb0EEE_02cbe3d8;
  *(undefined4 *)(param_1 + 0x2a) = 0;
  param_1[0x27] = 0;
  param_1[0x26] = 0;
  *(undefined4 *)(param_1 + 0x2c) = 0;
  param_1[0x29] = (long)(puVar2 + 0x10);
  param_1[0x2b] = (long)puVar1;
  *(undefined1 *)(param_1 + 0x2f) = 0;
  param_1[0x2e] = 0;
  param_1[0x2d] = 0;
  puVar2 = PTR__ZTVN4Aska11TPoolLegacyINS_12SoundCommandELb0EEE_02cbc4e8;
  *(undefined4 *)(param_1 + 0x34) = 0;
  param_1[0x31] = 0;
  param_1[0x30] = 0;
  *(undefined4 *)(param_1 + 0x36) = 0;
  param_1[0x33] = (long)(puVar2 + 0x10);
  param_1[0x35] = (long)puVar1;
  *(undefined1 *)(param_1 + 0x39) = 0;
  param_1[0x38] = 0;
  param_1[0x37] = 0;
  puVar2 = PTR__ZTVN4Aska11TPoolLegacyINS_9SoundPassELb0EEE_02cbd7b0;
  *(undefined4 *)(param_1 + 0x3e) = 0;
  param_1[0x3b] = 0;
  param_1[0x3a] = 0;
  *(undefined4 *)(param_1 + 0x40) = 0;
  param_1[0x3d] = (long)(puVar2 + 0x10);
  param_1[0x3f] = (long)puVar1;
  *(undefined1 *)(param_1 + 0x43) = 0;
  param_1[0x42] = 0;
  param_1[0x41] = 0;
  puVar2 = PTR__ZTVN4Aska11TPoolLegacyINS_14AudioInterfaceELb0EEE_02cb87a8;
  *(undefined4 *)(param_1 + 0x48) = 0;
  param_1[0x45] = 0;
  param_1[0x44] = 0;
  *(undefined4 *)(param_1 + 0x4a) = 0;
  param_1[0x47] = (long)(puVar2 + 0x10);
  param_1[0x49] = (long)puVar1;
  *(undefined1 *)(param_1 + 0x4d) = 0;
  param_1[0x4c] = 0;
  param_1[0x4b] = 0;
  puVar2 = PTR__ZTVN4Aska11TPoolLegacyINS_11SoundServer21AskaAdpcmDecodeBufferELb0EEE_02cc1e68;
  *(undefined4 *)(param_1 + 0x52) = 0;
  param_1[0x4f] = 0;
  param_1[0x4e] = 0;
  *(undefined4 *)(param_1 + 0x54) = 0;
  param_1[0x51] = (long)(puVar2 + 0x10);
  param_1[0x53] = (long)puVar1;
  *(undefined1 *)(param_1 + 0x57) = 0;
  param_1[0x56] = 0;
  param_1[0x55] = 0;
  puVar2 = PTR__ZTVN4Aska11TPoolLegacyINS_11SoundServer14FilePathBufferELb0EEE_02cbe0c0;
  param_1[0x5d] = (long)puVar1;
  *(undefined4 *)(param_1 + 0x5c) = 0;
  param_1[0x5b] = (long)(puVar2 + 0x10);
  param_1[0x59] = 0;
  param_1[0x58] = 0;
  *(undefined4 *)(param_1 + 0x5e) = 0;
  *(undefined1 *)(param_1 + 0x61) = 0;
  param_1[0x60] = 0;
  param_1[0x5f] = 0;
  param_1[99] = 0;
  param_1[0x62] = 0;
  Aska::FastCriticalSection::FastCriticalSection()(param_1 + 0x65);
  Aska::FastCriticalSection::FastCriticalSection()(param_1 + 0x77);
  Aska::FastCriticalSection::FastCriticalSection()(param_1 + 0x89);
  Aska::FastCriticalSection::FastCriticalSection()(param_1 + 0x9b);
  memset(param_1 + 0xad,0,0xa1);
  return;
}

// ==== Aska::SoundServer::Initialize()
// vaddr 0x1f75e9c | ghidra 0x2075e9c | size 884 | symbol _ZN4Aska11SoundServer10InitializeEv | lib libSOA-3.7.0.so | 2026-10-08
undefined4 _ZN4Aska11SoundServer10InitializeEv(long param_1)

{
  int iVar1;
  int iVar2;
  long lVar3;
  ulong uVar4;
  undefined4 uVar5;
  ulong uVar6;
  ulong uVar7;
  undefined1 auStack_38 [8];
  
  if (*(char *)(param_1 + 0x608) != '\0') {
    return 0;
  }
  Aska::AppAudioCommonSettingProxy::AppAudioCommonSettingProxy()(auStack_38);
  iVar1 = Aska::AppAudioCommonSettingProxy::GetSoundObjectMax() const(auStack_38);
  iVar2 = Aska::AppAudioCommonSettingProxy::GetSoundPoolMargin() const(auStack_38);
  uVar6 = (ulong)((iVar1 + iVar2) - 2);
  lVar3 = Aska::SoundMemory::Malloc(unsigned long)(uVar6 * 0x340);
  *(long *)(param_1 + 0x568) = lVar3;
  if (lVar3 != 0) {
    lVar3 = Aska::SoundMemory::Malloc(unsigned long)(uVar6 + 0x1f >> 3 & 0x3ffffffc);
    *(long *)(param_1 + 0x570) = lVar3;
    if ((lVar3 != 0) &&
       (uVar6 = Aska::TPoolLegacy<Aska::SEControlObject, false>::SecurePool(unsigned int, bool, void const*, unsigned int const*)(param_1 + 8,uVar6,0,*(undefined8 *)(param_1 + 0x568),lVar3),
       (uVar6 & 1) != 0)) {
      lVar3 = Aska::SoundMemory::Malloc(unsigned long)(0x460);
      *(long *)(param_1 + 0x578) = lVar3;
      if (lVar3 != 0) {
        lVar3 = Aska::SoundMemory::Malloc(unsigned long)(4);
        *(long *)(param_1 + 0x580) = lVar3;
        if ((lVar3 != 0) &&
           (uVar6 = Aska::TPoolLegacy<Aska::BGMControlObject, false>::SecurePool(unsigned int, bool, void const*, unsigned int const*)(param_1 + 0x58,2,0,*(undefined8 *)(param_1 + 0x578),lVar3),
           (uVar6 & 1) != 0)) {
          uVar6 = (ulong)(uint)(iVar2 + iVar1);
          lVar3 = Aska::SoundMemory::Malloc(unsigned long)(uVar6 << 5);
          *(long *)(param_1 + 0x588) = lVar3;
          if (lVar3 != 0) {
            lVar3 = Aska::SoundMemory::Malloc(unsigned long)(uVar6 + 0x1f >> 3 & 0x3ffffffc);
            *(long *)(param_1 + 0x590) = lVar3;
            if ((lVar3 != 0) &&
               (uVar6 = Aska::TPoolLegacy<Aska::SoundHandle, false>::SecurePool(unsigned int, bool, void const*, unsigned int const*)(param_1 + 0xf8,uVar6,0,*(undefined8 *)(param_1 + 0x588),
                                        lVar3), (uVar6 & 1) != 0)) {
              uVar6 = (ulong)(iVar2 + 0x1b);
              lVar3 = Aska::SoundMemory::Malloc(unsigned long)(uVar6 << 6);
              *(long *)(param_1 + 0x598) = lVar3;
              if (lVar3 != 0) {
                uVar7 = uVar6 + 0x1f >> 3 & 0x3ffffffc;
                lVar3 = Aska::SoundMemory::Malloc(unsigned long)(uVar7);
                *(long *)(param_1 + 0x5a0) = lVar3;
                if ((lVar3 != 0) &&
                   (uVar4 = Aska::TPoolLegacy<Aska::AudioMessageNote, false>::SecurePool(unsigned int, bool, void const*, unsigned int const*)(param_1 + 0xa8,uVar6,0,*(undefined8 *)(param_1 + 0x598),
                                            lVar3), (uVar4 & 1) != 0)) {
                  uVar4 = (ulong)(iVar2 + 0x19);
                  lVar3 = Aska::SoundMemory::Malloc(unsigned long)(uVar4 * 0x648);
                  *(long *)(param_1 + 0x5b8) = lVar3;
                  if (lVar3 != 0) {
                    lVar3 = Aska::SoundMemory::Malloc(unsigned long)(uVar4 + 0x1f >> 3 & 0x3ffffffc);
                    *(long *)(param_1 + 0x5c0) = lVar3;
                    if ((lVar3 != 0) &&
                       (uVar4 = Aska::TPoolLegacy<Aska::SLVoice, false>::SecurePool(unsigned int, bool, void const*, unsigned int const*)(param_1 + 0x148,uVar4,0,
                                                *(undefined8 *)(param_1 + 0x5b8),lVar3),
                       (uVar4 & 1) != 0)) {
                      lVar3 = Aska::SoundMemory::Malloc(unsigned long)(uVar6 * 0xa8);
                      *(long *)(param_1 + 0x5a8) = lVar3;
                      if (lVar3 != 0) {
                        lVar3 = Aska::SoundMemory::Malloc(unsigned long)(uVar7);
                        *(long *)(param_1 + 0x5b0) = lVar3;
                        if ((lVar3 != 0) &&
                           (uVar4 = Aska::TPoolLegacy<Aska::SoundCommand, false>::SecurePool(unsigned int, bool, void const*, unsigned int const*)(param_1 + 0x198,uVar6,0,
                                                    *(undefined8 *)(param_1 + 0x5a8),lVar3),
                           (uVar4 & 1) != 0)) {
                          lVar3 = Aska::SoundMemory::Malloc(unsigned long)(uVar6 * 0xe8);
                          *(long *)(param_1 + 0x5c8) = lVar3;
                          if (lVar3 != 0) {
                            lVar3 = Aska::SoundMemory::Malloc(unsigned long)(uVar7);
                            *(long *)(param_1 + 0x5d0) = lVar3;
                            if ((lVar3 != 0) &&
                               (uVar6 = Aska::TPoolLegacy<Aska::SoundPass, false>::SecurePool(unsigned int, bool, void const*, unsigned int const*)(param_1 + 0x1e8,uVar6,0,
                                                        *(undefined8 *)(param_1 + 0x5c8),lVar3),
                               (uVar6 & 1) != 0)) {
                              uVar6 = (ulong)(iVar2 + 0x39);
                              lVar3 = Aska::SoundMemory::Malloc(unsigned long)(uVar6 * 0x28);
                              *(long *)(param_1 + 0x5d8) = lVar3;
                              if (lVar3 != 0) {
                                lVar3 = Aska::SoundMemory::Malloc(unsigned long)(uVar6 + 0x1f >> 3 & 0x3ffffffc);
                                *(long *)(param_1 + 0x5e0) = lVar3;
                                if ((lVar3 != 0) &&
                                   (uVar6 = Aska::TPoolLegacy<Aska::AudioInterface, false>::SecurePool(unsigned int, bool, void const*, unsigned int const*)(param_1 + 0x238,uVar6,0,
                                                            *(undefined8 *)(param_1 + 0x5d8),lVar3),
                                   (uVar6 & 1) != 0)) {
                                  uVar6 = (ulong)(uint)(iVar1 << 2);
                                  lVar3 = Aska::SoundMemory::ResourceAlloc(unsigned long, unsigned long)(uVar6 * 0x6000,0x10);
                                  *(long *)(param_1 + 0x5e8) = lVar3;
                                  if (lVar3 != 0) {
                                    lVar3 = Aska::SoundMemory::ResourceAlloc(unsigned long, unsigned long)(uVar6 + 0x1f >> 3 & 0x3ffffffc,0x10);
                                    *(long *)(param_1 + 0x5f0) = lVar3;
                                    if ((lVar3 != 0) &&
                                       (uVar6 = Aska::TPoolLegacy<Aska::SoundServer::AskaAdpcmDecodeBuffer, false>::SecurePool(unsigned int, bool, void const*, unsigned int const*)(param_1 + 0x288,uVar6,0,
                                                                *(undefined8 *)(param_1 + 0x5e8),
                                                                lVar3), (uVar6 & 1) != 0)) {
                                      lVar3 = Aska::SoundMemory::Malloc(unsigned long)(0x208);
                                      *(long *)(param_1 + 0x5f8) = lVar3;
                                      if (lVar3 != 0) {
                                        lVar3 = Aska::SoundMemory::Malloc(unsigned long)(4);
                                        *(long *)(param_1 + 0x600) = lVar3;
                                        if ((lVar3 != 0) &&
                                           (uVar6 = Aska::TPoolLegacy<Aska::SoundServer::FilePathBuffer, false>::SecurePool(unsigned int, bool, void const*, unsigned int const*)(param_1 + 0x2d8,2,0,
                                                                    *(undefined8 *)(param_1 + 0x5f8)
                                                                    ,lVar3), (uVar6 & 1) != 0)) {
                                          uVar5 = 1;
                                          *(undefined1 *)(param_1 + 0x608) = 1;
                                          goto code_r0x020761f0;
                                        }
                                      }
                                    }
                                  }
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  *(undefined1 *)(param_1 + 0x608) = 1;
  Aska::SoundServer::Finalize()(param_1);
  uVar5 = 0;
code_r0x020761f0:
  Aska::AppAudioCommonSettingProxy::~AppAudioCommonSettingProxy()(auStack_38);
  return uVar5;
}

// ==== Aska::TPoolLegacy<Aska::SoundServer::AskaAdpcmDecodeBuffer, false>::SecurePool(unsigned int, bool, void const*, unsigned int const*)
// vaddr 0x1f76c48 | ghidra 0x2076c48 | size 320 | symbol _ZN4Aska11TPoolLegacyINS_11SoundServer21AskaAdpcmDecodeBufferELb0EE10SecurePoolEjbPKvPKj | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska11TPoolLegacyINS_11SoundServer21AskaAdpcmDecodeBufferELb0EE10SecurePoolEjbPKvPKj
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
code_r0x02076d30:
    uVar3 = 1;
  }
  else {
    if (param_4 == 0) {
      lVar1 = operator new[](unsigned long, unsigned long, bool)(param_2 * 0x6000,1,1);
      *(undefined1 *)(param_1 + 0x48) = 1;
      *(long *)(param_1 + 0x40) = lVar1;
      lVar4 = 0;
      if (lVar1 != 0) goto code_r0x02076ce8;
    }
    else {
      *(undefined1 *)(param_1 + 0x48) = 0;
      *(long *)(param_1 + 0x40) = param_4;
code_r0x02076ce8:
      uVar2 = Aska::TBitArray<unsigned int, false>::Alloc(unsigned int, unsigned int const*)(param_1 + 0x10,param_2,param_5);
      if ((uVar2 & 1) != 0) {
        if ((param_3 & 1) != 0) {
          memset(*(undefined8 *)(param_1 + 0x40),0,(ulong)param_2 * 0x6000);
        }
        *(undefined8 *)(param_1 + 0x38) = 0;
        if (*(int *)(param_1 + 0x28) != 0) {
          memset(*plVar5,0,*(int *)(param_1 + 0x28) << 2);
        }
        goto code_r0x02076d30;
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

// ==== Aska::TPoolLegacy<Aska::SoundServer::FilePathBuffer, false>::SecurePool(unsigned int, bool, void const*, unsigned int const*)
// vaddr 0x1f76d88 | ghidra 0x2076d88 | size 320 | symbol _ZN4Aska11TPoolLegacyINS_11SoundServer14FilePathBufferELb0EE10SecurePoolEjbPKvPKj | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska11TPoolLegacyINS_11SoundServer14FilePathBufferELb0EE10SecurePoolEjbPKvPKj
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
code_r0x02076e70:
    uVar3 = 1;
  }
  else {
    if (param_4 == 0) {
      lVar1 = operator new[](unsigned long, unsigned long, bool)(param_2 * 0x104,1,1);
      *(undefined1 *)(param_1 + 0x48) = 1;
      *(long *)(param_1 + 0x40) = lVar1;
      lVar4 = 0;
      if (lVar1 != 0) goto code_r0x02076e28;
    }
    else {
      *(undefined1 *)(param_1 + 0x48) = 0;
      *(long *)(param_1 + 0x40) = param_4;
code_r0x02076e28:
      uVar2 = Aska::TBitArray<unsigned int, false>::Alloc(unsigned int, unsigned int const*)(param_1 + 0x10,param_2,param_5);
      if ((uVar2 & 1) != 0) {
        if ((param_3 & 1) != 0) {
          memset(*(undefined8 *)(param_1 + 0x40),0,(ulong)param_2 * 0x104);
        }
        *(undefined8 *)(param_1 + 0x38) = 0;
        if (*(int *)(param_1 + 0x28) != 0) {
          memset(*plVar5,0,*(int *)(param_1 + 0x28) << 2);
        }
        goto code_r0x02076e70;
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

// ==== Aska::SoundServer::InitializeEffects()
// vaddr 0x1f76ec8 | ghidra 0x2076ec8 | size 8 | symbol _ZN4Aska11SoundServer17InitializeEffectsEv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska11SoundServer17InitializeEffectsEv(void)

{
  return 1;
}

// ==== Aska::SoundServer::Finalize()
// vaddr 0x1f76ed0 | ghidra 0x2076ed0 | size 956 | symbol _ZN4Aska11SoundServer8FinalizeEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska11SoundServer8FinalizeEv(long param_1)

{
  if (*(char *)(param_1 + 0x608) != '\0') {
    if ((*(long *)(param_1 + 0x28) != 0) && (*(char *)(param_1 + 0x38) != '\0')) {
      operator delete[](void*)();
      *(undefined1 *)(param_1 + 0x38) = 0;
    }
    *(long *)(param_1 + 0x28) = 0;
    *(undefined8 *)(param_1 + 0x30) = 0;
    *(undefined8 *)(param_1 + 0x40) = 0;
    if (*(long *)(param_1 + 0x48) != 0) {
      if (*(char *)(param_1 + 0x50) != '\0') {
        operator delete[](void*)();
      }
      *(undefined8 *)(param_1 + 0x48) = 0;
    }
    if (*(long *)(param_1 + 0x568) != 0) {
      operator delete[](void*)();
      *(undefined8 *)(param_1 + 0x568) = 0;
    }
    if (*(long *)(param_1 + 0x570) != 0) {
      operator delete[](void*)();
      *(undefined8 *)(param_1 + 0x570) = 0;
    }
    if ((*(long *)(param_1 + 0x78) != 0) && (*(char *)(param_1 + 0x88) != '\0')) {
      operator delete[](void*)();
      *(undefined1 *)(param_1 + 0x88) = 0;
    }
    *(long *)(param_1 + 0x78) = 0;
    *(undefined8 *)(param_1 + 0x80) = 0;
    *(undefined8 *)(param_1 + 0x90) = 0;
    if (*(long *)(param_1 + 0x98) != 0) {
      if (*(char *)(param_1 + 0xa0) != '\0') {
        operator delete[](void*)();
      }
      *(undefined8 *)(param_1 + 0x98) = 0;
    }
    if (*(long *)(param_1 + 0x578) != 0) {
      operator delete[](void*)();
      *(undefined8 *)(param_1 + 0x578) = 0;
    }
    if (*(long *)(param_1 + 0x580) != 0) {
      operator delete[](void*)();
      *(undefined8 *)(param_1 + 0x580) = 0;
    }
    if ((*(long *)(param_1 + 0x118) != 0) && (*(char *)(param_1 + 0x128) != '\0')) {
      operator delete[](void*)();
      *(undefined1 *)(param_1 + 0x128) = 0;
    }
    *(undefined8 *)(param_1 + 0x118) = 0;
    *(undefined8 *)(param_1 + 0x120) = 0;
    *(undefined8 *)(param_1 + 0x130) = 0;
    if (*(long *)(param_1 + 0x138) != 0) {
      if (*(char *)(param_1 + 0x140) != '\0') {
        operator delete[](void*)();
      }
      *(undefined8 *)(param_1 + 0x138) = 0;
    }
    if (*(long *)(param_1 + 0x588) != 0) {
      operator delete[](void*)();
      *(undefined8 *)(param_1 + 0x588) = 0;
    }
    if (*(long *)(param_1 + 0x590) != 0) {
      operator delete[](void*)();
      *(undefined8 *)(param_1 + 0x590) = 0;
    }
    if ((*(long *)(param_1 + 200) != 0) && (*(char *)(param_1 + 0xd8) != '\0')) {
      operator delete[](void*)();
      *(undefined1 *)(param_1 + 0xd8) = 0;
    }
    *(long *)(param_1 + 200) = 0;
    *(undefined8 *)(param_1 + 0xd0) = 0;
    *(undefined8 *)(param_1 + 0xe0) = 0;
    if (*(long *)(param_1 + 0xe8) != 0) {
      if (*(char *)(param_1 + 0xf0) != '\0') {
        operator delete[](void*)();
      }
      *(undefined8 *)(param_1 + 0xe8) = 0;
    }
    if (*(long *)(param_1 + 0x598) != 0) {
      operator delete[](void*)();
      *(undefined8 *)(param_1 + 0x598) = 0;
    }
    if (*(long *)(param_1 + 0x5a0) != 0) {
      operator delete[](void*)();
      *(undefined8 *)(param_1 + 0x5a0) = 0;
    }
    if ((*(long *)(param_1 + 0x168) != 0) && (*(char *)(param_1 + 0x178) != '\0')) {
      operator delete[](void*)();
      *(undefined1 *)(param_1 + 0x178) = 0;
    }
    *(undefined8 *)(param_1 + 0x168) = 0;
    *(undefined8 *)(param_1 + 0x170) = 0;
    *(undefined8 *)(param_1 + 0x180) = 0;
    if (*(long *)(param_1 + 0x188) != 0) {
      if (*(char *)(param_1 + 400) != '\0') {
        operator delete[](void*)();
      }
      *(undefined8 *)(param_1 + 0x188) = 0;
    }
    if (*(long *)(param_1 + 0x5b8) != 0) {
      operator delete[](void*)();
      *(undefined8 *)(param_1 + 0x5b8) = 0;
    }
    if (*(long *)(param_1 + 0x5c0) != 0) {
      operator delete[](void*)();
      *(undefined8 *)(param_1 + 0x5c0) = 0;
    }
    if ((*(long *)(param_1 + 0x1b8) != 0) && (*(char *)(param_1 + 0x1c8) != '\0')) {
      operator delete[](void*)();
      *(undefined1 *)(param_1 + 0x1c8) = 0;
    }
    *(undefined8 *)(param_1 + 0x1b8) = 0;
    *(undefined8 *)(param_1 + 0x1c0) = 0;
    *(undefined8 *)(param_1 + 0x1d0) = 0;
    if (*(long *)(param_1 + 0x1d8) != 0) {
      if (*(char *)(param_1 + 0x1e0) != '\0') {
        operator delete[](void*)();
      }
      *(undefined8 *)(param_1 + 0x1d8) = 0;
    }
    if (*(long *)(param_1 + 0x5a8) != 0) {
      operator delete[](void*)();
      *(undefined8 *)(param_1 + 0x5a8) = 0;
    }
    if (*(long *)(param_1 + 0x5b0) != 0) {
      operator delete[](void*)();
      *(undefined8 *)(param_1 + 0x5b0) = 0;
    }
    if ((*(long *)(param_1 + 0x208) != 0) && (*(char *)(param_1 + 0x218) != '\0')) {
      operator delete[](void*)();
      *(undefined1 *)(param_1 + 0x218) = 0;
    }
    *(undefined8 *)(param_1 + 0x208) = 0;
    *(undefined8 *)(param_1 + 0x210) = 0;
    *(undefined8 *)(param_1 + 0x220) = 0;
    if (*(long *)(param_1 + 0x228) != 0) {
      if (*(char *)(param_1 + 0x230) != '\0') {
        operator delete[](void*)();
      }
      *(undefined8 *)(param_1 + 0x228) = 0;
    }
    if (*(long *)(param_1 + 0x5c8) != 0) {
      operator delete[](void*)();
      *(undefined8 *)(param_1 + 0x5c8) = 0;
    }
    if (*(long *)(param_1 + 0x5d0) != 0) {
      operator delete[](void*)();
      *(undefined8 *)(param_1 + 0x5d0) = 0;
    }
    if ((*(long *)(param_1 + 600) != 0) && (*(char *)(param_1 + 0x268) != '\0')) {
      operator delete[](void*)();
      *(undefined1 *)(param_1 + 0x268) = 0;
    }
    *(undefined8 *)(param_1 + 600) = 0;
    *(undefined8 *)(param_1 + 0x260) = 0;
    *(undefined8 *)(param_1 + 0x270) = 0;
    if (*(long *)(param_1 + 0x278) != 0) {
      if (*(char *)(param_1 + 0x280) != '\0') {
        operator delete[](void*)();
      }
      *(undefined8 *)(param_1 + 0x278) = 0;
    }
    if (*(long *)(param_1 + 0x5d8) != 0) {
      operator delete[](void*)();
      *(undefined8 *)(param_1 + 0x5d8) = 0;
    }
    if (*(long *)(param_1 + 0x5e0) != 0) {
      operator delete[](void*)();
      *(undefined8 *)(param_1 + 0x5e0) = 0;
    }
    if ((*(long *)(param_1 + 0x2a8) != 0) && (*(char *)(param_1 + 0x2b8) != '\0')) {
      operator delete[](void*)();
      *(undefined1 *)(param_1 + 0x2b8) = 0;
    }
    *(undefined8 *)(param_1 + 0x2a8) = 0;
    *(undefined8 *)(param_1 + 0x2b0) = 0;
    *(undefined8 *)(param_1 + 0x2c0) = 0;
    if (*(long *)(param_1 + 0x2c8) != 0) {
      if (*(char *)(param_1 + 0x2d0) != '\0') {
        operator delete[](void*)();
      }
      *(undefined8 *)(param_1 + 0x2c8) = 0;
    }
    if (*(long *)(param_1 + 0x5e8) != 0) {
      Aska::SoundMemory::ResourceFree(void*)();
      *(undefined8 *)(param_1 + 0x5e8) = 0;
    }
    if (*(long *)(param_1 + 0x5f0) != 0) {
      Aska::SoundMemory::ResourceFree(void*)();
      *(undefined8 *)(param_1 + 0x5f0) = 0;
    }
    if ((*(long *)(param_1 + 0x2f8) != 0) && (*(char *)(param_1 + 0x308) != '\0')) {
      operator delete[](void*)();
      *(undefined1 *)(param_1 + 0x308) = 0;
    }
    *(undefined8 *)(param_1 + 0x2f8) = 0;
    *(undefined8 *)(param_1 + 0x300) = 0;
    *(undefined8 *)(param_1 + 0x310) = 0;
    if (*(long *)(param_1 + 0x318) != 0) {
      if (*(char *)(param_1 + 800) != '\0') {
        operator delete[](void*)();
      }
      *(undefined8 *)(param_1 + 0x318) = 0;
    }
    if (*(long *)(param_1 + 0x5f8) != 0) {
      operator delete[](void*)();
      *(undefined8 *)(param_1 + 0x5f8) = 0;
    }
    if (*(long *)(param_1 + 0x600) != 0) {
      operator delete[](void*)();
      *(undefined8 *)(param_1 + 0x600) = 0;
    }
    *(undefined1 *)(param_1 + 0x608) = 0;
  }
  return;
}

// ==== Aska::SoundServer::FinalizeEffects()
// vaddr 0x1f7728c | ghidra 0x207728c | size 4 | symbol _ZN4Aska11SoundServer15FinalizeEffectsEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska11SoundServer15FinalizeEffectsEv(void)

{
  return;
}

// ==== Aska::SoundServer::AcquireSoundCommand()
// vaddr 0x1f77290 | ghidra 0x2077290 | size 556 | symbol _ZN4Aska11SoundServer19AcquireSoundCommandEv | lib libSOA-3.7.0.so | 2026-10-08
long * _ZN4Aska11SoundServer19AcquireSoundCommandEv(long param_1)

{
  int *piVar1;
  int *piVar2;
  undefined *puVar3;
  uint uVar4;
  char cVar5;
  bool bVar6;
  uint uVar7;
  long *plVar8;
  ulong uVar9;
  int iVar10;
  long lVar11;
  uint uVar12;
  long lVar13;
  ulong uVar14;
  ulong uVar15;
  
  piVar1 = (int *)(param_1 + 0x510);
  iVar10 = 0;
code_r0x020772a8:
  do {
    if (*piVar1 != -1) {
      ClearExclusiveLocal();
      bVar6 = iVar10 < 0x1ff;
      iVar10 = iVar10 + 1;
      if (bVar6) goto code_r0x020772a8;
      piVar2 = (int *)(param_1 + 0x514);
      do {
        cVar5 = '\x01';
        bVar6 = (bool)ExclusiveMonitorPass(piVar2,0x10);
        if (bVar6) {
          *piVar2 = *piVar2 + 1;
          cVar5 = ExclusiveMonitorsStatus();
        }
      } while (cVar5 != '\0');
      do {
        if (*piVar1 != -1) {
          ClearExclusiveLocal();
          do {
            uVar9 = Aska::Semaphore::IsReady() const(param_1 + 0x550);
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
              Aska::Semaphore::Wait() const(param_1 + 0x550);
            }
            do {
              cVar5 = '\x01';
              bVar6 = (bool)ExclusiveMonitorPass(piVar2,0x10);
              if (bVar6) {
                *piVar2 = *piVar2 + 1;
                cVar5 = ExclusiveMonitorsStatus();
              }
            } while (cVar5 != '\0');
            while (*piVar1 == -1) {
              cVar5 = '\x01';
              bVar6 = (bool)ExclusiveMonitorPass(piVar1,0x10);
              if (bVar6) {
                *piVar1 = 0;
                cVar5 = ExclusiveMonitorsStatus();
              }
              if (cVar5 == '\0') goto code_r0x02077360;
            }
            ClearExclusiveLocal();
          } while( true );
        }
        cVar5 = '\x01';
        bVar6 = (bool)ExclusiveMonitorPass(piVar1,0x10);
        if (bVar6) {
          *piVar1 = 0;
          cVar5 = ExclusiveMonitorsStatus();
        }
      } while (cVar5 != '\0');
code_r0x02077360:
      do {
        cVar5 = '\x01';
        bVar6 = (bool)ExclusiveMonitorPass(piVar2,0x10);
        if (bVar6) {
          *piVar2 = *piVar2 + -1;
          cVar5 = ExclusiveMonitorsStatus();
        }
      } while (cVar5 != '\0');
code_r0x02077370:
      DataMemoryBarrier(2,3);
      if (*(uint *)(param_1 + 0x1d4) < *(uint *)(param_1 + 0x1c4)) {
        lVar11 = *(long *)(param_1 + 0x1b8);
        uVar7 = *(uint *)(param_1 + 0x1d0);
        do {
          uVar12 = uVar7;
          if (*(uint *)(param_1 + 0x1c4) <= uVar12) {
            uVar12 = 0;
          }
          uVar4 = 1 << (ulong)(uVar12 & 0x1f);
          uVar7 = uVar12 + 1;
        } while ((uVar4 & *(uint *)(lVar11 + (ulong)(uVar12 >> 5) * 4)) != 0);
        uVar14 = *(long *)(param_1 + 0x1d8) + (ulong)uVar12 * 0xa8;
        uVar9 = uVar14;
        do {
          uVar15 = uVar9 + 0x7f & 0xffffffffffffff81;
          Hint_Prefetch(uVar9,0,2,0);
          uVar9 = uVar15;
        } while (uVar15 < uVar14 + 0xa8);
        *(uint *)(param_1 + 0x1d0) = uVar12 + 1;
        lVar13 = (ulong)(uVar12 >> 5) * 4;
        *(uint *)(param_1 + 0x1d4) = *(uint *)(param_1 + 0x1d4) + 1;
        *(uint *)(lVar11 + lVar13) = *(uint *)(lVar11 + lVar13) | uVar4;
        plVar8 = (long *)(*(long *)(param_1 + 0x1d8) + (ulong)uVar12 * 0xa8);
        puVar3 = PTR__ZTVN4Aska12SoundCommandE_02cc0710 + 0x10;
        plVar8[1] = 0;
        plVar8[2] = 0;
        *plVar8 = (long)puVar3;
        *(undefined4 *)(plVar8 + 3) = 0;
        plVar8[4] = 0;
        plVar8 = (long *)(*(long *)(param_1 + 0x1d8) + (ulong)uVar12 * 0xa8);
        if (plVar8 != (long *)0x0) goto code_r0x02077460;
      }
      plVar8 = (long *)Aska::SoundMemory::Malloc(unsigned long)(0xa8);
      if (plVar8 != (long *)0x0) {
        plVar8[2] = 0;
        puVar3 = PTR__ZTVN4Aska12SoundCommandE_02cc0710;
        *(undefined4 *)(plVar8 + 3) = 0;
        plVar8[4] = 0;
        *plVar8 = (long)(puVar3 + 0x10);
        plVar8[1] = 0;
      }
code_r0x02077460:
      DataMemoryBarrier(2,3);
      *(undefined4 *)(param_1 + 0x510) = 0xffffffff;
      DataMemoryBarrier(2,3);
      if (0x14 < *(int *)(param_1 + 0x514)) {
        piVar1 = (int *)(param_1 + 0x514);
        do {
          cVar5 = '\x01';
          bVar6 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar6) {
            *piVar1 = *piVar1 + -1;
            cVar5 = ExclusiveMonitorsStatus();
          }
        } while (cVar5 != '\0');
        uVar9 = Aska::Semaphore::IsReady() const(param_1 + 0x550);
        if ((uVar9 & 1) != 0) {
          Aska::Semaphore::Signal() const(param_1 + 0x550);
        }
      }
      return plVar8;
    }
    cVar5 = '\x01';
    bVar6 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar6) {
      *piVar1 = 0;
      cVar5 = ExclusiveMonitorsStatus();
    }
    if (cVar5 == '\0') goto code_r0x02077370;
  } while( true );
}

// ==== Aska::SoundServer::ReleaseSoundCommand(Aska::SoundCommand*)
// vaddr 0x1f774bc | ghidra 0x20774bc | size 492 | symbol _ZN4Aska11SoundServer19ReleaseSoundCommandEPNS_12SoundCommandE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska11SoundServer19ReleaseSoundCommandEPNS_12SoundCommandE(long param_1,long *param_2)

{
  int *piVar1;
  int *piVar2;
  char cVar3;
  bool bVar4;
  int iVar5;
  long *plVar6;
  long lVar7;
  ulong uVar8;
  
  piVar1 = (int *)(param_1 + 0x510);
  iVar5 = 0;
  do {
    while (*piVar1 == -1) {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = 0;
        cVar3 = ExclusiveMonitorsStatus();
      }
      if (cVar3 == '\0') goto code_r0x020775a0;
    }
    ClearExclusiveLocal();
    bVar4 = iVar5 < 0x1ff;
    iVar5 = iVar5 + 1;
  } while (bVar4);
  piVar2 = (int *)(param_1 + 0x514);
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
        uVar8 = Aska::Semaphore::IsReady() const(param_1 + 0x550);
        if ((uVar8 & 1) == 0) {
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
          Aska::Semaphore::Wait() const(param_1 + 0x550);
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
          if (cVar3 == '\0') goto code_r0x02077590;
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
code_r0x02077590:
  do {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar4) {
      *piVar2 = *piVar2 + -1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
code_r0x020775a0:
  DataMemoryBarrier(2,3);
  plVar6 = *(long **)(param_1 + 0x1d8);
  if (((plVar6 == (long *)0x0) || (param_2 < plVar6)) ||
     (plVar6 + (ulong)*(uint *)(param_1 + 0x1c4) * 0x15 <= param_2)) {
    if (param_2 != (long *)0x0) {
      (**(code **)(*param_2 + 8))(param_2);
    }
  }
  else {
    uVar8 = ((long)param_2 - (long)plVar6 >> 3) * -0x30c30c30c30c30c3;
    (**(code **)plVar6[(uVar8 & 0xffffffff) * 0x15])();
    lVar7 = (uVar8 >> 5 & 0x7ffffff) * 4;
    *(uint *)(*(long *)(param_1 + 0x1b8) + lVar7) =
         *(uint *)(*(long *)(param_1 + 0x1b8) + lVar7) &
         (1 << (ulong)((uint)uVar8 & 0x1f) ^ 0xffffffffU);
    *(int *)(param_1 + 0x1d4) = *(int *)(param_1 + 0x1d4) + -1;
  }
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_1 + 0x510) = 0xffffffff;
  DataMemoryBarrier(2,3);
  if (0x14 < *(int *)(param_1 + 0x514)) {
    piVar1 = (int *)(param_1 + 0x514);
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
    uVar8 = Aska::Semaphore::IsReady() const(param_1 + 0x550);
    if ((uVar8 & 1) != 0) {
      (*(code *)PTR__ZNK4Aska9Semaphore6SignalEv_02c96cd0)(param_1 + 0x550);
      return;
    }
  }
  return;
}

// ==== Aska::SoundServer::AcquireWaveVoice()
// vaddr 0x1f776a8 | ghidra 0x20776a8 | size 520 | symbol _ZN4Aska11SoundServer16AcquireWaveVoiceEv | lib libSOA-3.7.0.so | 2026-10-08
long _ZN4Aska11SoundServer16AcquireWaveVoiceEv(long param_1)

{
  int *piVar1;
  int *piVar2;
  uint uVar3;
  char cVar4;
  bool bVar5;
  uint uVar6;
  ulong uVar7;
  int iVar8;
  long lVar9;
  long lVar10;
  uint uVar11;
  ulong uVar12;
  ulong uVar13;
  
  piVar1 = (int *)(param_1 + 0x360);
  iVar8 = 0;
  do {
    while (*piVar1 == -1) {
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar5) {
        *piVar1 = 0;
        cVar4 = ExclusiveMonitorsStatus();
      }
      if (cVar4 == '\0') goto code_r0x02077788;
    }
    ClearExclusiveLocal();
    bVar5 = iVar8 < 0x1ff;
    iVar8 = iVar8 + 1;
  } while (bVar5);
  piVar2 = (int *)(param_1 + 0x364);
  do {
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar5) {
      *piVar2 = *piVar2 + 1;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
  do {
    if (*piVar1 != -1) {
      ClearExclusiveLocal();
      do {
        uVar7 = Aska::Semaphore::IsReady() const(param_1 + 0x3a0);
        if ((uVar7 & 1) == 0) {
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
          Aska::Semaphore::Wait() const(param_1 + 0x3a0);
        }
        do {
          cVar4 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
          if (bVar5) {
            *piVar2 = *piVar2 + 1;
            cVar4 = ExclusiveMonitorsStatus();
          }
        } while (cVar4 != '\0');
        while (*piVar1 == -1) {
          cVar4 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar5) {
            *piVar1 = 0;
            cVar4 = ExclusiveMonitorsStatus();
          }
          if (cVar4 == '\0') goto code_r0x02077778;
        }
        ClearExclusiveLocal();
      } while( true );
    }
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar5) {
      *piVar1 = 0;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
code_r0x02077778:
  do {
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar5) {
      *piVar2 = *piVar2 + -1;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
code_r0x02077788:
  DataMemoryBarrier(2,3);
  if (*(uint *)(param_1 + 0x184) < *(uint *)(param_1 + 0x174)) {
    lVar10 = *(long *)(param_1 + 0x168);
    uVar6 = *(uint *)(param_1 + 0x180);
    do {
      uVar11 = uVar6;
      if (*(uint *)(param_1 + 0x174) <= uVar11) {
        uVar11 = 0;
      }
      uVar3 = 1 << (ulong)(uVar11 & 0x1f);
      uVar6 = uVar11 + 1;
    } while ((uVar3 & *(uint *)(lVar10 + (ulong)(uVar11 >> 5) * 4)) != 0);
    uVar12 = *(long *)(param_1 + 0x188) + (ulong)uVar11 * 0x648;
    uVar7 = uVar12;
    do {
      uVar13 = uVar7 + 0x7f & 0xffffffffffffff81;
      Hint_Prefetch(uVar7,0,2,0);
      uVar7 = uVar13;
    } while (uVar13 < uVar12 + 0x400);
    *(uint *)(param_1 + 0x180) = uVar11 + 1;
    *(uint *)(param_1 + 0x184) = *(uint *)(param_1 + 0x184) + 1;
    lVar9 = (ulong)(uVar11 >> 5) * 4;
    *(uint *)(lVar10 + lVar9) = *(uint *)(lVar10 + lVar9) | uVar3;
    Aska::SLVoice::SLVoice()(*(long *)(param_1 + 0x188) + (ulong)uVar11 * 0x648);
    lVar10 = *(long *)(param_1 + 0x188) + (ulong)uVar11 * 0x648;
  }
  else {
    lVar10 = 0;
  }
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_1 + 0x360) = 0xffffffff;
  DataMemoryBarrier(2,3);
  if (0x14 < *(int *)(param_1 + 0x364)) {
    piVar1 = (int *)(param_1 + 0x364);
    do {
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar5) {
        *piVar1 = *piVar1 + -1;
        cVar4 = ExclusiveMonitorsStatus();
      }
    } while (cVar4 != '\0');
    uVar7 = Aska::Semaphore::IsReady() const(param_1 + 0x3a0);
    if ((uVar7 & 1) != 0) {
      Aska::Semaphore::Signal() const(param_1 + 0x3a0);
    }
  }
  if ((lVar10 == 0) && (lVar10 = Aska::SoundMemory::Malloc(unsigned long)(0x648), lVar10 != 0)) {
    Aska::SLVoice::SLVoice()(lVar10);
  }
  return lVar10;
}

// ==== Aska::SoundServer::ReleaseWaveVoice(Aska::WaveVoiceBase*)
// vaddr 0x1f778b0 | ghidra 0x20778b0 | size 492 | symbol _ZN4Aska11SoundServer16ReleaseWaveVoiceEPNS_13WaveVoiceBaseE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska11SoundServer16ReleaseWaveVoiceEPNS_13WaveVoiceBaseE(long param_1,long *param_2)

{
  int *piVar1;
  int *piVar2;
  char cVar3;
  bool bVar4;
  int iVar5;
  long *plVar6;
  long lVar7;
  ulong uVar8;
  
  piVar1 = (int *)(param_1 + 0x360);
  iVar5 = 0;
  do {
    while (*piVar1 == -1) {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = 0;
        cVar3 = ExclusiveMonitorsStatus();
      }
      if (cVar3 == '\0') goto code_r0x02077994;
    }
    ClearExclusiveLocal();
    bVar4 = iVar5 < 0x1ff;
    iVar5 = iVar5 + 1;
  } while (bVar4);
  piVar2 = (int *)(param_1 + 0x364);
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
        uVar8 = Aska::Semaphore::IsReady() const(param_1 + 0x3a0);
        if ((uVar8 & 1) == 0) {
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
          Aska::Semaphore::Wait() const(param_1 + 0x3a0);
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
          if (cVar3 == '\0') goto code_r0x02077984;
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
code_r0x02077984:
  do {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar4) {
      *piVar2 = *piVar2 + -1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
code_r0x02077994:
  DataMemoryBarrier(2,3);
  plVar6 = *(long **)(param_1 + 0x188);
  if (((plVar6 == (long *)0x0) || (param_2 < plVar6)) ||
     (plVar6 + (ulong)*(uint *)(param_1 + 0x174) * 0xc9 <= param_2)) {
    if (param_2 != (long *)0x0) {
      (**(code **)(*param_2 + 8))(param_2);
    }
  }
  else {
    uVar8 = ((long)param_2 - (long)plVar6 >> 3) * -0x51832f1fd73e687;
    (**(code **)plVar6[(uVar8 & 0xffffffff) * 0xc9])();
    lVar7 = (uVar8 >> 5 & 0x7ffffff) * 4;
    *(uint *)(*(long *)(param_1 + 0x168) + lVar7) =
         *(uint *)(*(long *)(param_1 + 0x168) + lVar7) &
         (1 << (ulong)((uint)uVar8 & 0x1f) ^ 0xffffffffU);
    *(int *)(param_1 + 0x184) = *(int *)(param_1 + 0x184) + -1;
  }
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_1 + 0x360) = 0xffffffff;
  DataMemoryBarrier(2,3);
  if (0x14 < *(int *)(param_1 + 0x364)) {
    piVar1 = (int *)(param_1 + 0x364);
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
    uVar8 = Aska::Semaphore::IsReady() const(param_1 + 0x3a0);
    if ((uVar8 & 1) != 0) {
      (*(code *)PTR__ZNK4Aska9Semaphore6SignalEv_02c96cd0)(param_1 + 0x3a0);
      return;
    }
  }
  return;
}

// ==== Aska::SoundServer::AcquireSoundPass()
// vaddr 0x1f77a9c | ghidra 0x2077a9c | size 220 | symbol _ZN4Aska11SoundServer16AcquireSoundPassEv | lib libSOA-3.7.0.so | 2026-10-08
long _ZN4Aska11SoundServer16AcquireSoundPassEv(long param_1)

{
  uint uVar1;
  uint uVar2;
  long lVar3;
  long lVar4;
  uint uVar5;
  ulong uVar6;
  ulong uVar7;
  ulong uVar8;
  
  if (*(uint *)(param_1 + 0x224) < *(uint *)(param_1 + 0x214)) {
    lVar4 = *(long *)(param_1 + 0x208);
    uVar2 = *(uint *)(param_1 + 0x220);
    do {
      uVar5 = uVar2;
      if (*(uint *)(param_1 + 0x214) <= uVar5) {
        uVar5 = 0;
      }
      uVar1 = 1 << (ulong)(uVar5 & 0x1f);
      uVar2 = uVar5 + 1;
    } while ((uVar1 & *(uint *)(lVar4 + (ulong)(uVar5 >> 5) * 4)) != 0);
    uVar6 = *(long *)(param_1 + 0x228) + (ulong)uVar5 * 0xe8;
    uVar7 = uVar6;
    do {
      uVar8 = uVar7 + 0x7f & 0xffffffffffffff81;
      Hint_Prefetch(uVar7,0,2,0);
      uVar7 = uVar8;
    } while (uVar8 < uVar6 + 0xe8);
    *(uint *)(param_1 + 0x220) = uVar5 + 1;
    *(uint *)(param_1 + 0x224) = *(uint *)(param_1 + 0x224) + 1;
    lVar3 = (ulong)(uVar5 >> 5) * 4;
    *(uint *)(lVar4 + lVar3) = *(uint *)(lVar4 + lVar3) | uVar1;
    Aska::SoundPass::SoundPass()(*(long *)(param_1 + 0x228) + (ulong)uVar5 * 0xe8);
    lVar4 = *(long *)(param_1 + 0x228) + (ulong)uVar5 * 0xe8;
    if (lVar4 != 0) {
      return lVar4;
    }
  }
  lVar4 = Aska::SoundMemory::Malloc(unsigned long)(0xe8);
  if (lVar4 != 0) {
    Aska::SoundPass::SoundPass()(lVar4);
  }
  return lVar4;
}

// ==== Aska::SoundServer::ReleaseSoundPass(Aska::SoundPass*)
// vaddr 0x1f77b78 | ghidra 0x2077b78 | size 192 | symbol _ZN4Aska11SoundServer16ReleaseSoundPassEPNS_9SoundPassE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska11SoundServer16ReleaseSoundPassEPNS_9SoundPassE(long param_1,long *param_2)

{
  long *plVar1;
  long lVar2;
  ulong uVar3;
  
  plVar1 = *(long **)(param_1 + 0x228);
  if (((plVar1 == (long *)0x0) || (param_2 < plVar1)) ||
     (plVar1 + (ulong)*(uint *)(param_1 + 0x214) * 0x1d <= param_2)) {
    if (param_2 != (long *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x02077c28. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (**(code **)(*param_2 + 8))(param_2);
      return;
    }
  }
  else {
    uVar3 = ((long)param_2 - (long)plVar1 >> 3) * 0x34f72c234f72c235;
    (**(code **)plVar1[(uVar3 & 0xffffffff) * 0x1d])();
    lVar2 = (uVar3 >> 5 & 0x7ffffff) * 4;
    *(uint *)(*(long *)(param_1 + 0x208) + lVar2) =
         *(uint *)(*(long *)(param_1 + 0x208) + lVar2) &
         (1 << (ulong)((uint)uVar3 & 0x1f) ^ 0xffffffffU);
    *(int *)(param_1 + 0x224) = *(int *)(param_1 + 0x224) + -1;
  }
  return;
}

// ==== Aska::SoundServer::AcquireAudioInterface()
// vaddr 0x1f77c38 | ghidra 0x2077c38 | size 512 | symbol _ZN4Aska11SoundServer21AcquireAudioInterfaceEv | lib libSOA-3.7.0.so | 2026-10-08
long _ZN4Aska11SoundServer21AcquireAudioInterfaceEv(long param_1)

{
  int *piVar1;
  int *piVar2;
  uint uVar3;
  char cVar4;
  bool bVar5;
  uint uVar6;
  ulong uVar7;
  int iVar8;
  long lVar9;
  long lVar10;
  uint uVar11;
  ulong uVar12;
  ulong uVar13;
  
  piVar1 = (int *)(param_1 + 0x480);
  iVar8 = 0;
code_r0x02077c50:
  do {
    if (*piVar1 != -1) {
      ClearExclusiveLocal();
      bVar5 = iVar8 < 0x1ff;
      iVar8 = iVar8 + 1;
      if (bVar5) goto code_r0x02077c50;
      piVar2 = (int *)(param_1 + 0x484);
      do {
        cVar4 = '\x01';
        bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
        if (bVar5) {
          *piVar2 = *piVar2 + 1;
          cVar4 = ExclusiveMonitorsStatus();
        }
      } while (cVar4 != '\0');
      do {
        if (*piVar1 != -1) {
          ClearExclusiveLocal();
          do {
            uVar7 = Aska::Semaphore::IsReady() const(param_1 + 0x4c0);
            if ((uVar7 & 1) == 0) {
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
              Aska::Semaphore::Wait() const(param_1 + 0x4c0);
            }
            do {
              cVar4 = '\x01';
              bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
              if (bVar5) {
                *piVar2 = *piVar2 + 1;
                cVar4 = ExclusiveMonitorsStatus();
              }
            } while (cVar4 != '\0');
            while (*piVar1 == -1) {
              cVar4 = '\x01';
              bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
              if (bVar5) {
                *piVar1 = 0;
                cVar4 = ExclusiveMonitorsStatus();
              }
              if (cVar4 == '\0') goto code_r0x02077d08;
            }
            ClearExclusiveLocal();
          } while( true );
        }
        cVar4 = '\x01';
        bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
        if (bVar5) {
          *piVar1 = 0;
          cVar4 = ExclusiveMonitorsStatus();
        }
      } while (cVar4 != '\0');
code_r0x02077d08:
      do {
        cVar4 = '\x01';
        bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
        if (bVar5) {
          *piVar2 = *piVar2 + -1;
          cVar4 = ExclusiveMonitorsStatus();
        }
      } while (cVar4 != '\0');
code_r0x02077d18:
      DataMemoryBarrier(2,3);
      if (*(uint *)(param_1 + 0x274) < *(uint *)(param_1 + 0x264)) {
        lVar10 = *(long *)(param_1 + 600);
        uVar6 = *(uint *)(param_1 + 0x270);
        do {
          uVar11 = uVar6;
          if (*(uint *)(param_1 + 0x264) <= uVar11) {
            uVar11 = 0;
          }
          uVar3 = 1 << (ulong)(uVar11 & 0x1f);
          uVar6 = uVar11 + 1;
        } while ((uVar3 & *(uint *)(lVar10 + (ulong)(uVar11 >> 5) * 4)) != 0);
        uVar12 = *(long *)(param_1 + 0x278) + (ulong)uVar11 * 0x28;
        uVar7 = uVar12;
        do {
          uVar13 = uVar7 + 0x7f & 0xffffffffffffff81;
          Hint_Prefetch(uVar7,0,2,0);
          uVar7 = uVar13;
        } while (uVar13 < uVar12 + 0x28);
        *(uint *)(param_1 + 0x270) = uVar11 + 1;
        *(uint *)(param_1 + 0x274) = *(uint *)(param_1 + 0x274) + 1;
        lVar9 = (ulong)(uVar11 >> 5) * 4;
        *(uint *)(lVar10 + lVar9) = *(uint *)(lVar10 + lVar9) | uVar3;
        Aska::AudioInterface::AudioInterface()(*(long *)(param_1 + 0x278) + (ulong)uVar11 * 0x28);
        lVar10 = *(long *)(param_1 + 0x278) + (ulong)uVar11 * 0x28;
        if (lVar10 != 0) goto code_r0x02077ddc;
      }
      lVar10 = Aska::SoundMemory::Malloc(unsigned long)(0x28);
      if (lVar10 != 0) {
        Aska::AudioInterface::AudioInterface()(lVar10);
      }
code_r0x02077ddc:
      DataMemoryBarrier(2,3);
      *(undefined4 *)(param_1 + 0x480) = 0xffffffff;
      DataMemoryBarrier(2,3);
      if (0x14 < *(int *)(param_1 + 0x484)) {
        piVar1 = (int *)(param_1 + 0x484);
        do {
          cVar4 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar5) {
            *piVar1 = *piVar1 + -1;
            cVar4 = ExclusiveMonitorsStatus();
          }
        } while (cVar4 != '\0');
        uVar7 = Aska::Semaphore::IsReady() const(param_1 + 0x4c0);
        if ((uVar7 & 1) != 0) {
          Aska::Semaphore::Signal() const(param_1 + 0x4c0);
        }
      }
      return lVar10;
    }
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar5) {
      *piVar1 = 0;
      cVar4 = ExclusiveMonitorsStatus();
    }
    if (cVar4 == '\0') goto code_r0x02077d18;
  } while( true );
}

// ==== Aska::SoundServer::ReleaseAudioInterface(Aska::AudioInterface*)
// vaddr 0x1f77e38 | ghidra 0x2077e38 | size 484 | symbol _ZN4Aska11SoundServer21ReleaseAudioInterfaceEPNS_14AudioInterfaceE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska11SoundServer21ReleaseAudioInterfaceEPNS_14AudioInterfaceE(long param_1,long *param_2)

{
  int *piVar1;
  int *piVar2;
  char cVar3;
  bool bVar4;
  int iVar5;
  long *plVar6;
  long lVar7;
  ulong uVar8;
  
  piVar1 = (int *)(param_1 + 0x480);
  iVar5 = 0;
  do {
    while (*piVar1 == -1) {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = 0;
        cVar3 = ExclusiveMonitorsStatus();
      }
      if (cVar3 == '\0') goto code_r0x02077f1c;
    }
    ClearExclusiveLocal();
    bVar4 = iVar5 < 0x1ff;
    iVar5 = iVar5 + 1;
  } while (bVar4);
  piVar2 = (int *)(param_1 + 0x484);
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
        uVar8 = Aska::Semaphore::IsReady() const(param_1 + 0x4c0);
        if ((uVar8 & 1) == 0) {
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
          Aska::Semaphore::Wait() const(param_1 + 0x4c0);
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
          if (cVar3 == '\0') goto code_r0x02077f0c;
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
code_r0x02077f0c:
  do {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar4) {
      *piVar2 = *piVar2 + -1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
code_r0x02077f1c:
  DataMemoryBarrier(2,3);
  plVar6 = *(long **)(param_1 + 0x278);
  if (((plVar6 == (long *)0x0) || (param_2 < plVar6)) ||
     (plVar6 + (ulong)*(uint *)(param_1 + 0x264) * 5 <= param_2)) {
    if (param_2 != (long *)0x0) {
      (**(code **)(*param_2 + 8))(param_2);
    }
  }
  else {
    uVar8 = ((long)param_2 - (long)plVar6 >> 3) * -0x3333333333333333;
    (**(code **)plVar6[(uVar8 & 0xffffffff) * 5])();
    lVar7 = (uVar8 >> 5 & 0x7ffffff) * 4;
    *(uint *)(*(long *)(param_1 + 600) + lVar7) =
         *(uint *)(*(long *)(param_1 + 600) + lVar7) &
         (1 << (ulong)((uint)uVar8 & 0x1f) ^ 0xffffffffU);
    *(int *)(param_1 + 0x274) = *(int *)(param_1 + 0x274) + -1;
  }
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_1 + 0x480) = 0xffffffff;
  DataMemoryBarrier(2,3);
  if (0x14 < *(int *)(param_1 + 0x484)) {
    piVar1 = (int *)(param_1 + 0x484);
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
    uVar8 = Aska::Semaphore::IsReady() const(param_1 + 0x4c0);
    if ((uVar8 & 1) != 0) {
      (*(code *)PTR__ZNK4Aska9Semaphore6SignalEv_02c96cd0)(param_1 + 0x4c0);
      return;
    }
  }
  return;
}

// ==== Aska::SoundServer::AcquireAskaAdpcmDecodeBuffer()
// vaddr 0x1f7801c | ghidra 0x207801c | size 180 | symbol _ZN4Aska11SoundServer28AcquireAskaAdpcmDecodeBufferEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska11SoundServer28AcquireAskaAdpcmDecodeBufferEv(long param_1)

{
  uint uVar1;
  uint uVar2;
  long lVar3;
  long lVar4;
  uint uVar5;
  ulong uVar6;
  ulong uVar7;
  ulong uVar8;
  
  if (*(uint *)(param_1 + 0x2c4) < *(uint *)(param_1 + 0x2b4)) {
    lVar4 = *(long *)(param_1 + 0x2a8);
    uVar2 = *(uint *)(param_1 + 0x2c0);
    do {
      uVar5 = uVar2;
      if (*(uint *)(param_1 + 0x2b4) <= uVar5) {
        uVar5 = 0;
      }
      uVar1 = 1 << (ulong)(uVar5 & 0x1f);
      uVar2 = uVar5 + 1;
    } while ((uVar1 & *(uint *)(lVar4 + (ulong)(uVar5 >> 5) * 4)) != 0);
    uVar6 = *(long *)(param_1 + 0x2c8) + (ulong)uVar5 * 0x6000;
    uVar7 = uVar6;
    do {
      uVar8 = uVar7 + 0x7f & 0xffffffffffffff81;
      Hint_Prefetch(uVar7,0,2,0);
      uVar7 = uVar8;
    } while (uVar8 < uVar6 + 0x400);
    *(uint *)(param_1 + 0x2c0) = uVar5 + 1;
    *(uint *)(param_1 + 0x2c4) = *(uint *)(param_1 + 0x2c4) + 1;
    lVar3 = (ulong)(uVar5 >> 5) * 4;
    *(uint *)(lVar4 + lVar3) = *(uint *)(lVar4 + lVar3) | uVar1;
    if (*(long *)(param_1 + 0x2c8) + (ulong)uVar5 * 0x6000 != 0) {
      return;
    }
  }
  Aska::SoundMemory::ResourceAlloc(unsigned long, unsigned long)(0x6000,0x10);
  return;
}

// ==== Aska::SoundServer::ReleaseAskaAdpcmDecodeBuffer(void*)
// vaddr 0x1f780d0 | ghidra 0x20780d0 | size 124 | symbol _ZN4Aska11SoundServer28ReleaseAskaAdpcmDecodeBufferEPv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska11SoundServer28ReleaseAskaAdpcmDecodeBufferEPv(long param_1,ulong param_2)

{
  ulong uVar1;
  long lVar2;
  
  uVar1 = *(ulong *)(param_1 + 0x2c8);
  if (((uVar1 != 0) && (uVar1 <= param_2)) &&
     (param_2 < uVar1 + (ulong)*(uint *)(param_1 + 0x2b4) * 0x6000)) {
    uVar1 = ((long)(param_2 - uVar1) >> 0xd) * -0x5555555555555555;
    lVar2 = (uVar1 >> 5 & 0x7ffffff) * 4;
    *(uint *)(*(long *)(param_1 + 0x2a8) + lVar2) =
         *(uint *)(*(long *)(param_1 + 0x2a8) + lVar2) &
         (1 << (ulong)((uint)uVar1 & 0x1f) ^ 0xffffffffU);
    *(int *)(param_1 + 0x2c4) = *(int *)(param_1 + 0x2c4) + -1;
    return;
  }
  if (param_2 != 0) {
    (*(code *)PTR__ZN4Aska11SoundMemory12ResourceFreeEPv_02c988d8)(param_2);
    return;
  }
  return;
}

// ==== Aska::SoundServer::AcquireFilePathBuffer()
// vaddr 0x1f7814c | ghidra 0x207814c | size 176 | symbol _ZN4Aska11SoundServer21AcquireFilePathBufferEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska11SoundServer21AcquireFilePathBufferEv(long param_1)

{
  uint uVar1;
  uint uVar2;
  long lVar3;
  long lVar4;
  uint uVar5;
  ulong uVar6;
  ulong uVar7;
  ulong uVar8;
  
  if (*(uint *)(param_1 + 0x314) < *(uint *)(param_1 + 0x304)) {
    lVar4 = *(long *)(param_1 + 0x2f8);
    uVar2 = *(uint *)(param_1 + 0x310);
    do {
      uVar5 = uVar2;
      if (*(uint *)(param_1 + 0x304) <= uVar5) {
        uVar5 = 0;
      }
      uVar1 = 1 << (ulong)(uVar5 & 0x1f);
      uVar2 = uVar5 + 1;
    } while ((uVar1 & *(uint *)(lVar4 + (ulong)(uVar5 >> 5) * 4)) != 0);
    uVar6 = *(long *)(param_1 + 0x318) + (ulong)uVar5 * 0x104;
    uVar7 = uVar6;
    do {
      uVar8 = uVar7 + 0x7f & 0xffffffffffffff81;
      Hint_Prefetch(uVar7,0,2,0);
      uVar7 = uVar8;
    } while (uVar8 < uVar6 + 0x104);
    *(uint *)(param_1 + 0x310) = uVar5 + 1;
    *(uint *)(param_1 + 0x314) = *(uint *)(param_1 + 0x314) + 1;
    lVar3 = (ulong)(uVar5 >> 5) * 4;
    *(uint *)(lVar4 + lVar3) = *(uint *)(lVar4 + lVar3) | uVar1;
    if (*(long *)(param_1 + 0x318) + (ulong)uVar5 * 0x104 != 0) {
      return;
    }
  }
  Aska::SoundMemory::Malloc(unsigned long)(0x104);
  return;
}

// ==== Aska::SoundServer::ReleaseFilePathBuffer(char*)
// vaddr 0x1f781fc | ghidra 0x20781fc | size 132 | symbol _ZN4Aska11SoundServer21ReleaseFilePathBufferEPc | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska11SoundServer21ReleaseFilePathBufferEPc(long param_1,ulong param_2)

{
  ulong uVar1;
  long lVar2;
  
  uVar1 = *(ulong *)(param_1 + 0x318);
  if (((uVar1 != 0) && (uVar1 <= param_2)) &&
     (param_2 < uVar1 + (ulong)*(uint *)(param_1 + 0x304) * 0x104)) {
    uVar1 = ((long)(param_2 - uVar1) >> 2) * 0xfc0fc0fc0fc0fc1;
    lVar2 = (uVar1 >> 5 & 0x7ffffff) * 4;
    *(uint *)(*(long *)(param_1 + 0x2f8) + lVar2) =
         *(uint *)(*(long *)(param_1 + 0x2f8) + lVar2) &
         (1 << (ulong)((uint)uVar1 & 0x1f) ^ 0xffffffffU);
    *(int *)(param_1 + 0x314) = *(int *)(param_1 + 0x314) + -1;
    return;
  }
  if (param_2 != 0) {
    (*(code *)PTR__ZdlPv_02ca4758)(param_2);
    return;
  }
  return;
}

// ==== Aska::SoundServer::~SoundServer()
// vaddr 0x1f78280 | ghidra 0x2078280 | size 1804 | symbol _ZN4Aska11SoundServerD2Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska11SoundServerD2Ev(long *param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  long *plVar3;
  
  *param_1 = (long)(PTR__ZTVN4Aska11SoundServerE_02cbfa60 + 0x10);
  Aska::SoundServer::Finalize()();
  Aska::FastCriticalSection::~FastCriticalSection()(param_1 + 0x9b);
  Aska::FastCriticalSection::~FastCriticalSection()(param_1 + 0x89);
  Aska::FastCriticalSection::~FastCriticalSection()(param_1 + 0x77);
  Aska::FastCriticalSection::~FastCriticalSection()(param_1 + 0x65);
  param_1[0x5b] =
       (long)(PTR__ZTVN4Aska11TPoolLegacyINS_11SoundServer14FilePathBufferELb0EEE_02cbe0c0 + 0x10);
  if ((param_1[0x5f] != 0) && ((char)param_1[0x61] != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 0x61) = 0;
  }
  param_1[0x5f] = 0;
  param_1[0x60] = 0;
  param_1[0x62] = 0;
  if (param_1[99] == 0) {
code_r0x02078344:
    param_1[0x5d] = (long)(PTR__ZTVN4Aska9TBitArrayIjLb0EEE_02cba038 + 0x10);
  }
  else {
    if ((char)param_1[100] == '\0') {
      param_1[99] = 0;
      goto code_r0x02078344;
    }
    operator delete[](void*)();
    param_1[99] = 0;
    param_1[0x5d] = (long)(PTR__ZTVN4Aska9TBitArrayIjLb0EEE_02cba038 + 0x10);
    if ((param_1[0x5f] != 0) && ((char)param_1[0x61] != '\0')) {
      operator delete[](void*)();
      *(undefined1 *)(param_1 + 0x61) = 0;
    }
  }
  param_1[0x5f] = 0;
  param_1[0x60] = 0;
  puVar2 = PTR__ZTVN4Aska13TSmartPointerILb0EEE_02cc2320;
  puVar1 = PTR__ZTVN4Aska13TSmartPointerILb0EEE_02cc2320 + 0x10;
  param_1[0x5d] = (long)puVar1;
  param_1[0x5b] = (long)puVar1;
  param_1[0x51] =
       (long)(PTR__ZTVN4Aska11TPoolLegacyINS_11SoundServer21AskaAdpcmDecodeBufferELb0EEE_02cc1e68 +
             0x10);
  if ((param_1[0x55] != 0) && ((char)param_1[0x57] != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 0x57) = 0;
  }
  param_1[0x55] = 0;
  param_1[0x56] = 0;
  param_1[0x58] = 0;
  if (param_1[0x59] == 0) {
code_r0x020783f0:
    param_1[0x53] = (long)(PTR__ZTVN4Aska9TBitArrayIjLb0EEE_02cba038 + 0x10);
  }
  else {
    if ((char)param_1[0x5a] == '\0') {
      param_1[0x59] = 0;
      goto code_r0x020783f0;
    }
    operator delete[](void*)();
    param_1[0x59] = 0;
    param_1[0x53] = (long)(PTR__ZTVN4Aska9TBitArrayIjLb0EEE_02cba038 + 0x10);
    if ((param_1[0x55] != 0) && ((char)param_1[0x57] != '\0')) {
      operator delete[](void*)();
      *(undefined1 *)(param_1 + 0x57) = 0;
    }
  }
  param_1[0x55] = 0;
  param_1[0x56] = 0;
  param_1[0x53] = (long)(puVar2 + 0x10);
  param_1[0x51] = (long)(puVar2 + 0x10);
  param_1[0x47] = (long)(PTR__ZTVN4Aska11TPoolLegacyINS_14AudioInterfaceELb0EEE_02cb87a8 + 0x10);
  if ((param_1[0x4b] != 0) && ((char)param_1[0x4d] != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 0x4d) = 0;
  }
  param_1[0x4b] = 0;
  param_1[0x4c] = 0;
  param_1[0x4e] = 0;
  if (param_1[0x4f] == 0) {
code_r0x02078494:
    param_1[0x49] = (long)(PTR__ZTVN4Aska9TBitArrayIjLb0EEE_02cba038 + 0x10);
  }
  else {
    if ((char)param_1[0x50] == '\0') {
      param_1[0x4f] = 0;
      goto code_r0x02078494;
    }
    operator delete[](void*)();
    param_1[0x4f] = 0;
    param_1[0x49] = (long)(PTR__ZTVN4Aska9TBitArrayIjLb0EEE_02cba038 + 0x10);
    if ((param_1[0x4b] != 0) && ((char)param_1[0x4d] != '\0')) {
      operator delete[](void*)();
      *(undefined1 *)(param_1 + 0x4d) = 0;
    }
  }
  param_1[0x4b] = 0;
  param_1[0x4c] = 0;
  param_1[0x49] = (long)(puVar2 + 0x10);
  param_1[0x47] = (long)(puVar2 + 0x10);
  param_1[0x3d] = (long)(PTR__ZTVN4Aska11TPoolLegacyINS_9SoundPassELb0EEE_02cbd7b0 + 0x10);
  if ((param_1[0x41] != 0) && ((char)param_1[0x43] != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 0x43) = 0;
  }
  param_1[0x41] = 0;
  param_1[0x42] = 0;
  param_1[0x44] = 0;
  if (param_1[0x45] == 0) {
code_r0x02078538:
    param_1[0x3f] = (long)(PTR__ZTVN4Aska9TBitArrayIjLb0EEE_02cba038 + 0x10);
  }
  else {
    if ((char)param_1[0x46] == '\0') {
      param_1[0x45] = 0;
      goto code_r0x02078538;
    }
    operator delete[](void*)();
    param_1[0x45] = 0;
    param_1[0x3f] = (long)(PTR__ZTVN4Aska9TBitArrayIjLb0EEE_02cba038 + 0x10);
    if ((param_1[0x41] != 0) && ((char)param_1[0x43] != '\0')) {
      operator delete[](void*)();
      *(undefined1 *)(param_1 + 0x43) = 0;
    }
  }
  param_1[0x41] = 0;
  param_1[0x42] = 0;
  param_1[0x3f] = (long)(puVar2 + 0x10);
  param_1[0x3d] = (long)(puVar2 + 0x10);
  param_1[0x33] = (long)(PTR__ZTVN4Aska11TPoolLegacyINS_12SoundCommandELb0EEE_02cbc4e8 + 0x10);
  if ((param_1[0x37] != 0) && ((char)param_1[0x39] != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 0x39) = 0;
  }
  param_1[0x37] = 0;
  param_1[0x38] = 0;
  param_1[0x3a] = 0;
  if (param_1[0x3b] == 0) {
code_r0x020785dc:
    param_1[0x35] = (long)(PTR__ZTVN4Aska9TBitArrayIjLb0EEE_02cba038 + 0x10);
  }
  else {
    if ((char)param_1[0x3c] == '\0') {
      param_1[0x3b] = 0;
      goto code_r0x020785dc;
    }
    operator delete[](void*)();
    param_1[0x3b] = 0;
    param_1[0x35] = (long)(PTR__ZTVN4Aska9TBitArrayIjLb0EEE_02cba038 + 0x10);
    if ((param_1[0x37] != 0) && ((char)param_1[0x39] != '\0')) {
      operator delete[](void*)();
      *(undefined1 *)(param_1 + 0x39) = 0;
    }
  }
  param_1[0x37] = 0;
  param_1[0x38] = 0;
  param_1[0x35] = (long)(puVar2 + 0x10);
  param_1[0x33] = (long)(puVar2 + 0x10);
  param_1[0x29] = (long)(PTR__ZTVN4Aska11TPoolLegacyINS_7SLVoiceELb0EEE_02cbe3d8 + 0x10);
  if ((param_1[0x2d] != 0) && ((char)param_1[0x2f] != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 0x2f) = 0;
  }
  param_1[0x2d] = 0;
  param_1[0x2e] = 0;
  param_1[0x30] = 0;
  if (param_1[0x31] == 0) {
code_r0x02078680:
    param_1[0x2b] = (long)(PTR__ZTVN4Aska9TBitArrayIjLb0EEE_02cba038 + 0x10);
  }
  else {
    if ((char)param_1[0x32] == '\0') {
      param_1[0x31] = 0;
      goto code_r0x02078680;
    }
    operator delete[](void*)();
    param_1[0x31] = 0;
    param_1[0x2b] = (long)(PTR__ZTVN4Aska9TBitArrayIjLb0EEE_02cba038 + 0x10);
    if ((param_1[0x2d] != 0) && ((char)param_1[0x2f] != '\0')) {
      operator delete[](void*)();
      *(undefined1 *)(param_1 + 0x2f) = 0;
    }
  }
  param_1[0x2d] = 0;
  param_1[0x2e] = 0;
  param_1[0x2b] = (long)(puVar2 + 0x10);
  param_1[0x29] = (long)(puVar2 + 0x10);
  param_1[0x1f] = (long)(PTR__ZTVN4Aska11TPoolLegacyINS_11SoundHandleELb0EEE_02cc1b30 + 0x10);
  if ((param_1[0x23] != 0) && ((char)param_1[0x25] != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 0x25) = 0;
  }
  param_1[0x23] = 0;
  param_1[0x24] = 0;
  param_1[0x26] = 0;
  if (param_1[0x27] != 0) {
    if ((char)param_1[0x28] != '\0') {
      operator delete[](void*)();
      param_1[0x27] = 0;
      param_1[0x21] = (long)(PTR__ZTVN4Aska9TBitArrayIjLb0EEE_02cba038 + 0x10);
      if ((param_1[0x23] != 0) && ((char)param_1[0x25] != '\0')) {
        operator delete[](void*)();
        *(undefined1 *)(param_1 + 0x25) = 0;
      }
      goto code_r0x02078738;
    }
    param_1[0x27] = 0;
  }
  param_1[0x21] = (long)(PTR__ZTVN4Aska9TBitArrayIjLb0EEE_02cba038 + 0x10);
code_r0x02078738:
  param_1[0x23] = 0;
  param_1[0x24] = 0;
  param_1[0x21] = (long)(puVar2 + 0x10);
  puVar1 = PTR__ZTVN4Aska11TPoolLegacyINS_16AudioMessageNoteELb0EEE_02cc2ea0;
  plVar3 = param_1 + 0x19;
  param_1[0x1f] = (long)(puVar2 + 0x10);
  param_1[0x15] = (long)(puVar1 + 0x10);
  if ((*plVar3 != 0) && ((char)param_1[0x1b] != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 0x1b) = 0;
  }
  *plVar3 = 0;
  param_1[0x1a] = 0;
  param_1[0x1c] = 0;
  if (param_1[0x1d] == 0) {
    param_1[0x17] = (long)(PTR__ZTVN4Aska9TBitArrayIjLb0EEE_02cba038 + 0x10);
  }
  else if ((char)param_1[0x1e] == '\0') {
    param_1[0x17] = (long)(PTR__ZTVN4Aska9TBitArrayIjLb0EEE_02cba038 + 0x10);
    param_1[0x1d] = 0;
  }
  else {
    operator delete[](void*)();
    param_1[0x17] = (long)(PTR__ZTVN4Aska9TBitArrayIjLb0EEE_02cba038 + 0x10);
    param_1[0x1d] = 0;
    if ((param_1[0x19] != 0) && ((char)param_1[0x1b] != '\0')) {
      operator delete[](void*)();
      *(undefined1 *)(param_1 + 0x1b) = 0;
    }
  }
  *plVar3 = 0;
  param_1[0x1a] = 0;
  param_1[0x17] = (long)(puVar2 + 0x10);
  puVar1 = PTR__ZTVN4Aska11TPoolLegacyINS_16BGMControlObjectELb0EEE_02cba3c8;
  plVar3 = param_1 + 0xf;
  param_1[0x15] = (long)(puVar2 + 0x10);
  param_1[0xb] = (long)(puVar1 + 0x10);
  if ((*plVar3 != 0) && ((char)param_1[0x11] != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 0x11) = 0;
  }
  *plVar3 = 0;
  param_1[0x10] = 0;
  param_1[0x12] = 0;
  if (param_1[0x13] == 0) {
    param_1[0xd] = (long)(PTR__ZTVN4Aska9TBitArrayIjLb0EEE_02cba038 + 0x10);
  }
  else if ((char)param_1[0x14] == '\0') {
    param_1[0xd] = (long)(PTR__ZTVN4Aska9TBitArrayIjLb0EEE_02cba038 + 0x10);
    param_1[0x13] = 0;
  }
  else {
    operator delete[](void*)();
    param_1[0xd] = (long)(PTR__ZTVN4Aska9TBitArrayIjLb0EEE_02cba038 + 0x10);
    param_1[0x13] = 0;
    if ((param_1[0xf] != 0) && ((char)param_1[0x11] != '\0')) {
      operator delete[](void*)();
      *(undefined1 *)(param_1 + 0x11) = 0;
    }
  }
  *plVar3 = 0;
  param_1[0x10] = 0;
  param_1[0xd] = (long)(puVar2 + 0x10);
  puVar1 = PTR__ZTVN4Aska11TPoolLegacyINS_15SEControlObjectELb0EEE_02cbe858;
  plVar3 = param_1 + 5;
  param_1[0xb] = (long)(puVar2 + 0x10);
  param_1[1] = (long)(puVar1 + 0x10);
  if ((*plVar3 != 0) && ((char)param_1[7] != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 7) = 0;
  }
  *plVar3 = 0;
  param_1[6] = 0;
  param_1[8] = 0;
  if (param_1[9] == 0) {
    param_1[3] = (long)(PTR__ZTVN4Aska9TBitArrayIjLb0EEE_02cba038 + 0x10);
  }
  else if ((char)param_1[10] == '\0') {
    param_1[3] = (long)(PTR__ZTVN4Aska9TBitArrayIjLb0EEE_02cba038 + 0x10);
    param_1[9] = 0;
  }
  else {
    operator delete[](void*)();
    param_1[3] = (long)(PTR__ZTVN4Aska9TBitArrayIjLb0EEE_02cba038 + 0x10);
    param_1[9] = 0;
    if ((param_1[5] != 0) && ((char)param_1[7] != '\0')) {
      operator delete[](void*)();
      *(undefined1 *)(param_1 + 7) = 0;
    }
  }
  *plVar3 = 0;
  param_1[6] = 0;
  param_1[3] = (long)(puVar2 + 0x10);
  param_1[1] = (long)(puVar2 + 0x10);
  return;
}

// ==== Aska::SoundServer::~SoundServer()
// vaddr 0x1f7898c | ghidra 0x207898c | size 24 | symbol _ZN4Aska11SoundServerD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska11SoundServerD0Ev(undefined8 param_1)

{
  Aska::SoundServer::~SoundServer()();
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::TPoolLegacy<Aska::SoundServer::AskaAdpcmDecodeBuffer, false>::~TPoolLegacy()
// vaddr 0x1f79764 | ghidra 0x2079764 | size 220 | symbol _ZN4Aska11TPoolLegacyINS_11SoundServer21AskaAdpcmDecodeBufferELb0EED2Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska11TPoolLegacyINS_11SoundServer21AskaAdpcmDecodeBufferELb0EED2Ev(long *param_1)

{
  undefined *puVar1;
  long *plVar2;
  
  *param_1 = (long)(
                   PTR__ZTVN4Aska11TPoolLegacyINS_11SoundServer21AskaAdpcmDecodeBufferELb0EEE_02cc1e68
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

// ==== Aska::TPoolLegacy<Aska::SoundServer::AskaAdpcmDecodeBuffer, false>::~TPoolLegacy()
// vaddr 0x1f79840 | ghidra 0x2079840 | size 220 | symbol _ZN4Aska11TPoolLegacyINS_11SoundServer21AskaAdpcmDecodeBufferELb0EED0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska11TPoolLegacyINS_11SoundServer21AskaAdpcmDecodeBufferELb0EED0Ev(long *param_1)

{
  long *plVar1;
  
  *param_1 = (long)(
                   PTR__ZTVN4Aska11TPoolLegacyINS_11SoundServer21AskaAdpcmDecodeBufferELb0EEE_02cc1e68
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

// ==== Aska::TPoolLegacy<Aska::SoundServer::FilePathBuffer, false>::~TPoolLegacy()
// vaddr 0x1f7991c | ghidra 0x207991c | size 220 | symbol _ZN4Aska11TPoolLegacyINS_11SoundServer14FilePathBufferELb0EED2Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska11TPoolLegacyINS_11SoundServer14FilePathBufferELb0EED2Ev(long *param_1)

{
  undefined *puVar1;
  long *plVar2;
  
  *param_1 = (long)(PTR__ZTVN4Aska11TPoolLegacyINS_11SoundServer14FilePathBufferELb0EEE_02cbe0c0 +
                   0x10);
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

// ==== Aska::TPoolLegacy<Aska::SoundServer::FilePathBuffer, false>::~TPoolLegacy()
// vaddr 0x1f799f8 | ghidra 0x20799f8 | size 220 | symbol _ZN4Aska11TPoolLegacyINS_11SoundServer14FilePathBufferELb0EED0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska11TPoolLegacyINS_11SoundServer14FilePathBufferELb0EED0Ev(long *param_1)

{
  long *plVar1;
  
  *param_1 = (long)(PTR__ZTVN4Aska11TPoolLegacyINS_11SoundServer14FilePathBufferELb0EEE_02cbe0c0 +
                   0x10);
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

// ==== Aska::SoundUtility::GetDspEffectParamSize(Aska::ESound::EDspEffect)
// vaddr 0x1f79ad4 | ghidra 0x2079ad4 | size 8 | symbol _ZN4Aska12SoundUtility21GetDspEffectParamSizeENS_6ESound10EDspEffectE | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska12SoundUtility21GetDspEffectParamSizeENS_6ESound10EDspEffectE(void)

{
  return 0;
}

// ==== Aska::SoundUtility::GetDefaultSpeakerAssign(unsigned char*, int)
// vaddr 0x1f79adc | ghidra 0x2079adc | size 112 | symbol _ZN4Aska12SoundUtility23GetDefaultSpeakerAssignEPhi | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12SoundUtility23GetDefaultSpeakerAssignEPhi(undefined4 *param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  undefined1 uVar2;
  
  uVar2 = 4;
  puVar1 = param_1;
  switch(param_2) {
  case 1:
    break;
  case 2:
    puVar1 = (undefined4 *)((long)param_1 + 1);
    *(undefined1 *)param_1 = 1;
    uVar2 = 2;
    break;
  default:
    goto code_r0x02079b48;
  case 4:
    *(undefined2 *)param_1 = 0x201;
    *(undefined1 *)((long)param_1 + 2) = 0x10;
    puVar1 = (undefined4 *)((long)param_1 + 3);
    goto code_r0x02079b40;
  case 6:
    *param_1 = 0x8040201;
    *(undefined1 *)(param_1 + 1) = 0x10;
    puVar1 = (undefined4 *)((long)param_1 + 5);
code_r0x02079b40:
    uVar2 = 0x20;
  }
  *(undefined1 *)puVar1 = uVar2;
code_r0x02079b48:
  return;
}

// ==== Aska::SoundUtility::VolumeDBBlend(float, float)
// vaddr 0x1f79b4c | ghidra 0x2079b4c | size 32 | symbol _ZN4Aska12SoundUtility13VolumeDBBlendEff | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float _ZN4Aska12SoundUtility13VolumeDBBlendEff(float param_1,float param_2)

{
  float fVar1;
  float fVar2;
  
  fVar2 = (float)NEON_fminnm(param_1 + param_2,0x41400000);
  fVar1 = _UNK_02965bf8;
  if (_UNK_02965bf8 <= param_1 + param_2) {
    fVar1 = fVar2;
  }
  return fVar1;
}

// ==== Aska::SoundUtility::PitchBlend(float, float)
// vaddr 0x1f79b6c | ghidra 0x2079b6c | size 28 | symbol _ZN4Aska12SoundUtility10PitchBlendEff | lib libSOA-3.7.0.so | 2026-10-08
undefined4 _ZN4Aska12SoundUtility10PitchBlendEff(float param_1,float param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  uVar2 = NEON_fminnm(param_1 + param_2,0x40000000);
  uVar1 = 0xc1400000;
  if (-12.0 <= param_1 + param_2) {
    uVar1 = uVar2;
  }
  return uVar1;
}

// ==== Aska::SoundUtility::CalcLoopAndOffset(unsigned int*, unsigned int*, unsigned int*, Aska::AFF::AaoWAVE const*, unsigned int)
// vaddr 0x1f79b88 | ghidra 0x2079b88 | size 828 | symbol _ZN4Aska12SoundUtility17CalcLoopAndOffsetEPjS1_S1_PKNS_3AFF7AaoWAVEEj | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8
_ZN4Aska12SoundUtility17CalcLoopAndOffsetEPjS1_S1_PKNS_3AFF7AaoWAVEEj
          (int *param_1,uint *param_2,uint *param_3,long param_4,uint param_5)

{
  undefined8 *puVar1;
  undefined8 *puVar2;
  undefined8 *puVar3;
  int iVar4;
  uint uVar5;
  undefined4 uVar6;
  undefined2 uVar7;
  undefined8 *puVar8;
  int *piVar9;
  long lVar10;
  long lVar11;
  long lVar12;
  uint uVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  int iVar17;
  int iVar18;
  int iVar19;
  int iVar20;
  int iVar21;
  undefined8 uVar22;
  
  iVar4 = Aska::AFF::AacUtil::GetBitRateType(Aska::AACWAVFORMAT)(*(undefined1 *)(param_4 + 0x14));
  if (iVar4 != 1) {
    if (iVar4 != 0) {
      return 1;
    }
    uVar5 = *(uint *)(param_4 + 0x44);
    *param_1 = *(int *)(param_4 + 0x40);
    *param_2 = uVar5;
    if (param_5 == 0) {
      return 1;
    }
    if (*(char *)(param_4 + 0x14) == '\r') {
      uVar6 = *(undefined4 *)(param_4 + 0x54);
      uVar7 = *(undefined2 *)(param_4 + 0x60);
    }
    else {
      uVar7 = 0;
      uVar6 = 0;
    }
    uVar5 = Aska::AFF::AacUtil::ConvertMsec2Byte(unsigned int, Aska::AACWAVFORMAT, int, int, int, int, int)(param_5,*(char *)(param_4 + 0x14),*(undefined1 *)(param_4 + 0x15),
                            *(undefined4 *)(param_4 + 0x18),*(undefined1 *)(param_4 + 0x17),uVar6,
                            uVar7);
    if (uVar5 < *param_2) {
      *param_3 = uVar5;
      return 1;
    }
    return 0;
  }
  uVar5 = *(uint *)(param_4 + 0x58);
  uVar13 = uVar5;
  if (*(char *)(param_4 + 0x14) == '\x0e') {
    uVar13 = 0;
    if (uVar5 != 0) {
      uVar13 = uVar5 - 1;
    }
  }
  if ((*(int *)(param_4 + 0x50) == 0) && (*(int *)(param_4 + 0x54) == 0)) {
    uVar13 = *(uint *)(param_4 + 0x1c);
    iVar14 = 0;
  }
  else {
    iVar4 = *(int *)(param_4 + 0x40);
    if (iVar4 == 0) {
      if (*(uint *)(param_4 + 0x70) == 0) {
        iVar14 = 0;
      }
      else {
        iVar14 = 0;
        if (uVar13 != 0) {
          lVar11 = (ulong)*(uint *)(param_4 + 0x70) + param_4;
          if (uVar13 < 8) {
            lVar10 = 0;
code_r0x02079d24:
            iVar14 = 0;
          }
          else {
            lVar10 = (ulong)uVar13 - (ulong)(uVar13 & 7);
            if (lVar10 == 0) goto code_r0x02079d24;
            puVar8 = (undefined8 *)(lVar11 + 0x10);
            iVar14 = 0;
            iVar15 = 0;
            iVar16 = 0;
            iVar17 = 0;
            iVar18 = 0;
            iVar19 = 0;
            iVar21 = 0;
            iVar20 = 0;
            lVar12 = lVar10;
            do {
              puVar1 = puVar8 + -2;
              puVar2 = puVar8 + -1;
              puVar3 = puVar8 + 1;
              uVar22 = *puVar8;
              lVar12 = lVar12 + -8;
              puVar8 = puVar8 + 4;
              iVar14 = (int)*puVar1 + iVar14;
              iVar15 = (int)((ulong)*puVar1 >> 0x20) + iVar15;
              iVar16 = (int)*puVar2 + iVar16;
              iVar17 = (int)((ulong)*puVar2 >> 0x20) + iVar17;
              iVar18 = (int)uVar22 + iVar18;
              iVar19 = (int)((ulong)uVar22 >> 0x20) + iVar19;
              iVar21 = (int)*puVar3 + iVar21;
              iVar20 = (int)((ulong)*puVar3 >> 0x20) + iVar20;
            } while (lVar12 != 0);
            iVar14 = iVar18 + iVar14 + iVar19 + iVar15 + iVar21 + iVar16 + iVar20 + iVar17;
            if ((uVar13 & 7) == 0) goto code_r0x02079c20;
          }
          lVar12 = (ulong)uVar13 - lVar10;
          piVar9 = (int *)(lVar11 + lVar10 * 4);
          do {
            lVar12 = lVar12 + -1;
            iVar14 = *piVar9 + iVar14;
            piVar9 = piVar9 + 1;
          } while (lVar12 != 0);
        }
      }
    }
    else {
      iVar14 = iVar4 * uVar13;
    }
code_r0x02079c20:
    uVar5 = *(int *)(param_4 + 0x5c) + 1;
    if (uVar5 == *(uint *)(param_4 + 0x44)) {
      uVar13 = *(uint *)(param_4 + 0x1c);
    }
    else if (iVar4 == 0) {
      if (*(uint *)(param_4 + 0x70) == 0) {
        uVar13 = 0;
      }
      else {
        uVar13 = 0;
        if (uVar5 != 0) {
          lVar11 = (ulong)*(uint *)(param_4 + 0x70) + param_4;
          if (uVar5 < 8) {
            lVar10 = 0;
code_r0x02079d94:
            uVar13 = 0;
          }
          else {
            lVar10 = (ulong)uVar5 - (ulong)(uVar5 & 7);
            if (lVar10 == 0) goto code_r0x02079d94;
            puVar8 = (undefined8 *)(lVar11 + 0x10);
            iVar4 = 0;
            iVar15 = 0;
            iVar16 = 0;
            iVar17 = 0;
            iVar18 = 0;
            iVar19 = 0;
            iVar21 = 0;
            iVar20 = 0;
            lVar12 = lVar10;
            do {
              puVar1 = puVar8 + -2;
              puVar2 = puVar8 + -1;
              puVar3 = puVar8 + 1;
              uVar22 = *puVar8;
              lVar12 = lVar12 + -8;
              puVar8 = puVar8 + 4;
              iVar4 = (int)*puVar1 + iVar4;
              iVar15 = (int)((ulong)*puVar1 >> 0x20) + iVar15;
              iVar16 = (int)*puVar2 + iVar16;
              iVar17 = (int)((ulong)*puVar2 >> 0x20) + iVar17;
              iVar18 = (int)uVar22 + iVar18;
              iVar19 = (int)((ulong)uVar22 >> 0x20) + iVar19;
              iVar21 = (int)*puVar3 + iVar21;
              iVar20 = (int)((ulong)*puVar3 >> 0x20) + iVar20;
            } while (lVar12 != 0);
            uVar13 = iVar18 + iVar4 + iVar19 + iVar15 + iVar21 + iVar16 + iVar20 + iVar17;
            if ((uVar5 & 7) == 0) goto code_r0x02079db0;
          }
          lVar12 = (ulong)uVar5 - lVar10;
          piVar9 = (int *)(lVar11 + lVar10 * 4);
          do {
            lVar12 = lVar12 + -1;
            uVar13 = *piVar9 + uVar13;
            piVar9 = piVar9 + 1;
          } while (lVar12 != 0);
        }
      }
    }
    else {
      uVar13 = iVar4 * uVar5;
    }
  }
code_r0x02079db0:
  *param_1 = iVar14;
  *param_2 = uVar13;
  if (param_5 == 0) {
    return 1;
  }
  if (*(uint *)(param_4 + 0x44) != 0) {
    uVar5 = 0;
    do {
      if ((uint)(int)(((float)*(int *)(param_4 + 0x18) / _UNK_027e51a0) * (float)param_5) <=
          *(uint *)((ulong)*(uint *)(param_4 + 0x48) + param_4 + (ulong)uVar5 * 4))
      goto code_r0x02079e0c;
      uVar5 = uVar5 + 1;
    } while (uVar5 < *(uint *)(param_4 + 0x44));
  }
  uVar5 = 0;
code_r0x02079e0c:
  if (*(int *)(param_4 + 0x40) != 0) {
    uVar13 = *(int *)(param_4 + 0x40) * uVar5;
    goto code_r0x02079eac;
  }
  if ((*(uint *)(param_4 + 0x70) == 0) || (uVar5 == 0)) {
    uVar13 = 0;
    goto code_r0x02079eac;
  }
  param_4 = (ulong)*(uint *)(param_4 + 0x70) + param_4;
  if (uVar5 < 8) {
    lVar11 = 0;
code_r0x02079e90:
    uVar13 = 0;
  }
  else {
    lVar11 = (ulong)uVar5 - (ulong)(uVar5 & 7);
    if (lVar11 == 0) goto code_r0x02079e90;
    puVar8 = (undefined8 *)(param_4 + 0x10);
    iVar4 = 0;
    iVar14 = 0;
    iVar15 = 0;
    iVar16 = 0;
    iVar17 = 0;
    iVar18 = 0;
    iVar19 = 0;
    iVar21 = 0;
    lVar10 = lVar11;
    do {
      puVar1 = puVar8 + -2;
      puVar2 = puVar8 + -1;
      puVar3 = puVar8 + 1;
      uVar22 = *puVar8;
      lVar10 = lVar10 + -8;
      puVar8 = puVar8 + 4;
      iVar4 = (int)*puVar1 + iVar4;
      iVar14 = (int)((ulong)*puVar1 >> 0x20) + iVar14;
      iVar15 = (int)*puVar2 + iVar15;
      iVar16 = (int)((ulong)*puVar2 >> 0x20) + iVar16;
      iVar17 = (int)uVar22 + iVar17;
      iVar18 = (int)((ulong)uVar22 >> 0x20) + iVar18;
      iVar19 = (int)*puVar3 + iVar19;
      iVar21 = (int)((ulong)*puVar3 >> 0x20) + iVar21;
    } while (lVar10 != 0);
    uVar13 = iVar17 + iVar4 + iVar18 + iVar14 + iVar19 + iVar15 + iVar21 + iVar16;
    if ((uVar5 & 7) == 0) goto code_r0x02079eac;
  }
  lVar10 = (ulong)uVar5 - lVar11;
  piVar9 = (int *)(param_4 + lVar11 * 4);
  do {
    lVar10 = lVar10 + -1;
    uVar13 = *piVar9 + uVar13;
    piVar9 = piVar9 + 1;
  } while (lVar10 != 0);
code_r0x02079eac:
  *param_3 = uVar13;
  return 1;
}

// ==== Aska::SoundUtility::CalcBlockOffsetByte(unsigned int, Aska::AFF::AaoVBRWAVE const*)
// vaddr 0x1f79ec4 | ghidra 0x2079ec4 | size 164 | symbol _ZN4Aska12SoundUtility19CalcBlockOffsetByteEjPKNS_3AFF10AaoVBRWAVEE | lib libSOA-3.7.0.so | 2026-10-08
ulong _ZN4Aska12SoundUtility19CalcBlockOffsetByteEjPKNS_3AFF10AaoVBRWAVEE
                (ulong param_1,long param_2)

{
  undefined8 *puVar1;
  undefined8 *puVar2;
  undefined8 *puVar3;
  uint uVar4;
  ulong uVar5;
  int *piVar6;
  long lVar7;
  long lVar8;
  undefined8 *puVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  int iVar17;
  undefined8 uVar18;
  
  uVar4 = (uint)param_1;
  if (*(int *)(param_2 + 0x40) != 0) {
    return (ulong)(*(int *)(param_2 + 0x40) * uVar4);
  }
  if (*(uint *)(param_2 + 0x70) == 0) {
    return 0;
  }
  if (uVar4 == 0) {
    return param_1;
  }
  param_2 = (ulong)*(uint *)(param_2 + 0x70) + param_2;
  if (uVar4 < 8) {
    lVar8 = 0;
  }
  else {
    lVar8 = (param_1 & 0xffffffff) - (ulong)(uVar4 & 7);
    if (lVar8 != 0) {
      puVar9 = (undefined8 *)(param_2 + 0x10);
      iVar10 = 0;
      iVar11 = 0;
      iVar12 = 0;
      iVar13 = 0;
      iVar14 = 0;
      iVar15 = 0;
      iVar16 = 0;
      iVar17 = 0;
      lVar7 = lVar8;
      do {
        puVar1 = puVar9 + -2;
        puVar2 = puVar9 + -1;
        puVar3 = puVar9 + 1;
        uVar18 = *puVar9;
        lVar7 = lVar7 + -8;
        puVar9 = puVar9 + 4;
        iVar10 = (int)*puVar1 + iVar10;
        iVar11 = (int)((ulong)*puVar1 >> 0x20) + iVar11;
        iVar12 = (int)*puVar2 + iVar12;
        iVar13 = (int)((ulong)*puVar2 >> 0x20) + iVar13;
        iVar14 = (int)uVar18 + iVar14;
        iVar15 = (int)((ulong)uVar18 >> 0x20) + iVar15;
        iVar16 = (int)*puVar3 + iVar16;
        iVar17 = (int)((ulong)*puVar3 >> 0x20) + iVar17;
      } while (lVar7 != 0);
      uVar5 = (ulong)(uint)(iVar14 + iVar10 + iVar15 + iVar11 + iVar16 + iVar12 + iVar17 + iVar13);
      if ((param_1 & 7) == 0) {
        return uVar5;
      }
      goto code_r0x02079f4c;
    }
  }
  uVar5 = 0;
code_r0x02079f4c:
  lVar7 = (param_1 & 0xffffffff) - lVar8;
  piVar6 = (int *)(param_2 + lVar8 * 4);
  do {
    lVar7 = lVar7 + -1;
    uVar5 = (ulong)(uint)(*piVar6 + (int)uVar5);
    piVar6 = piVar6 + 1;
  } while (lVar7 != 0);
  return uVar5;
}

// ==== Aska::SoundUtility::CalcSampleInBlock(unsigned int*, unsigned int*, unsigned int*, unsigned int, Aska::AFF::AaoVBRWAVE const*)
// vaddr 0x1f79f68 | ghidra 0x2079f68 | size 128 | symbol _ZN4Aska12SoundUtility17CalcSampleInBlockEPjS1_S1_jPKNS_3AFF10AaoVBRWAVEE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12SoundUtility17CalcSampleInBlockEPjS1_S1_jPKNS_3AFF10AaoVBRWAVEE
               (uint *param_1,int *param_2,uint *param_3,uint param_4,long param_5)

{
  long lVar1;
  int iVar2;
  uint uVar3;
  long lVar4;
  
  if (*(uint *)(param_5 + 0x44) != 0) {
    uVar3 = 0;
    lVar1 = (ulong)*(uint *)(param_5 + 0x48) + param_5;
    do {
      if (param_4 <= *(uint *)(lVar1 + (ulong)uVar3 * 4)) {
        *param_1 = uVar3;
        iVar2 = *(int *)(lVar1 + (ulong)uVar3 * 4);
        if (uVar3 != 0) {
          lVar4 = (ulong)(uVar3 - 1) * 4;
          *param_2 = iVar2 - *(int *)(lVar1 + lVar4);
          *param_3 = param_4 - *(int *)(lVar1 + lVar4);
          return;
        }
        *param_2 = iVar2;
        *param_3 = param_4;
        return;
      }
      uVar3 = uVar3 + 1;
    } while (uVar3 < *(uint *)(param_5 + 0x44));
  }
  *param_1 = 0;
  *param_2 = 0;
  *param_3 = 0;
  return;
}

// ==== Aska::SoundUtility::CalcLoopCount(int, int)
// vaddr 0x1f79fe8 | ghidra 0x2079fe8 | size 28 | symbol _ZN4Aska12SoundUtility13CalcLoopCountEii | lib libSOA-3.7.0.so | 2026-10-08
ulong _ZN4Aska12SoundUtility13CalcLoopCountEii(ulong param_1,uint param_2)

{
  uint uVar1;
  uint uVar2;
  
  uVar2 = (uint)param_1;
  if (uVar2 != 0xffffffff) {
    uVar1 = 0;
    if (param_2 != 0xffffffff) {
      uVar1 = param_2;
    }
    if ((int)uVar2 <= (int)uVar1) {
      uVar2 = uVar1;
    }
    param_1 = (ulong)uVar2;
  }
  return param_1;
}

// ==== Aska::SoundUtility::DownMix_To4(float*, float const*, int)
// vaddr 0x1f7a004 | ghidra 0x207a004 | size 972 | symbol _ZN4Aska12SoundUtility11DownMix_To4EPfPKfi | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska12SoundUtility11DownMix_To4EPfPKfi(float *param_1,float *param_2,int param_3)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  
  memset(param_1,0,0x90);
  fVar4 = _UNK_02965bf8;
  fVar5 = _UNK_027fac84;
  if (param_3 < 1) {
    return;
  }
  fVar3 = _UNK_02965bf8;
  if (_UNK_027fac84 <= ABS(param_2[2])) {
    fVar3 = (float)log10f();
    fVar3 = fVar3 * 20.0;
  }
  fVar6 = *param_2;
  if (fVar3 + -3.0 <= fVar4) {
    fVar7 = param_2[1];
    fVar4 = 0.0;
    fVar3 = 0.0;
  }
  else {
    fVar3 = (fVar3 + -3.0) * _UNK_027edb4c;
    fVar4 = (float)powf(0x41200000,fVar3);
    fVar7 = param_2[1];
    fVar3 = (float)powf(0x41200000,fVar3);
  }
  fVar8 = param_2[4];
  fVar1 = param_2[5];
  *param_1 = fVar6 + fVar4;
  param_1[1] = fVar7 + fVar3;
  param_1[4] = fVar8;
  param_1[5] = fVar1;
  if (param_3 < 2) {
    return;
  }
  fVar4 = _UNK_02972434;
  if (fVar5 <= ABS(param_2[8])) {
    fVar4 = (float)log10f();
    fVar4 = fVar4 * 20.0 + -3.0;
  }
  fVar3 = _UNK_02965bf8;
  fVar6 = param_2[6];
  if (fVar4 <= _UNK_02965bf8) {
    fVar8 = param_2[7];
    fVar7 = 0.0;
    fVar4 = 0.0;
  }
  else {
    fVar4 = fVar4 * _UNK_027edb4c;
    fVar7 = (float)powf(0x41200000,fVar4);
    fVar8 = param_2[7];
    fVar4 = (float)powf(0x41200000,fVar4);
  }
  fVar1 = param_2[10];
  fVar2 = param_2[0xb];
  param_1[6] = fVar6 + fVar7;
  param_1[7] = fVar8 + fVar4;
  param_1[10] = fVar1;
  param_1[0xb] = fVar2;
  if (param_3 < 3) {
    return;
  }
  if (fVar5 <= ABS(param_2[0xe])) {
    fVar4 = (float)log10f();
    fVar6 = param_2[0xc];
    fVar4 = fVar4 * 20.0 + -3.0;
    if (fVar4 <= fVar3) goto code_r0x0207a1e0;
    fVar4 = fVar4 * _UNK_027edb4c;
    fVar7 = (float)powf(0x41200000,fVar4);
    fVar8 = param_2[0xd];
    fVar4 = (float)powf(0x41200000,fVar4);
  }
  else {
    fVar6 = param_2[0xc];
code_r0x0207a1e0:
    fVar8 = param_2[0xd];
    fVar7 = 0.0;
    fVar4 = 0.0;
  }
  fVar1 = param_2[0x10];
  fVar2 = param_2[0x11];
  param_1[0xc] = fVar6 + fVar7;
  param_1[0xd] = fVar8 + fVar4;
  param_1[0x10] = fVar1;
  param_1[0x11] = fVar2;
  if (param_3 < 4) {
    return;
  }
  if (fVar5 <= ABS(param_2[0x14])) {
    fVar4 = (float)log10f();
    fVar6 = param_2[0x12];
    fVar4 = fVar4 * 20.0 + -3.0;
    if (fVar4 <= fVar3) goto code_r0x0207a270;
    fVar4 = fVar4 * _UNK_027edb4c;
    fVar7 = (float)powf(0x41200000,fVar4);
    fVar8 = param_2[0x13];
    fVar4 = (float)powf(0x41200000,fVar4);
  }
  else {
    fVar6 = param_2[0x12];
code_r0x0207a270:
    fVar8 = param_2[0x13];
    fVar7 = 0.0;
    fVar4 = 0.0;
  }
  fVar1 = param_2[0x16];
  fVar2 = param_2[0x17];
  param_1[0x12] = fVar6 + fVar7;
  param_1[0x13] = fVar8 + fVar4;
  param_1[0x16] = fVar1;
  param_1[0x17] = fVar2;
  if (param_3 < 5) {
    return;
  }
  if (fVar5 <= ABS(param_2[0x1a])) {
    fVar4 = (float)log10f();
    fVar6 = param_2[0x18];
    fVar4 = fVar4 * 20.0 + -3.0;
    if (fVar4 <= fVar3) goto code_r0x0207a300;
    fVar4 = fVar4 * _UNK_027edb4c;
    fVar7 = (float)powf(0x41200000,fVar4);
    fVar8 = param_2[0x19];
    fVar4 = (float)powf(0x41200000,fVar4);
  }
  else {
    fVar6 = param_2[0x18];
code_r0x0207a300:
    fVar8 = param_2[0x19];
    fVar7 = 0.0;
    fVar4 = 0.0;
  }
  fVar1 = param_2[0x1c];
  fVar2 = param_2[0x1d];
  param_1[0x18] = fVar6 + fVar7;
  param_1[0x19] = fVar8 + fVar4;
  param_1[0x1c] = fVar1;
  param_1[0x1d] = fVar2;
  if (param_3 < 6) {
    return;
  }
  if (fVar5 <= ABS(param_2[0x20])) {
    fVar5 = (float)log10f();
    fVar4 = param_2[0x1e];
    fVar5 = fVar5 * 20.0 + -3.0;
    if (fVar3 < fVar5) {
      fVar5 = fVar5 * _UNK_027edb4c;
      fVar3 = (float)powf(0x41200000,fVar5);
      fVar6 = param_2[0x1f];
      fVar5 = (float)powf(0x41200000,fVar5);
      goto code_r0x0207a39c;
    }
  }
  else {
    fVar4 = param_2[0x1e];
  }
  fVar6 = param_2[0x1f];
  fVar3 = 0.0;
  fVar5 = 0.0;
code_r0x0207a39c:
  fVar7 = param_2[0x22];
  fVar8 = param_2[0x23];
  param_1[0x1e] = fVar4 + fVar3;
  param_1[0x1f] = fVar6 + fVar5;
  param_1[0x22] = fVar7;
  param_1[0x23] = fVar8;
  return;
}

// ==== Aska::SoundUtility::DownMix_To2(float*, float const*, int, bool)
// vaddr 0x1f7a3d0 | ghidra 0x207a3d0 | size 896 | symbol _ZN4Aska12SoundUtility11DownMix_To2EPfPKfib | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska12SoundUtility11DownMix_To2EPfPKfib(long param_1,long param_2,int param_3,uint param_4)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float *pfVar4;
  float *pfVar5;
  long lVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  
  memset(param_1,0,0x90);
  fVar15 = _UNK_0297243c;
  fVar13 = _UNK_02972438;
  fVar3 = _UNK_02965bf8;
  fVar2 = _UNK_027fac84;
  fVar1 = _UNK_027edb4c;
  if ((param_4 & 1) == 0) {
    lVar6 = 0;
    pfVar4 = (float *)(param_1 + 4);
    pfVar5 = (float *)(param_2 + 0x10);
    do {
      if (lVar6 < param_3) {
        fVar15 = pfVar5[-4];
        fVar7 = pfVar5[-3];
        fVar13 = fVar3;
        if (fVar2 <= ABS(*pfVar5)) {
          fVar13 = (float)log10f();
          fVar13 = fVar13 * 20.0;
        }
        fVar14 = fVar3;
        if (fVar2 <= ABS(pfVar5[1])) {
          fVar14 = (float)log10f();
          fVar14 = fVar14 * 20.0;
        }
        fVar8 = 0.0;
        fVar16 = 0.0;
        if (fVar3 < fVar13 + -3.0) {
          fVar16 = (float)powf(0x41200000,(fVar13 + -3.0) * fVar1);
        }
        if (fVar3 < fVar14 + -3.0) {
          fVar8 = (float)powf(0x41200000,(fVar14 + -3.0) * fVar1);
        }
        fVar15 = fVar15 + fVar16;
        fVar7 = fVar7 + fVar8;
        if (5 < param_3) {
          fVar13 = fVar3;
          if (fVar2 <= ABS(pfVar5[-2])) {
            fVar13 = (float)log10f();
            fVar13 = fVar13 * 20.0;
          }
          fVar14 = 0.0;
          fVar16 = 0.0;
          if (fVar3 < fVar13 + -3.0) {
            fVar13 = (fVar13 + -3.0) * fVar1;
            fVar14 = (float)powf(0x41200000,fVar13);
            fVar16 = (float)powf(0x41200000,fVar13);
          }
          fVar15 = fVar15 + fVar14;
          fVar7 = fVar7 + fVar16;
        }
        pfVar4[-1] = fVar15;
        *pfVar4 = fVar7;
      }
      lVar6 = lVar6 + 1;
      pfVar4 = pfVar4 + 6;
      pfVar5 = pfVar5 + 6;
    } while (lVar6 != 6);
  }
  else {
    lVar6 = 0;
    pfVar4 = (float *)(param_2 + 0x10);
    pfVar5 = (float *)(param_1 + 4);
    do {
      if (lVar6 < param_3) {
        fVar14 = pfVar4[-4];
        fVar16 = pfVar4[-3];
        fVar7 = fVar3;
        if (fVar2 <= ABS(*pfVar4)) {
          fVar7 = (float)log10f();
          fVar7 = fVar7 * 20.0;
        }
        fVar8 = fVar3;
        if (fVar2 <= ABS(pfVar4[1])) {
          fVar8 = (float)log10f();
          fVar8 = fVar8 * 20.0;
        }
        fVar11 = 0.0;
        fVar10 = 0.0;
        fVar9 = fVar7 + fVar13;
        if (fVar3 < fVar9) {
          fVar10 = (float)powf(0x41200000,fVar9 * fVar1);
        }
        fVar9 = fVar8 + fVar15;
        if (fVar3 < fVar9) {
          fVar11 = (float)powf(0x41200000,fVar9 * fVar1);
        }
        fVar8 = fVar8 + fVar13;
        fVar12 = 0.0;
        fVar9 = 0.0;
        if (fVar3 < fVar8) {
          fVar9 = (float)powf(0x41200000,fVar8 * fVar1);
        }
        fVar7 = fVar7 + fVar15;
        if (fVar3 < fVar7) {
          fVar12 = (float)powf(0x41200000,fVar7 * fVar1);
        }
        fVar11 = fVar14 + fVar10 + fVar11;
        fVar12 = fVar16 + fVar9 + fVar12;
        if (5 < param_3) {
          fVar7 = fVar3;
          if (fVar2 <= ABS(pfVar4[-2])) {
            fVar7 = (float)log10f();
            fVar7 = fVar7 * 20.0;
          }
          fVar14 = 0.0;
          fVar16 = 0.0;
          if (fVar3 < fVar7 + -3.0) {
            fVar7 = (fVar7 + -3.0) * fVar1;
            fVar14 = (float)powf(0x41200000,fVar7);
            fVar16 = (float)powf(0x41200000,fVar7);
          }
          fVar11 = fVar11 + fVar14;
          fVar12 = fVar12 + fVar16;
        }
        pfVar5[-1] = fVar11;
        *pfVar5 = fVar12;
      }
      lVar6 = lVar6 + 1;
      pfVar4 = pfVar4 + 6;
      pfVar5 = pfVar5 + 6;
    } while (lVar6 != 6);
  }
  return;
}

// ==== Aska::SoundUtility::DownMix_2To1(float*, float const*)
// vaddr 0x1f7a750 | ghidra 0x207a750 | size 64 | symbol _ZN4Aska12SoundUtility12DownMix_2To1EPfPKf | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12SoundUtility12DownMix_2To1EPfPKf(long param_1,float *param_2)

{
  memset(param_1,0,0x90);
  *(float *)(param_1 + 8) = *param_2 + param_2[1];
  *(float *)(param_1 + 0x20) = param_2[6] + param_2[7];
  return;
}

// ==== Aska::SoundUtility::DownMix_4To1(float*, float const*)
// vaddr 0x1f7a790 | ghidra 0x207a790 | size 136 | symbol _ZN4Aska12SoundUtility12DownMix_4To1EPfPKf | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12SoundUtility12DownMix_4To1EPfPKf(long param_1,float *param_2)

{
  memset(param_1,0,0x90);
  *(float *)(param_1 + 8) = *param_2 + param_2[1] + param_2[4] + param_2[5];
  *(float *)(param_1 + 0x20) = param_2[6] + param_2[7] + param_2[10] + param_2[0xb];
  *(float *)(param_1 + 0x38) = param_2[0xc] + param_2[0xd] + param_2[0x10] + param_2[0x11];
  *(float *)(param_1 + 0x50) = param_2[0x12] + param_2[0x13] + param_2[0x16] + param_2[0x17];
  return;
}

// ==== Aska::SoundUtility::DownMix_51To1(float*, float const*)
// vaddr 0x1f7a818 | ghidra 0x207a818 | size 232 | symbol _ZN4Aska12SoundUtility13DownMix_51To1EPfPKf | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12SoundUtility13DownMix_51To1EPfPKf(long param_1,float *param_2)

{
  memset(param_1,0,0x90);
  *(float *)(param_1 + 8) = *param_2 + param_2[1] + param_2[2] + param_2[4] + param_2[5];
  *(float *)(param_1 + 0x20) = param_2[6] + param_2[7] + param_2[8] + param_2[10] + param_2[0xb];
  *(float *)(param_1 + 0x38) =
       param_2[0xc] + param_2[0xd] + param_2[0xe] + param_2[0x10] + param_2[0x11];
  *(float *)(param_1 + 0x50) =
       param_2[0x12] + param_2[0x13] + param_2[0x14] + param_2[0x16] + param_2[0x17];
  *(float *)(param_1 + 0x68) =
       param_2[0x18] + param_2[0x19] + param_2[0x1a] + param_2[0x1c] + param_2[0x1d];
  *(float *)(param_1 + 0x80) =
       param_2[0x1e] + param_2[0x1f] + param_2[0x20] + param_2[0x22] + param_2[0x23];
  return;
}

// ==== Aska::SoundUtility::UpMix_1To2(float*, float const*)
// vaddr 0x1f7a900 | ghidra 0x207a900 | size 144 | symbol _ZN4Aska12SoundUtility10UpMix_1To2EPfPKf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska12SoundUtility10UpMix_1To2EPfPKf(undefined4 *param_1,float *param_2)

{
  float fVar1;
  undefined4 uVar2;
  
  memset(param_1,0,0x90);
  uVar2 = 0;
  if (_UNK_027fac84 <= ABS(*param_2 + param_2[1])) {
    fVar1 = (float)log10f();
    fVar1 = fVar1 * 20.0 + -3.0;
    uVar2 = 0;
    if (_UNK_02965bf8 < fVar1) {
      uVar2 = powf(0x41200000,fVar1 * _UNK_027edb4c);
    }
  }
  *param_1 = uVar2;
  param_1[1] = uVar2;
  return;
}

// ==== Aska::SoundUtility::UpMix_2To4(float*, float const*)
// vaddr 0x1f7a990 | ghidra 0x207a990 | size 76 | symbol _ZN4Aska12SoundUtility10UpMix_2To4EPfPKf | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12SoundUtility10UpMix_2To4EPfPKf(float *param_1,float *param_2)

{
  float fVar1;
  
  memset(param_1,0,0x90);
  fVar1 = *param_2;
  *param_1 = fVar1 * 0.5;
  param_1[4] = fVar1 * 0.5;
  fVar1 = param_2[7];
  param_1[7] = fVar1 * 0.5;
  param_1[0xb] = fVar1 * 0.5;
  return;
}

// ==== Aska::SoundUtility::UpMix_1To4(float*, float const*)
// vaddr 0x1f7a9dc | ghidra 0x207a9dc | size 148 | symbol _ZN4Aska12SoundUtility10UpMix_1To4EPfPKf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska12SoundUtility10UpMix_1To4EPfPKf(undefined4 *param_1,float *param_2)

{
  float fVar1;
  undefined4 uVar2;
  
  memset(param_1,0,0x90);
  uVar2 = 0;
  if (_UNK_027fac84 <= ABS(*param_2 + param_2[1])) {
    fVar1 = (float)log10f();
    fVar1 = fVar1 * 20.0 + -6.0;
    uVar2 = 0;
    if (_UNK_02965bf8 < fVar1) {
      uVar2 = powf(0x41200000,fVar1 * _UNK_027edb4c);
    }
  }
  *param_1 = uVar2;
  param_1[1] = uVar2;
  param_1[4] = uVar2;
  param_1[5] = uVar2;
  return;
}

// ==== Aska::SoundUtility::UpMix_4To51(float*, float const*)
// vaddr 0x1f7aa70 | ghidra 0x207aa70 | size 88 | symbol _ZN4Aska12SoundUtility11UpMix_4To51EPfPKf | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12SoundUtility11UpMix_4To51EPfPKf(float *param_1,float *param_2)

{
  float fVar1;
  
  memset(param_1,0,0x90);
  fVar1 = *param_2;
  *param_1 = fVar1 * 0.5;
  param_1[2] = fVar1 * 0.5;
  fVar1 = param_2[7];
  param_1[7] = fVar1 * 0.5;
  param_1[8] = fVar1 * 0.5;
  param_1[0x10] = param_2[0x10];
  param_1[0x17] = param_2[0x17];
  return;
}

// ==== Aska::SoundUtility::UpMix_2To51(float*, float const*)
// vaddr 0x1f7aac8 | ghidra 0x207aac8 | size 80 | symbol _ZN4Aska12SoundUtility11UpMix_2To51EPfPKf | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12SoundUtility11UpMix_2To51EPfPKf(float *param_1,float *param_2)

{
  float fVar1;
  
  memset(param_1,0,0x90);
  fVar1 = *param_2 / 3.0;
  *param_1 = fVar1;
  param_1[2] = fVar1;
  param_1[4] = fVar1;
  fVar1 = param_2[7] / 3.0;
  param_1[7] = fVar1;
  param_1[8] = fVar1;
  param_1[0xb] = fVar1;
  return;
}

// ==== Aska::SoundUtility::UpMix_1To51(float*, float const*)
// vaddr 0x1f7ab18 | ghidra 0x207ab18 | size 152 | symbol _ZN4Aska12SoundUtility11UpMix_1To51EPfPKf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska12SoundUtility11UpMix_1To51EPfPKf(undefined4 *param_1,float *param_2)

{
  float fVar1;
  undefined4 uVar2;
  
  memset(param_1,0,0x90);
  uVar2 = 0;
  if (_UNK_027fac84 <= ABS(*param_2 + param_2[1])) {
    fVar1 = (float)log10f();
    fVar1 = fVar1 * 20.0 + -7.0;
    uVar2 = 0;
    if (_UNK_02965bf8 < fVar1) {
      uVar2 = powf(0x41200000,fVar1 * _UNK_027edb4c);
    }
  }
  *param_1 = uVar2;
  param_1[1] = uVar2;
  param_1[2] = uVar2;
  param_1[4] = uVar2;
  param_1[5] = uVar2;
  return;
}

// ==== Aska::SoundUtility::PhysicalStereoDownMix(float*, float const*)
// vaddr 0x1f7abb0 | ghidra 0x207abb0 | size 124 | symbol _ZN4Aska12SoundUtility21PhysicalStereoDownMixEPfPKf | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12SoundUtility21PhysicalStereoDownMixEPfPKf(float *param_1,float *param_2)

{
  int iVar1;
  undefined8 uVar2;
  float fVar3;
  
  iVar1 = *(int *)(*(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50 + 0x115c);
  if (iVar1 == 2) {
    uVar2 = 1;
  }
  else {
    if (iVar1 != 1) {
      if (iVar1 == 0) {
        param_1[0] = 0.0;
        param_1[1] = 0.0;
        param_1[2] = 0.0;
        param_1[3] = 0.0;
        fVar3 = *param_2 + param_2[1] + param_2[2] + param_2[4] + param_2[5];
        *param_1 = fVar3;
        param_1[1] = fVar3;
        fVar3 = param_2[6] + param_2[7] + param_2[8] + param_2[10] + param_2[0xb];
        param_1[2] = fVar3;
        param_1[3] = fVar3;
      }
      return;
    }
    uVar2 = 0;
  }
  (*(code *)PTR__ZN4Aska12SoundUtility27PhysicalStereoDownMix_51To2EPfPKfb_02cb31e8)
            (param_1,param_2,uVar2);
  return;
}

// ==== Aska::SoundUtility::PhysicalStereoDownMix_51To1(float*, float const*)
// vaddr 0x1f7ac2c | ghidra 0x207ac2c | size 72 | symbol _ZN4Aska12SoundUtility27PhysicalStereoDownMix_51To1EPfPKf | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12SoundUtility27PhysicalStereoDownMix_51To1EPfPKf(float *param_1,float *param_2)

{
  float fVar1;
  
  param_1[0] = 0.0;
  param_1[1] = 0.0;
  param_1[2] = 0.0;
  param_1[3] = 0.0;
  fVar1 = *param_2 + param_2[1] + param_2[2] + param_2[4] + param_2[5];
  *param_1 = fVar1;
  param_1[1] = fVar1;
  fVar1 = param_2[6] + param_2[7] + param_2[8] + param_2[10] + param_2[0xb];
  param_1[2] = fVar1;
  param_1[3] = fVar1;
  return;
}

// ==== Aska::SoundUtility::PhysicalStereoDownMix_51To2(float*, float const*, bool)
// vaddr 0x1f7ac74 | ghidra 0x207ac74 | size 1452 | symbol _ZN4Aska12SoundUtility27PhysicalStereoDownMix_51To2EPfPKfb | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska12SoundUtility27PhysicalStereoDownMix_51To2EPfPKfb
               (float *param_1,float *param_2,uint param_3)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  
  param_1[0] = 0.0;
  param_1[1] = 0.0;
  param_1[2] = 0.0;
  fVar2 = _UNK_02972434;
  fVar11 = _UNK_02965bf8;
  fVar10 = _UNK_027fac84;
  param_1[3] = 0.0;
  fVar12 = *param_2;
  fVar13 = param_2[1];
  if ((param_3 & 1) == 0) {
    fVar11 = _UNK_02972434;
    if (_UNK_027fac84 <= ABS(param_2[4])) {
      fVar11 = (float)log10f();
      fVar11 = fVar11 * 20.0 + -3.0;
    }
    if (fVar10 <= ABS(param_2[5])) {
      fVar2 = (float)log10f();
      fVar2 = fVar2 * 20.0 + -3.0;
    }
    fVar3 = _UNK_02965bf8;
    fVar4 = 0.0;
    fVar8 = 0.0;
    if (_UNK_02965bf8 < fVar11) {
      fVar8 = (float)powf(0x41200000,fVar11 * _UNK_027edb4c);
    }
    if (fVar3 < fVar2) {
      fVar4 = (float)powf(0x41200000,fVar2 * _UNK_027edb4c);
    }
    fVar11 = 0.0;
    if (fVar10 <= ABS(param_2[2])) {
      fVar2 = (float)log10f();
      fVar5 = fVar2 * 20.0 + -3.0;
      fVar2 = 0.0;
      if (fVar3 < fVar5) {
        fVar5 = fVar5 * _UNK_027edb4c;
        fVar11 = (float)powf(0x41200000,fVar5);
        fVar2 = (float)powf(0x41200000,fVar5);
      }
    }
    else {
      fVar2 = 0.0;
    }
    *param_1 = fVar12 + fVar8 + fVar11;
    param_1[1] = fVar13 + fVar4 + fVar2;
    fVar11 = _UNK_02972434;
    fVar12 = param_2[6];
    fVar13 = param_2[7];
    fVar2 = _UNK_02972434;
    if (fVar10 <= ABS(param_2[10])) {
      fVar2 = (float)log10f();
      fVar2 = fVar2 * 20.0 + -3.0;
    }
    if (fVar10 <= ABS(param_2[0xb])) {
      fVar11 = (float)log10f();
      fVar11 = fVar11 * 20.0 + -3.0;
    }
    fVar4 = 0.0;
    fVar8 = 0.0;
    if (fVar3 < fVar2) {
      fVar8 = (float)powf(0x41200000,fVar2 * _UNK_027edb4c);
    }
    if (fVar3 < fVar11) {
      fVar4 = (float)powf(0x41200000,fVar11 * _UNK_027edb4c);
    }
    fVar11 = 0.0;
    if (fVar10 <= ABS(param_2[8])) {
      fVar10 = (float)log10f();
      fVar2 = fVar10 * 20.0 + -3.0;
      fVar10 = 0.0;
      if (fVar3 < fVar2) {
        fVar2 = fVar2 * _UNK_027edb4c;
        fVar11 = (float)powf(0x41200000,fVar2);
        fVar10 = (float)powf(0x41200000,fVar2);
      }
    }
    else {
      fVar10 = 0.0;
    }
    fVar11 = fVar12 + fVar8 + fVar11;
    fVar10 = fVar13 + fVar4 + fVar10;
  }
  else {
    fVar2 = _UNK_02965bf8;
    if (_UNK_027fac84 <= ABS(param_2[4])) {
      fVar2 = (float)log10f();
      fVar2 = fVar2 * 20.0;
    }
    fVar3 = fVar11;
    if (fVar10 <= ABS(param_2[5])) {
      fVar3 = (float)log10f();
      fVar3 = fVar3 * 20.0;
    }
    fVar8 = _UNK_02972438;
    fVar5 = 0.0;
    fVar4 = 0.0;
    if (fVar11 < fVar2 + _UNK_02972438) {
      fVar4 = (float)powf(0x41200000,(fVar2 + _UNK_02972438) * _UNK_027edb4c);
    }
    fVar1 = _UNK_0297243c;
    fVar11 = _UNK_02965bf8;
    if (_UNK_02965bf8 < fVar3 + _UNK_0297243c) {
      fVar5 = (float)powf(0x41200000,(fVar3 + _UNK_0297243c) * _UNK_027edb4c);
    }
    fVar7 = 0.0;
    fVar6 = 0.0;
    if (fVar11 < fVar3 + fVar8) {
      fVar6 = (float)powf(0x41200000,(fVar3 + fVar8) * _UNK_027edb4c);
    }
    if (fVar11 < fVar2 + fVar1) {
      fVar7 = (float)powf(0x41200000,(fVar2 + fVar1) * _UNK_027edb4c);
    }
    fVar2 = 0.0;
    if (fVar10 <= ABS(param_2[2])) {
      fVar3 = (float)log10f();
      fVar9 = fVar3 * 20.0 + -3.0;
      fVar3 = 0.0;
      if (fVar11 < fVar9) {
        fVar9 = fVar9 * _UNK_027edb4c;
        fVar2 = (float)powf(0x41200000,fVar9);
        fVar3 = (float)powf(0x41200000,fVar9);
      }
    }
    else {
      fVar3 = 0.0;
    }
    *param_1 = fVar12 + fVar4 + fVar5 + fVar2;
    param_1[1] = fVar13 + fVar6 + fVar7 + fVar3;
    fVar12 = param_2[6];
    fVar13 = param_2[7];
    fVar2 = fVar11;
    if (fVar10 <= ABS(param_2[10])) {
      fVar2 = (float)log10f();
      fVar2 = fVar2 * 20.0;
    }
    fVar3 = fVar11;
    if (fVar10 <= ABS(param_2[0xb])) {
      fVar3 = (float)log10f();
      fVar3 = fVar3 * 20.0;
    }
    fVar5 = 0.0;
    fVar4 = 0.0;
    if (fVar11 < fVar2 + fVar8) {
      fVar4 = (float)powf(0x41200000,(fVar2 + fVar8) * _UNK_027edb4c);
    }
    fVar6 = _UNK_02965bf8;
    if (_UNK_02965bf8 < fVar3 + fVar1) {
      fVar5 = (float)powf(0x41200000,(fVar3 + fVar1) * _UNK_027edb4c);
    }
    fVar9 = 0.0;
    fVar7 = 0.0;
    if (fVar6 < fVar3 + fVar8) {
      fVar7 = (float)powf(0x41200000,(fVar3 + fVar8) * _UNK_027edb4c);
    }
    if (fVar6 < fVar2 + fVar1) {
      fVar9 = (float)powf(0x41200000,(fVar2 + fVar1) * _UNK_027edb4c);
    }
    fVar11 = 0.0;
    if (fVar10 <= ABS(param_2[8])) {
      fVar10 = (float)log10f();
      fVar2 = fVar10 * 20.0 + -3.0;
      fVar10 = 0.0;
      if (fVar6 < fVar2) {
        fVar2 = fVar2 * _UNK_027edb4c;
        fVar11 = (float)powf(0x41200000,fVar2);
        fVar10 = (float)powf(0x41200000,fVar2);
      }
    }
    else {
      fVar10 = 0.0;
    }
    fVar11 = fVar12 + fVar4 + fVar5 + fVar11;
    fVar10 = fVar13 + fVar7 + fVar9 + fVar10;
  }
  param_1[2] = fVar11;
  param_1[3] = fVar10;
  return;
}

// ==== Aska::SoundUtility::PhysicalStereoUpMix_AllSamples(float*, float const*, int)
// vaddr 0x1f7b220 | ghidra 0x207b220 | size 180 | symbol _ZN4Aska12SoundUtility30PhysicalStereoUpMix_AllSamplesEPfPKfi | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12SoundUtility30PhysicalStereoUpMix_AllSamplesEPfPKfi
               (long param_1,long param_2,uint param_3)

{
  float *pfVar1;
  ulong uVar2;
  undefined4 *puVar3;
  float *pfVar4;
  undefined4 *puVar5;
  float *pfVar6;
  long lVar7;
  float fVar8;
  
  lVar7 = *(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50;
  memset(param_1,0,(long)(int)param_3 * 0x18);
  if (*(int *)(lVar7 + 0x115c) - 1U < 2) {
    if (0 < (int)param_3) {
      uVar2 = (ulong)param_3;
      puVar3 = (undefined4 *)(param_1 + 4);
      puVar5 = (undefined4 *)(param_2 + 4);
      do {
        uVar2 = uVar2 - 1;
        puVar3[-1] = puVar5[-1];
        *puVar3 = *puVar5;
        puVar3 = puVar3 + 6;
        puVar5 = puVar5 + 2;
      } while (uVar2 != 0);
    }
  }
  else if ((*(int *)(lVar7 + 0x115c) == 0) && (0 < (int)param_3)) {
    uVar2 = (ulong)param_3;
    pfVar6 = (float *)(param_2 + 4);
    pfVar4 = (float *)(param_1 + 8);
    do {
      pfVar1 = pfVar6 + -1;
      fVar8 = *pfVar6;
      uVar2 = uVar2 - 1;
      pfVar6 = pfVar6 + 2;
      *pfVar4 = *pfVar1 + fVar8;
      pfVar4 = pfVar4 + 6;
    } while (uVar2 != 0);
  }
  return;
}

// ==== Aska::SoundUtility::DownMixArray_51To2(float*, float const*, bool)
// vaddr 0x1f7b2d4 | ghidra 0x207b2d4 | size 536 | symbol _ZN4Aska12SoundUtility18DownMixArray_51To2EPfPKfb | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska12SoundUtility18DownMixArray_51To2EPfPKfb(float *param_1,float *param_2,uint param_3)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  
  fVar4 = _UNK_02965bf8;
  fVar8 = _UNK_027fac84;
  fVar10 = *param_2;
  fVar11 = param_2[1];
  fVar3 = _UNK_02965bf8;
  if (_UNK_027fac84 <= ABS(param_2[4])) {
    fVar3 = (float)log10f();
    fVar3 = fVar3 * 20.0;
  }
  if (fVar8 <= ABS(param_2[5])) {
    fVar4 = (float)log10f();
    fVar4 = fVar4 * 20.0;
  }
  fVar1 = _UNK_02972438;
  fVar9 = _UNK_02965bf8;
  if ((param_3 & 1) == 0) {
    fVar6 = 0.0;
    if (_UNK_02965bf8 < fVar3 + -3.0) {
      fVar6 = (float)powf(0x41200000,(fVar3 + -3.0) * _UNK_027edb4c);
    }
    fVar6 = fVar10 + fVar6;
    fVar3 = fVar4 + -3.0;
  }
  else {
    fVar6 = 0.0;
    fVar5 = 0.0;
    if (_UNK_02965bf8 < fVar3 + _UNK_02972438) {
      fVar5 = (float)powf(0x41200000,(fVar3 + _UNK_02972438) * _UNK_027edb4c);
    }
    fVar2 = _UNK_0297243c;
    if (fVar9 < fVar4 + _UNK_0297243c) {
      fVar6 = (float)powf(0x41200000,(fVar4 + _UNK_0297243c) * _UNK_027edb4c);
    }
    fVar7 = 0.0;
    if (fVar9 < fVar4 + fVar1) {
      fVar7 = (float)powf(0x41200000,(fVar4 + fVar1) * _UNK_027edb4c);
    }
    fVar6 = fVar10 + fVar5 + fVar6;
    fVar3 = fVar3 + fVar2;
    fVar11 = fVar11 + fVar7;
  }
  fVar4 = _UNK_02965bf8;
  fVar9 = 0.0;
  fVar10 = 0.0;
  if (_UNK_02965bf8 < fVar3) {
    fVar10 = (float)powf(0x41200000,fVar3 * _UNK_027edb4c);
  }
  if (fVar8 <= ABS(param_2[2])) {
    fVar8 = (float)log10f(param_2[2]);
    fVar3 = fVar8 * 20.0 + -3.0;
    fVar8 = 0.0;
    if (fVar4 < fVar3) {
      fVar3 = fVar3 * _UNK_027edb4c;
      fVar9 = (float)powf(0x41200000,fVar3);
      fVar8 = (float)powf(0x41200000,fVar3);
    }
  }
  else {
    fVar8 = 0.0;
  }
  *param_1 = fVar6 + fVar9;
  param_1[1] = fVar11 + fVar10 + fVar8;
  return;
}

// ==== Aska::SoundManager::AddAudioInterface(Aska::AudioInterface*)
// vaddr 0x224206c | ghidra 0x234206c | size 372 | symbol _ZN4Aska12SoundManager17AddAudioInterfaceEPNS_14AudioInterfaceE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12SoundManager17AddAudioInterfaceEPNS_14AudioInterfaceE(long param_1,long param_2)

{
  int *piVar1;
  int *piVar2;
  char cVar3;
  bool bVar4;
  ulong uVar5;
  int iVar6;
  long lVar7;
  
  piVar1 = (int *)(param_1 + 0xed0);
  iVar6 = 0;
  do {
    while (*piVar1 != -1) {
      ClearExclusiveLocal();
      bVar4 = 0x1fe < iVar6;
      iVar6 = iVar6 + 1;
      if (bVar4) {
        piVar2 = (int *)(param_1 + 0xed4);
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
              uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0xf10);
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
                Aska::Semaphore::Wait() const(param_1 + 0xf10);
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
                if (cVar3 == '\0') goto code_r0x023421c8;
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
code_r0x023421c8:
        do {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
          if (bVar4) {
            *piVar2 = *piVar2 + -1;
            cVar3 = ExclusiveMonitorsStatus();
          }
        } while (cVar3 != '\0');
        DataMemoryBarrier(2,3);
code_r0x023420e4:
        lVar7 = *(long *)(param_1 + 0xbd8);
        *(long *)(param_2 + 8) = lVar7;
        *(long *)(param_2 + 0x10) = param_1 + 0xbd0;
        *(long *)(param_1 + 0xbd8) = param_2;
        *(long *)(lVar7 + 0x10) = param_2;
        *(int *)(param_1 + 0xbf8) = *(int *)(param_1 + 0xbf8) + 1;
        DataMemoryBarrier(2,3);
        *(undefined4 *)(param_1 + 0xed0) = 0xffffffff;
        DataMemoryBarrier(2,3);
        piVar1 = (int *)(param_1 + 0xed4);
        if (0x14 < *piVar1) {
          do {
            cVar3 = '\x01';
            bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
            if (bVar4) {
              *piVar1 = *piVar1 + -1;
              cVar3 = ExclusiveMonitorsStatus();
            }
          } while (cVar3 != '\0');
          uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0xf10);
          if ((uVar5 & 1) != 0) {
            (*(code *)PTR__ZNK4Aska9Semaphore6SignalEv_02c96cd0)(param_1 + 0xf10);
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
  goto code_r0x023420e4;
}

// ==== Aska::SoundManager::DeleteAudioInterface(Aska::AudioInterface*)
// vaddr 0x22421e0 | ghidra 0x23421e0 | size 408 | symbol _ZN4Aska12SoundManager20DeleteAudioInterfaceEPNS_14AudioInterfaceE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12SoundManager20DeleteAudioInterfaceEPNS_14AudioInterfaceE(long param_1,long param_2)

{
  int *piVar1;
  int *piVar2;
  char cVar3;
  bool bVar4;
  ulong uVar5;
  int iVar6;
  long lVar7;
  long lVar8;
  
  piVar1 = (int *)(param_1 + 0xed0);
  iVar6 = 0;
  do {
    while (*piVar1 == -1) {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = 0;
        cVar3 = ExclusiveMonitorsStatus();
      }
      if (cVar3 == '\0') goto code_r0x023422c4;
    }
    ClearExclusiveLocal();
    bVar4 = iVar6 < 0x1ff;
    iVar6 = iVar6 + 1;
  } while (bVar4);
  piVar2 = (int *)(param_1 + 0xed4);
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
        uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0xf10);
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
          Aska::Semaphore::Wait() const(param_1 + 0xf10);
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
          if (cVar3 == '\0') goto code_r0x023422b4;
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
code_r0x023422b4:
  do {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar4) {
      *piVar2 = *piVar2 + -1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
code_r0x023422c4:
  DataMemoryBarrier(2,3);
  if ((param_1 + 0xbd0 != param_2) && (param_2 != 0)) {
    lVar7 = *(long *)(param_2 + 8);
    lVar8 = *(long *)(param_2 + 0x10);
    if (lVar7 != 0) {
      *(long *)(lVar7 + 0x10) = lVar8;
    }
    if (lVar8 != 0) {
      *(long *)(lVar8 + 8) = lVar7;
    }
    if (0 < *(int *)(param_1 + 0xbf8)) {
      *(int *)(param_1 + 0xbf8) = *(int *)(param_1 + 0xbf8) + -1;
    }
    *(long *)(param_2 + 8) = 0;
    *(undefined8 *)(param_2 + 0x10) = 0;
  }
  Aska::SoundServer::ReleaseAudioInterface(Aska::AudioInterface*)(*(undefined8 *)(param_1 + 0xe8),param_2);
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_1 + 0xed0) = 0xffffffff;
  DataMemoryBarrier(2,3);
  if (0x14 < *(int *)(param_1 + 0xed4)) {
    piVar1 = (int *)(param_1 + 0xed4);
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
    uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0xf10);
    if ((uVar5 & 1) != 0) {
      (*(code *)PTR__ZNK4Aska9Semaphore6SignalEv_02c96cd0)(param_1 + 0xf10);
      return;
    }
  }
  return;
}

// ==== Aska::SoundUtility::DownMix_4To2(float*, float const*)
// vaddr 0x2243f90 | ghidra 0x2343f90 | size 12 | symbol _ZN4Aska12SoundUtility12DownMix_4To2EPfPKf | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12SoundUtility12DownMix_4To2EPfPKf(undefined8 param_1,undefined8 param_2)

{
  (*(code *)PTR__ZN4Aska12SoundUtility11DownMix_To2EPfPKfib_02c99658)(param_1,param_2,4,0);
  return;
}

// ==== Aska::SoundUtility::DownMix_51To2(float*, float const*)
// vaddr 0x2243f9c | ghidra 0x2343f9c | size 12 | symbol _ZN4Aska12SoundUtility13DownMix_51To2EPfPKf | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12SoundUtility13DownMix_51To2EPfPKf(undefined8 param_1,undefined8 param_2)

{
  (*(code *)PTR__ZN4Aska12SoundUtility11DownMix_To2EPfPKfib_02c99658)(param_1,param_2,6,0);
  return;
}

// ==== Aska::SoundUtility::DownMix_51To4(float*, float const*)
// vaddr 0x2243fa8 | ghidra 0x2343fa8 | size 8 | symbol _ZN4Aska12SoundUtility13DownMix_51To4EPfPKf | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12SoundUtility13DownMix_51To4EPfPKf(undefined8 param_1,undefined8 param_2)

{
  (*(code *)PTR__ZN4Aska12SoundUtility11DownMix_To4EPfPKfi_02c9f2f0)(param_1,param_2,6);
  return;
}

// ==== Aska::SoundCommand::ProcessCommand(Aska::SoundCommand**)
// vaddr 0x2246970 | ghidra 0x2346970 | size 1544 | symbol _ZN4Aska12SoundCommand14ProcessCommandEPPS0_ | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Type propagation algorithm not settling */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 _ZN4Aska12SoundCommand14ProcessCommandEPPS0_(long param_1,undefined8 *param_2)

{
  undefined4 uVar1;
  int iVar2;
  bool bVar3;
  undefined *puVar4;
  undefined4 uVar5;
  uint uVar6;
  long lVar7;
  ulong uVar8;
  long lVar9;
  long *plVar10;
  byte bVar11;
  undefined8 uVar12;
  long lVar13;
  uint uVar14;
  float fVar15;
  
  *param_2 = 0;
  puVar4 = PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50;
  switch(*(undefined4 *)(param_1 + 0x18)) {
  case 1:
    lVar9 = Aska::SoundServer::AcquireSoundPass()(*(undefined8 *)
                             (*(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50 + 0xe8));
    if (lVar9 != 0) {
      uVar8 = *(ulong *)(param_1 + 0x28);
      uVar1 = *(undefined4 *)(param_1 + 0x34);
      uVar14 = *(uint *)(param_1 + 0x38);
      iVar2 = *(int *)(param_1 + 0x30);
      if ((uVar14 >> 2 & 1) == 0) {
        *(undefined4 *)(lVar9 + 0x18) = 1;
        if (iVar2 == 0) {
          plVar10 = (long *)Aska::FileReadManager::GetReadableDevice(int)(*(undefined8 *)
                                             PTR__ZN4Aska6Global18m_pFileReadManagerE_02cbf970,
                                            uVar8 & 0xffffffff);
          uVar5 = (**(code **)(*plVar10 + 0x48))();
          *(ulong *)(lVar9 + 0x20) = uVar8;
          bVar11 = *(byte *)(lVar9 + 0xe0) & 0xfe;
        }
        else {
          uVar5 = Aska::FileReadManager::GetDirectReadAlign() const();
          *(ulong *)(lVar9 + 0x20) = uVar8;
          bVar11 = *(byte *)(lVar9 + 0xe0) | 1;
        }
        *(byte *)(lVar9 + 0xe0) = bVar11;
        *(undefined4 *)(lVar9 + 0x28) = uVar5;
      }
      else {
        *(undefined8 *)(lVar9 + 0x20) = 0;
        *(undefined4 *)(lVar9 + 0x18) = 2;
        *(byte *)(lVar9 + 0xe0) = *(byte *)(lVar9 + 0xe0) & 0xfe;
        *(ulong *)(lVar9 + 0x30) = uVar8;
      }
      *(undefined4 *)(lVar9 + 0x2c) = uVar1;
      uVar12 = *(undefined8 *)(param_1 + 0x20);
      *(uint *)(lVar9 + 0x70) = uVar14;
      *(undefined8 *)(lVar9 + 0x58) = uVar12;
      *(undefined8 *)(lVar9 + 0xa8) = *(undefined8 *)(param_1 + 0x6c);
      uVar12 = *(undefined8 *)(param_1 + 0x5c);
      *(undefined8 *)(lVar9 + 0xa0) = *(undefined8 *)(param_1 + 100);
      *(undefined8 *)(lVar9 + 0x98) = uVar12;
      uVar12 = *(undefined8 *)(param_1 + 0x4c);
      *(undefined8 *)(lVar9 + 0x90) = *(undefined8 *)(param_1 + 0x54);
      *(undefined8 *)(lVar9 + 0x88) = uVar12;
      uVar12 = *(undefined8 *)(param_1 + 0x3c);
      *(undefined8 *)(lVar9 + 0x80) = *(undefined8 *)(param_1 + 0x44);
      *(undefined8 *)(lVar9 + 0x78) = uVar12;
      if ((uVar14 >> 1 & 1) != 0) {
        lVar7 = *(long *)(param_1 + 0x20);
        *(ulong *)(lVar7 + 0x1f8) = uVar8;
        *(bool *)(lVar7 + 0x210) = iVar2 != 0;
        *(undefined4 *)(lVar7 + 0x200) = uVar1;
        fVar15 = _UNK_02965bf8;
        if (_UNK_027fac84 <= ABS(*(float *)(param_1 + 0x4c))) {
          fVar15 = (float)log10f();
          fVar15 = fVar15 * 20.0;
        }
        *(float *)(lVar7 + 0x204) = fVar15;
        *(undefined4 *)(lVar7 + 0x208) = *(undefined4 *)(param_1 + 0x50);
        *(undefined4 *)(lVar7 + 0x214) = *(undefined4 *)(param_1 + 0x60);
        *(undefined4 *)(lVar7 + 0x20c) = *(undefined4 *)(param_1 + 0x48);
        *(undefined4 *)(lVar7 + 0x218) = *(undefined4 *)(param_1 + 100);
        *(undefined4 *)(lVar7 + 0x21c) = *(undefined4 *)(param_1 + 0x68);
        *(undefined4 *)(lVar7 + 0x220) = *(undefined4 *)(param_1 + 0x5c);
        *(undefined1 *)(lVar7 + 0x211) = *(undefined1 *)(param_1 + 0x5b);
      }
      lVar7 = *(long *)puVar4;
      lVar13 = *(long *)(lVar7 + 0xae0);
      *(long *)(lVar9 + 8) = lVar13;
      *(long *)(lVar9 + 0x10) = lVar7 + 0xad8;
      *(long *)(lVar7 + 0xae0) = lVar9;
      *(long *)(lVar13 + 0x10) = lVar9;
      *(int *)(lVar7 + 0xbc0) = *(int *)(lVar7 + 0xbc0) + 1;
      return 1;
    }
    break;
  case 2:
    uVar8 = Aska::SoundObject::Stop(unsigned int)(*(undefined8 *)(param_1 + 0x20),*(undefined4 *)(param_1 + 0x28));
    goto joined_r0x02346c3c;
  case 3:
    uVar14 = *(uint *)(param_1 + 0x28);
    if ((uVar14 & 1) == 0) {
      bVar3 = false;
    }
    else {
      lVar7 = *(long *)(*(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50 + 0x108);
      lVar9 = *(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50 + 0xf8;
      if (lVar9 == lVar7) {
        bVar3 = false;
      }
      else {
        bVar3 = false;
        do {
          uVar8 = Aska::SoundObject::Stop(unsigned int)(lVar7,0);
          lVar7 = *(long *)(lVar7 + 0x10);
          if ((uVar8 & 1) == 0) {
            bVar3 = true;
          }
        } while (lVar9 != lVar7);
      }
    }
    if ((uVar14 >> 1 & 1) != 0) {
      lVar7 = *(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50;
      lVar9 = *(long *)(lVar7 + 0x130);
      while (lVar7 + 0x120 != lVar9) {
        uVar8 = Aska::SoundObject::Stop(unsigned int)(lVar9,0);
        lVar9 = *(long *)(lVar9 + 0x10);
        if ((uVar8 & 1) == 0) {
          bVar3 = true;
        }
      }
    }
    if (!bVar3) {
      return 1;
    }
    break;
  case 4:
    uVar8 = Aska::SoundObject::Pause()(*(undefined8 *)(param_1 + 0x20));
    goto joined_r0x02346c3c;
  case 5:
    uVar8 = Aska::SoundObject::Resume()(*(undefined8 *)(param_1 + 0x20));
    goto joined_r0x02346c3c;
  case 6:
    uVar6 = *(uint *)(param_1 + 0x28);
    if ((uVar6 & 1) == 0) {
code_r0x02346c64:
      uVar14 = 0;
    }
    else {
      lVar7 = *(long *)(*(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50 + 0x108);
      lVar9 = *(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50 + 0xf8;
      if (lVar9 == lVar7) goto code_r0x02346c64;
      uVar14 = 0;
      do {
        uVar8 = Aska::SoundObject::Pause()(lVar7);
        lVar7 = *(long *)(lVar7 + 0x10);
        if ((uVar8 & 1) == 0) {
          uVar14 = 1;
        }
      } while (lVar9 != lVar7);
    }
    if ((uVar6 >> 1 & 1) != 0) {
      lVar7 = *(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50;
      for (lVar9 = *(long *)(lVar7 + 0x130); lVar7 + 0x120 != lVar9; lVar9 = *(long *)(lVar9 + 0x10)
          ) {
        uVar6 = Aska::SoundObject::Pause()(lVar9);
        uVar14 = uVar14 | uVar6 ^ 1;
      }
    }
    goto joined_r0x02346d50;
  case 7:
    lVar9 = *(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50;
    lVar7 = *(long *)(lVar9 + 0x108);
    if (lVar9 + 0xf8 == lVar7) {
      uVar14 = 0;
    }
    else {
      uVar14 = 0;
      do {
        uVar6 = Aska::SoundObject::Resume()(lVar7);
        lVar7 = *(long *)(lVar7 + 0x10);
        uVar14 = uVar14 | uVar6 ^ 1;
      } while (lVar9 + 0xf8 != lVar7);
      lVar9 = *(long *)puVar4;
    }
    for (lVar7 = *(long *)(lVar9 + 0x130); lVar9 + 0x120 != lVar7; lVar7 = *(long *)(lVar7 + 0x10))
    {
      uVar6 = Aska::SoundObject::Resume()(lVar7);
      uVar14 = uVar14 | uVar6 ^ 1;
    }
joined_r0x02346d50:
    if ((uVar14 & 1) != 0) {
      return 1;
    }
    break;
  case 8:
    uVar8 = Aska::SoundCommand::ProcessPushBGM(Aska::SoundCommand**, unsigned int)(param_1,param_2,*(undefined4 *)(param_1 + 0x28));
    goto joined_r0x02346c3c;
  case 9:
    uVar8 = Aska::SoundCommand::ProcessPopBGM(Aska::SoundCommand**, unsigned int)(param_1,param_2,*(undefined4 *)(param_1 + 0x28));
joined_r0x02346c3c:
    if ((uVar8 & 1) != 0) {
      return 1;
    }
    break;
  case 10:
    Aska::PushPopBGMList::Clear()(*(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50 + 0x140);
    return 1;
  case 0xb:
    uVar14 = *(uint *)(param_1 + 0x28);
    iVar2 = *(int *)(param_1 + 0x2c);
    uVar1 = *(undefined4 *)(param_1 + 0x30);
    lVar9 = 0;
    if (*(int *)(param_1 + 0x34) != 0) {
      lVar9 = param_1 + 0x38;
    }
    lVar7 = Aska::SoundManager::AcquireAuxiliaryDevice(unsigned int)(*(undefined8 *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50,uVar14);
    if (lVar7 != 0) {
      if (iVar2 == -1) {
        return 1;
      }
      if (uVar14 < 5) {
        lVar7 = Aska::AudioMixer::GetBusChannel(unsigned int)(*(undefined8 *)(*(long *)puVar4 + 0x6c8),uVar14);
        if (lVar7 != 0) {
          lVar7 = lVar7 + 0x18;
          goto code_r0x02346d90;
        }
      }
      else {
        lVar7 = Aska::SoundManager::QueryAuxiliaryDevice(unsigned int) const(*(long *)puVar4,uVar14);
        if (lVar7 != 0) {
          lVar7 = lVar7 + 0x50;
          goto code_r0x02346d90;
        }
      }
    }
    break;
  case 0xc:
    uVar1 = *(undefined4 *)(param_1 + 0x28);
    lVar9 = Aska::SoundManager::QueryAuxiliaryDevice(unsigned int) const(*(undefined8 *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50,uVar1);
    if (lVar9 != 0) {
      Aska::SoundManager::ReleaseAuxiliaryDevice(unsigned int)(*(undefined8 *)puVar4,uVar1);
      return 1;
    }
    break;
  case 0xd:
    iVar2 = *(int *)(param_1 + 0x2c);
    uVar1 = *(undefined4 *)(param_1 + 0x30);
    lVar9 = 0;
    if (*(int *)(param_1 + 0x34) != 0) {
      lVar9 = param_1 + 0x38;
    }
    if (*(uint *)(param_1 + 0x28) < 5) {
      lVar7 = Aska::AudioMixer::GetBusChannel(unsigned int)(*(undefined8 *)
                               (*(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50 + 0x6c8));
      if (lVar7 != 0) {
        lVar7 = lVar7 + 0x18;
code_r0x02346d90:
        uVar8 = Aska::AudioEffector::InstallDspEffect(unsigned int, Aska::ESound::EDspEffect, void const*)(lVar7,iVar2,uVar1,lVar9);
        goto joined_r0x02346c3c;
      }
    }
    else {
      lVar7 = Aska::SoundManager::QueryAuxiliaryDevice(unsigned int) const();
      if (lVar7 != 0) {
        lVar7 = lVar7 + 0x50;
        goto code_r0x02346d90;
      }
    }
    break;
  case 0xe:
    uVar1 = *(undefined4 *)(param_1 + 0x2c);
    if (*(uint *)(param_1 + 0x28) < 5) {
      lVar9 = Aska::AudioMixer::GetBusChannel(unsigned int)(*(undefined8 *)
                               (*(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50 + 0x6c8));
      if (lVar9 != 0) {
        lVar9 = lVar9 + 0x18;
code_r0x02346d14:
        Aska::AudioEffector::UninstallDspEffect(unsigned int)(lVar9,uVar1);
        return 1;
      }
    }
    else {
      lVar9 = Aska::SoundManager::QueryAuxiliaryDevice(unsigned int) const();
      if (lVar9 != 0) {
        lVar9 = lVar9 + 0x50;
        goto code_r0x02346d14;
      }
    }
    break;
  case 0xf:
    uVar1 = *(undefined4 *)(param_1 + 0x2c);
    uVar5 = *(undefined4 *)(param_1 + 0x30);
    lVar9 = Aska::SoundManager::QueryAuxiliaryDevice(unsigned int) const(*(undefined8 *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50,
                            *(undefined4 *)(param_1 + 0x28));
    if (lVar9 != 0) {
      uVar8 = Aska::AuxiliaryDevice::ConnectDevice(unsigned int, unsigned int)(lVar9,uVar1,uVar5);
      goto joined_r0x02346c3c;
    }
    break;
  case 0x10:
    lVar9 = Aska::SoundManager::QueryAuxiliaryDevice(unsigned int) const(*(undefined8 *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50,
                            *(undefined4 *)(param_1 + 0x28));
    if (lVar9 != 0) {
      Aska::AuxiliaryDevice::DisconnectDevice()();
      return 1;
    }
    break;
  default:
    goto code_r0x02346e54;
  }
  puVar4 = PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50;
  if (*(int *)(param_1 + 0x18) == 9) {
    Aska::SoundManager::DeleteSoundObject(Aska::SoundObject*, bool)(*(undefined8 *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50,
                    *(undefined8 *)(param_1 + 0x20),0);
    *(undefined8 *)(param_1 + 0x20) = 0;
  }
  else if (*(int *)(param_1 + 0x18) == 1) {
    lVar9 = *(long *)(param_1 + 0x28);
    iVar2 = *(int *)(param_1 + 0x30);
    Aska::SoundManager::DeleteSoundObject(Aska::SoundObject*, bool)(*(undefined8 *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50,
                    *(undefined8 *)(param_1 + 0x20),*(undefined1 *)(param_1 + 0x5b));
    *(undefined8 *)(param_1 + 0x20) = 0;
    if ((lVar9 != 0) && (iVar2 != 0)) {
      Aska::SoundServer::ReleaseFilePathBuffer(char*)(*(undefined8 *)(*(long *)puVar4 + 0xe8),lVar9);
    }
  }
code_r0x02346e54:
  return 1;
}

// ==== Aska::SoundCommand::ProcessPauseAll(unsigned int)
// vaddr 0x2246f78 | ghidra 0x2346f78 | size 176 | symbol _ZN4Aska12SoundCommand15ProcessPauseAllEj | lib libSOA-3.7.0.so | 2026-10-08
uint _ZN4Aska12SoundCommand15ProcessPauseAllEj(undefined8 param_1,uint param_2)

{
  uint uVar1;
  ulong uVar2;
  long lVar3;
  long lVar4;
  uint uVar5;
  
  if ((param_2 & 1) != 0) {
    lVar4 = *(long *)(*(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50 + 0x108);
    lVar3 = *(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50 + 0xf8;
    if (lVar3 != lVar4) {
      uVar5 = 0;
      do {
        uVar2 = Aska::SoundObject::Pause()(lVar4);
        lVar4 = *(long *)(lVar4 + 0x10);
        if ((uVar2 & 1) == 0) {
          uVar5 = 1;
        }
      } while (lVar3 != lVar4);
      goto joined_r0x02346fd8;
    }
  }
  uVar5 = 0;
joined_r0x02346fd8:
  if ((param_2 >> 1 & 1) != 0) {
    lVar4 = *(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50;
    for (lVar3 = *(long *)(lVar4 + 0x130); lVar4 + 0x120 != lVar3; lVar3 = *(long *)(lVar3 + 0x10))
    {
      uVar1 = Aska::SoundObject::Pause()(lVar3);
      uVar5 = uVar5 | uVar1 ^ 1;
    }
  }
  return uVar5 & 1;
}

// ==== Aska::SoundCommand::ProcessResumeAll()
// vaddr 0x2247028 | ghidra 0x2347028 | size 148 | symbol _ZN4Aska12SoundCommand16ProcessResumeAllEv | lib libSOA-3.7.0.so | 2026-10-08
uint _ZN4Aska12SoundCommand16ProcessResumeAllEv(void)

{
  undefined *puVar1;
  uint uVar2;
  long lVar3;
  long lVar4;
  uint uVar5;
  
  puVar1 = PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50;
  lVar3 = *(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50;
  lVar4 = *(long *)(lVar3 + 0x108);
  if (lVar3 + 0xf8 == lVar4) {
    uVar5 = 0;
  }
  else {
    uVar5 = 0;
    do {
      uVar2 = Aska::SoundObject::Resume()(lVar4);
      lVar4 = *(long *)(lVar4 + 0x10);
      uVar5 = uVar5 | uVar2 ^ 1;
    } while (lVar3 + 0xf8 != lVar4);
    lVar3 = *(long *)puVar1;
  }
  for (lVar4 = *(long *)(lVar3 + 0x130); lVar3 + 0x120 != lVar4; lVar4 = *(long *)(lVar4 + 0x10)) {
    uVar2 = Aska::SoundObject::Resume()(lVar4);
    uVar5 = uVar5 | uVar2 ^ 1;
  }
  return uVar5 & 1;
}

// ==== Aska::SoundCommand::ProcessPushBGM(Aska::SoundCommand**, unsigned int)
// vaddr 0x22470bc | ghidra 0x23470bc | size 564 | symbol _ZN4Aska12SoundCommand14ProcessPushBGMEPPS0_j | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8
_ZN4Aska12SoundCommand14ProcessPushBGMEPPS0_j(long param_1,long *param_2,undefined4 param_3)

{
  byte bVar1;
  int iVar2;
  long *plVar3;
  long lVar4;
  undefined8 uVar5;
  long lVar6;
  long lVar7;
  float fVar8;
  float fVar9;
  undefined4 uVar10;
  
  *param_2 = 0;
  lVar6 = *(long *)(param_1 + 0x20);
  if (*(int *)(lVar6 + 0x1e4) - 1U < 4) {
    lVar7 = *(long *)(lVar6 + 0x128);
    if (lVar7 != 0) {
      lVar4 = *(long *)(lVar7 + 0x120);
      if (lVar4 != 0) {
        *(undefined8 *)(lVar6 + 0x1f8) = *(undefined8 *)(*(long *)(lVar4 + 8) + 0x20);
        bVar1 = *(byte *)(*(long *)(lVar4 + 8) + 0x2c);
        *(byte *)(lVar6 + 0x210) = bVar1 & 1;
        *(undefined4 *)(lVar6 + 0x200) = *(undefined4 *)(lVar4 + 0x10);
        if ((bVar1 & 1) != 0) {
          *(undefined8 *)(*(long *)(lVar4 + 8) + 0x20) = 0;
        }
      }
      uVar10 = 0;
      plVar3 = *(long **)(*(long *)(param_1 + 0x20) + 0x128);
      fVar9 = 0.0;
      if ((plVar3 != (long *)0x0) &&
         (fVar8 = (float)(**(code **)(*plVar3 + 0x88))(plVar3,0), fVar9 = _UNK_02965bf8,
         _UNK_027fac84 <= ABS(fVar8))) {
        fVar9 = (float)log10f();
        fVar9 = fVar9 * 20.0;
      }
      *(float *)(lVar6 + 0x204) = fVar9;
      plVar3 = *(long **)(*(long *)(param_1 + 0x20) + 0x128);
      if (plVar3 != (long *)0x0) {
        uVar10 = (**(code **)(*plVar3 + 0x88))(plVar3,1);
      }
      *(undefined4 *)(lVar6 + 0x208) = uVar10;
      lVar4 = *(long *)(*(long *)(param_1 + 0x20) + 0x128);
      uVar10 = 0;
      if (lVar4 != 0) {
        lVar4 = *(long *)(lVar4 + 0x118);
        uVar10 = 0;
        if (lVar4 != 0) {
          uVar10 = *(undefined4 *)(*(long *)(*(long *)(lVar4 + 0x30) + 8) + 0x58);
        }
      }
      *(undefined4 *)(lVar6 + 0x214) = uVar10;
      *(byte *)(lVar6 + 0x211) = (byte)*(undefined4 *)(*(long *)(param_1 + 0x20) + 0x1ec) & 1;
      uVar10 = 0;
      if (*(long **)(lVar7 + 0x118) != (long *)0x0) {
        uVar10 = (**(code **)(**(long **)(lVar7 + 0x118) + 0x40))();
      }
      *(undefined4 *)(lVar6 + 0x20c) = uVar10;
      if (((((*(byte *)(*(long *)(param_1 + 0x20) + 0x1e8) >> 3 & 1) == 0) ||
           (lVar7 = *(long *)(*(long *)(param_1 + 0x20) + 0x128), lVar7 == 0)) ||
          (lVar7 = *(long *)(lVar7 + 0x118), lVar7 == 0)) ||
         (lVar7 = *(long *)(*(long *)(lVar7 + 0x30) + 8), lVar7 == 0)) {
        uVar10 = 0;
        *(undefined4 *)(lVar6 + 0x218) = 0;
      }
      else {
        *(int *)(lVar6 + 0x218) = (int)*(undefined8 *)(lVar7 + 0x2a8);
        uVar10 = *(undefined4 *)
                  (*(long *)(*(long *)(*(long *)(*(long *)(*(long *)(param_1 + 0x20) + 0x128) +
                                                0x118) + 0x30) + 8) + 0x778);
      }
      *(undefined4 *)(lVar6 + 0x21c) = uVar10;
    }
    lVar7 = *(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50;
    iVar2 = *(int *)(lVar7 + 0x2c0);
    if (iVar2 < 8) {
      lVar4 = lVar7 + (long)iVar2 * 0x30;
      *(int *)(lVar7 + 0x2c0) = iVar2 + 1;
      *(undefined8 *)(lVar4 + 0x140) = 0;
      uVar5 = *(undefined8 *)(lVar6 + 0x218);
      *(undefined8 *)(lVar4 + 0x168) = *(undefined8 *)(lVar6 + 0x220);
      *(undefined8 *)(lVar4 + 0x160) = uVar5;
      uVar5 = *(undefined8 *)(lVar6 + 0x208);
      *(undefined8 *)(lVar4 + 0x158) = *(undefined8 *)(lVar6 + 0x210);
      *(undefined8 *)(lVar4 + 0x150) = uVar5;
      uVar5 = *(undefined8 *)(lVar6 + 0x1f8);
      *(undefined8 *)(lVar4 + 0x148) = *(undefined8 *)(lVar6 + 0x200);
      *(undefined8 *)(lVar4 + 0x140) = uVar5;
      lVar6 = Aska::SoundServer::AcquireSoundCommand()(*(undefined8 *)(lVar7 + 0xe8));
      if (lVar6 != 0) {
        *(undefined4 *)(lVar6 + 0x18) = 2;
        uVar5 = *(undefined8 *)(param_1 + 0x20);
        *(undefined4 *)(lVar6 + 0x28) = param_3;
        *(undefined8 *)(lVar6 + 0x20) = uVar5;
        *param_2 = lVar6;
        return 1;
      }
      if (*(int *)(lVar7 + 0x2c0) < 1) {
        return 0;
      }
      *(int *)(lVar7 + 0x2c0) = *(int *)(lVar7 + 0x2c0) + -1;
      return 0;
    }
  }
  return 0;
}

// ==== Aska::SoundCommand::ProcessPopBGM(Aska::SoundCommand**, unsigned int)
// vaddr 0x22472f0 | ghidra 0x23472f0 | size 368 | symbol _ZN4Aska12SoundCommand13ProcessPopBGMEPPS0_j | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8
_ZN4Aska12SoundCommand13ProcessPopBGMEPPS0_j(long param_1,long *param_2,undefined4 param_3)

{
  float *pfVar1;
  byte bVar2;
  int iVar3;
  undefined *puVar4;
  long lVar5;
  undefined8 uVar6;
  long lVar7;
  long lVar8;
  undefined4 uVar9;
  undefined8 uStack_78;
  undefined4 uStack_70;
  undefined4 uStack_6c;
  undefined4 uStack_64;
  undefined7 uStack_60;
  undefined1 uStack_59;
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined8 uStack_48;
  
  *param_2 = 0;
  puVar4 = PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50;
  lVar5 = Aska::SoundServer::AcquireSoundCommand()(*(undefined8 *)
                           (*(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50 + 0xe8));
  uVar6 = 0;
  if (lVar5 != 0) {
    lVar8 = *(long *)puVar4;
    iVar3 = *(int *)(lVar8 + 0x2c0) + -1;
    if (*(int *)(lVar8 + 0x2c0) < 1) {
      Aska::SoundServer::ReleaseSoundCommand(Aska::SoundCommand*)(*(undefined8 *)(lVar8 + 0xe8),lVar5);
      uVar6 = 0;
    }
    else {
      *(int *)(lVar8 + 0x2c0) = iVar3;
      Aska::SoundManager::SetDefaultDirectPlaybackSettings(Aska::DirectPlaybackSettings*)(&uStack_78);
      lVar7 = lVar8 + (long)iVar3 * 0x30;
      uStack_54 = *(undefined4 *)(lVar7 + 0x15c);
      uStack_6c = *(undefined4 *)(lVar7 + 0x154);
      uStack_64 = *(undefined4 *)(lVar7 + 0x150);
      uStack_59 = *(undefined1 *)(lVar7 + 0x159);
      uStack_58 = *(undefined4 *)(lVar7 + 0x168);
      uStack_50 = *(undefined4 *)(lVar7 + 0x160);
      uStack_4c = *(undefined4 *)(lVar7 + 0x164);
      pfVar1 = (float *)(lVar7 + 0x14c);
      if (*(char *)(*(long *)(param_1 + 0x20) + 0x22c) != '\0') {
        pfVar1 = (float *)(*(long *)(param_1 + 0x20) + 0x228);
      }
      uVar9 = 0;
      uStack_70 = param_3;
      if (_UNK_02965bf8 < *pfVar1) {
        uVar9 = powf(0x41200000,*pfVar1 * _UNK_027edb4c);
      }
      uVar6 = 1;
      *(undefined4 *)(lVar5 + 0x18) = 1;
      lVar8 = lVar8 + (long)iVar3 * 0x30;
      *(undefined8 *)(lVar5 + 0x20) = *(undefined8 *)(param_1 + 0x20);
      bVar2 = *(byte *)(lVar8 + 0x158);
      *(undefined8 *)(lVar5 + 0x28) = *(undefined8 *)(lVar8 + 0x140);
      *(uint *)(lVar5 + 0x30) = (uint)bVar2;
      *(undefined4 *)(lVar5 + 0x34) = *(undefined4 *)(lVar8 + 0x148);
      *(undefined4 *)(lVar5 + 0x38) = 2;
      *(undefined8 *)(lVar5 + 0x6c) = uStack_48;
      *(ulong *)(lVar5 + 100) = CONCAT44(uStack_4c,uStack_50);
      *(ulong *)(lVar5 + 0x5c) = CONCAT44(uStack_54,uStack_58);
      *(ulong *)(lVar5 + 0x54) = CONCAT17(uStack_59,uStack_60);
      *(ulong *)(lVar5 + 0x4c) = CONCAT44(uStack_64,uVar9);
      *(ulong *)(lVar5 + 0x44) = CONCAT44(uStack_6c,uStack_70);
      *(undefined8 *)(lVar5 + 0x3c) = uStack_78;
      *param_2 = lVar5;
    }
  }
  return uVar6;
}

// ==== Aska::SoundCommand::ProcessCreateAuxEffector(unsigned int, unsigned int, Aska::ESound::EDspEffect, void const*)
// vaddr 0x2247460 | ghidra 0x2347460 | size 156 | symbol _ZN4Aska12SoundCommand24ProcessCreateAuxEffectorEjjNS_6ESound10EDspEffectEPKv | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska12SoundCommand24ProcessCreateAuxEffectorEjjNS_6ESound10EDspEffectEPKv
          (undefined8 param_1,uint param_2,int param_3,undefined4 param_4,undefined8 param_5)

{
  undefined *puVar1;
  long lVar2;
  ulong uVar3;
  undefined8 uVar4;
  
  puVar1 = PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50;
  lVar2 = Aska::SoundManager::AcquireAuxiliaryDevice(unsigned int)(*(undefined8 *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50);
  if (lVar2 == 0) {
    return 0;
  }
  if (param_3 == -1) {
code_r0x023474e0:
    uVar4 = 1;
  }
  else {
    if (param_2 < 5) {
      lVar2 = Aska::AudioMixer::GetBusChannel(unsigned int)(*(undefined8 *)(*(long *)puVar1 + 0x6c8),param_2);
      if (lVar2 != 0) {
        lVar2 = lVar2 + 0x18;
code_r0x023474cc:
        uVar3 = Aska::AudioEffector::InstallDspEffect(unsigned int, Aska::ESound::EDspEffect, void const*)(lVar2,param_3,param_4,param_5);
        if ((uVar3 & 1) != 0) goto code_r0x023474e0;
      }
    }
    else {
      lVar2 = Aska::SoundManager::QueryAuxiliaryDevice(unsigned int) const(*(long *)puVar1,param_2);
      if (lVar2 != 0) {
        lVar2 = lVar2 + 0x50;
        goto code_r0x023474cc;
      }
    }
    uVar4 = 0;
  }
  return uVar4;
}

// ==== Aska::SoundCommand::ProcessDeleteAuxEffector(unsigned int)
// vaddr 0x22474fc | ghidra 0x23474fc | size 60 | symbol _ZN4Aska12SoundCommand24ProcessDeleteAuxEffectorEj | lib libSOA-3.7.0.so | 2026-10-08
bool _ZN4Aska12SoundCommand24ProcessDeleteAuxEffectorEj(undefined8 param_1,undefined4 param_2)

{
  undefined *puVar1;
  long lVar2;
  
  puVar1 = PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50;
  lVar2 = Aska::SoundManager::QueryAuxiliaryDevice(unsigned int) const(*(undefined8 *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50);
  if (lVar2 != 0) {
    Aska::SoundManager::ReleaseAuxiliaryDevice(unsigned int)(*(undefined8 *)puVar1,param_2);
  }
  return lVar2 != 0;
}

// ==== Aska::SoundCommand::ProcessInstallDspEffect(unsigned int, unsigned int, Aska::ESound::EDspEffect, void const*)
// vaddr 0x2247538 | ghidra 0x2347538 | size 116 | symbol _ZN4Aska12SoundCommand23ProcessInstallDspEffectEjjNS_6ESound10EDspEffectEPKv | lib libSOA-3.7.0.so | 2026-10-08
bool _ZN4Aska12SoundCommand23ProcessInstallDspEffectEjjNS_6ESound10EDspEffectEPKv
               (undefined8 param_1,uint param_2,undefined4 param_3,undefined4 param_4,
               undefined8 param_5)

{
  long lVar1;
  ulong uVar2;
  
  if (param_2 < 5) {
    lVar1 = Aska::AudioMixer::GetBusChannel(unsigned int)(*(undefined8 *)
                             (*(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50 + 0x6c8));
    if (lVar1 == 0) {
      return false;
    }
    lVar1 = lVar1 + 0x18;
  }
  else {
    lVar1 = Aska::SoundManager::QueryAuxiliaryDevice(unsigned int) const();
    if (lVar1 == 0) {
      return false;
    }
    lVar1 = lVar1 + 0x50;
  }
  uVar2 = Aska::AudioEffector::InstallDspEffect(unsigned int, Aska::ESound::EDspEffect, void const*)(lVar1,param_3,param_4,param_5);
  return (uVar2 & 1) != 0;
}

// ==== Aska::SoundCommand::ProcessUninstallDspEffect(unsigned int, unsigned int)
// vaddr 0x22475ac | ghidra 0x23475ac | size 80 | symbol _ZN4Aska12SoundCommand25ProcessUninstallDspEffectEjj | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska12SoundCommand25ProcessUninstallDspEffectEjj
          (undefined8 param_1,uint param_2,undefined4 param_3)

{
  long lVar1;
  
  if (param_2 < 5) {
    lVar1 = Aska::AudioMixer::GetBusChannel(unsigned int)(*(undefined8 *)
                             (*(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50 + 0x6c8));
    if (lVar1 == 0) {
      return 0;
    }
    lVar1 = lVar1 + 0x18;
  }
  else {
    lVar1 = Aska::SoundManager::QueryAuxiliaryDevice(unsigned int) const();
    if (lVar1 == 0) {
      return 0;
    }
    lVar1 = lVar1 + 0x50;
  }
  Aska::AudioEffector::UninstallDspEffect(unsigned int)(lVar1,param_3);
  return 1;
}

// ==== Aska::SoundCommand::ProcessConnectAuxEffector(unsigned int, unsigned int, unsigned int)
// vaddr 0x22475fc | ghidra 0x23475fc | size 68 | symbol _ZN4Aska12SoundCommand25ProcessConnectAuxEffectorEjjj | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12SoundCommand25ProcessConnectAuxEffectorEjjj
               (undefined8 param_1,undefined8 param_2,undefined4 param_3,undefined4 param_4)

{
  long lVar1;
  
  lVar1 = Aska::SoundManager::QueryAuxiliaryDevice(unsigned int) const(*(undefined8 *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50);
  if (lVar1 != 0) {
    (*(code *)PTR__ZN4Aska15AuxiliaryDevice13ConnectDeviceEjj_02ca2b10)(lVar1,param_3,param_4);
    return;
  }
  return;
}

// ==== Aska::SoundCommand::ProcessDisconnectAuxEffector(unsigned int)
// vaddr 0x2247640 | ghidra 0x2347640 | size 40 | symbol _ZN4Aska12SoundCommand28ProcessDisconnectAuxEffectorEj | lib libSOA-3.7.0.so | 2026-10-08
bool _ZN4Aska12SoundCommand28ProcessDisconnectAuxEffectorEj(void)

{
  long lVar1;
  
  lVar1 = Aska::SoundManager::QueryAuxiliaryDevice(unsigned int) const(*(undefined8 *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50);
  if (lVar1 != 0) {
    Aska::AuxiliaryDevice::DisconnectDevice()();
  }
  return lVar1 != 0;
}

// ==== Aska::SoundCommand::ErrorHandler()
// vaddr 0x2247668 | ghidra 0x2347668 | size 148 | symbol _ZN4Aska12SoundCommand12ErrorHandlerEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12SoundCommand12ErrorHandlerEv(long param_1)

{
  long lVar1;
  int iVar2;
  undefined *puVar3;
  
  puVar3 = PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50;
  if (*(int *)(param_1 + 0x18) == 9) {
    Aska::SoundManager::DeleteSoundObject(Aska::SoundObject*, bool)(*(undefined8 *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50,
                    *(undefined8 *)(param_1 + 0x20),0);
    *(undefined8 *)(param_1 + 0x20) = 0;
  }
  else if (*(int *)(param_1 + 0x18) == 1) {
    lVar1 = *(long *)(param_1 + 0x28);
    iVar2 = *(int *)(param_1 + 0x30);
    Aska::SoundManager::DeleteSoundObject(Aska::SoundObject*, bool)(*(undefined8 *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50,
                    *(undefined8 *)(param_1 + 0x20),*(undefined1 *)(param_1 + 0x5b));
    *(undefined8 *)(param_1 + 0x20) = 0;
    if ((lVar1 != 0) && (iVar2 != 0)) {
      (*(code *)PTR__ZN4Aska11SoundServer21ReleaseFilePathBufferEPc_02ca6680)
                (*(undefined8 *)(*(long *)puVar3 + 0xe8),lVar1);
      return;
    }
  }
  return;
}

// ==== Aska::SoundCommand::ArrangeCommand(Aska::TList<Aska::SoundCommand>*)
// vaddr 0x22476fc | ghidra 0x23476fc | size 84 | symbol _ZN4Aska12SoundCommand14ArrangeCommandEPNS_5TListIS0_EE | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska12SoundCommand14ArrangeCommandEPNS_5TListIS0_EE(long param_1)

{
  ulong uVar1;
  
  if (((*(long *)(param_1 + 0x20) != 0) && (*(uint *)(param_1 + 0x18) < 9)) &&
     ((1 << (ulong)(*(uint *)(param_1 + 0x18) & 0x1f) & 0x134U) != 0)) {
    uVar1 = Aska::SoundManager::IsAvailable(Aska::SoundObject*) const(*(undefined8 *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50);
    if ((uVar1 & 1) == 0) {
      return 1;
    }
  }
  return 0;
}


// FAILED to create function at 02971a30 typeinfo name for Aska::Sequencer2::WaitingNoteNotify
// FAILED to create function at 02971ec0 typeinfo name for Aska::TSoundDynamicQueue<Aska::SoundObject::RequestContainer>
// FAILED to create function at 02971f10 typeinfo name for Aska::TDynamicQueue<Aska::SoundObject::RequestContainer, true>
// FAILED to create function at 02971f80 typeinfo name for Aska::SoundPass::LoadEndNotify
// FAILED to create function at 02972390 typeinfo name for Aska::TPoolLegacy<Aska::SoundServer::AskaAdpcmDecodeBuffer, false>
// FAILED to create function at 029723e0 typeinfo name for Aska::TPoolLegacy<Aska::SoundServer::FilePathBuffer, false>
// FAILED to create function at 02bb3028 Aska::Sequencer2::vtable
// FAILED to create function at 02bb3048 Aska::Sequencer2::typeinfo
// FAILED to create function at 02bb3058 Aska::Sequencer2::WaitingNoteNotify::vtable
// FAILED to create function at 02bb3080 Aska::Sequencer2::WaitingNoteNotify::typeinfo
// FAILED to create function at 02bb3128 Aska::SoundManagerThread::vtable
// FAILED to create function at 02bb3150 Aska::SoundManager::vtable
// FAILED to create function at 02bb3200 Aska::SoundManagerThread::typeinfo
// FAILED to create function at 02bb3220 Aska::SoundManager::typeinfo
// FAILED to create function at 02bb3508 Aska::SoundHandle::vtable
// FAILED to create function at 02bb3530 Aska::SoundHandle::typeinfo
// FAILED to create function at 02bb3598 Aska::SoundCommand::vtable
// FAILED to create function at 02bb35c0 Aska::SoundCommand::typeinfo
// FAILED to create function at 02bb36f8 Aska::SEControlObject::vtable
// FAILED to create function at 02bb37d8 Aska::SoundObject::vtable
// FAILED to create function at 02bb3850 Aska::SoundObject::typeinfo
// FAILED to create function at 02bb3870 Aska::SEControlObject::typeinfo
// FAILED to create function at 02bb38a8 Aska::TSoundDynamicQueue<Aska::SoundObject::RequestContainer>::vtable
// FAILED to create function at 02bb38c8 Aska::TDynamicQueue<Aska::SoundObject::RequestContainer,true>::typeinfo
// FAILED to create function at 02bb38e0 Aska::TSoundDynamicQueue<Aska::SoundObject::RequestContainer>::typeinfo
// FAILED to create function at 02bb38f8 Aska::TDynamicQueue<Aska::SoundObject::RequestContainer,true>::vtable
// FAILED to create function at 02bb3918 Aska::SoundPass::vtable
// FAILED to create function at 02bb3940 Aska::SoundPass::typeinfo
// FAILED to create function at 02bb3958 Aska::SoundPass::LoadEndNotify::vtable
// FAILED to create function at 02bb39a0 Aska::SoundPass::LoadEndNotify::typeinfo
// FAILED to create function at 02bb3d38 Aska::SoundServer::vtable
// FAILED to create function at 02bb3d58 Aska::SoundServer::typeinfo
// FAILED to create function at 02bb3f68 Aska::TPoolLegacy<Aska::SoundServer::AskaAdpcmDecodeBuffer,false>::vtable
// FAILED to create function at 02bb3f90 Aska::TPoolLegacy<Aska::SoundServer::AskaAdpcmDecodeBuffer,false>::typeinfo
// FAILED to create function at 02bb3fa8 Aska::TPoolLegacy<Aska::SoundServer::FilePathBuffer,false>::vtable
// FAILED to create function at 02bb3fd0 Aska::TPoolLegacy<Aska::SoundServer::FilePathBuffer,false>::typeinfo
// FAILED to create function at 02dcd8d8 Aska::SoundManager::m_pInstance
// FAILED to create function at 02dcd8e0 Aska::SoundMemory::m_pMemHeap
// FAILED to create function at 02dcd8e8 Aska::SoundMemory::m_pMemResource
