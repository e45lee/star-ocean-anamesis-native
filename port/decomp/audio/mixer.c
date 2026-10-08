// port/decomp/audio/mixer.c: Ghidra decompiles for the audio subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-08 13:02 UTC: tools/decomp.sh '--into' 'audio/mixer' 'Aska::Audio[A-Za-z0-9]*::'

// ==== Aska::Audio3DEngine::Audio3DEngine()
// vaddr 0x1f67e0c | ghidra 0x2067e0c | size 88 | symbol _ZN4Aska13Audio3DEngineC1Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska13Audio3DEngineC2Ev(long *param_1)

{
  long *plVar1;
  
  *param_1 = (long)(PTR__ZTVN4Aska13Audio3DEngineE_02cbe8a8 + 0x10);
  Aska::AudioListener::AudioListener()(param_1 + 2);
  plVar1 = param_1 + 0x28;
  param_1[0x26] = (long)(PTR__ZTVN4Aska5TListINS_12AudioEmitterEEE_02cbfb10 + 0x10);
  Aska::AudioEmitter::AudioEmitter()(plVar1);
  *(undefined4 *)(param_1 + 0x4e) = 0;
  param_1[0x29] = (long)plVar1;
  param_1[0x2a] = (long)plVar1;
  param_1[100] = 0;
  return;
}

// ==== Aska::Audio3DEngine::~Audio3DEngine()
// vaddr 0x1f67e64 | ghidra 0x2067e64 | size 60 | symbol _ZN4Aska13Audio3DEngineD1Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska13Audio3DEngineD2Ev(long *param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZTVN4Aska5TListINS_12AudioEmitterEEE_02cbfb10 + 0x10;
  *param_1 = (long)(PTR__ZTVN4Aska13Audio3DEngineE_02cbe8a8 + 0x10);
  param_1[0x26] = (long)puVar1;
  Aska::AudioEmitter::~AudioEmitter()(param_1 + 0x28);
  (*(code *)PTR__ZN4Aska13AudioListenerD2Ev_02ca3220)(param_1 + 2);
  return;
}

// ==== Aska::Audio3DEngine::~Audio3DEngine()
// vaddr 0x1f67eb4 | ghidra 0x2067eb4 | size 68 | symbol _ZN4Aska13Audio3DEngineD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska13Audio3DEngineD0Ev(long *param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZTVN4Aska5TListINS_12AudioEmitterEEE_02cbfb10 + 0x10;
  *param_1 = (long)(PTR__ZTVN4Aska13Audio3DEngineE_02cbe8a8 + 0x10);
  param_1[0x26] = (long)puVar1;
  Aska::AudioEmitter::~AudioEmitter()(param_1 + 0x28);
  Aska::AudioListener::~AudioListener()(param_1 + 2);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::Audio3DEngine::Initialize()
// vaddr 0x1f67ef8 | ghidra 0x2067ef8 | size 356 | symbol _ZN4Aska13Audio3DEngine10InitializeEv | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 _ZN4Aska13Audio3DEngine10InitializeEv(long param_1)

{
  undefined *puVar1;
  long *plVar2;
  long *plVar3;
  undefined8 uVar4;
  
  *(undefined8 *)(param_1 + 0x280) = 0x4120000000000000;
  *(undefined4 *)(param_1 + 0x288) = 0x447a0000;
  *(undefined8 *)(param_1 + 0x310) = 0x4348000041200000;
  *(undefined4 *)(param_1 + 0x318) = 0x3f800000;
  plVar2 = (long *)Aska::SoundMemory::Malloc(unsigned long)(0xb8);
  *(long **)(param_1 + 800) = plVar2;
  plVar3 = (long *)0x0;
  if (plVar2 != (long *)0x0) {
    *(undefined4 *)(plVar2 + 9) = 0x3f800000;
    *(undefined8 *)((long)plVar2 + 0x4c) = 0;
    puVar1 = PTR__ZTVN4Aska19TFastQuadraticCurveILi8EEE_02cba7e8;
    plVar2[8] = 0;
    plVar2[7] = 0;
    plVar2[6] = 0;
    plVar2[5] = 0;
    plVar2[4] = 0;
    plVar2[3] = 0;
    plVar2[2] = 0;
    plVar2[1] = 0;
    *plVar2 = (long)(puVar1 + 0x10);
    *(undefined1 *)((long)plVar2 + 0xb4) = 1;
    plVar3 = *(long **)(param_1 + 800);
  }
  uVar4 = 0;
  if (plVar3 != (long *)0x0) {
    if ((int)plVar3[10] < 8) {
      *(undefined4 *)((long)plVar3 + (long)(int)plVar3[10] * 4 + 8) = 0;
      *(undefined4 *)((long)plVar3 + (long)(int)plVar3[10] * 4 + 0x28) = 0x3f800000;
      *(int *)(plVar3 + 10) = (int)plVar3[10] + 1;
      plVar3 = *(long **)(param_1 + 800);
    }
    if ((int)plVar3[10] < 8) {
      *(undefined4 *)((long)plVar3 + (long)(int)plVar3[10] * 4 + 8) = 0x3f000000;
      *(undefined4 *)((long)plVar3 + (long)(int)plVar3[10] * 4 + 0x28) = 0x3f000000;
      *(int *)(plVar3 + 10) = (int)plVar3[10] + 1;
      plVar3 = *(long **)(param_1 + 800);
    }
    if ((int)plVar3[10] < 8) {
      *(undefined4 *)((long)plVar3 + (long)(int)plVar3[10] * 4 + 8) = 0x3f800000;
      *(undefined4 *)((long)plVar3 + (long)(int)plVar3[10] * 4 + 0x28) = 0;
      *(int *)(plVar3 + 10) = (int)plVar3[10] + 1;
      plVar3 = *(long **)(param_1 + 800);
    }
    (**(code **)(*plVar3 + 0x90))();
    uVar4 = _UNK_029718b0;
    *(undefined8 *)(param_1 + 0x294) = _UNK_029718b8;
    *(undefined8 *)(param_1 + 0x28c) = uVar4;
    *(undefined8 *)(param_1 + 0x29c) = 0x408ba0583ff5be0c;
    Aska::Audio3DEngine::UpdateSpeakersPosition()(param_1);
    uVar4 = 1;
  }
  return uVar4;
}

// ==== Aska::Audio3DEngine::ResetSpeakerPositionRadian()
// vaddr 0x1f6805c | ghidra 0x206805c | size 44 | symbol _ZN4Aska13Audio3DEngine26ResetSpeakerPositionRadianEv | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska13Audio3DEngine26ResetSpeakerPositionRadianEv(long param_1)

{
  undefined8 uVar1;
  
  uVar1 = _UNK_029718b0;
  *(undefined8 *)(param_1 + 0x294) = _UNK_029718b8;
  *(undefined8 *)(param_1 + 0x28c) = uVar1;
  *(undefined8 *)(param_1 + 0x29c) = 0x408ba0583ff5be0c;
  (*(code *)PTR__ZN4Aska13Audio3DEngine22UpdateSpeakersPositionEv_02ca44d8)();
  return;
}

// ==== Aska::Audio3DEngine::Finalize()
// vaddr 0x1f68088 | ghidra 0x2068088 | size 40 | symbol _ZN4Aska13Audio3DEngine8FinalizeEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska13Audio3DEngine8FinalizeEv(long param_1)

{
  if (*(long **)(param_1 + 800) != (long *)0x0) {
    (**(code **)(**(long **)(param_1 + 800) + 8))();
    *(undefined8 *)(param_1 + 800) = 0;
  }
  return;
}

// ==== Aska::Audio3DEngine::SetAudioListener(Aska::HierarchicalObject*, float)
// vaddr 0x1f680b0 | ghidra 0x20680b0 | size 400 | symbol _ZN4Aska13Audio3DEngine16SetAudioListenerEPNS_18HierarchicalObjectEf | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska13Audio3DEngine16SetAudioListenerEPNS_18HierarchicalObjectEf
               (undefined4 param_1,long param_2,long param_3)

{
  int *piVar1;
  int *piVar2;
  char cVar3;
  bool bVar4;
  ulong uVar5;
  int iVar6;
  
  if (param_3 == 0) {
    return;
  }
  Aska::Audio3DEngine::DeleteAudioListener()(param_2);
  piVar1 = (int *)(param_2 + 0x68);
  iVar6 = 0;
  do {
    while (*piVar1 != -1) {
      ClearExclusiveLocal();
      bVar4 = 0x1fe < iVar6;
      iVar6 = iVar6 + 1;
      if (bVar4) {
        piVar2 = (int *)(param_2 + 0x6c);
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
              uVar5 = Aska::Semaphore::IsReady() const(param_2 + 0xa8);
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
                Aska::Semaphore::Wait() const(param_2 + 0xa8);
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
                if (cVar3 == '\0') goto code_r0x02068228;
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
code_r0x02068228:
        do {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
          if (bVar4) {
            *piVar2 = *piVar2 + -1;
            cVar3 = ExclusiveMonitorsStatus();
          }
        } while (cVar3 != '\0');
        DataMemoryBarrier(2,3);
        goto code_r0x02068144;
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
code_r0x02068144:
  *(long *)(param_2 + 0x28) = param_3;
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_2 + 0x68) = 0xffffffff;
  DataMemoryBarrier(2,3);
  piVar1 = (int *)(param_2 + 0x6c);
  if (0x14 < *piVar1) {
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
    uVar5 = Aska::Semaphore::IsReady() const(param_2 + 0xa8);
    if ((uVar5 & 1) != 0) {
      Aska::Semaphore::Signal() const(param_2 + 0xa8);
    }
  }
  Aska::Audio3DObject::UpdateMatrix()(param_2 + 0x10);
  *(undefined4 *)(param_2 + 0x100) = param_1;
  Aska::Audio3DObject::UpdateMatrix()(param_2 + 0x10);
  *(undefined **)(param_3 + 0x28) =
       PTR__ZN4Aska13Audio3DEngine19Func3DObjectDeletedEPKNS_18HierarchicalObjectE_02cbaac0;
  return;
}

// ==== Aska::Audio3DEngine::DeleteAudioListener()
// vaddr 0x1f68240 | ghidra 0x2068240 | size 348 | symbol _ZN4Aska13Audio3DEngine19DeleteAudioListenerEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska13Audio3DEngine19DeleteAudioListenerEv(long param_1)

{
  int *piVar1;
  int *piVar2;
  char cVar3;
  bool bVar4;
  ulong uVar5;
  int iVar6;
  
  if (*(long *)(param_1 + 0x28) != 0) {
    *(undefined8 *)(*(long *)(param_1 + 0x28) + 0x28) = 0;
  }
  piVar1 = (int *)(param_1 + 0x68);
  iVar6 = 0;
  do {
    while (*piVar1 != -1) {
      ClearExclusiveLocal();
      bVar4 = 0x1fe < iVar6;
      iVar6 = iVar6 + 1;
      if (bVar4) {
        piVar2 = (int *)(param_1 + 0x6c);
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
              uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0xa8);
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
                Aska::Semaphore::Wait() const(param_1 + 0xa8);
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
                if (cVar3 == '\0') goto code_r0x02068384;
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
code_r0x02068384:
        do {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
          if (bVar4) {
            *piVar2 = *piVar2 + -1;
            cVar3 = ExclusiveMonitorsStatus();
          }
        } while (cVar3 != '\0');
        DataMemoryBarrier(2,3);
code_r0x020682c4:
        *(undefined8 *)(param_1 + 0x28) = 0;
        DataMemoryBarrier(2,3);
        *(undefined4 *)(param_1 + 0x68) = 0xffffffff;
        DataMemoryBarrier(2,3);
        piVar1 = (int *)(param_1 + 0x6c);
        if (0x14 < *piVar1) {
          do {
            cVar3 = '\x01';
            bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
            if (bVar4) {
              *piVar1 = *piVar1 + -1;
              cVar3 = ExclusiveMonitorsStatus();
            }
          } while (cVar3 != '\0');
          uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0xa8);
          if ((uVar5 & 1) != 0) {
            Aska::Semaphore::Signal() const(param_1 + 0xa8);
          }
        }
        (*(code *)PTR__ZN4Aska13Audio3DObject12UpdateMatrixEv_02cb19f8)(param_1 + 0x10);
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
  goto code_r0x020682c4;
}

// ==== Aska::Audio3DObject::UpdateMatrix()
// vaddr 0x1f6839c | ghidra 0x206839c | size 424 | symbol _ZN4Aska13Audio3DObject12UpdateMatrixEv | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska13Audio3DObject12UpdateMatrixEv(long param_1)

{
  int *piVar1;
  char cVar2;
  bool bVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  undefined8 *puVar8;
  ulong uVar9;
  int iVar10;
  int *piVar11;
  undefined8 uVar12;
  undefined8 uVar13;
  undefined8 uVar14;
  
  piVar11 = (int *)(param_1 + 0x58);
  iVar10 = 0;
  do {
    while (*piVar11 == -1) {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar11,0x10);
      if (bVar3) {
        *piVar11 = 0;
        cVar2 = ExclusiveMonitorsStatus();
      }
      if (cVar2 == '\0') goto code_r0x0206847c;
    }
    ClearExclusiveLocal();
    bVar3 = iVar10 < 0x1ff;
    iVar10 = iVar10 + 1;
  } while (bVar3);
  piVar1 = (int *)(param_1 + 0x5c);
  do {
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar3) {
      *piVar1 = *piVar1 + 1;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
  do {
    if (*piVar11 != -1) {
      ClearExclusiveLocal();
      do {
        uVar9 = Aska::Semaphore::IsReady() const(param_1 + 0x98);
        if ((uVar9 & 1) == 0) {
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
          Aska::Semaphore::Wait() const(param_1 + 0x98);
        }
        do {
          cVar2 = '\x01';
          bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar3) {
            *piVar1 = *piVar1 + 1;
            cVar2 = ExclusiveMonitorsStatus();
          }
        } while (cVar2 != '\0');
        while (*piVar11 == -1) {
          cVar2 = '\x01';
          bVar3 = (bool)ExclusiveMonitorPass(piVar11,0x10);
          if (bVar3) {
            *piVar11 = 0;
            cVar2 = ExclusiveMonitorsStatus();
          }
          if (cVar2 == '\0') goto code_r0x0206846c;
        }
        ClearExclusiveLocal();
      } while( true );
    }
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar11,0x10);
    if (bVar3) {
      *piVar11 = 0;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
code_r0x0206846c:
  do {
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar3) {
      *piVar1 = *piVar1 + -1;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
code_r0x0206847c:
  uVar14 = _UNK_027dbb38;
  uVar13 = _UNK_027dbb30;
  uVar7 = _UNK_027dbb28;
  uVar6 = _UNK_027dbb20;
  uVar5 = _UNK_027dbb18;
  uVar4 = _UNK_027dbb10;
  uVar12 = _UNK_027dbb00;
  DataMemoryBarrier(2,3);
  if (*(long **)(param_1 + 0x18) == (long *)0x0) {
    *(undefined8 *)(param_1 + 0xb8) = _UNK_027dbb08;
    *(undefined8 *)(param_1 + 0xb0) = uVar12;
    *(undefined8 *)(param_1 + 200) = uVar5;
    *(undefined8 *)(param_1 + 0xc0) = uVar4;
    *(undefined8 *)(param_1 + 0xd8) = uVar7;
    *(undefined8 *)(param_1 + 0xd0) = uVar6;
  }
  else {
    puVar8 = (undefined8 *)(**(code **)(**(long **)(param_1 + 0x18) + 0x98))();
    uVar12 = *puVar8;
    *(undefined8 *)(param_1 + 0xb8) = puVar8[1];
    *(undefined8 *)(param_1 + 0xb0) = uVar12;
    uVar12 = puVar8[2];
    *(undefined8 *)(param_1 + 200) = puVar8[3];
    *(undefined8 *)(param_1 + 0xc0) = uVar12;
    uVar12 = puVar8[4];
    *(undefined8 *)(param_1 + 0xd8) = puVar8[5];
    *(undefined8 *)(param_1 + 0xd0) = uVar12;
    uVar14 = puVar8[7];
    uVar13 = puVar8[6];
  }
  *(undefined8 *)(param_1 + 0xe8) = uVar14;
  *(undefined8 *)(param_1 + 0xe0) = uVar13;
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_1 + 0x58) = 0xffffffff;
  DataMemoryBarrier(2,3);
  piVar11 = (int *)(param_1 + 0x5c);
  if (0x14 < *piVar11) {
    do {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar11,0x10);
      if (bVar3) {
        *piVar11 = *piVar11 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    uVar9 = Aska::Semaphore::IsReady() const(param_1 + 0x98);
    if ((uVar9 & 1) != 0) {
      (*(code *)PTR__ZNK4Aska9Semaphore6SignalEv_02c96cd0)(param_1 + 0x98);
      return;
    }
  }
  return;
}

// ==== Aska::Audio3DEngine::Func3DObjectDeleted(Aska::HierarchicalObject const*)
// vaddr 0x1f68544 | ghidra 0x2068544 | size 32 | symbol _ZN4Aska13Audio3DEngine19Func3DObjectDeletedEPKNS_18HierarchicalObjectE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska13Audio3DEngine19Func3DObjectDeletedEPKNS_18HierarchicalObjectE(undefined8 param_1)

{
  (*(code *)
    PTR__ZN4Aska13Audio3DEngine24LocalFunc3DObjectDeletedEPKNS_18HierarchicalObjectE_02cb51f8)
            (*(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50 + 0x390,param_1);
  return;
}

// ==== Aska::Audio3DEngine::AddAudioEmitter(Aska::AudioEmitter*)
// vaddr 0x1f68564 | ghidra 0x2068564 | size 56 | symbol _ZN4Aska13Audio3DEngine15AddAudioEmitterEPNS_12AudioEmitterE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska13Audio3DEngine15AddAudioEmitterEPNS_12AudioEmitterE(long param_1,long param_2)

{
  long lVar1;
  
  if (*(long *)(param_2 + 0x18) != 0) {
    *(undefined **)(*(long *)(param_2 + 0x18) + 0x28) =
         PTR__ZN4Aska13Audio3DEngine19Func3DObjectDeletedEPKNS_18HierarchicalObjectE_02cbaac0;
  }
  lVar1 = *(long *)(param_1 + 0x148);
  *(long *)(param_2 + 8) = lVar1;
  *(long *)(param_2 + 0x10) = param_1 + 0x140;
  *(long *)(param_1 + 0x148) = param_2;
  *(long *)(lVar1 + 0x10) = param_2;
  *(int *)(param_1 + 0x270) = *(int *)(param_1 + 0x270) + 1;
  return;
}

// ==== Aska::Audio3DEngine::DeleteAudioEmitter(Aska::AudioEmitter*)
// vaddr 0x1f685c0 | ghidra 0x20685c0 | size 144 | symbol _ZN4Aska13Audio3DEngine18DeleteAudioEmitterEPNS_12AudioEmitterE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska13Audio3DEngine18DeleteAudioEmitterEPNS_12AudioEmitterE(long param_1,long param_2)

{
  long *plVar1;
  int iVar2;
  long lVar3;
  long lVar4;
  
  lVar3 = param_1 + 0x140;
  if (lVar3 == *(long *)(param_1 + 0x150)) {
    iVar2 = 0;
  }
  else {
    iVar2 = 0;
    lVar4 = *(long *)(param_1 + 0x150);
    do {
      plVar1 = (long *)(lVar4 + 0x10);
      if (*(long *)(lVar4 + 0x18) == *(long *)(param_2 + 0x18)) {
        iVar2 = iVar2 + 1;
      }
      lVar4 = *plVar1;
    } while (lVar3 != *plVar1);
  }
  if ((lVar3 != param_2) && (param_2 != 0)) {
    lVar3 = *(long *)(param_2 + 8);
    lVar4 = *(long *)(param_2 + 0x10);
    if (lVar3 != 0) {
      *(long *)(lVar3 + 0x10) = lVar4;
    }
    if (lVar4 != 0) {
      *(long *)(lVar4 + 8) = lVar3;
    }
    if (0 < *(int *)(param_1 + 0x270)) {
      *(int *)(param_1 + 0x270) = *(int *)(param_1 + 0x270) + -1;
    }
    *(long *)(param_2 + 8) = 0;
    *(undefined8 *)(param_2 + 0x10) = 0;
  }
  if ((iVar2 == 1) && (*(long *)(param_2 + 0x18) != 0)) {
    *(undefined8 *)(*(long *)(param_2 + 0x18) + 0x28) = 0;
  }
  return;
}

// ==== Aska::Audio3DEngine::UpdateAll3DObjectMatrix()
// vaddr 0x1f68690 | ghidra 0x2068690 | size 68 | symbol _ZN4Aska13Audio3DEngine23UpdateAll3DObjectMatrixEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska13Audio3DEngine23UpdateAll3DObjectMatrixEv(long param_1)

{
  long lVar1;
  
  Aska::Audio3DObject::UpdateMatrix()(param_1 + 0x10);
  for (lVar1 = *(long *)(param_1 + 0x150); param_1 + 0x140 != lVar1; lVar1 = *(long *)(lVar1 + 0x10)
      ) {
    Aska::Audio3DObject::UpdateMatrix()(lVar1);
  }
  return;
}

// ==== Aska::Audio3DEngine::UpdateSpeakersPosition()
// vaddr 0x1f686d4 | ghidra 0x20686d4 | size 1052 | symbol _ZN4Aska13Audio3DEngine22UpdateSpeakersPositionEv | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska13Audio3DEngine22UpdateSpeakersPositionEv(long param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  float fVar19;
  float fVar20;
  float fVar21;
  float fVar22;
  float fVar23;
  float fVar24;
  float fVar25;
  float fVar26;
  float fVar27;
  float fVar28;
  float fVar29;
  float fVar30;
  float fVar31;
  float fVar32;
  float fVar33;
  float fVar34;
  float fVar35;
  float fVar36;
  float fVar37;
  float fVar38;
  float fVar39;
  float fVar40;
  float fVar41;
  
  fVar12 = *(float *)(param_1 + 0x314);
  if (_UNK_027fac84 <= ABS(fVar12)) {
    iVar6 = (int)(*(float *)(param_1 + 0x28c) * _UNK_027ebdf4);
    iVar7 = (int)(*(float *)(param_1 + 0x290) * _UNK_027ebdf4);
    iVar8 = (int)(*(float *)(param_1 + 0x294) * _UNK_027ebdf4);
    iVar9 = (int)(*(float *)(param_1 + 0x298) * _UNK_027ebdf4);
    iVar10 = (int)(*(float *)(param_1 + 0x29c) * _UNK_027ebdf4);
    iVar11 = (int)(*(float *)(param_1 + 0x2a0) * _UNK_027ebdf4);
    fVar34 = *(float *)(param_1 + 0x28c) - (float)iVar6 * _UNK_027e3fd0;
    fVar29 = *(float *)(param_1 + 0x290) - (float)iVar7 * _UNK_027e3fd0;
    fVar30 = *(float *)(param_1 + 0x294) - (float)iVar8 * _UNK_027e3fd0;
    fVar19 = *(float *)(param_1 + 0x298) - (float)iVar9 * _UNK_027e3fd0;
    fVar17 = *(float *)(param_1 + 0x29c) - (float)iVar10 * _UNK_027e3fd0;
    fVar14 = *(float *)(param_1 + 0x2a0) - (float)iVar11 * _UNK_027e3fd0;
    fVar20 = fVar34 * fVar34;
    fVar21 = fVar29 * fVar29;
    fVar24 = fVar30 * fVar30;
    fVar31 = fVar19 * fVar19;
    fVar18 = fVar17 * fVar17;
    fVar15 = fVar14 * fVar14;
    fVar13 = (float)(iVar6 << 0x1f | 0x3f800000);
    fVar38 = fVar21 * (fVar21 * (fVar21 * _UNK_027ebdf8 + _UNK_027ebdfc) + _UNK_027ebe00) +
             _UNK_027ebe04;
    fVar40 = fVar24 * (fVar24 * (fVar24 * _UNK_027ebdf8 + _UNK_027ebdfc) + _UNK_027ebe00) +
             _UNK_027ebe04;
    fVar22 = fVar31 * (fVar31 * (fVar31 * _UNK_027ebdf8 + _UNK_027ebdfc) + _UNK_027ebe00) +
             _UNK_027ebe04;
    fVar25 = fVar18 * (fVar18 * (fVar18 * _UNK_027ebdf8 + _UNK_027ebdfc) + _UNK_027ebe00) +
             _UNK_027ebe04;
    fVar26 = fVar15 * (fVar15 * (fVar15 * _UNK_027ebdf8 + _UNK_027ebdfc) + _UNK_027ebe00) +
             _UNK_027ebe04;
    fVar1 = (float)(iVar7 << 0x1f | 0x3f800000);
    fVar2 = (float)(iVar8 << 0x1f | 0x3f800000);
    fVar3 = (float)(iVar9 << 0x1f | 0x3f800000);
    fVar4 = (float)(iVar10 << 0x1f | 0x3f800000);
    fVar5 = (float)(iVar11 << 0x1f | 0x3f800000);
    fVar35 = fVar1 * _UNK_027ebe0c;
    fVar39 = fVar2 * _UNK_027ebe0c;
    fVar41 = fVar3 * _UNK_027ebe0c;
    fVar23 = fVar4 * _UNK_027ebe0c;
    fVar27 = fVar5 * _UNK_027ebe0c;
    fVar28 = fVar20 * (fVar20 * (fVar20 * (fVar20 * _UNK_027f7ca4 + _UNK_027f7ca8) + _UNK_027f7cac)
                      + _UNK_027f7cb0) + _UNK_027f7cb4;
    fVar32 = fVar21 * (fVar21 * (fVar21 * (fVar21 * _UNK_027f7ca4 + _UNK_027f7ca8) + _UNK_027f7cac)
                      + _UNK_027f7cb0) + _UNK_027f7cb4;
    fVar33 = fVar24 * (fVar24 * (fVar24 * (fVar24 * _UNK_027f7ca4 + _UNK_027f7ca8) + _UNK_027f7cac)
                      + _UNK_027f7cb0) + _UNK_027f7cb4;
    fVar36 = fVar31 * (fVar31 * (fVar31 * (fVar31 * _UNK_027f7ca4 + _UNK_027f7ca8) + _UNK_027f7cac)
                      + _UNK_027f7cb0) + _UNK_027f7cb4;
    fVar37 = fVar18 * (fVar18 * (fVar18 * (fVar18 * _UNK_027f7ca4 + _UNK_027f7ca8) + _UNK_027f7cac)
                      + _UNK_027f7cb0) + _UNK_027f7cb4;
    fVar16 = fVar15 * (fVar15 * (fVar15 * (fVar15 * _UNK_027f7ca4 + _UNK_027f7ca8) + _UNK_027f7cac)
                      + _UNK_027f7cb0) + _UNK_027f7cb4;
    *(float *)(param_1 + 0x2b8) =
         fVar12 * (fVar13 * _UNK_027ebe0c +
                  fVar20 * fVar13 *
                  (fVar20 * (fVar20 * (fVar20 * _UNK_027ebdf8 + _UNK_027ebdfc) + _UNK_027ebe00) +
                  _UNK_027ebe04));
    *(float *)(param_1 + 0x2c8) = fVar12 * (fVar35 + fVar21 * fVar1 * fVar38);
    *(undefined4 *)(param_1 + 0x2b4) = 0;
    *(undefined4 *)(param_1 + 0x2c4) = 0;
    *(undefined4 *)(param_1 + 0x2d4) = 0;
    *(undefined4 *)(param_1 + 0x2e4) = 0;
    *(undefined4 *)(param_1 + 0x2f4) = 0;
    *(float *)(param_1 + 0x2d8) = fVar12 * (fVar39 + fVar24 * fVar2 * fVar40);
    *(float *)(param_1 + 0x2e8) = fVar12 * (fVar41 + fVar31 * fVar3 * fVar22);
    *(float *)(param_1 + 0x2f8) = fVar12 * (fVar23 + fVar18 * fVar4 * fVar25);
    *(float *)(param_1 + 0x2b0) = -(fVar12 * fVar34 * fVar13 * fVar28);
    *(float *)(param_1 + 0x2c0) = -(fVar12 * fVar29 * fVar1 * fVar32);
    *(float *)(param_1 + 0x2d0) = -(fVar12 * fVar30 * fVar2 * fVar33);
    *(float *)(param_1 + 0x2e0) = -(fVar12 * fVar19 * fVar3 * fVar36);
    *(float *)(param_1 + 0x2f0) = -(fVar12 * fVar17 * fVar4 * fVar37);
    fVar13 = -(fVar12 * fVar14 * fVar5 * fVar16);
    fVar12 = fVar12 * (fVar27 + fVar15 * fVar5 * fVar26);
  }
  else {
    *(undefined4 *)(param_1 + 0x2b0) = 0;
    *(undefined8 *)(param_1 + 0x2b4) = 0;
    *(undefined4 *)(param_1 + 0x2c0) = 0;
    *(undefined8 *)(param_1 + 0x2c4) = 0;
    *(undefined4 *)(param_1 + 0x2d0) = 0;
    *(undefined8 *)(param_1 + 0x2d4) = 0;
    *(undefined4 *)(param_1 + 0x2e0) = 0;
    *(undefined8 *)(param_1 + 0x2e4) = 0;
    fVar13 = 0.0;
    *(undefined4 *)(param_1 + 0x2f0) = 0;
    *(undefined8 *)(param_1 + 0x2f4) = 0;
    fVar12 = 0.0;
  }
  *(float *)(param_1 + 0x300) = fVar13;
  *(undefined4 *)(param_1 + 0x304) = 0;
  *(float *)(param_1 + 0x308) = fVar12;
  return;
}

// ==== Aska::Audio3DEngine::UpdateSpeakerPosition(int)
// vaddr 0x1f68af0 | ghidra 0x2068af0 | size 284 | symbol _ZN4Aska13Audio3DEngine21UpdateSpeakerPositionEi | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska13Audio3DEngine21UpdateSpeakerPositionEi(long param_1,int param_2)

{
  int iVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  
  fVar2 = *(float *)(param_1 + 0x314);
  fVar3 = 0.0;
  fVar4 = 0.0;
  if (_UNK_027fac84 <= ABS(fVar2)) {
    fVar3 = *(float *)(param_1 + (long)param_2 * 4 + 0x28c);
    iVar1 = (int)(fVar3 * _UNK_027ebdf4);
    fVar3 = fVar3 + (float)iVar1 * _UNK_027edb30;
    fVar5 = fVar3 * fVar3;
    fVar4 = (float)(iVar1 << 0x1f | 0x3f800000);
    fVar3 = -(fVar2 * fVar3 * fVar4 *
                      (fVar5 * (fVar5 * (fVar5 * (fVar5 * _UNK_027f7ca4 + _UNK_027f7ca8) +
                                        _UNK_027f7cac) + _UNK_027f7cb0) + _UNK_027f7cb4));
    fVar4 = fVar2 * (fVar4 * _UNK_027ebe0c +
                    fVar5 * fVar4 *
                    (fVar5 * (fVar5 * (fVar5 * _UNK_027ebdf8 + _UNK_027ebdfc) + _UNK_027ebe00) +
                    _UNK_027ebe04));
  }
  param_1 = param_1 + (long)param_2 * 0x10;
  *(float *)(param_1 + 0x2b0) = fVar3;
  *(undefined4 *)(param_1 + 0x2b4) = 0;
  *(float *)(param_1 + 0x2b8) = fVar4;
  return;
}

// ==== Aska::Audio3DEngine::LocalFunc3DObjectDeleted(Aska::HierarchicalObject const*)
// vaddr 0x1f68c0c | ghidra 0x2068c0c | size 484 | symbol _ZN4Aska13Audio3DEngine24LocalFunc3DObjectDeletedEPKNS_18HierarchicalObjectE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska13Audio3DEngine24LocalFunc3DObjectDeletedEPKNS_18HierarchicalObjectE
               (long param_1,long param_2)

{
  int *piVar1;
  int *piVar2;
  long lVar3;
  char cVar4;
  bool bVar5;
  long lVar6;
  ulong uVar7;
  int iVar8;
  long lVar9;
  
  if (*(long *)(param_1 + 0x28) == param_2) {
    (*(code *)PTR__ZN4Aska13Audio3DEngine19DeleteAudioListenerEv_02c973b8)(param_1);
    return;
  }
  lVar3 = *(long *)(param_1 + 0x150);
joined_r0x02068c40:
  do {
    lVar6 = lVar3;
    if (param_1 + 0x140 == lVar6) {
      return;
    }
    lVar3 = *(long *)(lVar6 + 0x10);
  } while (*(long *)(lVar6 + 0x18) != param_2);
  lVar9 = *(long *)(lVar6 + 8);
  if (lVar9 != 0) {
    *(long *)(lVar9 + 0x10) = lVar3;
  }
  if (lVar3 != 0) {
    *(long *)(lVar3 + 8) = lVar9;
  }
  if (0 < *(int *)(param_1 + 0x270)) {
    *(int *)(param_1 + 0x270) = *(int *)(param_1 + 0x270) + -1;
  }
  *(long *)(lVar6 + 8) = 0;
  *(undefined8 *)(lVar6 + 0x10) = 0;
  piVar1 = (int *)(lVar6 + 0x58);
  iVar8 = 0;
code_r0x02068d24:
  do {
    if (*piVar1 == -1) goto code_r0x02068d30;
    ClearExclusiveLocal();
    bVar5 = iVar8 < 0x1ff;
    iVar8 = iVar8 + 1;
  } while (bVar5);
  piVar2 = (int *)(lVar6 + 0x5c);
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
        uVar7 = Aska::Semaphore::IsReady() const(lVar6 + 0x98);
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
          Aska::Semaphore::Wait() const(lVar6 + 0x98);
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
          if (cVar4 == '\0') goto code_r0x02068ccc;
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
code_r0x02068ccc:
  do {
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar5) {
      *piVar2 = *piVar2 + -1;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
  DataMemoryBarrier(2,3);
  goto code_r0x02068d80;
code_r0x02068d30:
  cVar4 = '\x01';
  bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
  if (bVar5) {
    *piVar1 = 0;
    cVar4 = ExclusiveMonitorsStatus();
  }
  if (cVar4 == '\0') goto code_r0x02068d78;
  goto code_r0x02068d24;
code_r0x02068d78:
  DataMemoryBarrier(2,3);
code_r0x02068d80:
  *(undefined8 *)(lVar6 + 0x18) = 0;
  DataMemoryBarrier(2,3);
  *(undefined4 *)(lVar6 + 0x58) = 0xffffffff;
  DataMemoryBarrier(2,3);
  piVar1 = (int *)(lVar6 + 0x5c);
  if (0x14 < *piVar1) {
    do {
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar5) {
        *piVar1 = *piVar1 + -1;
        cVar4 = ExclusiveMonitorsStatus();
      }
    } while (cVar4 != '\0');
    uVar7 = Aska::Semaphore::IsReady() const(lVar6 + 0x98);
    if ((uVar7 & 1) != 0) {
      Aska::Semaphore::Signal() const(lVar6 + 0x98);
    }
  }
  Aska::Audio3DObject::UpdateMatrix()(lVar6);
  goto joined_r0x02068c40;
}

// ==== Aska::AudioListener::AudioListener()
// vaddr 0x1f69a94 | ghidra 0x2069a94 | size 76 | symbol _ZN4Aska13AudioListenerC2Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska13AudioListenerC1Ev(long *param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZTVN4Aska13Audio3DObjectE_02cc1128;
  param_1[2] = 0;
  param_1[3] = 0;
  *param_1 = (long)(puVar1 + 0x10);
  param_1[1] = 0;
  Aska::FastCriticalSection::FastCriticalSection()(param_1 + 4);
  puVar1 = PTR__ZTVN4Aska13AudioListenerE_02cc28d8;
  *(undefined4 *)(param_1 + 0x1e) = 0;
  *(undefined4 *)(param_1 + 0x20) = 0;
  *param_1 = (long)(puVar1 + 0x10);
  *(undefined8 *)((long)param_1 + 0x104) = 0;
  return;
}

// ==== Aska::AudioListener::~AudioListener()
// vaddr 0x1f69ae0 | ghidra 0x2069ae0 | size 20 | symbol _ZN4Aska13AudioListenerD1Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska13AudioListenerD2Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska13Audio3DObjectE_02cc1128 + 0x10);
  (*(code *)PTR__ZN4Aska19FastCriticalSectionD2Ev_02ca21e0)(param_1 + 4);
  return;
}

// ==== Aska::AudioListener::~AudioListener()
// vaddr 0x1f69af4 | ghidra 0x2069af4 | size 40 | symbol _ZN4Aska13AudioListenerD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska13AudioListenerD0Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska13Audio3DObjectE_02cc1128 + 0x10);
  Aska::FastCriticalSection::~FastCriticalSection()(param_1 + 4);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::AudioListener::Compute()
// vaddr 0x1f69b1c | ghidra 0x2069b1c | size 408 | symbol _ZN4Aska13AudioListener7ComputeEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska13AudioListener7ComputeEv(long param_1)

{
  int *piVar1;
  int *piVar2;
  char cVar3;
  bool bVar4;
  ulong uVar5;
  int iVar6;
  undefined8 uStack_80;
  undefined4 uStack_78;
  undefined4 uStack_74;
  undefined8 uStack_70;
  undefined8 uStack_68;
  undefined8 uStack_60;
  undefined8 uStack_58;
  undefined8 uStack_50;
  undefined8 uStack_48;
  undefined8 uStack_40;
  undefined8 uStack_38;
  
  piVar1 = (int *)(param_1 + 0x58);
  iVar6 = 0;
  do {
    while (*piVar1 != -1) {
      ClearExclusiveLocal();
      bVar4 = 0x1fe < iVar6;
      iVar6 = iVar6 + 1;
      if (bVar4) {
        piVar2 = (int *)(param_1 + 0x5c);
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
              uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0x98);
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
                Aska::Semaphore::Wait() const(param_1 + 0x98);
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
                if (cVar3 == '\0') goto code_r0x02069c9c;
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
code_r0x02069c9c:
        do {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
          if (bVar4) {
            *piVar2 = *piVar2 + -1;
            cVar3 = ExclusiveMonitorsStatus();
          }
        } while (cVar3 != '\0');
        DataMemoryBarrier(2,3);
code_r0x02069b94:
        uStack_68 = *(undefined8 *)(param_1 + 0xb8);
        uStack_70 = *(undefined8 *)(param_1 + 0xb0);
        uStack_58 = *(undefined8 *)(param_1 + 200);
        uStack_60 = *(undefined8 *)(param_1 + 0xc0);
        uStack_48 = *(undefined8 *)(param_1 + 0xd8);
        uStack_50 = *(undefined8 *)(param_1 + 0xd0);
        uStack_38 = *(undefined8 *)(param_1 + 0xe8);
        uStack_40 = *(undefined8 *)(param_1 + 0xe0);
        DataMemoryBarrier(2,3);
        *(undefined4 *)(param_1 + 0x58) = 0xffffffff;
        DataMemoryBarrier(2,3);
        piVar1 = (int *)(param_1 + 0x5c);
        if (0x14 < *piVar1) {
          do {
            cVar3 = '\x01';
            bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
            if (bVar4) {
              *piVar1 = *piVar1 + -1;
              cVar3 = ExclusiveMonitorsStatus();
            }
          } while (cVar3 != '\0');
          uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0x98);
          if ((uVar5 & 1) != 0) {
            Aska::Semaphore::Signal() const(param_1 + 0x98);
          }
        }
        uStack_78 = *(undefined4 *)(param_1 + 0xf0);
        uStack_80 = 0;
        uStack_74 = 0x3f800000;
        Aska::Vector::ApplyMatrix(Aska::Vector*, Aska::Matrix const*) const(&uStack_80,param_1 + 0x100,&uStack_70);
        Aska::Quaternion::Create(Aska::Matrix const*)(param_1 + 0x110,&uStack_70);
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
  goto code_r0x02069b94;
}

// ==== Aska::AudioEmitter::AudioEmitter()
// vaddr 0x1f69cb4 | ghidra 0x2069cb4 | size 112 | symbol _ZN4Aska12AudioEmitterC1Ev | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska12AudioEmitterC2Ev(long *param_1)

{
  long lVar1;
  long lVar2;
  long lVar3;
  undefined *puVar4;
  
  puVar4 = PTR__ZTVN4Aska13Audio3DObjectE_02cc1128;
  param_1[2] = 0;
  param_1[3] = 0;
  *param_1 = (long)(puVar4 + 0x10);
  param_1[1] = 0;
  Aska::FastCriticalSection::FastCriticalSection()(param_1 + 4);
  puVar4 = PTR__ZTVN4Aska12AudioEmitterE_02cb6cc0;
  param_1[0x23] = 0;
  *(undefined1 *)(param_1 + 0x24) = 0;
  param_1[0x1e] = 0x4448000041200000;
  lVar3 = _UNK_02971988;
  lVar2 = _UNK_02971980;
  lVar1 = _UNK_02971978;
  *(undefined4 *)(param_1 + 0x22) = 0x3f800000;
  *param_1 = (long)(puVar4 + 0x10);
  param_1[0x21] = lVar3;
  param_1[0x20] = lVar2;
  param_1[0x1f] = lVar1;
  return;
}

// ==== Aska::AudioEmitter::~AudioEmitter()
// vaddr 0x1f69d24 | ghidra 0x2069d24 | size 20 | symbol _ZN4Aska12AudioEmitterD1Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12AudioEmitterD2Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska13Audio3DObjectE_02cc1128 + 0x10);
  (*(code *)PTR__ZN4Aska19FastCriticalSectionD2Ev_02ca21e0)(param_1 + 4);
  return;
}

// ==== Aska::AudioEmitter::~AudioEmitter()
// vaddr 0x1f69d38 | ghidra 0x2069d38 | size 40 | symbol _ZN4Aska12AudioEmitterD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12AudioEmitterD0Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska13Audio3DObjectE_02cc1128 + 0x10);
  Aska::FastCriticalSection::~FastCriticalSection()(param_1 + 4);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::AudioEmitter::Compute()
// vaddr 0x1f69d60 | ghidra 0x2069d60 | size 1952 | symbol _ZN4Aska12AudioEmitter7ComputeEv | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska12AudioEmitter7ComputeEv(long param_1)

{
  int *piVar1;
  int *piVar2;
  long lVar3;
  uint uVar4;
  char cVar5;
  bool bVar6;
  undefined4 uVar7;
  ulong uVar8;
  int iVar9;
  long lVar10;
  uint uVar11;
  long lVar12;
  long lVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  float fVar19;
  float fVar20;
  undefined4 uVar21;
  float fVar22;
  float fVar23;
  float afStack_188 [6];
  float fStack_170;
  float fStack_16c;
  float fStack_168;
  undefined4 uStack_164;
  undefined8 uStack_160;
  undefined8 uStack_158;
  undefined8 uStack_150;
  undefined8 uStack_148;
  undefined8 uStack_140;
  undefined8 uStack_138;
  undefined8 uStack_130;
  undefined8 uStack_128;
  undefined8 uStack_120;
  undefined8 uStack_118;
  undefined8 uStack_110;
  undefined8 uStack_108;
  undefined8 uStack_100;
  undefined8 uStack_f8;
  undefined8 uStack_f0;
  undefined8 uStack_e8;
  undefined8 uStack_e0;
  undefined8 uStack_d8;
  undefined8 uStack_d0;
  undefined8 uStack_c8;
  undefined8 uStack_c0;
  undefined8 uStack_b8;
  undefined8 uStack_b0;
  undefined8 uStack_a8;
  undefined1 auStack_a0 [16];
  
  lVar13 = *(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50;
  *(undefined8 *)(param_1 + 0x100) = 0;
  *(undefined8 *)(param_1 + 0x108) = 0;
  *(undefined8 *)(param_1 + 0xf8) = 0;
  piVar1 = (int *)(param_1 + 0x58);
  iVar9 = 0;
  do {
    while (*piVar1 != -1) {
      ClearExclusiveLocal();
      bVar6 = 0x1fe < iVar9;
      iVar9 = iVar9 + 1;
      if (bVar6) {
        piVar2 = (int *)(param_1 + 0x5c);
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
              uVar8 = Aska::Semaphore::IsReady() const(param_1 + 0x98);
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
                Aska::Semaphore::Wait() const(param_1 + 0x98);
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
                if (cVar5 == '\0') goto code_r0x0206a4e8;
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
code_r0x0206a4e8:
        do {
          cVar5 = '\x01';
          bVar6 = (bool)ExclusiveMonitorPass(piVar2,0x10);
          if (bVar6) {
            *piVar2 = *piVar2 + -1;
            cVar5 = ExclusiveMonitorsStatus();
          }
        } while (cVar5 != '\0');
        DataMemoryBarrier(2,3);
        goto code_r0x02069e0c;
      }
    }
    cVar5 = '\x01';
    bVar6 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar6) {
      *piVar1 = 0;
      cVar5 = ExclusiveMonitorsStatus();
    }
  } while (cVar5 != '\0');
  DataMemoryBarrier(2,3);
code_r0x02069e0c:
  uStack_d8 = *(undefined8 *)(param_1 + 0xb8);
  uStack_e0 = *(undefined8 *)(param_1 + 0xb0);
  uStack_c8 = *(undefined8 *)(param_1 + 200);
  uStack_d0 = *(undefined8 *)(param_1 + 0xc0);
  uStack_b8 = *(undefined8 *)(param_1 + 0xd8);
  uStack_c0 = *(undefined8 *)(param_1 + 0xd0);
  uStack_a8 = *(undefined8 *)(param_1 + 0xe8);
  uStack_b0 = *(undefined8 *)(param_1 + 0xe0);
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_1 + 0x58) = 0xffffffff;
  DataMemoryBarrier(2,3);
  piVar1 = (int *)(param_1 + 0x5c);
  if (0x14 < *piVar1) {
    do {
      cVar5 = '\x01';
      bVar6 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar6) {
        *piVar1 = *piVar1 + -1;
        cVar5 = ExclusiveMonitorsStatus();
      }
    } while (cVar5 != '\0');
    uVar8 = Aska::Semaphore::IsReady() const(param_1 + 0x98);
    if ((uVar8 & 1) != 0) {
      Aska::Semaphore::Signal() const(param_1 + 0x98);
    }
  }
  fVar17 = uStack_d8._4_4_;
  fVar20 = uStack_c8._4_4_;
  fVar16 = uStack_b8._4_4_;
  Aska::Quaternion::Create(Aska::Matrix const*)(auStack_a0,&uStack_e0);
  fVar14 = *(float *)(lVar13 + 0x4a0) - fVar17;
  fVar18 = *(float *)(lVar13 + 0x4a4) - fVar20;
  fVar22 = *(float *)(lVar13 + 0x4a8) - fVar16;
  fVar18 = fVar14 * fVar14 + fVar18 * fVar18 + fVar22 * fVar22;
  fVar14 = SQRT(fVar18);
  if (NAN(fVar14)) {
    fVar14 = (float)sqrtf(fVar18);
  }
  fVar15 = *(float *)(lVar13 + 0x6a4);
  fVar23 = 0.0;
  fVar22 = 0.0;
  fVar19 = 1.0;
  if (fVar18 < fVar15 * fVar15) {
    fVar22 = *(float *)(lVar13 + 0x6a0);
    if (fVar18 <= fVar22 * fVar22) {
      fVar19 = 0.0;
      fVar22 = 1.0;
    }
    else {
      fVar15 = fVar15 - fVar22;
      if (fVar15 <= 0.0) {
        fVar15 = 0.0;
      }
      fVar18 = (fVar15 - (fVar14 - fVar22)) * (1.0 / fVar15);
      fVar19 = (float)NEON_fminnm(fVar18,0x3f800000);
      fVar22 = 0.0;
      if (0.0 <= fVar18) {
        fVar22 = fVar19;
      }
      fVar19 = 1.0 - fVar22;
    }
  }
  Aska::Matrix::Create(Aska::Quaternion const*)(&uStack_e0,lVar13 + 0x4b0);
  Aska::Matrix::InvertLowError(Aska::Matrix*) const(&uStack_e0,&uStack_120);
  uStack_158 = uStack_118;
  uStack_160 = uStack_120;
  uStack_148 = uStack_108;
  uStack_150 = uStack_110;
  uStack_138 = uStack_f8;
  uStack_140 = uStack_100;
  uStack_128 = uStack_e8;
  uStack_130 = uStack_f0;
  fStack_170 = fVar17 - *(float *)(lVar13 + 0x4a0);
  fStack_16c = fVar20 - *(float *)(lVar13 + 0x4a4);
  uStack_164 = 0x3f800000;
  fStack_168 = fVar16 - *(float *)(lVar13 + 0x4a8);
  Aska::Vector::ApplyMatrixNoTransport(Aska::Matrix const*)(&fStack_170,&uStack_160);
  fVar16 = fStack_168;
  fVar20 = fStack_170;
  fVar17 = _UNK_027e519c;
  if ((_UNK_027e519c <= ABS(fStack_170)) ||
     (fVar18 = 1.0, fVar15 = 0.0, _UNK_027e519c <= ABS(fStack_168))) {
    fVar15 = fStack_170 * fStack_170 + 0.0 + fStack_168 * fStack_168;
    fVar18 = SQRT(fVar15);
    if (NAN(fVar18)) {
      fVar18 = (float)sqrtf(fVar15);
    }
    if (fVar17 <= fVar18) {
      fVar20 = (1.0 / fVar18) * fVar20;
      fVar16 = (1.0 / fVar18) * fVar16;
    }
    uVar21 = NEON_fminnm(fVar16,0x3f800000);
    uVar7 = 0xbf800000;
    if (-1.0 <= fVar16) {
      uVar7 = uVar21;
    }
    fVar18 = (float)acosf(uVar7);
    fVar23 = 0.0;
    fVar16 = _UNK_027edb34 - fVar18;
    if (fVar20 <= 0.0) {
      fVar16 = fVar18;
    }
    fVar18 = fVar22;
    fVar15 = fVar19;
    if (0.0 <= fVar16) {
      fVar23 = (float)NEON_fminnm(fVar16,_UNK_027edb34);
    }
  }
  afStack_188[0] = *(float *)(lVar13 + 0x61c);
  afStack_188[4] = *(float *)(lVar13 + 0x62c);
  afStack_188[5] = *(float *)(lVar13 + 0x630);
  afStack_188[1] = *(float *)(lVar13 + 0x620);
  afStack_188[2] = *(float *)(lVar13 + 0x624);
  if (fVar17 <= fVar15) {
    uVar11 = 2;
    lVar10 = 2;
    if (*(float *)(lVar13 + 0x624) <= fVar23) {
      if (*(float *)(lVar13 + 0x61c) <= fVar23) {
        if (*(float *)(lVar13 + 0x62c) <= fVar23) {
          if (*(float *)(lVar13 + 0x630) <= fVar23) {
            if (*(float *)(lVar13 + 0x620) <= fVar23) {
              uVar11 = 1;
              lVar10 = 1;
            }
            else {
              lVar10 = 5;
              uVar11 = 1;
            }
          }
          else {
            lVar10 = 4;
            uVar11 = 5;
          }
        }
        else {
          lVar10 = 0;
          uVar11 = 4;
        }
      }
      else {
        uVar11 = 0;
        lVar10 = 2;
      }
    }
    uVar4 = 2;
    if ((uint)lVar10 != uVar11) {
      uVar4 = uVar11;
    }
    lVar12 = (ulong)uVar4 * 4;
    fVar20 = afStack_188[uVar4] + _UNK_027edb34;
    if (uVar4 != 2) {
      fVar20 = afStack_188[uVar4];
    }
    lVar3 = param_1 + 0xf8;
    fVar16 = (fVar23 - afStack_188[lVar10]) / (fVar20 - afStack_188[lVar10]);
    fVar22 = (float)NEON_fminnm(fVar16,0x3f800000);
    fVar20 = 0.0;
    if (0.0 <= fVar16) {
      fVar20 = fVar22;
    }
    *(float *)(lVar3 + lVar10 * 4) = *(float *)(lVar3 + lVar10 * 4) + fVar15 * (1.0 - fVar20);
    *(float *)(lVar3 + lVar12) = *(float *)(lVar3 + lVar12) + fVar15 * fVar20;
  }
  if (fVar17 <= fVar18) {
    fVar17 = fStack_170 - *(float *)(lVar13 + 0x660);
    fVar20 = fStack_16c - *(float *)(lVar13 + 0x664);
    fVar16 = fStack_168 - *(float *)(lVar13 + 0x668);
    fVar20 = fVar17 * fVar17 + fVar20 * fVar20 + fVar16 * fVar16;
    fVar17 = SQRT(fVar20);
    if (NAN(fVar17)) {
      fVar17 = (float)sqrtf(fVar20);
    }
    fVar20 = fStack_170 - *(float *)(lVar13 + 0x640);
    fVar16 = fStack_16c - *(float *)(lVar13 + 0x644);
    fVar22 = fStack_168 - *(float *)(lVar13 + 0x648);
    fVar16 = fVar20 * fVar20 + fVar16 * fVar16 + fVar22 * fVar22;
    fVar20 = SQRT(fVar16);
    if (NAN(fVar20)) {
      fVar20 = (float)sqrtf(fVar16);
    }
    fVar16 = fStack_170 - *(float *)(lVar13 + 0x680);
    fVar22 = fStack_16c - *(float *)(lVar13 + 0x684);
    fVar19 = fStack_168 - *(float *)(lVar13 + 0x688);
    fVar22 = fVar16 * fVar16 + fVar22 * fVar22 + fVar19 * fVar19;
    fVar16 = SQRT(fVar22);
    if (NAN(fVar16)) {
      fVar16 = (float)sqrtf(fVar22);
    }
    fVar22 = fStack_170 - *(float *)(lVar13 + 0x690);
    fVar19 = fStack_16c - *(float *)(lVar13 + 0x694);
    fVar15 = fStack_168 - *(float *)(lVar13 + 0x698);
    fVar19 = fVar22 * fVar22 + fVar19 * fVar19 + fVar15 * fVar15;
    fVar22 = SQRT(fVar19);
    if (NAN(fVar22)) {
      fVar22 = (float)sqrtf(fVar19);
    }
    fVar19 = fStack_170 - *(float *)(lVar13 + 0x650);
    fVar15 = fStack_16c - *(float *)(lVar13 + 0x654);
    fVar23 = fStack_168 - *(float *)(lVar13 + 0x658);
    fVar15 = fVar19 * fVar19 + fVar15 * fVar15 + fVar23 * fVar23;
    fVar19 = SQRT(fVar15);
    if (NAN(fVar19)) {
      fVar19 = (float)sqrtf(fVar15);
    }
    fVar15 = 1.0 / (1.0 / fVar17 + 0.0 + 1.0 / fVar20 + 1.0 / fVar16 + 1.0 / fVar22 + 1.0 / fVar19);
    *(float *)(param_1 + 0xfc) = *(float *)(param_1 + 0xfc) + fVar18 * fVar15 * (1.0 / fVar19);
    *(float *)(param_1 + 0x100) = *(float *)(param_1 + 0x100) + fVar18 * fVar15 * (1.0 / fVar17);
    *(float *)(param_1 + 0xf8) = *(float *)(param_1 + 0xf8) + fVar18 * fVar15 * (1.0 / fVar20);
    *(float *)(param_1 + 0x108) = *(float *)(param_1 + 0x108) + fVar18 * fVar15 * (1.0 / fVar16);
    *(float *)(param_1 + 0x10c) = *(float *)(param_1 + 0x10c) + fVar18 * fVar15 * (1.0 / fVar22);
  }
  fVar17 = (float)(**(code **)(**(long **)(lVar13 + 0x6b0) + 0x78))
                            (fVar14 / (*(float *)(lVar13 + 0x618) * *(float *)(lVar13 + 0x6a8) *
                                      *(float *)(param_1 + 0x110)));
  fVar20 = (float)(**(code **)(**(long **)(param_1 + 0x118) + 0x78))
                            (fVar14 / (*(float *)(param_1 + 0xf4) * *(float *)(lVar13 + 0x6a8) *
                                      *(float *)(param_1 + 0x110)));
  fVar16 = 0.0;
  if (_UNK_02965bf8 < *(float *)(lVar13 + 0x610)) {
    fVar16 = (float)powf(0x41200000,*(float *)(lVar13 + 0x610) * _UNK_027edb4c);
    fVar16 = fVar16 * _UNK_027e3fd8;
  }
  fVar16 = fVar17 * fVar20 * fVar16;
  *(float *)(param_1 + 0xfc) = fVar16 * *(float *)(param_1 + 0xfc);
  *(float *)(param_1 + 0x100) = fVar16 * *(float *)(param_1 + 0x100);
  *(float *)(param_1 + 0xf8) = fVar16 * *(float *)(param_1 + 0xf8);
  *(float *)(param_1 + 0x108) = fVar16 * *(float *)(param_1 + 0x108);
  *(float *)(param_1 + 0x10c) = fVar16 * *(float *)(param_1 + 0x10c);
  *(undefined1 *)(param_1 + 0x120) = 1;
  return;
}

// ==== Aska::Audio3DObject::~Audio3DObject()
// vaddr 0x1f6a500 | ghidra 0x206a500 | size 20 | symbol _ZN4Aska13Audio3DObjectD2Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska13Audio3DObjectD2Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska13Audio3DObjectE_02cc1128 + 0x10);
  (*(code *)PTR__ZN4Aska19FastCriticalSectionD2Ev_02ca21e0)(param_1 + 4);
  return;
}

// ==== Aska::Audio3DObject::~Audio3DObject()
// vaddr 0x1f6a514 | ghidra 0x206a514 | size 40 | symbol _ZN4Aska13Audio3DObjectD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska13Audio3DObjectD0Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska13Audio3DObjectE_02cc1128 + 0x10);
  Aska::FastCriticalSection::~FastCriticalSection()(param_1 + 4);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::AudioMessageNote::~AudioMessageNote()
// vaddr 0x1f6b36c | ghidra 0x206b36c | size 4 | symbol _ZN4Aska16AudioMessageNoteD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska16AudioMessageNoteD0Ev(void)

{
  (*(code *)PTR__ZdlPv_02ca4758)();
  return;
}

// ==== Aska::AudioEffector::~AudioEffector()
// vaddr 0x1f704fc | ghidra 0x20704fc | size 112 | symbol _ZN4Aska13AudioEffectorD2Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska13AudioEffectorD2Ev(long *param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZTVN4Aska13AudioEffectorE_02cc4a78;
  *(undefined4 *)(param_1 + 4) = 0;
  *param_1 = (long)(puVar1 + 0x10);
  param_1[3] = 1;
  if (param_1[5] != 0) {
    operator delete[](void*)();
    param_1[5] = 0;
  }
  Aska::FastCriticalSection::~FastCriticalSection()(param_1 + 6);
  puVar1 = PTR__ZTVN4Aska13TDynamicQueueINS_15EffectorRequest16RequestContainerELb1EEE_02cb7d20;
  *(undefined4 *)(param_1 + 4) = 0;
  param_1[2] = (long)(puVar1 + 0x10);
  param_1[3] = 1;
  if (param_1[5] != 0) {
    operator delete[](void*)();
    param_1[5] = 0;
  }
  (*(code *)PTR__ZN4Aska11IAnimatableD2Ev_02cb13b8)(param_1);
  return;
}

// ==== Aska::TDynamicArray<Aska::AudioSmallHeap::HeapInfo, Aska::AudioAllocator<Aska::AudioSmallHeap::HeapInfo> >::~TDynamicArray()
// vaddr 0x1f70670 | ghidra 0x2070670 | size 112 | symbol _ZN4Aska13TDynamicArrayINS_14AudioSmallHeap8HeapInfoENS_14AudioAllocatorIS2_EEED2Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska13TDynamicArrayINS_14AudioSmallHeap8HeapInfoENS_14AudioAllocatorIS2_EEED2Ev
               (long *param_1)

{
  long lVar1;
  long *plVar2;
  long lVar3;
  
  *param_1 = (long)(
                   PTR__ZTVN4Aska13TDynamicArrayINS_14AudioSmallHeap8HeapInfoENS_14AudioAllocatorIS2_EEEE_02cbaab0
                   + 0x10);
  plVar2 = param_1 + 1;
  lVar1 = *plVar2;
  if (param_1[3] != lVar1) {
    lVar3 = param_1[2];
    if (lVar3 != lVar1) {
      do {
        Aska::detail::FixedSizeHeap::~FixedSizeHeap()(lVar1 + 8);
        lVar1 = lVar1 + 0x30;
      } while (lVar3 != lVar1);
      lVar1 = *plVar2;
    }
    if (lVar1 != 0) {
      operator delete[](void*)(lVar1);
    }
    param_1[2] = 0;
    param_1[3] = 0;
    *plVar2 = 0;
  }
  return;
}

// ==== Aska::TDynamicArray<Aska::AudioSmallHeap::HeapInfo, Aska::AudioAllocator<Aska::AudioSmallHeap::HeapInfo> >::~TDynamicArray()
// vaddr 0x1f706e0 | ghidra 0x20706e0 | size 108 | symbol _ZN4Aska13TDynamicArrayINS_14AudioSmallHeap8HeapInfoENS_14AudioAllocatorIS2_EEED0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska13TDynamicArrayINS_14AudioSmallHeap8HeapInfoENS_14AudioAllocatorIS2_EEED0Ev
               (long *param_1)

{
  long lVar1;
  long lVar2;
  
  lVar1 = param_1[1];
  *param_1 = (long)(
                   PTR__ZTVN4Aska13TDynamicArrayINS_14AudioSmallHeap8HeapInfoENS_14AudioAllocatorIS2_EEEE_02cbaab0
                   + 0x10);
  if (param_1[3] != lVar1) {
    lVar2 = param_1[2];
    if (lVar2 != lVar1) {
      do {
        Aska::detail::FixedSizeHeap::~FixedSizeHeap()(lVar1 + 8);
        lVar1 = lVar1 + 0x30;
      } while (lVar2 != lVar1);
      lVar1 = param_1[1];
    }
    if (lVar1 != 0) {
      operator delete[](void*)(lVar1);
    }
  }
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::AudioMixer::GetThisType() const
// vaddr 0x1f70804 | ghidra 0x2070804 | size 8 | symbol _ZNK4Aska10AudioMixer11GetThisTypeEv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK4Aska10AudioMixer11GetThisTypeEv(void)

{
  return 0;
}

// ==== Aska::AudioSmallHeap::Initialize(Aska::AudioSmallHeap::InitParam const&)
// vaddr 0x1f70ff0 | ghidra 0x2070ff0 | size 656 | symbol _ZN4Aska14AudioSmallHeap10InitializeERKNS0_9InitParamE | lib libSOA-3.7.0.so | 2026-10-08
undefined4 _ZN4Aska14AudioSmallHeap10InitializeERKNS0_9InitParamE(long param_1,long *param_2)

{
  int *piVar1;
  char cVar2;
  bool bVar3;
  undefined *puVar4;
  long lVar5;
  ulong uVar6;
  int iVar7;
  int *piVar8;
  undefined4 uVar9;
  long lVar10;
  ulong uVar11;
  long lVar12;
  ulong uVar13;
  long lStack_78;
  long lStack_70;
  long *plStack_68;
  
  if (param_1 != 0) {
    piVar8 = (int *)(param_1 + 0x38);
    iVar7 = 0;
code_r0x02071020:
    do {
      if (*piVar8 == -1) goto code_r0x0207102c;
      ClearExclusiveLocal();
      bVar3 = iVar7 < 0x1ff;
      iVar7 = iVar7 + 1;
    } while (bVar3);
    piVar1 = (int *)(param_1 + 0x3c);
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
          uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x78);
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
            Aska::Semaphore::Wait() const(param_1 + 0x78);
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
            if (cVar2 == '\0') goto code_r0x020710d8;
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
code_r0x020710d8:
    do {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar3) {
        *piVar1 = *piVar1 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
code_r0x020710e8:
    DataMemoryBarrier(2,3);
  }
  if (*(long *)(param_1 + 0xb8) == 0) {
    Aska::TDynamicArray<Aska::AudioSmallHeap::HeapInfo, Aska::AudioAllocator<Aska::AudioSmallHeap::HeapInfo> >::Reserve(unsigned long)(param_1 + 0x90,param_2[1]);
    puVar4 = PTR__ZN4Aska11SoundMemory10m_pMemHeapE_02cbbc38;
    uVar6 = param_2[1];
    if (uVar6 != 0) {
      lVar12 = 0;
      uVar13 = 0;
      do {
        lVar10 = *(long *)(*param_2 + lVar12 + 8);
        if ((lVar10 != 0) && (uVar11 = *(ulong *)(*param_2 + lVar12), (uVar11 - 1 & uVar11) == 0)) {
          lVar5 = *(long *)puVar4;
          uVar6 = uVar11;
          if (uVar11 < 0x21) {
            uVar6 = 0x20;
          }
          if (lVar5 == 0) {
            lVar5 = Aska::Global::GetAvailableMemoryManager()();
          }
          lStack_78 = Aska::MemoryManager::AlignedMalloc(unsigned long, long)(lVar5,lVar10,(long)(int)uVar6);
          if (lStack_78 != 0) {
            plStack_68 = &lStack_78;
            lStack_70 = param_1 + 0xb0;
            Aska::TArrayIterator<Aska::TDynamicArray<Aska::AudioSmallHeap::HeapInfo, Aska::AudioAllocator<Aska::AudioSmallHeap::HeapInfo> > > Aska::TDynamicArray<Aska::AudioSmallHeap::HeapInfo, Aska::AudioAllocator<Aska::AudioSmallHeap::HeapInfo> >::Insert_<Aska::Memory::TConstruct1<Aska::AudioAllocator<Aska::AudioSmallHeap::HeapInfo>, void*> >(Aska::AudioSmallHeap::HeapInfo const*, unsigned long, Aska::Memory::TConstruct1<Aska::AudioAllocator<Aska::AudioSmallHeap::HeapInfo>, void*> const&)(param_1 + 0x90,*(undefined8 *)(param_1 + 0xa0),1,&lStack_70);
            lVar5 = *(long *)(param_1 + 0xa0);
            if ((*(long *)(param_1 + 0x98) != lVar5) && (*(long *)(lVar5 + -0x30) == lStack_78)) {
              uVar6 = Aska::detail::FixedSizeHeap::Assign(void*, unsigned long, unsigned long)(lVar5 + -0x28,*(long *)(lVar5 + -0x30),lVar10,uVar11);
              if ((uVar6 & 1) != 0) {
                *(long *)(param_1 + 0xb8) =
                     *(long *)(param_1 + 0xb8) + *(long *)(lVar5 + -8) * *(long *)(lVar5 + -0x10);
              }
              uVar6 = param_2[1];
              goto code_r0x020711dc;
            }
            if (lStack_78 != 0) {
              operator delete[](void*)();
            }
          }
          Aska::AudioSmallHeap::Finalize()(param_1);
          uVar9 = 0;
          goto joined_r0x02071210;
        }
code_r0x020711dc:
        uVar13 = uVar13 + 1;
        lVar12 = lVar12 + 0x10;
      } while (uVar13 < uVar6);
    }
    uVar9 = 1;
  }
  else {
    uVar9 = 0;
  }
joined_r0x02071210:
  if (param_1 != 0) {
    DataMemoryBarrier(2,3);
    *(undefined4 *)(param_1 + 0x38) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar8 = (int *)(param_1 + 0x3c);
    if (0x14 < *piVar8) {
      do {
        cVar2 = '\x01';
        bVar3 = (bool)ExclusiveMonitorPass(piVar8,0x10);
        if (bVar3) {
          *piVar8 = *piVar8 + -1;
          cVar2 = ExclusiveMonitorsStatus();
        }
      } while (cVar2 != '\0');
      uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x78);
      if ((uVar6 & 1) != 0) {
        Aska::Semaphore::Signal() const(param_1 + 0x78);
      }
    }
  }
  return uVar9;
code_r0x0207102c:
  cVar2 = '\x01';
  bVar3 = (bool)ExclusiveMonitorPass(piVar8,0x10);
  if (bVar3) {
    *piVar8 = 0;
    cVar2 = ExclusiveMonitorsStatus();
  }
  if (cVar2 == '\0') goto code_r0x020710e8;
  goto code_r0x02071020;
}

// ==== Aska::TDynamicArray<Aska::AudioSmallHeap::HeapInfo, Aska::AudioAllocator<Aska::AudioSmallHeap::HeapInfo> >::Reserve(unsigned long)
// vaddr 0x1f71280 | ghidra 0x2071280 | size 256 | symbol _ZN4Aska13TDynamicArrayINS_14AudioSmallHeap8HeapInfoENS_14AudioAllocatorIS2_EEE7ReserveEm | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska13TDynamicArrayINS_14AudioSmallHeap8HeapInfoENS_14AudioAllocatorIS2_EEE7ReserveEm
               (long param_1,ulong param_2)

{
  long lVar1;
  undefined8 *puVar2;
  undefined8 *puVar3;
  undefined8 *puVar4;
  undefined8 *puVar5;
  undefined8 *puVar6;
  undefined8 *puVar7;
  undefined8 uVar8;
  
  if ((param_2 < 0x555555555555556) &&
     ((ulong)((*(long *)(param_1 + 0x18) - *(long *)(param_1 + 8) >> 4) * -0x5555555555555555) <
      param_2)) {
    lVar1 = *(long *)PTR__ZN4Aska11SoundMemory10m_pMemHeapE_02cbbc38;
    if (lVar1 == 0) {
      lVar1 = Aska::Global::GetAvailableMemoryManager()();
    }
    puVar2 = (undefined8 *)Aska::MemoryManager::AlignedMalloc(unsigned long, long)(lVar1,param_2 * 0x30,8);
    if (puVar2 != (undefined8 *)0x0) {
      puVar4 = *(undefined8 **)(param_1 + 8);
      puVar7 = *(undefined8 **)(param_1 + 0x10);
      puVar5 = puVar2;
      puVar6 = puVar2;
      if (puVar4 != puVar7) {
        do {
          uVar8 = puVar4[4];
          puVar5[5] = puVar4[5];
          puVar5[4] = uVar8;
          uVar8 = puVar4[2];
          puVar5[3] = puVar4[3];
          puVar5[2] = uVar8;
          puVar3 = puVar4 + 6;
          uVar8 = *puVar4;
          puVar6 = puVar5 + 6;
          puVar5[1] = puVar4[1];
          *puVar5 = uVar8;
          puVar4 = puVar3;
          puVar5 = puVar6;
        } while (puVar7 != puVar3);
        puVar7 = *(undefined8 **)(param_1 + 8);
        puVar4 = *(undefined8 **)(param_1 + 0x10);
        if (puVar7 != puVar4) {
          do {
            Aska::detail::FixedSizeHeap::~FixedSizeHeap()(puVar7 + 1);
            puVar7 = puVar7 + 6;
          } while (puVar4 != puVar7);
          puVar4 = *(undefined8 **)(param_1 + 8);
        }
      }
      if (puVar4 != (undefined8 *)0x0) {
        operator delete[](void*)(puVar4);
      }
      *(undefined8 **)(param_1 + 8) = puVar2;
      *(undefined8 **)(param_1 + 0x10) = puVar6;
      *(undefined8 **)(param_1 + 0x18) = puVar2 + param_2 * 6;
    }
  }
  return;
}

// ==== Aska::AudioSmallHeap::Finalize()
// vaddr 0x1f71380 | ghidra 0x2071380 | size 440 | symbol _ZN4Aska14AudioSmallHeap8FinalizeEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska14AudioSmallHeap8FinalizeEv(long param_1)

{
  int *piVar1;
  char cVar2;
  bool bVar3;
  ulong uVar4;
  int iVar5;
  int *piVar6;
  long *plVar7;
  long *plVar8;
  
  if (param_1 == 0) {
code_r0x02071468:
    plVar7 = *(long **)(param_1 + 0x98);
    plVar8 = *(long **)(param_1 + 0xa0);
    if (plVar7 != plVar8) {
      do {
        if (*plVar7 != 0) {
          operator delete[](void*)();
        }
        plVar7 = plVar7 + 6;
      } while (plVar8 != plVar7);
      plVar7 = *(long **)(param_1 + 0x98);
    }
    if (*(long **)(param_1 + 0xa8) != plVar7) {
      plVar8 = *(long **)(param_1 + 0xa0);
      if (plVar8 != plVar7) {
        do {
          Aska::detail::FixedSizeHeap::~FixedSizeHeap()(plVar7 + 1);
          plVar7 = plVar7 + 6;
        } while (plVar8 != plVar7);
        plVar7 = *(long **)(param_1 + 0x98);
      }
      *(long **)(param_1 + 0xa0) = plVar7;
    }
    Aska::TDynamicArray<Aska::AudioSmallHeap::HeapInfo, Aska::AudioAllocator<Aska::AudioSmallHeap::HeapInfo> >::ShrinkToFit()(param_1 + 0x90);
    *(undefined8 *)(param_1 + 0xb8) = 0;
    DataMemoryBarrier(2,3);
    *(undefined4 *)(param_1 + 0x38) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar6 = (int *)(param_1 + 0x3c);
    if (0x14 < *piVar6) {
      do {
        cVar2 = '\x01';
        bVar3 = (bool)ExclusiveMonitorPass(piVar6,0x10);
        if (bVar3) {
          *piVar6 = *piVar6 + -1;
          cVar2 = ExclusiveMonitorsStatus();
        }
      } while (cVar2 != '\0');
      uVar4 = Aska::Semaphore::IsReady() const(param_1 + 0x78);
      if ((uVar4 & 1) != 0) {
        (*(code *)PTR__ZNK4Aska9Semaphore6SignalEv_02c96cd0)(param_1 + 0x78);
        return;
      }
    }
    return;
  }
  piVar6 = (int *)(param_1 + 0x38);
  iVar5 = 0;
code_r0x0207139c:
  do {
    if (*piVar6 != -1) {
      ClearExclusiveLocal();
      bVar3 = iVar5 < 0x1ff;
      iVar5 = iVar5 + 1;
      if (bVar3) goto code_r0x0207139c;
      piVar1 = (int *)(param_1 + 0x3c);
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
            uVar4 = Aska::Semaphore::IsReady() const(param_1 + 0x78);
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
              Aska::Semaphore::Wait() const(param_1 + 0x78);
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
              if (cVar2 == '\0') goto code_r0x02071454;
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
code_r0x02071454:
      do {
        cVar2 = '\x01';
        bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
        if (bVar3) {
          *piVar1 = *piVar1 + -1;
          cVar2 = ExclusiveMonitorsStatus();
        }
      } while (cVar2 != '\0');
code_r0x02071464:
      DataMemoryBarrier(2,3);
      goto code_r0x02071468;
    }
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar6,0x10);
    if (bVar3) {
      *piVar6 = 0;
      cVar2 = ExclusiveMonitorsStatus();
    }
    if (cVar2 == '\0') goto code_r0x02071464;
  } while( true );
}

// ==== Aska::TDynamicArray<Aska::AudioSmallHeap::HeapInfo, Aska::AudioAllocator<Aska::AudioSmallHeap::HeapInfo> >::ShrinkToFit()
// vaddr 0x1f71538 | ghidra 0x2071538 | size 236 | symbol _ZN4Aska13TDynamicArrayINS_14AudioSmallHeap8HeapInfoENS_14AudioAllocatorIS2_EEE11ShrinkToFitEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska13TDynamicArrayINS_14AudioSmallHeap8HeapInfoENS_14AudioAllocatorIS2_EEE11ShrinkToFitEv
               (undefined **param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined *puStack_58;
  undefined *puStack_50;
  undefined *puStack_48;
  undefined *puStack_40;
  undefined *puStack_30;
  undefined *puStack_28;
  
  puVar1 = 
  PTR__ZTVN4Aska13TDynamicArrayINS_14AudioSmallHeap8HeapInfoENS_14AudioAllocatorIS2_EEEE_02cbaab0;
  puStack_48 = (undefined *)0x0;
  puStack_40 = (undefined *)0x0;
  puStack_58 = PTR__ZTVN4Aska13TDynamicArrayINS_14AudioSmallHeap8HeapInfoENS_14AudioAllocatorIS2_EEEE_02cbaab0
               + 0x10;
  puStack_50 = (undefined *)0x0;
  puStack_30 = param_1[1];
  puStack_28 = param_1[2];
  Aska::TArrayIterator<Aska::TDynamicArray<Aska::AudioSmallHeap::HeapInfo, Aska::AudioAllocator<Aska::AudioSmallHeap::HeapInfo> > > Aska::TDynamicArray<Aska::AudioSmallHeap::HeapInfo, Aska::AudioAllocator<Aska::AudioSmallHeap::HeapInfo> >::Insert_<Aska::Memory::TUninitializedCopy<Aska::AudioSmallHeap::HeapInfo*> >(Aska::AudioSmallHeap::HeapInfo const*, unsigned long, Aska::Memory::TUninitializedCopy<Aska::AudioSmallHeap::HeapInfo*> const&)(&puStack_58,0,((long)puStack_28 - (long)puStack_30 >> 4) * -0x5555555555555555,
                  &puStack_30);
  if (&puStack_58 == param_1) {
    puVar2 = param_1[3];
  }
  else {
    puVar4 = param_1[2];
    puVar3 = param_1[1];
    param_1[1] = puStack_50;
    param_1[2] = puStack_48;
    puVar2 = param_1[3];
    param_1[3] = puStack_40;
    puStack_50 = puVar3;
    puStack_48 = puVar4;
    puStack_40 = puVar2;
  }
  puVar3 = puStack_48;
  puStack_58 = puVar1 + 0x10;
  puVar1 = puStack_50;
  if (puVar2 != puStack_50) {
    for (; puVar3 != puVar1; puVar1 = puVar1 + 0x30) {
      Aska::detail::FixedSizeHeap::~FixedSizeHeap()(puVar1 + 8);
    }
    if (puStack_50 != (undefined *)0x0) {
      operator delete[](void*)(puStack_50);
    }
  }
  return;
}

// ==== Aska::AudioSmallHeap::Allocate(unsigned long, unsigned long)
// vaddr 0x1f71624 | ghidra 0x2071624 | size 460 | symbol _ZN4Aska14AudioSmallHeap8AllocateEmm | lib libSOA-3.7.0.so | 2026-10-08
long _ZN4Aska14AudioSmallHeap8AllocateEmm(long param_1,ulong param_2,int param_3)

{
  int *piVar1;
  char cVar2;
  bool bVar3;
  long lVar4;
  ulong uVar5;
  int iVar6;
  int *piVar7;
  
  if (param_1 != 0) {
    piVar7 = (int *)(param_1 + 0x38);
    iVar6 = 0;
code_r0x0207164c:
    do {
      if (*piVar7 == -1) goto code_r0x02071658;
      ClearExclusiveLocal();
      bVar3 = iVar6 < 0x1ff;
      iVar6 = iVar6 + 1;
    } while (bVar3);
    piVar1 = (int *)(param_1 + 0x3c);
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
          uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0x78);
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
            Aska::Semaphore::Wait() const(param_1 + 0x78);
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
            if (cVar2 == '\0') goto code_r0x02071704;
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
code_r0x02071704:
    do {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar3) {
        *piVar1 = *piVar1 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
code_r0x02071714:
    DataMemoryBarrier(2,3);
  }
  if (param_2 == 0) {
    lVar4 = 0;
  }
  else {
    for (lVar4 = *(long *)(param_1 + 0x98); lVar4 != *(long *)(param_1 + 0xa0); lVar4 = lVar4 + 0x30
        ) {
      if (param_2 <= *(ulong *)(lVar4 + 0x20)) {
        lVar4 = Aska::detail::FixedSizeHeap::Allocate(unsigned long, unsigned long)(lVar4 + 8,param_2,0x20);
        if (lVar4 != 0) goto joined_r0x02071748;
        break;
      }
    }
    lVar4 = *(long *)PTR__ZN4Aska11SoundMemory10m_pMemHeapE_02cbbc38;
    if (lVar4 == 0) {
      lVar4 = Aska::Global::GetAvailableMemoryManager()();
    }
    lVar4 = Aska::MemoryManager::AlignedMalloc(unsigned long, long)(lVar4,param_2,(long)param_3);
  }
joined_r0x02071748:
  if (param_1 != 0) {
    DataMemoryBarrier(2,3);
    *(undefined4 *)(param_1 + 0x38) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar7 = (int *)(param_1 + 0x3c);
    if (0x14 < *piVar7) {
      do {
        cVar2 = '\x01';
        bVar3 = (bool)ExclusiveMonitorPass(piVar7,0x10);
        if (bVar3) {
          *piVar7 = *piVar7 + -1;
          cVar2 = ExclusiveMonitorsStatus();
        }
      } while (cVar2 != '\0');
      uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0x78);
      if ((uVar5 & 1) != 0) {
        Aska::Semaphore::Signal() const(param_1 + 0x78);
      }
    }
  }
  return lVar4;
code_r0x02071658:
  cVar2 = '\x01';
  bVar3 = (bool)ExclusiveMonitorPass(piVar7,0x10);
  if (bVar3) {
    *piVar7 = 0;
    cVar2 = ExclusiveMonitorsStatus();
  }
  if (cVar2 == '\0') goto code_r0x02071714;
  goto code_r0x0207164c;
}

// ==== Aska::AudioSmallHeap::Reallocate(unsigned long, void*, unsigned long)
// vaddr 0x1f717f0 | ghidra 0x20717f0 | size 584 | symbol _ZN4Aska14AudioSmallHeap10ReallocateEmPvm | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Possible PIC construction at 0x02071820: Changing call to branch */
/* WARNING: Removing unreachable block (ram,0x02071824) */
/* WARNING: Removing unreachable block (ram,0x0207182c) */
/* WARNING: Removing unreachable block (ram,0x02071830) */
/* WARNING: Removing unreachable block (ram,0x02071838) */
/* WARNING: Removing unreachable block (ram,0x02071850) */
/* WARNING: Removing unreachable block (ram,0x02071860) */
/* WARNING: Removing unreachable block (ram,0x02071864) */
/* WARNING: Removing unreachable block (ram,0x0207186c) */
/* WARNING: Removing unreachable block (ram,0x02071874) */
/* WARNING: Removing unreachable block (ram,0x020718c4) */
/* WARNING: Removing unreachable block (ram,0x020718d4) */
/* WARNING: Removing unreachable block (ram,0x020718ec) */
/* WARNING: Removing unreachable block (ram,0x020718f4) */
/* WARNING: Removing unreachable block (ram,0x020718fc) */
/* WARNING: Removing unreachable block (ram,0x020718e0) */
/* WARNING: Removing unreachable block (ram,0x02071904) */
/* WARNING: Removing unreachable block (ram,0x0207190c) */
/* WARNING: Removing unreachable block (ram,0x02071914) */
/* WARNING: Removing unreachable block (ram,0x020718d0) */
/* WARNING: Removing unreachable block (ram,0x02071920) */
/* WARNING: Removing unreachable block (ram,0x02071880) */
/* WARNING: Removing unreachable block (ram,0x02071888) */
/* WARNING: Removing unreachable block (ram,0x02071928) */
/* WARNING: Removing unreachable block (ram,0x02071930) */
/* WARNING: Removing unreachable block (ram,0x02071844) */
/* WARNING: Removing unreachable block (ram,0x0207184c) */
/* WARNING: Removing unreachable block (ram,0x02071938) */
/* WARNING: Removing unreachable block (ram,0x0207193c) */
/* WARNING: Removing unreachable block (ram,0x02071948) */
/* WARNING: Removing unreachable block (ram,0x02071970) */
/* WARNING: Removing unreachable block (ram,0x02071958) */
/* WARNING: Removing unreachable block (ram,0x02071964) */
/* WARNING: Removing unreachable block (ram,0x02071978) */
/* WARNING: Removing unreachable block (ram,0x02071998) */
/* WARNING: Removing unreachable block (ram,0x020719a0) */
/* WARNING: Removing unreachable block (ram,0x020719a8) */
/* WARNING: Removing unreachable block (ram,0x020719b8) */
/* WARNING: Removing unreachable block (ram,0x0207196c) */
/* WARNING: Removing unreachable block (ram,0x020719c0) */
/* WARNING: Removing unreachable block (ram,0x020719c4) */
/* WARNING: Removing unreachable block (ram,0x020719d4) */
/* WARNING: Removing unreachable block (ram,0x020719d8) */
/* WARNING: Removing unreachable block (ram,0x02071a30) */
/* WARNING: Removing unreachable block (ram,0x020719e8) */
/* WARNING: Removing unreachable block (ram,0x02071a00) */
/* WARNING: Removing unreachable block (ram,0x020719f8) */
/* WARNING: Removing unreachable block (ram,0x02071a04) */

undefined8
_ZN4Aska14AudioSmallHeap10ReallocateEmPvm
          (undefined8 param_1,long param_2,long param_3,undefined8 param_4)

{
  undefined8 uVar1;
  
  if ((param_3 != 0) && (param_2 == 0)) {
    Aska::AudioSmallHeap::Free(void*, unsigned long)(param_1,param_3,0);
    return 0;
  }
  uVar1 = (*(code *)PTR__ZN4Aska14AudioSmallHeap8AllocateEmm_02ca08e8)(param_1,param_2,param_4);
  return uVar1;
}

// ==== Aska::AudioSmallHeap::Free(void*, unsigned long)
// vaddr 0x1f71a38 | ghidra 0x2071a38 | size 432 | symbol _ZN4Aska14AudioSmallHeap4FreeEPvm | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska14AudioSmallHeap4FreeEPvm(long param_1,long param_2,undefined8 param_3)

{
  int *piVar1;
  long lVar2;
  long lVar3;
  char cVar4;
  bool bVar5;
  ulong uVar6;
  int iVar7;
  int *piVar8;
  
  if (param_1 != 0) {
    piVar8 = (int *)(param_1 + 0x38);
    iVar7 = 0;
code_r0x02071a60:
    do {
      if (*piVar8 == -1) goto code_r0x02071a6c;
      ClearExclusiveLocal();
      bVar5 = iVar7 < 0x1ff;
      iVar7 = iVar7 + 1;
    } while (bVar5);
    piVar1 = (int *)(param_1 + 0x3c);
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
          uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x78);
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
            Aska::Semaphore::Wait() const(param_1 + 0x78);
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
            if (cVar4 == '\0') goto code_r0x02071b18;
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
code_r0x02071b18:
    do {
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar5) {
        *piVar1 = *piVar1 + -1;
        cVar4 = ExclusiveMonitorsStatus();
      }
    } while (cVar4 != '\0');
code_r0x02071b28:
    DataMemoryBarrier(2,3);
  }
  if (param_2 != 0) {
    lVar3 = *(long *)(param_1 + 0xa0);
    for (lVar2 = *(long *)(param_1 + 0x98); lVar2 != lVar3; lVar2 = lVar2 + 0x30) {
      uVar6 = Aska::detail::FixedSizeHeap::IsValidPointer(void const*) const(lVar2 + 8,param_2);
      if ((uVar6 & 1) != 0) {
        Aska::detail::FixedSizeHeap::Free(void*, unsigned long)(lVar2 + 8,param_2,param_3);
        goto joined_r0x02071bd0;
      }
    }
    operator delete[](void*)(param_2);
  }
joined_r0x02071bd0:
  if (param_1 != 0) {
    DataMemoryBarrier(2,3);
    *(undefined4 *)(param_1 + 0x38) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar8 = (int *)(param_1 + 0x3c);
    if (0x14 < *piVar8) {
      do {
        cVar4 = '\x01';
        bVar5 = (bool)ExclusiveMonitorPass(piVar8,0x10);
        if (bVar5) {
          *piVar8 = *piVar8 + -1;
          cVar4 = ExclusiveMonitorsStatus();
        }
      } while (cVar4 != '\0');
      uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x78);
      if ((uVar6 & 1) != 0) {
        (*(code *)PTR__ZNK4Aska9Semaphore6SignalEv_02c96cd0)(param_1 + 0x78);
        return;
      }
    }
  }
  return;
code_r0x02071a6c:
  cVar4 = '\x01';
  bVar5 = (bool)ExclusiveMonitorPass(piVar8,0x10);
  if (bVar5) {
    *piVar8 = 0;
    cVar4 = ExclusiveMonitorsStatus();
  }
  if (cVar4 == '\0') goto code_r0x02071b28;
  goto code_r0x02071a60;
}

// ==== Aska::AudioSmallHeap::GetUsedSize() const
// vaddr 0x1f71be8 | ghidra 0x2071be8 | size 392 | symbol _ZNK4Aska14AudioSmallHeap11GetUsedSizeEv | lib libSOA-3.7.0.so | 2026-10-08
long _ZNK4Aska14AudioSmallHeap11GetUsedSizeEv(long param_1)

{
  long *plVar1;
  int *piVar2;
  long lVar3;
  char cVar4;
  bool bVar5;
  long lVar6;
  ulong uVar7;
  int iVar8;
  int *piVar9;
  long lVar10;
  long lVar11;
  long lVar12;
  
  if (param_1 != 0) {
    piVar9 = (int *)(param_1 + 0x38);
    iVar8 = 0;
    do {
      while (*piVar9 == -1) {
        cVar4 = '\x01';
        bVar5 = (bool)ExclusiveMonitorPass(piVar9,0x10);
        if (bVar5) {
          *piVar9 = 0;
          cVar4 = ExclusiveMonitorsStatus();
        }
        if (cVar4 == '\0') goto code_r0x02071ccc;
      }
      ClearExclusiveLocal();
      bVar5 = iVar8 < 0x1ff;
      iVar8 = iVar8 + 1;
    } while (bVar5);
    piVar2 = (int *)(param_1 + 0x3c);
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
          uVar7 = Aska::Semaphore::IsReady() const(param_1 + 0x78);
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
            Aska::Semaphore::Wait() const(param_1 + 0x78);
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
            if (cVar4 == '\0') goto code_r0x02071cbc;
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
code_r0x02071cbc:
    do {
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
      if (bVar5) {
        *piVar2 = *piVar2 + -1;
        cVar4 = ExclusiveMonitorsStatus();
      }
    } while (cVar4 != '\0');
code_r0x02071ccc:
    DataMemoryBarrier(2,3);
  }
  lVar11 = *(long *)(param_1 + 0x98);
  lVar3 = *(long *)(param_1 + 0xa0);
  if (lVar11 == lVar3) {
    lVar10 = 0;
  }
  else {
    lVar10 = 0;
    do {
      lVar12 = *(long *)(lVar11 + 0x28);
      lVar6 = Aska::detail::FixedSizeHeap::GetFreeBlockCount() const(lVar11 + 8);
      plVar1 = (long *)(lVar11 + 0x20);
      lVar11 = lVar11 + 0x30;
      lVar10 = lVar10 + (lVar12 - lVar6) * *plVar1;
    } while (lVar3 != lVar11);
  }
  if (param_1 != 0) {
    DataMemoryBarrier(2,3);
    *(undefined4 *)(param_1 + 0x38) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar9 = (int *)(param_1 + 0x3c);
    if (0x14 < *piVar9) {
      do {
        cVar4 = '\x01';
        bVar5 = (bool)ExclusiveMonitorPass(piVar9,0x10);
        if (bVar5) {
          *piVar9 = *piVar9 + -1;
          cVar4 = ExclusiveMonitorsStatus();
        }
      } while (cVar4 != '\0');
      uVar7 = Aska::Semaphore::IsReady() const(param_1 + 0x78);
      if ((uVar7 & 1) != 0) {
        Aska::Semaphore::Signal() const(param_1 + 0x78);
      }
    }
  }
  return lVar10;
}

// ==== Aska::TArrayIterator<Aska::TDynamicArray<Aska::AudioSmallHeap::HeapInfo, Aska::AudioAllocator<Aska::AudioSmallHeap::HeapInfo> > > Aska::TDynamicArray<Aska::AudioSmallHeap::HeapInfo, Aska::AudioAllocator<Aska::AudioSmallHeap::HeapInfo> >::Insert_<Aska::Memory::TConstruct1<Aska::AudioAllocator<Aska::AudioSmallHeap::HeapInfo>, void*> >(Aska::AudioSmallHeap::HeapInfo const*, unsigned long, Aska::Memory::TConstruct1<Aska::AudioAllocator<Aska::AudioSmallHeap::HeapInfo>, void*> const&)
// vaddr 0x1f71d70 | ghidra 0x2071d70 | size 492 | symbol _ZN4Aska13TDynamicArrayINS_14AudioSmallHeap8HeapInfoENS_14AudioAllocatorIS2_EEE7Insert_INS_6Memory11TConstruct1IS4_PvEEEENS_14TArrayIteratorIS5_EEPKS2_mRKT_ | lib libSOA-3.7.0.so | 2026-10-08
undefined8 *
_ZN4Aska13TDynamicArrayINS_14AudioSmallHeap8HeapInfoENS_14AudioAllocatorIS2_EEE7Insert_INS_6Memory11TConstruct1IS4_PvEEEENS_14TArrayIteratorIS5_EEPKS2_mRKT_
          (long param_1,undefined8 *param_2,long param_3,long param_4)

{
  undefined8 *puVar1;
  undefined8 *puVar2;
  ulong uVar3;
  undefined8 *puVar4;
  undefined8 *puVar5;
  ulong uVar6;
  long lVar7;
  undefined8 *puVar8;
  undefined8 *puVar9;
  undefined8 uVar10;
  
  if (param_3 != 0) {
    puVar2 = *(undefined8 **)(param_1 + 0x10);
    lVar7 = *(long *)(param_1 + 0x18) - *(long *)(param_1 + 8) >> 4;
    uVar6 = param_3 + ((long)puVar2 - *(long *)(param_1 + 8) >> 4) * -0x5555555555555555;
    if ((ulong)(lVar7 * -0x5555555555555555) < uVar6) {
      uVar3 = lVar7 * 0x5555555555555556;
      if (uVar6 <= uVar3) {
        uVar6 = uVar3;
      }
      if (uVar6 < 0x555555555555556) {
        lVar7 = *(long *)PTR__ZN4Aska11SoundMemory10m_pMemHeapE_02cbbc38;
        if (lVar7 == 0) {
          lVar7 = Aska::Global::GetAvailableMemoryManager()();
        }
        puVar2 = (undefined8 *)Aska::MemoryManager::AlignedMalloc(unsigned long, long)(lVar7,uVar6 * 0x30,8);
        if (puVar2 != (undefined8 *)0x0) {
          puVar1 = puVar2;
          for (puVar4 = *(undefined8 **)(param_1 + 8); puVar4 != param_2; puVar4 = puVar4 + 6) {
            uVar10 = puVar4[4];
            puVar1[5] = puVar4[5];
            puVar1[4] = uVar10;
            uVar10 = puVar4[2];
            puVar1[3] = puVar4[3];
            puVar1[2] = uVar10;
            uVar10 = *puVar4;
            puVar1[1] = puVar4[1];
            *puVar1 = uVar10;
            puVar1 = puVar1 + 6;
          }
          *puVar1 = **(undefined8 **)(param_4 + 8);
          Aska::detail::FixedSizeHeap::FixedSizeHeap()(puVar1 + 1);
          puVar5 = *(undefined8 **)(param_1 + 0x10);
          puVar9 = puVar1 + param_3 * 6;
          puVar4 = puVar9;
          if (puVar5 != param_2) {
            do {
              uVar10 = param_2[4];
              puVar4[5] = param_2[5];
              puVar4[4] = uVar10;
              uVar10 = param_2[2];
              puVar4[3] = param_2[3];
              puVar4[2] = uVar10;
              puVar8 = param_2 + 6;
              uVar10 = *param_2;
              puVar9 = puVar4 + 6;
              puVar4[1] = param_2[1];
              *puVar4 = uVar10;
              param_2 = puVar8;
              puVar4 = puVar9;
            } while (puVar5 != puVar8);
            param_2 = *(undefined8 **)(param_1 + 0x10);
          }
          puVar4 = *(undefined8 **)(param_1 + 8);
          if (puVar4 != param_2) {
            do {
              Aska::detail::FixedSizeHeap::~FixedSizeHeap()(puVar4 + 1);
              puVar4 = puVar4 + 6;
            } while (param_2 != puVar4);
            param_2 = *(undefined8 **)(param_1 + 8);
          }
          if (param_2 != (undefined8 *)0x0) {
            operator delete[](void*)(param_2);
          }
          *(undefined8 **)(param_1 + 8) = puVar2;
          *(undefined8 **)(param_1 + 0x10) = puVar9;
          *(undefined8 **)(param_1 + 0x18) = puVar2 + uVar6 * 6;
          param_2 = puVar1;
        }
      }
    }
    else {
      if (puVar2 != param_2) {
        puVar2 = puVar2 + -6;
        do {
          uVar10 = puVar2[4];
          puVar4 = puVar2 + param_3 * 6;
          puVar4[5] = puVar2[5];
          puVar4[4] = uVar10;
          uVar10 = puVar2[2];
          puVar4[3] = puVar2[3];
          puVar4[2] = uVar10;
          uVar10 = *puVar2;
          puVar4[1] = puVar2[1];
          *puVar4 = uVar10;
          Aska::detail::FixedSizeHeap::~FixedSizeHeap()(puVar2 + 1);
          puVar2 = puVar2 + -6;
        } while ((long)puVar2 - (long)param_2 != -0x30);
      }
      *param_2 = **(undefined8 **)(param_4 + 8);
      Aska::detail::FixedSizeHeap::FixedSizeHeap()(param_2 + 1);
      *(long *)(param_1 + 0x10) = *(long *)(param_1 + 0x10) + param_3 * 0x30;
    }
  }
  return param_2;
}

// ==== Aska::TArrayIterator<Aska::TDynamicArray<Aska::AudioSmallHeap::HeapInfo, Aska::AudioAllocator<Aska::AudioSmallHeap::HeapInfo> > > Aska::TDynamicArray<Aska::AudioSmallHeap::HeapInfo, Aska::AudioAllocator<Aska::AudioSmallHeap::HeapInfo> >::Insert_<Aska::Memory::TUninitializedCopy<Aska::AudioSmallHeap::HeapInfo*> >(Aska::AudioSmallHeap::HeapInfo const*, unsigned long, Aska::Memory::TUninitializedCopy<Aska::AudioSmallHeap::HeapInfo*> const&)
// vaddr 0x1f71f5c | ghidra 0x2071f5c | size 548 | symbol _ZN4Aska13TDynamicArrayINS_14AudioSmallHeap8HeapInfoENS_14AudioAllocatorIS2_EEE7Insert_INS_6Memory18TUninitializedCopyIPS2_EEEENS_14TArrayIteratorIS5_EEPKS2_mRKT_ | lib libSOA-3.7.0.so | 2026-10-08
undefined8 *
_ZN4Aska13TDynamicArrayINS_14AudioSmallHeap8HeapInfoENS_14AudioAllocatorIS2_EEE7Insert_INS_6Memory18TUninitializedCopyIPS2_EEEENS_14TArrayIteratorIS5_EEPKS2_mRKT_
          (long param_1,undefined8 *param_2,long param_3,long *param_4)

{
  undefined8 *puVar1;
  undefined8 *puVar2;
  ulong uVar3;
  undefined8 *puVar4;
  undefined8 *puVar5;
  ulong uVar6;
  long lVar7;
  undefined8 *puVar8;
  undefined8 *puVar9;
  undefined8 uVar10;
  
  if (param_3 != 0) {
    puVar2 = *(undefined8 **)(param_1 + 0x10);
    lVar7 = *(long *)(param_1 + 0x18) - *(long *)(param_1 + 8) >> 4;
    uVar6 = param_3 + ((long)puVar2 - *(long *)(param_1 + 8) >> 4) * -0x5555555555555555;
    if ((ulong)(lVar7 * -0x5555555555555555) < uVar6) {
      uVar3 = lVar7 * 0x5555555555555556;
      if (uVar6 <= uVar3) {
        uVar6 = uVar3;
      }
      if (uVar6 < 0x555555555555556) {
        lVar7 = *(long *)PTR__ZN4Aska11SoundMemory10m_pMemHeapE_02cbbc38;
        if (lVar7 == 0) {
          lVar7 = Aska::Global::GetAvailableMemoryManager()();
        }
        puVar2 = (undefined8 *)Aska::MemoryManager::AlignedMalloc(unsigned long, long)(lVar7,uVar6 * 0x30,8);
        if (puVar2 != (undefined8 *)0x0) {
          puVar1 = puVar2;
          for (puVar4 = *(undefined8 **)(param_1 + 8); puVar4 != param_2; puVar4 = puVar4 + 6) {
            uVar10 = puVar4[4];
            puVar1[5] = puVar4[5];
            puVar1[4] = uVar10;
            uVar10 = puVar4[2];
            puVar1[3] = puVar4[3];
            puVar1[2] = uVar10;
            uVar10 = *puVar4;
            puVar1[1] = puVar4[1];
            *puVar1 = uVar10;
            puVar1 = puVar1 + 6;
          }
          puVar5 = (undefined8 *)param_4[1];
          puVar9 = puVar1;
          for (puVar4 = (undefined8 *)*param_4; puVar4 != puVar5; puVar4 = puVar4 + 6) {
            uVar10 = puVar4[4];
            puVar9[5] = puVar4[5];
            puVar9[4] = uVar10;
            uVar10 = puVar4[2];
            puVar9[3] = puVar4[3];
            puVar9[2] = uVar10;
            uVar10 = *puVar4;
            puVar9[1] = puVar4[1];
            *puVar9 = uVar10;
            puVar9 = puVar9 + 6;
          }
          puVar5 = *(undefined8 **)(param_1 + 0x10);
          puVar9 = puVar1 + param_3 * 6;
          puVar4 = puVar9;
          if (puVar5 != param_2) {
            do {
              uVar10 = param_2[4];
              puVar4[5] = param_2[5];
              puVar4[4] = uVar10;
              uVar10 = param_2[2];
              puVar4[3] = param_2[3];
              puVar4[2] = uVar10;
              puVar8 = param_2 + 6;
              uVar10 = *param_2;
              puVar9 = puVar4 + 6;
              puVar4[1] = param_2[1];
              *puVar4 = uVar10;
              param_2 = puVar8;
              puVar4 = puVar9;
            } while (puVar5 != puVar8);
            param_2 = *(undefined8 **)(param_1 + 0x10);
          }
          puVar4 = *(undefined8 **)(param_1 + 8);
          if (puVar4 != param_2) {
            do {
              Aska::detail::FixedSizeHeap::~FixedSizeHeap()(puVar4 + 1);
              puVar4 = puVar4 + 6;
            } while (param_2 != puVar4);
            param_2 = *(undefined8 **)(param_1 + 8);
          }
          if (param_2 != (undefined8 *)0x0) {
            operator delete[](void*)(param_2);
          }
          *(undefined8 **)(param_1 + 8) = puVar2;
          *(undefined8 **)(param_1 + 0x10) = puVar9;
          *(undefined8 **)(param_1 + 0x18) = puVar2 + uVar6 * 6;
          param_2 = puVar1;
        }
      }
    }
    else {
      if (puVar2 != param_2) {
        puVar2 = puVar2 + -6;
        do {
          uVar10 = puVar2[4];
          puVar4 = puVar2 + param_3 * 6;
          puVar4[5] = puVar2[5];
          puVar4[4] = uVar10;
          uVar10 = puVar2[2];
          puVar4[3] = puVar2[3];
          puVar4[2] = uVar10;
          uVar10 = *puVar2;
          puVar4[1] = puVar2[1];
          *puVar4 = uVar10;
          Aska::detail::FixedSizeHeap::~FixedSizeHeap()(puVar2 + 1);
          puVar2 = puVar2 + -6;
        } while ((long)puVar2 - (long)param_2 != -0x30);
      }
      puVar4 = (undefined8 *)param_4[1];
      puVar1 = param_2;
      for (puVar2 = (undefined8 *)*param_4; puVar2 != puVar4; puVar2 = puVar2 + 6) {
        uVar10 = puVar2[4];
        puVar1[5] = puVar2[5];
        puVar1[4] = uVar10;
        uVar10 = puVar2[2];
        puVar1[3] = puVar2[3];
        puVar1[2] = uVar10;
        uVar10 = *puVar2;
        puVar1[1] = puVar2[1];
        *puVar1 = uVar10;
        puVar1 = puVar1 + 6;
      }
      *(long *)(param_1 + 0x10) = *(long *)(param_1 + 0x10) + param_3 * 0x30;
    }
  }
  return param_2;
}

// ==== Aska::AudioEffector::AudioEffector()
// vaddr 0x2240e94 | ghidra 0x2340e94 | size 56 | symbol _ZN4Aska13AudioEffectorC2Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska13AudioEffectorC1Ev(long *param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  
  puVar2 = PTR__ZTVN4Aska13AudioEffectorE_02cc4a78;
  param_1[5] = 0;
  puVar1 = PTR__ZTVN4Aska18TSoundDynamicQueueINS_15EffectorRequest16RequestContainerEEE_02cc40e0 +
           0x10;
  *param_1 = (long)(puVar2 + 0x10);
  param_1[1] = 0;
  param_1[2] = (long)puVar1;
  param_1[3] = 1;
  *(undefined4 *)(param_1 + 4) = 0;
  (*(code *)PTR__ZN4Aska19FastCriticalSectionC1Ev_02cade18)(param_1 + 6);
  return;
}

// ==== Aska::AudioEffector::SetupEffector(unsigned int)
// vaddr 0x2240ecc | ghidra 0x2340ecc | size 312 | symbol _ZN4Aska13AudioEffector13SetupEffectorEj | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska13AudioEffector13SetupEffectorEj(long param_1,uint param_2)

{
  undefined8 uVar1;
  long lVar2;
  long lVar3;
  ulong uVar4;
  
  if (param_2 - 1 < 7) {
    lVar2 = Aska::SoundMemory::Malloc(unsigned long)(0x88);
    *(long *)(param_1 + 8) = lVar2;
    lVar3 = 0;
    if (lVar2 != 0) {
      Aska::SubBusSL::SubBusSL()();
      lVar3 = *(long *)(param_1 + 8);
    }
    uVar1 = 0;
    if (lVar3 != 0) {
      uVar4 = Aska::SubBusSL::SetupBus(Aska::InitBusContext*, unsigned int)(lVar3,(ulong)param_2 * 0xc + 0x2ce7124,param_2);
      if ((uVar4 & 1) == 0) {
        if (*(long **)(param_1 + 8) != (long *)0x0) {
          (**(code **)(**(long **)(param_1 + 8) + 8))();
        }
        uVar1 = 0;
        *(undefined8 *)(param_1 + 8) = 0;
      }
      else if (*(int *)(param_1 + 0x20) == 5) {
        uVar1 = 1;
      }
      else {
        if (*(long *)(param_1 + 0x28) != 0) {
          operator delete[](void*)();
          *(undefined8 *)(param_1 + 0x28) = 0;
        }
        lVar2 = Aska::SoundMemory::Malloc(unsigned long)(0x2f8);
        *(long *)(param_1 + 0x28) = lVar2;
        lVar3 = 0;
        if (lVar2 != 0) {
          memset(lVar2,0,0x98);
          memset(*(long *)(param_1 + 0x28) + 0x98,0,0x98);
          memset(*(long *)(param_1 + 0x28) + 0x130,0,0x98);
          memset(*(long *)(param_1 + 0x28) + 0x1c8,0,0x98);
          memset(*(long *)(param_1 + 0x28) + 0x260,0,0x98);
          lVar3 = *(long *)(param_1 + 0x28);
        }
        if (lVar3 == 0) {
          *(undefined4 *)(param_1 + 0x20) = 0;
          uVar1 = 0;
        }
        else {
          uVar1 = 1;
          *(undefined4 *)(param_1 + 0x20) = 5;
          *(undefined8 *)(param_1 + 0x18) = 1;
        }
      }
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

// ==== Aska::AudioEffector::FinishEffector()
// vaddr 0x2241004 | ghidra 0x2341004 | size 576 | symbol _ZN4Aska13AudioEffector14FinishEffectorEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska13AudioEffector14FinishEffectorEv(long param_1)

{
  long lVar1;
  long *plVar2;
  
  lVar1 = *(long *)(param_1 + 8);
  if (lVar1 != 0) {
    plVar2 = *(long **)(lVar1 + 0x30);
    if (plVar2 != (long *)0x0) {
      Aska::SubBusSL::UnassignDspEffect(int)(lVar1,0);
      (**(code **)(*plVar2 + 0x20))(plVar2);
      (**(code **)(*plVar2 + 8))(plVar2);
      lVar1 = *(long *)(param_1 + 8);
      if (lVar1 == 0) goto code_r0x023411d4;
    }
    plVar2 = *(long **)(lVar1 + 0x38);
    if (plVar2 != (long *)0x0) {
      Aska::SubBusSL::UnassignDspEffect(int)(lVar1,1);
      (**(code **)(*plVar2 + 0x20))(plVar2);
      (**(code **)(*plVar2 + 8))(plVar2);
      lVar1 = *(long *)(param_1 + 8);
      if (lVar1 == 0) goto code_r0x023411d4;
    }
    plVar2 = *(long **)(lVar1 + 0x40);
    if (plVar2 != (long *)0x0) {
      Aska::SubBusSL::UnassignDspEffect(int)(lVar1,2);
      (**(code **)(*plVar2 + 0x20))(plVar2);
      (**(code **)(*plVar2 + 8))(plVar2);
      lVar1 = *(long *)(param_1 + 8);
      if (lVar1 == 0) goto code_r0x023411d4;
    }
    plVar2 = *(long **)(lVar1 + 0x48);
    if (plVar2 != (long *)0x0) {
      Aska::SubBusSL::UnassignDspEffect(int)(lVar1,3);
      (**(code **)(*plVar2 + 0x20))(plVar2);
      (**(code **)(*plVar2 + 8))(plVar2);
      lVar1 = *(long *)(param_1 + 8);
      if (lVar1 == 0) goto code_r0x023411d4;
    }
    plVar2 = *(long **)(lVar1 + 0x50);
    if (plVar2 != (long *)0x0) {
      Aska::SubBusSL::UnassignDspEffect(int)(lVar1,4);
      (**(code **)(*plVar2 + 0x20))(plVar2);
      (**(code **)(*plVar2 + 8))(plVar2);
      lVar1 = *(long *)(param_1 + 8);
      if (lVar1 == 0) goto code_r0x023411d4;
    }
    plVar2 = *(long **)(lVar1 + 0x58);
    if (plVar2 != (long *)0x0) {
      Aska::SubBusSL::UnassignDspEffect(int)(lVar1,5);
      (**(code **)(*plVar2 + 0x20))(plVar2);
      (**(code **)(*plVar2 + 8))(plVar2);
      lVar1 = *(long *)(param_1 + 8);
      if (lVar1 == 0) goto code_r0x023411d4;
    }
    plVar2 = *(long **)(lVar1 + 0x60);
    if (plVar2 != (long *)0x0) {
      Aska::SubBusSL::UnassignDspEffect(int)(lVar1,6);
      (**(code **)(*plVar2 + 0x20))(plVar2);
      (**(code **)(*plVar2 + 8))(plVar2);
      lVar1 = *(long *)(param_1 + 8);
      if (lVar1 == 0) goto code_r0x023411d4;
    }
    plVar2 = *(long **)(lVar1 + 0x68);
    if (plVar2 != (long *)0x0) {
      Aska::SubBusSL::UnassignDspEffect(int)(lVar1,7);
      (**(code **)(*plVar2 + 0x20))(plVar2);
      (**(code **)(*plVar2 + 8))(plVar2);
      lVar1 = *(long *)(param_1 + 8);
    }
  }
code_r0x023411d4:
  if (*(long *)(lVar1 + 0x20) != 0) {
    Aska::SubBusSL::DisconnectRouting(int)(lVar1,0);
    lVar1 = *(long *)(param_1 + 8);
  }
  if (*(long *)(lVar1 + 0x28) != 0) {
    Aska::SubBusSL::DisconnectRouting(int)(lVar1,1);
    lVar1 = *(long *)(param_1 + 8);
  }
  if (lVar1 != 0) {
    Aska::SubBusSL::FinishBus()();
    if (*(long **)(param_1 + 8) != (long *)0x0) {
      (**(code **)(**(long **)(param_1 + 8) + 8))();
    }
    *(undefined8 *)(param_1 + 8) = 0;
  }
  *(undefined8 *)(param_1 + 0x18) = 1;
  *(undefined4 *)(param_1 + 0x20) = 0;
  if (*(long *)(param_1 + 0x28) != 0) {
    operator delete[](void*)();
    *(undefined8 *)(param_1 + 0x28) = 0;
  }
  return;
}

// ==== Aska::AudioEffector::UninstallDspEffect(unsigned int)
// vaddr 0x2241244 | ghidra 0x2341244 | size 72 | symbol _ZN4Aska13AudioEffector18UninstallDspEffectEj | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska13AudioEffector18UninstallDspEffectEj(long param_1,int param_2)

{
  long *plVar1;
  
  if (*(long *)(param_1 + 8) != 0) {
    plVar1 = *(long **)(*(long *)(param_1 + 8) + (long)param_2 * 8 + 0x30);
    if (plVar1 != (long *)0x0) {
      Aska::SubBusSL::UnassignDspEffect(int)();
      (**(code **)(*plVar1 + 0x20))(plVar1);
                    /* WARNING: Could not recover jumptable at 0x02341280. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (**(code **)(*plVar1 + 8))(plVar1);
      return;
    }
  }
  return;
}

// ==== Aska::AudioEffector::DisconnectBus(int)
// vaddr 0x224128c | ghidra 0x234128c | size 112 | symbol _ZN4Aska13AudioEffector13DisconnectBusEi | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Possible PIC construction at 0x023412bc: Changing call to branch */
/* WARNING: Removing unreachable block (ram,0x023412c0) */

ulong _ZN4Aska13AudioEffector13DisconnectBusEi(long param_1,undefined8 param_2)

{
  uint uVar1;
  ulong uVar2;
  long lVar3;
  
  lVar3 = *(long *)(param_1 + 8);
  if ((int)param_2 == -1) {
    if (*(long *)(lVar3 + 0x20) == 0) {
      uVar1 = 1;
      if (*(long *)(lVar3 + 0x28) != 0) {
        uVar1 = Aska::SubBusSL::DisconnectRouting(int)(lVar3,1);
        uVar1 = uVar1 & 1;
      }
      return (ulong)uVar1;
    }
    param_2 = 0;
  }
  uVar2 = (*(code *)PTR__ZN4Aska8SubBusSL17DisconnectRoutingEi_02cb43d8)(lVar3,param_2);
  return uVar2;
}

// ==== Aska::AudioEffector::ConnectBus(int, Aska::IBus*)
// vaddr 0x22412fc | ghidra 0x23412fc | size 100 | symbol _ZN4Aska13AudioEffector10ConnectBusEiPNS_4IBusE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska13AudioEffector10ConnectBusEiPNS_4IBusE(long param_1,int param_2,undefined8 param_3)

{
  long lVar1;
  int iVar2;
  
  lVar1 = *(long *)(param_1 + 8);
  iVar2 = param_2;
  if (param_2 == -1) {
    if (*(long *)(lVar1 + 0x20) != 0) {
      Aska::SubBusSL::DisconnectRouting(int)(lVar1,0);
      lVar1 = *(long *)(param_1 + 8);
    }
    if (*(long *)(lVar1 + 0x28) == 0) goto code_r0x011c5610;
    iVar2 = 1;
  }
  Aska::SubBusSL::DisconnectRouting(int)(lVar1,iVar2);
code_r0x011c5610:
  (*(code *)PTR__ZN4Aska8SubBusSL14ConnectRoutingEiPNS_4IBusE_02c9aaf8)
            (*(undefined8 *)(param_1 + 8),param_2,param_3);
  return;
}

// ==== Aska::AudioEffector::InstallDspEffect(unsigned int, Aska::ESound::EDspEffect, void const*)
// vaddr 0x2241360 | ghidra 0x2341360 | size 72 | symbol _ZN4Aska13AudioEffector16InstallDspEffectEjNS_6ESound10EDspEffectEPKv | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska13AudioEffector16InstallDspEffectEjNS_6ESound10EDspEffectEPKv(long param_1,int param_2)

{
  long *plVar1;
  
  if (*(long *)(param_1 + 8) != 0) {
    plVar1 = *(long **)(*(long *)(param_1 + 8) + (long)param_2 * 8 + 0x30);
    if (plVar1 != (long *)0x0) {
      Aska::SubBusSL::UnassignDspEffect(int)();
      (**(code **)(*plVar1 + 0x20))(plVar1);
      (**(code **)(*plVar1 + 8))(plVar1);
    }
  }
  return 1;
}

// ==== Aska::AudioEffector::AudioRun()
// vaddr 0x22413a8 | ghidra 0x23413a8 | size 456 | symbol _ZN4Aska13AudioEffector8AudioRunEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska13AudioEffector8AudioRunEv(long *param_1)

{
  long *plVar1;
  int *piVar2;
  long *plVar3;
  uint uVar4;
  char cVar5;
  bool bVar6;
  ulong uVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  undefined1 auStack_d8 [152];
  
  uVar8 = *(uint *)(param_1 + 3);
  if (uVar8 <= *(uint *)((long)param_1 + 0x1c)) {
    uVar8 = (int)param_1[4] + uVar8;
  }
  iVar10 = uVar8 + ~*(uint *)((long)param_1 + 0x1c);
  if (iVar10 < 1) {
    return;
  }
  plVar1 = param_1 + 0xd;
  piVar2 = (int *)((long)param_1 + 0x6c);
  plVar3 = param_1 + 0x15;
  do {
    memset(auStack_d8,0,0x98);
    iVar9 = 0;
    do {
      while ((int)*plVar1 == -1) {
        cVar5 = '\x01';
        bVar6 = (bool)ExclusiveMonitorPass(plVar1,0x10);
        if (bVar6) {
          *(int *)plVar1 = 0;
          cVar5 = ExclusiveMonitorsStatus();
        }
        if (cVar5 == '\0') goto code_r0x023414c4;
      }
      ClearExclusiveLocal();
      bVar6 = iVar9 < 0x1ff;
      iVar9 = iVar9 + 1;
    } while (bVar6);
    do {
      cVar5 = '\x01';
      bVar6 = (bool)ExclusiveMonitorPass(piVar2,0x10);
      if (bVar6) {
        *piVar2 = *piVar2 + 1;
        cVar5 = ExclusiveMonitorsStatus();
      }
    } while (cVar5 != '\0');
    do {
      if ((int)*plVar1 != -1) {
        do {
          ClearExclusiveLocal();
          uVar7 = Aska::Semaphore::IsReady() const(plVar3);
          if ((uVar7 & 1) == 0) {
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
            Aska::Semaphore::Wait() const(plVar3);
          }
          do {
            cVar5 = '\x01';
            bVar6 = (bool)ExclusiveMonitorPass(piVar2,0x10);
            if (bVar6) {
              *piVar2 = *piVar2 + 1;
              cVar5 = ExclusiveMonitorsStatus();
            }
          } while (cVar5 != '\0');
          while ((int)*plVar1 == -1) {
            cVar5 = '\x01';
            bVar6 = (bool)ExclusiveMonitorPass(plVar1,0x10);
            if (bVar6) {
              *(int *)plVar1 = 0;
              cVar5 = ExclusiveMonitorsStatus();
            }
            if (cVar5 == '\0') goto code_r0x023414b4;
          }
        } while( true );
      }
      cVar5 = '\x01';
      bVar6 = (bool)ExclusiveMonitorPass(plVar1,0x10);
      if (bVar6) {
        *(int *)plVar1 = 0;
        cVar5 = ExclusiveMonitorsStatus();
      }
    } while (cVar5 != '\0');
code_r0x023414b4:
    do {
      cVar5 = '\x01';
      bVar6 = (bool)ExclusiveMonitorPass(piVar2,0x10);
      if (bVar6) {
        *piVar2 = *piVar2 + -1;
        cVar5 = ExclusiveMonitorsStatus();
      }
    } while (cVar5 != '\0');
code_r0x023414c4:
    DataMemoryBarrier(2,3);
    uVar4 = *(uint *)((long)param_1 + 0x1c);
    uVar8 = 0;
    if (uVar4 + 1 < *(uint *)(param_1 + 4)) {
      uVar8 = uVar4 + 1;
    }
    if (uVar8 != *(uint *)(param_1 + 3)) {
      *(uint *)((long)param_1 + 0x1c) = uVar8;
      uVar4 = uVar8;
    }
    memcpy(auStack_d8,param_1[5] + (ulong)uVar4 * 0x98,0x98);
    DataMemoryBarrier(2,3);
    *(undefined4 *)(param_1 + 0xd) = 0xffffffff;
    DataMemoryBarrier(2,3);
    if (0x14 < *(int *)((long)param_1 + 0x6c)) {
      do {
        cVar5 = '\x01';
        bVar6 = (bool)ExclusiveMonitorPass(piVar2,0x10);
        if (bVar6) {
          *piVar2 = *piVar2 + -1;
          cVar5 = ExclusiveMonitorsStatus();
        }
      } while (cVar5 != '\0');
      uVar7 = Aska::Semaphore::IsReady() const(plVar3);
      if ((uVar7 & 1) != 0) {
        Aska::Semaphore::Signal() const(plVar3);
      }
    }
    (**(code **)(*param_1 + 0x38))(param_1,auStack_d8);
    iVar9 = iVar10 + -1;
    bVar6 = iVar10 < 1;
    iVar10 = iVar9;
    if (iVar9 == 0 || bVar6) {
      return;
    }
  } while( true );
}

// ==== Aska::AudioEffector::ProcRequest(Aska::EffectorRequest::RequestContainer const*)
// vaddr 0x2241570 | ghidra 0x2341570 | size 152 | symbol _ZN4Aska13AudioEffector11ProcRequestEPKNS_15EffectorRequest16RequestContainerE | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska13AudioEffector11ProcRequestEPKNS_15EffectorRequest16RequestContainerE
          (long param_1,int *param_2)

{
  int iVar1;
  long lVar2;
  
  iVar1 = *param_2;
  if (iVar1 == 3) {
    if ((*(long *)(param_1 + 8) != 0) &&
       (*(long *)(*(long *)(param_1 + 8) + (long)param_2[4] * 8 + 0x30) != 0)) {
      return 1;
    }
  }
  else {
    if (iVar1 != 2) {
      if (iVar1 == 1) {
        *(int *)(*(long *)(param_1 + 8) + 0x78) = param_2[1];
        return 1;
      }
      return 0;
    }
    lVar2 = *(long *)(param_1 + 8);
    if ((lVar2 != 0) && (*(long *)(lVar2 + (long)param_2[4] * 8 + 0x30) != 0)) {
      *(undefined1 *)(lVar2 + (ulong)(uint)param_2[4] + 0x80) = *(undefined1 *)((long)param_2 + 0xd)
      ;
      return 1;
    }
  }
  Aska::EffectorRequest::RequestSet(Aska::EffectorRequest::RequestContainer const*)(param_1 + 0x10);
  return 1;
}

// ==== Aska::AudioEffector::SetDspEffectParameterImmediately(unsigned int, void const*)
// vaddr 0x2241770 | ghidra 0x2341770 | size 4 | symbol _ZN4Aska13AudioEffector32SetDspEffectParameterImmediatelyEjPKv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska13AudioEffector32SetDspEffectParameterImmediatelyEjPKv(void)

{
  return;
}

// ==== Aska::AudioEffector::CheckSubBusMatch(Aska::IDspEffect*) const
// vaddr 0x2241774 | ghidra 0x2341774 | size 112 | symbol _ZNK4Aska13AudioEffector16CheckSubBusMatchEPNS_10IDspEffectE | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK4Aska13AudioEffector16CheckSubBusMatchEPNS_10IDspEffectE(long param_1,long *param_2)

{
  int iVar1;
  int iVar2;
  undefined8 uVar3;
  
  if (((*(int *)(*(long *)(param_1 + 8) + 8) == 2) ||
      (iVar1 = (**(code **)(*param_2 + 0x38))(param_2), iVar1 == 2)) ||
     (iVar1 = *(int *)(*(long *)(param_1 + 8) + 8), iVar2 = (**(code **)(*param_2 + 0x38))(param_2),
     iVar1 == iVar2)) {
    uVar3 = 1;
  }
  else {
    uVar3 = 0;
  }
  return uVar3;
}

// ==== Aska::AudioEffector::Get(unsigned long, void*) const
// vaddr 0x22417e4 | ghidra 0x23417e4 | size 516 | symbol _ZNK4Aska13AudioEffector3GetEmPv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK4Aska13AudioEffector3GetEmPv(long param_1,ulong param_2,undefined4 *param_3)

{
  uint uVar1;
  undefined4 uVar2;
  long *plVar3;
  long lVar4;
  long lVar5;
  
  if ((param_2 & 0xffff00000000) != 0) {
    return 0;
  }
  lVar5 = *(long *)(param_1 + 8);
  if (lVar5 == 0) {
    return 0;
  }
  if (0x16 < ((uint)param_2 & 0xffff)) {
    return 0;
  }
  uVar1 = (uint)(param_2 >> 0x10) & 0xffff;
  switch(param_2 & 0xffff) {
  case 0:
    uVar2 = *(undefined4 *)(lVar5 + 8);
    break;
  case 1:
    uVar2 = *(undefined4 *)(lVar5 + 0xc);
    break;
  case 2:
    uVar2 = *(undefined4 *)(lVar5 + 0x10);
    break;
  case 3:
    uVar2 = *(undefined4 *)(lVar5 + 0x78);
    break;
  default:
    return 0;
  case 0x14:
    if ((((((param_2 & 0xffff0000) != 0) ||
          (plVar3 = *(long **)(lVar5 + 0x30), plVar3 == (long *)0x0)) &&
         ((uVar1 != 1 || (plVar3 = *(long **)(lVar5 + 0x38), plVar3 == (long *)0x0)))) &&
        ((uVar1 != 2 || (plVar3 = *(long **)(lVar5 + 0x40), plVar3 == (long *)0x0)))) &&
       (((uVar1 != 3 || (plVar3 = *(long **)(lVar5 + 0x48), plVar3 == (long *)0x0)) &&
        ((((uVar1 != 4 || (plVar3 = *(long **)(lVar5 + 0x50), plVar3 == (long *)0x0)) &&
          ((uVar1 != 5 || (plVar3 = *(long **)(lVar5 + 0x58), plVar3 == (long *)0x0)))) &&
         ((uVar1 != 6 || (plVar3 = *(long **)(lVar5 + 0x60), plVar3 == (long *)0x0)))))))) {
      if (uVar1 != 7) {
        return 0;
      }
      plVar3 = *(long **)(lVar5 + 0x68);
      if (plVar3 == (long *)0x0) {
        return 0;
      }
    }
    uVar2 = (**(code **)(*plVar3 + 0x10))(plVar3);
    *param_3 = uVar2;
    return 1;
  case 0x16:
    if (((param_2 & 0xffff0000) == 0) && (*(long *)(lVar5 + 0x30) != 0)) {
      lVar4 = 0;
    }
    else if ((uVar1 == 1) && (*(long *)(lVar5 + 0x38) != 0)) {
      lVar4 = 1;
    }
    else if ((uVar1 == 2) && (*(long *)(lVar5 + 0x40) != 0)) {
      lVar4 = 2;
    }
    else if ((uVar1 == 3) && (*(long *)(lVar5 + 0x48) != 0)) {
      lVar4 = 3;
    }
    else if ((uVar1 == 4) && (*(long *)(lVar5 + 0x50) != 0)) {
      lVar4 = 4;
    }
    else if ((uVar1 == 5) && (*(long *)(lVar5 + 0x58) != 0)) {
      lVar4 = 5;
    }
    else if ((uVar1 == 6) && (*(long *)(lVar5 + 0x60) != 0)) {
      lVar4 = 6;
    }
    else {
      if (uVar1 != 7) {
        return 0;
      }
      if (*(long *)(lVar5 + 0x68) == 0) {
        return 0;
      }
      lVar4 = 7;
    }
    *(undefined1 *)param_3 = *(undefined1 *)(lVar5 + lVar4 + 0x80);
    return 1;
  }
  *param_3 = uVar2;
  return 1;
}

// ==== Aska::AudioEffector::Set(unsigned long, void const*)
// vaddr 0x22419e8 | ghidra 0x23419e8 | size 336 | symbol _ZN4Aska13AudioEffector3SetEmPKv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska13AudioEffector3SetEmPKv(long param_1,undefined8 param_2,undefined4 *param_3)

{
  uint uVar1;
  undefined8 uVar2;
  long lVar3;
  
  if ((short)((ulong)param_2 >> 0x20) != 0) {
    return 0;
  }
  lVar3 = *(long *)(param_1 + 8);
  if (lVar3 == 0) {
    return 0;
  }
  uVar1 = (uint)param_2 & 0xffff;
  if (uVar1 == 3) {
    uVar2 = 1;
    *(undefined4 *)(lVar3 + 0x78) = *param_3;
  }
  else {
    if (uVar1 != 0x16) {
      return 0;
    }
    uVar1 = (uint)param_2 >> 0x10;
    if ((*(long *)(lVar3 + 0x30) != 0) && (uVar1 == 0)) {
      *(undefined1 *)(lVar3 + 0x80) = *(undefined1 *)param_3;
      return 0;
    }
    if ((*(long *)(lVar3 + 0x38) != 0) && (uVar1 == 1)) {
      *(undefined1 *)(lVar3 + 0x81) = *(undefined1 *)param_3;
      return 0;
    }
    if ((*(long *)(lVar3 + 0x40) != 0) && (uVar1 == 2)) {
      *(undefined1 *)(lVar3 + 0x82) = *(undefined1 *)param_3;
      return 0;
    }
    if ((*(long *)(lVar3 + 0x48) != 0) && (uVar1 == 3)) {
      *(undefined1 *)(lVar3 + 0x83) = *(undefined1 *)param_3;
      return 0;
    }
    if ((*(long *)(lVar3 + 0x50) != 0) && (uVar1 == 4)) {
      *(undefined1 *)(lVar3 + 0x84) = *(undefined1 *)param_3;
      return 0;
    }
    if ((*(long *)(lVar3 + 0x58) != 0) && (uVar1 == 5)) {
      *(undefined1 *)(lVar3 + 0x85) = *(undefined1 *)param_3;
      return 0;
    }
    if ((*(long *)(lVar3 + 0x60) != 0) && (uVar1 == 6)) {
      *(undefined1 *)(lVar3 + 0x86) = *(undefined1 *)param_3;
      return 0;
    }
    uVar2 = 0;
    if ((*(long *)(lVar3 + 0x68) != 0) && (uVar1 == 7)) {
      *(undefined1 *)(lVar3 + 0x87) = *(undefined1 *)param_3;
      return 0;
    }
  }
  return uVar2;
}

// ==== Aska::AudioEffector::~AudioEffector()
// vaddr 0x22424f0 | ghidra 0x23424f0 | size 120 | symbol _ZN4Aska13AudioEffectorD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska13AudioEffectorD0Ev(long *param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZTVN4Aska13AudioEffectorE_02cc4a78;
  *(undefined4 *)(param_1 + 4) = 0;
  *param_1 = (long)(puVar1 + 0x10);
  param_1[3] = 1;
  if (param_1[5] != 0) {
    operator delete[](void*)();
    param_1[5] = 0;
  }
  Aska::FastCriticalSection::~FastCriticalSection()(param_1 + 6);
  puVar1 = PTR__ZTVN4Aska13TDynamicQueueINS_15EffectorRequest16RequestContainerELb1EEE_02cb7d20;
  *(undefined4 *)(param_1 + 4) = 0;
  param_1[2] = (long)(puVar1 + 0x10);
  param_1[3] = 1;
  if (param_1[5] != 0) {
    operator delete[](void*)();
    param_1[5] = 0;
  }
  Aska::IAnimatable::~IAnimatable()(param_1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::AudioEffector::GetClassID(int) const
// vaddr 0x2242568 | ghidra 0x2342568 | size 24 | symbol _ZNK4Aska13AudioEffector10GetClassIDEi | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK4Aska13AudioEffector10GetClassIDEi(undefined8 param_1,int param_2)

{
  undefined8 uVar1;
  
  uVar1 = 0xf000f21a;
  if (param_2 != 0) {
    uVar1 = 0xf000;
  }
  return uVar1;
}

// ==== Aska::AudioInterface::CheckConnectable(Aska::AudioConnector const*, Aska::AudioConnector const*)
// vaddr 0x2242840 | ghidra 0x2342840 | size 124 | symbol _ZN4Aska14AudioInterface16CheckConnectableEPKNS_14AudioConnectorES3_ | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska14AudioInterface16CheckConnectableEPKNS_14AudioConnectorES3_
          (undefined8 param_1,uint *param_2,long param_3)

{
  byte bVar1;
  uint uVar2;
  
  if (param_3 != 0) {
    bVar1 = *(byte *)(param_3 + 3);
    uVar2 = *param_2 >> 0x18;
    if (uVar2 == 3) {
      if (bVar1 != 1) {
        return 0;
      }
    }
    else if (uVar2 == 2) {
      if (bVar1 != 1) {
        return 0;
      }
    }
    else if (uVar2 == 1) {
      if ((bVar1 & 0xfe) != 2) {
        return 0;
      }
    }
    else if ((uVar2 == 4) && (bVar1 != 4)) {
      return 0;
    }
  }
  return 1;
}

// ==== Aska::AudioInterface::AudioInterface()
// vaddr 0x22428bc | ghidra 0x23428bc | size 28 | symbol _ZN4Aska14AudioInterfaceC2Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska14AudioInterfaceC1Ev(long *param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZTVN4Aska14AudioInterfaceE_02cb7330;
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[2] = 0;
  *param_1 = (long)(puVar1 + 0x10);
  param_1[1] = 0;
  return;
}

// ==== Aska::AudioInterface::Connect(Aska::AudioConnector*)
// vaddr 0x22428d8 | ghidra 0x23428d8 | size 284 | symbol _ZN4Aska14AudioInterface7ConnectEPNS_14AudioConnectorE | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska14AudioInterface7ConnectEPNS_14AudioConnectorE(long param_1,uint *param_2)

{
  long lVar1;
  byte bVar2;
  uint uVar3;
  
  if (param_2 == (uint *)0x0) {
    return 0;
  }
  lVar1 = *(long *)(param_1 + 0x20);
  if (*(long *)(param_1 + 0x18) == 0) {
    if (lVar1 != 0) {
      bVar2 = *(byte *)(lVar1 + 3);
      uVar3 = *param_2 >> 0x18;
      if (uVar3 == 3) {
        if (bVar2 != 1) {
          return 0;
        }
      }
      else if (uVar3 == 2) {
        if (bVar2 != 1) {
          return 0;
        }
      }
      else if (uVar3 == 1) {
        if ((bVar2 & 0xfe) != 2) {
          return 0;
        }
      }
      else if ((uVar3 == 4) && (bVar2 != 4)) {
        return 0;
      }
    }
    *(uint **)(param_1 + 0x18) = param_2;
  }
  else {
    if (lVar1 != 0) {
      return 0;
    }
    bVar2 = *(byte *)(*(long *)(param_1 + 0x18) + 3);
    uVar3 = *param_2 >> 0x18;
    if (uVar3 == 3) {
      if (bVar2 != 1) {
        return 0;
      }
    }
    else if (uVar3 == 2) {
      if (bVar2 != 1) {
        return 0;
      }
    }
    else if (uVar3 == 1) {
      if ((bVar2 & 0xfe) != 2) {
        return 0;
      }
    }
    else if ((uVar3 == 4) && (bVar2 != 4)) {
      return 0;
    }
    *(uint **)(param_1 + 0x20) = param_2;
  }
  *(long *)(param_2 + 4) = param_1;
  return 1;
}

// ==== Aska::AudioInterface::Disconnect(Aska::AudioConnector*)
// vaddr 0x22429f4 | ghidra 0x23429f4 | size 76 | symbol _ZN4Aska14AudioInterface10DisconnectEPNS_14AudioConnectorE | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska14AudioInterface10DisconnectEPNS_14AudioConnectorE(long param_1,long param_2)

{
  if (param_2 == 0) {
    return 0;
  }
  if (*(long *)(param_1 + 0x18) != param_2) {
    if (*(long *)(param_1 + 0x20) != param_2) {
      return 0;
    }
    *(undefined8 *)(param_2 + 0x10) = 0;
    *(undefined8 *)(param_1 + 0x20) = 0;
    return 1;
  }
  *(undefined8 *)(param_2 + 0x10) = 0;
  *(undefined8 *)(param_1 + 0x18) = 0;
  return 1;
}

// ==== Aska::AudioInterface::GetThisConnector(Aska::IAudioDevice*)
// vaddr 0x2242a40 | ghidra 0x2342a40 | size 52 | symbol _ZN4Aska14AudioInterface16GetThisConnectorEPNS_12IAudioDeviceE | lib libSOA-3.7.0.so | 2026-10-08
long _ZN4Aska14AudioInterface16GetThisConnectorEPNS_12IAudioDeviceE(long param_1,long param_2)

{
  long lVar1;
  
  lVar1 = *(long *)(param_1 + 0x18);
  if (((lVar1 == 0) || (*(long *)(lVar1 + 8) != param_2)) &&
     ((lVar1 = *(long *)(param_1 + 0x20), lVar1 == 0 || (*(long *)(lVar1 + 8) != param_2)))) {
    lVar1 = 0;
  }
  return lVar1;
}

// ==== Aska::AudioInterface::GetAnotherConnector(Aska::IAudioDevice*)
// vaddr 0x2242a74 | ghidra 0x2342a74 | size 60 | symbol _ZN4Aska14AudioInterface19GetAnotherConnectorEPNS_12IAudioDeviceE | lib libSOA-3.7.0.so | 2026-10-08
long _ZN4Aska14AudioInterface19GetAnotherConnectorEPNS_12IAudioDeviceE(long param_1,long param_2)

{
  long lVar1;
  
  lVar1 = *(long *)(param_1 + 0x18);
  if ((lVar1 != 0) && (*(long *)(lVar1 + 8) == param_2)) {
    return *(long *)(param_1 + 0x20);
  }
  if (*(long *)(param_1 + 0x20) != 0) {
    if (*(long *)(*(long *)(param_1 + 0x20) + 8) != param_2) {
      lVar1 = 0;
    }
    return lVar1;
  }
  return 0;
}

// ==== Aska::AudioInterface::GetAnotherConnector(Aska::AudioConnector*)
// vaddr 0x2242ab0 | ghidra 0x2342ab0 | size 24 | symbol _ZN4Aska14AudioInterface19GetAnotherConnectorEPNS_14AudioConnectorE | lib libSOA-3.7.0.so | 2026-10-08
long _ZN4Aska14AudioInterface19GetAnotherConnectorEPNS_14AudioConnectorE(long param_1,long param_2)

{
  long lVar1;
  long lVar2;
  
  lVar1 = *(long *)(param_1 + 0x18);
  if (*(long *)(param_1 + 0x20) != param_2) {
    lVar1 = 0;
  }
  lVar2 = *(long *)(param_1 + 0x20);
  if (*(long *)(param_1 + 0x18) != param_2) {
    lVar2 = lVar1;
  }
  return lVar2;
}

// ==== Aska::AudioInterface::~AudioInterface()
// vaddr 0x2242ac8 | ghidra 0x2342ac8 | size 4 | symbol _ZN4Aska14AudioInterfaceD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska14AudioInterfaceD0Ev(void)

{
  (*(code *)PTR__ZdlPv_02ca4758)();
  return;
}

// ==== Aska::AudioMixer::AudioMixer()
// vaddr 0x2242b70 | ghidra 0x2342b70 | size 1808 | symbol _ZN4Aska10AudioMixerC1Ev | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska10AudioMixerC2Ev(long *param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  long lVar3;
  long lVar4;
  undefined *puVar5;
  
  Aska::IAudioDevice::IAudioDevice()();
  puVar5 = PTR__ZTVN4Aska11MasterBusSLE_02cc4308;
  puVar1 = PTR__ZTVN4Aska10AudioMixerE_02cbab18;
  *(undefined4 *)(param_1 + 8) = 0;
  param_1[7] = 0;
  puVar2 = PTR__ZTVN4Aska12MixerChannelE_02cbe548;
  lVar4 = _UNK_0285f1f8;
  lVar3 = _UNK_0285f1f0;
  *param_1 = (long)(puVar1 + 0x10);
  param_1[4] = (long)(puVar5 + 0x10);
  puVar1 = PTR__ZTVN4Aska10BusChannelE_02cc1238 + 0x10;
  *(undefined4 *)(param_1 + 0xb) = 0xffffffff;
  *(undefined4 *)(param_1 + 0xe) = 0xffffffff;
  param_1[9] = (long)(puVar2 + 0x10);
  param_1[10] = 0;
  param_1[0xc] = (long)puVar1;
  param_1[0xd] = 0;
  param_1[6] = lVar4;
  param_1[5] = lVar3;
  Aska::AudioEffector::AudioEffector()(param_1 + 0xf);
  puVar2 = PTR__ZTVN4Aska17InsertionEffectorE_02cc1378;
  param_1[0x27] = (long)puVar1;
  param_1[0x28] = 0;
  *(undefined4 *)(param_1 + 0x29) = 0xffffffff;
  puVar2 = puVar2 + 0x10;
  param_1[0xf] = (long)puVar2;
  Aska::AudioEffector::AudioEffector()(param_1 + 0x2a);
  param_1[0x2a] = (long)puVar2;
  param_1[0x43] = 0;
  *(undefined4 *)(param_1 + 0x44) = 0xffffffff;
  param_1[0x42] = (long)puVar1;
  Aska::AudioEffector::AudioEffector()(param_1 + 0x45);
  param_1[0x45] = (long)puVar2;
  param_1[0x5e] = 0;
  *(undefined4 *)(param_1 + 0x5f) = 0xffffffff;
  param_1[0x5d] = (long)puVar1;
  Aska::AudioEffector::AudioEffector()(param_1 + 0x60);
  param_1[0x60] = (long)puVar2;
  *(undefined4 *)(param_1 + 0x78) = 0;
  *(undefined4 *)(param_1 + 0x7b) = 0;
  param_1[0x7a] = 0;
  param_1[0x79] = 0;
  *(undefined4 *)(param_1 + 0x7e) = 0;
  param_1[0x7c] = 0;
  param_1[0x7d] = 0;
  *(undefined4 *)(param_1 + 0x81) = 0;
  param_1[0x80] = 0;
  param_1[0x7f] = 0;
  *(undefined4 *)(param_1 + 0x84) = 0;
  param_1[0x83] = 0;
  param_1[0x82] = 0;
  *(undefined4 *)(param_1 + 0x87) = 0;
  param_1[0x85] = 0;
  param_1[0x86] = 0;
  *(undefined4 *)(param_1 + 0x8a) = 0;
  param_1[0x88] = 0;
  param_1[0x89] = 0;
  *(undefined4 *)(param_1 + 0x8d) = 0;
  param_1[0x8b] = 0;
  param_1[0x8c] = 0;
  *(undefined4 *)(param_1 + 0x90) = 0;
  param_1[0x8e] = 0;
  param_1[0x8f] = 0;
  *(undefined4 *)(param_1 + 0x93) = 0;
  param_1[0x91] = 0;
  param_1[0x92] = 0;
  *(undefined4 *)(param_1 + 0x96) = 0;
  param_1[0x94] = 0;
  param_1[0x95] = 0;
  *(undefined4 *)(param_1 + 0x99) = 0;
  param_1[0x97] = 0;
  param_1[0x98] = 0;
  *(undefined4 *)(param_1 + 0x9c) = 0;
  param_1[0x9a] = 0;
  param_1[0x9b] = 0;
  *(undefined4 *)(param_1 + 0x9f) = 0;
  param_1[0x9d] = 0;
  param_1[0x9e] = 0;
  *(undefined4 *)(param_1 + 0xa2) = 0;
  param_1[0xa0] = 0;
  param_1[0xa1] = 0;
  *(undefined4 *)(param_1 + 0xa5) = 0;
  param_1[0xa3] = 0;
  param_1[0xa4] = 0;
  *(undefined4 *)(param_1 + 0xa8) = 0;
  param_1[0xa6] = 0;
  param_1[0xa7] = 0;
  *(undefined4 *)(param_1 + 0xab) = 0;
  param_1[0xa9] = 0;
  param_1[0xaa] = 0;
  *(undefined4 *)(param_1 + 0xae) = 0;
  param_1[0xac] = 0;
  param_1[0xad] = 0;
  *(undefined4 *)(param_1 + 0xb1) = 0;
  param_1[0xaf] = 0;
  param_1[0xb0] = 0;
  *(undefined4 *)(param_1 + 0xb4) = 0;
  param_1[0xb2] = 0;
  param_1[0xb3] = 0;
  *(undefined4 *)(param_1 + 0xb7) = 0;
  param_1[0xb5] = 0;
  param_1[0xb6] = 0;
  *(undefined4 *)(param_1 + 0xba) = 0;
  param_1[0xb8] = 0;
  param_1[0xb9] = 0;
  *(undefined4 *)(param_1 + 0xbd) = 0;
  param_1[0xbb] = 0;
  param_1[0xbc] = 0;
  *(undefined4 *)(param_1 + 0xc0) = 0;
  param_1[0xbe] = 0;
  param_1[0xbf] = 0;
  *(undefined4 *)(param_1 + 0xc3) = 0;
  param_1[0xc1] = 0;
  param_1[0xc2] = 0;
  *(undefined4 *)(param_1 + 0xc6) = 0;
  param_1[0xc4] = 0;
  param_1[0xc5] = 0;
  *(undefined4 *)(param_1 + 0xc9) = 0;
  param_1[199] = 0;
  param_1[200] = 0;
  *(undefined4 *)(param_1 + 0xcc) = 0;
  param_1[0xca] = 0;
  param_1[0xcb] = 0;
  *(undefined4 *)(param_1 + 0xcf) = 0;
  param_1[0xcd] = 0;
  param_1[0xce] = 0;
  *(undefined4 *)(param_1 + 0xd2) = 0;
  param_1[0xd0] = 0;
  param_1[0xd1] = 0;
  *(undefined4 *)(param_1 + 0xd5) = 0;
  param_1[0xd3] = 0;
  param_1[0xd4] = 0;
  *(undefined4 *)(param_1 + 0xd8) = 0;
  param_1[0xd6] = 0;
  param_1[0xd7] = 0;
  *(undefined4 *)(param_1 + 0xdb) = 0;
  param_1[0xd9] = 0;
  param_1[0xda] = 0;
  *(undefined4 *)(param_1 + 0xde) = 0;
  param_1[0xdc] = 0;
  param_1[0xdd] = 0;
  *(undefined4 *)(param_1 + 0xe1) = 0;
  param_1[0xdf] = 0;
  param_1[0xe0] = 0;
  *(undefined4 *)(param_1 + 0xe4) = 0;
  param_1[0xe2] = 0;
  param_1[0xe3] = 0;
  *(undefined4 *)(param_1 + 0xe7) = 0;
  param_1[0xe5] = 0;
  param_1[0xe6] = 0;
  *(undefined4 *)(param_1 + 0xea) = 0;
  param_1[0xe8] = 0;
  param_1[0xe9] = 0;
  *(undefined4 *)(param_1 + 0xed) = 0;
  param_1[0xeb] = 0;
  param_1[0xec] = 0;
  *(undefined4 *)(param_1 + 0xf0) = 0;
  param_1[0xee] = 0;
  param_1[0xef] = 0;
  *(undefined4 *)(param_1 + 0xf3) = 0;
  param_1[0xf1] = 0;
  param_1[0xf2] = 0;
  *(undefined4 *)(param_1 + 0xf6) = 0;
  param_1[0xf4] = 0;
  param_1[0xf5] = 0;
  *(undefined4 *)(param_1 + 0xf9) = 0;
  param_1[0xf7] = 0;
  param_1[0xf8] = 0;
  *(undefined4 *)(param_1 + 0xfc) = 0;
  param_1[0xfa] = 0;
  param_1[0xfb] = 0;
  *(undefined4 *)(param_1 + 0xff) = 0;
  param_1[0xfd] = 0;
  param_1[0xfe] = 0;
  *(undefined4 *)(param_1 + 0x102) = 0;
  param_1[0x100] = 0;
  param_1[0x101] = 0;
  *(undefined4 *)(param_1 + 0x105) = 0;
  param_1[0x103] = 0;
  param_1[0x104] = 0;
  *(undefined4 *)(param_1 + 0x108) = 0;
  param_1[0x106] = 0;
  param_1[0x107] = 0;
  *(undefined4 *)(param_1 + 0x10b) = 0;
  param_1[0x109] = 0;
  param_1[0x10a] = 0;
  *(undefined4 *)(param_1 + 0x10e) = 0;
  param_1[0x10c] = 0;
  param_1[0x10d] = 0;
  *(undefined4 *)(param_1 + 0x111) = 0;
  param_1[0x10f] = 0;
  param_1[0x110] = 0;
  *(undefined4 *)(param_1 + 0x114) = 0;
  param_1[0x112] = 0;
  param_1[0x113] = 0;
  *(undefined4 *)(param_1 + 0x117) = 0;
  param_1[0x115] = 0;
  param_1[0x116] = 0;
  *(undefined4 *)(param_1 + 0x11a) = 0;
  param_1[0x118] = 0;
  param_1[0x119] = 0;
  *(undefined4 *)(param_1 + 0x11d) = 0;
  param_1[0x11b] = 0;
  param_1[0x11c] = 0;
  *(undefined4 *)(param_1 + 0x120) = 0;
  param_1[0x11e] = 0;
  param_1[0x11f] = 0;
  *(undefined4 *)(param_1 + 0x123) = 0;
  param_1[0x121] = 0;
  param_1[0x122] = 0;
  *(undefined4 *)(param_1 + 0x126) = 0;
  param_1[0x124] = 0;
  param_1[0x125] = 0;
  *(undefined4 *)(param_1 + 0x129) = 0;
  param_1[0x127] = 0;
  param_1[0x128] = 0;
  *(undefined4 *)(param_1 + 300) = 0;
  param_1[0x12a] = 0;
  param_1[299] = 0;
  *(undefined4 *)(param_1 + 0x12f) = 0;
  param_1[0x12d] = 0;
  param_1[0x12e] = 0;
  *(undefined4 *)(param_1 + 0x132) = 0;
  param_1[0x130] = 0;
  param_1[0x131] = 0;
  *(undefined4 *)(param_1 + 0x135) = 0;
  param_1[0x133] = 0;
  param_1[0x134] = 0;
  *(undefined4 *)(param_1 + 0x138) = 0;
  param_1[0x136] = 0;
  param_1[0x137] = 0;
  *(undefined4 *)(param_1 + 0x13b) = 0;
  param_1[0x139] = 0;
  param_1[0x13a] = 0;
  *(undefined4 *)(param_1 + 0x13e) = 0;
  param_1[0x13c] = 0;
  param_1[0x13d] = 0;
  *(undefined4 *)(param_1 + 0x141) = 0;
  param_1[0x13f] = 0;
  param_1[0x140] = 0;
  *(undefined4 *)(param_1 + 0x144) = 0;
  param_1[0x142] = 0;
  param_1[0x143] = 0;
  *(undefined4 *)(param_1 + 0x147) = 0;
  param_1[0x145] = 0;
  param_1[0x146] = 0;
  *(undefined4 *)(param_1 + 0x14a) = 0;
  param_1[0x148] = 0;
  param_1[0x149] = 0;
  *(undefined4 *)(param_1 + 0x14d) = 0;
  param_1[0x14b] = 0;
  param_1[0x14c] = 0;
  *(undefined4 *)(param_1 + 0x150) = 0;
  param_1[0x14e] = 0;
  param_1[0x14f] = 0;
  *(undefined4 *)(param_1 + 0x153) = 0;
  param_1[0x151] = 0;
  param_1[0x152] = 0;
  *(undefined4 *)(param_1 + 0x156) = 0;
  param_1[0x154] = 0;
  param_1[0x155] = 0;
  *(undefined4 *)(param_1 + 0x159) = 0;
  param_1[0x157] = 0;
  param_1[0x158] = 0;
  *(undefined4 *)(param_1 + 0x15c) = 0;
  param_1[0x15a] = 0;
  param_1[0x15b] = 0;
  *(undefined4 *)(param_1 + 0x15f) = 0;
  param_1[0x15d] = 0;
  param_1[0x15e] = 0;
  *(undefined4 *)(param_1 + 0x162) = 0;
  param_1[0x160] = 0;
  param_1[0x161] = 0;
  *(undefined4 *)(param_1 + 0x165) = 0;
  param_1[0x163] = 0;
  param_1[0x164] = 0;
  *(undefined4 *)(param_1 + 0x168) = 0;
  param_1[0x166] = 0;
  param_1[0x167] = 0;
  *(undefined4 *)(param_1 + 0x16b) = 0;
  param_1[0x169] = 0;
  param_1[0x16a] = 0;
  *(undefined4 *)(param_1 + 0x16e) = 0;
  param_1[0x16c] = 0;
  param_1[0x16d] = 0;
  *(undefined4 *)(param_1 + 0x171) = 0;
  param_1[0x16f] = 0;
  param_1[0x170] = 0;
  *(undefined4 *)(param_1 + 0x174) = 0;
  param_1[0x172] = 0;
  param_1[0x173] = 0;
  *(undefined4 *)(param_1 + 0x177) = 0;
  param_1[0x175] = 0;
  param_1[0x176] = 0;
  *(undefined4 *)(param_1 + 0x17a) = 0;
  param_1[0x178] = 0;
  param_1[0x179] = 0;
  *(undefined4 *)(param_1 + 0x17d) = 0;
  param_1[0x17b] = 0;
  param_1[0x17c] = 0;
  *(undefined4 *)(param_1 + 0x180) = 0;
  param_1[0x17e] = 0;
  param_1[0x17f] = 0;
  *(undefined4 *)(param_1 + 0x183) = 0;
  param_1[0x181] = 0;
  param_1[0x182] = 0;
  *(undefined4 *)(param_1 + 0x186) = 0;
  param_1[0x184] = 0;
  param_1[0x185] = 0;
  *(undefined4 *)(param_1 + 0x189) = 0;
  param_1[0x187] = 0;
  param_1[0x188] = 0;
  *(undefined4 *)(param_1 + 0x18c) = 0;
  param_1[0x18a] = 0;
  param_1[0x18b] = 0;
  *(undefined4 *)(param_1 + 399) = 0;
  param_1[0x18d] = 0;
  param_1[0x18e] = 0;
  *(undefined4 *)(param_1 + 0x192) = 0;
  param_1[400] = 0;
  param_1[0x191] = 0;
  *(undefined4 *)(param_1 + 0x195) = 0;
  param_1[0x193] = 0;
  param_1[0x194] = 0;
  *(undefined4 *)(param_1 + 0x198) = 0;
  param_1[0x196] = 0;
  param_1[0x197] = 0;
  *(undefined4 *)(param_1 + 0x19b) = 0;
  param_1[0x199] = 0;
  param_1[0x19a] = 0;
  *(undefined4 *)(param_1 + 0x19e) = 0;
  param_1[0x19c] = 0;
  param_1[0x19d] = 0;
  *(undefined4 *)(param_1 + 0x1a1) = 0;
  param_1[0x19f] = 0;
  param_1[0x1a0] = 0;
  *(undefined4 *)(param_1 + 0x1a4) = 0;
  param_1[0x1a2] = 0;
  param_1[0x1a3] = 0;
  *(undefined4 *)(param_1 + 0x1a7) = 0;
  param_1[0x1a5] = 0;
  param_1[0x1a6] = 0;
  *(undefined4 *)(param_1 + 0x1aa) = 0;
  param_1[0x1a8] = 0;
  param_1[0x1a9] = 0;
  *(undefined4 *)(param_1 + 0x1ad) = 0;
  param_1[0x1ab] = 0;
  param_1[0x1ac] = 0;
  *(undefined4 *)(param_1 + 0x1b0) = 0;
  param_1[0x1ae] = 0;
  param_1[0x1af] = 0;
  *(undefined4 *)(param_1 + 0x1b3) = 0;
  param_1[0x1b1] = 0;
  param_1[0x1b2] = 0;
  *(undefined4 *)(param_1 + 0x1b6) = 0;
  param_1[0x1b4] = 0;
  param_1[0x1b5] = 0;
  *(undefined4 *)(param_1 + 0x1b9) = 0;
  param_1[0x1b7] = 0;
  param_1[0x1b8] = 0;
  *(undefined4 *)(param_1 + 0x1bc) = 0;
  param_1[0x1ba] = 0;
  param_1[0x1bb] = 0;
  *(undefined4 *)(param_1 + 0x1bf) = 0;
  param_1[0x1bd] = 0;
  param_1[0x1be] = 0;
  *(undefined4 *)(param_1 + 0x1c2) = 0;
  param_1[0x1c0] = 0;
  param_1[0x1c1] = 0;
  *(undefined4 *)(param_1 + 0x1c5) = 0;
  param_1[0x1c3] = 0;
  param_1[0x1c4] = 0;
  *(undefined4 *)(param_1 + 0x1c8) = 0;
  param_1[0x1c6] = 0;
  param_1[0x1c7] = 0;
  *(undefined4 *)(param_1 + 0x1cb) = 0;
  param_1[0x1c9] = 0;
  param_1[0x1ca] = 0;
  *(undefined4 *)(param_1 + 0x1ce) = 0;
  param_1[0x1cc] = 0;
  param_1[0x1cd] = 0;
  *(undefined4 *)(param_1 + 0x1d1) = 0;
  param_1[0x1cf] = 0;
  param_1[0x1d0] = 0;
  *(undefined4 *)(param_1 + 0x1d4) = 0;
  param_1[0x1d2] = 0;
  param_1[0x1d3] = 0;
  *(undefined4 *)(param_1 + 0x1d7) = 0;
  param_1[0x1d5] = 0;
  param_1[0x1d6] = 0;
  *(undefined4 *)(param_1 + 0x1da) = 0;
  param_1[0x1d8] = 0;
  param_1[0x1d9] = 0;
  *(undefined4 *)(param_1 + 0x1dd) = 0;
  param_1[0x1db] = 0;
  param_1[0x1dc] = 0;
  *(undefined4 *)(param_1 + 0x1e0) = 0;
  param_1[0x1de] = 0;
  param_1[0x1df] = 0;
  *(undefined4 *)(param_1 + 0x1e3) = 0;
  param_1[0x1e1] = 0;
  param_1[0x1e2] = 0;
  *(undefined4 *)(param_1 + 0x1e6) = 0;
  param_1[0x1e4] = 0;
  param_1[0x1e5] = 0;
  *(undefined4 *)(param_1 + 0x1e9) = 0;
  param_1[0x1e7] = 0;
  param_1[0x1e8] = 0;
  *(undefined4 *)(param_1 + 0x1ec) = 0;
  param_1[0x1ea] = 0;
  param_1[0x1eb] = 0;
  *(undefined4 *)(param_1 + 0x1ef) = 0;
  param_1[0x1ed] = 0;
  param_1[0x1ee] = 0;
  *(undefined4 *)(param_1 + 0x1f2) = 0;
  param_1[0x1f0] = 0;
  param_1[0x1f1] = 0;
  *(undefined4 *)(param_1 + 0x1f5) = 0;
  param_1[499] = 0;
  param_1[500] = 0;
  param_1[0x1f6] = 0;
  param_1[0x1f7] = 0;
  *(undefined4 *)(param_1 + 0x1f8) = 0;
  *(undefined4 *)(param_1 + 0x1fb) = 0;
  param_1[0x1fa] = 0;
  param_1[0x1f9] = 0;
  *(undefined4 *)(param_1 + 0x1fe) = 0;
  param_1[0x1fc] = 0;
  param_1[0x1fd] = 0;
  *(undefined4 *)(param_1 + 0x201) = 0;
  param_1[0x1ff] = 0;
  param_1[0x200] = 0;
  param_1[0x202] = 0;
  param_1[0x203] = 0;
  return;
}

// ==== Aska::AudioMixer::~AudioMixer()
// vaddr 0x2243280 | ghidra 0x2343280 | size 468 | symbol _ZN4Aska10AudioMixerD1Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska10AudioMixerD2Ev(long *param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  
  puVar4 = PTR__ZTVN4Aska13AudioEffectorE_02cc4a78;
  puVar3 = PTR__ZTVN4Aska10BusChannelE_02cc1238;
  puVar1 = PTR__ZTVN4Aska10BusChannelE_02cc1238 + 0x10;
  puVar2 = PTR__ZTVN4Aska13AudioEffectorE_02cc4a78 + 0x10;
  *param_1 = (long)(PTR__ZTVN4Aska10AudioMixerE_02cbab18 + 0x10);
  param_1[0x5d] = (long)puVar1;
  param_1[0x60] = (long)puVar2;
  param_1[99] = 1;
  *(undefined4 *)(param_1 + 100) = 0;
  if (param_1[0x65] != 0) {
    operator delete[](void*)();
    param_1[0x65] = 0;
  }
  Aska::FastCriticalSection::~FastCriticalSection()(param_1 + 0x66);
  puVar1 = PTR__ZTVN4Aska13TDynamicQueueINS_15EffectorRequest16RequestContainerELb1EEE_02cb7d20;
  *(undefined4 *)(param_1 + 100) = 0;
  param_1[0x62] = (long)(puVar1 + 0x10);
  param_1[99] = 1;
  if (param_1[0x65] != 0) {
    operator delete[](void*)();
    param_1[0x65] = 0;
  }
  Aska::IAnimatable::~IAnimatable()(param_1 + 0x60);
  param_1[0x42] = (long)(puVar3 + 0x10);
  param_1[0x45] = (long)(puVar4 + 0x10);
  param_1[0x48] = 1;
  *(undefined4 *)(param_1 + 0x49) = 0;
  if (param_1[0x4a] != 0) {
    operator delete[](void*)();
    param_1[0x4a] = 0;
  }
  Aska::FastCriticalSection::~FastCriticalSection()(param_1 + 0x4b);
  param_1[0x47] = (long)(puVar1 + 0x10);
  param_1[0x48] = 1;
  *(undefined4 *)(param_1 + 0x49) = 0;
  if (param_1[0x4a] != 0) {
    operator delete[](void*)();
    param_1[0x4a] = 0;
  }
  Aska::IAnimatable::~IAnimatable()(param_1 + 0x45);
  param_1[0x27] = (long)(puVar3 + 0x10);
  param_1[0x2a] = (long)(puVar4 + 0x10);
  param_1[0x2d] = 1;
  *(undefined4 *)(param_1 + 0x2e) = 0;
  if (param_1[0x2f] != 0) {
    operator delete[](void*)();
    param_1[0x2f] = 0;
  }
  Aska::FastCriticalSection::~FastCriticalSection()(param_1 + 0x30);
  param_1[0x2c] = (long)(puVar1 + 0x10);
  param_1[0x2d] = 1;
  *(undefined4 *)(param_1 + 0x2e) = 0;
  if (param_1[0x2f] != 0) {
    operator delete[](void*)();
    param_1[0x2f] = 0;
  }
  Aska::IAnimatable::~IAnimatable()(param_1 + 0x2a);
  param_1[0xf] = (long)(puVar4 + 0x10);
  param_1[0xc] = (long)(puVar3 + 0x10);
  param_1[0x12] = 1;
  *(undefined4 *)(param_1 + 0x13) = 0;
  if (param_1[0x14] != 0) {
    operator delete[](void*)();
    param_1[0x14] = 0;
  }
  Aska::FastCriticalSection::~FastCriticalSection()(param_1 + 0x15);
  param_1[0x11] = (long)(puVar1 + 0x10);
  param_1[0x12] = 1;
  *(undefined4 *)(param_1 + 0x13) = 0;
  if (param_1[0x14] != 0) {
    operator delete[](void*)();
    param_1[0x14] = 0;
  }
  Aska::IAnimatable::~IAnimatable()(param_1 + 0xf);
  (*(code *)PTR__ZN4Aska12IAudioDeviceD1Ev_02ca0420)(param_1);
  return;
}

// ==== Aska::AudioMixer::~AudioMixer()
// vaddr 0x22434e4 | ghidra 0x23434e4 | size 24 | symbol _ZN4Aska10AudioMixerD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska10AudioMixerD0Ev(undefined8 param_1)

{
  Aska::AudioMixer::~AudioMixer()();
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::AudioMixer::SetupDevice()
// vaddr 0x22434fc | ghidra 0x23434fc | size 328 | symbol _ZN4Aska10AudioMixer11SetupDeviceEv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska10AudioMixer11SetupDeviceEv(long *param_1)

{
  ulong uVar1;
  uint uVar2;
  long lVar3;
  long *plVar4;
  
  if (((int)param_1[3] == 0) && (uVar1 = Aska::MasterBusSL::SetupBus(Aska::InitBusContext*)(param_1 + 4,0x2ce7184), (uVar1 & 1) != 0))
  {
    param_1[10] = (long)param_1;
    *(undefined4 *)(param_1 + 0xb) = 0;
    uVar1 = (**(code **)(param_1[0xc] + 0x10))(param_1 + 0xc,param_1,1);
    if (((uVar1 & 1) != 0) &&
       (((uVar1 = (**(code **)(param_1[0x27] + 0x10))(param_1 + 0x27,param_1,2), (uVar1 & 1) != 0 &&
         (uVar1 = (**(code **)(param_1[0x42] + 0x10))(param_1 + 0x42,param_1,3), (uVar1 & 1) != 0))
        && (uVar1 = (**(code **)(param_1[0x5d] + 0x10))(param_1 + 0x5d,param_1,4), (uVar1 & 1) != 0)
        ))) {
      lVar3 = 0;
      plVar4 = param_1 + 0x79;
      do {
        uVar2 = (uint)lVar3;
        lVar3 = lVar3 + 1;
        *plVar4 = (long)param_1;
        *(uint *)(plVar4 + -1) = uVar2 | 0x1ff0000;
        plVar4 = plVar4 + 3;
      } while (lVar3 != 0x80);
      *(uint *)(param_1 + 0x1f8) = (*(uint *)(param_1 + 0xe) & 0xff) << 0x10 | 0x3000000;
      param_1[0x1f9] = (long)param_1;
      param_1[0x1fc] = (long)param_1;
      param_1[0x1ff] = (long)param_1;
      param_1[0x202] = (long)param_1;
      *(uint *)(param_1 + 0x1fb) = (*(uint *)(param_1 + 0x29) & 0xff) << 0x10 | 0x3000000;
      *(uint *)(param_1 + 0x1fe) = (*(uint *)(param_1 + 0x44) & 0xff) << 0x10 | 0x3000000;
      *(uint *)(param_1 + 0x201) = (*(uint *)(param_1 + 0x5f) & 0xff) << 0x10 | 0x3000000;
      *(undefined4 *)(param_1 + 3) = 1;
      return 1;
    }
    *(undefined4 *)(param_1 + 3) = 1;
    (**(code **)(*param_1 + 0x60))(param_1);
  }
  return 0;
}

// ==== Aska::AudioMixer::FinishDevice()
// vaddr 0x2243644 | ghidra 0x2343644 | size 208 | symbol _ZN4Aska10AudioMixer12FinishDeviceEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska10AudioMixer12FinishDeviceEv(long param_1)

{
  long lVar1;
  long lVar2;
  
  if (*(int *)(param_1 + 0x18) != 0) {
    *(undefined8 *)(param_1 + 0x50) = 0;
    *(undefined4 *)(param_1 + 0x58) = 0xffffffff;
    (**(code **)(*(long *)(param_1 + 0x60) + 0x18))((long *)(param_1 + 0x60));
    (**(code **)(*(long *)(param_1 + 0x138) + 0x18))(param_1 + 0x138);
    (**(code **)(*(long *)(param_1 + 0x210) + 0x18))(param_1 + 0x210);
    (**(code **)(*(long *)(param_1 + 0x2e8) + 0x18))(param_1 + 0x2e8);
    lVar2 = 0;
    do {
      lVar1 = param_1 + lVar2;
      lVar2 = lVar2 + 0x18;
      *(undefined4 *)(lVar1 + 0x3c0) = 0;
      *(undefined8 *)(lVar1 + 0x3d0) = 0;
      *(undefined8 *)(lVar1 + 0x3c8) = 0;
    } while (lVar2 != 0xc00);
    *(undefined4 *)(param_1 + 0xfc0) = 0;
    *(undefined8 *)(param_1 + 0x1018) = 0;
    *(undefined8 *)(param_1 + 0x1010) = 0;
    *(undefined4 *)(param_1 + 0xfd8) = 0;
    *(undefined8 *)(param_1 + 0xfc8) = 0;
    *(undefined8 *)(param_1 + 0xfd0) = 0;
    *(undefined4 *)(param_1 + 0xff0) = 0;
    *(undefined8 *)(param_1 + 0xfe0) = 0;
    *(undefined8 *)(param_1 + 0xfe8) = 0;
    *(undefined4 *)(param_1 + 0x1008) = 0;
    *(undefined8 *)(param_1 + 0xff8) = 0;
    *(undefined8 *)(param_1 + 0x1000) = 0;
    Aska::MasterBusSL::FinishBus()(param_1 + 0x20);
    *(undefined4 *)(param_1 + 0x18) = 0;
  }
  return;
}

// ==== Aska::AudioMixer::AudioRun()
// vaddr 0x2243714 | ghidra 0x2343714 | size 44 | symbol _ZN4Aska10AudioMixer8AudioRunEv | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Possible PIC construction at 0x02343720: Changing call to branch */
/* WARNING: Possible PIC construction at 0x02343730: Changing call to branch */
/* WARNING: Removing unreachable block (ram,0x02343724) */
/* WARNING: Removing unreachable block (ram,0x02343734) */

void _ZN4Aska10AudioMixer8AudioRunEv(long param_1)

{
  (*(code *)PTR__ZN4Aska13AudioEffector8AudioRunEv_02c9bb40)(param_1 + 0x78);
  return;
}

// ==== Aska::AudioMixer::GetBus(unsigned long)
// vaddr 0x2243740 | ghidra 0x2343740 | size 100 | symbol _ZN4Aska10AudioMixer6GetBusEm | lib libSOA-3.7.0.so | 2026-10-08
long _ZN4Aska10AudioMixer6GetBusEm(long param_1,uint param_2)

{
  uint uVar1;
  long lVar2;
  
  uVar1 = param_2 >> 0x10 & 0xff;
  if (*(uint *)(param_1 + 0x58) == uVar1) {
    lVar2 = param_1 + 0x48;
  }
  else {
    if (uVar1 < *(uint *)(param_1 + 0x70)) {
      return 0;
    }
    if (*(uint *)(param_1 + 0x2f8) < uVar1) {
      return 0;
    }
    lVar2 = param_1 + (ulong)(uVar1 - *(uint *)(param_1 + 0x70)) * 0xd8 + 0x60;
  }
  if (*(uint *)(lVar2 + 0x10) != *(uint *)(param_1 + 0x58)) {
    return *(long *)(lVar2 + 0x20);
  }
  return param_1 + 0x20;
}

// ==== Aska::AudioMixer::GetMixerChannel(unsigned int)
// vaddr 0x22437a4 | ghidra 0x23437a4 | size 60 | symbol _ZN4Aska10AudioMixer15GetMixerChannelEj | lib libSOA-3.7.0.so | 2026-10-08
long _ZN4Aska10AudioMixer15GetMixerChannelEj(long param_1,uint param_2)

{
  long lVar1;
  
  if (*(uint *)(param_1 + 0x58) == param_2) {
    return param_1 + 0x48;
  }
  lVar1 = 0;
  if (param_2 <= *(uint *)(param_1 + 0x2f8) && *(uint *)(param_1 + 0x70) <= param_2) {
    lVar1 = param_1 + (ulong)(param_2 - *(uint *)(param_1 + 0x70)) * 0xd8 + 0x60;
  }
  return lVar1;
}

// ==== Aska::AudioMixer::MakeRouting()
// vaddr 0x22437e0 | ghidra 0x23437e0 | size 480 | symbol _ZN4Aska10AudioMixer11MakeRoutingEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska10AudioMixer11MakeRoutingEv(long *param_1)

{
  uint uVar1;
  byte bVar2;
  int iVar3;
  long lVar4;
  long *plVar5;
  long lVar6;
  ulong uVar7;
  uint uVar8;
  long *plVar9;
  long *plVar10;
  long *plVar11;
  long lVar12;
  
  Aska::AudioEffector::DisconnectBus(int)(param_1 + 0xf,1);
  Aska::AudioEffector::DisconnectBus(int)(param_1 + 0x2a,1);
  Aska::AudioEffector::DisconnectBus(int)(param_1 + 0x45,1);
  Aska::AudioEffector::DisconnectBus(int)(param_1 + 0x60,1);
  lVar12 = 0;
  do {
    uVar1 = (*(uint *)(param_1 + lVar12 * 0x1b + 0xe) & 0xff) << 0x10 | 0x3000000;
    lVar4 = Aska::IAudioDevice::GetRouteConnector(unsigned int)(param_1,uVar1);
    plVar5 = (long *)Aska::IAudioDevice::GetRouteDevice(unsigned int)(param_1,uVar1);
    lVar6 = Aska::IAudioDevice::GetRouteBus(unsigned int)(param_1,uVar1);
    if (lVar6 != 0) {
      plVar10 = param_1 + lVar12 * 0x1b + 0xf;
      plVar11 = param_1;
      do {
        while (plVar9 = plVar5, iVar3 = (**(code **)(*plVar11 + 0x38))(plVar11), iVar3 != 0) {
          iVar3 = (**(code **)(*plVar11 + 0x38))(plVar11);
          plVar5 = plVar9;
          if (iVar3 == 2) {
            uVar7 = Aska::AudioEffector::ConnectBus(int, Aska::IBus*)(plVar10,0,lVar6);
            if ((uVar7 & 1) == 0) goto code_r0x0234399c;
            bVar2 = *(byte *)(lVar4 + 2);
            if (*(uint *)(param_1 + 0xb) == (uint)bVar2) goto code_r0x0234399c;
            uVar1 = (uint)bVar2 << 0x10 | 0x3000000;
            uVar8 = (uint)bVar2;
            plVar10 = (long *)0x0;
            if (uVar8 <= *(uint *)(param_1 + 0x5f) && *(uint *)(param_1 + 0xe) <= uVar8) {
              plVar10 = param_1 + (ulong)(uVar8 - *(uint *)(param_1 + 0xe)) * 0x1b + 0xc;
            }
            plVar10 = plVar10 + 3;
            lVar4 = Aska::IAudioDevice::GetRouteConnector(unsigned int)(plVar9,uVar1);
            plVar5 = (long *)Aska::IAudioDevice::GetRouteDevice(unsigned int)(plVar9,uVar1);
            lVar6 = Aska::IAudioDevice::GetRouteBus(unsigned int)(plVar9,uVar1);
            plVar11 = plVar9;
            if (lVar6 == 0) goto code_r0x0234399c;
          }
        }
        uVar7 = Aska::AudioEffector::ConnectBus(int, Aska::IBus*)(plVar10,1,lVar6);
        if ((uVar7 & 1) == 0) break;
        plVar10 = plVar9 + 10;
        lVar4 = Aska::IAudioDevice::GetRouteConnector(unsigned int)(plVar9,0x2ff0000);
        plVar5 = (long *)Aska::IAudioDevice::GetRouteDevice(unsigned int)(plVar9,0x2ff0000);
        lVar6 = Aska::IAudioDevice::GetRouteBus(unsigned int)(plVar9,0x2ff0000);
        plVar11 = plVar9;
      } while (lVar6 != 0);
    }
code_r0x0234399c:
    lVar12 = lVar12 + 1;
    if (lVar12 == 4) {
      return;
    }
  } while( true );
}

// ==== Aska::AudioMixer::GetBusChannel(unsigned int)
// vaddr 0x22439c0 | ghidra 0x23439c0 | size 60 | symbol _ZN4Aska10AudioMixer13GetBusChannelEj | lib libSOA-3.7.0.so | 2026-10-08
long _ZN4Aska10AudioMixer13GetBusChannelEj(long param_1,uint param_2)

{
  long lVar1;
  
  if (*(uint *)(param_1 + 0x58) == param_2) {
    return 0;
  }
  lVar1 = 0;
  if (param_2 <= *(uint *)(param_1 + 0x2f8) && *(uint *)(param_1 + 0x70) <= param_2) {
    lVar1 = param_1 + (ulong)(param_2 - *(uint *)(param_1 + 0x70)) * 0xd8 + 0x60;
  }
  return lVar1;
}

// ==== Aska::AudioMixer::SetInterface(unsigned int, Aska::AudioInterface*)
// vaddr 0x22439fc | ghidra 0x23439fc | size 304 | symbol _ZN4Aska10AudioMixer12SetInterfaceEjPNS_14AudioInterfaceE | lib libSOA-3.7.0.so | 2026-10-08
ulong _ZN4Aska10AudioMixer12SetInterfaceEjPNS_14AudioInterfaceE
                (long *param_1,ulong param_2,long param_3)

{
  uint uVar1;
  ulong uVar2;
  uint *puVar3;
  uint uVar4;
  long lVar5;
  uint uVar6;
  
  uVar6 = (uint)(param_2 >> 0x18) & 0xff;
  if ((uVar6 | 2) == 3) {
    if (param_3 == 0) {
      puVar3 = (uint *)(**(code **)(*param_1 + 0x50))();
      if (puVar3 != (uint *)0x0) {
        lVar5 = Aska::SoundManager::QueryAudioInterface(Aska::AudioConnector*) const(*(undefined8 *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50,puVar3
                               );
        if (lVar5 != 0) {
          Aska::AudioInterface::Disconnect(Aska::AudioConnector*)(lVar5,puVar3);
        }
        if (uVar6 == 1) {
          *puVar3 = *puVar3 | 0xff0000;
        }
        uVar4 = 1;
        goto code_r0x02343ad4;
      }
    }
    else {
      uVar1 = (uint)param_2 >> 0x10 & 0xff;
      if ((*(uint *)(param_1 + 0xb) != uVar1) &&
         ((uVar4 = 0, uVar1 < *(uint *)(param_1 + 0xe) || (*(uint *)(param_1 + 0x5f) < uVar1))))
      goto code_r0x02343ad4;
      if (uVar6 == 3) {
        uVar4 = 0;
        if (((uVar1 < 5) && (uVar4 = 0, (param_2 & 0xffff) == 0)) &&
           (*(uint *)(param_1 + 0xb) != uVar1)) {
          puVar3 = (uint *)(param_1 + (ulong)(uVar1 - 1) * 3 + 0x1f8);
code_r0x011e5ef0:
          uVar2 = (*(code *)PTR__ZN4Aska14AudioInterface7ConnectEPNS_14AudioConnectorE_02caaf68)
                            (param_3,puVar3);
          return uVar2;
        }
        goto code_r0x02343ad4;
      }
      if (uVar6 == 1) {
        puVar3 = (uint *)(param_1 + 0x78);
        lVar5 = -1;
        do {
          uVar6 = *puVar3;
          if ((~uVar6 & 0xff0000) == 0) {
            *puVar3 = uVar6 & 0xff000000 | uVar6 & 0xffff | uVar1 << 0x10;
            goto code_r0x011e5ef0;
          }
          lVar5 = lVar5 + 1;
          puVar3 = puVar3 + 6;
        } while (lVar5 < 0x7f);
      }
    }
  }
  uVar4 = 0;
code_r0x02343ad4:
  return (ulong)uVar4;
}

// ==== Aska::AudioMixer::GetInterface(unsigned int)
// vaddr 0x2243b2c | ghidra 0x2343b2c | size 56 | symbol _ZN4Aska10AudioMixer12GetInterfaceEj | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska10AudioMixer12GetInterfaceEj(long *param_1)

{
  long lVar1;
  
  lVar1 = (**(code **)(*param_1 + 0x50))();
  if (lVar1 != 0) {
    (*(code *)PTR__ZNK4Aska12SoundManager19QueryAudioInterfaceEPNS_14AudioConnectorE_02ca99d0)
              (*(undefined8 *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50,lVar1);
    return;
  }
  return;
}

// ==== Aska::AudioMixer::GetConnector(unsigned int)
// vaddr 0x2243b64 | ghidra 0x2343b64 | size 144 | symbol _ZN4Aska10AudioMixer12GetConnectorEj | lib libSOA-3.7.0.so | 2026-10-08
long _ZN4Aska10AudioMixer12GetConnectorEj(long param_1,uint param_2)

{
  uint uVar1;
  uint uVar2;
  long lVar3;
  
  uVar1 = param_2 & 0xffff;
  if (param_2 >> 0x18 == 3) {
    uVar2 = param_2 >> 0x10 & 0xff;
    if (4 < uVar2) {
      return 0;
    }
    lVar3 = 0;
    if ((uVar1 == 0) && (uVar2 != *(uint *)(param_1 + 0x58))) {
      lVar3 = param_1 + (ulong)(uVar2 - 1) * 0x18 + 0xfc0;
    }
    return lVar3;
  }
  if (param_2 >> 0x18 == 1) {
    if (0x7f < uVar1) {
      return 0;
    }
    return param_1 + (ulong)uVar1 * 0x18 + 0x3c0;
  }
  return 0;
}

// ==== Aska::AudioMixer::BuildFinalVolumeAndPanpot(float*, float*, float, float)
// vaddr 0x2243bf4 | ghidra 0x2343bf4 | size 40 | symbol _ZN4Aska10AudioMixer25BuildFinalVolumeAndPanpotEPfS1_ff | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska10AudioMixer25BuildFinalVolumeAndPanpotEPfS1_ff
               (undefined4 param_1,undefined4 param_2,undefined4 *param_3,undefined4 *param_4)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = *(int *)(*(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50 + 0x115c);
  *param_3 = param_1;
  uVar2 = 0;
  if (iVar1 != 0) {
    uVar2 = param_2;
  }
  *param_4 = uVar2;
  return;
}

// ==== Aska::AudioMixer::AutoChannelAssign(float*, float, float*, int)
// vaddr 0x2243c1c | ghidra 0x2343c1c | size 196 | symbol _ZN4Aska10AudioMixer17AutoChannelAssignEPffS1_i | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska10AudioMixer17AutoChannelAssignEPffS1_i
               (float param_1,float *param_2,float *param_3,undefined4 param_4)

{
  float *pfVar1;
  long lVar2;
  float fVar3;
  
  switch(param_4) {
  case 1:
    fVar3 = *param_3;
    lVar2 = 1;
    goto code_r0x02343c50;
  case 2:
    fVar3 = *param_3;
    lVar2 = 7;
    param_3 = param_3 + 1;
code_r0x02343c50:
    *param_2 = fVar3 * param_1;
    break;
  default:
    goto code_r0x02343cdc;
  case 4:
    lVar2 = 0x17;
    *param_2 = *param_3 * param_1;
    param_2[7] = param_3[1] * param_1;
    pfVar1 = param_3 + 2;
    param_3 = param_3 + 3;
    param_2[0x10] = *pfVar1 * param_1;
    break;
  case 6:
    lVar2 = 0x23;
    *param_2 = *param_3 * param_1;
    param_2[7] = param_3[1] * param_1;
    param_2[0xe] = param_3[2] * param_1;
    param_2[0x15] = param_3[3] * param_1;
    pfVar1 = param_3 + 4;
    param_3 = param_3 + 5;
    param_2[0x1c] = *pfVar1 * param_1;
  }
  param_2[lVar2] = *param_3 * param_1;
code_r0x02343cdc:
  return;
}

// ==== Aska::AudioMixer::AutoChannelAssignFromMap(float*, float, float*, int, unsigned int)
// vaddr 0x2243ce0 | ghidra 0x2343ce0 | size 212 | symbol _ZN4Aska10AudioMixer24AutoChannelAssignFromMapEPffS1_ij | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska10AudioMixer24AutoChannelAssignFromMapEPffS1_ij
               (float param_1,long param_2,float *param_3,uint param_4,undefined4 param_5)

{
  ulong uVar1;
  float *pfVar2;
  float fVar3;
  
  switch(param_5) {
  case 1:
    if (0 < (int)param_4) {
      uVar1 = (ulong)param_4;
      pfVar2 = (float *)(param_2 + 4);
      do {
        fVar3 = *param_3;
        uVar1 = uVar1 - 1;
        pfVar2[-1] = fVar3 * param_1;
        *pfVar2 = fVar3 * param_1;
        pfVar2 = pfVar2 + 6;
        param_3 = param_3 + 1;
      } while (uVar1 != 0);
    }
    break;
  case 2:
    if (0 < (int)param_4) {
      uVar1 = (ulong)param_4;
      pfVar2 = (float *)(param_2 + 4);
      do {
        fVar3 = *param_3;
        uVar1 = uVar1 - 1;
        pfVar2[-1] = fVar3 * param_1;
        *pfVar2 = fVar3 * param_1;
        pfVar2 = pfVar2 + 6;
        param_3 = param_3 + 1;
      } while (uVar1 != 0);
    }
    break;
  case 3:
    if (0 < (int)param_4) {
      uVar1 = (ulong)param_4;
      pfVar2 = (float *)(param_2 + 0x10);
      do {
        uVar1 = uVar1 - 1;
        fVar3 = *param_3 * param_1;
        pfVar2[-4] = fVar3;
        pfVar2[-3] = fVar3;
        *pfVar2 = fVar3;
        pfVar2[1] = fVar3;
        param_3 = param_3 + 1;
        pfVar2 = pfVar2 + 6;
      } while (uVar1 != 0);
    }
    break;
  case 4:
    if (0 < (int)param_4) {
      uVar1 = (ulong)param_4;
      pfVar2 = (float *)(param_2 + 0x10);
      do {
        uVar1 = uVar1 - 1;
        fVar3 = *param_3 * param_1;
        pfVar2[-4] = fVar3;
        pfVar2[-3] = fVar3;
        pfVar2[-2] = fVar3;
        *pfVar2 = fVar3;
        pfVar2[1] = fVar3;
        param_3 = param_3 + 1;
        pfVar2 = pfVar2 + 6;
      } while (uVar1 != 0);
    }
  }
  return;
}

// ==== Aska::AudioMixer::FreeChannelAssign(float*, float, float*, int, unsigned char const*)
// vaddr 0x2243db4 | ghidra 0x2343db4 | size 168 | symbol _ZN4Aska10AudioMixer17FreeChannelAssignEPffS1_iPKh | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Type propagation algorithm not settling */

void _ZN4Aska10AudioMixer17FreeChannelAssignEPffS1_iPKh
               (float param_1,long param_2,float *param_3,uint param_4,byte *param_5)

{
  byte bVar1;
  long lVar2;
  ulong uVar3;
  float *pfVar4;
  float fVar5;
  
  if (0 < (int)param_4) {
    lVar2 = 0;
    uVar3 = (ulong)param_4;
    pfVar4 = (float *)(param_2 + 0xc);
    do {
      bVar1 = *param_5;
      fVar5 = *param_3 * param_1;
      if ((bVar1 & 1) != 0) {
        pfVar4[-3] = fVar5;
        bVar1 = *param_5;
      }
      if ((bVar1 >> 1 & 1) != 0) {
        *(float *)(param_2 + (lVar2 >> 0x1e | 4U)) = fVar5;
        bVar1 = *param_5;
      }
      if ((bVar1 >> 2 & 1) != 0) {
        pfVar4[-1] = fVar5;
        bVar1 = *param_5;
      }
      if ((bVar1 >> 3 & 1) != 0) {
        *pfVar4 = fVar5;
        bVar1 = *param_5;
      }
      if ((bVar1 >> 4 & 1) != 0) {
        pfVar4[1] = fVar5;
        bVar1 = *param_5;
      }
      if ((bVar1 >> 5 & 1) != 0) {
        pfVar4[2] = fVar5;
      }
      lVar2 = lVar2 + 0x600000000;
      param_3 = param_3 + 1;
      param_5 = param_5 + 1;
      uVar3 = uVar3 - 1;
      pfVar4 = pfVar4 + 6;
    } while (uVar3 != 0);
  }
  return;
}

// ==== Aska::AudioMixer::DownUpMixMatrix(float*, int, unsigned int, bool)
// vaddr 0x2243e5c | ghidra 0x2343e5c | size 308 | symbol _ZN4Aska10AudioMixer15DownUpMixMatrixEPfijb | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska10AudioMixer15DownUpMixMatrixEPfijb
               (undefined8 param_1,int param_2,uint param_3,uint param_4)

{
  int iVar1;
  bool bVar2;
  bool bVar3;
  uint uVar4;
  ulong uVar5;
  uint uVar6;
  uint uVar7;
  code *pcVar8;
  undefined1 auStack_b0 [144];
  
  if ((param_4 & 1) != 0) {
    if (param_2 - 2U < 5) {
      uVar7 = *(uint *)(&UNK_029d9830 + (long)(int)(param_2 - 2U) * 4);
      uVar4 = param_3 - 1;
    }
    else {
      uVar7 = 0;
      uVar4 = param_3 - 1;
    }
    goto code_r0x02343f00;
  }
  uVar7 = 0;
  uVar4 = 0;
  switch(param_2) {
  case 1:
    uVar7 = param_3 - 1;
    uVar4 = param_3 - 1;
    break;
  case 2:
    uVar7 = param_3 - 1;
    uVar4 = uVar7;
    if (param_3 < 3) {
      uVar7 = 1;
      uVar4 = uVar7;
    }
    break;
  case 4:
    bVar2 = 2 < param_3;
    bVar3 = param_3 == 3;
    uVar6 = 2;
    goto code_r0x02343ef8;
  case 6:
    bVar2 = 3 < param_3;
    bVar3 = param_3 == 4;
    uVar6 = 3;
code_r0x02343ef8:
    uVar7 = param_3 - 1;
    uVar4 = param_3 - 1;
    if (!bVar2 || bVar3) {
      uVar7 = uVar6;
      uVar4 = uVar6;
    }
  }
code_r0x02343f00:
  iVar1 = *(int *)(*(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50 + 0x115c);
  if (iVar1 == 1) {
    uVar6 = uVar4;
    if (1 < (int)uVar4 || uVar4 == 0) {
      uVar6 = 1;
    }
  }
  else if (iVar1 == 0) {
    uVar6 = uVar4 & (int)uVar4 >> 0x1f;
  }
  else {
    uVar6 = 3;
    if (iVar1 != 2 || (int)uVar4 < 4) {
      uVar6 = uVar4;
    }
  }
  uVar5 = (ulong)(int)(uVar6 + uVar7 * 4);
  if ((0x7bdeUL >> (uVar5 & 0x3f) & 1) != 0) {
    pcVar8 = *(code **)(&UNK_02c5f518 + uVar5 * 8);
    memcpy(auStack_b0,param_1,0x90);
    (*pcVar8)(param_1,auStack_b0);
  }
  return;
}

// ==== Aska::AudioMixer::Get(unsigned long, void*) const
// vaddr 0x2243fb0 | ghidra 0x2343fb0 | size 8 | symbol _ZNK4Aska10AudioMixer3GetEmPv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK4Aska10AudioMixer3GetEmPv(void)

{
  return 0;
}

// ==== Aska::AudioMixer::Set(unsigned long, void const*)
// vaddr 0x2243fb8 | ghidra 0x2343fb8 | size 8 | symbol _ZN4Aska10AudioMixer3SetEmPKv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska10AudioMixer3SetEmPKv(void)

{
  return 0;
}

// ==== Aska::AudioMixer::GetClassID(int) const
// vaddr 0x2244058 | ghidra 0x2344058 | size 68 | symbol _ZNK4Aska10AudioMixer10GetClassIDEi | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK4Aska10AudioMixer10GetClassIDEi(undefined8 param_1,int param_2)

{
  undefined8 uVar1;
  undefined8 uVar2;
  
  if (param_2 != 0) {
    uVar2 = 0xf000f001;
    if (param_2 != 2) {
      uVar2 = 0xf000;
    }
    uVar1 = 0xf000f001f212;
    if (param_2 != 1) {
      uVar1 = uVar2;
    }
    return uVar1;
  }
  return 0xf000f212f213;
}

// ==== Aska::AudioPlayer::AudioPlayer()
// vaddr 0x22440b4 | ghidra 0x23440b4 | size 92 | symbol _ZN4Aska11AudioPlayerC2Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska11AudioPlayerC2Ev(long *param_1)

{
  undefined *puVar1;
  
  Aska::IAudioDevice::IAudioDevice()();
  puVar1 = PTR__ZTVN4Aska11AudioPlayerE_02cc3ba0;
  *(undefined8 *)((long)param_1 + 0x1c) = 0;
  *(undefined8 *)((long)param_1 + 0x22) = 0;
  *(undefined8 *)((long)param_1 + 0x32) = 0;
  *(undefined8 *)((long)param_1 + 0x2c) = 0;
  *(undefined8 *)((long)param_1 + 0x42) = 0;
  *(undefined8 *)((long)param_1 + 0x3c) = 0;
  param_1[0xd] = 0;
  *param_1 = (long)(puVar1 + 0x10);
  puVar1 = PTR__ZTVN4Aska18TSoundDynamicQueueINS_12AudioMessageEEE_02cbd5a0;
  *(undefined4 *)(param_1 + 0xc) = 0;
  param_1[10] = (long)(puVar1 + 0x10);
  param_1[0xb] = 1;
  (*(code *)PTR__ZN4Aska19FastCriticalSectionC1Ev_02cade18)(param_1 + 0xe);
  return;
}

// ==== Aska::AudioPlayer::~AudioPlayer()
// vaddr 0x2244110 | ghidra 0x2344110 | size 84 | symbol _ZN4Aska11AudioPlayerD1Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska11AudioPlayerD2Ev(long *param_1)

{
  undefined *puVar1;
  
  *param_1 = (long)(PTR__ZTVN4Aska11AudioPlayerE_02cc3ba0 + 0x10);
  Aska::FastCriticalSection::~FastCriticalSection()(param_1 + 0xe);
  puVar1 = PTR__ZTVN4Aska13TDynamicQueueINS_12AudioMessageELb1EEE_02cc2768;
  *(undefined4 *)(param_1 + 0xc) = 0;
  param_1[10] = (long)(puVar1 + 0x10);
  param_1[0xb] = 1;
  if (param_1[0xd] != 0) {
    operator delete[](void*)();
    param_1[0xd] = 0;
  }
  (*(code *)PTR__ZN4Aska12IAudioDeviceD1Ev_02ca0420)(param_1);
  return;
}

// ==== Aska::AudioPlayer::~AudioPlayer()
// vaddr 0x2244164 | ghidra 0x2344164 | size 4 | symbol _ZN4Aska11AudioPlayerD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska11AudioPlayerD0Ev(void)

{
  code *pcVar1;
  
                    /* WARNING: Does not return */
  pcVar1 = (code *)SoftwareBreakpoint(1,0x2344168);
  (*pcVar1)();
}

// ==== Aska::AudioPlayer::SetupDevice()
// vaddr 0x2244168 | ghidra 0x2344168 | size 116 | symbol _ZN4Aska11AudioPlayer11SetupDeviceEv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska11AudioPlayer11SetupDeviceEv(long param_1)

{
  long lVar1;
  
  if (*(int *)(param_1 + 0x18) != 0) {
    return 0;
  }
  if (*(int *)(param_1 + 0x60) != 7) {
    if (*(long *)(param_1 + 0x68) != 0) {
      operator delete[](void*)();
      *(undefined8 *)(param_1 + 0x68) = 0;
    }
    lVar1 = Aska::SoundMemory::Malloc(unsigned long)(0xa8);
    *(long *)(param_1 + 0x68) = lVar1;
    if (lVar1 == 0) {
      *(undefined4 *)(param_1 + 0x60) = 0;
      return 0;
    }
    *(undefined4 *)(param_1 + 0x60) = 7;
    *(undefined8 *)(param_1 + 0x58) = 1;
  }
  *(undefined4 *)(param_1 + 0x18) = 1;
  return 1;
}

// ==== Aska::AudioPlayer::FinishDevice()
// vaddr 0x22441dc | ghidra 0x23441dc | size 56 | symbol _ZN4Aska11AudioPlayer12FinishDeviceEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska11AudioPlayer12FinishDeviceEv(long param_1)

{
  if (*(int *)(param_1 + 0x18) != 0) {
    *(undefined8 *)(param_1 + 0x58) = 1;
    *(undefined4 *)(param_1 + 0x60) = 0;
    if (*(long *)(param_1 + 0x68) != 0) {
      operator delete[](void*)();
      *(undefined8 *)(param_1 + 0x68) = 0;
    }
    *(undefined4 *)(param_1 + 0x18) = 0;
  }
  return;
}

// ==== Aska::AudioPlayer::SendMessage(unsigned int, void*, void*)
// vaddr 0x2244214 | ghidra 0x2344214 | size 372 | symbol _ZN4Aska11AudioPlayer11SendMessageEjPvS1_ | lib libSOA-3.7.0.so | 2026-10-08
bool _ZN4Aska11AudioPlayer11SendMessageEjPvS1_
               (long param_1,undefined4 param_2,undefined8 param_3,undefined8 param_4)

{
  int *piVar1;
  char cVar2;
  bool bVar3;
  undefined4 *puVar4;
  ulong uVar5;
  int iVar6;
  int *piVar7;
  
  piVar7 = (int *)(param_1 + 0xa8);
  iVar6 = 0;
  do {
    while (*piVar7 == -1) {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar7,0x10);
      if (bVar3) {
        *piVar7 = 0;
        cVar2 = ExclusiveMonitorsStatus();
      }
      if (cVar2 == '\0') goto code_r0x02344304;
    }
    ClearExclusiveLocal();
    bVar3 = iVar6 < 0x1ff;
    iVar6 = iVar6 + 1;
  } while (bVar3);
  piVar1 = (int *)(param_1 + 0xac);
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
        uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0xe8);
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
          Aska::Semaphore::Wait() const(param_1 + 0xe8);
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
          if (cVar2 == '\0') goto code_r0x023442f4;
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
code_r0x023442f4:
  do {
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar3) {
      *piVar1 = *piVar1 + -1;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
code_r0x02344304:
  DataMemoryBarrier(2,3);
  puVar4 = (undefined4 *)Aska::TSoundDynamicQueue<Aska::AudioMessage>::AddEx()(param_1 + 0x50);
  if (puVar4 != (undefined4 *)0x0) {
    *(undefined8 *)(puVar4 + 2) = param_3;
    *(undefined8 *)(puVar4 + 4) = param_4;
    *puVar4 = param_2;
  }
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_1 + 0xa8) = 0xffffffff;
  DataMemoryBarrier(2,3);
  piVar7 = (int *)(param_1 + 0xac);
  if (0x14 < *piVar7) {
    do {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar7,0x10);
      if (bVar3) {
        *piVar7 = *piVar7 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0xe8);
    if ((uVar5 & 1) != 0) {
      Aska::Semaphore::Signal() const(param_1 + 0xe8);
    }
  }
  return puVar4 != (undefined4 *)0x0;
}

// ==== Aska::AudioPlayer::GetMessage(Aska::AudioMessage*)
// vaddr 0x224446c | ghidra 0x234446c | size 392 | symbol _ZN4Aska11AudioPlayer10GetMessageEPNS_12AudioMessageE | lib libSOA-3.7.0.so | 2026-10-08
bool _ZN4Aska11AudioPlayer10GetMessageEPNS_12AudioMessageE(long param_1,undefined8 *param_2)

{
  int *piVar1;
  uint uVar2;
  char cVar3;
  bool bVar4;
  bool bVar5;
  ulong uVar6;
  int iVar7;
  undefined8 *puVar8;
  int *piVar9;
  undefined8 uVar10;
  
  piVar9 = (int *)(param_1 + 0xa8);
  iVar7 = 0;
  do {
    while (*piVar9 == -1) {
      cVar3 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar9,0x10);
      if (bVar5) {
        *piVar9 = 0;
        cVar3 = ExclusiveMonitorsStatus();
      }
      if (cVar3 == '\0') goto code_r0x02344550;
    }
    ClearExclusiveLocal();
    bVar5 = iVar7 < 0x1ff;
    iVar7 = iVar7 + 1;
  } while (bVar5);
  piVar1 = (int *)(param_1 + 0xac);
  do {
    cVar3 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar5) {
      *piVar1 = *piVar1 + 1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
  do {
    if (*piVar9 != -1) {
      ClearExclusiveLocal();
      do {
        uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0xe8);
        if ((uVar6 & 1) == 0) {
          do {
            cVar3 = '\x01';
            bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
            if (bVar5) {
              *piVar1 = *piVar1 + -1;
              cVar3 = ExclusiveMonitorsStatus();
            }
          } while (cVar3 != '\0');
          Aska::Thread::Sleep(unsigned int)(1);
        }
        else {
          Aska::Semaphore::Wait() const(param_1 + 0xe8);
        }
        do {
          cVar3 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar5) {
            *piVar1 = *piVar1 + 1;
            cVar3 = ExclusiveMonitorsStatus();
          }
        } while (cVar3 != '\0');
        while (*piVar9 == -1) {
          cVar3 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(piVar9,0x10);
          if (bVar5) {
            *piVar9 = 0;
            cVar3 = ExclusiveMonitorsStatus();
          }
          if (cVar3 == '\0') goto code_r0x02344540;
        }
        ClearExclusiveLocal();
      } while( true );
    }
    cVar3 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar9,0x10);
    if (bVar5) {
      *piVar9 = 0;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
code_r0x02344540:
  do {
    cVar3 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar5) {
      *piVar1 = *piVar1 + -1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
code_r0x02344550:
  DataMemoryBarrier(2,3);
  uVar2 = 0;
  if (*(int *)(param_1 + 0x5c) + 1U < *(uint *)(param_1 + 0x60)) {
    uVar2 = *(int *)(param_1 + 0x5c) + 1;
  }
  bVar5 = uVar2 != *(uint *)(param_1 + 0x58);
  if (bVar5) {
    *(uint *)(param_1 + 0x5c) = uVar2;
    puVar8 = (undefined8 *)(*(long *)(param_1 + 0x68) + (ulong)uVar2 * 0x18);
    param_2[2] = puVar8[2];
    uVar10 = *puVar8;
    param_2[1] = puVar8[1];
    *param_2 = uVar10;
  }
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_1 + 0xa8) = 0xffffffff;
  DataMemoryBarrier(2,3);
  piVar9 = (int *)(param_1 + 0xac);
  if (0x14 < *piVar9) {
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
      if (bVar4) {
        *piVar9 = *piVar9 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
    uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0xe8);
    if ((uVar6 & 1) != 0) {
      Aska::Semaphore::Signal() const(param_1 + 0xe8);
    }
  }
  return bVar5;
}

// ==== Aska::AudioPlayer::AudioRun()
// vaddr 0x22445f4 | ghidra 0x23445f4 | size 304 | symbol _ZN4Aska11AudioPlayer8AudioRunEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska11AudioPlayer8AudioRunEv(long *param_1)

{
  float fVar1;
  float fVar2;
  
  (**(code **)(*param_1 + 0x78))();
  if (((int)param_1[3] != 4) && ((int)param_1[3] != 2)) {
    return;
  }
  if (*(char *)((long)param_1 + 0x29) != '\0') {
    fVar2 = *(float *)((long)param_1 + 0x1c);
    fVar1 = *(float *)((long)param_1 + 0x24) + *(float *)(param_1 + 4);
    *(float *)(param_1 + 4) = fVar1;
    if (0.0 <= *(float *)((long)param_1 + 0x24)) {
      if (fVar2 <= fVar1) goto code_r0x02344644;
    }
    else if (fVar1 <= fVar2) {
code_r0x02344644:
      *(float *)(param_1 + 4) = fVar2;
      *(undefined1 *)((long)param_1 + 0x29) = 0;
      fVar1 = fVar2;
    }
    (**(code **)(*param_1 + 0x80))(fVar1,param_1,(char)param_1[5]);
  }
  if (*(char *)((long)param_1 + 0x39) != '\0') {
    fVar2 = *(float *)((long)param_1 + 0x2c);
    fVar1 = *(float *)((long)param_1 + 0x34) + *(float *)(param_1 + 6);
    *(float *)(param_1 + 6) = fVar1;
    if (0.0 <= *(float *)((long)param_1 + 0x34)) {
      if (fVar2 <= fVar1) goto code_r0x0234468c;
    }
    else if (fVar1 <= fVar2) {
code_r0x0234468c:
      *(float *)(param_1 + 6) = fVar2;
      *(undefined1 *)((long)param_1 + 0x39) = 0;
      fVar1 = fVar2;
    }
    (**(code **)(*param_1 + 0x80))(fVar1,param_1,(char)param_1[7]);
  }
  if (*(char *)((long)param_1 + 0x49) == '\0') {
    return;
  }
  fVar2 = *(float *)((long)param_1 + 0x3c);
  fVar1 = *(float *)((long)param_1 + 0x44) + *(float *)(param_1 + 8);
  *(float *)(param_1 + 8) = fVar1;
  if (0.0 <= *(float *)((long)param_1 + 0x44)) {
    if (fVar1 < fVar2) goto code_r0x023446e0;
  }
  else if (fVar2 < fVar1) goto code_r0x023446e0;
  *(float *)(param_1 + 8) = fVar2;
  *(undefined1 *)((long)param_1 + 0x49) = 0;
  fVar1 = fVar2;
code_r0x023446e0:
                    /* WARNING: Could not recover jumptable at 0x023446f4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*param_1 + 0x80))(fVar1,param_1,(char)param_1[9]);
  return;
}

// ==== Aska::AudioPlayer::SetDeviceParam(unsigned int, float, float)
// vaddr 0x2244724 | ghidra 0x2344724 | size 140 | symbol _ZN4Aska11AudioPlayer14SetDeviceParamEjff | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8
_ZN4Aska11AudioPlayer14SetDeviceParamEjff(float param_1,float param_2,long *param_3,uint param_4)

{
  undefined8 uVar1;
  float fVar2;
  float fVar3;
  
  if ((param_4 < 3) &&
     (fVar2 = (float)(**(code **)(*param_3 + 0x88))(param_3,param_4), fVar2 != param_1)) {
    fVar3 = param_1 - fVar2;
    if (param_2 != 0.0) {
      fVar3 = (fVar3 * _UNK_029d94a4) / param_2;
    }
    uVar1 = 1;
    *(char *)(param_3 + (ulong)param_4 * 2 + 5) = (char)param_4;
    *(float *)((long)param_3 + (ulong)param_4 * 0x10 + 0x1c) = param_1;
    *(float *)(param_3 + (ulong)param_4 * 2 + 4) = fVar2;
    *(float *)((long)param_3 + (ulong)param_4 * 0x10 + 0x24) = fVar3;
    *(undefined1 *)((long)param_3 + (ulong)param_4 * 0x10 + 0x29) = 1;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

// ==== Aska::AudioPlayer::GetDeviceParam(unsigned int)
// vaddr 0x22447b0 | ghidra 0x23447b0 | size 52 | symbol _ZN4Aska11AudioPlayer14GetDeviceParamEj | lib libSOA-3.7.0.so | 2026-10-08
undefined1  [16] _ZN4Aska11AudioPlayer14GetDeviceParamEj(long *param_1,uint param_2)

{
  uint uVar1;
  undefined4 extraout_s0;
  undefined4 extraout_var;
  undefined8 extraout_var_00;
  undefined1 auVar2 [16];
  
  uVar1 = 0;
  if (param_2 < 3) {
    if (*(char *)((long)param_1 + (ulong)param_2 * 0x10 + 0x29) == '\0') {
                    /* WARNING: Could not recover jumptable at 0x023447e0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (**(code **)(*param_1 + 0x88))(0);
      auVar2._4_4_ = extraout_var;
      auVar2._0_4_ = extraout_s0;
      auVar2._8_8_ = extraout_var_00;
      return auVar2;
    }
    uVar1 = *(uint *)((long)param_1 + (ulong)param_2 * 0x10 + 0x1c);
  }
  return ZEXT416(uVar1);
}

// ==== Aska::AudioSignalNotify::AddSignalVoiceList(Aska::SLVoice*)
// vaddr 0x224595c | ghidra 0x234595c | size 580 | symbol _ZN4Aska17AudioSignalNotify18AddSignalVoiceListEPNS_7SLVoiceE | lib libSOA-3.7.0.so | 2026-10-08
undefined4 _ZN4Aska17AudioSignalNotify18AddSignalVoiceListEPNS_7SLVoiceE(long param_1,long param_2)

{
  int *piVar1;
  char cVar2;
  bool bVar3;
  ulong uVar4;
  int iVar5;
  long *plVar6;
  int *piVar7;
  undefined4 uVar8;
  
  piVar7 = (int *)(param_1 + 0xe0);
  iVar5 = 0;
  do {
    while (*piVar7 == -1) {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar7,0x10);
      if (bVar3) {
        *piVar7 = 0;
        cVar2 = ExclusiveMonitorsStatus();
      }
      if (cVar2 == '\0') goto code_r0x02345a40;
    }
    ClearExclusiveLocal();
    bVar3 = iVar5 < 0x1ff;
    iVar5 = iVar5 + 1;
  } while (bVar3);
  piVar1 = (int *)(param_1 + 0xe4);
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
        uVar4 = Aska::Semaphore::IsReady() const(param_1 + 0x120);
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
          Aska::Semaphore::Wait() const(param_1 + 0x120);
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
          if (cVar2 == '\0') goto code_r0x02345a30;
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
code_r0x02345a30:
  do {
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar3) {
      *piVar1 = *piVar1 + -1;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
code_r0x02345a40:
  DataMemoryBarrier(2,3);
  plVar6 = (long *)(param_1 + 8);
  if (((((((*plVar6 == 0) || (plVar6 = (long *)(param_1 + 0x10), *plVar6 == 0)) ||
         (plVar6 = (long *)(param_1 + 0x18), *plVar6 == 0)) ||
        ((plVar6 = (long *)(param_1 + 0x20), *plVar6 == 0 ||
         (plVar6 = (long *)(param_1 + 0x28), *plVar6 == 0)))) ||
       (((plVar6 = (long *)(param_1 + 0x30), *plVar6 == 0 ||
         ((plVar6 = (long *)(param_1 + 0x38), *plVar6 == 0 ||
          (plVar6 = (long *)(param_1 + 0x40), *plVar6 == 0)))) ||
        (plVar6 = (long *)(param_1 + 0x48), *plVar6 == 0)))) ||
      ((((plVar6 = (long *)(param_1 + 0x50), *plVar6 == 0 ||
         (plVar6 = (long *)(param_1 + 0x58), *plVar6 == 0)) ||
        (plVar6 = (long *)(param_1 + 0x60), *plVar6 == 0)) ||
       (((plVar6 = (long *)(param_1 + 0x68), *plVar6 == 0 ||
         (plVar6 = (long *)(param_1 + 0x70), *plVar6 == 0)) ||
        ((plVar6 = (long *)(param_1 + 0x78), *plVar6 == 0 ||
         ((plVar6 = (long *)(param_1 + 0x80), *plVar6 == 0 ||
          (plVar6 = (long *)(param_1 + 0x88), *plVar6 == 0)))))))))) ||
     ((plVar6 = (long *)(param_1 + 0x90), *plVar6 == 0 ||
      ((plVar6 = (long *)(param_1 + 0x98), *plVar6 == 0 ||
       (plVar6 = (long *)(param_1 + 0xa0), *plVar6 == 0)))))) {
    *plVar6 = param_2;
    uVar8 = 1;
  }
  else {
    uVar8 = 0;
  }
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_1 + 0xe0) = 0xffffffff;
  DataMemoryBarrier(2,3);
  piVar7 = (int *)(param_1 + 0xe4);
  if (0x14 < *piVar7) {
    do {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar7,0x10);
      if (bVar3) {
        *piVar7 = *piVar7 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    uVar4 = Aska::Semaphore::IsReady() const(param_1 + 0x120);
    if ((uVar4 & 1) != 0) {
      Aska::Semaphore::Signal() const(param_1 + 0x120);
    }
  }
  return uVar8;
}

// ==== Aska::AudioSignalNotify::DeleteSignalVoiceList(Aska::SLVoice*)
// vaddr 0x2245ba0 | ghidra 0x2345ba0 | size 660 | symbol _ZN4Aska17AudioSignalNotify21DeleteSignalVoiceListEPNS_7SLVoiceE | lib libSOA-3.7.0.so | 2026-10-08
undefined4
_ZN4Aska17AudioSignalNotify21DeleteSignalVoiceListEPNS_7SLVoiceE(long param_1,long param_2)

{
  int *piVar1;
  char cVar2;
  bool bVar3;
  ulong uVar4;
  int iVar5;
  long *plVar6;
  int *piVar7;
  undefined4 uVar8;
  
  piVar7 = (int *)(param_1 + 0xe0);
  iVar5 = 0;
  do {
    while (*piVar7 == -1) {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar7,0x10);
      if (bVar3) {
        *piVar7 = 0;
        cVar2 = ExclusiveMonitorsStatus();
      }
      if (cVar2 == '\0') goto code_r0x02345c84;
    }
    ClearExclusiveLocal();
    bVar3 = iVar5 < 0x1ff;
    iVar5 = iVar5 + 1;
  } while (bVar3);
  piVar1 = (int *)(param_1 + 0xe4);
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
        uVar4 = Aska::Semaphore::IsReady() const(param_1 + 0x120);
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
          Aska::Semaphore::Wait() const(param_1 + 0x120);
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
          if (cVar2 == '\0') goto code_r0x02345c74;
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
code_r0x02345c74:
  do {
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar3) {
      *piVar1 = *piVar1 + -1;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
code_r0x02345c84:
  DataMemoryBarrier(2,3);
  plVar6 = (long *)(param_1 + 8);
  if (((((((*plVar6 == param_2) || (plVar6 = (long *)(param_1 + 0x10), *plVar6 == param_2)) ||
         (plVar6 = (long *)(param_1 + 0x18), *plVar6 == param_2)) ||
        ((plVar6 = (long *)(param_1 + 0x20), *plVar6 == param_2 ||
         (plVar6 = (long *)(param_1 + 0x28), *plVar6 == param_2)))) ||
       (((plVar6 = (long *)(param_1 + 0x30), *plVar6 == param_2 ||
         ((plVar6 = (long *)(param_1 + 0x38), *plVar6 == param_2 ||
          (plVar6 = (long *)(param_1 + 0x40), *plVar6 == param_2)))) ||
        (plVar6 = (long *)(param_1 + 0x48), *plVar6 == param_2)))) ||
      ((((plVar6 = (long *)(param_1 + 0x50), *plVar6 == param_2 ||
         (plVar6 = (long *)(param_1 + 0x58), *plVar6 == param_2)) ||
        (plVar6 = (long *)(param_1 + 0x60), *plVar6 == param_2)) ||
       (((plVar6 = (long *)(param_1 + 0x68), *plVar6 == param_2 ||
         (plVar6 = (long *)(param_1 + 0x70), *plVar6 == param_2)) ||
        ((plVar6 = (long *)(param_1 + 0x78), *plVar6 == param_2 ||
         ((plVar6 = (long *)(param_1 + 0x80), *plVar6 == param_2 ||
          (plVar6 = (long *)(param_1 + 0x88), *plVar6 == param_2)))))))))) ||
     ((plVar6 = (long *)(param_1 + 0x90), *plVar6 == param_2 ||
      ((plVar6 = (long *)(param_1 + 0x98), *plVar6 == param_2 ||
       (plVar6 = (long *)(param_1 + 0xa0), *plVar6 == param_2)))))) {
    uVar8 = 1;
    *plVar6 = 0;
  }
  else {
    uVar8 = 0;
  }
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_1 + 0xe0) = 0xffffffff;
  DataMemoryBarrier(2,3);
  piVar7 = (int *)(param_1 + 0xe4);
  if (0x14 < *piVar7) {
    do {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar7,0x10);
      if (bVar3) {
        *piVar7 = *piVar7 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    uVar4 = Aska::Semaphore::IsReady() const(param_1 + 0x120);
    if ((uVar4 & 1) != 0) {
      Aska::Semaphore::Signal() const(param_1 + 0x120);
    }
  }
  return uVar8;
}

// ==== Aska::AudioSignalNotify::GetSignalCount() const
// vaddr 0x2245e34 | ghidra 0x2345e34 | size 536 | symbol _ZNK4Aska17AudioSignalNotify14GetSignalCountEv | lib libSOA-3.7.0.so | 2026-10-08
uint _ZNK4Aska17AudioSignalNotify14GetSignalCountEv(long param_1)

{
  int *piVar1;
  uint uVar2;
  char cVar3;
  bool bVar4;
  ulong uVar5;
  int iVar6;
  int *piVar7;
  uint uVar8;
  
  piVar7 = (int *)(param_1 + 0xe0);
  iVar6 = 0;
  do {
    while (*piVar7 != -1) {
      ClearExclusiveLocal();
      bVar4 = 0x1fe < iVar6;
      iVar6 = iVar6 + 1;
      if (bVar4) {
        piVar1 = (int *)(param_1 + 0xe4);
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
              uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0x120);
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
                Aska::Semaphore::Wait() const(param_1 + 0x120);
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
                if (cVar3 == '\0') goto code_r0x02346034;
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
code_r0x02346034:
        do {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar4) {
            *piVar1 = *piVar1 + -1;
            cVar3 = ExclusiveMonitorsStatus();
          }
        } while (cVar3 != '\0');
        DataMemoryBarrier(2,3);
code_r0x02345ea8:
        piVar7 = (int *)(param_1 + 0xe4);
        DataMemoryBarrier(2,3);
        *(undefined4 *)(param_1 + 0xe0) = 0xffffffff;
        bVar4 = *(long *)(param_1 + 0x10) != 0;
        uVar8 = 2;
        if (!bVar4) {
          uVar8 = 1;
        }
        uVar2 = (uint)bVar4;
        if (*(long *)(param_1 + 8) != 0) {
          uVar2 = uVar8;
        }
        if (*(long *)(param_1 + 0x18) != 0) {
          uVar2 = uVar2 + 1;
        }
        if (*(long *)(param_1 + 0x20) != 0) {
          uVar2 = uVar2 + 1;
        }
        if (*(long *)(param_1 + 0x28) != 0) {
          uVar2 = uVar2 + 1;
        }
        if (*(long *)(param_1 + 0x30) != 0) {
          uVar2 = uVar2 + 1;
        }
        if (*(long *)(param_1 + 0x38) != 0) {
          uVar2 = uVar2 + 1;
        }
        if (*(long *)(param_1 + 0x40) != 0) {
          uVar2 = uVar2 + 1;
        }
        if (*(long *)(param_1 + 0x48) != 0) {
          uVar2 = uVar2 + 1;
        }
        if (*(long *)(param_1 + 0x50) != 0) {
          uVar2 = uVar2 + 1;
        }
        if (*(long *)(param_1 + 0x58) != 0) {
          uVar2 = uVar2 + 1;
        }
        if (*(long *)(param_1 + 0x60) != 0) {
          uVar2 = uVar2 + 1;
        }
        if (*(long *)(param_1 + 0x68) != 0) {
          uVar2 = uVar2 + 1;
        }
        if (*(long *)(param_1 + 0x70) != 0) {
          uVar2 = uVar2 + 1;
        }
        if (*(long *)(param_1 + 0x78) != 0) {
          uVar2 = uVar2 + 1;
        }
        DataMemoryBarrier(2,3);
        if (*(long *)(param_1 + 0x80) != 0) {
          uVar2 = uVar2 + 1;
        }
        if (*(long *)(param_1 + 0x88) != 0) {
          uVar2 = uVar2 + 1;
        }
        if (*(long *)(param_1 + 0x90) != 0) {
          uVar2 = uVar2 + 1;
        }
        if (*(long *)(param_1 + 0x98) != 0) {
          uVar2 = uVar2 + 1;
        }
        if (*(long *)(param_1 + 0xa0) != 0) {
          uVar2 = uVar2 + 1;
        }
        if (0x14 < *(int *)(param_1 + 0xe4)) {
          do {
            cVar3 = '\x01';
            bVar4 = (bool)ExclusiveMonitorPass(piVar7,0x10);
            if (bVar4) {
              *piVar7 = *piVar7 + -1;
              cVar3 = ExclusiveMonitorsStatus();
            }
          } while (cVar3 != '\0');
          uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0x120);
          if ((uVar5 & 1) != 0) {
            Aska::Semaphore::Signal() const(param_1 + 0x120);
          }
        }
        return uVar2;
      }
    }
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar7,0x10);
    if (bVar4) {
      *piVar7 = 0;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
  DataMemoryBarrier(2,3);
  goto code_r0x02345ea8;
}

// ==== Aska::AudioSignalNotify::Handler(unsigned long)
// vaddr 0x224604c | ghidra 0x234604c | size 808 | symbol _ZN4Aska17AudioSignalNotify7HandlerEm | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska17AudioSignalNotify7HandlerEm(long param_1)

{
  int *piVar1;
  char cVar2;
  bool bVar3;
  long *plVar4;
  ulong uVar5;
  int iVar6;
  int *piVar7;
  
  piVar7 = (int *)(param_1 + 0xe0);
  iVar6 = 0;
  do {
    while (*piVar7 == -1) {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar7,0x10);
      if (bVar3) {
        *piVar7 = 0;
        cVar2 = ExclusiveMonitorsStatus();
      }
      if (cVar2 == '\0') goto code_r0x0234612c;
    }
    ClearExclusiveLocal();
    bVar3 = iVar6 < 0x1ff;
    iVar6 = iVar6 + 1;
  } while (bVar3);
  piVar1 = (int *)(param_1 + 0xe4);
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
        uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0x120);
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
          Aska::Semaphore::Wait() const(param_1 + 0x120);
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
          if (cVar2 == '\0') goto code_r0x0234611c;
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
code_r0x0234611c:
  do {
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar3) {
      *piVar1 = *piVar1 + -1;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
code_r0x0234612c:
  DataMemoryBarrier(2,3);
  plVar4 = *(long **)(param_1 + 8);
  if (plVar4 != (long *)0x0) {
    (**(code **)(*plVar4 + 0x50))(plVar4,0);
  }
  plVar4 = *(long **)(param_1 + 0x10);
  if (plVar4 != (long *)0x0) {
    (**(code **)(*plVar4 + 0x50))(plVar4,1);
  }
  plVar4 = *(long **)(param_1 + 0x18);
  if (plVar4 != (long *)0x0) {
    (**(code **)(*plVar4 + 0x50))(plVar4,2);
  }
  plVar4 = *(long **)(param_1 + 0x20);
  if (plVar4 != (long *)0x0) {
    (**(code **)(*plVar4 + 0x50))(plVar4,3);
  }
  plVar4 = *(long **)(param_1 + 0x28);
  if (plVar4 != (long *)0x0) {
    (**(code **)(*plVar4 + 0x50))(plVar4,4);
  }
  plVar4 = *(long **)(param_1 + 0x30);
  if (plVar4 != (long *)0x0) {
    (**(code **)(*plVar4 + 0x50))(plVar4,5);
  }
  plVar4 = *(long **)(param_1 + 0x38);
  if (plVar4 != (long *)0x0) {
    (**(code **)(*plVar4 + 0x50))(plVar4,6);
  }
  plVar4 = *(long **)(param_1 + 0x40);
  if (plVar4 != (long *)0x0) {
    (**(code **)(*plVar4 + 0x50))(plVar4,7);
  }
  plVar4 = *(long **)(param_1 + 0x48);
  if (plVar4 != (long *)0x0) {
    (**(code **)(*plVar4 + 0x50))(plVar4,8);
  }
  plVar4 = *(long **)(param_1 + 0x50);
  if (plVar4 != (long *)0x0) {
    (**(code **)(*plVar4 + 0x50))(plVar4,9);
  }
  plVar4 = *(long **)(param_1 + 0x58);
  if (plVar4 != (long *)0x0) {
    (**(code **)(*plVar4 + 0x50))(plVar4,10);
  }
  plVar4 = *(long **)(param_1 + 0x60);
  if (plVar4 != (long *)0x0) {
    (**(code **)(*plVar4 + 0x50))(plVar4,0xb);
  }
  plVar4 = *(long **)(param_1 + 0x68);
  if (plVar4 != (long *)0x0) {
    (**(code **)(*plVar4 + 0x50))(plVar4,0xc);
  }
  plVar4 = *(long **)(param_1 + 0x70);
  if (plVar4 != (long *)0x0) {
    (**(code **)(*plVar4 + 0x50))(plVar4,0xd);
  }
  plVar4 = *(long **)(param_1 + 0x78);
  if (plVar4 != (long *)0x0) {
    (**(code **)(*plVar4 + 0x50))(plVar4,0xe);
  }
  plVar4 = *(long **)(param_1 + 0x80);
  if (plVar4 != (long *)0x0) {
    (**(code **)(*plVar4 + 0x50))(plVar4,0xf);
  }
  plVar4 = *(long **)(param_1 + 0x88);
  if (plVar4 != (long *)0x0) {
    (**(code **)(*plVar4 + 0x50))(plVar4,0x10);
  }
  plVar4 = *(long **)(param_1 + 0x90);
  if (plVar4 != (long *)0x0) {
    (**(code **)(*plVar4 + 0x50))(plVar4,0x11);
  }
  plVar4 = *(long **)(param_1 + 0x98);
  if (plVar4 != (long *)0x0) {
    (**(code **)(*plVar4 + 0x50))(plVar4,0x12);
  }
  plVar4 = *(long **)(param_1 + 0xa0);
  if (plVar4 != (long *)0x0) {
    (**(code **)(*plVar4 + 0x50))(plVar4,0x13);
  }
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_1 + 0xe0) = 0xffffffff;
  DataMemoryBarrier(2,3);
  piVar7 = (int *)(param_1 + 0xe4);
  if (0x14 < *piVar7) {
    do {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar7,0x10);
      if (bVar3) {
        *piVar7 = *piVar7 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0x120);
    if ((uVar5 & 1) != 0) {
      (*(code *)PTR__ZNK4Aska9Semaphore6SignalEv_02c96cd0)(param_1 + 0x120);
      return;
    }
  }
  return;
}

// ==== Aska::AudioSignal::DeleteThis(Aska::DeleteManager*)
// vaddr 0x2246374 | ghidra 0x2346374 | size 4 | symbol _ZN4Aska11AudioSignal10DeleteThisEPNS_13DeleteManagerE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska11AudioSignal10DeleteThisEPNS_13DeleteManagerE(void)

{
  (*(code *)PTR__ZN4Aska4Task10DeleteThisEPNS_13DeleteManagerE_02cac0f0)();
  return;
}

// ==== Aska::AudioSignal::AddSignalVoiceList(Aska::SLVoice*)
// vaddr 0x2246378 | ghidra 0x2346378 | size 132 | symbol _ZN4Aska11AudioSignal18AddSignalVoiceListEPNS_7SLVoiceE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska11AudioSignal18AddSignalVoiceListEPNS_7SLVoiceE(long param_1,undefined8 param_2)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  
  iVar1 = Aska::AudioSignalNotify::GetSignalCount() const(param_1 + 0x28);
  if (iVar1 == -1) {
    uVar2 = 0xffffffff;
  }
  else {
    uVar2 = Aska::AudioSignalNotify::GetSignalCount() const(param_1 + 0x28);
  }
  uVar3 = Aska::AudioSignalNotify::GetSignalCount() const(param_1 + 0x160);
  if (uVar3 < uVar2) {
    Aska::AudioSignalNotify::GetSignalCount() const(param_1 + 0x160);
  }
  (*(code *)PTR__ZN4Aska17AudioSignalNotify18AddSignalVoiceListEPNS_7SLVoiceE_02cb3260)
            (param_1 + (ulong)(uVar3 < uVar2) * 0x138 + 0x28,param_2);
  return;
}

// ==== Aska::AudioSignal::DeleteSignalVoiceList(Aska::SLVoice*)
// vaddr 0x22463fc | ghidra 0x23463fc | size 60 | symbol _ZN4Aska11AudioSignal21DeleteSignalVoiceListEPNS_7SLVoiceE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Possible PIC construction at 0x02346410: Changing call to branch */
/* WARNING: Removing unreachable block (ram,0x02346414) */
/* WARNING: Removing unreachable block (ram,0x02346424) */
/* WARNING: Removing unreachable block (ram,0x02346418) */

void _ZN4Aska11AudioSignal21DeleteSignalVoiceListEPNS_7SLVoiceE(long param_1)

{
  (*(code *)PTR__ZN4Aska17AudioSignalNotify21DeleteSignalVoiceListEPNS_7SLVoiceE_02cad770)
            (param_1 + 0x28);
  return;
}

// ==== Aska::AudioSignal::Run(int)
// vaddr 0x2246438 | ghidra 0x2346438 | size 164 | symbol _ZN4Aska11AudioSignal3RunEi | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska11AudioSignal3RunEi(long param_1)

{
  undefined4 uVar1;
  int iVar2;
  ulong uVar3;
  undefined8 uVar4;
  
  uVar1 = Aska::Global::GetCPUTime()();
  *(undefined4 *)(param_1 + 0x298) = uVar1;
  uVar4 = *(undefined8 *)PTR__ZN4Aska6Global20m_pMessageDispatcherE_02cb77c8;
  iVar2 = Aska::AudioSignalNotify::GetSignalCount() const(param_1 + 0x28);
  if (iVar2 != 0) {
    while (uVar3 = Aska::SimpleMessageDispatcher::PostMessage(unsigned short, Aska::INotify*, void*, void*, unsigned int*, signed char)(uVar4,0x467,param_1 + 0x28,0,0,0,0), (uVar3 & 1) == 0) {
      Aska::Thread::Switch()();
    }
  }
  iVar2 = Aska::AudioSignalNotify::GetSignalCount() const(param_1 + 0x160);
  if (iVar2 != 0) {
    while (uVar3 = Aska::SimpleMessageDispatcher::PostMessage(unsigned short, Aska::INotify*, void*, void*, unsigned int*, signed char)(uVar4,0x468,param_1 + 0x160,0,0,0,0), (uVar3 & 1) == 0) {
      Aska::Thread::Switch()();
    }
  }
  return;
}

// ==== Aska::AudioSafetySignalNotify::Initialize(Aska::Event*)
// vaddr 0x22464dc | ghidra 0x23464dc | size 16 | symbol _ZN4Aska23AudioSafetySignalNotify10InitializeEPNS_5EventE | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska23AudioSafetySignalNotify10InitializeEPNS_5EventE(long param_1,undefined8 param_2)

{
  *(undefined8 *)(param_1 + 8) = param_2;
  return 1;
}

// ==== Aska::AudioSafetySignalNotify::Finalize()
// vaddr 0x22464ec | ghidra 0x23464ec | size 8 | symbol _ZN4Aska23AudioSafetySignalNotify8FinalizeEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska23AudioSafetySignalNotify8FinalizeEv(long param_1)

{
  *(undefined8 *)(param_1 + 8) = 0;
  return;
}

// ==== Aska::AudioSafetySignalNotify::Handler(unsigned long)
// vaddr 0x22464f4 | ghidra 0x23464f4 | size 80 | symbol _ZN4Aska23AudioSafetySignalNotify7HandlerEm | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska23AudioSafetySignalNotify7HandlerEm(long param_1)

{
  int iVar1;
  long lVar2;
  
  lVar2 = *(long *)(*(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50 + 0x40);
  iVar1 = Aska::Global::GetCPUTime()();
  if ((0x42 < iVar1 - *(int *)(lVar2 + 0x298)) && (*(long *)(param_1 + 8) != 0)) {
    (*(code *)PTR__ZNK4Aska5Event3SetEv_02c9dcf0)();
    return;
  }
  return;
}

// ==== Aska::AudioSafetySignalThread::Initialize()
// vaddr 0x2246544 | ghidra 0x2346544 | size 64 | symbol _ZN4Aska23AudioSafetySignalThread10InitializeEv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska23AudioSafetySignalThread10InitializeEv(long param_1)

{
  undefined8 uVar1;
  ulong uVar2;
  
  uVar2 = Aska::Thread::Create(bool, int, int, bool)(param_1,0,0x81,0x8000,1);
  if ((uVar2 & 1) != 0) {
    uVar1 = (*(code *)PTR__ZN4Aska5Event6CreateEbb_02c9b448)(param_1 + 0x18,1,0);
    return uVar1;
  }
  return 0;
}

// ==== Aska::AudioSafetySignalThread::Handler()
// vaddr 0x2246584 | ghidra 0x2346584 | size 116 | symbol _ZN4Aska23AudioSafetySignalThread7HandlerEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska23AudioSafetySignalThread7HandlerEv(long param_1)

{
  undefined *puVar1;
  long lVar2;
  
  puVar1 = PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50;
  do {
    Aska::Event::Wait(unsigned int) const(param_1 + 0x18,0);
    Aska::Event::Reset() const(param_1 + 0x18);
    if (*(char *)(param_1 + 0x80) != '\0') {
      Aska::Thread::Exit()();
    }
    lVar2 = *(long *)(*(long *)puVar1 + 0x40);
    (*(code *)**(undefined8 **)(lVar2 + 0x28))((undefined8 *)(lVar2 + 0x28),0);
    (*(code *)**(undefined8 **)(lVar2 + 0x160))(lVar2 + 0x160,0);
  } while( true );
}

// ==== Aska::AudioSignalNotify::~AudioSignalNotify()
// vaddr 0x22465f8 | ghidra 0x23465f8 | size 20 | symbol _ZN4Aska17AudioSignalNotifyD2Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska17AudioSignalNotifyD2Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska17AudioSignalNotifyE_02cb9718 + 0x10);
  (*(code *)PTR__ZN4Aska19FastCriticalSectionD2Ev_02ca21e0)(param_1 + 0x15);
  return;
}

// ==== Aska::AudioSignalNotify::~AudioSignalNotify()
// vaddr 0x224660c | ghidra 0x234660c | size 40 | symbol _ZN4Aska17AudioSignalNotifyD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska17AudioSignalNotifyD0Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska17AudioSignalNotifyE_02cb9718 + 0x10);
  Aska::FastCriticalSection::~FastCriticalSection()(param_1 + 0x15);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::AudioSignal::~AudioSignal()
// vaddr 0x2246634 | ghidra 0x2346634 | size 80 | symbol _ZN4Aska11AudioSignalD2Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska11AudioSignalD2Ev(long *param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZTVN4Aska17AudioSignalNotifyE_02cb9718 + 0x10;
  *param_1 = (long)(PTR__ZTVN4Aska11AudioSignalE_02cb93d0 + 0x10);
  param_1[0x2c] = (long)puVar1;
  Aska::FastCriticalSection::~FastCriticalSection()(param_1 + 0x41);
  param_1[5] = (long)puVar1;
  Aska::FastCriticalSection::~FastCriticalSection()(param_1 + 0x1a);
  (*(code *)PTR__ZN4Aska4TaskD1Ev_02c92d10)(param_1);
  return;
}

// ==== Aska::AudioSignal::~AudioSignal()
// vaddr 0x2246684 | ghidra 0x2346684 | size 88 | symbol _ZN4Aska11AudioSignalD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska11AudioSignalD0Ev(long *param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZTVN4Aska17AudioSignalNotifyE_02cb9718 + 0x10;
  *param_1 = (long)(PTR__ZTVN4Aska11AudioSignalE_02cb93d0 + 0x10);
  param_1[0x2c] = (long)puVar1;
  Aska::FastCriticalSection::~FastCriticalSection()(param_1 + 0x41);
  param_1[5] = (long)puVar1;
  Aska::FastCriticalSection::~FastCriticalSection()(param_1 + 0x1a);
  Aska::Task::~Task()(param_1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::AudioSignal::GetClassID(int) const
// vaddr 0x22466dc | ghidra 0x23466dc | size 72 | symbol _ZNK4Aska11AudioSignal10GetClassIDEi | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK4Aska11AudioSignal10GetClassIDEi(undefined8 param_1,int param_2)

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
  return 0xf000f001f002f21d;
}

// ==== Aska::AudioSignal::GetDefaultLevel() const
// vaddr 0x2246724 | ghidra 0x2346724 | size 8 | symbol _ZNK4Aska11AudioSignal15GetDefaultLevelEv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK4Aska11AudioSignal15GetDefaultLevelEv(void)

{
  return 0x400000;
}

// ==== Aska::AudioSafetySignalNotify::~AudioSafetySignalNotify()
// vaddr 0x224672c | ghidra 0x234672c | size 4 | symbol _ZN4Aska23AudioSafetySignalNotifyD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska23AudioSafetySignalNotifyD0Ev(void)

{
  (*(code *)PTR__ZdlPv_02ca4758)();
  return;
}

// ==== Aska::AudioSafetySignalThread::~AudioSafetySignalThread()
// vaddr 0x2246730 | ghidra 0x2346730 | size 40 | symbol _ZN4Aska23AudioSafetySignalThreadD2Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska23AudioSafetySignalThreadD2Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska23AudioSafetySignalThreadE_02cbf2a0 + 0x10);
  Aska::Event::Exit()(param_1 + 3);
  (*(code *)PTR__ZN4Aska6ThreadD1Ev_02c9be08)(param_1);
  return;
}

// ==== Aska::AudioSafetySignalThread::~AudioSafetySignalThread()
// vaddr 0x2246758 | ghidra 0x2346758 | size 48 | symbol _ZN4Aska23AudioSafetySignalThreadD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska23AudioSafetySignalThreadD0Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska23AudioSafetySignalThreadE_02cbf2a0 + 0x10);
  Aska::Event::Exit()(param_1 + 3);
  Aska::Thread::~Thread()(param_1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}


// FAILED to create function at 02971c30 typeinfo name for Aska::TDynamicArray<Aska::AudioSmallHeap::HeapInfo, Aska::AudioAllocator<Aska::AudioSmallHeap::HeapInfo> >
// FAILED to create function at 02bb2de8 Aska::Audio3DEngine::vtable
// FAILED to create function at 02bb2e08 Aska::Audio3DEngine::typeinfo
// FAILED to create function at 02bb2f68 Aska::AudioListener::vtable
// FAILED to create function at 02bb2f88 Aska::AudioEmitter::vtable
// FAILED to create function at 02bb2fb0 Aska::Audio3DObject::typeinfo
// FAILED to create function at 02bb2fd0 Aska::AudioListener::typeinfo
// FAILED to create function at 02bb2ff0 Aska::AudioEmitter::typeinfo
// FAILED to create function at 02bb3008 Aska::Audio3DObject::vtable
// FAILED to create function at 02bb30e8 Aska::AudioMessageNote::vtable
// FAILED to create function at 02bb3110 Aska::AudioMessageNote::typeinfo
// FAILED to create function at 02bb33e8 Aska::TDynamicArray<Aska::AudioSmallHeap::HeapInfo,Aska::AudioAllocator<Aska::AudioSmallHeap::HeapInfo>>::vtable
// FAILED to create function at 02bb3408 Aska::TDynamicArray<Aska::AudioSmallHeap::HeapInfo,Aska::AudioAllocator<Aska::AudioSmallHeap::HeapInfo>>::typeinfo
// FAILED to create function at 02c5f298 Aska::AudioEffector::vtable
// FAILED to create function at 02c5f2f0 Aska::AudioEffector::typeinfo
// FAILED to create function at 02c5f458 Aska::AudioInterface::vtable
// FAILED to create function at 02c5f480 Aska::AudioInterface::typeinfo
// FAILED to create function at 02c5f498 Aska::AudioMixer::vtable
// FAILED to create function at 02c5f630 Aska::AudioMixer::typeinfo
// FAILED to create function at 02c5f6a8 Aska::AudioPlayer::vtable
// FAILED to create function at 02c5f7f0 Aska::AudioPlayer::typeinfo
// FAILED to create function at 02c5f898 Aska::AudioSignalNotify::vtable
// FAILED to create function at 02c5f8c0 Aska::AudioSignalNotify::typeinfo
// FAILED to create function at 02c5f8d8 Aska::AudioSignal::vtable
// FAILED to create function at 02c5f980 Aska::AudioSignal::typeinfo
// FAILED to create function at 02c5f998 Aska::AudioSafetySignalNotify::vtable
// FAILED to create function at 02c5f9c0 Aska::AudioSafetySignalNotify::typeinfo
// FAILED to create function at 02c5f9d8 Aska::AudioSafetySignalThread::vtable
// FAILED to create function at 02c5fa00 Aska::AudioSafetySignalThread::typeinfo
